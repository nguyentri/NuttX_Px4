/*
 * arch/arm/src/rzv/rzv_gpt.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_PWM

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

#include <nuttx/compiler.h>
#include <nuttx/arch.h>
#include <nuttx/irq.h>
#include <nuttx/timers/pwm.h>

#include "arm_internal.h"
#include "rzv_clock.h"
#include "rzv_icu.h"
#include "rzv_gpt.h"
#include "hardware/rzv_gpt.h"

/* GPT Pin Configuration Requirements:
 *
 * The GPT module requires proper GPIO pin configuration for PWM output.
 * Before using GPT/PWM, configure pins via rzv_gpio_config():
 *
 * For GPT channel N:
 *   - GTIOCA_N: PWM output A (channel 0 in CONFIG_PWM_MULTICHAN)
 *   - GTIOCB_N: PWM output B (channel 1 in CONFIG_PWM_MULTICHAN)
 *
 * Example for GPT0:
 *   rzv_gpio_config(GPIO_GPT0_GTIOCA);  // Configure as peripheral function
 *   rzv_gpio_config(GPIO_GPT0_GTIOCB);  // Configure as peripheral function
 *
 * Pin definitions should be in board.h using pinmap constants:
 *   #define GPIO_GPT0_GTIOCA  (GPIO_PERIPH | GPIO_PORT_XX | GPIO_PIN_YY | ...)
 *
 * Refer to RZV2H hardware manual for pin assignment tables and
 * peripheral function select (PSEL) values for each GPT channel.
 */

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifndef nitems
#  define nitems(a) (sizeof(a) / sizeof((a)[0]))
#endif

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct rzv_gpt_lowerhalf_s
{
  struct pwm_lowerhalf_s dev;
  uintptr_t              base;
  uint32_t               pclk;
  uint32_t               period;
  uint8_t                channel;   /* Logical channel index (0-15) */
  uint8_t                hw_ch;     /* HW channel within unit (channel % 8).
                                     * Used for GTSTR/GTSTP/GTCLR channel mask.
                                     * channel_mask = 1U << (channel % 8) for unit1. */
  uint8_t                divsel;
  bool                   initialized;
  bool                   running;
#ifdef CONFIG_PWM_PULSECOUNT
  volatile uint32_t      remaining;
  FAR void              *handle;
  int                    irq;
  bool                   oneshot;
#endif
};

struct rzv_gpt_divider_s
{
  uint16_t divider;
  uint8_t  tpcs;
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static inline uint32_t gpt_getreg(FAR struct rzv_gpt_lowerhalf_s *priv,
                                  unsigned int offset);
static inline void gpt_putreg(FAR struct rzv_gpt_lowerhalf_s *priv,
                              unsigned int offset, uint32_t value);
static inline void gpt_unlock(FAR struct rzv_gpt_lowerhalf_s *priv);
static inline void gpt_lock(FAR struct rzv_gpt_lowerhalf_s *priv);
static int  gpt_compute_period(FAR struct rzv_gpt_lowerhalf_s *priv,
                               uint32_t frequency,
                               FAR uint32_t *period,
                               FAR uint32_t *tpcs);
static uint32_t gpt_duty_to_counts(uint32_t period, ub16_t duty);
static uint32_t gpt_compose_gtior(uint32_t duty_a_counts,
                                  uint32_t duty_b_counts,
                                  uint32_t period_counts);
static uint32_t gpt_compute_gtuddtyc(uint32_t duty_a_counts,
                                     uint32_t duty_b_counts,
                                     uint32_t period_counts);

static int rzv_gpt_setup(FAR struct pwm_lowerhalf_s *dev);
static int rzv_gpt_shutdown(FAR struct pwm_lowerhalf_s *dev);
#ifdef CONFIG_PWM_PULSECOUNT
static int rzv_gpt_start(FAR struct pwm_lowerhalf_s *dev,
                         FAR const struct pwm_info_s *info,
                         FAR void *handle);
#else
static int rzv_gpt_start(FAR struct pwm_lowerhalf_s *dev,
                         FAR const struct pwm_info_s *info);
#endif
static int rzv_gpt_stop(FAR struct pwm_lowerhalf_s *dev);
static int rzv_gpt_ioctl(FAR struct pwm_lowerhalf_s *dev,
                         int cmd, unsigned long arg);

#ifdef CONFIG_PWM_PULSECOUNT
static int rzv_gpt_irq(int irq, FAR void *context, FAR void *arg);
static int rzv_gpt_attach_irq(FAR struct rzv_gpt_lowerhalf_s *priv);
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct pwm_ops_s g_rzv_gpt_ops =
{
  .setup    = rzv_gpt_setup,
  .shutdown = rzv_gpt_shutdown,
  .start    = rzv_gpt_start,
  .stop     = rzv_gpt_stop,
  .ioctl    = rzv_gpt_ioctl,
};

static const struct rzv_gpt_divider_s g_rzv_gpt_dividers[] =
{
  { 1,  GPT_TPCS_DIV1 },
  { 2,  GPT_TPCS_DIV2 },
  { 4,  GPT_TPCS_DIV4 },
  { 8,  GPT_TPCS_DIV8 },
  { 16, GPT_TPCS_DIV16 },
  { 32, GPT_TPCS_DIV32 },
  { 64, GPT_TPCS_DIV64 },
  { 128, GPT_TPCS_DIV128 },
  { 256, GPT_TPCS_DIV256 },
  { 512, GPT_TPCS_DIV512 },
  { 1024, GPT_TPCS_DIV1024 },
  { 2048, GPT_TPCS_DIV2048 },
  { 4096, GPT_TPCS_DIV4096 },
  { 8192, GPT_TPCS_DIV8192 },
};

#ifdef CONFIG_PWM_PULSECOUNT
/* Overflow ELC event IDs per logical channel.
 * Unit0 (logical 0-7) → U0 events; Unit1 (logical 8-15) → U1 events.
 * U1 events for GPT10-17 are indexed 0-7 within unit1. */
static const uint16_t g_rzv_gpt_overflow_event[RZV_GPT_LOGICAL_CHANNELS] =
{
  RZV_ELC_GPT_U0_GPT_ELCOVF_0,  /* logical 0  */
  RZV_ELC_GPT_U0_GPT_ELCOVF_1,  /* logical 1  */
  RZV_ELC_GPT_U0_GPT_ELCOVF_2,  /* logical 2  */
  RZV_ELC_GPT_U0_GPT_ELCOVF_3,  /* logical 3  */
  RZV_ELC_GPT_U0_GPT_ELCOVF_4,  /* logical 4  */
  RZV_ELC_GPT_U0_GPT_ELCOVF_5,  /* logical 5  */
  RZV_ELC_GPT_U0_GPT_ELCOVF_6,  /* logical 6  */
  RZV_ELC_GPT_U0_GPT_ELCOVF_7,  /* logical 7  */
  RZV_ELC_GPT_U1_GPT_ELCOVF_0,  /* logical 8  = physical GPT10 */
  RZV_ELC_GPT_U1_GPT_ELCOVF_1,  /* logical 9  = physical GPT11 */
  RZV_ELC_GPT_U1_GPT_ELCOVF_2,  /* logical 10 = physical GPT12 */
  RZV_ELC_GPT_U1_GPT_ELCOVF_3,  /* logical 11 = physical GPT13 */
  RZV_ELC_GPT_U1_GPT_ELCOVF_4,  /* logical 12 = physical GPT14 */
  RZV_ELC_GPT_U1_GPT_ELCOVF_5,  /* logical 13 = physical GPT15 */
  RZV_ELC_GPT_U1_GPT_ELCOVF_6,  /* logical 14 = physical GPT16 */
  RZV_ELC_GPT_U1_GPT_ELCOVF_7,  /* logical 15 = physical GPT17 */
};
#endif

#if defined(CONFIG_PWM_PULSECOUNT)
#  define RZV_GPT_PULSE_INIT \
    .remaining = 0,          \
    .handle    = NULL,       \
    .irq       = -1,         \
    .oneshot   = false,
#else
#  define RZV_GPT_PULSE_INIT
#endif

/* hw_ch: hardware channel within the GPT unit (ch % 8).
 * Used for GTSTR/GTSTP/GTCLR channel mask bits (unit-local bit index).
 * channel_mask = 1U << (channel % 8) for unit1 channels per RZ/V2H UM. */
#define RZV_GPT_LOWER_INIT(ch)                                 \
  {                                                             \
    .dev       = { .ops = &g_rzv_gpt_ops },                     \
    .base      = RZV_GPT_LOGICAL_BASE(ch),                       \
    .channel   = (ch),                                          \
    .hw_ch     = RZV_GPT_LOGICAL_UNIT_CHANNEL(ch),               \
    .pclk      = 0,                                             \
    .period    = 0,                                             \
    .divsel    = 0,                                             \
    .initialized = false,                                       \
    .running   = false,                                         \
    RZV_GPT_PULSE_INIT                                          \
  }

#ifdef CONFIG_RZV_GPT0
static struct rzv_gpt_lowerhalf_s g_rzv_gpt0 = RZV_GPT_LOWER_INIT(0);
#endif
#ifdef CONFIG_RZV_GPT1
static struct rzv_gpt_lowerhalf_s g_rzv_gpt1 = RZV_GPT_LOWER_INIT(1);
#endif
#ifdef CONFIG_RZV_GPT2
static struct rzv_gpt_lowerhalf_s g_rzv_gpt2 = RZV_GPT_LOWER_INIT(2);
#endif
#ifdef CONFIG_RZV_GPT3
static struct rzv_gpt_lowerhalf_s g_rzv_gpt3 = RZV_GPT_LOWER_INIT(3);
#endif
#ifdef CONFIG_RZV_GPT4
static struct rzv_gpt_lowerhalf_s g_rzv_gpt4 = RZV_GPT_LOWER_INIT(4);
#endif
#ifdef CONFIG_RZV_GPT5
static struct rzv_gpt_lowerhalf_s g_rzv_gpt5 = RZV_GPT_LOWER_INIT(5);
#endif
#ifdef CONFIG_RZV_GPT6
static struct rzv_gpt_lowerhalf_s g_rzv_gpt6 = RZV_GPT_LOWER_INIT(6);
#endif
#ifdef CONFIG_RZV_GPT7
static struct rzv_gpt_lowerhalf_s g_rzv_gpt7 = RZV_GPT_LOWER_INIT(7);
#endif
#ifdef CONFIG_RZV_GPT8
static struct rzv_gpt_lowerhalf_s g_rzv_gpt8 = RZV_GPT_LOWER_INIT(8);
#endif
#ifdef CONFIG_RZV_GPT9
static struct rzv_gpt_lowerhalf_s g_rzv_gpt9 = RZV_GPT_LOWER_INIT(9);
#endif
#ifdef CONFIG_RZV_GPT10
static struct rzv_gpt_lowerhalf_s g_rzv_gpt10 = RZV_GPT_LOWER_INIT(10);
#endif
#ifdef CONFIG_RZV_GPT11
static struct rzv_gpt_lowerhalf_s g_rzv_gpt11 = RZV_GPT_LOWER_INIT(11);
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static inline uint32_t gpt_getreg(FAR struct rzv_gpt_lowerhalf_s *priv,
                                  unsigned int offset)
{
  return getreg32(priv->base + offset);
}

static inline void gpt_putreg(FAR struct rzv_gpt_lowerhalf_s *priv,
                              unsigned int offset, uint32_t value)
{
  putreg32(value, priv->base + offset);
}

static inline void gpt_unlock(FAR struct rzv_gpt_lowerhalf_s *priv)
{
  gpt_putreg(priv, RZV_GPT_GTWP_OFFSET, GPT_GTWP_UNLOCK);
}

static inline void gpt_lock(FAR struct rzv_gpt_lowerhalf_s *priv)
{
  gpt_putreg(priv, RZV_GPT_GTWP_OFFSET, GPT_GTWP_LOCK);
}

static int gpt_compute_period(FAR struct rzv_gpt_lowerhalf_s *priv,
                              uint32_t frequency,
                              FAR uint32_t *period,
                              FAR uint32_t *tpcs)
{
  uint64_t clk = priv->pclk;
  uint64_t best_error = UINT64_MAX;
  uint32_t best_period = 0;
  uint32_t best_tpcs = 0;

  if (frequency == 0)
    {
      return -EINVAL;
    }

  /* Frequency range check (Step ):
   * Maximum: clk / (div1 * 2) — minimum 2-count period, div=1.
   * Minimum: clk / (div8192 * UINT32_MAX) — largest possible period.
   * Both limits checked implicitly by the best_period==0 sentinel below,
   * but return -ERANGE explicitly for cleaner error propagation. */
  uint64_t clk_hz = (uint64_t)clk;
  uint64_t freq_u  = (uint64_t)frequency;

  /* Max achievable: clk / (div1 * 2) = clk/2 */
  if (freq_u > clk_hz / 2u)
    {
      return -ERANGE;
    }

  /* Min achievable: clk / (div8192 * 0xFFFFFFFF) */
  uint64_t min_freq_num = clk_hz;
  uint64_t min_freq_den = (uint64_t)8192u * (uint64_t)UINT32_MAX;
  if (min_freq_den > 0 && freq_u < ((min_freq_num + min_freq_den - 1u) / min_freq_den))
    {
      return -ERANGE;
    }

  for (unsigned int i = 0; i < nitems(g_rzv_gpt_dividers); i++)
    {
      uint64_t denom = (uint64_t)frequency * g_rzv_gpt_dividers[i].divider;

      if (denom == 0)
        {
          continue;
        }

      uint64_t counts = (clk + (denom / 2u)) / denom;

      if (counts == 0 || counts > UINT32_MAX)
        {
          continue;
        }

      uint64_t actual = ((uint64_t)counts) * denom;
      uint64_t error = (clk > actual) ? (clk - actual) : (actual - clk);

      if (error < best_error)
        {
          best_error = error;
          best_period = (uint32_t)counts;
          best_tpcs = g_rzv_gpt_dividers[i].tpcs;

          if (error == 0)
            {
              break;
            }
        }
    }

  if (best_period == 0)
    {
      return -ERANGE;
    }

  *period = best_period;
  *tpcs = best_tpcs;
  return OK;
}

static uint32_t gpt_duty_to_counts(uint32_t period, ub16_t duty)
{
  /* Use 64-bit arithmetic to prevent overflow even with maximum
   * 32-bit period and 16-bit duty cycle values.
   * Add 0x8000 for rounding (equivalent to 0.5 in fixed-point).
   *
   * Maximum calculation: (2^32 - 1) * (2^16 - 1) + 0x8000 fits in 64 bits.
   * This ensures no overflow even at highest frequencies and duty cycles.
   */
  uint64_t tmp = ((uint64_t)period * duty + 0x8000u);
  tmp >>= 16;

  /* Clamp to valid range */
  if (tmp >= period)
    {
      return period ? period - 1 : 0;
    }

  return (uint32_t)tmp;
}

/* Compute GTIOR value for standard PWM output (high at start, low at compare).
 * 0%/100% duty is handled separately via GTUDDTYC, not by disabling output here.
 * Output enable bits (OAE/OBE) remain set regardless of duty so POEG can track
 * the output state per RZ/V2H GPT hardware manual. */
static uint32_t gpt_compose_gtior(uint32_t duty_a_counts,
                                  uint32_t duty_b_counts,
                                  uint32_t period_counts)
{
  uint32_t gtior = 0;

  UNUSED(duty_a_counts);  /* duty 0%/100% handled by GTUDDTYC, not GTIOR */

  if (period_counts == 0)
    {
      return 0;
    }

  /* GTIOCA: initial high, compare-match low (saw-wave PWM normal polarity).
   * OAE always set — 0%/100% forced via GTUDDTYC.OADTY instead of disabling. */
  gtior |= GPT_GTIOR_GTIOA_HIGH_CMP_LOW | GPT_GTIOR_OAE;

#ifdef CONFIG_PWM_MULTICHAN
  /* GTIOCB: same configuration when B channel is used. */
  UNUSED(duty_b_counts);
  gtior |= GPT_GTIOR_GTIOB_HIGH_CMP_LOW | GPT_GTIOR_OBE;
#else
  UNUSED(duty_b_counts);
#endif

  return gtior;
}

/* Compute GTUDDTYC value to enforce 0%/100% duty or return to compare mode.
 * OADTY/OBDTY fields per RZ/V2H GPT hardware manual:
 *   0 = normal compare-match (register value), 2 = force 0%, 3 = force 100%. */
static uint32_t gpt_compute_gtuddtyc(uint32_t duty_a_counts,
                                     uint32_t duty_b_counts,
                                     uint32_t period_counts)
{
  uint32_t gtuddtyc;
  uint32_t oadty;

  /* Base value: count up direction. UDF=0 (software not required). */
  gtuddtyc = GPT_GTUDDTYC_UD;

  /* OADTY: forced duty for GTIOCA */
  if (period_counts == 0 || duty_a_counts == 0)
    {
      /* 0% duty: force pin low.
       * GTIOR_GTIOA_HIGH_CMP_LOW means pin starts high, so 0 counts → force low. */
      oadty = GPT_UDDTYC_DTY_0_PERCENT;
    }
  else if (duty_a_counts >= period_counts)
    {
      /* 100% duty: force pin high. */
      oadty = GPT_UDDTYC_DTY_100_PERCENT;
    }
  else
    {
      /* Normal compare-match: use register value. */
      oadty = GPT_UDDTYC_DTY_REGISTER;
    }

  gtuddtyc |= (oadty << GPT_GTUDDTYC_OADTY_SHIFT) & GPT_GTUDDTYC_OADTY_MASK;

#ifdef CONFIG_PWM_MULTICHAN
  /* OBDTY: forced duty for GTIOCB */
  uint32_t obdty;

  if (period_counts == 0 || duty_b_counts == 0)
    {
      obdty = GPT_UDDTYC_DTY_0_PERCENT;
    }
  else if (duty_b_counts >= period_counts)
    {
      obdty = GPT_UDDTYC_DTY_100_PERCENT;
    }
  else
    {
      obdty = GPT_UDDTYC_DTY_REGISTER;
    }

  gtuddtyc |= (obdty << GPT_GTUDDTYC_OBDTY_SHIFT) & GPT_GTUDDTYC_OBDTY_MASK;
#else
  UNUSED(duty_b_counts);
  /* Single-channel mode: OBDTY = 0% (B output unused). */
  gtuddtyc |= (GPT_UDDTYC_DTY_0_PERCENT << GPT_GTUDDTYC_OBDTY_SHIFT) &
              GPT_GTUDDTYC_OBDTY_MASK;
#endif

  return gtuddtyc;
}

#ifdef CONFIG_PWM_PULSECOUNT
static int rzv_gpt_attach_irq(FAR struct rzv_gpt_lowerhalf_s *priv)
{
  if (g_rzv_gpt_overflow_event[priv->channel] == 0)
    {
      return -ENOTSUP;
    }

  if (priv->irq >= 0)
    {
      return OK;
    }

  int irq = rzv_icu_attach(g_rzv_gpt_overflow_event[priv->channel],
                            rzv_gpt_irq, priv, false);
  if (irq < 0)
    {
      return irq;
    }

  priv->irq = irq;
  return OK;
}
#endif

/****************************************************************************
 * PWM Lower-Half Methods
 ****************************************************************************/

static int rzv_gpt_setup(FAR struct pwm_lowerhalf_s *dev)
{
  FAR struct rzv_gpt_lowerhalf_s *priv =
    (FAR struct rzv_gpt_lowerhalf_s *)dev;
  int ret;

  if (priv->initialized)
    {
      return OK;
    }

  ret = rzv_gpt_module_start(priv->channel);
  if (ret < 0)
    {
      return ret;
    }

  /* Use dedicated GPT clock accessor — P0CLK on R9A09G057H (100 MHz default).
   * Separating from generic pclk allows future update if GPTCK differs. */
  priv->pclk = rzv_get_gpt_clock_hz();

  irqstate_t flags = enter_critical_section();
  gpt_unlock(priv);
  /* Use hw_ch (unit-local channel 0-7) for GTSTR/GTSTP/GTCLR channel mask.
   * channel_mask = 1U << (channel % 8) for unit1. */
  gpt_putreg(priv, RZV_GPT_GTSTP_OFFSET, RZV_GPT_UNIT_BIT(priv->hw_ch));
  gpt_putreg(priv, RZV_GPT_GTCLR_OFFSET, RZV_GPT_UNIT_BIT(priv->hw_ch));
  gpt_putreg(priv, RZV_GPT_GTST_OFFSET, 0);
  gpt_putreg(priv, RZV_GPT_GTINTAD_OFFSET, 0);
  gpt_putreg(priv, RZV_GPT_GTITC_OFFSET, 0);
  gpt_putreg(priv, RZV_GPT_GTCR_OFFSET, 0);
  gpt_lock(priv);
  leave_critical_section(flags);

#ifdef CONFIG_PWM_PULSECOUNT
  priv->irq = -1;
  priv->oneshot = false;
  priv->handle = NULL;
  priv->remaining = 0;
#endif

  priv->initialized = true;
  return OK;
}

static int rzv_gpt_shutdown(FAR struct pwm_lowerhalf_s *dev)
{
  FAR struct rzv_gpt_lowerhalf_s *priv =
    (FAR struct rzv_gpt_lowerhalf_s *)dev;

  if (!priv->initialized)
    {
      return OK;
    }

  rzv_gpt_stop(dev);

#ifdef CONFIG_PWM_PULSECOUNT
  if (priv->irq >= 0)
    {
      rzv_icu_detach(priv->irq);
      priv->irq = -1;
    }
#endif

  (void)rzv_gpt_module_stop(priv->channel);
  priv->initialized = false;
  return OK;
}

#ifdef CONFIG_PWM_PULSECOUNT
static int rzv_gpt_start(FAR struct pwm_lowerhalf_s *dev,
                         FAR const struct pwm_info_s *info,
                         FAR void *handle)
#else
static int rzv_gpt_start(FAR struct pwm_lowerhalf_s *dev,
                         FAR const struct pwm_info_s *info)
#endif
{
  FAR struct rzv_gpt_lowerhalf_s *priv =
    (FAR struct rzv_gpt_lowerhalf_s *)dev;
  uint32_t period;
  uint32_t tpcs;
  uint32_t duty_a_counts = 0;
  uint32_t duty_b_counts = 0;
  int ret;

  if (!priv->initialized)
    {
      ret = rzv_gpt_setup(dev);
      if (ret < 0)
        {
          return ret;
        }
    }

  ret = gpt_compute_period(priv, info->frequency, &period, &tpcs);
  if (ret < 0)
    {
      return ret;
    }

#ifdef CONFIG_PWM_MULTICHAN
  for (int i = 0; i < CONFIG_PWM_NCHANNELS; i++)
    {
      if (info->channels[i].channel == 0)
        {
          duty_a_counts = gpt_duty_to_counts(period, info->channels[i].duty);
        }
      else if (info->channels[i].channel == 1)
        {
          duty_b_counts = gpt_duty_to_counts(period, info->channels[i].duty);
        }
    }
#else
  duty_a_counts = gpt_duty_to_counts(period, info->duty);
#endif

#ifdef CONFIG_PWM_PULSECOUNT
#  ifndef CONFIG_PWM_MULTICHAN
  uint32_t pulsecount = info->count;
#  else
  uint32_t pulsecount = 0;
#  endif
#endif

  irqstate_t flags = enter_critical_section();
  gpt_unlock(priv);

  /* Stop and clear counter before reconfiguration. Use hw_ch (unit-local bit)
   * for GTSTR/GTSTP/GTCLR: 1U << (channel % 8). */
  gpt_putreg(priv, RZV_GPT_GTSTP_OFFSET, RZV_GPT_UNIT_BIT(priv->hw_ch));
  gpt_putreg(priv, RZV_GPT_GTCLR_OFFSET, RZV_GPT_UNIT_BIT(priv->hw_ch));

  /* Set mode: saw-wave up-count, prescaler. */
  gpt_putreg(priv, RZV_GPT_GTCR_OFFSET,
             GPT_GTCR_MD_SAW |
             ((uint32_t)tpcs << GPT_GTCR_TPCS_SHIFT));

  /* Set period register directly (used immediately since counter is stopped). */
  gpt_putreg(priv, RZV_GPT_GTPR_OFFSET, period - 1u);

  /* Compare = high-time - 1: with GTBER buffered saw-wave output the GTIOC pin
   * transitions one cycle after compare match, so the register holds
   * (duty_counts - 1) to realise duty_counts of high-time (matches FSP
   * gpt_calculate_duty_cycle). 0%/100% are forced via GTUDDTYC, so 0 never
   * reaches compare mode; guard the subtraction anyway. */
  uint32_t ccr_a = (duty_a_counts > 0u) ? duty_a_counts - 1u : 0u;
#ifdef CONFIG_PWM_MULTICHAN
  uint32_t ccr_b = (duty_b_counts > 0u) ? duty_b_counts - 1u : 0u;
#endif

  /* Set compare registers for duty cycle (active registers for initial values). */
  gpt_putreg(priv, RZV_GPT_GTCCRA_OFFSET, ccr_a);
#ifdef CONFIG_PWM_MULTICHAN
  gpt_putreg(priv, RZV_GPT_GTCCRB_OFFSET, ccr_b);
#endif

  /* Set up GTBER double-buffering for glitch-free live duty updates.
   * GTBER = 0x550000: CCRA_BITS[17:16]=01, CCRB_BITS[19:18]=01, PR_BITS[21:20]=01
   * with force-transfer mode.  New values written to GTCCRC/GTCCRE/GTPBR
   * are latched into GTCCRA/GTCCRB/GTPR at next overflow — no mid-cycle glitch.
   * GPT_PRV_GTBER_BUFFER_ENABLE_FORCE_TRANSFER = 0x550000U per RZ/V2H UM. */
  gpt_putreg(priv, RZV_GPT_GTPBR_OFFSET, period - 1u);
  gpt_putreg(priv, RZV_GPT_GTCCRC_OFFSET, ccr_a);
#ifdef CONFIG_PWM_MULTICHAN
  gpt_putreg(priv, RZV_GPT_GTCCRE_OFFSET, ccr_b);
#else
  gpt_putreg(priv, RZV_GPT_GTCCRE_OFFSET, ccr_a);
#endif
  gpt_putreg(priv, RZV_GPT_GTBER_OFFSET, GPT_GTBER_FORCE_TRANSFER);

  /* Configure IO control register: output mode and enable. */
  gpt_putreg(priv, RZV_GPT_GTIOR_OFFSET,
             gpt_compose_gtior(duty_a_counts, duty_b_counts, period));

  /* Set GTUDDTYC to handle 0%/100% duty via forced static levels.
   * Replaces old GTIOA_DISABLE hack which disabled the output buffer.
   * GPT_DUTY_CYCLE_MODE_0/100_PERCENT per RZ/V2H GPT hardware manual. */
  gpt_putreg(priv, RZV_GPT_GTUDDTYC_OFFSET,
             gpt_compute_gtuddtyc(duty_a_counts, duty_b_counts, period));

  gpt_putreg(priv, RZV_GPT_GTST_OFFSET, 0);

#ifdef CONFIG_PWM_PULSECOUNT
  if (handle != NULL && pulsecount > 0)
    {
      ret = rzv_gpt_attach_irq(priv);
      if (ret < 0)
        {
          gpt_lock(priv);
          leave_critical_section(flags);
          return ret;
        }

      priv->handle = handle;
      priv->remaining = pulsecount;
      priv->oneshot = true;
      gpt_putreg(priv, RZV_GPT_GTINTAD_OFFSET, GPT_GTINTAD_ENABLE_OVF);
      up_enable_irq(priv->irq);
    }
  else
    {
      priv->handle = NULL;
      priv->remaining = 0;
      priv->oneshot = false;
      gpt_putreg(priv, RZV_GPT_GTINTAD_OFFSET, 0);
    }
#else
  gpt_putreg(priv, RZV_GPT_GTINTAD_OFFSET, 0);
#endif

  gpt_lock(priv);
  gpt_putreg(priv, RZV_GPT_GTSTR_OFFSET, RZV_GPT_UNIT_BIT(priv->hw_ch));
  leave_critical_section(flags);

  priv->running = true;
  priv->period = period;
  priv->divsel = (uint8_t)tpcs;
  return OK;
}

static int rzv_gpt_stop(FAR struct pwm_lowerhalf_s *dev)
{
  FAR struct rzv_gpt_lowerhalf_s *priv =
    (FAR struct rzv_gpt_lowerhalf_s *)dev;

  irqstate_t flags = enter_critical_section();
  gpt_unlock(priv);
  gpt_putreg(priv, RZV_GPT_GTSTP_OFFSET, RZV_GPT_UNIT_BIT(priv->hw_ch));
  gpt_putreg(priv, RZV_GPT_GTINTAD_OFFSET, 0);
  gpt_lock(priv);

#ifdef CONFIG_PWM_PULSECOUNT
  if (priv->irq >= 0)
    {
      up_disable_irq(priv->irq);
    }
  priv->oneshot = false;
  priv->handle = NULL;
  priv->remaining = 0;
#endif

  priv->running = false;
  leave_critical_section(flags);
  return OK;
}

static int rzv_gpt_ioctl(FAR struct pwm_lowerhalf_s *dev,
                         int cmd, unsigned long arg)
{
  UNUSED(dev);
  UNUSED(cmd);
  UNUSED(arg);
  return -ENOTTY;
}

#ifdef CONFIG_PWM_PULSECOUNT
static int rzv_gpt_irq(int irq, FAR void *context, FAR void *arg)
{
  FAR struct rzv_gpt_lowerhalf_s *priv =
    (FAR struct rzv_gpt_lowerhalf_s *)arg;

  UNUSED(irq);
  gpt_putreg(priv, RZV_GPT_GTST_OFFSET, 0);

  if (!priv->oneshot)
    {
      return OK;
    }

  if (priv->remaining > 0 && --priv->remaining == 0)
    {
      irqstate_t flags = enter_critical_section();
      gpt_putreg(priv, RZV_GPT_GTSTP_OFFSET,
                 RZV_GPT_UNIT_BIT(priv->hw_ch));
      gpt_putreg(priv, RZV_GPT_GTINTAD_OFFSET, 0);
      priv->running = false;
      priv->oneshot = false;
      leave_critical_section(flags);

      if (priv->handle != NULL)
        {
          pwm_expired(priv->handle);
        }
    }

  return OK;
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

FAR struct pwm_lowerhalf_s *rzv_gpt_initialize(int channel)
{
  switch (channel)
    {
#ifdef CONFIG_RZV_GPT0
      case 0:
        return &g_rzv_gpt0.dev;
#endif
#ifdef CONFIG_RZV_GPT1
      case 1:
        return &g_rzv_gpt1.dev;
#endif
#ifdef CONFIG_RZV_GPT2
      case 2:
        return &g_rzv_gpt2.dev;
#endif
#ifdef CONFIG_RZV_GPT3
      case 3:
        return &g_rzv_gpt3.dev;
#endif
#ifdef CONFIG_RZV_GPT4
      case 4:
        return &g_rzv_gpt4.dev;
#endif
#ifdef CONFIG_RZV_GPT5
      case 5:
        return &g_rzv_gpt5.dev;
#endif
#ifdef CONFIG_RZV_GPT6
      case 6:
        return &g_rzv_gpt6.dev;
#endif
#ifdef CONFIG_RZV_GPT7
      case 7:
        return &g_rzv_gpt7.dev;
#endif
#ifdef CONFIG_RZV_GPT8
      case 8:
        return &g_rzv_gpt8.dev;
#endif
#ifdef CONFIG_RZV_GPT9
      case 9:
        return &g_rzv_gpt9.dev;
#endif
#ifdef CONFIG_RZV_GPT10
      case 10:
        return &g_rzv_gpt10.dev;
#endif
#ifdef CONFIG_RZV_GPT11
      case 11:
        return &g_rzv_gpt11.dev;
#endif
      default:
        return NULL;
    }
}

#endif /* CONFIG_RZV_PWM */

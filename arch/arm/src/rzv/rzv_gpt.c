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

#ifdef CONFIG_RZV_GPT_PWM

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
  uint32_t               clkid;
  uint32_t               pclk;
  uint32_t               period;
  uint8_t                channel;
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

static const uintptr_t g_rzv_gpt_base[RZV_GPT_MAX_CHANNELS] =
{
  RZV_GPT0_BASE,
  RZV_GPT1_BASE,
  RZV_GPT2_BASE,
  RZV_GPT3_BASE,
  RZV_GPT4_BASE,
  RZV_GPT5_BASE,
  RZV_GPT6_BASE,
  RZV_GPT7_BASE,
};

static const uint32_t g_rzv_gpt_clkid[RZV_GPT_MAX_CHANNELS] =
{
  RZV_CPG_CLK_GPT0,
  RZV_CPG_CLK_GPT1,
  RZV_CPG_CLK_GPT2,
  RZV_CPG_CLK_GPT3,
  RZV_CPG_CLK_GPT4,
  RZV_CPG_CLK_GPT5,
  RZV_CPG_CLK_GPT6,
  RZV_CPG_CLK_GPT7,
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
static const uint16_t g_rzv_gpt_overflow_event[RZV_GPT_MAX_CHANNELS] =
{
  RZV_ELC_GPT_U0_GPT_ELCOVF_0,
  RZV_ELC_GPT_U0_GPT_ELCOVF_1,
  RZV_ELC_GPT_U0_GPT_ELCOVF_2,
  RZV_ELC_GPT_U0_GPT_ELCOVF_3,
  RZV_ELC_GPT_U0_GPT_ELCOVF_4,
  RZV_ELC_GPT_U0_GPT_ELCOVF_5,
  RZV_ELC_GPT_U0_GPT_ELCOVF_6,
  RZV_ELC_GPT_U0_GPT_ELCOVF_7,
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

#define RZV_GPT_LOWER_INIT(ch)                                 \
  {                                                             \
    .dev       = { .ops = &g_rzv_gpt_ops },                     \
    .base      = g_rzv_gpt_base[ch],                            \
    .clkid     = g_rzv_gpt_clkid[ch],                           \
    .channel   = (ch),                                          \
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
  uint64_t tmp = ((uint64_t)period * duty + 0x8000u);
  tmp >>= 16;
  if (tmp >= period)
    {
      return period ? period - 1 : 0;
    }

  return (uint32_t)tmp;
}

static uint32_t gpt_compose_gtior(uint32_t duty_a_counts,
                                  uint32_t duty_b_counts,
                                  uint32_t period_counts)
{
  uint32_t gtior = 0;

  if (period_counts == 0)
    {
      return 0;
    }

  gtior |= GPT_GTIOR_GTIOA_HIGH_CMP_LOW | GPT_GTIOR_OAE;

  if (duty_a_counts == 0)
    {
      gtior &= ~GPT_GTIOR_OAE;
      gtior |= GPT_GTIOR_GTIOA_DISABLE;
    }

#ifdef CONFIG_PWM_MULTICHAN
  if (duty_b_counts > 0)
    {
      gtior |= GPT_GTIOR_GTIOB_HIGH_CMP_LOW | GPT_GTIOR_OBE;
    }
  else
    {
      gtior |= GPT_GTIOR_GTIOB_DISABLE;
    }
#else
  UNUSED(duty_b_counts);
#endif

  return gtior;
}

#ifdef CONFIG_PWM_PULSECOUNT
static int rzv_gpt_attach_irq(FAR struct rzv_gpt_lowerhalf_s *priv)
{
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

  ret = rzv_clock_enable(priv->clkid);
  if (ret < 0)
    {
      return ret;
    }

  ret = rzv_module_reset(priv->clkid);
  if (ret < 0)
    {
      return ret;
    }

  priv->pclk = rzv_get_pclk_frequency();

  irqstate_t flags = enter_critical_section();
  gpt_unlock(priv);
  gpt_putreg(priv, RZV_GPT_GTSTP_OFFSET, RZV_GPT_CHANNEL_MASK(priv->channel));
  gpt_putreg(priv, RZV_GPT_GTCLR_OFFSET, RZV_GPT_CHANNEL_MASK(priv->channel));
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

  rzv_clock_disable(priv->clkid);
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
  gpt_putreg(priv, RZV_GPT_GTSTP_OFFSET, RZV_GPT_CHANNEL_MASK(priv->channel));
  gpt_putreg(priv, RZV_GPT_GTCLR_OFFSET, RZV_GPT_CHANNEL_MASK(priv->channel));
  gpt_putreg(priv, RZV_GPT_GTCR_OFFSET,
             GPT_GTCR_MD_SAW |
             ((uint32_t)tpcs << GPT_GTCR_TPCS_SHIFT));
  gpt_putreg(priv, RZV_GPT_GTPR_OFFSET, period - 1u);
  gpt_putreg(priv, RZV_GPT_GTCCRA_OFFSET, duty_a_counts);
#ifdef CONFIG_PWM_MULTICHAN
  gpt_putreg(priv, RZV_GPT_GTCCRB_OFFSET, duty_b_counts);
#endif
  gpt_putreg(priv, RZV_GPT_GTIOR_OFFSET,
             gpt_compose_gtior(duty_a_counts, duty_b_counts, period));
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
  gpt_putreg(priv, RZV_GPT_GTSTR_OFFSET, RZV_GPT_CHANNEL_MASK(priv->channel));
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
  gpt_putreg(priv, RZV_GPT_GTSTP_OFFSET, RZV_GPT_CHANNEL_MASK(priv->channel));
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
                 RZV_GPT_CHANNEL_MASK(priv->channel));
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
      default:
        return NULL;
    }
}

#endif /* CONFIG_RZV_GPT_PWM */

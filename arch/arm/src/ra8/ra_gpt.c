/****************************************************************************
 * arch/arm/src/ra8/ra_gpt.c
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
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>
#include <inttypes.h>
#include <string.h>

#include <nuttx/arch.h>
#include <nuttx/timers/pwm.h>
#include <nuttx/timers/timer.h>
#include <nuttx/clock.h>
#include <nuttx/timers/arch_timer.h>
#include <nuttx/irq.h>
#include <arch/board/board.h>

#include "chip.h"
#include "hardware/ra_memorymap.h"
#include "arm_internal.h"
#include "nvic.h"
#if defined(CONFIG_RA8E1_GROUP)
#include "hardware/ra8e1/ra_gpt32.h"
#include "hardware/ra8e1/ra_gpt16.h"
#elif defined(CONFIG_RA8P1_GROUP)
#include "hardware/ra8p1/ra_gpt32.h"
#endif
#include "ra_gpt.h"
#include "ra_mstp.h"
#include "ra_clock.h"
#include "ra_icu.h"
#include "ra_elc.h"
#ifdef CONFIG_RA_DMAC
#include "ra_dmac.h"
#endif
#include <syslog.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Buffer enable mask for PWM mode */
#define GPT_GTBER_PWM_ENABLE            (GPT_GTBER_CCRA | GPT_GTBER_CCRB | GPT_GTBER_PR)

/* Software source select enable bit (bit 31) for GTSSR/GTPSR/GTCSR registers.
 * When set, enables software control via GTSTR/GTSTP/GTCLR registers.
 * Without this, external trigger sources may interfere with timer operation.
 * Uses 0x80000000 to enable software source.
 */
#define GPT_SOURCE_SW_SELECT            (1ul << 31)

/* GTINTAD overflow/underflow interrupt enable.
 * For saw-wave up-counting mode, use overflow interrupt (TCFPO).
 * The GRP (group) field selects which interrupt group triggers on overflow.
 * Setting GRP[1:0] = 0 and enabling via ICU allows overflow interrupt.
 * Note: The actual interrupt source is routed via ELC event, but GTINTAD
 * must have the appropriate enable bits set for the GPT to assert the
 * interrupt request signal.
 */
#define GPT_GTINTAD_GRP_SHIFT           (24)      /* Interrupt output group select shift */
#define GPT_GTINTAD_GRP_MASK            (0x3 << GPT_GTINTAD_GRP_SHIFT)
#define GPT_GTINTAD_GRP_A               (0 << GPT_GTINTAD_GRP_SHIFT)  /* Group A interrupt output */
#define GPT_GTINTAD_GRPABH_OVF_UDF      (1 << 28) /* Output overflow/underflow on Group A/B high */

/* Prescaler values */
#define GPT_PRESCALER_1                 1
#define GPT_PRESCALER_4                 4
#define GPT_PRESCALER_16                16
#define GPT_PRESCALER_64                64
#define GPT_PRESCALER_256               256
#define GPT_PRESCALER_1024              1024

#ifdef CONFIG_RA_GPT
/****************************************************************************
 * Private Types
 ****************************************************************************/

/* GPT channel configuration structure */
struct ra_gpt_channel_config_s
{
  uint32_t base;                   /* GPT peripheral base address */
  ra_mstp_module_t mstp;           /* Module stop control bit */
  uint32_t pclkd_freq;             /* PCLKD frequency */
  uint32_t max_period;             /* Maximum period in timer counts, 16-bit timer: 65535 and 32-bit timer: 4294967295 */
  uint32_t channel;                /* GPT channel (0-13) */
  uint32_t elc;                    /* ELC event for timer mode interrupt.
                                    * For timer/PWM mode: use COUNTER_OVERFLOW event.
                                    * For input capture mode: use CAPTURE_COMPARE_A event.
                                    * This field is used by gpt_timer_setcallback() to route
                                    * overflow interrupts through ICU. */
};

/* GPT device state structure */
struct ra_gpt_s
{
  const struct pwm_ops_s *ops;     /* PWM operations */
#ifdef CONFIG_TIMER
  const struct timer_ops_s *timer_ops; /* Timer operations */
#endif
  const struct ra_gpt_channel_config_s *config; /* GPT configuration */
  uint32_t frequency;             /* Current frequency */
  uint32_t period;                /* Period in timer counts */
  uint32_t prescaler;             /* Current prescaler setting */
  /* Current Duty cycle values stored as timer ticks for compare A/B.
   * These reflect the last started configuration and are used to answer
   * PWMIOC_GETCHARACTERISTICS and for logging. duty_b is only present
   * when multi-channel support is enabled.
   */
  uint32_t duty_a;                /* Current Duty cycle for channel A in timer counts */
#ifdef CONFIG_PWM_MULTICHAN
  uint32_t duty_b;                /* Current Duty cycle for channel B in timer counts */
#endif
  int       irq;                  /* Timer interrupt slot IRQ number assigned in the runtime */
  uint8_t mode;                   /* GPT mode (PWM/Timer) */
  bool started;                   /* True: Started */
  bool pwm_mode;                  /* True: PWM mode, False: Timer mode */
  void (*callback)(void *arg);    /* Timer callback function */
  void *arg;                      /* Timer callback argument */
#ifdef CONFIG_PWM_MULTICHAN
  uint8_t  nchannels;             /* Number of channels */
#endif
#ifdef CONFIG_RA_DMAC
  ra_dmac_handle_t dma_handle;    /* DMA handle */
  int dma_channel;                /* Assigned DMA channel (-1 = dynamic) */
#endif
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Register access helpers */
static inline uint32_t gpt_getreg(struct ra_gpt_s *priv, int offset);
static inline void gpt_putreg(struct ra_gpt_s *priv, int offset, uint32_t value);

/* Low-level GPT operations */
static int gpt_configure(struct ra_gpt_s *priv);
static uint32_t gpt_calculate_prescaler(uint32_t frequency, uint32_t pclkd);
static void gpt_dumpregs(struct ra_gpt_s *priv, const char *msg);
#ifdef CONFIG_DEBUG_PWM_INFO
static void gpt_log_channel(uint8_t ch,
                            uint32_t freq_hz,
                            uint32_t prescaler,
                            uint32_t pclkd,
                            uint32_t reload_ticks,
                            uint32_t duty_ticks);
#endif

#ifdef CONFIG_TIMER
/* Interrupt handler (used for timer mode) */
static int gpt_interrupt(int irq, void *context, void *arg);
#endif

/* PWM driver methods */
static int gpt_setup(struct pwm_lowerhalf_s *dev);
static int gpt_shutdown(struct pwm_lowerhalf_s *dev);
static int gpt_start(struct pwm_lowerhalf_s *dev, const struct pwm_info_s *info);
static int gpt_stop(struct pwm_lowerhalf_s *dev);
static int gpt_ioctl(struct pwm_lowerhalf_s *dev, int cmd, unsigned long arg);

#ifdef CONFIG_TIMER
/* Timer driver methods */
static int gpt_timer_start(struct timer_lowerhalf_s *lower);
static int gpt_timer_stop(struct timer_lowerhalf_s *lower);
static int gpt_timer_getstatus(struct timer_lowerhalf_s *lower,
                               struct timer_status_s *status);
static int gpt_timer_settimeout(struct timer_lowerhalf_s *lower,
                                uint32_t timeout);
static void gpt_timer_setcallback(struct timer_lowerhalf_s *lower,
                                  tccb_t callback, void *arg);
static int gpt_timer_maxtimeout(struct timer_lowerhalf_s *lower,
                                uint32_t *maxtimeout);
#endif /* CONFIG_TIMER */

/* Dead-time control */
static int gpt_set_deadtime(struct ra_gpt_s *priv, uint32_t deadtime_up,
                            uint32_t deadtime_dn, bool enable);

/* External trigger control */
static int gpt_set_trigger(struct ra_gpt_s *priv,
                           const struct ra_gpt_trigger_s *config);

/* Input capture mode */
static int gpt_set_capture(struct ra_gpt_s *priv,
                           const struct ra_gpt_capture_s *config);
static int gpt_get_capture(struct ra_gpt_s *priv,
                           struct ra_gpt_captured_s *result);

#ifdef CONFIG_RA_DMAC
/* DMA support */
static void gpt_get_dma_channel(struct ra_gpt_s *priv, int *channel);
static int gpt_set_dma(struct ra_gpt_s *priv,
                       const struct ra_gpt_dma_s *config);
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* This is the list of lower half PWM driver methods used by the upper half
 * driver
 */
static const struct pwm_ops_s g_gpt_ops =
{
  .setup      = gpt_setup,
  .shutdown   = gpt_shutdown,
  .start      = gpt_start,
  .stop       = gpt_stop,
  .ioctl      = gpt_ioctl,
};

#ifdef CONFIG_TIMER
/* This is the list of lower half timer driver methods used by the upper half
 * driver
 */
static const struct timer_ops_s g_gpt_timer_ops =
{
  .start       = gpt_timer_start,
  .stop        = gpt_timer_stop,
  .getstatus   = gpt_timer_getstatus,
  .settimeout  = gpt_timer_settimeout,
  .setcallback = gpt_timer_setcallback,
  .maxtimeout  = gpt_timer_maxtimeout,
};
#endif /* CONFIG_TIMER */

/* GPT device configurations */
static const struct ra_gpt_channel_config_s g_gpt_configs[] =
{
/* GPT channel configurations.
 * For timer/PWM mode, use COUNTER_OVERFLOW events for periodic interrupt.
 * For input capture, the PX4 io_timer_impl.c uses CAPTURE_COMPARE_A directly.
 */
#ifdef CONFIG_RA_GPT0
  {
    .base       = R_GPT32_CH_BASE(0),
    .mstp       = RA_MSTP_GPT0,
    .pclkd_freq = RA_PCLKD_FREQUENCY,
    .max_period = UINT32_MAX, /* 32-bit timer */
    .channel    = 0,
    .elc        = RA_ELC_GPT0_COUNTER_OVERFLOW,  /* GPT0 overflow for timer mode */
  },
#endif
#ifdef CONFIG_RA_GPT1
  {
    .base       = R_GPT32_CH_BASE(1),
    .mstp       = RA_MSTP_GPT1,
    .pclkd_freq = RA_PCLKD_FREQUENCY,
    .max_period = UINT32_MAX, /* 32-bit timer */
    .channel    = 1,
    .elc        = RA_ELC_GPT1_COUNTER_OVERFLOW,  /* GPT1 overflow for timer mode */
  },
#endif
#ifdef CONFIG_RA_GPT2
  {
    .base       = R_GPT32_CH_BASE(2),
    .mstp       = RA_MSTP_GPT2,
    .pclkd_freq = RA_PCLKD_FREQUENCY,
    .max_period = UINT32_MAX, /* 32-bit timer */
    .channel    = 2,
    .elc        = RA_ELC_GPT2_COUNTER_OVERFLOW,  /* GPT2 overflow for timer mode */
  },
#endif
#ifdef CONFIG_RA_GPT3
  {
    .base       = R_GPT32_CH_BASE(3),
    .mstp       = RA_MSTP_GPT3,
    .pclkd_freq = RA_PCLKD_FREQUENCY,
    .max_period = UINT32_MAX, /* 32-bit timer */
    .channel    = 3,
    .elc        = RA_ELC_GPT3_COUNTER_OVERFLOW,  /* GPT3 overflow for timer mode */
  },
#endif
#ifdef CONFIG_RA_GPT4
  {
    .base       = R_GPT32_CH_BASE(4),
    .mstp       = RA_MSTP_GPT4,
    .pclkd_freq = RA_PCLKD_FREQUENCY,
    .max_period = UINT32_MAX, /* 32-bit timer */
    .channel    = 4,
    .elc        = RA_ELC_GPT4_COUNTER_OVERFLOW,  /* GPT4 overflow for timer mode */
  },
#endif
#ifdef CONFIG_RA_GPT5
  {
    .base       = R_GPT32_CH_BASE(5),
    .mstp       = RA_MSTP_GPT5,
    .pclkd_freq = RA_PCLKD_FREQUENCY,
    .max_period = UINT32_MAX, /* 32-bit timer */
    .channel    = 5,
    .elc        = RA_ELC_GPT5_COUNTER_OVERFLOW,  /* GPT5 overflow for timer mode */
  },
#endif
#ifdef CONFIG_RA_GPT6
  {
    .base       = R_GPT32_CH_BASE(6),
    .mstp       = RA_MSTP_GPT6,
    .pclkd_freq = RA_PCLKD_FREQUENCY,
    .max_period = UINT32_MAX, /* 32-bit timer */
    .channel    = 6,
    .elc        = RA_ELC_GPT6_COUNTER_OVERFLOW,  /* GPT6 overflow for timer mode */
  },
#endif
#ifdef CONFIG_RA_GPT7
  {
    .base       = R_GPT32_CH_BASE(7),
    .mstp       = RA_MSTP_GPT7,
    .pclkd_freq = RA_PCLKD_FREQUENCY,
    .max_period = UINT32_MAX, /* 32-bit timer */
    .channel    = 7,
    .elc        = RA_ELC_GPT7_COUNTER_OVERFLOW,  /* GPT7 overflow for timer mode */
  },
#endif
#ifdef CONFIG_RA_GPT8
  {
    .base       = R_GPT32_CH_BASE(8),
    .mstp       = RA_MSTP_GPT8,
    .pclkd_freq = RA_PCLKD_FREQUENCY,
    .max_period = UINT32_MAX, /* 32-bit timer */
    .channel    = 8,
    .elc        = RA_ELC_GPT8_COUNTER_OVERFLOW,  /* GPT8 overflow for timer mode */
  },
#endif
#ifdef CONFIG_RA_GPT9
  {
    .base       = R_GPT32_CH_BASE(9),
    .mstp       = RA_MSTP_GPT9,
    .pclkd_freq = RA_PCLKD_FREQUENCY,
    .max_period = UINT32_MAX, /* 32-bit timer */
    .channel    = 9,
    .elc        = RA_ELC_GPT9_COUNTER_OVERFLOW,  /* GPT9 overflow for timer mode */
  },
#endif
#ifdef CONFIG_RA_GPT10
  {
    .base       = R_GPT32_CH_BASE(10),
    .mstp       = RA_MSTP_GPT10,
    .pclkd_freq = RA_PCLKD_FREQUENCY,
    .max_period = UINT32_MAX, /* 32-bit timer */
    .channel    = 10,
    .elc        = RA_ELC_GPT10_COUNTER_OVERFLOW,  /* GPT10 overflow for timer mode */
  },
#endif
#ifdef CONFIG_RA_GPT11
  {
    .base       = R_GPT32_CH_BASE(11),
    .mstp       = RA_MSTP_GPT11,
    .pclkd_freq = RA_PCLKD_FREQUENCY,
    .max_period = UINT32_MAX, /* 32-bit timer */
    .channel    = 11,
    .elc        = RA_ELC_GPT11_COUNTER_OVERFLOW,  /* GPT11 overflow for timer mode */
  },
#endif
#ifdef CONFIG_RA_GPT12
  {
    .base       = R_GPT32_CH_BASE(12),
    .mstp       = RA_MSTP_GPT12,
    .pclkd_freq = RA_PCLKD_FREQUENCY,
    .max_period = UINT32_MAX, /* 32-bit timer */
    .channel    = 12,
    .elc        = RA_ELC_GPT12_COUNTER_OVERFLOW,  /* GPT12 overflow for timer mode */
  },
#endif
#ifdef CONFIG_RA_GPT13
  {
    .base       = R_GPT32_CH_BASE(13),
    .mstp       = RA_MSTP_GPT13,
    .pclkd_freq = RA_PCLKD_FREQUENCY,
    .max_period = UINT32_MAX, /* 32-bit timer */
    .channel    = 13,
    .elc        = RA_ELC_GPT13_COUNTER_OVERFLOW,  /* GPT13 overflow for timer mode */
  },
#endif
};

#define NGPT_CONFIGS (sizeof(g_gpt_configs) / sizeof(struct ra_gpt_channel_config_s))

/* GPT device instances */
static struct ra_gpt_s g_gpt_devs[NGPT_CONFIGS];

#define NGPT_DEVS (sizeof(g_gpt_devs) / sizeof(struct ra_gpt_s))

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: gpt_getreg
 *
 * Description:
 *   Read the value of a GPT timer register.
 *
 * Input Parameters:
 *   priv   - A reference to the GPT structure
 *   offset - The offset to the register to read
 *
 * Returned Value:
 *   The value of the register
 *
 ****************************************************************************/

static inline uint32_t gpt_getreg(struct ra_gpt_s *priv, int offset)
{
  return getreg32(priv->config->base + offset);
}

/****************************************************************************
 * Name: gpt_putreg
 *
 * Description:
 *   Write a value to a GPT timer register.
 *
 * Input Parameters:
 *   priv   - A reference to the GPT structure
 *   offset - The offset to the register to write to
 *   value  - The value to write to the register
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

static inline void gpt_putreg(struct ra_gpt_s *priv, int offset,
                              uint32_t value)
{
  putreg32(value, priv->config->base + offset);
}

/****************************************************************************
 * Name: gpt_dumpregs
 *
 * Description:
 *   Dump all timer registers.
 *
 * Input Parameters:
 *   priv - A reference to the GPT structure
 *   msg  - Message to print before the register dump
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

static void gpt_dumpregs(struct ra_gpt_s *priv, const char *msg)
{
#ifdef CONFIG_DEBUG_PWM_INFO
  pwminfo("%s:\n", msg);
  pwminfo("  GTCR:    %08x  GTPR:    %08x  GTCNT:   %08x\n",
          gpt_getreg(priv, R_GPT32_GTCR_OFFSET),
          gpt_getreg(priv, R_GPT32_GTPR_OFFSET),
          gpt_getreg(priv, R_GPT32_GTCNT_OFFSET));
  pwminfo("  GTCCRA:  %08x  GTCCRB:  %08x  GTIOR:   %08x\n",
          gpt_getreg(priv, R_GPT32_GTCCRA_OFFSET),
          gpt_getreg(priv, R_GPT32_GTCCRB_OFFSET),
          gpt_getreg(priv, R_GPT32_GTIOR_OFFSET));
  pwminfo("  GTINTAD: %08x  GTST:    %08x\n",
          gpt_getreg(priv, R_GPT32_GTINTAD_OFFSET),
          gpt_getreg(priv, R_GPT32_GTST_OFFSET));
#endif
}

/*
 * Log helper that prints channel timing info to syslog and low-level debug.
 */
#ifdef CONFIG_DEBUG_PWM_INFO
static void gpt_log_channel(uint8_t ch,
                            uint32_t freq_hz,
                            uint32_t prescaler,
                            uint32_t pclkd,
                            uint32_t reload_ticks,
                            uint32_t duty_ticks)
{
  uint32_t period_us = 0;
  uint32_t duty_us = 0;
  uint32_t duty_pct = 0;
  uint64_t timer_tick_freq = 0;
  /* Full prescaler divider table - matches gpt_calculate_prescaler() */
  static const uint32_t prescaler_divs[] = {1, 2, 4, 8, 16, 32, 64, 256, 1024};

  /* Validate prescaler index and pclkd */
  if (prescaler < (sizeof(prescaler_divs) / sizeof(prescaler_divs[0])) && pclkd > 0)
    {
      timer_tick_freq = (uint64_t)pclkd / prescaler_divs[prescaler];
    }

  /* If the reload register contains the default/unprogrammed value
   * (UINT32_MAX for 32-bit, 0xFFFF for 16-bit) then this GPT has not been
   * programmed yet; avoid computing and printing misleading large us values.
   */
  if (reload_ticks == UINT32_MAX || reload_ticks == 0xFFFF)
    {
      syslog(LOG_INFO,
             "GPT ch%u: unprogrammed reload=0x%" PRIx32 "\n",
             (unsigned)ch, reload_ticks);
      pwminfo("GPT ch%u: unprogrammed\n", (unsigned)ch);
      return;
    }

  if (timer_tick_freq > 0 && reload_ticks > 0)
    {
      /* reload_ticks are timer ticks at prescaled timer clock. Convert to us
       * Use integer rounding: add half of divisor before divide.
       */
      period_us = (uint32_t)((((uint64_t)reload_ticks * 1000000ULL) + (timer_tick_freq >> 1)) / timer_tick_freq);
      duty_us   = (uint32_t)((((uint64_t)duty_ticks * 1000000ULL) + (timer_tick_freq >> 1)) / timer_tick_freq);

      /* Percent with rounding: (duty*100 + reload/2)/reload */
      duty_pct  = (uint32_t)((((uint64_t)duty_ticks * 100ULL) + (reload_ticks >> 1)) / reload_ticks);
    }

  syslog(LOG_INFO,
    "GPT ch%u: freq=%" PRIu32 "Hz presc=%" PRIu32 " reload=%" PRIu32 " ticks period~%" PRIu32 "us duty=%" PRIu32 " ticks ~%" PRIu32 "us (%" PRIu32 "%%)\n",
    (unsigned)ch, freq_hz, prescaler, reload_ticks, period_us, duty_ticks, duty_us, duty_pct);

  /* Use pwminfo for low-level PWM info logging (lldbg may be unavailable
   * in some build configs). */
  pwminfo("GPT ch%u: period~%" PRIu32 "us duty~%" PRIu32 "us (%" PRIu32 "%%)\n",
     (unsigned)ch, period_us, duty_us, duty_pct);
}
#else
#  define gpt_log_channel(ch,freq_hz,prescaler,pclkd,reload_ticks,duty_ticks)
#endif

/****************************************************************************
 * Name: gpt_calculate_prescaler
 *
 * Description:
 *   Calculate the appropriate prescaler for the given frequency.
 *
 * Input Parameters:
 *   frequency - The desired PWM frequency
 *   pclkd     - The PCLKD frequency
 *
 * Returned Value:
 *   The prescaler value (0-5) or -1 on error
 *
 ****************************************************************************/

static uint32_t gpt_calculate_prescaler(uint32_t frequency, uint32_t pclkd)
{
  /* Full prescaler divider table:
   * TPCS[3:0]  Divisor  Index
   * 0000 (0)   1        0
   * 0001 (1)   2        1
   * 0010 (2)   4        2
   * 0011 (3)   8        3
   * 0100 (4)   16       4
   * 0101 (5)   32       5
   * 0110 (6)   64       6
   * 0111 (7)   Reserved -
   * 1000 (8)   256      7
   * 1001 (9)   Reserved -
   * 1010 (10)  1024     8
   *
   * Note: Index 7 maps to TPCS=8 (256), Index 8 maps to TPCS=10 (1024).
   * A separate mapping table converts array index to TPCS register value.
   */
  static const uint32_t prescaler_divs[] = {1, 2, 4, 8, 16, 32, 64, 256, 1024};
  uint32_t i;
  uint32_t timer_freq;
  uint32_t period;

  for (i = 0; i < sizeof(prescaler_divs) / sizeof(prescaler_divs[0]); i++)
    {
      timer_freq = pclkd / prescaler_divs[i];

      /* Compute period rounded to nearest tick: period = round(timer_freq / frequency)
       * Use 64-bit math to avoid overflow.
       */
  period = (uint32_t)((((uint64_t)timer_freq) + ((uint64_t)frequency >> 1)) / (uint64_t)frequency);

      /* Check if period fits in 32-bit counter and is reasonable */
      if (period > 1 && period <= UINT32_MAX)
        {
          return i;
        }
    }

  return UINT32_MAX; /* Error */
}

/****************************************************************************
 * Name: gpt_configure
 *
 * Description:
 *   Configure the GPT timer for PWM operation.
 *
 * Input Parameters:
 *   priv - A reference to the GPT structure
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

static int gpt_configure(struct ra_gpt_s *priv)
{
  uint32_t regval;

  pwminfo("Configuring GPT%" PRIu32 "\n", priv->config->channel);

  /* Ensure the GPT module clock is enabled before accessing registers.
   * This is critical if gpt_configure() is called without going through
   * ra_gpt_initialize() (e.g., direct gpt_setup() call).
   */
  ra_mstp_start(priv->config->mstp);

  /* Perform the multi-register configuration atomically to avoid races */
  irqstate_t flags = enter_critical_section();

  /* Disable write protection */
  gpt_putreg(priv, R_GPT32_GTWP_OFFSET, GPT_GTWP_PRKEY);

  /* Stop the timer if it's running */
  regval = gpt_getreg(priv, R_GPT32_GTCR_OFFSET);
  regval &= ~GPT_GTCR_CST;
  gpt_putreg(priv, R_GPT32_GTCR_OFFSET, regval);

  /* Initialize source select registers for software control.
   * Set bit 31 (software source select enable) in GTSSR, GTPSR, GTCSR
   * to enable software start/stop/clear via GTSTR/GTSTP/GTCLR registers.
   * Without this, external trigger sources could interfere with timer operation.
   * Uses 0x80000000 to enable software source.
   */
  gpt_putreg(priv, R_GPT32_GTSSR_OFFSET, GPT_SOURCE_SW_SELECT);
  gpt_putreg(priv, R_GPT32_GTPSR_OFFSET, GPT_SOURCE_SW_SELECT);
  gpt_putreg(priv, R_GPT32_GTCSR_OFFSET, GPT_SOURCE_SW_SELECT);

  /* Configure timer for saw-wave PWM mode (up-counting) */
  regval = GPT_GTCR_MD_SAW_WAVE_UP | GPT_GTCR_TPCS_PCLKD_1;
  gpt_putreg(priv, R_GPT32_GTCR_OFFSET, regval);

  /* Configure I/O pins for PWM output:
   * - Saw-wave PWM mode: Initial low, high at compare match, low at period end
   * - Enable output on both GTIOCA and GTIOCB pins
   */
  regval = GPT_GTIOR_PWM_HIGH_AB;
  gpt_putreg(priv, R_GPT32_GTIOR_OFFSET, regval);

  /* Initialize counter and period */
  gpt_putreg(priv, R_GPT32_GTCNT_OFFSET, 0);
  gpt_putreg(priv, R_GPT32_GTPR_OFFSET, 0xffff);

  /* Initialize compare registers */
  gpt_putreg(priv, R_GPT32_GTCCRA_OFFSET, 0);
  gpt_putreg(priv, R_GPT32_GTCCRB_OFFSET, 0);

  /* Enable buffer operation for glitch-free duty cycle updates.
   * GTBER enables single buffer operation:
   * - CCRA: GTCCRA <-> GTCCRC (compare A buffer)
   * - CCRB: GTCCRB <-> GTCCRE (compare B buffer)
   * - PR:   GTPBR -> GTPR (period buffer)
   * Transfers occur at counter overflow/underflow for saw-wave mode.
   */
  gpt_putreg(priv, R_GPT32_GTBER_OFFSET, GPT_GTBER_PWM_ENABLE);

  /* Clear all interrupt flags */
  regval = gpt_getreg(priv, R_GPT32_GTST_OFFSET);
  gpt_putreg(priv, R_GPT32_GTST_OFFSET, regval);

  /* Re-enable write protection */
  gpt_putreg(priv, R_GPT32_GTWP_OFFSET,
             GPT_GTWP_PRKEY | GPT_GTWP_WP | GPT_GTWP_CMNWP);

  leave_critical_section(flags);

  gpt_dumpregs(priv, "After configuration");

  /* Mark as PWM mode */
  priv->pwm_mode = true;

  /* Log channel state */
  gpt_log_channel((uint8_t)priv->config->channel,
                  priv->frequency,
                  priv->prescaler,
                  priv->config->pclkd_freq,
                  gpt_getreg(priv, R_GPT32_GTPR_OFFSET),
                  gpt_getreg(priv, R_GPT32_GTCCRA_OFFSET));

  return 0;
}

/****************************************************************************
 * Name: gpt_setup
 *
 * Description:
 *   This method is called when the driver is opened.  The lower half driver
 *   should configure and initialize the device so that it is ready for use.
 *   It should not, however, output pulses until the start method is called.
 *
 * Input Parameters:
 *   dev - A reference to the lower half PWM driver state structure
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

static int gpt_setup(struct pwm_lowerhalf_s *dev)
{
  struct ra_gpt_s *priv = (struct ra_gpt_s *)dev;

  pwminfo("GPT%" PRIu32 " setup\n", priv->config->channel);

  return gpt_configure(priv);
}

/****************************************************************************
 * Name: gpt_shutdown
 *
 * Description:
 *   This method is called when the driver is closed.  The lower half driver
 *   stop pulsed output, free any resources, disable the timer hardware, and
 *   put the system into the lowest possible power usage state
 *
 * Input Parameters:
 *   dev - A reference to the lower half PWM driver state structure
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

static int gpt_shutdown(struct pwm_lowerhalf_s *dev)
{
  struct ra_gpt_s *priv = (struct ra_gpt_s *)dev;
  uint32_t regval;

  pwminfo("GPT%" PRIu32 " shutdown\n", priv->config->channel);

  /* Make shutdown sequence atomic */
  irqstate_t flags = enter_critical_section();

  /* Disable write protection */
  gpt_putreg(priv, R_GPT32_GTWP_OFFSET, GPT_GTWP_PRKEY);

  /* Stop the timer */
  regval = gpt_getreg(priv, R_GPT32_GTCR_OFFSET);
  regval &= ~GPT_GTCR_CST;
  gpt_putreg(priv, R_GPT32_GTCR_OFFSET, regval);

  /* Reset the timer to its default state */
  gpt_putreg(priv, R_GPT32_GTCNT_OFFSET, 0);
  gpt_putreg(priv, R_GPT32_GTCCRA_OFFSET, 0);
  gpt_putreg(priv, R_GPT32_GTCCRB_OFFSET, 0);
  gpt_putreg(priv, R_GPT32_GTIOR_OFFSET, 0);

  /* Re-enable write protection */
  gpt_putreg(priv, R_GPT32_GTWP_OFFSET,
             GPT_GTWP_PRKEY | GPT_GTWP_WP | GPT_GTWP_CMNWP);

  leave_critical_section(flags);

  /* Put the GPT back into module stop state to save power */
  ra_mstp_stop(priv->config->mstp);

  priv->started = false;
  return 0;
}

/****************************************************************************
 * Name: gpt_start
 *
 * Description:
 *   (Re-)initialize the timer resources and start the pulsed output
 *
 * Input Parameters:
 *   dev  - A reference to the lower half PWM driver state structure
 *   info - A reference to the characteristics of the pulsed output
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

static int gpt_start(struct pwm_lowerhalf_s *dev,
                     const struct pwm_info_s *info)
{
  struct ra_gpt_s *priv = (struct ra_gpt_s *)dev;
  uint32_t prescaler;
  uint32_t timer_freq;
  uint32_t period;
  uint32_t duty_a, duty_b;
  uint32_t regval;

#ifdef CONFIG_PWM_MULTICHAN
  pwminfo("GPT%d start: frequency=%" PRIu32 " (multichan)\n",
          priv->config->channel, info->frequency);
#else
  pwminfo("GPT%" PRIu32 " start: frequency=%" PRIu32 " duty=%08" PRIx32 "\n",
          priv->config->channel, info->frequency, (uint32_t)info->duty);
#endif

  DEBUGASSERT(info->frequency > 0);

  /* Calculate the prescaler and period */

  prescaler = gpt_calculate_prescaler(info->frequency, priv->config->pclkd_freq);
  if (prescaler == UINT32_MAX)
    {
      pwmerr("ERROR: Cannot achieve frequency %" PRIu32 "\n", info->frequency);
      return -ERANGE;
    }

  /* Compute timer tick frequency using prescaler divisor table and round
   * the period (timer ticks) to the nearest integer to avoid systematic
   * truncation biases.
   */
  {
    /* Full prescaler divider table - matches gpt_calculate_prescaler() */
    static const uint32_t prescaler_divs[] = {1, 2, 4, 8, 16, 32, 64, 256, 1024};

    if (prescaler >= (sizeof(prescaler_divs) / sizeof(prescaler_divs[0])))
      {
        pwmerr("ERROR: invalid prescaler index %" PRIu32 "\n", prescaler);
        return -EINVAL;
      }

    timer_freq = priv->config->pclkd_freq / prescaler_divs[prescaler];

    /* period = round(timer_freq / frequency) -> (timer_freq + freq >> 1)/freq */
    period = (uint32_t)((((uint64_t)timer_freq) + ((uint64_t)info->frequency >> 1)) /
            (uint64_t)info->frequency);
  }

  /* Verify period fits in the channel's maximum period */
  if (period == 0 || period > priv->config->max_period)
    {
      pwmerr("ERROR: period %" PRIu32 " out of range for GPT%" PRIu32 " (max %" PRIu32 ")\n",
             period, priv->config->channel, priv->config->max_period);
      return -ERANGE;
    }

  pwminfo("prescaler=%" PRIu32 ", timer_freq=%" PRIu32 ", period=%" PRIu32 "\n",
    prescaler, timer_freq, period);

  /* Calculate duty cycle values */

#ifdef CONFIG_PWM_MULTICHAN
  /* Map per-channel requests to GTIOCA (A) and GTIOCB (B).
   * pwm.h channel numbers start at 1. We treat channel==1 -> A, ==2 -> B.
   * channel==0 indicates unused and negative channel indicates end.
   */
  duty_a = duty_b = 0;
  for (int i = 0; i < CONFIG_PWM_NCHANNELS; i++)
    {
      int8_t ch = info->channels[i].channel;
      if (ch == 0)
        {
          /* channel 0: not used */
          continue;
        }
      if (ch < 0)
        {
          /* negative channel indicates no more channels */
          break;
        }

      /* Convert ub16 duty to timer ticks with rounding: add 0.5 (0x8000) before shift */
      uint32_t chduty = (uint32_t)((((uint64_t)period * (uint64_t)info->channels[i].duty) + 0x8000ULL) >> 16);
      if (ch == 1)
        {
          duty_a = chduty;
        }
      else if (ch == 2)
        {
          duty_b = chduty;
        }
      else
        {
          pwmerr("GPT%u: Unsupported channel number %d\n",
                 priv->config->channel, ch);
          return -EINVAL;
        }
    }

  /* If only one channel was provided, duplicate to the other compare */
  if (duty_b == 0 && duty_a != 0)
    {
      duty_b = duty_a;
    }
#else
  /* Convert ub16 duty to timer ticks with rounding */
  duty_a = (uint32_t)((((uint64_t)period * (uint64_t)info->duty) + 0x8000ULL) >> 16);
  duty_b = duty_a;
#endif


  /* Make the start sequence atomic */
  irqstate_t flags = enter_critical_section();

  /* Disable write protection */
  gpt_putreg(priv, R_GPT32_GTWP_OFFSET, GPT_GTWP_PRKEY);

  /* Stop the timer */
  regval = gpt_getreg(priv, R_GPT32_GTCR_OFFSET);
  regval &= ~GPT_GTCR_CST;
  gpt_putreg(priv, R_GPT32_GTCR_OFFSET, regval);

  /* Configure the prescaler using TPCS mapping table */
  {
    static const uint32_t prescaler_to_tpcs[] = {0, 1, 2, 3, 4, 5, 6, 8, 10};
    uint32_t tpcs = prescaler_to_tpcs[prescaler];
    regval = GPT_GTCR_MD_SAW_WAVE_UP | (tpcs << GPT_GTCR_TPCS_SHIFT);
    gpt_putreg(priv, R_GPT32_GTCR_OFFSET, regval);
  }

  /* Set the period */
  gpt_putreg(priv, R_GPT32_GTPR_OFFSET, period - 1);

  /* Set the duty cycles */
  gpt_putreg(priv, R_GPT32_GTCCRA_OFFSET, duty_a);
  gpt_putreg(priv, R_GPT32_GTCCRB_OFFSET, duty_b);

  /* Force buffer transfer to ensure atomic duty cycle update.
   * Setting CCRSWT triggers immediate transfer from buffer registers
   * to compare registers, preventing glitches during rapid updates.
   * This bit is write-only and auto-clears after transfer.
   */
  gpt_putreg(priv, R_GPT32_GTBER_OFFSET,
             GPT_GTBER_PWM_ENABLE | GPT_GTBER_CCRSWT);

  /* Reset the counter */
  gpt_putreg(priv, R_GPT32_GTCNT_OFFSET, 0);

  /* Configure I/O pins for PWM output:
   * - Saw-wave PWM mode: Initial low, high at compare match, low at period end
   * - Enable output on both GTIOCA and GTIOCB pins
   */
  regval = GPT_GTIOR_PWM_HIGH_AB;
  gpt_putreg(priv, R_GPT32_GTIOR_OFFSET, regval);

  /* Start the timer */
  regval = gpt_getreg(priv, R_GPT32_GTCR_OFFSET);
  regval |= GPT_GTCR_CST;
  gpt_putreg(priv, R_GPT32_GTCR_OFFSET, regval);

  /* Re-enable write protection */
  gpt_putreg(priv, R_GPT32_GTWP_OFFSET,
             GPT_GTWP_PRKEY | GPT_GTWP_WP | GPT_GTWP_CMNWP);

  leave_critical_section(flags);

  gpt_dumpregs(priv, "After start");

  priv->started = true;
  priv->frequency = info->frequency;
  priv->period = period;
  priv->prescaler = prescaler;
  priv->duty_a = duty_a;
#ifdef CONFIG_PWM_MULTICHAN
  priv->duty_b = duty_b;
#endif

  /* Log the channel timing after start */
  gpt_log_channel((uint8_t)priv->config->channel,
                  info->frequency,
                  prescaler,
                  priv->config->pclkd_freq,
                  period,
                  duty_a);

  return 0;
}

/****************************************************************************
 * Name: gpt_stop
 *
 * Description:
 *   Stop the pulsed output and reset the timer resources
 *
 * Input Parameters:
 *   dev - A reference to the lower half PWM driver state structure
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

static int gpt_stop(struct pwm_lowerhalf_s *dev)
{
  struct ra_gpt_s *priv = (struct ra_gpt_s *)dev;
  uint32_t regval;

  pwminfo("GPT%" PRIu32 " stop\n", priv->config->channel);


  irqstate_t flags = enter_critical_section();

  /* Disable write protection */
  gpt_putreg(priv, R_GPT32_GTWP_OFFSET, GPT_GTWP_PRKEY);

  /* Stop the timer */
  regval = gpt_getreg(priv, R_GPT32_GTCR_OFFSET);
  regval &= ~GPT_GTCR_CST;
  gpt_putreg(priv, R_GPT32_GTCR_OFFSET, regval);

  /* Disable PWM outputs - clear output enable bits and set to low */
  regval = GPT_GTIOR_GTIOA_INITIAL_LOW | GPT_GTIOR_GTIOB_INITIAL_LOW;
  gpt_putreg(priv, R_GPT32_GTIOR_OFFSET, regval);

  /* Re-enable write protection */
  gpt_putreg(priv, R_GPT32_GTWP_OFFSET,
             GPT_GTWP_PRKEY | GPT_GTWP_WP | GPT_GTWP_CMNWP);

  leave_critical_section(flags);

  gpt_dumpregs(priv, "After stop");

  priv->started = false;
  return 0;
}

/****************************************************************************
 * Name: gpt_ioctl
 *
 * Description:
 *   Lower-half logic may support platform-specific ioctl commands
 *
 * Input Parameters:
 *   dev - A reference to the lower half PWM driver state structure
 *   cmd - The ioctl command
 *   arg - The argument accompanying the ioctl command
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

static int gpt_ioctl(struct pwm_lowerhalf_s *dev, int cmd,
                     unsigned long arg)
{
  struct ra_gpt_s *priv = (struct ra_gpt_s *)dev;
  int ret = 0;

  pwminfo("GPT%" PRIu32 " ioctl: cmd=%d arg=%08lx\n", priv->config->channel, cmd, arg);

  switch (cmd)
    {
      case PWMIOC_GETCHARACTERISTICS:
        {
          /* Populate a pwm_info_s with the current settings */
          struct pwm_info_s info;
          memset(&info, 0, sizeof(info));

          info.frequency = priv->frequency;
#ifdef CONFIG_PWM_MULTICHAN
          /* Fill channels array: channel numbers 1->A, 2->B */
          info.channels[0].channel = 1;
          /* Convert ticks to ub16 (16.16) with rounding: add half period before divide */
          info.channels[0].duty = (ub16_t)((priv->period == 0) ? 0 :
                                    (ub16_t)((((uint64_t)priv->duty_a << 16) + (priv->period >> 1)) / priv->period));
          info.channels[1].channel = 2;
          info.channels[1].duty = (ub16_t)((priv->period == 0) ? 0 :
                                    (ub16_t)((((uint64_t)priv->duty_b << 16) + (priv->period >> 1)) / priv->period));
#else
          /* Convert ticks to ub16 (16.16) with rounding */
          info.duty = (ub16_t)((priv->period == 0) ? 0 :
                                (ub16_t)((((uint64_t)priv->duty_a << 16) + (priv->period >> 1)) / priv->period));
#endif
          /* Copy into caller-provided buffer (arg is a pointer in kernel space)
           * Since ioctl() is called from kernel context, simple assignment is OK.
           */
          struct pwm_info_s *user = (struct pwm_info_s *)((FAR void *)arg);
          if (user == NULL)
            {
              ret = -EFAULT;
            }
          else
            {
              memcpy(user, &info, sizeof(info));
              ret = 0;
            }
        }
        break;

      /* Dead-time configuration command */
      case RA_GPTIOC_SETDEADTIME:
        {
          struct ra_gpt_deadtime_s *dt =
                        (struct ra_gpt_deadtime_s *)((FAR void *)arg);
          if (dt == NULL)
            {
              ret = -EFAULT;
            }
          else
            {
              ret = gpt_set_deadtime(priv, dt->deadtime_up, dt->deadtime_dn,
                                     dt->enable);
            }
        }
        break;

      /* External trigger configuration command */
      case RA_GPTIOC_SETTRIGGER:
        {
          struct ra_gpt_trigger_s *trig =
                        (struct ra_gpt_trigger_s *)((FAR void *)arg);
          if (trig == NULL)
            {
              ret = -EFAULT;
            }
          else
            {
              ret = gpt_set_trigger(priv, trig);
            }
        }
        break;

      /* Input capture configuration command */
      case RA_GPTIOC_SETCAPTURE:
        {
          struct ra_gpt_capture_s *cap =
                        (struct ra_gpt_capture_s *)((FAR void *)arg);
          if (cap == NULL)
            {
              ret = -EFAULT;
            }
          else
            {
              ret = gpt_set_capture(priv, cap);
            }
        }
        break;

      /* Get captured value command */
      case RA_GPTIOC_GETCAPTURE:
        {
          struct ra_gpt_captured_s *cap =
                        (struct ra_gpt_captured_s *)((FAR void *)arg);
          if (cap == NULL)
            {
              ret = -EFAULT;
            }
          else
            {
              ret = gpt_get_capture(priv, cap);
            }
        }
        break;

#ifdef CONFIG_RA_DMAC
      /* DMA configuration command */
      case RA_GPTIOC_SETDMA:
        {
          struct ra_gpt_dma_s *dma =
                        (struct ra_gpt_dma_s *)((FAR void *)arg);
          if (dma == NULL)
            {
              ret = -EFAULT;
            }
          else
            {
              ret = gpt_set_dma(priv, dma);
            }
        }
        break;
#endif /* CONFIG_RA_DMAC */

      default:
        ret = -ENOTTY;
        break;
    }

  return ret;
}

#ifdef CONFIG_TIMER
/****************************************************************************
 * Name: gpt_interrupt
 *
 * Description:
 *   GPT timer interrupt handler. Handles overflow and compare match
 *   interrupts for timer mode operation.
 *
 * Input Parameters:
 *   irq     - The IRQ number
 *   context - The interrupt context
 *   arg     - The GPT device structure
 *
 * Returned Value:
 *   OK on success
 *
 ****************************************************************************/

static int gpt_interrupt(int irq, void *context, void *arg)
{
  struct ra_gpt_s *priv = (struct ra_gpt_s *)arg;
  uint32_t status;

  DEBUGASSERT(priv != NULL);

  /* Disable write protection to access status register */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET, GPT_GTWP_PRKEY);

  /* Read and clear status flags */

  status = gpt_getreg(priv, R_GPT32_GTST_OFFSET);

  /* Clear the interrupt flags by writing 0 to the flag bits */

  gpt_putreg(priv, R_GPT32_GTST_OFFSET, 0);

  /* Re-enable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET,
             GPT_GTWP_PRKEY | GPT_GTWP_WP | GPT_GTWP_CMNWP);

  /* Check for overflow interrupt (timer mode) */

  if (status & GPT_GTST_TCFPO)
    {
      /* Call the user callback if registered */

      if (priv->callback != NULL)
        {
          priv->callback(priv->arg);
        }
    }

  /* Check for compare match A interrupt */

  if (status & GPT_GTST_TCFA)
    {
      /* Handle compare match A - could be used for PWM notifications */
    }

  /* Check for compare match B interrupt */

  if (status & GPT_GTST_TCFB)
    {
      /* Handle compare match B - could be used for PWM notifications */
    }

  return OK;
}

/****************************************************************************
 * Name: gpt_timer_start
 *
 * Description:
 *   Start the timer in timer mode.
 *
 * Input Parameters:
 *   lower - A reference to the lower half timer driver state structure
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

static int gpt_timer_start(struct timer_lowerhalf_s *lower)
{
  struct ra_gpt_s *priv = (struct ra_gpt_s *)lower;
  uint32_t regval;

  pwminfo("GPT%" PRIu32 " timer start\n", priv->config->channel);

  irqstate_t flags = enter_critical_section();

  /* Disable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET, GPT_GTWP_PRKEY);

  /* Reset counter to 0 */

  gpt_putreg(priv, R_GPT32_GTCNT_OFFSET, 0);

  /* Start the timer */

  regval = gpt_getreg(priv, R_GPT32_GTCR_OFFSET);
  regval |= GPT_GTCR_CST;
  gpt_putreg(priv, R_GPT32_GTCR_OFFSET, regval);

  /* Re-enable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET,
             GPT_GTWP_PRKEY | GPT_GTWP_WP | GPT_GTWP_CMNWP);

  leave_critical_section(flags);

  priv->started = true;
  return OK;
}

/****************************************************************************
 * Name: gpt_timer_stop
 *
 * Description:
 *   Stop the timer.
 *
 * Input Parameters:
 *   lower - A reference to the lower half timer driver state structure
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

static int gpt_timer_stop(struct timer_lowerhalf_s *lower)
{
  struct ra_gpt_s *priv = (struct ra_gpt_s *)lower;
  uint32_t regval;

  pwminfo("GPT%" PRIu32 " timer stop\n", priv->config->channel);

  irqstate_t flags = enter_critical_section();

  /* Disable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET, GPT_GTWP_PRKEY);

  /* Stop the timer */

  regval = gpt_getreg(priv, R_GPT32_GTCR_OFFSET);
  regval &= ~GPT_GTCR_CST;
  gpt_putreg(priv, R_GPT32_GTCR_OFFSET, regval);

  /* Re-enable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET,
             GPT_GTWP_PRKEY | GPT_GTWP_WP | GPT_GTWP_CMNWP);

  leave_critical_section(flags);

  priv->started = false;
  return OK;
}

/****************************************************************************
 * Name: gpt_timer_getstatus
 *
 * Description:
 *   Get the current timer status.
 *
 * Input Parameters:
 *   lower  - A reference to the lower half timer driver state structure
 *   status - Pointer to status structure to fill
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

static int gpt_timer_getstatus(struct timer_lowerhalf_s *lower,
                               struct timer_status_s *status)
{
  struct ra_gpt_s *priv = (struct ra_gpt_s *)lower;
  uint32_t period;
  uint32_t counter;
  uint32_t timer_freq;
  /* Full prescaler divider table - matches gpt_calculate_prescaler() */
  static const uint32_t prescaler_divs[] = {1, 2, 4, 8, 16, 32, 64, 256, 1024};

  DEBUGASSERT(status != NULL);

  irqstate_t flags = enter_critical_section();

  /* Read current values */

  period = gpt_getreg(priv, R_GPT32_GTPR_OFFSET);
  counter = gpt_getreg(priv, R_GPT32_GTCNT_OFFSET);

  leave_critical_section(flags);

  /* Calculate timer frequency */

  if (priv->prescaler < (sizeof(prescaler_divs) / sizeof(prescaler_divs[0])))
    {
      timer_freq = priv->config->pclkd_freq / prescaler_divs[priv->prescaler];
    }
  else
    {
      timer_freq = priv->config->pclkd_freq;
    }

  /* Convert timer ticks to microseconds */

  status->flags = 0;
  if (priv->started)
    {
      status->flags |= TCFLAGS_ACTIVE;
    }

  if (priv->callback != NULL)
    {
      status->flags |= TCFLAGS_HANDLER;
    }

  /* timeout = period in microseconds */

  if (timer_freq > 0)
    {
      status->timeout = (uint32_t)(((uint64_t)(period + 1) * 1000000ULL) / timer_freq);
      status->timeleft = (uint32_t)(((uint64_t)(period - counter) * 1000000ULL) / timer_freq);
    }
  else
    {
      status->timeout = 0;
      status->timeleft = 0;
    }

  return OK;
}

/****************************************************************************
 * Name: gpt_timer_settimeout
 *
 * Description:
 *   Set a new timeout value (and reset the timer).
 *
 * Input Parameters:
 *   lower   - A reference to the lower half timer driver state structure
 *   timeout - Timeout in microseconds
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

static int gpt_timer_settimeout(struct timer_lowerhalf_s *lower,
                                uint32_t timeout)
{
  struct ra_gpt_s *priv = (struct ra_gpt_s *)lower;
  uint32_t prescaler;
  uint32_t timer_freq;
  uint32_t period;
  uint32_t regval;
  /* Full prescaler divider table - matches gpt_calculate_prescaler() */
  static const uint32_t prescaler_divs[] = {1, 2, 4, 8, 16, 32, 64, 256, 1024};
  static const uint32_t prescaler_to_tpcs[] = {0, 1, 2, 3, 4, 5, 6, 8, 10};
  const size_t num_prescalers = sizeof(prescaler_divs) / sizeof(prescaler_divs[0]);

  pwminfo("GPT%" PRIu32 " timer settimeout: %" PRIu32 " us\n",
          priv->config->channel, timeout);

  /* Convert timeout in microseconds to timer ticks.
   * First, find an appropriate prescaler.
   */

  for (prescaler = 0; prescaler < num_prescalers; prescaler++)
    {
      timer_freq = priv->config->pclkd_freq / prescaler_divs[prescaler];

      /* period = (timeout_us * timer_freq) / 1000000 */

      period = (uint32_t)(((uint64_t)timeout * timer_freq + 500000ULL) / 1000000ULL);

      /* Check if period fits in 32-bit counter */

      if (period > 0 && period <= priv->config->max_period)
        {
          break;
        }
    }

  if (prescaler >= num_prescalers)
    {
      pwmerr("ERROR: timeout %" PRIu32 " us exceeds max period\n", timeout);
      return -ERANGE;
    }

  irqstate_t flags = enter_critical_section();

  /* Disable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET, GPT_GTWP_PRKEY);

  /* Stop the timer first */

  regval = gpt_getreg(priv, R_GPT32_GTCR_OFFSET);
  regval &= ~GPT_GTCR_CST;
  gpt_putreg(priv, R_GPT32_GTCR_OFFSET, regval);

  /* Configure the prescaler using TPCS mapping table */

  regval = GPT_GTCR_MD_SAW_WAVE_UP | (prescaler_to_tpcs[prescaler] << GPT_GTCR_TPCS_SHIFT);
  gpt_putreg(priv, R_GPT32_GTCR_OFFSET, regval);

  /* Set the period */

  gpt_putreg(priv, R_GPT32_GTPR_OFFSET, period - 1);

  /* Reset counter */

  gpt_putreg(priv, R_GPT32_GTCNT_OFFSET, 0);

  /* Re-enable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET,
             GPT_GTWP_PRKEY | GPT_GTWP_WP | GPT_GTWP_CMNWP);

  leave_critical_section(flags);

  priv->prescaler = prescaler;
  priv->period = period;

  return OK;
}

/****************************************************************************
 * Name: gpt_timer_setcallback
 *
 * Description:
 *   Set the timer callback function. This function will be called when the
 *   timer expires.
 *
 * Input Parameters:
 *   lower    - A reference to the lower half timer driver state structure
 *   callback - The callback function to call on timer expiration
 *   arg      - Argument to pass to the callback function
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

static void gpt_timer_setcallback(struct timer_lowerhalf_s *lower,
                                  tccb_t callback, void *arg)
{
  struct ra_gpt_s *priv = (struct ra_gpt_s *)lower;
  irqstate_t flags;
  uint32_t regval;
  int ret;

  pwminfo("GPT%" PRIu32 " timer setcallback\n", priv->config->channel);

  flags = enter_critical_section();

  /* Save the callback */

  priv->callback = (void (*)(void *))callback;
  priv->arg = arg;

  /* Disable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET, GPT_GTWP_PRKEY);

  if (callback != NULL)
    {
      /* Attach the interrupt handler if not already attached */

      if (priv->irq == 0)
        {
          /* Attach interrupt handler via ICU using overflow ELC event */

          ret = ra_icu_attach(priv->config->elc, gpt_interrupt,
                              (void *)priv, true);
          if (ret >= 0)
            {
              priv->irq = ret;
            }
          else
            {
              pwmerr("ERROR: Failed to attach GPT interrupt: %d\n", ret);
            }
        }

      /* Enable overflow interrupt in GTINTAD register.
       * For saw-wave up-counting mode (timer mode), the counter overflows
       * when it reaches GTPR and resets to 0. This sets the TCFPO flag in
       * GTST and generates an interrupt if enabled in GTINTAD.
       *
       * GTINTAD bits for overflow interrupt:
       * - GRPABH_OVF_UDF (bit 28): Output overflow/underflow on interrupt group
       * - GRP (bits 25:24): Select interrupt output group (0 = Group A)
       *
       * The ELC event (configured in config->elc) routes the interrupt to ICU.
       */
      regval = gpt_getreg(priv, R_GPT32_GTINTAD_OFFSET);
      regval |= GPT_GTINTAD_GRP_A | GPT_GTINTAD_GRPABH_OVF_UDF;
      gpt_putreg(priv, R_GPT32_GTINTAD_OFFSET, regval);

      pwminfo("GPT%" PRIu32 " overflow interrupt enabled, GTINTAD=%08" PRIx32 "\n",
              priv->config->channel, regval);
    }
  else
    {
      /* Disable overflow interrupt in GTINTAD */

      regval = gpt_getreg(priv, R_GPT32_GTINTAD_OFFSET);
      regval &= ~(GPT_GTINTAD_GRP_MASK | GPT_GTINTAD_GRPABH_OVF_UDF);
      gpt_putreg(priv, R_GPT32_GTINTAD_OFFSET, regval);

      /* Disable interrupt and detach handler */

      if (priv->irq != 0)
        {
          ra_icu_detach(priv->irq);
          priv->irq = 0;
        }
    }

  /* Re-enable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET,
             GPT_GTWP_PRKEY | GPT_GTWP_WP | GPT_GTWP_CMNWP);

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: gpt_timer_maxtimeout
 *
 * Description:
 *   Get the maximum supported timeout value.
 *
 * Input Parameters:
 *   lower      - A reference to the lower half timer driver state structure
 *   maxtimeout - Pointer to store the maximum timeout in microseconds
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

static int gpt_timer_maxtimeout(struct timer_lowerhalf_s *lower,
                                uint32_t *maxtimeout)
{
  struct ra_gpt_s *priv = (struct ra_gpt_s *)lower;
  uint64_t max_us;
  uint32_t min_timer_freq;

  DEBUGASSERT(maxtimeout != NULL);

  /* With the largest prescaler (1024), calculate max timeout */

  min_timer_freq = priv->config->pclkd_freq / 1024;

  /* max_timeout_us = (max_period * 1000000) / min_timer_freq */

  max_us = ((uint64_t)priv->config->max_period * 1000000ULL) / min_timer_freq;

  /* Clamp to 32-bit max */

  if (max_us > UINT32_MAX)
    {
      *maxtimeout = UINT32_MAX;
    }
  else
    {
      *maxtimeout = (uint32_t)max_us;
    }

  return OK;
}
#endif /* CONFIG_TIMER */

/****************************************************************************
 * Name: gpt_set_deadtime
 *
 * Description:
 *   Configure dead-time for complementary PWM output.
 *   Dead-time inserts a delay between turning off one output and turning on
 *   the complementary output to prevent shoot-through in half-bridge drivers.
 *
 * Input Parameters:
 *   priv        - A reference to the GPT structure
 *   deadtime_up - Dead-time value for rising edge (in timer ticks)
 *   deadtime_dn - Dead-time value for falling edge (in timer ticks)
 *   enable      - True to enable dead-time, false to disable
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

static int gpt_set_deadtime(struct ra_gpt_s *priv, uint32_t deadtime_up,
                            uint32_t deadtime_dn, bool enable)
{
  uint32_t regval;
  irqstate_t flags;

  pwminfo("GPT%" PRIu32 " deadtime: up=%" PRIu32 " dn=%" PRIu32 " en=%d\n",
          priv->config->channel, deadtime_up, deadtime_dn, enable);

  flags = enter_critical_section();

  /* Disable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET, GPT_GTWP_PRKEY);

  if (enable)
    {
      /* Set dead-time values
       * GTDVU: Dead-time for up-counting (rising edge delay)
       * GTDVD: Dead-time for down-counting (falling edge delay)
       * Note: For saw-wave mode, only GTDVU is typically used
       */

      gpt_putreg(priv, R_GPT32_GTDVU_OFFSET, deadtime_up);
#if defined(CONFIG_RA8P1_GROUP)
      /* RA8P1 has separate GTDVD register */
      gpt_putreg(priv, R_GPT32_GTDVD_OFFSET, deadtime_dn);
#endif

      /* Enable dead-time generation
       * TDE (bit 0): Enable negative-phase waveform (dead-time)
       * When TDE=1, GTIOCB output becomes the complement of GTIOCA
       * with dead-time insertion
       */

      regval = GPT_GTDTCR_TDE;
      gpt_putreg(priv, R_GPT32_GTDTCR_OFFSET, regval);
    }
  else
    {
      /* Disable dead-time generation */

      gpt_putreg(priv, R_GPT32_GTDTCR_OFFSET, 0);
      gpt_putreg(priv, R_GPT32_GTDVU_OFFSET, 0);
#if defined(CONFIG_RA8P1_GROUP)
      gpt_putreg(priv, R_GPT32_GTDVD_OFFSET, 0);
#endif
    }

  /* Re-enable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET,
             GPT_GTWP_PRKEY | GPT_GTWP_WP | GPT_GTWP_CMNWP);

  leave_critical_section(flags);

  return OK;
}

/****************************************************************************
 * Name: gpt_set_trigger
 *
 * Description:
 *   Configure external trigger sources for the GPT channel.
 *   This enables ELC events to start, stop, clear, or count the timer.
 *
 * Input Parameters:
 *   priv   - A reference to the GPT structure
 *   config - Trigger configuration
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

static int gpt_set_trigger(struct ra_gpt_s *priv,
                           const struct ra_gpt_trigger_s *config)
{
  uint32_t regval;
  irqstate_t flags;

  DEBUGASSERT(priv != NULL && config != NULL);

  pwminfo("GPT%" PRIu32 " trigger: source=%d action=%02x elc=%04x en=%d\n",
          priv->config->channel, config->source, config->action,
          config->elc_event, config->enable);

  flags = enter_critical_section();

  /* Disable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET, GPT_GTWP_PRKEY);

  if (config->enable && config->source == RA_GPT_TRIGGER_ELC)
    {
      /* Configure start source (GTSSR) if START action is requested */

      if (config->action & RA_GPT_TRIGGER_START)
        {
          /* Set ELC event as start source
           * The ELC event number maps to specific bits in GTSSR
           * For ELC events, we use the event link controller to route
           * peripheral events to GPT start triggers
           */

          regval = GPT_SSSR_ELC_EVENT(config->elc_event & 0x07);
          gpt_putreg(priv, R_GPT32_GTSSR_OFFSET, regval);
        }

      /* Configure stop source (GTPSR) if STOP action is requested */

      if (config->action & RA_GPT_TRIGGER_STOP)
        {
          regval = GPT_SSSR_ELC_EVENT(config->elc_event & 0x07);
          gpt_putreg(priv, R_GPT32_GTPSR_OFFSET, regval);
        }

      /* Configure clear source (GTCSR) if CLEAR action is requested */

      if (config->action & RA_GPT_TRIGGER_CLEAR)
        {
          regval = GPT_SSSR_ELC_EVENT(config->elc_event & 0x07);
          gpt_putreg(priv, R_GPT32_GTCSR_OFFSET, regval);
        }

      /* Configure up count source (GTUPSR) if COUNT_UP action is requested */

      if (config->action & RA_GPT_TRIGGER_COUNT_UP)
        {
          regval = GPT_SSSR_ELC_EVENT(config->elc_event & 0x07);
          gpt_putreg(priv, R_GPT32_GTUPSR_OFFSET, regval);
        }

      /* Configure down count source (GTDNSR) if COUNT_DN action is requested */

      if (config->action & RA_GPT_TRIGGER_COUNT_DN)
        {
          regval = GPT_SSSR_ELC_EVENT(config->elc_event & 0x07);
          gpt_putreg(priv, R_GPT32_GTDNSR_OFFSET, regval);
        }

      /* Configure input capture A source (GTICASR) if CAPTURE_A action */

      if (config->action & RA_GPT_TRIGGER_CAPTURE_A)
        {
          regval = GPT_SSSR_ELC_EVENT(config->elc_event & 0x07);
          gpt_putreg(priv, R_GPT32_GTICASR_OFFSET, regval);
        }

      /* Configure input capture B source (GTICBSR) if CAPTURE_B action */

      if (config->action & RA_GPT_TRIGGER_CAPTURE_B)
        {
          regval = GPT_SSSR_ELC_EVENT(config->elc_event & 0x07);
          gpt_putreg(priv, R_GPT32_GTICBSR_OFFSET, regval);
        }
    }
  else
    {
      /* Disable external triggers - clear all source select registers */

      gpt_putreg(priv, R_GPT32_GTSSR_OFFSET, 0);
      gpt_putreg(priv, R_GPT32_GTPSR_OFFSET, 0);
      gpt_putreg(priv, R_GPT32_GTCSR_OFFSET, 0);
      gpt_putreg(priv, R_GPT32_GTUPSR_OFFSET, 0);
      gpt_putreg(priv, R_GPT32_GTDNSR_OFFSET, 0);
      gpt_putreg(priv, R_GPT32_GTICASR_OFFSET, 0);
      gpt_putreg(priv, R_GPT32_GTICBSR_OFFSET, 0);
    }

  /* Re-enable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET,
             GPT_GTWP_PRKEY | GPT_GTWP_WP | GPT_GTWP_CMNWP);

  leave_critical_section(flags);

  return OK;
}

/****************************************************************************
 * Name: gpt_set_capture
 *
 * Description:
 *   Configure input capture mode for the GPT channel.
 *   This enables capturing the counter value on external pin edges.
 *
 * Input Parameters:
 *   priv   - A reference to the GPT structure
 *   config - Capture configuration
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

static int gpt_set_capture(struct ra_gpt_s *priv,
                           const struct ra_gpt_capture_s *config)
{
  uint32_t gtior;
  uint32_t gticsr;
  irqstate_t flags;

  DEBUGASSERT(priv != NULL && config != NULL);

  pwminfo("GPT%" PRIu32 " capture: ch=%d edge=%d filter=%d en=%d\n",
          priv->config->channel, config->channel, config->edge,
          config->filter_enable, config->enable);

  if (config->channel > 1)
    {
      return -EINVAL;
    }

  flags = enter_critical_section();

  /* Disable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET, GPT_GTWP_PRKEY);

  /* Read current GTIOR register */

  gtior = gpt_getreg(priv, R_GPT32_GTIOR_OFFSET);

  if (config->enable)
    {
      /* Configure GTIOR for input capture mode */

      if (config->channel == 0)  /* Capture A (GTIOCA) */
        {
          /* Clear existing GTIOA configuration */

          gtior &= ~GPT_GTIOR_GTIOA_MASK;
          gtior &= ~GPT_GTIOR_OAE;  /* Disable output, configure as input */

          /* Set edge detection mode */

          switch (config->edge)
            {
              case RA_GPT_CAPTURE_RISING:
                gtior |= GPT_GTIOR_GTIOA_INPUT_RISE;
                break;
              case RA_GPT_CAPTURE_FALLING:
                gtior |= GPT_GTIOR_GTIOA_INPUT_FALL;
                break;
              case RA_GPT_CAPTURE_BOTH:
                gtior |= GPT_GTIOR_GTIOA_INPUT_BOTH;
                break;
              default:
                gtior |= GPT_GTIOR_GTIOA_DISABLED;
                break;
            }

          /* Configure noise filter A */

          if (config->filter_enable)
            {
              gtior |= GPT_GTIOR_NFAEN;
              gtior &= ~GPT_GTIOR_NFCSA_MASK;
              gtior |= (config->filter_clock & 0x03) << GPT_GTIOR_NFCSA_SHIFT;
            }
          else
            {
              gtior &= ~GPT_GTIOR_NFAEN;
            }

          /* Configure capture source - rising/falling edge on GTIOCA */

          gticsr = 0;
          if (config->edge & RA_GPT_CAPTURE_RISING)
            {
              gticsr |= GPT_GTICSR_GTIOCA_RISE;
            }

          if (config->edge & RA_GPT_CAPTURE_FALLING)
            {
              gticsr |= GPT_GTICSR_GTIOCA_FALL;
            }

          gpt_putreg(priv, R_GPT32_GTICASR_OFFSET, gticsr);
        }
      else  /* Capture B (GTIOCB) */
        {
          /* Clear existing GTIOB configuration */

          gtior &= ~GPT_GTIOR_GTIOB_MASK;
          gtior &= ~GPT_GTIOR_OBE;  /* Disable output, configure as input */

          /* Set edge detection mode */

          switch (config->edge)
            {
              case RA_GPT_CAPTURE_RISING:
                gtior |= GPT_GTIOR_GTIOB_INPUT_RISE;
                break;
              case RA_GPT_CAPTURE_FALLING:
                gtior |= GPT_GTIOR_GTIOB_INPUT_FALL;
                break;
              case RA_GPT_CAPTURE_BOTH:
                gtior |= GPT_GTIOR_GTIOB_INPUT_BOTH;
                break;
              default:
                gtior |= GPT_GTIOR_GTIOB_DISABLED;
                break;
            }

          /* Configure noise filter B */

          if (config->filter_enable)
            {
              gtior |= GPT_GTIOR_NFBEN;
              gtior &= ~GPT_GTIOR_NFCSB_MASK;
              gtior |= (config->filter_clock & 0x03) << GPT_GTIOR_NFCSB_SHIFT;
            }
          else
            {
              gtior &= ~GPT_GTIOR_NFBEN;
            }

          /* Configure capture source - rising/falling edge on GTIOCB */

          gticsr = 0;
          if (config->edge & RA_GPT_CAPTURE_RISING)
            {
              gticsr |= GPT_GTICSR_GTIOCB_RISE;
            }

          if (config->edge & RA_GPT_CAPTURE_FALLING)
            {
              gticsr |= GPT_GTICSR_GTIOCB_FALL;
            }

          gpt_putreg(priv, R_GPT32_GTICBSR_OFFSET, gticsr);
        }

      /* Update mode to input capture */

      priv->mode = RA_GPT_MODE_INPUT_CAPTURE;
    }
  else
    {
      /* Disable input capture - disable capture source and reset to PWM mode */

      if (config->channel == 0)
        {
          gpt_putreg(priv, R_GPT32_GTICASR_OFFSET, 0);
          gtior &= ~GPT_GTIOR_NFAEN;
        }
      else
        {
          gpt_putreg(priv, R_GPT32_GTICBSR_OFFSET, 0);
          gtior &= ~GPT_GTIOR_NFBEN;
        }
    }

  /* Write updated GTIOR */

  gpt_putreg(priv, R_GPT32_GTIOR_OFFSET, gtior);

  /* Re-enable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET,
             GPT_GTWP_PRKEY | GPT_GTWP_WP | GPT_GTWP_CMNWP);

  leave_critical_section(flags);

  return OK;
}

/****************************************************************************
 * Name: gpt_get_capture
 *
 * Description:
 *   Get the captured counter value from input capture mode.
 *
 * Input Parameters:
 *   priv    - A reference to the GPT structure
 *   capture - Pointer to capture result structure
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

static int gpt_get_capture(struct ra_gpt_s *priv,
                           struct ra_gpt_captured_s *capture)
{
  uint32_t status;
  irqstate_t flags;

  DEBUGASSERT(priv != NULL && capture != NULL);

  if (capture->channel > 1)
    {
      return -EINVAL;
    }

  flags = enter_critical_section();

  /* Read status register */

  status = gpt_getreg(priv, R_GPT32_GTST_OFFSET);

  /* Read captured value from appropriate register */

  if (capture->channel == 0)
    {
      capture->value = gpt_getreg(priv, R_GPT32_GTCCRA_OFFSET);
      capture->overflow = (status & GPT_GTST_TCFPO) != 0;
    }
  else
    {
      capture->value = gpt_getreg(priv, R_GPT32_GTCCRB_OFFSET);
      capture->overflow = (status & GPT_GTST_TCFPO) != 0;
    }

  leave_critical_section(flags);

  return OK;
}

#ifdef CONFIG_RA_DMAC
/****************************************************************************
 * Name: gpt_get_dma_channel
 *
 * Description:
 *   Get DMA channel assignment from Kconfig for the specified GPT channel
 *
 ****************************************************************************/

static void gpt_get_dma_channel(struct ra_gpt_s *priv, int *channel)
{
  /* Default to dynamic allocation */
  *channel = -1;

#ifdef CONFIG_RA_GPT0
  if (priv->config->channel == 0)
    {
#ifdef CONFIG_RA_DMAC_GPT0_CHANNEL
      *channel = CONFIG_RA_DMAC_GPT0_CHANNEL;
#endif
    }
#endif

#ifdef CONFIG_RA_GPT1
  if (priv->config->channel == 1)
    {
#ifdef CONFIG_RA_DMAC_GPT1_CHANNEL
      *channel = CONFIG_RA_DMAC_GPT1_CHANNEL;
#endif
    }
#endif

#ifdef CONFIG_RA_GPT2
  if (priv->config->channel == 2)
    {
#ifdef CONFIG_RA_DMAC_GPT2_CHANNEL
      *channel = CONFIG_RA_DMAC_GPT2_CHANNEL;
#endif
    }
#endif

#ifdef CONFIG_RA_GPT3
  if (priv->config->channel == 3)
    {
#ifdef CONFIG_RA_DMAC_GPT3_CHANNEL
      *channel = CONFIG_RA_DMAC_GPT3_CHANNEL;
#endif
    }
#endif

#ifdef CONFIG_RA_GPT4
  if (priv->config->channel == 4)
    {
#ifdef CONFIG_RA_DMAC_GPT4_CHANNEL
      *channel = CONFIG_RA_DMAC_GPT4_CHANNEL;
#endif
    }
#endif

#ifdef CONFIG_RA_GPT5
  if (priv->config->channel == 5)
    {
#ifdef CONFIG_RA_DMAC_GPT5_CHANNEL
      *channel = CONFIG_RA_DMAC_GPT5_CHANNEL;
#endif
    }
#endif

#ifdef CONFIG_RA_GPT10
  if (priv->config->channel == 10)
    {
#ifdef CONFIG_RA_DMAC_GPT10_CHANNEL
      *channel = CONFIG_RA_DMAC_GPT10_CHANNEL;
#endif
    }
#endif

#ifdef CONFIG_RA_GPT11
  if (priv->config->channel == 11)
    {
#ifdef CONFIG_RA_DMAC_GPT11_CHANNEL
      *channel = CONFIG_RA_DMAC_GPT11_CHANNEL;
#endif
    }
#endif

#ifdef CONFIG_RA_GPT12
  if (priv->config->channel == 12)
    {
#ifdef CONFIG_RA_DMAC_GPT12_CHANNEL
      *channel = CONFIG_RA_DMAC_GPT12_CHANNEL;
#endif
    }
#endif

#ifdef CONFIG_RA_GPT13
  if (priv->config->channel == 13)
    {
#ifdef CONFIG_RA_DMAC_GPT13_CHANNEL
      *channel = CONFIG_RA_DMAC_GPT13_CHANNEL;
#endif
    }
#endif

  pwminfo("GPT%" PRIu32 " DMA channel: %d\n", priv->config->channel, *channel);
}

/****************************************************************************
 * Name: gpt_set_dma
 *
 * Description:
 *   Configure DMA for waveform generation on the GPT channel.
 *   This enables automatic duty cycle updates via DMA transfers triggered
 *   by timer compare match or overflow events.
 *
 * Input Parameters:
 *   priv   - A reference to the GPT structure
 *   config - DMA configuration
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

static int gpt_set_dma(struct ra_gpt_s *priv,
                       const struct ra_gpt_dma_s *config)
{
  uint32_t regval;
  irqstate_t flags;
  ra_dmac_config_t dma_config;
  int ret;

  DEBUGASSERT(priv != NULL && config != NULL);

  pwminfo("GPT%" PRIu32 " DMA: trigger=%d src=%08lx dst=%08lx cnt=%" PRIu32 " en=%d\n",
          priv->config->channel, config->trigger,
          (unsigned long)config->src_addr,
          (unsigned long)config->dst_addr,
          config->transfer_count, config->enable);

  flags = enter_critical_section();

  /* Disable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET, GPT_GTWP_PRKEY);

  if (config->enable)
    {
      /* Configure GTINTAD for A/D (DMA) start request based on trigger */

      regval = gpt_getreg(priv, R_GPT32_GTINTAD_OFFSET);

      switch (config->trigger)
        {
          case 0:  /* Compare match A */
            regval |= GPT_GTINTAD_ADTRAUEN;
            /* Set A/D timing register A to trigger point */
            gpt_putreg(priv, R_GPT32_GTADTRA_OFFSET,
                       gpt_getreg(priv, R_GPT32_GTCCRA_OFFSET));
            break;

          case 1:  /* Compare match B */
            regval |= GPT_GTINTAD_ADTRBUEN;
            /* Set A/D timing register B to trigger point */
            gpt_putreg(priv, R_GPT32_GTADTRB_OFFSET,
                       gpt_getreg(priv, R_GPT32_GTCCRB_OFFSET));
            break;

          case 2:  /* Overflow - use compare at period-1 */
            regval |= GPT_GTINTAD_ADTRAUEN;
            gpt_putreg(priv, R_GPT32_GTADTRA_OFFSET,
                       gpt_getreg(priv, R_GPT32_GTPR_OFFSET));
            break;

          default:
            leave_critical_section(flags);
            return -EINVAL;
        }

      gpt_putreg(priv, R_GPT32_GTINTAD_OFFSET, regval);

      /* Configure DMA channel */

      memset(&dma_config, 0, sizeof(dma_config));
      dma_config.mode = RA_DMAC_MODE_REPEAT;
      dma_config.size = RA_DMAC_SIZE_32BIT;
      dma_config.src_addr_mode = RA_DMAC_ADDR_INCR;
      dma_config.dest_addr_mode = RA_DMAC_ADDR_FIXED;
      dma_config.trigger = RA_DMAC_TRIGGER_HW;
      dma_config.src_addr = config->src_addr;
      dma_config.dest_addr = config->dst_addr;
      dma_config.transfer_count = config->transfer_count;
      dma_config.repeat_area = RA_DMAC_REPEAT_AREA_SRC;

      /* The ELC event for GPT A/D request depends on channel
       * Use COMPARE_A event for DMA triggers as A/D trigger events
       * are not separately defined in the ELC event table
       */

      switch (priv->config->channel)
        {
          case 0:
            dma_config.elc_src = RA_ELC_GPT0_CAPTURE_COMPARE_A;
            break;
          case 1:
            dma_config.elc_src = RA_ELC_GPT1_CAPTURE_COMPARE_A;
            break;
          case 2:
            dma_config.elc_src = RA_ELC_GPT2_CAPTURE_COMPARE_A;
            break;
          case 3:
            dma_config.elc_src = RA_ELC_GPT3_CAPTURE_COMPARE_A;
            break;
          case 4:
            dma_config.elc_src = RA_ELC_GPT4_CAPTURE_COMPARE_A;
            break;
          case 5:
            dma_config.elc_src = RA_ELC_GPT5_CAPTURE_COMPARE_A;
            break;
          default:
            /* Use first channel for other GPT channels */
            dma_config.elc_src = RA_ELC_GPT0_CAPTURE_COMPARE_A;
            break;
        }

      /* Get DMA channel assignment from Kconfig */
      gpt_get_dma_channel(priv, &priv->dma_channel);

      /* Use assigned channel if configured, otherwise use dynamic allocation */
      if (priv->dma_channel >= 0)
        {
          ret = ra_dmac_open_channel(&priv->dma_handle, &dma_config, priv->dma_channel);
          pwminfo("GPT DMA using assigned channel %d\n", priv->dma_channel);
        }
      else
        {
          ret = ra_dmac_open(&priv->dma_handle, &dma_config);
          pwminfo("GPT DMA using dynamic channel allocation\n");
        }

      if (ret < 0)
        {
          pwmerr("Failed to open DMA: %d\n", ret);
          leave_critical_section(flags);
          return ret;
        }

      ret = ra_dmac_enable(priv->dma_handle);
      if (ret < 0)
        {
          pwmerr("Failed to enable DMA: %d\n", ret);
          ra_dmac_close(priv->dma_handle);
          priv->dma_handle = NULL;
          leave_critical_section(flags);
          return ret;
        }

      pwminfo("GPT%" PRIu32 " DMA configured and enabled\n", priv->config->channel);
    }
  else
    {
      /* Disable DMA triggers - clear ADTRA/ADTRB enables */

      regval = gpt_getreg(priv, R_GPT32_GTINTAD_OFFSET);
      regval &= ~(GPT_GTINTAD_ADTRAUEN | GPT_GTINTAD_ADTRADEN |
                  GPT_GTINTAD_ADTRBUEN | GPT_GTINTAD_ADTRBDEN);
      gpt_putreg(priv, R_GPT32_GTINTAD_OFFSET, regval);

      ret = OK;
    }

  /* Re-enable write protection */

  gpt_putreg(priv, R_GPT32_GTWP_OFFSET,
             GPT_GTWP_PRKEY | GPT_GTWP_WP | GPT_GTWP_CMNWP);

  leave_critical_section(flags);

  return ret;
}
#endif /* CONFIG_RA_DMAC */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_gpt_initialize
 *
 * Description:
 *   Initialize one GPT timer for use with the upper_level PWM driver.
 *
 * Input Parameters:
 *   channel - A number identifying the timer channel.
 *
 * Returned Value:
 *   On success, a pointer to the RA8 lower half PWM driver is returned.
 *   NULL is returned on any failure.
 *
 ****************************************************************************/

struct pwm_lowerhalf_s *ra_gpt_initialize(int channel)
{
  struct ra_gpt_s *lower;
  int i;

  pwminfo("GPT%d PWM initialize\n", channel);

  /* Find the matching configuration */

  for (i = 0; i < NGPT_CONFIGS; i++)
    {
      if (g_gpt_configs[i].channel == channel)
        {
          lower = &g_gpt_devs[i];

          /* Initialize the device structure */
          memset(lower, 0, sizeof(struct ra_gpt_s));

          lower->ops = &g_gpt_ops;
          lower->config = &g_gpt_configs[i];
          lower->pwm_mode = true;
          lower->started = false;

          /* GPIO pins for PWM output are configured at board level */

          /* Take the GPT out of module stop state */
          ra_mstp_start(lower->config->mstp);
#ifdef CONFIG_PWM_MULTICHAN
          lower->nchannels = 2;  /* GTIOCA and GTIOCB */
#endif
          break;
        }
    }

  if (i >= NGPT_CONFIGS)
    {
      pwmerr("ERROR: No such timer configured: %d\n", channel);
      return NULL;
    }

  /* Emit a log for the newly-initialized channel (registers may be default)
   * Use register reads for period/duty if available.
   */
  gpt_log_channel((uint8_t)lower->config->channel,
                  lower->frequency,
                  lower->prescaler,
                  lower->config->pclkd_freq,
                  gpt_getreg(lower, R_GPT32_GTPR_OFFSET),
                  gpt_getreg(lower, R_GPT32_GTCCRA_OFFSET));

  return (struct pwm_lowerhalf_s *)lower;
}

#ifdef CONFIG_TIMER
/****************************************************************************
 * Name: ra_gpt_timer_setup
 *
 * Description:
 *   Initialize one GPT timer for use with the upper_level timer driver.
 *   This provides a timer interface (periodic/one-shot) rather than PWM.
 *
 * Input Parameters:
 *   channel - A number identifying the timer channel.
 *
 * Returned Value:
 *   On success, a pointer to the RA8 lower half timer driver is returned.
 *   NULL is returned on any failure.
 *
 ****************************************************************************/

struct timer_lowerhalf_s *ra_gpt_timer_setup(int channel)
{
  struct ra_gpt_s *lower;
  int i;

  pwminfo("GPT%d timer initialize\n", channel);

  /* Find the matching configuration */

  for (i = 0; i < NGPT_CONFIGS; i++)
    {
      if (g_gpt_configs[i].channel == channel)
        {
          lower = &g_gpt_devs[i];

          /* Initialize the device structure */

          memset(lower, 0, sizeof(struct ra_gpt_s));

          lower->timer_ops = &g_gpt_timer_ops;
          lower->config = &g_gpt_configs[i];
          lower->pwm_mode = false;  /* Timer mode */
          lower->started = false;
          lower->callback = NULL;
          lower->arg = NULL;
          lower->irq = 0;

          /* Take the GPT out of module stop state */

          ra_mstp_start(lower->config->mstp);

          /* Configure for timer mode (saw-wave up-counting, no PWM output) */

          gpt_putreg(lower, R_GPT32_GTWP_OFFSET, GPT_GTWP_PRKEY);

          /* Configure timer for saw-wave mode (up-counting) with prescaler 1 */

          gpt_putreg(lower, R_GPT32_GTCR_OFFSET,
                     GPT_GTCR_MD_SAW_WAVE_UP | GPT_GTCR_TPCS_PCLKD_1);

          /* Disable all I/O outputs (timer mode - no PWM) */

          gpt_putreg(lower, R_GPT32_GTIOR_OFFSET, 0);

          /* Set default period */

          gpt_putreg(lower, R_GPT32_GTPR_OFFSET, 0xFFFFFFFF);
          gpt_putreg(lower, R_GPT32_GTCNT_OFFSET, 0);

          /* Re-enable write protection */

          gpt_putreg(lower, R_GPT32_GTWP_OFFSET,
                     GPT_GTWP_PRKEY | GPT_GTWP_WP | GPT_GTWP_CMNWP);

          lower->prescaler = 0;  /* Prescaler 1 */

          break;
        }
    }

  if (i >= NGPT_CONFIGS)
    {
      pwmerr("ERROR: No such timer configured: %d\n", channel);
      return NULL;
    }

  return (struct timer_lowerhalf_s *)lower;
}
#endif /* CONFIG_TIMER */

/****************************************************************************
 * Name: ra_gpt_set_trigger
 *
 * Description:
 *   Configure external trigger sources for the specified GPT channel.
 *   This allows ELC events to start, stop, clear, or count the timer.
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *   config  - Trigger configuration
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_set_trigger(int channel, const struct ra_gpt_trigger_s *config)
{
  struct ra_gpt_s *priv = NULL;
  int i;

  if (config == NULL)
    {
      return -EINVAL;
    }

  /* Find the matching device */

  for (i = 0; i < NGPT_CONFIGS; i++)
    {
      if (g_gpt_configs[i].channel == channel)
        {
          priv = &g_gpt_devs[i];
          break;
        }
    }

  if (priv == NULL || priv->config == NULL)
    {
      return -ENODEV;
    }

  return gpt_set_trigger(priv, config);
}

/****************************************************************************
 * Name: ra_gpt_set_capture
 *
 * Description:
 *   Configure input capture mode for the specified GPT channel.
 *   This enables capturing the counter value on external pin edges.
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *   config  - Capture configuration
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_set_capture(int channel, const struct ra_gpt_capture_s *config)
{
  struct ra_gpt_s *priv = NULL;
  int i;

  if (config == NULL)
    {
      return -EINVAL;
    }

  /* Find the matching device */

  for (i = 0; i < NGPT_CONFIGS; i++)
    {
      if (g_gpt_configs[i].channel == channel)
        {
          priv = &g_gpt_devs[i];
          break;
        }
    }

  if (priv == NULL || priv->config == NULL)
    {
      return -ENODEV;
    }

  return gpt_set_capture(priv, config);
}

/****************************************************************************
 * Name: ra_gpt_get_capture
 *
 * Description:
 *   Get the captured counter value from input capture mode.
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *   capture - Pointer to capture result structure
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_get_capture(int channel, struct ra_gpt_captured_s *capture)
{
  struct ra_gpt_s *priv = NULL;
  int i;

  if (capture == NULL)
    {
      return -EINVAL;
    }

  /* Find the matching device */

  for (i = 0; i < NGPT_CONFIGS; i++)
    {
      if (g_gpt_configs[i].channel == channel)
        {
          priv = &g_gpt_devs[i];
          break;
        }
    }

  if (priv == NULL || priv->config == NULL)
    {
      return -ENODEV;
    }

  return gpt_get_capture(priv, capture);
}

#ifdef CONFIG_RA_DMAC
/****************************************************************************
 * Name: ra_gpt_set_dma
 *
 * Description:
 *   Configure DMA for waveform generation on the specified GPT channel.
 *   This enables automatic duty cycle updates via DMA transfers.
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *   config  - DMA configuration
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_set_dma(int channel, const struct ra_gpt_dma_s *config)
{
  struct ra_gpt_s *priv = NULL;
  int i;

  if (config == NULL)
    {
      return -EINVAL;
    }

  /* Find the matching device */

  for (i = 0; i < NGPT_CONFIGS; i++)
    {
      if (g_gpt_configs[i].channel == channel)
        {
          priv = &g_gpt_devs[i];
          break;
        }
    }

  if (priv == NULL || priv->config == NULL)
    {
      return -ENODEV;
    }

  return gpt_set_dma(priv, config);
}
#endif /* CONFIG_RA_DMAC */

#endif /* CONFIG_RA_GPT */

/****************************************************************************
 * End of file
 ****************************************************************************/

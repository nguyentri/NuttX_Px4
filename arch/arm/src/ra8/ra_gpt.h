/****************************************************************************
 * arch/arm/src/ra8/ra_gpt.h
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

#ifndef __ARCH_ARM_SRC_RA_RA8_GPT_H
#define __ARCH_ARM_SRC_RA_RA8_GPT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/timers/pwm.h>
#include <nuttx/timers/timer.h>
#include "chip.h"
#include "hardware/ra_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Maximum number of GPT channels */
#define RA_GPT_NCHANNELS               14

/* GPT modes */
#define RA_GPT_MODE_TIMER              0   /* Timer mode */
#define RA_GPT_MODE_PWM                1   /* PWM mode */
#define RA_GPT_MODE_INPUT_CAPTURE      2   /* Input capture mode */

/* GPT timer modes */
#define RA_GPT_TIMER_PERIODIC          0   /* Periodic timer */
#define RA_GPT_TIMER_ONE_SHOT          1   /* One-shot timer */

/* GPT PWM output modes */
#define RA_GPT_PWM_SINGLE_OUTPUT       0   /* Single output (GTIOCA only) */
#define RA_GPT_PWM_COMPLEMENTARY       1   /* Complementary output (GTIOCA + GTIOCB) */
#define RA_GPT_PWM_INDEPENDENT         2   /* Independent outputs */

/* GPT interrupt sources */
#define RA_GPT_INT_OVERFLOW            (1 << 0)
#define RA_GPT_INT_UNDERFLOW           (1 << 1)
#define RA_GPT_INT_COMPARE_A           (1 << 2)
#define RA_GPT_INT_COMPARE_B           (1 << 3)
#define RA_GPT_INT_COMPARE_C           (1 << 4)
#define RA_GPT_INT_COMPARE_D           (1 << 5)

/**********************************************************************/

/* GTWP Register bit definitions */
#define GPT_GTWP_PRKEY                            (0xa500 << 8)  /* Write protect key */
#define GPT_GTWP_WP                               (1 << 0)       /* Write protection enable */
#define GPT_GTWP_CMNWP                            (1 << 4)       /* Common register write protect */

/* GTCR Register bit definitions */
#define GPT_GTCR_CST                              (1 << 0)       /* Count start */
#define GPT_GTCR_MD_SHIFT                         (1)            /* Count mode shift */
#define GPT_GTCR_MD_MASK                          (0x7 << GPT_GTCR_MD_SHIFT)
#define GPT_GTCR_MD_SAW_WAVE_UP                   (0 << GPT_GTCR_MD_SHIFT)
#define GPT_GTCR_MD_SAW_WAVE_DN                   (1 << GPT_GTCR_MD_SHIFT)
#define GPT_GTCR_MD_TRIANGULAR_WAVE               (2 << GPT_GTCR_MD_SHIFT)

#define GPT_GTCR_TPCS_SHIFT                       (4)            /* Timer prescaler shift */
#define GPT_GTCR_TPCS_MASK                        (0x7 << GPT_GTCR_TPCS_SHIFT)
#define GPT_GTCR_TPCS_PCLKD_1                     (0 << GPT_GTCR_TPCS_SHIFT) /* Prescaler = 1 */
#define GPT_GTCR_TPCS_PCLKD_4                     (1 << GPT_GTCR_TPCS_SHIFT) /* Prescaler = 4 */
#define GPT_GTCR_TPCS_PCLKD_16                    (2 << GPT_GTCR_TPCS_SHIFT) /* Prescaler = 16 */
#define GPT_GTCR_TPCS_PCLKD_64                    (3 << GPT_GTCR_TPCS_SHIFT) /* Prescaler = 64 */
#define GPT_GTCR_TPCS_PCLKD_256                   (4 << GPT_GTCR_TPCS_SHIFT) /* Prescaler = 256 */
#define GPT_GTCR_TPCS_PCLKD_1024                  (5 << GPT_GTCR_TPCS_SHIFT) /* Prescaler = 1024 */

/* GTIOR Register bit definitions */
#define GPT_GTIOR_GTIOA_SHIFT                     (0)
#define GPT_GTIOR_GTIOA_MASK                      (0xf << GPT_GTIOR_GTIOA_SHIFT)
#define GPT_GTIOR_GTIOA_INITIAL_LOW               (0 << GPT_GTIOR_GTIOA_SHIFT) /* Initial low, no change */
#define GPT_GTIOR_GTIOA_INITIAL_HIGH              (1 << GPT_GTIOR_GTIOA_SHIFT) /* Initial high, no change */
#define GPT_GTIOR_GTIOA_LOW_ON_CMP                (4 << GPT_GTIOR_GTIOA_SHIFT) /* Low on match, high on period */
#define GPT_GTIOR_GTIOA_HIGH_ON_CMP               (5 << GPT_GTIOR_GTIOA_SHIFT) /* High on match, low on period */

#define GPT_GTIOR_GTIOB_SHIFT                     (8)
#define GPT_GTIOR_GTIOB_MASK                      (0xf << GPT_GTIOR_GTIOB_SHIFT)
#define GPT_GTIOR_GTIOB_INITIAL_LOW               (0 << GPT_GTIOR_GTIOB_SHIFT) /* Initial low, no change */
#define GPT_GTIOR_GTIOB_INITIAL_HIGH              (1 << GPT_GTIOR_GTIOB_SHIFT) /* Initial high, no change */
#define GPT_GTIOR_GTIOB_LOW_ON_CMP                (4 << GPT_GTIOR_GTIOB_SHIFT) /* Low on match, high on period */
#define GPT_GTIOR_GTIOB_HIGH_ON_CMP               (5 << GPT_GTIOR_GTIOB_SHIFT) /* High on match, low on period */

/* GTBER Register bit definitions (Buffer Enable Register) */
#define GPT_GTBER_CCRA                            (1 << 16)
#define GPT_GTBER_CCRB                            (1 << 17)
#define GPT_GTBER_PR                              (1 << 18)

/* GTST Register bit definitions (Status Register) */
#define GPT_GTST_ADTRAUEN                         (1 << 16) /* A/D Start Request Active */
#define GPT_GTST_ADTRBUEN                         (1 << 17) /* A/D Start Request Active */
#define GPT_GTST_ADTRADEN                         (1 << 20) /* A/D Start Request Active */
#define GPT_GTST_ADTRBDEN                         (1 << 21) /* A/D Start Request Active */

/****************************************************************************
 * Public Types
 ****************************************************************************/


/* GPT Channel Configuration Structure */

struct ra_gpt_config_s
{
  uint32_t base;                   /* GPT peripheral base address */
  uint32_t pclkd_frequency;        /* PCLKD frequency in Hz */
  uint8_t  channel;                /* GPT channel (0-13) */
  uint8_t  irq;                    /* Interrupt request number */
};

/* GPT Device Structure */

struct ra_gpt_dev_s
{
  const struct ra_gpt_config_s *config;  /* GPT configuration */
  uint32_t frequency;                      /* PWM frequency */
  uint32_t period;                         /* PWM period in timer counts */
  bool started;                            /* PWM started flag */
};


/* GPT timer configuration */
struct ra_gpt_timer_config_s
{
  uint8_t  channel;                /* GPT channel number */
  uint8_t  mode;                   /* Timer mode (periodic/one-shot) */
  uint32_t frequency;              /* Timer frequency in Hz */
  uint32_t timeout_us;             /* Timeout in microseconds (for one-shot) */
  void     (*callback)(void *arg); /* Timer callback function */
  void     *arg;                   /* Callback argument */
};

/* GPT PWM configuration */
struct ra_gpt_pwm_config_s
{
  uint8_t  channel;                /* GPT channel number */
  uint8_t  output_mode;            /* PWM output mode */
  uint32_t frequency;              /* PWM frequency in Hz */
  uint32_t duty_a;                 /* Duty cycle for GTIOCA (0-65535) */
  uint32_t duty_b;                 /* Duty cycle for GTIOCB (0-65535) */
  bool     enable_deadtime;        /* Enable dead time control */
  uint16_t deadtime_up;            /* Dead time for rising edge */
  uint16_t deadtime_down;          /* Dead time for falling edge */
};

/* GPT channel configuration */
struct ra_gpt_channel_s
{
  uint8_t channel;                 /* GPT channel number (0-13) */
  uint8_t mode;                    /* GPT mode flags */
  uint32_t pin_a;                  /* GTIOA pin configuration */
  uint32_t pin_b;                  /* GTIOB pin configuration (for complementary mode) */
  uint16_t deadtime_up;            /* Dead time for rising edge (in timer counts) */
  uint16_t deadtime_down;          /* Dead time for falling edge (in timer counts) */
};

/* GPT driver configuration */
struct ra_gpt_driver_config_s
{
  uint8_t nchannels;               /* Number of GPT channels */
  const struct ra_gpt_channel_s *channels; /* GPT channel configurations */
  uint32_t base_frequency;         /* Base timer frequency in Hz */
  uint32_t default_frequency;      /* Default PWM frequency in Hz */
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifndef __ASSEMBLY__

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: ra_gpt_initialize
 *
 * Description:
 *   Initialize the GPT subsystem
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

struct pwm_lowerhalf_s *ra_gpt_initialize(int channel);

/****************************************************************************
 * Name: ra_gpt_pwm_setup
 *
 * Description:
 *   Initialize one PWM channel for the given GPT channel
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *
 * Returned Value:
 *   On success, a pointer to the RA GPT lower half PWM driver is returned.
 *   NULL is returned on any failure.
 *
 ****************************************************************************/

struct pwm_lowerhalf_s *ra_gpt_pwm_setup(int channel);

/****************************************************************************
 * Name: ra_gpt_timer_setup
 *
 * Description:
 *   Initialize one timer for the given GPT channel
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *
 * Returned Value:
 *   On success, a pointer to the RA GPT lower half timer driver is returned.
 *   NULL is returned on any failure.
 *
 ****************************************************************************/

struct timer_lowerhalf_s *ra_gpt_timer_setup(int channel);

/****************************************************************************
 * Name: ra_gpt_start
 *
 * Description:
 *   Start the specified GPT channel
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_start(int channel);

/****************************************************************************
 * Name: ra_gpt_stop
 *
 * Description:
 *   Stop the specified GPT channel
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_stop(int channel);

/****************************************************************************
 * Name: ra_gpt_pwm_config
 *
 * Description:
 *   Configure PWM parameters for the specified GPT channel
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *   config  - PWM configuration
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_pwm_config(int channel, const struct ra_gpt_pwm_config_s *config);

/****************************************************************************
 * Name: ra_gpt_timer_config
 *
 * Description:
 *   Configure timer parameters for the specified GPT channel
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *   config  - Timer configuration
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_timer_config(int channel, const struct ra_gpt_timer_config_s *config);

/****************************************************************************
 * Name: ra_gpt_get_counter
 *
 * Description:
 *   Get the current counter value for the specified GPT channel
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *
 * Returned Value:
 *   Current counter value, or 0 on error.
 *
 ****************************************************************************/

uint32_t ra_gpt_get_counter(int channel);

/****************************************************************************
 * Name: ra_gpt_set_period
 *
 * Description:
 *   Set the period for the specified GPT channel
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *   period  - Period value in timer counts
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_set_period(int channel, uint32_t period);

/****************************************************************************
 * Name: ra_gpt_set_compare
 *
 * Description:
 *   Set the compare value for the specified GPT channel and compare register
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *   compare - Compare register (0=A, 1=B, 2=C, 3=D)
 *   value   - Compare value in timer counts
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_set_compare(int channel, int compare, uint32_t value);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RA_RA8_GPT_H */

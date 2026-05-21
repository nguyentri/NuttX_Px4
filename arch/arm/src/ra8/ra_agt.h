/****************************************************************************
 * arch/arm/src/ra8/ra_agt.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_AGT_H
#define __ARCH_ARM_SRC_RA8_RA_AGT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>
#include <nuttx/irq.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* AGT register offsets */

#define RA_AGT_OFFSET         0x00  /* Counter register */
#define RA_AGTCMA_OFFSET      0x02  /* Compare match A */
#define RA_AGTCMB_OFFSET      0x04  /* Compare match B */
#define RA_AGTCR_OFFSET       0x08  /* Control register */
#define RA_AGTMR1_OFFSET      0x09  /* Mode register 1 */
#define RA_AGTMR2_OFFSET      0x0A  /* Mode register 2 */
#define RA_AGTIOC_OFFSET      0x0B  /* I/O control */
#define RA_AGTISR_OFFSET      0x0C  /* Event pin select */
#define RA_AGTCMSR_OFFSET     0x0D  /* Compare match function select */
#define RA_AGTIOSEL_OFFSET    0x0E  /* I/O pin select */

/* AGTCR - Control Register bits */

#define AGTCR_TSTART          (1 << 0)  /* Start bit */
#define AGTCR_TCSTF           (1 << 1)  /* Count status flag */
#define AGTCR_TSTOP           (1 << 2)  /* Force stop bit */
#define AGTCR_TUNDF           (1 << 5)  /* Underflow flag */
#define AGTCR_TCMAF           (1 << 6)  /* Compare match A flag */
#define AGTCR_TCMBF           (1 << 7)  /* Compare match B flag */

/* AGTCR commands */

#define AGTCR_START_CMD       0xF1      /* Start timer */
#define AGTCR_STOP_CMD        0xF0      /* Stop timer */

/* AGTMR1 - Mode Register 1 bits */

#define AGTMR1_TMOD_SHIFT     (0)       /* Operating mode */
#define AGTMR1_TMOD_MASK      (0x07 << AGTMR1_TMOD_SHIFT)
#define AGTMR1_TMOD_TIMER     (0x00 << AGTMR1_TMOD_SHIFT)
#define AGTMR1_TMOD_PULSE     (0x03 << AGTMR1_TMOD_SHIFT)
#define AGTMR1_TMOD_EVENT     (0x02 << AGTMR1_TMOD_SHIFT)

#define AGTMR1_TEDGPL         (1 << 3)  /* Edge polarity */
#define AGTMR1_TCK_SHIFT      (4)       /* Count source */
#define AGTMR1_TCK_MASK       (0x07 << AGTMR1_TCK_SHIFT)

#define AGTMR1_CKS_SHIFT      (7)       /* Clock divider */
#define AGTMR1_CKS_MASK       (0x07 << AGTMR1_CKS_SHIFT)

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* AGT clock sources */

enum ra_agt_clock_e
{
  RA_AGT_CLOCK_PCLKB      = 0x00,  /* PCLKB (default) */
  RA_AGT_CLOCK_LOCO       = 0x40,  /* Low-speed on-chip oscillator */
  RA_AGT_CLOCK_SUBCLOCK   = 0x60,  /* 32.768 kHz subclock */
  RA_AGT_CLOCK_AGTIO      = 0x80,  /* External event on AGTIO pin */
};

/* AGT operational mode */

enum ra_agt_mode_e
{
  RA_AGT_MODE_PERIODIC    = 0,     /* Continuous counting */
  RA_AGT_MODE_ONESHOT     = 1,     /* Stop after underflow */
};

/* AGT channel configuration (per-instance, board-defined) */

struct ra_agt_config_s
{
  uint8_t  channel;                /* AGT channel number (0-6) */
  uint32_t base;                   /* Register base address */
  enum ra_agt_clock_e clock;       /* Clock source */
  uint8_t  divider;                /* Clock divider (0=1, 1=2, 2=4, ..., 7=128) */
  bool     is_agtw;                /* true=32-bit AGTW, false=16-bit AGT */
  int      elc_int;                /* ELC event number for AGT interrupt */
};

/* AGT instance private data (opaque to upper layers) */

struct ra_agt_priv_s
{
  const struct ra_agt_config_s *config;  /* Hardware configuration */
  uint32_t period;                       /* Current period in counts */
  enum ra_agt_mode_e mode;               /* Current mode */
  xcpt_t   handler;                      /* ISR callback */
  void    *arg;                          /* Callback argument */
  int      irq;                          /* Assigned IRQ number */
  bool     started;                      /* Timer running state */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Name: ra_agt_initialize
 *
 * Description:
 *   Initialize AGT instance (does not start timer)
 *
 * Input Parameters:
 *   config - AGT configuration structure
 *
 * Returned Value:
 *   Pointer to private instance data, or NULL on error
 *
 ****************************************************************************/

struct ra_agt_priv_s *ra_agt_initialize(
    const struct ra_agt_config_s *config);

/****************************************************************************
 * Name: ra_agt_start
 *
 * Description:
 *   Start timer counting
 *
 * Input Parameters:
 *   priv - AGT private instance data
 *
 * Returned Value:
 *   OK on success, negative errno on error
 *
 ****************************************************************************/

int ra_agt_start(struct ra_agt_priv_s *priv);

/****************************************************************************
 * Name: ra_agt_stop
 *
 * Description:
 *   Stop timer
 *
 * Input Parameters:
 *   priv - AGT private instance data
 *
 * Returned Value:
 *   OK on success, negative errno on error
 *
 ****************************************************************************/

int ra_agt_stop(struct ra_agt_priv_s *priv);

/****************************************************************************
 * Name: ra_agt_setperiod
 *
 * Description:
 *   Set period in counts
 *
 * Input Parameters:
 *   priv   - AGT private instance data
 *   counts - Period value in timer counts
 *
 * Returned Value:
 *   OK on success, negative errno on error
 *
 ****************************************************************************/

int ra_agt_setperiod(struct ra_agt_priv_s *priv, uint32_t counts);

/****************************************************************************
 * Name: ra_agt_setmode
 *
 * Description:
 *   Set mode (periodic/oneshot)
 *
 * Input Parameters:
 *   priv - AGT private instance data
 *   mode - Operating mode
 *
 * Returned Value:
 *   OK on success, negative errno on error
 *
 ****************************************************************************/

int ra_agt_setmode(struct ra_agt_priv_s *priv, enum ra_agt_mode_e mode);

/****************************************************************************
 * Name: ra_agt_attach
 *
 * Description:
 *   Attach ISR callback
 *
 * Input Parameters:
 *   priv    - AGT private instance data
 *   handler - Interrupt handler function
 *   arg     - Argument to pass to handler
 *
 * Returned Value:
 *   OK on success, negative errno on error
 *
 ****************************************************************************/

int ra_agt_attach(struct ra_agt_priv_s *priv, xcpt_t handler, void *arg);

/****************************************************************************
 * Name: ra_agt_getcounter
 *
 * Description:
 *   Get current counter value
 *
 * Input Parameters:
 *   priv - AGT private instance data
 *
 * Returned Value:
 *   Current counter value
 *
 ****************************************************************************/

uint32_t ra_agt_getcounter(struct ra_agt_priv_s *priv);

/****************************************************************************
 * Name: ra_agt_getfrequency
 *
 * Description:
 *   Get timer frequency in Hz
 *
 * Input Parameters:
 *   priv - AGT private instance data
 *
 * Returned Value:
 *   Timer frequency in Hz
 *
 ****************************************************************************/

uint32_t ra_agt_getfrequency(struct ra_agt_priv_s *priv);

/****************************************************************************
 * Name: ra_agt_isrunning
 *
 * Description:
 *   Check if timer is running
 *
 * Input Parameters:
 *   priv - AGT private instance data
 *
 * Returned Value:
 *   true if running, false if stopped
 *
 ****************************************************************************/

bool ra_agt_isrunning(struct ra_agt_priv_s *priv);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RA8_RA_AGT_H */

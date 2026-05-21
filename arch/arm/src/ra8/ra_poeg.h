/****************************************************************************
 * arch/arm/src/ra8/ra_poeg.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_POEG_H
#define __ARCH_ARM_SRC_RA8_RA_POEG_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* POEG Channel Groups */

#define RA_POEG_CHANNEL_A    0  /* POEG Group A (GTETRGA) */
#define RA_POEG_CHANNEL_B    1  /* POEG Group B (GTETRGB) */
#define RA_POEG_CHANNEL_C    2  /* POEG Group C (GTETRGC) */
#define RA_POEG_CHANNEL_D    3  /* POEG Group D (GTETRGD) */

/* POEG Trigger Sources (can be OR'd together) */

#define RA_POEG_TRIGGER_SOFTWARE         0x00  /* Software trigger only */
#define RA_POEG_TRIGGER_PIN              0x01  /* GTETRG pin level */
#define RA_POEG_TRIGGER_GPT_OUTPUT       0x02  /* GPT output level detection */
#define RA_POEG_TRIGGER_OSCILLATION_STOP 0x04  /* Main oscillator stop */
#define RA_POEG_TRIGGER_ACMPHS0          0x10  /* ACMPHS0 comparator */
#define RA_POEG_TRIGGER_ACMPHS1          0x20  /* ACMPHS1 comparator */
#define RA_POEG_TRIGGER_ACMPHS2          0x40  /* ACMPHS2 comparator */
#define RA_POEG_TRIGGER_ACMPHS3          0x80  /* ACMPHS3 comparator */

/* POEG Pin Polarity */

#define RA_POEG_POLARITY_ACTIVE_HIGH     0  /* Disable when pin is HIGH */
#define RA_POEG_POLARITY_ACTIVE_LOW      1  /* Disable when pin is LOW */

/* POEG Noise Filter Settings */

#define RA_POEG_FILTER_DISABLED          0  /* No noise filter */
#define RA_POEG_FILTER_PCLKB_DIV_1       1  /* Sample at PCLKB/1 */
#define RA_POEG_FILTER_PCLKB_DIV_8       3  /* Sample at PCLKB/8 */
#define RA_POEG_FILTER_PCLKB_DIV_32      5  /* Sample at PCLKB/32 */
#define RA_POEG_FILTER_PCLKB_DIV_128     7  /* Sample at PCLKB/128 */

/* POEG Status Flags */

#define RA_POEG_STATUS_PIN_DETECT        0x00001  /* Pin detection flag */
#define RA_POEG_STATUS_GPT_DETECT        0x00002  /* GPT/ACMPHS detection flag */
#define RA_POEG_STATUS_OSC_STOP          0x00004  /* Oscillation stop flag */
#define RA_POEG_STATUS_SOFTWARE          0x00008  /* Software disable flag */
#define RA_POEG_STATUS_PIN_ACTIVE        0x10000  /* GTETRG pin is active */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* POEG callback function type */

typedef void (*poeg_callback_t)(uint8_t channel, uint32_t status, void *arg);

/* POEG configuration structure */

struct ra_poeg_config_s
{
  uint8_t channel;              /* POEG channel (0-3) */
  uint8_t trigger;              /* Trigger sources (OR'd RA_POEG_TRIGGER_*) */
  uint8_t polarity;             /* Pin polarity (RA_POEG_POLARITY_*) */
  uint8_t noise_filter;         /* Noise filter setting (RA_POEG_FILTER_*) */
  int     elc_event;            /* ELC event number for interrupt */
  uint8_t priority;             /* Interrupt priority (0-15) */
  poeg_callback_t callback;     /* Callback function */
  void   *arg;                  /* Callback argument */
};

/* POEG status structure */

struct ra_poeg_status_s
{
  uint32_t flags;               /* Status flags (RA_POEG_STATUS_*) */
  bool     disabled;            /* True if GPT outputs are disabled */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Name: ra_poeg_initialize
 *
 * Description:
 *   Initialize the POEG driver for a specific channel.
 *
 * Input Parameters:
 *   config - Pointer to POEG configuration structure
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_poeg_initialize(const struct ra_poeg_config_s *config);

/****************************************************************************
 * Name: ra_poeg_deinitialize
 *
 * Description:
 *   Deinitialize the POEG driver for a specific channel.
 *
 * Input Parameters:
 *   channel - POEG channel (0-3)
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_poeg_deinitialize(uint8_t channel);

/****************************************************************************
 * Name: ra_poeg_software_disable
 *
 * Description:
 *   Trigger software disable of GPT outputs.
 *
 * Input Parameters:
 *   channel - POEG channel (0-3)
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_poeg_software_disable(uint8_t channel);

/****************************************************************************
 * Name: ra_poeg_reset
 *
 * Description:
 *   Reset POEG status flags and re-enable GPT outputs (if trigger
 *   condition is resolved).
 *
 * Input Parameters:
 *   channel - POEG channel (0-3)
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_poeg_reset(uint8_t channel);

/****************************************************************************
 * Name: ra_poeg_get_status
 *
 * Description:
 *   Get the current POEG status.
 *
 * Input Parameters:
 *   channel - POEG channel (0-3)
 *   status  - Pointer to status structure to fill
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_poeg_get_status(uint8_t channel, struct ra_poeg_status_s *status);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RA8_RA_POEG_H */

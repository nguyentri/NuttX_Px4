/****************************************************************************
 * arch/arm/src/ra8/ra_ulpt.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_ULPT_H
#define __ARCH_ARM_SRC_RA8_RA_ULPT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Number of ULPT channels */

#define RA_ULPT_CHANNELS    2

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* ULPT clock source selection */

enum ra_ulpt_clock_e
{
  RA_ULPT_CLOCK_LOCO     = 0x00,  /* LOCO count source */
  RA_ULPT_CLOCK_SUBCLOCK = 0x20,  /* Subclock count source */
  RA_ULPT_CLOCK_ULPTEVI  = 0x02,  /* External event count */
};

/* ULPT clock divider selection */

enum ra_ulpt_divider_e
{
  RA_ULPT_DIV_1   = 0,    /* Divide by 1 */
  RA_ULPT_DIV_2   = 1,    /* Divide by 2 */
  RA_ULPT_DIV_4   = 2,    /* Divide by 4 */
  RA_ULPT_DIV_8   = 3,    /* Divide by 8 */
  RA_ULPT_DIV_16  = 4,    /* Divide by 16 */
  RA_ULPT_DIV_32  = 5,    /* Divide by 32 */
  RA_ULPT_DIV_64  = 6,    /* Divide by 64 */
  RA_ULPT_DIV_128 = 7,    /* Divide by 128 */
};

/* ULPT callback type */

typedef void (*ra_ulpt_callback_t)(int channel, void *arg);

/* ULPT configuration structure */

struct ra_ulpt_config_s
{
  uint8_t channel;                    /* ULPT channel (0 or 1) */
  enum ra_ulpt_clock_e clock;         /* Clock source */
  enum ra_ulpt_divider_e divider;     /* Clock divider */
  uint32_t period;                    /* Timer period in counts */
  bool low_power_mode;                /* Enable low power mode */
  bool compare_a_enable;              /* Enable compare match A */
  bool compare_b_enable;              /* Enable compare match B */
  uint32_t compare_a;                 /* Compare match A value */
  uint32_t compare_b;                 /* Compare match B value */
  ra_ulpt_callback_t callback;        /* Underflow/compare callback */
  void *callback_arg;                 /* Callback argument */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Name: ra_ulpt_initialize
 *
 * Description:
 *   Initialize a ULPT channel
 *
 * Input Parameters:
 *   config - Pointer to configuration structure
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ulpt_initialize(FAR const struct ra_ulpt_config_s *config);

/****************************************************************************
 * Name: ra_ulpt_start
 *
 * Description:
 *   Start the ULPT timer
 *
 * Input Parameters:
 *   channel - ULPT channel number (0 or 1)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ulpt_start(int channel);

/****************************************************************************
 * Name: ra_ulpt_stop
 *
 * Description:
 *   Stop the ULPT timer
 *
 * Input Parameters:
 *   channel - ULPT channel number (0 or 1)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ulpt_stop(int channel);

/****************************************************************************
 * Name: ra_ulpt_reset
 *
 * Description:
 *   Reset the ULPT counter to the period value
 *
 * Input Parameters:
 *   channel - ULPT channel number (0 or 1)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ulpt_reset(int channel);

/****************************************************************************
 * Name: ra_ulpt_set_period
 *
 * Description:
 *   Set the timer period
 *
 * Input Parameters:
 *   channel - ULPT channel number (0 or 1)
 *   period  - New period value in timer counts
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ulpt_set_period(int channel, uint32_t period);

/****************************************************************************
 * Name: ra_ulpt_get_count
 *
 * Description:
 *   Get the current counter value
 *
 * Input Parameters:
 *   channel - ULPT channel number (0 or 1)
 *
 * Returned Value:
 *   Current counter value
 *
 ****************************************************************************/

uint32_t ra_ulpt_get_count(int channel);

/****************************************************************************
 * Name: ra_ulpt_set_callback
 *
 * Description:
 *   Set the timer callback function
 *
 * Input Parameters:
 *   channel  - ULPT channel number (0 or 1)
 *   callback - Callback function pointer
 *   arg      - Callback argument
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ulpt_set_callback(int channel, ra_ulpt_callback_t callback,
                         void *arg);

/****************************************************************************
 * Name: ra_ulpt_deinitialize
 *
 * Description:
 *   De-initialize the ULPT channel
 *
 * Input Parameters:
 *   channel - ULPT channel number (0 or 1)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ulpt_deinitialize(int channel);

/****************************************************************************
 * Name: ra_ulpt_setup_lpm_wakeup
 *
 * Description:
 *   Configure ULPT as a wake-up source for low power modes
 *
 * Input Parameters:
 *   channel    - ULPT channel number (0 or 1)
 *   timeout_ms - Wake-up timeout in milliseconds
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ulpt_setup_lpm_wakeup(int channel, uint32_t timeout_ms);

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RA8_RA_ULPT_H */

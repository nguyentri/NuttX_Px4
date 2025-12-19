/****************************************************************************
 * arch/arm/src/rzv/rzv_gtm.h
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

#ifndef __ARCH_ARM_SRC_RZV_RZV_GTM_H
#define __ARCH_ARM_SRC_RZV_RZV_GTM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Default clock frequency for GTM (200 MHz typical for RZV2H) */
#ifndef CONFIG_RZV_GTM_CLOCK_FREQUENCY
#  define CONFIG_RZV_GTM_CLOCK_FREQUENCY  200000000
#endif

/****************************************************************************
 * Public Types
 ****************************************************************************/

#ifndef __ASSEMBLY__

struct timer_lowerhalf_s;

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_gtm_timer_initialize
 *
 * Description:
 *   Initialize GTM timer for use as NuttX timer device.
 *   Returns timer_lowerhalf_s interface for registration with timer_register().
 *
 * Input Parameters:
 *   channel - GTM channel number (0-7)
 *
 * Returned Value:
 *   Pointer to timer_lowerhalf_s on success, NULL on failure
 *
 ****************************************************************************/

FAR struct timer_lowerhalf_s *rzv_gtm_timer_initialize(int channel);

/****************************************************************************
 * Name: rzv_gtm_get_frequency
 *
 * Description:
 *   Get the clock frequency for a GTM channel in Hz.
 *
 * Input Parameters:
 *   channel - GTM channel number (0-7)
 *
 * Returned Value:
 *   Clock frequency in Hz, or 0 on error
 *
 ****************************************************************************/

uint32_t rzv_gtm_get_frequency(int channel);

#endif /* __ASSEMBLY__ */

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RZV_RZV_GTM_H */


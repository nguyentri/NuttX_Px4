/****************************************************************************
 * arch/arm/src/rzv/rzv_wdt.h
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

#ifndef __ARCH_ARM_SRC_RZV_RZV_WDT_H
#define __ARCH_ARM_SRC_RZV_RZV_WDT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/timers/watchdog.h>

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
 * Name: rzv_wdt_initialize
 *
 * Description:
 *   Initialize the WDT watchdog timer. The watchdog timer is initialized and
 *   registered as 'devpath'. The initial state of the watchdog timer is
 *   disabled.
 *
 * Input Parameters:
 *   devpath - The full path to the watchdog. This should be of the form
 *             /dev/watchdog0
 *   channel - The WDT channel number (0..RZV_WDT_MAX_CHANNELS-1)
 *             Channel 0: CR8_0 domain (typically used for RT control)
 *             Channel 1: CR8_1 domain
 *             Channel 2: CM33 domain
 *             Channel 3: CA55 domain
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is returned on
 *   any failure.
 *
 ****************************************************************************/

int rzv_wdt_initialize(FAR const char *devpath, int channel);

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RZV_RZV_WDT_H */

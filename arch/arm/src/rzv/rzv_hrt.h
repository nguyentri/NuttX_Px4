/****************************************************************************
 * arch/arm/src/rzv/rzv_hrt.h
 *
 * PX4 High-Resolution Timer (HRT) shim for RZ/V2H.
 *
 * Back-end: GTM7 in free-running mode (P1CLK = 100 MHz → 10 ns resolution,
 * 42.9 s wrap).  Channel GTM7 is chosen as the HRT-dedicated channel;
 * GTM0-6 remain available for NuttX timer devices / tick.
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

#ifndef __ARCH_ARM_SRC_RZV_RZV_HRT_H
#define __ARCH_ARM_SRC_RZV_RZV_HRT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>

#ifdef CONFIG_RZV_HRT

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GTM channel dedicated to HRT — must not overlap with tick or timer
 * devices.  GTM7 is reserved; GTM0-6 are available for other uses.
 */

#define RZV_HRT_GTM_CHANNEL   7

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* HRT callback type: called from ISR context, must be brief (<2 µs) */

typedef void (*rzv_hrt_callback_t)(void *arg);

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_hrt_initialize
 *
 * Description:
 *   Initialize the HRT subsystem.  Must be called once before any other
 *   rzv_hrt_* functions.  Starts GTM7 in free-running mode.
 *
 * Returned Value:
 *   0 on success, negative errno on failure.
 *
 ****************************************************************************/

int rzv_hrt_initialize(void);

/****************************************************************************
 * Name: rzv_hrt_absolute_time
 *
 * Description:
 *   Return the current HRT time in microseconds (monotonic, wraps at
 *   ~42.9 s due to 32-bit counter @ P1CLK = 100 MHz).
 *
 * Returned Value:
 *   Current HRT time in microseconds.
 *
 ****************************************************************************/

uint64_t rzv_hrt_absolute_time(void);

/****************************************************************************
 * Name: rzv_hrt_call_after
 *
 * Description:
 *   Schedule a one-shot callback after 'delay_us' microseconds.
 *   Replaces any pending one-shot call.
 *
 * Input Parameters:
 *   delay_us - Delay in microseconds (must be >= 1, <= ~42.9e9)
 *   callback - Function to call from ISR context
 *   arg      - Opaque argument passed to callback
 *
 * Returned Value:
 *   0 on success, -ERANGE if delay exceeds 32-bit counter capacity,
 *   -EINVAL on invalid parameters.
 *
 ****************************************************************************/

int rzv_hrt_call_after(uint32_t delay_us, rzv_hrt_callback_t callback,
                       void *arg);

/****************************************************************************
 * Name: rzv_hrt_call_every
 *
 * Description:
 *   Schedule a periodic callback every 'period_us' microseconds.
 *   Uses interval mode (GTM auto-reload).  Replaces any pending call.
 *
 * Input Parameters:
 *   period_us - Period in microseconds (must be >= 1)
 *   callback  - Function to call from ISR context each period
 *   arg       - Opaque argument passed to callback
 *
 * Returned Value:
 *   0 on success, -ERANGE, -EINVAL on error.
 *
 ****************************************************************************/

int rzv_hrt_call_every(uint32_t period_us, rzv_hrt_callback_t callback,
                       void *arg);

/****************************************************************************
 * Name: rzv_hrt_cancel
 *
 * Description:
 *   Cancel any pending one-shot or periodic HRT call.
 *   Stops the HRT GTM channel.
 *
 ****************************************************************************/

void rzv_hrt_cancel(void);

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_RZV_HRT */

#endif /* __ARCH_ARM_SRC_RZV_RZV_HRT_H */

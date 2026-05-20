/****************************************************************************
 * arch/arm/src/rzv/rzv_canfd.h
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

/* Public API for the RZ/V2H CAN-FD lower-half driver.
 *
 * Board-level code (e.g. boards/arm/rzv/rdk-rzv2h/src/rzv2h_canfd.c) calls:
 *   rzv_canfd_initialize(channel)  — clock + reset + peripheral init
 *   rzv_canfd_register(devpath, channel) — register /dev/canN
 *
 * Mirrors arch/arm/src/ra8/ra_canfd.h interface.
 */

#ifndef __ARCH_ARM_SRC_RZV_RZV_CANFD_H
#define __ARCH_ARM_SRC_RZV_RZV_CANFD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>
#include <nuttx/can/can.h>

#ifdef CONFIG_RZV_CANFD

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Maximum number of CAN-FD channels on RZ/V2H (hardware supports 6) */

#define RZV_CANFD_NUM_CHANNELS        2   /* v1: CH0 + CH1 framework */

/* Maximum data length for CAN-FD frames */

#define RZV_CANFD_MAX_DATA_LENGTH     64

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Name: rzv_canfd_initialize
 *
 * Description:
 *   Initialize the CAN-FD peripheral for the given channel.  Enables CPG
 *   clock gate and releases module reset.  Performs one-time global IP
 *   initialization on first call.
 *
 * Input Parameters:
 *   channel - CAN-FD channel number (0 or 1)
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/

int rzv_canfd_initialize(int channel);

/****************************************************************************
 * Name: rzv_canfd_register
 *
 * Description:
 *   Register the CAN-FD character device via the NuttX CAN upper half.
 *   Calls rzv_canfd_initialize() internally if not already done.
 *
 * Input Parameters:
 *   devpath - Device node path (e.g. "/dev/can0")
 *   channel - CAN-FD channel number (0 or 1)
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/

int rzv_canfd_register(const char *devpath, int channel);

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_RZV_CANFD */

#endif /* __ARCH_ARM_SRC_RZV_RZV_CANFD_H */

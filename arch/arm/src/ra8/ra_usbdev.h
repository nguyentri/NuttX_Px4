/****************************************************************************
 * arch/arm/src/ra8/ra_usbdev.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_USBDEV_H
#define __ARCH_ARM_SRC_RA8_RA_USBDEV_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/usb/usbdev.h>

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Name: ra_usbdev_initialize
 *
 * Description:
 *   Initialize the USB device controller hardware and driver.
 *   This function must be called before any USB class driver is initialized.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

void ra_usbdev_initialize(void);

/****************************************************************************
 * Name: ra_usbdev_uninitialize
 *
 * Description:
 *   Uninitialize the USB device controller and release resources.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

void ra_usbdev_uninitialize(void);

/****************************************************************************
 * Name: ra_usbdev_connected
 *
 * Description:
 *   Check if USB device is connected and configured.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   true if connected and configured, false otherwise
 *
 ****************************************************************************/

bool ra_usbdev_connected(void);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RA8_RA_USBDEV_H */

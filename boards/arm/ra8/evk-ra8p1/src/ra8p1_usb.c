/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_usb.c
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

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <debug.h>

#include <nuttx/usb/usbdev.h>
#include <nuttx/usb/usbdev_trace.h>

#include "chip.h"
#include "arm_internal.h"
#include "ra_gpio.h"
#include "ra8_usbdev.h"

#ifdef CONFIG_RA_USBDEV

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra8p1_usb_initialize
 *
 * Description:
 *   Initialize USB device hardware for EVK-RA8P1 board
 *
 ****************************************************************************/

int ra8p1_usb_initialize(void)
{
  uinfo("Initializing USB for EVK-RA8P1\n");

  /* USB pins are dedicated function - no GPIO configuration needed */
  /* P411: USB_DM, P410: USB_DP, P407: USB_VBUS */

  /* Initialize the USB device controller hardware */

  ra_usbdev_initialize();

  return OK;
}

/****************************************************************************
 * Name: ra8p1_usbpullup
 *
 * Description:
 *   Enable/disable USB D+ pullup resistor (called by upper layers)
 *
 ****************************************************************************/

int ra8p1_usbpullup(struct usbdev_s *dev, bool enable)
{
  uinfo("USB pullup: %s\n", enable ? "enabled" : "disabled");

  /* Pullup control is handled by the driver via SYSCFG.DPRPU */

  return OK;
}

/****************************************************************************
 * Name: ra8p1_usbsuspend
 *
 * Description:
 *   Board logic must provide the ra8p1_usbsuspend logic if USB suspend is
 *   supported.  This function is called whenever the USB enters or leaves
 *   suspend mode. This is an opportunity for the board logic to shutdown
 *   clocks, power, etc. while the USB is suspended.
 *
 ****************************************************************************/

void ra8p1_usbsuspend(struct usbdev_s *dev, bool resume)
{
  uinfo("USB %s\n", resume ? "resume" : "suspend");

  if (resume)
    {
      /* Resume from suspend - restore clocks/power if needed */
    }
  else
    {
      /* Enter suspend - reduce power if possible */
    }
}

#endif /* CONFIG_RA_USBDEV */

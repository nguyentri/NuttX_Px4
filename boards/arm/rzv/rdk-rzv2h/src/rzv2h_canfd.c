/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_canfd.c
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

/* Board-level CAN-FD glue for RDK-RZV2H.
 *
 * Mirrors the pattern of rzv2h_ether.c: configure GPIO pins then delegate
 * to the arch driver via rzv_canfd_register().
 *
 * v1 scope: CH0 only (/dev/can0).  CH1 pin macros are defined in board.h
 * but the CH1 init block below is compiled-out until CONFIG_RZV_CANFD1=y.
 *
 * Internal loopback at boot is the driver default (set in rzv_canfd.c
 * rzv_canfd_initialize); no board-level knob is needed here.
 */

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_CANFD

#include <errno.h>
#include <debug.h>
#include <syslog.h>

#include "rzv_gpio.h"
#include "rzv_canfd.h"
#include <arch/board/board.h>
#include "rdk-rzv2h.h"

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_canfd0_pins_setup
 *
 * Description:
 *   Configure GPIO pins for CAN-FD channel 0.
 *   P80 (PORT8 pin 0) → CTX0 (CAN1_TXD on RDK), PSEL=5
 *   P81 (PORT8 pin 1) → CRX0 (CAN1_RXD on RDK), PSEL=5
 *
 ****************************************************************************/

static void rzv2h_canfd0_pins_setup(void)
{
  rzv_gpioconfig(BOARD_CANFD0_TX_GPIO);
  rzv_gpioconfig(BOARD_CANFD0_RX_GPIO);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_canfd_initialize
 *
 * Description:
 *   Configure CAN-FD GPIO pins and register CAN-FD character device(s).
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/

int board_canfd_initialize(void)
{
  int ret = OK;

#ifdef CONFIG_RZV_CANFD0
  /* Configure CH0 GPIO pins (P80=TX, P81=RX) */

  rzv2h_canfd0_pins_setup();

  /* Register /dev/can0 via the arch lower-half driver */

  ret = rzv_canfd_register("/dev/can0", 0);
  if (ret < 0)
    {
      canerr("ERROR: rzv_canfd_register(\"/dev/can0\", 0) failed: %d\n",
             ret);
      return ret;
    }

  syslog(LOG_INFO, "CAN-FD CH0 registered as /dev/can0 (internal loopback)\n");
#endif /* CONFIG_RZV_CANFD0 */

  /* CH1 is not registered at v1. Pin macros BOARD_CANFD1_TX_GPIO /
   * BOARD_CANFD1_RX_GPIO (P86/P87) are defined in board.h for future use.
   * Enable CONFIG_RZV_CANFD1 and add the CH1 block here once CH0
   * hardware-validates on the RDK board.
   */

  return ret;
}

#endif /* CONFIG_RZV_CANFD */

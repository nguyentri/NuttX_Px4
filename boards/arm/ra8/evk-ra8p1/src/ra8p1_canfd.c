/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_canfd.c
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

#include <errno.h>
#include <debug.h>

#include <nuttx/can/can.h>

#include "ra_canfd.h"
#include "ra_gpio.h"

#include "arm_internal.h"
#include <arch/board/board.h>
#include "evk-ra8p1.h"

#ifdef CONFIG_RA_CANFD

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_canfd_initialize
 *
 * Description:
 *   Initialize CAN-FD interfaces for the EVK-RA8P1 board.
 *
 *   This function:
 *   1. Enables CANFD module clock
 *   2. Configures GPIO pins for CAN TX/RX
 *   3. Initializes the CANFD driver
 *   4. Registers the device nodes
 *
 ****************************************************************************/

int board_canfd_initialize(void)
{
  int ret;

  caninfo("Initializing CANFD\n");

#ifdef CONFIG_RA_CANFD0
  /* Configure CAN0 pins */
  ra_gpioconfig(GPIO_CANFD0_RX);
  ra_gpioconfig(GPIO_CANFD0_TX);

  /* Initialize CAN0 */
  ret = ra_canfd_register("/dev/can0", 0);
  if (ret < 0)
    {
      canerr("ERROR: CAN0 initialization failed: %d\n", ret);
      return ret;
    }

  caninfo("CAN0 initialized\n");
#endif

#ifdef CONFIG_RA_CANFD1
  /* Configure CAN1 pins */
  ra_gpioconfig(GPIO_CANFD1_RX);
  ra_gpioconfig(GPIO_CANFD1_TX);

  /* Initialize CAN1 */
  ret = ra_canfd_register("/dev/can1", 1);
  if (ret < 0)
    {
      canerr("ERROR: CAN1 initialization failed: %d\n", ret);
      return ret;
    }

  caninfo("CAN1 initialized\n");
#endif

  return OK;
}

#endif /* CONFIG_RA_CANFD */

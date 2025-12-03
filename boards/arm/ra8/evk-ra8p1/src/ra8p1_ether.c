/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_ether.c
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

#include <stdint.h>
#include <stdbool.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/board.h>
#include <arch/board/board.h>

#include "arm_internal.h"
#include "ra_gpio.h"
#include "ra_ether.h"
#include "evk-ra8p1.h"

#ifdef CONFIG_RA_ETHERNET

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/



/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: arm_netinitialize
 *
 * Description:
 *   Initialize the Ethernet driver for the board.
 *
 ****************************************************************************/

void arm_netinitialize(void)
{
  int ret;

  /* Configure Pins */
  ra_gpioconfig(GPIO_ETH_MDC);
  ra_gpioconfig(GPIO_ETH_MDIO);
  ra_gpioconfig(GPIO_ETH_RSTN);
  ra_gpioconfig(GPIO_ETH_INT);

  ra_gpioconfig(GPIO_ETH_TXD0);
  ra_gpioconfig(GPIO_ETH_TXD1);
  ra_gpioconfig(GPIO_ETH_TXD2);
  ra_gpioconfig(GPIO_ETH_TXD3);
  ra_gpioconfig(GPIO_ETH_TX_CTL);
  ra_gpioconfig(GPIO_ETH_TX_CLK);

  ra_gpioconfig(GPIO_ETH_RXD0);
  ra_gpioconfig(GPIO_ETH_RXD1);
  ra_gpioconfig(GPIO_ETH_RXD2);
  ra_gpioconfig(GPIO_ETH_RXD3);
  ra_gpioconfig(GPIO_ETH_RX_CTL);
  ra_gpioconfig(GPIO_ETH_RX_CLK);

  /* Reset PHY */
  ra_gpioconfig(GPIO_ETH_RSTN);
  ra_gpiowrite(GPIO_ETH_RSTN, 0);
  up_mdelay(10);
  ra_gpiowrite(GPIO_ETH_RSTN, 1);
  up_mdelay(10);

  /* Initialize the driver */
  ret = ra_ether_initialize(0);
  if (ret < 0)
    {
      nerr("ra_ether_initialize failed: %d\n", ret);
    }
}

#endif /* CONFIG_RA_ETHERNET */

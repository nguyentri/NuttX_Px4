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
#include "ra_ether_phy.h"
#include "evk-ra8p1.h"

#ifdef CONFIG_RA_ETHERNET

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* PHY Address - EK-RA8P1 EVK uses PHY address 0 */

#ifndef CONFIG_RA_ETHERNET_PHY_ADDRESS
#  define CONFIG_RA_ETHERNET_PHY_ADDRESS 0
#endif

/* PHY Reset timing (in milliseconds) */

#define PHY_RESET_ASSERT_TIME_MS   10
#define PHY_RESET_DEASSERT_TIME_MS 50

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Board-specific PHY configuration for EK-RA8P1 EVK */

static const struct ra_ether_phy_config_s g_phy_config =
{
  .phy_address = CONFIG_RA_ETHERNET_PHY_ADDRESS,
#ifdef CONFIG_RA_ETHERNET_PHY_GPY111
  .phy_type    = RA_PHY_TYPE_GPY111,
#elif defined(CONFIG_RA_ETHERNET_PHY_KSZ8091RNB)
  .phy_type    = RA_PHY_TYPE_KSZ8091RNB,
#elif defined(CONFIG_RA_ETHERNET_PHY_KSZ8041)
  .phy_type    = RA_PHY_TYPE_KSZ8041,
#elif defined(CONFIG_RA_ETHERNET_PHY_DP83620)
  .phy_type    = RA_PHY_TYPE_DP83620,
#elif defined(CONFIG_RA_ETHERNET_PHY_ICS1894)
  .phy_type    = RA_PHY_TYPE_ICS1894,
#else
  .phy_type    = RA_PHY_TYPE_GPY111,  /* Default for RA8P1 EVK */
#endif
#ifdef CONFIG_RA_ETHERNET_PHY_AUTONEG
  .autoneg     = true,
#else
  .autoneg     = false,
#endif
#ifdef CONFIG_RA_ETHERNET_PHY_SPEED_100
  .speed_100   = true,
#else
  .speed_100   = false,
#endif
#ifdef CONFIG_RA_ETHERNET_PHY_FULLDUPLEX
  .full_duplex = true,
#else
  .full_duplex = false,
#endif
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra8p1_phy_reset
 *
 * Description:
 *   Reset the PHY using the hardware reset pin.
 *
 ****************************************************************************/

static void ra8p1_phy_reset(void)
{
  /* Assert reset (active low) */

  ra_gpiowrite(GPIO_ETH_RSTN, 0);
  up_mdelay(PHY_RESET_ASSERT_TIME_MS);

  /* Deassert reset */

  ra_gpiowrite(GPIO_ETH_RSTN, 1);
  up_mdelay(PHY_RESET_DEASSERT_TIME_MS);

  ninfo("PHY hardware reset complete\n");
}

/****************************************************************************
 * Name: ra8p1_configure_eth_pins
 *
 * Description:
 *   Configure GPIO pins for Ethernet RGMII interface.
 *
 ****************************************************************************/

static void ra8p1_configure_eth_pins(void)
{
  /* Configure MDIO interface pins */

  ra_gpioconfig(GPIO_ETH_MDC);
  ra_gpioconfig(GPIO_ETH_MDIO);

  /* Configure PHY control pins */

  ra_gpioconfig(GPIO_ETH_RSTN);
  ra_gpioconfig(GPIO_ETH_INT);

  /* Configure RGMII transmit interface */

  ra_gpioconfig(GPIO_ETH_TXD0);
  ra_gpioconfig(GPIO_ETH_TXD1);
  ra_gpioconfig(GPIO_ETH_TXD2);
  ra_gpioconfig(GPIO_ETH_TXD3);
  ra_gpioconfig(GPIO_ETH_TX_CTL);
  ra_gpioconfig(GPIO_ETH_TX_CLK);

  /* Configure RGMII receive interface */

  ra_gpioconfig(GPIO_ETH_RXD0);
  ra_gpioconfig(GPIO_ETH_RXD1);
  ra_gpioconfig(GPIO_ETH_RXD2);
  ra_gpioconfig(GPIO_ETH_RXD3);
  ra_gpioconfig(GPIO_ETH_RX_CTL);
  ra_gpioconfig(GPIO_ETH_RX_CLK);

  ninfo("Ethernet GPIO pins configured\n");
}

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

  ninfo("Initializing Ethernet for EK-RA8P1\n");

  /* Configure GPIO pins for Ethernet */

  ra8p1_configure_eth_pins();

  /* Hardware reset the PHY */

  ra8p1_phy_reset();

  /* Initialize the Ethernet driver with board-specific PHY config */

  ret = ra_ether_initialize(0);
  if (ret < 0)
    {
      nerr("ERROR: ra_ether_initialize failed: %d\n", ret);
      return;
    }

  ninfo("Ethernet initialization complete\n");
}

/****************************************************************************
 * Name: board_phy_config
 *
 * Description:
 *   Get the board-specific PHY configuration.
 *
 * Input Parameters:
 *   intf - Interface number (0 or 1)
 *
 * Returned Value:
 *   Pointer to the PHY configuration structure, or NULL if invalid.
 *
 ****************************************************************************/

const struct ra_ether_phy_config_s *board_phy_config(int intf)
{
  if (intf == 0)
    {
      return &g_phy_config;
    }

  return NULL;
}

#endif /* CONFIG_RA_ETHERNET */

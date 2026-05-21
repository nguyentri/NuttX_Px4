/****************************************************************************
 * arch/arm/src/ra8/ra_ether_phy_ksz8041.c
 *
 * Microchip KSZ8041 10/100 PHY Driver
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
 * KSZ8041 is a 10/100 Mbps Ethernet PHY from Microchip.
 *
 * Features:
 *   - 10/100 Mbps operation
 *   - MII/RMII interface
 *   - HP Auto MDI/MDI-X
 *
 * Reference: FSP r_rmac_phy_target_ksz8041.c
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <debug.h>

#include "ra_ether_phy.h"

#ifdef CONFIG_RA_ETHERNET

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* KSZ8041 Vendor-Specific Registers */

#define KSZ8041_REG_PHYCTRL1            0x1E   /* PHY Control 1 */

/* PHY Control 1 LED Mode bits */

#define KSZ8041_LED_MODE_MASK           0xC000
#define KSZ8041_LED_MODE_LINK_ACT       0x4000 /* LED0=Link, LED1=Activity */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_phy_ksz8041_init
 *
 * Description:
 *   KSZ8041-specific initialization.
 *   Configures LED mode.
 *
 * Input Parameters:
 *   priv - PHY control block
 *
 ****************************************************************************/

void ra_phy_ksz8041_init(struct ra_phy_ctrl_s *priv)
{
  uint16_t regval;
  int ret;

  ninfo("KSZ8041 initialization\n");

  /* Read PHY Control 1 register */

  ret = ra_phy_reg_read(priv, KSZ8041_REG_PHYCTRL1, &regval);
  if (ret < 0)
    {
      nwarn("Failed to read PHYCTRL1: %d\n", ret);
      return;
    }

  /* Configure LED mode:
   * By default the LINK pin is combined with ACTIVITY.
   * Change so LED0 shows only LINK status and LED1 shows ACTIVITY.
   */

  regval &= ~KSZ8041_LED_MODE_MASK;
  regval |= KSZ8041_LED_MODE_LINK_ACT;

  ret = ra_phy_reg_write(priv, KSZ8041_REG_PHYCTRL1, regval);
  if (ret < 0)
    {
      nwarn("Failed to write PHYCTRL1: %d\n", ret);
    }

  ninfo("KSZ8041 configured\n");
}

/****************************************************************************
 * Name: ra_phy_ksz8041_supports_mode
 *
 * Description:
 *   Check if KSZ8041 supports a given speed/duplex mode.
 *   This is a 10/100 PHY - does not support Gigabit.
 *
 * Input Parameters:
 *   priv - PHY control block
 *   mode - Speed/duplex mode to check
 *
 * Returned Value:
 *   true if supported, false otherwise.
 *
 ****************************************************************************/

bool ra_phy_ksz8041_supports_mode(struct ra_phy_ctrl_s *priv,
                                  phy_link_speed_duplex_t mode)
{
  (void)priv;

  /* KSZ8041 supports 10/100 Mbps only */

  switch (mode)
    {
    case PHY_LINK_SPEED_DUPLEX_10HD:
    case PHY_LINK_SPEED_DUPLEX_10FD:
    case PHY_LINK_SPEED_DUPLEX_100HD:
    case PHY_LINK_SPEED_DUPLEX_100FD:
      return true;

    case PHY_LINK_SPEED_DUPLEX_1000HD:
    case PHY_LINK_SPEED_DUPLEX_1000FD:
    default:
      return false;  /* No Gigabit support */
    }
}

#endif /* CONFIG_RA_ETHERNET */


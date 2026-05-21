/****************************************************************************
 * arch/arm/src/ra8/ra_ether_phy_ics1894.c
 *
 * Renesas ICS1894 10/100 PHY Driver
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
 * ICS1894 is a 10/100 Mbps Ethernet PHY from Renesas.
 *
 * Features:
 *   - 10/100 Mbps operation
 *   - MII/RMII interface
 *   - Full duplex only (half duplex not supported)
 *
 * Reference: FSP r_rmac_phy_target_ics1894.c
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

/* ICS1894 Vendor-Specific Registers */

#define ICS1894_REG_PHYCTRL20           0x14   /* PHY Control 20 */

/* PHY Control 20 LED configuration bits */

#define ICS1894_PHYCTRL20_LED_CFG       0x0007 /* LED configuration mask */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_phy_ics1894_init
 *
 * Description:
 *   ICS1894-specific initialization.
 *   Configures LED mode.
 *
 * Input Parameters:
 *   priv - PHY control block
 *
 ****************************************************************************/

void ra_phy_ics1894_init(struct ra_phy_ctrl_s *priv)
{
  uint16_t regval;
  int ret;

  ninfo("ICS1894 initialization\n");

  /* Read PHY Control 20 register */

  ret = ra_phy_reg_read(priv, ICS1894_REG_PHYCTRL20, &regval);
  if (ret < 0)
    {
      nwarn("Failed to read PHYCTRL20: %d\n", ret);
      return;
    }

  /* Configure LED mode:
   * By default LINK pin is combined with ACTIVITY.
   * Change so LINK status is shown separately.
   */

  regval |= ICS1894_PHYCTRL20_LED_CFG;

  ret = ra_phy_reg_write(priv, ICS1894_REG_PHYCTRL20, regval);
  if (ret < 0)
    {
      nwarn("Failed to write PHYCTRL20: %d\n", ret);
    }

  ninfo("ICS1894 configured\n");
}

/****************************************************************************
 * Name: ra_phy_ics1894_supports_mode
 *
 * Description:
 *   Check if ICS1894 supports a given speed/duplex mode.
 *   This PHY only supports FULL DUPLEX mode (no half duplex).
 *
 * Input Parameters:
 *   priv - PHY control block
 *   mode - Speed/duplex mode to check
 *
 * Returned Value:
 *   true if supported, false otherwise.
 *
 ****************************************************************************/

bool ra_phy_ics1894_supports_mode(struct ra_phy_ctrl_s *priv,
                                  phy_link_speed_duplex_t mode)
{
  (void)priv;

  /* ICS1894 supports 10/100 Mbps FULL DUPLEX only */

  switch (mode)
    {
    case PHY_LINK_SPEED_DUPLEX_10FD:
    case PHY_LINK_SPEED_DUPLEX_100FD:
      return true;

    case PHY_LINK_SPEED_DUPLEX_10HD:
    case PHY_LINK_SPEED_DUPLEX_100HD:
    case PHY_LINK_SPEED_DUPLEX_1000HD:
    case PHY_LINK_SPEED_DUPLEX_1000FD:
    default:
      return false;  /* No half duplex or Gigabit support */
    }
}

#endif /* CONFIG_RA_ETHERNET */

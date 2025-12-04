/****************************************************************************
 * arch/arm/src/ra8/ra_ether_phy_ksz8091rnb.c
 *
 * Microchip KSZ8091RNB 10/100 PHY Driver
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
 * KSZ8091RNB is a 10/100 Mbps Ethernet PHY from Microchip.
 *
 * Features:
 *   - 10/100 Mbps operation
 *   - MII/RMII interface
 *   - HP Auto MDI/MDI-X
 *   - Energy Efficient Ethernet (EEE)
 *
 * Reference: FSP r_rmac_phy_target_ksz8091rnb.c
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

/* KSZ8091RNB Vendor-Specific Registers */

#define KSZ8091_REG_INTCTRL             0x1B   /* Interrupt Control/Status */
#define KSZ8091_REG_PHYCTRL2            0x1F   /* PHY Control 2 */

/* Interrupt Control Register Bits */

#define KSZ8091_INTCTRL_LUIE            (1 << 8)   /* Link Up Interrupt Enable */
#define KSZ8091_INTCTRL_LDIE            (1 << 10)  /* Link Down Interrupt Enable */

/* PHY Control 2 Register Bits */

#define KSZ8091_PHYCTRL2_RMII_RCS       (1 << 7)   /* RMII Ref Clock Select */
#define KSZ8091_PHYCTRL2_RMII_IL        (1 << 9)   /* Interrupt Level (1=high) */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_phy_ksz8091rnb_init
 *
 * Description:
 *   KSZ8091RNB-specific initialization.
 *   Configures interrupt and clock settings.
 *
 * Input Parameters:
 *   priv - PHY control block
 *
 ****************************************************************************/

void ra_phy_ksz8091rnb_init(struct ra_phy_ctrl_s *priv)
{
  uint16_t regval;
  int ret;

  ninfo("KSZ8091RNB initialization\n");

  /* Enable link-up and link-down interrupts */

  regval = KSZ8091_INTCTRL_LUIE | KSZ8091_INTCTRL_LDIE;

  ret = ra_phy_reg_write(priv, KSZ8091_REG_INTCTRL, regval);
  if (ret < 0)
    {
      nwarn("Failed to write INTCTRL: %d\n", ret);
    }

  /* Read interrupt control to clear any pending status */

  ra_phy_reg_read(priv, KSZ8091_REG_INTCTRL, &regval);

  /* Configure PHY Control 2 */

  ret = ra_phy_reg_read(priv, KSZ8091_REG_PHYCTRL2, &regval);
  if (ret < 0)
    {
      nwarn("Failed to read PHYCTRL2: %d\n", ret);
      return;
    }

  /* Configure for 50MHz reference clock mode if using external clock
   * Set interrupt pin to active low
   */

#ifdef CONFIG_RA_ETHERNET_PHY_REFCLK_50MHZ
  regval |= KSZ8091_PHYCTRL2_RMII_RCS;
#endif

  regval &= ~KSZ8091_PHYCTRL2_RMII_IL;  /* Interrupt active low */

  ret = ra_phy_reg_write(priv, KSZ8091_REG_PHYCTRL2, regval);
  if (ret < 0)
    {
      nwarn("Failed to write PHYCTRL2: %d\n", ret);
    }

  ninfo("KSZ8091RNB configured\n");
}

/****************************************************************************
 * Name: ra_phy_ksz8091rnb_supports_mode
 *
 * Description:
 *   Check if KSZ8091RNB supports a given speed/duplex mode.
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

bool ra_phy_ksz8091rnb_supports_mode(struct ra_phy_ctrl_s *priv,
                                     phy_link_speed_duplex_t mode)
{
  (void)priv;

  /* KSZ8091RNB supports 10/100 Mbps only */

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


/****************************************************************************
 * arch/arm/src/ra8/ra_ether_phy_gpy111.c
 *
 * MaxLinear GPY111 Gigabit PHY Driver
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
 * GPY111 is a Gigabit Ethernet PHY from MaxLinear.
 * Used on the EVK-RA8P1 evaluation kit.
 *
 * Features:
 *   - 10/100/1000 Mbps operation
 *   - RGMII/GMII/MII interface
 *   - IEEE 1588v2 PTP support
 *   - Wake-on-LAN support
 *
 * Key registers beyond standard MII:
 *   - Reg 0x17 (MIICTRL): MII Control with RX timing skew
 *
 * Reference: FSP r_rmac_phy_target_gpy111.c
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

/* GPY111 Vendor-Specific Registers */

#define GPY111_REG_MIICTRL              0x17   /* MII Control Register */

/* MIICTRL Register Bits */

#define GPY111_MIICTRL_RXSKEW_MASK      0x7000 /* RX Timing Skew [14:12] */
#define GPY111_MIICTRL_RXSKEW_0NS       0x0000 /* 0 ns skew */
#define GPY111_MIICTRL_RXSKEW_0_5NS     0x1000 /* 0.5 ns skew */
#define GPY111_MIICTRL_RXSKEW_1NS       0x2000 /* 1.0 ns skew (recommended) */
#define GPY111_MIICTRL_RXSKEW_1_5NS     0x3000 /* 1.5 ns skew */
#define GPY111_MIICTRL_RXSKEW_2NS       0x4000 /* 2.0 ns skew */
#define GPY111_MIICTRL_RXSKEW_2_5NS     0x5000 /* 2.5 ns skew */
#define GPY111_MIICTRL_RXSKEW_3NS       0x6000 /* 3.0 ns skew */
#define GPY111_MIICTRL_RXSKEW_3_5NS     0x7000 /* 3.5 ns skew */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_phy_gpy111_init
 *
 * Description:
 *   GPY111-specific initialization.
 *   Sets up RGMII timing skew for proper operation.
 *
 * Input Parameters:
 *   priv - PHY control block
 *
 ****************************************************************************/

void ra_phy_gpy111_init(struct ra_phy_ctrl_s *priv)
{
  uint16_t regval;
  int ret;

  ninfo("GPY111 initialization\n");

  /* Read current MIICTRL register value */

  ret = ra_phy_reg_read(priv, GPY111_REG_MIICTRL, &regval);
  if (ret < 0)
    {
      nwarn("Failed to read MIICTRL: %d\n", ret);
      return;
    }

  /* Set RGMII receive timing skew to 1.0 ns
   * This compensates for board trace length differences and ensures
   * reliable data sampling at Gigabit speeds.
   * The 1.0 ns value is recommended by FSP for EVK-RA8P1.
   */

  regval = (regval & ~GPY111_MIICTRL_RXSKEW_MASK) |
           GPY111_MIICTRL_RXSKEW_1NS;

  ret = ra_phy_reg_write(priv, GPY111_REG_MIICTRL, regval);
  if (ret < 0)
    {
      nwarn("Failed to write MIICTRL: %d\n", ret);
      return;
    }

  ninfo("GPY111 RX skew set to 1.0 ns\n");
}

/****************************************************************************
 * Name: ra_phy_gpy111_supports_mode
 *
 * Description:
 *   Check if GPY111 supports a given speed/duplex mode.
 *
 * Input Parameters:
 *   priv - PHY control block
 *   mode - Speed/duplex mode to check
 *
 * Returned Value:
 *   true if supported, false otherwise.
 *
 ****************************************************************************/

bool ra_phy_gpy111_supports_mode(struct ra_phy_ctrl_s *priv,
                                 phy_link_speed_duplex_t mode)
{
  (void)priv;  /* Unused - GPY111 supports all standard modes */

  /* GPY111 supports all speed/duplex combinations up to Gigabit */

  switch (mode)
    {
    case PHY_LINK_SPEED_DUPLEX_10HD:
    case PHY_LINK_SPEED_DUPLEX_10FD:
    case PHY_LINK_SPEED_DUPLEX_100HD:
    case PHY_LINK_SPEED_DUPLEX_100FD:
    case PHY_LINK_SPEED_DUPLEX_1000HD:
    case PHY_LINK_SPEED_DUPLEX_1000FD:
      return true;

    default:
      return false;
    }
}

#endif /* CONFIG_RA_ETHERNET */

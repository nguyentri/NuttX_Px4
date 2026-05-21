/****************************************************************************
 * arch/arm/src/ra8/ra_ether_phy_dp83620.c
 *
 * Texas Instruments DP83620 10/100 PHY Driver
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
 * DP83620 is a 10/100 Mbps Ethernet PHY from Texas Instruments.
 *
 * Features:
 *   - 10/100 Mbps operation
 *   - MII/RMII interface
 *   - IEEE 1588 PTP support
 *   - Wake-on-LAN
 *
 * Reference: FSP r_rmac_phy_target_dp83620.c
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

/* DP83620 Vendor-Specific Registers */

#define DP83620_REG_PAGESEL             0x13   /* Page Select */
#define DP83620_REG_14H                 0x14   /* Page-specific register 14H */

/* Page 6 register 14H for RMII clock output configuration */

#define DP83620_REG14H_RMII_MASTER      0x800A /* Default RMII master mode */
#define DP83620_REG14H_RMII_CLKOUT      0x000A /* 50MHz clock output config */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_phy_dp83620_init
 *
 * Description:
 *   DP83620-specific initialization.
 *   Configures RMII clock output for RMII master mode.
 *
 * Input Parameters:
 *   priv - PHY control block
 *
 ****************************************************************************/

void ra_phy_dp83620_init(struct ra_phy_ctrl_s *priv)
{
  uint16_t regval;
  int ret;

  ninfo("DP83620 initialization\n");

  /* For RMII mode, configure clock output settings.
   * This is TI's recommended setting for RMII master mode
   * to output 50 MHz from CLK_OUT.
   */

#ifdef CONFIG_RA_ETHERNET_PHY_RMII
  /* Select page 6 for clock configuration */

  ret = ra_phy_reg_write(priv, DP83620_REG_PAGESEL, 0x0006);
  if (ret < 0)
    {
      nwarn("Failed to write PAGESEL: %d\n", ret);
      return;
    }

  /* Read register 14H on page 6 */

  ret = ra_phy_reg_read(priv, DP83620_REG_14H, &regval);
  if (ret < 0)
    {
      nwarn("Failed to read REG14H: %d\n", ret);
      goto restore_page;
    }

  /* If default RMII master mode value, configure for clock output */

  if (regval == DP83620_REG14H_RMII_MASTER)
    {
      ret = ra_phy_reg_write(priv, DP83620_REG_14H, DP83620_REG14H_RMII_CLKOUT);
      if (ret < 0)
        {
          nwarn("Failed to write REG14H: %d\n", ret);
        }
    }

restore_page:
  /* Restore to page 0 for normal operation */

  ra_phy_reg_write(priv, DP83620_REG_PAGESEL, 0x0000);
#endif

  ninfo("DP83620 configured\n");
}

/****************************************************************************
 * Name: ra_phy_dp83620_supports_mode
 *
 * Description:
 *   Check if DP83620 supports a given speed/duplex mode.
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

bool ra_phy_dp83620_supports_mode(struct ra_phy_ctrl_s *priv,
                                  phy_link_speed_duplex_t mode)
{
  (void)priv;

  /* DP83620 supports 10/100 Mbps only */

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

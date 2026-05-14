/****************************************************************************
 * arch/arm/src/rzv/rzv_ether_phy.c
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
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/clock.h>

#include "arm_internal.h"
#include "hardware/rzv_ether.h"
#include "rzv_ether_phy.h"

#ifdef CONFIG_RZV_ETHERNET

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Timeout values */

#define MDIO_TIMEOUT_MS             100  /* MDIO operation timeout in ms */
#define PHY_RESET_TIMEOUT_MS        500  /* PHY reset timeout in ms */
#define PHY_AUTONEG_TIMEOUT_MS      3000 /* Auto-negotiation timeout in ms */

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_phy_mdio_wait
 *
 * Description:
 *   Wait for MDIO operation to complete
 *
 ****************************************************************************/

static int rzv_phy_mdio_wait(uintptr_t base)
{
  uint32_t timeout = MDIO_TIMEOUT_MS;
  uint32_t regval;

  while (timeout > 0)
    {
      regval = getreg32(base + RZV_ETH_MAC_MII_ADDR);
      if ((regval & MAC_MII_ADDR_GB) == 0)
        {
          return OK;
        }

      up_mdelay(1);
      timeout--;
    }

  nerr("ERROR: MDIO timeout\n");
  return -ETIMEDOUT;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_phy_read
 *
 * Description:
 *   Read a PHY register via MDIO
 *
 ****************************************************************************/

int rzv_phy_read(uintptr_t base, uint8_t phyaddr, uint8_t regaddr,
                 uint16_t *data)
{
  uint32_t regval;
  int ret;

  /* Wait for any pending MDIO operation to complete */

  ret = rzv_phy_mdio_wait(base);
  if (ret < 0)
    {
      return ret;
    }

  /* Build MDIO address register value for read operation */

  regval = MAC_MII_ADDR_GB |
           MAC_MII_ADDR_GR |
           MAC_MII_ADDR_CR_150_250MHZ |
           ((phyaddr << MAC_MII_ADDR_PA_SHIFT) & MAC_MII_ADDR_PA_MASK) |
           ((regaddr << MAC_MII_ADDR_GR_SHIFT) & MAC_MII_ADDR_GR_MASK);

  /* Write to MDIO address register to start read operation */

  putreg32(regval, base + RZV_ETH_MAC_MII_ADDR);

  /* Wait for read operation to complete */

  ret = rzv_phy_mdio_wait(base);
  if (ret < 0)
    {
      return ret;
    }

  /* Read data from MDIO data register */

  *data = (uint16_t)(getreg32(base + RZV_ETH_MAC_MII_DATA) & 0xffff);

  return OK;
}

/****************************************************************************
 * Name: rzv_phy_write
 *
 * Description:
 *   Write a PHY register via MDIO
 *
 ****************************************************************************/

int rzv_phy_write(uintptr_t base, uint8_t phyaddr, uint8_t regaddr,
                  uint16_t data)
{
  uint32_t regval;
  int ret;

  /* Wait for any pending MDIO operation to complete */

  ret = rzv_phy_mdio_wait(base);
  if (ret < 0)
    {
      return ret;
    }

  /* Write data to MDIO data register */

  putreg32((uint32_t)data, base + RZV_ETH_MAC_MII_DATA);

  /* Build MDIO address register value for write operation */

  regval = MAC_MII_ADDR_GB |
           MAC_MII_ADDR_GW |
           MAC_MII_ADDR_CR_150_250MHZ |
           ((phyaddr << MAC_MII_ADDR_PA_SHIFT) & MAC_MII_ADDR_PA_MASK) |
           ((regaddr << MAC_MII_ADDR_GR_SHIFT) & MAC_MII_ADDR_GR_MASK);

  /* Write to MDIO address register to start write operation */

  putreg32(regval, base + RZV_ETH_MAC_MII_ADDR);

  /* Wait for write operation to complete */

  ret = rzv_phy_mdio_wait(base);
  if (ret < 0)
    {
      return ret;
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_phy_reset
 *
 * Description:
 *   Perform a software reset of the PHY
 *
 ****************************************************************************/

int rzv_phy_reset(uintptr_t base, uint8_t phyaddr)
{
  uint16_t regval;
  uint32_t timeout = PHY_RESET_TIMEOUT_MS;
  int ret;

  ninfo("Resetting PHY at address %d\n", phyaddr);

  /* Write reset bit to control register */

  ret = rzv_phy_write(base, phyaddr, PHY_REG_CONTROL, PHY_CTRL_RESET);
  if (ret < 0)
    {
      nerr("ERROR: Failed to write PHY reset: %d\n", ret);
      return ret;
    }

  /* Wait for reset to complete (reset bit clears when done) */

  while (timeout > 0)
    {
      ret = rzv_phy_read(base, phyaddr, PHY_REG_CONTROL, &regval);
      if (ret < 0)
        {
          nerr("ERROR: Failed to read PHY control register: %d\n", ret);
          return ret;
        }

      if ((regval & PHY_CTRL_RESET) == 0)
        {
          ninfo("PHY reset completed\n");
          return OK;
        }

      up_mdelay(1);
      timeout--;
    }

  nerr("ERROR: PHY reset timeout\n");
  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: rzv_phy_probe
 *
 * Description:
 *   Probe a PHY address or scan the MDIO bus for a valid PHY ID.
 *
 ****************************************************************************/

int rzv_phy_probe(uintptr_t base, int fixed_phyaddr, uint8_t *phyaddr,
                  uint32_t *phyid)
{
  uint16_t id1;
  uint16_t id2;
  int start;
  int end;
  int addr;
  int ret;

  if (fixed_phyaddr >= 0 && fixed_phyaddr <= 31)
    {
      start = fixed_phyaddr;
      end = fixed_phyaddr;
    }
  else
    {
      start = 0;
      end = 31;
    }

  for (addr = start; addr <= end; addr++)
    {
      ret = rzv_phy_read(base, addr, PHY_REG_PHYID1, &id1);
      if (ret < 0)
        {
          continue;
        }

      ret = rzv_phy_read(base, addr, PHY_REG_PHYID2, &id2);
      if (ret < 0)
        {
          continue;
        }

      if ((id1 == 0xffff && id2 == 0xffff) || (id1 == 0 && id2 == 0))
        {
          continue;
        }

      *phyaddr = addr;
      *phyid = ((uint32_t)id1 << 16) | id2;
      ninfo("PHY found: addr=%d id=%08" PRIx32 "\n", addr, *phyid);
      return OK;
    }

  nerr("ERROR: no valid PHY found\n");
  return -ENODEV;
}

/****************************************************************************
 * Name: rzv_phy_autonegotiate
 *
 * Description:
 *   Start auto-negotiation and wait for completion
 *
 ****************************************************************************/

int rzv_phy_autonegotiate(uintptr_t base, uint8_t phyaddr)
{
  uint16_t regval;
  uint32_t timeout = PHY_AUTONEG_TIMEOUT_MS;
  int ret;

  ninfo("Starting PHY auto-negotiation\n");

  /* Read current control register value */

  ret = rzv_phy_read(base, phyaddr, PHY_REG_CONTROL, &regval);
  if (ret < 0)
    {
      nerr("ERROR: Failed to read PHY control register: %d\n", ret);
      return ret;
    }

  /* Enable auto-negotiation and restart it */

  regval |= PHY_CTRL_AN_ENABLE | PHY_CTRL_AN_RESTART;
  ret = rzv_phy_write(base, phyaddr, PHY_REG_CONTROL, regval);
  if (ret < 0)
    {
      nerr("ERROR: Failed to start auto-negotiation: %d\n", ret);
      return ret;
    }

  /* Wait for auto-negotiation to complete */

  while (timeout > 0)
    {
      ret = rzv_phy_read(base, phyaddr, PHY_REG_STATUS, &regval);
      if (ret < 0)
        {
          nerr("ERROR: Failed to read PHY status register: %d\n", ret);
          return ret;
        }

      if (regval & PHY_STAT_AN_COMPLETE)
        {
          ninfo("Auto-negotiation completed\n");
          return rzv_phy_linkstatus(base, phyaddr);
        }

      up_mdelay(10);
      timeout -= 10;
    }

  nwarn("WARNING: Auto-negotiation timeout, checking link status\n");
  return rzv_phy_linkstatus(base, phyaddr);
}

/****************************************************************************
 * Name: rzv_phy_linkstatus
 *
 * Description:
 *   Read the current link status from the PHY
 *
 ****************************************************************************/

int rzv_phy_linkstatus(uintptr_t base, uint8_t phyaddr)
{
  uint16_t status;
  uint16_t anar;
  uint16_t anlpar;
  uint16_t ability;
  uint16_t btsr;
  int ret;
  int linkstatus = PHY_LINK_DOWN;

  /* Read PHY status register twice.  The link bit is latch-low on many
   * PHYs, so the second read reflects current state.
   */

  ret = rzv_phy_read(base, phyaddr, PHY_REG_STATUS, &status);
  if (ret < 0)
    {
      nerr("ERROR: Failed to read PHY status: %d\n", ret);
      return ret;
    }

  ret = rzv_phy_read(base, phyaddr, PHY_REG_STATUS, &status);
  if (ret < 0)
    {
      nerr("ERROR: Failed to read PHY status: %d\n", ret);
      return ret;
    }

  /* Check if link is up */

  if ((status & PHY_STAT_LINK_UP) == 0)
    {
      ninfo("Link is down\n");
      return PHY_LINK_DOWN;
    }

  /* Check for 1000BASE-T capability and status */

  ret = rzv_phy_read(base, phyaddr, PHY_REG_1000BTSR, &btsr);
  if (ret == OK && (btsr & PHY_1000BTSR_LP_1000FD))
    {
      ninfo("Link is up: 1000 Mbps Full Duplex\n");
      return PHY_LINK_1000FD;
    }

  /* Read local and link-partner auto-negotiation abilities.  The BMSR
   * capability bits are not laid out like ANAR/ANLPAR.
   */

  ret = rzv_phy_read(base, phyaddr, PHY_REG_ANAR, &anar);
  if (ret < 0)
    {
      nerr("ERROR: Failed to read ANAR: %d\n", ret);
      return ret;
    }

  ret = rzv_phy_read(base, phyaddr, PHY_REG_ANLPAR, &anlpar);
  if (ret < 0)
    {
      nerr("ERROR: Failed to read ANLPAR: %d\n", ret);
      return ret;
    }

  /* Determine link speed and duplex from common advertised capability. */

  ability = anar & anlpar;

  if (ability & PHY_AN_100BASE_TX_FD)
    {
      linkstatus = PHY_LINK_100FD;
      ninfo("Link is up: 100 Mbps Full Duplex\n");
    }
  else if (ability & PHY_AN_100BASE_TX_HD)
    {
      linkstatus = PHY_LINK_100HD;
      ninfo("Link is up: 100 Mbps Half Duplex\n");
    }
  else if (ability & PHY_AN_10BASE_T_FD)
    {
      linkstatus = PHY_LINK_10FD;
      ninfo("Link is up: 10 Mbps Full Duplex\n");
    }
  else if (ability & PHY_AN_10BASE_T_HD)
    {
      linkstatus = PHY_LINK_10HD;
      ninfo("Link is up: 10 Mbps Half Duplex\n");
    }
  else
    {
      nwarn("WARNING: Link up but unable to determine speed/duplex\n");
      linkstatus = PHY_LINK_100FD; /* Default to 100FD */
    }

  return linkstatus;
}

#endif /* CONFIG_RZV_ETHERNET */

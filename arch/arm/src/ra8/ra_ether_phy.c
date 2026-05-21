/****************************************************************************
 * arch/arm/src/ra8/ra_ether_phy.c
 *
 * Core PHY Driver for RA8P1 Ethernet
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
 * This driver provides a hardware-abstraction layer for PHY management
 * on RA8P1 Ethernet. It uses the RMAC MPSM register for MDIO access.
 *
 * Supported PHY devices:
 *   - GPY111 (MaxLinear Gigabit - EVK-RA8P1 default)
 *   - KSZ8091RNB (Microchip 10/100)
 *   - KSZ8041 (Microchip 10/100)
 *   - DP83620 (TI 10/100)
 *   - ICS1894 (Renesas 10/100)
 *
 * Reference: FSP r_rmac_phy.c
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/clock.h>

#include "arm_internal.h"
#include "ra_ether.h"
#include "ra_ether_phy.h"

#ifdef CONFIG_RA_ETHERNET

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* PHY OUI (Organizationally Unique Identifier) definitions
 * Format: PHYID1 = OUI[3:18], PHYID2[15:10] = OUI[19:24]
 */

/* MaxLinear GPY111 */
#define PHY_OUI_GPY111_ID1          0x67C9
#define PHY_OUI_GPY111_ID2_MASK     0xFFF0
#define PHY_OUI_GPY111_ID2          0xDC10

/* Microchip KSZ8091RNB */
#define PHY_OUI_KSZ8091RNB_ID1      0x0022
#define PHY_OUI_KSZ8091RNB_ID2_MASK 0xFFF0
#define PHY_OUI_KSZ8091RNB_ID2      0x1560

/* Microchip KSZ8041 */
#define PHY_OUI_KSZ8041_ID1         0x0022
#define PHY_OUI_KSZ8041_ID2_MASK    0xFFF0
#define PHY_OUI_KSZ8041_ID2         0x1510

/* TI DP83620 */
#define PHY_OUI_DP83620_ID1         0x2000
#define PHY_OUI_DP83620_ID2_MASK    0xFFF0
#define PHY_OUI_DP83620_ID2         0x5CE0

/* Renesas ICS1894 */
#define PHY_OUI_ICS1894_ID1         0x0015
#define PHY_OUI_ICS1894_ID2_MASK    0xFFF0
#define PHY_OUI_ICS1894_ID2         0xF450

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* PHY control blocks for each port */

static struct ra_phy_ctrl_s g_phy_ctrl[2];

/* Target operations table indexed by PHY type.
 * NOTE: Currently unused - PHY-specific operations are implemented inline.
 * This table is reserved for future modular PHY driver support.
 */

static unused_data const struct ra_phy_target_ops_s * const
  g_phy_target_ops[] =
{
  NULL,                  /* PHY_TYPE_UNKNOWN */
  NULL,                  /* PHY_TYPE_KSZ8091RNB - TODO */
  NULL,                  /* PHY_TYPE_KSZ8041 - TODO */
  NULL,                  /* PHY_TYPE_DP83620 - TODO */
  NULL,                  /* PHY_TYPE_ICS1894 - TODO */
  NULL,                  /* PHY_TYPE_GPY111 - Implemented inline */
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_phy_identify
 *
 * Description:
 *   Identify the PHY type by reading PHY ID registers.
 *
 ****************************************************************************/

static phy_device_type_t ra_phy_identify(struct ra_phy_ctrl_s *priv)
{
  uint16_t id1;
  uint16_t id2;
  int ret;

  /* Read PHY ID registers */

  ret = ra_phy_reg_read(priv, PHY_REG_PHYID1, &id1);
  if (ret < 0)
    {
      nerr("Failed to read PHY ID1: %d\n", ret);
      return PHY_TYPE_UNKNOWN;
    }

  ret = ra_phy_reg_read(priv, PHY_REG_PHYID2, &id2);
  if (ret < 0)
    {
      nerr("Failed to read PHY ID2: %d\n", ret);
      return PHY_TYPE_UNKNOWN;
    }

  ninfo("PHY ID: 0x%04x:0x%04x\n", id1, id2);

  /* Identify PHY based on ID values */

  if (id1 == PHY_OUI_GPY111_ID1 &&
      (id2 & PHY_OUI_GPY111_ID2_MASK) == PHY_OUI_GPY111_ID2)
    {
      ninfo("Detected MaxLinear GPY111 Gigabit PHY\n");
      return PHY_TYPE_GPY111;
    }

  if (id1 == PHY_OUI_KSZ8091RNB_ID1 &&
      (id2 & PHY_OUI_KSZ8091RNB_ID2_MASK) == PHY_OUI_KSZ8091RNB_ID2)
    {
      ninfo("Detected Microchip KSZ8091RNB PHY\n");
      return PHY_TYPE_KSZ8091RNB;
    }

  if (id1 == PHY_OUI_KSZ8041_ID1 &&
      (id2 & PHY_OUI_KSZ8041_ID2_MASK) == PHY_OUI_KSZ8041_ID2)
    {
      ninfo("Detected Microchip KSZ8041 PHY\n");
      return PHY_TYPE_KSZ8041;
    }

  if (id1 == PHY_OUI_DP83620_ID1 &&
      (id2 & PHY_OUI_DP83620_ID2_MASK) == PHY_OUI_DP83620_ID2)
    {
      ninfo("Detected TI DP83620 PHY\n");
      return PHY_TYPE_DP83620;
    }

  if (id1 == PHY_OUI_ICS1894_ID1 &&
      (id2 & PHY_OUI_ICS1894_ID2_MASK) == PHY_OUI_ICS1894_ID2)
    {
      ninfo("Detected Renesas ICS1894 PHY\n");
      return PHY_TYPE_ICS1894;
    }

  nwarn("Unknown PHY ID: 0x%04x:0x%04x\n", id1, id2);
  return PHY_TYPE_UNKNOWN;
}

/****************************************************************************
 * Name: ra_phy_chip_init
 *
 * Description:
 *   Perform chip-specific initialization after reset.
 *
 ****************************************************************************/

static int ra_phy_chip_init(struct ra_phy_ctrl_s *priv)
{
  /* Call target-specific initialization based on PHY type */

  switch (priv->type)
    {
    case PHY_TYPE_GPY111:
      ra_phy_gpy111_init(priv);
      break;

    case PHY_TYPE_KSZ8091RNB:
      ra_phy_ksz8091rnb_init(priv);
      break;

    case PHY_TYPE_KSZ8041:
      ra_phy_ksz8041_init(priv);
      break;

    case PHY_TYPE_DP83620:
      ra_phy_dp83620_init(priv);
      break;

    case PHY_TYPE_ICS1894:
      ra_phy_ics1894_init(priv);
      break;

    default:
      nwarn("No target-specific init for PHY type %d\n", priv->type);
      break;
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_phy_reg_read
 *
 * Description:
 *   Read a PHY register via RMAC MPSM.
 *
 ****************************************************************************/

int ra_phy_reg_read(struct ra_phy_ctrl_s *priv, uint8_t regaddr,
                    uint16_t *data)
{
  if (priv == NULL || data == NULL)
    {
      return -EINVAL;
    }

  return ra_phy_read(priv->port, priv->phyaddr, regaddr, data);
}

/****************************************************************************
 * Name: ra_phy_reg_write
 *
 * Description:
 *   Write a PHY register via RMAC MPSM.
 *
 ****************************************************************************/

int ra_phy_reg_write(struct ra_phy_ctrl_s *priv, uint8_t regaddr,
                     uint16_t data)
{
  if (priv == NULL)
    {
      return -EINVAL;
    }

  return ra_phy_write(priv->port, priv->phyaddr, regaddr, data);
}

/****************************************************************************
 * Name: ra_phy_reset
 *
 * Description:
 *   Perform software reset of PHY and wait for completion.
 *
 ****************************************************************************/

int ra_phy_reset(struct ra_phy_ctrl_s *priv)
{
  uint16_t regval;
  int timeout;
  int ret;

  if (priv == NULL)
    {
      return -EINVAL;
    }

  ninfo("Resetting PHY on port %d, addr %d\n", priv->port, priv->phyaddr);

  /* Set reset bit in control register */

  ret = ra_phy_reg_write(priv, PHY_REG_CONTROL, PHY_CTRL_RESET);
  if (ret < 0)
    {
      nerr("Failed to write reset: %d\n", ret);
      return ret;
    }

  /* Wait for reset to complete (reset bit clears itself) */

  timeout = PHY_RESET_TIMEOUT_MS;
  while (timeout > 0)
    {
      ret = ra_phy_reg_read(priv, PHY_REG_CONTROL, &regval);
      if (ret < 0)
        {
          /* MDIO access may fail briefly during reset */

          up_mdelay(1);
          timeout--;
          continue;
        }

      if ((regval & PHY_CTRL_RESET) == 0)
        {
          ninfo("PHY reset complete\n");
          return OK;
        }

      up_mdelay(1);
      timeout--;
    }

  nerr("PHY reset timeout\n");
  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: ra_phy_open
 *
 * Description:
 *   Initialize PHY on the specified port.
 *
 ****************************************************************************/

struct ra_phy_ctrl_s *ra_phy_open(int port, uint8_t phyaddr)
{
  struct ra_phy_ctrl_s *priv;
  int ret;

  if (port < 0 || port > 1 || phyaddr > 31)
    {
      nerr("Invalid parameters: port=%d, phyaddr=%d\n", port, phyaddr);
      return NULL;
    }

  priv = &g_phy_ctrl[port];

  /* Initialize control block */

  memset(priv, 0, sizeof(struct ra_phy_ctrl_s));
  priv->port = port;
  priv->phyaddr = phyaddr;
  priv->type = PHY_TYPE_UNKNOWN;
  priv->initialized = false;
  priv->link_up = false;
  priv->speed_duplex = PHY_LINK_SPEED_DUPLEX_INVALID;

  /* Perform PHY reset */

  ret = ra_phy_reset(priv);
  if (ret < 0)
    {
      nerr("PHY reset failed: %d\n", ret);
      return NULL;
    }

  /* Small delay after reset for PHY stabilization */

  up_mdelay(10);

  /* Identify PHY type */

  priv->type = ra_phy_identify(priv);

  /* Perform chip-specific initialization */

  ret = ra_phy_chip_init(priv);
  if (ret < 0)
    {
      nerr("PHY chip init failed: %d\n", ret);
      return NULL;
    }

  priv->initialized = true;
  ninfo("PHY initialized: port=%d, addr=%d, type=%d\n",
        port, phyaddr, priv->type);

  return priv;
}

/****************************************************************************
 * Name: ra_phy_close
 *
 * Description:
 *   Shut down PHY.
 *
 ****************************************************************************/

int ra_phy_close(struct ra_phy_ctrl_s *priv)
{
  if (priv == NULL)
    {
      return -EINVAL;
    }

  /* Put PHY in power-down mode */

  ra_phy_reg_write(priv, PHY_REG_CONTROL, PHY_CTRL_POWER_DOWN);

  priv->initialized = false;
  priv->link_up = false;

  return OK;
}

/****************************************************************************
 * Name: ra_phy_start_autoneg
 *
 * Description:
 *   Start auto-negotiation process.
 *
 ****************************************************************************/

int ra_phy_start_autoneg(struct ra_phy_ctrl_s *priv)
{
  uint16_t anar;
  uint16_t btcr;
  uint16_t ctrl;
  int ret;

  if (priv == NULL || !priv->initialized)
    {
      return -EINVAL;
    }

  ninfo("Starting auto-negotiation on port %d\n", priv->port);

  /* Set up advertisement register for 10/100 capabilities */

  anar = PHY_ANAR_SELECTOR_802_3 |
         PHY_ANAR_10BASE_T_HD |
         PHY_ANAR_10BASE_T_FD |
         PHY_ANAR_100BASE_TX_HD |
         PHY_ANAR_100BASE_TX_FD |
         PHY_ANAR_PAUSE;

  ret = ra_phy_reg_write(priv, PHY_REG_ANAR, anar);
  if (ret < 0)
    {
      nerr("Failed to write ANAR: %d\n", ret);
      return ret;
    }

  /* For Gigabit PHYs, also set up 1000Base-T advertisement */

  if (priv->type == PHY_TYPE_GPY111)
    {
      btcr = PHY_1000BTCR_1000BASE_T_FD | PHY_1000BTCR_1000BASE_T_HD;

      ret = ra_phy_reg_write(priv, PHY_REG_1000BTCR, btcr);
      if (ret < 0)
        {
          nwarn("Failed to write 1000BTCR: %d\n", ret);
          /* Continue anyway - will negotiate at lower speed */
        }
    }

  /* Enable auto-negotiation and restart */

  ctrl = PHY_CTRL_AN_ENABLE | PHY_CTRL_AN_RESTART;

  ret = ra_phy_reg_write(priv, PHY_REG_CONTROL, ctrl);
  if (ret < 0)
    {
      nerr("Failed to write control: %d\n", ret);
      return ret;
    }

  ninfo("Auto-negotiation started\n");
  return OK;
}

/****************************************************************************
 * Name: ra_phy_get_link_status
 *
 * Description:
 *   Check current link status.
 *
 ****************************************************************************/

bool ra_phy_get_link_status(struct ra_phy_ctrl_s *priv)
{
  uint16_t status;
  int ret;

  if (priv == NULL || !priv->initialized)
    {
      return false;
    }

  /* Read status register twice - first read may latch old status */

  ret = ra_phy_reg_read(priv, PHY_REG_STATUS, &status);
  if (ret < 0)
    {
      return false;
    }

  ret = ra_phy_reg_read(priv, PHY_REG_STATUS, &status);
  if (ret < 0)
    {
      return false;
    }

  priv->link_up = (status & PHY_STAT_LINK_UP) != 0;

  return priv->link_up;
}

/****************************************************************************
 * Name: ra_phy_get_link_partner_ability
 *
 * Description:
 *   Get resolved link speed and duplex after auto-negotiation.
 *
 ****************************************************************************/

int ra_phy_get_link_partner_ability(struct ra_phy_ctrl_s *priv,
                                    phy_link_speed_duplex_t *speed_duplex,
                                    uint8_t *local_pause,
                                    uint8_t *partner_pause)
{
  uint16_t status;
  uint16_t anar;
  uint16_t anlpar;
  uint16_t btsr = 0;
  uint16_t ability;
  int ret;

  if (priv == NULL || !priv->initialized || speed_duplex == NULL)
    {
      return -EINVAL;
    }

  /* Read status to check if AN is complete */

  ret = ra_phy_reg_read(priv, PHY_REG_STATUS, &status);
  if (ret < 0)
    {
      return ret;
    }

  if (!(status & PHY_STAT_AN_COMPLETE))
    {
      *speed_duplex = PHY_LINK_SPEED_DUPLEX_INVALID;
      return -EAGAIN;  /* AN not complete yet */
    }

  /* Read advertisement and link partner ability */

  ret = ra_phy_reg_read(priv, PHY_REG_ANAR, &anar);
  if (ret < 0)
    {
      return ret;
    }

  ret = ra_phy_reg_read(priv, PHY_REG_ANLPAR, &anlpar);
  if (ret < 0)
    {
      return ret;
    }

  /* For Gigabit PHY, read 1000Base-T status */

  if (priv->type == PHY_TYPE_GPY111)
    {
      ret = ra_phy_reg_read(priv, PHY_REG_1000BTSR, &btsr);
      if (ret < 0)
        {
          btsr = 0;  /* Assume no gigabit on error */
        }
    }

  /* Extract pause capabilities */

  if (local_pause != NULL)
    {
      *local_pause = 0;
      if (anar & PHY_ANAR_PAUSE)
        {
          *local_pause |= 0x01;
        }

      if (anar & PHY_ANAR_ASYMMETRIC_PAUSE)
        {
          *local_pause |= 0x02;
        }
    }

  if (partner_pause != NULL)
    {
      *partner_pause = 0;
      if (anlpar & PHY_ANLPAR_PAUSE)
        {
          *partner_pause |= 0x01;
        }

      if (anlpar & PHY_ANLPAR_ASYMMETRIC_PAUSE)
        {
          *partner_pause |= 0x02;
        }
    }

  /* Resolve speed/duplex - priority: 1000FD > 1000HD > 100FD > 100HD > 10FD > 10HD */

  /* Check 1000 Mbps first */

  if (btsr & PHY_1000BTSR_LP_1000BASE_T_FD)
    {
      *speed_duplex = PHY_LINK_SPEED_DUPLEX_1000FD;
    }
  else if (btsr & PHY_1000BTSR_LP_1000BASE_T_HD)
    {
      *speed_duplex = PHY_LINK_SPEED_DUPLEX_1000HD;
    }
  else
    {
      /* Check 10/100 Mbps via ANLPAR */

      ability = anar & anlpar;  /* Common capabilities */

      if (ability & PHY_ANLPAR_100BASE_TX_FD)
        {
          *speed_duplex = PHY_LINK_SPEED_DUPLEX_100FD;
        }
      else if (ability & PHY_ANLPAR_100BASE_TX_HD)
        {
          *speed_duplex = PHY_LINK_SPEED_DUPLEX_100HD;
        }
      else if (ability & PHY_ANLPAR_10BASE_T_FD)
        {
          *speed_duplex = PHY_LINK_SPEED_DUPLEX_10FD;
        }
      else if (ability & PHY_ANLPAR_10BASE_T_HD)
        {
          *speed_duplex = PHY_LINK_SPEED_DUPLEX_10HD;
        }
      else
        {
          *speed_duplex = PHY_LINK_SPEED_DUPLEX_INVALID;
          return -ENOLINK;
        }
    }

  priv->speed_duplex = *speed_duplex;

  ninfo("Resolved speed/duplex: %d\n", *speed_duplex);
  return OK;
}

/****************************************************************************
 * Name: ra_phy_get_id
 *
 * Description:
 *   Read PHY identifier registers.
 *
 ****************************************************************************/

int ra_phy_get_id(struct ra_phy_ctrl_s *priv, uint32_t *phyid)
{
  uint16_t id1;
  uint16_t id2;
  int ret;

  if (priv == NULL || phyid == NULL)
    {
      return -EINVAL;
    }

  ret = ra_phy_reg_read(priv, PHY_REG_PHYID1, &id1);
  if (ret < 0)
    {
      return ret;
    }

  ret = ra_phy_reg_read(priv, PHY_REG_PHYID2, &id2);
  if (ret < 0)
    {
      return ret;
    }

  *phyid = ((uint32_t)id1 << 16) | id2;
  return OK;
}

#endif /* CONFIG_RA_ETHERNET */

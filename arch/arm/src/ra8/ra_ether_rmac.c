/****************************************************************************
 * arch/arm/src/ra8/ra_ether_rmac.c
 *
 * RMAC Driver for RA8P1 Ethernet
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
 * The RMAC driver manages the MAC layer for each Ethernet port on the
 * RA8P1 Layer 3 Ethernet Switch. It handles:
 *   - PHY initialization and auto-negotiation
 *   - Link status monitoring
 *   - MAC address configuration
 *   - Reception filter settings
 *
 * Reference: FSP r_rmac.c
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

#include "arm_internal.h"
#include "chip.h"
#include "ra_ether.h"
#include "ra_ether_phy.h"
#include "ra_ether_rmac.h"

/* Hardware headers */

#include "hardware/ra8p1/ra_rmac.h"

#ifdef CONFIG_RA_ETHERNET

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* RMAC Filter Configuration Values */

#define RMAC_MRAFC_PROMISCUOUS    (R_RMAC_MRAFC_UCENE | R_RMAC_MRAFC_MCENE | \
                                   R_RMAC_MRAFC_BCENE | R_RMAC_MRAFC_BCACE | \
                                   R_RMAC_MRAFC_NDAREE | R_RMAC_MRAFC_SDSFREE | \
                                   R_RMAC_MRAFC_NSAREE | R_RMAC_MRAFC_UCENP | \
                                   R_RMAC_MRAFC_MCENP | R_RMAC_MRAFC_BCENP | \
                                   R_RMAC_MRAFC_BCACP | R_RMAC_MRAFC_NDAREP | \
                                   R_RMAC_MRAFC_SDSFREP | R_RMAC_MRAFC_NSAREP)

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* RMAC control blocks for each port */

static struct ra_rmac_ctrl_s g_rmac_ctrl[2];

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_rmac_configure_phy_interface
 *
 * Description:
 *   Configure RMAC for the resolved PHY interface mode and speed.
 *
 ****************************************************************************/

static int ra_rmac_configure_phy_interface(struct ra_rmac_ctrl_s *priv)
{
  uintptr_t base;
  uint32_t mpic_val;

  base = R_RMAC_BASE + (priv->port * R_RMAC_CH_STRIDE);

  /* Build MPIC register value:
   * PIS[1:0] - PHY Interface Select
   * LSC[3:2] - Link Speed Config
   */

  mpic_val = 0;

  /* Set PHY interface mode */

  switch (priv->phy_mode)
    {
    case RA_ETHER_PHY_MII:
      mpic_val |= (0 << R_RMAC_MPIC_PIS_SHIFT);
      break;

    case RA_ETHER_PHY_RMII:
      mpic_val |= (1 << R_RMAC_MPIC_PIS_SHIFT);
      break;

    case RA_ETHER_PHY_GMII:
      mpic_val |= (2 << R_RMAC_MPIC_PIS_SHIFT);
      break;

    case RA_ETHER_PHY_RGMII:
    default:
      mpic_val |= (3 << R_RMAC_MPIC_PIS_SHIFT);
      break;
    }

  /* Set link speed */

  switch (priv->speed)
    {
    case RA_ETHER_SPEED_10M:
      mpic_val |= (0 << R_RMAC_MPIC_LSC_SHIFT);
      break;

    case RA_ETHER_SPEED_100M:
      mpic_val |= (1 << R_RMAC_MPIC_LSC_SHIFT);
      break;

    case RA_ETHER_SPEED_1000M:
      mpic_val |= (2 << R_RMAC_MPIC_LSC_SHIFT);
      break;

    case RA_ETHER_SPEED_2500M:
    default:
      mpic_val |= (3 << R_RMAC_MPIC_LSC_SHIFT);
      break;
    }

  /* Write MPIC configuration */

  putreg32(mpic_val, base + R_RMAC_MPIC_OFFSET);

  ninfo("RMAC[%d] MPIC=0x%08lx (mode=%d, speed=%d)\n",
        priv->port, (unsigned long)mpic_val, priv->phy_mode, priv->speed);

  return OK;
}

/****************************************************************************
 * Name: ra_rmac_apply_link_settings
 *
 * Description:
 *   Apply resolved link settings from PHY to RMAC.
 *
 ****************************************************************************/

static int ra_rmac_apply_link_settings(struct ra_rmac_ctrl_s *priv,
                                       phy_link_speed_duplex_t speed_duplex)
{
  /* Convert PHY speed/duplex to RMAC settings */

  switch (speed_duplex)
    {
    case PHY_LINK_SPEED_DUPLEX_10HD:
      priv->speed = RA_ETHER_SPEED_10M;
      priv->duplex = RA_ETHER_DUPLEX_HALF;
      break;

    case PHY_LINK_SPEED_DUPLEX_10FD:
      priv->speed = RA_ETHER_SPEED_10M;
      priv->duplex = RA_ETHER_DUPLEX_FULL;
      break;

    case PHY_LINK_SPEED_DUPLEX_100HD:
      priv->speed = RA_ETHER_SPEED_100M;
      priv->duplex = RA_ETHER_DUPLEX_HALF;
      break;

    case PHY_LINK_SPEED_DUPLEX_100FD:
      priv->speed = RA_ETHER_SPEED_100M;
      priv->duplex = RA_ETHER_DUPLEX_FULL;
      break;

    case PHY_LINK_SPEED_DUPLEX_1000HD:
      priv->speed = RA_ETHER_SPEED_1000M;
      priv->duplex = RA_ETHER_DUPLEX_HALF;
      break;

    case PHY_LINK_SPEED_DUPLEX_1000FD:
      priv->speed = RA_ETHER_SPEED_1000M;
      priv->duplex = RA_ETHER_DUPLEX_FULL;
      break;

    default:
      return -EINVAL;
    }

  /* Apply to RMAC */

  return ra_rmac_configure_phy_interface(priv);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_rmac_open
 *
 * Description:
 *   Initialize and open the RMAC for a port.
 *
 ****************************************************************************/

struct ra_rmac_ctrl_s *ra_rmac_open(int port, const uint8_t *mac,
                                    uint8_t phyaddr)
{
  struct ra_rmac_ctrl_s *priv;
  int ret;

  if (port < 0 || port > 1 || mac == NULL)
    {
      nerr("Invalid parameters\n");
      return NULL;
    }

  priv = &g_rmac_ctrl[port];

  /* Initialize control block */

  memset(priv, 0, sizeof(struct ra_rmac_ctrl_s));
  priv->port = port;
  priv->initialized = false;
  priv->link_status = RMAC_LINK_DOWN;
  priv->link_change = RMAC_LINK_NO_CHANGE;

  /* Set default PHY mode - RGMII for Gigabit PHY */

  priv->phy_mode = RMAC_DEFAULT_PHY_MODE;
  priv->speed = RMAC_DEFAULT_SPEED;
  priv->duplex = RMAC_DEFAULT_DUPLEX;

  /* Copy MAC address */

  memcpy(priv->mac, mac, 6);

  /* Initialize PHY */

  priv->phy = ra_phy_open(port, phyaddr);
  if (priv->phy == NULL)
    {
      nerr("Failed to open PHY\n");
      return NULL;
    }

  /* Set MAC address in RMAC */

  ret = ra_rmac_set_mac(priv, mac);
  if (ret < 0)
    {
      nerr("Failed to set MAC address: %d\n", ret);
      ra_phy_close(priv->phy);
      return NULL;
    }

  /* Configure PHY interface */

  ret = ra_rmac_configure_phy_interface(priv);
  if (ret < 0)
    {
      nerr("Failed to configure PHY interface: %d\n", ret);
      ra_phy_close(priv->phy);
      return NULL;
    }

  priv->initialized = true;

  ninfo("RMAC[%d] opened, MAC=%02x:%02x:%02x:%02x:%02x:%02x\n",
        port, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

  return priv;
}

/****************************************************************************
 * Name: ra_rmac_close
 *
 * Description:
 *   Close the RMAC for a port.
 *
 ****************************************************************************/

int ra_rmac_close(struct ra_rmac_ctrl_s *priv)
{
  if (priv == NULL)
    {
      return -EINVAL;
    }

  /* Close PHY */

  if (priv->phy != NULL)
    {
      ra_phy_close(priv->phy);
      priv->phy = NULL;
    }

  priv->initialized = false;
  priv->link_status = RMAC_LINK_DOWN;

  ninfo("RMAC[%d] closed\n", priv->port);
  return OK;
}

/****************************************************************************
 * Name: ra_rmac_start_link
 *
 * Description:
 *   Start link negotiation.
 *
 ****************************************************************************/

int ra_rmac_start_link(struct ra_rmac_ctrl_s *priv)
{
  if (priv == NULL || !priv->initialized || priv->phy == NULL)
    {
      return -EINVAL;
    }

  /* Start PHY auto-negotiation */

  return ra_phy_start_autoneg(priv->phy);
}

/****************************************************************************
 * Name: ra_rmac_link_process
 *
 * Description:
 *   Process link status changes.
 *
 ****************************************************************************/

int ra_rmac_link_process(struct ra_rmac_ctrl_s *priv)
{
  phy_link_speed_duplex_t speed_duplex;
  uint8_t local_pause;
  uint8_t partner_pause;
  bool link_up;
  int ret;

  if (priv == NULL || !priv->initialized || priv->phy == NULL)
    {
      return -EINVAL;
    }

  /* Check current link status */

  link_up = ra_phy_get_link_status(priv->phy);

  /* Detect link transitions */

  if (link_up && priv->link_status == RMAC_LINK_DOWN)
    {
      /* Link just came up */

      priv->link_change = RMAC_LINK_CHANGE_UP;
      priv->link_status = RMAC_LINK_UP;

      /* Get resolved speed/duplex */

      ret = ra_phy_get_link_partner_ability(priv->phy, &speed_duplex,
                                            &local_pause, &partner_pause);
      if (ret == OK)
        {
          ninfo("Link UP: speed_duplex=%d\n", speed_duplex);

          /* Apply link settings to RMAC */

          ra_rmac_apply_link_settings(priv, speed_duplex);
        }
      else if (ret == -EAGAIN)
        {
          /* AN not complete yet - keep polling */

          priv->link_status = RMAC_LINK_DOWN;
          priv->link_change = RMAC_LINK_NO_CHANGE;
        }
    }
  else if (!link_up && priv->link_status == RMAC_LINK_UP)
    {
      /* Link just went down */

      priv->link_change = RMAC_LINK_CHANGE_DOWN;
      priv->link_status = RMAC_LINK_DOWN;

      ninfo("Link DOWN\n");
    }
  else
    {
      priv->link_change = RMAC_LINK_NO_CHANGE;
    }

  return OK;
}

/****************************************************************************
 * Name: ra_rmac_get_link_status
 *
 * Description:
 *   Get current link status.
 *
 ****************************************************************************/

rmac_link_status_t ra_rmac_get_link_status(struct ra_rmac_ctrl_s *priv)
{
  if (priv == NULL)
    {
      return RMAC_LINK_DOWN;
    }

  return priv->link_status;
}

/****************************************************************************
 * Name: ra_rmac_set_mac
 *
 * Description:
 *   Set MAC address for the port.
 *
 ****************************************************************************/

int ra_rmac_set_mac(struct ra_rmac_ctrl_s *priv, const uint8_t *mac)
{
  uintptr_t base;

  if (priv == NULL || mac == NULL)
    {
      return -EINVAL;
    }

  base = R_RMAC_BASE + (priv->port * R_RMAC_CH_STRIDE);

  /* Update local copy */

  memcpy(priv->mac, mac, 6);

  /* Set RMAC MAC address registers
   * MRMAC0: Lower 32 bits (bytes 2-5)
   * MRMAC1: Upper 16 bits (bytes 0-1)
   */

  putreg32((mac[2] << 24) | (mac[3] << 16) | (mac[4] << 8) | mac[5],
           base + R_RMAC_MRMAC0_OFFSET);

  putreg32((mac[0] << 8) | mac[1],
           base + R_RMAC_MRMAC1_OFFSET);

  return OK;
}

/****************************************************************************
 * Name: ra_rmac_configure_filter
 *
 * Description:
 *   Configure RMAC reception filters.
 *
 ****************************************************************************/

int ra_rmac_configure_filter(struct ra_rmac_ctrl_s *priv,
                             bool promiscuous,
                             bool multicast,
                             bool broadcast)
{
  uintptr_t base;
  uint32_t mrafc;

  if (priv == NULL)
    {
      return -EINVAL;
    }

  base = R_RMAC_BASE + (priv->port * R_RMAC_CH_STRIDE);

  /* Read current filter configuration */

  mrafc = getreg32(base + R_RMAC_MRAFC_OFFSET);

  if (promiscuous)
    {
      /* Enable all reception in promiscuous mode */

      mrafc = RMAC_MRAFC_PROMISCUOUS;
    }
  else
    {
      /* Configure multicast */

      if (multicast)
        {
          mrafc |= R_RMAC_MRAFC_MCENE | R_RMAC_MRAFC_MCENP;
        }
      else
        {
          mrafc &= ~(R_RMAC_MRAFC_MCENE | R_RMAC_MRAFC_MCENP);
        }

      /* Configure broadcast */

      if (broadcast)
        {
          mrafc |= R_RMAC_MRAFC_BCENE | R_RMAC_MRAFC_BCENP;
        }
      else
        {
          mrafc &= ~(R_RMAC_MRAFC_BCENE | R_RMAC_MRAFC_BCENP);
        }
    }

  /* Apply configuration */

  putreg32(mrafc, base + R_RMAC_MRAFC_OFFSET);

  return OK;
}

/****************************************************************************
 * Name: ra_rmac_isr
 *
 * Description:
 *   RMAC PHY interrupt handler.
 *
 ****************************************************************************/

void ra_rmac_isr(struct ra_rmac_ctrl_s *priv)
{
  uintptr_t base;
  uint32_t status;

  if (priv == NULL)
    {
      return;
    }

  base = R_RMAC_BASE + (priv->port * R_RMAC_CH_STRIDE);

  /* Read interrupt status */

  status = getreg32(base + R_RMAC_MMIS0_OFFSET);

  /* Clear interrupt by writing to MMIS2 */

  putreg32(status, base + R_RMAC_MMIS2_OFFSET);

  /* Check for magic packet detection */

  if (status & R_RMAC_MMIS2_MPDIS)
    {
      ninfo("Magic packet detected\n");

      /* Disable magic packet interrupt */

      putreg32(R_RMAC_MMID2_MPDID, base + R_RMAC_MMID2_OFFSET);
    }

  /* Process link status change */

  ra_rmac_link_process(priv);
}

#endif /* CONFIG_RA_ETHERNET */

/****************************************************************************
 * arch/arm/src/ra8/ra_ether_rmac.h
 *
 * RMAC Driver Interface for RA8P1 Ethernet
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

#ifndef __ARCH_ARM_SRC_RA8_RA_ETHER_RMAC_H
#define __ARCH_ARM_SRC_RA8_RA_ETHER_RMAC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

#include "ra_ether.h"
#include "ra_ether_phy.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* RMAC Configuration Default Values */

#define RMAC_DEFAULT_PHY_MODE           RA_ETHER_PHY_RGMII
#define RMAC_DEFAULT_SPEED              RA_ETHER_SPEED_1000M
#define RMAC_DEFAULT_DUPLEX             RA_ETHER_DUPLEX_FULL

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* RMAC Link Status */

typedef enum
{
  RMAC_LINK_DOWN = 0,
  RMAC_LINK_UP
} rmac_link_status_t;

/* RMAC Link Change Event */

typedef enum
{
  RMAC_LINK_NO_CHANGE = 0,
  RMAC_LINK_CHANGE_UP,
  RMAC_LINK_CHANGE_DOWN
} rmac_link_change_t;

/* RMAC Control Block */

struct ra_rmac_ctrl_s
{
  uint8_t                 port;           /* Ethernet port number (0 or 1) */
  bool                    initialized;    /* Initialization complete */
  rmac_link_status_t      link_status;    /* Current link status */
  rmac_link_change_t      link_change;    /* Pending link change event */

  /* PHY configuration */

  struct ra_phy_ctrl_s   *phy;            /* PHY control block */
  ra_ether_phy_mode_t     phy_mode;       /* PHY interface mode */
  ra_ether_speed_t        speed;          /* Link speed */
  ra_ether_duplex_t       duplex;         /* Duplex mode */

  /* MAC address */

  uint8_t                 mac[6];
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: ra_rmac_open
 *
 * Description:
 *   Initialize and open the RMAC for a port.
 *   - Initializes PHY
 *   - Configures MAC address
 *   - Sets up PHY interface mode
 *
 * Input Parameters:
 *   port    - Ethernet port number (0 or 1)
 *   mac     - MAC address (6 bytes)
 *   phyaddr - PHY MDIO address
 *
 * Returned Value:
 *   Pointer to RMAC control block on success, NULL on failure.
 *
 ****************************************************************************/

struct ra_rmac_ctrl_s *ra_rmac_open(int port, const uint8_t *mac,
                                    uint8_t phyaddr);

/****************************************************************************
 * Name: ra_rmac_close
 *
 * Description:
 *   Close the RMAC for a port.
 *   - Shuts down PHY
 *   - Disables interrupts
 *
 * Input Parameters:
 *   priv - RMAC control block
 *
 * Returned Value:
 *   OK on success; negated errno on failure.
 *
 ****************************************************************************/

int ra_rmac_close(struct ra_rmac_ctrl_s *priv);

/****************************************************************************
 * Name: ra_rmac_link_process
 *
 * Description:
 *   Process link status changes.
 *   Called periodically or from interrupt to handle link up/down events.
 *
 * Input Parameters:
 *   priv - RMAC control block
 *
 * Returned Value:
 *   OK on success; negated errno on failure.
 *
 ****************************************************************************/

int ra_rmac_link_process(struct ra_rmac_ctrl_s *priv);

/****************************************************************************
 * Name: ra_rmac_start_link
 *
 * Description:
 *   Start link negotiation.
 *   Initiates PHY auto-negotiation.
 *
 * Input Parameters:
 *   priv - RMAC control block
 *
 * Returned Value:
 *   OK on success; negated errno on failure.
 *
 ****************************************************************************/

int ra_rmac_start_link(struct ra_rmac_ctrl_s *priv);

/****************************************************************************
 * Name: ra_rmac_get_link_status
 *
 * Description:
 *   Get current link status.
 *
 * Input Parameters:
 *   priv - RMAC control block
 *
 * Returned Value:
 *   Current link status.
 *
 ****************************************************************************/

rmac_link_status_t ra_rmac_get_link_status(struct ra_rmac_ctrl_s *priv);

/****************************************************************************
 * Name: ra_rmac_set_mac
 *
 * Description:
 *   Set MAC address for the port.
 *
 * Input Parameters:
 *   priv - RMAC control block
 *   mac  - New MAC address (6 bytes)
 *
 * Returned Value:
 *   OK on success; negated errno on failure.
 *
 ****************************************************************************/

int ra_rmac_set_mac(struct ra_rmac_ctrl_s *priv, const uint8_t *mac);

/****************************************************************************
 * Name: ra_rmac_configure_filter
 *
 * Description:
 *   Configure RMAC reception filters.
 *
 * Input Parameters:
 *   priv       - RMAC control block
 *   promiscuous - Enable promiscuous mode
 *   multicast  - Enable multicast reception
 *   broadcast  - Enable broadcast reception
 *
 * Returned Value:
 *   OK on success; negated errno on failure.
 *
 ****************************************************************************/

int ra_rmac_configure_filter(struct ra_rmac_ctrl_s *priv,
                             bool promiscuous,
                             bool multicast,
                             bool broadcast);

/****************************************************************************
 * Name: ra_rmac_isr
 *
 * Description:
 *   RMAC PHY interrupt handler (RMPI).
 *   Called from interrupt context.
 *
 * Input Parameters:
 *   priv - RMAC control block
 *
 ****************************************************************************/

void ra_rmac_isr(struct ra_rmac_ctrl_s *priv);

#endif /* __ARCH_ARM_SRC_RA8_RA_ETHER_RMAC_H */

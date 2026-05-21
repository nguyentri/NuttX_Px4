/****************************************************************************
 * arch/arm/src/ra8/ra_ether_phy.h
 *
 * PHY Driver Interface for RA8P1 Ethernet
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

#ifndef __ARCH_ARM_SRC_RA8_RA_ETHER_PHY_H
#define __ARCH_ARM_SRC_RA8_RA_ETHER_PHY_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* =========================================================================
 * Standard MII PHY Registers (IEEE 802.3)
 * ========================================================================= */

#define PHY_REG_CONTROL             0   /* Control Register */
#define PHY_REG_STATUS              1   /* Status Register */
#define PHY_REG_PHYID1              2   /* PHY ID Register 1 */
#define PHY_REG_PHYID2              3   /* PHY ID Register 2 */
#define PHY_REG_ANAR                4   /* Auto-Negotiation Advertisement */
#define PHY_REG_ANLPAR              5   /* Auto-Negotiation Link Partner Ability */
#define PHY_REG_ANER                6   /* Auto-Negotiation Expansion */
#define PHY_REG_1000BTCR            9   /* 1000Base-T Control Register */
#define PHY_REG_1000BTSR           10   /* 1000Base-T Status Register */

/* =========================================================================
 * PHY Control Register (Reg 0) Bit Definitions
 * ========================================================================= */

#define PHY_CTRL_RESET              (1 << 15)  /* Software Reset */
#define PHY_CTRL_LOOPBACK           (1 << 14)  /* Loopback Enable */
#define PHY_CTRL_SPEED_SEL_LSB      (1 << 13)  /* Speed Select LSB */
#define PHY_CTRL_AN_ENABLE          (1 << 12)  /* Auto-Negotiation Enable */
#define PHY_CTRL_POWER_DOWN         (1 << 11)  /* Power Down */
#define PHY_CTRL_ISOLATE            (1 << 10)  /* Electrical Isolation */
#define PHY_CTRL_AN_RESTART         (1 << 9)   /* Restart Auto-Negotiation */
#define PHY_CTRL_DUPLEX             (1 << 8)   /* Full Duplex Mode */
#define PHY_CTRL_COLLISION          (1 << 7)   /* Collision Test */
#define PHY_CTRL_SPEED_SEL_MSB      (1 << 6)   /* Speed Select MSB */

/* Speed selection using both bits:
 *   [6:13] = 00: 10 Mbps
 *   [6:13] = 01: 100 Mbps
 *   [6:13] = 10: 1000 Mbps
 */
#define PHY_CTRL_SPEED_10           (0)
#define PHY_CTRL_SPEED_100          PHY_CTRL_SPEED_SEL_LSB
#define PHY_CTRL_SPEED_1000         PHY_CTRL_SPEED_SEL_MSB

/* =========================================================================
 * PHY Status Register (Reg 1) Bit Definitions
 * ========================================================================= */

#define PHY_STAT_100BASE_T4         (1 << 15)  /* 100BASE-T4 capable */
#define PHY_STAT_100BASE_TX_FD      (1 << 14)  /* 100BASE-TX Full Duplex */
#define PHY_STAT_100BASE_TX_HD      (1 << 13)  /* 100BASE-TX Half Duplex */
#define PHY_STAT_10BASE_T_FD        (1 << 12)  /* 10BASE-T Full Duplex */
#define PHY_STAT_10BASE_T_HD        (1 << 11)  /* 10BASE-T Half Duplex */
#define PHY_STAT_100BASE_T2_FD      (1 << 10)  /* 100BASE-T2 Full Duplex */
#define PHY_STAT_100BASE_T2_HD      (1 << 9)   /* 100BASE-T2 Half Duplex */
#define PHY_STAT_EXTENDED_STATUS    (1 << 8)   /* Extended Status in Reg 15 */
#define PHY_STAT_RESERVED           (1 << 7)   /* Reserved */
#define PHY_STAT_MF_PREAMBLE        (1 << 6)   /* MF Preamble Suppression */
#define PHY_STAT_AN_COMPLETE        (1 << 5)   /* Auto-Negotiation Complete */
#define PHY_STAT_REMOTE_FAULT       (1 << 4)   /* Remote Fault Detected */
#define PHY_STAT_AN_ABILITY         (1 << 3)   /* Auto-Negotiation Ability */
#define PHY_STAT_LINK_UP            (1 << 2)   /* Link Status */
#define PHY_STAT_JABBER             (1 << 1)   /* Jabber Detect */
#define PHY_STAT_EXTENDED           (1 << 0)   /* Extended Capabilities */

/* =========================================================================
 * Auto-Negotiation Advertisement Register (Reg 4) Bit Definitions
 * ========================================================================= */

#define PHY_ANAR_NEXT_PAGE          (1 << 15)  /* Next Page */
#define PHY_ANAR_RESERVED           (1 << 14)  /* Reserved */
#define PHY_ANAR_REMOTE_FAULT       (1 << 13)  /* Remote Fault */
#define PHY_ANAR_ASYMMETRIC_PAUSE   (1 << 11)  /* Asymmetric Pause */
#define PHY_ANAR_PAUSE              (1 << 10)  /* Pause Capable */
#define PHY_ANAR_100BASE_T4         (1 << 9)   /* 100BASE-T4 */
#define PHY_ANAR_100BASE_TX_FD      (1 << 8)   /* 100BASE-TX Full Duplex */
#define PHY_ANAR_100BASE_TX_HD      (1 << 7)   /* 100BASE-TX Half Duplex */
#define PHY_ANAR_10BASE_T_FD        (1 << 6)   /* 10BASE-T Full Duplex */
#define PHY_ANAR_10BASE_T_HD        (1 << 5)   /* 10BASE-T Half Duplex */
#define PHY_ANAR_SELECTOR_MASK      (0x001F)   /* Selector Field */
#define PHY_ANAR_SELECTOR_802_3     (0x0001)   /* IEEE 802.3 CSMA/CD */

/* =========================================================================
 * Auto-Negotiation Link Partner Ability Register (Reg 5) Bit Definitions
 * ========================================================================= */

#define PHY_ANLPAR_NEXT_PAGE        (1 << 15)  /* Next Page */
#define PHY_ANLPAR_ACK              (1 << 14)  /* Acknowledge */
#define PHY_ANLPAR_REMOTE_FAULT     (1 << 13)  /* Remote Fault */
#define PHY_ANLPAR_ASYMMETRIC_PAUSE (1 << 11)  /* Asymmetric Pause */
#define PHY_ANLPAR_PAUSE            (1 << 10)  /* Pause Capable */
#define PHY_ANLPAR_100BASE_T4       (1 << 9)   /* 100BASE-T4 */
#define PHY_ANLPAR_100BASE_TX_FD    (1 << 8)   /* 100BASE-TX Full Duplex */
#define PHY_ANLPAR_100BASE_TX_HD    (1 << 7)   /* 100BASE-TX Half Duplex */
#define PHY_ANLPAR_10BASE_T_FD      (1 << 6)   /* 10BASE-T Full Duplex */
#define PHY_ANLPAR_10BASE_T_HD      (1 << 5)   /* 10BASE-T Half Duplex */
#define PHY_ANLPAR_SELECTOR_MASK    (0x001F)   /* Selector Field */

/* =========================================================================
 * 1000Base-T Control Register (Reg 9) Bit Definitions
 * ========================================================================= */

#define PHY_1000BTCR_TEST_MODE_MASK (0xE000)   /* Test Mode [15:13] */
#define PHY_1000BTCR_MS_ENABLE      (1 << 12)  /* Manual Master/Slave Enable */
#define PHY_1000BTCR_MS_VALUE       (1 << 11)  /* Master/Slave Value */
#define PHY_1000BTCR_PORT_TYPE      (1 << 10)  /* Multi-Port Device */
#define PHY_1000BTCR_1000BASE_T_FD  (1 << 9)   /* Advertise 1000BASE-T Full */
#define PHY_1000BTCR_1000BASE_T_HD  (1 << 8)   /* Advertise 1000BASE-T Half */

/* =========================================================================
 * 1000Base-T Status Register (Reg 10) Bit Definitions
 * ========================================================================= */

#define PHY_1000BTSR_MS_CONFIG_FAULT (1 << 15) /* Master/Slave Config Fault */
#define PHY_1000BTSR_MS_CONFIG       (1 << 14) /* Master/Slave Config Result */
#define PHY_1000BTSR_LOCAL_RX_OK     (1 << 13) /* Local Receiver Status */
#define PHY_1000BTSR_REMOTE_RX_OK    (1 << 12) /* Remote Receiver Status */
#define PHY_1000BTSR_LP_1000BASE_T_FD (1 << 11) /* LP 1000BASE-T Full Duplex */
#define PHY_1000BTSR_LP_1000BASE_T_HD (1 << 10) /* LP 1000BASE-T Half Duplex */
#define PHY_1000BTSR_IDLE_ERR_CNT    (0x00FF)  /* Idle Error Count [7:0] */

/* =========================================================================
 * PHY Timeouts and Delays
 * ========================================================================= */

#define PHY_RESET_TIMEOUT_MS        1000       /* Reset completion timeout */
#define PHY_AN_TIMEOUT_MS           5000       /* Auto-negotiation timeout */
#define PHY_LINK_TIMEOUT_MS         3000       /* Link detection timeout */
#define PHY_MDIO_TIMEOUT_MS         10         /* MDIO operation timeout */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* PHY Link Speed Duplex combined value
 * Used by auto-negotiation resolution
 */

typedef enum
{
  PHY_LINK_SPEED_DUPLEX_10HD = 0,         /* 10 Mbps Half Duplex */
  PHY_LINK_SPEED_DUPLEX_10FD,             /* 10 Mbps Full Duplex */
  PHY_LINK_SPEED_DUPLEX_100HD,            /* 100 Mbps Half Duplex */
  PHY_LINK_SPEED_DUPLEX_100FD,            /* 100 Mbps Full Duplex */
  PHY_LINK_SPEED_DUPLEX_1000HD,           /* 1000 Mbps Half Duplex */
  PHY_LINK_SPEED_DUPLEX_1000FD,           /* 1000 Mbps Full Duplex */
  PHY_LINK_SPEED_DUPLEX_INVALID = 0xFF
} phy_link_speed_duplex_t;

/* PHY Device Types */

typedef enum
{
  PHY_TYPE_UNKNOWN = 0,
  PHY_TYPE_KSZ8091RNB,       /* Microchip KSZ8091RNB - 10/100 */
  PHY_TYPE_KSZ8041,          /* Microchip KSZ8041 - 10/100 */
  PHY_TYPE_DP83620,          /* TI DP83620 - 10/100 */
  PHY_TYPE_ICS1894,          /* Renesas ICS1894 - 10/100 */
  PHY_TYPE_GPY111,           /* MaxLinear GPY111 - 10/100/1000 (Gigabit) */
} phy_device_type_t;

/* Board configuration PHY type enum (for Kconfig options) */

typedef enum
{
  RA_PHY_TYPE_GPY111 = PHY_TYPE_GPY111,
  RA_PHY_TYPE_KSZ8091RNB = PHY_TYPE_KSZ8091RNB,
  RA_PHY_TYPE_KSZ8041 = PHY_TYPE_KSZ8041,
  RA_PHY_TYPE_DP83620 = PHY_TYPE_DP83620,
  RA_PHY_TYPE_ICS1894 = PHY_TYPE_ICS1894,
} ra_phy_type_t;

/* Board-level PHY configuration structure */

struct ra_ether_phy_config_s
{
  uint8_t phy_address;       /* PHY MDIO address (0-31) */
  ra_phy_type_t phy_type;    /* PHY type */
  bool autoneg;              /* Enable auto-negotiation */
  bool speed_100;            /* Force 100 Mbps (if autoneg disabled) */
  bool full_duplex;          /* Force full duplex (if autoneg disabled) */
};

/* PHY Control Block */

struct ra_phy_ctrl_s
{
  uint8_t             port;           /* Ethernet port number (0 or 1) */
  uint8_t             phyaddr;        /* PHY MDIO address (0-31) */
  phy_device_type_t   type;           /* PHY device type */
  bool                initialized;    /* Initialization complete flag */
  bool                link_up;        /* Link status */
  phy_link_speed_duplex_t speed_duplex; /* Resolved speed/duplex */
};

/* PHY Target Operations - per-device customization */

struct ra_phy_target_ops_s
{
  /* Target-specific initialization (after reset) */

  int (*init)(struct ra_phy_ctrl_s *priv);

  /* Check if target supports a given speed/duplex mode */

  bool (*supports_mode)(struct ra_phy_ctrl_s *priv,
                        phy_link_speed_duplex_t mode);
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: ra_phy_open
 *
 * Description:
 *   Initialize PHY on the specified port.
 *   - Performs PHY reset
 *   - Identifies PHY type from ID registers
 *   - Applies target-specific initialization
 *
 * Input Parameters:
 *   port    - Ethernet port number (0 or 1)
 *   phyaddr - PHY MDIO address (0-31)
 *
 * Returned Value:
 *   Pointer to PHY control block on success, NULL on failure.
 *
 ****************************************************************************/

struct ra_phy_ctrl_s *ra_phy_open(int port, uint8_t phyaddr);

/****************************************************************************
 * Name: ra_phy_close
 *
 * Description:
 *   Shut down PHY.
 *
 * Input Parameters:
 *   priv - PHY control block
 *
 * Returned Value:
 *   OK on success; negated errno on failure.
 *
 ****************************************************************************/

int ra_phy_close(struct ra_phy_ctrl_s *priv);

/****************************************************************************
 * Name: ra_phy_reset
 *
 * Description:
 *   Perform software reset of PHY and wait for completion.
 *
 * Input Parameters:
 *   priv - PHY control block
 *
 * Returned Value:
 *   OK on success; negated errno on failure or timeout.
 *
 ****************************************************************************/

int ra_phy_reset(struct ra_phy_ctrl_s *priv);

/****************************************************************************
 * Name: ra_phy_read
 *
 * Description:
 *   Read a PHY register.
 *
 * Input Parameters:
 *   priv    - PHY control block
 *   regaddr - Register address (0-31)
 *   data    - Pointer to store read value
 *
 * Returned Value:
 *   OK on success; negated errno on failure.
 *
 ****************************************************************************/

int ra_phy_reg_read(struct ra_phy_ctrl_s *priv, uint8_t regaddr,
                    uint16_t *data);

/****************************************************************************
 * Name: ra_phy_write
 *
 * Description:
 *   Write a PHY register.
 *
 * Input Parameters:
 *   priv    - PHY control block
 *   regaddr - Register address (0-31)
 *   data    - Value to write
 *
 * Returned Value:
 *   OK on success; negated errno on failure.
 *
 ****************************************************************************/

int ra_phy_reg_write(struct ra_phy_ctrl_s *priv, uint8_t regaddr,
                     uint16_t data);

/****************************************************************************
 * Name: ra_phy_start_autoneg
 *
 * Description:
 *   Start auto-negotiation process.
 *
 * Input Parameters:
 *   priv - PHY control block
 *
 * Returned Value:
 *   OK on success; negated errno on failure.
 *
 ****************************************************************************/

int ra_phy_start_autoneg(struct ra_phy_ctrl_s *priv);

/****************************************************************************
 * Name: ra_phy_get_link_status
 *
 * Description:
 *   Check current link status.
 *
 * Input Parameters:
 *   priv - PHY control block
 *
 * Returned Value:
 *   true if link is up, false if link is down.
 *
 ****************************************************************************/

bool ra_phy_get_link_status(struct ra_phy_ctrl_s *priv);

/****************************************************************************
 * Name: ra_phy_get_link_partner_ability
 *
 * Description:
 *   Get resolved link speed and duplex after auto-negotiation.
 *
 * Input Parameters:
 *   priv         - PHY control block
 *   speed_duplex - Pointer to store resolved speed/duplex
 *   local_pause  - Pointer to store local pause capability bits
 *   partner_pause - Pointer to store partner pause capability bits
 *
 * Returned Value:
 *   OK on success; negated errno on failure.
 *
 ****************************************************************************/

int ra_phy_get_link_partner_ability(struct ra_phy_ctrl_s *priv,
                                    phy_link_speed_duplex_t *speed_duplex,
                                    uint8_t *local_pause,
                                    uint8_t *partner_pause);

/****************************************************************************
 * Name: ra_phy_get_id
 *
 * Description:
 *   Read PHY identifier registers.
 *
 * Input Parameters:
 *   priv  - PHY control block
 *   phyid - Pointer to store 32-bit PHY ID (PHYID1 << 16 | PHYID2)
 *
 * Returned Value:
 *   OK on success; negated errno on failure.
 *
 ****************************************************************************/

int ra_phy_get_id(struct ra_phy_ctrl_s *priv, uint32_t *phyid);

/****************************************************************************
 * Target-specific PHY initialization functions
 * These are called by the core PHY driver based on detected PHY type.
 ****************************************************************************/

/* GPY111 (MaxLinear Gigabit PHY - used on EVK-RA8P1) */

void ra_phy_gpy111_init(struct ra_phy_ctrl_s *priv);
bool ra_phy_gpy111_supports_mode(struct ra_phy_ctrl_s *priv,
                                 phy_link_speed_duplex_t mode);

/* KSZ8091RNB (Microchip 10/100 PHY) */

void ra_phy_ksz8091rnb_init(struct ra_phy_ctrl_s *priv);
bool ra_phy_ksz8091rnb_supports_mode(struct ra_phy_ctrl_s *priv,
                                     phy_link_speed_duplex_t mode);

/* KSZ8041 (Microchip 10/100 PHY) */

void ra_phy_ksz8041_init(struct ra_phy_ctrl_s *priv);
bool ra_phy_ksz8041_supports_mode(struct ra_phy_ctrl_s *priv,
                                  phy_link_speed_duplex_t mode);

/* DP83620 (TI 10/100 PHY) */

void ra_phy_dp83620_init(struct ra_phy_ctrl_s *priv);
bool ra_phy_dp83620_supports_mode(struct ra_phy_ctrl_s *priv,
                                  phy_link_speed_duplex_t mode);

/* ICS1894 (Renesas 10/100 PHY) */

void ra_phy_ics1894_init(struct ra_phy_ctrl_s *priv);
bool ra_phy_ics1894_supports_mode(struct ra_phy_ctrl_s *priv,
                                  phy_link_speed_duplex_t mode);

#endif /* __ARCH_ARM_SRC_RA8_RA_ETHER_PHY_H */

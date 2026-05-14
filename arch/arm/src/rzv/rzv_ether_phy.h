/****************************************************************************
 * arch/arm/src/rzv/rzv_ether_phy.h
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

#ifndef __ARCH_ARM_SRC_RZV_RZV_ETHER_PHY_H
#define __ARCH_ARM_SRC_RZV_RZV_ETHER_PHY_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Standard IEEE 802.3 PHY Register Addresses */

#define PHY_REG_CONTROL             0   /* Control Register */
#define PHY_REG_STATUS              1   /* Status Register */
#define PHY_REG_PHYID1              2   /* PHY ID Register 1 */
#define PHY_REG_PHYID2              3   /* PHY ID Register 2 */
#define PHY_REG_ANAR                4   /* Auto-Negotiation Advertisement */
#define PHY_REG_ANLPAR              5   /* Auto-Negotiation Link Partner Ability */
#define PHY_REG_ANER                6   /* Auto-Negotiation Expansion */
#define PHY_REG_1000BTCR            9   /* 1000Base-T Control Register */
#define PHY_REG_1000BTSR           10   /* 1000Base-T Status Register */

/* MMD (MDIO Managed Device) Access Registers */

#define PHY_REG_MMD_CTRL           13   /* MMD Access Control Register */
#define PHY_REG_MMD_DATA           14   /* MMD Access Address/Data Register */

/* PHY Control Register Bits */

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
 * MSB LSB  Speed
 *  0   0   10 Mbps
 *  0   1   100 Mbps
 *  1   0   1000 Mbps
 *  1   1   Reserved
 */

#define PHY_CTRL_SPEED_10           (0)
#define PHY_CTRL_SPEED_100          PHY_CTRL_SPEED_SEL_LSB
#define PHY_CTRL_SPEED_1000         PHY_CTRL_SPEED_SEL_MSB

/* PHY Status Register Bits */

#define PHY_STAT_100BASE_T4         (1 << 15)  /* 100BASE-T4 capable */
#define PHY_STAT_100BASE_TX_FD      (1 << 14)  /* 100BASE-TX Full Duplex */
#define PHY_STAT_100BASE_TX_HD      (1 << 13)  /* 100BASE-TX Half Duplex */
#define PHY_STAT_10BASE_T_FD        (1 << 12)  /* 10BASE-T Full Duplex */
#define PHY_STAT_10BASE_T_HD        (1 << 11)  /* 10BASE-T Half Duplex */
#define PHY_STAT_100BASE_T2_FD      (1 << 10)  /* 100BASE-T2 Full Duplex */
#define PHY_STAT_100BASE_T2_HD      (1 << 9)   /* 100BASE-T2 Half Duplex */
#define PHY_STAT_EXTENDED_STATUS    (1 << 8)   /* Extended Status in Reg 15 */
#define PHY_STAT_MF_PREAMBLE        (1 << 6)   /* MF Preamble Suppression */
#define PHY_STAT_AN_COMPLETE        (1 << 5)   /* Auto-Negotiation Complete */
#define PHY_STAT_REMOTE_FAULT       (1 << 4)   /* Remote Fault Detected */
#define PHY_STAT_AN_ABILITY         (1 << 3)   /* Auto-Negotiation Ability */
#define PHY_STAT_LINK_UP            (1 << 2)   /* Link Status */
#define PHY_STAT_JABBER             (1 << 1)   /* Jabber Detect */
#define PHY_STAT_EXTENDED           (1 << 0)   /* Extended Capabilities */

/* Auto-Negotiation Advertisement / Link Partner Ability Register Bits */

#define PHY_AN_100BASE_T4           (1 << 9)   /* 100BASE-T4 */
#define PHY_AN_100BASE_TX_FD        (1 << 8)   /* 100BASE-TX Full Duplex */
#define PHY_AN_100BASE_TX_HD        (1 << 7)   /* 100BASE-TX Half Duplex */
#define PHY_AN_10BASE_T_FD          (1 << 6)   /* 10BASE-T Full Duplex */
#define PHY_AN_10BASE_T_HD          (1 << 5)   /* 10BASE-T Half Duplex */

/* 1000BASE-T Control Register Bits */

#define PHY_1000BTCR_TEST_MODE      (7 << 13)  /* Test Mode */
#define PHY_1000BTCR_MS_MANUAL      (1 << 12)  /* Manual Master/Slave Config */
#define PHY_1000BTCR_MS_VALUE       (1 << 11)  /* Master/Slave Config Value */
#define PHY_1000BTCR_PORT_TYPE      (1 << 10)  /* Port Type */
#define PHY_1000BTCR_ADV_1000FD     (1 << 9)   /* Advertise 1000BASE-T FD */
#define PHY_1000BTCR_ADV_1000HD     (1 << 8)   /* Advertise 1000BASE-T HD */

/* 1000BASE-T Status Register Bits */

#define PHY_1000BTSR_MS_FAULT       (1 << 15)  /* Master/Slave Fault */
#define PHY_1000BTSR_MS_RESOLVED    (1 << 14)  /* Master/Slave Resolved */
#define PHY_1000BTSR_LOCAL_RX_OK    (1 << 13)  /* Local Receiver Status */
#define PHY_1000BTSR_REMOTE_RX_OK   (1 << 12)  /* Remote Receiver Status */
#define PHY_1000BTSR_LP_1000FD      (1 << 11)  /* Link Partner 1000FD Able */
#define PHY_1000BTSR_LP_1000HD      (1 << 10)  /* Link Partner 1000HD Able */

/* Link status definitions */

#define PHY_LINK_DOWN               0
#define PHY_LINK_10HD               1
#define PHY_LINK_10FD               2
#define PHY_LINK_100HD              3
#define PHY_LINK_100FD              4
#define PHY_LINK_1000FD             5

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifndef __ASSEMBLY__

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_phy_read
 *
 * Description:
 *   Read a PHY register via MDIO
 *
 * Input Parameters:
 *   base    - Ethernet controller base address
 *   phyaddr - PHY address (0-31)
 *   regaddr - PHY register address (0-31)
 *   data    - Pointer to receive the read data
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_phy_read(uintptr_t base, uint8_t phyaddr, uint8_t regaddr,
                 uint16_t *data);

/****************************************************************************
 * Name: rzv_phy_write
 *
 * Description:
 *   Write a PHY register via MDIO
 *
 * Input Parameters:
 *   base    - Ethernet controller base address
 *   phyaddr - PHY address (0-31)
 *   regaddr - PHY register address (0-31)
 *   data    - Data to write
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_phy_write(uintptr_t base, uint8_t phyaddr, uint8_t regaddr,
                  uint16_t data);

/****************************************************************************
 * Name: rzv_phy_probe
 *
 * Description:
 *   Probe a fixed PHY address or scan the MDIO bus for a valid PHY ID.
 *
 * Input Parameters:
 *   base          - Ethernet controller base address
 *   fixed_phyaddr - PHY address 0-31, or negative to scan all addresses
 *   phyaddr       - Pointer to receive discovered PHY address
 *   phyid         - Pointer to receive combined PHY ID registers
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_phy_probe(uintptr_t base, int fixed_phyaddr, uint8_t *phyaddr,
                  uint32_t *phyid);

/****************************************************************************
 * Name: rzv_phy_reset
 *
 * Description:
 *   Perform a software reset of the PHY
 *
 * Input Parameters:
 *   base    - Ethernet controller base address
 *   phyaddr - PHY address (0-31)
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_phy_reset(uintptr_t base, uint8_t phyaddr);

/****************************************************************************
 * Name: rzv_phy_autonegotiate
 *
 * Description:
 *   Start auto-negotiation and wait for completion
 *
 * Input Parameters:
 *   base    - Ethernet controller base address
 *   phyaddr - PHY address (0-31)
 *
 * Returned Value:
 *   Link status (PHY_LINK_xxx) on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_phy_autonegotiate(uintptr_t base, uint8_t phyaddr);

/****************************************************************************
 * Name: rzv_phy_linkstatus
 *
 * Description:
 *   Read the current link status from the PHY
 *
 * Input Parameters:
 *   base    - Ethernet controller base address
 *   phyaddr - PHY address (0-31)
 *
 * Returned Value:
 *   Link status (PHY_LINK_xxx)
 *
 ****************************************************************************/

int rzv_phy_linkstatus(uintptr_t base, uint8_t phyaddr);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RZV_RZV_ETHER_PHY_H */

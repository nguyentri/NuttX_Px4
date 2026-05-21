/****************************************************************************
 * arch/arm/src/ra8/ra_ether.h
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

#ifndef __ARCH_ARM_SRC_RA_RA8_ETHER_H
#define __ARCH_ARM_SRC_RA_RA8_ETHER_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/net/netdev.h>
#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* RA8P1 Layer 3 Ethernet Switch Architecture
 *
 * The RA8P1 uses a Layer 3 Ethernet Switch architecture with the following
 * components:
 *   - COMA (Common Agent): Clock enable/reset control and buffer pool mgmt
 *   - GWCA (Gateway CPU Agent): CPU interface with TX/RX descriptor chains
 *   - ETHA (Ethernet Agent): Per-port TX queue management
 *   - RMAC: MAC layer for each Ethernet port
 *   - PTPM: PTP Timer Module
 *
 * Reference: FSP r_ether.c and r_layer3_switch.c implementations
 */

/* Maximum number of Ethernet ports */
#define RA_ETHER_MAX_PORTS          2

/* GWCA/ETHA Operation Mode values (OPC field)
 * State machine: RESET -> DISABLE -> CONFIG -> OPERATION
 */
#define RA_ETHER_OPC_RESET          0   /* Reset mode */
#define RA_ETHER_OPC_DISABLE        1   /* Disable mode */
#define RA_ETHER_OPC_CONFIG         2   /* Configuration mode */
#define RA_ETHER_OPC_OPERATION      3   /* Operation mode */

/* GWCA Descriptor Chain Configuration bits are defined in hardware/ra8p1/ra_gwca.h
 * as R_GWCA_GWDCC_EDE, R_GWCA_GWDCC_DQT, R_GWCA_GWDCC_BALR, etc.
 */

/* =========================================================================
 * GWCA Extended Descriptor Format - Reference: FSP layer3_switch_descriptor_t
 * =========================================================================
 * The RA8P1 uses 16-byte descriptors with the following format:
 *   Word 0 (INFO): DT[31:28] | DIE[27] | Reserved | DS[25:16] | Reserved
 *   Word 1 (CTRL): Control bits depend on descriptor type
 *   Word 2 (BUF_LO): Lower 32 bits of buffer address
 *   Word 3 (BUF_HI): Upper 8 bits of buffer address (bits 39:32)
 */

/* Descriptor Type (DT) values - bits [31:28] of INFO word */
#define RA_DESC_DT_MASK             (0xF0000000)  /* Descriptor Type mask */
#define RA_DESC_DT_SHIFT            (28)

/* Frame descriptor types */
#define RA_DESC_DT_FEMPTY           (0x00000000)  /* Frame Empty (DT=0) */
#define RA_DESC_DT_FEMPTY_IS        (0x10000000)  /* Frame Empty - Int Set (DT=1) */
#define RA_DESC_DT_FEMPTY_IC        (0x20000000)  /* Frame Empty - Int Clear (DT=2) */
#define RA_DESC_DT_FEMPTY_ND        (0x30000000)  /* Frame Empty - No Data (DT=3) */
#define RA_DESC_DT_FMID             (0x40000000)  /* Frame Middle (DT=4) */
#define RA_DESC_DT_FSTART           (0x50000000)  /* Frame Start (DT=5) */
#define RA_DESC_DT_FEND             (0x60000000)  /* Frame End (DT=6) */
#define RA_DESC_DT_FSINGLE          (0x70000000)  /* Frame Single (DT=7) */

/* Link descriptor types */
#define RA_DESC_DT_LINK             (0x80000000)  /* Link Descriptor (DT=8) */
#define RA_DESC_DT_LINKFIX          (0x90000000)  /* Link Fix Descriptor (DT=9) */
#define RA_DESC_DT_EOS              (0xA0000000)  /* End of Stream (DT=10) */
#define RA_DESC_DT_LEMPTY           (0xC0000000)  /* Link Empty (DT=12) */

/* Descriptor Interrupt Enable */
#define RA_DESC_DIE                 (1 << 27)     /* Descriptor Interrupt Enable */

/* Data Size field - bits [25:16] of INFO word (10 bits = max 1024 for DS) */
#define RA_DESC_DS_MASK             (0x03FF0000)  /* Data Size mask (10 bits) */
#define RA_DESC_DS_SHIFT            (16)

/* TX Descriptor Control word (Word 1) fields */
#define RA_TXDESC_MSC_MASK          (0x0000000F)  /* MAC Select Control */
#define RA_TXDESC_TSEL_SHIFT        (4)           /* Target Select shift */
#define RA_TXDESC_TSEL_MASK         (0x000000F0)  /* Target Select mask */

/* RX Descriptor Control word (Word 1) fields */
#define RA_RXDESC_PS_MASK           (0x00000007)  /* Port Source mask */
#define RA_RXDESC_PF                (1 << 4)      /* PTP Flag */
#define RA_RXDESC_MS                (1 << 5)      /* MAC Select */

/* =========================================================================
 * RMAC Configuration
 * ========================================================================= */

/* RMAC PHY Interface Selection (MPIC.PIS field) */
#define RMAC_MPIC_PIS_MII           (0)           /* MII interface */
#define RMAC_MPIC_PIS_RMII          (1)           /* RMII interface */
#define RMAC_MPIC_PIS_GMII          (2)           /* GMII interface */
#define RMAC_MPIC_PIS_RGMII         (3)           /* RGMII interface */

/* RMAC Link Speed Configuration (MPIC.LSC field) */
#define RMAC_MPIC_LSC_10M           (0)           /* 10 Mbps */
#define RMAC_MPIC_LSC_100M          (1)           /* 100 Mbps */
#define RMAC_MPIC_LSC_1000M         (2)           /* 1000 Mbps (Gigabit) */
#define RMAC_MPIC_LSC_2500M         (3)           /* 2.5 Gbps */

/* RMAC MPSM (PHY Station Management) register bits */
#define RMAC_MPSM_PSME              (1 << 0)      /* PHY Station Management Enable */
#define RMAC_MPSM_PSMAD_SHIFT       (3)           /* PHY Address shift */
#define RMAC_MPSM_PSMAD_MASK        (0x1F << 3)   /* PHY Address mask (5 bits) */
#define RMAC_MPSM_PDA_SHIFT         (8)           /* PHY Data Address shift */
#define RMAC_MPSM_PDA_MASK          (0x1F << 8)   /* PHY Data Address mask */
#define RMAC_MPSM_PRA_SHIFT         (13)          /* PHY Register Address shift */
#define RMAC_MPSM_PRA_MASK          (0x1F << 13)  /* PHY Register Address mask */
#define RMAC_MPSM_PRD_SHIFT         (16)          /* PHY Read Data shift */
#define RMAC_MPSM_PRD_MASK          (0xFFFF << 16) /* PHY Read Data mask */
#define RMAC_MPSM_PSMCS_IDLE        (0 << 1)      /* MDIO Clock idle */
#define RMAC_MPSM_PSMCS_READ        (2 << 1)      /* MDIO Read operation */
#define RMAC_MPSM_PSMCS_WRITE       (1 << 1)      /* MDIO Write operation */

/* =========================================================================
 * Buffer Configuration
 * ========================================================================= */

#define RA_MAX_PACKET_SIZE          1536          /* Maximum Ethernet frame size */
#define RA_DESC_ALIGN               16            /* Descriptor alignment */
#define RA_BUF_ALIGN                32            /* Buffer alignment */

/* Default descriptor counts */
#ifndef CONFIG_RA_ETHERNET_NTXDESC
#  define CONFIG_RA_ETHERNET_NTXDESC 8
#endif

#ifndef CONFIG_RA_ETHERNET_NRXDESC
#  define CONFIG_RA_ETHERNET_NRXDESC 8
#endif

/* GWCA Descriptor Queue Configuration */
#define RA_ETHER_RX_QUEUE           0             /* RX queue number for CPU */
#define RA_ETHER_TX_QUEUE           0             /* TX queue number for CPU */

/* COMA Reset/Clock Enable bits */
#define COMA_RRC_RR                 (1 << 0)      /* Software Reset */
#define COMA_RCEC_RCE               (1 << 16)     /* Root Clock Enable */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* GWCA Extended Transmit/Receive Descriptor
 * 16-byte aligned structure matching FSP layer3_switch_descriptor_t
 */

struct ra_eth_desc_s
{
  volatile uint32_t info;         /* DT[31:28] | DIE[27] | DS[25:16] */
  volatile uint32_t ctrl;         /* Control/Status bits */
  volatile uint32_t buf_lo;       /* Buffer Address Low (32-bit) */
  volatile uint32_t buf_hi;       /* Buffer Address High (8-bit) */
};

/* Separate types for clarity (same underlying structure) */

typedef struct ra_eth_desc_s ra_eth_txdesc_t;
typedef struct ra_eth_desc_s ra_eth_rxdesc_t;
typedef struct ra_eth_desc_s ra_eth_linkdesc_t;

/* PHY Interface Mode */

typedef enum
{
  RA_ETHER_PHY_MII = 0,           /* MII interface */
  RA_ETHER_PHY_RMII,              /* RMII interface */
  RA_ETHER_PHY_GMII,              /* GMII interface */
  RA_ETHER_PHY_RGMII              /* RGMII interface */
} ra_ether_phy_mode_t;

/* Link Speed */

typedef enum
{
  RA_ETHER_SPEED_10M = 0,         /* 10 Mbps */
  RA_ETHER_SPEED_100M,            /* 100 Mbps */
  RA_ETHER_SPEED_1000M,           /* 1000 Mbps */
  RA_ETHER_SPEED_2500M            /* 2500 Mbps */
} ra_ether_speed_t;

/* Duplex Mode */

typedef enum
{
  RA_ETHER_DUPLEX_HALF = 0,       /* Half duplex */
  RA_ETHER_DUPLEX_FULL            /* Full duplex */
} ra_ether_duplex_t;

/* Ethernet Port Configuration */

struct ra_ether_config_s
{
  ra_ether_phy_mode_t phy_mode;   /* PHY interface mode */
  ra_ether_speed_t    speed;      /* Link speed */
  ra_ether_duplex_t   duplex;     /* Duplex mode */
  uint8_t             mac[6];     /* MAC address */
  uint8_t             phyaddr;    /* PHY address (0-31) */
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: ra_ether_initialize
 *
 * Description:
 *   Initialize the Ethernet driver for the specified port.
 *   This initializes the Layer 3 Ethernet Switch components:
 *   COMA, GWCA, ETHA, and RMAC.
 *
 * Input Parameters:
 *   port   - The Ethernet port number (0 or 1)
 *
 * Returned Value:
 *   OK on success; Negated errno on failure.
 *
 ****************************************************************************/

int ra_ether_initialize(int port);

/****************************************************************************
 * Name: ra_ether_set_macaddr
 *
 * Description:
 *   Set the MAC address for the specified Ethernet port.
 *
 * Input Parameters:
 *   port - The Ethernet port number (0 or 1)
 *   mac  - Pointer to 6-byte MAC address
 *
 * Returned Value:
 *   OK on success; Negated errno on failure.
 *
 ****************************************************************************/

int ra_ether_set_macaddr(int port, const uint8_t *mac);

/****************************************************************************
 * Name: ra_ether_get_macaddr
 *
 * Description:
 *   Get the MAC address for the specified Ethernet port.
 *
 * Input Parameters:
 *   port - The Ethernet port number (0 or 1)
 *   mac  - Pointer to 6-byte buffer to receive MAC address
 *
 * Returned Value:
 *   OK on success; Negated errno on failure.
 *
 ****************************************************************************/

int ra_ether_get_macaddr(int port, uint8_t *mac);

/****************************************************************************
 * Name: ra_phy_read
 *
 * Description:
 *   Read a PHY register via MDIO/MDC using RMAC MPSM register.
 *
 * Input Parameters:
 *   port    - Ethernet port number (0 or 1)
 *   phyaddr - PHY address (0-31)
 *   regaddr - Register address (0-31)
 *   data    - Pointer to store read data
 *
 * Returned Value:
 *   OK on success; Negated errno on failure.
 *
 ****************************************************************************/

int ra_phy_read(int port, uint8_t phyaddr, uint8_t regaddr, uint16_t *data);

/****************************************************************************
 * Name: ra_phy_write
 *
 * Description:
 *   Write a PHY register via MDIO/MDC using RMAC MPSM register.
 *
 * Input Parameters:
 *   port    - Ethernet port number (0 or 1)
 *   phyaddr - PHY address (0-31)
 *   regaddr - Register address (0-31)
 *   data    - Data to write
 *
 * Returned Value:
 *   OK on success; Negated errno on failure.
 *
 ****************************************************************************/

int ra_phy_write(int port, uint8_t phyaddr, uint8_t regaddr, uint16_t data);

#endif /* __ARCH_ARM_SRC_RA_RA8_ETHER_H */

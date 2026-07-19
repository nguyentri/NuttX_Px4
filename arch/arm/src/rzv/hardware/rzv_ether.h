/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_ether.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_ETHER_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_ETHER_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Register Base Addresses */

#define RZV_ETHER0_BASE             0x15C30000
#define RZV_ETHER1_BASE             0x15C40000

/* Register Offsets */

/* MAC Registers */
#define RZV_ETH_MAC_CONF            0x0000 /* MAC Configuration */
#define RZV_ETH_MAC_EXT_CONF        0x0004 /* MAC Extended Configuration */
#define RZV_ETH_MAC_PKT_FILT        0x0008 /* MAC Packet Filter */
#define RZV_ETH_MAC_WD_TO           0x000C /* MAC Watchdog Timeout */
#define RZV_ETH_MAC_HASH_HI         0x0010 /* MAC Hash Table High */
#define RZV_ETH_MAC_HASH_LO         0x0014 /* MAC Hash Table Low */
#define RZV_ETH_MAC_MII_ADDR        0x0200 /* MAC MDIO Address */
#define RZV_ETH_MAC_MII_DATA        0x0204 /* MAC MDIO Data */
#define RZV_ETH_MAC_TX_FLOW_CTRL    0x0070 /* MAC TX Flow Control */
#define RZV_ETH_MAC_RX_FLOW_CTRL    0x0090 /* MAC RX Flow Control */
#define RZV_ETH_MAC_FLOW_CTRL       0x0090 /* Legacy alias for RX flow control */
#define RZV_ETH_MAC_RXQ_CTRL0       0x00A0 /* MAC RX Queue 0 Control */
#define RZV_ETH_MAC_RXQ_CTRL1       0x00A4 /* MAC RX Queue 1 Control */
#define RZV_ETH_MAC_RXQ_CTRL2       0x00A8 /* MAC RX Queue Priority Mapping 0 */
#define RZV_ETH_MAC_RXQ_CTRL3       0x00AC /* MAC RX Queue Priority Mapping 1 */
#define RZV_ETH_MAC_INT_STAT        0x00B0 /* MAC Interrupt Status */
#define RZV_ETH_MAC_INT_EN          0x00B4 /* MAC Interrupt Enable */
#define RZV_ETH_MAC_ADDR0_HI        0x0300 /* MAC Address 0 High */
#define RZV_ETH_MAC_ADDR0_LO        0x0304 /* MAC Address 0 Low */

/* MTL Registers (Queue 0) */

#define RZV_ETH_MTL_OPERATION_MODE  0x0C00 /* MTL Operation Mode */
#define RZV_ETH_MTL_RXQ_DMA_MAP0    0x0C30 /* MTL RX Queue DMA Map 0 */
#define RZV_ETH_MTL_TXQ0_OP_MODE    0x0D00 /* MTL TX Queue 0 Operation Mode */
#define RZV_ETH_MTL_RXQ0_OP_MODE    0x0D30 /* MTL RX Queue 0 Operation Mode */

/* DMA Registers (Channel 0) */
#define RZV_ETH_DMA_MODE            0x1000 /* DMA Mode */
#define RZV_ETH_DMA_SYSBUS_MODE     0x1004 /* DMA System Bus Mode */
#define RZV_ETH_DMA_INT_STATUS      0x1008 /* DMA Interrupt Status */
#define RZV_ETH_DMA_CH0_CTRL        0x1100 /* DMA Channel 0 Control */
#define RZV_ETH_DMA_CH0_TX_CTRL     0x1104 /* DMA Channel 0 TX Control */
#define RZV_ETH_DMA_CH0_RX_CTRL     0x1108 /* DMA Channel 0 RX Control */
#define RZV_ETH_DMA_CH0_TXDESC_HI   0x1110 /* DMA Channel 0 TX Descriptor High Address */
#define RZV_ETH_DMA_CH0_TXDESC_LIST 0x1114 /* DMA Channel 0 TX Descriptor List Address */
#define RZV_ETH_DMA_CH0_RXDESC_HI   0x1118 /* DMA Channel 0 RX Descriptor High Address */
#define RZV_ETH_DMA_CH0_RXDESC_LIST 0x111C /* DMA Channel 0 RX Descriptor List Address */
#define RZV_ETH_DMA_CH0_TXDESC_TAIL 0x1120 /* DMA Channel 0 TX Descriptor Tail Pointer */
#define RZV_ETH_DMA_CH0_RXDESC_TAIL 0x1128 /* DMA Channel 0 RX Descriptor Tail Pointer */
#define RZV_ETH_DMA_CH0_TXDESC_RING 0x112C /* DMA Channel 0 TX Descriptor Ring Length */
#define RZV_ETH_DMA_CH0_RX_CTRL2    0x1130 /* DMA Channel 0 RX Control 2 */
#define RZV_ETH_DMA_CH0_INT_EN      0x1134 /* DMA Channel 0 Interrupt Enable */
#define RZV_ETH_DMA_CH0_RX_INT_WD   0x113C /* DMA Channel 0 RX Interrupt Watchdog Timer */
#define RZV_ETH_DMA_CH0_SLOT_CTRL   0x1140 /* DMA Channel 0 Slot Function Control Status */
#define RZV_ETH_DMA_CH0_CUR_TXDESC  0x1144 /* DMA Channel 0 Current Host Transmit Descriptor */
#define RZV_ETH_DMA_CH0_CUR_RXDESC  0x114C /* DMA Channel 0 Current Host Receive Descriptor */
#define RZV_ETH_DMA_CH0_CUR_TXBUF   0x1154 /* DMA Channel 0 Current Host Transmit Buffer Address */
#define RZV_ETH_DMA_CH0_CUR_RXBUF   0x115C /* DMA Channel 0 Current Host Receive Buffer Address */
#define RZV_ETH_DMA_CH0_STATUS      0x1160 /* DMA Channel 0 Status */

/* Bit Definitions */

/* MAC Configuration Register */
#define MAC_CONF_RE                 (1 << 0)  /* Receiver Enable */
#define MAC_CONF_TE                 (1 << 1)  /* Transmitter Enable */
#define MAC_CONF_DC                 (1 << 2)  /* Deferral Check */
#define MAC_CONF_BL_SHIFT           (4)       /* Back-Off Limit */
#define MAC_CONF_BL_MASK            (3 << MAC_CONF_BL_SHIFT)
#define MAC_CONF_ACS                (1 << 7)  /* Automatic Pad/CRC Stripping */
#define MAC_CONF_DR                 (1 << 9)  /* Disable Retry */
#define MAC_CONF_IPC                (1 << 10) /* Checksum Offload */
#define MAC_CONF_DM                 (1 << 11) /* Duplex Mode */
#define MAC_CONF_LM                 (1 << 12) /* Loopback Mode */
#define MAC_CONF_DO                 (1 << 13) /* Disable Receive Own */
#define MAC_CONF_FES                (1 << 14) /* Speed */
#define MAC_CONF_PS                 (1 << 15) /* Port Select */
#define MAC_CONF_JE                 (1 << 16) /* Jumbo Frame Enable */
#define MAC_CONF_JD                 (1 << 17) /* Jabber Disable */
#define MAC_CONF_WD                 (1 << 23) /* Watchdog Disable */
#define MAC_CONF_BE                 (1 << 18) /* Burst Enable for gigabit */
#define MAC_CONF_S2KP               (1 << 22) /* Support 2K Packets */
#define MAC_CONF_CST                (1 << 25) /* CRC Stripping for Type frames */

/* Baseline MAC_CONFIGURATION bits programmed by the FSP reference at power-on
 * (JE|JD|BE|WD|GPSLCE family = 0x009B0000).  Merging these into MAC_CONF
 * matches the validated register profile and disables the jabber/watchdog
 * behavior that can otherwise drop legitimate frames.
 */

#define MAC_CONF_FSP_BASELINE       (MAC_CONF_JE | MAC_CONF_JD | \
                                     MAC_CONF_BE | MAC_CONF_WD)

/* MAC RX Queue 0 Control (0x00A0): route RXQ0 into the DMA path.
 * RXQ0EN field (bits 1:0):
 *   00 = Disabled (packets dropped in MAC)
 *   01 = AV enabled
 *   10 = DCB enabled  <-- FSP default
 */

#define MAC_RXQ_CTRL0_RXQ0EN_SHIFT  (0)
#define MAC_RXQ_CTRL0_RXQ0EN_MASK   (0x3 << MAC_RXQ_CTRL0_RXQ0EN_SHIFT)
#define MAC_RXQ_CTRL0_RXQ0EN_DCB    (0x2 << MAC_RXQ_CTRL0_RXQ0EN_SHIFT)
#define MAC_RXQ_CTRL0_RXQ0EN_AV     (0x1 << MAC_RXQ_CTRL0_RXQ0EN_SHIFT)

/* DMA Mode Register */
#define DMA_MODE_SWR                (1 << 0)  /* Software Reset */

/* DMA System Bus Mode Register */
#define DMA_SYSBUS_MODE_AAL         (1 << 12) /* Address-aligned beats */

/* DMA Channel 0 Status Register */
#define DMA_CH0_STATUS_TI           (1 << 0)  /* Transmit Interrupt */
#define DMA_CH0_STATUS_TPS          (1 << 1)  /* Transmit Process Stopped */
#define DMA_CH0_STATUS_TBU          (1 << 2)  /* Transmit Buffer Unavailable */
#define DMA_CH0_STATUS_RI           (1 << 6)  /* Receive Interrupt */
#define DMA_CH0_STATUS_RBU          (1 << 7)  /* Receive Buffer Unavailable */
#define DMA_CH0_STATUS_RPS          (1 << 8)  /* Receive Process Stopped */
#define DMA_CH0_STATUS_AIS          (1 << 15) /* Abnormal Interrupt Summary */
#define DMA_CH0_STATUS_NIS          (1 << 16) /* Normal Interrupt Summary */

/* DMA Channel 0 Interrupt Enable Register */
#define DMA_CH0_INT_EN_TIE          (1 << 0)  /* Transmit Interrupt Enable */
#define DMA_CH0_INT_EN_TBUE         (1 << 2)  /* Transmit Buffer Unavailable Enable */
#define DMA_CH0_INT_EN_RIE          (1 << 6)  /* Receive Interrupt Enable */
#define DMA_CH0_INT_EN_RBUE         (1 << 7)  /* Receive Buffer Unavailable Enable */
#define DMA_CH0_INT_EN_AISE         (1 << 15) /* Abnormal Interrupt Summary Enable */
#define DMA_CH0_INT_EN_NISE         (1 << 16) /* Normal Interrupt Summary Enable */

/* DMA Channel 0 Control Register (0x1100) */
#define DMA_CH0_CTRL_PBLX8          (1 << 16) /* Multiply PBL by 8 */

/* DMA Channel TX/RX Control Registers */
#define DMA_CH0_TX_CTRL_ST          (1 << 0)  /* Start/Stop Transmission */
#define DMA_CH0_TX_CTRL_OSP         (1 << 4)  /* Operate on Second Packet */
#define DMA_CH0_TX_CTRL_TXPBL_SHIFT (16)
#define DMA_CH0_TX_CTRL_TXPBL_MASK  (0x3f << DMA_CH0_TX_CTRL_TXPBL_SHIFT)
#define DMA_CH0_TX_CTRL_TXPBL(n)    ((n) << DMA_CH0_TX_CTRL_TXPBL_SHIFT)

#define DMA_CH0_RX_CTRL_SR          (1 << 0)  /* Start/Stop Receive */
#define DMA_CH0_RX_CTRL_RBSZ_SHIFT  (1)
#define DMA_CH0_RX_CTRL_RBSZ_MASK   (0x3fff << DMA_CH0_RX_CTRL_RBSZ_SHIFT)
#define DMA_CH0_RX_CTRL_RBSZ(n)     ((n) << DMA_CH0_RX_CTRL_RBSZ_SHIFT)
#define DMA_CH0_RX_CTRL_RXPBL_SHIFT (16)
#define DMA_CH0_RX_CTRL_RXPBL_MASK  (0x3f << DMA_CH0_RX_CTRL_RXPBL_SHIFT)
#define DMA_CH0_RX_CTRL_RXPBL(n)    ((n) << DMA_CH0_RX_CTRL_RXPBL_SHIFT)

/* MAC MDIO Address Register
 *
 * DWMAC4/EQOS GOC[3:2] is a 2-bit opcode field:
 *   01 = Write, 10 = Post-Increment-Read, 11 = Single Read.
 * Use MAC_MII_ADDR_GOC_WRITE / MAC_MII_ADDR_GOC_READ helpers below; the
 * legacy MAC_MII_ADDR_GW / MAC_MII_ADDR_GR aliases are kept for readers
 * familiar with the older single-bit naming.
 */

#define MAC_MII_ADDR_GB             (1 << 0)  /* GMII Busy */
#define MAC_MII_ADDR_GOC_SHIFT      (2)
#define MAC_MII_ADDR_GOC_MASK       (0x3 << MAC_MII_ADDR_GOC_SHIFT)
#define MAC_MII_ADDR_GOC_WRITE      (0x1 << MAC_MII_ADDR_GOC_SHIFT)
#define MAC_MII_ADDR_GOC_READ       (0x3 << MAC_MII_ADDR_GOC_SHIFT)
#define MAC_MII_ADDR_GW             MAC_MII_ADDR_GOC_WRITE
#define MAC_MII_ADDR_GR             MAC_MII_ADDR_GOC_READ
#define MAC_MII_ADDR_CR_SHIFT       (8)       /* CSR Clock Range */
#define MAC_MII_ADDR_CR_MASK        (0xF << MAC_MII_ADDR_CR_SHIFT)
#define MAC_MII_ADDR_GR_SHIFT       (16)      /* GMII Register */
#define MAC_MII_ADDR_GR_MASK        (0x1F << MAC_MII_ADDR_GR_SHIFT)
#define MAC_MII_ADDR_PA_SHIFT       (21)      /* Physical Layer Address */
#define MAC_MII_ADDR_PA_MASK        (0x1F << MAC_MII_ADDR_PA_SHIFT)
#define MAC_MII_ADDR_CR_150_250MHZ  (4 << MAC_MII_ADDR_CR_SHIFT)
#define MAC_MII_ADDR_CR_100_150MHZ  (1 << MAC_MII_ADDR_CR_SHIFT)
#define MAC_MII_ADDR_CR_250_300MHZ  (5 << MAC_MII_ADDR_CR_SHIFT)

/* MAC Packet Filter Register (0x0008) */

#define MAC_PKT_FILT_PR             (1 << 0)  /* Promiscuous Mode */
#define MAC_PKT_FILT_HUC            (1 << 1)  /* Hash Unicast */
#define MAC_PKT_FILT_HMC            (1 << 2)  /* Hash Multicast */
#define MAC_PKT_FILT_DAIF           (1 << 3)  /* DA Inverse Filtering */
#define MAC_PKT_FILT_PM             (1 << 4)  /* Pass All Multicast */
#define MAC_PKT_FILT_DBF            (1 << 5)  /* Disable Broadcast */
#define MAC_PKT_FILT_PCF_SHIFT      (6)
#define MAC_PKT_FILT_PCF_MASK       (0x3 << MAC_PKT_FILT_PCF_SHIFT)
#define MAC_PKT_FILT_HPF            (1 << 10) /* Hash or Perfect Filter */
#define MAC_PKT_FILT_RA             (1 << 31) /* Receive All */

/* MTL Operation Mode Register (0x0C00) */

#define MTL_OP_MODE_DTXSTS          (1 << 1)  /* Drop TX Status */
#define MTL_OP_MODE_RAA             (1 << 2)  /* Receive Arbitration Algorithm */

/* MTL TXQ0 Operation Mode (0x0D00) */

#define MTL_TXQ_OP_FTQ              (1 << 0)  /* Flush Transmit Queue */
#define MTL_TXQ_OP_TSF              (1 << 1)  /* Transmit Store-and-Forward */
#define MTL_TXQ_OP_TXQEN_SHIFT      (2)       /* Bits 3:2 TX Queue Enable */
#define MTL_TXQ_OP_TXQEN_MASK       (0x3 << MTL_TXQ_OP_TXQEN_SHIFT)
#define MTL_TXQ_OP_TXQEN_EN         (0x2 << MTL_TXQ_OP_TXQEN_SHIFT) /* Enabled */
#define MTL_TXQ_OP_TTC_SHIFT        (4)       /* Bits 6:4 TX Threshold */
#define MTL_TXQ_OP_TTC_MASK         (0x7 << MTL_TXQ_OP_TTC_SHIFT)
#define MTL_TXQ_OP_TQS_SHIFT        (16)      /* Bits 24:16 TX Queue Size */
#define MTL_TXQ_OP_TQS_MASK         (0x1FF << MTL_TXQ_OP_TQS_SHIFT)
#define MTL_TXQ_OP_TQS(n)           ((n) << MTL_TXQ_OP_TQS_SHIFT)

/* MTL RXQ0 Operation Mode (0x0D30) */

#define MTL_RXQ_OP_RTC_SHIFT        (0)       /* Bits 1:0 RX Threshold */
#define MTL_RXQ_OP_RTC_MASK         (0x3 << MTL_RXQ_OP_RTC_SHIFT)
#define MTL_RXQ_OP_FUP              (1 << 3)  /* Forward Undersized Good Frames */
#define MTL_RXQ_OP_FEP              (1 << 4)  /* Forward Error Packets */
#define MTL_RXQ_OP_RSF              (1 << 5)  /* RX Store-and-Forward */
#define MTL_RXQ_OP_DIS_TCP_EF       (1 << 6)  /* Disable Dropping of TCP/IP CSE err */
#define MTL_RXQ_OP_EHFC             (1 << 7)  /* Enable Hardware Flow Control */
#define MTL_RXQ_OP_RFA_SHIFT        (8)       /* Threshold for Activating */
#define MTL_RXQ_OP_RFD_SHIFT        (14)      /* Threshold for Deactivating */
#define MTL_RXQ_OP_RQS_SHIFT        (20)      /* Bits 28:20 RX Queue Size */
#define MTL_RXQ_OP_RQS_MASK         (0x1FF << MTL_RXQ_OP_RQS_SHIFT)
#define MTL_RXQ_OP_RQS(n)           ((n) << MTL_RXQ_OP_RQS_SHIFT)

/* MTL RXQ DMA Map 0 (0x0C30) - route RXQ0 -> DMA CH0 */

#define MTL_RXQ_DMA_MAP_Q0MDMACH_SHIFT (0)
#define MTL_RXQ_DMA_MAP_Q0MDMACH_MASK  (0x7 << MTL_RXQ_DMA_MAP_Q0MDMACH_SHIFT)
#define MTL_RXQ_DMA_MAP_Q0DDMACH       (1 << 4)  /* Q0 Dynamic DMA Channel */

/* Descriptors */

/* TDES0 (Read Format) */
#define TDES0_BUF1AP                (0xFFFFFFFF) /* Buffer 1 Address Pointer */

/* TDES1 (Read Format) */
#define TDES1_BUF2AP                (0xFFFFFFFF) /* Buffer 2 Address Pointer */

/* TDES2 (Read Format) */
#define TDES2_B1L_SHIFT             (0)
#define TDES2_B1L_MASK              (0x3FFF << TDES2_B1L_SHIFT) /* Buffer 1 Length */
#define TDES2_VTIR_SHIFT            (14)
#define TDES2_VTIR_MASK             (0x3 << TDES2_VTIR_SHIFT) /* VLAN Tag Insertion/Replacement */
#define TDES2_B2L_SHIFT             (16)
#define TDES2_B2L_MASK              (0x3FFF << TDES2_B2L_SHIFT) /* Buffer 2 Length */
#define TDES2_TTSE                  (1 << 30) /* Transmit Timestamp Enable */
#define TDES2_IOC                   (1 << 31) /* Interrupt on Completion */

/* TDES3 (Read Format) */
#define TDES3_FL_SHIFT              (0)
#define TDES3_FL_MASK               (0x7FFF << TDES3_FL_SHIFT) /* Frame Length */
#define TDES3_CIC_SHIFT             (16)
#define TDES3_CIC_MASK              (0x3 << TDES3_CIC_SHIFT) /* Checksum Insertion Control */
#define TDES3_TSE                   (1 << 18) /* TCP Segmentation Enable */
#define TDES3_SLOTNUM_SHIFT         (19)
#define TDES3_SLOTNUM_MASK          (0xF << TDES3_SLOTNUM_SHIFT) /* Slot Number Control */
#define TDES3_SAIC_SHIFT            (23)
#define TDES3_SAIC_MASK             (0x7 << TDES3_SAIC_SHIFT) /* SA Insertion Control */
#define TDES3_CPC_SHIFT             (26)
#define TDES3_CPC_MASK              (0x3 << TDES3_CPC_SHIFT) /* CRC Pad Control */
#define TDES3_LD                    (1 << 28) /* Last Descriptor */
#define TDES3_FD                    (1 << 29) /* First Descriptor */
#define TDES3_CTXT                  (1 << 30) /* Context Type */
#define TDES3_OWN                   (1 << 31) /* Own Bit */

/* RDES3 Read Format (CPU -> DMA) */
#define RDES3_BUF1V                 (1 << 24) /* Buffer 1 Address Valid */
#define RDES3_BUF2V                 (1 << 25) /* Buffer 2 Address Valid */
#define RDES3_IOC                   (1 << 30) /* Interrupt on Completion */
#define RDES3_OWN                   (1 << 31) /* Own Bit (1=DMA owns) */

/* RDES3 Write-Back Format (DMA -> CPU) */
#define RDES3_FL_SHIFT              (0)
#define RDES3_FL_MASK               (0x7FFF << RDES3_FL_SHIFT) /* Frame Length */
#define RDES3_ES                    (1 << 15) /* Error Summary */
#define RDES3_LD                    (1 << 28) /* Last Descriptor */
#define RDES3_FD                    (1 << 29) /* First Descriptor */
#define RDES3_CTXT                  (1 << 30) /* Context Descriptor */

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_ETHER_H */

/****************************************************************************
 * arch/arm/src/ra8/hardware/ra_etherc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA_ETHERC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA_ETHERC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ETHERC Base Address */
#ifndef RA_ETHERC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define RA_ETHERC_BASE           0x40354100
#else
#define RA_ETHERC_BASE           0x50354100
#endif
#endif

/* ETHERC Register Offsets */

#define RA_ETHERC_ECMR_OFFSET     0x00000000  /* ETHERC Mode Register */
#define RA_ETHERC_RFLR_OFFSET     0x00000008  /* Receive Frame Maximum Length Register */
#define RA_ETHERC_ECSR_OFFSET     0x00000010  /* ETHERC Status Register */
#define RA_ETHERC_ECSIPR_OFFSET     0x00000018  /* ETHERC Interrupt Enable Register */
#define RA_ETHERC_PIR_OFFSET     0x00000020  /* PHY Interface Register */
#define RA_ETHERC_PSR_OFFSET     0x00000028  /* PHY Status Register */
#define RA_ETHERC_RDMLR_OFFSET     0x00000040  /* Random Number Generation Counter Upper Limit Setting Register */
#define RA_ETHERC_IPGR_OFFSET     0x00000050  /* Interpacket Gap Register */
#define RA_ETHERC_APR_OFFSET     0x00000054  /* Automatic PAUSE Frame Register */
#define RA_ETHERC_MPR_OFFSET     0x00000058  /* Manual PAUSE Frame Register */
#define RA_ETHERC_RFCF_OFFSET     0x00000060  /* Received PAUSE Frame Counter */
#define RA_ETHERC_TPAUSER_OFFSET     0x00000064  /* PAUSE Frame Retransmit Count Setting Register */
#define RA_ETHERC_TPAUSECR_OFFSET     0x00000068  /* PAUSE Frame Retransmit Counter */
#define RA_ETHERC_BCFRR_OFFSET     0x0000006c  /* Broadcast Frame Receive Count Setting Register */
#define RA_ETHERC_MAHR_OFFSET     0x000000c0  /* MAC Address Upper Bit Register */
#define RA_ETHERC_MALR_OFFSET     0x000000c8  /* MAC Address Lower Bit Register */
#define RA_ETHERC_TROCR_OFFSET     0x000000d0  /* Transmit Retry Over Counter Register */
#define RA_ETHERC_CDCR_OFFSET     0x000000d4  /* Late Collision Detect Counter Register */
#define RA_ETHERC_LCCR_OFFSET     0x000000d8  /* Lost Carrier Counter Register */
#define RA_ETHERC_CNDCR_OFFSET     0x000000dc  /* Carrier Not Detect Counter Register */
#define RA_ETHERC_CEFCR_OFFSET     0x000000e4  /* CRC Error Frame Receive Counter Register */
#define RA_ETHERC_FRECR_OFFSET     0x000000e8  /* Frame Receive Error Counter Register */
#define RA_ETHERC_TSFRCR_OFFSET     0x000000ec  /* Too-Short Frame Receive Counter Register */
#define RA_ETHERC_TLFRCR_OFFSET     0x000000f0  /* Too-Long Frame Receive Counter Register */
#define RA_ETHERC_RFCR_OFFSET     0x000000f4  /* Received Alignment Error Frame Counter Register */
#define RA_ETHERC_MAFCR_OFFSET     0x000000f8  /* Multicast Address Frame Receive Counter Register */

/* Register bit definitions */
/* ECMR Register bit definitions */
#define ETHERC_ECMR_PRM          (1 << 0)  /* Promiscuous Mode */

#define ETHERC_ECMR_DM          (1 << 1)  /* Duplex Mode */

#define ETHERC_ECMR_RTM          (1 << 2)  /* Bit Rate */

#define ETHERC_ECMR_ILB          (1 << 3)  /* Internal Loopback Mode */

#define ETHERC_ECMR_TE          (1 << 5)  /* Transmission Enable */

#define ETHERC_ECMR_RE          (1 << 6)  /* Reception Enable */

#define ETHERC_ECMR_MPDE          (1 << 9)  /* Magic Packet Detection Enable */

#define ETHERC_ECMR_PRCEF          (1 << 12)  /* CRC Error Frame Receive Mode */

#define ETHERC_ECMR_TXF          (1 << 16)  /* Transmit Flow Control Operating Mode */

#define ETHERC_ECMR_RXF          (1 << 17)  /* Receive Flow Control Operating Mode */

#define ETHERC_ECMR_PFR          (1 << 18)  /* PAUSE Frame Receive Mode */

#define ETHERC_ECMR_ZPF          (1 << 19)  /* 0 Time PAUSE Frame Enable */

#define ETHERC_ECMR_TPC          (1 << 20)  /* PAUSE Frame Transmit */

/* RFLR Register bit definitions */
#define ETHERC_RFLR_RFL_SHIFT    (0)       /* Receive Frame Maximum Length */
#define ETHERC_RFLR_RFL_MASK     (0xfff)

/* ECSR Register bit definitions */
#define ETHERC_ECSR_ICD          (1 << 0)  /* False Carrier Detect Flag */

#define ETHERC_ECSR_MPD          (1 << 1)  /* Magic Packet Detect Flag */

#define ETHERC_ECSR_LCHNG          (1 << 2)  /* Link Signal Change Flag */

#define ETHERC_ECSR_PSRTO          (1 << 4)  /* PAUSE Frame Retransmit Over Flag */

#define ETHERC_ECSR_BFR          (1 << 5)  /* Continuous Broadcast Frame Reception Flag */

/* ECSIPR Register bit definitions */
#define ETHERC_ECSIPR_ICDIP          (1 << 0)  /* False Carrier Detect Interrupt Enable */

#define ETHERC_ECSIPR_MPDIP          (1 << 1)  /* Magic Packet Detect Interrupt Enable */

#define ETHERC_ECSIPR_LCHNGIP          (1 << 2)  /* LINK Signal Change Interrupt Enable */

#define ETHERC_ECSIPR_PSRTOIP          (1 << 4)  /* PAUSE Frame Retransmit Over Interrupt Enable */

#define ETHERC_ECSIPR_BFSIPR          (1 << 5)  /* Continuous Broadcast Frame Reception Interrupt Enable */

/* PIR Register bit definitions */
#define ETHERC_PIR_MDC          (1 << 0)  /* MII/RMII Management Data Clock */

#define ETHERC_PIR_MMD          (1 << 1)  /* MII/RMII Management Mode */

#define ETHERC_PIR_MDO          (1 << 2)  /* MII/RMII Management Data-Out */

#define ETHERC_PIR_MDI          (1 << 3)  /* MII/RMII Management Data-In */

/* PSR Register bit definitions */
#define ETHERC_PSR_LMON          (1 << 0)  /* ET0_LINKSTA Pin Status Flag */

/* RDMLR Register bit definitions */
#define ETHERC_RDMLR_RMD_SHIFT    (0)       /* Random Number Generation Counter */
#define ETHERC_RDMLR_RMD_MASK     (0xfffff)

/* IPGR Register bit definitions */
#define ETHERC_IPGR_IPG_SHIFT    (0)       /*  */
#define ETHERC_IPGR_IPG_MASK     (0x1f)

/* APR Register bit definitions */
#define ETHERC_APR_AP_SHIFT    (0)       /* Automatic PAUSE Time Setting */
#define ETHERC_APR_AP_MASK     (0xffff)

/* MPR Register bit definitions */
#define ETHERC_MPR_MP_SHIFT    (0)       /* Manual PAUSE Time Setting */
#define ETHERC_MPR_MP_MASK     (0xffff)

/* RFCF Register bit definitions */
#define ETHERC_RFCF_RPAUSE_SHIFT    (0)       /* Received PAUSE Frame Count */
#define ETHERC_RFCF_RPAUSE_MASK     (0xff)

/* TPAUSER Register bit definitions */
#define ETHERC_TPAUSER_TPAUSE_SHIFT    (0)       /*  */
#define ETHERC_TPAUSER_TPAUSE_MASK     (0xffff)

/* TPAUSECR Register bit definitions */
#define ETHERC_TPAUSECR_TXP_SHIFT    (0)       /* PAUSE Frame Retransmit Count */
#define ETHERC_TPAUSECR_TXP_MASK     (0xff)

/* BCFRR Register bit definitions */
#define ETHERC_BCFRR_BCF_SHIFT    (0)       /*  */
#define ETHERC_BCFRR_BCF_MASK     (0xffff)

/* MAHR Register bit definitions */
#define ETHERC_MAHR_MAHR_SHIFT    (0)       /* MAC Address Upper Bit */
#define ETHERC_MAHR_MAHR_MASK     (0xffffffff)

/* MALR Register bit definitions */
#define ETHERC_MALR_MALR_SHIFT    (0)       /* MAC Address Lower Bit */
#define ETHERC_MALR_MALR_MASK     (0xffff)

/* TROCR Register bit definitions */
#define ETHERC_TROCR_TROCR_SHIFT    (0)       /* Transmit Retry Over Counter */
#define ETHERC_TROCR_TROCR_MASK     (0xffffffff)

/* CDCR Register bit definitions */
#define ETHERC_CDCR_CDCR_SHIFT    (0)       /* Late Collision Detect Counter */
#define ETHERC_CDCR_CDCR_MASK     (0xffffffff)

/* LCCR Register bit definitions */
#define ETHERC_LCCR_LCCR_SHIFT    (0)       /* Lost Carrier Counter */
#define ETHERC_LCCR_LCCR_MASK     (0xffffffff)

/* CNDCR Register bit definitions */
#define ETHERC_CNDCR_CNDCR_SHIFT    (0)       /* Carrier Not Detect Counter */
#define ETHERC_CNDCR_CNDCR_MASK     (0xffffffff)

/* CEFCR Register bit definitions */
#define ETHERC_CEFCR_CEFCR_SHIFT    (0)       /* CRC Error Frame Receive Counter */
#define ETHERC_CEFCR_CEFCR_MASK     (0xffffffff)

/* FRECR Register bit definitions */
#define ETHERC_FRECR_FRECR_SHIFT    (0)       /* Frame Receive Error Counter */
#define ETHERC_FRECR_FRECR_MASK     (0xffffffff)

/* TSFRCR Register bit definitions */
#define ETHERC_TSFRCR_TSFRCR_SHIFT    (0)       /* Too-Short Frame Receive Counter */
#define ETHERC_TSFRCR_TSFRCR_MASK     (0xffffffff)

/* TLFRCR Register bit definitions */
#define ETHERC_TLFRCR_TLFRCR_SHIFT    (0)       /* Too-Long Frame Receive Counter */
#define ETHERC_TLFRCR_TLFRCR_MASK     (0xffffffff)

/* RFCR Register bit definitions */
#define ETHERC_RFCR_RFCR_SHIFT    (0)       /* Received Alignment Error Frame Counter */
#define ETHERC_RFCR_RFCR_MASK     (0xffffffff)

/* MAFCR Register bit definitions */
#define ETHERC_MAFCR_MAFCR_SHIFT    (0)       /* Multicast Address Frame Receive Counter */
#define ETHERC_MAFCR_MAFCR_MASK     (0xffffffff)


/* Maximum number of channels */

#define ETHERC_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA_ETHERC_H */

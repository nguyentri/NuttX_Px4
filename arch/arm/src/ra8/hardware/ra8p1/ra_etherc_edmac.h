/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_etherc_edmac.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ETHERC_EDMAC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ETHERC_EDMAC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ETHERC_EDMAC Base Address */
#ifndef R_ETHERC_EDMAC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_ETHERC_EDMAC_BASE           0x40354000
#else
#define R_ETHERC_EDMAC_BASE           0x50354000
#endif
#endif

/* ETHERC_EDMAC Register Offsets */

#define R_ETHERC_EDMAC_EDMR_OFFSET                0x00000000  /* EDMAC Mode Register */
#define R_ETHERC_EDMAC_EDTRR_OFFSET               0x00000008  /* EDMAC Transmit Request Register */
#define R_ETHERC_EDMAC_EDRRR_OFFSET               0x00000010  /* EDMAC Receive Request Register */
#define R_ETHERC_EDMAC_TDLAR_OFFSET               0x00000018  /* Transmit Descriptor List Start Address Register */
#define R_ETHERC_EDMAC_RDLAR_OFFSET               0x00000020  /* Receive Descriptor List Start Address Register */
#define R_ETHERC_EDMAC_EESR_OFFSET                0x00000028  /* ETHERC/EDMAC Status Register */
#define R_ETHERC_EDMAC_EESIPR_OFFSET              0x00000030  /* ETHERC/EDMAC Status Interrupt Enable Register */
#define R_ETHERC_EDMAC_TRSCER_OFFSET              0x00000038  /* ETHERC/EDMAC Transmit/Receive Status Copy Enable Register */
#define R_ETHERC_EDMAC_RMFCR_OFFSET               0x00000040  /* Missed-Frame Counter Register */
#define R_ETHERC_EDMAC_TFTR_OFFSET                0x00000048  /* Transmit FIFO Threshold Register */
#define R_ETHERC_EDMAC_FDR_OFFSET                 0x00000050  /* Transmit FIFO Threshold Register */
#define R_ETHERC_EDMAC_RMCR_OFFSET                0x00000058  /* Receive Method Control Register */
#define R_ETHERC_EDMAC_TFUCR_OFFSET               0x00000064  /* Transmit FIFO Underflow Counter */
#define R_ETHERC_EDMAC_RFOCR_OFFSET               0x00000068  /* Receive FIFO Overflow Counter */
#define R_ETHERC_EDMAC_IOSR_OFFSET                0x0000006c  /* Independent Output Signal Setting Register */
#define R_ETHERC_EDMAC_FCFTR_OFFSET               0x00000070  /* Flow Control Start FIFO Threshold Setting Register */
#define R_ETHERC_EDMAC_RPADIR_OFFSET              0x00000078  /* Receive Data Padding Insert Register */
#define R_ETHERC_EDMAC_TRIMD_OFFSET               0x0000007c  /* Transmit Interrupt Setting Register */
#define R_ETHERC_EDMAC_RBWAR_OFFSET               0x000000c8  /* Receive Buffer Write Address Register */
#define R_ETHERC_EDMAC_RDFAR_OFFSET               0x000000cc  /* Receive Descriptor Fetch Address Register */
#define R_ETHERC_EDMAC_TBRAR_OFFSET               0x000000d4  /* Transmit Buffer Read Address Register */
#define R_ETHERC_EDMAC_TDFAR_OFFSET               0x000000d8  /* Transmit Descriptor Fetch Address Register */

/* ETHERC_EDMAC Register Addresses */

#define R_ETHERC_EDMAC_EDMR                       (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_EDMR_OFFSET)
#define R_ETHERC_EDMAC_EDTRR                      (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_EDTRR_OFFSET)
#define R_ETHERC_EDMAC_EDRRR                      (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_EDRRR_OFFSET)
#define R_ETHERC_EDMAC_TDLAR                      (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_TDLAR_OFFSET)
#define R_ETHERC_EDMAC_RDLAR                      (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_RDLAR_OFFSET)
#define R_ETHERC_EDMAC_EESR                       (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_EESR_OFFSET)
#define R_ETHERC_EDMAC_EESIPR                     (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_EESIPR_OFFSET)
#define R_ETHERC_EDMAC_TRSCER                     (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_TRSCER_OFFSET)
#define R_ETHERC_EDMAC_RMFCR                      (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_RMFCR_OFFSET)
#define R_ETHERC_EDMAC_TFTR                       (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_TFTR_OFFSET)
#define R_ETHERC_EDMAC_FDR                        (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_FDR_OFFSET)
#define R_ETHERC_EDMAC_RMCR                       (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_RMCR_OFFSET)
#define R_ETHERC_EDMAC_TFUCR                      (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_TFUCR_OFFSET)
#define R_ETHERC_EDMAC_RFOCR                      (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_RFOCR_OFFSET)
#define R_ETHERC_EDMAC_IOSR                       (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_IOSR_OFFSET)
#define R_ETHERC_EDMAC_FCFTR                      (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_FCFTR_OFFSET)
#define R_ETHERC_EDMAC_RPADIR                     (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_RPADIR_OFFSET)
#define R_ETHERC_EDMAC_TRIMD                      (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_TRIMD_OFFSET)
#define R_ETHERC_EDMAC_RBWAR                      (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_RBWAR_OFFSET)
#define R_ETHERC_EDMAC_RDFAR                      (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_RDFAR_OFFSET)
#define R_ETHERC_EDMAC_TBRAR                      (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_TBRAR_OFFSET)
#define R_ETHERC_EDMAC_TDFAR                      (R_ETHERC_EDMAC_BASE + R_ETHERC_EDMAC_TDFAR_OFFSET)

/* Register bit definitions */
/* EDMR Register bit definitions */
#define R_ETHERC_EDMAC_EDMR_DE                    (1 << 6)  /* Big Endian Mode/Little Endian ModeNOTE: This setting applies to data for the transmit/receive buffer. It does not apply to transmit/receive descriptors and registers. */

#define R_ETHERC_EDMAC_EDMR_DL_SHIFT              (4)  /* Transmit/Receive DescriptorLength */
#define R_ETHERC_EDMAC_EDMR_DL_MASK               0x30
#  define R_ETHERC_EDMAC_EDMR_DL_00                       (0 << R_ETHERC_EDMAC_EDMR_DL_SHIFT)  /* 16 bytes */
#  define R_ETHERC_EDMAC_EDMR_DL_01                       (1 << R_ETHERC_EDMAC_EDMR_DL_SHIFT)  /* 32 bytes */
#  define R_ETHERC_EDMAC_EDMR_DL_10                       (2 << R_ETHERC_EDMAC_EDMR_DL_SHIFT)  /* 64 bytes */
#  define R_ETHERC_EDMAC_EDMR_DL_11                       (3 << R_ETHERC_EDMAC_EDMR_DL_SHIFT)  /* 16 bytes */

#define R_ETHERC_EDMAC_EDMR_SWR                   (1 << 0)  /* Software Reset */

/* EDTRR Register bit definitions */
#define R_ETHERC_EDMAC_EDTRR_TR                   (1 << 0)  /* Transmit Request */

/* EDRRR Register bit definitions */
#define R_ETHERC_EDMAC_EDRRR_RR                   (1 << 0)  /* Receive Request */

/* TDLAR Register bit definitions */
#define R_ETHERC_EDMAC_TDLAR_TDLAR_SHIFT          (0)  /* The start address of the transmit descriptor list is set. Set the start address according to the descriptor length selected by the EDMR.DL[1:0] bits.16-byte boundary: Lower 4 bits = 0000b32-byte boundary: Lower 5 bits = 00000b64-byte boundary: Lower 6 bits = 000000b */
#define R_ETHERC_EDMAC_TDLAR_TDLAR_MASK           0xffffffff

/* RDLAR Register bit definitions */
#define R_ETHERC_EDMAC_RDLAR_RDLAR_SHIFT          (0)  /* The start address of the receive descriptor list is set. Set the start address according to the descriptor length selected by the EDMR.DL[1:0] bits.16-byte boundary: Lower 4 bits = 0000b32-byte boundary: Lower 5 bits = 00000b64-byte boundary: Lower 6 bits = 000000b */
#define R_ETHERC_EDMAC_RDLAR_RDLAR_MASK           0xffffffff

/* EESR Register bit definitions */
#define R_ETHERC_EDMAC_EESR_TWB                   (1 << 30)  /* Write-Back Complete Flag */

#define R_ETHERC_EDMAC_EESR_TABT                  (1 << 26)  /* Transmit Abort Detect Flag */

#define R_ETHERC_EDMAC_EESR_RABT                  (1 << 25)  /* Receive Abort Detect Flag */

#define R_ETHERC_EDMAC_EESR_RFCOF                 (1 << 24)  /* Receive Frame Counter Overflow Flag */

#define R_ETHERC_EDMAC_EESR_ADE                   (1 << 23)  /* Address Error Flag */

#define R_ETHERC_EDMAC_EESR_ECI                   (1 << 22)  /* ETHERC Status Register Source FlagNOTE: When the source in the ETHERCn.ECSR register is cleared, the ECI flag is also cleared. */

#define R_ETHERC_EDMAC_EESR_TC                    (1 << 21)  /* Frame Transfer Complete Flag */

#define R_ETHERC_EDMAC_EESR_TDE                   (1 << 20)  /* Transmit Descriptor Empty Flag */

#define R_ETHERC_EDMAC_EESR_TFUF                  (1 << 19)  /* Transmit FIFO Underflow Flag */

#define R_ETHERC_EDMAC_EESR_FR                    (1 << 18)  /* Frame Receive Flag */

#define R_ETHERC_EDMAC_EESR_RDE                   (1 << 17)  /* Receive Descriptor Empty Flag */

#define R_ETHERC_EDMAC_EESR_RFOF                  (1 << 16)  /* Receive FIFO Overflow Flag */

#define R_ETHERC_EDMAC_EESR_CND                   (1 << 11)  /* Carrier Not Detect Flag */

#define R_ETHERC_EDMAC_EESR_DLC                   (1 << 10)  /* Loss of Carrier Detect Flag */

#define R_ETHERC_EDMAC_EESR_CD                    (1 << 9)  /* Late Collision Detect Flag */

#define R_ETHERC_EDMAC_EESR_TRO                   (1 << 8)  /* Transmit Retry Over Flag */

#define R_ETHERC_EDMAC_EESR_RMAF                  (1 << 7)  /* Multicast Address Frame Receive Flag */

#define R_ETHERC_EDMAC_EESR_RRF                   (1 << 4)  /* Alignment Error Flag */

#define R_ETHERC_EDMAC_EESR_RTLF                  (1 << 3)  /* Frame-Too-Long Error Flag */

#define R_ETHERC_EDMAC_EESR_RTSF                  (1 << 2)  /* Frame-Too-Short Error Flag */

#define R_ETHERC_EDMAC_EESR_PRE                   (1 << 1)  /* PHY-LSI Receive Error Flag */

#define R_ETHERC_EDMAC_EESR_CERF                  (1 << 0)  /* CRC Error Flag */

/* EESIPR Register bit definitions */
#define R_ETHERC_EDMAC_EESIPR_TWBIP               (1 << 30)  /* Write-Back Complete Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_TABTIP              (1 << 26)  /* Transmit Abort Detect Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_RABTIP              (1 << 25)  /* Receive Abort Detect Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_RFCOFIP             (1 << 24)  /* Receive Frame Counter Overflow Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_ADEIP               (1 << 23)  /* Address Error Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_ECIIP               (1 << 22)  /* ETHERC Status Register Source Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_TCIP                (1 << 21)  /* Frame Transfer Complete Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_TDEIP               (1 << 20)  /* Transmit Descriptor Empty Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_TFUFIP              (1 << 19)  /* Transmit FIFO Underflow Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_FRIP                (1 << 18)  /* Frame Receive Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_RDEIP               (1 << 17)  /* Receive Descriptor Empty Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_RFOFIP              (1 << 16)  /* Receive FIFO Overflow Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_CNDIP               (1 << 11)  /* Carrier Not Detect Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_DLCIP               (1 << 10)  /* Loss of Carrier Detect Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_CDIP                (1 << 9)  /* Late Collision Detect Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_TROIP               (1 << 8)  /* Transmit Retry Over Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_RMAFIP              (1 << 7)  /* Multicast Address Frame Receive Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_RRFIP               (1 << 4)  /* Alignment Error Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_RTLFIP              (1 << 3)  /* Frame-Too-Long Error Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_RTSFIP              (1 << 2)  /* Frame-Too-Short Error Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_PREIP               (1 << 1)  /* PHY-LSI Receive Error Interrupt Request Enable */

#define R_ETHERC_EDMAC_EESIPR_CERFIP              (1 << 0)  /* CRC Error Interrupt Request Enable */

/* TRSCER Register bit definitions */
#define R_ETHERC_EDMAC_TRSCER_RMAFCE              (1 << 7)  /* RMAF Flag Copy Enable */

#define R_ETHERC_EDMAC_TRSCER_RRFCE               (1 << 4)  /* RRF Flag Copy Enable */

/* RMFCR Register bit definitions */
#define R_ETHERC_EDMAC_RMFCR_MFC_SHIFT            (0)  /* Missed-Frame CounterThese bits indicate the number of frames that are discarded and not transferred to the receive buffer during reception. */
#define R_ETHERC_EDMAC_RMFCR_MFC_MASK             0xffff

/* TFTR Register bit definitions */
#define R_ETHERC_EDMAC_TFTR_TFT_SHIFT             (0)  /* Transmit FIFO Threshold00Dh to 200h: The threshold is the set value multiplied by 4.  Example:     00Dh: 52 bytes     040h: 256 bytes     100h: 1024 bytes     200h: 2048 bytes */
#define R_ETHERC_EDMAC_TFTR_TFT_MASK              0x7ff
#  define R_ETHERC_EDMAC_TFTR_TFT_0X000                   (0 << R_ETHERC_EDMAC_TFTR_TFT_SHIFT)  /* Store and forward mode */

/* FDR Register bit definitions */
#define R_ETHERC_EDMAC_FDR_TFD_SHIFT              (8)  /* Receive FIFO Depth */
#define R_ETHERC_EDMAC_FDR_TFD_MASK               0x1f00
#  define R_ETHERC_EDMAC_FDR_TFD_01111                    (15 << R_ETHERC_EDMAC_FDR_TFD_SHIFT)  /* 4096 bytes */

#define R_ETHERC_EDMAC_FDR_RFD_SHIFT              (0)  /* Transmit FIFO Depth */
#define R_ETHERC_EDMAC_FDR_RFD_MASK               0x1f
#  define R_ETHERC_EDMAC_FDR_RFD_00111                    (7 << R_ETHERC_EDMAC_FDR_RFD_SHIFT)  /* 2048 bytes */

/* RMCR Register bit definitions */
#define R_ETHERC_EDMAC_RMCR_RNR                   (1 << 0)  /* Receive Request Reset */

/* TFUCR Register bit definitions */
#define R_ETHERC_EDMAC_TFUCR_UNDER_SHIFT          (0)  /* Transmit FIFO Underflow CountThese bits indicate how many times the transmit FIFO has underflowed. The counter stops when the counter value reaches FFFFh. */
#define R_ETHERC_EDMAC_TFUCR_UNDER_MASK           0xffff

/* RFOCR Register bit definitions */
#define R_ETHERC_EDMAC_RFOCR_OVER_SHIFT           (0)  /* Receive FIFO Overflow CountThese bits indicate how many times the receive FIFO has overflowed. The counter stops when the counter value reaches FFFFh. */
#define R_ETHERC_EDMAC_RFOCR_OVER_MASK            0xffff

/* IOSR Register bit definitions */
#define R_ETHERC_EDMAC_IOSR_ELB                   (1 << 0)  /* External Loopback Mode */

/* FCFTR Register bit definitions */
#define R_ETHERC_EDMAC_FCFTR_RFFO_SHIFT           (16)  /* Receive FIFO Frame PAUSE Output Threshold(When ((RFFO+1)x2) receive frames have been stored in the receive FIFO.) */
#define R_ETHERC_EDMAC_FCFTR_RFFO_MASK            0x70000
#  define R_ETHERC_EDMAC_FCFTR_RFFO_000                   (0 << R_ETHERC_EDMAC_FCFTR_RFFO_SHIFT)  /* When 2 receive frames have been stored in the receive FIFO. */
#  define R_ETHERC_EDMAC_FCFTR_RFFO_001                   (1 << R_ETHERC_EDMAC_FCFTR_RFFO_SHIFT)  /* When 4 receive frames have been stored in the receive FIFO. */
#  define R_ETHERC_EDMAC_FCFTR_RFFO_010                   (2 << R_ETHERC_EDMAC_FCFTR_RFFO_SHIFT)  /* When 6 receive frames have been stored in the receive FIFO. */
#  define R_ETHERC_EDMAC_FCFTR_RFFO_011                   (3 << R_ETHERC_EDMAC_FCFTR_RFFO_SHIFT)  /* When 8 receive frames have been stored in the receive FIFO. */
#  define R_ETHERC_EDMAC_FCFTR_RFFO_100                   (4 << R_ETHERC_EDMAC_FCFTR_RFFO_SHIFT)  /* When 10 receive frames have been stored in the receive FIFO. */
#  define R_ETHERC_EDMAC_FCFTR_RFFO_101                   (5 << R_ETHERC_EDMAC_FCFTR_RFFO_SHIFT)  /* When 12 receive frames have been stored in the receive FIFO. */
#  define R_ETHERC_EDMAC_FCFTR_RFFO_110                   (6 << R_ETHERC_EDMAC_FCFTR_RFFO_SHIFT)  /* When 14 receive frames have been stored in the receive FIFO. */
#  define R_ETHERC_EDMAC_FCFTR_RFFO_111                   (7 << R_ETHERC_EDMAC_FCFTR_RFFO_SHIFT)  /* When 16 receive frames have been stored in the receive FIFO. */

#define R_ETHERC_EDMAC_FCFTR_RFDO_SHIFT           (0)  /* Receive FIFO Data PAUSE Output Threshold(When  (RFDO+1)x256-32 bytes of data is stored in the receive FIFO.) */
#define R_ETHERC_EDMAC_FCFTR_RFDO_MASK            0x7
#  define R_ETHERC_EDMAC_FCFTR_RFDO_000                   (0 << R_ETHERC_EDMAC_FCFTR_RFDO_SHIFT)  /* When  224 ( 256 - 32) bytes of data is stored in the receive FIFO. */
#  define R_ETHERC_EDMAC_FCFTR_RFDO_001                   (1 << R_ETHERC_EDMAC_FCFTR_RFDO_SHIFT)  /* When  480 ( 512 - 32) bytes of data is stored in the receive FIFO. */
#  define R_ETHERC_EDMAC_FCFTR_RFDO_010                   (2 << R_ETHERC_EDMAC_FCFTR_RFDO_SHIFT)  /* When  736 ( 768 - 32) bytes of data is stored in the receive FIFO. */
#  define R_ETHERC_EDMAC_FCFTR_RFDO_011                   (3 << R_ETHERC_EDMAC_FCFTR_RFDO_SHIFT)  /* When  992 (1024 - 32) bytes of data is stored in the receive FIFO. */
#  define R_ETHERC_EDMAC_FCFTR_RFDO_100                   (4 << R_ETHERC_EDMAC_FCFTR_RFDO_SHIFT)  /* When 1248 (1280 - 32) bytes of data is stored in the receive FIFO. */
#  define R_ETHERC_EDMAC_FCFTR_RFDO_101                   (5 << R_ETHERC_EDMAC_FCFTR_RFDO_SHIFT)  /* When 1504 (1536 - 32) bytes of data is stored in the receive FIFO. */
#  define R_ETHERC_EDMAC_FCFTR_RFDO_110                   (6 << R_ETHERC_EDMAC_FCFTR_RFDO_SHIFT)  /* When 1760 (1792 - 32) bytes of data is stored in the receive FIFO. */
#  define R_ETHERC_EDMAC_FCFTR_RFDO_111                   (7 << R_ETHERC_EDMAC_FCFTR_RFDO_SHIFT)  /* When 2016 (2048 - 32) bytes of data is stored in the receive FIFO. */

/* RPADIR Register bit definitions */
#define R_ETHERC_EDMAC_RPADIR_PADS_SHIFT          (16)  /* Padding Size */
#define R_ETHERC_EDMAC_RPADIR_PADS_MASK           0x30000
#  define R_ETHERC_EDMAC_RPADIR_PADS_00                   (0 << R_ETHERC_EDMAC_RPADIR_PADS_SHIFT)  /* No padding is inserted. */
#  define R_ETHERC_EDMAC_RPADIR_PADS_01                   (1 << R_ETHERC_EDMAC_RPADIR_PADS_SHIFT)  /* 1 byte is inserted. */
#  define R_ETHERC_EDMAC_RPADIR_PADS_10                   (2 << R_ETHERC_EDMAC_RPADIR_PADS_SHIFT)  /* 2 bytes are inserted. */
#  define R_ETHERC_EDMAC_RPADIR_PADS_11                   (3 << R_ETHERC_EDMAC_RPADIR_PADS_SHIFT)  /* 3 bytes are inserted. */

#define R_ETHERC_EDMAC_RPADIR_PADR_SHIFT          (0)  /* Padding Slot */
#define R_ETHERC_EDMAC_RPADIR_PADR_MASK           0x3f
#  define R_ETHERC_EDMAC_RPADIR_PADR_00H                  (0 << R_ETHERC_EDMAC_RPADIR_PADR_SHIFT)  /* Padding is inserted at the head of received data. */

/* TRIMD Register bit definitions */
#define R_ETHERC_EDMAC_TRIMD_TIM                  (1 << 4)  /* Transmit Interrupt Mode */

#define R_ETHERC_EDMAC_TRIMD_TIS                  (1 << 0)  /* Transmit Interrupt EnableSet the EESR.TWB flag to 1 in the mode selected by the TIM bit to notify an interrupt. */

/* RBWAR Register bit definitions */
#define R_ETHERC_EDMAC_RBWAR_RBWAR_SHIFT          (0)  /* Receive Buffer Write Address RegisterThe RBWAR register indicates the last address that the EDMAC has written data to when writing to the receive buffer.Refer to the address indicated by the RBWAR register to recognize which address in the receive buffer the EDMAC is writing data to. Note that the address that the EDMAC is outputting to the receive buffer may not match the read value of the RBWAR register during data reception. */
#define R_ETHERC_EDMAC_RBWAR_RBWAR_MASK           0xffffffff

/* RDFAR Register bit definitions */
#define R_ETHERC_EDMAC_RDFAR_RDFAR_SHIFT          (0)  /* Receive Descriptor Fetch Address RegisterThe RDFAR register indicates the start address of the last fetched receive descriptor when the EDMAC fetches descriptor information from the receive descriptor.Refer to the address indicated by the RDFAR register to recognize which receive descriptor information the EDMAC is using for the current processing. Note that the address of the receive descriptor that the EDMAC fetches may not match the read value of the RDFAR register during data reception. */
#define R_ETHERC_EDMAC_RDFAR_RDFAR_MASK           0xffffffff

/* TBRAR Register bit definitions */
#define R_ETHERC_EDMAC_TBRAR_TBRAR_SHIFT          (0)  /* Transmit Buffer Read Address RegisterThe TBRAR register indicates the last address that the EDMAC has read data from when reading data from the transmit buffer.Refer to the address indicated by the TBRAR register to recognize which address in the transmit buffer the EDMAC is reading from. Note that the address that the EDMAC is outputting to the transmit buffer may not match the read value of the TBRAR register. */
#define R_ETHERC_EDMAC_TBRAR_TBRAR_MASK           0xffffffff

/* TDFAR Register bit definitions */
#define R_ETHERC_EDMAC_TDFAR_TDFAR_SHIFT          (0)  /* Transmit Descriptor Fetch Address RegisterThe TDFAR register indicates the start address of the last fetched transmit descriptor when the EDMAC fetches descriptor information from the transmit descriptor.Refer to the address indicated by the TDFAR register to recognize which transmit descriptor information the EDMAC is using for the current processing. Note that the address of the transmit descriptor that the EDMAC fetches may not match the read value of the TDFAR register. */
#define R_ETHERC_EDMAC_TDFAR_TDFAR_MASK           0xffffffff


/* Maximum number of channels */

#define ETHERC_EDMAC_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ETHERC_EDMAC_H */

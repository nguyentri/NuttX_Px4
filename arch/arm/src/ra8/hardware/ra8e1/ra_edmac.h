/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_edmac.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_EDMAC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_EDMAC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* EDMAC Base Address */
#ifndef R_EDMAC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_EDMAC_BASE           0x40354000
#else
#define R_EDMAC_BASE           0x50354000
#endif
#endif

/* EDMAC Register Offsets */

#define R_EDMAC_EDMR_OFFSET                       0x00000000  /* EDMAC Mode Register */
#define R_EDMAC_EDTRR_OFFSET                      0x00000008  /* EDMAC Transmit Request Register */
#define R_EDMAC_EDRRR_OFFSET                      0x00000010  /* EDMAC Receive Request Register */
#define R_EDMAC_TDLAR_OFFSET                      0x00000018  /* Transmit Descriptor List Start Address Register */
#define R_EDMAC_RDLAR_OFFSET                      0x00000020  /* Receive Descriptor List Start Address Register */
#define R_EDMAC_EESR_OFFSET                       0x00000028  /* ETHERC/EDMAC Status Register */
#define R_EDMAC_EESIPR_OFFSET                     0x00000030  /* ETHERC/EDMAC Status Interrupt Enable Register */
#define R_EDMAC_TRSCER_OFFSET                     0x00000038  /* ETHERC/EDMAC Transmit/Receive Status Copy Enable Register */
#define R_EDMAC_RMFCR_OFFSET                      0x00000040  /* Missed-Frame Counter Register */
#define R_EDMAC_TFTR_OFFSET                       0x00000048  /* Transmit FIFO Threshold Register */
#define R_EDMAC_FDR_OFFSET                        0x00000050  /* FIFO Depth Register */
#define R_EDMAC_RMCR_OFFSET                       0x00000058  /* Receive Method Control Register */
#define R_EDMAC_TFUCR_OFFSET                      0x00000064  /* Transmit FIFO Underflow Counter */
#define R_EDMAC_RFOCR_OFFSET                      0x00000068  /* Receive FIFO Overflow Counter */
#define R_EDMAC_IOSR_OFFSET                       0x0000006c  /* Independent Output Signal Setting Register */
#define R_EDMAC_FCFTR_OFFSET                      0x00000070  /* Flow Control Start FIFO Threshold Setting Register */
#define R_EDMAC_RPADIR_OFFSET                     0x00000078  /* Receive Data Padding Insert Register */
#define R_EDMAC_TRIMD_OFFSET                      0x0000007c  /* Transmit Interrupt Setting Register */
#define R_EDMAC_RBWAR_OFFSET                      0x000000c8  /* Receive Buffer Write Address Register */
#define R_EDMAC_RDFAR_OFFSET                      0x000000cc  /* Receive Descriptor Fetch Address Register */
#define R_EDMAC_TBRAR_OFFSET                      0x000000d4  /* Transmit Buffer Read Address Register */
#define R_EDMAC_TDFAR_OFFSET                      0x000000d8  /* Transmit Descriptor Fetch Address Register */

/* EDMAC Register Addresses */

#define R_EDMAC_EDMR                              (R_EDMAC_BASE + R_EDMAC_EDMR_OFFSET)
#define R_EDMAC_EDTRR                             (R_EDMAC_BASE + R_EDMAC_EDTRR_OFFSET)
#define R_EDMAC_EDRRR                             (R_EDMAC_BASE + R_EDMAC_EDRRR_OFFSET)
#define R_EDMAC_TDLAR                             (R_EDMAC_BASE + R_EDMAC_TDLAR_OFFSET)
#define R_EDMAC_RDLAR                             (R_EDMAC_BASE + R_EDMAC_RDLAR_OFFSET)
#define R_EDMAC_EESR                              (R_EDMAC_BASE + R_EDMAC_EESR_OFFSET)
#define R_EDMAC_EESIPR                            (R_EDMAC_BASE + R_EDMAC_EESIPR_OFFSET)
#define R_EDMAC_TRSCER                            (R_EDMAC_BASE + R_EDMAC_TRSCER_OFFSET)
#define R_EDMAC_RMFCR                             (R_EDMAC_BASE + R_EDMAC_RMFCR_OFFSET)
#define R_EDMAC_TFTR                              (R_EDMAC_BASE + R_EDMAC_TFTR_OFFSET)
#define R_EDMAC_FDR                               (R_EDMAC_BASE + R_EDMAC_FDR_OFFSET)
#define R_EDMAC_RMCR                              (R_EDMAC_BASE + R_EDMAC_RMCR_OFFSET)
#define R_EDMAC_TFUCR                             (R_EDMAC_BASE + R_EDMAC_TFUCR_OFFSET)
#define R_EDMAC_RFOCR                             (R_EDMAC_BASE + R_EDMAC_RFOCR_OFFSET)
#define R_EDMAC_IOSR                              (R_EDMAC_BASE + R_EDMAC_IOSR_OFFSET)
#define R_EDMAC_FCFTR                             (R_EDMAC_BASE + R_EDMAC_FCFTR_OFFSET)
#define R_EDMAC_RPADIR                            (R_EDMAC_BASE + R_EDMAC_RPADIR_OFFSET)
#define R_EDMAC_TRIMD                             (R_EDMAC_BASE + R_EDMAC_TRIMD_OFFSET)
#define R_EDMAC_RBWAR                             (R_EDMAC_BASE + R_EDMAC_RBWAR_OFFSET)
#define R_EDMAC_RDFAR                             (R_EDMAC_BASE + R_EDMAC_RDFAR_OFFSET)
#define R_EDMAC_TBRAR                             (R_EDMAC_BASE + R_EDMAC_TBRAR_OFFSET)
#define R_EDMAC_TDFAR                             (R_EDMAC_BASE + R_EDMAC_TDFAR_OFFSET)

/* Register bit definitions */
/* EDMR Register bit definitions */
#define R_EDMAC_EDMR_SWR                          (1 << 0)  /* Software Reset */

#define R_EDMAC_EDMR_DL_SHIFT                     (4)  /* Transmit/Receive Descriptor Length */
#define R_EDMAC_EDMR_DL_MASK                      0x30
#  define R_EDMAC_EDMR_DL_00                              (0 << R_EDMAC_EDMR_DL_SHIFT)  /* 16 bytes */
#  define R_EDMAC_EDMR_DL_01                              (1 << R_EDMAC_EDMR_DL_SHIFT)  /* 32 bytes */
#  define R_EDMAC_EDMR_DL_10                              (2 << R_EDMAC_EDMR_DL_SHIFT)  /* 64 bytes */
#  define R_EDMAC_EDMR_DL_11                              (3 << R_EDMAC_EDMR_DL_SHIFT)  /* 16 bytes. */

#define R_EDMAC_EDMR_DE                           (1 << 6)  /* Big Endian Mode/Little Endian Mode */

/* EDTRR Register bit definitions */
#define R_EDMAC_EDTRR_TR                          (1 << 0)  /* Transmit Request */

/* EDRRR Register bit definitions */
#define R_EDMAC_EDRRR_RR                          (1 << 0)  /* Receive Request */

/* EESR Register bit definitions */
#define R_EDMAC_EESR_CERF                         (1 << 0)  /* CRC Error Flag */

#define R_EDMAC_EESR_PRE                          (1 << 1)  /* PHY-LSI Receive Error Flag */

#define R_EDMAC_EESR_RTSF                         (1 << 2)  /* Frame-Too-Short Error Flag */

#define R_EDMAC_EESR_RTLF                         (1 << 3)  /* Frame-Too-Long Error Flag */

#define R_EDMAC_EESR_RRF                          (1 << 4)  /* Alignment Error Flag */

#define R_EDMAC_EESR_RMAF                         (1 << 7)  /* Multicast Address Frame Receive Flag */

#define R_EDMAC_EESR_TRO                          (1 << 8)  /* Transmit Retry Over Flag */

#define R_EDMAC_EESR_CD                           (1 << 9)  /* Late Collision Detect Flag */

#define R_EDMAC_EESR_DLC                          (1 << 10)  /* Loss of Carrier Detect Flag */

#define R_EDMAC_EESR_CND                          (1 << 11)  /* Carrier Not Detect Flag */

#define R_EDMAC_EESR_RFOF                         (1 << 16)  /* Receive FIFO Overflow Flag */

#define R_EDMAC_EESR_RDE                          (1 << 17)  /* Receive Descriptor Empty Flag */

#define R_EDMAC_EESR_FR                           (1 << 18)  /* Frame Receive Flag */

#define R_EDMAC_EESR_TFUF                         (1 << 19)  /* Transmit FIFO Underflow Flag */

#define R_EDMAC_EESR_TDE                          (1 << 20)  /* Transmit Descriptor Empty Flag */

#define R_EDMAC_EESR_TC                           (1 << 21)  /* Frame Transfer Complete Flag */

#define R_EDMAC_EESR_ECI                          (1 << 22)  /* ETHERC Status Register Source Flag */

#define R_EDMAC_EESR_ADE                          (1 << 23)  /* Address Error Flag */

#define R_EDMAC_EESR_RFCOF                        (1 << 24)  /* Receive Frame Counter Overflow Flag */

#define R_EDMAC_EESR_RABT                         (1 << 25)  /* Receive Abort Detect Flag */

#define R_EDMAC_EESR_TABT                         (1 << 26)  /* Transmit Abort Detect Flag */

#define R_EDMAC_EESR_TWB                          (1 << 30)  /* Write-Back Complete Flag */

/* EESIPR Register bit definitions */
#define R_EDMAC_EESIPR_CERFIP                     (1 << 0)  /* CRC Error Interrupt Request Enable */

#define R_EDMAC_EESIPR_PREIP                      (1 << 1)  /* PHY-LSI Receive Error Interrupt Request Enable */

#define R_EDMAC_EESIPR_RTSFIP                     (1 << 2)  /* Frame-Too-Short Error Interrupt Request Enable */

#define R_EDMAC_EESIPR_RTLFIP                     (1 << 3)  /* Frame-Too-Long Error Interrupt Request Enable */

#define R_EDMAC_EESIPR_RRFIP                      (1 << 4)  /* Alignment Error Interrupt Request Enable */

#define R_EDMAC_EESIPR_RMAFIP                     (1 << 7)  /* Multicast Address Frame Receive Interrupt Request Enable */

#define R_EDMAC_EESIPR_TROIP                      (1 << 8)  /* Transmit Retry Over Interrupt Request Enable */

#define R_EDMAC_EESIPR_CDIP                       (1 << 9)  /* Late Collision Detect Interrupt Request Enable */

#define R_EDMAC_EESIPR_DLCIP                      (1 << 10)  /* Loss of Carrier Detect Interrupt Request Enable */

#define R_EDMAC_EESIPR_CNDIP                      (1 << 11)  /* Carrier Not Detect Interrupt Request Enable */

#define R_EDMAC_EESIPR_RFOFIP                     (1 << 16)  /* Receive FIFO Overflow Interrupt Request Enable */

#define R_EDMAC_EESIPR_RDEIP                      (1 << 17)  /* Receive Descriptor Empty Interrupt Request Enable */

#define R_EDMAC_EESIPR_FRIP                       (1 << 18)  /* Frame Receive Interrupt Request Enable */

#define R_EDMAC_EESIPR_TFUFIP                     (1 << 19)  /* Transmit FIFO Underflow Interrupt Request Enable */

#define R_EDMAC_EESIPR_TDEIP                      (1 << 20)  /* Transmit Descriptor Empty Interrupt Request Enable */

#define R_EDMAC_EESIPR_TCIP                       (1 << 21)  /* Frame Transfer Complete Interrupt Request Enable */

#define R_EDMAC_EESIPR_ECIIP                      (1 << 22)  /* ETHERC Status Register Source Interrupt Request Enable */

#define R_EDMAC_EESIPR_ADEIP                      (1 << 23)  /* Address Error Interrupt Request Enable */

#define R_EDMAC_EESIPR_RFCOFIP                    (1 << 24)  /* Receive Frame Counter Overflow Interrupt Request Enable */

#define R_EDMAC_EESIPR_RABTIP                     (1 << 25)  /* Receive Abort Detect Interrupt Request Enable */

#define R_EDMAC_EESIPR_TABTIP                     (1 << 26)  /* Transmit Abort Detect Interrupt Request Enable */

#define R_EDMAC_EESIPR_TWBIP                      (1 << 30)  /* Write-Back Complete Interrupt Request Enable */

/* TRSCER Register bit definitions */
#define R_EDMAC_TRSCER_RRFCE                      (1 << 4)  /* RRF Flag Copy Enable */

#define R_EDMAC_TRSCER_RMAFCE                     (1 << 7)  /* RMAF Flag Copy Enable */

/* RMFCR Register bit definitions */
#define R_EDMAC_RMFCR_MFC_SHIFT                   (0)  /* Missed-Frame Counter */
#define R_EDMAC_RMFCR_MFC_MASK                    0xffff

/* TFTR Register bit definitions */
#define R_EDMAC_TFTR_TFT_SHIFT                    (0)  /* Transmit FIFO Threshold */
#define R_EDMAC_TFTR_TFT_MASK                     0x7ff

/* FDR Register bit definitions */
#define R_EDMAC_FDR_RFD_SHIFT                     (0)  /* Receive FIFO Depth */
#define R_EDMAC_FDR_RFD_MASK                      0x1f
#  define R_EDMAC_FDR_RFD_0X0F                            (0 << R_EDMAC_FDR_RFD_SHIFT)  /* 4096 bytes */

#define R_EDMAC_FDR_TFD_SHIFT                     (8)  /* Transmit FIFO Depth */
#define R_EDMAC_FDR_TFD_MASK                      0x1f00
#  define R_EDMAC_FDR_TFD_0X07                            (0 << R_EDMAC_FDR_TFD_SHIFT)  /* 2048 bytes */

/* RMCR Register bit definitions */
#define R_EDMAC_RMCR_RNR                          (1 << 0)  /* Receive Request Reset */

/* TFUCR Register bit definitions */
#define R_EDMAC_TFUCR_UNDER_SHIFT                 (0)  /* Transmit FIFO Underflow Count */
#define R_EDMAC_TFUCR_UNDER_MASK                  0xffff

/* RFOCR Register bit definitions */
#define R_EDMAC_RFOCR_OVER_SHIFT                  (0)  /* Receive FIFO Overflow Count */
#define R_EDMAC_RFOCR_OVER_MASK                   0xffff

/* IOSR Register bit definitions */
#define R_EDMAC_IOSR_ELB                          (1 << 0)  /* External Loopback Mode */

/* FCFTR Register bit definitions */
#define R_EDMAC_FCFTR_RFDO_SHIFT                  (0)  /* Receive FIFO Data PAUSE Output Threshold */
#define R_EDMAC_FCFTR_RFDO_MASK                   0x7

#define R_EDMAC_FCFTR_RFFO_SHIFT                  (16)  /* Receive FIFO Frame PAUSE Output Threshold */
#define R_EDMAC_FCFTR_RFFO_MASK                   0x70000

/* RPADIR Register bit definitions */
#define R_EDMAC_RPADIR_PADR_SHIFT                 (0)  /* Padding Slot */
#define R_EDMAC_RPADIR_PADR_MASK                  0x3f

#define R_EDMAC_RPADIR_PADS_SHIFT                 (16)  /* Padding Size */
#define R_EDMAC_RPADIR_PADS_MASK                  0x30000
#  define R_EDMAC_RPADIR_PADS_00                          (0 << R_EDMAC_RPADIR_PADS_SHIFT)  /* Do not insert padding */

/* TRIMD Register bit definitions */
#define R_EDMAC_TRIMD_TIS                         (1 << 0)  /* Transmit Interrupt Enable */

#define R_EDMAC_TRIMD_TIM                         (1 << 4)  /* Transmit Interrupt Mode */


/* Maximum number of channels */

#define EDMAC_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_EDMAC_H */

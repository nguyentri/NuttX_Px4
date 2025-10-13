/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_ssie.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SSIE_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SSIE_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SSIE Base Address */
#ifndef R_SSIE_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_SSIE_BASE           0x4025d000
#else
#define R_SSIE_BASE           0x5025d000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_SSIE_CH_STRIDE    0x00000100
#define R_SSIE_CH_BASE(ch)   (R_SSIE_BASE + ((uint32_t)(ch) * R_SSIE_CH_STRIDE))

/* SSIE Register Offsets */

#define R_SSIE_SSICR_OFFSET     0x00000000  /* Control Register */
#define R_SSIE_SSISR_OFFSET     0x00000004  /* Status Register */
#define R_SSIE_SSIFCR_OFFSET     0x00000010  /* FIFO Control Register */
#define R_SSIE_SSIFSR_OFFSET     0x00000014  /* FIFO Status Register */
#define R_SSIE_SSIFTDR_OFFSET     0x00000018  /* Transmit FIFO Data Register */
#define R_SSIE_SSIFRDR_OFFSET     0x0000001c  /* Receive FIFO Data Register */
#define R_SSIE_SSIOFR_OFFSET     0x00000020  /* Audio Format Register */
#define R_SSIE_SSISCR_OFFSET     0x00000024  /* Status Control Register */

/* SSIE Register Addresses */

#define R_SSIE_SSICR                 (R_SSIE_BASE + R_SSIE_SSICR_OFFSET)
#define R_SSIE_SSISR                 (R_SSIE_BASE + R_SSIE_SSISR_OFFSET)
#define R_SSIE_SSIFCR                 (R_SSIE_BASE + R_SSIE_SSIFCR_OFFSET)
#define R_SSIE_SSIFSR                 (R_SSIE_BASE + R_SSIE_SSIFSR_OFFSET)
#define R_SSIE_SSIFTDR                 (R_SSIE_BASE + R_SSIE_SSIFTDR_OFFSET)
#define R_SSIE_SSIFRDR                 (R_SSIE_BASE + R_SSIE_SSIFRDR_OFFSET)
#define R_SSIE_SSIOFR                 (R_SSIE_BASE + R_SSIE_SSIOFR_OFFSET)
#define R_SSIE_SSISCR                 (R_SSIE_BASE + R_SSIE_SSISCR_OFFSET)

/* Register bit definitions */
/* SSICR Register bit definitions */
#define R_SSIE_SSICR_REN                          (1 << 0)  /* Reception Enable */

#define R_SSIE_SSICR_TEN                          (1 << 1)  /* Transmission Enable */

#define R_SSIE_SSICR_MUEN                         (1 << 3)  /* Mute Enable */

#define R_SSIE_SSICR_CKDV_SHIFT                   (4)  /* Selects Bit Clock Division Ratio */
#define R_SSIE_SSICR_CKDV_MASK                    0xf0
#  define R_SSIE_SSICR_CKDV_0X0                           (0 << R_SSIE_SSICR_CKDV_SHIFT)  /* AUDIO_MCK */
#  define R_SSIE_SSICR_CKDV_0X1                           (0 << R_SSIE_SSICR_CKDV_SHIFT)  /* AUDIO_MCK/2 */
#  define R_SSIE_SSICR_CKDV_0X2                           (0 << R_SSIE_SSICR_CKDV_SHIFT)  /* AUDIO_MCK/4 */
#  define R_SSIE_SSICR_CKDV_0X3                           (0 << R_SSIE_SSICR_CKDV_SHIFT)  /* AUDIO_MCK/8 */
#  define R_SSIE_SSICR_CKDV_0X4                           (0 << R_SSIE_SSICR_CKDV_SHIFT)  /* AUDIO_MCK/16 */
#  define R_SSIE_SSICR_CKDV_0X5                           (0 << R_SSIE_SSICR_CKDV_SHIFT)  /* AUDIO_MCK/32 */
#  define R_SSIE_SSICR_CKDV_0X6                           (0 << R_SSIE_SSICR_CKDV_SHIFT)  /* AUDIO_MCK/64 */
#  define R_SSIE_SSICR_CKDV_0X7                           (0 << R_SSIE_SSICR_CKDV_SHIFT)  /* AUDIO_MCK/128 */
#  define R_SSIE_SSICR_CKDV_0X8                           (0 << R_SSIE_SSICR_CKDV_SHIFT)  /* AUDIO_MCK/6 */
#  define R_SSIE_SSICR_CKDV_0X9                           (0 << R_SSIE_SSICR_CKDV_SHIFT)  /* AUDIO_MCK/12 */
#  define R_SSIE_SSICR_CKDV_0XA                           (0 << R_SSIE_SSICR_CKDV_SHIFT)  /* AUDIO_MCK/24 */
#  define R_SSIE_SSICR_CKDV_0XB                           (0 << R_SSIE_SSICR_CKDV_SHIFT)  /* AUDIO_MCK/48 */
#  define R_SSIE_SSICR_CKDV_0XC                           (0 << R_SSIE_SSICR_CKDV_SHIFT)  /* AUDIO_MCK/96 */

#define R_SSIE_SSICR_DEL                          (1 << 8)  /* Selects Serial Data Delay */

#define R_SSIE_SSICR_PDTA                         (1 << 9)  /* Selects Placement Data Alignment */

#define R_SSIE_SSICR_SDTA                         (1 << 10)  /* Selects Serial Data Alignment */

#define R_SSIE_SSICR_SPDP                         (1 << 11)  /* Selects Serial Padding Polarity */

#define R_SSIE_SSICR_LRCKP                        (1 << 12)  /* Selects the Initial Value and Polarity of LR Clock/Frame Synchronization Signal */

#define R_SSIE_SSICR_BCKP                         (1 << 13)  /* Selects Bit Clock Polarity */

#define R_SSIE_SSICR_MST                          (1 << 14)  /* Master Enable */

#define R_SSIE_SSICR_SWL_SHIFT                    (16)  /* Selects System Word Length */
#define R_SSIE_SSICR_SWL_MASK                     0x70000
#  define R_SSIE_SSICR_SWL_000                            (0 << R_SSIE_SSICR_SWL_SHIFT)  /* 8 bits */
#  define R_SSIE_SSICR_SWL_001                            (1 << R_SSIE_SSICR_SWL_SHIFT)  /* 16 bits */
#  define R_SSIE_SSICR_SWL_010                            (2 << R_SSIE_SSICR_SWL_SHIFT)  /* 24 bits */
#  define R_SSIE_SSICR_SWL_011                            (3 << R_SSIE_SSICR_SWL_SHIFT)  /* 32 bits */
#  define R_SSIE_SSICR_SWL_100                            (4 << R_SSIE_SSICR_SWL_SHIFT)  /* 48 bits */
#  define R_SSIE_SSICR_SWL_101                            (5 << R_SSIE_SSICR_SWL_SHIFT)  /* 64 bits */
#  define R_SSIE_SSICR_SWL_110                            (6 << R_SSIE_SSICR_SWL_SHIFT)  /* 128 bits */
#  define R_SSIE_SSICR_SWL_111                            (7 << R_SSIE_SSICR_SWL_SHIFT)  /* 256 bits */

#define R_SSIE_SSICR_DWL_SHIFT                    (19)  /* Selects Data Word Length */
#define R_SSIE_SSICR_DWL_MASK                     0x380000
#  define R_SSIE_SSICR_DWL_000                            (0 << R_SSIE_SSICR_DWL_SHIFT)  /* 8 bits */
#  define R_SSIE_SSICR_DWL_001                            (1 << R_SSIE_SSICR_DWL_SHIFT)  /* 16 bits */
#  define R_SSIE_SSICR_DWL_010                            (2 << R_SSIE_SSICR_DWL_SHIFT)  /* 18 bits */
#  define R_SSIE_SSICR_DWL_011                            (3 << R_SSIE_SSICR_DWL_SHIFT)  /* 20 bits */
#  define R_SSIE_SSICR_DWL_100                            (4 << R_SSIE_SSICR_DWL_SHIFT)  /* 22 bits */
#  define R_SSIE_SSICR_DWL_101                            (5 << R_SSIE_SSICR_DWL_SHIFT)  /* 24 bits */
#  define R_SSIE_SSICR_DWL_110                            (6 << R_SSIE_SSICR_DWL_SHIFT)  /* 32 bits */
#  define R_SSIE_SSICR_DWL_111                            (7 << R_SSIE_SSICR_DWL_SHIFT)  /* Setting prohibited */

#define R_SSIE_SSICR_FRM_SHIFT                    (22)  /* Selects Frame Word Number */
#define R_SSIE_SSICR_FRM_MASK                     0xc00000

#define R_SSIE_SSICR_IIEN                         (1 << 25)  /* Idle Mode Interrupt Output Enable */

#define R_SSIE_SSICR_ROIEN                        (1 << 26)  /* Receive Overflow Interrupt Output Enable */

#define R_SSIE_SSICR_RUIEN                        (1 << 27)  /* Receive Underflow Interrupt Output Enable */

#define R_SSIE_SSICR_TOIEN                        (1 << 28)  /* Transmit Overflow Interrupt Output Enable */

#define R_SSIE_SSICR_TUIEN                        (1 << 29)  /* Transmit Underflow Interrupt Output Enable */

#define R_SSIE_SSICR_CKS                          (1 << 30)  /* Selects an Audio Clock for Master-mode Communication */

/* SSISR Register bit definitions */
#define R_SSIE_SSISR_IIRQ                         (1 << 25)  /* Idle Mode Status Flag */

#define R_SSIE_SSISR_ROIRQ                        (1 << 26)  /* Receive Overflow Error Status Flag */

#define R_SSIE_SSISR_RUIRQ                        (1 << 27)  /* Receive Underflow Error Status Flag */

#define R_SSIE_SSISR_TOIRQ                        (1 << 28)  /* Transmit Overflow Error Status Flag */

#define R_SSIE_SSISR_TUIRQ                        (1 << 29)  /* Transmit Underflow Error Status flag */

/* SSIFCR Register bit definitions */
#define R_SSIE_SSIFCR_RFRST                       (1 << 0)  /* Receive FIFO Data Register Reset */

#define R_SSIE_SSIFCR_TFRST                       (1 << 1)  /* Transmit FIFO Data Register Reset */

#define R_SSIE_SSIFCR_RIE                         (1 << 2)  /* Receive Data Full Interrupt Output Enable */

#define R_SSIE_SSIFCR_TIE                         (1 << 3)  /* Transmit Data Empty Interrupt Output Enable */

#define R_SSIE_SSIFCR_BSW                         (1 << 11)  /* Byte Swap Enable */

#define R_SSIE_SSIFCR_SSIRST                      (1 << 16)  /* Software Reset */

#define R_SSIE_SSIFCR_AUCKE                       (1 << 31)  /* AUDIO_MCK Enable in Mastermode Communication */

/* SSIFSR Register bit definitions */
#define R_SSIE_SSIFSR_RDF                         (1 << 0)  /* Receive Data Full Flag */

#define R_SSIE_SSIFSR_RDC_SHIFT                   (8)  /* Number of Receive FIFO Data Indication Flag */
#define R_SSIE_SSIFSR_RDC_MASK                    0x3f00

#define R_SSIE_SSIFSR_TDE                         (1 << 16)  /* Transmit Data Empty Flag */

#define R_SSIE_SSIFSR_TDC_SHIFT                   (24)  /* Number of Transmit FIFO Data Indication Flag */
#define R_SSIE_SSIFSR_TDC_MASK                    0x3f000000

/* SSIFTDR Register bit definitions */
#define R_SSIE_SSIFTDR_SSIFTDR_SHIFT              (0)  /* Transmit FIFO Data */
#define R_SSIE_SSIFTDR_SSIFTDR_MASK               0xffffffff

/* SSIFRDR Register bit definitions */
#define R_SSIE_SSIFRDR_SSIFRDR_SHIFT              (0)  /* Receive FIFO Data */
#define R_SSIE_SSIFRDR_SSIFRDR_MASK               0xffffffff

/* SSIOFR Register bit definitions */
#define R_SSIE_SSIOFR_OMOD_SHIFT                  (0)  /* Audio Format Select */
#define R_SSIE_SSIOFR_OMOD_MASK                   0x3
#  define R_SSIE_SSIOFR_OMOD_00                           (0 << R_SSIE_SSIOFR_OMOD_SHIFT)  /* I2S format */
#  define R_SSIE_SSIOFR_OMOD_01                           (1 << R_SSIE_SSIOFR_OMOD_SHIFT)  /* TDM format */
#  define R_SSIE_SSIOFR_OMOD_10                           (2 << R_SSIE_SSIOFR_OMOD_SHIFT)  /* Monaural format */
#  define R_SSIE_SSIOFR_OMOD_11                           (3 << R_SSIE_SSIOFR_OMOD_SHIFT)  /* Setting prohibited */

#define R_SSIE_SSIOFR_LRCONT                      (1 << 8)  /* Whether to Enable LRCK/FS Continuation */

#define R_SSIE_SSIOFR_BCKASTP                     (1 << 9)  /* Whether to Enable Stopping BCK Output When SSIE is in Idle Status */

/* SSISCR Register bit definitions */
#define R_SSIE_SSISCR_RDFS_SHIFT                  (0)  /* RDF Setting Condition Select */
#define R_SSIE_SSISCR_RDFS_MASK                   0x1f

#define R_SSIE_SSISCR_TDES_SHIFT                  (8)  /* TDE Setting Condition Select */
#define R_SSIE_SSISCR_TDES_MASK                   0x1f00


/* Maximum number of channels */

#define SSIE_MAX_CHANNELS    2

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SSIE_H */

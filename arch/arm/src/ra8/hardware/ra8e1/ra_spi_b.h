/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_spi_b.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SPI_B_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SPI_B_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SPI_B Base Address */
#ifndef R_SPI_B_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_SPI_B_BASE           0x4035c000
#else
#define R_SPI_B_BASE           0x5035c000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_SPI_B_CH_STRIDE    0x00000004
#define R_SPI_B_CH_BASE(ch)   (R_SPI_B_BASE + ((uint32_t)(ch) * R_SPI_B_CH_STRIDE))

/* SPI_B Register Offsets */

#define R_SPI_B_SPDR_OFFSET                       0x00000000  /* SPI Data Register */
#define R_SPI_B_SPDECR_OFFSET                     0x00000004  /* SPI Delay Control Register */
#define R_SPI_B_SPCR_OFFSET                       0x00000008  /* SPI Control Register */
#define R_SPI_B_SPCR2_OFFSET                      0x0000000c  /* SPI Control Register 2 */
#define R_SPI_B_SPCR3_OFFSET                      0x00000010  /* SPI Control Register 3 */
/* SPCMD%s Registers (0-7) */
#define R_SPI_B_SPCMD_OFFSET(m)                   (0x00000014 + ((m) * 0x00000004))  /* SPI Command Register */
#define R_SPI_B_SPCMD_INCREMENT                   0x00000004
#define R_SPI_B_SPDCR_OFFSET                      0x00000040  /* SPI Data Control Register */
#define R_SPI_B_SPDCR2_OFFSET                     0x00000044  /* SPI Data Control Register 2 */
#define R_SPI_B_SPSR_OFFSET                       0x00000050  /* SPI Status Register */
#define R_SPI_B_SPTFSR_OFFSET                     0x00000058  /* SPI Transfer FIFO Status Register */
#define R_SPI_B_SPRFSR_OFFSET                     0x0000005c  /* SPI Receive FIFO Status Register */
#define R_SPI_B_SPPSR_OFFSET                      0x00000060  /* SPI Polling Register */
#define R_SPI_B_SPSRC_OFFSET                      0x00000068  /* SPI Status Clear Register */
#define R_SPI_B_SPFCR_OFFSET                      0x0000006c  /* SPI FIFO Clear Register */

/* SPI_B Register Addresses */

#define R_SPI_B_SPDR                              (R_SPI_B_CH_BASE(n) + R_SPI_B_SPDR_OFFSET)
#define R_SPI_B_SPDECR                            (R_SPI_B_CH_BASE(n) + R_SPI_B_SPDECR_OFFSET)
#define R_SPI_B_SPCR                              (R_SPI_B_CH_BASE(n) + R_SPI_B_SPCR_OFFSET)
#define R_SPI_B_SPCR2                             (R_SPI_B_CH_BASE(n) + R_SPI_B_SPCR2_OFFSET)
#define R_SPI_B_SPCR3                             (R_SPI_B_CH_BASE(n) + R_SPI_B_SPCR3_OFFSET)
#define R_SPI_B_SPCMD(n)                          (R_SPI_B_CH_BASE(n) + R_SPI_B_SPCMD_OFFSET + (n)*0x00000004)
#define R_SPI_B_SPDCR                             (R_SPI_B_CH_BASE(n) + R_SPI_B_SPDCR_OFFSET)
#define R_SPI_B_SPDCR2                            (R_SPI_B_CH_BASE(n) + R_SPI_B_SPDCR2_OFFSET)
#define R_SPI_B_SPSR                              (R_SPI_B_CH_BASE(n) + R_SPI_B_SPSR_OFFSET)
#define R_SPI_B_SPTFSR                            (R_SPI_B_CH_BASE(n) + R_SPI_B_SPTFSR_OFFSET)
#define R_SPI_B_SPRFSR                            (R_SPI_B_CH_BASE(n) + R_SPI_B_SPRFSR_OFFSET)
#define R_SPI_B_SPPSR                             (R_SPI_B_CH_BASE(n) + R_SPI_B_SPPSR_OFFSET)
#define R_SPI_B_SPSRC                             (R_SPI_B_CH_BASE(n) + R_SPI_B_SPSRC_OFFSET)
#define R_SPI_B_SPFCR                             (R_SPI_B_CH_BASE(n) + R_SPI_B_SPFCR_OFFSET)

/* Register bit definitions */
/* SPDR Register bit definitions */
#define R_SPI_B_SPDR_SPD_SHIFT                    (0)  /* These bits are the interface with the buffers that hold data for transmission and reception by the SPI. */
#define R_SPI_B_SPDR_SPD_MASK                     0xffffffff

/* SPDECR Register bit definitions */
#define R_SPI_B_SPDECR_SCKDL_SHIFT                (0)  /* RSPCK Delay */
#define R_SPI_B_SPDECR_SCKDL_MASK                 0x7
#  define R_SPI_B_SPDECR_SCKDL_000                        (0 << R_SPI_B_SPDECR_SCKDL_SHIFT)  /* 1RSPCK */
#  define R_SPI_B_SPDECR_SCKDL_001                        (1 << R_SPI_B_SPDECR_SCKDL_SHIFT)  /* 2RSPCK */
#  define R_SPI_B_SPDECR_SCKDL_010                        (10 << R_SPI_B_SPDECR_SCKDL_SHIFT)  /* 3RSPCK */
#  define R_SPI_B_SPDECR_SCKDL_011                        (3 << R_SPI_B_SPDECR_SCKDL_SHIFT)  /* 4RSPCK */
#  define R_SPI_B_SPDECR_SCKDL_100                        (4 << R_SPI_B_SPDECR_SCKDL_SHIFT)  /* 5RSPCK */
#  define R_SPI_B_SPDECR_SCKDL_101                        (5 << R_SPI_B_SPDECR_SCKDL_SHIFT)  /* 6RSPCK */
#  define R_SPI_B_SPDECR_SCKDL_110                        (6 << R_SPI_B_SPDECR_SCKDL_SHIFT)  /* 7RSPCK */
#  define R_SPI_B_SPDECR_SCKDL_111                        (7 << R_SPI_B_SPDECR_SCKDL_SHIFT)  /* 8RSPCK */

#define R_SPI_B_SPDECR_SLNDL_SHIFT                (8)  /* SSL Negation Delay */
#define R_SPI_B_SPDECR_SLNDL_MASK                 0x700
#  define R_SPI_B_SPDECR_SLNDL_000                        (0 << R_SPI_B_SPDECR_SLNDL_SHIFT)  /* 1RSPCK */
#  define R_SPI_B_SPDECR_SLNDL_001                        (1 << R_SPI_B_SPDECR_SLNDL_SHIFT)  /* 2RSPCK */
#  define R_SPI_B_SPDECR_SLNDL_010                        (10 << R_SPI_B_SPDECR_SLNDL_SHIFT)  /* 3RSPCK */
#  define R_SPI_B_SPDECR_SLNDL_011                        (3 << R_SPI_B_SPDECR_SLNDL_SHIFT)  /* 4RSPCK */
#  define R_SPI_B_SPDECR_SLNDL_100                        (4 << R_SPI_B_SPDECR_SLNDL_SHIFT)  /* 5RSPCK */
#  define R_SPI_B_SPDECR_SLNDL_101                        (5 << R_SPI_B_SPDECR_SLNDL_SHIFT)  /* 6RSPCK */
#  define R_SPI_B_SPDECR_SLNDL_110                        (6 << R_SPI_B_SPDECR_SLNDL_SHIFT)  /* 7RSPCK */
#  define R_SPI_B_SPDECR_SLNDL_111                        (7 << R_SPI_B_SPDECR_SLNDL_SHIFT)  /* 8RSPCK */

#define R_SPI_B_SPDECR_SPNDL_SHIFT                (16)  /* SPI Next-Access Delay */
#define R_SPI_B_SPDECR_SPNDL_MASK                 0x70000
#  define R_SPI_B_SPDECR_SPNDL_000                        (0 << R_SPI_B_SPDECR_SPNDL_SHIFT)  /* 1RSPCK + 5TCLK */
#  define R_SPI_B_SPDECR_SPNDL_001                        (1 << R_SPI_B_SPDECR_SPNDL_SHIFT)  /* 2RSPCK + 5TCLK */
#  define R_SPI_B_SPDECR_SPNDL_010                        (10 << R_SPI_B_SPDECR_SPNDL_SHIFT)  /* 3RSPCK + 5TCLK */
#  define R_SPI_B_SPDECR_SPNDL_011                        (3 << R_SPI_B_SPDECR_SPNDL_SHIFT)  /* 4RSPCK + 5TCLK */
#  define R_SPI_B_SPDECR_SPNDL_100                        (4 << R_SPI_B_SPDECR_SPNDL_SHIFT)  /* 5RSPCK + 5TCLK */
#  define R_SPI_B_SPDECR_SPNDL_101                        (5 << R_SPI_B_SPDECR_SPNDL_SHIFT)  /* 6RSPCK + 5TCLK */
#  define R_SPI_B_SPDECR_SPNDL_110                        (6 << R_SPI_B_SPDECR_SPNDL_SHIFT)  /* 7RSPCK + 5TCLK */
#  define R_SPI_B_SPDECR_SPNDL_111                        (7 << R_SPI_B_SPDECR_SPNDL_SHIFT)  /* 8RSPCK + 5TCLK */

#define R_SPI_B_SPDECR_ARST_SHIFT                 (24)  /* Receive Sampling Timing Adjustment bits */
#define R_SPI_B_SPDECR_ARST_MASK                  0x7000000

/* SPCR Register bit definitions */
#define R_SPI_B_SPCR_SPE                          (1 << 0)  /* SPI Function Enable */

#define R_SPI_B_SPCR_SPPE                         (1 << 8)  /* Parity Enable */

#define R_SPI_B_SPCR_SPOE                         (1 << 9)  /* Parity Mode */

#define R_SPI_B_SPCR_PTE                          (1 << 11)  /* Parity Self-Diagnosis Enable */

#define R_SPI_B_SPCR_SCKASE                       (1 << 12)  /* RSPCK Auto-Stop Function Enable */

#define R_SPI_B_SPCR_BFDS                         (1 << 13)  /* Between Burst Transfer Frames Delay Select */

#define R_SPI_B_SPCR_MODFEN                       (1 << 14)  /* Mode Fault Error Detection Enable */

#define R_SPI_B_SPCR_SPEIE                        (1 << 16)  /* SPI Error Interrupt Enable */

#define R_SPI_B_SPCR_SPRIE                        (1 << 17)  /* SPI Receive Buffer Full Interrupt Enable */

#define R_SPI_B_SPCR_SPIIE                        (1 << 18)  /* SPI Idle Interrupt Enable */

#define R_SPI_B_SPCR_SPDRES                       (1 << 19)  /* SPI receive data ready error select */

#define R_SPI_B_SPCR_SPTIE                        (1 << 20)  /* SPI Transmit Buffer Empty Interrupt Enable */

#define R_SPI_B_SPCR_CENDIE                       (1 << 21)  /* SPI Communication End Interrupt Enable */

#define R_SPI_B_SPCR_SPMS                         (1 << 24)  /* SPI Mode Select */

#define R_SPI_B_SPCR_SPFRF                        (1 << 25)  /* SPI Frame Format Select */

#define R_SPI_B_SPCR_TXMD_SHIFT                   (28)  /* Communication Mode Select */
#define R_SPI_B_SPCR_TXMD_MASK                    0x30000000
#  define R_SPI_B_SPCR_TXMD_00                            (0 << R_SPI_B_SPCR_TXMD_SHIFT)  /* Transmit-Receive */
#  define R_SPI_B_SPCR_TXMD_01                            (1 << R_SPI_B_SPCR_TXMD_SHIFT)  /* Transmit only */

#define R_SPI_B_SPCR_MSTR                         (1 << 30)  /* SPI Master/Slave Mode Select */

#define R_SPI_B_SPCR_BPEN                         (1 << 31)  /* Synchronization Circuit Bypass Enable */

#define R_SPI_B_SPCR_SPSCKSEL                     (1 << 7)  /* RSPI Master Receive Clock Select */

/* SPCR2 Register bit definitions */
#define R_SPI_B_SPCR2_RMFM_SHIFT                  (0)  /* Frame processing count setting in Master Receive only */
#define R_SPI_B_SPCR2_RMFM_MASK                   0x1f

#define R_SPI_B_SPCR2_RMEDTG                      (1 << 6)  /* End Trigger in Master Receive only */

#define R_SPI_B_SPCR2_RMSTTG                      (1 << 7)  /* Start Trigger in Master Receive only */

#define R_SPI_B_SPCR2_SPDRC_SHIFT                 (8)  /* SPI received data ready detect adjustment */
#define R_SPI_B_SPCR2_SPDRC_MASK                  0xff00

#define R_SPI_B_SPCR2_SPLP                        (1 << 16)  /* SPI Loopback */

#define R_SPI_B_SPCR2_SPLP2                       (1 << 17)  /* SPI Loopback 2 */

#define R_SPI_B_SPCR2_MOIFV                       (1 << 20)  /* MOSI Idle Fixed Value */

#define R_SPI_B_SPCR2_MOIFE                       (1 << 21)  /* MOSI Idle Fixed Value Enable */

/* SPCR3 Register bit definitions */
#define R_SPI_B_SPCR3_SSL0P                       (1 << 0)  /* SSL0 Signal Polarity */

#define R_SPI_B_SPCR3_SSL1P                       (1 << 1)  /* SSL1 Signal Polarity */

#define R_SPI_B_SPCR3_SSL2P                       (1 << 2)  /* SSL2 Signal Polarity */

#define R_SPI_B_SPCR3_SSL3P                       (1 << 3)  /* SSL3 Signal Polarity */

#define R_SPI_B_SPCR3_SPBR_SHIFT                  (8)  /* SPI Bit Rate */
#define R_SPI_B_SPCR3_SPBR_MASK                   0xff00

#define R_SPI_B_SPCR3_SPSLN_SHIFT                 (24)  /* SPI Sequence Length */
#define R_SPI_B_SPCR3_SPSLN_MASK                  0x7000000
#  define R_SPI_B_SPCR3_SPSLN_000                         (0 << R_SPI_B_SPCR3_SPSLN_SHIFT)  /* Sequence Length is 1 (Referenced SPCMDn, n = 0→0→…) */
#  define R_SPI_B_SPCR3_SPSLN_001                         (1 << R_SPI_B_SPCR3_SPSLN_SHIFT)  /* Sequence Length is 2 (Referenced SPCMDn, n = 0→1→0→…) */
#  define R_SPI_B_SPCR3_SPSLN_010                         (10 << R_SPI_B_SPCR3_SPSLN_SHIFT)  /* Sequence Length is 3 (Referenced SPCMDn, n = 0→1→2→0→…) */
#  define R_SPI_B_SPCR3_SPSLN_011                         (3 << R_SPI_B_SPCR3_SPSLN_SHIFT)  /* Sequence Length is 4 (Referenced SPCMDn, n = 0→1→2→3→0→…) */
#  define R_SPI_B_SPCR3_SPSLN_100                         (4 << R_SPI_B_SPCR3_SPSLN_SHIFT)  /* Sequence Length is 5 (Referenced SPCMDn, n = 0→1→2→3→4→0→…) */
#  define R_SPI_B_SPCR3_SPSLN_101                         (5 << R_SPI_B_SPCR3_SPSLN_SHIFT)  /* Sequence Length is 6 (Referenced SPCMDn, n = 0→1→2→3→4→5→0→…) */
#  define R_SPI_B_SPCR3_SPSLN_110                         (6 << R_SPI_B_SPCR3_SPSLN_SHIFT)  /* Sequence Length is 7 (Referenced SPCMDn, n = 0→1→2→3→4→5→6→0→…) */
#  define R_SPI_B_SPCR3_SPSLN_111                         (7 << R_SPI_B_SPCR3_SPSLN_SHIFT)  /* Sequence Length is 8 (Referenced SPCMDn, n = 0→1→2→3→4→5→6→7→0→…) */

/* SPCMD Register bit definitions */
#define R_SPI_B_SPCMD_CPHA                        (1 << 0)  /* RSPCK Phase */

#define R_SPI_B_SPCMD_CPOL                        (1 << 1)  /* RSPCK Polarity */

#define R_SPI_B_SPCMD_BRDV_SHIFT                  (2)  /* Bit Rate Division */
#define R_SPI_B_SPCMD_BRDV_MASK                   0xc
#  define R_SPI_B_SPCMD_BRDV_00                           (0 << R_SPI_B_SPCMD_BRDV_SHIFT)  /* Base bit rate */
#  define R_SPI_B_SPCMD_BRDV_01                           (1 << R_SPI_B_SPCMD_BRDV_SHIFT)  /* Base bit rate divided by 2 */
#  define R_SPI_B_SPCMD_BRDV_10                           (10 << R_SPI_B_SPCMD_BRDV_SHIFT)  /* Base bit rate divided by 4 */
#  define R_SPI_B_SPCMD_BRDV_11                           (3 << R_SPI_B_SPCMD_BRDV_SHIFT)  /* Base bit rate divided by 8 */

#define R_SPI_B_SPCMD_SSLKP                       (1 << 7)  /* SSL Signal Level Hold */

#define R_SPI_B_SPCMD_LSBF                        (1 << 12)  /* SPI LSB First */

#define R_SPI_B_SPCMD_SPNDEN                      (1 << 13)  /* SPI Next-Access Delay Enable */

#define R_SPI_B_SPCMD_SLNDEN                      (1 << 14)  /* SSL Negation Delay Setting Enable */

#define R_SPI_B_SPCMD_SCKDEN                      (1 << 15)  /* RSPCK Delay Setting Enable */

#define R_SPI_B_SPCMD_SPB_SHIFT                   (16)  /* SPI Data Length */
#define R_SPI_B_SPCMD_SPB_MASK                    0x1f0000

#define R_SPI_B_SPCMD_SSLA_SHIFT                  (24)  /* SSL Signal Assertion */
#define R_SPI_B_SPCMD_SSLA_MASK                   0x7000000
#  define R_SPI_B_SPCMD_SSLA_000                          (0 << R_SPI_B_SPCMD_SSLA_SHIFT)  /* SSL0 */
#  define R_SPI_B_SPCMD_SSLA_001                          (1 << R_SPI_B_SPCMD_SSLA_SHIFT)  /* SSL1 */
#  define R_SPI_B_SPCMD_SSLA_010                          (10 << R_SPI_B_SPCMD_SSLA_SHIFT)  /* SSL2 */
#  define R_SPI_B_SPCMD_SSLA_011                          (3 << R_SPI_B_SPCMD_SSLA_SHIFT)  /* SSL3 */

/* SPDCR Register bit definitions */
#define R_SPI_B_SPDCR_BYSW                        (1 << 0)  /* Byte Swap Operating Mode Select */

#define R_SPI_B_SPDCR_SPRDTD                      (1 << 3)  /* SPI Receive Data or Transmit Data Select */

#define R_SPI_B_SPDCR_SINV                        (1 << 4)  /* Serial data invert bit */

#define R_SPI_B_SPDCR_SPFC_SHIFT                  (8)  /* Frame Count */
#define R_SPI_B_SPDCR_SPFC_MASK                   0x300
#  define R_SPI_B_SPDCR_SPFC_00                           (0 << R_SPI_B_SPDCR_SPFC_SHIFT)  /* 1 frame */
#  define R_SPI_B_SPDCR_SPFC_01                           (1 << R_SPI_B_SPDCR_SPFC_SHIFT)  /* 2 frames */
#  define R_SPI_B_SPDCR_SPFC_10                           (10 << R_SPI_B_SPDCR_SPFC_SHIFT)  /* 3 frames */
#  define R_SPI_B_SPDCR_SPFC_11                           (3 << R_SPI_B_SPDCR_SPFC_SHIFT)  /* 4 frames */

/* SPDCR2 Register bit definitions */
#define R_SPI_B_SPDCR2_RTRG_SHIFT                 (0)  /* Receive FIFO threshold setting */
#define R_SPI_B_SPDCR2_RTRG_MASK                  0x3
#  define R_SPI_B_SPDCR2_RTRG_00                          (0 << R_SPI_B_SPDCR2_RTRG_SHIFT)  /* threshold 0 */
#  define R_SPI_B_SPDCR2_RTRG_01                          (1 << R_SPI_B_SPDCR2_RTRG_SHIFT)  /* threshold 1 */
#  define R_SPI_B_SPDCR2_RTRG_10                          (10 << R_SPI_B_SPDCR2_RTRG_SHIFT)  /* threshold 2 */
#  define R_SPI_B_SPDCR2_RTRG_11                          (3 << R_SPI_B_SPDCR2_RTRG_SHIFT)  /* threshold 3 */

#define R_SPI_B_SPDCR2_TTRG_SHIFT                 (8)  /* Transmission FIFO threshold setting */
#define R_SPI_B_SPDCR2_TTRG_MASK                  0x300
#  define R_SPI_B_SPDCR2_TTRG_00                          (0 << R_SPI_B_SPDCR2_TTRG_SHIFT)  /* threshold 0 */
#  define R_SPI_B_SPDCR2_TTRG_01                          (1 << R_SPI_B_SPDCR2_TTRG_SHIFT)  /* threshold 1 */
#  define R_SPI_B_SPDCR2_TTRG_10                          (10 << R_SPI_B_SPDCR2_TTRG_SHIFT)  /* threshold 2 */
#  define R_SPI_B_SPDCR2_TTRG_11                          (3 << R_SPI_B_SPDCR2_TTRG_SHIFT)  /* threshold 3 */

/* SPSR Register bit definitions */
#define R_SPI_B_SPSR_SPCP_SHIFT                   (8)  /* SPI Command Pointer */
#define R_SPI_B_SPSR_SPCP_MASK                    0x700
#  define R_SPI_B_SPSR_SPCP_000                           (0 << R_SPI_B_SPSR_SPCP_SHIFT)  /* SPCMD0 */
#  define R_SPI_B_SPSR_SPCP_001                           (1 << R_SPI_B_SPSR_SPCP_SHIFT)  /* SPCMD1 */
#  define R_SPI_B_SPSR_SPCP_010                           (10 << R_SPI_B_SPSR_SPCP_SHIFT)  /* SPCMD2 */
#  define R_SPI_B_SPSR_SPCP_011                           (3 << R_SPI_B_SPSR_SPCP_SHIFT)  /* SPCMD3 */
#  define R_SPI_B_SPSR_SPCP_100                           (4 << R_SPI_B_SPSR_SPCP_SHIFT)  /* SPCMD4 */
#  define R_SPI_B_SPSR_SPCP_101                           (5 << R_SPI_B_SPSR_SPCP_SHIFT)  /* SPCMD5 */
#  define R_SPI_B_SPSR_SPCP_110                           (6 << R_SPI_B_SPSR_SPCP_SHIFT)  /* SPCMD6 */
#  define R_SPI_B_SPSR_SPCP_111                           (7 << R_SPI_B_SPSR_SPCP_SHIFT)  /* SPCMD7 */

#define R_SPI_B_SPSR_SPECM_SHIFT                  (12)  /* SPI Error Command */
#define R_SPI_B_SPSR_SPECM_MASK                   0x7000
#  define R_SPI_B_SPSR_SPECM_000                          (0 << R_SPI_B_SPSR_SPECM_SHIFT)  /* SPCMD0 */
#  define R_SPI_B_SPSR_SPECM_001                          (1 << R_SPI_B_SPSR_SPECM_SHIFT)  /* SPCMD1 */
#  define R_SPI_B_SPSR_SPECM_010                          (10 << R_SPI_B_SPSR_SPECM_SHIFT)  /* SPCMD2 */
#  define R_SPI_B_SPSR_SPECM_011                          (3 << R_SPI_B_SPSR_SPECM_SHIFT)  /* SPCMD3 */
#  define R_SPI_B_SPSR_SPECM_100                          (4 << R_SPI_B_SPSR_SPECM_SHIFT)  /* SPCMD4 */
#  define R_SPI_B_SPSR_SPECM_101                          (5 << R_SPI_B_SPSR_SPECM_SHIFT)  /* SPCMD5 */
#  define R_SPI_B_SPSR_SPECM_110                          (6 << R_SPI_B_SPSR_SPECM_SHIFT)  /* SPCMD6 */
#  define R_SPI_B_SPSR_SPECM_111                          (7 << R_SPI_B_SPSR_SPECM_SHIFT)  /* SPCMD7 */

#define R_SPI_B_SPSR_SPDRF                        (1 << 23)  /* SPI Receive Data Ready Flag */

#define R_SPI_B_SPSR_OVRF                         (1 << 24)  /* Overrun Error Flag */

#define R_SPI_B_SPSR_IDLNF                        (1 << 25)  /* SPI Idle Flag */

#define R_SPI_B_SPSR_MODF                         (1 << 26)  /* Mode Fault Error Flag */

#define R_SPI_B_SPSR_PERF                         (1 << 27)  /* Parity Error Flag */

#define R_SPI_B_SPSR_UDRF                         (1 << 28)  /* Underrun Error Flag */

#define R_SPI_B_SPSR_SPTEF                        (1 << 29)  /* SPI Transmit Buffer Empty Flag */

#define R_SPI_B_SPSR_CENDF                        (1 << 30)  /* Communication End Flag */

#define R_SPI_B_SPSR_SPRF                         (1 << 31)  /* SPI Receive Buffer Full Flag */

/* SPTFSR Register bit definitions */
#define R_SPI_B_SPTFSR_TFDN_SHIFT                 (0)  /* Transmit FIFO data empty stage number */
#define R_SPI_B_SPTFSR_TFDN_MASK                  0x7

/* SPRFSR Register bit definitions */
#define R_SPI_B_SPRFSR_RFDN_SHIFT                 (0)  /* Receive FIFO data store stage number */
#define R_SPI_B_SPRFSR_RFDN_MASK                  0x7

/* SPPSR Register bit definitions */
#define R_SPI_B_SPPSR_SPEPS                       (1 << 0)  /* SPI Polling Status */

/* SPSRC Register bit definitions */
#define R_SPI_B_SPSRC_SPDRFC                      (1 << 23)  /* SPI Receive Data Ready Flag Clear */

#define R_SPI_B_SPSRC_OVRFC                       (1 << 24)  /* Overrun Error Flag Clear */

#define R_SPI_B_SPSRC_MODFC                       (1 << 26)  /* Mode Fault Error Flag Clear */

#define R_SPI_B_SPSRC_PERFC                       (1 << 27)  /* Parity Error Flag Clear */

#define R_SPI_B_SPSRC_UDRFC                       (1 << 28)  /* Underrun Error Flag Clear */

#define R_SPI_B_SPSRC_SPTEFC                      (1 << 29)  /* SPI Transmit Buffer Empty Flag Clear */

#define R_SPI_B_SPSRC_CENDFC                      (1 << 30)  /* Communication End Flag Clear */

#define R_SPI_B_SPSRC_SPRFC                       (1 << 31)  /* SPI Receive Buffer Full Flag Clear */

/* SPFCR Register bit definitions */
#define R_SPI_B_SPFCR_SPFRST                      (1 << 0)  /* SPI FIFO clear */


/* Maximum number of channels */

#define SPI_B_MAX_CHANNELS    8

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SPI_B_H */

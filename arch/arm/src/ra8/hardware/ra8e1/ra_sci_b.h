/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_sci_b.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SCI_B_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SCI_B_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCI_B Base Address */
#ifndef R_SCI_B_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_SCI_B_BASE           0x40358000
#else
#define R_SCI_B_BASE           0x50358000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_SCI_B_CH_STRIDE    0x00000100
#define R_SCI_B_CH_BASE(ch)   (R_SCI_B_BASE + ((uint32_t)(ch) * R_SCI_B_CH_STRIDE))

/* SCI_B Register Offsets */

#define R_SCI_B_RDR_OFFSET                        0x00000000  /* Receive Data Register */
#define R_SCI_B_RDR_BY_OFFSET                     0x00000000  /* Receive Data Register */
#define R_SCI_B_TDR_OFFSET                        0x00000004  /* Transmit Data Register */
#define R_SCI_B_TDRLL_OFFSET                      0x00000004  /* Transmit Data Register */
#define R_SCI_B_TDRLH_OFFSET                      0x00000005  /* Transmit Data Register */
#define R_SCI_B_CCR0_OFFSET                       0x00000008  /* Common Control Register 0 */
#define R_SCI_B_CCR1_OFFSET                       0x0000000c  /* Common Control Register 1 */
#define R_SCI_B_CCR2_OFFSET                       0x00000010  /* Common Control Register 2 */
#define R_SCI_B_CCR3_OFFSET                       0x00000014  /* Common Control Register 3 */
#define R_SCI_B_CCR4_OFFSET                       0x00000018  /* Common Control Register 4 */
#define R_SCI_B_CESR_OFFSET                       0x0000001c  /* Communication Enable Status Register */
#define R_SCI_B_ICR_OFFSET                        0x00000020  /* Simple IIC Control Register */
#define R_SCI_B_FCR_OFFSET                        0x00000024  /* FIFO Control Register */
#define R_SCI_B_MCR_OFFSET                        0x0000002c  /* Manchester Control Register */
#define R_SCI_B_DCR_OFFSET                        0x00000030  /* Driver Control Register */
#define R_SCI_B_XCR0_OFFSET                       0x00000034  /* Simple LIN Control Register 0 */
#define R_SCI_B_XCR1_OFFSET                       0x00000038  /* Simple LIN Control Register 1 */
#define R_SCI_B_XCR2_OFFSET                       0x0000003c  /* Simple LIN Control Register 2 */
#define R_SCI_B_CSR_OFFSET                        0x00000048  /* Common Status Register */
#define R_SCI_B_ISR_OFFSET                        0x0000004c  /* Simple IIC Status Register */
#define R_SCI_B_FRSR_OFFSET                       0x00000050  /* FIFO Receive Status Register */
#define R_SCI_B_FTSR_OFFSET                       0x00000054  /* FIFO Transmit Status Register */
#define R_SCI_B_MSR_OFFSET                        0x00000058  /* Manchester Status Register */
#define R_SCI_B_XSR0_OFFSET                       0x0000005c  /* Simple LIN Status Register 0 */
#define R_SCI_B_XSR1_OFFSET                       0x00000060  /* Simple LIN Status Register 1 */
#define R_SCI_B_CFCLR_OFFSET                      0x00000068  /* Common Flag Clear Register */
#define R_SCI_B_ICFCLR_OFFSET                     0x0000006c  /* Simple IIC Flag Clear Register */
#define R_SCI_B_FFCLR_OFFSET                      0x00000070  /* FIFO Flag Clear Register */
#define R_SCI_B_MFCLR_OFFSET                      0x00000074  /* Manchester Flag Clear Register */
#define R_SCI_B_XFCLR_OFFSET                      0x00000078  /* Simple LIN Flag Clear Register */

/* SCI_B Register Addresses */

#define R_SCI_B_RDR                               (R_SCI_B_BASE + R_SCI_B_RDR_OFFSET)
#define R_SCI_B_RDR_BY                            (R_SCI_B_BASE + R_SCI_B_RDR_BY_OFFSET)
#define R_SCI_B_TDR                               (R_SCI_B_BASE + R_SCI_B_TDR_OFFSET)
#define R_SCI_B_TDRLL                             (R_SCI_B_BASE + R_SCI_B_TDRLL_OFFSET)
#define R_SCI_B_TDRLH                             (R_SCI_B_BASE + R_SCI_B_TDRLH_OFFSET)
#define R_SCI_B_CCR0                              (R_SCI_B_BASE + R_SCI_B_CCR0_OFFSET)
#define R_SCI_B_CCR1                              (R_SCI_B_BASE + R_SCI_B_CCR1_OFFSET)
#define R_SCI_B_CCR2                              (R_SCI_B_BASE + R_SCI_B_CCR2_OFFSET)
#define R_SCI_B_CCR3                              (R_SCI_B_BASE + R_SCI_B_CCR3_OFFSET)
#define R_SCI_B_CCR4                              (R_SCI_B_BASE + R_SCI_B_CCR4_OFFSET)
#define R_SCI_B_CESR                              (R_SCI_B_BASE + R_SCI_B_CESR_OFFSET)
#define R_SCI_B_ICR                               (R_SCI_B_BASE + R_SCI_B_ICR_OFFSET)
#define R_SCI_B_FCR                               (R_SCI_B_BASE + R_SCI_B_FCR_OFFSET)
#define R_SCI_B_MCR                               (R_SCI_B_BASE + R_SCI_B_MCR_OFFSET)
#define R_SCI_B_DCR                               (R_SCI_B_BASE + R_SCI_B_DCR_OFFSET)
#define R_SCI_B_XCR0                              (R_SCI_B_BASE + R_SCI_B_XCR0_OFFSET)
#define R_SCI_B_XCR1                              (R_SCI_B_BASE + R_SCI_B_XCR1_OFFSET)
#define R_SCI_B_XCR2                              (R_SCI_B_BASE + R_SCI_B_XCR2_OFFSET)
#define R_SCI_B_CSR                               (R_SCI_B_BASE + R_SCI_B_CSR_OFFSET)
#define R_SCI_B_ISR                               (R_SCI_B_BASE + R_SCI_B_ISR_OFFSET)
#define R_SCI_B_FRSR                              (R_SCI_B_BASE + R_SCI_B_FRSR_OFFSET)
#define R_SCI_B_FTSR                              (R_SCI_B_BASE + R_SCI_B_FTSR_OFFSET)
#define R_SCI_B_MSR                               (R_SCI_B_BASE + R_SCI_B_MSR_OFFSET)
#define R_SCI_B_XSR0                              (R_SCI_B_BASE + R_SCI_B_XSR0_OFFSET)
#define R_SCI_B_XSR1                              (R_SCI_B_BASE + R_SCI_B_XSR1_OFFSET)
#define R_SCI_B_CFCLR                             (R_SCI_B_BASE + R_SCI_B_CFCLR_OFFSET)
#define R_SCI_B_ICFCLR                            (R_SCI_B_BASE + R_SCI_B_ICFCLR_OFFSET)
#define R_SCI_B_FFCLR                             (R_SCI_B_BASE + R_SCI_B_FFCLR_OFFSET)
#define R_SCI_B_MFCLR                             (R_SCI_B_BASE + R_SCI_B_MFCLR_OFFSET)
#define R_SCI_B_XFCLR                             (R_SCI_B_BASE + R_SCI_B_XFCLR_OFFSET)

/* Register bit definitions */
/* RDR Register bit definitions */
#define R_SCI_B_RDR_RDAT_SHIFT                    (0)  /* Serial receive data */
#define R_SCI_B_RDR_RDAT_MASK                     0x1ff

#define R_SCI_B_RDR_MPB                           (1 << 9)  /* Multi-processor flag */

#define R_SCI_B_RDR_DR                            (1 << 10)  /* Receive data ready flag */

#define R_SCI_B_RDR_FPER                          (1 << 11)  /* FIFO parity error flag */

#define R_SCI_B_RDR_FFER                          (1 << 12)  /* FIFO framing error flag */

#define R_SCI_B_RDR_ORER                          (1 << 24)  /* Overrun Error flag */

#define R_SCI_B_RDR_PER                           (1 << 27)  /* Parity error flag */

#define R_SCI_B_RDR_FER                           (1 << 28)  /* Framing error flag */

/* RDR_BY Register bit definitions */
#define R_SCI_B_RDR_BY_ORER                       (1 << 0)  /* Overrun Error flag */

#define R_SCI_B_RDR_BY_PER                        (1 << 3)  /* Parity error flag */

#define R_SCI_B_RDR_BY_FER                        (1 << 4)  /* Framing error flag */

#define R_SCI_B_RDR_BY_RDAT_SHIFT                 (0)  /* Serial receive data */
#define R_SCI_B_RDR_BY_RDAT_MASK                  0xff

/* TDR Register bit definitions */
#define R_SCI_B_TDR_TDAT_SHIFT                    (0)  /* Serial transmit data */
#define R_SCI_B_TDR_TDAT_MASK                     0x1ff

#define R_SCI_B_TDR_MPBT                          (1 << 9)  /* Multi-processor transfer bit flag */

#define R_SCI_B_TDR_TSYNC                         (1 << 12)  /* Transmit SYNC data */

/* TDRLH Register bit definitions */
#define R_SCI_B_TDRLH_TDAT                        (1 << 0)  /* Serial transmit data */

#define R_SCI_B_TDRLH_MPBT                        (1 << 1)  /* Multi-processor transfer bit flag */

#define R_SCI_B_TDRLH_TSYNC                       (1 << 4)  /* Transmit SYNC data */

/* CCR0 Register bit definitions */
#define R_SCI_B_CCR0_RE                           (1 << 0)  /* Receive Enable */

#define R_SCI_B_CCR0_TE                           (1 << 4)  /* Transmit Enable */

#define R_SCI_B_CCR0_MPIE                         (1 << 8)  /* Multi-Processor Interrupt Enable */

#define R_SCI_B_CCR0_DCME                         (1 << 9)  /* Data Compare Match Enable */

#define R_SCI_B_CCR0_IDSEL                        (1 << 10)  /* ID Frame Select */

#define R_SCI_B_CCR0_RIE                          (1 << 16)  /* Receive Interrupt Enable */

#define R_SCI_B_CCR0_TIE                          (1 << 20)  /* Transmit Interrupt Enable */

#define R_SCI_B_CCR0_TEIE                         (1 << 21)  /* Transmit End Interrupt Enable */

#define R_SCI_B_CCR0_SSE                          (1 << 24)  /* SSn Pin Function Enable */

/* CCR1 Register bit definitions */
#define R_SCI_B_CCR1_CTSE                         (1 << 0)  /* CTS Enable */

#define R_SCI_B_CCR1_CTSPEN                       (1 << 1)  /* CTS External Pin Enable */

#define R_SCI_B_CCR1_SPB2DT                       (1 << 4)  /* Serial Port Break Data Select */

#define R_SCI_B_CCR1_SPB2IO                       (1 << 5)  /* Serial Port Break I/O */

#define R_SCI_B_CCR1_PE                           (1 << 8)  /* Parity Enable */

#define R_SCI_B_CCR1_PM                           (1 << 9)  /* Parity Mode */

#define R_SCI_B_CCR1_TINV                         (1 << 12)  /* TXD Invert */

#define R_SCI_B_CCR1_RINV                         (1 << 13)  /* RXD Invert */

#define R_SCI_B_CCR1_SPLP                         (1 << 16)  /* Loopback Control */

#define R_SCI_B_CCR1_SHARPS                       (1 << 20)  /* Half-Duplex Communication Select */

#define R_SCI_B_CCR1_NFCS_SHIFT                   (24)  /* Noise Filter Clock Select */
#define R_SCI_B_CCR1_NFCS_MASK                    0x7000000
#  define R_SCI_B_CCR1_NFCS_000                           (0 << R_SCI_B_CCR1_NFCS_SHIFT)  /* The base clock signal divided by 1 */
#  define R_SCI_B_CCR1_NFCS_001                           (1 << R_SCI_B_CCR1_NFCS_SHIFT)  /* The on-chip baud rate generator source clock divided by 1 */
#  define R_SCI_B_CCR1_NFCS_010                           (2 << R_SCI_B_CCR1_NFCS_SHIFT)  /* The on-chip baud rate generator source clock divided by 2 */
#  define R_SCI_B_CCR1_NFCS_011                           (3 << R_SCI_B_CCR1_NFCS_SHIFT)  /* The on-chip baud rate generator source clock divided by 4 */
#  define R_SCI_B_CCR1_NFCS_100                           (4 << R_SCI_B_CCR1_NFCS_SHIFT)  /* The on-chip baud rate generator source clock divided by 8 */

#define R_SCI_B_CCR1_NFEN                         (1 << 28)  /* Digital Noise Filter Function Enable */

#define R_SCI_B_CCR1_NFM                          (1 << 29)  /* Noise Filter Mode */

/* CCR2 Register bit definitions */
#define R_SCI_B_CCR2_BCP_SHIFT                    (0)  /* Base Clock Pulse */
#define R_SCI_B_CCR2_BCP_MASK                     0x7
#  define R_SCI_B_CCR2_BCP_000                            (0 << R_SCI_B_CCR2_BCP_SHIFT)  /* 93 clock cycles (S = 93) */
#  define R_SCI_B_CCR2_BCP_001                            (1 << R_SCI_B_CCR2_BCP_SHIFT)  /* 128 clock cycles (S = 128) */
#  define R_SCI_B_CCR2_BCP_010                            (2 << R_SCI_B_CCR2_BCP_SHIFT)  /* 186 clock cycles (S = 186) */
#  define R_SCI_B_CCR2_BCP_011                            (3 << R_SCI_B_CCR2_BCP_SHIFT)  /* 512 clock cycles (S = 512) */
#  define R_SCI_B_CCR2_BCP_100                            (4 << R_SCI_B_CCR2_BCP_SHIFT)  /* 32 clock cycles (S = 32) (Initial value) */
#  define R_SCI_B_CCR2_BCP_101                            (5 << R_SCI_B_CCR2_BCP_SHIFT)  /* 64 clock cycles (S = 64) */
#  define R_SCI_B_CCR2_BCP_110                            (6 << R_SCI_B_CCR2_BCP_SHIFT)  /* 372 clock cycles (S = 372) */
#  define R_SCI_B_CCR2_BCP_111                            (7 << R_SCI_B_CCR2_BCP_SHIFT)  /* 256 clock cycles (S = 256) */

#define R_SCI_B_CCR2_BGDM                         (1 << 4)  /* Baud Rate Generator Double-Speed Mode Select */

#define R_SCI_B_CCR2_ABCS                         (1 << 5)  /* Asynchronous Mode Base Clock Select */

#define R_SCI_B_CCR2_ABCSE                        (1 << 6)  /* Asynchronous Mode Extended Base Clock Select */

#define R_SCI_B_CCR2_ABCSE2                       (1 << 7)  /* Asynchronous Mode Extended Base Clock Select 2 */

#define R_SCI_B_CCR2_BRR_SHIFT                    (8)  /* Bit Rate Setting */
#define R_SCI_B_CCR2_BRR_MASK                     0xff00

#define R_SCI_B_CCR2_BRME                         (1 << 16)  /* Bit Rate Modulation Enable */

#define R_SCI_B_CCR2_CKS_SHIFT                    (20)  /* Clock Select */
#define R_SCI_B_CCR2_CKS_MASK                     0x300000
#  define R_SCI_B_CCR2_CKS_00                             (0 << R_SCI_B_CCR2_CKS_SHIFT)  /* TCLK clock (n = 0) */
#  define R_SCI_B_CCR2_CKS_01                             (1 << R_SCI_B_CCR2_CKS_SHIFT)  /* TCLK/4 clock (n = 1) */
#  define R_SCI_B_CCR2_CKS_10                             (2 << R_SCI_B_CCR2_CKS_SHIFT)  /* TCLK/16 clock (n = 2) */
#  define R_SCI_B_CCR2_CKS_11                             (3 << R_SCI_B_CCR2_CKS_SHIFT)  /* TCLK/64 clock (n = 3) */

#define R_SCI_B_CCR2_MDDR_SHIFT                   (24)  /* Modulation Duty Setting */
#define R_SCI_B_CCR2_MDDR_MASK                    0xff000000

/* CCR3 Register bit definitions */
#define R_SCI_B_CCR3_CPHA                         (1 << 0)  /* Clock Phase Select */

#define R_SCI_B_CCR3_CPOL                         (1 << 1)  /* Clock Polarity Select */

#define R_SCI_B_CCR3_BPEN                         (1 << 7)  /* Synchronizer Bypass Enable */

#define R_SCI_B_CCR3_CHR_SHIFT                    (8)  /* Character Length */
#define R_SCI_B_CCR3_CHR_MASK                     0x300
#  define R_SCI_B_CCR3_CHR_00                             (0 << R_SCI_B_CCR3_CHR_SHIFT)  /* Transmit/receive in 9-bit data length */
#  define R_SCI_B_CCR3_CHR_01                             (1 << R_SCI_B_CCR3_CHR_SHIFT)  /* Transmit/receive in 9-bit data length */
#  define R_SCI_B_CCR3_CHR_10                             (2 << R_SCI_B_CCR3_CHR_SHIFT)  /* Transmit/receive in 8-bit data length (initial value) */
#  define R_SCI_B_CCR3_CHR_11                             (3 << R_SCI_B_CCR3_CHR_SHIFT)  /* Transmit/receive in 7-bit data length */

#define R_SCI_B_CCR3_LSBF                         (1 << 12)  /* LSB First select */

#define R_SCI_B_CCR3_SINV                         (1 << 13)  /* Transmitted/Received Data Invert */

#define R_SCI_B_CCR3_STP                          (1 << 14)  /* Stop Bit Length */

#define R_SCI_B_CCR3_RXDESEL                      (1 << 15)  /* Asynchronous Start Bit Edge Detection Select */

#define R_SCI_B_CCR3_MOD_SHIFT                    (16)  /* Communication Mode Select */
#define R_SCI_B_CCR3_MOD_MASK                     0x70000
#  define R_SCI_B_CCR3_MOD_000                            (0 << R_SCI_B_CCR3_MOD_SHIFT)  /* Asynchronous mode (multi-processor mode) */
#  define R_SCI_B_CCR3_MOD_001                            (1 << R_SCI_B_CCR3_MOD_SHIFT)  /* Smart card interface mode */
#  define R_SCI_B_CCR3_MOD_010                            (2 << R_SCI_B_CCR3_MOD_SHIFT)  /* Clock synchronous mode */
#  define R_SCI_B_CCR3_MOD_011                            (3 << R_SCI_B_CCR3_MOD_SHIFT)  /* Simple SPI mode */
#  define R_SCI_B_CCR3_MOD_100                            (4 << R_SCI_B_CCR3_MOD_SHIFT)  /* Simple IIC mode */
#  define R_SCI_B_CCR3_MOD_101                            (5 << R_SCI_B_CCR3_MOD_SHIFT)  /* Manchester mode */
#  define R_SCI_B_CCR3_MOD_110                            (6 << R_SCI_B_CCR3_MOD_SHIFT)  /* Simple LIN mode */
#  define R_SCI_B_CCR3_MOD_111                            (7 << R_SCI_B_CCR3_MOD_SHIFT)  /* Setting prohibited */

#define R_SCI_B_CCR3_MP                           (1 << 19)  /* Multi-Processor Mode */

#define R_SCI_B_CCR3_FM                           (1 << 20)  /* FIFO Mode Select */

#define R_SCI_B_CCR3_DEN                          (1 << 21)  /* Driver Enable */

#define R_SCI_B_CCR3_CKE_SHIFT                    (24)  /* Clock Enable */
#define R_SCI_B_CCR3_CKE_MASK                     0x3000000

#define R_SCI_B_CCR3_ACS0                         (1 << 26)  /* Asynchronous Mode Clock Source Select */

#define R_SCI_B_CCR3_GM                           (1 << 28)  /* GSM Mode */

#define R_SCI_B_CCR3_BLK                          (1 << 29)  /* Block Transfer Mode */

/* CCR4 Register bit definitions */
#define R_SCI_B_CCR4_CMPD_SHIFT                   (0)  /* Compare Match Data */
#define R_SCI_B_CCR4_CMPD_MASK                    0x1ff

#define R_SCI_B_CCR4_ASEN                         (1 << 16)  /* Adjust Receive Sampling Timing Enable */

#define R_SCI_B_CCR4_ATEN                         (1 << 17)  /* Adjust Transmit Timing Enable */

#define R_SCI_B_CCR4_SCKSEL                       (1 << 19)  /* Master receive clock selection */

#define R_SCI_B_CCR4_AST_SHIFT                    (24)  /* Adjustment Value for Receive Sampling Timing */
#define R_SCI_B_CCR4_AST_MASK                     0x7000000
#  define R_SCI_B_CCR4_AST_000                            (0 << R_SCI_B_CCR4_AST_SHIFT)  /* 1-TCLK delay */
#  define R_SCI_B_CCR4_AST_001                            (1 << R_SCI_B_CCR4_AST_SHIFT)  /* 2-TCLK delay */
#  define R_SCI_B_CCR4_AST_010                            (2 << R_SCI_B_CCR4_AST_SHIFT)  /* 3-TCLK delay */
#  define R_SCI_B_CCR4_AST_011                            (3 << R_SCI_B_CCR4_AST_SHIFT)  /* 4-TCLK delay */

#define R_SCI_B_CCR4_AJD                          (1 << 27)  /* Adjustment Direction for Receive Sampling Timing */

#define R_SCI_B_CCR4_ATT_SHIFT                    (28)  /* Adjustment Value for Transmit Timing */
#define R_SCI_B_CCR4_ATT_MASK                     0x70000000

#define R_SCI_B_CCR4_AET                          (1 << 31)  /* Adjustment Edge for Transmit Timing */

/* CESR Register bit definitions */
#define R_SCI_B_CESR_RIST                         (1 << 0)  /* RE Internal Status */

#define R_SCI_B_CESR_TIST                         (1 << 4)  /* TE Internal Status */

/* ICR Register bit definitions */
#define R_SCI_B_ICR_IICDL_SHIFT                   (0)  /* SDA Delay Output Select */
#define R_SCI_B_ICR_IICDL_MASK                    0x1f

#define R_SCI_B_ICR_IICINTM                       (1 << 8)  /* IIC Interrupt Mode Select */

#define R_SCI_B_ICR_IICCSC                        (1 << 9)  /* Clock Synchronization */

#define R_SCI_B_ICR_IICACKT                       (1 << 13)  /* ACK Transmission Data */

#define R_SCI_B_ICR_IICSTAREQ                     (1 << 16)  /* Start Condition Generation */

#define R_SCI_B_ICR_IICRSTAREQ                    (1 << 17)  /* Restart Condition Generation */

#define R_SCI_B_ICR_IICSTPREQ                     (1 << 18)  /* Stop Condition Generation */

#define R_SCI_B_ICR_IICSDAS_SHIFT                 (20)  /* SDA Output Select */
#define R_SCI_B_ICR_IICSDAS_MASK                  0x300000
#  define R_SCI_B_ICR_IICSDAS_00                          (0 << R_SCI_B_ICR_IICSDAS_SHIFT)  /* Serial data output */
#  define R_SCI_B_ICR_IICSDAS_01                          (1 << R_SCI_B_ICR_IICSDAS_SHIFT)  /* Generate a start, restart, or stop condition */
#  define R_SCI_B_ICR_IICSDAS_10                          (2 << R_SCI_B_ICR_IICSDAS_SHIFT)  /* Output the low level on the SDAn pin */
#  define R_SCI_B_ICR_IICSDAS_11                          (3 << R_SCI_B_ICR_IICSDAS_SHIFT)  /* Place the SDAn pin in the high-impedance state */

#define R_SCI_B_ICR_IICSCLS_SHIFT                 (22)  /* SCL Output Select */
#define R_SCI_B_ICR_IICSCLS_MASK                  0xc00000
#  define R_SCI_B_ICR_IICSCLS_00                          (0 << R_SCI_B_ICR_IICSCLS_SHIFT)  /* Serial clock output */
#  define R_SCI_B_ICR_IICSCLS_01                          (1 << R_SCI_B_ICR_IICSCLS_SHIFT)  /* Generate a start, restart, or stop condition */
#  define R_SCI_B_ICR_IICSCLS_10                          (2 << R_SCI_B_ICR_IICSCLS_SHIFT)  /* Output the low level on the SCLn pin */
#  define R_SCI_B_ICR_IICSCLS_11                          (3 << R_SCI_B_ICR_IICSCLS_SHIFT)  /* Place the SCLn pin in the high-impedance state */

/* FCR Register bit definitions */
#define R_SCI_B_FCR_DRES                          (1 << 0)  /* Receive Data Ready Error Select Bit */

#define R_SCI_B_FCR_TTRG_SHIFT                    (8)  /* Transmit FIFO Data Trigger Number */
#define R_SCI_B_FCR_TTRG_MASK                     0x1f00

#define R_SCI_B_FCR_TFRST                         (1 << 15)  /* Transmit FIFO Data Register Reset */

#define R_SCI_B_FCR_RTRG_SHIFT                    (16)  /* Receive FIFO Data Trigger Number */
#define R_SCI_B_FCR_RTRG_MASK                     0x1f0000

#define R_SCI_B_FCR_RFRST                         (1 << 23)  /* Receive FIFO Data Register Reset */

#define R_SCI_B_FCR_RSTRG_SHIFT                   (24)  /* RTS Output Active Trigger Number Select */
#define R_SCI_B_FCR_RSTRG_MASK                    0x1f000000

/* MCR Register bit definitions */
#define R_SCI_B_MCR_RMPOL                         (1 << 0)  /* Polarity of Received Manchester Code */

#define R_SCI_B_MCR_TMPOL                         (1 << 1)  /* Polarity of Transmit Manchester Code */

#define R_SCI_B_MCR_ERTEN                         (1 << 2)  /* Manchester Edge Retiming Enable */

#define R_SCI_B_MCR_SYNVAL                        (1 << 4)  /* SYNC value Setting */

#define R_SCI_B_MCR_SYNSEL                        (1 << 5)  /* SYNC Select */

#define R_SCI_B_MCR_SBSEL                         (1 << 6)  /* Start Bit Select */

#define R_SCI_B_MCR_TPLEN_SHIFT                   (8)  /* Transmit Preface Length */
#define R_SCI_B_MCR_TPLEN_MASK                    0xf00
#  define R_SCI_B_MCR_TPLEN_0X0                           (0 << R_SCI_B_MCR_TPLEN_SHIFT)  /* Disables the transmit preface generation */

#define R_SCI_B_MCR_TPPAT_SHIFT                   (12)  /* Transmit Preface Pattern */
#define R_SCI_B_MCR_TPPAT_MASK                    0x3000
#  define R_SCI_B_MCR_TPPAT_00                            (0 << R_SCI_B_MCR_TPPAT_SHIFT)  /* ALL ZERO */
#  define R_SCI_B_MCR_TPPAT_01                            (1 << R_SCI_B_MCR_TPPAT_SHIFT)  /* ZERO ONE */
#  define R_SCI_B_MCR_TPPAT_10                            (2 << R_SCI_B_MCR_TPPAT_SHIFT)  /* ONE ZERO */
#  define R_SCI_B_MCR_TPPAT_11                            (3 << R_SCI_B_MCR_TPPAT_SHIFT)  /* ALL ONE */

#define R_SCI_B_MCR_RPLEN_SHIFT                   (16)  /* Receive Preface Length */
#define R_SCI_B_MCR_RPLEN_MASK                    0xf0000
#  define R_SCI_B_MCR_RPLEN_0X0                           (0 << R_SCI_B_MCR_RPLEN_SHIFT)  /* Disables the receive preface generation */

#define R_SCI_B_MCR_RPPAT_SHIFT                   (20)  /* Receive Preface Pattern */
#define R_SCI_B_MCR_RPPAT_MASK                    0x300000
#  define R_SCI_B_MCR_RPPAT_00                            (0 << R_SCI_B_MCR_RPPAT_SHIFT)  /* ALL ZERO */
#  define R_SCI_B_MCR_RPPAT_01                            (1 << R_SCI_B_MCR_RPPAT_SHIFT)  /* ZERO ONE */
#  define R_SCI_B_MCR_RPPAT_10                            (2 << R_SCI_B_MCR_RPPAT_SHIFT)  /* ONE ZERO */
#  define R_SCI_B_MCR_RPPAT_11                            (3 << R_SCI_B_MCR_RPPAT_SHIFT)  /* ALL ONE */

#define R_SCI_B_MCR_PFEREN                        (1 << 24)  /* Preface Error Enable */

#define R_SCI_B_MCR_SYEREN                        (1 << 25)  /* Receive SYNC Error Enable */

#define R_SCI_B_MCR_SBEREN                        (1 << 26)  /* Start Bit Error Enable */

/* DCR Register bit definitions */
#define R_SCI_B_DCR_DEPOL                         (1 << 0)  /* Driver Effective Polarity Select */

#define R_SCI_B_DCR_DEAST_SHIFT                   (8)  /* Driver Assertion Time */
#define R_SCI_B_DCR_DEAST_MASK                    0x1f00

#define R_SCI_B_DCR_DENGT_SHIFT                   (16)  /* Driver Negate Time */
#define R_SCI_B_DCR_DENGT_MASK                    0x1f0000

/* XCR0 Register bit definitions */
#define R_SCI_B_XCR0_TCSS_SHIFT                   (0)  /* Timer Count Clock Source Selection */
#define R_SCI_B_XCR0_TCSS_MASK                    0x3
#  define R_SCI_B_XCR0_TCSS_01                            (1 << R_SCI_B_XCR0_TCSS_SHIFT)  /* TCLK/4 */
#  define R_SCI_B_XCR0_TCSS_10                            (2 << R_SCI_B_XCR0_TCSS_SHIFT)  /* TCLK/16 */
#  define R_SCI_B_XCR0_TCSS_11                            (3 << R_SCI_B_XCR0_TCSS_SHIFT)  /* TCLK/64 */

#define R_SCI_B_XCR0_BFE                          (1 << 8)  /* Break Field Enable */

#define R_SCI_B_XCR0_CF0RE                        (1 << 9)  /* Control Field 0 Enable */

#define R_SCI_B_XCR0_CF1DS_SHIFT                  (10)  /* Control Field1 Compare Data Select */
#define R_SCI_B_XCR0_CF1DS_MASK                   0xc00
#  define R_SCI_B_XCR0_CF1DS_00                           (0 << R_SCI_B_XCR0_CF1DS_SHIFT)  /* Select XCR1.PCF1D[7:0] as the compare data */
#  define R_SCI_B_XCR0_CF1DS_01                           (1 << R_SCI_B_XCR0_CF1DS_SHIFT)  /* Select XCR1.SCF1D[7:0] as the compare data */
#  define R_SCI_B_XCR0_CF1DS_10                           (2 << R_SCI_B_XCR0_CF1DS_SHIFT)  /* Select both XCR1.PCF1D[7:0] and XCR1.SCF1D[7:0] as the compare data */
#  define R_SCI_B_XCR0_CF1DS_11                           (3 << R_SCI_B_XCR0_CF1DS_SHIFT)  /* Setting prohibited */

#define R_SCI_B_XCR0_PIBE                         (1 << 12)  /* Priority Interrupt Bit Enable */

#define R_SCI_B_XCR0_PIBS_SHIFT                   (13)  /* Priority Interrupt Bit Select */
#define R_SCI_B_XCR0_PIBS_MASK                    0xe000
#  define R_SCI_B_XCR0_PIBS_000                           (0 << R_SCI_B_XCR0_PIBS_SHIFT)  /* Bit 0 of Control Field 1 */
#  define R_SCI_B_XCR0_PIBS_001                           (1 << R_SCI_B_XCR0_PIBS_SHIFT)  /* Bit 1 of Control Field 1 */
#  define R_SCI_B_XCR0_PIBS_010                           (2 << R_SCI_B_XCR0_PIBS_SHIFT)  /* Bit 2 of Control Field 1 */
#  define R_SCI_B_XCR0_PIBS_011                           (3 << R_SCI_B_XCR0_PIBS_SHIFT)  /* Bit 3 of Control Field 1 */
#  define R_SCI_B_XCR0_PIBS_100                           (4 << R_SCI_B_XCR0_PIBS_SHIFT)  /* Bit 4 of Control Field 1 */
#  define R_SCI_B_XCR0_PIBS_101                           (5 << R_SCI_B_XCR0_PIBS_SHIFT)  /* Bit 5 of Control Field 1 */
#  define R_SCI_B_XCR0_PIBS_110                           (6 << R_SCI_B_XCR0_PIBS_SHIFT)  /* Bit 6 of Control Field 1 */
#  define R_SCI_B_XCR0_PIBS_111                           (7 << R_SCI_B_XCR0_PIBS_SHIFT)  /* Bit 7 of Control Field 1 */

#define R_SCI_B_XCR0_BFOIE                        (1 << 16)  /* Break Field Output Completion Interrupt Enable */

#define R_SCI_B_XCR0_BCDIE                        (1 << 17)  /* Bus Conflict Detection Interrupt Enable */

#define R_SCI_B_XCR0_BFDIE                        (1 << 20)  /* Break Field Detection Interrupt Enable */

#define R_SCI_B_XCR0_COFIE                        (1 << 21)  /* Counter Overflow Interrupt Enable */

#define R_SCI_B_XCR0_AEDIE                        (1 << 22)  /* Active Edge Detection Interrupt Enable */

#define R_SCI_B_XCR0_BCCS_SHIFT                   (24)  /* Bus Conflict Detection Clock Selection */
#define R_SCI_B_XCR0_BCCS_MASK                    0x3000000
#  define R_SCI_B_XCR0_BCCS_00                            (0 << R_SCI_B_XCR0_BCCS_SHIFT)  /* Base clock */
#  define R_SCI_B_XCR0_BCCS_01                            (1 << R_SCI_B_XCR0_BCCS_SHIFT)  /* Base clock/2 */
#  define R_SCI_B_XCR0_BCCS_10                            (2 << R_SCI_B_XCR0_BCCS_SHIFT)  /* Base clock/4 */
#  define R_SCI_B_XCR0_BCCS_11                            (3 << R_SCI_B_XCR0_BCCS_SHIFT)  /* Setting prohibited */

/* XCR1 Register bit definitions */
#define R_SCI_B_XCR1_TCST                         (1 << 0)  /* Break Field Output Timer Count Start Trigger */

#define R_SCI_B_XCR1_SDST                         (1 << 4)  /* Start Frame Detection Enable */

#define R_SCI_B_XCR1_BMEN                         (1 << 5)  /* Bit Rate Measurement Enable */

#define R_SCI_B_XCR1_PCF1D_SHIFT                  (8)  /* Priority Compare Data for Control Field 1 */
#define R_SCI_B_XCR1_PCF1D_MASK                   0xff00

#define R_SCI_B_XCR1_SCF1D_SHIFT                  (16)  /* Secondary Compare Data for Control Field 1 */
#define R_SCI_B_XCR1_SCF1D_MASK                   0xff0000

#define R_SCI_B_XCR1_CF1CE_SHIFT                  (24)  /* Control Field 1 Compare Bit Enable */
#define R_SCI_B_XCR1_CF1CE_MASK                   0xff000000
#  define R_SCI_B_XCR1_CF1CE_0                            (0 << R_SCI_B_XCR1_CF1CE_SHIFT)  /* Control Field 1 bit N compare disabled */
#  define R_SCI_B_XCR1_CF1CE_1                            (1 << R_SCI_B_XCR1_CF1CE_SHIFT)  /* Control Field 1 bit N compare enabled */

/* XCR2 Register bit definitions */
#define R_SCI_B_XCR2_CF0D_SHIFT                   (0)  /* Control Field 0 Compare Data */
#define R_SCI_B_XCR2_CF0D_MASK                    0xff

#define R_SCI_B_XCR2_CF0CE_SHIFT                  (8)  /* Control Field 0 Compare Bit Enable */
#define R_SCI_B_XCR2_CF0CE_MASK                   0xff00
#  define R_SCI_B_XCR2_CF0CE_0                            (0 << R_SCI_B_XCR2_CF0CE_SHIFT)  /* Control Field 0 bit N compare disabled */
#  define R_SCI_B_XCR2_CF0CE_1                            (1 << R_SCI_B_XCR2_CF0CE_SHIFT)  /* Control Field 0 bit N compare enabled */

#define R_SCI_B_XCR2_BFLW_SHIFT                   (16)  /* Break Field Length Setting */
#define R_SCI_B_XCR2_BFLW_MASK                    0xffff0000

/* CSR Register bit definitions */
#define R_SCI_B_CSR_ERS                           (1 << 4)  /* Error Signal Status Flag */

#define R_SCI_B_CSR_RXDMON                        (1 << 15)  /* Serial Input Data Monitor Bit */

#define R_SCI_B_CSR_DCMF                          (1 << 16)  /* Data Compare Match Flag */

#define R_SCI_B_CSR_DPER                          (1 << 17)  /* Data Compare Match Parity Error Flag */

#define R_SCI_B_CSR_DFER                          (1 << 18)  /* Data Compare Match Framing Error Flag */

#define R_SCI_B_CSR_ORER                          (1 << 24)  /* Overrun Error Flag */

#define R_SCI_B_CSR_MFF                           (1 << 26)  /* Mode Fault Error Flag */

#define R_SCI_B_CSR_PER                           (1 << 27)  /* Parity Error Flag */

#define R_SCI_B_CSR_FER                           (1 << 28)  /* Framing Error Flag */

#define R_SCI_B_CSR_TDRE                          (1 << 29)  /* Transmit Data Empty Flag */

#define R_SCI_B_CSR_TEND                          (1 << 30)  /* Transmit End Flag */

#define R_SCI_B_CSR_RDRF                          (1 << 31)  /* Receive Data Full Flag */

/* ISR Register bit definitions */
#define R_SCI_B_ISR_IICACKR                       (1 << 0)  /* ACK Reception Data Flag */

#define R_SCI_B_ISR_IICSTIF                       (1 << 3)  /* Issuing of Start, Restart, or Stop Condition Completed Flag */

/* FRSR Register bit definitions */
#define R_SCI_B_FRSR_DR                           (1 << 0)  /* Receive Data Ready Flag */

#define R_SCI_B_FRSR_R_SHIFT                      (8)  /* Receive-FIFO Data Count */
#define R_SCI_B_FRSR_R_MASK                       0x3f00

#define R_SCI_B_FRSR_PNUM_SHIFT                   (16)  /* Parity Error Count */
#define R_SCI_B_FRSR_PNUM_MASK                    0x3f0000

#define R_SCI_B_FRSR_FNUM_SHIFT                   (24)  /* Framing Error Count */
#define R_SCI_B_FRSR_FNUM_MASK                    0x3f000000

/* FTSR Register bit definitions */
#define R_SCI_B_FTSR_T_SHIFT                      (0)  /* Transmit-FIFO Data Count */
#define R_SCI_B_FTSR_T_MASK                       0x3f

/* MSR Register bit definitions */
#define R_SCI_B_MSR_PFER                          (1 << 0)  /* Preface Error Flag */

#define R_SCI_B_MSR_SYER                          (1 << 1)  /* SYNC Error Flag */

#define R_SCI_B_MSR_SBER                          (1 << 2)  /* Start Bit Error Flag */

#define R_SCI_B_MSR_MER                           (1 << 4)  /* Manchester Error Flag */

#define R_SCI_B_MSR_RSYNC                         (1 << 6)  /* Receive SYNC Data Bit */

/* XSR0 Register bit definitions */
#define R_SCI_B_XSR0_SFSF                         (1 << 0)  /* Start Frame Status Flag */

#define R_SCI_B_XSR0_RXDSF                        (1 << 1)  /* RXDn Input Status Flag */

#define R_SCI_B_XSR0_BFOF                         (1 << 8)  /* Break Field Output Completion Flag */

#define R_SCI_B_XSR0_BCDF                         (1 << 9)  /* Bus Conflict Detection Flag */

#define R_SCI_B_XSR0_BFDF                         (1 << 10)  /* Break Field Detection Flag */

#define R_SCI_B_XSR0_CF0MF                        (1 << 11)  /* Control Field 0 Compare Match Flag */

#define R_SCI_B_XSR0_CF1MF                        (1 << 12)  /* Control Field 1 Compare Match Flag */

#define R_SCI_B_XSR0_PIBDF                        (1 << 13)  /* Priority Interrupt Bit Detection Flag */

#define R_SCI_B_XSR0_COF                          (1 << 14)  /* Counter Overflow Flag */

#define R_SCI_B_XSR0_AEDF                         (1 << 15)  /* Active Edge Detection Flag */

#define R_SCI_B_XSR0_CF0RD_SHIFT                  (16)  /* Control Field 0 received data */
#define R_SCI_B_XSR0_CF0RD_MASK                   0xff0000

#define R_SCI_B_XSR0_CF1RD_SHIFT                  (24)  /* Control Field 1 received data */
#define R_SCI_B_XSR0_CF1RD_MASK                   0xff000000

/* XSR1 Register bit definitions */
#define R_SCI_B_XSR1_TCNT_SHIFT                   (0)  /* Timer Count Capture Value */
#define R_SCI_B_XSR1_TCNT_MASK                    0xffff

/* CFCLR Register bit definitions */
#define R_SCI_B_CFCLR_ERSC                        (1 << 4)  /* ERS Clear Bit */

#define R_SCI_B_CFCLR_DCMFC                       (1 << 16)  /* DCMF Clear Bit */

#define R_SCI_B_CFCLR_DPERC                       (1 << 17)  /* DPER Clear Bit */

#define R_SCI_B_CFCLR_DFERC                       (1 << 18)  /* DFER Clear Bit */

#define R_SCI_B_CFCLR_ORERC                       (1 << 24)  /* ORER Clear Bit */

#define R_SCI_B_CFCLR_MFFC                        (1 << 26)  /* MFF Clear Bit */

#define R_SCI_B_CFCLR_PERC                        (1 << 27)  /* PER Clear Bit */

#define R_SCI_B_CFCLR_FERC                        (1 << 28)  /* FER Clear Bit */

#define R_SCI_B_CFCLR_TDREC                       (1 << 29)  /* TDRE Clear Bit */

#define R_SCI_B_CFCLR_RDRFC                       (1 << 31)  /* RDRF Clear Bit */

/* ICFCLR Register bit definitions */
#define R_SCI_B_ICFCLR_IICSTIFC                   (1 << 3)  /* IICSTIF Clear Bit */

/* FFCLR Register bit definitions */
#define R_SCI_B_FFCLR_DRC                         (1 << 0)  /* DR Clear Bit */

/* MFCLR Register bit definitions */
#define R_SCI_B_MFCLR_PFERC                       (1 << 0)  /* PFER Clear Bit */

#define R_SCI_B_MFCLR_SYERC                       (1 << 1)  /* SYER Clear Bit */

#define R_SCI_B_MFCLR_SBERC                       (1 << 2)  /* SBER Clear Bit */

#define R_SCI_B_MFCLR_MERC                        (1 << 4)  /* MER Clear Bit */

/* XFCLR Register bit definitions */
#define R_SCI_B_XFCLR_BFOC                        (1 << 8)  /* BFOF Clear Bit */

#define R_SCI_B_XFCLR_BCDC                        (1 << 9)  /* BCDF Clear Bit */

#define R_SCI_B_XFCLR_BFDC                        (1 << 10)  /* BFDF Clear Bit */

#define R_SCI_B_XFCLR_CF0MC                       (1 << 11)  /* CF0MF Clear Bit */

#define R_SCI_B_XFCLR_CF1MC                       (1 << 12)  /* CF1MF Clear Bit */

#define R_SCI_B_XFCLR_PIBDC                       (1 << 13)  /* PIBDF Clear Bit */

#define R_SCI_B_XFCLR_COFC                        (1 << 14)  /* COFF Clear Bit */

#define R_SCI_B_XFCLR_AEDC                        (1 << 15)  /* AEDF Clear Bit */


/* Maximum number of channels */

#define SCI_B_MAX_CHANNELS    6

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SCI_B_H */

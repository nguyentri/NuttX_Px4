/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_ssi.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SSI_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SSI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SSI Base Address */
#ifndef R_SSI_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_SSI_BASE           0x4025d000
#else
#define R_SSI_BASE           0x5025d000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_SSI_CH_STRIDE    0x00000100
#define R_SSI_CH_BASE(ch)   (R_SSI_BASE + ((uint32_t)(ch) * R_SSI_CH_STRIDE))

/* SSI Register Offsets */

#define R_SSI_SSICR_OFFSET                        0x00000000  /* Control Register */
#define R_SSI_SSISR_OFFSET                        0x00000004  /* Status Register */
#define R_SSI_SSIFCR_OFFSET                       0x00000010  /* FIFO Control Register */
#define R_SSI_SSIFSR_OFFSET                       0x00000014  /* FIFO Status Register */
#define R_SSI_SSIFTDR_OFFSET                      0x00000018  /* Transmit FIFO Data Register */
#define R_SSI_SSIFTDR16_OFFSET                    0x00000018  /* Transmit FIFO Data Register */
#define R_SSI_SSIFTDR8_OFFSET                     0x00000018  /* Transmit FIFO Data Register */
#define R_SSI_SSIFRDR_OFFSET                      0x0000001c  /* Receive FIFO Data Register */
#define R_SSI_SSIFRDR16_OFFSET                    0x0000001c  /* Receive FIFO Data Register */
#define R_SSI_SSIFRDR8_OFFSET                     0x0000001c  /* Receive FIFO Data Register */
#define R_SSI_SSIOFR_OFFSET                       0x00000020  /* Audio Format Register */
#define R_SSI_SSISCR_OFFSET                       0x00000024  /* Status Control Register */

/* SSI Register Addresses */

#define R_SSI_SSICR(n)                            (R_SSI_CH_BASE(n) + R_SSI_SSICR_OFFSET)
#define R_SSI_SSISR(n)                            (R_SSI_CH_BASE(n) + R_SSI_SSISR_OFFSET)
#define R_SSI_SSIFCR(n)                           (R_SSI_CH_BASE(n) + R_SSI_SSIFCR_OFFSET)
#define R_SSI_SSIFSR(n)                           (R_SSI_CH_BASE(n) + R_SSI_SSIFSR_OFFSET)
#define R_SSI_SSIFTDR(n)                          (R_SSI_CH_BASE(n) + R_SSI_SSIFTDR_OFFSET)
#define R_SSI_SSIFTDR16(n)                        (R_SSI_CH_BASE(n) + R_SSI_SSIFTDR16_OFFSET)
#define R_SSI_SSIFTDR8(n)                         (R_SSI_CH_BASE(n) + R_SSI_SSIFTDR8_OFFSET)
#define R_SSI_SSIFRDR(n)                          (R_SSI_CH_BASE(n) + R_SSI_SSIFRDR_OFFSET)
#define R_SSI_SSIFRDR16(n)                        (R_SSI_CH_BASE(n) + R_SSI_SSIFRDR16_OFFSET)
#define R_SSI_SSIFRDR8(n)                         (R_SSI_CH_BASE(n) + R_SSI_SSIFRDR8_OFFSET)
#define R_SSI_SSIOFR(n)                           (R_SSI_CH_BASE(n) + R_SSI_SSIOFR_OFFSET)
#define R_SSI_SSISCR(n)                           (R_SSI_CH_BASE(n) + R_SSI_SSISCR_OFFSET)

/* Register bit definitions */
/* SSICR Register bit definitions */
#define R_SSI_SSICR_CKS                           (1 << 30)  /* Oversampling Clock Select */

#define R_SSI_SSICR_TUIEN                         (1 << 29)  /* Transmit Underflow Interrupt Enable */

#define R_SSI_SSICR_TOIEN                         (1 << 28)  /* Transmit Overflow Interrupt Enable */

#define R_SSI_SSICR_RUIEN                         (1 << 27)  /* Receive Underflow Interrupt Enable */

#define R_SSI_SSICR_ROIEN                         (1 << 26)  /* Receive Overflow Interrupt Enable */

#define R_SSI_SSICR_IIEN                          (1 << 25)  /* Idle Mode Interrupt Enable */

#define R_SSI_SSICR_FRM_SHIFT                     (22)  /* Channels */
#define R_SSI_SSICR_FRM_MASK                      0xc00000
#  define R_SSI_SSICR_FRM_00                              (0 << R_SSI_SSICR_FRM_SHIFT)  /* One channel */

#define R_SSI_SSICR_DWL_SHIFT                     (19)  /* Data Word Length */
#define R_SSI_SSICR_DWL_MASK                      0x380000
#  define R_SSI_SSICR_DWL_000                             (0 << R_SSI_SSICR_DWL_SHIFT)  /* 8 bits */
#  define R_SSI_SSICR_DWL_001                             (1 << R_SSI_SSICR_DWL_SHIFT)  /* 16 bits */
#  define R_SSI_SSICR_DWL_010                             (2 << R_SSI_SSICR_DWL_SHIFT)  /* 18 bits */
#  define R_SSI_SSICR_DWL_011                             (3 << R_SSI_SSICR_DWL_SHIFT)  /* 20 bits */
#  define R_SSI_SSICR_DWL_100                             (4 << R_SSI_SSICR_DWL_SHIFT)  /* 22 bits */
#  define R_SSI_SSICR_DWL_101                             (5 << R_SSI_SSICR_DWL_SHIFT)  /* 24 bits */

#define R_SSI_SSICR_SWL_SHIFT                     (16)  /* System Word LengthSet the system word length to the bit clock frequency/2 fs. */
#define R_SSI_SSICR_SWL_MASK                      0x70000
#  define R_SSI_SSICR_SWL_000                             (0 << R_SSI_SSICR_SWL_SHIFT)  /* 8 bits (serial bit clock frequency = 16fs ) */
#  define R_SSI_SSICR_SWL_001                             (1 << R_SSI_SSICR_SWL_SHIFT)  /* 16 bits (serial bit clock frequency = 32fs ) */
#  define R_SSI_SSICR_SWL_010                             (2 << R_SSI_SSICR_SWL_SHIFT)  /* 24 bits (serial bit clock frequency = 48fs ) */
#  define R_SSI_SSICR_SWL_011                             (3 << R_SSI_SSICR_SWL_SHIFT)  /* 32 bits (serial bit clock frequency = 64fs ) */

#define R_SSI_SSICR_MST                           (1 << 14)  /* Serial WS Direction NOTE: Only the following settings are allowed: (SCKD, SWSD) = (0, 0) and (1, 1). Other settings are prohibited. */

#define R_SSI_SSICR_BCKP                          (1 << 13)  /* Serial Bit Clock Polarity */

#define R_SSI_SSICR_LRCKP                         (1 << 12)  /* Serial WS Polarity */

#define R_SSI_SSICR_SPDP                          (1 << 11)  /* Serial Padding Polarity */

#define R_SSI_SSICR_SDTA                          (1 << 10)  /* Serial Data Alignment */

#define R_SSI_SSICR_PDTA                          (1 << 9)  /* Parallel Data Alignment */

#define R_SSI_SSICR_DEL                           (1 << 8)  /* Serial Data Delay */

#define R_SSI_SSICR_CKDV_SHIFT                    (4)  /* Serial Oversampling Clock Division Ratio */
#define R_SSI_SSICR_CKDV_MASK                     0xf0
#  define R_SSI_SSICR_CKDV_0X0                            (0 << R_SSI_SSICR_CKDV_SHIFT)  /* CLK */
#  define R_SSI_SSICR_CKDV_0X1                            (1 << R_SSI_SSICR_CKDV_SHIFT)  /* CLK/2 */
#  define R_SSI_SSICR_CKDV_0X2                            (2 << R_SSI_SSICR_CKDV_SHIFT)  /* CLK/4 */
#  define R_SSI_SSICR_CKDV_0X3                            (3 << R_SSI_SSICR_CKDV_SHIFT)  /* CLK/8 */
#  define R_SSI_SSICR_CKDV_0X4                            (4 << R_SSI_SSICR_CKDV_SHIFT)  /* CLK/16 */
#  define R_SSI_SSICR_CKDV_0X5                            (5 << R_SSI_SSICR_CKDV_SHIFT)  /* CLK/32 */
#  define R_SSI_SSICR_CKDV_0X6                            (6 << R_SSI_SSICR_CKDV_SHIFT)  /* CLK/64 */
#  define R_SSI_SSICR_CKDV_0X7                            (7 << R_SSI_SSICR_CKDV_SHIFT)  /* CLK/128 */
#  define R_SSI_SSICR_CKDV_0X8                            (8 << R_SSI_SSICR_CKDV_SHIFT)  /* CLK/6 */
#  define R_SSI_SSICR_CKDV_0X9                            (9 << R_SSI_SSICR_CKDV_SHIFT)  /* CLK/12 (These bits are only settable for channel 0. Setting these bits in the register for channel 1 is prohibited.) */
#  define R_SSI_SSICR_CKDV_0XA                            (10 << R_SSI_SSICR_CKDV_SHIFT)  /* CLK/24 */
#  define R_SSI_SSICR_CKDV_0XB                            (11 << R_SSI_SSICR_CKDV_SHIFT)  /* CLK/48(These bits are only settable for channel 0. Setting these bits in the register for channel 1 is prohibited.) */
#  define R_SSI_SSICR_CKDV_0XC                            (12 << R_SSI_SSICR_CKDV_SHIFT)  /* CLK/96(These bits are only settable for channel 0. Setting these bits in the register for channel 1 is prohibited.) */

#define R_SSI_SSICR_MUEN                          (1 << 3)  /* Mute EnableNOTE: When this module is muted, the value of outputting serial data is rewritten to 0 but data transmission is not stopped. Write dummy data to the SSIFTDR not to generate a transmit underflow because the number of data in the transmit FIFO is decreasing. */

#define R_SSI_SSICR_TEN                           (1 << 1)  /* Transmit Enable */

#define R_SSI_SSICR_REN                           (1 << 0)  /* Receive Enable */

/* SSISR Register bit definitions */
#define R_SSI_SSISR_TUIRQ                         (1 << 29)  /* Transmit Underflow Error Interrupt Status Flag NOTE: Writable only to clear the flag. Confirm the value is 1 and then write 0. */

#define R_SSI_SSISR_TOIRQ                         (1 << 28)  /* Transmit Overflow Error Interrupt Status Flag NOTE: Writable only to clear the flag. Confirm the value is 1 and then write 0. */

#define R_SSI_SSISR_RUIRQ                         (1 << 27)  /* Receive Underflow Error Interrupt Status Flag NOTE: Writable only to clear the flag. Confirm the value is 1 and then write 0. */

#define R_SSI_SSISR_ROIRQ                         (1 << 26)  /* Receive Overflow Error Interrupt Status Flag NOTE: Writable only to clear the flag. Confirm the value is 1 and then write 0. */

#define R_SSI_SSISR_IIRQ                          (1 << 25)  /* Idle Mode Interrupt Status Flag */

#define R_SSI_SSISR_TCHNO_SHIFT                   (5)  /* Transmit Channel Number */
#define R_SSI_SSISR_TCHNO_MASK                    0x60

#define R_SSI_SSISR_TSWNO                         (1 << 4)  /* Transmit Serial Word Number */

#define R_SSI_SSISR_RCHNO_SHIFT                   (2)  /* Receive Channel Number.These bits are read as 00b. */
#define R_SSI_SSISR_RCHNO_MASK                    0xc

#define R_SSI_SSISR_RSWNO                         (1 << 1)  /* Receive Serial Word Number */

#define R_SSI_SSISR_IDST                          (1 << 0)  /* Idle Mode Status Flag */

/* SSIFCR Register bit definitions */
#define R_SSI_SSIFCR_AUCKE                        (1 << 31)  /* Oversampling Clock Enable */

#define R_SSI_SSIFCR_SSIRST                       (1 << 16)  /* SSI soft ware reset */

#define R_SSI_SSIFCR_TTRG_SHIFT                   (6)  /* Transmit Data Trigger Number NOTE: The values in parenthesis are the number of empty stages in SSIFTDR at which the TDE flag is set. */
#define R_SSI_SSIFCR_TTRG_MASK                    0xc0
#  define R_SSI_SSIFCR_TTRG_00                            (0 << R_SSI_SSIFCR_TTRG_SHIFT)  /* 7 (1) */
#  define R_SSI_SSIFCR_TTRG_01                            (1 << R_SSI_SSIFCR_TTRG_SHIFT)  /* 6 (2) */
#  define R_SSI_SSIFCR_TTRG_10                            (2 << R_SSI_SSIFCR_TTRG_SHIFT)  /* 4 (4) */
#  define R_SSI_SSIFCR_TTRG_11                            (3 << R_SSI_SSIFCR_TTRG_SHIFT)  /* 2 (6) */

#define R_SSI_SSIFCR_RTRG_SHIFT                   (4)  /* Receive Data Trigger Number */
#define R_SSI_SSIFCR_RTRG_MASK                    0x30
#  define R_SSI_SSIFCR_RTRG_00                            (0 << R_SSI_SSIFCR_RTRG_SHIFT)  /* 1 */
#  define R_SSI_SSIFCR_RTRG_01                            (1 << R_SSI_SSIFCR_RTRG_SHIFT)  /* 2 */
#  define R_SSI_SSIFCR_RTRG_10                            (2 << R_SSI_SSIFCR_RTRG_SHIFT)  /* 4 */
#  define R_SSI_SSIFCR_RTRG_11                            (3 << R_SSI_SSIFCR_RTRG_SHIFT)  /* 6 */

#define R_SSI_SSIFCR_TIE                          (1 << 3)  /* Transmit Interrupt Enable NOTE: TXI can be cleared by clearing either the TDE flag (see the description of the TDE bit for details) or TIE bit. */

#define R_SSI_SSIFCR_RIE                          (1 << 2)  /* Receive Interrupt Enable NOTE: RXI can be cleared by clearing either the RDF flag (see the description of the RDF bit for details) or RIE bit. */

#define R_SSI_SSIFCR_TFRST                        (1 << 1)  /* Transmit FIFO Data Register Reset */

#define R_SSI_SSIFCR_RFRST                        (1 << 0)  /* Receive FIFO Data Register Reset */

#define R_SSI_SSIFCR_BSW                          (1 << 11)  /* Byte Swap Enable */

/* SSIFSR Register bit definitions */
#define R_SSI_SSIFSR_TDC_SHIFT                    (24)  /* Transmit Data Indicate Flag(Indicates the number of data units stored in SSIFTDR) */
#define R_SSI_SSIFSR_TDC_MASK                     0x3f000000

#define R_SSI_SSIFSR_TDE                          (1 << 16)  /* Transmit Data Empty Flag NOTE: Since the SSIFTDR register is a 32-byte FIFO register, the maximum number of bytes that can be written to it while the TDE flag is 1 is 8 - TDC[3:0]. If writing data to the SSIFTDR register is continued after all the data is written, writing will be invalid and an overflow occurs. */

#define R_SSI_SSIFSR_RDC_SHIFT                    (8)  /* Receive Data Indicate Flag(Indicates the number of data units stored in SSIFRDR) */
#define R_SSI_SSIFSR_RDC_MASK                     0x3f00

#define R_SSI_SSIFSR_RDF                          (1 << 0)  /* Receive Data Full Flag NOTE:  Since the SSIFRDR register is a 32-byte FIFO register, the maximum number of data bytes that can be read from it while the RDF flag is 1 is indicated in the RDC[3:0] flags. If reading data from the SSIFRDR register is continued after all the data is read, undefined values will be read. */

/* SSIFTDR Register bit definitions */
#define R_SSI_SSIFTDR_SSIFTDR_SHIFT               (0)  /* SSIFTDR is a write-only FIFO register consisting of eight stages of 32-bit registers for storing data to be serially transmitted.  NOTE: that when the SSIFTDR register is full of data (32 bytes), the next data cannot be written to it. If writing is attempted, it will be ignored and an overflow occurs. */
#define R_SSI_SSIFTDR_SSIFTDR_MASK                0xffffffff

/* SSIFRDR Register bit definitions */
#define R_SSI_SSIFRDR_SSIFRDR_SHIFT               (0)  /* SSIFRDR is a read-only FIFO register consisting of eight stages of 32-bit registers for storing serially received data. */
#define R_SSI_SSIFRDR_SSIFRDR_MASK                0xffffffff

/* SSIOFR Register bit definitions */
#define R_SSI_SSIOFR_BCKASTP                      (1 << 9)  /* Whether to Enable Stopping BCK Output When SSIE is in Idle Status */

#define R_SSI_SSIOFR_LRCONT                       (1 << 8)  /* Whether to Enable LRCK/FS Continuation */

#define R_SSI_SSIOFR_OMOD_SHIFT                   (0)  /* Audio Format Select */
#define R_SSI_SSIOFR_OMOD_MASK                    0x3
#  define R_SSI_SSIOFR_OMOD_00                            (0 << R_SSI_SSIOFR_OMOD_SHIFT)  /* I2S format */
#  define R_SSI_SSIOFR_OMOD_01                            (1 << R_SSI_SSIOFR_OMOD_SHIFT)  /* TDM format */
#  define R_SSI_SSIOFR_OMOD_10                            (2 << R_SSI_SSIOFR_OMOD_SHIFT)  /* Monaural format */
#  define R_SSI_SSIOFR_OMOD_11                            (3 << R_SSI_SSIOFR_OMOD_SHIFT)  /* Setting prohibited. */

/* SSISCR Register bit definitions */
#define R_SSI_SSISCR_TDES_SHIFT                   (8)  /* TDE Setting Condition Select */
#define R_SSI_SSISCR_TDES_MASK                    0x1f00
#  define R_SSI_SSISCR_TDES_00000                         (0 << R_SSI_SSISCR_TDES_SHIFT)  /* SSIFTDR has one stage or more free space */
#  define R_SSI_SSISCR_TDES_00001                         (1 << R_SSI_SSISCR_TDES_SHIFT)  /* SSIFTDR has two stages or more free space (snip) */
#  define R_SSI_SSISCR_TDES_11110                         (30 << R_SSI_SSISCR_TDES_SHIFT)  /* SSIFTDR has thirty-one stages or more free space */
#  define R_SSI_SSISCR_TDES_11111                         (31 << R_SSI_SSISCR_TDES_SHIFT)  /* SSIFTDR has thirty-two stages or more free space. */

#define R_SSI_SSISCR_RDFS_SHIFT                   (0)  /* RDF Setting Condition Select */
#define R_SSI_SSISCR_RDFS_MASK                    0x1f
#  define R_SSI_SSISCR_RDFS_00000                         (0 << R_SSI_SSISCR_RDFS_SHIFT)  /* SSIFRDR has one stage or more data size */
#  define R_SSI_SSISCR_RDFS_00001                         (1 << R_SSI_SSISCR_RDFS_SHIFT)  /* SSIFRDR has two stages or more data size (snip) */
#  define R_SSI_SSISCR_RDFS_11110                         (30 << R_SSI_SSISCR_RDFS_SHIFT)  /* SSIFRDR has thirty-one stages or more data size */
#  define R_SSI_SSISCR_RDFS_11111                         (31 << R_SSI_SSISCR_RDFS_SHIFT)  /* SSIFRDR has thirty-two stages or more data size. */


/* Maximum number of channels */

#define SSI_MAX_CHANNELS    2

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SSI_H */

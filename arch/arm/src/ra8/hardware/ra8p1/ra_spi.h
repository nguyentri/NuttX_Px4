/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_spi.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SPI_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SPI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SPI Base Address */
#ifndef R_SPI_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_SPI_BASE           0x4035c000
#else
#define R_SPI_BASE           0x5035c000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_SPI_CH_STRIDE    0x002e9e00
#define R_SPI_CH_BASE(ch)   (R_SPI_BASE + ((uint32_t)(ch) * R_SPI_CH_STRIDE))

/* SPI Register Offsets */

#define R_SPI_SPCR_OFFSET                         0x00000000  /* SPI Control Register */
#define R_SPI_SSLP_OFFSET                         0x00000001  /* SPI Slave Select Polarity Register */
#define R_SPI_SPPCR_OFFSET                        0x00000002  /* SPI Pin Control Register */
#define R_SPI_SPSR_OFFSET                         0x00000003  /* SPI Status Register */
#define R_SPI_SPDR_OFFSET                         0x00000004  /* SPI Data Register */
#define R_SPI_SPDR_HA_OFFSET                      0x00000004  /* SPI Data Register ( halfword access ) */
#define R_SPI_SPDR_BY_OFFSET                      0x00000004  /* SPI Data Register ( byte access ) */
#define R_SPI_SPSCR_OFFSET                        0x00000008  /* SPI Sequence Control Register */
#define R_SPI_SPSSR_OFFSET                        0x00000009  /* SPI Sequence Status Register */
#define R_SPI_SPBR_OFFSET                         0x0000000a  /* SPI Bit Rate Register */
#define R_SPI_SPDCR_OFFSET                        0x0000000b  /* SPI Data Control Register */
#define R_SPI_SPCKD_OFFSET                        0x0000000c  /* SPI Clock Delay Register */
#define R_SPI_SSLND_OFFSET                        0x0000000d  /* SPI Slave Select Negation Delay Register */
#define R_SPI_SPND_OFFSET                         0x0000000e  /* SPI Next-Access Delay Register */
#define R_SPI_SPCR2_OFFSET                        0x0000000f  /* SPI Control Register 2 */
/* SPCMD[%s] Registers () */
#define R_SPI_SPCMD_OFFSET(m)                     (0x00000010 + ((m) * 0x00000002))  /* SPI Command Register %s */
#define R_SPI_SPDCR2_OFFSET                       0x00000020  /* SPI Data Control Register 2 */
#define R_SPI_SPCR3_OFFSET                        0x00000021  /* RSPI Control Register 3 */
#define R_SPI_SPPR_OFFSET                         0x0000003e  /* RSPI Parameter Read Register */

/* SPI Register Addresses */

#define R_SPI_SPCR(n)                             (R_SPI_CH_BASE(n) + R_SPI_SPCR_OFFSET)
#define R_SPI_SSLP(n)                             (R_SPI_CH_BASE(n) + R_SPI_SSLP_OFFSET)
#define R_SPI_SPPCR(n)                            (R_SPI_CH_BASE(n) + R_SPI_SPPCR_OFFSET)
#define R_SPI_SPSR(n)                             (R_SPI_CH_BASE(n) + R_SPI_SPSR_OFFSET)
#define R_SPI_SPDR(n)                             (R_SPI_CH_BASE(n) + R_SPI_SPDR_OFFSET)
#define R_SPI_SPDR_HA(n)                          (R_SPI_CH_BASE(n) + R_SPI_SPDR_HA_OFFSET)
#define R_SPI_SPDR_BY(n)                          (R_SPI_CH_BASE(n) + R_SPI_SPDR_BY_OFFSET)
#define R_SPI_SPSCR(n)                            (R_SPI_CH_BASE(n) + R_SPI_SPSCR_OFFSET)
#define R_SPI_SPSSR(n)                            (R_SPI_CH_BASE(n) + R_SPI_SPSSR_OFFSET)
#define R_SPI_SPBR(n)                             (R_SPI_CH_BASE(n) + R_SPI_SPBR_OFFSET)
#define R_SPI_SPDCR(n)                            (R_SPI_CH_BASE(n) + R_SPI_SPDCR_OFFSET)
#define R_SPI_SPCKD(n)                            (R_SPI_CH_BASE(n) + R_SPI_SPCKD_OFFSET)
#define R_SPI_SSLND(n)                            (R_SPI_CH_BASE(n) + R_SPI_SSLND_OFFSET)
#define R_SPI_SPND(n)                             (R_SPI_CH_BASE(n) + R_SPI_SPND_OFFSET)
#define R_SPI_SPCR2(n)                            (R_SPI_CH_BASE(n) + R_SPI_SPCR2_OFFSET)
#define R_SPI_SPCMD(n, m)                         (R_SPI_CH_BASE(n) + R_SPI_SPCMD_OFFSET(m))
#define R_SPI_SPDCR2(n)                           (R_SPI_CH_BASE(n) + R_SPI_SPDCR2_OFFSET)
#define R_SPI_SPCR3(n)                            (R_SPI_CH_BASE(n) + R_SPI_SPCR3_OFFSET)
#define R_SPI_SPPR(n)                             (R_SPI_CH_BASE(n) + R_SPI_SPPR_OFFSET)

/* Register bit definitions */
/* SPCR Register bit definitions */
#define R_SPI_SPCR_SPRIE                          (1 << 7)  /* SPI Receive Buffer Full Interrupt Enable */

#define R_SPI_SPCR_SPE                            (1 << 6)  /* SPI Function Enable */

#define R_SPI_SPCR_SPTIE                          (1 << 5)  /* Transmit Buffer Empty Interrupt Enable */

#define R_SPI_SPCR_SPEIE                          (1 << 4)  /* SPI Error Interrupt Enable */

#define R_SPI_SPCR_MSTR                           (1 << 3)  /* SPI Master/Slave Mode Select */

#define R_SPI_SPCR_MODFEN                         (1 << 2)  /* Mode Fault Error Detection Enable */

#define R_SPI_SPCR_TXMD                           (1 << 1)  /* Communications Operating Mode Select */

#define R_SPI_SPCR_SPMS                           (1 << 0)  /* SPI Mode Select */

/* SSLP Register bit definitions */
#define R_SPI_SSLP_SSL3P                          (1 << 3)  /* SSL3 Signal Polarity Setting */

#define R_SPI_SSLP_SSL2P                          (1 << 2)  /* SSL2 Signal Polarity Setting */

#define R_SPI_SSLP_SSL1P                          (1 << 1)  /* SSL1 Signal Polarity Setting */

#define R_SPI_SSLP_SSL0P                          (1 << 0)  /* SSL0 Signal Polarity Setting */

#define R_SPI_SSLP_SSL4P                          (1 << 4)  /* SSL4 Signal Polarity Setting */

#define R_SPI_SSLP_SSL5P                          (1 << 5)  /* SSL5 Signal Polarity Setting */

#define R_SPI_SSLP_SSL6P                          (1 << 6)  /* SSL6 Signal Polarity Setting */

#define R_SPI_SSLP_SSL7P                          (1 << 7)  /* SSL7 Signal Polarity Setting */

/* SPPCR Register bit definitions */
#define R_SPI_SPPCR_MOIFE                         (1 << 5)  /* MOSI Idle Value Fixing Enable */

#define R_SPI_SPPCR_MOIFV                         (1 << 4)  /* MOSI Idle Fixed Value */

#define R_SPI_SPPCR_SPLP2                         (1 << 1)  /* SPI Loopback 2 */

#define R_SPI_SPPCR_SPLP                          (1 << 0)  /* SPI Loopback */

/* SPSR Register bit definitions */
#define R_SPI_SPSR_SPRF                           (1 << 7)  /* SPI Receive Buffer Full Flag */

#define R_SPI_SPSR_SPTEF                          (1 << 5)  /* SPI Transmit Buffer Empty Flag */

#define R_SPI_SPSR_UDRF                           (1 << 4)  /* Underrun Error Flag(When MODF is 0,  This bit is invalid.) */

#define R_SPI_SPSR_PERF                           (1 << 3)  /* Parity Error Flag */

#define R_SPI_SPSR_MODF                           (1 << 2)  /* Mode Fault Error Flag */

#define R_SPI_SPSR_IDLNF                          (1 << 1)  /* SPI Idle Flag */

#define R_SPI_SPSR_OVRF                           (1 << 0)  /* Overrun Error Flag */

#define R_SPI_SPSR_CENDF                          (1 << 6)  /* Communication End Flag */

/* SPSCR Register bit definitions */
#define R_SPI_SPSCR_SPSLN_SHIFT                   (0)  /* RSPI Sequence Length Specification
The order in which the SPCMD0 to SPCMD07 registers are to be referenced is changed in accordance with the sequence length that is set in these bits. The relationship among the setting of these bits, sequence length, and SPCMD0 to SPCMD7 registers referenced by the RSPI is shown above. However, the RSPI in slave mode always references SPCMD0. */
#define R_SPI_SPSCR_SPSLN_MASK                    0x7
#  define R_SPI_SPSCR_SPSLN_000                           (0 << R_SPI_SPSCR_SPSLN_SHIFT)  /* Length 1    SPDMDx   x = 0->0->... */
#  define R_SPI_SPSCR_SPSLN_001                           (1 << R_SPI_SPSCR_SPSLN_SHIFT)  /* Length 2    SPDMDx   x = 0->1->0->... */
#  define R_SPI_SPSCR_SPSLN_010                           (2 << R_SPI_SPSCR_SPSLN_SHIFT)  /* Length 3    SPDMDx   x = 0->1->2->0->... */
#  define R_SPI_SPSCR_SPSLN_011                           (3 << R_SPI_SPSCR_SPSLN_SHIFT)  /* Length 4    SPDMDx   x = 0->1->2->3->0->... */
#  define R_SPI_SPSCR_SPSLN_100                           (4 << R_SPI_SPSCR_SPSLN_SHIFT)  /* Length 5    SPDMDx   x = 0->1->2->3->4->0->... */
#  define R_SPI_SPSCR_SPSLN_101                           (5 << R_SPI_SPSCR_SPSLN_SHIFT)  /* Length 6    SPDMDx   x = 0->1->2->3->4->5->0->... */
#  define R_SPI_SPSCR_SPSLN_110                           (6 << R_SPI_SPSCR_SPSLN_SHIFT)  /* Length 7    SPDMDx   x = 0->1->2->3->4->5->6->0->... */
#  define R_SPI_SPSCR_SPSLN_111                           (7 << R_SPI_SPSCR_SPSLN_SHIFT)  /* Length 8    SPDMDx   x = 0->1->2->3->4->5->6->7->0->... */

/* SPBR Register bit definitions */
#define R_SPI_SPBR_SPR_SHIFT                      (0)  /* SPBR sets the bit rate in master mode. */
#define R_SPI_SPBR_SPR_MASK                       0xff

/* SPDCR Register bit definitions */
#define R_SPI_SPDCR_SPBYT                         (1 << 6)  /* SPI Byte Access Specification */

#define R_SPI_SPDCR_SPLW                          (1 << 5)  /* SPI Word Access/Halfword Access Specification */

#define R_SPI_SPDCR_SPRDTD                        (1 << 4)  /* SPI Receive/Transmit Data Selection */

#define R_SPI_SPDCR_SPFC_SHIFT                    (0)  /* Number of Frames Specification */
#define R_SPI_SPDCR_SPFC_MASK                     0x3
#  define R_SPI_SPDCR_SPFC_00                             (0 << R_SPI_SPDCR_SPFC_SHIFT)  /* 1 frame */
#  define R_SPI_SPDCR_SPFC_01                             (1 << R_SPI_SPDCR_SPFC_SHIFT)  /* 2 frames */
#  define R_SPI_SPDCR_SPFC_10                             (2 << R_SPI_SPDCR_SPFC_SHIFT)  /* 3 frames */
#  define R_SPI_SPDCR_SPFC_11                             (3 << R_SPI_SPDCR_SPFC_SHIFT)  /* 4 frames. */

#define R_SPI_SPDCR_SLSEL_SHIFT                   (2)  /* SSL Pin Output Select */
#define R_SPI_SPDCR_SLSEL_MASK                    0xc
#  define R_SPI_SPDCR_SLSEL_00                            (0 << R_SPI_SPDCR_SLSEL_SHIFT)  /* SSL2 to SSL7->output, SSL1->output */
#  define R_SPI_SPDCR_SLSEL_01                            (1 << R_SPI_SPDCR_SLSEL_SHIFT)  /* SSL2 to SSL7->I/O, SSL1->I/O  */
#  define R_SPI_SPDCR_SLSEL_10                            (2 << R_SPI_SPDCR_SLSEL_SHIFT)  /* SSL2 to SSL7->I/O, SSL1->output */
#  define R_SPI_SPDCR_SLSEL_11                            (3 << R_SPI_SPDCR_SLSEL_SHIFT)  /* Setting prohibited */

/* SPCKD Register bit definitions */
#define R_SPI_SPCKD_SCKDL_SHIFT                   (0)  /* RSPCK Delay Setting */
#define R_SPI_SPCKD_SCKDL_MASK                    0x7
#  define R_SPI_SPCKD_SCKDL_000                           (0 << R_SPI_SPCKD_SCKDL_SHIFT)  /* 1 RSPCK */
#  define R_SPI_SPCKD_SCKDL_001                           (1 << R_SPI_SPCKD_SCKDL_SHIFT)  /* 2 RSPCK */
#  define R_SPI_SPCKD_SCKDL_010                           (2 << R_SPI_SPCKD_SCKDL_SHIFT)  /* 3 RSPCK */
#  define R_SPI_SPCKD_SCKDL_011                           (3 << R_SPI_SPCKD_SCKDL_SHIFT)  /* 4 RSPCK */
#  define R_SPI_SPCKD_SCKDL_100                           (4 << R_SPI_SPCKD_SCKDL_SHIFT)  /* 5 RSPCK */
#  define R_SPI_SPCKD_SCKDL_101                           (5 << R_SPI_SPCKD_SCKDL_SHIFT)  /* 6 RSPCK */
#  define R_SPI_SPCKD_SCKDL_110                           (6 << R_SPI_SPCKD_SCKDL_SHIFT)  /* 7 RSPCK */
#  define R_SPI_SPCKD_SCKDL_111                           (7 << R_SPI_SPCKD_SCKDL_SHIFT)  /* 8 RSPCK */

/* SSLND Register bit definitions */
#define R_SPI_SSLND_SLNDL_SHIFT                   (0)  /* SSL Negation Delay Setting */
#define R_SPI_SSLND_SLNDL_MASK                    0x7
#  define R_SPI_SSLND_SLNDL_000                           (0 << R_SPI_SSLND_SLNDL_SHIFT)  /* 1 RSPCK */
#  define R_SPI_SSLND_SLNDL_001                           (1 << R_SPI_SSLND_SLNDL_SHIFT)  /* 2 RSPCK */
#  define R_SPI_SSLND_SLNDL_010                           (2 << R_SPI_SSLND_SLNDL_SHIFT)  /* 3 RSPCK */
#  define R_SPI_SSLND_SLNDL_011                           (3 << R_SPI_SSLND_SLNDL_SHIFT)  /* 4 RSPCK */
#  define R_SPI_SSLND_SLNDL_100                           (4 << R_SPI_SSLND_SLNDL_SHIFT)  /* 5 RSPCK */
#  define R_SPI_SSLND_SLNDL_101                           (5 << R_SPI_SSLND_SLNDL_SHIFT)  /* 6 RSPCK */
#  define R_SPI_SSLND_SLNDL_110                           (6 << R_SPI_SSLND_SLNDL_SHIFT)  /* 7 RSPCK */
#  define R_SPI_SSLND_SLNDL_111                           (7 << R_SPI_SSLND_SLNDL_SHIFT)  /* 8 RSPCK */

/* SPND Register bit definitions */
#define R_SPI_SPND_SPNDL_SHIFT                    (0)  /* SPI Next-Access Delay Setting */
#define R_SPI_SPND_SPNDL_MASK                     0x7
#  define R_SPI_SPND_SPNDL_000                            (0 << R_SPI_SPND_SPNDL_SHIFT)  /* 1 RSPCK + 2 PCLK */
#  define R_SPI_SPND_SPNDL_001                            (1 << R_SPI_SPND_SPNDL_SHIFT)  /* 2 RSPCK + 2 PCLK */
#  define R_SPI_SPND_SPNDL_010                            (2 << R_SPI_SPND_SPNDL_SHIFT)  /* 3 RSPCK + 2 PCLK */
#  define R_SPI_SPND_SPNDL_011                            (3 << R_SPI_SPND_SPNDL_SHIFT)  /* 4 RSPCK + 2 PCLK */
#  define R_SPI_SPND_SPNDL_100                            (4 << R_SPI_SPND_SPNDL_SHIFT)  /* 5 RSPCK + 2 PCLK */
#  define R_SPI_SPND_SPNDL_101                            (5 << R_SPI_SPND_SPNDL_SHIFT)  /* 6 RSPCK + 2 PCLK */
#  define R_SPI_SPND_SPNDL_110                            (6 << R_SPI_SPND_SPNDL_SHIFT)  /* 7 RSPCK + 2 PCLK */
#  define R_SPI_SPND_SPNDL_111                            (7 << R_SPI_SPND_SPNDL_SHIFT)  /* 8 RSPCK + 2 PCLK */

/* SPCR2 Register bit definitions */
#define R_SPI_SPCR2_SCKASE                        (1 << 4)  /* RSPCK Auto-Stop Function Enable */

#define R_SPI_SPCR2_PTE                           (1 << 3)  /* Parity Self-Testing */

#define R_SPI_SPCR2_SPIIE                         (1 << 2)  /* SPI Idle Interrupt Enable */

#define R_SPI_SPCR2_SPOE                          (1 << 1)  /* Parity Mode */

#define R_SPI_SPCR2_SPPE                          (1 << 0)  /* Parity Enable */

#define R_SPI_SPCR2_SPTDDL_SHIFT                  (5)  /* RSPI Transmit Data Delay */
#define R_SPI_SPCR2_SPTDDL_MASK                   0xe0
#  define R_SPI_SPCR2_SPTDDL_010                          (2 << R_SPI_SPCR2_SPTDDL_SHIFT)  /* Same as above */
#  define R_SPI_SPCR2_SPTDDL_011                          (3 << R_SPI_SPCR2_SPTDDL_SHIFT)  /* Same as above */
#  define R_SPI_SPCR2_SPTDDL_100                          (4 << R_SPI_SPCR2_SPTDDL_SHIFT)  /* Same as above */
#  define R_SPI_SPCR2_SPTDDL_101                          (5 << R_SPI_SPCR2_SPTDDL_SHIFT)  /* Same as above */
#  define R_SPI_SPCR2_SPTDDL_110                          (6 << R_SPI_SPCR2_SPTDDL_SHIFT)  /* Same as above */
#  define R_SPI_SPCR2_SPTDDL_111                          (7 << R_SPI_SPCR2_SPTDDL_SHIFT)  /* Same as above */

/* SPCMD Register bit definitions */
#define R_SPI_SPCMD_SCKDEN                        (1 << 15)  /* RSPCK Delay Setting Enable */

#define R_SPI_SPCMD_SLNDEN                        (1 << 14)  /* SSL Negation Delay Setting Enable */

#define R_SPI_SPCMD_SPNDEN                        (1 << 13)  /* SPI Next-Access Delay Enable */

#define R_SPI_SPCMD_LSBF                          (1 << 12)  /* SPI LSB First */

#define R_SPI_SPCMD_SPB_SHIFT                     (8)  /* SPI Data Length Setting */
#define R_SPI_SPCMD_SPB_MASK                      0xf00
#  define R_SPI_SPCMD_SPB_0100                            (4 << R_SPI_SPCMD_SPB_SHIFT)  /* 8 bits */
#  define R_SPI_SPCMD_SPB_0101                            (5 << R_SPI_SPCMD_SPB_SHIFT)  /* 8 bits */
#  define R_SPI_SPCMD_SPB_0110                            (6 << R_SPI_SPCMD_SPB_SHIFT)  /* 8 bits */
#  define R_SPI_SPCMD_SPB_0111                            (7 << R_SPI_SPCMD_SPB_SHIFT)  /* 8 bits */
#  define R_SPI_SPCMD_SPB_1000                            (8 << R_SPI_SPCMD_SPB_SHIFT)  /* 9 bits */
#  define R_SPI_SPCMD_SPB_1001                            (9 << R_SPI_SPCMD_SPB_SHIFT)  /* 10 bits */
#  define R_SPI_SPCMD_SPB_1010                            (10 << R_SPI_SPCMD_SPB_SHIFT)  /* 11 bits */
#  define R_SPI_SPCMD_SPB_1011                            (11 << R_SPI_SPCMD_SPB_SHIFT)  /* 12 bits */
#  define R_SPI_SPCMD_SPB_1100                            (12 << R_SPI_SPCMD_SPB_SHIFT)  /* 13 bits */
#  define R_SPI_SPCMD_SPB_1101                            (13 << R_SPI_SPCMD_SPB_SHIFT)  /* 14 bits */
#  define R_SPI_SPCMD_SPB_1110                            (14 << R_SPI_SPCMD_SPB_SHIFT)  /* 15 bits */
#  define R_SPI_SPCMD_SPB_1111                            (15 << R_SPI_SPCMD_SPB_SHIFT)  /* 16 bits */

#define R_SPI_SPCMD_SSLKP                         (1 << 7)  /* SSL Signal Level Keeping */

#define R_SPI_SPCMD_SSLA_SHIFT                    (4)  /* SSL Signal Assertion Setting */
#define R_SPI_SPCMD_SSLA_MASK                     0x70
#  define R_SPI_SPCMD_SSLA_000                            (0 << R_SPI_SPCMD_SSLA_SHIFT)  /* SSL0 */
#  define R_SPI_SPCMD_SSLA_001                            (1 << R_SPI_SPCMD_SSLA_SHIFT)  /* SSL1 */
#  define R_SPI_SPCMD_SSLA_010                            (2 << R_SPI_SPCMD_SSLA_SHIFT)  /* SSL2 */
#  define R_SPI_SPCMD_SSLA_011                            (3 << R_SPI_SPCMD_SSLA_SHIFT)  /* SSL3 */

#define R_SPI_SPCMD_BRDV_SHIFT                    (2)  /* Bit Rate Division Setting */
#define R_SPI_SPCMD_BRDV_MASK                     0xc
#  define R_SPI_SPCMD_BRDV_00                             (0 << R_SPI_SPCMD_BRDV_SHIFT)  /* These bits select the base bit rate */
#  define R_SPI_SPCMD_BRDV_01                             (1 << R_SPI_SPCMD_BRDV_SHIFT)  /* These bits select the base bit rate divided by 2 */
#  define R_SPI_SPCMD_BRDV_10                             (2 << R_SPI_SPCMD_BRDV_SHIFT)  /* These bits select the base bit rate divided by 4 */
#  define R_SPI_SPCMD_BRDV_11                             (3 << R_SPI_SPCMD_BRDV_SHIFT)  /* These bits select the base bit rate divided by 8 */

#define R_SPI_SPCMD_CPOL                          (1 << 1)  /* RSPCK Polarity Setting */

#define R_SPI_SPCMD_CPHA                          (1 << 0)  /* RSPCK Phase Setting */

/* SPDCR2 Register bit definitions */
#define R_SPI_SPDCR2_BYSW                         (1 << 0)  /* Byte Swap Operating Mode  Select */

#define R_SPI_SPDCR2_SINV                         (1 << 1)  /* Serial data invert bit */

/* SPSSR Register bit definitions */
#define R_SPI_SPSSR_SPCP_SHIFT                    (0)  /* RSPI Command Pointer */
#define R_SPI_SPSSR_SPCP_MASK                     0x7
#  define R_SPI_SPSSR_SPCP_000                            (0 << R_SPI_SPSSR_SPCP_SHIFT)  /* SPCMD0 */
#  define R_SPI_SPSSR_SPCP_001                            (1 << R_SPI_SPSSR_SPCP_SHIFT)  /* SPCMD1 */
#  define R_SPI_SPSSR_SPCP_010                            (2 << R_SPI_SPSSR_SPCP_SHIFT)  /* SPCMD2 */
#  define R_SPI_SPSSR_SPCP_011                            (3 << R_SPI_SPSSR_SPCP_SHIFT)  /* SPCMD3 */
#  define R_SPI_SPSSR_SPCP_100                            (4 << R_SPI_SPSSR_SPCP_SHIFT)  /* SPCMD4 */
#  define R_SPI_SPSSR_SPCP_101                            (5 << R_SPI_SPSSR_SPCP_SHIFT)  /* SPCMD5 */
#  define R_SPI_SPSSR_SPCP_110                            (6 << R_SPI_SPSSR_SPCP_SHIFT)  /* SPCMD6 */
#  define R_SPI_SPSSR_SPCP_111                            (7 << R_SPI_SPSSR_SPCP_SHIFT)  /* SPCMD7 */

#define R_SPI_SPSSR_SPECM_SHIFT                   (4)  /* RSPI Error Command */
#define R_SPI_SPSSR_SPECM_MASK                    0x70
#  define R_SPI_SPSSR_SPECM_000                           (0 << R_SPI_SPSSR_SPECM_SHIFT)  /* SPCMD0 */
#  define R_SPI_SPSSR_SPECM_001                           (1 << R_SPI_SPSSR_SPECM_SHIFT)  /* SPCMD1 */
#  define R_SPI_SPSSR_SPECM_010                           (2 << R_SPI_SPSSR_SPECM_SHIFT)  /* SPCMD2 */
#  define R_SPI_SPSSR_SPECM_011                           (3 << R_SPI_SPSSR_SPECM_SHIFT)  /* SPCMD3 */
#  define R_SPI_SPSSR_SPECM_100                           (4 << R_SPI_SPSSR_SPECM_SHIFT)  /* SPCMD4 */
#  define R_SPI_SPSSR_SPECM_101                           (5 << R_SPI_SPSSR_SPECM_SHIFT)  /* SPCMD5 */
#  define R_SPI_SPSSR_SPECM_110                           (6 << R_SPI_SPSSR_SPECM_SHIFT)  /* SPCMD6 */
#  define R_SPI_SPSSR_SPECM_111                           (7 << R_SPI_SPSSR_SPECM_SHIFT)  /* SPCMD7 */

/* SPCR3 Register bit definitions */
#define R_SPI_SPCR3_ETXMD                         (1 << 0)  /* Extended Communication Mode Select */

#define R_SPI_SPCR3_BFDS                          (1 << 1)  /* Between Burst Transfer Frames Delay Select */

#define R_SPI_SPCR3_CENDIE                        (1 << 4)  /* RSPI Communication End Interrupt Enable */

/* SPPR Register bit definitions */
#define R_SPI_SPPR_BUFWID                         (1 << 4)  /* Buffer Width check */

#define R_SPI_SPPR_BUFNUM_SHIFT                   (8)  /* Buffer Number check */
#define R_SPI_SPPR_BUFNUM_MASK                    0x700
#  define R_SPI_SPPR_BUFNUM_001                           (1 << R_SPI_SPPR_BUFNUM_SHIFT)  /* 1 Buffer */
#  define R_SPI_SPPR_BUFNUM_100                           (4 << R_SPI_SPPR_BUFNUM_SHIFT)  /* 4 Buffer */

#define R_SPI_SPPR_CMDNUM_SHIFT                   (12)  /* Command Number check */
#define R_SPI_SPPR_CMDNUM_MASK                    0xf000
#  define R_SPI_SPPR_CMDNUM_0001                          (1 << R_SPI_SPPR_CMDNUM_SHIFT)  /* 1 Command */
#  define R_SPI_SPPR_CMDNUM_1000                          (8 << R_SPI_SPPR_CMDNUM_SHIFT)  /* 8 Command */


/* Maximum number of channels */

#define SPI_MAX_CHANNELS    8

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SPI_H */

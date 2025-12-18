/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_spi.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SPI_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SPI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SPI Base Addresses ****************************************************/

#ifndef RZV_SPI0_BASE
#  define RZV_SPI0_BASE               0x12800000
#endif
#ifndef RZV_SPI1_BASE
#  define RZV_SPI1_BASE               0x12800400
#endif
#ifndef RZV_SPI2_BASE
#  define RZV_SPI2_BASE               0x12800800
#endif

/* SPI Register Offsets ***************************************************/

#define RZV_SPI_SPCMD_OFFSET(m)                 (0x00000014 + ((m) * 0x00000004))  /* SPCMD Register %s */

/* Note: provide simple, non-parameterized offsets that the driver expects
 * in addition to the parameterized SPCMD macro above. Some driver code
 * uses object-like names (for channel 0) such as RZV_SPI_SPCMD0_OFFSET
 * and RZV_SPI_SPBR_OFFSET. Define those here for compatibility.
 */

/* SPBR (Bit Rate) register - located before SPCMD */
#define RZV_SPI_SPBR_OFFSET                          0x0010  /* SPI Bit Rate Register */

/* SPCMD0..7 convenience offsets */
#define RZV_SPI_SPCMD0_OFFSET                        RZV_SPI_SPCMD_OFFSET(0)
#define RZV_SPI_SPCMD1_OFFSET                        RZV_SPI_SPCMD_OFFSET(1)
#define RZV_SPI_SPCMD2_OFFSET                        RZV_SPI_SPCMD_OFFSET(2)
#define RZV_SPI_SPCMD3_OFFSET                        RZV_SPI_SPCMD_OFFSET(3)
#define RZV_SPI_SPCMD4_OFFSET                        RZV_SPI_SPCMD_OFFSET(4)
#define RZV_SPI_SPCMD5_OFFSET                        RZV_SPI_SPCMD_OFFSET(5)
#define RZV_SPI_SPCMD6_OFFSET                        RZV_SPI_SPCMD_OFFSET(6)
#define RZV_SPI_SPCMD7_OFFSET                        RZV_SPI_SPCMD_OFFSET(7)

#define RZV_SPI_SPDR_OFFSET                            0x0000  /* SPI Data Register */
#define RZV_SPI_SPDECR_OFFSET                          0x0004  /* SPI Delay Control Register */
#define RZV_SPI_SPCR_OFFSET                           0x0008  /* SPI Control Register */
#define RZV_SPI_SPDCR_OFFSET                             0x0040  /* SPI Data Control Register */
#define RZV_SPI_SPDCR2_OFFSET                            0x0044  /* SPI Data Control Register 2 */
#define RZV_SPI_SPSR_OFFSET                              0x0050  /* SPI Status Register */
#define RZV_SPI_SPTFSR_OFFSET                            0x0058  /* SPI Transfer FIFO Status Register */
#define RZV_SPI_SPRFSR_OFFSET                            0x005C  /* SPI Receive FIFO Status Register */
#define RZV_SPI_SPPSR_OFFSET                             0x0060  /* SPI Polling RegisterPPSR */
#define RZV_SPI_SPSRC_OFFSET                             0x0068  /* SPI Status Clear Register */
#define RZV_SPI_SPFCR_OFFSET                             0x006C  /* SPI FIFO Clear Register */

/* SPI Register Addresses **************************************************/

#define RZV_SPI_SPCMD(ch,m)                     (RZV_SPI##ch##_BASE + RZV_SPI_SPCMD_OFFSET(m))
#define RZV_SPI_SPDR(ch)                             (RZV_SPI##ch##_BASE + RZV_SPI_SPDR_OFFSET)
#define RZV_SPI_SPDECR(ch)                           (RZV_SPI##ch##_BASE + RZV_SPI_SPDECR_OFFSET)
#define RZV_SPI_SPCR(ch)                             (RZV_SPI##ch##_BASE + RZV_SPI_SPCR_OFFSET)
#define RZV_SPI_SPDCR(ch)                            (RZV_SPI##ch##_BASE + RZV_SPI_SPDCR_OFFSET)
#define RZV_SPI_SPDCR2(ch)                           (RZV_SPI##ch##_BASE + RZV_SPI_SPDCR2_OFFSET)
#define RZV_SPI_SPSR(ch)                             (RZV_SPI##ch##_BASE + RZV_SPI_SPSR_OFFSET)
#define RZV_SPI_SPTFSR(ch)                           (RZV_SPI##ch##_BASE + RZV_SPI_SPTFSR_OFFSET)
#define RZV_SPI_SPRFSR(ch)                           (RZV_SPI##ch##_BASE + RZV_SPI_SPRFSR_OFFSET)
#define RZV_SPI_SPPSR(ch)                            (RZV_SPI##ch##_BASE + RZV_SPI_SPPSR_OFFSET)
#define RZV_SPI_SPSRC(ch)                            (RZV_SPI##ch##_BASE + RZV_SPI_SPSRC_OFFSET)
#define RZV_SPI_SPFCR(ch)                            (RZV_SPI##ch##_BASE + RZV_SPI_SPFCR_OFFSET)

/* SPI SPCMD Register Bit Definitions (Parameterized) **********************/

#define SPI_SPCMD_CPHA                                (1 << 0)  /* Cpha */
#define SPI_SPCMD_CPOL                                (1 << 1)  /* Cpol */
#define SPI_SPCMD_BRDV_SHIFT                              (2)      /* Bits 2-3: Brdv */
#define SPI_SPCMD_BRDV_MASK                             (0x3 << SPI_SPCMD_BRDV_SHIFT)
#define SPI_SPCMD_BRDV(val)                             (((val) << SPI_SPCMD_BRDV_SHIFT) & SPI_SPCMD_BRDV_MASK)
#define SPI_SPCMD_SSLKP                                     (1 << 7)  /* Sslkp */
#define SPI_SPCMD_LSBF                                      (1 << 12)  /* Lsbf */
#define SPI_SPCMD_SPNDEN(m)                               (1 << 13)  /* Spnden */
#define SPI_SPCMD_SLNDEN(m)                               (1 << 14)  /* Slnden */
#define SPI_SPCMD_SCKDEN(m)                               (1 << 15)  /* Sckden */
#define SPI_SPCMD_SPB_SHIFT                               (16)      /* Bits 16-20: Spb */
/* Non-parameterized mask and helper for the data-length field. The driver
 * uses non-parameterized names in several places, so provide object-like
 * aliases for the mask and value helper. */
#define SPI_SPCMD_SPB_MASK                                (0x1f << SPI_SPCMD_SPB_SHIFT)
#define SPI_SPCMD_SPB_VAL(val)                            (((val) << SPI_SPCMD_SPB_SHIFT) & SPI_SPCMD_SPB_MASK)
/* (legacy parameter-less name 'SPI_SPCMD_SPB_MASK' is provided above) */
#define SPI_SPCMD_SSLA_SHIFT                              (24)      /* Bits 24-25: Ssla */
#define SPI_SPCMD_SSLA_MASK(m)                            (0x3 << SPI_SPCMD_SSLA_SHIFT)
#define SPI_SPCMD_SSLA(m,val)                             (((val) << SPI_SPCMD_SSLA_SHIFT) & SPI_SPCMD_SSLA_MASK(m))

/* SPI SPCR Register Bit Definitions (Parameterized) ***********************/

#define SPI_SPCR_RMFM_SHIFT                               (0)      /* Bits 0-4: Rmfm */
#define SPI_SPCR_RMFM_MASK(m)                             (0x1f << SPI_SPCR_RMFM_SHIFT)
#define SPI_SPCR_RMFM(m,val)                              (((val) << SPI_SPCR_RMFM_SHIFT) & SPI_SPCR_RMFM_MASK(m))
#define SPI_SPCR_RMEDTG(m)                                (1 << 6)  /* Rmedtg */
#define SPI_SPCR_RMSTTG(m)                                (1 << 7)  /* Rmsttg */
#define SPI_SPCR_SPDRC_SHIFT                              (8)      /* Bits 8-15: Spdrc */
#define SPI_SPCR_SPDRC_MASK(m)                            (0xff << SPI_SPCR_SPDRC_SHIFT)
#define SPI_SPCR_SPDRC(m,val)                             (((val) << SPI_SPCR_SPDRC_SHIFT) & SPI_SPCR_SPDRC_MASK(m))
#define SPI_SPCR_SPLP(m)                                  (1 << 16)  /* Splp */
#define SPI_SPCR_SPLP2(m)                                 (1 << 17)  /* Splp2 */
#define SPI_SPCR_SPOM(m)                                  (1 << 18)  /* Spom */
#define SPI_SPCR_MOIFV(m)                                 (1 << 20)  /* Moifv */
#define SPI_SPCR_MOIFE(m)                                 (1 << 21)  /* Moife */
#define SPI_SPCR_SPSCKDL_SHIFT                            (24)      /* Bits 24-26: Spsckdl */
#define SPI_SPCR_SPSCKDL_MASK(m)                          (0x7 << SPI_SPCR_SPSCKDL_SHIFT)
#define SPI_SPCR_SPSCKDL(m,val)                           (((val) << SPI_SPCR_SPSCKDL_SHIFT) & SPI_SPCR_SPSCKDL_MASK(m))

/* SPI SPCR Register Bit Definitions *********************************/

#define SPI_SPCR_SPE                            (1 << 0)  /* SPI Function Enable */

#define SPI_SPCR_SPSCKSEL                       (1 << 7)  /* SPI Master Receive Clock Select -  MRCLK (Adjust with Digital Delay */

#define SPI_SPCR_SPPE                           (1 << 8)  /* Parity Enable */

#define SPI_SPCR_SPOE                           (1 << 9)  /* Parity Mode */

#define SPI_SPCR_PTE                            (1 << 11)  /* Parity Self-Diagnosis Enable */

#define SPI_SPCR_SCKASE                         (1 << 12)  /* RSPCK Auto-Stop Function Enable */

#define SPI_SPCR_BFDS                           (1 << 13)  /* Between Burst Transfer Frames Delay Select */

#define SPI_SPCR_MODFEN                         (1 << 14)  /* Mode Fault Error Detection Enable */

#define SPI_SPCR_SPEIE                          (1 << 16)  /* SPI Error Interrupt Enable */

#define SPI_SPCR_SPRIE                          (1 << 17)  /* SPI Receive Buffer Full Interrupt Enable */

#define SPI_SPCR_SPIIE                          (1 << 18)  /* SPI Idle Interrupt Enable */

#define SPI_SPCR_SPDRES                         (1 << 19)  /* SPI Receive Data Ready Error Select */

#define SPI_SPCR_SPTIE                          (1 << 20)  /* SPI Transmit Buffer Empty Interrupt Enable */

#define SPI_SPCR_CENDIE                         (1 << 21)  /* SPI Communication End Interrupt Enable */

#define SPI_SPCR_SPMS                           (1 << 24)  /* SPI Function Enable */

#define SPI_SPCR_SPFRF                          (1 << 25)  /* SPI Frame Format Select */

#define SPI_SPCR_TXMD_SHIFT                     (28)      /* Bits 28-29: Communication Mode Select */
#define SPI_SPCR_TXMD_MASK                      (0x3 << SPI_SPCR_TXMD_SHIFT)

#define SPI_SPCR_MSTR                           (1 << 30)  /* SPI Master/Slave Mode Select */

#define SPI_SPCR_BPEN                           (1 << 31)  /* Synchronization Circuit Bypass Enable */

/* SPI SPDCR Register Bit Definitions ********************************/

#define SPI_SPDCR_BYSW                          (1 << 0)  /* Bysw */

#define SPI_SPDCR_SLSEL_SHIFT                   (1)      /* Bits 1-2: Slsel */
#define SPI_SPDCR_SLSEL_MASK                    (0x3 << SPI_SPDCR_SLSEL_SHIFT)

#define SPI_SPDCR_SPRDTD                        (1 << 3)  /* Sprdtd */

#define SPI_SPDCR_SINV                          (1 << 4)  /* Sinv */

#define SPI_SPDCR_SPFC_SHIFT                    (8)      /* Bits 8-11: Spfc */
#define SPI_SPDCR_SPFC_MASK                     (0xf << SPI_SPDCR_SPFC_SHIFT)

/* SPI SPDCR2 Register Bit Definitions *******************************/

#define SPI_SPDCR2_RTRG_SHIFT                   (0)      /* Bits 0-3: Rtrg */
#define SPI_SPDCR2_RTRG_MASK                    (0xf << SPI_SPDCR2_RTRG_SHIFT)

#define SPI_SPDCR2_TTRG_SHIFT                   (8)      /* Bits 8-11: Ttrg */
#define SPI_SPDCR2_TTRG_MASK                    (0xf << SPI_SPDCR2_TTRG_SHIFT)

/* SPI SPDECR Register Bit Definitions *******************************/

#define SPI_SPDECR_SCKDL_SHIFT                  (0)      /* Bits 0-2: RSPCK Delay Setting */
#define SPI_SPDECR_SCKDL_MASK                   (0x7 << SPI_SPDECR_SCKDL_SHIFT)

#define SPI_SPDECR_SLNDL_SHIFT                  (8)      /* Bits 8-10: SSL Negation Delay Setting */
#define SPI_SPDECR_SLNDL_MASK                   (0x7 << SPI_SPDECR_SLNDL_SHIFT)

#define SPI_SPDECR_SPNDL_SHIFT                  (16)      /* Bits 16-18: SPI Next-Access Delay Setting */
#define SPI_SPDECR_SPNDL_MASK                   (0x7 << SPI_SPDECR_SPNDL_SHIFT)

#define SPI_SPDECR_ARST_SHIFT                   (24)      /* Bits 24-26: Auto Reset Setting */
#define SPI_SPDECR_ARST_MASK                    (0x7 << SPI_SPDECR_ARST_SHIFT)

/* SPI SPFCR Register Bit Definitions ********************************/

#define SPI_SPFCR_SPFRST                        (1 << 0)  /* Spfrst */

/* SPI SPPSR Register Bit Definitions ********************************/

#define SPI_SPPSR_SPEPS                         (1 << 0)  /* Speps */

/* SPI SPRFSR Register Bit Definitions *******************************/

#define SPI_SPRFSR_RFDN_SHIFT                   (0)      /* Bits 0-4: Rfdn */
#define SPI_SPRFSR_RFDN_MASK                    (0x1f << SPI_SPRFSR_RFDN_SHIFT)

/* SPI SPSR Register Bit Definitions *********************************/

#define SPI_SPSR_SPCP_SHIFT                     (8)      /* Bits 8-10: Spcp */
#define SPI_SPSR_SPCP_MASK                      (0x7 << SPI_SPSR_SPCP_SHIFT)

#define SPI_SPSR_SPECM_SHIFT                    (12)      /* Bits 12-14: Specm */
#define SPI_SPSR_SPECM_MASK                     (0x7 << SPI_SPSR_SPECM_SHIFT)

#define SPI_SPSR_SPDRF                          (1 << 23)  /* Spdrf */

#define SPI_SPSR_OVRF                           (1 << 24)  /* Ovrf */

#define SPI_SPSR_IDLNF                          (1 << 25)  /* Idlnf */

#define SPI_SPSR_MODF                           (1 << 26)  /* Modf */

#define SPI_SPSR_PERF                           (1 << 27)  /* Perf */

#define SPI_SPSR_UDRF                           (1 << 28)  /* Udrf */

#define SPI_SPSR_SPTEF                          (1 << 29)  /* Sptef */

#define SPI_SPSR_CENDF                          (1 << 30)  /* Cendf */

#define SPI_SPSR_SPRF                           (1 << 31)  /* Sprf */

/* SPI SPSRC Register Bit Definitions ********************************/

#define SPI_SPSRC_SPDRFC                        (1 << 23)  /* Spdrfc */

#define SPI_SPSRC_OVRFC                         (1 << 24)  /* Ovrfc */

#define SPI_SPSRC_MODFC                         (1 << 26)  /* Modfc */

#define SPI_SPSRC_PERFC                         (1 << 27)  /* Perfc */

#define SPI_SPSRC_UDRFC                         (1 << 28)  /* Udrfc */

#define SPI_SPSRC_SPTEFC                        (1 << 29)  /* Sptefc */

#define SPI_SPSRC_CENDFC                        (1 << 30)  /* Cendfc */

#define SPI_SPSRC_SPRFC                         (1 << 31)  /* Sprfc */

/* SPI SPTFSR Register Bit Definitions *******************************/

#define SPI_SPTFSR_TFDN_SHIFT                   (0)      /* Bits 0-4: Tfdn */
#define SPI_SPTFSR_TFDN_MASK                    (0x1f << SPI_SPTFSR_TFDN_SHIFT)

/* SPI Data Length Settings */
#define SPI_SPB_8_BITS          0x7       /* 8 bits */
#define SPI_SPB_16_BITS         0xF       /* 16 bits */
#define SPI_SPB_24_BITS         0x17      /* 24 bits */
#define SPI_SPB_32_BITS         0x1F      /* 32 bits */

/* Aliases for compatibility */
#define SPI_SPCMD_SPB_8BIT      (SPI_SPB_8_BITS << SPI_SPCMD_SPB_SHIFT)
#define SPI_SPCMD_SPB_16BIT     (SPI_SPB_16_BITS << SPI_SPCMD_SPB_SHIFT)

/* SPI Bit Rate Division Settings */
#define SPI_BRDV_DIV_1          0x0       /* Base clock */
#define SPI_BRDV_DIV_2          0x1       /* Base clock / 2 */
#define SPI_BRDV_DIV_4          0x2       /* Base clock / 4 */
#define SPI_BRDV_DIV_8          0x3       /* Base clock / 8 */

/* SPI Channel definitions */
#define RZV_SPI_CHANNEL_0          0
#define RZV_SPI_CHANNEL_1          1
#define RZV_SPI_CHANNEL_2          2

/* Maximum number of SPI channels */
#define RZV_SPI_MAX_CHANNELS       3

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SPI_H */

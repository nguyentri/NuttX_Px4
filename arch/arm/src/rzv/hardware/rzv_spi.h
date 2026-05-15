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

/* Register offsets confirmed against FSP spi_b_iodefine.h (R9A09G057H).
 * Phase-07 fix: dropped false SPBR_OFFSET=0x10; SPBR now lives in SPCR3[15:8].
 *               SPCR2 (0x0C) and SPCR3 (0x10) added.
 *               RMFM/RMEDTG/RMSTTG/SPDRC/SPLP/MOIFV moved to SPCR2 section.
 */

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SPI_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SPI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SPI Base Addresses (FSP spi_b_iodefine.h R_SPI_B0/1/2_BASE) ***********/

#ifndef RZV_SPI0_BASE
#  define RZV_SPI0_BASE               0x12800000
#endif
#ifndef RZV_SPI1_BASE
#  define RZV_SPI1_BASE               0x12800400
#endif
#ifndef RZV_SPI2_BASE
#  define RZV_SPI2_BASE               0x12800800
#endif

/* SPI Register Offsets (from FSP spi_b_iodefine.h struct R_SPI_B0_Type) **/

#define RZV_SPI_SPDR_OFFSET                          0x0000  /* SPI Data Register (32-bit) */
#define RZV_SPI_SPDECR_OFFSET                        0x0004  /* SPI Delay Control Register */
#define RZV_SPI_SPCR_OFFSET                          0x0008  /* SPI Control Register */
#define RZV_SPI_SPCR2_OFFSET                         0x000C  /* SPI Control Register 2 (RMFM/SPLP/MOIFV/SPDRC) */
#define RZV_SPI_SPCR3_OFFSET                         0x0010  /* SPI Control Register 3 (SSL polarity, SPBR, SPSLN) */

/* NOTE: old RZV_SPI_SPBR_OFFSET=0x10 was WRONG — offset 0x10 is SPCR3.
 * SPBR is in SPCR3[15:8].  Write via 32-bit RMW to preserve SSL polarity
 * bits in SPCR3[3:0] and sequence-length in SPCR3[26:24].
 */
#define SPI_SPCR3_SPBR_SHIFT                         8
#define SPI_SPCR3_SPBR_MASK                          (0xFFu << SPI_SPCR3_SPBR_SHIFT)
#define SPI_SPCR3_SSL0P                              (1 << 0)  /* SSL0 polarity */
#define SPI_SPCR3_SSL1P                              (1 << 1)
#define SPI_SPCR3_SSL2P                              (1 << 2)
#define SPI_SPCR3_SSL3P                              (1 << 3)
#define SPI_SPCR3_SPSLN_SHIFT                        24
#define SPI_SPCR3_SPSLN_MASK                         (0x7u << SPI_SPCR3_SPSLN_SHIFT)

/* SPCMD0-7 at 0x14, 0x18, 0x1C, 0x20, 0x24, 0x28, 0x2C, 0x30 ***********/

#define RZV_SPI_SPCMD_OFFSET(m)                 (0x00000014u + ((m) * 0x00000004u))

/* Convenience aliases */
#define RZV_SPI_SPCMD0_OFFSET                   RZV_SPI_SPCMD_OFFSET(0)
#define RZV_SPI_SPCMD1_OFFSET                   RZV_SPI_SPCMD_OFFSET(1)
#define RZV_SPI_SPCMD2_OFFSET                   RZV_SPI_SPCMD_OFFSET(2)
#define RZV_SPI_SPCMD3_OFFSET                   RZV_SPI_SPCMD_OFFSET(3)
#define RZV_SPI_SPCMD4_OFFSET                   RZV_SPI_SPCMD_OFFSET(4)
#define RZV_SPI_SPCMD5_OFFSET                   RZV_SPI_SPCMD_OFFSET(5)
#define RZV_SPI_SPCMD6_OFFSET                   RZV_SPI_SPCMD_OFFSET(6)
#define RZV_SPI_SPCMD7_OFFSET                   RZV_SPI_SPCMD_OFFSET(7)

/* 3 reserved 32-bit words after SPCMD7 (0x34, 0x38, 0x3C) */

#define RZV_SPI_SPDCR_OFFSET                    0x0040  /* SPI Data Control Register */
#define RZV_SPI_SPDCR2_OFFSET                   0x0044  /* SPI Data Control Register 2 (FIFO thresholds) */
/* 0x48, 0x4C reserved */
#define RZV_SPI_SPSR_OFFSET                     0x0050  /* SPI Status Register (read-only) */
/* 0x54 reserved */
#define RZV_SPI_SPTFSR_OFFSET                   0x0058  /* SPI Transfer FIFO Status Register */
#define RZV_SPI_SPRFSR_OFFSET                   0x005C  /* SPI Receive FIFO Status Register */
#define RZV_SPI_SPPSR_OFFSET                    0x0060  /* SPI Polling Register */
/* 0x64 reserved */
#define RZV_SPI_SPSRC_OFFSET                    0x0068  /* SPI Status Clear Register */
#define RZV_SPI_SPFCR_OFFSET                    0x006C  /* SPI FIFO Clear Register */

/* SPI Register Address Helpers *******************************************/

#define RZV_SPI_SPCMD(ch, m)    (RZV_SPI##ch##_BASE + RZV_SPI_SPCMD_OFFSET(m))
#define RZV_SPI_SPDR(ch)        (RZV_SPI##ch##_BASE + RZV_SPI_SPDR_OFFSET)
#define RZV_SPI_SPDECR(ch)      (RZV_SPI##ch##_BASE + RZV_SPI_SPDECR_OFFSET)
#define RZV_SPI_SPCR(ch)        (RZV_SPI##ch##_BASE + RZV_SPI_SPCR_OFFSET)
#define RZV_SPI_SPCR2(ch)       (RZV_SPI##ch##_BASE + RZV_SPI_SPCR2_OFFSET)
#define RZV_SPI_SPCR3(ch)       (RZV_SPI##ch##_BASE + RZV_SPI_SPCR3_OFFSET)
#define RZV_SPI_SPDCR(ch)       (RZV_SPI##ch##_BASE + RZV_SPI_SPDCR_OFFSET)
#define RZV_SPI_SPDCR2(ch)      (RZV_SPI##ch##_BASE + RZV_SPI_SPDCR2_OFFSET)
#define RZV_SPI_SPSR(ch)        (RZV_SPI##ch##_BASE + RZV_SPI_SPSR_OFFSET)
#define RZV_SPI_SPTFSR(ch)      (RZV_SPI##ch##_BASE + RZV_SPI_SPTFSR_OFFSET)
#define RZV_SPI_SPRFSR(ch)      (RZV_SPI##ch##_BASE + RZV_SPI_SPRFSR_OFFSET)
#define RZV_SPI_SPPSR(ch)       (RZV_SPI##ch##_BASE + RZV_SPI_SPPSR_OFFSET)
#define RZV_SPI_SPSRC(ch)       (RZV_SPI##ch##_BASE + RZV_SPI_SPSRC_OFFSET)
#define RZV_SPI_SPFCR(ch)       (RZV_SPI##ch##_BASE + RZV_SPI_SPFCR_OFFSET)

/* SPCMD Register Bit Definitions (FSP spi_b_iodefine.h SPCMD0_b) *********/

#define SPI_SPCMD_CPHA                          (1u << 0)   /* RSPCK Phase */
#define SPI_SPCMD_CPOL                          (1u << 1)   /* RSPCK Polarity */
#define SPI_SPCMD_BRDV_SHIFT                    (2)
#define SPI_SPCMD_BRDV_MASK                     (0x3u << SPI_SPCMD_BRDV_SHIFT)
#define SPI_SPCMD_BRDV(val)                     (((val) << SPI_SPCMD_BRDV_SHIFT) & SPI_SPCMD_BRDV_MASK)
#define SPI_SPCMD_SSLKP                         (1u << 7)   /* SSL Signal Level Hold */
#define SPI_SPCMD_LSBF                          (1u << 12)  /* RSPI LSB First */
#define SPI_SPCMD_SPNDEN                        (1u << 13)  /* RSPI Next-Access Delay Enable */
#define SPI_SPCMD_SLNDEN                        (1u << 14)  /* SSL Negation Delay Enable */
#define SPI_SPCMD_SCKDEN                        (1u << 15)  /* RSPCK Delay Enable */
#define SPI_SPCMD_SPB_SHIFT                     (16)
#define SPI_SPCMD_SPB_MASK                      (0x1fu << SPI_SPCMD_SPB_SHIFT)
#define SPI_SPCMD_SPB_VAL(val)                  (((val) << SPI_SPCMD_SPB_SHIFT) & SPI_SPCMD_SPB_MASK)
#define SPI_SPCMD_SSLA_SHIFT                    (24)
#define SPI_SPCMD_SSLA_MASK                     (0x3u << SPI_SPCMD_SSLA_SHIFT)
#define SPI_SPCMD_SSLA(val)                     (((val) << SPI_SPCMD_SSLA_SHIFT) & SPI_SPCMD_SSLA_MASK)

/* SPCR Register Bit Definitions (FSP spi_b_iodefine.h SPCR_b) ************/

#define SPI_SPCR_SPE                            (1u << 0)   /* SPI Function Enable */
#define SPI_SPCR_SPSCKSEL                       (1u << 7)   /* SPI Master Receive Clock Select */
#define SPI_SPCR_SPPE                           (1u << 8)   /* Parity Enable */
#define SPI_SPCR_SPOE                           (1u << 9)   /* Parity Mode */
#define SPI_SPCR_PTE                            (1u << 11)  /* Parity Self-Diagnosis Enable */
#define SPI_SPCR_SCKASE                         (1u << 12)  /* RSPCK Auto-Stop Function Enable */
#define SPI_SPCR_BFDS                           (1u << 13)  /* Between Burst Transfer Frames Delay */
#define SPI_SPCR_MODFEN                         (1u << 14)  /* Mode Fault Error Detection Enable */
#define SPI_SPCR_SPEIE                          (1u << 16)  /* SPI Error Interrupt Enable */
#define SPI_SPCR_SPRIE                          (1u << 17)  /* SPI Receive Buffer Full Interrupt Enable */
#define SPI_SPCR_SPIIE                          (1u << 18)  /* SPI Idle Interrupt Enable */
#define SPI_SPCR_SPDRES                         (1u << 19)  /* SPI Receive Data Ready Error Select */
#define SPI_SPCR_SPTIE                          (1u << 20)  /* SPI Transmit Buffer Empty Interrupt Enable */
#define SPI_SPCR_CENDIE                         (1u << 21)  /* SPI Communication End Interrupt Enable */
#define SPI_SPCR_SPMS                           (1u << 24)  /* SPI Mode Select (1=3-wire) */
#define SPI_SPCR_SPFRF                          (1u << 25)  /* SPI Frame Format Select */
#define SPI_SPCR_TXMD_SHIFT                     (28)
#define SPI_SPCR_TXMD_MASK                      (0x3u << SPI_SPCR_TXMD_SHIFT)
#define SPI_SPCR_MSTR                           (1u << 30)  /* Master/Slave Mode Select */
#define SPI_SPCR_BPEN                           (1u << 31)  /* Synchronization Circuit Bypass Enable */

/* SPCR2 Register Bit Definitions (FSP spi_b_iodefine.h SPCR2_b at 0x0C) */
/* Phase-07 fix: these bits were WRONGLY listed under SPCR in old header.  */

#define SPI_SPCR2_RMFM_SHIFT                    (0)
#define SPI_SPCR2_RMFM_MASK                     (0x1fu << SPI_SPCR2_RMFM_SHIFT)
#define SPI_SPCR2_RMFM(val)                     (((val) << SPI_SPCR2_RMFM_SHIFT) & SPI_SPCR2_RMFM_MASK)
#define SPI_SPCR2_RMEDTG                        (1u << 6)   /* End Trigger in Master Receive only */
#define SPI_SPCR2_RMSTTG                        (1u << 7)   /* Start Trigger in Master Receive only */
#define SPI_SPCR2_SPDRC_SHIFT                   (8)
#define SPI_SPCR2_SPDRC_MASK                    (0xffu << SPI_SPCR2_SPDRC_SHIFT)
#define SPI_SPCR2_SPDRC(val)                    (((val) << SPI_SPCR2_SPDRC_SHIFT) & SPI_SPCR2_SPDRC_MASK)
#define SPI_SPCR2_SPLP                          (1u << 16)  /* RSPI Loopback (MOSI→MISO internally) */
#define SPI_SPCR2_SPLP2                         (1u << 17)  /* RSPI Loopback 2 */
#define SPI_SPCR2_SPOM                          (1u << 18)
#define SPI_SPCR2_MOIFV                         (1u << 20)  /* MOSI Idle Fixed Value */
#define SPI_SPCR2_MOIFE                         (1u << 21)  /* MOSI Idle Fixed Value Enable */
#define SPI_SPCR2_SPSCKDL_SHIFT                 (24)
#define SPI_SPCR2_SPSCKDL_MASK                  (0x7u << SPI_SPCR2_SPSCKDL_SHIFT)

/* SPDCR Register Bit Definitions *****************************************/

#define SPI_SPDCR_BYSW                          (1u << 0)   /* Byte Swap */
#define SPI_SPDCR_SLSEL_SHIFT                   (1)
#define SPI_SPDCR_SLSEL_MASK                    (0x3u << SPI_SPDCR_SLSEL_SHIFT)
#define SPI_SPDCR_SPRDTD                        (1u << 3)   /* Receive/Transmit Data Select */
#define SPI_SPDCR_SINV                          (1u << 4)   /* Serial data invert */
#define SPI_SPDCR_SPFC_SHIFT                    (8)
#define SPI_SPDCR_SPFC_MASK                     (0xfu << SPI_SPDCR_SPFC_SHIFT)

/* SPDCR2 Register Bit Definitions ****************************************/

#define SPI_SPDCR2_RTRG_SHIFT                   (0)
#define SPI_SPDCR2_RTRG_MASK                    (0xfu << SPI_SPDCR2_RTRG_SHIFT)
#define SPI_SPDCR2_TTRG_SHIFT                   (8)
#define SPI_SPDCR2_TTRG_MASK                    (0xfu << SPI_SPDCR2_TTRG_SHIFT)

/* SPDECR Register Bit Definitions ****************************************/

#define SPI_SPDECR_SCKDL_SHIFT                  (0)
#define SPI_SPDECR_SCKDL_MASK                   (0x7u << SPI_SPDECR_SCKDL_SHIFT)
#define SPI_SPDECR_SLNDL_SHIFT                  (8)
#define SPI_SPDECR_SLNDL_MASK                   (0x7u << SPI_SPDECR_SLNDL_SHIFT)
#define SPI_SPDECR_SPNDL_SHIFT                  (16)
#define SPI_SPDECR_SPNDL_MASK                   (0x7u << SPI_SPDECR_SPNDL_SHIFT)
#define SPI_SPDECR_ARST_SHIFT                   (24)
#define SPI_SPDECR_ARST_MASK                    (0x7u << SPI_SPDECR_ARST_SHIFT)

/* SPSR Status Register Bit Definitions ***********************************/

#define SPI_SPSR_SPCP_SHIFT                     (8)
#define SPI_SPSR_SPCP_MASK                      (0x7u << SPI_SPSR_SPCP_SHIFT)
#define SPI_SPSR_SPECM_SHIFT                    (12)
#define SPI_SPSR_SPECM_MASK                     (0x7u << SPI_SPSR_SPECM_SHIFT)
#define SPI_SPSR_SPDRF                          (1u << 23)  /* Receive Data Ready Flag */
#define SPI_SPSR_OVRF                           (1u << 24)  /* Overrun Error Flag */
#define SPI_SPSR_IDLNF                          (1u << 25)  /* Idle Flag */
#define SPI_SPSR_MODF                           (1u << 26)  /* Mode Fault Error Flag */
#define SPI_SPSR_PERF                           (1u << 27)  /* Parity Error Flag */
#define SPI_SPSR_UDRF                           (1u << 28)  /* Underrun Error Flag */
#define SPI_SPSR_SPTEF                          (1u << 29)  /* Transmit Buffer Empty Flag */
#define SPI_SPSR_CENDF                          (1u << 30)  /* Communication End Flag */
#define SPI_SPSR_SPRF                           (1u << 31)  /* Receive Buffer Full Flag */

/* SPSRC Status Clear Register Bit Definitions ****************************/

#define SPI_SPSRC_SPDRFC                        (1u << 23)
#define SPI_SPSRC_OVRFC                         (1u << 24)
#define SPI_SPSRC_MODFC                         (1u << 26)
#define SPI_SPSRC_PERFC                         (1u << 27)
#define SPI_SPSRC_UDRFC                         (1u << 28)
#define SPI_SPSRC_SPTEFC                        (1u << 29)
#define SPI_SPSRC_CENDFC                        (1u << 30)
#define SPI_SPSRC_SPRFC                         (1u << 31)

/* Clear all clearable status bits (FSP SPI_B_PRV_SPSRC_ALL_CLEAR) */
#define SPI_SPSRC_ALL_CLEAR  (SPI_SPSRC_SPDRFC | SPI_SPSRC_OVRFC | \
                              SPI_SPSRC_MODFC  | SPI_SPSRC_PERFC | \
                              SPI_SPSRC_UDRFC  | SPI_SPSRC_SPTEFC | \
                              SPI_SPSRC_CENDFC | SPI_SPSRC_SPRFC)

/* SPTFSR / SPRFSR Register Bit Definitions *******************************/

#define SPI_SPTFSR_TFDN_SHIFT                   (0)
#define SPI_SPTFSR_TFDN_MASK                    (0x1fu << SPI_SPTFSR_TFDN_SHIFT)
#define SPI_SPRFSR_RFDN_SHIFT                   (0)
#define SPI_SPRFSR_RFDN_MASK                    (0x1fu << SPI_SPRFSR_RFDN_SHIFT)

/* SPFCR Register Bit Definitions *****************************************/

#define SPI_SPFCR_SPFRST                        (1u << 0)

/* SPPSR Register Bit Definitions *****************************************/

#define SPI_SPPSR_SPEPS                         (1u << 0)

/* SPB (data-length) values for SPCMD.SPB field ***************************/

#define SPI_SPB_8_BITS                          0x07u
#define SPI_SPB_16_BITS                         0x0fu
#define SPI_SPB_24_BITS                         0x17u
#define SPI_SPB_32_BITS                         0x1fu

#define SPI_SPCMD_SPB_8BIT   SPI_SPCMD_SPB_VAL(SPI_SPB_8_BITS)
#define SPI_SPCMD_SPB_16BIT  SPI_SPCMD_SPB_VAL(SPI_SPB_16_BITS)
#define SPI_SPCMD_SPB_32BIT  SPI_SPCMD_SPB_VAL(SPI_SPB_32_BITS)

/* BRDV divider values ****************************************************/

#define SPI_BRDV_DIV_1                          0x0u
#define SPI_BRDV_DIV_2                          0x1u
#define SPI_BRDV_DIV_4                          0x2u
#define SPI_BRDV_DIV_8                          0x3u

/* Error flags to check in SPSR.
 * [M9] MODF requires SPCR.MODFEN; PERF requires SPCR.SPPE — neither is set,
 * so those flags can never assert.  Keep only OVRF and UDRF which are always
 * active and do not depend on enable bits.
 */

#define SPI_ERROR_FLAGS  (SPI_SPSR_OVRF | SPI_SPSR_UDRF)

/* Error flag clear bits in SPSRC (maps 1:1 with SPSR error bits) ********/

#define SPI_ERROR_CLEAR_FLAGS  (SPI_SPSRC_OVRFC | SPI_SPSRC_UDRFC)

/* SPI FIFO depth (SPTFSR.TFDN is 5 bits → max 31 entries; HW depth = 16) */
#define SPI_FIFO_DEPTH                          16

/* SPI Channel Definitions ************************************************/

#define RZV_SPI_CHANNEL_0                       0
#define RZV_SPI_CHANNEL_1                       1
#define RZV_SPI_CHANNEL_2                       2
#define RZV_SPI_MAX_CHANNELS                    3

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SPI_H */

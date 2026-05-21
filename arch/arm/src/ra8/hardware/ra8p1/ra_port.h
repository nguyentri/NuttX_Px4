/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_port.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PORT_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PORT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* PORT Base Address */
#ifndef R_PORT_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_PORT_BASE           0x40400000
#else
#define R_PORT_BASE           0x50400000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_PORT_CH_STRIDE    0x00000020
#define R_PORT_CH_BASE(ch)   (R_PORT_BASE + ((uint32_t)(ch) * R_PORT_CH_STRIDE))

/* PORT Register Offsets */

#define R_PORT_PCNTR1_OFFSET                      0x00000000  /* Port Control Register 1 */
#define R_PORT_PDR_OFFSET                         0x00000000  /* Data direction register */
#define R_PORT_PODR_OFFSET                        0x00000002  /* Output data register */
#define R_PORT_PCNTR2_OFFSET                      0x00000004  /* Port Control Register 2 */
#define R_PORT_PIDR_OFFSET                        0x00000004  /* Input data register */
#define R_PORT_EIDR_OFFSET                        0x00000006  /* Event input data register */
#define R_PORT_PCNTR3_OFFSET                      0x00000008  /* Port Control Register 3 */
#define R_PORT_POSR_OFFSET                        0x00000008  /* Output reset register */
#define R_PORT_PORR_OFFSET                        0x0000000a  /* Output set register */
#define R_PORT_PCNTR4_OFFSET                      0x0000000c  /* Port Control Register 4 */
#define R_PORT_EOSR_OFFSET                        0x0000000c  /* Event output reset register */
#define R_PORT_EORR_OFFSET                        0x0000000e  /* Event output set register */

/* PORT Register Addresses */

#define R_PORT_PCNTR1(port)                       (R_PORT_CH_BASE(port) + R_PORT_PCNTR1_OFFSET)
#define R_PORT_PDR(port)                          (R_PORT_CH_BASE(port) + R_PORT_PDR_OFFSET)
#define R_PORT_PODR(port)                         (R_PORT_CH_BASE(port) + R_PORT_PODR_OFFSET)
#define R_PORT_PCNTR2(port)                       (R_PORT_CH_BASE(port) + R_PORT_PCNTR2_OFFSET)
#define R_PORT_PIDR(port)                         (R_PORT_CH_BASE(port) + R_PORT_PIDR_OFFSET)
#define R_PORT_EIDR(port)                         (R_PORT_CH_BASE(port) + R_PORT_EIDR_OFFSET)
#define R_PORT_PCNTR3(port)                       (R_PORT_CH_BASE(port) + R_PORT_PCNTR3_OFFSET)
#define R_PORT_POSR(port)                         (R_PORT_CH_BASE(port) + R_PORT_POSR_OFFSET)
#define R_PORT_PORR(port)                         (R_PORT_CH_BASE(port) + R_PORT_PORR_OFFSET)
#define R_PORT_PCNTR4(port)                       (R_PORT_CH_BASE(port) + R_PORT_PCNTR4_OFFSET)
#define R_PORT_EOSR(port)                         (R_PORT_CH_BASE(port) + R_PORT_EOSR_OFFSET)
#define R_PORT_EORR(port)                         (R_PORT_CH_BASE(port) + R_PORT_EORR_OFFSET)

/* Register bit definitions */
/* PCNTR1 Register bit definitions */
#define R_PORT_PCNTR1_PDR_SHIFT                   (0)  /* Pmn Direction */
#define R_PORT_PCNTR1_PDR_MASK                    0xffff
#  define R_PORT_PCNTR1_PDR_0                             (0 << R_PORT_PCNTR1_PDR_SHIFT)  /* Input (functions as an input pin) */
#  define R_PORT_PCNTR1_PDR_1                             (1 << R_PORT_PCNTR1_PDR_SHIFT)  /* Output (functions as an output pin). */

#define R_PORT_PCNTR1_PODR_SHIFT                  (16)  /* Pmn Output Data */
#define R_PORT_PCNTR1_PODR_MASK                   0xffff0000
#  define R_PORT_PCNTR1_PODR_0                            (0 << R_PORT_PCNTR1_PODR_SHIFT)  /* Low output */
#  define R_PORT_PCNTR1_PODR_1                            (1 << R_PORT_PCNTR1_PODR_SHIFT)  /* High output. */

/* PDR Register bit definitions */
#define R_PORT_PDR_PDR_S                          (1 << 0)  /* Pmn Direction */

#define R_PORT_PDR_PDR0                           (1 << 0)  /* Pmn Direction */

#define R_PORT_PDR_PDR1                           (1 << 1)  /* Pmn Direction */

#define R_PORT_PDR_PDR2                           (1 << 2)  /* Pmn Direction */

#define R_PORT_PDR_PDR3                           (1 << 3)  /* Pmn Direction */

#define R_PORT_PDR_PDR4                           (1 << 4)  /* Pmn Direction */

#define R_PORT_PDR_PDR5                           (1 << 5)  /* Pmn Direction */

#define R_PORT_PDR_PDR6                           (1 << 6)  /* Pmn Direction */

#define R_PORT_PDR_PDR7                           (1 << 7)  /* Pmn Direction */

#define R_PORT_PDR_PDR8                           (1 << 8)  /* Pmn Direction */

#define R_PORT_PDR_PDR9                           (1 << 9)  /* Pmn Direction */

#define R_PORT_PDR_PDR10                          (1 << 10)  /* Pmn Direction */

#define R_PORT_PDR_PDR11                          (1 << 11)  /* Pmn Direction */

#define R_PORT_PDR_PDR12                          (1 << 12)  /* Pmn Direction */

#define R_PORT_PDR_PDR13                          (1 << 13)  /* Pmn Direction */

#define R_PORT_PDR_PDR14                          (1 << 14)  /* Pmn Direction */

#define R_PORT_PDR_PDR15                          (1 << 15)  /* Pmn Direction */

/* PODR Register bit definitions */
#define R_PORT_PODR_PODR_S                        (1 << 0)  /* Pmn Output Data */

#define R_PORT_PODR_PODR0                         (1 << 0)  /* Pmn Output Data */

#define R_PORT_PODR_PODR1                         (1 << 1)  /* Pmn Output Data */

#define R_PORT_PODR_PODR2                         (1 << 2)  /* Pmn Output Data */

#define R_PORT_PODR_PODR3                         (1 << 3)  /* Pmn Output Data */

#define R_PORT_PODR_PODR4                         (1 << 4)  /* Pmn Output Data */

#define R_PORT_PODR_PODR5                         (1 << 5)  /* Pmn Output Data */

#define R_PORT_PODR_PODR6                         (1 << 6)  /* Pmn Output Data */

#define R_PORT_PODR_PODR7                         (1 << 7)  /* Pmn Output Data */

#define R_PORT_PODR_PODR8                         (1 << 8)  /* Pmn Output Data */

#define R_PORT_PODR_PODR9                         (1 << 9)  /* Pmn Output Data */

#define R_PORT_PODR_PODR10                        (1 << 10)  /* Pmn Output Data */

#define R_PORT_PODR_PODR11                        (1 << 11)  /* Pmn Output Data */

#define R_PORT_PODR_PODR12                        (1 << 12)  /* Pmn Output Data */

#define R_PORT_PODR_PODR13                        (1 << 13)  /* Pmn Output Data */

#define R_PORT_PODR_PODR14                        (1 << 14)  /* Pmn Output Data */

#define R_PORT_PODR_PODR15                        (1 << 15)  /* Pmn Output Data */

/* PCNTR2 Register bit definitions */
#define R_PORT_PCNTR2_PIDR_SHIFT                  (0)  /* Pmn Input Data */
#define R_PORT_PCNTR2_PIDR_MASK                   0xffff
#  define R_PORT_PCNTR2_PIDR_0                            (0 << R_PORT_PCNTR2_PIDR_SHIFT)  /* Low input */
#  define R_PORT_PCNTR2_PIDR_1                            (1 << R_PORT_PCNTR2_PIDR_SHIFT)  /* High input. */

#define R_PORT_PCNTR2_EIDR_SHIFT                  (16)  /* Pmn Event Input Data */
#define R_PORT_PCNTR2_EIDR_MASK                   0xffff0000
#  define R_PORT_PCNTR2_EIDR_0                            (0 << R_PORT_PCNTR2_EIDR_SHIFT)  /* Low input */
#  define R_PORT_PCNTR2_EIDR_1                            (1 << R_PORT_PCNTR2_EIDR_SHIFT)  /* High input. */

/* PIDR Register bit definitions */
#define R_PORT_PIDR_PIDR_S                        (1 << 0)  /* Pmn Input Data */

#define R_PORT_PIDR_PIDR0                         (1 << 0)  /* Pmn Input Data */

#define R_PORT_PIDR_PIDR1                         (1 << 1)  /* Pmn Input Data */

#define R_PORT_PIDR_PIDR2                         (1 << 2)  /* Pmn Input Data */

#define R_PORT_PIDR_PIDR3                         (1 << 3)  /* Pmn Input Data */

#define R_PORT_PIDR_PIDR4                         (1 << 4)  /* Pmn Input Data */

#define R_PORT_PIDR_PIDR5                         (1 << 5)  /* Pmn Input Data */

#define R_PORT_PIDR_PIDR6                         (1 << 6)  /* Pmn Input Data */

#define R_PORT_PIDR_PIDR7                         (1 << 7)  /* Pmn Input Data */

#define R_PORT_PIDR_PIDR8                         (1 << 8)  /* Pmn Input Data */

#define R_PORT_PIDR_PIDR9                         (1 << 9)  /* Pmn Input Data */

#define R_PORT_PIDR_PIDR10                        (1 << 10)  /* Pmn Input Data */

#define R_PORT_PIDR_PIDR11                        (1 << 11)  /* Pmn Input Data */

#define R_PORT_PIDR_PIDR12                        (1 << 12)  /* Pmn Input Data */

#define R_PORT_PIDR_PIDR13                        (1 << 13)  /* Pmn Input Data */

#define R_PORT_PIDR_PIDR14                        (1 << 14)  /* Pmn Input Data */

#define R_PORT_PIDR_PIDR15                        (1 << 15)  /* Pmn Input Data */

/* EIDR Register bit definitions */
#define R_PORT_EIDR_EIDR_S                        (1 << 0)  /* Pmn Event Input Data */

#define R_PORT_EIDR_EIDR0                         (1 << 0)  /* Pmn Event Input Data */

#define R_PORT_EIDR_EIDR1                         (1 << 1)  /* Pmn Event Input Data */

#define R_PORT_EIDR_EIDR2                         (1 << 2)  /* Pmn Event Input Data */

#define R_PORT_EIDR_EIDR3                         (1 << 3)  /* Pmn Event Input Data */

#define R_PORT_EIDR_EIDR4                         (1 << 4)  /* Pmn Event Input Data */

#define R_PORT_EIDR_EIDR5                         (1 << 5)  /* Pmn Event Input Data */

#define R_PORT_EIDR_EIDR6                         (1 << 6)  /* Pmn Event Input Data */

#define R_PORT_EIDR_EIDR7                         (1 << 7)  /* Pmn Event Input Data */

#define R_PORT_EIDR_EIDR8                         (1 << 8)  /* Pmn Event Input Data */

#define R_PORT_EIDR_EIDR9                         (1 << 9)  /* Pmn Event Input Data */

#define R_PORT_EIDR_EIDR10                        (1 << 10)  /* Pmn Event Input Data */

#define R_PORT_EIDR_EIDR11                        (1 << 11)  /* Pmn Event Input Data */

#define R_PORT_EIDR_EIDR12                        (1 << 12)  /* Pmn Event Input Data */

#define R_PORT_EIDR_EIDR13                        (1 << 13)  /* Pmn Event Input Data */

#define R_PORT_EIDR_EIDR14                        (1 << 14)  /* Pmn Event Input Data */

#define R_PORT_EIDR_EIDR15                        (1 << 15)  /* Pmn Event Input Data */

/* PCNTR3 Register bit definitions */
#define R_PORT_PCNTR3_POSR_SHIFT                  (0)  /* Pmn Output Set */
#define R_PORT_PCNTR3_POSR_MASK                   0xffff
#  define R_PORT_PCNTR3_POSR_0                            (0 << R_PORT_PCNTR3_POSR_SHIFT)  /* No affect to output */
#  define R_PORT_PCNTR3_POSR_1                            (1 << R_PORT_PCNTR3_POSR_SHIFT)  /* High output. */

#define R_PORT_PCNTR3_PORR_SHIFT                  (16)  /* Pmn Output Reset */
#define R_PORT_PCNTR3_PORR_MASK                   0xffff0000
#  define R_PORT_PCNTR3_PORR_0                            (0 << R_PORT_PCNTR3_PORR_SHIFT)  /* No affect to output */
#  define R_PORT_PCNTR3_PORR_1                            (1 << R_PORT_PCNTR3_PORR_SHIFT)  /* Low output. */

/* POSR Register bit definitions */
#define R_PORT_POSR_POSR_S                        (1 << 0)  /* Pmn Output Set */

#define R_PORT_POSR_POSR0                         (1 << 0)  /* Pmn Output Set */

#define R_PORT_POSR_POSR1                         (1 << 1)  /* Pmn Output Set */

#define R_PORT_POSR_POSR2                         (1 << 2)  /* Pmn Output Set */

#define R_PORT_POSR_POSR3                         (1 << 3)  /* Pmn Output Set */

#define R_PORT_POSR_POSR4                         (1 << 4)  /* Pmn Output Set */

#define R_PORT_POSR_POSR5                         (1 << 5)  /* Pmn Output Set */

#define R_PORT_POSR_POSR6                         (1 << 6)  /* Pmn Output Set */

#define R_PORT_POSR_POSR7                         (1 << 7)  /* Pmn Output Set */

#define R_PORT_POSR_POSR8                         (1 << 8)  /* Pmn Output Set */

#define R_PORT_POSR_POSR9                         (1 << 9)  /* Pmn Output Set */

#define R_PORT_POSR_POSR10                        (1 << 10)  /* Pmn Output Set */

#define R_PORT_POSR_POSR11                        (1 << 11)  /* Pmn Output Set */

#define R_PORT_POSR_POSR12                        (1 << 12)  /* Pmn Output Set */

#define R_PORT_POSR_POSR13                        (1 << 13)  /* Pmn Output Set */

#define R_PORT_POSR_POSR14                        (1 << 14)  /* Pmn Output Set */

#define R_PORT_POSR_POSR15                        (1 << 15)  /* Pmn Output Set */

/* PORR Register bit definitions */
#define R_PORT_PORR_PORR_S                        (1 << 0)  /* Pmn Output Reset */

#define R_PORT_PORR_PORR0                         (1 << 0)  /* Pmn Output Reset */

#define R_PORT_PORR_PORR1                         (1 << 1)  /* Pmn Output Reset */

#define R_PORT_PORR_PORR2                         (1 << 2)  /* Pmn Output Reset */

#define R_PORT_PORR_PORR3                         (1 << 3)  /* Pmn Output Reset */

#define R_PORT_PORR_PORR4                         (1 << 4)  /* Pmn Output Reset */

#define R_PORT_PORR_PORR5                         (1 << 5)  /* Pmn Output Reset */

#define R_PORT_PORR_PORR6                         (1 << 6)  /* Pmn Output Reset */

#define R_PORT_PORR_PORR7                         (1 << 7)  /* Pmn Output Reset */

#define R_PORT_PORR_PORR8                         (1 << 8)  /* Pmn Output Reset */

#define R_PORT_PORR_PORR9                         (1 << 9)  /* Pmn Output Reset */

#define R_PORT_PORR_PORR10                        (1 << 10)  /* Pmn Output Reset */

#define R_PORT_PORR_PORR11                        (1 << 11)  /* Pmn Output Reset */

#define R_PORT_PORR_PORR12                        (1 << 12)  /* Pmn Output Reset */

#define R_PORT_PORR_PORR13                        (1 << 13)  /* Pmn Output Reset */

#define R_PORT_PORR_PORR14                        (1 << 14)  /* Pmn Output Reset */

#define R_PORT_PORR_PORR15                        (1 << 15)  /* Pmn Output Reset */

/* PCNTR4 Register bit definitions */
#define R_PORT_PCNTR4_EOSR_SHIFT                  (0)  /* Pmn Event Output Set */
#define R_PORT_PCNTR4_EOSR_MASK                   0xffff
#  define R_PORT_PCNTR4_EOSR_0                            (0 << R_PORT_PCNTR4_EOSR_SHIFT)  /* No affect to output */
#  define R_PORT_PCNTR4_EOSR_1                            (1 << R_PORT_PCNTR4_EOSR_SHIFT)  /* High output. */

#define R_PORT_PCNTR4_EORR_SHIFT                  (16)  /* Pmn Event Output Reset */
#define R_PORT_PCNTR4_EORR_MASK                   0xffff0000
#  define R_PORT_PCNTR4_EORR_0                            (0 << R_PORT_PCNTR4_EORR_SHIFT)  /* No affect to output */
#  define R_PORT_PCNTR4_EORR_1                            (1 << R_PORT_PCNTR4_EORR_SHIFT)  /* Low output */

/* EOSR Register bit definitions */
#define R_PORT_EOSR_EOSR_S                        (1 << 0)  /* Pmn Event Output Set */

#define R_PORT_EOSR_EOSR0                         (1 << 0)  /* Pmn Event Output Set */

#define R_PORT_EOSR_EOSR1                         (1 << 1)  /* Pmn Event Output Set */

#define R_PORT_EOSR_EOSR2                         (1 << 2)  /* Pmn Event Output Set */

#define R_PORT_EOSR_EOSR3                         (1 << 3)  /* Pmn Event Output Set */

#define R_PORT_EOSR_EOSR4                         (1 << 4)  /* Pmn Event Output Set */

#define R_PORT_EOSR_EOSR5                         (1 << 5)  /* Pmn Event Output Set */

#define R_PORT_EOSR_EOSR6                         (1 << 6)  /* Pmn Event Output Set */

#define R_PORT_EOSR_EOSR7                         (1 << 7)  /* Pmn Event Output Set */

#define R_PORT_EOSR_EOSR8                         (1 << 8)  /* Pmn Event Output Set */

#define R_PORT_EOSR_EOSR9                         (1 << 9)  /* Pmn Event Output Set */

#define R_PORT_EOSR_EOSR10                        (1 << 10)  /* Pmn Event Output Set */

#define R_PORT_EOSR_EOSR11                        (1 << 11)  /* Pmn Event Output Set */

#define R_PORT_EOSR_EOSR12                        (1 << 12)  /* Pmn Event Output Set */

#define R_PORT_EOSR_EOSR13                        (1 << 13)  /* Pmn Event Output Set */

#define R_PORT_EOSR_EOSR14                        (1 << 14)  /* Pmn Event Output Set */

#define R_PORT_EOSR_EOSR15                        (1 << 15)  /* Pmn Event Output Set */

/* EORR Register bit definitions */
#define R_PORT_EORR_EORR_S                        (1 << 0)  /* Pmn Event Output Reset */

#define R_PORT_EORR_EORR0                         (1 << 0)  /* Pmn Event Output Reset */

#define R_PORT_EORR_EORR1                         (1 << 1)  /* Pmn Event Output Reset */

#define R_PORT_EORR_EORR2                         (1 << 2)  /* Pmn Event Output Reset */

#define R_PORT_EORR_EORR3                         (1 << 3)  /* Pmn Event Output Reset */

#define R_PORT_EORR_EORR4                         (1 << 4)  /* Pmn Event Output Reset */

#define R_PORT_EORR_EORR5                         (1 << 5)  /* Pmn Event Output Reset */

#define R_PORT_EORR_EORR6                         (1 << 6)  /* Pmn Event Output Reset */

#define R_PORT_EORR_EORR7                         (1 << 7)  /* Pmn Event Output Reset */

#define R_PORT_EORR_EORR8                         (1 << 8)  /* Pmn Event Output Reset */

#define R_PORT_EORR_EORR9                         (1 << 9)  /* Pmn Event Output Reset */

#define R_PORT_EORR_EORR10                        (1 << 10)  /* Pmn Event Output Reset */

#define R_PORT_EORR_EORR11                        (1 << 11)  /* Pmn Event Output Reset */

#define R_PORT_EORR_EORR12                        (1 << 12)  /* Pmn Event Output Reset */

#define R_PORT_EORR_EORR13                        (1 << 13)  /* Pmn Event Output Reset */

#define R_PORT_EORR_EORR14                        (1 << 14)  /* Pmn Event Output Reset */

#define R_PORT_EORR_EORR15                        (1 << 15)  /* Pmn Event Output Reset */


/* Maximum number of channels */

#define PORT_MAX_CHANNELS    15

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PORT_H */

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
#define R_PORT_PDR_OFFSET                         0x00000000  /* Port Control Register 1 */
#define R_PORT_PODR_OFFSET                        0x00000002  /* Port Control Register 1 */
#define R_PORT_PCNTR2_OFFSET                      0x00000004  /* Port Control Register 2 */
#define R_PORT_PIDR_OFFSET                        0x00000004  /* Port Control Register 2 */
#define R_PORT_PCNTR3_OFFSET                      0x00000008  /* Port Control Register 3 */
#define R_PORT_POSR_OFFSET                        0x00000008  /* Port Control Register 3 */
#define R_PORT_PORR_OFFSET                        0x0000000a  /* Port Control Register 3 */

/* PORT Register Addresses */

#define R_PORT_PCNTR1(port)                       (R_PORT_CH_BASE(port) + R_PORT_PCNTR1_OFFSET)
#define R_PORT_PDR(port)                          (R_PORT_CH_BASE(port) + R_PORT_PDR_OFFSET)
#define R_PORT_PODR(port)                         (R_PORT_CH_BASE(port) + R_PORT_PODR_OFFSET)
#define R_PORT_PCNTR2(port)                       (R_PORT_CH_BASE(port) + R_PORT_PCNTR2_OFFSET)
#define R_PORT_PIDR(port)                         (R_PORT_CH_BASE(port) + R_PORT_PIDR_OFFSET)
#define R_PORT_PCNTR3(port)                       (R_PORT_CH_BASE(port) + R_PORT_PCNTR3_OFFSET)
#define R_PORT_POSR(port)                         (R_PORT_CH_BASE(port) + R_PORT_POSR_OFFSET)
#define R_PORT_PORR(port)                         (R_PORT_CH_BASE(port) + R_PORT_PORR_OFFSET)

/* Register bit definitions */
/* PCNTR1 Register bit definitions */
#define R_PORT_PCNTR1_PDR00                       (1 << 0)  /* Pmn Direction */

#define R_PORT_PCNTR1_PDR01                       (1 << 1)  /* Pmn Direction */

#define R_PORT_PCNTR1_PDR02                       (1 << 2)  /* Pmn Direction */

#define R_PORT_PCNTR1_PDR03                       (1 << 3)  /* Pmn Direction */

#define R_PORT_PCNTR1_PDR04                       (1 << 4)  /* Pmn Direction */

#define R_PORT_PCNTR1_PDR05                       (1 << 5)  /* Pmn Direction */

#define R_PORT_PCNTR1_PDR06                       (1 << 6)  /* Pmn Direction */

#define R_PORT_PCNTR1_PDR07                       (1 << 7)  /* Pmn Direction */

#define R_PORT_PCNTR1_PDR08                       (1 << 8)  /* Pmn Direction */

#define R_PORT_PCNTR1_PDR09                       (1 << 9)  /* Pmn Direction */

#define R_PORT_PCNTR1_PDR10                       (1 << 10)  /* Pmn Direction */

#define R_PORT_PCNTR1_PDR11                       (1 << 11)  /* Pmn Direction */

#define R_PORT_PCNTR1_PDR12                       (1 << 12)  /* Pmn Direction */

#define R_PORT_PCNTR1_PDR13                       (1 << 13)  /* Pmn Direction */

#define R_PORT_PCNTR1_PDR14                       (1 << 14)  /* Pmn Direction */

#define R_PORT_PCNTR1_PDR15                       (1 << 15)  /* Pmn Direction */

#define R_PORT_PCNTR1_PODR00                      (1 << 16)  /* Pmn Output Data */

#define R_PORT_PCNTR1_PODR01                      (1 << 17)  /* Pmn Output Data */

#define R_PORT_PCNTR1_PODR02                      (1 << 18)  /* Pmn Output Data */

#define R_PORT_PCNTR1_PODR03                      (1 << 19)  /* Pmn Output Data */

#define R_PORT_PCNTR1_PODR04                      (1 << 20)  /* Pmn Output Data */

#define R_PORT_PCNTR1_PODR05                      (1 << 21)  /* Pmn Output Data */

#define R_PORT_PCNTR1_PODR06                      (1 << 22)  /* Pmn Output Data */

#define R_PORT_PCNTR1_PODR07                      (1 << 23)  /* Pmn Output Data */

#define R_PORT_PCNTR1_PODR08                      (1 << 24)  /* Pmn Output Data */

#define R_PORT_PCNTR1_PODR09                      (1 << 25)  /* Pmn Output Data */

#define R_PORT_PCNTR1_PODR10                      (1 << 26)  /* Pmn Output Data */

#define R_PORT_PCNTR1_PODR11                      (1 << 27)  /* Pmn Output Data */

#define R_PORT_PCNTR1_PODR12                      (1 << 28)  /* Pmn Output Data */

#define R_PORT_PCNTR1_PODR13                      (1 << 29)  /* Pmn Output Data */

#define R_PORT_PCNTR1_PODR14                      (1 << 30)  /* Pmn Output Data */

#define R_PORT_PCNTR1_PODR15                      (1 << 31)  /* Pmn Output Data */

#define R_PORT_PCNTR1_PDR_SHIFT                   (0)  /* Pmn Direction */
#define R_PORT_PCNTR1_PDR_MASK                    0xffff

#define R_PORT_PCNTR1_PODR_SHIFT                  (16)  /* Pmn Output Data */
#define R_PORT_PCNTR1_PODR_MASK                   0xffff0000

/* PDR Register bit definitions */
#define R_PORT_PDR_PODR00                         (1 << 0)  /* Pmn Output Data */

#define R_PORT_PDR_PODR01                         (1 << 1)  /* Pmn Output Data */

#define R_PORT_PDR_PODR02                         (1 << 2)  /* Pmn Output Data */

#define R_PORT_PDR_PODR03                         (1 << 3)  /* Pmn Output Data */

#define R_PORT_PDR_PODR04                         (1 << 4)  /* Pmn Output Data */

#define R_PORT_PDR_PODR05                         (1 << 5)  /* Pmn Output Data */

#define R_PORT_PDR_PODR06                         (1 << 6)  /* Pmn Output Data */

#define R_PORT_PDR_PODR07                         (1 << 7)  /* Pmn Output Data */

#define R_PORT_PDR_PODR08                         (1 << 8)  /* Pmn Output Data */

#define R_PORT_PDR_PODR09                         (1 << 9)  /* Pmn Output Data */

#define R_PORT_PDR_PODR10                         (1 << 10)  /* Pmn Output Data */

#define R_PORT_PDR_PODR11                         (1 << 11)  /* Pmn Output Data */

#define R_PORT_PDR_PODR12                         (1 << 12)  /* Pmn Output Data */

#define R_PORT_PDR_PODR13                         (1 << 13)  /* Pmn Output Data */

#define R_PORT_PDR_PODR14                         (1 << 14)  /* Pmn Output Data */

#define R_PORT_PDR_PODR15                         (1 << 15)  /* Pmn Output Data */

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
#define R_PORT_PODR_PDR00                         (1 << 0)  /* Pmn Direction */

#define R_PORT_PODR_PDR01                         (1 << 1)  /* Pmn Direction */

#define R_PORT_PODR_PDR02                         (1 << 2)  /* Pmn Direction */

#define R_PORT_PODR_PDR03                         (1 << 3)  /* Pmn Direction */

#define R_PORT_PODR_PDR04                         (1 << 4)  /* Pmn Direction */

#define R_PORT_PODR_PDR05                         (1 << 5)  /* Pmn Direction */

#define R_PORT_PODR_PDR06                         (1 << 6)  /* Pmn Direction */

#define R_PORT_PODR_PDR07                         (1 << 7)  /* Pmn Direction */

#define R_PORT_PODR_PDR08                         (1 << 8)  /* Pmn Direction */

#define R_PORT_PODR_PDR09                         (1 << 9)  /* Pmn Direction */

#define R_PORT_PODR_PDR10                         (1 << 10)  /* Pmn Direction */

#define R_PORT_PODR_PDR11                         (1 << 11)  /* Pmn Direction */

#define R_PORT_PODR_PDR12                         (1 << 12)  /* Pmn Direction */

#define R_PORT_PODR_PDR13                         (1 << 13)  /* Pmn Direction */

#define R_PORT_PODR_PDR14                         (1 << 14)  /* Pmn Direction */

#define R_PORT_PODR_PDR15                         (1 << 15)  /* Pmn Direction */

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
#define R_PORT_PCNTR2_PIDR00                      (1 << 0)  /* Pmn State */

#define R_PORT_PCNTR2_PIDR01                      (1 << 1)  /* Pmn State */

#define R_PORT_PCNTR2_PIDR02                      (1 << 2)  /* Pmn State */

#define R_PORT_PCNTR2_PIDR03                      (1 << 3)  /* Pmn State */

#define R_PORT_PCNTR2_PIDR04                      (1 << 4)  /* Pmn State */

#define R_PORT_PCNTR2_PIDR05                      (1 << 5)  /* Pmn State */

#define R_PORT_PCNTR2_PIDR06                      (1 << 6)  /* Pmn State */

#define R_PORT_PCNTR2_PIDR07                      (1 << 7)  /* Pmn State */

#define R_PORT_PCNTR2_PIDR08                      (1 << 8)  /* Pmn State */

#define R_PORT_PCNTR2_PIDR09                      (1 << 9)  /* Pmn State */

#define R_PORT_PCNTR2_PIDR10                      (1 << 10)  /* Pmn State */

#define R_PORT_PCNTR2_PIDR11                      (1 << 11)  /* Pmn State */

#define R_PORT_PCNTR2_PIDR12                      (1 << 12)  /* Pmn State */

#define R_PORT_PCNTR2_PIDR13                      (1 << 13)  /* Pmn State */

#define R_PORT_PCNTR2_PIDR14                      (1 << 14)  /* Pmn State */

#define R_PORT_PCNTR2_PIDR15                      (1 << 15)  /* Pmn State */

#define R_PORT_PCNTR2_PIDR_SHIFT                  (0)  /* Pmn Input Data */
#define R_PORT_PCNTR2_PIDR_MASK                   0xffff

#define R_PORT_PCNTR2_EIDR_SHIFT                  (16)  /* Pmn Event Input Data */
#define R_PORT_PCNTR2_EIDR_MASK                   0xffff0000

/* PIDR Register bit definitions */
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

/* PCNTR3 Register bit definitions */
#define R_PORT_PCNTR3_POSR00                      (1 << 0)  /* Pmn Output Set */

#define R_PORT_PCNTR3_POSR01                      (1 << 1)  /* Pmn Output Set */

#define R_PORT_PCNTR3_POSR02                      (1 << 2)  /* Pmn Output Set */

#define R_PORT_PCNTR3_POSR03                      (1 << 3)  /* Pmn Output Set */

#define R_PORT_PCNTR3_POSR04                      (1 << 4)  /* Pmn Output Set */

#define R_PORT_PCNTR3_POSR05                      (1 << 5)  /* Pmn Output Set */

#define R_PORT_PCNTR3_POSR06                      (1 << 6)  /* Pmn Output Set */

#define R_PORT_PCNTR3_POSR07                      (1 << 7)  /* Pmn Output Set */

#define R_PORT_PCNTR3_POSR08                      (1 << 8)  /* Pmn Output Set */

#define R_PORT_PCNTR3_POSR09                      (1 << 9)  /* Pmn Output Set */

#define R_PORT_PCNTR3_POSR10                      (1 << 10)  /* Pmn Output Set */

#define R_PORT_PCNTR3_POSR11                      (1 << 11)  /* Pmn Output Set */

#define R_PORT_PCNTR3_POSR12                      (1 << 12)  /* Pmn Output Set */

#define R_PORT_PCNTR3_POSR13                      (1 << 13)  /* Pmn Output Set */

#define R_PORT_PCNTR3_POSR14                      (1 << 14)  /* Pmn Output Set */

#define R_PORT_PCNTR3_POSR15                      (1 << 15)  /* Pmn Output Set */

#define R_PORT_PCNTR3_PORR00                      (1 << 16)  /* Pmn Output Reset */

#define R_PORT_PCNTR3_PORR01                      (1 << 17)  /* Pmn Output Reset */

#define R_PORT_PCNTR3_PORR02                      (1 << 18)  /* Pmn Output Reset */

#define R_PORT_PCNTR3_PORR03                      (1 << 19)  /* Pmn Output Reset */

#define R_PORT_PCNTR3_PORR04                      (1 << 20)  /* Pmn Output Reset */

#define R_PORT_PCNTR3_PORR05                      (1 << 21)  /* Pmn Output Reset */

#define R_PORT_PCNTR3_PORR06                      (1 << 22)  /* Pmn Output Reset */

#define R_PORT_PCNTR3_PORR07                      (1 << 23)  /* Pmn Output Reset */

#define R_PORT_PCNTR3_PORR08                      (1 << 24)  /* Pmn Output Reset */

#define R_PORT_PCNTR3_PORR09                      (1 << 25)  /* Pmn Output Reset */

#define R_PORT_PCNTR3_PORR10                      (1 << 26)  /* Pmn Output Reset */

#define R_PORT_PCNTR3_PORR11                      (1 << 27)  /* Pmn Output Reset */

#define R_PORT_PCNTR3_PORR12                      (1 << 28)  /* Pmn Output Reset */

#define R_PORT_PCNTR3_PORR13                      (1 << 29)  /* Pmn Output Reset */

#define R_PORT_PCNTR3_PORR14                      (1 << 30)  /* Pmn Output Reset */

#define R_PORT_PCNTR3_PORR15                      (1 << 31)  /* Pmn Output Reset */

#define R_PORT_PCNTR3_POSR_SHIFT                  (0)  /* Pmn Output Set */
#define R_PORT_PCNTR3_POSR_MASK                   0xffff

#define R_PORT_PCNTR3_PORR_SHIFT                  (16)  /* Pmn Output Reset */
#define R_PORT_PCNTR3_PORR_MASK                   0xffff0000

/* POSR Register bit definitions */
#define R_PORT_POSR_PORR00                        (1 << 0)  /* Pmn Output Reset */

#define R_PORT_POSR_PORR01                        (1 << 1)  /* Pmn Output Reset */

#define R_PORT_POSR_PORR02                        (1 << 2)  /* Pmn Output Reset */

#define R_PORT_POSR_PORR03                        (1 << 3)  /* Pmn Output Reset */

#define R_PORT_POSR_PORR04                        (1 << 4)  /* Pmn Output Reset */

#define R_PORT_POSR_PORR05                        (1 << 5)  /* Pmn Output Reset */

#define R_PORT_POSR_PORR06                        (1 << 6)  /* Pmn Output Reset */

#define R_PORT_POSR_PORR07                        (1 << 7)  /* Pmn Output Reset */

#define R_PORT_POSR_PORR08                        (1 << 8)  /* Pmn Output Reset */

#define R_PORT_POSR_PORR09                        (1 << 9)  /* Pmn Output Reset */

#define R_PORT_POSR_PORR10                        (1 << 10)  /* Pmn Output Reset */

#define R_PORT_POSR_PORR11                        (1 << 11)  /* Pmn Output Reset */

#define R_PORT_POSR_PORR12                        (1 << 12)  /* Pmn Output Reset */

#define R_PORT_POSR_PORR13                        (1 << 13)  /* Pmn Output Reset */

#define R_PORT_POSR_PORR14                        (1 << 14)  /* Pmn Output Reset */

#define R_PORT_POSR_PORR15                        (1 << 15)  /* Pmn Output Reset */

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
#define R_PORT_PORR_POSR00                        (1 << 0)  /* Pmn Output Set */

#define R_PORT_PORR_POSR01                        (1 << 1)  /* Pmn Output Set */

#define R_PORT_PORR_POSR02                        (1 << 2)  /* Pmn Output Set */

#define R_PORT_PORR_POSR03                        (1 << 3)  /* Pmn Output Set */

#define R_PORT_PORR_POSR04                        (1 << 4)  /* Pmn Output Set */

#define R_PORT_PORR_POSR05                        (1 << 5)  /* Pmn Output Set */

#define R_PORT_PORR_POSR06                        (1 << 6)  /* Pmn Output Set */

#define R_PORT_PORR_POSR07                        (1 << 7)  /* Pmn Output Set */

#define R_PORT_PORR_POSR08                        (1 << 8)  /* Pmn Output Set */

#define R_PORT_PORR_POSR09                        (1 << 9)  /* Pmn Output Set */

#define R_PORT_PORR_POSR10                        (1 << 10)  /* Pmn Output Set */

#define R_PORT_PORR_POSR11                        (1 << 11)  /* Pmn Output Set */

#define R_PORT_PORR_POSR12                        (1 << 12)  /* Pmn Output Set */

#define R_PORT_PORR_POSR13                        (1 << 13)  /* Pmn Output Set */

#define R_PORT_PORR_POSR14                        (1 << 14)  /* Pmn Output Set */

#define R_PORT_PORR_POSR15                        (1 << 15)  /* Pmn Output Set */

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


/* Maximum number of channels */

#define PORT_MAX_CHANNELS    12

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PORT_H */

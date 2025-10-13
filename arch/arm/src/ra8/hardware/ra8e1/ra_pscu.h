/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8e1/ra_pscu.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_PSCU_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_PSCU_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* PSCU Base Address */
#ifndef R_PSCU_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_PSCU_BASE           0x40204000
#else
#define R_PSCU_BASE           0x50204000
#endif
#endif

/* PSCU Register Offsets */

#define R_PSCU_PSARB_OFFSET                       0x00000004  /* Peripheral Security Attribution Register B */
#define R_PSCU_PSARC_OFFSET                       0x00000008  /* Peripheral Security Attribution Register C */
#define R_PSCU_PSARD_OFFSET                       0x0000000c  /* Peripheral Security Attribution Register D */
#define R_PSCU_PSARE_OFFSET                       0x00000010  /* Peripheral Security Attribution Register E */
#define R_PSCU_MSSAR_OFFSET                       0x00000014  /* Module Stop Security Attribution Register */
#define R_PSCU_PPARB_OFFSET                       0x0000001c  /* Peripheral Privilege Attribution Register B */
#define R_PSCU_PPARC_OFFSET                       0x00000020  /* Peripheral Privilege Attribution Register C */
#define R_PSCU_PPARD_OFFSET                       0x00000024  /* Peripheral Privilege Attribution Register D */
#define R_PSCU_PPARE_OFFSET                       0x00000028  /* Peripheral Privilege Attribution Register E */
#define R_PSCU_MSPAR_OFFSET                       0x0000002c  /* Module Stop Privilege Attribution Register */
#define R_PSCU_CFSAMONA_OFFSET                    0x00000030  /* Code Flash Security Attribution Monitor Register A */
#define R_PSCU_DFSAMON_OFFSET                     0x00000034  /* Data Flash Security Attribution Monitor Register */
#define R_PSCU_DLMMON_OFFSET                      0x00000038  /* Device Lifecycle Management State Monitor Register */

/* PSCU Register Addresses */

#define R_PSCU_PSARB                              (R_PSCU_BASE + R_PSCU_PSARB_OFFSET)
#define R_PSCU_PSARC                              (R_PSCU_BASE + R_PSCU_PSARC_OFFSET)
#define R_PSCU_PSARD                              (R_PSCU_BASE + R_PSCU_PSARD_OFFSET)
#define R_PSCU_PSARE                              (R_PSCU_BASE + R_PSCU_PSARE_OFFSET)
#define R_PSCU_MSSAR                              (R_PSCU_BASE + R_PSCU_MSSAR_OFFSET)
#define R_PSCU_PPARB                              (R_PSCU_BASE + R_PSCU_PPARB_OFFSET)
#define R_PSCU_PPARC                              (R_PSCU_BASE + R_PSCU_PPARC_OFFSET)
#define R_PSCU_PPARD                              (R_PSCU_BASE + R_PSCU_PPARD_OFFSET)
#define R_PSCU_PPARE                              (R_PSCU_BASE + R_PSCU_PPARE_OFFSET)
#define R_PSCU_MSPAR                              (R_PSCU_BASE + R_PSCU_MSPAR_OFFSET)
#define R_PSCU_CFSAMONA                           (R_PSCU_BASE + R_PSCU_CFSAMONA_OFFSET)
#define R_PSCU_DFSAMON                            (R_PSCU_BASE + R_PSCU_DFSAMON_OFFSET)
#define R_PSCU_DLMMON                             (R_PSCU_BASE + R_PSCU_DLMMON_OFFSET)

/* Register bit definitions */
/* PSARB Register bit definitions */
#define R_PSCU_PSARB_PSARB8                       (1 << 8)  /* I2C Bus Interface 1 Security Attribution */

#define R_PSCU_PSARB_PSARB9                       (1 << 9)  /* I2C Bus Interface 0 Security Attribution */

#define R_PSCU_PSARB_PSARB11                      (1 << 11)  /* Universal Serial Bus 2.0 FS Interface 0 Security Attribution */

#define R_PSCU_PSARB_PSARB15                      (1 << 15)  /* ETHERC/EDMAC Controller Security Attribution */

#define R_PSCU_PSARB_PSARB16                      (1 << 16)  /* Octa Memory Controller Security Attribution */

#define R_PSCU_PSARB_PSARB18                      (1 << 18)  /* Serial Peripheral Interface 1 Security Attribution */

#define R_PSCU_PSARB_PSARB19                      (1 << 19)  /* Serial Peripheral Interface 0 Security Attribution */

#define R_PSCU_PSARB_PSARB22                      (1 << 22)  /* Serial Communication Interface 9 Security Attribution */

#define R_PSCU_PSARB_PSARB27                      (1 << 27)  /* Serial Communication Interface 4 Security Attribution */

#define R_PSCU_PSARB_PSARB28                      (1 << 28)  /* Serial Communication Interface 3 Security Attribution */

#define R_PSCU_PSARB_PSARB29                      (1 << 29)  /* Serial Communication Interface 2 Security Attribution */

#define R_PSCU_PSARB_PSARB30                      (1 << 30)  /* Serial Communication Interface 1 Security Attribution */

#define R_PSCU_PSARB_PSARB31                      (1 << 31)  /* Serial Communication Interface 0 Security Attribution */

#define R_PSCU_PSARB_PSARB0                       (1 << 0)  /* Peripheral security attribution bit 0 */

#define R_PSCU_PSARB_PSARB1                       (1 << 1)  /* Peripheral security attribution bit 1 */

#define R_PSCU_PSARB_PSARB2                       (1 << 2)  /* Peripheral security attribution bit 2 */

#define R_PSCU_PSARB_PSARB3                       (1 << 3)  /* Peripheral security attribution bit 3 */

#define R_PSCU_PSARB_PSARB4                       (1 << 4)  /* Peripheral security attribution bit 4 */

#define R_PSCU_PSARB_PSARB5                       (1 << 5)  /* Peripheral security attribution bit 5 */

#define R_PSCU_PSARB_PSARB6                       (1 << 6)  /* Peripheral security attribution bit 6 */

#define R_PSCU_PSARB_PSARB7                       (1 << 7)  /* Peripheral security attribution bit 7 */

#define R_PSCU_PSARB_PSARB10                      (1 << 10)  /* Peripheral security attribution bit 10 */

#define R_PSCU_PSARB_PSARB12                      (1 << 12)  /* Peripheral security attribution bit 12 */

#define R_PSCU_PSARB_PSARB13                      (1 << 13)  /* Peripheral security attribution bit 13 */

#define R_PSCU_PSARB_PSARB14                      (1 << 14)  /* Peripheral security attribution bit 14 */

#define R_PSCU_PSARB_PSARB17                      (1 << 17)  /* Peripheral security attribution bit 17 */

#define R_PSCU_PSARB_PSARB20                      (1 << 20)  /* Peripheral security attribution bit 20 */

#define R_PSCU_PSARB_PSARB21                      (1 << 21)  /* Peripheral security attribution bit 21 */

#define R_PSCU_PSARB_PSARB23                      (1 << 23)  /* Peripheral security attribution bit 23 */

#define R_PSCU_PSARB_PSARB24                      (1 << 24)  /* Peripheral security attribution bit 24 */

#define R_PSCU_PSARB_PSARB25                      (1 << 25)  /* Peripheral security attribution bit 25 */

#define R_PSCU_PSARB_PSARB26                      (1 << 26)  /* Peripheral security attribution bit 26 */

/* PSARC Register bit definitions */
#define R_PSCU_PSARC_PSARC0                       (1 << 0)  /* Clock Frequency Accuracy Measurement Circuit Security Attribution register specifies the security attribution for each module and the corresponding bit in Module Stop Control Register. */

#define R_PSCU_PSARC_PSARC1                       (1 << 1)  /* Cyclic Redundancy Check Calculator Security Attribution */

#define R_PSCU_PSARC_PSARC7                       (1 << 7)  /* Serial Sound Interface Enhanced (channel 1) Security Attribution */

#define R_PSCU_PSARC_PSARC8                       (1 << 8)  /* Serial Sound Interface Enhanced (channel 0) Security Attribution */

#define R_PSCU_PSARC_PSARC13                      (1 << 13)  /* Data Operation Circuit Security Attribution */

#define R_PSCU_PSARC_PSARC16                      (1 << 16)  /* CEU Security Attribution */

#define R_PSCU_PSARC_PSARC26                      (1 << 26)  /* Controller Area Network with Flexible Data-Rate 1 Security Attribution */

#define R_PSCU_PSARC_PSARC27                      (1 << 27)  /* Controller Area Network with Flexible Data-Rate 0 Security Attribution */

#define R_PSCU_PSARC_PSARC31                      (1 << 31)  /* RSIP-E51A Security Attribution */

#define R_PSCU_PSARC_PSARC2                       (1 << 2)  /* Peripheral security attribution bit 2 */

#define R_PSCU_PSARC_PSARC3                       (1 << 3)  /* Peripheral security attribution bit 3 */

#define R_PSCU_PSARC_PSARC4                       (1 << 4)  /* Peripheral security attribution bit 4 */

#define R_PSCU_PSARC_PSARC5                       (1 << 5)  /* Peripheral security attribution bit 5 */

#define R_PSCU_PSARC_PSARC6                       (1 << 6)  /* Peripheral security attribution bit 6 */

#define R_PSCU_PSARC_PSARC9                       (1 << 9)  /* Peripheral security attribution bit 9 */

#define R_PSCU_PSARC_PSARC10                      (1 << 10)  /* Peripheral security attribution bit 10 */

#define R_PSCU_PSARC_PSARC11                      (1 << 11)  /* Peripheral security attribution bit 11 */

#define R_PSCU_PSARC_PSARC12                      (1 << 12)  /* Peripheral security attribution bit 12 */

#define R_PSCU_PSARC_PSARC14                      (1 << 14)  /* Peripheral security attribution bit 14 */

#define R_PSCU_PSARC_PSARC15                      (1 << 15)  /* Peripheral security attribution bit 15 */

#define R_PSCU_PSARC_PSARC17                      (1 << 17)  /* Peripheral security attribution bit 17 */

#define R_PSCU_PSARC_PSARC18                      (1 << 18)  /* Peripheral security attribution bit 18 */

#define R_PSCU_PSARC_PSARC19                      (1 << 19)  /* Peripheral security attribution bit 19 */

#define R_PSCU_PSARC_PSARC20                      (1 << 20)  /* Peripheral security attribution bit 20 */

#define R_PSCU_PSARC_PSARC21                      (1 << 21)  /* Peripheral security attribution bit 21 */

#define R_PSCU_PSARC_PSARC22                      (1 << 22)  /* Peripheral security attribution bit 22 */

#define R_PSCU_PSARC_PSARC23                      (1 << 23)  /* Peripheral security attribution bit 23 */

#define R_PSCU_PSARC_PSARC24                      (1 << 24)  /* Peripheral security attribution bit 24 */

#define R_PSCU_PSARC_PSARC25                      (1 << 25)  /* Peripheral security attribution bit 25 */

#define R_PSCU_PSARC_PSARC28                      (1 << 28)  /* Peripheral security attribution bit 28 */

#define R_PSCU_PSARC_PSARC29                      (1 << 29)  /* Peripheral security attribution bit 29 */

#define R_PSCU_PSARC_PSARC30                      (1 << 30)  /* Peripheral security attribution bit 30 */

/* PSARD Register bit definitions */
#define R_PSCU_PSARD_PSARD4                       (1 << 4)  /* Asynchronous General Purpose Timer 1 Security Attribution */

#define R_PSCU_PSARD_PSARD5                       (1 << 5)  /* Asynchronous General Purpose Timer 0 Security Attribution */

#define R_PSCU_PSARD_PSARD11                      (1 << 11)  /* Port Output Enable for GPT Group 3 Security Attribution */

#define R_PSCU_PSARD_PSARD12                      (1 << 12)  /* Port Output Enable for GPT Group 2 Security Attribution */

#define R_PSCU_PSARD_PSARD13                      (1 << 13)  /* Port Output Enable for GPT Group 1 Security Attribution */

#define R_PSCU_PSARD_PSARD14                      (1 << 14)  /* Port Output Enable for GPT Group 0 Security Attribution */

#define R_PSCU_PSARD_PSARD15                      (1 << 15)  /* 12-Bit A/D 1 Converter Security Attribution */

#define R_PSCU_PSARD_PSARD16                      (1 << 16)  /* 12-Bit A/D 0 Converter Security Attribution */

#define R_PSCU_PSARD_PSARD20                      (1 << 20)  /* 12-Bit D/A Converter Security Attribution */

#define R_PSCU_PSARD_PSARD22                      (1 << 22)  /* Temperature Sensor Security Attribution */

#define R_PSCU_PSARD_PSARD27                      (1 << 27)  /* High Speed Analog Comparator 1 Security Attribution */

#define R_PSCU_PSARD_PSARD28                      (1 << 28)  /* High Speed Analog Comparator 0 Security Attribution */

#define R_PSCU_PSARD_PSARD0                       (1 << 0)  /* Peripheral security attribution bit 0 */

#define R_PSCU_PSARD_PSARD1                       (1 << 1)  /* Peripheral security attribution bit 1 */

#define R_PSCU_PSARD_PSARD2                       (1 << 2)  /* Peripheral security attribution bit 2 */

#define R_PSCU_PSARD_PSARD3                       (1 << 3)  /* Peripheral security attribution bit 3 */

#define R_PSCU_PSARD_PSARD6                       (1 << 6)  /* Peripheral security attribution bit 6 */

#define R_PSCU_PSARD_PSARD7                       (1 << 7)  /* Peripheral security attribution bit 7 */

#define R_PSCU_PSARD_PSARD8                       (1 << 8)  /* Peripheral security attribution bit 8 */

#define R_PSCU_PSARD_PSARD9                       (1 << 9)  /* Peripheral security attribution bit 9 */

#define R_PSCU_PSARD_PSARD10                      (1 << 10)  /* Peripheral security attribution bit 10 */

#define R_PSCU_PSARD_PSARD17                      (1 << 17)  /* Peripheral security attribution bit 17 */

#define R_PSCU_PSARD_PSARD18                      (1 << 18)  /* Peripheral security attribution bit 18 */

#define R_PSCU_PSARD_PSARD19                      (1 << 19)  /* Peripheral security attribution bit 19 */

#define R_PSCU_PSARD_PSARD21                      (1 << 21)  /* Peripheral security attribution bit 21 */

#define R_PSCU_PSARD_PSARD23                      (1 << 23)  /* Peripheral security attribution bit 23 */

#define R_PSCU_PSARD_PSARD24                      (1 << 24)  /* Peripheral security attribution bit 24 */

#define R_PSCU_PSARD_PSARD25                      (1 << 25)  /* Peripheral security attribution bit 25 */

#define R_PSCU_PSARD_PSARD26                      (1 << 26)  /* Peripheral security attribution bit 26 */

#define R_PSCU_PSARD_PSARD29                      (1 << 29)  /* Peripheral security attribution bit 29 */

#define R_PSCU_PSARD_PSARD30                      (1 << 30)  /* Peripheral security attribution bit 30 */

#define R_PSCU_PSARD_PSARD31                      (1 << 31)  /* Peripheral security attribution bit 31 */

/* PSARE Register bit definitions */
#define R_PSCU_PSARE_PSARE1                       (1 << 1)  /* WDT Security Attribution */

#define R_PSCU_PSARE_PSARE2                       (1 << 2)  /* IWDT Security Attribution */

#define R_PSCU_PSARE_PSARE3                       (1 << 3)  /* Real Time Clock Security Attribution */

#define R_PSCU_PSARE_PSARE8                       (1 << 8)  /* ULPT1 Security Attribution */

#define R_PSCU_PSARE_PSARE9                       (1 << 9)  /* ULPT0 Security Attribution */

#define R_PSCU_PSARE_PSARE18                      (1 << 18)  /* General PWM Timer Channel 13 Security Attribution */

#define R_PSCU_PSARE_PSARE19                      (1 << 19)  /* General PWM Timer Channel 12 Security Attribution */

#define R_PSCU_PSARE_PSARE20                      (1 << 20)  /* General PWM Timer Channel 11 Security Attribution */

#define R_PSCU_PSARE_PSARE21                      (1 << 21)  /* General PWM Timer Channel 10 Security Attribution */

#define R_PSCU_PSARE_PSARE26                      (1 << 26)  /* General PWM Timer Channel 5 Security Attribution */

#define R_PSCU_PSARE_PSARE27                      (1 << 27)  /* General PWM Timer Channel 4 Security Attribution */

#define R_PSCU_PSARE_PSARE28                      (1 << 28)  /* General PWM Timer Channel 3 Security Attribution */

#define R_PSCU_PSARE_PSARE29                      (1 << 29)  /* General PWM Timer Channel 2 Security Attribution */

#define R_PSCU_PSARE_PSARE30                      (1 << 30)  /* General PWM Timer Channel 1 Security Attribution */

#define R_PSCU_PSARE_PSARE31                      (1 << 31)  /* General PWM Timer Channel 0 Security Attribution */

#define R_PSCU_PSARE_PSARE0                       (1 << 0)  /* Peripheral security attribution bit 0 */

#define R_PSCU_PSARE_PSARE4                       (1 << 4)  /* Peripheral security attribution bit 4 */

#define R_PSCU_PSARE_PSARE5                       (1 << 5)  /* Peripheral security attribution bit 5 */

#define R_PSCU_PSARE_PSARE6                       (1 << 6)  /* Peripheral security attribution bit 6 */

#define R_PSCU_PSARE_PSARE7                       (1 << 7)  /* Peripheral security attribution bit 7 */

#define R_PSCU_PSARE_PSARE10                      (1 << 10)  /* Peripheral security attribution bit 10 */

#define R_PSCU_PSARE_PSARE11                      (1 << 11)  /* Peripheral security attribution bit 11 */

#define R_PSCU_PSARE_PSARE12                      (1 << 12)  /* Peripheral security attribution bit 12 */

#define R_PSCU_PSARE_PSARE13                      (1 << 13)  /* Peripheral security attribution bit 13 */

#define R_PSCU_PSARE_PSARE14                      (1 << 14)  /* Peripheral security attribution bit 14 */

#define R_PSCU_PSARE_PSARE15                      (1 << 15)  /* Peripheral security attribution bit 15 */

#define R_PSCU_PSARE_PSARE16                      (1 << 16)  /* Peripheral security attribution bit 16 */

#define R_PSCU_PSARE_PSARE17                      (1 << 17)  /* Peripheral security attribution bit 17 */

#define R_PSCU_PSARE_PSARE22                      (1 << 22)  /* Peripheral security attribution bit 22 */

#define R_PSCU_PSARE_PSARE23                      (1 << 23)  /* Peripheral security attribution bit 23 */

#define R_PSCU_PSARE_PSARE24                      (1 << 24)  /* Peripheral security attribution bit 24 */

#define R_PSCU_PSARE_PSARE25                      (1 << 25)  /* Peripheral security attribution bit 25 */

/* MSSAR Register bit definitions */
#define R_PSCU_MSSAR_MSSAR0                       (1 << 0)  /* Unnecessary Circuit Clock Stop Security Attribution */

#define R_PSCU_MSSAR_MSSAR1                       (1 << 1)  /* SRAM1 Clock Stop Security Attribution */

#define R_PSCU_MSSAR_MSSAR15                      (1 << 15)  /* Standby RAM Clock Stop Security Attribution */

#define R_PSCU_MSSAR_MSSAR22                      (1 << 22)  /* DMAC/DTC Clock Stop Security Attribution */

#define R_PSCU_MSSAR_MSSAR31                      (1 << 31)  /* ELC Clock Stop Security Attribution */

#define R_PSCU_MSSAR_MSSAR2                       (1 << 2)  /* Module stop security attribution bit 2 */

#define R_PSCU_MSSAR_MSSAR3                       (1 << 3)  /* Module stop security attribution bit 3 */

#define R_PSCU_MSSAR_MSSAR4                       (1 << 4)  /* Module stop security attribution bit 4 */

#define R_PSCU_MSSAR_MSSAR5                       (1 << 5)  /* Module stop security attribution bit 5 */

#define R_PSCU_MSSAR_MSSAR6                       (1 << 6)  /* Module stop security attribution bit 6 */

#define R_PSCU_MSSAR_MSSAR7                       (1 << 7)  /* Module stop security attribution bit 7 */

#define R_PSCU_MSSAR_MSSAR8                       (1 << 8)  /* Module stop security attribution bit 8 */

#define R_PSCU_MSSAR_MSSAR9                       (1 << 9)  /* Module stop security attribution bit 9 */

#define R_PSCU_MSSAR_MSSAR10                      (1 << 10)  /* Module stop security attribution bit 10 */

#define R_PSCU_MSSAR_MSSAR11                      (1 << 11)  /* Module stop security attribution bit 11 */

#define R_PSCU_MSSAR_MSSAR12                      (1 << 12)  /* Module stop security attribution bit 12 */

#define R_PSCU_MSSAR_MSSAR13                      (1 << 13)  /* Module stop security attribution bit 13 */

#define R_PSCU_MSSAR_MSSAR14                      (1 << 14)  /* Module stop security attribution bit 14 */

#define R_PSCU_MSSAR_MSSAR16                      (1 << 16)  /* Module stop security attribution bit 16 */

#define R_PSCU_MSSAR_MSSAR17                      (1 << 17)  /* Module stop security attribution bit 17 */

#define R_PSCU_MSSAR_MSSAR18                      (1 << 18)  /* Module stop security attribution bit 18 */

#define R_PSCU_MSSAR_MSSAR19                      (1 << 19)  /* Module stop security attribution bit 19 */

#define R_PSCU_MSSAR_MSSAR20                      (1 << 20)  /* Module stop security attribution bit 20 */

#define R_PSCU_MSSAR_MSSAR21                      (1 << 21)  /* Module stop security attribution bit 21 */

#define R_PSCU_MSSAR_MSSAR23                      (1 << 23)  /* Module stop security attribution bit 23 */

#define R_PSCU_MSSAR_MSSAR24                      (1 << 24)  /* Module stop security attribution bit 24 */

#define R_PSCU_MSSAR_MSSAR25                      (1 << 25)  /* Module stop security attribution bit 25 */

#define R_PSCU_MSSAR_MSSAR26                      (1 << 26)  /* Module stop security attribution bit 26 */

#define R_PSCU_MSSAR_MSSAR27                      (1 << 27)  /* Module stop security attribution bit 27 */

#define R_PSCU_MSSAR_MSSAR28                      (1 << 28)  /* Module stop security attribution bit 28 */

#define R_PSCU_MSSAR_MSSAR29                      (1 << 29)  /* Module stop security attribution bit 29 */

#define R_PSCU_MSSAR_MSSAR30                      (1 << 30)  /* Module stop security attribution bit 30 */

/* PPARB Register bit definitions */
#define R_PSCU_PPARB_PPARB8                       (1 << 8)  /* I2C Bus Interface 1 Privilege Attribution */

#define R_PSCU_PPARB_PPARB9                       (1 << 9)  /* I2C Bus Interface 0 Privilege Attribution */

#define R_PSCU_PPARB_PPARB11                      (1 << 11)  /* Universal Serial Bus 2.0 FS Interface 0 Privilege Attribution */

#define R_PSCU_PPARB_PPARB15                      (1 << 15)  /* ETHERC/EDMAC Controller Privilege Attribution */

#define R_PSCU_PPARB_PPARB16                      (1 << 16)  /* Octa Memory Controller Privilege Attribution */

#define R_PSCU_PPARB_PPARB18                      (1 << 18)  /* Serial Peripheral Interface 1 Privilege Attribution */

#define R_PSCU_PPARB_PPARB19                      (1 << 19)  /* Serial Peripheral Interface 0 Privilege Attribution */

#define R_PSCU_PPARB_PPARB22                      (1 << 22)  /* Serial Communication Interface 9 Privilege Attribution */

#define R_PSCU_PPARB_PPARB27                      (1 << 27)  /* Serial Communication Interface 4 Privilege Attribution */

#define R_PSCU_PPARB_PPARB28                      (1 << 28)  /* Serial Communication Interface 3 Privilege Attribution */

#define R_PSCU_PPARB_PPARB29                      (1 << 29)  /* Serial Communication Interface 2 Privilege Attribution */

#define R_PSCU_PPARB_PPARB30                      (1 << 30)  /* Serial Communication Interface 1 Privilege Attribution */

#define R_PSCU_PPARB_PPARB31                      (1 << 31)  /* Serial Communication Interface 0 Privilege Attribution */

#define R_PSCU_PPARB_PPARB0                       (1 << 0)  /* Peripheral privilege attribution bit 0 */

#define R_PSCU_PPARB_PPARB1                       (1 << 1)  /* Peripheral privilege attribution bit 1 */

#define R_PSCU_PPARB_PPARB2                       (1 << 2)  /* Peripheral privilege attribution bit 2 */

#define R_PSCU_PPARB_PPARB3                       (1 << 3)  /* Peripheral privilege attribution bit 3 */

#define R_PSCU_PPARB_PPARB4                       (1 << 4)  /* Peripheral privilege attribution bit 4 */

#define R_PSCU_PPARB_PPARB5                       (1 << 5)  /* Peripheral privilege attribution bit 5 */

#define R_PSCU_PPARB_PPARB6                       (1 << 6)  /* Peripheral privilege attribution bit 6 */

#define R_PSCU_PPARB_PPARB7                       (1 << 7)  /* Peripheral privilege attribution bit 7 */

#define R_PSCU_PPARB_PPARB10                      (1 << 10)  /* Peripheral privilege attribution bit 10 */

#define R_PSCU_PPARB_PPARB12                      (1 << 12)  /* Peripheral privilege attribution bit 12 */

#define R_PSCU_PPARB_PPARB13                      (1 << 13)  /* Peripheral privilege attribution bit 13 */

#define R_PSCU_PPARB_PPARB14                      (1 << 14)  /* Peripheral privilege attribution bit 14 */

#define R_PSCU_PPARB_PPARB17                      (1 << 17)  /* Peripheral privilege attribution bit 17 */

#define R_PSCU_PPARB_PPARB20                      (1 << 20)  /* Peripheral privilege attribution bit 20 */

#define R_PSCU_PPARB_PPARB21                      (1 << 21)  /* Peripheral privilege attribution bit 21 */

#define R_PSCU_PPARB_PPARB23                      (1 << 23)  /* Peripheral privilege attribution bit 23 */

#define R_PSCU_PPARB_PPARB24                      (1 << 24)  /* Peripheral privilege attribution bit 24 */

#define R_PSCU_PPARB_PPARB25                      (1 << 25)  /* Peripheral privilege attribution bit 25 */

#define R_PSCU_PPARB_PPARB26                      (1 << 26)  /* Peripheral privilege attribution bit 26 */

/* PPARC Register bit definitions */
#define R_PSCU_PPARC_PPARC0                       (1 << 0)  /* Clock Frequency Accuracy Measurement Circuit Privilege Attribution */

#define R_PSCU_PPARC_PPARC1                       (1 << 1)  /* Cyclic Redundancy Check Calculator Privilege Attribution */

#define R_PSCU_PPARC_PPARC7                       (1 << 7)  /* Serial Sound Interface Enhanced (Channel 1) Privilege Attribution */

#define R_PSCU_PPARC_PPARC8                       (1 << 8)  /* Serial Sound Interface Enhanced (Channel 0) Privilege Attribution */

#define R_PSCU_PPARC_PPARC13                      (1 << 13)  /* Data Operation Circuit Privilege Attribution */

#define R_PSCU_PPARC_PPARC16                      (1 << 16)  /* CEU Privilege Attribution */

#define R_PSCU_PPARC_PPARC26                      (1 << 26)  /* Controller Area Network with Flexible Data-Rate 1 Privilege Attribution */

#define R_PSCU_PPARC_PPARC27                      (1 << 27)  /* Controller Area Network with Flexible Data-Rate 0 Privilege Attribution */

#define R_PSCU_PPARC_PPARC31                      (1 << 31)  /* RSIP-E51A Privilege Attribution */

#define R_PSCU_PPARC_PPARC2                       (1 << 2)  /* Peripheral privilege attribution bit 2 */

#define R_PSCU_PPARC_PPARC3                       (1 << 3)  /* Peripheral privilege attribution bit 3 */

#define R_PSCU_PPARC_PPARC4                       (1 << 4)  /* Peripheral privilege attribution bit 4 */

#define R_PSCU_PPARC_PPARC5                       (1 << 5)  /* Peripheral privilege attribution bit 5 */

#define R_PSCU_PPARC_PPARC6                       (1 << 6)  /* Peripheral privilege attribution bit 6 */

#define R_PSCU_PPARC_PPARC9                       (1 << 9)  /* Peripheral privilege attribution bit 9 */

#define R_PSCU_PPARC_PPARC10                      (1 << 10)  /* Peripheral privilege attribution bit 10 */

#define R_PSCU_PPARC_PPARC11                      (1 << 11)  /* Peripheral privilege attribution bit 11 */

#define R_PSCU_PPARC_PPARC12                      (1 << 12)  /* Peripheral privilege attribution bit 12 */

#define R_PSCU_PPARC_PPARC14                      (1 << 14)  /* Peripheral privilege attribution bit 14 */

#define R_PSCU_PPARC_PPARC15                      (1 << 15)  /* Peripheral privilege attribution bit 15 */

#define R_PSCU_PPARC_PPARC17                      (1 << 17)  /* Peripheral privilege attribution bit 17 */

#define R_PSCU_PPARC_PPARC18                      (1 << 18)  /* Peripheral privilege attribution bit 18 */

#define R_PSCU_PPARC_PPARC19                      (1 << 19)  /* Peripheral privilege attribution bit 19 */

#define R_PSCU_PPARC_PPARC20                      (1 << 20)  /* Peripheral privilege attribution bit 20 */

#define R_PSCU_PPARC_PPARC21                      (1 << 21)  /* Peripheral privilege attribution bit 21 */

#define R_PSCU_PPARC_PPARC22                      (1 << 22)  /* Peripheral privilege attribution bit 22 */

#define R_PSCU_PPARC_PPARC23                      (1 << 23)  /* Peripheral privilege attribution bit 23 */

#define R_PSCU_PPARC_PPARC24                      (1 << 24)  /* Peripheral privilege attribution bit 24 */

#define R_PSCU_PPARC_PPARC25                      (1 << 25)  /* Peripheral privilege attribution bit 25 */

#define R_PSCU_PPARC_PPARC28                      (1 << 28)  /* Peripheral privilege attribution bit 28 */

#define R_PSCU_PPARC_PPARC29                      (1 << 29)  /* Peripheral privilege attribution bit 29 */

#define R_PSCU_PPARC_PPARC30                      (1 << 30)  /* Peripheral privilege attribution bit 30 */

/* PPARD Register bit definitions */
#define R_PSCU_PPARD_PPARD4                       (1 << 4)  /* Asynchronous General Purpose Timer 1 Privilege Attribution */

#define R_PSCU_PPARD_PPARD5                       (1 << 5)  /* Asynchronous General Purpose Timer 0 Privilege Attribution */

#define R_PSCU_PPARD_PPARD11                      (1 << 11)  /* Port Output Enable for GPT Group 3 Privilege Attribution */

#define R_PSCU_PPARD_PPARD12                      (1 << 12)  /* Port Output Enable for GPT Group 2 Privilege Attribution */

#define R_PSCU_PPARD_PPARD13                      (1 << 13)  /* Port Output Enable for GPT Group 1 Privilege Attribution */

#define R_PSCU_PPARD_PPARD14                      (1 << 14)  /* Port Output Enable for GPT Group 0 Privilege Attribution */

#define R_PSCU_PPARD_PPARD15                      (1 << 15)  /* 12-Bit A/D 1 Converter Privilege Attribution */

#define R_PSCU_PPARD_PPARD16                      (1 << 16)  /* 12-Bit A/D 0 Converter Privilege Attribution */

#define R_PSCU_PPARD_PPARD20                      (1 << 20)  /* 12-Bit D/A Converter Privilege Attribution */

#define R_PSCU_PPARD_PPARD22                      (1 << 22)  /* Temperature Sensor Privilege Attribution */

#define R_PSCU_PPARD_PPARD27                      (1 << 27)  /* High speed analog Comparator 1 Privilege Attribution */

#define R_PSCU_PPARD_PPARD28                      (1 << 28)  /* High speed analog Comparator 0 Privilege Attribution */

#define R_PSCU_PPARD_PPARD0                       (1 << 0)  /* Peripheral privilege attribution bit 0 */

#define R_PSCU_PPARD_PPARD1                       (1 << 1)  /* Peripheral privilege attribution bit 1 */

#define R_PSCU_PPARD_PPARD2                       (1 << 2)  /* Peripheral privilege attribution bit 2 */

#define R_PSCU_PPARD_PPARD3                       (1 << 3)  /* Peripheral privilege attribution bit 3 */

#define R_PSCU_PPARD_PPARD6                       (1 << 6)  /* Peripheral privilege attribution bit 6 */

#define R_PSCU_PPARD_PPARD7                       (1 << 7)  /* Peripheral privilege attribution bit 7 */

#define R_PSCU_PPARD_PPARD8                       (1 << 8)  /* Peripheral privilege attribution bit 8 */

#define R_PSCU_PPARD_PPARD9                       (1 << 9)  /* Peripheral privilege attribution bit 9 */

#define R_PSCU_PPARD_PPARD10                      (1 << 10)  /* Peripheral privilege attribution bit 10 */

#define R_PSCU_PPARD_PPARD17                      (1 << 17)  /* Peripheral privilege attribution bit 17 */

#define R_PSCU_PPARD_PPARD18                      (1 << 18)  /* Peripheral privilege attribution bit 18 */

#define R_PSCU_PPARD_PPARD19                      (1 << 19)  /* Peripheral privilege attribution bit 19 */

#define R_PSCU_PPARD_PPARD21                      (1 << 21)  /* Peripheral privilege attribution bit 21 */

#define R_PSCU_PPARD_PPARD23                      (1 << 23)  /* Peripheral privilege attribution bit 23 */

#define R_PSCU_PPARD_PPARD24                      (1 << 24)  /* Peripheral privilege attribution bit 24 */

#define R_PSCU_PPARD_PPARD25                      (1 << 25)  /* Peripheral privilege attribution bit 25 */

#define R_PSCU_PPARD_PPARD26                      (1 << 26)  /* Peripheral privilege attribution bit 26 */

#define R_PSCU_PPARD_PPARD29                      (1 << 29)  /* Peripheral privilege attribution bit 29 */

#define R_PSCU_PPARD_PPARD30                      (1 << 30)  /* Peripheral privilege attribution bit 30 */

#define R_PSCU_PPARD_PPARD31                      (1 << 31)  /* Peripheral privilege attribution bit 31 */

/* PPARE Register bit definitions */
#define R_PSCU_PPARE_PPARE1                       (1 << 1)  /* WDT Privilege Attribution */

#define R_PSCU_PPARE_PPARE2                       (1 << 2)  /* IWDT Privilege Attribution */

#define R_PSCU_PPARE_PPARE3                       (1 << 3)  /* Real Time Clock Privilege Attribution */

#define R_PSCU_PPARE_PPARE8                       (1 << 8)  /* ULPT1 Privilege Attribution */

#define R_PSCU_PPARE_PPARE9                       (1 << 9)  /* ULPT0 Privilege Attribution */

#define R_PSCU_PPARE_PPARE18                      (1 << 18)  /* General PWM Timer Channel 13 Privilege Attribution */

#define R_PSCU_PPARE_PPARE19                      (1 << 19)  /* General PWM Timer Channel 12 Privilege Attribution */

#define R_PSCU_PPARE_PPARE20                      (1 << 20)  /* General PWM Timer Channel 11 Privilege Attribution */

#define R_PSCU_PPARE_PPARE21                      (1 << 21)  /* General PWM Timer Channel 10 Privilege Attribution */

#define R_PSCU_PPARE_PPARE26                      (1 << 26)  /* General PWM Timer Channel 5 Privilege Attribution */

#define R_PSCU_PPARE_PPARE27                      (1 << 27)  /* General PWM Timer Channel 4 Privilege Attribution */

#define R_PSCU_PPARE_PPARE28                      (1 << 28)  /* General PWM Timer Channel 3 Privilege Attribution */

#define R_PSCU_PPARE_PPARE29                      (1 << 29)  /* General PWM Timer Channel 2 Privilege Attribution */

#define R_PSCU_PPARE_PPARE30                      (1 << 30)  /* General PWM Timer Channel 1 Privilege Attribution */

#define R_PSCU_PPARE_PPARE31                      (1 << 31)  /* General PWM Timer Channel 0 Privilege Attribution */

#define R_PSCU_PPARE_PPARE0                       (1 << 0)  /* Peripheral privilege attribution bit 0 */

#define R_PSCU_PPARE_PPARE4                       (1 << 4)  /* Peripheral privilege attribution bit 4 */

#define R_PSCU_PPARE_PPARE5                       (1 << 5)  /* Peripheral privilege attribution bit 5 */

#define R_PSCU_PPARE_PPARE6                       (1 << 6)  /* Peripheral privilege attribution bit 6 */

#define R_PSCU_PPARE_PPARE7                       (1 << 7)  /* Peripheral privilege attribution bit 7 */

#define R_PSCU_PPARE_PPARE10                      (1 << 10)  /* Peripheral privilege attribution bit 10 */

#define R_PSCU_PPARE_PPARE11                      (1 << 11)  /* Peripheral privilege attribution bit 11 */

#define R_PSCU_PPARE_PPARE12                      (1 << 12)  /* Peripheral privilege attribution bit 12 */

#define R_PSCU_PPARE_PPARE13                      (1 << 13)  /* Peripheral privilege attribution bit 13 */

#define R_PSCU_PPARE_PPARE14                      (1 << 14)  /* Peripheral privilege attribution bit 14 */

#define R_PSCU_PPARE_PPARE15                      (1 << 15)  /* Peripheral privilege attribution bit 15 */

#define R_PSCU_PPARE_PPARE16                      (1 << 16)  /* Peripheral privilege attribution bit 16 */

#define R_PSCU_PPARE_PPARE17                      (1 << 17)  /* Peripheral privilege attribution bit 17 */

#define R_PSCU_PPARE_PPARE22                      (1 << 22)  /* Peripheral privilege attribution bit 22 */

#define R_PSCU_PPARE_PPARE23                      (1 << 23)  /* Peripheral privilege attribution bit 23 */

#define R_PSCU_PPARE_PPARE24                      (1 << 24)  /* Peripheral privilege attribution bit 24 */

#define R_PSCU_PPARE_PPARE25                      (1 << 25)  /* Peripheral privilege attribution bit 25 */

/* MSPAR Register bit definitions */
#define R_PSCU_MSPAR_MSPAR31                      (1 << 31)  /* ELC Clock Stop Privilege Attribution */

#define R_PSCU_MSPAR_MSPAR0                       (1 << 0)  /* Peripheral privilege attribution bit 0 */

#define R_PSCU_MSPAR_MSPAR1                       (1 << 1)  /* Peripheral privilege attribution bit 1 */

#define R_PSCU_MSPAR_MSPAR2                       (1 << 2)  /* Peripheral privilege attribution bit 2 */

#define R_PSCU_MSPAR_MSPAR3                       (1 << 3)  /* Peripheral privilege attribution bit 3 */

#define R_PSCU_MSPAR_MSPAR4                       (1 << 4)  /* Peripheral privilege attribution bit 4 */

#define R_PSCU_MSPAR_MSPAR5                       (1 << 5)  /* Peripheral privilege attribution bit 5 */

#define R_PSCU_MSPAR_MSPAR6                       (1 << 6)  /* Peripheral privilege attribution bit 6 */

#define R_PSCU_MSPAR_MSPAR7                       (1 << 7)  /* Peripheral privilege attribution bit 7 */

#define R_PSCU_MSPAR_MSPAR8                       (1 << 8)  /* Peripheral privilege attribution bit 8 */

#define R_PSCU_MSPAR_MSPAR9                       (1 << 9)  /* Peripheral privilege attribution bit 9 */

#define R_PSCU_MSPAR_MSPAR10                      (1 << 10)  /* Peripheral privilege attribution bit 10 */

#define R_PSCU_MSPAR_MSPAR11                      (1 << 11)  /* Peripheral privilege attribution bit 11 */

#define R_PSCU_MSPAR_MSPAR12                      (1 << 12)  /* Peripheral privilege attribution bit 12 */

#define R_PSCU_MSPAR_MSPAR13                      (1 << 13)  /* Peripheral privilege attribution bit 13 */

#define R_PSCU_MSPAR_MSPAR14                      (1 << 14)  /* Peripheral privilege attribution bit 14 */

#define R_PSCU_MSPAR_MSPAR15                      (1 << 15)  /* Peripheral privilege attribution bit 15 */

#define R_PSCU_MSPAR_MSPAR16                      (1 << 16)  /* Peripheral privilege attribution bit 16 */

#define R_PSCU_MSPAR_MSPAR17                      (1 << 17)  /* Peripheral privilege attribution bit 17 */

#define R_PSCU_MSPAR_MSPAR18                      (1 << 18)  /* Peripheral privilege attribution bit 18 */

#define R_PSCU_MSPAR_MSPAR19                      (1 << 19)  /* Peripheral privilege attribution bit 19 */

#define R_PSCU_MSPAR_MSPAR20                      (1 << 20)  /* Peripheral privilege attribution bit 20 */

#define R_PSCU_MSPAR_MSPAR21                      (1 << 21)  /* Peripheral privilege attribution bit 21 */

#define R_PSCU_MSPAR_MSPAR22                      (1 << 22)  /* Peripheral privilege attribution bit 22 */

#define R_PSCU_MSPAR_MSPAR23                      (1 << 23)  /* Peripheral privilege attribution bit 23 */

#define R_PSCU_MSPAR_MSPAR24                      (1 << 24)  /* Peripheral privilege attribution bit 24 */

#define R_PSCU_MSPAR_MSPAR25                      (1 << 25)  /* Peripheral privilege attribution bit 25 */

#define R_PSCU_MSPAR_MSPAR26                      (1 << 26)  /* Peripheral privilege attribution bit 26 */

#define R_PSCU_MSPAR_MSPAR27                      (1 << 27)  /* Peripheral privilege attribution bit 27 */

#define R_PSCU_MSPAR_MSPAR28                      (1 << 28)  /* Peripheral privilege attribution bit 28 */

#define R_PSCU_MSPAR_MSPAR29                      (1 << 29)  /* Peripheral privilege attribution bit 29 */

#define R_PSCU_MSPAR_MSPAR30                      (1 << 30)  /* Peripheral privilege attribution bit 30 */

/* CFSAMONA Register bit definitions */
#define R_PSCU_CFSAMONA_CFS2_SHIFT                (15)  /* Code Flash Secure Area */
#define R_PSCU_CFSAMONA_CFS2_MASK                 0xff8000

/* DFSAMON Register bit definitions */
#define R_PSCU_DFSAMON_DFS_SHIFT                  (10)  /* Data Flash Secure Area */
#define R_PSCU_DFSAMON_DFS_MASK                   0xfc00

/* DLMMON Register bit definitions */
#define R_PSCU_DLMMON_DLMMON_SHIFT                (0)  /* Device Lifecycle Management State Monitor */
#define R_PSCU_DLMMON_DLMMON_MASK                 0xf
#  define R_PSCU_DLMMON_DLMMON_0X0                        (0 << R_PSCU_DLMMON_DLMMON_SHIFT)  /* Reserved */
#  define R_PSCU_DLMMON_DLMMON_0X1                        (1 << R_PSCU_DLMMON_DLMMON_SHIFT)  /* Reserved */
#  define R_PSCU_DLMMON_DLMMON_0X2                        (2 << R_PSCU_DLMMON_DLMMON_SHIFT)  /* Reserved */
#  define R_PSCU_DLMMON_DLMMON_0X3                        (3 << R_PSCU_DLMMON_DLMMON_SHIFT)  /* Reserved */
#  define R_PSCU_DLMMON_DLMMON_0X4                        (4 << R_PSCU_DLMMON_DLMMON_SHIFT)  /* OEM */
#  define R_PSCU_DLMMON_DLMMON_0X5                        (5 << R_PSCU_DLMMON_DLMMON_SHIFT)  /* Reserved */
#  define R_PSCU_DLMMON_DLMMON_0X6                        (6 << R_PSCU_DLMMON_DLMMON_SHIFT)  /* LCK_BOOT */
#  define R_PSCU_DLMMON_DLMMON_0X7                        (7 << R_PSCU_DLMMON_DLMMON_SHIFT)  /* RMA_REQ */
#  define R_PSCU_DLMMON_DLMMON_0X8                        (8 << R_PSCU_DLMMON_DLMMON_SHIFT)  /* RMA_ACK */
#  define R_PSCU_DLMMON_DLMMON_0X9                        (9 << R_PSCU_DLMMON_DLMMON_SHIFT)  /* RMA_RET */


/* Maximum number of channels */

#define PSCU_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_PSCU_H */

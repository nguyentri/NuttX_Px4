/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_gpt32.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT32_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT32_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPT32 Base Address */
#ifndef R_GPT32_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_GPT32_BASE           0x40322000
#else
#define R_GPT32_BASE           0x50322000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_GPT32_CH_STRIDE    0x00000100
#define R_GPT32_CH_BASE(ch)   (R_GPT32_BASE + ((uint32_t)(ch) * R_GPT32_CH_STRIDE))

/* GPT32 Register Offsets */

#define R_GPT32_GTWP_OFFSET                       0x00000000  /* General PWM Timer Write-Protection Register */
#define R_GPT32_GTSTR_OFFSET                      0x00000004  /* General PWM Timer Software Start Register */
#define R_GPT32_GTSTP_OFFSET                      0x00000008  /* General PWM Timer Software Stop Register */
#define R_GPT32_GTCLR_OFFSET                      0x0000000c  /* General PWM Timer Software Clear Register */
#define R_GPT32_GTSSR_OFFSET                      0x00000010  /* General PWM Timer Start Source Select Register */
#define R_GPT32_GTPSR_OFFSET                      0x00000014  /* General PWM Timer Stop Source Select Register */
#define R_GPT32_GTCSR_OFFSET                      0x00000018  /* General PWM Timer Clear Source Select Register */
#define R_GPT32_GTUPSR_OFFSET                     0x0000001c  /* General PWM Timer Up Count Source Select Register */
#define R_GPT32_GTDNSR_OFFSET                     0x00000020  /* General PWM Timer Down Count Source Select Register */
#define R_GPT32_GTICASR_OFFSET                    0x00000024  /* General PWM Timer Input Capture Source Select Register A */
#define R_GPT32_GTICBSR_OFFSET                    0x00000028  /* General PWM Timer Input Capture Source Select Register B */
#define R_GPT32_GTCR_OFFSET                       0x0000002c  /* General PWM Timer Control Register */
#define R_GPT32_GTUDDTYC_OFFSET                   0x00000030  /* General PWM Timer Count Direction and Duty Setting Register */
#define R_GPT32_GTIOR_OFFSET                      0x00000034  /* General PWM Timer I/O Control Register */
#define R_GPT32_GTINTAD_OFFSET                    0x00000038  /* General PWM Timer Interrupt Output Setting Register */
#define R_GPT32_GTST_OFFSET                       0x0000003c  /* General PWM Timer Status Register */
#define R_GPT32_GTBER_OFFSET                      0x00000040  /* General PWM Timer Buffer Enable Register */
#define R_GPT32_GTCNT_OFFSET                      0x00000048  /* General PWM Timer Counter */
#define R_GPT32_GTCCRA_OFFSET                     0x0000004c  /* General PWM Timer Compare Capture Register A */
#define R_GPT32_GTCCRB_OFFSET                     0x00000050  /* General PWM Timer Compare Capture Register B */
#define R_GPT32_GTCCRC_OFFSET                     0x00000054  /* General PWM Timer Compare Capture Register C */
#define R_GPT32_GTCCRE_OFFSET                     0x00000058  /* General PWM Timer Compare Capture Register E */
#define R_GPT32_GTCCRD_OFFSET                     0x0000005c  /* General PWM Timer Compare Capture Register D */
#define R_GPT32_GTCCRF_OFFSET                     0x00000060  /* General PWM Timer Compare Capture Register F */
#define R_GPT32_GTPR_OFFSET                       0x00000064  /* General PWM Timer Cycle Setting Register */
#define R_GPT32_GTPBR_OFFSET                      0x00000068  /* General PWM Timer Cycle Setting Buffer Register */
#define R_GPT32_GTADTRA_OFFSET                    0x00000070  /* A/D Conversion Start Request Timing Register A */
#define R_GPT32_GTADTBRA_OFFSET                   0x00000074  /* A/D Conversion Start Request Timing Buffer Register A */
#define R_GPT32_GTADTDBRA_OFFSET                  0x00000078  /* A/D Conversion Start Request Timing Double-Buffer Register A */
#define R_GPT32_GTADTRB_OFFSET                    0x0000007c  /* A/D Conversion Start Request Timing Register B */
#define R_GPT32_GTADTBRB_OFFSET                   0x00000080  /* A/D Conversion Start Request Timing Buffer Register B */
#define R_GPT32_GTADTDBRB_OFFSET                  0x00000084  /* A/D Conversion Start Request Timing Double-Buffer Register B */
#define R_GPT32_GTDTCR_OFFSET                     0x00000088  /* General PWM Timer Dead Time Control Register */
#define R_GPT32_GTDVU_OFFSET                      0x0000008c  /* General PWM Timer Dead Time Value Register U */
#define R_GPT32_GTADSMR_OFFSET                    0x000000a4  /* General PWM Timer A/D Conversion Start Request Signal Monitoring Register */
#define R_GPT32_GTICLF_OFFSET                     0x000000b8  /* General PWM Timer Inter Channel Logical Operation Function Setting Register */
#define R_GPT32_GTPC_OFFSET                       0x000000bc  /* General PWM Timer Period Count Register */
#define R_GPT32_GTSECSR_OFFSET                    0x000000d0  /* General PWM Timer Operation Enable Bit Simultaneous Control Channel Select Register */
#define R_GPT32_GTSECR_OFFSET                     0x000000d4  /* General PWM Timer Operation Enable Bit Simultaneous Control Register */

/* GPT32 Register Addresses */

#define R_GPT32_GTWP                              (R_GPT32_BASE + R_GPT32_GTWP_OFFSET)
#define R_GPT32_GTSTR                             (R_GPT32_BASE + R_GPT32_GTSTR_OFFSET)
#define R_GPT32_GTSTP                             (R_GPT32_BASE + R_GPT32_GTSTP_OFFSET)
#define R_GPT32_GTCLR                             (R_GPT32_BASE + R_GPT32_GTCLR_OFFSET)
#define R_GPT32_GTSSR                             (R_GPT32_BASE + R_GPT32_GTSSR_OFFSET)
#define R_GPT32_GTPSR                             (R_GPT32_BASE + R_GPT32_GTPSR_OFFSET)
#define R_GPT32_GTCSR                             (R_GPT32_BASE + R_GPT32_GTCSR_OFFSET)
#define R_GPT32_GTUPSR                            (R_GPT32_BASE + R_GPT32_GTUPSR_OFFSET)
#define R_GPT32_GTDNSR                            (R_GPT32_BASE + R_GPT32_GTDNSR_OFFSET)
#define R_GPT32_GTICASR                           (R_GPT32_BASE + R_GPT32_GTICASR_OFFSET)
#define R_GPT32_GTICBSR                           (R_GPT32_BASE + R_GPT32_GTICBSR_OFFSET)
#define R_GPT32_GTCR                              (R_GPT32_BASE + R_GPT32_GTCR_OFFSET)
#define R_GPT32_GTUDDTYC                          (R_GPT32_BASE + R_GPT32_GTUDDTYC_OFFSET)
#define R_GPT32_GTIOR                             (R_GPT32_BASE + R_GPT32_GTIOR_OFFSET)
#define R_GPT32_GTINTAD                           (R_GPT32_BASE + R_GPT32_GTINTAD_OFFSET)
#define R_GPT32_GTST                              (R_GPT32_BASE + R_GPT32_GTST_OFFSET)
#define R_GPT32_GTBER                             (R_GPT32_BASE + R_GPT32_GTBER_OFFSET)
#define R_GPT32_GTCNT                             (R_GPT32_BASE + R_GPT32_GTCNT_OFFSET)
#define R_GPT32_GTCCRA                            (R_GPT32_BASE + R_GPT32_GTCCRA_OFFSET)
#define R_GPT32_GTCCRB                            (R_GPT32_BASE + R_GPT32_GTCCRB_OFFSET)
#define R_GPT32_GTCCRC                            (R_GPT32_BASE + R_GPT32_GTCCRC_OFFSET)
#define R_GPT32_GTCCRE                            (R_GPT32_BASE + R_GPT32_GTCCRE_OFFSET)
#define R_GPT32_GTCCRD                            (R_GPT32_BASE + R_GPT32_GTCCRD_OFFSET)
#define R_GPT32_GTCCRF                            (R_GPT32_BASE + R_GPT32_GTCCRF_OFFSET)
#define R_GPT32_GTPR                              (R_GPT32_BASE + R_GPT32_GTPR_OFFSET)
#define R_GPT32_GTPBR                             (R_GPT32_BASE + R_GPT32_GTPBR_OFFSET)
#define R_GPT32_GTADTRA                           (R_GPT32_BASE + R_GPT32_GTADTRA_OFFSET)
#define R_GPT32_GTADTBRA                          (R_GPT32_BASE + R_GPT32_GTADTBRA_OFFSET)
#define R_GPT32_GTADTDBRA                         (R_GPT32_BASE + R_GPT32_GTADTDBRA_OFFSET)
#define R_GPT32_GTADTRB                           (R_GPT32_BASE + R_GPT32_GTADTRB_OFFSET)
#define R_GPT32_GTADTBRB                          (R_GPT32_BASE + R_GPT32_GTADTBRB_OFFSET)
#define R_GPT32_GTADTDBRB                         (R_GPT32_BASE + R_GPT32_GTADTDBRB_OFFSET)
#define R_GPT32_GTDTCR                            (R_GPT32_BASE + R_GPT32_GTDTCR_OFFSET)
#define R_GPT32_GTDVU                             (R_GPT32_BASE + R_GPT32_GTDVU_OFFSET)
#define R_GPT32_GTADSMR                           (R_GPT32_BASE + R_GPT32_GTADSMR_OFFSET)
#define R_GPT32_GTICLF                            (R_GPT32_BASE + R_GPT32_GTICLF_OFFSET)
#define R_GPT32_GTPC                              (R_GPT32_BASE + R_GPT32_GTPC_OFFSET)
#define R_GPT32_GTSECSR                           (R_GPT32_BASE + R_GPT32_GTSECSR_OFFSET)
#define R_GPT32_GTSECR                            (R_GPT32_BASE + R_GPT32_GTSECR_OFFSET)

/* Register bit definitions */
/* GTWP Register bit definitions */
#define R_GPT32_GTWP_WP                           (1 << 0)  /* Register Write Disable */

#define R_GPT32_GTWP_STRWP                        (1 << 1)  /* GTSTR.CSTRT Bit Write Disable */

#define R_GPT32_GTWP_STPWP                        (1 << 2)  /* GTSTP.CSTOP Bit Write Disable */

#define R_GPT32_GTWP_CLRWP                        (1 << 3)  /* GTCLR.CCLR Bit Write Disable */

#define R_GPT32_GTWP_CMNWP                        (1 << 4)  /* Common Register Write Disabled */

#define R_GPT32_GTWP_PRKEY_SHIFT                  (8)  /* GTWP Key Code */
#define R_GPT32_GTWP_PRKEY_MASK                   0xff00

/* GTSTR Register bit definitions */
#define R_GPT32_GTSTR_CSTRT0                      (1 << 0)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT32_GTSTR_CSTRT1                      (1 << 1)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT32_GTSTR_CSTRT2                      (1 << 2)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT32_GTSTR_CSTRT3                      (1 << 3)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT32_GTSTR_CSTRT4                      (1 << 4)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT32_GTSTR_CSTRT5                      (1 << 5)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT32_GTSTR_CSTRT6                      (1 << 6)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT32_GTSTR_CSTRT7                      (1 << 7)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT32_GTSTR_CSTRT8                      (1 << 8)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT32_GTSTR_CSTRT9                      (1 << 9)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

/* GTSTP Register bit definitions */
#define R_GPT32_GTSTP_CSTOP0                      (1 << 0)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT32_GTSTP_CSTOP1                      (1 << 1)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT32_GTSTP_CSTOP2                      (1 << 2)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT32_GTSTP_CSTOP3                      (1 << 3)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT32_GTSTP_CSTOP4                      (1 << 4)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT32_GTSTP_CSTOP5                      (1 << 5)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT32_GTSTP_CSTOP6                      (1 << 6)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT32_GTSTP_CSTOP7                      (1 << 7)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT32_GTSTP_CSTOP8                      (1 << 8)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT32_GTSTP_CSTOP9                      (1 << 9)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

/* GTCLR Register bit definitions */
#define R_GPT32_GTCLR_CCLR0                       (1 << 0)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT32_GTCLR_CCLR1                       (1 << 1)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT32_GTCLR_CCLR2                       (1 << 2)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT32_GTCLR_CCLR3                       (1 << 3)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT32_GTCLR_CCLR4                       (1 << 4)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT32_GTCLR_CCLR5                       (1 << 5)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT32_GTCLR_CCLR6                       (1 << 6)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT32_GTCLR_CCLR7                       (1 << 7)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT32_GTCLR_CCLR8                       (1 << 8)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT32_GTCLR_CCLR9                       (1 << 9)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

/* GTSSR Register bit definitions */
#define R_GPT32_GTSSR_SSGTRGAR                    (1 << 0)  /* GTETRGA Pin Rising Input Source Counter Start Enable */

#define R_GPT32_GTSSR_SSGTRGAF                    (1 << 1)  /* GTETRGA Pin Falling Input Source Counter Start Enable */

#define R_GPT32_GTSSR_SSGTRGBR                    (1 << 2)  /* GTETRGB Pin Rising Input Source Counter Start Enable */

#define R_GPT32_GTSSR_SSGTRGBF                    (1 << 3)  /* GTETRGB Pin Falling Input Source Counter Start Enable */

#define R_GPT32_GTSSR_SSGTRGCR                    (1 << 4)  /* GTETRGC Pin Rising Input Source Counter Start Enable */

#define R_GPT32_GTSSR_SSGTRGCF                    (1 << 5)  /* GTETRGC Pin Falling Input Source Counter Start Enable */

#define R_GPT32_GTSSR_SSGTRGDR                    (1 << 6)  /* GTETRGD Pin Rising Input Source Counter Start Enable */

#define R_GPT32_GTSSR_SSGTRGDF                    (1 << 7)  /* GTETRGD Pin Falling Input Source Counter Start Enable */

#define R_GPT32_GTSSR_SSCARBL                     (1 << 8)  /* GTIOCnA Pin Rising Input during GTIOCnB Value Low Source Counter Start Enable */

#define R_GPT32_GTSSR_SSCARBH                     (1 << 9)  /* GTIOCnA Pin Rising Input during GTIOCnB Value High Source Counter Start Enable */

#define R_GPT32_GTSSR_SSCAFBL                     (1 << 10)  /* GTIOCnA Pin Falling Input during GTIOCnB Value Low Source Counter Start Enable */

#define R_GPT32_GTSSR_SSCAFBH                     (1 << 11)  /* GTIOCnA Pin Falling Input during GTIOCnB Value High Source Counter Start Enable */

#define R_GPT32_GTSSR_SSCBRAL                     (1 << 12)  /* GTIOCnB Pin Rising Input during GTIOCnA Value Low Source Counter Start Enable */

#define R_GPT32_GTSSR_SSCBRAH                     (1 << 13)  /* GTIOCnB Pin Rising Input during GTIOCnA Value High Source Counter Start Enable */

#define R_GPT32_GTSSR_SSCBFAL                     (1 << 14)  /* GTIOCnB Pin Falling Input during GTIOCnA Value Low Source Counter Start Enable */

#define R_GPT32_GTSSR_SSCBFAH                     (1 << 15)  /* GTIOCnB Pin Falling Input during GTIOCnA Value High Source Counter Start Enable */

#define R_GPT32_GTSSR_SSELCA                      (1 << 16)  /* ELC_GPTA Event Source Counter Start Enable */

#define R_GPT32_GTSSR_SSELCB                      (1 << 17)  /* ELC_GPTB Event Source Counter Start Enable */

#define R_GPT32_GTSSR_SSELCC                      (1 << 18)  /* ELC_GPTC Event Source Counter Start Enable */

#define R_GPT32_GTSSR_SSELCD                      (1 << 19)  /* ELC_GPTD Event Source Counter Start Enable */

#define R_GPT32_GTSSR_SSELCE                      (1 << 20)  /* ELC_GPTE Event Source Counter Start Enable */

#define R_GPT32_GTSSR_SSELCF                      (1 << 21)  /* ELC_GPTF Event Source Counter Start Enable */

#define R_GPT32_GTSSR_SSELCG                      (1 << 22)  /* ELC_GPTG Event Source Counter Start Enable */

#define R_GPT32_GTSSR_SSELCH                      (1 << 23)  /* ELC_GPTH Event Source Counter Start Enable */

#define R_GPT32_GTSSR_CSTRT                       (1 << 31)  /* Software Source Counter Start Enable */

/* GTPSR Register bit definitions */
#define R_GPT32_GTPSR_PSGTRGAR                    (1 << 0)  /* GTETRGA Pin Rising Input Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSGTRGAF                    (1 << 1)  /* GTETRGA Pin Falling Input Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSGTRGBR                    (1 << 2)  /* GTETRGB Pin Rising Input Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSGTRGBF                    (1 << 3)  /* GTETRGB Pin Falling Input Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSGTRGCR                    (1 << 4)  /* GTETRGC Pin Rising Input Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSGTRGCF                    (1 << 5)  /* GTETRGC Pin Falling Input Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSGTRGDR                    (1 << 6)  /* GTETRGD Pin Rising Input Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSGTRGDF                    (1 << 7)  /* GTETRGD Pin Falling Input Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSCARBL                     (1 << 8)  /* GTIOCnA Pin Rising Input during GTIOCnB Value Low Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSCARBH                     (1 << 9)  /* GTIOCnA Pin Rising Input during GTIOCnB Value High Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSCAFBL                     (1 << 10)  /* GTIOCnA Pin Falling Input during GTIOCnB Value Low Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSCAFBH                     (1 << 11)  /* GTIOCnA Pin Falling Input during GTIOCnB Value High Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSCBRAL                     (1 << 12)  /* GTIOCnB Pin Rising Input during GTIOCnA Value Low Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSCBRAH                     (1 << 13)  /* GTIOCnB Pin Rising Input during GTIOCnA Value High Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSCBFAL                     (1 << 14)  /* GTIOCnB Pin Falling Input during GTIOCnA Value Low Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSCBFAH                     (1 << 15)  /* GTIOCnB Pin Falling Input during GTIOCnA Value High Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSELCA                      (1 << 16)  /* ELC_GPTA Event Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSELCB                      (1 << 17)  /* ELC_GPTB Event Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSELCC                      (1 << 18)  /* ELC_GPTC Event Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSELCD                      (1 << 19)  /* ELC_GPTD Event Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSELCE                      (1 << 20)  /* ELC_GPTE Event Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSELCF                      (1 << 21)  /* ELC_GPTF Event Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSELCG                      (1 << 22)  /* ELC_GPTG Event Source Counter Stop Enable */

#define R_GPT32_GTPSR_PSELCH                      (1 << 23)  /* ELC_GPTH Event Source Counter Stop Enable */

#define R_GPT32_GTPSR_CSTOP                       (1 << 31)  /* Software Source Counter Stop Enable */

/* GTCSR Register bit definitions */
#define R_GPT32_GTCSR_CSGTRGAR                    (1 << 0)  /* GTETRGA Pin Rising Input Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSGTRGAF                    (1 << 1)  /* GTETRGA Pin Falling Input Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSGTRGBR                    (1 << 2)  /* GTETRGB Pin Rising Input Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSGTRGBF                    (1 << 3)  /* GTETRGB Pin Falling Input Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSGTRGCR                    (1 << 4)  /* GTETRGC Pin Rising Input Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSGTRGCF                    (1 << 5)  /* GTETRGC Pin Falling Input Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSGTRGDR                    (1 << 6)  /* GTETRGD Pin Rising Input Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSGTRGDF                    (1 << 7)  /* GTETRGD Pin Falling Input Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSCARBL                     (1 << 8)  /* GTIOCnA Pin Rising Input during GTIOCnB Value Low Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSCARBH                     (1 << 9)  /* GTIOCnA Pin Rising Input during GTIOCnB Value High Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSCAFBL                     (1 << 10)  /* GTIOCnA Pin Falling Input during GTIOCnB Value Low Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSCAFBH                     (1 << 11)  /* GTIOCnA Pin Falling Input during GTIOCnB Value High Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSCBRAL                     (1 << 12)  /* GTIOCnB Pin Rising Input during GTIOCnA Value Low Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSCBRAH                     (1 << 13)  /* GTIOCnB Pin Rising Input during GTIOCnA Value High Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSCBFAL                     (1 << 14)  /* GTIOCnB Pin Falling Input during GTIOCnA Value Low Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSCBFAH                     (1 << 15)  /* GTIOCnB Pin Falling Input during GTIOCnA Value High Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSELCA                      (1 << 16)  /* ELC_GPTA Event Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSELCB                      (1 << 17)  /* ELC_GPTB Event Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSELCC                      (1 << 18)  /* ELC_GPTC Event Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSELCD                      (1 << 19)  /* ELC_GPTD Event Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSELCE                      (1 << 20)  /* ELC_GPTE Event Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSELCF                      (1 << 21)  /* ELC_GPTF Event Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSELCG                      (1 << 22)  /* ELC_GPTG Event Source Counter Clear Enable */

#define R_GPT32_GTCSR_CSELCH                      (1 << 23)  /* ELC_GPTH Event Source Counter Clear Enable */

#define R_GPT32_GTCSR_CCLR                        (1 << 31)  /* Software Source Counter Clear Enable */

/* GTUPSR Register bit definitions */
#define R_GPT32_GTUPSR_USGTRGAR                   (1 << 0)  /* GTETRGA Pin Rising Input Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USGTRGAF                   (1 << 1)  /* GTETRGA Pin Falling Input Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USGTRGBR                   (1 << 2)  /* GTETRGB Pin Rising Input Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USGTRGBF                   (1 << 3)  /* GTETRGB Pin Falling Input Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USGTRGCR                   (1 << 4)  /* GTETRGC Pin Rising Input Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USGTRGCF                   (1 << 5)  /* GTETRGC Pin Falling Input Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USGTRGDR                   (1 << 6)  /* GTETRGD Pin Rising Input Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USGTRGDF                   (1 << 7)  /* GTETRGD Pin Falling Input Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USCARBL                    (1 << 8)  /* GTIOCnA Pin Rising Input during GTIOCnB Value Low Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USCARBH                    (1 << 9)  /* GTIOCnA Pin Rising Input during GTIOCnB Value High Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USCAFBL                    (1 << 10)  /* GTIOCnA Pin Falling Input during GTIOCnB Value Low Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USCAFBH                    (1 << 11)  /* GTIOCnA Pin Falling Input during GTIOCnB Value High Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USCBRAL                    (1 << 12)  /* GTIOCnB Pin Rising Input during GTIOCnA Value Low Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USCBRAH                    (1 << 13)  /* GTIOCnB Pin Rising Input during GTIOCnA Value High Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USCBFAL                    (1 << 14)  /* GTIOCnB Pin Falling Input during GTIOCnA Value Low Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USCBFAH                    (1 << 15)  /* GTIOCnB Pin Falling Input during GTIOCnA Value High Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USELCA                     (1 << 16)  /* ELC_GPTA Event Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USELCB                     (1 << 17)  /* ELC_GPTB Event Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USELCC                     (1 << 18)  /* ELC_GPTC Event Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USELCD                     (1 << 19)  /* ELC_GPTD Event Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USELCE                     (1 << 20)  /* ELC_GPTE Event Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USELCF                     (1 << 21)  /* ELC_GPTF Event Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USELCG                     (1 << 22)  /* ELC_GPTG Event Source Counter Count Up Enable */

#define R_GPT32_GTUPSR_USELCH                     (1 << 23)  /* ELC_GPTH Event Source Counter Count Up Enable */

/* GTDNSR Register bit definitions */
#define R_GPT32_GTDNSR_DSGTRGAR                   (1 << 0)  /* GTETRGA Pin Rising Input Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSGTRGAF                   (1 << 1)  /* GTETRGA Pin Falling Input Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSGTRGBR                   (1 << 2)  /* GTETRGB Pin Rising Input Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSGTRGBF                   (1 << 3)  /* GTETRGB Pin Falling Input Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSGTRGCR                   (1 << 4)  /* GTETRGC Pin Rising Input Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSGTRGCF                   (1 << 5)  /* GTETRGC Pin Falling Input Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSGTRGDR                   (1 << 6)  /* GTETRGD Pin Rising Input Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSGTRGDF                   (1 << 7)  /* GTETRGD Pin Falling Input Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSCARBL                    (1 << 8)  /* GTIOCnA Pin Rising Input during GTIOCnB Value Low Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSCARBH                    (1 << 9)  /* GTIOCnA Pin Rising Input during GTIOCnB Value High Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSCAFBL                    (1 << 10)  /* GTIOCnA Pin Falling Input during GTIOCnB Value Low Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSCAFBH                    (1 << 11)  /* GTIOCnA Pin Falling Input during GTIOCnB Value High Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSCBRAL                    (1 << 12)  /* GTIOCnB Pin Rising Input during GTIOCnA Value Low Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSCBRAH                    (1 << 13)  /* GTIOCnB Pin Rising Input during GTIOCnA Value High Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSCBFAL                    (1 << 14)  /* GTIOCnB Pin Falling Input during GTIOCnA Value Low Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSCBFAH                    (1 << 15)  /* GTIOCnB Pin Falling Input during GTIOCnA Value High Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSELCA                     (1 << 16)  /* ELC_GPTA Event Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSELCB                     (1 << 17)  /* ELC_GPTB Event Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSELCC                     (1 << 18)  /* ELC_GPTC Event Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSELCD                     (1 << 19)  /* ELC_GPTD Event Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSELCE                     (1 << 20)  /* ELC_GPTE Event Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSELCF                     (1 << 21)  /* ELC_GPTF Event Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSELCG                     (1 << 22)  /* ELC_GPTG Event Source Counter Count Down Enable */

#define R_GPT32_GTDNSR_DSELCH                     (1 << 23)  /* ELC_GPTF Event Source Counter Count Down Enable */

/* GTICASR Register bit definitions */
#define R_GPT32_GTICASR_ASGTRGAR                  (1 << 0)  /* GTETRGA Pin Rising Input Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASGTRGAF                  (1 << 1)  /* GTETRGA Pin Falling Input Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASGTRGBR                  (1 << 2)  /* GTETRGB Pin Rising Input Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASGTRGBF                  (1 << 3)  /* GTETRGB Pin Falling Input Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASGTRGCR                  (1 << 4)  /* GTETRGC Pin Rising Input Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASGTRGCF                  (1 << 5)  /* GTETRGC Pin Falling Input Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASGTRGDR                  (1 << 6)  /* GTETRGD Pin Rising Input Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASGTRGDF                  (1 << 7)  /* GTETRGD Pin Falling Input Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASCARBL                   (1 << 8)  /* GTIOCnA Pin Rising Input during GTIOCnB Value Low Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASCARBH                   (1 << 9)  /* GTIOCnA Pin Rising Input during GTIOCnB Value High Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASCAFBL                   (1 << 10)  /* GTIOCnA Pin Falling Input during GTIOCnB Value Low Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASCAFBH                   (1 << 11)  /* GTIOCnA Pin Falling Input during GTIOCnB Value High Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASCBRAL                   (1 << 12)  /* GTIOCnB Pin Rising Input during GTIOCnA Value Low Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASCBRAH                   (1 << 13)  /* GTIOCnB Pin Rising Input during GTIOCnA Value High Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASCBFAL                   (1 << 14)  /* GTIOCnB Pin Falling Input during GTIOCnA Value Low Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASCBFAH                   (1 << 15)  /* GTIOCnB Pin Falling Input during GTIOCnA Value High Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASELCA                    (1 << 16)  /* ELC_GPTA Event Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASELCB                    (1 << 17)  /* ELC_GPTB Event Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASELCC                    (1 << 18)  /* ELC_GPTC Event Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASELCD                    (1 << 19)  /* ELC_GPTD Event Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASELCE                    (1 << 20)  /* ELC_GPTE Event Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASELCF                    (1 << 21)  /* ELC_GPTF Event Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASELCG                    (1 << 22)  /* ELC_GPTG Event Source GTCCRA Input Capture Enable */

#define R_GPT32_GTICASR_ASELCH                    (1 << 23)  /* ELC_GPTH Event Source GTCCRA Input Capture Enable */

/* GTICBSR Register bit definitions */
#define R_GPT32_GTICBSR_BSGTRGAR                  (1 << 0)  /* GTETRGA Pin Rising Input Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSGTRGAF                  (1 << 1)  /* GTETRGA Pin Falling Input Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSGTRGBR                  (1 << 2)  /* GTETRGB Pin Rising Input Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSGTRGBF                  (1 << 3)  /* GTETRGB Pin Falling Input Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSGTRGCR                  (1 << 4)  /* GTETRGC Pin Rising Input Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSGTRGCF                  (1 << 5)  /* GTETRGC Pin Falling Input Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSGTRGDR                  (1 << 6)  /* GTETRGD Pin Rising Input Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSGTRGDF                  (1 << 7)  /* GTETRGD Pin Falling Input Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSCARBL                   (1 << 8)  /* GTIOCnA Pin Rising Input during GTIOCnB Value Low Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSCARBH                   (1 << 9)  /* GTIOCnA Pin Rising Input during GTIOCnB Value High Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSCAFBL                   (1 << 10)  /* GTIOCnA Pin Falling Input during GTIOCnB Value Low Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSCAFBH                   (1 << 11)  /* GTIOCnA Pin Falling Input during GTIOCnB Value High Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSCBRAL                   (1 << 12)  /* GTIOCnB Pin Rising Input during GTIOCnA Value Low Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSCBRAH                   (1 << 13)  /* GTIOCnB Pin Rising Input during GTIOCnA Value High Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSCBFAL                   (1 << 14)  /* GTIOCnB Pin Falling Input during GTIOCnA Value Low Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSCBFAH                   (1 << 15)  /* GTIOCnB Pin Falling Input during GTIOCnA Value High Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSELCA                    (1 << 16)  /* ELC_GPTA Event Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSELCB                    (1 << 17)  /* ELC_GPTB Event Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSELCC                    (1 << 18)  /* ELC_GPTC Event Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSELCD                    (1 << 19)  /* ELC_GPTD Event Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSELCE                    (1 << 20)  /* ELC_GPTE Event Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSELCF                    (1 << 21)  /* ELC_GPTF Event Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSELCG                    (1 << 22)  /* ELC_GPTG Event Source GTCCRB Input Capture Enable */

#define R_GPT32_GTICBSR_BSELCH                    (1 << 23)  /* ELC_GPTH Event Source GTCCRB Input Capture Enable */

/* GTCR Register bit definitions */
#define R_GPT32_GTCR_CST                          (1 << 0)  /* Count Start */

#define R_GPT32_GTCR_MD_SHIFT                     (16)  /* Mode Select */
#define R_GPT32_GTCR_MD_MASK                      0x70000
#  define R_GPT32_GTCR_MD_000                             (0 << R_GPT32_GTCR_MD_SHIFT)  /* Saw-wave PWM mode (single buffer or double buffer possible) */
#  define R_GPT32_GTCR_MD_001                             (1 << R_GPT32_GTCR_MD_SHIFT)  /* Saw-wave one-shot pulse mode (fixed buffer operation) */
#  define R_GPT32_GTCR_MD_010                             (2 << R_GPT32_GTCR_MD_SHIFT)  /* Setting prohibited */
#  define R_GPT32_GTCR_MD_011                             (3 << R_GPT32_GTCR_MD_SHIFT)  /* Setting prohibited */
#  define R_GPT32_GTCR_MD_100                             (4 << R_GPT32_GTCR_MD_SHIFT)  /* Triangle-wave PWM mode 1 (32-bit transfer at trough) (single buffer or double buffer is possible) */
#  define R_GPT32_GTCR_MD_101                             (5 << R_GPT32_GTCR_MD_SHIFT)  /* Triangle-wave PWM mode 2 (32-bit transfer at crest and trough) (single buffer or double buffer is possible) */
#  define R_GPT32_GTCR_MD_110                             (6 << R_GPT32_GTCR_MD_SHIFT)  /* Triangle-wave PWM mode 3 (64-bit transfer at trough) (fixed buffer operation) */
#  define R_GPT32_GTCR_MD_111                             (7 << R_GPT32_GTCR_MD_SHIFT)  /* Setting prohibited */

#define R_GPT32_GTCR_TPCS_SHIFT                   (23)  /* Timer Prescaler Select */
#define R_GPT32_GTCR_TPCS_MASK                    0x7800000
#  define R_GPT32_GTCR_TPCS_0X0                           (0 << R_GPT32_GTCR_TPCS_SHIFT)  /* PCLKD/1  */
#  define R_GPT32_GTCR_TPCS_0X1                           (0 << R_GPT32_GTCR_TPCS_SHIFT)  /* PCLKD/2  */
#  define R_GPT32_GTCR_TPCS_0X2                           (0 << R_GPT32_GTCR_TPCS_SHIFT)  /* PCLKD/4  */
#  define R_GPT32_GTCR_TPCS_0X3                           (0 << R_GPT32_GTCR_TPCS_SHIFT)  /* PCLKD/8  */
#  define R_GPT32_GTCR_TPCS_0X4                           (0 << R_GPT32_GTCR_TPCS_SHIFT)  /* PCLKD/16  */
#  define R_GPT32_GTCR_TPCS_0X5                           (0 << R_GPT32_GTCR_TPCS_SHIFT)  /* PCLKD/32  */
#  define R_GPT32_GTCR_TPCS_0X6                           (0 << R_GPT32_GTCR_TPCS_SHIFT)  /* PCLKD/64  */
#  define R_GPT32_GTCR_TPCS_0X7                           (0 << R_GPT32_GTCR_TPCS_SHIFT)  /* Setting prohibited */
#  define R_GPT32_GTCR_TPCS_0X8                           (0 << R_GPT32_GTCR_TPCS_SHIFT)  /* PCLKD/256  */
#  define R_GPT32_GTCR_TPCS_0X9                           (0 << R_GPT32_GTCR_TPCS_SHIFT)  /* Setting prohibited */
#  define R_GPT32_GTCR_TPCS_0XA                           (0 << R_GPT32_GTCR_TPCS_SHIFT)  /* PCLKD/1024  */
#  define R_GPT32_GTCR_TPCS_0XB                           (0 << R_GPT32_GTCR_TPCS_SHIFT)  /* Setting prohibited */
#  define R_GPT32_GTCR_TPCS_0XC                           (0 << R_GPT32_GTCR_TPCS_SHIFT)  /* GTETRGA (Via the POEG) */
#  define R_GPT32_GTCR_TPCS_0XD                           (0 << R_GPT32_GTCR_TPCS_SHIFT)  /* GTETRGB (Via the POEG) */
#  define R_GPT32_GTCR_TPCS_0XE                           (0 << R_GPT32_GTCR_TPCS_SHIFT)  /* GTETRGC (Via the POEG) */
#  define R_GPT32_GTCR_TPCS_0XF                           (0 << R_GPT32_GTCR_TPCS_SHIFT)  /* GTETRGD (Via the POEG) */

/* GTUDDTYC Register bit definitions */
#define R_GPT32_GTUDDTYC_UD                       (1 << 0)  /* Count Direction Setting */

#define R_GPT32_GTUDDTYC_UDF                      (1 << 1)  /* Forcible Count Direction Setting */

#define R_GPT32_GTUDDTYC_OADTY_SHIFT              (16)  /* GTIOCnA Output Duty Setting */
#define R_GPT32_GTUDDTYC_OADTY_MASK               0x30000
#  define R_GPT32_GTUDDTYC_OADTY_00                       (0 << R_GPT32_GTUDDTYC_OADTY_SHIFT)  /* GTIOCnA pin duty depends on the compare match */
#  define R_GPT32_GTUDDTYC_OADTY_01                       (1 << R_GPT32_GTUDDTYC_OADTY_SHIFT)  /* GTIOCnA pin duty depends on the compare match */
#  define R_GPT32_GTUDDTYC_OADTY_10                       (2 << R_GPT32_GTUDDTYC_OADTY_SHIFT)  /* GTIOCnA pin duty 0% */
#  define R_GPT32_GTUDDTYC_OADTY_11                       (3 << R_GPT32_GTUDDTYC_OADTY_SHIFT)  /* GTIOCnA pin duty 100% */

#define R_GPT32_GTUDDTYC_OADTYF                   (1 << 18)  /* Forcible GTIOCnA Output Duty Setting */

#define R_GPT32_GTUDDTYC_OADTYR                   (1 << 19)  /* GTIOCnA Output Value Selecting after Releasing 0%/100% Duty Setting */

#define R_GPT32_GTUDDTYC_OBDTY_SHIFT              (24)  /* GTIOCnB Output Duty Setting */
#define R_GPT32_GTUDDTYC_OBDTY_MASK               0x3000000
#  define R_GPT32_GTUDDTYC_OBDTY_00                       (0 << R_GPT32_GTUDDTYC_OBDTY_SHIFT)  /* GTIOCnB pin duty depends on the compare match */
#  define R_GPT32_GTUDDTYC_OBDTY_01                       (1 << R_GPT32_GTUDDTYC_OBDTY_SHIFT)  /* GTIOCnB pin duty depends on the compare match */
#  define R_GPT32_GTUDDTYC_OBDTY_10                       (2 << R_GPT32_GTUDDTYC_OBDTY_SHIFT)  /* GTIOCnB pin duty 0% */
#  define R_GPT32_GTUDDTYC_OBDTY_11                       (3 << R_GPT32_GTUDDTYC_OBDTY_SHIFT)  /* GTIOCnB pin duty 100% */

#define R_GPT32_GTUDDTYC_OBDTYF                   (1 << 26)  /* Forcible GTIOCnB Output Duty Setting */

#define R_GPT32_GTUDDTYC_OBDTYR                   (1 << 27)  /* GTIOCnB Output Value Selecting after Releasing 0%/100% Duty Setting */

/* GTIOR Register bit definitions */
#define R_GPT32_GTIOR_GTIOA_SHIFT                 (0)  /* GTIOCnA Pin Function Select */
#define R_GPT32_GTIOR_GTIOA_MASK                  0x1f

#define R_GPT32_GTIOR_OADFLT                      (1 << 6)  /* GTIOCnA Pin Output Value Setting at the Count Stop */

#define R_GPT32_GTIOR_OAHLD                       (1 << 7)  /* GTIOCnA Pin Output Setting at the Start/Stop Count */

#define R_GPT32_GTIOR_OAE                         (1 << 8)  /* GTIOCnA Pin Output Enable */

#define R_GPT32_GTIOR_OADF_SHIFT                  (9)  /* GTIOCnA Pin Disable Value Setting */
#define R_GPT32_GTIOR_OADF_MASK                   0x600
#  define R_GPT32_GTIOR_OADF_00                           (0 << R_GPT32_GTIOR_OADF_SHIFT)  /* None of the below options are specified */
#  define R_GPT32_GTIOR_OADF_01                           (1 << R_GPT32_GTIOR_OADF_SHIFT)  /* GTIOCnA pin is set to Hi-Z in response to controlling the output negation */
#  define R_GPT32_GTIOR_OADF_10                           (2 << R_GPT32_GTIOR_OADF_SHIFT)  /* GTIOCnA pin is set to 0 in response to controlling the output negation */
#  define R_GPT32_GTIOR_OADF_11                           (3 << R_GPT32_GTIOR_OADF_SHIFT)  /* GTIOCnA pin is set to 1 in response to controlling the output negation */

#define R_GPT32_GTIOR_NFAEN                       (1 << 13)  /* Noise Filter A Enable */

#define R_GPT32_GTIOR_NFCSA_SHIFT                 (14)  /* Noise Filter A Sampling Clock Select */
#define R_GPT32_GTIOR_NFCSA_MASK                  0xc000
#  define R_GPT32_GTIOR_NFCSA_00                          (0 << R_GPT32_GTIOR_NFCSA_SHIFT)  /* PCLKD/1 */
#  define R_GPT32_GTIOR_NFCSA_01                          (1 << R_GPT32_GTIOR_NFCSA_SHIFT)  /* PCLKD/4 */
#  define R_GPT32_GTIOR_NFCSA_10                          (2 << R_GPT32_GTIOR_NFCSA_SHIFT)  /* PCLKD/16 */
#  define R_GPT32_GTIOR_NFCSA_11                          (3 << R_GPT32_GTIOR_NFCSA_SHIFT)  /* PCLKD/64 */

#define R_GPT32_GTIOR_GTIOB_SHIFT                 (16)  /* GTIOCnB Pin Function Select */
#define R_GPT32_GTIOR_GTIOB_MASK                  0x1f0000

#define R_GPT32_GTIOR_OBDFLT                      (1 << 22)  /* GTIOCnB Pin Output Value Setting at the Count Stop */

#define R_GPT32_GTIOR_OBHLD                       (1 << 23)  /* GTIOCnB Pin Output Setting at the Start/Stop Count */

#define R_GPT32_GTIOR_OBE                         (1 << 24)  /* GTIOCnB Pin Output Enable */

#define R_GPT32_GTIOR_OBDF_SHIFT                  (25)  /* GTIOCnB Pin Disable Value Setting */
#define R_GPT32_GTIOR_OBDF_MASK                   0x6000000
#  define R_GPT32_GTIOR_OBDF_00                           (0 << R_GPT32_GTIOR_OBDF_SHIFT)  /* None of the below options are specified */
#  define R_GPT32_GTIOR_OBDF_01                           (1 << R_GPT32_GTIOR_OBDF_SHIFT)  /* GTIOCnB pin is set to Hi-Z in response to controlling the output negation */
#  define R_GPT32_GTIOR_OBDF_10                           (2 << R_GPT32_GTIOR_OBDF_SHIFT)  /* GTIOCnB pin is set to 0 in response to controlling the output negation */
#  define R_GPT32_GTIOR_OBDF_11                           (3 << R_GPT32_GTIOR_OBDF_SHIFT)  /* GTIOCnB pin is set to 1 in response to controlling the output negation */

#define R_GPT32_GTIOR_NFBEN                       (1 << 29)  /* Noise Filter B Enable */

#define R_GPT32_GTIOR_NFCSB_SHIFT                 (30)  /* Noise Filter B Sampling Clock Select */
#define R_GPT32_GTIOR_NFCSB_MASK                  0xc0000000
#  define R_GPT32_GTIOR_NFCSB_00                          (0 << R_GPT32_GTIOR_NFCSB_SHIFT)  /* PCLKD/1 */
#  define R_GPT32_GTIOR_NFCSB_01                          (1 << R_GPT32_GTIOR_NFCSB_SHIFT)  /* PCLKD/4 */
#  define R_GPT32_GTIOR_NFCSB_10                          (2 << R_GPT32_GTIOR_NFCSB_SHIFT)  /* PCLKD/16 */
#  define R_GPT32_GTIOR_NFCSB_11                          (3 << R_GPT32_GTIOR_NFCSB_SHIFT)  /* PCLKD/64 */

/* GTINTAD Register bit definitions */
#define R_GPT32_GTINTAD_GRP_SHIFT                 (24)  /* Output Disable Source Select */
#define R_GPT32_GTINTAD_GRP_MASK                  0x3000000
#  define R_GPT32_GTINTAD_GRP_00                          (0 << R_GPT32_GTINTAD_GRP_SHIFT)  /* Group A output disable request is selected */
#  define R_GPT32_GTINTAD_GRP_01                          (1 << R_GPT32_GTINTAD_GRP_SHIFT)  /* Group B output disable request is selected */
#  define R_GPT32_GTINTAD_GRP_10                          (2 << R_GPT32_GTINTAD_GRP_SHIFT)  /* Group C output disable request is selected */
#  define R_GPT32_GTINTAD_GRP_11                          (3 << R_GPT32_GTINTAD_GRP_SHIFT)  /* Group D output disable request is selected */

#define R_GPT32_GTINTAD_GRPABH                    (1 << 29)  /* Same Time Output Level High Disable Request Enable */

#define R_GPT32_GTINTAD_GRPABL                    (1 << 30)  /* Same Time Output Level Low Disable Request Enable */

/* GTST Register bit definitions */
#define R_GPT32_GTST_TCFA                         (1 << 0)  /* Input Capture/Compare Match Flag A */

#define R_GPT32_GTST_TCFB                         (1 << 1)  /* Input Capture/Compare Match Flag B */

#define R_GPT32_GTST_TCFC                         (1 << 2)  /* Input Compare Match Flag C */

#define R_GPT32_GTST_TCFD                         (1 << 3)  /* Input Compare Match Flag D */

#define R_GPT32_GTST_TCFE                         (1 << 4)  /* Input Compare Match Flag E */

#define R_GPT32_GTST_TCFF                         (1 << 5)  /* Input Compare Match Flag F */

#define R_GPT32_GTST_TCFPO                        (1 << 6)  /* Overflow Flag */

#define R_GPT32_GTST_TCFPU                        (1 << 7)  /* Underflow Flag */

#define R_GPT32_GTST_TUCF                         (1 << 15)  /* Count Direction Flag */

#define R_GPT32_GTST_ADTRAUF                      (1 << 16)  /* GTADTRA Register Compare Match (Up-Counting) A/D Conversion Start Request Flag */

#define R_GPT32_GTST_ADTRADF                      (1 << 17)  /* GTADTRA Register Compare Match (Down-Counting) A/D Conversion Start Request Flag */

#define R_GPT32_GTST_ADTRBUF                      (1 << 18)  /* GTADTRB Register Compare Match (Up-Counting) A/D Conversion Start Request Flag */

#define R_GPT32_GTST_ADTRBDF                      (1 << 19)  /* GTADTRB Register Compare Match (Down-Counting) A/D Conversion Start Request Flag */

#define R_GPT32_GTST_ODF                          (1 << 24)  /* Output Disable Flag */

#define R_GPT32_GTST_OABHF                        (1 << 29)  /* Same Time Output Level High Flag */

#define R_GPT32_GTST_OABLF                        (1 << 30)  /* Same Time Output Level Low Flag */

#define R_GPT32_GTST_PCF                          (1 << 31)  /* Period Count Function Finish Flag */

/* GTBER Register bit definitions */
#define R_GPT32_GTBER_BD0                         (1 << 0)  /* GTCCR Buffer Operation Disable */

#define R_GPT32_GTBER_BD1                         (1 << 1)  /* GTPR Buffer Operation Disable */

#define R_GPT32_GTBER_BD2                         (1 << 2)  /* GTADTRA/GTADTRB Registers Buffer Operation Disable */

#define R_GPT32_GTBER_CCRA_SHIFT                  (16)  /* GTCCRA Buffer Operation */
#define R_GPT32_GTBER_CCRA_MASK                   0x30000
#  define R_GPT32_GTBER_CCRA_00                           (0 << R_GPT32_GTBER_CCRA_SHIFT)  /* No buffer operation */
#  define R_GPT32_GTBER_CCRA_01                           (1 << R_GPT32_GTBER_CCRA_SHIFT)  /* Single buffer operation (GTCCRA <---->GTCCRC) */

#define R_GPT32_GTBER_CCRB_SHIFT                  (18)  /* GTCCRB Buffer Operation */
#define R_GPT32_GTBER_CCRB_MASK                   0xc0000
#  define R_GPT32_GTBER_CCRB_00                           (0 << R_GPT32_GTBER_CCRB_SHIFT)  /* No buffer operation */
#  define R_GPT32_GTBER_CCRB_01                           (1 << R_GPT32_GTBER_CCRB_SHIFT)  /* Single buffer operation (GTCCRB <----> GTCCRE) */

#define R_GPT32_GTBER_PR_SHIFT                    (20)  /* GTPR Buffer Operation */
#define R_GPT32_GTBER_PR_MASK                     0x300000
#  define R_GPT32_GTBER_PR_00                             (0 << R_GPT32_GTBER_PR_SHIFT)  /* No buffer operation */
#  define R_GPT32_GTBER_PR_01                             (1 << R_GPT32_GTBER_PR_SHIFT)  /* Single buffer operation (GTPBR --> GTPR) */

#define R_GPT32_GTBER_CCRSWT                      (1 << 22)  /* GTCCRA and GTCCRB Forcible Buffer Operation */

#define R_GPT32_GTBER_ADTTA_SHIFT                 (24)  /* GTADTRA Register Buffer Transfer Timing Select */
#define R_GPT32_GTBER_ADTTA_MASK                  0x3000000
#  define R_GPT32_GTBER_ADTTA_00                          (0 << R_GPT32_GTBER_ADTTA_SHIFT)  /* In triangle wave mode, no transfer. In saw-wave mode, no transfer.  */
#  define R_GPT32_GTBER_ADTTA_01                          (1 << R_GPT32_GTBER_ADTTA_SHIFT)  /* In triangle wave mode, transfer at crest. In saw-wave mode, transfer at underflow (in down-counting), overflow (in up-counting), or counter clearing.  */
#  define R_GPT32_GTBER_ADTTA_10                          (2 << R_GPT32_GTBER_ADTTA_SHIFT)  /* In triangle wave mode, transfer at trough. In saw-wave mode, transfer at underflow (in down-counting), overflow (in up-counting), or counter clearing.  */
#  define R_GPT32_GTBER_ADTTA_11                          (3 << R_GPT32_GTBER_ADTTA_SHIFT)  /* In triangle wave, transfer at both crest and trough. In saw-wave mode, transfer at underflow (in down-counting), overflow (in up-counting), or counter clearing.  */

#define R_GPT32_GTBER_ADTDA                       (1 << 26)  /* GTADTRA Register Double Buffer Operation */

#define R_GPT32_GTBER_ADTTB_SHIFT                 (28)  /* GTADTRB Register Buffer Transfer Timing Select */
#define R_GPT32_GTBER_ADTTB_MASK                  0x30000000
#  define R_GPT32_GTBER_ADTTB_00                          (0 << R_GPT32_GTBER_ADTTB_SHIFT)  /* In triangle wave mode, no transfer. In saw-wave mode, no transfer.  */
#  define R_GPT32_GTBER_ADTTB_01                          (1 << R_GPT32_GTBER_ADTTB_SHIFT)  /* In triangle wave mode, transfer at crest. In saw-wave mode, transfer at underflow (in down-counting), overflow (in up-counting), or counter clearing.  */
#  define R_GPT32_GTBER_ADTTB_10                          (2 << R_GPT32_GTBER_ADTTB_SHIFT)  /* In triangle wave mode, transfer at trough. In saw-wave mode, transfer at underflow (in down-counting), overflow (in up-counting), or counter clearing.  */
#  define R_GPT32_GTBER_ADTTB_11                          (3 << R_GPT32_GTBER_ADTTB_SHIFT)  /* In triangle wave mode, transfer at both crest and trough. In saw-wave mode, transfer at underflow (in down-counting), overflow (in up-counting), or counter clearing.  */

#define R_GPT32_GTBER_ADTDB                       (1 << 30)  /* GTADTRB Register Double Buffer Operation */

/* GTDTCR Register bit definitions */
#define R_GPT32_GTDTCR_TDE                        (1 << 0)  /* Negative-Phase Waveform Setting */

/* GTADSMR Register bit definitions */
#define R_GPT32_GTADSMR_ADSMS0_SHIFT              (0)  /* A/D Conversion Start Request Signal Monitor 0 Selection */
#define R_GPT32_GTADSMR_ADSMS0_MASK               0x3
#  define R_GPT32_GTADSMR_ADSMS0_00                       (0 << R_GPT32_GTADSMR_ADSMS0_SHIFT)  /* A/D conversion start request signal generated by the GTADTRA register during up-counting. */
#  define R_GPT32_GTADSMR_ADSMS0_01                       (1 << R_GPT32_GTADSMR_ADSMS0_SHIFT)  /* A/D conversion start request signal generated by the GTADTRA register during down-counting. */
#  define R_GPT32_GTADSMR_ADSMS0_10                       (2 << R_GPT32_GTADSMR_ADSMS0_SHIFT)  /* A/D conversion start request signal generated by the GTADTRB register during up-counting. */
#  define R_GPT32_GTADSMR_ADSMS0_11                       (3 << R_GPT32_GTADSMR_ADSMS0_SHIFT)  /* A/D conversion start request signal generated by the GTADTRB register during down-counting. */

#define R_GPT32_GTADSMR_ADSMEN0                   (1 << 8)  /* A/D Conversion Start Request Signal Monitor 0 Output Enabling */

#define R_GPT32_GTADSMR_ADSMS1_SHIFT              (16)  /* A/D Conversion Start Request Signal Monitor 1 Selection */
#define R_GPT32_GTADSMR_ADSMS1_MASK               0x30000
#  define R_GPT32_GTADSMR_ADSMS1_00                       (0 << R_GPT32_GTADSMR_ADSMS1_SHIFT)  /* A/D conversion start request signal generated by the GTADTRA register during up-counting. */
#  define R_GPT32_GTADSMR_ADSMS1_01                       (1 << R_GPT32_GTADSMR_ADSMS1_SHIFT)  /* A/D conversion start request signal generated by the GTADTRA register during down-counting. */
#  define R_GPT32_GTADSMR_ADSMS1_10                       (2 << R_GPT32_GTADSMR_ADSMS1_SHIFT)  /* A/D conversion start request signal generated by the GTADTRB register during up-counting. */
#  define R_GPT32_GTADSMR_ADSMS1_11                       (3 << R_GPT32_GTADSMR_ADSMS1_SHIFT)  /* A/D conversion start request signal generated by the GTADTRB register during down-counting. */

#define R_GPT32_GTADSMR_ADSMEN1                   (1 << 24)  /* A/D Conversion Start Request Signal Monitor 1 Output Enabling */

/* GTICLF Register bit definitions */
#define R_GPT32_GTICLF_ICLFA_SHIFT                (0)  /* GTIOCnA Output Logical Operation Function Select */
#define R_GPT32_GTICLF_ICLFA_MASK                 0x7
#  define R_GPT32_GTICLF_ICLFA_000                        (0 << R_GPT32_GTICLF_ICLFA_SHIFT)  /* A (no delay) */
#  define R_GPT32_GTICLF_ICLFA_001                        (1 << R_GPT32_GTICLF_ICLFA_SHIFT)  /* NOT A (no delay) */
#  define R_GPT32_GTICLF_ICLFA_010                        (2 << R_GPT32_GTICLF_ICLFA_SHIFT)  /* C (1PCLKD delay) */
#  define R_GPT32_GTICLF_ICLFA_011                        (3 << R_GPT32_GTICLF_ICLFA_SHIFT)  /* NOT C (1PCLKD delay) */
#  define R_GPT32_GTICLF_ICLFA_100                        (4 << R_GPT32_GTICLF_ICLFA_SHIFT)  /* A AND C (1PCLKD delay) */
#  define R_GPT32_GTICLF_ICLFA_101                        (5 << R_GPT32_GTICLF_ICLFA_SHIFT)  /* A OR C (1PCLKD delay) */
#  define R_GPT32_GTICLF_ICLFA_110                        (6 << R_GPT32_GTICLF_ICLFA_SHIFT)  /* A EXOR C (1PCLKD delay) */
#  define R_GPT32_GTICLF_ICLFA_111                        (7 << R_GPT32_GTICLF_ICLFA_SHIFT)  /* A NOR C (1PCLKD delay) */

#define R_GPT32_GTICLF_ICLFSELC_SHIFT             (4)  /* Inter Channel Signal C Select */
#define R_GPT32_GTICLF_ICLFSELC_MASK              0x3f0
#  define R_GPT32_GTICLF_ICLFSELC_0X00                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC0A */
#  define R_GPT32_GTICLF_ICLFSELC_0X01                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC0B */
#  define R_GPT32_GTICLF_ICLFSELC_0X02                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC1A */
#  define R_GPT32_GTICLF_ICLFSELC_0X03                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC1B */
#  define R_GPT32_GTICLF_ICLFSELC_0X04                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC2A */
#  define R_GPT32_GTICLF_ICLFSELC_0X05                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC2B */
#  define R_GPT32_GTICLF_ICLFSELC_0X06                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC3A */
#  define R_GPT32_GTICLF_ICLFSELC_0X07                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC3B */
#  define R_GPT32_GTICLF_ICLFSELC_0X08                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC4A */
#  define R_GPT32_GTICLF_ICLFSELC_0X09                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC4B */
#  define R_GPT32_GTICLF_ICLFSELC_0X0A                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC5A */
#  define R_GPT32_GTICLF_ICLFSELC_0X0B                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC5B */
#  define R_GPT32_GTICLF_ICLFSELC_0X0C                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC6A */
#  define R_GPT32_GTICLF_ICLFSELC_0X0D                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC6B */
#  define R_GPT32_GTICLF_ICLFSELC_0X0E                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC7A */
#  define R_GPT32_GTICLF_ICLFSELC_0X0F                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC7B */
#  define R_GPT32_GTICLF_ICLFSELC_0X10                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC8A */
#  define R_GPT32_GTICLF_ICLFSELC_0X11                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC8B */
#  define R_GPT32_GTICLF_ICLFSELC_0X12                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC9A */
#  define R_GPT32_GTICLF_ICLFSELC_0X13                    (0 << R_GPT32_GTICLF_ICLFSELC_SHIFT)  /* GTIOC9B */

#define R_GPT32_GTICLF_ICLFB_SHIFT                (16)  /* GTIOCnB Output Logical Operation Function Select */
#define R_GPT32_GTICLF_ICLFB_MASK                 0x70000
#  define R_GPT32_GTICLF_ICLFB_000                        (0 << R_GPT32_GTICLF_ICLFB_SHIFT)  /* B (no delay) */
#  define R_GPT32_GTICLF_ICLFB_001                        (1 << R_GPT32_GTICLF_ICLFB_SHIFT)  /* NOT B (no delay) */
#  define R_GPT32_GTICLF_ICLFB_010                        (2 << R_GPT32_GTICLF_ICLFB_SHIFT)  /* D (1PCLKD delay) */
#  define R_GPT32_GTICLF_ICLFB_011                        (3 << R_GPT32_GTICLF_ICLFB_SHIFT)  /* NOT D (1PCLKD delay) */
#  define R_GPT32_GTICLF_ICLFB_100                        (4 << R_GPT32_GTICLF_ICLFB_SHIFT)  /* B AND D (1PCLKD delay) */
#  define R_GPT32_GTICLF_ICLFB_101                        (5 << R_GPT32_GTICLF_ICLFB_SHIFT)  /* B OR D (1PCLKDn delay) */
#  define R_GPT32_GTICLF_ICLFB_110                        (6 << R_GPT32_GTICLF_ICLFB_SHIFT)  /* B EXOR D (1PCLKD delay) */
#  define R_GPT32_GTICLF_ICLFB_111                        (7 << R_GPT32_GTICLF_ICLFB_SHIFT)  /* B NOR D (1PCLKD delay) */

#define R_GPT32_GTICLF_ICLFSELD_SHIFT             (20)  /* Inter Channel Signal D Select */
#define R_GPT32_GTICLF_ICLFSELD_MASK              0x3f00000
#  define R_GPT32_GTICLF_ICLFSELD_0X00                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC0A */
#  define R_GPT32_GTICLF_ICLFSELD_0X01                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC0B */
#  define R_GPT32_GTICLF_ICLFSELD_0X02                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC1A */
#  define R_GPT32_GTICLF_ICLFSELD_0X03                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC1B */
#  define R_GPT32_GTICLF_ICLFSELD_0X04                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC2A */
#  define R_GPT32_GTICLF_ICLFSELD_0X05                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC2B */
#  define R_GPT32_GTICLF_ICLFSELD_0X06                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC3A */
#  define R_GPT32_GTICLF_ICLFSELD_0X07                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC3B */
#  define R_GPT32_GTICLF_ICLFSELD_0X08                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC4A */
#  define R_GPT32_GTICLF_ICLFSELD_0X09                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC4B */
#  define R_GPT32_GTICLF_ICLFSELD_0X0A                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC5A */
#  define R_GPT32_GTICLF_ICLFSELD_0X0B                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC5B */
#  define R_GPT32_GTICLF_ICLFSELD_0X0C                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC6A */
#  define R_GPT32_GTICLF_ICLFSELD_0X0D                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC6B */
#  define R_GPT32_GTICLF_ICLFSELD_0X0E                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC7A */
#  define R_GPT32_GTICLF_ICLFSELD_0X0F                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC7B */
#  define R_GPT32_GTICLF_ICLFSELD_0X10                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC8A */
#  define R_GPT32_GTICLF_ICLFSELD_0X11                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC8B */
#  define R_GPT32_GTICLF_ICLFSELD_0X12                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC9A */
#  define R_GPT32_GTICLF_ICLFSELD_0X13                    (0 << R_GPT32_GTICLF_ICLFSELD_SHIFT)  /* GTIOC9B */

/* GTPC Register bit definitions */
#define R_GPT32_GTPC_PCEN                         (1 << 0)  /* Period Count Function Enable */

#define R_GPT32_GTPC_ASTP                         (1 << 8)  /* Automatic Stop Function Enable */

#define R_GPT32_GTPC_PCNT_SHIFT                   (16)  /* Period Counter */
#define R_GPT32_GTPC_PCNT_MASK                    0xfff0000

/* GTSECSR Register bit definitions */
#define R_GPT32_GTSECSR_SECSEL0                   (1 << 0)  /* Channel 0 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT32_GTSECSR_SECSEL1                   (1 << 1)  /* Channel 1 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT32_GTSECSR_SECSEL2                   (1 << 2)  /* Channel 2 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT32_GTSECSR_SECSEL3                   (1 << 3)  /* Channel 3 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT32_GTSECSR_SECSEL4                   (1 << 4)  /* Channel 4 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT32_GTSECSR_SECSEL5                   (1 << 5)  /* Channel 5 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT32_GTSECSR_SECSEL10                  (1 << 10)  /* Channel 10 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT32_GTSECSR_SECSEL11                  (1 << 11)  /* Channel 11 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT32_GTSECSR_SECSEL12                  (1 << 12)  /* Channel 12 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT32_GTSECSR_SECSEL13                  (1 << 13)  /* Channel 13 Operation Enable Bit Simultaneous Control Channel Select */

/* GTSECR Register bit definitions */
#define R_GPT32_GTSECR_SBDCE                      (1 << 0)  /* GTCCR Register Buffer Operation Simultaneous Enable */

#define R_GPT32_GTSECR_SBDPE                      (1 << 1)  /* GTPR Register Buffer Operation Simultaneous Enable */

#define R_GPT32_GTSECR_SBDAE                      (1 << 2)  /* GTADTR Register Buffer Operation Simultaneous Enable */

#define R_GPT32_GTSECR_SBDCD                      (1 << 8)  /* GTCCR Register Buffer Operation Simultaneous Disable */

#define R_GPT32_GTSECR_SBDPD                      (1 << 9)  /* GTPR Register Buffer Operation Simultaneous Disable */

#define R_GPT32_GTSECR_SBDAD                      (1 << 10)  /* GTADTR Register Buffer Operation Simultaneous Disable */

#define R_GPT32_GTSECR_SPCE                       (1 << 16)  /* Period Count Function Simultaneous Enable */

#define R_GPT32_GTSECR_SPCD                       (1 << 24)  /* Period Count Function Simultaneous Disable */


/* Maximum number of channels */

#define GPT32_MAX_CHANNELS    8

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT32_H */

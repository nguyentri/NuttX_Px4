/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8e1/ra_gpt16.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_GPT16_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_GPT16_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPT16 Base Address */
#ifndef R_GPT16_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_GPT16_BASE           0x40322800
#else
#define R_GPT16_BASE           0x50322800
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_GPT16_CH_STRIDE    0x00000100
#define R_GPT16_CH_BASE(ch)   (R_GPT16_BASE + ((uint32_t)(ch) * R_GPT16_CH_STRIDE))

/* GPT16 Register Offsets */

#define R_GPT16_GTSTR_OFFSET                      0x00000004  /* General PWM Timer Software Start Register */
#define R_GPT16_GTSTP_OFFSET                      0x00000008  /* General PWM Timer Software Stop Register */
#define R_GPT16_GTCLR_OFFSET                      0x0000000c  /* General PWM Timer Software Clear Register */
#define R_GPT16_GTSSR_OFFSET                      0x00000010  /* General PWM Timer Start Source Select Register */
#define R_GPT16_GTPSR_OFFSET                      0x00000014  /* General PWM Timer Stop Source Select Register */
#define R_GPT16_GTCSR_OFFSET                      0x00000018  /* General PWM Timer Clear Source Select Register */
#define R_GPT16_GTUPSR_OFFSET                     0x0000001c  /* General PWM Timer Up Count Source Select Register */
#define R_GPT16_GTDNSR_OFFSET                     0x00000020  /* General PWM Timer Down Count Source Select Register */
#define R_GPT16_GTICASR_OFFSET                    0x00000024  /* General PWM Timer Input Capture Source Select Register A */
#define R_GPT16_GTICBSR_OFFSET                    0x00000028  /* General PWM Timer Input Capture Source Select Register B */
#define R_GPT16_GTCR_OFFSET                       0x0000002c  /* General PWM Timer Control Register */
#define R_GPT16_GTINTAD_OFFSET                    0x00000038  /* General PWM Timer Interrupt Output Setting Register */
#define R_GPT16_GTADTRA_OFFSET                    0x00000070  /* A/D Conversion Start Request Timing Register A */
#define R_GPT16_GTADTBRA_OFFSET                   0x00000074  /* A/D Conversion Start Request Timing Buffer Register A */
#define R_GPT16_GTADTDBRA_OFFSET                  0x00000078  /* A/D Conversion Start Request Timing Double-Buffer Register A */
#define R_GPT16_GTADTRB_OFFSET                    0x0000007c  /* A/D Conversion Start Request Timing Register B */
#define R_GPT16_GTADTBRB_OFFSET                   0x00000080  /* A/D Conversion Start Request Timing Buffer Register B */
#define R_GPT16_GTADTDBRB_OFFSET                  0x00000084  /* A/D Conversion Start Request Timing Double-Buffer Register B */
#define R_GPT16_GTADSMR_OFFSET                    0x000000a4  /* General PWM Timer A/D Conversion Start Request Signal Monitoring Register */
#define R_GPT16_GTICLF_OFFSET                     0x000000b8  /* General PWM Timer Inter Channel Logical Operation Function Setting Register */

/* GPT16 Register Addresses */

#define R_GPT16_GTSTR(n)                          (R_GPT16_CH_BASE(n) + R_GPT16_GTSTR_OFFSET)
#define R_GPT16_GTSTP(n)                          (R_GPT16_CH_BASE(n) + R_GPT16_GTSTP_OFFSET)
#define R_GPT16_GTCLR(n)                          (R_GPT16_CH_BASE(n) + R_GPT16_GTCLR_OFFSET)
#define R_GPT16_GTSSR(n)                          (R_GPT16_CH_BASE(n) + R_GPT16_GTSSR_OFFSET)
#define R_GPT16_GTPSR(n)                          (R_GPT16_CH_BASE(n) + R_GPT16_GTPSR_OFFSET)
#define R_GPT16_GTCSR(n)                          (R_GPT16_CH_BASE(n) + R_GPT16_GTCSR_OFFSET)
#define R_GPT16_GTUPSR(n)                         (R_GPT16_CH_BASE(n) + R_GPT16_GTUPSR_OFFSET)
#define R_GPT16_GTDNSR(n)                         (R_GPT16_CH_BASE(n) + R_GPT16_GTDNSR_OFFSET)
#define R_GPT16_GTICASR(n)                        (R_GPT16_CH_BASE(n) + R_GPT16_GTICASR_OFFSET)
#define R_GPT16_GTICBSR(n)                        (R_GPT16_CH_BASE(n) + R_GPT16_GTICBSR_OFFSET)
#define R_GPT16_GTCR(n)                           (R_GPT16_CH_BASE(n) + R_GPT16_GTCR_OFFSET)
#define R_GPT16_GTINTAD(n)                        (R_GPT16_CH_BASE(n) + R_GPT16_GTINTAD_OFFSET)
#define R_GPT16_GTADTRA(n)                        (R_GPT16_CH_BASE(n) + R_GPT16_GTADTRA_OFFSET)
#define R_GPT16_GTADTBRA(n)                       (R_GPT16_CH_BASE(n) + R_GPT16_GTADTBRA_OFFSET)
#define R_GPT16_GTADTDBRA(n)                      (R_GPT16_CH_BASE(n) + R_GPT16_GTADTDBRA_OFFSET)
#define R_GPT16_GTADTRB(n)                        (R_GPT16_CH_BASE(n) + R_GPT16_GTADTRB_OFFSET)
#define R_GPT16_GTADTBRB(n)                       (R_GPT16_CH_BASE(n) + R_GPT16_GTADTBRB_OFFSET)
#define R_GPT16_GTADTDBRB(n)                      (R_GPT16_CH_BASE(n) + R_GPT16_GTADTDBRB_OFFSET)
#define R_GPT16_GTADSMR(n)                        (R_GPT16_CH_BASE(n) + R_GPT16_GTADSMR_OFFSET)
#define R_GPT16_GTICLF(n)                         (R_GPT16_CH_BASE(n) + R_GPT16_GTICLF_OFFSET)

/* Register bit definitions */
/* GTSTR Register bit definitions */
#define R_GPT16_GTSTR_CSTRT0                      (1 << 0)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT16_GTSTR_CSTRT1                      (1 << 1)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT16_GTSTR_CSTRT2                      (1 << 2)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT16_GTSTR_CSTRT3                      (1 << 3)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT16_GTSTR_CSTRT4                      (1 << 4)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT16_GTSTR_CSTRT5                      (1 << 5)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT16_GTSTR_CSTRT6                      (1 << 6)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT16_GTSTR_CSTRT7                      (1 << 7)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT16_GTSTR_CSTRT8                      (1 << 8)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

#define R_GPT16_GTSTR_CSTRT9                      (1 << 9)  /* Channel n GTCNT Count Start (n : the same as bit position value) */

/* GTSTP Register bit definitions */
#define R_GPT16_GTSTP_CSTOP0                      (1 << 0)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT16_GTSTP_CSTOP1                      (1 << 1)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT16_GTSTP_CSTOP2                      (1 << 2)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT16_GTSTP_CSTOP3                      (1 << 3)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT16_GTSTP_CSTOP4                      (1 << 4)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT16_GTSTP_CSTOP5                      (1 << 5)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT16_GTSTP_CSTOP6                      (1 << 6)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT16_GTSTP_CSTOP7                      (1 << 7)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT16_GTSTP_CSTOP8                      (1 << 8)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

#define R_GPT16_GTSTP_CSTOP9                      (1 << 9)  /* Channel n GTCNT Count Stop (n : the same as bit position value) */

/* GTCLR Register bit definitions */
#define R_GPT16_GTCLR_CCLR0                       (1 << 0)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT16_GTCLR_CCLR1                       (1 << 1)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT16_GTCLR_CCLR2                       (1 << 2)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT16_GTCLR_CCLR3                       (1 << 3)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT16_GTCLR_CCLR4                       (1 << 4)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT16_GTCLR_CCLR5                       (1 << 5)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT16_GTCLR_CCLR6                       (1 << 6)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT16_GTCLR_CCLR7                       (1 << 7)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT16_GTCLR_CCLR8                       (1 << 8)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

#define R_GPT16_GTCLR_CCLR9                       (1 << 9)  /* Channel n GTCNT Count Clear (n : the same as bit position value) */

/* GTSSR Register bit definitions */
#define R_GPT16_GTSSR_SSGTRGAR                    (1 << 0)  /* GTETRGA Pin Rising Input Source Counter Start Enable */

#define R_GPT16_GTSSR_SSGTRGAF                    (1 << 1)  /* GTETRGA Pin Falling Input Source Counter Start Enable */

#define R_GPT16_GTSSR_SSGTRGBR                    (1 << 2)  /* GTETRGB Pin Rising Input Source Counter Start Enable */

#define R_GPT16_GTSSR_SSGTRGBF                    (1 << 3)  /* GTETRGB Pin Falling Input Source Counter Start Enable */

#define R_GPT16_GTSSR_SSGTRGCR                    (1 << 4)  /* GTETRGC Pin Rising Input Source Counter Start Enable */

#define R_GPT16_GTSSR_SSGTRGCF                    (1 << 5)  /* GTETRGC Pin Falling Input Source Counter Start Enable */

#define R_GPT16_GTSSR_SSGTRGDR                    (1 << 6)  /* GTETRGD Pin Rising Input Source Counter Start Enable */

#define R_GPT16_GTSSR_SSGTRGDF                    (1 << 7)  /* GTETRGD Pin Falling Input Source Counter Start Enable */

#define R_GPT16_GTSSR_SSCARBL                     (1 << 8)  /* GTIOCnA Pin Rising Input during GTIOCnB Value Low Source Counter Start Enable */

#define R_GPT16_GTSSR_SSCARBH                     (1 << 9)  /* GTIOCnA Pin Rising Input during GTIOCnB Value High Source Counter Start Enable */

#define R_GPT16_GTSSR_SSCAFBL                     (1 << 10)  /* GTIOCnA Pin Falling Input during GTIOCnB Value Low Source Counter Start Enable */

#define R_GPT16_GTSSR_SSCAFBH                     (1 << 11)  /* GTIOCnA Pin Falling Input during GTIOCnB Value High Source Counter Start Enable */

#define R_GPT16_GTSSR_SSCBRAL                     (1 << 12)  /* GTIOCnB Pin Rising Input during GTIOCnA Value Low Source Counter Start Enable */

#define R_GPT16_GTSSR_SSCBRAH                     (1 << 13)  /* GTIOCnB Pin Rising Input during GTIOCnA Value High Source Counter Start Enable */

#define R_GPT16_GTSSR_SSCBFAL                     (1 << 14)  /* GTIOCnB Pin Falling Input during GTIOCnA Value Low Source Counter Start Enable */

#define R_GPT16_GTSSR_SSCBFAH                     (1 << 15)  /* GTIOCnB Pin Falling Input during GTIOCnA Value High Source Counter Start Enable */

#define R_GPT16_GTSSR_SSELCA                      (1 << 16)  /* ELC_GPTA Event Source Counter Start Enable */

#define R_GPT16_GTSSR_SSELCB                      (1 << 17)  /* ELC_GPTB Event Source Counter Start Enable */

#define R_GPT16_GTSSR_SSELCC                      (1 << 18)  /* ELC_GPTC Event Source Counter Start Enable */

#define R_GPT16_GTSSR_SSELCD                      (1 << 19)  /* ELC_GPTD Event Source Counter Start Enable */

#define R_GPT16_GTSSR_SSELCE                      (1 << 20)  /* ELC_GPTE Event Source Counter Start Enable */

#define R_GPT16_GTSSR_SSELCF                      (1 << 21)  /* ELC_GPTF Event Source Counter Start Enable */

#define R_GPT16_GTSSR_SSELCG                      (1 << 22)  /* ELC_GPTG Event Source Counter Start Enable */

#define R_GPT16_GTSSR_SSELCH                      (1 << 23)  /* ELC_GPTH Event Source Counter Start Enable */

#define R_GPT16_GTSSR_CSTRT                       (1 << 31)  /* Software Source Counter Start Enable */

/* GTPSR Register bit definitions */
#define R_GPT16_GTPSR_PSGTRGAR                    (1 << 0)  /* GTETRGA Pin Rising Input Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSGTRGAF                    (1 << 1)  /* GTETRGA Pin Falling Input Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSGTRGBR                    (1 << 2)  /* GTETRGB Pin Rising Input Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSGTRGBF                    (1 << 3)  /* GTETRGB Pin Falling Input Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSGTRGCR                    (1 << 4)  /* GTETRGC Pin Rising Input Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSGTRGCF                    (1 << 5)  /* GTETRGC Pin Falling Input Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSGTRGDR                    (1 << 6)  /* GTETRGD Pin Rising Input Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSGTRGDF                    (1 << 7)  /* GTETRGD Pin Falling Input Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSCARBL                     (1 << 8)  /* GTIOCnA Pin Rising Input during GTIOCnB Value Low Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSCARBH                     (1 << 9)  /* GTIOCnA Pin Rising Input during GTIOCnB Value High Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSCAFBL                     (1 << 10)  /* GTIOCnA Pin Falling Input during GTIOCnB Value Low Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSCAFBH                     (1 << 11)  /* GTIOCnA Pin Falling Input during GTIOCnB Value High Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSCBRAL                     (1 << 12)  /* GTIOCnB Pin Rising Input during GTIOCnA Value Low Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSCBRAH                     (1 << 13)  /* GTIOCnB Pin Rising Input during GTIOCnA Value High Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSCBFAL                     (1 << 14)  /* GTIOCnB Pin Falling Input during GTIOCnA Value Low Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSCBFAH                     (1 << 15)  /* GTIOCnB Pin Falling Input during GTIOCnA Value High Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSELCA                      (1 << 16)  /* ELC_GPTA Event Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSELCB                      (1 << 17)  /* ELC_GPTB Event Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSELCC                      (1 << 18)  /* ELC_GPTC Event Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSELCD                      (1 << 19)  /* ELC_GPTD Event Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSELCE                      (1 << 20)  /* ELC_GPTE Event Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSELCF                      (1 << 21)  /* ELC_GPTF Event Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSELCG                      (1 << 22)  /* ELC_GPTG Event Source Counter Stop Enable */

#define R_GPT16_GTPSR_PSELCH                      (1 << 23)  /* ELC_GPTH Event Source Counter Stop Enable */

#define R_GPT16_GTPSR_CSTOP                       (1 << 31)  /* Software Source Counter Stop Enable */

/* GTCSR Register bit definitions */
#define R_GPT16_GTCSR_CSGTRGAR                    (1 << 0)  /* GTETRGA Pin Rising Input Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSGTRGAF                    (1 << 1)  /* GTETRGA Pin Falling Input Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSGTRGBR                    (1 << 2)  /* GTETRGB Pin Rising Input Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSGTRGBF                    (1 << 3)  /* GTETRGB Pin Falling Input Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSGTRGCR                    (1 << 4)  /* GTETRGC Pin Rising Input Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSGTRGCF                    (1 << 5)  /* GTETRGC Pin Falling Input Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSGTRGDR                    (1 << 6)  /* GTETRGD Pin Rising Input Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSGTRGDF                    (1 << 7)  /* GTETRGD Pin Falling Input Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSCARBL                     (1 << 8)  /* GTIOCnA Pin Rising Input during GTIOCnB Value Low Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSCARBH                     (1 << 9)  /* GTIOCnA Pin Rising Input during GTIOCnB Value High Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSCAFBL                     (1 << 10)  /* GTIOCnA Pin Falling Input during GTIOCnB Value Low Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSCAFBH                     (1 << 11)  /* GTIOCnA Pin Falling Input during GTIOCnB Value High Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSCBRAL                     (1 << 12)  /* GTIOCnB Pin Rising Input during GTIOCnA Value Low Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSCBRAH                     (1 << 13)  /* GTIOCnB Pin Rising Input during GTIOCnA Value High Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSCBFAL                     (1 << 14)  /* GTIOCnB Pin Falling Input during GTIOCnA Value Low Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSCBFAH                     (1 << 15)  /* GTIOCnB Pin Falling Input during GTIOCnA Value High Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSELCA                      (1 << 16)  /* ELC_GPTA Event Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSELCB                      (1 << 17)  /* ELC_GPTB Event Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSELCC                      (1 << 18)  /* ELC_GPTC Event Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSELCD                      (1 << 19)  /* ELC_GPTD Event Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSELCE                      (1 << 20)  /* ELC_GPTE Event Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSELCF                      (1 << 21)  /* ELC_GPTF Event Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSELCG                      (1 << 22)  /* ELC_GPTG Event Source Counter Clear Enable */

#define R_GPT16_GTCSR_CSELCH                      (1 << 23)  /* ELC_GPTH Event Source Counter Clear Enable */

#define R_GPT16_GTCSR_CCLR                        (1 << 31)  /* Software Source Counter Clear Enable */

/* GTUPSR Register bit definitions */
#define R_GPT16_GTUPSR_USGTRGAR                   (1 << 0)  /* GTETRGA Pin Rising Input Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USGTRGAF                   (1 << 1)  /* GTETRGA Pin Falling Input Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USGTRGBR                   (1 << 2)  /* GTETRGB Pin Rising Input Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USGTRGBF                   (1 << 3)  /* GTETRGB Pin Falling Input Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USGTRGCR                   (1 << 4)  /* GTETRGC Pin Rising Input Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USGTRGCF                   (1 << 5)  /* GTETRGC Pin Falling Input Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USGTRGDR                   (1 << 6)  /* GTETRGD Pin Rising Input Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USGTRGDF                   (1 << 7)  /* GTETRGD Pin Falling Input Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USCARBL                    (1 << 8)  /* GTIOCnA Pin Rising Input during GTIOCnB Value Low Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USCARBH                    (1 << 9)  /* GTIOCnA Pin Rising Input during GTIOCnB Value High Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USCAFBL                    (1 << 10)  /* GTIOCnA Pin Falling Input during GTIOCnB Value Low Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USCAFBH                    (1 << 11)  /* GTIOCnA Pin Falling Input during GTIOCnB Value High Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USCBRAL                    (1 << 12)  /* GTIOCnB Pin Rising Input during GTIOCnA Value Low Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USCBRAH                    (1 << 13)  /* GTIOCnB Pin Rising Input during GTIOCnA Value High Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USCBFAL                    (1 << 14)  /* GTIOCnB Pin Falling Input during GTIOCnA Value Low Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USCBFAH                    (1 << 15)  /* GTIOCnB Pin Falling Input during GTIOCnA Value High Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USELCA                     (1 << 16)  /* ELC_GPTA Event Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USELCB                     (1 << 17)  /* ELC_GPTB Event Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USELCC                     (1 << 18)  /* ELC_GPTC Event Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USELCD                     (1 << 19)  /* ELC_GPTD Event Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USELCE                     (1 << 20)  /* ELC_GPTE Event Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USELCF                     (1 << 21)  /* ELC_GPTF Event Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USELCG                     (1 << 22)  /* ELC_GPTG Event Source Counter Count Up Enable */

#define R_GPT16_GTUPSR_USELCH                     (1 << 23)  /* ELC_GPTH Event Source Counter Count Up Enable */

/* GTDNSR Register bit definitions */
#define R_GPT16_GTDNSR_DSGTRGAR                   (1 << 0)  /* GTETRGA Pin Rising Input Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSGTRGAF                   (1 << 1)  /* GTETRGA Pin Falling Input Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSGTRGBR                   (1 << 2)  /* GTETRGB Pin Rising Input Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSGTRGBF                   (1 << 3)  /* GTETRGB Pin Falling Input Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSGTRGCR                   (1 << 4)  /* GTETRGC Pin Rising Input Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSGTRGCF                   (1 << 5)  /* GTETRGC Pin Falling Input Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSGTRGDR                   (1 << 6)  /* GTETRGD Pin Rising Input Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSGTRGDF                   (1 << 7)  /* GTETRGD Pin Falling Input Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSCARBL                    (1 << 8)  /* GTIOCnA Pin Rising Input during GTIOCnB Value Low Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSCARBH                    (1 << 9)  /* GTIOCnA Pin Rising Input during GTIOCnB Value High Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSCAFBL                    (1 << 10)  /* GTIOCnA Pin Falling Input during GTIOCnB Value Low Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSCAFBH                    (1 << 11)  /* GTIOCnA Pin Falling Input during GTIOCnB Value High Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSCBRAL                    (1 << 12)  /* GTIOCnB Pin Rising Input during GTIOCnA Value Low Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSCBRAH                    (1 << 13)  /* GTIOCnB Pin Rising Input during GTIOCnA Value High Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSCBFAL                    (1 << 14)  /* GTIOCnB Pin Falling Input during GTIOCnA Value Low Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSCBFAH                    (1 << 15)  /* GTIOCnB Pin Falling Input during GTIOCnA Value High Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSELCA                     (1 << 16)  /* ELC_GPTA Event Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSELCB                     (1 << 17)  /* ELC_GPTB Event Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSELCC                     (1 << 18)  /* ELC_GPTC Event Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSELCD                     (1 << 19)  /* ELC_GPTD Event Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSELCE                     (1 << 20)  /* ELC_GPTE Event Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSELCF                     (1 << 21)  /* ELC_GPTF Event Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSELCG                     (1 << 22)  /* ELC_GPTG Event Source Counter Count Down Enable */

#define R_GPT16_GTDNSR_DSELCH                     (1 << 23)  /* ELC_GPTF Event Source Counter Count Down Enable */

/* GTICASR Register bit definitions */
#define R_GPT16_GTICASR_ASGTRGAR                  (1 << 0)  /* GTETRGA Pin Rising Input Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASGTRGAF                  (1 << 1)  /* GTETRGA Pin Falling Input Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASGTRGBR                  (1 << 2)  /* GTETRGB Pin Rising Input Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASGTRGBF                  (1 << 3)  /* GTETRGB Pin Falling Input Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASGTRGCR                  (1 << 4)  /* GTETRGC Pin Rising Input Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASGTRGCF                  (1 << 5)  /* GTETRGC Pin Falling Input Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASGTRGDR                  (1 << 6)  /* GTETRGD Pin Rising Input Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASGTRGDF                  (1 << 7)  /* GTETRGD Pin Falling Input Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASCARBL                   (1 << 8)  /* GTIOCnA Pin Rising Input during GTIOCnB Value Low Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASCARBH                   (1 << 9)  /* GTIOCnA Pin Rising Input during GTIOCnB Value High Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASCAFBL                   (1 << 10)  /* GTIOCnA Pin Falling Input during GTIOCnB Value Low Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASCAFBH                   (1 << 11)  /* GTIOCnA Pin Falling Input during GTIOCnB Value High Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASCBRAL                   (1 << 12)  /* GTIOCnB Pin Rising Input during GTIOCnA Value Low Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASCBRAH                   (1 << 13)  /* GTIOCnB Pin Rising Input during GTIOCnA Value High Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASCBFAL                   (1 << 14)  /* GTIOCnB Pin Falling Input during GTIOCnA Value Low Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASCBFAH                   (1 << 15)  /* GTIOCnB Pin Falling Input during GTIOCnA Value High Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASELCA                    (1 << 16)  /* ELC_GPTA Event Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASELCB                    (1 << 17)  /* ELC_GPTB Event Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASELCC                    (1 << 18)  /* ELC_GPTC Event Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASELCD                    (1 << 19)  /* ELC_GPTD Event Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASELCE                    (1 << 20)  /* ELC_GPTE Event Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASELCF                    (1 << 21)  /* ELC_GPTF Event Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASELCG                    (1 << 22)  /* ELC_GPTG Event Source GTCCRA Input Capture Enable */

#define R_GPT16_GTICASR_ASELCH                    (1 << 23)  /* ELC_GPTH Event Source GTCCRA Input Capture Enable */

/* GTICBSR Register bit definitions */
#define R_GPT16_GTICBSR_BSGTRGAR                  (1 << 0)  /* GTETRGA Pin Rising Input Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSGTRGAF                  (1 << 1)  /* GTETRGA Pin Falling Input Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSGTRGBR                  (1 << 2)  /* GTETRGB Pin Rising Input Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSGTRGBF                  (1 << 3)  /* GTETRGB Pin Falling Input Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSGTRGCR                  (1 << 4)  /* GTETRGC Pin Rising Input Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSGTRGCF                  (1 << 5)  /* GTETRGC Pin Falling Input Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSGTRGDR                  (1 << 6)  /* GTETRGD Pin Rising Input Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSGTRGDF                  (1 << 7)  /* GTETRGD Pin Falling Input Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSCARBL                   (1 << 8)  /* GTIOCnA Pin Rising Input during GTIOCnB Value Low Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSCARBH                   (1 << 9)  /* GTIOCnA Pin Rising Input during GTIOCnB Value High Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSCAFBL                   (1 << 10)  /* GTIOCnA Pin Falling Input during GTIOCnB Value Low Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSCAFBH                   (1 << 11)  /* GTIOCnA Pin Falling Input during GTIOCnB Value High Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSCBRAL                   (1 << 12)  /* GTIOCnB Pin Rising Input during GTIOCnA Value Low Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSCBRAH                   (1 << 13)  /* GTIOCnB Pin Rising Input during GTIOCnA Value High Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSCBFAL                   (1 << 14)  /* GTIOCnB Pin Falling Input during GTIOCnA Value Low Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSCBFAH                   (1 << 15)  /* GTIOCnB Pin Falling Input during GTIOCnA Value High Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSELCA                    (1 << 16)  /* ELC_GPTA Event Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSELCB                    (1 << 17)  /* ELC_GPTB Event Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSELCC                    (1 << 18)  /* ELC_GPTC Event Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSELCD                    (1 << 19)  /* ELC_GPTD Event Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSELCE                    (1 << 20)  /* ELC_GPTE Event Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSELCF                    (1 << 21)  /* ELC_GPTF Event Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSELCG                    (1 << 22)  /* ELC_GPTG Event Source GTCCRB Input Capture Enable */

#define R_GPT16_GTICBSR_BSELCH                    (1 << 23)  /* ELC_GPTH Event Source GTCCRB Input Capture Enable */

/* GTCR Register bit definitions */
#define R_GPT16_GTCR_CST                          (1 << 0)  /* Count Start */

#define R_GPT16_GTCR_MD_SHIFT                     (16)  /* Mode Select */
#define R_GPT16_GTCR_MD_MASK                      0x70000
#  define R_GPT16_GTCR_MD_000                             (0 << R_GPT16_GTCR_MD_SHIFT)  /* Saw-wave PWM mode (single buffer or double buffer possible) */
#  define R_GPT16_GTCR_MD_001                             (1 << R_GPT16_GTCR_MD_SHIFT)  /* Saw-wave one-shot pulse mode (fixed buffer operation) */
#  define R_GPT16_GTCR_MD_010                             (2 << R_GPT16_GTCR_MD_SHIFT)  /* Setting prohibited */
#  define R_GPT16_GTCR_MD_011                             (3 << R_GPT16_GTCR_MD_SHIFT)  /* Setting prohibited */
#  define R_GPT16_GTCR_MD_100                             (4 << R_GPT16_GTCR_MD_SHIFT)  /* Triangle-wave PWM mode 1 (32-bit transfer at trough) (single buffer or double buffer is possible) */
#  define R_GPT16_GTCR_MD_101                             (5 << R_GPT16_GTCR_MD_SHIFT)  /* Triangle-wave PWM mode 2 (32-bit transfer at crest and trough) (single buffer or double buffer is possible) */
#  define R_GPT16_GTCR_MD_110                             (6 << R_GPT16_GTCR_MD_SHIFT)  /* Triangle-wave PWM mode 3 (64-bit transfer at trough) (fixed buffer operation) */
#  define R_GPT16_GTCR_MD_111                             (7 << R_GPT16_GTCR_MD_SHIFT)  /* Setting prohibited */

#define R_GPT16_GTCR_TPCS_SHIFT                   (23)  /* Timer Prescaler Select */
#define R_GPT16_GTCR_TPCS_MASK                    0x7800000
#  define R_GPT16_GTCR_TPCS_0X0                           (0 << R_GPT16_GTCR_TPCS_SHIFT)  /* PCLKD/1  */
#  define R_GPT16_GTCR_TPCS_0X1                           (1 << R_GPT16_GTCR_TPCS_SHIFT)  /* PCLKD/2  */
#  define R_GPT16_GTCR_TPCS_0X2                           (2 << R_GPT16_GTCR_TPCS_SHIFT)  /* PCLKD/4  */
#  define R_GPT16_GTCR_TPCS_0X3                           (3 << R_GPT16_GTCR_TPCS_SHIFT)  /* PCLKD/8  */
#  define R_GPT16_GTCR_TPCS_0X4                           (4 << R_GPT16_GTCR_TPCS_SHIFT)  /* PCLKD/16  */
#  define R_GPT16_GTCR_TPCS_0X5                           (5 << R_GPT16_GTCR_TPCS_SHIFT)  /* PCLKD/32  */
#  define R_GPT16_GTCR_TPCS_0X6                           (6 << R_GPT16_GTCR_TPCS_SHIFT)  /* PCLKD/64  */
#  define R_GPT16_GTCR_TPCS_0X7                           (7 << R_GPT16_GTCR_TPCS_SHIFT)  /* Setting prohibited */
#  define R_GPT16_GTCR_TPCS_0X8                           (8 << R_GPT16_GTCR_TPCS_SHIFT)  /* PCLKD/256  */
#  define R_GPT16_GTCR_TPCS_0X9                           (9 << R_GPT16_GTCR_TPCS_SHIFT)  /* Setting prohibited */
#  define R_GPT16_GTCR_TPCS_0XA                           (10 << R_GPT16_GTCR_TPCS_SHIFT)  /* PCLKD/1024  */
#  define R_GPT16_GTCR_TPCS_0XB                           (11 << R_GPT16_GTCR_TPCS_SHIFT)  /* Setting prohibited */
#  define R_GPT16_GTCR_TPCS_0XC                           (12 << R_GPT16_GTCR_TPCS_SHIFT)  /* GTETRGA (Via the POEG) */
#  define R_GPT16_GTCR_TPCS_0XD                           (13 << R_GPT16_GTCR_TPCS_SHIFT)  /* GTETRGB (Via the POEG) */
#  define R_GPT16_GTCR_TPCS_0XE                           (14 << R_GPT16_GTCR_TPCS_SHIFT)  /* GTETRGC (Via the POEG) */
#  define R_GPT16_GTCR_TPCS_0XF                           (15 << R_GPT16_GTCR_TPCS_SHIFT)  /* GTETRGD (Via the POEG) */

/* GTINTAD Register bit definitions */
#define R_GPT16_GTINTAD_GRP_SHIFT                 (24)  /* Output Disable Source Select */
#define R_GPT16_GTINTAD_GRP_MASK                  0x3000000
#  define R_GPT16_GTINTAD_GRP_00                          (0 << R_GPT16_GTINTAD_GRP_SHIFT)  /* Group A output disable request is selected */
#  define R_GPT16_GTINTAD_GRP_01                          (1 << R_GPT16_GTINTAD_GRP_SHIFT)  /* Group B output disable request is selected */
#  define R_GPT16_GTINTAD_GRP_10                          (2 << R_GPT16_GTINTAD_GRP_SHIFT)  /* Group C output disable request is selected */
#  define R_GPT16_GTINTAD_GRP_11                          (3 << R_GPT16_GTINTAD_GRP_SHIFT)  /* Group D output disable request is selected */

#define R_GPT16_GTINTAD_GRPABH                    (1 << 29)  /* Same Time Output Level High Disable Request Enable */

#define R_GPT16_GTINTAD_GRPABL                    (1 << 30)  /* Same Time Output Level Low Disable Request Enable */

/* GTADSMR Register bit definitions */
#define R_GPT16_GTADSMR_ADSMS0_SHIFT              (0)  /* A/D Conversion Start Request Signal Monitor 0 Selection */
#define R_GPT16_GTADSMR_ADSMS0_MASK               0x3
#  define R_GPT16_GTADSMR_ADSMS0_00                       (0 << R_GPT16_GTADSMR_ADSMS0_SHIFT)  /* A/D conversion start request signal generated by the GTADTRA register during up-counting. */
#  define R_GPT16_GTADSMR_ADSMS0_01                       (1 << R_GPT16_GTADSMR_ADSMS0_SHIFT)  /* A/D conversion start request signal generated by the GTADTRA register during down-counting. */
#  define R_GPT16_GTADSMR_ADSMS0_10                       (2 << R_GPT16_GTADSMR_ADSMS0_SHIFT)  /* A/D conversion start request signal generated by the GTADTRB register during up-counting. */
#  define R_GPT16_GTADSMR_ADSMS0_11                       (3 << R_GPT16_GTADSMR_ADSMS0_SHIFT)  /* A/D conversion start request signal generated by the GTADTRB register during down-counting. */

#define R_GPT16_GTADSMR_ADSMEN0                   (1 << 8)  /* A/D Conversion Start Request Signal Monitor 0 Output Enabling */

#define R_GPT16_GTADSMR_ADSMS1_SHIFT              (16)  /* A/D Conversion Start Request Signal Monitor 1 Selection */
#define R_GPT16_GTADSMR_ADSMS1_MASK               0x30000
#  define R_GPT16_GTADSMR_ADSMS1_00                       (0 << R_GPT16_GTADSMR_ADSMS1_SHIFT)  /* A/D conversion start request signal generated by the GTADTRA register during up-counting. */
#  define R_GPT16_GTADSMR_ADSMS1_01                       (1 << R_GPT16_GTADSMR_ADSMS1_SHIFT)  /* A/D conversion start request signal generated by the GTADTRA register during down-counting. */
#  define R_GPT16_GTADSMR_ADSMS1_10                       (2 << R_GPT16_GTADSMR_ADSMS1_SHIFT)  /* A/D conversion start request signal generated by the GTADTRB register during up-counting. */
#  define R_GPT16_GTADSMR_ADSMS1_11                       (3 << R_GPT16_GTADSMR_ADSMS1_SHIFT)  /* A/D conversion start request signal generated by the GTADTRB register during down-counting. */

#define R_GPT16_GTADSMR_ADSMEN1                   (1 << 24)  /* A/D Conversion Start Request Signal Monitor 1 Output Enabling */

/* GTICLF Register bit definitions */
#define R_GPT16_GTICLF_ICLFA_SHIFT                (0)  /* GTIOCnA Output Logical Operation Function Select */
#define R_GPT16_GTICLF_ICLFA_MASK                 0x7
#  define R_GPT16_GTICLF_ICLFA_000                        (0 << R_GPT16_GTICLF_ICLFA_SHIFT)  /* A (no delay) */
#  define R_GPT16_GTICLF_ICLFA_001                        (1 << R_GPT16_GTICLF_ICLFA_SHIFT)  /* NOT A (no delay) */
#  define R_GPT16_GTICLF_ICLFA_010                        (2 << R_GPT16_GTICLF_ICLFA_SHIFT)  /* C (1PCLKD delay) */
#  define R_GPT16_GTICLF_ICLFA_011                        (3 << R_GPT16_GTICLF_ICLFA_SHIFT)  /* NOT C (1PCLKD delay) */
#  define R_GPT16_GTICLF_ICLFA_100                        (4 << R_GPT16_GTICLF_ICLFA_SHIFT)  /* A AND C (1PCLKD delay) */
#  define R_GPT16_GTICLF_ICLFA_101                        (5 << R_GPT16_GTICLF_ICLFA_SHIFT)  /* A OR C (1PCLKD delay) */
#  define R_GPT16_GTICLF_ICLFA_110                        (6 << R_GPT16_GTICLF_ICLFA_SHIFT)  /* A EXOR C (1PCLKD delay) */
#  define R_GPT16_GTICLF_ICLFA_111                        (7 << R_GPT16_GTICLF_ICLFA_SHIFT)  /* A NOR C (1PCLKD delay) */

#define R_GPT16_GTICLF_ICLFSELC_SHIFT             (4)  /* Inter Channel Signal C Select */
#define R_GPT16_GTICLF_ICLFSELC_MASK              0x3f0
#  define R_GPT16_GTICLF_ICLFSELC_0X00                    (0 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC0A */
#  define R_GPT16_GTICLF_ICLFSELC_0X01                    (1 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC0B */
#  define R_GPT16_GTICLF_ICLFSELC_0X02                    (2 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC1A */
#  define R_GPT16_GTICLF_ICLFSELC_0X03                    (3 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC1B */
#  define R_GPT16_GTICLF_ICLFSELC_0X04                    (4 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC2A */
#  define R_GPT16_GTICLF_ICLFSELC_0X05                    (5 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC2B */
#  define R_GPT16_GTICLF_ICLFSELC_0X06                    (6 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC3A */
#  define R_GPT16_GTICLF_ICLFSELC_0X07                    (7 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC3B */
#  define R_GPT16_GTICLF_ICLFSELC_0X08                    (8 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC4A */
#  define R_GPT16_GTICLF_ICLFSELC_0X09                    (9 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC4B */
#  define R_GPT16_GTICLF_ICLFSELC_0X0A                    (10 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC5A */
#  define R_GPT16_GTICLF_ICLFSELC_0X0B                    (11 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC5B */
#  define R_GPT16_GTICLF_ICLFSELC_0X0C                    (12 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC6A */
#  define R_GPT16_GTICLF_ICLFSELC_0X0D                    (13 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC6B */
#  define R_GPT16_GTICLF_ICLFSELC_0X0E                    (14 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC7A */
#  define R_GPT16_GTICLF_ICLFSELC_0X0F                    (15 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC7B */
#  define R_GPT16_GTICLF_ICLFSELC_0X10                    (16 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC8A */
#  define R_GPT16_GTICLF_ICLFSELC_0X11                    (17 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC8B */
#  define R_GPT16_GTICLF_ICLFSELC_0X12                    (18 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC9A */
#  define R_GPT16_GTICLF_ICLFSELC_0X13                    (19 << R_GPT16_GTICLF_ICLFSELC_SHIFT)  /* GTIOC9B */

#define R_GPT16_GTICLF_ICLFB_SHIFT                (16)  /* GTIOCnB Output Logical Operation Function Select */
#define R_GPT16_GTICLF_ICLFB_MASK                 0x70000
#  define R_GPT16_GTICLF_ICLFB_000                        (0 << R_GPT16_GTICLF_ICLFB_SHIFT)  /* B (no delay) */
#  define R_GPT16_GTICLF_ICLFB_001                        (1 << R_GPT16_GTICLF_ICLFB_SHIFT)  /* NOT B (no delay) */
#  define R_GPT16_GTICLF_ICLFB_010                        (2 << R_GPT16_GTICLF_ICLFB_SHIFT)  /* D (1PCLKD delay) */
#  define R_GPT16_GTICLF_ICLFB_011                        (3 << R_GPT16_GTICLF_ICLFB_SHIFT)  /* NOT D (1PCLKD delay) */
#  define R_GPT16_GTICLF_ICLFB_100                        (4 << R_GPT16_GTICLF_ICLFB_SHIFT)  /* B AND D (1PCLKD delay) */
#  define R_GPT16_GTICLF_ICLFB_101                        (5 << R_GPT16_GTICLF_ICLFB_SHIFT)  /* B OR D (1PCLKDn delay) */
#  define R_GPT16_GTICLF_ICLFB_110                        (6 << R_GPT16_GTICLF_ICLFB_SHIFT)  /* B EXOR D (1PCLKD delay) */
#  define R_GPT16_GTICLF_ICLFB_111                        (7 << R_GPT16_GTICLF_ICLFB_SHIFT)  /* B NOR D (1PCLKD delay) */

#define R_GPT16_GTICLF_ICLFSELD_SHIFT             (20)  /* Inter Channel Signal D Select */
#define R_GPT16_GTICLF_ICLFSELD_MASK              0x3f00000
#  define R_GPT16_GTICLF_ICLFSELD_0X00                    (0 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC0A */
#  define R_GPT16_GTICLF_ICLFSELD_0X01                    (1 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC0B */
#  define R_GPT16_GTICLF_ICLFSELD_0X02                    (2 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC1A */
#  define R_GPT16_GTICLF_ICLFSELD_0X03                    (3 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC1B */
#  define R_GPT16_GTICLF_ICLFSELD_0X04                    (4 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC2A */
#  define R_GPT16_GTICLF_ICLFSELD_0X05                    (5 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC2B */
#  define R_GPT16_GTICLF_ICLFSELD_0X06                    (6 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC3A */
#  define R_GPT16_GTICLF_ICLFSELD_0X07                    (7 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC3B */
#  define R_GPT16_GTICLF_ICLFSELD_0X08                    (8 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC4A */
#  define R_GPT16_GTICLF_ICLFSELD_0X09                    (9 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC4B */
#  define R_GPT16_GTICLF_ICLFSELD_0X0A                    (10 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC5A */
#  define R_GPT16_GTICLF_ICLFSELD_0X0B                    (11 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC5B */
#  define R_GPT16_GTICLF_ICLFSELD_0X0C                    (12 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC6A */
#  define R_GPT16_GTICLF_ICLFSELD_0X0D                    (13 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC6B */
#  define R_GPT16_GTICLF_ICLFSELD_0X0E                    (14 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC7A */
#  define R_GPT16_GTICLF_ICLFSELD_0X0F                    (15 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC7B */
#  define R_GPT16_GTICLF_ICLFSELD_0X10                    (16 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC8A */
#  define R_GPT16_GTICLF_ICLFSELD_0X11                    (17 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC8B */
#  define R_GPT16_GTICLF_ICLFSELD_0X12                    (18 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC9A */
#  define R_GPT16_GTICLF_ICLFSELD_0X13                    (19 << R_GPT16_GTICLF_ICLFSELD_SHIFT)  /* GTIOC9B */


/* Maximum number of channels */

#define GPT16_MAX_CHANNELS    6

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_GPT16_H */

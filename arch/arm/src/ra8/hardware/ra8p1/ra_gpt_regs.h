/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_gpt_regs.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_REGS_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_REGS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GTWP Register bit definitions */
#define GPT_GTWP_PRKEY                            (0xa500 << 8)  /* Write protect key */
#define GPT_GTWP_WP                               (1 << 0)       /* Write protection enable */
#define GPT_GTWP_CMNWP                            (1 << 4)       /* Common register write protect */

/* GTCR Register bit definitions */
#define GPT_GTCR_CST                              (1 << 0)       /* Count start */
#define GPT_GTCR_MD_SHIFT                         (1)            /* Count mode shift */
#define GPT_GTCR_MD_MASK                          (0x7 << GPT_GTCR_MD_SHIFT)
#define GPT_GTCR_MD_SAW_WAVE_UP                   (0 << GPT_GTCR_MD_SHIFT)
#define GPT_GTCR_MD_SAW_WAVE_DN                   (1 << GPT_GTCR_MD_SHIFT)
#define GPT_GTCR_MD_TRIANGULAR_WAVE               (2 << GPT_GTCR_MD_SHIFT)

#define GPT_GTCR_TPCS_SHIFT                       (4)            /* Timer prescaler shift */
#define GPT_GTCR_TPCS_MASK                        (0x7 << GPT_GTCR_TPCS_SHIFT)
#define GPT_GTCR_TPCS_PCLKD_1                     (0 << GPT_GTCR_TPCS_SHIFT) /* Prescaler = 1 */
#define GPT_GTCR_TPCS_PCLKD_4                     (1 << GPT_GTCR_TPCS_SHIFT) /* Prescaler = 4 */
#define GPT_GTCR_TPCS_PCLKD_16                    (2 << GPT_GTCR_TPCS_SHIFT) /* Prescaler = 16 */
#define GPT_GTCR_TPCS_PCLKD_64                    (3 << GPT_GTCR_TPCS_SHIFT) /* Prescaler = 64 */
#define GPT_GTCR_TPCS_PCLKD_256                   (4 << GPT_GTCR_TPCS_SHIFT) /* Prescaler = 256 */
#define GPT_GTCR_TPCS_PCLKD_1024                  (5 << GPT_GTCR_TPCS_SHIFT) /* Prescaler = 1024 */

/* GTIOR Register bit definitions */
#define GPT_GTIOR_GTIOA_SHIFT                     (0)
#define GPT_GTIOR_GTIOA_MASK                      (0xf << GPT_GTIOR_GTIOA_SHIFT)
#define GPT_GTIOR_GTIOA_INITIAL_LOW               (0 << GPT_GTIOR_GTIOA_SHIFT) /* Initial low, no change */
#define GPT_GTIOR_GTIOA_INITIAL_HIGH              (1 << GPT_GTIOR_GTIOA_SHIFT) /* Initial high, no change */
#define GPT_GTIOR_GTIOA_LOW_ON_CMP                (4 << GPT_GTIOR_GTIOA_SHIFT) /* Low on match, high on period */
#define GPT_GTIOR_GTIOA_HIGH_ON_CMP               (5 << GPT_GTIOR_GTIOA_SHIFT) /* High on match, low on period */

#define GPT_GTIOR_GTIOB_SHIFT                     (8)
#define GPT_GTIOR_GTIOB_MASK                      (0xf << GPT_GTIOR_GTIOB_SHIFT)
#define GPT_GTIOR_GTIOB_INITIAL_LOW               (0 << GPT_GTIOR_GTIOB_SHIFT) /* Initial low, no change */
#define GPT_GTIOR_GTIOB_INITIAL_HIGH              (1 << GPT_GTIOR_GTIOB_SHIFT) /* Initial high, no change */
#define GPT_GTIOR_GTIOB_LOW_ON_CMP                (4 << GPT_GTIOR_GTIOB_SHIFT) /* Low on match, high on period */
#define GPT_GTIOR_GTIOB_HIGH_ON_CMP               (5 << GPT_GTIOR_GTIOB_SHIFT) /* High on match, low on period */

/* GTBER Register bit definitions (Buffer Enable Register) */
#define GPT_GTBER_CCRA                            (1 << 16)
#define GPT_GTBER_CCRB                            (1 << 17)
#define GPT_GTBER_PR                              (1 << 18)

/* GTST Register bit definitions (Status Register) */
#define GPT_GTST_ADTRAUEN                         (1 << 16) /* A/D Start Request Active */
#define GPT_GTST_ADTRBUEN                         (1 << 17) /* A/D Start Request Active */
#define GPT_GTST_ADTRADEN                         (1 << 20) /* A/D Start Request Active */
#define GPT_GTST_ADTRBDEN                         (1 << 21) /* A/D Start Request Active */

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_REGS_H */

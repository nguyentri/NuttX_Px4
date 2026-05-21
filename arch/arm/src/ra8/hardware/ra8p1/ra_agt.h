/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_agt.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_AGT_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_AGT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* AGT Base Address */
#ifndef R_AGT_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_AGT_BASE           0x40221000
#else
#define R_AGT_BASE           0x50221000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_AGT_CH_STRIDE    0x00000100
#define R_AGT_CH_BASE(ch)   (R_AGT_BASE + ((uint32_t)(ch) * R_AGT_CH_STRIDE))

/* AGT Register Offsets */

#define R_AGT_AGT_OFFSET                          0x00000000  /* AGT Counter Register */
#define R_AGT_AGTCMA_OFFSET                       0x00000002  /* AGT Compare Match A Register */
#define R_AGT_AGTCMB_OFFSET                       0x00000004  /* AGT Compare Match B Register */
#define R_AGT_AGTCR_OFFSET                        0x00000008  /* AGT Control Register */
#define R_AGT_AGTMR1_OFFSET                       0x00000009  /* AGT Mode Register 1 */
#define R_AGT_AGTMR2_OFFSET                       0x0000000a  /* AGT Mode Register 2 */
#define R_AGT_AGTIOC_OFFSET                       0x0000000c  /* AGT I/O Control Register */
#define R_AGT_AGTISR_OFFSET                       0x0000000d  /* AGT Event Pin Select Register */
#define R_AGT_AGTCMSR_OFFSET                      0x0000000e  /* AGT Compare Match Function Select Register */
#define R_AGT_AGTIOSEL_OFFSET                     0x0000000f  /* AGT Pin Select Register */

/* AGT Register Addresses */

#define R_AGT_AGT(n)                              (R_AGT_CH_BASE(n) + R_AGT_AGT_OFFSET)
#define R_AGT_AGTCMA(n)                           (R_AGT_CH_BASE(n) + R_AGT_AGTCMA_OFFSET)
#define R_AGT_AGTCMB(n)                           (R_AGT_CH_BASE(n) + R_AGT_AGTCMB_OFFSET)
#define R_AGT_AGTCR(n)                            (R_AGT_CH_BASE(n) + R_AGT_AGTCR_OFFSET)
#define R_AGT_AGTMR1(n)                           (R_AGT_CH_BASE(n) + R_AGT_AGTMR1_OFFSET)
#define R_AGT_AGTMR2(n)                           (R_AGT_CH_BASE(n) + R_AGT_AGTMR2_OFFSET)
#define R_AGT_AGTIOC(n)                           (R_AGT_CH_BASE(n) + R_AGT_AGTIOC_OFFSET)
#define R_AGT_AGTISR(n)                           (R_AGT_CH_BASE(n) + R_AGT_AGTISR_OFFSET)
#define R_AGT_AGTCMSR(n)                          (R_AGT_CH_BASE(n) + R_AGT_AGTCMSR_OFFSET)
#define R_AGT_AGTIOSEL(n)                         (R_AGT_CH_BASE(n) + R_AGT_AGTIOSEL_OFFSET)

/* Register bit definitions */
/* AGTCR Register bit definitions */
#define R_AGT_AGTCR_TSTART                        (1 << 0)  /* AGT Count Start */

#define R_AGT_AGTCR_TCSTF                         (1 << 1)  /* AGT Count Status Flag */

#define R_AGT_AGTCR_TSTOP                         (1 << 2)  /* AGT Count Forced Stop */

#define R_AGT_AGTCR_TEDGF                         (1 << 4)  /* Active Edge Judgment Flag */

#define R_AGT_AGTCR_TUNDF                         (1 << 5)  /* Underflow Flag */

#define R_AGT_AGTCR_TCMAF                         (1 << 6)  /* Compare Match A Flag */

#define R_AGT_AGTCR_TCMBF                         (1 << 7)  /* Compare Match B Flag */

/* AGTMR1 Register bit definitions */
#define R_AGT_AGTMR1_TMOD_SHIFT                   (0)  /* Operating Mode */
#define R_AGT_AGTMR1_TMOD_MASK                    0x7
#  define R_AGT_AGTMR1_TMOD_000                           (0 << R_AGT_AGTMR1_TMOD_SHIFT)  /* Timer mode */
#  define R_AGT_AGTMR1_TMOD_001                           (1 << R_AGT_AGTMR1_TMOD_SHIFT)  /* Pulse output mode */
#  define R_AGT_AGTMR1_TMOD_010                           (2 << R_AGT_AGTMR1_TMOD_SHIFT)  /* Event counter mode */
#  define R_AGT_AGTMR1_TMOD_011                           (3 << R_AGT_AGTMR1_TMOD_SHIFT)  /* Pulse width measurement mode */
#  define R_AGT_AGTMR1_TMOD_100                           (4 << R_AGT_AGTMR1_TMOD_SHIFT)  /* Pulse period measurement mode */

#define R_AGT_AGTMR1_TEDGPL                       (1 << 3)  /* Edge Polarity */

#define R_AGT_AGTMR1_TCK_SHIFT                    (4)  /* Count Source */
#define R_AGT_AGTMR1_TCK_MASK                     0x70
#  define R_AGT_AGTMR1_TCK_000                            (0 << R_AGT_AGTMR1_TCK_SHIFT)  /* PCLKB */
#  define R_AGT_AGTMR1_TCK_001                            (1 << R_AGT_AGTMR1_TCK_SHIFT)  /* PCLKB/8 */
#  define R_AGT_AGTMR1_TCK_011                            (3 << R_AGT_AGTMR1_TCK_SHIFT)  /* PCLKB/2 */
#  define R_AGT_AGTMR1_TCK_100                            (4 << R_AGT_AGTMR1_TCK_SHIFT)  /* Divided clock AGTLCLK specified by CKS[2:0] bits in the AGTMR2 register */
#  define R_AGT_AGTMR1_TCK_101                            (5 << R_AGT_AGTMR1_TCK_SHIFT)  /* Underflow event signal from AGT0 */
#  define R_AGT_AGTMR1_TCK_110                            (6 << R_AGT_AGTMR1_TCK_SHIFT)  /* Divided clock AGTSCLK specified by CKS[2:0] bits in the AGTMR2 register */

/* AGTMR2 Register bit definitions */
#define R_AGT_AGTMR2_CKS_SHIFT                    (0)  /* AGTLCLK or AGTSCLK Count Source Clock Frequency Division Ratio */
#define R_AGT_AGTMR2_CKS_MASK                     0x7
#  define R_AGT_AGTMR2_CKS_000                            (0 << R_AGT_AGTMR2_CKS_SHIFT)  /* 1/1 */
#  define R_AGT_AGTMR2_CKS_001                            (1 << R_AGT_AGTMR2_CKS_SHIFT)  /* 1/2 */
#  define R_AGT_AGTMR2_CKS_010                            (2 << R_AGT_AGTMR2_CKS_SHIFT)  /* 1/4 */
#  define R_AGT_AGTMR2_CKS_011                            (3 << R_AGT_AGTMR2_CKS_SHIFT)  /* 1/8 */
#  define R_AGT_AGTMR2_CKS_100                            (4 << R_AGT_AGTMR2_CKS_SHIFT)  /* 1/16 */
#  define R_AGT_AGTMR2_CKS_101                            (5 << R_AGT_AGTMR2_CKS_SHIFT)  /* 1/32 */
#  define R_AGT_AGTMR2_CKS_110                            (6 << R_AGT_AGTMR2_CKS_SHIFT)  /* 1/64 */
#  define R_AGT_AGTMR2_CKS_111                            (7 << R_AGT_AGTMR2_CKS_SHIFT)  /* 1/128 */

#define R_AGT_AGTMR2_LPM                          (1 << 7)  /* Low Power Mode */

/* AGTIOC Register bit definitions */
#define R_AGT_AGTIOC_TEDGSEL                      (1 << 0)  /* I/O Polarity Switch */

#define R_AGT_AGTIOC_TOE                          (1 << 2)  /* AGTOn pin Output Enable */

#define R_AGT_AGTIOC_TIPF_SHIFT                   (4)  /* Input Filter */
#define R_AGT_AGTIOC_TIPF_MASK                    0x30
#  define R_AGT_AGTIOC_TIPF_00                            (0 << R_AGT_AGTIOC_TIPF_SHIFT)  /* No filter */
#  define R_AGT_AGTIOC_TIPF_01                            (1 << R_AGT_AGTIOC_TIPF_SHIFT)  /* Filter sampled at PCLKB */
#  define R_AGT_AGTIOC_TIPF_10                            (2 << R_AGT_AGTIOC_TIPF_SHIFT)  /* Filter sampled at PCLKB/8 */
#  define R_AGT_AGTIOC_TIPF_11                            (3 << R_AGT_AGTIOC_TIPF_SHIFT)  /* Filter sampled at PCLKB/32 */

#define R_AGT_AGTIOC_TIOGT_SHIFT                  (6)  /* Count Control */
#define R_AGT_AGTIOC_TIOGT_MASK                   0xc0
#  define R_AGT_AGTIOC_TIOGT_00                           (0 << R_AGT_AGTIOC_TIOGT_SHIFT)  /* Event is always counted */
#  define R_AGT_AGTIOC_TIOGT_01                           (1 << R_AGT_AGTIOC_TIOGT_SHIFT)  /* Event is counted during polarity period specified for AGTEEn pin */

/* AGTISR Register bit definitions */
#define R_AGT_AGTISR_EEPS                         (1 << 2)  /* AGTEEn Polarity Selection */

/* AGTCMSR Register bit definitions */
#define R_AGT_AGTCMSR_TCMEA                       (1 << 0)  /* AGT Compare Match A Register Enable */

#define R_AGT_AGTCMSR_TOEA                        (1 << 1)  /* AGTOAn Pin Output Enable */

#define R_AGT_AGTCMSR_TOPOLA                      (1 << 2)  /* AGTOAn Pin Polarity Select */

#define R_AGT_AGTCMSR_TCMEB                       (1 << 4)  /* AGT Compare Match B Register Enable */

#define R_AGT_AGTCMSR_TOEB                        (1 << 5)  /* AGTOBn Pin Output Enable */

#define R_AGT_AGTCMSR_TOPOLB                      (1 << 6)  /* AGTOBn Pin Polarity Select */

/* AGTIOSEL Register bit definitions */
#define R_AGT_AGTIOSEL_TIES                       (1 << 4)  /* AGTIOn Pin Input Enable */


/* Maximum number of channels */

#define AGT_MAX_CHANNELS    2

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_AGT_H */

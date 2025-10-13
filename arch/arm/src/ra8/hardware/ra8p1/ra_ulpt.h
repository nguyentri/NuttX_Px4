/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_ulpt.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ULPT_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ULPT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ULPT Base Address */
#ifndef R_ULPT_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_ULPT_BASE           0x40220000
#else
#define R_ULPT_BASE           0x50220000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_ULPT_CH_STRIDE    0x00000100
#define R_ULPT_CH_BASE(ch)   (R_ULPT_BASE + ((uint32_t)(ch) * R_ULPT_CH_STRIDE))

/* ULPT Register Offsets */

#define R_ULPT_ULPTCNT_OFFSET                     0x00000000  /* ULPT Counter Register */
#define R_ULPT_ULPTCMA_OFFSET                     0x00000004  /* ULPT Compare Match A Register */
#define R_ULPT_ULPTCMB_OFFSET                     0x00000008  /* ULPT Compare Match B Register */
#define R_ULPT_ULPTCR_OFFSET                      0x0000000c  /* ULPT Control Register */
#define R_ULPT_ULPTMR1_OFFSET                     0x0000000d  /* ULPT Mode Register 1 */
#define R_ULPT_ULPTMR2_OFFSET                     0x0000000e  /* ULPT Mode Register 2 */
#define R_ULPT_ULPTMR3_OFFSET                     0x0000000f  /* ULPT Mode Register 3 */
#define R_ULPT_ULPTIOC_OFFSET                     0x00000010  /* ULPT I/O Control Register */
#define R_ULPT_ULPTISR_OFFSET                     0x00000011  /* ULPT Event Pin Select Register */
#define R_ULPT_ULPTCMSR_OFFSET                    0x00000012  /* ULPT Compare Match Function Select Register */

/* ULPT Register Addresses */

#define R_ULPT_ULPTCNT(n)                         (R_ULPT_CH_BASE(n) + R_ULPT_ULPTCNT_OFFSET)
#define R_ULPT_ULPTCMA(n)                         (R_ULPT_CH_BASE(n) + R_ULPT_ULPTCMA_OFFSET)
#define R_ULPT_ULPTCMB(n)                         (R_ULPT_CH_BASE(n) + R_ULPT_ULPTCMB_OFFSET)
#define R_ULPT_ULPTCR(n)                          (R_ULPT_CH_BASE(n) + R_ULPT_ULPTCR_OFFSET)
#define R_ULPT_ULPTMR1(n)                         (R_ULPT_CH_BASE(n) + R_ULPT_ULPTMR1_OFFSET)
#define R_ULPT_ULPTMR2(n)                         (R_ULPT_CH_BASE(n) + R_ULPT_ULPTMR2_OFFSET)
#define R_ULPT_ULPTMR3(n)                         (R_ULPT_CH_BASE(n) + R_ULPT_ULPTMR3_OFFSET)
#define R_ULPT_ULPTIOC(n)                         (R_ULPT_CH_BASE(n) + R_ULPT_ULPTIOC_OFFSET)
#define R_ULPT_ULPTISR(n)                         (R_ULPT_CH_BASE(n) + R_ULPT_ULPTISR_OFFSET)
#define R_ULPT_ULPTCMSR(n)                        (R_ULPT_CH_BASE(n) + R_ULPT_ULPTCMSR_OFFSET)

/* Register bit definitions */
/* ULPTCNT Register bit definitions */
#define R_ULPT_ULPTCNT_ULPTCNT_SHIFT              (0)  /* Setting range : 0x00000000 to 0xFFFFFFFF */
#define R_ULPT_ULPTCNT_ULPTCNT_MASK               0xffffffff

/* ULPTCMA Register bit definitions */
#define R_ULPT_ULPTCMA_ULPTCMA_SHIFT              (0)  /* 32-bit Compare Match A Data */
#define R_ULPT_ULPTCMA_ULPTCMA_MASK               0xffffffff

/* ULPTCMB Register bit definitions */
#define R_ULPT_ULPTCMB_ULPTCMB_SHIFT              (0)  /* 32-bit Compare Match B Data */
#define R_ULPT_ULPTCMB_ULPTCMB_MASK               0xffffffff

/* ULPTCR Register bit definitions */
#define R_ULPT_ULPTCR_TSTART                      (1 << 0)  /* Counter Start */

#define R_ULPT_ULPTCR_TCSTF                       (1 << 1)  /* Counter Status Flag */

#define R_ULPT_ULPTCR_TSTOP                       (1 << 2)  /* Counter Forcible Stop */

#define R_ULPT_ULPTCR_TUNDF                       (1 << 5)  /* Underflow Flag */

#define R_ULPT_ULPTCR_TCMAF                       (1 << 6)  /* Compare Match A Flag */

#define R_ULPT_ULPTCR_TCMBF                       (1 << 7)  /* Compare Match B Flag */

/* ULPTMR1 Register bit definitions */
#define R_ULPT_ULPTMR1_TMOD1                      (1 << 1)  /* Operating Mode */

#define R_ULPT_ULPTMR1_TEDGPL                     (1 << 3)  /* ULPTEVIn Edge Polarity */

#define R_ULPT_ULPTMR1_TCK1                       (1 << 5)  /* Count Source */

/* ULPTMR2 Register bit definitions */
#define R_ULPT_ULPTMR2_CKS_SHIFT                  (0)  /* ULPTLCLK/ULPTSCLK Count Source Clock Division Ratio */
#define R_ULPT_ULPTMR2_CKS_MASK                   0x7
#  define R_ULPT_ULPTMR2_CKS_000                          (0 << R_ULPT_ULPTMR2_CKS_SHIFT)  /* 1/1 */
#  define R_ULPT_ULPTMR2_CKS_001                          (1 << R_ULPT_ULPTMR2_CKS_SHIFT)  /* 1/2 */
#  define R_ULPT_ULPTMR2_CKS_010                          (2 << R_ULPT_ULPTMR2_CKS_SHIFT)  /* 1/4 */
#  define R_ULPT_ULPTMR2_CKS_011                          (3 << R_ULPT_ULPTMR2_CKS_SHIFT)  /* 1/8 */
#  define R_ULPT_ULPTMR2_CKS_100                          (4 << R_ULPT_ULPTMR2_CKS_SHIFT)  /* 1/16 */
#  define R_ULPT_ULPTMR2_CKS_101                          (5 << R_ULPT_ULPTMR2_CKS_SHIFT)  /* 1/32 */
#  define R_ULPT_ULPTMR2_CKS_110                          (6 << R_ULPT_ULPTMR2_CKS_SHIFT)  /* 1/64 */
#  define R_ULPT_ULPTMR2_CKS_111                          (7 << R_ULPT_ULPTMR2_CKS_SHIFT)  /* 1/128 */

#define R_ULPT_ULPTMR2_LPM                        (1 << 7)  /* Low Power Mode */

/* ULPTMR3 Register bit definitions */
#define R_ULPT_ULPTMR3_TCNTCTL                    (1 << 0)  /* Count Function Select */

#define R_ULPT_ULPTMR3_TEVPOL                     (1 << 1)  /* ULPTEVIn Polarity Switch */

#define R_ULPT_ULPTMR3_TOPOL                      (1 << 2)  /* ULPTOn Polarity Select */

#define R_ULPT_ULPTMR3_TEECTL_SHIFT               (4)  /* ULPTEEn Function Select */
#define R_ULPT_ULPTMR3_TEECTL_MASK                0x30
#  define R_ULPT_ULPTMR3_TEECTL_00                        (0 << R_ULPT_ULPTMR3_TEECTL_SHIFT)  /* Count enable mode */
#  define R_ULPT_ULPTMR3_TEECTL_10                        (2 << R_ULPT_ULPTMR3_TEECTL_SHIFT)  /* Count start mode */
#  define R_ULPT_ULPTMR3_TEECTL_11                        (3 << R_ULPT_ULPTMR3_TEECTL_SHIFT)  /* Count restart mode */

#define R_ULPT_ULPTMR3_TEEPOL_SHIFT               (6)  /* ULPTEEn Edge Polarity Select */
#define R_ULPT_ULPTMR3_TEEPOL_MASK                0xc0
#  define R_ULPT_ULPTMR3_TEEPOL_00                        (0 << R_ULPT_ULPTMR3_TEEPOL_SHIFT)  /* Rising edge */
#  define R_ULPT_ULPTMR3_TEEPOL_01                        (1 << R_ULPT_ULPTMR3_TEEPOL_SHIFT)  /* Falling edge */
#  define R_ULPT_ULPTMR3_TEEPOL_10                        (2 << R_ULPT_ULPTMR3_TEEPOL_SHIFT)  /* Both edges */

/* ULPTIOC Register bit definitions */
#define R_ULPT_ULPTIOC_TOE                        (1 << 2)  /* ULPTOn Output Enable */

#define R_ULPT_ULPTIOC_TIPF_SHIFT                 (4)  /* ULPTEVIn Input Filter */
#define R_ULPT_ULPTIOC_TIPF_MASK                  0x30
#  define R_ULPT_ULPTIOC_TIPF_00                          (0 << R_ULPT_ULPTIOC_TIPF_SHIFT)  /* No filter */
#  define R_ULPT_ULPTIOC_TIPF_01                          (1 << R_ULPT_ULPTIOC_TIPF_SHIFT)  /* Filter sampling at PCLKB */
#  define R_ULPT_ULPTIOC_TIPF_10                          (2 << R_ULPT_ULPTIOC_TIPF_SHIFT)  /* Filter sampling at PCLKB/8 */
#  define R_ULPT_ULPTIOC_TIPF_11                          (3 << R_ULPT_ULPTIOC_TIPF_SHIFT)  /* Filter sampling at PCLKB/32 */

#define R_ULPT_ULPTIOC_TIOGT0                     (1 << 6)  /* ULPTEVIn Count Control */

/* ULPTISR Register bit definitions */
#define R_ULPT_ULPTISR_RCCPSEL2                   (1 << 2)  /* ULPTEEn Polarity Select */

/* ULPTCMSR Register bit definitions */
#define R_ULPT_ULPTCMSR_TCMEA                     (1 << 0)  /* Compare Match A Register Enable */

#define R_ULPT_ULPTCMSR_TOEA                      (1 << 1)  /* ULPTOAn Output Enable */

#define R_ULPT_ULPTCMSR_TOPOLA                    (1 << 2)  /* ULPTOAn Polarity Select */

#define R_ULPT_ULPTCMSR_TCMEB                     (1 << 4)  /* Compare Match B Register Enable */

#define R_ULPT_ULPTCMSR_TOEB                      (1 << 5)  /* ULPTOBn Output Enable */

#define R_ULPT_ULPTCMSR_TOPOLB                    (1 << 6)  /* ULPTOBn Polarity Select */


/* Maximum number of channels */

#define ULPT_MAX_CHANNELS    2

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ULPT_H */

/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_wdt.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_WDT_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_WDT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* WDT Base Address */
#ifndef R_WDT_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_WDT_BASE           0x40202600
#else
#define R_WDT_BASE           0x50202600
#endif
#endif

/* WDT Register Offsets */

#define R_WDT_WDTRR_OFFSET                        0x00000000  /* WDT Refresh Register */
#define R_WDT_WDTCR_OFFSET                        0x00000002  /* WDT Control Register */
#define R_WDT_WDTSR_OFFSET                        0x00000004  /* WDT Status Register */
#define R_WDT_WDTRCR_OFFSET                       0x00000006  /* WDT Reset Control Register */
#define R_WDT_WDTCSTPR_OFFSET                     0x00000008  /* WDT Count Stop Control Register */

/* WDT Register Addresses */

#define R_WDT_WDTRR                               (R_WDT_BASE + R_WDT_WDTRR_OFFSET)
#define R_WDT_WDTCR                               (R_WDT_BASE + R_WDT_WDTCR_OFFSET)
#define R_WDT_WDTSR                               (R_WDT_BASE + R_WDT_WDTSR_OFFSET)
#define R_WDT_WDTRCR                              (R_WDT_BASE + R_WDT_WDTRCR_OFFSET)
#define R_WDT_WDTCSTPR                            (R_WDT_BASE + R_WDT_WDTCSTPR_OFFSET)

/* Register bit definitions */
/* WDTRR Register bit definitions */
#define R_WDT_WDTRR_WDTRR_SHIFT                   (0)  /* WDTRR is an 8-bit register that refreshes the down-counter of the WDT. */
#define R_WDT_WDTRR_WDTRR_MASK                    0xff

/* WDTCR Register bit definitions */
#define R_WDT_WDTCR_TOPS_SHIFT                    (0)  /* Timeout Period Select */
#define R_WDT_WDTCR_TOPS_MASK                     0x3
#  define R_WDT_WDTCR_TOPS_00                             (0 << R_WDT_WDTCR_TOPS_SHIFT)  /* 1024 cycles (0x03FF) */
#  define R_WDT_WDTCR_TOPS_01                             (1 << R_WDT_WDTCR_TOPS_SHIFT)  /* 4096 cycles (0x0FFF) */
#  define R_WDT_WDTCR_TOPS_10                             (2 << R_WDT_WDTCR_TOPS_SHIFT)  /* 8192 cycles (0x1FFF) */
#  define R_WDT_WDTCR_TOPS_11                             (3 << R_WDT_WDTCR_TOPS_SHIFT)  /* 16384 cycles (0x3FFF) */

#define R_WDT_WDTCR_CKS_SHIFT                     (4)  /* Clock Division Ratio Select */
#define R_WDT_WDTCR_CKS_MASK                      0xf0
#  define R_WDT_WDTCR_CKS_0001                            (1 << R_WDT_WDTCR_CKS_SHIFT)  /* PCLKB/4 */
#  define R_WDT_WDTCR_CKS_0100                            (4 << R_WDT_WDTCR_CKS_SHIFT)  /* PCLKB/64 */
#  define R_WDT_WDTCR_CKS_1111                            (15 << R_WDT_WDTCR_CKS_SHIFT)  /* PCLKB/128 */
#  define R_WDT_WDTCR_CKS_0110                            (6 << R_WDT_WDTCR_CKS_SHIFT)  /* PCLKB/512 */
#  define R_WDT_WDTCR_CKS_0111                            (7 << R_WDT_WDTCR_CKS_SHIFT)  /* PCLKB/2048 */
#  define R_WDT_WDTCR_CKS_1000                            (8 << R_WDT_WDTCR_CKS_SHIFT)  /* PCLKB/8192 */

#define R_WDT_WDTCR_RPES_SHIFT                    (8)  /* Window End Position Select */
#define R_WDT_WDTCR_RPES_MASK                     0x300
#  define R_WDT_WDTCR_RPES_00                             (0 << R_WDT_WDTCR_RPES_SHIFT)  /* 75% */
#  define R_WDT_WDTCR_RPES_01                             (1 << R_WDT_WDTCR_RPES_SHIFT)  /* 50% */
#  define R_WDT_WDTCR_RPES_10                             (2 << R_WDT_WDTCR_RPES_SHIFT)  /* 25% */
#  define R_WDT_WDTCR_RPES_11                             (3 << R_WDT_WDTCR_RPES_SHIFT)  /* 0% (do not specify window end position). */

#define R_WDT_WDTCR_RPSS_SHIFT                    (12)  /* Window Start Position Select */
#define R_WDT_WDTCR_RPSS_MASK                     0x3000
#  define R_WDT_WDTCR_RPSS_00                             (0 << R_WDT_WDTCR_RPSS_SHIFT)  /* 25% */
#  define R_WDT_WDTCR_RPSS_01                             (1 << R_WDT_WDTCR_RPSS_SHIFT)  /* 50% */
#  define R_WDT_WDTCR_RPSS_10                             (2 << R_WDT_WDTCR_RPSS_SHIFT)  /* 75% */
#  define R_WDT_WDTCR_RPSS_11                             (3 << R_WDT_WDTCR_RPSS_SHIFT)  /* 100% (do not specify window start position). */

/* WDTSR Register bit definitions */
#define R_WDT_WDTSR_CNTVAL_SHIFT                  (0)  /* Down-Counter Value */
#define R_WDT_WDTSR_CNTVAL_MASK                   0x3fff

#define R_WDT_WDTSR_UNDFF                         (1 << 14)  /* Underflow Flag */

#define R_WDT_WDTSR_REFEF                         (1 << 15)  /* Refresh Error Flag */

/* WDTRCR Register bit definitions */
#define R_WDT_WDTRCR_RSTIRQS                      (1 << 7)  /* WDT Behavior Selection */

/* WDTCSTPR Register bit definitions */
#define R_WDT_WDTCSTPR_SLCSTP                     (1 << 7)  /* CPU Sleep-Mode Count Stop Control Register */


/* Maximum number of channels */

#define WDT_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_WDT_H */

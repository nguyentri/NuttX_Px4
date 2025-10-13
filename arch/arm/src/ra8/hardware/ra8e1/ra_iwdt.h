/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8e1/ra_iwdt.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_IWDT_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_IWDT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* IWDT Base Address */
#ifndef R_IWDT_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_IWDT_BASE           0x40202200
#else
#define R_IWDT_BASE           0x50202200
#endif
#endif

/* IWDT Register Offsets */

#define R_IWDT_IWDTRR_OFFSET                      0x00000000  /* IWDT Refresh Register */
#define R_IWDT_IWDTCR_OFFSET                      0x00000002  /* IWDT Control Register */
#define R_IWDT_IWDTSR_OFFSET                      0x00000004  /* IWDT Status Register */
#define R_IWDT_IWDTRCR_OFFSET                     0x00000006  /* IWDT Reset Control Register */
#define R_IWDT_IWDTCSTPR_OFFSET                   0x00000008  /* IWDT Count Stop Control Register */

/* IWDT Register Addresses */

#define R_IWDT_IWDTRR                             (R_IWDT_BASE + R_IWDT_IWDTRR_OFFSET)
#define R_IWDT_IWDTCR                             (R_IWDT_BASE + R_IWDT_IWDTCR_OFFSET)
#define R_IWDT_IWDTSR                             (R_IWDT_BASE + R_IWDT_IWDTSR_OFFSET)
#define R_IWDT_IWDTRCR                            (R_IWDT_BASE + R_IWDT_IWDTRCR_OFFSET)
#define R_IWDT_IWDTCSTPR                          (R_IWDT_BASE + R_IWDT_IWDTCSTPR_OFFSET)

/* Register bit definitions */
/* IWDTRR Register bit definitions */
#define R_IWDT_IWDTRR_REFRESH_SHIFT               (0)  /* Refresh Register */
#define R_IWDT_IWDTRR_REFRESH_MASK                0xff

#define R_IWDT_IWDTRR_IWDTRR_SHIFT                (0)  /* The counter is refreshed by writing 0x00 and then writing 0xFF to this register. */
#define R_IWDT_IWDTRR_IWDTRR_MASK                 0xff

/* IWDTCR Register bit definitions */
#define R_IWDT_IWDTCR_TOPS_SHIFT                  (0)  /* Timeout Period Select */
#define R_IWDT_IWDTCR_TOPS_MASK                   0x3
#  define R_IWDT_IWDTCR_TOPS_00                           (0 << R_IWDT_IWDTCR_TOPS_SHIFT)  /* 128 cycles (0x007F) */
#  define R_IWDT_IWDTCR_TOPS_01                           (1 << R_IWDT_IWDTCR_TOPS_SHIFT)  /* 512 cycles (0x01FF) */
#  define R_IWDT_IWDTCR_TOPS_10                           (2 << R_IWDT_IWDTCR_TOPS_SHIFT)  /* 1024 cycles (0x03FF) */
#  define R_IWDT_IWDTCR_TOPS_11                           (3 << R_IWDT_IWDTCR_TOPS_SHIFT)  /* 2048 cycles (0x07FF) */

#define R_IWDT_IWDTCR_CKS_SHIFT                   (4)  /* Clock Division Ratio Select */
#define R_IWDT_IWDTCR_CKS_MASK                    0xf0

#define R_IWDT_IWDTCR_RPES_SHIFT                  (8)  /* Window End Position Select */
#define R_IWDT_IWDTCR_RPES_MASK                   0x300
#  define R_IWDT_IWDTCR_RPES_00                           (0 << R_IWDT_IWDTCR_RPES_SHIFT)  /* 75% */
#  define R_IWDT_IWDTCR_RPES_01                           (1 << R_IWDT_IWDTCR_RPES_SHIFT)  /* 50% */
#  define R_IWDT_IWDTCR_RPES_10                           (2 << R_IWDT_IWDTCR_RPES_SHIFT)  /* 25% */
#  define R_IWDT_IWDTCR_RPES_11                           (3 << R_IWDT_IWDTCR_RPES_SHIFT)  /* 0% (No window end position setting) */

#define R_IWDT_IWDTCR_RPSS_SHIFT                  (12)  /* Window Start Position Select */
#define R_IWDT_IWDTCR_RPSS_MASK                   0x3000
#  define R_IWDT_IWDTCR_RPSS_00                           (0 << R_IWDT_IWDTCR_RPSS_SHIFT)  /* 25% */
#  define R_IWDT_IWDTCR_RPSS_01                           (1 << R_IWDT_IWDTCR_RPSS_SHIFT)  /* 50% */
#  define R_IWDT_IWDTCR_RPSS_10                           (2 << R_IWDT_IWDTCR_RPSS_SHIFT)  /* 75% */
#  define R_IWDT_IWDTCR_RPSS_11                           (3 << R_IWDT_IWDTCR_RPSS_SHIFT)  /* 100% (No window start position setting) */

/* IWDTSR Register bit definitions */
#define R_IWDT_IWDTSR_CNTVAL_SHIFT                (0)  /* Down-Counter Value */
#define R_IWDT_IWDTSR_CNTVAL_MASK                 0x3fff

#define R_IWDT_IWDTSR_UNDFF                       (1 << 14)  /* Underflow Flag */

#define R_IWDT_IWDTSR_REFEF                       (1 << 15)  /* Refresh Error Flag */

/* IWDTRCR Register bit definitions */
#define R_IWDT_IWDTRCR_RSTIRQS                    (1 << 7)  /* Reset Interrupt Request Select */

/* IWDTCSTPR Register bit definitions */
#define R_IWDT_IWDTCSTPR_SLCSTP                   (1 << 7)  /* CPU Sleep-Mode Count Stop Select */


/* Maximum number of channels */

#define IWDT_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_IWDT_H */

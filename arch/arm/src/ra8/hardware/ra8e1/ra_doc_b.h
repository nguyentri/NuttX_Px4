/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8e1/ra_doc_b.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_DOC_B_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_DOC_B_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DOC_B Base Address */
#ifndef R_DOC_B_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_DOC_B_BASE           0x40311000
#else
#define R_DOC_B_BASE           0x50311000
#endif
#endif

/* DOC_B Register Offsets */

#define R_DOC_B_DOCR_OFFSET                       0x00000000  /* DOC Control Register */
#define R_DOC_B_DOSR_OFFSET                       0x00000004  /* DOC Flag Status Register */
#define R_DOC_B_DOSCR_OFFSET                      0x00000008  /* DOC Flag Status Clear Register */
#define R_DOC_B_DODIR_OFFSET                      0x0000000c  /* DOC Data Input Register */
#define R_DOC_B_DODSR0_OFFSET                     0x00000010  /* DOC Data Setting Register 0 */
#define R_DOC_B_DODSR1_OFFSET                     0x00000014  /* DOC Data Setting Register 1 */

/* DOC_B Register Addresses */

#define R_DOC_B_DOCR                              (R_DOC_B_BASE + R_DOC_B_DOCR_OFFSET)
#define R_DOC_B_DOSR                              (R_DOC_B_BASE + R_DOC_B_DOSR_OFFSET)
#define R_DOC_B_DOSCR                             (R_DOC_B_BASE + R_DOC_B_DOSCR_OFFSET)
#define R_DOC_B_DODIR                             (R_DOC_B_BASE + R_DOC_B_DODIR_OFFSET)
#define R_DOC_B_DODSR0                            (R_DOC_B_BASE + R_DOC_B_DODSR0_OFFSET)
#define R_DOC_B_DODSR1                            (R_DOC_B_BASE + R_DOC_B_DODSR1_OFFSET)

/* Register bit definitions */
/* DOCR Register bit definitions */
#define R_DOC_B_DOCR_OMS_SHIFT                    (0)  /* Operating Mode Select */
#define R_DOC_B_DOCR_OMS_MASK                     0x3
#  define R_DOC_B_DOCR_OMS_00                             (0 << R_DOC_B_DOCR_OMS_SHIFT)  /* Data comparison mode */
#  define R_DOC_B_DOCR_OMS_01                             (1 << R_DOC_B_DOCR_OMS_SHIFT)  /* Data addition mode */
#  define R_DOC_B_DOCR_OMS_10                             (2 << R_DOC_B_DOCR_OMS_SHIFT)  /* Data subtraction mode */
#  define R_DOC_B_DOCR_OMS_11                             (3 << R_DOC_B_DOCR_OMS_SHIFT)  /* Setting prohibited */

#define R_DOC_B_DOCR_DOBW                         (1 << 3)  /* Data Operation Bit Width Select */

#define R_DOC_B_DOCR_DCSEL_SHIFT                  (4)  /* Detection Condition Select */
#define R_DOC_B_DOCR_DCSEL_MASK                   0x70
#  define R_DOC_B_DOCR_DCSEL_000                          (0 << R_DOC_B_DOCR_DCSEL_SHIFT)  /* Mismatch (DODSR0 ≠ DODIR) */
#  define R_DOC_B_DOCR_DCSEL_001                          (1 << R_DOC_B_DOCR_DCSEL_SHIFT)  /* Match (DODSR0 = DODIR) */
#  define R_DOC_B_DOCR_DCSEL_010                          (2 << R_DOC_B_DOCR_DCSEL_SHIFT)  /* Lower (DODSR0 > DODIR) */
#  define R_DOC_B_DOCR_DCSEL_011                          (3 << R_DOC_B_DOCR_DCSEL_SHIFT)  /* Upper (DODSR0 < DODIR) */
#  define R_DOC_B_DOCR_DCSEL_100                          (4 << R_DOC_B_DOCR_DCSEL_SHIFT)  /* Inside window (DODSR0 < DODIR < DODSR1) */
#  define R_DOC_B_DOCR_DCSEL_101                          (5 << R_DOC_B_DOCR_DCSEL_SHIFT)  /* Outside window (DODIR < DODSR0, DODSR1 < DODIR) */

/* DOSR Register bit definitions */
#define R_DOC_B_DOSR_DOPCF                        (1 << 0)  /* Data Operation Circuit Flag */

/* DOSCR Register bit definitions */
#define R_DOC_B_DOSCR_DOPCFCL                     (1 << 0)  /* DOPCF Clear */


/* Maximum number of channels */

#define DOC_B_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_DOC_B_H */

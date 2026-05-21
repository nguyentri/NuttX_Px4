/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_doc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DOC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DOC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DOC Base Address */
#ifndef R_DOC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_DOC_BASE           0x40311000
#else
#define R_DOC_BASE           0x50311000
#endif
#endif

/* DOC Register Offsets */

#define R_DOC_DOCR_OFFSET                         0x00000000  /* DOC Control Register */
#define R_DOC_DODIR_OFFSET                        0x00000002  /* DOC Data Input Register */
#define R_DOC_DODSR_OFFSET                        0x00000004  /* DOC Data Setting Register */

/* DOC Register Addresses */

#define R_DOC_DOCR                                (R_DOC_BASE + R_DOC_DOCR_OFFSET)
#define R_DOC_DODIR                               (R_DOC_BASE + R_DOC_DODIR_OFFSET)
#define R_DOC_DODSR                               (R_DOC_BASE + R_DOC_DODSR_OFFSET)

/* Register bit definitions */
/* DOCR Register bit definitions */
#define R_DOC_DOCR_DOPCFCL                        (1 << 6)  /* DOPCF Clear */

#define R_DOC_DOCR_DOPCF                          (1 << 5)  /* Data Operation Circuit Flag */

#define R_DOC_DOCR_DCSEL                          (1 << 2)  /* Detection Condition Select */

#define R_DOC_DOCR_OMS_SHIFT                      (0)  /* Operating Mode Select */
#define R_DOC_DOCR_OMS_MASK                       0x3
#  define R_DOC_DOCR_OMS_00                               (0 << R_DOC_DOCR_OMS_SHIFT)  /* Data comparison mode */
#  define R_DOC_DOCR_OMS_01                               (1 << R_DOC_DOCR_OMS_SHIFT)  /* Data addition mode */
#  define R_DOC_DOCR_OMS_10                               (2 << R_DOC_DOCR_OMS_SHIFT)  /* Data subtraction mode */
#  define R_DOC_DOCR_OMS_11                               (3 << R_DOC_DOCR_OMS_SHIFT)  /* Setting prohibited */

/* DODIR Register bit definitions */
#define R_DOC_DODIR_DODIR_SHIFT                   (0)  /* 16-bit read-write register in which 16-bit data for use in the operations are stored. */
#define R_DOC_DODIR_DODIR_MASK                    0xffff

/* DODSR Register bit definitions */
#define R_DOC_DODSR_DODSR_SHIFT                   (0)  /* This register stores 16-bit data for use as a reference in data comparison mode. This register also stores the results of operations in data addition and data subtraction modes. */
#define R_DOC_DODSR_DODSR_MASK                    0xffff


/* Maximum number of channels */

#define DOC_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DOC_H */

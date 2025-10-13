/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_poeg.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_POEG_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_POEG_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* POEG Base Address */
#ifndef R_POEG_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_POEG_BASE           0x40212000
#else
#define R_POEG_BASE           0x50212000
#endif
#endif

/* POEG Register Offsets */

#define R_POEG_POEGGA_OFFSET                      0x00000000  /* POEG Group A Setting Register */
#define R_POEG_POEGGB_OFFSET                      0x00000100  /* POEG Group B Setting Register */
#define R_POEG_POEGGC_OFFSET                      0x00000200  /* POEG Group C Setting Register */
#define R_POEG_POEGGD_OFFSET                      0x00000300  /* POEG Group D Setting Register */

/* POEG Register Addresses */

#define R_POEG_POEGGA                             (R_POEG_BASE + R_POEG_POEGGA_OFFSET)
#define R_POEG_POEGGB                             (R_POEG_BASE + R_POEG_POEGGB_OFFSET)
#define R_POEG_POEGGC                             (R_POEG_BASE + R_POEG_POEGGC_OFFSET)
#define R_POEG_POEGGD                             (R_POEG_BASE + R_POEG_POEGGD_OFFSET)

/* Register bit definitions */
/* POEGGA Register bit definitions */
#define R_POEG_POEGGA_PIDF                        (1 << 0)  /* Port Input Detection Flag */

#define R_POEG_POEGGA_IOCF                        (1 << 1)  /* Detection Flag for GPT or ACMPHS Output-Disable Request */

#define R_POEG_POEGGA_OSTPF                       (1 << 2)  /* Oscillation Stop Detection Flag */

#define R_POEG_POEGGA_SSF                         (1 << 3)  /* Software Stop Flag */

#define R_POEG_POEGGA_PIDE                        (1 << 4)  /* Port Input Detection Enable */

#define R_POEG_POEGGA_IOCE                        (1 << 5)  /* Enable for GPT Output-Disable Request */

#define R_POEG_POEGGA_OSTPE                       (1 << 6)  /* Oscillation Stop Detection Enable */

#define R_POEG_POEGGA_CDRE0                       (1 << 8)  /*  */

#define R_POEG_POEGGA_CDRE1                       (1 << 9)  /*  */

#define R_POEG_POEGGA_CDRE2                       (1 << 10)  /*  */

#define R_POEG_POEGGA_CDRE3                       (1 << 11)  /*  */

#define R_POEG_POEGGA_ST                          (1 << 16)  /* GTETRGn Input Status Flag */

#define R_POEG_POEGGA_INV                         (1 << 28)  /* GTETRGn Input Reverse */

#define R_POEG_POEGGA_NFEN                        (1 << 29)  /* Noise Filter Enable */

#define R_POEG_POEGGA_NFCS_SHIFT                  (30)  /* Noise Filter Clock Select */
#define R_POEG_POEGGA_NFCS_MASK                   0xc0000000
#  define R_POEG_POEGGA_NFCS_00                           (0 << R_POEG_POEGGA_NFCS_SHIFT)  /* Sample GTETRGn pin input level three times every PCLKB */
#  define R_POEG_POEGGA_NFCS_01                           (1 << R_POEG_POEGGA_NFCS_SHIFT)  /* Sample GTETRGn pin input level three times every PCLKB/8 */
#  define R_POEG_POEGGA_NFCS_10                           (2 << R_POEG_POEGGA_NFCS_SHIFT)  /* Sample GTETRGn pin input level three times every PCLKB/32 */
#  define R_POEG_POEGGA_NFCS_11                           (3 << R_POEG_POEGGA_NFCS_SHIFT)  /* Sample GTETRGn pin input level three times every PCLKB/128 */

/* POEGGB Register bit definitions */
#define R_POEG_POEGGB_PIDF                        (1 << 0)  /* Port Input Detection Flag */

#define R_POEG_POEGGB_IOCF                        (1 << 1)  /* Detection Flag for GPT or ACMPHS Output-Disable Request */

#define R_POEG_POEGGB_OSTPF                       (1 << 2)  /* Oscillation Stop Detection Flag */

#define R_POEG_POEGGB_SSF                         (1 << 3)  /* Software Stop Flag */

#define R_POEG_POEGGB_PIDE                        (1 << 4)  /* Port Input Detection Enable */

#define R_POEG_POEGGB_IOCE                        (1 << 5)  /* Enable for GPT Output-Disable Request */

#define R_POEG_POEGGB_OSTPE                       (1 << 6)  /* Oscillation Stop Detection Enable */

#define R_POEG_POEGGB_CDRE0                       (1 << 8)  /*  */

#define R_POEG_POEGGB_CDRE1                       (1 << 9)  /*  */

#define R_POEG_POEGGB_CDRE2                       (1 << 10)  /*  */

#define R_POEG_POEGGB_CDRE3                       (1 << 11)  /*  */

#define R_POEG_POEGGB_ST                          (1 << 16)  /* GTETRGn Input Status Flag */

#define R_POEG_POEGGB_INV                         (1 << 28)  /* GTETRGn Input Reverse */

#define R_POEG_POEGGB_NFEN                        (1 << 29)  /* Noise Filter Enable */

#define R_POEG_POEGGB_NFCS_SHIFT                  (30)  /* Noise Filter Clock Select */
#define R_POEG_POEGGB_NFCS_MASK                   0xc0000000
#  define R_POEG_POEGGB_NFCS_00                           (0 << R_POEG_POEGGB_NFCS_SHIFT)  /* Sample GTETRGn pin input level three times every PCLKB */
#  define R_POEG_POEGGB_NFCS_01                           (1 << R_POEG_POEGGB_NFCS_SHIFT)  /* Sample GTETRGn pin input level three times every PCLKB/8 */
#  define R_POEG_POEGGB_NFCS_10                           (2 << R_POEG_POEGGB_NFCS_SHIFT)  /* Sample GTETRGn pin input level three times every PCLKB/32 */
#  define R_POEG_POEGGB_NFCS_11                           (3 << R_POEG_POEGGB_NFCS_SHIFT)  /* Sample GTETRGn pin input level three times every PCLKB/128 */

/* POEGGC Register bit definitions */
#define R_POEG_POEGGC_PIDF                        (1 << 0)  /* Port Input Detection Flag */

#define R_POEG_POEGGC_IOCF                        (1 << 1)  /* Detection Flag for GPT or ACMPHS Output-Disable Request */

#define R_POEG_POEGGC_OSTPF                       (1 << 2)  /* Oscillation Stop Detection Flag */

#define R_POEG_POEGGC_SSF                         (1 << 3)  /* Software Stop Flag */

#define R_POEG_POEGGC_PIDE                        (1 << 4)  /* Port Input Detection Enable */

#define R_POEG_POEGGC_IOCE                        (1 << 5)  /* Enable for GPT Output-Disable Request */

#define R_POEG_POEGGC_OSTPE                       (1 << 6)  /* Oscillation Stop Detection Enable */

#define R_POEG_POEGGC_CDRE0                       (1 << 8)  /*  */

#define R_POEG_POEGGC_CDRE1                       (1 << 9)  /*  */

#define R_POEG_POEGGC_CDRE2                       (1 << 10)  /*  */

#define R_POEG_POEGGC_CDRE3                       (1 << 11)  /*  */

#define R_POEG_POEGGC_ST                          (1 << 16)  /* GTETRGn Input Status Flag */

#define R_POEG_POEGGC_INV                         (1 << 28)  /* GTETRGn Input Reverse */

#define R_POEG_POEGGC_NFEN                        (1 << 29)  /* Noise Filter Enable */

#define R_POEG_POEGGC_NFCS_SHIFT                  (30)  /* Noise Filter Clock Select */
#define R_POEG_POEGGC_NFCS_MASK                   0xc0000000
#  define R_POEG_POEGGC_NFCS_00                           (0 << R_POEG_POEGGC_NFCS_SHIFT)  /* Sample GTETRGn pin input level three times every PCLKB */
#  define R_POEG_POEGGC_NFCS_01                           (1 << R_POEG_POEGGC_NFCS_SHIFT)  /* Sample GTETRGn pin input level three times every PCLKB/8 */
#  define R_POEG_POEGGC_NFCS_10                           (2 << R_POEG_POEGGC_NFCS_SHIFT)  /* Sample GTETRGn pin input level three times every PCLKB/32 */
#  define R_POEG_POEGGC_NFCS_11                           (3 << R_POEG_POEGGC_NFCS_SHIFT)  /* Sample GTETRGn pin input level three times every PCLKB/128 */

/* POEGGD Register bit definitions */
#define R_POEG_POEGGD_PIDF                        (1 << 0)  /* Port Input Detection Flag */

#define R_POEG_POEGGD_IOCF                        (1 << 1)  /* Detection Flag for GPT or ACMPHS Output-Disable Request */

#define R_POEG_POEGGD_OSTPF                       (1 << 2)  /* Oscillation Stop Detection Flag */

#define R_POEG_POEGGD_SSF                         (1 << 3)  /* Software Stop Flag */

#define R_POEG_POEGGD_PIDE                        (1 << 4)  /* Port Input Detection Enable */

#define R_POEG_POEGGD_IOCE                        (1 << 5)  /* Enable for GPT Output-Disable Request */

#define R_POEG_POEGGD_OSTPE                       (1 << 6)  /* Oscillation Stop Detection Enable */

#define R_POEG_POEGGD_CDRE0                       (1 << 8)  /*  */

#define R_POEG_POEGGD_CDRE1                       (1 << 9)  /*  */

#define R_POEG_POEGGD_CDRE2                       (1 << 10)  /*  */

#define R_POEG_POEGGD_CDRE3                       (1 << 11)  /*  */

#define R_POEG_POEGGD_ST                          (1 << 16)  /* GTETRGn Input Status Flag */

#define R_POEG_POEGGD_INV                         (1 << 28)  /* GTETRGn Input Reverse */

#define R_POEG_POEGGD_NFEN                        (1 << 29)  /* Noise Filter Enable */

#define R_POEG_POEGGD_NFCS_SHIFT                  (30)  /* Noise Filter Clock Select */
#define R_POEG_POEGGD_NFCS_MASK                   0xc0000000
#  define R_POEG_POEGGD_NFCS_00                           (0 << R_POEG_POEGGD_NFCS_SHIFT)  /* Sample GTETRGn pin input level three times every PCLKB */
#  define R_POEG_POEGGD_NFCS_01                           (1 << R_POEG_POEGGD_NFCS_SHIFT)  /* Sample GTETRGn pin input level three times every PCLKB/8 */
#  define R_POEG_POEGGD_NFCS_10                           (2 << R_POEG_POEGGD_NFCS_SHIFT)  /* Sample GTETRGn pin input level three times every PCLKB/32 */
#  define R_POEG_POEGGD_NFCS_11                           (3 << R_POEG_POEGGD_NFCS_SHIFT)  /* Sample GTETRGn pin input level three times every PCLKB/128 */


/* Maximum number of channels */

#define POEG_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_POEG_H */

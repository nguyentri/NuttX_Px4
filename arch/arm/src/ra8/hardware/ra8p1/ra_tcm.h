/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_tcm.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_TCM_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_TCM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* TCM Base Address */
#ifndef R_TCM_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_TCM_BASE           0x4001c800
#else
#define R_TCM_BASE           0x5001c800
#endif
#endif

/* TCM Register Offsets */

#define R_TCM_TCMPRCR_S_OFFSET                    0x00000000  /* TCM Protection Control Register for Secure */
#define R_TCM_TCMCRC_OFFSET                       0x00000010  /* TCM Control Register */
#define R_TCM_TCMCRS_OFFSET                       0x00000014  /* TCM Control Register */
#define R_TCM_TCMESR_OFFSET                       0x00000040  /* TCM Error Status Register */
#define R_TCM_TCMESCLR_OFFSET                     0x00000048  /* TCM Error Status Clear Register */
#define R_TCM_TCMEARC0_OFFSET                     0x00000050  /* TCM Error Address Register */
#define R_TCM_TCMEARC1_OFFSET                     0x00000054  /* TCM Error Address Register */
#define R_TCM_TCMEARS0_OFFSET                     0x00000058  /* TCM Error Address Register */
#define R_TCM_TCMEARS1_OFFSET                     0x0000005c  /* TCM Error Address Register */

/* TCM Register Addresses */

#define R_TCM_TCMPRCR_S                           (R_TCM_BASE + R_TCM_TCMPRCR_S_OFFSET)
#define R_TCM_TCMCRC                              (R_TCM_BASE + R_TCM_TCMCRC_OFFSET)
#define R_TCM_TCMCRS                              (R_TCM_BASE + R_TCM_TCMCRS_OFFSET)
#define R_TCM_TCMESR                              (R_TCM_BASE + R_TCM_TCMESR_OFFSET)
#define R_TCM_TCMESCLR                            (R_TCM_BASE + R_TCM_TCMESCLR_OFFSET)
#define R_TCM_TCMEARC0                            (R_TCM_BASE + R_TCM_TCMEARC0_OFFSET)
#define R_TCM_TCMEARC1                            (R_TCM_BASE + R_TCM_TCMEARC1_OFFSET)
#define R_TCM_TCMEARS0                            (R_TCM_BASE + R_TCM_TCMEARS0_OFFSET)
#define R_TCM_TCMEARS1                            (R_TCM_BASE + R_TCM_TCMEARS1_OFFSET)

/* Register bit definitions */
/* TCMPRCR_S Register bit definitions */
#define R_TCM_TCMPRCR_S_PR                        (1 << 0)  /* Register Write Control */

#define R_TCM_TCMPRCR_S_KW_SHIFT                  (8)  /* Write Key Code */
#define R_TCM_TCMPRCR_S_KW_MASK                   0xff00

/* TCMCRC Register bit definitions */
#define R_TCM_TCMCRC_OAD                          (1 << 0)  /* Operation after ECC error detection */

#define R_TCM_TCMCRC_ECCMOD_SHIFT                 (2)  /* ECC Operating Mode Select */
#define R_TCM_TCMCRC_ECCMOD_MASK                  0xc
#  define R_TCM_TCMCRC_ECCMOD_00                          (0 << R_TCM_TCMCRC_ECCMOD_SHIFT)  /* Disable ECC function */
#  define R_TCM_TCMCRC_ECCMOD_01                          (1 << R_TCM_TCMCRC_ECCMOD_SHIFT)  /* Setting prohibited */
#  define R_TCM_TCMCRC_ECCMOD_10                          (2 << R_TCM_TCMCRC_ECCMOD_SHIFT)  /* Enable ECC function without error checking */
#  define R_TCM_TCMCRC_ECCMOD_11                          (3 << R_TCM_TCMCRC_ECCMOD_SHIFT)  /* Enable ECC function with error checking */

#define R_TCM_TCMCRC_E1STSEN                      (1 << 4)  /* ECC 1-Bit Error Information Update Enable */

#define R_TCM_TCMCRC_TSTBYP                       (1 << 7)  /* ECC Test Enable/ECC Bypass Select */

/* TCMCRS Register bit definitions */
#define R_TCM_TCMCRS_OAD                          (1 << 0)  /* Operation after ECC error detection */

#define R_TCM_TCMCRS_ECCMOD_SHIFT                 (2)  /* ECC Operating Mode Select */
#define R_TCM_TCMCRS_ECCMOD_MASK                  0xc
#  define R_TCM_TCMCRS_ECCMOD_00                          (0 << R_TCM_TCMCRS_ECCMOD_SHIFT)  /* Disable ECC function */
#  define R_TCM_TCMCRS_ECCMOD_01                          (1 << R_TCM_TCMCRS_ECCMOD_SHIFT)  /* Setting prohibited */
#  define R_TCM_TCMCRS_ECCMOD_10                          (2 << R_TCM_TCMCRS_ECCMOD_SHIFT)  /* Enable ECC function without error checking */
#  define R_TCM_TCMCRS_ECCMOD_11                          (3 << R_TCM_TCMCRS_ECCMOD_SHIFT)  /* Enable ECC function with error checking */

#define R_TCM_TCMCRS_E1STSEN                      (1 << 4)  /* ECC 1-Bit Error Information Update Enable */

#define R_TCM_TCMCRS_TSTBYP                       (1 << 7)  /* ECC Test Enable/ECC Bypass Select */

/* TCMESR Register bit definitions */
#define R_TCM_TCMESR_ERRC0                        (1 << 0)  /* C-TCM 1-bit ECC Error Status */

#define R_TCM_TCMESR_ERRC1                        (1 << 1)  /* C-TCM 2-bit ECC Error Status */

#define R_TCM_TCMESR_ERRS0                        (1 << 2)  /* S-TCM 1-bit ECC Error Status */

#define R_TCM_TCMESR_ERRS1                        (1 << 3)  /* S-TCM 2-bit ECC Error Status */

/* TCMESCLR Register bit definitions */
#define R_TCM_TCMESCLR_CLRC0                      (1 << 0)  /* C-TCM 1-bit ECC Error Status Clear */

#define R_TCM_TCMESCLR_CLRC1                      (1 << 1)  /* C-TCM 2-bit ECC Error Status Clear */

#define R_TCM_TCMESCLR_CLRS0                      (1 << 2)  /* S-TCM 1-bit ECC Error Status Clear */

#define R_TCM_TCMESCLR_CLRS1                      (1 << 3)  /* S-TCM 2-bit ECC Error Status Clear */

/* TCMEARC0 Register bit definitions */
#define R_TCM_TCMEARC0_EAR_SHIFT                  (2)  /* When an SRAM error occurs, an error address is stored. */
#define R_TCM_TCMEARC0_EAR_MASK                   0x3fffc

/* TCMEARC1 Register bit definitions */
#define R_TCM_TCMEARC1_EAR_SHIFT                  (2)  /* When an SRAM error occurs, an error address is stored. */
#define R_TCM_TCMEARC1_EAR_MASK                   0x3fffc

/* TCMEARS0 Register bit definitions */
#define R_TCM_TCMEARS0_EAR_SHIFT                  (2)  /* When an SRAM error occurs, an error address is stored. */
#define R_TCM_TCMEARS0_EAR_MASK                   0x3fffc

/* TCMEARS1 Register bit definitions */
#define R_TCM_TCMEARS1_EAR_SHIFT                  (2)  /* When an SRAM error occurs, an error address is stored. */
#define R_TCM_TCMEARS1_EAR_MASK                   0x3fffc


/* Maximum number of channels */

#define TCM_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_TCM_H */

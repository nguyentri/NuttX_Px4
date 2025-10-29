/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_sram.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SRAM_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SRAM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SRAM Base Address */
#ifndef R_SRAM_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_SRAM_BASE           0x40002000
#else
#define R_SRAM_BASE           0x50002000
#endif
#endif

/* SRAM Register Offsets */

#define R_SRAM_SRAMPRCR_OFFSET                    0x00000000  /* SRAM Protection Control Register for Secure */
#define R_SRAM_SRAMPRCR_NS_OFFSET                 0x00000004  /* SRAM Protection Control Register for Non-Secure */
#define R_SRAM_SRAMWTSC_OFFSET                    0x00000008  /* SRAM Wait State Control Register */
/* SRAMCR%s Registers (0-3) */
#define R_SRAM_SRAMCR_OFFSET(m)                   (0x00000010 + ((m) * 0x00000004))  /* SRAM Control Register %s */
/* SRAMECCRGN%s Registers (0-3) */
#define R_SRAM_SRAMECCRGN_OFFSET(m)               (0x00000030 + ((m) * 0x00000004))  /* SRAM ECC Region Control Register %s */
#define R_SRAM_SRAMESR_OFFSET                     0x00000040  /* SRAM Error Status Register For ECC RAM */
#define R_SRAM_SRAMESCLR_OFFSET                   0x00000048  /* SRAM Error Status Clear Register For ECC RAM */
/* SRAMEAR%s0 Registers (0-3) */
#define R_SRAM_SRAMEAR0_OFFSET(m)                 (0x00000050 + ((m) * 0x00000010))  /* SRAM Error Address Register %s0 */
/* SRAMEAR%s1 Registers (0-3) */
#define R_SRAM_SRAMEAR1_OFFSET(m)                 (0x00000054 + ((m) * 0x00000010))  /* SRAM Error Address Register %s1 */

/* SRAM Register Addresses */

#define R_SRAM_SRAMPRCR                           (R_SRAM_BASE + R_SRAM_SRAMPRCR_OFFSET)
#define R_SRAM_SRAMPRCR_NS                        (R_SRAM_BASE + R_SRAM_SRAMPRCR_NS_OFFSET)
#define R_SRAM_SRAMWTSC                           (R_SRAM_BASE + R_SRAM_SRAMWTSC_OFFSET)
#define R_SRAM_SRAMCR(m)                          (R_SRAM_BASE + R_SRAM_SRAMCR_OFFSET(m))
#define R_SRAM_SRAMECCRGN(m)                      (R_SRAM_BASE + R_SRAM_SRAMECCRGN_OFFSET(m))
#define R_SRAM_SRAMESR                            (R_SRAM_BASE + R_SRAM_SRAMESR_OFFSET)
#define R_SRAM_SRAMESCLR                          (R_SRAM_BASE + R_SRAM_SRAMESCLR_OFFSET)
#define R_SRAM_SRAMEAR0(m)                        (R_SRAM_BASE + R_SRAM_SRAMEAR0_OFFSET(m))
#define R_SRAM_SRAMEAR1(m)                        (R_SRAM_BASE + R_SRAM_SRAMEAR1_OFFSET(m))

/* Register bit definitions */
/* SRAMPRCR Register bit definitions */
#define R_SRAM_SRAMPRCR_PR                        (1 << 0)  /* Register Write Control */

#define R_SRAM_SRAMPRCR_KW_SHIFT                  (8)  /* Write Key Code */
#define R_SRAM_SRAMPRCR_KW_MASK                   0xff00

/* SRAMPRCR_NS Register bit definitions */
#define R_SRAM_SRAMPRCR_NS_PR                     (1 << 0)  /* Register Write Control */

#define R_SRAM_SRAMPRCR_NS_KW_SHIFT               (8)  /* Write Key Code */
#define R_SRAM_SRAMPRCR_NS_KW_MASK                0xff00

/* SRAMWTSC Register bit definitions */
#define R_SRAM_SRAMWTSC_WTEN                      (1 << 0)  /* SRAM wait enable */

/* SRAMCR Register bit definitions */
#define R_SRAM_SRAMCR_OAD                         (1 << 0)  /* Operation after error detection */

#define R_SRAM_SRAMCR_ECCMOD_SHIFT                (2)  /* ECC Operating Mode Select */
#define R_SRAM_SRAMCR_ECCMOD_MASK                 0xc
#  define R_SRAM_SRAMCR_ECCMOD_00                         (0 << R_SRAM_SRAMCR_ECCMOD_SHIFT)  /* Disable ECC function */
#  define R_SRAM_SRAMCR_ECCMOD_01                         (1 << R_SRAM_SRAMCR_ECCMOD_SHIFT)  /* Setting prohibited */
#  define R_SRAM_SRAMCR_ECCMOD_10                         (2 << R_SRAM_SRAMCR_ECCMOD_SHIFT)  /* Enable ECC function without error checking */
#  define R_SRAM_SRAMCR_ECCMOD_11                         (3 << R_SRAM_SRAMCR_ECCMOD_SHIFT)  /* Enable ECC function with error checking */

#define R_SRAM_SRAMCR_E1STSEN                     (1 << 4)  /* ECC 1-bit Error Update Enable */

#define R_SRAM_SRAMCR_TSTBYP                      (1 << 7)  /* ECC Test Enable / ECC Bypass Select */

/* SRAMECCRGN Register bit definitions */
#define R_SRAM_SRAMECCRGN_ECCRGN_SHIFT            (0)  /* ECC target Region select */
#define R_SRAM_SRAMECCRGN_ECCRGN_MASK             0x7

/* SRAMESR Register bit definitions */
#define R_SRAM_SRAMESR_ERR_S0                     (1 << 0)  /* SRAM%s 1-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR_S1                     (1 << 1)  /* SRAM%s 2-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR00                      (1 << 0)  /* SRAM0 1-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR01                      (1 << 1)  /* SRAM0 2-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR10                      (1 << 2)  /* SRAM1 1-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR11                      (1 << 3)  /* SRAM1 2-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR20                      (1 << 4)  /* SRAM2 1-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR21                      (1 << 5)  /* SRAM2 2-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR30                      (1 << 6)  /* SRAM3 1-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR31                      (1 << 7)  /* SRAM3 2-bit ECC Error Status */

/* SRAMESCLR Register bit definitions */
#define R_SRAM_SRAMESCLR_CLR_S0                   (1 << 0)  /* SRAM%s 1-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR_S1                   (1 << 1)  /* SRAM%s 2-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR00                    (1 << 0)  /* SRAM0 1-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR01                    (1 << 1)  /* SRAM0 2-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR10                    (1 << 2)  /* SRAM1 1-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR11                    (1 << 3)  /* SRAM1 2-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR20                    (1 << 4)  /* SRAM2 1-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR21                    (1 << 5)  /* SRAM2 2-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR30                    (1 << 6)  /* SRAM3 1-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR31                    (1 << 7)  /* SRAM3 2-bit ECC Error Status Clear */

/* SRAMEAR Register bit definitions */
#define R_SRAM_SRAMEAR_SRAMEAR_SHIFT              (0)  /* When an SRAM error occurs, it stores an error address */
#define R_SRAM_SRAMEAR_SRAMEAR_MASK               0xffffffff

/* SRAMEAR Register bit definitions */
#define R_SRAM_SRAMEAR_SRAMEAR_SHIFT              (0)  /* When an SRAM error occurs, it stores an error address */
#define R_SRAM_SRAMEAR_SRAMEAR_MASK               0xffffffff


/* Maximum number of channels */

#define SRAM_MAX_CHANNELS    4

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SRAM_H */

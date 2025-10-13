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

/* Channel stride for multi-channel peripherals */
#define R_SRAM_CH_STRIDE    0x00000004
#define R_SRAM_CH_BASE(ch)   (R_SRAM_BASE + ((uint32_t)(ch) * R_SRAM_CH_STRIDE))

/* SRAM Register Offsets */

#define R_SRAM_SRAMPRCR_S_OFFSET     0x00000000  /* SRAM Protection Control Register for Secure */
#define R_SRAM_SRAMWTSC_OFFSET     0x00000008  /* SRAM Wait State Control Register */
/* SRAMCR%s Registers (0-3) */
#define R_SRAM_SRAMCR0_OFFSET     0x00000010  /* SRAM Control Register 0 For ECC RAM */
#define R_SRAM_SRAMCR1_OFFSET     0x00000014  /* SRAM Control Register 1 For ECC RAM */
#define R_SRAM_SRAMCR2_OFFSET     0x00000018  /* SRAM Control Register 2 For ECC RAM */
#define R_SRAM_SRAMCR3_OFFSET     0x0000001c  /* SRAM Control Register 3 For ECC RAM */
#define R_SRAM_SRAMECCRGN0_OFFSET     0x00000030  /* SRAM ECC Region Control Register 0 */
#define R_SRAM_SRAMECCRGN1_OFFSET     0x00000034  /* SRAM ECC Region Control Register 1 */
#define R_SRAM_SRAMECCRGN2_OFFSET     0x00000038  /* SRAM ECC Region Control Register 2 */
#define R_SRAM_SRAMECCRGN3_OFFSET     0x0000003c  /* SRAM ECC Region Control Register 3 */
#define R_SRAM_SRAMESR_OFFSET     0x00000040  /* SRAM Error Status Register For ECC RAM */
#define R_SRAM_SRAMESCLR_OFFSET     0x00000048  /* SRAM Error Status Clear Register For ECC RAM */
/* SRAMEAR%s0 Registers (0-3) */
#define R_SRAM_SRAMEAR00_OFFSET     0x00000050  /* SRAM Error Address Register n0 For ECC RAM */
#define R_SRAM_SRAMEAR10_OFFSET     0x00000060  /* SRAM Error Address Register n0 For ECC RAM */
#define R_SRAM_SRAMEAR20_OFFSET     0x00000070  /* SRAM Error Address Register n0 For ECC RAM */
#define R_SRAM_SRAMEAR30_OFFSET     0x00000080  /* SRAM Error Address Register n0 For ECC RAM */
/* SRAMEAR%s1 Registers (0-3) */
#define R_SRAM_SRAMEAR01_OFFSET     0x00000054  /* SRAM Error Address Register n1 For ECC RAM */
#define R_SRAM_SRAMEAR11_OFFSET     0x00000064  /* SRAM Error Address Register n1 For ECC RAM */
#define R_SRAM_SRAMEAR21_OFFSET     0x00000074  /* SRAM Error Address Register n1 For ECC RAM */
#define R_SRAM_SRAMEAR31_OFFSET     0x00000084  /* SRAM Error Address Register n1 For ECC RAM */

/* SRAM Register Addresses */

#define R_SRAM_SRAMPRCR_S                 (R_SRAM_BASE + R_SRAM_SRAMPRCR_S_OFFSET)
#define R_SRAM_SRAMWTSC                 (R_SRAM_BASE + R_SRAM_SRAMWTSC_OFFSET)
#define R_SRAM_SRAMCR0                 (R_SRAM_BASE + R_SRAM_SRAMCR0_OFFSET)
#define R_SRAM_SRAMCR1                 (R_SRAM_BASE + R_SRAM_SRAMCR1_OFFSET)
#define R_SRAM_SRAMCR2                 (R_SRAM_BASE + R_SRAM_SRAMCR2_OFFSET)
#define R_SRAM_SRAMCR3                 (R_SRAM_BASE + R_SRAM_SRAMCR3_OFFSET)
#define R_SRAM_SRAMECCRGN0                 (R_SRAM_BASE + R_SRAM_SRAMECCRGN0_OFFSET)
#define R_SRAM_SRAMECCRGN1                 (R_SRAM_BASE + R_SRAM_SRAMECCRGN1_OFFSET)
#define R_SRAM_SRAMECCRGN2                 (R_SRAM_BASE + R_SRAM_SRAMECCRGN2_OFFSET)
#define R_SRAM_SRAMECCRGN3                 (R_SRAM_BASE + R_SRAM_SRAMECCRGN3_OFFSET)
#define R_SRAM_SRAMESR                 (R_SRAM_BASE + R_SRAM_SRAMESR_OFFSET)
#define R_SRAM_SRAMESCLR                 (R_SRAM_BASE + R_SRAM_SRAMESCLR_OFFSET)
#define R_SRAM_SRAMEAR00                 (R_SRAM_BASE + R_SRAM_SRAMEAR00_OFFSET)
#define R_SRAM_SRAMEAR10                 (R_SRAM_BASE + R_SRAM_SRAMEAR10_OFFSET)
#define R_SRAM_SRAMEAR20                 (R_SRAM_BASE + R_SRAM_SRAMEAR20_OFFSET)
#define R_SRAM_SRAMEAR30                 (R_SRAM_BASE + R_SRAM_SRAMEAR30_OFFSET)
#define R_SRAM_SRAMEAR01                 (R_SRAM_BASE + R_SRAM_SRAMEAR01_OFFSET)
#define R_SRAM_SRAMEAR11                 (R_SRAM_BASE + R_SRAM_SRAMEAR11_OFFSET)
#define R_SRAM_SRAMEAR21                 (R_SRAM_BASE + R_SRAM_SRAMEAR21_OFFSET)
#define R_SRAM_SRAMEAR31                 (R_SRAM_BASE + R_SRAM_SRAMEAR31_OFFSET)

/* Register bit definitions */
/* SRAMPRCR_S Register bit definitions */
#define R_SRAM_SRAMPRCR_S_PR                      (1 << 0)  /* Register Write Control */

#define R_SRAM_SRAMPRCR_S_KW_SHIFT                (8)  /* Write Key Code */
#define R_SRAM_SRAMPRCR_S_KW_MASK                 0xff00

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

/* SRAMECCRGN0 Register bit definitions */
#define R_SRAM_SRAMECCRGN0_ECCRGN_SHIFT           (0)  /* ECC target region select */
#define R_SRAM_SRAMECCRGN0_ECCRGN_MASK            0x7
#  define R_SRAM_SRAMECCRGN0_ECCRGN_000                   (0 << R_SRAM_SRAMECCRGN0_ECCRGN_SHIFT)  /* No ECC target region */
#  define R_SRAM_SRAMECCRGN0_ECCRGN_001                   (1 << R_SRAM_SRAMECCRGN0_ECCRGN_SHIFT)  /* 0x2200_0000–0x2201_FFFF 0x3200_0000–0x3201_FFFF (128 KB)  */
#  define R_SRAM_SRAMECCRGN0_ECCRGN_010                   (2 << R_SRAM_SRAMECCRGN0_ECCRGN_SHIFT)  /* 0x2200_0000–0x2203_FFFF 0x3200_0000–0x3203_FFFF (256 KB)  */
#  define R_SRAM_SRAMECCRGN0_ECCRGN_011                   (3 << R_SRAM_SRAMECCRGN0_ECCRGN_SHIFT)  /* 0x2200_0000–0x2205_FFFF 0x3200_0000–0x3205_FFFF (384 KB)  */
#  define R_SRAM_SRAMECCRGN0_ECCRGN_100                   (4 << R_SRAM_SRAMECCRGN0_ECCRGN_SHIFT)  /* 0x2200_0000–0x2207_FFFF 0x3200_0000–0x3207_FFFF (512 KB)  */

/* SRAMECCRGN1 Register bit definitions */
#define R_SRAM_SRAMECCRGN1_ECCRGN_SHIFT           (0)  /* ECC target region select */
#define R_SRAM_SRAMECCRGN1_ECCRGN_MASK            0x7
#  define R_SRAM_SRAMECCRGN1_ECCRGN_000                   (0 << R_SRAM_SRAMECCRGN1_ECCRGN_SHIFT)  /* No ECC target region */
#  define R_SRAM_SRAMECCRGN1_ECCRGN_001                   (1 << R_SRAM_SRAMECCRGN1_ECCRGN_SHIFT)  /* 0x2208_0000–0x2209_FFFF 0x3208_0000–0x3209_FFFF (128 KB)  */
#  define R_SRAM_SRAMECCRGN1_ECCRGN_010                   (2 << R_SRAM_SRAMECCRGN1_ECCRGN_SHIFT)  /* 0x2208_0000–0x220B_FFFF 0x3208_0000–0x320B_FFFF (256 KB)  */
#  define R_SRAM_SRAMECCRGN1_ECCRGN_011                   (3 << R_SRAM_SRAMECCRGN1_ECCRGN_SHIFT)  /* 0x2208_0000–0x220D_FFFF 0x3208_0000–0x320D_FFFF (384 KB)  */
#  define R_SRAM_SRAMECCRGN1_ECCRGN_100                   (4 << R_SRAM_SRAMECCRGN1_ECCRGN_SHIFT)  /* 0x2208_0000–0x220F_FFFF 0x3208_0000–0x320F_FFFF (512 KB)  */

/* SRAMECCRGN2 Register bit definitions */
#define R_SRAM_SRAMECCRGN2_ECCRGN_SHIFT           (0)  /* ECC target region select */
#define R_SRAM_SRAMECCRGN2_ECCRGN_MASK            0x7
#  define R_SRAM_SRAMECCRGN2_ECCRGN_000                   (0 << R_SRAM_SRAMECCRGN2_ECCRGN_SHIFT)  /* No ECC target region */
#  define R_SRAM_SRAMECCRGN2_ECCRGN_001                   (1 << R_SRAM_SRAMECCRGN2_ECCRGN_SHIFT)  /* 0x2210_0000–0x2211_FFFF 0x3210_0000–0x3211_FFFF (128 KB)  */
#  define R_SRAM_SRAMECCRGN2_ECCRGN_010                   (2 << R_SRAM_SRAMECCRGN2_ECCRGN_SHIFT)  /* 0x2210_0000–0x2213_FFFF 0x3210_0000–0x3213_FFFF (256 KB)  */
#  define R_SRAM_SRAMECCRGN2_ECCRGN_011                   (3 << R_SRAM_SRAMECCRGN2_ECCRGN_SHIFT)  /* 0x2210_0000–0x2215_FFFF 0x3210_0000–0x3215_FFFF (384 KB)  */
#  define R_SRAM_SRAMECCRGN2_ECCRGN_100                   (4 << R_SRAM_SRAMECCRGN2_ECCRGN_SHIFT)  /* 0x2210_0000–0x2217_FFFF 0x3210_0000–0x3217_FFFF (512 KB)  */

/* SRAMECCRGN3 Register bit definitions */
#define R_SRAM_SRAMECCRGN3_ECCRGN_SHIFT           (0)  /* ECC target region select */
#define R_SRAM_SRAMECCRGN3_ECCRGN_MASK            0x7
#  define R_SRAM_SRAMECCRGN3_ECCRGN_000                   (0 << R_SRAM_SRAMECCRGN3_ECCRGN_SHIFT)  /* No ECC target region */
#  define R_SRAM_SRAMECCRGN3_ECCRGN_001                   (1 << R_SRAM_SRAMECCRGN3_ECCRGN_SHIFT)  /* 0x2218_0000–0x2219_FFFF 0x3218_0000–0x3219_FFFF (128 KB)  */

/* SRAMESR Register bit definitions */
#define R_SRAM_SRAMESR_ERR00                      (1 << 0)  /* SRAM0 1-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR01                      (1 << 1)  /* SRAM0 2-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR10                      (1 << 2)  /* SRAM1 1-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR11                      (1 << 3)  /* SRAM1 2-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR20                      (1 << 4)  /* SRAM2 1-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR21                      (1 << 5)  /* SRAM2 2-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR30                      (1 << 6)  /* SRAM3 1-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR31                      (1 << 7)  /* SRAM3 2-bit ECC Error Status */

/* SRAMESCLR Register bit definitions */
#define R_SRAM_SRAMESCLR_CLR00                    (1 << 0)  /* SRAM0 1-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR01                    (1 << 1)  /* SRAM0 2-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR10                    (1 << 2)  /* SRAM1 1-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR11                    (1 << 3)  /* SRAM1 2-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR20                    (1 << 4)  /* SRAM2 1-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR21                    (1 << 5)  /* SRAM2 2-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR30                    (1 << 6)  /* SRAM3 1-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR31                    (1 << 7)  /* SRAM3 2-bit ECC Error Status Clear */


/* Maximum number of channels */

#define SRAM_MAX_CHANNELS    4

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SRAM_H */

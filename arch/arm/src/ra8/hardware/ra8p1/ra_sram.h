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

/* SDRAM Controller Registers (Mapped to BUS peripheral) */
/* These definitions are added here as requested, but physically belong to the BUS peripheral */

#define R_BUS_SDRAM_SDCCR_OFFSET                  0x00000000
#define R_BUS_SDRAM_SDCMOD_OFFSET                 0x00000001
#define R_BUS_SDRAM_SDAMOD_OFFSET                 0x00000002
#define R_BUS_SDRAM_SDSELF_OFFSET                 0x00000010
#define R_BUS_SDRAM_SDRFCR_OFFSET                 0x00000014
#define R_BUS_SDRAM_SDRFEN_OFFSET                 0x00000016
#define R_BUS_SDRAM_SDICR_OFFSET                  0x00000020
#define R_BUS_SDRAM_SDIR_OFFSET                   0x00000024
#define R_BUS_SDRAM_SDADR_OFFSET                  0x00000040
#define R_BUS_SDRAM_SDTR_OFFSET                   0x00000044
#define R_BUS_SDRAM_SDMOD_OFFSET                  0x00000048
#define R_BUS_SDRAM_SDSR_OFFSET                   0x00000050

/* SDCCR - SDC Control Register */
#define R_BUS_SDRAM_SDCCR_EXENB                   (1 << 0)  /* Operation Enable */
#define R_BUS_SDRAM_SDCCR_BSIZE_SHIFT             (4)       /* SDRAM Bus Width Select */
#define R_BUS_SDRAM_SDCCR_BSIZE_MASK              (3 << 4)
#define R_BUS_SDRAM_SDCCR_BSIZE_16BIT             (0 << 4)
#define R_BUS_SDRAM_SDCCR_BSIZE_32BIT             (1 << 4)
#define R_BUS_SDRAM_SDCCR_BSIZE_8BIT              (2 << 4)

/* SDCMOD - SDC Mode Register */
#define R_BUS_SDRAM_SDCMOD_EMODE                  (1 << 0)  /* Endian Mode (0: Little, 1: Big) */

/* SDAMOD - SDRAM Access Mode Register */
#define R_BUS_SDRAM_SDAMOD_BE                     (1 << 0)  /* Continuous Access Enable */

/* SDSELF - SDRAM Self-Refresh Control Register */
#define R_BUS_SDRAM_SDSELF_SFEN                   (1 << 0)  /* SDRAM Self-Refresh Enable */

/* SDRFCR - SDRAM Refresh Control Register */
#define R_BUS_SDRAM_SDRFCR_RFC_SHIFT              (0)       /* Auto-Refresh Request Interval Setting */
#define R_BUS_SDRAM_SDRFCR_RFC_MASK               (0xfff << 0)
#define R_BUS_SDRAM_SDRFCR_REFW_SHIFT             (12)      /* Auto-Refresh Cycle/ Self-Refresh Clearing Cycle Count Setting */
#define R_BUS_SDRAM_SDRFCR_REFW_MASK              (0xf << 12)

/* SDRFEN - SDRAM Auto-Refresh Control Register */
#define R_BUS_SDRAM_SDRFEN_RFEN                   (1 << 0)  /* Auto-Refresh Operation Enable */

/* SDICR - SDRAM Initialization Sequence Control Register */
#define R_BUS_SDRAM_SDICR_INIRQ                   (1 << 0)  /* Initialization Sequence Start */

/* SDIR - SDRAM Initialization Register */
#define R_BUS_SDRAM_SDIR_ARFI_SHIFT               (0)       /* Initialization Auto-Refresh Interval */
#define R_BUS_SDRAM_SDIR_ARFI_MASK                (0xf << 0)
#define R_BUS_SDRAM_SDIR_ARFC_SHIFT               (4)       /* Initialization Auto-Refresh Count */
#define R_BUS_SDRAM_SDIR_ARFC_MASK                (0xf << 4)
#define R_BUS_SDRAM_SDIR_PRC_SHIFT                (8)       /* Initialization Precharge Cycle Count */
#define R_BUS_SDRAM_SDIR_PRC_MASK                 (0x7 << 8)

/* SDADR - SDRAM Address Register */
#define R_BUS_SDRAM_SDADR_MXC_SHIFT               (0)       /* Address Multiplex Select */
#define R_BUS_SDRAM_SDADR_MXC_MASK                (0x3 << 0)
#define R_BUS_SDRAM_SDADR_MXC_8BIT_SHIFT          (0)       /* 8-bit shift */
#define R_BUS_SDRAM_SDADR_MXC_9BIT_SHIFT          (1)       /* 9-bit shift */
#define R_BUS_SDRAM_SDADR_MXC_10BIT_SHIFT         (2)       /* 10-bit shift */
#define R_BUS_SDRAM_SDADR_MXC_11BIT_SHIFT         (3)       /* 11-bit shift */

/* SDTR - SDRAM Timing Register */
#define R_BUS_SDRAM_SDTR_CL_SHIFT                 (0)       /* SDRAMC Column Latency */
#define R_BUS_SDRAM_SDTR_CL_MASK                  (0x7 << 0)
#define R_BUS_SDRAM_SDTR_WR                       (1 << 8)  /* Write Recovery Interval */
#define R_BUS_SDRAM_SDTR_RP_SHIFT                 (9)       /* Row Precharge Interval */
#define R_BUS_SDRAM_SDTR_RP_MASK                  (0x7 << 9)
#define R_BUS_SDRAM_SDTR_RCD_SHIFT                (12)      /* Row Column Latency */
#define R_BUS_SDRAM_SDTR_RCD_MASK                 (0x3 << 12)
#define R_BUS_SDRAM_SDTR_RAS_SHIFT                (16)      /* Row Active Interval */
#define R_BUS_SDRAM_SDTR_RAS_MASK                 (0x7 << 16)

/* SDMOD - SDRAM Mode Register */
#define R_BUS_SDRAM_SDMOD_MR_SHIFT                (0)       /* Mode Register Setting */
#define R_BUS_SDRAM_SDMOD_MR_MASK                 (0x7fff << 0)

/* SDSR - SDRAM Status Register */
#define R_BUS_SDRAM_SDSR_MRSST                    (1 << 0)  /* Mode Register Setting Status */
#define R_BUS_SDRAM_SDSR_INIST                    (1 << 3)  /* Initialization Status */
#define R_BUS_SDRAM_SDSR_SRFST                    (1 << 4)  /* Self-Refresh Transition/Recovery Status */

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SRAM_H */

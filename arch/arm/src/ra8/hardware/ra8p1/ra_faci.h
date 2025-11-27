/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_faci.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_FACI_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_FACI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* FACI Base Address */
#ifndef R_FACI_BASE
#define R_FACI_BASE           0x4011e000
#endif

/* FACI Register Offsets */

#define R_FACI_FASTAT_OFFSET                      0x00000010  /* Flash Access Status Register */
#define R_FACI_FAEINT_OFFSET                      0x00000014  /* Flash Access Error Interrupt Enable Register */
#define R_FACI_FRDYIE_OFFSET                      0x00000018  /* Flash Ready Interrupt Enable Register */
#define R_FACI_FSADDR_OFFSET                      0x00000030  /* FACI Command Start Address Register */
#define R_FACI_FEADDR_OFFSET                      0x00000034  /* FACI Command End Address Register */
#define R_FACI_FMEPROT_OFFSET                     0x00000044  /* Flash P/E Mode Entry Protection Register */
#define R_FACI_FCNTSELR_OFFSET                    0x00000048  /* Flash Counter Select Register */
/* FCNTDATAR%s Registers (0-1) */
#define R_FACI_FCNTDATAR_OFFSET(m)                (0x0000004c + ((m) * 0x00000004))  /* Flash Counter Data Register %s */
#define R_FACI_FBPROT0_OFFSET                     0x00000078  /* Flash Block Protection Register */
#define R_FACI_FBPROT1_OFFSET                     0x0000007c  /* Flash Block Protection for Secure Register */
#define R_FACI_FSTATR_OFFSET                      0x00000080  /* Flash Status Register */
#define R_FACI_FENTRYR_OFFSET                     0x00000084  /* Flash P/E Mode Entry Register */
#define R_FACI_FSUINITR_OFFSET                    0x0000008c  /* Flash Sequencer Setup Initialization Register */
#define R_FACI_FCMDR_OFFSET                       0x000000a0  /* FACI Command Register */
#define R_FACI_FBCCNT_OFFSET                      0x000000d0  /* Blank Check Control Register */
#define R_FACI_FBCSTAT_OFFSET                     0x000000d4  /* Blank Check Status Register */
#define R_FACI_FPSADDR_OFFSET                     0x000000d8  /* Data Flash Programming Start Address Register */
#define R_FACI_FSUASMON_OFFSET                    0x000000dc  /* Flash Startup Area Select Monitor Register */
#define R_FACI_FCPSR_OFFSET                       0x000000e0  /* Flash Sequencer Processing Switching Register */
#define R_FACI_FPCKAR_OFFSET                      0x000000e4  /* Flash Sequencer Processing Clock Notification Register */
#define R_FACI_FSUACR_OFFSET                      0x000000e8  /* Flash Startup Area Control Register */

/* FACI Register Addresses */

#define R_FACI_FASTAT                             (R_FACI_BASE + R_FACI_FASTAT_OFFSET)
#define R_FACI_FAEINT                             (R_FACI_BASE + R_FACI_FAEINT_OFFSET)
#define R_FACI_FRDYIE                             (R_FACI_BASE + R_FACI_FRDYIE_OFFSET)
#define R_FACI_FSADDR                             (R_FACI_BASE + R_FACI_FSADDR_OFFSET)
#define R_FACI_FEADDR                             (R_FACI_BASE + R_FACI_FEADDR_OFFSET)
#define R_FACI_FMEPROT                            (R_FACI_BASE + R_FACI_FMEPROT_OFFSET)
#define R_FACI_FCNTSELR                           (R_FACI_BASE + R_FACI_FCNTSELR_OFFSET)
#define R_FACI_FCNTDATAR(m)                       (R_FACI_BASE + R_FACI_FCNTDATAR_OFFSET(m))
#define R_FACI_FBPROT0                            (R_FACI_BASE + R_FACI_FBPROT0_OFFSET)
#define R_FACI_FBPROT1                            (R_FACI_BASE + R_FACI_FBPROT1_OFFSET)
#define R_FACI_FSTATR                             (R_FACI_BASE + R_FACI_FSTATR_OFFSET)
#define R_FACI_FENTRYR                            (R_FACI_BASE + R_FACI_FENTRYR_OFFSET)
#define R_FACI_FSUINITR                           (R_FACI_BASE + R_FACI_FSUINITR_OFFSET)
#define R_FACI_FCMDR                              (R_FACI_BASE + R_FACI_FCMDR_OFFSET)
#define R_FACI_FBCCNT                             (R_FACI_BASE + R_FACI_FBCCNT_OFFSET)
#define R_FACI_FBCSTAT                            (R_FACI_BASE + R_FACI_FBCSTAT_OFFSET)
#define R_FACI_FPSADDR                            (R_FACI_BASE + R_FACI_FPSADDR_OFFSET)
#define R_FACI_FSUASMON                           (R_FACI_BASE + R_FACI_FSUASMON_OFFSET)
#define R_FACI_FCPSR                              (R_FACI_BASE + R_FACI_FCPSR_OFFSET)
#define R_FACI_FPCKAR                             (R_FACI_BASE + R_FACI_FPCKAR_OFFSET)
#define R_FACI_FSUACR                             (R_FACI_BASE + R_FACI_FSUACR_OFFSET)

/* Register bit definitions */
/* FBPROT0 Register bit definitions */
#define R_FACI_FBPROT0_BPCN0                      (1 << 0)  /* Block Protection for Non-secure Cancel */

#define R_FACI_FBPROT0_KEY_SHIFT                  (8)  /* Key Code */
#define R_FACI_FBPROT0_KEY_MASK                   0xff00

/* FBPROT1 Register bit definitions */
#define R_FACI_FBPROT1_BPCN1                      (1 << 0)  /* Block Protection for Secure Cancel */

#define R_FACI_FBPROT1_KEY_SHIFT                  (8)  /* Key Code */
#define R_FACI_FBPROT1_KEY_MASK                   0xff00

/* FASTAT Register bit definitions */
#define R_FACI_FASTAT_DFAE                        (1 << 3)  /* Data Flash Memory Access Violation Flag */

#define R_FACI_FASTAT_CMDLK                       (1 << 4)  /* Command Lock Flag */

#define R_FACI_FASTAT_CFAE                        (1 << 7)  /* Code Flash Memory Access Violation Flag */

/* FAEINT Register bit definitions */
#define R_FACI_FAEINT_DFAEIE                      (1 << 3)  /* Data Flash Memory Access Violation Interrupt Enable */

#define R_FACI_FAEINT_CMDLKIE                     (1 << 4)  /* Command Lock Interrupt Enable */

#define R_FACI_FAEINT_CFAEIE                      (1 << 7)  /* Code Flash Memory Access Violation Interrupt Enable */

/* FRDYIE Register bit definitions */
#define R_FACI_FRDYIE_FRDYIE                      (1 << 0)  /* Flash Ready Interrupt Enable */

/* FEADDR Register bit definitions */
#define R_FACI_FEADDR_FEADDR_SHIFT                (0)  /* End Address for FACI Command Processing */
#define R_FACI_FEADDR_FEADDR_MASK                 0xffffffff

/* FMEPROT Register bit definitions */
#define R_FACI_FMEPROT_CEPROT                     (1 << 0)  /* Code Flash P/E Mode Entry Protection */

#define R_FACI_FMEPROT_KEY_SHIFT                  (8)  /* Key Code */
#define R_FACI_FMEPROT_KEY_MASK                   0xff00

/* FCNTSELR Register bit definitions */
#define R_FACI_FCNTSELR_CNTSEL_SHIFT              (0)  /* Counter Select */
#define R_FACI_FCNTSELR_CNTSEL_MASK               0x7

/* FCNTDATAR Register bit definitions */
#define R_FACI_FCNTDATAR_CNTRDAT_SHIFT            (0)  /* Counter Read Data */
#define R_FACI_FCNTDATAR_CNTRDAT_MASK             0xffffffff

/* FSTATR Register bit definitions */
#define R_FACI_FSTATR_FLWEERR                     (1 << 6)  /* Flash Write/Erase Protect Error Flag */

#define R_FACI_FSTATR_PRGSPD                      (1 << 8)  /* Programming Suspend Status Flag */

#define R_FACI_FSTATR_ERSSPD                      (1 << 9)  /* Erasure Suspend Status Flag */

#define R_FACI_FSTATR_DBFULL                      (1 << 10)  /* Data Buffer Full Flag */

#define R_FACI_FSTATR_SUSRDY                      (1 << 11)  /* Suspend Ready Flag */

#define R_FACI_FSTATR_PRGERR                      (1 << 12)  /* Programming Error Flag */

#define R_FACI_FSTATR_ERSERR                      (1 << 13)  /* Erasure Error Flag */

#define R_FACI_FSTATR_ILGLERR                     (1 << 14)  /* Illegal Command Error Flag */

#define R_FACI_FSTATR_FRDY                        (1 << 15)  /* Flash Ready Flag */

#define R_FACI_FSTATR_TZFERR                      (1 << 19)  /* TrustZone Filter Error */

#define R_FACI_FSTATR_OTERR                       (1 << 20)  /* Other Error */

#define R_FACI_FSTATR_SECERR                      (1 << 21)  /* Security Error */

#define R_FACI_FSTATR_FESETERR                    (1 << 22)  /* FENTRY Setting Error */

#define R_FACI_FSTATR_ILGCOMERR                   (1 << 23)  /* Illegal Command Error */

/* FENTRYR Register bit definitions */
#define R_FACI_FENTRYR_FENTRYC                    (1 << 0)  /* Code Flash P/E Mode Entry */

#define R_FACI_FENTRYR_FENTRYD                    (1 << 7)  /* Data Flash P/E Mode Entry */

#define R_FACI_FENTRYR_KEY_SHIFT                  (8)  /* Key Code */
#define R_FACI_FENTRYR_KEY_MASK                   0xff00

/* FSUINITR Register bit definitions */
#define R_FACI_FSUINITR_SUINIT                    (1 << 0)  /* Set-Up Initialization */

#define R_FACI_FSUINITR_KEY_SHIFT                 (8)  /* Key Code */
#define R_FACI_FSUINITR_KEY_MASK                  0xff00

/* FCMDR Register bit definitions */
#define R_FACI_FCMDR_PCMDR_SHIFT                  (0)  /* Pre-command Flag */
#define R_FACI_FCMDR_PCMDR_MASK                   0xff

#define R_FACI_FCMDR_CMDR_SHIFT                   (8)  /* Command Flag */
#define R_FACI_FCMDR_CMDR_MASK                    0xff00

/* FBCCNT Register bit definitions */
#define R_FACI_FBCCNT_BCDIR                       (1 << 0)  /* Blank Check Direction */

/* FBCSTAT Register bit definitions */
#define R_FACI_FBCSTAT_BCST                       (1 << 0)  /* Blank Check Status Flag */

/* FPSADDR Register bit definitions */
#define R_FACI_FPSADDR_PSADR_SHIFT                (0)  /* Programmed Area Start Address */
#define R_FACI_FPSADDR_PSADR_MASK                 0x1ffff

/* FSUASMON Register bit definitions */
#define R_FACI_FSUASMON_FSPR                      (1 << 15)  /* Protection Programming Flag to set Boot Flag and Startup Area Control */

#define R_FACI_FSUASMON_BTFLG                     (1 << 31)  /* Flag of Startup Area Select for Boot Swap */

/* FCPSR Register bit definitions */
#define R_FACI_FCPSR_ESUSPMD                      (1 << 0)  /* Erasure Suspend Mode */

/* FPCKAR Register bit definitions */
#define R_FACI_FPCKAR_PCKA_SHIFT                  (0)  /* Flash Sequencer Operating Clock Notification */
#define R_FACI_FPCKAR_PCKA_MASK                   0xff

#define R_FACI_FPCKAR_KEY_SHIFT                   (8)  /* Key Code */
#define R_FACI_FPCKAR_KEY_MASK                    0xff00

/* FSUACR Register bit definitions */
#define R_FACI_FSUACR_SAS_SHIFT                   (0)  /* Startup Area Select */
#define R_FACI_FSUACR_SAS_MASK                    0x3
#  define R_FACI_FSUACR_SAS_00                            (0 << R_FACI_FSUACR_SAS_SHIFT)  /* Startup area is selected by BTFLG bit */
#  define R_FACI_FSUACR_SAS_01                            (1 << R_FACI_FSUACR_SAS_SHIFT)  /* Startup area is selected by BTFLG bit */
#  define R_FACI_FSUACR_SAS_10                            (2 << R_FACI_FSUACR_SAS_SHIFT)  /* Startup area is temporarily switched to the default area (block 0) */
#  define R_FACI_FSUACR_SAS_11                            (3 << R_FACI_FSUACR_SAS_SHIFT)  /* Startup area is temporarily switched to the alternate area (block 1). */

#define R_FACI_FSUACR_KEY_SHIFT                   (8)  /* Key Code */
#define R_FACI_FSUACR_KEY_MASK                    0xff00


/* Maximum number of channels */

#define FACI_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_FACI_H */

/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_mram.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MRAM_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MRAM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* MRAM Base Address */
#ifndef R_MRAM_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_MRAM_BASE           0x4013c000
#else
#define R_MRAM_BASE           0x5013c000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_MRAM_CH_STRIDE    0x00000004
#define R_MRAM_CH_BASE(ch)   (R_MRAM_BASE + ((uint32_t)(ch) * R_MRAM_CH_STRIDE))

/* MRAM Register Offsets */

#define R_MRAM_MRCPFB_OFFSET     0x00000000  /* Code MRAM Prefetch Buffer Enable Register */
#define R_MRAM_MRCFREQ_OFFSET     0x00000004  /* Code MRAM Frequency Notifications Register */
#define R_MRAM_MREFREQ_OFFSET     0x00000008  /* Extra MRAM Frequency Notifications Register */
#define R_MRAM_MRCDECC_OFFSET     0x00000010  /* Code MRAM ECC Decoder Control Register */
#define R_MRAM_MRCRAEINT_OFFSET     0x00000014  /* Code MRAM Read Access Error Interrupt Enable Register */
#define R_MRAM_MRCRAES_OFFSET     0x00000018  /* Code MRAM Read Access Error Status Register */
#define R_MRAM_MRCRTEA_OFFSET     0x0000001c  /* Code MRAM TED Error Address Register */
#define R_MRAM_MRCRDEA_OFFSET     0x00000020  /* Code MRAM DEC Error Address Register */
#define R_MRAM_MRERAEINT_OFFSET     0x00000034  /* Extra MRAM Read Access Error Interrupt Enable Register */
#define R_MRAM_MRERAES_OFFSET     0x00000038  /* Extra MRAM Read Access Error Status Register */
#define R_MRAM_MRERTEA_OFFSET     0x0000003c  /* Extra MRAM TED Error Address Register */
#define R_MRAM_MRERDEA_OFFSET     0x00000040  /* Extra MRAM DEC Error Address Register */
#define R_MRAM_MSAR_OFFSET     0x00000100  /* MRAM Security Attribution Register */
#define R_MRAM_MREZS_OFFSET     0x00000400  /* Extra MRAM Zeroization Status Register */
#define R_MRAM_MREZC_OFFSET     0x00000404  /* Extra MRAM Zeroization Control Register */
#define R_MRAM_MASTAT_OFFSET     0x00002010  /* Extra MRAM Access Status Register */
#define R_MRAM_MPAEINT_OFFSET     0x00002014  /* Extra MRAM Access Error Interrupt Enable Register */
#define R_MRAM_MRDYIE_OFFSET     0x00002018  /* Extra MRAM Ready Interrupt Enable Register */
#define R_MRAM_MSADDR_OFFSET     0x00002030  /* MACI Command Start Address Register */
#define R_MRAM_MCNTSELR_OFFSET     0x00002048  /* MRAM Counter Select Register */
/* MCNTDTR%s Registers (0-1) */
#define R_MRAM_MCNTDTR0_OFFSET     0x0000204c  /* MRAM Counter Data Register (n = 0, 1) */
#define R_MRAM_MCNTDTR1_OFFSET     0x00002050  /* MRAM Counter Data Register (n = 0, 1) */
#define R_MRAM_MCTRCNTR_OFFSET     0x00002060  /* MRAM Configuration Update Transfer Control Register */
#define R_MRAM_MCTRLSR_OFFSET     0x00002064  /* MRAM Configuration Update Transfer List Select Register */
#define R_MRAM_MCTRSTATR_OFFSET     0x0000206c  /* MRAM Configuration Update Transfer Status Register */
#define R_MRAM_MSTATR_OFFSET     0x00002080  /* Extra MRAM Status Register */
#define R_MRAM_MENTRYR_OFFSET     0x00002084  /* Extra MRAM Program Mode Entry Register */
#define R_MRAM_MSUINITR_OFFSET     0x0000208c  /* Extra MRAM Sequencer Setup Initialization Register */
#define R_MRAM_MCMDR_OFFSET     0x000020a0  /* MACI Command Register */
#define R_MRAM_MSUASMON_OFFSET     0x000020dc  /* MRAM Startup Area Select Monitor Register */
#define R_MRAM_MSUACR_OFFSET     0x000020e8  /* MRAM Startup Area Control Register */
#define R_MRAM_MRPSC_OFFSET     0x00002800  /* MRAM Program Speed Control Register */
#define R_MRAM_MRCPC0_OFFSET     0x00003000  /* Code MRAM Program Control Register */
#define R_MRAM_MRCPC1_OFFSET     0x00003004  /* Code MRAM Program Control Register for Secure */
#define R_MRAM_MRCBPROT0_OFFSET     0x00003008  /* Code MRAM Block Protection Register */
#define R_MRAM_MRCBPROT1_OFFSET     0x0000300c  /* Code MRAM Block Protection Register for Secure */
#define R_MRAM_MRCPS_OFFSET     0x00003010  /* Code MRAM Program Status Register */
#define R_MRAM_MRCPAEINT_OFFSET     0x00003014  /* Code MRAM Program Access Error Interrupt Enable Register */
#define R_MRAM_MRCPEA_OFFSET     0x00003018  /* Code MRAM Program Error Address Register */
#define R_MRAM_MRCFLR_OFFSET     0x00003030  /* Code MRAM Flush Register */
#define R_MRAM_MRCEECC_OFFSET     0x00003804  /* Code MRAM ECC Encoder Control Register */

/* MRAM Register Addresses */

#define R_MRAM_MRCPFB                 (R_MRAM_BASE + R_MRAM_MRCPFB_OFFSET)
#define R_MRAM_MRCFREQ                 (R_MRAM_BASE + R_MRAM_MRCFREQ_OFFSET)
#define R_MRAM_MREFREQ                 (R_MRAM_BASE + R_MRAM_MREFREQ_OFFSET)
#define R_MRAM_MRCDECC                 (R_MRAM_BASE + R_MRAM_MRCDECC_OFFSET)
#define R_MRAM_MRCRAEINT                 (R_MRAM_BASE + R_MRAM_MRCRAEINT_OFFSET)
#define R_MRAM_MRCRAES                 (R_MRAM_BASE + R_MRAM_MRCRAES_OFFSET)
#define R_MRAM_MRCRTEA                 (R_MRAM_BASE + R_MRAM_MRCRTEA_OFFSET)
#define R_MRAM_MRCRDEA                 (R_MRAM_BASE + R_MRAM_MRCRDEA_OFFSET)
#define R_MRAM_MRERAEINT                 (R_MRAM_BASE + R_MRAM_MRERAEINT_OFFSET)
#define R_MRAM_MRERAES                 (R_MRAM_BASE + R_MRAM_MRERAES_OFFSET)
#define R_MRAM_MRERTEA                 (R_MRAM_BASE + R_MRAM_MRERTEA_OFFSET)
#define R_MRAM_MRERDEA                 (R_MRAM_BASE + R_MRAM_MRERDEA_OFFSET)
#define R_MRAM_MSAR                 (R_MRAM_BASE + R_MRAM_MSAR_OFFSET)
#define R_MRAM_MREZS                 (R_MRAM_BASE + R_MRAM_MREZS_OFFSET)
#define R_MRAM_MREZC                 (R_MRAM_BASE + R_MRAM_MREZC_OFFSET)
#define R_MRAM_MASTAT                 (R_MRAM_BASE + R_MRAM_MASTAT_OFFSET)
#define R_MRAM_MPAEINT                 (R_MRAM_BASE + R_MRAM_MPAEINT_OFFSET)
#define R_MRAM_MRDYIE                 (R_MRAM_BASE + R_MRAM_MRDYIE_OFFSET)
#define R_MRAM_MSADDR                 (R_MRAM_BASE + R_MRAM_MSADDR_OFFSET)
#define R_MRAM_MCNTSELR                 (R_MRAM_BASE + R_MRAM_MCNTSELR_OFFSET)
#define R_MRAM_MCNTDTR0                 (R_MRAM_BASE + R_MRAM_MCNTDTR0_OFFSET)
#define R_MRAM_MCNTDTR1                 (R_MRAM_BASE + R_MRAM_MCNTDTR1_OFFSET)
#define R_MRAM_MCTRCNTR                 (R_MRAM_BASE + R_MRAM_MCTRCNTR_OFFSET)
#define R_MRAM_MCTRLSR                 (R_MRAM_BASE + R_MRAM_MCTRLSR_OFFSET)
#define R_MRAM_MCTRSTATR                 (R_MRAM_BASE + R_MRAM_MCTRSTATR_OFFSET)
#define R_MRAM_MSTATR                 (R_MRAM_BASE + R_MRAM_MSTATR_OFFSET)
#define R_MRAM_MENTRYR                 (R_MRAM_BASE + R_MRAM_MENTRYR_OFFSET)
#define R_MRAM_MSUINITR                 (R_MRAM_BASE + R_MRAM_MSUINITR_OFFSET)
#define R_MRAM_MCMDR                 (R_MRAM_BASE + R_MRAM_MCMDR_OFFSET)
#define R_MRAM_MSUASMON                 (R_MRAM_BASE + R_MRAM_MSUASMON_OFFSET)
#define R_MRAM_MSUACR                 (R_MRAM_BASE + R_MRAM_MSUACR_OFFSET)
#define R_MRAM_MRPSC                 (R_MRAM_BASE + R_MRAM_MRPSC_OFFSET)
#define R_MRAM_MRCPC0                 (R_MRAM_BASE + R_MRAM_MRCPC0_OFFSET)
#define R_MRAM_MRCPC1                 (R_MRAM_BASE + R_MRAM_MRCPC1_OFFSET)
#define R_MRAM_MRCBPROT0                 (R_MRAM_BASE + R_MRAM_MRCBPROT0_OFFSET)
#define R_MRAM_MRCBPROT1                 (R_MRAM_BASE + R_MRAM_MRCBPROT1_OFFSET)
#define R_MRAM_MRCPS                 (R_MRAM_BASE + R_MRAM_MRCPS_OFFSET)
#define R_MRAM_MRCPAEINT                 (R_MRAM_BASE + R_MRAM_MRCPAEINT_OFFSET)
#define R_MRAM_MRCPEA                 (R_MRAM_BASE + R_MRAM_MRCPEA_OFFSET)
#define R_MRAM_MRCFLR                 (R_MRAM_BASE + R_MRAM_MRCFLR_OFFSET)
#define R_MRAM_MRCEECC                 (R_MRAM_BASE + R_MRAM_MRCEECC_OFFSET)

/* Register bit definitions */
/* MRCPFB Register bit definitions */
#define R_MRAM_MRCPFB_MPFBEN                      (1 << 0)  /* Code MRAM Prefetch Buffer Enable */

/* MRCFREQ Register bit definitions */
#define R_MRAM_MRCFREQ_MRCMHZ_SHIFT               (0)  /* Code MRAM Frequency Notifications */
#define R_MRAM_MRCFREQ_MRCMHZ_MASK                0x3ff

#define R_MRAM_MRCFREQ_KEY_SHIFT                  (24)  /* Key Code */
#define R_MRAM_MRCFREQ_KEY_MASK                   0xff000000

/* MREFREQ Register bit definitions */
#define R_MRAM_MREFREQ_MREMHZ_SHIFT               (0)  /* Extra MRAM Frequency Notifications */
#define R_MRAM_MREFREQ_MREMHZ_MASK                0xff

#define R_MRAM_MREFREQ_KEY_SHIFT                  (24)  /*  */
#define R_MRAM_MREFREQ_KEY_MASK                   0xff000000

/* MRCDECC Register bit definitions */
#define R_MRAM_MRCDECC_DECDISC                    (1 << 0)  /* Code MRAM ECC Decoder Disable */

#define R_MRAM_MRCDECC_ECCSELC                    (1 << 1)  /* Code MRAM ECC Bits Select */

#define R_MRAM_MRCDECC_KEY_SHIFT                  (8)  /* Key Code */
#define R_MRAM_MRCDECC_KEY_MASK                   0xff00

/* MRCRAEINT Register bit definitions */
#define R_MRAM_MRCRAEINT_INTENBDC                 (1 << 0)  /* Code MRAM DEC Error Interrupt Enable */

#define R_MRAM_MRCRAEINT_INTENBTC                 (1 << 1)  /* Code MRAM TED Error Interrupt Enable */

/* MRCRAES Register bit definitions */
#define R_MRAM_MRCRAES_DECERRC                    (1 << 0)  /* Code MRAM DEC Error Detected */

#define R_MRAM_MRCRAES_TEDERRC                    (1 << 1)  /* Code MRAM TED Error Detected */

/* MRCRTEA Register bit definitions */
#define R_MRAM_MRCRTEA_MRCRTEA_SHIFT              (5)  /* Code MRAM Read Access TED Error Address */
#define R_MRAM_MRCRTEA_MRCRTEA_MASK               0xffffffe0

/* MRCRDEA Register bit definitions */
#define R_MRAM_MRCRDEA_MRCRDEA_SHIFT              (5)  /* Code MRAM Read Access DEC Error Address */
#define R_MRAM_MRCRDEA_MRCRDEA_MASK               0xffffffe0

/* MRERAEINT Register bit definitions */
#define R_MRAM_MRERAEINT_INTENBDE                 (1 << 0)  /* Code MRAM DEC Error Interrupt Enable */

#define R_MRAM_MRERAEINT_INTENBTE                 (1 << 1)  /* Code MRAM TED Error Interrupt Enable */

/* MRERAES Register bit definitions */
#define R_MRAM_MRERAES_DECERRE                    (1 << 0)  /* Extra MRAM DEC Error Detected */

#define R_MRAM_MRERAES_TEDERRE                    (1 << 1)  /* Extra MRAM TED Error Detected */

/* MRERTEA Register bit definitions */
#define R_MRAM_MRERTEA_MRERTEA_SHIFT              (4)  /* Extra MRAM Read Access TED Error Address */
#define R_MRAM_MRERTEA_MRERTEA_MASK               0xfffffff0

/* MRERDEA Register bit definitions */
#define R_MRAM_MRERDEA_MRERDEA_SHIFT              (4)  /* Extra MRAM Read Access DEC Error Address */
#define R_MRAM_MRERDEA_MRERDEA_MASK               0xfffffff0

/* MSAR Register bit definitions */
#define R_MRAM_MSAR_MREECCSA                      (1 << 0)  /* Extra MRAM ECC Register Security Attribution */

#define R_MRAM_MSAR_MREFREQSA                     (1 << 1)  /* MREFREQ Register Security Attribution */

#define R_MRAM_MSAR_MRCECCSA                      (1 << 2)  /* Code MRAM ECC Register Security Attribution */

#define R_MRAM_MSAR_MRCFREQSA                     (1 << 3)  /* MRCFREQ Register Security Attribution */

#define R_MRAM_MSAR_MPFBENSA                      (1 << 4)  /* MRCPFB Register Security Attribution */

#define R_MRAM_MSAR_MACICMISA                     (1 << 9)  /* MACI command Issuing Security Attribution */

#define R_MRAM_MSAR_MACICMRSA                     (1 << 10)  /* MACI Command Registers Security Attribution */

#define R_MRAM_MSAR_MACITRSA                      (1 << 11)  /* MACI Transfer Security Attribution */

#define R_MRAM_MSAR_MRCPSA                        (1 << 13)  /* Code MRAM Program Register Security Attribution */

#define R_MRAM_MSAR_MREPSEQSA                     (1 << 14)  /* EPSEQ Area Register Security Attribution */

#define R_MRAM_MSAR_MRCPSEQSA                     (1 << 15)  /* CPSEQ Area Register Security Attribution */

/* MREZS Register bit definitions */
#define R_MRAM_MREZS_WHUKZF                       (1 << 0)  /* W-HUK Zero Flag Status */

#define R_MRAM_MREZS_WHUKEXE                      (1 << 1)  /* W-HUK Zeroization Executing Status */

/* MREZC Register bit definitions */
#define R_MRAM_MREZC_WHUKZE_SHIFT                 (0)  /* W-HUK Zeroization Execute */
#define R_MRAM_MREZC_WHUKZE_MASK                  0x7
#  define R_MRAM_MREZC_WHUKZE_XX0                         (0 << R_MRAM_MREZC_WHUKZE_SHIFT)  /* W-HUK zeroization not executes */
#  define R_MRAM_MREZC_WHUKZE_111                         (7 << R_MRAM_MREZC_WHUKZE_SHIFT)  /* W-HUK zeroization executes */

#define R_MRAM_MREZC_KEY_SHIFT                    (8)  /* Key Code */
#define R_MRAM_MREZC_KEY_MASK                     0xff00

/* MASTAT Register bit definitions */
#define R_MRAM_MASTAT_MREAE                       (1 << 3)  /* Extra MRAM Access Violation Flag */

#define R_MRAM_MASTAT_CMDLK                       (1 << 4)  /* Command Lock Flag */

/* MPAEINT Register bit definitions */
#define R_MRAM_MPAEINT_MREAEIE                    (1 << 3)  /* Extra MRAM Access Violation Interrupt Enable */

#define R_MRAM_MPAEINT_CMDLKIE                    (1 << 4)  /* Command Lock Interrupt Enable */

/* MRDYIE Register bit definitions */
#define R_MRAM_MRDYIE_MRDYIE                      (1 << 0)  /* Extra MRAM Ready Interrupt Enable */

/* MSADDR Register bit definitions */
#define R_MRAM_MSADDR_MSADDR_SHIFT                (0)  /* Start Address for MACI Command Processing */
#define R_MRAM_MSADDR_MSADDR_MASK                 0xffffffff

/* MCNTSELR Register bit definitions */
#define R_MRAM_MCNTSELR_CNTSEL_SHIFT              (0)  /* Counter select */
#define R_MRAM_MCNTSELR_CNTSEL_MASK               0x7
#  define R_MRAM_MCNTSELR_CNTSEL_000                      (0 << R_MRAM_MCNTSELR_CNTSEL_SHIFT)  /* Anti-rollback counter is not selected. */
#  define R_MRAM_MCNTSELR_CNTSEL_001                      (1 << R_MRAM_MCNTSELR_CNTSEL_SHIFT)  /* ARC_SEC is selected. Counter size is 64 bits. */
#  define R_MRAM_MCNTSELR_CNTSEL_010                      (2 << R_MRAM_MCNTSELR_CNTSEL_SHIFT)  /* ARC_OEMBL is selected. Counter size is 64 bits. */
#  define R_MRAM_MCNTSELR_CNTSEL_011                      (3 << R_MRAM_MCNTSELR_CNTSEL_SHIFT)  /* Anti-rollback counter is not selected. */
#  define R_MRAM_MCNTSELR_CNTSEL_1XX                      (0 << R_MRAM_MCNTSELR_CNTSEL_SHIFT)  /* ARC_NSEC is selected. Counter configuration is 64 or 256 bits. See , , and for details of the counter select condition. */

/* MCNTDTR Register bit definitions */
#define R_MRAM_MCNTDTR_CNTRDAT_SHIFT              (0)  /* Counter Read Data */
#define R_MRAM_MCNTDTR_CNTRDAT_MASK               0xffffffff

/* MCTRCNTR Register bit definitions */
#define R_MRAM_MCTRCNTR_TRTRG                     (1 << 0)  /* Transfer Start Trigger */

#define R_MRAM_MCTRCNTR_KEY_SHIFT                 (8)  /* Key code */
#define R_MRAM_MCTRCNTR_KEY_MASK                  0xff00

/* MCTRLSR Register bit definitions */
#define R_MRAM_MCTRLSR_TRLIST_SHIFT               (0)  /* Configuration Update Transfer List */
#define R_MRAM_MCTRLSR_TRLIST_MASK                0x7
#  define R_MRAM_MCTRLSR_TRLIST_001                       (1 << R_MRAM_MCTRLSR_TRLIST_SHIFT)  /* Transfer list 1 is selected */

/* MCTRSTATR Register bit definitions */
#define R_MRAM_MCTRSTATR_TRBUSY                   (1 << 0)  /* Transfer Busy Status */

#define R_MRAM_MCTRSTATR_TRMD                     (1 << 2)  /* Transfer Mode Setting Status */

/* MSTATR Register bit definitions */
#define R_MRAM_MSTATR_CFGSETERR                   (1 << 5)  /* Configuration Set Error Flag */

#define R_MRAM_MSTATR_PRGERR                      (1 << 12)  /* Programming Error Flag */

#define R_MRAM_MSTATR_ILGLERR                     (1 << 14)  /* Illegal Command Error Flag */

#define R_MRAM_MSTATR_MRDY                        (1 << 15)  /* Extra MRAM Ready Flag */

#define R_MRAM_MSTATR_TZFERR                      (1 << 19)  /* TrustZone Filter Error */

#define R_MRAM_MSTATR_OTERR                       (1 << 20)  /* Other Error */

#define R_MRAM_MSTATR_SECERR                      (1 << 21)  /* Security Error */

#define R_MRAM_MSTATR_ILGCOMERR                   (1 << 23)  /* Illegal Command Error */

/* MENTRYR Register bit definitions */
#define R_MRAM_MENTRYR_MENTRY                     (1 << 7)  /* Extra MRAM Program Mode Entry */

#define R_MRAM_MENTRYR_KEY_SHIFT                  (8)  /*  */
#define R_MRAM_MENTRYR_KEY_MASK                   0xff00

/* MSUINITR Register bit definitions */
#define R_MRAM_MSUINITR_SUINIT                    (1 << 0)  /* Setup Initialization */

#define R_MRAM_MSUINITR_KEY_SHIFT                 (8)  /* Key Code */
#define R_MRAM_MSUINITR_KEY_MASK                  0xff00

/* MCMDR Register bit definitions */
#define R_MRAM_MCMDR_PCMDR_SHIFT                  (0)  /* Pre-command Flag */
#define R_MRAM_MCMDR_PCMDR_MASK                   0xff

#define R_MRAM_MCMDR_CMDR_SHIFT                   (8)  /* Command Flag */
#define R_MRAM_MCMDR_CMDR_MASK                    0xff00

/* MSUASMON Register bit definitions */
#define R_MRAM_MSUASMON_FSPR                      (1 << 15)  /* Protection flag of programming to set boot flag and startup area control */

#define R_MRAM_MSUASMON_BTSIZE_SHIFT              (29)  /* Size of startup area select for boot swap */
#define R_MRAM_MSUASMON_BTSIZE_MASK               0x60000000
#  define R_MRAM_MSUASMON_BTSIZE_00                       (0 << R_MRAM_MSUASMON_BTSIZE_SHIFT)  /* Reserved */
#  define R_MRAM_MSUASMON_BTSIZE_01                       (1 << R_MRAM_MSUASMON_BTSIZE_SHIFT)  /* Startup area size is set to 32 KB */
#  define R_MRAM_MSUASMON_BTSIZE_10                       (2 << R_MRAM_MSUASMON_BTSIZE_SHIFT)  /* Startup area size is set to 16 KB */
#  define R_MRAM_MSUASMON_BTSIZE_11                       (3 << R_MRAM_MSUASMON_BTSIZE_SHIFT)  /* Startup area size is set to 8 KB */

#define R_MRAM_MSUASMON_BTFLG                     (1 << 31)  /* Flag of startup area select for boot swap */

/* MSUACR Register bit definitions */
#define R_MRAM_MSUACR_SAS_SHIFT                   (0)  /* Startup Area Select */
#define R_MRAM_MSUACR_SAS_MASK                    0x3
#  define R_MRAM_MSUACR_SAS_0X                            (0 << R_MRAM_MSUACR_SAS_SHIFT)  /* Startup area is selected by BTFLG bit */
#  define R_MRAM_MSUACR_SAS_10                            (2 << R_MRAM_MSUACR_SAS_SHIFT)  /* Startup area is temporarily switched to the default area */
#  define R_MRAM_MSUACR_SAS_11                            (3 << R_MRAM_MSUACR_SAS_SHIFT)  /* Startup area is temporarily switched to the alternate area */

#define R_MRAM_MSUACR_KEY_SHIFT                   (8)  /* Key Code */
#define R_MRAM_MSUACR_KEY_MASK                    0xff00

/* MRPSC Register bit definitions */
#define R_MRAM_MRPSC_MHSPEN                       (1 << 0)  /* MRAM High-Speed Program Mode Enable */

/* MRCPC0 Register bit definitions */
#define R_MRAM_MRCPC0_MRCPNEN                     (1 << 0)  /* Code MRAM Program Enable for Non-secure */

#define R_MRAM_MRCPC0_KEY_SHIFT                   (8)  /* Key Code */
#define R_MRAM_MRCPC0_KEY_MASK                    0xff00

/* MRCPC1 Register bit definitions */
#define R_MRAM_MRCPC1_MRCPSEN                     (1 << 0)  /* Code MRAM Program Enable for Secure */

#define R_MRAM_MRCPC1_KEY_SHIFT                   (8)  /* Key Code */
#define R_MRAM_MRCPC1_KEY_MASK                    0xff00

/* MRCBPROT0 Register bit definitions */
#define R_MRAM_MRCBPROT0_BPCN0                    (1 << 0)  /* Code MRAM Block Protection Cancel for Non-secure */

#define R_MRAM_MRCBPROT0_KEY_SHIFT                (8)  /* Key Code */
#define R_MRAM_MRCBPROT0_KEY_MASK                 0xff00

/* MRCBPROT1 Register bit definitions */
#define R_MRAM_MRCBPROT1_BPCN1                    (1 << 0)  /* Code MRAM Block Protection Cancel for Secure */

#define R_MRAM_MRCBPROT1_KEY_SHIFT                (8)  /* Key Code */
#define R_MRAM_MRCBPROT1_KEY_MASK                 0xff00

/* MRCPS Register bit definitions */
#define R_MRAM_MRCPS_PRGERRC                      (1 << 0)  /* Programming Error */

#define R_MRAM_MRCPS_ECCERRC                      (1 << 1)  /* ECC Error */

#define R_MRAM_MRCPS_ABUFEMP                      (1 << 5)  /* Address Buffer Empty */

#define R_MRAM_MRCPS_ABUFFULL                     (1 << 6)  /* Address Buffer Full */

#define R_MRAM_MRCPS_PRGBSYC                      (1 << 7)  /* Code MRAM Program Busy */

/* MRCPAEINT Register bit definitions */
#define R_MRAM_MRCPAEINT_MRCAEIE                  (1 << 7)  /* Code MRAM Program Access Error Interrupt Enable */

/* MRCPEA Register bit definitions */
#define R_MRAM_MRCPEA_MCPEA_SHIFT                 (5)  /* Code MRAM Program Error Address */
#define R_MRAM_MRCPEA_MCPEA_MASK                  0xffffffe0

/* MRCFLR Register bit definitions */
#define R_MRAM_MRCFLR_MRCFL                       (1 << 0)  /* Flush Write Data Buffer for Code MRAM */

#define R_MRAM_MRCFLR_KEY_SHIFT                   (8)  /* Key Code */
#define R_MRAM_MRCFLR_KEY_MASK                    0xff00

/* MRCEECC Register bit definitions */
#define R_MRAM_MRCEECC_ECCBYPC                    (1 << 0)  /* Code MRAM ECC Encoder Outputs Bypass Enable */

#define R_MRAM_MRCEECC_KEY_SHIFT                  (8)  /* Key Code */
#define R_MRAM_MRCEECC_KEY_MASK                   0xff00


/* Maximum number of channels */

#define MRAM_MAX_CHANNELS    2

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MRAM_H */

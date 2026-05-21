/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_mrms.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MRMS_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MRMS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* MRMS Base Address */
#ifndef R_MRMS_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_MRMS_BASE           0x4013c000
#else
#define R_MRMS_BASE           0x5013c000
#endif
#endif

/* MRMS Register Offsets */

#define R_MRMS_MRCPFB_OFFSET                      0x00000000  /* Code MRAM Pre-Fetch Buffer Enable Register */
#define R_MRMS_MRCFREQ_OFFSET                     0x00000004  /* Code MRAM Frequency Notifications Register  */
#define R_MRMS_MREFREQ_OFFSET                     0x00000008  /* Extra MRAM Frequency Notifications Register  */
#define R_MRMS_MRCDECC_OFFSET                     0x00000010  /* Code MRAM ECC Decoder Control Register  */
#define R_MRMS_MRCRAEINT_OFFSET                   0x00000014  /* Code MRAM Read Access Error Interrupt Enable Register */
#define R_MRMS_MRCRAES_OFFSET                     0x00000018  /* Code MRAM Read Access Error Status Register */
#define R_MRMS_MRCRTEA_OFFSET                     0x0000001c  /* Code MRAM TED Error Address Register  */
#define R_MRMS_MRCRDEA_OFFSET                     0x00000020  /* Code MRAM DEC Error Address Register */
#define R_MRMS_MRERAINT_OFFSET                    0x00000034  /* Extra MRAM Read Access Error Interrupt Enable Register */
#define R_MRMS_MRERAES_OFFSET                     0x00000038  /* Extra MRAM Read Access Error Status Register  */
#define R_MRMS_MRERTEA_OFFSET                     0x0000003c  /* Extra MRAM TED Error Address Register  */
#define R_MRMS_MRERDEA_OFFSET                     0x00000040  /* Extra MRAM DEC Error Address Register */
#define R_MRMS_MSAR_OFFSET                        0x00000100  /* MRAM Security Attribution Register */
#define R_MRMS_MREZS_OFFSET                       0x00000400  /* Extra MRAM Zeroization Status Register  */
#define R_MRMS_MREZC_OFFSET                       0x00000404  /* Extra MRAM Zeroization Control Register  */
#define R_MRMS_MASTAT_OFFSET                      0x00002010  /* Extra MRAM Access Status Register */
#define R_MRMS_MPAEINT_OFFSET                     0x00002014  /* Extra MRAM Access Error Interrupt Enable Register */
#define R_MRMS_MRDYIE_OFFSET                      0x00002018  /* Extra MRAM Ready Interrupt Enable Register */
#define R_MRMS_MSADDR_OFFSET                      0x00002030  /* MACI Command Start Address Register */
#define R_MRMS_MCNTSELR_OFFSET                    0x00002048  /* MRAM Counter Select Register */
#define R_MRMS_MCNTDTR0_OFFSET                    0x0000204c  /* MRAM Counter Data Register 0 */
#define R_MRMS_MCNTDTR1_OFFSET                    0x00002050  /* MRAM Counter Data Register 1 */
#define R_MRMS_MCTRCNTR_OFFSET                    0x00002060  /* MRAM Configuration Update Transfer Control Register */
#define R_MRMS_MCTRLSR_OFFSET                     0x00002064  /* MRAM Configuration Update Transfer List Select Register */
#define R_MRMS_MCTRSTATR_OFFSET                   0x0000206c  /* MRAM Configuration Update Transfer Status Register */
#define R_MRMS_MSTATR_OFFSET                      0x00002080  /* Extra MRAM Status Register */
#define R_MRMS_MENTRYR_OFFSET                     0x00002084  /* Extra MRAM Program Mode Entry Register  */
#define R_MRMS_MSUINITR_OFFSET                    0x0000208c  /* Extra MRAM Sequencer Set-Up Initialization Register  */
#define R_MRMS_MCMDR_OFFSET                       0x000020a0  /* MACI Command Register */
#define R_MRMS_MSUASMON_OFFSET                    0x000020dc  /* MRAM Start-Up Area Select Monitor Register */
#define R_MRMS_MSUACR_OFFSET                      0x000020e8  /* MRAM Start-Up Area Control Register */
#define R_MRMS_MRPSC_OFFSET                       0x00002800  /* MRAM Program Speed Control Register  */
#define R_MRMS_MRCPC0_OFFSET                      0x00003000  /* Code MRAM Program Control Register  */
#define R_MRMS_MRCPC1_OFFSET                      0x00003004  /* Code MRAM Program Control for Secure Register  */
#define R_MRMS_MRCBPROT0_OFFSET                   0x00003008  /* Code MRAM Block Protection Register */
#define R_MRMS_MRCBPROT1_OFFSET                   0x0000300c  /* Code MRAM Block Protection for Secure Register */
#define R_MRMS_MRCPS_OFFSET                       0x00003010  /* Code MRAM Program Status Register */
#define R_MRMS_MRCPAEINT_OFFSET                   0x00003014  /* Code MRAM Program Access Error Interrupt Enable Register  */
#define R_MRMS_MRCPEA_OFFSET                      0x00003018  /* Code MRAM Program Error Address Register */
#define R_MRMS_MRCFLR_OFFSET                      0x00003030  /* Code MRAM Flush Register */
#define R_MRMS_MRCEECC_OFFSET                     0x00003804  /* Code MRAM ECC Encoder Control Register  */

/* MRMS Register Addresses */

#define R_MRMS_MRCPFB                             (R_MRMS_BASE + R_MRMS_MRCPFB_OFFSET)
#define R_MRMS_MRCFREQ                            (R_MRMS_BASE + R_MRMS_MRCFREQ_OFFSET)
#define R_MRMS_MREFREQ                            (R_MRMS_BASE + R_MRMS_MREFREQ_OFFSET)
#define R_MRMS_MRCDECC                            (R_MRMS_BASE + R_MRMS_MRCDECC_OFFSET)
#define R_MRMS_MRCRAEINT                          (R_MRMS_BASE + R_MRMS_MRCRAEINT_OFFSET)
#define R_MRMS_MRCRAES                            (R_MRMS_BASE + R_MRMS_MRCRAES_OFFSET)
#define R_MRMS_MRCRTEA                            (R_MRMS_BASE + R_MRMS_MRCRTEA_OFFSET)
#define R_MRMS_MRCRDEA                            (R_MRMS_BASE + R_MRMS_MRCRDEA_OFFSET)
#define R_MRMS_MRERAINT                           (R_MRMS_BASE + R_MRMS_MRERAINT_OFFSET)
#define R_MRMS_MRERAES                            (R_MRMS_BASE + R_MRMS_MRERAES_OFFSET)
#define R_MRMS_MRERTEA                            (R_MRMS_BASE + R_MRMS_MRERTEA_OFFSET)
#define R_MRMS_MRERDEA                            (R_MRMS_BASE + R_MRMS_MRERDEA_OFFSET)
#define R_MRMS_MSAR                               (R_MRMS_BASE + R_MRMS_MSAR_OFFSET)
#define R_MRMS_MREZS                              (R_MRMS_BASE + R_MRMS_MREZS_OFFSET)
#define R_MRMS_MREZC                              (R_MRMS_BASE + R_MRMS_MREZC_OFFSET)
#define R_MRMS_MASTAT                             (R_MRMS_BASE + R_MRMS_MASTAT_OFFSET)
#define R_MRMS_MPAEINT                            (R_MRMS_BASE + R_MRMS_MPAEINT_OFFSET)
#define R_MRMS_MRDYIE                             (R_MRMS_BASE + R_MRMS_MRDYIE_OFFSET)
#define R_MRMS_MSADDR                             (R_MRMS_BASE + R_MRMS_MSADDR_OFFSET)
#define R_MRMS_MCNTSELR                           (R_MRMS_BASE + R_MRMS_MCNTSELR_OFFSET)
#define R_MRMS_MCNTDTR0                           (R_MRMS_BASE + R_MRMS_MCNTDTR0_OFFSET)
#define R_MRMS_MCNTDTR1                           (R_MRMS_BASE + R_MRMS_MCNTDTR1_OFFSET)
#define R_MRMS_MCTRCNTR                           (R_MRMS_BASE + R_MRMS_MCTRCNTR_OFFSET)
#define R_MRMS_MCTRLSR                            (R_MRMS_BASE + R_MRMS_MCTRLSR_OFFSET)
#define R_MRMS_MCTRSTATR                          (R_MRMS_BASE + R_MRMS_MCTRSTATR_OFFSET)
#define R_MRMS_MSTATR                             (R_MRMS_BASE + R_MRMS_MSTATR_OFFSET)
#define R_MRMS_MENTRYR                            (R_MRMS_BASE + R_MRMS_MENTRYR_OFFSET)
#define R_MRMS_MSUINITR                           (R_MRMS_BASE + R_MRMS_MSUINITR_OFFSET)
#define R_MRMS_MCMDR                              (R_MRMS_BASE + R_MRMS_MCMDR_OFFSET)
#define R_MRMS_MSUASMON                           (R_MRMS_BASE + R_MRMS_MSUASMON_OFFSET)
#define R_MRMS_MSUACR                             (R_MRMS_BASE + R_MRMS_MSUACR_OFFSET)
#define R_MRMS_MRPSC                              (R_MRMS_BASE + R_MRMS_MRPSC_OFFSET)
#define R_MRMS_MRCPC0                             (R_MRMS_BASE + R_MRMS_MRCPC0_OFFSET)
#define R_MRMS_MRCPC1                             (R_MRMS_BASE + R_MRMS_MRCPC1_OFFSET)
#define R_MRMS_MRCBPROT0                          (R_MRMS_BASE + R_MRMS_MRCBPROT0_OFFSET)
#define R_MRMS_MRCBPROT1                          (R_MRMS_BASE + R_MRMS_MRCBPROT1_OFFSET)
#define R_MRMS_MRCPS                              (R_MRMS_BASE + R_MRMS_MRCPS_OFFSET)
#define R_MRMS_MRCPAEINT                          (R_MRMS_BASE + R_MRMS_MRCPAEINT_OFFSET)
#define R_MRMS_MRCPEA                             (R_MRMS_BASE + R_MRMS_MRCPEA_OFFSET)
#define R_MRMS_MRCFLR                             (R_MRMS_BASE + R_MRMS_MRCFLR_OFFSET)
#define R_MRMS_MRCEECC                            (R_MRMS_BASE + R_MRMS_MRCEECC_OFFSET)

/* Register bit definitions */
/* MRCPFB Register bit definitions */
#define R_MRMS_MRCPFB_MPFBEN                      (1 << 0)  /* MRAM Pre-Fetch Buffer enable. */

/* MRCFREQ Register bit definitions */
#define R_MRMS_MRCFREQ_MRCMHZ_SHIFT               (0)  /* Setting the operating frequency in the order of MHz */
#define R_MRMS_MRCFREQ_MRCMHZ_MASK                0x3ff

#define R_MRMS_MRCFREQ_KEY_SHIFT                  (24)  /* Key Code */
#define R_MRMS_MRCFREQ_KEY_MASK                   0xff000000

/* MREFREQ Register bit definitions */
#define R_MRMS_MREFREQ_MREMHZ_SHIFT               (0)  /* Setting the operating frequency in the order of MHz */
#define R_MRMS_MREFREQ_MREMHZ_MASK                0xff

#define R_MRMS_MREFREQ_KEY_SHIFT                  (24)  /* Key Code */
#define R_MRMS_MREFREQ_KEY_MASK                   0xff000000

/* MRCDECC Register bit definitions */
#define R_MRMS_MRCDECC_DECDISC                    (1 << 0)  /* MRC ECC Decoder disable */

#define R_MRMS_MRCDECC_ECCSELC                    (1 << 1)  /* MRC ECC Data select */

#define R_MRMS_MRCDECC_KEY_SHIFT                  (8)  /* Key Code */
#define R_MRMS_MRCDECC_KEY_MASK                   0xff00

/* MRCRAEINT Register bit definitions */
#define R_MRMS_MRCRAEINT_INTENBDC                 (1 << 0)  /* MRC DEC error interrupt enable. */

#define R_MRMS_MRCRAEINT_INTENBTC                 (1 << 1)  /* MRC TED error interrupt enable. */

/* MRCRAES Register bit definitions */
#define R_MRMS_MRCRAES_DECERRC                    (1 << 0)  /* MRC DEC error detected. */

#define R_MRMS_MRCRAES_TEDERRC                    (1 << 1)  /* MRC TED error detected. */

/* MRCRTEA Register bit definitions */
#define R_MRMS_MRCRTEA_MRCRTEA_SHIFT              (5)  /* MRC read access TED error Address. */
#define R_MRMS_MRCRTEA_MRCRTEA_MASK               0xffffffe0

/* MRCRDEA Register bit definitions */
#define R_MRMS_MRCRDEA_MRCRDEA_SHIFT              (5)  /* MRC read access DEC error Address. */
#define R_MRMS_MRCRDEA_MRCRDEA_MASK               0xffffffe0

/* MRERAINT Register bit definitions */
#define R_MRMS_MRERAINT_INTENBDE                  (1 << 0)  /* MRE DEC error interrupt enable. */

#define R_MRMS_MRERAINT_INTENBTE                  (1 << 1)  /* MRE TED error interrupt enable. */

/* MRERAES Register bit definitions */
#define R_MRMS_MRERAES_DECERRE                    (1 << 0)  /* MRE DEC error detected. */

#define R_MRMS_MRERAES_TEDERRE                    (1 << 1)  /* MRE TED error detected. */

/* MRERTEA Register bit definitions */
#define R_MRMS_MRERTEA_MRERTEA_SHIFT              (4)  /* MRE read access TED error Address. */
#define R_MRMS_MRERTEA_MRERTEA_MASK               0xfffffff0

/* MRERDEA Register bit definitions */
#define R_MRMS_MRERDEA_MRERDEA_SHIFT              (4)  /* MRE read access DEC error Address. */
#define R_MRMS_MRERDEA_MRERDEA_MASK               0xfffffff0

/* MSAR Register bit definitions */
#define R_MRMS_MSAR_MREECCSA                      (1 << 0)  /* Extra MRAM ECC Register Security Attribution */

#define R_MRMS_MSAR_MREFREQSA                     (1 << 1)  /* MREFREQ register Security Attribution */

#define R_MRMS_MSAR_MRCECCSA                      (1 << 2)  /* Code MRAM ECC Register Security Attribution */

#define R_MRMS_MSAR_MRCFREQSA                     (1 << 3)  /* MRCFREQ register Security Attribution */

#define R_MRMS_MSAR_MPFBENSA                      (1 << 4)  /* MRCPFB register Security Attribution */

#define R_MRMS_MSAR_MACICMISA                     (1 << 9)  /* MACI Command Issuing Security Attribution */

#define R_MRMS_MSAR_MACICMRSA                     (1 << 10)  /* MACI Command Registers Security Attribution */

#define R_MRMS_MSAR_MACITRSA                      (1 << 11)  /* MACI Transfer Security Attribution */

#define R_MRMS_MSAR_MRCPSA                        (1 << 13)  /* Code MRAM Program Register Security Attribution */

#define R_MRMS_MSAR_MREPSEQSA                     (1 << 14)  /* EPSEQ Area Register Security Attribution */

#define R_MRMS_MSAR_MRCPSEQSA                     (1 << 15)  /* CPSEQ Area Register Security Attribution */

#define R_MRMS_MSAR_MREPSEQSA                     (1 << 14)  /* EPSEQ Area Register Security Attribution */

/* MREZS Register bit definitions */
#define R_MRMS_MREZS_WHUKZF                       (1 << 0)  /* W-HUK Zero Flag Status. */

#define R_MRMS_MREZS_WHUKEXE                      (1 << 1)  /* W-HUK Zeroization Executing Status */

/* MREZC Register bit definitions */
#define R_MRMS_MREZC_WHUKZE_SHIFT                 (0)  /* W-KUK zeroization execute. */
#define R_MRMS_MREZC_WHUKZE_MASK                  0x7

#define R_MRMS_MREZC_KEY_SHIFT                    (8)  /* Key Code */
#define R_MRMS_MREZC_KEY_MASK                     0xff00

/* MASTAT Register bit definitions */
#define R_MRMS_MASTAT_MREAE                       (1 << 3)  /* Extra MRAM Access Error */

#define R_MRMS_MASTAT_CMDLK                       (1 << 4)  /* Command Lock */

/* MPAEINT Register bit definitions */
#define R_MRMS_MPAEINT_MREAEIE                    (1 << 3)  /* MRE Access Error Interrupt Enable */

#define R_MRMS_MPAEINT_CMDLKIE                    (1 << 4)  /* Command Lock Interrupt Enable */

/* MRDYIE Register bit definitions */
#define R_MRMS_MRDYIE_MRDYIE                      (1 << 0)  /* MRDY Interrupt Enable */

/* MSADDR Register bit definitions */
#define R_MRMS_MSADDR_MSADDR_SHIFT                (0)  /* Start Address for MACI Command Processing */
#define R_MRMS_MSADDR_MSADDR_MASK                 0xffffffff

/* MCNTSELR Register bit definitions */
#define R_MRMS_MCNTSELR_CNTSEL_SHIFT              (0)  /* Counter Select */
#define R_MRMS_MCNTSELR_CNTSEL_MASK               0x7

/* MCNTDTR0 Register bit definitions */
#define R_MRMS_MCNTDTR0_CNTRDAT_SHIFT             (0)  /* Counter Read Data */
#define R_MRMS_MCNTDTR0_CNTRDAT_MASK              0xffffffff

/* MCNTDTR1 Register bit definitions */
#define R_MRMS_MCNTDTR1_CNTRDAT_SHIFT             (0)  /* Counter Read Data */
#define R_MRMS_MCNTDTR1_CNTRDAT_MASK              0xffffffff

/* MCTRCNTR Register bit definitions */
#define R_MRMS_MCTRCNTR_TRTRG                     (1 << 0)  /* Transfer Start Trigger */

#define R_MRMS_MCTRCNTR_KEY_SHIFT                 (8)  /* Key Code */
#define R_MRMS_MCTRCNTR_KEY_MASK                  0xff00

/* MCTRLSR Register bit definitions */
#define R_MRMS_MCTRLSR_TRLIST_SHIFT               (0)  /* Configuration Update Transfer List */
#define R_MRMS_MCTRLSR_TRLIST_MASK                0x7

/* MCTRSTATR Register bit definitions */
#define R_MRMS_MCTRSTATR_TRBUSY                   (1 << 0)  /* Transfer Busy Status */

#define R_MRMS_MCTRSTATR_TRMD                     (1 << 2)  /* Transfer Mode Setting Status */

/* MSTATR Register bit definitions */
#define R_MRMS_MSTATR_CFGSETERR                   (1 << 5)  /* Configuration Set Error Flag */

#define R_MRMS_MSTATR_PRGERR                      (1 << 12)  /* Programming Error */

#define R_MRMS_MSTATR_ILGLERR                     (1 << 14)  /* Illegal Error */

#define R_MRMS_MSTATR_MRDY                        (1 << 15)  /* MRE Ready */

#define R_MRMS_MSTATR_TZFERR                      (1 << 19)  /* TrustZone Filter Error */

#define R_MRMS_MSTATR_OTERR                       (1 << 20)  /* Other Error */

#define R_MRMS_MSTATR_SECERR                      (1 << 21)  /* Security Error */

#define R_MRMS_MSTATR_ILGCOMERR                   (1 << 23)  /* Illegal Command Error */

/* MENTRYR Register bit definitions */
#define R_MRMS_MENTRYR_MENTRY                     (1 << 7)  /* Extra MRAM Mode Entry */

#define R_MRMS_MENTRYR_KEY_SHIFT                  (8)  /* Key Code */
#define R_MRMS_MENTRYR_KEY_MASK                   0xff00

/* MSUINITR Register bit definitions */
#define R_MRMS_MSUINITR_SUINIT                    (1 << 0)  /* Set-up Initialization */

#define R_MRMS_MSUINITR_KEY_SHIFT                 (8)  /* Key Code */
#define R_MRMS_MSUINITR_KEY_MASK                  0xff00

/* MCMDR Register bit definitions */
#define R_MRMS_MCMDR_PCMDR_SHIFT                  (0)  /* Pre-command Flag */
#define R_MRMS_MCMDR_PCMDR_MASK                   0xff

#define R_MRMS_MCMDR_CMDR_SHIFT                   (8)  /* Command Flag */
#define R_MRMS_MCMDR_CMDR_MASK                    0xff00

/* MSUASMON Register bit definitions */
#define R_MRMS_MSUASMON_FSPR                      (1 << 15)  /* Protection Flag of programing to set the Start-Up Area Select setting */

#define R_MRMS_MSUASMON_BTSIZE_SHIFT              (29)  /* Size of Start-Up area select for Boot Swap */
#define R_MRMS_MSUASMON_BTSIZE_MASK               0x60000000

#define R_MRMS_MSUASMON_BTFLG                     (1 << 31)  /* Flag of Start-Up area select for Boot Swap */

/* MSUACR Register bit definitions */
#define R_MRMS_MSUACR_SAS_SHIFT                   (0)  /* Start Up Area Select */
#define R_MRMS_MSUACR_SAS_MASK                    0x3
#  define R_MRMS_MSUACR_SAS_10                            (2 << R_MRMS_MSUACR_SAS_SHIFT)  /* Start-up area is temporarily switched to the default area */
#  define R_MRMS_MSUACR_SAS_11                            (3 << R_MRMS_MSUACR_SAS_SHIFT)  /* Start-up area is temporarily switched to the alternate area */

#define R_MRMS_MSUACR_KEY_SHIFT                   (8)  /* Key Code */
#define R_MRMS_MSUACR_KEY_MASK                    0xff00

/* MRPSC Register bit definitions */
#define R_MRMS_MRPSC_MHSPEN                       (1 << 0)  /* MRAM high speed program mode enable. */

/* MRCPC0 Register bit definitions */
#define R_MRMS_MRCPC0_MRCPNEN                     (1 << 0)  /* Code MRAM Program Enable for Non-secure */

#define R_MRMS_MRCPC0_KEY_SHIFT                   (8)  /* Key Code */
#define R_MRMS_MRCPC0_KEY_MASK                    0xff00

/* MRCPC1 Register bit definitions */
#define R_MRMS_MRCPC1_MRCPSEN                     (1 << 0)  /* Code MRAM Program Enable for Secure */

#define R_MRMS_MRCPC1_KEY_SHIFT                   (8)  /* Key Code */
#define R_MRMS_MRCPC1_KEY_MASK                    0xff00

/* MRCBPROT0 Register bit definitions */
#define R_MRMS_MRCBPROT0_BPCN0                    (1 << 0)  /* Code MRAM Block Protection Cancel for Non-secure */

#define R_MRMS_MRCBPROT0_KEY_SHIFT                (8)  /* Key Code */
#define R_MRMS_MRCBPROT0_KEY_MASK                 0xff00

/* MRCBPROT1 Register bit definitions */
#define R_MRMS_MRCBPROT1_BPCN1                    (1 << 0)  /* Code MRAM Block Protection Cancel for Secure */

#define R_MRMS_MRCBPROT1_KEY_SHIFT                (8)  /* Key Code */
#define R_MRMS_MRCBPROT1_KEY_MASK                 0xff00

/* MRCPS Register bit definitions */
#define R_MRMS_MRCPS_PRGERRC                      (1 << 0)  /* Programming Error */

#define R_MRMS_MRCPS_ECCERRC                      (1 << 1)  /* ECC Error */

#define R_MRMS_MRCPS_ABUFEMP                      (1 << 5)  /* Address Buffer Empty */

#define R_MRMS_MRCPS_ABUFFULL                     (1 << 6)  /* Address Buffer Full */

#define R_MRMS_MRCPS_PRGBSYC                      (1 << 7)  /* Code MRAM Program Busy */

/* MRCPAEINT Register bit definitions */
#define R_MRMS_MRCPAEINT_MRCAEIE                  (1 << 7)  /* Code MRAM Program Access Error Interrupt Enable */

/* MRCPEA Register bit definitions */
#define R_MRMS_MRCPEA_MCPEA_SHIFT                 (5)  /* Code MRAM Program Error Address */
#define R_MRMS_MRCPEA_MCPEA_MASK                  0xffffffe0

/* MRCFLR Register bit definitions */
#define R_MRMS_MRCFLR_MRCFL                       (1 << 0)  /* Flush Write Data Buffer for code MRAM */

#define R_MRMS_MRCFLR_KEY_SHIFT                   (8)  /* Key Code */
#define R_MRMS_MRCFLR_KEY_MASK                    0xff00

/* MRCEECC Register bit definitions */
#define R_MRMS_MRCEECC_ECCBYPC                    (1 << 0)  /* Code MRAM ECC encoder outputs bypass enable */

#define R_MRMS_MRCEECC_KEY_SHIFT                  (8)  /* Key Code */
#define R_MRMS_MRCEECC_KEY_MASK                   0xff00


/* Maximum number of channels */

#define MRMS_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MRMS_H */

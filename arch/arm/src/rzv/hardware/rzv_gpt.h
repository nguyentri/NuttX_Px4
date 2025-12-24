/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_gpt.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_GPT_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_GPT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPT Base Addresses ****************************************************/

#ifndef RZV_GPT0_BASE
#  define RZV_GPT0_BASE               0x13010000
#endif
#ifndef RZV_GPT1_BASE
#  define RZV_GPT1_BASE               0x13010100
#endif
#ifndef RZV_GPT10_BASE
#  define RZV_GPT10_BASE              0x13020000
#endif
#ifndef RZV_GPT11_BASE
#  define RZV_GPT11_BASE              0x13020100
#endif
#ifndef RZV_GPT12_BASE
#  define RZV_GPT12_BASE              0x13020200
#endif
#ifndef RZV_GPT13_BASE
#  define RZV_GPT13_BASE              0x13020300
#endif
#ifndef RZV_GPT14_BASE
#  define RZV_GPT14_BASE              0x13020400
#endif
#ifndef RZV_GPT15_BASE
#  define RZV_GPT15_BASE              0x13020500
#endif
#ifndef RZV_GPT16_BASE
#  define RZV_GPT16_BASE              0x13020600
#endif
#ifndef RZV_GPT17_BASE
#  define RZV_GPT17_BASE              0x13020700
#endif
#ifndef RZV_GPT2_BASE
#  define RZV_GPT2_BASE               0x13010200
#endif
#ifndef RZV_GPT3_BASE
#  define RZV_GPT3_BASE               0x13010300
#endif
#ifndef RZV_GPT4_BASE
#  define RZV_GPT4_BASE               0x13010400
#endif
#ifndef RZV_GPT5_BASE
#  define RZV_GPT5_BASE               0x13010500
#endif
#ifndef RZV_GPT6_BASE
#  define RZV_GPT6_BASE               0x13010600
#endif
#ifndef RZV_GPT7_BASE
#  define RZV_GPT7_BASE               0x13010700
#endif
#ifndef RZV_GPT8_BASE
#  define RZV_GPT8_BASE               0x13010800
#endif
#ifndef RZV_GPT9_BASE
#  define RZV_GPT9_BASE               0x13010900
#endif

#define RZV_GPT_CHANNEL_MASK(ch)      (1u << (ch))

/* GPT Register Offsets ***************************************************/

/* GTEITLI%s Registers (1-2) */
#define RZV_GPT_GTEITLI_OFFSET(m)               (0x000000a8 + ((m) * 0x00000004))  /* GTEITLI Register %s */
#define RZV_GPT_GTWP_OFFSET                              0x0000  /* GPT Write Protect Register */
#define RZV_GPT_GTSTR_OFFSET                             0x0004  /* GPT Start Register */
#define RZV_GPT_GTSTP_OFFSET                             0x0008  /* GPT Stop Register */
#define RZV_GPT_GTCLR_OFFSET                             0x000C  /* GPT Software Clear Register */
#define RZV_GPT_GTSSR_OFFSET                             0x0010  /* GPT Start Source Select Register */
#define RZV_GPT_GTPSR_OFFSET                             0x0014  /* GPT Stop Source Select Register */
#define RZV_GPT_GTCSR_OFFSET                             0x0018  /* GPT Clear Source Select Register */
#define RZV_GPT_GTUPSR_OFFSET                            0x001C  /* GPT Up Count Source Select Register */
#define RZV_GPT_GTDNSR_OFFSET                            0x0020  /* GPT Down Count Source Select Register */
#define RZV_GPT_GTICASR_OFFSET                           0x0024  /* GPT Input Capture Source Select Register A */
#define RZV_GPT_GTICBSR_OFFSET                           0x0028  /* GPT Input Capture Source Select Register B */
#define RZV_GPT_GTCR_OFFSET                              0x002C  /* GPT Control Register */
#define RZV_GPT_GTUDDTYC_OFFSET                          0x0030  /* GPT Count Direction and Duty Setting Register */
#define RZV_GPT_GTIOR_OFFSET                             0x0034  /* GPT I/O Control Register */
#define RZV_GPT_GTINTAD_OFFSET                           0x0038  /* GPT Interrupt Output Setting Register */
#define RZV_GPT_GTST_OFFSET                              0x003C  /* GPT Status Register */
#define RZV_GPT_GTBER_OFFSET                             0x0040  /* GPT Buffer Enable Register */
#define RZV_GPT_GTITC_OFFSET                             0x0044  /* GPT Interrupt and Capture Setting Register */
#define RZV_GPT_GTCNT_OFFSET                             0x0048  /* GPT Counter */
#define RZV_GPT_GTCCRA_OFFSET                            0x004C  /* GPT Capture/Compare Register A */
#define RZV_GPT_GTCCRB_OFFSET                            0x0050  /* GPT Capture/Compare Register B */
#define RZV_GPT_GTCCRC_OFFSET                            0x0054  /* GPT Compare Register C */
#define RZV_GPT_GTCCRE_OFFSET                            0x0058  /* GPT Compare Register E */
#define RZV_GPT_GTCCRD_OFFSET                            0x005C  /* GPT Compare Register D */
#define RZV_GPT_GTCCRF_OFFSET                            0x0060  /* GPT Compare Register F */
#define RZV_GPT_GTPR_OFFSET                              0x0064  /* GPT Cycle Setting Register */
#define RZV_GPT_GTPBR_OFFSET                             0x0068  /* GPT Cycle Setting Buffer Register */
#define RZV_GPT_GTPDBR_OFFSET                            0x006C  /* GPT Dead Time Buffer Register */
#define RZV_GPT_GTADTRA_OFFSET                           0x0070  /* GPT A/D Converter Start Request Timing Register A */
#define RZV_GPT_GTADTBRA_OFFSET                          0x0074  /* GPT A/D Converter Start Request Timing Buffer Register A */
#define RZV_GPT_GTADTDBRA_OFFSET                         0x0078  /* GPT A/D Converter Start Request Timing Dead Time Buffer Register A */
#define RZV_GPT_GTADTRB_OFFSET                           0x007C  /* GPT A/D Converter Start Request Timing Register B */
#define RZV_GPT_GTADTBRB_OFFSET                          0x0080  /* GPT A/D Converter Start Request Timing Buffer Register B */
#define RZV_GPT_GTADTDBRB_OFFSET                         0x0084  /* GPT A/D Converter Start Request Timing Dead Time Buffer Register B */
#define RZV_GPT_GTDTCR_OFFSET                            0x0088  /* GTDTCR */
#define RZV_GPT_GTDVU_OFFSET                             0x008C  /* GTDVU */
#define RZV_GPT_GTDVD_OFFSET                             0x0090  /* GTDVD */
#define RZV_GPT_GTDBU_OFFSET                             0x0094  /* GTDBU */
#define RZV_GPT_GTDBB_OFFSET                             0x0098  /* GTDBB */
#define RZV_GPT_GTSOS_OFFSET                             0x009C  /* GTSOS */
#define RZV_GPT_GTSOTR_OFFSET                            0x00A0  /* GTSOTR */
#define RZV_GPT_GTEITC_OFFSET                            0x00A8  /* GTEITC */
#define RZV_GPT_GTEITLB_OFFSET                           0x00B4  /* GTEITLB */
#define RZV_GPT_GTICLF_OFFSET                            0x00B8  /* GTICLF */
#define RZV_GPT_GTSECSR_OFFSET                           0x00D0  /* GTSECSR */
#define RZV_GPT_GTSECR_OFFSET                            0x00D4  /* GTSECR */

/* GPT Register Addresses **************************************************/

#define RZV_GPT_GTEITLI(ch,m)                   (RZV_GPT##ch##_BASE + RZV_GPT_GTEITLI_OFFSET(m))
#define RZV_GPT_GTWP(ch)                             (RZV_GPT##ch##_BASE + RZV_GPT_GTWP_OFFSET)
#define RZV_GPT_GTSTR(ch)                            (RZV_GPT##ch##_BASE + RZV_GPT_GTSTR_OFFSET)
#define RZV_GPT_GTSTP(ch)                            (RZV_GPT##ch##_BASE + RZV_GPT_GTSTP_OFFSET)
#define RZV_GPT_GTCLR(ch)                            (RZV_GPT##ch##_BASE + RZV_GPT_GTCLR_OFFSET)
#define RZV_GPT_GTSSR(ch)                            (RZV_GPT##ch##_BASE + RZV_GPT_GTSSR_OFFSET)
#define RZV_GPT_GTPSR(ch)                            (RZV_GPT##ch##_BASE + RZV_GPT_GTPSR_OFFSET)
#define RZV_GPT_GTCSR(ch)                            (RZV_GPT##ch##_BASE + RZV_GPT_GTCSR_OFFSET)
#define RZV_GPT_GTUPSR(ch)                           (RZV_GPT##ch##_BASE + RZV_GPT_GTUPSR_OFFSET)
#define RZV_GPT_GTDNSR(ch)                           (RZV_GPT##ch##_BASE + RZV_GPT_GTDNSR_OFFSET)
#define RZV_GPT_GTICASR(ch)                          (RZV_GPT##ch##_BASE + RZV_GPT_GTICASR_OFFSET)
#define RZV_GPT_GTICBSR(ch)                          (RZV_GPT##ch##_BASE + RZV_GPT_GTICBSR_OFFSET)
#define RZV_GPT_GTCR(ch)                             (RZV_GPT##ch##_BASE + RZV_GPT_GTCR_OFFSET)
#define RZV_GPT_GTUDDTYC(ch)                         (RZV_GPT##ch##_BASE + RZV_GPT_GTUDDTYC_OFFSET)
#define RZV_GPT_GTIOR(ch)                            (RZV_GPT##ch##_BASE + RZV_GPT_GTIOR_OFFSET)
#define RZV_GPT_GTINTAD(ch)                          (RZV_GPT##ch##_BASE + RZV_GPT_GTINTAD_OFFSET)
#define RZV_GPT_GTST(ch)                             (RZV_GPT##ch##_BASE + RZV_GPT_GTST_OFFSET)
#define RZV_GPT_GTBER(ch)                            (RZV_GPT##ch##_BASE + RZV_GPT_GTBER_OFFSET)
#define RZV_GPT_GTITC(ch)                            (RZV_GPT##ch##_BASE + RZV_GPT_GTITC_OFFSET)
#define RZV_GPT_GTCNT(ch)                            (RZV_GPT##ch##_BASE + RZV_GPT_GTCNT_OFFSET)
#define RZV_GPT_GTCCRA(ch)                           (RZV_GPT##ch##_BASE + RZV_GPT_GTCCRA_OFFSET)
#define RZV_GPT_GTCCRB(ch)                           (RZV_GPT##ch##_BASE + RZV_GPT_GTCCRB_OFFSET)
#define RZV_GPT_GTCCRC(ch)                           (RZV_GPT##ch##_BASE + RZV_GPT_GTCCRC_OFFSET)
#define RZV_GPT_GTCCRE(ch)                           (RZV_GPT##ch##_BASE + RZV_GPT_GTCCRE_OFFSET)
#define RZV_GPT_GTCCRD(ch)                           (RZV_GPT##ch##_BASE + RZV_GPT_GTCCRD_OFFSET)
#define RZV_GPT_GTCCRF(ch)                           (RZV_GPT##ch##_BASE + RZV_GPT_GTCCRF_OFFSET)
#define RZV_GPT_GTPR(ch)                             (RZV_GPT##ch##_BASE + RZV_GPT_GTPR_OFFSET)
#define RZV_GPT_GTPBR(ch)                            (RZV_GPT##ch##_BASE + RZV_GPT_GTPBR_OFFSET)
#define RZV_GPT_GTPDBR(ch)                           (RZV_GPT##ch##_BASE + RZV_GPT_GTPDBR_OFFSET)
#define RZV_GPT_GTADTRA(ch)                          (RZV_GPT##ch##_BASE + RZV_GPT_GTADTRA_OFFSET)
#define RZV_GPT_GTADTBRA(ch)                         (RZV_GPT##ch##_BASE + RZV_GPT_GTADTBRA_OFFSET)
#define RZV_GPT_GTADTDBRA(ch)                        (RZV_GPT##ch##_BASE + RZV_GPT_GTADTDBRA_OFFSET)
#define RZV_GPT_GTADTRB(ch)                          (RZV_GPT##ch##_BASE + RZV_GPT_GTADTRB_OFFSET)
#define RZV_GPT_GTADTBRB(ch)                         (RZV_GPT##ch##_BASE + RZV_GPT_GTADTBRB_OFFSET)
#define RZV_GPT_GTADTDBRB(ch)                        (RZV_GPT##ch##_BASE + RZV_GPT_GTADTDBRB_OFFSET)
#define RZV_GPT_GTDTCR(ch)                           (RZV_GPT##ch##_BASE + RZV_GPT_GTDTCR_OFFSET)
#define RZV_GPT_GTDVU(ch)                            (RZV_GPT##ch##_BASE + RZV_GPT_GTDVU_OFFSET)
#define RZV_GPT_GTDVD(ch)                            (RZV_GPT##ch##_BASE + RZV_GPT_GTDVD_OFFSET)
#define RZV_GPT_GTDBU(ch)                            (RZV_GPT##ch##_BASE + RZV_GPT_GTDBU_OFFSET)
#define RZV_GPT_GTDBB(ch)                            (RZV_GPT##ch##_BASE + RZV_GPT_GTDBB_OFFSET)
#define RZV_GPT_GTSOS(ch)                            (RZV_GPT##ch##_BASE + RZV_GPT_GTSOS_OFFSET)
#define RZV_GPT_GTSOTR(ch)                           (RZV_GPT##ch##_BASE + RZV_GPT_GTSOTR_OFFSET)
#define RZV_GPT_GTEITC(ch)                           (RZV_GPT##ch##_BASE + RZV_GPT_GTEITC_OFFSET)
#define RZV_GPT_GTEITLB(ch)                          (RZV_GPT##ch##_BASE + RZV_GPT_GTEITLB_OFFSET)
#define RZV_GPT_GTICLF(ch)                           (RZV_GPT##ch##_BASE + RZV_GPT_GTICLF_OFFSET)
#define RZV_GPT_GTSECSR(ch)                          (RZV_GPT##ch##_BASE + RZV_GPT_GTSECSR_OFFSET)
#define RZV_GPT_GTSECR(ch)                           (RZV_GPT##ch##_BASE + RZV_GPT_GTSECR_OFFSET)

/* GPT GTEITLI Register Bit Definitions (Parameterized) ********************/

#define GPT_GTEITLI_EITLA_SHIFT                           (0)      /* Bits 0-2: Eitla */
#define GPT_GTEITLI_EITLA_MASK(m)                         (0x7 << GPT_GTEITLI_EITLA_SHIFT)
#define GPT_GTEITLI_EITLA(m,val)                          (((val) << GPT_GTEITLI_EITLA_SHIFT) & GPT_GTEITLI_EITLA_MASK(m))
#define GPT_GTEITLI_EITLPA(m)                             (1 << 3)  /* Eitlpa */
#define GPT_GTEITLI_EITLB_SHIFT                           (4)      /* Bits 4-6: Eitlb */
#define GPT_GTEITLI_EITLB_MASK(m)                         (0x7 << GPT_GTEITLI_EITLB_SHIFT)
#define GPT_GTEITLI_EITLB(m,val)                          (((val) << GPT_GTEITLI_EITLB_SHIFT) & GPT_GTEITLI_EITLB_MASK(m))
#define GPT_GTEITLI_EITLPB(m)                             (1 << 7)  /* Eitlpb */
#define GPT_GTEITLI_EITLC_SHIFT                           (8)      /* Bits 8-10: Eitlc */
#define GPT_GTEITLI_EITLC_MASK(m)                         (0x7 << GPT_GTEITLI_EITLC_SHIFT)
#define GPT_GTEITLI_EITLC(m,val)                          (((val) << GPT_GTEITLI_EITLC_SHIFT) & GPT_GTEITLI_EITLC_MASK(m))
#define GPT_GTEITLI_EITLPC(m)                             (1 << 11)  /* Eitlpc */
#define GPT_GTEITLI_EITLD_SHIFT                           (12)      /* Bits 12-14: Eitld */
#define GPT_GTEITLI_EITLD_MASK(m)                         (0x7 << GPT_GTEITLI_EITLD_SHIFT)
#define GPT_GTEITLI_EITLD(m,val)                          (((val) << GPT_GTEITLI_EITLD_SHIFT) & GPT_GTEITLI_EITLD_MASK(m))
#define GPT_GTEITLI_EITLPD(m)                             (1 << 15)  /* Eitlpd */
#define GPT_GTEITLI_EITLE_SHIFT                           (16)      /* Bits 16-18: Eitle */
#define GPT_GTEITLI_EITLE_MASK(m)                         (0x7 << GPT_GTEITLI_EITLE_SHIFT)
#define GPT_GTEITLI_EITLE(m,val)                          (((val) << GPT_GTEITLI_EITLE_SHIFT) & GPT_GTEITLI_EITLE_MASK(m))
#define GPT_GTEITLI_EITLPE(m)                             (1 << 19)  /* Eitlpe */
#define GPT_GTEITLI_EITLF_SHIFT                           (20)      /* Bits 20-22: Eitlf */
#define GPT_GTEITLI_EITLF_MASK(m)                         (0x7 << GPT_GTEITLI_EITLF_SHIFT)
#define GPT_GTEITLI_EITLF(m,val)                          (((val) << GPT_GTEITLI_EITLF_SHIFT) & GPT_GTEITLI_EITLF_MASK(m))
#define GPT_GTEITLI_EITLPF(m)                             (1 << 23)  /* Eitlpf */
#define GPT_GTEITLI_EITLV_SHIFT                           (24)      /* Bits 24-26: Eitlv */
#define GPT_GTEITLI_EITLV_MASK(m)                         (0x7 << GPT_GTEITLI_EITLV_SHIFT)
#define GPT_GTEITLI_EITLV(m,val)                          (((val) << GPT_GTEITLI_EITLV_SHIFT) & GPT_GTEITLI_EITLV_MASK(m))
#define GPT_GTEITLI_EITLPV(m)                             (1 << 27)  /* Eitlpv */
#define GPT_GTEITLI_EITLU_SHIFT                           (28)      /* Bits 28-30: Eitlu */
#define GPT_GTEITLI_EITLU_MASK(m)                         (0x7 << GPT_GTEITLI_EITLU_SHIFT)
#define GPT_GTEITLI_EITLU(m,val)                          (((val) << GPT_GTEITLI_EITLU_SHIFT) & GPT_GTEITLI_EITLU_MASK(m))
#define GPT_GTEITLI_EITLPU(m)                             (1 << 31)  /* Eitlpu */

/* GPT GTADTBRA Register Bit Definitions *****************************/

#define GPT_GTADTBRA_GTADTBR_SHIFT              (0)      /* Bits 0-31: Gtadtbr */
#define GPT_GTADTBRA_GTADTBR_MASK               (0xffffffff << GPT_GTADTBRA_GTADTBR_SHIFT)

/* GPT GTADTBRB Register Bit Definitions *****************************/

#define GPT_GTADTBRB_GTADTBR_SHIFT              (0)      /* Bits 0-31: Gtadtbr */
#define GPT_GTADTBRB_GTADTBR_MASK               (0xffffffff << GPT_GTADTBRB_GTADTBR_SHIFT)

/* GPT GTADTDBRA Register Bit Definitions ****************************/

#define GPT_GTADTDBRA_GTADTDBR_SHIFT            (0)      /* Bits 0-31: Gtadtdbr */
#define GPT_GTADTDBRA_GTADTDBR_MASK             (0xffffffff << GPT_GTADTDBRA_GTADTDBR_SHIFT)

/* GPT GTADTDBRB Register Bit Definitions ****************************/

#define GPT_GTADTDBRB_GTADTDBR_SHIFT            (0)      /* Bits 0-31: Gtadtdbr */
#define GPT_GTADTDBRB_GTADTDBR_MASK             (0xffffffff << GPT_GTADTDBRB_GTADTDBR_SHIFT)

/* GPT GTADTRA Register Bit Definitions ******************************/

#define GPT_GTADTRA_GTADTR_SHIFT                (0)      /* Bits 0-31: Gtadtr */
#define GPT_GTADTRA_GTADTR_MASK                 (0xffffffff << GPT_GTADTRA_GTADTR_SHIFT)

/* GPT GTADTRB Register Bit Definitions ******************************/

#define GPT_GTADTRB_GTADTR_SHIFT                (0)      /* Bits 0-31: Gtadtr */
#define GPT_GTADTRB_GTADTR_MASK                 (0xffffffff << GPT_GTADTRB_GTADTR_SHIFT)

/* GPT GTBER Register Bit Definitions ********************************/

/* BD fields (parameterized for indices 0-3) */
#define GPT_GTBER_BD(n)                                   (1u << (0 + ((unsigned)(n) * 1)))  /* Bd0 */

#define GPT_GTBER_DBRTECA                       (1 << 8)  /* Dbrteca */

#define GPT_GTBER_DBRTSCA                       (1 << 9)  /* Dbrtsca */

#define GPT_GTBER_DBRTECB                       (1 << 10)  /* Dbrtecb */

#define GPT_GTBER_DBRTSCB                       (1 << 11)  /* Dbrtscb */

#define GPT_GTBER_DBRTEADA                      (1 << 12)  /* Dbrteada */

#define GPT_GTBER_DBRTSADA                      (1 << 13)  /* Dbrtsada */

#define GPT_GTBER_DBRTEADB                      (1 << 14)  /* Dbrteadb */

#define GPT_GTBER_DBRTSADB                      (1 << 15)  /* Dbrtsadb */

#define GPT_GTBER_CCRA_SHIFT                    (16)      /* Bits 16-17: Ccra */
#define GPT_GTBER_CCRA_MASK                     (0x3 << GPT_GTBER_CCRA_SHIFT)

#define GPT_GTBER_CCRB_SHIFT                    (18)      /* Bits 18-19: Ccrb */
#define GPT_GTBER_CCRB_MASK                     (0x3 << GPT_GTBER_CCRB_SHIFT)

#define GPT_GTBER_PR_SHIFT                      (20)      /* Bits 20-21: Pr */
#define GPT_GTBER_PR_MASK                       (0x3 << GPT_GTBER_PR_SHIFT)

#define GPT_GTBER_CCRSWT                        (1 << 22)  /* Ccrswt */

#define GPT_GTBER_ADTTA_SHIFT                   (24)      /* Bits 24-25: Adtta */
#define GPT_GTBER_ADTTA_MASK                    (0x3 << GPT_GTBER_ADTTA_SHIFT)

#define GPT_GTBER_ADTDA                         (1 << 26)  /* Adtda */

#define GPT_GTBER_ADTTB_SHIFT                   (28)      /* Bits 28-29: Adttb */
#define GPT_GTBER_ADTTB_MASK                    (0x3 << GPT_GTBER_ADTTB_SHIFT)

#define GPT_GTBER_ADTDB                         (1 << 30)  /* Adtdb */

/* GPT GTCCRA Register Bit Definitions *******************************/

#define GPT_GTCCRA_GTCCR_SHIFT                  (0)      /* Bits 0-31: Gtccr */
#define GPT_GTCCRA_GTCCR_MASK                   (0xffffffff << GPT_GTCCRA_GTCCR_SHIFT)

/* GPT GTCCRB Register Bit Definitions *******************************/

#define GPT_GTCCRB_GTCCR_SHIFT                  (0)      /* Bits 0-31: Gtccr */
#define GPT_GTCCRB_GTCCR_MASK                   (0xffffffff << GPT_GTCCRB_GTCCR_SHIFT)

/* GPT GTCCRC Register Bit Definitions *******************************/

#define GPT_GTCCRC_GTCCR_SHIFT                  (0)      /* Bits 0-31: Gtccr */
#define GPT_GTCCRC_GTCCR_MASK                   (0xffffffff << GPT_GTCCRC_GTCCR_SHIFT)

/* GPT GTCCRD Register Bit Definitions *******************************/

#define GPT_GTCCRD_GTCCR_SHIFT                  (0)      /* Bits 0-31: Gtccr */
#define GPT_GTCCRD_GTCCR_MASK                   (0xffffffff << GPT_GTCCRD_GTCCR_SHIFT)

/* GPT GTCCRE Register Bit Definitions *******************************/

#define GPT_GTCCRE_GTCCR_SHIFT                  (0)      /* Bits 0-31: Gtccr */
#define GPT_GTCCRE_GTCCR_MASK                   (0xffffffff << GPT_GTCCRE_GTCCR_SHIFT)

/* GPT GTCCRF Register Bit Definitions *******************************/

#define GPT_GTCCRF_GTCCR_SHIFT                  (0)      /* Bits 0-31: Gtccr */
#define GPT_GTCCRF_GTCCR_MASK                   (0xffffffff << GPT_GTCCRF_GTCCR_SHIFT)

/* GPT GTCLR Register Bit Definitions ********************************/

#define GPT_GTCLR_CCLR_SHIFT                    (0)      /* Bits 0-31: Cclr */
#define GPT_GTCLR_CCLR_MASK                     (0xffffffff << GPT_GTCLR_CCLR_SHIFT)

/* GPT GTCNT Register Bit Definitions ********************************/

#define GPT_GTCNT_GTCNT_SHIFT                   (0)      /* Bits 0-31: Gtcnt */
#define GPT_GTCNT_GTCNT_MASK                    (0xffffffff << GPT_GTCNT_GTCNT_SHIFT)

/* GPT GTCR Register Bit Definitions *********************************/

#define GPT_GTCR_CST                            (1 << 0)  /* Cst */

#define GPT_GTCR_MD_SHIFT                       (16)      /* Bits 16-18: Md */
#define GPT_GTCR_MD_MASK                        (0x7 << GPT_GTCR_MD_SHIFT)
#define GPT_GTCR_MD_SAW                         (0 << GPT_GTCR_MD_SHIFT)

#define GPT_GTCR_TPCS_SHIFT                     (23)      /* Bits 23-26: Tpcs */
#define GPT_GTCR_TPCS_MASK                      (0xf << GPT_GTCR_TPCS_SHIFT)
#define GPT_TPCS_DIV1                           0
#define GPT_TPCS_DIV2                           1
#define GPT_TPCS_DIV4                           2
#define GPT_TPCS_DIV8                           3
#define GPT_TPCS_DIV16                          4
#define GPT_TPCS_DIV32                          5
#define GPT_TPCS_DIV64                          6
#define GPT_TPCS_DIV128                         7
#define GPT_TPCS_DIV256                         8
#define GPT_TPCS_DIV512                         9
#define GPT_TPCS_DIV1024                        10
#define GPT_TPCS_DIV2048                        11
#define GPT_TPCS_DIV4096                        12
#define GPT_TPCS_DIV8192                        13

/* GPT GTCSR Register Bit Definitions ********************************/

#define GPT_GTCSR_CSGTRGAR                      (1 << 0)  /* Csgtrgar */

#define GPT_GTCSR_CSGTRGAF                      (1 << 1)  /* Csgtrgaf */

#define GPT_GTCSR_CSGTRGBR                      (1 << 2)  /* Csgtrgbr */

#define GPT_GTCSR_CSGTRGBF                      (1 << 3)  /* Csgtrgbf */

#define GPT_GTCSR_CSGTRGCR                      (1 << 4)  /* Csgtrgcr */

#define GPT_GTCSR_CSGTRGCF                      (1 << 5)  /* Csgtrgcf */

#define GPT_GTCSR_CSGTRGDR                      (1 << 6)  /* Csgtrgdr */

#define GPT_GTCSR_CSGTRGDF                      (1 << 7)  /* Csgtrgdf */

#define GPT_GTCSR_CSCARBL                       (1 << 8)  /* Cscarbl */

#define GPT_GTCSR_CSCARBH                       (1 << 9)  /* Cscarbh */

#define GPT_GTCSR_CSCAFBL                       (1 << 10)  /* Cscafbl */

#define GPT_GTCSR_CSCAFBH                       (1 << 11)  /* Cscafbh */

#define GPT_GTCSR_CSCBRAL                       (1 << 12)  /* Cscbral */

#define GPT_GTCSR_CSCBRAH                       (1 << 13)  /* Cscbrah */

#define GPT_GTCSR_CSCBFAL                       (1 << 14)  /* Cscbfal */

#define GPT_GTCSR_CSCBFAH                       (1 << 15)  /* Cscbfah */

#define GPT_GTCSR_CSELCA                        (1 << 16)  /* Cselca */

#define GPT_GTCSR_CSELCB                        (1 << 17)  /* Cselcb */

#define GPT_GTCSR_CSELCC                        (1 << 18)  /* Cselcc */

#define GPT_GTCSR_CSELCD                        (1 << 19)  /* Cselcd */

#define GPT_GTCSR_CSELCE                        (1 << 20)  /* Cselce */

#define GPT_GTCSR_CSELCF                        (1 << 21)  /* Cselcf */

#define GPT_GTCSR_CSELCG                        (1 << 22)  /* Cselcg */

#define GPT_GTCSR_CSELCH                        (1 << 23)  /* Cselch */

#define GPT_GTCSR_CCLR                          (1 << 31)  /* Cclr */

/* GPT GTDBB Register Bit Definitions ********************************/

#define GPT_GTDBB_GTDB_SHIFT                    (0)      /* Bits 0-31: Gtdb */
#define GPT_GTDBB_GTDB_MASK                     (0xffffffff << GPT_GTDBB_GTDB_SHIFT)

/* GPT GTDBU Register Bit Definitions ********************************/

#define GPT_GTDBU_GTDB_SHIFT                    (0)      /* Bits 0-31: Gtdb */
#define GPT_GTDBU_GTDB_MASK                     (0xffffffff << GPT_GTDBU_GTDB_SHIFT)

/* GPT GTDNSR Register Bit Definitions *******************************/

#define GPT_GTDNSR_DSGTRGAR                     (1 << 0)  /* Dsgtrgar */

#define GPT_GTDNSR_DSGTRGAF                     (1 << 1)  /* Dsgtrgaf */

#define GPT_GTDNSR_DSGTRGBR                     (1 << 2)  /* Dsgtrgbr */

#define GPT_GTDNSR_DSGTRGBF                     (1 << 3)  /* Dsgtrgbf */

#define GPT_GTDNSR_DSGTRGCR                     (1 << 4)  /* Dsgtrgcr */

#define GPT_GTDNSR_DSGTRGCF                     (1 << 5)  /* Dsgtrgcf */

#define GPT_GTDNSR_DSGTRGDR                     (1 << 6)  /* Dsgtrgdr */

#define GPT_GTDNSR_DSGTRGDF                     (1 << 7)  /* Dsgtrgdf */

#define GPT_GTDNSR_DSCARBL                      (1 << 8)  /* Dscarbl */

#define GPT_GTDNSR_DSCARBH                      (1 << 9)  /* Dscarbh */

#define GPT_GTDNSR_DSCAFBL                      (1 << 10)  /* Dscafbl */

#define GPT_GTDNSR_DSCAFBH                      (1 << 11)  /* Dscafbh */

#define GPT_GTDNSR_DSCBRAL                      (1 << 12)  /* Dscbral */

#define GPT_GTDNSR_DSCBRAH                      (1 << 13)  /* Dscbrah */

#define GPT_GTDNSR_DSCBFAL                      (1 << 14)  /* Dscbfal */

#define GPT_GTDNSR_DSCBFAH                      (1 << 15)  /* Dscbfah */

#define GPT_GTDNSR_DSELCA                       (1 << 16)  /* Dselca */

#define GPT_GTDNSR_DSELCB                       (1 << 17)  /* Dselcb */

#define GPT_GTDNSR_DSELCC                       (1 << 18)  /* Dselcc */

#define GPT_GTDNSR_DSELCD                       (1 << 19)  /* Dselcd */

#define GPT_GTDNSR_DSELCE                       (1 << 20)  /* Dselce */

#define GPT_GTDNSR_DSELCF                       (1 << 21)  /* Dselcf */

#define GPT_GTDNSR_DSELCG                       (1 << 22)  /* Dselcg */

#define GPT_GTDNSR_DSELCH                       (1 << 23)  /* Dselch */

/* GPT GTDTCR Register Bit Definitions *******************************/

#define GPT_GTDTCR_TDE                          (1 << 0)  /* Tde */

#define GPT_GTDTCR_TDBUE                        (1 << 4)  /* Tdbue */

#define GPT_GTDTCR_TDBDE                        (1 << 5)  /* Tdbde */

#define GPT_GTDTCR_TDFER                        (1 << 8)  /* Tdfer */

/* GPT GTDVD Register Bit Definitions ********************************/

#define GPT_GTDVD_GTDV_SHIFT                    (0)      /* Bits 0-31: Gtdv */
#define GPT_GTDVD_GTDV_MASK                     (0xffffffff << GPT_GTDVD_GTDV_SHIFT)

/* GPT GTDVU Register Bit Definitions ********************************/

#define GPT_GTDVU_GTDV_SHIFT                    (0)      /* Bits 0-31: Gtdv */
#define GPT_GTDVU_GTDV_MASK                     (0xffffffff << GPT_GTDVU_GTDV_SHIFT)

/* GPT GTEITC Register Bit Definitions *******************************/

#define GPT_GTEITC_EIVTC1_SHIFT                 (0)      /* Bits 0-1: Eivtc1 */
#define GPT_GTEITC_EIVTC1_MASK                  (0x3 << GPT_GTEITC_EIVTC1_SHIFT)

#define GPT_GTEITC_EIVTT1_SHIFT                 (4)      /* Bits 4-7: Eivtt1 */
#define GPT_GTEITC_EIVTT1_MASK                  (0xf << GPT_GTEITC_EIVTT1_SHIFT)

#define GPT_GTEITC_EITCNT1_SHIFT                (12)      /* Bits 12-15: Eitcnt1 */
#define GPT_GTEITC_EITCNT1_MASK                 (0xf << GPT_GTEITC_EITCNT1_SHIFT)

#define GPT_GTEITC_EIVTC2_SHIFT                 (16)      /* Bits 16-17: Eivtc2 */
#define GPT_GTEITC_EIVTC2_MASK                  (0x3 << GPT_GTEITC_EIVTC2_SHIFT)

#define GPT_GTEITC_EIVTT2_SHIFT                 (20)      /* Bits 20-23: Eivtt2 */
#define GPT_GTEITC_EIVTT2_MASK                  (0xf << GPT_GTEITC_EIVTT2_SHIFT)

#define GPT_GTEITC_EITCNT2IV_SHIFT              (24)      /* Bits 24-27: Eitcnt2Iv */
#define GPT_GTEITC_EITCNT2IV_MASK               (0xf << GPT_GTEITC_EITCNT2IV_SHIFT)

#define GPT_GTEITC_EITCNT2_SHIFT                (28)      /* Bits 28-31: Eitcnt2 */
#define GPT_GTEITC_EITCNT2_MASK                 (0xf << GPT_GTEITC_EITCNT2_SHIFT)

/* GPT GTEITLB Register Bit Definitions ******************************/

#define GPT_GTEITLB_EBTLCA_SHIFT                (0)      /* Bits 0-2: Ebtlca */
#define GPT_GTEITLB_EBTLCA_MASK                 (0x7 << GPT_GTEITLB_EBTLCA_SHIFT)

#define GPT_GTEITLB_EBTLCB_SHIFT                (4)      /* Bits 4-6: Ebtlcb */
#define GPT_GTEITLB_EBTLCB_MASK                 (0x7 << GPT_GTEITLB_EBTLCB_SHIFT)

#define GPT_GTEITLB_EBTLPR_SHIFT                (8)      /* Bits 8-10: Ebtlpr */
#define GPT_GTEITLB_EBTLPR_MASK                 (0x7 << GPT_GTEITLB_EBTLPR_SHIFT)

#define GPT_GTEITLB_EBTLADA_SHIFT               (16)      /* Bits 16-18: Ebtlada */
#define GPT_GTEITLB_EBTLADA_MASK                (0x7 << GPT_GTEITLB_EBTLADA_SHIFT)

#define GPT_GTEITLB_EBTLADB_SHIFT               (20)      /* Bits 20-22: Ebtladb */
#define GPT_GTEITLB_EBTLADB_MASK                (0x7 << GPT_GTEITLB_EBTLADB_SHIFT)

#define GPT_GTEITLB_EBTLDVU_SHIFT               (24)      /* Bits 24-26: Ebtldvu */
#define GPT_GTEITLB_EBTLDVU_MASK                (0x7 << GPT_GTEITLB_EBTLDVU_SHIFT)

#define GPT_GTEITLB_EBTLDVD_SHIFT               (28)      /* Bits 28-30: Ebtldvd */
#define GPT_GTEITLB_EBTLDVD_MASK                (0x7 << GPT_GTEITLB_EBTLDVD_SHIFT)

/* GPT GTICASR Register Bit Definitions ******************************/

#define GPT_GTICASR_ASGTRGAR                    (1 << 0)  /* Asgtrgar */

#define GPT_GTICASR_ASGTRGAF                    (1 << 1)  /* Asgtrgaf */

#define GPT_GTICASR_ASGTRGBR                    (1 << 2)  /* Asgtrgbr */

#define GPT_GTICASR_ASGTRGBF                    (1 << 3)  /* Asgtrgbf */

#define GPT_GTICASR_ASGTRGCR                    (1 << 4)  /* Asgtrgcr */

#define GPT_GTICASR_ASGTRGCF                    (1 << 5)  /* Asgtrgcf */

#define GPT_GTICASR_ASGTRGDR                    (1 << 6)  /* Asgtrgdr */

#define GPT_GTICASR_ASGTRGDF                    (1 << 7)  /* Asgtrgdf */

#define GPT_GTICASR_ASCARBL                     (1 << 8)  /* Ascarbl */

#define GPT_GTICASR_ASCARBH                     (1 << 9)  /* Ascarbh */

#define GPT_GTICASR_ASCAFBL                     (1 << 10)  /* Ascafbl */

#define GPT_GTICASR_ASCAFBH                     (1 << 11)  /* Ascafbh */

#define GPT_GTICASR_ASCBRAL                     (1 << 12)  /* Ascbral */

#define GPT_GTICASR_ASCBRAH                     (1 << 13)  /* Ascbrah */

#define GPT_GTICASR_ASCBFAL                     (1 << 14)  /* Ascbfal */

#define GPT_GTICASR_ASCBFAH                     (1 << 15)  /* Ascbfah */

#define GPT_GTICASR_ASELCA                      (1 << 16)  /* Aselca */

#define GPT_GTICASR_ASELCB                      (1 << 17)  /* Aselcb */

#define GPT_GTICASR_ASELCC                      (1 << 18)  /* Aselcc */

#define GPT_GTICASR_ASELCD                      (1 << 19)  /* Aselcd */

#define GPT_GTICASR_ASELCE                      (1 << 20)  /* Aselce */

#define GPT_GTICASR_ASELCF                      (1 << 21)  /* Aselcf */

#define GPT_GTICASR_ASELCG                      (1 << 22)  /* Aselcg */

#define GPT_GTICASR_ASELCH                      (1 << 23)  /* Aselch */

/* GPT GTICBSR Register Bit Definitions ******************************/

#define GPT_GTICBSR_BSGTRGAR                    (1 << 0)  /* Bsgtrgar */

#define GPT_GTICBSR_BSGTRGAF                    (1 << 1)  /* Bsgtrgaf */

#define GPT_GTICBSR_BSGTRGBR                    (1 << 2)  /* Bsgtrgbr */

#define GPT_GTICBSR_BSGTRGBF                    (1 << 3)  /* Bsgtrgbf */

#define GPT_GTICBSR_BSGTRGCR                    (1 << 4)  /* Bsgtrgcr */

#define GPT_GTICBSR_BSGTRGCF                    (1 << 5)  /* Bsgtrgcf */

#define GPT_GTICBSR_BSGTRGDR                    (1 << 6)  /* Bsgtrgdr */

#define GPT_GTICBSR_BSGTRGDF                    (1 << 7)  /* Bsgtrgdf */

#define GPT_GTICBSR_BSCARBL                     (1 << 8)  /* Bscarbl */

#define GPT_GTICBSR_BSCARBH                     (1 << 9)  /* Bscarbh */

#define GPT_GTICBSR_BSCAFBL                     (1 << 10)  /* Bscafbl */

#define GPT_GTICBSR_BSCAFBH                     (1 << 11)  /* Bscafbh */

#define GPT_GTICBSR_BSCBRAL                     (1 << 12)  /* Bscbral */

#define GPT_GTICBSR_BSCBRAH                     (1 << 13)  /* Bscbrah */

#define GPT_GTICBSR_BSCBFAL                     (1 << 14)  /* Bscbfal */

#define GPT_GTICBSR_BSCBFAH                     (1 << 15)  /* Bscbfah */

#define GPT_GTICBSR_BSELCA                      (1 << 16)  /* Bselca */

#define GPT_GTICBSR_BSELCB                      (1 << 17)  /* Bselcb */

#define GPT_GTICBSR_BSELCC                      (1 << 18)  /* Bselcc */

#define GPT_GTICBSR_BSELCD                      (1 << 19)  /* Bselcd */

#define GPT_GTICBSR_BSELCE                      (1 << 20)  /* Bselce */

#define GPT_GTICBSR_BSELCF                      (1 << 21)  /* Bselcf */

#define GPT_GTICBSR_BSELCG                      (1 << 22)  /* Bselcg */

#define GPT_GTICBSR_BSELCH                      (1 << 23)  /* Bselch */

/* GPT GTICLF Register Bit Definitions *******************************/

#define GPT_GTICLF_ICLFA_SHIFT                  (0)      /* Bits 0-2: Iclfa */
#define GPT_GTICLF_ICLFA_MASK                   (0x7 << GPT_GTICLF_ICLFA_SHIFT)

#define GPT_GTICLF_ICLFSELC_SHIFT               (4)      /* Bits 4-9: Iclfselc */
#define GPT_GTICLF_ICLFSELC_MASK                (0x3f << GPT_GTICLF_ICLFSELC_SHIFT)

#define GPT_GTICLF_ICLFB_SHIFT                  (16)      /* Bits 16-18: Iclfb */
#define GPT_GTICLF_ICLFB_MASK                   (0x7 << GPT_GTICLF_ICLFB_SHIFT)

#define GPT_GTICLF_ICLFSELD_SHIFT               (20)      /* Bits 20-25: Iclfseld */
#define GPT_GTICLF_ICLFSELD_MASK                (0x3f << GPT_GTICLF_ICLFSELD_SHIFT)

/* GPT GTINTAD Register Bit Definitions ******************************/

#define GPT_GTINTAD_GTINTA                      (1 << 0)  /* Gtinta */

#define GPT_GTINTAD_GTINTB                      (1 << 1)  /* Gtintb */

#define GPT_GTINTAD_GTINTC                      (1 << 2)  /* Gtintc */

#define GPT_GTINTAD_GTINTD                      (1 << 3)  /* Gtintd */

#define GPT_GTINTAD_GTINTE                      (1 << 4)  /* Gtinte */

#define GPT_GTINTAD_GTINTF                      (1 << 5)  /* Gtintf */

#define GPT_GTINTAD_GTINTPR_SHIFT               (6)      /* Bits 6-7: Gtintpr */
#define GPT_GTINTAD_GTINTPR_MASK                (0x3 << GPT_GTINTAD_GTINTPR_SHIFT)

#define GPT_GTINTAD_ADTRAUEN                    (1 << 16)  /* Adtrauen */

#define GPT_GTINTAD_ADTRADEN                    (1 << 17)  /* Adtraden */

#define GPT_GTINTAD_ADTRBUEN                    (1 << 18)  /* Adtrbuen */

#define GPT_GTINTAD_ADTRBDEN                    (1 << 19)  /* Adtrbden */

#define GPT_GTINTAD_GRP_SHIFT                   (24)      /* Bits 24-25: Grp */
#define GPT_GTINTAD_GRP_MASK                    (0x3 << GPT_GTINTAD_GRP_SHIFT)

#define GPT_GTINTAD_GRPDTE                      (1 << 28)  /* Grpdte */

#define GPT_GTINTAD_GRPABH                      (1 << 29)  /* Grpabh */

#define GPT_GTINTAD_GRPABL                      (1 << 30)  /* Grpabl */
#define GPT_GTINTAD_ENABLE_OVF                  (1 << 6)

/* GPT GTIOR Register Bit Definitions ********************************/

#define GPT_GTIOR_GTIOA_SHIFT                   (0)      /* Bits 0-4: Gtioa */
#define GPT_GTIOR_GTIOA_MASK                    (0x1f << GPT_GTIOR_GTIOA_SHIFT)
#define GPT_GTIOR_GTIOA_DISABLE                 (0x00 << GPT_GTIOR_GTIOA_SHIFT)
#define GPT_GTIOR_GTIOA_HIGH_CMP_LOW            (0x09 << GPT_GTIOR_GTIOA_SHIFT)

#define GPT_GTIOR_OADFLT                        (1 << 6)  /* Oadflt */

#define GPT_GTIOR_OAHLD                         (1 << 7)  /* Oahld */

#define GPT_GTIOR_OAE                           (1 << 8)  /* Oae */

#define GPT_GTIOR_OADF_SHIFT                    (9)      /* Bits 9-10: Oadf */
#define GPT_GTIOR_OADF_MASK                     (0x3 << GPT_GTIOR_OADF_SHIFT)

#define GPT_GTIOR_NFAEN                         (1 << 13)  /* Nfaen */

#define GPT_GTIOR_NFCSA_SHIFT                   (14)      /* Bits 14-15: Nfcsa */
#define GPT_GTIOR_NFCSA_MASK                    (0x3 << GPT_GTIOR_NFCSA_SHIFT)

#define GPT_GTIOR_GTIOB_SHIFT                   (16)      /* Bits 16-20: Gtiob */
#define GPT_GTIOR_GTIOB_MASK                    (0x1f << GPT_GTIOR_GTIOB_SHIFT)
#define GPT_GTIOR_GTIOB_DISABLE                 (0x00 << GPT_GTIOR_GTIOB_SHIFT)
#define GPT_GTIOR_GTIOB_HIGH_CMP_LOW            (0x09 << GPT_GTIOR_GTIOB_SHIFT)

#define GPT_GTIOR_OBDFLT                        (1 << 22)  /* Obdflt */

#define GPT_GTIOR_OBHLD                         (1 << 23)  /* Obhld */

#define GPT_GTIOR_OBE                           (1 << 24)  /* Obe */

#define GPT_GTIOR_OBDF_SHIFT                    (25)      /* Bits 25-26: Obdf */
#define GPT_GTIOR_OBDF_MASK                     (0x3 << GPT_GTIOR_OBDF_SHIFT)

#define GPT_GTIOR_NFBEN                         (1 << 29)  /* Nfben */

#define GPT_GTIOR_NFCSB_SHIFT                   (30)      /* Bits 30-31: Nfcsb */
#define GPT_GTIOR_NFCSB_MASK                    (0x3 << GPT_GTIOR_NFCSB_SHIFT)

/* GPT GTITC Register Bit Definitions ********************************/

#define GPT_GTITC_ITLA                          (1 << 0)  /* Itla */

#define GPT_GTITC_ITLB                          (1 << 1)  /* Itlb */

#define GPT_GTITC_ITLC                          (1 << 2)  /* Itlc */

#define GPT_GTITC_ITLD                          (1 << 3)  /* Itld */

#define GPT_GTITC_ITLE                          (1 << 4)  /* Itle */

#define GPT_GTITC_ITLF                          (1 << 5)  /* Itlf */

#define GPT_GTITC_IVTC_SHIFT                    (6)      /* Bits 6-7: Ivtc */
#define GPT_GTITC_IVTC_MASK                     (0x3 << GPT_GTITC_IVTC_SHIFT)

#define GPT_GTITC_IVTT_SHIFT                    (8)      /* Bits 8-10: Ivtt */
#define GPT_GTITC_IVTT_MASK                     (0x7 << GPT_GTITC_IVTT_SHIFT)

#define GPT_GTITC_ADTAL                         (1 << 12)  /* Adtal */

#define GPT_GTITC_ADTBL                         (1 << 14)  /* Adtbl */

/* GPT GTPBR Register Bit Definitions ********************************/

#define GPT_GTPBR_GTPBR_SHIFT                   (0)      /* Bits 0-31: Gtpbr */
#define GPT_GTPBR_GTPBR_MASK                    (0xffffffff << GPT_GTPBR_GTPBR_SHIFT)

/* GPT GTPDBR Register Bit Definitions *******************************/

#define GPT_GTPDBR_GTPDBR_SHIFT                 (0)      /* Bits 0-31: Gtpdbr */
#define GPT_GTPDBR_GTPDBR_MASK                  (0xffffffff << GPT_GTPDBR_GTPDBR_SHIFT)

/* GPT GTPR Register Bit Definitions *********************************/

#define GPT_GTPR_GTPR_SHIFT                     (0)      /* Bits 0-31: Gtpr */
#define GPT_GTPR_GTPR_MASK                      (0xffffffff << GPT_GTPR_GTPR_SHIFT)

/* GPT GTPSR Register Bit Definitions ********************************/

#define GPT_GTPSR_PSGTRGAR                      (1 << 0)  /* Psgtrgar */

#define GPT_GTPSR_PSGTRGAF                      (1 << 1)  /* Psgtrgaf */

#define GPT_GTPSR_PSGTRGBR                      (1 << 2)  /* Psgtrgbr */

#define GPT_GTPSR_PSGTRGBF                      (1 << 3)  /* Psgtrgbf */

#define GPT_GTPSR_PSGTRGCR                      (1 << 4)  /* Psgtrgcr */

#define GPT_GTPSR_PSGTRGCF                      (1 << 5)  /* Psgtrgcf */

#define GPT_GTPSR_PSGTRGDR                      (1 << 6)  /* Psgtrgdr */

#define GPT_GTPSR_PSGTRGDF                      (1 << 7)  /* Psgtrgdf */

#define GPT_GTPSR_PSCARBL                       (1 << 8)  /* Pscarbl */

#define GPT_GTPSR_PSCARBH                       (1 << 9)  /* Pscarbh */

#define GPT_GTPSR_PSCAFBL                       (1 << 10)  /* Pscafbl */

#define GPT_GTPSR_PSCAFBH                       (1 << 11)  /* Pscafbh */

#define GPT_GTPSR_PSCBRAL                       (1 << 12)  /* Pscbral */

#define GPT_GTPSR_PSCBRAH                       (1 << 13)  /* Pscbrah */

#define GPT_GTPSR_PSCBFAL                       (1 << 14)  /* Pscbfal */

#define GPT_GTPSR_PSCBFAH                       (1 << 15)  /* Pscbfah */

#define GPT_GTPSR_PSELCA                        (1 << 16)  /* Pselca */

#define GPT_GTPSR_PSELCB                        (1 << 17)  /* Pselcb */

#define GPT_GTPSR_PSELCC                        (1 << 18)  /* Pselcc */

#define GPT_GTPSR_PSELCD                        (1 << 19)  /* Pselcd */

#define GPT_GTPSR_PSELCE                        (1 << 20)  /* Pselce */

#define GPT_GTPSR_PSELCF                        (1 << 21)  /* Pselcf */

#define GPT_GTPSR_PSELCG                        (1 << 22)  /* Pselcg */

#define GPT_GTPSR_PSELCH                        (1 << 23)  /* Pselch */

#define GPT_GTPSR_CSTOP                         (1 << 31)  /* Cstop */

/* GPT GTSECR Register Bit Definitions *******************************/

#define GPT_GTSECR_SBDCE                        (1 << 0)  /* Sbdce */

#define GPT_GTSECR_SBDPE                        (1 << 1)  /* Sbdpe */

#define GPT_GTSECR_SBDCD                        (1 << 8)  /* Sbdcd */

#define GPT_GTSECR_SBDPD                        (1 << 9)  /* Sbdpd */

#define GPT_GTSECR_SPCE                         (1 << 16)  /* Spce */

#define GPT_GTSECR_SPCD                         (1 << 24)  /* Spcd */

/* GPT GTSECSR Register Bit Definitions ******************************/

/* SECSEL fields (parameterized for indices 0-15) */
#define GPT_GTSECSR_SECSEL(n)                             (1u << (0 + ((unsigned)(n) * 1)))  /* Secsel0 */

/* GPT GTSOS Register Bit Definitions ********************************/

#define GPT_GTSOS_SOS_SHIFT                     (0)      /* Bits 0-1: Sos */
#define GPT_GTSOS_SOS_MASK                      (0x3 << GPT_GTSOS_SOS_SHIFT)

#define GPT_GTSOS_OAMON                         (1 << 8)  /* Oamon */

#define GPT_GTSOS_OBMON                         (1 << 9)  /* Obmon */

/* GPT GTSOTR Register Bit Definitions *******************************/

#define GPT_GTSOTR_SOTR                         (1 << 0)  /* Sotr */

/* GPT GTSSR Register Bit Definitions ********************************/

#define GPT_GTSSR_SSGTRGAR                      (1 << 0)  /* Ssgtrgar */

#define GPT_GTSSR_SSGTRGAF                      (1 << 1)  /* Ssgtrgaf */

#define GPT_GTSSR_SSGTRGBR                      (1 << 2)  /* Ssgtrgbr */

#define GPT_GTSSR_SSGTRGBF                      (1 << 3)  /* Ssgtrgbf */

#define GPT_GTSSR_SSGTRGCR                      (1 << 4)  /* Ssgtrgcr */

#define GPT_GTSSR_SSGTRGCF                      (1 << 5)  /* Ssgtrgcf */

#define GPT_GTSSR_SSGTRGDR                      (1 << 6)  /* Ssgtrgdr */

#define GPT_GTSSR_SSGTRGDF                      (1 << 7)  /* Ssgtrgdf */

#define GPT_GTSSR_SSCARBL                       (1 << 8)  /* Sscarbl */

#define GPT_GTSSR_SSCARBH                       (1 << 9)  /* Sscarbh */

#define GPT_GTSSR_SSCAFBL                       (1 << 10)  /* Sscafbl */

#define GPT_GTSSR_SSCAFBH                       (1 << 11)  /* Sscafbh */

#define GPT_GTSSR_SSCBRAL                       (1 << 12)  /* Sscbral */

#define GPT_GTSSR_SSCBRAH                       (1 << 13)  /* Sscbrah */

#define GPT_GTSSR_SSCBFAL                       (1 << 14)  /* Sscbfal */

#define GPT_GTSSR_SSCBFAH                       (1 << 15)  /* Sscbfah */

#define GPT_GTSSR_SSELCA                        (1 << 16)  /* Sselca */

#define GPT_GTSSR_SSELCB                        (1 << 17)  /* Sselcb */

#define GPT_GTSSR_SSELCC                        (1 << 18)  /* Sselcc */

#define GPT_GTSSR_SSELCD                        (1 << 19)  /* Sselcd */

#define GPT_GTSSR_SSELCE                        (1 << 20)  /* Sselce */

#define GPT_GTSSR_SSELCF                        (1 << 21)  /* Sselcf */

#define GPT_GTSSR_SSELCG                        (1 << 22)  /* Sselcg */

#define GPT_GTSSR_SSELCH                        (1 << 23)  /* Sselch */

#define GPT_GTSSR_CSTRT                         (1 << 31)  /* Cstrt */

/* GPT GTST Register Bit Definitions *********************************/

#define GPT_GTST_TCFA                           (1 << 0)  /* Tcfa */

#define GPT_GTST_TCFB                           (1 << 1)  /* Tcfb */

#define GPT_GTST_TCFC                           (1 << 2)  /* Tcfc */

#define GPT_GTST_TCFD                           (1 << 3)  /* Tcfd */

#define GPT_GTST_TCFE                           (1 << 4)  /* Tcfe */

#define GPT_GTST_TCFF                           (1 << 5)  /* Tcff */

#define GPT_GTST_TCFPO                          (1 << 6)  /* Tcfpo */

#define GPT_GTST_TCFPU                          (1 << 7)  /* Tcfpu */

#define GPT_GTST_ITCNT_SHIFT                    (8)      /* Bits 8-10: Itcnt */
#define GPT_GTST_ITCNT_MASK                     (0x7 << GPT_GTST_ITCNT_SHIFT)

#define GPT_GTST_TUCF                           (1 << 15)  /* Tucf */

#define GPT_GTST_ADTRAUF                        (1 << 16)  /* Adtrauf */

#define GPT_GTST_ADTRADF                        (1 << 17)  /* Adtradf */

#define GPT_GTST_ADTRBUF                        (1 << 18)  /* Adtrbuf */

#define GPT_GTST_ADTRBDF                        (1 << 19)  /* Adtrbdf */

#define GPT_GTST_ODF                            (1 << 24)  /* Odf */

#define GPT_GTST_DTEF                           (1 << 28)  /* Dtef */

#define GPT_GTST_OABHF                          (1 << 29)  /* Oabhf */

#define GPT_GTST_OABLF                          (1 << 30)  /* Oablf */

#define GPT_GTST_PCF                            (1 << 31)  /* Pcf */

/* GPT GTSTP Register Bit Definitions ********************************/

#define GPT_GTSTP_CSTOP_SHIFT                   (0)      /* Bits 0-31: Cstop */
#define GPT_GTSTP_CSTOP_MASK                    (0xffffffff << GPT_GTSTP_CSTOP_SHIFT)

/* GPT GTSTR Register Bit Definitions ********************************/

#define GPT_GTSTR_CSTRT_SHIFT                   (0)      /* Bits 0-31: Cstrt */
#define GPT_GTSTR_CSTRT_MASK                    (0xffffffff << GPT_GTSTR_CSTRT_SHIFT)

/* GPT GTUDDTYC Register Bit Definitions *****************************/

#define GPT_GTUDDTYC_UD                         (1 << 0)  /* Ud */

#define GPT_GTUDDTYC_UDF                        (1 << 1)  /* Udf */

#define GPT_GTUDDTYC_OADTY_SHIFT                (16)      /* Bits 16-17: Oadty */
#define GPT_GTUDDTYC_OADTY_MASK                 (0x3 << GPT_GTUDDTYC_OADTY_SHIFT)

#define GPT_GTUDDTYC_OADTYF                     (1 << 18)  /* Oadtyf */

#define GPT_GTUDDTYC_OADTYR                     (1 << 19)  /* Oadtyr */

#define GPT_GTUDDTYC_OBDTY_SHIFT                (24)      /* Bits 24-25: Obdty */
#define GPT_GTUDDTYC_OBDTY_MASK                 (0x3 << GPT_GTUDDTYC_OBDTY_SHIFT)

#define GPT_GTUDDTYC_OBDTYF                     (1 << 26)  /* Obdtyf */

#define GPT_GTUDDTYC_OBDTYR                     (1 << 27)  /* Obdtyr */

/* GPT GTUPSR Register Bit Definitions *******************************/

#define GPT_GTUPSR_USGTRGAR                     (1 << 0)  /* Usgtrgar */

#define GPT_GTUPSR_USGTRGAF                     (1 << 1)  /* Usgtrgaf */

#define GPT_GTUPSR_USGTRGBR                     (1 << 2)  /* Usgtrgbr */

#define GPT_GTUPSR_USGTRGBF                     (1 << 3)  /* Usgtrgbf */

#define GPT_GTUPSR_USGTRGCR                     (1 << 4)  /* Usgtrgcr */

#define GPT_GTUPSR_USGTRGCF                     (1 << 5)  /* Usgtrgcf */

#define GPT_GTUPSR_USGTRGDR                     (1 << 6)  /* Usgtrgdr */

#define GPT_GTUPSR_USGTRGDF                     (1 << 7)  /* Usgtrgdf */

#define GPT_GTUPSR_USCARBL                      (1 << 8)  /* Uscarbl */

#define GPT_GTUPSR_USCARBH                      (1 << 9)  /* Uscarbh */

#define GPT_GTUPSR_USCAFBL                      (1 << 10)  /* Uscafbl */

#define GPT_GTUPSR_USCAFBH                      (1 << 11)  /* Uscafbh */

#define GPT_GTUPSR_USCBRAL                      (1 << 12)  /* Uscbral */

#define GPT_GTUPSR_USCBRAH                      (1 << 13)  /* Uscbrah */

#define GPT_GTUPSR_USCBFAL                      (1 << 14)  /* Uscbfal */

#define GPT_GTUPSR_USCBFAH                      (1 << 15)  /* Uscbfah */

#define GPT_GTUPSR_USELCA                       (1 << 16)  /* Uselca */

#define GPT_GTUPSR_USELCB                       (1 << 17)  /* Uselcb */

#define GPT_GTUPSR_USELCC                       (1 << 18)  /* Uselcc */

#define GPT_GTUPSR_USELCD                       (1 << 19)  /* Uselcd */

#define GPT_GTUPSR_USELCE                       (1 << 20)  /* Uselce */

#define GPT_GTUPSR_USELCF                       (1 << 21)  /* Uselcf */

#define GPT_GTUPSR_USELCG                       (1 << 22)  /* Uselcg */

#define GPT_GTUPSR_USELCH                       (1 << 23)  /* Uselch */

/* GPT GTWP Register Bit Definitions *********************************/

#define GPT_GTWP_WP                             (1 << 0)  /* Wp */

#define GPT_GTWP_STRWP                          (1 << 1)  /* Strwp */

#define GPT_GTWP_STPWP                          (1 << 2)  /* Stpwp */

#define GPT_GTWP_CLRWP                          (1 << 3)  /* Clrwp */

#define GPT_GTWP_CMNWP                          (1 << 4)  /* Cmnwp */

#define GPT_GTWP_PRKEY_SHIFT                    (8)      /* Bits 8-15: Prkey */
#define GPT_GTWP_PRKEY_MASK                     (0xff << GPT_GTWP_PRKEY_SHIFT)
#define GPT_GTWP_PRKEY                          (0xA5u << GPT_GTWP_PRKEY_SHIFT)
#define GPT_GTWP_UNLOCK                         (GPT_GTWP_PRKEY)
#define GPT_GTWP_LOCK                           (GPT_GTWP_PRKEY | GPT_GTWP_WP | GPT_GTWP_CMNWP)

/* GPT Channel definitions */
#define RZV_GPT_CHANNEL_0          0
#define RZV_GPT_CHANNEL_1          1
#define RZV_GPT_CHANNEL_10         10
#define RZV_GPT_CHANNEL_11         11
#define RZV_GPT_CHANNEL_12         12
#define RZV_GPT_CHANNEL_13         13
#define RZV_GPT_CHANNEL_14         14
#define RZV_GPT_CHANNEL_15         15
#define RZV_GPT_CHANNEL_16         16
#define RZV_GPT_CHANNEL_17         17
#define RZV_GPT_CHANNEL_2          2
#define RZV_GPT_CHANNEL_3          3
#define RZV_GPT_CHANNEL_4          4
#define RZV_GPT_CHANNEL_5          5
#define RZV_GPT_CHANNEL_6          6
#define RZV_GPT_CHANNEL_7          7

/* Maximum number of GPT channels */
#define RZV_GPT_MAX_CHANNELS       16

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_GPT_H */

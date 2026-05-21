/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_i2c.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_I2C_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_I2C_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* RIIC Base Addresses ***************************************************/

#ifndef RZV_RIIC0_BASE
#  define RZV_RIIC0_BASE              0x14400400
#endif
#ifndef RZV_RIIC1_BASE
#  define RZV_RIIC1_BASE              0x14400800
#endif
#ifndef RZV_RIIC2_BASE
#  define RZV_RIIC2_BASE              0x14400C00
#endif
#ifndef RZV_RIIC3_BASE
#  define RZV_RIIC3_BASE              0x14401000
#endif
#ifndef RZV_RIIC4_BASE
#  define RZV_RIIC4_BASE              0x14401400
#endif
#ifndef RZV_RIIC5_BASE
#  define RZV_RIIC5_BASE              0x14401800
#endif
#ifndef RZV_RIIC6_BASE
#  define RZV_RIIC6_BASE              0x14401C00
#endif
#ifndef RZV_RIIC7_BASE
#  define RZV_RIIC7_BASE              0x14402000
#endif
#ifndef RZV_RIIC8_BASE
#  define RZV_RIIC8_BASE              0x11C01000
#endif

/* RIIC Register Offsets **************************************************/

/* ICCR%s Registers (1-2) */
#define RZV_RIIC_ICCR_OFFSET(m)                 (0x00000000 + ((m) * 0x00000001))  /* ICCR Register %s */
/* ICMR%s Registers (1-3) */
#define RZV_RIIC_ICMR_OFFSET(m)                 (0x00000002 + ((m) * 0x00000001))  /* ICMR Register %s */
/* ICSAR%s Registers (0-2) */
#define RZV_RIIC_ICSAR_OFFSET(m)                (0x0000000a + ((m) * 0x00000002))  /* ICSAR Register %s */
/* ICSARU%s Registers (0-2) */
#define RZV_RIIC_ICSARU_OFFSET(m)               (0x0000000b + ((m) * 0x00000002))  /* ICSARU Register %s */
/* ICSR%s Registers (1-2) */
#define RZV_RIIC_ICSR_OFFSET(m)                 (0x00000008 + ((m) * 0x00000001))  /* ICSR Register %s */
#define RZV_RIIC_ICFER_OFFSET                            0x0005  /* I2C Bus Function Enable Register */
#define RZV_RIIC_ICSER_OFFSET                            0x0006  /* I2C Bus Status Enable Register */
#define RZV_RIIC_ICIER_OFFSET                            0x0007  /* I2C Bus Interrupt Enable Register */
#define RZV_RIIC_ICBRL_OFFSET                            0x0010  /* I2C Bus Bit Rate Low-Level Register */
#define RZV_RIIC_ICBRH_OFFSET                            0x0011  /* I2C Bus Bit Rate High-Level Register */
#define RZV_RIIC_ICDRT_OFFSET                            0x0012  /* I2C Bus Transmit Data Register */
#define RZV_RIIC_ICDRR_OFFSET                            0x0013  /* I2C Bus Receive Data Register */

/* RIIC Register Addresses *************************************************/

#define RZV_RIIC_ICCR(ch,m)                     (RZV_RIIC##ch##_BASE + RZV_RIIC_ICCR_OFFSET(m))
#define RZV_RIIC_ICMR(ch,m)                     (RZV_RIIC##ch##_BASE + RZV_RIIC_ICMR_OFFSET(m))
#define RZV_RIIC_ICSAR(ch,m)                    (RZV_RIIC##ch##_BASE + RZV_RIIC_ICSAR_OFFSET(m))
#define RZV_RIIC_ICSARU(ch,m)                   (RZV_RIIC##ch##_BASE + RZV_RIIC_ICSARU_OFFSET(m))
#define RZV_RIIC_ICSR(ch,m)                     (RZV_RIIC##ch##_BASE + RZV_RIIC_ICSR_OFFSET(m))
#define RZV_RIIC_ICFER(ch)                           (RZV_RIIC##ch##_BASE + RZV_RIIC_ICFER_OFFSET)
#define RZV_RIIC_ICSER(ch)                           (RZV_RIIC##ch##_BASE + RZV_RIIC_ICSER_OFFSET)
#define RZV_RIIC_ICIER(ch)                           (RZV_RIIC##ch##_BASE + RZV_RIIC_ICIER_OFFSET)
#define RZV_RIIC_ICBRL(ch)                           (RZV_RIIC##ch##_BASE + RZV_RIIC_ICBRL_OFFSET)
#define RZV_RIIC_ICBRH(ch)                           (RZV_RIIC##ch##_BASE + RZV_RIIC_ICBRH_OFFSET)
#define RZV_RIIC_ICDRT(ch)                           (RZV_RIIC##ch##_BASE + RZV_RIIC_ICDRT_OFFSET)
#define RZV_RIIC_ICDRR(ch)                           (RZV_RIIC##ch##_BASE + RZV_RIIC_ICDRR_OFFSET)

/* RIIC ICCR Register Bit Definitions (Parameterized) **********************/

#define RIIC_ICCR_SDAI(m)                                 (1 << 0)  /* Sdai */
#define RIIC_ICCR_SCLI(m)                                 (1 << 1)  /* Scli */
#define RIIC_ICCR_SDAO(m)                                 (1 << 2)  /* Sdao */
#define RIIC_ICCR_SCLO(m)                                 (1 << 3)  /* Sclo */
#define RIIC_ICCR_SOWP(m)                                 (1 << 4)  /* Sowp */
#define RIIC_ICCR_CLO(m)                                  (1 << 5)  /* Clo */
#define RIIC_ICCR_IICRST(m)                               (1 << 6)  /* Iicrst */
#define RIIC_ICCR_ICE(m)                                  (1 << 7)  /* Ice */

/* RIIC ICMR Register Bit Definitions (Parameterized) **********************/

#define RIIC_ICMR_BC_SHIFT                                (0)      /* Bits 0-2: Bc */
#define RIIC_ICMR_BC_MASK(m)                              (0x7 << RIIC_ICMR_BC_SHIFT)
#define RIIC_ICMR_BC(m,val)                               (((val) << RIIC_ICMR_BC_SHIFT) & RIIC_ICMR_BC_MASK(m))
#define RIIC_ICMR_BCWP(m)                                 (1 << 3)  /* Bcwp */
#define RIIC_ICMR_CKS_SHIFT                               (4)      /* Bits 4-6: Cks */
#define RIIC_ICMR_CKS_MASK(m)                             (0x7 << RIIC_ICMR_CKS_SHIFT)
#define RIIC_ICMR_CKS(m,val)                              (((val) << RIIC_ICMR_CKS_SHIFT) & RIIC_ICMR_CKS_MASK(m))
#define RIIC_ICMR_MTWP(m)                                 (1 << 7)  /* Mtwp */

/* RIIC ICSAR Register Bit Definitions (Parameterized) *********************/

#define RIIC_ICSAR_SVA0(m)                                (1 << 0)  /* Sva0 */
#define RIIC_ICSAR_SVA_SHIFT                              (1)      /* Bits 1-7: Sva */
#define RIIC_ICSAR_SVA_MASK(m)                            (0x7f << RIIC_ICSAR_SVA_SHIFT)
#define RIIC_ICSAR_SVA(m,val)                             (((val) << RIIC_ICSAR_SVA_SHIFT) & RIIC_ICSAR_SVA_MASK(m))

/* RIIC ICSARU Register Bit Definitions (Parameterized) ********************/

#define RIIC_ICSARU_FS(m)                                 (1 << 0)  /* Fs */
#define RIIC_ICSARU_SVA_SHIFT                             (1)      /* Bits 1-2: Sva */
#define RIIC_ICSARU_SVA_MASK(m)                           (0x3 << RIIC_ICSARU_SVA_SHIFT)
#define RIIC_ICSARU_SVA(m,val)                            (((val) << RIIC_ICSARU_SVA_SHIFT) & RIIC_ICSARU_SVA_MASK(m))

/* RIIC ICSR Register Bit Definitions (Parameterized) **********************/

#define RIIC_ICSR_AAS(m,n)                                (1u << (0 + ((unsigned)(n) * 1)))  /* Aas0 */

#define RIIC_ICSR_GCA(m)                                  (1 << 3)  /* Gca */
#define RIIC_ICSR_DID(m)                                  (1 << 5)  /* Did */
#define RIIC_ICSR_HOA(m)                                  (1 << 7)  /* Hoa */

/* RIIC ICBRH Register Bit Definitions *******************************/

#define RIIC_ICBRH_BRH_SHIFT                    (0)      /* Bits 0-4: Brh */
#define RIIC_ICBRH_BRH_MASK                     (0x1f << RIIC_ICBRH_BRH_SHIFT)

/* RIIC ICBRL Register Bit Definitions *******************************/

#define RIIC_ICBRL_BRL_SHIFT                    (0)      /* Bits 0-4: Brl */
#define RIIC_ICBRL_BRL_MASK                     (0x1f << RIIC_ICBRL_BRL_SHIFT)

/* RIIC ICDRR Register Bit Definitions *******************************/

#define RIIC_ICDRR_DRR_SHIFT                    (0)      /* Bits 0-7: Drr */
#define RIIC_ICDRR_DRR_MASK                     (0xff << RIIC_ICDRR_DRR_SHIFT)

/* RIIC ICDRT Register Bit Definitions *******************************/

#define RIIC_ICDRT_DRT_SHIFT                    (0)      /* Bits 0-7: Drt */
#define RIIC_ICDRT_DRT_MASK                     (0xff << RIIC_ICDRT_DRT_SHIFT)

/* RIIC ICFER Register Bit Definitions *******************************/

#define RIIC_ICFER_TMOE                         (1 << 0)  /* Tmoe */

#define RIIC_ICFER_MALE                         (1 << 1)  /* Male */

#define RIIC_ICFER_NALE                         (1 << 2)  /* Nale */

#define RIIC_ICFER_SALE                         (1 << 3)  /* Sale */

#define RIIC_ICFER_NACKE                        (1 << 4)  /* Nacke */

#define RIIC_ICFER_NFE                          (1 << 5)  /* Nfe */

#define RIIC_ICFER_SCLE                         (1 << 6)  /* Scle */

#define RIIC_ICFER_FMPE                         (1 << 7)  /* Fmpe */

/* RIIC ICIER Register Bit Definitions *******************************/

#define RIIC_ICIER_TMOIE                        (1 << 0)  /* Tmoie */

#define RIIC_ICIER_ALIE                         (1 << 1)  /* Alie */

#define RIIC_ICIER_STIE                         (1 << 2)  /* Stie */

#define RIIC_ICIER_SPIE                         (1 << 3)  /* Spie */

#define RIIC_ICIER_NAKIE                        (1 << 4)  /* Nakie */

#define RIIC_ICIER_RIE                          (1 << 5)  /* Rie */

#define RIIC_ICIER_TEIE                         (1 << 6)  /* Teie */

#define RIIC_ICIER_TIE                          (1 << 7)  /* Tie */

/* RIIC ICSER Register Bit Definitions *******************************/

#define RIIC_ICSER_SAR0E                        (1 << 0)  /* Sar0E */

#define RIIC_ICSER_SAR1E                        (1 << 1)  /* Sar1E */

#define RIIC_ICSER_SAR2E                        (1 << 2)  /* Sar2E */

#define RIIC_ICSER_GCAE                         (1 << 3)  /* Gcae */

#define RIIC_ICSER_DIDE                         (1 << 5)  /* Dide */

#define RIIC_ICSER_HOAE                         (1 << 7)  /* Hoae */

/* RIIC Channel definitions */
#define RZV_RIIC_CHANNEL_0         0
#define RZV_RIIC_CHANNEL_1         1
#define RZV_RIIC_CHANNEL_2         2
#define RZV_RIIC_CHANNEL_3         3
#define RZV_RIIC_CHANNEL_4         4
#define RZV_RIIC_CHANNEL_5         5
#define RZV_RIIC_CHANNEL_6         6
#define RZV_RIIC_CHANNEL_7         7
#define RZV_RIIC_CHANNEL_8         8

/* Maximum number of RIIC channels */
#define RZV_RIIC_MAX_CHANNELS      9

/*
 * Backwards-compatible register/bitfield names expected by the
 * existing RIIC driver. The driver uses numbered register names
 * (ICMR1/ICMR3, ICCR1/ICCR2, ICSR2) and bitfield names without
 * the Renesas R_ prefix. Provide mappings to the parameterized
 * offsets and (when available) to the Renesas CMSIS iobitmasks
 * present in the tree (R_RIIC_*). This keeps the driver unchanged
 * while using the canonical header definitions here.
 */

/* Concrete register offsets (map numbered names to parameterized offsets)
 * Note: the parameter 'm' in the parameterized macros follows the same
 * numbering used by the driver (1..3 etc).
 */
#ifndef RZV_RIIC_ICMR1_OFFSET
#  define RZV_RIIC_ICMR1_OFFSET    RZV_RIIC_ICMR_OFFSET(1)
#endif

#ifndef RZV_RIIC_ICMR2_OFFSET
#  define RZV_RIIC_ICMR2_OFFSET    RZV_RIIC_ICMR_OFFSET(2)
#endif

#ifndef RZV_RIIC_ICMR3_OFFSET
#  define RZV_RIIC_ICMR3_OFFSET    RZV_RIIC_ICMR_OFFSET(3)
#endif

#ifndef RZV_RIIC_ICCR1_OFFSET
#  define RZV_RIIC_ICCR1_OFFSET    RZV_RIIC_ICCR_OFFSET(1)
#endif

#ifndef RZV_RIIC_ICCR2_OFFSET
#  define RZV_RIIC_ICCR2_OFFSET    RZV_RIIC_ICCR_OFFSET(2)
#endif

#ifndef RZV_RIIC_ICSR1_OFFSET
#  define RZV_RIIC_ICSR1_OFFSET    RZV_RIIC_ICSR_OFFSET(1)
#endif

#ifndef RZV_RIIC_ICSR2_OFFSET
#  define RZV_RIIC_ICSR2_OFFSET    RZV_RIIC_ICSR_OFFSET(2)
#endif

/* Bitfield compatibility: map driver-expected names to either the
 * generic parameterized macros above or the Renesas iobitmask defines
 * (which use the R_RIIC_* naming). Prefer the R_RIIC_* defines when
 * available in the tree.
 */

/* ICMR1: clock selection mask/shift */
#ifndef RIIC_ICMR1_CKS_MASK
#  ifdef R_RIIC_ICMR1_CKS_Msk
#    define RIIC_ICMR1_CKS_MASK   (R_RIIC_ICMR1_CKS_Msk)
#  else
#    define RIIC_ICMR1_CKS_MASK   RIIC_ICMR_CKS_MASK(1)
#  endif
#endif

#ifndef RIIC_ICMR1_CKS_SHIFT
#  ifdef R_RIIC_ICMR1_CKS_Pos
#    define RIIC_ICMR1_CKS_SHIFT  (R_RIIC_ICMR1_CKS_Pos)
#  else
#    define RIIC_ICMR1_CKS_SHIFT  RIIC_ICMR_CKS_SHIFT
#  endif
#endif

/* ICCR2 control bits (master/transmit/start/stop/restart) */
#ifndef RIIC_ICCR2_MST
#  ifdef R_RIIC_ICCR2_MST_Msk
#    define RIIC_ICCR2_MST       (R_RIIC_ICCR2_MST_Msk)
#  else
#    define RIIC_ICCR2_MST       (1 << 6)
#  endif
#endif

#ifndef RIIC_ICCR2_TRS
#  ifdef R_RIIC_ICCR2_TRS_Msk
#    define RIIC_ICCR2_TRS       (R_RIIC_ICCR2_TRS_Msk)
#  else
#    define RIIC_ICCR2_TRS       (1 << 5)
#  endif
#endif

#ifndef RIIC_ICCR2_ST
#  ifdef R_RIIC_ICCR2_ST_Msk
#    define RIIC_ICCR2_ST        (R_RIIC_ICCR2_ST_Msk)
#  else
#    define RIIC_ICCR2_ST        (1 << 1)
#  endif
#endif

#ifndef RIIC_ICCR2_SP
#  ifdef R_RIIC_ICCR2_SP_Msk
#    define RIIC_ICCR2_SP        (R_RIIC_ICCR2_SP_Msk)
#  else
#    define RIIC_ICCR2_SP        (1 << 3)
#  endif
#endif

#ifndef RIIC_ICCR2_RS
#  ifdef R_RIIC_ICCR2_RS_Msk
#    define RIIC_ICCR2_RS        (R_RIIC_ICCR2_RS_Msk)
#  else
#    define RIIC_ICCR2_RS        (1 << 2)
#  endif
#endif

/* ICMR3 noise filter / wait */
#ifndef RIIC_ICMR3_NF_MASK
#  ifdef R_RIIC_ICMR3_NF_Msk
#    define RIIC_ICMR3_NF_MASK   (R_RIIC_ICMR3_NF_Msk)
#  else
#    define RIIC_ICMR3_NF_MASK   0x03
#  endif
#endif

#ifndef RIIC_ICMR3_WAIT
#  ifdef R_RIIC_ICMR3_WAIT_Msk
#    define RIIC_ICMR3_WAIT      (R_RIIC_ICMR3_WAIT_Msk)
#  else
#    define RIIC_ICMR3_WAIT      (1 << 6)
#  endif
#endif

/* ICSR2 status flags */
#ifndef RIIC_ICSR2_NACKF
#  ifdef R_RIIC_ICSR2_NACKF_Msk
#    define RIIC_ICSR2_NACKF     (R_RIIC_ICSR2_NACKF_Msk)
#  else
#    define RIIC_ICSR2_NACKF     (1 << 4)
#  endif
#endif

#ifndef RIIC_ICSR2_AL
#  ifdef R_RIIC_ICSR2_AL_Msk
#    define RIIC_ICSR2_AL        (R_RIIC_ICSR2_AL_Msk)
#  else
#    define RIIC_ICSR2_AL        (1 << 1)
#  endif
#endif

#ifndef RIIC_ICSR2_TMOF
#  ifdef R_RIIC_ICSR2_TMOF_Msk
#    define RIIC_ICSR2_TMOF      (R_RIIC_ICSR2_TMOF_Msk)
#  else
#    define RIIC_ICSR2_TMOF      (1 << 0)
#  endif
#endif

#ifndef RIIC_ICSR2_STOP
#  ifdef R_RIIC_ICSR2_STOP_Msk
#    define RIIC_ICSR2_STOP      (R_RIIC_ICSR2_STOP_Msk)
#  else
#    define RIIC_ICSR2_STOP      (1 << 3)
#  endif
#endif

/* ICCR1 bits */
#ifndef RIIC_ICCR1_IICRST
#  ifdef R_RIIC_ICCR1_IICRST_Msk
#    define RIIC_ICCR1_IICRST    (R_RIIC_ICCR1_IICRST_Msk)
#  else
#    define RIIC_ICCR1_IICRST    (1 << 6)
#  endif
#endif

#ifndef RIIC_ICCR1_ICE
#  ifdef R_RIIC_ICCR1_ICE_Msk
#    define RIIC_ICCR1_ICE       (R_RIIC_ICCR1_ICE_Msk)
#  else
#    define RIIC_ICCR1_ICE       (1 << 7)
#  endif
#endif

/* ICMR3 ACK bit used when sending NACK */
#ifndef RIIC_ICMR3_ACKBT
#  ifdef R_RIIC_ICMR3_ACKBT_Msk
#    define RIIC_ICMR3_ACKBT     (R_RIIC_ICMR3_ACKBT_Msk)
#  else
#    define RIIC_ICMR3_ACKBT     (1 << 3)
#  endif
#endif

/* Bit rate configuration constants ****************************************/
/* These values are calculated for P0CLK = 100MHz (RZV2H default)
 * Formula: SCL frequency = P0CLK / (2 * (BRH + 1 + BRL + 1) * 2^CKS)
 *
 * For 100kHz (Standard mode):
 *   100000 = 100000000 / (2 * (BRH + 1 + BRL + 1) * 2^CKS)
 *   Need: (BRH + BRL + 2) * 2^CKS = 500
 *   Using CKS=3 (divide by 8): BRH + BRL + 2 = 62.5 ≈ 63
 *   Using BRH=31, BRL=30: (31+1+30+1)*8 = 504 → ~99.2kHz
 *
 * For 400kHz (Fast mode):
 *   400000 = 100000000 / (2 * (BRH + 1 + BRL + 1) * 2^CKS)
 *   Need: (BRH + BRL + 2) * 2^CKS = 125
 *   Using CKS=3 (divide by 8): BRH + BRL + 2 = 15.625 ≈ 16
 *   Using BRH=7, BRL=7: (7+1+7+1)*8 = 128 → ~390kHz
 *
 * For 1MHz (Fast mode plus):
 *   1000000 = 100000000 / (2 * (BRH + 1 + BRL + 1) * 2^CKS)
 *   Need: (BRH + BRL + 2) * 2^CKS = 50
 *   Using CKS=2 (divide by 4): BRH + BRL + 2 = 12.5 ≈ 13
 *   Using BRH=6, BRL=5: (6+1+5+1)*4 = 52 → ~961kHz
 */

/* Standard mode: ~100kHz */
#define RIIC_CKS_100K       3    /* Clock divisor: divide by 2^3 = 8 */
#define RIIC_BRH_100K       31   /* Bit rate high period */
#define RIIC_BRL_100K       30   /* Bit rate low period */

/* Fast mode: ~400kHz */
#define RIIC_CKS_400K       3    /* Clock divisor: divide by 2^3 = 8 */
#define RIIC_BRH_400K       7    /* Bit rate high period */
#define RIIC_BRL_400K       7    /* Bit rate low period */

/* Fast mode plus: ~1MHz */
#define RIIC_CKS_1M         2    /* Clock divisor: divide by 2^2 = 4 */
#define RIIC_BRH_1M         6    /* Bit rate high period */
#define RIIC_BRL_1M         5    /* Bit rate low period */

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_I2C_H */

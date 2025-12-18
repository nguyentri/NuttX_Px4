/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_i3c.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_I3C_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_I3C_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* I3C Base Addresses ****************************************************/

#ifndef RZV_I3C0_BASE
#  define RZV_I3C0_BASE               0x12400000
#endif
#ifndef RZV_I3C_BASE
#  define RZV_I3C_BASE                RZV_I3C0_BASE
#endif

/* I3C Register Offsets ***************************************************/

/* DATBAS%s Registers (0-7) */
#define RZV_I3C_DATBAS_OFFSET(m)                (0x00000218 + ((m) * 0x00000004))  /* DATBAS Register %s */
/* MSDCT%s Registers (0-7) */
#define RZV_I3C_MSDCT_OFFSET(m)                 (0x000002c4 + ((m) * 0x00000004))  /* MSDCT Register %s */
/* SDATBAS%s Registers (0-2) */
#define RZV_I3C_SDATBAS_OFFSET(m)               (0x000002a4 + ((m) * 0x00000004))  /* SDATBAS Register %s */
/* SVDVAD%s Registers (0-2) */
#define RZV_I3C_SVDVAD_OFFSET(m)                (0x00000324 + ((m) * 0x00000004))  /* SVDVAD Register %s */
#define RZV_I3C_PRTS_OFFSET                              0x0000  /* PRTS */
#define RZV_I3C_BCTL_OFFSET                              0x0014  /* BCTL */
#define RZV_I3C_MSDVAD_OFFSET                            0x0018  /* MSDVAD */
#define RZV_I3C_RSTCTL_OFFSET                            0x0020  /* RSTCTL */
#define RZV_I3C_PRSST_OFFSET                             0x0024  /* PRSST */
#define RZV_I3C_INST_OFFSET                              0x0030  /* INST */
#define RZV_I3C_INSTE_OFFSET                             0x0034  /* INSTE */
#define RZV_I3C_INIE_OFFSET                              0x0038  /* INIE */
#define RZV_I3C_DVCT_OFFSET                              0x0040  /* DVCT */
#define RZV_I3C_IBINCTL_OFFSET                           0x0054  /* IBINCTL */
#define RZV_I3C_BFCTL_OFFSET                             0x005C  /* BFCTL */
#define RZV_I3C_SVCTL_OFFSET                             0x0060  /* SVCTL */
#define RZV_I3C_REFCKCTL_OFFSET                          0x006C  /* REFCKCTL */
#define RZV_I3C_STDBR_OFFSET                             0x0070  /* STDBR */
#define RZV_I3C_EXTBR_OFFSET                             0x0074  /* EXTBR */
#define RZV_I3C_BFRECDT_OFFSET                           0x0078  /* BFRECDT */
#define RZV_I3C_BAVLCDT_OFFSET                           0x007C  /* BAVLCDT */
#define RZV_I3C_BIDLCDT_OFFSET                           0x0080  /* BIDLCDT */
#define RZV_I3C_OUTCTL_OFFSET                            0x0084  /* OUTCTL */
#define RZV_I3C_INCTL_OFFSET                             0x0088  /* INCTL */
#define RZV_I3C_TMOCTL_OFFSET                            0x008C  /* TMOCTL */
#define RZV_I3C_WUCTL_OFFSET                             0x0094  /* WUCTL */
#define RZV_I3C_ACKCTL_OFFSET                            0x009C  /* ACKCTL */
#define RZV_I3C_SCSTRCTL_OFFSET                          0x00A0  /* SCSTRCTL */
#define RZV_I3C_SCSTLCTL_OFFSET                          0x00AC  /* SCSTLCTL */
#define RZV_I3C_SVTDLG0_OFFSET                           0x00BC  /* SVTDLG0 */
#define RZV_I3C_STCTL_OFFSET                             0x011C  /* STCTL */
#define RZV_I3C_ATCTL_OFFSET                             0x0120  /* ATCTL */
#define RZV_I3C_ATCCNTE_OFFSET                           0x0124  /* ATCCNTE */
#define RZV_I3C_CNDCTL_OFFSET                            0x0138  /* CNDCTL */
#define RZV_I3C_NRSPQP_OFFSET                            0x0148  /* NRSPQP */
#define RZV_I3C_NTDTBP0_OFFSET                           0x014C  /* NTDTBP0 */
#define RZV_I3C_NTDTBP0_BY_OFFSET                        0x0150  /* NTDTBP0_BY */
#define RZV_I3C_NIBIQP_OFFSET                            0x0174  /* NIBIQP */
#define RZV_I3C_NRSQP_OFFSET                             0x0178  /* NRSQP */
#define RZV_I3C_NQTHCTL_OFFSET                           0x0188  /* NQTHCTL */
#define RZV_I3C_NTBTHCTL0_OFFSET                         0x018C  /* NTBTHCTL0 */
#define RZV_I3C_NRQTHCTL_OFFSET                          0x01B8  /* NRQTHCTL */
#define RZV_I3C_BST_OFFSET                               0x01C8  /* BST */
#define RZV_I3C_BSTE_OFFSET                              0x01CC  /* BSTE */
#define RZV_I3C_BIE_OFFSET                               0x01D0  /* BIE */
#define RZV_I3C_BSTFC_OFFSET                             0x01D4  /* BSTFC */
#define RZV_I3C_NTST_OFFSET                              0x01D8  /* NTST */
#define RZV_I3C_NTSTE_OFFSET                             0x01DC  /* NTSTE */
#define RZV_I3C_NTIE_OFFSET                              0x01E0  /* NTIE */
#define RZV_I3C_BCST_OFFSET                              0x0204  /* BCST */
#define RZV_I3C_SVST_OFFSET                              0x0208  /* SVST */
#define RZV_I3C_WUST_OFFSET                              0x020C  /* WUST */
#define RZV_I3C_MRCCPT_OFFSET                            0x0210  /* MRCCPT */
#define RZV_I3C_EXDATBAS_OFFSET                          0x0304  /* EXDATBAS */
#define RZV_I3C_SVDCT_OFFSET                             0x0314  /* SVDCT */
#define RZV_I3C_SDCTPIDL_OFFSET                          0x0318  /* SDCTPIDL */
#define RZV_I3C_SDCTPIDH_OFFSET                          0x031C  /* SDCTPIDH */
#define RZV_I3C_CSECMD_OFFSET                            0x0344  /* CSECMD */
#define RZV_I3C_CEACTST_OFFSET                           0x0348  /* CEACTST */
#define RZV_I3C_CMWLG_OFFSET                             0x034C  /* CMWLG */
#define RZV_I3C_CMRLG_OFFSET                             0x0350  /* CMRLG */
#define RZV_I3C_CETSTMD_OFFSET                           0x0354  /* CETSTMD */
#define RZV_I3C_CGDVST_OFFSET                            0x0358  /* CGDVST */
#define RZV_I3C_CMDSPW_OFFSET                            0x035C  /* CMDSPW */
#define RZV_I3C_CMDSPR_OFFSET                            0x0360  /* CMDSPR */
#define RZV_I3C_CMDSPT_OFFSET                            0x0364  /* CMDSPT */
#define RZV_I3C_CETSM_OFFSET                             0x0368  /* CETSM */
#define RZV_I3C_CETSS_OFFSET                             0x036C  /* CETSS */
#define RZV_I3C_BITCNT_OFFSET                            0x0374  /* BITCNT */
#define RZV_I3C_NQSTLV_OFFSET                            0x0388  /* NQSTLV */
#define RZV_I3C_NDBSTLV0_OFFSET                          0x038C  /* NDBSTLV0 */
#define RZV_I3C_NRSQSTLV_OFFSET                          0x03B4  /* NRSQSTLV */
#define RZV_I3C_PRSTDBG_OFFSET                           0x03C0  /* PRSTDBG */
#define RZV_I3C_MSERRCNT_OFFSET                          0x03C4  /* MSERRCNT */
#define RZV_I3C_SC1CPT_OFFSET                            0x03D4  /* SC1CPT */
#define RZV_I3C_SC2CPT_OFFSET                            0x03D8  /* SC2CPT */

/* I3C Register Addresses **************************************************/

#define RZV_I3C_DATBAS(m)                       (RZV_I3C_BASE + RZV_I3C_DATBAS_OFFSET(m))
#define RZV_I3C_MSDCT(m)                        (RZV_I3C_BASE + RZV_I3C_MSDCT_OFFSET(m))
#define RZV_I3C_SDATBAS(m)                      (RZV_I3C_BASE + RZV_I3C_SDATBAS_OFFSET(m))
#define RZV_I3C_SVDVAD(m)                       (RZV_I3C_BASE + RZV_I3C_SVDVAD_OFFSET(m))
#define RZV_I3C_PRTS                                 (RZV_I3C_BASE + RZV_I3C_PRTS_OFFSET)
#define RZV_I3C_BCTL                                 (RZV_I3C_BASE + RZV_I3C_BCTL_OFFSET)
#define RZV_I3C_MSDVAD                               (RZV_I3C_BASE + RZV_I3C_MSDVAD_OFFSET)
#define RZV_I3C_RSTCTL                               (RZV_I3C_BASE + RZV_I3C_RSTCTL_OFFSET)
#define RZV_I3C_PRSST                                (RZV_I3C_BASE + RZV_I3C_PRSST_OFFSET)
#define RZV_I3C_INST                                 (RZV_I3C_BASE + RZV_I3C_INST_OFFSET)
#define RZV_I3C_INSTE                                (RZV_I3C_BASE + RZV_I3C_INSTE_OFFSET)
#define RZV_I3C_INIE                                 (RZV_I3C_BASE + RZV_I3C_INIE_OFFSET)
#define RZV_I3C_DVCT                                 (RZV_I3C_BASE + RZV_I3C_DVCT_OFFSET)
#define RZV_I3C_IBINCTL                              (RZV_I3C_BASE + RZV_I3C_IBINCTL_OFFSET)
#define RZV_I3C_BFCTL                                (RZV_I3C_BASE + RZV_I3C_BFCTL_OFFSET)
#define RZV_I3C_SVCTL                                (RZV_I3C_BASE + RZV_I3C_SVCTL_OFFSET)
#define RZV_I3C_REFCKCTL                             (RZV_I3C_BASE + RZV_I3C_REFCKCTL_OFFSET)
#define RZV_I3C_STDBR                                (RZV_I3C_BASE + RZV_I3C_STDBR_OFFSET)
#define RZV_I3C_EXTBR                                (RZV_I3C_BASE + RZV_I3C_EXTBR_OFFSET)
#define RZV_I3C_BFRECDT                              (RZV_I3C_BASE + RZV_I3C_BFRECDT_OFFSET)
#define RZV_I3C_BAVLCDT                              (RZV_I3C_BASE + RZV_I3C_BAVLCDT_OFFSET)
#define RZV_I3C_BIDLCDT                              (RZV_I3C_BASE + RZV_I3C_BIDLCDT_OFFSET)
#define RZV_I3C_OUTCTL                               (RZV_I3C_BASE + RZV_I3C_OUTCTL_OFFSET)
#define RZV_I3C_INCTL                                (RZV_I3C_BASE + RZV_I3C_INCTL_OFFSET)
#define RZV_I3C_TMOCTL                               (RZV_I3C_BASE + RZV_I3C_TMOCTL_OFFSET)
#define RZV_I3C_WUCTL                                (RZV_I3C_BASE + RZV_I3C_WUCTL_OFFSET)
#define RZV_I3C_ACKCTL                               (RZV_I3C_BASE + RZV_I3C_ACKCTL_OFFSET)
#define RZV_I3C_SCSTRCTL                             (RZV_I3C_BASE + RZV_I3C_SCSTRCTL_OFFSET)
#define RZV_I3C_SCSTLCTL                             (RZV_I3C_BASE + RZV_I3C_SCSTLCTL_OFFSET)
#define RZV_I3C_SVTDLG0                              (RZV_I3C_BASE + RZV_I3C_SVTDLG0_OFFSET)
#define RZV_I3C_STCTL                                (RZV_I3C_BASE + RZV_I3C_STCTL_OFFSET)
#define RZV_I3C_ATCTL                                (RZV_I3C_BASE + RZV_I3C_ATCTL_OFFSET)
#define RZV_I3C_ATCCNTE                              (RZV_I3C_BASE + RZV_I3C_ATCCNTE_OFFSET)
#define RZV_I3C_CNDCTL                               (RZV_I3C_BASE + RZV_I3C_CNDCTL_OFFSET)
#define RZV_I3C_NRSPQP                               (RZV_I3C_BASE + RZV_I3C_NRSPQP_OFFSET)
#define RZV_I3C_NTDTBP0                              (RZV_I3C_BASE + RZV_I3C_NTDTBP0_OFFSET)
#define RZV_I3C_NTDTBP0_BY                           (RZV_I3C_BASE + RZV_I3C_NTDTBP0_BY_OFFSET)
#define RZV_I3C_NIBIQP                               (RZV_I3C_BASE + RZV_I3C_NIBIQP_OFFSET)
#define RZV_I3C_NRSQP                                (RZV_I3C_BASE + RZV_I3C_NRSQP_OFFSET)
#define RZV_I3C_NQTHCTL                              (RZV_I3C_BASE + RZV_I3C_NQTHCTL_OFFSET)
#define RZV_I3C_NTBTHCTL0                            (RZV_I3C_BASE + RZV_I3C_NTBTHCTL0_OFFSET)
#define RZV_I3C_NRQTHCTL                             (RZV_I3C_BASE + RZV_I3C_NRQTHCTL_OFFSET)
#define RZV_I3C_BST                                  (RZV_I3C_BASE + RZV_I3C_BST_OFFSET)
#define RZV_I3C_BSTE                                 (RZV_I3C_BASE + RZV_I3C_BSTE_OFFSET)
#define RZV_I3C_BIE                                  (RZV_I3C_BASE + RZV_I3C_BIE_OFFSET)
#define RZV_I3C_BSTFC                                (RZV_I3C_BASE + RZV_I3C_BSTFC_OFFSET)
#define RZV_I3C_NTST                                 (RZV_I3C_BASE + RZV_I3C_NTST_OFFSET)
#define RZV_I3C_NTSTE                                (RZV_I3C_BASE + RZV_I3C_NTSTE_OFFSET)
#define RZV_I3C_NTIE                                 (RZV_I3C_BASE + RZV_I3C_NTIE_OFFSET)
#define RZV_I3C_BCST                                 (RZV_I3C_BASE + RZV_I3C_BCST_OFFSET)
#define RZV_I3C_SVST                                 (RZV_I3C_BASE + RZV_I3C_SVST_OFFSET)
#define RZV_I3C_WUST                                 (RZV_I3C_BASE + RZV_I3C_WUST_OFFSET)
#define RZV_I3C_MRCCPT                               (RZV_I3C_BASE + RZV_I3C_MRCCPT_OFFSET)
#define RZV_I3C_EXDATBAS                             (RZV_I3C_BASE + RZV_I3C_EXDATBAS_OFFSET)
#define RZV_I3C_SVDCT                                (RZV_I3C_BASE + RZV_I3C_SVDCT_OFFSET)
#define RZV_I3C_SDCTPIDL                             (RZV_I3C_BASE + RZV_I3C_SDCTPIDL_OFFSET)
#define RZV_I3C_SDCTPIDH                             (RZV_I3C_BASE + RZV_I3C_SDCTPIDH_OFFSET)
#define RZV_I3C_CSECMD                               (RZV_I3C_BASE + RZV_I3C_CSECMD_OFFSET)
#define RZV_I3C_CEACTST                              (RZV_I3C_BASE + RZV_I3C_CEACTST_OFFSET)
#define RZV_I3C_CMWLG                                (RZV_I3C_BASE + RZV_I3C_CMWLG_OFFSET)
#define RZV_I3C_CMRLG                                (RZV_I3C_BASE + RZV_I3C_CMRLG_OFFSET)
#define RZV_I3C_CETSTMD                              (RZV_I3C_BASE + RZV_I3C_CETSTMD_OFFSET)
#define RZV_I3C_CGDVST                               (RZV_I3C_BASE + RZV_I3C_CGDVST_OFFSET)
#define RZV_I3C_CMDSPW                               (RZV_I3C_BASE + RZV_I3C_CMDSPW_OFFSET)
#define RZV_I3C_CMDSPR                               (RZV_I3C_BASE + RZV_I3C_CMDSPR_OFFSET)
#define RZV_I3C_CMDSPT                               (RZV_I3C_BASE + RZV_I3C_CMDSPT_OFFSET)
#define RZV_I3C_CETSM                                (RZV_I3C_BASE + RZV_I3C_CETSM_OFFSET)
#define RZV_I3C_CETSS                                (RZV_I3C_BASE + RZV_I3C_CETSS_OFFSET)
#define RZV_I3C_BITCNT                               (RZV_I3C_BASE + RZV_I3C_BITCNT_OFFSET)
#define RZV_I3C_NQSTLV                               (RZV_I3C_BASE + RZV_I3C_NQSTLV_OFFSET)
#define RZV_I3C_NDBSTLV0                             (RZV_I3C_BASE + RZV_I3C_NDBSTLV0_OFFSET)
#define RZV_I3C_NRSQSTLV                             (RZV_I3C_BASE + RZV_I3C_NRSQSTLV_OFFSET)
#define RZV_I3C_PRSTDBG                              (RZV_I3C_BASE + RZV_I3C_PRSTDBG_OFFSET)
#define RZV_I3C_MSERRCNT                             (RZV_I3C_BASE + RZV_I3C_MSERRCNT_OFFSET)
#define RZV_I3C_SC1CPT                               (RZV_I3C_BASE + RZV_I3C_SC1CPT_OFFSET)
#define RZV_I3C_SC2CPT                               (RZV_I3C_BASE + RZV_I3C_SC2CPT_OFFSET)

/* I3C DATBAS Register Bit Definitions (Parameterized) *********************/

#define I3C_DATBAS_DVSTAD_SHIFT                           (0)      /* Bits 0-6: Dvstad */
#define I3C_DATBAS_DVSTAD_MASK(m)                         (0x7f << I3C_DATBAS_DVSTAD_SHIFT)
#define I3C_DATBAS_DVSTAD(m,val)                          (((val) << I3C_DATBAS_DVSTAD_SHIFT) & I3C_DATBAS_DVSTAD_MASK(m))
#define I3C_DATBAS_DVIBIPL(m)                             (1 << 12)  /* Dvibipl */
#define I3C_DATBAS_DVSIRRJ(m)                             (1 << 13)  /* Dvsirrj */
#define I3C_DATBAS_DVMRRJ(m)                              (1 << 14)  /* Dvmrrj */
#define I3C_DATBAS_DVIBITS(m)                             (1 << 15)  /* Dvibits */
#define I3C_DATBAS_DVDYAD_SHIFT                           (16)      /* Bits 16-23: Dvdyad */
#define I3C_DATBAS_DVDYAD_MASK(m)                         (0xff << I3C_DATBAS_DVDYAD_SHIFT)
#define I3C_DATBAS_DVDYAD(m,val)                          (((val) << I3C_DATBAS_DVDYAD_SHIFT) & I3C_DATBAS_DVDYAD_MASK(m))
#define I3C_DATBAS_DVNACK_SHIFT                           (29)      /* Bits 29-30: Dvnack */
#define I3C_DATBAS_DVNACK_MASK(m)                         (0x3 << I3C_DATBAS_DVNACK_SHIFT)
#define I3C_DATBAS_DVNACK(m,val)                          (((val) << I3C_DATBAS_DVNACK_SHIFT) & I3C_DATBAS_DVNACK_MASK(m))
#define I3C_DATBAS_DVTYP(m)                               (1 << 31)  /* Dvtyp */
#define I3C_DATBAS_SDSTAD_SHIFT                           (0)      /* Bits 0-9: Sdstad */
#define I3C_DATBAS_SDSTAD_MASK(m)                         (0x3ff << I3C_DATBAS_SDSTAD_SHIFT)
#define I3C_DATBAS_SDSTAD(m,val)                          (((val) << I3C_DATBAS_SDSTAD_SHIFT) & I3C_DATBAS_SDSTAD_MASK(m))
#define I3C_DATBAS_SDADLS(m)                              (1 << 10)  /* Sdadls */
#define I3C_DATBAS_SDIBIPL(m)                             (1 << 12)  /* Sdibipl */
#define I3C_DATBAS_SDDYAD_SHIFT                           (16)      /* Bits 16-22: Sddyad */
#define I3C_DATBAS_SDDYAD_MASK(m)                         (0x7f << I3C_DATBAS_SDDYAD_SHIFT)
#define I3C_DATBAS_SDDYAD(m,val)                          (((val) << I3C_DATBAS_SDDYAD_SHIFT) & I3C_DATBAS_SDDYAD_MASK(m))

/* I3C MSDCT Register Bit Definitions (Parameterized) **********************/

#define I3C_MSDCT_RBCR(m)                                 (1 << 8)  /* Rbcr0 */
#define I3C_MSDCT_RBCR(m)                                 (1 << 9)  /* Rbcr1 */
#define I3C_MSDCT_RBCR(m)                                 (1 << 10)  /* Rbcr2 */
#define I3C_MSDCT_RBCR(m)                                 (1 << 11)  /* Rbcr3 */
#define I3C_MSDCT_RBCR_SHIFT                              (14)      /* Bits 14-15: Rbcr76 */
#define I3C_MSDCT_RBCR_MASK(m)                            (0x3 << I3C_MSDCT_RBCR_SHIFT)
#define I3C_MSDCT_RBCR(m,val)                             (((val) << I3C_MSDCT_RBCR_SHIFT) & I3C_MSDCT_RBCR_MASK(m))

/* I3C SVDVAD Register Bit Definitions (Parameterized) *********************/

#define I3C_SVDVAD_SVAD_SHIFT                             (16)      /* Bits 16-25: Svad */
#define I3C_SVDVAD_SVAD_MASK(m)                           (0x3ff << I3C_SVDVAD_SVAD_SHIFT)
#define I3C_SVDVAD_SVAD(m,val)                            (((val) << I3C_SVDVAD_SVAD_SHIFT) & I3C_SVDVAD_SVAD_MASK(m))
#define I3C_SVDVAD_SADLG(m)                               (1 << 27)  /* Sadlg */
#define I3C_SVDVAD_SSTADV(m)                              (1 << 30)  /* Sstadv */
#define I3C_SVDVAD_SDYADV(m)                              (1 << 31)  /* Sdyadv */

/* I3C ACKCTL Register Bit Definitions *******************************/

#define I3C_ACKCTL_ACKR                         (1 << 0)  /* Ackr */

#define I3C_ACKCTL_ACKT                         (1 << 1)  /* Ackt */

#define I3C_ACKCTL_ACKTWP                       (1 << 2)  /* Acktwp */

/* I3C ATCCNTE Register Bit Definitions ******************************/

#define I3C_ATCCNTE_ATCE                        (1 << 0)  /* Atce */

/* I3C ATCTL Register Bit Definitions ********************************/

#define I3C_ATCTL_MREFOE                        (1 << 1)  /* Mrefoe */

#define I3C_ATCTL_AMEOE                         (1 << 2)  /* Ameoe */

#define I3C_ATCTL_CDIV_SHIFT                    (8)      /* Bits 8-15: Cdiv */
#define I3C_ATCTL_CDIV_MASK                     (0xff << I3C_ATCTL_CDIV_SHIFT)

/* I3C BAVLCDT Register Bit Definitions ******************************/

#define I3C_BAVLCDT_AVLCYC_SHIFT                (0)      /* Bits 0-8: Avlcyc */
#define I3C_BAVLCDT_AVLCYC_MASK                 (0x1ff << I3C_BAVLCDT_AVLCYC_SHIFT)

/* I3C BCST Register Bit Definitions *********************************/

#define I3C_BCST_BFREF                          (1 << 0)  /* Bfref */

#define I3C_BCST_BAVLF                          (1 << 1)  /* Bavlf */

#define I3C_BCST_BIDLF                          (1 << 2)  /* Bidlf */

/* I3C BCTL Register Bit Definitions *********************************/

#define I3C_BCTL_INCBA                          (1 << 0)  /* Incba */

#define I3C_BCTL_HJACKCTL                       (1 << 8)  /* Hjackctl */

#define I3C_BCTL_ABT                            (1 << 29)  /* Abt */

#define I3C_BCTL_RSM                            (1 << 30)  /* Rsm */

#define I3C_BCTL_BUSE                           (1 << 31)  /* Buse */

/* I3C BFCTL Register Bit Definitions ********************************/

#define I3C_BFCTL_MALE                          (1 << 0)  /* Male */

#define I3C_BFCTL_NALE                          (1 << 1)  /* Nale */

#define I3C_BFCTL_SALE                          (1 << 2)  /* Sale */

#define I3C_BFCTL_SCSYNE                        (1 << 8)  /* Scsyne */

#define I3C_BFCTL_SMBS                          (1 << 12)  /* Smbs */

#define I3C_BFCTL_FMPE                          (1 << 14)  /* Fmpe */

#define I3C_BFCTL_HSME                          (1 << 15)  /* Hsme */

/* I3C BFRECDT Register Bit Definitions ******************************/

#define I3C_BFRECDT_FRECYC_SHIFT                (0)      /* Bits 0-8: Frecyc */
#define I3C_BFRECDT_FRECYC_MASK                 (0x1ff << I3C_BFRECDT_FRECYC_SHIFT)

/* I3C BIDLCDT Register Bit Definitions ******************************/

#define I3C_BIDLCDT_IDLCYC_SHIFT                (0)      /* Bits 0-17: Idlcyc */
#define I3C_BIDLCDT_IDLCYC_MASK                 (0x3ffff << I3C_BIDLCDT_IDLCYC_SHIFT)

/* I3C BIE Register Bit Definitions **********************************/

#define I3C_BIE_STCNDDIE                        (1 << 0)  /* Stcnddie */

#define I3C_BIE_SPCNDDIE                        (1 << 1)  /* Spcnddie */

#define I3C_BIE_NACKDIE                         (1 << 4)  /* Nackdie */

#define I3C_BIE_TENDIE                          (1 << 8)  /* Tendie */

#define I3C_BIE_ALIE                            (1 << 16)  /* Alie */

#define I3C_BIE_TODIE                           (1 << 20)  /* Todie */

#define I3C_BIE_WUCNDDIE                        (1 << 24)  /* Wucnddie */

/* I3C BITCNT Register Bit Definitions *******************************/

#define I3C_BITCNT_BCNT_SHIFT                   (0)      /* Bits 0-4: Bcnt */
#define I3C_BITCNT_BCNT_MASK                    (0x1f << I3C_BITCNT_BCNT_SHIFT)

/* I3C BST Register Bit Definitions **********************************/

#define I3C_BST_STCNDDF                         (1 << 0)  /* Stcnddf */

#define I3C_BST_SPCNDDF                         (1 << 1)  /* Spcnddf */

#define I3C_BST_NACKDF                          (1 << 4)  /* Nackdf */

#define I3C_BST_TENDF                           (1 << 8)  /* Tendf */

#define I3C_BST_ALF                             (1 << 16)  /* Alf */

#define I3C_BST_TODF                            (1 << 20)  /* Todf */

#define I3C_BST_WUCNDDF                         (1 << 24)  /* Wucnddf */

/* I3C BSTE Register Bit Definitions *********************************/

#define I3C_BSTE_STCNDDE                        (1 << 0)  /* Stcndde */

#define I3C_BSTE_SPCNDDE                        (1 << 1)  /* Spcndde */

#define I3C_BSTE_NACKDE                         (1 << 4)  /* Nackde */

#define I3C_BSTE_TENDE                          (1 << 8)  /* Tende */

#define I3C_BSTE_ALE                            (1 << 16)  /* Ale */

#define I3C_BSTE_TODE                           (1 << 20)  /* Tode */

#define I3C_BSTE_WUCNDDE                        (1 << 24)  /* Wucndde */

/* I3C BSTFC Register Bit Definitions ********************************/

#define I3C_BSTFC_STCNDDFC                      (1 << 0)  /* Stcnddfc */

#define I3C_BSTFC_SPCNDDFC                      (1 << 1)  /* Spcnddfc */

#define I3C_BSTFC_NACKDFC                       (1 << 4)  /* Nackdfc */

#define I3C_BSTFC_TENDFC                        (1 << 8)  /* Tendfc */

#define I3C_BSTFC_ALFC                          (1 << 16)  /* Alfc */

#define I3C_BSTFC_TODFC                         (1 << 20)  /* Todfc */

#define I3C_BSTFC_WUCNDDFC                      (1 << 24)  /* Wucnddfc */

/* I3C B_ATTRG Register Bit Definitions ******************************/

#define I3C_B_ATTRG_ATSTRG                      (1 << 0)  /* Atstrg */

/* I3C B_INSTFC Register Bit Definitions *****************************/

#define I3C_B_INSTFC_INEFC                      (1 << 10)  /* Inefc */

/* I3C B_NCMDQP Register Bit Definitions *****************************/

#define I3C_B_NCMDQP_NCMDQP_SHIFT               (0)      /* Bits 0-31: Ncmdqp */
#define I3C_B_NCMDQP_NCMDQP_MASK                (0xffffffff << I3C_B_NCMDQP_NCMDQP_SHIFT)

/* I3C B_NTSTFC Register Bit Definitions *****************************/

#define I3C_B_NTSTFC_TDBEFC0                    (1 << 0)  /* Tdbefc0 */

#define I3C_B_NTSTFC_RDBFFC0                    (1 << 1)  /* Rdbffc0 */

#define I3C_B_NTSTFC_IBIQEFFC                   (1 << 2)  /* Ibiqeffc */

#define I3C_B_NTSTFC_CMDQEFC                    (1 << 3)  /* Cmdqefc */

#define I3C_B_NTSTFC_RSPQFFC                    (1 << 4)  /* Rspqffc */

#define I3C_B_NTSTFC_TABTFC                     (1 << 5)  /* Tabtfc */

#define I3C_B_NTSTFC_TEFC                       (1 << 9)  /* Tefc */

#define I3C_B_NTSTFC_RSQFFC                     (1 << 20)  /* Rsqffc */

/* I3C CEACTST Register Bit Definitions ******************************/

#define I3C_CEACTST_ACTST_SHIFT                 (0)      /* Bits 0-3: Actst */
#define I3C_CEACTST_ACTST_MASK                  (0xf << I3C_CEACTST_ACTST_SHIFT)

/* I3C CETSM Register Bit Definitions ********************************/

#define I3C_CETSM_SPTSYN                        (1 << 0)  /* Sptsyn */

#define I3C_CETSM_SPTASYN0                      (1 << 1)  /* Sptasyn0 */

#define I3C_CETSM_SPTASYN1                      (1 << 2)  /* Sptasyn1 */

#define I3C_CETSM_FREQ_SHIFT                    (8)      /* Bits 8-15: Freq */
#define I3C_CETSM_FREQ_MASK                     (0xff << I3C_CETSM_FREQ_SHIFT)

#define I3C_CETSM_INAC_SHIFT                    (16)      /* Bits 16-23: Inac */
#define I3C_CETSM_INAC_MASK                     (0xff << I3C_CETSM_INAC_SHIFT)

/* I3C CETSS Register Bit Definitions ********************************/

#define I3C_CETSS_SYNE                          (1 << 0)  /* Syne */

#define I3C_CETSS_ASYNE_SHIFT                   (1)      /* Bits 1-2: Asyne */
#define I3C_CETSS_ASYNE_MASK                    (0x3 << I3C_CETSS_ASYNE_SHIFT)

#define I3C_CETSS_ICOVF                         (1 << 7)  /* Icovf */

/* I3C CETSTMD Register Bit Definitions ******************************/

#define I3C_CETSTMD_TSTMD_SHIFT                 (0)      /* Bits 0-7: Tstmd */
#define I3C_CETSTMD_TSTMD_MASK                  (0xff << I3C_CETSTMD_TSTMD_SHIFT)

/* I3C CGDVST Register Bit Definitions *******************************/

#define I3C_CGDVST_PNDINT_SHIFT                 (0)      /* Bits 0-3: Pndint */
#define I3C_CGDVST_PNDINT_MASK                  (0xf << I3C_CGDVST_PNDINT_SHIFT)

#define I3C_CGDVST_PRTE                         (1 << 5)  /* Prte */

#define I3C_CGDVST_ACTMD_SHIFT                  (6)      /* Bits 6-7: Actmd */
#define I3C_CGDVST_ACTMD_MASK                   (0x3 << I3C_CGDVST_ACTMD_SHIFT)

#define I3C_CGDVST_VDRSV_SHIFT                  (8)      /* Bits 8-15: Vdrsv */
#define I3C_CGDVST_VDRSV_MASK                   (0xff << I3C_CGDVST_VDRSV_SHIFT)

/* I3C CMDSPR Register Bit Definitions *******************************/

#define I3C_CMDSPR_MSRDR_SHIFT                  (0)      /* Bits 0-2: Msrdr */
#define I3C_CMDSPR_MSRDR_MASK                   (0x7 << I3C_CMDSPR_MSRDR_SHIFT)

#define I3C_CMDSPR_CDTTIM_SHIFT                 (3)      /* Bits 3-5: Cdttim */
#define I3C_CMDSPR_CDTTIM_MASK                  (0x7 << I3C_CMDSPR_CDTTIM_SHIFT)

/* I3C CMDSPT Register Bit Definitions *******************************/

#define I3C_CMDSPT_MRTTIM_SHIFT                 (0)      /* Bits 0-23: Mrttim */
#define I3C_CMDSPT_MRTTIM_MASK                  (0xffffff << I3C_CMDSPT_MRTTIM_SHIFT)

#define I3C_CMDSPT_MRTE                         (1 << 31)  /* Mrte */

/* I3C CMDSPW Register Bit Definitions *******************************/

#define I3C_CMDSPW_MSWDR_SHIFT                  (0)      /* Bits 0-2: Mswdr */
#define I3C_CMDSPW_MSWDR_MASK                   (0x7 << I3C_CMDSPW_MSWDR_SHIFT)

/* I3C CMRLG Register Bit Definitions ********************************/

#define I3C_CMRLG_MRLG_SHIFT                    (0)      /* Bits 0-15: Mrlg */
#define I3C_CMRLG_MRLG_MASK                     (0xffff << I3C_CMRLG_MRLG_SHIFT)

#define I3C_CMRLG_IBIPSZ_SHIFT                  (16)      /* Bits 16-23: Ibipsz */
#define I3C_CMRLG_IBIPSZ_MASK                   (0xff << I3C_CMRLG_IBIPSZ_SHIFT)

/* I3C CMWLG Register Bit Definitions ********************************/

#define I3C_CMWLG_MWLG_SHIFT                    (0)      /* Bits 0-15: Mwlg */
#define I3C_CMWLG_MWLG_MASK                     (0xffff << I3C_CMWLG_MWLG_SHIFT)

/* I3C CNDCTL Register Bit Definitions *******************************/

#define I3C_CNDCTL_STCND                        (1 << 0)  /* Stcnd */

#define I3C_CNDCTL_SRCND                        (1 << 1)  /* Srcnd */

#define I3C_CNDCTL_SPCND                        (1 << 2)  /* Spcnd */

/* I3C CSECMD Register Bit Definitions *******************************/

#define I3C_CSECMD_SVIRQE                       (1 << 0)  /* Svirqe */

#define I3C_CSECMD_MSRQE                        (1 << 1)  /* Msrqe */

#define I3C_CSECMD_HJEVE                        (1 << 3)  /* Hjeve */

/* I3C DVCT Register Bit Definitions *********************************/

#define I3C_DVCT_IDX_SHIFT                      (19)      /* Bits 19-23: Idx */
#define I3C_DVCT_IDX_MASK                       (0x1f << I3C_DVCT_IDX_SHIFT)

/* I3C EXDATBAS Register Bit Definitions *****************************/

#define I3C_EXDATBAS_EDSTAD_SHIFT               (0)      /* Bits 0-6: Edstad */
#define I3C_EXDATBAS_EDSTAD_MASK                (0x7f << I3C_EXDATBAS_EDSTAD_SHIFT)

#define I3C_EXDATBAS_EDDYAD_SHIFT               (16)      /* Bits 16-23: Eddyad */
#define I3C_EXDATBAS_EDDYAD_MASK                (0xff << I3C_EXDATBAS_EDDYAD_SHIFT)

#define I3C_EXDATBAS_EDNACK_SHIFT               (29)      /* Bits 29-30: Ednack */
#define I3C_EXDATBAS_EDNACK_MASK                (0x3 << I3C_EXDATBAS_EDNACK_SHIFT)

#define I3C_EXDATBAS_EDTYP                      (1 << 31)  /* Edtyp */

/* I3C EXTBR Register Bit Definitions ********************************/

#define I3C_EXTBR_EBRLO_SHIFT                   (0)      /* Bits 0-7: Ebrlo */
#define I3C_EXTBR_EBRLO_MASK                    (0xff << I3C_EXTBR_EBRLO_SHIFT)

#define I3C_EXTBR_EBRHO_SHIFT                   (8)      /* Bits 8-15: Ebrho */
#define I3C_EXTBR_EBRHO_MASK                    (0xff << I3C_EXTBR_EBRHO_SHIFT)

#define I3C_EXTBR_EBRLP_SHIFT                   (16)      /* Bits 16-21: Ebrlp */
#define I3C_EXTBR_EBRLP_MASK                    (0x3f << I3C_EXTBR_EBRLP_SHIFT)

#define I3C_EXTBR_EBRHP_SHIFT                   (24)      /* Bits 24-29: Ebrhp */
#define I3C_EXTBR_EBRHP_MASK                    (0x3f << I3C_EXTBR_EBRHP_SHIFT)

/* I3C IBINCTL Register Bit Definitions ******************************/

#define I3C_IBINCTL_NRHJCTL                     (1 << 0)  /* Nrhjctl */

#define I3C_IBINCTL_NRMRCTL                     (1 << 1)  /* Nrmrctl */

#define I3C_IBINCTL_NRSIRCTL                    (1 << 3)  /* Nrsirctl */

/* I3C INCTL Register Bit Definitions ********************************/

#define I3C_INCTL_DNFS_SHIFT                    (0)      /* Bits 0-3: Dnfs */
#define I3C_INCTL_DNFS_MASK                     (0xf << I3C_INCTL_DNFS_SHIFT)

#define I3C_INCTL_DNFE                          (1 << 4)  /* Dnfe */

/* I3C INIE Register Bit Definitions *********************************/

#define I3C_INIE_INEIE                          (1 << 10)  /* Ineie */

/* I3C INST Register Bit Definitions *********************************/

#define I3C_INST_INEF                           (1 << 10)  /* Inef */

/* I3C INSTE Register Bit Definitions ********************************/

#define I3C_INSTE_INEE                          (1 << 10)  /* Inee */

/* I3C MRCCPT Register Bit Definitions *******************************/

#define I3C_MRCCPT_MRCCPT_SHIFT                 (0)      /* Bits 0-31: Mrccpt */
#define I3C_MRCCPT_MRCCPT_MASK                  (0xffffffff << I3C_MRCCPT_MRCCPT_SHIFT)

/* I3C MSDVAD Register Bit Definitions *******************************/

#define I3C_MSDVAD_MDYAD_SHIFT                  (16)      /* Bits 16-22: Mdyad */
#define I3C_MSDVAD_MDYAD_MASK                   (0x7f << I3C_MSDVAD_MDYAD_SHIFT)

#define I3C_MSDVAD_MDYADV                       (1 << 31)  /* Mdyadv */

/* I3C MSERRCNT Register Bit Definitions *****************************/

#define I3C_MSERRCNT_M2ECNT_SHIFT               (0)      /* Bits 0-7: M2Ecnt */
#define I3C_MSERRCNT_M2ECNT_MASK                (0xff << I3C_MSERRCNT_M2ECNT_SHIFT)

/* I3C NDBSTLV0 Register Bit Definitions *****************************/

#define I3C_NDBSTLV0_TDBFLV_SHIFT               (0)      /* Bits 0-7: Tdbflv */
#define I3C_NDBSTLV0_TDBFLV_MASK                (0xff << I3C_NDBSTLV0_TDBFLV_SHIFT)

#define I3C_NDBSTLV0_RDBLV_SHIFT                (8)      /* Bits 8-15: Rdblv */
#define I3C_NDBSTLV0_RDBLV_MASK                 (0xff << I3C_NDBSTLV0_RDBLV_SHIFT)

/* I3C NIBIQP Register Bit Definitions *******************************/

#define I3C_NIBIQP_NIBIQP_SHIFT                 (0)      /* Bits 0-31: Nibiqp */
#define I3C_NIBIQP_NIBIQP_MASK                  (0xffffffff << I3C_NIBIQP_NIBIQP_SHIFT)

/* I3C NQSTLV Register Bit Definitions *******************************/

#define I3C_NQSTLV_CMDQFLV_SHIFT                (0)      /* Bits 0-7: Cmdqflv */
#define I3C_NQSTLV_CMDQFLV_MASK                 (0xff << I3C_NQSTLV_CMDQFLV_SHIFT)

#define I3C_NQSTLV_RSPQLV_SHIFT                 (8)      /* Bits 8-15: Rspqlv */
#define I3C_NQSTLV_RSPQLV_MASK                  (0xff << I3C_NQSTLV_RSPQLV_SHIFT)

#define I3C_NQSTLV_IBIQLV_SHIFT                 (16)      /* Bits 16-23: Ibiqlv */
#define I3C_NQSTLV_IBIQLV_MASK                  (0xff << I3C_NQSTLV_IBIQLV_SHIFT)

#define I3C_NQSTLV_IBISCNT_SHIFT                (24)      /* Bits 24-28: Ibiscnt */
#define I3C_NQSTLV_IBISCNT_MASK                 (0x1f << I3C_NQSTLV_IBISCNT_SHIFT)

/* I3C NQTHCTL Register Bit Definitions ******************************/

#define I3C_NQTHCTL_CMDQTH_SHIFT                (0)      /* Bits 0-1: Cmdqth */
#define I3C_NQTHCTL_CMDQTH_MASK                 (0x3 << I3C_NQTHCTL_CMDQTH_SHIFT)

#define I3C_NQTHCTL_RSPQTH_SHIFT                (8)      /* Bits 8-9: Rspqth */
#define I3C_NQTHCTL_RSPQTH_MASK                 (0x3 << I3C_NQTHCTL_RSPQTH_SHIFT)

#define I3C_NQTHCTL_IBIDSSZ_SHIFT               (16)      /* Bits 16-23: Ibidssz */
#define I3C_NQTHCTL_IBIDSSZ_MASK                (0xff << I3C_NQTHCTL_IBIDSSZ_SHIFT)

#define I3C_NQTHCTL_IBIQTH_SHIFT                (24)      /* Bits 24-26: Ibiqth */
#define I3C_NQTHCTL_IBIQTH_MASK                 (0x7 << I3C_NQTHCTL_IBIQTH_SHIFT)

/* I3C NRQTHCTL Register Bit Definitions *****************************/

#define I3C_NRQTHCTL_RSQTH                      (1 << 0)  /* Rsqth */

/* I3C NRSPQP Register Bit Definitions *******************************/

#define I3C_NRSPQP_NRSPQP_SHIFT                 (0)      /* Bits 0-31: Nrspqp */
#define I3C_NRSPQP_NRSPQP_MASK                  (0xffffffff << I3C_NRSPQP_NRSPQP_SHIFT)

/* I3C NRSQP Register Bit Definitions ********************************/

#define I3C_NRSQP_NRSQP_SHIFT                   (0)      /* Bits 0-31: Nrsqp */
#define I3C_NRSQP_NRSQP_MASK                    (0xffffffff << I3C_NRSQP_NRSQP_SHIFT)

/* I3C NRSQSTLV Register Bit Definitions *****************************/

#define I3C_NRSQSTLV_RSQLV_SHIFT                (0)      /* Bits 0-7: Rsqlv */
#define I3C_NRSQSTLV_RSQLV_MASK                 (0xff << I3C_NRSQSTLV_RSQLV_SHIFT)

/* I3C NTBTHCTL0 Register Bit Definitions ****************************/

#define I3C_NTBTHCTL0_TXDBTH_SHIFT              (0)      /* Bits 0-2: Txdbth */
#define I3C_NTBTHCTL0_TXDBTH_MASK               (0x7 << I3C_NTBTHCTL0_TXDBTH_SHIFT)

#define I3C_NTBTHCTL0_RXDBTH_SHIFT              (8)      /* Bits 8-10: Rxdbth */
#define I3C_NTBTHCTL0_RXDBTH_MASK               (0x7 << I3C_NTBTHCTL0_RXDBTH_SHIFT)

#define I3C_NTBTHCTL0_TXSTTH_SHIFT              (16)      /* Bits 16-18: Txstth */
#define I3C_NTBTHCTL0_TXSTTH_MASK               (0x7 << I3C_NTBTHCTL0_TXSTTH_SHIFT)

#define I3C_NTBTHCTL0_RXSTTH_SHIFT              (24)      /* Bits 24-26: Rxstth */
#define I3C_NTBTHCTL0_RXSTTH_MASK               (0x7 << I3C_NTBTHCTL0_RXSTTH_SHIFT)

/* I3C NTDTBP0 Register Bit Definitions ******************************/

#define I3C_NTDTBP0_NTDTBP0_SHIFT               (0)      /* Bits 0-31: Ntdtbp0 */
#define I3C_NTDTBP0_NTDTBP0_MASK                (0xffffffff << I3C_NTDTBP0_NTDTBP0_SHIFT)

#define I3C_NTDTBP0_BY_NTDTBP0_SHIFT            (0)      /* Bits 0-7: By Ntdtbp0 */
#define I3C_NTDTBP0_BY_NTDTBP0_MASK             (0xff << I3C_NTDTBP0_BY_NTDTBP0_SHIFT)

/* I3C NTIE Register Bit Definitions *********************************/

#define I3C_NTIE_TDBEIE0                        (1 << 0)  /* Tdbeie0 */

#define I3C_NTIE_RDBFIE0                        (1 << 1)  /* Rdbfie0 */

#define I3C_NTIE_IBIQEFIE                       (1 << 2)  /* Ibiqefie */

#define I3C_NTIE_CMDQEIE                        (1 << 3)  /* Cmdqeie */

#define I3C_NTIE_RSPQFIE                        (1 << 4)  /* Rspqfie */

#define I3C_NTIE_TABTIE                         (1 << 5)  /* Tabtie */

#define I3C_NTIE_TEIE                           (1 << 9)  /* Teie */

#define I3C_NTIE_RSQFIE                         (1 << 20)  /* Rsqfie */

/* I3C NTST Register Bit Definitions *********************************/

#define I3C_NTST_TDBEF0                         (1 << 0)  /* Tdbef0 */

#define I3C_NTST_RDBFF0                         (1 << 1)  /* Rdbff0 */

#define I3C_NTST_IBIQEFF                        (1 << 2)  /* Ibiqeff */

#define I3C_NTST_CMDQEF                         (1 << 3)  /* Cmdqef */

#define I3C_NTST_RSPQFF                         (1 << 4)  /* Rspqff */

#define I3C_NTST_TABTF                          (1 << 5)  /* Tabtf */

#define I3C_NTST_TEF                            (1 << 9)  /* Tef */

#define I3C_NTST_RSQFF                          (1 << 20)  /* Rsqff */

/* I3C NTSTE Register Bit Definitions ********************************/

#define I3C_NTSTE_TDBEE0                        (1 << 0)  /* Tdbee0 */

#define I3C_NTSTE_RDBFE0                        (1 << 1)  /* Rdbfe0 */

#define I3C_NTSTE_IBIQEFE                       (1 << 2)  /* Ibiqefe */

#define I3C_NTSTE_CMDQEE                        (1 << 3)  /* Cmdqee */

#define I3C_NTSTE_RSPQFE                        (1 << 4)  /* Rspqfe */

#define I3C_NTSTE_TABTE                         (1 << 5)  /* Tabte */

#define I3C_NTSTE_TEE                           (1 << 9)  /* Tee */

#define I3C_NTSTE_RSQFE                         (1 << 20)  /* Rsqfe */

/* I3C OUTCTL Register Bit Definitions *******************************/

#define I3C_OUTCTL_SDOC                         (1 << 0)  /* Sdoc */

#define I3C_OUTCTL_SCOC                         (1 << 1)  /* Scoc */

#define I3C_OUTCTL_SOCWP                        (1 << 2)  /* Socwp */

#define I3C_OUTCTL_EXCYC                        (1 << 4)  /* Excyc */

#define I3C_OUTCTL_SDOD_SHIFT                   (8)      /* Bits 8-10: Sdod */
#define I3C_OUTCTL_SDOD_MASK                    (0x7 << I3C_OUTCTL_SDOD_SHIFT)

#define I3C_OUTCTL_SDODCS                       (1 << 15)  /* Sdodcs */

/* I3C PRSST Register Bit Definitions ********************************/

#define I3C_PRSST_CRMS                          (1 << 2)  /* Crms */

#define I3C_PRSST_TRMD                          (1 << 4)  /* Trmd */

#define I3C_PRSST_PRSSTWP                       (1 << 7)  /* Prsstwp */

/* I3C PRSTDBG Register Bit Definitions ******************************/

#define I3C_PRSTDBG_SCILV                       (1 << 0)  /* Scilv */

#define I3C_PRSTDBG_SDILV                       (1 << 1)  /* Sdilv */

#define I3C_PRSTDBG_SCOLV                       (1 << 2)  /* Scolv */

#define I3C_PRSTDBG_SDOLV                       (1 << 3)  /* Sdolv */

/* I3C PRTS Register Bit Definitions *********************************/

#define I3C_PRTS_PRTMD                          (1 << 0)  /* Prtmd */

/* I3C REFCKCTL Register Bit Definitions *****************************/

#define I3C_REFCKCTL_IREFCKS_SHIFT              (0)      /* Bits 0-2: Irefcks */
#define I3C_REFCKCTL_IREFCKS_MASK               (0x7 << I3C_REFCKCTL_IREFCKS_SHIFT)

/* I3C RSTCTL Register Bit Definitions *******************************/

#define I3C_RSTCTL_RI3C_BRST                    (1 << 0)  /* Ri3C Brst */

#define I3C_RSTCTL_CMDQRST                      (1 << 1)  /* Cmdqrst */

#define I3C_RSTCTL_RSPQRST                      (1 << 2)  /* Rspqrst */

#define I3C_RSTCTL_TDBRST                       (1 << 3)  /* Tdbrst */

#define I3C_RSTCTL_RDBRST                       (1 << 4)  /* Rdbrst */

#define I3C_RSTCTL_IBIQRST                      (1 << 5)  /* Ibiqrst */

#define I3C_RSTCTL_RSQRST                       (1 << 6)  /* Rsqrst */

#define I3C_RSTCTL_INTLRST                      (1 << 16)  /* Intlrst */

/* I3C SC1CPT Register Bit Definitions *******************************/

#define I3C_SC1CPT_SC1CPT_SHIFT                 (0)      /* Bits 0-15: Sc1Cpt */
#define I3C_SC1CPT_SC1CPT_MASK                  (0xffff << I3C_SC1CPT_SC1CPT_SHIFT)

/* I3C SC2CPT Register Bit Definitions *******************************/

#define I3C_SC2CPT_SC2CPT_SHIFT                 (0)      /* Bits 0-15: Sc2Cpt */
#define I3C_SC2CPT_SC2CPT_MASK                  (0xffff << I3C_SC2CPT_SC2CPT_SHIFT)

/* I3C SCSTLCTL Register Bit Definitions *****************************/

#define I3C_SCSTLCTL_STLCYC_SHIFT               (0)      /* Bits 0-15: Stlcyc */
#define I3C_SCSTLCTL_STLCYC_MASK                (0xffff << I3C_SCSTLCTL_STLCYC_SHIFT)

#define I3C_SCSTLCTL_AAPE                       (1 << 28)  /* Aape */

#define I3C_SCSTLCTL_PARPE                      (1 << 30)  /* Parpe */

#define I3C_SCSTLCTL_ACKPE                      (1 << 31)  /* Ackpe */

/* I3C SCSTRCTL Register Bit Definitions *****************************/

#define I3C_SCSTRCTL_ACKTWE                     (1 << 0)  /* Acktwe */

#define I3C_SCSTRCTL_RWE                        (1 << 1)  /* Rwe */

/* I3C SDCTPIDH Register Bit Definitions *****************************/

#define I3C_SDCTPIDH_SDCTPIDH_SHIFT             (0)      /* Bits 0-31: Sdctpidh */
#define I3C_SDCTPIDH_SDCTPIDH_MASK              (0xffffffff << I3C_SDCTPIDH_SDCTPIDH_SHIFT)

/* I3C SDCTPIDL Register Bit Definitions *****************************/

#define I3C_SDCTPIDL_SDCTPIDL_SHIFT             (0)      /* Bits 0-31: Sdctpidl */
#define I3C_SDCTPIDL_SDCTPIDL_MASK              (0xffffffff << I3C_SDCTPIDL_SDCTPIDL_SHIFT)

/* I3C STCTL Register Bit Definitions ********************************/

#define I3C_STCTL_STOE                          (1 << 0)  /* Stoe */

/* I3C STDBR Register Bit Definitions ********************************/

#define I3C_STDBR_SBRLO_SHIFT                   (0)      /* Bits 0-7: Sbrlo */
#define I3C_STDBR_SBRLO_MASK                    (0xff << I3C_STDBR_SBRLO_SHIFT)

#define I3C_STDBR_SBRHO_SHIFT                   (8)      /* Bits 8-15: Sbrho */
#define I3C_STDBR_SBRHO_MASK                    (0xff << I3C_STDBR_SBRHO_SHIFT)

#define I3C_STDBR_SBRLP_SHIFT                   (16)      /* Bits 16-21: Sbrlp */
#define I3C_STDBR_SBRLP_MASK                    (0x3f << I3C_STDBR_SBRLP_SHIFT)

#define I3C_STDBR_SBRHP_SHIFT                   (24)      /* Bits 24-29: Sbrhp */
#define I3C_STDBR_SBRHP_MASK                    (0x3f << I3C_STDBR_SBRHP_SHIFT)

#define I3C_STDBR_DSBRPO                        (1 << 31)  /* Dsbrpo */

/* I3C SVCTL Register Bit Definitions ********************************/

/* SVAE fields (parameterized for indices 0-2) */
#define I3C_SVCTL_SVAE(n)                                 (1u << (16 + ((unsigned)(n) * 1)))  /* Svae0 */

#define I3C_SVCTL_GCAE                          (1 << 0)  /* Gcae */

#define I3C_SVCTL_HSMCE                         (1 << 5)  /* Hsmce */

#define I3C_SVCTL_DVIDE                         (1 << 6)  /* Dvide */

#define I3C_SVCTL_HOAE                          (1 << 15)  /* Hoae */

/* I3C SVDCT Register Bit Definitions ********************************/

#define I3C_SVDCT_TDCR_SHIFT                    (0)      /* Bits 0-7: Tdcr */
#define I3C_SVDCT_TDCR_MASK                     (0xff << I3C_SVDCT_TDCR_SHIFT)

#define I3C_SVDCT_TBCR0                         (1 << 8)  /* Tbcr0 */

#define I3C_SVDCT_TBCR1                         (1 << 9)  /* Tbcr1 */

#define I3C_SVDCT_TBCR2                         (1 << 10)  /* Tbcr2 */

#define I3C_SVDCT_TBCR3                         (1 << 11)  /* Tbcr3 */

#define I3C_SVDCT_TBCR76_SHIFT                  (14)      /* Bits 14-15: Tbcr76 */
#define I3C_SVDCT_TBCR76_MASK                   (0x3 << I3C_SVDCT_TBCR76_SHIFT)

/* I3C SVST Register Bit Definitions *********************************/

/* SVAF fields (parameterized for indices 0-2) */
#define I3C_SVST_SVAF(n)                                  (1u << (16 + ((unsigned)(n) * 1)))  /* Svaf0 */

#define I3C_SVST_GCAF                           (1 << 0)  /* Gcaf */

#define I3C_SVST_HSMCF                          (1 << 5)  /* Hsmcf */

#define I3C_SVST_DVIDF                          (1 << 6)  /* Dvidf */

#define I3C_SVST_HOAF                           (1 << 15)  /* Hoaf */

/* I3C SVTDLG0 Register Bit Definitions ******************************/

#define I3C_SVTDLG0_STDLG_SHIFT                 (16)      /* Bits 16-31: Stdlg */
#define I3C_SVTDLG0_STDLG_MASK                  (0xffff << I3C_SVTDLG0_STDLG_SHIFT)

/* I3C TMOCTL Register Bit Definitions *******************************/

#define I3C_TMOCTL_TODTS_SHIFT                  (0)      /* Bits 0-1: Todts */
#define I3C_TMOCTL_TODTS_MASK                   (0x3 << I3C_TMOCTL_TODTS_SHIFT)

#define I3C_TMOCTL_TOLCTL                       (1 << 4)  /* Tolctl */

#define I3C_TMOCTL_TOHCTL                       (1 << 5)  /* Tohctl */

#define I3C_TMOCTL_TOMDS_SHIFT                  (6)      /* Bits 6-7: Tomds */
#define I3C_TMOCTL_TOMDS_MASK                   (0x3 << I3C_TMOCTL_TOMDS_SHIFT)

/* I3C WUCTL Register Bit Definitions ********************************/

#define I3C_WUCTL_WUACKS                        (1 << 0)  /* Wuacks */

#define I3C_WUCTL_WUANFS                        (1 << 4)  /* Wuanfs */

#define I3C_WUCTL_WUFSYNE                       (1 << 6)  /* Wufsyne */

#define I3C_WUCTL_WUFE                          (1 << 7)  /* Wufe */

/* I3C WUST Register Bit Definitions *********************************/

#define I3C_WUST_WUASYNF                        (1 << 0)  /* Wuasynf */

/* I3C Channel definitions */
#define RZV_I3C_CHANNEL_0          0

/* Maximum number of I3C channels */
#define RZV_I3C_MAX_CHANNELS       1

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_I3C_H */

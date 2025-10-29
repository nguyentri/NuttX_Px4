/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_i3c.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_I3C_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_I3C_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* I3C Base Address */
#ifndef R_I3C_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_I3C_BASE           0x4035f000
#else
#define R_I3C_BASE           0x5035f000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_I3C_CH_STRIDE    0x00000100
#define R_I3C_CH_BASE(ch)   (R_I3C_BASE + ((uint32_t)(ch) * R_I3C_CH_STRIDE))

/* I3C Register Offsets */

#define R_I3C_PRTS_OFFSET                         0x00000000  /* Protocol Selection Register */
#define R_I3C_CECTL_OFFSET                        0x00000010  /* Clock Enable Control Resisters */
#define R_I3C_BCTL_OFFSET                         0x00000014  /* Bus Control Register */
#define R_I3C_MSDVAD_OFFSET                       0x00000018  /* Master Device Address Register */
#define R_I3C_RSTCTL_OFFSET                       0x00000020  /* Reset Control Register */
#define R_I3C_PRSST_OFFSET                        0x00000024  /* Present State Register */
#define R_I3C_INST_OFFSET                         0x00000030  /* Internal Status Register */
#define R_I3C_INSTE_OFFSET                        0x00000034  /* Internal Status Enable Register */
#define R_I3C_INIE_OFFSET                         0x00000038  /* Internal Interrupt Enable Register */
#define R_I3C_INSTFC_OFFSET                       0x0000003c  /* Internal Status Force Register */
#define R_I3C_DVCT_OFFSET                         0x00000044  /* Device Characteristic Table Register */
#define R_I3C_IBINCTL_OFFSET                      0x00000058  /* IBI Notify Control Register */
#define R_I3C_BFCTL_OFFSET                        0x00000060  /* Bus Function Control Register */
#define R_I3C_SVCTL_OFFSET                        0x00000064  /* Slave Control Register */
#define R_I3C_REFCKCTL_OFFSET                     0x00000070  /* Reference Clock Control Register */
#define R_I3C_STDBR_OFFSET                        0x00000074  /* Standard Bit Rate Register */
#define R_I3C_EXTBR_OFFSET                        0x00000078  /* Extended Bit Rate Register */
#define R_I3C_BFRECDT_OFFSET                      0x0000007c  /* Bus Free Condition Detection Time Register */
#define R_I3C_BAVLCDT_OFFSET                      0x00000080  /* Bus Available Condition Detection Time Register */
#define R_I3C_BIDLCDT_OFFSET                      0x00000084  /* Bus Idle Condition Detection Time Register */
#define R_I3C_OUTCTL_OFFSET                       0x00000088  /* Output Control Register */
#define R_I3C_INCTL_OFFSET                        0x0000008c  /* Input Control Register */
#define R_I3C_TMOCTL_OFFSET                       0x00000090  /* Timeout Control Register */
#define R_I3C_WUCTL_OFFSET                        0x00000098  /* Wake Up Unit Control Register */
#define R_I3C_ACKCTL_OFFSET                       0x000000a0  /* Acknowledge Control Register */
#define R_I3C_SCSTRCTL_OFFSET                     0x000000a4  /* SCL Stretch Control Register */
#define R_I3C_SCSTLCTL_OFFSET                     0x000000b0  /* SCL Stalling Control Register */
#define R_I3C_SVTDLG0_OFFSET                      0x000000c0  /* Slave Transfer Data Length Register 0 */
#define R_I3C_STCTL_OFFSET                        0x00000120  /* Synchronous Timing Control Register */
#define R_I3C_ATCTL_OFFSET                        0x00000124  /* Asynchronous Timing Control Register */
#define R_I3C_ATTRG_OFFSET                        0x00000128  /* Asynchronous Timing Trigger Register */
#define R_I3C_ATCCNTE_OFFSET                      0x0000012c  /* Asynchronous Timing Contorol Counter enable Register */
#define R_I3C_CNDCTL_OFFSET                       0x00000140  /* Condition Control Register */
#define R_I3C_NCMDQP_OFFSET                       0x00000150  /* Normal Command Queue Port Register */
#define R_I3C_NRSPQP_OFFSET                       0x00000154  /* Normal Response Queue Port Register */
#define R_I3C_NTDTBP0_OFFSET                      0x00000158  /* Normal Transfer Data Buffer Port Register 0 */
#define R_I3C_NIBIQP_OFFSET                       0x0000017c  /* Normal IBI Queue Port Register */
#define R_I3C_NRSQP_OFFSET                        0x00000180  /* Normal Receive Status Queue Port Register */
#define R_I3C_HCMDQP_OFFSET                       0x00000184  /* High Priority Command Queue Port Register */
#define R_I3C_HRSPQP_OFFSET                       0x00000188  /* High Priority Response Queue Port Register */
#define R_I3C_HTDTBP_OFFSET                       0x0000018c  /* High Priority Transfer Data Buffer Port Register */
#define R_I3C_NQTHCTL_OFFSET                      0x00000190  /* Normal Queue Threshold Control Register */
#define R_I3C_NTBTHCTL0_OFFSET                    0x00000194  /* Normal Transfer Data Buffer Threshold Control Register 0 */
#define R_I3C_NRQTHCTL_OFFSET                     0x000001c0  /* Normal Receive Status Queue Threshold Control Register */
#define R_I3C_HQTHCTL_OFFSET                      0x000001c4  /* High Priority Queue Threshold Control Register */
#define R_I3C_HTBTHCTL_OFFSET                     0x000001c8  /* High Priority Transfer Data Buffer Threshold Control Register */
#define R_I3C_BST_OFFSET                          0x000001d0  /* Bus Status Register */
#define R_I3C_BSTE_OFFSET                         0x000001d4  /* Bus Status Enable Register */
#define R_I3C_BIE_OFFSET                          0x000001d8  /* Bus Interrupt Enable Register */
#define R_I3C_BSTFC_OFFSET                        0x000001dc  /* Bus Status Force Register */
#define R_I3C_NTST_OFFSET                         0x000001e0  /* Normal Transfer Status Register */
#define R_I3C_NTSTE_OFFSET                        0x000001e4  /* Normal Transfer Status Enable Register */
#define R_I3C_NTIE_OFFSET                         0x000001e8  /* Normal Transfer Interrupt Enable Register */
#define R_I3C_NTSTFC_OFFSET                       0x000001ec  /* Normal Transfer Status Force Register */
#define R_I3C_HTST_OFFSET                         0x00000200  /* High Priority Transfer Status Register */
#define R_I3C_HTSTE_OFFSET                        0x00000204  /* High Priority Transfer Status Enable Register */
#define R_I3C_HTIE_OFFSET                         0x00000208  /* High Priority Transfer Interrupt Enable Register */
#define R_I3C_HTSTFC_OFFSET                       0x0000020c  /* High Priority Transfer Status Force Register */
#define R_I3C_BCST_OFFSET                         0x00000210  /* Bus Condition Status Register */
#define R_I3C_SVST_OFFSET                         0x00000214  /* Slave Status Register */
#define R_I3C_WUST_OFFSET                         0x00000218  /* Wake Up Unit Operating Status Register */
#define R_I3C_MRCCPT_OFFSET                       0x0000021c  /* MsyncCNT Counter Capture Register */
/* DATBAS%s Registers (0-7) */
#define R_I3C_DATBAS_OFFSET(m)                    (0x00000224 + ((m) * 0x00000008))  /* Device Address Table Basic Register %s */
#define R_I3C_EXDATBAS_OFFSET                     0x000002a0  /* Extended Device Address Table Basic Register */
/* SDATBAS%s Registers (0-2) */
#define R_I3C_SDATBAS_OFFSET(m)                   (0x000002b0 + ((m) * 0x00000004))  /* Slave Device Address Table Basic Register %s */
/* MSDCT%s Registers (0-7) */
#define R_I3C_MSDCT_OFFSET(m)                     (0x000002d0 + ((m) * 0x00000004))  /* Master Device Characteristic Table Register %s */
#define R_I3C_SVDCT_OFFSET                        0x00000320  /* Slave Device Characteristic Table Register */
#define R_I3C_SDCTPIDL_OFFSET                     0x00000324  /* Slave Device Characteristic Table Provisional ID Low Register */
#define R_I3C_SDCTPIDH_OFFSET                     0x00000328  /* Slave Device Characteristic Table Provisional ID High Register */
/* SVDVAD%s Registers (0-2) */
#define R_I3C_SVDVAD_OFFSET(m)                    (0x00000330 + ((m) * 0x00000004))  /* Slave Device Address Register %s */
#define R_I3C_CSECMD_OFFSET                       0x00000350  /* CCC Slave Events Command Register */
#define R_I3C_CEACTST_OFFSET                      0x00000354  /* CCC Enter Activity State Register */
#define R_I3C_CMWLG_OFFSET                        0x00000358  /* CCC Max Write Length Register */
#define R_I3C_CMRLG_OFFSET                        0x0000035c  /* CCC Max Read Length Register */
#define R_I3C_CETSTMD_OFFSET                      0x00000360  /* CCC Enter Test Mode Register */
#define R_I3C_CGDVST_OFFSET                       0x00000364  /* CCC Get Device Status Register */
#define R_I3C_CMDSPW_OFFSET                       0x00000368  /* CCC Max Data Speed W (Write) Register */
#define R_I3C_CMDSPR_OFFSET                       0x0000036c  /* CCC Max Data Speed R (Read) Register */
#define R_I3C_CMDSPT_OFFSET                       0x00000370  /* CCC Max Data Speed T (Turnaround) Register */
#define R_I3C_CETSM_OFFSET                        0x00000374  /* CCC Exchange Timing Support Information M (Mode) Register */
#define R_I3C_CETSS_OFFSET                        0x00000378  /* CCC Exchange Timing Support Information S (State) Register */
#define R_I3C_CGHDRCAP_OFFSET                     0x0000037c  /* CCC Get HDR Capability Register */
#define R_I3C_BITCNT_OFFSET                       0x00000380  /* Bit Count Register */
#define R_I3C_NQSTLV_OFFSET                       0x00000394  /* Normal Queue Status Level Register */
#define R_I3C_NDBSTLV0_OFFSET                     0x00000398  /* Normal Data Buffer Status Level Register 0 */
#define R_I3C_NRSQSTLV_OFFSET                     0x000003c0  /* Normal Receive Status Queue Status Level Register */
#define R_I3C_HQSTLV_OFFSET                       0x000003c4  /* High Priority Queue Status Level Register */
#define R_I3C_HDBSTLV_OFFSET                      0x000003c8  /* High Priority Data Buffer Status Level Register */
#define R_I3C_PRSTDBG_OFFSET                      0x000003cc  /* Present State Debug Register */
#define R_I3C_MSERRCNT_OFFSET                     0x000003d0  /* Master Error Counters Register */
#define R_I3C_SC1CPT_OFFSET                       0x000003e0  /* SC1 Capture monitor Register */
#define R_I3C_SC2CPT_OFFSET                       0x000003e4  /* SC2 Capture monitor Register */

/* I3C Register Addresses */

#define R_I3C_PRTS(n)                             (R_I3C_CH_BASE(n) + R_I3C_PRTS_OFFSET)
#define R_I3C_CECTL(n)                            (R_I3C_CH_BASE(n) + R_I3C_CECTL_OFFSET)
#define R_I3C_BCTL(n)                             (R_I3C_CH_BASE(n) + R_I3C_BCTL_OFFSET)
#define R_I3C_MSDVAD(n)                           (R_I3C_CH_BASE(n) + R_I3C_MSDVAD_OFFSET)
#define R_I3C_RSTCTL(n)                           (R_I3C_CH_BASE(n) + R_I3C_RSTCTL_OFFSET)
#define R_I3C_PRSST(n)                            (R_I3C_CH_BASE(n) + R_I3C_PRSST_OFFSET)
#define R_I3C_INST(n)                             (R_I3C_CH_BASE(n) + R_I3C_INST_OFFSET)
#define R_I3C_INSTE(n)                            (R_I3C_CH_BASE(n) + R_I3C_INSTE_OFFSET)
#define R_I3C_INIE(n)                             (R_I3C_CH_BASE(n) + R_I3C_INIE_OFFSET)
#define R_I3C_INSTFC(n)                           (R_I3C_CH_BASE(n) + R_I3C_INSTFC_OFFSET)
#define R_I3C_DVCT(n)                             (R_I3C_CH_BASE(n) + R_I3C_DVCT_OFFSET)
#define R_I3C_IBINCTL(n)                          (R_I3C_CH_BASE(n) + R_I3C_IBINCTL_OFFSET)
#define R_I3C_BFCTL(n)                            (R_I3C_CH_BASE(n) + R_I3C_BFCTL_OFFSET)
#define R_I3C_SVCTL(n)                            (R_I3C_CH_BASE(n) + R_I3C_SVCTL_OFFSET)
#define R_I3C_REFCKCTL(n)                         (R_I3C_CH_BASE(n) + R_I3C_REFCKCTL_OFFSET)
#define R_I3C_STDBR(n)                            (R_I3C_CH_BASE(n) + R_I3C_STDBR_OFFSET)
#define R_I3C_EXTBR(n)                            (R_I3C_CH_BASE(n) + R_I3C_EXTBR_OFFSET)
#define R_I3C_BFRECDT(n)                          (R_I3C_CH_BASE(n) + R_I3C_BFRECDT_OFFSET)
#define R_I3C_BAVLCDT(n)                          (R_I3C_CH_BASE(n) + R_I3C_BAVLCDT_OFFSET)
#define R_I3C_BIDLCDT(n)                          (R_I3C_CH_BASE(n) + R_I3C_BIDLCDT_OFFSET)
#define R_I3C_OUTCTL(n)                           (R_I3C_CH_BASE(n) + R_I3C_OUTCTL_OFFSET)
#define R_I3C_INCTL(n)                            (R_I3C_CH_BASE(n) + R_I3C_INCTL_OFFSET)
#define R_I3C_TMOCTL(n)                           (R_I3C_CH_BASE(n) + R_I3C_TMOCTL_OFFSET)
#define R_I3C_WUCTL(n)                            (R_I3C_CH_BASE(n) + R_I3C_WUCTL_OFFSET)
#define R_I3C_ACKCTL(n)                           (R_I3C_CH_BASE(n) + R_I3C_ACKCTL_OFFSET)
#define R_I3C_SCSTRCTL(n)                         (R_I3C_CH_BASE(n) + R_I3C_SCSTRCTL_OFFSET)
#define R_I3C_SCSTLCTL(n)                         (R_I3C_CH_BASE(n) + R_I3C_SCSTLCTL_OFFSET)
#define R_I3C_SVTDLG0(n)                          (R_I3C_CH_BASE(n) + R_I3C_SVTDLG0_OFFSET)
#define R_I3C_STCTL(n)                            (R_I3C_CH_BASE(n) + R_I3C_STCTL_OFFSET)
#define R_I3C_ATCTL(n)                            (R_I3C_CH_BASE(n) + R_I3C_ATCTL_OFFSET)
#define R_I3C_ATTRG(n)                            (R_I3C_CH_BASE(n) + R_I3C_ATTRG_OFFSET)
#define R_I3C_ATCCNTE(n)                          (R_I3C_CH_BASE(n) + R_I3C_ATCCNTE_OFFSET)
#define R_I3C_CNDCTL(n)                           (R_I3C_CH_BASE(n) + R_I3C_CNDCTL_OFFSET)
#define R_I3C_NCMDQP(n)                           (R_I3C_CH_BASE(n) + R_I3C_NCMDQP_OFFSET)
#define R_I3C_NRSPQP(n)                           (R_I3C_CH_BASE(n) + R_I3C_NRSPQP_OFFSET)
#define R_I3C_NTDTBP0(n)                          (R_I3C_CH_BASE(n) + R_I3C_NTDTBP0_OFFSET)
#define R_I3C_NIBIQP(n)                           (R_I3C_CH_BASE(n) + R_I3C_NIBIQP_OFFSET)
#define R_I3C_NRSQP(n)                            (R_I3C_CH_BASE(n) + R_I3C_NRSQP_OFFSET)
#define R_I3C_HCMDQP(n)                           (R_I3C_CH_BASE(n) + R_I3C_HCMDQP_OFFSET)
#define R_I3C_HRSPQP(n)                           (R_I3C_CH_BASE(n) + R_I3C_HRSPQP_OFFSET)
#define R_I3C_HTDTBP(n)                           (R_I3C_CH_BASE(n) + R_I3C_HTDTBP_OFFSET)
#define R_I3C_NQTHCTL(n)                          (R_I3C_CH_BASE(n) + R_I3C_NQTHCTL_OFFSET)
#define R_I3C_NTBTHCTL0(n)                        (R_I3C_CH_BASE(n) + R_I3C_NTBTHCTL0_OFFSET)
#define R_I3C_NRQTHCTL(n)                         (R_I3C_CH_BASE(n) + R_I3C_NRQTHCTL_OFFSET)
#define R_I3C_HQTHCTL(n)                          (R_I3C_CH_BASE(n) + R_I3C_HQTHCTL_OFFSET)
#define R_I3C_HTBTHCTL(n)                         (R_I3C_CH_BASE(n) + R_I3C_HTBTHCTL_OFFSET)
#define R_I3C_BST(n)                              (R_I3C_CH_BASE(n) + R_I3C_BST_OFFSET)
#define R_I3C_BSTE(n)                             (R_I3C_CH_BASE(n) + R_I3C_BSTE_OFFSET)
#define R_I3C_BIE(n)                              (R_I3C_CH_BASE(n) + R_I3C_BIE_OFFSET)
#define R_I3C_BSTFC(n)                            (R_I3C_CH_BASE(n) + R_I3C_BSTFC_OFFSET)
#define R_I3C_NTST(n)                             (R_I3C_CH_BASE(n) + R_I3C_NTST_OFFSET)
#define R_I3C_NTSTE(n)                            (R_I3C_CH_BASE(n) + R_I3C_NTSTE_OFFSET)
#define R_I3C_NTIE(n)                             (R_I3C_CH_BASE(n) + R_I3C_NTIE_OFFSET)
#define R_I3C_NTSTFC(n)                           (R_I3C_CH_BASE(n) + R_I3C_NTSTFC_OFFSET)
#define R_I3C_HTST(n)                             (R_I3C_CH_BASE(n) + R_I3C_HTST_OFFSET)
#define R_I3C_HTSTE(n)                            (R_I3C_CH_BASE(n) + R_I3C_HTSTE_OFFSET)
#define R_I3C_HTIE(n)                             (R_I3C_CH_BASE(n) + R_I3C_HTIE_OFFSET)
#define R_I3C_HTSTFC(n)                           (R_I3C_CH_BASE(n) + R_I3C_HTSTFC_OFFSET)
#define R_I3C_BCST(n)                             (R_I3C_CH_BASE(n) + R_I3C_BCST_OFFSET)
#define R_I3C_SVST(n)                             (R_I3C_CH_BASE(n) + R_I3C_SVST_OFFSET)
#define R_I3C_WUST(n)                             (R_I3C_CH_BASE(n) + R_I3C_WUST_OFFSET)
#define R_I3C_MRCCPT(n)                           (R_I3C_CH_BASE(n) + R_I3C_MRCCPT_OFFSET)
#define R_I3C_DATBAS(n, m)                        (R_I3C_CH_BASE(n) + R_I3C_DATBAS_OFFSET(m))
#define R_I3C_EXDATBAS(n)                         (R_I3C_CH_BASE(n) + R_I3C_EXDATBAS_OFFSET)
#define R_I3C_SDATBAS(n, m)                       (R_I3C_CH_BASE(n) + R_I3C_SDATBAS_OFFSET(m))
#define R_I3C_MSDCT(n, m)                         (R_I3C_CH_BASE(n) + R_I3C_MSDCT_OFFSET(m))
#define R_I3C_SVDCT(n)                            (R_I3C_CH_BASE(n) + R_I3C_SVDCT_OFFSET)
#define R_I3C_SDCTPIDL(n)                         (R_I3C_CH_BASE(n) + R_I3C_SDCTPIDL_OFFSET)
#define R_I3C_SDCTPIDH(n)                         (R_I3C_CH_BASE(n) + R_I3C_SDCTPIDH_OFFSET)
#define R_I3C_SVDVAD(n, m)                        (R_I3C_CH_BASE(n) + R_I3C_SVDVAD_OFFSET(m))
#define R_I3C_CSECMD(n)                           (R_I3C_CH_BASE(n) + R_I3C_CSECMD_OFFSET)
#define R_I3C_CEACTST(n)                          (R_I3C_CH_BASE(n) + R_I3C_CEACTST_OFFSET)
#define R_I3C_CMWLG(n)                            (R_I3C_CH_BASE(n) + R_I3C_CMWLG_OFFSET)
#define R_I3C_CMRLG(n)                            (R_I3C_CH_BASE(n) + R_I3C_CMRLG_OFFSET)
#define R_I3C_CETSTMD(n)                          (R_I3C_CH_BASE(n) + R_I3C_CETSTMD_OFFSET)
#define R_I3C_CGDVST(n)                           (R_I3C_CH_BASE(n) + R_I3C_CGDVST_OFFSET)
#define R_I3C_CMDSPW(n)                           (R_I3C_CH_BASE(n) + R_I3C_CMDSPW_OFFSET)
#define R_I3C_CMDSPR(n)                           (R_I3C_CH_BASE(n) + R_I3C_CMDSPR_OFFSET)
#define R_I3C_CMDSPT(n)                           (R_I3C_CH_BASE(n) + R_I3C_CMDSPT_OFFSET)
#define R_I3C_CETSM(n)                            (R_I3C_CH_BASE(n) + R_I3C_CETSM_OFFSET)
#define R_I3C_CETSS(n)                            (R_I3C_CH_BASE(n) + R_I3C_CETSS_OFFSET)
#define R_I3C_CGHDRCAP(n)                         (R_I3C_CH_BASE(n) + R_I3C_CGHDRCAP_OFFSET)
#define R_I3C_BITCNT(n)                           (R_I3C_CH_BASE(n) + R_I3C_BITCNT_OFFSET)
#define R_I3C_NQSTLV(n)                           (R_I3C_CH_BASE(n) + R_I3C_NQSTLV_OFFSET)
#define R_I3C_NDBSTLV0(n)                         (R_I3C_CH_BASE(n) + R_I3C_NDBSTLV0_OFFSET)
#define R_I3C_NRSQSTLV(n)                         (R_I3C_CH_BASE(n) + R_I3C_NRSQSTLV_OFFSET)
#define R_I3C_HQSTLV(n)                           (R_I3C_CH_BASE(n) + R_I3C_HQSTLV_OFFSET)
#define R_I3C_HDBSTLV(n)                          (R_I3C_CH_BASE(n) + R_I3C_HDBSTLV_OFFSET)
#define R_I3C_PRSTDBG(n)                          (R_I3C_CH_BASE(n) + R_I3C_PRSTDBG_OFFSET)
#define R_I3C_MSERRCNT(n)                         (R_I3C_CH_BASE(n) + R_I3C_MSERRCNT_OFFSET)
#define R_I3C_SC1CPT(n)                           (R_I3C_CH_BASE(n) + R_I3C_SC1CPT_OFFSET)
#define R_I3C_SC2CPT(n)                           (R_I3C_CH_BASE(n) + R_I3C_SC2CPT_OFFSET)

/* Register bit definitions */
/* PRTS Register bit definitions */
#define R_I3C_PRTS_PRTMD                          (1 << 0)  /* Protocol Mode */

/* CECTL Register bit definitions */
#define R_I3C_CECTL_CLKE                          (1 << 0)  /* Clock Enable */

/* BCTL Register bit definitions */
#define R_I3C_BCTL_INCBA                          (1 << 0)  /* Include I3C Broadcast Address */

#define R_I3C_BCTL_BMDS                           (1 << 7)  /* Bus Mode Selection */

#define R_I3C_BCTL_HJACKCTL                       (1 << 8)  /* Hot-Join Acknowledge Control */

#define R_I3C_BCTL_ABT                            (1 << 29)  /* Abort */

#define R_I3C_BCTL_RSM                            (1 << 30)  /* Resume */

#define R_I3C_BCTL_BUSE                           (1 << 31)  /* Bus Enable */

/* MSDVAD Register bit definitions */
#define R_I3C_MSDVAD_MDYAD_SHIFT                  (16)  /* Master Dynamic Address */
#define R_I3C_MSDVAD_MDYAD_MASK                   0x7f0000

#define R_I3C_MSDVAD_MDYADV                       (1 << 31)  /* Master Dynamic Address Valid */

/* RSTCTL Register bit definitions */
#define R_I3C_RSTCTL_RI3CRST                      (1 << 0)  /* I3C Software Reset */

#define R_I3C_RSTCTL_CMDQRST                      (1 << 1)  /* Command Queue Software Reset */

#define R_I3C_RSTCTL_RSPQRST                      (1 << 2)  /* Response Queue Software Reset */

#define R_I3C_RSTCTL_TDBRST                       (1 << 3)  /* Transmit Data Buffer Software Reset */

#define R_I3C_RSTCTL_RDBRST                       (1 << 4)  /* Receive Data Buffer Software Reset */

#define R_I3C_RSTCTL_IBIQRST                      (1 << 5)  /* IBI Queue Software Reset */

#define R_I3C_RSTCTL_RSQRST                       (1 << 6)  /* Receive Status Queue Software Reset */

#define R_I3C_RSTCTL_HCMDQRST                     (1 << 9)  /* High Priority Command Queue Software Reset */

#define R_I3C_RSTCTL_HRSPQRST                     (1 << 10)  /* High Priority Response Queue Software Rese */

#define R_I3C_RSTCTL_HTDBRST                      (1 << 11)  /* High Priority Tx Data Buffer Software Reset */

#define R_I3C_RSTCTL_HRDBRST                      (1 << 12)  /* High Priority Rx Data Buffer Software Reset */

#define R_I3C_RSTCTL_INTLRST                      (1 << 16)  /* Internal Software Reset */

/* PRSST Register bit definitions */
#define R_I3C_PRSST_CRMS                          (1 << 2)  /* Current Master */

#define R_I3C_PRSST_TRMD                          (1 << 4)  /* Transmit/Receive Mode */

#define R_I3C_PRSST_PRSSTWP                       (1 << 7)  /* Present State Write Protect */

/* INST Register bit definitions */
#define R_I3C_INST_INEF                           (1 << 10)  /* Internal Error Flag */

/* INSTE Register bit definitions */
#define R_I3C_INSTE_INEE                          (1 << 10)  /* Internal Error Enable */

/* INIE Register bit definitions */
#define R_I3C_INIE_INEIE                          (1 << 10)  /* Internal Error Interrupt Enable */

/* INSTFC Register bit definitions */
#define R_I3C_INSTFC_INEFC                        (1 << 10)  /* Internal Error Force */

/* DVCT Register bit definitions */
#define R_I3C_DVCT_IDX_SHIFT                      (19)  /* DCT Table Index */
#define R_I3C_DVCT_IDX_MASK                       0xf80000

/* IBINCTL Register bit definitions */
#define R_I3C_IBINCTL_NRHJCTL                     (1 << 0)  /* Notify Rejected Hot-Join Control */

#define R_I3C_IBINCTL_NRMRCTL                     (1 << 1)  /* Notify Rejected Master Request Control */

#define R_I3C_IBINCTL_NRSIRCTL                    (1 << 3)  /* Notify Rejected Slave Interrupt Request Control */

/* BFCTL Register bit definitions */
#define R_I3C_BFCTL_MALE                          (1 << 0)  /* Master Arbitration-Lost Detection Enable */

#define R_I3C_BFCTL_NALE                          (1 << 1)  /* NACK Transmission Arbitration-Lost Detection Enable */

#define R_I3C_BFCTL_SALE                          (1 << 2)  /* Slave Arbitration-Lost Detection Enable */

#define R_I3C_BFCTL_SCSYNE                        (1 << 8)  /* SCL Synchronous Circuit Enable */

#define R_I3C_BFCTL_SMBS                          (1 << 12)  /* SMBus/I2C Bus Selection */

#define R_I3C_BFCTL_FMPE                          (1 << 14)  /* Fast-mode Plus Enable */

#define R_I3C_BFCTL_HSME                          (1 << 15)  /* High Speed Mode Enable */

/* SVCTL Register bit definitions */
#define R_I3C_SVCTL_GCAE                          (1 << 0)  /* General Call Address Enable */

#define R_I3C_SVCTL_HSMCE                         (1 << 5)  /* Hs-mode Master Code Enable */

#define R_I3C_SVCTL_DVIDE                         (1 << 6)  /* Device-ID Address Enable */

#define R_I3C_SVCTL_HOAE                          (1 << 15)  /* Host Address Enable */

#define R_I3C_SVCTL_SVAEN_SHIFT                   (16)  /* Slave Address Enable */
#define R_I3C_SVCTL_SVAEN_MASK                    0x70000
#  define R_I3C_SVCTL_SVAEN_0                             (0 << R_I3C_SVCTL_SVAEN_SHIFT)  /* Slave n disables */
#  define R_I3C_SVCTL_SVAEN_1                             (1 << R_I3C_SVCTL_SVAEN_SHIFT)  /* Slave n enables */

#define R_I3C_SVCTL_SVAEN_SHIFT                   (16)  /* Slave Address Enable */
#define R_I3C_SVCTL_SVAEN_MASK                    0x70000

/* REFCKCTL Register bit definitions */
#define R_I3C_REFCKCTL_IREFCKS_SHIFT              (0)  /* Internal Reference Clock Selection */
#define R_I3C_REFCKCTL_IREFCKS_MASK               0x7
#  define R_I3C_REFCKCTL_IREFCKS_000                      (0 << R_I3C_REFCKCTL_IREFCKS_SHIFT)  /* PCLKD/1 clock */
#  define R_I3C_REFCKCTL_IREFCKS_001                      (1 << R_I3C_REFCKCTL_IREFCKS_SHIFT)  /* PCLKD/2 clock */
#  define R_I3C_REFCKCTL_IREFCKS_010                      (2 << R_I3C_REFCKCTL_IREFCKS_SHIFT)  /* PCLKD/4 clock */
#  define R_I3C_REFCKCTL_IREFCKS_011                      (3 << R_I3C_REFCKCTL_IREFCKS_SHIFT)  /* PCLKD/8 clock */
#  define R_I3C_REFCKCTL_IREFCKS_100                      (4 << R_I3C_REFCKCTL_IREFCKS_SHIFT)  /* PCLKD/16 clock */
#  define R_I3C_REFCKCTL_IREFCKS_101                      (5 << R_I3C_REFCKCTL_IREFCKS_SHIFT)  /* PCLKD/32 clock */
#  define R_I3C_REFCKCTL_IREFCKS_110                      (6 << R_I3C_REFCKCTL_IREFCKS_SHIFT)  /* PCLKD/64 clock */
#  define R_I3C_REFCKCTL_IREFCKS_111                      (7 << R_I3C_REFCKCTL_IREFCKS_SHIFT)  /* PCLKD/128 clock */

/* STDBR Register bit definitions */
#define R_I3C_STDBR_SBRLO_SHIFT                   (0)  /* Count value of the Low-level period of SCL clock */
#define R_I3C_STDBR_SBRLO_MASK                    0xff

#define R_I3C_STDBR_SBRHO_SHIFT                   (8)  /* Count value of the High-level period of SCL clock */
#define R_I3C_STDBR_SBRHO_MASK                    0xff00

#define R_I3C_STDBR_SBRLP_SHIFT                   (16)  /* Standard Bit Rate Low-level Period Push-Pull */
#define R_I3C_STDBR_SBRLP_MASK                    0x3f0000

#define R_I3C_STDBR_SBRHP_SHIFT                   (24)  /* Standard Bit Rate High-Level Period Push-Pull */
#define R_I3C_STDBR_SBRHP_MASK                    0x3f000000

#define R_I3C_STDBR_DSBRPO                        (1 << 31)  /* Double the Standard Bit Rate Period for Open-Drain */

/* EXTBR Register bit definitions */
#define R_I3C_EXTBR_EBRLO_SHIFT                   (0)  /* Extended Bit Rate Low-Level Period Open-Drain */
#define R_I3C_EXTBR_EBRLO_MASK                    0xff

#define R_I3C_EXTBR_EBRHO_SHIFT                   (8)  /* Extended Bit Rate High-Level Period Open-Drain */
#define R_I3C_EXTBR_EBRHO_MASK                    0xff00

#define R_I3C_EXTBR_EBRLP_SHIFT                   (16)  /* Extended Bit Rate Low-Level Period Push-Pull */
#define R_I3C_EXTBR_EBRLP_MASK                    0x3f0000

#define R_I3C_EXTBR_EBRHP_SHIFT                   (24)  /* Extended Bit Rate High-Level Period Push-Pull */
#define R_I3C_EXTBR_EBRHP_MASK                    0x3f000000

/* BFRECDT Register bit definitions */
#define R_I3C_BFRECDT_FRECYC_SHIFT                (0)  /* Bus Free Condition Detection Cycle */
#define R_I3C_BFRECDT_FRECYC_MASK                 0x1ff

/* BAVLCDT Register bit definitions */
#define R_I3C_BAVLCDT_AVLCYC_SHIFT                (0)  /* Bus Available Condition Detection Cycle */
#define R_I3C_BAVLCDT_AVLCYC_MASK                 0x1ff

/* BIDLCDT Register bit definitions */
#define R_I3C_BIDLCDT_IDLCYC_SHIFT                (0)  /* Bus Idle Condition Detection Cycle */
#define R_I3C_BIDLCDT_IDLCYC_MASK                 0x3ffff

/* OUTCTL Register bit definitions */
#define R_I3C_OUTCTL_SDOC                         (1 << 0)  /* SDA Output Control */

#define R_I3C_OUTCTL_SCOC                         (1 << 1)  /* SCL Output Control */

#define R_I3C_OUTCTL_SOCWP                        (1 << 2)  /* SCL/SDA Output Control Write Protect */

#define R_I3C_OUTCTL_EXCYC                        (1 << 4)  /* Extra SCL Clock Cycle Output */

#define R_I3C_OUTCTL_SDOD_SHIFT                   (8)  /* SDA Output Delay */
#define R_I3C_OUTCTL_SDOD_MASK                    0x700
#  define R_I3C_OUTCTL_SDOD_000                           (0 << R_I3C_OUTCTL_SDOD_SHIFT)  /* No output delay */
#  define R_I3C_OUTCTL_SDOD_001                           (1 << R_I3C_OUTCTL_SDOD_SHIFT)  /* 1 I3Cphi cycle (When OUTCTL.SDODCS = 0 (I3Cphi))
1 or 2 I3Cphi cycles (When OUTCTL.SDODCS = 1 (I3Cphi/2))
 */
#  define R_I3C_OUTCTL_SDOD_010                           (2 << R_I3C_OUTCTL_SDOD_SHIFT)  /* 2 I3Cphi cycles (When OUTCTL.SDODCS = 0 (I3Cphi))
3 or 4 I3Cphi cycles (When OUTCTL.SDODCS = 1 (I3Cphi/2))
 */
#  define R_I3C_OUTCTL_SDOD_011                           (3 << R_I3C_OUTCTL_SDOD_SHIFT)  /* 3 I3Cphi cycles (When OUTCTL.SDODCS = 0 (I3Cphi))
5 or 6 I3Cphi cycles (When OUTCTL.SDODCS = 1 (I3Cphi/2))
 */
#  define R_I3C_OUTCTL_SDOD_100                           (4 << R_I3C_OUTCTL_SDOD_SHIFT)  /* 4 I3Cphi cycles (When OUTCTL.SDODCS = 0 (I3Cphi))
7 or 8 I3Cphi cycles (When OUTCTL.SDODCS = 1 (I3Cphi/2))
 */
#  define R_I3C_OUTCTL_SDOD_101                           (5 << R_I3C_OUTCTL_SDOD_SHIFT)  /* 5 I3Cphi cycles (When OUTCTL.SDODCS = 0 (I3Cphi))
9 or 10 I3Cphi cycles (When OUTCTL.SDODCS = 1 (I3Cphi/2))
 */
#  define R_I3C_OUTCTL_SDOD_110                           (6 << R_I3C_OUTCTL_SDOD_SHIFT)  /* 6 I3Cphi cycles (When OUTCTL.SDODCS = 0 (I3Cphi))
11 or 12 I3Cphi cycles (When OUTCTL.SDODCS = 1 (I3Cphi/2))
 */
#  define R_I3C_OUTCTL_SDOD_111                           (7 << R_I3C_OUTCTL_SDOD_SHIFT)  /* 7 I3Cphi cycles (When OUTCTL.SDODCS = 0 (I3Cphi))
13 or 14 I3Cphi cycles (When OUTCTL.SDODCS = 1 (I3Cphi/2))
 */

#define R_I3C_OUTCTL_SDODCS                       (1 << 15)  /* SDA Output Delay Clock Source Selection */

/* INCTL Register bit definitions */
#define R_I3C_INCTL_DNFS_SHIFT                    (0)  /* Digital Noise Filter Stage Selection */
#define R_I3C_INCTL_DNFS_MASK                     0xf

#define R_I3C_INCTL_DNFE                          (1 << 4)  /* Digital Noise Filter Circuit Enable */

/* TMOCTL Register bit definitions */
#define R_I3C_TMOCTL_TODTS_SHIFT                  (0)  /* Timeout Detection Time Selection */
#define R_I3C_TMOCTL_TODTS_MASK                   0x3
#  define R_I3C_TMOCTL_TODTS_00                           (0 << R_I3C_TMOCTL_TODTS_SHIFT)  /* 16bit-timeout */
#  define R_I3C_TMOCTL_TODTS_01                           (1 << R_I3C_TMOCTL_TODTS_SHIFT)  /* 14bit-timeout */
#  define R_I3C_TMOCTL_TODTS_10                           (2 << R_I3C_TMOCTL_TODTS_SHIFT)  /* 8bit-timeout */
#  define R_I3C_TMOCTL_TODTS_11                           (3 << R_I3C_TMOCTL_TODTS_SHIFT)  /* 6bit-timeout */

#define R_I3C_TMOCTL_TOLCTL                       (1 << 4)  /* Timeout L Count Control */

#define R_I3C_TMOCTL_TOHCTL                       (1 << 5)  /* Timeout H Count Control */

#define R_I3C_TMOCTL_TOMDS_SHIFT                  (6)  /* Timeout Operation Mode Selection */
#define R_I3C_TMOCTL_TOMDS_MASK                   0xc0
#  define R_I3C_TMOCTL_TOMDS_00                           (0 << R_I3C_TMOCTL_TOMDS_SHIFT)  /* Timeout is detected during the following conditions:
The bus is busy (BCST.BFREF = 0) in master mode.I3C's own slave address is detected and the bus is busy in slave
 mode.The bus is free (BCST.BFREF = 1) while generation of a START condition is
 requested (CNDCTL.STCND = 1). */
#  define R_I3C_TMOCTL_TOMDS_01                           (1 << R_I3C_TMOCTL_TOMDS_SHIFT)  /* Timeout is detected while the bus is busy. */
#  define R_I3C_TMOCTL_TOMDS_10                           (2 << R_I3C_TMOCTL_TOMDS_SHIFT)  /* Timeout is detected while the bus is free. */
#  define R_I3C_TMOCTL_TOMDS_11                           (3 << R_I3C_TMOCTL_TOMDS_SHIFT)  /* Setting prohibited */

/* WUCTL Register bit definitions */
#define R_I3C_WUCTL_WUACKS                        (1 << 0)  /* Wake-Up Acknowledge Selection */

#define R_I3C_WUCTL_WUANFS                        (1 << 4)  /* Wake-Up Analog Noise Filter Selection */

#define R_I3C_WUCTL_WUFSYNE                       (1 << 6)  /* Wake-Up function PCLKA Synchronous Enable */

#define R_I3C_WUCTL_WUFE                          (1 << 7)  /* Wake-Up function Enable. */

/* ACKCTL Register bit definitions */
#define R_I3C_ACKCTL_ACKR                         (1 << 0)  /* Acknowledge Reception */

#define R_I3C_ACKCTL_ACKT                         (1 << 1)  /* Acknowledge Transmission */

#define R_I3C_ACKCTL_ACKTWP                       (1 << 2)  /* ACKT Write Protect */

/* SCSTRCTL Register bit definitions */
#define R_I3C_SCSTRCTL_ACKTWE                     (1 << 0)  /* Acknowledge Transmission Wait Enable */

#define R_I3C_SCSTRCTL_RWE                        (1 << 1)  /* Receive Wait Enable */

/* SCSTLCTL Register bit definitions */
#define R_I3C_SCSTLCTL_STLCYC_SHIFT               (0)  /* Stalling Cycle */
#define R_I3C_SCSTLCTL_STLCYC_MASK                0xffff

#define R_I3C_SCSTLCTL_AAPE                       (1 << 28)  /* Assigend Address Phase Enable */

#define R_I3C_SCSTLCTL_TRAPE                      (1 << 29)  /* Transition Phase Enable */

#define R_I3C_SCSTLCTL_PARPE                      (1 << 30)  /* Parity Phase Enable */

#define R_I3C_SCSTLCTL_ACKPE                      (1 << 31)  /* ACK phase Enable */

/* SVTDLG0 Register bit definitions */
#define R_I3C_SVTDLG0_STDLG_SHIFT                 (16)  /* Slave Transfer Data Length */
#define R_I3C_SVTDLG0_STDLG_MASK                  0xffff0000

/* STCTL Register bit definitions */
#define R_I3C_STCTL_STOE                          (1 << 0)  /* Synchronous Timing output Enable */

/* ATCTL Register bit definitions */
#define R_I3C_ATCTL_ATTRGS                        (1 << 0)  /* Asynchronous Timing Trigger Select */

#define R_I3C_ATCTL_MREFOE                        (1 << 1)  /* MREF Output Enable (Capture Event / Counter Overflow) */

#define R_I3C_ATCTL_AMEOE                         (1 << 2)  /* Additional Master-initiated bus Event Output Enable */

#define R_I3C_ATCTL_CDIV_SHIFT                    (8)  /* TCLK Counter Divide Setting */
#define R_I3C_ATCTL_CDIV_MASK                     0xff00

/* ATTRG Register bit definitions */
#define R_I3C_ATTRG_ATSTRG                        (1 << 0)  /* Asynchronous Timing Software Trigger */

/* ATCCNTE Register bit definitions */
#define R_I3C_ATCCNTE_ATCE                        (1 << 0)  /* Asynchronous Timing Counter Enable for MREF, MC2, SC1, SC2. */

/* CNDCTL Register bit definitions */
#define R_I3C_CNDCTL_STCND                        (1 << 0)  /* START (S) Condition Issuance */

#define R_I3C_CNDCTL_SRCND                        (1 << 1)  /* Repeated START (Sr) Condition Issuance */

#define R_I3C_CNDCTL_SPCND                        (1 << 2)  /* STOP (P) Condition Issuance */

/* HCMDQP Register bit definitions */
#define R_I3C_HCMDQP_HCMDQP_SHIFT                 (0)  /* High Priority Command Queue Port */
#define R_I3C_HCMDQP_HCMDQP_MASK                  0xffffffff

/* HRSPQP Register bit definitions */
#define R_I3C_HRSPQP_HRSPQP_SHIFT                 (0)  /* High Priority Response Queue Port */
#define R_I3C_HRSPQP_HRSPQP_MASK                  0xffffffff

/* HTDTBP Register bit definitions */
#define R_I3C_HTDTBP_HTDTBP_SHIFT                 (0)  /* High Priority Transfer Data Buffer Port */
#define R_I3C_HTDTBP_HTDTBP_MASK                  0xffffffff

/* NQTHCTL Register bit definitions */
#define R_I3C_NQTHCTL_CMDQTH_SHIFT                (0)  /* Normal Command Ready Queue Threshold */
#define R_I3C_NQTHCTL_CMDQTH_MASK                 0xff
#  define R_I3C_NQTHCTL_CMDQTH_0                          (0 << R_I3C_NQTHCTL_CMDQTH_SHIFT)  /* Interrupt is issued when Command Queue is completely empty. */

#define R_I3C_NQTHCTL_RSPQTH_SHIFT                (8)  /* Normal Response Queue Threshold */
#define R_I3C_NQTHCTL_RSPQTH_MASK                 0xff00
#  define R_I3C_NQTHCTL_RSPQTH_0                          (0 << R_I3C_NQTHCTL_RSPQTH_SHIFT)  /* Interrupt is issued when Response Queue contains 1 entry
 (DWORD). */

#define R_I3C_NQTHCTL_IBIDSSZ_SHIFT               (16)  /* Normal IBI Data Segment Size */
#define R_I3C_NQTHCTL_IBIDSSZ_MASK                0xff0000

#define R_I3C_NQTHCTL_IBIQTH_SHIFT                (24)  /* Normal IBI Queue Threshold */
#define R_I3C_NQTHCTL_IBIQTH_MASK                 0xff000000
#  define R_I3C_NQTHCTL_IBIQTH_0                          (0 << R_I3C_NQTHCTL_IBIQTH_SHIFT)  /* I3C Protocol mode (Master):
Interrupt is generated when the Outstanding IBI Status count is >= 1.
I3C Protocol mode (Slave):
Interrupt is issued when IBI Data Buffer is completely empty.
 */

/* NTBTHCTL0 Register bit definitions */
#define R_I3C_NTBTHCTL0_TXDBTH_SHIFT              (0)  /* Normal Transmit Data Buffer Threshold */
#define R_I3C_NTBTHCTL0_TXDBTH_MASK               0x7
#  define R_I3C_NTBTHCTL0_TXDBTH_0X0                      (0 << R_I3C_NTBTHCTL0_TXDBTH_SHIFT)  /* Interrupt triggers at 2 Tx Buffer empties, DWORDs */
#  define R_I3C_NTBTHCTL0_TXDBTH_0X1                      (1 << R_I3C_NTBTHCTL0_TXDBTH_SHIFT)  /* Interrupt triggers at 4 Tx Buffer empties, DWORDs */
#  define R_I3C_NTBTHCTL0_TXDBTH_0X2                      (2 << R_I3C_NTBTHCTL0_TXDBTH_SHIFT)  /* Interrupt triggers at 8 Tx Buffer empties, DWORDs */
#  define R_I3C_NTBTHCTL0_TXDBTH_0X3                      (3 << R_I3C_NTBTHCTL0_TXDBTH_SHIFT)  /* Interrupt triggers at 16 Tx Buffer empties, DWORDs */
#  define R_I3C_NTBTHCTL0_TXDBTH_0X4                      (4 << R_I3C_NTBTHCTL0_TXDBTH_SHIFT)  /* Interrupt triggers at 32 Tx Buffer empties, DWORDs */
#  define R_I3C_NTBTHCTL0_TXDBTH_0X5                      (5 << R_I3C_NTBTHCTL0_TXDBTH_SHIFT)  /* Interrupt triggers at 64 Tx Buffer empties, DWORDs */
#  define R_I3C_NTBTHCTL0_TXDBTH_0X6                      (6 << R_I3C_NTBTHCTL0_TXDBTH_SHIFT)  /* Interrupt triggers at 128 Tx Buffer empties, DWORDs */
#  define R_I3C_NTBTHCTL0_TXDBTH_0X7                      (7 << R_I3C_NTBTHCTL0_TXDBTH_SHIFT)  /* Interrupt triggers at 256 Tx Buffer empties, DWORDs */

#define R_I3C_NTBTHCTL0_RXDBTH_SHIFT              (8)  /* Normal Receive Data Buffer Threshold */
#define R_I3C_NTBTHCTL0_RXDBTH_MASK               0x700
#  define R_I3C_NTBTHCTL0_RXDBTH_0X0                      (0 << R_I3C_NTBTHCTL0_RXDBTH_SHIFT)  /* Interrupt triggers at 2 Rx Buffer entries, DWORDs */
#  define R_I3C_NTBTHCTL0_RXDBTH_0X1                      (1 << R_I3C_NTBTHCTL0_RXDBTH_SHIFT)  /* Interrupt triggers at 4 Rx Buffer entries, DWORDs */
#  define R_I3C_NTBTHCTL0_RXDBTH_0X2                      (2 << R_I3C_NTBTHCTL0_RXDBTH_SHIFT)  /* Interrupt triggers at 8 Rx Buffer entries, DWORDs */
#  define R_I3C_NTBTHCTL0_RXDBTH_0X3                      (3 << R_I3C_NTBTHCTL0_RXDBTH_SHIFT)  /* Interrupt triggers at 16 Rx Buffer entries, DWORDs */
#  define R_I3C_NTBTHCTL0_RXDBTH_0X4                      (4 << R_I3C_NTBTHCTL0_RXDBTH_SHIFT)  /* Interrupt triggers at 32 Rx Buffer entries, DWORDs */
#  define R_I3C_NTBTHCTL0_RXDBTH_0X5                      (5 << R_I3C_NTBTHCTL0_RXDBTH_SHIFT)  /* Interrupt triggers at 64 Rx Buffer entries, DWORDs */
#  define R_I3C_NTBTHCTL0_RXDBTH_0X6                      (6 << R_I3C_NTBTHCTL0_RXDBTH_SHIFT)  /* Interrupt triggers at 128 Rx Buffer entries, DWORDs */
#  define R_I3C_NTBTHCTL0_RXDBTH_0X7                      (7 << R_I3C_NTBTHCTL0_RXDBTH_SHIFT)  /* Interrupt triggers at 256 Rx Buffer entries, DWORDs */

#define R_I3C_NTBTHCTL0_TXSTTH_SHIFT              (16)  /* Normal Tx Start Threshold */
#define R_I3C_NTBTHCTL0_TXSTTH_MASK               0x70000
#  define R_I3C_NTBTHCTL0_TXSTTH_0X0                      (0 << R_I3C_NTBTHCTL0_TXSTTH_SHIFT)  /* Wait for 2 DWORDs */
#  define R_I3C_NTBTHCTL0_TXSTTH_0X1                      (1 << R_I3C_NTBTHCTL0_TXSTTH_SHIFT)  /* Wait for 4 DWORDs */
#  define R_I3C_NTBTHCTL0_TXSTTH_0X2                      (2 << R_I3C_NTBTHCTL0_TXSTTH_SHIFT)  /* Wait for 8 DWORDs */
#  define R_I3C_NTBTHCTL0_TXSTTH_0X3                      (3 << R_I3C_NTBTHCTL0_TXSTTH_SHIFT)  /* Wait for 16 DWORDs */
#  define R_I3C_NTBTHCTL0_TXSTTH_0X4                      (4 << R_I3C_NTBTHCTL0_TXSTTH_SHIFT)  /* Wait for 32 DWORDs */
#  define R_I3C_NTBTHCTL0_TXSTTH_0X5                      (5 << R_I3C_NTBTHCTL0_TXSTTH_SHIFT)  /* Wait for 64 DWORDs */
#  define R_I3C_NTBTHCTL0_TXSTTH_0X6                      (6 << R_I3C_NTBTHCTL0_TXSTTH_SHIFT)  /* Wait for 128 DWORDs */
#  define R_I3C_NTBTHCTL0_TXSTTH_0X7                      (7 << R_I3C_NTBTHCTL0_TXSTTH_SHIFT)  /* Wait for 256 DWORDs */

#define R_I3C_NTBTHCTL0_RXSTTH_SHIFT              (24)  /* Normal Rx Start Threshold */
#define R_I3C_NTBTHCTL0_RXSTTH_MASK               0x7000000
#  define R_I3C_NTBTHCTL0_RXSTTH_0X0                      (0 << R_I3C_NTBTHCTL0_RXSTTH_SHIFT)  /* Wait for 2 empty DWORDs */
#  define R_I3C_NTBTHCTL0_RXSTTH_0X1                      (1 << R_I3C_NTBTHCTL0_RXSTTH_SHIFT)  /* Wait for 4 empty DWORDs */
#  define R_I3C_NTBTHCTL0_RXSTTH_0X2                      (2 << R_I3C_NTBTHCTL0_RXSTTH_SHIFT)  /* Wait for 8 empty DWORDs */
#  define R_I3C_NTBTHCTL0_RXSTTH_0X3                      (3 << R_I3C_NTBTHCTL0_RXSTTH_SHIFT)  /* Wait for 16 empty DWORDs */
#  define R_I3C_NTBTHCTL0_RXSTTH_0X4                      (4 << R_I3C_NTBTHCTL0_RXSTTH_SHIFT)  /* Wait for 32 empty DWORDs */
#  define R_I3C_NTBTHCTL0_RXSTTH_0X5                      (5 << R_I3C_NTBTHCTL0_RXSTTH_SHIFT)  /* Wait for 64 empty DWORDs */
#  define R_I3C_NTBTHCTL0_RXSTTH_0X6                      (6 << R_I3C_NTBTHCTL0_RXSTTH_SHIFT)  /* Wait for 128 empty DWORDs */
#  define R_I3C_NTBTHCTL0_RXSTTH_0X7                      (7 << R_I3C_NTBTHCTL0_RXSTTH_SHIFT)  /* Wait for 256 empty DWORDs */

/* NRQTHCTL Register bit definitions */
#define R_I3C_NRQTHCTL_RSQTH_SHIFT                (0)  /* Normal Receive Status Queue Threshold */
#define R_I3C_NRQTHCTL_RSQTH_MASK                 0xff
#  define R_I3C_NRQTHCTL_RSQTH_0                          (0 << R_I3C_NRQTHCTL_RSQTH_SHIFT)  /* Interrupt is issued when Receive Status Queue contains 1 entry
 (DWORD). */

/* HQTHCTL Register bit definitions */
#define R_I3C_HQTHCTL_CMDQTH_SHIFT                (0)  /* High Priority Command Queue Threshold */
#define R_I3C_HQTHCTL_CMDQTH_MASK                 0xff

#define R_I3C_HQTHCTL_RSPQTH_SHIFT                (8)  /* High Priority Response Queue Threshold */
#define R_I3C_HQTHCTL_RSPQTH_MASK                 0xff00
#  define R_I3C_HQTHCTL_RSPQTH_0X00                       (0 << R_I3C_HQTHCTL_RSPQTH_SHIFT)  /* Interrupt is issued when High Priority Response Queue contains 1 entry (DWORD). */

/* HTBTHCTL Register bit definitions */
#define R_I3C_HTBTHCTL_TXDBTH_SHIFT               (0)  /* High Priority Tx Data Buffer Threshold  */
#define R_I3C_HTBTHCTL_TXDBTH_MASK                0x7
#  define R_I3C_HTBTHCTL_TXDBTH_000                       (0 << R_I3C_HTBTHCTL_TXDBTH_SHIFT)  /* Interrupt triggers at 2 High Priority Tx Buffer empties, DWORDs */
#  define R_I3C_HTBTHCTL_TXDBTH_001                       (1 << R_I3C_HTBTHCTL_TXDBTH_SHIFT)  /* Reserved */

#define R_I3C_HTBTHCTL_RXDBTH_SHIFT               (8)  /* High Priority Rx Data Buffer Threshold */
#define R_I3C_HTBTHCTL_RXDBTH_MASK                0x700
#  define R_I3C_HTBTHCTL_RXDBTH_000                       (0 << R_I3C_HTBTHCTL_RXDBTH_SHIFT)  /* Interrupt triggers at 2 High Priority Rx Buffer entries, DWORDs */
#  define R_I3C_HTBTHCTL_RXDBTH_001                       (1 << R_I3C_HTBTHCTL_RXDBTH_SHIFT)  /* Reserved */

#define R_I3C_HTBTHCTL_TXSTTH_SHIFT               (16)  /* High Priority Tx Start Threshold */
#define R_I3C_HTBTHCTL_TXSTTH_MASK                0x70000
#  define R_I3C_HTBTHCTL_TXSTTH_000                       (0 << R_I3C_HTBTHCTL_TXSTTH_SHIFT)  /* Wait for 2 entry DWORDs */
#  define R_I3C_HTBTHCTL_TXSTTH_001                       (1 << R_I3C_HTBTHCTL_TXSTTH_SHIFT)  /* Reserved */

#define R_I3C_HTBTHCTL_RXSTTH_SHIFT               (24)  /* High Priority Rx Start Threshold  */
#define R_I3C_HTBTHCTL_RXSTTH_MASK                0x7000000
#  define R_I3C_HTBTHCTL_RXSTTH_000                       (0 << R_I3C_HTBTHCTL_RXSTTH_SHIFT)  /* Wait for 2 empty DWORDs */
#  define R_I3C_HTBTHCTL_RXSTTH_001                       (1 << R_I3C_HTBTHCTL_RXSTTH_SHIFT)  /* Reserved */

/* BST Register bit definitions */
#define R_I3C_BST_STCNDDF                         (1 << 0)  /* START condition Detection Flag */

#define R_I3C_BST_SPCNDDF                         (1 << 1)  /* STOP condition Detection Flag */

#define R_I3C_BST_HDREXDF                         (1 << 2)  /* HDR Exit Pattern Detection Flag */

#define R_I3C_BST_NACKDF                          (1 << 4)  /* NACK Detection Flag */

#define R_I3C_BST_TENDF                           (1 << 8)  /* Transmit End Flag */

#define R_I3C_BST_ALF                             (1 << 16)  /* Arbitration Lost Flag */

#define R_I3C_BST_TODF                            (1 << 20)  /* Timeout Detection Flag */

#define R_I3C_BST_WUCNDDF                         (1 << 24)  /* Wake-Up Condition Detection Flag */

/* BSTE Register bit definitions */
#define R_I3C_BSTE_STCNDDE                        (1 << 0)  /* START condition Detection Enable */

#define R_I3C_BSTE_SPCNDDE                        (1 << 1)  /* STOP condition Detection Enable */

#define R_I3C_BSTE_HDREXDE                        (1 << 2)  /* HDR Exit Pattern Detection Enable */

#define R_I3C_BSTE_NACKDE                         (1 << 4)  /* NACK Detection Enable */

#define R_I3C_BSTE_TENDE                          (1 << 8)  /* Transmit End Enable */

#define R_I3C_BSTE_ALE                            (1 << 16)  /* Arbitration Lost Enable */

#define R_I3C_BSTE_TODE                           (1 << 20)  /* Timeout Detection Enable */

#define R_I3C_BSTE_WUCNDDE                        (1 << 24)  /* Wake-up Condition Detection Enable */

/* BIE Register bit definitions */
#define R_I3C_BIE_STCNDDIE                        (1 << 0)  /* START condition Detection Interrupt Enable */

#define R_I3C_BIE_SPCNDDIE                        (1 << 1)  /* STOP condition Detection Interrupt Enable */

#define R_I3C_BIE_HDREXDIE                        (1 << 2)  /* HDR Exit Pattern Detection Interrupt Enable */

#define R_I3C_BIE_NACKDIE                         (1 << 4)  /* NACK Detection Interrupt Enable */

#define R_I3C_BIE_TENDIE                          (1 << 8)  /* Transmit End Interrupt Enable */

#define R_I3C_BIE_ALIE                            (1 << 16)  /* Arbitration Lost Interrupt Enable */

#define R_I3C_BIE_TODIE                           (1 << 20)  /* Timeout Detection Interrupt Enable */

#define R_I3C_BIE_WUCNDDIE                        (1 << 24)  /* Wake-Up Condition Detection Interrupt Enable */

/* BSTFC Register bit definitions */
#define R_I3C_BSTFC_STCNDDFC                      (1 << 0)  /* START condition Detection Force */

#define R_I3C_BSTFC_SPCNDDFC                      (1 << 1)  /* STOP condition Detection Force */

#define R_I3C_BSTFC_HDREXDFC                      (1 << 2)  /* HDR Exit Pattern Detection Force */

#define R_I3C_BSTFC_NACKDFC                       (1 << 4)  /* NACK Detection Force */

#define R_I3C_BSTFC_TENDFC                        (1 << 8)  /* Transmit End Force */

#define R_I3C_BSTFC_ALFC                          (1 << 16)  /* Arbitration Lost Force */

#define R_I3C_BSTFC_TODFC                         (1 << 20)  /* Timeout Detection Force */

#define R_I3C_BSTFC_WUCNDDFC                      (1 << 24)  /* Wake-Up Condition Detection Force */

/* NTST Register bit definitions */
#define R_I3C_NTST_TDBEF0                         (1 << 0)  /* Normal Transmit Data Buffer Empty Flag 0 */

#define R_I3C_NTST_RDBFF0                         (1 << 1)  /* Normal Receive Data Buffer Full Flag 0 */

#define R_I3C_NTST_IBIQEFF                        (1 << 2)  /* Normal IBI Queue Empty/Full Flag */

#define R_I3C_NTST_CMDQEF                         (1 << 3)  /* Normal Command Queue Empty Flag */

#define R_I3C_NTST_RSPQFF                         (1 << 4)  /* Normal Response Queue Full Flag */

#define R_I3C_NTST_TABTF                          (1 << 5)  /* Normal Transfer Abort Flag */

#define R_I3C_NTST_TEF                            (1 << 9)  /* Normal Transfer Error Flag */

#define R_I3C_NTST_RSQFF                          (1 << 20)  /* Normal Receive Status Queue Full Flag */

/* NTSTE Register bit definitions */
#define R_I3C_NTSTE_TDBEE0                        (1 << 0)  /* Normal Transmit Data Buffer Empty Enable 0 */

#define R_I3C_NTSTE_RDBFE0                        (1 << 1)  /* Normal Receive Data Buffer Full Enable 0 */

#define R_I3C_NTSTE_IBIQEFE                       (1 << 2)  /* Normal IBI Queue Empty/Full Enable */

#define R_I3C_NTSTE_CMDQEE                        (1 << 3)  /* Normal Command Queue Empty Enable */

#define R_I3C_NTSTE_RSPQFE                        (1 << 4)  /* Normal Response Queue Full Enable */

#define R_I3C_NTSTE_TABTE                         (1 << 5)  /* Normal Transfer Abort Enable */

#define R_I3C_NTSTE_TEE                           (1 << 9)  /* Normal Transfer Error Enable */

#define R_I3C_NTSTE_RSQFE                         (1 << 20)  /* Normal Receive Status Queue Full Enable */

/* NTIE Register bit definitions */
#define R_I3C_NTIE_TDBEIE0                        (1 << 0)  /* Normal Transmit Data Buffer Empty Interrupt Enable 0 */

#define R_I3C_NTIE_RDBFIE0                        (1 << 1)  /* Normal Receive Data Buffer Full Interrupt Enable 0 */

#define R_I3C_NTIE_IBIQEFIE                       (1 << 2)  /* Normal IBI Queue Empty/Full Interrupt Enable */

#define R_I3C_NTIE_CMDQEIE                        (1 << 3)  /* Normal Command Queue Empty Interrupt Enable */

#define R_I3C_NTIE_RSPQFIE                        (1 << 4)  /* Normal Response Queue Full Interrupt Enable */

#define R_I3C_NTIE_TABTIE                         (1 << 5)  /* Normal Transfer Abort Interrupt Enable */

#define R_I3C_NTIE_TEIE                           (1 << 9)  /* Normal Transfer Error Interrupt Enable */

#define R_I3C_NTIE_RSQFIE                         (1 << 20)  /* Normal Receive Status Queue Full Interrupt Enable */

/* NTSTFC Register bit definitions */
#define R_I3C_NTSTFC_TDBEFC0                      (1 << 0)  /* Normal Transmit Data Buffer Empty Force 0 */

#define R_I3C_NTSTFC_RDBFFC0                      (1 << 1)  /* Normal Receive Data Buffer Full Force 0 */

#define R_I3C_NTSTFC_IBIQEFFC                     (1 << 2)  /* Normal IBI Queue Empty/Full Force */

#define R_I3C_NTSTFC_CMDQEFC                      (1 << 3)  /* Normal Command Queue Empty Force */

#define R_I3C_NTSTFC_RSPQFFC                      (1 << 4)  /* Normal Response Queue Full Force */

#define R_I3C_NTSTFC_TABTFC                       (1 << 5)  /* Normal Transfer Abort Force */

#define R_I3C_NTSTFC_TEFC                         (1 << 9)  /* Normal Transfer Error Force */

#define R_I3C_NTSTFC_RSQFFC                       (1 << 20)  /* Normal Receive Status Queue Full Force */

/* HTST Register bit definitions */
#define R_I3C_HTST_TDBEF                          (1 << 0)  /* High Priority Tx Data Buffer Empty Flag */

#define R_I3C_HTST_RDBFF                          (1 << 1)  /* High Priority Rx Data Buffer Full Flag */

#define R_I3C_HTST_CMDQEF                         (1 << 3)  /* High Priority Command Queue Empty Flag */

#define R_I3C_HTST_RSPQFF                         (1 << 4)  /* High Priority Response Queue Full Flag */

#define R_I3C_HTST_TABTF                          (1 << 5)  /* High Priority Transfer Abort Flag  */

#define R_I3C_HTST_TEF                            (1 << 9)  /* High Priority Transfer Error Flag  */

/* HTSTE Register bit definitions */
#define R_I3C_HTSTE_TDBEE                         (1 << 0)  /* High Priority Tx Data Buffer Empty Enable */

#define R_I3C_HTSTE_RDBFE                         (1 << 1)  /* High Priority Rx Data Buffer Full Enable */

#define R_I3C_HTSTE_CMDQEE                        (1 << 3)  /* High Priority Command Queue Empty Enable */

#define R_I3C_HTSTE_RSPQFE                        (1 << 4)  /* High Priority Response Queue Full Enable  */

#define R_I3C_HTSTE_TABTE                         (1 << 5)  /* High Priority Transfer Abort Enable */

#define R_I3C_HTSTE_TEE                           (1 << 9)  /* High Priority Transfer Error Enable */

/* HTIE Register bit definitions */
#define R_I3C_HTIE_TDBEIE                         (1 << 0)  /* High Priority Tx Data Buffer Empty Interrupt Enable  */

#define R_I3C_HTIE_RDBFIE                         (1 << 1)  /* High Priority Rx Data Buffer Full Interrupt Enable */

#define R_I3C_HTIE_CMDQEIE                        (1 << 3)  /* High Priority Command Queue Empty Interrupt Enable */

#define R_I3C_HTIE_RSPQFIE                        (1 << 4)  /* High Priority Response Queue Full Interrupt Enable  */

#define R_I3C_HTIE_TABTIE                         (1 << 5)  /* High Priority Transfer Abort Interrupt Enable */

#define R_I3C_HTIE_TEIE                           (1 << 9)  /* High Priority Transfer Error Interrupt Enable */

/* HTSTFC Register bit definitions */
#define R_I3C_HTSTFC_TDBEFC                       (1 << 0)  /* High Priority Tx Data Buffer Empty Force */

#define R_I3C_HTSTFC_RDBFFC                       (1 << 1)  /* High Priority Rx Data Buffer Full Force */

#define R_I3C_HTSTFC_CMDQEFC                      (1 << 3)  /* High Priority Command Queue Empty Force */

#define R_I3C_HTSTFC_RSPQFFC                      (1 << 4)  /* High Priority Response Queue Full Force */

#define R_I3C_HTSTFC_TABTFC                       (1 << 5)  /* High Priority Transfer Abort Force */

#define R_I3C_HTSTFC_TEFC                         (1 << 9)  /* High Priority Transfer Error Force */

/* BCST Register bit definitions */
#define R_I3C_BCST_BFREF                          (1 << 0)  /* Bus Free Detection Flag */

#define R_I3C_BCST_BAVLF                          (1 << 1)  /* Bus Available Detection Flag */

#define R_I3C_BCST_BIDLF                          (1 << 2)  /* Bus Idle Detection Flag */

/* SVST Register bit definitions */
#define R_I3C_SVST_GCAF                           (1 << 0)  /* General Call Address Detection Flag */

#define R_I3C_SVST_HSMCF                          (1 << 5)  /* Hs-mode Master Code Detection Flag */

#define R_I3C_SVST_DVIDF                          (1 << 6)  /* Device-ID Address Detection Flag */

#define R_I3C_SVST_HOAF                           (1 << 15)  /* Host Address Detection Flag */

#define R_I3C_SVST_SVAFN_SHIFT                    (16)  /* Slave Address Detection Flag */
#define R_I3C_SVST_SVAFN_MASK                     0x70000
#  define R_I3C_SVST_SVAFN_0                              (0 << R_I3C_SVST_SVAFN_SHIFT)  /* Slave n does not detect */
#  define R_I3C_SVST_SVAFN_1                              (1 << R_I3C_SVST_SVAFN_SHIFT)  /* Slave n detect */

#define R_I3C_SVST_SVAFN_SHIFT                    (16)  /* Slave Address Detection Flag */
#define R_I3C_SVST_SVAFN_MASK                     0x70000

/* WUST Register bit definitions */
#define R_I3C_WUST_WUASYNF                        (1 << 0)  /* Wake-up function asynchronous operation status flag. */

/* MRCCPT Register bit definitions */
#define R_I3C_MRCCPT_MRCCPT_SHIFT                 (0)  /* MSyncCNT Counter Capture */
#define R_I3C_MRCCPT_MRCCPT_MASK                  0xffffffff

/* DATBAS Register bit definitions */
#define R_I3C_DATBAS_DVSTAD_SHIFT                 (0)  /* Device Static Address */
#define R_I3C_DATBAS_DVSTAD_MASK                  0x7f

#define R_I3C_DATBAS_DVIBIPL                      (1 << 12)  /* Device IBI Payload */

#define R_I3C_DATBAS_DVSIRRJ                      (1 << 13)  /* Device In-Band Slave Interrupt Request Reject */

#define R_I3C_DATBAS_DVMRRJ                       (1 << 14)  /* Device In-Band Master Request Reject */

#define R_I3C_DATBAS_DVIBITS                      (1 << 15)  /* Device IBI Time-stamp */

#define R_I3C_DATBAS_DVDYAD_SHIFT                 (16)  /* Device I3C Dynamic Address */
#define R_I3C_DATBAS_DVDYAD_MASK                  0xff0000

#define R_I3C_DATBAS_DVNACK_SHIFT                 (29)  /* Device NACK Retry Count */
#define R_I3C_DATBAS_DVNACK_MASK                  0x60000000

#define R_I3C_DATBAS_DVTYP                        (1 << 31)  /* Device Type */

/* EXDATBAS Register bit definitions */
#define R_I3C_EXDATBAS_EDSTAD_SHIFT               (0)  /* Extended Device Static Address */
#define R_I3C_EXDATBAS_EDSTAD_MASK                0x7f

#define R_I3C_EXDATBAS_EDDYAD_SHIFT               (16)  /* Extended Device I3C Dynamic Address */
#define R_I3C_EXDATBAS_EDDYAD_MASK                0xff0000

#define R_I3C_EXDATBAS_EDNACK_SHIFT               (29)  /* Extended Device NACK Retry Count */
#define R_I3C_EXDATBAS_EDNACK_MASK                0x60000000

#define R_I3C_EXDATBAS_EDTYP                      (1 << 31)  /* Extended Device Type */

/* SDATBAS Register bit definitions */
#define R_I3C_SDATBAS_SDSTAD_SHIFT                (0)  /* Slave Device Static Address */
#define R_I3C_SDATBAS_SDSTAD_MASK                 0x3ff

#define R_I3C_SDATBAS_SDADLS                      (1 << 10)  /* Slave Device Address Length Selection */

#define R_I3C_SDATBAS_SDIBIPL                     (1 << 12)  /* Slave Device IBI Payload */

#define R_I3C_SDATBAS_SDDYAD_SHIFT                (16)  /* Slave Device I3C Dynamic Address */
#define R_I3C_SDATBAS_SDDYAD_MASK                 0x7f0000

/* MSDCT Register bit definitions */
#define R_I3C_MSDCT_RBCR0                         (1 << 8)  /* Max Data Speed Limitation */

#define R_I3C_MSDCT_RBCR1                         (1 << 9)  /* IBI Request Capable */

#define R_I3C_MSDCT_RBCR2                         (1 << 10)  /* IBI Payload */

#define R_I3C_MSDCT_RBCR3                         (1 << 11)  /* Offline Capable */

#define R_I3C_MSDCT_RBCR4                         (1 << 12)  /* Bridge Identifier */

#define R_I3C_MSDCT_RBCR5                         (1 << 13)  /* SDR Only / SDR and HDR Capable */

#define R_I3C_MSDCT_RBCR76_SHIFT                  (14)  /* Device Role */
#define R_I3C_MSDCT_RBCR76_MASK                   0xc000
#  define R_I3C_MSDCT_RBCR76_00                           (0 << R_I3C_MSDCT_RBCR76_SHIFT)  /* I3C Slave */
#  define R_I3C_MSDCT_RBCR76_01                           (1 << R_I3C_MSDCT_RBCR76_SHIFT)  /* I3C Master */
#  define R_I3C_MSDCT_RBCR76_10                           (2 << R_I3C_MSDCT_RBCR76_SHIFT)  /* Reserved for future definition by MIPI Sensor WG */
#  define R_I3C_MSDCT_RBCR76_11                           (3 << R_I3C_MSDCT_RBCR76_SHIFT)  /* Reserved for future definition by MIPI Sensor WG */

/* SVDCT Register bit definitions */
#define R_I3C_SVDCT_TDCR_SHIFT                    (0)  /* Transfar Device Characteristic Register */
#define R_I3C_SVDCT_TDCR_MASK                     0xff

#define R_I3C_SVDCT_TBCR0                         (1 << 8)  /* Max Data Speed Limitation */

#define R_I3C_SVDCT_TBCR1                         (1 << 9)  /* IBI Request Capable */

#define R_I3C_SVDCT_TBCR2                         (1 << 10)  /* IBI Payload */

#define R_I3C_SVDCT_TBCR3                         (1 << 11)  /* Offline Capable */

#define R_I3C_SVDCT_TBCR4                         (1 << 12)  /* Bridge Identifier */

#define R_I3C_SVDCT_TBCR5                         (1 << 13)  /* SDR Only / SDR and HDR Capable */

#define R_I3C_SVDCT_TBCR76_SHIFT                  (14)  /* Device Role */
#define R_I3C_SVDCT_TBCR76_MASK                   0xc000
#  define R_I3C_SVDCT_TBCR76_00                           (0 << R_I3C_SVDCT_TBCR76_SHIFT)  /* I3C Slave */
#  define R_I3C_SVDCT_TBCR76_01                           (1 << R_I3C_SVDCT_TBCR76_SHIFT)  /* I3C Master */
#  define R_I3C_SVDCT_TBCR76_10                           (2 << R_I3C_SVDCT_TBCR76_SHIFT)  /* Reserved for future definition by MIPI Sensor WG */
#  define R_I3C_SVDCT_TBCR76_11                           (3 << R_I3C_SVDCT_TBCR76_SHIFT)  /* Reserved for future definition by MIPI Sensor WG */

/* SVDVAD Register bit definitions */
#define R_I3C_SVDVAD_SVAD_SHIFT                   (16)  /* Slave Address */
#define R_I3C_SVDVAD_SVAD_MASK                    0x3ff0000

#define R_I3C_SVDVAD_SADLG                        (1 << 27)  /* Slave Address Length */

#define R_I3C_SVDVAD_SSTADV                       (1 << 30)  /* Slave Static Address Valid */

#define R_I3C_SVDVAD_SDYADV                       (1 << 31)  /* Slave Dynamic Address Valid */

/* CSECMD Register bit definitions */
#define R_I3C_CSECMD_SVIRQE                       (1 << 0)  /* Slave Interrupt Requests Enable */

#define R_I3C_CSECMD_MSRQE                        (1 << 1)  /* Mastership Requests Enable */

#define R_I3C_CSECMD_HJEVE                        (1 << 3)  /* Hot-Join Event Enable */

/* CEACTST Register bit definitions */
#define R_I3C_CEACTST_ACTST_SHIFT                 (0)  /* Activity State */
#define R_I3C_CEACTST_ACTST_MASK                  0xf
#  define R_I3C_CEACTST_ACTST_0X1                         (1 << R_I3C_CEACTST_ACTST_SHIFT)  /* ENTAS0 (1us: Latency-free operation) */
#  define R_I3C_CEACTST_ACTST_0X2                         (2 << R_I3C_CEACTST_ACTST_SHIFT)  /* ENTAS1 (100 us) */
#  define R_I3C_CEACTST_ACTST_0X4                         (4 << R_I3C_CEACTST_ACTST_SHIFT)  /* ENTAS2 (2 ms) */
#  define R_I3C_CEACTST_ACTST_0X8                         (8 << R_I3C_CEACTST_ACTST_SHIFT)  /* ENTAS3 (50 ms: Lowest-activity operation) */

/* CMWLG Register bit definitions */
#define R_I3C_CMWLG_MWLG_SHIFT                    (0)  /* Max Write Length */
#define R_I3C_CMWLG_MWLG_MASK                     0xffff

/* CMRLG Register bit definitions */
#define R_I3C_CMRLG_MRLG_SHIFT                    (0)  /* Max Read Length */
#define R_I3C_CMRLG_MRLG_MASK                     0xffff

#define R_I3C_CMRLG_IBIPSZ_SHIFT                  (16)  /* IBI Payload Size */
#define R_I3C_CMRLG_IBIPSZ_MASK                   0xff0000

/* CETSTMD Register bit definitions */
#define R_I3C_CETSTMD_TSTMD_SHIFT                 (0)  /* Test Mode */
#define R_I3C_CETSTMD_TSTMD_MASK                  0xff
#  define R_I3C_CETSTMD_TSTMD_0X00                        (0 << R_I3C_CETSTMD_TSTMD_SHIFT)  /* Exit Test Mode
This value removes all I3C devices from Test Mode.
 */
#  define R_I3C_CETSTMD_TSTMD_0X01                        (1 << R_I3C_CETSTMD_TSTMD_SHIFT)  /* Vendor Test Mode
This value indicates that I3C devices shall return a random 32bit value in the provisional ID
 during the Dynamic Address Assignment procedure.
 */

/* CGDVST Register bit definitions */
#define R_I3C_CGDVST_PNDINT_SHIFT                 (0)  /* Pending Interrupt */
#define R_I3C_CGDVST_PNDINT_MASK                  0xf

#define R_I3C_CGDVST_PRTE                         (1 << 5)  /* Protocol Error */

#define R_I3C_CGDVST_ACTMD_SHIFT                  (6)  /* Slave Device's current Activity Mode */
#define R_I3C_CGDVST_ACTMD_MASK                   0xc0
#  define R_I3C_CGDVST_ACTMD_00                           (0 << R_I3C_CGDVST_ACTMD_SHIFT)  /* Activity Mode 0 */
#  define R_I3C_CGDVST_ACTMD_01                           (1 << R_I3C_CGDVST_ACTMD_SHIFT)  /* Activity Mode 1 */
#  define R_I3C_CGDVST_ACTMD_10                           (2 << R_I3C_CGDVST_ACTMD_SHIFT)  /* Activity Mode 2 */
#  define R_I3C_CGDVST_ACTMD_11                           (3 << R_I3C_CGDVST_ACTMD_SHIFT)  /* Activity Mode 3 */

#define R_I3C_CGDVST_VDRSV_SHIFT                  (8)  /* Vendor Reserved */
#define R_I3C_CGDVST_VDRSV_MASK                   0xff00

/* CMDSPW Register bit definitions */
#define R_I3C_CMDSPW_MSWDR_SHIFT                  (0)  /* Maximum Sustained Write Data Rate */
#define R_I3C_CMDSPW_MSWDR_MASK                   0x7
#  define R_I3C_CMDSPW_MSWDR_000                          (0 << R_I3C_CMDSPW_MSWDR_SHIFT)  /* fscl Max (default value) */
#  define R_I3C_CMDSPW_MSWDR_001                          (1 << R_I3C_CMDSPW_MSWDR_SHIFT)  /* 8MHz */
#  define R_I3C_CMDSPW_MSWDR_010                          (2 << R_I3C_CMDSPW_MSWDR_SHIFT)  /* 6MHz */
#  define R_I3C_CMDSPW_MSWDR_011                          (3 << R_I3C_CMDSPW_MSWDR_SHIFT)  /* 4MHz */
#  define R_I3C_CMDSPW_MSWDR_100                          (4 << R_I3C_CMDSPW_MSWDR_SHIFT)  /* 2MHz */

/* CMDSPR Register bit definitions */
#define R_I3C_CMDSPR_MSRDR_SHIFT                  (0)  /* Maximum Sustained Read Data Rate */
#define R_I3C_CMDSPR_MSRDR_MASK                   0x7
#  define R_I3C_CMDSPR_MSRDR_000                          (0 << R_I3C_CMDSPR_MSRDR_SHIFT)  /* fscl Max (default value) */
#  define R_I3C_CMDSPR_MSRDR_001                          (1 << R_I3C_CMDSPR_MSRDR_SHIFT)  /* Setting prohibited */
#  define R_I3C_CMDSPR_MSRDR_010                          (2 << R_I3C_CMDSPR_MSRDR_SHIFT)  /* Setting prohibited */
#  define R_I3C_CMDSPR_MSRDR_011                          (3 << R_I3C_CMDSPR_MSRDR_SHIFT)  /* 4MHz */
#  define R_I3C_CMDSPR_MSRDR_100                          (4 << R_I3C_CMDSPR_MSRDR_SHIFT)  /* 2MHz */

#define R_I3C_CMDSPR_CDTTIM_SHIFT                 (3)  /* Clock to Data Turnaround Time (TSCO) */
#define R_I3C_CMDSPR_CDTTIM_MASK                  0x38
#  define R_I3C_CMDSPR_CDTTIM_000                         (0 << R_I3C_CMDSPR_CDTTIM_SHIFT)  /* 8 ns or less (default value) */
#  define R_I3C_CMDSPR_CDTTIM_001                         (1 << R_I3C_CMDSPR_CDTTIM_SHIFT)  /* 9 ns or less */
#  define R_I3C_CMDSPR_CDTTIM_010                         (2 << R_I3C_CMDSPR_CDTTIM_SHIFT)  /* 10 ns or less */
#  define R_I3C_CMDSPR_CDTTIM_011                         (3 << R_I3C_CMDSPR_CDTTIM_SHIFT)  /* 11 ns or less */
#  define R_I3C_CMDSPR_CDTTIM_100                         (4 << R_I3C_CMDSPR_CDTTIM_SHIFT)  /* 12 ns or less */
#  define R_I3C_CMDSPR_CDTTIM_111                         (7 << R_I3C_CMDSPR_CDTTIM_SHIFT)  /* TSCO is more than 12 ns. */

/* CMDSPT Register bit definitions */
#define R_I3C_CMDSPT_MRTTIM_SHIFT                 (0)  /* Maximum Read Turnaround Time */
#define R_I3C_CMDSPT_MRTTIM_MASK                  0xffffff

#define R_I3C_CMDSPT_MRTE                         (1 << 31)  /* Maximum Read Turnaround Time Enable */

/* CETSM Register bit definitions */
#define R_I3C_CETSM_SPTSYN                        (1 << 0)  /* Supports Sync Mode */

#define R_I3C_CETSM_SPTASYN0                      (1 << 1)  /* Support Async Mode 0 */

#define R_I3C_CETSM_SPTASYN1                      (1 << 2)  /* Support Async Mode 1 */

#define R_I3C_CETSM_FREQ_SHIFT                    (8)  /* Frequency Byte */
#define R_I3C_CETSM_FREQ_MASK                     0xff00
#  define R_I3C_CETSM_FREQ_0X00                           (0 << R_I3C_CETSM_FREQ_SHIFT)  /* 32.0 KHz */
#  define R_I3C_CETSM_FREQ_0X0F                           (15 << R_I3C_CETSM_FREQ_SHIFT)  /* 7.5 MHz */
#  define R_I3C_CETSM_FREQ_0X1F                           (31 << R_I3C_CETSM_FREQ_SHIFT)  /* 15.5 MHz */
#  define R_I3C_CETSM_FREQ_0X2F                           (47 << R_I3C_CETSM_FREQ_SHIFT)  /* 23.5 MHz */
#  define R_I3C_CETSM_FREQ_0X3F                           (63 << R_I3C_CETSM_FREQ_SHIFT)  /* 31.5 MHz */
#  define R_I3C_CETSM_FREQ_0X4F                           (79 << R_I3C_CETSM_FREQ_SHIFT)  /* 39.5 MHz */
#  define R_I3C_CETSM_FREQ_0X5F                           (95 << R_I3C_CETSM_FREQ_SHIFT)  /* 47.5 MHz */
#  define R_I3C_CETSM_FREQ_0X6F                           (111 << R_I3C_CETSM_FREQ_SHIFT)  /* 55.5 MHz */
#  define R_I3C_CETSM_FREQ_0X7F                           (127 << R_I3C_CETSM_FREQ_SHIFT)  /* 63.5 MHz */
#  define R_I3C_CETSM_FREQ_0X8F                           (143 << R_I3C_CETSM_FREQ_SHIFT)  /* Setting prohibited */
#  define R_I3C_CETSM_FREQ_0X9F                           (159 << R_I3C_CETSM_FREQ_SHIFT)  /* Setting prohibited */
#  define R_I3C_CETSM_FREQ_0XAF                           (175 << R_I3C_CETSM_FREQ_SHIFT)  /* Setting prohibited */
#  define R_I3C_CETSM_FREQ_0XBF                           (191 << R_I3C_CETSM_FREQ_SHIFT)  /* Setting prohibited */
#  define R_I3C_CETSM_FREQ_0XCF                           (207 << R_I3C_CETSM_FREQ_SHIFT)  /* Setting prohibited */
#  define R_I3C_CETSM_FREQ_0XDF                           (223 << R_I3C_CETSM_FREQ_SHIFT)  /* Setting prohibited */
#  define R_I3C_CETSM_FREQ_0XEF                           (239 << R_I3C_CETSM_FREQ_SHIFT)  /* Setting prohibited */
#  define R_I3C_CETSM_FREQ_0XFF                           (255 << R_I3C_CETSM_FREQ_SHIFT)  /* Setting prohibited */

#define R_I3C_CETSM_INAC_SHIFT                    (16)  /* Inaccuracy Byte */
#define R_I3C_CETSM_INAC_MASK                     0xff0000
#  define R_I3C_CETSM_INAC_0X00                           (0 << R_I3C_CETSM_INAC_SHIFT)  /* 0.0% */
#  define R_I3C_CETSM_INAC_0X0F                           (15 << R_I3C_CETSM_INAC_SHIFT)  /* 1.5% */
#  define R_I3C_CETSM_INAC_0X1F                           (31 << R_I3C_CETSM_INAC_SHIFT)  /* 3.1% */
#  define R_I3C_CETSM_INAC_0X2F                           (47 << R_I3C_CETSM_INAC_SHIFT)  /* 4.7% */
#  define R_I3C_CETSM_INAC_0X3F                           (63 << R_I3C_CETSM_INAC_SHIFT)  /* 6.3% */
#  define R_I3C_CETSM_INAC_0X4F                           (79 << R_I3C_CETSM_INAC_SHIFT)  /* 7.9% */
#  define R_I3C_CETSM_INAC_0X5F                           (95 << R_I3C_CETSM_INAC_SHIFT)  /* 9.5% */
#  define R_I3C_CETSM_INAC_0X6F                           (111 << R_I3C_CETSM_INAC_SHIFT)  /* 11.1% */
#  define R_I3C_CETSM_INAC_0X7F                           (127 << R_I3C_CETSM_INAC_SHIFT)  /* 12.7% */
#  define R_I3C_CETSM_INAC_0X8F                           (143 << R_I3C_CETSM_INAC_SHIFT)  /* 14.3% */
#  define R_I3C_CETSM_INAC_0X9F                           (159 << R_I3C_CETSM_INAC_SHIFT)  /* 15.9% */
#  define R_I3C_CETSM_INAC_0XAF                           (175 << R_I3C_CETSM_INAC_SHIFT)  /* 17.5% */
#  define R_I3C_CETSM_INAC_0XBF                           (191 << R_I3C_CETSM_INAC_SHIFT)  /* 19.1% */
#  define R_I3C_CETSM_INAC_0XCF                           (207 << R_I3C_CETSM_INAC_SHIFT)  /* 20.7% */
#  define R_I3C_CETSM_INAC_0XDF                           (223 << R_I3C_CETSM_INAC_SHIFT)  /* 22.3% */
#  define R_I3C_CETSM_INAC_0XEF                           (239 << R_I3C_CETSM_INAC_SHIFT)  /* 23.9% */
#  define R_I3C_CETSM_INAC_0XFF                           (255 << R_I3C_CETSM_INAC_SHIFT)  /* 25.5% */

/* CETSS Register bit definitions */
#define R_I3C_CETSS_SYNE                          (1 << 0)  /* Sync Mode Enabled */

#define R_I3C_CETSS_ASYNE_SHIFT                   (1)  /* Async Mode Enabled */
#define R_I3C_CETSS_ASYNE_MASK                    0x6
#  define R_I3C_CETSS_ASYNE_00                            (0 << R_I3C_CETSS_ASYNE_SHIFT)  /* All Mode Disable */
#  define R_I3C_CETSS_ASYNE_01                            (1 << R_I3C_CETSS_ASYNE_SHIFT)  /* Async Mode 0 Enabled */
#  define R_I3C_CETSS_ASYNE_10                            (2 << R_I3C_CETSS_ASYNE_SHIFT)  /* Async Mode 1 Enabled */

#define R_I3C_CETSS_ICOVF                         (1 << 7)  /* Internal Counter Overflow */

/* CGHDRCAP Register bit definitions */
#define R_I3C_CGHDRCAP_DDREN                      (1 << 0)  /* HDR-DDR Operation Enable */

#define R_I3C_CGHDRCAP_TSPEN                      (1 << 1)  /* HDR-TSP Operation Enable */

#define R_I3C_CGHDRCAP_TSLEN                      (1 << 2)  /* HDR-TSL Operation Enable */

/* BITCNT Register bit definitions */
#define R_I3C_BITCNT_BCNT_SHIFT                   (0)  /* Bit Counter */
#define R_I3C_BITCNT_BCNT_MASK                    0x1f
#  define R_I3C_BITCNT_BCNT_0X00                          (0 << R_I3C_BITCNT_BCNT_SHIFT)  /* 9 bits (SDR/Legacy I2C Message)
 */
#  define R_I3C_BITCNT_BCNT_0X01                          (1 << R_I3C_BITCNT_BCNT_SHIFT)  /* 1 bit (SDR/Legacy I2C Message)
 */
#  define R_I3C_BITCNT_BCNT_0X02                          (2 << R_I3C_BITCNT_BCNT_SHIFT)  /* 2 bits (SDR/Legacy I2C Message)
 */
#  define R_I3C_BITCNT_BCNT_0X03                          (3 << R_I3C_BITCNT_BCNT_SHIFT)  /* 3 bits (SDR/Legacy I2C Message)
 */
#  define R_I3C_BITCNT_BCNT_0X04                          (4 << R_I3C_BITCNT_BCNT_SHIFT)  /* 4 bits (SDR/Legacy I2C Message)
 */
#  define R_I3C_BITCNT_BCNT_0X05                          (5 << R_I3C_BITCNT_BCNT_SHIFT)  /* 5 bits (SDR/Legacy I2C Message)
 */
#  define R_I3C_BITCNT_BCNT_0X06                          (6 << R_I3C_BITCNT_BCNT_SHIFT)  /* 6 bits (SDR/Legacy I2C Message)
 */
#  define R_I3C_BITCNT_BCNT_0X07                          (7 << R_I3C_BITCNT_BCNT_SHIFT)  /* 7 bits (SDR/Legacy I2C Message)
 */
#  define R_I3C_BITCNT_BCNT_0X08                          (8 << R_I3C_BITCNT_BCNT_SHIFT)  /* 8 bits (SDR/Legacy I2C Message)
 */

#define R_I3C_BITCNT_BCNTWP                       (1 << 7)  /* BCNT Write Protect */

/* NQSTLV Register bit definitions */
#define R_I3C_NQSTLV_CMDQFLV_SHIFT                (0)  /* Normal Command Queue Free Level */
#define R_I3C_NQSTLV_CMDQFLV_MASK                 0xff

#define R_I3C_NQSTLV_RSPQLV_SHIFT                 (8)  /* Normal Response Queue Level */
#define R_I3C_NQSTLV_RSPQLV_MASK                  0xff00

#define R_I3C_NQSTLV_IBIQLV_SHIFT                 (16)  /* Normal IBI Queue Level */
#define R_I3C_NQSTLV_IBIQLV_MASK                  0xff0000

#define R_I3C_NQSTLV_IBISCNT_SHIFT                (24)  /* Normal IBI Status Count */
#define R_I3C_NQSTLV_IBISCNT_MASK                 0x1f000000

/* NDBSTLV0 Register bit definitions */
#define R_I3C_NDBSTLV0_TDBFLV_SHIFT               (0)  /* Normal Transmit Data Buffer Free Level */
#define R_I3C_NDBSTLV0_TDBFLV_MASK                0xff

#define R_I3C_NDBSTLV0_RDBLV_SHIFT                (8)  /* Normal Receive Data Buffer Level */
#define R_I3C_NDBSTLV0_RDBLV_MASK                 0xff00

/* NRSQSTLV Register bit definitions */
#define R_I3C_NRSQSTLV_RSQLV_SHIFT                (0)  /* Normal Receive Status Queue Level */
#define R_I3C_NRSQSTLV_RSQLV_MASK                 0xff

/* HQSTLV Register bit definitions */
#define R_I3C_HQSTLV_CMDQLV_SHIFT                 (0)  /* High Priority Command Queue Level */
#define R_I3C_HQSTLV_CMDQLV_MASK                  0xff

#define R_I3C_HQSTLV_RSPQLV_SHIFT                 (8)  /* High Priority Response Queue Level */
#define R_I3C_HQSTLV_RSPQLV_MASK                  0xff00

/* HDBSTLV Register bit definitions */
#define R_I3C_HDBSTLV_TDBFLV_SHIFT                (0)  /* High Priority Tx Data Buffer Free Level */
#define R_I3C_HDBSTLV_TDBFLV_MASK                 0xff

#define R_I3C_HDBSTLV_RDBLV_SHIFT                 (8)  /* High Priority Rx Data Buffer Level */
#define R_I3C_HDBSTLV_RDBLV_MASK                  0xff00

/* PRSTDBG Register bit definitions */
#define R_I3C_PRSTDBG_SCILV                       (1 << 0)  /* SCL Line Signal Level */

#define R_I3C_PRSTDBG_SDILV                       (1 << 1)  /* SDA Line Signal Level */

#define R_I3C_PRSTDBG_SCOLV                       (1 << 2)  /* SCL Output Level */

#define R_I3C_PRSTDBG_SDOLV                       (1 << 3)  /* SDA Output Level */

/* MSERRCNT Register bit definitions */
#define R_I3C_MSERRCNT_M2ECNT_SHIFT               (0)  /* M2 Error Counter */
#define R_I3C_MSERRCNT_M2ECNT_MASK                0xff

/* SC1CPT Register bit definitions */
#define R_I3C_SC1CPT_SC1C_SHIFT                   (0)  /* SC1 Capture */
#define R_I3C_SC1CPT_SC1C_MASK                    0xffff

/* SC2CPT Register bit definitions */
#define R_I3C_SC2CPT_SC2C_SHIFT                   (0)  /* SC2 Capture */
#define R_I3C_SC2CPT_SC2C_MASK                    0xffff


/* Maximum number of channels */

#define I3C_MAX_CHANNELS    8

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_I3C_H */

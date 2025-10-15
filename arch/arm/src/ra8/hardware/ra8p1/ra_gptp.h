/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_gptp.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPTP_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPTP_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPTP Base Address */
#ifndef R_GPTP_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_GPTP_BASE           0x403e0000
#else
#define R_GPTP_BASE           0x503e0000
#endif
#endif

/* GPTP Register Offsets */

#define R_GPTP_PTPIPV_OFFSET                      0x00000000  /* IP Version Register */
#define R_GPTP_PTPTMEC_OFFSET                     0x00000010  /* Timer Enable Configuration Register */
#define R_GPTP_PTPTMDC_OFFSET                     0x00000014  /* Timer Disable Configuration Register */
/* PTPTIVC%s Registers (0-1) */
#define R_GPTP_PTPTIVC_OFFSET(m)                  (0x00000020 + ((m) * 0x00000040))  /* Timer %s Increment Value Configuration Register */
/* PTPTOVC%sL Registers (0-1) */
#define R_GPTP_PTPTOVCL_OFFSET(m)                 (0x00000030 + ((m) * 0x00000040))  /* Timer %s Offset Value Configuration Register L */
/* PTPTOVCM%s Registers (0-1) */
#define R_GPTP_PTPTOVCM_OFFSET(m)                 (0x00000034 + ((m) * 0x00000040))  /* Timer %s Offset Value Configuration Register M */
/* PTPTOVC%sU Registers (0-1) */
#define R_GPTP_PTPTOVCU_OFFSET(m)                 (0x00000038 + ((m) * 0x00000040))  /* Timer %s Offset Value Configuration Register U */
/* PTPAVTPTM%sL Registers (0-1) */
#define R_GPTP_PTPAVTPTML_OFFSET(m)               (0x00000040 + ((m) * 0x00000040))  /* AVTP Timer %s Monitoring Register L */
/* PTPAVTPTM%sU Registers (0-1) */
#define R_GPTP_PTPAVTPTMU_OFFSET(m)               (0x00000044 + ((m) * 0x00000040))  /* AVTP Timer %s Monitoring Register U */
/* PTPGPTPTM%sL Registers (0-1) */
#define R_GPTP_PTPGPTPTML_OFFSET(m)               (0x00000050 + ((m) * 0x00000040))  /* GPTP Timer %s Monitoring Register L */
/* PTPGPTPTM%sM Registers (0-1) */
#define R_GPTP_PTPGPTPTMM_OFFSET(m)               (0x00000054 + ((m) * 0x00000040))  /* GPTP Timer %s Monitoring Register M */
/* PTPGPTPTM%sU Registers (0-1) */
#define R_GPTP_PTPGPTPTMU_OFFSET(m)               (0x00000058 + ((m) * 0x00000040))  /* GPTP Timer %s Monitoring Register U */
/* PTPMCCC%s Registers (0-1) */
#define R_GPTP_PTPMCCC_OFFSET(m)                  (0x00000200 + ((m) * 0x00000010))  /* Media Clock %s Capture Configuration Register */
/* PTPMCCM%sL Registers (0-1) */
#define R_GPTP_PTPMCCML_OFFSET(m)                 (0x00000204 + ((m) * 0x00000010))  /* Media Clock %s Capture Monitoring Register L */
/* PTPMCCM%sM Registers (0-1) */
#define R_GPTP_PTPMCCMM_OFFSET(m)                 (0x00000208 + ((m) * 0x00000010))  /* Media Clock %s Capture Monitoring Register M */
/* PTPMCCM%sU Registers (0-1) */
#define R_GPTP_PTPMCCMU_OFFSET(m)                 (0x0000020c + ((m) * 0x00000010))  /* Media Clock %s Capture Monitoring Register U */
/* PTPMCRC%s Registers (0-1) */
#define R_GPTP_PTPMCRC_OFFSET(m)                  (0x00000300 + ((m) * 0x00000010))  /* Media Clock %s Recovery Configuration Register */
/* PTPMCRTC%sL Registers (0-1) */
#define R_GPTP_PTPMCRTCL_OFFSET(m)                (0x00000304 + ((m) * 0x00000010))  /* Media Clock %s Recovery Time Configuration Register L */
/* PTPMCRTC%sM Registers (0-1) */
#define R_GPTP_PTPMCRTCM_OFFSET(m)                (0x00000308 + ((m) * 0x00000010))  /* Media Clock %s Recovery Time Configuration Register M */
/* PTPMCRTC%sU Registers (0-1) */
#define R_GPTP_PTPMCRTCU_OFFSET(m)                (0x0000030c + ((m) * 0x00000010))  /* Media Clock %s Recovery Time Configuration Register U */
/* PTPMCPC%s Registers (0-1) */
#define R_GPTP_PTPMCPC_OFFSET(m)                  (0x00000400 + ((m) * 0x00000004))  /* Media Clock %s Pin Configuration Register */
/* PTPCCC%s0 Registers (0-7) */
#define R_GPTP_PTPCCC0_OFFSET(m)                  (0x00000500 + ((m) * 0x00000008))  /* Cyclic Compare %s Configuration Register 0 (c = 0 to 7) */
/* PTPCCC%s1 Registers (0-7) */
#define R_GPTP_PTPCCC1_OFFSET(m)                  (0x00000504 + ((m) * 0x00000008))  /* Cyclic Compare %s Configuration Register 1 (c = 0 to 7) */
#define R_GPTP_PTPIS0_OFFSET                      0x00000700  /* Interrupt Status Register 0 */
#define R_GPTP_PTPIE0_OFFSET                      0x00000704  /* Interrupt Enable Register 0 */
#define R_GPTP_PTPID0_OFFSET                      0x00000708  /* Interrupt Disable Register 0 */
#define R_GPTP_PTPIS1_OFFSET                      0x00000710  /* Interrupt Status Register 1 */
#define R_GPTP_PTPIE1_OFFSET                      0x00000714  /* Interrupt Enable Register 1 */
#define R_GPTP_PTPID1_OFFSET                      0x00000718  /* Interrupt Disable Register 1 */
#define R_GPTP_POTCFGR_OFFSET                     0x00001000  /* Pulse Output Timer Configuration Register */
/* POTCR%s Registers (0-3) */
#define R_GPTP_POTCR_OFFSET(m)                    (0x00001004 + ((m) * 0x00000030))  /* Pulse Output Timer Control Register %s */
/* POTSTR%sU Registers (0-3) */
#define R_GPTP_POTSTRU_OFFSET(m)                  (0x00001008 + ((m) * 0x00000030))  /* Pulse Output Start Time Setting Register nU */
/* POTSTR%sM Registers (0-3) */
#define R_GPTP_POTSTRM_OFFSET(m)                  (0x0000100c + ((m) * 0x00000030))  /* Pulse Output Start Time Setting Register nM */
/* POTSTR%sL Registers (0-3) */
#define R_GPTP_POTSTRL_OFFSET(m)                  (0x00001010 + ((m) * 0x00000030))  /* Pulse Output Start Time Setting Register nL */
/* POTPER%sU Registers (0-3) */
#define R_GPTP_POTPERU_OFFSET(m)                  (0x00001014 + ((m) * 0x00000030))  /* Period Setting Register nU */
/* POTPER%sM Registers (0-3) */
#define R_GPTP_POTPERM_OFFSET(m)                  (0x00001018 + ((m) * 0x00000030))  /* Period Setting Register nM */
/* POTPER%sL Registers (0-3) */
#define R_GPTP_POTPERL_OFFSET(m)                  (0x0000101c + ((m) * 0x00000030))  /* Period Setting Register nL */
/* POTPWR%s Registers (0-3) */
#define R_GPTP_POTPWR_OFFSET(m)                   (0x00001020 + ((m) * 0x00000030))  /* Pulse Width Setting Register %s */
/* POTCPR%sU Registers (0-3) */
#define R_GPTP_POTCPRU_OFFSET(m)                  (0x00001028 + ((m) * 0x00000030))  /* Time Capture Register nU */
/* POTCPR%sM Registers (0-3) */
#define R_GPTP_POTCPRM_OFFSET(m)                  (0x0000102c + ((m) * 0x00000030))  /* Time Capture Register nM */
/* POTCPR%sL Registers (0-3) */
#define R_GPTP_POTCPRL_OFFSET(m)                  (0x00001030 + ((m) * 0x00000030))  /* Time Capture Register nL */

/* GPTP Register Addresses */

#define R_GPTP_PTPIPV                             (R_GPTP_BASE + R_GPTP_PTPIPV_OFFSET)
#define R_GPTP_PTPTMEC                            (R_GPTP_BASE + R_GPTP_PTPTMEC_OFFSET)
#define R_GPTP_PTPTMDC                            (R_GPTP_BASE + R_GPTP_PTPTMDC_OFFSET)
#define R_GPTP_PTPTIVC(m)                         (R_GPTP_BASE + R_GPTP_PTPTIVC_OFFSET(m))
#define R_GPTP_PTPTOVCL(m)                        (R_GPTP_BASE + R_GPTP_PTPTOVCL_OFFSET(m))
#define R_GPTP_PTPTOVCM(m)                        (R_GPTP_BASE + R_GPTP_PTPTOVCM_OFFSET(m))
#define R_GPTP_PTPTOVCU(m)                        (R_GPTP_BASE + R_GPTP_PTPTOVCU_OFFSET(m))
#define R_GPTP_PTPAVTPTML(m)                      (R_GPTP_BASE + R_GPTP_PTPAVTPTML_OFFSET(m))
#define R_GPTP_PTPAVTPTMU(m)                      (R_GPTP_BASE + R_GPTP_PTPAVTPTMU_OFFSET(m))
#define R_GPTP_PTPGPTPTML(m)                      (R_GPTP_BASE + R_GPTP_PTPGPTPTML_OFFSET(m))
#define R_GPTP_PTPGPTPTMM(m)                      (R_GPTP_BASE + R_GPTP_PTPGPTPTMM_OFFSET(m))
#define R_GPTP_PTPGPTPTMU(m)                      (R_GPTP_BASE + R_GPTP_PTPGPTPTMU_OFFSET(m))
#define R_GPTP_PTPMCCC(m)                         (R_GPTP_BASE + R_GPTP_PTPMCCC_OFFSET(m))
#define R_GPTP_PTPMCCML(m)                        (R_GPTP_BASE + R_GPTP_PTPMCCML_OFFSET(m))
#define R_GPTP_PTPMCCMM(m)                        (R_GPTP_BASE + R_GPTP_PTPMCCMM_OFFSET(m))
#define R_GPTP_PTPMCCMU(m)                        (R_GPTP_BASE + R_GPTP_PTPMCCMU_OFFSET(m))
#define R_GPTP_PTPMCRC(m)                         (R_GPTP_BASE + R_GPTP_PTPMCRC_OFFSET(m))
#define R_GPTP_PTPMCRTCL(m)                       (R_GPTP_BASE + R_GPTP_PTPMCRTCL_OFFSET(m))
#define R_GPTP_PTPMCRTCM(m)                       (R_GPTP_BASE + R_GPTP_PTPMCRTCM_OFFSET(m))
#define R_GPTP_PTPMCRTCU(m)                       (R_GPTP_BASE + R_GPTP_PTPMCRTCU_OFFSET(m))
#define R_GPTP_PTPMCPC(m)                         (R_GPTP_BASE + R_GPTP_PTPMCPC_OFFSET(m))
#define R_GPTP_PTPCCC0(m)                         (R_GPTP_BASE + R_GPTP_PTPCCC0_OFFSET(m))
#define R_GPTP_PTPCCC1(m)                         (R_GPTP_BASE + R_GPTP_PTPCCC1_OFFSET(m))
#define R_GPTP_PTPIS0                             (R_GPTP_BASE + R_GPTP_PTPIS0_OFFSET)
#define R_GPTP_PTPIE0                             (R_GPTP_BASE + R_GPTP_PTPIE0_OFFSET)
#define R_GPTP_PTPID0                             (R_GPTP_BASE + R_GPTP_PTPID0_OFFSET)
#define R_GPTP_PTPIS1                             (R_GPTP_BASE + R_GPTP_PTPIS1_OFFSET)
#define R_GPTP_PTPIE1                             (R_GPTP_BASE + R_GPTP_PTPIE1_OFFSET)
#define R_GPTP_PTPID1                             (R_GPTP_BASE + R_GPTP_PTPID1_OFFSET)
#define R_GPTP_POTCFGR                            (R_GPTP_BASE + R_GPTP_POTCFGR_OFFSET)
#define R_GPTP_POTCR(m)                           (R_GPTP_BASE + R_GPTP_POTCR_OFFSET(m))
#define R_GPTP_POTSTRU(m)                         (R_GPTP_BASE + R_GPTP_POTSTRU_OFFSET(m))
#define R_GPTP_POTSTRM(m)                         (R_GPTP_BASE + R_GPTP_POTSTRM_OFFSET(m))
#define R_GPTP_POTSTRL(m)                         (R_GPTP_BASE + R_GPTP_POTSTRL_OFFSET(m))
#define R_GPTP_POTPERU(m)                         (R_GPTP_BASE + R_GPTP_POTPERU_OFFSET(m))
#define R_GPTP_POTPERM(m)                         (R_GPTP_BASE + R_GPTP_POTPERM_OFFSET(m))
#define R_GPTP_POTPERL(m)                         (R_GPTP_BASE + R_GPTP_POTPERL_OFFSET(m))
#define R_GPTP_POTPWR(m)                          (R_GPTP_BASE + R_GPTP_POTPWR_OFFSET(m))
#define R_GPTP_POTCPRU(m)                         (R_GPTP_BASE + R_GPTP_POTCPRU_OFFSET(m))
#define R_GPTP_POTCPRM(m)                         (R_GPTP_BASE + R_GPTP_POTCPRM_OFFSET(m))
#define R_GPTP_POTCPRL(m)                         (R_GPTP_BASE + R_GPTP_POTCPRL_OFFSET(m))

/* Register bit definitions */
/* PTPIPV Register bit definitions */
#define R_GPTP_PTPIPV_IPV_SHIFT                   (0)  /* IP Version */
#define R_GPTP_PTPIPV_IPV_MASK                    0xffffffff

/* PTPTMEC Register bit definitions */
#define R_GPTP_PTPTMEC_TE0                        (1 << 0)  /* Timer q Enable (q = 0, 1) */

#define R_GPTP_PTPTMEC_TE1                        (1 << 1)  /* Timer q Enable (q = 0, 1) */

#define R_GPTP_PTPTMEC_TE_SHIFT                   (0)  /* Timer Enable */
#define R_GPTP_PTPTMEC_TE_MASK                    0x3

/* PTPTMDC Register bit definitions */
#define R_GPTP_PTPTMDC_TD1_TO_TD0_SHIFT           (0)  /* Timer n Disable (n = 0, 1) */
#define R_GPTP_PTPTMDC_TD1_TO_TD0_MASK            0x3
#  define R_GPTP_PTPTMDC_TD1_TO_TD0_0                     (0 << R_GPTP_PTPTMDC_TD1_TO_TD0_SHIFT)  /* No effect */
#  define R_GPTP_PTPTMDC_TD1_TO_TD0_1                     (1 << R_GPTP_PTPTMDC_TD1_TO_TD0_SHIFT)  /* Bit q of this register clears PTPTMEC.TEq */

#define R_GPTP_PTPTMDC_TD_SHIFT                   (0)  /* Timer Disable */
#define R_GPTP_PTPTMDC_TD_MASK                    0x3

/* PTPTIVC Register bit definitions */
#define R_GPTP_PTPTIVC_TIV_SHIFT                  (0)  /* Timer Increment Value */
#define R_GPTP_PTPTIVC_TIV_MASK                   0xffffffff

/* PTPTOVCL Register bit definitions */
#define R_GPTP_PTPTOVCL_TOVL_SHIFT                (0)  /* Timer Offset Value Lower Part */
#define R_GPTP_PTPTOVCL_TOVL_MASK                 0x3fffffff

/* PTPTOVCM Register bit definitions */
#define R_GPTP_PTPTOVCM_TOVM_SHIFT                (0)  /* Timer Offset Value Middle Part */
#define R_GPTP_PTPTOVCM_TOVM_MASK                 0xffffffff

/* PTPTOVCU Register bit definitions */
#define R_GPTP_PTPTOVCU_TOVU_SHIFT                (0)  /* Timer Offset Value Upper Part */
#define R_GPTP_PTPTOVCU_TOVU_MASK                 0xffff

/* PTPAVTPTML Register bit definitions */
#define R_GPTP_PTPAVTPTML_AVTPL_SHIFT             (0)  /* AVTP Timer Value Lower Part */
#define R_GPTP_PTPAVTPTML_AVTPL_MASK              0xffffffff

/* PTPAVTPTMU Register bit definitions */
#define R_GPTP_PTPAVTPTMU_AVTPU_SHIFT             (0)  /* AVTP Timer Value Upper Part */
#define R_GPTP_PTPAVTPTMU_AVTPU_MASK              0xffffffff

/* PTPGPTPTML Register bit definitions */
#define R_GPTP_PTPGPTPTML_GPTPL_SHIFT             (0)  /* GPTP Timer Value Lower Part */
#define R_GPTP_PTPGPTPTML_GPTPL_MASK              0x3fffffff

/* PTPGPTPTMM Register bit definitions */
#define R_GPTP_PTPGPTPTMM_GPTPM_SHIFT             (0)  /* GPTP Timer Value Middle Part */
#define R_GPTP_PTPGPTPTMM_GPTPM_MASK              0xffffffff

/* PTPGPTPTMU Register bit definitions */
#define R_GPTP_PTPGPTPTMU_GPTPU_SHIFT             (0)  /* GPTP Timer Value Upper Part */
#define R_GPTP_PTPGPTPTMU_GPTPU_MASK              0xffff

/* PTPMCCC Register bit definitions */
#define R_GPTP_PTPMCCC_MCPEE                      (1 << 0)  /* Media Clock Capture Positive Edge Enable */

#define R_GPTP_PTPMCCC_MCNEE                      (1 << 1)  /* Media Clock Capture Negative Edge Enable */

#define R_GPTP_PTPMCCC_MCTTS                      (1 << 2)  /* Media Clock Capture Timer Type Select */

#define R_GPTP_PTPMCCC_MCTNS                      (1 << 3)  /* Media Clock Capture Timer Number Select */

#define R_GPTP_PTPMCCC_MCCR                       (1 << 16)  /* Media Clock Capture Request */

/* PTPMCCML Register bit definitions */
#define R_GPTP_PTPMCCML_MCCTVL_SHIFT              (0)  /* Media Clock Captured Timer Value Lower Part */
#define R_GPTP_PTPMCCML_MCCTVL_MASK               0xffffffff

/* PTPMCCMM Register bit definitions */
#define R_GPTP_PTPMCCMM_MCCTVM_SHIFT              (0)  /* Media Clock Captured Timer Value Middle Part */
#define R_GPTP_PTPMCCMM_MCCTVM_MASK               0xffffffff

/* PTPMCCMU Register bit definitions */
#define R_GPTP_PTPMCCMU_MCCTVU_SHIFT              (0)  /* Media Clock Captured Timer Value Upper Part */
#define R_GPTP_PTPMCCMU_MCCTVU_MASK               0xffff

#define R_GPTP_PTPMCCMU_MCPEC                     (1 << 16)  /* Media Clock Positive Edge Captured */

#define R_GPTP_PTPMCCMU_MCNEC                     (1 << 17)  /* Media Clock Negative Edge Captured */

#define R_GPTP_PTPMCCMU_MCSWC                     (1 << 18)  /* Media Clock Software Captured */

#define R_GPTP_PTPMCCMU_MCCN_SHIFT                (24)  /* Media Clock Capture Number */
#define R_GPTP_PTPMCCMU_MCCN_MASK                 0x3000000

/* PTPMCRC Register bit definitions */
#define R_GPTP_PTPMCRC_MRTTS                      (1 << 0)  /* Media Clock Recovery Timer Type Select */

#define R_GPTP_PTPMCRC_MRAMS                      (1 << 1)  /* Media Clock Recovery AVTP Mode Select */

#define R_GPTP_PTPMCRC_MRTNS                      (1 << 2)  /* Media Clock Recovery Timer Number Select */

#define R_GPTP_PTPMCRC_MRPL_SHIFT                 (16)  /* Media Clock Recovery Pulse Length */
#define R_GPTP_PTPMCRC_MRPL_MASK                  0xffff0000

/* PTPMCRTCL Register bit definitions */
#define R_GPTP_PTPMCRTCL_MRTVL_SHIFT              (0)  /* Media Clock Recovery Timer Value Lower Part */
#define R_GPTP_PTPMCRTCL_MRTVL_MASK               0xffffffff

/* PTPMCRTCM Register bit definitions */
#define R_GPTP_PTPMCRTCM_MRTVM_SHIFT              (0)  /* Media Clock Recovery Timer Value Middle Part */
#define R_GPTP_PTPMCRTCM_MRTVM_MASK               0xffffffff

/* PTPMCRTCU Register bit definitions */
#define R_GPTP_PTPMCRTCU_MRTVU_SHIFT              (0)  /* Media Clock Recovery Timer Value Upper Part */
#define R_GPTP_PTPMCRTCU_MRTVU_MASK               0xffff

#define R_GPTP_PTPMCRTCU_MRTT_SHIFT               (16)  /* Media Clock Recovery Trigger Type */
#define R_GPTP_PTPMCRTCU_MRTT_MASK                0x30000
#  define R_GPTP_PTPMCRTCU_MRTT_00                        (0 << R_GPTP_PTPMCRTCU_MRTT_SHIFT)  /* When timer match, time recovery pin is set to 1 */
#  define R_GPTP_PTPMCRTCU_MRTT_01                        (1 << R_GPTP_PTPMCRTCU_MRTT_SHIFT)  /* When timer match, time recovery pin is set to 0 */
#  define R_GPTP_PTPMCRTCU_MRTT_10                        (2 << R_GPTP_PTPMCRTCU_MRTT_SHIFT)  /* When timer match, time recovery pin is inverted */
#  define R_GPTP_PTPMCRTCU_MRTT_11                        (3 << R_GPTP_PTPMCRTCU_MRTT_SHIFT)  /* When timer match, a positive pulse of length PTPMCRCm.MRPL is output on time recovery pin */

#define R_GPTP_PTPMCRTCU_MCRN_SHIFT               (18)  /* Media Clock Recovery Number */
#define R_GPTP_PTPMCRTCU_MCRN_MASK                0x1c0000

#define R_GPTP_PTPMCRTCU_MRBCR                    (1 << 31)  /* Media Clock Recovery Buffer Clear Request */

/* PTPMCPC Register bit definitions */
#define R_GPTP_PTPMCPC_PE                         (1 << 0)  /* Pin Enable */

#define R_GPTP_PTPMCPC_MRS                        (1 << 1)  /* Media Clock Recovery Select */

/* PTPCCC Register bit definitions */
#define R_GPTP_PTPCCC_CCTNS                       (1 << 0)  /* Cyclic Compare Timer Number Select */

#define R_GPTP_PTPCCC_CCOPS                       (1 << 4)  /* Cyclic Compare Output Pin Select */

/* PTPCCC Register bit definitions */
#define R_GPTP_PTPCCC_CCV_SHIFT                   (0)  /* Cycle Compare Value */
#define R_GPTP_PTPCCC_CCV_MASK                    0xffffffff

/* PTPIS0 Register bit definitions */
#define R_GPTP_PTPIS0_MCCS1_TO_MCCS0_SHIFT        (0)  /* Media Clock n Capture Status Flag (n = 0, 1) */
#define R_GPTP_PTPIS0_MCCS1_TO_MCCS0_MASK         0x3

#define R_GPTP_PTPIS0_MCCOES1_TO_MCCOES0_SHIFT    (16)  /* Media Clock n Capture Overflow Error Status Flag (n = 0, 1) */
#define R_GPTP_PTPIS0_MCCOES1_TO_MCCOES0_MASK     0x30000

#define R_GPTP_PTPIS0_MCCS_SHIFT                  (0)  /* Media Clock Capture Status */
#define R_GPTP_PTPIS0_MCCS_MASK                   0x3

#define R_GPTP_PTPIS0_MCCOES_SHIFT                (16)  /* Media Clock Capture Overflow Error Status */
#define R_GPTP_PTPIS0_MCCOES_MASK                 0x30000

/* PTPIE0 Register bit definitions */
#define R_GPTP_PTPIE0_MCCE1_TO_MCCE0_SHIFT        (0)  /* Media Clock m Capture Enable (m = 0, 1) */
#define R_GPTP_PTPIE0_MCCE1_TO_MCCE0_MASK         0x3
#  define R_GPTP_PTPIE0_MCCE1_TO_MCCE0_0                  (0 << R_GPTP_PTPIE0_MCCE1_TO_MCCE0_SHIFT)  /* Interrupt m disabled */
#  define R_GPTP_PTPIE0_MCCE1_TO_MCCE0_1                  (1 << R_GPTP_PTPIE0_MCCE1_TO_MCCE0_SHIFT)  /* Interrupt m enabled */

#define R_GPTP_PTPIE0_MCCOEE1_TO_MCCOEE0_SHIFT    (16)  /* Media Clock m Capture Overflow Error Enable (m = 0, 1) */
#define R_GPTP_PTPIE0_MCCOEE1_TO_MCCOEE0_MASK     0x30000
#  define R_GPTP_PTPIE0_MCCOEE1_TO_MCCOEE0_0              (0 << R_GPTP_PTPIE0_MCCOEE1_TO_MCCOEE0_SHIFT)  /* Interrupt m disabled */
#  define R_GPTP_PTPIE0_MCCOEE1_TO_MCCOEE0_1              (1 << R_GPTP_PTPIE0_MCCOEE1_TO_MCCOEE0_SHIFT)  /* Interrupt m enabled */

#define R_GPTP_PTPIE0_MCCE_SHIFT                  (0)  /* Media Clock Capture Enable */
#define R_GPTP_PTPIE0_MCCE_MASK                   0x3

#define R_GPTP_PTPIE0_MCCOEE_SHIFT                (16)  /* Media Clock Capture Overflow Error Enable */
#define R_GPTP_PTPIE0_MCCOEE_MASK                 0x30000

/* PTPID0 Register bit definitions */
#define R_GPTP_PTPID0_MCCD1_TO_MCCD0_SHIFT        (0)  /* Media Clock m Capture Disable (m = 0, 1) */
#define R_GPTP_PTPID0_MCCD1_TO_MCCD0_MASK         0x3

#define R_GPTP_PTPID0_MCCOED1_TO_MCCOED0_SHIFT    (16)  /* Media Clock m Capture Overflow Error Disable (m = 0, 1) */
#define R_GPTP_PTPID0_MCCOED1_TO_MCCOED0_MASK     0x30000

#define R_GPTP_PTPID0_MCCD_SHIFT                  (0)  /* Media Clock Capture Disable */
#define R_GPTP_PTPID0_MCCD_MASK                   0x3

#define R_GPTP_PTPID0_MCCOED_SHIFT                (16)  /* Media Clock Capture Overflow Error Disable */
#define R_GPTP_PTPID0_MCCOED_MASK                 0x30000

/* PTPIS1 Register bit definitions */
#define R_GPTP_PTPIS1_MCRMS1_TO_MCRMS0_SHIFT      (0)  /* Media Clock m Recovery Match Status Flag (m = 0, 1) */
#define R_GPTP_PTPIS1_MCRMS1_TO_MCRMS0_MASK       0x3

#define R_GPTP_PTPIS1_MCRMS_SHIFT                 (0)  /* Media Clock Recovery Match Status */
#define R_GPTP_PTPIS1_MCRMS_MASK                  0x3

/* PTPIE1 Register bit definitions */
#define R_GPTP_PTPIE1_MCRME1_TO_MCRME0_SHIFT      (0)  /* Media Clock m Recovery Match Enable (m = 0, 1) */
#define R_GPTP_PTPIE1_MCRME1_TO_MCRME0_MASK       0x3
#  define R_GPTP_PTPIE1_MCRME1_TO_MCRME0_0                (0 << R_GPTP_PTPIE1_MCRME1_TO_MCRME0_SHIFT)  /* Interrupt m disabled */
#  define R_GPTP_PTPIE1_MCRME1_TO_MCRME0_1                (1 << R_GPTP_PTPIE1_MCRME1_TO_MCRME0_SHIFT)  /* Interrupt m enabled */

#define R_GPTP_PTPIE1_MCRME_SHIFT                 (0)  /* Media Clock Recovery Match Enable */
#define R_GPTP_PTPIE1_MCRME_MASK                  0x3

/* PTPID1 Register bit definitions */
#define R_GPTP_PTPID1_MCRMD1_TO_MCRMD0_SHIFT      (0)  /* Media Clock m Recovery Match Disable (m = 0, 1) */
#define R_GPTP_PTPID1_MCRMD1_TO_MCRMD0_MASK       0x3

#define R_GPTP_PTPID1_MCRMD_SHIFT                 (0)  /* Media Clock Recovery Match Disable */
#define R_GPTP_PTPID1_MCRMD_MASK                  0x3

/* POTCFGR Register bit definitions */
#define R_GPTP_POTCFGR_REFSEL                     (1 << 0)  /* Reference Timer Select */

/* POTCR Register bit definitions */
#define R_GPTP_POTCR_START                        (1 << 0)  /* Pulse Output Enable */


/* Maximum number of channels */

#define GPTP_MAX_CHANNELS    8

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPTP_H */

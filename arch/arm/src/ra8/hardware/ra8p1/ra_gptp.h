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

/* Channel stride for multi-channel peripherals */
#define R_GPTP_CH_STRIDE    0x00000040
#define R_GPTP_CH_BASE(ch)   (R_GPTP_BASE + ((uint32_t)(ch) * R_GPTP_CH_STRIDE))

/* GPTP Register Offsets */

#define R_GPTP_PTPIPV_OFFSET     0x00000000  /* IP Version Register */
#define R_GPTP_PTPTMEC_OFFSET     0x00000010  /* Timer Enable Configuration Register */
#define R_GPTP_PTPTMDC_OFFSET     0x00000014  /* Timer Disable Configuration Register */
/* PTPTIVC%s Registers (0-1) */
#define R_GPTP_PTPTIVC0_OFFSET     0x00000020  /* Timer 0 Increment Value Configuration Register */
#define R_GPTP_PTPTIVC1_OFFSET     0x00000060  /* Timer 1 Increment Value Configuration Register */
/* PTPTOVC%sL Registers (0-1) */
#define R_GPTP_PTPTOVC0L_OFFSET     0x00000030  /* Timer 0 Offset Value Configuration Register L */
#define R_GPTP_PTPTOVC1L_OFFSET     0x00000070  /* Timer 1 Offset Value Configuration Register L */
/* PTPTOVCM%s Registers (0-1) */
#define R_GPTP_PTPTOVCM0_OFFSET     0x00000034  /* Timer 0 Offset Value Configuration Register M */
#define R_GPTP_PTPTOVCM1_OFFSET     0x00000074  /* Timer 1 Offset Value Configuration Register M */
/* PTPTOVC%sU Registers (0-1) */
#define R_GPTP_PTPTOVC0U_OFFSET     0x00000038  /* Timer 0 Offset Value Configuration Register U */
#define R_GPTP_PTPTOVC1U_OFFSET     0x00000078  /* Timer 1 Offset Value Configuration Register U */
/* PTPAVTPTM%sL Registers (0-1) */
#define R_GPTP_PTPAVTPTM0L_OFFSET     0x00000040  /* AVTP Timer 0 Monitoring Register L */
#define R_GPTP_PTPAVTPTM1L_OFFSET     0x00000080  /* AVTP Timer 1 Monitoring Register L */
/* PTPAVTPTM%sU Registers (0-1) */
#define R_GPTP_PTPAVTPTM0U_OFFSET     0x00000044  /* AVTP Timer 0 Monitoring Register U */
#define R_GPTP_PTPAVTPTM1U_OFFSET     0x00000084  /* AVTP Timer 1 Monitoring Register U */
/* PTPGPTPTM%sL Registers (0-1) */
#define R_GPTP_PTPGPTPTM0L_OFFSET     0x00000050  /* GPTP Timer 0 Monitoring Register L */
#define R_GPTP_PTPGPTPTM1L_OFFSET     0x00000090  /* GPTP Timer 1 Monitoring Register L */
/* PTPGPTPTM%sM Registers (0-1) */
#define R_GPTP_PTPGPTPTM0M_OFFSET     0x00000054  /* GPTP Timer 0 Monitoring Register M */
#define R_GPTP_PTPGPTPTM1M_OFFSET     0x00000094  /* GPTP Timer 1 Monitoring Register M */
/* PTPGPTPTM%sU Registers (0-1) */
#define R_GPTP_PTPGPTPTM0U_OFFSET     0x00000058  /* GPTP Timer 0 Monitoring Register U */
#define R_GPTP_PTPGPTPTM1U_OFFSET     0x00000098  /* GPTP Timer 1 Monitoring Register U */
/* PTPMCCC%s Registers (0-1) */
#define R_GPTP_PTPMCCC0_OFFSET     0x00000200  /* Media Clock 0 Capture Configuration Register */
#define R_GPTP_PTPMCCC1_OFFSET     0x00000210  /* Media Clock 1 Capture Configuration Register */
/* PTPMCCM%sL Registers (0-1) */
#define R_GPTP_PTPMCCM0L_OFFSET     0x00000204  /* Media Clock 0 Capture Monitoring Register L */
#define R_GPTP_PTPMCCM1L_OFFSET     0x00000214  /* Media Clock 1 Capture Monitoring Register L */
/* PTPMCCM%sM Registers (0-1) */
#define R_GPTP_PTPMCCM0M_OFFSET     0x00000208  /* Media Clock 0 Capture Monitoring Register M */
#define R_GPTP_PTPMCCM1M_OFFSET     0x00000218  /* Media Clock 1 Capture Monitoring Register M */
/* PTPMCCM%sU Registers (0-1) */
#define R_GPTP_PTPMCCM0U_OFFSET     0x0000020c  /* Media Clock 0 Capture Monitoring Register U */
#define R_GPTP_PTPMCCM1U_OFFSET     0x0000021c  /* Media Clock 1 Capture Monitoring Register U */
/* PTPMCRC%s Registers (0-1) */
#define R_GPTP_PTPMCRC0_OFFSET     0x00000300  /* Media Clock 0 Recovery Configuration Register */
#define R_GPTP_PTPMCRC1_OFFSET     0x00000310  /* Media Clock 1 Recovery Configuration Register */
/* PTPMCRTC%sL Registers (0-1) */
#define R_GPTP_PTPMCRTC0L_OFFSET     0x00000304  /* Media Clock 0 Recovery Time Configuration Register L */
#define R_GPTP_PTPMCRTC1L_OFFSET     0x00000314  /* Media Clock 1 Recovery Time Configuration Register L */
/* PTPMCRTC%sM Registers (0-1) */
#define R_GPTP_PTPMCRTC0M_OFFSET     0x00000308  /* Media Clock 0 Recovery Time Configuration Register M */
#define R_GPTP_PTPMCRTC1M_OFFSET     0x00000318  /* Media Clock 1 Recovery Time Configuration Register M */
/* PTPMCRTC%sU Registers (0-1) */
#define R_GPTP_PTPMCRTC0U_OFFSET     0x0000030c  /* Media Clock 0 Recovery Time Configuration Register U */
#define R_GPTP_PTPMCRTC1U_OFFSET     0x0000031c  /* Media Clock 1 Recovery Time Configuration Register U */
/* PTPMCPC%s Registers (0-1) */
#define R_GPTP_PTPMCPC0_OFFSET     0x00000400  /* Media Clock 0 Pin Configuration Register */
#define R_GPTP_PTPMCPC1_OFFSET     0x00000404  /* Media Clock 1 Pin Configuration Register */
/* PTPCCC%s0 Registers (0-7) */
#define R_GPTP_PTPCCC00_OFFSET     0x00000500  /* Cyclic Compare 0 Configuration Register 0 (c = 0 to 7) */
#define R_GPTP_PTPCCC10_OFFSET     0x00000508  /* Cyclic Compare 1 Configuration Register 0 (c = 0 to 7) */
#define R_GPTP_PTPCCC20_OFFSET     0x00000510  /* Cyclic Compare 2 Configuration Register 0 (c = 0 to 7) */
#define R_GPTP_PTPCCC30_OFFSET     0x00000518  /* Cyclic Compare 3 Configuration Register 0 (c = 0 to 7) */
#define R_GPTP_PTPCCC40_OFFSET     0x00000520  /* Cyclic Compare 4 Configuration Register 0 (c = 0 to 7) */
#define R_GPTP_PTPCCC50_OFFSET     0x00000528  /* Cyclic Compare 5 Configuration Register 0 (c = 0 to 7) */
#define R_GPTP_PTPCCC60_OFFSET     0x00000530  /* Cyclic Compare 6 Configuration Register 0 (c = 0 to 7) */
#define R_GPTP_PTPCCC70_OFFSET     0x00000538  /* Cyclic Compare 7 Configuration Register 0 (c = 0 to 7) */
/* PTPCCC%s1 Registers (0-7) */
#define R_GPTP_PTPCCC01_OFFSET     0x00000504  /* Cyclic Compare 0 Configuration Register 1 (c = 0 to 7) */
#define R_GPTP_PTPCCC11_OFFSET     0x0000050c  /* Cyclic Compare 1 Configuration Register 1 (c = 0 to 7) */
#define R_GPTP_PTPCCC21_OFFSET     0x00000514  /* Cyclic Compare 2 Configuration Register 1 (c = 0 to 7) */
#define R_GPTP_PTPCCC31_OFFSET     0x0000051c  /* Cyclic Compare 3 Configuration Register 1 (c = 0 to 7) */
#define R_GPTP_PTPCCC41_OFFSET     0x00000524  /* Cyclic Compare 4 Configuration Register 1 (c = 0 to 7) */
#define R_GPTP_PTPCCC51_OFFSET     0x0000052c  /* Cyclic Compare 5 Configuration Register 1 (c = 0 to 7) */
#define R_GPTP_PTPCCC61_OFFSET     0x00000534  /* Cyclic Compare 6 Configuration Register 1 (c = 0 to 7) */
#define R_GPTP_PTPCCC71_OFFSET     0x0000053c  /* Cyclic Compare 7 Configuration Register 1 (c = 0 to 7) */
#define R_GPTP_PTPIS0_OFFSET     0x00000700  /* Interrupt Status Register 0 */
#define R_GPTP_PTPIE0_OFFSET     0x00000704  /* Interrupt Enable Register 0 */
#define R_GPTP_PTPID0_OFFSET     0x00000708  /* Interrupt Disable Register 0 */
#define R_GPTP_PTPIS1_OFFSET     0x00000710  /* Interrupt Status Register 1 */
#define R_GPTP_PTPIE1_OFFSET     0x00000714  /* Interrupt Enable Register 1 */
#define R_GPTP_PTPID1_OFFSET     0x00000718  /* Interrupt Disable Register 1 */
#define R_GPTP_POTCFGR_OFFSET     0x00001000  /* Pulse Output Timer Configuration Register */
/* POTCR%s Registers (0-3) */
#define R_GPTP_POTCR0_OFFSET     0x00001004  /* Pulse Output Timer Control Register 0 */
#define R_GPTP_POTCR1_OFFSET     0x00001034  /* Pulse Output Timer Control Register 1 */
#define R_GPTP_POTCR2_OFFSET     0x00001064  /* Pulse Output Timer Control Register 2 */
#define R_GPTP_POTCR3_OFFSET     0x00001094  /* Pulse Output Timer Control Register 3 */
/* POTSTR%sU Registers (0-3) */
#define R_GPTP_POTSTR0U_OFFSET     0x00001008  /* Pulse Output Start Time Setting Register nU */
#define R_GPTP_POTSTR1U_OFFSET     0x00001038  /* Pulse Output Start Time Setting Register nU */
#define R_GPTP_POTSTR2U_OFFSET     0x00001068  /* Pulse Output Start Time Setting Register nU */
#define R_GPTP_POTSTR3U_OFFSET     0x00001098  /* Pulse Output Start Time Setting Register nU */
/* POTSTR%sM Registers (0-3) */
#define R_GPTP_POTSTR0M_OFFSET     0x0000100c  /* Pulse Output Start Time Setting Register nM */
#define R_GPTP_POTSTR1M_OFFSET     0x0000103c  /* Pulse Output Start Time Setting Register nM */
#define R_GPTP_POTSTR2M_OFFSET     0x0000106c  /* Pulse Output Start Time Setting Register nM */
#define R_GPTP_POTSTR3M_OFFSET     0x0000109c  /* Pulse Output Start Time Setting Register nM */
/* POTSTR%sL Registers (0-3) */
#define R_GPTP_POTSTR0L_OFFSET     0x00001010  /* Pulse Output Start Time Setting Register nL */
#define R_GPTP_POTSTR1L_OFFSET     0x00001040  /* Pulse Output Start Time Setting Register nL */
#define R_GPTP_POTSTR2L_OFFSET     0x00001070  /* Pulse Output Start Time Setting Register nL */
#define R_GPTP_POTSTR3L_OFFSET     0x000010a0  /* Pulse Output Start Time Setting Register nL */
/* POTPER%sU Registers (0-3) */
#define R_GPTP_POTPER0U_OFFSET     0x00001014  /* Period Setting Register nU */
#define R_GPTP_POTPER1U_OFFSET     0x00001044  /* Period Setting Register nU */
#define R_GPTP_POTPER2U_OFFSET     0x00001074  /* Period Setting Register nU */
#define R_GPTP_POTPER3U_OFFSET     0x000010a4  /* Period Setting Register nU */
/* POTPER%sM Registers (0-3) */
#define R_GPTP_POTPER0M_OFFSET     0x00001018  /* Period Setting Register nM */
#define R_GPTP_POTPER1M_OFFSET     0x00001048  /* Period Setting Register nM */
#define R_GPTP_POTPER2M_OFFSET     0x00001078  /* Period Setting Register nM */
#define R_GPTP_POTPER3M_OFFSET     0x000010a8  /* Period Setting Register nM */
/* POTPER%sL Registers (0-3) */
#define R_GPTP_POTPER0L_OFFSET     0x0000101c  /* Period Setting Register nL */
#define R_GPTP_POTPER1L_OFFSET     0x0000104c  /* Period Setting Register nL */
#define R_GPTP_POTPER2L_OFFSET     0x0000107c  /* Period Setting Register nL */
#define R_GPTP_POTPER3L_OFFSET     0x000010ac  /* Period Setting Register nL */
/* POTPWR%s Registers (0-3) */
#define R_GPTP_POTPWR0_OFFSET     0x00001020  /* Pulse Width Setting Register 0 */
#define R_GPTP_POTPWR1_OFFSET     0x00001050  /* Pulse Width Setting Register 1 */
#define R_GPTP_POTPWR2_OFFSET     0x00001080  /* Pulse Width Setting Register 2 */
#define R_GPTP_POTPWR3_OFFSET     0x000010b0  /* Pulse Width Setting Register 3 */
/* POTCPR%sU Registers (0-3) */
#define R_GPTP_POTCPR0U_OFFSET     0x00001028  /* Time Capture Register nU */
#define R_GPTP_POTCPR1U_OFFSET     0x00001058  /* Time Capture Register nU */
#define R_GPTP_POTCPR2U_OFFSET     0x00001088  /* Time Capture Register nU */
#define R_GPTP_POTCPR3U_OFFSET     0x000010b8  /* Time Capture Register nU */
/* POTCPR%sM Registers (0-3) */
#define R_GPTP_POTCPR0M_OFFSET     0x0000102c  /* Time Capture Register nM */
#define R_GPTP_POTCPR1M_OFFSET     0x0000105c  /* Time Capture Register nM */
#define R_GPTP_POTCPR2M_OFFSET     0x0000108c  /* Time Capture Register nM */
#define R_GPTP_POTCPR3M_OFFSET     0x000010bc  /* Time Capture Register nM */
/* POTCPR%sL Registers (0-3) */
#define R_GPTP_POTCPR0L_OFFSET     0x00001030  /* Time Capture Register nL */
#define R_GPTP_POTCPR1L_OFFSET     0x00001060  /* Time Capture Register nL */
#define R_GPTP_POTCPR2L_OFFSET     0x00001090  /* Time Capture Register nL */
#define R_GPTP_POTCPR3L_OFFSET     0x000010c0  /* Time Capture Register nL */

/* GPTP Register Addresses */

#define R_GPTP_PTPIPV                 (R_GPTP_BASE + R_GPTP_PTPIPV_OFFSET)
#define R_GPTP_PTPTMEC                 (R_GPTP_BASE + R_GPTP_PTPTMEC_OFFSET)
#define R_GPTP_PTPTMDC                 (R_GPTP_BASE + R_GPTP_PTPTMDC_OFFSET)
#define R_GPTP_PTPTIVC0                 (R_GPTP_BASE + R_GPTP_PTPTIVC0_OFFSET)
#define R_GPTP_PTPTIVC1                 (R_GPTP_BASE + R_GPTP_PTPTIVC1_OFFSET)
#define R_GPTP_PTPTOVC0L                 (R_GPTP_BASE + R_GPTP_PTPTOVC0L_OFFSET)
#define R_GPTP_PTPTOVC1L                 (R_GPTP_BASE + R_GPTP_PTPTOVC1L_OFFSET)
#define R_GPTP_PTPTOVCM0                 (R_GPTP_BASE + R_GPTP_PTPTOVCM0_OFFSET)
#define R_GPTP_PTPTOVCM1                 (R_GPTP_BASE + R_GPTP_PTPTOVCM1_OFFSET)
#define R_GPTP_PTPTOVC0U                 (R_GPTP_BASE + R_GPTP_PTPTOVC0U_OFFSET)
#define R_GPTP_PTPTOVC1U                 (R_GPTP_BASE + R_GPTP_PTPTOVC1U_OFFSET)
#define R_GPTP_PTPAVTPTM0L                 (R_GPTP_BASE + R_GPTP_PTPAVTPTM0L_OFFSET)
#define R_GPTP_PTPAVTPTM1L                 (R_GPTP_BASE + R_GPTP_PTPAVTPTM1L_OFFSET)
#define R_GPTP_PTPAVTPTM0U                 (R_GPTP_BASE + R_GPTP_PTPAVTPTM0U_OFFSET)
#define R_GPTP_PTPAVTPTM1U                 (R_GPTP_BASE + R_GPTP_PTPAVTPTM1U_OFFSET)
#define R_GPTP_PTPGPTPTM0L                 (R_GPTP_BASE + R_GPTP_PTPGPTPTM0L_OFFSET)
#define R_GPTP_PTPGPTPTM1L                 (R_GPTP_BASE + R_GPTP_PTPGPTPTM1L_OFFSET)
#define R_GPTP_PTPGPTPTM0M                 (R_GPTP_BASE + R_GPTP_PTPGPTPTM0M_OFFSET)
#define R_GPTP_PTPGPTPTM1M                 (R_GPTP_BASE + R_GPTP_PTPGPTPTM1M_OFFSET)
#define R_GPTP_PTPGPTPTM0U                 (R_GPTP_BASE + R_GPTP_PTPGPTPTM0U_OFFSET)
#define R_GPTP_PTPGPTPTM1U                 (R_GPTP_BASE + R_GPTP_PTPGPTPTM1U_OFFSET)
#define R_GPTP_PTPMCCC0                 (R_GPTP_BASE + R_GPTP_PTPMCCC0_OFFSET)
#define R_GPTP_PTPMCCC1                 (R_GPTP_BASE + R_GPTP_PTPMCCC1_OFFSET)
#define R_GPTP_PTPMCCM0L                 (R_GPTP_BASE + R_GPTP_PTPMCCM0L_OFFSET)
#define R_GPTP_PTPMCCM1L                 (R_GPTP_BASE + R_GPTP_PTPMCCM1L_OFFSET)
#define R_GPTP_PTPMCCM0M                 (R_GPTP_BASE + R_GPTP_PTPMCCM0M_OFFSET)
#define R_GPTP_PTPMCCM1M                 (R_GPTP_BASE + R_GPTP_PTPMCCM1M_OFFSET)
#define R_GPTP_PTPMCCM0U                 (R_GPTP_BASE + R_GPTP_PTPMCCM0U_OFFSET)
#define R_GPTP_PTPMCCM1U                 (R_GPTP_BASE + R_GPTP_PTPMCCM1U_OFFSET)
#define R_GPTP_PTPMCRC0                 (R_GPTP_BASE + R_GPTP_PTPMCRC0_OFFSET)
#define R_GPTP_PTPMCRC1                 (R_GPTP_BASE + R_GPTP_PTPMCRC1_OFFSET)
#define R_GPTP_PTPMCRTC0L                 (R_GPTP_BASE + R_GPTP_PTPMCRTC0L_OFFSET)
#define R_GPTP_PTPMCRTC1L                 (R_GPTP_BASE + R_GPTP_PTPMCRTC1L_OFFSET)
#define R_GPTP_PTPMCRTC0M                 (R_GPTP_BASE + R_GPTP_PTPMCRTC0M_OFFSET)
#define R_GPTP_PTPMCRTC1M                 (R_GPTP_BASE + R_GPTP_PTPMCRTC1M_OFFSET)
#define R_GPTP_PTPMCRTC0U                 (R_GPTP_BASE + R_GPTP_PTPMCRTC0U_OFFSET)
#define R_GPTP_PTPMCRTC1U                 (R_GPTP_BASE + R_GPTP_PTPMCRTC1U_OFFSET)
#define R_GPTP_PTPMCPC0                 (R_GPTP_BASE + R_GPTP_PTPMCPC0_OFFSET)
#define R_GPTP_PTPMCPC1                 (R_GPTP_BASE + R_GPTP_PTPMCPC1_OFFSET)
#define R_GPTP_PTPCCC00                 (R_GPTP_BASE + R_GPTP_PTPCCC00_OFFSET)
#define R_GPTP_PTPCCC10                 (R_GPTP_BASE + R_GPTP_PTPCCC10_OFFSET)
#define R_GPTP_PTPCCC20                 (R_GPTP_BASE + R_GPTP_PTPCCC20_OFFSET)
#define R_GPTP_PTPCCC30                 (R_GPTP_BASE + R_GPTP_PTPCCC30_OFFSET)
#define R_GPTP_PTPCCC40                 (R_GPTP_BASE + R_GPTP_PTPCCC40_OFFSET)
#define R_GPTP_PTPCCC50                 (R_GPTP_BASE + R_GPTP_PTPCCC50_OFFSET)
#define R_GPTP_PTPCCC60                 (R_GPTP_BASE + R_GPTP_PTPCCC60_OFFSET)
#define R_GPTP_PTPCCC70                 (R_GPTP_BASE + R_GPTP_PTPCCC70_OFFSET)
#define R_GPTP_PTPCCC01                 (R_GPTP_BASE + R_GPTP_PTPCCC01_OFFSET)
#define R_GPTP_PTPCCC11                 (R_GPTP_BASE + R_GPTP_PTPCCC11_OFFSET)
#define R_GPTP_PTPCCC21                 (R_GPTP_BASE + R_GPTP_PTPCCC21_OFFSET)
#define R_GPTP_PTPCCC31                 (R_GPTP_BASE + R_GPTP_PTPCCC31_OFFSET)
#define R_GPTP_PTPCCC41                 (R_GPTP_BASE + R_GPTP_PTPCCC41_OFFSET)
#define R_GPTP_PTPCCC51                 (R_GPTP_BASE + R_GPTP_PTPCCC51_OFFSET)
#define R_GPTP_PTPCCC61                 (R_GPTP_BASE + R_GPTP_PTPCCC61_OFFSET)
#define R_GPTP_PTPCCC71                 (R_GPTP_BASE + R_GPTP_PTPCCC71_OFFSET)
#define R_GPTP_PTPIS0                 (R_GPTP_BASE + R_GPTP_PTPIS0_OFFSET)
#define R_GPTP_PTPIE0                 (R_GPTP_BASE + R_GPTP_PTPIE0_OFFSET)
#define R_GPTP_PTPID0                 (R_GPTP_BASE + R_GPTP_PTPID0_OFFSET)
#define R_GPTP_PTPIS1                 (R_GPTP_BASE + R_GPTP_PTPIS1_OFFSET)
#define R_GPTP_PTPIE1                 (R_GPTP_BASE + R_GPTP_PTPIE1_OFFSET)
#define R_GPTP_PTPID1                 (R_GPTP_BASE + R_GPTP_PTPID1_OFFSET)
#define R_GPTP_POTCFGR                 (R_GPTP_BASE + R_GPTP_POTCFGR_OFFSET)
#define R_GPTP_POTCR0                 (R_GPTP_BASE + R_GPTP_POTCR0_OFFSET)
#define R_GPTP_POTCR1                 (R_GPTP_BASE + R_GPTP_POTCR1_OFFSET)
#define R_GPTP_POTCR2                 (R_GPTP_BASE + R_GPTP_POTCR2_OFFSET)
#define R_GPTP_POTCR3                 (R_GPTP_BASE + R_GPTP_POTCR3_OFFSET)
#define R_GPTP_POTSTR0U                 (R_GPTP_BASE + R_GPTP_POTSTR0U_OFFSET)
#define R_GPTP_POTSTR1U                 (R_GPTP_BASE + R_GPTP_POTSTR1U_OFFSET)
#define R_GPTP_POTSTR2U                 (R_GPTP_BASE + R_GPTP_POTSTR2U_OFFSET)
#define R_GPTP_POTSTR3U                 (R_GPTP_BASE + R_GPTP_POTSTR3U_OFFSET)
#define R_GPTP_POTSTR0M                 (R_GPTP_BASE + R_GPTP_POTSTR0M_OFFSET)
#define R_GPTP_POTSTR1M                 (R_GPTP_BASE + R_GPTP_POTSTR1M_OFFSET)
#define R_GPTP_POTSTR2M                 (R_GPTP_BASE + R_GPTP_POTSTR2M_OFFSET)
#define R_GPTP_POTSTR3M                 (R_GPTP_BASE + R_GPTP_POTSTR3M_OFFSET)
#define R_GPTP_POTSTR0L                 (R_GPTP_BASE + R_GPTP_POTSTR0L_OFFSET)
#define R_GPTP_POTSTR1L                 (R_GPTP_BASE + R_GPTP_POTSTR1L_OFFSET)
#define R_GPTP_POTSTR2L                 (R_GPTP_BASE + R_GPTP_POTSTR2L_OFFSET)
#define R_GPTP_POTSTR3L                 (R_GPTP_BASE + R_GPTP_POTSTR3L_OFFSET)
#define R_GPTP_POTPER0U                 (R_GPTP_BASE + R_GPTP_POTPER0U_OFFSET)
#define R_GPTP_POTPER1U                 (R_GPTP_BASE + R_GPTP_POTPER1U_OFFSET)
#define R_GPTP_POTPER2U                 (R_GPTP_BASE + R_GPTP_POTPER2U_OFFSET)
#define R_GPTP_POTPER3U                 (R_GPTP_BASE + R_GPTP_POTPER3U_OFFSET)
#define R_GPTP_POTPER0M                 (R_GPTP_BASE + R_GPTP_POTPER0M_OFFSET)
#define R_GPTP_POTPER1M                 (R_GPTP_BASE + R_GPTP_POTPER1M_OFFSET)
#define R_GPTP_POTPER2M                 (R_GPTP_BASE + R_GPTP_POTPER2M_OFFSET)
#define R_GPTP_POTPER3M                 (R_GPTP_BASE + R_GPTP_POTPER3M_OFFSET)
#define R_GPTP_POTPER0L                 (R_GPTP_BASE + R_GPTP_POTPER0L_OFFSET)
#define R_GPTP_POTPER1L                 (R_GPTP_BASE + R_GPTP_POTPER1L_OFFSET)
#define R_GPTP_POTPER2L                 (R_GPTP_BASE + R_GPTP_POTPER2L_OFFSET)
#define R_GPTP_POTPER3L                 (R_GPTP_BASE + R_GPTP_POTPER3L_OFFSET)
#define R_GPTP_POTPWR0                 (R_GPTP_BASE + R_GPTP_POTPWR0_OFFSET)
#define R_GPTP_POTPWR1                 (R_GPTP_BASE + R_GPTP_POTPWR1_OFFSET)
#define R_GPTP_POTPWR2                 (R_GPTP_BASE + R_GPTP_POTPWR2_OFFSET)
#define R_GPTP_POTPWR3                 (R_GPTP_BASE + R_GPTP_POTPWR3_OFFSET)
#define R_GPTP_POTCPR0U                 (R_GPTP_BASE + R_GPTP_POTCPR0U_OFFSET)
#define R_GPTP_POTCPR1U                 (R_GPTP_BASE + R_GPTP_POTCPR1U_OFFSET)
#define R_GPTP_POTCPR2U                 (R_GPTP_BASE + R_GPTP_POTCPR2U_OFFSET)
#define R_GPTP_POTCPR3U                 (R_GPTP_BASE + R_GPTP_POTCPR3U_OFFSET)
#define R_GPTP_POTCPR0M                 (R_GPTP_BASE + R_GPTP_POTCPR0M_OFFSET)
#define R_GPTP_POTCPR1M                 (R_GPTP_BASE + R_GPTP_POTCPR1M_OFFSET)
#define R_GPTP_POTCPR2M                 (R_GPTP_BASE + R_GPTP_POTCPR2M_OFFSET)
#define R_GPTP_POTCPR3M                 (R_GPTP_BASE + R_GPTP_POTCPR3M_OFFSET)
#define R_GPTP_POTCPR0L                 (R_GPTP_BASE + R_GPTP_POTCPR0L_OFFSET)
#define R_GPTP_POTCPR1L                 (R_GPTP_BASE + R_GPTP_POTCPR1L_OFFSET)
#define R_GPTP_POTCPR2L                 (R_GPTP_BASE + R_GPTP_POTCPR2L_OFFSET)
#define R_GPTP_POTCPR3L                 (R_GPTP_BASE + R_GPTP_POTCPR3L_OFFSET)

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
#define R_GPTP_PTPTMDC_TD1 TO TD0_SHIFT           (0)  /* Timer n Disable (n = 0, 1) */
#define R_GPTP_PTPTMDC_TD1 TO TD0_MASK            0x3
#  define R_GPTP_PTPTMDC_TD1 TO TD0_0                     (0 << R_GPTP_PTPTMDC_TD1 TO TD0_SHIFT)  /* No effect */
#  define R_GPTP_PTPTMDC_TD1 TO TD0_1                     (1 << R_GPTP_PTPTMDC_TD1 TO TD0_SHIFT)  /* Bit q of this register clears PTPTMEC.TEq */

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
#define R_GPTP_PTPIS0_MCCS1 TO MCCS0_SHIFT        (0)  /* Media Clock n Capture Status Flag (n = 0, 1) */
#define R_GPTP_PTPIS0_MCCS1 TO MCCS0_MASK         0x3

#define R_GPTP_PTPIS0_MCCOES1 TO MCCOES0_SHIFT    (16)  /* Media Clock n Capture Overflow Error Status Flag (n = 0, 1) */
#define R_GPTP_PTPIS0_MCCOES1 TO MCCOES0_MASK     0x30000

#define R_GPTP_PTPIS0_MCCS_SHIFT                  (0)  /* Media Clock Capture Status */
#define R_GPTP_PTPIS0_MCCS_MASK                   0x3

#define R_GPTP_PTPIS0_MCCOES_SHIFT                (16)  /* Media Clock Capture Overflow Error Status */
#define R_GPTP_PTPIS0_MCCOES_MASK                 0x30000

/* PTPIE0 Register bit definitions */
#define R_GPTP_PTPIE0_MCCE1 TO MCCE0_SHIFT        (0)  /* Media Clock m Capture Enable (m = 0, 1) */
#define R_GPTP_PTPIE0_MCCE1 TO MCCE0_MASK         0x3
#  define R_GPTP_PTPIE0_MCCE1 TO MCCE0_0                  (0 << R_GPTP_PTPIE0_MCCE1 TO MCCE0_SHIFT)  /* Interrupt m disabled */
#  define R_GPTP_PTPIE0_MCCE1 TO MCCE0_1                  (1 << R_GPTP_PTPIE0_MCCE1 TO MCCE0_SHIFT)  /* Interrupt m enabled */

#define R_GPTP_PTPIE0_MCCOEE1 TO MCCOEE0_SHIFT    (16)  /* Media Clock m Capture Overflow Error Enable (m = 0, 1) */
#define R_GPTP_PTPIE0_MCCOEE1 TO MCCOEE0_MASK     0x30000
#  define R_GPTP_PTPIE0_MCCOEE1 TO MCCOEE0_0              (0 << R_GPTP_PTPIE0_MCCOEE1 TO MCCOEE0_SHIFT)  /* Interrupt m disabled */
#  define R_GPTP_PTPIE0_MCCOEE1 TO MCCOEE0_1              (1 << R_GPTP_PTPIE0_MCCOEE1 TO MCCOEE0_SHIFT)  /* Interrupt m enabled */

#define R_GPTP_PTPIE0_MCCE_SHIFT                  (0)  /* Media Clock Capture Enable */
#define R_GPTP_PTPIE0_MCCE_MASK                   0x3

#define R_GPTP_PTPIE0_MCCOEE_SHIFT                (16)  /* Media Clock Capture Overflow Error Enable */
#define R_GPTP_PTPIE0_MCCOEE_MASK                 0x30000

/* PTPID0 Register bit definitions */
#define R_GPTP_PTPID0_MCCD1 TO MCCD0_SHIFT        (0)  /* Media Clock m Capture Disable (m = 0, 1) */
#define R_GPTP_PTPID0_MCCD1 TO MCCD0_MASK         0x3

#define R_GPTP_PTPID0_MCCOED1 TO MCCOED0_SHIFT    (16)  /* Media Clock m Capture Overflow Error Disable (m = 0, 1) */
#define R_GPTP_PTPID0_MCCOED1 TO MCCOED0_MASK     0x30000

#define R_GPTP_PTPID0_MCCD_SHIFT                  (0)  /* Media Clock Capture Disable */
#define R_GPTP_PTPID0_MCCD_MASK                   0x3

#define R_GPTP_PTPID0_MCCOED_SHIFT                (16)  /* Media Clock Capture Overflow Error Disable */
#define R_GPTP_PTPID0_MCCOED_MASK                 0x30000

/* PTPIS1 Register bit definitions */
#define R_GPTP_PTPIS1_MCRMS1 TO MCRMS0_SHIFT      (0)  /* Media Clock m Recovery Match Status Flag (m = 0, 1) */
#define R_GPTP_PTPIS1_MCRMS1 TO MCRMS0_MASK       0x3

#define R_GPTP_PTPIS1_MCRMS_SHIFT                 (0)  /* Media Clock Recovery Match Status */
#define R_GPTP_PTPIS1_MCRMS_MASK                  0x3

/* PTPIE1 Register bit definitions */
#define R_GPTP_PTPIE1_MCRME1 TO MCRME0_SHIFT      (0)  /* Media Clock m Recovery Match Enable (m = 0, 1) */
#define R_GPTP_PTPIE1_MCRME1 TO MCRME0_MASK       0x3
#  define R_GPTP_PTPIE1_MCRME1 TO MCRME0_0                (0 << R_GPTP_PTPIE1_MCRME1 TO MCRME0_SHIFT)  /* Interrupt m disabled */
#  define R_GPTP_PTPIE1_MCRME1 TO MCRME0_1                (1 << R_GPTP_PTPIE1_MCRME1 TO MCRME0_SHIFT)  /* Interrupt m enabled */

#define R_GPTP_PTPIE1_MCRME_SHIFT                 (0)  /* Media Clock Recovery Match Enable */
#define R_GPTP_PTPIE1_MCRME_MASK                  0x3

/* PTPID1 Register bit definitions */
#define R_GPTP_PTPID1_MCRMD1 TO MCRMD0_SHIFT      (0)  /* Media Clock m Recovery Match Disable (m = 0, 1) */
#define R_GPTP_PTPID1_MCRMD1 TO MCRMD0_MASK       0x3

#define R_GPTP_PTPID1_MCRMD_SHIFT                 (0)  /* Media Clock Recovery Match Disable */
#define R_GPTP_PTPID1_MCRMD_MASK                  0x3

/* POTCFGR Register bit definitions */
#define R_GPTP_POTCFGR_REFSEL                     (1 << 0)  /* Reference Timer Select */

/* POTCR Register bit definitions */
#define R_GPTP_POTCR_START                        (1 << 0)  /* Pulse Output Enable */


/* Maximum number of channels */

#define GPTP_MAX_CHANNELS    8

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPTP_H */

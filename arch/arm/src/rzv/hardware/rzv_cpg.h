/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_cpg.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_CPG_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_CPG_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CPG Base Addresses ****************************************************/

#ifndef RZV_CPG0_BASE
#  define RZV_CPG0_BASE               0x10420010
#endif
#ifndef RZV_CPG_BASE
#  define RZV_CPG_BASE                RZV_CPG0_BASE
#endif

/* CPG Register Offsets ***************************************************/

/* CDDIV%s Registers (0-4) */
#define RZV_CPG_CDDIV_OFFSET(m)                 (0x000003f0 + ((m) * 0x00000004))  /* CDDIV Register %s */
/* CLKMON%s Registers (0-10) */
#define RZV_CPG_CLKMON_OFFSET(m)                (0x000007f0 + ((m) * 0x00000004))  /* CLKMON Register %s */
/* CLKON%s Registers (0-24) */
#define RZV_CPG_CLKON_OFFSET(m)                 (0x000005f0 + ((m) * 0x00000004))  /* CLKON Register %s */
/* CSDIV%s Registers (0-1) */
#define RZV_CPG_CSDIV_OFFSET(m)                 (0x000004f0 + ((m) * 0x00000004))  /* CSDIV Register %s */
/* ERRORRST_SEL%s Registers (1-8) */
#define RZV_CPG_ERRORRST_SEL_OFFSET(m)          (0x00000af0 + ((m) * 0x00000004))  /* ERRORRST_SEL Register %s */
/* ERROR_RST%s Registers (2-8) */
#define RZV_CPG_ERROR_RST_OFFSET(m)             (0x00000b30 + ((m) * 0x00000004))  /* ERROR_RST Register %s */
/* LP_CST_CTL%s Registers (2-3) */
#define RZV_CPG_LP_CST_CTL_OFFSET(m)            (0x00000c60 + ((m) * 0x00000004))  /* LP_CST_CTL Register %s */
/* LP_CTL%s Registers (1-2) */
#define RZV_CPG_LP_CTL_OFFSET(m)                (0x00000bf0 + ((m) * 0x00000004))  /* LP_CTL Register %s */
/* LP_PWC_CTL%s Registers (1-2) */
#define RZV_CPG_LP_PWC_CTL_OFFSET(m)            (0x00000c68 + ((m) * 0x00000004))  /* LP_PWC_CTL Register %s */
/* LP_SRAM_STBY_CTL%s Registers (1-3) */
#define RZV_CPG_LP_SRAM_STBY_CTL_OFFSET(m)      (0x00000c40 + ((m) * 0x00000004))  /* LP_SRAM_STBY_CTL Register %s */
/* PLLDRP_CLK%s Registers (1-2) */
#define RZV_CPG_PLLDRP_CLK_OFFSET(m)            (0x00000134 + ((m) * 0x00000004))  /* PLLDRP_CLK Register %s */
/* PLLDSI_CLK%s Registers (1-2) */
#define RZV_CPG_PLLDSI_CLK_OFFSET(m)            (0x000000b4 + ((m) * 0x00000004))  /* PLLDSI_CLK Register %s */
/* PLLGPU_CLK%s Registers (1-2) */
#define RZV_CPG_PLLGPU_CLK_OFFSET(m)            (0x00000114 + ((m) * 0x00000004))  /* PLLGPU_CLK Register %s */
/* RST%s Registers (0-17) */
#define RZV_CPG_RST_OFFSET(m)                   (0x000008f0 + ((m) * 0x00000004))  /* RST Register %s */
/* RSTMON%s Registers (0-8) */
#define RZV_CPG_RSTMON_OFFSET(m)                (0x000009f0 + ((m) * 0x00000004))  /* RSTMON Register %s */
/* SSEL%s Registers (0-2) */
#define RZV_CPG_SSEL_OFFSET(m)                  (0x000002f0 + ((m) * 0x00000004))  /* SSEL Register %s */
#define RZV_CPG_PLLCM33_MON_OFFSET                       0x0000  /* PLLCM33_MON */
#define RZV_CPG_PLLCLN_STBY_OFFSET                       0x0010  /* PLLCLN_STBY */
#define RZV_CPG_PLLCLN_MON_OFFSET                        0x0020  /* PLLCLN_MON */
#define RZV_CPG_PLLDTY_STBY_OFFSET                       0x0030  /* PLLDTY_STBY */
#define RZV_CPG_PLLDTY_MON_OFFSET                        0x0040  /* PLLDTY_MON */
#define RZV_CPG_PLLCA55_STBY_OFFSET                      0x0050  /* PLLCA55_STBY */
#define RZV_CPG_PLLCA55_CLK1_OFFSET                      0x0054  /* PLLCA55_CLK1 */
#define RZV_CPG_PLLCA55_CLK2_OFFSET                      0x0058  /* PLLCA55_CLK2 */
#define RZV_CPG_PLLCA55_MON_OFFSET                       0x0060  /* PLLCA55_MON */
#define RZV_CPG_PLLVDO_STBY_OFFSET                       0x0070  /* PLLVDO_STBY */
#define RZV_CPG_PLLVDO_MON_OFFSET                        0x0080  /* PLLVDO_MON */
#define RZV_CPG_PLLETH_STBY_OFFSET                       0x0090  /* PLLETH_STBY */
#define RZV_CPG_PLLETH_MON_OFFSET                        0x00A0  /* PLLETH_MON */
#define RZV_CPG_PLLDSI_STBY_OFFSET                       0x00B0  /* PLLDSI_STBY */
#define RZV_CPG_PLLDSI_MON_OFFSET                        0x00C0  /* PLLDSI_MON */
#define RZV_CPG_PLLDDR0_STBY_OFFSET                      0x00D0  /* PLLDDR0_STBY */
#define RZV_CPG_PLLDDR0_MON_OFFSET                       0x00E0  /* PLLDDR0_MON */
#define RZV_CPG_PLLDDR1_STBY_OFFSET                      0x00F0  /* PLLDDR1_STBY */
#define RZV_CPG_PLLDDR1_MON_OFFSET                       0x0100  /* PLLDDR1_MON */
#define RZV_CPG_PLLGPU_STBY_OFFSET                       0x0110  /* PLLGPU_STBY */
#define RZV_CPG_PLLGPU_MON_OFFSET                        0x0120  /* PLLGPU_MON */
#define RZV_CPG_PLLDRP_STBY_OFFSET                       0x0130  /* PLLDRP_STBY */
#define RZV_CPG_PLLDRP_MON_OFFSET                        0x0140  /* PLLDRP_MON */
#define RZV_CPG_CLMA0_CTL_OFFSET                         0x01F0  /* CLMA0_CTL */
#define RZV_CPG_CLMA1_CTL_OFFSET                         0x01F4  /* CLMA1_CTL */
#define RZV_CPG_CLMA2_CTL_OFFSET                         0x01F8  /* CLMA2_CTL */
#define RZV_CPG_CLMA3_CTL_OFFSET                         0x01FC  /* CLMA3_CTL */
#define RZV_CPG_CLMA4_CTL_OFFSET                         0x0200  /* CLMA4_CTL */
#define RZV_CPG_CLMA5_CTL_OFFSET                         0x0204  /* CLMA5_CTL */
#define RZV_CPG_CLMA6_CTL_OFFSET                         0x0208  /* CLMA6_CTL */
#define RZV_CPG_CLMA7_CTL_OFFSET                         0x020C  /* CLMA7_CTL */
#define RZV_CPG_CLMA8_CTL_OFFSET                         0x0210  /* CLMA8_CTL */
#define RZV_CPG_CLMA9_CTL_OFFSET                         0x0214  /* CLMA9_CTL */
#define RZV_CPG_CLMA10_CTL_OFFSET                        0x0218  /* CLMA10_CTL */
#define RZV_CPG_CLMA11_CTL_OFFSET                        0x021C  /* CLMA11_CTL */
#define RZV_CPG_CLMA12_CTL_OFFSET                        0x0220  /* CLMA12_CTL */
#define RZV_CPG_CLMA13_CTL_OFFSET                        0x0224  /* CLMA13_CTL */
#define RZV_CPG_CLMA14_CTL_OFFSET                        0x0228  /* CLMA14_CTL */
#define RZV_CPG_CLMA_MON_OFFSET                          0x0270  /* CLMA_MON */
#define RZV_CPG_CLKSTATUS0_OFFSET                        0x06F0  /* CPG_CLKSTATUS0 */
#define RZV_CPG_LP_GPU_CTL_OFFSET                        0x0BF8  /* LP_GPU_CTL */
#define RZV_CPG_CM33_CTL_OFFSET                          0x0BFC  /* CM33_CTL */
#define RZV_CPG_CR8_CORESTATUS_OFFSET                    0x0C00  /* CR8_CORESTATUS */
#define RZV_CPG_CR8_CONFIG1_OFFSET                       0x0C04  /* CR8_CONFIG1 */
#define RZV_CPG_LP_CM33CTL0_OFFSET                       0x0C08  /* LP_CM33CTL0 */
#define RZV_CPG_LP_CM33CTL1_OFFSET                       0x0C0C  /* LP_CM33CTL1 */
#define RZV_CPG_LP_CA55_CTL1_OFFSET                      0x0C10  /* LP_CA55_CTL1 */
#define RZV_CPG_LP_CA55_CTL2_OFFSET                      0x0C14  /* LP_CA55_CTL2 */
#define RZV_CPG_LP_CA55_CTL3_OFFSET                      0x0C18  /* LP_CA55_CTL3 */
#define RZV_CPG_LP_CA55_CTL6_OFFSET                      0x0C24  /* LP_CA55_CTL6 */
#define RZV_CPG_LP_CA55_CTL7_OFFSET                      0x0C28  /* LP_CA55_CTL7 */
#define RZV_CPG_LP_CR8_CTL3_OFFSET                       0x0C34  /* LP_CR8_CTL3 */
#define RZV_CPG_LP_CR8_CTL4_OFFSET                       0x0C38  /* LP_CR8_CTL4 */
#define RZV_CPG_LP_PMU_CTL1_OFFSET                       0x0C3C  /* LP_PMU_CTL1 */
#define RZV_CPG_OTP_HANDSHAKE_MON_OFFSET                 0x0C78  /* OTP_HANDSHAKE_MON */
#define RZV_CPG_OTHERS_INI_OFFSET                        0x0C7C  /* OTHERS_INI */
#define RZV_CPG_BUS_1_MSTOP_OFFSET                       0x0CF0  /* BUS_1_MSTOP */
#define RZV_CPG_BUS_2_MSTOP_OFFSET                       0x0CF4  /* BUS_2_MSTOP */
#define RZV_CPG_BUS_3_MSTOP_OFFSET                       0x0CF8  /* BUS_3_MSTOP */
#define RZV_CPG_BUS_4_MSTOP_OFFSET                       0x0CFC  /* BUS_4_MSTOP */
#define RZV_CPG_BUS_5_MSTOP_OFFSET                       0x0D00  /* BUS_5_MSTOP */
#define RZV_CPG_BUS_6_MSTOP_OFFSET                       0x0D04  /* BUS_6_MSTOP */
#define RZV_CPG_BUS_7_MSTOP_OFFSET                       0x0D08  /* BUS_7_MSTOP */
#define RZV_CPG_BUS_8_MSTOP_OFFSET                       0x0D0C  /* BUS_8_MSTOP */
#define RZV_CPG_BUS_9_MSTOP_OFFSET                       0x0D10  /* BUS_9_MSTOP */
#define RZV_CPG_BUS_10_MSTOP_OFFSET                      0x0D14  /* BUS_10_MSTOP */
#define RZV_CPG_BUS_11_MSTOP_OFFSET                      0x0D18  /* BUS_11_MSTOP */
#define RZV_CPG_BUS_12_MSTOP_OFFSET                      0x0D1C  /* BUS_12_MSTOP */

/* CPG Register Addresses **************************************************/

#define RZV_CPG_CDDIV(m)                        (RZV_CPG_BASE + RZV_CPG_CDDIV_OFFSET(m))
#define RZV_CPG_CLKMON(m)                       (RZV_CPG_BASE + RZV_CPG_CLKMON_OFFSET(m))
#define RZV_CPG_CLKON(m)                        (RZV_CPG_BASE + RZV_CPG_CLKON_OFFSET(m))
#define RZV_CPG_CSDIV(m)                        (RZV_CPG_BASE + RZV_CPG_CSDIV_OFFSET(m))
#define RZV_CPG_ERRORRST_SEL(m)                 (RZV_CPG_BASE + RZV_CPG_ERRORRST_SEL_OFFSET(m))
#define RZV_CPG_ERROR_RST(m)                    (RZV_CPG_BASE + RZV_CPG_ERROR_RST_OFFSET(m))
#define RZV_CPG_LP_CST_CTL(m)                   (RZV_CPG_BASE + RZV_CPG_LP_CST_CTL_OFFSET(m))
#define RZV_CPG_LP_CTL(m)                       (RZV_CPG_BASE + RZV_CPG_LP_CTL_OFFSET(m))
#define RZV_CPG_LP_PWC_CTL(m)                   (RZV_CPG_BASE + RZV_CPG_LP_PWC_CTL_OFFSET(m))
#define RZV_CPG_LP_SRAM_STBY_CTL(m)             (RZV_CPG_BASE + RZV_CPG_LP_SRAM_STBY_CTL_OFFSET(m))
#define RZV_CPG_PLLDRP_CLK(m)                   (RZV_CPG_BASE + RZV_CPG_PLLDRP_CLK_OFFSET(m))
#define RZV_CPG_PLLDSI_CLK(m)                   (RZV_CPG_BASE + RZV_CPG_PLLDSI_CLK_OFFSET(m))
#define RZV_CPG_PLLGPU_CLK(m)                   (RZV_CPG_BASE + RZV_CPG_PLLGPU_CLK_OFFSET(m))
#define RZV_CPG_RST(m)                          (RZV_CPG_BASE + RZV_CPG_RST_OFFSET(m))
#define RZV_CPG_RSTMON(m)                       (RZV_CPG_BASE + RZV_CPG_RSTMON_OFFSET(m))
#define RZV_CPG_SSEL(m)                         (RZV_CPG_BASE + RZV_CPG_SSEL_OFFSET(m))
#define RZV_CPG_PLLCM33_MON                          (RZV_CPG_BASE + RZV_CPG_PLLCM33_MON_OFFSET)
#define RZV_CPG_PLLCLN_STBY                          (RZV_CPG_BASE + RZV_CPG_PLLCLN_STBY_OFFSET)
#define RZV_CPG_PLLCLN_MON                           (RZV_CPG_BASE + RZV_CPG_PLLCLN_MON_OFFSET)
#define RZV_CPG_PLLDTY_STBY                          (RZV_CPG_BASE + RZV_CPG_PLLDTY_STBY_OFFSET)
#define RZV_CPG_PLLDTY_MON                           (RZV_CPG_BASE + RZV_CPG_PLLDTY_MON_OFFSET)
#define RZV_CPG_PLLCA55_STBY                         (RZV_CPG_BASE + RZV_CPG_PLLCA55_STBY_OFFSET)
#define RZV_CPG_PLLCA55_CLK1                         (RZV_CPG_BASE + RZV_CPG_PLLCA55_CLK1_OFFSET)
#define RZV_CPG_PLLCA55_CLK2                         (RZV_CPG_BASE + RZV_CPG_PLLCA55_CLK2_OFFSET)
#define RZV_CPG_PLLCA55_MON                          (RZV_CPG_BASE + RZV_CPG_PLLCA55_MON_OFFSET)
#define RZV_CPG_PLLVDO_STBY                          (RZV_CPG_BASE + RZV_CPG_PLLVDO_STBY_OFFSET)
#define RZV_CPG_PLLVDO_MON                           (RZV_CPG_BASE + RZV_CPG_PLLVDO_MON_OFFSET)
#define RZV_CPG_PLLETH_STBY                          (RZV_CPG_BASE + RZV_CPG_PLLETH_STBY_OFFSET)
#define RZV_CPG_PLLETH_MON                           (RZV_CPG_BASE + RZV_CPG_PLLETH_MON_OFFSET)
#define RZV_CPG_PLLDSI_STBY                          (RZV_CPG_BASE + RZV_CPG_PLLDSI_STBY_OFFSET)
#define RZV_CPG_PLLDSI_MON                           (RZV_CPG_BASE + RZV_CPG_PLLDSI_MON_OFFSET)
#define RZV_CPG_PLLDDR0_STBY                         (RZV_CPG_BASE + RZV_CPG_PLLDDR0_STBY_OFFSET)
#define RZV_CPG_PLLDDR0_MON                          (RZV_CPG_BASE + RZV_CPG_PLLDDR0_MON_OFFSET)
#define RZV_CPG_PLLDDR1_STBY                         (RZV_CPG_BASE + RZV_CPG_PLLDDR1_STBY_OFFSET)
#define RZV_CPG_PLLDDR1_MON                          (RZV_CPG_BASE + RZV_CPG_PLLDDR1_MON_OFFSET)
#define RZV_CPG_PLLGPU_STBY                          (RZV_CPG_BASE + RZV_CPG_PLLGPU_STBY_OFFSET)
#define RZV_CPG_PLLGPU_MON                           (RZV_CPG_BASE + RZV_CPG_PLLGPU_MON_OFFSET)
#define RZV_CPG_PLLDRP_STBY                          (RZV_CPG_BASE + RZV_CPG_PLLDRP_STBY_OFFSET)
#define RZV_CPG_PLLDRP_MON                           (RZV_CPG_BASE + RZV_CPG_PLLDRP_MON_OFFSET)
#define RZV_CPG_CLMA0_CTL                            (RZV_CPG_BASE + RZV_CPG_CLMA0_CTL_OFFSET)
#define RZV_CPG_CLMA1_CTL                            (RZV_CPG_BASE + RZV_CPG_CLMA1_CTL_OFFSET)
#define RZV_CPG_CLMA2_CTL                            (RZV_CPG_BASE + RZV_CPG_CLMA2_CTL_OFFSET)
#define RZV_CPG_CLMA3_CTL                            (RZV_CPG_BASE + RZV_CPG_CLMA3_CTL_OFFSET)
#define RZV_CPG_CLMA4_CTL                            (RZV_CPG_BASE + RZV_CPG_CLMA4_CTL_OFFSET)
#define RZV_CPG_CLMA5_CTL                            (RZV_CPG_BASE + RZV_CPG_CLMA5_CTL_OFFSET)
#define RZV_CPG_CLMA6_CTL                            (RZV_CPG_BASE + RZV_CPG_CLMA6_CTL_OFFSET)
#define RZV_CPG_CLMA7_CTL                            (RZV_CPG_BASE + RZV_CPG_CLMA7_CTL_OFFSET)
#define RZV_CPG_CLMA8_CTL                            (RZV_CPG_BASE + RZV_CPG_CLMA8_CTL_OFFSET)
#define RZV_CPG_CLMA9_CTL                            (RZV_CPG_BASE + RZV_CPG_CLMA9_CTL_OFFSET)
#define RZV_CPG_CLMA10_CTL                           (RZV_CPG_BASE + RZV_CPG_CLMA10_CTL_OFFSET)
#define RZV_CPG_CLMA11_CTL                           (RZV_CPG_BASE + RZV_CPG_CLMA11_CTL_OFFSET)
#define RZV_CPG_CLMA12_CTL                           (RZV_CPG_BASE + RZV_CPG_CLMA12_CTL_OFFSET)
#define RZV_CPG_CLMA13_CTL                           (RZV_CPG_BASE + RZV_CPG_CLMA13_CTL_OFFSET)
#define RZV_CPG_CLMA14_CTL                           (RZV_CPG_BASE + RZV_CPG_CLMA14_CTL_OFFSET)
#define RZV_CPG_CLMA_MON                             (RZV_CPG_BASE + RZV_CPG_CLMA_MON_OFFSET)
#define RZV_CPG_CLKSTATUS0                           (RZV_CPG_BASE + RZV_CPG_CLKSTATUS0_OFFSET)
#define RZV_CPG_LP_GPU_CTL                           (RZV_CPG_BASE + RZV_CPG_LP_GPU_CTL_OFFSET)
#define RZV_CPG_CM33_CTL                             (RZV_CPG_BASE + RZV_CPG_CM33_CTL_OFFSET)
#define RZV_CPG_CR8_CORESTATUS                       (RZV_CPG_BASE + RZV_CPG_CR8_CORESTATUS_OFFSET)
#define RZV_CPG_CR8_CONFIG1                          (RZV_CPG_BASE + RZV_CPG_CR8_CONFIG1_OFFSET)
#define RZV_CPG_LP_CM33CTL0                          (RZV_CPG_BASE + RZV_CPG_LP_CM33CTL0_OFFSET)
#define RZV_CPG_LP_CM33CTL1                          (RZV_CPG_BASE + RZV_CPG_LP_CM33CTL1_OFFSET)
#define RZV_CPG_LP_CA55_CTL1                         (RZV_CPG_BASE + RZV_CPG_LP_CA55_CTL1_OFFSET)
#define RZV_CPG_LP_CA55_CTL2                         (RZV_CPG_BASE + RZV_CPG_LP_CA55_CTL2_OFFSET)
#define RZV_CPG_LP_CA55_CTL3                         (RZV_CPG_BASE + RZV_CPG_LP_CA55_CTL3_OFFSET)
#define RZV_CPG_LP_CA55_CTL6                         (RZV_CPG_BASE + RZV_CPG_LP_CA55_CTL6_OFFSET)
#define RZV_CPG_LP_CA55_CTL7                         (RZV_CPG_BASE + RZV_CPG_LP_CA55_CTL7_OFFSET)
#define RZV_CPG_LP_CR8_CTL3                          (RZV_CPG_BASE + RZV_CPG_LP_CR8_CTL3_OFFSET)
#define RZV_CPG_LP_CR8_CTL4                          (RZV_CPG_BASE + RZV_CPG_LP_CR8_CTL4_OFFSET)
#define RZV_CPG_LP_PMU_CTL1                          (RZV_CPG_BASE + RZV_CPG_LP_PMU_CTL1_OFFSET)
#define RZV_CPG_OTP_HANDSHAKE_MON                    (RZV_CPG_BASE + RZV_CPG_OTP_HANDSHAKE_MON_OFFSET)
#define RZV_CPG_OTHERS_INI                           (RZV_CPG_BASE + RZV_CPG_OTHERS_INI_OFFSET)
#define RZV_CPG_BUS_1_MSTOP                          (RZV_CPG_BASE + RZV_CPG_BUS_1_MSTOP_OFFSET)
#define RZV_CPG_BUS_2_MSTOP                          (RZV_CPG_BASE + RZV_CPG_BUS_2_MSTOP_OFFSET)
#define RZV_CPG_BUS_3_MSTOP                          (RZV_CPG_BASE + RZV_CPG_BUS_3_MSTOP_OFFSET)
#define RZV_CPG_BUS_4_MSTOP                          (RZV_CPG_BASE + RZV_CPG_BUS_4_MSTOP_OFFSET)
#define RZV_CPG_BUS_5_MSTOP                          (RZV_CPG_BASE + RZV_CPG_BUS_5_MSTOP_OFFSET)
#define RZV_CPG_BUS_6_MSTOP                          (RZV_CPG_BASE + RZV_CPG_BUS_6_MSTOP_OFFSET)
#define RZV_CPG_BUS_7_MSTOP                          (RZV_CPG_BASE + RZV_CPG_BUS_7_MSTOP_OFFSET)
#define RZV_CPG_BUS_8_MSTOP                          (RZV_CPG_BASE + RZV_CPG_BUS_8_MSTOP_OFFSET)
#define RZV_CPG_BUS_9_MSTOP                          (RZV_CPG_BASE + RZV_CPG_BUS_9_MSTOP_OFFSET)
#define RZV_CPG_BUS_10_MSTOP                         (RZV_CPG_BASE + RZV_CPG_BUS_10_MSTOP_OFFSET)
#define RZV_CPG_BUS_11_MSTOP                         (RZV_CPG_BASE + RZV_CPG_BUS_11_MSTOP_OFFSET)
#define RZV_CPG_BUS_12_MSTOP                         (RZV_CPG_BASE + RZV_CPG_BUS_12_MSTOP_OFFSET)

/* CLKON 2-bit-pair peripheral marker **************************************/
/* Peripherals that require both CLK0+CLK1 of a CLKON register to be set.
 * FSP bsp_clocks.h: DMAC uses 3U<<CLK0_ON_Pos; ADC uses 3U<<CLK0_ON_Pos.
 * audit Critical-3.  rzv_clock_enable/disable use RZV_CPG_DOMAIN(clk_id)
 * comparison against the DMAC domain index to detect 2-bit pair entries. */
#define RZV_CPG_CLKBIT_DMAC_MASK    0x3u  /* bits [1:0] = 2-bit pair for DMAC */
#define RZV_CPG_CLKBIT_ADC_MASK     0x3u  /* bits [1:0] = 2-bit pair for ADC  */

/* CPG CDDIV Register Bit Definitions (Parameterized) **********************/

#define CPG_CDDIV_DIVCTL_SHIFT(n)                         ((unsigned)(0 + ((n) * 4)))  /* Bits for DIVCTLn */
#define CPG_CDDIV_DIVCTL_MASK(m,n)                        (0x7u << CPG_CDDIV_DIVCTL_SHIFT(n))
#define CPG_CDDIV_DIVCTL(m,n,v)                           (((unsigned)(v) & 0x7u) << CPG_CDDIV_DIVCTL_SHIFT(n))

#define CPG_CDDIV_DIVCTL0WEN(m)                           (1 << 16)  /* Divctl0Wen */
#define CPG_CDDIV_DIVCTL1WEN(m)                           (1 << 20)  /* Divctl1Wen */
#define CPG_CDDIV_DIVCTL2WEN(m)                           (1 << 24)  /* Divctl2Wen */
#define CPG_CDDIV_DIVCTL3WEN(m)                           (1 << 28)  /* Divctl3Wen */

/* CPG CLKMON Register Bit Definitions (Parameterized) *********************/

#define CPG_CLKMON_CLK0_MON(m)                            (1 << 0)  /* Clk0 Mon */
#define CPG_CLKMON_CLK1_MON(m)                            (1 << 1)  /* Clk1 Mon */
#define CPG_CLKMON_CLK2_MON(m)                            (1 << 2)  /* Clk2 Mon */
#define CPG_CLKMON_CLK3_MON(m)                            (1 << 3)  /* Clk3 Mon */
#define CPG_CLKMON_CLK4_MON(m)                            (1 << 4)  /* Clk4 Mon */
#define CPG_CLKMON_CLK5_MON(m)                            (1 << 5)  /* Clk5 Mon */
#define CPG_CLKMON_CLK6_MON(m)                            (1 << 6)  /* Clk6 Mon */
#define CPG_CLKMON_CLK7_MON(m)                            (1 << 7)  /* Clk7 Mon */
#define CPG_CLKMON_CLK8_MON(m)                            (1 << 8)  /* Clk8 Mon */
#define CPG_CLKMON_CLK9_MON(m)                            (1 << 9)  /* Clk9 Mon */
#define CPG_CLKMON_CLK10_MON(m)                           (1 << 10)  /* Clk10 Mon */
#define CPG_CLKMON_CLK11_MON(m)                           (1 << 11)  /* Clk11 Mon */
#define CPG_CLKMON_CLK12_MON(m)                           (1 << 12)  /* Clk12 Mon */
#define CPG_CLKMON_CLK13_MON(m)                           (1 << 13)  /* Clk13 Mon */
#define CPG_CLKMON_CLK14_MON(m)                           (1 << 14)  /* Clk14 Mon */
#define CPG_CLKMON_CLK15_MON(m)                           (1 << 15)  /* Clk15 Mon */
#define CPG_CLKMON_CLK16_MON(m)                           (1 << 16)  /* Clk16 Mon */
#define CPG_CLKMON_CLK17_MON(m)                           (1 << 17)  /* Clk17 Mon */
#define CPG_CLKMON_CLK18_MON(m)                           (1 << 18)  /* Clk18 Mon */
#define CPG_CLKMON_CLK19_MON(m)                           (1 << 19)  /* Clk19 Mon */
#define CPG_CLKMON_CLK20_MON(m)                           (1 << 20)  /* Clk20 Mon */
#define CPG_CLKMON_CLK21_MON(m)                           (1 << 21)  /* Clk21 Mon */
#define CPG_CLKMON_CLK22_MON(m)                           (1 << 22)  /* Clk22 Mon */
#define CPG_CLKMON_CLK23_MON(m)                           (1 << 23)  /* Clk23 Mon */
#define CPG_CLKMON_CLK24_MON(m)                           (1 << 24)  /* Clk24 Mon */
#define CPG_CLKMON_CLK25_MON(m)                           (1 << 25)  /* Clk25 Mon */
#define CPG_CLKMON_CLK26_MON(m)                           (1 << 26)  /* Clk26 Mon */
#define CPG_CLKMON_CLK27_MON(m)                           (1 << 27)  /* Clk27 Mon */
#define CPG_CLKMON_CLK28_MON(m)                           (1 << 28)  /* Clk28 Mon */
#define CPG_CLKMON_CLK29_MON(m)                           (1 << 29)  /* Clk29 Mon */
#define CPG_CLKMON_CLK30_MON(m)                           (1 << 30)  /* Clk30 Mon */
#define CPG_CLKMON_CLK31_MON(m)                           (1 << 31)  /* Clk31 Mon */

/* CPG CLKON Register Bit Definitions (Parameterized) **********************/

#define CPG_CLKON_CLK0_ON(m)                              (1 << 0)  /* Clk0 On */
#define CPG_CLKON_CLK1_ON(m)                              (1 << 1)  /* Clk1 On */
#define CPG_CLKON_CLK2_ON(m)                              (1 << 2)  /* Clk2 On */
#define CPG_CLKON_CLK3_ON(m)                              (1 << 3)  /* Clk3 On */
#define CPG_CLKON_CLK4_ON(m)                              (1 << 4)  /* Clk4 On */
#define CPG_CLKON_CLK5_ON(m)                              (1 << 5)  /* Clk5 On */
#define CPG_CLKON_CLK6_ON(m)                              (1 << 6)  /* Clk6 On */
#define CPG_CLKON_CLK7_ON(m)                              (1 << 7)  /* Clk7 On */
#define CPG_CLKON_CLK8_ON(m)                              (1 << 8)  /* Clk8 On */
#define CPG_CLKON_CLK9_ON(m)                              (1 << 9)  /* Clk9 On */
#define CPG_CLKON_CLK10_ON(m)                             (1 << 10)  /* Clk10 On */
#define CPG_CLKON_CLK11_ON(m)                             (1 << 11)  /* Clk11 On */
#define CPG_CLKON_CLK12_ON(m)                             (1 << 12)  /* Clk12 On */
#define CPG_CLKON_CLK13_ON(m)                             (1 << 13)  /* Clk13 On */
#define CPG_CLKON_CLK14_ON(m)                             (1 << 14)  /* Clk14 On */
#define CPG_CLKON_CLK15_ON(m)                             (1 << 15)  /* Clk15 On */
#define CPG_CLKON_CLK0_ONWEN(m)                           (1 << 16)  /* Clk0 Onwen */
#define CPG_CLKON_CLK1_ONWEN(m)                           (1 << 17)  /* Clk1 Onwen */
#define CPG_CLKON_CLK2_ONWEN(m)                           (1 << 18)  /* Clk2 Onwen */
#define CPG_CLKON_CLK3_ONWEN(m)                           (1 << 19)  /* Clk3 Onwen */
#define CPG_CLKON_CLK4_ONWEN(m)                           (1 << 20)  /* Clk4 Onwen */
#define CPG_CLKON_CLK5_ONWEN(m)                           (1 << 21)  /* Clk5 Onwen */
#define CPG_CLKON_CLK6_ONWEN(m)                           (1 << 22)  /* Clk6 Onwen */
#define CPG_CLKON_CLK7_ONWEN(m)                           (1 << 23)  /* Clk7 Onwen */
#define CPG_CLKON_CLK8_ONWEN(m)                           (1 << 24)  /* Clk8 Onwen */
#define CPG_CLKON_CLK9_ONWEN(m)                           (1 << 25)  /* Clk9 Onwen */
#define CPG_CLKON_CLK10_ONWEN(m)                          (1 << 26)  /* Clk10 Onwen */
#define CPG_CLKON_CLK11_ONWEN(m)                          (1 << 27)  /* Clk11 Onwen */
#define CPG_CLKON_CLK12_ONWEN(m)                          (1 << 28)  /* Clk12 Onwen */
#define CPG_CLKON_CLK13_ONWEN(m)                          (1 << 29)  /* Clk13 Onwen */
#define CPG_CLKON_CLK14_ONWEN(m)                          (1 << 30)  /* Clk14 Onwen */
#define CPG_CLKON_CLK15_ONWEN(m)                          (1 << 31)  /* Clk15 Onwen */

/* CPG CSDIV Register Bit Definitions (Parameterized) **********************/

#define CPG_CSDIV_DIVCTL0_SHIFT                           (0)      /* Bits 0-1: Divctl0 */
#define CPG_CSDIV_DIVCTL0_MASK(m)                         (0x3 << CPG_CSDIV_DIVCTL0_SHIFT)
#define CPG_CSDIV_DIVCTL0(m,val)                          (((val) << CPG_CSDIV_DIVCTL0_SHIFT) & CPG_CSDIV_DIVCTL0_MASK(m))
#define CPG_CSDIV_DIVCTL1_SHIFT                           (4)      /* Bits 4-5: Divctl1 */
#define CPG_CSDIV_DIVCTL1_MASK(m)                         (0x3 << CPG_CSDIV_DIVCTL1_SHIFT)
#define CPG_CSDIV_DIVCTL1(m,val)                          (((val) << CPG_CSDIV_DIVCTL1_SHIFT) & CPG_CSDIV_DIVCTL1_MASK(m))
#define CPG_CSDIV_DIVCTL2_SHIFT                           (8)      /* Bits 8-11: Divctl2 */
#define CPG_CSDIV_DIVCTL2_MASK(m)                         (0xf << CPG_CSDIV_DIVCTL2_SHIFT)
#define CPG_CSDIV_DIVCTL2(m,val)                          (((val) << CPG_CSDIV_DIVCTL2_SHIFT) & CPG_CSDIV_DIVCTL2_MASK(m))
#define CPG_CSDIV_DIVCTL3_SHIFT                           (12)      /* Bits 12-13: Divctl3 */
#define CPG_CSDIV_DIVCTL3_MASK(m)                         (0x3 << CPG_CSDIV_DIVCTL3_SHIFT)
#define CPG_CSDIV_DIVCTL3(m,val)                          (((val) << CPG_CSDIV_DIVCTL3_SHIFT) & CPG_CSDIV_DIVCTL3_MASK(m))
#define CPG_CSDIV_DIVCTL0WEN(m)                           (1 << 16)  /* Divctl0Wen */
#define CPG_CSDIV_DIVCTL1WEN(m)                           (1 << 20)  /* Divctl1Wen */
#define CPG_CSDIV_DIVCTL2WEN(m)                           (1 << 24)  /* Divctl2Wen */
#define CPG_CSDIV_DIVCTL3WEN(m)                           (1 << 28)  /* Divctl3Wen */

/* CPG ERRORRST_SEL Register Bit Definitions (Parameterized) ***************/

#define CPG_ERRORRST_SEL_ERRRSTSEL(m,n)                   (1u << (0 + ((unsigned)(n) * 1)))  /* Errrstsel0 */

#define CPG_ERRORRST_SEL_ERRRSTSEL0_WEN(m)                (1 << 16)  /* Errrstsel0 Wen */
#define CPG_ERRORRST_SEL_ERRRSTSEL1_WEN(m)                (1 << 17)  /* Errrstsel1 Wen */
#define CPG_ERRORRST_SEL_ERRRSTSEL2_WEN(m)                (1 << 18)  /* Errrstsel2 Wen */
#define CPG_ERRORRST_SEL_ERRRSTSEL3_WEN(m)                (1 << 19)  /* Errrstsel3 Wen */

/* CPG ERROR_RST Register Bit Definitions (Parameterized) ******************/

#define CPG_ERROR_RST_ERROR_RST(m,n)                      (1u << (0 + ((unsigned)(n) * 1)))  /* Error Rst0 */

#define CPG_ERROR_RST_ERROR_RST0_WEN(m)                   (1 << 16)  /* Error Rst0 Wen */
#define CPG_ERROR_RST_ERROR_RST1_WEN(m)                   (1 << 17)  /* Error Rst1 Wen */
#define CPG_ERROR_RST_ERROR_RST2_WEN(m)                   (1 << 18)  /* Error Rst2 Wen */
#define CPG_ERROR_RST_ERROR_RST3_WEN(m)                   (1 << 19)  /* Error Rst3 Wen */
#define CPG_ERROR_RST_ERROR_RST4_WEN(m)                   (1 << 20)  /* Error Rst4 Wen */
#define CPG_ERROR_RST_ERROR_RST5_WEN(m)                   (1 << 21)  /* Error Rst5 Wen */
#define CPG_ERROR_RST_ERROR_RST6_WEN(m)                   (1 << 22)  /* Error Rst6 Wen */
#define CPG_ERROR_RST_ERROR_RST7_WEN(m)                   (1 << 23)  /* Error Rst7 Wen */
#define CPG_ERROR_RST_ERROR_RST8_WEN(m)                   (1 << 24)  /* Error Rst8 Wen */
#define CPG_ERROR_RST_ERROR_RST9_WEN(m)                   (1 << 25)  /* Error Rst9 Wen */
#define CPG_ERROR_RST_ERROR_RST10_WEN(m)                  (1 << 26)  /* Error Rst10 Wen */
#define CPG_ERROR_RST_ERROR_RST11_WEN(m)                  (1 << 27)  /* Error Rst11 Wen */
#define CPG_ERROR_RST_ERROR_RST12_WEN(m)                  (1 << 28)  /* Error Rst12 Wen */
#define CPG_ERROR_RST_ERROR_RST13_WEN(m)                  (1 << 29)  /* Error Rst13 Wen */
#define CPG_ERROR_RST_ERROR_RST14_WEN(m)                  (1 << 30)  /* Error Rst14 Wen */
#define CPG_ERROR_RST_ERROR_RST15_WEN(m)                  (1 << 31)  /* Error Rst15 Wen */
#define CPG_ERROR_RST_WEN(m)                              (1 << 18)  /* Wen */
#define CPG_ERROR_RST_WEN(m)                              (1 << 18)  /* Wen */
#define CPG_ERROR_RST_WEN(m)                              (1 << 18)  /* Wen */
#define CPG_ERROR_RST_WEN(m)                              (1 << 18)  /* Wen */
#define CPG_ERROR_RST_WEN(m)                              (1 << 18)  /* Wen */
#define CPG_ERROR_RST_WEN(m)                              (1 << 18)  /* Wen */

/* CPG LP_CST_CTL Register Bit Definitions (Parameterized) *****************/

#define CPG_LP_CST_CTL_LPI_ATB_ACK_CA(m,n)                (1u << (1 + ((unsigned)(n) * 8)))  /* Lpi Atb Ack Ca550 */

#define CPG_LP_CST_CTL_LPI_ATB_REQ_CA(m,n)                (1u << (0 + ((unsigned)(n) * 8)))  /* Lpi Atb Req Ca550 */

#define CPG_LP_CST_CTL_Reserved(m,n)                      (1u << (2 + ((unsigned)(n) * 8)))  /* Reserved1 */


/* CPG LP_CTL Register Bit Definitions (Parameterized) *********************/

#define CPG_LP_CTL_STBY(m)                                (1 << 0)  /* Stby */
#define CPG_LP_CTL_CA55SLEEP_REQ_SHIFT                    (8)      /* Bits 8-11: Ca55Sleep Req */
#define CPG_LP_CTL_CA55SLEEP_REQ_MASK(m)                  (0xf << CPG_LP_CTL_CA55SLEEP_REQ_SHIFT)
#define CPG_LP_CTL_CA55SLEEP_REQ(m,val)                   (((val) << CPG_LP_CTL_CA55SLEEP_REQ_SHIFT) & CPG_LP_CTL_CA55SLEEP_REQ_MASK(m))
#define CPG_LP_CTL_CM33SLEEP_REQ(m)                       (1 << 12)  /* Cm33Sleep Req */
#define CPG_LP_CTL_CR8SLEEP_REQ_SHIFT                     (13)      /* Bits 13-14: Cr8Sleep Req */
#define CPG_LP_CTL_CR8SLEEP_REQ_MASK(m)                   (0x3 << CPG_LP_CTL_CR8SLEEP_REQ_SHIFT)
#define CPG_LP_CTL_CR8SLEEP_REQ(m,val)                    (((val) << CPG_LP_CTL_CR8SLEEP_REQ_SHIFT) & CPG_LP_CTL_CR8SLEEP_REQ_MASK(m))
#define CPG_LP_CTL_CM33WRESET_REQ(m)                      (1 << 15)  /* Cm33Wreset Req */
#define CPG_LP_CTL_STBY_CA55ST(m)                         (1 << 16)  /* Stby Ca55St */
#define CPG_LP_CTL_STBY_CM33ST(m)                         (1 << 17)  /* Stby Cm33St */
#define CPG_LP_CTL_CA55SLEEP_ACK_SHIFT                    (24)      /* Bits 24-27: Ca55Sleep Ack */
#define CPG_LP_CTL_CA55SLEEP_ACK_MASK(m)                  (0xf << CPG_LP_CTL_CA55SLEEP_ACK_SHIFT)
#define CPG_LP_CTL_CA55SLEEP_ACK(m,val)                   (((val) << CPG_LP_CTL_CA55SLEEP_ACK_SHIFT) & CPG_LP_CTL_CA55SLEEP_ACK_MASK(m))
#define CPG_LP_CTL_CM33SLEEP_ACK(m)                       (1 << 28)  /* Cm33Sleep Ack */
#define CPG_LP_CTL_CR8SLEEP_ACK_SHIFT                     (29)      /* Bits 29-30: Cr8Sleep Ack */
#define CPG_LP_CTL_CR8SLEEP_ACK_MASK(m)                   (0x3 << CPG_LP_CTL_CR8SLEEP_ACK_SHIFT)
#define CPG_LP_CTL_CR8SLEEP_ACK(m,val)                    (((val) << CPG_LP_CTL_CR8SLEEP_ACK_SHIFT) & CPG_LP_CTL_CR8SLEEP_ACK_MASK(m))
#define CPG_LP_CTL_Reserved(m)                            (1 << 31)  /* Reserved */

/* CPG LP_PWC_CTL Register Bit Definitions (Parameterized) *****************/

#define CPG_LP_PWC_CTL_OTHERS_ON_TRG(m)                   (1 << 0)  /* Others On Trg */
#define CPG_LP_PWC_CTL_OTHERS_OFF_TRG(m)                  (1 << 1)  /* Others Off Trg */
#define CPG_LP_PWC_CTL_AWO_OFF_TRG(m)                     (1 << 2)  /* Awo Off Trg */
#define CPG_LP_PWC_CTL_ALL_OFF_TRG(m)                     (1 << 3)  /* All Off Trg */

/* CPG LP_SRAM_STBY_CTL Register Bit Definitions (Parameterized) ***********/

#define CPG_LP_SRAM_STBY_CTL_SRAM_STBY_CTL_SHIFT          (0)      /* Bits 0-31: Sram Stby Ctl */
#define CPG_LP_SRAM_STBY_CTL_SRAM_STBY_CTL_MASK(m)        (0xffffffff << CPG_LP_SRAM_STBY_CTL_SRAM_STBY_CTL_SHIFT)
#define CPG_LP_SRAM_STBY_CTL_SRAM_STBY_CTL(m,val)         (((val) << CPG_LP_SRAM_STBY_CTL_SRAM_STBY_CTL_SHIFT) & CPG_LP_SRAM_STBY_CTL_SRAM_STBY_CTL_MASK(m))

/* CPG PLLDRP_CLK Register Bit Definitions (Parameterized) *****************/

#define CPG_PLLDRP_CLK_DIV_P_SHIFT                        (0)      /* Bits 0-5: Div P */
#define CPG_PLLDRP_CLK_DIV_P_MASK(m)                      (0x3f << CPG_PLLDRP_CLK_DIV_P_SHIFT)
#define CPG_PLLDRP_CLK_DIV_P(m,val)                       (((val) << CPG_PLLDRP_CLK_DIV_P_SHIFT) & CPG_PLLDRP_CLK_DIV_P_MASK(m))
#define CPG_PLLDRP_CLK_DIV_M_SHIFT                        (6)      /* Bits 6-15: Div M */
#define CPG_PLLDRP_CLK_DIV_M_MASK(m)                      (0x3ff << CPG_PLLDRP_CLK_DIV_M_SHIFT)
#define CPG_PLLDRP_CLK_DIV_M(m,val)                       (((val) << CPG_PLLDRP_CLK_DIV_M_SHIFT) & CPG_PLLDRP_CLK_DIV_M_MASK(m))
#define CPG_PLLDRP_CLK_DIV_K_SHIFT                        (16)      /* Bits 16-31: Div K */
#define CPG_PLLDRP_CLK_DIV_K_MASK(m)                      (0xffff << CPG_PLLDRP_CLK_DIV_K_SHIFT)
#define CPG_PLLDRP_CLK_DIV_K(m,val)                       (((val) << CPG_PLLDRP_CLK_DIV_K_SHIFT) & CPG_PLLDRP_CLK_DIV_K_MASK(m))

/* CPG PLLDSI_CLK Register Bit Definitions (Parameterized) *****************/

#define CPG_PLLDSI_CLK_DIV_P_SHIFT                        (0)      /* Bits 0-5: Div P */
#define CPG_PLLDSI_CLK_DIV_P_MASK(m)                      (0x3f << CPG_PLLDSI_CLK_DIV_P_SHIFT)
#define CPG_PLLDSI_CLK_DIV_P(m,val)                       (((val) << CPG_PLLDSI_CLK_DIV_P_SHIFT) & CPG_PLLDSI_CLK_DIV_P_MASK(m))
#define CPG_PLLDSI_CLK_DIV_M_SHIFT                        (6)      /* Bits 6-15: Div M */
#define CPG_PLLDSI_CLK_DIV_M_MASK(m)                      (0x3ff << CPG_PLLDSI_CLK_DIV_M_SHIFT)
#define CPG_PLLDSI_CLK_DIV_M(m,val)                       (((val) << CPG_PLLDSI_CLK_DIV_M_SHIFT) & CPG_PLLDSI_CLK_DIV_M_MASK(m))
#define CPG_PLLDSI_CLK_DIV_K_SHIFT                        (16)      /* Bits 16-31: Div K */
#define CPG_PLLDSI_CLK_DIV_K_MASK(m)                      (0xffff << CPG_PLLDSI_CLK_DIV_K_SHIFT)
#define CPG_PLLDSI_CLK_DIV_K(m,val)                       (((val) << CPG_PLLDSI_CLK_DIV_K_SHIFT) & CPG_PLLDSI_CLK_DIV_K_MASK(m))

/* CPG PLLGPU_CLK Register Bit Definitions (Parameterized) *****************/

#define CPG_PLLGPU_CLK_DIV_P_SHIFT                        (0)      /* Bits 0-5: Div P */
#define CPG_PLLGPU_CLK_DIV_P_MASK(m)                      (0x3f << CPG_PLLGPU_CLK_DIV_P_SHIFT)
#define CPG_PLLGPU_CLK_DIV_P(m,val)                       (((val) << CPG_PLLGPU_CLK_DIV_P_SHIFT) & CPG_PLLGPU_CLK_DIV_P_MASK(m))
#define CPG_PLLGPU_CLK_DIV_M_SHIFT                        (6)      /* Bits 6-15: Div M */
#define CPG_PLLGPU_CLK_DIV_M_MASK(m)                      (0x3ff << CPG_PLLGPU_CLK_DIV_M_SHIFT)
#define CPG_PLLGPU_CLK_DIV_M(m,val)                       (((val) << CPG_PLLGPU_CLK_DIV_M_SHIFT) & CPG_PLLGPU_CLK_DIV_M_MASK(m))
#define CPG_PLLGPU_CLK_DIV_K_SHIFT                        (16)      /* Bits 16-31: Div K */
#define CPG_PLLGPU_CLK_DIV_K_MASK(m)                      (0xffff << CPG_PLLGPU_CLK_DIV_K_SHIFT)
#define CPG_PLLGPU_CLK_DIV_K(m,val)                       (((val) << CPG_PLLGPU_CLK_DIV_K_SHIFT) & CPG_PLLGPU_CLK_DIV_K_MASK(m))

/* CPG RST Register Bit Definitions (Parameterized) ************************/

#define CPG_RST_RSTB(m,n)                                 (1u << (0 + ((unsigned)(n) * 1)))  /* Rstb0 */

#define CPG_RST_RSTB0_WEN(m)                              (1 << 16)  /* Rstb0 Wen */
#define CPG_RST_RSTB1_WEN(m)                              (1 << 17)  /* Rstb1 Wen */
#define CPG_RST_RSTB2_WEN(m)                              (1 << 18)  /* Rstb2 Wen */
#define CPG_RST_RSTB3_WEN(m)                              (1 << 19)  /* Rstb3 Wen */
#define CPG_RST_RSTB4_WEN(m)                              (1 << 20)  /* Rstb4 Wen */
#define CPG_RST_RSTB5_WEN(m)                              (1 << 21)  /* Rstb5 Wen */
#define CPG_RST_RSTB6_WEN(m)                              (1 << 22)  /* Rstb6 Wen */
#define CPG_RST_RSTB7_WEN(m)                              (1 << 23)  /* Rstb7 Wen */
#define CPG_RST_RSTB8_WEN(m)                              (1 << 24)  /* Rstb8 Wen */
#define CPG_RST_RSTB9_WEN(m)                              (1 << 25)  /* Rstb9 Wen */
#define CPG_RST_RSTB10_WEN(m)                             (1 << 26)  /* Rstb10 Wen */
#define CPG_RST_RSTB11_WEN(m)                             (1 << 27)  /* Rstb11 Wen */
#define CPG_RST_RSTB12_WEN(m)                             (1 << 28)  /* Rstb12 Wen */
#define CPG_RST_RSTB13_WEN(m)                             (1 << 29)  /* Rstb13 Wen */
#define CPG_RST_RSTB14_WEN(m)                             (1 << 30)  /* Rstb14 Wen */
#define CPG_RST_RSTB15_WEN(m)                             (1 << 31)  /* Rstb15 Wen */

/* CPG RSTMON Register Bit Definitions (Parameterized) *********************/

#define CPG_RSTMON_RST0_MON(m)                            (1 << 0)  /* Rst0 Mon */
#define CPG_RSTMON_RST1_MON(m)                            (1 << 1)  /* Rst1 Mon */
#define CPG_RSTMON_RST2_MON(m)                            (1 << 2)  /* Rst2 Mon */
#define CPG_RSTMON_RST3_MON(m)                            (1 << 3)  /* Rst3 Mon */
#define CPG_RSTMON_RST4_MON(m)                            (1 << 4)  /* Rst4 Mon */
#define CPG_RSTMON_RST5_MON(m)                            (1 << 5)  /* Rst5 Mon */
#define CPG_RSTMON_RST6_MON(m)                            (1 << 6)  /* Rst6 Mon */
#define CPG_RSTMON_RST7_MON(m)                            (1 << 7)  /* Rst7 Mon */
#define CPG_RSTMON_RST8_MON(m)                            (1 << 8)  /* Rst8 Mon */
#define CPG_RSTMON_RST9_MON(m)                            (1 << 9)  /* Rst9 Mon */
#define CPG_RSTMON_RST10_MON(m)                           (1 << 10)  /* Rst10 Mon */
#define CPG_RSTMON_RST11_MON(m)                           (1 << 11)  /* Rst11 Mon */
#define CPG_RSTMON_RST12_MON(m)                           (1 << 12)  /* Rst12 Mon */
#define CPG_RSTMON_RST13_MON(m)                           (1 << 13)  /* Rst13 Mon */
#define CPG_RSTMON_RST14_MON(m)                           (1 << 14)  /* Rst14 Mon */
#define CPG_RSTMON_RST15_MON(m)                           (1 << 15)  /* Rst15 Mon */
#define CPG_RSTMON_RST16_MON(m)                           (1 << 16)  /* Rst16 Mon */
#define CPG_RSTMON_RST17_MON(m)                           (1 << 17)  /* Rst17 Mon */
#define CPG_RSTMON_RST18_MON(m)                           (1 << 18)  /* Rst18 Mon */
#define CPG_RSTMON_RST19_MON(m)                           (1 << 19)  /* Rst19 Mon */
#define CPG_RSTMON_RST20_MON(m)                           (1 << 20)  /* Rst20 Mon */
#define CPG_RSTMON_RST21_MON(m)                           (1 << 21)  /* Rst21 Mon */
#define CPG_RSTMON_RST22_MON(m)                           (1 << 22)  /* Rst22 Mon */
#define CPG_RSTMON_RST23_MON(m)                           (1 << 23)  /* Rst23 Mon */
#define CPG_RSTMON_RST24_MON(m)                           (1 << 24)  /* Rst24 Mon */
#define CPG_RSTMON_RST25_MON(m)                           (1 << 25)  /* Rst25 Mon */
#define CPG_RSTMON_RST26_MON(m)                           (1 << 26)  /* Rst26 Mon */
#define CPG_RSTMON_RST27_MON(m)                           (1 << 27)  /* Rst27 Mon */
#define CPG_RSTMON_RST28_MON(m)                           (1 << 28)  /* Rst28 Mon */
#define CPG_RSTMON_RST29_MON(m)                           (1 << 29)  /* Rst29 Mon */
#define CPG_RSTMON_RST30_MON(m)                           (1 << 30)  /* Rst30 Mon */
#define CPG_RSTMON_RST31_MON(m)                           (1 << 31)  /* Rst31 Mon */

/* CPG SSEL Register Bit Definitions (Parameterized) ***********************/

#define CPG_SSEL_SELCTL(m,n)                              (1u << (0 + ((unsigned)(n) * 4)))  /* Selctl0 */

#define CPG_SSEL_SELCTL0WEN(m)                            (1 << 16)  /* Selctl0Wen */
#define CPG_SSEL_SELCTL1WEN(m)                            (1 << 20)  /* Selctl1Wen */
#define CPG_SSEL_SELCTL2WEN(m)                            (1 << 24)  /* Selctl2Wen */
#define CPG_SSEL_SELCTL3WEN(m)                            (1 << 28)  /* Selctl3Wen */

/* CPG BUS_10_MSTOP Register Bit Definitions *************************/

#define CPG_BUS_10_MSTOP_MSTOP0_ON              (1 << 0)  /* Mstop0 On */

#define CPG_BUS_10_MSTOP_MSTOP1_ON              (1 << 1)  /* Mstop1 On */

#define CPG_BUS_10_MSTOP_MSTOP2_ON              (1 << 2)  /* Mstop2 On */

#define CPG_BUS_10_MSTOP_MSTOP3_ON              (1 << 3)  /* Mstop3 On */

#define CPG_BUS_10_MSTOP_MSTOP4_ON              (1 << 4)  /* Mstop4 On */

#define CPG_BUS_10_MSTOP_MSTOP5_ON              (1 << 5)  /* Mstop5 On */

#define CPG_BUS_10_MSTOP_MSTOP6_ON              (1 << 6)  /* Mstop6 On */

#define CPG_BUS_10_MSTOP_MSTOP7_ON              (1 << 7)  /* Mstop7 On */

#define CPG_BUS_10_MSTOP_MSTOP8_ON              (1 << 8)  /* Mstop8 On */

#define CPG_BUS_10_MSTOP_MSTOP9_ON              (1 << 9)  /* Mstop9 On */

#define CPG_BUS_10_MSTOP_MSTOP10_ON             (1 << 10)  /* Mstop10 On */

#define CPG_BUS_10_MSTOP_MSTOP11_ON             (1 << 11)  /* Mstop11 On */

#define CPG_BUS_10_MSTOP_MSTOP12_ON             (1 << 12)  /* Mstop12 On */

#define CPG_BUS_10_MSTOP_MSTOP13_ON             (1 << 13)  /* Mstop13 On */

#define CPG_BUS_10_MSTOP_MSTOP14_ON             (1 << 14)  /* Mstop14 On */

#define CPG_BUS_10_MSTOP_MSTOP15_ON             (1 << 15)  /* Mstop15 On */

#define CPG_BUS_10_MSTOP_MSTOP0_ON_WEN          (1 << 16)  /* Mstop0 On Wen */

#define CPG_BUS_10_MSTOP_MSTOP1_ON_WEN          (1 << 17)  /* Mstop1 On Wen */

#define CPG_BUS_10_MSTOP_MSTOP2_ON_WEN          (1 << 18)  /* Mstop2 On Wen */

#define CPG_BUS_10_MSTOP_MSTOP3_ON_WEN          (1 << 19)  /* Mstop3 On Wen */

#define CPG_BUS_10_MSTOP_MSTOP4_ON_WEN          (1 << 20)  /* Mstop4 On Wen */

#define CPG_BUS_10_MSTOP_MSTOP5_ON_WEN          (1 << 21)  /* Mstop5 On Wen */

#define CPG_BUS_10_MSTOP_MSTOP6_ON_WEN          (1 << 22)  /* Mstop6 On Wen */

#define CPG_BUS_10_MSTOP_MSTOP7_ON_WEN          (1 << 23)  /* Mstop7 On Wen */

#define CPG_BUS_10_MSTOP_MSTOP8_ON_WEN          (1 << 24)  /* Mstop8 On Wen */

#define CPG_BUS_10_MSTOP_MSTOP9_ON_WEN          (1 << 25)  /* Mstop9 On Wen */

#define CPG_BUS_10_MSTOP_MSTOP10_ON_WEN         (1 << 26)  /* Mstop10 On Wen */

#define CPG_BUS_10_MSTOP_MSTOP11_ON_WEN         (1 << 27)  /* Mstop11 On Wen */

#define CPG_BUS_10_MSTOP_MSTOP12_ON_WEN         (1 << 28)  /* Mstop12 On Wen */

#define CPG_BUS_10_MSTOP_MSTOP13_ON_WEN         (1 << 29)  /* Mstop13 On Wen */

#define CPG_BUS_10_MSTOP_MSTOP14_ON_WEN         (1 << 30)  /* Mstop14 On Wen */

#define CPG_BUS_10_MSTOP_MSTOP15_ON_WEN         (1 << 31)  /* Mstop15 On Wen */

/* CPG BUS_11_MSTOP Register Bit Definitions *************************/

#define CPG_BUS_11_MSTOP_MSTOP0_ON              (1 << 0)  /* Mstop0 On */

#define CPG_BUS_11_MSTOP_MSTOP1_ON              (1 << 1)  /* Mstop1 On */

#define CPG_BUS_11_MSTOP_MSTOP2_ON              (1 << 2)  /* Mstop2 On */

#define CPG_BUS_11_MSTOP_MSTOP3_ON              (1 << 3)  /* Mstop3 On */

#define CPG_BUS_11_MSTOP_MSTOP4_ON              (1 << 4)  /* Mstop4 On */

#define CPG_BUS_11_MSTOP_MSTOP5_ON              (1 << 5)  /* Mstop5 On */

#define CPG_BUS_11_MSTOP_MSTOP6_ON              (1 << 6)  /* Mstop6 On */

#define CPG_BUS_11_MSTOP_MSTOP7_ON              (1 << 7)  /* Mstop7 On */

#define CPG_BUS_11_MSTOP_MSTOP8_ON              (1 << 8)  /* Mstop8 On */

#define CPG_BUS_11_MSTOP_MSTOP9_ON              (1 << 9)  /* Mstop9 On */

#define CPG_BUS_11_MSTOP_MSTOP10_ON             (1 << 10)  /* Mstop10 On */

#define CPG_BUS_11_MSTOP_MSTOP11_ON             (1 << 11)  /* Mstop11 On */

#define CPG_BUS_11_MSTOP_MSTOP12_ON             (1 << 12)  /* Mstop12 On */

#define CPG_BUS_11_MSTOP_MSTOP13_ON             (1 << 13)  /* Mstop13 On */

#define CPG_BUS_11_MSTOP_MSTOP14_ON             (1 << 14)  /* Mstop14 On */

#define CPG_BUS_11_MSTOP_MSTOP15_ON             (1 << 15)  /* Mstop15 On */

#define CPG_BUS_11_MSTOP_MSTOP0_ON_WEN          (1 << 16)  /* Mstop0 On Wen */

#define CPG_BUS_11_MSTOP_MSTOP1_ON_WEN          (1 << 17)  /* Mstop1 On Wen */

#define CPG_BUS_11_MSTOP_MSTOP2_ON_WEN          (1 << 18)  /* Mstop2 On Wen */

#define CPG_BUS_11_MSTOP_MSTOP3_ON_WEN          (1 << 19)  /* Mstop3 On Wen */

#define CPG_BUS_11_MSTOP_MSTOP4_ON_WEN          (1 << 20)  /* Mstop4 On Wen */

#define CPG_BUS_11_MSTOP_MSTOP5_ON_WEN          (1 << 21)  /* Mstop5 On Wen */

#define CPG_BUS_11_MSTOP_MSTOP6_ON_WEN          (1 << 22)  /* Mstop6 On Wen */

#define CPG_BUS_11_MSTOP_MSTOP7_ON_WEN          (1 << 23)  /* Mstop7 On Wen */

#define CPG_BUS_11_MSTOP_MSTOP8_ON_WEN          (1 << 24)  /* Mstop8 On Wen */

#define CPG_BUS_11_MSTOP_MSTOP9_ON_WEN          (1 << 25)  /* Mstop9 On Wen */

#define CPG_BUS_11_MSTOP_MSTOP10_ON_WEN         (1 << 26)  /* Mstop10 On Wen */

#define CPG_BUS_11_MSTOP_MSTOP11_ON_WEN         (1 << 27)  /* Mstop11 On Wen */

#define CPG_BUS_11_MSTOP_MSTOP12_ON_WEN         (1 << 28)  /* Mstop12 On Wen */

#define CPG_BUS_11_MSTOP_MSTOP13_ON_WEN         (1 << 29)  /* Mstop13 On Wen */

#define CPG_BUS_11_MSTOP_MSTOP14_ON_WEN         (1 << 30)  /* Mstop14 On Wen */

#define CPG_BUS_11_MSTOP_MSTOP15_ON_WEN         (1 << 31)  /* Mstop15 On Wen */

/* CPG BUS_12_MSTOP Register Bit Definitions *************************/

#define CPG_BUS_12_MSTOP_MSTOP0_ON              (1 << 0)  /* Mstop0 On */

#define CPG_BUS_12_MSTOP_MSTOP1_ON              (1 << 1)  /* Mstop1 On */

#define CPG_BUS_12_MSTOP_MSTOP2_ON              (1 << 2)  /* Mstop2 On */

#define CPG_BUS_12_MSTOP_MSTOP3_ON              (1 << 3)  /* Mstop3 On */

#define CPG_BUS_12_MSTOP_MSTOP4_ON              (1 << 4)  /* Mstop4 On */

#define CPG_BUS_12_MSTOP_MSTOP5_ON              (1 << 5)  /* Mstop5 On */

#define CPG_BUS_12_MSTOP_MSTOP6_ON              (1 << 6)  /* Mstop6 On */

#define CPG_BUS_12_MSTOP_MSTOP7_ON              (1 << 7)  /* Mstop7 On */

#define CPG_BUS_12_MSTOP_MSTOP8_ON              (1 << 8)  /* Mstop8 On */

#define CPG_BUS_12_MSTOP_MSTOP9_ON              (1 << 9)  /* Mstop9 On */

#define CPG_BUS_12_MSTOP_MSTOP10_ON             (1 << 10)  /* Mstop10 On */

#define CPG_BUS_12_MSTOP_MSTOP11_ON             (1 << 11)  /* Mstop11 On */

#define CPG_BUS_12_MSTOP_MSTOP12_ON             (1 << 12)  /* Mstop12 On */

#define CPG_BUS_12_MSTOP_MSTOP13_ON             (1 << 13)  /* Mstop13 On */

#define CPG_BUS_12_MSTOP_MSTOP14_ON             (1 << 14)  /* Mstop14 On */

#define CPG_BUS_12_MSTOP_MSTOP15_ON             (1 << 15)  /* Mstop15 On */

#define CPG_BUS_12_MSTOP_MSTOP0_ON_WEN          (1 << 16)  /* Mstop0 On Wen */

#define CPG_BUS_12_MSTOP_MSTOP1_ON_WEN          (1 << 17)  /* Mstop1 On Wen */

#define CPG_BUS_12_MSTOP_MSTOP2_ON_WEN          (1 << 18)  /* Mstop2 On Wen */

#define CPG_BUS_12_MSTOP_MSTOP3_ON_WEN          (1 << 19)  /* Mstop3 On Wen */

#define CPG_BUS_12_MSTOP_MSTOP4_ON_WEN          (1 << 20)  /* Mstop4 On Wen */

#define CPG_BUS_12_MSTOP_MSTOP5_ON_WEN          (1 << 21)  /* Mstop5 On Wen */

#define CPG_BUS_12_MSTOP_MSTOP6_ON_WEN          (1 << 22)  /* Mstop6 On Wen */

#define CPG_BUS_12_MSTOP_MSTOP7_ON_WEN          (1 << 23)  /* Mstop7 On Wen */

#define CPG_BUS_12_MSTOP_MSTOP8_ON_WEN          (1 << 24)  /* Mstop8 On Wen */

#define CPG_BUS_12_MSTOP_MSTOP9_ON_WEN          (1 << 25)  /* Mstop9 On Wen */

#define CPG_BUS_12_MSTOP_MSTOP10_ON_WEN         (1 << 26)  /* Mstop10 On Wen */

#define CPG_BUS_12_MSTOP_MSTOP11_ON_WEN         (1 << 27)  /* Mstop11 On Wen */

#define CPG_BUS_12_MSTOP_MSTOP12_ON_WEN         (1 << 28)  /* Mstop12 On Wen */

#define CPG_BUS_12_MSTOP_MSTOP13_ON_WEN         (1 << 29)  /* Mstop13 On Wen */

#define CPG_BUS_12_MSTOP_MSTOP14_ON_WEN         (1 << 30)  /* Mstop14 On Wen */

#define CPG_BUS_12_MSTOP_MSTOP15_ON_WEN         (1 << 31)  /* Mstop15 On Wen */

/* CPG BUS_1_MSTOP Register Bit Definitions **************************/

#define CPG_BUS_1_MSTOP_MSTOP0_ON               (1 << 0)  /* Mstop0 On */

#define CPG_BUS_1_MSTOP_MSTOP1_ON               (1 << 1)  /* Mstop1 On */

#define CPG_BUS_1_MSTOP_MSTOP2_ON               (1 << 2)  /* Mstop2 On */

#define CPG_BUS_1_MSTOP_MSTOP3_ON               (1 << 3)  /* Mstop3 On */

#define CPG_BUS_1_MSTOP_MSTOP4_ON               (1 << 4)  /* Mstop4 On */

#define CPG_BUS_1_MSTOP_MSTOP5_ON               (1 << 5)  /* Mstop5 On */

#define CPG_BUS_1_MSTOP_MSTOP6_ON               (1 << 6)  /* Mstop6 On */

#define CPG_BUS_1_MSTOP_MSTOP7_ON               (1 << 7)  /* Mstop7 On */

#define CPG_BUS_1_MSTOP_MSTOP8_ON               (1 << 8)  /* Mstop8 On */

#define CPG_BUS_1_MSTOP_MSTOP9_ON               (1 << 9)  /* Mstop9 On */

#define CPG_BUS_1_MSTOP_MSTOP10_ON              (1 << 10)  /* Mstop10 On */

#define CPG_BUS_1_MSTOP_MSTOP11_ON              (1 << 11)  /* Mstop11 On */

#define CPG_BUS_1_MSTOP_MSTOP12_ON              (1 << 12)  /* Mstop12 On */

#define CPG_BUS_1_MSTOP_MSTOP13_ON              (1 << 13)  /* Mstop13 On */

#define CPG_BUS_1_MSTOP_MSTOP14_ON              (1 << 14)  /* Mstop14 On */

#define CPG_BUS_1_MSTOP_MSTOP15_ON              (1 << 15)  /* Mstop15 On */

#define CPG_BUS_1_MSTOP_MSTOP0_ON_WEN           (1 << 16)  /* Mstop0 On Wen */

#define CPG_BUS_1_MSTOP_MSTOP1_ON_WEN           (1 << 17)  /* Mstop1 On Wen */

#define CPG_BUS_1_MSTOP_MSTOP2_ON_WEN           (1 << 18)  /* Mstop2 On Wen */

#define CPG_BUS_1_MSTOP_MSTOP3_ON_WEN           (1 << 19)  /* Mstop3 On Wen */

#define CPG_BUS_1_MSTOP_MSTOP4_ON_WEN           (1 << 20)  /* Mstop4 On Wen */

#define CPG_BUS_1_MSTOP_MSTOP5_ON_WEN           (1 << 21)  /* Mstop5 On Wen */

#define CPG_BUS_1_MSTOP_MSTOP6_ON_WEN           (1 << 22)  /* Mstop6 On Wen */

#define CPG_BUS_1_MSTOP_MSTOP7_ON_WEN           (1 << 23)  /* Mstop7 On Wen */

#define CPG_BUS_1_MSTOP_MSTOP8_ON_WEN           (1 << 24)  /* Mstop8 On Wen */

#define CPG_BUS_1_MSTOP_MSTOP9_ON_WEN           (1 << 25)  /* Mstop9 On Wen */

#define CPG_BUS_1_MSTOP_MSTOP10_ON_WEN          (1 << 26)  /* Mstop10 On Wen */

#define CPG_BUS_1_MSTOP_MSTOP11_ON_WEN          (1 << 27)  /* Mstop11 On Wen */

#define CPG_BUS_1_MSTOP_MSTOP12_ON_WEN          (1 << 28)  /* Mstop12 On Wen */

#define CPG_BUS_1_MSTOP_MSTOP13_ON_WEN          (1 << 29)  /* Mstop13 On Wen */

#define CPG_BUS_1_MSTOP_MSTOP14_ON_WEN          (1 << 30)  /* Mstop14 On Wen */

#define CPG_BUS_1_MSTOP_MSTOP15_ON_WEN          (1 << 31)  /* Mstop15 On Wen */

/* CPG BUS_2_MSTOP Register Bit Definitions **************************/

#define CPG_BUS_2_MSTOP_MSTOP0_ON               (1 << 0)  /* Mstop0 On */

#define CPG_BUS_2_MSTOP_MSTOP1_ON               (1 << 1)  /* Mstop1 On */

#define CPG_BUS_2_MSTOP_MSTOP2_ON               (1 << 2)  /* Mstop2 On */

#define CPG_BUS_2_MSTOP_MSTOP3_ON               (1 << 3)  /* Mstop3 On */

#define CPG_BUS_2_MSTOP_MSTOP4_ON               (1 << 4)  /* Mstop4 On */

#define CPG_BUS_2_MSTOP_MSTOP5_ON               (1 << 5)  /* Mstop5 On */

#define CPG_BUS_2_MSTOP_MSTOP6_ON               (1 << 6)  /* Mstop6 On */

#define CPG_BUS_2_MSTOP_MSTOP7_ON               (1 << 7)  /* Mstop7 On */

#define CPG_BUS_2_MSTOP_MSTOP8_ON               (1 << 8)  /* Mstop8 On */

#define CPG_BUS_2_MSTOP_MSTOP9_ON               (1 << 9)  /* Mstop9 On */

#define CPG_BUS_2_MSTOP_MSTOP10_ON              (1 << 10)  /* Mstop10 On */

#define CPG_BUS_2_MSTOP_MSTOP11_ON              (1 << 11)  /* Mstop11 On */

#define CPG_BUS_2_MSTOP_MSTOP12_ON              (1 << 12)  /* Mstop12 On */

#define CPG_BUS_2_MSTOP_MSTOP13_ON              (1 << 13)  /* Mstop13 On */

#define CPG_BUS_2_MSTOP_MSTOP14_ON              (1 << 14)  /* Mstop14 On */

#define CPG_BUS_2_MSTOP_MSTOP15_ON              (1 << 15)  /* Mstop15 On */

#define CPG_BUS_2_MSTOP_MSTOP0_ON_WEN           (1 << 16)  /* Mstop0 On Wen */

#define CPG_BUS_2_MSTOP_MSTOP1_ON_WEN           (1 << 17)  /* Mstop1 On Wen */

#define CPG_BUS_2_MSTOP_MSTOP2_ON_WEN           (1 << 18)  /* Mstop2 On Wen */

#define CPG_BUS_2_MSTOP_MSTOP3_ON_WEN           (1 << 19)  /* Mstop3 On Wen */

#define CPG_BUS_2_MSTOP_MSTOP4_ON_WEN           (1 << 20)  /* Mstop4 On Wen */

#define CPG_BUS_2_MSTOP_MSTOP5_ON_WEN           (1 << 21)  /* Mstop5 On Wen */

#define CPG_BUS_2_MSTOP_MSTOP6_ON_WEN           (1 << 22)  /* Mstop6 On Wen */

#define CPG_BUS_2_MSTOP_MSTOP7_ON_WEN           (1 << 23)  /* Mstop7 On Wen */

#define CPG_BUS_2_MSTOP_MSTOP8_ON_WEN           (1 << 24)  /* Mstop8 On Wen */

#define CPG_BUS_2_MSTOP_MSTOP9_ON_WEN           (1 << 25)  /* Mstop9 On Wen */

#define CPG_BUS_2_MSTOP_MSTOP10_ON_WEN          (1 << 26)  /* Mstop10 On Wen */

#define CPG_BUS_2_MSTOP_MSTOP11_ON_WEN          (1 << 27)  /* Mstop11 On Wen */

#define CPG_BUS_2_MSTOP_MSTOP12_ON_WEN          (1 << 28)  /* Mstop12 On Wen */

#define CPG_BUS_2_MSTOP_MSTOP13_ON_WEN          (1 << 29)  /* Mstop13 On Wen */

#define CPG_BUS_2_MSTOP_MSTOP14_ON_WEN          (1 << 30)  /* Mstop14 On Wen */

#define CPG_BUS_2_MSTOP_MSTOP15_ON_WEN          (1 << 31)  /* Mstop15 On Wen */

/* CPG BUS_3_MSTOP Register Bit Definitions **************************/

#define CPG_BUS_3_MSTOP_MSTOP0_ON               (1 << 0)  /* Mstop0 On */

#define CPG_BUS_3_MSTOP_MSTOP1_ON               (1 << 1)  /* Mstop1 On */

#define CPG_BUS_3_MSTOP_MSTOP2_ON               (1 << 2)  /* Mstop2 On */

#define CPG_BUS_3_MSTOP_MSTOP3_ON               (1 << 3)  /* Mstop3 On */

#define CPG_BUS_3_MSTOP_MSTOP4_ON               (1 << 4)  /* Mstop4 On */

#define CPG_BUS_3_MSTOP_MSTOP5_ON               (1 << 5)  /* Mstop5 On */

#define CPG_BUS_3_MSTOP_MSTOP6_ON               (1 << 6)  /* Mstop6 On */

#define CPG_BUS_3_MSTOP_MSTOP7_ON               (1 << 7)  /* Mstop7 On */

#define CPG_BUS_3_MSTOP_MSTOP8_ON               (1 << 8)  /* Mstop8 On */

#define CPG_BUS_3_MSTOP_MSTOP9_ON               (1 << 9)  /* Mstop9 On */

#define CPG_BUS_3_MSTOP_MSTOP10_ON              (1 << 10)  /* Mstop10 On */

#define CPG_BUS_3_MSTOP_MSTOP11_ON              (1 << 11)  /* Mstop11 On */

#define CPG_BUS_3_MSTOP_MSTOP12_ON              (1 << 12)  /* Mstop12 On */

#define CPG_BUS_3_MSTOP_MSTOP13_ON              (1 << 13)  /* Mstop13 On */

#define CPG_BUS_3_MSTOP_MSTOP14_ON              (1 << 14)  /* Mstop14 On */

#define CPG_BUS_3_MSTOP_MSTOP15_ON              (1 << 15)  /* Mstop15 On */

#define CPG_BUS_3_MSTOP_MSTOP0_ON_WEN           (1 << 16)  /* Mstop0 On Wen */

#define CPG_BUS_3_MSTOP_MSTOP1_ON_WEN           (1 << 17)  /* Mstop1 On Wen */

#define CPG_BUS_3_MSTOP_MSTOP2_ON_WEN           (1 << 18)  /* Mstop2 On Wen */

#define CPG_BUS_3_MSTOP_MSTOP3_ON_WEN           (1 << 19)  /* Mstop3 On Wen */

#define CPG_BUS_3_MSTOP_MSTOP4_ON_WEN           (1 << 20)  /* Mstop4 On Wen */

#define CPG_BUS_3_MSTOP_MSTOP5_ON_WEN           (1 << 21)  /* Mstop5 On Wen */

#define CPG_BUS_3_MSTOP_MSTOP6_ON_WEN           (1 << 22)  /* Mstop6 On Wen */

#define CPG_BUS_3_MSTOP_MSTOP7_ON_WEN           (1 << 23)  /* Mstop7 On Wen */

#define CPG_BUS_3_MSTOP_MSTOP8_ON_WEN           (1 << 24)  /* Mstop8 On Wen */

#define CPG_BUS_3_MSTOP_MSTOP9_ON_WEN           (1 << 25)  /* Mstop9 On Wen */

#define CPG_BUS_3_MSTOP_MSTOP10_ON_WEN          (1 << 26)  /* Mstop10 On Wen */

#define CPG_BUS_3_MSTOP_MSTOP11_ON_WEN          (1 << 27)  /* Mstop11 On Wen */

#define CPG_BUS_3_MSTOP_MSTOP12_ON_WEN          (1 << 28)  /* Mstop12 On Wen */

#define CPG_BUS_3_MSTOP_MSTOP13_ON_WEN          (1 << 29)  /* Mstop13 On Wen */

#define CPG_BUS_3_MSTOP_MSTOP14_ON_WEN          (1 << 30)  /* Mstop14 On Wen */

#define CPG_BUS_3_MSTOP_MSTOP15_ON_WEN          (1 << 31)  /* Mstop15 On Wen */

/* CPG BUS_4_MSTOP Register Bit Definitions **************************/

#define CPG_BUS_4_MSTOP_MSTOP0_ON               (1 << 0)  /* Mstop0 On */

#define CPG_BUS_4_MSTOP_MSTOP1_ON               (1 << 1)  /* Mstop1 On */

#define CPG_BUS_4_MSTOP_MSTOP2_ON               (1 << 2)  /* Mstop2 On */

#define CPG_BUS_4_MSTOP_MSTOP3_ON               (1 << 3)  /* Mstop3 On */

#define CPG_BUS_4_MSTOP_MSTOP4_ON               (1 << 4)  /* Mstop4 On */

#define CPG_BUS_4_MSTOP_MSTOP5_ON               (1 << 5)  /* Mstop5 On */

#define CPG_BUS_4_MSTOP_MSTOP6_ON               (1 << 6)  /* Mstop6 On */

#define CPG_BUS_4_MSTOP_MSTOP7_ON               (1 << 7)  /* Mstop7 On */

#define CPG_BUS_4_MSTOP_MSTOP8_ON               (1 << 8)  /* Mstop8 On */

#define CPG_BUS_4_MSTOP_MSTOP9_ON               (1 << 9)  /* Mstop9 On */

#define CPG_BUS_4_MSTOP_MSTOP10_ON              (1 << 10)  /* Mstop10 On */

#define CPG_BUS_4_MSTOP_MSTOP11_ON              (1 << 11)  /* Mstop11 On */

#define CPG_BUS_4_MSTOP_MSTOP12_ON              (1 << 12)  /* Mstop12 On */

#define CPG_BUS_4_MSTOP_MSTOP13_ON              (1 << 13)  /* Mstop13 On */

#define CPG_BUS_4_MSTOP_MSTOP14_ON              (1 << 14)  /* Mstop14 On */

#define CPG_BUS_4_MSTOP_MSTOP15_ON              (1 << 15)  /* Mstop15 On */

#define CPG_BUS_4_MSTOP_MSTOP0_ON_WEN           (1 << 16)  /* Mstop0 On Wen */

#define CPG_BUS_4_MSTOP_MSTOP1_ON_WEN           (1 << 17)  /* Mstop1 On Wen */

#define CPG_BUS_4_MSTOP_MSTOP2_ON_WEN           (1 << 18)  /* Mstop2 On Wen */

#define CPG_BUS_4_MSTOP_MSTOP3_ON_WEN           (1 << 19)  /* Mstop3 On Wen */

#define CPG_BUS_4_MSTOP_MSTOP4_ON_WEN           (1 << 20)  /* Mstop4 On Wen */

#define CPG_BUS_4_MSTOP_MSTOP5_ON_WEN           (1 << 21)  /* Mstop5 On Wen */

#define CPG_BUS_4_MSTOP_MSTOP6_ON_WEN           (1 << 22)  /* Mstop6 On Wen */

#define CPG_BUS_4_MSTOP_MSTOP7_ON_WEN           (1 << 23)  /* Mstop7 On Wen */

#define CPG_BUS_4_MSTOP_MSTOP8_ON_WEN           (1 << 24)  /* Mstop8 On Wen */

#define CPG_BUS_4_MSTOP_MSTOP9_ON_WEN           (1 << 25)  /* Mstop9 On Wen */

#define CPG_BUS_4_MSTOP_MSTOP10_ON_WEN          (1 << 26)  /* Mstop10 On Wen */

#define CPG_BUS_4_MSTOP_MSTOP11_ON_WEN          (1 << 27)  /* Mstop11 On Wen */

#define CPG_BUS_4_MSTOP_MSTOP12_ON_WEN          (1 << 28)  /* Mstop12 On Wen */

#define CPG_BUS_4_MSTOP_MSTOP13_ON_WEN          (1 << 29)  /* Mstop13 On Wen */

#define CPG_BUS_4_MSTOP_MSTOP14_ON_WEN          (1 << 30)  /* Mstop14 On Wen */

#define CPG_BUS_4_MSTOP_MSTOP15_ON_WEN          (1 << 31)  /* Mstop15 On Wen */

/* CPG BUS_5_MSTOP Register Bit Definitions **************************/

#define CPG_BUS_5_MSTOP_MSTOP0_ON               (1 << 0)  /* Mstop0 On */

#define CPG_BUS_5_MSTOP_MSTOP1_ON               (1 << 1)  /* Mstop1 On */

#define CPG_BUS_5_MSTOP_MSTOP2_ON               (1 << 2)  /* Mstop2 On */

#define CPG_BUS_5_MSTOP_MSTOP3_ON               (1 << 3)  /* Mstop3 On */

#define CPG_BUS_5_MSTOP_MSTOP4_ON               (1 << 4)  /* Mstop4 On */

#define CPG_BUS_5_MSTOP_MSTOP5_ON               (1 << 5)  /* Mstop5 On */

#define CPG_BUS_5_MSTOP_MSTOP6_ON               (1 << 6)  /* Mstop6 On */

#define CPG_BUS_5_MSTOP_MSTOP7_ON               (1 << 7)  /* Mstop7 On */

#define CPG_BUS_5_MSTOP_MSTOP8_ON               (1 << 8)  /* Mstop8 On */

#define CPG_BUS_5_MSTOP_MSTOP9_ON               (1 << 9)  /* Mstop9 On */

#define CPG_BUS_5_MSTOP_MSTOP10_ON              (1 << 10)  /* Mstop10 On */

#define CPG_BUS_5_MSTOP_MSTOP11_ON              (1 << 11)  /* Mstop11 On */

#define CPG_BUS_5_MSTOP_MSTOP12_ON              (1 << 12)  /* Mstop12 On */

#define CPG_BUS_5_MSTOP_MSTOP13_ON              (1 << 13)  /* Mstop13 On */

#define CPG_BUS_5_MSTOP_MSTOP14_ON              (1 << 14)  /* Mstop14 On */

#define CPG_BUS_5_MSTOP_MSTOP15_ON              (1 << 15)  /* Mstop15 On */

#define CPG_BUS_5_MSTOP_MSTOP0_ON_WEN           (1 << 16)  /* Mstop0 On Wen */

#define CPG_BUS_5_MSTOP_MSTOP1_ON_WEN           (1 << 17)  /* Mstop1 On Wen */

#define CPG_BUS_5_MSTOP_MSTOP2_ON_WEN           (1 << 18)  /* Mstop2 On Wen */

#define CPG_BUS_5_MSTOP_MSTOP3_ON_WEN           (1 << 19)  /* Mstop3 On Wen */

#define CPG_BUS_5_MSTOP_MSTOP4_ON_WEN           (1 << 20)  /* Mstop4 On Wen */

#define CPG_BUS_5_MSTOP_MSTOP5_ON_WEN           (1 << 21)  /* Mstop5 On Wen */

#define CPG_BUS_5_MSTOP_MSTOP6_ON_WEN           (1 << 22)  /* Mstop6 On Wen */

#define CPG_BUS_5_MSTOP_MSTOP7_ON_WEN           (1 << 23)  /* Mstop7 On Wen */

#define CPG_BUS_5_MSTOP_MSTOP8_ON_WEN           (1 << 24)  /* Mstop8 On Wen */

#define CPG_BUS_5_MSTOP_MSTOP9_ON_WEN           (1 << 25)  /* Mstop9 On Wen */

#define CPG_BUS_5_MSTOP_MSTOP10_ON_WEN          (1 << 26)  /* Mstop10 On Wen */

#define CPG_BUS_5_MSTOP_MSTOP11_ON_WEN          (1 << 27)  /* Mstop11 On Wen */

#define CPG_BUS_5_MSTOP_MSTOP12_ON_WEN          (1 << 28)  /* Mstop12 On Wen */

#define CPG_BUS_5_MSTOP_MSTOP13_ON_WEN          (1 << 29)  /* Mstop13 On Wen */

#define CPG_BUS_5_MSTOP_MSTOP14_ON_WEN          (1 << 30)  /* Mstop14 On Wen */

#define CPG_BUS_5_MSTOP_MSTOP15_ON_WEN          (1 << 31)  /* Mstop15 On Wen */

/* CPG BUS_6_MSTOP Register Bit Definitions **************************/

#define CPG_BUS_6_MSTOP_MSTOP0_ON               (1 << 0)  /* Mstop0 On */

#define CPG_BUS_6_MSTOP_MSTOP1_ON               (1 << 1)  /* Mstop1 On */

#define CPG_BUS_6_MSTOP_MSTOP2_ON               (1 << 2)  /* Mstop2 On */

#define CPG_BUS_6_MSTOP_MSTOP3_ON               (1 << 3)  /* Mstop3 On */

#define CPG_BUS_6_MSTOP_MSTOP4_ON               (1 << 4)  /* Mstop4 On */

#define CPG_BUS_6_MSTOP_MSTOP5_ON               (1 << 5)  /* Mstop5 On */

#define CPG_BUS_6_MSTOP_MSTOP6_ON               (1 << 6)  /* Mstop6 On */

#define CPG_BUS_6_MSTOP_MSTOP7_ON               (1 << 7)  /* Mstop7 On */

#define CPG_BUS_6_MSTOP_MSTOP8_ON               (1 << 8)  /* Mstop8 On */

#define CPG_BUS_6_MSTOP_MSTOP9_ON               (1 << 9)  /* Mstop9 On */

#define CPG_BUS_6_MSTOP_MSTOP10_ON              (1 << 10)  /* Mstop10 On */

#define CPG_BUS_6_MSTOP_MSTOP11_ON              (1 << 11)  /* Mstop11 On */

#define CPG_BUS_6_MSTOP_MSTOP12_ON              (1 << 12)  /* Mstop12 On */

#define CPG_BUS_6_MSTOP_MSTOP13_ON              (1 << 13)  /* Mstop13 On */

#define CPG_BUS_6_MSTOP_MSTOP14_ON              (1 << 14)  /* Mstop14 On */

#define CPG_BUS_6_MSTOP_MSTOP15_ON              (1 << 15)  /* Mstop15 On */

#define CPG_BUS_6_MSTOP_MSTOP0_ON_WEN           (1 << 16)  /* Mstop0 On Wen */

#define CPG_BUS_6_MSTOP_MSTOP1_ON_WEN           (1 << 17)  /* Mstop1 On Wen */

#define CPG_BUS_6_MSTOP_MSTOP2_ON_WEN           (1 << 18)  /* Mstop2 On Wen */

#define CPG_BUS_6_MSTOP_MSTOP3_ON_WEN           (1 << 19)  /* Mstop3 On Wen */

#define CPG_BUS_6_MSTOP_MSTOP4_ON_WEN           (1 << 20)  /* Mstop4 On Wen */

#define CPG_BUS_6_MSTOP_MSTOP5_ON_WEN           (1 << 21)  /* Mstop5 On Wen */

#define CPG_BUS_6_MSTOP_MSTOP6_ON_WEN           (1 << 22)  /* Mstop6 On Wen */

#define CPG_BUS_6_MSTOP_MSTOP7_ON_WEN           (1 << 23)  /* Mstop7 On Wen */

#define CPG_BUS_6_MSTOP_MSTOP8_ON_WEN           (1 << 24)  /* Mstop8 On Wen */

#define CPG_BUS_6_MSTOP_MSTOP9_ON_WEN           (1 << 25)  /* Mstop9 On Wen */

#define CPG_BUS_6_MSTOP_MSTOP10_ON_WEN          (1 << 26)  /* Mstop10 On Wen */

#define CPG_BUS_6_MSTOP_MSTOP11_ON_WEN          (1 << 27)  /* Mstop11 On Wen */

#define CPG_BUS_6_MSTOP_MSTOP12_ON_WEN          (1 << 28)  /* Mstop12 On Wen */

#define CPG_BUS_6_MSTOP_MSTOP13_ON_WEN          (1 << 29)  /* Mstop13 On Wen */

#define CPG_BUS_6_MSTOP_MSTOP14_ON_WEN          (1 << 30)  /* Mstop14 On Wen */

#define CPG_BUS_6_MSTOP_MSTOP15_ON_WEN          (1 << 31)  /* Mstop15 On Wen */

/* CPG BUS_7_MSTOP Register Bit Definitions **************************/

#define CPG_BUS_7_MSTOP_MSTOP0_ON               (1 << 0)  /* Mstop0 On */

#define CPG_BUS_7_MSTOP_MSTOP1_ON               (1 << 1)  /* Mstop1 On */

#define CPG_BUS_7_MSTOP_MSTOP2_ON               (1 << 2)  /* Mstop2 On */

#define CPG_BUS_7_MSTOP_MSTOP3_ON               (1 << 3)  /* Mstop3 On */

#define CPG_BUS_7_MSTOP_MSTOP4_ON               (1 << 4)  /* Mstop4 On */

#define CPG_BUS_7_MSTOP_MSTOP5_ON               (1 << 5)  /* Mstop5 On */

#define CPG_BUS_7_MSTOP_MSTOP6_ON               (1 << 6)  /* Mstop6 On */

#define CPG_BUS_7_MSTOP_MSTOP7_ON               (1 << 7)  /* Mstop7 On */

#define CPG_BUS_7_MSTOP_MSTOP8_ON               (1 << 8)  /* Mstop8 On */

#define CPG_BUS_7_MSTOP_MSTOP9_ON               (1 << 9)  /* Mstop9 On */

#define CPG_BUS_7_MSTOP_MSTOP10_ON              (1 << 10)  /* Mstop10 On */

#define CPG_BUS_7_MSTOP_MSTOP11_ON              (1 << 11)  /* Mstop11 On */

#define CPG_BUS_7_MSTOP_MSTOP12_ON              (1 << 12)  /* Mstop12 On */

#define CPG_BUS_7_MSTOP_MSTOP13_ON              (1 << 13)  /* Mstop13 On */

#define CPG_BUS_7_MSTOP_MSTOP14_ON              (1 << 14)  /* Mstop14 On */

#define CPG_BUS_7_MSTOP_MSTOP15_ON              (1 << 15)  /* Mstop15 On */

#define CPG_BUS_7_MSTOP_MSTOP0_ON_WEN           (1 << 16)  /* Mstop0 On Wen */

#define CPG_BUS_7_MSTOP_MSTOP1_ON_WEN           (1 << 17)  /* Mstop1 On Wen */

#define CPG_BUS_7_MSTOP_MSTOP2_ON_WEN           (1 << 18)  /* Mstop2 On Wen */

#define CPG_BUS_7_MSTOP_MSTOP3_ON_WEN           (1 << 19)  /* Mstop3 On Wen */

#define CPG_BUS_7_MSTOP_MSTOP4_ON_WEN           (1 << 20)  /* Mstop4 On Wen */

#define CPG_BUS_7_MSTOP_MSTOP5_ON_WEN           (1 << 21)  /* Mstop5 On Wen */

#define CPG_BUS_7_MSTOP_MSTOP6_ON_WEN           (1 << 22)  /* Mstop6 On Wen */

#define CPG_BUS_7_MSTOP_MSTOP7_ON_WEN           (1 << 23)  /* Mstop7 On Wen */

#define CPG_BUS_7_MSTOP_MSTOP8_ON_WEN           (1 << 24)  /* Mstop8 On Wen */

#define CPG_BUS_7_MSTOP_MSTOP9_ON_WEN           (1 << 25)  /* Mstop9 On Wen */

#define CPG_BUS_7_MSTOP_MSTOP10_ON_WEN          (1 << 26)  /* Mstop10 On Wen */

#define CPG_BUS_7_MSTOP_MSTOP11_ON_WEN          (1 << 27)  /* Mstop11 On Wen */

#define CPG_BUS_7_MSTOP_MSTOP12_ON_WEN          (1 << 28)  /* Mstop12 On Wen */

#define CPG_BUS_7_MSTOP_MSTOP13_ON_WEN          (1 << 29)  /* Mstop13 On Wen */

#define CPG_BUS_7_MSTOP_MSTOP14_ON_WEN          (1 << 30)  /* Mstop14 On Wen */

#define CPG_BUS_7_MSTOP_MSTOP15_ON_WEN          (1 << 31)  /* Mstop15 On Wen */

/* CPG BUS_8_MSTOP Register Bit Definitions **************************/

#define CPG_BUS_8_MSTOP_MSTOP0_ON               (1 << 0)  /* Mstop0 On */

#define CPG_BUS_8_MSTOP_MSTOP1_ON               (1 << 1)  /* Mstop1 On */

#define CPG_BUS_8_MSTOP_MSTOP2_ON               (1 << 2)  /* Mstop2 On */

#define CPG_BUS_8_MSTOP_MSTOP3_ON               (1 << 3)  /* Mstop3 On */

#define CPG_BUS_8_MSTOP_MSTOP4_ON               (1 << 4)  /* Mstop4 On */

#define CPG_BUS_8_MSTOP_MSTOP5_ON               (1 << 5)  /* Mstop5 On */

#define CPG_BUS_8_MSTOP_MSTOP6_ON               (1 << 6)  /* Mstop6 On */

#define CPG_BUS_8_MSTOP_MSTOP7_ON               (1 << 7)  /* Mstop7 On */

#define CPG_BUS_8_MSTOP_MSTOP8_ON               (1 << 8)  /* Mstop8 On */

#define CPG_BUS_8_MSTOP_MSTOP9_ON               (1 << 9)  /* Mstop9 On */

#define CPG_BUS_8_MSTOP_MSTOP10_ON              (1 << 10)  /* Mstop10 On */

#define CPG_BUS_8_MSTOP_MSTOP11_ON              (1 << 11)  /* Mstop11 On */

#define CPG_BUS_8_MSTOP_MSTOP12_ON              (1 << 12)  /* Mstop12 On */

#define CPG_BUS_8_MSTOP_MSTOP13_ON              (1 << 13)  /* Mstop13 On */

#define CPG_BUS_8_MSTOP_MSTOP14_ON              (1 << 14)  /* Mstop14 On */

#define CPG_BUS_8_MSTOP_MSTOP15_ON              (1 << 15)  /* Mstop15 On */

#define CPG_BUS_8_MSTOP_MSTOP0_ON_WEN           (1 << 16)  /* Mstop0 On Wen */

#define CPG_BUS_8_MSTOP_MSTOP1_ON_WEN           (1 << 17)  /* Mstop1 On Wen */

#define CPG_BUS_8_MSTOP_MSTOP2_ON_WEN           (1 << 18)  /* Mstop2 On Wen */

#define CPG_BUS_8_MSTOP_MSTOP3_ON_WEN           (1 << 19)  /* Mstop3 On Wen */

#define CPG_BUS_8_MSTOP_MSTOP4_ON_WEN           (1 << 20)  /* Mstop4 On Wen */

#define CPG_BUS_8_MSTOP_MSTOP5_ON_WEN           (1 << 21)  /* Mstop5 On Wen */

#define CPG_BUS_8_MSTOP_MSTOP6_ON_WEN           (1 << 22)  /* Mstop6 On Wen */

#define CPG_BUS_8_MSTOP_MSTOP7_ON_WEN           (1 << 23)  /* Mstop7 On Wen */

#define CPG_BUS_8_MSTOP_MSTOP8_ON_WEN           (1 << 24)  /* Mstop8 On Wen */

#define CPG_BUS_8_MSTOP_MSTOP9_ON_WEN           (1 << 25)  /* Mstop9 On Wen */

#define CPG_BUS_8_MSTOP_MSTOP10_ON_WEN          (1 << 26)  /* Mstop10 On Wen */

#define CPG_BUS_8_MSTOP_MSTOP11_ON_WEN          (1 << 27)  /* Mstop11 On Wen */

#define CPG_BUS_8_MSTOP_MSTOP12_ON_WEN          (1 << 28)  /* Mstop12 On Wen */

#define CPG_BUS_8_MSTOP_MSTOP13_ON_WEN          (1 << 29)  /* Mstop13 On Wen */

#define CPG_BUS_8_MSTOP_MSTOP14_ON_WEN          (1 << 30)  /* Mstop14 On Wen */

#define CPG_BUS_8_MSTOP_MSTOP15_ON_WEN          (1 << 31)  /* Mstop15 On Wen */

/* CPG BUS_9_MSTOP Register Bit Definitions **************************/

#define CPG_BUS_9_MSTOP_MSTOP0_ON               (1 << 0)  /* Mstop0 On */

#define CPG_BUS_9_MSTOP_MSTOP1_ON               (1 << 1)  /* Mstop1 On */

#define CPG_BUS_9_MSTOP_MSTOP2_ON               (1 << 2)  /* Mstop2 On */

#define CPG_BUS_9_MSTOP_MSTOP3_ON               (1 << 3)  /* Mstop3 On */

#define CPG_BUS_9_MSTOP_MSTOP4_ON               (1 << 4)  /* Mstop4 On */

#define CPG_BUS_9_MSTOP_MSTOP5_ON               (1 << 5)  /* Mstop5 On */

#define CPG_BUS_9_MSTOP_MSTOP6_ON               (1 << 6)  /* Mstop6 On */

#define CPG_BUS_9_MSTOP_MSTOP7_ON               (1 << 7)  /* Mstop7 On */

#define CPG_BUS_9_MSTOP_MSTOP8_ON               (1 << 8)  /* Mstop8 On */

#define CPG_BUS_9_MSTOP_MSTOP9_ON               (1 << 9)  /* Mstop9 On */

#define CPG_BUS_9_MSTOP_MSTOP10_ON              (1 << 10)  /* Mstop10 On */

#define CPG_BUS_9_MSTOP_MSTOP11_ON              (1 << 11)  /* Mstop11 On */

#define CPG_BUS_9_MSTOP_MSTOP12_ON              (1 << 12)  /* Mstop12 On */

#define CPG_BUS_9_MSTOP_MSTOP13_ON              (1 << 13)  /* Mstop13 On */

#define CPG_BUS_9_MSTOP_MSTOP14_ON              (1 << 14)  /* Mstop14 On */

#define CPG_BUS_9_MSTOP_MSTOP15_ON              (1 << 15)  /* Mstop15 On */

#define CPG_BUS_9_MSTOP_MSTOP0_ON_WEN           (1 << 16)  /* Mstop0 On Wen */

#define CPG_BUS_9_MSTOP_MSTOP1_ON_WEN           (1 << 17)  /* Mstop1 On Wen */

#define CPG_BUS_9_MSTOP_MSTOP2_ON_WEN           (1 << 18)  /* Mstop2 On Wen */

#define CPG_BUS_9_MSTOP_MSTOP3_ON_WEN           (1 << 19)  /* Mstop3 On Wen */

#define CPG_BUS_9_MSTOP_MSTOP4_ON_WEN           (1 << 20)  /* Mstop4 On Wen */

#define CPG_BUS_9_MSTOP_MSTOP5_ON_WEN           (1 << 21)  /* Mstop5 On Wen */

#define CPG_BUS_9_MSTOP_MSTOP6_ON_WEN           (1 << 22)  /* Mstop6 On Wen */

#define CPG_BUS_9_MSTOP_MSTOP7_ON_WEN           (1 << 23)  /* Mstop7 On Wen */

#define CPG_BUS_9_MSTOP_MSTOP8_ON_WEN           (1 << 24)  /* Mstop8 On Wen */

#define CPG_BUS_9_MSTOP_MSTOP9_ON_WEN           (1 << 25)  /* Mstop9 On Wen */

#define CPG_BUS_9_MSTOP_MSTOP10_ON_WEN          (1 << 26)  /* Mstop10 On Wen */

#define CPG_BUS_9_MSTOP_MSTOP11_ON_WEN          (1 << 27)  /* Mstop11 On Wen */

#define CPG_BUS_9_MSTOP_MSTOP12_ON_WEN          (1 << 28)  /* Mstop12 On Wen */

#define CPG_BUS_9_MSTOP_MSTOP13_ON_WEN          (1 << 29)  /* Mstop13 On Wen */

#define CPG_BUS_9_MSTOP_MSTOP14_ON_WEN          (1 << 30)  /* Mstop14 On Wen */

#define CPG_BUS_9_MSTOP_MSTOP15_ON_WEN          (1 << 31)  /* Mstop15 On Wen */

/* CPG CLKSTATUS0 Register Bit Definitions ***************************/

#define CPG_CLKSTATUS0_DDIV0CTL0_STS            (1 << 0)  /* Ddiv0Ctl0 Sts */

#define CPG_CLKSTATUS0_DDIV0CTL1_STS            (1 << 1)  /* Ddiv0Ctl1 Sts */

#define CPG_CLKSTATUS0_DDIV0CTL2_STS            (1 << 2)  /* Ddiv0Ctl2 Sts */

#define CPG_CLKSTATUS0_DDIV0CTL3_STS            (1 << 3)  /* Ddiv0Ctl3 Sts */

#define CPG_CLKSTATUS0_DDIV1CTL0_STS            (1 << 4)  /* Ddiv1Ctl0 Sts */

#define CPG_CLKSTATUS0_DDIV1CTL1_STS            (1 << 5)  /* Ddiv1Ctl1 Sts */

#define CPG_CLKSTATUS0_DDIV1CTL2_STS            (1 << 6)  /* Ddiv1Ctl2 Sts */

#define CPG_CLKSTATUS0_DDIV1CTL3_STS            (1 << 7)  /* Ddiv1Ctl3 Sts */

#define CPG_CLKSTATUS0_DDIV2CTL0_STS            (1 << 8)  /* Ddiv2Ctl0 Sts */

#define CPG_CLKSTATUS0_DDIV2CTL1_STS            (1 << 9)  /* Ddiv2Ctl1 Sts */

#define CPG_CLKSTATUS0_DDIV2CTL2_STS            (1 << 10)  /* Ddiv2Ctl2 Sts */

#define CPG_CLKSTATUS0_DDIV2CTL3_STS            (1 << 11)  /* Ddiv2Ctl3 Sts */

#define CPG_CLKSTATUS0_DDIV3CTL0_STS            (1 << 12)  /* Ddiv3Ctl0 Sts */

#define CPG_CLKSTATUS0_DDIV3CTL1_STS            (1 << 13)  /* Ddiv3Ctl1 Sts */

#define CPG_CLKSTATUS0_DDIV3CTL2_STS            (1 << 14)  /* Ddiv3Ctl2 Sts */

#define CPG_CLKSTATUS0_DDIV3CTL3_STS            (1 << 15)  /* Ddiv3Ctl3 Sts */

#define CPG_CLKSTATUS0_DDIV4CTL0_STS            (1 << 16)  /* Ddiv4Ctl0 Sts */

#define CPG_CLKSTATUS0_DDIV4CTL1_STS            (1 << 17)  /* Ddiv4Ctl1 Sts */

#define CPG_CLKSTATUS0_DDIV4CTL2_STS            (1 << 18)  /* Ddiv4Ctl2 Sts */

/* CPG CLMA0_CTL Register Bit Definitions ****************************/

#define CPG_CLMA0_CTL_PRESETZ                   (1 << 0)  /* Presetz */

#define CPG_CLMA0_CTL_CLMATMONRESZ              (1 << 1)  /* Clmatmonresz */

#define CPG_CLMA0_CTL_CLMATSMPRESZ              (1 << 2)  /* Clmatsmpresz */

#define CPG_CLMA0_CTL_CLMATCSEL                 (1 << 3)  /* Clmatcsel */

#define CPG_CLMA0_CTL_CLMATEN                   (1 << 4)  /* Clmaten */

#define CPG_CLMA0_CTL_PRESETZ_WEN               (1 << 16)  /* Presetz Wen */

#define CPG_CLMA0_CTL_CLMATMONRESZ_WEN          (1 << 17)  /* Clmatmonresz Wen */

#define CPG_CLMA0_CTL_CLMATSMPRESZ_WEN          (1 << 18)  /* Clmatsmpresz Wen */

#define CPG_CLMA0_CTL_CLMATCSEL_WEN             (1 << 19)  /* Clmatcsel Wen */

#define CPG_CLMA0_CTL_CLMATEN_WEN               (1 << 20)  /* Clmaten Wen */

/* CPG CLMA10_CTL Register Bit Definitions ***************************/

#define CPG_CLMA10_CTL_PRESETZ                  (1 << 0)  /* Presetz */

#define CPG_CLMA10_CTL_CLMATMONRESZ             (1 << 1)  /* Clmatmonresz */

#define CPG_CLMA10_CTL_CLMATSMPRESZ             (1 << 2)  /* Clmatsmpresz */

#define CPG_CLMA10_CTL_CLMATCSEL                (1 << 3)  /* Clmatcsel */

#define CPG_CLMA10_CTL_CLMATEN                  (1 << 4)  /* Clmaten */

#define CPG_CLMA10_CTL_PRESETZ_WEN              (1 << 16)  /* Presetz Wen */

#define CPG_CLMA10_CTL_CLMATMONRESZ_WEN         (1 << 17)  /* Clmatmonresz Wen */

#define CPG_CLMA10_CTL_CLMATSMPRESZ_WEN         (1 << 18)  /* Clmatsmpresz Wen */

#define CPG_CLMA10_CTL_CLMATCSEL_WEN            (1 << 19)  /* Clmatcsel Wen */

#define CPG_CLMA10_CTL_CLMATEN_WEN              (1 << 20)  /* Clmaten Wen */

/* CPG CLMA11_CTL Register Bit Definitions ***************************/

#define CPG_CLMA11_CTL_PRESETZ                  (1 << 0)  /* Presetz */

#define CPG_CLMA11_CTL_CLMATMONRESZ             (1 << 1)  /* Clmatmonresz */

#define CPG_CLMA11_CTL_CLMATSMPRESZ             (1 << 2)  /* Clmatsmpresz */

#define CPG_CLMA11_CTL_CLMATCSEL                (1 << 3)  /* Clmatcsel */

#define CPG_CLMA11_CTL_CLMATEN                  (1 << 4)  /* Clmaten */

#define CPG_CLMA11_CTL_PRESETZ_WEN              (1 << 16)  /* Presetz Wen */

#define CPG_CLMA11_CTL_CLMATMONRESZ_WEN         (1 << 17)  /* Clmatmonresz Wen */

#define CPG_CLMA11_CTL_CLMATSMPRESZ_WEN         (1 << 18)  /* Clmatsmpresz Wen */

#define CPG_CLMA11_CTL_CLMATCSEL_WEN            (1 << 19)  /* Clmatcsel Wen */

#define CPG_CLMA11_CTL_CLMATEN_WEN              (1 << 20)  /* Clmaten Wen */

/* CPG CLMA12_CTL Register Bit Definitions ***************************/

#define CPG_CLMA12_CTL_PRESETZ                  (1 << 0)  /* Presetz */

#define CPG_CLMA12_CTL_CLMATMONRESZ             (1 << 1)  /* Clmatmonresz */

#define CPG_CLMA12_CTL_CLMATSMPRESZ             (1 << 2)  /* Clmatsmpresz */

#define CPG_CLMA12_CTL_CLMATCSEL                (1 << 3)  /* Clmatcsel */

#define CPG_CLMA12_CTL_CLMATEN                  (1 << 4)  /* Clmaten */

#define CPG_CLMA12_CTL_PRESETZ_WEN              (1 << 16)  /* Presetz Wen */

#define CPG_CLMA12_CTL_CLMATMONRESZ_WEN         (1 << 17)  /* Clmatmonresz Wen */

#define CPG_CLMA12_CTL_CLMATSMPRESZ_WEN         (1 << 18)  /* Clmatsmpresz Wen */

#define CPG_CLMA12_CTL_CLMATCSEL_WEN            (1 << 19)  /* Clmatcsel Wen */

#define CPG_CLMA12_CTL_CLMATEN_WEN              (1 << 20)  /* Clmaten Wen */

/* CPG CLMA13_CTL Register Bit Definitions ***************************/

#define CPG_CLMA13_CTL_PRESETZ                  (1 << 0)  /* Presetz */

#define CPG_CLMA13_CTL_CLMATMONRESZ             (1 << 1)  /* Clmatmonresz */

#define CPG_CLMA13_CTL_CLMATSMPRESZ             (1 << 2)  /* Clmatsmpresz */

#define CPG_CLMA13_CTL_CLMATCSEL                (1 << 3)  /* Clmatcsel */

#define CPG_CLMA13_CTL_CLMATEN                  (1 << 4)  /* Clmaten */

#define CPG_CLMA13_CTL_PRESETZ_WEN              (1 << 16)  /* Presetz Wen */

#define CPG_CLMA13_CTL_CLMATMONRESZ_WEN         (1 << 17)  /* Clmatmonresz Wen */

#define CPG_CLMA13_CTL_CLMATSMPRESZ_WEN         (1 << 18)  /* Clmatsmpresz Wen */

#define CPG_CLMA13_CTL_CLMATCSEL_WEN            (1 << 19)  /* Clmatcsel Wen */

#define CPG_CLMA13_CTL_CLMATEN_WEN              (1 << 20)  /* Clmaten Wen */

/* CPG CLMA14_CTL Register Bit Definitions ***************************/

#define CPG_CLMA14_CTL_PRESETZ                  (1 << 0)  /* Presetz */

#define CPG_CLMA14_CTL_CLMATMONRESZ             (1 << 1)  /* Clmatmonresz */

#define CPG_CLMA14_CTL_CLMATSMPRESZ             (1 << 2)  /* Clmatsmpresz */

#define CPG_CLMA14_CTL_CLMATCSEL                (1 << 3)  /* Clmatcsel */

#define CPG_CLMA14_CTL_CLMATEN                  (1 << 4)  /* Clmaten */

#define CPG_CLMA14_CTL_PRESETZ_WEN              (1 << 16)  /* Presetz Wen */

#define CPG_CLMA14_CTL_CLMATMONRESZ_WEN         (1 << 17)  /* Clmatmonresz Wen */

#define CPG_CLMA14_CTL_CLMATSMPRESZ_WEN         (1 << 18)  /* Clmatsmpresz Wen */

#define CPG_CLMA14_CTL_CLMATCSEL_WEN            (1 << 19)  /* Clmatcsel Wen */

#define CPG_CLMA14_CTL_CLMATEN_WEN              (1 << 20)  /* Clmaten Wen */

/* CPG CLMA1_CTL Register Bit Definitions ****************************/

#define CPG_CLMA1_CTL_PRESETZ                   (1 << 0)  /* Presetz */

#define CPG_CLMA1_CTL_CLMATMONRESZ              (1 << 1)  /* Clmatmonresz */

#define CPG_CLMA1_CTL_CLMATSMPRESZ              (1 << 2)  /* Clmatsmpresz */

#define CPG_CLMA1_CTL_CLMATCSEL                 (1 << 3)  /* Clmatcsel */

#define CPG_CLMA1_CTL_CLMATEN                   (1 << 4)  /* Clmaten */

#define CPG_CLMA1_CTL_PRESETZ_WEN               (1 << 16)  /* Presetz Wen */

#define CPG_CLMA1_CTL_CLMATMONRESZ_WEN          (1 << 17)  /* Clmatmonresz Wen */

#define CPG_CLMA1_CTL_CLMATSMPRESZ_WEN          (1 << 18)  /* Clmatsmpresz Wen */

#define CPG_CLMA1_CTL_CLMATCSEL_WEN             (1 << 19)  /* Clmatcsel Wen */

#define CPG_CLMA1_CTL_CLMATEN_WEN               (1 << 20)  /* Clmaten Wen */

/* CPG CLMA2_CTL Register Bit Definitions ****************************/

#define CPG_CLMA2_CTL_PRESETZ                   (1 << 0)  /* Presetz */

#define CPG_CLMA2_CTL_CLMATMONRESZ              (1 << 1)  /* Clmatmonresz */

#define CPG_CLMA2_CTL_CLMATSMPRESZ              (1 << 2)  /* Clmatsmpresz */

#define CPG_CLMA2_CTL_CLMATCSEL                 (1 << 3)  /* Clmatcsel */

#define CPG_CLMA2_CTL_CLMATEN                   (1 << 4)  /* Clmaten */

#define CPG_CLMA2_CTL_PRESETZ_WEN               (1 << 16)  /* Presetz Wen */

#define CPG_CLMA2_CTL_CLMATMONRESZ_WEN          (1 << 17)  /* Clmatmonresz Wen */

#define CPG_CLMA2_CTL_CLMATSMPRESZ_WEN          (1 << 18)  /* Clmatsmpresz Wen */

#define CPG_CLMA2_CTL_CLMATCSEL_WEN             (1 << 19)  /* Clmatcsel Wen */

#define CPG_CLMA2_CTL_CLMATEN_WEN               (1 << 20)  /* Clmaten Wen */

/* CPG CLMA3_CTL Register Bit Definitions ****************************/

#define CPG_CLMA3_CTL_PRESETZ                   (1 << 0)  /* Presetz */

#define CPG_CLMA3_CTL_CLMATMONRESZ              (1 << 1)  /* Clmatmonresz */

#define CPG_CLMA3_CTL_CLMATSMPRESZ              (1 << 2)  /* Clmatsmpresz */

#define CPG_CLMA3_CTL_CLMATCSEL                 (1 << 3)  /* Clmatcsel */

#define CPG_CLMA3_CTL_CLMATEN                   (1 << 4)  /* Clmaten */

#define CPG_CLMA3_CTL_PRESETZ_WEN               (1 << 16)  /* Presetz Wen */

#define CPG_CLMA3_CTL_CLMATMONRESZ_WEN          (1 << 17)  /* Clmatmonresz Wen */

#define CPG_CLMA3_CTL_CLMATSMPRESZ_WEN          (1 << 18)  /* Clmatsmpresz Wen */

#define CPG_CLMA3_CTL_CLMATCSEL_WEN             (1 << 19)  /* Clmatcsel Wen */

#define CPG_CLMA3_CTL_CLMATEN_WEN               (1 << 20)  /* Clmaten Wen */

/* CPG CLMA4_CTL Register Bit Definitions ****************************/

#define CPG_CLMA4_CTL_PRESETZ                   (1 << 0)  /* Presetz */

#define CPG_CLMA4_CTL_CLMATMONRESZ              (1 << 1)  /* Clmatmonresz */

#define CPG_CLMA4_CTL_CLMATSMPRESZ              (1 << 2)  /* Clmatsmpresz */

#define CPG_CLMA4_CTL_CLMATCSEL                 (1 << 3)  /* Clmatcsel */

#define CPG_CLMA4_CTL_CLMATEN                   (1 << 4)  /* Clmaten */

#define CPG_CLMA4_CTL_PRESETZ_WEN               (1 << 16)  /* Presetz Wen */

#define CPG_CLMA4_CTL_CLMATMONRESZ_WEN          (1 << 17)  /* Clmatmonresz Wen */

#define CPG_CLMA4_CTL_CLMATSMPRESZ_WEN          (1 << 18)  /* Clmatsmpresz Wen */

#define CPG_CLMA4_CTL_CLMATCSEL_WEN             (1 << 19)  /* Clmatcsel Wen */

#define CPG_CLMA4_CTL_CLMATEN_WEN               (1 << 20)  /* Clmaten Wen */

/* CPG CLMA5_CTL Register Bit Definitions ****************************/

#define CPG_CLMA5_CTL_PRESETZ                   (1 << 0)  /* Presetz */

#define CPG_CLMA5_CTL_CLMATMONRESZ              (1 << 1)  /* Clmatmonresz */

#define CPG_CLMA5_CTL_CLMATSMPRESZ              (1 << 2)  /* Clmatsmpresz */

#define CPG_CLMA5_CTL_CLMATCSEL                 (1 << 3)  /* Clmatcsel */

#define CPG_CLMA5_CTL_CLMATEN                   (1 << 4)  /* Clmaten */

#define CPG_CLMA5_CTL_PRESETZ_WEN               (1 << 16)  /* Presetz Wen */

#define CPG_CLMA5_CTL_CLMATMONRESZ_WEN          (1 << 17)  /* Clmatmonresz Wen */

#define CPG_CLMA5_CTL_CLMATSMPRESZ_WEN          (1 << 18)  /* Clmatsmpresz Wen */

#define CPG_CLMA5_CTL_CLMATCSEL_WEN             (1 << 19)  /* Clmatcsel Wen */

#define CPG_CLMA5_CTL_CLMATEN_WEN               (1 << 20)  /* Clmaten Wen */

/* CPG CLMA6_CTL Register Bit Definitions ****************************/

#define CPG_CLMA6_CTL_PRESETZ                   (1 << 0)  /* Presetz */

#define CPG_CLMA6_CTL_CLMATMONRESZ              (1 << 1)  /* Clmatmonresz */

#define CPG_CLMA6_CTL_CLMATSMPRESZ              (1 << 2)  /* Clmatsmpresz */

#define CPG_CLMA6_CTL_CLMATCSEL                 (1 << 3)  /* Clmatcsel */

#define CPG_CLMA6_CTL_CLMATEN                   (1 << 4)  /* Clmaten */

#define CPG_CLMA6_CTL_PRESETZ_WEN               (1 << 16)  /* Presetz Wen */

#define CPG_CLMA6_CTL_CLMATMONRESZ_WEN          (1 << 17)  /* Clmatmonresz Wen */

#define CPG_CLMA6_CTL_CLMATSMPRESZ_WEN          (1 << 18)  /* Clmatsmpresz Wen */

#define CPG_CLMA6_CTL_CLMATCSEL_WEN             (1 << 19)  /* Clmatcsel Wen */

#define CPG_CLMA6_CTL_CLMATEN_WEN               (1 << 20)  /* Clmaten Wen */

/* CPG CLMA7_CTL Register Bit Definitions ****************************/

#define CPG_CLMA7_CTL_PRESETZ                   (1 << 0)  /* Presetz */

#define CPG_CLMA7_CTL_CLMATMONRESZ              (1 << 1)  /* Clmatmonresz */

#define CPG_CLMA7_CTL_CLMATSMPRESZ              (1 << 2)  /* Clmatsmpresz */

#define CPG_CLMA7_CTL_CLMATCSEL                 (1 << 3)  /* Clmatcsel */

#define CPG_CLMA7_CTL_CLMATEN                   (1 << 4)  /* Clmaten */

#define CPG_CLMA7_CTL_PRESETZ_WEN               (1 << 16)  /* Presetz Wen */

#define CPG_CLMA7_CTL_CLMATMONRESZ_WEN          (1 << 17)  /* Clmatmonresz Wen */

#define CPG_CLMA7_CTL_CLMATSMPRESZ_WEN          (1 << 18)  /* Clmatsmpresz Wen */

#define CPG_CLMA7_CTL_CLMATCSEL_WEN             (1 << 19)  /* Clmatcsel Wen */

#define CPG_CLMA7_CTL_CLMATEN_WEN               (1 << 20)  /* Clmaten Wen */

/* CPG CLMA8_CTL Register Bit Definitions ****************************/

#define CPG_CLMA8_CTL_PRESETZ                   (1 << 0)  /* Presetz */

#define CPG_CLMA8_CTL_CLMATMONRESZ              (1 << 1)  /* Clmatmonresz */

#define CPG_CLMA8_CTL_CLMATSMPRESZ              (1 << 2)  /* Clmatsmpresz */

#define CPG_CLMA8_CTL_CLMATCSEL                 (1 << 3)  /* Clmatcsel */

#define CPG_CLMA8_CTL_CLMATEN                   (1 << 4)  /* Clmaten */

#define CPG_CLMA8_CTL_PRESETZ_WEN               (1 << 16)  /* Presetz Wen */

#define CPG_CLMA8_CTL_CLMATMONRESZ_WEN          (1 << 17)  /* Clmatmonresz Wen */

#define CPG_CLMA8_CTL_CLMATSMPRESZ_WEN          (1 << 18)  /* Clmatsmpresz Wen */

#define CPG_CLMA8_CTL_CLMATCSEL_WEN             (1 << 19)  /* Clmatcsel Wen */

#define CPG_CLMA8_CTL_CLMATEN_WEN               (1 << 20)  /* Clmaten Wen */

/* CPG CLMA9_CTL Register Bit Definitions ****************************/

#define CPG_CLMA9_CTL_PRESETZ                   (1 << 0)  /* Presetz */

#define CPG_CLMA9_CTL_CLMATMONRESZ              (1 << 1)  /* Clmatmonresz */

#define CPG_CLMA9_CTL_CLMATSMPRESZ              (1 << 2)  /* Clmatsmpresz */

#define CPG_CLMA9_CTL_CLMATCSEL                 (1 << 3)  /* Clmatcsel */

#define CPG_CLMA9_CTL_CLMATEN                   (1 << 4)  /* Clmaten */

#define CPG_CLMA9_CTL_PRESETZ_WEN               (1 << 16)  /* Presetz Wen */

#define CPG_CLMA9_CTL_CLMATMONRESZ_WEN          (1 << 17)  /* Clmatmonresz Wen */

#define CPG_CLMA9_CTL_CLMATSMPRESZ_WEN          (1 << 18)  /* Clmatsmpresz Wen */

#define CPG_CLMA9_CTL_CLMATCSEL_WEN             (1 << 19)  /* Clmatcsel Wen */

#define CPG_CLMA9_CTL_CLMATEN_WEN               (1 << 20)  /* Clmaten Wen */

/* CPG CLMA_MON Register Bit Definitions *****************************/

/* CLMATENMON fields (parameterized for indices 0-14) */
#define CPG_CLMA_MON_CLMATENMON(n)                        (1u << (0 + ((unsigned)(n) * 1)))  /* Clmatenmon0 */

/* CPG CM33_CTL Register Bit Definitions *****************************/

#define CPG_CM33_CTL_CM33_BOOTCTL               (1 << 0)  /* Cm33 Bootctl */

/* CPG CR8_CONFIG1 Register Bit Definitions **************************/

#define CPG_CR8_CONFIG1_nCPUHALT_SHIFT          (0)      /* Bits 0-1: Ncpuhalt */
#define CPG_CR8_CONFIG1_nCPUHALT_MASK           (0x3 << CPG_CR8_CONFIG1_nCPUHALT_SHIFT)

/* CPG CR8_CORESTATUS Register Bit Definitions ***********************/

#define CPG_CR8_CORESTATUS_STANDBYWFI_SHIFT     (16)      /* Bits 16-17: Standbywfi */
#define CPG_CR8_CORESTATUS_STANDBYWFI_MASK      (0x3 << CPG_CR8_CORESTATUS_STANDBYWFI_SHIFT)

#define CPG_CR8_CORESTATUS_STANDBYWFE_SHIFT     (18)      /* Bits 18-19: Standbywfe */
#define CPG_CR8_CORESTATUS_STANDBYWFE_MASK      (0x3 << CPG_CR8_CORESTATUS_STANDBYWFE_SHIFT)

/* CPG LP_CA55_CTL1 Register Bit Definitions *************************/

#define CPG_LP_CA55_CTL1_CLUSTERPREQ            (1 << 0)  /* Clusterpreq */

#define CPG_LP_CA55_CTL1_CLUSTERPSTATE_SHIFT    (1)      /* Bits 1-7: Clusterpstate */
#define CPG_LP_CA55_CTL1_CLUSTERPSTATE_MASK     (0x7f << CPG_LP_CA55_CTL1_CLUSTERPSTATE_SHIFT)

#define CPG_LP_CA55_CTL1_CLUSTERPDENY           (1 << 8)  /* Clusterpdeny */

#define CPG_LP_CA55_CTL1_CLUSTERPACCEPT         (1 << 9)  /* Clusterpaccept */

/* CPG LP_CA55_CTL2 Register Bit Definitions *************************/

#define CPG_LP_CA55_CTL2_COREPREQ0              (1 << 0)  /* Corepreq0 */

#define CPG_LP_CA55_CTL2_COREPSTATE0_SHIFT      (1)      /* Bits 1-6: Corepstate0 */
#define CPG_LP_CA55_CTL2_COREPSTATE0_MASK       (0x3f << CPG_LP_CA55_CTL2_COREPSTATE0_SHIFT)

#define CPG_LP_CA55_CTL2_COREPDENY0             (1 << 7)  /* Corepdeny0 */

#define CPG_LP_CA55_CTL2_COREPACCEPT0           (1 << 8)  /* Corepaccept0 */

#define CPG_LP_CA55_CTL2_COREPREQ1              (1 << 16)  /* Corepreq1 */

#define CPG_LP_CA55_CTL2_COREPSTATE1_SHIFT      (17)      /* Bits 17-22: Corepstate1 */
#define CPG_LP_CA55_CTL2_COREPSTATE1_MASK       (0x3f << CPG_LP_CA55_CTL2_COREPSTATE1_SHIFT)

#define CPG_LP_CA55_CTL2_COREPDENY1             (1 << 23)  /* Corepdeny1 */

#define CPG_LP_CA55_CTL2_COREPACCEPT1           (1 << 24)  /* Corepaccept1 */

/* CPG LP_CA55_CTL3 Register Bit Definitions *************************/

#define CPG_LP_CA55_CTL3_COREPREQ2              (1 << 0)  /* Corepreq2 */

#define CPG_LP_CA55_CTL3_COREPSTATE2_SHIFT      (1)      /* Bits 1-6: Corepstate2 */
#define CPG_LP_CA55_CTL3_COREPSTATE2_MASK       (0x3f << CPG_LP_CA55_CTL3_COREPSTATE2_SHIFT)

#define CPG_LP_CA55_CTL3_COREPDENY2             (1 << 7)  /* Corepdeny2 */

#define CPG_LP_CA55_CTL3_COREPACCEPT2           (1 << 8)  /* Corepaccept2 */

#define CPG_LP_CA55_CTL3_COREPREQ3              (1 << 16)  /* Corepreq3 */

#define CPG_LP_CA55_CTL3_COREPSTATE3_SHIFT      (17)      /* Bits 17-22: Corepstate3 */
#define CPG_LP_CA55_CTL3_COREPSTATE3_MASK       (0x3f << CPG_LP_CA55_CTL3_COREPSTATE3_SHIFT)

#define CPG_LP_CA55_CTL3_COREPDENY3             (1 << 23)  /* Corepdeny3 */

#define CPG_LP_CA55_CTL3_COREPACCEPT3           (1 << 24)  /* Corepaccept3 */

/* CPG LP_CA55_CTL6 Register Bit Definitions *************************/

#define CPG_LP_CA55_CTL6_COREINSTRRUN_SHIFT     (0)      /* Bits 0-3: Coreinstrrun */
#define CPG_LP_CA55_CTL6_COREINSTRRUN_MASK      (0xf << CPG_LP_CA55_CTL6_COREINSTRRUN_SHIFT)

/* CPG LP_CA55_CTL7 Register Bit Definitions *************************/

/* CSYSACK_AT_ fields (parameterized for indices 0-3) */
#define CPG_LP_CA55_CTL7_CSYSACK_AT(n)                    (1u << (8 + ((unsigned)(n) * 1)))  /* Csysack At0 */

/* CSYSREQ_AT_ fields (parameterized for indices 0-3) */
#define CPG_LP_CA55_CTL7_CSYSREQ_AT(n)                    (1u << (16 + ((unsigned)(n) * 1)))  /* Csysreq At0 */

#define CPG_LP_CA55_CTL7_CSYSACK_TS             (1 << 12)  /* Csysack Ts */

#define CPG_LP_CA55_CTL7_CSYSREQ_TS             (1 << 20)  /* Csysreq Ts */

/* CPG LP_CM33CTL0 Register Bit Definitions **************************/

#define CPG_LP_CM33CTL0_CM33_LP_CTL0            (1 << 0)  /* Cm33 Lp Ctl0 */

#define CPG_LP_CM33CTL0_CM33_LP_CTL4            (1 << 4)  /* Cm33 Lp Ctl4 */

#define CPG_LP_CM33CTL0_CM33_WARMRESETREQ       (1 << 9)  /* Cm33 Warmresetreq */

#define CPG_LP_CM33CTL0_CM33_LP_CTL24           (1 << 24)  /* Cm33 Lp Ctl24 */

#define CPG_LP_CM33CTL0_CM33_LP_CTL25           (1 << 25)  /* Cm33 Lp Ctl25 */

/* CPG LP_CM33CTL1 Register Bit Definitions **************************/

#define CPG_LP_CM33CTL1_CM33_LP_QCH3            (1 << 3)  /* Cm33 Lp Qch3 */

#define CPG_LP_CM33CTL1_CM33_LP_QCH4            (1 << 4)  /* Cm33 Lp Qch4 */

#define CPG_LP_CM33CTL1_CM33_LP_QCH12           (1 << 12)  /* Cm33 Lp Qch12 */

#define CPG_LP_CM33CTL1_CM33_LP_QCH13           (1 << 13)  /* Cm33 Lp Qch13 */

#define CPG_LP_CM33CTL1_Reserved5               (1 << 16)  /* Reserved5 */

#define CPG_LP_CM33CTL1_CM33_LP_QCH20           (1 << 20)  /* Cm33 Lp Qch20 */

#define CPG_LP_CM33CTL1_CM33_LP_QCH21           (1 << 21)  /* Cm33 Lp Qch21 */

#define CPG_LP_CM33CTL1_Reserved7               (1 << 24)  /* Reserved7 */

#define CPG_LP_CM33CTL1_CM33_LP_QCH28           (1 << 28)  /* Cm33 Lp Qch28 */

#define CPG_LP_CM33CTL1_CM33_LP_QCH29           (1 << 29)  /* Cm33 Lp Qch29 */

/* CPG LP_CR8_CTL3 Register Bit Definitions **************************/

#define CPG_LP_CR8_CTL3_CSYSACK_ATB0_DATA       (1 << 8)  /* Csysack Atb0 Data */

#define CPG_LP_CR8_CTL3_CSYSACK_ATB0_INST       (1 << 9)  /* Csysack Atb0 Inst */

#define CPG_LP_CR8_CTL3_CSYSACK_ATB1_DATA       (1 << 10)  /* Csysack Atb1 Data */

#define CPG_LP_CR8_CTL3_CSYSACK_ATB1_INST       (1 << 11)  /* Csysack Atb1 Inst */

#define CPG_LP_CR8_CTL3_CSYSACK_DBG             (1 << 12)  /* Csysack Dbg */

#define CPG_LP_CR8_CTL3_CSYSACK_TS              (1 << 13)  /* Csysack Ts */

#define CPG_LP_CR8_CTL3_CSYSREQ_ATB0_DATA       (1 << 16)  /* Csysreq Atb0 Data */

#define CPG_LP_CR8_CTL3_CSYSREQ_ATB0_INST       (1 << 17)  /* Csysreq Atb0 Inst */

#define CPG_LP_CR8_CTL3_CSYSREQ_ATB1_DATA       (1 << 18)  /* Csysreq Atb1 Data */

#define CPG_LP_CR8_CTL3_CSYSREQ_ATB1_INST       (1 << 19)  /* Csysreq Atb1 Inst */

#define CPG_LP_CR8_CTL3_CSYSREQ_DBG             (1 << 20)  /* Csysreq Dbg */

#define CPG_LP_CR8_CTL3_CSYSREQ_TS              (1 << 21)  /* Csysreq Ts */

/* CPG LP_CR8_CTL4 Register Bit Definitions **************************/

#define CPG_LP_CR8_CTL4_POWERUP_ACT             (1 << 0)  /* Powerup Act */

#define CPG_LP_CR8_CTL4_RESET_RELEASEREQ        (1 << 3)  /* Reset Releasereq */

#define CPG_LP_CR8_CTL4_RESET_CTRL_READY        (1 << 4)  /* Reset Ctrl Ready */

#define CPG_LP_CR8_CTL4_RESET_TRIG              (1 << 5)  /* Reset Trig */

/* CPG LP_GPU_CTL Register Bit Definitions ***************************/

#define CPG_LP_GPU_CTL_QACTIVE_GPU              (1 << 0)  /* Qactive Gpu */

#define CPG_LP_GPU_CTL_QACTIVE_AXI_SLV          (1 << 1)  /* Qactive Axi Slv */

#define CPG_LP_GPU_CTL_QACTIVE_AXI_MST          (1 << 2)  /* Qactive Axi Mst */

#define CPG_LP_GPU_CTL_QACTIVE_ACE_SLV          (1 << 3)  /* Qactive Ace Slv */

#define CPG_LP_GPU_CTL_QACTIVE_ACE_MST          (1 << 4)  /* Qactive Ace Mst */

#define CPG_LP_GPU_CTL_QREQn_GPU                (1 << 8)  /* Qreqn Gpu */

#define CPG_LP_GPU_CTL_QREQn_AXI_SLV            (1 << 9)  /* Qreqn Axi Slv */

#define CPG_LP_GPU_CTL_QREQn_AXI_MST            (1 << 10)  /* Qreqn Axi Mst */

#define CPG_LP_GPU_CTL_QREQn_ACE_SLV            (1 << 11)  /* Qreqn Ace Slv */

#define CPG_LP_GPU_CTL_QREQn_ACE_MST            (1 << 12)  /* Qreqn Ace Mst */

#define CPG_LP_GPU_CTL_QACCEPTn_GPU             (1 << 16)  /* Qacceptn Gpu */

#define CPG_LP_GPU_CTL_QACCEPTn_AXI_SLV         (1 << 17)  /* Qacceptn Axi Slv */

#define CPG_LP_GPU_CTL_QACCEPTn_AXI_MST         (1 << 18)  /* Qacceptn Axi Mst */

#define CPG_LP_GPU_CTL_QACCEPTn_ACE_SLV         (1 << 19)  /* Qacceptn Ace Slv */

#define CPG_LP_GPU_CTL_QACCEPTn_ACE_MST         (1 << 20)  /* Qacceptn Ace Mst */

#define CPG_LP_GPU_CTL_QDENY_GPU                (1 << 24)  /* Qdeny Gpu */

#define CPG_LP_GPU_CTL_QDENY_AXI_SLV            (1 << 25)  /* Qdeny Axi Slv */

#define CPG_LP_GPU_CTL_QDENY_AXI_MST            (1 << 26)  /* Qdeny Axi Mst */

#define CPG_LP_GPU_CTL_QDENY_ACE_SLV            (1 << 27)  /* Qdeny Ace Slv */

#define CPG_LP_GPU_CTL_QDENY_ACE_MST            (1 << 28)  /* Qdeny Ace Mst */

/* CPG LP_PMU_CTL1 Register Bit Definitions **************************/

#define CPG_LP_PMU_CTL1_CTRLREQ                 (1 << 0)  /* Ctrlreq */

#define CPG_LP_PMU_CTL1_PD_OTHERS_REQ           (1 << 1)  /* Pd Others Req */

#define CPG_LP_PMU_CTL1_CTRLACK                 (1 << 2)  /* Ctrlack */

#define CPG_LP_PMU_CTL1_PD_OTHERS_ACK           (1 << 3)  /* Pd Others Ack */

/* CPG OTHERS_INI Register Bit Definitions ***************************/

#define CPG_OTHERS_INI_OTHERS_RST               (1 << 0)  /* Others Rst */

/* CPG OTP_HANDSHAKE_MON Register Bit Definitions ********************/

#define CPG_OTP_HANDSHAKE_MON_DFT_DONE          (1 << 0)  /* Dft Done */

/* CPG PLLCA55_CLK1 Register Bit Definitions *************************/

#define CPG_PLLCA55_CLK1_DIV_P_SHIFT            (0)      /* Bits 0-5: Div P */
#define CPG_PLLCA55_CLK1_DIV_P_MASK             (0x3f << CPG_PLLCA55_CLK1_DIV_P_SHIFT)

#define CPG_PLLCA55_CLK1_DIV_M_SHIFT            (6)      /* Bits 6-15: Div M */
#define CPG_PLLCA55_CLK1_DIV_M_MASK             (0x3ff << CPG_PLLCA55_CLK1_DIV_M_SHIFT)

#define CPG_PLLCA55_CLK1_DIV_K_SHIFT            (16)      /* Bits 16-31: Div K */
#define CPG_PLLCA55_CLK1_DIV_K_MASK             (0xffff << CPG_PLLCA55_CLK1_DIV_K_SHIFT)

/* CPG PLLCA55_CLK2 Register Bit Definitions *************************/

#define CPG_PLLCA55_CLK2_DIV_S_SHIFT            (0)      /* Bits 0-2: Div S */
#define CPG_PLLCA55_CLK2_DIV_S_MASK             (0x7 << CPG_PLLCA55_CLK2_DIV_S_SHIFT)

/* CPG PLLCA55_MON Register Bit Definitions **************************/

#define CPG_PLLCA55_MON_PLLn_RESETB             (1 << 0)  /* Plln Resetb */

#define CPG_PLLCA55_MON_PLLn_LOCK               (1 << 4)  /* Plln Lock */

/* CPG PLLCA55_STBY Register Bit Definitions *************************/

#define CPG_PLLCA55_STBY_RESETB                 (1 << 0)  /* Resetb */

#define CPG_PLLCA55_STBY_SSC_EN                 (1 << 2)  /* Ssc En */

#define CPG_PLLCA55_STBY_RESETB_WEN             (1 << 16)  /* Resetb Wen */

#define CPG_PLLCA55_STBY_SSC_EN_WEN             (1 << 18)  /* Ssc En Wen */

/* CPG PLLCLN_MON Register Bit Definitions ***************************/

#define CPG_PLLCLN_MON_PLLn_RESETB              (1 << 0)  /* Plln Resetb */

#define CPG_PLLCLN_MON_PLLn_LOCK                (1 << 4)  /* Plln Lock */

/* CPG PLLCLN_STBY Register Bit Definitions **************************/

#define CPG_PLLCLN_STBY_RESETB                  (1 << 0)  /* Resetb */

#define CPG_PLLCLN_STBY_SSC_EN                  (1 << 2)  /* Ssc En */

#define CPG_PLLCLN_STBY_RESETB_WEN              (1 << 16)  /* Resetb Wen */

#define CPG_PLLCLN_STBY_SSC_EN_WEN              (1 << 18)  /* Ssc En Wen */

/* CPG PLLCM33_MON Register Bit Definitions **************************/

#define CPG_PLLCM33_MON_PLLn_RESETB             (1 << 0)  /* Plln Resetb */

#define CPG_PLLCM33_MON_PLLn_LOCK               (1 << 4)  /* Plln Lock */

/* CPG PLLDDR0_MON Register Bit Definitions **************************/

#define CPG_PLLDDR0_MON_PLLn_RESETB             (1 << 0)  /* Plln Resetb */

#define CPG_PLLDDR0_MON_PLLn_LOCK               (1 << 4)  /* Plln Lock */

/* CPG PLLDDR0_STBY Register Bit Definitions *************************/

#define CPG_PLLDDR0_STBY_RESETB                 (1 << 0)  /* Resetb */

#define CPG_PLLDDR0_STBY_SSC_EN                 (1 << 2)  /* Ssc En */

#define CPG_PLLDDR0_STBY_RESETB_WEN             (1 << 16)  /* Resetb Wen */

#define CPG_PLLDDR0_STBY_SSC_EN_WEN             (1 << 18)  /* Ssc En Wen */

/* CPG PLLDDR1_MON Register Bit Definitions **************************/

#define CPG_PLLDDR1_MON_PLLn_RESETB             (1 << 0)  /* Plln Resetb */

#define CPG_PLLDDR1_MON_PLLn_LOCK               (1 << 4)  /* Plln Lock */

/* CPG PLLDDR1_STBY Register Bit Definitions *************************/

#define CPG_PLLDDR1_STBY_RESETB                 (1 << 0)  /* Resetb */

#define CPG_PLLDDR1_STBY_SSC_EN                 (1 << 2)  /* Ssc En */

#define CPG_PLLDDR1_STBY_RESETB_WEN             (1 << 16)  /* Resetb Wen */

#define CPG_PLLDDR1_STBY_SSC_EN_WEN             (1 << 18)  /* Ssc En Wen */

/* CPG PLLDRP_MON Register Bit Definitions ***************************/

#define CPG_PLLDRP_MON_PLLn_RESETB              (1 << 0)  /* Plln Resetb */

#define CPG_PLLDRP_MON_PLLn_LOCK                (1 << 4)  /* Plln Lock */

/* CPG PLLDRP_STBY Register Bit Definitions **************************/

#define CPG_PLLDRP_STBY_RESETB                  (1 << 0)  /* Resetb */

#define CPG_PLLDRP_STBY_SSC_EN                  (1 << 2)  /* Ssc En */

#define CPG_PLLDRP_STBY_RESETB_WEN              (1 << 16)  /* Resetb Wen */

#define CPG_PLLDRP_STBY_SSC_EN_WEN              (1 << 18)  /* Ssc En Wen */

/* CPG PLLDSI_MON Register Bit Definitions ***************************/

#define CPG_PLLDSI_MON_PLLn_RESETB              (1 << 0)  /* Plln Resetb */

#define CPG_PLLDSI_MON_PLLn_LOCK                (1 << 4)  /* Plln Lock */

/* CPG PLLDSI_STBY Register Bit Definitions **************************/

#define CPG_PLLDSI_STBY_RESETB                  (1 << 0)  /* Resetb */

#define CPG_PLLDSI_STBY_SSC_EN                  (1 << 2)  /* Ssc En */

#define CPG_PLLDSI_STBY_RESETB_WEN              (1 << 16)  /* Resetb Wen */

#define CPG_PLLDSI_STBY_SSC_EN_WEN              (1 << 18)  /* Ssc En Wen */

/* CPG PLLDTY_MON Register Bit Definitions ***************************/

#define CPG_PLLDTY_MON_PLLn_RESETB              (1 << 0)  /* Plln Resetb */

#define CPG_PLLDTY_MON_PLLn_LOCK                (1 << 4)  /* Plln Lock */

/* CPG PLLDTY_STBY Register Bit Definitions **************************/

#define CPG_PLLDTY_STBY_RESETB                  (1 << 0)  /* Resetb */

#define CPG_PLLDTY_STBY_SSC_EN                  (1 << 2)  /* Ssc En */

#define CPG_PLLDTY_STBY_RESETB_WEN              (1 << 16)  /* Resetb Wen */

#define CPG_PLLDTY_STBY_SSC_EN_WEN              (1 << 18)  /* Ssc En Wen */

/* CPG PLLETH_MON Register Bit Definitions ***************************/

#define CPG_PLLETH_MON_PLLn_RESETB              (1 << 0)  /* Plln Resetb */

#define CPG_PLLETH_MON_PLLn_LOCK                (1 << 4)  /* Plln Lock */

/* CPG PLLETH_STBY Register Bit Definitions **************************/

#define CPG_PLLETH_STBY_RESETB                  (1 << 0)  /* Resetb */

#define CPG_PLLETH_STBY_SSC_EN                  (1 << 2)  /* Ssc En */

#define CPG_PLLETH_STBY_RESETB_WEN              (1 << 16)  /* Resetb Wen */

#define CPG_PLLETH_STBY_SSC_EN_WEN              (1 << 18)  /* Ssc En Wen */

/* CPG PLLGPU_MON Register Bit Definitions ***************************/

#define CPG_PLLGPU_MON_PLLn_RESETB              (1 << 0)  /* Plln Resetb */

#define CPG_PLLGPU_MON_PLLn_LOCK                (1 << 4)  /* Plln Lock */

/* CPG PLLGPU_STBY Register Bit Definitions **************************/

#define CPG_PLLGPU_STBY_RESETB                  (1 << 0)  /* Resetb */

#define CPG_PLLGPU_STBY_SSC_EN                  (1 << 2)  /* Ssc En */

#define CPG_PLLGPU_STBY_RESETB_WEN              (1 << 16)  /* Resetb Wen */

#define CPG_PLLGPU_STBY_SSC_EN_WEN              (1 << 18)  /* Ssc En Wen */

/* CPG PLLVDO_MON Register Bit Definitions ***************************/

#define CPG_PLLVDO_MON_PLLn_RESETB              (1 << 0)  /* Plln Resetb */

#define CPG_PLLVDO_MON_PLLn_LOCK                (1 << 4)  /* Plln Lock */

/* CPG PLLVDO_STBY Register Bit Definitions **************************/

#define CPG_PLLVDO_STBY_RESETB                  (1 << 0)  /* Resetb */

#define CPG_PLLVDO_STBY_SSC_EN                  (1 << 2)  /* Ssc En */

#define CPG_PLLVDO_STBY_RESETB_WEN              (1 << 16)  /* Resetb Wen */

#define CPG_PLLVDO_STBY_SSC_EN_WEN              (1 << 18)  /* Ssc En Wen */

/* CPG Channel definitions */
#define RZV_CPG_CHANNEL_0          0

/* Maximum number of CPG channels */
#define RZV_CPG_MAX_CHANNELS       1

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_CPG_H */

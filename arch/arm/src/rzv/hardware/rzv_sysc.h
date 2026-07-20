/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_sysc.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SYSC_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SYSC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SYSC Base Addresses ***************************************************/

#ifndef RZV_SYSC0_BASE
#  define RZV_SYSC0_BASE              0x10430000
#endif
#ifndef RZV_SYSC_BASE
#  define RZV_SYSC_BASE               RZV_SYSC0_BASE
#endif

/* SYSC Register Offsets **************************************************/

/* SYS_ACPU_CFG_RVAH%s Registers (0-3) */
#define RZV_SYSC_SYS_ACPU_CFG_RVAH_OFFSET(m)    (0x00000628 + ((m) * 0x00000008))  /* SYS_ACPU_CFG_RVAH Register %s */
/* SYS_ACPU_CFG_RVAL%s Registers (0-3) */
#define RZV_SYSC_SYS_ACPU_CFG_RVAL_OFFSET(m)    (0x00000624 + ((m) * 0x00000008))  /* SYS_ACPU_CFG_RVAL Register %s */
/* SYS_GPREG%s Registers (0-3) */
#define RZV_SYSC_SYS_GPREG_OFFSET(m)            (0x00001700 + ((m) * 0x00000004))  /* SYS_GPREG Register %s */
/* SYS_MCPU_CFG%s Registers (2-5) */
#define RZV_SYSC_SYS_MCPU_CFG_OFFSET(m)         (0x0000080c + ((m) * 0x00000004))  /* SYS_MCPU_CFG Register %s */
/* SYS_MSTACCCTL%s Registers (0-18) */
#define RZV_SYSC_SYS_MSTACCCTL_OFFSET(m)        (0x00000000 + ((m) * 0x00000004))  /* SYS_MSTACCCTL Register %s */
/* SYS_PCIE_ACK_CH%s Registers (0-1) */
#define RZV_SYSC_SYS_PCIE_ACK_CH_OFFSET(m)      (0x0000101c + ((m) * 0x00000030))  /* SYS_PCIE_ACK_CH Register %s */
/* SYS_PCIE_INTX_CH%s Registers (0-1) */
#define RZV_SYSC_SYS_PCIE_INTX_CH_OFFSET(m)     (0x00001000 + ((m) * 0x00000030))  /* SYS_PCIE_INTX_CH Register %s */
/* SYS_PCIE_MISC_CH%s Registers (0-1) */
#define RZV_SYSC_SYS_PCIE_MISC_CH_OFFSET(m)     (0x00001020 + ((m) * 0x00000030))  /* SYS_PCIE_MISC_CH Register %s */
/* SYS_PCIE_MODE_CH%s Registers (0-1) */
#define RZV_SYSC_SYS_PCIE_MODE_CH_OFFSET(m)     (0x00001024 + ((m) * 0x00000030))  /* SYS_PCIE_MODE_CH Register %s */
/* SYS_PCIE_PME_CH%s Registers (0-1) */
#define RZV_SYSC_SYS_PCIE_PME_CH_OFFSET(m)      (0x00001018 + ((m) * 0x00000030))  /* SYS_PCIE_PME_CH Register %s */
/* SYS_RCPU_CONFIG%s Registers (1-4) */
#define RZV_SYSC_SYS_RCPU_CONFIG_OFFSET(m)      (0x00000704 + ((m) * 0x00000004))  /* SYS_RCPU_CONFIG Register %s */
/* SYS_SPI_ENDADDCS%s Registers (0-1) */
#define RZV_SYSC_SYS_SPI_ENDADDCS_OFFSET(m)     (0x00000904 + ((m) * 0x00000008))  /* SYS_SPI_ENDADDCS Register %s */
/* SYS_SPI_STAADDCS%s Registers (0-1) */
#define RZV_SYSC_SYS_SPI_STAADDCS_OFFSET(m)     (0x00000900 + ((m) * 0x00000008))  /* SYS_SPI_STAADDCS Register %s */
#define RZV_SYSC_SYS_SLVACCCTL0_OFFSET                   0x0100  /* SYS_SLVACCCTL0 */
#define RZV_SYSC_SYS_SLVACCCTL1_OFFSET                   0x0104  /* SYS_SLVACCCTL1 */
#define RZV_SYSC_SYS_SLVACCCTL2_OFFSET                   0x0108  /* SYS_SLVACCCTL2 */
#define RZV_SYSC_SYS_SLVACCCTL3_OFFSET                   0x010C  /* SYS_SLVACCCTL3 */
#define RZV_SYSC_SYS_SLVACCCTL4_OFFSET                   0x0110  /* SYS_SLVACCCTL4 */
#define RZV_SYSC_SYS_SLVACCCTL5_OFFSET                   0x0114  /* SYS_SLVACCCTL5 */
#define RZV_SYSC_SYS_SLVACCCTL6_OFFSET                   0x0118  /* SYS_SLVACCCTL6 */
#define RZV_SYSC_SYS_SLVACCCTL7_OFFSET                   0x011C  /* SYS_SLVACCCTL7 */
#define RZV_SYSC_SYS_SLVACCCTL8_OFFSET                   0x0120  /* SYS_SLVACCCTL8 */
#define RZV_SYSC_SYS_SLVACCCTL9_OFFSET                   0x0124  /* SYS_SLVACCCTL9 */
#define RZV_SYSC_SYS_SLVACCCTL10_OFFSET                  0x0128  /* SYS_SLVACCCTL10 */
#define RZV_SYSC_SYS_SLVACCCTL11_OFFSET                  0x012C  /* SYS_SLVACCCTL11 */
#define RZV_SYSC_SYS_SLVACCCTL12_OFFSET                  0x0130  /* SYS_SLVACCCTL12 */
#define RZV_SYSC_SYS_SLVACCCTL13_OFFSET                  0x0134  /* SYS_SLVACCCTL13 */
#define RZV_SYSC_SYS_SLVACCCTL14_OFFSET                  0x0138  /* SYS_SLVACCCTL14 */
#define RZV_SYSC_SYS_SLVACCCTL15_OFFSET                  0x013C  /* SYS_SLVACCCTL15 */
#define RZV_SYSC_SYS_SLVACCCTL17_OFFSET                  0x0144  /* SYS_SLVACCCTL17 */
#define RZV_SYSC_SYS_SLVACCCTL19_OFFSET                  0x014C  /* SYS_SLVACCCTL19 */
#define RZV_SYSC_SYS_SLVACCCTL20_OFFSET                  0x0150  /* SYS_SLVACCCTL20 */
#define RZV_SYSC_SYS_SLVACCCTL21_OFFSET                  0x0154  /* SYS_SLVACCCTL21 */
#define RZV_SYSC_SYS_SLVACCCTL22_OFFSET                  0x0158  /* SYS_SLVACCCTL22 */
#define RZV_SYSC_SYS_SLVACCCTL32_OFFSET                  0x0180  /* SYS_SLVACCCTL32 */
#define RZV_SYSC_SYS_SLVACCCTL33_OFFSET                  0x0184  /* SYS_SLVACCCTL33 */
#define RZV_SYSC_SYS_SLVACCCTL35_OFFSET                  0x018C  /* SYS_SLVACCCTL35 */
#define RZV_SYSC_SYS_SLVACCCTL36_OFFSET                  0x0190  /* SYS_SLVACCCTL36 */
#define RZV_SYSC_SYS_SLVACCCTL37_OFFSET                  0x0194  /* SYS_SLVACCCTL37 */
#define RZV_SYSC_SYS_SLVACCCTL38_OFFSET                  0x0198  /* SYS_SLVACCCTL38 */
#define RZV_SYSC_SYS_SLVACCCTL39_OFFSET                  0x019C  /* SYS_SLVACCCTL39 */
#define RZV_SYSC_SYS_SLVACCCTL40_OFFSET                  0x01A0  /* SYS_SLVACCCTL40 */
#define RZV_SYSC_SYS_SLVACCCTL41_OFFSET                  0x01A4  /* SYS_SLVACCCTL41 */
#define RZV_SYSC_SYS_SLVACCCTL43_OFFSET                  0x01AC  /* SYS_SLVACCCTL43 */
#define RZV_SYSC_SYS_SLVACCCTL44_OFFSET                  0x01B0  /* SYS_SLVACCCTL44 */
#define RZV_SYSC_SYS_SLVACCCTL45_OFFSET                  0x01B4  /* SYS_SLVACCCTL45 */
#define RZV_SYSC_SYS_SLVACCCTL46_OFFSET                  0x01B8  /* SYS_SLVACCCTL46 */
#define RZV_SYSC_SYS_SLVACCCTL47_OFFSET                  0x01BC  /* SYS_SLVACCCTL47 */
#define RZV_SYSC_SYS_SLVACCCTL48_OFFSET                  0x01C0  /* SYS_SLVACCCTL48 */
#define RZV_SYSC_SYS_SLVACCCTL49_OFFSET                  0x01C4  /* SYS_SLVACCCTL49 */
#define RZV_SYSC_SYS_SLVACCCTL50_OFFSET                  0x01C8  /* SYS_SLVACCCTL50 */
#define RZV_SYSC_SYS_SLVACCCTL51_OFFSET                  0x01CC  /* SYS_SLVACCCTL51 */
#define RZV_SYSC_SYS_SLVACCCTL52_OFFSET                  0x01D0  /* SYS_SLVACCCTL52 */
#define RZV_SYSC_SYS_SLVACCCTL53_OFFSET                  0x01D4  /* SYS_SLVACCCTL53 */
#define RZV_SYSC_SYS_SLVACCCTL54_OFFSET                  0x01D8  /* SYS_SLVACCCTL54 */
#define RZV_SYSC_SYS_SLVACCCTL55_OFFSET                  0x01DC  /* SYS_SLVACCCTL55 */
#define RZV_SYSC_SYS_SLVACCCTL56_OFFSET                  0x01E0  /* SYS_SLVACCCTL56 */
#define RZV_SYSC_SYS_SLVACCCTL57_OFFSET                  0x01E4  /* SYS_SLVACCCTL57 */
#define RZV_SYSC_SYS_SLVACCCTL58_OFFSET                  0x01E8  /* SYS_SLVACCCTL58 */
#define RZV_SYSC_SYS_SLVACCCTL59_OFFSET                  0x01EC  /* SYS_SLVACCCTL59 */
#define RZV_SYSC_SYS_SLVACCCTL64_OFFSET                  0x0200  /* SYS_SLVACCCTL64 */
#define RZV_SYSC_SYS_SLVACCCTL65_OFFSET                  0x0204  /* SYS_SLVACCCTL65 */
#define RZV_SYSC_SYS_SLVACCCTL66_OFFSET                  0x0208  /* SYS_SLVACCCTL66 */
#define RZV_SYSC_SYS_SLVACCCTL67_OFFSET                  0x020C  /* SYS_SLVACCCTL67 */
#define RZV_SYSC_SYS_SLVACCCTL68_OFFSET                  0x0210  /* SYS_SLVACCCTL68 */
#define RZV_SYSC_SYS_SLVACCCTL80_OFFSET                  0x0240  /* SYS_SLVACCCTL80 */
#define RZV_SYSC_SYS_SLVACCCTL81_OFFSET                  0x0244  /* SYS_SLVACCCTL81 */
#define RZV_SYSC_SYS_SLVACCCTL82_OFFSET                  0x0248  /* SYS_SLVACCCTL82 */
#define RZV_SYSC_SYS_SLVACCCTL88_OFFSET                  0x0260  /* SYS_SLVACCCTL88 */
#define RZV_SYSC_SYS_SLVACCCTL89_OFFSET                  0x0264  /* SYS_SLVACCCTL89 */
#define RZV_SYSC_SYS_SLVACCCTL91_OFFSET                  0x026C  /* SYS_SLVACCCTL91 */
#define RZV_SYSC_SYS_SLVACCCTL92_OFFSET                  0x0270  /* SYS_SLVACCCTL92 */
#define RZV_SYSC_SYS_SLVACCCTL93_OFFSET                  0x0274  /* SYS_SLVACCCTL93 */
#define RZV_SYSC_SYS_LSI_MODE_OFFSET                     0x0300  /* SYS_LSI_MODE */
#define RZV_SYSC_SYS_LSI_DEVID_OFFSET                    0x0304  /* SYS_LSI_DEVID */
#define RZV_SYSC_SYS_LSI_PRR_OFFSET                      0x0308  /* SYS_LSI_PRR */
#define RZV_SYSC_SYS_LSI_OTPTSU0TRMVAL0_OFFSET           0x0320  /* SYS_LSI_OTPTSU0TRMVAL0 */
#define RZV_SYSC_SYS_LSI_OTPTSU0TRMVAL1_OFFSET           0x0324  /* SYS_LSI_OTPTSU0TRMVAL1 */
#define RZV_SYSC_SYS_LSI_OTPTSU1TRMVAL0_OFFSET           0x0330  /* SYS_LSI_OTPTSU1TRMVAL0 */
#define RZV_SYSC_SYS_LSI_OTPTSU1TRMVAL1_OFFSET           0x0334  /* SYS_LSI_OTPTSU1TRMVAL1 */
#define RZV_SYSC_SYS_AOF0_OFFSET                         0x0500  /* SYS_AOF0 */
#define RZV_SYSC_SYS_AOF1_OFFSET                         0x0504  /* SYS_AOF1 */
#define RZV_SYSC_SYS_AOF2_OFFSET                         0x0508  /* SYS_AOF2 */
#define RZV_SYSC_SYS_AOF3_OFFSET                         0x050C  /* SYS_AOF3 */
#define RZV_SYSC_SYS_AOF4_OFFSET                         0x0510  /* SYS_AOF4 */
#define RZV_SYSC_SYS_AOF16_OFFSET                        0x0540  /* SYS_AOF16 */
#define RZV_SYSC_SYS_AOF17_OFFSET                        0x0544  /* SYS_AOF17 */
#define RZV_SYSC_SYS_AOF18_OFFSET                        0x0548  /* SYS_AOF18 */
#define RZV_SYSC_SYS_AOF19_OFFSET                        0x054C  /* SYS_AOF19 */
#define RZV_SYSC_SYS_AOF20_OFFSET                        0x0550  /* SYS_AOF20 */
#define RZV_SYSC_SYS_AOF21_OFFSET                        0x0554  /* SYS_AOF21 */
#define RZV_SYSC_SYS_AOF22_OFFSET                        0x0558  /* SYS_AOF22 */
#define RZV_SYSC_SYS_AOF23_OFFSET                        0x055C  /* SYS_AOF23 */
#define RZV_SYSC_SYS_AOF24_OFFSET                        0x0560  /* SYS_AOF24 */
#define RZV_SYSC_SYS_AOF25_OFFSET                        0x0564  /* SYS_AOF25 */
#define RZV_SYSC_SYS_AOF32_OFFSET                        0x0580  /* SYS_AOF32 */
#define RZV_SYSC_SYS_AOF33_OFFSET                        0x0584  /* SYS_AOF33 */
#define RZV_SYSC_SYS_AOF40_OFFSET                        0x05A0  /* SYS_AOF40 */
#define RZV_SYSC_SYS_AOF41_OFFSET                        0x05A4  /* SYS_AOF41 */
#define RZV_SYSC_SYS_AOF42_OFFSET                        0x05A8  /* SYS_AOF42 */
#define RZV_SYSC_SYS_AOF43_OFFSET                        0x05AC  /* SYS_AOF43 */
#define RZV_SYSC_SYS_AOF48_OFFSET                        0x05C0  /* SYS_AOF48 */
#define RZV_SYSC_SYS_AOF49_OFFSET                        0x05C4  /* SYS_AOF49 */
#define RZV_SYSC_SYS_ACPU_CFG_SMPL_OFFSET                0x0600  /* SYS_ACPU_CFG_SMPL */
#define RZV_SYSC_SYS_ACPU_CFG_SMPH_OFFSET                0x0604  /* SYS_ACPU_CFG_SMPH */
#define RZV_SYSC_SYS_ACPU_CFG_EMPL_OFFSET                0x0608  /* SYS_ACPU_CFG_EMPL */
#define RZV_SYSC_SYS_ACPU_CFG_EMPH_OFFSET                0x060C  /* SYS_ACPU_CFG_EMPH */
#define RZV_SYSC_SYS_RCPU_CORESTATUS_OFFSET              0x071C  /* SYS_RCPU_CORESTATUS */
#define RZV_SYSC_SYS_SRAM0_ECC_OFFSET                    0x0B00  /* SYS_SRAM0_ECC */
#define RZV_SYSC_SYS_SRAM0_EN_OFFSET                     0x0B04  /* SYS_SRAM0_EN */
#define RZV_SYSC_SYS_SRAM1_ECC_OFFSET                    0x0B14  /* SYS_SRAM1_ECC */
#define RZV_SYSC_SYS_SRAM1_EN_OFFSET                     0x0B18  /* SYS_SRAM1_EN */
#define RZV_SYSC_SYS_SRAM2_ECC_OFFSET                    0x0B28  /* SYS_SRAM2_ECC */
#define RZV_SYSC_SYS_SRAM2_EN_OFFSET                     0x0B2C  /* SYS_SRAM2_EN */
#define RZV_SYSC_SYS_SRAM3_ECC_OFFSET                    0x0B3C  /* SYS_SRAM3_ECC */
#define RZV_SYSC_SYS_SRAM3_EN_OFFSET                     0x0B40  /* SYS_SRAM3_EN */
#define RZV_SYSC_SYS_SRAM4_ECC_OFFSET                    0x0B50  /* SYS_SRAM4_ECC */
#define RZV_SYSC_SYS_SRAM4_EN_OFFSET                     0x0B54  /* SYS_SRAM4_EN */
#define RZV_SYSC_SYS_SRAM5_ECC_OFFSET                    0x0B64  /* SYS_SRAM5_ECC */
#define RZV_SYSC_SYS_SRAM5_EN_OFFSET                     0x0B68  /* SYS_SRAM5_EN */
#define RZV_SYSC_SYS_SRAM6_ECC_OFFSET                    0x0B78  /* SYS_SRAM6_ECC */
#define RZV_SYSC_SYS_SRAM6_EN_OFFSET                     0x0B7C  /* SYS_SRAM6_EN */
#define RZV_SYSC_SYS_SRAM7_ECC_OFFSET                    0x0B8C  /* SYS_SRAM7_ECC */
#define RZV_SYSC_SYS_SRAM7_EN_OFFSET                     0x0B90  /* SYS_SRAM7_EN */
#define RZV_SYSC_SYS_SRAM8_ECC_OFFSET                    0x0BA0  /* SYS_SRAM8_ECC */
#define RZV_SYSC_SYS_SRAM8_EN_OFFSET                     0x0BA4  /* SYS_SRAM8_EN */
#define RZV_SYSC_SYS_SRAM9_ECC_OFFSET                    0x0BB4  /* SYS_SRAM9_ECC */
#define RZV_SYSC_SYS_SRAM9_EN_OFFSET                     0x0BB8  /* SYS_SRAM9_EN */
#define RZV_SYSC_SYS_SRAM10_ECC_OFFSET                   0x0BC8  /* SYS_SRAM10_ECC */
#define RZV_SYSC_SYS_SRAM10_EN_OFFSET                    0x0BCC  /* SYS_SRAM10_EN */
#define RZV_SYSC_SYS_SRAM11_ECC_OFFSET                   0x0BDC  /* SYS_SRAM11_ECC */
#define RZV_SYSC_SYS_SRAM11_EN_OFFSET                    0x0BE0  /* SYS_SRAM11_EN */
#define RZV_SYSC_SYS_WDT0_CTRL_OFFSET                    0x0C00  /* SYS_WDT0_CTRL */
#define RZV_SYSC_SYS_WDT2_CTRL_OFFSET                    0x0C04  /* SYS_WDT2_CTRL */
#define RZV_SYSC_SYS_WDT3_CTRL_OFFSET                    0x0C08  /* SYS_WDT3_CTRL */
#define RZV_SYSC_SYS_WDT1_CTRL_OFFSET                    0x0C0C  /* SYS_WDT1_CTRL */
#define RZV_SYSC_SYS_GBETH0_CFG_OFFSET                   0x0F00  /* SYS_GBETH0_CFG */
#define RZV_SYSC_SYS_GBETH1_CFG_OFFSET                   0x0F04  /* SYS_GBETH1_CFG */
#define RZV_SYSC_SYS_PCIE_MSI1_CH0_OFFSET                0x1004  /* SYS_PCIE_MSI1_CH0 */
#define RZV_SYSC_SYS_PCIE_MSI2_CH0_OFFSET                0x1008  /* SYS_PCIE_MSI2_CH0 */
#define RZV_SYSC_SYS_PCIE_MSI3_CH0_OFFSET                0x100C  /* SYS_PCIE_MSI3_CH0 */
#define RZV_SYSC_SYS_PCIE_MSI4_CH0_OFFSET                0x1010  /* SYS_PCIE_MSI4_CH0 */
#define RZV_SYSC_SYS_PCIE_MSI5_CH0_OFFSET                0x1014  /* SYS_PCIE_MSI5_CH0 */
#define RZV_SYSC_SYS_PCIE_MSI1_CH1_OFFSET                0x1034  /* SYS_PCIE_MSI1_CH1 */
#define RZV_SYSC_SYS_PCIE_MSI2_CH1_OFFSET                0x1038  /* SYS_PCIE_MSI2_CH1 */
#define RZV_SYSC_SYS_PCIE_MSI3_CH1_OFFSET                0x103C  /* SYS_PCIE_MSI3_CH1 */
#define RZV_SYSC_SYS_PCIE_MSI4_CH1_OFFSET                0x1040  /* SYS_PCIE_MSI4_CH1 */
#define RZV_SYSC_SYS_PCIE_MSI5_CH1_OFFSET                0x1044  /* SYS_PCIE_MSI5_CH1 */
#define RZV_SYSC_SYS_PCIE_MODE_OFFSET                    0x1060  /* SYS_PCIE_MODE */
#define RZV_SYSC_SYS_ADC_CFG_OFFSET                      0x1600  /* SYS_ADC_CFG */

/* SYSC Register Addresses *************************************************/

#define RZV_SYSC_SYS_ACPU_CFG_RVAH(m)           (RZV_SYSC_BASE + RZV_SYSC_SYS_ACPU_CFG_RVAH_OFFSET(m))
#define RZV_SYSC_SYS_ACPU_CFG_RVAL(m)           (RZV_SYSC_BASE + RZV_SYSC_SYS_ACPU_CFG_RVAL_OFFSET(m))
#define RZV_SYSC_SYS_GPREG(m)                   (RZV_SYSC_BASE + RZV_SYSC_SYS_GPREG_OFFSET(m))
#define RZV_SYSC_SYS_MCPU_CFG(m)                (RZV_SYSC_BASE + RZV_SYSC_SYS_MCPU_CFG_OFFSET(m))
#define RZV_SYSC_SYS_MSTACCCTL(m)               (RZV_SYSC_BASE + RZV_SYSC_SYS_MSTACCCTL_OFFSET(m))
#define RZV_SYSC_SYS_PCIE_ACK_CH(m)             (RZV_SYSC_BASE + RZV_SYSC_SYS_PCIE_ACK_CH_OFFSET(m))
#define RZV_SYSC_SYS_PCIE_INTX_CH(m)            (RZV_SYSC_BASE + RZV_SYSC_SYS_PCIE_INTX_CH_OFFSET(m))
#define RZV_SYSC_SYS_PCIE_MISC_CH(m)            (RZV_SYSC_BASE + RZV_SYSC_SYS_PCIE_MISC_CH_OFFSET(m))
#define RZV_SYSC_SYS_PCIE_MODE_CH(m)            (RZV_SYSC_BASE + RZV_SYSC_SYS_PCIE_MODE_CH_OFFSET(m))
#define RZV_SYSC_SYS_PCIE_PME_CH(m)             (RZV_SYSC_BASE + RZV_SYSC_SYS_PCIE_PME_CH_OFFSET(m))
#define RZV_SYSC_SYS_RCPU_CONFIG(m)             (RZV_SYSC_BASE + RZV_SYSC_SYS_RCPU_CONFIG_OFFSET(m))
#define RZV_SYSC_SYS_SPI_ENDADDCS(m)            (RZV_SYSC_BASE + RZV_SYSC_SYS_SPI_ENDADDCS_OFFSET(m))
#define RZV_SYSC_SYS_SPI_STAADDCS(m)            (RZV_SYSC_BASE + RZV_SYSC_SYS_SPI_STAADDCS_OFFSET(m))
#define RZV_SYSC_SYS_SLVACCCTL0                      (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL0_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL1                      (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL1_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL2                      (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL2_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL3                      (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL3_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL4                      (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL4_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL5                      (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL5_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL6                      (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL6_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL7                      (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL7_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL8                      (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL8_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL9                      (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL9_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL10                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL10_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL11                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL11_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL12                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL12_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL13                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL13_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL14                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL14_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL15                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL15_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL17                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL17_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL19                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL19_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL20                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL20_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL21                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL21_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL22                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL22_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL32                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL32_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL33                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL33_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL35                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL35_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL36                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL36_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL37                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL37_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL38                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL38_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL39                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL39_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL40                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL40_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL41                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL41_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL43                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL43_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL44                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL44_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL45                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL45_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL46                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL46_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL47                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL47_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL48                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL48_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL49                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL49_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL50                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL50_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL51                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL51_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL52                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL52_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL53                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL53_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL54                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL54_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL55                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL55_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL56                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL56_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL57                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL57_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL58                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL58_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL59                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL59_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL64                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL64_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL65                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL65_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL66                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL66_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL67                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL67_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL68                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL68_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL80                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL80_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL81                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL81_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL82                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL82_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL88                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL88_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL89                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL89_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL91                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL91_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL92                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL92_OFFSET)
#define RZV_SYSC_SYS_SLVACCCTL93                     (RZV_SYSC_BASE + RZV_SYSC_SYS_SLVACCCTL93_OFFSET)
#define RZV_SYSC_SYS_LSI_MODE                        (RZV_SYSC_BASE + RZV_SYSC_SYS_LSI_MODE_OFFSET)
#define RZV_SYSC_SYS_LSI_DEVID                       (RZV_SYSC_BASE + RZV_SYSC_SYS_LSI_DEVID_OFFSET)
#define RZV_SYSC_SYS_LSI_PRR                         (RZV_SYSC_BASE + RZV_SYSC_SYS_LSI_PRR_OFFSET)
#define RZV_SYSC_SYS_LSI_OTPTSU0TRMVAL0              (RZV_SYSC_BASE + RZV_SYSC_SYS_LSI_OTPTSU0TRMVAL0_OFFSET)
#define RZV_SYSC_SYS_LSI_OTPTSU0TRMVAL1              (RZV_SYSC_BASE + RZV_SYSC_SYS_LSI_OTPTSU0TRMVAL1_OFFSET)
#define RZV_SYSC_SYS_LSI_OTPTSU1TRMVAL0              (RZV_SYSC_BASE + RZV_SYSC_SYS_LSI_OTPTSU1TRMVAL0_OFFSET)
#define RZV_SYSC_SYS_LSI_OTPTSU1TRMVAL1              (RZV_SYSC_BASE + RZV_SYSC_SYS_LSI_OTPTSU1TRMVAL1_OFFSET)
#define RZV_SYSC_SYS_AOF0                            (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF0_OFFSET)
#define RZV_SYSC_SYS_AOF1                            (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF1_OFFSET)
#define RZV_SYSC_SYS_AOF2                            (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF2_OFFSET)
#define RZV_SYSC_SYS_AOF3                            (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF3_OFFSET)
#define RZV_SYSC_SYS_AOF4                            (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF4_OFFSET)
#define RZV_SYSC_SYS_AOF16                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF16_OFFSET)
#define RZV_SYSC_SYS_AOF17                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF17_OFFSET)
#define RZV_SYSC_SYS_AOF18                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF18_OFFSET)
#define RZV_SYSC_SYS_AOF19                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF19_OFFSET)
#define RZV_SYSC_SYS_AOF20                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF20_OFFSET)
#define RZV_SYSC_SYS_AOF21                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF21_OFFSET)
#define RZV_SYSC_SYS_AOF22                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF22_OFFSET)
#define RZV_SYSC_SYS_AOF23                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF23_OFFSET)
#define RZV_SYSC_SYS_AOF24                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF24_OFFSET)
#define RZV_SYSC_SYS_AOF25                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF25_OFFSET)
#define RZV_SYSC_SYS_AOF32                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF32_OFFSET)
#define RZV_SYSC_SYS_AOF33                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF33_OFFSET)
#define RZV_SYSC_SYS_AOF40                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF40_OFFSET)
#define RZV_SYSC_SYS_AOF41                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF41_OFFSET)
#define RZV_SYSC_SYS_AOF42                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF42_OFFSET)
#define RZV_SYSC_SYS_AOF43                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF43_OFFSET)
#define RZV_SYSC_SYS_AOF48                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF48_OFFSET)
#define RZV_SYSC_SYS_AOF49                           (RZV_SYSC_BASE + RZV_SYSC_SYS_AOF49_OFFSET)
#define RZV_SYSC_SYS_ACPU_CFG_SMPL                   (RZV_SYSC_BASE + RZV_SYSC_SYS_ACPU_CFG_SMPL_OFFSET)
#define RZV_SYSC_SYS_ACPU_CFG_SMPH                   (RZV_SYSC_BASE + RZV_SYSC_SYS_ACPU_CFG_SMPH_OFFSET)
#define RZV_SYSC_SYS_ACPU_CFG_EMPL                   (RZV_SYSC_BASE + RZV_SYSC_SYS_ACPU_CFG_EMPL_OFFSET)
#define RZV_SYSC_SYS_ACPU_CFG_EMPH                   (RZV_SYSC_BASE + RZV_SYSC_SYS_ACPU_CFG_EMPH_OFFSET)
#define RZV_SYSC_SYS_RCPU_CORESTATUS                 (RZV_SYSC_BASE + RZV_SYSC_SYS_RCPU_CORESTATUS_OFFSET)
#define RZV_SYSC_SYS_SRAM0_ECC                       (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM0_ECC_OFFSET)
#define RZV_SYSC_SYS_SRAM0_EN                        (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM0_EN_OFFSET)
#define RZV_SYSC_SYS_SRAM1_ECC                       (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM1_ECC_OFFSET)
#define RZV_SYSC_SYS_SRAM1_EN                        (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM1_EN_OFFSET)
#define RZV_SYSC_SYS_SRAM2_ECC                       (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM2_ECC_OFFSET)
#define RZV_SYSC_SYS_SRAM2_EN                        (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM2_EN_OFFSET)
#define RZV_SYSC_SYS_SRAM3_ECC                       (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM3_ECC_OFFSET)
#define RZV_SYSC_SYS_SRAM3_EN                        (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM3_EN_OFFSET)
#define RZV_SYSC_SYS_SRAM4_ECC                       (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM4_ECC_OFFSET)
#define RZV_SYSC_SYS_SRAM4_EN                        (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM4_EN_OFFSET)
#define RZV_SYSC_SYS_SRAM5_ECC                       (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM5_ECC_OFFSET)
#define RZV_SYSC_SYS_SRAM5_EN                        (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM5_EN_OFFSET)
#define RZV_SYSC_SYS_SRAM6_ECC                       (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM6_ECC_OFFSET)
#define RZV_SYSC_SYS_SRAM6_EN                        (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM6_EN_OFFSET)
#define RZV_SYSC_SYS_SRAM7_ECC                       (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM7_ECC_OFFSET)
#define RZV_SYSC_SYS_SRAM7_EN                        (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM7_EN_OFFSET)
#define RZV_SYSC_SYS_SRAM8_ECC                       (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM8_ECC_OFFSET)
#define RZV_SYSC_SYS_SRAM8_EN                        (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM8_EN_OFFSET)
#define RZV_SYSC_SYS_SRAM9_ECC                       (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM9_ECC_OFFSET)
#define RZV_SYSC_SYS_SRAM9_EN                        (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM9_EN_OFFSET)
#define RZV_SYSC_SYS_SRAM10_ECC                      (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM10_ECC_OFFSET)
#define RZV_SYSC_SYS_SRAM10_EN                       (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM10_EN_OFFSET)
#define RZV_SYSC_SYS_SRAM11_ECC                      (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM11_ECC_OFFSET)
#define RZV_SYSC_SYS_SRAM11_EN                       (RZV_SYSC_BASE + RZV_SYSC_SYS_SRAM11_EN_OFFSET)
#define RZV_SYSC_SYS_WDT0_CTRL                       (RZV_SYSC_BASE + RZV_SYSC_SYS_WDT0_CTRL_OFFSET)
#define RZV_SYSC_SYS_WDT2_CTRL                       (RZV_SYSC_BASE + RZV_SYSC_SYS_WDT2_CTRL_OFFSET)
#define RZV_SYSC_SYS_WDT3_CTRL                       (RZV_SYSC_BASE + RZV_SYSC_SYS_WDT3_CTRL_OFFSET)
#define RZV_SYSC_SYS_WDT1_CTRL                       (RZV_SYSC_BASE + RZV_SYSC_SYS_WDT1_CTRL_OFFSET)

/* SYS_WDTx_CTRL bit definitions (R9A09G057H sysc_iobitmask.h) */

#define SYS_WDT_CTRL_BP_HALTED                       (1u << 0)   /* Halt counter when 1 */
#define SYS_WDT_CTRL_WDTSTOPMASK                     (1u << 16)  /* Independent mask bit (NOT a write-enable): masks the WDT count-stop request during CPU debug/standby */
#define RZV_SYSC_SYS_GBETH0_CFG                      (RZV_SYSC_BASE + RZV_SYSC_SYS_GBETH0_CFG_OFFSET)
#define RZV_SYSC_SYS_GBETH1_CFG                      (RZV_SYSC_BASE + RZV_SYSC_SYS_GBETH1_CFG_OFFSET)
#define RZV_SYSC_SYS_PCIE_MSI1_CH0                   (RZV_SYSC_BASE + RZV_SYSC_SYS_PCIE_MSI1_CH0_OFFSET)
#define RZV_SYSC_SYS_PCIE_MSI2_CH0                   (RZV_SYSC_BASE + RZV_SYSC_SYS_PCIE_MSI2_CH0_OFFSET)
#define RZV_SYSC_SYS_PCIE_MSI3_CH0                   (RZV_SYSC_BASE + RZV_SYSC_SYS_PCIE_MSI3_CH0_OFFSET)
#define RZV_SYSC_SYS_PCIE_MSI4_CH0                   (RZV_SYSC_BASE + RZV_SYSC_SYS_PCIE_MSI4_CH0_OFFSET)
#define RZV_SYSC_SYS_PCIE_MSI5_CH0                   (RZV_SYSC_BASE + RZV_SYSC_SYS_PCIE_MSI5_CH0_OFFSET)
#define RZV_SYSC_SYS_PCIE_MSI1_CH1                   (RZV_SYSC_BASE + RZV_SYSC_SYS_PCIE_MSI1_CH1_OFFSET)
#define RZV_SYSC_SYS_PCIE_MSI2_CH1                   (RZV_SYSC_BASE + RZV_SYSC_SYS_PCIE_MSI2_CH1_OFFSET)
#define RZV_SYSC_SYS_PCIE_MSI3_CH1                   (RZV_SYSC_BASE + RZV_SYSC_SYS_PCIE_MSI3_CH1_OFFSET)
#define RZV_SYSC_SYS_PCIE_MSI4_CH1                   (RZV_SYSC_BASE + RZV_SYSC_SYS_PCIE_MSI4_CH1_OFFSET)
#define RZV_SYSC_SYS_PCIE_MSI5_CH1                   (RZV_SYSC_BASE + RZV_SYSC_SYS_PCIE_MSI5_CH1_OFFSET)
#define RZV_SYSC_SYS_PCIE_MODE                       (RZV_SYSC_BASE + RZV_SYSC_SYS_PCIE_MODE_OFFSET)
#define RZV_SYSC_SYS_ADC_CFG                         (RZV_SYSC_BASE + RZV_SYSC_SYS_ADC_CFG_OFFSET)

/* SYSC SYS_ACPU_CFG_RVAH Register Bit Definitions (Parameterized) *********/

#define SYSC_SYS_ACPU_CFG_RVAH_RVBARADDRH_SHIFT           (0)      /* Bits 0-7: Rvbaraddrh0 */
#define SYSC_SYS_ACPU_CFG_RVAH_RVBARADDRH_MASK(m)         (0xff << SYSC_SYS_ACPU_CFG_RVAH_RVBARADDRH_SHIFT)
#define SYSC_SYS_ACPU_CFG_RVAH_RVBARADDRH(m,val)          (((val) << SYSC_SYS_ACPU_CFG_RVAH_RVBARADDRH_SHIFT) & SYSC_SYS_ACPU_CFG_RVAH_RVBARADDRH_MASK(m))

/* SYSC SYS_ACPU_CFG_RVAL Register Bit Definitions (Parameterized) *********/

#define SYSC_SYS_ACPU_CFG_RVAL_RVBARADDRL_SHIFT           (2)      /* Bits 2-31: Rvbaraddrl0 */
#define SYSC_SYS_ACPU_CFG_RVAL_RVBARADDRL_MASK(m)         (0x3fffffff << SYSC_SYS_ACPU_CFG_RVAL_RVBARADDRL_SHIFT)
#define SYSC_SYS_ACPU_CFG_RVAL_RVBARADDRL(m,val)          (((val) << SYSC_SYS_ACPU_CFG_RVAL_RVBARADDRL_SHIFT) & SYSC_SYS_ACPU_CFG_RVAL_RVBARADDRL_MASK(m))

/* SYSC SYS_GPREG Register Bit Definitions (Parameterized) *****************/

#define SYSC_SYS_GPREG_CPREG_SHIFT                        (0)      /* Bits 0-31: Cpreg0 */
#define SYSC_SYS_GPREG_CPREG_MASK(m)                      (0xffffffff << SYSC_SYS_GPREG_CPREG_SHIFT)
#define SYSC_SYS_GPREG_CPREG(m,val)                       (((val) << SYSC_SYS_GPREG_CPREG_SHIFT) & SYSC_SYS_GPREG_CPREG_MASK(m))

/* SYSC SYS_MCPU_CFG Register Bit Definitions (Parameterized) **************/

#define SYSC_SYS_MCPU_CFG_INITSVTOR_SHIFT                 (7)      /* Bits 7-31: Initsvtor */
#define SYSC_SYS_MCPU_CFG_INITSVTOR_MASK(m)               (0x1ffffff << SYSC_SYS_MCPU_CFG_INITSVTOR_SHIFT)
#define SYSC_SYS_MCPU_CFG_INITSVTOR(m,val)                (((val) << SYSC_SYS_MCPU_CFG_INITSVTOR_SHIFT) & SYSC_SYS_MCPU_CFG_INITSVTOR_MASK(m))

/* SYSC SYS_MSTACCCTL Register Bit Definitions (Parameterized) *************/

#define SYSC_SYS_MSTACCCTL_SXMDMC_AWPU(m)                 (1 << 0)  /* Sxmdmc Awpu */
#define SYSC_SYS_MSTACCCTL_SXMDMC_AWNS(m)                 (1 << 1)  /* Sxmdmc Awns */
#define SYSC_SYS_MSTACCCTL_SXMDMC_AWSEL(m)                (1 << 3)  /* Sxmdmc Awsel */
#define SYSC_SYS_MSTACCCTL_SXMDMC_ARPU(m)                 (1 << 4)  /* Sxmdmc Arpu */
#define SYSC_SYS_MSTACCCTL_SXMDMC_ARNS(m)                 (1 << 5)  /* Sxmdmc Arns */
#define SYSC_SYS_MSTACCCTL_SXMDMC_ARSEL(m)                (1 << 7)  /* Sxmdmc Arsel */
#define SYSC_SYS_MSTACCCTL_SXADMC00_AWPU(m)               (1 << 8)  /* Sxadmc00 Awpu */
#define SYSC_SYS_MSTACCCTL_SXADMC00_AWNS(m)               (1 << 9)  /* Sxadmc00 Awns */
#define SYSC_SYS_MSTACCCTL_SXADMC00_AWSEL(m)              (1 << 11)  /* Sxadmc00 Awsel */
#define SYSC_SYS_MSTACCCTL_SXADMC00_ARPU(m)               (1 << 12)  /* Sxadmc00 Arpu */
#define SYSC_SYS_MSTACCCTL_SXADMC00_ARNS(m)               (1 << 13)  /* Sxadmc00 Arns */
#define SYSC_SYS_MSTACCCTL_SXADMC00_ARSEL(m)              (1 << 15)  /* Sxadmc00 Arsel */
#define SYSC_SYS_MSTACCCTL_SXADMC1_AWPU(m)                (1 << 16)  /* Sxadmc1 Awpu */
#define SYSC_SYS_MSTACCCTL_SXADMC1_AWNS(m)                (1 << 17)  /* Sxadmc1 Awns */
#define SYSC_SYS_MSTACCCTL_SXADMC1_AWSEL(m)               (1 << 19)  /* Sxadmc1 Awsel */
#define SYSC_SYS_MSTACCCTL_SXADMC1_ARPU(m)                (1 << 20)  /* Sxadmc1 Arpu */
#define SYSC_SYS_MSTACCCTL_SXADMC1_ARNS(m)                (1 << 21)  /* Sxadmc1 Arns */
#define SYSC_SYS_MSTACCCTL_SXADMC1_ARSEL(m)               (1 << 23)  /* Sxadmc1 Arsel */
#define SYSC_SYS_MSTACCCTL_SXRDMC0_AWPU(m)                (1 << 24)  /* Sxrdmc0 Awpu */
#define SYSC_SYS_MSTACCCTL_SXRDMC0_AWNS(m)                (1 << 25)  /* Sxrdmc0 Awns */
#define SYSC_SYS_MSTACCCTL_SXRDMC0_AWSEL(m)               (1 << 27)  /* Sxrdmc0 Awsel */
#define SYSC_SYS_MSTACCCTL_SXRDMC0_ARPU(m)                (1 << 28)  /* Sxrdmc0 Arpu */
#define SYSC_SYS_MSTACCCTL_SXRDMC0_ARNS(m)                (1 << 29)  /* Sxrdmc0 Arns */
#define SYSC_SYS_MSTACCCTL_SXRDMC0_ARSEL(m)               (1 << 31)  /* Sxrdmc0 Arsel */

/* SYSC SYS_PCIE_ACK_CH Register Bit Definitions (Parameterized) ***********/

#define SYSC_SYS_PCIE_ACK_CH_TURN_OFF_EVENT_ACK(m)        (1 << 0)  /* Turn Off Event Ack */
#define SYSC_SYS_PCIE_ACK_CH_D3_ECENT_ACK_F0(m)           (1 << 8)  /* D3 Ecent Ack F0 */
#define SYSC_SYS_PCIE_ACK_CH_D3_ECENT_ACK_F1(m)           (1 << 9)  /* D3 Ecent Ack F1 */

/* SYSC SYS_PCIE_INTX_CH Register Bit Definitions (Parameterized) **********/

#define SYSC_SYS_PCIE_INTX_CH_INTX_EP_F0(m)               (1 << 0)  /* Intx Ep F0 */
#define SYSC_SYS_PCIE_INTX_CH_INTX_EP_F1(m)               (1 << 1)  /* Intx Ep F1 */

/* SYSC SYS_PCIE_MISC_CH Register Bit Definitions (Parameterized) **********/

#define SYSC_SYS_PCIE_MISC_CH_ALLOW_ENTER_L(m)            (1 << 0)  /* Allow Enter L1 */
#define SYSC_SYS_PCIE_MISC_CH_FLR_RESET_SHIFT             (16)      /* Bits 16-17: Flr Reset */
#define SYSC_SYS_PCIE_MISC_CH_FLR_RESET_MASK(m)           (0x3 << SYSC_SYS_PCIE_MISC_CH_FLR_RESET_SHIFT)
#define SYSC_SYS_PCIE_MISC_CH_FLR_RESET(m,val)            (((val) << SYSC_SYS_PCIE_MISC_CH_FLR_RESET_SHIFT) & SYSC_SYS_PCIE_MISC_CH_FLR_RESET_MASK(m))
#define SYSC_SYS_PCIE_MISC_CH_FLR_REQ_SHIFT               (18)      /* Bits 18-19: Flr Req */
#define SYSC_SYS_PCIE_MISC_CH_FLR_REQ_MASK(m)             (0x3 << SYSC_SYS_PCIE_MISC_CH_FLR_REQ_SHIFT)
#define SYSC_SYS_PCIE_MISC_CH_FLR_REQ(m,val)              (((val) << SYSC_SYS_PCIE_MISC_CH_FLR_REQ_SHIFT) & SYSC_SYS_PCIE_MISC_CH_FLR_REQ_MASK(m))

/* SYSC SYS_PCIE_MODE_CH Register Bit Definitions (Parameterized) **********/

#define SYSC_SYS_PCIE_MODE_CH_MODE_PORT(m)                (1 << 0)  /* Mode Port */

/* SYSC SYS_PCIE_PME_CH Register Bit Definitions (Parameterized) ***********/

#define SYSC_SYS_PCIE_PME_CH_PME_TIM(m)                   (1 << 0)  /* Pme Tim */
#define SYSC_SYS_PCIE_PME_CH_CFG_PMCSR_PME_STATUS_F0(m)   (1 << 8)  /* Cfg Pmcsr Pme Status F0 */
#define SYSC_SYS_PCIE_PME_CH_CFG_PMCSR_PME_STATUS_F1(m)   (1 << 9)  /* Cfg Pmcsr Pme Status F1 */

/* SYSC SYS_RCPU_CONFIG Register Bit Definitions (Parameterized) ***********/

#define SYSC_SYS_RCPU_CONFIG_MFILTEREN(m)                 (1 << 2)  /* Mfilteren */
#define SYSC_SYS_RCPU_CONFIG_ITCMECCEN(m)                 (1 << 3)  /* Itcmeccen */

/* SYSC SYS_SPI_ENDADDCS Register Bit Definitions (Parameterized) **********/

#define SYSC_SYS_SPI_ENDADDCS_XSPI_ENDADDRCS_SHIFT        (0)      /* Bits 0-31: Xspi Endaddrcs0 */
#define SYSC_SYS_SPI_ENDADDCS_XSPI_ENDADDRCS_MASK(m)      (0xffffffff << SYSC_SYS_SPI_ENDADDCS_XSPI_ENDADDRCS_SHIFT)
#define SYSC_SYS_SPI_ENDADDCS_XSPI_ENDADDRCS(m,val)       (((val) << SYSC_SYS_SPI_ENDADDCS_XSPI_ENDADDRCS_SHIFT) & SYSC_SYS_SPI_ENDADDCS_XSPI_ENDADDRCS_MASK(m))

/* SYSC SYS_SPI_STAADDCS Register Bit Definitions (Parameterized) **********/

#define SYSC_SYS_SPI_STAADDCS_XSPI_STARTADDRCS_SHIFT      (0)      /* Bits 0-31: Xspi Startaddrcs0 */
#define SYSC_SYS_SPI_STAADDCS_XSPI_STARTADDRCS_MASK(m)    (0xffffffff << SYSC_SYS_SPI_STAADDCS_XSPI_STARTADDRCS_SHIFT)
#define SYSC_SYS_SPI_STAADDCS_XSPI_STARTADDRCS(m,val)     (((val) << SYSC_SYS_SPI_STAADDCS_XSPI_STARTADDRCS_SHIFT) & SYSC_SYS_SPI_STAADDCS_XSPI_STARTADDRCS_MASK(m))

/* SYSC SYS_ACPU_CFG_EMPH Register Bit Definitions *******************/

#define SYSC_SYS_ACPU_CFG_EMPH_AENDMPH_SHIFT    (0)      /* Bits 0-7: Aendmph */
#define SYSC_SYS_ACPU_CFG_EMPH_AENDMPH_MASK     (0xff << SYSC_SYS_ACPU_CFG_EMPH_AENDMPH_SHIFT)

/* SYSC SYS_ACPU_CFG_EMPL Register Bit Definitions *******************/

#define SYSC_SYS_ACPU_CFG_EMPL_AENDMPLMPL_SHIFT (20)      /* Bits 20-31: Aendmplmpl */
#define SYSC_SYS_ACPU_CFG_EMPL_AENDMPLMPL_MASK  (0xfff << SYSC_SYS_ACPU_CFG_EMPL_AENDMPLMPL_SHIFT)

/* SYSC SYS_ACPU_CFG_SMPH Register Bit Definitions *******************/

#define SYSC_SYS_ACPU_CFG_SMPH_ASTARTMPH_SHIFT  (20)      /* Bits 20-31: Astartmph */
#define SYSC_SYS_ACPU_CFG_SMPH_ASTARTMPH_MASK   (0xfff << SYSC_SYS_ACPU_CFG_SMPH_ASTARTMPH_SHIFT)

/* SYSC SYS_ACPU_CFG_SMPL Register Bit Definitions *******************/

#define SYSC_SYS_ACPU_CFG_SMPL_ASTARTMPL_SHIFT  (0)      /* Bits 0-7: Astartmpl */
#define SYSC_SYS_ACPU_CFG_SMPL_ASTARTMPL_MASK   (0xff << SYSC_SYS_ACPU_CFG_SMPL_ASTARTMPL_SHIFT)

/* SYSC SYS_ADC_CFG Register Bit Definitions *************************/

#define SYSC_SYS_ADC_CFG_sy_mstp_ada            (1 << 0)  /* Sy Mstp Ada */

/* SYSC SYS_AOF0 Register Bit Definitions ****************************/

#define SYSC_SYS_AOF0_OFS00_0_SHIFT             (0)      /* Bits 0-5: Ofs00 0 */
#define SYSC_SYS_AOF0_OFS00_0_MASK              (0x3f << SYSC_SYS_AOF0_OFS00_0_SHIFT)

#define SYSC_SYS_AOF0_OFS01_0_SHIFT             (8)      /* Bits 8-13: Ofs01 0 */
#define SYSC_SYS_AOF0_OFS01_0_MASK              (0x3f << SYSC_SYS_AOF0_OFS01_0_SHIFT)

#define SYSC_SYS_AOF0_OFS10_0_SHIFT             (16)      /* Bits 16-21: Ofs10 0 */
#define SYSC_SYS_AOF0_OFS10_0_MASK              (0x3f << SYSC_SYS_AOF0_OFS10_0_SHIFT)

#define SYSC_SYS_AOF0_OFS11_0_SHIFT             (24)      /* Bits 24-29: Ofs11 0 */
#define SYSC_SYS_AOF0_OFS11_0_MASK              (0x3f << SYSC_SYS_AOF0_OFS11_0_SHIFT)

/* SYSC SYS_AOF1 Register Bit Definitions ****************************/

#define SYSC_SYS_AOF1_OFS00_1_SHIFT             (0)      /* Bits 0-5: Ofs00 1 */
#define SYSC_SYS_AOF1_OFS00_1_MASK              (0x3f << SYSC_SYS_AOF1_OFS00_1_SHIFT)

#define SYSC_SYS_AOF1_OFS01_1_SHIFT             (8)      /* Bits 8-13: Ofs01 1 */
#define SYSC_SYS_AOF1_OFS01_1_MASK              (0x3f << SYSC_SYS_AOF1_OFS01_1_SHIFT)

#define SYSC_SYS_AOF1_OFS10_1_SHIFT             (16)      /* Bits 16-21: Ofs10 1 */
#define SYSC_SYS_AOF1_OFS10_1_MASK              (0x3f << SYSC_SYS_AOF1_OFS10_1_SHIFT)

#define SYSC_SYS_AOF1_OFS11_1_SHIFT             (24)      /* Bits 24-29: Ofs11 1 */
#define SYSC_SYS_AOF1_OFS11_1_MASK              (0x3f << SYSC_SYS_AOF1_OFS11_1_SHIFT)

/* SYSC SYS_AOF16 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF16_OFS00_16_SHIFT           (0)      /* Bits 0-5: Ofs00 16 */
#define SYSC_SYS_AOF16_OFS00_16_MASK            (0x3f << SYSC_SYS_AOF16_OFS00_16_SHIFT)

#define SYSC_SYS_AOF16_OFS01_16_SHIFT           (8)      /* Bits 8-13: Ofs01 16 */
#define SYSC_SYS_AOF16_OFS01_16_MASK            (0x3f << SYSC_SYS_AOF16_OFS01_16_SHIFT)

#define SYSC_SYS_AOF16_OFS10_16_SHIFT           (16)      /* Bits 16-21: Ofs10 16 */
#define SYSC_SYS_AOF16_OFS10_16_MASK            (0x3f << SYSC_SYS_AOF16_OFS10_16_SHIFT)

#define SYSC_SYS_AOF16_OFS11_16_SHIFT           (24)      /* Bits 24-29: Ofs11 16 */
#define SYSC_SYS_AOF16_OFS11_16_MASK            (0x3f << SYSC_SYS_AOF16_OFS11_16_SHIFT)

/* SYSC SYS_AOF17 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF17_OFS00_17_SHIFT           (0)      /* Bits 0-5: Ofs00 17 */
#define SYSC_SYS_AOF17_OFS00_17_MASK            (0x3f << SYSC_SYS_AOF17_OFS00_17_SHIFT)

#define SYSC_SYS_AOF17_OFS01_17_SHIFT           (8)      /* Bits 8-13: Ofs01 17 */
#define SYSC_SYS_AOF17_OFS01_17_MASK            (0x3f << SYSC_SYS_AOF17_OFS01_17_SHIFT)

#define SYSC_SYS_AOF17_OFS10_17_SHIFT           (16)      /* Bits 16-21: Ofs10 17 */
#define SYSC_SYS_AOF17_OFS10_17_MASK            (0x3f << SYSC_SYS_AOF17_OFS10_17_SHIFT)

#define SYSC_SYS_AOF17_OFS11_17_SHIFT           (24)      /* Bits 24-29: Ofs11 17 */
#define SYSC_SYS_AOF17_OFS11_17_MASK            (0x3f << SYSC_SYS_AOF17_OFS11_17_SHIFT)

/* SYSC SYS_AOF18 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF18_OFS00_18_SHIFT           (0)      /* Bits 0-5: Ofs00 18 */
#define SYSC_SYS_AOF18_OFS00_18_MASK            (0x3f << SYSC_SYS_AOF18_OFS00_18_SHIFT)

#define SYSC_SYS_AOF18_OFS01_18_SHIFT           (8)      /* Bits 8-13: Ofs01 18 */
#define SYSC_SYS_AOF18_OFS01_18_MASK            (0x3f << SYSC_SYS_AOF18_OFS01_18_SHIFT)

#define SYSC_SYS_AOF18_OFS10_18_SHIFT           (16)      /* Bits 16-21: Ofs10 18 */
#define SYSC_SYS_AOF18_OFS10_18_MASK            (0x3f << SYSC_SYS_AOF18_OFS10_18_SHIFT)

#define SYSC_SYS_AOF18_OFS11_18_SHIFT           (24)      /* Bits 24-29: Ofs11 18 */
#define SYSC_SYS_AOF18_OFS11_18_MASK            (0x3f << SYSC_SYS_AOF18_OFS11_18_SHIFT)

/* SYSC SYS_AOF19 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF19_OFS00_19_SHIFT           (0)      /* Bits 0-5: Ofs00 19 */
#define SYSC_SYS_AOF19_OFS00_19_MASK            (0x3f << SYSC_SYS_AOF19_OFS00_19_SHIFT)

#define SYSC_SYS_AOF19_OFS01_19_SHIFT           (8)      /* Bits 8-13: Ofs01 19 */
#define SYSC_SYS_AOF19_OFS01_19_MASK            (0x3f << SYSC_SYS_AOF19_OFS01_19_SHIFT)

#define SYSC_SYS_AOF19_OFS10_19_SHIFT           (16)      /* Bits 16-21: Ofs10 19 */
#define SYSC_SYS_AOF19_OFS10_19_MASK            (0x3f << SYSC_SYS_AOF19_OFS10_19_SHIFT)

#define SYSC_SYS_AOF19_OFS11_19_SHIFT           (24)      /* Bits 24-29: Ofs11 19 */
#define SYSC_SYS_AOF19_OFS11_19_MASK            (0x3f << SYSC_SYS_AOF19_OFS11_19_SHIFT)

/* SYSC SYS_AOF2 Register Bit Definitions ****************************/

#define SYSC_SYS_AOF2_OFS00_2_SHIFT             (0)      /* Bits 0-5: Ofs00 2 */
#define SYSC_SYS_AOF2_OFS00_2_MASK              (0x3f << SYSC_SYS_AOF2_OFS00_2_SHIFT)

#define SYSC_SYS_AOF2_OFS01_2_SHIFT             (8)      /* Bits 8-13: Ofs01 2 */
#define SYSC_SYS_AOF2_OFS01_2_MASK              (0x3f << SYSC_SYS_AOF2_OFS01_2_SHIFT)

#define SYSC_SYS_AOF2_OFS10_2_SHIFT             (16)      /* Bits 16-21: Ofs10 2 */
#define SYSC_SYS_AOF2_OFS10_2_MASK              (0x3f << SYSC_SYS_AOF2_OFS10_2_SHIFT)

#define SYSC_SYS_AOF2_OFS11_2_SHIFT             (24)      /* Bits 24-29: Ofs11 2 */
#define SYSC_SYS_AOF2_OFS11_2_MASK              (0x3f << SYSC_SYS_AOF2_OFS11_2_SHIFT)

/* SYSC SYS_AOF20 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF20_OFS00_20_SHIFT           (0)      /* Bits 0-5: Ofs00 20 */
#define SYSC_SYS_AOF20_OFS00_20_MASK            (0x3f << SYSC_SYS_AOF20_OFS00_20_SHIFT)

#define SYSC_SYS_AOF20_OFS01_20_SHIFT           (8)      /* Bits 8-13: Ofs01 20 */
#define SYSC_SYS_AOF20_OFS01_20_MASK            (0x3f << SYSC_SYS_AOF20_OFS01_20_SHIFT)

#define SYSC_SYS_AOF20_OFS10_20_SHIFT           (16)      /* Bits 16-21: Ofs10 20 */
#define SYSC_SYS_AOF20_OFS10_20_MASK            (0x3f << SYSC_SYS_AOF20_OFS10_20_SHIFT)

#define SYSC_SYS_AOF20_OFS11_20_SHIFT           (24)      /* Bits 24-29: Ofs11 20 */
#define SYSC_SYS_AOF20_OFS11_20_MASK            (0x3f << SYSC_SYS_AOF20_OFS11_20_SHIFT)

/* SYSC SYS_AOF21 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF21_OFS00_21_SHIFT           (0)      /* Bits 0-5: Ofs00 21 */
#define SYSC_SYS_AOF21_OFS00_21_MASK            (0x3f << SYSC_SYS_AOF21_OFS00_21_SHIFT)

#define SYSC_SYS_AOF21_OFS01_21_SHIFT           (8)      /* Bits 8-13: Ofs01 21 */
#define SYSC_SYS_AOF21_OFS01_21_MASK            (0x3f << SYSC_SYS_AOF21_OFS01_21_SHIFT)

#define SYSC_SYS_AOF21_OFS10_21_SHIFT           (16)      /* Bits 16-21: Ofs10 21 */
#define SYSC_SYS_AOF21_OFS10_21_MASK            (0x3f << SYSC_SYS_AOF21_OFS10_21_SHIFT)

#define SYSC_SYS_AOF21_OFS11_21_SHIFT           (24)      /* Bits 24-29: Ofs11 21 */
#define SYSC_SYS_AOF21_OFS11_21_MASK            (0x3f << SYSC_SYS_AOF21_OFS11_21_SHIFT)

/* SYSC SYS_AOF22 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF22_OFS00_22_SHIFT           (0)      /* Bits 0-5: Ofs00 22 */
#define SYSC_SYS_AOF22_OFS00_22_MASK            (0x3f << SYSC_SYS_AOF22_OFS00_22_SHIFT)

#define SYSC_SYS_AOF22_OFS01_22_SHIFT           (8)      /* Bits 8-13: Ofs01 22 */
#define SYSC_SYS_AOF22_OFS01_22_MASK            (0x3f << SYSC_SYS_AOF22_OFS01_22_SHIFT)

#define SYSC_SYS_AOF22_OFS10_22_SHIFT           (16)      /* Bits 16-21: Ofs10 22 */
#define SYSC_SYS_AOF22_OFS10_22_MASK            (0x3f << SYSC_SYS_AOF22_OFS10_22_SHIFT)

#define SYSC_SYS_AOF22_OFS11_22_SHIFT           (24)      /* Bits 24-29: Ofs11 22 */
#define SYSC_SYS_AOF22_OFS11_22_MASK            (0x3f << SYSC_SYS_AOF22_OFS11_22_SHIFT)

/* SYSC SYS_AOF23 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF23_OFS00_23_SHIFT           (0)      /* Bits 0-5: Ofs00 23 */
#define SYSC_SYS_AOF23_OFS00_23_MASK            (0x3f << SYSC_SYS_AOF23_OFS00_23_SHIFT)

#define SYSC_SYS_AOF23_OFS01_23_SHIFT           (8)      /* Bits 8-13: Ofs01 23 */
#define SYSC_SYS_AOF23_OFS01_23_MASK            (0x3f << SYSC_SYS_AOF23_OFS01_23_SHIFT)

#define SYSC_SYS_AOF23_OFS10_23_SHIFT           (16)      /* Bits 16-21: Ofs10 23 */
#define SYSC_SYS_AOF23_OFS10_23_MASK            (0x3f << SYSC_SYS_AOF23_OFS10_23_SHIFT)

#define SYSC_SYS_AOF23_OFS11_23_SHIFT           (24)      /* Bits 24-29: Ofs11 23 */
#define SYSC_SYS_AOF23_OFS11_23_MASK            (0x3f << SYSC_SYS_AOF23_OFS11_23_SHIFT)

/* SYSC SYS_AOF24 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF24_OFS00_24_SHIFT           (0)      /* Bits 0-5: Ofs00 24 */
#define SYSC_SYS_AOF24_OFS00_24_MASK            (0x3f << SYSC_SYS_AOF24_OFS00_24_SHIFT)

#define SYSC_SYS_AOF24_OFS01_24_SHIFT           (8)      /* Bits 8-13: Ofs01 24 */
#define SYSC_SYS_AOF24_OFS01_24_MASK            (0x3f << SYSC_SYS_AOF24_OFS01_24_SHIFT)

#define SYSC_SYS_AOF24_OFS10_24_SHIFT           (16)      /* Bits 16-21: Ofs10 24 */
#define SYSC_SYS_AOF24_OFS10_24_MASK            (0x3f << SYSC_SYS_AOF24_OFS10_24_SHIFT)

#define SYSC_SYS_AOF24_OFS11_24_SHIFT           (24)      /* Bits 24-29: Ofs11 24 */
#define SYSC_SYS_AOF24_OFS11_24_MASK            (0x3f << SYSC_SYS_AOF24_OFS11_24_SHIFT)

/* SYSC SYS_AOF25 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF25_OFS00_25_SHIFT           (0)      /* Bits 0-5: Ofs00 25 */
#define SYSC_SYS_AOF25_OFS00_25_MASK            (0x3f << SYSC_SYS_AOF25_OFS00_25_SHIFT)

#define SYSC_SYS_AOF25_OFS01_25_SHIFT           (8)      /* Bits 8-13: Ofs01 25 */
#define SYSC_SYS_AOF25_OFS01_25_MASK            (0x3f << SYSC_SYS_AOF25_OFS01_25_SHIFT)

#define SYSC_SYS_AOF25_OFS10_25_SHIFT           (16)      /* Bits 16-21: Ofs10 25 */
#define SYSC_SYS_AOF25_OFS10_25_MASK            (0x3f << SYSC_SYS_AOF25_OFS10_25_SHIFT)

#define SYSC_SYS_AOF25_OFS11_25_SHIFT           (24)      /* Bits 24-29: Ofs11 25 */
#define SYSC_SYS_AOF25_OFS11_25_MASK            (0x3f << SYSC_SYS_AOF25_OFS11_25_SHIFT)

/* SYSC SYS_AOF3 Register Bit Definitions ****************************/

#define SYSC_SYS_AOF3_OFS00_3_SHIFT             (0)      /* Bits 0-5: Ofs00 3 */
#define SYSC_SYS_AOF3_OFS00_3_MASK              (0x3f << SYSC_SYS_AOF3_OFS00_3_SHIFT)

#define SYSC_SYS_AOF3_OFS01_3_SHIFT             (8)      /* Bits 8-13: Ofs01 3 */
#define SYSC_SYS_AOF3_OFS01_3_MASK              (0x3f << SYSC_SYS_AOF3_OFS01_3_SHIFT)

#define SYSC_SYS_AOF3_OFS10_3_SHIFT             (16)      /* Bits 16-21: Ofs10 3 */
#define SYSC_SYS_AOF3_OFS10_3_MASK              (0x3f << SYSC_SYS_AOF3_OFS10_3_SHIFT)

#define SYSC_SYS_AOF3_OFS11_3_SHIFT             (24)      /* Bits 24-29: Ofs11 3 */
#define SYSC_SYS_AOF3_OFS11_3_MASK              (0x3f << SYSC_SYS_AOF3_OFS11_3_SHIFT)

/* SYSC SYS_AOF32 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF32_OFS0011_MCPUS_SHIFT      (0)      /* Bits 0-7: Ofs0011 Mcpus */
#define SYSC_SYS_AOF32_OFS0011_MCPUS_MASK       (0xff << SYSC_SYS_AOF32_OFS0011_MCPUS_SHIFT)

#define SYSC_SYS_AOF32_OFS0100_MCPUS_SHIFT      (8)      /* Bits 8-15: Ofs0100 Mcpus */
#define SYSC_SYS_AOF32_OFS0100_MCPUS_MASK       (0xff << SYSC_SYS_AOF32_OFS0100_MCPUS_SHIFT)

/* SYSC SYS_AOF33 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF33_OFS00_33_SHIFT           (0)      /* Bits 0-5: Ofs00 33 */
#define SYSC_SYS_AOF33_OFS00_33_MASK            (0x3f << SYSC_SYS_AOF33_OFS00_33_SHIFT)

#define SYSC_SYS_AOF33_OFS01_33_SHIFT           (8)      /* Bits 8-13: Ofs01 33 */
#define SYSC_SYS_AOF33_OFS01_33_MASK            (0x3f << SYSC_SYS_AOF33_OFS01_33_SHIFT)

#define SYSC_SYS_AOF33_OFS10_33_SHIFT           (16)      /* Bits 16-21: Ofs10 33 */
#define SYSC_SYS_AOF33_OFS10_33_MASK            (0x3f << SYSC_SYS_AOF33_OFS10_33_SHIFT)

#define SYSC_SYS_AOF33_OFS11_33_SHIFT           (24)      /* Bits 24-29: Ofs11 33 */
#define SYSC_SYS_AOF33_OFS11_33_MASK            (0x3f << SYSC_SYS_AOF33_OFS11_33_SHIFT)

/* SYSC SYS_AOF4 Register Bit Definitions ****************************/

#define SYSC_SYS_AOF4_OFS00_4_SHIFT             (0)      /* Bits 0-5: Ofs00 4 */
#define SYSC_SYS_AOF4_OFS00_4_MASK              (0x3f << SYSC_SYS_AOF4_OFS00_4_SHIFT)

#define SYSC_SYS_AOF4_OFS01_4_SHIFT             (8)      /* Bits 8-13: Ofs01 4 */
#define SYSC_SYS_AOF4_OFS01_4_MASK              (0x3f << SYSC_SYS_AOF4_OFS01_4_SHIFT)

#define SYSC_SYS_AOF4_OFS10_4_SHIFT             (16)      /* Bits 16-21: Ofs10 4 */
#define SYSC_SYS_AOF4_OFS10_4_MASK              (0x3f << SYSC_SYS_AOF4_OFS10_4_SHIFT)

#define SYSC_SYS_AOF4_OFS11_4_SHIFT             (24)      /* Bits 24-29: Ofs11 4 */
#define SYSC_SYS_AOF4_OFS11_4_MASK              (0x3f << SYSC_SYS_AOF4_OFS11_4_SHIFT)

/* SYSC SYS_AOF40 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF40_OFS00_40_SHIFT           (0)      /* Bits 0-5: Ofs00 40 */
#define SYSC_SYS_AOF40_OFS00_40_MASK            (0x3f << SYSC_SYS_AOF40_OFS00_40_SHIFT)

#define SYSC_SYS_AOF40_OFS01_40_SHIFT           (8)      /* Bits 8-13: Ofs01 40 */
#define SYSC_SYS_AOF40_OFS01_40_MASK            (0x3f << SYSC_SYS_AOF40_OFS01_40_SHIFT)

#define SYSC_SYS_AOF40_OFS10_40_SHIFT           (16)      /* Bits 16-21: Ofs10 40 */
#define SYSC_SYS_AOF40_OFS10_40_MASK            (0x3f << SYSC_SYS_AOF40_OFS10_40_SHIFT)

#define SYSC_SYS_AOF40_OFS11_40_SHIFT           (24)      /* Bits 24-29: Ofs11 40 */
#define SYSC_SYS_AOF40_OFS11_40_MASK            (0x3f << SYSC_SYS_AOF40_OFS11_40_SHIFT)

/* SYSC SYS_AOF41 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF41_OFS00_41_SHIFT           (0)      /* Bits 0-5: Ofs00 41 */
#define SYSC_SYS_AOF41_OFS00_41_MASK            (0x3f << SYSC_SYS_AOF41_OFS00_41_SHIFT)

#define SYSC_SYS_AOF41_OFS01_41_SHIFT           (8)      /* Bits 8-13: Ofs01 41 */
#define SYSC_SYS_AOF41_OFS01_41_MASK            (0x3f << SYSC_SYS_AOF41_OFS01_41_SHIFT)

#define SYSC_SYS_AOF41_OFS10_41_SHIFT           (16)      /* Bits 16-21: Ofs10 41 */
#define SYSC_SYS_AOF41_OFS10_41_MASK            (0x3f << SYSC_SYS_AOF41_OFS10_41_SHIFT)

#define SYSC_SYS_AOF41_OFS11_41_SHIFT           (24)      /* Bits 24-29: Ofs11 41 */
#define SYSC_SYS_AOF41_OFS11_41_MASK            (0x3f << SYSC_SYS_AOF41_OFS11_41_SHIFT)

/* SYSC SYS_AOF42 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF42_OFS00_42_SHIFT           (0)      /* Bits 0-5: Ofs00 42 */
#define SYSC_SYS_AOF42_OFS00_42_MASK            (0x3f << SYSC_SYS_AOF42_OFS00_42_SHIFT)

#define SYSC_SYS_AOF42_OFS01_42_SHIFT           (8)      /* Bits 8-13: Ofs01 42 */
#define SYSC_SYS_AOF42_OFS01_42_MASK            (0x3f << SYSC_SYS_AOF42_OFS01_42_SHIFT)

#define SYSC_SYS_AOF42_OFS10_42_SHIFT           (16)      /* Bits 16-21: Ofs10 42 */
#define SYSC_SYS_AOF42_OFS10_42_MASK            (0x3f << SYSC_SYS_AOF42_OFS10_42_SHIFT)

#define SYSC_SYS_AOF42_OFS11_42_SHIFT           (24)      /* Bits 24-29: Ofs11 42 */
#define SYSC_SYS_AOF42_OFS11_42_MASK            (0x3f << SYSC_SYS_AOF42_OFS11_42_SHIFT)

/* SYSC SYS_AOF43 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF43_OFS00_43_SHIFT           (0)      /* Bits 0-5: Ofs00 43 */
#define SYSC_SYS_AOF43_OFS00_43_MASK            (0x3f << SYSC_SYS_AOF43_OFS00_43_SHIFT)

#define SYSC_SYS_AOF43_OFS01_43_SHIFT           (8)      /* Bits 8-13: Ofs01 43 */
#define SYSC_SYS_AOF43_OFS01_43_MASK            (0x3f << SYSC_SYS_AOF43_OFS01_43_SHIFT)

#define SYSC_SYS_AOF43_OFS10_43_SHIFT           (16)      /* Bits 16-21: Ofs10 43 */
#define SYSC_SYS_AOF43_OFS10_43_MASK            (0x3f << SYSC_SYS_AOF43_OFS10_43_SHIFT)

#define SYSC_SYS_AOF43_OFS11_43_SHIFT           (24)      /* Bits 24-29: Ofs11 43 */
#define SYSC_SYS_AOF43_OFS11_43_MASK            (0x3f << SYSC_SYS_AOF43_OFS11_43_SHIFT)

/* SYSC SYS_AOF48 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF48_OFS00_48_SHIFT           (0)      /* Bits 0-5: Ofs00 48 */
#define SYSC_SYS_AOF48_OFS00_48_MASK            (0x3f << SYSC_SYS_AOF48_OFS00_48_SHIFT)

#define SYSC_SYS_AOF48_OFS01_48_SHIFT           (8)      /* Bits 8-13: Ofs01 48 */
#define SYSC_SYS_AOF48_OFS01_48_MASK            (0x3f << SYSC_SYS_AOF48_OFS01_48_SHIFT)

#define SYSC_SYS_AOF48_OFS10_48_SHIFT           (16)      /* Bits 16-21: Ofs10 48 */
#define SYSC_SYS_AOF48_OFS10_48_MASK            (0x3f << SYSC_SYS_AOF48_OFS10_48_SHIFT)

#define SYSC_SYS_AOF48_OFS11_48_SHIFT           (24)      /* Bits 24-29: Ofs11 48 */
#define SYSC_SYS_AOF48_OFS11_48_MASK            (0x3f << SYSC_SYS_AOF48_OFS11_48_SHIFT)

/* SYSC SYS_AOF49 Register Bit Definitions ***************************/

#define SYSC_SYS_AOF49_OFS00_49_SHIFT           (0)      /* Bits 0-5: Ofs00 49 */
#define SYSC_SYS_AOF49_OFS00_49_MASK            (0x3f << SYSC_SYS_AOF49_OFS00_49_SHIFT)

#define SYSC_SYS_AOF49_OFS01_49_SHIFT           (8)      /* Bits 8-13: Ofs01 49 */
#define SYSC_SYS_AOF49_OFS01_49_MASK            (0x3f << SYSC_SYS_AOF49_OFS01_49_SHIFT)

#define SYSC_SYS_AOF49_OFS10_49_SHIFT           (16)      /* Bits 16-21: Ofs10 49 */
#define SYSC_SYS_AOF49_OFS10_49_MASK            (0x3f << SYSC_SYS_AOF49_OFS10_49_SHIFT)

#define SYSC_SYS_AOF49_OFS11_49_SHIFT           (24)      /* Bits 24-29: Ofs11 49 */
#define SYSC_SYS_AOF49_OFS11_49_MASK            (0x3f << SYSC_SYS_AOF49_OFS11_49_SHIFT)

/* SYSC SYS_GBETH0_CFG Register Bit Definitions **********************/

#define SYSC_SYS_GBETH0_CFG_MAC_SPEED_SHIFT     (0)      /* Bits 0-1: Mac Speed */
#define SYSC_SYS_GBETH0_CFG_MAC_SPEED_MASK      (0x3 << SYSC_SYS_GBETH0_CFG_MAC_SPEED_SHIFT)

#define SYSC_SYS_GBETH0_CFG_PHY_INTF_TYPE_SHIFT (16)      /* Bits 16-18: Phy Intf Type */
#define SYSC_SYS_GBETH0_CFG_PHY_INTF_TYPE_MASK  (0x7 << SYSC_SYS_GBETH0_CFG_PHY_INTF_TYPE_SHIFT)

/* SYSC SYS_GBETH1_CFG Register Bit Definitions **********************/

#define SYSC_SYS_GBETH1_CFG_MAC_SPEED_SHIFT     (0)      /* Bits 0-1: Mac Speed */
#define SYSC_SYS_GBETH1_CFG_MAC_SPEED_MASK      (0x3 << SYSC_SYS_GBETH1_CFG_MAC_SPEED_SHIFT)

#define SYSC_SYS_GBETH1_CFG_PHY_INTF_TYPE_SHIFT (16)      /* Bits 16-18: Phy Intf Type */
#define SYSC_SYS_GBETH1_CFG_PHY_INTF_TYPE_MASK  (0x7 << SYSC_SYS_GBETH1_CFG_PHY_INTF_TYPE_SHIFT)

/* SYSC SYS_LSI_DEVID Register Bit Definitions ***********************/

#define SYSC_SYS_LSI_DEVID_DEV_ID_SHIFT         (0)      /* Bits 0-31: Dev Id */
#define SYSC_SYS_LSI_DEVID_DEV_ID_MASK          (0xffffffff << SYSC_SYS_LSI_DEVID_DEV_ID_SHIFT)

/* SYSC SYS_LSI_MODE Register Bit Definitions ************************/

#define SYSC_SYS_LSI_MODE_STAT_MD_BOOT_SHIFT    (0)      /* Bits 0-2: Stat Md Boot */
#define SYSC_SYS_LSI_MODE_STAT_MD_BOOT_MASK     (0x7 << SYSC_SYS_LSI_MODE_STAT_MD_BOOT_SHIFT)

#define SYSC_SYS_LSI_MODE_STAT_DEBUGEN          (1 << 9)  /* Stat Debugen */

#define SYSC_SYS_LSI_MODE_STAT_BOOTSELECTER     (1 << 10)  /* Stat Bootselecter */

#define SYSC_SYS_LSI_MODE_STAT_BOOTPLLCA55_SHIFT (11)      /* Bits 11-12: Stat Bootpllca55 */
#define SYSC_SYS_LSI_MODE_STAT_BOOTPLLCA55_MASK (0x3 << SYSC_SYS_LSI_MODE_STAT_BOOTPLLCA55_SHIFT)

#define SYSC_SYS_LSI_MODE_STAT_MD_CLKS          (1 << 13)  /* Stat Md Clks */

/* SYSC SYS_LSI_OTPTSU0TRMVAL0 Register Bit Definitions **************/

#define SYSC_SYS_LSI_OTPTSU0TRMVAL0_TSU0_TRMVAL0_SHIFT (0)      /* Bits 0-31: Tsu0 Trmval0 */
#define SYSC_SYS_LSI_OTPTSU0TRMVAL0_TSU0_TRMVAL0_MASK (0xffffffff << SYSC_SYS_LSI_OTPTSU0TRMVAL0_TSU0_TRMVAL0_SHIFT)

/* SYSC SYS_LSI_OTPTSU0TRMVAL1 Register Bit Definitions **************/

#define SYSC_SYS_LSI_OTPTSU0TRMVAL1_TSU0_TRMVAL1_SHIFT (0)      /* Bits 0-31: Tsu0 Trmval1 */
#define SYSC_SYS_LSI_OTPTSU0TRMVAL1_TSU0_TRMVAL1_MASK (0xffffffff << SYSC_SYS_LSI_OTPTSU0TRMVAL1_TSU0_TRMVAL1_SHIFT)

/* SYSC SYS_LSI_OTPTSU1TRMVAL0 Register Bit Definitions **************/

#define SYSC_SYS_LSI_OTPTSU1TRMVAL0_TSU1_TRMVAL0_SHIFT (0)      /* Bits 0-31: Tsu1 Trmval0 */
#define SYSC_SYS_LSI_OTPTSU1TRMVAL0_TSU1_TRMVAL0_MASK (0xffffffff << SYSC_SYS_LSI_OTPTSU1TRMVAL0_TSU1_TRMVAL0_SHIFT)

/* SYSC SYS_LSI_OTPTSU1TRMVAL1 Register Bit Definitions **************/

#define SYSC_SYS_LSI_OTPTSU1TRMVAL1_TSU1_TRMVAL1_SHIFT (0)      /* Bits 0-31: Tsu1 Trmval1 */
#define SYSC_SYS_LSI_OTPTSU1TRMVAL1_TSU1_TRMVAL1_MASK (0xffffffff << SYSC_SYS_LSI_OTPTSU1TRMVAL1_TSU1_TRMVAL1_SHIFT)

/* SYSC SYS_LSI_PRR Register Bit Definitions *************************/

#define SYSC_SYS_LSI_PRR_GPU_DIS                (1 << 0)  /* Gpu Dis */

#define SYSC_SYS_LSI_PRR_ISP_DIS                (1 << 4)  /* Isp Dis */

/* SYSC SYS_PCIE_MODE Register Bit Definitions ***********************/

#define SYSC_SYS_PCIE_MODE_LINK_MASTER_SHIFT    (8)      /* Bits 8-9: Link Master */
#define SYSC_SYS_PCIE_MODE_LINK_MASTER_MASK     (0x3 << SYSC_SYS_PCIE_MODE_LINK_MASTER_SHIFT)

/* SYSC SYS_PCIE_MSI1_CH0 Register Bit Definitions *******************/

/* UI_EXTMSI_VAL_ fields (parameterized for indices 0-4) */
#define SYSC_SYS_PCIE_MSI1_CH0_UI_EXTMSI_VAL(n)           (1u << (0 + ((unsigned)(n) * 1)))  /* Ui Extmsi Val0 */

/* SYSC SYS_PCIE_MSI1_CH1 Register Bit Definitions *******************/

/* UI_EXTMSI_VAL_ fields (parameterized for indices 0-4) */
#define SYSC_SYS_PCIE_MSI1_CH1_UI_EXTMSI_VAL(n)           (1u << (0 + ((unsigned)(n) * 1)))  /* Ui Extmsi Val0 */

/* SYSC SYS_PCIE_MSI2_CH0 Register Bit Definitions *******************/

/* UI_EXTMSI_VEC_ fields (parameterized for indices 0-3) */
#define SYSC_SYS_PCIE_MSI2_CH0_UI_EXTMSI_VEC_SHIFT(n)     ((unsigned)(0 + ((n) * 8)))  /* Bits for UI_EXTMSI_VECn */
#define SYSC_SYS_PCIE_MSI2_CH0_UI_EXTMSI_VEC_MASK(n)      (0x1fu << SYSC_SYS_PCIE_MSI2_CH0_UI_EXTMSI_VEC_SHIFT(n))
#define SYSC_SYS_PCIE_MSI2_CH0_UI_EXTMSI_VEC_VAL(n,v)     (((unsigned)(v) & 0x1fu) << SYSC_SYS_PCIE_MSI2_CH0_UI_EXTMSI_VEC_SHIFT(n))

/* SYSC SYS_PCIE_MSI2_CH1 Register Bit Definitions *******************/

/* UI_EXTMSI_VEC_ fields (parameterized for indices 0-3) */
#define SYSC_SYS_PCIE_MSI2_CH1_UI_EXTMSI_VEC_SHIFT(n)     ((unsigned)(0 + ((n) * 8)))  /* Bits for UI_EXTMSI_VECn */
#define SYSC_SYS_PCIE_MSI2_CH1_UI_EXTMSI_VEC_MASK(n)      (0x1fu << SYSC_SYS_PCIE_MSI2_CH1_UI_EXTMSI_VEC_SHIFT(n))
#define SYSC_SYS_PCIE_MSI2_CH1_UI_EXTMSI_VEC_VAL(n,v)     (((unsigned)(v) & 0x1fu) << SYSC_SYS_PCIE_MSI2_CH1_UI_EXTMSI_VEC_SHIFT(n))

/* SYSC SYS_PCIE_MSI3_CH0 Register Bit Definitions *******************/

#define SYSC_SYS_PCIE_MSI3_CH0_UI_EXTMSI_VEC_SHIFT (0)      /* Bits 0-4: Ui Extmsi Vec */
#define SYSC_SYS_PCIE_MSI3_CH0_UI_EXTMSI_VEC_MASK (0x1f << SYSC_SYS_PCIE_MSI3_CH0_UI_EXTMSI_VEC_SHIFT)

/* SYSC SYS_PCIE_MSI3_CH1 Register Bit Definitions *******************/

#define SYSC_SYS_PCIE_MSI3_CH1_UI_EXTMSI_VEC4_SHIFT (0)      /* Bits 0-4: Ui Extmsi Vec4 */
#define SYSC_SYS_PCIE_MSI3_CH1_UI_EXTMSI_VEC4_MASK (0x1f << SYSC_SYS_PCIE_MSI3_CH1_UI_EXTMSI_VEC4_SHIFT)

/* SYSC SYS_PCIE_MSI4_CH0 Register Bit Definitions *******************/

/* UI_EXTMSI_FUNC_ fields (parameterized for indices 0-3) */
#define SYSC_SYS_PCIE_MSI4_CH0_UI_EXTMSI_FUNC_SHIFT(n)    ((unsigned)(0 + ((n) * 8)))  /* Bits for UI_EXTMSI_FUNCn */
#define SYSC_SYS_PCIE_MSI4_CH0_UI_EXTMSI_FUNC_MASK(n)     (0x7u << SYSC_SYS_PCIE_MSI4_CH0_UI_EXTMSI_FUNC_SHIFT(n))
#define SYSC_SYS_PCIE_MSI4_CH0_UI_EXTMSI_FUNC_VAL(n,v)    (((unsigned)(v) & 0x7u) << SYSC_SYS_PCIE_MSI4_CH0_UI_EXTMSI_FUNC_SHIFT(n))

/* SYSC SYS_PCIE_MSI4_CH1 Register Bit Definitions *******************/

/* UI_EXTMSI_FUNC_ fields (parameterized for indices 0-3) */
#define SYSC_SYS_PCIE_MSI4_CH1_UI_EXTMSI_FUNC_SHIFT(n)    ((unsigned)(0 + ((n) * 8)))  /* Bits for UI_EXTMSI_FUNCn */
#define SYSC_SYS_PCIE_MSI4_CH1_UI_EXTMSI_FUNC_MASK(n)     (0x7u << SYSC_SYS_PCIE_MSI4_CH1_UI_EXTMSI_FUNC_SHIFT(n))
#define SYSC_SYS_PCIE_MSI4_CH1_UI_EXTMSI_FUNC_VAL(n,v)    (((unsigned)(v) & 0x7u) << SYSC_SYS_PCIE_MSI4_CH1_UI_EXTMSI_FUNC_SHIFT(n))

/* SYSC SYS_PCIE_MSI5_CH0 Register Bit Definitions *******************/

#define SYSC_SYS_PCIE_MSI5_CH0_UI_EXTMSI_FUNC4_SHIFT (0)      /* Bits 0-2: Ui Extmsi Func4 */
#define SYSC_SYS_PCIE_MSI5_CH0_UI_EXTMSI_FUNC4_MASK (0x7 << SYSC_SYS_PCIE_MSI5_CH0_UI_EXTMSI_FUNC4_SHIFT)

/* SYSC SYS_PCIE_MSI5_CH1 Register Bit Definitions *******************/

#define SYSC_SYS_PCIE_MSI5_CH1_UI_EXTMSI_FUNC40 (1 << 0)  /* Ui Extmsi Func40 */

#define SYSC_SYS_PCIE_MSI5_CH1_UI_EXTMSI_FUNC4_SHIFT (1)      /* Bits 1-2: Ui Extmsi Func4 */
#define SYSC_SYS_PCIE_MSI5_CH1_UI_EXTMSI_FUNC4_MASK (0x3 << SYSC_SYS_PCIE_MSI5_CH1_UI_EXTMSI_FUNC4_SHIFT)

/* SYSC SYS_RCPU_CORESTATUS Register Bit Definitions *****************/

#define SYSC_SYS_RCPU_CORESTATUS_SMPnAMP_SHIFT  (0)      /* Bits 0-1: Smpnamp */
#define SYSC_SYS_RCPU_CORESTATUS_SMPnAMP_MASK   (0x3 << SYSC_SYS_RCPU_CORESTATUS_SMPnAMP_SHIFT)

#define SYSC_SYS_RCPU_CORESTATUS_PMUPRIV_SHIFT  (8)      /* Bits 8-9: Pmupriv */
#define SYSC_SYS_RCPU_CORESTATUS_PMUPRIV_MASK   (0x3 << SYSC_SYS_RCPU_CORESTATUS_PMUPRIV_SHIFT)

#define SYSC_SYS_RCPU_CORESTATUS_PWRCTLO0_SHIFT (20)      /* Bits 20-21: Pwrctlo0 */
#define SYSC_SYS_RCPU_CORESTATUS_PWRCTLO0_MASK  (0x3 << SYSC_SYS_RCPU_CORESTATUS_PWRCTLO0_SHIFT)

#define SYSC_SYS_RCPU_CORESTATUS_PWRCTLO1_SHIFT (22)      /* Bits 22-23: Pwrctlo1 */
#define SYSC_SYS_RCPU_CORESTATUS_PWRCTLO1_MASK  (0x3 << SYSC_SYS_RCPU_CORESTATUS_PWRCTLO1_SHIFT)

#define SYSC_SYS_RCPU_CORESTATUS_SCUIDLE        (1 << 24)  /* Scuidle */

/* SYSC SYS_SLVACCCTL0 Register Bit Definitions **********************/

#define SYSC_SYS_SLVACCCTL0_MPCPG_SL_SHIFT      (0)      /* Bits 0-1: Mpcpg Sl */
#define SYSC_SYS_SLVACCCTL0_MPCPG_SL_MASK       (0x3 << SYSC_SYS_SLVACCCTL0_MPCPG_SL_SHIFT)

/* SYSC SYS_SLVACCCTL1 Register Bit Definitions **********************/

#define SYSC_SYS_SLVACCCTL1_MPSYS_SL_SHIFT      (0)      /* Bits 0-1: Mpsys Sl */
#define SYSC_SYS_SLVACCCTL1_MPSYS_SL_MASK       (0x3 << SYSC_SYS_SLVACCCTL1_MPSYS_SL_SHIFT)

/* SYSC SYS_SLVACCCTL10 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL10_MORTR_SL_SHIFT     (0)      /* Bits 0-1: Mortr Sl */
#define SYSC_SYS_SLVACCCTL10_MORTR_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL10_MORTR_SL_SHIFT)

/* SYSC SYS_SLVACCCTL11 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL11_SPI_REG_SL_SHIFT   (0)      /* Bits 0-1: Spi Reg Sl */
#define SYSC_SYS_SLVACCCTL11_SPI_REG_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL11_SPI_REG_SL_SHIFT)

/* SYSC SYS_SLVACCCTL12 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL12_MHGPO_SL_SHIFT     (0)      /* Bits 0-1: Mhgpo Sl */
#define SYSC_SYS_SLVACCCTL12_MHGPO_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL12_MHGPO_SL_SHIFT)

/* SYSC SYS_SLVACCCTL13 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL13_MPPDM0_SL_SHIFT    (0)      /* Bits 0-1: Mppdm0 Sl */
#define SYSC_SYS_SLVACCCTL13_MPPDM0_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL13_MPPDM0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL13_MPPDM1_SL_SHIFT    (2)      /* Bits 2-3: Mppdm1 Sl */
#define SYSC_SYS_SLVACCCTL13_MPPDM1_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL13_MPPDM1_SL_SHIFT)

/* SYSC SYS_SLVACCCTL14 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL14_MOADC_SL_SHIFT     (0)      /* Bits 0-1: Moadc Sl */
#define SYSC_SYS_SLVACCCTL14_MOADC_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL14_MOADC_SL_SHIFT)

/* SYSC SYS_SLVACCCTL15 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL15_MPMTSU0_SL_SHIFT   (0)      /* Bits 0-1: Mpmtsu0 Sl */
#define SYSC_SYS_SLVACCCTL15_MPMTSU0_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL15_MPMTSU0_SL_SHIFT)

/* SYSC SYS_SLVACCCTL17 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL17_MPCMA_SL_SHIFT     (0)      /* Bits 0-1: Mpcma Sl */
#define SYSC_SYS_SLVACCCTL17_MPCMA_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL17_MPCMA_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL17_MPCMO_SL_SHIFT     (2)      /* Bits 2-3: Mpcmo Sl */
#define SYSC_SYS_SLVACCCTL17_MPCMO_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL17_MPCMO_SL_SHIFT)

/* SYSC SYS_SLVACCCTL19 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL19_MOSCF_SL_SHIFT     (0)      /* Bits 0-1: Moscf Sl */
#define SYSC_SYS_SLVACCCTL19_MOSCF_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL19_MOSCF_SL_SHIFT)

/* SYSC SYS_SLVACCCTL2 Register Bit Definitions **********************/

#define SYSC_SYS_SLVACCCTL2_MPICU0_SL_SHIFT     (0)      /* Bits 0-1: Mpicu0 Sl */
#define SYSC_SYS_SLVACCCTL2_MPICU0_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL2_MPICU0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL2_MPICU1_SL_SHIFT     (2)      /* Bits 2-3: Mpicu1 Sl */
#define SYSC_SYS_SLVACCCTL2_MPICU1_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL2_MPICU1_SL_SHIFT)

/* SYSC SYS_SLVACCCTL20 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL20_MOMI2C_SL_SHIFT    (0)      /* Bits 0-1: Momi2C Sl */
#define SYSC_SYS_SLVACCCTL20_MOMI2C_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL20_MOMI2C_SL_SHIFT)

/* SYSC SYS_SLVACCCTL21 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL21_MPTSPI_SL_SHIFT    (0)      /* Bits 0-1: Mptspi Sl */
#define SYSC_SYS_SLVACCCTL21_MPTSPI_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL21_MPTSPI_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL21_MPTM33_SL_SHIFT    (2)      /* Bits 2-3: Mptm33 Sl */
#define SYSC_SYS_SLVACCCTL21_MPTM33_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL21_MPTM33_SL_SHIFT)

/* SYSC SYS_SLVACCCTL22 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL22_MXMGPV_SL_SHIFT    (0)      /* Bits 0-1: Mxmgpv Sl */
#define SYSC_SYS_SLVACCCTL22_MXMGPV_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL22_MXMGPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL22_MCPU_SYS_GPV_SL_SHIFT (2)      /* Bits 2-3: Mcpu Sys Gpv Sl */
#define SYSC_SYS_SLVACCCTL22_MCPU_SYS_GPV_SL_MASK (0x3 << SYSC_SYS_SLVACCCTL22_MCPU_SYS_GPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL22_MCPU_PERI0_GPV_SL_SHIFT (4)      /* Bits 4-5: Mcpu Peri0 Gpv Sl */
#define SYSC_SYS_SLVACCCTL22_MCPU_PERI0_GPV_SL_MASK (0x3 << SYSC_SYS_SLVACCCTL22_MCPU_PERI0_GPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL22_MCPU_PERI1_GPV_SL_SHIFT (6)      /* Bits 6-7: Mcpu Peri1 Gpv Sl */
#define SYSC_SYS_SLVACCCTL22_MCPU_PERI1_GPV_SL_MASK (0x3 << SYSC_SYS_SLVACCCTL22_MCPU_PERI1_GPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL22_MCPU_PERI2_GPV_SL_SHIFT (8)      /* Bits 8-9: Mcpu Peri2 Gpv Sl */
#define SYSC_SYS_SLVACCCTL22_MCPU_PERI2_GPV_SL_MASK (0x3 << SYSC_SYS_SLVACCCTL22_MCPU_PERI2_GPV_SL_SHIFT)

/* SYSC SYS_SLVACCCTL3 Register Bit Definitions **********************/

#define SYSC_SYS_SLVACCCTL3_MXMDMC_SL_SHIFT     (0)      /* Bits 0-1: Mxmdmc Sl */
#define SYSC_SYS_SLVACCCTL3_MXMDMC_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL3_MXMDMC_SL_SHIFT)

/* SYSC SYS_SLVACCCTL32 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL32_MXADMC0_SL_SHIFT   (0)      /* Bits 0-1: Mxadmc0 Sl */
#define SYSC_SYS_SLVACCCTL32_MXADMC0_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL32_MXADMC0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL32_MXADMC1_SL_SHIFT   (2)      /* Bits 2-3: Mxadmc1 Sl */
#define SYSC_SYS_SLVACCCTL32_MXADMC1_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL32_MXADMC1_SL_SHIFT)

/* SYSC SYS_SLVACCCTL33 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL33_MPASRM_SL_SHIFT    (0)      /* Bits 0-1: Mpasrm Sl */
#define SYSC_SYS_SLVACCCTL33_MPASRM_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL33_MPASRM_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL33_MPDSRM0_SL_SHIFT   (6)      /* Bits 6-7: Mpdsrm0 Sl */
#define SYSC_SYS_SLVACCCTL33_MPDSRM0_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL33_MPDSRM0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL33_MPDSRM1_SL_SHIFT   (8)      /* Bits 8-9: Mpdsrm1 Sl */
#define SYSC_SYS_SLVACCCTL33_MPDSRM1_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL33_MPDSRM1_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL33_MPDSRM2_SL_SHIFT   (10)      /* Bits 10-11: Mpdsrm2 Sl */
#define SYSC_SYS_SLVACCCTL33_MPDSRM2_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL33_MPDSRM2_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL33_MPDSRM3_SL_SHIFT   (12)      /* Bits 12-13: Mpdsrm3 Sl */
#define SYSC_SYS_SLVACCCTL33_MPDSRM3_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL33_MPDSRM3_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL33_MPDSRM4_SL_SHIFT   (14)      /* Bits 14-15: Mpdsrm4 Sl */
#define SYSC_SYS_SLVACCCTL33_MPDSRM4_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL33_MPDSRM4_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL33_MPDSRM5_SL_SHIFT   (16)      /* Bits 16-17: Mpdsrm5 Sl */
#define SYSC_SYS_SLVACCCTL33_MPDSRM5_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL33_MPDSRM5_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL33_MPDSRM6_SL_SHIFT   (18)      /* Bits 18-19: Mpdsrm6 Sl */
#define SYSC_SYS_SLVACCCTL33_MPDSRM6_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL33_MPDSRM6_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL33_MPDSRM7_SL_SHIFT   (20)      /* Bits 20-21: Mpdsrm7 Sl */
#define SYSC_SYS_SLVACCCTL33_MPDSRM7_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL33_MPDSRM7_SL_SHIFT)

/* SYSC SYS_SLVACCCTL35 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL35_MPSYC_SL_SHIFT     (0)      /* Bits 0-1: Mpsyc Sl */
#define SYSC_SYS_SLVACCCTL35_MPSYC_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL35_MPSYC_SL_SHIFT)

/* SYSC SYS_SLVACCCTL36 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL36_MPAOST0_SL_SHIFT   (0)      /* Bits 0-1: Mpaost0 Sl */
#define SYSC_SYS_SLVACCCTL36_MPAOST0_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL36_MPAOST0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL36_MPAOST1_SL_SHIFT   (2)      /* Bits 2-3: Mpaost1 Sl */
#define SYSC_SYS_SLVACCCTL36_MPAOST1_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL36_MPAOST1_SL_SHIFT)

/* SYSC SYS_SLVACCCTL37 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL37_MOAWDT_SL_SHIFT    (0)      /* Bits 0-1: Moawdt Sl */
#define SYSC_SYS_SLVACCCTL37_MOAWDT_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL37_MOAWDT_SL_SHIFT)

/* SYSC SYS_SLVACCCTL38 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL38_MOAI2C0_SL_SHIFT   (0)      /* Bits 0-1: Moai2C0 Sl */
#define SYSC_SYS_SLVACCCTL38_MOAI2C0_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL38_MOAI2C0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL38_MOAI2C1_SL_SHIFT   (2)      /* Bits 2-3: Moai2C1 Sl */
#define SYSC_SYS_SLVACCCTL38_MOAI2C1_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL38_MOAI2C1_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL38_MOAI2C2_SL_SHIFT   (4)      /* Bits 4-5: Moai2C2 Sl */
#define SYSC_SYS_SLVACCCTL38_MOAI2C2_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL38_MOAI2C2_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL38_MOAI2C3_SL_SHIFT   (6)      /* Bits 6-7: Moai2C3 Sl */
#define SYSC_SYS_SLVACCCTL38_MOAI2C3_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL38_MOAI2C3_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL38_MOAI2C4_SL_SHIFT   (8)      /* Bits 8-9: Moai2C4 Sl */
#define SYSC_SYS_SLVACCCTL38_MOAI2C4_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL38_MOAI2C4_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL38_MOAI2C5_SL_SHIFT   (10)      /* Bits 10-11: Moai2C5 Sl */
#define SYSC_SYS_SLVACCCTL38_MOAI2C5_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL38_MOAI2C5_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL38_MOAI2C6_SL_SHIFT   (12)      /* Bits 12-13: Moai2C6 Sl */
#define SYSC_SYS_SLVACCCTL38_MOAI2C6_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL38_MOAI2C6_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL38_MOAI2C7_SL_SHIFT   (14)      /* Bits 14-15: Moai2C7 Sl */
#define SYSC_SYS_SLVACCCTL38_MOAI2C7_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL38_MOAI2C7_SL_SHIFT)

/* SYSC SYS_SLVACCCTL39 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL39_MXSD0_SL_SHIFT     (0)      /* Bits 0-1: Mxsd0 Sl */
#define SYSC_SYS_SLVACCCTL39_MXSD0_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL39_MXSD0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL39_MXSD1_SL_SHIFT     (2)      /* Bits 2-3: Mxsd1 Sl */
#define SYSC_SYS_SLVACCCTL39_MXSD1_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL39_MXSD1_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL39_MXSD2_SL_SHIFT     (4)      /* Bits 4-5: Mxsd2 Sl */
#define SYSC_SYS_SLVACCCTL39_MXSD2_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL39_MXSD2_SL_SHIFT)

/* SYSC SYS_SLVACCCTL4 Register Bit Definitions **********************/

#define SYSC_SYS_SLVACCCTL4_MPMSRM0_SL_SHIFT    (0)      /* Bits 0-1: Mpmsrm0 Sl */
#define SYSC_SYS_SLVACCCTL4_MPMSRM0_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL4_MPMSRM0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL4_MPMSRM1_SL_SHIFT    (2)      /* Bits 2-3: Mpmsrm1 Sl */
#define SYSC_SYS_SLVACCCTL4_MPMSRM1_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL4_MPMSRM1_SL_SHIFT)

/* SYSC SYS_SLVACCCTL40 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL40_MXU3H0_SL_SHIFT    (0)      /* Bits 0-1: Mxu3H0 Sl */
#define SYSC_SYS_SLVACCCTL40_MXU3H0_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL40_MXU3H0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL40_MXU3H1_SL_SHIFT    (2)      /* Bits 2-3: Mxu3H1 Sl */
#define SYSC_SYS_SLVACCCTL40_MXU3H1_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL40_MXU3H1_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL40_MPU3P0_SL_SHIFT    (4)      /* Bits 4-5: Mpu3P0 Sl */
#define SYSC_SYS_SLVACCCTL40_MPU3P0_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL40_MPU3P0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL40_MPU3P1_SL_SHIFT    (6)      /* Bits 6-7: Mpu3P1 Sl */
#define SYSC_SYS_SLVACCCTL40_MPU3P1_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL40_MPU3P1_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL40_MHU2H0_SL_SHIFT    (8)      /* Bits 8-9: Mhu2H0 Sl */
#define SYSC_SYS_SLVACCCTL40_MHU2H0_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL40_MHU2H0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL40_MHU2H1_SL_SHIFT    (10)      /* Bits 10-11: Mhu2H1 Sl */
#define SYSC_SYS_SLVACCCTL40_MHU2H1_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL40_MHU2H1_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL40_MPU2P0_SL_SHIFT    (12)      /* Bits 12-13: Mpu2P0 Sl */
#define SYSC_SYS_SLVACCCTL40_MPU2P0_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL40_MPU2P0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL40_MPU2P1_SL_SHIFT    (14)      /* Bits 14-15: Mpu2P1 Sl */
#define SYSC_SYS_SLVACCCTL40_MPU2P1_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL40_MPU2P1_SL_SHIFT)

/* SYSC SYS_SLVACCCTL41 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL41_MXGBE0_SL_SHIFT    (0)      /* Bits 0-1: Mxgbe0 Sl */
#define SYSC_SYS_SLVACCCTL41_MXGBE0_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL41_MXGBE0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL41_MXGBE1_SL_SHIFT    (2)      /* Bits 2-3: Mxgbe1 Sl */
#define SYSC_SYS_SLVACCCTL41_MXGBE1_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL41_MXGBE1_SL_SHIFT)

/* SYSC SYS_SLVACCCTL43 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL43_MPDDM0_SL_SHIFT    (0)      /* Bits 0-1: Mpddm0 Sl */
#define SYSC_SYS_SLVACCCTL43_MPDDM0_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL43_MPDDM0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL43_MPDDM1_SL_SHIFT    (2)      /* Bits 2-3: Mpddm1 Sl */
#define SYSC_SYS_SLVACCCTL43_MPDDM1_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL43_MPDDM1_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL43_MPDDP0_SL_SHIFT    (4)      /* Bits 4-5: Mpddp0 Sl */
#define SYSC_SYS_SLVACCCTL43_MPDDP0_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL43_MPDDP0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL43_MPDDP1_SL_SHIFT    (6)      /* Bits 6-7: Mpddp1 Sl */
#define SYSC_SYS_SLVACCCTL43_MPDDP1_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL43_MPDDP1_SL_SHIFT)

/* SYSC SYS_SLVACCCTL44 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL44_MPCRU0_SL_SHIFT    (0)      /* Bits 0-1: Mpcru0 Sl */
#define SYSC_SYS_SLVACCCTL44_MPCRU0_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL44_MPCRU0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL44_MPCRU1_SL_SHIFT    (2)      /* Bits 2-3: Mpcru1 Sl */
#define SYSC_SYS_SLVACCCTL44_MPCRU1_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL44_MPCRU1_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL44_MPCRU2_SL_SHIFT    (4)      /* Bits 4-5: Mpcru2 Sl */
#define SYSC_SYS_SLVACCCTL44_MPCRU2_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL44_MPCRU2_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL44_MPCRU3_SL_SHIFT    (6)      /* Bits 6-7: Mpcru3 Sl */
#define SYSC_SYS_SLVACCCTL44_MPCRU3_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL44_MPCRU3_SL_SHIFT)

/* SYSC SYS_SLVACCCTL45 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL45_MPISP_SL_SHIFT     (0)      /* Bits 0-1: Mpisp Sl */
#define SYSC_SYS_SLVACCCTL45_MPISP_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL45_MPISP_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL45_MXISP_SL_SHIFT     (2)      /* Bits 2-3: Mxisp Sl */
#define SYSC_SYS_SLVACCCTL45_MXISP_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL45_MXISP_SL_SHIFT)

/* SYSC SYS_SLVACCCTL46 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL46_MPISU_SL_SHIFT     (0)      /* Bits 0-1: Mpisu Sl */
#define SYSC_SYS_SLVACCCTL46_MPISU_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL46_MPISU_SL_SHIFT)

/* SYSC SYS_SLVACCCTL47 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL47_MPDSD_SL_SHIFT     (0)      /* Bits 0-1: Mpdsd Sl */
#define SYSC_SYS_SLVACCCTL47_MPDSD_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL47_MPDSD_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL47_MPDSL_SL_SHIFT     (2)      /* Bits 2-3: Mpdsl Sl */
#define SYSC_SYS_SLVACCCTL47_MPDSL_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL47_MPDSL_SL_SHIFT)

/* SYSC SYS_SLVACCCTL48 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL48_MPLCD_SL_SHIFT     (0)      /* Bits 0-1: Mplcd Sl */
#define SYSC_SYS_SLVACCCTL48_MPLCD_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL48_MPLCD_SL_SHIFT)

/* SYSC SYS_SLVACCCTL49 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL49_MXGPU_SL_SHIFT     (0)      /* Bits 0-1: Mxgpu Sl */
#define SYSC_SYS_SLVACCCTL49_MXGPU_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL49_MXGPU_SL_SHIFT)

/* SYSC SYS_SLVACCCTL5 Register Bit Definitions **********************/

#define SYSC_SYS_SLVACCCTL5_MPCST_SL_SHIFT      (0)      /* Bits 0-1: Mpcst Sl */
#define SYSC_SYS_SLVACCCTL5_MPCST_SL_MASK       (0x3 << SYSC_SYS_SLVACCCTL5_MPCST_SL_SHIFT)

/* SYSC SYS_SLVACCCTL50 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL50_MPVCC_SL_SHIFT     (0)      /* Bits 0-1: Mpvcc Sl */
#define SYSC_SYS_SLVACCCTL50_MPVCC_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL50_MPVCC_SL_SHIFT)

/* SYSC SYS_SLVACCCTL51 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL51_MPSSIU_SL_SHIFT    (0)      /* Bits 0-1: Mpssiu Sl */
#define SYSC_SYS_SLVACCCTL51_MPSSIU_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL51_MPSSIU_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL51_MPSSIUDMC_SL_SHIFT (2)      /* Bits 2-3: Mpssiudmc Sl */
#define SYSC_SYS_SLVACCCTL51_MPSSIUDMC_SL_MASK  (0x3 << SYSC_SYS_SLVACCCTL51_MPSSIUDMC_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL51_MPADMC_SL_SHIFT    (4)      /* Bits 4-5: Mpadmc Sl */
#define SYSC_SYS_SLVACCCTL51_MPADMC_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL51_MPADMC_SL_SHIFT)

/* SYSC SYS_SLVACCCTL52 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL52_MOSPD0_SL_SHIFT    (0)      /* Bits 0-1: Mospd0 Sl */
#define SYSC_SYS_SLVACCCTL52_MOSPD0_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL52_MOSPD0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL52_MOSPD1_SL_SHIFT    (2)      /* Bits 2-3: Mospd1 Sl */
#define SYSC_SYS_SLVACCCTL52_MOSPD1_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL52_MOSPD1_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL52_MOSPD2_SL_SHIFT    (4)      /* Bits 4-5: Mospd2 Sl */
#define SYSC_SYS_SLVACCCTL52_MOSPD2_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL52_MOSPD2_SL_SHIFT)

/* SYSC SYS_SLVACCCTL53 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL53_MPSCU_SL_SHIFT     (0)      /* Bits 0-1: Mpscu Sl */
#define SYSC_SYS_SLVACCCTL53_MPSCU_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL53_MPSCU_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL53_MPSCUDMC_SL_SHIFT  (2)      /* Bits 2-3: Mpscudmc Sl */
#define SYSC_SYS_SLVACCCTL53_MPSCUDMC_SL_MASK   (0x3 << SYSC_SYS_SLVACCCTL53_MPSCUDMC_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL53_MPADG_SL_SHIFT     (4)      /* Bits 4-5: Mpadg Sl */
#define SYSC_SYS_SLVACCCTL53_MPADG_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL53_MPADG_SL_SHIFT)

/* SYSC SYS_SLVACCCTL54 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL54_MXDRP_SL_SHIFT     (0)      /* Bits 0-1: Mxdrp Sl */
#define SYSC_SYS_SLVACCCTL54_MXDRP_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL54_MXDRP_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL54_MXDRA_SL_SHIFT     (2)      /* Bits 2-3: Mxdra Sl */
#define SYSC_SYS_SLVACCCTL54_MXDRA_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL54_MXDRA_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL54_MXDRS_SL_SHIFT     (4)      /* Bits 4-5: Mxdrs Sl */
#define SYSC_SYS_SLVACCCTL54_MXDRS_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL54_MXDRS_SL_SHIFT)

/* SYSC SYS_SLVACCCTL55 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL55_MXGIC_SL_SHIFT     (0)      /* Bits 0-1: Mxgic Sl */
#define SYSC_SYS_SLVACCCTL55_MXGIC_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL55_MXGIC_SL_SHIFT)

/* SYSC SYS_SLVACCCTL56 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL56_MPMTSU1_SL_SHIFT   (0)      /* Bits 0-1: Mpmtsu1 Sl */
#define SYSC_SYS_SLVACCCTL56_MPMTSU1_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL56_MPMTSU1_SL_SHIFT)

/* SYSC SYS_SLVACCCTL57 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL57_MPTA55_SL_SHIFT    (0)      /* Bits 0-1: Mpta55 Sl */
#define SYSC_SYS_SLVACCCTL57_MPTA55_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL57_MPTA55_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL57_MPTR8_SL_SHIFT     (2)      /* Bits 2-3: Mptr8 Sl */
#define SYSC_SYS_SLVACCCTL57_MPTR8_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL57_MPTR8_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL57_MPTDD00_SL_SHIFT   (4)      /* Bits 4-5: Mptdd00 Sl */
#define SYSC_SYS_SLVACCCTL57_MPTDD00_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL57_MPTDD00_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL57_MPTDD01_SL_SHIFT   (6)      /* Bits 6-7: Mptdd01 Sl */
#define SYSC_SYS_SLVACCCTL57_MPTDD01_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL57_MPTDD01_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL57_MPTDD10_SL_SHIFT   (8)      /* Bits 8-9: Mptdd10 Sl */
#define SYSC_SYS_SLVACCCTL57_MPTDD10_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL57_MPTDD10_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL57_MPTDD11_SL_SHIFT   (10)      /* Bits 10-11: Mptdd11 Sl */
#define SYSC_SYS_SLVACCCTL57_MPTDD11_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL57_MPTDD11_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL57_MPTPCI_SL_SHIFT    (12)      /* Bits 12-13: Mptpci Sl */
#define SYSC_SYS_SLVACCCTL57_MPTPCI_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL57_MPTPCI_SL_SHIFT)

/* SYSC SYS_SLVACCCTL58 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL58_MXV0GPV_SL_SHIFT   (0)      /* Bits 0-1: Mxv0Gpv Sl */
#define SYSC_SYS_SLVACCCTL58_MXV0GPV_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL58_MXV0GPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL58_MXV1GPV_SL_SHIFT   (2)      /* Bits 2-3: Mxv1Gpv Sl */
#define SYSC_SYS_SLVACCCTL58_MXV1GPV_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL58_MXV1GPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL58_MXDPGPV_SL_SHIFT   (4)      /* Bits 4-5: Mxdpgpv Sl */
#define SYSC_SYS_SLVACCCTL58_MXDPGPV_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL58_MXDPGPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL58_MXCMGPV_SL_SHIFT   (6)      /* Bits 6-7: Mxcmgpv Sl */
#define SYSC_SYS_SLVACCCTL58_MXCMGPV_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL58_MXCMGPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL58_MXACGPV_SL_SHIFT   (8)      /* Bits 8-9: Mxacgpv Sl */
#define SYSC_SYS_SLVACCCTL58_MXACGPV_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL58_MXACGPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL58_ACPU_PERI0_GPV_SL_SHIFT (10)      /* Bits 10-11: Acpu Peri0 Gpv Sl */
#define SYSC_SYS_SLVACCCTL58_ACPU_PERI0_GPV_SL_MASK (0x3 << SYSC_SYS_SLVACCCTL58_ACPU_PERI0_GPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL58_ACPU_PERI1_GPV_SL_SHIFT (12)      /* Bits 12-13: Acpu Peri1 Gpv Sl */
#define SYSC_SYS_SLVACCCTL58_ACPU_PERI1_GPV_SL_MASK (0x3 << SYSC_SYS_SLVACCCTL58_ACPU_PERI1_GPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL58_MXACR0GPV_SL_SHIFT (14)      /* Bits 14-15: Mxacr0Gpv Sl */
#define SYSC_SYS_SLVACCCTL58_MXACR0GPV_SL_MASK  (0x3 << SYSC_SYS_SLVACCCTL58_MXACR0GPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL58_MXACR1GPV_SL_SHIFT (16)      /* Bits 16-17: Mxacr1Gpv Sl */
#define SYSC_SYS_SLVACCCTL58_MXACR1GPV_SL_MASK  (0x3 << SYSC_SYS_SLVACCCTL58_MXACR1GPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL58_ACPU_REG2_GPV_SL_SHIFT (18)      /* Bits 18-19: Acpu Reg2 Gpv Sl */
#define SYSC_SYS_SLVACCCTL58_ACPU_REG2_GPV_SL_MASK (0x3 << SYSC_SYS_SLVACCCTL58_ACPU_REG2_GPV_SL_SHIFT)

/* SYSC SYS_SLVACCCTL59 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL59_ACPU_PERIVIDEO0_GPV_SL_SHIFT (0)      /* Bits 0-1: Acpu Perivideo0 Gpv Sl */
#define SYSC_SYS_SLVACCCTL59_ACPU_PERIVIDEO0_GPV_SL_MASK (0x3 << SYSC_SYS_SLVACCCTL59_ACPU_PERIVIDEO0_GPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL59_ACPU_PERIVIDEO1_GPV_SL_SHIFT (2)      /* Bits 2-3: Acpu Perivideo1 Gpv Sl */
#define SYSC_SYS_SLVACCCTL59_ACPU_PERIVIDEO1_GPV_SL_MASK (0x3 << SYSC_SYS_SLVACCCTL59_ACPU_PERIVIDEO1_GPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL59_ACPU_PERIDRP0_GPV_SL_SHIFT (4)      /* Bits 4-5: Acpu Peridrp0 Gpv Sl */
#define SYSC_SYS_SLVACCCTL59_ACPU_PERIDRP0_GPV_SL_MASK (0x3 << SYSC_SYS_SLVACCCTL59_ACPU_PERIDRP0_GPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL59_ACPU_PERIDRP1_GPV_SL_SHIFT (6)      /* Bits 6-7: Acpu Peridrp1 Gpv Sl */
#define SYSC_SYS_SLVACCCTL59_ACPU_PERIDRP1_GPV_SL_MASK (0x3 << SYSC_SYS_SLVACCCTL59_ACPU_PERIDRP1_GPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL59_ACPU_PERICOM0_GPV_SL_SHIFT (8)      /* Bits 8-9: Acpu Pericom0 Gpv Sl */
#define SYSC_SYS_SLVACCCTL59_ACPU_PERICOM0_GPV_SL_MASK (0x3 << SYSC_SYS_SLVACCCTL59_ACPU_PERICOM0_GPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL59_ACPU_PERICOM1_GPV_SL_SHIFT (10)      /* Bits 10-11: Acpu Pericom1 Gpv Sl */
#define SYSC_SYS_SLVACCCTL59_ACPU_PERICOM1_GPV_SL_MASK (0x3 << SYSC_SYS_SLVACCCTL59_ACPU_PERICOM1_GPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL59_ACPU_PERIDDR_GPV_SL_SHIFT (12)      /* Bits 12-13: Acpu Periddr Gpv Sl */
#define SYSC_SYS_SLVACCCTL59_ACPU_PERIDDR_GPV_SL_MASK (0x3 << SYSC_SYS_SLVACCCTL59_ACPU_PERIDDR_GPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL59_MXCMSGPV_SL_SHIFT  (14)      /* Bits 14-15: Mxcmsgpv Sl */
#define SYSC_SYS_SLVACCCTL59_MXCMSGPV_SL_MASK   (0x3 << SYSC_SYS_SLVACCCTL59_MXCMSGPV_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL59_ACPU_PERICOM2_GPV_SL_SHIFT (16)      /* Bits 16-17: Acpu Pericom2 Gpv Sl */
#define SYSC_SYS_SLVACCCTL59_ACPU_PERICOM2_GPV_SL_MASK (0x3 << SYSC_SYS_SLVACCCTL59_ACPU_PERICOM2_GPV_SL_SHIFT)

/* SYSC SYS_SLVACCCTL6 Register Bit Definitions **********************/

#define SYSC_SYS_SLVACCCTL6_MPMHU_SL_SHIFT      (0)      /* Bits 0-1: Mpmhu Sl */
#define SYSC_SYS_SLVACCCTL6_MPMHU_SL_MASK       (0x3 << SYSC_SYS_SLVACCCTL6_MPMHU_SL_SHIFT)

/* SYSC SYS_SLVACCCTL64 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL64_MOCRC_SL_SHIFT     (0)      /* Bits 0-1: Mocrc Sl */
#define SYSC_SYS_SLVACCCTL64_MOCRC_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL64_MOCRC_SL_SHIFT)

/* SYSC SYS_SLVACCCTL65 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL65_MOGPT0_SL_SHIFT    (0)      /* Bits 0-1: Mogpt0 Sl */
#define SYSC_SYS_SLVACCCTL65_MOGPT0_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL65_MOGPT0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL65_MOGPT1_SL_SHIFT    (2)      /* Bits 2-3: Mogpt1 Sl */
#define SYSC_SYS_SLVACCCTL65_MOGPT1_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL65_MOGPT1_SL_SHIFT)

/* SYSC SYS_SLVACCCTL66 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL66_MOPOE0_SL_SHIFT    (0)      /* Bits 0-1: Mopoe0 Sl */
#define SYSC_SYS_SLVACCCTL66_MOPOE0_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL66_MOPOE0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL66_MOPOE1_SL_SHIFT    (2)      /* Bits 2-3: Mopoe1 Sl */
#define SYSC_SYS_SLVACCCTL66_MOPOE1_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL66_MOPOE1_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL66_MOPOE2_SL_SHIFT    (4)      /* Bits 4-5: Mopoe2 Sl */
#define SYSC_SYS_SLVACCCTL66_MOPOE2_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL66_MOPOE2_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL66_MOPOE3_SL_SHIFT    (6)      /* Bits 6-7: Mopoe3 Sl */
#define SYSC_SYS_SLVACCCTL66_MOPOE3_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL66_MOPOE3_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL66_MOPOE4_SL_SHIFT    (8)      /* Bits 8-9: Mopoe4 Sl */
#define SYSC_SYS_SLVACCCTL66_MOPOE4_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL66_MOPOE4_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL66_MOPOE5_SL_SHIFT    (10)      /* Bits 10-11: Mopoe5 Sl */
#define SYSC_SYS_SLVACCCTL66_MOPOE5_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL66_MOPOE5_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL66_MOPOE6_SL_SHIFT    (12)      /* Bits 12-13: Mopoe6 Sl */
#define SYSC_SYS_SLVACCCTL66_MOPOE6_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL66_MOPOE6_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL66_MOPOE7_SL_SHIFT    (14)      /* Bits 14-15: Mopoe7 Sl */
#define SYSC_SYS_SLVACCCTL66_MOPOE7_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL66_MOPOE7_SL_SHIFT)

/* SYSC SYS_SLVACCCTL67 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL67_MORCMT0_SL_SHIFT   (0)      /* Bits 0-1: Morcmt0 Sl */
#define SYSC_SYS_SLVACCCTL67_MORCMT0_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL67_MORCMT0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL67_MORCMT1_SL_SHIFT   (2)      /* Bits 2-3: Morcmt1 Sl */
#define SYSC_SYS_SLVACCCTL67_MORCMT1_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL67_MORCMT1_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL67_MORCMT2_SL_SHIFT   (4)      /* Bits 4-5: Morcmt2 Sl */
#define SYSC_SYS_SLVACCCTL67_MORCMT2_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL67_MORCMT2_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL67_MORCMT3_SL_SHIFT   (6)      /* Bits 6-7: Morcmt3 Sl */
#define SYSC_SYS_SLVACCCTL67_MORCMT3_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL67_MORCMT3_SL_SHIFT)

/* SYSC SYS_SLVACCCTL68 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL68_MORWDT0_SL_SHIFT   (0)      /* Bits 0-1: Morwdt0 Sl */
#define SYSC_SYS_SLVACCCTL68_MORWDT0_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL68_MORWDT0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL68_MORWDT1_SL_SHIFT   (2)      /* Bits 2-3: Morwdt1 Sl */
#define SYSC_SYS_SLVACCCTL68_MORWDT1_SL_MASK    (0x3 << SYSC_SYS_SLVACCCTL68_MORWDT1_SL_SHIFT)

/* SYSC SYS_SLVACCCTL7 Register Bit Definitions **********************/

#define SYSC_SYS_SLVACCCTL7_MOMCMT0_SL_SHIFT    (0)      /* Bits 0-1: Momcmt0 Sl */
#define SYSC_SYS_SLVACCCTL7_MOMCMT0_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL7_MOMCMT0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL7_MOMCMT1_SL_SHIFT    (2)      /* Bits 2-3: Momcmt1 Sl */
#define SYSC_SYS_SLVACCCTL7_MOMCMT1_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL7_MOMCMT1_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL7_MOMCMT2_SL_SHIFT    (4)      /* Bits 4-5: Momcmt2 Sl */
#define SYSC_SYS_SLVACCCTL7_MOMCMT2_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL7_MOMCMT2_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL7_MOMCMT3_SL_SHIFT    (6)      /* Bits 6-7: Momcmt3 Sl */
#define SYSC_SYS_SLVACCCTL7_MOMCMT3_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL7_MOMCMT3_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL7_MPMOST0_SL_SHIFT    (8)      /* Bits 8-9: Mpmost0 Sl */
#define SYSC_SYS_SLVACCCTL7_MPMOST0_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL7_MPMOST0_SL_SHIFT)

#define SYSC_SYS_SLVACCCTL7_MPMOST1_SL_SHIFT    (10)      /* Bits 10-11: Mpmost1 Sl */
#define SYSC_SYS_SLVACCCTL7_MPMOST1_SL_MASK     (0x3 << SYSC_SYS_SLVACCCTL7_MPMOST1_SL_SHIFT)

/* SYSC SYS_SLVACCCTL8 Register Bit Definitions **********************/

#define SYSC_SYS_SLVACCCTL8_MOMWDT_SL_SHIFT     (0)      /* Bits 0-1: Momwdt Sl */
#define SYSC_SYS_SLVACCCTL8_MOMWDT_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL8_MOMWDT_SL_SHIFT)

/* SYSC SYS_SLVACCCTL80 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL80_I3C_SL_SHIFT       (0)      /* Bits 0-1: I3C Sl */
#define SYSC_SYS_SLVACCCTL80_I3C_SL_MASK        (0x3 << SYSC_SYS_SLVACCCTL80_I3C_SL_SHIFT)

/* SYSC SYS_SLVACCCTL81 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL81_CANFD_SL_SHIFT     (0)      /* Bits 0-1: Canfd Sl */
#define SYSC_SYS_SLVACCCTL81_CANFD_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL81_CANFD_SL_SHIFT)

/* SYSC SYS_SLVACCCTL82 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL82_RCPU_SRAM_SL_SHIFT (0)      /* Bits 0-1: Rcpu Sram Sl */
#define SYSC_SYS_SLVACCCTL82_RCPU_SRAM_SL_MASK  (0x3 << SYSC_SYS_SLVACCCTL82_RCPU_SRAM_SL_SHIFT)

/* SYSC SYS_SLVACCCTL88 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL88_RCPU_SL_SHIFT      (0)      /* Bits 0-1: Rcpu Sl */
#define SYSC_SYS_SLVACCCTL88_RCPU_SL_MASK       (0x3 << SYSC_SYS_SLVACCCTL88_RCPU_SL_SHIFT)

/* SYSC SYS_SLVACCCTL89 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL89_MCPU_SL_SHIFT      (0)      /* Bits 0-1: Mcpu Sl */
#define SYSC_SYS_SLVACCCTL89_MCPU_SL_MASK       (0x3 << SYSC_SYS_SLVACCCTL89_MCPU_SL_SHIFT)

/* SYSC SYS_SLVACCCTL9 Register Bit Definitions **********************/

#define SYSC_SYS_SLVACCCTL9_MORTC_SL_SHIFT      (0)      /* Bits 0-1: Mortc Sl */
#define SYSC_SYS_SLVACCCTL9_MORTC_SL_MASK       (0x3 << SYSC_SYS_SLVACCCTL9_MORTC_SL_SHIFT)

/* SYSC SYS_SLVACCCTL91 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL91_LSI_SL_SHIFT       (0)      /* Bits 0-1: Lsi Sl */
#define SYSC_SYS_SLVACCCTL91_LSI_SL_MASK        (0x3 << SYSC_SYS_SLVACCCTL91_LSI_SL_SHIFT)

/* SYSC SYS_SLVACCCTL92 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL92_AOF_SL_SHIFT       (0)      /* Bits 0-1: Aof Sl */
#define SYSC_SYS_SLVACCCTL92_AOF_SL_MASK        (0x3 << SYSC_SYS_SLVACCCTL92_AOF_SL_SHIFT)

/* SYSC SYS_SLVACCCTL93 Register Bit Definitions *********************/

#define SYSC_SYS_SLVACCCTL93_GPREG_SL_SHIFT     (0)      /* Bits 0-1: Gpreg Sl */
#define SYSC_SYS_SLVACCCTL93_GPREG_SL_MASK      (0x3 << SYSC_SYS_SLVACCCTL93_GPREG_SL_SHIFT)

/* SYSC SYS_SRAM0_ECC Register Bit Definitions ***********************/

#define SYSC_SYS_SRAM0_ECC_VECCEN               (1 << 0)  /* Veccen */

/* SYSC SYS_SRAM0_EN Register Bit Definitions ************************/

#define SYSC_SYS_SRAM0_EN_VCEN                  (1 << 0)  /* Vcen */

#define SYSC_SYS_SRAM0_EN_VLWEN                 (1 << 1)  /* Vlwen */

/* SYSC SYS_SRAM10_ECC Register Bit Definitions **********************/

#define SYSC_SYS_SRAM10_ECC_VECCEN              (1 << 0)  /* Veccen */

/* SYSC SYS_SRAM10_EN Register Bit Definitions ***********************/

#define SYSC_SYS_SRAM10_EN_VCEN                 (1 << 0)  /* Vcen */

#define SYSC_SYS_SRAM10_EN_VLWEN                (1 << 1)  /* Vlwen */

/* SYSC SYS_SRAM11_ECC Register Bit Definitions **********************/

#define SYSC_SYS_SRAM11_ECC_VECCEN              (1 << 0)  /* Veccen */

/* SYSC SYS_SRAM11_EN Register Bit Definitions ***********************/

#define SYSC_SYS_SRAM11_EN_VCEN                 (1 << 0)  /* Vcen */

#define SYSC_SYS_SRAM11_EN_VLWEN                (1 << 1)  /* Vlwen */

/* SYSC SYS_SRAM1_ECC Register Bit Definitions ***********************/

#define SYSC_SYS_SRAM1_ECC_VECCEN               (1 << 0)  /* Veccen */

/* SYSC SYS_SRAM1_EN Register Bit Definitions ************************/

#define SYSC_SYS_SRAM1_EN_VCEN                  (1 << 0)  /* Vcen */

#define SYSC_SYS_SRAM1_EN_VLWEN                 (1 << 1)  /* Vlwen */

/* SYSC SYS_SRAM2_ECC Register Bit Definitions ***********************/

#define SYSC_SYS_SRAM2_ECC_VECCEN               (1 << 0)  /* Veccen */

/* SYSC SYS_SRAM2_EN Register Bit Definitions ************************/

#define SYSC_SYS_SRAM2_EN_VCEN                  (1 << 0)  /* Vcen */

#define SYSC_SYS_SRAM2_EN_VLWEN                 (1 << 1)  /* Vlwen */

/* SYSC SYS_SRAM3_ECC Register Bit Definitions ***********************/

#define SYSC_SYS_SRAM3_ECC_VECCEN               (1 << 0)  /* Veccen */

/* SYSC SYS_SRAM3_EN Register Bit Definitions ************************/

#define SYSC_SYS_SRAM3_EN_VCEN                  (1 << 0)  /* Vcen */

#define SYSC_SYS_SRAM3_EN_VLWEN                 (1 << 1)  /* Vlwen */

/* SYSC SYS_SRAM4_ECC Register Bit Definitions ***********************/

#define SYSC_SYS_SRAM4_ECC_VECCEN               (1 << 0)  /* Veccen */

/* SYSC SYS_SRAM4_EN Register Bit Definitions ************************/

#define SYSC_SYS_SRAM4_EN_VCEN                  (1 << 0)  /* Vcen */

#define SYSC_SYS_SRAM4_EN_VLWEN                 (1 << 1)  /* Vlwen */

/* SYSC SYS_SRAM5_ECC Register Bit Definitions ***********************/

#define SYSC_SYS_SRAM5_ECC_VECCEN               (1 << 0)  /* Veccen */

/* SYSC SYS_SRAM5_EN Register Bit Definitions ************************/

#define SYSC_SYS_SRAM5_EN_VCEN                  (1 << 0)  /* Vcen */

#define SYSC_SYS_SRAM5_EN_VLWEN                 (1 << 1)  /* Vlwen */

/* SYSC SYS_SRAM6_ECC Register Bit Definitions ***********************/

#define SYSC_SYS_SRAM6_ECC_VECCEN               (1 << 0)  /* Veccen */

/* SYSC SYS_SRAM6_EN Register Bit Definitions ************************/

#define SYSC_SYS_SRAM6_EN_VCEN                  (1 << 0)  /* Vcen */

#define SYSC_SYS_SRAM6_EN_VLWEN                 (1 << 1)  /* Vlwen */

/* SYSC SYS_SRAM7_ECC Register Bit Definitions ***********************/

#define SYSC_SYS_SRAM7_ECC_VECCEN               (1 << 0)  /* Veccen */

/* SYSC SYS_SRAM7_EN Register Bit Definitions ************************/

#define SYSC_SYS_SRAM7_EN_VCEN                  (1 << 0)  /* Vcen */

#define SYSC_SYS_SRAM7_EN_VLWEN                 (1 << 1)  /* Vlwen */

/* SYSC SYS_SRAM8_ECC Register Bit Definitions ***********************/

#define SYSC_SYS_SRAM8_ECC_VECCEN               (1 << 0)  /* Veccen */

/* SYSC SYS_SRAM8_EN Register Bit Definitions ************************/

#define SYSC_SYS_SRAM8_EN_VCEN                  (1 << 0)  /* Vcen */

#define SYSC_SYS_SRAM8_EN_VLWEN                 (1 << 1)  /* Vlwen */

/* SYSC SYS_SRAM9_ECC Register Bit Definitions ***********************/

#define SYSC_SYS_SRAM9_ECC_VECCEN               (1 << 0)  /* Veccen */

/* SYSC SYS_SRAM9_EN Register Bit Definitions ************************/

#define SYSC_SYS_SRAM9_EN_VCEN                  (1 << 0)  /* Vcen */

#define SYSC_SYS_SRAM9_EN_VLWEN                 (1 << 1)  /* Vlwen */

/* SYSC SYS_WDT0_CTRL Register Bit Definitions ***********************/

#define SYSC_SYS_WDT0_CTRL_bp_halted            (1 << 0)  /* Bp Halted */

#define SYSC_SYS_WDT0_CTRL_WDTSTOPMASK          (1 << 16)  /* Wdtstopmask */

/* SYSC SYS_WDT1_CTRL Register Bit Definitions ***********************/

#define SYSC_SYS_WDT1_CTRL_bp_halted            (1 << 0)  /* Bp Halted */

#define SYSC_SYS_WDT1_CTRL_WDTSTOPMASK          (1 << 16)  /* Wdtstopmask */

/* SYSC SYS_WDT2_CTRL Register Bit Definitions ***********************/

#define SYSC_SYS_WDT2_CTRL_bp_halted            (1 << 0)  /* Bp Halted */

#define SYSC_SYS_WDT2_CTRL_WDTSTOPMASK          (1 << 16)  /* Wdtstopmask */

/* SYSC SYS_WDT3_CTRL Register Bit Definitions ***********************/

#define SYSC_SYS_WDT3_CTRL_bp_halted            (1 << 0)  /* Bp Halted */

#define SYSC_SYS_WDT3_CTRL_WDTSTOPMASK          (1 << 16)  /* Wdtstopmask */

/* SYSC Channel definitions */
#define RZV_SYSC_CHANNEL_0         0

/* Maximum number of SYSC channels */
#define RZV_SYSC_MAX_CHANNELS      1

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SYSC_H */

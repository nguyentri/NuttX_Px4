/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_gpio.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_GPIO_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_GPIO_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPIO Base Addresses ***************************************************/

#ifndef RZV_GPIO0_BASE
#  define RZV_GPIO0_BASE              0x10410020
#endif
#ifndef RZV_GPIO_BASE
#  define RZV_GPIO_BASE               RZV_GPIO0_BASE
#endif

/* GPIO Register Offsets **************************************************/

/* All offsets below are relative to RZV_GPIO_BASE = R_GPIO_BASE
 * (0x10410020) and were verified with offsetof(R_GPIO_Type, <reg>) against
 * the FSP CMSIS device header
 * (cr/iodefines/gpio_iodefine.h, R9A09G057H):
 *   P20=0x0000, PM20=0x0120, PMC20=0x0200, PFC20=0x0460, PIN20=0x0800,
 *   IOLH20_L=0x10E0, SR20_L=0x14E0, PUPD20_L=0x1CE0, ISEL20_L=0x2CE0,
 *   NOD20_L=0x30E0, PWPR=0x3BE4.
 * A previous generation of this header was shifted (+4/+8/-8 per register
 * family), which redirected every GPIO access to a neighbouring register.
 */

/* P%s Registers (20-29) */
#define RZV_GPIO_P_OFFSET(m)                    (0x00000000 + ((m) * 0x00000001))  /* P Register %s */
/* PFC%s Registers (20-29) */
#define RZV_GPIO_PFC_OFFSET(m)                  (0x00000460 + ((m) * 0x00000004))  /* PFC Register %s */
/* PIN%s Registers (20-29) */
#define RZV_GPIO_PIN_OFFSET(m)                  (0x00000800 + ((m) * 0x00000001))  /* PIN Register %s */
/* PM%s Registers (20-29) */
#define RZV_GPIO_PM_OFFSET(m)                   (0x00000120 + ((m) * 0x00000002))  /* PM Register %s */
/* PMC%s Registers (20-29) */
#define RZV_GPIO_PMC_OFFSET(m)                  (0x00000200 + ((m) * 0x00000001))  /* PMC Register %s */
#define RZV_GPIO_ELC_PDBF_OFFSET                         0x37E4  /* ELC_PDBF */
#define RZV_GPIO_P2A_OFFSET                              0x000A  /* P2A */
#define RZV_GPIO_P2B_OFFSET                              0x000B  /* P2B */
#define RZV_GPIO_PM2A_OFFSET                             0x0134  /* PM2A */
#define RZV_GPIO_PM2B_OFFSET                             0x0136  /* PM2B */
#define RZV_GPIO_PMC2A_OFFSET                            0x020A  /* PMC2A */
#define RZV_GPIO_PMC2B_OFFSET                            0x020B  /* PMC2B */
#define RZV_GPIO_PFC2A_OFFSET                            0x0488  /* PFC2A */
#define RZV_GPIO_PFC2B_OFFSET                            0x048C  /* PFC2B */
#define RZV_GPIO_PIN2A_OFFSET                            0x080A  /* PIN2A */
#define RZV_GPIO_PIN2B_OFFSET                            0x080B  /* PIN2B */
#define RZV_GPIO_IOLH3_L_OFFSET                          0x0FF8  /* IOLH3_L */
#define RZV_GPIO_IOLH3_H_OFFSET                          0x0FFC  /* IOLH3_H */
#define RZV_GPIO_IOLH5_L_OFFSET                          0x1008  /* IOLH5_L */
#define RZV_GPIO_IOLH5_H_OFFSET                          0x100C  /* IOLH5_H */
#define RZV_GPIO_IOLH6_L_OFFSET                          0x1010  /* IOLH6_L */
#define RZV_GPIO_IOLH6_H_OFFSET                          0x1014  /* IOLH6_H */
#define RZV_GPIO_IOLH7_L_OFFSET                          0x1018  /* IOLH7_L */
#define RZV_GPIO_IOLH7_H_OFFSET                          0x101C  /* IOLH7_H */
#define RZV_GPIO_IOLH8_L_OFFSET                          0x1020  /* IOLH8_L */
#define RZV_GPIO_IOLH8_H_OFFSET                          0x1024  /* IOLH8_H */
#define RZV_GPIO_IOLH9_L_OFFSET                          0x1028  /* IOLH9_L */
#define RZV_GPIO_IOLH9_H_OFFSET                          0x102C  /* IOLH9_H */
#define RZV_GPIO_IOLHA_L_OFFSET                          0x1030  /* IOLHA_L */
#define RZV_GPIO_IOLHA_H_OFFSET                          0x1034  /* IOLHA_H */
#define RZV_GPIO_IOLHB_L_OFFSET                          0x1038  /* IOLHB_L */
#define RZV_GPIO_IOLHB_H_OFFSET                          0x103C  /* IOLHB_H */
#define RZV_GPIO_IOLHC_L_OFFSET                          0x1040  /* IOLHC_L */
#define RZV_GPIO_IOLHC_H_OFFSET                          0x1044  /* IOLHC_H */
#define RZV_GPIO_IOLHE_L_OFFSET                          0x1050  /* IOLHE_L */
#define RZV_GPIO_IOLHE_H_OFFSET                          0x1054  /* IOLHE_H */
#define RZV_GPIO_IOLHF_L_OFFSET                          0x1058  /* IOLHF_L */
#define RZV_GPIO_IOLHF_H_OFFSET                          0x105C  /* IOLHF_H */
#define RZV_GPIO_IOLH10_L_OFFSET                         0x1060  /* IOLH10_L */
#define RZV_GPIO_IOLH10_H_OFFSET                         0x1064  /* IOLH10_H */
#define RZV_GPIO_IOLH11_L_OFFSET                         0x1068  /* IOLH11_L */
#define RZV_GPIO_IOLH11_H_OFFSET                         0x106C  /* IOLH11_H */
#define RZV_GPIO_IOLH12_L_OFFSET                         0x1070  /* IOLH12_L */
#define RZV_GPIO_IOLH12_H_OFFSET                         0x1074  /* IOLH12_H */
#define RZV_GPIO_IOLH13_L_OFFSET                         0x1078  /* IOLH13_L */
#define RZV_GPIO_IOLH13_H_OFFSET                         0x107C  /* IOLH13_H */
#define RZV_GPIO_IOLH14_L_OFFSET                         0x1080  /* IOLH14_L */
#define RZV_GPIO_IOLH14_H_OFFSET                         0x1084  /* IOLH14_H */
#define RZV_GPIO_IOLH20_L_OFFSET                         0x10E0  /* IOLH20_L */
#define RZV_GPIO_IOLH20_H_OFFSET                         0x10E4  /* IOLH20_H */
#define RZV_GPIO_IOLH21_L_OFFSET                         0x10E8  /* IOLH21_L */
#define RZV_GPIO_IOLH21_H_OFFSET                         0x10EC  /* IOLH21_H */
#define RZV_GPIO_IOLH22_L_OFFSET                         0x10F0  /* IOLH22_L */
#define RZV_GPIO_IOLH22_H_OFFSET                         0x10F4  /* IOLH22_H */
#define RZV_GPIO_IOLH23_L_OFFSET                         0x10F8  /* IOLH23_L */
#define RZV_GPIO_IOLH23_H_OFFSET                         0x10FC  /* IOLH23_H */
#define RZV_GPIO_IOLH24_L_OFFSET                         0x1100  /* IOLH24_L */
#define RZV_GPIO_IOLH24_H_OFFSET                         0x1104  /* IOLH24_H */
#define RZV_GPIO_IOLH25_L_OFFSET                         0x1108  /* IOLH25_L */
#define RZV_GPIO_IOLH25_H_OFFSET                         0x110C  /* IOLH25_H */
#define RZV_GPIO_IOLH26_L_OFFSET                         0x1110  /* IOLH26_L */
#define RZV_GPIO_IOLH26_H_OFFSET                         0x1114  /* IOLH26_H */
#define RZV_GPIO_IOLH27_L_OFFSET                         0x1118  /* IOLH27_L */
#define RZV_GPIO_IOLH27_H_OFFSET                         0x111C  /* IOLH27_H */
#define RZV_GPIO_IOLH28_L_OFFSET                         0x1120  /* IOLH28_L */
#define RZV_GPIO_IOLH28_H_OFFSET                         0x1124  /* IOLH28_H */
#define RZV_GPIO_IOLH29_L_OFFSET                         0x1128  /* IOLH29_L */
#define RZV_GPIO_IOLH29_H_OFFSET                         0x112C  /* IOLH29_H */
#define RZV_GPIO_IOLH2A_L_OFFSET                         0x1130  /* IOLH2A_L */
#define RZV_GPIO_IOLH2A_H_OFFSET                         0x1134  /* IOLH2A_H */
#define RZV_GPIO_IOLH2B_L_OFFSET                         0x1138  /* IOLH2B_L */
#define RZV_GPIO_IOLH2B_H_OFFSET                         0x113C  /* IOLH2B_H */
#define RZV_GPIO_SR3_L_OFFSET                            0x13F8  /* SR3_L */
#define RZV_GPIO_SR3_H_OFFSET                            0x13FC  /* SR3_H */
#define RZV_GPIO_SR5_L_OFFSET                            0x1408  /* SR5_L */
#define RZV_GPIO_SR5_H_OFFSET                            0x140C  /* SR5_H */
#define RZV_GPIO_SR6_L_OFFSET                            0x1410  /* SR6_L */
#define RZV_GPIO_SR6_H_OFFSET                            0x1414  /* SR6_H */
#define RZV_GPIO_SR7_L_OFFSET                            0x1418  /* SR7_L */
#define RZV_GPIO_SR7_H_OFFSET                            0x141C  /* SR7_H */
#define RZV_GPIO_SR8_L_OFFSET                            0x1420  /* SR8_L */
#define RZV_GPIO_SR8_H_OFFSET                            0x1424  /* SR8_H */
#define RZV_GPIO_SR9_L_OFFSET                            0x1428  /* SR9_L */
#define RZV_GPIO_SR9_H_OFFSET                            0x142C  /* SR9_H */
#define RZV_GPIO_SRA_L_OFFSET                            0x1430  /* SRA_L */
#define RZV_GPIO_SRA_H_OFFSET                            0x1434  /* SRA_H */
#define RZV_GPIO_SRB_L_OFFSET                            0x1438  /* SRB_L */
#define RZV_GPIO_SRB_H_OFFSET                            0x143C  /* SRB_H */
#define RZV_GPIO_SRC_L_OFFSET                            0x1440  /* SRC_L */
#define RZV_GPIO_SRC_H_OFFSET                            0x1444  /* SRC_H */
#define RZV_GPIO_SRE_L_OFFSET                            0x1450  /* SRE_L */
#define RZV_GPIO_SRE_H_OFFSET                            0x1454  /* SRE_H */
#define RZV_GPIO_SRF_L_OFFSET                            0x1458  /* SRF_L */
#define RZV_GPIO_SRF_H_OFFSET                            0x145C  /* SRF_H */
#define RZV_GPIO_SR10_L_OFFSET                           0x1460  /* SR10_L */
#define RZV_GPIO_SR10_H_OFFSET                           0x1464  /* SR10_H */
#define RZV_GPIO_SR11_L_OFFSET                           0x1468  /* SR11_L */
#define RZV_GPIO_SR11_H_OFFSET                           0x146C  /* SR11_H */
#define RZV_GPIO_SR12_L_OFFSET                           0x1470  /* SR12_L */
#define RZV_GPIO_SR12_H_OFFSET                           0x1474  /* SR12_H */
#define RZV_GPIO_SR13_L_OFFSET                           0x1478  /* SR13_L */
#define RZV_GPIO_SR13_H_OFFSET                           0x147C  /* SR13_H */
#define RZV_GPIO_SR14_L_OFFSET                           0x1480  /* SR14_L */
#define RZV_GPIO_SR14_H_OFFSET                           0x1484  /* SR14_H */
#define RZV_GPIO_SR20_L_OFFSET                           0x14E0  /* SR20_L */
#define RZV_GPIO_SR20_H_OFFSET                           0x14E4  /* SR20_H */
#define RZV_GPIO_SR21_L_OFFSET                           0x14E8  /* SR21_L */
#define RZV_GPIO_SR21_H_OFFSET                           0x14EC  /* SR21_H */
#define RZV_GPIO_SR23_L_OFFSET                           0x14F8  /* SR23_L */
#define RZV_GPIO_SR23_H_OFFSET                           0x14FC  /* SR23_H */
#define RZV_GPIO_SR24_L_OFFSET                           0x1500  /* SR24_L */
#define RZV_GPIO_SR24_H_OFFSET                           0x1504  /* SR24_H */
#define RZV_GPIO_SR25_L_OFFSET                           0x1508  /* SR25_L */
#define RZV_GPIO_SR25_H_OFFSET                           0x150C  /* SR25_H */
#define RZV_GPIO_SR26_L_OFFSET                           0x1510  /* SR26_L */
#define RZV_GPIO_SR26_H_OFFSET                           0x1514  /* SR26_H */
#define RZV_GPIO_SR27_L_OFFSET                           0x1518  /* SR27_L */
#define RZV_GPIO_SR27_H_OFFSET                           0x151C  /* SR27_H */
#define RZV_GPIO_SR28_L_OFFSET                           0x1520  /* SR28_L */
#define RZV_GPIO_SR28_H_OFFSET                           0x1524  /* SR28_H */
#define RZV_GPIO_SR29_L_OFFSET                           0x1528  /* SR29_L */
#define RZV_GPIO_SR29_H_OFFSET                           0x152C  /* SR29_H */
#define RZV_GPIO_SR2A_L_OFFSET                           0x1530  /* SR2A_L */
#define RZV_GPIO_SR2A_H_OFFSET                           0x1534  /* SR2A_H */
#define RZV_GPIO_SR2B_L_OFFSET                           0x1538  /* SR2B_L */
#define RZV_GPIO_SR2B_H_OFFSET                           0x153C  /* SR2B_H */
#define RZV_GPIO_IEN3_L_OFFSET                           0x17F8  /* IEN3_L */
#define RZV_GPIO_IEN3_H_OFFSET                           0x17FC  /* IEN3_H */
#define RZV_GPIO_IEN9_L_OFFSET                           0x1828  /* IEN9_L */
#define RZV_GPIO_IEN9_H_OFFSET                           0x182C  /* IEN9_H */
#define RZV_GPIO_IENA_L_OFFSET                           0x1830  /* IENA_L */
#define RZV_GPIO_IENA_H_OFFSET                           0x1834  /* IENA_H */
#define RZV_GPIO_IENB_L_OFFSET                           0x1838  /* IENB_L */
#define RZV_GPIO_IENB_H_OFFSET                           0x183C  /* IENB_H */
#define RZV_GPIO_IENC_L_OFFSET                           0x1840  /* IENC_L */
#define RZV_GPIO_IENC_H_OFFSET                           0x1844  /* IENC_H */
#define RZV_GPIO_IENF_L_OFFSET                           0x1858  /* IENF_L */
#define RZV_GPIO_IENF_H_OFFSET                           0x185C  /* IENF_H */
#define RZV_GPIO_IEN12_L_OFFSET                          0x1870  /* IEN12_L */
#define RZV_GPIO_IEN12_H_OFFSET                          0x1874  /* IEN12_H */
#define RZV_GPIO_IEN2B_L_OFFSET                          0x1878  /* IEN2B_L */
#define RZV_GPIO_IEN2B_H_OFFSET                          0x187C  /* IEN2B_H */
#define RZV_GPIO_PUPD5_L_OFFSET                          0x1C08  /* PUPD5_L */
#define RZV_GPIO_PUPD5_H_OFFSET                          0x1C0C  /* PUPD5_H */
#define RZV_GPIO_PUPD6_L_OFFSET                          0x1C10  /* PUPD6_L */
#define RZV_GPIO_PUPD6_H_OFFSET                          0x1C14  /* PUPD6_H */
#define RZV_GPIO_PUPD7_L_OFFSET                          0x1C18  /* PUPD7_L */
#define RZV_GPIO_PUPD7_H_OFFSET                          0x1C1C  /* PUPD7_H */
#define RZV_GPIO_PUPD8_L_OFFSET                          0x1C20  /* PUPD8_L */
#define RZV_GPIO_PUPD8_H_OFFSET                          0x1C24  /* PUPD8_H */
#define RZV_GPIO_PUPD9_L_OFFSET                          0x1C28  /* PUPD9_L */
#define RZV_GPIO_PUPD9_H_OFFSET                          0x1C2C  /* PUPD9_H */
#define RZV_GPIO_PUPDA_L_OFFSET                          0x1C30  /* PUPDA_L */
#define RZV_GPIO_PUPDA_H_OFFSET                          0x1C34  /* PUPDA_H */
#define RZV_GPIO_PUPDB_L_OFFSET                          0x1C38  /* PUPDB_L */
#define RZV_GPIO_PUPDB_H_OFFSET                          0x1C3C  /* PUPDB_H */
#define RZV_GPIO_PUPDC_L_OFFSET                          0x1C40  /* PUPDC_L */
#define RZV_GPIO_PUPDC_H_OFFSET                          0x1C44  /* PUPDC_H */
#define RZV_GPIO_PUPDF_L_OFFSET                          0x1C58  /* PUPDF_L */
#define RZV_GPIO_PUPDF_H_OFFSET                          0x1C5C  /* PUPDF_H */
#define RZV_GPIO_PUPD10_L_OFFSET                         0x1C60  /* PUPD10_L */
#define RZV_GPIO_PUPD10_H_OFFSET                         0x1C64  /* PUPD10_H */
#define RZV_GPIO_PUPD11_L_OFFSET                         0x1C68  /* PUPD11_L */
#define RZV_GPIO_PUPD11_H_OFFSET                         0x1C6C  /* PUPD11_H */
#define RZV_GPIO_PUPD12_L_OFFSET                         0x1C70  /* PUPD12_L */
#define RZV_GPIO_PUPD12_H_OFFSET                         0x1C74  /* PUPD12_H */
#define RZV_GPIO_PUPD13_L_OFFSET                         0x1C78  /* PUPD13_L */
#define RZV_GPIO_PUPD13_H_OFFSET                         0x1C7C  /* PUPD13_H */
#define RZV_GPIO_PUPD14_L_OFFSET                         0x1C80  /* PUPD14_L */
#define RZV_GPIO_PUPD14_H_OFFSET                         0x1C84  /* PUPD14_H */
#define RZV_GPIO_PUPD20_L_OFFSET                         0x1CE0  /* PUPD20_L */
#define RZV_GPIO_PUPD20_H_OFFSET                         0x1CE4  /* PUPD20_H */
#define RZV_GPIO_PUPD21_L_OFFSET                         0x1CE8  /* PUPD21_L */
#define RZV_GPIO_PUPD21_H_OFFSET                         0x1CEC  /* PUPD21_H */
#define RZV_GPIO_PUPD22_L_OFFSET                         0x1CF0  /* PUPD22_L */
#define RZV_GPIO_PUPD22_H_OFFSET                         0x1CF4  /* PUPD22_H */
#define RZV_GPIO_PUPD23_L_OFFSET                         0x1CF8  /* PUPD23_L */
#define RZV_GPIO_PUPD23_H_OFFSET                         0x1CFC  /* PUPD23_H */
#define RZV_GPIO_PUPD24_L_OFFSET                         0x1D00  /* PUPD24_L */
#define RZV_GPIO_PUPD24_H_OFFSET                         0x1D04  /* PUPD24_H */
#define RZV_GPIO_PUPD25_L_OFFSET                         0x1D08  /* PUPD25_L */
#define RZV_GPIO_PUPD25_H_OFFSET                         0x1D0C  /* PUPD25_H */
#define RZV_GPIO_PUPD26_L_OFFSET                         0x1D10  /* PUPD26_L */
#define RZV_GPIO_PUPD26_H_OFFSET                         0x1D14  /* PUPD26_H */
#define RZV_GPIO_PUPD27_L_OFFSET                         0x1D18  /* PUPD27_L */
#define RZV_GPIO_PUPD27_H_OFFSET                         0x1D1C  /* PUPD27_H */
#define RZV_GPIO_PUPD28_L_OFFSET                         0x1D20  /* PUPD28_L */
#define RZV_GPIO_PUPD28_H_OFFSET                         0x1D24  /* PUPD28_H */
#define RZV_GPIO_PUPD29_L_OFFSET                         0x1D28  /* PUPD29_L */
#define RZV_GPIO_PUPD29_H_OFFSET                         0x1D2C  /* PUPD29_H */
#define RZV_GPIO_PUPD2A_L_OFFSET                         0x1D30  /* PUPD2A_L */
#define RZV_GPIO_PUPD2A_H_OFFSET                         0x1D34  /* PUPD2A_H */
#define RZV_GPIO_PUPD2B_L_OFFSET                         0x1D38  /* PUPD2B_L */
#define RZV_GPIO_PUPD2B_H_OFFSET                         0x1D3C  /* PUPD2B_H */
#define RZV_GPIO_FILONOFF1_L_OFFSET                      0x1FE8  /* FILONOFF1_L */
#define RZV_GPIO_FILONOFF1_H_OFFSET                      0x1FEC  /* FILONOFF1_H */
#define RZV_GPIO_FILONOFF20_L_OFFSET                     0x20E0  /* FILONOFF20_L */
#define RZV_GPIO_FILONOFF20_H_OFFSET                     0x20E4  /* FILONOFF20_H */
#define RZV_GPIO_FILONOFF21_L_OFFSET                     0x20E8  /* FILONOFF21_L */
#define RZV_GPIO_FILONOFF21_H_OFFSET                     0x20EC  /* FILONOFF21_H */
#define RZV_GPIO_FILONOFF22_L_OFFSET                     0x20F0  /* FILONOFF22_L */
#define RZV_GPIO_FILONOFF22_H_OFFSET                     0x20F4  /* FILONOFF22_H */
#define RZV_GPIO_FILONOFF23_L_OFFSET                     0x20F8  /* FILONOFF23_L */
#define RZV_GPIO_FILONOFF23_H_OFFSET                     0x20FC  /* FILONOFF23_H */
#define RZV_GPIO_FILONOFF24_L_OFFSET                     0x2100  /* FILONOFF24_L */
#define RZV_GPIO_FILONOFF24_H_OFFSET                     0x2104  /* FILONOFF24_H */
#define RZV_GPIO_FILONOFF25_L_OFFSET                     0x2108  /* FILONOFF25_L */
#define RZV_GPIO_FILONOFF25_H_OFFSET                     0x210C  /* FILONOFF25_H */
#define RZV_GPIO_FILONOFF26_L_OFFSET                     0x2110  /* FILONOFF26_L */
#define RZV_GPIO_FILONOFF26_H_OFFSET                     0x2114  /* FILONOFF26_H */
#define RZV_GPIO_FILONOFF27_L_OFFSET                     0x2118  /* FILONOFF27_L */
#define RZV_GPIO_FILONOFF27_H_OFFSET                     0x211C  /* FILONOFF27_H */
#define RZV_GPIO_FILONOFF28_L_OFFSET                     0x2120  /* FILONOFF28_L */
#define RZV_GPIO_FILONOFF28_H_OFFSET                     0x2124  /* FILONOFF28_H */
#define RZV_GPIO_FILONOFF29_L_OFFSET                     0x2128  /* FILONOFF29_L */
#define RZV_GPIO_FILONOFF29_H_OFFSET                     0x212C  /* FILONOFF29_H */
#define RZV_GPIO_FILONOFF2A_L_OFFSET                     0x2130  /* FILONOFF2A_L */
#define RZV_GPIO_FILONOFF2A_H_OFFSET                     0x2134  /* FILONOFF2A_H */
#define RZV_GPIO_FILONOFF2B_L_OFFSET                     0x2138  /* FILONOFF2B_L */
#define RZV_GPIO_FILONOFF2B_H_OFFSET                     0x213C  /* FILONOFF2B_H */
#define RZV_GPIO_FILNUM1_L_OFFSET                        0x23E8  /* FILNUM1_L */
#define RZV_GPIO_FILNUM1_H_OFFSET                        0x23EC  /* FILNUM1_H */
#define RZV_GPIO_FILNUM20_L_OFFSET                       0x24E0  /* FILNUM20_L */
#define RZV_GPIO_FILNUM20_H_OFFSET                       0x24E4  /* FILNUM20_H */
#define RZV_GPIO_FILNUM21_L_OFFSET                       0x24E8  /* FILNUM21_L */
#define RZV_GPIO_FILNUM21_H_OFFSET                       0x24EC  /* FILNUM21_H */
#define RZV_GPIO_FILNUM22_L_OFFSET                       0x24F0  /* FILNUM22_L */
#define RZV_GPIO_FILNUM22_H_OFFSET                       0x24F4  /* FILNUM22_H */
#define RZV_GPIO_FILNUM23_L_OFFSET                       0x24F8  /* FILNUM23_L */
#define RZV_GPIO_FILNUM23_H_OFFSET                       0x24FC  /* FILNUM23_H */
#define RZV_GPIO_FILNUM24_L_OFFSET                       0x2500  /* FILNUM24_L */
#define RZV_GPIO_FILNUM24_H_OFFSET                       0x2504  /* FILNUM24_H */
#define RZV_GPIO_FILNUM25_L_OFFSET                       0x2508  /* FILNUM25_L */
#define RZV_GPIO_FILNUM25_H_OFFSET                       0x250C  /* FILNUM25_H */
#define RZV_GPIO_FILNUM26_L_OFFSET                       0x2510  /* FILNUM26_L */
#define RZV_GPIO_FILNUM26_H_OFFSET                       0x2514  /* FILNUM26_H */
#define RZV_GPIO_FILNUM27_L_OFFSET                       0x2518  /* FILNUM27_L */
#define RZV_GPIO_FILNUM27_H_OFFSET                       0x251C  /* FILNUM27_H */
#define RZV_GPIO_FILNUM28_L_OFFSET                       0x2520  /* FILNUM28_L */
#define RZV_GPIO_FILNUM28_H_OFFSET                       0x2524  /* FILNUM28_H */
#define RZV_GPIO_FILNUM29_L_OFFSET                       0x2528  /* FILNUM29_L */
#define RZV_GPIO_FILNUM29_H_OFFSET                       0x252C  /* FILNUM29_H */
#define RZV_GPIO_FILNUM2A_L_OFFSET                       0x2530  /* FILNUM2A_L */
#define RZV_GPIO_FILNUM2A_H_OFFSET                       0x2534  /* FILNUM2A_H */
#define RZV_GPIO_FILNUM2B_L_OFFSET                       0x2538  /* FILNUM2B_L */
#define RZV_GPIO_FILNUM2B_H_OFFSET                       0x253C  /* FILNUM2B_H */
#define RZV_GPIO_FILCLKSEL1_L_OFFSET                     0x27E8  /* FILCLKSEL1_L */
#define RZV_GPIO_FILCLKSEL1_H_OFFSET                     0x27EC  /* FILCLKSEL1_H */
#define RZV_GPIO_FILCLKSEL20_L_OFFSET                    0x28E0  /* FILCLKSEL20_L */
#define RZV_GPIO_FILCLKSEL20_H_OFFSET                    0x28E4  /* FILCLKSEL20_H */
#define RZV_GPIO_FILCLKSEL21_L_OFFSET                    0x28E8  /* FILCLKSEL21_L */
#define RZV_GPIO_FILCLKSEL21_H_OFFSET                    0x28EC  /* FILCLKSEL21_H */
#define RZV_GPIO_FILCLKSEL22_L_OFFSET                    0x28F0  /* FILCLKSEL22_L */
#define RZV_GPIO_FILCLKSEL22_H_OFFSET                    0x28F4  /* FILCLKSEL22_H */
#define RZV_GPIO_FILCLKSEL23_L_OFFSET                    0x28F8  /* FILCLKSEL23_L */
#define RZV_GPIO_FILCLKSEL23_H_OFFSET                    0x28FC  /* FILCLKSEL23_H */
#define RZV_GPIO_FILCLKSEL24_L_OFFSET                    0x2900  /* FILCLKSEL24_L */
#define RZV_GPIO_FILCLKSEL24_H_OFFSET                    0x2904  /* FILCLKSEL24_H */
#define RZV_GPIO_FILCLKSEL25_L_OFFSET                    0x2908  /* FILCLKSEL25_L */
#define RZV_GPIO_FILCLKSEL25_H_OFFSET                    0x290C  /* FILCLKSEL25_H */
#define RZV_GPIO_FILCLKSEL26_L_OFFSET                    0x2910  /* FILCLKSEL26_L */
#define RZV_GPIO_FILCLKSEL26_H_OFFSET                    0x2914  /* FILCLKSEL26_H */
#define RZV_GPIO_FILCLKSEL27_L_OFFSET                    0x2918  /* FILCLKSEL27_L */
#define RZV_GPIO_FILCLKSEL27_H_OFFSET                    0x291C  /* FILCLKSEL27_H */
#define RZV_GPIO_FILCLKSEL28_L_OFFSET                    0x2920  /* FILCLKSEL28_L */
#define RZV_GPIO_FILCLKSEL28_H_OFFSET                    0x2924  /* FILCLKSEL28_H */
#define RZV_GPIO_FILCLKSEL29_L_OFFSET                    0x2928  /* FILCLKSEL29_L */
#define RZV_GPIO_FILCLKSEL29_H_OFFSET                    0x292C  /* FILCLKSEL29_H */
#define RZV_GPIO_FILCLKSEL2A_L_OFFSET                    0x2930  /* FILCLKSEL2A_L */
#define RZV_GPIO_FILCLKSEL2A_H_OFFSET                    0x2934  /* FILCLKSEL2A_H */
#define RZV_GPIO_FILCLKSEL2B_L_OFFSET                    0x2938  /* FILCLKSEL2B_L */
#define RZV_GPIO_FILCLKSEL2B_H_OFFSET                    0x293C  /* FILCLKSEL2B_H */
#define RZV_GPIO_ISEL20_L_OFFSET                         0x2CE0  /* ISEL20_L */
#define RZV_GPIO_ISEL20_H_OFFSET                         0x2CE4  /* ISEL20_H */
#define RZV_GPIO_ISEL21_L_OFFSET                         0x2CE8  /* ISEL21_L */
#define RZV_GPIO_ISEL21_H_OFFSET                         0x2CEC  /* ISEL21_H */
#define RZV_GPIO_ISEL22_L_OFFSET                         0x2CF0  /* ISEL22_L */
#define RZV_GPIO_ISEL22_H_OFFSET                         0x2CF4  /* ISEL22_H */
#define RZV_GPIO_ISEL23_L_OFFSET                         0x2CF8  /* ISEL23_L */
#define RZV_GPIO_ISEL23_H_OFFSET                         0x2CFC  /* ISEL23_H */
#define RZV_GPIO_ISEL24_L_OFFSET                         0x2D00  /* ISEL24_L */
#define RZV_GPIO_ISEL24_H_OFFSET                         0x2D04  /* ISEL24_H */
#define RZV_GPIO_ISEL25_L_OFFSET                         0x2D08  /* ISEL25_L */
#define RZV_GPIO_ISEL25_H_OFFSET                         0x2D0C  /* ISEL25_H */
#define RZV_GPIO_ISEL26_L_OFFSET                         0x2D10  /* ISEL26_L */
#define RZV_GPIO_ISEL26_H_OFFSET                         0x2D14  /* ISEL26_H */
#define RZV_GPIO_ISEL27_L_OFFSET                         0x2D18  /* ISEL27_L */
#define RZV_GPIO_ISEL27_H_OFFSET                         0x2D1C  /* ISEL27_H */
#define RZV_GPIO_ISEL28_L_OFFSET                         0x2D20  /* ISEL28_L */
#define RZV_GPIO_ISEL28_H_OFFSET                         0x2D24  /* ISEL28_H */
#define RZV_GPIO_ISEL29_L_OFFSET                         0x2D28  /* ISEL29_L */
#define RZV_GPIO_ISEL29_H_OFFSET                         0x2D2C  /* ISEL29_H */
#define RZV_GPIO_ISEL2A_L_OFFSET                         0x2D30  /* ISEL2A_L */
#define RZV_GPIO_ISEL2A_H_OFFSET                         0x2D34  /* ISEL2A_H */
#define RZV_GPIO_ISEL2B_L_OFFSET                         0x2D38  /* ISEL2B_L */
#define RZV_GPIO_ISEL2B_H_OFFSET                         0x2D3C  /* ISEL2B_H */
#define RZV_GPIO_NOD5_L_OFFSET                           0x3008  /* NOD5_L */
#define RZV_GPIO_NOD5_H_OFFSET                           0x300C  /* NOD5_H */
#define RZV_GPIO_NOD20_L_OFFSET                          0x30E0  /* NOD20_L */
#define RZV_GPIO_NOD20_H_OFFSET                          0x30E4  /* NOD20_H */
#define RZV_GPIO_NOD21_L_OFFSET                          0x30E8  /* NOD21_L */
#define RZV_GPIO_NOD21_H_OFFSET                          0x30EC  /* NOD21_H */
#define RZV_GPIO_NOD22_L_OFFSET                          0x30F0  /* NOD22_L */
#define RZV_GPIO_NOD22_H_OFFSET                          0x30F4  /* NOD22_H */
#define RZV_GPIO_NOD23_L_OFFSET                          0x30F8  /* NOD23_L */
#define RZV_GPIO_NOD23_H_OFFSET                          0x30FC  /* NOD23_H */
#define RZV_GPIO_NOD24_L_OFFSET                          0x3100  /* NOD24_L */
#define RZV_GPIO_NOD24_H_OFFSET                          0x3104  /* NOD24_H */
#define RZV_GPIO_NOD25_L_OFFSET                          0x3108  /* NOD25_L */
#define RZV_GPIO_NOD25_H_OFFSET                          0x310C  /* NOD25_H */
#define RZV_GPIO_NOD26_L_OFFSET                          0x3110  /* NOD26_L */
#define RZV_GPIO_NOD26_H_OFFSET                          0x3114  /* NOD26_H */
#define RZV_GPIO_NOD27_L_OFFSET                          0x3118  /* NOD27_L */
#define RZV_GPIO_NOD27_H_OFFSET                          0x311C  /* NOD27_H */
#define RZV_GPIO_NOD28_L_OFFSET                          0x3120  /* NOD28_L */
#define RZV_GPIO_NOD28_H_OFFSET                          0x3124  /* NOD28_H */
#define RZV_GPIO_NOD29_L_OFFSET                          0x3128  /* NOD29_L */
#define RZV_GPIO_NOD29_H_OFFSET                          0x312C  /* NOD29_H */
#define RZV_GPIO_NOD2A_L_OFFSET                          0x3130  /* NOD2A_L */
#define RZV_GPIO_NOD2A_H_OFFSET                          0x3134  /* NOD2A_H */
#define RZV_GPIO_NOD2B_L_OFFSET                          0x3138  /* NOD2B_L */
#define RZV_GPIO_NOD2B_H_OFFSET                          0x313C  /* NOD2B_H */
#define RZV_GPIO_SMT20_L_OFFSET                          0x34E0  /* SMT20_L */
#define RZV_GPIO_SMT20_H_OFFSET                          0x34E4  /* SMT20_H */
#define RZV_GPIO_SMT21_L_OFFSET                          0x34E8  /* SMT21_L */
#define RZV_GPIO_SMT21_H_OFFSET                          0x34EC  /* SMT21_H */
#define RZV_GPIO_SMT23_L_OFFSET                          0x34F8  /* SMT23_L */
#define RZV_GPIO_SMT23_H_OFFSET                          0x34FC  /* SMT23_H */
#define RZV_GPIO_SMT24_L_OFFSET                          0x3500  /* SMT24_L */
#define RZV_GPIO_SMT24_H_OFFSET                          0x3504  /* SMT24_H */
#define RZV_GPIO_SMT25_L_OFFSET                          0x3508  /* SMT25_L */
#define RZV_GPIO_SMT25_H_OFFSET                          0x350C  /* SMT25_H */
#define RZV_GPIO_SMT26_L_OFFSET                          0x3510  /* SMT26_L */
#define RZV_GPIO_SMT26_H_OFFSET                          0x3514  /* SMT26_H */
#define RZV_GPIO_SMT27_L_OFFSET                          0x3518  /* SMT27_L */
#define RZV_GPIO_SMT27_H_OFFSET                          0x351C  /* SMT27_H */
#define RZV_GPIO_SMT28_L_OFFSET                          0x3520  /* SMT28_L */
#define RZV_GPIO_SMT28_H_OFFSET                          0x3524  /* SMT28_H */
#define RZV_GPIO_SMT29_L_OFFSET                          0x3528  /* SMT29_L */
#define RZV_GPIO_SMT29_H_OFFSET                          0x352C  /* SMT29_H */
#define RZV_GPIO_SMT2A_L_OFFSET                          0x3530  /* SMT2A_L */
#define RZV_GPIO_SMT2A_H_OFFSET                          0x3534  /* SMT2A_H */
#define RZV_GPIO_SMT2B_L_OFFSET                          0x3538  /* SMT2B_L */
#define RZV_GPIO_SMT2B_H_OFFSET                          0x353C  /* SMT2B_H */
#define RZV_GPIO_ELC_DPTC_OFFSET                         0x37F0  /* ELC_DPTC */
#define RZV_GPIO_PFC_ELC_ELSR2_OFFSET                    0x37F1  /* PFC_ELC_ELSR2 */
#define RZV_GPIO_PFC_OSCBYPS_OFFSET                      0x3BE0  /* PFC_OSCBYPS */
#define RZV_GPIO_PWPR_OFFSET                             0x3BE4  /* PWPR (32-bit) */

/* PWPR Register bit definitions for RZV2H.
 * Phase-03 fix [High-5, audit §2, §8]: RZV2H uses REGWE_A/REGWE_B semantics,
 * NOT RA-style BOWI/PFSWE. PWPR is a 32-bit register (8-bit writes may be
 * silently dropped on AXI bus). Always use 32-bit RMW.
 *
 * Source: bsp_feature.h (rzv2h/cr):
 *   BSP_FEATURE_IOPORT_PFC_PWPR_REGWE_A_OFFSET = 6U
 *   BSP_FEATURE_IOPORT_PFC_PWPR_REGWE_A_MASK   = 0xFFFFFFBF  (clears bit 6)
 *   BSP_FEATURE_IOPORT_PFC_PWPR_REGWE_B_OFFSET = 5U
 *   BSP_FEATURE_IOPORT_PFC_PWPR_REGWE_B_MASK   = 0xFFFFFFDF  (clears bit 5)
 *
 * Enable  PFC/PMC write: *pwpr = (*pwpr & REGWE_A_MASK) | REGWE_A_BIT
 * Disable PFC/PMC write: *pwpr = (*pwpr & REGWE_A_MASK)
 */
#define RZV_GPIO_PWPR_REGWE_A_OFFSET  6U
#define RZV_GPIO_PWPR_REGWE_A_BIT     (1U << RZV_GPIO_PWPR_REGWE_A_OFFSET)
#define RZV_GPIO_PWPR_REGWE_A_MASK    (0xFFFFFFBFU)  /* preserve all except bit6 */
#define RZV_GPIO_PWPR_REGWE_B_OFFSET  5U
#define RZV_GPIO_PWPR_REGWE_B_BIT     (1U << RZV_GPIO_PWPR_REGWE_B_OFFSET)
#define RZV_GPIO_PWPR_REGWE_B_MASK    (0xFFFFFFDFU)  /* preserve all except bit5 */
#define RZV_GPIO_PFC_FILONOFF_IRQ_OFFSET                 0x3BE8  /* PFC_FILONOFF_IRQ */
#define RZV_GPIO_PFC_FILNUM_IRQ_OFFSET                   0x3BEC  /* PFC_FILNUM_IRQ */
#define RZV_GPIO_PFC_FILCLKSEL_IRQ_OFFSET                0x3BF0  /* PFC_FILCLKSEL_IRQ */
#define RZV_GPIO_PFC_FILONOFF_DMAC_REQ_OFFSET            0x3BF4  /* PFC_FILONOFF_DMAC_REQ */
#define RZV_GPIO_PFC_FILNUM_DMAC_REQ_OFFSET              0x3BF8  /* PFC_FILNUM_DMAC_REQ */
#define RZV_GPIO_PFC_FILCLKSEL_DMAC_REQ_OFFSET           0x3BFC  /* PFC_FILCLKSEL_DMAC_REQ */
#define RZV_GPIO_PFC_OEN_OFFSET                          0x3C20  /* PFC_OEN */

/* GP-group register offset macros for NuttX ports 0-11 (= HW ports 20-2B).
 *
 * Phase-03 fix [High-6, High-7, High-8, audit §2]: Replace hand-rolled
 * IOLH/PUPD formulas in rzv_gpio.c with these lookup macros.
 *
 * Source: bsp_feature.h (rzv2h/cr):
 *   BSP_FEATURE_IOPORT_GP_REG_BASE_NUM = 20  (GP group base = port 0x20)
 *   IOLH GP formula: offset = IOLH20_L + port*8  (port is 0-based in GP)
 *   PUPD GP formula: offset = PUPD20_L + port*8
 *   ISEL GP formula: offset = ISEL20_L + port*8
 *
 * For NuttX port N (0-11), pin P (0-7 → _L, 8-15 → _H):
 *   IOLH_L offset = RZV_GPIO_IOLH20_L_OFFSET + N*8
 *   IOLH_H offset = RZV_GPIO_IOLH20_L_OFFSET + N*8 + 4
 *   PUPD_L offset = RZV_GPIO_PUPD20_L_OFFSET + N*8
 *   PUPD_H offset = RZV_GPIO_PUPD20_L_OFFSET + N*8 + 4
 *   ISEL_L offset = RZV_GPIO_ISEL20_L_OFFSET + N*8
 *   ISEL_H offset = RZV_GPIO_ISEL20_L_OFFSET + N*8 + 4
 *
 * These macros replace the old formulas:
 *   OLD (wrong): iolh_offset = 0x0FFC + (port+3)*8  — used SP-group base
 *   OLD (wrong): pupd_offset = 0x1C10 + (port-5)*8  — missing ports 0-4
 *   OLD (wrong): isel_offset = 0x2CE8 + port*8      — formula was coincidentally
 *                                                      correct but unsourced
 */
#define RZV_GPIO_GP_IOLH_L_OFFSET(port) \
    (RZV_GPIO_IOLH20_L_OFFSET + (uint32_t)(port) * 8U)
#define RZV_GPIO_GP_IOLH_H_OFFSET(port) \
    (RZV_GPIO_IOLH20_L_OFFSET + (uint32_t)(port) * 8U + 4U)
#define RZV_GPIO_GP_PUPD_L_OFFSET(port) \
    (RZV_GPIO_PUPD20_L_OFFSET + (uint32_t)(port) * 8U)
#define RZV_GPIO_GP_PUPD_H_OFFSET(port) \
    (RZV_GPIO_PUPD20_L_OFFSET + (uint32_t)(port) * 8U + 4U)
#define RZV_GPIO_GP_ISEL_L_OFFSET(port) \
    (RZV_GPIO_ISEL20_L_OFFSET + (uint32_t)(port) * 8U)
#define RZV_GPIO_GP_ISEL_H_OFFSET(port) \
    (RZV_GPIO_ISEL20_L_OFFSET + (uint32_t)(port) * 8U + 4U)
#define RZV_GPIO_GP_SR_L_OFFSET(port) \
    (RZV_GPIO_SR20_L_OFFSET + (uint32_t)(port) * 8U)
#define RZV_GPIO_GP_SR_H_OFFSET(port) \
    (RZV_GPIO_SR20_L_OFFSET + (uint32_t)(port) * 8U + 4U)
#define RZV_GPIO_GP_NOD_L_OFFSET(port) \
    (RZV_GPIO_NOD20_L_OFFSET + (uint32_t)(port) * 8U)
#define RZV_GPIO_GP_NOD_H_OFFSET(port) \
    (RZV_GPIO_NOD20_L_OFFSET + (uint32_t)(port) * 8U + 4U)

/* GPIO Register Addresses *************************************************/

#define RZV_GPIO_P(m)                           (RZV_GPIO_BASE + RZV_GPIO_P_OFFSET(m))
#define RZV_GPIO_PFC(m)                         (RZV_GPIO_BASE + RZV_GPIO_PFC_OFFSET(m))
#define RZV_GPIO_PIN(m)                         (RZV_GPIO_BASE + RZV_GPIO_PIN_OFFSET(m))
#define RZV_GPIO_PM(m)                          (RZV_GPIO_BASE + RZV_GPIO_PM_OFFSET(m))
#define RZV_GPIO_PMC(m)                         (RZV_GPIO_BASE + RZV_GPIO_PMC_OFFSET(m))
#define RZV_GPIO_ELC_PDBF                            (RZV_GPIO_BASE + RZV_GPIO_ELC_PDBF_OFFSET)
#define RZV_GPIO_P2A                                 (RZV_GPIO_BASE + RZV_GPIO_P2A_OFFSET)
#define RZV_GPIO_P2B                                 (RZV_GPIO_BASE + RZV_GPIO_P2B_OFFSET)
#define RZV_GPIO_PM2A                                (RZV_GPIO_BASE + RZV_GPIO_PM2A_OFFSET)
#define RZV_GPIO_PM2B                                (RZV_GPIO_BASE + RZV_GPIO_PM2B_OFFSET)
#define RZV_GPIO_PMC2A                               (RZV_GPIO_BASE + RZV_GPIO_PMC2A_OFFSET)
#define RZV_GPIO_PMC2B                               (RZV_GPIO_BASE + RZV_GPIO_PMC2B_OFFSET)
#define RZV_GPIO_PFC2A                               (RZV_GPIO_BASE + RZV_GPIO_PFC2A_OFFSET)
#define RZV_GPIO_PFC2B                               (RZV_GPIO_BASE + RZV_GPIO_PFC2B_OFFSET)
#define RZV_GPIO_PIN2A                               (RZV_GPIO_BASE + RZV_GPIO_PIN2A_OFFSET)
#define RZV_GPIO_PIN2B                               (RZV_GPIO_BASE + RZV_GPIO_PIN2B_OFFSET)
#define RZV_GPIO_IOLH3_L                             (RZV_GPIO_BASE + RZV_GPIO_IOLH3_L_OFFSET)
#define RZV_GPIO_IOLH3_H                             (RZV_GPIO_BASE + RZV_GPIO_IOLH3_H_OFFSET)
#define RZV_GPIO_IOLH5_L                             (RZV_GPIO_BASE + RZV_GPIO_IOLH5_L_OFFSET)
#define RZV_GPIO_IOLH5_H                             (RZV_GPIO_BASE + RZV_GPIO_IOLH5_H_OFFSET)
#define RZV_GPIO_IOLH6_L                             (RZV_GPIO_BASE + RZV_GPIO_IOLH6_L_OFFSET)
#define RZV_GPIO_IOLH6_H                             (RZV_GPIO_BASE + RZV_GPIO_IOLH6_H_OFFSET)
#define RZV_GPIO_IOLH7_L                             (RZV_GPIO_BASE + RZV_GPIO_IOLH7_L_OFFSET)
#define RZV_GPIO_IOLH7_H                             (RZV_GPIO_BASE + RZV_GPIO_IOLH7_H_OFFSET)
#define RZV_GPIO_IOLH8_L                             (RZV_GPIO_BASE + RZV_GPIO_IOLH8_L_OFFSET)
#define RZV_GPIO_IOLH8_H                             (RZV_GPIO_BASE + RZV_GPIO_IOLH8_H_OFFSET)
#define RZV_GPIO_IOLH9_L                             (RZV_GPIO_BASE + RZV_GPIO_IOLH9_L_OFFSET)
#define RZV_GPIO_IOLH9_H                             (RZV_GPIO_BASE + RZV_GPIO_IOLH9_H_OFFSET)
#define RZV_GPIO_IOLHA_L                             (RZV_GPIO_BASE + RZV_GPIO_IOLHA_L_OFFSET)
#define RZV_GPIO_IOLHA_H                             (RZV_GPIO_BASE + RZV_GPIO_IOLHA_H_OFFSET)
#define RZV_GPIO_IOLHB_L                             (RZV_GPIO_BASE + RZV_GPIO_IOLHB_L_OFFSET)
#define RZV_GPIO_IOLHB_H                             (RZV_GPIO_BASE + RZV_GPIO_IOLHB_H_OFFSET)
#define RZV_GPIO_IOLHC_L                             (RZV_GPIO_BASE + RZV_GPIO_IOLHC_L_OFFSET)
#define RZV_GPIO_IOLHC_H                             (RZV_GPIO_BASE + RZV_GPIO_IOLHC_H_OFFSET)
#define RZV_GPIO_IOLHE_L                             (RZV_GPIO_BASE + RZV_GPIO_IOLHE_L_OFFSET)
#define RZV_GPIO_IOLHE_H                             (RZV_GPIO_BASE + RZV_GPIO_IOLHE_H_OFFSET)
#define RZV_GPIO_IOLHF_L                             (RZV_GPIO_BASE + RZV_GPIO_IOLHF_L_OFFSET)
#define RZV_GPIO_IOLHF_H                             (RZV_GPIO_BASE + RZV_GPIO_IOLHF_H_OFFSET)
#define RZV_GPIO_IOLH10_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH10_L_OFFSET)
#define RZV_GPIO_IOLH10_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH10_H_OFFSET)
#define RZV_GPIO_IOLH11_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH11_L_OFFSET)
#define RZV_GPIO_IOLH11_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH11_H_OFFSET)
#define RZV_GPIO_IOLH12_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH12_L_OFFSET)
#define RZV_GPIO_IOLH12_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH12_H_OFFSET)
#define RZV_GPIO_IOLH13_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH13_L_OFFSET)
#define RZV_GPIO_IOLH13_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH13_H_OFFSET)
#define RZV_GPIO_IOLH14_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH14_L_OFFSET)
#define RZV_GPIO_IOLH14_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH14_H_OFFSET)
#define RZV_GPIO_IOLH20_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH20_L_OFFSET)
#define RZV_GPIO_IOLH20_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH20_H_OFFSET)
#define RZV_GPIO_IOLH21_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH21_L_OFFSET)
#define RZV_GPIO_IOLH21_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH21_H_OFFSET)
#define RZV_GPIO_IOLH22_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH22_L_OFFSET)
#define RZV_GPIO_IOLH22_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH22_H_OFFSET)
#define RZV_GPIO_IOLH23_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH23_L_OFFSET)
#define RZV_GPIO_IOLH23_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH23_H_OFFSET)
#define RZV_GPIO_IOLH24_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH24_L_OFFSET)
#define RZV_GPIO_IOLH24_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH24_H_OFFSET)
#define RZV_GPIO_IOLH25_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH25_L_OFFSET)
#define RZV_GPIO_IOLH25_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH25_H_OFFSET)
#define RZV_GPIO_IOLH26_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH26_L_OFFSET)
#define RZV_GPIO_IOLH26_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH26_H_OFFSET)
#define RZV_GPIO_IOLH27_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH27_L_OFFSET)
#define RZV_GPIO_IOLH27_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH27_H_OFFSET)
#define RZV_GPIO_IOLH28_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH28_L_OFFSET)
#define RZV_GPIO_IOLH28_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH28_H_OFFSET)
#define RZV_GPIO_IOLH29_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH29_L_OFFSET)
#define RZV_GPIO_IOLH29_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH29_H_OFFSET)
#define RZV_GPIO_IOLH2A_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH2A_L_OFFSET)
#define RZV_GPIO_IOLH2A_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH2A_H_OFFSET)
#define RZV_GPIO_IOLH2B_L                            (RZV_GPIO_BASE + RZV_GPIO_IOLH2B_L_OFFSET)
#define RZV_GPIO_IOLH2B_H                            (RZV_GPIO_BASE + RZV_GPIO_IOLH2B_H_OFFSET)
#define RZV_GPIO_SR3_L                               (RZV_GPIO_BASE + RZV_GPIO_SR3_L_OFFSET)
#define RZV_GPIO_SR3_H                               (RZV_GPIO_BASE + RZV_GPIO_SR3_H_OFFSET)
#define RZV_GPIO_SR5_L                               (RZV_GPIO_BASE + RZV_GPIO_SR5_L_OFFSET)
#define RZV_GPIO_SR5_H                               (RZV_GPIO_BASE + RZV_GPIO_SR5_H_OFFSET)
#define RZV_GPIO_SR6_L                               (RZV_GPIO_BASE + RZV_GPIO_SR6_L_OFFSET)
#define RZV_GPIO_SR6_H                               (RZV_GPIO_BASE + RZV_GPIO_SR6_H_OFFSET)
#define RZV_GPIO_SR7_L                               (RZV_GPIO_BASE + RZV_GPIO_SR7_L_OFFSET)
#define RZV_GPIO_SR7_H                               (RZV_GPIO_BASE + RZV_GPIO_SR7_H_OFFSET)
#define RZV_GPIO_SR8_L                               (RZV_GPIO_BASE + RZV_GPIO_SR8_L_OFFSET)
#define RZV_GPIO_SR8_H                               (RZV_GPIO_BASE + RZV_GPIO_SR8_H_OFFSET)
#define RZV_GPIO_SR9_L                               (RZV_GPIO_BASE + RZV_GPIO_SR9_L_OFFSET)
#define RZV_GPIO_SR9_H                               (RZV_GPIO_BASE + RZV_GPIO_SR9_H_OFFSET)
#define RZV_GPIO_SRA_L                               (RZV_GPIO_BASE + RZV_GPIO_SRA_L_OFFSET)
#define RZV_GPIO_SRA_H                               (RZV_GPIO_BASE + RZV_GPIO_SRA_H_OFFSET)
#define RZV_GPIO_SRB_L                               (RZV_GPIO_BASE + RZV_GPIO_SRB_L_OFFSET)
#define RZV_GPIO_SRB_H                               (RZV_GPIO_BASE + RZV_GPIO_SRB_H_OFFSET)
#define RZV_GPIO_SRC_L                               (RZV_GPIO_BASE + RZV_GPIO_SRC_L_OFFSET)
#define RZV_GPIO_SRC_H                               (RZV_GPIO_BASE + RZV_GPIO_SRC_H_OFFSET)
#define RZV_GPIO_SRE_L                               (RZV_GPIO_BASE + RZV_GPIO_SRE_L_OFFSET)
#define RZV_GPIO_SRE_H                               (RZV_GPIO_BASE + RZV_GPIO_SRE_H_OFFSET)
#define RZV_GPIO_SRF_L                               (RZV_GPIO_BASE + RZV_GPIO_SRF_L_OFFSET)
#define RZV_GPIO_SRF_H                               (RZV_GPIO_BASE + RZV_GPIO_SRF_H_OFFSET)
#define RZV_GPIO_SR10_L                              (RZV_GPIO_BASE + RZV_GPIO_SR10_L_OFFSET)
#define RZV_GPIO_SR10_H                              (RZV_GPIO_BASE + RZV_GPIO_SR10_H_OFFSET)
#define RZV_GPIO_SR11_L                              (RZV_GPIO_BASE + RZV_GPIO_SR11_L_OFFSET)
#define RZV_GPIO_SR11_H                              (RZV_GPIO_BASE + RZV_GPIO_SR11_H_OFFSET)
#define RZV_GPIO_SR12_L                              (RZV_GPIO_BASE + RZV_GPIO_SR12_L_OFFSET)
#define RZV_GPIO_SR12_H                              (RZV_GPIO_BASE + RZV_GPIO_SR12_H_OFFSET)
#define RZV_GPIO_SR13_L                              (RZV_GPIO_BASE + RZV_GPIO_SR13_L_OFFSET)
#define RZV_GPIO_SR13_H                              (RZV_GPIO_BASE + RZV_GPIO_SR13_H_OFFSET)
#define RZV_GPIO_SR14_L                              (RZV_GPIO_BASE + RZV_GPIO_SR14_L_OFFSET)
#define RZV_GPIO_SR14_H                              (RZV_GPIO_BASE + RZV_GPIO_SR14_H_OFFSET)
#define RZV_GPIO_SR20_L                              (RZV_GPIO_BASE + RZV_GPIO_SR20_L_OFFSET)
#define RZV_GPIO_SR20_H                              (RZV_GPIO_BASE + RZV_GPIO_SR20_H_OFFSET)
#define RZV_GPIO_SR21_L                              (RZV_GPIO_BASE + RZV_GPIO_SR21_L_OFFSET)
#define RZV_GPIO_SR21_H                              (RZV_GPIO_BASE + RZV_GPIO_SR21_H_OFFSET)
#define RZV_GPIO_SR23_L                              (RZV_GPIO_BASE + RZV_GPIO_SR23_L_OFFSET)
#define RZV_GPIO_SR23_H                              (RZV_GPIO_BASE + RZV_GPIO_SR23_H_OFFSET)
#define RZV_GPIO_SR24_L                              (RZV_GPIO_BASE + RZV_GPIO_SR24_L_OFFSET)
#define RZV_GPIO_SR24_H                              (RZV_GPIO_BASE + RZV_GPIO_SR24_H_OFFSET)
#define RZV_GPIO_SR25_L                              (RZV_GPIO_BASE + RZV_GPIO_SR25_L_OFFSET)
#define RZV_GPIO_SR25_H                              (RZV_GPIO_BASE + RZV_GPIO_SR25_H_OFFSET)
#define RZV_GPIO_SR26_L                              (RZV_GPIO_BASE + RZV_GPIO_SR26_L_OFFSET)
#define RZV_GPIO_SR26_H                              (RZV_GPIO_BASE + RZV_GPIO_SR26_H_OFFSET)
#define RZV_GPIO_SR27_L                              (RZV_GPIO_BASE + RZV_GPIO_SR27_L_OFFSET)
#define RZV_GPIO_SR27_H                              (RZV_GPIO_BASE + RZV_GPIO_SR27_H_OFFSET)
#define RZV_GPIO_SR28_L                              (RZV_GPIO_BASE + RZV_GPIO_SR28_L_OFFSET)
#define RZV_GPIO_SR28_H                              (RZV_GPIO_BASE + RZV_GPIO_SR28_H_OFFSET)
#define RZV_GPIO_SR29_L                              (RZV_GPIO_BASE + RZV_GPIO_SR29_L_OFFSET)
#define RZV_GPIO_SR29_H                              (RZV_GPIO_BASE + RZV_GPIO_SR29_H_OFFSET)
#define RZV_GPIO_SR2A_L                              (RZV_GPIO_BASE + RZV_GPIO_SR2A_L_OFFSET)
#define RZV_GPIO_SR2A_H                              (RZV_GPIO_BASE + RZV_GPIO_SR2A_H_OFFSET)
#define RZV_GPIO_SR2B_L                              (RZV_GPIO_BASE + RZV_GPIO_SR2B_L_OFFSET)
#define RZV_GPIO_SR2B_H                              (RZV_GPIO_BASE + RZV_GPIO_SR2B_H_OFFSET)
#define RZV_GPIO_IEN3_L                              (RZV_GPIO_BASE + RZV_GPIO_IEN3_L_OFFSET)
#define RZV_GPIO_IEN3_H                              (RZV_GPIO_BASE + RZV_GPIO_IEN3_H_OFFSET)
#define RZV_GPIO_IEN9_L                              (RZV_GPIO_BASE + RZV_GPIO_IEN9_L_OFFSET)
#define RZV_GPIO_IEN9_H                              (RZV_GPIO_BASE + RZV_GPIO_IEN9_H_OFFSET)
#define RZV_GPIO_IENA_L                              (RZV_GPIO_BASE + RZV_GPIO_IENA_L_OFFSET)
#define RZV_GPIO_IENA_H                              (RZV_GPIO_BASE + RZV_GPIO_IENA_H_OFFSET)
#define RZV_GPIO_IENB_L                              (RZV_GPIO_BASE + RZV_GPIO_IENB_L_OFFSET)
#define RZV_GPIO_IENB_H                              (RZV_GPIO_BASE + RZV_GPIO_IENB_H_OFFSET)
#define RZV_GPIO_IENC_L                              (RZV_GPIO_BASE + RZV_GPIO_IENC_L_OFFSET)
#define RZV_GPIO_IENC_H                              (RZV_GPIO_BASE + RZV_GPIO_IENC_H_OFFSET)
#define RZV_GPIO_IENF_L                              (RZV_GPIO_BASE + RZV_GPIO_IENF_L_OFFSET)
#define RZV_GPIO_IENF_H                              (RZV_GPIO_BASE + RZV_GPIO_IENF_H_OFFSET)
#define RZV_GPIO_IEN12_L                             (RZV_GPIO_BASE + RZV_GPIO_IEN12_L_OFFSET)
#define RZV_GPIO_IEN12_H                             (RZV_GPIO_BASE + RZV_GPIO_IEN12_H_OFFSET)
#define RZV_GPIO_IEN2B_L                             (RZV_GPIO_BASE + RZV_GPIO_IEN2B_L_OFFSET)
#define RZV_GPIO_IEN2B_H                             (RZV_GPIO_BASE + RZV_GPIO_IEN2B_H_OFFSET)
#define RZV_GPIO_PUPD5_L                             (RZV_GPIO_BASE + RZV_GPIO_PUPD5_L_OFFSET)
#define RZV_GPIO_PUPD5_H                             (RZV_GPIO_BASE + RZV_GPIO_PUPD5_H_OFFSET)
#define RZV_GPIO_PUPD6_L                             (RZV_GPIO_BASE + RZV_GPIO_PUPD6_L_OFFSET)
#define RZV_GPIO_PUPD6_H                             (RZV_GPIO_BASE + RZV_GPIO_PUPD6_H_OFFSET)
#define RZV_GPIO_PUPD7_L                             (RZV_GPIO_BASE + RZV_GPIO_PUPD7_L_OFFSET)
#define RZV_GPIO_PUPD7_H                             (RZV_GPIO_BASE + RZV_GPIO_PUPD7_H_OFFSET)
#define RZV_GPIO_PUPD8_L                             (RZV_GPIO_BASE + RZV_GPIO_PUPD8_L_OFFSET)
#define RZV_GPIO_PUPD8_H                             (RZV_GPIO_BASE + RZV_GPIO_PUPD8_H_OFFSET)
#define RZV_GPIO_PUPD9_L                             (RZV_GPIO_BASE + RZV_GPIO_PUPD9_L_OFFSET)
#define RZV_GPIO_PUPD9_H                             (RZV_GPIO_BASE + RZV_GPIO_PUPD9_H_OFFSET)
#define RZV_GPIO_PUPDA_L                             (RZV_GPIO_BASE + RZV_GPIO_PUPDA_L_OFFSET)
#define RZV_GPIO_PUPDA_H                             (RZV_GPIO_BASE + RZV_GPIO_PUPDA_H_OFFSET)
#define RZV_GPIO_PUPDB_L                             (RZV_GPIO_BASE + RZV_GPIO_PUPDB_L_OFFSET)
#define RZV_GPIO_PUPDB_H                             (RZV_GPIO_BASE + RZV_GPIO_PUPDB_H_OFFSET)
#define RZV_GPIO_PUPDC_L                             (RZV_GPIO_BASE + RZV_GPIO_PUPDC_L_OFFSET)
#define RZV_GPIO_PUPDC_H                             (RZV_GPIO_BASE + RZV_GPIO_PUPDC_H_OFFSET)
#define RZV_GPIO_PUPDF_L                             (RZV_GPIO_BASE + RZV_GPIO_PUPDF_L_OFFSET)
#define RZV_GPIO_PUPDF_H                             (RZV_GPIO_BASE + RZV_GPIO_PUPDF_H_OFFSET)
#define RZV_GPIO_PUPD10_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD10_L_OFFSET)
#define RZV_GPIO_PUPD10_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD10_H_OFFSET)
#define RZV_GPIO_PUPD11_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD11_L_OFFSET)
#define RZV_GPIO_PUPD11_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD11_H_OFFSET)
#define RZV_GPIO_PUPD12_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD12_L_OFFSET)
#define RZV_GPIO_PUPD12_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD12_H_OFFSET)
#define RZV_GPIO_PUPD13_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD13_L_OFFSET)
#define RZV_GPIO_PUPD13_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD13_H_OFFSET)
#define RZV_GPIO_PUPD14_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD14_L_OFFSET)
#define RZV_GPIO_PUPD14_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD14_H_OFFSET)
#define RZV_GPIO_PUPD20_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD20_L_OFFSET)
#define RZV_GPIO_PUPD20_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD20_H_OFFSET)
#define RZV_GPIO_PUPD21_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD21_L_OFFSET)
#define RZV_GPIO_PUPD21_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD21_H_OFFSET)
#define RZV_GPIO_PUPD22_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD22_L_OFFSET)
#define RZV_GPIO_PUPD22_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD22_H_OFFSET)
#define RZV_GPIO_PUPD23_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD23_L_OFFSET)
#define RZV_GPIO_PUPD23_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD23_H_OFFSET)
#define RZV_GPIO_PUPD24_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD24_L_OFFSET)
#define RZV_GPIO_PUPD24_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD24_H_OFFSET)
#define RZV_GPIO_PUPD25_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD25_L_OFFSET)
#define RZV_GPIO_PUPD25_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD25_H_OFFSET)
#define RZV_GPIO_PUPD26_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD26_L_OFFSET)
#define RZV_GPIO_PUPD26_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD26_H_OFFSET)
#define RZV_GPIO_PUPD27_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD27_L_OFFSET)
#define RZV_GPIO_PUPD27_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD27_H_OFFSET)
#define RZV_GPIO_PUPD28_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD28_L_OFFSET)
#define RZV_GPIO_PUPD28_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD28_H_OFFSET)
#define RZV_GPIO_PUPD29_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD29_L_OFFSET)
#define RZV_GPIO_PUPD29_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD29_H_OFFSET)
#define RZV_GPIO_PUPD2A_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD2A_L_OFFSET)
#define RZV_GPIO_PUPD2A_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD2A_H_OFFSET)
#define RZV_GPIO_PUPD2B_L                            (RZV_GPIO_BASE + RZV_GPIO_PUPD2B_L_OFFSET)
#define RZV_GPIO_PUPD2B_H                            (RZV_GPIO_BASE + RZV_GPIO_PUPD2B_H_OFFSET)
#define RZV_GPIO_FILONOFF1_L                         (RZV_GPIO_BASE + RZV_GPIO_FILONOFF1_L_OFFSET)
#define RZV_GPIO_FILONOFF1_H                         (RZV_GPIO_BASE + RZV_GPIO_FILONOFF1_H_OFFSET)
#define RZV_GPIO_FILONOFF20_L                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF20_L_OFFSET)
#define RZV_GPIO_FILONOFF20_H                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF20_H_OFFSET)
#define RZV_GPIO_FILONOFF21_L                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF21_L_OFFSET)
#define RZV_GPIO_FILONOFF21_H                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF21_H_OFFSET)
#define RZV_GPIO_FILONOFF22_L                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF22_L_OFFSET)
#define RZV_GPIO_FILONOFF22_H                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF22_H_OFFSET)
#define RZV_GPIO_FILONOFF23_L                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF23_L_OFFSET)
#define RZV_GPIO_FILONOFF23_H                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF23_H_OFFSET)
#define RZV_GPIO_FILONOFF24_L                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF24_L_OFFSET)
#define RZV_GPIO_FILONOFF24_H                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF24_H_OFFSET)
#define RZV_GPIO_FILONOFF25_L                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF25_L_OFFSET)
#define RZV_GPIO_FILONOFF25_H                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF25_H_OFFSET)
#define RZV_GPIO_FILONOFF26_L                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF26_L_OFFSET)
#define RZV_GPIO_FILONOFF26_H                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF26_H_OFFSET)
#define RZV_GPIO_FILONOFF27_L                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF27_L_OFFSET)
#define RZV_GPIO_FILONOFF27_H                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF27_H_OFFSET)
#define RZV_GPIO_FILONOFF28_L                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF28_L_OFFSET)
#define RZV_GPIO_FILONOFF28_H                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF28_H_OFFSET)
#define RZV_GPIO_FILONOFF29_L                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF29_L_OFFSET)
#define RZV_GPIO_FILONOFF29_H                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF29_H_OFFSET)
#define RZV_GPIO_FILONOFF2A_L                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF2A_L_OFFSET)
#define RZV_GPIO_FILONOFF2A_H                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF2A_H_OFFSET)
#define RZV_GPIO_FILONOFF2B_L                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF2B_L_OFFSET)
#define RZV_GPIO_FILONOFF2B_H                        (RZV_GPIO_BASE + RZV_GPIO_FILONOFF2B_H_OFFSET)
#define RZV_GPIO_FILNUM1_L                           (RZV_GPIO_BASE + RZV_GPIO_FILNUM1_L_OFFSET)
#define RZV_GPIO_FILNUM1_H                           (RZV_GPIO_BASE + RZV_GPIO_FILNUM1_H_OFFSET)
#define RZV_GPIO_FILNUM20_L                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM20_L_OFFSET)
#define RZV_GPIO_FILNUM20_H                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM20_H_OFFSET)
#define RZV_GPIO_FILNUM21_L                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM21_L_OFFSET)
#define RZV_GPIO_FILNUM21_H                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM21_H_OFFSET)
#define RZV_GPIO_FILNUM22_L                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM22_L_OFFSET)
#define RZV_GPIO_FILNUM22_H                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM22_H_OFFSET)
#define RZV_GPIO_FILNUM23_L                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM23_L_OFFSET)
#define RZV_GPIO_FILNUM23_H                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM23_H_OFFSET)
#define RZV_GPIO_FILNUM24_L                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM24_L_OFFSET)
#define RZV_GPIO_FILNUM24_H                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM24_H_OFFSET)
#define RZV_GPIO_FILNUM25_L                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM25_L_OFFSET)
#define RZV_GPIO_FILNUM25_H                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM25_H_OFFSET)
#define RZV_GPIO_FILNUM26_L                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM26_L_OFFSET)
#define RZV_GPIO_FILNUM26_H                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM26_H_OFFSET)
#define RZV_GPIO_FILNUM27_L                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM27_L_OFFSET)
#define RZV_GPIO_FILNUM27_H                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM27_H_OFFSET)
#define RZV_GPIO_FILNUM28_L                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM28_L_OFFSET)
#define RZV_GPIO_FILNUM28_H                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM28_H_OFFSET)
#define RZV_GPIO_FILNUM29_L                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM29_L_OFFSET)
#define RZV_GPIO_FILNUM29_H                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM29_H_OFFSET)
#define RZV_GPIO_FILNUM2A_L                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM2A_L_OFFSET)
#define RZV_GPIO_FILNUM2A_H                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM2A_H_OFFSET)
#define RZV_GPIO_FILNUM2B_L                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM2B_L_OFFSET)
#define RZV_GPIO_FILNUM2B_H                          (RZV_GPIO_BASE + RZV_GPIO_FILNUM2B_H_OFFSET)
#define RZV_GPIO_FILCLKSEL1_L                        (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL1_L_OFFSET)
#define RZV_GPIO_FILCLKSEL1_H                        (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL1_H_OFFSET)
#define RZV_GPIO_FILCLKSEL20_L                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL20_L_OFFSET)
#define RZV_GPIO_FILCLKSEL20_H                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL20_H_OFFSET)
#define RZV_GPIO_FILCLKSEL21_L                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL21_L_OFFSET)
#define RZV_GPIO_FILCLKSEL21_H                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL21_H_OFFSET)
#define RZV_GPIO_FILCLKSEL22_L                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL22_L_OFFSET)
#define RZV_GPIO_FILCLKSEL22_H                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL22_H_OFFSET)
#define RZV_GPIO_FILCLKSEL23_L                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL23_L_OFFSET)
#define RZV_GPIO_FILCLKSEL23_H                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL23_H_OFFSET)
#define RZV_GPIO_FILCLKSEL24_L                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL24_L_OFFSET)
#define RZV_GPIO_FILCLKSEL24_H                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL24_H_OFFSET)
#define RZV_GPIO_FILCLKSEL25_L                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL25_L_OFFSET)
#define RZV_GPIO_FILCLKSEL25_H                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL25_H_OFFSET)
#define RZV_GPIO_FILCLKSEL26_L                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL26_L_OFFSET)
#define RZV_GPIO_FILCLKSEL26_H                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL26_H_OFFSET)
#define RZV_GPIO_FILCLKSEL27_L                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL27_L_OFFSET)
#define RZV_GPIO_FILCLKSEL27_H                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL27_H_OFFSET)
#define RZV_GPIO_FILCLKSEL28_L                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL28_L_OFFSET)
#define RZV_GPIO_FILCLKSEL28_H                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL28_H_OFFSET)
#define RZV_GPIO_FILCLKSEL29_L                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL29_L_OFFSET)
#define RZV_GPIO_FILCLKSEL29_H                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL29_H_OFFSET)
#define RZV_GPIO_FILCLKSEL2A_L                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL2A_L_OFFSET)
#define RZV_GPIO_FILCLKSEL2A_H                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL2A_H_OFFSET)
#define RZV_GPIO_FILCLKSEL2B_L                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL2B_L_OFFSET)
#define RZV_GPIO_FILCLKSEL2B_H                       (RZV_GPIO_BASE + RZV_GPIO_FILCLKSEL2B_H_OFFSET)
#define RZV_GPIO_ISEL20_L                            (RZV_GPIO_BASE + RZV_GPIO_ISEL20_L_OFFSET)
#define RZV_GPIO_ISEL20_H                            (RZV_GPIO_BASE + RZV_GPIO_ISEL20_H_OFFSET)
#define RZV_GPIO_ISEL21_L                            (RZV_GPIO_BASE + RZV_GPIO_ISEL21_L_OFFSET)
#define RZV_GPIO_ISEL21_H                            (RZV_GPIO_BASE + RZV_GPIO_ISEL21_H_OFFSET)
#define RZV_GPIO_ISEL22_L                            (RZV_GPIO_BASE + RZV_GPIO_ISEL22_L_OFFSET)
#define RZV_GPIO_ISEL22_H                            (RZV_GPIO_BASE + RZV_GPIO_ISEL22_H_OFFSET)
#define RZV_GPIO_ISEL23_L                            (RZV_GPIO_BASE + RZV_GPIO_ISEL23_L_OFFSET)
#define RZV_GPIO_ISEL23_H                            (RZV_GPIO_BASE + RZV_GPIO_ISEL23_H_OFFSET)
#define RZV_GPIO_ISEL24_L                            (RZV_GPIO_BASE + RZV_GPIO_ISEL24_L_OFFSET)
#define RZV_GPIO_ISEL24_H                            (RZV_GPIO_BASE + RZV_GPIO_ISEL24_H_OFFSET)
#define RZV_GPIO_ISEL25_L                            (RZV_GPIO_BASE + RZV_GPIO_ISEL25_L_OFFSET)
#define RZV_GPIO_ISEL25_H                            (RZV_GPIO_BASE + RZV_GPIO_ISEL25_H_OFFSET)
#define RZV_GPIO_ISEL26_L                            (RZV_GPIO_BASE + RZV_GPIO_ISEL26_L_OFFSET)
#define RZV_GPIO_ISEL26_H                            (RZV_GPIO_BASE + RZV_GPIO_ISEL26_H_OFFSET)
#define RZV_GPIO_ISEL27_L                            (RZV_GPIO_BASE + RZV_GPIO_ISEL27_L_OFFSET)
#define RZV_GPIO_ISEL27_H                            (RZV_GPIO_BASE + RZV_GPIO_ISEL27_H_OFFSET)
#define RZV_GPIO_ISEL28_L                            (RZV_GPIO_BASE + RZV_GPIO_ISEL28_L_OFFSET)
#define RZV_GPIO_ISEL28_H                            (RZV_GPIO_BASE + RZV_GPIO_ISEL28_H_OFFSET)
#define RZV_GPIO_ISEL29_L                            (RZV_GPIO_BASE + RZV_GPIO_ISEL29_L_OFFSET)
#define RZV_GPIO_ISEL29_H                            (RZV_GPIO_BASE + RZV_GPIO_ISEL29_H_OFFSET)
#define RZV_GPIO_ISEL2A_L                            (RZV_GPIO_BASE + RZV_GPIO_ISEL2A_L_OFFSET)
#define RZV_GPIO_ISEL2A_H                            (RZV_GPIO_BASE + RZV_GPIO_ISEL2A_H_OFFSET)
#define RZV_GPIO_ISEL2B_L                            (RZV_GPIO_BASE + RZV_GPIO_ISEL2B_L_OFFSET)
#define RZV_GPIO_ISEL2B_H                            (RZV_GPIO_BASE + RZV_GPIO_ISEL2B_H_OFFSET)
#define RZV_GPIO_NOD5_L                              (RZV_GPIO_BASE + RZV_GPIO_NOD5_L_OFFSET)
#define RZV_GPIO_NOD5_H                              (RZV_GPIO_BASE + RZV_GPIO_NOD5_H_OFFSET)
#define RZV_GPIO_NOD20_L                             (RZV_GPIO_BASE + RZV_GPIO_NOD20_L_OFFSET)
#define RZV_GPIO_NOD20_H                             (RZV_GPIO_BASE + RZV_GPIO_NOD20_H_OFFSET)
#define RZV_GPIO_NOD21_L                             (RZV_GPIO_BASE + RZV_GPIO_NOD21_L_OFFSET)
#define RZV_GPIO_NOD21_H                             (RZV_GPIO_BASE + RZV_GPIO_NOD21_H_OFFSET)
#define RZV_GPIO_NOD22_L                             (RZV_GPIO_BASE + RZV_GPIO_NOD22_L_OFFSET)
#define RZV_GPIO_NOD22_H                             (RZV_GPIO_BASE + RZV_GPIO_NOD22_H_OFFSET)
#define RZV_GPIO_NOD23_L                             (RZV_GPIO_BASE + RZV_GPIO_NOD23_L_OFFSET)
#define RZV_GPIO_NOD23_H                             (RZV_GPIO_BASE + RZV_GPIO_NOD23_H_OFFSET)
#define RZV_GPIO_NOD24_L                             (RZV_GPIO_BASE + RZV_GPIO_NOD24_L_OFFSET)
#define RZV_GPIO_NOD24_H                             (RZV_GPIO_BASE + RZV_GPIO_NOD24_H_OFFSET)
#define RZV_GPIO_NOD25_L                             (RZV_GPIO_BASE + RZV_GPIO_NOD25_L_OFFSET)
#define RZV_GPIO_NOD25_H                             (RZV_GPIO_BASE + RZV_GPIO_NOD25_H_OFFSET)
#define RZV_GPIO_NOD26_L                             (RZV_GPIO_BASE + RZV_GPIO_NOD26_L_OFFSET)
#define RZV_GPIO_NOD26_H                             (RZV_GPIO_BASE + RZV_GPIO_NOD26_H_OFFSET)
#define RZV_GPIO_NOD27_L                             (RZV_GPIO_BASE + RZV_GPIO_NOD27_L_OFFSET)
#define RZV_GPIO_NOD27_H                             (RZV_GPIO_BASE + RZV_GPIO_NOD27_H_OFFSET)
#define RZV_GPIO_NOD28_L                             (RZV_GPIO_BASE + RZV_GPIO_NOD28_L_OFFSET)
#define RZV_GPIO_NOD28_H                             (RZV_GPIO_BASE + RZV_GPIO_NOD28_H_OFFSET)
#define RZV_GPIO_NOD29_L                             (RZV_GPIO_BASE + RZV_GPIO_NOD29_L_OFFSET)
#define RZV_GPIO_NOD29_H                             (RZV_GPIO_BASE + RZV_GPIO_NOD29_H_OFFSET)
#define RZV_GPIO_NOD2A_L                             (RZV_GPIO_BASE + RZV_GPIO_NOD2A_L_OFFSET)
#define RZV_GPIO_NOD2A_H                             (RZV_GPIO_BASE + RZV_GPIO_NOD2A_H_OFFSET)
#define RZV_GPIO_NOD2B_L                             (RZV_GPIO_BASE + RZV_GPIO_NOD2B_L_OFFSET)
#define RZV_GPIO_NOD2B_H                             (RZV_GPIO_BASE + RZV_GPIO_NOD2B_H_OFFSET)
#define RZV_GPIO_SMT20_L                             (RZV_GPIO_BASE + RZV_GPIO_SMT20_L_OFFSET)
#define RZV_GPIO_SMT20_H                             (RZV_GPIO_BASE + RZV_GPIO_SMT20_H_OFFSET)
#define RZV_GPIO_SMT21_L                             (RZV_GPIO_BASE + RZV_GPIO_SMT21_L_OFFSET)
#define RZV_GPIO_SMT21_H                             (RZV_GPIO_BASE + RZV_GPIO_SMT21_H_OFFSET)
#define RZV_GPIO_SMT23_L                             (RZV_GPIO_BASE + RZV_GPIO_SMT23_L_OFFSET)
#define RZV_GPIO_SMT23_H                             (RZV_GPIO_BASE + RZV_GPIO_SMT23_H_OFFSET)
#define RZV_GPIO_SMT24_L                             (RZV_GPIO_BASE + RZV_GPIO_SMT24_L_OFFSET)
#define RZV_GPIO_SMT24_H                             (RZV_GPIO_BASE + RZV_GPIO_SMT24_H_OFFSET)
#define RZV_GPIO_SMT25_L                             (RZV_GPIO_BASE + RZV_GPIO_SMT25_L_OFFSET)
#define RZV_GPIO_SMT25_H                             (RZV_GPIO_BASE + RZV_GPIO_SMT25_H_OFFSET)
#define RZV_GPIO_SMT26_L                             (RZV_GPIO_BASE + RZV_GPIO_SMT26_L_OFFSET)
#define RZV_GPIO_SMT26_H                             (RZV_GPIO_BASE + RZV_GPIO_SMT26_H_OFFSET)
#define RZV_GPIO_SMT27_L                             (RZV_GPIO_BASE + RZV_GPIO_SMT27_L_OFFSET)
#define RZV_GPIO_SMT27_H                             (RZV_GPIO_BASE + RZV_GPIO_SMT27_H_OFFSET)
#define RZV_GPIO_SMT28_L                             (RZV_GPIO_BASE + RZV_GPIO_SMT28_L_OFFSET)
#define RZV_GPIO_SMT28_H                             (RZV_GPIO_BASE + RZV_GPIO_SMT28_H_OFFSET)
#define RZV_GPIO_SMT29_L                             (RZV_GPIO_BASE + RZV_GPIO_SMT29_L_OFFSET)
#define RZV_GPIO_SMT29_H                             (RZV_GPIO_BASE + RZV_GPIO_SMT29_H_OFFSET)
#define RZV_GPIO_SMT2A_L                             (RZV_GPIO_BASE + RZV_GPIO_SMT2A_L_OFFSET)
#define RZV_GPIO_SMT2A_H                             (RZV_GPIO_BASE + RZV_GPIO_SMT2A_H_OFFSET)
#define RZV_GPIO_SMT2B_L                             (RZV_GPIO_BASE + RZV_GPIO_SMT2B_L_OFFSET)
#define RZV_GPIO_SMT2B_H                             (RZV_GPIO_BASE + RZV_GPIO_SMT2B_H_OFFSET)
#define RZV_GPIO_ELC_DPTC                            (RZV_GPIO_BASE + RZV_GPIO_ELC_DPTC_OFFSET)
#define RZV_GPIO_PFC_ELC_ELSR2                       (RZV_GPIO_BASE + RZV_GPIO_PFC_ELC_ELSR2_OFFSET)
#define RZV_GPIO_PFC_OSCBYPS                         (RZV_GPIO_BASE + RZV_GPIO_PFC_OSCBYPS_OFFSET)
#define RZV_GPIO_PWPR                                (RZV_GPIO_BASE + RZV_GPIO_PWPR_OFFSET)
#define RZV_GPIO_PFC_FILONOFF_IRQ                    (RZV_GPIO_BASE + RZV_GPIO_PFC_FILONOFF_IRQ_OFFSET)
#define RZV_GPIO_PFC_FILNUM_IRQ                      (RZV_GPIO_BASE + RZV_GPIO_PFC_FILNUM_IRQ_OFFSET)
#define RZV_GPIO_PFC_FILCLKSEL_IRQ                   (RZV_GPIO_BASE + RZV_GPIO_PFC_FILCLKSEL_IRQ_OFFSET)
#define RZV_GPIO_PFC_FILONOFF_DMAC_REQ               (RZV_GPIO_BASE + RZV_GPIO_PFC_FILONOFF_DMAC_REQ_OFFSET)
#define RZV_GPIO_PFC_FILNUM_DMAC_REQ                 (RZV_GPIO_BASE + RZV_GPIO_PFC_FILNUM_DMAC_REQ_OFFSET)
#define RZV_GPIO_PFC_FILCLKSEL_DMAC_REQ              (RZV_GPIO_BASE + RZV_GPIO_PFC_FILCLKSEL_DMAC_REQ_OFFSET)
#define RZV_GPIO_PFC_OEN                             (RZV_GPIO_BASE + RZV_GPIO_PFC_OEN_OFFSET)

/* GPIO P Register Bit Definitions (Parameterized) *************************/

#define GPIO_P_P(m,n)                                     (1u << (0 + ((unsigned)(n) * 1)))  /* P0 */


/* GPIO PFC Register Bit Definitions (Parameterized) ***********************/

#define GPIO_PFC_PFC_SHIFT(n)                             ((unsigned)(0 + ((n) * 4)))  /* Bits for PFCn */
#define GPIO_PFC_PFC_MASK(m,n)                            (0xfu << GPIO_PFC_PFC_SHIFT(n))
#define GPIO_PFC_PFC(m,n,v)                               (((unsigned)(v) & 0xfu) << GPIO_PFC_PFC_SHIFT(n))


/* GPIO PIN Register Bit Definitions (Parameterized) ***********************/

#define GPIO_PIN_PIN(m,n)                                 (1u << (0 + ((unsigned)(n) * 1)))  /* Pin0 */


/* GPIO PM Register Bit Definitions (Parameterized) ************************/

#define GPIO_PM_PM_SHIFT(n)                               ((unsigned)(0 + ((n) * 2)))  /* Bits for PMn */
#define GPIO_PM_PM_MASK(m,n)                              (0x3u << GPIO_PM_PM_SHIFT(n))
#define GPIO_PM_PM(m,n,v)                                 (((unsigned)(v) & 0x3u) << GPIO_PM_PM_SHIFT(n))


/* GPIO PMC Register Bit Definitions (Parameterized) ***********************/

#define GPIO_PMC_P(m,n)                                   (1u << (0 + ((unsigned)(n) * 1)))  /* P0 */


/* GPIO ELC_DPTC0 Register Bit Definitions ***************************/

#define GPIO_ELC_DPTC0_PTC                      (1 << 0)  /* Ptc */

/* GPIO ELC_DPTC1 Register Bit Definitions ***************************/

#define GPIO_ELC_DPTC1_PTC                      (1 << 1)  /* Ptc */

/* GPIO ELC_DPTC2 Register Bit Definitions ***************************/

#define GPIO_ELC_DPTC2_PTC                      (1 << 2)  /* Ptc */

/* GPIO ELC_DPTC3 Register Bit Definitions ***************************/

#define GPIO_ELC_DPTC3_PTC                      (1 << 3)  /* Ptc */

/* GPIO ELC_PDBF Register Bit Definitions ****************************/

#define GPIO_ELC_PDBF_PDBF_SHIFT                (0)      /* Bits 0-7: Pdbf */
#define GPIO_ELC_PDBF_PDBF_MASK                 (0xff << GPIO_ELC_PDBF_PDBF_SHIFT)

/* GPIO ELC_PEL Register Bit Definitions *****************************/

#define GPIO_ELC_PEL_PSB_SHIFT                  (0)      /* Bits 0-2: Psb */
#define GPIO_ELC_PEL_PSB_MASK                   (0x7 << GPIO_ELC_PEL_PSB_SHIFT)

#define GPIO_ELC_PEL_PSP_SHIFT                  (3)      /* Bits 3-4: Psp */
#define GPIO_ELC_PEL_PSP_MASK                   (0x3 << GPIO_ELC_PEL_PSP_SHIFT)

#define GPIO_ELC_PEL_PSM_SHIFT                  (5)      /* Bits 5-6: Psm */
#define GPIO_ELC_PEL_PSM_MASK                   (0x3 << GPIO_ELC_PEL_PSM_SHIFT)

/* GPIO ELC_PGC Register Bit Definitions *****************************/

#define GPIO_ELC_PGC_PGCI_SHIFT                 (0)      /* Bits 0-1: Pgci */
#define GPIO_ELC_PGC_PGCI_MASK                  (0x3 << GPIO_ELC_PGC_PGCI_SHIFT)

#define GPIO_ELC_PGC_PGCOVE                     (1 << 2)  /* Pgcove */

#define GPIO_ELC_PGC_PGCO_SHIFT                 (4)      /* Bits 4-6: Pgco */
#define GPIO_ELC_PGC_PGCO_MASK                  (0x7 << GPIO_ELC_PGC_PGCO_SHIFT)

/* GPIO ELC_PGR Register Bit Definitions *****************************/

#define GPIO_ELC_PGR_PGR_SHIFT                  (0)      /* Bits 0-7: Pgr */
#define GPIO_ELC_PGR_PGR_MASK                   (0xff << GPIO_ELC_PGR_PGR_SHIFT)

/* GPIO FILCLKSEL1_H Register Bit Definitions ************************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL1_H_FILCLKSEL_SHIFT(n)              ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL1_H_FILCLKSEL_MASK(n)               (0x3u << GPIO_FILCLKSEL1_H_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL1_H_FILCLKSEL_VAL(n,v)              (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL1_H_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL1_L Register Bit Definitions ************************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL1_L_FILCLKSEL_SHIFT(n)              ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL1_L_FILCLKSEL_MASK(n)               (0x3u << GPIO_FILCLKSEL1_L_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL1_L_FILCLKSEL_VAL(n,v)              (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL1_L_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL20_H Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL20_H_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL20_H_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL20_H_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL20_H_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL20_H_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL20_L Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL20_L_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL20_L_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL20_L_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL20_L_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL20_L_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL21_H Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL21_H_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL21_H_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL21_H_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL21_H_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL21_H_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL21_L Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL21_L_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL21_L_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL21_L_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL21_L_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL21_L_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL22_H Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL22_H_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL22_H_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL22_H_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL22_H_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL22_H_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL22_L Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL22_L_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL22_L_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL22_L_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL22_L_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL22_L_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL23_H Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL23_H_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL23_H_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL23_H_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL23_H_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL23_H_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL23_L Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL23_L_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL23_L_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL23_L_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL23_L_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL23_L_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL24_H Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL24_H_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL24_H_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL24_H_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL24_H_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL24_H_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL24_L Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL24_L_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL24_L_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL24_L_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL24_L_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL24_L_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL25_H Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL25_H_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL25_H_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL25_H_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL25_H_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL25_H_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL25_L Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL25_L_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL25_L_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL25_L_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL25_L_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL25_L_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL26_H Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL26_H_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL26_H_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL26_H_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL26_H_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL26_H_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL26_L Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL26_L_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL26_L_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL26_L_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL26_L_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL26_L_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL27_H Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL27_H_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL27_H_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL27_H_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL27_H_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL27_H_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL27_L Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL27_L_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL27_L_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL27_L_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL27_L_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL27_L_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL28_H Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL28_H_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL28_H_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL28_H_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL28_H_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL28_H_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL28_L Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL28_L_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL28_L_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL28_L_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL28_L_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL28_L_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL29_H Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL29_H_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL29_H_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL29_H_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL29_H_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL29_H_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL29_L Register Bit Definitions ***********************/

/* FILCLKSEL_ fields (parameterized for indices 0-3) */
#define GPIO_FILCLKSEL29_L_FILCLKSEL_SHIFT(n)             ((unsigned)(0 + ((n) * 8)))  /* Bits for FILCLKSELn */
#define GPIO_FILCLKSEL29_L_FILCLKSEL_MASK(n)              (0x3u << GPIO_FILCLKSEL29_L_FILCLKSEL_SHIFT(n))
#define GPIO_FILCLKSEL29_L_FILCLKSEL_VAL(n,v)             (((unsigned)(v) & 0x3u) << GPIO_FILCLKSEL29_L_FILCLKSEL_SHIFT(n))

/* GPIO FILCLKSEL2A_H Register Bit Definitions ***********************/

#define GPIO_FILCLKSEL2A_H_FILCLKSEL_2A0_SHIFT  (0)      /* Bits 0-1: Filclksel 2A0 */
#define GPIO_FILCLKSEL2A_H_FILCLKSEL_2A0_MASK   (0x3 << GPIO_FILCLKSEL2A_H_FILCLKSEL_2A0_SHIFT)

#define GPIO_FILCLKSEL2A_H_FILCLKSEL_2A1_SHIFT  (8)      /* Bits 8-9: Filclksel 2A1 */
#define GPIO_FILCLKSEL2A_H_FILCLKSEL_2A1_MASK   (0x3 << GPIO_FILCLKSEL2A_H_FILCLKSEL_2A1_SHIFT)

#define GPIO_FILCLKSEL2A_H_FILCLKSEL_2A2_SHIFT  (16)      /* Bits 16-17: Filclksel 2A2 */
#define GPIO_FILCLKSEL2A_H_FILCLKSEL_2A2_MASK   (0x3 << GPIO_FILCLKSEL2A_H_FILCLKSEL_2A2_SHIFT)

#define GPIO_FILCLKSEL2A_H_FILCLKSEL_2A3_SHIFT  (24)      /* Bits 24-25: Filclksel 2A3 */
#define GPIO_FILCLKSEL2A_H_FILCLKSEL_2A3_MASK   (0x3 << GPIO_FILCLKSEL2A_H_FILCLKSEL_2A3_SHIFT)

/* GPIO FILCLKSEL2A_L Register Bit Definitions ***********************/

#define GPIO_FILCLKSEL2A_L_FILCLKSEL_2A0_SHIFT  (0)      /* Bits 0-1: Filclksel 2A0 */
#define GPIO_FILCLKSEL2A_L_FILCLKSEL_2A0_MASK   (0x3 << GPIO_FILCLKSEL2A_L_FILCLKSEL_2A0_SHIFT)

#define GPIO_FILCLKSEL2A_L_FILCLKSEL_2A1_SHIFT  (8)      /* Bits 8-9: Filclksel 2A1 */
#define GPIO_FILCLKSEL2A_L_FILCLKSEL_2A1_MASK   (0x3 << GPIO_FILCLKSEL2A_L_FILCLKSEL_2A1_SHIFT)

#define GPIO_FILCLKSEL2A_L_FILCLKSEL_2A2_SHIFT  (16)      /* Bits 16-17: Filclksel 2A2 */
#define GPIO_FILCLKSEL2A_L_FILCLKSEL_2A2_MASK   (0x3 << GPIO_FILCLKSEL2A_L_FILCLKSEL_2A2_SHIFT)

#define GPIO_FILCLKSEL2A_L_FILCLKSEL_2A3_SHIFT  (24)      /* Bits 24-25: Filclksel 2A3 */
#define GPIO_FILCLKSEL2A_L_FILCLKSEL_2A3_MASK   (0x3 << GPIO_FILCLKSEL2A_L_FILCLKSEL_2A3_SHIFT)

/* GPIO FILCLKSEL2B_H Register Bit Definitions ***********************/

#define GPIO_FILCLKSEL2B_H_FILCLKSEL_2B0_SHIFT  (0)      /* Bits 0-1: Filclksel 2B0 */
#define GPIO_FILCLKSEL2B_H_FILCLKSEL_2B0_MASK   (0x3 << GPIO_FILCLKSEL2B_H_FILCLKSEL_2B0_SHIFT)

#define GPIO_FILCLKSEL2B_H_FILCLKSEL_2B1_SHIFT  (8)      /* Bits 8-9: Filclksel 2B1 */
#define GPIO_FILCLKSEL2B_H_FILCLKSEL_2B1_MASK   (0x3 << GPIO_FILCLKSEL2B_H_FILCLKSEL_2B1_SHIFT)

#define GPIO_FILCLKSEL2B_H_FILCLKSEL_2B2_SHIFT  (16)      /* Bits 16-17: Filclksel 2B2 */
#define GPIO_FILCLKSEL2B_H_FILCLKSEL_2B2_MASK   (0x3 << GPIO_FILCLKSEL2B_H_FILCLKSEL_2B2_SHIFT)

#define GPIO_FILCLKSEL2B_H_FILCLKSEL_2B3_SHIFT  (24)      /* Bits 24-25: Filclksel 2B3 */
#define GPIO_FILCLKSEL2B_H_FILCLKSEL_2B3_MASK   (0x3 << GPIO_FILCLKSEL2B_H_FILCLKSEL_2B3_SHIFT)

/* GPIO FILCLKSEL2B_L Register Bit Definitions ***********************/

#define GPIO_FILCLKSEL2B_L_FILCLKSEL_2B0_SHIFT  (0)      /* Bits 0-1: Filclksel 2B0 */
#define GPIO_FILCLKSEL2B_L_FILCLKSEL_2B0_MASK   (0x3 << GPIO_FILCLKSEL2B_L_FILCLKSEL_2B0_SHIFT)

#define GPIO_FILCLKSEL2B_L_FILCLKSEL_2B1_SHIFT  (8)      /* Bits 8-9: Filclksel 2B1 */
#define GPIO_FILCLKSEL2B_L_FILCLKSEL_2B1_MASK   (0x3 << GPIO_FILCLKSEL2B_L_FILCLKSEL_2B1_SHIFT)

#define GPIO_FILCLKSEL2B_L_FILCLKSEL_2B2_SHIFT  (16)      /* Bits 16-17: Filclksel 2B2 */
#define GPIO_FILCLKSEL2B_L_FILCLKSEL_2B2_MASK   (0x3 << GPIO_FILCLKSEL2B_L_FILCLKSEL_2B2_SHIFT)

#define GPIO_FILCLKSEL2B_L_FILCLKSEL_2B3_SHIFT  (24)      /* Bits 24-25: Filclksel 2B3 */
#define GPIO_FILCLKSEL2B_L_FILCLKSEL_2B3_MASK   (0x3 << GPIO_FILCLKSEL2B_L_FILCLKSEL_2B3_SHIFT)

/* GPIO FILNUM1_H Register Bit Definitions ***************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM1_H_FILNUM_SHIFT(n)                    ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM1_H_FILNUM_MASK(n)                     (0x3u << GPIO_FILNUM1_H_FILNUM_SHIFT(n))
#define GPIO_FILNUM1_H_FILNUM_VAL(n,v)                    (((unsigned)(v) & 0x3u) << GPIO_FILNUM1_H_FILNUM_SHIFT(n))

/* GPIO FILNUM1_L Register Bit Definitions ***************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM1_L_FILNUM_SHIFT(n)                    ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM1_L_FILNUM_MASK(n)                     (0x3u << GPIO_FILNUM1_L_FILNUM_SHIFT(n))
#define GPIO_FILNUM1_L_FILNUM_VAL(n,v)                    (((unsigned)(v) & 0x3u) << GPIO_FILNUM1_L_FILNUM_SHIFT(n))

/* GPIO FILNUM20_H Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM20_H_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM20_H_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM20_H_FILNUM_SHIFT(n))
#define GPIO_FILNUM20_H_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM20_H_FILNUM_SHIFT(n))

/* GPIO FILNUM20_L Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM20_L_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM20_L_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM20_L_FILNUM_SHIFT(n))
#define GPIO_FILNUM20_L_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM20_L_FILNUM_SHIFT(n))

/* GPIO FILNUM21_H Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM21_H_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM21_H_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM21_H_FILNUM_SHIFT(n))
#define GPIO_FILNUM21_H_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM21_H_FILNUM_SHIFT(n))

/* GPIO FILNUM21_L Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM21_L_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM21_L_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM21_L_FILNUM_SHIFT(n))
#define GPIO_FILNUM21_L_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM21_L_FILNUM_SHIFT(n))

/* GPIO FILNUM22_H Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM22_H_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM22_H_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM22_H_FILNUM_SHIFT(n))
#define GPIO_FILNUM22_H_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM22_H_FILNUM_SHIFT(n))

/* GPIO FILNUM22_L Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM22_L_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM22_L_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM22_L_FILNUM_SHIFT(n))
#define GPIO_FILNUM22_L_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM22_L_FILNUM_SHIFT(n))

/* GPIO FILNUM23_H Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM23_H_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM23_H_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM23_H_FILNUM_SHIFT(n))
#define GPIO_FILNUM23_H_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM23_H_FILNUM_SHIFT(n))

/* GPIO FILNUM23_L Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM23_L_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM23_L_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM23_L_FILNUM_SHIFT(n))
#define GPIO_FILNUM23_L_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM23_L_FILNUM_SHIFT(n))

/* GPIO FILNUM24_H Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM24_H_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM24_H_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM24_H_FILNUM_SHIFT(n))
#define GPIO_FILNUM24_H_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM24_H_FILNUM_SHIFT(n))

/* GPIO FILNUM24_L Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM24_L_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM24_L_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM24_L_FILNUM_SHIFT(n))
#define GPIO_FILNUM24_L_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM24_L_FILNUM_SHIFT(n))

/* GPIO FILNUM25_H Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM25_H_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM25_H_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM25_H_FILNUM_SHIFT(n))
#define GPIO_FILNUM25_H_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM25_H_FILNUM_SHIFT(n))

/* GPIO FILNUM25_L Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM25_L_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM25_L_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM25_L_FILNUM_SHIFT(n))
#define GPIO_FILNUM25_L_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM25_L_FILNUM_SHIFT(n))

/* GPIO FILNUM26_H Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM26_H_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM26_H_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM26_H_FILNUM_SHIFT(n))
#define GPIO_FILNUM26_H_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM26_H_FILNUM_SHIFT(n))

/* GPIO FILNUM26_L Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM26_L_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM26_L_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM26_L_FILNUM_SHIFT(n))
#define GPIO_FILNUM26_L_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM26_L_FILNUM_SHIFT(n))

/* GPIO FILNUM27_H Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM27_H_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM27_H_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM27_H_FILNUM_SHIFT(n))
#define GPIO_FILNUM27_H_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM27_H_FILNUM_SHIFT(n))

/* GPIO FILNUM27_L Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM27_L_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM27_L_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM27_L_FILNUM_SHIFT(n))
#define GPIO_FILNUM27_L_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM27_L_FILNUM_SHIFT(n))

/* GPIO FILNUM28_H Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM28_H_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM28_H_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM28_H_FILNUM_SHIFT(n))
#define GPIO_FILNUM28_H_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM28_H_FILNUM_SHIFT(n))

/* GPIO FILNUM28_L Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM28_L_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM28_L_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM28_L_FILNUM_SHIFT(n))
#define GPIO_FILNUM28_L_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM28_L_FILNUM_SHIFT(n))

/* GPIO FILNUM29_H Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM29_H_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM29_H_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM29_H_FILNUM_SHIFT(n))
#define GPIO_FILNUM29_H_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM29_H_FILNUM_SHIFT(n))

/* GPIO FILNUM29_L Register Bit Definitions **************************/

/* FILNUM_ fields (parameterized for indices 0-3) */
#define GPIO_FILNUM29_L_FILNUM_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for FILNUMn */
#define GPIO_FILNUM29_L_FILNUM_MASK(n)                    (0x3u << GPIO_FILNUM29_L_FILNUM_SHIFT(n))
#define GPIO_FILNUM29_L_FILNUM_VAL(n,v)                   (((unsigned)(v) & 0x3u) << GPIO_FILNUM29_L_FILNUM_SHIFT(n))

/* GPIO FILNUM2A_H Register Bit Definitions **************************/

#define GPIO_FILNUM2A_H_FILNUM_2A0_SHIFT        (0)      /* Bits 0-1: Filnum 2A0 */
#define GPIO_FILNUM2A_H_FILNUM_2A0_MASK         (0x3 << GPIO_FILNUM2A_H_FILNUM_2A0_SHIFT)

#define GPIO_FILNUM2A_H_FILNUM_2A1_SHIFT        (8)      /* Bits 8-9: Filnum 2A1 */
#define GPIO_FILNUM2A_H_FILNUM_2A1_MASK         (0x3 << GPIO_FILNUM2A_H_FILNUM_2A1_SHIFT)

#define GPIO_FILNUM2A_H_FILNUM_2A2_SHIFT        (16)      /* Bits 16-17: Filnum 2A2 */
#define GPIO_FILNUM2A_H_FILNUM_2A2_MASK         (0x3 << GPIO_FILNUM2A_H_FILNUM_2A2_SHIFT)

#define GPIO_FILNUM2A_H_FILNUM_2A3_SHIFT        (24)      /* Bits 24-25: Filnum 2A3 */
#define GPIO_FILNUM2A_H_FILNUM_2A3_MASK         (0x3 << GPIO_FILNUM2A_H_FILNUM_2A3_SHIFT)

/* GPIO FILNUM2A_L Register Bit Definitions **************************/

#define GPIO_FILNUM2A_L_FILNUM_2A0_SHIFT        (0)      /* Bits 0-1: Filnum 2A0 */
#define GPIO_FILNUM2A_L_FILNUM_2A0_MASK         (0x3 << GPIO_FILNUM2A_L_FILNUM_2A0_SHIFT)

#define GPIO_FILNUM2A_L_FILNUM_2A1_SHIFT        (8)      /* Bits 8-9: Filnum 2A1 */
#define GPIO_FILNUM2A_L_FILNUM_2A1_MASK         (0x3 << GPIO_FILNUM2A_L_FILNUM_2A1_SHIFT)

#define GPIO_FILNUM2A_L_FILNUM_2A2_SHIFT        (16)      /* Bits 16-17: Filnum 2A2 */
#define GPIO_FILNUM2A_L_FILNUM_2A2_MASK         (0x3 << GPIO_FILNUM2A_L_FILNUM_2A2_SHIFT)

#define GPIO_FILNUM2A_L_FILNUM_2A3_SHIFT        (24)      /* Bits 24-25: Filnum 2A3 */
#define GPIO_FILNUM2A_L_FILNUM_2A3_MASK         (0x3 << GPIO_FILNUM2A_L_FILNUM_2A3_SHIFT)

/* GPIO FILNUM2B_H Register Bit Definitions **************************/

#define GPIO_FILNUM2B_H_FILNUM_2B0_SHIFT        (0)      /* Bits 0-1: Filnum 2B0 */
#define GPIO_FILNUM2B_H_FILNUM_2B0_MASK         (0x3 << GPIO_FILNUM2B_H_FILNUM_2B0_SHIFT)

#define GPIO_FILNUM2B_H_FILNUM_2B1_SHIFT        (8)      /* Bits 8-9: Filnum 2B1 */
#define GPIO_FILNUM2B_H_FILNUM_2B1_MASK         (0x3 << GPIO_FILNUM2B_H_FILNUM_2B1_SHIFT)

#define GPIO_FILNUM2B_H_FILNUM_2B2_SHIFT        (16)      /* Bits 16-17: Filnum 2B2 */
#define GPIO_FILNUM2B_H_FILNUM_2B2_MASK         (0x3 << GPIO_FILNUM2B_H_FILNUM_2B2_SHIFT)

#define GPIO_FILNUM2B_H_FILNUM_2B3_SHIFT        (24)      /* Bits 24-25: Filnum 2B3 */
#define GPIO_FILNUM2B_H_FILNUM_2B3_MASK         (0x3 << GPIO_FILNUM2B_H_FILNUM_2B3_SHIFT)

/* GPIO FILNUM2B_L Register Bit Definitions **************************/

#define GPIO_FILNUM2B_L_FILNUM_2B0_SHIFT        (0)      /* Bits 0-1: Filnum 2B0 */
#define GPIO_FILNUM2B_L_FILNUM_2B0_MASK         (0x3 << GPIO_FILNUM2B_L_FILNUM_2B0_SHIFT)

#define GPIO_FILNUM2B_L_FILNUM_2B1_SHIFT        (8)      /* Bits 8-9: Filnum 2B1 */
#define GPIO_FILNUM2B_L_FILNUM_2B1_MASK         (0x3 << GPIO_FILNUM2B_L_FILNUM_2B1_SHIFT)

#define GPIO_FILNUM2B_L_FILNUM_2B2_SHIFT        (16)      /* Bits 16-17: Filnum 2B2 */
#define GPIO_FILNUM2B_L_FILNUM_2B2_MASK         (0x3 << GPIO_FILNUM2B_L_FILNUM_2B2_SHIFT)

#define GPIO_FILNUM2B_L_FILNUM_2B3_SHIFT        (24)      /* Bits 24-25: Filnum 2B3 */
#define GPIO_FILNUM2B_L_FILNUM_2B3_MASK         (0x3 << GPIO_FILNUM2B_L_FILNUM_2B3_SHIFT)

/* GPIO FILONOFF1_H Register Bit Definitions *************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF1_H_FILONOFF(n)                      (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 10 */

/* GPIO FILONOFF1_L Register Bit Definitions *************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF1_L_FILONOFF(n)                      (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 10 */

/* GPIO FILONOFF20_H Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF20_H_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 200 */

/* GPIO FILONOFF20_L Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF20_L_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 200 */

/* GPIO FILONOFF21_H Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF21_H_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 210 */

/* GPIO FILONOFF21_L Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF21_L_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 210 */

/* GPIO FILONOFF22_H Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF22_H_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 220 */

/* GPIO FILONOFF22_L Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF22_L_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 220 */

/* GPIO FILONOFF23_H Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF23_H_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 230 */

/* GPIO FILONOFF23_L Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF23_L_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 230 */

/* GPIO FILONOFF24_H Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF24_H_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 240 */

/* GPIO FILONOFF24_L Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF24_L_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 240 */

/* GPIO FILONOFF25_H Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF25_H_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 250 */

/* GPIO FILONOFF25_L Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF25_L_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 250 */

/* GPIO FILONOFF26_H Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF26_H_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 260 */

/* GPIO FILONOFF26_L Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF26_L_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 260 */

/* GPIO FILONOFF27_H Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF27_H_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 270 */

/* GPIO FILONOFF27_L Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF27_L_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 270 */

/* GPIO FILONOFF28_H Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF28_H_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 280 */

/* GPIO FILONOFF28_L Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF28_L_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 280 */

/* GPIO FILONOFF29_H Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF29_H_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 290 */

/* GPIO FILONOFF29_L Register Bit Definitions ************************/

/* FILONOFF_ fields (parameterized for indices 0-3) */
#define GPIO_FILONOFF29_L_FILONOFF(n)                     (1u << (0 + ((unsigned)(n) * 8)))  /* Filonoff 290 */

/* GPIO FILONOFF2A_H Register Bit Definitions ************************/

#define GPIO_FILONOFF2A_H_FILONOFF_2A0          (1 << 0)  /* Filonoff 2A0 */

#define GPIO_FILONOFF2A_H_FILONOFF_2A1          (1 << 8)  /* Filonoff 2A1 */

#define GPIO_FILONOFF2A_H_FILONOFF_2A2          (1 << 16)  /* Filonoff 2A2 */

#define GPIO_FILONOFF2A_H_FILONOFF_2A3          (1 << 24)  /* Filonoff 2A3 */

/* GPIO FILONOFF2A_L Register Bit Definitions ************************/

#define GPIO_FILONOFF2A_L_FILONOFF_2A0          (1 << 0)  /* Filonoff 2A0 */

#define GPIO_FILONOFF2A_L_FILONOFF_2A1          (1 << 8)  /* Filonoff 2A1 */

#define GPIO_FILONOFF2A_L_FILONOFF_2A2          (1 << 16)  /* Filonoff 2A2 */

#define GPIO_FILONOFF2A_L_FILONOFF_2A3          (1 << 24)  /* Filonoff 2A3 */

/* GPIO FILONOFF2B_H Register Bit Definitions ************************/

#define GPIO_FILONOFF2B_H_FILONOFF_2B0          (1 << 0)  /* Filonoff 2B0 */

#define GPIO_FILONOFF2B_H_FILONOFF_2B1          (1 << 8)  /* Filonoff 2B1 */

#define GPIO_FILONOFF2B_H_FILONOFF_2B2          (1 << 16)  /* Filonoff 2B2 */

#define GPIO_FILONOFF2B_H_FILONOFF_2B3          (1 << 24)  /* Filonoff 2B3 */

/* GPIO FILONOFF2B_L Register Bit Definitions ************************/

#define GPIO_FILONOFF2B_L_FILONOFF_2B0          (1 << 0)  /* Filonoff 2B0 */

#define GPIO_FILONOFF2B_L_FILONOFF_2B1          (1 << 8)  /* Filonoff 2B1 */

#define GPIO_FILONOFF2B_L_FILONOFF_2B2          (1 << 16)  /* Filonoff 2B2 */

#define GPIO_FILONOFF2B_L_FILONOFF_2B3          (1 << 24)  /* Filonoff 2B3 */

/* GPIO IEN12_H Register Bit Definitions *****************************/

/* IEN_ fields (parameterized for indices 0-3) */
#define GPIO_IEN12_H_IEN(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Ien 120 */

/* GPIO IEN12_L Register Bit Definitions *****************************/

/* IEN_ fields (parameterized for indices 0-3) */
#define GPIO_IEN12_L_IEN(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Ien 120 */

/* GPIO IEN2B_H Register Bit Definitions *****************************/

#define GPIO_IEN2B_H_IEN_2B0                    (1 << 0)  /* Ien 2B0 */

#define GPIO_IEN2B_H_IEN_2B1                    (1 << 8)  /* Ien 2B1 */

#define GPIO_IEN2B_H_IEN_2B2                    (1 << 16)  /* Ien 2B2 */

#define GPIO_IEN2B_H_IEN_2B3                    (1 << 24)  /* Ien 2B3 */

/* GPIO IEN2B_L Register Bit Definitions *****************************/

#define GPIO_IEN2B_L_IEN_2B0                    (1 << 0)  /* Ien 2B0 */

#define GPIO_IEN2B_L_IEN_2B1                    (1 << 8)  /* Ien 2B1 */

#define GPIO_IEN2B_L_IEN_2B2                    (1 << 16)  /* Ien 2B2 */

#define GPIO_IEN2B_L_IEN_2B3                    (1 << 24)  /* Ien 2B3 */

/* GPIO IEN3_H Register Bit Definitions ******************************/

/* IEN_ fields (parameterized for indices 0-3) */
#define GPIO_IEN3_H_IEN(n)                                (1u << (0 + ((unsigned)(n) * 8)))  /* Ien 30 */

/* GPIO IEN3_L Register Bit Definitions ******************************/

/* IEN_ fields (parameterized for indices 0-3) */
#define GPIO_IEN3_L_IEN(n)                                (1u << (0 + ((unsigned)(n) * 8)))  /* Ien 30 */

/* GPIO IEN9_H Register Bit Definitions ******************************/

/* IEN_ fields (parameterized for indices 0-3) */
#define GPIO_IEN9_H_IEN(n)                                (1u << (0 + ((unsigned)(n) * 8)))  /* Ien 90 */

/* GPIO IEN9_L Register Bit Definitions ******************************/

/* IEN_ fields (parameterized for indices 0-3) */
#define GPIO_IEN9_L_IEN(n)                                (1u << (0 + ((unsigned)(n) * 8)))  /* Ien 90 */

/* GPIO IENA_H Register Bit Definitions ******************************/

/* IEN_A_ fields (parameterized for indices 0-3) */
#define GPIO_IENA_H_IEN_A(n)                              (1u << (0 + ((unsigned)(n) * 8)))  /* Ien A0 */

/* GPIO IENA_L Register Bit Definitions ******************************/

/* IEN_A_ fields (parameterized for indices 0-3) */
#define GPIO_IENA_L_IEN_A(n)                              (1u << (0 + ((unsigned)(n) * 8)))  /* Ien A0 */

/* GPIO IENB_H Register Bit Definitions ******************************/

/* IEN_B_ fields (parameterized for indices 0-3) */
#define GPIO_IENB_H_IEN_B(n)                              (1u << (0 + ((unsigned)(n) * 8)))  /* Ien B0 */

/* GPIO IENB_L Register Bit Definitions ******************************/

/* IEN_B_ fields (parameterized for indices 0-3) */
#define GPIO_IENB_L_IEN_B(n)                              (1u << (0 + ((unsigned)(n) * 8)))  /* Ien B0 */

/* GPIO IENC_H Register Bit Definitions ******************************/

/* IEN_C_ fields (parameterized for indices 0-3) */
#define GPIO_IENC_H_IEN_C(n)                              (1u << (0 + ((unsigned)(n) * 8)))  /* Ien C0 */

/* GPIO IENC_L Register Bit Definitions ******************************/

/* IEN_C_ fields (parameterized for indices 0-3) */
#define GPIO_IENC_L_IEN_C(n)                              (1u << (0 + ((unsigned)(n) * 8)))  /* Ien C0 */

/* GPIO IENF_H Register Bit Definitions ******************************/

/* IEN_F_ fields (parameterized for indices 0-3) */
#define GPIO_IENF_H_IEN_F(n)                              (1u << (0 + ((unsigned)(n) * 8)))  /* Ien F0 */

/* GPIO IENF_L Register Bit Definitions ******************************/

/* IEN_F_ fields (parameterized for indices 0-3) */
#define GPIO_IENF_L_IEN_F(n)                              (1u << (0 + ((unsigned)(n) * 8)))  /* Ien F0 */

/* GPIO IOLH10_H Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH10_H_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH10_H_IOLH_MASK(n)                        (0x3u << GPIO_IOLH10_H_IOLH_SHIFT(n))
#define GPIO_IOLH10_H_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH10_H_IOLH_SHIFT(n))

/* GPIO IOLH10_L Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH10_L_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH10_L_IOLH_MASK(n)                        (0x3u << GPIO_IOLH10_L_IOLH_SHIFT(n))
#define GPIO_IOLH10_L_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH10_L_IOLH_SHIFT(n))

/* GPIO IOLH11_H Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH11_H_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH11_H_IOLH_MASK(n)                        (0x3u << GPIO_IOLH11_H_IOLH_SHIFT(n))
#define GPIO_IOLH11_H_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH11_H_IOLH_SHIFT(n))

/* GPIO IOLH11_L Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH11_L_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH11_L_IOLH_MASK(n)                        (0x3u << GPIO_IOLH11_L_IOLH_SHIFT(n))
#define GPIO_IOLH11_L_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH11_L_IOLH_SHIFT(n))

/* GPIO IOLH12_H Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH12_H_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH12_H_IOLH_MASK(n)                        (0x3u << GPIO_IOLH12_H_IOLH_SHIFT(n))
#define GPIO_IOLH12_H_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH12_H_IOLH_SHIFT(n))

/* GPIO IOLH12_L Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH12_L_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH12_L_IOLH_MASK(n)                        (0x3u << GPIO_IOLH12_L_IOLH_SHIFT(n))
#define GPIO_IOLH12_L_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH12_L_IOLH_SHIFT(n))

/* GPIO IOLH13_H Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH13_H_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH13_H_IOLH_MASK(n)                        (0x3u << GPIO_IOLH13_H_IOLH_SHIFT(n))
#define GPIO_IOLH13_H_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH13_H_IOLH_SHIFT(n))

/* GPIO IOLH13_L Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH13_L_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH13_L_IOLH_MASK(n)                        (0x3u << GPIO_IOLH13_L_IOLH_SHIFT(n))
#define GPIO_IOLH13_L_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH13_L_IOLH_SHIFT(n))

/* GPIO IOLH14_H Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH14_H_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH14_H_IOLH_MASK(n)                        (0x3u << GPIO_IOLH14_H_IOLH_SHIFT(n))
#define GPIO_IOLH14_H_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH14_H_IOLH_SHIFT(n))

/* GPIO IOLH14_L Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH14_L_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH14_L_IOLH_MASK(n)                        (0x3u << GPIO_IOLH14_L_IOLH_SHIFT(n))
#define GPIO_IOLH14_L_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH14_L_IOLH_SHIFT(n))

/* GPIO IOLH20_H Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH20_H_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH20_H_IOLH_MASK(n)                        (0x3u << GPIO_IOLH20_H_IOLH_SHIFT(n))
#define GPIO_IOLH20_H_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH20_H_IOLH_SHIFT(n))

/* GPIO IOLH20_L Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH20_L_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH20_L_IOLH_MASK(n)                        (0x3u << GPIO_IOLH20_L_IOLH_SHIFT(n))
#define GPIO_IOLH20_L_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH20_L_IOLH_SHIFT(n))

/* GPIO IOLH21_H Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH21_H_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH21_H_IOLH_MASK(n)                        (0x3u << GPIO_IOLH21_H_IOLH_SHIFT(n))
#define GPIO_IOLH21_H_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH21_H_IOLH_SHIFT(n))

/* GPIO IOLH21_L Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH21_L_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH21_L_IOLH_MASK(n)                        (0x3u << GPIO_IOLH21_L_IOLH_SHIFT(n))
#define GPIO_IOLH21_L_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH21_L_IOLH_SHIFT(n))

/* GPIO IOLH22_H Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH22_H_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH22_H_IOLH_MASK(n)                        (0x3u << GPIO_IOLH22_H_IOLH_SHIFT(n))
#define GPIO_IOLH22_H_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH22_H_IOLH_SHIFT(n))

/* GPIO IOLH22_L Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH22_L_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH22_L_IOLH_MASK(n)                        (0x3u << GPIO_IOLH22_L_IOLH_SHIFT(n))
#define GPIO_IOLH22_L_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH22_L_IOLH_SHIFT(n))

/* GPIO IOLH23_H Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH23_H_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH23_H_IOLH_MASK(n)                        (0x3u << GPIO_IOLH23_H_IOLH_SHIFT(n))
#define GPIO_IOLH23_H_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH23_H_IOLH_SHIFT(n))

/* GPIO IOLH23_L Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH23_L_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH23_L_IOLH_MASK(n)                        (0x3u << GPIO_IOLH23_L_IOLH_SHIFT(n))
#define GPIO_IOLH23_L_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH23_L_IOLH_SHIFT(n))

/* GPIO IOLH24_H Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH24_H_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH24_H_IOLH_MASK(n)                        (0x3u << GPIO_IOLH24_H_IOLH_SHIFT(n))
#define GPIO_IOLH24_H_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH24_H_IOLH_SHIFT(n))

/* GPIO IOLH24_L Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH24_L_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH24_L_IOLH_MASK(n)                        (0x3u << GPIO_IOLH24_L_IOLH_SHIFT(n))
#define GPIO_IOLH24_L_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH24_L_IOLH_SHIFT(n))

/* GPIO IOLH25_H Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH25_H_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH25_H_IOLH_MASK(n)                        (0x3u << GPIO_IOLH25_H_IOLH_SHIFT(n))
#define GPIO_IOLH25_H_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH25_H_IOLH_SHIFT(n))

/* GPIO IOLH25_L Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH25_L_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH25_L_IOLH_MASK(n)                        (0x3u << GPIO_IOLH25_L_IOLH_SHIFT(n))
#define GPIO_IOLH25_L_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH25_L_IOLH_SHIFT(n))

/* GPIO IOLH26_H Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH26_H_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH26_H_IOLH_MASK(n)                        (0x3u << GPIO_IOLH26_H_IOLH_SHIFT(n))
#define GPIO_IOLH26_H_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH26_H_IOLH_SHIFT(n))

/* GPIO IOLH26_L Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH26_L_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH26_L_IOLH_MASK(n)                        (0x3u << GPIO_IOLH26_L_IOLH_SHIFT(n))
#define GPIO_IOLH26_L_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH26_L_IOLH_SHIFT(n))

/* GPIO IOLH27_H Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH27_H_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH27_H_IOLH_MASK(n)                        (0x3u << GPIO_IOLH27_H_IOLH_SHIFT(n))
#define GPIO_IOLH27_H_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH27_H_IOLH_SHIFT(n))

/* GPIO IOLH27_L Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH27_L_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH27_L_IOLH_MASK(n)                        (0x3u << GPIO_IOLH27_L_IOLH_SHIFT(n))
#define GPIO_IOLH27_L_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH27_L_IOLH_SHIFT(n))

/* GPIO IOLH28_H Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH28_H_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH28_H_IOLH_MASK(n)                        (0x3u << GPIO_IOLH28_H_IOLH_SHIFT(n))
#define GPIO_IOLH28_H_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH28_H_IOLH_SHIFT(n))

/* GPIO IOLH28_L Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH28_L_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH28_L_IOLH_MASK(n)                        (0x3u << GPIO_IOLH28_L_IOLH_SHIFT(n))
#define GPIO_IOLH28_L_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH28_L_IOLH_SHIFT(n))

/* GPIO IOLH29_H Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH29_H_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH29_H_IOLH_MASK(n)                        (0x3u << GPIO_IOLH29_H_IOLH_SHIFT(n))
#define GPIO_IOLH29_H_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH29_H_IOLH_SHIFT(n))

/* GPIO IOLH29_L Register Bit Definitions ****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH29_L_IOLH_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH29_L_IOLH_MASK(n)                        (0x3u << GPIO_IOLH29_L_IOLH_SHIFT(n))
#define GPIO_IOLH29_L_IOLH_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_IOLH29_L_IOLH_SHIFT(n))

/* GPIO IOLH2A_H Register Bit Definitions ****************************/

#define GPIO_IOLH2A_H_IOLH_2A0_SHIFT            (0)      /* Bits 0-1: Iolh 2A0 */
#define GPIO_IOLH2A_H_IOLH_2A0_MASK             (0x3 << GPIO_IOLH2A_H_IOLH_2A0_SHIFT)

#define GPIO_IOLH2A_H_IOLH_2A1_SHIFT            (8)      /* Bits 8-9: Iolh 2A1 */
#define GPIO_IOLH2A_H_IOLH_2A1_MASK             (0x3 << GPIO_IOLH2A_H_IOLH_2A1_SHIFT)

#define GPIO_IOLH2A_H_IOLH_2A2_SHIFT            (16)      /* Bits 16-17: Iolh 2A2 */
#define GPIO_IOLH2A_H_IOLH_2A2_MASK             (0x3 << GPIO_IOLH2A_H_IOLH_2A2_SHIFT)

#define GPIO_IOLH2A_H_IOLH_2A3_SHIFT            (24)      /* Bits 24-25: Iolh 2A3 */
#define GPIO_IOLH2A_H_IOLH_2A3_MASK             (0x3 << GPIO_IOLH2A_H_IOLH_2A3_SHIFT)

/* GPIO IOLH2A_L Register Bit Definitions ****************************/

#define GPIO_IOLH2A_L_IOLH_2A0_SHIFT            (0)      /* Bits 0-1: Iolh 2A0 */
#define GPIO_IOLH2A_L_IOLH_2A0_MASK             (0x3 << GPIO_IOLH2A_L_IOLH_2A0_SHIFT)

#define GPIO_IOLH2A_L_IOLH_2A1_SHIFT            (8)      /* Bits 8-9: Iolh 2A1 */
#define GPIO_IOLH2A_L_IOLH_2A1_MASK             (0x3 << GPIO_IOLH2A_L_IOLH_2A1_SHIFT)

#define GPIO_IOLH2A_L_IOLH_2A2_SHIFT            (16)      /* Bits 16-17: Iolh 2A2 */
#define GPIO_IOLH2A_L_IOLH_2A2_MASK             (0x3 << GPIO_IOLH2A_L_IOLH_2A2_SHIFT)

#define GPIO_IOLH2A_L_IOLH_2A3_SHIFT            (24)      /* Bits 24-25: Iolh 2A3 */
#define GPIO_IOLH2A_L_IOLH_2A3_MASK             (0x3 << GPIO_IOLH2A_L_IOLH_2A3_SHIFT)

/* GPIO IOLH2B_H Register Bit Definitions ****************************/

#define GPIO_IOLH2B_H_IOLH_2B0_SHIFT            (0)      /* Bits 0-1: Iolh 2B0 */
#define GPIO_IOLH2B_H_IOLH_2B0_MASK             (0x3 << GPIO_IOLH2B_H_IOLH_2B0_SHIFT)

#define GPIO_IOLH2B_H_IOLH_2B1_SHIFT            (8)      /* Bits 8-9: Iolh 2B1 */
#define GPIO_IOLH2B_H_IOLH_2B1_MASK             (0x3 << GPIO_IOLH2B_H_IOLH_2B1_SHIFT)

#define GPIO_IOLH2B_H_IOLH_2B2_SHIFT            (16)      /* Bits 16-17: Iolh 2B2 */
#define GPIO_IOLH2B_H_IOLH_2B2_MASK             (0x3 << GPIO_IOLH2B_H_IOLH_2B2_SHIFT)

#define GPIO_IOLH2B_H_IOLH_2B3_SHIFT            (24)      /* Bits 24-25: Iolh 2B3 */
#define GPIO_IOLH2B_H_IOLH_2B3_MASK             (0x3 << GPIO_IOLH2B_H_IOLH_2B3_SHIFT)

/* GPIO IOLH2B_L Register Bit Definitions ****************************/

#define GPIO_IOLH2B_L_IOLH_2B0_SHIFT            (0)      /* Bits 0-1: Iolh 2B0 */
#define GPIO_IOLH2B_L_IOLH_2B0_MASK             (0x3 << GPIO_IOLH2B_L_IOLH_2B0_SHIFT)

#define GPIO_IOLH2B_L_IOLH_2B1_SHIFT            (8)      /* Bits 8-9: Iolh 2B1 */
#define GPIO_IOLH2B_L_IOLH_2B1_MASK             (0x3 << GPIO_IOLH2B_L_IOLH_2B1_SHIFT)

#define GPIO_IOLH2B_L_IOLH_2B2_SHIFT            (16)      /* Bits 16-17: Iolh 2B2 */
#define GPIO_IOLH2B_L_IOLH_2B2_MASK             (0x3 << GPIO_IOLH2B_L_IOLH_2B2_SHIFT)

#define GPIO_IOLH2B_L_IOLH_2B3_SHIFT            (24)      /* Bits 24-25: Iolh 2B3 */
#define GPIO_IOLH2B_L_IOLH_2B3_MASK             (0x3 << GPIO_IOLH2B_L_IOLH_2B3_SHIFT)

/* GPIO IOLH3_H Register Bit Definitions *****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH3_H_IOLH_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH3_H_IOLH_MASK(n)                         (0x3u << GPIO_IOLH3_H_IOLH_SHIFT(n))
#define GPIO_IOLH3_H_IOLH_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_IOLH3_H_IOLH_SHIFT(n))

/* GPIO IOLH3_L Register Bit Definitions *****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH3_L_IOLH_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH3_L_IOLH_MASK(n)                         (0x3u << GPIO_IOLH3_L_IOLH_SHIFT(n))
#define GPIO_IOLH3_L_IOLH_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_IOLH3_L_IOLH_SHIFT(n))

/* GPIO IOLH5_H Register Bit Definitions *****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH5_H_IOLH_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH5_H_IOLH_MASK(n)                         (0x3u << GPIO_IOLH5_H_IOLH_SHIFT(n))
#define GPIO_IOLH5_H_IOLH_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_IOLH5_H_IOLH_SHIFT(n))

/* GPIO IOLH5_L Register Bit Definitions *****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH5_L_IOLH_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH5_L_IOLH_MASK(n)                         (0x3u << GPIO_IOLH5_L_IOLH_SHIFT(n))
#define GPIO_IOLH5_L_IOLH_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_IOLH5_L_IOLH_SHIFT(n))

/* GPIO IOLH6_H Register Bit Definitions *****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH6_H_IOLH_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH6_H_IOLH_MASK(n)                         (0x3u << GPIO_IOLH6_H_IOLH_SHIFT(n))
#define GPIO_IOLH6_H_IOLH_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_IOLH6_H_IOLH_SHIFT(n))

/* GPIO IOLH6_L Register Bit Definitions *****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH6_L_IOLH_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH6_L_IOLH_MASK(n)                         (0x3u << GPIO_IOLH6_L_IOLH_SHIFT(n))
#define GPIO_IOLH6_L_IOLH_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_IOLH6_L_IOLH_SHIFT(n))

/* GPIO IOLH7_H Register Bit Definitions *****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH7_H_IOLH_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH7_H_IOLH_MASK(n)                         (0x3u << GPIO_IOLH7_H_IOLH_SHIFT(n))
#define GPIO_IOLH7_H_IOLH_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_IOLH7_H_IOLH_SHIFT(n))

/* GPIO IOLH7_L Register Bit Definitions *****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH7_L_IOLH_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH7_L_IOLH_MASK(n)                         (0x3u << GPIO_IOLH7_L_IOLH_SHIFT(n))
#define GPIO_IOLH7_L_IOLH_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_IOLH7_L_IOLH_SHIFT(n))

/* GPIO IOLH8_H Register Bit Definitions *****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH8_H_IOLH_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH8_H_IOLH_MASK(n)                         (0x3u << GPIO_IOLH8_H_IOLH_SHIFT(n))
#define GPIO_IOLH8_H_IOLH_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_IOLH8_H_IOLH_SHIFT(n))

/* GPIO IOLH8_L Register Bit Definitions *****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH8_L_IOLH_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH8_L_IOLH_MASK(n)                         (0x3u << GPIO_IOLH8_L_IOLH_SHIFT(n))
#define GPIO_IOLH8_L_IOLH_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_IOLH8_L_IOLH_SHIFT(n))

/* GPIO IOLH9_H Register Bit Definitions *****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH9_H_IOLH_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH9_H_IOLH_MASK(n)                         (0x3u << GPIO_IOLH9_H_IOLH_SHIFT(n))
#define GPIO_IOLH9_H_IOLH_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_IOLH9_H_IOLH_SHIFT(n))

/* GPIO IOLH9_L Register Bit Definitions *****************************/

/* IOLH_ fields (parameterized for indices 0-3) */
#define GPIO_IOLH9_L_IOLH_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLHn */
#define GPIO_IOLH9_L_IOLH_MASK(n)                         (0x3u << GPIO_IOLH9_L_IOLH_SHIFT(n))
#define GPIO_IOLH9_L_IOLH_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_IOLH9_L_IOLH_SHIFT(n))

/* GPIO IOLHA_H Register Bit Definitions *****************************/

/* IOLH_A_ fields (parameterized for indices 0-3) */
#define GPIO_IOLHA_H_IOLH_A_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLH_An */
#define GPIO_IOLHA_H_IOLH_A_MASK(n)                       (0x3u << GPIO_IOLHA_H_IOLH_A_SHIFT(n))
#define GPIO_IOLHA_H_IOLH_A_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_IOLHA_H_IOLH_A_SHIFT(n))

/* GPIO IOLHA_L Register Bit Definitions *****************************/

/* IOLH_A_ fields (parameterized for indices 0-3) */
#define GPIO_IOLHA_L_IOLH_A_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLH_An */
#define GPIO_IOLHA_L_IOLH_A_MASK(n)                       (0x3u << GPIO_IOLHA_L_IOLH_A_SHIFT(n))
#define GPIO_IOLHA_L_IOLH_A_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_IOLHA_L_IOLH_A_SHIFT(n))

/* GPIO IOLHB_H Register Bit Definitions *****************************/

/* IOLH_B_ fields (parameterized for indices 0-3) */
#define GPIO_IOLHB_H_IOLH_B_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLH_Bn */
#define GPIO_IOLHB_H_IOLH_B_MASK(n)                       (0x3u << GPIO_IOLHB_H_IOLH_B_SHIFT(n))
#define GPIO_IOLHB_H_IOLH_B_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_IOLHB_H_IOLH_B_SHIFT(n))

/* GPIO IOLHB_L Register Bit Definitions *****************************/

/* IOLH_B_ fields (parameterized for indices 0-3) */
#define GPIO_IOLHB_L_IOLH_B_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLH_Bn */
#define GPIO_IOLHB_L_IOLH_B_MASK(n)                       (0x3u << GPIO_IOLHB_L_IOLH_B_SHIFT(n))
#define GPIO_IOLHB_L_IOLH_B_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_IOLHB_L_IOLH_B_SHIFT(n))

/* GPIO IOLHC_H Register Bit Definitions *****************************/

/* IOLH_C_ fields (parameterized for indices 0-3) */
#define GPIO_IOLHC_H_IOLH_C_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLH_Cn */
#define GPIO_IOLHC_H_IOLH_C_MASK(n)                       (0x3u << GPIO_IOLHC_H_IOLH_C_SHIFT(n))
#define GPIO_IOLHC_H_IOLH_C_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_IOLHC_H_IOLH_C_SHIFT(n))

/* GPIO IOLHC_L Register Bit Definitions *****************************/

/* IOLH_C_ fields (parameterized for indices 0-3) */
#define GPIO_IOLHC_L_IOLH_C_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLH_Cn */
#define GPIO_IOLHC_L_IOLH_C_MASK(n)                       (0x3u << GPIO_IOLHC_L_IOLH_C_SHIFT(n))
#define GPIO_IOLHC_L_IOLH_C_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_IOLHC_L_IOLH_C_SHIFT(n))

/* GPIO IOLHE_H Register Bit Definitions *****************************/

/* IOLH_E_ fields (parameterized for indices 0-3) */
#define GPIO_IOLHE_H_IOLH_E_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLH_En */
#define GPIO_IOLHE_H_IOLH_E_MASK(n)                       (0x3u << GPIO_IOLHE_H_IOLH_E_SHIFT(n))
#define GPIO_IOLHE_H_IOLH_E_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_IOLHE_H_IOLH_E_SHIFT(n))

/* GPIO IOLHE_L Register Bit Definitions *****************************/

/* IOLH_E_ fields (parameterized for indices 0-3) */
#define GPIO_IOLHE_L_IOLH_E_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLH_En */
#define GPIO_IOLHE_L_IOLH_E_MASK(n)                       (0x3u << GPIO_IOLHE_L_IOLH_E_SHIFT(n))
#define GPIO_IOLHE_L_IOLH_E_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_IOLHE_L_IOLH_E_SHIFT(n))

/* GPIO IOLHF_H Register Bit Definitions *****************************/

/* IOLH_F_ fields (parameterized for indices 0-3) */
#define GPIO_IOLHF_H_IOLH_F_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLH_Fn */
#define GPIO_IOLHF_H_IOLH_F_MASK(n)                       (0x3u << GPIO_IOLHF_H_IOLH_F_SHIFT(n))
#define GPIO_IOLHF_H_IOLH_F_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_IOLHF_H_IOLH_F_SHIFT(n))

/* GPIO IOLHF_L Register Bit Definitions *****************************/

/* IOLH_F_ fields (parameterized for indices 0-3) */
#define GPIO_IOLHF_L_IOLH_F_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for IOLH_Fn */
#define GPIO_IOLHF_L_IOLH_F_MASK(n)                       (0x3u << GPIO_IOLHF_L_IOLH_F_SHIFT(n))
#define GPIO_IOLHF_L_IOLH_F_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_IOLHF_L_IOLH_F_SHIFT(n))

/* GPIO ISEL20_H Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL20_H_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 200 */

/* GPIO ISEL20_L Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL20_L_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 200 */

/* GPIO ISEL21_H Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL21_H_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 210 */

/* GPIO ISEL21_L Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL21_L_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 210 */

/* GPIO ISEL22_H Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL22_H_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 220 */

/* GPIO ISEL22_L Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL22_L_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 220 */

/* GPIO ISEL23_H Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL23_H_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 230 */

/* GPIO ISEL23_L Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL23_L_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 230 */

/* GPIO ISEL24_H Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL24_H_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 240 */

/* GPIO ISEL24_L Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL24_L_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 240 */

/* GPIO ISEL25_H Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL25_H_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 250 */

/* GPIO ISEL25_L Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL25_L_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 250 */

/* GPIO ISEL26_H Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL26_H_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 260 */

/* GPIO ISEL26_L Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL26_L_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 260 */

/* GPIO ISEL27_H Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL27_H_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 270 */

/* GPIO ISEL27_L Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL27_L_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 270 */

/* GPIO ISEL28_H Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL28_H_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 280 */

/* GPIO ISEL28_L Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL28_L_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 280 */

/* GPIO ISEL29_H Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL29_H_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 290 */

/* GPIO ISEL29_L Register Bit Definitions ****************************/

/* ISEL_ fields (parameterized for indices 0-3) */
#define GPIO_ISEL29_L_ISEL(n)                             (1u << (0 + ((unsigned)(n) * 8)))  /* Isel 290 */

/* GPIO ISEL2A_H Register Bit Definitions ****************************/

#define GPIO_ISEL2A_H_ISEL_2A0                  (1 << 0)  /* Isel 2A0 */

#define GPIO_ISEL2A_H_ISEL_2A1                  (1 << 8)  /* Isel 2A1 */

#define GPIO_ISEL2A_H_ISEL_2A2                  (1 << 16)  /* Isel 2A2 */

#define GPIO_ISEL2A_H_ISEL_2A3                  (1 << 24)  /* Isel 2A3 */

/* GPIO ISEL2A_L Register Bit Definitions ****************************/

#define GPIO_ISEL2A_L_ISEL_2A0                  (1 << 0)  /* Isel 2A0 */

#define GPIO_ISEL2A_L_ISEL_2A1                  (1 << 8)  /* Isel 2A1 */

#define GPIO_ISEL2A_L_ISEL_2A2                  (1 << 16)  /* Isel 2A2 */

#define GPIO_ISEL2A_L_ISEL_2A3                  (1 << 24)  /* Isel 2A3 */

/* GPIO ISEL2B_H Register Bit Definitions ****************************/

#define GPIO_ISEL2B_H_ISEL_2B0                  (1 << 0)  /* Isel 2B0 */

#define GPIO_ISEL2B_H_ISEL_2B1                  (1 << 8)  /* Isel 2B1 */

#define GPIO_ISEL2B_H_ISEL_2B2                  (1 << 16)  /* Isel 2B2 */

#define GPIO_ISEL2B_H_ISEL_2B3                  (1 << 24)  /* Isel 2B3 */

/* GPIO ISEL2B_L Register Bit Definitions ****************************/

#define GPIO_ISEL2B_L_ISEL_2B0                  (1 << 0)  /* Isel 2B0 */

#define GPIO_ISEL2B_L_ISEL_2B1                  (1 << 8)  /* Isel 2B1 */

#define GPIO_ISEL2B_L_ISEL_2B2                  (1 << 16)  /* Isel 2B2 */

#define GPIO_ISEL2B_L_ISEL_2B3                  (1 << 24)  /* Isel 2B3 */

/* GPIO NOD20_H Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD20_H_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 200 */

/* GPIO NOD20_L Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD20_L_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 200 */

/* GPIO NOD21_H Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD21_H_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 210 */

/* GPIO NOD21_L Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD21_L_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 210 */

/* GPIO NOD22_H Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD22_H_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 220 */

/* GPIO NOD22_L Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD22_L_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 220 */

/* GPIO NOD23_H Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD23_H_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 230 */

/* GPIO NOD23_L Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD23_L_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 230 */

/* GPIO NOD24_H Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD24_H_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 240 */

/* GPIO NOD24_L Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD24_L_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 240 */

/* GPIO NOD25_H Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD25_H_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 250 */

/* GPIO NOD25_L Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD25_L_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 250 */

/* GPIO NOD26_H Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD26_H_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 260 */

/* GPIO NOD26_L Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD26_L_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 260 */

/* GPIO NOD27_H Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD27_H_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 270 */

/* GPIO NOD27_L Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD27_L_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 270 */

/* GPIO NOD28_H Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD28_H_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 280 */

/* GPIO NOD28_L Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD28_L_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 280 */

/* GPIO NOD29_H Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD29_H_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 290 */

/* GPIO NOD29_L Register Bit Definitions *****************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD29_L_NOD(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 290 */

/* GPIO NOD2A_H Register Bit Definitions *****************************/

#define GPIO_NOD2A_H_NOD_2A0                    (1 << 0)  /* Nod 2A0 */

#define GPIO_NOD2A_H_NOD_2A1                    (1 << 8)  /* Nod 2A1 */

#define GPIO_NOD2A_H_NOD_2A2                    (1 << 16)  /* Nod 2A2 */

#define GPIO_NOD2A_H_NOD_2A3                    (1 << 24)  /* Nod 2A3 */

/* GPIO NOD2A_L Register Bit Definitions *****************************/

#define GPIO_NOD2A_L_NOD_2A0                    (1 << 0)  /* Nod 2A0 */

#define GPIO_NOD2A_L_NOD_2A1                    (1 << 8)  /* Nod 2A1 */

#define GPIO_NOD2A_L_NOD_2A2                    (1 << 16)  /* Nod 2A2 */

#define GPIO_NOD2A_L_NOD_2A3                    (1 << 24)  /* Nod 2A3 */

/* GPIO NOD2B_H Register Bit Definitions *****************************/

#define GPIO_NOD2B_H_NOD_2B0                    (1 << 0)  /* Nod 2B0 */

#define GPIO_NOD2B_H_NOD_2B1                    (1 << 8)  /* Nod 2B1 */

#define GPIO_NOD2B_H_NOD_2B2                    (1 << 16)  /* Nod 2B2 */

#define GPIO_NOD2B_H_NOD_2B3                    (1 << 24)  /* Nod 2B3 */

/* GPIO NOD2B_L Register Bit Definitions *****************************/

#define GPIO_NOD2B_L_NOD_2B0                    (1 << 0)  /* Nod 2B0 */

#define GPIO_NOD2B_L_NOD_2B1                    (1 << 8)  /* Nod 2B1 */

#define GPIO_NOD2B_L_NOD_2B2                    (1 << 16)  /* Nod 2B2 */

#define GPIO_NOD2B_L_NOD_2B3                    (1 << 24)  /* Nod 2B3 */

/* GPIO NOD5_H Register Bit Definitions ******************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD5_H_NOD(n)                                (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 50 */

/* GPIO NOD5_L Register Bit Definitions ******************************/

/* NOD_ fields (parameterized for indices 0-3) */
#define GPIO_NOD5_L_NOD(n)                                (1u << (0 + ((unsigned)(n) * 8)))  /* Nod 50 */

/* GPIO P2A Register Bit Definitions *********************************/

/* PA fields (parameterized for indices 0-7) */
#define GPIO_P2A_PA(n)                                    (1u << (0 + ((unsigned)(n) * 1)))  /* Pa */

/* GPIO P2B Register Bit Definitions *********************************/

/* PB fields (parameterized for indices 0-7) */
#define GPIO_P2B_PB(n)                                    (1u << (0 + ((unsigned)(n) * 1)))  /* Pb */

/* GPIO PFC2A Register Bit Definitions *******************************/

/* PFC_A_ fields (parameterized for indices 0-7) */
#define GPIO_PFC2A_PFC_A_SHIFT(n)                         ((unsigned)(0 + ((n) * 4)))  /* Bits for PFC_An */
#define GPIO_PFC2A_PFC_A_MASK(n)                          (0xfu << GPIO_PFC2A_PFC_A_SHIFT(n))
#define GPIO_PFC2A_PFC_A_VAL(n,v)                         (((unsigned)(v) & 0xfu) << GPIO_PFC2A_PFC_A_SHIFT(n))

/* GPIO PFC2B Register Bit Definitions *******************************/

/* PFC_B_ fields (parameterized for indices 0-5) */
#define GPIO_PFC2B_PFC_B_SHIFT(n)                         ((unsigned)(0 + ((n) * 4)))  /* Bits for PFC_Bn */
#define GPIO_PFC2B_PFC_B_MASK(n)                          (0xfu << GPIO_PFC2B_PFC_B_SHIFT(n))
#define GPIO_PFC2B_PFC_B_VAL(n,v)                         (((unsigned)(v) & 0xfu) << GPIO_PFC2B_PFC_B_SHIFT(n))

/* GPIO PFC_ELC_ELSR2 Register Bit Definitions ***********************/

#define GPIO_PFC_ELC_ELSR2_PEG_SHIFT            (2)      /* Bits 2-3: Peg */
#define GPIO_PFC_ELC_ELSR2_PEG_MASK             (0x3 << GPIO_PFC_ELC_ELSR2_PEG_SHIFT)

#define GPIO_PFC_ELC_ELSR2_PES_SHIFT            (4)      /* Bits 4-7: Pes */
#define GPIO_PFC_ELC_ELSR2_PES_MASK             (0xf << GPIO_PFC_ELC_ELSR2_PES_SHIFT)

/* GPIO PFC_FILCLKSEL_DMAC_REQ Register Bit Definitions **************/

/* DMAC_REQ_ fields (parameterized for indices 0-4) */
#define GPIO_PFC_FILCLKSEL_DMAC_REQ_DMAC_REQ_SHIFT(n)     ((unsigned)(0 + ((n) * 2)))  /* Bits for DMAC_REQn */
#define GPIO_PFC_FILCLKSEL_DMAC_REQ_DMAC_REQ_MASK(n)      (0x3u << GPIO_PFC_FILCLKSEL_DMAC_REQ_DMAC_REQ_SHIFT(n))
#define GPIO_PFC_FILCLKSEL_DMAC_REQ_DMAC_REQ_VAL(n,v)     (((unsigned)(v) & 0x3u) << GPIO_PFC_FILCLKSEL_DMAC_REQ_DMAC_REQ_SHIFT(n))

/* GPIO PFC_FILCLKSEL_IRQ Register Bit Definitions *******************/

/* IRQ fields (parameterized for indices 0-15) */
#define GPIO_PFC_FILCLKSEL_IRQ_IRQ_SHIFT(n)               ((unsigned)(0 + ((n) * 2)))  /* Bits for IRQn */
#define GPIO_PFC_FILCLKSEL_IRQ_IRQ_MASK(n)                (0x3u << GPIO_PFC_FILCLKSEL_IRQ_IRQ_SHIFT(n))
#define GPIO_PFC_FILCLKSEL_IRQ_IRQ_VAL(n,v)               (((unsigned)(v) & 0x3u) << GPIO_PFC_FILCLKSEL_IRQ_IRQ_SHIFT(n))

/* GPIO PFC_FILNUM_DMAC_REQ Register Bit Definitions *****************/

/* DMAC_REQ_ fields (parameterized for indices 0-4) */
#define GPIO_PFC_FILNUM_DMAC_REQ_DMAC_REQ_SHIFT(n)        ((unsigned)(0 + ((n) * 2)))  /* Bits for DMAC_REQn */
#define GPIO_PFC_FILNUM_DMAC_REQ_DMAC_REQ_MASK(n)         (0x3u << GPIO_PFC_FILNUM_DMAC_REQ_DMAC_REQ_SHIFT(n))
#define GPIO_PFC_FILNUM_DMAC_REQ_DMAC_REQ_VAL(n,v)        (((unsigned)(v) & 0x3u) << GPIO_PFC_FILNUM_DMAC_REQ_DMAC_REQ_SHIFT(n))

/* GPIO PFC_FILNUM_IRQ Register Bit Definitions **********************/

/* IRQ fields (parameterized for indices 0-15) */
#define GPIO_PFC_FILNUM_IRQ_IRQ_SHIFT(n)                  ((unsigned)(0 + ((n) * 2)))  /* Bits for IRQn */
#define GPIO_PFC_FILNUM_IRQ_IRQ_MASK(n)                   (0x3u << GPIO_PFC_FILNUM_IRQ_IRQ_SHIFT(n))
#define GPIO_PFC_FILNUM_IRQ_IRQ_VAL(n,v)                  (((unsigned)(v) & 0x3u) << GPIO_PFC_FILNUM_IRQ_IRQ_SHIFT(n))

/* GPIO PFC_FILONOFF_DMAC_REQ Register Bit Definitions ***************/

/* DMAC_REQ_ fields (parameterized for indices 0-4) */
#define GPIO_PFC_FILONOFF_DMAC_REQ_DMAC_REQ(n)            (1u << (0 + ((unsigned)(n) * 2)))  /* Dmac Req0 */

/* GPIO PFC_FILONOFF_IRQ Register Bit Definitions ********************/

/* IRQ fields (parameterized for indices 0-15) */
#define GPIO_PFC_FILONOFF_IRQ_IRQ(n)                      (1u << (0 + ((unsigned)(n) * 2)))  /* Irq0 */

/* GPIO PFC_OEN Register Bit Definitions *****************************/

/* OEN fields (parameterized for indices 0-5) */
#define GPIO_PFC_OEN_OEN(n)                               (1u << (0 + ((unsigned)(n) * 1)))  /* Oen0 */

/* GPIO PFC_OSCBYPS Register Bit Definitions *************************/

/* OSCBYPS fields (parameterized for indices 0-2) */
#define GPIO_PFC_OSCBYPS_OSCBYPS(n)                       (1u << (0 + ((unsigned)(n) * 1)))  /* Oscbyps0 */

/* OSCPW fields (parameterized for indices 0-2) */
#define GPIO_PFC_OSCBYPS_OSCPW(n)                         (1u << (8 + ((unsigned)(n) * 1)))  /* Oscpw0 */

#define GPIO_PFC_OSCBYPS_OSCSF1_SHIFT           (18)      /* Bits 18-19: Oscsf1 */
#define GPIO_PFC_OSCBYPS_OSCSF1_MASK            (0x3 << GPIO_PFC_OSCBYPS_OSCSF1_SHIFT)

#define GPIO_PFC_OSCBYPS_OSCSF2_SHIFT           (20)      /* Bits 20-21: Oscsf2 */
#define GPIO_PFC_OSCBYPS_OSCSF2_MASK            (0x3 << GPIO_PFC_OSCBYPS_OSCSF2_SHIFT)

/* GPIO PIN2A Register Bit Definitions *******************************/

/* PINA fields (parameterized for indices 0-7) */
#define GPIO_PIN2A_PINA(n)                                (1u << (0 + ((unsigned)(n) * 1)))  /* Pina */

/* GPIO PIN2B Register Bit Definitions *******************************/

/* PINB fields (parameterized for indices 0-5) */
#define GPIO_PIN2B_PINB(n)                                (1u << (0 + ((unsigned)(n) * 1)))  /* Pinb */

/* GPIO PM2A Register Bit Definitions ********************************/

/* PM_A_ fields (parameterized for indices 0-7) */
#define GPIO_PM2A_PM_A_SHIFT(n)                           ((unsigned)(0 + ((n) * 2)))  /* Bits for PM_An */
#define GPIO_PM2A_PM_A_MASK(n)                            (0x3u << GPIO_PM2A_PM_A_SHIFT(n))
#define GPIO_PM2A_PM_A_VAL(n,v)                           (((unsigned)(v) & 0x3u) << GPIO_PM2A_PM_A_SHIFT(n))

/* GPIO PM2B Register Bit Definitions ********************************/

/* PM_B_ fields (parameterized for indices 0-5) */
#define GPIO_PM2B_PM_B_SHIFT(n)                           ((unsigned)(0 + ((n) * 2)))  /* Bits for PM_Bn */
#define GPIO_PM2B_PM_B_MASK(n)                            (0x3u << GPIO_PM2B_PM_B_SHIFT(n))
#define GPIO_PM2B_PM_B_VAL(n,v)                           (((unsigned)(v) & 0x3u) << GPIO_PM2B_PM_B_SHIFT(n))

/* GPIO PMC2A Register Bit Definitions *******************************/

/* PA fields (parameterized for indices 0-7) */
#define GPIO_PMC2A_PA(n)                                  (1u << (0 + ((unsigned)(n) * 1)))  /* Pa */

/* GPIO PMC2B Register Bit Definitions *******************************/

/* PB fields (parameterized for indices 0-5) */
#define GPIO_PMC2B_PB(n)                                  (1u << (0 + ((unsigned)(n) * 1)))  /* Pb */

/* GPIO PUPD10_H Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD10_H_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD10_H_PUPD_MASK(n)                        (0x3u << GPIO_PUPD10_H_PUPD_SHIFT(n))
#define GPIO_PUPD10_H_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD10_H_PUPD_SHIFT(n))

/* GPIO PUPD10_L Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD10_L_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD10_L_PUPD_MASK(n)                        (0x3u << GPIO_PUPD10_L_PUPD_SHIFT(n))
#define GPIO_PUPD10_L_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD10_L_PUPD_SHIFT(n))

/* GPIO PUPD11_H Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD11_H_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD11_H_PUPD_MASK(n)                        (0x3u << GPIO_PUPD11_H_PUPD_SHIFT(n))
#define GPIO_PUPD11_H_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD11_H_PUPD_SHIFT(n))

/* GPIO PUPD11_L Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD11_L_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD11_L_PUPD_MASK(n)                        (0x3u << GPIO_PUPD11_L_PUPD_SHIFT(n))
#define GPIO_PUPD11_L_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD11_L_PUPD_SHIFT(n))

/* GPIO PUPD12_H Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD12_H_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD12_H_PUPD_MASK(n)                        (0x3u << GPIO_PUPD12_H_PUPD_SHIFT(n))
#define GPIO_PUPD12_H_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD12_H_PUPD_SHIFT(n))

/* GPIO PUPD12_L Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD12_L_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD12_L_PUPD_MASK(n)                        (0x3u << GPIO_PUPD12_L_PUPD_SHIFT(n))
#define GPIO_PUPD12_L_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD12_L_PUPD_SHIFT(n))

/* GPIO PUPD13_H Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD13_H_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD13_H_PUPD_MASK(n)                        (0x3u << GPIO_PUPD13_H_PUPD_SHIFT(n))
#define GPIO_PUPD13_H_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD13_H_PUPD_SHIFT(n))

/* GPIO PUPD13_L Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD13_L_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD13_L_PUPD_MASK(n)                        (0x3u << GPIO_PUPD13_L_PUPD_SHIFT(n))
#define GPIO_PUPD13_L_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD13_L_PUPD_SHIFT(n))

/* GPIO PUPD14_H Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD14_H_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD14_H_PUPD_MASK(n)                        (0x3u << GPIO_PUPD14_H_PUPD_SHIFT(n))
#define GPIO_PUPD14_H_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD14_H_PUPD_SHIFT(n))

/* GPIO PUPD14_L Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD14_L_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD14_L_PUPD_MASK(n)                        (0x3u << GPIO_PUPD14_L_PUPD_SHIFT(n))
#define GPIO_PUPD14_L_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD14_L_PUPD_SHIFT(n))

/* GPIO PUPD20_H Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD20_H_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD20_H_PUPD_MASK(n)                        (0x3u << GPIO_PUPD20_H_PUPD_SHIFT(n))
#define GPIO_PUPD20_H_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD20_H_PUPD_SHIFT(n))

/* GPIO PUPD20_L Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD20_L_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD20_L_PUPD_MASK(n)                        (0x3u << GPIO_PUPD20_L_PUPD_SHIFT(n))
#define GPIO_PUPD20_L_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD20_L_PUPD_SHIFT(n))

/* GPIO PUPD21_H Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD21_H_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD21_H_PUPD_MASK(n)                        (0x3u << GPIO_PUPD21_H_PUPD_SHIFT(n))
#define GPIO_PUPD21_H_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD21_H_PUPD_SHIFT(n))

/* GPIO PUPD21_L Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD21_L_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD21_L_PUPD_MASK(n)                        (0x3u << GPIO_PUPD21_L_PUPD_SHIFT(n))
#define GPIO_PUPD21_L_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD21_L_PUPD_SHIFT(n))

/* GPIO PUPD22_H Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD22_H_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD22_H_PUPD_MASK(n)                        (0x3u << GPIO_PUPD22_H_PUPD_SHIFT(n))
#define GPIO_PUPD22_H_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD22_H_PUPD_SHIFT(n))

/* GPIO PUPD22_L Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD22_L_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD22_L_PUPD_MASK(n)                        (0x3u << GPIO_PUPD22_L_PUPD_SHIFT(n))
#define GPIO_PUPD22_L_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD22_L_PUPD_SHIFT(n))

/* GPIO PUPD23_H Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD23_H_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD23_H_PUPD_MASK(n)                        (0x3u << GPIO_PUPD23_H_PUPD_SHIFT(n))
#define GPIO_PUPD23_H_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD23_H_PUPD_SHIFT(n))

/* GPIO PUPD23_L Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD23_L_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD23_L_PUPD_MASK(n)                        (0x3u << GPIO_PUPD23_L_PUPD_SHIFT(n))
#define GPIO_PUPD23_L_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD23_L_PUPD_SHIFT(n))

/* GPIO PUPD24_H Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD24_H_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD24_H_PUPD_MASK(n)                        (0x3u << GPIO_PUPD24_H_PUPD_SHIFT(n))
#define GPIO_PUPD24_H_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD24_H_PUPD_SHIFT(n))

/* GPIO PUPD24_L Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD24_L_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD24_L_PUPD_MASK(n)                        (0x3u << GPIO_PUPD24_L_PUPD_SHIFT(n))
#define GPIO_PUPD24_L_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD24_L_PUPD_SHIFT(n))

/* GPIO PUPD25_H Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD25_H_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD25_H_PUPD_MASK(n)                        (0x3u << GPIO_PUPD25_H_PUPD_SHIFT(n))
#define GPIO_PUPD25_H_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD25_H_PUPD_SHIFT(n))

/* GPIO PUPD25_L Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD25_L_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD25_L_PUPD_MASK(n)                        (0x3u << GPIO_PUPD25_L_PUPD_SHIFT(n))
#define GPIO_PUPD25_L_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD25_L_PUPD_SHIFT(n))

/* GPIO PUPD26_H Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD26_H_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD26_H_PUPD_MASK(n)                        (0x3u << GPIO_PUPD26_H_PUPD_SHIFT(n))
#define GPIO_PUPD26_H_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD26_H_PUPD_SHIFT(n))

/* GPIO PUPD26_L Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD26_L_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD26_L_PUPD_MASK(n)                        (0x3u << GPIO_PUPD26_L_PUPD_SHIFT(n))
#define GPIO_PUPD26_L_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD26_L_PUPD_SHIFT(n))

/* GPIO PUPD27_H Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD27_H_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD27_H_PUPD_MASK(n)                        (0x3u << GPIO_PUPD27_H_PUPD_SHIFT(n))
#define GPIO_PUPD27_H_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD27_H_PUPD_SHIFT(n))

/* GPIO PUPD27_L Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD27_L_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD27_L_PUPD_MASK(n)                        (0x3u << GPIO_PUPD27_L_PUPD_SHIFT(n))
#define GPIO_PUPD27_L_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD27_L_PUPD_SHIFT(n))

/* GPIO PUPD28_H Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD28_H_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD28_H_PUPD_MASK(n)                        (0x3u << GPIO_PUPD28_H_PUPD_SHIFT(n))
#define GPIO_PUPD28_H_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD28_H_PUPD_SHIFT(n))

/* GPIO PUPD28_L Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD28_L_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD28_L_PUPD_MASK(n)                        (0x3u << GPIO_PUPD28_L_PUPD_SHIFT(n))
#define GPIO_PUPD28_L_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD28_L_PUPD_SHIFT(n))

/* GPIO PUPD29_H Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD29_H_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD29_H_PUPD_MASK(n)                        (0x3u << GPIO_PUPD29_H_PUPD_SHIFT(n))
#define GPIO_PUPD29_H_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD29_H_PUPD_SHIFT(n))

/* GPIO PUPD29_L Register Bit Definitions ****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD29_L_PUPD_SHIFT(n)                       ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD29_L_PUPD_MASK(n)                        (0x3u << GPIO_PUPD29_L_PUPD_SHIFT(n))
#define GPIO_PUPD29_L_PUPD_VAL(n,v)                       (((unsigned)(v) & 0x3u) << GPIO_PUPD29_L_PUPD_SHIFT(n))

/* GPIO PUPD2A_H Register Bit Definitions ****************************/

#define GPIO_PUPD2A_H_PUPD_2A0_SHIFT            (0)      /* Bits 0-1: Pupd 2A0 */
#define GPIO_PUPD2A_H_PUPD_2A0_MASK             (0x3 << GPIO_PUPD2A_H_PUPD_2A0_SHIFT)

#define GPIO_PUPD2A_H_PUPD_2A1_SHIFT            (8)      /* Bits 8-9: Pupd 2A1 */
#define GPIO_PUPD2A_H_PUPD_2A1_MASK             (0x3 << GPIO_PUPD2A_H_PUPD_2A1_SHIFT)

#define GPIO_PUPD2A_H_PUPD_2A2_SHIFT            (16)      /* Bits 16-17: Pupd 2A2 */
#define GPIO_PUPD2A_H_PUPD_2A2_MASK             (0x3 << GPIO_PUPD2A_H_PUPD_2A2_SHIFT)

#define GPIO_PUPD2A_H_PUPD_2A3_SHIFT            (24)      /* Bits 24-25: Pupd 2A3 */
#define GPIO_PUPD2A_H_PUPD_2A3_MASK             (0x3 << GPIO_PUPD2A_H_PUPD_2A3_SHIFT)

/* GPIO PUPD2A_L Register Bit Definitions ****************************/

#define GPIO_PUPD2A_L_PUPD_2A0_SHIFT            (0)      /* Bits 0-1: Pupd 2A0 */
#define GPIO_PUPD2A_L_PUPD_2A0_MASK             (0x3 << GPIO_PUPD2A_L_PUPD_2A0_SHIFT)

#define GPIO_PUPD2A_L_PUPD_2A1_SHIFT            (8)      /* Bits 8-9: Pupd 2A1 */
#define GPIO_PUPD2A_L_PUPD_2A1_MASK             (0x3 << GPIO_PUPD2A_L_PUPD_2A1_SHIFT)

#define GPIO_PUPD2A_L_PUPD_2A2_SHIFT            (16)      /* Bits 16-17: Pupd 2A2 */
#define GPIO_PUPD2A_L_PUPD_2A2_MASK             (0x3 << GPIO_PUPD2A_L_PUPD_2A2_SHIFT)

#define GPIO_PUPD2A_L_PUPD_2A3_SHIFT            (24)      /* Bits 24-25: Pupd 2A3 */
#define GPIO_PUPD2A_L_PUPD_2A3_MASK             (0x3 << GPIO_PUPD2A_L_PUPD_2A3_SHIFT)

/* GPIO PUPD2B_H Register Bit Definitions ****************************/

#define GPIO_PUPD2B_H_PUPD_2B0_SHIFT            (0)      /* Bits 0-1: Pupd 2B0 */
#define GPIO_PUPD2B_H_PUPD_2B0_MASK             (0x3 << GPIO_PUPD2B_H_PUPD_2B0_SHIFT)

#define GPIO_PUPD2B_H_PUPD_2B1_SHIFT            (8)      /* Bits 8-9: Pupd 2B1 */
#define GPIO_PUPD2B_H_PUPD_2B1_MASK             (0x3 << GPIO_PUPD2B_H_PUPD_2B1_SHIFT)

#define GPIO_PUPD2B_H_PUPD_2B2_SHIFT            (16)      /* Bits 16-17: Pupd 2B2 */
#define GPIO_PUPD2B_H_PUPD_2B2_MASK             (0x3 << GPIO_PUPD2B_H_PUPD_2B2_SHIFT)

#define GPIO_PUPD2B_H_PUPD_2B3_SHIFT            (24)      /* Bits 24-25: Pupd 2B3 */
#define GPIO_PUPD2B_H_PUPD_2B3_MASK             (0x3 << GPIO_PUPD2B_H_PUPD_2B3_SHIFT)

/* GPIO PUPD2B_L Register Bit Definitions ****************************/

#define GPIO_PUPD2B_L_PUPD_2B0_SHIFT            (0)      /* Bits 0-1: Pupd 2B0 */
#define GPIO_PUPD2B_L_PUPD_2B0_MASK             (0x3 << GPIO_PUPD2B_L_PUPD_2B0_SHIFT)

#define GPIO_PUPD2B_L_PUPD_2B1_SHIFT            (8)      /* Bits 8-9: Pupd 2B1 */
#define GPIO_PUPD2B_L_PUPD_2B1_MASK             (0x3 << GPIO_PUPD2B_L_PUPD_2B1_SHIFT)

#define GPIO_PUPD2B_L_PUPD_2B2_SHIFT            (16)      /* Bits 16-17: Pupd 2B2 */
#define GPIO_PUPD2B_L_PUPD_2B2_MASK             (0x3 << GPIO_PUPD2B_L_PUPD_2B2_SHIFT)

#define GPIO_PUPD2B_L_PUPD_2B3_SHIFT            (24)      /* Bits 24-25: Pupd 2B3 */
#define GPIO_PUPD2B_L_PUPD_2B3_MASK             (0x3 << GPIO_PUPD2B_L_PUPD_2B3_SHIFT)

/* GPIO PUPD5_H Register Bit Definitions *****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD5_H_PUPD_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD5_H_PUPD_MASK(n)                         (0x3u << GPIO_PUPD5_H_PUPD_SHIFT(n))
#define GPIO_PUPD5_H_PUPD_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_PUPD5_H_PUPD_SHIFT(n))

/* GPIO PUPD5_L Register Bit Definitions *****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD5_L_PUPD_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD5_L_PUPD_MASK(n)                         (0x3u << GPIO_PUPD5_L_PUPD_SHIFT(n))
#define GPIO_PUPD5_L_PUPD_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_PUPD5_L_PUPD_SHIFT(n))

/* GPIO PUPD6_H Register Bit Definitions *****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD6_H_PUPD_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD6_H_PUPD_MASK(n)                         (0x3u << GPIO_PUPD6_H_PUPD_SHIFT(n))
#define GPIO_PUPD6_H_PUPD_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_PUPD6_H_PUPD_SHIFT(n))

/* GPIO PUPD6_L Register Bit Definitions *****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD6_L_PUPD_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD6_L_PUPD_MASK(n)                         (0x3u << GPIO_PUPD6_L_PUPD_SHIFT(n))
#define GPIO_PUPD6_L_PUPD_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_PUPD6_L_PUPD_SHIFT(n))

/* GPIO PUPD7_H Register Bit Definitions *****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD7_H_PUPD_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD7_H_PUPD_MASK(n)                         (0x3u << GPIO_PUPD7_H_PUPD_SHIFT(n))
#define GPIO_PUPD7_H_PUPD_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_PUPD7_H_PUPD_SHIFT(n))

/* GPIO PUPD7_L Register Bit Definitions *****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD7_L_PUPD_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD7_L_PUPD_MASK(n)                         (0x3u << GPIO_PUPD7_L_PUPD_SHIFT(n))
#define GPIO_PUPD7_L_PUPD_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_PUPD7_L_PUPD_SHIFT(n))

/* GPIO PUPD8_H Register Bit Definitions *****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD8_H_PUPD_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD8_H_PUPD_MASK(n)                         (0x3u << GPIO_PUPD8_H_PUPD_SHIFT(n))
#define GPIO_PUPD8_H_PUPD_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_PUPD8_H_PUPD_SHIFT(n))

/* GPIO PUPD8_L Register Bit Definitions *****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD8_L_PUPD_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD8_L_PUPD_MASK(n)                         (0x3u << GPIO_PUPD8_L_PUPD_SHIFT(n))
#define GPIO_PUPD8_L_PUPD_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_PUPD8_L_PUPD_SHIFT(n))

/* GPIO PUPD9_H Register Bit Definitions *****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD9_H_PUPD_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD9_H_PUPD_MASK(n)                         (0x3u << GPIO_PUPD9_H_PUPD_SHIFT(n))
#define GPIO_PUPD9_H_PUPD_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_PUPD9_H_PUPD_SHIFT(n))

/* GPIO PUPD9_L Register Bit Definitions *****************************/

/* PUPD_ fields (parameterized for indices 0-3) */
#define GPIO_PUPD9_L_PUPD_SHIFT(n)                        ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPDn */
#define GPIO_PUPD9_L_PUPD_MASK(n)                         (0x3u << GPIO_PUPD9_L_PUPD_SHIFT(n))
#define GPIO_PUPD9_L_PUPD_VAL(n,v)                        (((unsigned)(v) & 0x3u) << GPIO_PUPD9_L_PUPD_SHIFT(n))

/* GPIO PUPDA_H Register Bit Definitions *****************************/

/* PUPD_A_ fields (parameterized for indices 0-3) */
#define GPIO_PUPDA_H_PUPD_A_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPD_An */
#define GPIO_PUPDA_H_PUPD_A_MASK(n)                       (0x3u << GPIO_PUPDA_H_PUPD_A_SHIFT(n))
#define GPIO_PUPDA_H_PUPD_A_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_PUPDA_H_PUPD_A_SHIFT(n))

/* GPIO PUPDA_L Register Bit Definitions *****************************/

/* PUPD_A_ fields (parameterized for indices 0-3) */
#define GPIO_PUPDA_L_PUPD_A_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPD_An */
#define GPIO_PUPDA_L_PUPD_A_MASK(n)                       (0x3u << GPIO_PUPDA_L_PUPD_A_SHIFT(n))
#define GPIO_PUPDA_L_PUPD_A_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_PUPDA_L_PUPD_A_SHIFT(n))

/* GPIO PUPDB_H Register Bit Definitions *****************************/

/* PUPD_B_ fields (parameterized for indices 0-3) */
#define GPIO_PUPDB_H_PUPD_B_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPD_Bn */
#define GPIO_PUPDB_H_PUPD_B_MASK(n)                       (0x3u << GPIO_PUPDB_H_PUPD_B_SHIFT(n))
#define GPIO_PUPDB_H_PUPD_B_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_PUPDB_H_PUPD_B_SHIFT(n))

/* GPIO PUPDB_L Register Bit Definitions *****************************/

/* PUPD_B_ fields (parameterized for indices 0-3) */
#define GPIO_PUPDB_L_PUPD_B_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPD_Bn */
#define GPIO_PUPDB_L_PUPD_B_MASK(n)                       (0x3u << GPIO_PUPDB_L_PUPD_B_SHIFT(n))
#define GPIO_PUPDB_L_PUPD_B_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_PUPDB_L_PUPD_B_SHIFT(n))

/* GPIO PUPDC_H Register Bit Definitions *****************************/

/* PUPD_C_ fields (parameterized for indices 0-3) */
#define GPIO_PUPDC_H_PUPD_C_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPD_Cn */
#define GPIO_PUPDC_H_PUPD_C_MASK(n)                       (0x3u << GPIO_PUPDC_H_PUPD_C_SHIFT(n))
#define GPIO_PUPDC_H_PUPD_C_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_PUPDC_H_PUPD_C_SHIFT(n))

/* GPIO PUPDC_L Register Bit Definitions *****************************/

/* PUPD_C_ fields (parameterized for indices 0-3) */
#define GPIO_PUPDC_L_PUPD_C_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPD_Cn */
#define GPIO_PUPDC_L_PUPD_C_MASK(n)                       (0x3u << GPIO_PUPDC_L_PUPD_C_SHIFT(n))
#define GPIO_PUPDC_L_PUPD_C_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_PUPDC_L_PUPD_C_SHIFT(n))

/* GPIO PUPDF_H Register Bit Definitions *****************************/

/* PUPD_F_ fields (parameterized for indices 0-3) */
#define GPIO_PUPDF_H_PUPD_F_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPD_Fn */
#define GPIO_PUPDF_H_PUPD_F_MASK(n)                       (0x3u << GPIO_PUPDF_H_PUPD_F_SHIFT(n))
#define GPIO_PUPDF_H_PUPD_F_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_PUPDF_H_PUPD_F_SHIFT(n))

/* GPIO PUPDF_L Register Bit Definitions *****************************/

/* PUPD_F_ fields (parameterized for indices 0-3) */
#define GPIO_PUPDF_L_PUPD_F_SHIFT(n)                      ((unsigned)(0 + ((n) * 8)))  /* Bits for PUPD_Fn */
#define GPIO_PUPDF_L_PUPD_F_MASK(n)                       (0x3u << GPIO_PUPDF_L_PUPD_F_SHIFT(n))
#define GPIO_PUPDF_L_PUPD_F_VAL(n,v)                      (((unsigned)(v) & 0x3u) << GPIO_PUPDF_L_PUPD_F_SHIFT(n))

/* GPIO PWPR Register Bit Definitions ********************************/

#define GPIO_PWPR_REGWE_B                       (1 << 5)  /* Regwe B */

#define GPIO_PWPR_REGWE_A                       (1 << 6)  /* Regwe A */

/* GPIO SMT20_H Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT20_H_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 200 */

/* GPIO SMT20_L Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT20_L_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 200 */

/* GPIO SMT21_H Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT21_H_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 210 */

/* GPIO SMT21_L Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT21_L_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 210 */

/* GPIO SMT23_H Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT23_H_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 230 */

/* GPIO SMT23_L Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT23_L_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 230 */

/* GPIO SMT24_H Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT24_H_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 240 */

/* GPIO SMT24_L Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT24_L_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 240 */

/* GPIO SMT25_H Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT25_H_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 250 */

/* GPIO SMT25_L Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT25_L_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 250 */

/* GPIO SMT26_H Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT26_H_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 260 */

/* GPIO SMT26_L Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT26_L_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 260 */

/* GPIO SMT27_H Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT27_H_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 270 */

/* GPIO SMT27_L Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT27_L_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 270 */

/* GPIO SMT28_H Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT28_H_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 280 */

/* GPIO SMT28_L Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT28_L_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 280 */

/* GPIO SMT29_H Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT29_H_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 290 */

/* GPIO SMT29_L Register Bit Definitions *****************************/

/* SMT_ fields (parameterized for indices 0-3) */
#define GPIO_SMT29_L_SMT(n)                               (1u << (0 + ((unsigned)(n) * 8)))  /* Smt 290 */

/* GPIO SMT2A_H Register Bit Definitions *****************************/

#define GPIO_SMT2A_H_SMT_2A0                    (1 << 0)  /* Smt 2A0 */

#define GPIO_SMT2A_H_SMT_2A1                    (1 << 8)  /* Smt 2A1 */

#define GPIO_SMT2A_H_SMT_2A2                    (1 << 16)  /* Smt 2A2 */

#define GPIO_SMT2A_H_SMT_2A3                    (1 << 24)  /* Smt 2A3 */

/* GPIO SMT2A_L Register Bit Definitions *****************************/

#define GPIO_SMT2A_L_SMT_2A0                    (1 << 0)  /* Smt 2A0 */

#define GPIO_SMT2A_L_SMT_2A1                    (1 << 8)  /* Smt 2A1 */

#define GPIO_SMT2A_L_SMT_2A2                    (1 << 16)  /* Smt 2A2 */

#define GPIO_SMT2A_L_SMT_2A3                    (1 << 24)  /* Smt 2A3 */

/* GPIO SMT2B_H Register Bit Definitions *****************************/

#define GPIO_SMT2B_H_SMT_2B0                    (1 << 0)  /* Smt 2B0 */

#define GPIO_SMT2B_H_SMT_2B1                    (1 << 8)  /* Smt 2B1 */

#define GPIO_SMT2B_H_SMT_2B2                    (1 << 16)  /* Smt 2B2 */

#define GPIO_SMT2B_H_SMT_2B3                    (1 << 24)  /* Smt 2B3 */

/* GPIO SMT2B_L Register Bit Definitions *****************************/

#define GPIO_SMT2B_L_SMT_2B0                    (1 << 0)  /* Smt 2B0 */

#define GPIO_SMT2B_L_SMT_2B1                    (1 << 8)  /* Smt 2B1 */

#define GPIO_SMT2B_L_SMT_2B2                    (1 << 16)  /* Smt 2B2 */

#define GPIO_SMT2B_L_SMT_2B3                    (1 << 24)  /* Smt 2B3 */

/* GPIO SR10_H Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR10_H_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 100 */

/* GPIO SR10_L Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR10_L_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 100 */

/* GPIO SR11_H Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR11_H_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 110 */

/* GPIO SR11_L Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR11_L_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 110 */

/* GPIO SR12_H Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR12_H_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 120 */

/* GPIO SR12_L Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR12_L_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 120 */

/* GPIO SR13_H Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR13_H_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 130 */

/* GPIO SR13_L Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR13_L_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 130 */

/* GPIO SR14_H Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR14_H_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 140 */

/* GPIO SR14_L Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR14_L_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 140 */

/* GPIO SR20_H Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR20_H_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 200 */

/* GPIO SR20_L Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR20_L_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 200 */

/* GPIO SR21_H Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR21_H_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 210 */

/* GPIO SR21_L Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR21_L_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 210 */

/* GPIO SR23_H Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR23_H_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 230 */

/* GPIO SR23_L Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR23_L_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 230 */

/* GPIO SR24_H Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR24_H_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 240 */

/* GPIO SR24_L Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR24_L_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 240 */

/* GPIO SR25_H Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR25_H_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 250 */

/* GPIO SR25_L Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR25_L_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 250 */

/* GPIO SR26_H Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR26_H_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 260 */

/* GPIO SR26_L Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR26_L_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 260 */

/* GPIO SR27_H Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR27_H_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 270 */

/* GPIO SR27_L Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR27_L_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 270 */

/* GPIO SR28_H Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR28_H_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 280 */

/* GPIO SR28_L Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR28_L_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 280 */

/* GPIO SR29_H Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR29_H_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 290 */

/* GPIO SR29_L Register Bit Definitions ******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR29_L_SR(n)                                 (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 290 */

/* GPIO SR2A_H Register Bit Definitions ******************************/

#define GPIO_SR2A_H_SR_2A0                      (1 << 0)  /* Sr 2A0 */

#define GPIO_SR2A_H_SR_2A1                      (1 << 8)  /* Sr 2A1 */

#define GPIO_SR2A_H_SR_2A2                      (1 << 16)  /* Sr 2A2 */

#define GPIO_SR2A_H_SR_2A3                      (1 << 24)  /* Sr 2A3 */

/* GPIO SR2A_L Register Bit Definitions ******************************/

#define GPIO_SR2A_L_SR_2A0                      (1 << 0)  /* Sr 2A0 */

#define GPIO_SR2A_L_SR_2A1                      (1 << 8)  /* Sr 2A1 */

#define GPIO_SR2A_L_SR_2A2                      (1 << 16)  /* Sr 2A2 */

#define GPIO_SR2A_L_SR_2A3                      (1 << 24)  /* Sr 2A3 */

/* GPIO SR2B_H Register Bit Definitions ******************************/

#define GPIO_SR2B_H_SR_2B0                      (1 << 0)  /* Sr 2B0 */

#define GPIO_SR2B_H_SR_2B1                      (1 << 8)  /* Sr 2B1 */

#define GPIO_SR2B_H_SR_2B2                      (1 << 16)  /* Sr 2B2 */

#define GPIO_SR2B_H_SR_2B3                      (1 << 24)  /* Sr 2B3 */

/* GPIO SR2B_L Register Bit Definitions ******************************/

#define GPIO_SR2B_L_SR_2B0                      (1 << 0)  /* Sr 2B0 */

#define GPIO_SR2B_L_SR_2B1                      (1 << 8)  /* Sr 2B1 */

#define GPIO_SR2B_L_SR_2B2                      (1 << 16)  /* Sr 2B2 */

#define GPIO_SR2B_L_SR_2B3                      (1 << 24)  /* Sr 2B3 */

/* GPIO SR3_H Register Bit Definitions *******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR3_H_SR(n)                                  (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 30 */

/* GPIO SR3_L Register Bit Definitions *******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR3_L_SR(n)                                  (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 30 */

/* GPIO SR5_H Register Bit Definitions *******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR5_H_SR(n)                                  (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 50 */

/* GPIO SR5_L Register Bit Definitions *******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR5_L_SR(n)                                  (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 50 */

/* GPIO SR6_H Register Bit Definitions *******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR6_H_SR(n)                                  (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 60 */

/* GPIO SR6_L Register Bit Definitions *******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR6_L_SR(n)                                  (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 60 */

/* GPIO SR7_H Register Bit Definitions *******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR7_H_SR(n)                                  (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 70 */

/* GPIO SR7_L Register Bit Definitions *******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR7_L_SR(n)                                  (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 70 */

/* GPIO SR8_H Register Bit Definitions *******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR8_H_SR(n)                                  (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 80 */

/* GPIO SR8_L Register Bit Definitions *******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR8_L_SR(n)                                  (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 80 */

/* GPIO SR9_H Register Bit Definitions *******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR9_H_SR(n)                                  (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 90 */

/* GPIO SR9_L Register Bit Definitions *******************************/

/* SR_ fields (parameterized for indices 0-3) */
#define GPIO_SR9_L_SR(n)                                  (1u << (0 + ((unsigned)(n) * 8)))  /* Sr 90 */

/* GPIO SRA_H Register Bit Definitions *******************************/

/* SR_A_ fields (parameterized for indices 0-3) */
#define GPIO_SRA_H_SR_A(n)                                (1u << (0 + ((unsigned)(n) * 8)))  /* Sr A0 */

/* GPIO SRA_L Register Bit Definitions *******************************/

/* SR_A_ fields (parameterized for indices 0-3) */
#define GPIO_SRA_L_SR_A(n)                                (1u << (0 + ((unsigned)(n) * 8)))  /* Sr A0 */

/* GPIO SRB_H Register Bit Definitions *******************************/

/* SR_B_ fields (parameterized for indices 0-3) */
#define GPIO_SRB_H_SR_B(n)                                (1u << (0 + ((unsigned)(n) * 8)))  /* Sr B0 */

/* GPIO SRB_L Register Bit Definitions *******************************/

/* SR_B_ fields (parameterized for indices 0-3) */
#define GPIO_SRB_L_SR_B(n)                                (1u << (0 + ((unsigned)(n) * 8)))  /* Sr B0 */

/* GPIO SRC_H Register Bit Definitions *******************************/

/* SR_C_ fields (parameterized for indices 0-3) */
#define GPIO_SRC_H_SR_C(n)                                (1u << (0 + ((unsigned)(n) * 8)))  /* Sr C0 */

/* GPIO SRC_L Register Bit Definitions *******************************/

/* SR_C_ fields (parameterized for indices 0-3) */
#define GPIO_SRC_L_SR_C(n)                                (1u << (0 + ((unsigned)(n) * 8)))  /* Sr C0 */

/* GPIO SRE_H Register Bit Definitions *******************************/

/* SR_E_ fields (parameterized for indices 0-3) */
#define GPIO_SRE_H_SR_E(n)                                (1u << (0 + ((unsigned)(n) * 8)))  /* Sr E0 */

/* GPIO SRE_L Register Bit Definitions *******************************/

/* SR_E_ fields (parameterized for indices 0-3) */
#define GPIO_SRE_L_SR_E(n)                                (1u << (0 + ((unsigned)(n) * 8)))  /* Sr E0 */

/* GPIO SRF_H Register Bit Definitions *******************************/

/* SR_F_ fields (parameterized for indices 0-3) */
#define GPIO_SRF_H_SR_F(n)                                (1u << (0 + ((unsigned)(n) * 8)))  /* Sr F0 */

/* GPIO SRF_L Register Bit Definitions *******************************/

/* SR_F_ fields (parameterized for indices 0-3) */
#define GPIO_SRF_L_SR_F(n)                                (1u << (0 + ((unsigned)(n) * 8)))  /* Sr F0 */

/* GPIO Channel definitions */
#define RZV_GPIO_CHANNEL_0         0

/* Maximum number of GPIO channels */
#define RZV_GPIO_MAX_CHANNELS      1

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_GPIO_H */

/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_icu.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ICU_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ICU_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ICU Base Address */
#ifndef R_ICU_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_ICU_BASE           0x4000c000
#else
#define R_ICU_BASE           0x5000c000
#endif
#endif

/* ICU Register Offsets */

#define R_ICU_NMIER_OFFSET                        0x00000100  /* Non-Maskable Interrupt Enable Register */
#define R_ICU_NMICLR_OFFSET                       0x00000110  /* Non-Maskable Interrupt Status Clear Register */
#define R_ICU_NMISR_OFFSET                        0x00000120  /* Non-Maskable Interrupt Status Register */
#define R_ICU_WUPEN0_OFFSET                       0x000001a0  /* Wake Up Interrupt Enable Register 0 */
#define R_ICU_WUPEN1_OFFSET                       0x000001a4  /* Wake Up Interrupt Enable Register 1 */
#define R_ICU_DSLPWUPIRQEN0_OFFSET                0x00000214  /* Deep Sleep Wake Up IRQ Enable Register 0 */
#define R_ICU_DSLPWUPIRQEN1_OFFSET                0x00000218  /* Deep Sleep Wake Up IRQ Enable Register 1 */
#define R_ICU_DSLPWUPIRQEN2_OFFSET                0x0000021c  /* Deep Sleep Wake Up IRQ Enable Register 2 */
#define R_ICU_DELSRM_OFFSET                       0x00000280  /* DMAC Event Link Setting Register m (m = 0 to 7) */
/* IELSR%s Registers (0-95) */
#define R_ICU_IELSR_OFFSET(m)                     (0x00000300 + ((m) * 0x00000004))  /* Interrupt Controller Unit Event Link Setting Register %s */

/* ICU Register Addresses */

#define R_ICU_NMIER                               (R_ICU_BASE + R_ICU_NMIER_OFFSET)
#define R_ICU_NMICLR                              (R_ICU_BASE + R_ICU_NMICLR_OFFSET)
#define R_ICU_NMISR                               (R_ICU_BASE + R_ICU_NMISR_OFFSET)
#define R_ICU_WUPEN0                              (R_ICU_BASE + R_ICU_WUPEN0_OFFSET)
#define R_ICU_WUPEN1                              (R_ICU_BASE + R_ICU_WUPEN1_OFFSET)
#define R_ICU_DSLPWUPIRQEN0                       (R_ICU_BASE + R_ICU_DSLPWUPIRQEN0_OFFSET)
#define R_ICU_DSLPWUPIRQEN1                       (R_ICU_BASE + R_ICU_DSLPWUPIRQEN1_OFFSET)
#define R_ICU_DSLPWUPIRQEN2                       (R_ICU_BASE + R_ICU_DSLPWUPIRQEN2_OFFSET)
#define R_ICU_DELSRM                              (R_ICU_BASE + R_ICU_DELSRM_OFFSET)
#define R_ICU_IELSR(m)                            (R_ICU_BASE + R_ICU_IELSR_OFFSET(m))

/* Register bit definitions */
/* NMIER Register bit definitions */
#define R_ICU_NMIER_IWDTEN                        (1 << 0)  /* IWDT Underflow/Refresh Error Interrupt Enable */

#define R_ICU_NMIER_WDTEN                         (1 << 1)  /* WDT Underflow/Refresh Error Interrupt Enable */

#define R_ICU_NMIER_PVD1EN                        (1 << 2)  /* Voltage monitor 1 Interrupt Enable */

#define R_ICU_NMIER_PVD2EN                        (1 << 3)  /* Voltage monitor 2 Interrupt Enable */

#define R_ICU_NMIER_SOSTEN                        (1 << 5)  /* Sub Oscillation Stop Detection Interrupt Enable */

#define R_ICU_NMIER_OSTEN                         (1 << 6)  /* Oscillation Stop Detection Interrupt Enable */

#define R_ICU_NMIER_NMIEN                         (1 << 7)  /* NMI Pin Interrupt Enable */

#define R_ICU_NMIER_BUSEN                         (1 << 12)  /*  */

#define R_ICU_NMIER_CMEN                          (1 << 13)  /*  */

#define R_ICU_NMIER_LMEN                          (1 << 14)  /* Local Memory Error Interrupt Enable */

#define R_ICU_NMIER_LUEN                          (1 << 15)  /*  */

#define R_ICU_NMIER_FPUEXCEN                      (1 << 16)  /* FPU Exception Interrupt Enable */

#define R_ICU_NMIER_MRCRDEN                       (1 << 17)  /* MRAM MRC read Error Interrupt Enable */

#define R_ICU_NMIER_MRERDEN                       (1 << 18)  /* MRAM MRE read Error Interrupt Enable */

#define R_ICU_NMIER_IPCEN                         (1 << 20)  /* IPC NMI CPU mutual Interrupt Enable */

#define R_ICU_NMIER_FPUFLTEN                      (1 << 16)  /* FPU FAULT Interrupt Enable */

/* NMICLR Register bit definitions */
#define R_ICU_NMICLR_IWDTCLR                      (1 << 0)  /* IWDT Underflow/Refresh Error Interrupt Status Flag Clear */

#define R_ICU_NMICLR_WDTCLR                       (1 << 1)  /* WDT Underflow/Refresh Error Interrupt Status Flag Clear */

#define R_ICU_NMICLR_PVD1CLR                      (1 << 2)  /* Voltage Monitor 1 Interrupt Status Flag Clear */

#define R_ICU_NMICLR_PVD2CLR                      (1 << 3)  /* Voltage Monitor 2 Interrupt Status Flag Clear */

#define R_ICU_NMICLR_SOSTCLR                      (1 << 5)  /* Oscillation Stop Detection Interrupt Status Flag Clear */

#define R_ICU_NMICLR_OSTCLR                       (1 << 6)  /* Oscillation Stop Detection Interrupt Status Flag Clear */

#define R_ICU_NMICLR_NMICLR                       (1 << 7)  /* NMI Pin Interrupt Status Flag Clear */

#define R_ICU_NMICLR_BUSCLR                       (1 << 12)  /*  */

#define R_ICU_NMICLR_CMCLR                        (1 << 13)  /*  */

#define R_ICU_NMICLR_LMCLR                        (1 << 14)  /*  */

#define R_ICU_NMICLR_LUCLR                        (1 << 15)  /*  */

#define R_ICU_NMICLR_FPUEXCCLR                    (1 << 16)  /* FPU Exception Interrupt Status Flag Clear */

#define R_ICU_NMICLR_MRCRDCLR                     (1 << 17)  /* MRAM MRC read Error Interrupt Status Flag Clear */

#define R_ICU_NMICLR_MRERDCLR                     (1 << 18)  /* MRAM MRE read Error Interrupt Status Flag Clear */

#define R_ICU_NMICLR_IPCCLR                       (1 << 20)  /* IPC NMI CPU mutual Interrupt Status Flag Clear */

#define R_ICU_NMICLR_FPUFLTCLR                    (1 << 16)  /* FPU FAULT Clear */

/* NMISR Register bit definitions */
#define R_ICU_NMISR_IWDTST                        (1 << 0)  /* IWDT Underflow/Refresh Error Interrupt Status Flag */

#define R_ICU_NMISR_WDTST                         (1 << 1)  /* WDT Underflow/Refresh Error Interrupt Status Flag */

#define R_ICU_NMISR_PVD1ST                        (1 << 2)  /* Voltage Monitor 1 Interrupt Status Flag */

#define R_ICU_NMISR_PVD2ST                        (1 << 3)  /* Voltage Monitor 2 Interrupt Status Flag */

#define R_ICU_NMISR_SOSTST                        (1 << 5)  /* Sub Oscillation Stop Detection Interrupt Status Flag */

#define R_ICU_NMISR_OSTST                         (1 << 6)  /* Main Clock Oscillation Stop Detection Interrupt Status Flag */

#define R_ICU_NMISR_NMIST                         (1 << 7)  /* NMI Pin Interrupt Status Flag */

#define R_ICU_NMISR_BUSST                         (1 << 12)  /* Bus Error Interrupt Status Flag */

#define R_ICU_NMISR_CMST                          (1 << 13)  /*  */

#define R_ICU_NMISR_LMST                          (1 << 14)  /*  */

#define R_ICU_NMISR_LUST                          (1 << 15)  /*  */

#define R_ICU_NMISR_FPUEXCST                      (1 << 16)  /*  */

#define R_ICU_NMISR_MRCRDST                       (1 << 17)  /*  */

#define R_ICU_NMISR_MRERDST                       (1 << 18)  /*  */

#define R_ICU_NMISR_IPCST                         (1 << 20)  /*  */

#define R_ICU_NMISR_FPUFLTST                      (1 << 16)  /* FPU FAULT Interrupt Status Flag */

/* WUPEN0 Register bit definitions */
#define R_ICU_WUPEN0_IRQWUPEN0                    (1 << 0)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN1                    (1 << 1)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN2                    (1 << 2)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN3                    (1 << 3)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN4                    (1 << 4)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN5                    (1 << 5)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN6                    (1 << 6)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN7                    (1 << 7)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN8                    (1 << 8)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN9                    (1 << 9)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN10                   (1 << 10)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN11                   (1 << 11)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN12                   (1 << 12)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN13                   (1 << 13)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN14                   (1 << 14)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN15                   (1 << 15)  /*  */

#define R_ICU_WUPEN0_IWDTWUPEN                    (1 << 16)  /* IWDT Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_PVD1WUPEN                    (1 << 18)  /* PVD1 Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_PVD2WUPEN                    (1 << 19)  /* PVD2 Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_VBATTWUPEN                   (1 << 20)  /* VBATT Monitor Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_RTCALMWUPEN                  (1 << 24)  /* RTC Alarm Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_RTCPRDWUPEN                  (1 << 25)  /* RTC Period Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_USBHSWUPEN                   (1 << 26)  /* USBHS Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_USBFS0WUPEN                  (1 << 27)  /* USBFS Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_AGT1UDWUPEN                  (1 << 28)  /* AGT1 Underflow Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_AGT1CAWUPEN                  (1 << 29)  /* AGT1 Compare Match A Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_AGT1CBWUPEN                  (1 << 30)  /* AGT1 Compare Match B Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_RIIC0WUPEN                   (1 << 31)  /* RIIC0 Address Match Interrupt Software Standby Mode Returns Enable bit */

/* WUPEN1 Register bit definitions */
#define R_ICU_WUPEN1_COMPHS0WUPEN                 (1 << 3)  /* Comparator-HS0 Interrupt Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_SOSCWUPEN                    (1 << 7)  /* Sub Oscillation Stop Detection Interrupt Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_ULP0UWUPEN                   (1 << 8)  /* ULPT0 Underflow Interrupt Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_ULP0AWUPEN                   (1 << 9)  /* ULPT0 Compare Match A Interrupt Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_ULP0BWUPEN                   (1 << 10)  /* ULPT0 Compare Match B Interrupt Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_I3CWUPEN                     (1 << 11)  /* I3C Wakeup Condition Detection Interrupt Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_ULP1UWUPEN                   (1 << 12)  /* ULPT1 Underflow Interrupt Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_ULP1AWUPEN                   (1 << 13)  /* ULPT1 Compare Match A Interrupt Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_ULP1BWUPEN                   (1 << 14)  /* ULPT1 Compare Match B Interrupt Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_PDMWUPEN                     (1 << 15)  /* PDMIF Sound Detection Interrupt Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN16                   (1 << 16)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN17                   (1 << 17)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN18                   (1 << 18)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN19                   (1 << 19)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN20                   (1 << 20)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN21                   (1 << 21)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN22                   (1 << 22)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN23                   (1 << 23)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN24                   (1 << 24)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN25                   (1 << 25)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN26                   (1 << 26)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN27                   (1 << 27)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN28                   (1 << 28)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN29                   (1 << 29)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN30                   (1 << 30)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN31                   (1 << 31)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_WUPEN16                      (1 << 0)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 16 */

#define R_ICU_WUPEN1_WUPEN17                      (1 << 1)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 17 */

#define R_ICU_WUPEN1_WUPEN18                      (1 << 2)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 18 */

#define R_ICU_WUPEN1_WUPEN19                      (1 << 3)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 19 */

#define R_ICU_WUPEN1_WUPEN20                      (1 << 4)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 20 */

#define R_ICU_WUPEN1_WUPEN21                      (1 << 5)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 21 */

#define R_ICU_WUPEN1_WUPEN22                      (1 << 6)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 22 */

#define R_ICU_WUPEN1_WUPEN23                      (1 << 7)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 23 */

#define R_ICU_WUPEN1_WUPEN24                      (1 << 8)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 24 */

#define R_ICU_WUPEN1_WUPEN25                      (1 << 9)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 25 */

#define R_ICU_WUPEN1_WUPEN26                      (1 << 10)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 26 */

#define R_ICU_WUPEN1_WUPEN27                      (1 << 11)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 27 */

#define R_ICU_WUPEN1_WUPEN28                      (1 << 12)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 28 */

#define R_ICU_WUPEN1_WUPEN29                      (1 << 13)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 29 */

#define R_ICU_WUPEN1_WUPEN30                      (1 << 14)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 30 */

#define R_ICU_WUPEN1_WUPEN31                      (1 << 15)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 31 */

/* DSLPWUPIRQEN0 Register bit definitions */
#define R_ICU_DSLPWUPIRQEN0_IRQ00                 (1 << 0)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ01                 (1 << 1)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ02                 (1 << 2)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ03                 (1 << 3)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ04                 (1 << 4)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ05                 (1 << 5)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ06                 (1 << 6)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ07                 (1 << 7)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ08                 (1 << 8)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ09                 (1 << 9)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ10                 (1 << 10)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ11                 (1 << 11)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ12                 (1 << 12)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ13                 (1 << 13)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ14                 (1 << 14)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ15                 (1 << 15)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ16                 (1 << 16)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ17                 (1 << 17)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ18                 (1 << 18)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ19                 (1 << 19)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ20                 (1 << 20)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ21                 (1 << 21)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ22                 (1 << 22)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ23                 (1 << 23)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ24                 (1 << 24)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ25                 (1 << 25)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ26                 (1 << 26)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ27                 (1 << 27)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ28                 (1 << 28)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ29                 (1 << 29)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ30                 (1 << 30)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ31                 (1 << 31)  /* IRQ Deep Sleep Returns Enable bit. */

/* DSLPWUPIRQEN1 Register bit definitions */
#define R_ICU_DSLPWUPIRQEN1_IRQ32                 (1 << 0)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ33                 (1 << 1)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ34                 (1 << 2)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ35                 (1 << 3)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ36                 (1 << 4)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ37                 (1 << 5)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ38                 (1 << 6)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ39                 (1 << 7)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ40                 (1 << 8)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ41                 (1 << 9)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ42                 (1 << 10)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ43                 (1 << 11)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ44                 (1 << 12)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ45                 (1 << 13)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ46                 (1 << 14)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ47                 (1 << 15)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ48                 (1 << 16)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ49                 (1 << 17)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ50                 (1 << 18)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ51                 (1 << 19)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ52                 (1 << 20)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ53                 (1 << 21)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ54                 (1 << 22)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ55                 (1 << 23)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ56                 (1 << 24)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ57                 (1 << 25)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ58                 (1 << 26)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ59                 (1 << 27)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ60                 (1 << 28)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ61                 (1 << 29)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ62                 (1 << 30)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ63                 (1 << 31)  /* IRQ Deep Sleep Returns Enable bit. */

/* DSLPWUPIRQEN2 Register bit definitions */
#define R_ICU_DSLPWUPIRQEN2_IRQ64                 (1 << 0)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ65                 (1 << 1)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ66                 (1 << 2)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ67                 (1 << 3)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ68                 (1 << 4)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ69                 (1 << 5)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ70                 (1 << 6)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ71                 (1 << 7)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ72                 (1 << 8)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ73                 (1 << 9)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ74                 (1 << 10)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ75                 (1 << 11)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ76                 (1 << 12)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ77                 (1 << 13)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ78                 (1 << 14)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ79                 (1 << 15)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ80                 (1 << 16)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ81                 (1 << 17)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ82                 (1 << 18)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ83                 (1 << 19)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ84                 (1 << 20)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ85                 (1 << 21)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ86                 (1 << 22)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ87                 (1 << 23)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ88                 (1 << 24)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ89                 (1 << 25)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ90                 (1 << 26)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ91                 (1 << 27)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ92                 (1 << 28)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ93                 (1 << 29)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ94                 (1 << 30)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ95                 (1 << 31)  /* IRQ Deep Sleep Returns Enable bit. */

/* DELSRM Register bit definitions */
#define R_ICU_DELSRM_DELS_SHIFT                   (0)  /* DMAC Event Link Select */
#define R_ICU_DELSRM_DELS_MASK                    0x3ff
#  define R_ICU_DELSRM_DELS_0X00                          (0 << R_ICU_DELSRM_DELS_SHIFT)  /* Disable interrupts to the associated DMAC module */

#define R_ICU_DELSRM_IR                           (1 << 16)  /* DMAC Activation Request Status flag */

/* IELSR Register bit definitions */
#define R_ICU_IELSR_IELS_SHIFT                    (0)  /* ICU Event Link Select */
#define R_ICU_IELSR_IELS_MASK                     0x3ff

#define R_ICU_IELSR_IR                            (1 << 16)  /* Interrupt Status Flag */

#define R_ICU_IELSR_DTCE                          (1 << 24)  /* DTC Activation Enable */


/* Maximum number of channels */

#define ICU_MAX_CHANNELS    96

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ICU_H */

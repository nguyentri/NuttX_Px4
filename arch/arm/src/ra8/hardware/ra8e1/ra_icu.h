/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8e1/ra_icu.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_ICU_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_ICU_H

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

#define R_ICU_IRQCR_OFFSET                        0x00000000  /* IRQ Control Register (8-bits) */
#define R_ICU_NMIER_OFFSET                        0x00000100  /* Non-Maskable Interrupt Enable Register */
#define R_ICU_NMICLR_OFFSET                       0x00000110  /* Non-Maskable Interrupt Status Clear Register */
#define R_ICU_NMISR_OFFSET                        0x00000120  /* Non-Maskable Interrupt Status Register */
#define R_ICU_WUPEN0_OFFSET                       0x000001a0  /* Wake Up Interrupt Enable Register 0 */
#define R_ICU_WUPEN1_OFFSET                       0x000001a4  /* Wake Up interrupt enable register 1 */
/* IELSR%s Registers (0-95) */
#define R_ICU_IELSR_OFFSET(m)                     (0x00000300 + ((m) * 0x00000004))  /* ICU Event Link Setting Register %s */
/* DELSR[%s] Registers () */
#define R_ICU_DELSR_OFFSET(m)                     (0x00006280 + ((m) * 0x00000004))  /* DMAC Event Link Setting Registers */

/* ICU Register Addresses */

#define R_ICU_IRQCR(m)                            (R_ICU_BASE + R_ICU_IRQCR_OFFSET + ((m) * 0x00000001))
#define R_ICU_NMIER                               (R_ICU_BASE + R_ICU_NMIER_OFFSET)
#define R_ICU_NMICLR                              (R_ICU_BASE + R_ICU_NMICLR_OFFSET)
#define R_ICU_NMISR                               (R_ICU_BASE + R_ICU_NMISR_OFFSET)
#define R_ICU_WUPEN0                              (R_ICU_BASE + R_ICU_WUPEN0_OFFSET)
#define R_ICU_WUPEN1                              (R_ICU_BASE + R_ICU_WUPEN1_OFFSET)
#define R_ICU_IELSR(m)                            (R_ICU_BASE + R_ICU_IELSR_OFFSET(m))
#define R_ICU_DELSR(m)                            (R_ICU_BASE + R_ICU_DELSR_OFFSET(m))

/* Register bit definitions */
/* IRQCR Register bit definitions */
#define R_ICU_IRQCR_FLTEN                         (1 << 7)  /* IRQ Digital Filter Enable */
#define R_ICU_IRQCR_FCLKSEL_SHIFT                 (4)       /* IRQ Digital Filter Sampling Clock Select */
#define R_ICU_IRQCR_FCLKSEL_MASK                  (0x03)
#define R_ICU_IRQCR_IRQMD_SHIFT                   (0)       /* IRQ Detection Sense Select */
#define R_ICU_IRQCR_IRQMD_MASK                    (0x03)

/* NMIER Register bit definitions */
#define R_ICU_NMIER_IWDTEN                        (1 << 0)  /* IWDT Underflow/Refresh Error Interrupt Enable */

#define R_ICU_NMIER_WDTEN                         (1 << 1)  /* WDT Underflow/Refresh Error Interrupt Enable */

#define R_ICU_NMIER_PVD1EN                        (1 << 2)  /* Voltage monitor 1 Interrupt Enable */

#define R_ICU_NMIER_PVD2EN                        (1 << 3)  /* Voltage monitor 2 Interrupt Enable */

#define R_ICU_NMIER_OSTEN                         (1 << 6)  /* Main Clock Oscillation Stop Detection Interrupt Enable */

#define R_ICU_NMIER_NMIEN                         (1 << 7)  /* NMI Pin Interrupt Enable */

#define R_ICU_NMIER_BUSEN                         (1 << 12)  /*  */

#define R_ICU_NMIER_CMEN                          (1 << 13)  /*  */

#define R_ICU_NMIER_LUEN                          (1 << 15)  /*  */

#define R_ICU_NMIER_LVD1EN                        (1 << 2)  /* Voltage-Monitoring 1 Interrupt Enable */

#define R_ICU_NMIER_LVD2EN                        (1 << 3)  /* Voltage-Monitoring 2 Interrupt Enable */

/* NMICLR Register bit definitions */
#define R_ICU_NMICLR_IWDTCLR                      (1 << 0)  /* IWDT Underflow/Refresh Error Interrupt Status Flag Clear */

#define R_ICU_NMICLR_WDTCLR                       (1 << 1)  /* WDT Underflow/Refresh Error Interrupt Status Flag Clear */

#define R_ICU_NMICLR_PVD1CLR                      (1 << 2)  /* Voltage Monitor 1 Interrupt Status Flag Clear */

#define R_ICU_NMICLR_PVD2CLR                      (1 << 3)  /* Voltage Monitor 2 Interrupt Status Flag Clear */

#define R_ICU_NMICLR_OSTCLR                       (1 << 6)  /* Oscillation Stop Detection Interrupt Status Flag Clear */

#define R_ICU_NMICLR_NMICLR                       (1 << 7)  /* NMI Pin Interrupt Status Flag Clear */

#define R_ICU_NMICLR_BUSCLR                       (1 << 12)  /*  */

#define R_ICU_NMICLR_CMCLR                        (1 << 13)  /*  */

#define R_ICU_NMICLR_LUCLR                        (1 << 15)  /*  */

#define R_ICU_NMICLR_LVD1CLR                      (1 << 2)  /* PVD1 Clear */

#define R_ICU_NMICLR_LVD2CLR                      (1 << 3)  /* PVD2 Clear */

/* NMISR Register bit definitions */
#define R_ICU_NMISR_IWDTST                        (1 << 0)  /* IWDT Underflow/Refresh Error Interrupt Status Flag */

#define R_ICU_NMISR_WDTST                         (1 << 1)  /* WDT Underflow/Refresh Error Interrupt Status Flag */

#define R_ICU_NMISR_PVD1ST                        (1 << 2)  /* Voltage Monitor 1 Interrupt Status Flag */

#define R_ICU_NMISR_PVD2ST                        (1 << 3)  /* Voltage Monitor 2 Interrupt Status Flag */

#define R_ICU_NMISR_OSTST                         (1 << 6)  /* Main Clock Oscillation Stop Detection Interrupt Status Flag */

#define R_ICU_NMISR_NMIST                         (1 << 7)  /* NMI Pin Interrupt Status Flag */

#define R_ICU_NMISR_BUSST                         (1 << 12)  /* Bus Error Interrupt Status Flag */

#define R_ICU_NMISR_CMST                          (1 << 13)  /*  */

#define R_ICU_NMISR_LUST                          (1 << 15)  /*  */

#define R_ICU_NMISR_LVD1ST                        (1 << 2)  /* Voltage-Monitoring 1 Interrupt Status Flag */

#define R_ICU_NMISR_LVD2ST                        (1 << 3)  /* Voltage-Monitoring 2 Interrupt Status Flag */

/* WUPEN0 Register bit definitions */
#define R_ICU_WUPEN0_IRQWUPEN_SHIFT               (0)  /*  */
#define R_ICU_WUPEN0_IRQWUPEN_MASK                0xffff
#  define R_ICU_WUPEN0_IRQWUPEN_0                         (0 << R_ICU_WUPEN0_IRQWUPEN_SHIFT)  /* Deep Sleep/Software Standby Mode returns by IRQn interrupt is disabled . */
#  define R_ICU_WUPEN0_IRQWUPEN_1                         (1 << R_ICU_WUPEN0_IRQWUPEN_SHIFT)  /* Deep Sleep/Software Standby Mode returns by IRQn interrupt is enabled */

#define R_ICU_WUPEN0_IWDTWUPEN                    (1 << 16)  /* IWDT Interrupt Deep Sleep/Software Standby Mode Returns Enable */

#define R_ICU_WUPEN0_PVD1WUPEN                    (1 << 18)  /* PVD1 Interrupt Deep Sleep/Software Standby Mode Returns Enable */

#define R_ICU_WUPEN0_PVD2WUPEN                    (1 << 19)  /* PVD2 Interrupt Deep Sleep/Software Standby Mode Returns Enable */

#define R_ICU_WUPEN0_VBATTWUPEN                   (1 << 20)  /* VBATT Monitor Interrupt Deep Sleep/Software Standby Mode Returns Enable */

#define R_ICU_WUPEN0_RTCALMWUPEN                  (1 << 24)  /* RTC Alarm Interrupt Deep Sleep/Software Standby Mode Returns Enable */

#define R_ICU_WUPEN0_RTCPRDWUPEN                  (1 << 25)  /* RTC Period Interrupt Deep Sleep/Software Standby Mode Returns Enable */

#define R_ICU_WUPEN0_USBFS0WUPEN                  (1 << 27)  /* USBFS Interrupt Deep Sleep/Software Standby Mode Returns Enable */

#define R_ICU_WUPEN0_AGT1UDWUPEN                  (1 << 28)  /* AGT1 Underflow Interrupt Deep Sleep/Software Standby Mode Returns Enable */

#define R_ICU_WUPEN0_AGT1CAWUPEN                  (1 << 29)  /* AGT1 Compare Match A Interrupt Deep Sleep/Software Standby Mode Returns Enable */

#define R_ICU_WUPEN0_AGT1CBWUPEN                  (1 << 30)  /* AGT1 Compare Match B Interrupt Deep Sleep/Software Standby Mode Returns Enable */

#define R_ICU_WUPEN0_IIC0WUPEN                    (1 << 31)  /* IIC0 Address Match Interrupt Deep Sleep/Software Standby Mode Returns Enable */

/* WUPEN1 Register bit definitions */
#define R_ICU_WUPEN1_COMPHS0WUPEN                 (1 << 3)  /* Comparator-HS0 Interrupt Deep Sleep/Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_ULP0UWUPEN                   (1 << 8)  /* ULPT0 Underflow Interrupt Deep Sleep/Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_ULP0AWUPEN                   (1 << 9)  /* ULPT0 Compare Match A Interrupt Deep Sleep/Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_ULP0BWUPEN                   (1 << 10)  /* ULPT0 Compare Match B Interrupt Deep Sleep/Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_ULP1UWUPEN                   (1 << 12)  /* ULPT1 Underflow Interrupt Deep Sleep/Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_ULP1AWUPEN                   (1 << 13)  /* ULPT1 Compare Match A Interrupt Deep Sleep/Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_ULP1BWUPEN                   (1 << 14)  /* ULPT1 Compare Match B Interrupt Deep Sleep/Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_I3CWUPEN                     (1 << 11)  /* I3C Wakeup Condition Detection Interrupt Deep Sleep/Software Standby Returns Enable bit */

/* DELSR Register bit definitions */
#define R_ICU_DELSR_DELS_SHIFT                    (0)  /* DMAC Event Link Select */
#define R_ICU_DELSR_DELS_MASK                     0x3ff

#define R_ICU_DELSR_IR                            (1 << 16)  /* DMAC Activation Request Status Flag */

/* IELSR Register bit definitions */
#define R_ICU_IELSR_IELS_SHIFT                    (0)  /* ICU Event selection to NVICSet the number for the event signal to be linked . */
#define R_ICU_IELSR_IELS_MASK                     0x1ff

#define R_ICU_IELSR_IR                            (1 << 16)  /* Interrupt Status Flag */

#define R_ICU_IELSR_DTCE                          (1 << 24)  /* DTC Activation Enable */


/* Maximum number of channels */

#define ICU_MAX_CHANNELS    96

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_ICU_H */

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
#define R_ICU_BASE           0x40006000
#else
#define R_ICU_BASE           0x50006000
#endif
#endif

/* ICU Register Offsets */

/* IRQCRa[%s] Registers () */
#define R_ICU_IRQCRA_OFFSET(m)                    (0x00000000 + ((m) * 0x00000001))  /* IRQ Control Register %s */
#define R_ICU_NMICR_OFFSET                        0x00000010  /* NMI Pin Interrupt Control Register */
/* IRQCRb[%s] Registers () */
#define R_ICU_IRQCRB_OFFSET(m)                    (0x00000014 + ((m) * 0x00000001))  /* IRQ Control Register %s */
/* INTSELR[%s] Registers () */
#define R_ICU_INTSELR_OFFSET(m)                   (0x00000040 + ((m) * 0x00000004))  /* Interrupt request select Register */
#define R_ICU_NMIER_OFFSET                        0x00006100  /* Non-Maskable Interrupt Enable Register */
#define R_ICU_NMICLR_OFFSET                       0x00006110  /* Non-Maskable Interrupt Status Clear Register */
#define R_ICU_NMISR_OFFSET                        0x00006120  /* Non-Maskable Interrupt Status Register */
#define R_ICU_WUPEN0_OFFSET                       0x000061a0  /* Wake Up Interrupt Enable Register 0 */
#define R_ICU_WUPEN1_OFFSET                       0x000061a4  /* Wake Up Interrupt Enable Register 1 */
/* DSLPWUPIRQEN[%s] Registers () */
#define R_ICU_DSLPWUPIRQEN_OFFSET(m)              (0x00006210 + ((m) * 0x00000004))  /* Deep Sleep Wake Up IRQ Enable Register */
/* DELSR[%s] Registers () */
#define R_ICU_DELSR_OFFSET(m)                     (0x00006280 + ((m) * 0x00000004))  /* DMAC Event Link Setting Registers */
/* IELSR[%s] Registers () */
#define R_ICU_IELSR_OFFSET(m)                     (0x00006300 + ((m) * 0x00000004))  /* ICU Event Link Setting Register %s */

/* ICU Register Addresses */

#define R_ICU_IRQCRA(m)                           (R_ICU_BASE + R_ICU_IRQCRA_OFFSET(m))
#define R_ICU_NMICR                               (R_ICU_BASE + R_ICU_NMICR_OFFSET)
#define R_ICU_IRQCRB(m)                           (R_ICU_BASE + R_ICU_IRQCRB_OFFSET(m))
#define R_ICU_INTSELR(m)                          (R_ICU_BASE + R_ICU_INTSELR_OFFSET(m))
#define R_ICU_NMIER                               (R_ICU_BASE + R_ICU_NMIER_OFFSET)
#define R_ICU_NMICLR                              (R_ICU_BASE + R_ICU_NMICLR_OFFSET)
#define R_ICU_NMISR                               (R_ICU_BASE + R_ICU_NMISR_OFFSET)
#define R_ICU_WUPEN0                              (R_ICU_BASE + R_ICU_WUPEN0_OFFSET)
#define R_ICU_WUPEN1                              (R_ICU_BASE + R_ICU_WUPEN1_OFFSET)
#define R_ICU_DSLPWUPIRQEN(m)                     (R_ICU_BASE + R_ICU_DSLPWUPIRQEN_OFFSET(m))
#define R_ICU_DELSR(m)                            (R_ICU_BASE + R_ICU_DELSR_OFFSET(m))
#define R_ICU_IELSR(m)                            (R_ICU_BASE + R_ICU_IELSR_OFFSET(m))

/* Register bit definitions */
/* IRQCRA Register bit definitions */
#define R_ICU_IRQCRA_IRQMD_SHIFT                  (0)  /* IRQ Detection Sense Select */
#define R_ICU_IRQCRA_IRQMD_MASK                   0x3
#  define R_ICU_IRQCRA_IRQMD_00                           (0 << R_ICU_IRQCRA_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_IRQCRA_IRQMD_01                           (1 << R_ICU_IRQCRA_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_IRQCRA_IRQMD_10                           (2 << R_ICU_IRQCRA_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_IRQCRA_IRQMD_11                           (3 << R_ICU_IRQCRA_IRQMD_SHIFT)  /* Low level */

#define R_ICU_IRQCRA_FCLKSEL_SHIFT                (4)  /* IRQ Digital Filter Sampling Clock Select */
#define R_ICU_IRQCRA_FCLKSEL_MASK                 0x30
#  define R_ICU_IRQCRA_FCLKSEL_00                         (0 << R_ICU_IRQCRA_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_IRQCRA_FCLKSEL_01                         (1 << R_ICU_IRQCRA_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_IRQCRA_FCLKSEL_10                         (2 << R_ICU_IRQCRA_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_IRQCRA_FCLKSEL_11                         (3 << R_ICU_IRQCRA_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_IRQCRA_FLTEN                        (1 << 7)  /* IRQ Digital Filter Enable */

/* NMICR Register bit definitions */
#define R_ICU_NMICR_NMIMD                         (1 << 0)  /* NMI Detection Set */

#define R_ICU_NMICR_NFCLKSEL_SHIFT                (4)  /* NMI Digital Filter Sampling Clock */
#define R_ICU_NMICR_NFCLKSEL_MASK                 0x30
#  define R_ICU_NMICR_NFCLKSEL_00                         (0 << R_ICU_NMICR_NFCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_NMICR_NFCLKSEL_01                         (1 << R_ICU_NMICR_NFCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_NMICR_NFCLKSEL_10                         (2 << R_ICU_NMICR_NFCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_NMICR_NFCLKSEL_11                         (3 << R_ICU_NMICR_NFCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_NMICR_NFLTEN                        (1 << 7)  /* NMI Digital Filter Enable */

/* IRQCRB Register bit definitions */
#define R_ICU_IRQCRB_IRQMD_SHIFT                  (0)  /* IRQ Detection Sense Select */
#define R_ICU_IRQCRB_IRQMD_MASK                   0x3
#  define R_ICU_IRQCRB_IRQMD_00                           (0 << R_ICU_IRQCRB_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_IRQCRB_IRQMD_01                           (1 << R_ICU_IRQCRB_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_IRQCRB_IRQMD_10                           (2 << R_ICU_IRQCRB_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_IRQCRB_IRQMD_11                           (3 << R_ICU_IRQCRB_IRQMD_SHIFT)  /* Low level */

#define R_ICU_IRQCRB_FCLKSEL_SHIFT                (4)  /* IRQ Digital Filter Sampling Clock Select */
#define R_ICU_IRQCRB_FCLKSEL_MASK                 0x30
#  define R_ICU_IRQCRB_FCLKSEL_00                         (0 << R_ICU_IRQCRB_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_IRQCRB_FCLKSEL_01                         (1 << R_ICU_IRQCRB_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_IRQCRB_FCLKSEL_10                         (2 << R_ICU_IRQCRB_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_IRQCRB_FCLKSEL_11                         (3 << R_ICU_IRQCRB_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_IRQCRB_FLTEN                        (1 << 7)  /* IRQ Digital Filter Enable */

/* INTSELR Register bit definitions */
#define R_ICU_INTSELR_IS_S                        (1 << 0)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS0                         (1 << 0)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS1                         (1 << 1)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS2                         (1 << 2)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS3                         (1 << 3)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS4                         (1 << 4)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS5                         (1 << 5)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS6                         (1 << 6)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS7                         (1 << 7)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS8                         (1 << 8)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS9                         (1 << 9)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS10                        (1 << 10)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS11                        (1 << 11)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS12                        (1 << 12)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS13                        (1 << 13)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS14                        (1 << 14)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS15                        (1 << 15)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS16                        (1 << 16)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS17                        (1 << 17)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS18                        (1 << 18)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS19                        (1 << 19)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS20                        (1 << 20)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS21                        (1 << 21)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS22                        (1 << 22)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS23                        (1 << 23)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS24                        (1 << 24)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS25                        (1 << 25)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS26                        (1 << 26)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS27                        (1 << 27)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS28                        (1 << 28)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS29                        (1 << 29)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS30                        (1 << 30)  /* Selects which CPU receives interrupt requests */

#define R_ICU_INTSELR_IS31                        (1 << 31)  /* Selects which CPU receives interrupt requests */

/* NMIER Register bit definitions */
#define R_ICU_NMIER_IWDTEN                        (1 << 0)  /* IWDT Underflow/Refresh Error Interrupt Enable */

#define R_ICU_NMIER_WDTEN                         (1 << 1)  /* WDT Underflow/Refresh Error Interrupt Enable */

#define R_ICU_NMIER_PVD1EN                        (1 << 2)  /* Voltage-Monitoring 1 Interrupt Enable */

#define R_ICU_NMIER_PVD2EN                        (1 << 3)  /* Voltage-Monitoring 2 Interrupt Enable */

#define R_ICU_NMIER_SOSTEN                        (1 << 5)  /* Sub Oscillation Stop Detection Interrupt Enable */

#define R_ICU_NMIER_OSTEN                         (1 << 6)  /* Oscillation Stop Detection Interrupt Enable */

#define R_ICU_NMIER_NMIEN                         (1 << 7)  /* NMI Pin Interrupt Enable */

#define R_ICU_NMIER_BUSEN                         (1 << 12)  /* BUS error Interrupt Enable */

#define R_ICU_NMIER_CMEN                          (1 << 13)  /* Common Memory error Interrupt Enable */

#define R_ICU_NMIER_LMEN                          (1 << 14)  /* Local Memory Error Interrupt Enable */

#define R_ICU_NMIER_LUEN                          (1 << 15)  /* LockUp Interrupt Enable */

#define R_ICU_NMIER_FPUFLTEN                      (1 << 16)  /* FPU FAULT Interrupt Enable */

#define R_ICU_NMIER_MRCRDEN                       (1 << 17)  /* MRAM MRC read Error Interrupt Enable */

#define R_ICU_NMIER_MRERDEN                       (1 << 18)  /* MRAM MRE read Error Interrupt Enable */

#define R_ICU_NMIER_IPCEN                         (1 << 20)  /* IPC NMI CPU mutual Interrupt Enable */

/* NMICLR Register bit definitions */
#define R_ICU_NMICLR_IWDTCLR                      (1 << 0)  /* IWDT Clear */

#define R_ICU_NMICLR_WDTCLR                       (1 << 1)  /* WDT Clear */

#define R_ICU_NMICLR_PVD1CLR                      (1 << 2)  /* PVD1 Clear */

#define R_ICU_NMICLR_PVD2CLR                      (1 << 3)  /* PVD2 Clear */

#define R_ICU_NMICLR_SOSTCLR                      (1 << 5)  /* Sub OST Clear */

#define R_ICU_NMICLR_OSTCLR                       (1 << 6)  /* OST Clear */

#define R_ICU_NMICLR_NMICLR                       (1 << 7)  /* NMI Clear */

#define R_ICU_NMICLR_BUSCLR                       (1 << 12)  /* Bus Clear */

#define R_ICU_NMICLR_CMCLR                        (1 << 13)  /* CM Clear */

#define R_ICU_NMICLR_LMCLR                        (1 << 14)  /* LM Clear */

#define R_ICU_NMICLR_LUCLR                        (1 << 15)  /* LU Clear */

#define R_ICU_NMICLR_FPUFLTCLR                    (1 << 16)  /* FPU FAULT Clear */

#define R_ICU_NMICLR_MRCRDCLR                     (1 << 17)  /* MRAM MRC read Error Interrupt Clear */

#define R_ICU_NMICLR_MRERDCLR                     (1 << 18)  /* MRAM MRE read Error Interrupt Clear */

#define R_ICU_NMICLR_IPCCLR                       (1 << 20)  /* IPC NMI CPU mutual Interrupt Clear */

/* NMISR Register bit definitions */
#define R_ICU_NMISR_IWDTST                        (1 << 0)  /* IWDT Underflow/Refresh Error Status Flag */

#define R_ICU_NMISR_WDTST                         (1 << 1)  /* WDT Underflow/Refresh Error Status Flag */

#define R_ICU_NMISR_PVD1ST                        (1 << 2)  /* Voltage-Monitoring 1 Interrupt Status Flag */

#define R_ICU_NMISR_PVD2ST                        (1 << 3)  /* Voltage-Monitoring 2 Interrupt Status Flag */

#define R_ICU_NMISR_SOSTST                        (1 << 5)  /* Sub Oscillation Stop Detection Interrupt Status Flag */

#define R_ICU_NMISR_OSTST                         (1 << 6)  /* Oscillation Stop Detection Interrupt Status Flag */

#define R_ICU_NMISR_NMIST                         (1 << 7)  /* NMI Status Flag */

#define R_ICU_NMISR_BUSST                         (1 << 12)  /* BUS error Interrupt Status Flag */

#define R_ICU_NMISR_CMST                          (1 << 13)  /* Common Memory error Interrupt Status Flag */

#define R_ICU_NMISR_LMST                          (1 << 14)  /* Local Memory Error Interrupt Status Flag */

#define R_ICU_NMISR_LUST                          (1 << 15)  /* LockUp Interrupt Status Flag */

#define R_ICU_NMISR_FPUFLTST                      (1 << 16)  /* FPU FAULT Interrupt Status Flag */

#define R_ICU_NMISR_MRCRDST                       (1 << 17)  /* MRAM MRC read Error Interrupt Status Flag */

#define R_ICU_NMISR_MRERDST                       (1 << 18)  /* MRAM MRE read Error Interrupt Status Flag */

#define R_ICU_NMISR_IPCST                         (1 << 20)  /* IPC NMI CPU mutual Interrupt Status Flag */

/* WUPEN Register bit definitions */
#define R_ICU_WUPEN_IRQWUPEN_S                    (1 << 0)  /* IRQ%s Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_WUPEN_S                       (1 << 16)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit %s */

#define R_ICU_WUPEN_IRQWUPEN0                     (1 << 0)  /* IRQ0 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_IRQWUPEN1                     (1 << 1)  /* IRQ1 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_IRQWUPEN2                     (1 << 2)  /* IRQ2 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_IRQWUPEN3                     (1 << 3)  /* IRQ3 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_IRQWUPEN4                     (1 << 4)  /* IRQ4 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_IRQWUPEN5                     (1 << 5)  /* IRQ5 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_IRQWUPEN6                     (1 << 6)  /* IRQ6 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_IRQWUPEN7                     (1 << 7)  /* IRQ7 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_IRQWUPEN8                     (1 << 8)  /* IRQ8 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_IRQWUPEN9                     (1 << 9)  /* IRQ9 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_IRQWUPEN10                    (1 << 10)  /* IRQ10 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_IRQWUPEN11                    (1 << 11)  /* IRQ11 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_IRQWUPEN12                    (1 << 12)  /* IRQ12 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_IRQWUPEN13                    (1 << 13)  /* IRQ13 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_IRQWUPEN14                    (1 << 14)  /* IRQ14 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_IRQWUPEN15                    (1 << 15)  /* IRQ15 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN_WUPEN0                        (1 << 16)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 0 */

#define R_ICU_WUPEN_WUPEN1                        (1 << 17)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 1 */

#define R_ICU_WUPEN_WUPEN2                        (1 << 18)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 2 */

#define R_ICU_WUPEN_WUPEN3                        (1 << 19)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 3 */

#define R_ICU_WUPEN_WUPEN4                        (1 << 20)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 4 */

#define R_ICU_WUPEN_WUPEN5                        (1 << 21)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 5 */

#define R_ICU_WUPEN_WUPEN6                        (1 << 22)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 6 */

#define R_ICU_WUPEN_WUPEN7                        (1 << 23)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 7 */

#define R_ICU_WUPEN_WUPEN8                        (1 << 24)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 8 */

#define R_ICU_WUPEN_WUPEN9                        (1 << 25)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 9 */

#define R_ICU_WUPEN_WUPEN10                       (1 << 26)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 10 */

#define R_ICU_WUPEN_WUPEN11                       (1 << 27)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 11 */

#define R_ICU_WUPEN_WUPEN12                       (1 << 28)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 12 */

#define R_ICU_WUPEN_WUPEN13                       (1 << 29)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 13 */

#define R_ICU_WUPEN_WUPEN14                       (1 << 30)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 14 */

#define R_ICU_WUPEN_WUPEN15                       (1 << 31)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit 15 */

/* WUPEN1 Register bit definitions */
#define R_ICU_WUPEN1_WUPEN_S                      (1 << 0)  /* Peripheral Interrupt Deep Sleep/Software Standby Returns Enable bit %s */

#define R_ICU_WUPEN1_IRQWUPEN_S                   (1 << 16)  /* IRQ%s Interrupt Deep Sleep/Software Standby Returns Enable bit */

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

#define R_ICU_WUPEN1_IRQWUPEN16                   (1 << 16)  /* IRQ16 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN17                   (1 << 17)  /* IRQ17 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN18                   (1 << 18)  /* IRQ18 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN19                   (1 << 19)  /* IRQ19 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN20                   (1 << 20)  /* IRQ20 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN21                   (1 << 21)  /* IRQ21 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN22                   (1 << 22)  /* IRQ22 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN23                   (1 << 23)  /* IRQ23 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN24                   (1 << 24)  /* IRQ24 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN25                   (1 << 25)  /* IRQ25 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN26                   (1 << 26)  /* IRQ26 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN27                   (1 << 27)  /* IRQ27 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN28                   (1 << 28)  /* IRQ28 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN29                   (1 << 29)  /* IRQ29 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN30                   (1 << 30)  /* IRQ30 Interrupt Deep Sleep/Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN31                   (1 << 31)  /* IRQ31 Interrupt Deep Sleep/Software Standby Returns Enable bit */

/* DSLPWUPIRQEN Register bit definitions */
#define R_ICU_DSLPWUPIRQEN_IRQ_S                  (1 << 0)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ0                   (1 << 0)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ1                   (1 << 1)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ2                   (1 << 2)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ3                   (1 << 3)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ4                   (1 << 4)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ5                   (1 << 5)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ6                   (1 << 6)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ7                   (1 << 7)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ8                   (1 << 8)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ9                   (1 << 9)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ10                  (1 << 10)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ11                  (1 << 11)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ12                  (1 << 12)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ13                  (1 << 13)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ14                  (1 << 14)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ15                  (1 << 15)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ16                  (1 << 16)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ17                  (1 << 17)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ18                  (1 << 18)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ19                  (1 << 19)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ20                  (1 << 20)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ21                  (1 << 21)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ22                  (1 << 22)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ23                  (1 << 23)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ24                  (1 << 24)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ25                  (1 << 25)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ26                  (1 << 26)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ27                  (1 << 27)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ28                  (1 << 28)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ29                  (1 << 29)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ30                  (1 << 30)  /* IRQ Deep Sleep Returns Enable bit */

#define R_ICU_DSLPWUPIRQEN_IRQ31                  (1 << 31)  /* IRQ Deep Sleep Returns Enable bit */

/* DELSR Register bit definitions */
#define R_ICU_DELSR_DELS_SHIFT                    (0)  /* DMAC Event Link Select */
#define R_ICU_DELSR_DELS_MASK                     0x3ff

#define R_ICU_DELSR_IR                            (1 << 16)  /* DMAC Activation Request Status Flag */

/* IELSR Register bit definitions */
#define R_ICU_IELSR_IELS_SHIFT                    (0)  /* ICU Event Link Select */
#define R_ICU_IELSR_IELS_MASK                     0x3ff
#  define R_ICU_IELSR_IELS_0X000                          (0 << R_ICU_IELSR_IELS_SHIFT)  /* Nothing is selected */

#define R_ICU_IELSR_IR                            (1 << 16)  /* Interrupt Status Flag */

#define R_ICU_IELSR_DTCE                          (1 << 24)  /* DTC Activation Enable */


/* Maximum number of channels */

#define ICU_MAX_CHANNELS    96

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ICU_H */

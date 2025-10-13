/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_sysc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SYSC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SYSC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SYSC Base Address */
#ifndef R_SYSC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_SYSC_BASE           0x4001e000
#else
#define R_SYSC_BASE           0x5001e000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_SYSC_CH_STRIDE    0x00000002
#define R_SYSC_CH_BASE(ch)   (R_SYSC_BASE + ((uint32_t)(ch) * R_SYSC_CH_STRIDE))

/* SYSC Register Offsets */

#define R_SYSC_SCKDIVCR_OFFSET                    0x00000020  /* System Clock Division Control Register */
#define R_SYSC_SCKDIVCR2_OFFSET                   0x00000024  /* System Clock Division Control Register 2 */
#define R_SYSC_SCKSCR_OFFSET                      0x00000026  /* System Clock Source Control Register */
#define R_SYSC_PLLCCR_OFFSET                      0x00000028  /* PLL Clock Control Register */
#define R_SYSC_PLLCR_OFFSET                       0x0000002a  /* PLL Control Register */
#define R_SYSC_MOSCCR_OFFSET                      0x00000032  /* Main Clock Oscillator Control Register */
#define R_SYSC_HOCOCR_OFFSET                      0x00000036  /* High-Speed On-Chip Oscillator Control Register */
#define R_SYSC_HOCOCR2_OFFSET                     0x00000037  /* High-Speed On-Chip Oscillator Control Register2 */
#define R_SYSC_MOCOCR_OFFSET                      0x00000038  /* Middle-Speed On-Chip Oscillator Control Register */
#define R_SYSC_FLLCR1_OFFSET                      0x00000039  /* FLL Control Register1 */
#define R_SYSC_FLLCR2_OFFSET                      0x0000003a  /* FLL Control Register2 */
#define R_SYSC_OSCSF_OFFSET                       0x0000003c  /* Oscillation Stabilization Flag Register */
#define R_SYSC_CKOCR_OFFSET                       0x0000003e  /* Clock Out Control Register */
#define R_SYSC_TRCKCR_OFFSET                      0x0000003f  /* Trace Clock Control Register */
#define R_SYSC_OSTDCR_OFFSET                      0x00000040  /* Oscillation Stop Detection Control Register */
#define R_SYSC_OSTDSR_OFFSET                      0x00000041  /* Oscillation Stop Detection Status Register */
#define R_SYSC_OSCMONR_OFFSET                     0x00000043  /* Oscillator Monitor Register */
#define R_SYSC_PLL2CCR_OFFSET                     0x00000048  /* PLL2 Clock Control Register */
#define R_SYSC_PLL2CR_OFFSET                      0x0000004a  /* PLL2 Control Register */
#define R_SYSC_PLLCCR2_OFFSET                     0x0000004c  /* PLL Clock Control Register 2 */
#define R_SYSC_PLL2CCR2_OFFSET                    0x0000004e  /* PLL2 Clock Control Register 2 */
#define R_SYSC_SCICKDIVCR_OFFSET                  0x00000054  /* SCI clock Division control register */
#define R_SYSC_SCICKCR_OFFSET                     0x00000055  /* SCI clock control register */
#define R_SYSC_SPICKDIVCR_OFFSET                  0x00000056  /* SPI clock Division control register */
#define R_SYSC_SPICKCR_OFFSET                     0x00000057  /* SPI clock control register */
#define R_SYSC_MOCOUTCR_OFFSET                    0x00000061  /* MOCO User Trimming Control Register */
#define R_SYSC_HOCOUTCR_OFFSET                    0x00000062  /* HOCO User Trimming Control Register */
#define R_SYSC_USBCKDIVCR_OFFSET                  0x0000006c  /* USB Clock Division Control Register */
#define R_SYSC_OCTACKDIVCR_OFFSET                 0x0000006d  /* Octal-SPI Clock Division Control Register */
#define R_SYSC_CANFDCKDIVCR_OFFSET                0x0000006e  /* CANFD Core Clock Division Control Register */
#define R_SYSC_USBCKCR_OFFSET                     0x00000074  /* USB Clock Control Register */
#define R_SYSC_OCTACKCR_OFFSET                    0x00000075  /* Octal-SPI Clock Control Register */
#define R_SYSC_CANFDCKCR_OFFSET                   0x00000076  /* CANFD Core Clock Control Register */
#define R_SYSC_MOSCSCR_OFFSET                     0x0000007c  /* Main Clock Oscillator Standby Control Register */
#define R_SYSC_HOCOSCR_OFFSET                     0x0000007d  /* High-Speed On-Chip Oscillator Standby Control Register */
#define R_SYSC_OPCCR_OFFSET                       0x000000a0  /* Operating Power Control Register */
#define R_SYSC_MOSCWTCR_OFFSET                    0x000000a2  /* Main Clock Oscillator Wait Control Register */
#define R_SYSC_RSTSR1_OFFSET                      0x000000c0  /* Reset Status Register 1 */
#define R_SYSC_SYRACCR_OFFSET                     0x000000cc  /* System Register Access Control Register */
/* PVD%sCR1 Registers (1-2) */
#define R_SYSC_PVDCR1_OFFSET                      0x000000e0  /* Voltage Monitor %s Circuit Control Register 1 */
#define R_SYSC_PVDCR1_INCREMENT                   0x00000002
/* PVD%sSR Registers (1-2) */
#define R_SYSC_PVDSR_OFFSET                       0x000000e1  /* Voltage Monitor %s Circuit Status Register */
#define R_SYSC_PVDSR_INCREMENT                    0x00000002
#define R_SYSC_PDRAMSCR0_OFFSET                   0x00000140  /* SRAM Power Domain Standby Control Register 0 */
#define R_SYSC_PDRAMSCR1_OFFSET                   0x00000142  /* SRAM Power Domain Standby Control Register 1 */
#define R_SYSC_VBRSABAR_OFFSET                    0x000003b0  /* VBATT Backup Register Security Attribute Boundary Address Register */
#define R_SYSC_VBRPABARS_OFFSET                   0x000003b4  /* VBATT Backup Register Privilege Attribute Boundary Address Register for Secure Region */
#define R_SYSC_CGFSAR_OFFSET                      0x000003c0  /* Clock Generation Function Security Attribute Register */
#define R_SYSC_RSTSAR_OFFSET                      0x000003c4  /* Reset Security Attribution Register */
#define R_SYSC_LPMSAR_OFFSET                      0x000003c8  /* Low Power Mode Security Attribution Register */
#define R_SYSC_PVDSAR_OFFSET                      0x000003cc  /* Programable Voltage Detection Security Attribution Register */
#define R_SYSC_BBFSAR_OFFSET                      0x000003d0  /* Battery Backup Function Security Attribute Register */
#define R_SYSC_DPFSAR_OFFSET                      0x000003e0  /* Deep Software Standby Interrupt Factor Security Attribution Register */
#define R_SYSC_RSCSAR_OFFSET                      0x000003e4  /* RAM Standby Control Security Attribution Register */
#define R_SYSC_PRCR_S_OFFSET                      0x000003fa  /* Protect Register for Secure (PRCR_S) */
#define R_SYSC_LOCOCR_OFFSET                      0x00000400  /* Low-Speed On-Chip Oscillator Control Register */
#define R_SYSC_LOCOUTCR_OFFSET                    0x00000402  /* LOCO User Trimming Control Register */
#define R_SYSC_DPSBYCR_OFFSET                     0x00000a00  /* Deep Software Standby Control Register */
#define R_SYSC_DPSWCR_OFFSET                      0x00000a04  /* Deep Software Standby Wait Control Register */
#define R_SYSC_DPSIER0_OFFSET                     0x00000a08  /* Deep Software Standby Interrupt Enable Register 0 */
#define R_SYSC_DPSIER1_OFFSET                     0x00000a0c  /* Deep Software Standby Interrupt Enable Register 1 */
#define R_SYSC_DPSIER2_OFFSET                     0x00000a10  /* Deep Software Standby Interrupt Enable Register 2 */
#define R_SYSC_DPSIER3_OFFSET                     0x00000a14  /* Deep Software Standby Interrupt Enable Register 3 */
#define R_SYSC_DPSIFR0_OFFSET                     0x00000a18  /* Deep Software Standby Interrupt Flag Register 0 */
#define R_SYSC_DPSIFR1_OFFSET                     0x00000a1c  /* Deep Software Standby Interrupt Flag Register 1 */
#define R_SYSC_DPSIFR2_OFFSET                     0x00000a20  /* Deep Software Standby Interrupt Flag Register 2 */
#define R_SYSC_DPSIFR3_OFFSET                     0x00000a24  /* Deep Software Standby Interrupt Flag Register 3 */
#define R_SYSC_DPSIEGR0_OFFSET                    0x00000a28  /* Deep Software Standby Interrupt Edge Register 0 */
#define R_SYSC_DPSIEGR1_OFFSET                    0x00000a2c  /* Deep Software Standby Interrupt Edge Register 1 */
#define R_SYSC_DPSIEGR2_OFFSET                    0x00000a30  /* Deep Software Standby Interrupt Edge Register 2 */
#define R_SYSC_SYOCDCR_OFFSET                     0x00000a38  /* System Control OCD Control Register */
#define R_SYSC_RSTSR0_OFFSET                      0x00000a40  /* Reset Status Register 0 */
#define R_SYSC_RSTSR2_OFFSET                      0x00000a44  /* Reset Status Register 2 */
#define R_SYSC_MOMCR_OFFSET                       0x00000a50  /* Main Clock Oscillator Mode Oscillation Control Register */
#define R_SYSC_FWEPROR_OFFSET                     0x00000a54  /* Flash P/E Protect Register */
/* PVD%sCMPCR Registers (1-2) */
#define R_SYSC_PVDCMPCR_OFFSET                    0x00000a58  /* Voltage Monitor %s Comparator Control Register */
#define R_SYSC_PVDCMPCR_INCREMENT                 0x00000004
/* PVD%sCR0 Registers (1-2) */
#define R_SYSC_PVDCR0_OFFSET                      0x00000a70  /* Voltage Monitor %s Circuit Control Register 0 */
#define R_SYSC_PVDCR0_INCREMENT                   0x00000004
#define R_SYSC_VBATTMNSELR_OFFSET                 0x00000a84  /* Battery Backup Voltage Monitor Function Select Register */
#define R_SYSC_VBTBPCR1_OFFSET                    0x00000a88  /* VBATT Battery Power Supply Control Register 1 */
#define R_SYSC_LPSCR_OFFSET                       0x00000a90  /* Low Power State Control Register */
#define R_SYSC_SSCR1_OFFSET                       0x00000a98  /* Software Standby Control Register 1 */
#define R_SYSC_LVOCR_OFFSET                       0x00000ab0  /* Low Voltage Operation Control register */
#define R_SYSC_SYRSTMSK0_OFFSET                   0x00000ad0  /* System Reset Mask Control Register 0 */
#define R_SYSC_SYRSTMSK2_OFFSET                   0x00000ad8  /* System Reset Mask Control Register 2 */
#define R_SYSC_PLL1LDOCR_OFFSET                   0x00000b04  /* PLL1-LDO Control Register */
#define R_SYSC_PLL2LDOCR_OFFSET                   0x00000b08  /* PLL2-LDO Control Register */
#define R_SYSC_HOCOLDOCR_OFFSET                   0x00000b0c  /* HOCO-LDO Control Register */
/* PVD%sFCR Registers (1-2) */
#define R_SYSC_PVDFCR_OFFSET                      0x00000b20  /* Voltage Monitor %s Function Control Register */
#define R_SYSC_PVDFCR_INCREMENT                   0x00000004
#define R_SYSC_SOSCCR_OFFSET                      0x00000c00  /* Sub-Clock Oscillator Control Register */
#define R_SYSC_SOMCR_OFFSET                       0x00000c01  /* Sub-Clock Oscillator Mode Control Register */
#define R_SYSC_VBTBER_OFFSET                      0x00000c40  /* VBATT Backup Enable Register */
#define R_SYSC_VBTBPCR2_OFFSET                    0x00000c45  /* VBATT Battery Power Supply Control Register 2 */
#define R_SYSC_VBTBPSR_OFFSET                     0x00000c46  /* VBATT Battery Power Supply Status Register */
#define R_SYSC_VBTADSR_OFFSET                     0x00000c48  /* VBATT Tamper detection Status Register */
#define R_SYSC_VBTADCR1_OFFSET                    0x00000c49  /* VBATT Tamper detection Control Register 1 */
#define R_SYSC_VBTADCR2_OFFSET                    0x00000c4a  /* VBATT Tamper detection Control Register 2 */
#define R_SYSC_VBTICTLR_OFFSET                    0x00000c4c  /* VBATT Input Control Register */
#define R_SYSC_VBTICTLR2_OFFSET                   0x00000c4d  /* VBATT Input Control Register 2 */
#define R_SYSC_VBTIMONR_OFFSET                    0x00000c4e  /* VBATT Input Monitor Register */
/* VBTBKR[%s] Registers () */
#define R_SYSC_VBTBKR_OFFSET                      0x00000d00  /* VBATT Backup Register */
#define R_SYSC_VBTBKR_INCREMENT                   0x00000001

/* SYSC Register Addresses */

#define R_SYSC_SCKDIVCR                           (R_SYSC_BASE + R_SYSC_SCKDIVCR_OFFSET)
#define R_SYSC_SCKDIVCR2                          (R_SYSC_BASE + R_SYSC_SCKDIVCR2_OFFSET)
#define R_SYSC_SCKSCR                             (R_SYSC_BASE + R_SYSC_SCKSCR_OFFSET)
#define R_SYSC_PLLCCR                             (R_SYSC_BASE + R_SYSC_PLLCCR_OFFSET)
#define R_SYSC_PLLCR                              (R_SYSC_BASE + R_SYSC_PLLCR_OFFSET)
#define R_SYSC_MOSCCR                             (R_SYSC_BASE + R_SYSC_MOSCCR_OFFSET)
#define R_SYSC_HOCOCR                             (R_SYSC_BASE + R_SYSC_HOCOCR_OFFSET)
#define R_SYSC_HOCOCR2                            (R_SYSC_BASE + R_SYSC_HOCOCR2_OFFSET)
#define R_SYSC_MOCOCR                             (R_SYSC_BASE + R_SYSC_MOCOCR_OFFSET)
#define R_SYSC_FLLCR1                             (R_SYSC_BASE + R_SYSC_FLLCR1_OFFSET)
#define R_SYSC_FLLCR2                             (R_SYSC_BASE + R_SYSC_FLLCR2_OFFSET)
#define R_SYSC_OSCSF                              (R_SYSC_BASE + R_SYSC_OSCSF_OFFSET)
#define R_SYSC_CKOCR                              (R_SYSC_BASE + R_SYSC_CKOCR_OFFSET)
#define R_SYSC_TRCKCR                             (R_SYSC_BASE + R_SYSC_TRCKCR_OFFSET)
#define R_SYSC_OSTDCR                             (R_SYSC_BASE + R_SYSC_OSTDCR_OFFSET)
#define R_SYSC_OSTDSR                             (R_SYSC_BASE + R_SYSC_OSTDSR_OFFSET)
#define R_SYSC_OSCMONR                            (R_SYSC_BASE + R_SYSC_OSCMONR_OFFSET)
#define R_SYSC_PLL2CCR                            (R_SYSC_BASE + R_SYSC_PLL2CCR_OFFSET)
#define R_SYSC_PLL2CR                             (R_SYSC_BASE + R_SYSC_PLL2CR_OFFSET)
#define R_SYSC_PLLCCR2                            (R_SYSC_BASE + R_SYSC_PLLCCR2_OFFSET)
#define R_SYSC_PLL2CCR2                           (R_SYSC_BASE + R_SYSC_PLL2CCR2_OFFSET)
#define R_SYSC_SCICKDIVCR                         (R_SYSC_BASE + R_SYSC_SCICKDIVCR_OFFSET)
#define R_SYSC_SCICKCR                            (R_SYSC_BASE + R_SYSC_SCICKCR_OFFSET)
#define R_SYSC_SPICKDIVCR                         (R_SYSC_BASE + R_SYSC_SPICKDIVCR_OFFSET)
#define R_SYSC_SPICKCR                            (R_SYSC_BASE + R_SYSC_SPICKCR_OFFSET)
#define R_SYSC_MOCOUTCR                           (R_SYSC_BASE + R_SYSC_MOCOUTCR_OFFSET)
#define R_SYSC_HOCOUTCR                           (R_SYSC_BASE + R_SYSC_HOCOUTCR_OFFSET)
#define R_SYSC_USBCKDIVCR                         (R_SYSC_BASE + R_SYSC_USBCKDIVCR_OFFSET)
#define R_SYSC_OCTACKDIVCR                        (R_SYSC_BASE + R_SYSC_OCTACKDIVCR_OFFSET)
#define R_SYSC_CANFDCKDIVCR                       (R_SYSC_BASE + R_SYSC_CANFDCKDIVCR_OFFSET)
#define R_SYSC_USBCKCR                            (R_SYSC_BASE + R_SYSC_USBCKCR_OFFSET)
#define R_SYSC_OCTACKCR                           (R_SYSC_BASE + R_SYSC_OCTACKCR_OFFSET)
#define R_SYSC_CANFDCKCR                          (R_SYSC_BASE + R_SYSC_CANFDCKCR_OFFSET)
#define R_SYSC_MOSCSCR                            (R_SYSC_BASE + R_SYSC_MOSCSCR_OFFSET)
#define R_SYSC_HOCOSCR                            (R_SYSC_BASE + R_SYSC_HOCOSCR_OFFSET)
#define R_SYSC_OPCCR                              (R_SYSC_BASE + R_SYSC_OPCCR_OFFSET)
#define R_SYSC_MOSCWTCR                           (R_SYSC_BASE + R_SYSC_MOSCWTCR_OFFSET)
#define R_SYSC_RSTSR1                             (R_SYSC_BASE + R_SYSC_RSTSR1_OFFSET)
#define R_SYSC_SYRACCR                            (R_SYSC_BASE + R_SYSC_SYRACCR_OFFSET)
#define R_SYSC_PVDCR1(n)                          (R_SYSC_BASE + R_SYSC_PVDCR1_OFFSET + (n)*0x00000002)
#define R_SYSC_PVDSR(n)                           (R_SYSC_BASE + R_SYSC_PVDSR_OFFSET + (n)*0x00000002)
#define R_SYSC_PDRAMSCR0                          (R_SYSC_BASE + R_SYSC_PDRAMSCR0_OFFSET)
#define R_SYSC_PDRAMSCR1                          (R_SYSC_BASE + R_SYSC_PDRAMSCR1_OFFSET)
#define R_SYSC_VBRSABAR                           (R_SYSC_BASE + R_SYSC_VBRSABAR_OFFSET)
#define R_SYSC_VBRPABARS                          (R_SYSC_BASE + R_SYSC_VBRPABARS_OFFSET)
#define R_SYSC_CGFSAR                             (R_SYSC_BASE + R_SYSC_CGFSAR_OFFSET)
#define R_SYSC_RSTSAR                             (R_SYSC_BASE + R_SYSC_RSTSAR_OFFSET)
#define R_SYSC_LPMSAR                             (R_SYSC_BASE + R_SYSC_LPMSAR_OFFSET)
#define R_SYSC_PVDSAR                             (R_SYSC_BASE + R_SYSC_PVDSAR_OFFSET)
#define R_SYSC_BBFSAR                             (R_SYSC_BASE + R_SYSC_BBFSAR_OFFSET)
#define R_SYSC_DPFSAR                             (R_SYSC_BASE + R_SYSC_DPFSAR_OFFSET)
#define R_SYSC_RSCSAR                             (R_SYSC_BASE + R_SYSC_RSCSAR_OFFSET)
#define R_SYSC_PRCR_S                             (R_SYSC_BASE + R_SYSC_PRCR_S_OFFSET)
#define R_SYSC_LOCOCR                             (R_SYSC_BASE + R_SYSC_LOCOCR_OFFSET)
#define R_SYSC_LOCOUTCR                           (R_SYSC_BASE + R_SYSC_LOCOUTCR_OFFSET)
#define R_SYSC_DPSBYCR                            (R_SYSC_BASE + R_SYSC_DPSBYCR_OFFSET)
#define R_SYSC_DPSWCR                             (R_SYSC_BASE + R_SYSC_DPSWCR_OFFSET)
#define R_SYSC_DPSIER0                            (R_SYSC_BASE + R_SYSC_DPSIER0_OFFSET)
#define R_SYSC_DPSIER1                            (R_SYSC_BASE + R_SYSC_DPSIER1_OFFSET)
#define R_SYSC_DPSIER2                            (R_SYSC_BASE + R_SYSC_DPSIER2_OFFSET)
#define R_SYSC_DPSIER3                            (R_SYSC_BASE + R_SYSC_DPSIER3_OFFSET)
#define R_SYSC_DPSIFR0                            (R_SYSC_BASE + R_SYSC_DPSIFR0_OFFSET)
#define R_SYSC_DPSIFR1                            (R_SYSC_BASE + R_SYSC_DPSIFR1_OFFSET)
#define R_SYSC_DPSIFR2                            (R_SYSC_BASE + R_SYSC_DPSIFR2_OFFSET)
#define R_SYSC_DPSIFR3                            (R_SYSC_BASE + R_SYSC_DPSIFR3_OFFSET)
#define R_SYSC_DPSIEGR0                           (R_SYSC_BASE + R_SYSC_DPSIEGR0_OFFSET)
#define R_SYSC_DPSIEGR1                           (R_SYSC_BASE + R_SYSC_DPSIEGR1_OFFSET)
#define R_SYSC_DPSIEGR2                           (R_SYSC_BASE + R_SYSC_DPSIEGR2_OFFSET)
#define R_SYSC_SYOCDCR                            (R_SYSC_BASE + R_SYSC_SYOCDCR_OFFSET)
#define R_SYSC_RSTSR0                             (R_SYSC_BASE + R_SYSC_RSTSR0_OFFSET)
#define R_SYSC_RSTSR2                             (R_SYSC_BASE + R_SYSC_RSTSR2_OFFSET)
#define R_SYSC_MOMCR                              (R_SYSC_BASE + R_SYSC_MOMCR_OFFSET)
#define R_SYSC_FWEPROR                            (R_SYSC_BASE + R_SYSC_FWEPROR_OFFSET)
#define R_SYSC_PVDCMPCR(n)                        (R_SYSC_BASE + R_SYSC_PVDCMPCR_OFFSET + (n)*0x00000004)
#define R_SYSC_PVDCR0(n)                          (R_SYSC_BASE + R_SYSC_PVDCR0_OFFSET + (n)*0x00000004)
#define R_SYSC_VBATTMNSELR                        (R_SYSC_BASE + R_SYSC_VBATTMNSELR_OFFSET)
#define R_SYSC_VBTBPCR1                           (R_SYSC_BASE + R_SYSC_VBTBPCR1_OFFSET)
#define R_SYSC_LPSCR                              (R_SYSC_BASE + R_SYSC_LPSCR_OFFSET)
#define R_SYSC_SSCR1                              (R_SYSC_BASE + R_SYSC_SSCR1_OFFSET)
#define R_SYSC_LVOCR                              (R_SYSC_BASE + R_SYSC_LVOCR_OFFSET)
#define R_SYSC_SYRSTMSK0                          (R_SYSC_BASE + R_SYSC_SYRSTMSK0_OFFSET)
#define R_SYSC_SYRSTMSK2                          (R_SYSC_BASE + R_SYSC_SYRSTMSK2_OFFSET)
#define R_SYSC_PLL1LDOCR                          (R_SYSC_BASE + R_SYSC_PLL1LDOCR_OFFSET)
#define R_SYSC_PLL2LDOCR                          (R_SYSC_BASE + R_SYSC_PLL2LDOCR_OFFSET)
#define R_SYSC_HOCOLDOCR                          (R_SYSC_BASE + R_SYSC_HOCOLDOCR_OFFSET)
#define R_SYSC_PVDFCR(n)                          (R_SYSC_BASE + R_SYSC_PVDFCR_OFFSET + (n)*0x00000004)
#define R_SYSC_SOSCCR                             (R_SYSC_BASE + R_SYSC_SOSCCR_OFFSET)
#define R_SYSC_SOMCR                              (R_SYSC_BASE + R_SYSC_SOMCR_OFFSET)
#define R_SYSC_VBTBER                             (R_SYSC_BASE + R_SYSC_VBTBER_OFFSET)
#define R_SYSC_VBTBPCR2                           (R_SYSC_BASE + R_SYSC_VBTBPCR2_OFFSET)
#define R_SYSC_VBTBPSR                            (R_SYSC_BASE + R_SYSC_VBTBPSR_OFFSET)
#define R_SYSC_VBTADSR                            (R_SYSC_BASE + R_SYSC_VBTADSR_OFFSET)
#define R_SYSC_VBTADCR1                           (R_SYSC_BASE + R_SYSC_VBTADCR1_OFFSET)
#define R_SYSC_VBTADCR2                           (R_SYSC_BASE + R_SYSC_VBTADCR2_OFFSET)
#define R_SYSC_VBTICTLR                           (R_SYSC_BASE + R_SYSC_VBTICTLR_OFFSET)
#define R_SYSC_VBTICTLR2                          (R_SYSC_BASE + R_SYSC_VBTICTLR2_OFFSET)
#define R_SYSC_VBTIMONR                           (R_SYSC_BASE + R_SYSC_VBTIMONR_OFFSET)
#define R_SYSC_VBTBKR(n)                          (R_SYSC_BASE + R_SYSC_VBTBKR_OFFSET + (n)*0x00000001)

/* Register bit definitions */
/* SCKDIVCR Register bit definitions */
#define R_SYSC_SCKDIVCR_PCKD_SHIFT                (0)  /* Peripheral Module Clock D (PCLKD) Select */
#define R_SYSC_SCKDIVCR_PCKD_MASK                 0xf
#  define R_SYSC_SCKDIVCR_PCKD_0000                       (0 << R_SYSC_SCKDIVCR_PCKD_SHIFT)  /* x 1/1 */
#  define R_SYSC_SCKDIVCR_PCKD_0001                       (1 << R_SYSC_SCKDIVCR_PCKD_SHIFT)  /* x 1/2 */
#  define R_SYSC_SCKDIVCR_PCKD_0010                       (2 << R_SYSC_SCKDIVCR_PCKD_SHIFT)  /* x 1/4 */
#  define R_SYSC_SCKDIVCR_PCKD_0011                       (3 << R_SYSC_SCKDIVCR_PCKD_SHIFT)  /* x 1/8 */
#  define R_SYSC_SCKDIVCR_PCKD_0100                       (4 << R_SYSC_SCKDIVCR_PCKD_SHIFT)  /* x 1/16 */
#  define R_SYSC_SCKDIVCR_PCKD_0101                       (5 << R_SYSC_SCKDIVCR_PCKD_SHIFT)  /* x 1/32 */
#  define R_SYSC_SCKDIVCR_PCKD_0110                       (6 << R_SYSC_SCKDIVCR_PCKD_SHIFT)  /* x 1/64 */
#  define R_SYSC_SCKDIVCR_PCKD_1000                       (8 << R_SYSC_SCKDIVCR_PCKD_SHIFT)  /* x 1/3 */
#  define R_SYSC_SCKDIVCR_PCKD_1001                       (9 << R_SYSC_SCKDIVCR_PCKD_SHIFT)  /* x 1/6 */
#  define R_SYSC_SCKDIVCR_PCKD_1010                       (10 << R_SYSC_SCKDIVCR_PCKD_SHIFT)  /* x 1/12 */

#define R_SYSC_SCKDIVCR_PCKC_SHIFT                (4)  /* Peripheral Module Clock C (PCLKC) Select */
#define R_SYSC_SCKDIVCR_PCKC_MASK                 0xf0
#  define R_SYSC_SCKDIVCR_PCKC_0000                       (0 << R_SYSC_SCKDIVCR_PCKC_SHIFT)  /* x 1/1 */
#  define R_SYSC_SCKDIVCR_PCKC_0001                       (1 << R_SYSC_SCKDIVCR_PCKC_SHIFT)  /* x 1/2 */
#  define R_SYSC_SCKDIVCR_PCKC_0010                       (2 << R_SYSC_SCKDIVCR_PCKC_SHIFT)  /* x 1/4 */
#  define R_SYSC_SCKDIVCR_PCKC_0011                       (3 << R_SYSC_SCKDIVCR_PCKC_SHIFT)  /* x 1/8 */
#  define R_SYSC_SCKDIVCR_PCKC_0100                       (4 << R_SYSC_SCKDIVCR_PCKC_SHIFT)  /* x 1/16 */
#  define R_SYSC_SCKDIVCR_PCKC_0101                       (5 << R_SYSC_SCKDIVCR_PCKC_SHIFT)  /* x 1/32 */
#  define R_SYSC_SCKDIVCR_PCKC_0110                       (6 << R_SYSC_SCKDIVCR_PCKC_SHIFT)  /* x 1/64 */
#  define R_SYSC_SCKDIVCR_PCKC_1000                       (8 << R_SYSC_SCKDIVCR_PCKC_SHIFT)  /* x 1/3 */
#  define R_SYSC_SCKDIVCR_PCKC_1001                       (9 << R_SYSC_SCKDIVCR_PCKC_SHIFT)  /* x 1/6 */
#  define R_SYSC_SCKDIVCR_PCKC_1010                       (10 << R_SYSC_SCKDIVCR_PCKC_SHIFT)  /* x 1/12 */

#define R_SYSC_SCKDIVCR_PCKB_SHIFT                (8)  /* Peripheral Module Clock B (PCLKB) Select */
#define R_SYSC_SCKDIVCR_PCKB_MASK                 0xf00
#  define R_SYSC_SCKDIVCR_PCKB_0000                       (0 << R_SYSC_SCKDIVCR_PCKB_SHIFT)  /* x 1/1 */
#  define R_SYSC_SCKDIVCR_PCKB_0001                       (1 << R_SYSC_SCKDIVCR_PCKB_SHIFT)  /* x 1/2 */
#  define R_SYSC_SCKDIVCR_PCKB_0010                       (2 << R_SYSC_SCKDIVCR_PCKB_SHIFT)  /* x 1/4 */
#  define R_SYSC_SCKDIVCR_PCKB_0011                       (3 << R_SYSC_SCKDIVCR_PCKB_SHIFT)  /* x 1/8 */
#  define R_SYSC_SCKDIVCR_PCKB_0100                       (4 << R_SYSC_SCKDIVCR_PCKB_SHIFT)  /* x 1/16 */
#  define R_SYSC_SCKDIVCR_PCKB_0101                       (5 << R_SYSC_SCKDIVCR_PCKB_SHIFT)  /* x 1/32 */
#  define R_SYSC_SCKDIVCR_PCKB_0110                       (6 << R_SYSC_SCKDIVCR_PCKB_SHIFT)  /* x 1/64 */
#  define R_SYSC_SCKDIVCR_PCKB_1000                       (8 << R_SYSC_SCKDIVCR_PCKB_SHIFT)  /* x 1/3 */
#  define R_SYSC_SCKDIVCR_PCKB_1001                       (9 << R_SYSC_SCKDIVCR_PCKB_SHIFT)  /* x 1/6 */
#  define R_SYSC_SCKDIVCR_PCKB_1010                       (10 << R_SYSC_SCKDIVCR_PCKB_SHIFT)  /* x 1/12 */

#define R_SYSC_SCKDIVCR_PCKA_SHIFT                (12)  /* Peripheral Module Clock A (PCLKA) Select */
#define R_SYSC_SCKDIVCR_PCKA_MASK                 0xf000
#  define R_SYSC_SCKDIVCR_PCKA_0000                       (0 << R_SYSC_SCKDIVCR_PCKA_SHIFT)  /* x 1/1 */
#  define R_SYSC_SCKDIVCR_PCKA_0001                       (1 << R_SYSC_SCKDIVCR_PCKA_SHIFT)  /* x 1/2 */
#  define R_SYSC_SCKDIVCR_PCKA_0010                       (2 << R_SYSC_SCKDIVCR_PCKA_SHIFT)  /* x 1/4 */
#  define R_SYSC_SCKDIVCR_PCKA_0011                       (3 << R_SYSC_SCKDIVCR_PCKA_SHIFT)  /* x 1/8 */
#  define R_SYSC_SCKDIVCR_PCKA_0100                       (4 << R_SYSC_SCKDIVCR_PCKA_SHIFT)  /* x 1/16 */
#  define R_SYSC_SCKDIVCR_PCKA_0101                       (5 << R_SYSC_SCKDIVCR_PCKA_SHIFT)  /* x 1/32 */
#  define R_SYSC_SCKDIVCR_PCKA_0110                       (6 << R_SYSC_SCKDIVCR_PCKA_SHIFT)  /* x 1/64 */
#  define R_SYSC_SCKDIVCR_PCKA_1000                       (8 << R_SYSC_SCKDIVCR_PCKA_SHIFT)  /* x 1/3 */
#  define R_SYSC_SCKDIVCR_PCKA_1001                       (9 << R_SYSC_SCKDIVCR_PCKA_SHIFT)  /* x 1/6 */
#  define R_SYSC_SCKDIVCR_PCKA_1010                       (10 << R_SYSC_SCKDIVCR_PCKA_SHIFT)  /* x 1/12 */

#define R_SYSC_SCKDIVCR_BCK_SHIFT                 (16)  /* Unnecessary clock (BCLK) Select */
#define R_SYSC_SCKDIVCR_BCK_MASK                  0xf0000
#  define R_SYSC_SCKDIVCR_BCK_0000                        (0 << R_SYSC_SCKDIVCR_BCK_SHIFT)  /* x 1/1 */
#  define R_SYSC_SCKDIVCR_BCK_0001                        (1 << R_SYSC_SCKDIVCR_BCK_SHIFT)  /* x 1/2 */
#  define R_SYSC_SCKDIVCR_BCK_0010                        (2 << R_SYSC_SCKDIVCR_BCK_SHIFT)  /* x 1/4 */
#  define R_SYSC_SCKDIVCR_BCK_0011                        (3 << R_SYSC_SCKDIVCR_BCK_SHIFT)  /* x 1/8 */
#  define R_SYSC_SCKDIVCR_BCK_0100                        (4 << R_SYSC_SCKDIVCR_BCK_SHIFT)  /* x 1/16 */
#  define R_SYSC_SCKDIVCR_BCK_0101                        (5 << R_SYSC_SCKDIVCR_BCK_SHIFT)  /* x 1/32 */
#  define R_SYSC_SCKDIVCR_BCK_0110                        (6 << R_SYSC_SCKDIVCR_BCK_SHIFT)  /* x 1/64 */
#  define R_SYSC_SCKDIVCR_BCK_1000                        (8 << R_SYSC_SCKDIVCR_BCK_SHIFT)  /* x 1/3 */
#  define R_SYSC_SCKDIVCR_BCK_1001                        (9 << R_SYSC_SCKDIVCR_BCK_SHIFT)  /* x 1/6 */
#  define R_SYSC_SCKDIVCR_BCK_1010                        (10 << R_SYSC_SCKDIVCR_BCK_SHIFT)  /* x 1/12 */

#define R_SYSC_SCKDIVCR_ICK_SHIFT                 (24)  /* System Clock (ICLK) Select */
#define R_SYSC_SCKDIVCR_ICK_MASK                  0xf000000
#  define R_SYSC_SCKDIVCR_ICK_0000                        (0 << R_SYSC_SCKDIVCR_ICK_SHIFT)  /* x 1/1 */
#  define R_SYSC_SCKDIVCR_ICK_0001                        (1 << R_SYSC_SCKDIVCR_ICK_SHIFT)  /* x 1/2 */
#  define R_SYSC_SCKDIVCR_ICK_0010                        (2 << R_SYSC_SCKDIVCR_ICK_SHIFT)  /* x 1/4 */
#  define R_SYSC_SCKDIVCR_ICK_0011                        (3 << R_SYSC_SCKDIVCR_ICK_SHIFT)  /* x 1/8 */
#  define R_SYSC_SCKDIVCR_ICK_0100                        (4 << R_SYSC_SCKDIVCR_ICK_SHIFT)  /* x 1/16 */
#  define R_SYSC_SCKDIVCR_ICK_0101                        (5 << R_SYSC_SCKDIVCR_ICK_SHIFT)  /* x 1/32 */
#  define R_SYSC_SCKDIVCR_ICK_0110                        (6 << R_SYSC_SCKDIVCR_ICK_SHIFT)  /* x 1/64 */
#  define R_SYSC_SCKDIVCR_ICK_1000                        (8 << R_SYSC_SCKDIVCR_ICK_SHIFT)  /* x 1/3 */
#  define R_SYSC_SCKDIVCR_ICK_1001                        (9 << R_SYSC_SCKDIVCR_ICK_SHIFT)  /* x 1/6 */
#  define R_SYSC_SCKDIVCR_ICK_1010                        (10 << R_SYSC_SCKDIVCR_ICK_SHIFT)  /* x 1/12 */

#define R_SYSC_SCKDIVCR_FCK_SHIFT                 (28)  /* FlashIF Clock (FCLK) Select */
#define R_SYSC_SCKDIVCR_FCK_MASK                  0xf0000000
#  define R_SYSC_SCKDIVCR_FCK_0000                        (0 << R_SYSC_SCKDIVCR_FCK_SHIFT)  /* x 1/1 */
#  define R_SYSC_SCKDIVCR_FCK_0001                        (1 << R_SYSC_SCKDIVCR_FCK_SHIFT)  /* x 1/2 */
#  define R_SYSC_SCKDIVCR_FCK_0010                        (2 << R_SYSC_SCKDIVCR_FCK_SHIFT)  /* x 1/4 */
#  define R_SYSC_SCKDIVCR_FCK_0011                        (3 << R_SYSC_SCKDIVCR_FCK_SHIFT)  /* x 1/8 */
#  define R_SYSC_SCKDIVCR_FCK_0100                        (4 << R_SYSC_SCKDIVCR_FCK_SHIFT)  /* x 1/16 */
#  define R_SYSC_SCKDIVCR_FCK_0101                        (5 << R_SYSC_SCKDIVCR_FCK_SHIFT)  /* x 1/32 */
#  define R_SYSC_SCKDIVCR_FCK_0110                        (6 << R_SYSC_SCKDIVCR_FCK_SHIFT)  /* x 1/64 */
#  define R_SYSC_SCKDIVCR_FCK_1000                        (8 << R_SYSC_SCKDIVCR_FCK_SHIFT)  /* x 1/3 */
#  define R_SYSC_SCKDIVCR_FCK_1001                        (9 << R_SYSC_SCKDIVCR_FCK_SHIFT)  /* x 1/6 */
#  define R_SYSC_SCKDIVCR_FCK_1010                        (10 << R_SYSC_SCKDIVCR_FCK_SHIFT)  /* x 1/12 */

#define R_SYSC_SCKDIVCR_PCKE_SHIFT                (20)  /* Peripheral Module Clock E (PCLKE) Select */
#define R_SYSC_SCKDIVCR_PCKE_MASK                 0xf00000

/* SCKDIVCR2 Register bit definitions */
#define R_SYSC_SCKDIVCR2_CPUCK_SHIFT              (0)  /* CPU Clock (CPUCLK) Select */
#define R_SYSC_SCKDIVCR2_CPUCK_MASK               0xf
#  define R_SYSC_SCKDIVCR2_CPUCK_0000                     (0 << R_SYSC_SCKDIVCR2_CPUCK_SHIFT)  /* x 1/1 */
#  define R_SYSC_SCKDIVCR2_CPUCK_0001                     (1 << R_SYSC_SCKDIVCR2_CPUCK_SHIFT)  /* x 1/2 */
#  define R_SYSC_SCKDIVCR2_CPUCK_0010                     (2 << R_SYSC_SCKDIVCR2_CPUCK_SHIFT)  /* x 1/4 */
#  define R_SYSC_SCKDIVCR2_CPUCK_0011                     (3 << R_SYSC_SCKDIVCR2_CPUCK_SHIFT)  /* x 1/8 */
#  define R_SYSC_SCKDIVCR2_CPUCK_0100                     (4 << R_SYSC_SCKDIVCR2_CPUCK_SHIFT)  /* x 1/16 */
#  define R_SYSC_SCKDIVCR2_CPUCK_0101                     (5 << R_SYSC_SCKDIVCR2_CPUCK_SHIFT)  /* x 1/32 */
#  define R_SYSC_SCKDIVCR2_CPUCK_0110                     (6 << R_SYSC_SCKDIVCR2_CPUCK_SHIFT)  /* x 1/64 */
#  define R_SYSC_SCKDIVCR2_CPUCK_1000                     (8 << R_SYSC_SCKDIVCR2_CPUCK_SHIFT)  /* x 1/3 */
#  define R_SYSC_SCKDIVCR2_CPUCK_1001                     (9 << R_SYSC_SCKDIVCR2_CPUCK_SHIFT)  /* x 1/6 */
#  define R_SYSC_SCKDIVCR2_CPUCK_1010                     (10 << R_SYSC_SCKDIVCR2_CPUCK_SHIFT)  /* x 1/12 */

/* SCKSCR Register bit definitions */
#define R_SYSC_SCKSCR_CKSEL_SHIFT                 (0)  /* Clock Source Select */
#define R_SYSC_SCKSCR_CKSEL_MASK                  0x7
#  define R_SYSC_SCKSCR_CKSEL_000                         (0 << R_SYSC_SCKSCR_CKSEL_SHIFT)  /* HOCO */
#  define R_SYSC_SCKSCR_CKSEL_001                         (1 << R_SYSC_SCKSCR_CKSEL_SHIFT)  /* MOCO (Value after reset) */
#  define R_SYSC_SCKSCR_CKSEL_010                         (2 << R_SYSC_SCKSCR_CKSEL_SHIFT)  /* Setting prohibited */
#  define R_SYSC_SCKSCR_CKSEL_011                         (3 << R_SYSC_SCKSCR_CKSEL_SHIFT)  /* Main clock oscillator (MOSC) */
#  define R_SYSC_SCKSCR_CKSEL_100                         (4 << R_SYSC_SCKSCR_CKSEL_SHIFT)  /* Sub-clock oscillator (SOSC) */
#  define R_SYSC_SCKSCR_CKSEL_101                         (5 << R_SYSC_SCKSCR_CKSEL_SHIFT)  /* PLL1 output clock P (PLL1P) */
#  define R_SYSC_SCKSCR_CKSEL_110                         (6 << R_SYSC_SCKSCR_CKSEL_SHIFT)  /* Setting prohibited */
#  define R_SYSC_SCKSCR_CKSEL_111                         (7 << R_SYSC_SCKSCR_CKSEL_SHIFT)  /* Setting prohibited */

/* PLLCCR Register bit definitions */
#define R_SYSC_PLLCCR_PLIDIV_SHIFT                (0)  /* PLL1 Input Frequency Division Ratio Select */
#define R_SYSC_PLLCCR_PLIDIV_MASK                 0x3
#  define R_SYSC_PLLCCR_PLIDIV_00                         (0 << R_SYSC_PLLCCR_PLIDIV_SHIFT)  /* 1/1 */
#  define R_SYSC_PLLCCR_PLIDIV_01                         (1 << R_SYSC_PLLCCR_PLIDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_PLLCCR_PLIDIV_10                         (2 << R_SYSC_PLLCCR_PLIDIV_SHIFT)  /* 1/3 */
#  define R_SYSC_PLLCCR_PLIDIV_11                         (3 << R_SYSC_PLLCCR_PLIDIV_SHIFT)  /* 1/4 */

#define R_SYSC_PLLCCR_PLSRCSEL                    (1 << 4)  /* PLL1 Clock Source Select */

#define R_SYSC_PLLCCR_PLLMULNF_SHIFT              (6)  /* PLL1 Frequency Multiplication Fractional Factor Select */
#define R_SYSC_PLLCCR_PLLMULNF_MASK               0xc0
#  define R_SYSC_PLLCCR_PLLMULNF_00                       (0 << R_SYSC_PLLCCR_PLLMULNF_SHIFT)  /* 0.00 (Value after reset) */
#  define R_SYSC_PLLCCR_PLLMULNF_01                       (1 << R_SYSC_PLLCCR_PLLMULNF_SHIFT)  /* 0.33 (1/3) */
#  define R_SYSC_PLLCCR_PLLMULNF_10                       (2 << R_SYSC_PLLCCR_PLLMULNF_SHIFT)  /* 0.66 (2/3) */
#  define R_SYSC_PLLCCR_PLLMULNF_11                       (3 << R_SYSC_PLLCCR_PLLMULNF_SHIFT)  /* 0.50 (1/2) */

#define R_SYSC_PLLCCR_PLLMUL_SHIFT                (8)  /* PLL1 Frequency Multiplication Factor Select */
#define R_SYSC_PLLCCR_PLLMUL_MASK                 0xff00

/* PLLCR Register bit definitions */
#define R_SYSC_PLLCR_PLLSTP                       (1 << 0)  /* PLL1 Stop Control */

/* MOSCCR Register bit definitions */
#define R_SYSC_MOSCCR_MOSTP                       (1 << 0)  /* Main Clock Oscillator Stop */

/* HOCOCR Register bit definitions */
#define R_SYSC_HOCOCR_HCSTP                       (1 << 0)  /* HOCO Stop */

/* HOCOCR2 Register bit definitions */
#define R_SYSC_HOCOCR2_HCFRQ0_SHIFT               (0)  /* HOCO Frequency Setting 0 */
#define R_SYSC_HOCOCR2_HCFRQ0_MASK                0x7
#  define R_SYSC_HOCOCR2_HCFRQ0_000                       (0 << R_SYSC_HOCOCR2_HCFRQ0_SHIFT)  /* 16MHz */
#  define R_SYSC_HOCOCR2_HCFRQ0_001                       (1 << R_SYSC_HOCOCR2_HCFRQ0_SHIFT)  /* 18MHz */
#  define R_SYSC_HOCOCR2_HCFRQ0_010                       (2 << R_SYSC_HOCOCR2_HCFRQ0_SHIFT)  /* 20MHz */
#  define R_SYSC_HOCOCR2_HCFRQ0_100                       (4 << R_SYSC_HOCOCR2_HCFRQ0_SHIFT)  /* 32MHz */
#  define R_SYSC_HOCOCR2_HCFRQ0_111                       (7 << R_SYSC_HOCOCR2_HCFRQ0_SHIFT)  /* 48MHz */

/* MOCOCR Register bit definitions */
#define R_SYSC_MOCOCR_MCSTP                       (1 << 0)  /* MOCO Stop */

/* FLLCR1 Register bit definitions */
#define R_SYSC_FLLCR1_FLLEN                       (1 << 0)  /* FLL Enable */

/* FLLCR2 Register bit definitions */
#define R_SYSC_FLLCR2_FLLCNTL_SHIFT               (0)  /* FLL Multiplication Control */
#define R_SYSC_FLLCR2_FLLCNTL_MASK                0x7ff

/* OSCSF Register bit definitions */
#define R_SYSC_OSCSF_HOCOSF                       (1 << 0)  /* HOCO Clock Oscillation Stabilization Flag */

#define R_SYSC_OSCSF_MOSCSF                       (1 << 3)  /* Main Clock Oscillation Stabilization Flag */

#define R_SYSC_OSCSF_PLLSF                        (1 << 5)  /* PLL1 Clock Oscillation Stabilization Flag */

#define R_SYSC_OSCSF_PLL2SF                       (1 << 6)  /* PLL2 Clock Oscillation Stabilization Flag */

/* CKOCR Register bit definitions */
#define R_SYSC_CKOCR_CKOSEL_SHIFT                 (0)  /* Clock Out Source Select */
#define R_SYSC_CKOCR_CKOSEL_MASK                  0x7
#  define R_SYSC_CKOCR_CKOSEL_000                         (0 << R_SYSC_CKOCR_CKOSEL_SHIFT)  /* HOCO */
#  define R_SYSC_CKOCR_CKOSEL_001                         (1 << R_SYSC_CKOCR_CKOSEL_SHIFT)  /* MOCO (Value after reset) */
#  define R_SYSC_CKOCR_CKOSEL_010                         (2 << R_SYSC_CKOCR_CKOSEL_SHIFT)  /* LOCO */
#  define R_SYSC_CKOCR_CKOSEL_011                         (3 << R_SYSC_CKOCR_CKOSEL_SHIFT)  /* MOSC */
#  define R_SYSC_CKOCR_CKOSEL_100                         (4 << R_SYSC_CKOCR_CKOSEL_SHIFT)  /* SOSC */

#define R_SYSC_CKOCR_CKODIV_SHIFT                 (4)  /* Clock Output Frequency Division Ratio */
#define R_SYSC_CKOCR_CKODIV_MASK                  0x70
#  define R_SYSC_CKOCR_CKODIV_000                         (0 << R_SYSC_CKOCR_CKODIV_SHIFT)  /* x 1/1 */
#  define R_SYSC_CKOCR_CKODIV_001                         (1 << R_SYSC_CKOCR_CKODIV_SHIFT)  /* x 1/2 */
#  define R_SYSC_CKOCR_CKODIV_010                         (2 << R_SYSC_CKOCR_CKODIV_SHIFT)  /* x 1/4 */
#  define R_SYSC_CKOCR_CKODIV_011                         (3 << R_SYSC_CKOCR_CKODIV_SHIFT)  /* x 1/8 */
#  define R_SYSC_CKOCR_CKODIV_100                         (4 << R_SYSC_CKOCR_CKODIV_SHIFT)  /* x 1/16 */
#  define R_SYSC_CKOCR_CKODIV_101                         (5 << R_SYSC_CKOCR_CKODIV_SHIFT)  /* x 1/32 */
#  define R_SYSC_CKOCR_CKODIV_110                         (6 << R_SYSC_CKOCR_CKODIV_SHIFT)  /* x 1/64 */
#  define R_SYSC_CKOCR_CKODIV_111                         (7 << R_SYSC_CKOCR_CKODIV_SHIFT)  /* x 1/128 */

#define R_SYSC_CKOCR_CKOEN                        (1 << 7)  /* Clock Out Enable */

/* TRCKCR Register bit definitions */
#define R_SYSC_TRCKCR_TRCK_SHIFT                  (0)  /* Trace Clock operating frequency select */
#define R_SYSC_TRCKCR_TRCK_MASK                   0xf
#  define R_SYSC_TRCKCR_TRCK_0000                         (0 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/1 */
#  define R_SYSC_TRCKCR_TRCK_0001                         (1 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/2 */
#  define R_SYSC_TRCKCR_TRCK_0010                         (2 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/4 (Value after reset) */
#  define R_SYSC_TRCKCR_TRCK_0011                         (3 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/8 */
#  define R_SYSC_TRCKCR_TRCK_0100                         (4 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/16 */
#  define R_SYSC_TRCKCR_TRCK_0101                         (5 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/32 */
#  define R_SYSC_TRCKCR_TRCK_0110                         (6 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/64 */
#  define R_SYSC_TRCKCR_TRCK_0111                         (7 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/128 */
#  define R_SYSC_TRCKCR_TRCK_1000                         (8 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/256 */
#  define R_SYSC_TRCKCR_TRCK_1001                         (9 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/3 */
#  define R_SYSC_TRCKCR_TRCK_1010                         (10 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/6 */
#  define R_SYSC_TRCKCR_TRCK_1011                         (11 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/12 */

#define R_SYSC_TRCKCR_TRCKSEL                     (1 << 4)  /* Trace Clock source select */

#define R_SYSC_TRCKCR_TRCKEN                      (1 << 7)  /* Trace Clock operating Enable */

/* OSTDCR Register bit definitions */
#define R_SYSC_OSTDCR_OSTDIE                      (1 << 0)  /* Oscillation Stop Detection Interrupt Enable */

#define R_SYSC_OSTDCR_OSTDE                       (1 << 7)  /* Oscillation Stop Detection Function Enable */

/* OSTDSR Register bit definitions */
#define R_SYSC_OSTDSR_OSTDF                       (1 << 0)  /* Oscillation Stop Detection Flag */

/* OSCMONR Register bit definitions */
#define R_SYSC_OSCMONR_MOCOMON                    (1 << 1)  /* MOCO operation monitor */

#define R_SYSC_OSCMONR_LOCOMON                    (1 << 2)  /* LOCO operation monitor */

/* PLL2CCR Register bit definitions */
#define R_SYSC_PLL2CCR_PL2IDIV_SHIFT              (0)  /* PLL2 Input Frequency Division Ratio Select */
#define R_SYSC_PLL2CCR_PL2IDIV_MASK               0x3
#  define R_SYSC_PLL2CCR_PL2IDIV_00                       (0 << R_SYSC_PLL2CCR_PL2IDIV_SHIFT)  /* 1/1 (Value after reset) */
#  define R_SYSC_PLL2CCR_PL2IDIV_01                       (1 << R_SYSC_PLL2CCR_PL2IDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_PLL2CCR_PL2IDIV_10                       (2 << R_SYSC_PLL2CCR_PL2IDIV_SHIFT)  /* 1/3 */
#  define R_SYSC_PLL2CCR_PL2IDIV_11                       (3 << R_SYSC_PLL2CCR_PL2IDIV_SHIFT)  /* 1/4 */

#define R_SYSC_PLL2CCR_PL2SRCSEL                  (1 << 4)  /* PLL2 Clock Source Select */

#define R_SYSC_PLL2CCR_PLL2MULNF_SHIFT            (6)  /* PLL2 Frequency Multiplication Fractional Factor Select */
#define R_SYSC_PLL2CCR_PLL2MULNF_MASK             0xc0
#  define R_SYSC_PLL2CCR_PLL2MULNF_00                     (0 << R_SYSC_PLL2CCR_PLL2MULNF_SHIFT)  /* 0.00 (Value after reset) */
#  define R_SYSC_PLL2CCR_PLL2MULNF_01                     (1 << R_SYSC_PLL2CCR_PLL2MULNF_SHIFT)  /* 0.33 (1/3) */
#  define R_SYSC_PLL2CCR_PLL2MULNF_10                     (2 << R_SYSC_PLL2CCR_PLL2MULNF_SHIFT)  /* 0.66 (2/3) */
#  define R_SYSC_PLL2CCR_PLL2MULNF_11                     (3 << R_SYSC_PLL2CCR_PLL2MULNF_SHIFT)  /* 0.50 (1/2) */

#define R_SYSC_PLL2CCR_PLL2MUL_SHIFT              (8)  /* PLL2 Frequency Multiplication Factor Select */
#define R_SYSC_PLL2CCR_PLL2MUL_MASK               0xff00

/* PLL2CR Register bit definitions */
#define R_SYSC_PLL2CR_PLL2STP                     (1 << 0)  /* PLL2 Stop Control */

/* PLLCCR2 Register bit definitions */
#define R_SYSC_PLLCCR2_PLODIVP_SHIFT              (0)  /* PLL1 Output Frequency Division Ratio Select for output clock P */
#define R_SYSC_PLLCCR2_PLODIVP_MASK               0xf
#  define R_SYSC_PLLCCR2_PLODIVP_0001                     (1 << R_SYSC_PLLCCR2_PLODIVP_SHIFT)  /* × 1/2 */
#  define R_SYSC_PLLCCR2_PLODIVP_0011                     (3 << R_SYSC_PLLCCR2_PLODIVP_SHIFT)  /* × 1/4 */
#  define R_SYSC_PLLCCR2_PLODIVP_0101                     (5 << R_SYSC_PLLCCR2_PLODIVP_SHIFT)  /* × 1/6 (Value after reset) */
#  define R_SYSC_PLLCCR2_PLODIVP_0111                     (7 << R_SYSC_PLLCCR2_PLODIVP_SHIFT)  /* × 1/8 */
#  define R_SYSC_PLLCCR2_PLODIVP_1111                     (15 << R_SYSC_PLLCCR2_PLODIVP_SHIFT)  /* × 1/16 */

#define R_SYSC_PLLCCR2_PLODIVQ_SHIFT              (4)  /* PLL1 Output Frequency Division Ratio Select for output clock Q */
#define R_SYSC_PLLCCR2_PLODIVQ_MASK               0xf0
#  define R_SYSC_PLLCCR2_PLODIVQ_0001                     (1 << R_SYSC_PLLCCR2_PLODIVQ_SHIFT)  /* × 1/2 */
#  define R_SYSC_PLLCCR2_PLODIVQ_0010                     (2 << R_SYSC_PLLCCR2_PLODIVQ_SHIFT)  /* × 1/3 */
#  define R_SYSC_PLLCCR2_PLODIVQ_0011                     (3 << R_SYSC_PLLCCR2_PLODIVQ_SHIFT)  /* × 1/4 */
#  define R_SYSC_PLLCCR2_PLODIVQ_0100                     (4 << R_SYSC_PLLCCR2_PLODIVQ_SHIFT)  /* × 1/5 */
#  define R_SYSC_PLLCCR2_PLODIVQ_0101                     (5 << R_SYSC_PLLCCR2_PLODIVQ_SHIFT)  /* × 1/6 (Value after reset) */
#  define R_SYSC_PLLCCR2_PLODIVQ_0111                     (7 << R_SYSC_PLLCCR2_PLODIVQ_SHIFT)  /* × 1/8 */
#  define R_SYSC_PLLCCR2_PLODIVQ_1000                     (8 << R_SYSC_PLLCCR2_PLODIVQ_SHIFT)  /* × 1/9 */

#define R_SYSC_PLLCCR2_PLODIVR_SHIFT              (8)  /* PLL1 Output Frequency Division Ratio Select for output clock R */
#define R_SYSC_PLLCCR2_PLODIVR_MASK               0xf00
#  define R_SYSC_PLLCCR2_PLODIVR_0001                     (1 << R_SYSC_PLLCCR2_PLODIVR_SHIFT)  /* × 1/2 */
#  define R_SYSC_PLLCCR2_PLODIVR_0010                     (2 << R_SYSC_PLLCCR2_PLODIVR_SHIFT)  /* × 1/3 */
#  define R_SYSC_PLLCCR2_PLODIVR_0011                     (3 << R_SYSC_PLLCCR2_PLODIVR_SHIFT)  /* × 1/4 */
#  define R_SYSC_PLLCCR2_PLODIVR_0100                     (4 << R_SYSC_PLLCCR2_PLODIVR_SHIFT)  /* × 1/5 */
#  define R_SYSC_PLLCCR2_PLODIVR_0101                     (5 << R_SYSC_PLLCCR2_PLODIVR_SHIFT)  /* × 1/6 (Value after reset) */
#  define R_SYSC_PLLCCR2_PLODIVR_0111                     (7 << R_SYSC_PLLCCR2_PLODIVR_SHIFT)  /* × 1/8 */
#  define R_SYSC_PLLCCR2_PLODIVR_1000                     (8 << R_SYSC_PLLCCR2_PLODIVR_SHIFT)  /* × 1/9 */

/* PLL2CCR2 Register bit definitions */
#define R_SYSC_PLL2CCR2_PL2ODIVP_SHIFT            (0)  /* PLL2 Output Frequency Division Ratio Select for output clock P */
#define R_SYSC_PLL2CCR2_PL2ODIVP_MASK             0xf
#  define R_SYSC_PLL2CCR2_PL2ODIVP_0001                   (1 << R_SYSC_PLL2CCR2_PL2ODIVP_SHIFT)  /* × 1/2 */
#  define R_SYSC_PLL2CCR2_PL2ODIVP_0011                   (3 << R_SYSC_PLL2CCR2_PL2ODIVP_SHIFT)  /* × 1/4 */
#  define R_SYSC_PLL2CCR2_PL2ODIVP_0101                   (5 << R_SYSC_PLL2CCR2_PL2ODIVP_SHIFT)  /* × 1/6 (Value after reset) */
#  define R_SYSC_PLL2CCR2_PL2ODIVP_0111                   (7 << R_SYSC_PLL2CCR2_PL2ODIVP_SHIFT)  /* × 1/8 */
#  define R_SYSC_PLL2CCR2_PL2ODIVP_1111                   (15 << R_SYSC_PLL2CCR2_PL2ODIVP_SHIFT)  /* × 1/16 */

#define R_SYSC_PLL2CCR2_PL2ODIVQ_SHIFT            (4)  /* PLL2 Output Frequency Division Ratio Select for output clock Q */
#define R_SYSC_PLL2CCR2_PL2ODIVQ_MASK             0xf0
#  define R_SYSC_PLL2CCR2_PL2ODIVQ_0001                   (1 << R_SYSC_PLL2CCR2_PL2ODIVQ_SHIFT)  /* × 1/2 */
#  define R_SYSC_PLL2CCR2_PL2ODIVQ_0010                   (2 << R_SYSC_PLL2CCR2_PL2ODIVQ_SHIFT)  /* × 1/3 */
#  define R_SYSC_PLL2CCR2_PL2ODIVQ_0011                   (3 << R_SYSC_PLL2CCR2_PL2ODIVQ_SHIFT)  /* × 1/4 */
#  define R_SYSC_PLL2CCR2_PL2ODIVQ_0100                   (4 << R_SYSC_PLL2CCR2_PL2ODIVQ_SHIFT)  /* × 1/5 */
#  define R_SYSC_PLL2CCR2_PL2ODIVQ_0101                   (5 << R_SYSC_PLL2CCR2_PL2ODIVQ_SHIFT)  /* × 1/6 (Value after reset) */
#  define R_SYSC_PLL2CCR2_PL2ODIVQ_0111                   (7 << R_SYSC_PLL2CCR2_PL2ODIVQ_SHIFT)  /* × 1/8 */
#  define R_SYSC_PLL2CCR2_PL2ODIVQ_1000                   (8 << R_SYSC_PLL2CCR2_PL2ODIVQ_SHIFT)  /* × 1/9 */

#define R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT            (8)  /* PLL2 Output Frequency Division Ratio Select for output clock R */
#define R_SYSC_PLL2CCR2_PL2ODIVR_MASK             0xf00
#  define R_SYSC_PLL2CCR2_PL2ODIVR_0001                   (1 << R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT)  /* × 1/2 */
#  define R_SYSC_PLL2CCR2_PL2ODIVR_0010                   (2 << R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT)  /* × 1/3 */
#  define R_SYSC_PLL2CCR2_PL2ODIVR_0011                   (3 << R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT)  /* × 1/4 */
#  define R_SYSC_PLL2CCR2_PL2ODIVR_0100                   (4 << R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT)  /* × 1/5 */
#  define R_SYSC_PLL2CCR2_PL2ODIVR_0101                   (5 << R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT)  /* × 1/6 (Value after reset) */
#  define R_SYSC_PLL2CCR2_PL2ODIVR_0111                   (7 << R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT)  /* × 1/8 */
#  define R_SYSC_PLL2CCR2_PL2ODIVR_1000                   (8 << R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT)  /* × 1/9 */

/* SCICKDIVCR Register bit definitions */
#define R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT          (0)  /* SCI clock (SCICLK) Division Select */
#define R_SYSC_SCICKDIVCR_SCICKDIV_MASK           0x7
#  define R_SYSC_SCICKDIVCR_SCICKDIV_000                  (0 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/1 (Value after reset) */
#  define R_SYSC_SCICKDIVCR_SCICKDIV_001                  (1 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_SCICKDIVCR_SCICKDIV_010                  (2 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_SCICKDIVCR_SCICKDIV_011                  (3 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_SCICKDIVCR_SCICKDIV_100                  (4 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_SCICKDIVCR_SCICKDIV_101                  (5 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/3 */
#  define R_SYSC_SCICKDIVCR_SCICKDIV_110                  (6 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/5 */

#define R_SYSC_SCICKDIVCR_CKDIV_SHIFT             (0)  /* Clock Division Select */
#define R_SYSC_SCICKDIVCR_CKDIV_MASK              0x7

/* SCICKCR Register bit definitions */
#define R_SYSC_SCICKCR_SCICKSEL_SHIFT             (0)  /* SCI clock (SCICLK) Source Select */
#define R_SYSC_SCICKCR_SCICKSEL_MASK              0xf
#  define R_SYSC_SCICKCR_SCICKSEL_0000                    (0 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* HOCO */
#  define R_SYSC_SCICKCR_SCICKSEL_0001                    (1 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* MOCO (Value after reset) */
#  define R_SYSC_SCICKCR_SCICKSEL_0010                    (2 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* LOCO */
#  define R_SYSC_SCICKCR_SCICKSEL_0011                    (3 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* Main clock oscillator */
#  define R_SYSC_SCICKCR_SCICKSEL_0100                    (4 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* Sub-clock oscillator */
#  define R_SYSC_SCICKCR_SCICKSEL_0101                    (5 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* PLL1P */
#  define R_SYSC_SCICKCR_SCICKSEL_0110                    (6 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* PLL2P */
#  define R_SYSC_SCICKCR_SCICKSEL_0111                    (7 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* PLL1Q */
#  define R_SYSC_SCICKCR_SCICKSEL_1000                    (8 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* PLL1R */
#  define R_SYSC_SCICKCR_SCICKSEL_1001                    (9 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* PLL2Q */
#  define R_SYSC_SCICKCR_SCICKSEL_1010                    (10 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* PLL2R */

#define R_SYSC_SCICKCR_SCICKSREQ                  (1 << 6)  /* SCI clock (SCICLK) Switching Request */

#define R_SYSC_SCICKCR_SCICKSRDY                  (1 << 7)  /* SCI clock (SCICLK) Switching Ready state flag */

#define R_SYSC_SCICKCR_CKSREQ                     (1 << 6)  /* Clock Switching Request */

#define R_SYSC_SCICKCR_CKSRDY                     (1 << 7)  /* Clock Switching Ready state flag */

/* SPICKDIVCR Register bit definitions */
#define R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT          (0)  /* SPI clock (SPICLK) Division Select */
#define R_SYSC_SPICKDIVCR_SPICKDIV_MASK           0x7
#  define R_SYSC_SPICKDIVCR_SPICKDIV_000                  (0 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/1 (Value after reset) */
#  define R_SYSC_SPICKDIVCR_SPICKDIV_001                  (1 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_SPICKDIVCR_SPICKDIV_010                  (2 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_SPICKDIVCR_SPICKDIV_011                  (3 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_SPICKDIVCR_SPICKDIV_100                  (4 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_SPICKDIVCR_SPICKDIV_101                  (5 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/3 */
#  define R_SYSC_SPICKDIVCR_SPICKDIV_110                  (6 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/5 */

#define R_SYSC_SPICKDIVCR_CKDIV_SHIFT             (0)  /* Clock Division Select */
#define R_SYSC_SPICKDIVCR_CKDIV_MASK              0x7

/* SPICKCR Register bit definitions */
#define R_SYSC_SPICKCR_SPICKSEL_SHIFT             (0)  /* SPI clock (SPICLK) Source Select */
#define R_SYSC_SPICKCR_SPICKSEL_MASK              0xf
#  define R_SYSC_SPICKCR_SPICKSEL_0000                    (0 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* HOCO */
#  define R_SYSC_SPICKCR_SPICKSEL_0001                    (1 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* MOCO (Value after reset) */
#  define R_SYSC_SPICKCR_SPICKSEL_0010                    (2 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* LOCO */
#  define R_SYSC_SPICKCR_SPICKSEL_0011                    (3 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* Main clock oscillator */
#  define R_SYSC_SPICKCR_SPICKSEL_0100                    (4 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* Sub-clock oscillator */
#  define R_SYSC_SPICKCR_SPICKSEL_0101                    (5 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* PLL1P */
#  define R_SYSC_SPICKCR_SPICKSEL_0110                    (6 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* PLL2P */
#  define R_SYSC_SPICKCR_SPICKSEL_0111                    (7 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* PLL1Q */
#  define R_SYSC_SPICKCR_SPICKSEL_1000                    (8 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* PLL1R */
#  define R_SYSC_SPICKCR_SPICKSEL_1001                    (9 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* PLL2Q */
#  define R_SYSC_SPICKCR_SPICKSEL_1010                    (10 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* PLL2R */

#define R_SYSC_SPICKCR_SPICKSREQ                  (1 << 6)  /* SPI clock (SPICLK) Switching Request */

#define R_SYSC_SPICKCR_SPICKSRDY                  (1 << 7)  /* SPI clock (SPICLK) Switching Ready state flag */

#define R_SYSC_SPICKCR_CKSEL_SHIFT                (0)  /* Clock Source Select */
#define R_SYSC_SPICKCR_CKSEL_MASK                 0xf

#define R_SYSC_SPICKCR_CKSREQ                     (1 << 6)  /* Clock Switching Request */

#define R_SYSC_SPICKCR_CKSRDY                     (1 << 7)  /* Clock Switching Ready state flag */

/* MOCOUTCR Register bit definitions */
#define R_SYSC_MOCOUTCR_MOCOUTRM_SHIFT            (0)  /* MOCO User Trimming */
#define R_SYSC_MOCOUTCR_MOCOUTRM_MASK             0xff

/* HOCOUTCR Register bit definitions */
#define R_SYSC_HOCOUTCR_HOCOUTRM_SHIFT            (0)  /* HOCO User Trimming */
#define R_SYSC_HOCOUTCR_HOCOUTRM_MASK             0xff

/* USBCKDIVCR Register bit definitions */
#define R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT          (0)  /* USB Clock (USBCLK) Division Select */
#define R_SYSC_USBCKDIVCR_USBCKDIV_MASK           0x7
#  define R_SYSC_USBCKDIVCR_USBCKDIV_000                  (0 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/1 */
#  define R_SYSC_USBCKDIVCR_USBCKDIV_001                  (1 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_USBCKDIVCR_USBCKDIV_010                  (2 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_USBCKDIVCR_USBCKDIV_011                  (3 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_USBCKDIVCR_USBCKDIV_100                  (4 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_USBCKDIVCR_USBCKDIV_101                  (5 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/3 */
#  define R_SYSC_USBCKDIVCR_USBCKDIV_110                  (6 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/5 */

/* OCTACKDIVCR Register bit definitions */
#define R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT        (0)  /* Octal-SPI Clock (OCTACLK) Division Select */
#define R_SYSC_OCTACKDIVCR_OCTACKDIV_MASK         0x7
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_000                (0 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/1 (Value after reset) */
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_001                (1 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_010                (2 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_011                (3 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_100                (4 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_101                (5 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/3 */
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_110                (6 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/5 */

/* CANFDCKDIVCR Register bit definitions */
#define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT      (0)  /* CANFD core clock (CANFDCLK) Division Select */
#define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_MASK       0x7
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_000              (0 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/1 (Value after reset) */
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_001              (1 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_010              (2 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_011              (3 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_100              (4 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_101              (5 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/3 */
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_110              (6 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/5 */

/* USBCKCR Register bit definitions */
#define R_SYSC_USBCKCR_USBCKSEL_SHIFT             (0)  /* USB Clock (USBCLK) Source Select */
#define R_SYSC_USBCKCR_USBCKSEL_MASK              0xf
#  define R_SYSC_USBCKCR_USBCKSEL_0000                    (0 << R_SYSC_USBCKCR_USBCKSEL_SHIFT)  /* HOCO */
#  define R_SYSC_USBCKCR_USBCKSEL_0001                    (1 << R_SYSC_USBCKCR_USBCKSEL_SHIFT)  /* MOCO (Value after reset) */
#  define R_SYSC_USBCKCR_USBCKSEL_0011                    (3 << R_SYSC_USBCKCR_USBCKSEL_SHIFT)  /* Main clock oscillator */
#  define R_SYSC_USBCKCR_USBCKSEL_0101                    (5 << R_SYSC_USBCKCR_USBCKSEL_SHIFT)  /* PLL1P */
#  define R_SYSC_USBCKCR_USBCKSEL_0110                    (6 << R_SYSC_USBCKCR_USBCKSEL_SHIFT)  /* PLL2P */
#  define R_SYSC_USBCKCR_USBCKSEL_0111                    (7 << R_SYSC_USBCKCR_USBCKSEL_SHIFT)  /* PLL1Q */
#  define R_SYSC_USBCKCR_USBCKSEL_1000                    (8 << R_SYSC_USBCKCR_USBCKSEL_SHIFT)  /* PLL1R */
#  define R_SYSC_USBCKCR_USBCKSEL_1001                    (9 << R_SYSC_USBCKCR_USBCKSEL_SHIFT)  /* PLL2Q */
#  define R_SYSC_USBCKCR_USBCKSEL_1010                    (10 << R_SYSC_USBCKCR_USBCKSEL_SHIFT)  /* PLL2R */

#define R_SYSC_USBCKCR_USBCKSREQ                  (1 << 6)  /* USB Clock (USBCLK) Switching Request */

#define R_SYSC_USBCKCR_USBCKSRDY                  (1 << 7)  /* USB Clock (USBCLK) Switching Ready state flag */

/* OCTACKCR Register bit definitions */
#define R_SYSC_OCTACKCR_OCTACKSEL_SHIFT           (0)  /* Octal-SPI Clock (OCTACLK) Source Select */
#define R_SYSC_OCTACKCR_OCTACKSEL_MASK            0xf
#  define R_SYSC_OCTACKCR_OCTACKSEL_0000                  (0 << R_SYSC_OCTACKCR_OCTACKSEL_SHIFT)  /* HOCO */
#  define R_SYSC_OCTACKCR_OCTACKSEL_0001                  (1 << R_SYSC_OCTACKCR_OCTACKSEL_SHIFT)  /* MOCO (Value after reset) */
#  define R_SYSC_OCTACKCR_OCTACKSEL_0010                  (2 << R_SYSC_OCTACKCR_OCTACKSEL_SHIFT)  /* LOCO */
#  define R_SYSC_OCTACKCR_OCTACKSEL_0011                  (3 << R_SYSC_OCTACKCR_OCTACKSEL_SHIFT)  /* Main clock oscillator */
#  define R_SYSC_OCTACKCR_OCTACKSEL_0100                  (4 << R_SYSC_OCTACKCR_OCTACKSEL_SHIFT)  /* Sub-clock oscillator */
#  define R_SYSC_OCTACKCR_OCTACKSEL_0101                  (5 << R_SYSC_OCTACKCR_OCTACKSEL_SHIFT)  /* PLL1P */
#  define R_SYSC_OCTACKCR_OCTACKSEL_0110                  (6 << R_SYSC_OCTACKCR_OCTACKSEL_SHIFT)  /* PLL2P */
#  define R_SYSC_OCTACKCR_OCTACKSEL_0111                  (7 << R_SYSC_OCTACKCR_OCTACKSEL_SHIFT)  /* PLL1Q */
#  define R_SYSC_OCTACKCR_OCTACKSEL_1000                  (8 << R_SYSC_OCTACKCR_OCTACKSEL_SHIFT)  /* PLL1R */
#  define R_SYSC_OCTACKCR_OCTACKSEL_1001                  (9 << R_SYSC_OCTACKCR_OCTACKSEL_SHIFT)  /* PLL2Q */
#  define R_SYSC_OCTACKCR_OCTACKSEL_1010                  (10 << R_SYSC_OCTACKCR_OCTACKSEL_SHIFT)  /* PLL2R */

#define R_SYSC_OCTACKCR_OCTACKSREQ                (1 << 6)  /* Octal-SPI Clock (OCTACLK) Switching Request */

#define R_SYSC_OCTACKCR_OCTACKSRDY                (1 << 7)  /* Octal-SPI Clock (OCTACLK) Switching Ready state flag */

/* CANFDCKCR Register bit definitions */
#define R_SYSC_CANFDCKCR_CANFDCKSEL_SHIFT         (0)  /* CANFD Core Clock (CANFDCLK) Source Select */
#define R_SYSC_CANFDCKCR_CANFDCKSEL_MASK          0xf
#  define R_SYSC_CANFDCKCR_CANFDCKSEL_0000                (0 << R_SYSC_CANFDCKCR_CANFDCKSEL_SHIFT)  /* HOCO */
#  define R_SYSC_CANFDCKCR_CANFDCKSEL_0001                (1 << R_SYSC_CANFDCKCR_CANFDCKSEL_SHIFT)  /* MOCO (Value after reset) */
#  define R_SYSC_CANFDCKCR_CANFDCKSEL_0010                (2 << R_SYSC_CANFDCKCR_CANFDCKSEL_SHIFT)  /* LOCO */
#  define R_SYSC_CANFDCKCR_CANFDCKSEL_0011                (3 << R_SYSC_CANFDCKCR_CANFDCKSEL_SHIFT)  /* Main clock oscillator */
#  define R_SYSC_CANFDCKCR_CANFDCKSEL_0100                (4 << R_SYSC_CANFDCKCR_CANFDCKSEL_SHIFT)  /* Sub-clock oscillator */
#  define R_SYSC_CANFDCKCR_CANFDCKSEL_0101                (5 << R_SYSC_CANFDCKCR_CANFDCKSEL_SHIFT)  /* PLL1P */
#  define R_SYSC_CANFDCKCR_CANFDCKSEL_0110                (6 << R_SYSC_CANFDCKCR_CANFDCKSEL_SHIFT)  /* PLL2P */
#  define R_SYSC_CANFDCKCR_CANFDCKSEL_0111                (7 << R_SYSC_CANFDCKCR_CANFDCKSEL_SHIFT)  /* PLL1Q */
#  define R_SYSC_CANFDCKCR_CANFDCKSEL_1000                (8 << R_SYSC_CANFDCKCR_CANFDCKSEL_SHIFT)  /* PLL1R */
#  define R_SYSC_CANFDCKCR_CANFDCKSEL_1001                (9 << R_SYSC_CANFDCKCR_CANFDCKSEL_SHIFT)  /* PLL2Q */
#  define R_SYSC_CANFDCKCR_CANFDCKSEL_1010                (10 << R_SYSC_CANFDCKCR_CANFDCKSEL_SHIFT)  /* PLL2R */

#define R_SYSC_CANFDCKCR_CANFDCKSREQ              (1 << 6)  /* CANFD Core Clock (CANFDCLK) Switching Request */

#define R_SYSC_CANFDCKCR_CANFDCKSRDY              (1 << 7)  /* CANFD Core clock (CANFDCLK) Switching Ready state flag */

/* MOSCSCR Register bit definitions */
#define R_SYSC_MOSCSCR_MOSCSOKP                   (1 << 0)  /* Main Clock Oscillator Standby Oscillation Keep select */

/* HOCOSCR Register bit definitions */
#define R_SYSC_HOCOSCR_HOCOSOKP                   (1 << 0)  /* HOCO Standby Oscillation Keep select. */

/* OPCCR Register bit definitions */
#define R_SYSC_OPCCR_OPCM_SHIFT                   (0)  /* Operating Power Control Mode Select */
#define R_SYSC_OPCCR_OPCM_MASK                    0x3
#  define R_SYSC_OPCCR_OPCM_00                            (0 << R_SYSC_OPCCR_OPCM_SHIFT)  /* High-speed mode */
#  define R_SYSC_OPCCR_OPCM_01                            (1 << R_SYSC_OPCCR_OPCM_SHIFT)  /* Setting prohibited */
#  define R_SYSC_OPCCR_OPCM_10                            (2 << R_SYSC_OPCCR_OPCM_SHIFT)  /* Setting prohibited */
#  define R_SYSC_OPCCR_OPCM_11                            (3 << R_SYSC_OPCCR_OPCM_SHIFT)  /* Low-speed mode */

#define R_SYSC_OPCCR_OPCMTSF                      (1 << 4)  /* Operating Power Control Mode Transition Status Flag */

/* MOSCWTCR Register bit definitions */
#define R_SYSC_MOSCWTCR_MSTS_SHIFT                (0)  /* Main Clock Oscillator Wait Time Setting */
#define R_SYSC_MOSCWTCR_MSTS_MASK                 0xf
#  define R_SYSC_MOSCWTCR_MSTS_0X0                        (0 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 3 cycles (11.4 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X1                        (0 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 35 cycles (133.5 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X2                        (0 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 67 cycles (255.6 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X3                        (0 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 131 cycles (499.7 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X4                        (0 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 259 cycles (988.0 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X5                        (0 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 547 cycles (2086.6 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X6                        (0 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 1059 cycles (4039.8 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X7                        (0 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 2147 cycles (8190.2 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X8                        (0 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 4291 cycles (16368.9 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X9                        (0 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 8163 cycles (31139.4 us) */

/* RSTSR1 Register bit definitions */
#define R_SYSC_RSTSR1_IWDTRF                      (1 << 0)  /* Independent Watchdog Timer Reset Detect Flag */

#define R_SYSC_RSTSR1_WDT0RF                      (1 << 1)  /* Watchdog Timer Reset Detect Flag */

#define R_SYSC_RSTSR1_SWRF                        (1 << 2)  /* Software Reset Detect Flag */

#define R_SYSC_RSTSR1_CLU0RF                      (1 << 4)  /* CPU Lockup Reset Detect Flag */

#define R_SYSC_RSTSR1_BUSRF                       (1 << 10)  /* Bus Error Reset Detect Flag */

#define R_SYSC_RSTSR1_CMRF                        (1 << 14)  /* Common Memory Error Reset Detect Flag */

#define R_SYSC_RSTSR1_WDTRF                       (1 << 1)  /* Watchdog Timer0 Reset Detect Flag. NOTE: Writable only to clear the flag. Confirm the value is 1 and then write 0. */

#define R_SYSC_RSTSR1_LM0RF                       (1 << 5)  /* Local memory 0 error Reset Detect Flag. NOTE: Writable only to clear the flag. Confirm the value is 1 and then write 0. */

#define R_SYSC_RSTSR1_WDT1RF                      (1 << 17)  /* Watchdog Timer1 Reset Detect Flag. NOTE: Writable only to clear the flag. Confirm the value is 1 and then write 0. */

#define R_SYSC_RSTSR1_LM1RF                       (1 << 21)  /* Local memory 1 error Reset Detect Flag. NOTE: Writable only to clear the flag. Confirm the value is 1 and then write 0. */

#define R_SYSC_RSTSR1_NWRF                        (1 << 22)  /* Network Reset Detect Flag. NOTE: Writable only to clear the flag. Confirm the value is 1 and then write 0. */

/* SYRACCR Register bit definitions */
#define R_SYSC_SYRACCR_BUSY                       (1 << 0)  /* Access Ready monitor */

/* PVDCR Register bit definitions */
#define R_SYSC_PVDCR_IDTSEL_SHIFT                 (0)  /* Voltage Monitor m Interrupt Generation Condition Select */
#define R_SYSC_PVDCR_IDTSEL_MASK                  0x3

#define R_SYSC_PVDCR_IRQSEL                       (1 << 2)  /* Voltage Monitor m Interrupt Type Select */

/* PVDSR Register bit definitions */
#define R_SYSC_PVDSR_DET                          (1 << 0)  /* Voltage Monitor m Voltage Change Detection Flag */

#define R_SYSC_PVDSR_MON                          (1 << 1)  /* Voltage Monitor 1 Signal Monitor Flag */

/* PDRAMSCR0 Register bit definitions */
#define R_SYSC_PDRAMSCR0_RKEEP0                   (1 << 0)  /* Unnecessary Circuit Retention */

#define R_SYSC_PDRAMSCR0_RKEEP1                   (1 << 1)  /* Unnecessary Circuit Retention */

#define R_SYSC_PDRAMSCR0_RKEEP2                   (1 << 2)  /* Unnecessary Circuit Retention */

#define R_SYSC_PDRAMSCR0_RKEEP3                   (1 << 3)  /* RAM Retention */

#define R_SYSC_PDRAMSCR0_RKEEP4                   (1 << 4)  /* RAM Retention */

#define R_SYSC_PDRAMSCR0_RKEEP5                   (1 << 5)  /* RAM Retention */

#define R_SYSC_PDRAMSCR0_RKEEP6                   (1 << 6)  /* RAM Retention */

/* PDRAMSCR1 Register bit definitions */
#define R_SYSC_PDRAMSCR1_RKEEP0                   (1 << 0)  /* RAM Retention */

/* VBRSABAR Register bit definitions */
#define R_SYSC_VBRSABAR_SABA_SHIFT                (0)  /* Boundary address between secure and non-secure */
#define R_SYSC_VBRSABAR_SABA_MASK                 0xffff

/* VBRPABARS Register bit definitions */
#define R_SYSC_VBRPABARS_PABAS_SHIFT              (0)  /* Boundary address between privileged and unprivileged. */
#define R_SYSC_VBRPABARS_PABAS_MASK               0xffff

/* CGFSAR Register bit definitions */
#define R_SYSC_CGFSAR_NONSEC00                    (1 << 0)  /* Non Secure Attribute bit 00 */

#define R_SYSC_CGFSAR_NONSEC02                    (1 << 2)  /* Non Secure Attribute bit 02 */

#define R_SYSC_CGFSAR_NONSEC03                    (1 << 3)  /* Non Secure Attribute bit 03 */

#define R_SYSC_CGFSAR_NONSEC04                    (1 << 4)  /* Non Secure Attribute bit 04 */

#define R_SYSC_CGFSAR_NONSEC05                    (1 << 5)  /* Non Secure Attribute bit 05 */

#define R_SYSC_CGFSAR_NONSEC06                    (1 << 6)  /* Non Secure Attribute bit 06 */

#define R_SYSC_CGFSAR_NONSEC07                    (1 << 7)  /* Non Secure Attribute bit 07 */

#define R_SYSC_CGFSAR_NONSEC08                    (1 << 8)  /* Non Secure Attribute bit 08 */

#define R_SYSC_CGFSAR_NONSEC09                    (1 << 9)  /* Non Secure Attribute bit 09 */

#define R_SYSC_CGFSAR_NONSEC11                    (1 << 11)  /* Non Secure Attribute bit 11 */

#define R_SYSC_CGFSAR_NONSEC16                    (1 << 16)  /* Non Secure Attribute bit 16 */

#define R_SYSC_CGFSAR_NONSEC17                    (1 << 17)  /* Non Secure Attribute bit 17 */

#define R_SYSC_CGFSAR_NONSEC18                    (1 << 18)  /* Non Secure Attribute bit 18 */

#define R_SYSC_CGFSAR_NONSEC21                    (1 << 21)  /* Non Secure Attribute bit 21 */

#define R_SYSC_CGFSAR_NONSEC22                    (1 << 22)  /* Non Secure Attribute bit 22 */

#define R_SYSC_CGFSAR_NONSEC12                    (1 << 12)  /* Non-secure Attribute bit 12 */

#define R_SYSC_CGFSAR_NONSEC13                    (1 << 13)  /* Non-secure Attribute bit 13 */

#define R_SYSC_CGFSAR_NONSEC19                    (1 << 19)  /* Non-secure Attribute bit 19 */

#define R_SYSC_CGFSAR_NONSEC20                    (1 << 20)  /* Non-secure Attribute bit 20 */

#define R_SYSC_CGFSAR_NONSEC24                    (1 << 24)  /* Non-secure Attribute bit 24 */

#define R_SYSC_CGFSAR_NONSEC25                    (1 << 25)  /* Non-secure Attribute bit 25 */

#define R_SYSC_CGFSAR_NONSEC26                    (1 << 26)  /* Non-secure Attribute bit 26 */

/* RSTSAR Register bit definitions */
#define R_SYSC_RSTSAR_NONSEC0                     (1 << 0)  /* Non-secure Attribute bit 0 */

#define R_SYSC_RSTSAR_NONSEC1                     (1 << 1)  /* Non-secure Attribute bit 1 */

#define R_SYSC_RSTSAR_NONSEC2                     (1 << 2)  /* Non-secure Attribute bit 2 */

#define R_SYSC_RSTSAR_NONSEC3                     (1 << 3)  /* Non-secure Attribute bit 3 */

/* LPMSAR Register bit definitions */
#define R_SYSC_LPMSAR_NONSEC0                     (1 << 0)  /* Non-secure Attribute bit 0 */

#define R_SYSC_LPMSAR_NONSEC1                     (1 << 1)  /* Non-secure Attribute bit 1 */

#define R_SYSC_LPMSAR_NONSEC2                     (1 << 2)  /* Non-secure Attribute bit 2 */

#define R_SYSC_LPMSAR_NONSEC8                     (1 << 8)  /* Non-secure Attribute bit 8 */

#define R_SYSC_LPMSAR_NONSEC17                    (1 << 17)  /* Non-secure Attribute bit 17 */

#define R_SYSC_LPMSAR_NONSEC18                    (1 << 18)  /* Non-secure Attribute bit 18 */

#define R_SYSC_LPMSAR_NONSEC19                    (1 << 19)  /* Non-secure Attribute bit 19 */

#define R_SYSC_LPMSAR_NONSEC21                    (1 << 21)  /* Non-secure Attribute bit 21 */

#define R_SYSC_LPMSAR_NONSEC3                     (1 << 3)  /* Non-secure Attribute bit 03 */

#define R_SYSC_LPMSAR_NONSEC16                    (1 << 16)  /* Non-secure Attribute bit 16 */

/* PVDSAR Register bit definitions */
#define R_SYSC_PVDSAR_NONSEC0                     (1 << 0)  /* Non Secure Attribute bit 0 */

#define R_SYSC_PVDSAR_NONSEC1                     (1 << 1)  /* Non Secure Attribute bit 1 */

/* BBFSAR Register bit definitions */
#define R_SYSC_BBFSAR_NONSEC0                     (1 << 0)  /* Non Secure Attribute bit 0 */

#define R_SYSC_BBFSAR_NONSEC1                     (1 << 1)  /* Non Secure Attribute bit 1 */

#define R_SYSC_BBFSAR_NONSEC2                     (1 << 2)  /* Non Secure Attribute bit 2 */

#define R_SYSC_BBFSAR_NONSEC3                     (1 << 3)  /* Non Secure Attribute bit 3 */

#define R_SYSC_BBFSAR_NONSEC4                     (1 << 4)  /* Non Secure Attribute bit 4 */

/* DPFSAR Register bit definitions */
#define R_SYSC_DPFSAR_DPFSA0                      (1 << 0)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 0 to 7) */

#define R_SYSC_DPFSAR_DPFSA1                      (1 << 1)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 0 to 7) */

#define R_SYSC_DPFSAR_DPFSA2                      (1 << 2)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 0 to 7) */

#define R_SYSC_DPFSAR_DPFSA3                      (1 << 3)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 0 to 7) */

#define R_SYSC_DPFSAR_DPFSA4                      (1 << 4)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 0 to 7) */

#define R_SYSC_DPFSAR_DPFSA5                      (1 << 5)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 0 to 7) */

#define R_SYSC_DPFSAR_DPFSA6                      (1 << 6)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 0 to 7) */

#define R_SYSC_DPFSAR_DPFSA7                      (1 << 7)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 0 to 7) */

#define R_SYSC_DPFSAR_DPFSA08                     (1 << 8)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 8 to 15) */

#define R_SYSC_DPFSAR_DPFSA09                     (1 << 9)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 8 to 15) */

#define R_SYSC_DPFSAR_DPFSA10                     (1 << 10)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 8 to 15) */

#define R_SYSC_DPFSAR_DPFSA11                     (1 << 11)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 8 to 15) */

#define R_SYSC_DPFSAR_DPFSA12                     (1 << 12)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 8 to 15) */

#define R_SYSC_DPFSAR_DPFSA13                     (1 << 13)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 8 to 15) */

#define R_SYSC_DPFSAR_DPFSA14                     (1 << 14)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 8 to 15) */

#define R_SYSC_DPFSAR_DPFSA15                     (1 << 15)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 8 to 15) */

#define R_SYSC_DPFSAR_DPFSA16                     (1 << 16)  /* Deep Software Standby Interrupt Factor Security Attribute bit 16 */

#define R_SYSC_DPFSAR_DPFSA17                     (1 << 17)  /* Deep Software Standby Interrupt Factor Security Attribute bit 17 */

#define R_SYSC_DPFSAR_DPFSA18                     (1 << 18)  /* Deep Software Standby Interrupt Factor Security Attribute bit 18 */

#define R_SYSC_DPFSAR_DPFSA19                     (1 << 19)  /* Deep Software Standby Interrupt Factor Security Attribute bit 19 */

#define R_SYSC_DPFSAR_DPFSA20                     (1 << 20)  /* Deep Software Standby Interrupt Factor Security Attribute bit 20 */

#define R_SYSC_DPFSAR_DPFSA24                     (1 << 24)  /* Deep Software Standby Interrupt Factor Security Attribute bit 24 */

#define R_SYSC_DPFSAR_DPFSA26                     (1 << 26)  /* Deep Software Standby Interrupt Factor Security Attribute bit 26 */

#define R_SYSC_DPFSAR_DPFSA27                     (1 << 27)  /* Deep Software Standby Interrupt Factor Security Attribute bit 27 */

#define R_SYSC_DPFSAR_DPFSA29                     (1 << 29)  /* Deep Software Standby Interrupt Factor Security Attribute bit 29 */

#define R_SYSC_DPFSAR_DPFSA31                     (1 << 31)  /* Deep Software Standby Interrupt Factor Security Attribute bit 31 */

#define R_SYSC_DPFSAR_DPFSA25                     (1 << 25)  /* Deep Standby Interrupt Factor Security Attribute bit 25 */

/* RSCSAR Register bit definitions */
#define R_SYSC_RSCSAR_RSCSA0                      (1 << 0)  /* Unnecessary Circuit Control Security Attribution bit n (n = 0 to 2) */

#define R_SYSC_RSCSAR_RSCSA1                      (1 << 1)  /* Unnecessary Circuit Control Security Attribution bit n (n = 0 to 2) */

#define R_SYSC_RSCSAR_RSCSA2                      (1 << 2)  /* Unnecessary Circuit Control Security Attribution bit n (n = 0 to 2) */

#define R_SYSC_RSCSAR_RSCSA3                      (1 << 3)  /* RAM Standby Control Security Attribute bit n (n = 3 to 6) */

#define R_SYSC_RSCSAR_RSCSA4                      (1 << 4)  /* RAM Standby Control Security Attribute bit n (n = 3 to 6) */

#define R_SYSC_RSCSAR_RSCSA5                      (1 << 5)  /* RAM Standby Control Security Attribute bit n (n = 3 to 6) */

#define R_SYSC_RSCSAR_RSCSA6                      (1 << 6)  /* RAM Standby Control Security Attribute bit n (n = 3 to 6) */

#define R_SYSC_RSCSAR_RSCSA16                     (1 << 16)  /* RAM Standby Control Security Attribute bit n (n = 16) */

#define R_SYSC_RSCSAR_RSCSA7                      (1 << 7)  /* RAM Standby Control Security Attribute bit 07 */

#define R_SYSC_RSCSAR_RSCSA8                      (1 << 8)  /* RAM Standby Control Security Attribute bit 08 */

#define R_SYSC_RSCSAR_RSCSA9                      (1 << 9)  /* RAM Standby Control Security Attribute bit 09 */

#define R_SYSC_RSCSAR_RSCSA10                     (1 << 10)  /* RAM Standby Control Security Attribute bit 10 */

#define R_SYSC_RSCSAR_RSCSA11                     (1 << 11)  /* RAM Standby Control Security Attribute bit 11 */

#define R_SYSC_RSCSAR_RSCSA12                     (1 << 12)  /* RAM Standby Control Security Attribute bit 12 */

#define R_SYSC_RSCSAR_RSCSA13                     (1 << 13)  /* RAM Standby Control Security Attribute bit 13 */

#define R_SYSC_RSCSAR_RSCSA14                     (1 << 14)  /* RAM Standby Control Security Attribute bit 14 */

#define R_SYSC_RSCSAR_RSCSA17                     (1 << 17)  /* RAM Standby Control Security Attribute bit 17 */

/* PRCR_S Register bit definitions */
#define R_SYSC_PRCR_S_PRC0                        (1 << 0)  /* Enable writing to the registers related to the clock generation circuit */

#define R_SYSC_PRCR_S_PRC1                        (1 << 1)  /* Enable writing to the registers related to the low power modes, and the battery backup function */

#define R_SYSC_PRCR_S_PRC3                        (1 << 3)  /* Enable writing to the registers related to the PVD */

#define R_SYSC_PRCR_S_PRC4                        (1 << 4)  /*  */

#define R_SYSC_PRCR_S_PRC5                        (1 << 5)  /*  */

#define R_SYSC_PRCR_S_PRKEY_SHIFT                 (8)  /* 0xA5: Enables writing to the PRCR_S register. */
#define R_SYSC_PRCR_S_PRKEY_MASK                  0xff00

/* LOCOCR Register bit definitions */
#define R_SYSC_LOCOCR_LCSTP                       (1 << 0)  /* LOCO Stop */

/* LOCOUTCR Register bit definitions */
#define R_SYSC_LOCOUTCR_LOCOUTRM_SHIFT            (0)  /* LOCO User Trimming */
#define R_SYSC_LOCOUTCR_LOCOUTRM_MASK             0xff

/* DPSBYCR Register bit definitions */
#define R_SYSC_DPSBYCR_DCSSMODE                   (1 << 2)  /*  */

#define R_SYSC_DPSBYCR_SRKEEP                     (1 << 4)  /* Standby SRAM Retention */

#define R_SYSC_DPSBYCR_IOKEEP                     (1 << 6)  /* I/O Port Rentention */

#define R_SYSC_DPSBYCR_DPSBY                      (1 << 7)  /* Deep Software Standby */

/* DPSWCR Register bit definitions */
#define R_SYSC_DPSWCR_WTSTS_SHIFT                 (0)  /* Deep Software Wait Standby Time Setting Bit */
#define R_SYSC_DPSWCR_WTSTS_MASK                  0xff
#  define R_SYSC_DPSWCR_WTSTS_0X0B                        (0 << R_SYSC_DPSWCR_WTSTS_SHIFT)  /* Wait cycle for fast recovery */
#  define R_SYSC_DPSWCR_WTSTS_0X9A                        (0 << R_SYSC_DPSWCR_WTSTS_SHIFT)  /* Wait cycle for slow recovery */

/* DPSIER0 Register bit definitions */
#define R_SYSC_DPSIER0_DIRQ0E                     (1 << 0)  /* IRQ0-DS Pin Enable */

#define R_SYSC_DPSIER0_DIRQ1E                     (1 << 1)  /* IRQ1-DS Pin Enable */

#define R_SYSC_DPSIER0_DIRQ2E                     (1 << 2)  /* IRQ2-DS Pin Enable */

#define R_SYSC_DPSIER0_DIRQ3E                     (1 << 3)  /* IRQ3-DS Pin Enable */

#define R_SYSC_DPSIER0_DIRQ4E                     (1 << 4)  /* IRQ4-DS Pin Enable */

#define R_SYSC_DPSIER0_DIRQ5E                     (1 << 5)  /* IRQ5-DS Pin Enable */

#define R_SYSC_DPSIER0_DIRQ6E                     (1 << 6)  /* IRQ6-DS Pin Enable */

#define R_SYSC_DPSIER0_DIRQ7E                     (1 << 7)  /* IRQ7-DS Pin Enable */

/* DPSIER1 Register bit definitions */
#define R_SYSC_DPSIER1_DIRQ8E                     (1 << 0)  /* IRQ8-DS Pin Enable */

#define R_SYSC_DPSIER1_DIRQ9E                     (1 << 1)  /* IRQ9-DS Pin Enable */

#define R_SYSC_DPSIER1_DIRQ10E                    (1 << 2)  /* IRQ10-DS Pin Enable */

#define R_SYSC_DPSIER1_DIRQ11E                    (1 << 3)  /* IRQ11-DS Pin Enable */

#define R_SYSC_DPSIER1_DIRQ12E                    (1 << 4)  /* IRQ12-DS Pin Enable */

#define R_SYSC_DPSIER1_DIRQ13E                    (1 << 5)  /* IRQ13-DS Pin Enable */

#define R_SYSC_DPSIER1_DIRQ14E                    (1 << 6)  /* IRQ14-DS Pin Enable */

#define R_SYSC_DPSIER1_DIRQ15E                    (1 << 7)  /* IRQ15-DS Pin Enable */

/* DPSIER2 Register bit definitions */
#define R_SYSC_DPSIER2_DPVD1IE                    (1 << 0)  /* PVD1 Deep Software Standby Cancel Signal Enable */

#define R_SYSC_DPSIER2_DPVD2IE                    (1 << 1)  /* PVD2 Deep Software Standby Cancel Signal Enable */

#define R_SYSC_DPSIER2_DRTCIIE                    (1 << 2)  /* RTC Interval interrupt Deep Software Standby Cancel Signal Enable */

#define R_SYSC_DPSIER2_DRTCAIE                    (1 << 3)  /* RTC Alarm interrupt Deep Software Standby Cancel Signal Enable */

#define R_SYSC_DPSIER2_DNMIE                      (1 << 4)  /* NMI Pin Deep Software Standby Cancel Signal Enable */

#define R_SYSC_DPSIER2_DTRTCIIE                   (1 << 2)  /* RTC Interval interrupt Deep Standby Cancel Signal Enable */

/* DPSIER3 Register bit definitions */
#define R_SYSC_DPSIER3_DUSBFSIE                   (1 << 0)  /* USBFS Suspend/Resume Deep Software Standby Cancel Signal Enable */

#define R_SYSC_DPSIER3_DULPT0IE                   (1 << 2)  /* ULPT0 Overflow Deep Software Standby Cancel Signal Enable */

#define R_SYSC_DPSIER3_DULPT1IE                   (1 << 3)  /* ULPT1 Overflow Deep Software Standby Cancel Signal Enable */

#define R_SYSC_DPSIER3_DIWDTIE                    (1 << 5)  /* IWDT Underflow Deep Software Standby Cancel Signal Enable */

#define R_SYSC_DPSIER3_DVBATTADIE                 (1 << 7)  /* VBATT Tamper Detection Deep Software Standby Cancel Signal Enable */

#define R_SYSC_DPSIER3_DUSBHSIE                   (1 << 1)  /* USBHS Suspend/Resume Deep Standby Cancel Signal Enable */

/* DPSIFR0 Register bit definitions */
#define R_SYSC_DPSIFR0_DIRQ0F                     (1 << 0)  /* IRQ0-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR0_DIRQ1F                     (1 << 1)  /* IRQ1-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR0_DIRQ2F                     (1 << 2)  /* IRQ2-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR0_DIRQ3F                     (1 << 3)  /* IRQ3-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR0_DIRQ4F                     (1 << 4)  /* IRQ4-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR0_DIRQ5F                     (1 << 5)  /* IRQ5-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR0_DIRQ6F                     (1 << 6)  /* IRQ6-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR0_DIRQ7F                     (1 << 7)  /* IRQ7-DS Pin Deep Software Standby Cancel Flag */

/* DPSIFR1 Register bit definitions */
#define R_SYSC_DPSIFR1_DIRQ8F                     (1 << 0)  /* IRQ8-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR1_DIRQ9F                     (1 << 1)  /* IRQ9-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR1_DIRQ10F                    (1 << 2)  /* IRQ10-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR1_DIRQ11F                    (1 << 3)  /* IRQ11-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR1_DIRQ12F                    (1 << 4)  /* IRQ12-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR1_DIRQ13F                    (1 << 5)  /* IRQ13-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR1_DIRQ14F                    (1 << 6)  /* IRQ14-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR1_DIRQ15F                    (1 << 7)  /* IRQ15-DS Pin Deep Software Standby Cancel Flag */

/* DPSIFR2 Register bit definitions */
#define R_SYSC_DPSIFR2_DPVD1IF                    (1 << 0)  /* PVD1 Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR2_DPVD2IF                    (1 << 1)  /* PVD2 Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR2_DRTCIIF                    (1 << 2)  /* RTC Interval Interrupt Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR2_DRTCAIF                    (1 << 3)  /* RTC Alarm Interrupt Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR2_DNMIF                      (1 << 4)  /* NMI Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR2_DTRTCIIF                   (1 << 2)  /* RTC Interval interrupt Deep Standby Cancel Flag */

/* DPSIFR3 Register bit definitions */
#define R_SYSC_DPSIFR3_DUSBFSIF                   (1 << 0)  /* USBFS Suspend/Resume Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR3_DULPT0IF                   (1 << 2)  /* ULPT0 Overflow Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR3_DULPT1IF                   (1 << 3)  /* ULPT1 Overflow Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR3_DIWDTIF                    (1 << 5)  /* IWDT Underflow Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR3_DVBATTADIF                 (1 << 7)  /* VBATT Tamper Detection Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR3_DUSBHSIF                   (1 << 1)  /* USBHS Suspend/Resume Deep Standby Cancel Flag */

/* DPSIEGR0 Register bit definitions */
#define R_SYSC_DPSIEGR0_DIRQ0EG                   (1 << 0)  /* IRQ0-DS Pin Edge Select */

#define R_SYSC_DPSIEGR0_DIRQ1EG                   (1 << 1)  /* IRQ1-DS Pin Edge Select */

#define R_SYSC_DPSIEGR0_DIRQ2EG                   (1 << 2)  /* IRQ2-DS Pin Edge Select */

#define R_SYSC_DPSIEGR0_DIRQ3EG                   (1 << 3)  /* IRQ3-DS Pin Edge Select */

#define R_SYSC_DPSIEGR0_DIRQ4EG                   (1 << 4)  /* IRQ4-DS Pin Edge Select */

#define R_SYSC_DPSIEGR0_DIRQ5EG                   (1 << 5)  /* IRQ5-DS Pin Edge Select */

#define R_SYSC_DPSIEGR0_DIRQ6EG                   (1 << 6)  /* IRQ6-DS Pin Edge Select */

#define R_SYSC_DPSIEGR0_DIRQ7EG                   (1 << 7)  /* IRQ7-DS Pin Edge Select */

/* DPSIEGR1 Register bit definitions */
#define R_SYSC_DPSIEGR1_DIRQ8EG                   (1 << 0)  /* IRQ8-DS Pin Edge Select */

#define R_SYSC_DPSIEGR1_DIRQ9EG                   (1 << 1)  /* IRQ9-DS Pin Edge Select */

#define R_SYSC_DPSIEGR1_DIRQ10EG                  (1 << 2)  /* IRQ10-DS Pin Edge Select */

#define R_SYSC_DPSIEGR1_DIRQ11EG                  (1 << 3)  /* IRQ11-DS Pin Edge Select */

#define R_SYSC_DPSIEGR1_DIRQ12EG                  (1 << 4)  /* IRQ12-DS Pin Edge Select */

#define R_SYSC_DPSIEGR1_DIRQ13EG                  (1 << 5)  /* IRQ13-DS Pin Edge Select */

#define R_SYSC_DPSIEGR1_DIRQ14EG                  (1 << 6)  /* IRQ14-DS Pin Edge Select */

#define R_SYSC_DPSIEGR1_DIRQ15EG                  (1 << 7)  /* IRQ15-DS Pin Edge Select */

/* DPSIEGR2 Register bit definitions */
#define R_SYSC_DPSIEGR2_DPVD1EG                   (1 << 0)  /* PVD1 Edge Select */

#define R_SYSC_DPSIEGR2_DPVD2EG                   (1 << 1)  /* PVD2 Edge Select */

#define R_SYSC_DPSIEGR2_DNMIEG                    (1 << 4)  /* NMI Pin Edge Select */

/* SYOCDCR Register bit definitions */
#define R_SYSC_SYOCDCR_DBGEN                      (1 << 7)  /* Debugger Enable bit */

#define R_SYSC_SYOCDCR_DOCDF                      (1 << 0)  /* Deep Standby OCD flag */

/* RSTSR0 Register bit definitions */
#define R_SYSC_RSTSR0_PORF                        (1 << 0)  /* Power-On Reset Detect Flag */

#define R_SYSC_RSTSR0_PVD0RF                      (1 << 1)  /* Voltage Monitor 0 Reset Detect Flag */

#define R_SYSC_RSTSR0_PVD1RF                      (1 << 2)  /* Voltage Monitor 1 Reset Detect Flag */

#define R_SYSC_RSTSR0_PVD2RF                      (1 << 3)  /* Voltage Monitor 2 Reset Detect Flag */

#define R_SYSC_RSTSR0_DPSRSTF                     (1 << 7)  /* Deep Software Standby Reset Flag */

#define R_SYSC_RSTSR0_LVD0RF                      (1 << 1)  /* Voltage Monitor 0 Reset Detect Flag. NOTE: Writable only to clear the flag. Confirm the value is 1 and then write 0. */

#define R_SYSC_RSTSR0_LVD1RF                      (1 << 2)  /* Voltage Monitor 1 Reset Detect Flag. NOTE: Writable only to clear the flag. Confirm the value is 1 and then write 0. */

#define R_SYSC_RSTSR0_LVD2RF                      (1 << 3)  /* Voltage Monitor 2 Reset Detect Flag. NOTE: Writable only to clear the flag. Confirm the value is 1 and then write 0. */

#define R_SYSC_RSTSR0_LVD3RF                      (1 << 4)  /* Voltage Monitor 3 Reset Detect Flag. NOTE: Writable only to clear the flag. Confirm the value is 1 and then write 0. */

#define R_SYSC_RSTSR0_LVD4RF                      (1 << 5)  /* Voltage Monitor 4 Reset Detect Flag. NOTE: Writable only to clear the flag. Confirm the value is 1 and then write 0. */

#define R_SYSC_RSTSR0_LVD5RF                      (1 << 6)  /* Voltage Monitor 5 Reset Detect Flag. NOTE: Writable only to clear the flag. Confirm the value is 1 and then write 0. */

/* RSTSR2 Register bit definitions */
#define R_SYSC_RSTSR2_CWSF                        (1 << 0)  /* Cold/Warm Start Determination Flag */

/* MOMCR Register bit definitions */
#define R_SYSC_MOMCR_MODRV0_SHIFT                 (1)  /* Main Clock Oscillator Drive Capability 0 Switching */
#define R_SYSC_MOMCR_MODRV0_MASK                  0xe
#  define R_SYSC_MOMCR_MODRV0_000                         (0 << R_SYSC_MOMCR_MODRV0_SHIFT)  /* 8 MHz */
#  define R_SYSC_MOMCR_MODRV0_011                         (3 << R_SYSC_MOMCR_MODRV0_SHIFT)  /* 8 MHz to 24 MHz */
#  define R_SYSC_MOMCR_MODRV0_101                         (5 << R_SYSC_MOMCR_MODRV0_SHIFT)  /* 8 MHz to 48 MHz */

#define R_SYSC_MOMCR_MOSEL                        (1 << 6)  /* Main Clock Oscillator Switching */

/* FWEPROR Register bit definitions */
#define R_SYSC_FWEPROR_FLWE_SHIFT                 (0)  /* Flash Programming and Erasure */
#define R_SYSC_FWEPROR_FLWE_MASK                  0x3
#  define R_SYSC_FWEPROR_FLWE_00                          (0 << R_SYSC_FWEPROR_FLWE_SHIFT)  /* Prohibits Program, Block Erase, Multi Block Erase, Blank Check, and Configuration set command processing. */
#  define R_SYSC_FWEPROR_FLWE_01                          (1 << R_SYSC_FWEPROR_FLWE_SHIFT)  /* Permits Program, Block Erase, Multi Block Erase, Blank Check, and Configuration set command processing. */
#  define R_SYSC_FWEPROR_FLWE_10                          (2 << R_SYSC_FWEPROR_FLWE_SHIFT)  /* Prohibits Program, Block Erase, Multi Block Erase, Blank Check, and Configuration set command processing. */
#  define R_SYSC_FWEPROR_FLWE_11                          (3 << R_SYSC_FWEPROR_FLWE_SHIFT)  /* Prohibits Program, Block Erase, Multi Block Erase, Blank Check, and Configuration set command processing. */

/* PVDCMPCR Register bit definitions */
#define R_SYSC_PVDCMPCR_PVDLVL_SHIFT              (0)  /* Detection Voltage m Level Select */
#define R_SYSC_PVDCMPCR_PVDLVL_MASK               0x1f
#  define R_SYSC_PVDCMPCR_PVDLVL_0X03                     (0 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 3.86 V (Vdetm_3) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X04                     (0 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 3.14 V (Vdetm_4) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X05                     (0 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 3.10 V (Vdetm_5) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X06                     (0 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 3.08 V (Vdetm_6) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X07                     (0 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 2.85 V (Vdetm_7) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X08                     (0 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 2.83 V (Vdetm_8) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X09                     (0 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 2.80 V (Vdetm_9) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X0A                     (0 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 2.62V (Vdetm_10) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X0B                     (0 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 2.33V (Vdetm_11) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X0C                     (0 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 1.90V (Vdetm_12) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X0D                     (0 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 1.86V (Vdetm_13) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X0E                     (0 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 1.74V (Vdetm_14) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X0F                     (0 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 1.71V (Vdetm_15) */

#define R_SYSC_PVDCMPCR_PVDE                      (1 << 7)  /* Voltage Detection m Enable */

/* PVDCR Register bit definitions */
#define R_SYSC_PVDCR_RIE                          (1 << 0)  /* Voltage Monitor m Interrupt/Reset Enable */

#define R_SYSC_PVDCR_DFDIS                        (1 << 1)  /* Voltage monitor m Digital Filter Disabled Mode Select */

#define R_SYSC_PVDCR_CMPE                         (1 << 2)  /* Voltage Monitor m Circuit Comparison Result Output Enable */

#define R_SYSC_PVDCR_FSAMP_SHIFT                  (4)  /* Sampling Clock Select */
#define R_SYSC_PVDCR_FSAMP_MASK                   0x30
#  define R_SYSC_PVDCR_FSAMP_00                           (0 << R_SYSC_PVDCR_FSAMP_SHIFT)  /* 1/2 LOCO frequency */
#  define R_SYSC_PVDCR_FSAMP_01                           (1 << R_SYSC_PVDCR_FSAMP_SHIFT)  /* 1/4 LOCO frequency */
#  define R_SYSC_PVDCR_FSAMP_10                           (2 << R_SYSC_PVDCR_FSAMP_SHIFT)  /* 1/8 LOCO frequency */
#  define R_SYSC_PVDCR_FSAMP_11                           (3 << R_SYSC_PVDCR_FSAMP_SHIFT)  /* 1/16 LOCO frequency */

#define R_SYSC_PVDCR_RI                           (1 << 6)  /* Voltage Monitor m Circuit Mode Select */

#define R_SYSC_PVDCR_RN                           (1 << 7)  /* Voltage Monitor m Reset Negate Select */

/* VBATTMNSELR Register bit definitions */
#define R_SYSC_VBATTMNSELR_VBTMNSEL               (1 << 0)  /* VBATT Voltage Monitor Function Select Bit */

#define R_SYSC_VBATTMNSELR_VBATTMNSEL             (1 << 0)  /* VBATT Voltage Monitor Function Select Bit */

/* VBTBPCR1 Register bit definitions */
#define R_SYSC_VBTBPCR1_BPWSWSTP                  (1 << 0)  /* Battery Power Supply Switch Stop */

/* LPSCR Register bit definitions */
#define R_SYSC_LPSCR_LPMD_SHIFT                   (0)  /* Low power mode setting bit */
#define R_SYSC_LPSCR_LPMD_MASK                    0xf
#  define R_SYSC_LPSCR_LPMD_0X0                           (0 << R_SYSC_LPSCR_LPMD_SHIFT)  /* System Active */
#  define R_SYSC_LPSCR_LPMD_0X4                           (0 << R_SYSC_LPSCR_LPMD_SHIFT)  /* Software Standby mode */
#  define R_SYSC_LPSCR_LPMD_0X8                           (0 << R_SYSC_LPSCR_LPMD_SHIFT)  /* Deep Software Standby mode 1 */
#  define R_SYSC_LPSCR_LPMD_0X9                           (0 << R_SYSC_LPSCR_LPMD_SHIFT)  /* Deep Software Standby mode 2 */
#  define R_SYSC_LPSCR_LPMD_0XA                           (0 << R_SYSC_LPSCR_LPMD_SHIFT)  /* Deep Software Standby mode 3 */

/* SSCR1 Register bit definitions */
#define R_SYSC_SSCR1_SS1FR                        (1 << 0)  /* Software Standby Fast Return */

/* LVOCR Register bit definitions */
#define R_SYSC_LVOCR_LVO0E                        (1 << 0)  /* Low Voltage Operation 0 Enable */

#define R_SYSC_LVOCR_LVO1E                        (1 << 1)  /* Low Voltage Operation 1 Enable */

/* SYRSTMSK0 Register bit definitions */
#define R_SYSC_SYRSTMSK0_IWDTMASK                 (1 << 0)  /* Independent Watchdog Timer Reset Mask */

#define R_SYSC_SYRSTMSK0_WDT0MASK                 (1 << 1)  /* Watchdog Timer Reset Mask */

#define R_SYSC_SYRSTMSK0_SWMASK                   (1 << 2)  /* Software Reset Mask */

#define R_SYSC_SYRSTMSK0_CLU0MASK                 (1 << 4)  /* CPU Lockup Reset Mask */

#define R_SYSC_SYRSTMSK0_CMMASK                   (1 << 6)  /* Common Memory Error Reset Mask */

#define R_SYSC_SYRSTMSK0_BUSMASK                  (1 << 7)  /* Bus Error Reset Mask */

#define R_SYSC_SYRSTMSK0_CLUP0MASK                (1 << 4)  /* CPU0 Lockup Reset Mask */

#define R_SYSC_SYRSTMSK0_LM0MASK                  (1 << 5)  /* Local memory 0 error Reset Mask */

/* SYRSTMSK2 Register bit definitions */
#define R_SYSC_SYRSTMSK2_PVD1MASK                 (1 << 0)  /* Voltage Monitor 1 Reset Mask */

#define R_SYSC_SYRSTMSK2_PVD2MASK                 (1 << 1)  /* Voltage Monitor 2 Reset Mask */

#define R_SYSC_SYRSTMSK2_LVD1MASK                 (1 << 0)  /* Voltage Monitor 1 Reset Mask */

#define R_SYSC_SYRSTMSK2_LVD2MASK                 (1 << 1)  /* Voltage Monitor 2 Reset Mask */

#define R_SYSC_SYRSTMSK2_LVD3MASK                 (1 << 2)  /* Voltage Monitor 3 Reset Mask */

#define R_SYSC_SYRSTMSK2_LVD4MASK                 (1 << 3)  /* Voltage Monitor 4 Reset Mask */

#define R_SYSC_SYRSTMSK2_LVD5MASK                 (1 << 4)  /* Voltage Monitor 5 Reset Mask */

/* PLL1LDOCR Register bit definitions */
#define R_SYSC_PLL1LDOCR_LDOSTP                   (1 << 0)  /* LDO Stop */

#define R_SYSC_PLL1LDOCR_SKEEP                    (1 << 1)  /* STBY Keep */

/* PLL2LDOCR Register bit definitions */
#define R_SYSC_PLL2LDOCR_LDOSTP                   (1 << 0)  /* LDO Stop */

#define R_SYSC_PLL2LDOCR_SKEEP                    (1 << 1)  /* STBY Keep */

/* HOCOLDOCR Register bit definitions */
#define R_SYSC_HOCOLDOCR_LDOSTP                   (1 << 0)  /* LDO Stop */

#define R_SYSC_HOCOLDOCR_SKEEP                    (1 << 1)  /* STBY Keep */

/* PVDFCR Register bit definitions */
#define R_SYSC_PVDFCR_RHSEL                       (1 << 0)  /* Rise Hysteresis Select */

/* SOSCCR Register bit definitions */
#define R_SYSC_SOSCCR_SOSTP                       (1 << 0)  /* Sub-Clock Oscillator Stop */

/* SOMCR Register bit definitions */
#define R_SYSC_SOMCR_SODRV_SHIFT                  (0)  /* Sub-Clock Oscillator Drive Capability Switching */
#define R_SYSC_SOMCR_SODRV_MASK                   0x3
#  define R_SYSC_SOMCR_SODRV_00                           (0 << R_SYSC_SOMCR_SODRV_SHIFT)  /* Standard (12.5pf) */
#  define R_SYSC_SOMCR_SODRV_01                           (1 << R_SYSC_SOMCR_SODRV_SHIFT)  /* Lowpower mode 1 (9pf) */
#  define R_SYSC_SOMCR_SODRV_10                           (2 << R_SYSC_SOMCR_SODRV_SHIFT)  /* Lowpower mode 2 (7pf) */
#  define R_SYSC_SOMCR_SODRV_11                           (3 << R_SYSC_SOMCR_SODRV_SHIFT)  /* Lowpower mode 3 (4pf) */

#define R_SYSC_SOMCR_SOSEL                        (1 << 6)  /* Sub-Clock Oscillator Switching */

/* VBTBER Register bit definitions */
#define R_SYSC_VBTBER_VBAE                        (1 << 3)  /* VBATT backup register access enable bit */

/* VBTBPCR2 Register bit definitions */
#define R_SYSC_VBTBPCR2_VDETLVL_SHIFT             (0)  /* VDETBAT Level Select */
#define R_SYSC_VBTBPCR2_VDETLVL_MASK              0x7
#  define R_SYSC_VBTBPCR2_VDETLVL_000                     (0 << R_SYSC_VBTBPCR2_VDETLVL_SHIFT)  /* 2.80 V */
#  define R_SYSC_VBTBPCR2_VDETLVL_001                     (1 << R_SYSC_VBTBPCR2_VDETLVL_SHIFT)  /* 2.53 V */
#  define R_SYSC_VBTBPCR2_VDETLVL_010                     (2 << R_SYSC_VBTBPCR2_VDETLVL_SHIFT)  /* 2.10 V */
#  define R_SYSC_VBTBPCR2_VDETLVL_011                     (3 << R_SYSC_VBTBPCR2_VDETLVL_SHIFT)  /* 1.95 V */
#  define R_SYSC_VBTBPCR2_VDETLVL_100                     (4 << R_SYSC_VBTBPCR2_VDETLVL_SHIFT)  /* 1.85 V */
#  define R_SYSC_VBTBPCR2_VDETLVL_101                     (5 << R_SYSC_VBTBPCR2_VDETLVL_SHIFT)  /* 1.75 V */
#  define R_SYSC_VBTBPCR2_VDETLVL_110                     (6 << R_SYSC_VBTBPCR2_VDETLVL_SHIFT)  /* setting prohibited */
#  define R_SYSC_VBTBPCR2_VDETLVL_111                     (7 << R_SYSC_VBTBPCR2_VDETLVL_SHIFT)  /* setting prohibited */

#define R_SYSC_VBTBPCR2_VDETE                     (1 << 4)  /* Voltage drop detection enable */

/* VBTBPSR Register bit definitions */
#define R_SYSC_VBTBPSR_VBPORF                     (1 << 0)  /* VBATT_POR Flag */

#define R_SYSC_VBTBPSR_VBPORM                     (1 << 4)  /* VBATT_POR Monitor */

#define R_SYSC_VBTBPSR_BPWSWM                     (1 << 5)  /* Battery Power Supply Switch Status Monitor */

/* VBTADSR Register bit definitions */
#define R_SYSC_VBTADSR_VBTADF0                    (1 << 0)  /* VBATT Tamper Detection flag 0 */

#define R_SYSC_VBTADSR_VBTADF1                    (1 << 1)  /* VBATT Tamper Detection flag 1 */

#define R_SYSC_VBTADSR_VBTADF2                    (1 << 2)  /* VBATT Tamper Detection flag 2 */

/* VBTADCR1 Register bit definitions */
#define R_SYSC_VBTADCR1_VBTADIE0                  (1 << 0)  /* VBATT Tamper Detection Interrupt Enable 0 */

#define R_SYSC_VBTADCR1_VBTADIE1                  (1 << 1)  /* VBATT Tamper Detection Interrupt Enable 1 */

#define R_SYSC_VBTADCR1_VBTADIE2                  (1 << 2)  /* VBATT Tamper Detection Interrupt Enable 2 */

#define R_SYSC_VBTADCR1_VBTADCE0                  (1 << 4)  /* VBATT Tamper Detection Backup Register Clear Enable 0 */

#define R_SYSC_VBTADCR1_VBTADCE1                  (1 << 5)  /* VBATT Tamper Detection Backup Register Clear Enable 1 */

#define R_SYSC_VBTADCR1_VBTADCE2                  (1 << 6)  /* VBATT Tamper Detection Backup Register Clear Enable 2 */

#define R_SYSC_VBTADCR1_VBTADCLE0                 (1 << 4)  /* VBATT Tamper Detection Backup Register Clear Enable 0 */

#define R_SYSC_VBTADCR1_VBTADCLE1                 (1 << 5)  /* VBATT Tamper Detection Backup Register Clear Enable 1 */

#define R_SYSC_VBTADCR1_VBTADCLE2                 (1 << 6)  /* VBATT Tamper Detection Backup Register Clear Enable 2 */

/* VBTADCR2 Register bit definitions */
#define R_SYSC_VBTADCR2_VBRTCES0                  (1 << 0)  /* VBATT RTC Time Capture Event Source Select 0 */

#define R_SYSC_VBTADCR2_VBRTCES1                  (1 << 1)  /* VBATT RTC Time Capture Event Source Select 1 */

#define R_SYSC_VBTADCR2_VBRTCES2                  (1 << 2)  /* VBATT RTC Time Capture Event Source Select 2 */

/* VBTICTLR Register bit definitions */
#define R_SYSC_VBTICTLR_VCH0INEN                  (1 << 0)  /* VBATT CH0 Input Enable */

#define R_SYSC_VBTICTLR_VCH1INEN                  (1 << 1)  /* VBATT CH1 Input Enable */

#define R_SYSC_VBTICTLR_VCH2INEN                  (1 << 2)  /* VBATT CH2 Input Enable */

/* VBTICTLR2 Register bit definitions */
#define R_SYSC_VBTICTLR2_VCH0NCE                  (1 << 0)  /* VBATT CH0 Input Noise Canceler Enable */

#define R_SYSC_VBTICTLR2_VCH1NCE                  (1 << 1)  /* VBATT CH1 Input Noise Canceler Enable */

#define R_SYSC_VBTICTLR2_VCH2NCE                  (1 << 2)  /* VBATT CH2 Input Noise Canceler Enable */

#define R_SYSC_VBTICTLR2_VCH0EG                   (1 << 4)  /* VBATT CH0 Input Edge Select */

#define R_SYSC_VBTICTLR2_VCH1EG                   (1 << 5)  /* VBATT CH1 Input Edge Select */

#define R_SYSC_VBTICTLR2_VCH2EG                   (1 << 6)  /* VBATT CH2 Input Edge Select */

/* VBTIMONR Register bit definitions */
#define R_SYSC_VBTIMONR_VCH0MON                   (1 << 0)  /* VBATT CH0 Input monitor */

#define R_SYSC_VBTIMONR_VCH1MON                   (1 << 1)  /* VBATT CH1 Input monitor */

#define R_SYSC_VBTIMONR_VCH2MON                   (1 << 2)  /* VBATT CH2 Input monitor */


/* Maximum number of channels */

#define SYSC_MAX_CHANNELS    128

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SYSC_H */

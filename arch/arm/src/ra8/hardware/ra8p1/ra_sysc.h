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

/* SYSC Register Offsets */

#define R_SYSC_SBYCR_OFFSET                       0x0000000c  /* Standby Control Register */
#define R_SYSC_VSCR_OFFSET                        0x00000014  /* Voltage Scaling Control Register */
#define R_SYSC_SCKDIVCR_OFFSET                    0x00000020  /* System Clock Division Control Register */
#define R_SYSC_SCKDIVCR2_OFFSET                   0x00000024  /* System Clock Division Control Register 2 */
#define R_SYSC_SCKSCR_OFFSET                      0x00000026  /* System Clock Source Control Register */
#define R_SYSC_PLLCR_OFFSET                       0x0000002a  /* PLL Control Register */
#define R_SYSC_BCKCR_OFFSET                       0x00000030  /* External Bus Clock Control Register */
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
#define R_SYSC_PLL2CR_OFFSET                      0x0000004a  /* PLL2 Control Register */
#define R_SYSC_PLLCCR2_OFFSET                     0x0000004c  /* PLL Clock Control Register 2 */
#define R_SYSC_PLL2CCR2_OFFSET                    0x0000004e  /* PLL2 Clock Control Register 2 */
#define R_SYSC_EBCKOCR_OFFSET                     0x00000052  /* External Bus Clock Output Control Register */
#define R_SYSC_SDCKOCR_OFFSET                     0x00000053  /* SDRAM Clock Output Control Register */
#define R_SYSC_SCICKDIVCR_OFFSET                  0x00000054  /* SCI Clock Division Control Register */
#define R_SYSC_SCICKCR_OFFSET                     0x00000055  /* SCI Clock Control Register */
#define R_SYSC_SPICKDIVCR_OFFSET                  0x00000056  /* SPI Clock Division Control Register */
#define R_SYSC_SPICKCR_OFFSET                     0x00000057  /* SPI Clock Control Register */
#define R_SYSC_ADCCKDIVCR_OFFSET                  0x0000005a  /* ADC Clock Division Control Register */
#define R_SYSC_ADCCKCR_OFFSET                     0x0000005b  /* ADC Clock Control Register */
#define R_SYSC_GPTCKDIVCR_OFFSET                  0x0000005c  /* GPT Clock Division Control Register */
#define R_SYSC_GPTCKCR_OFFSET                     0x0000005d  /* GPT Clock Control Register */
#define R_SYSC_LCDCKDIVCR_OFFSET                  0x0000005e  /* LCD Clock Division Control Register */
#define R_SYSC_LCDCKCR_OFFSET                     0x0000005f  /* LCD Clock Control Register */
#define R_SYSC_MOCOUTCR_OFFSET                    0x00000061  /* MOCO User Trimming Control Register */
#define R_SYSC_HOCOUTCR_OFFSET                    0x00000062  /* HOCO User Trimming Control Register */
#define R_SYSC_USBCKDIVCR_OFFSET                  0x0000006c  /* USB Clock Division Control Register */
#define R_SYSC_OCTACKDIVCR_OFFSET                 0x0000006d  /* Octal-SPI Clock Division Control Register */
#define R_SYSC_CANFDCKDIVCR_OFFSET                0x0000006e  /* CANFD Core Clock Division Control Register */
#define R_SYSC_USB60CKDIVCR_OFFSET                0x0000006f  /* USB60 Clock Division Control Register */
#define R_SYSC_I3CCKDIVCR_OFFSET                  0x00000070  /* I3C Clock Division Control Register */
#define R_SYSC_USBCKCR_OFFSET                     0x00000074  /* USB Clock Control Register */
#define R_SYSC_OCTACKCR_OFFSET                    0x00000075  /* Octal-SPI Clock Control Register */
#define R_SYSC_CANFDCKCR_OFFSET                   0x00000076  /* CANFD Core Clock Control Register */
#define R_SYSC_USB60CKCR_OFFSET                   0x00000077  /* USB60 Clock Control Register */
#define R_SYSC_I3CCKCR_OFFSET                     0x00000078  /* I3C Clock Control Register */
#define R_SYSC_MOSCSCR_OFFSET                     0x0000007c  /* Main Clock Oscillator Standby Control Register */
#define R_SYSC_HOCOSCR_OFFSET                     0x0000007d  /* High-Speed On-Chip Oscillator Standby Control Register */
#define R_SYSC_MOCOSCR_OFFSET                     0x00000084  /* Middle-Speed On-Chip Oscillator Standby Control Register */
#define R_SYSC_OPCCR_OFFSET                       0x000000a0  /* Operating Power Control Register */
#define R_SYSC_MOSCWTCR_OFFSET                    0x000000a2  /* Main Clock Oscillator Wait Control Register */
#define R_SYSC_PLLCCR_OFFSET                      0x000000ac  /* PLL Clock Control Register */
#define R_SYSC_RSTSR1_OFFSET                      0x000000c0  /* Reset Status Register 1 */
#define R_SYSC_PLL2CCR_OFFSET                     0x000000c8  /* PLL2 Clock Control Register */
#define R_SYSC_SYRACCR_OFFSET                     0x000000cc  /* System Register Access Control Register */
#define R_SYSC_BCKADIVCR_OFFSET                   0x000000d4  /* Asynchronous External Bus Clock Division Control Register */
#define R_SYSC_ESWCKDIVCR_OFFSET                  0x000000d5  /* EtherSW Clock Division Control Register */
#define R_SYSC_ESWPCKDIVCR_OFFSET                 0x000000d6  /* EtherSW-PHY Clock Division Control Register */
#define R_SYSC_ETHPCKDIVCR_OFFSET                 0x000000d8  /* Ether-PHY Clock Division Control Register */
#define R_SYSC_BCKACR_OFFSET                      0x000000da  /* Asynchronous External Bus Clock Control Register */
#define R_SYSC_ESWCKCR_OFFSET                     0x000000db  /* EtherSW Clock Control Register */
#define R_SYSC_ESWPCKCR_OFFSET                    0x000000dc  /* EtherSW-PHY Clock Control Register */
#define R_SYSC_ETHPCKCR_OFFSET                    0x000000de  /* Ether-PHY Clock Control Register */
/* PVD%sCR1 Registers (1-2) */
#define R_SYSC_PVDCR1_OFFSET(m)                   (0x000000e0 + ((m) * 0x00000002))  /* Voltage Monitor %s Circuit Control Register */
/* PVD%sSR Registers (1-2) */
#define R_SYSC_PVDSR_OFFSET(m)                    (0x000000e1 + ((m) * 0x00000002))  /* Voltage Monitor %s Circuit Status Register */
#define R_SYSC_CPUDSCR_OFFSET                     0x00000100  /* CPU Deep Sleep Control Register */
#define R_SYSC_PGSCR_OFFSET                       0x00000104  /* Power Gating Shift Control Register */
#define R_SYSC_PDCTRGD_OFFSET                     0x00000110  /* Graphics Power Domain Control Register */
#define R_SYSC_PDCTRNPU_OFFSET                    0x00000114  /* NPU Power Domain Control Register */
#define R_SYSC_PDCTRESWM_OFFSET                   0x00000118  /* ESWM Power Domain Control Register */
#define R_SYSC_PDRAMSCR0_OFFSET                   0x00000140  /* SRAM Power Domain Standby Control Register 0 */
#define R_SYSC_PDRAMSCR1_OFFSET                   0x00000142  /* SRAM Power Domain Standby Control Register 1 */
/* PSSTCR%s Registers (0-5) */
#define R_SYSC_PSSTCR_OFFSET(m)                   (0x00000210 + ((m) * 0x00000002))  /* Power Switch Control Start Time Control Register %s */
/* PSSTCR%s Registers (0-5) */
#define R_SYSC_PSSTCRX_OFFSET(m)                  (0x00000210 + ((m) * 0x00000002))  /* Power Switch Control Start Time Control Register %s */
#define R_SYSC_VBRSABAR_OFFSET                    0x000003b0  /* VBATT Backup Register Security Attribute Boundary Address Register */
#define R_SYSC_VBRPABARS_OFFSET                   0x000003b4  /* VBATT Backup Register Privilege Attribute Boundary Address Register for Secure Region */
#define R_SYSC_CGFSAR_OFFSET                      0x000003c0  /* Clock Generation Function Security Attribute Register */
#define R_SYSC_RSTSAR_OFFSET                      0x000003c4  /* Reset Security Attribution Register */
#define R_SYSC_LPMSAR_OFFSET                      0x000003c8  /* Low Power Mode Security Attribution Register */
#define R_SYSC_PVDSAR_OFFSET                      0x000003cc  /* Programable Voltage Detection Security Attribution Register */
#define R_SYSC_BBFSAR_OFFSET                      0x000003d0  /* Battery Backup Function Security Attribute Register */
#define R_SYSC_PGCSAR_OFFSET                      0x000003d8  /* Power Gating Control Security Attribution Register */
#define R_SYSC_DPFSAR_OFFSET                      0x000003e0  /* Deep Software Standby Interrupt Factor Security Attribution Register */
#define R_SYSC_RSCSAR_OFFSET                      0x000003e4  /* RAM Standby Control Security Attribution Register */
#define R_SYSC_DPFSAR1_OFFSET                     0x000003e8  /* Deep Software Standby Interrupt Factor Security Attribution Register 1 */
#define R_SYSC_PRCR_S_OFFSET                      0x000003fa  /* Protect Register for Secure */
#define R_SYSC_LOCOCR_OFFSET                      0x00000400  /* Low-Speed On-Chip Oscillator Control Register */
#define R_SYSC_LOCOUTCR_OFFSET                    0x00000402  /* LOCO User Trimming Control Register */
#define R_SYSC_DPSBYCR_OFFSET                     0x00000a00  /* Deep Software Standby Control Register */
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
#define R_SYSC_DPSIEGR3_OFFSET                    0x00000a34  /* Deep Software Standby Interrupt Edge Register 3 */
#define R_SYSC_SYOCDCR_OFFSET                     0x00000a38  /* System Control OCD Control Register */
#define R_SYSC_RSTSR0_OFFSET                      0x00000a40  /* Reset Status Register 0 */
#define R_SYSC_RSTSR2_OFFSET                      0x00000a44  /* Reset Status Register 2 */
#define R_SYSC_RSTSR3_OFFSET                      0x00000a48  /* Reset Status Register 3 */
#define R_SYSC_MOMCR_OFFSET                       0x00000a50  /* Main Clock Oscillator Mode Oscillation Control Register */
#define R_SYSC_FWEPROR_OFFSET                     0x00000a54  /* Flash P/E Protect Register */
/* PVD%sCMPCR Registers (1-2) */
#define R_SYSC_PVDCMPCR_OFFSET(m)                 (0x00000a58 + ((m) * 0x00000004))  /* Voltage Monitor %s Comparator Control Register */
/* PVD%sCMPCR Registers (4-5) */
#define R_SYSC_PVDXCMPCR_OFFSET(m)                (0x00000a64 + ((m) * 0x00000004))  /* Voltage Monitor %s Comparator Control Register */
/* PVD%sCR0 Registers (1-2) */
#define R_SYSC_PVDCR0_OFFSET(m)                   (0x00000a70 + ((m) * 0x00000004))  /* Voltage Monitor %s Circuit Control Register 0 */
/* PVD%sCR0 Registers (4-5) */
#define R_SYSC_PVDXCR0_OFFSET(m)                  (0x00000a7c + ((m) * 0x00000004))  /* Voltage Monitor %s Circuit Control Register 0 */
#define R_SYSC_VBATTMNSELR_OFFSET                 0x00000a84  /* Battery Backup Voltage Monitor Function Select Register */
#define R_SYSC_VBTBPCR1_OFFSET                    0x00000a88  /* VBATT Battery Power Supply Control Register 1 */
#define R_SYSC_LPSCR_OFFSET                       0x00000a90  /* Low Power State Control Register */
#define R_SYSC_SSCR1_OFFSET                       0x00000a98  /* Software Standby Control Register 1 */
#define R_SYSC_SVSCR_OFFSET                       0x00000a9c  /* SSTBY Voltage Scaling Control Register */
#define R_SYSC_LVOCR_OFFSET                       0x00000ab0  /* Low Voltage Operation Control Register */
#define R_SYSC_MWMCR_OFFSET                       0x00000ab4  /* OTP Write Mode Control Register */
#define R_SYSC_SYRSTMSK0_OFFSET                   0x00000ad0  /* System Reset Mask Control Register 0 */
#define R_SYSC_SYRSTMSK1_OFFSET                   0x00000ad4  /* System Reset Mask Control Register 1 */
#define R_SYSC_SYRSTMSK2_OFFSET                   0x00000ad8  /* System Reset Mask Control Register 2 */
#define R_SYSC_TEMPRCR_OFFSET                     0x00000adc  /* Temperature Monitor Reset Control Register */
#define R_SYSC_TEMPRLR_OFFSET                     0x00000ae0  /* Temperature Monitor Reset Lock Register */
#define R_SYSC_PLL1LDOCR_OFFSET                   0x00000b04  /* PLL1-LDO Control Register */
#define R_SYSC_PLL2LDOCR_OFFSET                   0x00000b08  /* PLL2-LDO Control Register */
#define R_SYSC_HOCOLDOCR_OFFSET                   0x00000b0c  /* HOCO-LDO Control Register */
/* PVD%sFCR Registers (1-2) */
#define R_SYSC_PVDFCR_OFFSET(m)                   (0x00000b20 + ((m) * 0x00000004))  /* Voltage Monitor %s Function Control Register */
/* PVD%sFCR Registers (4-5) */
#define R_SYSC_PVDXFCR_OFFSET(m)                  (0x00000b2c + ((m) * 0x00000004))  /* Voltage Monitor %s Function Control Register */
#define R_SYSC_PVDLR_OFFSET                       0x00000b34  /* Voltage Monitor Lock Register */
#define R_SYSC_DPSIER4_OFFSET                     0x00000b40  /* Deep Software Standby Interrupt Enable Register 4 */
#define R_SYSC_DPSIER5_OFFSET                     0x00000b44  /* Deep Software Standby Interrupt Enable Register 5 */
#define R_SYSC_DPSIFR4_OFFSET                     0x00000b48  /* Deep Software Standby Interrupt Flag Register 4 */
#define R_SYSC_DPSIFR5_OFFSET                     0x00000b4c  /* Deep Software Standby Interrupt Flag Register 5 */
#define R_SYSC_DPSIEGR4_OFFSET                    0x00000b50  /* Deep Software Standby Interrupt Edge Register 4 */
#define R_SYSC_SOSCCR_OFFSET                      0x00000c00  /* Sub-Clock Oscillator Control Register */
#define R_SYSC_SOMCR_OFFSET                       0x00000c01  /* Sub-Clock Oscillator Mode Control Register */
#define R_SYSC_SOSTDCR_OFFSET                     0x00000c04  /* Sub-clock Oscillation Stop Detection Control Register */
#define R_SYSC_SOSTDSR_OFFSET                     0x00000c05  /* Sub-clock Oscillation Stop Detection Status Register */
#define R_SYSC_VBTBER_OFFSET                      0x00000c40  /* VBATT Backup Enable Register */
#define R_SYSC_VBTBPCR2_OFFSET                    0x00000c45  /* VBATT Battery Power Supply Control Register 2 */
#define R_SYSC_VBTBPSR_OFFSET                     0x00000c46  /* VBATT Battery Power Supply Status Register */
#define R_SYSC_VBTADSR_OFFSET                     0x00000c48  /* VBATT Tamper Detection Status Register */
#define R_SYSC_VBTADCR1_OFFSET                    0x00000c49  /* VBATT Tamper Detection Control Register 1 */
#define R_SYSC_VBTADCR2_OFFSET                    0x00000c4a  /* VBATT Tamper Detection Control Register 2 */
#define R_SYSC_VBTICTLR_OFFSET                    0x00000c4c  /* VBATT Input Control Register */
#define R_SYSC_VBTICTLR2_OFFSET                   0x00000c4d  /* VBATT Input Control Register 2 */
#define R_SYSC_VBTIMONR_OFFSET                    0x00000c4e  /* VBATT Input Monitor Register */
#define R_SYSC_VBTNCWCR_OFFSET                    0x00000c50  /* VBATT Noise Canceler Width Control Register */
#define R_SYSC_VBTADCR3_OFFSET                    0x00000c54  /* VBATT Tamper Detection Control Register 3 */
/* VBTBKR%s Registers (0-127) */
#define R_SYSC_VBTBKR_OFFSET(m)                   (0x00000d00 + ((m) * 0x00000001))  /* VBATT Backup Register */

/* SYSC Register Addresses */

#define R_SYSC_SBYCR                              (R_SYSC_BASE + R_SYSC_SBYCR_OFFSET)
#define R_SYSC_VSCR                               (R_SYSC_BASE + R_SYSC_VSCR_OFFSET)
#define R_SYSC_SCKDIVCR                           (R_SYSC_BASE + R_SYSC_SCKDIVCR_OFFSET)
#define R_SYSC_SCKDIVCR2                          (R_SYSC_BASE + R_SYSC_SCKDIVCR2_OFFSET)
#define R_SYSC_SCKSCR                             (R_SYSC_BASE + R_SYSC_SCKSCR_OFFSET)
#define R_SYSC_PLLCR                              (R_SYSC_BASE + R_SYSC_PLLCR_OFFSET)
#define R_SYSC_BCKCR                              (R_SYSC_BASE + R_SYSC_BCKCR_OFFSET)
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
#define R_SYSC_PLL2CR                             (R_SYSC_BASE + R_SYSC_PLL2CR_OFFSET)
#define R_SYSC_PLLCCR2                            (R_SYSC_BASE + R_SYSC_PLLCCR2_OFFSET)
#define R_SYSC_PLL2CCR2                           (R_SYSC_BASE + R_SYSC_PLL2CCR2_OFFSET)
#define R_SYSC_EBCKOCR                            (R_SYSC_BASE + R_SYSC_EBCKOCR_OFFSET)
#define R_SYSC_SDCKOCR                            (R_SYSC_BASE + R_SYSC_SDCKOCR_OFFSET)
#define R_SYSC_SCICKDIVCR                         (R_SYSC_BASE + R_SYSC_SCICKDIVCR_OFFSET)
#define R_SYSC_SCICKCR                            (R_SYSC_BASE + R_SYSC_SCICKCR_OFFSET)
#define R_SYSC_SPICKDIVCR                         (R_SYSC_BASE + R_SYSC_SPICKDIVCR_OFFSET)
#define R_SYSC_SPICKCR                            (R_SYSC_BASE + R_SYSC_SPICKCR_OFFSET)
#define R_SYSC_ADCCKDIVCR                         (R_SYSC_BASE + R_SYSC_ADCCKDIVCR_OFFSET)
#define R_SYSC_ADCCKCR                            (R_SYSC_BASE + R_SYSC_ADCCKCR_OFFSET)
#define R_SYSC_GPTCKDIVCR                         (R_SYSC_BASE + R_SYSC_GPTCKDIVCR_OFFSET)
#define R_SYSC_GPTCKCR                            (R_SYSC_BASE + R_SYSC_GPTCKCR_OFFSET)
#define R_SYSC_LCDCKDIVCR                         (R_SYSC_BASE + R_SYSC_LCDCKDIVCR_OFFSET)
#define R_SYSC_LCDCKCR                            (R_SYSC_BASE + R_SYSC_LCDCKCR_OFFSET)
#define R_SYSC_MOCOUTCR                           (R_SYSC_BASE + R_SYSC_MOCOUTCR_OFFSET)
#define R_SYSC_HOCOUTCR                           (R_SYSC_BASE + R_SYSC_HOCOUTCR_OFFSET)
#define R_SYSC_USBCKDIVCR                         (R_SYSC_BASE + R_SYSC_USBCKDIVCR_OFFSET)
#define R_SYSC_OCTACKDIVCR                        (R_SYSC_BASE + R_SYSC_OCTACKDIVCR_OFFSET)
#define R_SYSC_CANFDCKDIVCR                       (R_SYSC_BASE + R_SYSC_CANFDCKDIVCR_OFFSET)
#define R_SYSC_USB60CKDIVCR                       (R_SYSC_BASE + R_SYSC_USB60CKDIVCR_OFFSET)
#define R_SYSC_I3CCKDIVCR                         (R_SYSC_BASE + R_SYSC_I3CCKDIVCR_OFFSET)
#define R_SYSC_USBCKCR                            (R_SYSC_BASE + R_SYSC_USBCKCR_OFFSET)
#define R_SYSC_OCTACKCR                           (R_SYSC_BASE + R_SYSC_OCTACKCR_OFFSET)
#define R_SYSC_CANFDCKCR                          (R_SYSC_BASE + R_SYSC_CANFDCKCR_OFFSET)
#define R_SYSC_USB60CKCR                          (R_SYSC_BASE + R_SYSC_USB60CKCR_OFFSET)
#define R_SYSC_I3CCKCR                            (R_SYSC_BASE + R_SYSC_I3CCKCR_OFFSET)
#define R_SYSC_MOSCSCR                            (R_SYSC_BASE + R_SYSC_MOSCSCR_OFFSET)
#define R_SYSC_HOCOSCR                            (R_SYSC_BASE + R_SYSC_HOCOSCR_OFFSET)
#define R_SYSC_MOCOSCR                            (R_SYSC_BASE + R_SYSC_MOCOSCR_OFFSET)
#define R_SYSC_OPCCR                              (R_SYSC_BASE + R_SYSC_OPCCR_OFFSET)
#define R_SYSC_MOSCWTCR                           (R_SYSC_BASE + R_SYSC_MOSCWTCR_OFFSET)
#define R_SYSC_PLLCCR                             (R_SYSC_BASE + R_SYSC_PLLCCR_OFFSET)
#define R_SYSC_RSTSR1                             (R_SYSC_BASE + R_SYSC_RSTSR1_OFFSET)
#define R_SYSC_PLL2CCR                            (R_SYSC_BASE + R_SYSC_PLL2CCR_OFFSET)
#define R_SYSC_SYRACCR                            (R_SYSC_BASE + R_SYSC_SYRACCR_OFFSET)
#define R_SYSC_BCKADIVCR                          (R_SYSC_BASE + R_SYSC_BCKADIVCR_OFFSET)
#define R_SYSC_ESWCKDIVCR                         (R_SYSC_BASE + R_SYSC_ESWCKDIVCR_OFFSET)
#define R_SYSC_ESWPCKDIVCR                        (R_SYSC_BASE + R_SYSC_ESWPCKDIVCR_OFFSET)
#define R_SYSC_ETHPCKDIVCR                        (R_SYSC_BASE + R_SYSC_ETHPCKDIVCR_OFFSET)
#define R_SYSC_BCKACR                             (R_SYSC_BASE + R_SYSC_BCKACR_OFFSET)
#define R_SYSC_ESWCKCR                            (R_SYSC_BASE + R_SYSC_ESWCKCR_OFFSET)
#define R_SYSC_ESWPCKCR                           (R_SYSC_BASE + R_SYSC_ESWPCKCR_OFFSET)
#define R_SYSC_ETHPCKCR                           (R_SYSC_BASE + R_SYSC_ETHPCKCR_OFFSET)
#define R_SYSC_PVDCR1(m)                          (R_SYSC_BASE + R_SYSC_PVDCR1_OFFSET(m))
#define R_SYSC_PVDSR(m)                           (R_SYSC_BASE + R_SYSC_PVDSR_OFFSET(m))
#define R_SYSC_CPUDSCR                            (R_SYSC_BASE + R_SYSC_CPUDSCR_OFFSET)
#define R_SYSC_PGSCR                              (R_SYSC_BASE + R_SYSC_PGSCR_OFFSET)
#define R_SYSC_PDCTRGD                            (R_SYSC_BASE + R_SYSC_PDCTRGD_OFFSET)
#define R_SYSC_PDCTRNPU                           (R_SYSC_BASE + R_SYSC_PDCTRNPU_OFFSET)
#define R_SYSC_PDCTRESWM                          (R_SYSC_BASE + R_SYSC_PDCTRESWM_OFFSET)
#define R_SYSC_PDRAMSCR0                          (R_SYSC_BASE + R_SYSC_PDRAMSCR0_OFFSET)
#define R_SYSC_PDRAMSCR1                          (R_SYSC_BASE + R_SYSC_PDRAMSCR1_OFFSET)
#define R_SYSC_PSSTCRX(m)                         (R_SYSC_BASE + R_SYSC_PSSTCRX_OFFSET(m))
#define R_SYSC_VBRSABAR                           (R_SYSC_BASE + R_SYSC_VBRSABAR_OFFSET)
#define R_SYSC_VBRPABARS                          (R_SYSC_BASE + R_SYSC_VBRPABARS_OFFSET)
#define R_SYSC_CGFSAR                             (R_SYSC_BASE + R_SYSC_CGFSAR_OFFSET)
#define R_SYSC_RSTSAR                             (R_SYSC_BASE + R_SYSC_RSTSAR_OFFSET)
#define R_SYSC_LPMSAR                             (R_SYSC_BASE + R_SYSC_LPMSAR_OFFSET)
#define R_SYSC_PVDSAR                             (R_SYSC_BASE + R_SYSC_PVDSAR_OFFSET)
#define R_SYSC_BBFSAR                             (R_SYSC_BASE + R_SYSC_BBFSAR_OFFSET)
#define R_SYSC_PGCSAR                             (R_SYSC_BASE + R_SYSC_PGCSAR_OFFSET)
#define R_SYSC_DPFSAR                             (R_SYSC_BASE + R_SYSC_DPFSAR_OFFSET)
#define R_SYSC_RSCSAR                             (R_SYSC_BASE + R_SYSC_RSCSAR_OFFSET)
#define R_SYSC_DPFSAR1                            (R_SYSC_BASE + R_SYSC_DPFSAR1_OFFSET)
#define R_SYSC_PRCR_S                             (R_SYSC_BASE + R_SYSC_PRCR_S_OFFSET)
#define R_SYSC_LOCOCR                             (R_SYSC_BASE + R_SYSC_LOCOCR_OFFSET)
#define R_SYSC_LOCOUTCR                           (R_SYSC_BASE + R_SYSC_LOCOUTCR_OFFSET)
#define R_SYSC_DPSBYCR                            (R_SYSC_BASE + R_SYSC_DPSBYCR_OFFSET)
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
#define R_SYSC_DPSIEGR3                           (R_SYSC_BASE + R_SYSC_DPSIEGR3_OFFSET)
#define R_SYSC_SYOCDCR                            (R_SYSC_BASE + R_SYSC_SYOCDCR_OFFSET)
#define R_SYSC_RSTSR0                             (R_SYSC_BASE + R_SYSC_RSTSR0_OFFSET)
#define R_SYSC_RSTSR2                             (R_SYSC_BASE + R_SYSC_RSTSR2_OFFSET)
#define R_SYSC_RSTSR3                             (R_SYSC_BASE + R_SYSC_RSTSR3_OFFSET)
#define R_SYSC_MOMCR                              (R_SYSC_BASE + R_SYSC_MOMCR_OFFSET)
#define R_SYSC_FWEPROR                            (R_SYSC_BASE + R_SYSC_FWEPROR_OFFSET)
#define R_SYSC_PVDXCMPCR(m)                       (R_SYSC_BASE + R_SYSC_PVDXCMPCR_OFFSET(m))
#define R_SYSC_PVDXCR0(m)                         (R_SYSC_BASE + R_SYSC_PVDXCR0_OFFSET(m))
#define R_SYSC_VBATTMNSELR                        (R_SYSC_BASE + R_SYSC_VBATTMNSELR_OFFSET)
#define R_SYSC_VBTBPCR1                           (R_SYSC_BASE + R_SYSC_VBTBPCR1_OFFSET)
#define R_SYSC_LPSCR                              (R_SYSC_BASE + R_SYSC_LPSCR_OFFSET)
#define R_SYSC_SSCR1                              (R_SYSC_BASE + R_SYSC_SSCR1_OFFSET)
#define R_SYSC_SVSCR                              (R_SYSC_BASE + R_SYSC_SVSCR_OFFSET)
#define R_SYSC_LVOCR                              (R_SYSC_BASE + R_SYSC_LVOCR_OFFSET)
#define R_SYSC_MWMCR                              (R_SYSC_BASE + R_SYSC_MWMCR_OFFSET)
#define R_SYSC_SYRSTMSK0                          (R_SYSC_BASE + R_SYSC_SYRSTMSK0_OFFSET)
#define R_SYSC_SYRSTMSK1                          (R_SYSC_BASE + R_SYSC_SYRSTMSK1_OFFSET)
#define R_SYSC_SYRSTMSK2                          (R_SYSC_BASE + R_SYSC_SYRSTMSK2_OFFSET)
#define R_SYSC_TEMPRCR                            (R_SYSC_BASE + R_SYSC_TEMPRCR_OFFSET)
#define R_SYSC_TEMPRLR                            (R_SYSC_BASE + R_SYSC_TEMPRLR_OFFSET)
#define R_SYSC_PLL1LDOCR                          (R_SYSC_BASE + R_SYSC_PLL1LDOCR_OFFSET)
#define R_SYSC_PLL2LDOCR                          (R_SYSC_BASE + R_SYSC_PLL2LDOCR_OFFSET)
#define R_SYSC_HOCOLDOCR                          (R_SYSC_BASE + R_SYSC_HOCOLDOCR_OFFSET)
#define R_SYSC_PVDXFCR(m)                         (R_SYSC_BASE + R_SYSC_PVDXFCR_OFFSET(m))
#define R_SYSC_PVDLR                              (R_SYSC_BASE + R_SYSC_PVDLR_OFFSET)
#define R_SYSC_DPSIER4                            (R_SYSC_BASE + R_SYSC_DPSIER4_OFFSET)
#define R_SYSC_DPSIER5                            (R_SYSC_BASE + R_SYSC_DPSIER5_OFFSET)
#define R_SYSC_DPSIFR4                            (R_SYSC_BASE + R_SYSC_DPSIFR4_OFFSET)
#define R_SYSC_DPSIFR5                            (R_SYSC_BASE + R_SYSC_DPSIFR5_OFFSET)
#define R_SYSC_DPSIEGR4                           (R_SYSC_BASE + R_SYSC_DPSIEGR4_OFFSET)
#define R_SYSC_SOSCCR                             (R_SYSC_BASE + R_SYSC_SOSCCR_OFFSET)
#define R_SYSC_SOMCR                              (R_SYSC_BASE + R_SYSC_SOMCR_OFFSET)
#define R_SYSC_SOSTDCR                            (R_SYSC_BASE + R_SYSC_SOSTDCR_OFFSET)
#define R_SYSC_SOSTDSR                            (R_SYSC_BASE + R_SYSC_SOSTDSR_OFFSET)
#define R_SYSC_VBTBER                             (R_SYSC_BASE + R_SYSC_VBTBER_OFFSET)
#define R_SYSC_VBTBPCR2                           (R_SYSC_BASE + R_SYSC_VBTBPCR2_OFFSET)
#define R_SYSC_VBTBPSR                            (R_SYSC_BASE + R_SYSC_VBTBPSR_OFFSET)
#define R_SYSC_VBTADSR                            (R_SYSC_BASE + R_SYSC_VBTADSR_OFFSET)
#define R_SYSC_VBTADCR1                           (R_SYSC_BASE + R_SYSC_VBTADCR1_OFFSET)
#define R_SYSC_VBTADCR2                           (R_SYSC_BASE + R_SYSC_VBTADCR2_OFFSET)
#define R_SYSC_VBTICTLR                           (R_SYSC_BASE + R_SYSC_VBTICTLR_OFFSET)
#define R_SYSC_VBTICTLR2                          (R_SYSC_BASE + R_SYSC_VBTICTLR2_OFFSET)
#define R_SYSC_VBTIMONR                           (R_SYSC_BASE + R_SYSC_VBTIMONR_OFFSET)
#define R_SYSC_VBTNCWCR                           (R_SYSC_BASE + R_SYSC_VBTNCWCR_OFFSET)
#define R_SYSC_VBTADCR3                           (R_SYSC_BASE + R_SYSC_VBTADCR3_OFFSET)
#define R_SYSC_VBTBKR(m)                          (R_SYSC_BASE + R_SYSC_VBTBKR_OFFSET(m))

/* Register bit definitions */
/* SBYCR Register bit definitions */
#define R_SYSC_SBYCR_OPE                          (1 << 6)  /* Output Port Enable */

/* VSCR Register bit definitions */
#define R_SYSC_VSCR_VSCM_SHIFT                    (0)  /* Voltage Scaling Control Mode Bit */
#define R_SYSC_VSCR_VSCM_MASK                     0x7
#  define R_SYSC_VSCR_VSCM_001                            (1 << R_SYSC_VSCR_VSCM_SHIFT)  /* VSCR_1 */
#  define R_SYSC_VSCR_VSCM_010                            (2 << R_SYSC_VSCR_VSCM_SHIFT)  /* VSCR_2 (default) */

#define R_SYSC_VSCR_VSCMTSF                       (1 << 4)  /* Voltage Scaling Control Mode Transition Status Flag */

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
#  define R_SYSC_SCKDIVCR_PCKD_1011                       (11 << R_SYSC_SCKDIVCR_PCKD_SHIFT)  /* x 1/24 */

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
#  define R_SYSC_SCKDIVCR_PCKC_1011                       (11 << R_SYSC_SCKDIVCR_PCKC_SHIFT)  /* x 1/24 */

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
#  define R_SYSC_SCKDIVCR_PCKB_1011                       (11 << R_SYSC_SCKDIVCR_PCKB_SHIFT)  /* x 1/24 */

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
#  define R_SYSC_SCKDIVCR_PCKA_1011                       (11 << R_SYSC_SCKDIVCR_PCKA_SHIFT)  /* x 1/24 */

#define R_SYSC_SCKDIVCR_BCK_SHIFT                 (16)  /* External Bus Clock (BCLK) Select */
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
#  define R_SYSC_SCKDIVCR_BCK_1011                        (11 << R_SYSC_SCKDIVCR_BCK_SHIFT)  /* x 1/24 */

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
#  define R_SYSC_SCKDIVCR_ICK_1011                        (11 << R_SYSC_SCKDIVCR_ICK_SHIFT)  /* x 1/24 */

#define R_SYSC_SCKDIVCR_MRPCK_SHIFT               (28)  /* MRAM Clock (MRPCLK) Select */
#define R_SYSC_SCKDIVCR_MRPCK_MASK                0xf0000000
#  define R_SYSC_SCKDIVCR_MRPCK_0000                      (0 << R_SYSC_SCKDIVCR_MRPCK_SHIFT)  /* x 1/1 */
#  define R_SYSC_SCKDIVCR_MRPCK_0001                      (1 << R_SYSC_SCKDIVCR_MRPCK_SHIFT)  /* x 1/2 */
#  define R_SYSC_SCKDIVCR_MRPCK_0010                      (2 << R_SYSC_SCKDIVCR_MRPCK_SHIFT)  /* x 1/4 */
#  define R_SYSC_SCKDIVCR_MRPCK_0011                      (3 << R_SYSC_SCKDIVCR_MRPCK_SHIFT)  /* x 1/8 */
#  define R_SYSC_SCKDIVCR_MRPCK_0100                      (4 << R_SYSC_SCKDIVCR_MRPCK_SHIFT)  /* x 1/16 */
#  define R_SYSC_SCKDIVCR_MRPCK_0101                      (5 << R_SYSC_SCKDIVCR_MRPCK_SHIFT)  /* x 1/32 */
#  define R_SYSC_SCKDIVCR_MRPCK_0110                      (6 << R_SYSC_SCKDIVCR_MRPCK_SHIFT)  /* x 1/64 */
#  define R_SYSC_SCKDIVCR_MRPCK_1000                      (8 << R_SYSC_SCKDIVCR_MRPCK_SHIFT)  /* x 1/3 */
#  define R_SYSC_SCKDIVCR_MRPCK_1001                      (9 << R_SYSC_SCKDIVCR_MRPCK_SHIFT)  /* x 1/6 */
#  define R_SYSC_SCKDIVCR_MRPCK_1010                      (10 << R_SYSC_SCKDIVCR_MRPCK_SHIFT)  /* x 1/12 */
#  define R_SYSC_SCKDIVCR_MRPCK_1011                      (11 << R_SYSC_SCKDIVCR_MRPCK_SHIFT)  /* x 1/24 */

#define R_SYSC_SCKDIVCR_PCKE_SHIFT                (20)  /* Peripheral Module Clock E (PCLKE) Select */
#define R_SYSC_SCKDIVCR_PCKE_MASK                 0xf00000

#define R_SYSC_SCKDIVCR_FCK_SHIFT                 (28)  /* MRAM Clock (MRPCLK) Select */
#define R_SYSC_SCKDIVCR_FCK_MASK                  0xf0000000

/* SCKDIVCR2 Register bit definitions */
#define R_SYSC_SCKDIVCR2_CPUCK0_SHIFT             (0)  /* CPU0 Clock (CPUCLK0) Select */
#define R_SYSC_SCKDIVCR2_CPUCK0_MASK              0xf
#  define R_SYSC_SCKDIVCR2_CPUCK0_0000                    (0 << R_SYSC_SCKDIVCR2_CPUCK0_SHIFT)  /* x 1/1 */
#  define R_SYSC_SCKDIVCR2_CPUCK0_0001                    (1 << R_SYSC_SCKDIVCR2_CPUCK0_SHIFT)  /* x 1/2 */
#  define R_SYSC_SCKDIVCR2_CPUCK0_0010                    (2 << R_SYSC_SCKDIVCR2_CPUCK0_SHIFT)  /* x 1/4 */
#  define R_SYSC_SCKDIVCR2_CPUCK0_0011                    (3 << R_SYSC_SCKDIVCR2_CPUCK0_SHIFT)  /* x 1/8 */
#  define R_SYSC_SCKDIVCR2_CPUCK0_0100                    (4 << R_SYSC_SCKDIVCR2_CPUCK0_SHIFT)  /* x 1/16 */
#  define R_SYSC_SCKDIVCR2_CPUCK0_0101                    (5 << R_SYSC_SCKDIVCR2_CPUCK0_SHIFT)  /* x 1/32 */
#  define R_SYSC_SCKDIVCR2_CPUCK0_0110                    (6 << R_SYSC_SCKDIVCR2_CPUCK0_SHIFT)  /* x 1/64 */
#  define R_SYSC_SCKDIVCR2_CPUCK0_1000                    (8 << R_SYSC_SCKDIVCR2_CPUCK0_SHIFT)  /* x 1/3 */
#  define R_SYSC_SCKDIVCR2_CPUCK0_1001                    (9 << R_SYSC_SCKDIVCR2_CPUCK0_SHIFT)  /* x 1/6 */
#  define R_SYSC_SCKDIVCR2_CPUCK0_1010                    (10 << R_SYSC_SCKDIVCR2_CPUCK0_SHIFT)  /* x 1/12 */
#  define R_SYSC_SCKDIVCR2_CPUCK0_1011                    (11 << R_SYSC_SCKDIVCR2_CPUCK0_SHIFT)  /* x 1/24 */

#define R_SYSC_SCKDIVCR2_CPUCK1_SHIFT             (4)  /* CPU1 Clock (CPUCLK1) Select */
#define R_SYSC_SCKDIVCR2_CPUCK1_MASK              0xf0
#  define R_SYSC_SCKDIVCR2_CPUCK1_0000                    (0 << R_SYSC_SCKDIVCR2_CPUCK1_SHIFT)  /* x 1/1 */
#  define R_SYSC_SCKDIVCR2_CPUCK1_0001                    (1 << R_SYSC_SCKDIVCR2_CPUCK1_SHIFT)  /* x 1/2 */
#  define R_SYSC_SCKDIVCR2_CPUCK1_0010                    (2 << R_SYSC_SCKDIVCR2_CPUCK1_SHIFT)  /* x 1/4 */
#  define R_SYSC_SCKDIVCR2_CPUCK1_0011                    (3 << R_SYSC_SCKDIVCR2_CPUCK1_SHIFT)  /* x 1/8 */
#  define R_SYSC_SCKDIVCR2_CPUCK1_0100                    (4 << R_SYSC_SCKDIVCR2_CPUCK1_SHIFT)  /* x 1/16 */
#  define R_SYSC_SCKDIVCR2_CPUCK1_0101                    (5 << R_SYSC_SCKDIVCR2_CPUCK1_SHIFT)  /* x 1/32 */
#  define R_SYSC_SCKDIVCR2_CPUCK1_0110                    (6 << R_SYSC_SCKDIVCR2_CPUCK1_SHIFT)  /* x 1/64 */
#  define R_SYSC_SCKDIVCR2_CPUCK1_1000                    (8 << R_SYSC_SCKDIVCR2_CPUCK1_SHIFT)  /* x 1/3 */
#  define R_SYSC_SCKDIVCR2_CPUCK1_1001                    (9 << R_SYSC_SCKDIVCR2_CPUCK1_SHIFT)  /* x 1/6 */
#  define R_SYSC_SCKDIVCR2_CPUCK1_1010                    (10 << R_SYSC_SCKDIVCR2_CPUCK1_SHIFT)  /* x 1/12 */
#  define R_SYSC_SCKDIVCR2_CPUCK1_1011                    (11 << R_SYSC_SCKDIVCR2_CPUCK1_SHIFT)  /* x 1/24 */

#define R_SYSC_SCKDIVCR2_CPUCK_SHIFT              (0)  /* CPU0 Clock (CPUCLK0) Select */
#define R_SYSC_SCKDIVCR2_CPUCK_MASK               0xf

#define R_SYSC_SCKDIVCR2_NPUCK_SHIFT              (8)  /* NPU Clock (NPUCLK) Select */
#define R_SYSC_SCKDIVCR2_NPUCK_MASK               0xf00

#define R_SYSC_SCKDIVCR2_MRICK_SHIFT              (12)  /* MRAM bus Clock (MRICLK) Select */
#define R_SYSC_SCKDIVCR2_MRICK_MASK               0xf000

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

/* PLLCR Register bit definitions */
#define R_SYSC_PLLCR_PLLSTP                       (1 << 0)  /* PLL1 Stop Control */

/* BCKCR Register bit definitions */
#define R_SYSC_BCKCR_BCLKDIV                      (1 << 0)  /* BCLK Pin Output Select */

#define R_SYSC_BCKCR_EBCKASEL                     (1 << 7)  /* External Bus Asynchronous Select */

/* MOSCCR Register bit definitions */
#define R_SYSC_MOSCCR_MOSTP                       (1 << 0)  /* Main Clock Oscillator Stop */

/* HOCOCR Register bit definitions */
#define R_SYSC_HOCOCR_HCSTP                       (1 << 0)  /* HOCO Stop */

/* HOCOCR2 Register bit definitions */
#define R_SYSC_HOCOCR2_HCFRQ0_SHIFT               (0)  /* HOCO Frequency Setting 0 */
#define R_SYSC_HOCOCR2_HCFRQ0_MASK                0x7
#  define R_SYSC_HOCOCR2_HCFRQ0_000                       (0 << R_SYSC_HOCOCR2_HCFRQ0_SHIFT)  /* 16 MHz */
#  define R_SYSC_HOCOCR2_HCFRQ0_001                       (1 << R_SYSC_HOCOCR2_HCFRQ0_SHIFT)  /* 18 MHz */
#  define R_SYSC_HOCOCR2_HCFRQ0_010                       (2 << R_SYSC_HOCOCR2_HCFRQ0_SHIFT)  /* 20 MHz */
#  define R_SYSC_HOCOCR2_HCFRQ0_100                       (4 << R_SYSC_HOCOCR2_HCFRQ0_SHIFT)  /* 32 MHz */
#  define R_SYSC_HOCOCR2_HCFRQ0_111                       (7 << R_SYSC_HOCOCR2_HCFRQ0_SHIFT)  /* 48 MHz */

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
#define R_SYSC_TRCKCR_TRCK_SHIFT                  (0)  /* Trace Clock Operating Frequency Select */
#define R_SYSC_TRCKCR_TRCK_MASK                   0xf
#  define R_SYSC_TRCKCR_TRCK_0000                         (0 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/1 */
#  define R_SYSC_TRCKCR_TRCK_0001                         (1 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/2 */
#  define R_SYSC_TRCKCR_TRCK_0010                         (2 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/4 (value after reset) */
#  define R_SYSC_TRCKCR_TRCK_0011                         (3 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/8 */
#  define R_SYSC_TRCKCR_TRCK_0100                         (4 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/16 */
#  define R_SYSC_TRCKCR_TRCK_0101                         (5 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/32 */
#  define R_SYSC_TRCKCR_TRCK_0110                         (6 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/64 */
#  define R_SYSC_TRCKCR_TRCK_0111                         (7 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/128 */
#  define R_SYSC_TRCKCR_TRCK_1000                         (8 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/256 */
#  define R_SYSC_TRCKCR_TRCK_1001                         (9 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/3 */
#  define R_SYSC_TRCKCR_TRCK_1010                         (10 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/6 */
#  define R_SYSC_TRCKCR_TRCK_1011                         (11 << R_SYSC_TRCKCR_TRCK_SHIFT)  /* 1/12 */

#define R_SYSC_TRCKCR_TRCKSEL                     (1 << 4)  /* Trace Clock Source Select */

#define R_SYSC_TRCKCR_TRCKEN                      (1 << 7)  /* Trace Clock Operating Enable */

/* OSTDCR Register bit definitions */
#define R_SYSC_OSTDCR_OSTDIE                      (1 << 0)  /* Oscillation Stop Detection Interrupt Enable */

#define R_SYSC_OSTDCR_OSTDE                       (1 << 7)  /* Oscillation Stop Detection Function Enable */

/* OSTDSR Register bit definitions */
#define R_SYSC_OSTDSR_OSTDF                       (1 << 0)  /* Oscillation Stop Detection Flag */

/* OSCMONR Register bit definitions */
#define R_SYSC_OSCMONR_MOCOMON                    (1 << 1)  /* MOCO operation monitor */

#define R_SYSC_OSCMONR_LOCOMON                    (1 << 2)  /* LOCO operation monitor */

/* PLL2CR Register bit definitions */
#define R_SYSC_PLL2CR_PLL2STP                     (1 << 0)  /* PLL2 Stop Control */

/* PLLCCR2 Register bit definitions */
#define R_SYSC_PLLCCR2_PLODIVP_SHIFT              (0)  /* PLL1 Output Frequency Division Ratio Select for output clock P */
#define R_SYSC_PLLCCR2_PLODIVP_MASK               0xf
#  define R_SYSC_PLLCCR2_PLODIVP_0001                     (1 << R_SYSC_PLLCCR2_PLODIVP_SHIFT)  /* × 1/2 */
#  define R_SYSC_PLLCCR2_PLODIVP_0010                     (2 << R_SYSC_PLLCCR2_PLODIVP_SHIFT)  /* × 1/3 */
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
#  define R_SYSC_PLLCCR2_PLODIVQ_1001                     (9 << R_SYSC_PLLCCR2_PLODIVQ_SHIFT)  /* × 1/1.5 */

#define R_SYSC_PLLCCR2_PLODIVR_SHIFT              (8)  /* PLL1 Output Frequency Division Ratio Select for output clock R */
#define R_SYSC_PLLCCR2_PLODIVR_MASK               0xf00
#  define R_SYSC_PLLCCR2_PLODIVR_0001                     (1 << R_SYSC_PLLCCR2_PLODIVR_SHIFT)  /* × 1/2 */
#  define R_SYSC_PLLCCR2_PLODIVR_0010                     (2 << R_SYSC_PLLCCR2_PLODIVR_SHIFT)  /* × 1/3 */
#  define R_SYSC_PLLCCR2_PLODIVR_0011                     (3 << R_SYSC_PLLCCR2_PLODIVR_SHIFT)  /* × 1/4 */
#  define R_SYSC_PLLCCR2_PLODIVR_0100                     (4 << R_SYSC_PLLCCR2_PLODIVR_SHIFT)  /* × 1/5 */
#  define R_SYSC_PLLCCR2_PLODIVR_0101                     (5 << R_SYSC_PLLCCR2_PLODIVR_SHIFT)  /* × 1/6 (Value after reset) */
#  define R_SYSC_PLLCCR2_PLODIVR_0111                     (7 << R_SYSC_PLLCCR2_PLODIVR_SHIFT)  /* × 1/8 */
#  define R_SYSC_PLLCCR2_PLODIVR_1000                     (8 << R_SYSC_PLLCCR2_PLODIVR_SHIFT)  /* × 1/9 */
#  define R_SYSC_PLLCCR2_PLODIVR_1001                     (9 << R_SYSC_PLLCCR2_PLODIVR_SHIFT)  /* × 1/1.5 */

/* PLL2CCR2 Register bit definitions */
#define R_SYSC_PLL2CCR2_PL2ODIVP_SHIFT            (0)  /* PLL2 Output Frequency Division Ratio Select for output clock P */
#define R_SYSC_PLL2CCR2_PL2ODIVP_MASK             0xf
#  define R_SYSC_PLL2CCR2_PL2ODIVP_0001                   (1 << R_SYSC_PLL2CCR2_PL2ODIVP_SHIFT)  /* × 1/2 */
#  define R_SYSC_PLL2CCR2_PL2ODIVP_0010                   (2 << R_SYSC_PLL2CCR2_PL2ODIVP_SHIFT)  /* × 1/3 */
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
#  define R_SYSC_PLL2CCR2_PL2ODIVQ_1001                   (9 << R_SYSC_PLL2CCR2_PL2ODIVQ_SHIFT)  /* × 1/1.5 */

#define R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT            (8)  /* PLL2 Output Frequency Division Ratio Select for output clock R */
#define R_SYSC_PLL2CCR2_PL2ODIVR_MASK             0xf00
#  define R_SYSC_PLL2CCR2_PL2ODIVR_0001                   (1 << R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT)  /* × 1/2 */
#  define R_SYSC_PLL2CCR2_PL2ODIVR_0010                   (2 << R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT)  /* × 1/3 */
#  define R_SYSC_PLL2CCR2_PL2ODIVR_0011                   (3 << R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT)  /* × 1/4 */
#  define R_SYSC_PLL2CCR2_PL2ODIVR_0100                   (4 << R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT)  /* × 1/5 */
#  define R_SYSC_PLL2CCR2_PL2ODIVR_0101                   (5 << R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT)  /* × 1/6 (Value after reset) */
#  define R_SYSC_PLL2CCR2_PL2ODIVR_0111                   (7 << R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT)  /* × 1/8 */
#  define R_SYSC_PLL2CCR2_PL2ODIVR_1000                   (8 << R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT)  /* × 1/9 */
#  define R_SYSC_PLL2CCR2_PL2ODIVR_1001                   (9 << R_SYSC_PLL2CCR2_PL2ODIVR_SHIFT)  /* × 1/1.5 */

/* EBCKOCR Register bit definitions */
#define R_SYSC_EBCKOCR_EBCKOEN                    (1 << 0)  /* EBCLK Pin Output Control */

/* SDCKOCR Register bit definitions */
#define R_SYSC_SDCKOCR_SDCKOEN                    (1 << 0)  /* SDCLK Pin Output Control */

/* SCICKDIVCR Register bit definitions */
#define R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT          (0)  /* SCI clock (SCICLK) Division Select */
#define R_SYSC_SCICKDIVCR_SCICKDIV_MASK           0xf
#  define R_SYSC_SCICKDIVCR_SCICKDIV_0000                 (0 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/1 (Value after reset) */
#  define R_SYSC_SCICKDIVCR_SCICKDIV_0001                 (1 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_SCICKDIVCR_SCICKDIV_0010                 (2 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_SCICKDIVCR_SCICKDIV_0011                 (3 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_SCICKDIVCR_SCICKDIV_0100                 (4 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_SCICKDIVCR_SCICKDIV_0101                 (5 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/3 */
#  define R_SYSC_SCICKDIVCR_SCICKDIV_0110                 (6 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/5 */
#  define R_SYSC_SCICKDIVCR_SCICKDIV_0111                 (7 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/10 */
#  define R_SYSC_SCICKDIVCR_SCICKDIV_1000                 (8 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/16 */
#  define R_SYSC_SCICKDIVCR_SCICKDIV_1001                 (9 << R_SYSC_SCICKDIVCR_SCICKDIV_SHIFT)  /* 1/32 */

#define R_SYSC_SCICKDIVCR_CKDIV_SHIFT             (0)  /* SCI clock (SCICLK) Division Select */
#define R_SYSC_SCICKDIVCR_CKDIV_MASK              0xf

/* SCICKCR Register bit definitions */
#define R_SYSC_SCICKCR_SCICKSEL_SHIFT             (0)  /* SCI Clock (SCICLK) Source Select */
#define R_SYSC_SCICKCR_SCICKSEL_MASK              0xf
#  define R_SYSC_SCICKCR_SCICKSEL_0000                    (0 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* HOCO */
#  define R_SYSC_SCICKCR_SCICKSEL_0001                    (1 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* MOCO (value after reset) */
#  define R_SYSC_SCICKCR_SCICKSEL_0010                    (2 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* LOCO */
#  define R_SYSC_SCICKCR_SCICKSEL_0011                    (3 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* Main clock oscillator */
#  define R_SYSC_SCICKCR_SCICKSEL_0100                    (4 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* Sub-clock oscillator */
#  define R_SYSC_SCICKCR_SCICKSEL_0101                    (5 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* PLL1P */
#  define R_SYSC_SCICKCR_SCICKSEL_0110                    (6 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* PLL2P */
#  define R_SYSC_SCICKCR_SCICKSEL_0111                    (7 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* PLL1Q */
#  define R_SYSC_SCICKCR_SCICKSEL_1000                    (8 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* PLL1R */
#  define R_SYSC_SCICKCR_SCICKSEL_1001                    (9 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* PLL2Q */
#  define R_SYSC_SCICKCR_SCICKSEL_1010                    (10 << R_SYSC_SCICKCR_SCICKSEL_SHIFT)  /* PLL2R */

#define R_SYSC_SCICKCR_SCICKSREQ                  (1 << 6)  /* SCI Clock (SCICLK) Switching Request */

#define R_SYSC_SCICKCR_SCICKSRDY                  (1 << 7)  /* SCI Clock (SCICLK) Switching Ready state flag */

#define R_SYSC_SCICKCR_CKSREQ                     (1 << 6)  /* SCI clock (SCICLK) Switching Request */

#define R_SYSC_SCICKCR_CKSRDY                     (1 << 7)  /* SCI clock (SCICLK) Switching Ready state flag */

/* SPICKDIVCR Register bit definitions */
#define R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT          (0)  /* SPI clock (SPICLK) Division Select */
#define R_SYSC_SPICKDIVCR_SPICKDIV_MASK           0xf
#  define R_SYSC_SPICKDIVCR_SPICKDIV_0000                 (0 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/1 (Value after reset) */
#  define R_SYSC_SPICKDIVCR_SPICKDIV_0001                 (1 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_SPICKDIVCR_SPICKDIV_0010                 (2 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_SPICKDIVCR_SPICKDIV_0011                 (3 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_SPICKDIVCR_SPICKDIV_0100                 (4 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_SPICKDIVCR_SPICKDIV_0101                 (5 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/3 */
#  define R_SYSC_SPICKDIVCR_SPICKDIV_0110                 (6 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/5 */
#  define R_SYSC_SPICKDIVCR_SPICKDIV_0111                 (7 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/10 */
#  define R_SYSC_SPICKDIVCR_SPICKDIV_1000                 (8 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/16 */
#  define R_SYSC_SPICKDIVCR_SPICKDIV_1001                 (9 << R_SYSC_SPICKDIVCR_SPICKDIV_SHIFT)  /* 1/32 */

#define R_SYSC_SPICKDIVCR_CKDIV_SHIFT             (0)  /* SPI clock (SPICLK) Division Select */
#define R_SYSC_SPICKDIVCR_CKDIV_MASK              0xf

/* SPICKCR Register bit definitions */
#define R_SYSC_SPICKCR_SPICKSEL_SHIFT             (0)  /* SPI Clock (SPICLK) Source Select */
#define R_SYSC_SPICKCR_SPICKSEL_MASK              0xf
#  define R_SYSC_SPICKCR_SPICKSEL_0000                    (0 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* HOCO */
#  define R_SYSC_SPICKCR_SPICKSEL_0001                    (1 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* MOCO (value after reset) */
#  define R_SYSC_SPICKCR_SPICKSEL_0010                    (2 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* LOCO */
#  define R_SYSC_SPICKCR_SPICKSEL_0011                    (3 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* Main clock oscillator */
#  define R_SYSC_SPICKCR_SPICKSEL_0100                    (4 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* Sub-clock oscillator */
#  define R_SYSC_SPICKCR_SPICKSEL_0101                    (5 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* PLL1P */
#  define R_SYSC_SPICKCR_SPICKSEL_0110                    (6 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* PLL2P */
#  define R_SYSC_SPICKCR_SPICKSEL_0111                    (7 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* PLL1Q */
#  define R_SYSC_SPICKCR_SPICKSEL_1000                    (8 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* PLL1R */
#  define R_SYSC_SPICKCR_SPICKSEL_1001                    (9 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* PLL2Q */
#  define R_SYSC_SPICKCR_SPICKSEL_1010                    (10 << R_SYSC_SPICKCR_SPICKSEL_SHIFT)  /* PLL2R */

#define R_SYSC_SPICKCR_SPICKSREQ                  (1 << 6)  /* SPI Clock (SPICLK) Switching Request */

#define R_SYSC_SPICKCR_SPICKSRDY                  (1 << 7)  /* SPI clock (SPICLK) Switching Ready State Flag */

#define R_SYSC_SPICKCR_CKSEL_SHIFT                (0)  /* SPI clock (SPICLK) Source Select */
#define R_SYSC_SPICKCR_CKSEL_MASK                 0xf

#define R_SYSC_SPICKCR_CKSREQ                     (1 << 6)  /* SPI clock (SPICLK) Switching Request */

#define R_SYSC_SPICKCR_CKSRDY                     (1 << 7)  /* SPI clock (SPICLK) Switching Ready state flag */

/* ADCCKDIVCR Register bit definitions */
#define R_SYSC_ADCCKDIVCR_ADCCKDIV_SHIFT          (0)  /* ADC Clock (ADCCLK) Division Select */
#define R_SYSC_ADCCKDIVCR_ADCCKDIV_MASK           0xf
#  define R_SYSC_ADCCKDIVCR_ADCCKDIV_0000                 (0 << R_SYSC_ADCCKDIVCR_ADCCKDIV_SHIFT)  /* 1/1 (value after reset) */
#  define R_SYSC_ADCCKDIVCR_ADCCKDIV_0001                 (1 << R_SYSC_ADCCKDIVCR_ADCCKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_ADCCKDIVCR_ADCCKDIV_0010                 (2 << R_SYSC_ADCCKDIVCR_ADCCKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_ADCCKDIVCR_ADCCKDIV_0011                 (3 << R_SYSC_ADCCKDIVCR_ADCCKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_ADCCKDIVCR_ADCCKDIV_0100                 (4 << R_SYSC_ADCCKDIVCR_ADCCKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_ADCCKDIVCR_ADCCKDIV_0111                 (7 << R_SYSC_ADCCKDIVCR_ADCCKDIV_SHIFT)  /* 1/10 */
#  define R_SYSC_ADCCKDIVCR_ADCCKDIV_1000                 (8 << R_SYSC_ADCCKDIVCR_ADCCKDIV_SHIFT)  /* 1/16 */
#  define R_SYSC_ADCCKDIVCR_ADCCKDIV_1001                 (9 << R_SYSC_ADCCKDIVCR_ADCCKDIV_SHIFT)  /* 1/32 */

#define R_SYSC_ADCCKDIVCR_CKDIV_SHIFT             (0)  /* Clock Division Select */
#define R_SYSC_ADCCKDIVCR_CKDIV_MASK              0xf

/* ADCCKCR Register bit definitions */
#define R_SYSC_ADCCKCR_ADCCKSEL_SHIFT             (0)  /* ADC Clock (ADCCLK) Source Select */
#define R_SYSC_ADCCKCR_ADCCKSEL_MASK              0xf
#  define R_SYSC_ADCCKCR_ADCCKSEL_0000                    (0 << R_SYSC_ADCCKCR_ADCCKSEL_SHIFT)  /* HOCO */
#  define R_SYSC_ADCCKCR_ADCCKSEL_0001                    (1 << R_SYSC_ADCCKCR_ADCCKSEL_SHIFT)  /* MOCO (value after reset) */
#  define R_SYSC_ADCCKCR_ADCCKSEL_0010                    (2 << R_SYSC_ADCCKCR_ADCCKSEL_SHIFT)  /* LOCO */
#  define R_SYSC_ADCCKCR_ADCCKSEL_0011                    (3 << R_SYSC_ADCCKCR_ADCCKSEL_SHIFT)  /* Main clock oscillator */
#  define R_SYSC_ADCCKCR_ADCCKSEL_0100                    (4 << R_SYSC_ADCCKCR_ADCCKSEL_SHIFT)  /* Sub-clock oscillator */
#  define R_SYSC_ADCCKCR_ADCCKSEL_0101                    (5 << R_SYSC_ADCCKCR_ADCCKSEL_SHIFT)  /* PLL1P */
#  define R_SYSC_ADCCKCR_ADCCKSEL_0110                    (6 << R_SYSC_ADCCKCR_ADCCKSEL_SHIFT)  /* PLL2P */
#  define R_SYSC_ADCCKCR_ADCCKSEL_0111                    (7 << R_SYSC_ADCCKCR_ADCCKSEL_SHIFT)  /* PLL1Q */
#  define R_SYSC_ADCCKCR_ADCCKSEL_1000                    (8 << R_SYSC_ADCCKCR_ADCCKSEL_SHIFT)  /* PLL1R */
#  define R_SYSC_ADCCKCR_ADCCKSEL_1001                    (9 << R_SYSC_ADCCKCR_ADCCKSEL_SHIFT)  /* PLL2Q */
#  define R_SYSC_ADCCKCR_ADCCKSEL_1010                    (10 << R_SYSC_ADCCKCR_ADCCKSEL_SHIFT)  /* PLL2R */

#define R_SYSC_ADCCKCR_ADCCKSREQ                  (1 << 6)  /* ADC Clock (ADCCLK) Switching Request */

#define R_SYSC_ADCCKCR_ADCCKSRDY                  (1 << 7)  /* ADC Clock (ADCCLK) Switching Ready State Flag */

#define R_SYSC_ADCCKCR_CKSEL_SHIFT                (0)  /* Clock Source Select */
#define R_SYSC_ADCCKCR_CKSEL_MASK                 0xf

#define R_SYSC_ADCCKCR_CKSREQ                     (1 << 6)  /* Clock Switching Request */

#define R_SYSC_ADCCKCR_CKSRDY                     (1 << 7)  /* Clock Switching Ready state flag */

/* GPTCKDIVCR Register bit definitions */
#define R_SYSC_GPTCKDIVCR_GPTCKDIV_SHIFT          (0)  /* GPT Clock (GPTCLK) Division Select */
#define R_SYSC_GPTCKDIVCR_GPTCKDIV_MASK           0xf
#  define R_SYSC_GPTCKDIVCR_GPTCKDIV_0000                 (0 << R_SYSC_GPTCKDIVCR_GPTCKDIV_SHIFT)  /* 1/1 (value after reset) */
#  define R_SYSC_GPTCKDIVCR_GPTCKDIV_0001                 (1 << R_SYSC_GPTCKDIVCR_GPTCKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_GPTCKDIVCR_GPTCKDIV_0010                 (2 << R_SYSC_GPTCKDIVCR_GPTCKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_GPTCKDIVCR_GPTCKDIV_0011                 (3 << R_SYSC_GPTCKDIVCR_GPTCKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_GPTCKDIVCR_GPTCKDIV_0100                 (4 << R_SYSC_GPTCKDIVCR_GPTCKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_GPTCKDIVCR_GPTCKDIV_0101                 (5 << R_SYSC_GPTCKDIVCR_GPTCKDIV_SHIFT)  /* 1/3 */
#  define R_SYSC_GPTCKDIVCR_GPTCKDIV_0110                 (6 << R_SYSC_GPTCKDIVCR_GPTCKDIV_SHIFT)  /* 1/5 */
#  define R_SYSC_GPTCKDIVCR_GPTCKDIV_0111                 (7 << R_SYSC_GPTCKDIVCR_GPTCKDIV_SHIFT)  /* 1/10 */
#  define R_SYSC_GPTCKDIVCR_GPTCKDIV_1000                 (8 << R_SYSC_GPTCKDIVCR_GPTCKDIV_SHIFT)  /* 1/16 */
#  define R_SYSC_GPTCKDIVCR_GPTCKDIV_1001                 (9 << R_SYSC_GPTCKDIVCR_GPTCKDIV_SHIFT)  /* 1/32 */

/* GPTCKCR Register bit definitions */
#define R_SYSC_GPTCKCR_GPTCKSEL_SHIFT             (0)  /* GPT Clock (GPTCLK) Source Select */
#define R_SYSC_GPTCKCR_GPTCKSEL_MASK              0xf
#  define R_SYSC_GPTCKCR_GPTCKSEL_0000                    (0 << R_SYSC_GPTCKCR_GPTCKSEL_SHIFT)  /* HOCO */
#  define R_SYSC_GPTCKCR_GPTCKSEL_0001                    (1 << R_SYSC_GPTCKCR_GPTCKSEL_SHIFT)  /* MOCO (value after reset) */
#  define R_SYSC_GPTCKCR_GPTCKSEL_0011                    (3 << R_SYSC_GPTCKCR_GPTCKSEL_SHIFT)  /* Main clock oscillator */
#  define R_SYSC_GPTCKCR_GPTCKSEL_0101                    (5 << R_SYSC_GPTCKCR_GPTCKSEL_SHIFT)  /* PLL1P */
#  define R_SYSC_GPTCKCR_GPTCKSEL_0110                    (6 << R_SYSC_GPTCKCR_GPTCKSEL_SHIFT)  /* PLL2P */
#  define R_SYSC_GPTCKCR_GPTCKSEL_0111                    (7 << R_SYSC_GPTCKCR_GPTCKSEL_SHIFT)  /* PLL1Q */
#  define R_SYSC_GPTCKCR_GPTCKSEL_1000                    (8 << R_SYSC_GPTCKCR_GPTCKSEL_SHIFT)  /* PLL1R */
#  define R_SYSC_GPTCKCR_GPTCKSEL_1001                    (9 << R_SYSC_GPTCKCR_GPTCKSEL_SHIFT)  /* PLL2Q */
#  define R_SYSC_GPTCKCR_GPTCKSEL_1010                    (10 << R_SYSC_GPTCKCR_GPTCKSEL_SHIFT)  /* PLL2R */

#define R_SYSC_GPTCKCR_GPTCKSREQ                  (1 << 6)  /* GPT Clock (GPTCLK) Switching Request */

#define R_SYSC_GPTCKCR_GPTCKSRDY                  (1 << 7)  /* GPT Clock (GPTCLK) Switching Ready State Flag */

/* LCDCKDIVCR Register bit definitions */
#define R_SYSC_LCDCKDIVCR_LCDCKDIV_SHIFT          (0)  /* LCD Clock (LCDCLK) Division Select */
#define R_SYSC_LCDCKDIVCR_LCDCKDIV_MASK           0xf
#  define R_SYSC_LCDCKDIVCR_LCDCKDIV_0000                 (0 << R_SYSC_LCDCKDIVCR_LCDCKDIV_SHIFT)  /* 1/1 */
#  define R_SYSC_LCDCKDIVCR_LCDCKDIV_0001                 (1 << R_SYSC_LCDCKDIVCR_LCDCKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_LCDCKDIVCR_LCDCKDIV_0010                 (2 << R_SYSC_LCDCKDIVCR_LCDCKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_LCDCKDIVCR_LCDCKDIV_0011                 (3 << R_SYSC_LCDCKDIVCR_LCDCKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_LCDCKDIVCR_LCDCKDIV_0100                 (4 << R_SYSC_LCDCKDIVCR_LCDCKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_LCDCKDIVCR_LCDCKDIV_0101                 (5 << R_SYSC_LCDCKDIVCR_LCDCKDIV_SHIFT)  /* 1/3 */
#  define R_SYSC_LCDCKDIVCR_LCDCKDIV_0110                 (6 << R_SYSC_LCDCKDIVCR_LCDCKDIV_SHIFT)  /* 1/5 */
#  define R_SYSC_LCDCKDIVCR_LCDCKDIV_0111                 (7 << R_SYSC_LCDCKDIVCR_LCDCKDIV_SHIFT)  /* 1/10 */
#  define R_SYSC_LCDCKDIVCR_LCDCKDIV_1000                 (8 << R_SYSC_LCDCKDIVCR_LCDCKDIV_SHIFT)  /* 1/16 */
#  define R_SYSC_LCDCKDIVCR_LCDCKDIV_1001                 (9 << R_SYSC_LCDCKDIVCR_LCDCKDIV_SHIFT)  /* 1/32 */

#define R_SYSC_LCDCKDIVCR_CKDIV_SHIFT             (0)  /* LCD clock (LCDCLK) Division Select */
#define R_SYSC_LCDCKDIVCR_CKDIV_MASK              0xf

/* LCDCKCR Register bit definitions */
#define R_SYSC_LCDCKCR_LCDCKSEL_SHIFT             (0)  /* LCD Clock (LCDCLK) Source Select */
#define R_SYSC_LCDCKCR_LCDCKSEL_MASK              0xf
#  define R_SYSC_LCDCKCR_LCDCKSEL_0001                    (1 << R_SYSC_LCDCKCR_LCDCKSEL_SHIFT)  /* MOCO (value after reset) */
#  define R_SYSC_LCDCKCR_LCDCKSEL_0101                    (5 << R_SYSC_LCDCKCR_LCDCKSEL_SHIFT)  /* PLL1P */
#  define R_SYSC_LCDCKCR_LCDCKSEL_0110                    (6 << R_SYSC_LCDCKCR_LCDCKSEL_SHIFT)  /* PLL2P */
#  define R_SYSC_LCDCKCR_LCDCKSEL_0111                    (7 << R_SYSC_LCDCKCR_LCDCKSEL_SHIFT)  /* PLL1Q */
#  define R_SYSC_LCDCKCR_LCDCKSEL_1000                    (8 << R_SYSC_LCDCKCR_LCDCKSEL_SHIFT)  /* PLL1R */
#  define R_SYSC_LCDCKCR_LCDCKSEL_1001                    (9 << R_SYSC_LCDCKCR_LCDCKSEL_SHIFT)  /* PLL2Q */
#  define R_SYSC_LCDCKCR_LCDCKSEL_1010                    (10 << R_SYSC_LCDCKCR_LCDCKSEL_SHIFT)  /* PLL2R */

#define R_SYSC_LCDCKCR_LCDCKSREQ                  (1 << 6)  /* LCD Clock (LCDCLK) Switching Request */

#define R_SYSC_LCDCKCR_LCDCKSRDY                  (1 << 7)  /* LCD Clock (LCDCLK) Switching Ready State Flag */

#define R_SYSC_LCDCKCR_CKSEL_SHIFT                (0)  /* LCD clock (LCDCLK) Source Select */
#define R_SYSC_LCDCKCR_CKSEL_MASK                 0xf

#define R_SYSC_LCDCKCR_CKSREQ                     (1 << 6)  /* LCD clock (LCDCLK) Switching Request */

#define R_SYSC_LCDCKCR_CKSRDY                     (1 << 7)  /* LCD clock (LCDCLK) Switching Ready state flag */

/* MOCOUTCR Register bit definitions */
#define R_SYSC_MOCOUTCR_MOCOUTRM_SHIFT            (0)  /* MOCO User Trimming */
#define R_SYSC_MOCOUTCR_MOCOUTRM_MASK             0xff

/* HOCOUTCR Register bit definitions */
#define R_SYSC_HOCOUTCR_HOCOUTRM_SHIFT            (0)  /* HOCO User Trimming */
#define R_SYSC_HOCOUTCR_HOCOUTRM_MASK             0xff

/* USBCKDIVCR Register bit definitions */
#define R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT          (0)  /* USB Clock (USBCLK) Division Select */
#define R_SYSC_USBCKDIVCR_USBCKDIV_MASK           0xf
#  define R_SYSC_USBCKDIVCR_USBCKDIV_0000                 (0 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/1 (value after reset) */
#  define R_SYSC_USBCKDIVCR_USBCKDIV_0001                 (1 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_USBCKDIVCR_USBCKDIV_0010                 (2 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_USBCKDIVCR_USBCKDIV_0011                 (3 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_USBCKDIVCR_USBCKDIV_0100                 (4 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_USBCKDIVCR_USBCKDIV_0101                 (5 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/3 */
#  define R_SYSC_USBCKDIVCR_USBCKDIV_0110                 (6 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/5 */
#  define R_SYSC_USBCKDIVCR_USBCKDIV_0111                 (7 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/10 */
#  define R_SYSC_USBCKDIVCR_USBCKDIV_1000                 (8 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/16 */
#  define R_SYSC_USBCKDIVCR_USBCKDIV_1001                 (9 << R_SYSC_USBCKDIVCR_USBCKDIV_SHIFT)  /* 1/32 */

/* OCTACKDIVCR Register bit definitions */
#define R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT        (0)  /* Octal-SPI Clock (OCTACLK) Division Select */
#define R_SYSC_OCTACKDIVCR_OCTACKDIV_MASK         0xf
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_0000               (0 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/1 (Value after reset) */
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_0001               (1 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_0010               (2 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_0011               (3 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_0100               (4 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_0101               (5 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/3 */
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_0110               (6 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/5 */
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_0111               (7 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/10 */
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_1000               (8 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/16 */
#  define R_SYSC_OCTACKDIVCR_OCTACKDIV_1001               (9 << R_SYSC_OCTACKDIVCR_OCTACKDIV_SHIFT)  /* 1/32 */

/* CANFDCKDIVCR Register bit definitions */
#define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT      (0)  /* CANFD core clock (CANFDCLK) Division Select */
#define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_MASK       0xf
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_0000             (0 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/1 (Value after reset) */
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_0001             (1 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_0010             (2 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_0011             (3 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_0100             (4 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_0101             (5 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/3 */
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_0110             (6 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/5 */
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_0111             (7 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/10 */
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_1000             (8 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/16 */
#  define R_SYSC_CANFDCKDIVCR_CANFDCKDIV_1001             (9 << R_SYSC_CANFDCKDIVCR_CANFDCKDIV_SHIFT)  /* 1/32 */

/* USB60CKDIVCR Register bit definitions */
#define R_SYSC_USB60CKDIVCR_USB60CKDIV_SHIFT      (0)  /* USB clock (USB60CLK) Division Select */
#define R_SYSC_USB60CKDIVCR_USB60CKDIV_MASK       0xf
#  define R_SYSC_USB60CKDIVCR_USB60CKDIV_0000             (0 << R_SYSC_USB60CKDIVCR_USB60CKDIV_SHIFT)  /* 1/1 (Value after reset) */
#  define R_SYSC_USB60CKDIVCR_USB60CKDIV_0001             (1 << R_SYSC_USB60CKDIVCR_USB60CKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_USB60CKDIVCR_USB60CKDIV_0010             (2 << R_SYSC_USB60CKDIVCR_USB60CKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_USB60CKDIVCR_USB60CKDIV_0011             (3 << R_SYSC_USB60CKDIVCR_USB60CKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_USB60CKDIVCR_USB60CKDIV_0100             (4 << R_SYSC_USB60CKDIVCR_USB60CKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_USB60CKDIVCR_USB60CKDIV_0101             (5 << R_SYSC_USB60CKDIVCR_USB60CKDIV_SHIFT)  /* 1/3 */
#  define R_SYSC_USB60CKDIVCR_USB60CKDIV_0110             (6 << R_SYSC_USB60CKDIVCR_USB60CKDIV_SHIFT)  /* 1/5 */
#  define R_SYSC_USB60CKDIVCR_USB60CKDIV_0111             (7 << R_SYSC_USB60CKDIVCR_USB60CKDIV_SHIFT)  /* 1/10 */
#  define R_SYSC_USB60CKDIVCR_USB60CKDIV_1000             (8 << R_SYSC_USB60CKDIVCR_USB60CKDIV_SHIFT)  /* 1/16 */
#  define R_SYSC_USB60CKDIVCR_USB60CKDIV_1001             (9 << R_SYSC_USB60CKDIVCR_USB60CKDIV_SHIFT)  /* 1/32 */

/* I3CCKDIVCR Register bit definitions */
#define R_SYSC_I3CCKDIVCR_I3CCKDIV_SHIFT          (0)  /* I3C clock (I3CCLK) Division Select */
#define R_SYSC_I3CCKDIVCR_I3CCKDIV_MASK           0xf
#  define R_SYSC_I3CCKDIVCR_I3CCKDIV_0000                 (0 << R_SYSC_I3CCKDIVCR_I3CCKDIV_SHIFT)  /* 1/1 (Value after reset) */
#  define R_SYSC_I3CCKDIVCR_I3CCKDIV_0001                 (1 << R_SYSC_I3CCKDIVCR_I3CCKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_I3CCKDIVCR_I3CCKDIV_0010                 (2 << R_SYSC_I3CCKDIVCR_I3CCKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_I3CCKDIVCR_I3CCKDIV_0011                 (3 << R_SYSC_I3CCKDIVCR_I3CCKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_I3CCKDIVCR_I3CCKDIV_0100                 (4 << R_SYSC_I3CCKDIVCR_I3CCKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_I3CCKDIVCR_I3CCKDIV_0101                 (5 << R_SYSC_I3CCKDIVCR_I3CCKDIV_SHIFT)  /* 1/3 */
#  define R_SYSC_I3CCKDIVCR_I3CCKDIV_0110                 (6 << R_SYSC_I3CCKDIVCR_I3CCKDIV_SHIFT)  /* 1/5 */
#  define R_SYSC_I3CCKDIVCR_I3CCKDIV_0111                 (7 << R_SYSC_I3CCKDIVCR_I3CCKDIV_SHIFT)  /* 1/10 */
#  define R_SYSC_I3CCKDIVCR_I3CCKDIV_1000                 (8 << R_SYSC_I3CCKDIVCR_I3CCKDIV_SHIFT)  /* 1/16 */
#  define R_SYSC_I3CCKDIVCR_I3CCKDIV_1001                 (9 << R_SYSC_I3CCKDIVCR_I3CCKDIV_SHIFT)  /* 1/32 */

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

#define R_SYSC_CANFDCKCR_CANFDCKSRDY              (1 << 7)  /* CANFD Core Clock (CANFDCLK) Switching Ready state flag */

/* USB60CKCR Register bit definitions */
#define R_SYSC_USB60CKCR_USB60CKSEL_SHIFT         (0)  /* USB60 Clock (USB60CK) Source Select */
#define R_SYSC_USB60CKCR_USB60CKSEL_MASK          0xf
#  define R_SYSC_USB60CKCR_USB60CKSEL_0000                (0 << R_SYSC_USB60CKCR_USB60CKSEL_SHIFT)  /* HOCO */
#  define R_SYSC_USB60CKCR_USB60CKSEL_0001                (1 << R_SYSC_USB60CKCR_USB60CKSEL_SHIFT)  /* MOCO (Value after reset) */
#  define R_SYSC_USB60CKCR_USB60CKSEL_0011                (3 << R_SYSC_USB60CKCR_USB60CKSEL_SHIFT)  /* Main clock oscillator */
#  define R_SYSC_USB60CKCR_USB60CKSEL_0101                (5 << R_SYSC_USB60CKCR_USB60CKSEL_SHIFT)  /* PLL1P */
#  define R_SYSC_USB60CKCR_USB60CKSEL_0110                (6 << R_SYSC_USB60CKCR_USB60CKSEL_SHIFT)  /* PLL2P */
#  define R_SYSC_USB60CKCR_USB60CKSEL_0111                (7 << R_SYSC_USB60CKCR_USB60CKSEL_SHIFT)  /* PLL1Q */
#  define R_SYSC_USB60CKCR_USB60CKSEL_1000                (8 << R_SYSC_USB60CKCR_USB60CKSEL_SHIFT)  /* PLL1R */
#  define R_SYSC_USB60CKCR_USB60CKSEL_1001                (9 << R_SYSC_USB60CKCR_USB60CKSEL_SHIFT)  /* PLL2Q */
#  define R_SYSC_USB60CKCR_USB60CKSEL_1010                (10 << R_SYSC_USB60CKCR_USB60CKSEL_SHIFT)  /* PLL2R */

#define R_SYSC_USB60CKCR_USB60CKSREQ              (1 << 6)  /* USB60 Clock (USB60CK) Switching Request */

#define R_SYSC_USB60CKCR_USB60CKSRDY              (1 << 7)  /* USB60 Clock (USB60CK) Switching Ready state flag */

/* I3CCKCR Register bit definitions */
#define R_SYSC_I3CCKCR_I3CCKSEL_SHIFT             (0)  /* I3C Clock (I3CCLK) Source Select */
#define R_SYSC_I3CCKCR_I3CCKSEL_MASK              0xf
#  define R_SYSC_I3CCKCR_I3CCKSEL_0001                    (1 << R_SYSC_I3CCKCR_I3CCKSEL_SHIFT)  /* MOCO (value after reset) */
#  define R_SYSC_I3CCKCR_I3CCKSEL_0101                    (5 << R_SYSC_I3CCKCR_I3CCKSEL_SHIFT)  /* PLL1P */
#  define R_SYSC_I3CCKCR_I3CCKSEL_0110                    (6 << R_SYSC_I3CCKCR_I3CCKSEL_SHIFT)  /* PLL2P */
#  define R_SYSC_I3CCKCR_I3CCKSEL_0111                    (7 << R_SYSC_I3CCKCR_I3CCKSEL_SHIFT)  /* PLL1Q */
#  define R_SYSC_I3CCKCR_I3CCKSEL_1000                    (8 << R_SYSC_I3CCKCR_I3CCKSEL_SHIFT)  /* PLL1R */
#  define R_SYSC_I3CCKCR_I3CCKSEL_1001                    (9 << R_SYSC_I3CCKCR_I3CCKSEL_SHIFT)  /* PLL2Q */
#  define R_SYSC_I3CCKCR_I3CCKSEL_1010                    (10 << R_SYSC_I3CCKCR_I3CCKSEL_SHIFT)  /* PLL2R */

#define R_SYSC_I3CCKCR_I3CCKSREQ                  (1 << 6)  /* I3C Clock (I3CCLK) Switching Request */

#define R_SYSC_I3CCKCR_I3CCKSRDY                  (1 << 7)  /* I3C Clock (I3CCLK) Switching Ready state flag */

/* MOSCSCR Register bit definitions */
#define R_SYSC_MOSCSCR_MOSCSOKP                   (1 << 0)  /* Main Clock Oscillator Standby Oscillation Keep select */

/* HOCOSCR Register bit definitions */
#define R_SYSC_HOCOSCR_HOCOSOKP                   (1 << 0)  /* HOCO Standby Oscillation Keep select. */

#define R_SYSC_HOCOSCR_HOSCSOKP                   (1 << 0)  /* HOCO Standby Oscillation Keep select */

/* MOCOSCR Register bit definitions */
#define R_SYSC_MOCOSCR_MOCOSOKP                   (1 << 0)  /* MOCO Standby Oscillation Keep select */

/* OPCCR Register bit definitions */
#define R_SYSC_OPCCR_OPCM_SHIFT                   (0)  /* Operating Power Control Mode Select */
#define R_SYSC_OPCCR_OPCM_MASK                    0x3
#  define R_SYSC_OPCCR_OPCM_00                            (0 << R_SYSC_OPCCR_OPCM_SHIFT)  /* High-speed mode */
#  define R_SYSC_OPCCR_OPCM_01                            (1 << R_SYSC_OPCCR_OPCM_SHIFT)  /* Prohibited */
#  define R_SYSC_OPCCR_OPCM_10                            (2 << R_SYSC_OPCCR_OPCM_SHIFT)  /* Prohibited */
#  define R_SYSC_OPCCR_OPCM_11                            (3 << R_SYSC_OPCCR_OPCM_SHIFT)  /* Prohibited */

#define R_SYSC_OPCCR_OPCMTSF                      (1 << 4)  /* Operating Power Control Mode Transition Status Flag */

/* MOSCWTCR Register bit definitions */
#define R_SYSC_MOSCWTCR_MSTS_SHIFT                (0)  /* Main Clock Oscillator Wait Time Setting */
#define R_SYSC_MOSCWTCR_MSTS_MASK                 0xf
#  define R_SYSC_MOSCWTCR_MSTS_0X0                        (0 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 3 cycles (11.4 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X1                        (1 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 35 cycles (133.5 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X2                        (2 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 67 cycles (255.6 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X3                        (3 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 131 cycles (499.7 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X4                        (4 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 259 cycles (988.0 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X5                        (5 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 547 cycles (2086.6 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X6                        (6 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 1059 cycles (4039.8 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X7                        (7 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 2147 cycles (8190.2 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X8                        (8 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 4291 cycles (16368.9 us) */
#  define R_SYSC_MOSCWTCR_MSTS_0X9                        (9 << R_SYSC_MOSCWTCR_MSTS_SHIFT)  /* Wait time = 8163 cycles (31139.4 us) */

/* PLLCCR Register bit definitions */
#define R_SYSC_PLLCCR_PLIDIV_SHIFT                (0)  /* PLL1 Input Frequency Division Ratio Select */
#define R_SYSC_PLLCCR_PLIDIV_MASK                 0x3
#  define R_SYSC_PLLCCR_PLIDIV_00                         (0 << R_SYSC_PLLCCR_PLIDIV_SHIFT)  /* 1/1 */
#  define R_SYSC_PLLCCR_PLIDIV_01                         (1 << R_SYSC_PLLCCR_PLIDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_PLLCCR_PLIDIV_10                         (2 << R_SYSC_PLLCCR_PLIDIV_SHIFT)  /* 1/3 */

#define R_SYSC_PLLCCR_PLSRCSEL                    (1 << 4)  /* PLL1 Clock Source Select */

#define R_SYSC_PLLCCR_PLLMULNF_SHIFT              (6)  /* PLL1 Frequency Multiplication Fractional Factor Select */
#define R_SYSC_PLLCCR_PLLMULNF_MASK               0xc0
#  define R_SYSC_PLLCCR_PLLMULNF_00                       (0 << R_SYSC_PLLCCR_PLLMULNF_SHIFT)  /* 0.00 (Value after reset) */
#  define R_SYSC_PLLCCR_PLLMULNF_01                       (1 << R_SYSC_PLLCCR_PLLMULNF_SHIFT)  /* 0.33 (1/3) */
#  define R_SYSC_PLLCCR_PLLMULNF_10                       (2 << R_SYSC_PLLCCR_PLLMULNF_SHIFT)  /* 0.66 (2/3) */
#  define R_SYSC_PLLCCR_PLLMULNF_11                       (3 << R_SYSC_PLLCCR_PLLMULNF_SHIFT)  /* 0.50 (1/2) */

#define R_SYSC_PLLCCR_PLLMUL_SHIFT                (8)  /* PLL1 Frequency Multiplication Factor Select */
#define R_SYSC_PLLCCR_PLLMUL_MASK                 0x1ff00

/* RSTSR1 Register bit definitions */
#define R_SYSC_RSTSR1_IWDTRF                      (1 << 0)  /* Independent Watchdog Timer Reset Detect Flag */

#define R_SYSC_RSTSR1_WDT0RF                      (1 << 1)  /* Watchdog Timer 0 Reset Detect Flag */

#define R_SYSC_RSTSR1_SWRF                        (1 << 2)  /* Software Reset Detect Flag */

#define R_SYSC_RSTSR1_CLU0RF                      (1 << 4)  /* CPU0 Lockup Reset Detect Flag */

#define R_SYSC_RSTSR1_LM0RF                       (1 << 5)  /* Local memory 0 error Reset Detect Flag */

#define R_SYSC_RSTSR1_BUSRF                       (1 << 10)  /* Bus Error Reset Detect Flag */

#define R_SYSC_RSTSR1_CMRF                        (1 << 14)  /* Common Memory Error Reset Detect Flag */

#define R_SYSC_RSTSR1_WDT1RF                      (1 << 17)  /* Watchdog Timer 1 Reset Detect Flag */

#define R_SYSC_RSTSR1_CLU1RF                      (1 << 20)  /* CPU1 Lockup Reset Detect Flag */

#define R_SYSC_RSTSR1_LM1RF                       (1 << 21)  /* Local memory 1 error Reset Detect Flag */

#define R_SYSC_RSTSR1_WDTRF                       (1 << 1)  /* Watchdog Timer Reset Detect Flag */

#define R_SYSC_RSTSR1_CLURF                       (1 << 4)  /* CPU0 Lockup Reset Detect flags */

#define R_SYSC_RSTSR1_BUSSRF                      (1 << 10)  /* Bus Slave MPU Reset Detect Flag */

#define R_SYSC_RSTSR1_NWRF                        (1 << 22)  /* Network Reset Detect Flag */

/* PLL2CCR Register bit definitions */
#define R_SYSC_PLL2CCR_PL2IDIV_SHIFT              (0)  /* PLL2 Input Frequency Division Ratio Select */
#define R_SYSC_PLL2CCR_PL2IDIV_MASK               0x3
#  define R_SYSC_PLL2CCR_PL2IDIV_00                       (0 << R_SYSC_PLL2CCR_PL2IDIV_SHIFT)  /* 1/1 (Value after reset) */
#  define R_SYSC_PLL2CCR_PL2IDIV_01                       (1 << R_SYSC_PLL2CCR_PL2IDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_PLL2CCR_PL2IDIV_10                       (2 << R_SYSC_PLL2CCR_PL2IDIV_SHIFT)  /* 1/3 */

#define R_SYSC_PLL2CCR_PL2SRCSEL                  (1 << 4)  /* PLL2 Clock Source Select */

#define R_SYSC_PLL2CCR_PLL2MULNF_SHIFT            (6)  /* PLL2 Frequency Multiplication Fractional Factor Select */
#define R_SYSC_PLL2CCR_PLL2MULNF_MASK             0xc0
#  define R_SYSC_PLL2CCR_PLL2MULNF_00                     (0 << R_SYSC_PLL2CCR_PLL2MULNF_SHIFT)  /* 0.00 (Value after reset) */
#  define R_SYSC_PLL2CCR_PLL2MULNF_01                     (1 << R_SYSC_PLL2CCR_PLL2MULNF_SHIFT)  /* 0.33 (1/3) */
#  define R_SYSC_PLL2CCR_PLL2MULNF_10                     (2 << R_SYSC_PLL2CCR_PLL2MULNF_SHIFT)  /* 0.66 (2/3) */
#  define R_SYSC_PLL2CCR_PLL2MULNF_11                     (3 << R_SYSC_PLL2CCR_PLL2MULNF_SHIFT)  /* 0.50 (1/2) */

#define R_SYSC_PLL2CCR_PLL2MUL_SHIFT              (8)  /* PLL2 Frequency Multiplication Factor Select */
#define R_SYSC_PLL2CCR_PLL2MUL_MASK               0x1ff00

/* SYRACCR Register bit definitions */
#define R_SYSC_SYRACCR_BUSY                       (1 << 0)  /* Access Ready monitor */

/* BCKADIVCR Register bit definitions */
#define R_SYSC_BCKADIVCR_BCKACKDIV_SHIFT          (0)  /* Asynchronous External Bus Clock (BCLKA) Division Select */
#define R_SYSC_BCKADIVCR_BCKACKDIV_MASK           0xf
#  define R_SYSC_BCKADIVCR_BCKACKDIV_0000                 (0 << R_SYSC_BCKADIVCR_BCKACKDIV_SHIFT)  /* 1/1 (value after reset) */
#  define R_SYSC_BCKADIVCR_BCKACKDIV_0001                 (1 << R_SYSC_BCKADIVCR_BCKACKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_BCKADIVCR_BCKACKDIV_0010                 (2 << R_SYSC_BCKADIVCR_BCKACKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_BCKADIVCR_BCKACKDIV_0011                 (3 << R_SYSC_BCKADIVCR_BCKACKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_BCKADIVCR_BCKACKDIV_0100                 (4 << R_SYSC_BCKADIVCR_BCKACKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_BCKADIVCR_BCKACKDIV_0111                 (7 << R_SYSC_BCKADIVCR_BCKACKDIV_SHIFT)  /* 1/10 */
#  define R_SYSC_BCKADIVCR_BCKACKDIV_1000                 (8 << R_SYSC_BCKADIVCR_BCKACKDIV_SHIFT)  /* 1/16 */
#  define R_SYSC_BCKADIVCR_BCKACKDIV_1001                 (9 << R_SYSC_BCKADIVCR_BCKACKDIV_SHIFT)  /* 1/32 */

#define R_SYSC_BCKADIVCR_CKDIV_SHIFT              (0)  /* Clock Division Select */
#define R_SYSC_BCKADIVCR_CKDIV_MASK               0xf

/* ESWCKDIVCR Register bit definitions */
#define R_SYSC_ESWCKDIVCR_ESWCKDIV_SHIFT          (0)  /* EtherSW Clock (ESWCLK) Division Select */
#define R_SYSC_ESWCKDIVCR_ESWCKDIV_MASK           0xf
#  define R_SYSC_ESWCKDIVCR_ESWCKDIV_0000                 (0 << R_SYSC_ESWCKDIVCR_ESWCKDIV_SHIFT)  /* 1/1 (value after reset) */
#  define R_SYSC_ESWCKDIVCR_ESWCKDIV_0001                 (1 << R_SYSC_ESWCKDIVCR_ESWCKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_ESWCKDIVCR_ESWCKDIV_0010                 (2 << R_SYSC_ESWCKDIVCR_ESWCKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_ESWCKDIVCR_ESWCKDIV_0011                 (3 << R_SYSC_ESWCKDIVCR_ESWCKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_ESWCKDIVCR_ESWCKDIV_0100                 (4 << R_SYSC_ESWCKDIVCR_ESWCKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_ESWCKDIVCR_ESWCKDIV_0111                 (7 << R_SYSC_ESWCKDIVCR_ESWCKDIV_SHIFT)  /* 1/10 */
#  define R_SYSC_ESWCKDIVCR_ESWCKDIV_1000                 (8 << R_SYSC_ESWCKDIVCR_ESWCKDIV_SHIFT)  /* 1/16 */
#  define R_SYSC_ESWCKDIVCR_ESWCKDIV_1001                 (9 << R_SYSC_ESWCKDIVCR_ESWCKDIV_SHIFT)  /* 1/32 */

#define R_SYSC_ESWCKDIVCR_CKDIV_SHIFT             (0)  /* Clock Division Select */
#define R_SYSC_ESWCKDIVCR_CKDIV_MASK              0xf

/* ESWPCKDIVCR Register bit definitions */
#define R_SYSC_ESWPCKDIVCR_ESWPCKDIV_SHIFT        (0)  /* EtherSW-PHY Clock (ESWPHYCLK) Division Select */
#define R_SYSC_ESWPCKDIVCR_ESWPCKDIV_MASK         0xf
#  define R_SYSC_ESWPCKDIVCR_ESWPCKDIV_0000               (0 << R_SYSC_ESWPCKDIVCR_ESWPCKDIV_SHIFT)  /* 1/1 (value after reset) */
#  define R_SYSC_ESWPCKDIVCR_ESWPCKDIV_0001               (1 << R_SYSC_ESWPCKDIVCR_ESWPCKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_ESWPCKDIVCR_ESWPCKDIV_0010               (2 << R_SYSC_ESWPCKDIVCR_ESWPCKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_ESWPCKDIVCR_ESWPCKDIV_0011               (3 << R_SYSC_ESWPCKDIVCR_ESWPCKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_ESWPCKDIVCR_ESWPCKDIV_0100               (4 << R_SYSC_ESWPCKDIVCR_ESWPCKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_ESWPCKDIVCR_ESWPCKDIV_0111               (7 << R_SYSC_ESWPCKDIVCR_ESWPCKDIV_SHIFT)  /* 1/10 */
#  define R_SYSC_ESWPCKDIVCR_ESWPCKDIV_1000               (8 << R_SYSC_ESWPCKDIVCR_ESWPCKDIV_SHIFT)  /* 1/16 */
#  define R_SYSC_ESWPCKDIVCR_ESWPCKDIV_1001               (9 << R_SYSC_ESWPCKDIVCR_ESWPCKDIV_SHIFT)  /* 1/32 */

#define R_SYSC_ESWPCKDIVCR_CKDIV_SHIFT            (0)  /* Clock Division Select */
#define R_SYSC_ESWPCKDIVCR_CKDIV_MASK             0xf

/* ETHPCKDIVCR Register bit definitions */
#define R_SYSC_ETHPCKDIVCR_ETHPCKDIV_SHIFT        (0)  /* Ether-PHY Clock (ETHPHYCLK) Division Select */
#define R_SYSC_ETHPCKDIVCR_ETHPCKDIV_MASK         0xf
#  define R_SYSC_ETHPCKDIVCR_ETHPCKDIV_0000               (0 << R_SYSC_ETHPCKDIVCR_ETHPCKDIV_SHIFT)  /* 1/1 (value after reset) */
#  define R_SYSC_ETHPCKDIVCR_ETHPCKDIV_0001               (1 << R_SYSC_ETHPCKDIVCR_ETHPCKDIV_SHIFT)  /* 1/2 */
#  define R_SYSC_ETHPCKDIVCR_ETHPCKDIV_0010               (2 << R_SYSC_ETHPCKDIVCR_ETHPCKDIV_SHIFT)  /* 1/4 */
#  define R_SYSC_ETHPCKDIVCR_ETHPCKDIV_0011               (3 << R_SYSC_ETHPCKDIVCR_ETHPCKDIV_SHIFT)  /* 1/6 */
#  define R_SYSC_ETHPCKDIVCR_ETHPCKDIV_0100               (4 << R_SYSC_ETHPCKDIVCR_ETHPCKDIV_SHIFT)  /* 1/8 */
#  define R_SYSC_ETHPCKDIVCR_ETHPCKDIV_0111               (7 << R_SYSC_ETHPCKDIVCR_ETHPCKDIV_SHIFT)  /* 1/10 */
#  define R_SYSC_ETHPCKDIVCR_ETHPCKDIV_1000               (8 << R_SYSC_ETHPCKDIVCR_ETHPCKDIV_SHIFT)  /* 1/16 */
#  define R_SYSC_ETHPCKDIVCR_ETHPCKDIV_1001               (9 << R_SYSC_ETHPCKDIVCR_ETHPCKDIV_SHIFT)  /* 1/32 */

#define R_SYSC_ETHPCKDIVCR_CKDIV_SHIFT            (0)  /* Clock Division Select */
#define R_SYSC_ETHPCKDIVCR_CKDIV_MASK             0xf

/* BCKACR Register bit definitions */
#define R_SYSC_BCKACR_BCKACKSEL_SHIFT             (0)  /* Asynchronous External Bus Clock (BCLKA) */
#define R_SYSC_BCKACR_BCKACKSEL_MASK              0xf
#  define R_SYSC_BCKACR_BCKACKSEL_0001                    (1 << R_SYSC_BCKACR_BCKACKSEL_SHIFT)  /* MOCO (value after reset) */
#  define R_SYSC_BCKACR_BCKACKSEL_0101                    (5 << R_SYSC_BCKACR_BCKACKSEL_SHIFT)  /* PLL1P */
#  define R_SYSC_BCKACR_BCKACKSEL_0110                    (6 << R_SYSC_BCKACR_BCKACKSEL_SHIFT)  /* PLL2P */
#  define R_SYSC_BCKACR_BCKACKSEL_0111                    (7 << R_SYSC_BCKACR_BCKACKSEL_SHIFT)  /* PLL1Q */
#  define R_SYSC_BCKACR_BCKACKSEL_1000                    (8 << R_SYSC_BCKACR_BCKACKSEL_SHIFT)  /* PLL1R */
#  define R_SYSC_BCKACR_BCKACKSEL_1001                    (9 << R_SYSC_BCKACR_BCKACKSEL_SHIFT)  /* PLL2Q */
#  define R_SYSC_BCKACR_BCKACKSEL_1010                    (10 << R_SYSC_BCKACR_BCKACKSEL_SHIFT)  /* PLL2R */

#define R_SYSC_BCKACR_BCKACKSREQ                  (1 << 6)  /* Asynchronous External Bus Clock (BCLKA) Switching Request */

#define R_SYSC_BCKACR_BCKACKSRDY                  (1 << 7)  /* Asynchronous External Bus Clock (BCLKA) Switching Ready State Flag */

#define R_SYSC_BCKACR_CKSEL_SHIFT                 (0)  /* Clock Source Select */
#define R_SYSC_BCKACR_CKSEL_MASK                  0xf

#define R_SYSC_BCKACR_CKSREQ                      (1 << 6)  /* Clock Switching Request */

#define R_SYSC_BCKACR_CKSRDY                      (1 << 7)  /* Clock Switching Ready state flag */

/* ESWCKCR Register bit definitions */
#define R_SYSC_ESWCKCR_ESWCKSEL_SHIFT             (0)  /* EtherSW Clock (ESWCLK) Source Select */
#define R_SYSC_ESWCKCR_ESWCKSEL_MASK              0xf
#  define R_SYSC_ESWCKCR_ESWCKSEL_0001                    (1 << R_SYSC_ESWCKCR_ESWCKSEL_SHIFT)  /* MOCO (value after reset) */
#  define R_SYSC_ESWCKCR_ESWCKSEL_0101                    (5 << R_SYSC_ESWCKCR_ESWCKSEL_SHIFT)  /* PLL1P */
#  define R_SYSC_ESWCKCR_ESWCKSEL_0110                    (6 << R_SYSC_ESWCKCR_ESWCKSEL_SHIFT)  /* PLL2P */
#  define R_SYSC_ESWCKCR_ESWCKSEL_0111                    (7 << R_SYSC_ESWCKCR_ESWCKSEL_SHIFT)  /* PLL1Q */
#  define R_SYSC_ESWCKCR_ESWCKSEL_1000                    (8 << R_SYSC_ESWCKCR_ESWCKSEL_SHIFT)  /* PLL1R */
#  define R_SYSC_ESWCKCR_ESWCKSEL_1001                    (9 << R_SYSC_ESWCKCR_ESWCKSEL_SHIFT)  /* PLL2Q */
#  define R_SYSC_ESWCKCR_ESWCKSEL_1010                    (10 << R_SYSC_ESWCKCR_ESWCKSEL_SHIFT)  /* PLL2R */

#define R_SYSC_ESWCKCR_ESWCKSREQ                  (1 << 6)  /* EtherSW Clock (ESWCLK) Switching Request */

#define R_SYSC_ESWCKCR_ESWCKSRDY                  (1 << 7)  /* EtherSW Clock (ESWCLK) Switching Ready State Flag */

#define R_SYSC_ESWCKCR_CKSEL_SHIFT                (0)  /* Clock Source Select */
#define R_SYSC_ESWCKCR_CKSEL_MASK                 0xf

#define R_SYSC_ESWCKCR_CKSREQ                     (1 << 6)  /* Clock Switching Request */

#define R_SYSC_ESWCKCR_CKSRDY                     (1 << 7)  /* Clock Switching Ready state flag */

/* ESWPCKCR Register bit definitions */
#define R_SYSC_ESWPCKCR_ESWPCKSEL_SHIFT           (0)  /* EtherSW-PHY Clock (ESWPHYCLK) Source Select */
#define R_SYSC_ESWPCKCR_ESWPCKSEL_MASK            0xf
#  define R_SYSC_ESWPCKCR_ESWPCKSEL_0001                  (1 << R_SYSC_ESWPCKCR_ESWPCKSEL_SHIFT)  /* MOCO (value after reset) */
#  define R_SYSC_ESWPCKCR_ESWPCKSEL_0101                  (5 << R_SYSC_ESWPCKCR_ESWPCKSEL_SHIFT)  /* PLL1P */
#  define R_SYSC_ESWPCKCR_ESWPCKSEL_0110                  (6 << R_SYSC_ESWPCKCR_ESWPCKSEL_SHIFT)  /* PLL2P */
#  define R_SYSC_ESWPCKCR_ESWPCKSEL_0111                  (7 << R_SYSC_ESWPCKCR_ESWPCKSEL_SHIFT)  /* PLL1Q */
#  define R_SYSC_ESWPCKCR_ESWPCKSEL_1000                  (8 << R_SYSC_ESWPCKCR_ESWPCKSEL_SHIFT)  /* PLL1R */
#  define R_SYSC_ESWPCKCR_ESWPCKSEL_1001                  (9 << R_SYSC_ESWPCKCR_ESWPCKSEL_SHIFT)  /* PLL2Q */
#  define R_SYSC_ESWPCKCR_ESWPCKSEL_1010                  (10 << R_SYSC_ESWPCKCR_ESWPCKSEL_SHIFT)  /* PLL2R */

#define R_SYSC_ESWPCKCR_ESWPCKSREQ                (1 << 6)  /* EtherSW-PHY Clock (ESWPHYCLK) Switching Request */

#define R_SYSC_ESWPCKCR_ESWPCKSRDY                (1 << 7)  /* EtherSW-PHY Clock (ESWPHYCLK) Switching Ready State Flag */

#define R_SYSC_ESWPCKCR_CKSEL_SHIFT               (0)  /* Clock Source Select */
#define R_SYSC_ESWPCKCR_CKSEL_MASK                0xf

#define R_SYSC_ESWPCKCR_CKSREQ                    (1 << 6)  /* Clock Switching Request */

#define R_SYSC_ESWPCKCR_CKSRDY                    (1 << 7)  /* Clock Switching Ready state flag */

/* ETHPCKCR Register bit definitions */
#define R_SYSC_ETHPCKCR_ETHPCKSEL_SHIFT           (0)  /* Ether-PHY Clock (ETHPHYCLK) Source Select */
#define R_SYSC_ETHPCKCR_ETHPCKSEL_MASK            0xf
#  define R_SYSC_ETHPCKCR_ETHPCKSEL_0001                  (1 << R_SYSC_ETHPCKCR_ETHPCKSEL_SHIFT)  /* MOCO (value after reset) */
#  define R_SYSC_ETHPCKCR_ETHPCKSEL_0011                  (3 << R_SYSC_ETHPCKCR_ETHPCKSEL_SHIFT)  /* Main clock oscillator */
#  define R_SYSC_ETHPCKCR_ETHPCKSEL_0101                  (5 << R_SYSC_ETHPCKCR_ETHPCKSEL_SHIFT)  /* PLL1P */
#  define R_SYSC_ETHPCKCR_ETHPCKSEL_0110                  (6 << R_SYSC_ETHPCKCR_ETHPCKSEL_SHIFT)  /* PLL2P */
#  define R_SYSC_ETHPCKCR_ETHPCKSEL_0111                  (7 << R_SYSC_ETHPCKCR_ETHPCKSEL_SHIFT)  /* PLL1Q */
#  define R_SYSC_ETHPCKCR_ETHPCKSEL_1000                  (8 << R_SYSC_ETHPCKCR_ETHPCKSEL_SHIFT)  /* PLL1R */
#  define R_SYSC_ETHPCKCR_ETHPCKSEL_1001                  (9 << R_SYSC_ETHPCKCR_ETHPCKSEL_SHIFT)  /* PLL2Q */
#  define R_SYSC_ETHPCKCR_ETHPCKSEL_1010                  (10 << R_SYSC_ETHPCKCR_ETHPCKSEL_SHIFT)  /* PLL2R */

#define R_SYSC_ETHPCKCR_ETHPCKSREQ                (1 << 6)  /* Ether-PHY Clock (ETHPHYCLK) Switching Request */

#define R_SYSC_ETHPCKCR_ETHPCKSRDY                (1 << 7)  /* Ether-PHY Clock (ETHPHYCLK) Switching Ready State Flag */

#define R_SYSC_ETHPCKCR_CKSEL_SHIFT               (0)  /* Clock Source Select */
#define R_SYSC_ETHPCKCR_CKSEL_MASK                0xf

#define R_SYSC_ETHPCKCR_CKSREQ                    (1 << 6)  /* Clock Switching Request */

#define R_SYSC_ETHPCKCR_CKSRDY                    (1 << 7)  /* Clock Switching Ready state flag */

/* PVDCR Register bit definitions */
#define R_SYSC_PVDCR_IDTSEL_SHIFT                 (0)  /* Voltage Monitor m Interrupt Generation Condition Select */
#define R_SYSC_PVDCR_IDTSEL_MASK                  0x3

#define R_SYSC_PVDCR_IRQSEL                       (1 << 2)  /* Voltage Monitor m Interrupt Type Select */

/* PVDSR Register bit definitions */
#define R_SYSC_PVDSR_DET                          (1 << 0)  /* Voltage Monitor m Voltage Change Detection Flag */

#define R_SYSC_PVDSR_MON                          (1 << 1)  /* Voltage Monitor 1 Signal Monitor Flag */

/* CPUDSCR Register bit definitions */
#define R_SYSC_CPUDSCR_PGD0                       (1 << 0)  /* Power Gating Disable for CPU0 */

#define R_SYSC_CPUDSCR_PGD1                       (1 << 1)  /* Power Gating Disable for CPU1 */

/* PGSCR Register bit definitions */
#define R_SYSC_PGSCR_PGS                          (1 << 0)  /* Power gating shift timing */

/* PDCTRGD Register bit definitions */
#define R_SYSC_PDCTRGD_PDDE                       (1 << 0)  /* Power control enable */

#define R_SYSC_PDCTRGD_PDCSF                      (1 << 6)  /* Power control status flag */

#define R_SYSC_PDCTRGD_PDPGSF                     (1 << 7)  /* Power gating status flag */

/* PDCTRNPU Register bit definitions */
#define R_SYSC_PDCTRNPU_PDDE                      (1 << 0)  /* Power control enable */

#define R_SYSC_PDCTRNPU_PDCSF                     (1 << 6)  /* Power control status flag */

#define R_SYSC_PDCTRNPU_PDPGSF                    (1 << 7)  /* Power gating status flag */

/* PDCTRESWM Register bit definitions */
#define R_SYSC_PDCTRESWM_PDDE                     (1 << 0)  /* Power control enable */

#define R_SYSC_PDCTRESWM_PDCSF                    (1 << 6)  /* Power control status flag */

#define R_SYSC_PDCTRESWM_PDPGSF                   (1 << 7)  /* Power gating status flag */

/* PDRAMSCR0 Register bit definitions */
#define R_SYSC_PDRAMSCR0_RKEEP_SHIFT              (0)  /* RAM Retention */
#define R_SYSC_PDRAMSCR0_RKEEP_MASK               0x1fff
#  define R_SYSC_PDRAMSCR0_RKEEP_0                        (0 << R_SYSC_PDRAMSCR0_RKEEP_SHIFT)  /* When entering the Software Standby mode, the contents of the target RAM are not kept. */
#  define R_SYSC_PDRAMSCR0_RKEEP_1                        (1 << R_SYSC_PDRAMSCR0_RKEEP_SHIFT)  /* When entering the Software Standby mode, the contents of the target RAM are kept. */

#define R_SYSC_PDRAMSCR0_RKEEP0                   (1 << 0)  /* RAM Retention bit 0 */

#define R_SYSC_PDRAMSCR0_RKEEP1                   (1 << 1)  /* RAM Retention bit 1 */

#define R_SYSC_PDRAMSCR0_RKEEP2                   (1 << 2)  /* RAM Retention bit 2 */

#define R_SYSC_PDRAMSCR0_RKEEP3                   (1 << 3)  /* RAM Retention bit 3 */

#define R_SYSC_PDRAMSCR0_RKEEP4                   (1 << 4)  /* RAM Retention bit 4 */

#define R_SYSC_PDRAMSCR0_RKEEP5                   (1 << 5)  /* RAM Retention bit 5 */

#define R_SYSC_PDRAMSCR0_RKEEP6                   (1 << 6)  /* RAM Retention bit 6 */

#define R_SYSC_PDRAMSCR0_RKEEP7                   (1 << 7)  /* RAM Retention bit 7 */

#define R_SYSC_PDRAMSCR0_RKEEP8                   (1 << 8)  /* RAM Retention bit 8 */

#define R_SYSC_PDRAMSCR0_RKEEP9                   (1 << 9)  /* RAM Retention bit 9 */

#define R_SYSC_PDRAMSCR0_RKEEP10                  (1 << 10)  /* RAM Retention bit 10 */

#define R_SYSC_PDRAMSCR0_RKEEP11                  (1 << 11)  /* RAM Retention bit 11 */

#define R_SYSC_PDRAMSCR0_RKEEP12                  (1 << 12)  /* RAM Retention bit 12 */

#define R_SYSC_PDRAMSCR0_RKEEP13                  (1 << 13)  /* RAM Retention bit 13 */

#define R_SYSC_PDRAMSCR0_RKEEP14                  (1 << 14)  /* RAM Retention bit 14 */

#define R_SYSC_PDRAMSCR0_RKEEP15                  (1 << 15)  /* RAM Retention bit 15 */

/* PDRAMSCR1 Register bit definitions */
#define R_SYSC_PDRAMSCR1_RKEEP0                   (1 << 0)  /* RAM Retention */

#define R_SYSC_PDRAMSCR1_RKEEP1                   (1 << 1)  /* RAM Retention */

#define R_SYSC_PDRAMSCR1_RKEEP2                   (1 << 2)  /* RAM Retention bit 2 */

#define R_SYSC_PDRAMSCR1_RKEEP3                   (1 << 3)  /* RAM Retention bit 3 */

#define R_SYSC_PDRAMSCR1_RKEEP4                   (1 << 4)  /* RAM Retention bit 4 */

#define R_SYSC_PDRAMSCR1_RKEEP5                   (1 << 5)  /* RAM Retention bit 5 */

#define R_SYSC_PDRAMSCR1_RKEEP6                   (1 << 6)  /* RAM Retention bit 6 */

#define R_SYSC_PDRAMSCR1_RKEEP7                   (1 << 7)  /* RAM Retention bit 7 */

/* PSSTCR Register bit definitions */
#define R_SYSC_PSSTCR_PSST_SHIFT                  (0)  /* Power switch control start time */
#define R_SYSC_PSSTCR_PSST_MASK                   0x1fff

/* PSSTCR Register bit definitions */
#define R_SYSC_PSSTCR_PSST_SHIFT                  (0)  /* Power switch control start time */
#define R_SYSC_PSSTCR_PSST_MASK                   0x1fff

/* VBRSABAR Register bit definitions */
#define R_SYSC_VBRSABAR_SABA_SHIFT                (0)  /* Boundary address between secure and non-secure */
#define R_SYSC_VBRSABAR_SABA_MASK                 0xffff

/* VBRPABARS Register bit definitions */
#define R_SYSC_VBRPABARS_PABAS_SHIFT              (0)  /* Privilege Attribute Boundary Address for Secure Region */
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

#define R_SYSC_CGFSAR_NONSEC10                    (1 << 10)  /* Non Secure Attribute bit 10 */

#define R_SYSC_CGFSAR_NONSEC11                    (1 << 11)  /* Non Secure Attribute bit 11 */

#define R_SYSC_CGFSAR_NONSEC12                    (1 << 12)  /* Non Secure Attribute bit 12 */

#define R_SYSC_CGFSAR_NONSEC13                    (1 << 13)  /* Non Secure Attribute bit 13 */

#define R_SYSC_CGFSAR_NONSEC14                    (1 << 14)  /* Non Secure Attribute bit 14 */

#define R_SYSC_CGFSAR_NONSEC16                    (1 << 16)  /* Non Secure Attribute bit 16 */

#define R_SYSC_CGFSAR_NONSEC17                    (1 << 17)  /* Non Secure Attribute bit 17 */

#define R_SYSC_CGFSAR_NONSEC18                    (1 << 18)  /* Non Secure Attribute bit 18 */

#define R_SYSC_CGFSAR_NONSEC19                    (1 << 19)  /* Non Secure Attribute bit 19 */

#define R_SYSC_CGFSAR_NONSEC20                    (1 << 20)  /* Non Secure Attribute bit 20 */

#define R_SYSC_CGFSAR_NONSEC21                    (1 << 21)  /* Non Secure Attribute bit 21 */

#define R_SYSC_CGFSAR_NONSEC22                    (1 << 22)  /* Non Secure Attribute bit 22 */

#define R_SYSC_CGFSAR_NONSEC24                    (1 << 24)  /* Non Secure Attribute bit 24 */

#define R_SYSC_CGFSAR_NONSEC25                    (1 << 25)  /* Non Secure Attribute bit 25 */

#define R_SYSC_CGFSAR_NONSEC26                    (1 << 26)  /* Non Secure Attribute bit 26 */

#define R_SYSC_CGFSAR_NONSEC27                    (1 << 27)  /* Non Secure Attribute bit 27 */

#define R_SYSC_CGFSAR_NONSEC28                    (1 << 28)  /* Non Secure Attribute bit 28 */

#define R_SYSC_CGFSAR_NONSEC01                    (1 << 1)  /* Non Secure Attribute bit 1 */

#define R_SYSC_CGFSAR_NONSEC15                    (1 << 15)  /* Non Secure Attribute bit 15 */

#define R_SYSC_CGFSAR_NONSEC23                    (1 << 23)  /* Non Secure Attribute bit 23 */

#define R_SYSC_CGFSAR_NONSEC29                    (1 << 29)  /* Non Secure Attribute bit 29 */

#define R_SYSC_CGFSAR_NONSEC30                    (1 << 30)  /* Non Secure Attribute bit 30 */

#define R_SYSC_CGFSAR_NONSEC31                    (1 << 31)  /* Non Secure Attribute bit 31 */

/* RSTSAR Register bit definitions */
#define R_SYSC_RSTSAR_NONSEC0                     (1 << 0)  /* Non-secure Attribute bit 0 */

#define R_SYSC_RSTSAR_NONSEC1                     (1 << 1)  /* Non-secure Attribute bit 1 */

#define R_SYSC_RSTSAR_NONSEC2                     (1 << 2)  /* Non-secure Attribute bit 2 */

#define R_SYSC_RSTSAR_NONSEC3                     (1 << 3)  /* Non-secure Attribute bit 3 */

#define R_SYSC_RSTSAR_NONSEC4                     (1 << 4)  /* Non Secure Attribute bit 4 */

/* LPMSAR Register bit definitions */
#define R_SYSC_LPMSAR_NONSEC0                     (1 << 0)  /* Non-secure Attribute bit 0 */

#define R_SYSC_LPMSAR_NONSEC1                     (1 << 1)  /* Non-secure Attribute bit 1 */

#define R_SYSC_LPMSAR_NONSEC2                     (1 << 2)  /* Non-secure Attribute bit 2 */

#define R_SYSC_LPMSAR_NONSEC4                     (1 << 4)  /* Non-secure Attribute bit 4 */

#define R_SYSC_LPMSAR_NONSEC8                     (1 << 8)  /* Non-secure Attribute bit 8 */

#define R_SYSC_LPMSAR_NONSEC17                    (1 << 17)  /* Non-secure Attribute bit 17 */

#define R_SYSC_LPMSAR_NONSEC18                    (1 << 18)  /* Non-secure Attribute bit 18 */

#define R_SYSC_LPMSAR_NONSEC19                    (1 << 19)  /* Non-secure Attribute bit 19 */

#define R_SYSC_LPMSAR_NONSEC21                    (1 << 21)  /* Non-secure Attribute bit 21 */

#define R_SYSC_LPMSAR_NONSEC3                     (1 << 3)  /* Non Secure Attribute bit 3 */

#define R_SYSC_LPMSAR_NONSEC5                     (1 << 5)  /* Non Secure Attribute bit 5 */

#define R_SYSC_LPMSAR_NONSEC6                     (1 << 6)  /* Non Secure Attribute bit 6 */

#define R_SYSC_LPMSAR_NONSEC7                     (1 << 7)  /* Non Secure Attribute bit 7 */

#define R_SYSC_LPMSAR_NONSEC9                     (1 << 9)  /* Non Secure Attribute bit 9 */

#define R_SYSC_LPMSAR_NONSEC10                    (1 << 10)  /* Non Secure Attribute bit 10 */

#define R_SYSC_LPMSAR_NONSEC11                    (1 << 11)  /* Non Secure Attribute bit 11 */

#define R_SYSC_LPMSAR_NONSEC12                    (1 << 12)  /* Non Secure Attribute bit 12 */

#define R_SYSC_LPMSAR_NONSEC13                    (1 << 13)  /* Non Secure Attribute bit 13 */

#define R_SYSC_LPMSAR_NONSEC14                    (1 << 14)  /* Non Secure Attribute bit 14 */

#define R_SYSC_LPMSAR_NONSEC15                    (1 << 15)  /* Non Secure Attribute bit 15 */

#define R_SYSC_LPMSAR_NONSEC16                    (1 << 16)  /* Non Secure Attribute bit 16 */

#define R_SYSC_LPMSAR_NONSEC20                    (1 << 20)  /* Non Secure Attribute bit 20 */

#define R_SYSC_LPMSAR_NONSEC22                    (1 << 22)  /* Non Secure Attribute bit 22 */

#define R_SYSC_LPMSAR_NONSEC23                    (1 << 23)  /* Non Secure Attribute bit 23 */

#define R_SYSC_LPMSAR_NONSEC24                    (1 << 24)  /* Non Secure Attribute bit 24 */

#define R_SYSC_LPMSAR_NONSEC25                    (1 << 25)  /* Non Secure Attribute bit 25 */

#define R_SYSC_LPMSAR_NONSEC26                    (1 << 26)  /* Non Secure Attribute bit 26 */

#define R_SYSC_LPMSAR_NONSEC27                    (1 << 27)  /* Non Secure Attribute bit 27 */

#define R_SYSC_LPMSAR_NONSEC28                    (1 << 28)  /* Non Secure Attribute bit 28 */

#define R_SYSC_LPMSAR_NONSEC29                    (1 << 29)  /* Non Secure Attribute bit 29 */

#define R_SYSC_LPMSAR_NONSEC30                    (1 << 30)  /* Non Secure Attribute bit 30 */

#define R_SYSC_LPMSAR_NONSEC31                    (1 << 31)  /* Non Secure Attribute bit 31 */

/* PVDSAR Register bit definitions */
#define R_SYSC_PVDSAR_NONSEC0                     (1 << 0)  /* Non Secure Attribute bit 0 */

#define R_SYSC_PVDSAR_NONSEC1                     (1 << 1)  /* Non Secure Attribute bit 1 */

/* BBFSAR Register bit definitions */
#define R_SYSC_BBFSAR_NONSEC0                     (1 << 0)  /* Non Secure Attribute bit 0 */

#define R_SYSC_BBFSAR_NONSEC1                     (1 << 1)  /* Non Secure Attribute bit 1 */

#define R_SYSC_BBFSAR_NONSEC2                     (1 << 2)  /* Non Secure Attribute bit 2 */

#define R_SYSC_BBFSAR_NONSEC3                     (1 << 3)  /* Non Secure Attribute bit 3 */

#define R_SYSC_BBFSAR_NONSEC4                     (1 << 4)  /* Non Secure Attribute bit 4 */

#define R_SYSC_BBFSAR_NONSEC5                     (1 << 5)  /* Non Secure Attribute bit 5 */

#define R_SYSC_BBFSAR_NONSEC6                     (1 << 6)  /* Non Secure Attribute bit 6 */

#define R_SYSC_BBFSAR_NONSEC7                     (1 << 7)  /* Non-secure Attribute bit 7 */

#define R_SYSC_BBFSAR_NONSEC8                     (1 << 8)  /* Non-secure Attribute bit 8 */

/* PGCSAR Register bit definitions */
#define R_SYSC_PGCSAR_NONSEC0                     (1 << 0)  /* Non-secure Attribute bit 0 */

#define R_SYSC_PGCSAR_NONSEC1                     (1 << 1)  /* Non-secure Attribute bit 1 */

#define R_SYSC_PGCSAR_NONSEC2                     (1 << 2)  /* Non-secure Attribute bit 2 */

#define R_SYSC_PGCSAR_NONSEC3                     (1 << 3)  /* Non-secure Attribute bit 3 */

#define R_SYSC_PGCSAR_NONSEC4                     (1 << 4)  /* Non-secure Attribute bit 4 */

#define R_SYSC_PGCSAR_NONSEC5                     (1 << 5)  /* Non-secure Attribute bit 5 */

#define R_SYSC_PGCSAR_NONSEC6                     (1 << 6)  /* Non-secure Attribute bit 6 */

#define R_SYSC_PGCSAR_NONSEC7                     (1 << 7)  /* Non-secure Attribute bit 7 */

#define R_SYSC_PGCSAR_NONSEC8                     (1 << 8)  /* Non-secure Attribute bit 8 */

#define R_SYSC_PGCSAR_NONSEC9                     (1 << 9)  /* Non-secure Attribute bit 9 */

#define R_SYSC_PGCSAR_NONSEC10                    (1 << 10)  /* Non-secure Attribute bit 10 */

#define R_SYSC_PGCSAR_NONSEC11                    (1 << 11)  /* Non-secure Attribute bit 11 */

#define R_SYSC_PGCSAR_NONSEC12                    (1 << 12)  /* Non-secure Attribute bit 12 */

#define R_SYSC_PGCSAR_NONSEC13                    (1 << 13)  /* Non-secure Attribute bit 13 */

#define R_SYSC_PGCSAR_NONSEC14                    (1 << 14)  /* Non-secure Attribute bit 14 */

#define R_SYSC_PGCSAR_NONSEC15                    (1 << 15)  /* Non-secure Attribute bit 15 */

#define R_SYSC_PGCSAR_NONSEC16                    (1 << 16)  /* Non-secure Attribute bit 16 */

#define R_SYSC_PGCSAR_NONSEC17                    (1 << 17)  /* Non-secure Attribute bit 17 */

#define R_SYSC_PGCSAR_NONSEC18                    (1 << 18)  /* Non-secure Attribute bit 18 */

#define R_SYSC_PGCSAR_NONSEC19                    (1 << 19)  /* Non-secure Attribute bit 19 */

#define R_SYSC_PGCSAR_NONSEC20                    (1 << 20)  /* Non-secure Attribute bit 20 */

#define R_SYSC_PGCSAR_NONSEC21                    (1 << 21)  /* Non-secure Attribute bit 21 */

#define R_SYSC_PGCSAR_NONSEC22                    (1 << 22)  /* Non-secure Attribute bit 22 */

#define R_SYSC_PGCSAR_NONSEC23                    (1 << 23)  /* Non-secure Attribute bit 23 */

#define R_SYSC_PGCSAR_NONSEC24                    (1 << 24)  /* Non-secure Attribute bit 24 */

#define R_SYSC_PGCSAR_NONSEC25                    (1 << 25)  /* Non-secure Attribute bit 25 */

#define R_SYSC_PGCSAR_NONSEC26                    (1 << 26)  /* Non-secure Attribute bit 26 */

#define R_SYSC_PGCSAR_NONSEC27                    (1 << 27)  /* Non-secure Attribute bit 27 */

#define R_SYSC_PGCSAR_NONSEC28                    (1 << 28)  /* Non-secure Attribute bit 28 */

#define R_SYSC_PGCSAR_NONSEC29                    (1 << 29)  /* Non-secure Attribute bit 29 */

#define R_SYSC_PGCSAR_NONSEC30                    (1 << 30)  /* Non-secure Attribute bit 30 */

#define R_SYSC_PGCSAR_NONSEC31                    (1 << 31)  /* Non-secure Attribute bit 31 */

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

#define R_SYSC_DPFSAR_DPFSA25                     (1 << 25)  /* Deep Software Standby Interrupt Factor Security Attribute bit 25 */

#define R_SYSC_DPFSAR_DPFSA26                     (1 << 26)  /* Deep Software Standby Interrupt Factor Security Attribute bit 26 */

#define R_SYSC_DPFSAR_DPFSA27                     (1 << 27)  /* Deep Software Standby Interrupt Factor Security Attribute bit 27 */

#define R_SYSC_DPFSAR_DPFSA29                     (1 << 29)  /* Deep Software Standby Interrupt Factor Security Attribute bit 29 */

#define R_SYSC_DPFSAR_DPFSA30                     (1 << 30)  /* Deep Software Standby Interrupt Factor Security Attribute bit 30 */

#define R_SYSC_DPFSAR_DPFSA31                     (1 << 31)  /* Deep Software Standby Interrupt Factor Security Attribute bit 31 */

#define R_SYSC_DPFSAR_DPFSA8                      (1 << 8)  /* Deep Standby Interrupt Factor Security Attribute bit 8 */

#define R_SYSC_DPFSAR_DPFSA9                      (1 << 9)  /* Deep Standby Interrupt Factor Security Attribute bit 9 */

#define R_SYSC_DPFSAR_DPFSA21                     (1 << 21)  /* Deep Standby Interrupt Factor Security Attribute bit 21 */

#define R_SYSC_DPFSAR_DPFSA22                     (1 << 22)  /* Deep Standby Interrupt Factor Security Attribute bit 22 */

#define R_SYSC_DPFSAR_DPFSA23                     (1 << 23)  /* Deep Standby Interrupt Factor Security Attribute bit 23 */

#define R_SYSC_DPFSAR_DPFSA28                     (1 << 28)  /* Deep Standby Interrupt Factor Security Attribute bit 28 */

/* RSCSAR Register bit definitions */
#define R_SYSC_RSCSAR_RSCSA_SHIFT                 (0)  /* RAM Standby Control Security Attribute bit n (n = 0 to 17) */
#define R_SYSC_RSCSAR_RSCSA_MASK                  0x3ffff
#  define R_SYSC_RSCSAR_RSCSA_0                           (0 << R_SYSC_RSCSAR_RSCSA_SHIFT)  /* Secure */
#  define R_SYSC_RSCSAR_RSCSA_1                           (1 << R_SYSC_RSCSAR_RSCSA_SHIFT)  /* Non-secure */

#define R_SYSC_RSCSAR_RSCSA0                      (1 << 0)  /* RAM Standby Control Security Attribute bit 0 */

#define R_SYSC_RSCSAR_RSCSA1                      (1 << 1)  /* RAM Standby Control Security Attribute bit 1 */

#define R_SYSC_RSCSAR_RSCSA2                      (1 << 2)  /* RAM Standby Control Security Attribute bit 2 */

#define R_SYSC_RSCSAR_RSCSA3                      (1 << 3)  /* RAM Standby Control Security Attribute bit 3 */

#define R_SYSC_RSCSAR_RSCSA4                      (1 << 4)  /* RAM Standby Control Security Attribute bit 4 */

#define R_SYSC_RSCSAR_RSCSA5                      (1 << 5)  /* RAM Standby Control Security Attribute bit 5 */

#define R_SYSC_RSCSAR_RSCSA6                      (1 << 6)  /* RAM Standby Control Security Attribute bit 6 */

#define R_SYSC_RSCSAR_RSCSA7                      (1 << 7)  /* RAM Standby Control Security Attribute bit 7 */

#define R_SYSC_RSCSAR_RSCSA8                      (1 << 8)  /* RAM Standby Control Security Attribute bit 8 */

#define R_SYSC_RSCSAR_RSCSA9                      (1 << 9)  /* RAM Standby Control Security Attribute bit 9 */

#define R_SYSC_RSCSAR_RSCSA10                     (1 << 10)  /* RAM Standby Control Security Attribute bit 10 */

#define R_SYSC_RSCSAR_RSCSA11                     (1 << 11)  /* RAM Standby Control Security Attribute bit 11 */

#define R_SYSC_RSCSAR_RSCSA12                     (1 << 12)  /* RAM Standby Control Security Attribute bit 12 */

#define R_SYSC_RSCSAR_RSCSA13                     (1 << 13)  /* RAM Standby Control Security Attribute bit 13 */

#define R_SYSC_RSCSAR_RSCSA14                     (1 << 14)  /* RAM Standby Control Security Attribute bit 14 */

#define R_SYSC_RSCSAR_RSCSA15                     (1 << 15)  /* RAM Standby Control Security Attribute bit 15 */

#define R_SYSC_RSCSAR_RSCSA16                     (1 << 16)  /* RAM Standby Control Security Attribute bit 16 */

#define R_SYSC_RSCSAR_RSCSA17                     (1 << 17)  /* RAM Standby Control Security Attribute bit 17 */

#define R_SYSC_RSCSAR_RSCSA18                     (1 << 18)  /* RAM Standby Control Security Attribute bit 18 */

#define R_SYSC_RSCSAR_RSCSA19                     (1 << 19)  /* RAM Standby Control Security Attribute bit 19 */

#define R_SYSC_RSCSAR_RSCSA20                     (1 << 20)  /* RAM Standby Control Security Attribute bit 20 */

#define R_SYSC_RSCSAR_RSCSA21                     (1 << 21)  /* RAM Standby Control Security Attribute bit 21 */

#define R_SYSC_RSCSAR_RSCSA22                     (1 << 22)  /* RAM Standby Control Security Attribute bit 22 */

#define R_SYSC_RSCSAR_RSCSA23                     (1 << 23)  /* RAM Standby Control Security Attribute bit 23 */

#define R_SYSC_RSCSAR_RSCSA24                     (1 << 24)  /* RAM Standby Control Security Attribute bit 24 */

#define R_SYSC_RSCSAR_RSCSA25                     (1 << 25)  /* RAM Standby Control Security Attribute bit 25 */

#define R_SYSC_RSCSAR_RSCSA26                     (1 << 26)  /* RAM Standby Control Security Attribute bit 26 */

#define R_SYSC_RSCSAR_RSCSA27                     (1 << 27)  /* RAM Standby Control Security Attribute bit 27 */

#define R_SYSC_RSCSAR_RSCSA28                     (1 << 28)  /* RAM Standby Control Security Attribute bit 28 */

#define R_SYSC_RSCSAR_RSCSA29                     (1 << 29)  /* RAM Standby Control Security Attribute bit 29 */

#define R_SYSC_RSCSAR_RSCSA30                     (1 << 30)  /* RAM Standby Control Security Attribute bit 30 */

#define R_SYSC_RSCSAR_RSCSA31                     (1 << 31)  /* RAM Standby Control Security Attribute bit 31 */

/* DPFSAR1 Register bit definitions */
#define R_SYSC_DPFSAR1_DPFSA0                     (1 << 0)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 0 to 7) */

#define R_SYSC_DPFSAR1_DPFSA1                     (1 << 1)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 0 to 7) */

#define R_SYSC_DPFSAR1_DPFSA2                     (1 << 2)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 0 to 7) */

#define R_SYSC_DPFSAR1_DPFSA3                     (1 << 3)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 0 to 7) */

#define R_SYSC_DPFSAR1_DPFSA4                     (1 << 4)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 0 to 7) */

#define R_SYSC_DPFSAR1_DPFSA5                     (1 << 5)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 0 to 7) */

#define R_SYSC_DPFSAR1_DPFSA6                     (1 << 6)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 0 to 7) */

#define R_SYSC_DPFSAR1_DPFSA7                     (1 << 7)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 0 to 7) */

#define R_SYSC_DPFSAR1_DPFSA08                    (1 << 8)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 8 to 15) */

#define R_SYSC_DPFSAR1_DPFSA09                    (1 << 9)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 8 to 15) */

#define R_SYSC_DPFSAR1_DPFSA10                    (1 << 10)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 8 to 15) */

#define R_SYSC_DPFSAR1_DPFSA11                    (1 << 11)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 8 to 15) */

#define R_SYSC_DPFSAR1_DPFSA12                    (1 << 12)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 8 to 15) */

#define R_SYSC_DPFSAR1_DPFSA13                    (1 << 13)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 8 to 15) */

#define R_SYSC_DPFSAR1_DPFSA14                    (1 << 14)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 8 to 15) */

#define R_SYSC_DPFSAR1_DPFSA15                    (1 << 15)  /* Deep Software Standby Interrupt Factor Security Attribute bit n (n = 8 to 15) */

#define R_SYSC_DPFSAR1_DPFSA8                     (1 << 8)  /* Deep Standby Interrupt Factor Security Attribute bit 8 */

#define R_SYSC_DPFSAR1_DPFSA9                     (1 << 9)  /* Deep Standby Interrupt Factor Security Attribute bit 9 */

#define R_SYSC_DPFSAR1_DPFSA16                    (1 << 16)  /* Deep Standby Interrupt Factor Security Attribute bit 16 */

#define R_SYSC_DPFSAR1_DPFSA17                    (1 << 17)  /* Deep Standby Interrupt Factor Security Attribute bit 17 */

#define R_SYSC_DPFSAR1_DPFSA18                    (1 << 18)  /* Deep Standby Interrupt Factor Security Attribute bit 18 */

#define R_SYSC_DPFSAR1_DPFSA19                    (1 << 19)  /* Deep Standby Interrupt Factor Security Attribute bit 19 */

#define R_SYSC_DPFSAR1_DPFSA20                    (1 << 20)  /* Deep Standby Interrupt Factor Security Attribute bit 20 */

#define R_SYSC_DPFSAR1_DPFSA21                    (1 << 21)  /* Deep Standby Interrupt Factor Security Attribute bit 21 */

#define R_SYSC_DPFSAR1_DPFSA22                    (1 << 22)  /* Deep Standby Interrupt Factor Security Attribute bit 22 */

#define R_SYSC_DPFSAR1_DPFSA23                    (1 << 23)  /* Deep Standby Interrupt Factor Security Attribute bit 23 */

#define R_SYSC_DPFSAR1_DPFSA24                    (1 << 24)  /* Deep Standby Interrupt Factor Security Attribute bit 24 */

#define R_SYSC_DPFSAR1_DPFSA25                    (1 << 25)  /* Deep Standby Interrupt Factor Security Attribute bit 25 */

#define R_SYSC_DPFSAR1_DPFSA26                    (1 << 26)  /* Deep Standby Interrupt Factor Security Attribute bit 26 */

#define R_SYSC_DPFSAR1_DPFSA27                    (1 << 27)  /* Deep Standby Interrupt Factor Security Attribute bit 27 */

#define R_SYSC_DPFSAR1_DPFSA28                    (1 << 28)  /* Deep Standby Interrupt Factor Security Attribute bit 28 */

#define R_SYSC_DPFSAR1_DPFSA29                    (1 << 29)  /* Deep Standby Interrupt Factor Security Attribute bit 29 */

#define R_SYSC_DPFSAR1_DPFSA30                    (1 << 30)  /* Deep Standby Interrupt Factor Security Attribute bit 30 */

#define R_SYSC_DPFSAR1_DPFSA31                    (1 << 31)  /* Deep Standby Interrupt Factor Security Attribute bit 31 */

/* PRCR_S Register bit definitions */
#define R_SYSC_PRCR_S_PRC0                        (1 << 0)  /* Enable writing to the registers related to the clock generation circuit */

#define R_SYSC_PRCR_S_PRC1                        (1 << 1)  /* Enable writing to the registers related to the low power modes, and the battery backup function */

#define R_SYSC_PRCR_S_PRC3                        (1 << 3)  /* Enable writing to the registers related to the PVD */

#define R_SYSC_PRCR_S_PRC4                        (1 << 4)  /*  */

#define R_SYSC_PRCR_S_PRC5                        (1 << 5)  /*  */

#define R_SYSC_PRCR_S_PRKEY_SHIFT                 (8)  /* PRC Key Code */
#define R_SYSC_PRCR_S_PRKEY_MASK                  0xff00

/* LOCOCR Register bit definitions */
#define R_SYSC_LOCOCR_LCSTP                       (1 << 0)  /* LOCO Stop */

/* LOCOUTCR Register bit definitions */
#define R_SYSC_LOCOUTCR_LOCOUTRM_SHIFT            (0)  /* LOCO User Trimming */
#define R_SYSC_LOCOUTCR_LOCOUTRM_MASK             0xff

/* DPSBYCR Register bit definitions */
#define R_SYSC_DPSBYCR_DCSSMODE_SHIFT             (2)  /* DCDC soft start mode */
#define R_SYSC_DPSBYCR_DCSSMODE_MASK              0xc
#  define R_SYSC_DPSBYCR_DCSSMODE_00                      (0 << R_SYSC_DPSBYCR_DCSSMODE_SHIFT)  /* Setting prohibited */
#  define R_SYSC_DPSBYCR_DCSSMODE_01                      (1 << R_SYSC_DPSBYCR_DCSSMODE_SHIFT)  /* 128 µs */
#  define R_SYSC_DPSBYCR_DCSSMODE_10                      (2 << R_SYSC_DPSBYCR_DCSSMODE_SHIFT)  /* 256 µs */
#  define R_SYSC_DPSBYCR_DCSSMODE_11                      (3 << R_SYSC_DPSBYCR_DCSSMODE_SHIFT)  /* 512 µs */

#define R_SYSC_DPSBYCR_IOKEEP                     (1 << 6)  /* I/O Port Retention */

#define R_SYSC_DPSBYCR_DEEPCUT_SHIFT              (0)  /* Power-Supply Control */
#define R_SYSC_DPSBYCR_DEEPCUT_MASK               0x3

#define R_SYSC_DPSBYCR_DPSBY                      (1 << 7)  /* Deep Software Standby */

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

#define R_SYSC_DPSIER2_DPVD3IE                    (1 << 5)  /* PVD3 Deep Standby Cancel Signal Enable */

/* DPSIER3 Register bit definitions */
#define R_SYSC_DPSIER3_DUSBFSIE                   (1 << 0)  /* USBFS Suspend/Resume Deep Software Standby Cancel Signal Enable */

#define R_SYSC_DPSIER3_DUSBHSIE                   (1 << 1)  /* USBHS Suspend/Resume Deep Software Standby Cancel Signal Enable */

#define R_SYSC_DPSIER3_DULPT0IE                   (1 << 2)  /* ULPT0 Overflow Deep Software Standby Cancel Signal Enable */

#define R_SYSC_DPSIER3_DULPT1IE                   (1 << 3)  /* ULPT1 Overflow Deep Software Standby Cancel Signal Enable */

#define R_SYSC_DPSIER3_DIWDTIE                    (1 << 5)  /* IWDT Overflow Deep Software Standby Cancel Signal Enable */

#define R_SYSC_DPSIER3_DSOSTDIE                   (1 << 6)  /* Sub-clock Oscillation stop detection Deep Software Standby Cancel Signal Enable */

#define R_SYSC_DPSIER3_DVBATTADIE                 (1 << 7)  /* VBATT Tamper Detection Deep Software Standby Cancel Signal Enable */

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

#define R_SYSC_DPSIFR2_DPVD3IF                    (1 << 5)  /* PVD5 Deep Standby Cancel Flag */

/* DPSIFR3 Register bit definitions */
#define R_SYSC_DPSIFR3_DUSBFSIF                   (1 << 0)  /* USBFS Suspend/Resume Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR3_DUSBHSIF                   (1 << 1)  /* USBHS Suspend/Resume Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR3_DULPT0IF                   (1 << 2)  /* ULPT0 Overflow Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR3_DULPT1IF                   (1 << 3)  /* ULPT1 Overflow Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR3_DIWDTIF                    (1 << 5)  /* IWDT Overflow Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR3_DSOSTDIF                   (1 << 6)  /* Sub-clock Oscillation stop detection Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR3_DVBATTADIF                 (1 << 7)  /* VBATT Tamper Detection Deep Software Standby Cancel Flag */

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

#define R_SYSC_DPSIEGR2_DLVD1IEG                  (1 << 0)  /* LVD1 Edge Select */

#define R_SYSC_DPSIEGR2_DLVD2IEG                  (1 << 1)  /* LVD2 Edge Select */

#define R_SYSC_DPSIEGR2_DLVD3IEG                  (1 << 5)  /* LVD3 Edge Select */

/* DPSIEGR3 Register bit definitions */
#define R_SYSC_DPSIEGR3_DIRQ16EG                  (1 << 0)  /* IRQ16-DS Pin Edge Select */

#define R_SYSC_DPSIEGR3_DIRQ17EG                  (1 << 1)  /* IRQ17-DS Pin Edge Select */

#define R_SYSC_DPSIEGR3_DIRQ18EG                  (1 << 2)  /* IRQ18-DS Pin Edge Select */

#define R_SYSC_DPSIEGR3_DIRQ19EG                  (1 << 3)  /* IRQ19-DS Pin Edge Select */

#define R_SYSC_DPSIEGR3_DIRQ20EG                  (1 << 4)  /* IRQ20-DS Pin Edge Select */

#define R_SYSC_DPSIEGR3_DIRQ21EG                  (1 << 5)  /* IRQ21-DS Pin Edge Select */

#define R_SYSC_DPSIEGR3_DIRQ22EG                  (1 << 6)  /* IRQ22-DS Pin Edge Select */

#define R_SYSC_DPSIEGR3_DIRQ23EG                  (1 << 7)  /* IRQ23-DS Pin Edge Select */

/* SYOCDCR Register bit definitions */
#define R_SYSC_SYOCDCR_DBGEN                      (1 << 7)  /* Debugger Enable bit */

#define R_SYSC_SYOCDCR_DOCDF                      (1 << 0)  /* Deep Standby OCD flag */

/* RSTSR0 Register bit definitions */
#define R_SYSC_RSTSR0_PORF                        (1 << 0)  /* Power-On Reset Detect Flag */

#define R_SYSC_RSTSR0_PVD0RF                      (1 << 1)  /* Voltage Monitor 0 Reset Detect Flag */

#define R_SYSC_RSTSR0_PVD1RF                      (1 << 2)  /* Voltage Monitor 1 Reset Detect Flag */

#define R_SYSC_RSTSR0_PVD2RF                      (1 << 3)  /* Voltage Monitor 2 Reset Detect Flag */

#define R_SYSC_RSTSR0_PVD4RF                      (1 << 5)  /* Voltage Monitor 4 Reset Detect Flag */

#define R_SYSC_RSTSR0_PVD5RF                      (1 << 6)  /* Voltage Monitor 5 Reset Detect Flag */

#define R_SYSC_RSTSR0_DPSRSTF                     (1 << 7)  /* Deep Software Standby Reset Flag */

#define R_SYSC_RSTSR0_LVD0RF                      (1 << 1)  /* Voltage Monitor 0 Reset Detect Flag */

#define R_SYSC_RSTSR0_LVD1RF                      (1 << 2)  /* Voltage Monitor 1 Reset Detect Flag */

#define R_SYSC_RSTSR0_LVD2RF                      (1 << 3)  /* Voltage Monitor 2 Reset Detect Flag */

#define R_SYSC_RSTSR0_LVD4RF                      (1 << 5)  /* Voltage Monitor 4 Reset Detect Flag */

#define R_SYSC_RSTSR0_LVD5RF                      (1 << 6)  /* Voltage Monitor 5 Reset Detect Flag */

/* RSTSR2 Register bit definitions */
#define R_SYSC_RSTSR2_CWSF                        (1 << 0)  /* Cold/Warm Start Determination Flag */

/* RSTSR3 Register bit definitions */
#define R_SYSC_RSTSR3_CVMRF                       (1 << 0)  /* Core Voltage Monitor Reset Detect Flag */

#define R_SYSC_RSTSR3_TEMPRF                      (1 << 7)  /* Temperature Monitor Reset Detect Flag */

#define R_SYSC_RSTSR3_OCPRF                       (1 << 4)  /* Overcurrent Protection Reset Detect Flag */

/* MOMCR Register bit definitions */
#define R_SYSC_MOMCR_MODRV0_SHIFT                 (1)  /* Main Clock Oscillator Drive Capability 0 Switching */
#define R_SYSC_MOMCR_MODRV0_MASK                  0xe
#  define R_SYSC_MOMCR_MODRV0_000                         (0 << R_SYSC_MOMCR_MODRV0_SHIFT)  /* 8 MHz */
#  define R_SYSC_MOMCR_MODRV0_011                         (3 << R_SYSC_MOMCR_MODRV0_SHIFT)  /* 8MHz to 24MHz */
#  define R_SYSC_MOMCR_MODRV0_101                         (5 << R_SYSC_MOMCR_MODRV0_SHIFT)  /* 8MHz to 48MHz */

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
#  define R_SYSC_PVDCMPCR_PVDLVL_0X03                     (3 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 3.86 V (Vdetm_3) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X04                     (4 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 3.14 V (Vdetm_4) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X05                     (5 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 3.10 V (Vdetm_5) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X06                     (6 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 3.08 V (Vdetm_6) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X07                     (7 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 2.85 V (Vdetm_7) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X08                     (8 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 2.83 V (Vdetm_8) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X09                     (9 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 2.80 V (Vdetm_9) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X0A                     (10 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 2.62V (Vdetm_10) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X0B                     (11 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 2.33V (Vdetm_11) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X0C                     (12 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 1.90V (Vdetm_12) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X0D                     (13 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 1.86V (Vdetm_13) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X0E                     (14 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 1.74V (Vdetm_14) */
#  define R_SYSC_PVDCMPCR_PVDLVL_0X0F                     (15 << R_SYSC_PVDCMPCR_PVDLVL_SHIFT)  /* 1.71V (Vdetm_15) */

#define R_SYSC_PVDCMPCR_PVDE                      (1 << 7)  /* Voltage Detection m Enable */

/* PVDCMPCR Register bit definitions */
#define R_SYSC_PVDCMPCR_PVDLVL_SHIFT              (0)  /* Detection Voltage n Level Select */
#define R_SYSC_PVDCMPCR_PVDLVL_MASK               0x1f

#define R_SYSC_PVDCMPCR_PVDE                      (1 << 7)  /* Voltage Detection n Enable */

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

/* PVDCR Register bit definitions */
#define R_SYSC_PVDCR_RE                           (1 << 0)  /* Voltage Monitor n Reset Enable */

#define R_SYSC_PVDCR_DFDIS                        (1 << 1)  /* Voltage Monitor n Digital Filter Disable Mode Select */

#define R_SYSC_PVDCR_CMPE                         (1 << 2)  /* Voltage Monitor n Circuit Comparison Result Output Enable */

#define R_SYSC_PVDCR_FSAMP_SHIFT                  (4)  /* Sampling Clock Select */
#define R_SYSC_PVDCR_FSAMP_MASK                   0x30
#  define R_SYSC_PVDCR_FSAMP_00                           (0 << R_SYSC_PVDCR_FSAMP_SHIFT)  /* 1/2 LOCO frequency */
#  define R_SYSC_PVDCR_FSAMP_01                           (1 << R_SYSC_PVDCR_FSAMP_SHIFT)  /* 1/4 LOCO frequency */
#  define R_SYSC_PVDCR_FSAMP_10                           (2 << R_SYSC_PVDCR_FSAMP_SHIFT)  /* 1/8 LOCO frequency */
#  define R_SYSC_PVDCR_FSAMP_11                           (3 << R_SYSC_PVDCR_FSAMP_SHIFT)  /* 1/16 LOCO frequency */

/* VBATTMNSELR Register bit definitions */
#define R_SYSC_VBATTMNSELR_VBTMNSEL               (1 << 0)  /* VBATT Voltage Monitor Function Select Bit */

#define R_SYSC_VBATTMNSELR_VBATTMNSEL             (1 << 0)  /* VBATT Low Voltage Detect Function Select Bit */

/* VBTBPCR1 Register bit definitions */
#define R_SYSC_VBTBPCR1_BPWSWSTP                  (1 << 0)  /* Battery Power Supply Switch Stop */

/* LPSCR Register bit definitions */
#define R_SYSC_LPSCR_LPMD_SHIFT                   (0)  /* Low power mode setting */
#define R_SYSC_LPSCR_LPMD_MASK                    0xf
#  define R_SYSC_LPSCR_LPMD_0X0                           (0 << R_SYSC_LPSCR_LPMD_SHIFT)  /* System Active */
#  define R_SYSC_LPSCR_LPMD_0X4                           (4 << R_SYSC_LPSCR_LPMD_SHIFT)  /* Reserved */
#  define R_SYSC_LPSCR_LPMD_0X5                           (5 << R_SYSC_LPSCR_LPMD_SHIFT)  /* Software Standby mode */
#  define R_SYSC_LPSCR_LPMD_0X8                           (8 << R_SYSC_LPSCR_LPMD_SHIFT)  /* Deep Software Standby mode 1 */
#  define R_SYSC_LPSCR_LPMD_0X9                           (9 << R_SYSC_LPSCR_LPMD_SHIFT)  /* Deep Software Standby mode 2 */
#  define R_SYSC_LPSCR_LPMD_0XA                           (10 << R_SYSC_LPSCR_LPMD_SHIFT)  /* Deep Software Standby mode 3 */

/* SSCR1 Register bit definitions */
#define R_SYSC_SSCR1_SS2FR                        (1 << 0)  /* Software Standby Fast Return */

#define R_SYSC_SSCR1_SS2LP_SHIFT                  (2)  /* Software Standby low power select */
#define R_SYSC_SSCR1_SS2LP_MASK                   0xc
#  define R_SYSC_SSCR1_SS2LP_00                           (0 << R_SYSC_SSCR1_SS2LP_SHIFT)  /* SS2LP_0 (default mode) */
#  define R_SYSC_SSCR1_SS2LP_01                           (1 << R_SYSC_SSCR1_SS2LP_SHIFT)  /* SS2LP_1 (Low power setting 1) */

/* SVSCR Register bit definitions */
#define R_SYSC_SVSCR_SVSCM_SHIFT                  (0)  /* SSTBY Voltage Scaling Control Mode Bit */
#define R_SYSC_SVSCR_SVSCM_MASK                   0x7
#  define R_SYSC_SVSCR_SVSCM_001                          (1 << R_SYSC_SVSCR_SVSCM_SHIFT)  /* SVSCR_1 */
#  define R_SYSC_SVSCR_SVSCM_010                          (2 << R_SYSC_SVSCR_SVSCM_SHIFT)  /* SVSCR_2 (default) */
#  define R_SYSC_SVSCR_SVSCM_011                          (3 << R_SYSC_SVSCR_SVSCM_SHIFT)  /* SVSCR_3 */
#  define R_SYSC_SVSCR_SVSCM_100                          (4 << R_SYSC_SVSCR_SVSCM_SHIFT)  /* SVSCR_4 */
#  define R_SYSC_SVSCR_SVSCM_101                          (5 << R_SYSC_SVSCR_SVSCM_SHIFT)  /* SVSCR_5 */

/* LVOCR Register bit definitions */
#define R_SYSC_LVOCR_LVO0E                        (1 << 0)  /* Low Voltage Operation 0 Enable */

#define R_SYSC_LVOCR_LVO1E                        (1 << 1)  /* Low Voltage Operation 1 Enable */

/* MWMCR Register bit definitions */
#define R_SYSC_MWMCR_MWM_SHIFT                    (0)  /* OTP Write Mode [1:0] */
#define R_SYSC_MWMCR_MWM_MASK                     0x3
#  define R_SYSC_MWMCR_MWM_00                             (0 << R_SYSC_MWMCR_MWM_SHIFT)  /* OTP normal speed write mode */
#  define R_SYSC_MWMCR_MWM_01                             (1 << R_SYSC_MWMCR_MWM_SHIFT)  /* OTP high speed write mode 0 */
#  define R_SYSC_MWMCR_MWM_10                             (2 << R_SYSC_MWMCR_MWM_SHIFT)  /* OTP high speed write mode 1 */
#  define R_SYSC_MWMCR_MWM_11                             (3 << R_SYSC_MWMCR_MWM_SHIFT)  /* Prohibited */

/* SYRSTMSK0 Register bit definitions */
#define R_SYSC_SYRSTMSK0_IWDTMASK                 (1 << 0)  /* Independent Watchdog Timer Reset Mask */

#define R_SYSC_SYRSTMSK0_WDT0MASK                 (1 << 1)  /* CPU0 Watchdog Timer Reset Mask */

#define R_SYSC_SYRSTMSK0_SWMASK                   (1 << 2)  /* Software Reset Mask */

#define R_SYSC_SYRSTMSK0_CLU0MASK                 (1 << 4)  /* CPU0 Lockup Reset Mask */

#define R_SYSC_SYRSTMSK0_LM0MASK                  (1 << 5)  /* Local Memory 0 Error Reset Mask */

#define R_SYSC_SYRSTMSK0_CMMASK                   (1 << 6)  /* Common Memory Error Reset Mask */

#define R_SYSC_SYRSTMSK0_BUSMASK                  (1 << 7)  /* Bus Error Reset Mask */

/* SYRSTMSK1 Register bit definitions */
#define R_SYSC_SYRSTMSK1_WDT1MASK                 (1 << 1)  /* CPU1 Watchdog Timer Reset Mask */

#define R_SYSC_SYRSTMSK1_CLU1MASK                 (1 << 4)  /* CPU1 Lockup Reset Mask */

#define R_SYSC_SYRSTMSK1_LM1MASK                  (1 << 5)  /* Local Memory 1 Error Reset Mask */

/* SYRSTMSK2 Register bit definitions */
#define R_SYSC_SYRSTMSK2_PVD1MASK                 (1 << 0)  /* Voltage Monitor 1 Reset Mask */

#define R_SYSC_SYRSTMSK2_PVD2MASK                 (1 << 1)  /* Voltage Monitor 2 Reset Mask */

/* TEMPRCR Register bit definitions */
#define R_SYSC_TEMPRCR_TEMPREN                    (1 << 0)  /* Temperature Reset Enable */

#define R_SYSC_TEMPRCR_TSNEN                      (1 << 1)  /* Temperature Sensor Enable */

#define R_SYSC_TEMPRCR_CMPEN                      (1 << 2)  /* Comparator Enable */

#define R_SYSC_TEMPRCR_TSNKEEP                    (1 << 3)  /* Temperature Sensor Latch Control */

/* TEMPRLR Register bit definitions */
#define R_SYSC_TEMPRLR_LOCK                       (1 << 0)  /* Temperature Monitor Reset Control Register Lock */

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

/* PVDFCR Register bit definitions */
#define R_SYSC_PVDFCR_RHSEL                       (1 << 0)  /* Rise Hysteresis Select */

/* PVDLR Register bit definitions */
#define R_SYSC_PVDLR_LOCK                         (1 << 0)  /* LOCK control */

/* DPSIER4 Register bit definitions */
#define R_SYSC_DPSIER4_DIRQ16E                    (1 << 0)  /* IRQ16-DS Pin Enable */

#define R_SYSC_DPSIER4_DIRQ17E                    (1 << 1)  /* IRQ17-DS Pin Enable */

#define R_SYSC_DPSIER4_DIRQ18E                    (1 << 2)  /* IRQ18-DS Pin Enable */

#define R_SYSC_DPSIER4_DIRQ19E                    (1 << 3)  /* IRQ19-DS Pin Enable */

#define R_SYSC_DPSIER4_DIRQ20E                    (1 << 4)  /* IRQ20-DS Pin Enable */

#define R_SYSC_DPSIER4_DIRQ21E                    (1 << 5)  /* IRQ21-DS Pin Enable */

#define R_SYSC_DPSIER4_DIRQ22E                    (1 << 6)  /* IRQ22-DS Pin Enable */

#define R_SYSC_DPSIER4_DIRQ23E                    (1 << 7)  /* IRQ23-DS Pin Enable */

/* DPSIER5 Register bit definitions */
#define R_SYSC_DPSIER5_DIRQ24E                    (1 << 0)  /* IRQ24-DS Pin Enable */

#define R_SYSC_DPSIER5_DIRQ25E                    (1 << 1)  /* IRQ25-DS Pin Enable */

#define R_SYSC_DPSIER5_DIRQ26E                    (1 << 2)  /* IRQ26-DS Pin Enable */

#define R_SYSC_DPSIER5_DIRQ27E                    (1 << 3)  /* IRQ27-DS Pin Enable */

#define R_SYSC_DPSIER5_DIRQ28E                    (1 << 4)  /* IRQ28-DS Pin Enable */

#define R_SYSC_DPSIER5_DIRQ29E                    (1 << 5)  /* IRQ29-DS Pin Enable */

#define R_SYSC_DPSIER5_DIRQ30E                    (1 << 6)  /* IRQ30-DS Pin Enable */

#define R_SYSC_DPSIER5_DIRQ31E                    (1 << 7)  /* IRQ31-DS Pin Enable */

/* DPSIFR4 Register bit definitions */
#define R_SYSC_DPSIFR4_DIRQ16F                    (1 << 0)  /* IRQ16-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR4_DIRQ17F                    (1 << 1)  /* IRQ17-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR4_DIRQ18F                    (1 << 2)  /* IRQ18-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR4_DIRQ19F                    (1 << 3)  /* IRQ19-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR4_DIRQ20F                    (1 << 4)  /* IRQ20-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR4_DIRQ21F                    (1 << 5)  /* IRQ21-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR4_DIRQ22F                    (1 << 6)  /* IRQ22-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR4_DIRQ23F                    (1 << 7)  /* IRQ23-DS Pin Deep Software Standby Cancel Flag */

/* DPSIFR5 Register bit definitions */
#define R_SYSC_DPSIFR5_DIRQ24F                    (1 << 0)  /* IRQ24-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR5_DIRQ25F                    (1 << 1)  /* IRQ25-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR5_DIRQ26F                    (1 << 2)  /* IRQ26-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR5_DIRQ27F                    (1 << 3)  /* IRQ27-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR5_DIRQ28F                    (1 << 4)  /* IRQ28-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR5_DIRQ29F                    (1 << 5)  /* IRQ29-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR5_DIRQ30F                    (1 << 6)  /* IRQ30-DS Pin Deep Software Standby Cancel Flag */

#define R_SYSC_DPSIFR5_DIRQ31F                    (1 << 7)  /* IRQ31-DS Pin Deep Software Standby Cancel Flag */

/* DPSIEGR4 Register bit definitions */
#define R_SYSC_DPSIEGR4_DIRQ24EG                  (1 << 0)  /* IRQ24-DS Pin Edge Select */

#define R_SYSC_DPSIEGR4_DIRQ25EG                  (1 << 1)  /* IRQ25-DS Pin Edge Select */

#define R_SYSC_DPSIEGR4_DIRQ26EG                  (1 << 2)  /* IRQ26-DS Pin Edge Select */

#define R_SYSC_DPSIEGR4_DIRQ27EG                  (1 << 3)  /* IRQ27-DS Pin Edge Select */

#define R_SYSC_DPSIEGR4_DIRQ28EG                  (1 << 4)  /* IRQ28-DS Pin Edge Select */

#define R_SYSC_DPSIEGR4_DIRQ29EG                  (1 << 5)  /* IRQ29-DS Pin Edge Select */

#define R_SYSC_DPSIEGR4_DIRQ30EG                  (1 << 6)  /* IRQ30-DS Pin Edge Select */

#define R_SYSC_DPSIEGR4_DIRQ31EG                  (1 << 7)  /* IRQ31-DS Pin Edge Select */

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

/* SOSTDCR Register bit definitions */
#define R_SYSC_SOSTDCR_SOSTDIE                    (1 << 0)  /* Sub-clock Oscillation Stop Detection Interrupt Enable */

#define R_SYSC_SOSTDCR_SOSTDE                     (1 << 7)  /* Sub-clock Oscillation Stop Detection Function Enable */

/* SOSTDSR Register bit definitions */
#define R_SYSC_SOSTDSR_SOSTDF                     (1 << 0)  /* Sub-clock Oscillation Stop Detection Flag */

/* VBTBER Register bit definitions */
#define R_SYSC_VBTBER_VBAE                        (1 << 3)  /* VBATT backup register access enable bit */

/* VBTBPCR2 Register bit definitions */
#define R_SYSC_VBTBPCR2_VDETLVL_SHIFT             (0)  /* VDETBATT Level Select */
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

/* VBTNCWCR Register bit definitions */
#define R_SYSC_VBTNCWCR_VINCW_SHIFT               (0)  /* VBATT Input Noise Canceler Width select */
#define R_SYSC_VBTNCWCR_VINCW_MASK                0x7
#  define R_SYSC_VBTNCWCR_VINCW_000                       (0 << R_SYSC_VBTNCWCR_VINCW_SHIFT)  /* 32.768 kHz */
#  define R_SYSC_VBTNCWCR_VINCW_001                       (1 << R_SYSC_VBTNCWCR_VINCW_SHIFT)  /* 64 Hz */
#  define R_SYSC_VBTNCWCR_VINCW_010                       (2 << R_SYSC_VBTNCWCR_VINCW_SHIFT)  /* 32 Hz */
#  define R_SYSC_VBTNCWCR_VINCW_011                       (3 << R_SYSC_VBTNCWCR_VINCW_SHIFT)  /* 16 Hz */
#  define R_SYSC_VBTNCWCR_VINCW_100                       (4 << R_SYSC_VBTNCWCR_VINCW_SHIFT)  /* 8 Hz */
#  define R_SYSC_VBTNCWCR_VINCW_101                       (5 << R_SYSC_VBTNCWCR_VINCW_SHIFT)  /* 4 Hz */
#  define R_SYSC_VBTNCWCR_VINCW_110                       (6 << R_SYSC_VBTNCWCR_VINCW_SHIFT)  /* 2 Hz */
#  define R_SYSC_VBTNCWCR_VINCW_111                       (7 << R_SYSC_VBTNCWCR_VINCW_SHIFT)  /* 1 Hz */

/* VBTADCR3 Register bit definitions */
#define R_SYSC_VBTADCR3_VBTADZE0                  (1 << 0)  /* VBATT Tamper Detection Zeroization Enable 0 */

#define R_SYSC_VBTADCR3_VBTADZE1                  (1 << 1)  /* VBATT Tamper Detection Zeroization Enable 1 */

#define R_SYSC_VBTADCR3_VBTADZE2                  (1 << 2)  /* VBATT Tamper Detection Zeroization Enable 2 */

/* VBTBKR Register bit definitions */
#define R_SYSC_VBTBKR_VBTBKRN_SHIFT               (0)  /* VBATT Backup Register */
#define R_SYSC_VBTBKR_VBTBKRN_MASK                0xff

#define R_SYSC_VBTBKR_VBTBKR_SHIFT                (0)  /* VBTBKR is a 512-byte readable/writable register to store data powered by VBATT.The value of this register is retained even when VCC is not powered but VBATT is powered.VBTBKR is initialized by VBATT selected voltage power-on-reset. */
#define R_SYSC_VBTBKR_VBTBKR_MASK                 0xff


/* Maximum number of channels */

#define SYSC_MAX_CHANNELS    128

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SYSC_H */

/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_system.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SYSTEM_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SYSTEM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SYSTEM Base Address */
#ifndef R_SYSTEM_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_SYSTEM_BASE           0x4001e000
#else
#define R_SYSTEM_BASE           0x5001e000
#endif
#endif

/* SYSTEM Register Offsets */

#define R_SYSTEM_SBYCR_OFFSET                     0x0000000c  /* Standby Control Register */
#define R_SYSTEM_SSCR2_OFFSET                     0x0000000e  /* Software Standby Control Register 2 */
#define R_SYSTEM_MRSCR_OFFSET                     0x00000010  /* MRAM Standby Control Register */
#define R_SYSTEM_VSCR_OFFSET                      0x00000014  /* Voltage Scaling Control Register */
#define R_SYSTEM_SRMONR_OFFSET                    0x00000018  /* SRAM Monitor Register */
#define R_SYSTEM_SCKDIVCR_OFFSET                  0x00000020  /* System Clock Division Control Register */
#define R_SYSTEM_SCKDIVCR2_OFFSET                 0x00000024  /* System Clock Division Control Register 2 */
#define R_SYSTEM_SCKSCR_OFFSET                    0x00000026  /* System Clock Source Control Register */
#define R_SYSTEM_PLLCR_OFFSET                     0x0000002a  /* PLL1 Control Register */
#define R_SYSTEM_BCKCR_OFFSET                     0x00000030  /* External Bus Clock Control Register */
#define R_SYSTEM_MEMWAIT_OFFSET                   0x00000031  /* Memory Wait Cycle Control Register */
#define R_SYSTEM_MOSCCR_OFFSET                    0x00000032  /* Main Clock Oscillator Control Register  */
#define R_SYSTEM_HOCOCR_OFFSET                    0x00000036  /* High-Speed On-Chip Oscillator Control Register */
#define R_SYSTEM_MOCOCR_OFFSET                    0x00000038  /* Middle-Speed On-Chip Oscillator Control Register */
#define R_SYSTEM_FLLCR1_OFFSET                    0x00000039  /* FLL Control Register 1 */
#define R_SYSTEM_FLLCR2_OFFSET                    0x0000003a  /* FLL Control Register 2 */
#define R_SYSTEM_OSCSF_OFFSET                     0x0000003c  /* Oscillation Stabilization Flag Register */
#define R_SYSTEM_CKOCR_OFFSET                     0x0000003e  /* Clock Out Control Register */
#define R_SYSTEM_TRCKCR_OFFSET                    0x0000003f  /* Trace Clock Control Register */
#define R_SYSTEM_OSTDCR_OFFSET                    0x00000040  /* Oscillation Stop Detection Control Register */
#define R_SYSTEM_OSTDSR_OFFSET                    0x00000041  /* Oscillation Stop Detection Status Register */
#define R_SYSTEM_OSCMONR_OFFSET                   0x00000043  /* Oscillator Monitor Register */
#define R_SYSTEM_PLL2CR_OFFSET                    0x0000004a  /* PLL2 Control Register */
#define R_SYSTEM_PLLCCR2_OFFSET                   0x0000004c  /* PLL1 Clock Control Register 2 */
#define R_SYSTEM_LPOPT_OFFSET                     0x0000004c  /* Lower Power Operation Control Register */
#define R_SYSTEM_PLL2CCR2_OFFSET                  0x0000004e  /* PLL2 Clock Control Register 2 */
#define R_SYSTEM_SLCDSCKCR_OFFSET                 0x00000050  /* Segment LCD Source Clock Control Register */
#define R_SYSTEM_EBCKOCR_OFFSET                   0x00000052  /* External Bus Clock Output Control Register */
#define R_SYSTEM_SDCKOCR_OFFSET                   0x00000053  /* SDRAM Clock Output Control Register */
#define R_SYSTEM_SCICKDIVCR_OFFSET                0x00000054  /* SCI clock Division control register */
#define R_SYSTEM_SCICKCR_OFFSET                   0x00000055  /* SCI clock control register */
#define R_SYSTEM_SPICKDIVCR_OFFSET                0x00000056  /* SPI clock Division control register */
#define R_SYSTEM_SPICKCR_OFFSET                   0x00000057  /* SPI clock control register */
#define R_SYSTEM_ADCCKDIVCR_OFFSET                0x0000005a  /* ADC clock Division control register */
#define R_SYSTEM_ADCCKCR_OFFSET                   0x0000005b  /* ADC clock control register */
#define R_SYSTEM_GPTCKDIVCR_OFFSET                0x0000005c  /* GPT Clock Division Control Register */
#define R_SYSTEM_GPTCKCR_OFFSET                   0x0000005d  /* GPT clock control register */
#define R_SYSTEM_LCDCKDIVCR_OFFSET                0x0000005e  /* LCD clock Division control register */
#define R_SYSTEM_LCDCKCR_OFFSET                   0x0000005f  /* LCD clock control register */
#define R_SYSTEM_MOCOUTCR_OFFSET                  0x00000061  /* MOCO User Trimming Control Register */
#define R_SYSTEM_HOCOUTCR_OFFSET                  0x00000062  /* HOCO User Trimming Control Register */
#define R_SYSTEM_USBCKDIVCR_OFFSET                0x0000006c  /* USB Clock Division Control Register */
#define R_SYSTEM_OCTACKDIVCR_OFFSET               0x0000006d  /* Octal-SPI Clock Division Control Register */
#define R_SYSTEM_CANFDCKDIVCR_OFFSET              0x0000006e  /* CANFD Clock Division Control Register */
#define R_SYSTEM_USB60CKDIVCR_OFFSET              0x0000006f  /* USB60 Clock Division Control Register */
#define R_SYSTEM_I3CCKDIVCR_OFFSET                0x00000070  /* I3C Clock Division control register */
#define R_SYSTEM_USBCKCR_OFFSET                   0x00000074  /* USB Clock Control Register */
#define R_SYSTEM_OCTACKCR_OFFSET                  0x00000075  /* Octal-SPI Clock Control Register */
#define R_SYSTEM_CANFDCKCR_OFFSET                 0x00000076  /* CANFD Clock Control Register */
#define R_SYSTEM_USB60CKCR_OFFSET                 0x00000077  /* USB60 clock control register */
#define R_SYSTEM_I3CCKCR_OFFSET                   0x00000078  /* I3C Clock Control Register */
#define R_SYSTEM_MOSCSCR_OFFSET                   0x0000007c  /* Main Clock Oscillator Standby Control Register */
#define R_SYSTEM_HOCOSCR_OFFSET                   0x0000007d  /* High-Speed On-Chip Oscillator Standby Control Register */
#define R_SYSTEM_MOCOSCR_OFFSET                   0x00000084  /* Middle-Speed On-Chip Oscillator Standby Control Register */
#define R_SYSTEM_FLSTOP_OFFSET                    0x0000009e  /* Flash Operation Control Register */
#define R_SYSTEM_PSMCR_OFFSET                     0x0000009f  /* Power Save Memory Control Register */
#define R_SYSTEM_OPCCR_OFFSET                     0x000000a0  /* Operating Power Control Register */
#define R_SYSTEM_MOSCWTCR_OFFSET                  0x000000a2  /* Main Clock Oscillator Wait Control Register */
#define R_SYSTEM_HOCOWTCR_OFFSET                  0x000000a5  /* High-speed on-chip oscillator wait control register */
#define R_SYSTEM_SOPCCR_OFFSET                    0x000000aa  /* Sub Operating Power Control Register */
#define R_SYSTEM_PLLCCR_OFFSET                    0x000000ac  /* PLL1 Clock Control Register */
#define R_SYSTEM_RSTSR1_OFFSET                    0x000000c0  /* Reset Status Register 1 */
#define R_SYSTEM_PLL2CCR_OFFSET                   0x000000c8  /* PLL2 Clock Control Register */
#define R_SYSTEM_SYRACCR_OFFSET                   0x000000cc  /* System Register Access Control Register */
#define R_SYSTEM_USBCKCR_ALT_OFFSET               0x000000d0  /* USB Clock Control Register */
#define R_SYSTEM_SDADCCKCR_OFFSET                 0x000000d1  /* 24-bit Sigma-Delta A/D Converter Clock Control Register */
#define R_SYSTEM_BCKADIVCR_OFFSET                 0x000000d4  /* Asynchronous external Bus clock Division control register */
#define R_SYSTEM_ESWCKDIVCR_OFFSET                0x000000d5  /* EtherSW clock Division control register */
#define R_SYSTEM_ESWPCKDIVCR_OFFSET               0x000000d6  /* EtherSW-PHY clock Division control register */
#define R_SYSTEM_ESCCKDIVCR_OFFSET                0x000000d7  /* EtherCAT clock Division control register */
#define R_SYSTEM_ETHPCKDIVCR_OFFSET               0x000000d8  /* Ether-PHY clock Division control register */
#define R_SYSTEM_BCKACR_OFFSET                    0x000000da  /* Asynchronous external bus clock control register */
#define R_SYSTEM_ESWCKCR_OFFSET                   0x000000db  /* EtherSW clock control register */
#define R_SYSTEM_ESWPCKCR_OFFSET                  0x000000dc  /* EtherSW-PHY clock control register */
#define R_SYSTEM_ESCCKCR_OFFSET                   0x000000dd  /* EtherCAT clock control register */
#define R_SYSTEM_ETHPCKCR_OFFSET                  0x000000de  /* Ether-PHY clock control register */
/* LVD%sCR1 Registers (1-5) */
#define R_SYSTEM_LVDCR1_OFFSET(m)                 (0x000000e0 + ((m) * 0x00000002))  /* Voltage Monitor %s Circuit Control Register 1 */
/* LVD%sSR Registers (1-3) */
#define R_SYSTEM_LVDSR_OFFSET(m)                  (0x000000e1 + ((m) * 0x00000002))  /* Voltage Monitor %s Circuit Status Register */
#define R_SYSTEM_CRVSYSCR_OFFSET                  0x000000f0  /* Clock Recovery System Control Register */
#define R_SYSTEM_CPUDSCR_OFFSET                   0x00000100  /* CPU Deep Sleep Control Register */
/* PDCTR%s Registers (GD,NPU,ESWM) */
#define R_SYSTEM_PDCTR_OFFSET(m)                  (0x00000110 + ((m) * 0x00000004))  /* General Power Domain %s Control Register */
#define R_SYSTEM_PDRAMSCR0_OFFSET                 0x00000140  /* SRAM power domain Standby Control Register 0 */
#define R_SYSTEM_PDRAMSCR1_OFFSET                 0x00000142  /* SRAM power domain Standby Control Register 1 */
#define R_SYSTEM_VBRSABAR_OFFSET                  0x000003b0  /* VBATT Backup Register Security Attribute Boundary Address Register */
#define R_SYSTEM_VBRPABARS_OFFSET                 0x000003b4  /* VBATT Backup Register Privilege Attribute Boundary Address Register for Secure Region */
#define R_SYSTEM_VBRPABARNS_OFFSET                0x000003b8  /* VBATT Backup Register Privilege Attribute Boundary Address Register for Non-secure Region */
#define R_SYSTEM_CGFSAR_OFFSET                    0x000003c0  /* Clock Generation Function Security Attribute Register */
#define R_SYSTEM_RSTSAR_OFFSET                    0x000003c4  /* Reset Security Attribution Register */
#define R_SYSTEM_LPMSAR_OFFSET                    0x000003c8  /* Low Power Mode Security Attribution Register */
#define R_SYSTEM_LVDSAR_OFFSET                    0x000003cc  /* Low Voltage Detection Security Attribution Register */
#define R_SYSTEM_BBFSAR_OFFSET                    0x000003d0  /* Battery Backup Function Security Attribute Register */
#define R_SYSTEM_PGCSAR_OFFSET                    0x000003d8  /* Power Gating Control Security Attribution Register */
#define R_SYSTEM_DPFSAR_OFFSET                    0x000003e0  /* Deep Standby Interrupt Factor Security Attribution Register */
#define R_SYSTEM_RSCSAR_OFFSET                    0x000003e4  /* RAM Standby Control Security Attribution Register */
#define R_SYSTEM_DPFSAR1_OFFSET                   0x000003e8  /* Deep Standby Interrupt Factor Security Attribution Register 1 */
#define R_SYSTEM_PRCR_OFFSET                      0x000003fa  /* Protect Register for Secure Register */
#define R_SYSTEM_PRCR_NS_OFFSET                   0x000003fe  /* Protect Register for Non-secure Register */
#define R_SYSTEM_LOCOCR_OFFSET                    0x00000400  /* Low-Speed On-Chip Oscillator Control Register */
#define R_SYSTEM_LOCOUTCR_OFFSET                  0x00000402  /* LOCO User Trimming Control Register */
#define R_SYSTEM_STCONR_OFFSET                    0x0000040f  /* Standby Condition Register */
#define R_SYSTEM_FWEPROR_OFFSET                   0x00000416  /* Flash P/E Protect Register */
#define R_SYSTEM_VBATTMONR_OFFSET                 0x0000041e  /* Battery Backup Voltage Monitor Register */
#define R_SYSTEM_VBTCR1_OFFSET                    0x0000041f  /* VBATT Control Register1 */
#define R_SYSTEM_DCDCCTL_OFFSET                   0x00000440  /* DCDC/LDO Control Register */
#define R_SYSTEM_VCCSEL_OFFSET                    0x00000441  /* Voltage Level Selection Control Register */
#define R_SYSTEM_SOMRG_OFFSET                     0x00000482  /* Sub Clock Oscillator Margin Check Register */
#define R_SYSTEM_VBTCR2_OFFSET                    0x000004b0  /* VBATT Control Register2 */
#define R_SYSTEM_VBTSR_OFFSET                     0x000004b1  /* VBATT Status Register */
#define R_SYSTEM_VBTCMPCR_OFFSET                  0x000004b2  /* VBATT Comparator Control Register */
#define R_SYSTEM_VBTLVDICR_OFFSET                 0x000004b4  /* VBATT Pin Low Voltage Detect Interrupt Control Register */
#define R_SYSTEM_VBTWCTLR_OFFSET                  0x000004b6  /* VBATT Wakeup function Control Register */
#define R_SYSTEM_VBTWCH0OTSR_OFFSET               0x000004b8  /* VBATT Wakeup I/O 0 Output Trigger Select Register */
#define R_SYSTEM_VBTWCH1OTSR_OFFSET               0x000004b9  /* VBATT Wakeup I/O 1 Output Trigger Select Register */
#define R_SYSTEM_VBTWCH2OTSR_OFFSET               0x000004ba  /* VBATT Wakeup I/O 2 Output Trigger Select Register */
#define R_SYSTEM_VBTOCTLR_OFFSET                  0x000004bc  /* VBATT Output Control Register */
#define R_SYSTEM_VBTWTER_OFFSET                   0x000004bd  /* VBATT Wakeup Trigger source Enable Register */
#define R_SYSTEM_VBTWEGR_OFFSET                   0x000004be  /* VBATT Wakeup Trigger source Edge Register */
#define R_SYSTEM_VBTWFR_OFFSET                    0x000004bf  /* VBATT Wakeup trigger source Flag Register */
#define R_SYSTEM_DPSBYCR_OFFSET                   0x00000a00  /* Deep Standby Control Register */
#define R_SYSTEM_DPSIER0_OFFSET                   0x00000a08  /* Deep Standby Interrupt Enable Register 0 */
#define R_SYSTEM_DPSIER1_OFFSET                   0x00000a0c  /* Deep Standby Interrupt Enable Register 1 */
#define R_SYSTEM_DPSIER2_OFFSET                   0x00000a10  /* Deep Standby Interrupt Enable Register 2 */
#define R_SYSTEM_DPSIER3_OFFSET                   0x00000a14  /* Deep Standby Interrupt Enable Register 3 */
#define R_SYSTEM_DPSIFR0_OFFSET                   0x00000a18  /* Deep Standby Interrupt Flag Register 0 */
#define R_SYSTEM_DPSIFR1_OFFSET                   0x00000a1c  /* Deep Standby Interrupt Flag Register 1 */
#define R_SYSTEM_DPSIFR2_OFFSET                   0x00000a20  /* Deep Standby Interrupt Flag Register 2 */
#define R_SYSTEM_DPSIFR3_OFFSET                   0x00000a24  /* Deep Standby Interrupt Flag Register 3 */
#define R_SYSTEM_DPSIEGR0_OFFSET                  0x00000a28  /* Deep Standby Interrupt Edge Register 0 */
#define R_SYSTEM_DPSIEGR1_OFFSET                  0x00000a2c  /* Deep Standby Interrupt Edge Register 1 */
#define R_SYSTEM_DPSIEGR2_OFFSET                  0x00000a30  /* Deep Standby Interrupt Edge Register 2 */
#define R_SYSTEM_DPSIEGR3_OFFSET                  0x00000a34  /* Deep Standby Interrupt Edge Register 3 */
#define R_SYSTEM_SYOCDCR_OFFSET                   0x00000a38  /* System Control OCD Control Register */
#define R_SYSTEM_RSTSR0_OFFSET                    0x00000a40  /* Reset Status Register 0 */
#define R_SYSTEM_RSTSR2_OFFSET                    0x00000a44  /* Reset Status Register 2 */
#define R_SYSTEM_RSTSR3_OFFSET                    0x00000a48  /* Reset Status Register 3 */
#define R_SYSTEM_MOMCR_OFFSET                     0x00000a50  /* Main Clock Oscillator Mode Oscillation Control Register */
/* LVD%sCMPCR Registers (1-5) */
#define R_SYSTEM_LVDCMPCR_OFFSET(m)               (0x00000a58 + ((m) * 0x00000004))  /* Voltage Monitoring %s Comparator Control Register */
/* LVD%sCR0 Registers (1-5) */
#define R_SYSTEM_LVDCR0_OFFSET(m)                 (0x00000a70 + ((m) * 0x00000004))  /* Voltage Monitor %s Circuit Control Register 0 */
#define R_SYSTEM_VBATTMNSELR_OFFSET               0x00000a84  /* Battery Backup Voltage Monitor Function Select Register */
#define R_SYSTEM_VBTBPCR1_OFFSET                  0x00000a88  /* VBATT Battery Power Supply Control Register 1 */
#define R_SYSTEM_LPSCR_OFFSET                     0x00000a90  /* Low Power State Control Register */
#define R_SYSTEM_SSCR1_OFFSET                     0x00000a98  /* Software Standby Control Register 1 */
#define R_SYSTEM_SVSCR_OFFSET                     0x00000a9c  /* SSTBY Voltage Scaling Control Register */
#define R_SYSTEM_LVOCR_OFFSET                     0x00000ab0  /* Low Voltage Operation Control Register */
#define R_SYSTEM_MWMCR_OFFSET                     0x00000ab4  /* MRAM-OTP Write Mode Control Register */
#define R_SYSTEM_SYRSTMSK0_OFFSET                 0x00000ad0  /* System Reset Mask Control Register 0 */
#define R_SYSTEM_SYRSTMSK1_OFFSET                 0x00000ad4  /* System Reset Mask Control Register 1 */
#define R_SYSTEM_SYRSTMSK2_OFFSET                 0x00000ad8  /* System Reset Mask Control Register 2 */
#define R_SYSTEM_TEMPRCR_OFFSET                   0x00000adc  /* Temperature Monitor Reset Control Register */
#define R_SYSTEM_TEMPRLR_OFFSET                   0x00000ae0  /* Temperature Monitor Reset Lock Register */
#define R_SYSTEM_LDOSCR_OFFSET                    0x00000b00  /* LDO Stop Control Register */
/* PLL%sLDOCR Registers (1-2) */
#define R_SYSTEM_PLLLDOCR_OFFSET(m)               (0x00000b04 + ((m) * 0x00000004))  /* PLL%s-LDO Stop Control Register */
#define R_SYSTEM_HOCOLDOCR_OFFSET                 0x00000b0c  /* HOCO-LDO Control Register */
#define R_SYSTEM_MOMCR2_OFFSET                    0x00000b10  /* Main Clock Oscillator Mode Oscillation Control Register 2 */
/* LVD%sFCR Registers (1-5) */
#define R_SYSTEM_LVDFCR_OFFSET(m)                 (0x00000b20 + ((m) * 0x00000004))  /* Voltage Monitor %s Function Control Register */
#define R_SYSTEM_PVDLR_OFFSET                     0x00000b34  /* Voltage Monitor Lock Register */
#define R_SYSTEM_DPSIER4_OFFSET                   0x00000b40  /* Deep Standby Interrupt Enable Register 4 */
#define R_SYSTEM_DPSIER5_OFFSET                   0x00000b44  /* Deep Standby Interrupt Enable Register 5 */
#define R_SYSTEM_DPSIFR4_OFFSET                   0x00000b48  /* Deep Standby Interrupt Flag Register 4 */
#define R_SYSTEM_DPSIFR5_OFFSET                   0x00000b4c  /* Deep Standby Interrupt Flag Register 5 */
#define R_SYSTEM_DPSIEGR4_OFFSET                  0x00000b50  /* Deep Standby Interrupt Edge Register 4 */
#define R_SYSTEM_VBTSWMON_OFFSET                  0x00000b60  /* LVDVBATSW control Monitor Register */
#define R_SYSTEM_VBTSWSCR_OFFSET                  0x00000b64  /* LVDVBATSW Start-up stable wait Control Register */
#define R_SYSTEM_SOSCCR_OFFSET                    0x00000c00  /* Sub-Clock Oscillator Control Register */
#define R_SYSTEM_SOMCR_OFFSET                     0x00000c01  /* Sub Clock Oscillator Mode Control Register */
#define R_SYSTEM_SOSTDCR _OFFSET                  0x00000c04  /* Sub-clock Oscillation Stop Detection Control Register */
#define R_SYSTEM_SOSTDSR _OFFSET                  0x00000c05  /* Sub-clock Oscillation Stop Detection Status Register */
#define R_SYSTEM_VBTBER_OFFSET                    0x00000c40  /* VBATT Backup Enable Register */
#define R_SYSTEM_VBTBPCR2_OFFSET                  0x00000c45  /* VBATT Battery Power Supply Control Register 2 */
#define R_SYSTEM_VBTBPSR_OFFSET                   0x00000c46  /* VBATT Battery Power Supply Status Register */
#define R_SYSTEM_VBTADSR_OFFSET                   0x00000c48  /* VBATT Tamper detection Status Register */
#define R_SYSTEM_VBTADCR1_OFFSET                  0x00000c49  /* VBATT Tamper detection Control  Register 1 */
#define R_SYSTEM_VBTADCR2_OFFSET                  0x00000c4a  /* VBATT Tamper detection Control  Register 2 */
#define R_SYSTEM_VBTICTLR_OFFSET                  0x00000c4c  /* VBATT Input Control Register */
#define R_SYSTEM_VBTICTLR2_OFFSET                 0x00000c4d  /* VBATT Input Control Register 2 */
#define R_SYSTEM_VBTIMONR_OFFSET                  0x00000c4e  /* VBATT Input Monitor Register */
#define R_SYSTEM_VBTNCWCR_OFFSET                  0x00000c50  /* VBATT Noise Canceler Width Control Register */
#define R_SYSTEM_VBTADCR3_OFFSET                  0x00000c54  /* VBATT Tamper detection Control Register 3 */
/* VBTBKR[%s] Registers () */
#define R_SYSTEM_VBTBKR_OFFSET(m)                 (0x00000d00 + ((m) * 0x00000001))  /* VBATT Backup Register [%s] */

/* SYSTEM Register Addresses */

#define R_SYSTEM_SBYCR                            (R_SYSTEM_BASE + R_SYSTEM_SBYCR_OFFSET)
#define R_SYSTEM_SSCR2                            (R_SYSTEM_BASE + R_SYSTEM_SSCR2_OFFSET)
#define R_SYSTEM_MRSCR                            (R_SYSTEM_BASE + R_SYSTEM_MRSCR_OFFSET)
#define R_SYSTEM_VSCR                             (R_SYSTEM_BASE + R_SYSTEM_VSCR_OFFSET)
#define R_SYSTEM_SRMONR                           (R_SYSTEM_BASE + R_SYSTEM_SRMONR_OFFSET)
#define R_SYSTEM_SCKDIVCR                         (R_SYSTEM_BASE + R_SYSTEM_SCKDIVCR_OFFSET)
#define R_SYSTEM_SCKDIVCR2                        (R_SYSTEM_BASE + R_SYSTEM_SCKDIVCR2_OFFSET)
#define R_SYSTEM_SCKSCR                           (R_SYSTEM_BASE + R_SYSTEM_SCKSCR_OFFSET)
#define R_SYSTEM_PLLCR                            (R_SYSTEM_BASE + R_SYSTEM_PLLCR_OFFSET)
#define R_SYSTEM_BCKCR                            (R_SYSTEM_BASE + R_SYSTEM_BCKCR_OFFSET)
#define R_SYSTEM_MEMWAIT                          (R_SYSTEM_BASE + R_SYSTEM_MEMWAIT_OFFSET)
#define R_SYSTEM_MOSCCR                           (R_SYSTEM_BASE + R_SYSTEM_MOSCCR_OFFSET)
#define R_SYSTEM_HOCOCR                           (R_SYSTEM_BASE + R_SYSTEM_HOCOCR_OFFSET)
#define R_SYSTEM_MOCOCR                           (R_SYSTEM_BASE + R_SYSTEM_MOCOCR_OFFSET)
#define R_SYSTEM_FLLCR1                           (R_SYSTEM_BASE + R_SYSTEM_FLLCR1_OFFSET)
#define R_SYSTEM_FLLCR2                           (R_SYSTEM_BASE + R_SYSTEM_FLLCR2_OFFSET)
#define R_SYSTEM_OSCSF                            (R_SYSTEM_BASE + R_SYSTEM_OSCSF_OFFSET)
#define R_SYSTEM_CKOCR                            (R_SYSTEM_BASE + R_SYSTEM_CKOCR_OFFSET)
#define R_SYSTEM_TRCKCR                           (R_SYSTEM_BASE + R_SYSTEM_TRCKCR_OFFSET)
#define R_SYSTEM_OSTDCR                           (R_SYSTEM_BASE + R_SYSTEM_OSTDCR_OFFSET)
#define R_SYSTEM_OSTDSR                           (R_SYSTEM_BASE + R_SYSTEM_OSTDSR_OFFSET)
#define R_SYSTEM_OSCMONR                          (R_SYSTEM_BASE + R_SYSTEM_OSCMONR_OFFSET)
#define R_SYSTEM_PLL2CR                           (R_SYSTEM_BASE + R_SYSTEM_PLL2CR_OFFSET)
#define R_SYSTEM_PLLCCR2                          (R_SYSTEM_BASE + R_SYSTEM_PLLCCR2_OFFSET)
#define R_SYSTEM_LPOPT                            (R_SYSTEM_BASE + R_SYSTEM_LPOPT_OFFSET)
#define R_SYSTEM_PLL2CCR2                         (R_SYSTEM_BASE + R_SYSTEM_PLL2CCR2_OFFSET)
#define R_SYSTEM_SLCDSCKCR                        (R_SYSTEM_BASE + R_SYSTEM_SLCDSCKCR_OFFSET)
#define R_SYSTEM_EBCKOCR                          (R_SYSTEM_BASE + R_SYSTEM_EBCKOCR_OFFSET)
#define R_SYSTEM_SDCKOCR                          (R_SYSTEM_BASE + R_SYSTEM_SDCKOCR_OFFSET)
#define R_SYSTEM_SCICKDIVCR                       (R_SYSTEM_BASE + R_SYSTEM_SCICKDIVCR_OFFSET)
#define R_SYSTEM_SCICKCR                          (R_SYSTEM_BASE + R_SYSTEM_SCICKCR_OFFSET)
#define R_SYSTEM_SPICKDIVCR                       (R_SYSTEM_BASE + R_SYSTEM_SPICKDIVCR_OFFSET)
#define R_SYSTEM_SPICKCR                          (R_SYSTEM_BASE + R_SYSTEM_SPICKCR_OFFSET)
#define R_SYSTEM_ADCCKDIVCR                       (R_SYSTEM_BASE + R_SYSTEM_ADCCKDIVCR_OFFSET)
#define R_SYSTEM_ADCCKCR                          (R_SYSTEM_BASE + R_SYSTEM_ADCCKCR_OFFSET)
#define R_SYSTEM_GPTCKDIVCR                       (R_SYSTEM_BASE + R_SYSTEM_GPTCKDIVCR_OFFSET)
#define R_SYSTEM_GPTCKCR                          (R_SYSTEM_BASE + R_SYSTEM_GPTCKCR_OFFSET)
#define R_SYSTEM_LCDCKDIVCR                       (R_SYSTEM_BASE + R_SYSTEM_LCDCKDIVCR_OFFSET)
#define R_SYSTEM_LCDCKCR                          (R_SYSTEM_BASE + R_SYSTEM_LCDCKCR_OFFSET)
#define R_SYSTEM_MOCOUTCR                         (R_SYSTEM_BASE + R_SYSTEM_MOCOUTCR_OFFSET)
#define R_SYSTEM_HOCOUTCR                         (R_SYSTEM_BASE + R_SYSTEM_HOCOUTCR_OFFSET)
#define R_SYSTEM_USBCKDIVCR                       (R_SYSTEM_BASE + R_SYSTEM_USBCKDIVCR_OFFSET)
#define R_SYSTEM_OCTACKDIVCR                      (R_SYSTEM_BASE + R_SYSTEM_OCTACKDIVCR_OFFSET)
#define R_SYSTEM_CANFDCKDIVCR                     (R_SYSTEM_BASE + R_SYSTEM_CANFDCKDIVCR_OFFSET)
#define R_SYSTEM_USB60CKDIVCR                     (R_SYSTEM_BASE + R_SYSTEM_USB60CKDIVCR_OFFSET)
#define R_SYSTEM_I3CCKDIVCR                       (R_SYSTEM_BASE + R_SYSTEM_I3CCKDIVCR_OFFSET)
#define R_SYSTEM_USBCKCR                          (R_SYSTEM_BASE + R_SYSTEM_USBCKCR_OFFSET)
#define R_SYSTEM_OCTACKCR                         (R_SYSTEM_BASE + R_SYSTEM_OCTACKCR_OFFSET)
#define R_SYSTEM_CANFDCKCR                        (R_SYSTEM_BASE + R_SYSTEM_CANFDCKCR_OFFSET)
#define R_SYSTEM_USB60CKCR                        (R_SYSTEM_BASE + R_SYSTEM_USB60CKCR_OFFSET)
#define R_SYSTEM_I3CCKCR                          (R_SYSTEM_BASE + R_SYSTEM_I3CCKCR_OFFSET)
#define R_SYSTEM_MOSCSCR                          (R_SYSTEM_BASE + R_SYSTEM_MOSCSCR_OFFSET)
#define R_SYSTEM_HOCOSCR                          (R_SYSTEM_BASE + R_SYSTEM_HOCOSCR_OFFSET)
#define R_SYSTEM_MOCOSCR                          (R_SYSTEM_BASE + R_SYSTEM_MOCOSCR_OFFSET)
#define R_SYSTEM_FLSTOP                           (R_SYSTEM_BASE + R_SYSTEM_FLSTOP_OFFSET)
#define R_SYSTEM_PSMCR                            (R_SYSTEM_BASE + R_SYSTEM_PSMCR_OFFSET)
#define R_SYSTEM_OPCCR                            (R_SYSTEM_BASE + R_SYSTEM_OPCCR_OFFSET)
#define R_SYSTEM_MOSCWTCR                         (R_SYSTEM_BASE + R_SYSTEM_MOSCWTCR_OFFSET)
#define R_SYSTEM_HOCOWTCR                         (R_SYSTEM_BASE + R_SYSTEM_HOCOWTCR_OFFSET)
#define R_SYSTEM_SOPCCR                           (R_SYSTEM_BASE + R_SYSTEM_SOPCCR_OFFSET)
#define R_SYSTEM_PLLCCR                           (R_SYSTEM_BASE + R_SYSTEM_PLLCCR_OFFSET)
#define R_SYSTEM_RSTSR1                           (R_SYSTEM_BASE + R_SYSTEM_RSTSR1_OFFSET)
#define R_SYSTEM_PLL2CCR                          (R_SYSTEM_BASE + R_SYSTEM_PLL2CCR_OFFSET)
#define R_SYSTEM_SYRACCR                          (R_SYSTEM_BASE + R_SYSTEM_SYRACCR_OFFSET)
#define R_SYSTEM_USBCKCR_ALT                      (R_SYSTEM_BASE + R_SYSTEM_USBCKCR_ALT_OFFSET)
#define R_SYSTEM_SDADCCKCR                        (R_SYSTEM_BASE + R_SYSTEM_SDADCCKCR_OFFSET)
#define R_SYSTEM_BCKADIVCR                        (R_SYSTEM_BASE + R_SYSTEM_BCKADIVCR_OFFSET)
#define R_SYSTEM_ESWCKDIVCR                       (R_SYSTEM_BASE + R_SYSTEM_ESWCKDIVCR_OFFSET)
#define R_SYSTEM_ESWPCKDIVCR                      (R_SYSTEM_BASE + R_SYSTEM_ESWPCKDIVCR_OFFSET)
#define R_SYSTEM_ESCCKDIVCR                       (R_SYSTEM_BASE + R_SYSTEM_ESCCKDIVCR_OFFSET)
#define R_SYSTEM_ETHPCKDIVCR                      (R_SYSTEM_BASE + R_SYSTEM_ETHPCKDIVCR_OFFSET)
#define R_SYSTEM_BCKACR                           (R_SYSTEM_BASE + R_SYSTEM_BCKACR_OFFSET)
#define R_SYSTEM_ESWCKCR                          (R_SYSTEM_BASE + R_SYSTEM_ESWCKCR_OFFSET)
#define R_SYSTEM_ESWPCKCR                         (R_SYSTEM_BASE + R_SYSTEM_ESWPCKCR_OFFSET)
#define R_SYSTEM_ESCCKCR                          (R_SYSTEM_BASE + R_SYSTEM_ESCCKCR_OFFSET)
#define R_SYSTEM_ETHPCKCR                         (R_SYSTEM_BASE + R_SYSTEM_ETHPCKCR_OFFSET)
#define R_SYSTEM_LVDCR1(m)                        (R_SYSTEM_BASE + R_SYSTEM_LVDCR1_OFFSET(m))
#define R_SYSTEM_LVDSR(m)                         (R_SYSTEM_BASE + R_SYSTEM_LVDSR_OFFSET(m))
#define R_SYSTEM_CRVSYSCR                         (R_SYSTEM_BASE + R_SYSTEM_CRVSYSCR_OFFSET)
#define R_SYSTEM_CPUDSCR                          (R_SYSTEM_BASE + R_SYSTEM_CPUDSCR_OFFSET)
#define R_SYSTEM_PDCTR(m)                         (R_SYSTEM_BASE + R_SYSTEM_PDCTR_OFFSET(m))
#define R_SYSTEM_PDRAMSCR0                        (R_SYSTEM_BASE + R_SYSTEM_PDRAMSCR0_OFFSET)
#define R_SYSTEM_PDRAMSCR1                        (R_SYSTEM_BASE + R_SYSTEM_PDRAMSCR1_OFFSET)
#define R_SYSTEM_VBRSABAR                         (R_SYSTEM_BASE + R_SYSTEM_VBRSABAR_OFFSET)
#define R_SYSTEM_VBRPABARS                        (R_SYSTEM_BASE + R_SYSTEM_VBRPABARS_OFFSET)
#define R_SYSTEM_VBRPABARNS                       (R_SYSTEM_BASE + R_SYSTEM_VBRPABARNS_OFFSET)
#define R_SYSTEM_CGFSAR                           (R_SYSTEM_BASE + R_SYSTEM_CGFSAR_OFFSET)
#define R_SYSTEM_RSTSAR                           (R_SYSTEM_BASE + R_SYSTEM_RSTSAR_OFFSET)
#define R_SYSTEM_LPMSAR                           (R_SYSTEM_BASE + R_SYSTEM_LPMSAR_OFFSET)
#define R_SYSTEM_LVDSAR                           (R_SYSTEM_BASE + R_SYSTEM_LVDSAR_OFFSET)
#define R_SYSTEM_BBFSAR                           (R_SYSTEM_BASE + R_SYSTEM_BBFSAR_OFFSET)
#define R_SYSTEM_PGCSAR                           (R_SYSTEM_BASE + R_SYSTEM_PGCSAR_OFFSET)
#define R_SYSTEM_DPFSAR                           (R_SYSTEM_BASE + R_SYSTEM_DPFSAR_OFFSET)
#define R_SYSTEM_RSCSAR                           (R_SYSTEM_BASE + R_SYSTEM_RSCSAR_OFFSET)
#define R_SYSTEM_DPFSAR1                          (R_SYSTEM_BASE + R_SYSTEM_DPFSAR1_OFFSET)
#define R_SYSTEM_PRCR                             (R_SYSTEM_BASE + R_SYSTEM_PRCR_OFFSET)
#define R_SYSTEM_PRCR_NS                          (R_SYSTEM_BASE + R_SYSTEM_PRCR_NS_OFFSET)
#define R_SYSTEM_LOCOCR                           (R_SYSTEM_BASE + R_SYSTEM_LOCOCR_OFFSET)
#define R_SYSTEM_LOCOUTCR                         (R_SYSTEM_BASE + R_SYSTEM_LOCOUTCR_OFFSET)
#define R_SYSTEM_STCONR                           (R_SYSTEM_BASE + R_SYSTEM_STCONR_OFFSET)
#define R_SYSTEM_FWEPROR                          (R_SYSTEM_BASE + R_SYSTEM_FWEPROR_OFFSET)
#define R_SYSTEM_VBATTMONR                        (R_SYSTEM_BASE + R_SYSTEM_VBATTMONR_OFFSET)
#define R_SYSTEM_VBTCR1                           (R_SYSTEM_BASE + R_SYSTEM_VBTCR1_OFFSET)
#define R_SYSTEM_DCDCCTL                          (R_SYSTEM_BASE + R_SYSTEM_DCDCCTL_OFFSET)
#define R_SYSTEM_VCCSEL                           (R_SYSTEM_BASE + R_SYSTEM_VCCSEL_OFFSET)
#define R_SYSTEM_SOMRG                            (R_SYSTEM_BASE + R_SYSTEM_SOMRG_OFFSET)
#define R_SYSTEM_VBTCR2                           (R_SYSTEM_BASE + R_SYSTEM_VBTCR2_OFFSET)
#define R_SYSTEM_VBTSR                            (R_SYSTEM_BASE + R_SYSTEM_VBTSR_OFFSET)
#define R_SYSTEM_VBTCMPCR                         (R_SYSTEM_BASE + R_SYSTEM_VBTCMPCR_OFFSET)
#define R_SYSTEM_VBTLVDICR                        (R_SYSTEM_BASE + R_SYSTEM_VBTLVDICR_OFFSET)
#define R_SYSTEM_VBTWCTLR                         (R_SYSTEM_BASE + R_SYSTEM_VBTWCTLR_OFFSET)
#define R_SYSTEM_VBTWCH0OTSR                      (R_SYSTEM_BASE + R_SYSTEM_VBTWCH0OTSR_OFFSET)
#define R_SYSTEM_VBTWCH1OTSR                      (R_SYSTEM_BASE + R_SYSTEM_VBTWCH1OTSR_OFFSET)
#define R_SYSTEM_VBTWCH2OTSR                      (R_SYSTEM_BASE + R_SYSTEM_VBTWCH2OTSR_OFFSET)
#define R_SYSTEM_VBTOCTLR                         (R_SYSTEM_BASE + R_SYSTEM_VBTOCTLR_OFFSET)
#define R_SYSTEM_VBTWTER                          (R_SYSTEM_BASE + R_SYSTEM_VBTWTER_OFFSET)
#define R_SYSTEM_VBTWEGR                          (R_SYSTEM_BASE + R_SYSTEM_VBTWEGR_OFFSET)
#define R_SYSTEM_VBTWFR                           (R_SYSTEM_BASE + R_SYSTEM_VBTWFR_OFFSET)
#define R_SYSTEM_DPSBYCR                          (R_SYSTEM_BASE + R_SYSTEM_DPSBYCR_OFFSET)
#define R_SYSTEM_DPSIER0                          (R_SYSTEM_BASE + R_SYSTEM_DPSIER0_OFFSET)
#define R_SYSTEM_DPSIER1                          (R_SYSTEM_BASE + R_SYSTEM_DPSIER1_OFFSET)
#define R_SYSTEM_DPSIER2                          (R_SYSTEM_BASE + R_SYSTEM_DPSIER2_OFFSET)
#define R_SYSTEM_DPSIER3                          (R_SYSTEM_BASE + R_SYSTEM_DPSIER3_OFFSET)
#define R_SYSTEM_DPSIFR0                          (R_SYSTEM_BASE + R_SYSTEM_DPSIFR0_OFFSET)
#define R_SYSTEM_DPSIFR1                          (R_SYSTEM_BASE + R_SYSTEM_DPSIFR1_OFFSET)
#define R_SYSTEM_DPSIFR2                          (R_SYSTEM_BASE + R_SYSTEM_DPSIFR2_OFFSET)
#define R_SYSTEM_DPSIFR3                          (R_SYSTEM_BASE + R_SYSTEM_DPSIFR3_OFFSET)
#define R_SYSTEM_DPSIEGR0                         (R_SYSTEM_BASE + R_SYSTEM_DPSIEGR0_OFFSET)
#define R_SYSTEM_DPSIEGR1                         (R_SYSTEM_BASE + R_SYSTEM_DPSIEGR1_OFFSET)
#define R_SYSTEM_DPSIEGR2                         (R_SYSTEM_BASE + R_SYSTEM_DPSIEGR2_OFFSET)
#define R_SYSTEM_DPSIEGR3                         (R_SYSTEM_BASE + R_SYSTEM_DPSIEGR3_OFFSET)
#define R_SYSTEM_SYOCDCR                          (R_SYSTEM_BASE + R_SYSTEM_SYOCDCR_OFFSET)
#define R_SYSTEM_RSTSR0                           (R_SYSTEM_BASE + R_SYSTEM_RSTSR0_OFFSET)
#define R_SYSTEM_RSTSR2                           (R_SYSTEM_BASE + R_SYSTEM_RSTSR2_OFFSET)
#define R_SYSTEM_RSTSR3                           (R_SYSTEM_BASE + R_SYSTEM_RSTSR3_OFFSET)
#define R_SYSTEM_MOMCR                            (R_SYSTEM_BASE + R_SYSTEM_MOMCR_OFFSET)
#define R_SYSTEM_LVDCMPCR(m)                      (R_SYSTEM_BASE + R_SYSTEM_LVDCMPCR_OFFSET(m))
#define R_SYSTEM_LVDCR0(m)                        (R_SYSTEM_BASE + R_SYSTEM_LVDCR0_OFFSET(m))
#define R_SYSTEM_VBATTMNSELR                      (R_SYSTEM_BASE + R_SYSTEM_VBATTMNSELR_OFFSET)
#define R_SYSTEM_VBTBPCR1                         (R_SYSTEM_BASE + R_SYSTEM_VBTBPCR1_OFFSET)
#define R_SYSTEM_LPSCR                            (R_SYSTEM_BASE + R_SYSTEM_LPSCR_OFFSET)
#define R_SYSTEM_SSCR1                            (R_SYSTEM_BASE + R_SYSTEM_SSCR1_OFFSET)
#define R_SYSTEM_SVSCR                            (R_SYSTEM_BASE + R_SYSTEM_SVSCR_OFFSET)
#define R_SYSTEM_LVOCR                            (R_SYSTEM_BASE + R_SYSTEM_LVOCR_OFFSET)
#define R_SYSTEM_MWMCR                            (R_SYSTEM_BASE + R_SYSTEM_MWMCR_OFFSET)
#define R_SYSTEM_SYRSTMSK0                        (R_SYSTEM_BASE + R_SYSTEM_SYRSTMSK0_OFFSET)
#define R_SYSTEM_SYRSTMSK1                        (R_SYSTEM_BASE + R_SYSTEM_SYRSTMSK1_OFFSET)
#define R_SYSTEM_SYRSTMSK2                        (R_SYSTEM_BASE + R_SYSTEM_SYRSTMSK2_OFFSET)
#define R_SYSTEM_TEMPRCR                          (R_SYSTEM_BASE + R_SYSTEM_TEMPRCR_OFFSET)
#define R_SYSTEM_TEMPRLR                          (R_SYSTEM_BASE + R_SYSTEM_TEMPRLR_OFFSET)
#define R_SYSTEM_LDOSCR                           (R_SYSTEM_BASE + R_SYSTEM_LDOSCR_OFFSET)
#define R_SYSTEM_PLLLDOCR(m)                      (R_SYSTEM_BASE + R_SYSTEM_PLLLDOCR_OFFSET(m))
#define R_SYSTEM_HOCOLDOCR                        (R_SYSTEM_BASE + R_SYSTEM_HOCOLDOCR_OFFSET)
#define R_SYSTEM_MOMCR2                           (R_SYSTEM_BASE + R_SYSTEM_MOMCR2_OFFSET)
#define R_SYSTEM_LVDFCR(m)                        (R_SYSTEM_BASE + R_SYSTEM_LVDFCR_OFFSET(m))
#define R_SYSTEM_PVDLR                            (R_SYSTEM_BASE + R_SYSTEM_PVDLR_OFFSET)
#define R_SYSTEM_DPSIER4                          (R_SYSTEM_BASE + R_SYSTEM_DPSIER4_OFFSET)
#define R_SYSTEM_DPSIER5                          (R_SYSTEM_BASE + R_SYSTEM_DPSIER5_OFFSET)
#define R_SYSTEM_DPSIFR4                          (R_SYSTEM_BASE + R_SYSTEM_DPSIFR4_OFFSET)
#define R_SYSTEM_DPSIFR5                          (R_SYSTEM_BASE + R_SYSTEM_DPSIFR5_OFFSET)
#define R_SYSTEM_DPSIEGR4                         (R_SYSTEM_BASE + R_SYSTEM_DPSIEGR4_OFFSET)
#define R_SYSTEM_VBTSWMON                         (R_SYSTEM_BASE + R_SYSTEM_VBTSWMON_OFFSET)
#define R_SYSTEM_VBTSWSCR                         (R_SYSTEM_BASE + R_SYSTEM_VBTSWSCR_OFFSET)
#define R_SYSTEM_SOSCCR                           (R_SYSTEM_BASE + R_SYSTEM_SOSCCR_OFFSET)
#define R_SYSTEM_SOMCR                            (R_SYSTEM_BASE + R_SYSTEM_SOMCR_OFFSET)
#define R_SYSTEM_SOSTDCR                          (R_SYSTEM_BASE + R_SYSTEM_SOSTDCR _OFFSET)
#define R_SYSTEM_SOSTDSR                          (R_SYSTEM_BASE + R_SYSTEM_SOSTDSR _OFFSET)
#define R_SYSTEM_VBTBER                           (R_SYSTEM_BASE + R_SYSTEM_VBTBER_OFFSET)
#define R_SYSTEM_VBTBPCR2                         (R_SYSTEM_BASE + R_SYSTEM_VBTBPCR2_OFFSET)
#define R_SYSTEM_VBTBPSR                          (R_SYSTEM_BASE + R_SYSTEM_VBTBPSR_OFFSET)
#define R_SYSTEM_VBTADSR                          (R_SYSTEM_BASE + R_SYSTEM_VBTADSR_OFFSET)
#define R_SYSTEM_VBTADCR1                         (R_SYSTEM_BASE + R_SYSTEM_VBTADCR1_OFFSET)
#define R_SYSTEM_VBTADCR2                         (R_SYSTEM_BASE + R_SYSTEM_VBTADCR2_OFFSET)
#define R_SYSTEM_VBTICTLR                         (R_SYSTEM_BASE + R_SYSTEM_VBTICTLR_OFFSET)
#define R_SYSTEM_VBTICTLR2                        (R_SYSTEM_BASE + R_SYSTEM_VBTICTLR2_OFFSET)
#define R_SYSTEM_VBTIMONR                         (R_SYSTEM_BASE + R_SYSTEM_VBTIMONR_OFFSET)
#define R_SYSTEM_VBTNCWCR                         (R_SYSTEM_BASE + R_SYSTEM_VBTNCWCR_OFFSET)
#define R_SYSTEM_VBTADCR3                         (R_SYSTEM_BASE + R_SYSTEM_VBTADCR3_OFFSET)
#define R_SYSTEM_VBTBKR(m)                        (R_SYSTEM_BASE + R_SYSTEM_VBTBKR_OFFSET(m))

/* Register bit definitions */
/* SBYCR Register bit definitions */
#define R_SYSTEM_SBYCR_OPE                        (1 << 6)  /* Output Port Enable */

/* SSCR2 Register bit definitions */
#define R_SYSTEM_SSCR2_SS2FSR                     (1 << 0)  /* Software Standby 2 Fast Return */

/* MRSCR Register bit definitions */
#define R_SYSTEM_MRSCR_MRSWCF                     (1 << 0)  /* MRAM Stabilization wait completion flag */

/* VSCR Register bit definitions */
#define R_SYSTEM_VSCR_VSCM_SHIFT                  (0)  /* Voltage Scaling Control Mode */
#define R_SYSTEM_VSCR_VSCM_MASK                   0x7

#define R_SYSTEM_VSCR_VSCMTSF                     (1 << 4)  /* Voltage Scaling Control Mode Transition Status Flag */

/* SRMONR Register bit definitions */
#define R_SYSTEM_SRMONR_MON_SHIFT                 (0)  /* SRAM Voltage Monitor */
#define R_SYSTEM_SRMONR_MON_MASK                  0x3

/* SCKDIVCR Register bit definitions */
#define R_SYSTEM_SCKDIVCR_PCKD_SHIFT              (0)  /* Peripheral Module Clock D (PCLKD) Select  */
#define R_SYSTEM_SCKDIVCR_PCKD_MASK               0xf

#define R_SYSTEM_SCKDIVCR_PCKC_SHIFT              (4)  /* Peripheral Module Clock C (PCLKC) Select */
#define R_SYSTEM_SCKDIVCR_PCKC_MASK               0xf0

#define R_SYSTEM_SCKDIVCR_PCKB_SHIFT              (8)  /* Peripheral Module Clock B (PCLKB) Select */
#define R_SYSTEM_SCKDIVCR_PCKB_MASK               0xf00

#define R_SYSTEM_SCKDIVCR_PCKA_SHIFT              (12)  /* Peripheral Module Clock A (PCLKA) Select  */
#define R_SYSTEM_SCKDIVCR_PCKA_MASK               0xf000

#define R_SYSTEM_SCKDIVCR_BCK_SHIFT               (16)  /* External Bus Clock (BCLK) Select */
#define R_SYSTEM_SCKDIVCR_BCK_MASK                0xf0000

#define R_SYSTEM_SCKDIVCR_PCKE_SHIFT              (20)  /* Peripheral Module Clock E (PCLKE) Select */
#define R_SYSTEM_SCKDIVCR_PCKE_MASK               0xf00000

#define R_SYSTEM_SCKDIVCR_ICK_SHIFT               (24)  /* System Clock (ICLK) Select */
#define R_SYSTEM_SCKDIVCR_ICK_MASK                0xf000000

#define R_SYSTEM_SCKDIVCR_FCK_SHIFT               (28)  /* MRAM Clock (MRPCLK) Select */
#define R_SYSTEM_SCKDIVCR_FCK_MASK                0xf0000000

/* SCKDIVCR2 Register bit definitions */
#define R_SYSTEM_SCKDIVCR2_CPUCK_SHIFT            (0)  /* CPU0 Clock (CPUCLK0) Select */
#define R_SYSTEM_SCKDIVCR2_CPUCK_MASK             0xf

#define R_SYSTEM_SCKDIVCR2_CPUCK1_SHIFT           (4)  /* CPU1 Clock (CPUCLK1) Select */
#define R_SYSTEM_SCKDIVCR2_CPUCK1_MASK            0xf0

#define R_SYSTEM_SCKDIVCR2_NPUCK_SHIFT            (8)  /* NPU Clock (NPUCLK) Select */
#define R_SYSTEM_SCKDIVCR2_NPUCK_MASK             0xf00

#define R_SYSTEM_SCKDIVCR2_MRICK_SHIFT            (12)  /* MRAM bus Clock (MRICLK) Select */
#define R_SYSTEM_SCKDIVCR2_MRICK_MASK             0xf000

/* SCKSCR Register bit definitions */
#define R_SYSTEM_SCKSCR_CKSEL_SHIFT               (0)  /* Clock Source Select */
#define R_SYSTEM_SCKSCR_CKSEL_MASK                0x7
#  define R_SYSTEM_SCKSCR_CKSEL_000                       (0 << R_SYSTEM_SCKSCR_CKSEL_SHIFT)  /* HOCO  */
#  define R_SYSTEM_SCKSCR_CKSEL_001                       (1 << R_SYSTEM_SCKSCR_CKSEL_SHIFT)  /* MOCO */
#  define R_SYSTEM_SCKSCR_CKSEL_010                       (2 << R_SYSTEM_SCKSCR_CKSEL_SHIFT)  /* LOCO  */
#  define R_SYSTEM_SCKSCR_CKSEL_011                       (3 << R_SYSTEM_SCKSCR_CKSEL_SHIFT)  /* Main clock oscillator  */
#  define R_SYSTEM_SCKSCR_CKSEL_100                       (4 << R_SYSTEM_SCKSCR_CKSEL_SHIFT)  /* Sub-clock oscillator  */
#  define R_SYSTEM_SCKSCR_CKSEL_101                       (5 << R_SYSTEM_SCKSCR_CKSEL_SHIFT)  /* PLL */

/* PLLCR Register bit definitions */
#define R_SYSTEM_PLLCR_PLLSTP                     (1 << 0)  /* PLL1 Stop Control */

/* BCKCR Register bit definitions */
#define R_SYSTEM_BCKCR_BCLKDIV                    (1 << 0)  /* BCLK Pin Output Select */

#define R_SYSTEM_BCKCR_EBCKASEL                   (1 << 7)  /* External Bus Asynchronous Select */

/* MEMWAIT Register bit definitions */
#define R_SYSTEM_MEMWAIT_MEMWAIT                  (1 << 0)  /* Memory Wait Cycle SelectNote: Writing 0 to the MEMWAIT is prohibited when SCKDIVCR.ICK selects division by 1 and SCKSCR.CKSEL[2:0] bits select thesystem clock source that is faster than 32 MHz (ICLK > 32 MHz). */

/* MOSCCR Register bit definitions */
#define R_SYSTEM_MOSCCR_MOSTP                     (1 << 0)  /* Main Clock Oscillator Stop */

/* HOCOCR Register bit definitions */
#define R_SYSTEM_HOCOCR_HCSTP                     (1 << 0)  /* HOCO Stop */

/* MOCOCR Register bit definitions */
#define R_SYSTEM_MOCOCR_MCSTP                     (1 << 0)  /* MOCO Stop */

/* FLLCR1 Register bit definitions */
#define R_SYSTEM_FLLCR1_FLLEN                     (1 << 0)  /* FLL Enable */

/* FLLCR2 Register bit definitions */
#define R_SYSTEM_FLLCR2_FLLCNTL_SHIFT             (0)  /* FLL Multiplication Control */
#define R_SYSTEM_FLLCR2_FLLCNTL_MASK              0x7ff

/* OSCSF Register bit definitions */
#define R_SYSTEM_OSCSF_HOCOSF                     (1 << 0)  /* HOCO Clock Oscillation Stabilization FlagNOTE: The HOCOSF bit value after a reset is 1 when the OFS1.HOCOEN bit is 0. It is 0 when the OFS1.HOCOEN bit is 1. */

#define R_SYSTEM_OSCSF_MOSCSF                     (1 << 3)  /* Main Clock Oscillation Stabilization Flag */

#define R_SYSTEM_OSCSF_PLLSF                      (1 << 5)  /* PLL1 Clock Oscillation Stabilization Flag */

#define R_SYSTEM_OSCSF_PLL2SF                     (1 << 6)  /* PLL2 Clock Oscillation Stabilization Flag */

/* CKOCR Register bit definitions */
#define R_SYSTEM_CKOCR_CKOSEL_SHIFT               (0)  /* Clock Out source select */
#define R_SYSTEM_CKOCR_CKOSEL_MASK                0x7
#  define R_SYSTEM_CKOCR_CKOSEL_000                       (0 << R_SYSTEM_CKOCR_CKOSEL_SHIFT)  /* HOCO */
#  define R_SYSTEM_CKOCR_CKOSEL_001                       (1 << R_SYSTEM_CKOCR_CKOSEL_SHIFT)  /* MOCO (Value after reset) */
#  define R_SYSTEM_CKOCR_CKOSEL_010                       (2 << R_SYSTEM_CKOCR_CKOSEL_SHIFT)  /* LOCO */
#  define R_SYSTEM_CKOCR_CKOSEL_011                       (3 << R_SYSTEM_CKOCR_CKOSEL_SHIFT)  /* MOSC */
#  define R_SYSTEM_CKOCR_CKOSEL_100                       (4 << R_SYSTEM_CKOCR_CKOSEL_SHIFT)  /* SOSC */

#define R_SYSTEM_CKOCR_CKODIV_SHIFT               (4)  /* Clock out input frequency Division Select */
#define R_SYSTEM_CKOCR_CKODIV_MASK                0x70

#define R_SYSTEM_CKOCR_CKOEN                      (1 << 7)  /* Clock out enable */

/* TRCKCR Register bit definitions */
#define R_SYSTEM_TRCKCR_TRCK_SHIFT                (0)  /* Trace Clock operating frequency select */
#define R_SYSTEM_TRCKCR_TRCK_MASK                 0xf

#define R_SYSTEM_TRCKCR_TRCKSEL                   (1 << 4)  /* Trace Clock Control Register */

#define R_SYSTEM_TRCKCR_TRCKEN                    (1 << 7)  /* Trace Clock operating Enable */

/* OSTDCR Register bit definitions */
#define R_SYSTEM_OSTDCR_OSTDIE                    (1 << 0)  /* Oscillation Stop Detection Interrupt Enable */

#define R_SYSTEM_OSTDCR_OSTDE                     (1 << 7)  /* Oscillation Stop Detection Function Enable */

/* OSTDSR Register bit definitions */
#define R_SYSTEM_OSTDSR_OSTDF                     (1 << 0)  /* Oscillation Stop Detection Flag */

/* OSCMONR Register bit definitions */
#define R_SYSTEM_OSCMONR_MOCOMON                  (1 << 1)  /* MOCO operation monitor */

#define R_SYSTEM_OSCMONR_LOCOMON                  (1 << 2)  /* LOCO operation monitor */

/* PLL2CR Register bit definitions */
#define R_SYSTEM_PLL2CR_PLL2STP                   (1 << 0)  /* PLL2 Stop Control */

/* PLLCCR2 Register bit definitions */
#define R_SYSTEM_PLLCCR2_PLODIVP_SHIFT            (0)  /* PLL1 Output Frequency Division Ratio Select for output clock P */
#define R_SYSTEM_PLLCCR2_PLODIVP_MASK             0xf

#define R_SYSTEM_PLLCCR2_PLODIVQ_SHIFT            (4)  /* PLL1 Output Frequency Division Ratio Select for output clock Q */
#define R_SYSTEM_PLLCCR2_PLODIVQ_MASK             0xf0

#define R_SYSTEM_PLLCCR2_PLODIVR_SHIFT            (8)  /* PLL1 Output Frequency Division Ratio Select for output clock R */
#define R_SYSTEM_PLLCCR2_PLODIVR_MASK             0xf00

/* LPOPT Register bit definitions */
#define R_SYSTEM_LPOPT_MPUDIS                     (1 << 0)  /* MPU Clock Disable Control. Stop the MPU operate clock (valid only when LPOPTEN = 1) */

#define R_SYSTEM_LPOPT_DCLKDIS_SHIFT              (1)  /* Debug Clock Disable Control */
#define R_SYSTEM_LPOPT_DCLKDIS_MASK               0x6
#  define R_SYSTEM_LPOPT_DCLKDIS_00                       (0 << R_SYSTEM_LPOPT_DCLKDIS_SHIFT)  /* Debug clock does not stop */
#  define R_SYSTEM_LPOPT_DCLKDIS_01                       (1 << R_SYSTEM_LPOPT_DCLKDIS_SHIFT)  /* Debug clock stops (valid only when LPOPT.LPOPTEN = 1) */
#  define R_SYSTEM_LPOPT_DCLKDIS_10                       (2 << R_SYSTEM_LPOPT_DCLKDIS_SHIFT)  /* Debug clock stops (valid only when LPOPT.LPOPTEN = 1) */
#  define R_SYSTEM_LPOPT_DCLKDIS_11                       (3 << R_SYSTEM_LPOPT_DCLKDIS_SHIFT)  /* Debug clock stops (valid only when LPOPT.LPOPTEN = 1) */

#define R_SYSTEM_LPOPT_BPFCLKDIS                  (1 << 3)  /* BPF Clock Disable Control. Stop the Flash register R/W clock (valid only when LPOPT.LPOPTEN = 1) */

#define R_SYSTEM_LPOPT_LPOPTEN                    (1 << 7)  /* Lower Power Operation Enable */

/* PLL2CCR2 Register bit definitions */
#define R_SYSTEM_PLL2CCR2_PL2ODIVP_SHIFT          (0)  /* PLL2 Output Frequency Division Ratio Select for output clock P */
#define R_SYSTEM_PLL2CCR2_PL2ODIVP_MASK           0xf

#define R_SYSTEM_PLL2CCR2_PL2ODIVQ_SHIFT          (4)  /* PLL2 Output Frequency Division Ratio Select for output clock Q */
#define R_SYSTEM_PLL2CCR2_PL2ODIVQ_MASK           0xf0

#define R_SYSTEM_PLL2CCR2_PL2ODIVR_SHIFT          (8)  /* PLL2 Output Frequency Division Ratio Select for output clock R */
#define R_SYSTEM_PLL2CCR2_PL2ODIVR_MASK           0xf00

/* SLCDSCKCR Register bit definitions */
#define R_SYSTEM_SLCDSCKCR_LCDSCKSEL_SHIFT        (0)  /* LCD Source Clock (LCDSRCCLK) Select */
#define R_SYSTEM_SLCDSCKCR_LCDSCKSEL_MASK         0x7
#  define R_SYSTEM_SLCDSCKCR_LCDSCKSEL_000                (0 << R_SYSTEM_SLCDSCKCR_LCDSCKSEL_SHIFT)  /* LOCO */
#  define R_SYSTEM_SLCDSCKCR_LCDSCKSEL_001                (1 << R_SYSTEM_SLCDSCKCR_LCDSCKSEL_SHIFT)  /* SOSC */
#  define R_SYSTEM_SLCDSCKCR_LCDSCKSEL_010                (2 << R_SYSTEM_SLCDSCKCR_LCDSCKSEL_SHIFT)  /* MOSC */
#  define R_SYSTEM_SLCDSCKCR_LCDSCKSEL_100                (4 << R_SYSTEM_SLCDSCKCR_LCDSCKSEL_SHIFT)  /* HOCO */

#define R_SYSTEM_SLCDSCKCR_LCDSCKEN               (1 << 7)  /* LCD Source Clock Out Enable */

/* EBCKOCR Register bit definitions */
#define R_SYSTEM_EBCKOCR_EBCKOEN                  (1 << 0)  /* EBCLK Pin Output Control */

/* SDCKOCR Register bit definitions */
#define R_SYSTEM_SDCKOCR_SDCKOEN                  (1 << 0)  /* SDCLK Pin Output Control */

/* SCICKDIVCR Register bit definitions */
#define R_SYSTEM_SCICKDIVCR_CKDIV_SHIFT           (0)  /* SCI clock (SCICLK) Division Select */
#define R_SYSTEM_SCICKDIVCR_CKDIV_MASK            0xf

/* SCICKCR Register bit definitions */
#define R_SYSTEM_SCICKCR_SCICKSEL_SHIFT           (0)  /* SCI clock (SCICLK) Source Select */
#define R_SYSTEM_SCICKCR_SCICKSEL_MASK            0xf

#define R_SYSTEM_SCICKCR_CKSREQ                   (1 << 6)  /* SCI clock (SCICLK) Switching Request */

#define R_SYSTEM_SCICKCR_CKSRDY                   (1 << 7)  /* SCI clock (SCICLK) Switching Ready state flag */

/* SPICKDIVCR Register bit definitions */
#define R_SYSTEM_SPICKDIVCR_CKDIV_SHIFT           (0)  /* SPI clock (SPICLK) Division Select */
#define R_SYSTEM_SPICKDIVCR_CKDIV_MASK            0xf

/* SPICKCR Register bit definitions */
#define R_SYSTEM_SPICKCR_CKSEL_SHIFT              (0)  /* SPI clock (SPICLK) Source Select */
#define R_SYSTEM_SPICKCR_CKSEL_MASK               0xf

#define R_SYSTEM_SPICKCR_CKSREQ                   (1 << 6)  /* SPI clock (SPICLK) Switching Request */

#define R_SYSTEM_SPICKCR_CKSRDY                   (1 << 7)  /* SPI clock (SPICLK) Switching Ready state flag */

/* ADCCKDIVCR Register bit definitions */
#define R_SYSTEM_ADCCKDIVCR_CKDIV_SHIFT           (0)  /* Clock Division Select */
#define R_SYSTEM_ADCCKDIVCR_CKDIV_MASK            0xf

/* ADCCKCR Register bit definitions */
#define R_SYSTEM_ADCCKCR_CKSEL_SHIFT              (0)  /* Clock Source Select */
#define R_SYSTEM_ADCCKCR_CKSEL_MASK               0xf

#define R_SYSTEM_ADCCKCR_CKSREQ                   (1 << 6)  /* Clock Switching Request */

#define R_SYSTEM_ADCCKCR_CKSRDY                   (1 << 7)  /* Clock Switching Ready state flag */

/* GPTCKDIVCR Register bit definitions */
#define R_SYSTEM_GPTCKDIVCR_GPTCKDIV_SHIFT        (0)  /* GPT Clock (GPTCLK) Division Select */
#define R_SYSTEM_GPTCKDIVCR_GPTCKDIV_MASK         0xf

/* GPTCKCR Register bit definitions */
#define R_SYSTEM_GPTCKCR_GPTCKSEL_SHIFT           (0)  /* Clock Source Select */
#define R_SYSTEM_GPTCKCR_GPTCKSEL_MASK            0xf

#define R_SYSTEM_GPTCKCR_GPTCKSREQ                (1 << 6)  /* Clock Switching Request */

#define R_SYSTEM_GPTCKCR_GPTCKSRDY                (1 << 7)  /* Clock Switching Ready state flag */

/* LCDCKDIVCR Register bit definitions */
#define R_SYSTEM_LCDCKDIVCR_CKDIV_SHIFT           (0)  /* LCD clock (LCDCLK) Division Select */
#define R_SYSTEM_LCDCKDIVCR_CKDIV_MASK            0xf

/* LCDCKCR Register bit definitions */
#define R_SYSTEM_LCDCKCR_CKSEL_SHIFT              (0)  /* LCD clock (LCDCLK) Source Select */
#define R_SYSTEM_LCDCKCR_CKSEL_MASK               0xf

#define R_SYSTEM_LCDCKCR_CKSREQ                   (1 << 6)  /* LCD clock (LCDCLK) Switching Request */

#define R_SYSTEM_LCDCKCR_CKSRDY                   (1 << 7)  /* LCD clock (LCDCLK) Switching Ready state flag */

/* MOCOUTCR Register bit definitions */
#define R_SYSTEM_MOCOUTCR_MOCOUTRM_SHIFT          (0)  /* MOCO User Trimming */
#define R_SYSTEM_MOCOUTCR_MOCOUTRM_MASK           0xff

/* HOCOUTCR Register bit definitions */
#define R_SYSTEM_HOCOUTCR_HOCOUTRM_SHIFT          (0)  /* HOCO User Trimming */
#define R_SYSTEM_HOCOUTCR_HOCOUTRM_MASK           0xff

/* USBCKDIVCR Register bit definitions */
#define R_SYSTEM_USBCKDIVCR_USBCKDIV_SHIFT        (0)  /* USB Clock (USBCLK) Division Select */
#define R_SYSTEM_USBCKDIVCR_USBCKDIV_MASK         0xf

/* OCTACKDIVCR Register bit definitions */
#define R_SYSTEM_OCTACKDIVCR_OCTACKDIV_SHIFT      (0)  /* Octal-SPI Clock (OCTACLK) Division Select */
#define R_SYSTEM_OCTACKDIVCR_OCTACKDIV_MASK       0xf

/* CANFDCKDIVCR Register bit definitions */
#define R_SYSTEM_CANFDCKDIVCR_CANFDCKDIV_SHIFT    (0)  /* CANFD Clock (CANFDCLK) Division Select */
#define R_SYSTEM_CANFDCKDIVCR_CANFDCKDIV_MASK     0xf

/* USB60CKDIVCR Register bit definitions */
#define R_SYSTEM_USB60CKDIVCR_USB60CKDIV_SHIFT    (0)  /* USB clock (USB60CLK) Division Select */
#define R_SYSTEM_USB60CKDIVCR_USB60CKDIV_MASK     0xf

/* I3CCKDIVCR Register bit definitions */
#define R_SYSTEM_I3CCKDIVCR_I3CCKDIV_SHIFT        (0)  /* I3C clock (I3CCLK) Division Select */
#define R_SYSTEM_I3CCKDIVCR_I3CCKDIV_MASK         0xf

/* USBCKCR Register bit definitions */
#define R_SYSTEM_USBCKCR_USBCKSEL_SHIFT           (0)  /* USB Clock (USBCLK) Source Select */
#define R_SYSTEM_USBCKCR_USBCKSEL_MASK            0xf

#define R_SYSTEM_USBCKCR_USBCKSREQ                (1 << 6)  /* USB Clock (USBCLK) Switching Request */

#define R_SYSTEM_USBCKCR_USBCKSRDY                (1 << 7)  /* USB Clock (USBCLK) Switching Ready state flag */

/* OCTACKCR Register bit definitions */
#define R_SYSTEM_OCTACKCR_OCTACKSEL_SHIFT         (0)  /* Octal-SPI Clock (OCTACLK) Source Select */
#define R_SYSTEM_OCTACKCR_OCTACKSEL_MASK          0xf

#define R_SYSTEM_OCTACKCR_OCTACKSREQ              (1 << 6)  /* Octal-SPI Clock (OCTACLK) Switching Request */

#define R_SYSTEM_OCTACKCR_OCTACKSRDY              (1 << 7)  /* Octal-SPI Clock (OCTACLK) Switching Ready state flag */

/* CANFDCKCR Register bit definitions */
#define R_SYSTEM_CANFDCKCR_CANFDCKSEL_SHIFT       (0)  /* CANFD Clock (CANFDCLK) Source Select */
#define R_SYSTEM_CANFDCKCR_CANFDCKSEL_MASK        0xf

#define R_SYSTEM_CANFDCKCR_CANFDCKSREQ            (1 << 6)  /* CANFD Clock (CANFDCLK) Switching Request */

#define R_SYSTEM_CANFDCKCR_CANFDCKSRDY            (1 << 7)  /* CANFD Clock (CANFDCLK) Switching Ready state flag */

/* USB60CKCR Register bit definitions */
#define R_SYSTEM_USB60CKCR_USB60CKSEL_SHIFT       (0)  /* USB clock (USB60CLK) Source Select */
#define R_SYSTEM_USB60CKCR_USB60CKSEL_MASK        0xf

#define R_SYSTEM_USB60CKCR_USB60CKSREQ            (1 << 6)  /* USB clock (USB60CLK) Switching Request */

#define R_SYSTEM_USB60CKCR_USB60CKSRDY            (1 << 7)  /* USB clock (USB60CLK) Switching Ready state flag */

/* I3CCKCR Register bit definitions */
#define R_SYSTEM_I3CCKCR_I3CCKSEL_SHIFT           (0)  /* I3C clock (I3CCLK) source select */
#define R_SYSTEM_I3CCKCR_I3CCKSEL_MASK            0xf

#define R_SYSTEM_I3CCKCR_I3CCKSREQ                (1 << 6)  /* I3C clock (I3CCLK) switching request */

#define R_SYSTEM_I3CCKCR_I3CCKSRDY                (1 << 7)  /* I3C clock (I3CCLK) switching ready state flag */

/* MOSCSCR Register bit definitions */
#define R_SYSTEM_MOSCSCR_MOSCSOKP                 (1 << 0)  /* Main Clock Oscillator Standby Oscillation Keep select */

/* HOCOSCR Register bit definitions */
#define R_SYSTEM_HOCOSCR_HOSCSOKP                 (1 << 0)  /* HOCO Standby Oscillation Keep select */

/* MOCOSCR Register bit definitions */
#define R_SYSTEM_MOCOSCR_MOCOSOKP                 (1 << 0)  /* MOCO Standby Oscillation Keep select */

/* FLSTOP Register bit definitions */
#define R_SYSTEM_FLSTOP_FLSTOP                    (1 << 0)  /* Selecting ON/OFF of the Flash Memory Operation */

#define R_SYSTEM_FLSTOP_FLSTPF                    (1 << 4)  /* Flash Memory Operation Status Flag */

/* PSMCR Register bit definitions */
#define R_SYSTEM_PSMCR_PSMC_SHIFT                 (0)  /* Power save memory control. */
#define R_SYSTEM_PSMCR_PSMC_MASK                  0x3
#  define R_SYSTEM_PSMCR_PSMC_00                          (0 << R_SYSTEM_PSMCR_PSMC_SHIFT)  /* All RAM is on Software Standby mode. */
#  define R_SYSTEM_PSMCR_PSMC_01                          (1 << R_SYSTEM_PSMCR_PSMC_SHIFT)  /* 48KB RAM is on in Software Standby mode. */

/* OPCCR Register bit definitions */
#define R_SYSTEM_OPCCR_OPCM_SHIFT                 (0)  /* Operating Power Control Mode Select */
#define R_SYSTEM_OPCCR_OPCM_MASK                  0x3
#  define R_SYSTEM_OPCCR_OPCM_00                          (0 << R_SYSTEM_OPCCR_OPCM_SHIFT)  /* High-speed mode */
#  define R_SYSTEM_OPCCR_OPCM_01                          (1 << R_SYSTEM_OPCCR_OPCM_SHIFT)  /* Prohibited */
#  define R_SYSTEM_OPCCR_OPCM_10                          (2 << R_SYSTEM_OPCCR_OPCM_SHIFT)  /* Prohibited */
#  define R_SYSTEM_OPCCR_OPCM_11                          (3 << R_SYSTEM_OPCCR_OPCM_SHIFT)  /* Low-speed mode  */

#define R_SYSTEM_OPCCR_OPCMTSF                    (1 << 4)  /* Operating Power Control Mode Transition Status Flag */

/* MOSCWTCR Register bit definitions */
#define R_SYSTEM_MOSCWTCR_MSTS_SHIFT              (0)  /* Main clock oscillator wait time setting */
#define R_SYSTEM_MOSCWTCR_MSTS_MASK               0xf

/* HOCOWTCR Register bit definitions */
#define R_SYSTEM_HOCOWTCR_HSTS_SHIFT              (0)  /* HOCO wait time settingWaiting time (sec) = setting of the HSTS[2:0] bits/fLOCO(Trimmed) + 3/fLOC(Untrimmed)  */
#define R_SYSTEM_HOCOWTCR_HSTS_MASK               0x7

/* SOPCCR Register bit definitions */
#define R_SYSTEM_SOPCCR_SOPCM                     (1 << 0)  /* Sub Operating Power Control Mode Select */

#define R_SYSTEM_SOPCCR_SOPCMTSF                  (1 << 4)  /* Sub Operating Power Control Mode Transition Status Flag */

/* PLLCCR Register bit definitions */
#define R_SYSTEM_PLLCCR_PLIDIV_SHIFT              (0)  /* PLL1 Input Frequency Division Ratio Select */
#define R_SYSTEM_PLLCCR_PLIDIV_MASK               0x3

#define R_SYSTEM_PLLCCR_PLSRCSEL                  (1 << 4)  /* PLL1 Clock Source Select */

#define R_SYSTEM_PLLCCR_PLLMULNF_SHIFT            (6)  /* PLL1 Frequency Multiplication Fractional Factor Select */
#define R_SYSTEM_PLLCCR_PLLMULNF_MASK             0xc0

#define R_SYSTEM_PLLCCR_PLLMUL_SHIFT              (8)  /* PLL1 Frequency Multiplication Factor Select */
#define R_SYSTEM_PLLCCR_PLLMUL_MASK               0x1ff00

/* RSTSR1 Register bit definitions */
#define R_SYSTEM_RSTSR1_IWDTRF                    (1 << 0)  /* Independent Watchdog Timer Reset Detect Flag */

#define R_SYSTEM_RSTSR1_WDTRF                     (1 << 1)  /* Watchdog Timer Reset Detect Flag */

#define R_SYSTEM_RSTSR1_SWRF                      (1 << 2)  /* Software Reset Detect Flag */

#define R_SYSTEM_RSTSR1_CLURF                     (1 << 4)  /* CPU0 Lockup Reset Detect flags */

#define R_SYSTEM_RSTSR1_LM0RF                     (1 << 5)  /* Local memory 0 error Reset Detect Flag */

#define R_SYSTEM_RSTSR1_BUSSRF                    (1 << 10)  /* Bus Slave MPU Reset Detect Flag */

#define R_SYSTEM_RSTSR1_CMRF                      (1 << 14)  /* Common memory error Reset Detect Flag */

#define R_SYSTEM_RSTSR1_WDT1RF                    (1 << 17)  /* Watchdog Timer1 Reset Detect Flag */

#define R_SYSTEM_RSTSR1_CLU1RF                    (1 << 20)  /* CPU1 Lockup Reset Detect Flag */

#define R_SYSTEM_RSTSR1_LM1RF                     (1 << 21)  /* Local memory 1 error Reset Detect Flag */

#define R_SYSTEM_RSTSR1_NWRF                      (1 << 22)  /* Network Reset Detect Flag */

/* PLL2CCR Register bit definitions */
#define R_SYSTEM_PLL2CCR_PL2IDIV_SHIFT            (0)  /* PLL2 Input Frequency Division Ratio Select */
#define R_SYSTEM_PLL2CCR_PL2IDIV_MASK             0x3

#define R_SYSTEM_PLL2CCR_PL2SRCSEL                (1 << 4)  /* PLL2 Clock Source Select */

#define R_SYSTEM_PLL2CCR_PLL2MULNF_SHIFT          (6)  /* PLL2 Frequency Multiplication Fractional Factor Select */
#define R_SYSTEM_PLL2CCR_PLL2MULNF_MASK           0xc0

#define R_SYSTEM_PLL2CCR_PLL2MUL_SHIFT            (8)  /* PLL2 Frequency Multiplication Factor Select */
#define R_SYSTEM_PLL2CCR_PLL2MUL_MASK             0x1ff00

/* SYRACCR Register bit definitions */
#define R_SYSTEM_SYRACCR_BUSY                     (1 << 0)  /* Access Ready Monitor */

/* USBCKCR_ALT Register bit definitions */
#define R_SYSTEM_USBCKCR_ALT_USBCLKSEL            (1 << 0)  /* The USBCLKSEL bit selects the source of the USB clock (UCLK). */

/* SDADCCKCR Register bit definitions */
#define R_SYSTEM_SDADCCKCR_SDADCCKSEL             (1 << 0)  /* 24-bit Sigma-Delta A/D Converter Clock Select */

#define R_SYSTEM_SDADCCKCR_SDADCCKEN              (1 << 7)  /* 24-bit Sigma-Delta A/D Converter Clock Enable */

/* BCKADIVCR Register bit definitions */
#define R_SYSTEM_BCKADIVCR_CKDIV_SHIFT            (0)  /* Clock Division Select */
#define R_SYSTEM_BCKADIVCR_CKDIV_MASK             0xf

/* ESWCKDIVCR Register bit definitions */
#define R_SYSTEM_ESWCKDIVCR_CKDIV_SHIFT           (0)  /* Clock Division Select */
#define R_SYSTEM_ESWCKDIVCR_CKDIV_MASK            0xf

/* ESWPCKDIVCR Register bit definitions */
#define R_SYSTEM_ESWPCKDIVCR_CKDIV_SHIFT          (0)  /* Clock Division Select */
#define R_SYSTEM_ESWPCKDIVCR_CKDIV_MASK           0xf

/* ESCCKDIVCR Register bit definitions */
#define R_SYSTEM_ESCCKDIVCR_CKDIV_SHIFT           (0)  /* Clock Division Select */
#define R_SYSTEM_ESCCKDIVCR_CKDIV_MASK            0xf

/* ETHPCKDIVCR Register bit definitions */
#define R_SYSTEM_ETHPCKDIVCR_CKDIV_SHIFT          (0)  /* Clock Division Select */
#define R_SYSTEM_ETHPCKDIVCR_CKDIV_MASK           0xf

/* BCKACR Register bit definitions */
#define R_SYSTEM_BCKACR_CKSEL_SHIFT               (0)  /* Clock Source Select */
#define R_SYSTEM_BCKACR_CKSEL_MASK                0xf

#define R_SYSTEM_BCKACR_CKSREQ                    (1 << 6)  /* Clock Switching Request */

#define R_SYSTEM_BCKACR_CKSRDY                    (1 << 7)  /* Clock Switching Ready state flag */

/* ESWCKCR Register bit definitions */
#define R_SYSTEM_ESWCKCR_CKSEL_SHIFT              (0)  /* Clock Source Select */
#define R_SYSTEM_ESWCKCR_CKSEL_MASK               0xf

#define R_SYSTEM_ESWCKCR_CKSREQ                   (1 << 6)  /* Clock Switching Request */

#define R_SYSTEM_ESWCKCR_CKSRDY                   (1 << 7)  /* Clock Switching Ready state flag */

/* ESWPCKCR Register bit definitions */
#define R_SYSTEM_ESWPCKCR_CKSEL_SHIFT             (0)  /* Clock Source Select */
#define R_SYSTEM_ESWPCKCR_CKSEL_MASK              0xf

#define R_SYSTEM_ESWPCKCR_CKSREQ                  (1 << 6)  /* Clock Switching Request */

#define R_SYSTEM_ESWPCKCR_CKSRDY                  (1 << 7)  /* Clock Switching Ready state flag */

/* ESCCKCR Register bit definitions */
#define R_SYSTEM_ESCCKCR_CKSEL_SHIFT              (0)  /* Clock Source Select */
#define R_SYSTEM_ESCCKCR_CKSEL_MASK               0xf

#define R_SYSTEM_ESCCKCR_CKSREQ                   (1 << 6)  /* Clock Switching Request */

#define R_SYSTEM_ESCCKCR_CKSRDY                   (1 << 7)  /* Clock Switching Ready state flag */

/* ETHPCKCR Register bit definitions */
#define R_SYSTEM_ETHPCKCR_CKSEL_SHIFT             (0)  /* Clock Source Select */
#define R_SYSTEM_ETHPCKCR_CKSEL_MASK              0xf

#define R_SYSTEM_ETHPCKCR_CKSREQ                  (1 << 6)  /* Clock Switching Request */

#define R_SYSTEM_ETHPCKCR_CKSRDY                  (1 << 7)  /* Clock Switching Ready state flag */

/* LVDCR Register bit definitions */
#define R_SYSTEM_LVDCR_IDTSEL_SHIFT               (0)  /* Voltage Monitor Interrupt Generation Condition Select */
#define R_SYSTEM_LVDCR_IDTSEL_MASK                0x3
#  define R_SYSTEM_LVDCR_IDTSEL_00                        (0 << R_SYSTEM_LVDCR_IDTSEL_SHIFT)  /* Generate when VCC>=Vdet (rise) is detected */
#  define R_SYSTEM_LVDCR_IDTSEL_01                        (1 << R_SYSTEM_LVDCR_IDTSEL_SHIFT)  /* Generate when VCC<Vdet (drop) is detected */
#  define R_SYSTEM_LVDCR_IDTSEL_10                        (2 << R_SYSTEM_LVDCR_IDTSEL_SHIFT)  /* Generate when drop and rise are detected */
#  define R_SYSTEM_LVDCR_IDTSEL_11                        (3 << R_SYSTEM_LVDCR_IDTSEL_SHIFT)  /* Settings prohibited */

#define R_SYSTEM_LVDCR_IRQSEL                     (1 << 2)  /* Voltage Monitor Interrupt Type Select */

/* LVDSR Register bit definitions */
#define R_SYSTEM_LVDSR_DET                        (1 << 0)  /* Voltage Monitor Voltage Change Detection Flag */

#define R_SYSTEM_LVDSR_MON                        (1 << 1)  /* Voltage Monitor 1 Signal Monitor Flag */

/* CRVSYSCR Register bit definitions */
#define R_SYSTEM_CRVSYSCR_CRVEN                   (1 << 0)  /* Clock Recovery Enable */

/* CPUDSCR Register bit definitions */
#define R_SYSTEM_CPUDSCR_PGD_S                    (1 << 0)  /* Power Gating Disable for CPU%s */

#define R_SYSTEM_CPUDSCR_PGD0                     (1 << 0)  /* Power Gating Disable for CPU0 */

#define R_SYSTEM_CPUDSCR_PGD1                     (1 << 1)  /* Power Gating Disable for CPU1 */

/* PDCTR Register bit definitions */
#define R_SYSTEM_PDCTR_PDDE                       (1 << 0)  /* Power control enable */

#define R_SYSTEM_PDCTR_PDCSF                      (1 << 6)  /* Power control status flag */

#define R_SYSTEM_PDCTR_PDPGSF                     (1 << 7)  /* Power gating status flag */

/* PDRAMSCR0 Register bit definitions */
#define R_SYSTEM_PDRAMSCR0_RKEEP_S                (1 << 0)  /* RAM Retention bit %s */

#define R_SYSTEM_PDRAMSCR0_RKEEP0                 (1 << 0)  /* RAM Retention bit 0 */

#define R_SYSTEM_PDRAMSCR0_RKEEP1                 (1 << 1)  /* RAM Retention bit 1 */

#define R_SYSTEM_PDRAMSCR0_RKEEP2                 (1 << 2)  /* RAM Retention bit 2 */

#define R_SYSTEM_PDRAMSCR0_RKEEP3                 (1 << 3)  /* RAM Retention bit 3 */

#define R_SYSTEM_PDRAMSCR0_RKEEP4                 (1 << 4)  /* RAM Retention bit 4 */

#define R_SYSTEM_PDRAMSCR0_RKEEP5                 (1 << 5)  /* RAM Retention bit 5 */

#define R_SYSTEM_PDRAMSCR0_RKEEP6                 (1 << 6)  /* RAM Retention bit 6 */

#define R_SYSTEM_PDRAMSCR0_RKEEP7                 (1 << 7)  /* RAM Retention bit 7 */

#define R_SYSTEM_PDRAMSCR0_RKEEP8                 (1 << 8)  /* RAM Retention bit 8 */

#define R_SYSTEM_PDRAMSCR0_RKEEP9                 (1 << 9)  /* RAM Retention bit 9 */

#define R_SYSTEM_PDRAMSCR0_RKEEP10                (1 << 10)  /* RAM Retention bit 10 */

#define R_SYSTEM_PDRAMSCR0_RKEEP11                (1 << 11)  /* RAM Retention bit 11 */

#define R_SYSTEM_PDRAMSCR0_RKEEP12                (1 << 12)  /* RAM Retention bit 12 */

#define R_SYSTEM_PDRAMSCR0_RKEEP13                (1 << 13)  /* RAM Retention bit 13 */

#define R_SYSTEM_PDRAMSCR0_RKEEP14                (1 << 14)  /* RAM Retention bit 14 */

#define R_SYSTEM_PDRAMSCR0_RKEEP15                (1 << 15)  /* RAM Retention bit 15 */

/* PDRAMSCR1 Register bit definitions */
#define R_SYSTEM_PDRAMSCR1_RKEEP_S                (1 << 0)  /* RAM Retention bit %s */

#define R_SYSTEM_PDRAMSCR1_RKEEP0                 (1 << 0)  /* RAM Retention bit 0 */

#define R_SYSTEM_PDRAMSCR1_RKEEP1                 (1 << 1)  /* RAM Retention bit 1 */

#define R_SYSTEM_PDRAMSCR1_RKEEP2                 (1 << 2)  /* RAM Retention bit 2 */

#define R_SYSTEM_PDRAMSCR1_RKEEP3                 (1 << 3)  /* RAM Retention bit 3 */

#define R_SYSTEM_PDRAMSCR1_RKEEP4                 (1 << 4)  /* RAM Retention bit 4 */

#define R_SYSTEM_PDRAMSCR1_RKEEP5                 (1 << 5)  /* RAM Retention bit 5 */

#define R_SYSTEM_PDRAMSCR1_RKEEP6                 (1 << 6)  /* RAM Retention bit 6 */

#define R_SYSTEM_PDRAMSCR1_RKEEP7                 (1 << 7)  /* RAM Retention bit 7 */

/* VBRSABAR Register bit definitions */
#define R_SYSTEM_VBRSABAR_SABA_SHIFT              (0)  /* Security Attribute Boundary Address */
#define R_SYSTEM_VBRSABAR_SABA_MASK               0xffff

/* VBRPABARS Register bit definitions */
#define R_SYSTEM_VBRPABARS_PABAS_SHIFT            (0)  /* Privilege Attribute Boundary Address for Secure Region */
#define R_SYSTEM_VBRPABARS_PABAS_MASK             0xffff

/* VBRPABARNS Register bit definitions */
#define R_SYSTEM_VBRPABARNS_PABANS_SHIFT          (0)  /* Privilege Attribute Boundary Address for Non-secure Region */
#define R_SYSTEM_VBRPABARNS_PABANS_MASK           0xffff

/* CGFSAR Register bit definitions */
#define R_SYSTEM_CGFSAR_NONSEC0_S                 (1 << 0)  /* Non Secure Attribute bit %s */

#define R_SYSTEM_CGFSAR_NONSEC_S                  (1 << 10)  /* Non Secure Attribute bit %s */

#define R_SYSTEM_CGFSAR_NONSEC00                  (1 << 0)  /* Non Secure Attribute bit 0 */

#define R_SYSTEM_CGFSAR_NONSEC01                  (1 << 1)  /* Non Secure Attribute bit 1 */

#define R_SYSTEM_CGFSAR_NONSEC02                  (1 << 2)  /* Non Secure Attribute bit 2 */

#define R_SYSTEM_CGFSAR_NONSEC03                  (1 << 3)  /* Non Secure Attribute bit 3 */

#define R_SYSTEM_CGFSAR_NONSEC04                  (1 << 4)  /* Non Secure Attribute bit 4 */

#define R_SYSTEM_CGFSAR_NONSEC05                  (1 << 5)  /* Non Secure Attribute bit 5 */

#define R_SYSTEM_CGFSAR_NONSEC06                  (1 << 6)  /* Non Secure Attribute bit 6 */

#define R_SYSTEM_CGFSAR_NONSEC07                  (1 << 7)  /* Non Secure Attribute bit 7 */

#define R_SYSTEM_CGFSAR_NONSEC08                  (1 << 8)  /* Non Secure Attribute bit 8 */

#define R_SYSTEM_CGFSAR_NONSEC09                  (1 << 9)  /* Non Secure Attribute bit 9 */

#define R_SYSTEM_CGFSAR_NONSEC10                  (1 << 10)  /* Non Secure Attribute bit 10 */

#define R_SYSTEM_CGFSAR_NONSEC11                  (1 << 11)  /* Non Secure Attribute bit 11 */

#define R_SYSTEM_CGFSAR_NONSEC12                  (1 << 12)  /* Non Secure Attribute bit 12 */

#define R_SYSTEM_CGFSAR_NONSEC13                  (1 << 13)  /* Non Secure Attribute bit 13 */

#define R_SYSTEM_CGFSAR_NONSEC14                  (1 << 14)  /* Non Secure Attribute bit 14 */

#define R_SYSTEM_CGFSAR_NONSEC15                  (1 << 15)  /* Non Secure Attribute bit 15 */

#define R_SYSTEM_CGFSAR_NONSEC16                  (1 << 16)  /* Non Secure Attribute bit 16 */

#define R_SYSTEM_CGFSAR_NONSEC17                  (1 << 17)  /* Non Secure Attribute bit 17 */

#define R_SYSTEM_CGFSAR_NONSEC18                  (1 << 18)  /* Non Secure Attribute bit 18 */

#define R_SYSTEM_CGFSAR_NONSEC19                  (1 << 19)  /* Non Secure Attribute bit 19 */

#define R_SYSTEM_CGFSAR_NONSEC20                  (1 << 20)  /* Non Secure Attribute bit 20 */

#define R_SYSTEM_CGFSAR_NONSEC21                  (1 << 21)  /* Non Secure Attribute bit 21 */

#define R_SYSTEM_CGFSAR_NONSEC22                  (1 << 22)  /* Non Secure Attribute bit 22 */

#define R_SYSTEM_CGFSAR_NONSEC23                  (1 << 23)  /* Non Secure Attribute bit 23 */

#define R_SYSTEM_CGFSAR_NONSEC24                  (1 << 24)  /* Non Secure Attribute bit 24 */

#define R_SYSTEM_CGFSAR_NONSEC25                  (1 << 25)  /* Non Secure Attribute bit 25 */

#define R_SYSTEM_CGFSAR_NONSEC26                  (1 << 26)  /* Non Secure Attribute bit 26 */

#define R_SYSTEM_CGFSAR_NONSEC27                  (1 << 27)  /* Non Secure Attribute bit 27 */

#define R_SYSTEM_CGFSAR_NONSEC28                  (1 << 28)  /* Non Secure Attribute bit 28 */

#define R_SYSTEM_CGFSAR_NONSEC29                  (1 << 29)  /* Non Secure Attribute bit 29 */

#define R_SYSTEM_CGFSAR_NONSEC30                  (1 << 30)  /* Non Secure Attribute bit 30 */

#define R_SYSTEM_CGFSAR_NONSEC31                  (1 << 31)  /* Non Secure Attribute bit 31 */

/* RSTSAR Register bit definitions */
#define R_SYSTEM_RSTSAR_NONSEC_S                  (1 << 0)  /* Non Secure Attribute bit %s */

#define R_SYSTEM_RSTSAR_NONSEC0                   (1 << 0)  /* Non Secure Attribute bit 0 */

#define R_SYSTEM_RSTSAR_NONSEC1                   (1 << 1)  /* Non Secure Attribute bit 1 */

#define R_SYSTEM_RSTSAR_NONSEC2                   (1 << 2)  /* Non Secure Attribute bit 2 */

#define R_SYSTEM_RSTSAR_NONSEC3                   (1 << 3)  /* Non Secure Attribute bit 3 */

#define R_SYSTEM_RSTSAR_NONSEC4                   (1 << 4)  /* Non Secure Attribute bit 4 */

/* LPMSAR Register bit definitions */
#define R_SYSTEM_LPMSAR_NONSEC_S                  (1 << 0)  /* Non Secure Attribute bit %s */

#define R_SYSTEM_LPMSAR_NONSEC0                   (1 << 0)  /* Non Secure Attribute bit 0 */

#define R_SYSTEM_LPMSAR_NONSEC1                   (1 << 1)  /* Non Secure Attribute bit 1 */

#define R_SYSTEM_LPMSAR_NONSEC2                   (1 << 2)  /* Non Secure Attribute bit 2 */

#define R_SYSTEM_LPMSAR_NONSEC3                   (1 << 3)  /* Non Secure Attribute bit 3 */

#define R_SYSTEM_LPMSAR_NONSEC4                   (1 << 4)  /* Non Secure Attribute bit 4 */

#define R_SYSTEM_LPMSAR_NONSEC5                   (1 << 5)  /* Non Secure Attribute bit 5 */

#define R_SYSTEM_LPMSAR_NONSEC6                   (1 << 6)  /* Non Secure Attribute bit 6 */

#define R_SYSTEM_LPMSAR_NONSEC7                   (1 << 7)  /* Non Secure Attribute bit 7 */

#define R_SYSTEM_LPMSAR_NONSEC8                   (1 << 8)  /* Non Secure Attribute bit 8 */

#define R_SYSTEM_LPMSAR_NONSEC9                   (1 << 9)  /* Non Secure Attribute bit 9 */

#define R_SYSTEM_LPMSAR_NONSEC10                  (1 << 10)  /* Non Secure Attribute bit 10 */

#define R_SYSTEM_LPMSAR_NONSEC11                  (1 << 11)  /* Non Secure Attribute bit 11 */

#define R_SYSTEM_LPMSAR_NONSEC12                  (1 << 12)  /* Non Secure Attribute bit 12 */

#define R_SYSTEM_LPMSAR_NONSEC13                  (1 << 13)  /* Non Secure Attribute bit 13 */

#define R_SYSTEM_LPMSAR_NONSEC14                  (1 << 14)  /* Non Secure Attribute bit 14 */

#define R_SYSTEM_LPMSAR_NONSEC15                  (1 << 15)  /* Non Secure Attribute bit 15 */

#define R_SYSTEM_LPMSAR_NONSEC16                  (1 << 16)  /* Non Secure Attribute bit 16 */

#define R_SYSTEM_LPMSAR_NONSEC17                  (1 << 17)  /* Non Secure Attribute bit 17 */

#define R_SYSTEM_LPMSAR_NONSEC18                  (1 << 18)  /* Non Secure Attribute bit 18 */

#define R_SYSTEM_LPMSAR_NONSEC19                  (1 << 19)  /* Non Secure Attribute bit 19 */

#define R_SYSTEM_LPMSAR_NONSEC20                  (1 << 20)  /* Non Secure Attribute bit 20 */

#define R_SYSTEM_LPMSAR_NONSEC21                  (1 << 21)  /* Non Secure Attribute bit 21 */

#define R_SYSTEM_LPMSAR_NONSEC22                  (1 << 22)  /* Non Secure Attribute bit 22 */

#define R_SYSTEM_LPMSAR_NONSEC23                  (1 << 23)  /* Non Secure Attribute bit 23 */

#define R_SYSTEM_LPMSAR_NONSEC24                  (1 << 24)  /* Non Secure Attribute bit 24 */

#define R_SYSTEM_LPMSAR_NONSEC25                  (1 << 25)  /* Non Secure Attribute bit 25 */

#define R_SYSTEM_LPMSAR_NONSEC26                  (1 << 26)  /* Non Secure Attribute bit 26 */

#define R_SYSTEM_LPMSAR_NONSEC27                  (1 << 27)  /* Non Secure Attribute bit 27 */

#define R_SYSTEM_LPMSAR_NONSEC28                  (1 << 28)  /* Non Secure Attribute bit 28 */

#define R_SYSTEM_LPMSAR_NONSEC29                  (1 << 29)  /* Non Secure Attribute bit 29 */

#define R_SYSTEM_LPMSAR_NONSEC30                  (1 << 30)  /* Non Secure Attribute bit 30 */

#define R_SYSTEM_LPMSAR_NONSEC31                  (1 << 31)  /* Non Secure Attribute bit 31 */

/* LVDSAR Register bit definitions */
#define R_SYSTEM_LVDSAR_NONSEC0                   (1 << 0)  /* Non Secure Attribute bit 0 */

#define R_SYSTEM_LVDSAR_NONSEC1                   (1 << 1)  /* Non Secure Attribute bit 1 */

/* BBFSAR Register bit definitions */
#define R_SYSTEM_BBFSAR_NONSEC0                   (1 << 0)  /* Non-secure Attribute bit 0 */

#define R_SYSTEM_BBFSAR_NONSEC1                   (1 << 1)  /* Non-secure Attribute bit 1 */

#define R_SYSTEM_BBFSAR_NONSEC2                   (1 << 2)  /* Non-secure Attribute bit 2 */

#define R_SYSTEM_BBFSAR_NONSEC3                   (1 << 3)  /* Non-secure Attribute bit 3 */

#define R_SYSTEM_BBFSAR_NONSEC4                   (1 << 4)  /* Non-secure Attribute bit 4 */

#define R_SYSTEM_BBFSAR_NONSEC5                   (1 << 5)  /* Non-secure Attribute bit 5 */

#define R_SYSTEM_BBFSAR_NONSEC6                   (1 << 6)  /* Non-secure Attribute bit 6 */

#define R_SYSTEM_BBFSAR_NONSEC7                   (1 << 7)  /* Non-secure Attribute bit 7 */

#define R_SYSTEM_BBFSAR_NONSEC8                   (1 << 8)  /* Non-secure Attribute bit 8 */

/* PGCSAR Register bit definitions */
#define R_SYSTEM_PGCSAR_NONSEC_S                  (1 << 0)  /* Non-secure Attribute bit %s */

#define R_SYSTEM_PGCSAR_NONSEC0                   (1 << 0)  /* Non-secure Attribute bit 0 */

#define R_SYSTEM_PGCSAR_NONSEC1                   (1 << 1)  /* Non-secure Attribute bit 1 */

#define R_SYSTEM_PGCSAR_NONSEC2                   (1 << 2)  /* Non-secure Attribute bit 2 */

#define R_SYSTEM_PGCSAR_NONSEC3                   (1 << 3)  /* Non-secure Attribute bit 3 */

#define R_SYSTEM_PGCSAR_NONSEC4                   (1 << 4)  /* Non-secure Attribute bit 4 */

#define R_SYSTEM_PGCSAR_NONSEC5                   (1 << 5)  /* Non-secure Attribute bit 5 */

#define R_SYSTEM_PGCSAR_NONSEC6                   (1 << 6)  /* Non-secure Attribute bit 6 */

#define R_SYSTEM_PGCSAR_NONSEC7                   (1 << 7)  /* Non-secure Attribute bit 7 */

#define R_SYSTEM_PGCSAR_NONSEC8                   (1 << 8)  /* Non-secure Attribute bit 8 */

#define R_SYSTEM_PGCSAR_NONSEC9                   (1 << 9)  /* Non-secure Attribute bit 9 */

#define R_SYSTEM_PGCSAR_NONSEC10                  (1 << 10)  /* Non-secure Attribute bit 10 */

#define R_SYSTEM_PGCSAR_NONSEC11                  (1 << 11)  /* Non-secure Attribute bit 11 */

#define R_SYSTEM_PGCSAR_NONSEC12                  (1 << 12)  /* Non-secure Attribute bit 12 */

#define R_SYSTEM_PGCSAR_NONSEC13                  (1 << 13)  /* Non-secure Attribute bit 13 */

#define R_SYSTEM_PGCSAR_NONSEC14                  (1 << 14)  /* Non-secure Attribute bit 14 */

#define R_SYSTEM_PGCSAR_NONSEC15                  (1 << 15)  /* Non-secure Attribute bit 15 */

#define R_SYSTEM_PGCSAR_NONSEC16                  (1 << 16)  /* Non-secure Attribute bit 16 */

#define R_SYSTEM_PGCSAR_NONSEC17                  (1 << 17)  /* Non-secure Attribute bit 17 */

#define R_SYSTEM_PGCSAR_NONSEC18                  (1 << 18)  /* Non-secure Attribute bit 18 */

#define R_SYSTEM_PGCSAR_NONSEC19                  (1 << 19)  /* Non-secure Attribute bit 19 */

#define R_SYSTEM_PGCSAR_NONSEC20                  (1 << 20)  /* Non-secure Attribute bit 20 */

#define R_SYSTEM_PGCSAR_NONSEC21                  (1 << 21)  /* Non-secure Attribute bit 21 */

#define R_SYSTEM_PGCSAR_NONSEC22                  (1 << 22)  /* Non-secure Attribute bit 22 */

#define R_SYSTEM_PGCSAR_NONSEC23                  (1 << 23)  /* Non-secure Attribute bit 23 */

#define R_SYSTEM_PGCSAR_NONSEC24                  (1 << 24)  /* Non-secure Attribute bit 24 */

#define R_SYSTEM_PGCSAR_NONSEC25                  (1 << 25)  /* Non-secure Attribute bit 25 */

#define R_SYSTEM_PGCSAR_NONSEC26                  (1 << 26)  /* Non-secure Attribute bit 26 */

#define R_SYSTEM_PGCSAR_NONSEC27                  (1 << 27)  /* Non-secure Attribute bit 27 */

#define R_SYSTEM_PGCSAR_NONSEC28                  (1 << 28)  /* Non-secure Attribute bit 28 */

#define R_SYSTEM_PGCSAR_NONSEC29                  (1 << 29)  /* Non-secure Attribute bit 29 */

#define R_SYSTEM_PGCSAR_NONSEC30                  (1 << 30)  /* Non-secure Attribute bit 30 */

#define R_SYSTEM_PGCSAR_NONSEC31                  (1 << 31)  /* Non-secure Attribute bit 31 */

/* DPFSAR Register bit definitions */
#define R_SYSTEM_DPFSAR_DPFSA_S                   (1 << 0)  /* Deep Standby Interrupt Factor Security Attribute bit %s */

#define R_SYSTEM_DPFSAR_DPFSA0                    (1 << 0)  /* Deep Standby Interrupt Factor Security Attribute bit 0 */

#define R_SYSTEM_DPFSAR_DPFSA1                    (1 << 1)  /* Deep Standby Interrupt Factor Security Attribute bit 1 */

#define R_SYSTEM_DPFSAR_DPFSA2                    (1 << 2)  /* Deep Standby Interrupt Factor Security Attribute bit 2 */

#define R_SYSTEM_DPFSAR_DPFSA3                    (1 << 3)  /* Deep Standby Interrupt Factor Security Attribute bit 3 */

#define R_SYSTEM_DPFSAR_DPFSA4                    (1 << 4)  /* Deep Standby Interrupt Factor Security Attribute bit 4 */

#define R_SYSTEM_DPFSAR_DPFSA5                    (1 << 5)  /* Deep Standby Interrupt Factor Security Attribute bit 5 */

#define R_SYSTEM_DPFSAR_DPFSA6                    (1 << 6)  /* Deep Standby Interrupt Factor Security Attribute bit 6 */

#define R_SYSTEM_DPFSAR_DPFSA7                    (1 << 7)  /* Deep Standby Interrupt Factor Security Attribute bit 7 */

#define R_SYSTEM_DPFSAR_DPFSA8                    (1 << 8)  /* Deep Standby Interrupt Factor Security Attribute bit 8 */

#define R_SYSTEM_DPFSAR_DPFSA9                    (1 << 9)  /* Deep Standby Interrupt Factor Security Attribute bit 9 */

#define R_SYSTEM_DPFSAR_DPFSA10                   (1 << 10)  /* Deep Standby Interrupt Factor Security Attribute bit 10 */

#define R_SYSTEM_DPFSAR_DPFSA11                   (1 << 11)  /* Deep Standby Interrupt Factor Security Attribute bit 11 */

#define R_SYSTEM_DPFSAR_DPFSA12                   (1 << 12)  /* Deep Standby Interrupt Factor Security Attribute bit 12 */

#define R_SYSTEM_DPFSAR_DPFSA13                   (1 << 13)  /* Deep Standby Interrupt Factor Security Attribute bit 13 */

#define R_SYSTEM_DPFSAR_DPFSA14                   (1 << 14)  /* Deep Standby Interrupt Factor Security Attribute bit 14 */

#define R_SYSTEM_DPFSAR_DPFSA15                   (1 << 15)  /* Deep Standby Interrupt Factor Security Attribute bit 15 */

#define R_SYSTEM_DPFSAR_DPFSA16                   (1 << 16)  /* Deep Standby Interrupt Factor Security Attribute bit 16 */

#define R_SYSTEM_DPFSAR_DPFSA17                   (1 << 17)  /* Deep Standby Interrupt Factor Security Attribute bit 17 */

#define R_SYSTEM_DPFSAR_DPFSA18                   (1 << 18)  /* Deep Standby Interrupt Factor Security Attribute bit 18 */

#define R_SYSTEM_DPFSAR_DPFSA19                   (1 << 19)  /* Deep Standby Interrupt Factor Security Attribute bit 19 */

#define R_SYSTEM_DPFSAR_DPFSA20                   (1 << 20)  /* Deep Standby Interrupt Factor Security Attribute bit 20 */

#define R_SYSTEM_DPFSAR_DPFSA21                   (1 << 21)  /* Deep Standby Interrupt Factor Security Attribute bit 21 */

#define R_SYSTEM_DPFSAR_DPFSA22                   (1 << 22)  /* Deep Standby Interrupt Factor Security Attribute bit 22 */

#define R_SYSTEM_DPFSAR_DPFSA23                   (1 << 23)  /* Deep Standby Interrupt Factor Security Attribute bit 23 */

#define R_SYSTEM_DPFSAR_DPFSA24                   (1 << 24)  /* Deep Standby Interrupt Factor Security Attribute bit 24 */

#define R_SYSTEM_DPFSAR_DPFSA25                   (1 << 25)  /* Deep Standby Interrupt Factor Security Attribute bit 25 */

#define R_SYSTEM_DPFSAR_DPFSA26                   (1 << 26)  /* Deep Standby Interrupt Factor Security Attribute bit 26 */

#define R_SYSTEM_DPFSAR_DPFSA27                   (1 << 27)  /* Deep Standby Interrupt Factor Security Attribute bit 27 */

#define R_SYSTEM_DPFSAR_DPFSA28                   (1 << 28)  /* Deep Standby Interrupt Factor Security Attribute bit 28 */

#define R_SYSTEM_DPFSAR_DPFSA29                   (1 << 29)  /* Deep Standby Interrupt Factor Security Attribute bit 29 */

#define R_SYSTEM_DPFSAR_DPFSA30                   (1 << 30)  /* Deep Standby Interrupt Factor Security Attribute bit 30 */

#define R_SYSTEM_DPFSAR_DPFSA31                   (1 << 31)  /* Deep Standby Interrupt Factor Security Attribute bit 31 */

/* RSCSAR Register bit definitions */
#define R_SYSTEM_RSCSAR_RSCSA_S                   (1 << 0)  /* RAM Standby Control Security Attribute bit %s */

#define R_SYSTEM_RSCSAR_RSCSA0                    (1 << 0)  /* RAM Standby Control Security Attribute bit 0 */

#define R_SYSTEM_RSCSAR_RSCSA1                    (1 << 1)  /* RAM Standby Control Security Attribute bit 1 */

#define R_SYSTEM_RSCSAR_RSCSA2                    (1 << 2)  /* RAM Standby Control Security Attribute bit 2 */

#define R_SYSTEM_RSCSAR_RSCSA3                    (1 << 3)  /* RAM Standby Control Security Attribute bit 3 */

#define R_SYSTEM_RSCSAR_RSCSA4                    (1 << 4)  /* RAM Standby Control Security Attribute bit 4 */

#define R_SYSTEM_RSCSAR_RSCSA5                    (1 << 5)  /* RAM Standby Control Security Attribute bit 5 */

#define R_SYSTEM_RSCSAR_RSCSA6                    (1 << 6)  /* RAM Standby Control Security Attribute bit 6 */

#define R_SYSTEM_RSCSAR_RSCSA7                    (1 << 7)  /* RAM Standby Control Security Attribute bit 7 */

#define R_SYSTEM_RSCSAR_RSCSA8                    (1 << 8)  /* RAM Standby Control Security Attribute bit 8 */

#define R_SYSTEM_RSCSAR_RSCSA9                    (1 << 9)  /* RAM Standby Control Security Attribute bit 9 */

#define R_SYSTEM_RSCSAR_RSCSA10                   (1 << 10)  /* RAM Standby Control Security Attribute bit 10 */

#define R_SYSTEM_RSCSAR_RSCSA11                   (1 << 11)  /* RAM Standby Control Security Attribute bit 11 */

#define R_SYSTEM_RSCSAR_RSCSA12                   (1 << 12)  /* RAM Standby Control Security Attribute bit 12 */

#define R_SYSTEM_RSCSAR_RSCSA13                   (1 << 13)  /* RAM Standby Control Security Attribute bit 13 */

#define R_SYSTEM_RSCSAR_RSCSA14                   (1 << 14)  /* RAM Standby Control Security Attribute bit 14 */

#define R_SYSTEM_RSCSAR_RSCSA15                   (1 << 15)  /* RAM Standby Control Security Attribute bit 15 */

#define R_SYSTEM_RSCSAR_RSCSA16                   (1 << 16)  /* RAM Standby Control Security Attribute bit 16 */

#define R_SYSTEM_RSCSAR_RSCSA17                   (1 << 17)  /* RAM Standby Control Security Attribute bit 17 */

#define R_SYSTEM_RSCSAR_RSCSA18                   (1 << 18)  /* RAM Standby Control Security Attribute bit 18 */

#define R_SYSTEM_RSCSAR_RSCSA19                   (1 << 19)  /* RAM Standby Control Security Attribute bit 19 */

#define R_SYSTEM_RSCSAR_RSCSA20                   (1 << 20)  /* RAM Standby Control Security Attribute bit 20 */

#define R_SYSTEM_RSCSAR_RSCSA21                   (1 << 21)  /* RAM Standby Control Security Attribute bit 21 */

#define R_SYSTEM_RSCSAR_RSCSA22                   (1 << 22)  /* RAM Standby Control Security Attribute bit 22 */

#define R_SYSTEM_RSCSAR_RSCSA23                   (1 << 23)  /* RAM Standby Control Security Attribute bit 23 */

#define R_SYSTEM_RSCSAR_RSCSA24                   (1 << 24)  /* RAM Standby Control Security Attribute bit 24 */

#define R_SYSTEM_RSCSAR_RSCSA25                   (1 << 25)  /* RAM Standby Control Security Attribute bit 25 */

#define R_SYSTEM_RSCSAR_RSCSA26                   (1 << 26)  /* RAM Standby Control Security Attribute bit 26 */

#define R_SYSTEM_RSCSAR_RSCSA27                   (1 << 27)  /* RAM Standby Control Security Attribute bit 27 */

#define R_SYSTEM_RSCSAR_RSCSA28                   (1 << 28)  /* RAM Standby Control Security Attribute bit 28 */

#define R_SYSTEM_RSCSAR_RSCSA29                   (1 << 29)  /* RAM Standby Control Security Attribute bit 29 */

#define R_SYSTEM_RSCSAR_RSCSA30                   (1 << 30)  /* RAM Standby Control Security Attribute bit 30 */

#define R_SYSTEM_RSCSAR_RSCSA31                   (1 << 31)  /* RAM Standby Control Security Attribute bit 31 */

/* DPFSAR1 Register bit definitions */
#define R_SYSTEM_DPFSAR1_DPFSA_S                  (1 << 0)  /* Deep Standby Interrupt Factor Security Attribute bit %s */

#define R_SYSTEM_DPFSAR1_DPFSA0                   (1 << 0)  /* Deep Standby Interrupt Factor Security Attribute bit 0 */

#define R_SYSTEM_DPFSAR1_DPFSA1                   (1 << 1)  /* Deep Standby Interrupt Factor Security Attribute bit 1 */

#define R_SYSTEM_DPFSAR1_DPFSA2                   (1 << 2)  /* Deep Standby Interrupt Factor Security Attribute bit 2 */

#define R_SYSTEM_DPFSAR1_DPFSA3                   (1 << 3)  /* Deep Standby Interrupt Factor Security Attribute bit 3 */

#define R_SYSTEM_DPFSAR1_DPFSA4                   (1 << 4)  /* Deep Standby Interrupt Factor Security Attribute bit 4 */

#define R_SYSTEM_DPFSAR1_DPFSA5                   (1 << 5)  /* Deep Standby Interrupt Factor Security Attribute bit 5 */

#define R_SYSTEM_DPFSAR1_DPFSA6                   (1 << 6)  /* Deep Standby Interrupt Factor Security Attribute bit 6 */

#define R_SYSTEM_DPFSAR1_DPFSA7                   (1 << 7)  /* Deep Standby Interrupt Factor Security Attribute bit 7 */

#define R_SYSTEM_DPFSAR1_DPFSA8                   (1 << 8)  /* Deep Standby Interrupt Factor Security Attribute bit 8 */

#define R_SYSTEM_DPFSAR1_DPFSA9                   (1 << 9)  /* Deep Standby Interrupt Factor Security Attribute bit 9 */

#define R_SYSTEM_DPFSAR1_DPFSA10                  (1 << 10)  /* Deep Standby Interrupt Factor Security Attribute bit 10 */

#define R_SYSTEM_DPFSAR1_DPFSA11                  (1 << 11)  /* Deep Standby Interrupt Factor Security Attribute bit 11 */

#define R_SYSTEM_DPFSAR1_DPFSA12                  (1 << 12)  /* Deep Standby Interrupt Factor Security Attribute bit 12 */

#define R_SYSTEM_DPFSAR1_DPFSA13                  (1 << 13)  /* Deep Standby Interrupt Factor Security Attribute bit 13 */

#define R_SYSTEM_DPFSAR1_DPFSA14                  (1 << 14)  /* Deep Standby Interrupt Factor Security Attribute bit 14 */

#define R_SYSTEM_DPFSAR1_DPFSA15                  (1 << 15)  /* Deep Standby Interrupt Factor Security Attribute bit 15 */

#define R_SYSTEM_DPFSAR1_DPFSA16                  (1 << 16)  /* Deep Standby Interrupt Factor Security Attribute bit 16 */

#define R_SYSTEM_DPFSAR1_DPFSA17                  (1 << 17)  /* Deep Standby Interrupt Factor Security Attribute bit 17 */

#define R_SYSTEM_DPFSAR1_DPFSA18                  (1 << 18)  /* Deep Standby Interrupt Factor Security Attribute bit 18 */

#define R_SYSTEM_DPFSAR1_DPFSA19                  (1 << 19)  /* Deep Standby Interrupt Factor Security Attribute bit 19 */

#define R_SYSTEM_DPFSAR1_DPFSA20                  (1 << 20)  /* Deep Standby Interrupt Factor Security Attribute bit 20 */

#define R_SYSTEM_DPFSAR1_DPFSA21                  (1 << 21)  /* Deep Standby Interrupt Factor Security Attribute bit 21 */

#define R_SYSTEM_DPFSAR1_DPFSA22                  (1 << 22)  /* Deep Standby Interrupt Factor Security Attribute bit 22 */

#define R_SYSTEM_DPFSAR1_DPFSA23                  (1 << 23)  /* Deep Standby Interrupt Factor Security Attribute bit 23 */

#define R_SYSTEM_DPFSAR1_DPFSA24                  (1 << 24)  /* Deep Standby Interrupt Factor Security Attribute bit 24 */

#define R_SYSTEM_DPFSAR1_DPFSA25                  (1 << 25)  /* Deep Standby Interrupt Factor Security Attribute bit 25 */

#define R_SYSTEM_DPFSAR1_DPFSA26                  (1 << 26)  /* Deep Standby Interrupt Factor Security Attribute bit 26 */

#define R_SYSTEM_DPFSAR1_DPFSA27                  (1 << 27)  /* Deep Standby Interrupt Factor Security Attribute bit 27 */

#define R_SYSTEM_DPFSAR1_DPFSA28                  (1 << 28)  /* Deep Standby Interrupt Factor Security Attribute bit 28 */

#define R_SYSTEM_DPFSAR1_DPFSA29                  (1 << 29)  /* Deep Standby Interrupt Factor Security Attribute bit 29 */

#define R_SYSTEM_DPFSAR1_DPFSA30                  (1 << 30)  /* Deep Standby Interrupt Factor Security Attribute bit 30 */

#define R_SYSTEM_DPFSAR1_DPFSA31                  (1 << 31)  /* Deep Standby Interrupt Factor Security Attribute bit 31 */

/* PRCR Register bit definitions */
#define R_SYSTEM_PRCR_PRC0                        (1 << 0)  /* Enables writing to the registers related to the clock generation circuit. */

#define R_SYSTEM_PRCR_PRC1                        (1 << 1)  /* Enables writing to the registers related to the operating modes, the low power modes, and the battery backup function. */

#define R_SYSTEM_PRCR_PRC3                        (1 << 3)  /* Enables writing to the registers related to the PVD. */

#define R_SYSTEM_PRCR_PRC4                        (1 << 4)  /* Enables writing to the registers related to the security and privilege setting registers. */

#define R_SYSTEM_PRCR_PRC5                        (1 << 5)  /* Enables writing to the registers related the reset control. */

#define R_SYSTEM_PRCR_PRKEY_SHIFT                 (8)  /* PRC Key Code */
#define R_SYSTEM_PRCR_PRKEY_MASK                  0xff00
#  define R_SYSTEM_PRCR_PRKEY_0XA5                        (165 << R_SYSTEM_PRCR_PRKEY_SHIFT)  /* Enables writing to the PRCR_S register. */

/* PRCR_NS Register bit definitions */
#define R_SYSTEM_PRCR_NS_PRC0                     (1 << 0)  /* Enables writing to the registers related to the clock generation circuit. */

#define R_SYSTEM_PRCR_NS_PRC1                     (1 << 1)  /* Enables writing to the registers related to the operating modes, the low power modes, and the battery backup function. */

#define R_SYSTEM_PRCR_NS_PRC3                     (1 << 3)  /* Enables writing to the registers related to the PVD. */

#define R_SYSTEM_PRCR_NS_PRC4                     (1 << 4)  /* Enables writing to the registers related to the privilege setting registers. */

#define R_SYSTEM_PRCR_NS_PRKEY_SHIFT              (8)  /* PRC Key Code */
#define R_SYSTEM_PRCR_NS_PRKEY_MASK               0xff00
#  define R_SYSTEM_PRCR_NS_PRKEY_0XA5                     (165 << R_SYSTEM_PRCR_NS_PRKEY_SHIFT)  /* Enables writing to the PRCR_NS register. */

/* LOCOCR Register bit definitions */
#define R_SYSTEM_LOCOCR_LCSTP                     (1 << 0)  /* LOCO Stop */

/* LOCOUTCR Register bit definitions */
#define R_SYSTEM_LOCOUTCR_LOCOUTRM_SHIFT          (0)  /* LOCO User Trimming */
#define R_SYSTEM_LOCOUTCR_LOCOUTRM_MASK           0xff

/* STCONR Register bit definitions */
#define R_SYSTEM_STCONR_STCON_SHIFT               (0)  /* SSTBY condition bit */
#define R_SYSTEM_STCONR_STCON_MASK                0x3
#  define R_SYSTEM_STCONR_STCON_00                        (0 << R_SYSTEM_STCONR_STCON_SHIFT)  /* set this value in case of transferring to Software Standby Mode in using HOCO. */
#  define R_SYSTEM_STCONR_STCON_11                        (3 << R_SYSTEM_STCONR_STCON_SHIFT)  /* set this value in case of transferring to Software Standby Mode in using expect for HOCO. */

/* FWEPROR Register bit definitions */
#define R_SYSTEM_FWEPROR_FLWE_SHIFT               (0)  /* Flash Programming and Erasure */
#define R_SYSTEM_FWEPROR_FLWE_MASK                0x3
#  define R_SYSTEM_FWEPROR_FLWE_00                        (0 << R_SYSTEM_FWEPROR_FLWE_SHIFT)  /* Prohibits programming and erasure of the code flash, data flash or blank checking. */
#  define R_SYSTEM_FWEPROR_FLWE_01                        (1 << R_SYSTEM_FWEPROR_FLWE_SHIFT)  /* Permits programming and erasure of the code flash, data flash or blank checking. */
#  define R_SYSTEM_FWEPROR_FLWE_10                        (2 << R_SYSTEM_FWEPROR_FLWE_SHIFT)  /* Prohibits programming and erasure of the code flash, data flash or blank checking. */
#  define R_SYSTEM_FWEPROR_FLWE_11                        (3 << R_SYSTEM_FWEPROR_FLWE_SHIFT)  /* Prohibits programming and erasure of the code flash, data flash or blank checking. */

/* VBATTMONR Register bit definitions */
#define R_SYSTEM_VBATTMONR_VBATTMON               (1 << 0)  /* VBATT Voltage Monitor Bit */

/* VBTCR1 Register bit definitions */
#define R_SYSTEM_VBTCR1_BPWSWSTP                  (1 << 0)  /* Battery Power supply Switch Stop */

/* DCDCCTL Register bit definitions */
#define R_SYSTEM_DCDCCTL_DCDCON                   (1 << 0)  /* LDO/DCDC on/off Control bit */

#define R_SYSTEM_DCDCCTL_OCPEN                    (1 << 1)  /* DCDC OCP Function Enable bit */

#define R_SYSTEM_DCDCCTL_STOPZA                   (1 << 4)  /* DCDC IO Buffer Power Control bit */

#define R_SYSTEM_DCDCCTL_LCBOOST                  (1 << 5)  /* LDO LCBOOST Mode Control bit */

#define R_SYSTEM_DCDCCTL_FST                      (1 << 6)  /* DCDC Fast Startup */

#define R_SYSTEM_DCDCCTL_PD                       (1 << 7)  /* DCDC VREF Generate Disable bit */

/* VCCSEL Register bit definitions */
#define R_SYSTEM_VCCSEL_VCCSEL_SHIFT              (0)  /* DCDC Working Voltage Level Selection */
#define R_SYSTEM_VCCSEL_VCCSEL_MASK               0x3
#  define R_SYSTEM_VCCSEL_VCCSEL_00                       (0 << R_SYSTEM_VCCSEL_VCCSEL_SHIFT)  /* 2.7V <= VCC < 3.6V */
#  define R_SYSTEM_VCCSEL_VCCSEL_01                       (1 << R_SYSTEM_VCCSEL_VCCSEL_SHIFT)  /* 3.6V <= VCC < 4.5V */
#  define R_SYSTEM_VCCSEL_VCCSEL_10                       (2 << R_SYSTEM_VCCSEL_VCCSEL_SHIFT)  /* 4.5V <= VCC <= 5.5V */
#  define R_SYSTEM_VCCSEL_VCCSEL_11                       (3 << R_SYSTEM_VCCSEL_VCCSEL_SHIFT)  /* 2.4V <= VCC < 2.7V */

/* SOMRG Register bit definitions */
#define R_SYSTEM_SOMRG_SOSCMRG_SHIFT              (0)  /* Sub Clock Oscillator Margin check Switching */
#define R_SYSTEM_SOMRG_SOSCMRG_MASK               0x3
#  define R_SYSTEM_SOMRG_SOSCMRG_00                       (0 << R_SYSTEM_SOMRG_SOSCMRG_SHIFT)  /* Normal Current */
#  define R_SYSTEM_SOMRG_SOSCMRG_01                       (1 << R_SYSTEM_SOMRG_SOSCMRG_SHIFT)  /* Lower Margin check */
#  define R_SYSTEM_SOMRG_SOSCMRG_10                       (2 << R_SYSTEM_SOMRG_SOSCMRG_SHIFT)  /* Upper Margin check */

/* VBTCR2 Register bit definitions */
#define R_SYSTEM_VBTCR2_VBTLVDEN                  (1 << 4)  /* VBATT Pin Low Voltage Detect Enable Bit */

#define R_SYSTEM_VBTCR2_VBTLVDLVL_SHIFT           (6)  /* VBATT Pin Voltage Low Voltage Detect Level Select Bit */
#define R_SYSTEM_VBTCR2_VBTLVDLVL_MASK            0xc0
#  define R_SYSTEM_VBTCR2_VBTLVDLVL_00                    (0 << R_SYSTEM_VBTCR2_VBTLVDLVL_SHIFT)  /* 2.7V */
#  define R_SYSTEM_VBTCR2_VBTLVDLVL_01                    (1 << R_SYSTEM_VBTCR2_VBTLVDLVL_SHIFT)  /* Setting prohibited */
#  define R_SYSTEM_VBTCR2_VBTLVDLVL_10                    (2 << R_SYSTEM_VBTCR2_VBTLVDLVL_SHIFT)  /* 2.3V */
#  define R_SYSTEM_VBTCR2_VBTLVDLVL_11                    (3 << R_SYSTEM_VBTCR2_VBTLVDLVL_SHIFT)  /* 2.1V */

/* VBTSR Register bit definitions */
#define R_SYSTEM_VBTSR_VBTRDF                     (1 << 0)  /* VBAT_R Reset Detect Flag */

#define R_SYSTEM_VBTSR_VBTBLDF                    (1 << 1)  /* VBATT Battery Low voltage Detect Flag */

#define R_SYSTEM_VBTSR_VBTRVLD                    (1 << 4)  /* VBATT_R Valid */

/* VBTCMPCR Register bit definitions */
#define R_SYSTEM_VBTCMPCR_VBTCMPE                 (1 << 0)  /* VBATT pin low voltage detect circuit output enable */

/* VBTLVDICR Register bit definitions */
#define R_SYSTEM_VBTLVDICR_VBTLVDIE               (1 << 0)  /* VBATT Pin Low Voltage Detect Interrupt Enable bit */

#define R_SYSTEM_VBTLVDICR_VBTLVDISEL             (1 << 1)  /* Pin Low Voltage Detect Interrupt Select bit */

/* VBTWCTLR Register bit definitions */
#define R_SYSTEM_VBTWCTLR_VWEN                    (1 << 0)  /* VBATT wakeup enable */

/* VBTWCH0OTSR Register bit definitions */
#define R_SYSTEM_VBTWCH0OTSR_CH0VCH1TE            (1 << 1)  /* VBATWIO0 Output VBATWIO1 Trigger Enable */

#define R_SYSTEM_VBTWCH0OTSR_CH0VCH2TE            (1 << 2)  /* VBATWIO0 Output VBATWIO2 Trigger Enable */

#define R_SYSTEM_VBTWCH0OTSR_CH0VRTCTE            (1 << 3)  /* VBATWIO0 Output RTC Periodic Signal Enable */

#define R_SYSTEM_VBTWCH0OTSR_CH0VRTCATE           (1 << 4)  /* VBATWIO0 Output RTC Alarm Signal Enable */

#define R_SYSTEM_VBTWCH0OTSR_CH0VAGTUTE           (1 << 5)  /* CH0 Output AGT(ch1) underflow  Signal Enable */

/* VBTWCH1OTSR Register bit definitions */
#define R_SYSTEM_VBTWCH1OTSR_CH1VCH0TE            (1 << 0)  /* VBATWIO1 Output VBATWIO0 Trigger Enable */

#define R_SYSTEM_VBTWCH1OTSR_CH1VCH2TE            (1 << 2)  /* VBATWIO1 Output VBATWIO2 Trigger Enable */

#define R_SYSTEM_VBTWCH1OTSR_CH1VRTCTE            (1 << 3)  /* VBATWIO1 Output RTC Periodic Signal Enable */

#define R_SYSTEM_VBTWCH1OTSR_CH1VRTCATE           (1 << 4)  /* VBATWIO1 Output RTC Alarm Signal Enable */

#define R_SYSTEM_VBTWCH1OTSR_CH1VAGTUTE           (1 << 5)  /* CH1 Output AGT(ch1) underflow  Signal Enable */

/* VBTWCH2OTSR Register bit definitions */
#define R_SYSTEM_VBTWCH2OTSR_CH2VCH0TE            (1 << 0)  /* VBATWIO2 Output VBATWIO0 Trigger Enable */

#define R_SYSTEM_VBTWCH2OTSR_CH2VCH1TE            (1 << 1)  /* VBATWIO2 Output VBATWIO1 Trigger Enable */

#define R_SYSTEM_VBTWCH2OTSR_CH2VRTCTE            (1 << 3)  /* VBATWIO2 Output RTC Periodic Signal Enable */

#define R_SYSTEM_VBTWCH2OTSR_CH2VRTCATE           (1 << 4)  /* VBATWIO2 Output RTC Alarm Signal Enable */

#define R_SYSTEM_VBTWCH2OTSR_CH2VAGTUTE           (1 << 5)  /* CH2 Output AGT(CH2) underflow  Signal Enable */

/* VBTOCTLR Register bit definitions */
#define R_SYSTEM_VBTOCTLR_VCH0OEN                 (1 << 0)  /* VBATT Wakeup I/O 0 Output Enable */

#define R_SYSTEM_VBTOCTLR_VCH1OEN                 (1 << 1)  /* VBATT Wakeup I/O 1 Output Enable */

#define R_SYSTEM_VBTOCTLR_VCH2OEN                 (1 << 2)  /* VBATT Wakeup I/O 2 Output Enable */

#define R_SYSTEM_VBTOCTLR_VOUT0LSEL               (1 << 3)  /* VBATT Wakeup I/O 0 Output Level Selection */

#define R_SYSTEM_VBTOCTLR_VCOU1LSEL               (1 << 4)  /* VBATT Wakeup I/O 1 Output Level Selection */

#define R_SYSTEM_VBTOCTLR_VOUT2LSEL               (1 << 5)  /* VBATT Wakeup I/O 2 Output Level Selection */

/* VBTWTER Register bit definitions */
#define R_SYSTEM_VBTWTER_VCH0E                    (1 << 0)  /* VBATWIO0 Pin Enable */

#define R_SYSTEM_VBTWTER_VCH1E                    (1 << 1)  /* VBATWIO1 Pin Enable */

#define R_SYSTEM_VBTWTER_VCH2E                    (1 << 2)  /* VBATWIO2 Pin Enable */

#define R_SYSTEM_VBTWTER_VRTCIE                   (1 << 3)  /* RTC Periodic Signal Enable */

#define R_SYSTEM_VBTWTER_VRTCAE                   (1 << 4)  /* RTC Alarm Signal Enable */

#define R_SYSTEM_VBTWTER_VAGTUE                   (1 << 5)  /* AGT(ch1) underflow  Signal Enable */

/* VBTWEGR Register bit definitions */
#define R_SYSTEM_VBTWEGR_VCH0EG                   (1 << 0)  /* VBATWIO0 Wakeup Trigger Source Edge Select */

#define R_SYSTEM_VBTWEGR_VCH1EG                   (1 << 1)  /* VBATWIO1 Wakeup Trigger Source Edge Select */

#define R_SYSTEM_VBTWEGR_VCH2EG                   (1 << 2)  /* VBATWIO2 Wakeup Trigger Source Edge Select */

/* VBTWFR Register bit definitions */
#define R_SYSTEM_VBTWFR_VCH0F                     (1 << 0)  /* VBATWIO0 Wakeup Trigger Flag */

#define R_SYSTEM_VBTWFR_VCH1F                     (1 << 1)  /* VBATWIO1 Wakeup Trigger Flag */

#define R_SYSTEM_VBTWFR_VCH2F                     (1 << 2)  /* VBATWIO2 Wakeup Trigger Flag */

#define R_SYSTEM_VBTWFR_VRTCIF                    (1 << 3)  /* VBATT RTC-Interval  Wakeup Trigger Flag */

#define R_SYSTEM_VBTWFR_VRTCAF                    (1 << 4)  /* VBATT RTC-Alarm Wakeup Trigger Flag */

#define R_SYSTEM_VBTWFR_VAGTUF                    (1 << 5)  /* AGT(ch1) underflow   VBATT Wakeup Trigger Flag */

/* DPSBYCR Register bit definitions */
#define R_SYSTEM_DPSBYCR_DEEPCUT_SHIFT            (0)  /* Power-Supply Control */
#define R_SYSTEM_DPSBYCR_DEEPCUT_MASK             0x3
#  define R_SYSTEM_DPSBYCR_DEEPCUT_00                     (0 << R_SYSTEM_DPSBYCR_DEEPCUT_SHIFT)  /* Power to the standby RAM, Low-speed on-chip oscillator, AGTn, and USBFS/HS resume detecting unit is supplied in deep software standby mode. */
#  define R_SYSTEM_DPSBYCR_DEEPCUT_01                     (1 << R_SYSTEM_DPSBYCR_DEEPCUT_SHIFT)  /* Power to the standby RAM, Low-speed on-chip oscillator, AGTn, and USBFS/HS resume detecting unit is not supplied in deep software standby mode. */
#  define R_SYSTEM_DPSBYCR_DEEPCUT_10                     (2 << R_SYSTEM_DPSBYCR_DEEPCUT_SHIFT)  /* Setting prohibited.  */
#  define R_SYSTEM_DPSBYCR_DEEPCUT_11                     (3 << R_SYSTEM_DPSBYCR_DEEPCUT_SHIFT)  /* Power to the standby RAM, Low-speed on-chip oscillator, AGTn, and USBFS/HS resume detecting unit is supplied in deep software standby mode. In addition, LVD is disabled and the low power function in a power-on reset circuit is enabled. */

#define R_SYSTEM_DPSBYCR_DCSSMODE_SHIFT           (2)  /* DCDC SSMODE */
#define R_SYSTEM_DPSBYCR_DCSSMODE_MASK            0xc

#define R_SYSTEM_DPSBYCR_IOKEEP                   (1 << 6)  /* I/O Port Retention */

#define R_SYSTEM_DPSBYCR_DPSBY                    (1 << 7)  /* Deep Software Standby */

/* DPSIER0 Register bit definitions */
#define R_SYSTEM_DPSIER0_DIRQ_SE                  (1 << 0)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER0_DIRQ0E                   (1 << 0)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER0_DIRQ1E                   (1 << 1)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER0_DIRQ2E                   (1 << 2)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER0_DIRQ3E                   (1 << 3)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER0_DIRQ4E                   (1 << 4)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER0_DIRQ5E                   (1 << 5)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER0_DIRQ6E                   (1 << 6)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER0_DIRQ7E                   (1 << 7)  /* IRQ-DS Pin Enable */

/* DPSIER1 Register bit definitions */
#define R_SYSTEM_DPSIER1_DIRQ_SE                  (1 << 0)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER1_DIRQ8E                   (1 << 0)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER1_DIRQ9E                   (1 << 1)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER1_DIRQ10E                  (1 << 2)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER1_DIRQ11E                  (1 << 3)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER1_DIRQ12E                  (1 << 4)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER1_DIRQ13E                  (1 << 5)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER1_DIRQ14E                  (1 << 6)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER1_DIRQ15E                  (1 << 7)  /* IRQ-DS Pin Enable */

/* DPSIER2 Register bit definitions */
#define R_SYSTEM_DPSIER2_DPVD1IE                  (1 << 0)  /* PVD1 Deep Standby Cancel Signal Enable */

#define R_SYSTEM_DPSIER2_DPVD2IE                  (1 << 1)  /* PVD2 Deep Standby Cancel Signal Enable */

#define R_SYSTEM_DPSIER2_DRTCIIE                  (1 << 2)  /* RTC Interval interrupt Deep Standby Cancel Signal Enable */

#define R_SYSTEM_DPSIER2_DRTCAIE                  (1 << 3)  /* RTC Alarm interrupt Deep Standby Cancel Signal Enable */

#define R_SYSTEM_DPSIER2_DNMIE                    (1 << 4)  /* NMI Pin Enable */

#define R_SYSTEM_DPSIER2_DPVD3IE                  (1 << 5)  /* PVD3 Deep Standby Cancel Signal Enable */

/* DPSIER3 Register bit definitions */
#define R_SYSTEM_DPSIER3_DUSBFSIE                 (1 << 0)  /* USBFS Suspend/Resume Deep Standby Cancel Signal Enable */

#define R_SYSTEM_DPSIER3_DUSBHSIE                 (1 << 1)  /* USBHS Suspend/Resume Deep Standby Cancel Signal Enable */

#define R_SYSTEM_DPSIER3_DULPT0IE                 (1 << 2)  /* ULPT0 Overflow Deep Standby Cancel Signal Enable */

#define R_SYSTEM_DPSIER3_DULPT1IE                 (1 << 3)  /* ULPT1 Overflow Deep Standby Cancel Signal Enable */

#define R_SYSTEM_DPSIER3_DIWDTIE                  (1 << 5)  /* IWDT Overflow Deep Standby Cancel Signal Enable */

#define R_SYSTEM_DPSIER3_DSOSTDIE                 (1 << 6)  /* Sub-clock Oscillation stop detection Deep Standby Cancel Signal Enable */

#define R_SYSTEM_DPSIER3_DVBATTADIE               (1 << 7)  /* VBATT Tamper Detection Deep Standby Cancel Signal Enable */

/* DPSIFR0 Register bit definitions */
#define R_SYSTEM_DPSIFR0_DIRQ_SF                  (1 << 0)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR0_DIRQ0F                   (1 << 0)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR0_DIRQ1F                   (1 << 1)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR0_DIRQ2F                   (1 << 2)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR0_DIRQ3F                   (1 << 3)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR0_DIRQ4F                   (1 << 4)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR0_DIRQ5F                   (1 << 5)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR0_DIRQ6F                   (1 << 6)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR0_DIRQ7F                   (1 << 7)  /* IRQ-DS Pin Deep Standby Cancel Flag */

/* DPSIFR1 Register bit definitions */
#define R_SYSTEM_DPSIFR1_DIRQ_SF                  (1 << 0)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR1_DIRQ8F                   (1 << 0)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR1_DIRQ9F                   (1 << 1)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR1_DIRQ10F                  (1 << 2)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR1_DIRQ11F                  (1 << 3)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR1_DIRQ12F                  (1 << 4)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR1_DIRQ13F                  (1 << 5)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR1_DIRQ14F                  (1 << 6)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR1_DIRQ15F                  (1 << 7)  /* IRQ-DS Pin Deep Standby Cancel Flag */

/* DPSIFR2 Register bit definitions */
#define R_SYSTEM_DPSIFR2_DPVD1IF                  (1 << 0)  /* PVD1 Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR2_DPVD2IF                  (1 << 1)  /* PVD2 Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR2_DRTCIIF                  (1 << 2)  /* RTC Interval interrupt Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR2_DRTCAIF                  (1 << 3)  /* RTC Alarm interrupt Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR2_DNMIF                    (1 << 4)  /* NMI Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR2_DPVD3IF                  (1 << 5)  /* PVD5 Deep Standby Cancel Flag */

/* DPSIFR3 Register bit definitions */
#define R_SYSTEM_DPSIFR3_DUSBFSIF                 (1 << 0)  /* USBFS Suspend/Resume Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR3_DUSBHSIF                 (1 << 1)  /* USBHS Suspend/Resume Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR3_DULPT0IF                 (1 << 2)  /* ULPT0 Overflow Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR3_DULPT1IF                 (1 << 3)  /* ULPT1 Overflow Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR3_DIWDTIF                  (1 << 5)  /* IWDT Overflow Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR3_DSOSTDIF                 (1 << 6)  /* Sub-clock Oscillation stop detection Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR3_DVBATTADIF               (1 << 7)  /* VBATT Tamper Detection Deep Standby Cancel Flag */

/* DPSIEGR0 Register bit definitions */
#define R_SYSTEM_DPSIEGR0_DIRQ_SEG                (1 << 0)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR0_DIRQ0EG                 (1 << 0)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR0_DIRQ1EG                 (1 << 1)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR0_DIRQ2EG                 (1 << 2)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR0_DIRQ3EG                 (1 << 3)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR0_DIRQ4EG                 (1 << 4)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR0_DIRQ5EG                 (1 << 5)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR0_DIRQ6EG                 (1 << 6)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR0_DIRQ7EG                 (1 << 7)  /* IRQ-DS Pin Edge Select */

/* DPSIEGR1 Register bit definitions */
#define R_SYSTEM_DPSIEGR1_DIRQ_SEG                (1 << 0)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR1_DIRQ8EG                 (1 << 0)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR1_DIRQ9EG                 (1 << 1)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR1_DIRQ10EG                (1 << 2)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR1_DIRQ11EG                (1 << 3)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR1_DIRQ12EG                (1 << 4)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR1_DIRQ13EG                (1 << 5)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR1_DIRQ14EG                (1 << 6)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR1_DIRQ15EG                (1 << 7)  /* IRQ-DS Pin Edge Select */

/* DPSIEGR2 Register bit definitions */
#define R_SYSTEM_DPSIEGR2_DLVD1IEG                (1 << 0)  /* LVD1 Edge Select */

#define R_SYSTEM_DPSIEGR2_DLVD2IEG                (1 << 1)  /* LVD2 Edge Select */

#define R_SYSTEM_DPSIEGR2_DNMIEG                  (1 << 4)  /* NMI Pin Edge Select */

#define R_SYSTEM_DPSIEGR2_DLVD3IEG                (1 << 5)  /* LVD3 Edge Select */

/* DPSIEGR3 Register bit definitions */
#define R_SYSTEM_DPSIEGR3_DIRQ_SEG                (1 << 0)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR3_DIRQ16EG                (1 << 0)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR3_DIRQ17EG                (1 << 1)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR3_DIRQ18EG                (1 << 2)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR3_DIRQ19EG                (1 << 3)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR3_DIRQ20EG                (1 << 4)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR3_DIRQ21EG                (1 << 5)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR3_DIRQ22EG                (1 << 6)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR3_DIRQ23EG                (1 << 7)  /* IRQ-DS Pin Edge Select */

/* SYOCDCR Register bit definitions */
#define R_SYSTEM_SYOCDCR_DOCDF                    (1 << 0)  /* Deep Standby OCD flag */

#define R_SYSTEM_SYOCDCR_DBGEN                    (1 << 7)  /* Debugger Enable bit */

/* RSTSR0 Register bit definitions */
#define R_SYSTEM_RSTSR0_PORF                      (1 << 0)  /* Power-On Reset Detect Flag */

#define R_SYSTEM_RSTSR0_LVD0RF                    (1 << 1)  /* Voltage Monitor 0 Reset Detect Flag */

#define R_SYSTEM_RSTSR0_LVD1RF                    (1 << 2)  /* Voltage Monitor 1 Reset Detect Flag */

#define R_SYSTEM_RSTSR0_LVD2RF                    (1 << 3)  /* Voltage Monitor 2 Reset Detect Flag */

#define R_SYSTEM_RSTSR0_LVD4RF                    (1 << 5)  /* Voltage Monitor 4 Reset Detect Flag */

#define R_SYSTEM_RSTSR0_LVD5RF                    (1 << 6)  /* Voltage Monitor 5 Reset Detect Flag */

#define R_SYSTEM_RSTSR0_DPSRSTF                   (1 << 7)  /* Deep Software Standby Reset Flag */

/* RSTSR2 Register bit definitions */
#define R_SYSTEM_RSTSR2_CWSF                      (1 << 0)  /* Cold/Warm Start Determination Flag */

/* RSTSR3 Register bit definitions */
#define R_SYSTEM_RSTSR3_CVMRF                     (1 << 0)  /* Core Voltage Monitor Reset Detect Flag */

#define R_SYSTEM_RSTSR3_OCPRF                     (1 << 4)  /* Overcurrent Protection Reset Detect Flag */

#define R_SYSTEM_RSTSR3_TEMPRF                    (1 << 7)  /* Temperature Monitor Reset Detect Flag */

/* MOMCR Register bit definitions */
#define R_SYSTEM_MOMCR_MODRV0_SHIFT               (1)  /* Main Clock Oscillator Drive Capability 0 Switching */
#define R_SYSTEM_MOMCR_MODRV0_MASK                0xe

#define R_SYSTEM_MOMCR_MOSEL                      (1 << 6)  /* Main Clock Oscillator Switching */

/* LVDCMPCR Register bit definitions */
#define R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT            (0)  /* Detection Voltage Level Select(Standard voltage during drop in voltage) */
#define R_SYSTEM_LVDCMPCR_LVDLVL_MASK             0x1f
#  define R_SYSTEM_LVDCMPCR_LVDLVL_00000                  (0 << R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT)  /* 4.29V (Vdetm_0)  */
#  define R_SYSTEM_LVDCMPCR_LVDLVL_00001                  (1 << R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT)  /* 4.16V (Vdetm_1)  */
#  define R_SYSTEM_LVDCMPCR_LVDLVL_00010                  (2 << R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT)  /* 4.03V (Vdetm_2)  */
#  define R_SYSTEM_LVDCMPCR_LVDLVL_00011                  (3 << R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT)  /* 3.86V (Vdetm_3)  */
#  define R_SYSTEM_LVDCMPCR_LVDLVL_00100                  (4 << R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT)  /* 3.14V (Vdetm_4)  */
#  define R_SYSTEM_LVDCMPCR_LVDLVL_00101                  (5 << R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT)  /* 3.10V (Vdetm_5)  */
#  define R_SYSTEM_LVDCMPCR_LVDLVL_00110                  (6 << R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT)  /* 3.08V (Vdetm_6)  */
#  define R_SYSTEM_LVDCMPCR_LVDLVL_00111                  (7 << R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT)  /* 2.85V (Vdetm_7)  */
#  define R_SYSTEM_LVDCMPCR_LVDLVL_01000                  (8 << R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT)  /* 2.83V (Vdetm_8)  */
#  define R_SYSTEM_LVDCMPCR_LVDLVL_01001                  (9 << R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT)  /* 2.80V (Vdetm_9)  */
#  define R_SYSTEM_LVDCMPCR_LVDLVL_01010                  (10 << R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT)  /* 2.62V (Vdetm_10)  */
#  define R_SYSTEM_LVDCMPCR_LVDLVL_01011                  (11 << R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT)  /* 2.33V (Vdetm_11)  */
#  define R_SYSTEM_LVDCMPCR_LVDLVL_01100                  (12 << R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT)  /* 1.90V (Vdetm_12)  */
#  define R_SYSTEM_LVDCMPCR_LVDLVL_01101                  (13 << R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT)  /* 1.86V (Vdetm_13)  */
#  define R_SYSTEM_LVDCMPCR_LVDLVL_01110                  (14 << R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT)  /* 1.74V (Vdetm_14)  */
#  define R_SYSTEM_LVDCMPCR_LVDLVL_01111                  (15 << R_SYSTEM_LVDCMPCR_LVDLVL_SHIFT)  /* 1.71V (Vdetm_15)  */

#define R_SYSTEM_LVDCMPCR_LVDE                    (1 << 7)  /* Voltage Detection Enable */

/* LVDCR Register bit definitions */
#define R_SYSTEM_LVDCR_RIE                        (1 << 0)  /* Voltage Monitor Interrupt/Reset Enable */

#define R_SYSTEM_LVDCR_DFDIS                      (1 << 1)  /* Voltage Monitor Digital Filter Disable Mode Select */

#define R_SYSTEM_LVDCR_CMPE                       (1 << 2)  /* Voltage Monitor Circuit Comparison Result Output Enable */

#define R_SYSTEM_LVDCR_FSAMP_SHIFT                (4)  /* Sampling Clock Select */
#define R_SYSTEM_LVDCR_FSAMP_MASK                 0x30
#  define R_SYSTEM_LVDCR_FSAMP_00                         (0 << R_SYSTEM_LVDCR_FSAMP_SHIFT)  /* 1/2 LOCO frequency */
#  define R_SYSTEM_LVDCR_FSAMP_01                         (1 << R_SYSTEM_LVDCR_FSAMP_SHIFT)  /* 1/4 LOCO frequency */
#  define R_SYSTEM_LVDCR_FSAMP_10                         (2 << R_SYSTEM_LVDCR_FSAMP_SHIFT)  /* 1/8 LOCO frequency */
#  define R_SYSTEM_LVDCR_FSAMP_11                         (3 << R_SYSTEM_LVDCR_FSAMP_SHIFT)  /* 1/16 LOCO frequency */

#define R_SYSTEM_LVDCR_RI                         (1 << 6)  /* Voltage Monitor Circuit Mode Select */

#define R_SYSTEM_LVDCR_RN                         (1 << 7)  /* Voltage Monitor Reset Negate Select */

/* VBATTMNSELR Register bit definitions */
#define R_SYSTEM_VBATTMNSELR_VBATTMNSEL           (1 << 0)  /* VBATT Low Voltage Detect Function Select Bit */

/* VBTBPCR1 Register bit definitions */
#define R_SYSTEM_VBTBPCR1_BPWSWSTP                (1 << 0)  /* Battery Power Supply Switch Stop */

/* LPSCR Register bit definitions */
#define R_SYSTEM_LPSCR_LPMD_SHIFT                 (0)  /* Low power mode setting bit */
#define R_SYSTEM_LPSCR_LPMD_MASK                  0xf

/* SSCR1 Register bit definitions */
#define R_SYSTEM_SSCR1_SS2FR                      (1 << 0)  /* Software Standby 2 Fast Return */

#define R_SYSTEM_SSCR1_SS2LP_SHIFT                (2)  /* Software Standby 2 Low Power Select */
#define R_SYSTEM_SSCR1_SS2LP_MASK                 0xc

/* SVSCR Register bit definitions */
#define R_SYSTEM_SVSCR_SVSCM_SHIFT                (0)  /* SSTBY Voltage Scaling Control Mode */
#define R_SYSTEM_SVSCR_SVSCM_MASK                 0x7

/* LVOCR Register bit definitions */
#define R_SYSTEM_LVOCR_LVO0E                      (1 << 0)  /* Low Voltage Operation 0 Enable */

#define R_SYSTEM_LVOCR_LVO1E                      (1 << 1)  /* Low Voltage Operation 1 Enable */

/* MWMCR Register bit definitions */
#define R_SYSTEM_MWMCR_MWM_SHIFT                  (0)  /* MRAM-OTP Write Mode */
#define R_SYSTEM_MWMCR_MWM_MASK                   0x3

/* SYRSTMSK0 Register bit definitions */
#define R_SYSTEM_SYRSTMSK0_IWDTMASK               (1 << 0)  /* Independent Watchdog Timer Reset Mask */

#define R_SYSTEM_SYRSTMSK0_WDT0MASK               (1 << 1)  /* Watchdog Timer Reset Mask */

#define R_SYSTEM_SYRSTMSK0_SWMASK                 (1 << 2)  /* Software Reset Mask */

#define R_SYSTEM_SYRSTMSK0_CLU0MASK               (1 << 4)  /* CPU Lockup Reset Mask */

#define R_SYSTEM_SYRSTMSK0_LM0MASK                (1 << 5)  /* Local Memory 0 Error Reset Mask */

#define R_SYSTEM_SYRSTMSK0_CMMASK                 (1 << 6)  /* Common Memory Error Reset Mask */

#define R_SYSTEM_SYRSTMSK0_BUSMASK                (1 << 7)  /* Bus Error Reset Mask */

/* SYRSTMSK1 Register bit definitions */
#define R_SYSTEM_SYRSTMSK1_WDT1MASK               (1 << 1)  /* CPU1 Watchdog Timer Reset Mask */

#define R_SYSTEM_SYRSTMSK1_CLU1MASK               (1 << 4)  /* CPU1 Lockup Reset Mask */

#define R_SYSTEM_SYRSTMSK1_LM1MASK                (1 << 5)  /* Local Memory 1 Error Reset Mask */

/* SYRSTMSK2 Register bit definitions */
#define R_SYSTEM_SYRSTMSK2_PVD1MASK               (1 << 0)  /* Voltage Monitor 1 Reset Mask */

#define R_SYSTEM_SYRSTMSK2_PVD2MASK               (1 << 1)  /* Voltage Monitor 2 Reset Mask */

/* TEMPRCR Register bit definitions */
#define R_SYSTEM_TEMPRCR_TEMPREN                  (1 << 0)  /* Temperature Monitor Reset Enable */

#define R_SYSTEM_TEMPRCR_TSNEN                    (1 << 1)  /* Temperature Monitor Sensor Enable */

#define R_SYSTEM_TEMPRCR_CMPEN                    (1 << 2)  /* Comparator Enable */

#define R_SYSTEM_TEMPRCR_TSNKEEP                  (1 << 3)  /* Temperature Monitor Sensor Latch Control */

/* TEMPRLR Register bit definitions */
#define R_SYSTEM_TEMPRLR_LOCK                     (1 << 0)  /* Temperature Monitor Reset Control Register Lock */

/* LDOSCR Register bit definitions */
#define R_SYSTEM_LDOSCR_LDOSTP_S                  (1 << 0)  /* LDO%s Stop */

#define R_SYSTEM_LDOSCR_LDOSTP0                   (1 << 0)  /* LDO0 Stop */

#define R_SYSTEM_LDOSCR_LDOSTP1                   (1 << 1)  /* LDO1 Stop */

#define R_SYSTEM_LDOSCR_LDOSTP2                   (1 << 2)  /* LDO2 Stop */

#define R_SYSTEM_LDOSCR_LDOSTP3                   (1 << 3)  /* LDO3 Stop */

#define R_SYSTEM_LDOSCR_LDOSTP4                   (1 << 4)  /* LDO4 Stop */

#define R_SYSTEM_LDOSCR_LDOSTP5                   (1 << 5)  /* LDO5 Stop */

#define R_SYSTEM_LDOSCR_LDOSTP6                   (1 << 6)  /* LDO6 Stop */

#define R_SYSTEM_LDOSCR_LDOSTP7                   (1 << 7)  /* LDO7 Stop */

/* PLLLDOCR Register bit definitions */
#define R_SYSTEM_PLLLDOCR_LDOSTP                  (1 << 0)  /* LDO Stop */

#define R_SYSTEM_PLLLDOCR_SKEEP                   (1 << 1)  /* STBY Keep */

/* HOCOLDOCR Register bit definitions */
#define R_SYSTEM_HOCOLDOCR_LDOSTP                 (1 << 0)  /* LDO0 Stop */

#define R_SYSTEM_HOCOLDOCR_SKEEP                  (1 << 1)  /* STBY Keep */

/* MOMCR2 Register bit definitions */
#define R_SYSTEM_MOMCR2_MOMODE                    (1 << 0)  /* Main Clock Oscillator Mode Select */

/* LVDFCR Register bit definitions */
#define R_SYSTEM_LVDFCR_RHSEL                     (1 << 0)  /* Rise Hysteresis Select */

/* PVDLR Register bit definitions */
#define R_SYSTEM_PVDLR_LOCK                       (1 << 0)  /* LOCK control */

/* DPSIER4 Register bit definitions */
#define R_SYSTEM_DPSIER4_DIRQ_SE                  (1 << 0)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER4_DIRQ16E                  (1 << 0)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER4_DIRQ17E                  (1 << 1)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER4_DIRQ18E                  (1 << 2)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER4_DIRQ19E                  (1 << 3)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER4_DIRQ20E                  (1 << 4)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER4_DIRQ21E                  (1 << 5)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER4_DIRQ22E                  (1 << 6)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER4_DIRQ23E                  (1 << 7)  /* IRQ-DS Pin Enable */

/* DPSIER5 Register bit definitions */
#define R_SYSTEM_DPSIER5_DIRQ_SE                  (1 << 0)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER5_DIRQ24E                  (1 << 0)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER5_DIRQ25E                  (1 << 1)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER5_DIRQ26E                  (1 << 2)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER5_DIRQ27E                  (1 << 3)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER5_DIRQ28E                  (1 << 4)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER5_DIRQ29E                  (1 << 5)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER5_DIRQ30E                  (1 << 6)  /* IRQ-DS Pin Enable */

#define R_SYSTEM_DPSIER5_DIRQ31E                  (1 << 7)  /* IRQ-DS Pin Enable */

/* DPSIFR4 Register bit definitions */
#define R_SYSTEM_DPSIFR4_DIRQ_SF                  (1 << 0)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR4_DIRQ16F                  (1 << 0)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR4_DIRQ17F                  (1 << 1)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR4_DIRQ18F                  (1 << 2)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR4_DIRQ19F                  (1 << 3)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR4_DIRQ20F                  (1 << 4)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR4_DIRQ21F                  (1 << 5)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR4_DIRQ22F                  (1 << 6)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR4_DIRQ23F                  (1 << 7)  /* IRQ-DS Pin Deep Standby Cancel Flag */

/* DPSIFR5 Register bit definitions */
#define R_SYSTEM_DPSIFR5_DIRQ_SF                  (1 << 0)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR5_DIRQ24F                  (1 << 0)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR5_DIRQ25F                  (1 << 1)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR5_DIRQ26F                  (1 << 2)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR5_DIRQ27F                  (1 << 3)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR5_DIRQ28F                  (1 << 4)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR5_DIRQ29F                  (1 << 5)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR5_DIRQ30F                  (1 << 6)  /* IRQ-DS Pin Deep Standby Cancel Flag */

#define R_SYSTEM_DPSIFR5_DIRQ31F                  (1 << 7)  /* IRQ-DS Pin Deep Standby Cancel Flag */

/* DPSIEGR4 Register bit definitions */
#define R_SYSTEM_DPSIEGR4_DIRQ_SEG                (1 << 0)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR4_DIRQ24EG                (1 << 0)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR4_DIRQ25EG                (1 << 1)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR4_DIRQ26EG                (1 << 2)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR4_DIRQ27EG                (1 << 3)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR4_DIRQ28EG                (1 << 4)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR4_DIRQ29EG                (1 << 5)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR4_DIRQ30EG                (1 << 6)  /* IRQ-DS Pin Edge Select */

#define R_SYSTEM_DPSIEGR4_DIRQ31EG                (1 << 7)  /* IRQ-DS Pin Edge Select */

/* VBTSWMON Register bit definitions */
#define R_SYSTEM_VBTSWMON_VLVLMON_SHIFT           (0)  /* VDETBAT Level Monitor */
#define R_SYSTEM_VBTSWMON_VLVLMON_MASK            0x7

#define R_SYSTEM_VBTSWMON_VDETEMON                (1 << 4)  /* Voltage drop detection enable Monitor */

/* VBTSWSCR Register bit definitions */
#define R_SYSTEM_VBTSWSCR_VBTSWE                  (1 << 0)  /* LVDVBATSW output enable */

/* SOSCCR Register bit definitions */
#define R_SYSTEM_SOSCCR_SOSTP                     (1 << 0)  /* Sub-Clock Oscillator Stop */

/* SOMCR Register bit definitions */
#define R_SYSTEM_SOMCR_SODRV_SHIFT                (0)  /* Sub-Clock Oscillator Drive Capability Switching */
#define R_SYSTEM_SOMCR_SODRV_MASK                 0x3

#define R_SYSTEM_SOMCR_SOSEL                      (1 << 6)  /* Sub-Clock Oscillator Switching */

/* SOSTDCR Register bit definitions */
#define R_SYSTEM_SOSTDCR_SOSTDIE                  (1 << 0)  /* Sub-clock Oscillation Stop Detection Interrupt Enable */

#define R_SYSTEM_SOSTDCR_SOSTDE                   (1 << 7)  /* Sub-clock Oscillation Stop Detection Function Enable */

/* SOSTDSR Register bit definitions */
#define R_SYSTEM_SOSTDSR_SOSTDF                   (1 << 0)  /* Sub-clock Oscillation Stop Detection Flag */

/* VBTBER Register bit definitions */
#define R_SYSTEM_VBTBER_VBAE                      (1 << 3)  /* VBATT backup register access enable bit */

/* VBTBPCR2 Register bit definitions */
#define R_SYSTEM_VBTBPCR2_VDETLVL_SHIFT           (0)  /* VDETBAT Level Select */
#define R_SYSTEM_VBTBPCR2_VDETLVL_MASK            0x7
#  define R_SYSTEM_VBTBPCR2_VDETLVL_000                   (0 << R_SYSTEM_VBTBPCR2_VDETLVL_SHIFT)  /* 2.8V */
#  define R_SYSTEM_VBTBPCR2_VDETLVL_001                   (1 << R_SYSTEM_VBTBPCR2_VDETLVL_SHIFT)  /* 2.53V */
#  define R_SYSTEM_VBTBPCR2_VDETLVL_010                   (2 << R_SYSTEM_VBTBPCR2_VDETLVL_SHIFT)  /* 2.10V */
#  define R_SYSTEM_VBTBPCR2_VDETLVL_011                   (3 << R_SYSTEM_VBTBPCR2_VDETLVL_SHIFT)  /* 1.95V */
#  define R_SYSTEM_VBTBPCR2_VDETLVL_100                   (4 << R_SYSTEM_VBTBPCR2_VDETLVL_SHIFT)  /* 1.85V */
#  define R_SYSTEM_VBTBPCR2_VDETLVL_101                   (5 << R_SYSTEM_VBTBPCR2_VDETLVL_SHIFT)  /* 1.75V */
#  define R_SYSTEM_VBTBPCR2_VDETLVL_110                   (6 << R_SYSTEM_VBTBPCR2_VDETLVL_SHIFT)  /* 1.65V */
#  define R_SYSTEM_VBTBPCR2_VDETLVL_111                   (7 << R_SYSTEM_VBTBPCR2_VDETLVL_SHIFT)  /* prohibited (1.55V) */

#define R_SYSTEM_VBTBPCR2_VDETE                   (1 << 4)  /* Voltage drop detection enable */

/* VBTBPSR Register bit definitions */
#define R_SYSTEM_VBTBPSR_VBPORF                   (1 << 0)  /* VBATT_POR Flag */

#define R_SYSTEM_VBTBPSR_VBPORM                   (1 << 4)  /* VBATT_POR Monitor */

#define R_SYSTEM_VBTBPSR_BPWSWM                   (1 << 5)  /* Battery Power Supply Switch Status Monitor */

/* VBTADSR Register bit definitions */
#define R_SYSTEM_VBTADSR_VBTADF0                  (1 << 0)  /* VBATT Tamper Detection flag 0 */

#define R_SYSTEM_VBTADSR_VBTADF1                  (1 << 1)  /* VBATT Tamper Detection flag 1 */

#define R_SYSTEM_VBTADSR_VBTADF2                  (1 << 2)  /* VBATT Tamper Detection flag 2 */

/* VBTADCR1 Register bit definitions */
#define R_SYSTEM_VBTADCR1_VBTADIE0                (1 << 0)  /* VBATT Tamper Detection Interrupt Enable 0 */

#define R_SYSTEM_VBTADCR1_VBTADIE1                (1 << 1)  /* VBATT Tamper Detection Interrupt Enable 1 */

#define R_SYSTEM_VBTADCR1_VBTADIE2                (1 << 2)  /* VBATT Tamper Detection Interrupt Enable 2 */

#define R_SYSTEM_VBTADCR1_VBTADCLE0               (1 << 4)  /* VBATT Tamper Detection Backup Register Clear Enable 0 */

#define R_SYSTEM_VBTADCR1_VBTADCLE1               (1 << 5)  /* VBATT Tamper Detection Backup Register Clear Enable 1 */

#define R_SYSTEM_VBTADCR1_VBTADCLE2               (1 << 6)  /* VBATT Tamper Detection Backup Register Clear Enable 2 */

/* VBTADCR2 Register bit definitions */
#define R_SYSTEM_VBTADCR2_VBRTCES0                (1 << 0)  /* VBATT RTC Time Capture Event Source Select 0 */

#define R_SYSTEM_VBTADCR2_VBRTCES1                (1 << 1)  /* VBATT RTC Time Capture Event Source Select 1 */

#define R_SYSTEM_VBTADCR2_VBRTCES2                (1 << 2)  /* VBATT RTC Time Capture Event Source Select 2 */

/* VBTICTLR Register bit definitions */
#define R_SYSTEM_VBTICTLR_VCH0INEN                (1 << 0)  /* RTCIC0 Input Enable */

#define R_SYSTEM_VBTICTLR_VCH1INEN                (1 << 1)  /* RTCIC1 Input Enable */

#define R_SYSTEM_VBTICTLR_VCH2INEN                (1 << 2)  /* RTCIC2 Input Enable */

/* VBTICTLR2 Register bit definitions */
#define R_SYSTEM_VBTICTLR2_VCH0NCE                (1 << 0)  /* VBATT CH0 Input Noise Canceler Enable */

#define R_SYSTEM_VBTICTLR2_VCH1NCE                (1 << 1)  /* VBATT CH1 Input Noise Canceler Enable */

#define R_SYSTEM_VBTICTLR2_VCH2NCE                (1 << 2)  /* VBATT CH2 Input Noise Canceler Enable */

#define R_SYSTEM_VBTICTLR2_VCH0EG                 (1 << 4)  /* VBATT CH0 Input Edge Select */

#define R_SYSTEM_VBTICTLR2_VCH1EG                 (1 << 5)  /* VBATT CH1 Input Edge Select */

#define R_SYSTEM_VBTICTLR2_VCH2EG                 (1 << 6)  /* VBATT CH2 Input Edge Select */

/* VBTIMONR Register bit definitions */
#define R_SYSTEM_VBTIMONR_VCH0MON                 (1 << 0)  /* VBATT CH0 Input monitor */

#define R_SYSTEM_VBTIMONR_VCH1MON                 (1 << 1)  /* VBATT CH1 Input monitor */

#define R_SYSTEM_VBTIMONR_VCH2MON                 (1 << 2)  /* VBATT CH2 Input monitor */

/* VBTNCWCR Register bit definitions */
#define R_SYSTEM_VBTNCWCR_VINCW_SHIFT             (0)  /* VBATT Input Noise Canceler Width select */
#define R_SYSTEM_VBTNCWCR_VINCW_MASK              0x7
#  define R_SYSTEM_VBTNCWCR_VINCW_000                     (0 << R_SYSTEM_VBTNCWCR_VINCW_SHIFT)  /* 62.5us (SOSC)  */
#  define R_SYSTEM_VBTNCWCR_VINCW_001                     (1 << R_SYSTEM_VBTNCWCR_VINCW_SHIFT)  /* 62.5us (SOSC) prohibited */
#  define R_SYSTEM_VBTNCWCR_VINCW_010                     (2 << R_SYSTEM_VBTNCWCR_VINCW_SHIFT)  /* 62.5us (SOSC) prohibited */
#  define R_SYSTEM_VBTNCWCR_VINCW_011                     (3 << R_SYSTEM_VBTNCWCR_VINCW_SHIFT)  /* 62.5us (SOSC) prohibited */
#  define R_SYSTEM_VBTNCWCR_VINCW_100                     (4 << R_SYSTEM_VBTNCWCR_VINCW_SHIFT)  /* 31.25ms (R64CNT[0] 64Hz) */
#  define R_SYSTEM_VBTNCWCR_VINCW_101                     (5 << R_SYSTEM_VBTNCWCR_VINCW_SHIFT)  /* 62.5ms (R64CNT[1] 32Hz) */
#  define R_SYSTEM_VBTNCWCR_VINCW_110                     (6 << R_SYSTEM_VBTNCWCR_VINCW_SHIFT)  /* 125ms (R64CNT[2] 16Hz) */
#  define R_SYSTEM_VBTNCWCR_VINCW_111                     (7 << R_SYSTEM_VBTNCWCR_VINCW_SHIFT)  /* 125ms prohibited(R64CNT[2] 16Hz) */

/* VBTADCR3 Register bit definitions */
#define R_SYSTEM_VBTADCR3_VBTADZE0                (1 << 0)  /* VBATT Tamper Detection Zeroization Enable 0 */

#define R_SYSTEM_VBTADCR3_VBTADZE1                (1 << 1)  /* VBATT Tamper Detection Zeroization Enable 1 */

#define R_SYSTEM_VBTADCR3_VBTADZE2                (1 << 2)  /* VBATT Tamper Detection Zeroization Enable 2 */

/* VBTBKR Register bit definitions */
#define R_SYSTEM_VBTBKR_VBTBKR_SHIFT              (0)  /* VBTBKR is a 512-byte readable/writable register to store data powered by VBATT.The value of this register is retained even when VCC is not powered but VBATT is powered.VBTBKR is initialized by VBATT selected voltage power-on-reset. */
#define R_SYSTEM_VBTBKR_VBTBKR_MASK               0xff


/* Maximum number of channels */

#define SYSTEM_MAX_CHANNELS    128

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SYSTEM_H */

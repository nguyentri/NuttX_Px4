/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_adc_b.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ADC_B_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ADC_B_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ADC_B Base Address */
#ifndef R_ADC_B_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_ADC_B_BASE           0x40338000
#else
#define R_ADC_B_BASE           0x50338000
#endif
#endif

/* ADC_B Register Offsets */

#define R_ADC_B_ADCLKENR_OFFSET                   0x00000000  /* A/D Conversion Clock Enable Register */
#define R_ADC_B_ADCLKSR_OFFSET                    0x00000004  /* A/D Conversion Clock Status Register */
#define R_ADC_B_ADCLKCR_OFFSET                    0x00000008  /* A/D Conversion Clock Control Register */
#define R_ADC_B_ADSYCR_OFFSET                     0x0000000c  /* A/D Converter Synchronous Operation Control Register */
#define R_ADC_B_ADUSLPCR0_OFFSET                  0x00000010  /* A/D Converter Unit Sleep Control Register 0 */
#define R_ADC_B_ADUSLPCR1_OFFSET                  0x00000014  /* A/D Converter Unit Sleep Control Register 1 */
#define R_ADC_B_ADERINTCR_OFFSET                  0x00000020  /* A/D Conversion Error Interrupt Enable Register */
#define R_ADC_B_ADOVFINTCR_OFFSET                 0x00000024  /* A/D Conversion Overflow Interrupt Enable Register */
#define R_ADC_B_ADCALINTCR_OFFSET                 0x00000028  /* Calibration Interrupt Enable Register */
#define R_ADC_B_ADMDR_OFFSET                      0x00000040  /* A/D Converter Mode Selection Register */
#define R_ADC_B_ADGSPCR_OFFSET                    0x00000044  /* A/D Group Scan Priority Control Register */
#define R_ADC_B_ADSGER_OFFSET                     0x00000048  /* Scan Group Enable Register */
#define R_ADC_B_ADSGCR0_OFFSET                    0x0000004c  /* Scan Group Control Register 0 */
#define R_ADC_B_ADSGCR1_OFFSET                    0x00000050  /* Scan Group Control Register 1 */
#define R_ADC_B_ADSGCR2_OFFSET                    0x00000054  /* Scan Group Control Register 2 */
#define R_ADC_B_ADINTCR_OFFSET                    0x0000005c  /* Scan End Interrupt Enable Register */
#define R_ADC_B_ADSWNR0_OFFSET                    0x00000060  /* A/D conversion times per scan Register 0 */
#define R_ADC_B_ADSWNR1_OFFSET                    0x00000064  /* A/D conversion times per scan Register 1 */
#define R_ADC_B_ADDECCR_OFFSET                    0x00000080  /* One-channel Continuous Scan Mode Decimation Control Register */
#define R_ADC_B_ADACMDR_OFFSET                    0x00000084  /* A/D Converter Accuracy Mode Register */
/* ADTRGEXT%s Registers (0-8) */
#define R_ADC_B_ADTRGEXT_OFFSET(m)                (0x000000c0 + ((m) * 0x00000010))  /* External Trigger Enable Register %s */
/* ADTRGELC%s Registers (0-8) */
#define R_ADC_B_ADTRGELC_OFFSET(m)                (0x000000c4 + ((m) * 0x00000010))  /* ELC Trigger Enable Register %s */
/* ADTRGGPT%s Registers (0-8) */
#define R_ADC_B_ADTRGGPT_OFFSET(m)                (0x000000c8 + ((m) * 0x00000010))  /* GPT Trigger Enable Register %s */
#define R_ADC_B_ADTRGDLR0_OFFSET                  0x000001c0  /* A/D Conversion Start Trigger Delay Register 0 */
#define R_ADC_B_ADTRGDLR1_OFFSET                  0x000001c4  /* A/D Conversion Start Trigger Delay Register 1 */
#define R_ADC_B_ADTRGDLR2_OFFSET                  0x000001c8  /* A/D Conversion Start Trigger Delay Register 2 */
#define R_ADC_B_ADTRGDLR3_OFFSET                  0x000001cc  /* A/D Conversion Start Trigger Delay Register 3 */
#define R_ADC_B_ADTRGDLR4_OFFSET                  0x000001d0  /* A/D Conversion Start Trigger Delay Register 4 */
/* ADSGDCR%s Registers (0-8) */
#define R_ADC_B_ADSGDCR_OFFSET(m)                 (0x00000200 + ((m) * 0x00000004))  /* Scan Group Diagnosis Function Control Register %s */
#define R_ADC_B_ADSSTR0_OFFSET                    0x00000240  /* Sampling State Table Register 0 */
#define R_ADC_B_ADSSTR1_OFFSET                    0x00000244  /* Sampling State Table Register 1 */
#define R_ADC_B_ADSSTR2_OFFSET                    0x00000248  /* Sampling State Table Register 2 */
#define R_ADC_B_ADSSTR3_OFFSET                    0x0000024c  /* Sampling State Table Register 3 */
#define R_ADC_B_ADSSTR4_OFFSET                    0x00000250  /* Sampling State Table Register 4 */
#define R_ADC_B_ADSSTR5_OFFSET                    0x00000254  /* Sampling State Table Register 5 */
#define R_ADC_B_ADSSTR6_OFFSET                    0x00000258  /* Sampling State Table Register 6 */
#define R_ADC_B_ADSSTR7_OFFSET                    0x0000025c  /* Sampling State Table Register 7 */
#define R_ADC_B_ADCNVSTR_OFFSET                   0x00000260  /* A/D Conversion State Register */
#define R_ADC_B_ADCALSTCR_OFFSET                  0x00000264  /* A/D Converter Self-calibration State Register */
#define R_ADC_B_ADSHCR0_OFFSET                    0x00000280  /* Channel-dedicated Sample-and-hold Circuit Control Register 0 */
#define R_ADC_B_ADSHDCR0_OFFSET                   0x00000284  /* Channel-dedicated Sample-and-hold Circuit Diagnosis Control Register 0 */
#define R_ADC_B_ADSHSTR0_OFFSET                   0x00000288  /* Channel-dedicated Sample-and-hold Circuit State Register 0 */
#define R_ADC_B_ADSHCR1_OFFSET                    0x0000028c  /* Channel-dedicated Sample-and-hold Circuit Control Register 1 */
#define R_ADC_B_ADSHDCR1_OFFSET                   0x00000290  /* Channel-dedicated Sample-and-hold Circuit Diagnosis Control Register 1 */
#define R_ADC_B_ADSHSTR1_OFFSET                   0x00000294  /* Channel-dedicated Sample-and-hold Circuit State Register 1 */
#define R_ADC_B_ADCALSHCR_OFFSET                  0x000002b0  /* Channel-dedicated Sample-and-hold Circuit Self-calibration State Register */
#define R_ADC_B_ADSHSBPCR_OFFSET                  0x00000310  /* Channel-dedicated Sample-and-hold Circuit Single-ended Input Mode Bypass Control Register */
#define R_ADC_B_ADSHDBPCR_OFFSET                  0x00000314  /* Channel-dedicated Sample-and-hold Circuit Differential Input Mode Bypass Control Register */
#define R_ADC_B_ADSHSDCR0_OFFSET                  0x00000318  /* Channel-dedicated Sample-and-hold Circuit Self-diagnosis Control Register 0 */
#define R_ADC_B_ADSHSDCR1_OFFSET                  0x0000031c  /* Channel-dedicated Sample-and-hold Circuit Self-diagnosis Control Register 1 */
#define R_ADC_B_ADREFCR_OFFSET                    0x00000320  /* Internal Reference Voltage Monitor Enable Register */
/* ADDFSR%s Registers (0-1) */
#define R_ADC_B_ADDFSR_OFFSET(m)                  (0x00000340 + ((m) * 0x00000004))  /* A/D Converter Digital Filter Selection Register %s */
/* ADUOFTR%s Registers (0-7) */
#define R_ADC_B_ADUOFTR_OFFSET(m)                 (0x00000360 + ((m) * 0x00000004))  /* User Offset Table Register %s */
/* ADUGTR%s Registers (0-7) */
#define R_ADC_B_ADUGTR_OFFSET(m)                  (0x00000380 + ((m) * 0x00000004))  /* User Gain Table Register %s */
#define R_ADC_B_ADLIMINTCR_OFFSET                 0x000003a0  /* Limiter Clip Interrupt Enable Register */
/* ADLIMTR%s Registers (0-7) */
#define R_ADC_B_ADLIMTR_OFFSET(m)                 (0x000003a4 + ((m) * 0x00000004))  /* Limiter Clip Table Register %s */
#define R_ADC_B_ADCMPENR_OFFSET                   0x00000400  /* Compare Match Enable Register */
#define R_ADC_B_ADCMPINTCR_OFFSET                 0x00000404  /* Compare Match Interrupt Enable Register */
/* ADCCMPCR%s Registers (0-1) */
#define R_ADC_B_ADCCMPCR_OFFSET(m)                (0x00000408 + ((m) * 0x00000004))  /* Composite Compare Match Configuration Register %s */
#define R_ADC_B_ADCMPMDR0_OFFSET                  0x00000448  /* Compare Match Mode Selection Register 0 */
#define R_ADC_B_ADCMPMDR1_OFFSET                  0x0000044c  /* Compare Match Mode Selection Register 1 */
/* ADCMPTBR%s Registers (0-7) */
#define R_ADC_B_ADCMPTBR_OFFSET(m)                (0x00000458 + ((m) * 0x00000004))  /* Compare Match Table Register %s */
#define R_ADC_B_ADFIFOCR_OFFSET                   0x000004c0  /* FIFO Control Register */
#define R_ADC_B_ADFIFOINTCR_OFFSET                0x000004c4  /* FIFO Interrupt Control Register */
#define R_ADC_B_ADFIFOINTLR0_OFFSET               0x000004c8  /* FIFO Interrupt Generation Level Register 0 */
#define R_ADC_B_ADFIFOINTLR1_OFFSET               0x000004cc  /* FIFO Interrupt Generation Level Register 1 */
#define R_ADC_B_ADFIFOINTLR2_OFFSET               0x000004d0  /* FIFO Interrupt Generation Level Register 2 */
#define R_ADC_B_ADFIFOINTLR3_OFFSET               0x000004d4  /* FIFO Interrupt Generation Level Register 3 */
#define R_ADC_B_ADFIFOINTLR4_OFFSET               0x000004d8  /* FIFO Interrupt Generation Level Register 4 */
/* ADCHCR%s Registers (0-32) */
#define R_ADC_B_ADCHCR_OFFSET(m)                  (0x00000600 + ((m) * 0x00000010))  /* A/D Conversion Channel Configuration Register %s */
/* ADDOPCRA%s Registers (0-32) */
#define R_ADC_B_ADDOPCRA_OFFSET(m)                (0x00000604 + ((m) * 0x00000010))  /* A/D Conversion Data Operation Control A Register %s */
/* ADDOPCRB%s Registers (0-32) */
#define R_ADC_B_ADDOPCRB_OFFSET(m)                (0x00000608 + ((m) * 0x00000010))  /* A/D Conversion Data Operation Control B Register %s */
/* ADDOPCRC%s Registers (0-32) */
#define R_ADC_B_ADDOPCRC_OFFSET(m)                (0x0000060c + ((m) * 0x00000010))  /* A/D Conversion Data Operation Control C Register %s */
#define R_ADC_B_ADCALSTR_OFFSET                   0x00000c00  /* A/D Converter Self-calibration Start Register */
#define R_ADC_B_ADSHCSCR_OFFSET                   0x00000c04  /* Channel-Dedicated Sample & Hold Circuit Constant Sampling Control Register */
#define R_ADC_B_ADTRGENR_OFFSET                   0x00000c08  /* A/D Conversion Start Trigger Enable Register */
#define R_ADC_B_ADSYSTR_OFFSET                    0x00000c10  /* A/D Conversion Synchronous Software Start Register */
/* ADSTR%s Registers (0-8) */
#define R_ADC_B_ADSTR_OFFSET(m)                   (0x00000c20 + ((m) * 0x00000004))  /* A/D Conversion Software Start Register %s */
#define R_ADC_B_ADSTOPR_OFFSET                    0x00000c60  /* A/D Conversion Stop Register */
#define R_ADC_B_ADSR_OFFSET                       0x00000c80  /* A/D Conversion Status Register */
#define R_ADC_B_ADGRSR_OFFSET                     0x00000c84  /* Scan Group Status Register */
#define R_ADC_B_ADERSR_OFFSET                     0x00000c88  /* A/D Conversion Error Status Register */
#define R_ADC_B_ADERSCR_OFFSET                    0x00000c8c  /* A/D Conversion Error Status Clear Register */
#define R_ADC_B_ADCALENDSR_OFFSET                 0x00000c98  /* A/D Converter Self-calibration End Status Register */
#define R_ADC_B_ADCALENDSCR_OFFSET                0x00000c9c  /* A/D Converter Self-calibration End Status Clear Register */
#define R_ADC_B_ADOVFERSR_OFFSET                  0x00000ca0  /* A/D Conversion Overflow Error Status Register */
#define R_ADC_B_ADOVFCHSR0_OFFSET                 0x00000ca4  /* A/D Conversion Overflow Channel Status Register 0 */
#define R_ADC_B_ADOVFEXSR_OFFSET                  0x00000cb0  /* Extended Analog A/D Conversion Overflow Status Register */
#define R_ADC_B_ADOVFERSCR_OFFSET                 0x00000cb4  /* A/D Conversion Overflow Error Status Clear Register */
#define R_ADC_B_ADOVFCHSCR0_OFFSET                0x00000cb8  /* A/D Conversion Overflow Channel Status Clear Register 0 */
#define R_ADC_B_ADOVFEXSCR_OFFSET                 0x00000cc4  /* Extended Analog A/D Conversion Overflow Status Clear Register */
#define R_ADC_B_ADFIFOSR0_OFFSET                  0x00000cd0  /* FIFO Status Register 0 */
#define R_ADC_B_ADFIFOSR1_OFFSET                  0x00000cd4  /* FIFO Status Register 1 */
#define R_ADC_B_ADFIFOSR2_OFFSET                  0x00000cd8  /* FIFO Status Register 2 */
#define R_ADC_B_ADFIFOSR3_OFFSET                  0x00000cdc  /* FIFO Status Register 3 */
#define R_ADC_B_ADFIFOSR4_OFFSET                  0x00000ce0  /* FIFO Status Register 4 */
#define R_ADC_B_ADFIFODCR_OFFSET                  0x00000cf0  /* FIFO Data Clear Register */
#define R_ADC_B_ADFIFOERSR_OFFSET                 0x00000cf4  /* FIFO Error Status Register */
#define R_ADC_B_ADFIFOERSCR_OFFSET                0x00000cf8  /* FIFO Error Status Clear Register */
#define R_ADC_B_ADCMPTBSR_OFFSET                  0x00000d00  /* Compare Match Table Status Register */
#define R_ADC_B_ADCMPTBSCR_OFFSET                 0x00000d04  /* Compare Match Table Status Clear Register */
#define R_ADC_B_ADCMPCHSR0_OFFSET                 0x00000d08  /* Compare Match Channel Status Register 0 */
#define R_ADC_B_ADCMPEXSR_OFFSET                  0x00000d14  /* Extended Analog Compare Match Status Register */
#define R_ADC_B_ADCMPCHSCR0_OFFSET                0x00000d18  /* Compare Match Channel Status Clear Register 0 */
#define R_ADC_B_ADCMPEXSCR_OFFSET                 0x00000d24  /* Extended Analog Compare Match Status Clear Register */
#define R_ADC_B_ADLIMGRSR_OFFSET                  0x00000d28  /* Limiter Clip Scan Group Status Register */
#define R_ADC_B_ADLIMCHSR0_OFFSET                 0x00000d2c  /* Limiter Clip Channel Status Register 0 */
#define R_ADC_B_ADLIMEXSR_OFFSET                  0x00000d38  /* Extended Analog Limiter Clip Status Register */
#define R_ADC_B_ADLIMGRSCR_OFFSET                 0x00000d3c  /* Limiter Clip Scan Group Status Clear Register */
#define R_ADC_B_ADLIMCHSCR0_OFFSET                0x00000d40  /* Limiter Clip Channel Status Clear Register 0 */
#define R_ADC_B_ADLIMEXSCR_OFFSET                 0x00000d4c  /* Extended Analog Limiter Clip Status Clear Register */
#define R_ADC_B_ADSCANENDSR_OFFSET                0x00000d50  /* Scan End Status Register */
#define R_ADC_B_ADSCANENDSCR_OFFSET               0x00000d54  /* Scan End Status Clear Register */
/* ADDR%s Registers (0-22) */
#define R_ADC_B_ADDR_OFFSET(m)                    (0x00002000 + ((m) * 0x00000004))  /* A/D Data Register %s */
/* ADFIFODR%s Registers (0-8) */
#define R_ADC_B_ADFIFODR_OFFSET(m)                (0x00002200 + ((m) * 0x00000004))  /* FIFO Data Register %s */

/* ADC_B Register Addresses */

#define R_ADC_B_ADCLKENR                          (R_ADC_B_BASE + R_ADC_B_ADCLKENR_OFFSET)
#define R_ADC_B_ADCLKSR                           (R_ADC_B_BASE + R_ADC_B_ADCLKSR_OFFSET)
#define R_ADC_B_ADCLKCR                           (R_ADC_B_BASE + R_ADC_B_ADCLKCR_OFFSET)
#define R_ADC_B_ADSYCR                            (R_ADC_B_BASE + R_ADC_B_ADSYCR_OFFSET)
#define R_ADC_B_ADUSLPCR0                         (R_ADC_B_BASE + R_ADC_B_ADUSLPCR0_OFFSET)
#define R_ADC_B_ADUSLPCR1                         (R_ADC_B_BASE + R_ADC_B_ADUSLPCR1_OFFSET)
#define R_ADC_B_ADERINTCR                         (R_ADC_B_BASE + R_ADC_B_ADERINTCR_OFFSET)
#define R_ADC_B_ADOVFINTCR                        (R_ADC_B_BASE + R_ADC_B_ADOVFINTCR_OFFSET)
#define R_ADC_B_ADCALINTCR                        (R_ADC_B_BASE + R_ADC_B_ADCALINTCR_OFFSET)
#define R_ADC_B_ADMDR                             (R_ADC_B_BASE + R_ADC_B_ADMDR_OFFSET)
#define R_ADC_B_ADGSPCR                           (R_ADC_B_BASE + R_ADC_B_ADGSPCR_OFFSET)
#define R_ADC_B_ADSGER                            (R_ADC_B_BASE + R_ADC_B_ADSGER_OFFSET)
#define R_ADC_B_ADSGCR0                           (R_ADC_B_BASE + R_ADC_B_ADSGCR0_OFFSET)
#define R_ADC_B_ADSGCR1                           (R_ADC_B_BASE + R_ADC_B_ADSGCR1_OFFSET)
#define R_ADC_B_ADSGCR2                           (R_ADC_B_BASE + R_ADC_B_ADSGCR2_OFFSET)
#define R_ADC_B_ADINTCR                           (R_ADC_B_BASE + R_ADC_B_ADINTCR_OFFSET)
#define R_ADC_B_ADSWNR0                           (R_ADC_B_BASE + R_ADC_B_ADSWNR0_OFFSET)
#define R_ADC_B_ADSWNR1                           (R_ADC_B_BASE + R_ADC_B_ADSWNR1_OFFSET)
#define R_ADC_B_ADDECCR                           (R_ADC_B_BASE + R_ADC_B_ADDECCR_OFFSET)
#define R_ADC_B_ADACMDR                           (R_ADC_B_BASE + R_ADC_B_ADACMDR_OFFSET)
#define R_ADC_B_ADTRGEXT(m)                       (R_ADC_B_BASE + R_ADC_B_ADTRGEXT_OFFSET(m))
#define R_ADC_B_ADTRGELC(m)                       (R_ADC_B_BASE + R_ADC_B_ADTRGELC_OFFSET(m))
#define R_ADC_B_ADTRGGPT(m)                       (R_ADC_B_BASE + R_ADC_B_ADTRGGPT_OFFSET(m))
#define R_ADC_B_ADTRGDLR0                         (R_ADC_B_BASE + R_ADC_B_ADTRGDLR0_OFFSET)
#define R_ADC_B_ADTRGDLR1                         (R_ADC_B_BASE + R_ADC_B_ADTRGDLR1_OFFSET)
#define R_ADC_B_ADTRGDLR2                         (R_ADC_B_BASE + R_ADC_B_ADTRGDLR2_OFFSET)
#define R_ADC_B_ADTRGDLR3                         (R_ADC_B_BASE + R_ADC_B_ADTRGDLR3_OFFSET)
#define R_ADC_B_ADTRGDLR4                         (R_ADC_B_BASE + R_ADC_B_ADTRGDLR4_OFFSET)
#define R_ADC_B_ADSGDCR(m)                        (R_ADC_B_BASE + R_ADC_B_ADSGDCR_OFFSET(m))
#define R_ADC_B_ADSSTR0                           (R_ADC_B_BASE + R_ADC_B_ADSSTR0_OFFSET)
#define R_ADC_B_ADSSTR1                           (R_ADC_B_BASE + R_ADC_B_ADSSTR1_OFFSET)
#define R_ADC_B_ADSSTR2                           (R_ADC_B_BASE + R_ADC_B_ADSSTR2_OFFSET)
#define R_ADC_B_ADSSTR3                           (R_ADC_B_BASE + R_ADC_B_ADSSTR3_OFFSET)
#define R_ADC_B_ADSSTR4                           (R_ADC_B_BASE + R_ADC_B_ADSSTR4_OFFSET)
#define R_ADC_B_ADSSTR5                           (R_ADC_B_BASE + R_ADC_B_ADSSTR5_OFFSET)
#define R_ADC_B_ADSSTR6                           (R_ADC_B_BASE + R_ADC_B_ADSSTR6_OFFSET)
#define R_ADC_B_ADSSTR7                           (R_ADC_B_BASE + R_ADC_B_ADSSTR7_OFFSET)
#define R_ADC_B_ADCNVSTR                          (R_ADC_B_BASE + R_ADC_B_ADCNVSTR_OFFSET)
#define R_ADC_B_ADCALSTCR                         (R_ADC_B_BASE + R_ADC_B_ADCALSTCR_OFFSET)
#define R_ADC_B_ADSHCR0                           (R_ADC_B_BASE + R_ADC_B_ADSHCR0_OFFSET)
#define R_ADC_B_ADSHDCR0                          (R_ADC_B_BASE + R_ADC_B_ADSHDCR0_OFFSET)
#define R_ADC_B_ADSHSTR0                          (R_ADC_B_BASE + R_ADC_B_ADSHSTR0_OFFSET)
#define R_ADC_B_ADSHCR1                           (R_ADC_B_BASE + R_ADC_B_ADSHCR1_OFFSET)
#define R_ADC_B_ADSHDCR1                          (R_ADC_B_BASE + R_ADC_B_ADSHDCR1_OFFSET)
#define R_ADC_B_ADSHSTR1                          (R_ADC_B_BASE + R_ADC_B_ADSHSTR1_OFFSET)
#define R_ADC_B_ADCALSHCR                         (R_ADC_B_BASE + R_ADC_B_ADCALSHCR_OFFSET)
#define R_ADC_B_ADSHSBPCR                         (R_ADC_B_BASE + R_ADC_B_ADSHSBPCR_OFFSET)
#define R_ADC_B_ADSHDBPCR                         (R_ADC_B_BASE + R_ADC_B_ADSHDBPCR_OFFSET)
#define R_ADC_B_ADSHSDCR0                         (R_ADC_B_BASE + R_ADC_B_ADSHSDCR0_OFFSET)
#define R_ADC_B_ADSHSDCR1                         (R_ADC_B_BASE + R_ADC_B_ADSHSDCR1_OFFSET)
#define R_ADC_B_ADREFCR                           (R_ADC_B_BASE + R_ADC_B_ADREFCR_OFFSET)
#define R_ADC_B_ADDFSR(m)                         (R_ADC_B_BASE + R_ADC_B_ADDFSR_OFFSET(m))
#define R_ADC_B_ADUOFTR(m)                        (R_ADC_B_BASE + R_ADC_B_ADUOFTR_OFFSET(m))
#define R_ADC_B_ADUGTR(m)                         (R_ADC_B_BASE + R_ADC_B_ADUGTR_OFFSET(m))
#define R_ADC_B_ADLIMINTCR                        (R_ADC_B_BASE + R_ADC_B_ADLIMINTCR_OFFSET)
#define R_ADC_B_ADLIMTR(m)                        (R_ADC_B_BASE + R_ADC_B_ADLIMTR_OFFSET(m))
#define R_ADC_B_ADCMPENR                          (R_ADC_B_BASE + R_ADC_B_ADCMPENR_OFFSET)
#define R_ADC_B_ADCMPINTCR                        (R_ADC_B_BASE + R_ADC_B_ADCMPINTCR_OFFSET)
#define R_ADC_B_ADCCMPCR(m)                       (R_ADC_B_BASE + R_ADC_B_ADCCMPCR_OFFSET(m))
#define R_ADC_B_ADCMPMDR0                         (R_ADC_B_BASE + R_ADC_B_ADCMPMDR0_OFFSET)
#define R_ADC_B_ADCMPMDR1                         (R_ADC_B_BASE + R_ADC_B_ADCMPMDR1_OFFSET)
#define R_ADC_B_ADCMPTBR(m)                       (R_ADC_B_BASE + R_ADC_B_ADCMPTBR_OFFSET(m))
#define R_ADC_B_ADFIFOCR                          (R_ADC_B_BASE + R_ADC_B_ADFIFOCR_OFFSET)
#define R_ADC_B_ADFIFOINTCR                       (R_ADC_B_BASE + R_ADC_B_ADFIFOINTCR_OFFSET)
#define R_ADC_B_ADFIFOINTLR0                      (R_ADC_B_BASE + R_ADC_B_ADFIFOINTLR0_OFFSET)
#define R_ADC_B_ADFIFOINTLR1                      (R_ADC_B_BASE + R_ADC_B_ADFIFOINTLR1_OFFSET)
#define R_ADC_B_ADFIFOINTLR2                      (R_ADC_B_BASE + R_ADC_B_ADFIFOINTLR2_OFFSET)
#define R_ADC_B_ADFIFOINTLR3                      (R_ADC_B_BASE + R_ADC_B_ADFIFOINTLR3_OFFSET)
#define R_ADC_B_ADFIFOINTLR4                      (R_ADC_B_BASE + R_ADC_B_ADFIFOINTLR4_OFFSET)
#define R_ADC_B_ADCHCR(m)                         (R_ADC_B_BASE + R_ADC_B_ADCHCR_OFFSET(m))
#define R_ADC_B_ADDOPCRA(m)                       (R_ADC_B_BASE + R_ADC_B_ADDOPCRA_OFFSET(m))
#define R_ADC_B_ADDOPCRB(m)                       (R_ADC_B_BASE + R_ADC_B_ADDOPCRB_OFFSET(m))
#define R_ADC_B_ADDOPCRC(m)                       (R_ADC_B_BASE + R_ADC_B_ADDOPCRC_OFFSET(m))
#define R_ADC_B_ADCALSTR                          (R_ADC_B_BASE + R_ADC_B_ADCALSTR_OFFSET)
#define R_ADC_B_ADSHCSCR                          (R_ADC_B_BASE + R_ADC_B_ADSHCSCR_OFFSET)
#define R_ADC_B_ADTRGENR                          (R_ADC_B_BASE + R_ADC_B_ADTRGENR_OFFSET)
#define R_ADC_B_ADSYSTR                           (R_ADC_B_BASE + R_ADC_B_ADSYSTR_OFFSET)
#define R_ADC_B_ADSTR(m)                          (R_ADC_B_BASE + R_ADC_B_ADSTR_OFFSET(m))
#define R_ADC_B_ADSTOPR                           (R_ADC_B_BASE + R_ADC_B_ADSTOPR_OFFSET)
#define R_ADC_B_ADSR                              (R_ADC_B_BASE + R_ADC_B_ADSR_OFFSET)
#define R_ADC_B_ADGRSR                            (R_ADC_B_BASE + R_ADC_B_ADGRSR_OFFSET)
#define R_ADC_B_ADERSR                            (R_ADC_B_BASE + R_ADC_B_ADERSR_OFFSET)
#define R_ADC_B_ADERSCR                           (R_ADC_B_BASE + R_ADC_B_ADERSCR_OFFSET)
#define R_ADC_B_ADCALENDSR                        (R_ADC_B_BASE + R_ADC_B_ADCALENDSR_OFFSET)
#define R_ADC_B_ADCALENDSCR                       (R_ADC_B_BASE + R_ADC_B_ADCALENDSCR_OFFSET)
#define R_ADC_B_ADOVFERSR                         (R_ADC_B_BASE + R_ADC_B_ADOVFERSR_OFFSET)
#define R_ADC_B_ADOVFCHSR0                        (R_ADC_B_BASE + R_ADC_B_ADOVFCHSR0_OFFSET)
#define R_ADC_B_ADOVFEXSR                         (R_ADC_B_BASE + R_ADC_B_ADOVFEXSR_OFFSET)
#define R_ADC_B_ADOVFERSCR                        (R_ADC_B_BASE + R_ADC_B_ADOVFERSCR_OFFSET)
#define R_ADC_B_ADOVFCHSCR0                       (R_ADC_B_BASE + R_ADC_B_ADOVFCHSCR0_OFFSET)
#define R_ADC_B_ADOVFEXSCR                        (R_ADC_B_BASE + R_ADC_B_ADOVFEXSCR_OFFSET)
#define R_ADC_B_ADFIFOSR0                         (R_ADC_B_BASE + R_ADC_B_ADFIFOSR0_OFFSET)
#define R_ADC_B_ADFIFOSR1                         (R_ADC_B_BASE + R_ADC_B_ADFIFOSR1_OFFSET)
#define R_ADC_B_ADFIFOSR2                         (R_ADC_B_BASE + R_ADC_B_ADFIFOSR2_OFFSET)
#define R_ADC_B_ADFIFOSR3                         (R_ADC_B_BASE + R_ADC_B_ADFIFOSR3_OFFSET)
#define R_ADC_B_ADFIFOSR4                         (R_ADC_B_BASE + R_ADC_B_ADFIFOSR4_OFFSET)
#define R_ADC_B_ADFIFODCR                         (R_ADC_B_BASE + R_ADC_B_ADFIFODCR_OFFSET)
#define R_ADC_B_ADFIFOERSR                        (R_ADC_B_BASE + R_ADC_B_ADFIFOERSR_OFFSET)
#define R_ADC_B_ADFIFOERSCR                       (R_ADC_B_BASE + R_ADC_B_ADFIFOERSCR_OFFSET)
#define R_ADC_B_ADCMPTBSR                         (R_ADC_B_BASE + R_ADC_B_ADCMPTBSR_OFFSET)
#define R_ADC_B_ADCMPTBSCR                        (R_ADC_B_BASE + R_ADC_B_ADCMPTBSCR_OFFSET)
#define R_ADC_B_ADCMPCHSR0                        (R_ADC_B_BASE + R_ADC_B_ADCMPCHSR0_OFFSET)
#define R_ADC_B_ADCMPEXSR                         (R_ADC_B_BASE + R_ADC_B_ADCMPEXSR_OFFSET)
#define R_ADC_B_ADCMPCHSCR0                       (R_ADC_B_BASE + R_ADC_B_ADCMPCHSCR0_OFFSET)
#define R_ADC_B_ADCMPEXSCR                        (R_ADC_B_BASE + R_ADC_B_ADCMPEXSCR_OFFSET)
#define R_ADC_B_ADLIMGRSR                         (R_ADC_B_BASE + R_ADC_B_ADLIMGRSR_OFFSET)
#define R_ADC_B_ADLIMCHSR0                        (R_ADC_B_BASE + R_ADC_B_ADLIMCHSR0_OFFSET)
#define R_ADC_B_ADLIMEXSR                         (R_ADC_B_BASE + R_ADC_B_ADLIMEXSR_OFFSET)
#define R_ADC_B_ADLIMGRSCR                        (R_ADC_B_BASE + R_ADC_B_ADLIMGRSCR_OFFSET)
#define R_ADC_B_ADLIMCHSCR0                       (R_ADC_B_BASE + R_ADC_B_ADLIMCHSCR0_OFFSET)
#define R_ADC_B_ADLIMEXSCR                        (R_ADC_B_BASE + R_ADC_B_ADLIMEXSCR_OFFSET)
#define R_ADC_B_ADSCANENDSR                       (R_ADC_B_BASE + R_ADC_B_ADSCANENDSR_OFFSET)
#define R_ADC_B_ADSCANENDSCR                      (R_ADC_B_BASE + R_ADC_B_ADSCANENDSCR_OFFSET)
#define R_ADC_B_ADDR(m)                           (R_ADC_B_BASE + R_ADC_B_ADDR_OFFSET(m))
#define R_ADC_B_ADFIFODR(m)                       (R_ADC_B_BASE + R_ADC_B_ADFIFODR_OFFSET(m))

/* Register bit definitions */
/* ADCLKENR Register bit definitions */
#define R_ADC_B_ADCLKENR_CLKEN                    (1 << 0)  /* ADCLK Operating Enable */

/* ADCLKSR Register bit definitions */
#define R_ADC_B_ADCLKSR_CLKSR                     (1 << 0)  /* ADCLK status */

/* ADCLKCR Register bit definitions */
#define R_ADC_B_ADCLKCR_CLKSEL_SHIFT              (0)  /* ADCLK Clock Source Select */
#define R_ADC_B_ADCLKCR_CLKSEL_MASK               0x3
#  define R_ADC_B_ADCLKCR_CLKSEL_00                       (0 << R_ADC_B_ADCLKCR_CLKSEL_SHIFT)  /* ADC Clock (ADCCLK) */
#  define R_ADC_B_ADCLKCR_CLKSEL_01                       (1 << R_ADC_B_ADCLKCR_CLKSEL_SHIFT)  /* GPT Clock (GPTCLK) */
#  define R_ADC_B_ADCLKCR_CLKSEL_10                       (2 << R_ADC_B_ADCLKCR_CLKSEL_SHIFT)  /* Peripheral Module Clock A (PCLKA) */
#  define R_ADC_B_ADCLKCR_CLKSEL_11                       (3 << R_ADC_B_ADCLKCR_CLKSEL_SHIFT)  /* Setting prohibited */

#define R_ADC_B_ADCLKCR_DIVR_SHIFT                (16)  /* Clock Division Ratio Select */
#define R_ADC_B_ADCLKCR_DIVR_MASK                 0x70000
#  define R_ADC_B_ADCLKCR_DIVR_000                        (0 << R_ADC_B_ADCLKCR_DIVR_SHIFT)  /* 1/1 */
#  define R_ADC_B_ADCLKCR_DIVR_001                        (1 << R_ADC_B_ADCLKCR_DIVR_SHIFT)  /* 1/2 */
#  define R_ADC_B_ADCLKCR_DIVR_010                        (2 << R_ADC_B_ADCLKCR_DIVR_SHIFT)  /* 1/3 */
#  define R_ADC_B_ADCLKCR_DIVR_011                        (3 << R_ADC_B_ADCLKCR_DIVR_SHIFT)  /* 1/4 */
#  define R_ADC_B_ADCLKCR_DIVR_100                        (4 << R_ADC_B_ADCLKCR_DIVR_SHIFT)  /* 1/5 */

/* ADSYCR Register bit definitions */
#define R_ADC_B_ADSYCR_ADSYCYC_SHIFT              (0)  /* Synchronous Operation Period Cycle */
#define R_ADC_B_ADSYCR_ADSYCYC_MASK               0x7ff

#define R_ADC_B_ADSYCR_ADSYDIS0                   (1 << 16)  /* ADC0 Synchronous Operation Select */

#define R_ADC_B_ADSYCR_ADSYDIS1                   (1 << 17)  /* ADC1 Synchronous Operation Select */

/* ADUSLPCR0 Register bit definitions */
#define R_ADC_B_ADUSLPCR0_ADUSLP                  (1 << 0)  /* Sleep setting of A/D converter unit 0 */

/* ADUSLPCR1 Register bit definitions */
#define R_ADC_B_ADUSLPCR1_ADUSLP                  (1 << 0)  /* Sleep setting of A/D converter unit 1 */

/* ADERINTCR Register bit definitions */
#define R_ADC_B_ADERINTCR_ADEIE0                  (1 << 0)  /* ADC0 A/D Conversion Error Interrupt Enable */

#define R_ADC_B_ADERINTCR_ADEIE1                  (1 << 1)  /* ADC1 A/D Conversion Error Interrupt Enable */

/* ADOVFINTCR Register bit definitions */
#define R_ADC_B_ADOVFINTCR_ADOVFIE0               (1 << 0)  /* ADC0 A/D Conversion Overflow Interrupt Enable */

#define R_ADC_B_ADOVFINTCR_ADOVFIE1               (1 << 1)  /* ADC1 A/D Conversion Overflow Interrupt Enable */

/* ADCALINTCR Register bit definitions */
#define R_ADC_B_ADCALINTCR_CALENDIE0              (1 << 16)  /* ADC0 Calibration End Interrupt Enable */

#define R_ADC_B_ADCALINTCR_CALENDIE1              (1 << 17)  /* ADC1 Calibration End Interrupt Enable */

/* ADMDR Register bit definitions */
#define R_ADC_B_ADMDR_ADMD0_SHIFT                 (0)  /* ADC0 Mode Selection */
#define R_ADC_B_ADMDR_ADMD0_MASK                  0xf
#  define R_ADC_B_ADMDR_ADMD0_0X0                         (0 << R_ADC_B_ADMDR_ADMD0_SHIFT)  /* SAR mode – Single scan mode */
#  define R_ADC_B_ADMDR_ADMD0_0X1                         (1 << R_ADC_B_ADMDR_ADMD0_SHIFT)  /* SAR mode – Continuous scan mode */
#  define R_ADC_B_ADMDR_ADMD0_0X4                         (4 << R_ADC_B_ADMDR_ADMD0_SHIFT)  /* Oversampling mode – Single scan mode */
#  define R_ADC_B_ADMDR_ADMD0_0X5                         (5 << R_ADC_B_ADMDR_ADMD0_SHIFT)  /* Oversampling mode – Continuous scan mode */
#  define R_ADC_B_ADMDR_ADMD0_0X6                         (6 << R_ADC_B_ADMDR_ADMD0_SHIFT)  /* Oversampling mode – One-channel continuous scan mode */
#  define R_ADC_B_ADMDR_ADMD0_0X8                         (8 << R_ADC_B_ADMDR_ADMD0_SHIFT)  /* Hybrid mode – Single scan mode */
#  define R_ADC_B_ADMDR_ADMD0_0X9                         (9 << R_ADC_B_ADMDR_ADMD0_SHIFT)  /* Hybrid mode – Continuous scan mode */
#  define R_ADC_B_ADMDR_ADMD0_0XA                         (10 << R_ADC_B_ADMDR_ADMD0_SHIFT)  /* Hybrid mode – Background continuous scan mode */
#  define R_ADC_B_ADMDR_ADMD0_0XB                         (11 << R_ADC_B_ADMDR_ADMD0_SHIFT)  /* Hybrid mode – Fixed-channel continuous scan mode */

#define R_ADC_B_ADMDR_ADMD1_SHIFT                 (8)  /* ADC1 Mode Selection */
#define R_ADC_B_ADMDR_ADMD1_MASK                  0xf00
#  define R_ADC_B_ADMDR_ADMD1_0X0                         (0 << R_ADC_B_ADMDR_ADMD1_SHIFT)  /* SAR mode – Single scan mode */
#  define R_ADC_B_ADMDR_ADMD1_0X1                         (1 << R_ADC_B_ADMDR_ADMD1_SHIFT)  /* SAR mode – Continuous scan mode */
#  define R_ADC_B_ADMDR_ADMD1_0X4                         (4 << R_ADC_B_ADMDR_ADMD1_SHIFT)  /* Oversampling mode – Single scan mode */
#  define R_ADC_B_ADMDR_ADMD1_0X5                         (5 << R_ADC_B_ADMDR_ADMD1_SHIFT)  /* Oversampling mode – Continuous scan mode */
#  define R_ADC_B_ADMDR_ADMD1_0X6                         (6 << R_ADC_B_ADMDR_ADMD1_SHIFT)  /* Oversampling mode – One-channel continuous scan mode */
#  define R_ADC_B_ADMDR_ADMD1_0X8                         (8 << R_ADC_B_ADMDR_ADMD1_SHIFT)  /* Hybrid mode – Single scan mode */
#  define R_ADC_B_ADMDR_ADMD1_0X9                         (9 << R_ADC_B_ADMDR_ADMD1_SHIFT)  /* Hybrid mode – Continuous scan mode */
#  define R_ADC_B_ADMDR_ADMD1_0XA                         (10 << R_ADC_B_ADMDR_ADMD1_SHIFT)  /* Hybrid mode – Background continuous scan mode */
#  define R_ADC_B_ADMDR_ADMD1_0XB                         (11 << R_ADC_B_ADMDR_ADMD1_SHIFT)  /* Hybrid mode – Fixed-channel continuous scan mode */

/* ADGSPCR Register bit definitions */
#define R_ADC_B_ADGSPCR_PGS0                      (1 << 0)  /* ADC0 Group Priority Control Setting */

#define R_ADC_B_ADGSPCR_RSCN0                     (1 << 1)  /* ADC0 Group Priority Control Setting 2 */

#define R_ADC_B_ADGSPCR_LGRRS0                    (1 << 2)  /* ADC0 Group Priority Control Setting 3 */

#define R_ADC_B_ADGSPCR_GRP0                      (1 << 3)  /* ADC0 Group Priority Control Setting 4 */

#define R_ADC_B_ADGSPCR_PGS1                      (1 << 8)  /* ADC1 Group Priority Control Setting */

#define R_ADC_B_ADGSPCR_RSCN1                     (1 << 9)  /* ADC1 Group Priority Control Setting 2 */

#define R_ADC_B_ADGSPCR_LGRRS1                    (1 << 10)  /* ADC1 Group Priority Control Setting 3 */

#define R_ADC_B_ADGSPCR_GRP1                      (1 << 11)  /* ADC1 Group Priority Control Setting 4 */

/* ADSGER Register bit definitions */
#define R_ADC_B_ADSGER_SGRE0                      (1 << 0)  /* Scan Group n Enable */

#define R_ADC_B_ADSGER_SGRE1                      (1 << 1)  /* Scan Group n Enable */

#define R_ADC_B_ADSGER_SGRE2                      (1 << 2)  /* Scan Group n Enable */

#define R_ADC_B_ADSGER_SGRE3                      (1 << 3)  /* Scan Group n Enable */

#define R_ADC_B_ADSGER_SGRE4                      (1 << 4)  /* Scan Group n Enable */

#define R_ADC_B_ADSGER_SGRE5                      (1 << 5)  /* Scan Group n Enable */

#define R_ADC_B_ADSGER_SGRE6                      (1 << 6)  /* Scan Group n Enable */

#define R_ADC_B_ADSGER_SGRE7                      (1 << 7)  /* Scan Group n Enable */

#define R_ADC_B_ADSGER_SGRE8                      (1 << 8)  /* Scan Group n Enable */

#define R_ADC_B_ADSGER_SGREN_SHIFT                (0)  /* Scan Group n Enable */
#define R_ADC_B_ADSGER_SGREN_MASK                 0x1ff

/* ADSGCR0 Register bit definitions */
#define R_ADC_B_ADSGCR0_SGADS0_SHIFT              (0)  /* Scan Group 0 A/D Converter Selection */
#define R_ADC_B_ADSGCR0_SGADS0_MASK               0x3
#  define R_ADC_B_ADSGCR0_SGADS0_00                       (0 << R_ADC_B_ADSGCR0_SGADS0_SHIFT)  /* Select ADC0 */
#  define R_ADC_B_ADSGCR0_SGADS0_01                       (1 << R_ADC_B_ADSGCR0_SGADS0_SHIFT)  /* Select ADC1 */

#define R_ADC_B_ADSGCR0_SGADS1_SHIFT              (8)  /* Scan Group 1 A/D Converter Selection */
#define R_ADC_B_ADSGCR0_SGADS1_MASK               0x300
#  define R_ADC_B_ADSGCR0_SGADS1_00                       (0 << R_ADC_B_ADSGCR0_SGADS1_SHIFT)  /* Select ADC0 */
#  define R_ADC_B_ADSGCR0_SGADS1_01                       (1 << R_ADC_B_ADSGCR0_SGADS1_SHIFT)  /* Select ADC1 */

#define R_ADC_B_ADSGCR0_SGADS2_SHIFT              (16)  /* Scan Group 2 A/D Converter Selection */
#define R_ADC_B_ADSGCR0_SGADS2_MASK               0x30000
#  define R_ADC_B_ADSGCR0_SGADS2_00                       (0 << R_ADC_B_ADSGCR0_SGADS2_SHIFT)  /* Select ADC0 */
#  define R_ADC_B_ADSGCR0_SGADS2_01                       (1 << R_ADC_B_ADSGCR0_SGADS2_SHIFT)  /* Select ADC1 */

#define R_ADC_B_ADSGCR0_SGADS3_SHIFT              (24)  /* Scan Group 3 A/D Converter Selection */
#define R_ADC_B_ADSGCR0_SGADS3_MASK               0x3000000
#  define R_ADC_B_ADSGCR0_SGADS3_00                       (0 << R_ADC_B_ADSGCR0_SGADS3_SHIFT)  /* Select ADC0 */
#  define R_ADC_B_ADSGCR0_SGADS3_01                       (1 << R_ADC_B_ADSGCR0_SGADS3_SHIFT)  /* Select ADC1 */

/* ADSGCR1 Register bit definitions */
#define R_ADC_B_ADSGCR1_SGADS4_SHIFT              (0)  /* Scan Group 4 A/D Converter Selection */
#define R_ADC_B_ADSGCR1_SGADS4_MASK               0x3
#  define R_ADC_B_ADSGCR1_SGADS4_00                       (0 << R_ADC_B_ADSGCR1_SGADS4_SHIFT)  /* Select ADC0 */
#  define R_ADC_B_ADSGCR1_SGADS4_01                       (1 << R_ADC_B_ADSGCR1_SGADS4_SHIFT)  /* Select ADC1 */

#define R_ADC_B_ADSGCR1_SGADS5_SHIFT              (8)  /* Scan Group 5 A/D Converter Selection */
#define R_ADC_B_ADSGCR1_SGADS5_MASK               0x300
#  define R_ADC_B_ADSGCR1_SGADS5_00                       (0 << R_ADC_B_ADSGCR1_SGADS5_SHIFT)  /* Select ADC0 */
#  define R_ADC_B_ADSGCR1_SGADS5_01                       (1 << R_ADC_B_ADSGCR1_SGADS5_SHIFT)  /* Select ADC1 */

#define R_ADC_B_ADSGCR1_SGADS6_SHIFT              (16)  /* Scan Group 6 A/D Converter Selection */
#define R_ADC_B_ADSGCR1_SGADS6_MASK               0x30000
#  define R_ADC_B_ADSGCR1_SGADS6_00                       (0 << R_ADC_B_ADSGCR1_SGADS6_SHIFT)  /* Select ADC0 */
#  define R_ADC_B_ADSGCR1_SGADS6_01                       (1 << R_ADC_B_ADSGCR1_SGADS6_SHIFT)  /* Select ADC1 */

#define R_ADC_B_ADSGCR1_SGADS7_SHIFT              (24)  /* Scan Group 7 A/D Converter Selection */
#define R_ADC_B_ADSGCR1_SGADS7_MASK               0x3000000
#  define R_ADC_B_ADSGCR1_SGADS7_00                       (0 << R_ADC_B_ADSGCR1_SGADS7_SHIFT)  /* Select ADC0 */
#  define R_ADC_B_ADSGCR1_SGADS7_01                       (1 << R_ADC_B_ADSGCR1_SGADS7_SHIFT)  /* Select ADC1 */

/* ADSGCR2 Register bit definitions */
#define R_ADC_B_ADSGCR2_SGADS8_SHIFT              (0)  /* Scan Group 8 A/D Converter Selection */
#define R_ADC_B_ADSGCR2_SGADS8_MASK               0x3
#  define R_ADC_B_ADSGCR2_SGADS8_00                       (0 << R_ADC_B_ADSGCR2_SGADS8_SHIFT)  /* Select ADC0 */
#  define R_ADC_B_ADSGCR2_SGADS8_01                       (1 << R_ADC_B_ADSGCR2_SGADS8_SHIFT)  /* Select ADC1 */

/* ADINTCR Register bit definitions */
#define R_ADC_B_ADINTCR_ADIE0                     (1 << 0)  /* Scan Group n Scan End Interrupt Enable */

#define R_ADC_B_ADINTCR_ADIE1                     (1 << 1)  /* Scan Group n Scan End Interrupt Enable */

#define R_ADC_B_ADINTCR_ADIE2                     (1 << 2)  /* Scan Group n Scan End Interrupt Enable */

#define R_ADC_B_ADINTCR_ADIE3                     (1 << 3)  /* Scan Group n Scan End Interrupt Enable */

#define R_ADC_B_ADINTCR_ADIE4                     (1 << 4)  /* Scan Group n Scan End Interrupt Enable */

#define R_ADC_B_ADINTCR_ADIE5                     (1 << 5)  /* Scan Group n Scan End Interrupt Enable */

#define R_ADC_B_ADINTCR_ADIE6                     (1 << 6)  /* Scan Group n Scan End Interrupt Enable */

#define R_ADC_B_ADINTCR_ADIE7                     (1 << 7)  /* Scan Group n Scan End Interrupt Enable */

#define R_ADC_B_ADINTCR_ADIE8                     (1 << 8)  /* Scan Group n Scan End Interrupt Enable */

#define R_ADC_B_ADINTCR_ADIEN_SHIFT               (0)  /* Scan Group n Scan End Interrupt Enable */
#define R_ADC_B_ADINTCR_ADIEN_MASK                0x1ff

/* ADSWNR0 Register bit definitions */
#define R_ADC_B_ADSWNR0_SWNUM_SHIFT               (0)  /* Sweep Conversion Channel Number per scan */
#define R_ADC_B_ADSWNR0_SWNUM_MASK                0x7

#define R_ADC_B_ADSWNR0_BCSSTSL_SHIFT             (8)  /* Blank Channel Sampling State Table Select */
#define R_ADC_B_ADSWNR0_BCSSTSL_MASK              0xf00

#define R_ADC_B_ADSWNR0_SWFIX_SHIFT               (16)  /* Fixed channel Number */
#define R_ADC_B_ADSWNR0_SWFIX_MASK                0x30000
#  define R_ADC_B_ADSWNR0_SWFIX_0X0                       (0 << R_ADC_B_ADSWNR0_SWFIX_SHIFT)  /* 1 fixed channel */
#  define R_ADC_B_ADSWNR0_SWFIX_0X1                       (1 << R_ADC_B_ADSWNR0_SWFIX_SHIFT)  /* 2 fixed channels */
#  define R_ADC_B_ADSWNR0_SWFIX_0X2                       (2 << R_ADC_B_ADSWNR0_SWFIX_SHIFT)  /* 3 fixed channels */
#  define R_ADC_B_ADSWNR0_SWFIX_0X3                       (3 << R_ADC_B_ADSWNR0_SWFIX_SHIFT)  /* Setting prohibited */

#define R_ADC_B_ADSWNR0_SWNOFIX_SHIFT             (24)  /* Non-Fixed Channel Number */
#define R_ADC_B_ADSWNR0_SWNOFIX_MASK              0x7000000
#  define R_ADC_B_ADSWNR0_SWNOFIX_0X1                     (1 << R_ADC_B_ADSWNR0_SWNOFIX_SHIFT)  /* 1 channels */

/* ADSWNR1 Register bit definitions */
#define R_ADC_B_ADSWNR1_SWNUM_SHIFT               (0)  /* Sweep Conversion Channel Number per scan */
#define R_ADC_B_ADSWNR1_SWNUM_MASK                0x7

#define R_ADC_B_ADSWNR1_BCSSTSL_SHIFT             (8)  /* Blank Channel Sampling State Table Select */
#define R_ADC_B_ADSWNR1_BCSSTSL_MASK              0xf00

#define R_ADC_B_ADSWNR1_SWFIX_SHIFT               (16)  /* Fixed channel Number */
#define R_ADC_B_ADSWNR1_SWFIX_MASK                0x30000
#  define R_ADC_B_ADSWNR1_SWFIX_0X0                       (0 << R_ADC_B_ADSWNR1_SWFIX_SHIFT)  /* 1 fixed channel */
#  define R_ADC_B_ADSWNR1_SWFIX_0X1                       (1 << R_ADC_B_ADSWNR1_SWFIX_SHIFT)  /* 2 fixed channels */
#  define R_ADC_B_ADSWNR1_SWFIX_0X2                       (2 << R_ADC_B_ADSWNR1_SWFIX_SHIFT)  /* 3 fixed channels */
#  define R_ADC_B_ADSWNR1_SWFIX_0X3                       (3 << R_ADC_B_ADSWNR1_SWFIX_SHIFT)  /* Setting prohibited */

#define R_ADC_B_ADSWNR1_SWNOFIX_SHIFT             (24)  /* Non-Fixed Channel Number */
#define R_ADC_B_ADSWNR1_SWNOFIX_MASK              0x7000000
#  define R_ADC_B_ADSWNR1_SWNOFIX_0X1                     (1 << R_ADC_B_ADSWNR1_SWNOFIX_SHIFT)  /* 1 channels */

/* ADDECCR Register bit definitions */
#define R_ADC_B_ADDECCR_DCIM0_SHIFT               (0)  /* One-channel continuous scan mode output decimation setting for A/D converter unit 0 */
#define R_ADC_B_ADDECCR_DCIM0_MASK                0x1f
#  define R_ADC_B_ADDECCR_DCIM0_0X0                       (0 << R_ADC_B_ADDECCR_DCIM0_SHIFT)  /* No decimation */
#  define R_ADC_B_ADDECCR_DCIM0_0X3                       (3 << R_ADC_B_ADDECCR_DCIM0_SHIFT)  /* Output data once for every 4 conversions (thinned 3 times) */
#  define R_ADC_B_ADDECCR_DCIM0_0X7                       (7 << R_ADC_B_ADDECCR_DCIM0_SHIFT)  /* Output data once for every 8 conversions (thinned out 7 times) */

#define R_ADC_B_ADDECCR_DCIM1_SHIFT               (8)  /* One-channel continuous scan mode output decimation setting for A/D converter unit 1 */
#define R_ADC_B_ADDECCR_DCIM1_MASK                0x1f00
#  define R_ADC_B_ADDECCR_DCIM1_0X0                       (0 << R_ADC_B_ADDECCR_DCIM1_SHIFT)  /* No decimation */
#  define R_ADC_B_ADDECCR_DCIM1_0X3                       (3 << R_ADC_B_ADDECCR_DCIM1_SHIFT)  /* Output data once for every 4 conversions (thinned 3 times) */
#  define R_ADC_B_ADDECCR_DCIM1_0X7                       (7 << R_ADC_B_ADDECCR_DCIM1_SHIFT)  /* Output data once for every 8 conversions (thinned out 7 times) */

/* ADACMDR Register bit definitions */
#define R_ADC_B_ADACMDR_ADHACMD0                  (1 << 0)  /* A/D converter unit 0 high accuracy mode setting */

#define R_ADC_B_ADACMDR_ADHACMD1                  (1 << 8)  /* A/D converter unit 1 high accuracy mode setting */

/* ADTRGEXT Register bit definitions */
#define R_ADC_B_ADTRGEXT_TRGEXT0                  (1 << 0)  /* External Trigger Input 0 (ADTRG0) Enable */

#define R_ADC_B_ADTRGEXT_TRGEXT1                  (1 << 1)  /* External Trigger Input 1 (ADTRG1) Enable */

/* ADTRGELC Register bit definitions */
#define R_ADC_B_ADTRGELC_TRGELC0                  (1 << 0)  /* ELC Trigger m Enable */

#define R_ADC_B_ADTRGELC_TRGELC1                  (1 << 1)  /* ELC Trigger m Enable */

#define R_ADC_B_ADTRGELC_TRGELC2                  (1 << 2)  /* ELC Trigger m Enable */

#define R_ADC_B_ADTRGELC_TRGELC3                  (1 << 3)  /* ELC Trigger m Enable */

#define R_ADC_B_ADTRGELC_TRGELC4                  (1 << 4)  /* ELC Trigger m Enable */

#define R_ADC_B_ADTRGELC_TRGELC5                  (1 << 5)  /* ELC Trigger m Enable */

/* ADTRGGPT Register bit definitions */
#define R_ADC_B_ADTRGGPT_TRGGPTA0                 (1 << 0)  /* GPT channel m A/D Conversion Starting Request A Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTA1                 (1 << 1)  /* GPT channel m A/D Conversion Starting Request A Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTA2                 (1 << 2)  /* GPT channel m A/D Conversion Starting Request A Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTA3                 (1 << 3)  /* GPT channel m A/D Conversion Starting Request A Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTA4                 (1 << 4)  /* GPT channel m A/D Conversion Starting Request A Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTA5                 (1 << 5)  /* GPT channel m A/D Conversion Starting Request A Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTA6                 (1 << 6)  /* GPT channel m A/D Conversion Starting Request A Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTA7                 (1 << 7)  /* GPT channel m A/D Conversion Starting Request A Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTA8                 (1 << 8)  /* GPT channel m A/D Conversion Starting Request A Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTA9                 (1 << 9)  /* GPT channel m A/D Conversion Starting Request A Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTA10                (1 << 10)  /* GPT channel m A/D Conversion Starting Request A Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTA11                (1 << 11)  /* GPT channel m A/D Conversion Starting Request A Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTA12                (1 << 12)  /* GPT channel m A/D Conversion Starting Request A Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTA13                (1 << 13)  /* GPT channel m A/D Conversion Starting Request A Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTB0                 (1 << 16)  /* GPT channel m A/D Conversion Starting Request B Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTB1                 (1 << 17)  /* GPT channel m A/D Conversion Starting Request B Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTB2                 (1 << 18)  /* GPT channel m A/D Conversion Starting Request B Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTB3                 (1 << 19)  /* GPT channel m A/D Conversion Starting Request B Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTB4                 (1 << 20)  /* GPT channel m A/D Conversion Starting Request B Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTB5                 (1 << 21)  /* GPT channel m A/D Conversion Starting Request B Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTB6                 (1 << 22)  /* GPT channel m A/D Conversion Starting Request B Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTB7                 (1 << 23)  /* GPT channel m A/D Conversion Starting Request B Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTB8                 (1 << 24)  /* GPT channel m A/D Conversion Starting Request B Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTB9                 (1 << 25)  /* GPT channel m A/D Conversion Starting Request B Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTB10                (1 << 26)  /* GPT channel m A/D Conversion Starting Request B Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTB11                (1 << 27)  /* GPT channel m A/D Conversion Starting Request B Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTB12                (1 << 28)  /* GPT channel m A/D Conversion Starting Request B Enable */

#define R_ADC_B_ADTRGGPT_TRGGPTB13                (1 << 29)  /* GPT channel m A/D Conversion Starting Request B Enable */

/* ADTRGDLR0 Register bit definitions */
#define R_ADC_B_ADTRGDLR0_TRGDLY0_SHIFT           (0)  /* Scan Group 0 Trigger Input Delay Configuration */
#define R_ADC_B_ADTRGDLR0_TRGDLY0_MASK            0xff

#define R_ADC_B_ADTRGDLR0_TRGDLY1_SHIFT           (16)  /* Scan Group 1 Trigger Input Delay Configuration */
#define R_ADC_B_ADTRGDLR0_TRGDLY1_MASK            0xff0000

/* ADTRGDLR1 Register bit definitions */
#define R_ADC_B_ADTRGDLR1_TRGDLY2_SHIFT           (0)  /* Scan Group 2 Trigger Input Delay Configuration */
#define R_ADC_B_ADTRGDLR1_TRGDLY2_MASK            0xff

#define R_ADC_B_ADTRGDLR1_TRGDLY3_SHIFT           (16)  /* Scan Group 3 Trigger Input Delay Configuration */
#define R_ADC_B_ADTRGDLR1_TRGDLY3_MASK            0xff0000

/* ADTRGDLR2 Register bit definitions */
#define R_ADC_B_ADTRGDLR2_TRGDLY4_SHIFT           (0)  /* Scan Group 4 Trigger Input Delay Configuration */
#define R_ADC_B_ADTRGDLR2_TRGDLY4_MASK            0xff

#define R_ADC_B_ADTRGDLR2_TRGDLY5_SHIFT           (16)  /* Scan Group 5 Trigger Input Delay Configuration */
#define R_ADC_B_ADTRGDLR2_TRGDLY5_MASK            0xff0000

/* ADTRGDLR3 Register bit definitions */
#define R_ADC_B_ADTRGDLR3_TRGDLY6_SHIFT           (0)  /* Scan Group 6 Trigger Input Delay Configuration */
#define R_ADC_B_ADTRGDLR3_TRGDLY6_MASK            0xff

#define R_ADC_B_ADTRGDLR3_TRGDLY7_SHIFT           (16)  /* Scan Group 7 Trigger Input Delay Configuration */
#define R_ADC_B_ADTRGDLR3_TRGDLY7_MASK            0xff0000

/* ADTRGDLR4 Register bit definitions */
#define R_ADC_B_ADTRGDLR4_TRGDLY8_SHIFT           (0)  /* Scan Group 8 Trigger Input Delay Configuration */
#define R_ADC_B_ADTRGDLR4_TRGDLY8_MASK            0xff

/* ADSGDCR Register bit definitions */
#define R_ADC_B_ADSGDCR_DIAGVAL_SHIFT             (0)  /* Self-diagnosis Mode Selection */
#define R_ADC_B_ADSGDCR_DIAGVAL_MASK              0x7
#  define R_ADC_B_ADSGDCR_DIAGVAL_000                     (0 << R_ADC_B_ADSGDCR_DIAGVAL_SHIFT)  /* Set when any self-diagnosis channel are not included. Setting prohibited when any self-diagnosis channels are included.  */
#  define R_ADC_B_ADSGDCR_DIAGVAL_100                     (4 << R_ADC_B_ADSGDCR_DIAGVAL_SHIFT)  /* Self-diagnosis mode 1 */
#  define R_ADC_B_ADSGDCR_DIAGVAL_101                     (5 << R_ADC_B_ADSGDCR_DIAGVAL_SHIFT)  /* Self-diagnosis mode 2 */
#  define R_ADC_B_ADSGDCR_DIAGVAL_110                     (6 << R_ADC_B_ADSGDCR_DIAGVAL_SHIFT)  /* Self-diagnosis mode 3 */

#define R_ADC_B_ADSGDCR_ADDISEN                   (1 << 16)  /* Disconnection Detection Assist Enable */

#define R_ADC_B_ADSGDCR_ADDISP                    (1 << 20)  /* Disconnection Detection Assist Mode Selection */

#define R_ADC_B_ADSGDCR_ADDISN                    (1 << 21)  /* Disconnection Detection Assist Mode Selection */

#define R_ADC_B_ADSGDCR_ADNDIS_SHIFT              (24)  /* Disconnection Detection Assist Period */
#define R_ADC_B_ADSGDCR_ADNDIS_MASK               0xff000000
#  define R_ADC_B_ADSGDCR_ADNDIS_0X0                      (0 << R_ADC_B_ADSGDCR_ADNDIS_SHIFT)  /* Setting prohibited when the disconnection detection assist function is enabled */
#  define R_ADC_B_ADSGDCR_ADNDIS_0X1                      (1 << R_ADC_B_ADSGDCR_ADNDIS_SHIFT)  /* Setting prohibited */
#  define R_ADC_B_ADSGDCR_ADNDIS_0X2                      (2 << R_ADC_B_ADSGDCR_ADNDIS_SHIFT)  /* Setting prohibited */
#  define R_ADC_B_ADSGDCR_ADNDIS_0X3                      (3 << R_ADC_B_ADSGDCR_ADNDIS_SHIFT)  /* Setting prohibited */

/* ADSSTR0 Register bit definitions */
#define R_ADC_B_ADSSTR0_SST0_SHIFT                (0)  /* Sampling State Table 0 */
#define R_ADC_B_ADSSTR0_SST0_MASK                 0x3ff

#define R_ADC_B_ADSSTR0_SST1_SHIFT                (16)  /* Sampling State Table 1 */
#define R_ADC_B_ADSSTR0_SST1_MASK                 0x3ff0000

/* ADSSTR1 Register bit definitions */
#define R_ADC_B_ADSSTR1_SST2_SHIFT                (0)  /* Sampling State Table 2 */
#define R_ADC_B_ADSSTR1_SST2_MASK                 0x3ff

#define R_ADC_B_ADSSTR1_SST3_SHIFT                (16)  /* Sampling State Table 3 */
#define R_ADC_B_ADSSTR1_SST3_MASK                 0x3ff0000

/* ADSSTR2 Register bit definitions */
#define R_ADC_B_ADSSTR2_SST4_SHIFT                (0)  /* Sampling State Table 4 */
#define R_ADC_B_ADSSTR2_SST4_MASK                 0x3ff

#define R_ADC_B_ADSSTR2_SST5_SHIFT                (16)  /* Sampling State Table 5 */
#define R_ADC_B_ADSSTR2_SST5_MASK                 0x3ff0000

/* ADSSTR3 Register bit definitions */
#define R_ADC_B_ADSSTR3_SST6_SHIFT                (0)  /* Sampling State Table 6 */
#define R_ADC_B_ADSSTR3_SST6_MASK                 0x3ff

#define R_ADC_B_ADSSTR3_SST7_SHIFT                (16)  /* Sampling State Table 7 */
#define R_ADC_B_ADSSTR3_SST7_MASK                 0x3ff0000

/* ADSSTR4 Register bit definitions */
#define R_ADC_B_ADSSTR4_SST8_SHIFT                (0)  /* Sampling State Table 8 */
#define R_ADC_B_ADSSTR4_SST8_MASK                 0x3ff

#define R_ADC_B_ADSSTR4_SST9_SHIFT                (16)  /* Sampling State Table 9 */
#define R_ADC_B_ADSSTR4_SST9_MASK                 0x3ff0000

/* ADSSTR5 Register bit definitions */
#define R_ADC_B_ADSSTR5_SST10_SHIFT               (0)  /* Sampling State Table 10 */
#define R_ADC_B_ADSSTR5_SST10_MASK                0x3ff

#define R_ADC_B_ADSSTR5_SST11_SHIFT               (16)  /* Sampling State Table 11 */
#define R_ADC_B_ADSSTR5_SST11_MASK                0x3ff0000

/* ADSSTR6 Register bit definitions */
#define R_ADC_B_ADSSTR6_SST12_SHIFT               (0)  /* Sampling State Table 12 */
#define R_ADC_B_ADSSTR6_SST12_MASK                0x3ff

#define R_ADC_B_ADSSTR6_SST13_SHIFT               (16)  /* Sampling State Table 13 */
#define R_ADC_B_ADSSTR6_SST13_MASK                0x3ff0000

/* ADSSTR7 Register bit definitions */
#define R_ADC_B_ADSSTR7_SST14_SHIFT               (0)  /* Sampling State Table 14 */
#define R_ADC_B_ADSSTR7_SST14_MASK                0x3ff

#define R_ADC_B_ADSSTR7_SST15_SHIFT               (16)  /* Sampling State Table 15 */
#define R_ADC_B_ADSSTR7_SST15_MASK                0x3ff0000

/* ADCNVSTR Register bit definitions */
#define R_ADC_B_ADCNVSTR_CST0_SHIFT               (0)  /* A/D Converter Unit 0 (ADC0) */
#define R_ADC_B_ADCNVSTR_CST0_MASK                0x3f

#define R_ADC_B_ADCNVSTR_CST1_SHIFT               (8)  /* A/D Converter Unit 1 (ADC1) */
#define R_ADC_B_ADCNVSTR_CST1_MASK                0x3f00

/* ADCALSTCR Register bit definitions */
#define R_ADC_B_ADCALSTCR_CALADSST_SHIFT          (0)  /* A/D Converter Self-calibration Sampling Time Configuration */
#define R_ADC_B_ADCALSTCR_CALADSST_MASK           0x3ff

#define R_ADC_B_ADCALSTCR_CALADCST_SHIFT          (16)  /* A/D Converter Self-calibration Successive Approximation Time Configuration. */
#define R_ADC_B_ADCALSTCR_CALADCST_MASK           0x3f0000

/* ADSHCR0 Register bit definitions */
#define R_ADC_B_ADSHCR0_SHEN0                     (1 << 0)  /* Channel-dedicated Sample-and-hold Circuit Unit 0 Select */

#define R_ADC_B_ADSHCR0_SHEN1                     (1 << 1)  /* Channel-dedicated Sample-and-hold Circuit Unit 1 Select */

#define R_ADC_B_ADSHCR0_SHEN2                     (1 << 2)  /* Channel-dedicated Sample-and-hold Circuit Unit 2 Select */

#define R_ADC_B_ADSHCR0_SHMD0                     (1 << 16)  /* Channel-dedicated Sample-and-hold Circuit Unit 0 Input Mode Select */

#define R_ADC_B_ADSHCR0_SHMD1                     (1 << 17)  /* Channel-dedicated Sample-and-hold Circuit Unit 1 Input Mode Select */

#define R_ADC_B_ADSHCR0_SHMD2                     (1 << 18)  /* Channel-dedicated Sample-and-hold Circuit Unit 2 Input Mode Select */

/* ADSHDCR0 Register bit definitions */
#define R_ADC_B_ADSHDCR0_SH0DISEN                 (1 << 0)  /* A/D converter unit 0 channel-dedicated sample-and-hold circuit disconnection detection assist enable */

#define R_ADC_B_ADSHDCR0_SH0DIS                   (1 << 4)  /* A/D converter unit 0 channel-dedicated sample-and-hold circuit disconnection detection assist selection */

/* ADSHSTR0 Register bit definitions */
#define R_ADC_B_ADSHSTR0_SHSST_SHIFT              (0)  /* Channel-dedicated Sample-and-hold Circuit Unit 0 to 2 */
#define R_ADC_B_ADSHSTR0_SHSST_MASK               0xff

#define R_ADC_B_ADSHSTR0_SHHST_SHIFT              (16)  /* Channel-dedicated Sample-and-hold Circuit Unit 0 to 2 */
#define R_ADC_B_ADSHSTR0_SHHST_MASK               0x70000

/* ADSHCR1 Register bit definitions */
#define R_ADC_B_ADSHCR1_SHEN4                     (1 << 0)  /* Channel-dedicated Sample-and-hold Circuit Unit 4 Select */

#define R_ADC_B_ADSHCR1_SHEN5                     (1 << 1)  /* Channel-dedicated Sample-and-hold Circuit Unit 5 Select */

#define R_ADC_B_ADSHCR1_SHEN6                     (1 << 2)  /* Channel-dedicated Sample-and-hold Circuit Unit 6 Select */

#define R_ADC_B_ADSHCR1_SHMD4                     (1 << 16)  /* Channel-dedicated Sample-and-hold Circuit Unit 4 Input Mode Select */

#define R_ADC_B_ADSHCR1_SHMD5                     (1 << 17)  /* Channel-dedicated Sample-and-hold Circuit Unit 5 Input Mode Select */

#define R_ADC_B_ADSHCR1_SHMD6                     (1 << 18)  /* Channel-dedicated Sample-and-hold Circuit Unit 6 Input Mode Select */

/* ADSHDCR1 Register bit definitions */
#define R_ADC_B_ADSHDCR1_SH1DISEN                 (1 << 0)  /* A/D converter unit 1 channel-dedicated sample-and-hold circuit disconnection detection assist enable */

#define R_ADC_B_ADSHDCR1_SH1DIS                   (1 << 4)  /* A/D converter unit 1 channel-dedicated sample-and-hold circuit disconnection detection assist selection */

/* ADSHSTR1 Register bit definitions */
#define R_ADC_B_ADSHSTR1_SHSST_SHIFT              (0)  /* Channel-dedicated Sample-and-hold Circuit Unit 4 to 6 */
#define R_ADC_B_ADSHSTR1_SHSST_MASK               0xff

#define R_ADC_B_ADSHSTR1_SHHST_SHIFT              (16)  /* Channel-dedicated Sample-and-hold Circuit Unit 4 to 6 */
#define R_ADC_B_ADSHSTR1_SHHST_MASK               0x70000

/* ADCALSHCR Register bit definitions */
#define R_ADC_B_ADCALSHCR_CALSHSST_SHIFT          (0)  /* Channel-dedicated Sample-and-hold Circuit Self-calibration Sampling Time Configuration */
#define R_ADC_B_ADCALSHCR_CALSHSST_MASK           0xff

#define R_ADC_B_ADCALSHCR_CALSHHST_SHIFT          (16)  /* Channel-dedicated Sample-and-hold Circuit Self-calibration Hold Mode Switching Time Configuration */
#define R_ADC_B_ADCALSHCR_CALSHHST_MASK           0x70000

/* ADSHSBPCR Register bit definitions */
#define R_ADC_B_ADSHSBPCR_SHSBP0                  (1 << 0)  /* Channel-dedicated sample-and-hold circuit unit 0 single-ended input bypass selection (even-numbered analog channel) */

#define R_ADC_B_ADSHSBPCR_SHSBP1                  (1 << 1)  /* Channel-dedicated sample-and-hold circuit unit 1 single-ended input bypass selection (even-numbered analog channel) */

#define R_ADC_B_ADSHSBPCR_SHSBP2                  (1 << 2)  /* Channel-dedicated sample-and-hold circuit unit 2 single-ended input bypass selection (even-numbered analog channel) */

#define R_ADC_B_ADSHSBPCR_SHSBP4                  (1 << 4)  /* Channel-dedicated sample-and-hold circuit unit 4 single-ended input bypass selection (even-numbered analog channel) */

#define R_ADC_B_ADSHSBPCR_SHSBP5                  (1 << 5)  /* Channel-dedicated sample-and-hold circuit unit 5 single-ended input bypass selection (even-numbered analog channel) */

#define R_ADC_B_ADSHSBPCR_SHSBP6                  (1 << 6)  /* Channel-dedicated sample-and-hold circuit unit 6 single-ended input bypass selection (even-numbered analog channel) */

#define R_ADC_B_ADSHSBPCR_SHSBN0                  (1 << 16)  /* Channel-dedicated sample-and-hold circuit unit 0 single-ended input bypass selection (odd analog channel) */

#define R_ADC_B_ADSHSBPCR_SHSBN1                  (1 << 17)  /* Channel-dedicated sample-and-hold circuit unit 1 single-ended input bypass selection (odd analog channel) */

#define R_ADC_B_ADSHSBPCR_SHSBN2                  (1 << 18)  /* Channel-dedicated sample-and-hold circuit unit 2 single-ended input bypass selection (odd analog channel) */

#define R_ADC_B_ADSHSBPCR_SHSBN4                  (1 << 20)  /* Channel-dedicated sample-and-hold circuit unit 4 single-ended input bypass selection (odd analog channel) */

#define R_ADC_B_ADSHSBPCR_SHSBN5                  (1 << 21)  /* Channel-dedicated sample-and-hold circuit unit 5 single-ended input bypass selection (odd analog channel) */

#define R_ADC_B_ADSHSBPCR_SHSBN6                  (1 << 22)  /* Channel-dedicated sample-and-hold circuit unit 6 single-ended input bypass selection (odd analog channel) */

/* ADSHDBPCR Register bit definitions */
#define R_ADC_B_ADSHDBPCR_SHDBP0                  (1 << 0)  /* Scan group 0 channel-dedicated sample-and-hold circuit differential input bypass select */

#define R_ADC_B_ADSHDBPCR_SHDBP1                  (1 << 1)  /* Scan group 1 channel-dedicated sample-and-hold circuit differential input bypass select */

#define R_ADC_B_ADSHDBPCR_SHDBP2                  (1 << 2)  /* Scan group 2 channel-dedicated sample-and-hold circuit differential input bypass select */

#define R_ADC_B_ADSHDBPCR_SHDBP3                  (1 << 3)  /* Scan group 3 channel-dedicated sample-and-hold circuit differential input bypass select */

#define R_ADC_B_ADSHDBPCR_SHDBP4                  (1 << 4)  /* Scan group 4 channel-dedicated sample-and-hold circuit differential input bypass select */

#define R_ADC_B_ADSHDBPCR_SHDBP5                  (1 << 5)  /* Scan group 5 channel-dedicated sample-and-hold circuit differential input bypass select */

#define R_ADC_B_ADSHDBPCR_SHDBP6                  (1 << 6)  /* Scan group 6 channel-dedicated sample-and-hold circuit differential input bypass select */

#define R_ADC_B_ADSHDBPCR_SHDBP7                  (1 << 7)  /* Scan group 7 channel-dedicated sample-and-hold circuit differential input bypass select */

#define R_ADC_B_ADSHDBPCR_SHDBP8                  (1 << 8)  /* Scan group 8 channel-dedicated sample-and-hold circuit differential input bypass select */

/* ADSHSDCR0 Register bit definitions */
#define R_ADC_B_ADSHSDCR0_SHDIAG0_SHIFT           (0)  /* Scan group 0 channel-dedicated sample-and-hold circuit self-diagnostic voltage selection */
#define R_ADC_B_ADSHSDCR0_SHDIAG0_MASK            0x7
#  define R_ADC_B_ADSHSDCR0_SHDIAG0_000                   (0 << R_ADC_B_ADSHSDCR0_SHDIAG0_SHIFT)  /* Normal operation */
#  define R_ADC_B_ADSHSDCR0_SHDIAG0_001                   (1 << R_ADC_B_ADSHSDCR0_SHDIAG0_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR0_SHDIAG0_010                   (2 << R_ADC_B_ADSHSDCR0_SHDIAG0_SHIFT)  /* Self-diagnostic voltage −VREFH */
#  define R_ADC_B_ADSHSDCR0_SHDIAG0_011                   (3 << R_ADC_B_ADSHSDCR0_SHDIAG0_SHIFT)  /* Self-diagnostic voltage +VREFH */
#  define R_ADC_B_ADSHSDCR0_SHDIAG0_100                   (4 << R_ADC_B_ADSHSDCR0_SHDIAG0_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR0_SHDIAG0_101                   (5 << R_ADC_B_ADSHSDCR0_SHDIAG0_SHIFT)  /* Self-diagnostic voltage −VREFH/2 */
#  define R_ADC_B_ADSHSDCR0_SHDIAG0_110                   (6 << R_ADC_B_ADSHSDCR0_SHDIAG0_SHIFT)  /* Self-diagnostic voltage +VREFH/2 */
#  define R_ADC_B_ADSHSDCR0_SHDIAG0_111                   (7 << R_ADC_B_ADSHSDCR0_SHDIAG0_SHIFT)  /* Setting prohibited */

#define R_ADC_B_ADSHSDCR0_SHDIAG1_SHIFT           (4)  /* Scan group 1 channel-dedicated sample-and-hold circuit self-diagnostic voltage selection */
#define R_ADC_B_ADSHSDCR0_SHDIAG1_MASK            0x70
#  define R_ADC_B_ADSHSDCR0_SHDIAG1_000                   (0 << R_ADC_B_ADSHSDCR0_SHDIAG1_SHIFT)  /* Normal operation */
#  define R_ADC_B_ADSHSDCR0_SHDIAG1_001                   (1 << R_ADC_B_ADSHSDCR0_SHDIAG1_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR0_SHDIAG1_010                   (2 << R_ADC_B_ADSHSDCR0_SHDIAG1_SHIFT)  /* Self-diagnostic voltage −VREFH */
#  define R_ADC_B_ADSHSDCR0_SHDIAG1_011                   (3 << R_ADC_B_ADSHSDCR0_SHDIAG1_SHIFT)  /* Self-diagnostic voltage +VREFH */
#  define R_ADC_B_ADSHSDCR0_SHDIAG1_100                   (4 << R_ADC_B_ADSHSDCR0_SHDIAG1_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR0_SHDIAG1_101                   (5 << R_ADC_B_ADSHSDCR0_SHDIAG1_SHIFT)  /* Self-diagnostic voltage −VREFH/2 */
#  define R_ADC_B_ADSHSDCR0_SHDIAG1_110                   (6 << R_ADC_B_ADSHSDCR0_SHDIAG1_SHIFT)  /* Self-diagnostic voltage +VREFH/2 */
#  define R_ADC_B_ADSHSDCR0_SHDIAG1_111                   (7 << R_ADC_B_ADSHSDCR0_SHDIAG1_SHIFT)  /* Setting prohibited */

#define R_ADC_B_ADSHSDCR0_SHDIAG2_SHIFT           (8)  /* Scan group 2 channel-dedicated sample-and-hold circuit self-diagnostic voltage selection */
#define R_ADC_B_ADSHSDCR0_SHDIAG2_MASK            0x700
#  define R_ADC_B_ADSHSDCR0_SHDIAG2_000                   (0 << R_ADC_B_ADSHSDCR0_SHDIAG2_SHIFT)  /* Normal operation */
#  define R_ADC_B_ADSHSDCR0_SHDIAG2_001                   (1 << R_ADC_B_ADSHSDCR0_SHDIAG2_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR0_SHDIAG2_010                   (2 << R_ADC_B_ADSHSDCR0_SHDIAG2_SHIFT)  /* Self-diagnostic voltage −VREFH */
#  define R_ADC_B_ADSHSDCR0_SHDIAG2_011                   (3 << R_ADC_B_ADSHSDCR0_SHDIAG2_SHIFT)  /* Self-diagnostic voltage +VREFH */
#  define R_ADC_B_ADSHSDCR0_SHDIAG2_100                   (4 << R_ADC_B_ADSHSDCR0_SHDIAG2_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR0_SHDIAG2_101                   (5 << R_ADC_B_ADSHSDCR0_SHDIAG2_SHIFT)  /* Self-diagnostic voltage −VREFH/2 */
#  define R_ADC_B_ADSHSDCR0_SHDIAG2_110                   (6 << R_ADC_B_ADSHSDCR0_SHDIAG2_SHIFT)  /* Self-diagnostic voltage +VREFH/2 */
#  define R_ADC_B_ADSHSDCR0_SHDIAG2_111                   (7 << R_ADC_B_ADSHSDCR0_SHDIAG2_SHIFT)  /* Setting prohibited */

#define R_ADC_B_ADSHSDCR0_SHDIAG3_SHIFT           (12)  /* Scan group 3 channel-dedicated sample-and-hold circuit self-diagnostic voltage selection */
#define R_ADC_B_ADSHSDCR0_SHDIAG3_MASK            0x7000
#  define R_ADC_B_ADSHSDCR0_SHDIAG3_000                   (0 << R_ADC_B_ADSHSDCR0_SHDIAG3_SHIFT)  /* Normal operation */
#  define R_ADC_B_ADSHSDCR0_SHDIAG3_001                   (1 << R_ADC_B_ADSHSDCR0_SHDIAG3_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR0_SHDIAG3_010                   (2 << R_ADC_B_ADSHSDCR0_SHDIAG3_SHIFT)  /* Self-diagnostic voltage −VREFH */
#  define R_ADC_B_ADSHSDCR0_SHDIAG3_011                   (3 << R_ADC_B_ADSHSDCR0_SHDIAG3_SHIFT)  /* Self-diagnostic voltage +VREFH */
#  define R_ADC_B_ADSHSDCR0_SHDIAG3_100                   (4 << R_ADC_B_ADSHSDCR0_SHDIAG3_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR0_SHDIAG3_101                   (5 << R_ADC_B_ADSHSDCR0_SHDIAG3_SHIFT)  /* Self-diagnostic voltage −VREFH/2 */
#  define R_ADC_B_ADSHSDCR0_SHDIAG3_110                   (6 << R_ADC_B_ADSHSDCR0_SHDIAG3_SHIFT)  /* Self-diagnostic voltage +VREFH/2 */
#  define R_ADC_B_ADSHSDCR0_SHDIAG3_111                   (7 << R_ADC_B_ADSHSDCR0_SHDIAG3_SHIFT)  /* Setting prohibited */

#define R_ADC_B_ADSHSDCR0_SHDIAG4_SHIFT           (16)  /* Scan group 4 channel-dedicated sample-and-hold circuit self-diagnostic voltage selection */
#define R_ADC_B_ADSHSDCR0_SHDIAG4_MASK            0x70000
#  define R_ADC_B_ADSHSDCR0_SHDIAG4_000                   (0 << R_ADC_B_ADSHSDCR0_SHDIAG4_SHIFT)  /* Normal operation */
#  define R_ADC_B_ADSHSDCR0_SHDIAG4_001                   (1 << R_ADC_B_ADSHSDCR0_SHDIAG4_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR0_SHDIAG4_010                   (2 << R_ADC_B_ADSHSDCR0_SHDIAG4_SHIFT)  /* Self-diagnostic voltage −VREFH */
#  define R_ADC_B_ADSHSDCR0_SHDIAG4_011                   (3 << R_ADC_B_ADSHSDCR0_SHDIAG4_SHIFT)  /* Self-diagnostic voltage +VREFH */
#  define R_ADC_B_ADSHSDCR0_SHDIAG4_100                   (4 << R_ADC_B_ADSHSDCR0_SHDIAG4_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR0_SHDIAG4_101                   (5 << R_ADC_B_ADSHSDCR0_SHDIAG4_SHIFT)  /* Self-diagnostic voltage −VREFH/2 */
#  define R_ADC_B_ADSHSDCR0_SHDIAG4_110                   (6 << R_ADC_B_ADSHSDCR0_SHDIAG4_SHIFT)  /* Self-diagnostic voltage +VREFH/2 */
#  define R_ADC_B_ADSHSDCR0_SHDIAG4_111                   (7 << R_ADC_B_ADSHSDCR0_SHDIAG4_SHIFT)  /* Setting prohibited */

#define R_ADC_B_ADSHSDCR0_SHDIAG5_SHIFT           (20)  /* Scan group 5 channel-dedicated sample-and-hold circuit self-diagnostic voltage selection */
#define R_ADC_B_ADSHSDCR0_SHDIAG5_MASK            0x700000
#  define R_ADC_B_ADSHSDCR0_SHDIAG5_000                   (0 << R_ADC_B_ADSHSDCR0_SHDIAG5_SHIFT)  /* Normal operation */
#  define R_ADC_B_ADSHSDCR0_SHDIAG5_001                   (1 << R_ADC_B_ADSHSDCR0_SHDIAG5_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR0_SHDIAG5_010                   (2 << R_ADC_B_ADSHSDCR0_SHDIAG5_SHIFT)  /* Self-diagnostic voltage −VREFH */
#  define R_ADC_B_ADSHSDCR0_SHDIAG5_011                   (3 << R_ADC_B_ADSHSDCR0_SHDIAG5_SHIFT)  /* Self-diagnostic voltage +VREFH */
#  define R_ADC_B_ADSHSDCR0_SHDIAG5_100                   (4 << R_ADC_B_ADSHSDCR0_SHDIAG5_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR0_SHDIAG5_101                   (5 << R_ADC_B_ADSHSDCR0_SHDIAG5_SHIFT)  /* Self-diagnostic voltage −VREFH/2 */
#  define R_ADC_B_ADSHSDCR0_SHDIAG5_110                   (6 << R_ADC_B_ADSHSDCR0_SHDIAG5_SHIFT)  /* Self-diagnostic voltage +VREFH/2 */
#  define R_ADC_B_ADSHSDCR0_SHDIAG5_111                   (7 << R_ADC_B_ADSHSDCR0_SHDIAG5_SHIFT)  /* Setting prohibited */

#define R_ADC_B_ADSHSDCR0_SHDIAG6_SHIFT           (24)  /* Scan group 6 channel-dedicated sample-and-hold circuit self-diagnostic voltage selection */
#define R_ADC_B_ADSHSDCR0_SHDIAG6_MASK            0x7000000
#  define R_ADC_B_ADSHSDCR0_SHDIAG6_000                   (0 << R_ADC_B_ADSHSDCR0_SHDIAG6_SHIFT)  /* Normal operation */
#  define R_ADC_B_ADSHSDCR0_SHDIAG6_001                   (1 << R_ADC_B_ADSHSDCR0_SHDIAG6_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR0_SHDIAG6_010                   (2 << R_ADC_B_ADSHSDCR0_SHDIAG6_SHIFT)  /* Self-diagnostic voltage −VREFH */
#  define R_ADC_B_ADSHSDCR0_SHDIAG6_011                   (3 << R_ADC_B_ADSHSDCR0_SHDIAG6_SHIFT)  /* Self-diagnostic voltage +VREFH */
#  define R_ADC_B_ADSHSDCR0_SHDIAG6_100                   (4 << R_ADC_B_ADSHSDCR0_SHDIAG6_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR0_SHDIAG6_101                   (5 << R_ADC_B_ADSHSDCR0_SHDIAG6_SHIFT)  /* Self-diagnostic voltage −VREFH/2 */
#  define R_ADC_B_ADSHSDCR0_SHDIAG6_110                   (6 << R_ADC_B_ADSHSDCR0_SHDIAG6_SHIFT)  /* Self-diagnostic voltage +VREFH/2 */
#  define R_ADC_B_ADSHSDCR0_SHDIAG6_111                   (7 << R_ADC_B_ADSHSDCR0_SHDIAG6_SHIFT)  /* Setting prohibited */

#define R_ADC_B_ADSHSDCR0_SHDIAG7_SHIFT           (28)  /* Scan group 7 channel-dedicated sample-and-hold circuit self-diagnostic voltage selection */
#define R_ADC_B_ADSHSDCR0_SHDIAG7_MASK            0x70000000
#  define R_ADC_B_ADSHSDCR0_SHDIAG7_000                   (0 << R_ADC_B_ADSHSDCR0_SHDIAG7_SHIFT)  /* Normal operation */
#  define R_ADC_B_ADSHSDCR0_SHDIAG7_001                   (1 << R_ADC_B_ADSHSDCR0_SHDIAG7_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR0_SHDIAG7_010                   (2 << R_ADC_B_ADSHSDCR0_SHDIAG7_SHIFT)  /* Self-diagnostic voltage −VREFH */
#  define R_ADC_B_ADSHSDCR0_SHDIAG7_011                   (3 << R_ADC_B_ADSHSDCR0_SHDIAG7_SHIFT)  /* Self-diagnostic voltage +VREFH */
#  define R_ADC_B_ADSHSDCR0_SHDIAG7_100                   (4 << R_ADC_B_ADSHSDCR0_SHDIAG7_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR0_SHDIAG7_101                   (5 << R_ADC_B_ADSHSDCR0_SHDIAG7_SHIFT)  /* Self-diagnostic voltage −VREFH/2 */
#  define R_ADC_B_ADSHSDCR0_SHDIAG7_110                   (6 << R_ADC_B_ADSHSDCR0_SHDIAG7_SHIFT)  /* Self-diagnostic voltage +VREFH/2 */
#  define R_ADC_B_ADSHSDCR0_SHDIAG7_111                   (7 << R_ADC_B_ADSHSDCR0_SHDIAG7_SHIFT)  /* Setting prohibited */

/* ADSHSDCR1 Register bit definitions */
#define R_ADC_B_ADSHSDCR1_SHDIAG8_SHIFT           (0)  /* Scan group 8 channel-dedicated sample-and-hold circuit self-diagnostic voltage selection */
#define R_ADC_B_ADSHSDCR1_SHDIAG8_MASK            0x7
#  define R_ADC_B_ADSHSDCR1_SHDIAG8_000                   (0 << R_ADC_B_ADSHSDCR1_SHDIAG8_SHIFT)  /* Normal operation */
#  define R_ADC_B_ADSHSDCR1_SHDIAG8_001                   (1 << R_ADC_B_ADSHSDCR1_SHDIAG8_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR1_SHDIAG8_010                   (2 << R_ADC_B_ADSHSDCR1_SHDIAG8_SHIFT)  /* Self-diagnostic voltage −VREFH */
#  define R_ADC_B_ADSHSDCR1_SHDIAG8_011                   (3 << R_ADC_B_ADSHSDCR1_SHDIAG8_SHIFT)  /* Self-diagnostic voltage +VREFH */
#  define R_ADC_B_ADSHSDCR1_SHDIAG8_100                   (4 << R_ADC_B_ADSHSDCR1_SHDIAG8_SHIFT)  /* Self-diagnostic voltage 0 V */
#  define R_ADC_B_ADSHSDCR1_SHDIAG8_101                   (5 << R_ADC_B_ADSHSDCR1_SHDIAG8_SHIFT)  /* Self-diagnostic voltage −VREFH/2 */
#  define R_ADC_B_ADSHSDCR1_SHDIAG8_110                   (6 << R_ADC_B_ADSHSDCR1_SHDIAG8_SHIFT)  /* Self-diagnostic voltage +VREFH/2 */
#  define R_ADC_B_ADSHSDCR1_SHDIAG8_111                   (7 << R_ADC_B_ADSHSDCR1_SHDIAG8_SHIFT)  /* Setting prohibited */

/* ADREFCR Register bit definitions */
#define R_ADC_B_ADREFCR_VDE                       (1 << 0)  /* Internal Reference Voltage A/D Conversion Select */

/* ADDFSR Register bit definitions */
#define R_ADC_B_ADDFSR_DFSEL0_SHIFT               (0)  /* A/D Converter Unit n the 1st Digital Filter Characteristic Selection */
#define R_ADC_B_ADDFSR_DFSEL0_MASK                0x3
#  define R_ADC_B_ADDFSR_DFSEL0_01                        (1 << R_ADC_B_ADDFSR_DFSEL0_SHIFT)  /* Sinc filter */

#define R_ADC_B_ADDFSR_DFSEL1_SHIFT               (8)  /* A/D Converter Unit n the 2nd Digital Filter Characteristic Selection */
#define R_ADC_B_ADDFSR_DFSEL1_MASK                0x300
#  define R_ADC_B_ADDFSR_DFSEL1_01                        (1 << R_ADC_B_ADDFSR_DFSEL1_SHIFT)  /* Sinc filter */

#define R_ADC_B_ADDFSR_DFSEL2_SHIFT               (16)  /* A/D Converter Unit n the 3rd Digital Filter Characteristic Selection */
#define R_ADC_B_ADDFSR_DFSEL2_MASK                0x30000
#  define R_ADC_B_ADDFSR_DFSEL2_01                        (1 << R_ADC_B_ADDFSR_DFSEL2_SHIFT)  /* Sinc filter */

#define R_ADC_B_ADDFSR_DFSEL3_SHIFT               (24)  /* A/D Converter Unit n the 4th Digital Filter Characteristic Selection */
#define R_ADC_B_ADDFSR_DFSEL3_MASK                0x3000000
#  define R_ADC_B_ADDFSR_DFSEL3_01                        (1 << R_ADC_B_ADDFSR_DFSEL3_SHIFT)  /* Sinc filter */

/* ADUOFTR Register bit definitions */
#define R_ADC_B_ADUOFTR_UOFSET_SHIFT              (0)  /* User Offset Table n */
#define R_ADC_B_ADUOFTR_UOFSET_MASK               0xffff

/* ADUGTR Register bit definitions */
#define R_ADC_B_ADUGTR_UGAIN_SHIFT                (0)  /* User Gain Table n */
#define R_ADC_B_ADUGTR_UGAIN_MASK                 0xffff

/* ADLIMINTCR Register bit definitions */
#define R_ADC_B_ADLIMINTCR_LIMIE0                 (1 << 0)  /* Limiter Clip Interrupt n Enable bit */

#define R_ADC_B_ADLIMINTCR_LIMIE1                 (1 << 1)  /* Limiter Clip Interrupt n Enable bit */

#define R_ADC_B_ADLIMINTCR_LIMIE2                 (1 << 2)  /* Limiter Clip Interrupt n Enable bit */

#define R_ADC_B_ADLIMINTCR_LIMIE3                 (1 << 3)  /* Limiter Clip Interrupt n Enable bit */

#define R_ADC_B_ADLIMINTCR_LIMIE4                 (1 << 4)  /* Limiter Clip Interrupt n Enable bit */

#define R_ADC_B_ADLIMINTCR_LIMIE5                 (1 << 5)  /* Limiter Clip Interrupt n Enable bit */

#define R_ADC_B_ADLIMINTCR_LIMIE6                 (1 << 6)  /* Limiter Clip Interrupt n Enable bit */

#define R_ADC_B_ADLIMINTCR_LIMIE7                 (1 << 7)  /* Limiter Clip Interrupt n Enable bit */

#define R_ADC_B_ADLIMINTCR_LIMIE8                 (1 << 8)  /* Limiter Clip Interrupt n Enable bit */

#define R_ADC_B_ADLIMINTCR_LIMIEN_SHIFT           (0)  /* Limiter Clip Interrupt n Enable bit */
#define R_ADC_B_ADLIMINTCR_LIMIEN_MASK            0x1ff

/* ADLIMTR Register bit definitions */
#define R_ADC_B_ADLIMTR_LIML_SHIFT                (0)  /* Limiter clip table n : Lower-side limit value */
#define R_ADC_B_ADLIMTR_LIML_MASK                 0xffff

#define R_ADC_B_ADLIMTR_LIMU_SHIFT                (16)  /* Limiter clip table n : Upper-side limit value */
#define R_ADC_B_ADLIMTR_LIMU_MASK                 0xffff0000

/* ADCMPENR Register bit definitions */
#define R_ADC_B_ADCMPENR_CMPEN0                   (1 << 0)  /* Compare Match n Enable */

#define R_ADC_B_ADCMPENR_CMPEN1                   (1 << 1)  /* Compare Match n Enable */

#define R_ADC_B_ADCMPENR_CMPEN2                   (1 << 2)  /* Compare Match n Enable */

#define R_ADC_B_ADCMPENR_CMPEN3                   (1 << 3)  /* Compare Match n Enable */

#define R_ADC_B_ADCMPENR_CMPEN4                   (1 << 4)  /* Compare Match n Enable */

#define R_ADC_B_ADCMPENR_CMPEN5                   (1 << 5)  /* Compare Match n Enable */

#define R_ADC_B_ADCMPENR_CMPEN6                   (1 << 6)  /* Compare Match n Enable */

#define R_ADC_B_ADCMPENR_CMPEN7                   (1 << 7)  /* Compare Match n Enable */

#define R_ADC_B_ADCMPENR_CMPENN_SHIFT             (0)  /* Compare Match n Enable */
#define R_ADC_B_ADCMPENR_CMPENN_MASK              0xff

/* ADCMPINTCR Register bit definitions */
#define R_ADC_B_ADCMPINTCR_CMPIE0                 (1 << 0)  /* Compare Match Interrupt n Enable */

#define R_ADC_B_ADCMPINTCR_CMPIE1                 (1 << 1)  /* Compare Match Interrupt n Enable */

#define R_ADC_B_ADCMPINTCR_CMPIE2                 (1 << 2)  /* Compare Match Interrupt n Enable */

#define R_ADC_B_ADCMPINTCR_CMPIE3                 (1 << 3)  /* Compare Match Interrupt n Enable */

#define R_ADC_B_ADCMPINTCR_CMPIEN_SHIFT           (0)  /* Compare Match Interrupt n Enable */
#define R_ADC_B_ADCMPINTCR_CMPIEN_MASK            0xf

/* ADCCMPCR Register bit definitions */
#define R_ADC_B_ADCCMPCR_CCMPCND_SHIFT            (0)  /* Composite Compare Match Condition Selection */
#define R_ADC_B_ADCCMPCR_CCMPCND_MASK             0x3
#  define R_ADC_B_ADCCMPCR_CCMPCND_00                     (0 << R_ADC_B_ADCCMPCR_CCMPCND_SHIFT)  /* Logical disjunction (OR) conditions */

#define R_ADC_B_ADCCMPCR_CCMPTBL0                 (1 << 16)  /* Composite Compare Match Condition Table Selection */

#define R_ADC_B_ADCCMPCR_CCMPTBL1                 (1 << 17)  /* Composite Compare Match Condition Table Selection */

#define R_ADC_B_ADCCMPCR_CCMPTBL2                 (1 << 18)  /* Composite Compare Match Condition Table Selection */

#define R_ADC_B_ADCCMPCR_CCMPTBL3                 (1 << 19)  /* Composite Compare Match Condition Table Selection */

#define R_ADC_B_ADCCMPCR_CCMPTBL4                 (1 << 20)  /* Composite Compare Match Condition Table Selection */

#define R_ADC_B_ADCCMPCR_CCMPTBL5                 (1 << 21)  /* Composite Compare Match Condition Table Selection */

#define R_ADC_B_ADCCMPCR_CCMPTBL6                 (1 << 22)  /* Composite Compare Match Condition Table Selection */

#define R_ADC_B_ADCCMPCR_CCMPTBL7                 (1 << 23)  /* Composite Compare Match Condition Table Selection */

/* ADCMPMDR0 Register bit definitions */
#define R_ADC_B_ADCMPMDR0_CMPMD0_SHIFT            (0)  /* Compare Match 0 : Match Mode Selection */
#define R_ADC_B_ADCMPMDR0_CMPMD0_MASK             0x3
#  define R_ADC_B_ADCMPMDR0_CMPMD0_00                     (0 << R_ADC_B_ADCMPMDR0_CMPMD0_SHIFT)  /* Generate the match event when high-side level or more */
#  define R_ADC_B_ADCMPMDR0_CMPMD0_01                     (1 << R_ADC_B_ADCMPMDR0_CMPMD0_SHIFT)  /* Generate the match event when low-side level or less */
#  define R_ADC_B_ADCMPMDR0_CMPMD0_10                     (2 << R_ADC_B_ADCMPMDR0_CMPMD0_SHIFT)  /* Generate the match event when high-side level or more, or low-side level or less */
#  define R_ADC_B_ADCMPMDR0_CMPMD0_11                     (3 << R_ADC_B_ADCMPMDR0_CMPMD0_SHIFT)  /* Generate the match event when low-side level or more and high-side level or less */

#define R_ADC_B_ADCMPMDR0_CMPMD1_SHIFT            (8)  /* Compare Match 1 : Match Mode Selection */
#define R_ADC_B_ADCMPMDR0_CMPMD1_MASK             0x300
#  define R_ADC_B_ADCMPMDR0_CMPMD1_00                     (0 << R_ADC_B_ADCMPMDR0_CMPMD1_SHIFT)  /* Generate the match event when high-side level or more */
#  define R_ADC_B_ADCMPMDR0_CMPMD1_01                     (1 << R_ADC_B_ADCMPMDR0_CMPMD1_SHIFT)  /* Generate the match event when low-side level or less */
#  define R_ADC_B_ADCMPMDR0_CMPMD1_10                     (2 << R_ADC_B_ADCMPMDR0_CMPMD1_SHIFT)  /* Generate the match event when high-side level or more, or low-side level or less */
#  define R_ADC_B_ADCMPMDR0_CMPMD1_11                     (3 << R_ADC_B_ADCMPMDR0_CMPMD1_SHIFT)  /* Generate the match event when low-side level or more and high-side level or less */

#define R_ADC_B_ADCMPMDR0_CMPMD2_SHIFT            (16)  /* Compare Match 2 : Match Mode Selection */
#define R_ADC_B_ADCMPMDR0_CMPMD2_MASK             0x30000
#  define R_ADC_B_ADCMPMDR0_CMPMD2_00                     (0 << R_ADC_B_ADCMPMDR0_CMPMD2_SHIFT)  /* Generate the match event when high-side level or more */
#  define R_ADC_B_ADCMPMDR0_CMPMD2_01                     (1 << R_ADC_B_ADCMPMDR0_CMPMD2_SHIFT)  /* Generate the match event when low-side level or less */
#  define R_ADC_B_ADCMPMDR0_CMPMD2_10                     (2 << R_ADC_B_ADCMPMDR0_CMPMD2_SHIFT)  /* Generate the match event when high-side level or more, or low-side level or less */
#  define R_ADC_B_ADCMPMDR0_CMPMD2_11                     (3 << R_ADC_B_ADCMPMDR0_CMPMD2_SHIFT)  /* Generate the match event when low-side level or more and high-side level or less */

#define R_ADC_B_ADCMPMDR0_CMPMD3_SHIFT            (24)  /* Compare Match 3 : Match Mode Selection */
#define R_ADC_B_ADCMPMDR0_CMPMD3_MASK             0x3000000
#  define R_ADC_B_ADCMPMDR0_CMPMD3_00                     (0 << R_ADC_B_ADCMPMDR0_CMPMD3_SHIFT)  /* Generate the match event when high-side level or more */
#  define R_ADC_B_ADCMPMDR0_CMPMD3_01                     (1 << R_ADC_B_ADCMPMDR0_CMPMD3_SHIFT)  /* Generate the match event when low-side level or less */
#  define R_ADC_B_ADCMPMDR0_CMPMD3_10                     (2 << R_ADC_B_ADCMPMDR0_CMPMD3_SHIFT)  /* Generate the match event when high-side level or more, or low-side level or less */
#  define R_ADC_B_ADCMPMDR0_CMPMD3_11                     (3 << R_ADC_B_ADCMPMDR0_CMPMD3_SHIFT)  /* Generate the match event when low-side level or more and high-side level or less */

/* ADCMPMDR1 Register bit definitions */
#define R_ADC_B_ADCMPMDR1_CMPMD4_SHIFT            (0)  /* Compare Match 4 : Match Mode Selection */
#define R_ADC_B_ADCMPMDR1_CMPMD4_MASK             0x3
#  define R_ADC_B_ADCMPMDR1_CMPMD4_00                     (0 << R_ADC_B_ADCMPMDR1_CMPMD4_SHIFT)  /* Generate the match event when high-side level or more */
#  define R_ADC_B_ADCMPMDR1_CMPMD4_01                     (1 << R_ADC_B_ADCMPMDR1_CMPMD4_SHIFT)  /* Generate the match event when low-side level or less */
#  define R_ADC_B_ADCMPMDR1_CMPMD4_10                     (2 << R_ADC_B_ADCMPMDR1_CMPMD4_SHIFT)  /* Generate the match event when high-side level or more, or low-side level or less */
#  define R_ADC_B_ADCMPMDR1_CMPMD4_11                     (3 << R_ADC_B_ADCMPMDR1_CMPMD4_SHIFT)  /* Generate the match event when low-side level or more and high-side level or less */

#define R_ADC_B_ADCMPMDR1_CMPMD5_SHIFT            (8)  /* Compare Match 5 : Match Mode Selection */
#define R_ADC_B_ADCMPMDR1_CMPMD5_MASK             0x300
#  define R_ADC_B_ADCMPMDR1_CMPMD5_00                     (0 << R_ADC_B_ADCMPMDR1_CMPMD5_SHIFT)  /* Generate the match event when high-side level or more */
#  define R_ADC_B_ADCMPMDR1_CMPMD5_01                     (1 << R_ADC_B_ADCMPMDR1_CMPMD5_SHIFT)  /* Generate the match event when low-side level or less */
#  define R_ADC_B_ADCMPMDR1_CMPMD5_10                     (2 << R_ADC_B_ADCMPMDR1_CMPMD5_SHIFT)  /* Generate the match event when high-side level or more, or low-side level or less */
#  define R_ADC_B_ADCMPMDR1_CMPMD5_11                     (3 << R_ADC_B_ADCMPMDR1_CMPMD5_SHIFT)  /* Generate the match event when low-side level or more and high-side level or less */

#define R_ADC_B_ADCMPMDR1_CMPMD6_SHIFT            (16)  /* Compare Match 6 : Match Mode Selection */
#define R_ADC_B_ADCMPMDR1_CMPMD6_MASK             0x30000
#  define R_ADC_B_ADCMPMDR1_CMPMD6_00                     (0 << R_ADC_B_ADCMPMDR1_CMPMD6_SHIFT)  /* Generate the match event when high-side level or more */
#  define R_ADC_B_ADCMPMDR1_CMPMD6_01                     (1 << R_ADC_B_ADCMPMDR1_CMPMD6_SHIFT)  /* Generate the match event when low-side level or less */
#  define R_ADC_B_ADCMPMDR1_CMPMD6_10                     (2 << R_ADC_B_ADCMPMDR1_CMPMD6_SHIFT)  /* Generate the match event when high-side level or more, or low-side level or less */
#  define R_ADC_B_ADCMPMDR1_CMPMD6_11                     (3 << R_ADC_B_ADCMPMDR1_CMPMD6_SHIFT)  /* Generate the match event when low-side level or more and high-side level or less */

#define R_ADC_B_ADCMPMDR1_CMPMD7_SHIFT            (24)  /* Compare Match 7 : Match Mode Selection */
#define R_ADC_B_ADCMPMDR1_CMPMD7_MASK             0x3000000
#  define R_ADC_B_ADCMPMDR1_CMPMD7_00                     (0 << R_ADC_B_ADCMPMDR1_CMPMD7_SHIFT)  /* Generate the match event when high-side level or more */
#  define R_ADC_B_ADCMPMDR1_CMPMD7_01                     (1 << R_ADC_B_ADCMPMDR1_CMPMD7_SHIFT)  /* Generate the match event when low-side level or less */
#  define R_ADC_B_ADCMPMDR1_CMPMD7_10                     (2 << R_ADC_B_ADCMPMDR1_CMPMD7_SHIFT)  /* Generate the match event when high-side level or more, or low-side level or less */
#  define R_ADC_B_ADCMPMDR1_CMPMD7_11                     (3 << R_ADC_B_ADCMPMDR1_CMPMD7_SHIFT)  /* Generate the match event when low-side level or more and high-side level or less */

/* ADCMPTBR Register bit definitions */
#define R_ADC_B_ADCMPTBR_CMPTBL_SHIFT             (0)  /* Compare Match Table n : Low-side level */
#define R_ADC_B_ADCMPTBR_CMPTBL_MASK              0xffff

#define R_ADC_B_ADCMPTBR_CMPTBH_SHIFT             (16)  /* Compare Match Table n : High-side level */
#define R_ADC_B_ADCMPTBR_CMPTBH_MASK              0xffff0000

/* ADFIFOCR Register bit definitions */
#define R_ADC_B_ADFIFOCR_FIFOEN0                  (1 << 0)  /* Scan Group n FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOEN1                  (1 << 1)  /* Scan Group n FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOEN2                  (1 << 2)  /* Scan Group n FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOEN3                  (1 << 3)  /* Scan Group n FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOEN4                  (1 << 4)  /* Scan Group n FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOEN5                  (1 << 5)  /* Scan Group n FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOEN6                  (1 << 6)  /* Scan Group n FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOEN7                  (1 << 7)  /* Scan Group n FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOEN8                  (1 << 8)  /* Scan Group n FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOCE0                  (1 << 16)  /* Scan Group n FIFO clear enable at scan start/resume */

#define R_ADC_B_ADFIFOCR_FIFOCE1                  (1 << 17)  /* Scan Group n FIFO clear enable at scan start/resume */

#define R_ADC_B_ADFIFOCR_FIFOCE2                  (1 << 18)  /* Scan Group n FIFO clear enable at scan start/resume */

#define R_ADC_B_ADFIFOCR_FIFOCE3                  (1 << 19)  /* Scan Group n FIFO clear enable at scan start/resume */

#define R_ADC_B_ADFIFOCR_FIFOCE4                  (1 << 20)  /* Scan Group n FIFO clear enable at scan start/resume */

#define R_ADC_B_ADFIFOCR_FIFOCE5                  (1 << 21)  /* Scan Group n FIFO clear enable at scan start/resume */

#define R_ADC_B_ADFIFOCR_FIFOCE6                  (1 << 22)  /* Scan Group n FIFO clear enable at scan start/resume */

#define R_ADC_B_ADFIFOCR_FIFOCE7                  (1 << 23)  /* Scan Group n FIFO clear enable at scan start/resume */

#define R_ADC_B_ADFIFOCR_FIFOCE8                  (1 << 24)  /* Scan Group n FIFO clear enable at scan start/resume */

/* ADFIFOINTCR Register bit definitions */
#define R_ADC_B_ADFIFOINTCR_FIFOIE0               (1 << 0)  /* Scan Group n FIFO Interrupt Enable */

#define R_ADC_B_ADFIFOINTCR_FIFOIE1               (1 << 1)  /* Scan Group n FIFO Interrupt Enable */

#define R_ADC_B_ADFIFOINTCR_FIFOIE2               (1 << 2)  /* Scan Group n FIFO Interrupt Enable */

#define R_ADC_B_ADFIFOINTCR_FIFOIE3               (1 << 3)  /* Scan Group n FIFO Interrupt Enable */

#define R_ADC_B_ADFIFOINTCR_FIFOIE4               (1 << 4)  /* Scan Group n FIFO Interrupt Enable */

#define R_ADC_B_ADFIFOINTCR_FIFOIE5               (1 << 5)  /* Scan Group n FIFO Interrupt Enable */

#define R_ADC_B_ADFIFOINTCR_FIFOIE6               (1 << 6)  /* Scan Group n FIFO Interrupt Enable */

#define R_ADC_B_ADFIFOINTCR_FIFOIE7               (1 << 7)  /* Scan Group n FIFO Interrupt Enable */

#define R_ADC_B_ADFIFOINTCR_FIFOIE8               (1 << 8)  /* Scan Group n FIFO Interrupt Enable */

/* ADFIFOINTLR0 Register bit definitions */
#define R_ADC_B_ADFIFOINTLR0_FIFOILV0_SHIFT       (0)  /* Scan Group 0 FIFO Interrupt Output Timing Setting */
#define R_ADC_B_ADFIFOINTLR0_FIFOILV0_MASK        0xf

#define R_ADC_B_ADFIFOINTLR0_FIFOILV1_SHIFT       (16)  /* Scan Group 1 FIFO Interrupt Output Timing Setting */
#define R_ADC_B_ADFIFOINTLR0_FIFOILV1_MASK        0xf0000

/* ADFIFOINTLR1 Register bit definitions */
#define R_ADC_B_ADFIFOINTLR1_FIFOILV2_SHIFT       (0)  /* Scan Group 2 FIFO Interrupt Output Timing Setting */
#define R_ADC_B_ADFIFOINTLR1_FIFOILV2_MASK        0xf

#define R_ADC_B_ADFIFOINTLR1_FIFOILV3_SHIFT       (16)  /* Scan Group 3 FIFO Interrupt Output Timing Setting */
#define R_ADC_B_ADFIFOINTLR1_FIFOILV3_MASK        0xf0000

/* ADFIFOINTLR2 Register bit definitions */
#define R_ADC_B_ADFIFOINTLR2_FIFOILV4_SHIFT       (0)  /* Scan Group 4 FIFO Interrupt Output Timing Setting */
#define R_ADC_B_ADFIFOINTLR2_FIFOILV4_MASK        0xf

#define R_ADC_B_ADFIFOINTLR2_FIFOILV5_SHIFT       (16)  /* Scan Group 5 FIFO Interrupt Output Timing Setting */
#define R_ADC_B_ADFIFOINTLR2_FIFOILV5_MASK        0xf0000

/* ADFIFOINTLR3 Register bit definitions */
#define R_ADC_B_ADFIFOINTLR3_FIFOILV6_SHIFT       (0)  /* Scan Group 6 FIFO Interrupt Output Timing Setting */
#define R_ADC_B_ADFIFOINTLR3_FIFOILV6_MASK        0xf

#define R_ADC_B_ADFIFOINTLR3_FIFOILV7_SHIFT       (16)  /* Scan Group 7 FIFO Interrupt Output Timing Setting */
#define R_ADC_B_ADFIFOINTLR3_FIFOILV7_MASK        0xf0000

/* ADFIFOINTLR4 Register bit definitions */
#define R_ADC_B_ADFIFOINTLR4_FIFOILV8_SHIFT       (0)  /* Scan Group 8 FIFO Interrupt Output Timing Setting */
#define R_ADC_B_ADFIFOINTLR4_FIFOILV8_MASK        0xf

/* ADCHCR Register bit definitions */
#define R_ADC_B_ADCHCR_SGSEL_SHIFT                (0)  /* Scan Group Selection */
#define R_ADC_B_ADCHCR_SGSEL_MASK                 0x1f

#define R_ADC_B_ADCHCR_CNVCS_SHIFT                (8)  /* A/D Conversion Channel Selection */
#define R_ADC_B_ADCHCR_CNVCS_MASK                 0x7f00

#define R_ADC_B_ADCHCR_AINMD                      (1 << 15)  /* Analog Input mode selection, */

#define R_ADC_B_ADCHCR_SSTSEL_SHIFT               (16)  /* Sampling State Table Selection */
#define R_ADC_B_ADCHCR_SSTSEL_MASK                0xf0000

/* ADDOPCRA Register bit definitions */
#define R_ADC_B_ADDOPCRA_DFSEL_SHIFT              (0)  /* Digital Filter Selection */
#define R_ADC_B_ADDOPCRA_DFSEL_MASK               0x7
#  define R_ADC_B_ADDOPCRA_DFSEL_0X0                      (0 << R_ADC_B_ADDOPCRA_DFSEL_SHIFT)  /* Not use the digital filter */
#  define R_ADC_B_ADDOPCRA_DFSEL_0X1                      (1 << R_ADC_B_ADDOPCRA_DFSEL_SHIFT)  /* Use the 1st digital filter */
#  define R_ADC_B_ADDOPCRA_DFSEL_0X2                      (2 << R_ADC_B_ADDOPCRA_DFSEL_SHIFT)  /* Use the 2nd digital filter */
#  define R_ADC_B_ADDOPCRA_DFSEL_0X3                      (3 << R_ADC_B_ADDOPCRA_DFSEL_SHIFT)  /* Use the 3rd digital filter */
#  define R_ADC_B_ADDOPCRA_DFSEL_0X4                      (4 << R_ADC_B_ADDOPCRA_DFSEL_SHIFT)  /* Use the 4th digital filter */

#define R_ADC_B_ADDOPCRA_GAINSEL_SHIFT            (16)  /* User Gain Table Selection */
#define R_ADC_B_ADDOPCRA_GAINSEL_MASK             0xf0000

#define R_ADC_B_ADDOPCRA_OFSETSEL_SHIFT           (24)  /* User Offset Table Selection */
#define R_ADC_B_ADDOPCRA_OFSETSEL_MASK            0xf000000

/* ADDOPCRB Register bit definitions */
#define R_ADC_B_ADDOPCRB_AVEMD_SHIFT              (0)  /* Addition/Averaging Mode Selection */
#define R_ADC_B_ADDOPCRB_AVEMD_MASK               0x3
#  define R_ADC_B_ADDOPCRB_AVEMD_00                       (0 << R_ADC_B_ADDOPCRB_AVEMD_SHIFT)  /* Not use Addition/Averaging mode */
#  define R_ADC_B_ADDOPCRB_AVEMD_01                       (1 << R_ADC_B_ADDOPCRB_AVEMD_SHIFT)  /* Addition mode */
#  define R_ADC_B_ADDOPCRB_AVEMD_10                       (2 << R_ADC_B_ADDOPCRB_AVEMD_SHIFT)  /* Averaging mode */
#  define R_ADC_B_ADDOPCRB_AVEMD_11                       (3 << R_ADC_B_ADDOPCRB_AVEMD_SHIFT)  /* Setting prohibited */

#define R_ADC_B_ADDOPCRB_ADC_SHIFT                (8)  /* Addition/Averaging Times Selection */
#define R_ADC_B_ADDOPCRB_ADC_MASK                 0xf00
#  define R_ADC_B_ADDOPCRB_ADC_0X0                        (0 << R_ADC_B_ADDOPCRB_ADC_SHIFT)  /* 1-time conversion (no addition, same as normal conversion) */
#  define R_ADC_B_ADDOPCRB_ADC_0X1                        (1 << R_ADC_B_ADDOPCRB_ADC_SHIFT)  /* 2-time conversion (1 addition) */
#  define R_ADC_B_ADDOPCRB_ADC_0X3                        (3 << R_ADC_B_ADDOPCRB_ADC_SHIFT)  /* 4-time conversion (3 additions) */
#  define R_ADC_B_ADDOPCRB_ADC_0X4                        (4 << R_ADC_B_ADDOPCRB_ADC_SHIFT)  /* 8-time conversion (7 additions) */
#  define R_ADC_B_ADDOPCRB_ADC_0X5                        (5 << R_ADC_B_ADDOPCRB_ADC_SHIFT)  /* 16-time conversion (15 additions) */
#  define R_ADC_B_ADDOPCRB_ADC_0X6                        (6 << R_ADC_B_ADDOPCRB_ADC_SHIFT)  /* 32-time conversion (31 additions) */
#  define R_ADC_B_ADDOPCRB_ADC_0X7                        (7 << R_ADC_B_ADDOPCRB_ADC_SHIFT)  /* 64-time conversion (63 additions) */
#  define R_ADC_B_ADDOPCRB_ADC_0X8                        (8 << R_ADC_B_ADDOPCRB_ADC_SHIFT)  /* 128-time conversion (127 additions) */
#  define R_ADC_B_ADDOPCRB_ADC_0X9                        (9 << R_ADC_B_ADDOPCRB_ADC_SHIFT)  /* 256-time conversion (255 additions) */
#  define R_ADC_B_ADDOPCRB_ADC_0XA                        (10 << R_ADC_B_ADDOPCRB_ADC_SHIFT)  /* 512-time conversion (511 additions) */
#  define R_ADC_B_ADDOPCRB_ADC_0XB                        (11 << R_ADC_B_ADDOPCRB_ADC_SHIFT)  /* 1024-time conversion (1023 additions) */

#define R_ADC_B_ADDOPCRB_CMPTBLE0                 (1 << 16)  /* Compare Match Enable */

#define R_ADC_B_ADDOPCRB_CMPTBLE1                 (1 << 17)  /* Compare Match Enable */

#define R_ADC_B_ADDOPCRB_CMPTBLE2                 (1 << 18)  /* Compare Match Enable */

#define R_ADC_B_ADDOPCRB_CMPTBLE3                 (1 << 19)  /* Compare Match Enable */

#define R_ADC_B_ADDOPCRB_CMPTBLE4                 (1 << 20)  /* Compare Match Enable */

#define R_ADC_B_ADDOPCRB_CMPTBLE5                 (1 << 21)  /* Compare Match Enable */

#define R_ADC_B_ADDOPCRB_CMPTBLE6                 (1 << 22)  /* Compare Match Enable */

#define R_ADC_B_ADDOPCRB_CMPTBLE7                 (1 << 23)  /* Compare Match Enable */

/* ADDOPCRC Register bit definitions */
#define R_ADC_B_ADDOPCRC_LIMTBLS_SHIFT            (0)  /* Limiter Clip Table Selection */
#define R_ADC_B_ADDOPCRC_LIMTBLS_MASK             0xf

#define R_ADC_B_ADDOPCRC_ADPRC_SHIFT              (16)  /* A/D Conversion Data Format Selection */
#define R_ADC_B_ADDOPCRC_ADPRC_MASK               0x30000
#  define R_ADC_B_ADDOPCRC_ADPRC_00                       (0 << R_ADC_B_ADDOPCRC_ADPRC_SHIFT)  /* Store the A/D conversion result as 16-bit data format */
#  define R_ADC_B_ADDOPCRC_ADPRC_01                       (1 << R_ADC_B_ADDOPCRC_ADPRC_SHIFT)  /* Store the A/D conversion result as 14-bit data format */
#  define R_ADC_B_ADDOPCRC_ADPRC_10                       (2 << R_ADC_B_ADDOPCRC_ADPRC_SHIFT)  /* Store the A/D conversion result as 12-bit data format */
#  define R_ADC_B_ADDOPCRC_ADPRC_11                       (3 << R_ADC_B_ADDOPCRC_ADPRC_SHIFT)  /* Store the A/D conversion result as 10-bit data format */

#define R_ADC_B_ADDOPCRC_SIGNSEL                  (1 << 20)  /* A/D Conversion Data Signed/Un-signed Selection */

/* ADCALSTR Register bit definitions */
#define R_ADC_B_ADCALSTR_ADCALST0_SHIFT           (0)  /* A/D Converter Unit 0 (ADC0) Self-calibration Start Control */
#define R_ADC_B_ADCALSTR_ADCALST0_MASK            0x7

#define R_ADC_B_ADCALSTR_ADCALST1_SHIFT           (8)  /* A/D Converter Unit 1 (ADC1) Self-calibration Start Control */
#define R_ADC_B_ADCALSTR_ADCALST1_MASK            0x700

/* ADSHCSCR Register bit definitions */
#define R_ADC_B_ADSHCSCR_SHCSST0                  (1 << 0)  /* Channel-dedicated sample-and-hold circuit constant sampling control bit for A/D converter unit 0 (ADC0) */

#define R_ADC_B_ADSHCSCR_SHCSST1                  (1 << 8)  /* Channel-dedicated sample-and-hold circuit constant sampling control bit for A/D converter unit 1 (ADC1) */

/* ADTRGENR Register bit definitions */
#define R_ADC_B_ADTRGENR_STTRGEN0                 (1 << 0)  /* Scan Group n A/D Conversion Start Trigger Enable */

#define R_ADC_B_ADTRGENR_STTRGEN1                 (1 << 1)  /* Scan Group n A/D Conversion Start Trigger Enable */

#define R_ADC_B_ADTRGENR_STTRGEN2                 (1 << 2)  /* Scan Group n A/D Conversion Start Trigger Enable */

#define R_ADC_B_ADTRGENR_STTRGEN3                 (1 << 3)  /* Scan Group n A/D Conversion Start Trigger Enable */

#define R_ADC_B_ADTRGENR_STTRGEN4                 (1 << 4)  /* Scan Group n A/D Conversion Start Trigger Enable */

#define R_ADC_B_ADTRGENR_STTRGEN5                 (1 << 5)  /* Scan Group n A/D Conversion Start Trigger Enable */

#define R_ADC_B_ADTRGENR_STTRGEN6                 (1 << 6)  /* Scan Group n A/D Conversion Start Trigger Enable */

#define R_ADC_B_ADTRGENR_STTRGEN7                 (1 << 7)  /* Scan Group n A/D Conversion Start Trigger Enable */

#define R_ADC_B_ADTRGENR_STTRGEN8                 (1 << 8)  /* Scan Group n A/D Conversion Start Trigger Enable */

#define R_ADC_B_ADTRGENR_STTRGENN_SHIFT           (0)  /* Scan Group n A/D Conversion Start Trigger Enable */
#define R_ADC_B_ADTRGENR_STTRGENN_MASK            0x1ff

/* ADSYSTR Register bit definitions */
#define R_ADC_B_ADSYSTR_ADSYST0                   (1 << 0)  /* Scan Group n: A/D Conversion start */

#define R_ADC_B_ADSYSTR_ADSYST1                   (1 << 1)  /* Scan Group n: A/D Conversion start */

#define R_ADC_B_ADSYSTR_ADSYST2                   (1 << 2)  /* Scan Group n: A/D Conversion start */

#define R_ADC_B_ADSYSTR_ADSYST3                   (1 << 3)  /* Scan Group n: A/D Conversion start */

#define R_ADC_B_ADSYSTR_ADSYST4                   (1 << 4)  /* Scan Group n: A/D Conversion start */

#define R_ADC_B_ADSYSTR_ADSYST5                   (1 << 5)  /* Scan Group n: A/D Conversion start */

#define R_ADC_B_ADSYSTR_ADSYST6                   (1 << 6)  /* Scan Group n: A/D Conversion start */

#define R_ADC_B_ADSYSTR_ADSYST7                   (1 << 7)  /* Scan Group n: A/D Conversion start */

#define R_ADC_B_ADSYSTR_ADSYST8                   (1 << 8)  /* Scan Group n: A/D Conversion start */

#define R_ADC_B_ADSYSTR_ADSYSTN_SHIFT             (0)  /* Scan Group n : A/D Conversion start */
#define R_ADC_B_ADSYSTR_ADSYSTN_MASK              0x1ff

/* ADSTR Register bit definitions */
#define R_ADC_B_ADSTR_ADST                        (1 << 0)  /* Scan Group n A/D Conversion Start */

/* ADSTOPR Register bit definitions */
#define R_ADC_B_ADSTOPR_ADSTOP0                   (1 << 0)  /* A/D Converter Unit 0 Force Stop */

#define R_ADC_B_ADSTOPR_ADSTOP1                   (1 << 8)  /* A/D Converter Unit 1 Force Stop */

/* ADSR Register bit definitions */
#define R_ADC_B_ADSR_ADACT0                       (1 << 0)  /* A/D Converter Unit 0 (ADC0) A/D Conversion Status */

#define R_ADC_B_ADSR_ADACT1                       (1 << 1)  /* A/D Converter Unit 1 (ADC1) A/D Conversion Status */

#define R_ADC_B_ADSR_CALACT0                      (1 << 16)  /* A/D Converter Unit 0 (ADC0) : Calibration Status */

#define R_ADC_B_ADSR_CALACT1                      (1 << 17)  /* A/D Converter Unit 1 (ADC1) : Calibration Status */

/* ADGRSR Register bit definitions */
#define R_ADC_B_ADGRSR_ACTGR0                     (1 << 0)  /* Scan Group n Status */

#define R_ADC_B_ADGRSR_ACTGR1                     (1 << 1)  /* Scan Group n Status */

#define R_ADC_B_ADGRSR_ACTGR2                     (1 << 2)  /* Scan Group n Status */

#define R_ADC_B_ADGRSR_ACTGR3                     (1 << 3)  /* Scan Group n Status */

#define R_ADC_B_ADGRSR_ACTGR4                     (1 << 4)  /* Scan Group n Status */

#define R_ADC_B_ADGRSR_ACTGR5                     (1 << 5)  /* Scan Group n Status */

#define R_ADC_B_ADGRSR_ACTGR6                     (1 << 6)  /* Scan Group n Status */

#define R_ADC_B_ADGRSR_ACTGR7                     (1 << 7)  /* Scan Group n Status */

#define R_ADC_B_ADGRSR_ACTGR8                     (1 << 8)  /* Scan Group n Status */

#define R_ADC_B_ADGRSR_ACTGRN_SHIFT               (0)  /* Scan Group n Status */
#define R_ADC_B_ADGRSR_ACTGRN_MASK                0x1ff

/* ADERSR Register bit definitions */
#define R_ADC_B_ADERSR_ADERF0                     (1 << 0)  /* A/D Converter Unit 0 (ADC0) Error Flag */

#define R_ADC_B_ADERSR_ADERF1                     (1 << 1)  /* A/D Converter Unit 1 (ADC1) Error Flag */

/* ADERSCR Register bit definitions */
#define R_ADC_B_ADERSCR_ADERCLR0                  (1 << 0)  /* A/D Converter Unit 0 Error Flag Clear */

#define R_ADC_B_ADERSCR_ADERCLR1                  (1 << 1)  /* A/D Converter Unit 1 Error Flag Clear */

/* ADCALENDSR Register bit definitions */
#define R_ADC_B_ADCALENDSR_CALENDF0               (1 << 0)  /* A/D Converter Unit 0 Calibration End flag */

#define R_ADC_B_ADCALENDSR_CALENDF1               (1 << 1)  /* A/D Converter Unit 1 Calibration End flag */

/* ADCALENDSCR Register bit definitions */
#define R_ADC_B_ADCALENDSCR_CALENDC0              (1 << 0)  /* A/D Converter Unit 0 Calibration End Flag Clear */

#define R_ADC_B_ADCALENDSCR_CALENDC1              (1 << 1)  /* A/D Converter Unit 1 Calibration End Flag Clear */

/* ADOVFERSR Register bit definitions */
#define R_ADC_B_ADOVFERSR_ADOVFEF0                (1 << 0)  /* A/D Converter Unit 0 (ADC0) Overflow Error Flag */

#define R_ADC_B_ADOVFERSR_ADOVFEF1                (1 << 1)  /* A/D Converter Unit 1 (ADC1) Overflow Error Flag */

/* ADOVFCHSR0 Register bit definitions */
#define R_ADC_B_ADOVFCHSR0_OVFCHF0                (1 << 0)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF1                (1 << 1)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF2                (1 << 2)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF3                (1 << 3)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF4                (1 << 4)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF5                (1 << 5)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF6                (1 << 6)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF7                (1 << 7)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF8                (1 << 8)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF9                (1 << 9)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF10               (1 << 10)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF11               (1 << 11)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF12               (1 << 12)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF13               (1 << 13)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF14               (1 << 14)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF15               (1 << 15)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF16               (1 << 16)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF17               (1 << 17)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF18               (1 << 18)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF19               (1 << 19)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF20               (1 << 20)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF21               (1 << 21)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHF22               (1 << 22)  /* Analog Channel n: Overflow Flag */

#define R_ADC_B_ADOVFCHSR0_OVFCHFN_SHIFT          (0)  /* Analog Input Channel No. n : Overflow Flag */
#define R_ADC_B_ADOVFCHSR0_OVFCHFN_MASK           0x7fffff

/* ADOVFEXSR Register bit definitions */
#define R_ADC_B_ADOVFEXSR_OVFEXF0                 (1 << 0)  /* Self-diagnosis channel for A/D unit 0: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF1                 (1 << 1)  /* Self-diagnosis channel for A/D unit 1: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF4                 (1 << 4)  /* Temperature sensor channel: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF5                 (1 << 5)  /* Internal reference voltage channel: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF6                 (1 << 6)  /* VBATT 1/6 voltage monitor output channel: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF8                 (1 << 8)  /* D/A converter 0 channel: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF9                 (1 << 9)  /* D/A converter 1 channel: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF16                (1 << 16)  /* Self-diagnosis channel for sample-and-hold circuit unit 0: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF17                (1 << 17)  /* Self-diagnosis channel for sample-and-hold circuit unit 1: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF18                (1 << 18)  /* Self-diagnosis channel for sample-and-hold circuit unit 2: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF20                (1 << 20)  /* Self-diagnosis channel for sample-and-hold circuit unit 4: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF21                (1 << 21)  /* Self-diagnosis channel for sample-and-hold circuit unit 5: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF22                (1 << 22)  /* Self-diagnosis channel for sample-and-hold circuit unit 6: Overflow Flag */

/* ADOVFERSCR Register bit definitions */
#define R_ADC_B_ADOVFERSCR_ADOVFEC0               (1 << 0)  /* A/D Converter Unit 0 (ADC0) Overflow Error Flag Clear */

#define R_ADC_B_ADOVFERSCR_ADOVFEC1               (1 << 1)  /* A/D Converter Unit 1 (ADC1) Overflow Error Flag Clear */

/* ADOVFCHSCR0 Register bit definitions */
#define R_ADC_B_ADOVFCHSCR0_OVFCHC0               (1 << 0)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC1               (1 << 1)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC2               (1 << 2)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC3               (1 << 3)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC4               (1 << 4)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC5               (1 << 5)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC6               (1 << 6)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC7               (1 << 7)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC8               (1 << 8)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC9               (1 << 9)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC10              (1 << 10)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC11              (1 << 11)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC12              (1 << 12)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC13              (1 << 13)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC14              (1 << 14)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC15              (1 << 15)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC16              (1 << 16)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC17              (1 << 17)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC18              (1 << 18)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC19              (1 << 19)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC20              (1 << 20)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC21              (1 << 21)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHC22              (1 << 22)  /* Analog Channel n: Overflow Flag Clear */

#define R_ADC_B_ADOVFCHSCR0_OVFCHCN_SHIFT         (0)  /* Analog Input Channel No. n : Overflow Flag Clear */
#define R_ADC_B_ADOVFCHSCR0_OVFCHCN_MASK          0x7fffff

/* ADOVFEXSCR Register bit definitions */
#define R_ADC_B_ADOVFEXSCR_OVFEXC0                (1 << 0)  /* Self-diagnosis Channel for A/D unit 0: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC1                (1 << 1)  /* Self-diagnosis Channel for A/D unit 1: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC4                (1 << 4)  /* Temperature Sensor Channel: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC5                (1 << 5)  /* Internal Reference Voltage Channel: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC6                (1 << 6)  /* VBATT 1/6 voltage monitor output Channel: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXF8                (1 << 8)  /* D/A Converter 0 Channel: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXF9                (1 << 9)  /* D/A Converter 1 Channel: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXF16               (1 << 16)  /* Self-diagnosis Channel for Sample-and-hold circuit unit0: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXF17               (1 << 17)  /* Self-diagnosis Channel for Sample-and-hold circuit unit1: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC18               (1 << 18)  /* Self-diagnosis Channel for Sample-and-hold circuit unit2: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC20               (1 << 20)  /* Self-diagnosis Channel for Sample-and-hold circuit unit4: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC21               (1 << 21)  /* Self-diagnosis Channel for Sample-and-hold circuit unit5: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC22               (1 << 22)  /* Self-diagnosis Channel for Sample-and-hold circuit unit6: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC8                (1 << 8)  /* D/A Converter 0 Channel: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC9                (1 << 9)  /* D/A Converter 1 Channel: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC16               (1 << 16)  /* Self-diagnosis Channel for Sample-and-hold circuit unit0: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC17               (1 << 17)  /* Self-diagnosis Channel for Sample-and-hold circuit unit1: Compare Match Flag Clear */

/* ADFIFOSR0 Register bit definitions */
#define R_ADC_B_ADFIFOSR0_FIFOST0_SHIFT           (0)  /* Number of vacant stages in FIFO for Scan Group 0 */
#define R_ADC_B_ADFIFOSR0_FIFOST0_MASK            0xf

#define R_ADC_B_ADFIFOSR0_FIFOST1_SHIFT           (16)  /* Number of vacant stages in FIFO for Scan Group 1 */
#define R_ADC_B_ADFIFOSR0_FIFOST1_MASK            0xf0000

/* ADFIFOSR1 Register bit definitions */
#define R_ADC_B_ADFIFOSR1_FIFOST2_SHIFT           (0)  /* Number of vacant stages in FIFO for Scan Group 2 */
#define R_ADC_B_ADFIFOSR1_FIFOST2_MASK            0xf

#define R_ADC_B_ADFIFOSR1_FIFOST3_SHIFT           (16)  /* Number of vacant stages in FIFO for Scan Group 3 */
#define R_ADC_B_ADFIFOSR1_FIFOST3_MASK            0xf0000

/* ADFIFOSR2 Register bit definitions */
#define R_ADC_B_ADFIFOSR2_FIFOST4_SHIFT           (0)  /* Number of vacant stages in FIFO for Scan Group 4 */
#define R_ADC_B_ADFIFOSR2_FIFOST4_MASK            0xf

#define R_ADC_B_ADFIFOSR2_FIFOST5_SHIFT           (16)  /* Number of vacant stages in FIFO for Scan Group 5 */
#define R_ADC_B_ADFIFOSR2_FIFOST5_MASK            0xf0000

/* ADFIFOSR3 Register bit definitions */
#define R_ADC_B_ADFIFOSR3_FIFOST6_SHIFT           (0)  /* Number of vacant stages in FIFO for Scan Group 6 */
#define R_ADC_B_ADFIFOSR3_FIFOST6_MASK            0xf

#define R_ADC_B_ADFIFOSR3_FIFOST7_SHIFT           (16)  /* Number of vacant stages in FIFO for Scan Group 7 */
#define R_ADC_B_ADFIFOSR3_FIFOST7_MASK            0xf0000

/* ADFIFOSR4 Register bit definitions */
#define R_ADC_B_ADFIFOSR4_FIFOST8_SHIFT           (0)  /* Number of vacant stages in FIFO for Scan Group 8 */
#define R_ADC_B_ADFIFOSR4_FIFOST8_MASK            0xf

/* ADFIFODCR Register bit definitions */
#define R_ADC_B_ADFIFODCR_FIFODC0                 (1 << 0)  /* Scan Group n FIFO Data Clear */

#define R_ADC_B_ADFIFODCR_FIFODC1                 (1 << 1)  /* Scan Group n FIFO Data Clear */

#define R_ADC_B_ADFIFODCR_FIFODC2                 (1 << 2)  /* Scan Group n FIFO Data Clear */

#define R_ADC_B_ADFIFODCR_FIFODC3                 (1 << 3)  /* Scan Group n FIFO Data Clear */

#define R_ADC_B_ADFIFODCR_FIFODC4                 (1 << 4)  /* Scan Group n FIFO Data Clear */

#define R_ADC_B_ADFIFODCR_FIFODC5                 (1 << 5)  /* Scan Group n FIFO Data Clear */

#define R_ADC_B_ADFIFODCR_FIFODC6                 (1 << 6)  /* Scan Group n FIFO Data Clear */

#define R_ADC_B_ADFIFODCR_FIFODC7                 (1 << 7)  /* Scan Group n FIFO Data Clear */

#define R_ADC_B_ADFIFODCR_FIFODC8                 (1 << 8)  /* Scan Group n FIFO Data Clear */

#define R_ADC_B_ADFIFODCR_FIFODCN_SHIFT           (0)  /* Scan Group n FIFO Data Clear */
#define R_ADC_B_ADFIFODCR_FIFODCN_MASK            0x1ff

/* ADFIFOERSR Register bit definitions */
#define R_ADC_B_ADFIFOERSR_FIFOOVF0               (1 << 0)  /* Scan Group n FIFO Overflow Flag */

#define R_ADC_B_ADFIFOERSR_FIFOOVF1               (1 << 1)  /* Scan Group n FIFO Overflow Flag */

#define R_ADC_B_ADFIFOERSR_FIFOOVF2               (1 << 2)  /* Scan Group n FIFO Overflow Flag */

#define R_ADC_B_ADFIFOERSR_FIFOOVF3               (1 << 3)  /* Scan Group n FIFO Overflow Flag */

#define R_ADC_B_ADFIFOERSR_FIFOOVF4               (1 << 4)  /* Scan Group n FIFO Overflow Flag */

#define R_ADC_B_ADFIFOERSR_FIFOOVF5               (1 << 5)  /* Scan Group n FIFO Overflow Flag */

#define R_ADC_B_ADFIFOERSR_FIFOOVF6               (1 << 6)  /* Scan Group n FIFO Overflow Flag */

#define R_ADC_B_ADFIFOERSR_FIFOOVF7               (1 << 7)  /* Scan Group n FIFO Overflow Flag */

#define R_ADC_B_ADFIFOERSR_FIFOOVF8               (1 << 8)  /* Scan Group n FIFO Overflow Flag */

#define R_ADC_B_ADFIFOERSR_FIFOFLF0               (1 << 16)  /* Scan Group n FIFO Data Read Request Flag */

#define R_ADC_B_ADFIFOERSR_FIFOFLF1               (1 << 17)  /* Scan Group n FIFO Data Read Request Flag */

#define R_ADC_B_ADFIFOERSR_FIFOFLF2               (1 << 18)  /* Scan Group n FIFO Data Read Request Flag */

#define R_ADC_B_ADFIFOERSR_FIFOFLF3               (1 << 19)  /* Scan Group n FIFO Data Read Request Flag */

#define R_ADC_B_ADFIFOERSR_FIFOFLF4               (1 << 20)  /* Scan Group n FIFO Data Read Request Flag */

#define R_ADC_B_ADFIFOERSR_FIFOFLF5               (1 << 21)  /* Scan Group n FIFO Data Read Request Flag */

#define R_ADC_B_ADFIFOERSR_FIFOFLF6               (1 << 22)  /* Scan Group n FIFO Data Read Request Flag */

#define R_ADC_B_ADFIFOERSR_FIFOFLF7               (1 << 23)  /* Scan Group n FIFO Data Read Request Flag */

#define R_ADC_B_ADFIFOERSR_FIFOFLF8               (1 << 24)  /* Scan Group n FIFO Data Read Request Flag */

#define R_ADC_B_ADFIFOERSR_FIFOOVFN_SHIFT         (0)  /* Scan Group n FIFO Overflow Flag */
#define R_ADC_B_ADFIFOERSR_FIFOOVFN_MASK          0x1ff

#define R_ADC_B_ADFIFOERSR_FIFOFLFN_SHIFT         (16)  /* Scan Group n FIFO Data Full Flag */
#define R_ADC_B_ADFIFOERSR_FIFOFLFN_MASK          0x1ff0000

/* ADFIFOERSCR Register bit definitions */
#define R_ADC_B_ADFIFOERSCR_FIFOOVFC0             (1 << 0)  /* Scan Group n FIFO Overflow Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOOVFC1             (1 << 1)  /* Scan Group n FIFO Overflow Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOOVFC2             (1 << 2)  /* Scan Group n FIFO Overflow Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOOVFC3             (1 << 3)  /* Scan Group n FIFO Overflow Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOOVFC4             (1 << 4)  /* Scan Group n FIFO Overflow Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOOVFC5             (1 << 5)  /* Scan Group n FIFO Overflow Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOOVFC6             (1 << 6)  /* Scan Group n FIFO Overflow Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOOVFC7             (1 << 7)  /* Scan Group n FIFO Overflow Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOOVFC8             (1 << 8)  /* Scan Group n FIFO Overflow Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOFLC0              (1 << 16)  /* Scan Group n FIFO Data Read Request Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOFLC1              (1 << 17)  /* Scan Group n FIFO Data Read Request Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOFLC2              (1 << 18)  /* Scan Group n FIFO Data Read Request Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOFLC3              (1 << 19)  /* Scan Group n FIFO Data Read Request Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOFLC4              (1 << 20)  /* Scan Group n FIFO Data Read Request Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOFLC5              (1 << 21)  /* Scan Group n FIFO Data Read Request Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOFLC6              (1 << 22)  /* Scan Group n FIFO Data Read Request Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOFLC7              (1 << 23)  /* Scan Group n FIFO Data Read Request Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOFLC8              (1 << 24)  /* Scan Group n FIFO Data Read Request Flag Clear */

#define R_ADC_B_ADFIFOERSCR_FIFOOVFCN_SHIFT       (0)  /* Scan Group n FIFO Overflow Flag Clear */
#define R_ADC_B_ADFIFOERSCR_FIFOOVFCN_MASK        0x1ff

#define R_ADC_B_ADFIFOERSCR_FIFOFLCN_SHIFT        (16)  /* Scan Group n FIFO Data Full Flag Clear */
#define R_ADC_B_ADFIFOERSCR_FIFOFLCN_MASK         0x1ff0000

/* ADCMPTBSR Register bit definitions */
#define R_ADC_B_ADCMPTBSR_CMPTBF0                 (1 << 0)  /* Compare Match Table n Match Flag */

#define R_ADC_B_ADCMPTBSR_CMPTBF1                 (1 << 1)  /* Compare Match Table n Match Flag */

#define R_ADC_B_ADCMPTBSR_CMPTBF2                 (1 << 2)  /* Compare Match Table n Match Flag */

#define R_ADC_B_ADCMPTBSR_CMPTBF3                 (1 << 3)  /* Compare Match Table n Match Flag */

#define R_ADC_B_ADCMPTBSR_CMPTBF4                 (1 << 4)  /* Compare Match Table n Match Flag */

#define R_ADC_B_ADCMPTBSR_CMPTBF5                 (1 << 5)  /* Compare Match Table n Match Flag */

#define R_ADC_B_ADCMPTBSR_CMPTBF6                 (1 << 6)  /* Compare Match Table n Match Flag */

#define R_ADC_B_ADCMPTBSR_CMPTBF7                 (1 << 7)  /* Compare Match Table n Match Flag */

#define R_ADC_B_ADCMPTBSR_CMPTBFN_SHIFT           (0)  /* Compare Match Table n Match Flag */
#define R_ADC_B_ADCMPTBSR_CMPTBFN_MASK            0xff

/* ADCMPTBSCR Register bit definitions */
#define R_ADC_B_ADCMPTBSCR_CMPTBC0                (1 << 0)  /* Compare Match Table n: Match Flag Clear */

#define R_ADC_B_ADCMPTBSCR_CMPTBC1                (1 << 1)  /* Compare Match Table n: Match Flag Clear */

#define R_ADC_B_ADCMPTBSCR_CMPTBC2                (1 << 2)  /* Compare Match Table n: Match Flag Clear */

#define R_ADC_B_ADCMPTBSCR_CMPTBC3                (1 << 3)  /* Compare Match Table n: Match Flag Clear */

#define R_ADC_B_ADCMPTBSCR_CMPTBC4                (1 << 4)  /* Compare Match Table n: Match Flag Clear */

#define R_ADC_B_ADCMPTBSCR_CMPTBC5                (1 << 5)  /* Compare Match Table n: Match Flag Clear */

#define R_ADC_B_ADCMPTBSCR_CMPTBC6                (1 << 6)  /* Compare Match Table n: Match Flag Clear */

#define R_ADC_B_ADCMPTBSCR_CMPTBC7                (1 << 7)  /* Compare Match Table n: Match Flag Clear */

#define R_ADC_B_ADCMPTBSCR_CMPTBCN_SHIFT          (0)  /* Compare Match Table n : Match Flag Clear */
#define R_ADC_B_ADCMPTBSCR_CMPTBCN_MASK           0xff

/* ADCMPCHSR0 Register bit definitions */
#define R_ADC_B_ADCMPCHSR0_CMPCHF0                (1 << 0)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF1                (1 << 1)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF2                (1 << 2)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF3                (1 << 3)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF4                (1 << 4)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF5                (1 << 5)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF6                (1 << 6)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF7                (1 << 7)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF8                (1 << 8)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF9                (1 << 9)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF10               (1 << 10)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF11               (1 << 11)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF12               (1 << 12)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF13               (1 << 13)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF14               (1 << 14)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF15               (1 << 15)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF16               (1 << 16)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF17               (1 << 17)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF18               (1 << 18)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF19               (1 << 19)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF20               (1 << 20)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF21               (1 << 21)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHF22               (1 << 22)  /* Analog Channel n: Compare Match Flag */

#define R_ADC_B_ADCMPCHSR0_CMPCHFN_SHIFT          (0)  /* Analog Channel No. n : Compare Match Flag */
#define R_ADC_B_ADCMPCHSR0_CMPCHFN_MASK           0x7fffff

/* ADCMPEXSR Register bit definitions */
#define R_ADC_B_ADCMPEXSR_CMPEXF0                 (1 << 0)  /* Self-diagnosis channel for A/D unit 0: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF1                 (1 << 1)  /* Self-diagnosis channel for A/D unit 1: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF4                 (1 << 4)  /* Temperature sensor channel: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF5                 (1 << 5)  /* Internal reference voltage channel: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF6                 (1 << 6)  /* VBATT 1/6 voltage monitor output Channel: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF8                 (1 << 8)  /* D/A converter 0 channel: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF9                 (1 << 9)  /* D/A converter 1 channel: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF16                (1 << 16)  /* Self-diagnosis channel for sample-and-hold circuit unit 0: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF17                (1 << 17)  /* Self-diagnosis channel for sample-and-hold circuit unit 1: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF18                (1 << 18)  /* Self-diagnosis channel for sample-and-hold circuit unit 2: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF20                (1 << 20)  /* Self-diagnosis channel for sample-and-hold circuit unit 4: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF21                (1 << 21)  /* Self-diagnosis channel for sample-and-hold circuit unit 5: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF22                (1 << 22)  /* Self-diagnosis channel for sample-and-hold circuit unit 6: Compare Match Flag */

/* ADCMPCHSCR0 Register bit definitions */
#define R_ADC_B_ADCMPCHSCR0_CMPCHC0               (1 << 0)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC1               (1 << 1)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC2               (1 << 2)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC3               (1 << 3)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC4               (1 << 4)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC5               (1 << 5)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC6               (1 << 6)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC7               (1 << 7)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC8               (1 << 8)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC9               (1 << 9)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC10              (1 << 10)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC11              (1 << 11)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC12              (1 << 12)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC13              (1 << 13)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC14              (1 << 14)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC15              (1 << 15)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC16              (1 << 16)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC17              (1 << 17)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC18              (1 << 18)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC19              (1 << 19)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC20              (1 << 20)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC21              (1 << 21)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHC22              (1 << 22)  /* Analog channel n: Compare Match Flag Clear bit */

#define R_ADC_B_ADCMPCHSCR0_CMPCHCN_SHIFT         (0)  /* Analog Channel No. n : Compare Match Flag Clear bit */
#define R_ADC_B_ADCMPCHSCR0_CMPCHCN_MASK          0x7fffff

/* ADCMPEXSCR Register bit definitions */
#define R_ADC_B_ADCMPEXSCR_CMPEXC0                (1 << 0)  /* Self-diagnosis channel for A/D unit 0: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC1                (1 << 1)  /* Self-diagnosis channel for A/D unit 1: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC4                (1 << 4)  /* Temperature sensor channel: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC5                (1 << 5)  /* Internal reference voltage channel: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC6                (1 << 6)  /* VBATT 1/6 voltage monitor output channel: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC8                (1 << 8)  /* D/A converter 0 channel: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC9                (1 << 9)  /* D/A converter 1 channel: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC16               (1 << 16)  /* Self-diagnosis channel for sample-and-hold circuit unit 0: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC17               (1 << 17)  /* Self-diagnosis channel for sample-and-hold circuit unit 1: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC18               (1 << 18)  /* Self-diagnosis channel for sample-and-hold circuit unit 2: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC20               (1 << 20)  /* Self-diagnosis channel for sample-and-hold circuit unit 4: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC21               (1 << 21)  /* Self-diagnosis channel for sample-and-hold circuit unit 5: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC22               (1 << 22)  /* Self-diagnosis channel for sample-and-hold circuit unit 6: Compare Match Flag Clear */

/* ADLIMGRSR Register bit definitions */
#define R_ADC_B_ADLIMGRSR_LIMGRF0                 (1 << 0)  /* Scan Group n Limiter Clip Flag */

#define R_ADC_B_ADLIMGRSR_LIMGRF1                 (1 << 1)  /* Scan Group n Limiter Clip Flag */

#define R_ADC_B_ADLIMGRSR_LIMGRF2                 (1 << 2)  /* Scan Group n Limiter Clip Flag */

#define R_ADC_B_ADLIMGRSR_LIMGRF3                 (1 << 3)  /* Scan Group n Limiter Clip Flag */

#define R_ADC_B_ADLIMGRSR_LIMGRF4                 (1 << 4)  /* Scan Group n Limiter Clip Flag */

#define R_ADC_B_ADLIMGRSR_LIMGRF5                 (1 << 5)  /* Scan Group n Limiter Clip Flag */

#define R_ADC_B_ADLIMGRSR_LIMGRF6                 (1 << 6)  /* Scan Group n Limiter Clip Flag */

#define R_ADC_B_ADLIMGRSR_LIMGRF7                 (1 << 7)  /* Scan Group n Limiter Clip Flag */

#define R_ADC_B_ADLIMGRSR_LIMGRF8                 (1 << 8)  /* Scan Group n Limiter Clip Flag */

#define R_ADC_B_ADLIMGRSR_LIMGRFN_SHIFT           (0)  /* Scan Group n Limiter Clip Flag */
#define R_ADC_B_ADLIMGRSR_LIMGRFN_MASK            0x1ff

/* ADLIMCHSR0 Register bit definitions */
#define R_ADC_B_ADLIMCHSR0_LIMCHF0                (1 << 0)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF1                (1 << 1)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF2                (1 << 2)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF3                (1 << 3)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF4                (1 << 4)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF5                (1 << 5)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF6                (1 << 6)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF7                (1 << 7)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF8                (1 << 8)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF9                (1 << 9)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF10               (1 << 10)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF11               (1 << 11)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF12               (1 << 12)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF13               (1 << 13)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF14               (1 << 14)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF15               (1 << 15)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF16               (1 << 16)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF17               (1 << 17)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF18               (1 << 18)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF19               (1 << 19)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF20               (1 << 20)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF21               (1 << 21)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHF22               (1 << 22)  /* Analog Channel n: Limiter Clip Flag */

#define R_ADC_B_ADLIMCHSR0_LIMCHFN_SHIFT          (0)  /* Analog Channel No. n : Limiter Clip Flag bit */
#define R_ADC_B_ADLIMCHSR0_LIMCHFN_MASK           0x7fffff

/* ADLIMEXSR Register bit definitions */
#define R_ADC_B_ADLIMEXSR_LIMEXF0                 (1 << 0)  /* Self-diagnosis Channel for A/D unit 0: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF1                 (1 << 1)  /* Temperature Sensor Channel for A/D unit 1: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF4                 (1 << 4)  /* Temperature Sensor Channel: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF5                 (1 << 5)  /* Internal Reference Voltage Channel: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF6                 (1 << 6)  /* VBATT 1/6 voltage monitor output Channel: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF8                 (1 << 8)  /* D/A Converter 0 Channel: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF9                 (1 << 9)  /* D/A Converter 1 Channel: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF16                (1 << 16)  /* Self-diagnosis Channel for Sample-and-hold circuit unit0: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF17                (1 << 17)  /* Self-diagnosis Channel for Sample-and-hold circuit unit1: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF18                (1 << 18)  /* Self-diagnosis Channel for Sample-and-hold circuit unit2: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF20                (1 << 20)  /* Self-diagnosis Channel for Sample-and-hold circuit unit4: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF21                (1 << 21)  /* Self-diagnosis Channel for Sample-and-hold circuit unit5: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF22                (1 << 22)  /* Self-diagnosis Channel for Sample-and-hold circuit unit6: Limiter Clip Flag */

/* ADLIMGRSCR Register bit definitions */
#define R_ADC_B_ADLIMGRSCR_LIMGRC0                (1 << 0)  /* Scan Group n Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMGRSCR_LIMGRC1                (1 << 1)  /* Scan Group n Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMGRSCR_LIMGRC2                (1 << 2)  /* Scan Group n Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMGRSCR_LIMGRC3                (1 << 3)  /* Scan Group n Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMGRSCR_LIMGRC4                (1 << 4)  /* Scan Group n Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMGRSCR_LIMGRC5                (1 << 5)  /* Scan Group n Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMGRSCR_LIMGRC6                (1 << 6)  /* Scan Group n Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMGRSCR_LIMGRC7                (1 << 7)  /* Scan Group n Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMGRSCR_LIMGRC8                (1 << 8)  /* Scan Group n Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMGRSCR_LIMGRCN_SHIFT          (0)  /* Scan Group n Limiter Clip Flag Clear */
#define R_ADC_B_ADLIMGRSCR_LIMGRCN_MASK           0x1ff

/* ADLIMCHSCR0 Register bit definitions */
#define R_ADC_B_ADLIMCHSCR0_LIMCHC0               (1 << 0)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC1               (1 << 1)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC2               (1 << 2)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC3               (1 << 3)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC4               (1 << 4)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC5               (1 << 5)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC6               (1 << 6)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC7               (1 << 7)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC8               (1 << 8)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC9               (1 << 9)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC10              (1 << 10)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC11              (1 << 11)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC12              (1 << 12)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC13              (1 << 13)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC14              (1 << 14)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC15              (1 << 15)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC16              (1 << 16)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC17              (1 << 17)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC18              (1 << 18)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC19              (1 << 19)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC20              (1 << 20)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC21              (1 << 21)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHC22              (1 << 22)  /* Analog Channel n Limiter Clip Flag Clear bit */

#define R_ADC_B_ADLIMCHSCR0_LIMCHCN_SHIFT         (0)  /* Analog Channel No. n Limiter Clip Flag Clear bit */
#define R_ADC_B_ADLIMCHSCR0_LIMCHCN_MASK          0x7fffff

/* ADLIMEXSCR Register bit definitions */
#define R_ADC_B_ADLIMEXSCR_LIMEXC0                (1 << 0)  /* Self-diagnosis channel for A/D unit 0: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXC1                (1 << 1)  /* Self-diagnosis channel for A/D unit 1: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXC4                (1 << 4)  /* Temperature sensor channel: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXC5                (1 << 5)  /* Internal reference voltage channel: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXC6                (1 << 6)  /* VBATT 1/6 voltage monitor output channel: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXC8                (1 << 8)  /* D/A converter 0 channel: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXC9                (1 << 9)  /* D/A converter 1 channel: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXC16               (1 << 16)  /* Self-diagnosis channel for sample-and-hold circuit unit 0: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXC17               (1 << 17)  /* Self-diagnosis channel for sample-and-hold circuit unit 1: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXC18               (1 << 18)  /* Self-diagnosis channel for sample-and-hold circuit unit 2: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXC20               (1 << 20)  /* Self-diagnosis channel for sample-and-hold circuit unit 4: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXC21               (1 << 21)  /* Self-diagnosis channel for sample-and-hold circuit unit 5: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXC22               (1 << 22)  /* Self-diagnosis channel for sample-and-hold circuit unit 6: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXF0                (1 << 0)  /* Self-diagnosis Channel for A/D unit 0: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXF1                (1 << 1)  /* Self-diagnosis Channel for A/D unit 1: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXF4                (1 << 4)  /* Temperature Sensor Channel: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXF5                (1 << 5)  /* Internal Reference Voltage Channel: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXF6                (1 << 6)  /* VBATT 1/3 voltage monitor output Channel: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXF8                (1 << 8)  /* D/A Converter 0 Channel: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXF9                (1 << 9)  /* D/A Converter 1 Channel: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXF16               (1 << 16)  /* Self-diagnosis Channel for Sample-and-hold circuit unit0: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXF17               (1 << 17)  /* Self-diagnosis Channel for Sample-and-hold circuit unit1: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXF18               (1 << 18)  /* Self-diagnosis Channel for Sample-and-hold circuit unit2: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXF20               (1 << 20)  /* Self-diagnosis Channel for Sample-and-hold circuit unit4: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXF21               (1 << 21)  /* Self-diagnosis Channel for Sample-and-hold circuit unit5: Limiter Clip Flag Clear */

#define R_ADC_B_ADLIMEXSCR_LIMEXF22               (1 << 22)  /* Self-diagnosis Channel for Sample-and-hold circuit unit6: Limiter Clip Flag Clear */

/* ADSCANENDSR Register bit definitions */
#define R_ADC_B_ADSCANENDSR_SCENDF0               (1 << 0)  /* Scan Group n Scan End Flag */

#define R_ADC_B_ADSCANENDSR_SCENDF1               (1 << 1)  /* Scan Group n Scan End Flag */

#define R_ADC_B_ADSCANENDSR_SCENDF2               (1 << 2)  /* Scan Group n Scan End Flag */

#define R_ADC_B_ADSCANENDSR_SCENDF3               (1 << 3)  /* Scan Group n Scan End Flag */

#define R_ADC_B_ADSCANENDSR_SCENDF4               (1 << 4)  /* Scan Group n Scan End Flag */

#define R_ADC_B_ADSCANENDSR_SCENDF5               (1 << 5)  /* Scan Group n Scan End Flag */

#define R_ADC_B_ADSCANENDSR_SCENDF6               (1 << 6)  /* Scan Group n Scan End Flag */

#define R_ADC_B_ADSCANENDSR_SCENDF7               (1 << 7)  /* Scan Group n Scan End Flag */

#define R_ADC_B_ADSCANENDSR_SCENDF8               (1 << 8)  /* Scan Group n Scan End Flag */

#define R_ADC_B_ADSCANENDSR_SCENDFN_SHIFT         (0)  /* Scan Group n Scan End Flag */
#define R_ADC_B_ADSCANENDSR_SCENDFN_MASK          0x1ff

/* ADSCANENDSCR Register bit definitions */
#define R_ADC_B_ADSCANENDSCR_SCENDC0              (1 << 0)  /* Scan Group n Scan End Flag Clear */

#define R_ADC_B_ADSCANENDSCR_SCENDC1              (1 << 1)  /* Scan Group n Scan End Flag Clear */

#define R_ADC_B_ADSCANENDSCR_SCENDC2              (1 << 2)  /* Scan Group n Scan End Flag Clear */

#define R_ADC_B_ADSCANENDSCR_SCENDC3              (1 << 3)  /* Scan Group n Scan End Flag Clear */

#define R_ADC_B_ADSCANENDSCR_SCENDC4              (1 << 4)  /* Scan Group n Scan End Flag Clear */

#define R_ADC_B_ADSCANENDSCR_SCENDC5              (1 << 5)  /* Scan Group n Scan End Flag Clear */

#define R_ADC_B_ADSCANENDSCR_SCENDC6              (1 << 6)  /* Scan Group n Scan End Flag Clear */

#define R_ADC_B_ADSCANENDSCR_SCENDC7              (1 << 7)  /* Scan Group n Scan End Flag Clear */

#define R_ADC_B_ADSCANENDSCR_SCENDC8              (1 << 8)  /* Scan Group n Scan End Flag Clear */

#define R_ADC_B_ADSCANENDSCR_SCENDCN_SHIFT        (0)  /* Scan Group n Scan End Flag Clear */
#define R_ADC_B_ADSCANENDSCR_SCENDCN_MASK         0x1ff

/* ADDR Register bit definitions */
#define R_ADC_B_ADDR_DATA_SHIFT                   (0)  /* A/D conversion data */
#define R_ADC_B_ADDR_DATA_MASK                    0xffff

#define R_ADC_B_ADDR_ERR                          (1 << 31)  /* A/D conversion data error status */

/* ADFIFODR Register bit definitions */
#define R_ADC_B_ADFIFODR_DATA_SHIFT               (0)  /* A/D Conversion Data */
#define R_ADC_B_ADFIFODR_DATA_MASK                0xffff

#define R_ADC_B_ADFIFODR_CH_SHIFT                 (24)  /* A/D Conversion Channel Number */
#define R_ADC_B_ADFIFODR_CH_MASK                  0x7f000000

#define R_ADC_B_ADFIFODR_ERR                      (1 << 31)  /* A/D Conversion Data Error Status */


/* Maximum number of channels */

#define ADC_B_MAX_CHANNELS    33

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ADC_B_H */

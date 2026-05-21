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
#define R_ADC_B_ADERINTCR_OFFSET                  0x00000020  /* A/D Conversion Error Interrupt Enable Register */
#define R_ADC_B_ADOVFINTCR_OFFSET                 0x00000024  /* A/D Conversion Overflow Interrupt Enable Register */
#define R_ADC_B_ADCALINTCR_OFFSET                 0x00000028  /* Calibration interrupt Enable Register */
#define R_ADC_B_ADMDR_OFFSET                      0x00000040  /* A/D Converter Mode Selection Register */
#define R_ADC_B_ADGSPCR_OFFSET                    0x00000044  /* A/D Group scan Priority Control Register */
#define R_ADC_B_ADSGER_OFFSET                     0x00000048  /* Scan Group Enable Register */
#define R_ADC_B_ADSGCR0_OFFSET                    0x0000004c  /* Scan Group Control Register 0 */
#define R_ADC_B_ADSGCR1_OFFSET                    0x00000050  /* Scan Group Control Register 1 */
#define R_ADC_B_ADSGCR2_OFFSET                    0x00000054  /* Scan Group Control Register 2 */
#define R_ADC_B_ADINTCR_OFFSET                    0x0000005c  /* Scan End Interrupt Enable Register */
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
#define R_ADC_B_ADCALSTCR_OFFSET                  0x00000264  /* A/D Converter Calibration State Register */
#define R_ADC_B_ADSHCR0_OFFSET                    0x00000280  /* Channel-Dedicated Sample-and-Hold Circuit Control Register 0 */
#define R_ADC_B_ADSHSTR0_OFFSET                   0x00000288  /* Channel-Dedicated Sample & Hold Circuit State Register 0 */
#define R_ADC_B_ADSHCR1_OFFSET                    0x0000028c  /* Channel-Dedicated Sample-and-Hold Circuit Control Register 1 */
#define R_ADC_B_ADSHSTR1_OFFSET                   0x00000294  /* Channel-Dedicated Sample & Hold Circuit State Register 1 */
#define R_ADC_B_ADCALSHCR_OFFSET                  0x000002b0  /* Channel-Dedicated Sample & Hold Circuit Calibration State Register */
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
#define R_ADC_B_ADCALSTR_OFFSET                   0x00000c00  /* A/D Converter Calibration Start Register */
#define R_ADC_B_ADTRGENR_OFFSET                   0x00000c08  /* A/D Conversion Start Trigger Enable Register */
#define R_ADC_B_ADSYSTR_OFFSET                    0x00000c10  /* A/D Conversion Synchronous Software Start Register */
/* ADSTR[%s] Registers () */
#define R_ADC_B_ADSTR_OFFSET(m)                   (0x00000c20 + ((m) * 0x00000004))  /* A/D Conversion Software Start Register %s */
#define R_ADC_B_ADSTOPR_OFFSET                    0x00000c60  /* A/D Conversion Stop Register */
#define R_ADC_B_ADSR_OFFSET                       0x00000c80  /* A/D Conversion Status Register */
#define R_ADC_B_ADGRSR_OFFSET                     0x00000c84  /* Scan Group Status Register */
#define R_ADC_B_ADERSR_OFFSET                     0x00000c88  /* A/D Conversion Error Status Register */
#define R_ADC_B_ADERSCR_OFFSET                    0x00000c8c  /* A/D Conversion Error Status Clear Register */
#define R_ADC_B_ADCALENDSR_OFFSET                 0x00000c98  /* A/D Converter Calibration End Status Register */
#define R_ADC_B_ADCALENDSCR_OFFSET                0x00000c9c  /* A/D Converter Calibration End Status Clear Register */
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
/* ADDR[%s] Registers () */
#define R_ADC_B_ADDR_OFFSET(m)                    (0x00002000 + ((m) * 0x00000004))  /* A/D Data Register %s */
/* ADEXDR[%s] Registers () */
#define R_ADC_B_ADEXDR_OFFSET(m)                  (0x00002180 + ((m) * 0x00000004))  /* A/D Extended Analog Data Register %s */
/* ADFIFODR%s Registers (0-8) */
#define R_ADC_B_ADFIFODR_OFFSET(m)                (0x00002200 + ((m) * 0x00000004))  /* FIFO Data Register %s */

/* ADC_B Register Addresses */

#define R_ADC_B_ADCLKENR                          (R_ADC_B_BASE + R_ADC_B_ADCLKENR_OFFSET)
#define R_ADC_B_ADCLKSR                           (R_ADC_B_BASE + R_ADC_B_ADCLKSR_OFFSET)
#define R_ADC_B_ADCLKCR                           (R_ADC_B_BASE + R_ADC_B_ADCLKCR_OFFSET)
#define R_ADC_B_ADSYCR                            (R_ADC_B_BASE + R_ADC_B_ADSYCR_OFFSET)
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
#define R_ADC_B_ADSHSTR0                          (R_ADC_B_BASE + R_ADC_B_ADSHSTR0_OFFSET)
#define R_ADC_B_ADSHCR1                           (R_ADC_B_BASE + R_ADC_B_ADSHCR1_OFFSET)
#define R_ADC_B_ADSHSTR1                          (R_ADC_B_BASE + R_ADC_B_ADSHSTR1_OFFSET)
#define R_ADC_B_ADCALSHCR                         (R_ADC_B_BASE + R_ADC_B_ADCALSHCR_OFFSET)
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
#define R_ADC_B_ADEXDR(m)                         (R_ADC_B_BASE + R_ADC_B_ADEXDR_OFFSET(m))
#define R_ADC_B_ADFIFODR(m)                       (R_ADC_B_BASE + R_ADC_B_ADFIFODR_OFFSET(m))

/* Register bit definitions */
/* ADCLKENR Register bit definitions */
#define R_ADC_B_ADCLKENR_CLKEN                    (1 << 0)  /* ADCLK Operating Enable bit */

/* ADCLKSR Register bit definitions */
#define R_ADC_B_ADCLKSR_CLKSR                     (1 << 0)  /* ADCLK status bit */

/* ADCLKCR Register bit definitions */
#define R_ADC_B_ADCLKCR_CLKSEL_SHIFT              (0)  /* ADCLK Clock Source Select */
#define R_ADC_B_ADCLKCR_CLKSEL_MASK               0x3
#  define R_ADC_B_ADCLKCR_CLKSEL_00                       (0 << R_ADC_B_ADCLKCR_CLKSEL_SHIFT)  /* Peripheral Module Clock C (PCLKC) */
#  define R_ADC_B_ADCLKCR_CLKSEL_01                       (1 << R_ADC_B_ADCLKCR_CLKSEL_SHIFT)  /* GPT clock (GPTCLK) */
#  define R_ADC_B_ADCLKCR_CLKSEL_10                       (2 << R_ADC_B_ADCLKCR_CLKSEL_SHIFT)  /* Peripheral Module Clock A (PCLKA) */
#  define R_ADC_B_ADCLKCR_CLKSEL_01                       (1 << R_ADC_B_ADCLKCR_CLKSEL_SHIFT)  /* Setting prohibited */

#define R_ADC_B_ADCLKCR_DIVR_SHIFT                (16)  /* Clock Division Ratio Select */
#define R_ADC_B_ADCLKCR_DIVR_MASK                 0x70000
#  define R_ADC_B_ADCLKCR_DIVR_000                        (0 << R_ADC_B_ADCLKCR_DIVR_SHIFT)  /* 1/1 */
#  define R_ADC_B_ADCLKCR_DIVR_001                        (1 << R_ADC_B_ADCLKCR_DIVR_SHIFT)  /* 1/2 */
#  define R_ADC_B_ADCLKCR_DIVR_010                        (2 << R_ADC_B_ADCLKCR_DIVR_SHIFT)  /* 1/3 */
#  define R_ADC_B_ADCLKCR_DIVR_011                        (3 << R_ADC_B_ADCLKCR_DIVR_SHIFT)  /* 1/4 */
#  define R_ADC_B_ADCLKCR_DIVR_100                        (4 << R_ADC_B_ADCLKCR_DIVR_SHIFT)  /* 1/5 */
#  define R_ADC_B_ADCLKCR_DIVR_101                        (5 << R_ADC_B_ADCLKCR_DIVR_SHIFT)  /* 1/6 */
#  define R_ADC_B_ADCLKCR_DIVR_110                        (6 << R_ADC_B_ADCLKCR_DIVR_SHIFT)  /* 1/7 */
#  define R_ADC_B_ADCLKCR_DIVR_111                        (7 << R_ADC_B_ADCLKCR_DIVR_SHIFT)  /* 1/8 */

/* ADSYCR Register bit definitions */
#define R_ADC_B_ADSYCR_ADSYCYC_SHIFT              (0)  /* A/D Converter Synchronous Operation Period Cycle */
#define R_ADC_B_ADSYCR_ADSYCYC_MASK               0x7ff

#define R_ADC_B_ADSYCR_ADSYDIS0                   (1 << 16)  /* ADC0 Synchronous Operation Select */

#define R_ADC_B_ADSYCR_ADSYDIS1                   (1 << 17)  /* ADC1 Synchronous Operation Select */

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
#  define R_ADC_B_ADMDR_ADMD0_0X0                         (0 << R_ADC_B_ADMDR_ADMD0_SHIFT)  /* (SAR mode) Single scan mode */
#  define R_ADC_B_ADMDR_ADMD0_0X1                         (1 << R_ADC_B_ADMDR_ADMD0_SHIFT)  /* (SAR mode) Continuous scan mode */
#  define R_ADC_B_ADMDR_ADMD0_0X4                         (4 << R_ADC_B_ADMDR_ADMD0_SHIFT)  /* (Oversampling mode) Single scan mode */
#  define R_ADC_B_ADMDR_ADMD0_0X5                         (5 << R_ADC_B_ADMDR_ADMD0_SHIFT)  /* (Oversampling mode) Continuous scan mode */
#  define R_ADC_B_ADMDR_ADMD0_0X8                         (8 << R_ADC_B_ADMDR_ADMD0_SHIFT)  /* (Hybrid mode) Single scan mode */
#  define R_ADC_B_ADMDR_ADMD0_0X9                         (9 << R_ADC_B_ADMDR_ADMD0_SHIFT)  /* (Hybrid mode) Continuous scan mode */
#  define R_ADC_B_ADMDR_ADMD0_0XA                         (10 << R_ADC_B_ADMDR_ADMD0_SHIFT)  /* (Hybrid mode) Background continuous scan mode */

#define R_ADC_B_ADMDR_ADMD1_SHIFT                 (8)  /* ADC1 Mode Selection */
#define R_ADC_B_ADMDR_ADMD1_MASK                  0xf00
#  define R_ADC_B_ADMDR_ADMD1_0X0                         (0 << R_ADC_B_ADMDR_ADMD1_SHIFT)  /* Single scan mode */
#  define R_ADC_B_ADMDR_ADMD1_0X1                         (1 << R_ADC_B_ADMDR_ADMD1_SHIFT)  /* Continuous scan mode */
#  define R_ADC_B_ADMDR_ADMD1_0X4                         (4 << R_ADC_B_ADMDR_ADMD1_SHIFT)  /* (Oversampling mode) Single scan mode */
#  define R_ADC_B_ADMDR_ADMD1_0X5                         (5 << R_ADC_B_ADMDR_ADMD1_SHIFT)  /* (Oversampling mode) Continuous scan mode */
#  define R_ADC_B_ADMDR_ADMD1_0X8                         (8 << R_ADC_B_ADMDR_ADMD1_SHIFT)  /* (Hybrid mode) Single scan mode */
#  define R_ADC_B_ADMDR_ADMD1_0X9                         (9 << R_ADC_B_ADMDR_ADMD1_SHIFT)  /* (Hybrid mode) Continuous scan mode */
#  define R_ADC_B_ADMDR_ADMD1_0XA                         (10 << R_ADC_B_ADMDR_ADMD1_SHIFT)  /* (Hybrid mode) Background continuous scan mode */

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
#define R_ADC_B_ADSGER_SGREN_SHIFT                (0)  /* Scan Group n Enable */
#define R_ADC_B_ADSGER_SGREN_MASK                 0x1ff
#  define R_ADC_B_ADSGER_SGREN_0                          (0 << R_ADC_B_ADSGER_SGREN_SHIFT)  /* Disable the scan group n */
#  define R_ADC_B_ADSGER_SGREN_1                          (1 << R_ADC_B_ADSGER_SGREN_SHIFT)  /* Enable the scan group n */

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
#define R_ADC_B_ADINTCR_ADIEN_SHIFT               (0)  /* Scan Group n Scan End Interrupt Enable */
#define R_ADC_B_ADINTCR_ADIEN_MASK                0x1ff
#  define R_ADC_B_ADINTCR_ADIEN_0                         (0 << R_ADC_B_ADINTCR_ADIEN_SHIFT)  /* Disable Scan End interrupt */
#  define R_ADC_B_ADINTCR_ADIEN_1                         (1 << R_ADC_B_ADINTCR_ADIEN_SHIFT)  /* Enable Scan End interrupt */

#define R_ADC_B_ADINTCR_ADIEN_SHIFT               (0)  /* Scan Group n Scan End Interrupt Enable */
#define R_ADC_B_ADINTCR_ADIEN_MASK                0x1ff

/* ADTRGEXT Register bit definitions */
#define R_ADC_B_ADTRGEXT_TRGEXT0                  (1 << 0)  /* External Trigger Input 0 (ADTRG0) Enable */

#define R_ADC_B_ADTRGEXT_TRGEXT1                  (1 << 1)  /* External Trigger Input 1 (ADTRG1) Enable */

/* ADTRGELC Register bit definitions */
#define R_ADC_B_ADTRGELC_TRGELCM_SHIFT            (0)  /* ELC Trigger m Enable */
#define R_ADC_B_ADTRGELC_TRGELCM_MASK             0x3f
#  define R_ADC_B_ADTRGELC_TRGELCM_0                      (0 << R_ADC_B_ADTRGELC_TRGELCM_SHIFT)  /* Disable ELC Trigger m */
#  define R_ADC_B_ADTRGELC_TRGELCM_1                      (1 << R_ADC_B_ADTRGELC_TRGELCM_SHIFT)  /* Enable ELC Trigger m */

/* ADTRGGPT Register bit definitions */
#define R_ADC_B_ADTRGGPT_TRGGPTAM_SHIFT           (0)  /* GPT channel m A/D Conversion Starting Request A Enable */
#define R_ADC_B_ADTRGGPT_TRGGPTAM_MASK            0x3fff
#  define R_ADC_B_ADTRGGPT_TRGGPTAM_0                     (0 << R_ADC_B_ADTRGGPT_TRGGPTAM_SHIFT)  /* Disable the A/D conversion stating request A from GPT channel m */
#  define R_ADC_B_ADTRGGPT_TRGGPTAM_1                     (1 << R_ADC_B_ADTRGGPT_TRGGPTAM_SHIFT)  /* Enable the A/D conversion stating request A from GPT channel m */

#define R_ADC_B_ADTRGGPT_TRGGPTBM_SHIFT           (16)  /* GPT channel m A/D Conversion Starting Request B Enable */
#define R_ADC_B_ADTRGGPT_TRGGPTBM_MASK            0x3fff0000
#  define R_ADC_B_ADTRGGPT_TRGGPTBM_0                     (0 << R_ADC_B_ADTRGGPT_TRGGPTBM_SHIFT)  /* Disable the A/D conversion stating request B from GPT channel m */
#  define R_ADC_B_ADTRGGPT_TRGGPTBM_1                     (1 << R_ADC_B_ADTRGGPT_TRGGPTBM_SHIFT)  /* Enable the A/D conversion stating request B from GPT channel m */

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
#define R_ADC_B_ADSGDCR_DIAGVAL_SHIFT             (0)  /* Self-diagnosis Voltage Selection */
#define R_ADC_B_ADSGDCR_DIAGVAL_MASK              0x7
#  define R_ADC_B_ADSGDCR_DIAGVAL_0X0                     (0 << R_ADC_B_ADSGDCR_DIAGVAL_SHIFT)  /* Set when any self-diagnosis channel are not included.
 Setting prohibited when any self-diagnosis channels are included. */
#  define R_ADC_B_ADSGDCR_DIAGVAL_0X4                     (4 << R_ADC_B_ADSGDCR_DIAGVAL_SHIFT)  /* Self-diagnosis mode 1 */
#  define R_ADC_B_ADSGDCR_DIAGVAL_0X5                     (5 << R_ADC_B_ADSGDCR_DIAGVAL_SHIFT)  /* Self-diagnosis mode 2 */
#  define R_ADC_B_ADSGDCR_DIAGVAL_0X6                     (6 << R_ADC_B_ADSGDCR_DIAGVAL_SHIFT)  /* Self-diagnosis mode 3 */

#define R_ADC_B_ADSGDCR_ADDISEN                   (1 << 16)  /* Disconnection Detection Assist Enable */

#define R_ADC_B_ADSGDCR_ADDISP                    (1 << 20)  /* Disconnection Detection Assist Mode Selection */

#define R_ADC_B_ADSGDCR_ADDISN                    (1 << 21)  /* Disconnection Detection Assist Mode Selection */

#define R_ADC_B_ADSGDCR_ADNDIS_SHIFT              (24)  /* Disconnection Detection Assist Period */
#define R_ADC_B_ADSGDCR_ADNDIS_MASK               0xff000000
#  define R_ADC_B_ADSGDCR_ADNDIS_0X0                      (0 << R_ADC_B_ADSGDCR_ADNDIS_SHIFT)  /* Setting prohibited when the Disconnection Detection Assist function is enabled */
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
#define R_ADC_B_ADCALSTCR_CALADSST_SHIFT          (0)  /* A/D Converter Calibration Sampling Time Configuration */
#define R_ADC_B_ADCALSTCR_CALADSST_MASK           0x3ff

#define R_ADC_B_ADCALSTCR_CALADCST_SHIFT          (16)  /* A/D Converter Calibration Conversion Time Configuration. */
#define R_ADC_B_ADCALSTCR_CALADCST_MASK           0x3f0000

/* ADSHCR0 Register bit definitions */
#define R_ADC_B_ADSHCR0_SHEN_S                    (1 << 0)  /* Channel-Dedicated Sample-and-Hold Circuit Unit %s Select */

#define R_ADC_B_ADSHCR0_SHMD_S                    (1 << 16)  /* Channel-dedicated Sample-and-hold Circuit Unit %s Input Mode Select */

#define R_ADC_B_ADSHCR0_SHEN0                     (1 << 0)  /* Channel-Dedicated Sample-and-Hold Circuit Unit 0 Select */

#define R_ADC_B_ADSHCR0_SHEN1                     (1 << 1)  /* Channel-Dedicated Sample-and-Hold Circuit Unit 1 Select */

#define R_ADC_B_ADSHCR0_SHEN2                     (1 << 2)  /* Channel-Dedicated Sample-and-Hold Circuit Unit 2 Select */

#define R_ADC_B_ADSHCR0_SHMD0                     (1 << 16)  /* Channel-dedicated Sample-and-hold Circuit Unit 0 Input Mode Select */

#define R_ADC_B_ADSHCR0_SHMD1                     (1 << 17)  /* Channel-dedicated Sample-and-hold Circuit Unit 1 Input Mode Select */

#define R_ADC_B_ADSHCR0_SHMD2                     (1 << 18)  /* Channel-dedicated Sample-and-hold Circuit Unit 2 Input Mode Select */

/* ADSHSTR0 Register bit definitions */
#define R_ADC_B_ADSHSTR0_SHSST_SHIFT              (0)  /* Channel-Dedicated Sample-and-Hold Circuit Unit 0 to 2 */
#define R_ADC_B_ADSHSTR0_SHSST_MASK               0xff

#define R_ADC_B_ADSHSTR0_SHHST_SHIFT              (16)  /* Channel-Dedicated Sample-and-Hold Circuit Unit 0 to 2 */
#define R_ADC_B_ADSHSTR0_SHHST_MASK               0x70000

/* ADSHCR1 Register bit definitions */
#define R_ADC_B_ADSHCR1_SHEN_S                    (1 << 0)  /* Channel-Dedicated Sample-and-Hold Circuit Unit %s Select */

#define R_ADC_B_ADSHCR1_SHMD_S                    (1 << 16)  /* Channel-dedicated Sample-and-hold Circuit Unit %s Input Mode Select */

#define R_ADC_B_ADSHCR1_SHEN4                     (1 << 0)  /* Channel-Dedicated Sample-and-Hold Circuit Unit 4 Select */

#define R_ADC_B_ADSHCR1_SHEN5                     (1 << 1)  /* Channel-Dedicated Sample-and-Hold Circuit Unit 5 Select */

#define R_ADC_B_ADSHCR1_SHEN6                     (1 << 2)  /* Channel-Dedicated Sample-and-Hold Circuit Unit 6 Select */

#define R_ADC_B_ADSHCR1_SHMD4                     (1 << 16)  /* Channel-dedicated Sample-and-hold Circuit Unit 4 Input Mode Select */

#define R_ADC_B_ADSHCR1_SHMD5                     (1 << 17)  /* Channel-dedicated Sample-and-hold Circuit Unit 5 Input Mode Select */

#define R_ADC_B_ADSHCR1_SHMD6                     (1 << 18)  /* Channel-dedicated Sample-and-hold Circuit Unit 6 Input Mode Select */

/* ADSHSTR1 Register bit definitions */
#define R_ADC_B_ADSHSTR1_SHSST_SHIFT              (0)  /* Channel-Dedicated Sample-and-Hold Circuit Unit 4 to 6 */
#define R_ADC_B_ADSHSTR1_SHSST_MASK               0xff

#define R_ADC_B_ADSHSTR1_SHHST_SHIFT              (16)  /* Channel-Dedicated Sample-and-Hold Circuit Unit 4 to 6 */
#define R_ADC_B_ADSHSTR1_SHHST_MASK               0x70000

/* ADCALSHCR Register bit definitions */
#define R_ADC_B_ADCALSHCR_CALSHSST_SHIFT          (0)  /* Channel-Dedicated Sample & Hold Circuit Calibration Sampling Time Configuration */
#define R_ADC_B_ADCALSHCR_CALSHSST_MASK           0xff

#define R_ADC_B_ADCALSHCR_CALSHHST_SHIFT          (16)  /* Channel-Dedicated Sample & Hold Circuit Calibration Holding Time Configuration */
#define R_ADC_B_ADCALSHCR_CALSHHST_MASK           0x70000

/* ADREFCR Register bit definitions */
#define R_ADC_B_ADREFCR_VDE                       (1 << 0)  /* Internal Reference Voltage A/D Conversion Select */

/* ADDFSR Register bit definitions */
#define R_ADC_B_ADDFSR_DFSEL0_SHIFT               (0)  /* A/D Converter unit the 1st digital filter characteristic selection. */
#define R_ADC_B_ADDFSR_DFSEL0_MASK                0x3
#  define R_ADC_B_ADDFSR_DFSEL0_01                        (1 << R_ADC_B_ADDFSR_DFSEL0_SHIFT)  /* Sinc3 Filter (Over Sampling Rate equal to 8) */
#  define R_ADC_B_ADDFSR_DFSEL0_10                        (2 << R_ADC_B_ADDFSR_DFSEL0_SHIFT)  /* Minimum Phase Filter (Group Delay less than 2) */

#define R_ADC_B_ADDFSR_DFSEL1_SHIFT               (8)  /* A/D Converter unit the 2nd digital filter characteristic selection. */
#define R_ADC_B_ADDFSR_DFSEL1_MASK                0x300
#  define R_ADC_B_ADDFSR_DFSEL1_01                        (1 << R_ADC_B_ADDFSR_DFSEL1_SHIFT)  /* Sinc3 Filter (Over Sampling Rate equal to 8) */
#  define R_ADC_B_ADDFSR_DFSEL1_10                        (2 << R_ADC_B_ADDFSR_DFSEL1_SHIFT)  /* Minimum Phase Filter (Group Delay less than 2) */

#define R_ADC_B_ADDFSR_DFSEL2_SHIFT               (16)  /* A/D Converter unit the 2nd digital filter characteristic selection. */
#define R_ADC_B_ADDFSR_DFSEL2_MASK                0x30000
#  define R_ADC_B_ADDFSR_DFSEL2_01                        (1 << R_ADC_B_ADDFSR_DFSEL2_SHIFT)  /* Sinc3 Filter (Over Sampling Rate equal to 8) */
#  define R_ADC_B_ADDFSR_DFSEL2_10                        (2 << R_ADC_B_ADDFSR_DFSEL2_SHIFT)  /* Minimum Phase Filter (Group Delay less than 2) */

#define R_ADC_B_ADDFSR_DFSEL3_SHIFT               (24)  /* A/D Converter unit the 4th digital filter characteristic selection. */
#define R_ADC_B_ADDFSR_DFSEL3_MASK                0x3000000
#  define R_ADC_B_ADDFSR_DFSEL3_01                        (1 << R_ADC_B_ADDFSR_DFSEL3_SHIFT)  /* Sinc3 Filter (Over Sampling Rate equal to 8) */
#  define R_ADC_B_ADDFSR_DFSEL3_10                        (2 << R_ADC_B_ADDFSR_DFSEL3_SHIFT)  /* Minimum Phase Filter (Group Delay less than 2) */

/* ADUOFTR Register bit definitions */
#define R_ADC_B_ADUOFTR_UOFSET_SHIFT              (0)  /* User Offset Table n */
#define R_ADC_B_ADUOFTR_UOFSET_MASK               0xffff

/* ADUGTR Register bit definitions */
#define R_ADC_B_ADUGTR_UGAINF_SHIFT               (0)  /* User Gain Table n - Fractional Gain */
#define R_ADC_B_ADUGTR_UGAINF_MASK                0x3fff

#define R_ADC_B_ADUGTR_UGAINI_SHIFT               (14)  /* User Gain Table n - Integer Gain */
#define R_ADC_B_ADUGTR_UGAINI_MASK                0xc000

/* ADLIMINTCR Register bit definitions */
#define R_ADC_B_ADLIMINTCR_LIMIEN_SHIFT           (0)  /* Limiter Clip Interrupt n Enable bit */
#define R_ADC_B_ADLIMINTCR_LIMIEN_MASK            0x1ff
#  define R_ADC_B_ADLIMINTCR_LIMIEN_0                     (0 << R_ADC_B_ADLIMINTCR_LIMIEN_SHIFT)  /* Disable the Limiter clip interrupt n */
#  define R_ADC_B_ADLIMINTCR_LIMIEN_1                     (1 << R_ADC_B_ADLIMINTCR_LIMIEN_SHIFT)  /* Enable the Limiter clip interrupt n */

#define R_ADC_B_ADLIMINTCR_LIMIEN_SHIFT           (0)  /* Limiter Clip Interrupt n Enable bit */
#define R_ADC_B_ADLIMINTCR_LIMIEN_MASK            0x1ff

/* ADLIMTR Register bit definitions */
#define R_ADC_B_ADLIMTR_LIML_SHIFT                (0)  /* Limiter clip table n : Lower-side limit value */
#define R_ADC_B_ADLIMTR_LIML_MASK                 0xffff

#define R_ADC_B_ADLIMTR_LIMU_SHIFT                (16)  /* Limiter clip table n : Upper-side limit value */
#define R_ADC_B_ADLIMTR_LIMU_MASK                 0xffff0000

/* ADCMPENR Register bit definitions */
#define R_ADC_B_ADCMPENR_CMPENN_SHIFT             (0)  /* Compare Match n Enable */
#define R_ADC_B_ADCMPENR_CMPENN_MASK              0xff
#  define R_ADC_B_ADCMPENR_CMPENN_0                       (0 << R_ADC_B_ADCMPENR_CMPENN_SHIFT)  /* Disable the compare match n */
#  define R_ADC_B_ADCMPENR_CMPENN_1                       (1 << R_ADC_B_ADCMPENR_CMPENN_SHIFT)  /* Enable the compare match n */

#define R_ADC_B_ADCMPENR_CMPENN_SHIFT             (0)  /* Compare Match n Enable */
#define R_ADC_B_ADCMPENR_CMPENN_MASK              0xff

/* ADCMPINTCR Register bit definitions */
#define R_ADC_B_ADCMPINTCR_CMPIEN_SHIFT           (0)  /* Compare Match Interrupt n Enable */
#define R_ADC_B_ADCMPINTCR_CMPIEN_MASK            0xf
#  define R_ADC_B_ADCMPINTCR_CMPIEN_0                     (0 << R_ADC_B_ADCMPINTCR_CMPIEN_SHIFT)  /* Disable the Compare Match interrupt n */
#  define R_ADC_B_ADCMPINTCR_CMPIEN_1                     (1 << R_ADC_B_ADCMPINTCR_CMPIEN_SHIFT)  /* Enable the Compare Match interrupt n */

#define R_ADC_B_ADCMPINTCR_CMPIEN_SHIFT           (0)  /* Compare Match Interrupt n Enable */
#define R_ADC_B_ADCMPINTCR_CMPIEN_MASK            0xf

/* ADCCMPCR Register bit definitions */
#define R_ADC_B_ADCCMPCR_CCMPCND_SHIFT            (0)  /* Composite Compare Match Condition Selection */
#define R_ADC_B_ADCCMPCR_CCMPCND_MASK             0x3
#  define R_ADC_B_ADCCMPCR_CCMPCND_00                     (0 << R_ADC_B_ADCCMPCR_CCMPCND_SHIFT)  /* Logical disjunction (OR) conditions */
#  define R_ADC_B_ADCCMPCR_CCMPCND_01                     (1 << R_ADC_B_ADCCMPCR_CCMPCND_SHIFT)  /* Logical conjunction (AND) conditions */
#  define R_ADC_B_ADCCMPCR_CCMPCND_10                     (2 << R_ADC_B_ADCCMPCR_CCMPCND_SHIFT)  /* Logical exclusive disjunction (EXOR) conditions */
#  define R_ADC_B_ADCCMPCR_CCMPCND_11                     (3 << R_ADC_B_ADCCMPCR_CCMPCND_SHIFT)  /* Setting prohibited */

#define R_ADC_B_ADCCMPCR_CCMPTBLM_SHIFT           (16)  /* Composite Compare Match Condition Table Selection */
#define R_ADC_B_ADCCMPCR_CCMPTBLM_MASK            0xff0000
#  define R_ADC_B_ADCCMPCR_CCMPTBLM_0                     (0 << R_ADC_B_ADCCMPCR_CCMPTBLM_SHIFT)  /* Not use the Compare Match Table m */
#  define R_ADC_B_ADCCMPCR_CCMPTBLM_1                     (1 << R_ADC_B_ADCCMPCR_CCMPTBLM_SHIFT)  /* Use the Compare Match table m */

/* ADCMPMDR0 Register bit definitions */
#define R_ADC_B_ADCMPMDR0_CMPMD0_SHIFT            (0)  /* Compare Match 0 : Match Mode Selection */
#define R_ADC_B_ADCMPMDR0_CMPMD0_MASK             0x3
#  define R_ADC_B_ADCMPMDR0_CMPMD0_00                     (0 << R_ADC_B_ADCMPMDR0_CMPMD0_SHIFT)  /* Generate the match when more than high-side level */
#  define R_ADC_B_ADCMPMDR0_CMPMD0_01                     (1 << R_ADC_B_ADCMPMDR0_CMPMD0_SHIFT)  /* Generate the match when less than low-side level */
#  define R_ADC_B_ADCMPMDR0_CMPMD0_10                     (2 << R_ADC_B_ADCMPMDR0_CMPMD0_SHIFT)  /* Generate the match when more than high-side level or less than low-side level */
#  define R_ADC_B_ADCMPMDR0_CMPMD0_11                     (3 << R_ADC_B_ADCMPMDR0_CMPMD0_SHIFT)  /* Generate the match when it is in the range from low-side level to high-side level */

#define R_ADC_B_ADCMPMDR0_CMPMD1_SHIFT            (8)  /* Compare Match 1 : Match Mode Selection */
#define R_ADC_B_ADCMPMDR0_CMPMD1_MASK             0x300
#  define R_ADC_B_ADCMPMDR0_CMPMD1_00                     (0 << R_ADC_B_ADCMPMDR0_CMPMD1_SHIFT)  /* Generate the match when more than high-side level */
#  define R_ADC_B_ADCMPMDR0_CMPMD1_01                     (1 << R_ADC_B_ADCMPMDR0_CMPMD1_SHIFT)  /* Generate the match when less than low-side level */
#  define R_ADC_B_ADCMPMDR0_CMPMD1_10                     (2 << R_ADC_B_ADCMPMDR0_CMPMD1_SHIFT)  /* Generate the match when more than high-side level or less than low-side level */
#  define R_ADC_B_ADCMPMDR0_CMPMD1_11                     (3 << R_ADC_B_ADCMPMDR0_CMPMD1_SHIFT)  /* Generate the match when it is in the range from low-side level to high-side level */

#define R_ADC_B_ADCMPMDR0_CMPMD2_SHIFT            (16)  /* Compare Match 2 : Match Mode Selection */
#define R_ADC_B_ADCMPMDR0_CMPMD2_MASK             0x30000
#  define R_ADC_B_ADCMPMDR0_CMPMD2_00                     (0 << R_ADC_B_ADCMPMDR0_CMPMD2_SHIFT)  /* Generate the match when more than high-side level */
#  define R_ADC_B_ADCMPMDR0_CMPMD2_01                     (1 << R_ADC_B_ADCMPMDR0_CMPMD2_SHIFT)  /* Generate the match when less than low-side level */
#  define R_ADC_B_ADCMPMDR0_CMPMD2_10                     (2 << R_ADC_B_ADCMPMDR0_CMPMD2_SHIFT)  /* Generate the match when more than high-side level or less than low-side level */
#  define R_ADC_B_ADCMPMDR0_CMPMD2_11                     (3 << R_ADC_B_ADCMPMDR0_CMPMD2_SHIFT)  /* Generate the match when it is in the range from low-side level to high-side level */

#define R_ADC_B_ADCMPMDR0_CMPMD3_SHIFT            (24)  /* Compare Match 3 : Match Mode Selection */
#define R_ADC_B_ADCMPMDR0_CMPMD3_MASK             0x3000000
#  define R_ADC_B_ADCMPMDR0_CMPMD3_00                     (0 << R_ADC_B_ADCMPMDR0_CMPMD3_SHIFT)  /* Generate the match when more than high-side level */
#  define R_ADC_B_ADCMPMDR0_CMPMD3_01                     (1 << R_ADC_B_ADCMPMDR0_CMPMD3_SHIFT)  /* Generate the match when less than low-side level */
#  define R_ADC_B_ADCMPMDR0_CMPMD3_10                     (2 << R_ADC_B_ADCMPMDR0_CMPMD3_SHIFT)  /* Generate the match when more than high-side level or less than low-side level */
#  define R_ADC_B_ADCMPMDR0_CMPMD3_11                     (3 << R_ADC_B_ADCMPMDR0_CMPMD3_SHIFT)  /* Generate the match when it is in the range from low-side level to high-side level */

/* ADCMPMDR1 Register bit definitions */
#define R_ADC_B_ADCMPMDR1_CMPMD4_SHIFT            (0)  /* Compare Match 4 : Match Mode Selection */
#define R_ADC_B_ADCMPMDR1_CMPMD4_MASK             0x3
#  define R_ADC_B_ADCMPMDR1_CMPMD4_00                     (0 << R_ADC_B_ADCMPMDR1_CMPMD4_SHIFT)  /* Generate the match when more than high-side level */
#  define R_ADC_B_ADCMPMDR1_CMPMD4_01                     (1 << R_ADC_B_ADCMPMDR1_CMPMD4_SHIFT)  /* Generate the match when less than low-side level */
#  define R_ADC_B_ADCMPMDR1_CMPMD4_10                     (2 << R_ADC_B_ADCMPMDR1_CMPMD4_SHIFT)  /* Generate the match when more than high-side level or less than low-side level */
#  define R_ADC_B_ADCMPMDR1_CMPMD4_11                     (3 << R_ADC_B_ADCMPMDR1_CMPMD4_SHIFT)  /* Generate the match when it is in the range from low-side level to high-side level */

#define R_ADC_B_ADCMPMDR1_CMPMD5_SHIFT            (8)  /* Compare Match 5 : Match Mode Selection */
#define R_ADC_B_ADCMPMDR1_CMPMD5_MASK             0x300
#  define R_ADC_B_ADCMPMDR1_CMPMD5_00                     (0 << R_ADC_B_ADCMPMDR1_CMPMD5_SHIFT)  /* Generate the match when more than high-side level */
#  define R_ADC_B_ADCMPMDR1_CMPMD5_01                     (1 << R_ADC_B_ADCMPMDR1_CMPMD5_SHIFT)  /* Generate the match when less than low-side level */
#  define R_ADC_B_ADCMPMDR1_CMPMD5_10                     (2 << R_ADC_B_ADCMPMDR1_CMPMD5_SHIFT)  /* Generate the match when more than high-side level or less than low-side level */
#  define R_ADC_B_ADCMPMDR1_CMPMD5_11                     (3 << R_ADC_B_ADCMPMDR1_CMPMD5_SHIFT)  /* Generate the match when it is in the range from low-side level to high-side level */

#define R_ADC_B_ADCMPMDR1_CMPMD6_SHIFT            (16)  /* Compare Match 6 : Match Mode Selection */
#define R_ADC_B_ADCMPMDR1_CMPMD6_MASK             0x30000
#  define R_ADC_B_ADCMPMDR1_CMPMD6_00                     (0 << R_ADC_B_ADCMPMDR1_CMPMD6_SHIFT)  /* Generate the match when more than high-side level */
#  define R_ADC_B_ADCMPMDR1_CMPMD6_01                     (1 << R_ADC_B_ADCMPMDR1_CMPMD6_SHIFT)  /* Generate the match when less than low-side level */
#  define R_ADC_B_ADCMPMDR1_CMPMD6_10                     (2 << R_ADC_B_ADCMPMDR1_CMPMD6_SHIFT)  /* Generate the match when more than high-side level or less than low-side level */
#  define R_ADC_B_ADCMPMDR1_CMPMD6_11                     (3 << R_ADC_B_ADCMPMDR1_CMPMD6_SHIFT)  /* Generate the match when it is in the range from low-side level to high-side level */

#define R_ADC_B_ADCMPMDR1_CMPMD7_SHIFT            (24)  /* Compare Match 7 : Match Mode Selection */
#define R_ADC_B_ADCMPMDR1_CMPMD7_MASK             0x3000000
#  define R_ADC_B_ADCMPMDR1_CMPMD7_00                     (0 << R_ADC_B_ADCMPMDR1_CMPMD7_SHIFT)  /* Generate the match when more than high-side level */
#  define R_ADC_B_ADCMPMDR1_CMPMD7_01                     (1 << R_ADC_B_ADCMPMDR1_CMPMD7_SHIFT)  /* Generate the match when less than low-side level */
#  define R_ADC_B_ADCMPMDR1_CMPMD7_10                     (2 << R_ADC_B_ADCMPMDR1_CMPMD7_SHIFT)  /* Generate the match when more than high-side level or less than low-side level */
#  define R_ADC_B_ADCMPMDR1_CMPMD7_11                     (3 << R_ADC_B_ADCMPMDR1_CMPMD7_SHIFT)  /* Generate the match when it is in the range from low-side level to high-side level */

/* ADCMPTBR Register bit definitions */
#define R_ADC_B_ADCMPTBR_CMPTBL_SHIFT             (0)  /* Compare Match Table n : Low-side level */
#define R_ADC_B_ADCMPTBR_CMPTBL_MASK              0xffff

#define R_ADC_B_ADCMPTBR_CMPTBH_SHIFT             (16)  /* Compare Match Table n : High-side level */
#define R_ADC_B_ADCMPTBR_CMPTBH_MASK              0xffff0000

/* ADFIFOCR Register bit definitions */
#define R_ADC_B_ADFIFOCR_FIFOEN0                  (1 << 0)  /* Scan Group 0 FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOEN1                  (1 << 1)  /* Scan Group 1 FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOEN2                  (1 << 2)  /* Scan Group 2 FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOEN3                  (1 << 3)  /* Scan Group 3 FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOEN4                  (1 << 4)  /* Scan Group 4 FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOEN5                  (1 << 5)  /* Scan Group 5 FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOEN6                  (1 << 6)  /* Scan Group 6 FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOEN7                  (1 << 7)  /* Scan Group 7 FIFO Enable */

#define R_ADC_B_ADFIFOCR_FIFOEN8                  (1 << 8)  /* Scan Group 8 FIFO Enable */

/* ADFIFOINTCR Register bit definitions */
#define R_ADC_B_ADFIFOINTCR_FIFOIE0               (1 << 0)  /* Scan Group 0 FIFO Interrupt Enable */

#define R_ADC_B_ADFIFOINTCR_FIFOIE1               (1 << 1)  /* Scan Group 1 FIFO Interrupt Enable */

#define R_ADC_B_ADFIFOINTCR_FIFOIE2               (1 << 2)  /* Scan Group 2 FIFO Interrupt Enable */

#define R_ADC_B_ADFIFOINTCR_FIFOIE3               (1 << 3)  /* Scan Group 3 FIFO Interrupt Enable */

#define R_ADC_B_ADFIFOINTCR_FIFOIE4               (1 << 4)  /* Scan Group 4 FIFO Interrupt Enable */

#define R_ADC_B_ADFIFOINTCR_FIFOIE5               (1 << 5)  /* Scan Group 5 FIFO Interrupt Enable */

#define R_ADC_B_ADFIFOINTCR_FIFOIE6               (1 << 6)  /* Scan Group 6 FIFO Interrupt Enable */

#define R_ADC_B_ADFIFOINTCR_FIFOIE7               (1 << 7)  /* Scan Group 7 FIFO Interrupt Enable */

#define R_ADC_B_ADFIFOINTCR_FIFOIE8               (1 << 8)  /* Scan Group 8 FIFO Interrupt Enable */

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

#define R_ADC_B_ADCHCR_AINMD                      (1 << 15)  /* Analog Input mode selection */

#define R_ADC_B_ADCHCR_SSTSEL_SHIFT               (16)  /* Sampling State Table Selection */
#define R_ADC_B_ADCHCR_SSTSEL_MASK                0xf0000

/* ADDOPCRA Register bit definitions */
#define R_ADC_B_ADDOPCRA_DFSEL_SHIFT              (0)  /* Digital Filter Table Selection */
#define R_ADC_B_ADDOPCRA_DFSEL_MASK               0x7

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

#define R_ADC_B_ADDOPCRB_CMPTBLEM_SHIFT           (16)  /* Compare Match Enable */
#define R_ADC_B_ADDOPCRB_CMPTBLEM_MASK            0xff0000
#  define R_ADC_B_ADDOPCRB_CMPTBLEM_0                     (0 << R_ADC_B_ADDOPCRB_CMPTBLEM_SHIFT)  /* Disable the compare match with the Compare Match Table m */
#  define R_ADC_B_ADDOPCRB_CMPTBLEM_1                     (1 << R_ADC_B_ADDOPCRB_CMPTBLEM_SHIFT)  /* Enable the compare match with the Compare Match Table m */

/* ADDOPCRC Register bit definitions */
#define R_ADC_B_ADDOPCRC_LIMTBLS_SHIFT            (0)  /* Limiter Clip Table Selection */
#define R_ADC_B_ADDOPCRC_LIMTBLS_MASK             0xf

#define R_ADC_B_ADDOPCRC_ADPRC_SHIFT              (16)  /* A/D Conversion Data Format Selection */
#define R_ADC_B_ADDOPCRC_ADPRC_MASK               0x30000
#  define R_ADC_B_ADDOPCRC_ADPRC_00                       (0 << R_ADC_B_ADDOPCRC_ADPRC_SHIFT)  /* Store the A/D conversion result as 16-bit data format */
#  define R_ADC_B_ADDOPCRC_ADPRC_01                       (1 << R_ADC_B_ADDOPCRC_ADPRC_SHIFT)  /* Store the A/D conversion result as 14-bit data format */
#  define R_ADC_B_ADDOPCRC_ADPRC_10                       (2 << R_ADC_B_ADDOPCRC_ADPRC_SHIFT)  /* Store the A/D conversion result as 12-bit data format */
#  define R_ADC_B_ADDOPCRC_ADPRC_11                       (3 << R_ADC_B_ADDOPCRC_ADPRC_SHIFT)  /* Store the A/D conversion result as 10-bit data format */

#define R_ADC_B_ADDOPCRC_SIGNSEL                  (1 << 20)  /* A/D Conversion Data Sign Selection */

/* ADCALSTR Register bit definitions */
#define R_ADC_B_ADCALSTR_ADCALST0_SHIFT           (0)  /* A/D Converter Unit 0 (ADC0) Calibration Start Control bits */
#define R_ADC_B_ADCALSTR_ADCALST0_MASK            0x7
#  define R_ADC_B_ADCALSTR_ADCALST0_0                     (0 << R_ADC_B_ADCALSTR_ADCALST0_SHIFT)  /* No effect (not start the calibration) */
#  define R_ADC_B_ADCALSTR_ADCALST0_1                     (1 << R_ADC_B_ADCALSTR_ADCALST0_SHIFT)  /* Start the calibration */

#define R_ADC_B_ADCALSTR_ADCALST1_SHIFT           (8)  /* A/D Converter Unit 1 (ADC1) Calibration Start Control bits */
#define R_ADC_B_ADCALSTR_ADCALST1_MASK            0x700
#  define R_ADC_B_ADCALSTR_ADCALST1_0                     (0 << R_ADC_B_ADCALSTR_ADCALST1_SHIFT)  /* No effect (not start the calibration) */
#  define R_ADC_B_ADCALSTR_ADCALST1_1                     (1 << R_ADC_B_ADCALSTR_ADCALST1_SHIFT)  /* Start the calibration */

/* ADTRGENR Register bit definitions */
#define R_ADC_B_ADTRGENR_STTRGENN_SHIFT           (0)  /* Scan Group n A/D Conversion Start Trigger Enable */
#define R_ADC_B_ADTRGENR_STTRGENN_MASK            0x1ff
#  define R_ADC_B_ADTRGENR_STTRGENN_0                     (0 << R_ADC_B_ADTRGENR_STTRGENN_SHIFT)  /* Disable the A/D conversion start trigger */
#  define R_ADC_B_ADTRGENR_STTRGENN_1                     (1 << R_ADC_B_ADTRGENR_STTRGENN_SHIFT)  /* Enable the A/D conversion start trigger */

#define R_ADC_B_ADTRGENR_STTRGENN_SHIFT           (0)  /* Scan Group n A/D Conversion Start Trigger Enable */
#define R_ADC_B_ADTRGENR_STTRGENN_MASK            0x1ff

/* ADSYSTR Register bit definitions */
#define R_ADC_B_ADSYSTR_ADSYSTN_SHIFT             (0)  /* Scan Group n : A/D Conversion start */
#define R_ADC_B_ADSYSTR_ADSYSTN_MASK              0x1ff
#  define R_ADC_B_ADSYSTR_ADSYSTN_0                       (0 << R_ADC_B_ADSYSTR_ADSYSTN_SHIFT)  /* No effect */
#  define R_ADC_B_ADSYSTR_ADSYSTN_1                       (1 << R_ADC_B_ADSYSTR_ADSYSTN_SHIFT)  /* Start the A/D conversion of scan group n */

#define R_ADC_B_ADSYSTR_ADSYSTN_SHIFT             (0)  /* Scan Group n : A/D Conversion start */
#define R_ADC_B_ADSYSTR_ADSYSTN_MASK              0x1ff

/* ADSTR Register bit definitions */
#define R_ADC_B_ADSTR_ADST                        (1 << 0)  /* Scan Group n A/D Conversion Start */

/* ADSTOPR Register bit definitions */
#define R_ADC_B_ADSTOPR_ADSTOP0                   (1 << 0)  /* A/D Converter Unit 0 Force Stop bit */

#define R_ADC_B_ADSTOPR_ADSTOP1                   (1 << 8)  /* A/D Converter Unit 1 Force Stop bit */

/* ADSR Register bit definitions */
#define R_ADC_B_ADSR_ADACT0                       (1 << 0)  /* A/D Converter Unit 0 (ADC0) A/D Conversion Status */

#define R_ADC_B_ADSR_ADACT1                       (1 << 1)  /* A/D Converter Unit 1 (ADC1) A/D Conversion Status */

#define R_ADC_B_ADSR_CALACT0                      (1 << 16)  /* A/D Converter Unit 0 (ADC0) : Calibration Status */

#define R_ADC_B_ADSR_CALACT1                      (1 << 17)  /* A/D Converter Unit 1 (ADC1) : Calibration Status */

/* ADGRSR Register bit definitions */
#define R_ADC_B_ADGRSR_ACTGRN_SHIFT               (0)  /* Scan Group n Status */
#define R_ADC_B_ADGRSR_ACTGRN_MASK                0x1ff
#  define R_ADC_B_ADGRSR_ACTGRN_0                         (0 << R_ADC_B_ADGRSR_ACTGRN_SHIFT)  /* Scan group n is idle */
#  define R_ADC_B_ADGRSR_ACTGRN_1                         (1 << R_ADC_B_ADGRSR_ACTGRN_SHIFT)  /* Scan group n is in the scanning operation */

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
#define R_ADC_B_ADOVFCHSR0_OVFCHFN_SHIFT          (0)  /* Analog Input Channel No. n : Overflow Flag */
#define R_ADC_B_ADOVFCHSR0_OVFCHFN_MASK           0x7fffff
#  define R_ADC_B_ADOVFCHSR0_OVFCHFN_0                    (0 << R_ADC_B_ADOVFCHSR0_OVFCHFN_SHIFT)  /* Overflow is not detected */
#  define R_ADC_B_ADOVFCHSR0_OVFCHFN_1                    (1 << R_ADC_B_ADOVFCHSR0_OVFCHFN_SHIFT)  /* Overflow is detected */

#define R_ADC_B_ADOVFCHSR0_OVFCHFN_SHIFT          (0)  /* Analog Input Channel No. n : Overflow Flag */
#define R_ADC_B_ADOVFCHSR0_OVFCHFN_MASK           0x7fffff

/* ADOVFEXSR Register bit definitions */
#define R_ADC_B_ADOVFEXSR_OVFEXF0                 (1 << 0)  /* Self-diagnosis Channel for A/D unit 0: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF1                 (1 << 1)  /* Self-diagnosis Channel for A/D unit 1: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF4                 (1 << 4)  /* Temperature Sensor Channel: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF5                 (1 << 5)  /* Internal Reference Voltage Channel: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF6                 (1 << 6)  /* VBATT 1/3 voltage monitor output Channel: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF8                 (1 << 8)  /* D/A Converter 0 Channel: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF9                 (1 << 9)  /* D/A Converter 1 Channel: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF16                (1 << 16)  /* Self-diagnosis Channel for Sample-and-hold circuit unit0: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF17                (1 << 17)  /* Self-diagnosis Channel for Sample-and-hold circuit unit1: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF18                (1 << 18)  /* Self-diagnosis Channel for Sample-and-hold circuit unit2: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF20                (1 << 20)  /* Self-diagnosis Channel for Sample-and-hold circuit unit4: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF21                (1 << 21)  /* Self-diagnosis Channel for Sample-and-hold circuit unit5: Overflow Flag */

#define R_ADC_B_ADOVFEXSR_OVFEXF22                (1 << 22)  /* Self-diagnosis Channel for Sample-and-hold circuit unit6: Overflow Flag */

/* ADOVFERSCR Register bit definitions */
#define R_ADC_B_ADOVFERSCR_ADOVFEC0               (1 << 0)  /* A/D Converter Unit 0 (ADC0) Overflow Error Flag Clear */

#define R_ADC_B_ADOVFERSCR_ADOVFEC1               (1 << 1)  /* A/D Converter Unit 1 (ADC1) Overflow Error Flag Clear */

/* ADOVFCHSCR0 Register bit definitions */
#define R_ADC_B_ADOVFCHSCR0_OVFCHCN_SHIFT         (0)  /* Analog Input Channel No. n : Overflow Flag Clear */
#define R_ADC_B_ADOVFCHSCR0_OVFCHCN_MASK          0x7fffff
#  define R_ADC_B_ADOVFCHSCR0_OVFCHCN_0                   (0 << R_ADC_B_ADOVFCHSCR0_OVFCHCN_SHIFT)  /* No effect */
#  define R_ADC_B_ADOVFCHSCR0_OVFCHCN_1                   (1 << R_ADC_B_ADOVFCHSCR0_OVFCHCN_SHIFT)  /* ADOVFCHSR0.OVFCHFn is cleared */

#define R_ADC_B_ADOVFCHSCR0_OVFCHCN_SHIFT         (0)  /* Analog Input Channel No. n : Overflow Flag Clear */
#define R_ADC_B_ADOVFCHSCR0_OVFCHCN_MASK          0x7fffff

/* ADOVFEXSCR Register bit definitions */
#define R_ADC_B_ADOVFEXSCR_OVFEXC0                (1 << 0)  /* Self-diagnosis Channel for A/D unit 0: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC1                (1 << 1)  /* Self-diagnosis Channel for A/D unit 1: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC4                (1 << 4)  /* Temperature Sensor Channel: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC5                (1 << 5)  /* Internal Reference Voltage Channel: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC6                (1 << 6)  /* VBATT 1/3 voltage monitor output Channel: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC8                (1 << 8)  /* D/A Converter 0 Channel: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC9                (1 << 9)  /* D/A Converter 1 Channel: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC16               (1 << 16)  /* Self-diagnosis Channel for Sample-and-hold circuit unit0: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC17               (1 << 17)  /* Self-diagnosis Channel for Sample-and-hold circuit unit1: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC18               (1 << 18)  /* Self-diagnosis Channel for Sample-and-hold circuit unit2: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC20               (1 << 20)  /* Self-diagnosis Channel for Sample-and-hold circuit unit4: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC21               (1 << 21)  /* Self-diagnosis Channel for Sample-and-hold circuit unit5: Compare Match Flag Clear */

#define R_ADC_B_ADOVFEXSCR_OVFEXC22               (1 << 22)  /* Self-diagnosis Channel for Sample-and-hold circuit unit6: Compare Match Flag Clear */

/* ADFIFOSR0 Register bit definitions */
#define R_ADC_B_ADFIFOSR0_FIFOST0_SHIFT           (0)  /* Number of Available Stages in FIFO for Scan Group 0 */
#define R_ADC_B_ADFIFOSR0_FIFOST0_MASK            0xf

#define R_ADC_B_ADFIFOSR0_FIFOST1_SHIFT           (16)  /* Number of Available Stages in FIFO for Scan Group 1 */
#define R_ADC_B_ADFIFOSR0_FIFOST1_MASK            0xf0000

/* ADFIFOSR1 Register bit definitions */
#define R_ADC_B_ADFIFOSR1_FIFOST2_SHIFT           (0)  /* Number of Available Stages in FIFO for Scan Group 2 */
#define R_ADC_B_ADFIFOSR1_FIFOST2_MASK            0xf

#define R_ADC_B_ADFIFOSR1_FIFOST3_SHIFT           (16)  /* Number of Available Stages in FIFO for Scan Group 3 */
#define R_ADC_B_ADFIFOSR1_FIFOST3_MASK            0xf0000

/* ADFIFOSR2 Register bit definitions */
#define R_ADC_B_ADFIFOSR2_FIFOST4_SHIFT           (0)  /* Number of Available Stages in FIFO for Scan Group 4 */
#define R_ADC_B_ADFIFOSR2_FIFOST4_MASK            0xf

#define R_ADC_B_ADFIFOSR2_FIFOST5_SHIFT           (16)  /* Number of Available Stages in FIFO for Scan Group 5 */
#define R_ADC_B_ADFIFOSR2_FIFOST5_MASK            0xf0000

/* ADFIFOSR3 Register bit definitions */
#define R_ADC_B_ADFIFOSR3_FIFOST6_SHIFT           (0)  /* Number of Available Stages in FIFO for Scan Group 6 */
#define R_ADC_B_ADFIFOSR3_FIFOST6_MASK            0xf

#define R_ADC_B_ADFIFOSR3_FIFOST7_SHIFT           (16)  /* Number of Available Stages in FIFO for Scan Group 7 */
#define R_ADC_B_ADFIFOSR3_FIFOST7_MASK            0xf0000

/* ADFIFOSR4 Register bit definitions */
#define R_ADC_B_ADFIFOSR4_FIFOST8_SHIFT           (0)  /* Number of Available Stages in FIFO for Scan Group 8 */
#define R_ADC_B_ADFIFOSR4_FIFOST8_MASK            0xf

/* ADFIFODCR Register bit definitions */
#define R_ADC_B_ADFIFODCR_FIFODCN_SHIFT           (0)  /* Scan Group n FIFO Data Clear */
#define R_ADC_B_ADFIFODCR_FIFODCN_MASK            0x1ff
#  define R_ADC_B_ADFIFODCR_FIFODCN_0                     (0 << R_ADC_B_ADFIFODCR_FIFODCN_SHIFT)  /* No effect */
#  define R_ADC_B_ADFIFODCR_FIFODCN_1                     (1 << R_ADC_B_ADFIFODCR_FIFODCN_SHIFT)  /* Clear the data of scan group n FIFO */

#define R_ADC_B_ADFIFODCR_FIFODCN_SHIFT           (0)  /* Scan Group n FIFO Data Clear */
#define R_ADC_B_ADFIFODCR_FIFODCN_MASK            0x1ff

/* ADFIFOERSR Register bit definitions */
#define R_ADC_B_ADFIFOERSR_FIFOOVFN_SHIFT         (0)  /* Scan Group n FIFO Overflow Flag */
#define R_ADC_B_ADFIFOERSR_FIFOOVFN_MASK          0x1ff
#  define R_ADC_B_ADFIFOERSR_FIFOOVFN_0                   (0 << R_ADC_B_ADFIFOERSR_FIFOOVFN_SHIFT)  /* No overflow */
#  define R_ADC_B_ADFIFOERSR_FIFOOVFN_1                   (1 << R_ADC_B_ADFIFOERSR_FIFOOVFN_SHIFT)  /* FIFO overflow is detected */

#define R_ADC_B_ADFIFOERSR_FIFOFLFN_SHIFT         (16)  /* Scan Group n FIFO Data Full Flag */
#define R_ADC_B_ADFIFOERSR_FIFOFLFN_MASK          0x1ff0000
#  define R_ADC_B_ADFIFOERSR_FIFOFLFN_0                   (0 << R_ADC_B_ADFIFOERSR_FIFOFLFN_SHIFT)  /* FIFO is not full */
#  define R_ADC_B_ADFIFOERSR_FIFOFLFN_1                   (1 << R_ADC_B_ADFIFOERSR_FIFOFLFN_SHIFT)  /* FIFO is detected full to capacity */

#define R_ADC_B_ADFIFOERSR_FIFOOVFN_SHIFT         (0)  /* Scan Group n FIFO Overflow Flag */
#define R_ADC_B_ADFIFOERSR_FIFOOVFN_MASK          0x1ff

#define R_ADC_B_ADFIFOERSR_FIFOFLFN_SHIFT         (16)  /* Scan Group n FIFO Data Full Flag */
#define R_ADC_B_ADFIFOERSR_FIFOFLFN_MASK          0x1ff0000

/* ADFIFOERSCR Register bit definitions */
#define R_ADC_B_ADFIFOERSCR_FIFOOVFCN_SHIFT       (0)  /* Scan Group n FIFO Overflow Flag Clear */
#define R_ADC_B_ADFIFOERSCR_FIFOOVFCN_MASK        0x1ff
#  define R_ADC_B_ADFIFOERSCR_FIFOOVFCN_0                 (0 << R_ADC_B_ADFIFOERSCR_FIFOOVFCN_SHIFT)  /* No effect */
#  define R_ADC_B_ADFIFOERSCR_FIFOOVFCN_1                 (1 << R_ADC_B_ADFIFOERSCR_FIFOOVFCN_SHIFT)  /* ADFIFOERSR.FIFOOVFn is cleared */

#define R_ADC_B_ADFIFOERSCR_FIFOFLCN_SHIFT        (16)  /* Scan Group n FIFO Data Full Flag Clear */
#define R_ADC_B_ADFIFOERSCR_FIFOFLCN_MASK         0x1ff0000
#  define R_ADC_B_ADFIFOERSCR_FIFOFLCN_0                  (0 << R_ADC_B_ADFIFOERSCR_FIFOFLCN_SHIFT)  /* No effect */
#  define R_ADC_B_ADFIFOERSCR_FIFOFLCN_1                  (1 << R_ADC_B_ADFIFOERSCR_FIFOFLCN_SHIFT)  /* ADFIFOERSR.FIFOFLFn is cleared */

#define R_ADC_B_ADFIFOERSCR_FIFOOVFCN_SHIFT       (0)  /* Scan Group n FIFO Overflow Flag Clear */
#define R_ADC_B_ADFIFOERSCR_FIFOOVFCN_MASK        0x1ff

#define R_ADC_B_ADFIFOERSCR_FIFOFLCN_SHIFT        (16)  /* Scan Group n FIFO Data Full Flag Clear */
#define R_ADC_B_ADFIFOERSCR_FIFOFLCN_MASK         0x1ff0000

/* ADCMPTBSR Register bit definitions */
#define R_ADC_B_ADCMPTBSR_CMPTBFN_SHIFT           (0)  /* Compare Match Table n Match Flag */
#define R_ADC_B_ADCMPTBSR_CMPTBFN_MASK            0xff
#  define R_ADC_B_ADCMPTBSR_CMPTBFN_0                     (0 << R_ADC_B_ADCMPTBSR_CMPTBFN_SHIFT)  /* Match event with compare match table n is not detected */
#  define R_ADC_B_ADCMPTBSR_CMPTBFN_1                     (1 << R_ADC_B_ADCMPTBSR_CMPTBFN_SHIFT)  /* Match event with compare match table n is detected */

#define R_ADC_B_ADCMPTBSR_CMPTBFN_SHIFT           (0)  /* Compare Match Table n Match Flag */
#define R_ADC_B_ADCMPTBSR_CMPTBFN_MASK            0xff

/* ADCMPTBSCR Register bit definitions */
#define R_ADC_B_ADCMPTBSCR_CMPTBCN_SHIFT          (0)  /* Compare Match Table n : Match Flag Clear */
#define R_ADC_B_ADCMPTBSCR_CMPTBCN_MASK           0xff
#  define R_ADC_B_ADCMPTBSCR_CMPTBCN_0                    (0 << R_ADC_B_ADCMPTBSCR_CMPTBCN_SHIFT)  /* No effect */
#  define R_ADC_B_ADCMPTBSCR_CMPTBCN_1                    (1 << R_ADC_B_ADCMPTBSCR_CMPTBCN_SHIFT)  /* ADCMPTBSR.CMPTBFn is cleared */

#define R_ADC_B_ADCMPTBSCR_CMPTBCN_SHIFT          (0)  /* Compare Match Table n : Match Flag Clear */
#define R_ADC_B_ADCMPTBSCR_CMPTBCN_MASK           0xff

/* ADCMPCHSR0 Register bit definitions */
#define R_ADC_B_ADCMPCHSR0_CMPCHFN_SHIFT          (0)  /* Analog Channel No. n : Compare Match Flag */
#define R_ADC_B_ADCMPCHSR0_CMPCHFN_MASK           0x7fffff
#  define R_ADC_B_ADCMPCHSR0_CMPCHFN_0                    (0 << R_ADC_B_ADCMPCHSR0_CMPCHFN_SHIFT)  /* Compare match is not detected */
#  define R_ADC_B_ADCMPCHSR0_CMPCHFN_1                    (1 << R_ADC_B_ADCMPCHSR0_CMPCHFN_SHIFT)  /* Compare match is detected */

#define R_ADC_B_ADCMPCHSR0_CMPCHFN_SHIFT          (0)  /* Analog Channel No. n : Compare Match Flag */
#define R_ADC_B_ADCMPCHSR0_CMPCHFN_MASK           0x7fffff

/* ADCMPEXSR Register bit definitions */
#define R_ADC_B_ADCMPEXSR_CMPEXF0                 (1 << 0)  /* Self-diagnosis Channel for A/D unit 0: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF1                 (1 << 1)  /* Self-diagnosis Channel for A/D unit 1: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF4                 (1 << 4)  /* Temperature Sensor Channel: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF5                 (1 << 5)  /* Internal Reference Voltage Channel: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF6                 (1 << 6)  /* VBATT 1/3 voltage monitor output Channel: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF8                 (1 << 8)  /* D/A Converter 0 Channel : Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF9                 (1 << 9)  /* D/A Converter 1 Channel: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF16                (1 << 16)  /* Self-diagnosis Channel for Sample-and-hold circuit unit0: Compare Match Flag  */

#define R_ADC_B_ADCMPEXSR_CMPEXF17                (1 << 17)  /* Self-diagnosis Channel for Sample-and-hold circuit unit1: Compare Match Flag  */

#define R_ADC_B_ADCMPEXSR_CMPEXF18                (1 << 18)  /* Self-diagnosis Channel for Sample-and-hold circuit unit2: Compare Match Flag  */

#define R_ADC_B_ADCMPEXSR_CMPEXF20                (1 << 20)  /* Self-diagnosis Channel for Sample-and-hold circuit unit4: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF21                (1 << 21)  /* Self-diagnosis Channel for Sample-and-hold circuit unit4: Compare Match Flag */

#define R_ADC_B_ADCMPEXSR_CMPEXF22                (1 << 22)  /* Self-diagnosis Channel for Sample-and-hold circuit unit4: Compare Match Flag */

/* ADCMPCHSCR0 Register bit definitions */
#define R_ADC_B_ADCMPCHSCR0_CMPCHCN_SHIFT         (0)  /* Analog Channel No. n : Compare Match Flag Clear bit */
#define R_ADC_B_ADCMPCHSCR0_CMPCHCN_MASK          0x7fffff
#  define R_ADC_B_ADCMPCHSCR0_CMPCHCN_0                   (0 << R_ADC_B_ADCMPCHSCR0_CMPCHCN_SHIFT)  /* No effect */
#  define R_ADC_B_ADCMPCHSCR0_CMPCHCN_1                   (1 << R_ADC_B_ADCMPCHSCR0_CMPCHCN_SHIFT)  /* ADCMPCHSR0.CMPCHFn is cleared */

#define R_ADC_B_ADCMPCHSCR0_CMPCHCN_SHIFT         (0)  /* Analog Channel No. n : Compare Match Flag Clear bit */
#define R_ADC_B_ADCMPCHSCR0_CMPCHCN_MASK          0x7fffff

/* ADCMPEXSCR Register bit definitions */
#define R_ADC_B_ADCMPEXSCR_CMPEXC0                (1 << 0)  /* Self-diagnosis Channel for A/D unit 0: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC1                (1 << 1)  /* Self-diagnosis Channel for A/D unit 1: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC4                (1 << 4)  /* Temperature Sensor Channel: Compare Match Flag Clear  */

#define R_ADC_B_ADCMPEXSCR_CMPEXC5                (1 << 5)  /* Internal Reference Voltage Channel: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC6                (1 << 6)  /* VBATT 1/3 voltage monitor output Channel: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC8                (1 << 8)  /* D/A Converter 0 Channel: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC9                (1 << 9)  /* D/A Converter 1 Channel : Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC16               (1 << 16)  /* Self-diagnosis Channel for Sample-and-hold circuit unit0: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC17               (1 << 17)  /* Self-diagnosis Channel for Sample-and-hold circuit unit1: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC18               (1 << 18)  /* Self-diagnosis Channel for Sample-and-hold circuit unit2: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC20               (1 << 20)  /* Self-diagnosis Channel for Sample-and-hold circuit unit4: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC21               (1 << 21)  /* Self-diagnosis Channel for Sample-and-hold circuit unit5: Compare Match Flag Clear */

#define R_ADC_B_ADCMPEXSCR_CMPEXC22               (1 << 22)  /* Self-diagnosis Channel for Sample-and-hold circuit unit6: Compare Match Flag Clear */

/* ADLIMGRSR Register bit definitions */
#define R_ADC_B_ADLIMGRSR_LIMGRFN_SHIFT           (0)  /* Scan Group n Limiter Clip Flag */
#define R_ADC_B_ADLIMGRSR_LIMGRFN_MASK            0x1ff
#  define R_ADC_B_ADLIMGRSR_LIMGRFN_0                     (0 << R_ADC_B_ADLIMGRSR_LIMGRFN_SHIFT)  /* Limiter clip for scan group n is not detected */
#  define R_ADC_B_ADLIMGRSR_LIMGRFN_1                     (1 << R_ADC_B_ADLIMGRSR_LIMGRFN_SHIFT)  /* Limiter clip for scan group n is detected */

#define R_ADC_B_ADLIMGRSR_LIMGRFN_SHIFT           (0)  /* Scan Group n Limiter Clip Flag */
#define R_ADC_B_ADLIMGRSR_LIMGRFN_MASK            0x1ff

/* ADLIMCHSR0 Register bit definitions */
#define R_ADC_B_ADLIMCHSR0_LIMCHFN_SHIFT          (0)  /* Analog Channel No. n : Limiter Clip Flag bit */
#define R_ADC_B_ADLIMCHSR0_LIMCHFN_MASK           0x7fffff
#  define R_ADC_B_ADLIMCHSR0_LIMCHFN_0                    (0 << R_ADC_B_ADLIMCHSR0_LIMCHFN_SHIFT)  /* Limiter clip is not detected */
#  define R_ADC_B_ADLIMCHSR0_LIMCHFN_1                    (1 << R_ADC_B_ADLIMCHSR0_LIMCHFN_SHIFT)  /* Limiter clip is detected */

#define R_ADC_B_ADLIMCHSR0_LIMCHFN_SHIFT          (0)  /* Analog Channel No. n : Limiter Clip Flag bit */
#define R_ADC_B_ADLIMCHSR0_LIMCHFN_MASK           0x7fffff

/* ADLIMEXSR Register bit definitions */
#define R_ADC_B_ADLIMEXSR_LIMEXF0                 (1 << 0)  /* Self-diagnosis Channel for A/D unit 0: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF1                 (1 << 1)  /* Temperature Sensor Channel for A/D unit 1: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF4                 (1 << 4)  /* Temperature Sensor Channel: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF5                 (1 << 5)  /* Internal Reference Voltage Channel: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF6                 (1 << 6)  /* VBATT 1/3 voltage monitor output Channel: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF8                 (1 << 8)  /* D/A Converter 0 Channel: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF9                 (1 << 9)  /* D/A Converter 1 Channel: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF16                (1 << 16)  /* Self-diagnosis Channel for Sample-and-hold circuit unit0: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF17                (1 << 17)  /* Self-diagnosis Channel for Sample-and-hold circuit unit1: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF18                (1 << 18)  /* Self-diagnosis Channel for Sample-and-hold circuit unit2: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF20                (1 << 20)  /* Self-diagnosis Channel for Sample-and-hold circuit unit4: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF21                (1 << 21)  /* Self-diagnosis Channel for Sample-and-hold circuit unit5: Limiter Clip Flag */

#define R_ADC_B_ADLIMEXSR_LIMEXF22                (1 << 22)  /* Self-diagnosis Channel for Sample-and-hold circuit unit6: Limiter Clip Flag */

/* ADLIMGRSCR Register bit definitions */
#define R_ADC_B_ADLIMGRSCR_LIMGRCN_SHIFT          (0)  /* Scan Group n Limiter Clip Flag Clear */
#define R_ADC_B_ADLIMGRSCR_LIMGRCN_MASK           0x1ff
#  define R_ADC_B_ADLIMGRSCR_LIMGRCN_0                    (0 << R_ADC_B_ADLIMGRSCR_LIMGRCN_SHIFT)  /* No effect */
#  define R_ADC_B_ADLIMGRSCR_LIMGRCN_1                    (1 << R_ADC_B_ADLIMGRSCR_LIMGRCN_SHIFT)  /* ADLIMGRSR.LIMGRFn is cleared */

#define R_ADC_B_ADLIMGRSCR_LIMGRCN_SHIFT          (0)  /* Scan Group n Limiter Clip Flag Clear */
#define R_ADC_B_ADLIMGRSCR_LIMGRCN_MASK           0x1ff

/* ADLIMCHSCR0 Register bit definitions */
#define R_ADC_B_ADLIMCHSCR0_LIMCHCN_SHIFT         (0)  /* Analog Channel No. n Limiter Clip Flag Clear bit */
#define R_ADC_B_ADLIMCHSCR0_LIMCHCN_MASK          0x7fffff
#  define R_ADC_B_ADLIMCHSCR0_LIMCHCN_0                   (0 << R_ADC_B_ADLIMCHSCR0_LIMCHCN_SHIFT)  /* No effect */
#  define R_ADC_B_ADLIMCHSCR0_LIMCHCN_1                   (1 << R_ADC_B_ADLIMCHSCR0_LIMCHCN_SHIFT)  /* ADLIMCHSR0.LIMCHFn is cleared */

#define R_ADC_B_ADLIMCHSCR0_LIMCHCN_SHIFT         (0)  /* Analog Channel No. n Limiter Clip Flag Clear bit */
#define R_ADC_B_ADLIMCHSCR0_LIMCHCN_MASK          0x7fffff

/* ADLIMEXSCR Register bit definitions */
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
#define R_ADC_B_ADSCANENDSR_SCENDFN_SHIFT         (0)  /* Scan Group n Scan End Flag */
#define R_ADC_B_ADSCANENDSR_SCENDFN_MASK          0x1ff
#  define R_ADC_B_ADSCANENDSR_SCENDFN_0                   (0 << R_ADC_B_ADSCANENDSR_SCENDFN_SHIFT)  /* Scan group n has not been scanned */
#  define R_ADC_B_ADSCANENDSR_SCENDFN_1                   (1 << R_ADC_B_ADSCANENDSR_SCENDFN_SHIFT)  /* End of scan for scan group n is detected */

#define R_ADC_B_ADSCANENDSR_SCENDFN_SHIFT         (0)  /* Scan Group n Scan End Flag */
#define R_ADC_B_ADSCANENDSR_SCENDFN_MASK          0x1ff

/* ADSCANENDSCR Register bit definitions */
#define R_ADC_B_ADSCANENDSCR_SCENDCN_SHIFT        (0)  /* Scan Group n Scan End Flag Clear */
#define R_ADC_B_ADSCANENDSCR_SCENDCN_MASK         0x1ff
#  define R_ADC_B_ADSCANENDSCR_SCENDCN_0                  (0 << R_ADC_B_ADSCANENDSCR_SCENDCN_SHIFT)  /* No effect */
#  define R_ADC_B_ADSCANENDSCR_SCENDCN_1                  (1 << R_ADC_B_ADSCANENDSCR_SCENDCN_SHIFT)  /* ADSCANENDSR.SCENDFn is cleared */

#define R_ADC_B_ADSCANENDSCR_SCENDCN_SHIFT        (0)  /* Scan Group n Scan End Flag Clear */
#define R_ADC_B_ADSCANENDSCR_SCENDCN_MASK         0x1ff

/* ADDR Register bit definitions */
#define R_ADC_B_ADDR_DATA_SHIFT                   (0)  /* A/D conversion data */
#define R_ADC_B_ADDR_DATA_MASK                    0xffff

#define R_ADC_B_ADDR_ERR                          (1 << 31)  /* A/D conversion data error status */

/* ADEXDR Register bit definitions */
#define R_ADC_B_ADEXDR_DATA_SHIFT                 (0)  /* A/D conversion data */
#define R_ADC_B_ADEXDR_DATA_MASK                  0xffff

#define R_ADC_B_ADEXDR_DIAGSR_SHIFT               (24)  /* Self-Diagnosis Status */
#define R_ADC_B_ADEXDR_DIAGSR_MASK                0x7000000

#define R_ADC_B_ADEXDR_ERR                        (1 << 31)  /* A/D Conversion Error Status */

/* ADFIFODR Register bit definitions */
#define R_ADC_B_ADFIFODR_DATA_SHIFT               (0)  /* A/D Conversion Data */
#define R_ADC_B_ADFIFODR_DATA_MASK                0xffff

#define R_ADC_B_ADFIFODR_CH_SHIFT                 (24)  /* A/D Conversion Channel Number */
#define R_ADC_B_ADFIFODR_CH_MASK                  0x7f000000

#define R_ADC_B_ADFIFODR_ERR                      (1 << 31)  /* A/D Conversion Data Error Status */


/* Maximum number of channels */

#define ADC_B_MAX_CHANNELS    33

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ADC_B_H */

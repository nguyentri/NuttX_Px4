/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8e1/ra_adc12.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_ADC12_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_ADC12_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ADC12 Base Address */
#ifndef R_ADC12_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_ADC12_BASE           0x40332000
#else
#define R_ADC12_BASE           0x50332000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_ADC12_CH_STRIDE    0x00000200
#define R_ADC12_CH_BASE(ch)   (R_ADC12_BASE + ((uint32_t)(ch) * R_ADC12_CH_STRIDE))

/* ADC12 Register Offsets */

#define R_ADC12_ADCSR_OFFSET                      0x00000000  /* A/D Control Register */
#define R_ADC12_ADANSA0_OFFSET                    0x00000004  /* A/D Channel Select Register A0 */
#define R_ADC12_ADANSA1_OFFSET                    0x00000006  /* A/D Channel Select Register A1 */
#define R_ADC12_ADADS0_OFFSET                     0x00000008  /* A/D-Converted Value Addition/Average Channel Select Register 0 */
#define R_ADC12_ADADS1_OFFSET                     0x0000000a  /* A/D-Converted Value Addition/Average Channel Select Register 1 */
#define R_ADC12_ADADC_OFFSET                      0x0000000c  /* A/D-Converted Value Addition/Average Count Select Register */
#define R_ADC12_ADCER_OFFSET                      0x0000000e  /* A/D Control Extended Register */
#define R_ADC12_ADSTRGR_OFFSET                    0x00000010  /* A/D Conversion Start Trigger Select Register */
#define R_ADC12_ADEXICR_OFFSET                    0x00000012  /* A/D Conversion Extended Input Control Registers */
#define R_ADC12_ADANSB0_OFFSET                    0x00000014  /* A/D Channel Select Register B0 */
#define R_ADC12_ADANSB1_OFFSET                    0x00000016  /* A/D Channel Select Register B1 */
#define R_ADC12_ADDBLDR_OFFSET                    0x00000018  /* A/D Data Duplexing Register */
#define R_ADC12_ADTSDR_OFFSET                     0x0000001a  /* A/D Temperature Sensor Data Register */
#define R_ADC12_ADOCDR_OFFSET                     0x0000001c  /* A/D Internal Reference Voltage Data Register */
#define R_ADC12_ADRD_OFFSET                       0x0000001e  /* A/D Self-Diagnosis Data Register */
/* ADDR%s Registers (0-8) */
#define R_ADC12_ADDR_OFFSET(m)                    (0x00000020 + ((m) * 0x00000002))  /* A/D Data Registers %s */
/* ADDR%s Registers (16-19) */
#define R_ADC12_ADVMDR_OFFSET                     0x00000026  /* A/D VBATT Monitor Data Register */
#define R_ADC12_ADSHCR_OFFSET                     0x00000066  /* A/D Sample and Hold Circuit Control Register */
#define R_ADC12_ADDISCR_OFFSET                    0x0000007a  /* A/D Disconnection Detection Control Register */
#define R_ADC12_ADSHMSR_OFFSET                    0x0000007c  /* A/D Sample and Hold Operation Mode Selection Register */
#define R_ADC12_ADGSPCR_OFFSET                    0x00000080  /* A/D Group Scan Priority Control Register */
#define R_ADC12_ADDBLDRA_OFFSET                   0x00000084  /* A/D Data Duplexing Register A */
#define R_ADC12_ADDBLDRB_OFFSET                   0x00000086  /* A/D Data Duplexing Register B */
#define R_ADC12_ADWINMON_OFFSET                   0x0000008c  /* A/D Compare Function Window A/B Status Monitor Register */
#define R_ADC12_ADCMPCR_OFFSET                    0x00000090  /* A/D Compare Function Control Register */
#define R_ADC12_ADCMPANSER_OFFSET                 0x00000092  /* A/D Compare Function Window A Extended Input Select Register */
#define R_ADC12_ADCMPLER_OFFSET                   0x00000093  /* A/D Compare Function Window A Extended Input Comparison Condition Setting Register */
#define R_ADC12_ADCMPANSR0_OFFSET                 0x00000094  /* A/D Compare Function Window A Channel Select Register 0 */
#define R_ADC12_ADCMPLR0_OFFSET                   0x00000098  /* A/D Compare Function Window A Comparison Condition Setting Register 0 */
/* ADCMPDR%s Registers (0-1) */
#define R_ADC12_ADCMPDR_OFFSET(m)                 (0x0000009c + ((m) * 0x00000002))  /* A/D Compare Function Window A Lower-Side/Upper-Side Level Setting Register */
#define R_ADC12_ADCMPSR0_OFFSET                   0x000000a0  /* A/D Compare Function Window A Channel Status Register 0 */
#define R_ADC12_ADCMPSER_OFFSET                   0x000000a4  /* A/D Compare Function Window A Extended Input Channel Status Register */
#define R_ADC12_ADCMPBNSR_OFFSET                  0x000000a6  /* A/D Compare Function Window B Channel Select Register */
#define R_ADC12_ADWINLLB_OFFSET                   0x000000a8  /* A/D Compare Function Window B Lower-Side/Upper-Side Level Setting Register */
#define R_ADC12_ADWINULB_OFFSET                   0x000000aa  /* A/D Compare Function Window B Lower-Side/Upper-Side Level Setting Register */
#define R_ADC12_ADCMPBSR_OFFSET                   0x000000ac  /* A/D Compare Function Window B Status Register */
/* ADBUF%s Registers (0-15) */
#define R_ADC12_ADBUF_OFFSET(m)                   (0x000000b0 + ((m) * 0x00000002))  /* A/D Data Buffer Registers %s */
#define R_ADC12_ADBUFEN_OFFSET                    0x000000d0  /* A/D Data Buffer Enable Register */
#define R_ADC12_ADBUFPTR_OFFSET                   0x000000d2  /* A/D Data Buffer Pointer Register */
#define R_ADC12_ADSSTRL_OFFSET                    0x000000dd  /* A/D Sampling State Register */
#define R_ADC12_ADSSTRT_OFFSET                    0x000000de  /* A/D Sampling State Register */
#define R_ADC12_ADSSTRO_OFFSET                    0x000000df  /* A/D Sampling State Register */
/* ADSSTR%s Registers (0-8) */
#define R_ADC12_ADSSTR_OFFSET(m)                  (0x000000e0 + ((m) * 0x00000001))  /* A/D Sampling State Register */
#define R_ADC12_ADSSTRV_OFFSET                    0x000000e3  /* A/D Sampling State Register */
/* ADSSTR%s Registers (16-19) */

/* ADC12 Register Addresses */

#define R_ADC12_ADCSR(n)                          (R_ADC12_CH_BASE(n) + R_ADC12_ADCSR_OFFSET)
#define R_ADC12_ADANSA0(n)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADANSA0_OFFSET)
#define R_ADC12_ADANSA1(n)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADANSA1_OFFSET)
#define R_ADC12_ADADS0(n)                         (R_ADC12_CH_BASE(n) + R_ADC12_ADADS0_OFFSET)
#define R_ADC12_ADADS1(n)                         (R_ADC12_CH_BASE(n) + R_ADC12_ADADS1_OFFSET)
#define R_ADC12_ADADC(n)                          (R_ADC12_CH_BASE(n) + R_ADC12_ADADC_OFFSET)
#define R_ADC12_ADCER(n)                          (R_ADC12_CH_BASE(n) + R_ADC12_ADCER_OFFSET)
#define R_ADC12_ADSTRGR(n)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADSTRGR_OFFSET)
#define R_ADC12_ADEXICR(n)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADEXICR_OFFSET)
#define R_ADC12_ADANSB0(n)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADANSB0_OFFSET)
#define R_ADC12_ADANSB1(n)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADANSB1_OFFSET)
#define R_ADC12_ADDBLDR(n)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADDBLDR_OFFSET)
#define R_ADC12_ADTSDR(n)                         (R_ADC12_CH_BASE(n) + R_ADC12_ADTSDR_OFFSET)
#define R_ADC12_ADOCDR(n)                         (R_ADC12_CH_BASE(n) + R_ADC12_ADOCDR_OFFSET)
#define R_ADC12_ADRD(n)                           (R_ADC12_CH_BASE(n) + R_ADC12_ADRD_OFFSET)
#define R_ADC12_ADDR(n, m)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADDR_OFFSET(m))
#define R_ADC12_ADVMDR(n)                         (R_ADC12_CH_BASE(n) + R_ADC12_ADVMDR_OFFSET)
#define R_ADC12_ADSHCR(n)                         (R_ADC12_CH_BASE(n) + R_ADC12_ADSHCR_OFFSET)
#define R_ADC12_ADDISCR(n)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADDISCR_OFFSET)
#define R_ADC12_ADSHMSR(n)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADSHMSR_OFFSET)
#define R_ADC12_ADGSPCR(n)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADGSPCR_OFFSET)
#define R_ADC12_ADDBLDRA(n)                       (R_ADC12_CH_BASE(n) + R_ADC12_ADDBLDRA_OFFSET)
#define R_ADC12_ADDBLDRB(n)                       (R_ADC12_CH_BASE(n) + R_ADC12_ADDBLDRB_OFFSET)
#define R_ADC12_ADWINMON(n)                       (R_ADC12_CH_BASE(n) + R_ADC12_ADWINMON_OFFSET)
#define R_ADC12_ADCMPCR(n)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADCMPCR_OFFSET)
#define R_ADC12_ADCMPANSER(n)                     (R_ADC12_CH_BASE(n) + R_ADC12_ADCMPANSER_OFFSET)
#define R_ADC12_ADCMPLER(n)                       (R_ADC12_CH_BASE(n) + R_ADC12_ADCMPLER_OFFSET)
#define R_ADC12_ADCMPANSR0(n)                     (R_ADC12_CH_BASE(n) + R_ADC12_ADCMPANSR0_OFFSET)
#define R_ADC12_ADCMPLR0(n)                       (R_ADC12_CH_BASE(n) + R_ADC12_ADCMPLR0_OFFSET)
#define R_ADC12_ADCMPDR(n, m)                     (R_ADC12_CH_BASE(n) + R_ADC12_ADCMPDR_OFFSET(m))
#define R_ADC12_ADCMPSR0(n)                       (R_ADC12_CH_BASE(n) + R_ADC12_ADCMPSR0_OFFSET)
#define R_ADC12_ADCMPSER(n)                       (R_ADC12_CH_BASE(n) + R_ADC12_ADCMPSER_OFFSET)
#define R_ADC12_ADCMPBNSR(n)                      (R_ADC12_CH_BASE(n) + R_ADC12_ADCMPBNSR_OFFSET)
#define R_ADC12_ADWINLLB(n)                       (R_ADC12_CH_BASE(n) + R_ADC12_ADWINLLB_OFFSET)
#define R_ADC12_ADWINULB(n)                       (R_ADC12_CH_BASE(n) + R_ADC12_ADWINULB_OFFSET)
#define R_ADC12_ADCMPBSR(n)                       (R_ADC12_CH_BASE(n) + R_ADC12_ADCMPBSR_OFFSET)
#define R_ADC12_ADBUF(n, m)                       (R_ADC12_CH_BASE(n) + R_ADC12_ADBUF_OFFSET(m))
#define R_ADC12_ADBUFEN(n)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADBUFEN_OFFSET)
#define R_ADC12_ADBUFPTR(n)                       (R_ADC12_CH_BASE(n) + R_ADC12_ADBUFPTR_OFFSET)
#define R_ADC12_ADSSTRL(n)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADSSTRL_OFFSET)
#define R_ADC12_ADSSTRT(n)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADSSTRT_OFFSET)
#define R_ADC12_ADSSTRO(n)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADSSTRO_OFFSET)
#define R_ADC12_ADSSTR(n, m)                      (R_ADC12_CH_BASE(n) + R_ADC12_ADSSTR_OFFSET(m))
#define R_ADC12_ADSSTRV(n)                        (R_ADC12_CH_BASE(n) + R_ADC12_ADSSTRV_OFFSET)

/* Register bit definitions */
/* ADCSR Register bit definitions */
#define R_ADC12_ADCSR_DBLANS_SHIFT                (0)  /* Double Trigger Channel Select */
#define R_ADC12_ADCSR_DBLANS_MASK                 0x1f

#define R_ADC12_ADCSR_GBADIE                      (1 << 6)  /* Group B Scan End Interrupt and ELC Event Enable */

#define R_ADC12_ADCSR_DBLE                        (1 << 7)  /* Double Trigger Mode Select */

#define R_ADC12_ADCSR_EXTRG                       (1 << 8)  /* Trigger Select */

#define R_ADC12_ADCSR_TRGE                        (1 << 9)  /* Trigger Start Enable */

#define R_ADC12_ADCSR_ADCS_SHIFT                  (13)  /* Scan Mode Select */
#define R_ADC12_ADCSR_ADCS_MASK                   0x6000
#  define R_ADC12_ADCSR_ADCS_00                           (0 << R_ADC12_ADCSR_ADCS_SHIFT)  /* Single scan mode */
#  define R_ADC12_ADCSR_ADCS_01                           (1 << R_ADC12_ADCSR_ADCS_SHIFT)  /* Group scan mode */
#  define R_ADC12_ADCSR_ADCS_10                           (2 << R_ADC12_ADCSR_ADCS_SHIFT)  /* Continuous scan mode */
#  define R_ADC12_ADCSR_ADCS_11                           (3 << R_ADC12_ADCSR_ADCS_SHIFT)  /* Setting prohibited */

#define R_ADC12_ADCSR_ADST                        (1 << 15)  /* A/D Conversion Start */

/* ADANSA0 Register bit definitions */
#define R_ADC12_ADANSA0_ANSA00                    (1 << 0)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSA0_ANSA01                    (1 << 1)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSA0_ANSA02                    (1 << 2)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSA0_ANSA03                    (1 << 3)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSA0_ANSA04                    (1 << 4)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSA0_ANSA05                    (1 << 5)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSA0_ANSA06                    (1 << 6)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSA0_ANSA07                    (1 << 7)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSA0_ANSA08                    (1 << 8)  /* A/D Conversion Channels Select */

/* ADANSA1 Register bit definitions */
#define R_ADC12_ADANSA1_ANSA16                    (1 << 0)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSA1_ANSA17                    (1 << 1)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSA1_ANSA18                    (1 << 2)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSA1_ANSA19                    (1 << 3)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSA1_ANSA20                    (1 << 4)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSA1_ANSA21                    (1 << 5)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSA1_ANSA22                    (1 << 6)  /* A/D Conversion Channels Select */

/* ADADS0 Register bit definitions */
#define R_ADC12_ADADS0_ADS00                      (1 << 0)  /* A/D-Converted Value Addition/Average Channel Select */

#define R_ADC12_ADADS0_ADS01                      (1 << 1)  /* A/D-Converted Value Addition/Average Channel Select */

#define R_ADC12_ADADS0_ADS02                      (1 << 2)  /* A/D-Converted Value Addition/Average Channel Select */

#define R_ADC12_ADADS0_ADS03                      (1 << 3)  /* A/D-Converted Value Addition/Average Channel Select */

#define R_ADC12_ADADS0_ADS04                      (1 << 4)  /* A/D-Converted Value Addition/Average Channel Select */

#define R_ADC12_ADADS0_ADS05                      (1 << 5)  /* A/D-Converted Value Addition/Average Channel Select */

#define R_ADC12_ADADS0_ADS06                      (1 << 6)  /* A/D-Converted Value Addition/Average Channel Select */

#define R_ADC12_ADADS0_ADS07                      (1 << 7)  /* A/D-Converted Value Addition/Average Channel Select */

#define R_ADC12_ADADS0_ADS08                      (1 << 8)  /* A/D-Converted Value Addition/Average Channel Select */

/* ADADS1 Register bit definitions */
#define R_ADC12_ADADS1_ADS16                      (1 << 0)  /* A/D Conversion Channels Select/Average Channel Select */

#define R_ADC12_ADADS1_ADS17                      (1 << 1)  /* A/D Conversion Channels Select/Average Channel Select */

#define R_ADC12_ADADS1_ADS18                      (1 << 2)  /* A/D Conversion Channels Select/Average Channel Select */

#define R_ADC12_ADADS1_ADS19                      (1 << 3)  /* A/D Conversion Channels Select/Average Channel Select */

#define R_ADC12_ADADS1_ADS20                      (1 << 4)  /* A/D Conversion Channels Select/Average Channel Select */

#define R_ADC12_ADADS1_ADS21                      (1 << 5)  /* A/D Conversion Channels Select/Average Channel Select */

#define R_ADC12_ADADS1_ADS22                      (1 << 6)  /* A/D Conversion Channels Select/Average Channel Select */

/* ADADC Register bit definitions */
#define R_ADC12_ADADC_ADC_SHIFT                   (0)  /* Addition/Average Count Select */
#define R_ADC12_ADADC_ADC_MASK                    0x7
#  define R_ADC12_ADADC_ADC_000                           (0 << R_ADC12_ADADC_ADC_SHIFT)  /* 1-time conversion (no addition, same as normal conversion) */
#  define R_ADC12_ADADC_ADC_001                           (1 << R_ADC12_ADADC_ADC_SHIFT)  /* 2-time conversion (1 addition) */
#  define R_ADC12_ADADC_ADC_010                           (2 << R_ADC12_ADADC_ADC_SHIFT)  /* 3-time conversion (2 additions) */
#  define R_ADC12_ADADC_ADC_011                           (3 << R_ADC12_ADADC_ADC_SHIFT)  /* 4-time conversion (3 additions) */
#  define R_ADC12_ADADC_ADC_101                           (5 << R_ADC12_ADADC_ADC_SHIFT)  /* 16-time conversion (15 additions) */

#define R_ADC12_ADADC_AVEE                        (1 << 7)  /* Average Mode Select */

/* ADCER Register bit definitions */
#define R_ADC12_ADCER_ADPRC_SHIFT                 (1)  /*  */
#define R_ADC12_ADCER_ADPRC_MASK                  0x6
#  define R_ADC12_ADCER_ADPRC_00                          (0 << R_ADC12_ADCER_ADPRC_SHIFT)  /* 12-bit accuracy */
#  define R_ADC12_ADCER_ADPRC_01                          (1 << R_ADC12_ADCER_ADPRC_SHIFT)  /* 10-bit accuracy */
#  define R_ADC12_ADCER_ADPRC_10                          (2 << R_ADC12_ADCER_ADPRC_SHIFT)  /* 8-bit accuracy */
#  define R_ADC12_ADCER_ADPRC_11                          (3 << R_ADC12_ADCER_ADPRC_SHIFT)  /* Setting prohibited */

#define R_ADC12_ADCER_ACE                         (1 << 5)  /* A/D Data Register Automatic Clearing Enable */

#define R_ADC12_ADCER_DIAGVAL_SHIFT               (8)  /* Self-Diagnosis Conversion Voltage Select */
#define R_ADC12_ADCER_DIAGVAL_MASK                0x300
#  define R_ADC12_ADCER_DIAGVAL_00                        (0 << R_ADC12_ADCER_DIAGVAL_SHIFT)  /* Setting prohibited when self-diagnosis is enabled */
#  define R_ADC12_ADCER_DIAGVAL_01                        (1 << R_ADC12_ADCER_DIAGVAL_SHIFT)  /* 0 volts */
#  define R_ADC12_ADCER_DIAGVAL_10                        (2 << R_ADC12_ADCER_DIAGVAL_SHIFT)  /* Reference voltage × 1/2 */
#  define R_ADC12_ADCER_DIAGVAL_11                        (3 << R_ADC12_ADCER_DIAGVAL_SHIFT)  /* Reference voltage */

#define R_ADC12_ADCER_DIAGLD                      (1 << 10)  /* Self-Diagnosis Mode Select */

#define R_ADC12_ADCER_DIAGM                       (1 << 11)  /* Self-Diagnosis Enable */

#define R_ADC12_ADCER_ADRFMT                      (1 << 15)  /* A/D Data Register Format Select */

/* ADSTRGR Register bit definitions */
#define R_ADC12_ADSTRGR_TRSB_SHIFT                (0)  /* A/D Conversion Start Trigger Select for Group B */
#define R_ADC12_ADSTRGR_TRSB_MASK                 0x3f

#define R_ADC12_ADSTRGR_TRSA_SHIFT                (8)  /* A/D Conversion Start Trigger Select */
#define R_ADC12_ADSTRGR_TRSA_MASK                 0x3f00

/* ADEXICR Register bit definitions */
#define R_ADC12_ADEXICR_TSSAD                     (1 << 0)  /* Temperature Sensor Output A/D-Converted Value Addition/Average Mode Select */

#define R_ADC12_ADEXICR_OCSAD                     (1 << 1)  /* Internal Reference Voltage A/D-Converted Value Addition/Average Mode Select */

#define R_ADC12_ADEXICR_TSSA                      (1 << 8)  /* Temperature Sensor Output A/D Conversion Select */

#define R_ADC12_ADEXICR_OCSA                      (1 << 9)  /* Internal Reference Voltage A/D Conversion Select */

#define R_ADC12_ADEXICR_TSSB                      (1 << 10)  /* Temperature Sensor Output A/D Conversion Select for Group B */

#define R_ADC12_ADEXICR_OCSB                      (1 << 11)  /* Internal Reference Voltage A/D Conversion Select for Group B */

/* ADANSB0 Register bit definitions */
#define R_ADC12_ADANSB0_ANSB00                    (1 << 0)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSB0_ANSB01                    (1 << 1)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSB0_ANSB02                    (1 << 2)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSB0_ANSB03                    (1 << 3)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSB0_ANSB04                    (1 << 4)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSB0_ANSB05                    (1 << 5)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSB0_ANSB06                    (1 << 6)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSB0_ANSB07                    (1 << 7)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSB0_ANSB08                    (1 << 8)  /* A/D Conversion Channels Select */

/* ADANSB1 Register bit definitions */
#define R_ADC12_ADANSB1_ANSB16                    (1 << 0)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSB1_ANSB17                    (1 << 1)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSB1_ANSB18                    (1 << 2)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSB1_ANSB19                    (1 << 3)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSB1_ANSB20                    (1 << 4)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSB1_ANSB21                    (1 << 5)  /* A/D Conversion Channels Select */

#define R_ADC12_ADANSB1_ANSB22                    (1 << 6)  /* A/D Conversion Channels Select */

/* ADDBLDR Register bit definitions */
#define R_ADC12_ADDBLDR_ADDBLDR_SHIFT             (0)  /* Converted Value 15 to 0 */
#define R_ADC12_ADDBLDR_ADDBLDR_MASK              0xffff

/* ADTSDR Register bit definitions */
#define R_ADC12_ADTSDR_ADTSDR_SHIFT               (0)  /* Converted Value 15 to 0 */
#define R_ADC12_ADTSDR_ADTSDR_MASK                0xffff

/* ADOCDR Register bit definitions */
#define R_ADC12_ADOCDR_ADOCDR_SHIFT               (0)  /* Converted Value 15 to 0 */
#define R_ADC12_ADOCDR_ADOCDR_MASK                0xffff

/* ADRD Register bit definitions */
#define R_ADC12_ADRD_AD_SHIFT                     (0)  /* Converted Value 11 to 0 */
#define R_ADC12_ADRD_AD_MASK                      0xfff

#define R_ADC12_ADRD_DIAGST_SHIFT                 (14)  /* Self-Diagnosis Status */
#define R_ADC12_ADRD_DIAGST_MASK                  0xc000
#  define R_ADC12_ADRD_DIAGST_00                          (0 << R_ADC12_ADRD_DIAGST_SHIFT)  /* Self-diagnosis not executed after power-on. */
#  define R_ADC12_ADRD_DIAGST_01                          (1 << R_ADC12_ADRD_DIAGST_SHIFT)  /* Self-diagnosis was executed using the 0 V voltage. */
#  define R_ADC12_ADRD_DIAGST_10                          (2 << R_ADC12_ADRD_DIAGST_SHIFT)  /* Self-diagnosis was executed using the reference voltage × 1/2. */
#  define R_ADC12_ADRD_DIAGST_11                          (3 << R_ADC12_ADRD_DIAGST_SHIFT)  /* Self-diagnosis was executed using the reference voltage . */

/* ADDR Register bit definitions */
#define R_ADC12_ADDR_ADDR_SHIFT                   (0)  /* Converted Value 15 to 0 */
#define R_ADC12_ADDR_ADDR_MASK                    0xffff

/* ADDR Register bit definitions */
#define R_ADC12_ADDR_ADDR_SHIFT                   (0)  /* Converted Value 15 to 0 */
#define R_ADC12_ADDR_ADDR_MASK                    0xffff

/* ADVMDR Register bit definitions */
#define R_ADC12_ADVMDR_ADDR_SHIFT                 (0)  /* Converted Value 15 to 0 */
#define R_ADC12_ADVMDR_ADDR_MASK                  0xffff

/* ADSHCR Register bit definitions */
#define R_ADC12_ADSHCR_SSTSH_SHIFT                (0)  /* Channel-Dedicated Sample-and-Hold Circuit Sampling Time Setting */
#define R_ADC12_ADSHCR_SSTSH_MASK                 0xff

#define R_ADC12_ADSHCR_SHANS_SHIFT                (8)  /* Channel-Dedicated Sample-and-Hold Circuit Bypass Select */
#define R_ADC12_ADSHCR_SHANS_MASK                 0x300
#  define R_ADC12_ADSHCR_SHANS_0                          (0 << R_ADC12_ADSHCR_SHANS_SHIFT)  /* Bypass the circuits */
#  define R_ADC12_ADSHCR_SHANS_1                          (1 << R_ADC12_ADSHCR_SHANS_SHIFT)  /* Use the circuits */

/* ADDISCR Register bit definitions */
#define R_ADC12_ADDISCR_ADNDIS_SHIFT              (0)  /* Disconnection Detection Assist Setting */
#define R_ADC12_ADDISCR_ADNDIS_MASK               0xf
#  define R_ADC12_ADDISCR_ADNDIS_0X0                      (0 << R_ADC12_ADDISCR_ADNDIS_SHIFT)  /* The disconnection detection assist function is disabled */
#  define R_ADC12_ADDISCR_ADNDIS_0X1                      (1 << R_ADC12_ADDISCR_ADNDIS_SHIFT)  /* Setting prohibited */

#define R_ADC12_ADDISCR_PCHG                      (1 << 4)  /* Precharge/discharge select */

/* ADSHMSR Register bit definitions */
#define R_ADC12_ADSHMSR_SHMD                      (1 << 0)  /* Sampling Operation Selection */

/* ADGSPCR Register bit definitions */
#define R_ADC12_ADGSPCR_PGS                       (1 << 0)  /* Group Priority Operation Setting */

#define R_ADC12_ADGSPCR_GBRSCN                    (1 << 1)  /* Lower-Priority Group Restart Setting */

#define R_ADC12_ADGSPCR_LGRRS                     (1 << 14)  /* Enabled only when PGS = 1 and GBRSCN = 1. */

#define R_ADC12_ADGSPCR_GBRP                      (1 << 15)  /* Single Scan Continuous Start */

/* ADDBLDRA Register bit definitions */
#define R_ADC12_ADDBLDRA_ADDBLDR_SHIFT            (0)  /* Converted Value 15 to 0 */
#define R_ADC12_ADDBLDRA_ADDBLDR_MASK             0xffff

/* ADDBLDRB Register bit definitions */
#define R_ADC12_ADDBLDRB_ADDBLDR_SHIFT            (0)  /* Converted Value 15 to 0 */
#define R_ADC12_ADDBLDRB_ADDBLDR_MASK             0xffff

/* ADWINMON Register bit definitions */
#define R_ADC12_ADWINMON_MONCOMB                  (1 << 0)  /* Combination Result Monitor */

#define R_ADC12_ADWINMON_MONCMPA                  (1 << 4)  /* Comparison Result Monitor A */

#define R_ADC12_ADWINMON_MONCMPB                  (1 << 5)  /* Comparison Result Monitor B */

/* ADCMPCR Register bit definitions */
#define R_ADC12_ADCMPCR_CMPAB_SHIFT               (0)  /* Window A/B Composite Conditions Setting */
#define R_ADC12_ADCMPCR_CMPAB_MASK                0x3
#  define R_ADC12_ADCMPCR_CMPAB_00                        (0 << R_ADC12_ADCMPCR_CMPAB_SHIFT)  /* Output ADC12i_WCMPM (i = 0, 1) when window A OR window B comparison conditions are met. Otherwise, output ADC12i_WCMPUM (i = 0, 1). */
#  define R_ADC12_ADCMPCR_CMPAB_01                        (1 << R_ADC12_ADCMPCR_CMPAB_SHIFT)  /* Output ADC12i_WCMPM (i = 0, 1) when window A EXOR window B comparison conditions are met. Otherwise, output ADC12i_WCMPUM (i = 0, 1). */
#  define R_ADC12_ADCMPCR_CMPAB_10                        (2 << R_ADC12_ADCMPCR_CMPAB_SHIFT)  /* Output ADC12i_WCMPM (i = 0, 1) when window A AND window B comparison conditions are met. Otherwise, output ADC12i_WCMPUM (i = 0, 1). */
#  define R_ADC12_ADCMPCR_CMPAB_11                        (3 << R_ADC12_ADCMPCR_CMPAB_SHIFT)  /* Setting prohibited. */

#define R_ADC12_ADCMPCR_CMPBE                     (1 << 9)  /* Compare Window B Operation Enable */

#define R_ADC12_ADCMPCR_CMPAE                     (1 << 11)  /* Compare Window A Operation Enable */

#define R_ADC12_ADCMPCR_CMPBIE                    (1 << 13)  /* Compare B Interrupt Enable */

#define R_ADC12_ADCMPCR_WCMPE                     (1 << 14)  /* Window Function Setting */

#define R_ADC12_ADCMPCR_CMPAIE                    (1 << 15)  /* Compare A Interrupt Enable */

/* ADCMPANSER Register bit definitions */
#define R_ADC12_ADCMPANSER_CMPTSA                 (1 << 0)  /* Temperature Sensor Output Compare Select */

#define R_ADC12_ADCMPANSER_CMPOCA                 (1 << 1)  /* Internal Reference Voltage Compare Select */

/* ADCMPLER Register bit definitions */
#define R_ADC12_ADCMPLER_CMPLTSA                  (1 << 0)  /* Compare Window A Temperature Sensor Output Comparison Condition Select */

#define R_ADC12_ADCMPLER_CMPLOCA                  (1 << 1)  /* Compare Window A Internal Reference Voltage Comparison Condition Select */

/* ADCMPANSR0 Register bit definitions */
#define R_ADC12_ADCMPANSR0_CMPCHA00               (1 << 0)  /* Compare Window A Channel Select */

#define R_ADC12_ADCMPANSR0_CMPCHA01               (1 << 1)  /* Compare Window A Channel Select */

#define R_ADC12_ADCMPANSR0_CMPCHA02               (1 << 2)  /* Compare Window A Channel Select */

#define R_ADC12_ADCMPANSR0_CMPCHA03               (1 << 3)  /* Compare Window A Channel Select */

#define R_ADC12_ADCMPANSR0_CMPCHA04               (1 << 4)  /* Compare Window A Channel Select */

#define R_ADC12_ADCMPANSR0_CMPCHA05               (1 << 5)  /* Compare Window A Channel Select */

#define R_ADC12_ADCMPANSR0_CMPCHA06               (1 << 6)  /* Compare Window A Channel Select */

#define R_ADC12_ADCMPANSR0_CMPCHA07               (1 << 7)  /* Compare Window A Channel Select */

#define R_ADC12_ADCMPANSR0_CMPCHA08               (1 << 8)  /* Compare Window A Channel Select */

#define R_ADC12_ADCMPANSR0_CMPCHA09               (1 << 9)  /* Compare Window A Channel Select */

#define R_ADC12_ADCMPANSR0_CMPCHA10               (1 << 10)  /* Compare Window A Channel Select */

#define R_ADC12_ADCMPANSR0_CMPCHA11               (1 << 11)  /* Compare Window A Channel Select */

#define R_ADC12_ADCMPANSR0_CMPCHA12               (1 << 12)  /* Compare Window A Channel Select */

#define R_ADC12_ADCMPANSR0_CMPCHA13               (1 << 13)  /* Compare Window A Channel Select */

#define R_ADC12_ADCMPANSR0_CMPCHA14               (1 << 14)  /* Compare Window A Channel Select */

#define R_ADC12_ADCMPANSR0_CMPCHA15               (1 << 15)  /* Compare Window A Channel Select */

/* ADCMPLR0 Register bit definitions */
#define R_ADC12_ADCMPLR0_CMPLCHA00                (1 << 0)  /* Compare Window A Comparison Condition Select */

#define R_ADC12_ADCMPLR0_CMPLCHA01                (1 << 1)  /* Compare Window A Comparison Condition Select */

#define R_ADC12_ADCMPLR0_CMPLCHA02                (1 << 2)  /* Compare Window A Comparison Condition Select */

#define R_ADC12_ADCMPLR0_CMPLCHA03                (1 << 3)  /* Compare Window A Comparison Condition Select */

#define R_ADC12_ADCMPLR0_CMPLCHA04                (1 << 4)  /* Compare Window A Comparison Condition Select */

#define R_ADC12_ADCMPLR0_CMPLCHA05                (1 << 5)  /* Compare Window A Comparison Condition Select */

#define R_ADC12_ADCMPLR0_CMPLCHA06                (1 << 6)  /* Compare Window A Comparison Condition Select */

#define R_ADC12_ADCMPLR0_CMPLCHA07                (1 << 7)  /* Compare Window A Comparison Condition Select */

#define R_ADC12_ADCMPLR0_CMPLCHA08                (1 << 8)  /* Compare Window A Comparison Condition Select */

#define R_ADC12_ADCMPLR0_CMPLCHA09                (1 << 9)  /* Compare Window A Comparison Condition Select */

#define R_ADC12_ADCMPLR0_CMPLCHA10                (1 << 10)  /* Compare Window A Comparison Condition Select */

#define R_ADC12_ADCMPLR0_CMPLCHA11                (1 << 11)  /* Compare Window A Comparison Condition Select */

#define R_ADC12_ADCMPLR0_CMPLCHA12                (1 << 12)  /* Compare Window A Comparison Condition Select */

#define R_ADC12_ADCMPLR0_CMPLCHA13                (1 << 13)  /* Compare Window A Comparison Condition Select */

#define R_ADC12_ADCMPLR0_CMPLCHA14                (1 << 14)  /* Compare Window A Comparison Condition Select */

#define R_ADC12_ADCMPLR0_CMPLCHA15                (1 << 15)  /* Compare Window A Comparison Condition Select */

/* ADCMPSR0 Register bit definitions */
#define R_ADC12_ADCMPSR0_CMPSTCHA00               (1 << 0)  /* Compare Window A Flag */

#define R_ADC12_ADCMPSR0_CMPSTCHA01               (1 << 1)  /* Compare Window A Flag */

#define R_ADC12_ADCMPSR0_CMPSTCHA02               (1 << 2)  /* Compare Window A Flag */

#define R_ADC12_ADCMPSR0_CMPSTCHA03               (1 << 3)  /* Compare Window A Flag */

#define R_ADC12_ADCMPSR0_CMPSTCHA04               (1 << 4)  /* Compare Window A Flag */

#define R_ADC12_ADCMPSR0_CMPSTCHA05               (1 << 5)  /* Compare Window A Flag */

#define R_ADC12_ADCMPSR0_CMPSTCHA06               (1 << 6)  /* Compare Window A Flag */

#define R_ADC12_ADCMPSR0_CMPSTCHA07               (1 << 7)  /* Compare Window A Flag */

#define R_ADC12_ADCMPSR0_CMPSTCHA08               (1 << 8)  /* Compare Window A Flag */

#define R_ADC12_ADCMPSR0_CMPSTCHA09               (1 << 9)  /* Compare Window A Flag */

#define R_ADC12_ADCMPSR0_CMPSTCHA10               (1 << 10)  /* Compare Window A Flag */

#define R_ADC12_ADCMPSR0_CMPSTCHA11               (1 << 11)  /* Compare Window A Flag */

#define R_ADC12_ADCMPSR0_CMPSTCHA12               (1 << 12)  /* Compare Window A Flag */

#define R_ADC12_ADCMPSR0_CMPSTCHA13               (1 << 13)  /* Compare Window A Flag */

#define R_ADC12_ADCMPSR0_CMPSTCHA14               (1 << 14)  /* Compare Window A Flag */

#define R_ADC12_ADCMPSR0_CMPSTCHA15               (1 << 15)  /* Compare Window A Flag */

/* ADCMPSER Register bit definitions */
#define R_ADC12_ADCMPSER_CMPSTTSA                 (1 << 0)  /* Compare Window A Temperature Sensor Output Compare Flag */

#define R_ADC12_ADCMPSER_CMPSTOCA                 (1 << 1)  /* Compare Window A Internal Reference Voltage Compare Flag */

/* ADCMPBNSR Register bit definitions */
#define R_ADC12_ADCMPBNSR_CMPCHB_SHIFT            (0)  /* Compare Window B Channel Select */
#define R_ADC12_ADCMPBNSR_CMPCHB_MASK             0x3f

#define R_ADC12_ADCMPBNSR_CMPLB                   (1 << 7)  /* Compare Window B Comparison Condition Setting */

/* ADCMPBSR Register bit definitions */
#define R_ADC12_ADCMPBSR_CMPSTB                   (1 << 0)  /* Compare Window B Flag */

/* ADBUF Register bit definitions */
#define R_ADC12_ADBUF_ADBUF_SHIFT                 (0)  /* Converted Value 15 to 0 */
#define R_ADC12_ADBUF_ADBUF_MASK                  0xffff

/* ADBUFEN Register bit definitions */
#define R_ADC12_ADBUFEN_BUFEN                     (1 << 0)  /* Data Buffer Enable */

/* ADBUFPTR Register bit definitions */
#define R_ADC12_ADBUFPTR_BUFPTR_SHIFT             (0)  /* Data Buffer Pointer */
#define R_ADC12_ADBUFPTR_BUFPTR_MASK              0xf

#define R_ADC12_ADBUFPTR_PTROVF                   (1 << 4)  /* Pointer Overflow Flag */

/* ADSSTRL Register bit definitions */
#define R_ADC12_ADSSTRL_SST_SHIFT                 (0)  /* Sampling Time Setting */
#define R_ADC12_ADSSTRL_SST_MASK                  0xff

/* ADSSTRT Register bit definitions */
#define R_ADC12_ADSSTRT_SST_SHIFT                 (0)  /* Sampling Time Setting */
#define R_ADC12_ADSSTRT_SST_MASK                  0xff

/* ADSSTRO Register bit definitions */
#define R_ADC12_ADSSTRO_SST_SHIFT                 (0)  /* Sampling Time Setting */
#define R_ADC12_ADSSTRO_SST_MASK                  0xff

/* ADSSTR Register bit definitions */
#define R_ADC12_ADSSTR_SST_SHIFT                  (0)  /* Sampling Time Setting */
#define R_ADC12_ADSSTR_SST_MASK                   0xff

/* ADSSTRV Register bit definitions */
#define R_ADC12_ADSSTRV_SST_SHIFT                 (0)  /* Sampling Time Setting */
#define R_ADC12_ADSSTRV_SST_MASK                  0xff

/* ADSSTR Register bit definitions */
#define R_ADC12_ADSSTR_SST_SHIFT                  (0)  /* Sampling Time Setting */
#define R_ADC12_ADSSTR_SST_MASK                   0xff


/* Maximum number of channels */

#define ADC12_MAX_CHANNELS    16

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_ADC12_H */

/****************************************************************************
 * arch/arm/src/ra8/hardware/ra_adc12.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA_ADC12_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA_ADC12_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ADC12 Base Address */
#ifndef RA_ADC12_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define RA_ADC12_BASE           0x40332000
#else
#define RA_ADC12_BASE           0x50332000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define RA_ADC12_CH_STRIDE    0x00000002
#define RA_ADC12_CH_BASE(ch)   (RA_ADC12_BASE + ((uint32_t)(ch) * RA_ADC12_CH_STRIDE))

/* ADC12 Register Offsets */

#define RA_ADC12_ADCSR_OFFSET     0x00000000  /* A/D Control Register */
#define RA_ADC12_ADANSA0_OFFSET     0x00000004  /* A/D Channel Select Register A0 */
#define RA_ADC12_ADANSA1_OFFSET     0x00000006  /* A/D Channel Select Register A1 */
#define RA_ADC12_ADADS0_OFFSET     0x00000008  /* A/D-Converted Value Addition/Average Channel Select Register 0 */
#define RA_ADC12_ADADS1_OFFSET     0x0000000a  /* A/D-Converted Value Addition/Average Channel Select Register 1 */
#define RA_ADC12_ADADC_OFFSET     0x0000000c  /* A/D-Converted Value Addition/Average Count Select Register */
#define RA_ADC12_ADCER_OFFSET     0x0000000e  /* A/D Control Extended Register */
#define RA_ADC12_ADSTRGR_OFFSET     0x00000010  /* A/D Conversion Start Trigger Select Register */
#define RA_ADC12_ADEXICR_OFFSET     0x00000012  /* A/D Conversion Extended Input Control Registers */
#define RA_ADC12_ADANSB0_OFFSET     0x00000014  /* A/D Channel Select Register B0 */
#define RA_ADC12_ADANSB1_OFFSET     0x00000016  /* A/D Channel Select Register B1 */
#define RA_ADC12_ADDBLDR_OFFSET     0x00000018  /* A/D Data Duplexing Register */
#define RA_ADC12_ADTSDR_OFFSET     0x0000001a  /* A/D Temperature Sensor Data Register */
#define RA_ADC12_ADOCDR_OFFSET     0x0000001c  /* A/D Internal Reference Voltage Data Register */
#define RA_ADC12_ADRD_OFFSET     0x0000001e  /* A/D Self-Diagnosis Data Register */
/* ADDR%s Registers (0-8) */
#define RA_ADC12_ADDR0_OFFSET     0x00000020  /* A/D Data Registers 0 */
#define RA_ADC12_ADDR1_OFFSET     0x00000022  /* A/D Data Registers 1 */
#define RA_ADC12_ADDR2_OFFSET     0x00000024  /* A/D Data Registers 2 */
#define RA_ADC12_ADDR3_OFFSET     0x00000026  /* A/D Data Registers 3 */
#define RA_ADC12_ADDR4_OFFSET     0x00000028  /* A/D Data Registers 4 */
#define RA_ADC12_ADDR5_OFFSET     0x0000002a  /* A/D Data Registers 5 */
#define RA_ADC12_ADDR6_OFFSET     0x0000002c  /* A/D Data Registers 6 */
#define RA_ADC12_ADDR7_OFFSET     0x0000002e  /* A/D Data Registers 7 */
#define RA_ADC12_ADDR8_OFFSET     0x00000030  /* A/D Data Registers 8 */
/* ADDR%s Registers (16-19) */
#define RA_ADC12_ADDR16_OFFSET     0x00000020  /* A/D Data Registers 16 */
#define RA_ADC12_ADDR17_OFFSET     0x00000022  /* A/D Data Registers 17 */
#define RA_ADC12_ADDR18_OFFSET     0x00000024  /* A/D Data Registers 18 */
#define RA_ADC12_ADDR19_OFFSET     0x00000026  /* A/D Data Registers 19 */
#define RA_ADC12_ADVMDR_OFFSET     0x00000026  /* A/D VBATT Monitor Data Register */
#define RA_ADC12_ADSHCR_OFFSET     0x00000066  /* A/D Sample and Hold Circuit Control Register */
#define RA_ADC12_ADDISCR_OFFSET     0x0000007a  /* A/D Disconnection Detection Control Register */
#define RA_ADC12_ADSHMSR_OFFSET     0x0000007c  /* A/D Sample and Hold Operation Mode Selection Register */
#define RA_ADC12_ADGSPCR_OFFSET     0x00000080  /* A/D Group Scan Priority Control Register */
#define RA_ADC12_ADDBLDRA_OFFSET     0x00000084  /* A/D Data Duplexing Register A */
#define RA_ADC12_ADDBLDRB_OFFSET     0x00000086  /* A/D Data Duplexing Register B */
#define RA_ADC12_ADWINMON_OFFSET     0x0000008c  /* A/D Compare Function Window A/B Status Monitor Register */
#define RA_ADC12_ADCMPCR_OFFSET     0x00000090  /* A/D Compare Function Control Register */
#define RA_ADC12_ADCMPANSER_OFFSET     0x00000092  /* A/D Compare Function Window A Extended Input Select Register */
#define RA_ADC12_ADCMPLER_OFFSET     0x00000093  /* A/D Compare Function Window A Extended Input Comparison Condition Setting Register */
#define RA_ADC12_ADCMPANSR0_OFFSET     0x00000094  /* A/D Compare Function Window A Channel Select Register 0 */
#define RA_ADC12_ADCMPLR0_OFFSET     0x00000098  /* A/D Compare Function Window A Comparison Condition Setting Register 0 */
/* ADCMPDR%s Registers (0-1) */
#define RA_ADC12_ADCMPDR0_OFFSET     0x0000009c  /* A/D Compare Function Window A Lower-Side/Upper-Side Level Setting Register */
#define RA_ADC12_ADCMPDR1_OFFSET     0x0000009e  /* A/D Compare Function Window A Lower-Side/Upper-Side Level Setting Register */
#define RA_ADC12_ADCMPSR0_OFFSET     0x000000a0  /* A/D Compare Function Window A Channel Status Register 0 */
#define RA_ADC12_ADCMPSER_OFFSET     0x000000a4  /* A/D Compare Function Window A Extended Input Channel Status Register */
#define RA_ADC12_ADCMPBNSR_OFFSET     0x000000a6  /* A/D Compare Function Window B Channel Select Register */
#define RA_ADC12_ADWINLLB_OFFSET     0x000000a8  /* A/D Compare Function Window B Lower-Side/Upper-Side Level Setting Register */
#define RA_ADC12_ADWINULB_OFFSET     0x000000aa  /* A/D Compare Function Window B Lower-Side/Upper-Side Level Setting Register */
#define RA_ADC12_ADCMPBSR_OFFSET     0x000000ac  /* A/D Compare Function Window B Status Register */
/* ADBUF%s Registers (0-15) */
#define RA_ADC12_ADBUF00_OFFSET     0x000000b0  /* A/D Data Buffer Registers 00 */
#define RA_ADC12_ADBUF01_OFFSET     0x000000b2  /* A/D Data Buffer Registers 01 */
#define RA_ADC12_ADBUF02_OFFSET     0x000000b4  /* A/D Data Buffer Registers 02 */
#define RA_ADC12_ADBUF03_OFFSET     0x000000b6  /* A/D Data Buffer Registers 03 */
#define RA_ADC12_ADBUF04_OFFSET     0x000000b8  /* A/D Data Buffer Registers 04 */
#define RA_ADC12_ADBUF05_OFFSET     0x000000ba  /* A/D Data Buffer Registers 05 */
#define RA_ADC12_ADBUF06_OFFSET     0x000000bc  /* A/D Data Buffer Registers 06 */
#define RA_ADC12_ADBUF07_OFFSET     0x000000be  /* A/D Data Buffer Registers 07 */
#define RA_ADC12_ADBUF08_OFFSET     0x000000c0  /* A/D Data Buffer Registers 08 */
#define RA_ADC12_ADBUF09_OFFSET     0x000000c2  /* A/D Data Buffer Registers 09 */
#define RA_ADC12_ADBUF10_OFFSET     0x000000c4  /* A/D Data Buffer Registers 10 */
#define RA_ADC12_ADBUF11_OFFSET     0x000000c6  /* A/D Data Buffer Registers 11 */
#define RA_ADC12_ADBUF12_OFFSET     0x000000c8  /* A/D Data Buffer Registers 12 */
#define RA_ADC12_ADBUF13_OFFSET     0x000000ca  /* A/D Data Buffer Registers 13 */
#define RA_ADC12_ADBUF14_OFFSET     0x000000cc  /* A/D Data Buffer Registers 14 */
#define RA_ADC12_ADBUF15_OFFSET     0x000000ce  /* A/D Data Buffer Registers 15 */
#define RA_ADC12_ADBUFEN_OFFSET     0x000000d0  /* A/D Data Buffer Enable Register */
#define RA_ADC12_ADBUFPTR_OFFSET     0x000000d2  /* A/D Data Buffer Pointer Register */
#define RA_ADC12_ADSSTRL_OFFSET     0x000000dd  /* A/D Sampling State Register */
#define RA_ADC12_ADSSTRT_OFFSET     0x000000de  /* A/D Sampling State Register */
#define RA_ADC12_ADSSTRO_OFFSET     0x000000df  /* A/D Sampling State Register */
/* ADSSTR%s Registers (0-8) */
#define RA_ADC12_ADSSTR0_OFFSET     0x000000e0  /* A/D Sampling State Register */
#define RA_ADC12_ADSSTR1_OFFSET     0x000000e1  /* A/D Sampling State Register */
#define RA_ADC12_ADSSTR2_OFFSET     0x000000e2  /* A/D Sampling State Register */
#define RA_ADC12_ADSSTR3_OFFSET     0x000000e3  /* A/D Sampling State Register */
#define RA_ADC12_ADSSTR4_OFFSET     0x000000e4  /* A/D Sampling State Register */
#define RA_ADC12_ADSSTR5_OFFSET     0x000000e5  /* A/D Sampling State Register */
#define RA_ADC12_ADSSTR6_OFFSET     0x000000e6  /* A/D Sampling State Register */
#define RA_ADC12_ADSSTR7_OFFSET     0x000000e7  /* A/D Sampling State Register */
#define RA_ADC12_ADSSTR8_OFFSET     0x000000e8  /* A/D Sampling State Register */
#define RA_ADC12_ADSSTRV_OFFSET     0x000000e3  /* A/D Sampling State Register */
/* ADSSTR%s Registers (16-19) */
#define RA_ADC12_ADSSTR16_OFFSET     0x000000ec  /* A/D Sampling State Register */
#define RA_ADC12_ADSSTR17_OFFSET     0x000000ed  /* A/D Sampling State Register */
#define RA_ADC12_ADSSTR18_OFFSET     0x000000ee  /* A/D Sampling State Register */
#define RA_ADC12_ADSSTR19_OFFSET     0x000000ef  /* A/D Sampling State Register */

/* Register bit definitions */
/* ADCSR Register bit definitions */
#define ADC12_ADCSR_DBLANS_SHIFT    (0)       /* Double Trigger Channel Select */
#define ADC12_ADCSR_DBLANS_MASK     (0x1f)

#define ADC12_ADCSR_GBADIE          (1 << 6)  /* Group B Scan End Interrupt and ELC Event Enable */

#define ADC12_ADCSR_DBLE          (1 << 7)  /* Double Trigger Mode Select */

#define ADC12_ADCSR_EXTRG          (1 << 8)  /* Trigger Select */

#define ADC12_ADCSR_TRGE          (1 << 9)  /* Trigger Start Enable */

#define ADC12_ADCSR_ADCS_SHIFT    (13)       /* Scan Mode Select */
#define ADC12_ADCSR_ADCS_MASK     (0x6000)
#  define ADC12_ADCSR_ADCS_00          (0 << ADC12_ADCSR_ADCS_SHIFT)  /* Single scan mode */
#  define ADC12_ADCSR_ADCS_01          (1 << ADC12_ADCSR_ADCS_SHIFT)  /* Group scan mode */
#  define ADC12_ADCSR_ADCS_10          (10 << ADC12_ADCSR_ADCS_SHIFT)  /* Continuous scan mode */
#  define ADC12_ADCSR_ADCS_11          (11 << ADC12_ADCSR_ADCS_SHIFT)  /* Setting prohibited */

#define ADC12_ADCSR_ADST          (1 << 15)  /* A/D Conversion Start */

/* ADANSA Register bit definitions */
#define ADC12_ADANSA_ANSA00          (1 << 0)  /* A/D Conversion Channels Select */

#define ADC12_ADANSA_ANSA01          (1 << 1)  /* A/D Conversion Channels Select */

#define ADC12_ADANSA_ANSA02          (1 << 2)  /* A/D Conversion Channels Select */

#define ADC12_ADANSA_ANSA03          (1 << 3)  /* A/D Conversion Channels Select */

#define ADC12_ADANSA_ANSA04          (1 << 4)  /* A/D Conversion Channels Select */

#define ADC12_ADANSA_ANSA05          (1 << 5)  /* A/D Conversion Channels Select */

#define ADC12_ADANSA_ANSA06          (1 << 6)  /* A/D Conversion Channels Select */

#define ADC12_ADANSA_ANSA07          (1 << 7)  /* A/D Conversion Channels Select */

#define ADC12_ADANSA_ANSA08          (1 << 8)  /* A/D Conversion Channels Select */

/* ADANSA Register bit definitions */
#define ADC12_ADANSA_ANSA16          (1 << 0)  /* A/D Conversion Channels Select */

#define ADC12_ADANSA_ANSA17          (1 << 1)  /* A/D Conversion Channels Select */

#define ADC12_ADANSA_ANSA18          (1 << 2)  /* A/D Conversion Channels Select */

#define ADC12_ADANSA_ANSA19          (1 << 3)  /* A/D Conversion Channels Select */

#define ADC12_ADANSA_ANSA20          (1 << 4)  /* A/D Conversion Channels Select */

#define ADC12_ADANSA_ANSA21          (1 << 5)  /* A/D Conversion Channels Select */

#define ADC12_ADANSA_ANSA22          (1 << 6)  /* A/D Conversion Channels Select */

/* ADADS Register bit definitions */
#define ADC12_ADADS_ADS00          (1 << 0)  /* A/D-Converted Value Addition/Average Channel Select */

#define ADC12_ADADS_ADS01          (1 << 1)  /* A/D-Converted Value Addition/Average Channel Select */

#define ADC12_ADADS_ADS02          (1 << 2)  /* A/D-Converted Value Addition/Average Channel Select */

#define ADC12_ADADS_ADS03          (1 << 3)  /* A/D-Converted Value Addition/Average Channel Select */

#define ADC12_ADADS_ADS04          (1 << 4)  /* A/D-Converted Value Addition/Average Channel Select */

#define ADC12_ADADS_ADS05          (1 << 5)  /* A/D-Converted Value Addition/Average Channel Select */

#define ADC12_ADADS_ADS06          (1 << 6)  /* A/D-Converted Value Addition/Average Channel Select */

#define ADC12_ADADS_ADS07          (1 << 7)  /* A/D-Converted Value Addition/Average Channel Select */

#define ADC12_ADADS_ADS08          (1 << 8)  /* A/D-Converted Value Addition/Average Channel Select */

/* ADADS Register bit definitions */
#define ADC12_ADADS_ADS16          (1 << 0)  /* A/D Conversion Channels Select/Average Channel Select */

#define ADC12_ADADS_ADS17          (1 << 1)  /* A/D Conversion Channels Select/Average Channel Select */

#define ADC12_ADADS_ADS18          (1 << 2)  /* A/D Conversion Channels Select/Average Channel Select */

#define ADC12_ADADS_ADS19          (1 << 3)  /* A/D Conversion Channels Select/Average Channel Select */

#define ADC12_ADADS_ADS20          (1 << 4)  /* A/D Conversion Channels Select/Average Channel Select */

#define ADC12_ADADS_ADS21          (1 << 5)  /* A/D Conversion Channels Select/Average Channel Select */

#define ADC12_ADADS_ADS22          (1 << 6)  /* A/D Conversion Channels Select/Average Channel Select */

/* ADADC Register bit definitions */
#define ADC12_ADADC_ADC_SHIFT    (0)       /* Addition/Average Count Select */
#define ADC12_ADADC_ADC_MASK     (0x7)
#  define ADC12_ADADC_ADC_000          (0 << ADC12_ADADC_ADC_SHIFT)  /* 1-time conversion (no addition, same as normal conversion) */
#  define ADC12_ADADC_ADC_001          (1 << ADC12_ADADC_ADC_SHIFT)  /* 2-time conversion (1 addition) */
#  define ADC12_ADADC_ADC_010          (10 << ADC12_ADADC_ADC_SHIFT)  /* 3-time conversion (2 additions) */
#  define ADC12_ADADC_ADC_011          (11 << ADC12_ADADC_ADC_SHIFT)  /* 4-time conversion (3 additions) */
#  define ADC12_ADADC_ADC_101          (101 << ADC12_ADADC_ADC_SHIFT)  /* 16-time conversion (15 additions) */

#define ADC12_ADADC_AVEE          (1 << 7)  /* Average Mode Select */

/* ADCER Register bit definitions */
#define ADC12_ADCER_ADPRC_SHIFT    (1)       /*  */
#define ADC12_ADCER_ADPRC_MASK     (0x6)
#  define ADC12_ADCER_ADPRC_00          (0 << ADC12_ADCER_ADPRC_SHIFT)  /* 12-bit accuracy */
#  define ADC12_ADCER_ADPRC_01          (1 << ADC12_ADCER_ADPRC_SHIFT)  /* 10-bit accuracy */
#  define ADC12_ADCER_ADPRC_10          (10 << ADC12_ADCER_ADPRC_SHIFT)  /* 8-bit accuracy */
#  define ADC12_ADCER_ADPRC_11          (11 << ADC12_ADCER_ADPRC_SHIFT)  /* Setting prohibited */

#define ADC12_ADCER_ACE          (1 << 5)  /* A/D Data Register Automatic Clearing Enable */

#define ADC12_ADCER_DIAGVAL_SHIFT    (8)       /* Self-Diagnosis Conversion Voltage Select */
#define ADC12_ADCER_DIAGVAL_MASK     (0x300)
#  define ADC12_ADCER_DIAGVAL_00          (0 << ADC12_ADCER_DIAGVAL_SHIFT)  /* Setting prohibited when self-diagnosis is enabled */
#  define ADC12_ADCER_DIAGVAL_01          (1 << ADC12_ADCER_DIAGVAL_SHIFT)  /* 0 volts */
#  define ADC12_ADCER_DIAGVAL_10          (10 << ADC12_ADCER_DIAGVAL_SHIFT)  /* Reference voltage × 1/2 */
#  define ADC12_ADCER_DIAGVAL_11          (11 << ADC12_ADCER_DIAGVAL_SHIFT)  /* Reference voltage */

#define ADC12_ADCER_DIAGLD          (1 << 10)  /* Self-Diagnosis Mode Select */

#define ADC12_ADCER_DIAGM          (1 << 11)  /* Self-Diagnosis Enable */

#define ADC12_ADCER_ADRFMT          (1 << 15)  /* A/D Data Register Format Select */

/* ADSTRGR Register bit definitions */
#define ADC12_ADSTRGR_TRSB_SHIFT    (0)       /* A/D Conversion Start Trigger Select for Group B */
#define ADC12_ADSTRGR_TRSB_MASK     (0x3f)

#define ADC12_ADSTRGR_TRSA_SHIFT    (8)       /* A/D Conversion Start Trigger Select */
#define ADC12_ADSTRGR_TRSA_MASK     (0x3f00)

/* ADEXICR Register bit definitions */
#define ADC12_ADEXICR_TSSAD          (1 << 0)  /* Temperature Sensor Output A/D-Converted Value Addition/Average Mode Select */

#define ADC12_ADEXICR_OCSAD          (1 << 1)  /* Internal Reference Voltage A/D-Converted Value Addition/Average Mode Select */

#define ADC12_ADEXICR_TSSA          (1 << 8)  /* Temperature Sensor Output A/D Conversion Select */

#define ADC12_ADEXICR_OCSA          (1 << 9)  /* Internal Reference Voltage A/D Conversion Select */

#define ADC12_ADEXICR_TSSB          (1 << 10)  /* Temperature Sensor Output A/D Conversion Select for Group B */

#define ADC12_ADEXICR_OCSB          (1 << 11)  /* Internal Reference Voltage A/D Conversion Select for Group B */

/* ADANSB Register bit definitions */
#define ADC12_ADANSB_ANSB00          (1 << 0)  /* A/D Conversion Channels Select */

#define ADC12_ADANSB_ANSB01          (1 << 1)  /* A/D Conversion Channels Select */

#define ADC12_ADANSB_ANSB02          (1 << 2)  /* A/D Conversion Channels Select */

#define ADC12_ADANSB_ANSB03          (1 << 3)  /* A/D Conversion Channels Select */

#define ADC12_ADANSB_ANSB04          (1 << 4)  /* A/D Conversion Channels Select */

#define ADC12_ADANSB_ANSB05          (1 << 5)  /* A/D Conversion Channels Select */

#define ADC12_ADANSB_ANSB06          (1 << 6)  /* A/D Conversion Channels Select */

#define ADC12_ADANSB_ANSB07          (1 << 7)  /* A/D Conversion Channels Select */

#define ADC12_ADANSB_ANSB08          (1 << 8)  /* A/D Conversion Channels Select */

/* ADANSB Register bit definitions */
#define ADC12_ADANSB_ANSB16          (1 << 0)  /* A/D Conversion Channels Select */

#define ADC12_ADANSB_ANSB17          (1 << 1)  /* A/D Conversion Channels Select */

#define ADC12_ADANSB_ANSB18          (1 << 2)  /* A/D Conversion Channels Select */

#define ADC12_ADANSB_ANSB19          (1 << 3)  /* A/D Conversion Channels Select */

#define ADC12_ADANSB_ANSB20          (1 << 4)  /* A/D Conversion Channels Select */

#define ADC12_ADANSB_ANSB21          (1 << 5)  /* A/D Conversion Channels Select */

#define ADC12_ADANSB_ANSB22          (1 << 6)  /* A/D Conversion Channels Select */

/* ADDBLDR Register bit definitions */
#define ADC12_ADDBLDR_ADDBLDR_SHIFT    (0)       /* Converted Value 15 to 0 */
#define ADC12_ADDBLDR_ADDBLDR_MASK     (0xffff)

/* ADTSDR Register bit definitions */
#define ADC12_ADTSDR_ADTSDR_SHIFT    (0)       /* Converted Value 15 to 0 */
#define ADC12_ADTSDR_ADTSDR_MASK     (0xffff)

/* ADOCDR Register bit definitions */
#define ADC12_ADOCDR_ADOCDR_SHIFT    (0)       /* Converted Value 15 to 0 */
#define ADC12_ADOCDR_ADOCDR_MASK     (0xffff)

/* ADRD Register bit definitions */
#define ADC12_ADRD_AD_SHIFT    (0)       /* Converted Value 11 to 0 */
#define ADC12_ADRD_AD_MASK     (0xfff)

#define ADC12_ADRD_DIAGST_SHIFT    (14)       /* Self-Diagnosis Status */
#define ADC12_ADRD_DIAGST_MASK     (0xc000)
#  define ADC12_ADRD_DIAGST_00          (0 << ADC12_ADRD_DIAGST_SHIFT)  /* Self-diagnosis not executed after power-on. */
#  define ADC12_ADRD_DIAGST_01          (1 << ADC12_ADRD_DIAGST_SHIFT)  /* Self-diagnosis was executed using the 0 V voltage. */
#  define ADC12_ADRD_DIAGST_10          (10 << ADC12_ADRD_DIAGST_SHIFT)  /* Self-diagnosis was executed using the reference voltage × 1/2. */
#  define ADC12_ADRD_DIAGST_11          (11 << ADC12_ADRD_DIAGST_SHIFT)  /* Self-diagnosis was executed using the reference voltage . */

/* ADDR Register bit definitions */
#define ADC12_ADDR_ADDR_SHIFT    (0)       /* Converted Value 15 to 0 */
#define ADC12_ADDR_ADDR_MASK     (0xffff)

/* ADDR Register bit definitions */
#define ADC12_ADDR_ADDR_SHIFT    (0)       /* Converted Value 15 to 0 */
#define ADC12_ADDR_ADDR_MASK     (0xffff)

/* ADVMDR Register bit definitions */
#define ADC12_ADVMDR_ADDR_SHIFT    (0)       /* Converted Value 15 to 0 */
#define ADC12_ADVMDR_ADDR_MASK     (0xffff)

/* ADSHCR Register bit definitions */
#define ADC12_ADSHCR_SSTSH_SHIFT    (0)       /* Channel-Dedicated Sample-and-Hold Circuit Sampling Time Setting */
#define ADC12_ADSHCR_SSTSH_MASK     (0xff)

#define ADC12_ADSHCR_SHANS_SHIFT    (8)       /* Channel-Dedicated Sample-and-Hold Circuit Bypass Select */
#define ADC12_ADSHCR_SHANS_MASK     (0x300)
#  define ADC12_ADSHCR_SHANS_0          (0 << ADC12_ADSHCR_SHANS_SHIFT)  /* Bypass the circuits */
#  define ADC12_ADSHCR_SHANS_1          (1 << ADC12_ADSHCR_SHANS_SHIFT)  /* Use the circuits */

/* ADDISCR Register bit definitions */
#define ADC12_ADDISCR_ADNDIS_SHIFT    (0)       /* Disconnection Detection Assist Setting */
#define ADC12_ADDISCR_ADNDIS_MASK     (0xf)
#  define ADC12_ADDISCR_ADNDIS_0X0          (0 << ADC12_ADDISCR_ADNDIS_SHIFT)  /* The disconnection detection assist function is disabled */
#  define ADC12_ADDISCR_ADNDIS_0X1          (0 << ADC12_ADDISCR_ADNDIS_SHIFT)  /* Setting prohibited */

#define ADC12_ADDISCR_PCHG          (1 << 4)  /* Precharge/discharge select */

/* ADSHMSR Register bit definitions */
#define ADC12_ADSHMSR_SHMD          (1 << 0)  /* Sampling Operation Selection */

/* ADGSPCR Register bit definitions */
#define ADC12_ADGSPCR_PGS          (1 << 0)  /* Group Priority Operation Setting */

#define ADC12_ADGSPCR_GBRSCN          (1 << 1)  /* Lower-Priority Group Restart Setting */

#define ADC12_ADGSPCR_LGRRS          (1 << 14)  /* Enabled only when PGS = 1 and GBRSCN = 1. */

#define ADC12_ADGSPCR_GBRP          (1 << 15)  /* Single Scan Continuous Start */

/* ADDBLDRA Register bit definitions */
#define ADC12_ADDBLDRA_ADDBLDR_SHIFT    (0)       /* Converted Value 15 to 0 */
#define ADC12_ADDBLDRA_ADDBLDR_MASK     (0xffff)

/* ADDBLDRB Register bit definitions */
#define ADC12_ADDBLDRB_ADDBLDR_SHIFT    (0)       /* Converted Value 15 to 0 */
#define ADC12_ADDBLDRB_ADDBLDR_MASK     (0xffff)

/* ADWINMON Register bit definitions */
#define ADC12_ADWINMON_MONCOMB          (1 << 0)  /* Combination Result Monitor */

#define ADC12_ADWINMON_MONCMPA          (1 << 4)  /* Comparison Result Monitor A */

#define ADC12_ADWINMON_MONCMPB          (1 << 5)  /* Comparison Result Monitor B */

/* ADCMPCR Register bit definitions */
#define ADC12_ADCMPCR_CMPAB_SHIFT    (0)       /* Window A/B Composite Conditions Setting */
#define ADC12_ADCMPCR_CMPAB_MASK     (0x3)
#  define ADC12_ADCMPCR_CMPAB_00          (0 << ADC12_ADCMPCR_CMPAB_SHIFT)  /* Output ADC12i_WCMPM (i = 0, 1) when window A OR window B comparison conditions are met. Otherwise, output ADC12i_WCMPUM (i = 0, 1). */
#  define ADC12_ADCMPCR_CMPAB_01          (1 << ADC12_ADCMPCR_CMPAB_SHIFT)  /* Output ADC12i_WCMPM (i = 0, 1) when window A EXOR window B comparison conditions are met. Otherwise, output ADC12i_WCMPUM (i = 0, 1). */
#  define ADC12_ADCMPCR_CMPAB_10          (10 << ADC12_ADCMPCR_CMPAB_SHIFT)  /* Output ADC12i_WCMPM (i = 0, 1) when window A AND window B comparison conditions are met. Otherwise, output ADC12i_WCMPUM (i = 0, 1). */
#  define ADC12_ADCMPCR_CMPAB_11          (11 << ADC12_ADCMPCR_CMPAB_SHIFT)  /* Setting prohibited. */

#define ADC12_ADCMPCR_CMPBE          (1 << 9)  /* Compare Window B Operation Enable */

#define ADC12_ADCMPCR_CMPAE          (1 << 11)  /* Compare Window A Operation Enable */

#define ADC12_ADCMPCR_CMPBIE          (1 << 13)  /* Compare B Interrupt Enable */

#define ADC12_ADCMPCR_WCMPE          (1 << 14)  /* Window Function Setting */

#define ADC12_ADCMPCR_CMPAIE          (1 << 15)  /* Compare A Interrupt Enable */

/* ADCMPANSER Register bit definitions */
#define ADC12_ADCMPANSER_CMPTSA          (1 << 0)  /* Temperature Sensor Output Compare Select */

#define ADC12_ADCMPANSER_CMPOCA          (1 << 1)  /* Internal Reference Voltage Compare Select */

/* ADCMPLER Register bit definitions */
#define ADC12_ADCMPLER_CMPLTSA          (1 << 0)  /* Compare Window A Temperature Sensor Output Comparison Condition Select */

#define ADC12_ADCMPLER_CMPLOCA          (1 << 1)  /* Compare Window A Internal Reference Voltage Comparison Condition Select */

/* ADCMPANSR Register bit definitions */
#define ADC12_ADCMPANSR_CMPCHA00          (1 << 0)  /* Compare Window A Channel Select */

#define ADC12_ADCMPANSR_CMPCHA01          (1 << 1)  /* Compare Window A Channel Select */

#define ADC12_ADCMPANSR_CMPCHA02          (1 << 2)  /* Compare Window A Channel Select */

#define ADC12_ADCMPANSR_CMPCHA03          (1 << 3)  /* Compare Window A Channel Select */

#define ADC12_ADCMPANSR_CMPCHA04          (1 << 4)  /* Compare Window A Channel Select */

#define ADC12_ADCMPANSR_CMPCHA05          (1 << 5)  /* Compare Window A Channel Select */

#define ADC12_ADCMPANSR_CMPCHA06          (1 << 6)  /* Compare Window A Channel Select */

#define ADC12_ADCMPANSR_CMPCHA07          (1 << 7)  /* Compare Window A Channel Select */

#define ADC12_ADCMPANSR_CMPCHA08          (1 << 8)  /* Compare Window A Channel Select */

#define ADC12_ADCMPANSR_CMPCHA09          (1 << 9)  /* Compare Window A Channel Select */

#define ADC12_ADCMPANSR_CMPCHA10          (1 << 10)  /* Compare Window A Channel Select */

#define ADC12_ADCMPANSR_CMPCHA11          (1 << 11)  /* Compare Window A Channel Select */

#define ADC12_ADCMPANSR_CMPCHA12          (1 << 12)  /* Compare Window A Channel Select */

#define ADC12_ADCMPANSR_CMPCHA13          (1 << 13)  /* Compare Window A Channel Select */

#define ADC12_ADCMPANSR_CMPCHA14          (1 << 14)  /* Compare Window A Channel Select */

#define ADC12_ADCMPANSR_CMPCHA15          (1 << 15)  /* Compare Window A Channel Select */

/* ADCMPLR Register bit definitions */
#define ADC12_ADCMPLR_CMPLCHA00          (1 << 0)  /* Compare Window A Comparison Condition Select */

#define ADC12_ADCMPLR_CMPLCHA01          (1 << 1)  /* Compare Window A Comparison Condition Select */

#define ADC12_ADCMPLR_CMPLCHA02          (1 << 2)  /* Compare Window A Comparison Condition Select */

#define ADC12_ADCMPLR_CMPLCHA03          (1 << 3)  /* Compare Window A Comparison Condition Select */

#define ADC12_ADCMPLR_CMPLCHA04          (1 << 4)  /* Compare Window A Comparison Condition Select */

#define ADC12_ADCMPLR_CMPLCHA05          (1 << 5)  /* Compare Window A Comparison Condition Select */

#define ADC12_ADCMPLR_CMPLCHA06          (1 << 6)  /* Compare Window A Comparison Condition Select */

#define ADC12_ADCMPLR_CMPLCHA07          (1 << 7)  /* Compare Window A Comparison Condition Select */

#define ADC12_ADCMPLR_CMPLCHA08          (1 << 8)  /* Compare Window A Comparison Condition Select */

#define ADC12_ADCMPLR_CMPLCHA09          (1 << 9)  /* Compare Window A Comparison Condition Select */

#define ADC12_ADCMPLR_CMPLCHA10          (1 << 10)  /* Compare Window A Comparison Condition Select */

#define ADC12_ADCMPLR_CMPLCHA11          (1 << 11)  /* Compare Window A Comparison Condition Select */

#define ADC12_ADCMPLR_CMPLCHA12          (1 << 12)  /* Compare Window A Comparison Condition Select */

#define ADC12_ADCMPLR_CMPLCHA13          (1 << 13)  /* Compare Window A Comparison Condition Select */

#define ADC12_ADCMPLR_CMPLCHA14          (1 << 14)  /* Compare Window A Comparison Condition Select */

#define ADC12_ADCMPLR_CMPLCHA15          (1 << 15)  /* Compare Window A Comparison Condition Select */

/* ADCMPSR Register bit definitions */
#define ADC12_ADCMPSR_CMPSTCHA00          (1 << 0)  /* Compare Window A Flag */

#define ADC12_ADCMPSR_CMPSTCHA01          (1 << 1)  /* Compare Window A Flag */

#define ADC12_ADCMPSR_CMPSTCHA02          (1 << 2)  /* Compare Window A Flag */

#define ADC12_ADCMPSR_CMPSTCHA03          (1 << 3)  /* Compare Window A Flag */

#define ADC12_ADCMPSR_CMPSTCHA04          (1 << 4)  /* Compare Window A Flag */

#define ADC12_ADCMPSR_CMPSTCHA05          (1 << 5)  /* Compare Window A Flag */

#define ADC12_ADCMPSR_CMPSTCHA06          (1 << 6)  /* Compare Window A Flag */

#define ADC12_ADCMPSR_CMPSTCHA07          (1 << 7)  /* Compare Window A Flag */

#define ADC12_ADCMPSR_CMPSTCHA08          (1 << 8)  /* Compare Window A Flag */

#define ADC12_ADCMPSR_CMPSTCHA09          (1 << 9)  /* Compare Window A Flag */

#define ADC12_ADCMPSR_CMPSTCHA10          (1 << 10)  /* Compare Window A Flag */

#define ADC12_ADCMPSR_CMPSTCHA11          (1 << 11)  /* Compare Window A Flag */

#define ADC12_ADCMPSR_CMPSTCHA12          (1 << 12)  /* Compare Window A Flag */

#define ADC12_ADCMPSR_CMPSTCHA13          (1 << 13)  /* Compare Window A Flag */

#define ADC12_ADCMPSR_CMPSTCHA14          (1 << 14)  /* Compare Window A Flag */

#define ADC12_ADCMPSR_CMPSTCHA15          (1 << 15)  /* Compare Window A Flag */

/* ADCMPSER Register bit definitions */
#define ADC12_ADCMPSER_CMPSTTSA          (1 << 0)  /* Compare Window A Temperature Sensor Output Compare Flag */

#define ADC12_ADCMPSER_CMPSTOCA          (1 << 1)  /* Compare Window A Internal Reference Voltage Compare Flag */

/* ADCMPBNSR Register bit definitions */
#define ADC12_ADCMPBNSR_CMPCHB_SHIFT    (0)       /* Compare Window B Channel Select */
#define ADC12_ADCMPBNSR_CMPCHB_MASK     (0x3f)

#define ADC12_ADCMPBNSR_CMPLB          (1 << 7)  /* Compare Window B Comparison Condition Setting */

/* ADCMPBSR Register bit definitions */
#define ADC12_ADCMPBSR_CMPSTB          (1 << 0)  /* Compare Window B Flag */

/* ADBUF Register bit definitions */
#define ADC12_ADBUF_ADBUF_SHIFT    (0)       /* Converted Value 15 to 0 */
#define ADC12_ADBUF_ADBUF_MASK     (0xffff)

/* ADBUFEN Register bit definitions */
#define ADC12_ADBUFEN_BUFEN          (1 << 0)  /* Data Buffer Enable */

/* ADBUFPTR Register bit definitions */
#define ADC12_ADBUFPTR_BUFPTR_SHIFT    (0)       /* Data Buffer Pointer */
#define ADC12_ADBUFPTR_BUFPTR_MASK     (0xf)

#define ADC12_ADBUFPTR_PTROVF          (1 << 4)  /* Pointer Overflow Flag */

/* ADSSTRL Register bit definitions */
#define ADC12_ADSSTRL_SST_SHIFT    (0)       /* Sampling Time Setting */
#define ADC12_ADSSTRL_SST_MASK     (0xff)

/* ADSSTRT Register bit definitions */
#define ADC12_ADSSTRT_SST_SHIFT    (0)       /* Sampling Time Setting */
#define ADC12_ADSSTRT_SST_MASK     (0xff)

/* ADSSTRO Register bit definitions */
#define ADC12_ADSSTRO_SST_SHIFT    (0)       /* Sampling Time Setting */
#define ADC12_ADSSTRO_SST_MASK     (0xff)

/* ADSSTR Register bit definitions */
#define ADC12_ADSSTR_SST_SHIFT    (0)       /* Sampling Time Setting */
#define ADC12_ADSSTR_SST_MASK     (0xff)

/* ADSSTRV Register bit definitions */
#define ADC12_ADSSTRV_SST_SHIFT    (0)       /* Sampling Time Setting */
#define ADC12_ADSSTRV_SST_MASK     (0xff)

/* ADSSTR Register bit definitions */
#define ADC12_ADSSTR_SST_SHIFT    (0)       /* Sampling Time Setting */
#define ADC12_ADSSTR_SST_MASK     (0xff)


/* Maximum number of channels */

#define ADC12_MAX_CHANNELS    16

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA_ADC12_H */

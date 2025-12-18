/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_adc_e.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_ADC_E_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_ADC_E_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ADC_E Base Addresses **************************************************/

#ifndef RZV_ADC_E0_BASE
#  define RZV_ADC_E0_BASE             0x11C00000
#endif
#ifndef RZV_ADC_E_BASE
#  define RZV_ADC_E_BASE              RZV_ADC_E0_BASE
#endif

/* ADC_E Register Offsets *************************************************/

/* ADCMPDR%s Registers (0-1) */
#define RZV_ADC_E_ADCMPDR_OFFSET(m)             (0x0000009c + ((m) * 0x00000002))  /* ADCMPDR Register %s */
/* ADDR%s Registers (0-7) */
#define RZV_ADC_E_ADDR_OFFSET(m)                (0x00000020 + ((m) * 0x00000002))  /* ADDR Register %s */
#define RZV_ADC_E_ADCSR_OFFSET                           0x0000  /* A/D Control/Status Register */
#define RZV_ADC_E_ADREF_OFFSET                           0x0002  /* A/D Reference Flag Register */
#define RZV_ADC_E_ADANSA0_OFFSET                         0x0004  /* A/D Channel Select Register A0 */
#define RZV_ADC_E_ADADS0_OFFSET                          0x0008  /* A/D-converted Value Addition/Average Channel Select Register 0 */
#define RZV_ADC_E_ADADC_OFFSET                           0x000C  /* A/D-converted Value Addition/Average Count Select Register */
#define RZV_ADC_E_ADCER_OFFSET                           0x000E  /* A/D Control Extended Register */
#define RZV_ADC_E_ADSTRGR_OFFSET                         0x0010  /* A/D Conversion Start Trigger Register */
#define RZV_ADC_E_ADANSB0_OFFSET                         0x0014  /* A/D Channel Select Register B0 */
#define RZV_ADC_E_ADDBLDR_OFFSET                         0x0018  /* A/D Data Duplication Register */
#define RZV_ADC_E_ADELCCR_OFFSET                         0x007D  /* A/D Event Link Control Register */
#define RZV_ADC_E_ADGSPCR_OFFSET                         0x0080  /* A/D Group Scan Priority Control Register */
#define RZV_ADC_E_ADDBLDRA_OFFSET                        0x0084  /* A/D Data Duplication Register A */
#define RZV_ADC_E_ADDBLDRB_OFFSET                        0x0086  /* A/D Data Duplication Register B */
#define RZV_ADC_E_ADWINMON_OFFSET                        0x008C  /* A/D Compare Function Window A/B Status Monitor Register */
#define RZV_ADC_E_ADCMPCR_OFFSET                         0x0090  /* A/D Compare Function Control Register */
#define RZV_ADC_E_ADCMPANSR0_OFFSET                      0x0094  /* A/D Compare Function Window A Channel Select Register 0 */
#define RZV_ADC_E_ADCMPLR0_OFFSET                        0x0098  /* A/D Compare Function Window A Extended Input Select Register */
#define RZV_ADC_E_ADCMPSR0_OFFSET                        0x00A0  /* A/D Compare Function Window A Channel Status Register 0 */
#define RZV_ADC_E_ADCMPBNSR_OFFSET                       0x00A6  /* ADCMPBNSR */
#define RZV_ADC_E_ADWINLLB_OFFSET                        0x00A8  /* ADWINLLB */
#define RZV_ADC_E_ADWINULB_OFFSET                        0x00AA  /* ADWINULB */
#define RZV_ADC_E_ADCMPBSR_OFFSET                        0x00AC  /* ADCMPBSR */
#define RZV_ADC_E_ADANSC0_OFFSET                         0x00D4  /* ADANSC0 */
#define RZV_ADC_E_ADGCTRGR_OFFSET                        0x00D9  /* ADGCTRGR */
#define RZV_ADC_E_ADERCR_OFFSET                          0x01E2  /* ADERCR */
#define RZV_ADC_E_ADERCLR_OFFSET                         0x01E3  /* ADERCLR */
#define RZV_ADC_E_ADOWER_OFFSET                          0x01E8  /* ADOWER */
#define RZV_ADC_E_ADOWEER_OFFSET                         0x01EA  /* ADOWEER */

/* ADC_E Register Addresses ************************************************/

#define RZV_ADC_E_ADCMPDR(m)                    (RZV_ADC_E_BASE + RZV_ADC_E_ADCMPDR_OFFSET(m))
#define RZV_ADC_E_ADDR(m)                       (RZV_ADC_E_BASE + RZV_ADC_E_ADDR_OFFSET(m))
#define RZV_ADC_E_ADCSR                              (RZV_ADC_E_BASE + RZV_ADC_E_ADCSR_OFFSET)
#define RZV_ADC_E_ADREF                              (RZV_ADC_E_BASE + RZV_ADC_E_ADREF_OFFSET)
#define RZV_ADC_E_ADANSA0                            (RZV_ADC_E_BASE + RZV_ADC_E_ADANSA0_OFFSET)
#define RZV_ADC_E_ADADS0                             (RZV_ADC_E_BASE + RZV_ADC_E_ADADS0_OFFSET)
#define RZV_ADC_E_ADADC                              (RZV_ADC_E_BASE + RZV_ADC_E_ADADC_OFFSET)
#define RZV_ADC_E_ADCER                              (RZV_ADC_E_BASE + RZV_ADC_E_ADCER_OFFSET)
#define RZV_ADC_E_ADSTRGR                            (RZV_ADC_E_BASE + RZV_ADC_E_ADSTRGR_OFFSET)
#define RZV_ADC_E_ADANSB0                            (RZV_ADC_E_BASE + RZV_ADC_E_ADANSB0_OFFSET)
#define RZV_ADC_E_ADDBLDR                            (RZV_ADC_E_BASE + RZV_ADC_E_ADDBLDR_OFFSET)
#define RZV_ADC_E_ADELCCR                            (RZV_ADC_E_BASE + RZV_ADC_E_ADELCCR_OFFSET)
#define RZV_ADC_E_ADGSPCR                            (RZV_ADC_E_BASE + RZV_ADC_E_ADGSPCR_OFFSET)
#define RZV_ADC_E_ADDBLDRA                           (RZV_ADC_E_BASE + RZV_ADC_E_ADDBLDRA_OFFSET)
#define RZV_ADC_E_ADDBLDRB                           (RZV_ADC_E_BASE + RZV_ADC_E_ADDBLDRB_OFFSET)
#define RZV_ADC_E_ADWINMON                           (RZV_ADC_E_BASE + RZV_ADC_E_ADWINMON_OFFSET)
#define RZV_ADC_E_ADCMPCR                            (RZV_ADC_E_BASE + RZV_ADC_E_ADCMPCR_OFFSET)
#define RZV_ADC_E_ADCMPANSR0                         (RZV_ADC_E_BASE + RZV_ADC_E_ADCMPANSR0_OFFSET)
#define RZV_ADC_E_ADCMPLR0                           (RZV_ADC_E_BASE + RZV_ADC_E_ADCMPLR0_OFFSET)
#define RZV_ADC_E_ADCMPSR0                           (RZV_ADC_E_BASE + RZV_ADC_E_ADCMPSR0_OFFSET)
#define RZV_ADC_E_ADCMPBNSR                          (RZV_ADC_E_BASE + RZV_ADC_E_ADCMPBNSR_OFFSET)
#define RZV_ADC_E_ADWINLLB                           (RZV_ADC_E_BASE + RZV_ADC_E_ADWINLLB_OFFSET)
#define RZV_ADC_E_ADWINULB                           (RZV_ADC_E_BASE + RZV_ADC_E_ADWINULB_OFFSET)
#define RZV_ADC_E_ADCMPBSR                           (RZV_ADC_E_BASE + RZV_ADC_E_ADCMPBSR_OFFSET)
#define RZV_ADC_E_ADANSC0                            (RZV_ADC_E_BASE + RZV_ADC_E_ADANSC0_OFFSET)
#define RZV_ADC_E_ADGCTRGR                           (RZV_ADC_E_BASE + RZV_ADC_E_ADGCTRGR_OFFSET)
#define RZV_ADC_E_ADERCR                             (RZV_ADC_E_BASE + RZV_ADC_E_ADERCR_OFFSET)
#define RZV_ADC_E_ADERCLR                            (RZV_ADC_E_BASE + RZV_ADC_E_ADERCLR_OFFSET)
#define RZV_ADC_E_ADOWER                             (RZV_ADC_E_BASE + RZV_ADC_E_ADOWER_OFFSET)
#define RZV_ADC_E_ADOWEER                            (RZV_ADC_E_BASE + RZV_ADC_E_ADOWEER_OFFSET)

/* ADC_E ADCMPDR Register Bit Definitions (Parameterized) ******************/

#define ADC_E_ADCMPDR_CMPLLA_SHIFT                        (0)      /* Bits 0-15: Cmplla */
#define ADC_E_ADCMPDR_CMPLLA_MASK(m)                      (0xffff << ADC_E_ADCMPDR_CMPLLA_SHIFT)
#define ADC_E_ADCMPDR_CMPLLA(m,val)                       (((val) << ADC_E_ADCMPDR_CMPLLA_SHIFT) & ADC_E_ADCMPDR_CMPLLA_MASK(m))

/* ADC_E ADDR Register Bit Definitions (Parameterized) *********************/

#define ADC_E_ADDR_DR_SHIFT                               (0)      /* Bits 0-15: Dr */
#define ADC_E_ADDR_DR_MASK(m)                             (0xffff << ADC_E_ADDR_DR_SHIFT)
#define ADC_E_ADDR_DR(m,val)                              (((val) << ADC_E_ADDR_DR_SHIFT) & ADC_E_ADDR_DR_MASK(m))

/* ADC_E ADADC Register Bit Definitions ******************************/

#define ADC_E_ADADC_ADC_SHIFT                   (0)      /* Bits 0-2: Adc */
#define ADC_E_ADADC_ADC_MASK                    (0x7 << ADC_E_ADADC_ADC_SHIFT)

#define ADC_E_ADADC_AVEE                        (1 << 7)  /* Avee */

/* ADC_E ADADS0 Register Bit Definitions *****************************/

#define ADC_E_ADADS0_ADS0_SHIFT                 (0)      /* Bits 0-7: Ads0 */
#define ADC_E_ADADS0_ADS0_MASK                  (0xff << ADC_E_ADADS0_ADS0_SHIFT)

/* ADC_E ADANSA0 Register Bit Definitions ****************************/

#define ADC_E_ADANSA0_ANSA0_SHIFT               (0)      /* Bits 0-7: Ansa0 */
#define ADC_E_ADANSA0_ANSA0_MASK                (0xff << ADC_E_ADANSA0_ANSA0_SHIFT)

/* ADC_E ADANSB0 Register Bit Definitions ****************************/

#define ADC_E_ADANSB0_ANSB0_SHIFT               (0)      /* Bits 0-7: Ansb0 */
#define ADC_E_ADANSB0_ANSB0_MASK                (0xff << ADC_E_ADANSB0_ANSB0_SHIFT)

/* ADC_E ADANSC0 Register Bit Definitions ****************************/

#define ADC_E_ADANSC0_ANSC0_SHIFT               (0)      /* Bits 0-7: Ansc0 */
#define ADC_E_ADANSC0_ANSC0_MASK                (0xff << ADC_E_ADANSC0_ANSC0_SHIFT)

/* ADC_E ADCER Register Bit Definitions ******************************/

#define ADC_E_ADCER_ADPRC_SHIFT                 (1)      /* Bits 1-2: Adprc */
#define ADC_E_ADCER_ADPRC_MASK                  (0x3 << ADC_E_ADCER_ADPRC_SHIFT)

#define ADC_E_ADCER_ACE                         (1 << 5)  /* Ace */

#define ADC_E_ADCER_ADRFMT                      (1 << 15)  /* Adrfmt */

/* ADC_E ADCMPANSR0 Register Bit Definitions *************************/

#define ADC_E_ADCMPANSR0_CMPCHA0_SHIFT          (0)      /* Bits 0-7: Cmpcha0 */
#define ADC_E_ADCMPANSR0_CMPCHA0_MASK           (0xff << ADC_E_ADCMPANSR0_CMPCHA0_SHIFT)

/* ADC_E ADCMPBNSR Register Bit Definitions **************************/

#define ADC_E_ADCMPBNSR_CMPCHB_SHIFT            (0)      /* Bits 0-5: Cmpchb */
#define ADC_E_ADCMPBNSR_CMPCHB_MASK             (0x3f << ADC_E_ADCMPBNSR_CMPCHB_SHIFT)

#define ADC_E_ADCMPBNSR_CMPLB                   (1 << 7)  /* Cmplb */

/* ADC_E ADCMPBSR Register Bit Definitions ***************************/

#define ADC_E_ADCMPBSR_CMPSTB                   (1 << 0)  /* Cmpstb */

/* ADC_E ADCMPCR Register Bit Definitions ****************************/

#define ADC_E_ADCMPCR_CMPAB_SHIFT               (0)      /* Bits 0-1: Cmpab */
#define ADC_E_ADCMPCR_CMPAB_MASK                (0x3 << ADC_E_ADCMPCR_CMPAB_SHIFT)

#define ADC_E_ADCMPCR_CMPBE                     (1 << 9)  /* Cmpbe */

#define ADC_E_ADCMPCR_CMPAE                     (1 << 11)  /* Cmpae */

#define ADC_E_ADCMPCR_CMPBIE                    (1 << 13)  /* Cmpbie */

#define ADC_E_ADCMPCR_WCMPE                     (1 << 14)  /* Wcmpe */

#define ADC_E_ADCMPCR_CMPAIE                    (1 << 15)  /* Cmpaie */

/* ADC_E ADCMPLR0 Register Bit Definitions ***************************/

#define ADC_E_ADCMPLR0_CMPLCHA0_SHIFT           (0)      /* Bits 0-7: Cmplcha0 */
#define ADC_E_ADCMPLR0_CMPLCHA0_MASK            (0xff << ADC_E_ADCMPLR0_CMPLCHA0_SHIFT)

/* ADC_E ADCMPSR0 Register Bit Definitions ***************************/

#define ADC_E_ADCMPSR0_CMPSTCHA0_SHIFT          (0)      /* Bits 0-7: Cmpstcha0 */
#define ADC_E_ADCMPSR0_CMPSTCHA0_MASK           (0xff << ADC_E_ADCMPSR0_CMPSTCHA0_SHIFT)

/* ADC_E ADCSR Register Bit Definitions ******************************/

#define ADC_E_ADCSR_DBLANS_SHIFT                (0)      /* Bits 0-4: Dblans */
#define ADC_E_ADCSR_DBLANS_MASK                 (0x1f << ADC_E_ADCSR_DBLANS_SHIFT)

#define ADC_E_ADCSR_GBADIE                      (1 << 6)  /* Gbadie */

#define ADC_E_ADCSR_DBLE                        (1 << 7)  /* Dble */

#define ADC_E_ADCSR_EXTRG                       (1 << 8)  /* Extrg */

#define ADC_E_ADCSR_TRGE                        (1 << 9)  /* Trge */

#define ADC_E_ADCSR_ADIE                        (1 << 12)  /* Adie */

#define ADC_E_ADCSR_ADCS_SHIFT                  (13)      /* Bits 13-14: Adcs */
#define ADC_E_ADCSR_ADCS_MASK                   (0x3 << ADC_E_ADCSR_ADCS_SHIFT)

#define ADC_E_ADCSR_ADST                        (1 << 15)  /* Adst */

/* ADC_E ADDBLDR Register Bit Definitions ****************************/

#define ADC_E_ADDBLDR_DBLDR_SHIFT               (0)      /* Bits 0-15: Dbldr */
#define ADC_E_ADDBLDR_DBLDR_MASK                (0xffff << ADC_E_ADDBLDR_DBLDR_SHIFT)

/* ADC_E ADDBLDRA Register Bit Definitions ***************************/

#define ADC_E_ADDBLDRA_DBLDRA_SHIFT             (0)      /* Bits 0-15: Dbldra */
#define ADC_E_ADDBLDRA_DBLDRA_MASK              (0xffff << ADC_E_ADDBLDRA_DBLDRA_SHIFT)

/* ADC_E ADDBLDRB Register Bit Definitions ***************************/

#define ADC_E_ADDBLDRB_DBLDRB_SHIFT             (0)      /* Bits 0-15: Dbldrb */
#define ADC_E_ADDBLDRB_DBLDRB_MASK              (0xffff << ADC_E_ADDBLDRB_DBLDRB_SHIFT)

/* ADC_E ADELCCR Register Bit Definitions ****************************/

#define ADC_E_ADELCCR_ELCC_SHIFT                (0)      /* Bits 0-1: Elcc */
#define ADC_E_ADELCCR_ELCC_MASK                 (0x3 << ADC_E_ADELCCR_ELCC_SHIFT)

#define ADC_E_ADELCCR_GCELC                     (1 << 2)  /* Gcelc */

/* ADC_E ADERCLR Register Bit Definitions ****************************/

#define ADC_E_ADERCLR_OWEC                      (1 << 2)  /* Owec */

/* ADC_E ADERCR Register Bit Definitions *****************************/

#define ADC_E_ADERCR_OWEIE                      (1 << 2)  /* Oweie */

/* ADC_E ADGCTRGR Register Bit Definitions ***************************/

#define ADC_E_ADGCTRGR_TRSC_SHIFT               (0)      /* Bits 0-5: Trsc */
#define ADC_E_ADGCTRGR_TRSC_MASK                (0x3f << ADC_E_ADGCTRGR_TRSC_SHIFT)

#define ADC_E_ADGCTRGR_GCADIE                   (1 << 6)  /* Gcadie */

#define ADC_E_ADGCTRGR_GRCE                     (1 << 7)  /* Grce */

/* ADC_E ADGSPCR Register Bit Definitions ****************************/

#define ADC_E_ADGSPCR_PGS                       (1 << 0)  /* Pgs */

#define ADC_E_ADGSPCR_GBRSCN                    (1 << 1)  /* Gbrscn */

#define ADC_E_ADGSPCR_LGRRS                     (1 << 14)  /* Lgrrs */

#define ADC_E_ADGSPCR_GBRP                      (1 << 15)  /* Gbrp */

/* ADC_E ADOWEER Register Bit Definitions ****************************/

#define ADC_E_ADOWEER_DBOWE                     (1 << 0)  /* Dbowe */

#define ADC_E_ADOWEER_DAOWE                     (1 << 1)  /* Daowe */

#define ADC_E_ADOWEER_DOWE                      (1 << 2)  /* Dowe */

/* ADC_E ADOWER Register Bit Definitions *****************************/

#define ADC_E_ADOWER_OWE_SHIFT                  (0)      /* Bits 0-7: Owe */
#define ADC_E_ADOWER_OWE_MASK                   (0xff << ADC_E_ADOWER_OWE_SHIFT)

/* ADC_E ADREF Register Bit Definitions ******************************/

#define ADC_E_ADREF_ADF                         (1 << 0)  /* Adf */

#define ADC_E_ADREF_ADSCACT                     (1 << 7)  /* Adscact */

/* ADC_E ADSTRGR Register Bit Definitions ****************************/

#define ADC_E_ADSTRGR_TRSB_SHIFT                (0)      /* Bits 0-5: Trsb */
#define ADC_E_ADSTRGR_TRSB_MASK                 (0x3f << ADC_E_ADSTRGR_TRSB_SHIFT)

#define ADC_E_ADSTRGR_TRSA_SHIFT                (8)      /* Bits 8-13: Trsa */
#define ADC_E_ADSTRGR_TRSA_MASK                 (0x3f << ADC_E_ADSTRGR_TRSA_SHIFT)

/* ADC_E ADWINLLB Register Bit Definitions ***************************/

#define ADC_E_ADWINLLB_CMPLLB_SHIFT             (0)      /* Bits 0-15: Cmpllb */
#define ADC_E_ADWINLLB_CMPLLB_MASK              (0xffff << ADC_E_ADWINLLB_CMPLLB_SHIFT)

/* ADC_E ADWINMON Register Bit Definitions ***************************/

#define ADC_E_ADWINMON_MONCOMB                  (1 << 0)  /* Moncomb */

#define ADC_E_ADWINMON_MONCMPA                  (1 << 4)  /* Moncmpa */

#define ADC_E_ADWINMON_MONCMPB                  (1 << 5)  /* Moncmpb */

/* ADC_E ADWINULB Register Bit Definitions ***************************/

#define ADC_E_ADWINULB_CMPULB_SHIFT             (0)      /* Bits 0-15: Cmpulb */
#define ADC_E_ADWINULB_CMPULB_MASK              (0xffff << ADC_E_ADWINULB_CMPULB_SHIFT)

/* ADC_E Channel definitions */
#define RZV_ADC_E_CHANNEL_0        0

/* Maximum number of ADC_E channels */
#define RZV_ADC_E_MAX_CHANNELS     1

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_ADC_E_H */

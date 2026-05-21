/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_elc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ELC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ELC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ELC Base Address */
#ifndef R_ELC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_ELC_BASE           0x40201000
#else
#define R_ELC_BASE           0x50201000
#endif
#endif

/* ELC Register Offsets */

#define R_ELC_ELCR_OFFSET                         0x00000000  /* Event Link Controller Register */
/* ELSEGR[%s] Registers () */
#define R_ELC_ELSEGR_OFFSET(m)                    (0x00000004 + ((m) * 0x00000004))  /* Event Link Software Event Generation Register */
/* ELSR[%s] Registers () */
#define R_ELC_ELSR_OFFSET(m)                      (0x00000020 + ((m) * 0x00000004))  /* Event Link Setting Register %s */
#define R_ELC_ELCSARA_OFFSET                      0x00000100  /* Event Link Controller Security Attribution Register A */
#define R_ELC_ELCSARB_OFFSET                      0x00000104  /* Event Link Controller Security Attribution Register B */
#define R_ELC_ELCSARC_OFFSET                      0x00000108  /* Event Link Controller Security Attribution Register C */
#define R_ELC_ELCPARA_OFFSET                      0x00000110  /* Event Link Controller Privilege Attribution Register A */
#define R_ELC_ELCPARB_OFFSET                      0x00000114  /* Event Link Controller Privilege Attribution Register B */
#define R_ELC_ELCPARC_OFFSET                      0x00000118  /* Event Link Controller Privilege Attribution Register C */

/* ELC Register Addresses */

#define R_ELC_ELCR                                (R_ELC_BASE + R_ELC_ELCR_OFFSET)
#define R_ELC_ELSEGR(m)                           (R_ELC_BASE + R_ELC_ELSEGR_OFFSET(m))
#define R_ELC_ELSR(m)                             (R_ELC_BASE + R_ELC_ELSR_OFFSET(m))
#define R_ELC_ELCSARA                             (R_ELC_BASE + R_ELC_ELCSARA_OFFSET)
#define R_ELC_ELCSARB                             (R_ELC_BASE + R_ELC_ELCSARB_OFFSET)
#define R_ELC_ELCSARC                             (R_ELC_BASE + R_ELC_ELCSARC_OFFSET)
#define R_ELC_ELCPARA                             (R_ELC_BASE + R_ELC_ELCPARA_OFFSET)
#define R_ELC_ELCPARB                             (R_ELC_BASE + R_ELC_ELCPARB_OFFSET)
#define R_ELC_ELCPARC                             (R_ELC_BASE + R_ELC_ELCPARC_OFFSET)

/* Register bit definitions */
/* ELCR Register bit definitions */
#define R_ELC_ELCR_ELCON                          (1 << 7)  /* All Event Link Enable */

/* ELCSARA Register bit definitions */
#define R_ELC_ELCSARA_ELCR                        (1 << 0)  /* Event Link Controller RegisterSecurity Attribution */

#define R_ELC_ELCSARA_ELSEGR_S                    (1 << 1)  /* Event Link Software Event Generation Register %s Security Attribution */

#define R_ELC_ELCSARA_ELSEGR0                     (1 << 1)  /* Event Link Software Event Generation Register 0 Security Attribution */

#define R_ELC_ELCSARA_ELSEGR1                     (1 << 2)  /* Event Link Software Event Generation Register 1 Security Attribution */

#define R_ELC_ELCSARA_ELSEGR2                     (1 << 3)  /* Event Link Software Event Generation Register 2 Security Attribution */

#define R_ELC_ELCSARA_ELSEGR3                     (1 << 4)  /* Event Link Software Event Generation Register 3 Security Attribution */

/* ELCSARB Register bit definitions */
#define R_ELC_ELCSARB_ELSR_S                      (1 << 0)  /* Event Link Setting Register %s Security Attribution */

#define R_ELC_ELCSARB_ELSR0                       (1 << 0)  /* Event Link Setting Register 0 Security Attribution */

#define R_ELC_ELCSARB_ELSR1                       (1 << 1)  /* Event Link Setting Register 1 Security Attribution */

#define R_ELC_ELCSARB_ELSR2                       (1 << 2)  /* Event Link Setting Register 2 Security Attribution */

#define R_ELC_ELCSARB_ELSR3                       (1 << 3)  /* Event Link Setting Register 3 Security Attribution */

#define R_ELC_ELCSARB_ELSR4                       (1 << 4)  /* Event Link Setting Register 4 Security Attribution */

#define R_ELC_ELCSARB_ELSR5                       (1 << 5)  /* Event Link Setting Register 5 Security Attribution */

#define R_ELC_ELCSARB_ELSR6                       (1 << 6)  /* Event Link Setting Register 6 Security Attribution */

#define R_ELC_ELCSARB_ELSR7                       (1 << 7)  /* Event Link Setting Register 7 Security Attribution */

#define R_ELC_ELCSARB_ELSR8                       (1 << 8)  /* Event Link Setting Register 8 Security Attribution */

#define R_ELC_ELCSARB_ELSR9                       (1 << 9)  /* Event Link Setting Register 9 Security Attribution */

#define R_ELC_ELCSARB_ELSR10                      (1 << 10)  /* Event Link Setting Register 10 Security Attribution */

#define R_ELC_ELCSARB_ELSR11                      (1 << 11)  /* Event Link Setting Register 11 Security Attribution */

#define R_ELC_ELCSARB_ELSR12                      (1 << 12)  /* Event Link Setting Register 12 Security Attribution */

#define R_ELC_ELCSARB_ELSR13                      (1 << 13)  /* Event Link Setting Register 13 Security Attribution */

#define R_ELC_ELCSARB_ELSR14                      (1 << 14)  /* Event Link Setting Register 14 Security Attribution */

#define R_ELC_ELCSARB_ELSR15                      (1 << 15)  /* Event Link Setting Register 15 Security Attribution */

#define R_ELC_ELCSARB_ELSR16                      (1 << 16)  /* Event Link Setting Register 16 Security Attribution */

#define R_ELC_ELCSARB_ELSR17                      (1 << 17)  /* Event Link Setting Register 17 Security Attribution */

#define R_ELC_ELCSARB_ELSR18                      (1 << 18)  /* Event Link Setting Register 18 Security Attribution */

#define R_ELC_ELCSARB_ELSR19                      (1 << 19)  /* Event Link Setting Register 19 Security Attribution */

#define R_ELC_ELCSARB_ELSR20                      (1 << 20)  /* Event Link Setting Register 20 Security Attribution */

#define R_ELC_ELCSARB_ELSR21                      (1 << 21)  /* Event Link Setting Register 21 Security Attribution */

#define R_ELC_ELCSARB_ELSR22                      (1 << 22)  /* Event Link Setting Register 22 Security Attribution */

#define R_ELC_ELCSARB_ELSR23                      (1 << 23)  /* Event Link Setting Register 23 Security Attribution */

#define R_ELC_ELCSARB_ELSR24                      (1 << 24)  /* Event Link Setting Register 24 Security Attribution */

#define R_ELC_ELCSARB_ELSR25                      (1 << 25)  /* Event Link Setting Register 25 Security Attribution */

#define R_ELC_ELCSARB_ELSR26                      (1 << 26)  /* Event Link Setting Register 26 Security Attribution */

#define R_ELC_ELCSARB_ELSR27                      (1 << 27)  /* Event Link Setting Register 27 Security Attribution */

#define R_ELC_ELCSARB_ELSR28                      (1 << 28)  /* Event Link Setting Register 28 Security Attribution */

#define R_ELC_ELCSARB_ELSR29                      (1 << 29)  /* Event Link Setting Register 29 Security Attribution */

#define R_ELC_ELCSARB_ELSR30                      (1 << 30)  /* Event Link Setting Register 30 Security Attribution */

#define R_ELC_ELCSARB_ELSR31                      (1 << 31)  /* Event Link Setting Register 31 Security Attribution */

/* ELCSARC Register bit definitions */
#define R_ELC_ELCSARC_ELSR_S                      (1 << 0)  /* Event Link Setting Register %s Security Attribution */

#define R_ELC_ELCSARC_ELSR0                       (1 << 0)  /* Event Link Setting Register 0 Security Attribution */

#define R_ELC_ELCSARC_ELSR1                       (1 << 1)  /* Event Link Setting Register 1 Security Attribution */

#define R_ELC_ELCSARC_ELSR2                       (1 << 2)  /* Event Link Setting Register 2 Security Attribution */

#define R_ELC_ELCSARC_ELSR3                       (1 << 3)  /* Event Link Setting Register 3 Security Attribution */

#define R_ELC_ELCSARC_ELSR4                       (1 << 4)  /* Event Link Setting Register 4 Security Attribution */

#define R_ELC_ELCSARC_ELSR5                       (1 << 5)  /* Event Link Setting Register 5 Security Attribution */

#define R_ELC_ELCSARC_ELSR6                       (1 << 6)  /* Event Link Setting Register 6 Security Attribution */

#define R_ELC_ELCSARC_ELSR7                       (1 << 7)  /* Event Link Setting Register 7 Security Attribution */

#define R_ELC_ELCSARC_ELSR8                       (1 << 8)  /* Event Link Setting Register 8 Security Attribution */

#define R_ELC_ELCSARC_ELSR9                       (1 << 9)  /* Event Link Setting Register 9 Security Attribution */

#define R_ELC_ELCSARC_ELSR10                      (1 << 10)  /* Event Link Setting Register 10 Security Attribution */

#define R_ELC_ELCSARC_ELSR11                      (1 << 11)  /* Event Link Setting Register 11 Security Attribution */

#define R_ELC_ELCSARC_ELSR12                      (1 << 12)  /* Event Link Setting Register 12 Security Attribution */

#define R_ELC_ELCSARC_ELSR13                      (1 << 13)  /* Event Link Setting Register 13 Security Attribution */

#define R_ELC_ELCSARC_ELSR14                      (1 << 14)  /* Event Link Setting Register 14 Security Attribution */

#define R_ELC_ELCSARC_ELSR15                      (1 << 15)  /* Event Link Setting Register 15 Security Attribution */

#define R_ELC_ELCSARC_ELSR16                      (1 << 16)  /* Event Link Setting Register 16 Security Attribution */

#define R_ELC_ELCSARC_ELSR17                      (1 << 17)  /* Event Link Setting Register 17 Security Attribution */

#define R_ELC_ELCSARC_ELSR18                      (1 << 18)  /* Event Link Setting Register 18 Security Attribution */

#define R_ELC_ELCSARC_ELSR19                      (1 << 19)  /* Event Link Setting Register 19 Security Attribution */

#define R_ELC_ELCSARC_ELSR20                      (1 << 20)  /* Event Link Setting Register 20 Security Attribution */

#define R_ELC_ELCSARC_ELSR21                      (1 << 21)  /* Event Link Setting Register 21 Security Attribution */

#define R_ELC_ELCSARC_ELSR22                      (1 << 22)  /* Event Link Setting Register 22 Security Attribution */

#define R_ELC_ELCSARC_ELSR23                      (1 << 23)  /* Event Link Setting Register 23 Security Attribution */

#define R_ELC_ELCSARC_ELSR24                      (1 << 24)  /* Event Link Setting Register 24 Security Attribution */

#define R_ELC_ELCSARC_ELSR25                      (1 << 25)  /* Event Link Setting Register 25 Security Attribution */

#define R_ELC_ELCSARC_ELSR26                      (1 << 26)  /* Event Link Setting Register 26 Security Attribution */

#define R_ELC_ELCSARC_ELSR27                      (1 << 27)  /* Event Link Setting Register 27 Security Attribution */

#define R_ELC_ELCSARC_ELSR28                      (1 << 28)  /* Event Link Setting Register 28 Security Attribution */

#define R_ELC_ELCSARC_ELSR29                      (1 << 29)  /* Event Link Setting Register 29 Security Attribution */

#define R_ELC_ELCSARC_ELSR30                      (1 << 30)  /* Event Link Setting Register 30 Security Attribution */

#define R_ELC_ELCSARC_ELSR31                      (1 << 31)  /* Event Link Setting Register 31 Security Attribution */

/* ELCPARA Register bit definitions */
#define R_ELC_ELCPARA_ELCR                        (1 << 0)  /* Event Link Controller Register Privilege Attribution */

#define R_ELC_ELCPARA_ELSEGR_S                    (1 << 1)  /* Event Link Software Event Generation Register %s Privilege Attribution */

#define R_ELC_ELCPARA_ELSEGR0                     (1 << 1)  /* Event Link Software Event Generation Register 0 Privilege Attribution */

#define R_ELC_ELCPARA_ELSEGR1                     (1 << 2)  /* Event Link Software Event Generation Register 1 Privilege Attribution */

#define R_ELC_ELCPARA_ELSEGR2                     (1 << 3)  /* Event Link Software Event Generation Register 2 Privilege Attribution */

#define R_ELC_ELCPARA_ELSEGR3                     (1 << 4)  /* Event Link Software Event Generation Register 3 Privilege Attribution */

/* ELCPARB Register bit definitions */
#define R_ELC_ELCPARB_ELSR_S                      (1 << 0)  /* Event Link Setting Register %s Privilege Attribution */

#define R_ELC_ELCPARB_ELSR0                       (1 << 0)  /* Event Link Setting Register 0 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR1                       (1 << 1)  /* Event Link Setting Register 1 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR2                       (1 << 2)  /* Event Link Setting Register 2 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR3                       (1 << 3)  /* Event Link Setting Register 3 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR4                       (1 << 4)  /* Event Link Setting Register 4 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR5                       (1 << 5)  /* Event Link Setting Register 5 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR6                       (1 << 6)  /* Event Link Setting Register 6 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR7                       (1 << 7)  /* Event Link Setting Register 7 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR8                       (1 << 8)  /* Event Link Setting Register 8 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR9                       (1 << 9)  /* Event Link Setting Register 9 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR10                      (1 << 10)  /* Event Link Setting Register 10 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR11                      (1 << 11)  /* Event Link Setting Register 11 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR12                      (1 << 12)  /* Event Link Setting Register 12 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR13                      (1 << 13)  /* Event Link Setting Register 13 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR14                      (1 << 14)  /* Event Link Setting Register 14 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR15                      (1 << 15)  /* Event Link Setting Register 15 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR16                      (1 << 16)  /* Event Link Setting Register 16 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR17                      (1 << 17)  /* Event Link Setting Register 17 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR18                      (1 << 18)  /* Event Link Setting Register 18 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR19                      (1 << 19)  /* Event Link Setting Register 19 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR20                      (1 << 20)  /* Event Link Setting Register 20 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR21                      (1 << 21)  /* Event Link Setting Register 21 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR22                      (1 << 22)  /* Event Link Setting Register 22 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR23                      (1 << 23)  /* Event Link Setting Register 23 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR24                      (1 << 24)  /* Event Link Setting Register 24 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR25                      (1 << 25)  /* Event Link Setting Register 25 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR26                      (1 << 26)  /* Event Link Setting Register 26 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR27                      (1 << 27)  /* Event Link Setting Register 27 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR28                      (1 << 28)  /* Event Link Setting Register 28 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR29                      (1 << 29)  /* Event Link Setting Register 29 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR30                      (1 << 30)  /* Event Link Setting Register 30 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR31                      (1 << 31)  /* Event Link Setting Register 31 Privilege Attribution */

/* ELCPARC Register bit definitions */
#define R_ELC_ELCPARC_ELSR_S                      (1 << 0)  /* Event Link Setting Register %s Privilege Attribution */

#define R_ELC_ELCPARC_ELSR0                       (1 << 0)  /* Event Link Setting Register 0 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR1                       (1 << 1)  /* Event Link Setting Register 1 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR2                       (1 << 2)  /* Event Link Setting Register 2 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR3                       (1 << 3)  /* Event Link Setting Register 3 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR4                       (1 << 4)  /* Event Link Setting Register 4 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR5                       (1 << 5)  /* Event Link Setting Register 5 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR6                       (1 << 6)  /* Event Link Setting Register 6 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR7                       (1 << 7)  /* Event Link Setting Register 7 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR8                       (1 << 8)  /* Event Link Setting Register 8 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR9                       (1 << 9)  /* Event Link Setting Register 9 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR10                      (1 << 10)  /* Event Link Setting Register 10 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR11                      (1 << 11)  /* Event Link Setting Register 11 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR12                      (1 << 12)  /* Event Link Setting Register 12 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR13                      (1 << 13)  /* Event Link Setting Register 13 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR14                      (1 << 14)  /* Event Link Setting Register 14 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR15                      (1 << 15)  /* Event Link Setting Register 15 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR16                      (1 << 16)  /* Event Link Setting Register 16 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR17                      (1 << 17)  /* Event Link Setting Register 17 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR18                      (1 << 18)  /* Event Link Setting Register 18 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR19                      (1 << 19)  /* Event Link Setting Register 19 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR20                      (1 << 20)  /* Event Link Setting Register 20 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR21                      (1 << 21)  /* Event Link Setting Register 21 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR22                      (1 << 22)  /* Event Link Setting Register 22 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR23                      (1 << 23)  /* Event Link Setting Register 23 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR24                      (1 << 24)  /* Event Link Setting Register 24 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR25                      (1 << 25)  /* Event Link Setting Register 25 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR26                      (1 << 26)  /* Event Link Setting Register 26 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR27                      (1 << 27)  /* Event Link Setting Register 27 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR28                      (1 << 28)  /* Event Link Setting Register 28 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR29                      (1 << 29)  /* Event Link Setting Register 29 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR30                      (1 << 30)  /* Event Link Setting Register 30 Privilege Attribution */

#define R_ELC_ELCPARC_ELSR31                      (1 << 31)  /* Event Link Setting Register 31 Privilege Attribution */

/* ELSEGR Register bit definitions - Software Event Generation */

#define R_ELC_ELSEGR_BY_WI                        (1 << 7)  /* Write Ignore bit */
#define R_ELC_ELSEGR_BY_WE                        (1 << 6)  /* Write Enable bit */
#define R_ELC_ELSEGR_BY_SEG                       (1 << 0)  /* Software Event Generation bit */

/* Steps necessary to unlock and write software event generation bits */

#define ELC_ELSEGRN_STEP1                         (0x00)  /* WI = 0, WE = 0, SEG = 0 */
#define ELC_ELSEGRN_STEP2                         (0x40)  /* WI = 0, WE = 1, SEG = 0 */
#define ELC_ELSEGRN_STEP3                         (0x41)  /* WI = 0, WE = 1, SEG = 1 */

/* ELC enable/disable control values */

#define ELC_ELCR_ELCON_DISABLE                    (0x00)  /* ELC operation disabled */
#define ELC_ELCR_ELCON_ENABLE                     (0x80)  /* ELC operation enabled */

/* Maximum number of peripherals/ELSR registers */

#define ELC_MAX_PERIPHERALS                       27      /* Number of ELC peripheral slots */
#define ELC_MAX_SOFTWARE_EVENTS                   4       /* Number of software event generators */

/* ELC Peripheral definitions - these map to ELSR register indices */

#define ELC_PERIPHERAL_GPT_A                      0       /* GPT A event input */
#define ELC_PERIPHERAL_GPT_B                      1       /* GPT B event input */
#define ELC_PERIPHERAL_GPT_C                      2       /* GPT C event input */
#define ELC_PERIPHERAL_GPT_D                      3       /* GPT D event input */
#define ELC_PERIPHERAL_GPT_E                      4       /* GPT E event input */
#define ELC_PERIPHERAL_GPT_F                      5       /* GPT F event input */
#define ELC_PERIPHERAL_GPT_G                      6       /* GPT G event input */
#define ELC_PERIPHERAL_GPT_H                      7       /* GPT H event input */
#define ELC_PERIPHERAL_DAC0                       8       /* DAC0 event input */
#define ELC_PERIPHERAL_DAC1                       9       /* DAC1 event input */
#define ELC_PERIPHERAL_IOPORT1                    10      /* IOPORT1 event input */
#define ELC_PERIPHERAL_IOPORT2                    11      /* IOPORT2 event input */
#define ELC_PERIPHERAL_IOPORT3                    12      /* IOPORT3 event input */
#define ELC_PERIPHERAL_IOPORT4                    13      /* IOPORT4 event input */
#define ELC_PERIPHERAL_ADC0                       14      /* ADC0 scan group 0 trigger A */
#define ELC_PERIPHERAL_ADC0_B                     15      /* ADC0 scan group 0 trigger B */
#define ELC_PERIPHERAL_ADC0_C                     16      /* ADC0 scan group 0 trigger C */
#define ELC_PERIPHERAL_ADC1                       17      /* ADC1 scan group 1 trigger A */
#define ELC_PERIPHERAL_ADC1_B                     18      /* ADC1 scan group 1 trigger B */
#define ELC_PERIPHERAL_ADC1_C                     19      /* ADC1 scan group 1 trigger C */
#define ELC_PERIPHERAL_ADC2                       20      /* ADC2 scan group 2 trigger A */
#define ELC_PERIPHERAL_ADC2_B                     21      /* ADC2 scan group 2 trigger B */
#define ELC_PERIPHERAL_ADC2_C                     22      /* ADC2 scan group 2 trigger C */
#define ELC_PERIPHERAL_I3C                        23      /* I3C event input */
#define ELC_PERIPHERAL_GPTP0                      24      /* gPTP 0 event input */
#define ELC_PERIPHERAL_GPTP1                      25      /* gPTP 1 event input */
#define ELC_PERIPHERAL_NONE                       26      /* No peripheral linked */

/* ELC Event None - used to disable a link */

#define ELC_EVENT_NONE                            0x000   /* No event linked */

/* Maximum number of channels */

#define ELC_MAX_CHANNELS    53

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ELC_H */

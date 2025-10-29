/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_cpscu.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CPSCU_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CPSCU_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CPSCU Base Address */
#ifndef R_CPSCU_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_CPSCU_BASE           0x40008000
#else
#define R_CPSCU_BASE           0x50008000
#endif
#endif

/* CPSCU Register Offsets */

#define R_CPSCU_CSAR_OFFSET                       0x00000000  /* Cache Security Attribution Register */
#define R_CPSCU_SRAMSAR_OFFSET                    0x00000010  /* SRAM Security Attribution Register */
#define R_CPSCU_STBRAMSAR_OFFSET                  0x00000014  /* Standby RAM memory Security Attribution Register */
#define R_CPSCU_DTCSAR_OFFSET                     0x00000030  /* DTC Controller Security Attribution Register */
#define R_CPSCU_DMACSAR_OFFSET                    0x00000034  /* DMAC Controller Security Attribution Register */
#define R_CPSCU_ICUSARA_OFFSET                    0x00000040  /* Interrupt Controller Unit Security Attribution Register A */
#define R_CPSCU_ICUSARB_OFFSET                    0x00000044  /* Interrupt Controller Unit Security Attribution Register B */
#define R_CPSCU_ICUSARC_OFFSET                    0x00000048  /* ICU Security Attribution Register C */
#define R_CPSCU_ICUSARD_OFFSET                    0x0000004c  /* ICU Security Attribution Register D */
#define R_CPSCU_ICUSARE_OFFSET                    0x00000050  /* Interrupt Controller Unit Security Attribution Register E */
#define R_CPSCU_ICUSARF_OFFSET                    0x00000054  /* Interrupt Controller Unit Security Attribution Register F */
#define R_CPSCU_ICUSARG_OFFSET                    0x00000070  /* Interrupt Controller Unit Security Attribution Register G */
#define R_CPSCU_ICUSARH_OFFSET                    0x00000074  /* Interrupt Controller Unit Security Attribution Register H */
#define R_CPSCU_ICUSARI_OFFSET                    0x00000078  /* Interrupt Controller Unit Security Attribution Register I */
#define R_CPSCU_ICUSARJ_OFFSET                    0x0000007c  /* Interrupt Controller Unit Security Attribution Register J */
#define R_CPSCU_ICUSARK_OFFSET                    0x00000080  /* Interrupt Controller Unit Security Attribution Register K */
#define R_CPSCU_ICUSARL_OFFSET                    0x00000084  /* Interrupt Controller Unit Security Attribution Register L */
#define R_CPSCU_BUSSARA_OFFSET                    0x00000100  /* Bus Security Attribution Register A */
#define R_CPSCU_BUSSARB_OFFSET                    0x00000104  /* Bus Security Attribution Register B */
#define R_CPSCU_BUSSARC_OFFSET                    0x00000110  /* Bus Security Attribution Register C */
#define R_CPSCU_BUSPARC_OFFSET                    0x00000114  /* Bus Privileged Attribution Register C */
#define R_CPSCU_NMISR_OFFSET                      0x00000120  /* Non-Maskable Interrupt Status Register */
#define R_CPSCU_MMPUSARA_OFFSET                   0x00000130  /* Master Memory Protection Unit Security Attribution Register A */
#define R_CPSCU_MMPUSARB_OFFSET                   0x00000134  /* Master Memory Protection Unit Security Attribution Register B */
#define R_CPSCU_CPUSAR_OFFSET                     0x00000170  /* CPU Security Attribution Register */
#define R_CPSCU_DEBUGSAR_OFFSET                   0x00000180  /* Debug Security Attribution Register */
#define R_CPSCU_DMACCHSAR_OFFSET                  0x000001a0  /* DMAC channel Security Attribution Register */
#define R_CPSCU_CPUDSAR_OFFSET                    0x000001b0  /* CPU Debug Security Attribution Register */
#define R_CPSCU_DMACCHPAR_OFFSET                  0x000001f0  /* DMA Channel Privilege Attribution Register */
/* SRAMSABAR%s Registers () */
#define R_CPSCU_SRAMSABAR_OFFSET(m)               (0x00000400 + ((m) * 0x00000004))  /* SRAM Security Attribute Boundary Address Register */
#define R_CPSCU_CACHESAR_OFFSET                   0x00000500  /* Cache Security Attribution Register */
#define R_CPSCU_TCMSAR_OFFSET                     0x00000504  /* TCM Security Attribution Register */
/* TCMSABAR%s Registers (C,S) */
#define R_CPSCU_TCMSABAR_OFFSET(m)                (0x00000508 + ((m) * 0x00000004))  /* TCM Security Attribute Boundary Address Register */
#define R_CPSCU_SRAMESAR_OFFSET                   0x00000510  /* SRAM ECC region Security Attribute Register */
#define R_CPSCU_TEVTRCR_OFFSET                    0x00000600  /* Trusted Event Route Control Register */
#define R_CPSCU_IPCSAR_OFFSET                     0x00000610  /* IPC Security Attribution Register */
#define R_CPSCU_IPCPAR_OFFSET                     0x00000614  /* IPC Privileged Attribution Register */

/* CPSCU Register Addresses */

#define R_CPSCU_CSAR                              (R_CPSCU_BASE + R_CPSCU_CSAR_OFFSET)
#define R_CPSCU_SRAMSAR                           (R_CPSCU_BASE + R_CPSCU_SRAMSAR_OFFSET)
#define R_CPSCU_STBRAMSAR                         (R_CPSCU_BASE + R_CPSCU_STBRAMSAR_OFFSET)
#define R_CPSCU_DTCSAR                            (R_CPSCU_BASE + R_CPSCU_DTCSAR_OFFSET)
#define R_CPSCU_DMACSAR                           (R_CPSCU_BASE + R_CPSCU_DMACSAR_OFFSET)
#define R_CPSCU_ICUSARA                           (R_CPSCU_BASE + R_CPSCU_ICUSARA_OFFSET)
#define R_CPSCU_ICUSARB                           (R_CPSCU_BASE + R_CPSCU_ICUSARB_OFFSET)
#define R_CPSCU_ICUSARC                           (R_CPSCU_BASE + R_CPSCU_ICUSARC_OFFSET)
#define R_CPSCU_ICUSARD                           (R_CPSCU_BASE + R_CPSCU_ICUSARD_OFFSET)
#define R_CPSCU_ICUSARE                           (R_CPSCU_BASE + R_CPSCU_ICUSARE_OFFSET)
#define R_CPSCU_ICUSARF                           (R_CPSCU_BASE + R_CPSCU_ICUSARF_OFFSET)
#define R_CPSCU_ICUSARG                           (R_CPSCU_BASE + R_CPSCU_ICUSARG_OFFSET)
#define R_CPSCU_ICUSARH                           (R_CPSCU_BASE + R_CPSCU_ICUSARH_OFFSET)
#define R_CPSCU_ICUSARI                           (R_CPSCU_BASE + R_CPSCU_ICUSARI_OFFSET)
#define R_CPSCU_ICUSARJ                           (R_CPSCU_BASE + R_CPSCU_ICUSARJ_OFFSET)
#define R_CPSCU_ICUSARK                           (R_CPSCU_BASE + R_CPSCU_ICUSARK_OFFSET)
#define R_CPSCU_ICUSARL                           (R_CPSCU_BASE + R_CPSCU_ICUSARL_OFFSET)
#define R_CPSCU_BUSSARA                           (R_CPSCU_BASE + R_CPSCU_BUSSARA_OFFSET)
#define R_CPSCU_BUSSARB                           (R_CPSCU_BASE + R_CPSCU_BUSSARB_OFFSET)
#define R_CPSCU_BUSSARC                           (R_CPSCU_BASE + R_CPSCU_BUSSARC_OFFSET)
#define R_CPSCU_BUSPARC                           (R_CPSCU_BASE + R_CPSCU_BUSPARC_OFFSET)
#define R_CPSCU_NMISR                             (R_CPSCU_BASE + R_CPSCU_NMISR_OFFSET)
#define R_CPSCU_MMPUSARA                          (R_CPSCU_BASE + R_CPSCU_MMPUSARA_OFFSET)
#define R_CPSCU_MMPUSARB                          (R_CPSCU_BASE + R_CPSCU_MMPUSARB_OFFSET)
#define R_CPSCU_CPUSAR                            (R_CPSCU_BASE + R_CPSCU_CPUSAR_OFFSET)
#define R_CPSCU_DEBUGSAR                          (R_CPSCU_BASE + R_CPSCU_DEBUGSAR_OFFSET)
#define R_CPSCU_DMACCHSAR                         (R_CPSCU_BASE + R_CPSCU_DMACCHSAR_OFFSET)
#define R_CPSCU_CPUDSAR                           (R_CPSCU_BASE + R_CPSCU_CPUDSAR_OFFSET)
#define R_CPSCU_DMACCHPAR                         (R_CPSCU_BASE + R_CPSCU_DMACCHPAR_OFFSET)
#define R_CPSCU_SRAMSABAR(m)                      (R_CPSCU_BASE + R_CPSCU_SRAMSABAR_OFFSET(m))
#define R_CPSCU_CACHESAR                          (R_CPSCU_BASE + R_CPSCU_CACHESAR_OFFSET)
#define R_CPSCU_TCMSAR                            (R_CPSCU_BASE + R_CPSCU_TCMSAR_OFFSET)
#define R_CPSCU_TCMSABAR(m)                       (R_CPSCU_BASE + R_CPSCU_TCMSABAR_OFFSET(m))
#define R_CPSCU_SRAMESAR                          (R_CPSCU_BASE + R_CPSCU_SRAMESAR_OFFSET)
#define R_CPSCU_TEVTRCR                           (R_CPSCU_BASE + R_CPSCU_TEVTRCR_OFFSET)
#define R_CPSCU_IPCSAR                            (R_CPSCU_BASE + R_CPSCU_IPCSAR_OFFSET)
#define R_CPSCU_IPCPAR                            (R_CPSCU_BASE + R_CPSCU_IPCPAR_OFFSET)

/* Register bit definitions */
/* CSAR Register bit definitions */
#define R_CPSCU_CSAR_CACHESA                      (1 << 0)  /* Security Attributes of Registers for Cache Control */

#define R_CPSCU_CSAR_CACHELSA                     (1 << 1)  /* Security Attributes of Registers for Cache Line Configuration */

#define R_CPSCU_CSAR_CACHEESA                     (1 << 2)  /* Security Attributes of Registers for Cache Error */

/* SRAMSAR Register bit definitions */
#define R_CPSCU_SRAMSAR_SRAMSA_S                  (1 << 0)  /* SRAM%s Register Security Attribution */

#define R_CPSCU_SRAMSAR_SRAMWTSA                  (1 << 8)  /* Security attribution for SRAMWTSC */

#define R_CPSCU_SRAMSAR_SRAMSA0                   (1 << 0)  /* SRAM0 Register Security Attribution */

#define R_CPSCU_SRAMSAR_SRAMSA1                   (1 << 1)  /* SRAM1 Register Security Attribution */

#define R_CPSCU_SRAMSAR_SRAMSA2                   (1 << 2)  /* SRAM2 Register Security Attribution */

#define R_CPSCU_SRAMSAR_SRAMSA3                   (1 << 3)  /* SRAM3 Register Security Attribution */

/* STBRAMSAR Register bit definitions */
#define R_CPSCU_STBRAMSAR_NSBSTBR_SHIFT           (0)  /* Security attributes of each region for Standby RAM */
#define R_CPSCU_STBRAMSAR_NSBSTBR_MASK            0xf
#  define R_CPSCU_STBRAMSAR_NSBSTBR_0X0                   (0 << R_CPSCU_STBRAMSAR_NSBSTBR_SHIFT)  /* Region7-0 are all Secure. */
#  define R_CPSCU_STBRAMSAR_NSBSTBR_0X1                   (1 << R_CPSCU_STBRAMSAR_NSBSTBR_SHIFT)  /* Region7 is Non-secure. Region6-0 are Secure */
#  define R_CPSCU_STBRAMSAR_NSBSTBR_0X2                   (2 << R_CPSCU_STBRAMSAR_NSBSTBR_SHIFT)  /* Region7-6 are Non-secure. Region5-0 are Secure. */
#  define R_CPSCU_STBRAMSAR_NSBSTBR_0X3                   (3 << R_CPSCU_STBRAMSAR_NSBSTBR_SHIFT)  /* Region7-5 are Non-secure. Region4-0 are Secure. */
#  define R_CPSCU_STBRAMSAR_NSBSTBR_0X4                   (4 << R_CPSCU_STBRAMSAR_NSBSTBR_SHIFT)  /* Region7-4 are Non-secure. Region 3-0 are Secure. */
#  define R_CPSCU_STBRAMSAR_NSBSTBR_0X5                   (5 << R_CPSCU_STBRAMSAR_NSBSTBR_SHIFT)  /* Region7-3 are Non-secure. Region 2-0 are Secure. */
#  define R_CPSCU_STBRAMSAR_NSBSTBR_0X6                   (6 << R_CPSCU_STBRAMSAR_NSBSTBR_SHIFT)  /* Region7-2 are Non-secure. Region 1-0 are Secure. */
#  define R_CPSCU_STBRAMSAR_NSBSTBR_0X7                   (7 << R_CPSCU_STBRAMSAR_NSBSTBR_SHIFT)  /* Region7-1 are Non-Secure. Region0 is Secure. */

/* DTCSAR Register bit definitions */
#define R_CPSCU_DTCSAR_DTCSTSA_S                  (1 << 0)  /* DTC%s Security Attribution */

#define R_CPSCU_DTCSAR_DTCSTSA0                   (1 << 0)  /* DTC0 Security Attribution */

#define R_CPSCU_DTCSAR_DTCSTSA1                   (1 << 16)  /* DTC1 Security Attribution */

/* DMACSAR Register bit definitions */
#define R_CPSCU_DMACSAR_DMASTSA_S                 (1 << 0)  /* DMAC%s DMAST Security Attribution */

#define R_CPSCU_DMACSAR_DMASTSA0                  (1 << 0)  /* DMAC0 DMAST Security Attribution */

#define R_CPSCU_DMACSAR_DMASTSA1                  (1 << 16)  /* DMAC1 DMAST Security Attribution */

/* ICUSARA Register bit definitions */
#define R_CPSCU_ICUSARA_SAIRQCR_S                 (1 << 0)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR0                  (1 << 0)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR1                  (1 << 1)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR2                  (1 << 2)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR3                  (1 << 3)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR4                  (1 << 4)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR5                  (1 << 5)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR6                  (1 << 6)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR7                  (1 << 7)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR8                  (1 << 8)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR9                  (1 << 9)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR10                 (1 << 10)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR11                 (1 << 11)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR12                 (1 << 12)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR13                 (1 << 13)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR14                 (1 << 14)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR15                 (1 << 15)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR16                 (1 << 16)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR17                 (1 << 17)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR18                 (1 << 18)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR19                 (1 << 19)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR20                 (1 << 20)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR21                 (1 << 21)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR22                 (1 << 22)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR23                 (1 << 23)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR24                 (1 << 24)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR25                 (1 << 25)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR26                 (1 << 26)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR27                 (1 << 27)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR28                 (1 << 28)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR29                 (1 << 29)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR30                 (1 << 30)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

#define R_CPSCU_ICUSARA_SAIRQCR31                 (1 << 31)  /* Security attributes of registers for the IRQCR, WUPEN0, WUPEN1 registers */

/* ICUSARB Register bit definitions */
#define R_CPSCU_ICUSARB_SANMI_S                   (1 << 0)  /* Security Attributes of registers */

#define R_CPSCU_ICUSARB_SANMI0                    (1 << 0)  /* Security Attributes of registers */

#define R_CPSCU_ICUSARB_SANMI1                    (1 << 1)  /* Security Attributes of registers */

#define R_CPSCU_ICUSARB_SANMI2                    (1 << 2)  /* Security Attributes of registers */

/* ICUSARC Register bit definitions */
#define R_CPSCU_ICUSARC_SADMACN_SHIFT             (0)  /* Security Attributes of registers for DMAC channel */
#define R_CPSCU_ICUSARC_SADMACN_MASK              0xff

#define R_CPSCU_ICUSARC_SADMACN_SHIFT             (0)  /* Security Attributes of registers for DMAC channel */
#define R_CPSCU_ICUSARC_SADMACN_MASK              0xff

/* ICUSARD Register bit definitions */
#define R_CPSCU_ICUSARD_SASELSR0                  (1 << 0)  /* Security Attributes of registers for SELSR0 */

/* ICUSARE Register bit definitions */
#define R_CPSCU_ICUSARE_SAIWDTWUP                 (1 << 16)  /* Security attributes of registers for WUPEN0.b16 */

#define R_CPSCU_ICUSARE_SALVD1WUP                 (1 << 18)  /* Security Attributes of registers for WUPEN0.b18 */

#define R_CPSCU_ICUSARE_SALVD2WUP                 (1 << 19)  /* Security Attributes of registers for WUPEN0.b19 */

#define R_CPSCU_ICUSARE_SAVBATTWUP                (1 << 20)  /* Security attributes of registers for WUPEN0.b20 */

#define R_CPSCU_ICUSARE_SARTCALMWUP               (1 << 24)  /* Security attributes of registers for WUPEN0.b24 */

#define R_CPSCU_ICUSARE_SARTCPRDWUP               (1 << 25)  /* Security attributes of registers for WUPEN0.b25 */

#define R_CPSCU_ICUSARE_SAUSBFS0WUP               (1 << 27)  /* Security attributes of registers for WUPEN0.b27 */

#define R_CPSCU_ICUSARE_SAAGT1UDWUP               (1 << 28)  /* Security attributes of registers for WUPEN0.b28 */

#define R_CPSCU_ICUSARE_SAAGT1CAWUP               (1 << 29)  /* Security attributes of registers for WUPEN0.b29 */

#define R_CPSCU_ICUSARE_SAAGT1CBWUP               (1 << 30)  /* Security attributes of registers for WUPEN0.b30 */

#define R_CPSCU_ICUSARE_SAIIC0WUP                 (1 << 31)  /* Security attributes of registers for WUPEN0.b31 */

/* ICUSARF Register bit definitions */
#define R_CPSCU_ICUSARF_SAAGT3UDWUP               (1 << 0)  /* Security Attributes of registers for WUPEN1.b 0 */

#define R_CPSCU_ICUSARF_SAAGT3CAWUP               (1 << 1)  /* Security Attributes of registers for WUPEN1.b 1 */

#define R_CPSCU_ICUSARF_SAAGT3CBWUP               (1 << 2)  /* Security Attributes of registers for WUPEN1.b 2 */

#define R_CPSCU_ICUSARF_SACOMPHS0WUP              (1 << 3)  /* Security attributes of registers for WUPEN1.b3 */

#define R_CPSCU_ICUSARF_SASOSCWUP                 (1 << 7)  /* Security attributes of registers for WUPEN1.b7 */

#define R_CPSCU_ICUSARF_SAULP0UWUP                (1 << 8)  /* Security attributes of registers for WUPEN1.b8 */

#define R_CPSCU_ICUSARF_SAULP0AWUP                (1 << 9)  /* Security attributes of registers for WUPEN1.b9 */

#define R_CPSCU_ICUSARF_SAULP0BWUP                (1 << 10)  /* Security attributes of registers for WUPEN1.b10 */

#define R_CPSCU_ICUSARF_SAI3CWUP                  (1 << 11)  /* Security attributes of registers for WUPEN1.b11 */

#define R_CPSCU_ICUSARF_SAULP1UWUP                (1 << 12)  /* Security attributes of registers for WUPEN1.b12 */

#define R_CPSCU_ICUSARF_SAULP1AWUP                (1 << 13)  /* Security attributes of registers for WUPEN1.b13 */

#define R_CPSCU_ICUSARF_SAULP1BWUP                (1 << 14)  /* Security attributes of registers for WUPEN1.b14 */

#define R_CPSCU_ICUSARF_SAPDMWUP                  (1 << 15)  /* Security attributes of registers for WUPEN1.b15 */

/* ICUSARG Register bit definitions */
#define R_CPSCU_ICUSARG_SAIELSR_S                 (1 << 0)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR0                  (1 << 0)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR1                  (1 << 1)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR2                  (1 << 2)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR3                  (1 << 3)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR4                  (1 << 4)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR5                  (1 << 5)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR6                  (1 << 6)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR7                  (1 << 7)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR8                  (1 << 8)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR9                  (1 << 9)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR10                 (1 << 10)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR11                 (1 << 11)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR12                 (1 << 12)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR13                 (1 << 13)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR14                 (1 << 14)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR15                 (1 << 15)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR16                 (1 << 16)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR17                 (1 << 17)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR18                 (1 << 18)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR19                 (1 << 19)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR20                 (1 << 20)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR21                 (1 << 21)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR22                 (1 << 22)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR23                 (1 << 23)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR24                 (1 << 24)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR25                 (1 << 25)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR26                 (1 << 26)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR27                 (1 << 27)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR28                 (1 << 28)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR29                 (1 << 29)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR30                 (1 << 30)  /* Security attributes of registers for ICU0 event link setting0 */

#define R_CPSCU_ICUSARG_SAIELSR31                 (1 << 31)  /* Security attributes of registers for ICU0 event link setting0 */

/* ICUSARH Register bit definitions */
#define R_CPSCU_ICUSARH_SAIELSR_S                 (1 << 0)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR32                 (1 << 0)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR33                 (1 << 1)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR34                 (1 << 2)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR35                 (1 << 3)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR36                 (1 << 4)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR37                 (1 << 5)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR38                 (1 << 6)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR39                 (1 << 7)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR40                 (1 << 8)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR41                 (1 << 9)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR42                 (1 << 10)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR43                 (1 << 11)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR44                 (1 << 12)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR45                 (1 << 13)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR46                 (1 << 14)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR47                 (1 << 15)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR48                 (1 << 16)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR49                 (1 << 17)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR50                 (1 << 18)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR51                 (1 << 19)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR52                 (1 << 20)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR53                 (1 << 21)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR54                 (1 << 22)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR55                 (1 << 23)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR56                 (1 << 24)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR57                 (1 << 25)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR58                 (1 << 26)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR59                 (1 << 27)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR60                 (1 << 28)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR61                 (1 << 29)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR62                 (1 << 30)  /* Security attributes of registers for ICU0 event link setting1 */

#define R_CPSCU_ICUSARH_SAIELSR63                 (1 << 31)  /* Security attributes of registers for ICU0 event link setting1 */

/* ICUSARI Register bit definitions */
#define R_CPSCU_ICUSARI_SAIELSR_S                 (1 << 0)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR64                 (1 << 0)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR65                 (1 << 1)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR66                 (1 << 2)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR67                 (1 << 3)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR68                 (1 << 4)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR69                 (1 << 5)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR70                 (1 << 6)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR71                 (1 << 7)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR72                 (1 << 8)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR73                 (1 << 9)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR74                 (1 << 10)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR75                 (1 << 11)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR76                 (1 << 12)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR77                 (1 << 13)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR78                 (1 << 14)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR79                 (1 << 15)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR80                 (1 << 16)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR81                 (1 << 17)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR82                 (1 << 18)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR83                 (1 << 19)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR84                 (1 << 20)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR85                 (1 << 21)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR86                 (1 << 22)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR87                 (1 << 23)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR88                 (1 << 24)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR89                 (1 << 25)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR90                 (1 << 26)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR91                 (1 << 27)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR92                 (1 << 28)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR93                 (1 << 29)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR94                 (1 << 30)  /* Security attributes of registers for ICU0 event link setting2 */

#define R_CPSCU_ICUSARI_SAIELSR95                 (1 << 31)  /* Security attributes of registers for ICU0 event link setting2 */

/* ICUSARJ Register bit definitions */
#define R_CPSCU_ICUSARJ_SAIELSR_S                 (1 << 0)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR0                  (1 << 0)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR1                  (1 << 1)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR2                  (1 << 2)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR3                  (1 << 3)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR4                  (1 << 4)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR5                  (1 << 5)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR6                  (1 << 6)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR7                  (1 << 7)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR8                  (1 << 8)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR9                  (1 << 9)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR10                 (1 << 10)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR11                 (1 << 11)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR12                 (1 << 12)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR13                 (1 << 13)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR14                 (1 << 14)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR15                 (1 << 15)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR16                 (1 << 16)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR17                 (1 << 17)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR18                 (1 << 18)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR19                 (1 << 19)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR20                 (1 << 20)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR21                 (1 << 21)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR22                 (1 << 22)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR23                 (1 << 23)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR24                 (1 << 24)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR25                 (1 << 25)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR26                 (1 << 26)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR27                 (1 << 27)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR28                 (1 << 28)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR29                 (1 << 29)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR30                 (1 << 30)  /* Security attributes of registers for ICU1 event link setting0 */

#define R_CPSCU_ICUSARJ_SAIELSR31                 (1 << 31)  /* Security attributes of registers for ICU1 event link setting0 */

/* ICUSARK Register bit definitions */
#define R_CPSCU_ICUSARK_SAIELSR_S                 (1 << 0)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR32                 (1 << 0)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR33                 (1 << 1)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR34                 (1 << 2)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR35                 (1 << 3)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR36                 (1 << 4)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR37                 (1 << 5)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR38                 (1 << 6)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR39                 (1 << 7)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR40                 (1 << 8)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR41                 (1 << 9)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR42                 (1 << 10)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR43                 (1 << 11)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR44                 (1 << 12)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR45                 (1 << 13)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR46                 (1 << 14)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR47                 (1 << 15)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR48                 (1 << 16)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR49                 (1 << 17)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR50                 (1 << 18)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR51                 (1 << 19)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR52                 (1 << 20)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR53                 (1 << 21)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR54                 (1 << 22)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR55                 (1 << 23)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR56                 (1 << 24)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR57                 (1 << 25)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR58                 (1 << 26)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR59                 (1 << 27)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR60                 (1 << 28)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR61                 (1 << 29)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR62                 (1 << 30)  /* Security attributes of registers for ICU1 event link setting1 */

#define R_CPSCU_ICUSARK_SAIELSR63                 (1 << 31)  /* Security attributes of registers for ICU1 event link setting1 */

/* ICUSARL Register bit definitions */
#define R_CPSCU_ICUSARL_SAIELSR_S                 (1 << 0)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR64                 (1 << 0)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR65                 (1 << 1)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR66                 (1 << 2)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR67                 (1 << 3)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR68                 (1 << 4)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR69                 (1 << 5)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR70                 (1 << 6)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR71                 (1 << 7)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR72                 (1 << 8)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR73                 (1 << 9)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR74                 (1 << 10)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR75                 (1 << 11)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR76                 (1 << 12)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR77                 (1 << 13)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR78                 (1 << 14)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR79                 (1 << 15)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR80                 (1 << 16)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR81                 (1 << 17)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR82                 (1 << 18)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR83                 (1 << 19)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR84                 (1 << 20)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR85                 (1 << 21)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR86                 (1 << 22)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR87                 (1 << 23)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR88                 (1 << 24)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR89                 (1 << 25)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR90                 (1 << 26)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR91                 (1 << 27)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR92                 (1 << 28)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR93                 (1 << 29)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR94                 (1 << 30)  /* Security attributes of registers for ICU1 event link setting2 */

#define R_CPSCU_ICUSARL_SAIELSR95                 (1 << 31)  /* Security attributes of registers for ICU1 event link setting2 */

/* BUSSARA Register bit definitions */
#define R_CPSCU_BUSSARA_BUSSA0                    (1 << 0)  /* Bus Security Attribution A0 */

/* BUSSARB Register bit definitions */
#define R_CPSCU_BUSSARB_BUSSB0                    (1 << 0)  /* Bus Security Attribution B0 */

/* BUSSARC Register bit definitions */
#define R_CPSCU_BUSSARC_BUSSC0                    (1 << 0)  /* Bus Security Attribution C0 */

/* BUSPARC Register bit definitions */
#define R_CPSCU_BUSPARC_BUSPA0                    (1 << 0)  /* External bus controller privilege attribution */

/* NMISR Register bit definitions */
#define R_CPSCU_NMISR_IWDTST                      (1 << 0)  /* IWDT Underflow/Refresh Error Interrupt Status Flag */

#define R_CPSCU_NMISR_WDTST                       (1 << 1)  /* WDT Underflow/Refresh Error Interrupt Status Flag */

#define R_CPSCU_NMISR_PVD1ST                      (1 << 2)  /* Voltage Monitor 1 Interrupt Status Flag */

#define R_CPSCU_NMISR_PVD2ST                      (1 << 3)  /* Voltage Monitor 2 Interrupt Status Flag */

#define R_CPSCU_NMISR_SOSTST                      (1 << 5)  /* Sub Oscillation Stop Detection Interrupt Status Flag */

#define R_CPSCU_NMISR_OSTST                       (1 << 6)  /* Main Clock Oscillation Stop Detection Interrupt Status Flag */

#define R_CPSCU_NMISR_NMIST                       (1 << 7)  /* NMI Pin Interrupt Status Flag */

#define R_CPSCU_NMISR_BUSST                       (1 << 12)  /* Bus Error Interrupt Status Flag */

#define R_CPSCU_NMISR_CMST                        (1 << 13)  /* Common Memory Error Interrupt Status Flag */

#define R_CPSCU_NMISR_LMST                        (1 << 14)  /* Local Memory Error Interrupt Status Flag */

#define R_CPSCU_NMISR_LUST                        (1 << 15)  /* LockUp Error Interrupt Status Flag */

#define R_CPSCU_NMISR_FPUEXCST                    (1 << 16)  /* FPU Exception Interrupt Status Flag */

#define R_CPSCU_NMISR_MRCRDST                     (1 << 17)  /* MRAM MRC read Error Interrupt Status Flag */

#define R_CPSCU_NMISR_MRERDST                     (1 << 18)  /* MRAM MRE read Error Interrupt Status Flag */

#define R_CPSCU_NMISR_IPCST                       (1 << 20)  /* IPC NMI CPU mutual Interrupt Status Flag */

/* MMPUSARA Register bit definitions */
#define R_CPSCU_MMPUSARA_MMPUASA_S                (1 << 0)  /* MMPUA%s Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA0                 (1 << 0)  /* MMPUA0 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA1                 (1 << 1)  /* MMPUA1 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA2                 (1 << 2)  /* MMPUA2 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA3                 (1 << 3)  /* MMPUA3 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA4                 (1 << 4)  /* MMPUA4 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA5                 (1 << 5)  /* MMPUA5 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA6                 (1 << 6)  /* MMPUA6 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA7                 (1 << 7)  /* MMPUA7 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA8                 (1 << 8)  /* MMPUA8 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA9                 (1 << 9)  /* MMPUA9 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA10                (1 << 10)  /* MMPUA10 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA11                (1 << 11)  /* MMPUA11 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA12                (1 << 12)  /* MMPUA12 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA13                (1 << 13)  /* MMPUA13 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA14                (1 << 14)  /* MMPUA14 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA15                (1 << 15)  /* MMPUA15 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA16                (1 << 16)  /* MMPUA16 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA17                (1 << 17)  /* MMPUA17 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA18                (1 << 18)  /* MMPUA18 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA19                (1 << 19)  /* MMPUA19 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA20                (1 << 20)  /* MMPUA20 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA21                (1 << 21)  /* MMPUA21 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA22                (1 << 22)  /* MMPUA22 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA23                (1 << 23)  /* MMPUA23 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA24                (1 << 24)  /* MMPUA24 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA25                (1 << 25)  /* MMPUA25 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA26                (1 << 26)  /* MMPUA26 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA27                (1 << 27)  /* MMPUA27 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA28                (1 << 28)  /* MMPUA28 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA29                (1 << 29)  /* MMPUA29 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA30                (1 << 30)  /* MMPUA30 Security Attribution */

#define R_CPSCU_MMPUSARA_MMPUASA31                (1 << 31)  /* MMPUA31 Security Attribution */

/* MMPUSARB Register bit definitions */
#define R_CPSCU_MMPUSARB_MMPUBSA_S                (1 << 0)  /* MMPUB%s Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA0                 (1 << 0)  /* MMPUB0 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA1                 (1 << 1)  /* MMPUB1 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA2                 (1 << 2)  /* MMPUB2 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA3                 (1 << 3)  /* MMPUB3 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA4                 (1 << 4)  /* MMPUB4 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA5                 (1 << 5)  /* MMPUB5 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA6                 (1 << 6)  /* MMPUB6 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA7                 (1 << 7)  /* MMPUB7 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA8                 (1 << 8)  /* MMPUB8 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA9                 (1 << 9)  /* MMPUB9 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA10                (1 << 10)  /* MMPUB10 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA11                (1 << 11)  /* MMPUB11 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA12                (1 << 12)  /* MMPUB12 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA13                (1 << 13)  /* MMPUB13 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA14                (1 << 14)  /* MMPUB14 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA15                (1 << 15)  /* MMPUB15 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA16                (1 << 16)  /* MMPUB16 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA17                (1 << 17)  /* MMPUB17 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA18                (1 << 18)  /* MMPUB18 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA19                (1 << 19)  /* MMPUB19 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA20                (1 << 20)  /* MMPUB20 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA21                (1 << 21)  /* MMPUB21 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA22                (1 << 22)  /* MMPUB22 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA23                (1 << 23)  /* MMPUB23 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA24                (1 << 24)  /* MMPUB24 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA25                (1 << 25)  /* MMPUB25 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA26                (1 << 26)  /* MMPUB26 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA27                (1 << 27)  /* MMPUB27 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA28                (1 << 28)  /* MMPUB28 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA29                (1 << 29)  /* MMPUB29 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA30                (1 << 30)  /* MMPUB30 Security Attribution */

#define R_CPSCU_MMPUSARB_MMPUBSA31                (1 << 31)  /* MMPUB31 Security Attribution */

/* CPUSAR Register bit definitions */
#define R_CPSCU_CPUSAR_CPUSA_S                    (1 << 0)  /* CPU Security Attribution %s */

#define R_CPSCU_CPUSAR_CPUSA0                     (1 << 0)  /* CPU Security Attribution 0 */

#define R_CPSCU_CPUSAR_CPUSA1                     (1 << 1)  /* CPU Security Attribution 1 */

/* DEBUGSAR Register bit definitions */
#define R_CPSCU_DEBUGSAR_DBGSA0                   (1 << 0)  /* Debug Security Attribution 0 */

/* DMACCHSAR Register bit definitions */
#define R_CPSCU_DMACCHSAR_SADMAC0_S               (1 << 0)  /* Security attributes of registers for DMAC0 channel */

#define R_CPSCU_DMACCHSAR_SADMAC1_S               (1 << 16)  /* Security attributes of registers for DMAC1 channel */

#define R_CPSCU_DMACCHSAR_SADMAC00                (1 << 0)  /* Security attributes of registers for DMAC0 channel */

#define R_CPSCU_DMACCHSAR_SADMAC01                (1 << 1)  /* Security attributes of registers for DMAC0 channel */

#define R_CPSCU_DMACCHSAR_SADMAC02                (1 << 2)  /* Security attributes of registers for DMAC0 channel */

#define R_CPSCU_DMACCHSAR_SADMAC03                (1 << 3)  /* Security attributes of registers for DMAC0 channel */

#define R_CPSCU_DMACCHSAR_SADMAC04                (1 << 4)  /* Security attributes of registers for DMAC0 channel */

#define R_CPSCU_DMACCHSAR_SADMAC05                (1 << 5)  /* Security attributes of registers for DMAC0 channel */

#define R_CPSCU_DMACCHSAR_SADMAC06                (1 << 6)  /* Security attributes of registers for DMAC0 channel */

#define R_CPSCU_DMACCHSAR_SADMAC07                (1 << 7)  /* Security attributes of registers for DMAC0 channel */

#define R_CPSCU_DMACCHSAR_SADMAC10                (1 << 16)  /* Security attributes of registers for DMAC1 channel */

#define R_CPSCU_DMACCHSAR_SADMAC11                (1 << 17)  /* Security attributes of registers for DMAC1 channel */

#define R_CPSCU_DMACCHSAR_SADMAC12                (1 << 18)  /* Security attributes of registers for DMAC1 channel */

#define R_CPSCU_DMACCHSAR_SADMAC13                (1 << 19)  /* Security attributes of registers for DMAC1 channel */

#define R_CPSCU_DMACCHSAR_SADMAC14                (1 << 20)  /* Security attributes of registers for DMAC1 channel */

#define R_CPSCU_DMACCHSAR_SADMAC15                (1 << 21)  /* Security attributes of registers for DMAC1 channel */

#define R_CPSCU_DMACCHSAR_SADMAC16                (1 << 22)  /* Security attributes of registers for DMAC1 channel */

#define R_CPSCU_DMACCHSAR_SADMAC17                (1 << 23)  /* Security attributes of registers for DMAC1 channel */

/* CPUDSAR Register bit definitions */
#define R_CPSCU_CPUDSAR_CPUDSA0                   (1 << 0)  /* CPU Debug Security Attribution 0 */

/* DMACCHPAR Register bit definitions */
#define R_CPSCU_DMACCHPAR_PADMAC0_S               (1 << 0)  /* Privilege attributes of outputs and registers for DMAC0 channel */

#define R_CPSCU_DMACCHPAR_PADMAC1_S               (1 << 16)  /* Privilege attributes of outputs and registers for DMAC1 channel */

#define R_CPSCU_DMACCHPAR_PADMAC00                (1 << 0)  /* Privilege attributes of outputs and registers for DMAC0 channel */

#define R_CPSCU_DMACCHPAR_PADMAC01                (1 << 1)  /* Privilege attributes of outputs and registers for DMAC0 channel */

#define R_CPSCU_DMACCHPAR_PADMAC02                (1 << 2)  /* Privilege attributes of outputs and registers for DMAC0 channel */

#define R_CPSCU_DMACCHPAR_PADMAC03                (1 << 3)  /* Privilege attributes of outputs and registers for DMAC0 channel */

#define R_CPSCU_DMACCHPAR_PADMAC04                (1 << 4)  /* Privilege attributes of outputs and registers for DMAC0 channel */

#define R_CPSCU_DMACCHPAR_PADMAC05                (1 << 5)  /* Privilege attributes of outputs and registers for DMAC0 channel */

#define R_CPSCU_DMACCHPAR_PADMAC06                (1 << 6)  /* Privilege attributes of outputs and registers for DMAC0 channel */

#define R_CPSCU_DMACCHPAR_PADMAC07                (1 << 7)  /* Privilege attributes of outputs and registers for DMAC0 channel */

#define R_CPSCU_DMACCHPAR_PADMAC10                (1 << 16)  /* Privilege attributes of outputs and registers for DMAC1 channel */

#define R_CPSCU_DMACCHPAR_PADMAC11                (1 << 17)  /* Privilege attributes of outputs and registers for DMAC1 channel */

#define R_CPSCU_DMACCHPAR_PADMAC12                (1 << 18)  /* Privilege attributes of outputs and registers for DMAC1 channel */

#define R_CPSCU_DMACCHPAR_PADMAC13                (1 << 19)  /* Privilege attributes of outputs and registers for DMAC1 channel */

#define R_CPSCU_DMACCHPAR_PADMAC14                (1 << 20)  /* Privilege attributes of outputs and registers for DMAC1 channel */

#define R_CPSCU_DMACCHPAR_PADMAC15                (1 << 21)  /* Privilege attributes of outputs and registers for DMAC1 channel */

#define R_CPSCU_DMACCHPAR_PADMAC16                (1 << 22)  /* Privilege attributes of outputs and registers for DMAC1 channel */

#define R_CPSCU_DMACCHPAR_PADMAC17                (1 << 23)  /* Privilege attributes of outputs and registers for DMAC1 channel */

/* SRAMSABAR Register bit definitions */
#define R_CPSCU_SRAMSABAR_SRAMSABAR_SHIFT         (13)  /* Boundary address between secure and non-secure */
#define R_CPSCU_SRAMSABAR_SRAMSABAR_MASK          0x1fe000

/* CACHESAR Register bit definitions */
#define R_CPSCU_CACHESAR_CACHESA                  (1 << 0)  /* Security attributes of registers for CACHE Control */

#define R_CPSCU_CACHESAR_CACHEESA                 (1 << 2)  /* Security attributes of registers for CACHE Error */

/* TCMSAR Register bit definitions */
#define R_CPSCU_TCMSAR_TCMSA                      (1 << 0)  /* Security attributes of registers for TCM Control */

/* TCMSABAR Register bit definitions */
#define R_CPSCU_TCMSABAR_TCMSABA_SHIFT            (13)  /* Boundary address between secure and non-secure. (Start address of non-secure region) */
#define R_CPSCU_TCMSABAR_TCMSABA_MASK             0x7e000

/* SRAMESAR Register bit definitions */
#define R_CPSCU_SRAMESAR_SRAMESA                  (1 << 0)  /* ECC region Security Attribution */

/* TEVTRCR Register bit definitions */
#define R_CPSCU_TEVTRCR_TEVTE                     (1 << 0)  /* Trusted Event Route Control Register for ELC */

#define R_CPSCU_TEVTRCR_TEVTEICU_S                (1 << 1)  /* Trusted Event Route Control Register for ICU%s */

#define R_CPSCU_TEVTRCR_TEVTEICU0                 (1 << 1)  /* Trusted Event Route Control Register for ICU0 */

#define R_CPSCU_TEVTRCR_TEVTEICU1                 (1 << 2)  /* Trusted Event Route Control Register for ICU1 */

/* IPCSAR Register bit definitions */
#define R_CPSCU_IPCSAR_SAIPCSEM_S                 (1 << 0)  /* Security attributes of registers for IPCSEMn */

#define R_CPSCU_IPCSAR_SAIPCNMI_S                 (1 << 8)  /* Security attributes of the registers */

#define R_CPSCU_IPCSAR_SAIPCIR0                   (1 << 16)  /* Security attributes of registers for IPC0STA0, IPC0ISET0, IPC0TXD0, IPC0RXD0 and IPC0CLR0 */

#define R_CPSCU_IPCSAR_SAIPCIR1                   (1 << 17)  /* Security attributes of registers for IPC0STA1, IPC0ISET1, IPC0TXD1, IPC0RXD1 and IPC0CLR1 */

#define R_CPSCU_IPCSAR_SAIPCIR2                   (1 << 18)  /* Security attributes of registers for IPC1STA0, IPC1ISET0, IPC1TXD0, IPC1RXD0 and IPC1CLR0 */

#define R_CPSCU_IPCSAR_SAIPCIR3                   (1 << 19)  /* Security attributes of registers for IPC1STA1, IPC1ISET1, IPC1TXD1, IPC1RXD1 and IPC1CLR1 */

#define R_CPSCU_IPCSAR_SAIPCSEM0                  (1 << 0)  /* Security attributes of registers for IPCSEMn */

#define R_CPSCU_IPCSAR_SAIPCSEM1                  (1 << 1)  /* Security attributes of registers for IPCSEMn */

#define R_CPSCU_IPCSAR_SAIPCNMI0                  (1 << 8)  /* Security attributes of the registers */

#define R_CPSCU_IPCSAR_SAIPCNMI1                  (1 << 9)  /* Security attributes of the registers */

/* IPCPAR Register bit definitions */
#define R_CPSCU_IPCPAR_PAIPCSEM_S                 (1 << 0)  /* Privileged attributes of registers for IPCSEMn */

#define R_CPSCU_IPCPAR_PAIPCNMI_S                 (1 << 8)  /* Privileged attributes of registers */

#define R_CPSCU_IPCPAR_PAIPCIR0                   (1 << 16)  /* Privileged attributes of registers for IPC0STA0, IPC0ISET0, IPC0TXD0, IPC0RXD0 and IPC0CLR0 */

#define R_CPSCU_IPCPAR_PAIPCIR1                   (1 << 17)  /* Privileged attributes of registers for IPC0STA1, IPC0ISET1, IPC0TXD1, IPC0RXD1 and IPC0CLR1 */

#define R_CPSCU_IPCPAR_PAIPCIR2                   (1 << 18)  /* Privileged attributes of registers for IPC1STA0, IPC1ISET0, IPC1TXD0, IPC1RXD0 and IPC1CLR0 */

#define R_CPSCU_IPCPAR_PAIPCIR3                   (1 << 19)  /* Privileged attributes of registers for IPC1STA1, IPC1ISET1, IPC1TXD1, IPC1RXD1 and IPC1CLR1 */

#define R_CPSCU_IPCPAR_PAIPCSEM0                  (1 << 0)  /* Privileged attributes of registers for IPCSEMn */

#define R_CPSCU_IPCPAR_PAIPCSEM1                  (1 << 1)  /* Privileged attributes of registers for IPCSEMn */

#define R_CPSCU_IPCPAR_PAIPCNMI0                  (1 << 8)  /* Privileged attributes of registers */

#define R_CPSCU_IPCPAR_PAIPCNMI1                  (1 << 9)  /* Privileged attributes of registers */


/* Maximum number of channels */

#define CPSCU_MAX_CHANNELS    4

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CPSCU_H */

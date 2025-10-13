/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8e1/ra_cpscu.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_CPSCU_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_CPSCU_H

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

#define R_CPSCU_SRAMSAR_OFFSET                    0x00000010  /* SRAM Security Attribution Register */
#define R_CPSCU_DTCSAR_OFFSET                     0x00000030  /* DTC Controller Security Attribution Register */
#define R_CPSCU_DMACSAR_OFFSET                    0x00000034  /* DMAC Controller Security Attribution Register */
#define R_CPSCU_ICUSARA_OFFSET                    0x00000040  /* Interrupt Controller Unit Security Attribution Register A */
#define R_CPSCU_ICUSARB_OFFSET                    0x00000044  /* Interrupt Controller Unit Security Attribution Register B */
#define R_CPSCU_ICUSARE_OFFSET                    0x00000050  /* Interrupt Controller Unit Security Attribution Register E */
#define R_CPSCU_ICUSARF_OFFSET                    0x00000054  /* Interrupt Controller Unit Security Attribution Register F */
#define R_CPSCU_ICUSARG_OFFSET                    0x00000070  /* Interrupt Controller Unit Security Attribution Register G */
#define R_CPSCU_ICUSARH_OFFSET                    0x00000074  /* Interrupt Controller Unit Security Attribution Register H */
#define R_CPSCU_ICUSARI_OFFSET                    0x00000078  /* Interrupt Controller Unit Security Attribution Register I */
#define R_CPSCU_BUSSARA_OFFSET                    0x00000100  /* Bus Security Attribution Register A */
#define R_CPSCU_BUSSARB_OFFSET                    0x00000104  /* Bus Security Attribution Register B */
#define R_CPSCU_MMPUSARA_OFFSET                   0x00000130  /* Master Memory Protection Unit Security Attribution Register A */
#define R_CPSCU_MMPUSARB_OFFSET                   0x00000134  /* Master Memory Protection Unit Security Attribution Register B */
#define R_CPSCU_CPUSAR_OFFSET                     0x00000170  /* CPU Security Attribution Register */
#define R_CPSCU_DEBUGSAR_OFFSET                   0x00000180  /* Debug Security Attribution Register */
#define R_CPSCU_DMACCHSAR_OFFSET                  0x000001a0  /* DMA channel Security Attribution Register */
#define R_CPSCU_DMACCHPAR_OFFSET                  0x000001f0  /* DMA channel Privilege Attribution Register */
#define R_CPSCU_SRAMSABAR1_OFFSET                 0x00000404  /* SRAM Error Address Register */
#define R_CPSCU_STBRAMSABAR_OFFSET                0x00000420  /* Standby SRAM Security Attribute Boundary Address Register */
#define R_CPSCU_STBRAMPABAR_S_OFFSET              0x00000494  /* Standby SRAM Privilege Attribute Boundary Address Register for Secure */
#define R_CPSCU_TEVTRCR_OFFSET                    0x00000600  /* Trusted Event Route Control Register */

/* CPSCU Register Addresses */

#define R_CPSCU_SRAMSAR                           (R_CPSCU_BASE + R_CPSCU_SRAMSAR_OFFSET)
#define R_CPSCU_DTCSAR                            (R_CPSCU_BASE + R_CPSCU_DTCSAR_OFFSET)
#define R_CPSCU_DMACSAR                           (R_CPSCU_BASE + R_CPSCU_DMACSAR_OFFSET)
#define R_CPSCU_ICUSARA                           (R_CPSCU_BASE + R_CPSCU_ICUSARA_OFFSET)
#define R_CPSCU_ICUSARB                           (R_CPSCU_BASE + R_CPSCU_ICUSARB_OFFSET)
#define R_CPSCU_ICUSARE                           (R_CPSCU_BASE + R_CPSCU_ICUSARE_OFFSET)
#define R_CPSCU_ICUSARF                           (R_CPSCU_BASE + R_CPSCU_ICUSARF_OFFSET)
#define R_CPSCU_ICUSARG                           (R_CPSCU_BASE + R_CPSCU_ICUSARG_OFFSET)
#define R_CPSCU_ICUSARH                           (R_CPSCU_BASE + R_CPSCU_ICUSARH_OFFSET)
#define R_CPSCU_ICUSARI                           (R_CPSCU_BASE + R_CPSCU_ICUSARI_OFFSET)
#define R_CPSCU_BUSSARA                           (R_CPSCU_BASE + R_CPSCU_BUSSARA_OFFSET)
#define R_CPSCU_BUSSARB                           (R_CPSCU_BASE + R_CPSCU_BUSSARB_OFFSET)
#define R_CPSCU_MMPUSARA                          (R_CPSCU_BASE + R_CPSCU_MMPUSARA_OFFSET)
#define R_CPSCU_MMPUSARB                          (R_CPSCU_BASE + R_CPSCU_MMPUSARB_OFFSET)
#define R_CPSCU_CPUSAR                            (R_CPSCU_BASE + R_CPSCU_CPUSAR_OFFSET)
#define R_CPSCU_DEBUGSAR                          (R_CPSCU_BASE + R_CPSCU_DEBUGSAR_OFFSET)
#define R_CPSCU_DMACCHSAR                         (R_CPSCU_BASE + R_CPSCU_DMACCHSAR_OFFSET)
#define R_CPSCU_DMACCHPAR                         (R_CPSCU_BASE + R_CPSCU_DMACCHPAR_OFFSET)
#define R_CPSCU_SRAMSABAR1                        (R_CPSCU_BASE + R_CPSCU_SRAMSABAR1_OFFSET)
#define R_CPSCU_STBRAMSABAR                       (R_CPSCU_BASE + R_CPSCU_STBRAMSABAR_OFFSET)
#define R_CPSCU_STBRAMPABAR_S                     (R_CPSCU_BASE + R_CPSCU_STBRAMPABAR_S_OFFSET)
#define R_CPSCU_TEVTRCR                           (R_CPSCU_BASE + R_CPSCU_TEVTRCR_OFFSET)

/* Register bit definitions */
/* SRAMSAR Register bit definitions */
#define R_CPSCU_SRAMSAR_SRAMSA1                   (1 << 1)  /* SRAM1 Register Security Attribution */

#define R_CPSCU_SRAMSAR_STBRAMSA                  (1 << 7)  /* Standby SRAM Register Security Attribution */

#define R_CPSCU_SRAMSAR_SRAMWTSA                  (1 << 8)  /* SRAMWTSC Security Attribution */

#define R_CPSCU_SRAMSAR_SRAMSA0                   (1 << 0)  /* Security attributes of registers for SRAM Protection */

#define R_CPSCU_SRAMSAR_SRAMSA2                   (1 << 2)  /* Security attributes of registers for ECC Relation */

/* DTCSAR Register bit definitions */
#define R_CPSCU_DTCSAR_DTCSTSA                    (1 << 0)  /* DTC Security Attribution */

/* DMACSAR Register bit definitions */
#define R_CPSCU_DMACSAR_DMASTSA                   (1 << 0)  /* DMAST Security Attribution */

/* ICUSARA Register bit definitions */
#define R_CPSCU_ICUSARA_SAIRQCR00                 (1 << 0)  /* Security attributes of registers for the IRQCRn register */

#define R_CPSCU_ICUSARA_SAIRQCR01                 (1 << 1)  /* Security attributes of registers for the IRQCRn register */

#define R_CPSCU_ICUSARA_SAIRQCR02                 (1 << 2)  /* Security attributes of registers for the IRQCRn register */

#define R_CPSCU_ICUSARA_SAIRQCR03                 (1 << 3)  /* Security attributes of registers for the IRQCRn register */

#define R_CPSCU_ICUSARA_SAIRQCR04                 (1 << 4)  /* Security attributes of registers for the IRQCRn register */

#define R_CPSCU_ICUSARA_SAIRQCR05                 (1 << 5)  /* Security attributes of registers for the IRQCRn register */

#define R_CPSCU_ICUSARA_SAIRQCR06                 (1 << 6)  /* Security attributes of registers for the IRQCRn register */

#define R_CPSCU_ICUSARA_SAIRQCR07                 (1 << 7)  /* Security attributes of registers for the IRQCRn register */

#define R_CPSCU_ICUSARA_SAIRQCR08                 (1 << 8)  /* Security attributes of registers for the IRQCRn register */

#define R_CPSCU_ICUSARA_SAIRQCR09                 (1 << 9)  /* Security attributes of registers for the IRQCRn register */

#define R_CPSCU_ICUSARA_SAIRQCR10                 (1 << 10)  /* Security attributes of registers for the IRQCRn register */

#define R_CPSCU_ICUSARA_SAIRQCR11                 (1 << 11)  /* Security attributes of registers for the IRQCRn register */

#define R_CPSCU_ICUSARA_SAIRQCR12                 (1 << 12)  /* Security attributes of registers for the IRQCRn register */

#define R_CPSCU_ICUSARA_SAIRQCR13                 (1 << 13)  /* Security attributes of registers for the IRQCRn register */

#define R_CPSCU_ICUSARA_SAIRQCR14                 (1 << 14)  /* Security attributes of registers for the IRQCRn register */

#define R_CPSCU_ICUSARA_SAIRQCR15                 (1 << 15)  /* Security attributes of registers for the IRQCRn register */

#define R_CPSCU_ICUSARA_SAIRQCRN_SHIFT            (0)  /* Security Attributes of registers for the IRQCRn registers */
#define R_CPSCU_ICUSARA_SAIRQCRN_MASK             0xffff

/* ICUSARB Register bit definitions */
#define R_CPSCU_ICUSARB_SANMI                     (1 << 0)  /* Security attributes of registers for nonmaskable interrupt */

/* ICUSARE Register bit definitions */
#define R_CPSCU_ICUSARE_SAIWDTWUP                 (1 << 16)  /* Security attributes of registers for WUPEN0.b16 */

#define R_CPSCU_ICUSARE_SAPVD1WUP                 (1 << 18)  /* Security attributes of registers for WUPEN0.b18 */

#define R_CPSCU_ICUSARE_SAPVD2WUP                 (1 << 19)  /* Security attributes of registers for WUPEN0.b19 */

#define R_CPSCU_ICUSARE_SAVBATTWUP                (1 << 20)  /* Security attributes of registers for WUPEN0.b20 */

#define R_CPSCU_ICUSARE_SARTCALMWUP               (1 << 24)  /* Security attributes of registers for WUPEN0.b24 */

#define R_CPSCU_ICUSARE_SARTCPRDWUP               (1 << 25)  /* Security attributes of registers for WUPEN0.b25 */

#define R_CPSCU_ICUSARE_SAUSBFS0WUP               (1 << 27)  /* Security attributes of registers for WUPEN0.b27 */

#define R_CPSCU_ICUSARE_SAAGT1UDWUP               (1 << 28)  /* Security attributes of registers for WUPEN0.b28 */

#define R_CPSCU_ICUSARE_SAAGT1CAWUP               (1 << 29)  /* Security attributes of registers for WUPEN0.b29 */

#define R_CPSCU_ICUSARE_SAAGT1CBWUP               (1 << 30)  /* Security attributes of registers for WUPEN0.b30 */

#define R_CPSCU_ICUSARE_SAIIC0WUP                 (1 << 31)  /* Security attributes of registers for WUPEN0.b31 */

#define R_CPSCU_ICUSARE_SALVD1WUP                 (1 << 18)  /* Security Attributes of registers for WUPEN0.b 18 */

#define R_CPSCU_ICUSARE_SALVD2WUP                 (1 << 19)  /* Security Attributes of registers for WUPEN0.b 19 */

#define R_CPSCU_ICUSARE_SAACMPLP0WUP              (1 << 23)  /* Security attributes of registers for WUPEN0.b 23 */

/* ICUSARF Register bit definitions */
#define R_CPSCU_ICUSARF_SACOMPHS0WUP              (1 << 3)  /* Security attributes of registers for WUPEN1.b3 */

#define R_CPSCU_ICUSARF_SAULP0UWUP                (1 << 8)  /* Security attributes of registers for WUPEN1.b8 */

#define R_CPSCU_ICUSARF_SAULP0AWUP                (1 << 9)  /* Security attributes of registers for WUPEN1.b9 */

#define R_CPSCU_ICUSARF_SAULP0BWUP                (1 << 10)  /* Security attributes of registers for WUPEN1.b10 */

#define R_CPSCU_ICUSARF_SAULP1UWUP                (1 << 12)  /* Security attributes of registers for WUPEN1.b12 */

#define R_CPSCU_ICUSARF_SAULP1AWUP                (1 << 13)  /* Security attributes of registers for WUPEN1.b13 */

#define R_CPSCU_ICUSARF_SAULP1BWUP                (1 << 14)  /* Security attributes of registers for WUPEN1.b14 */

#define R_CPSCU_ICUSARF_SAAGT3UDWUP               (1 << 0)  /* Security Attributes of registers for WUPEN1.b 0 */

#define R_CPSCU_ICUSARF_SAAGT3CAWUP               (1 << 1)  /* Security Attributes of registers for WUPEN1.b 1 */

#define R_CPSCU_ICUSARF_SAAGT3CBWUP               (1 << 2)  /* Security Attributes of registers for WUPEN1.b 2 */

#define R_CPSCU_ICUSARF_SASOSCWUP                 (1 << 7)  /* Security attributes of registers for WUPEN1.b 7 */

#define R_CPSCU_ICUSARF_SAI3CWUP                  (1 << 11)  /* Security Attributes of registers for WUPEN1.b 11 */

/* ICUSARG Register bit definitions */
#define R_CPSCU_ICUSARG_SAIELSR00                 (1 << 0)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR01                 (1 << 1)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR02                 (1 << 2)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR03                 (1 << 3)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR04                 (1 << 4)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR05                 (1 << 5)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR06                 (1 << 6)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR07                 (1 << 7)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR08                 (1 << 8)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR09                 (1 << 9)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR10                 (1 << 10)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR11                 (1 << 11)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR12                 (1 << 12)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR13                 (1 << 13)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR14                 (1 << 14)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR15                 (1 << 15)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR16                 (1 << 16)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR17                 (1 << 17)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR18                 (1 << 18)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR19                 (1 << 19)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR20                 (1 << 20)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR21                 (1 << 21)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR22                 (1 << 22)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR23                 (1 << 23)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR24                 (1 << 24)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR25                 (1 << 25)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR26                 (1 << 26)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR27                 (1 << 27)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR28                 (1 << 28)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR29                 (1 << 29)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR30                 (1 << 30)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSR31                 (1 << 31)  /* Security attributes of registers for IELSR31 to IELSR0 */

#define R_CPSCU_ICUSARG_SAIELSRN_SHIFT            (0)  /* Security Attributes of registers for IELSR31 to IELSR0 */
#define R_CPSCU_ICUSARG_SAIELSRN_MASK             0xffffffff

/* ICUSARH Register bit definitions */
#define R_CPSCU_ICUSARH_SAIELSR32                 (1 << 0)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR33                 (1 << 1)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR34                 (1 << 2)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR35                 (1 << 3)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR36                 (1 << 4)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR37                 (1 << 5)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR38                 (1 << 6)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR39                 (1 << 7)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR40                 (1 << 8)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR41                 (1 << 9)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR42                 (1 << 10)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR43                 (1 << 11)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR44                 (1 << 12)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR45                 (1 << 13)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR46                 (1 << 14)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR47                 (1 << 15)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR48                 (1 << 16)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR49                 (1 << 17)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR50                 (1 << 18)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR51                 (1 << 19)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR52                 (1 << 20)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR53                 (1 << 21)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR54                 (1 << 22)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR55                 (1 << 23)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR56                 (1 << 24)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR57                 (1 << 25)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR58                 (1 << 26)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR59                 (1 << 27)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR60                 (1 << 28)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR61                 (1 << 29)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR62                 (1 << 30)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSR63                 (1 << 31)  /* Security attributes of registers for IELSR63 to IELSR32 */

#define R_CPSCU_ICUSARH_SAIELSRN_SHIFT            (0)  /* Security Attributes of registers for IELSR63 to IELSR32 */
#define R_CPSCU_ICUSARH_SAIELSRN_MASK             0xffffffff

/* ICUSARI Register bit definitions */
#define R_CPSCU_ICUSARI_SAIELSR64                 (1 << 0)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR65                 (1 << 1)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR66                 (1 << 2)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR67                 (1 << 3)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR68                 (1 << 4)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR69                 (1 << 5)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR70                 (1 << 6)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR71                 (1 << 7)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR72                 (1 << 8)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR73                 (1 << 9)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR74                 (1 << 10)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR75                 (1 << 11)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR76                 (1 << 12)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR77                 (1 << 13)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR78                 (1 << 14)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR79                 (1 << 15)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR80                 (1 << 16)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR81                 (1 << 17)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR82                 (1 << 18)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR83                 (1 << 19)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR84                 (1 << 20)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR85                 (1 << 21)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR86                 (1 << 22)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR87                 (1 << 23)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR88                 (1 << 24)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR89                 (1 << 25)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR90                 (1 << 26)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR91                 (1 << 27)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR92                 (1 << 28)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR93                 (1 << 29)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR94                 (1 << 30)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSR95                 (1 << 31)  /* Security attributes of registers for IELSR95 to IELSR64 */

#define R_CPSCU_ICUSARI_SAIELSRN_SHIFT            (0)  /* Security Attributes of registers for IELSR95 to IELSR64 */
#define R_CPSCU_ICUSARI_SAIELSRN_MASK             0xffffffff

/* BUSSARA Register bit definitions */
#define R_CPSCU_BUSSARA_BUSSA0                    (1 << 0)  /* Bus Security Attribution A0 */

/* BUSSARB Register bit definitions */
#define R_CPSCU_BUSSARB_BUSSB0                    (1 << 0)  /* Bus Security Attribution B0 */

/* MMPUSARA Register bit definitions */
#define R_CPSCU_MMPUSARA_MMPUASAN_SHIFT           (0)  /* MMPUA Security Attribution n (n = 0 to 7) */
#define R_CPSCU_MMPUSARA_MMPUASAN_MASK            0xff
#  define R_CPSCU_MMPUSARA_MMPUASAN_0                     (0 << R_CPSCU_MMPUSARA_MMPUASAN_SHIFT)  /* Secure */
#  define R_CPSCU_MMPUSARA_MMPUASAN_1                     (1 << R_CPSCU_MMPUSARA_MMPUASAN_SHIFT)  /* Non-secure */

#define R_CPSCU_MMPUSARA_MMPUANSA_SHIFT           (0)  /* MMPUAn Security Attribution (n = 0 to 7) */
#define R_CPSCU_MMPUSARA_MMPUANSA_MASK            0xff

/* MMPUSARB Register bit definitions */
#define R_CPSCU_MMPUSARB_MMPUBSA0                 (1 << 0)  /* MMPUB Security Attribution 0 */

#define R_CPSCU_MMPUSARB_MMPUBSA8                 (1 << 8)  /* MMPUB Security Attribution 8 */

#define R_CPSCU_MMPUSARB_MMPUB0SA                 (1 << 0)  /* MMPUB0 Security Attribution */

/* CPUSAR Register bit definitions */
#define R_CPSCU_CPUSAR_CPUSA0                     (1 << 0)  /* CPU Control Registers Security Attribution */

/* DEBUGSAR Register bit definitions */
#define R_CPSCU_DEBUGSAR_DBGSA0                   (1 << 0)  /* Debug Resources Security Attribution 0 */

/* DMACCHSAR Register bit definitions */
#define R_CPSCU_DMACCHSAR_SADMAC0                 (1 << 0)  /* Security attributes of output and registers for DMAC channel */

#define R_CPSCU_DMACCHSAR_SADMAC1                 (1 << 1)  /* Security attributes of output and registers for DMAC channel */

#define R_CPSCU_DMACCHSAR_SADMAC2                 (1 << 2)  /* Security attributes of output and registers for DMAC channel */

#define R_CPSCU_DMACCHSAR_SADMAC3                 (1 << 3)  /* Security attributes of output and registers for DMAC channel */

#define R_CPSCU_DMACCHSAR_SADMAC4                 (1 << 4)  /* Security attributes of output and registers for DMAC channel */

#define R_CPSCU_DMACCHSAR_SADMAC5                 (1 << 5)  /* Security attributes of output and registers for DMAC channel */

#define R_CPSCU_DMACCHSAR_SADMAC6                 (1 << 6)  /* Security attributes of output and registers for DMAC channel */

#define R_CPSCU_DMACCHSAR_SADMAC7                 (1 << 7)  /* Security attributes of output and registers for DMAC channel */

#define R_CPSCU_DMACCHSAR_DMACCHSARN_SHIFT        (0)  /* Security attributes of output and registers for DMAC channel */
#define R_CPSCU_DMACCHSAR_DMACCHSARN_MASK         0xff

/* DMACCHPAR Register bit definitions */
#define R_CPSCU_DMACCHPAR_PADMAC0                 (1 << 0)  /* Privilege attributes of outputs and registers for DMAC channel */

#define R_CPSCU_DMACCHPAR_PADMAC1                 (1 << 1)  /* Privilege attributes of outputs and registers for DMAC channel */

#define R_CPSCU_DMACCHPAR_PADMAC2                 (1 << 2)  /* Privilege attributes of outputs and registers for DMAC channel */

#define R_CPSCU_DMACCHPAR_PADMAC3                 (1 << 3)  /* Privilege attributes of outputs and registers for DMAC channel */

#define R_CPSCU_DMACCHPAR_PADMAC4                 (1 << 4)  /* Privilege attributes of outputs and registers for DMAC channel */

#define R_CPSCU_DMACCHPAR_PADMAC5                 (1 << 5)  /* Privilege attributes of outputs and registers for DMAC channel */

#define R_CPSCU_DMACCHPAR_PADMAC6                 (1 << 6)  /* Privilege attributes of outputs and registers for DMAC channel */

#define R_CPSCU_DMACCHPAR_PADMAC7                 (1 << 7)  /* Privilege attributes of outputs and registers for DMAC channel */

/* SRAMSABAR1 Register bit definitions */
#define R_CPSCU_SRAMSABAR1_SRAMSABAR_SHIFT        (13)  /* Boundary address between secure and non-secure (Start address of non-secure region). */
#define R_CPSCU_SRAMSABAR1_SRAMSABAR_MASK         0x1fe000

/* TEVTRCR Register bit definitions */
#define R_CPSCU_TEVTRCR_TEVTE                     (1 << 0)  /* Trusted Event Route Control Register for IELSRn, DELSRn and ELCSRn */


/* Maximum number of channels */

#define CPSCU_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_CPSCU_H */

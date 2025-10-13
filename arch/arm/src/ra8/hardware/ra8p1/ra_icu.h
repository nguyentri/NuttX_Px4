/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_icu.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ICU_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ICU_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ICU Base Address */
#ifndef R_ICU_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_ICU_BASE           0x4000c000
#else
#define R_ICU_BASE           0x5000c000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_ICU_CH_STRIDE    0x00000004
#define R_ICU_CH_BASE(ch)   (R_ICU_BASE + ((uint32_t)(ch) * R_ICU_CH_STRIDE))

/* ICU Register Offsets */

#define R_ICU_NMIER_OFFSET     0x00000100  /* Non-Maskable Interrupt Enable Register */
#define R_ICU_NMICLR_OFFSET     0x00000110  /* Non-Maskable Interrupt Status Clear Register */
#define R_ICU_NMISR_OFFSET     0x00000120  /* Non-Maskable Interrupt Status Register */
#define R_ICU_WUPEN0_OFFSET     0x000001a0  /* Wake Up Interrupt Enable Register 0 */
#define R_ICU_WUPEN1_OFFSET     0x000001a4  /* Wake Up Interrupt Enable Register 1 */
#define R_ICU_DSLPWUPIRQEN0_OFFSET     0x00000214  /* Deep Sleep Wake Up IRQ Enable Register 0 */
#define R_ICU_DSLPWUPIRQEN1_OFFSET     0x00000218  /* Deep Sleep Wake Up IRQ Enable Register 1 */
#define R_ICU_DSLPWUPIRQEN2_OFFSET     0x0000021c  /* Deep Sleep Wake Up IRQ Enable Register 2 */
#define R_ICU_DELSRM_OFFSET     0x00000280  /* DMAC Event Link Setting Register m (m = 0 to 7) */
/* IELSR%s Registers (0-95) */
#define R_ICU_IELSR00_OFFSET     0x00000300  /* Interrupt Controller Unit Event Link Setting Register 00 */
#define R_ICU_IELSR01_OFFSET     0x00000304  /* Interrupt Controller Unit Event Link Setting Register 01 */
#define R_ICU_IELSR02_OFFSET     0x00000308  /* Interrupt Controller Unit Event Link Setting Register 02 */
#define R_ICU_IELSR03_OFFSET     0x0000030c  /* Interrupt Controller Unit Event Link Setting Register 03 */
#define R_ICU_IELSR04_OFFSET     0x00000310  /* Interrupt Controller Unit Event Link Setting Register 04 */
#define R_ICU_IELSR05_OFFSET     0x00000314  /* Interrupt Controller Unit Event Link Setting Register 05 */
#define R_ICU_IELSR06_OFFSET     0x00000318  /* Interrupt Controller Unit Event Link Setting Register 06 */
#define R_ICU_IELSR07_OFFSET     0x0000031c  /* Interrupt Controller Unit Event Link Setting Register 07 */
#define R_ICU_IELSR08_OFFSET     0x00000320  /* Interrupt Controller Unit Event Link Setting Register 08 */
#define R_ICU_IELSR09_OFFSET     0x00000324  /* Interrupt Controller Unit Event Link Setting Register 09 */
#define R_ICU_IELSR10_OFFSET     0x00000328  /* Interrupt Controller Unit Event Link Setting Register 10 */
#define R_ICU_IELSR11_OFFSET     0x0000032c  /* Interrupt Controller Unit Event Link Setting Register 11 */
#define R_ICU_IELSR12_OFFSET     0x00000330  /* Interrupt Controller Unit Event Link Setting Register 12 */
#define R_ICU_IELSR13_OFFSET     0x00000334  /* Interrupt Controller Unit Event Link Setting Register 13 */
#define R_ICU_IELSR14_OFFSET     0x00000338  /* Interrupt Controller Unit Event Link Setting Register 14 */
#define R_ICU_IELSR15_OFFSET     0x0000033c  /* Interrupt Controller Unit Event Link Setting Register 15 */
#define R_ICU_IELSR16_OFFSET     0x00000340  /* Interrupt Controller Unit Event Link Setting Register 16 */
#define R_ICU_IELSR17_OFFSET     0x00000344  /* Interrupt Controller Unit Event Link Setting Register 17 */
#define R_ICU_IELSR18_OFFSET     0x00000348  /* Interrupt Controller Unit Event Link Setting Register 18 */
#define R_ICU_IELSR19_OFFSET     0x0000034c  /* Interrupt Controller Unit Event Link Setting Register 19 */
#define R_ICU_IELSR20_OFFSET     0x00000350  /* Interrupt Controller Unit Event Link Setting Register 20 */
#define R_ICU_IELSR21_OFFSET     0x00000354  /* Interrupt Controller Unit Event Link Setting Register 21 */
#define R_ICU_IELSR22_OFFSET     0x00000358  /* Interrupt Controller Unit Event Link Setting Register 22 */
#define R_ICU_IELSR23_OFFSET     0x0000035c  /* Interrupt Controller Unit Event Link Setting Register 23 */
#define R_ICU_IELSR24_OFFSET     0x00000360  /* Interrupt Controller Unit Event Link Setting Register 24 */
#define R_ICU_IELSR25_OFFSET     0x00000364  /* Interrupt Controller Unit Event Link Setting Register 25 */
#define R_ICU_IELSR26_OFFSET     0x00000368  /* Interrupt Controller Unit Event Link Setting Register 26 */
#define R_ICU_IELSR27_OFFSET     0x0000036c  /* Interrupt Controller Unit Event Link Setting Register 27 */
#define R_ICU_IELSR28_OFFSET     0x00000370  /* Interrupt Controller Unit Event Link Setting Register 28 */
#define R_ICU_IELSR29_OFFSET     0x00000374  /* Interrupt Controller Unit Event Link Setting Register 29 */
#define R_ICU_IELSR30_OFFSET     0x00000378  /* Interrupt Controller Unit Event Link Setting Register 30 */
#define R_ICU_IELSR31_OFFSET     0x0000037c  /* Interrupt Controller Unit Event Link Setting Register 31 */
#define R_ICU_IELSR32_OFFSET     0x00000380  /* Interrupt Controller Unit Event Link Setting Register 32 */
#define R_ICU_IELSR33_OFFSET     0x00000384  /* Interrupt Controller Unit Event Link Setting Register 33 */
#define R_ICU_IELSR34_OFFSET     0x00000388  /* Interrupt Controller Unit Event Link Setting Register 34 */
#define R_ICU_IELSR35_OFFSET     0x0000038c  /* Interrupt Controller Unit Event Link Setting Register 35 */
#define R_ICU_IELSR36_OFFSET     0x00000390  /* Interrupt Controller Unit Event Link Setting Register 36 */
#define R_ICU_IELSR37_OFFSET     0x00000394  /* Interrupt Controller Unit Event Link Setting Register 37 */
#define R_ICU_IELSR38_OFFSET     0x00000398  /* Interrupt Controller Unit Event Link Setting Register 38 */
#define R_ICU_IELSR39_OFFSET     0x0000039c  /* Interrupt Controller Unit Event Link Setting Register 39 */
#define R_ICU_IELSR40_OFFSET     0x000003a0  /* Interrupt Controller Unit Event Link Setting Register 40 */
#define R_ICU_IELSR41_OFFSET     0x000003a4  /* Interrupt Controller Unit Event Link Setting Register 41 */
#define R_ICU_IELSR42_OFFSET     0x000003a8  /* Interrupt Controller Unit Event Link Setting Register 42 */
#define R_ICU_IELSR43_OFFSET     0x000003ac  /* Interrupt Controller Unit Event Link Setting Register 43 */
#define R_ICU_IELSR44_OFFSET     0x000003b0  /* Interrupt Controller Unit Event Link Setting Register 44 */
#define R_ICU_IELSR45_OFFSET     0x000003b4  /* Interrupt Controller Unit Event Link Setting Register 45 */
#define R_ICU_IELSR46_OFFSET     0x000003b8  /* Interrupt Controller Unit Event Link Setting Register 46 */
#define R_ICU_IELSR47_OFFSET     0x000003bc  /* Interrupt Controller Unit Event Link Setting Register 47 */
#define R_ICU_IELSR48_OFFSET     0x000003c0  /* Interrupt Controller Unit Event Link Setting Register 48 */
#define R_ICU_IELSR49_OFFSET     0x000003c4  /* Interrupt Controller Unit Event Link Setting Register 49 */
#define R_ICU_IELSR50_OFFSET     0x000003c8  /* Interrupt Controller Unit Event Link Setting Register 50 */
#define R_ICU_IELSR51_OFFSET     0x000003cc  /* Interrupt Controller Unit Event Link Setting Register 51 */
#define R_ICU_IELSR52_OFFSET     0x000003d0  /* Interrupt Controller Unit Event Link Setting Register 52 */
#define R_ICU_IELSR53_OFFSET     0x000003d4  /* Interrupt Controller Unit Event Link Setting Register 53 */
#define R_ICU_IELSR54_OFFSET     0x000003d8  /* Interrupt Controller Unit Event Link Setting Register 54 */
#define R_ICU_IELSR55_OFFSET     0x000003dc  /* Interrupt Controller Unit Event Link Setting Register 55 */
#define R_ICU_IELSR56_OFFSET     0x000003e0  /* Interrupt Controller Unit Event Link Setting Register 56 */
#define R_ICU_IELSR57_OFFSET     0x000003e4  /* Interrupt Controller Unit Event Link Setting Register 57 */
#define R_ICU_IELSR58_OFFSET     0x000003e8  /* Interrupt Controller Unit Event Link Setting Register 58 */
#define R_ICU_IELSR59_OFFSET     0x000003ec  /* Interrupt Controller Unit Event Link Setting Register 59 */
#define R_ICU_IELSR60_OFFSET     0x000003f0  /* Interrupt Controller Unit Event Link Setting Register 60 */
#define R_ICU_IELSR61_OFFSET     0x000003f4  /* Interrupt Controller Unit Event Link Setting Register 61 */
#define R_ICU_IELSR62_OFFSET     0x000003f8  /* Interrupt Controller Unit Event Link Setting Register 62 */
#define R_ICU_IELSR63_OFFSET     0x000003fc  /* Interrupt Controller Unit Event Link Setting Register 63 */
#define R_ICU_IELSR64_OFFSET     0x00000400  /* Interrupt Controller Unit Event Link Setting Register 64 */
#define R_ICU_IELSR65_OFFSET     0x00000404  /* Interrupt Controller Unit Event Link Setting Register 65 */
#define R_ICU_IELSR66_OFFSET     0x00000408  /* Interrupt Controller Unit Event Link Setting Register 66 */
#define R_ICU_IELSR67_OFFSET     0x0000040c  /* Interrupt Controller Unit Event Link Setting Register 67 */
#define R_ICU_IELSR68_OFFSET     0x00000410  /* Interrupt Controller Unit Event Link Setting Register 68 */
#define R_ICU_IELSR69_OFFSET     0x00000414  /* Interrupt Controller Unit Event Link Setting Register 69 */
#define R_ICU_IELSR70_OFFSET     0x00000418  /* Interrupt Controller Unit Event Link Setting Register 70 */
#define R_ICU_IELSR71_OFFSET     0x0000041c  /* Interrupt Controller Unit Event Link Setting Register 71 */
#define R_ICU_IELSR72_OFFSET     0x00000420  /* Interrupt Controller Unit Event Link Setting Register 72 */
#define R_ICU_IELSR73_OFFSET     0x00000424  /* Interrupt Controller Unit Event Link Setting Register 73 */
#define R_ICU_IELSR74_OFFSET     0x00000428  /* Interrupt Controller Unit Event Link Setting Register 74 */
#define R_ICU_IELSR75_OFFSET     0x0000042c  /* Interrupt Controller Unit Event Link Setting Register 75 */
#define R_ICU_IELSR76_OFFSET     0x00000430  /* Interrupt Controller Unit Event Link Setting Register 76 */
#define R_ICU_IELSR77_OFFSET     0x00000434  /* Interrupt Controller Unit Event Link Setting Register 77 */
#define R_ICU_IELSR78_OFFSET     0x00000438  /* Interrupt Controller Unit Event Link Setting Register 78 */
#define R_ICU_IELSR79_OFFSET     0x0000043c  /* Interrupt Controller Unit Event Link Setting Register 79 */
#define R_ICU_IELSR80_OFFSET     0x00000440  /* Interrupt Controller Unit Event Link Setting Register 80 */
#define R_ICU_IELSR81_OFFSET     0x00000444  /* Interrupt Controller Unit Event Link Setting Register 81 */
#define R_ICU_IELSR82_OFFSET     0x00000448  /* Interrupt Controller Unit Event Link Setting Register 82 */
#define R_ICU_IELSR83_OFFSET     0x0000044c  /* Interrupt Controller Unit Event Link Setting Register 83 */
#define R_ICU_IELSR84_OFFSET     0x00000450  /* Interrupt Controller Unit Event Link Setting Register 84 */
#define R_ICU_IELSR85_OFFSET     0x00000454  /* Interrupt Controller Unit Event Link Setting Register 85 */
#define R_ICU_IELSR86_OFFSET     0x00000458  /* Interrupt Controller Unit Event Link Setting Register 86 */
#define R_ICU_IELSR87_OFFSET     0x0000045c  /* Interrupt Controller Unit Event Link Setting Register 87 */
#define R_ICU_IELSR88_OFFSET     0x00000460  /* Interrupt Controller Unit Event Link Setting Register 88 */
#define R_ICU_IELSR89_OFFSET     0x00000464  /* Interrupt Controller Unit Event Link Setting Register 89 */
#define R_ICU_IELSR90_OFFSET     0x00000468  /* Interrupt Controller Unit Event Link Setting Register 90 */
#define R_ICU_IELSR91_OFFSET     0x0000046c  /* Interrupt Controller Unit Event Link Setting Register 91 */
#define R_ICU_IELSR92_OFFSET     0x00000470  /* Interrupt Controller Unit Event Link Setting Register 92 */
#define R_ICU_IELSR93_OFFSET     0x00000474  /* Interrupt Controller Unit Event Link Setting Register 93 */
#define R_ICU_IELSR94_OFFSET     0x00000478  /* Interrupt Controller Unit Event Link Setting Register 94 */
#define R_ICU_IELSR95_OFFSET     0x0000047c  /* Interrupt Controller Unit Event Link Setting Register 95 */

/* ICU Register Addresses */

#define R_ICU_NMIER                 (R_ICU_BASE + R_ICU_NMIER_OFFSET)
#define R_ICU_NMICLR                 (R_ICU_BASE + R_ICU_NMICLR_OFFSET)
#define R_ICU_NMISR                 (R_ICU_BASE + R_ICU_NMISR_OFFSET)
#define R_ICU_WUPEN0                 (R_ICU_BASE + R_ICU_WUPEN0_OFFSET)
#define R_ICU_WUPEN1                 (R_ICU_BASE + R_ICU_WUPEN1_OFFSET)
#define R_ICU_DSLPWUPIRQEN0                 (R_ICU_BASE + R_ICU_DSLPWUPIRQEN0_OFFSET)
#define R_ICU_DSLPWUPIRQEN1                 (R_ICU_BASE + R_ICU_DSLPWUPIRQEN1_OFFSET)
#define R_ICU_DSLPWUPIRQEN2                 (R_ICU_BASE + R_ICU_DSLPWUPIRQEN2_OFFSET)
#define R_ICU_DELSRM                 (R_ICU_BASE + R_ICU_DELSRM_OFFSET)
#define R_ICU_IELSR00                 (R_ICU_BASE + R_ICU_IELSR00_OFFSET)
#define R_ICU_IELSR01                 (R_ICU_BASE + R_ICU_IELSR01_OFFSET)
#define R_ICU_IELSR02                 (R_ICU_BASE + R_ICU_IELSR02_OFFSET)
#define R_ICU_IELSR03                 (R_ICU_BASE + R_ICU_IELSR03_OFFSET)
#define R_ICU_IELSR04                 (R_ICU_BASE + R_ICU_IELSR04_OFFSET)
#define R_ICU_IELSR05                 (R_ICU_BASE + R_ICU_IELSR05_OFFSET)
#define R_ICU_IELSR06                 (R_ICU_BASE + R_ICU_IELSR06_OFFSET)
#define R_ICU_IELSR07                 (R_ICU_BASE + R_ICU_IELSR07_OFFSET)
#define R_ICU_IELSR08                 (R_ICU_BASE + R_ICU_IELSR08_OFFSET)
#define R_ICU_IELSR09                 (R_ICU_BASE + R_ICU_IELSR09_OFFSET)
#define R_ICU_IELSR10                 (R_ICU_BASE + R_ICU_IELSR10_OFFSET)
#define R_ICU_IELSR11                 (R_ICU_BASE + R_ICU_IELSR11_OFFSET)
#define R_ICU_IELSR12                 (R_ICU_BASE + R_ICU_IELSR12_OFFSET)
#define R_ICU_IELSR13                 (R_ICU_BASE + R_ICU_IELSR13_OFFSET)
#define R_ICU_IELSR14                 (R_ICU_BASE + R_ICU_IELSR14_OFFSET)
#define R_ICU_IELSR15                 (R_ICU_BASE + R_ICU_IELSR15_OFFSET)
#define R_ICU_IELSR16                 (R_ICU_BASE + R_ICU_IELSR16_OFFSET)
#define R_ICU_IELSR17                 (R_ICU_BASE + R_ICU_IELSR17_OFFSET)
#define R_ICU_IELSR18                 (R_ICU_BASE + R_ICU_IELSR18_OFFSET)
#define R_ICU_IELSR19                 (R_ICU_BASE + R_ICU_IELSR19_OFFSET)
#define R_ICU_IELSR20                 (R_ICU_BASE + R_ICU_IELSR20_OFFSET)
#define R_ICU_IELSR21                 (R_ICU_BASE + R_ICU_IELSR21_OFFSET)
#define R_ICU_IELSR22                 (R_ICU_BASE + R_ICU_IELSR22_OFFSET)
#define R_ICU_IELSR23                 (R_ICU_BASE + R_ICU_IELSR23_OFFSET)
#define R_ICU_IELSR24                 (R_ICU_BASE + R_ICU_IELSR24_OFFSET)
#define R_ICU_IELSR25                 (R_ICU_BASE + R_ICU_IELSR25_OFFSET)
#define R_ICU_IELSR26                 (R_ICU_BASE + R_ICU_IELSR26_OFFSET)
#define R_ICU_IELSR27                 (R_ICU_BASE + R_ICU_IELSR27_OFFSET)
#define R_ICU_IELSR28                 (R_ICU_BASE + R_ICU_IELSR28_OFFSET)
#define R_ICU_IELSR29                 (R_ICU_BASE + R_ICU_IELSR29_OFFSET)
#define R_ICU_IELSR30                 (R_ICU_BASE + R_ICU_IELSR30_OFFSET)
#define R_ICU_IELSR31                 (R_ICU_BASE + R_ICU_IELSR31_OFFSET)
#define R_ICU_IELSR32                 (R_ICU_BASE + R_ICU_IELSR32_OFFSET)
#define R_ICU_IELSR33                 (R_ICU_BASE + R_ICU_IELSR33_OFFSET)
#define R_ICU_IELSR34                 (R_ICU_BASE + R_ICU_IELSR34_OFFSET)
#define R_ICU_IELSR35                 (R_ICU_BASE + R_ICU_IELSR35_OFFSET)
#define R_ICU_IELSR36                 (R_ICU_BASE + R_ICU_IELSR36_OFFSET)
#define R_ICU_IELSR37                 (R_ICU_BASE + R_ICU_IELSR37_OFFSET)
#define R_ICU_IELSR38                 (R_ICU_BASE + R_ICU_IELSR38_OFFSET)
#define R_ICU_IELSR39                 (R_ICU_BASE + R_ICU_IELSR39_OFFSET)
#define R_ICU_IELSR40                 (R_ICU_BASE + R_ICU_IELSR40_OFFSET)
#define R_ICU_IELSR41                 (R_ICU_BASE + R_ICU_IELSR41_OFFSET)
#define R_ICU_IELSR42                 (R_ICU_BASE + R_ICU_IELSR42_OFFSET)
#define R_ICU_IELSR43                 (R_ICU_BASE + R_ICU_IELSR43_OFFSET)
#define R_ICU_IELSR44                 (R_ICU_BASE + R_ICU_IELSR44_OFFSET)
#define R_ICU_IELSR45                 (R_ICU_BASE + R_ICU_IELSR45_OFFSET)
#define R_ICU_IELSR46                 (R_ICU_BASE + R_ICU_IELSR46_OFFSET)
#define R_ICU_IELSR47                 (R_ICU_BASE + R_ICU_IELSR47_OFFSET)
#define R_ICU_IELSR48                 (R_ICU_BASE + R_ICU_IELSR48_OFFSET)
#define R_ICU_IELSR49                 (R_ICU_BASE + R_ICU_IELSR49_OFFSET)
#define R_ICU_IELSR50                 (R_ICU_BASE + R_ICU_IELSR50_OFFSET)
#define R_ICU_IELSR51                 (R_ICU_BASE + R_ICU_IELSR51_OFFSET)
#define R_ICU_IELSR52                 (R_ICU_BASE + R_ICU_IELSR52_OFFSET)
#define R_ICU_IELSR53                 (R_ICU_BASE + R_ICU_IELSR53_OFFSET)
#define R_ICU_IELSR54                 (R_ICU_BASE + R_ICU_IELSR54_OFFSET)
#define R_ICU_IELSR55                 (R_ICU_BASE + R_ICU_IELSR55_OFFSET)
#define R_ICU_IELSR56                 (R_ICU_BASE + R_ICU_IELSR56_OFFSET)
#define R_ICU_IELSR57                 (R_ICU_BASE + R_ICU_IELSR57_OFFSET)
#define R_ICU_IELSR58                 (R_ICU_BASE + R_ICU_IELSR58_OFFSET)
#define R_ICU_IELSR59                 (R_ICU_BASE + R_ICU_IELSR59_OFFSET)
#define R_ICU_IELSR60                 (R_ICU_BASE + R_ICU_IELSR60_OFFSET)
#define R_ICU_IELSR61                 (R_ICU_BASE + R_ICU_IELSR61_OFFSET)
#define R_ICU_IELSR62                 (R_ICU_BASE + R_ICU_IELSR62_OFFSET)
#define R_ICU_IELSR63                 (R_ICU_BASE + R_ICU_IELSR63_OFFSET)
#define R_ICU_IELSR64                 (R_ICU_BASE + R_ICU_IELSR64_OFFSET)
#define R_ICU_IELSR65                 (R_ICU_BASE + R_ICU_IELSR65_OFFSET)
#define R_ICU_IELSR66                 (R_ICU_BASE + R_ICU_IELSR66_OFFSET)
#define R_ICU_IELSR67                 (R_ICU_BASE + R_ICU_IELSR67_OFFSET)
#define R_ICU_IELSR68                 (R_ICU_BASE + R_ICU_IELSR68_OFFSET)
#define R_ICU_IELSR69                 (R_ICU_BASE + R_ICU_IELSR69_OFFSET)
#define R_ICU_IELSR70                 (R_ICU_BASE + R_ICU_IELSR70_OFFSET)
#define R_ICU_IELSR71                 (R_ICU_BASE + R_ICU_IELSR71_OFFSET)
#define R_ICU_IELSR72                 (R_ICU_BASE + R_ICU_IELSR72_OFFSET)
#define R_ICU_IELSR73                 (R_ICU_BASE + R_ICU_IELSR73_OFFSET)
#define R_ICU_IELSR74                 (R_ICU_BASE + R_ICU_IELSR74_OFFSET)
#define R_ICU_IELSR75                 (R_ICU_BASE + R_ICU_IELSR75_OFFSET)
#define R_ICU_IELSR76                 (R_ICU_BASE + R_ICU_IELSR76_OFFSET)
#define R_ICU_IELSR77                 (R_ICU_BASE + R_ICU_IELSR77_OFFSET)
#define R_ICU_IELSR78                 (R_ICU_BASE + R_ICU_IELSR78_OFFSET)
#define R_ICU_IELSR79                 (R_ICU_BASE + R_ICU_IELSR79_OFFSET)
#define R_ICU_IELSR80                 (R_ICU_BASE + R_ICU_IELSR80_OFFSET)
#define R_ICU_IELSR81                 (R_ICU_BASE + R_ICU_IELSR81_OFFSET)
#define R_ICU_IELSR82                 (R_ICU_BASE + R_ICU_IELSR82_OFFSET)
#define R_ICU_IELSR83                 (R_ICU_BASE + R_ICU_IELSR83_OFFSET)
#define R_ICU_IELSR84                 (R_ICU_BASE + R_ICU_IELSR84_OFFSET)
#define R_ICU_IELSR85                 (R_ICU_BASE + R_ICU_IELSR85_OFFSET)
#define R_ICU_IELSR86                 (R_ICU_BASE + R_ICU_IELSR86_OFFSET)
#define R_ICU_IELSR87                 (R_ICU_BASE + R_ICU_IELSR87_OFFSET)
#define R_ICU_IELSR88                 (R_ICU_BASE + R_ICU_IELSR88_OFFSET)
#define R_ICU_IELSR89                 (R_ICU_BASE + R_ICU_IELSR89_OFFSET)
#define R_ICU_IELSR90                 (R_ICU_BASE + R_ICU_IELSR90_OFFSET)
#define R_ICU_IELSR91                 (R_ICU_BASE + R_ICU_IELSR91_OFFSET)
#define R_ICU_IELSR92                 (R_ICU_BASE + R_ICU_IELSR92_OFFSET)
#define R_ICU_IELSR93                 (R_ICU_BASE + R_ICU_IELSR93_OFFSET)
#define R_ICU_IELSR94                 (R_ICU_BASE + R_ICU_IELSR94_OFFSET)
#define R_ICU_IELSR95                 (R_ICU_BASE + R_ICU_IELSR95_OFFSET)

/* Register bit definitions */
/* NMIER Register bit definitions */
#define R_ICU_NMIER_IWDTEN                        (1 << 0)  /* IWDT Underflow/Refresh Error Interrupt Enable */

#define R_ICU_NMIER_WDTEN                         (1 << 1)  /* WDT Underflow/Refresh Error Interrupt Enable */

#define R_ICU_NMIER_PVD1EN                        (1 << 2)  /* Voltage monitor 1 Interrupt Enable */

#define R_ICU_NMIER_PVD2EN                        (1 << 3)  /* Voltage monitor 2 Interrupt Enable */

#define R_ICU_NMIER_SOSTEN                        (1 << 5)  /* Sub Oscillation Stop Detection Interrupt Enable */

#define R_ICU_NMIER_OSTEN                         (1 << 6)  /* Oscillation Stop Detection Interrupt Enable */

#define R_ICU_NMIER_NMIEN                         (1 << 7)  /* NMI Pin Interrupt Enable */

#define R_ICU_NMIER_BUSEN                         (1 << 12)  /*  */

#define R_ICU_NMIER_CMEN                          (1 << 13)  /*  */

#define R_ICU_NMIER_LMEN                          (1 << 14)  /* Local Memory Error Interrupt Enable */

#define R_ICU_NMIER_LUEN                          (1 << 15)  /*  */

#define R_ICU_NMIER_FPUEXCEN                      (1 << 16)  /* FPU Exception Interrupt Enable */

#define R_ICU_NMIER_MRCRDEN                       (1 << 17)  /* MRAM MRC read Error Interrupt Enable */

#define R_ICU_NMIER_MRERDEN                       (1 << 18)  /* MRAM MRE read Error Interrupt Enable */

#define R_ICU_NMIER_IPCEN                         (1 << 20)  /* IPC NMI CPU mutual Interrupt Enable */

#define R_ICU_NMIER_FPUFLTEN                      (1 << 16)  /* FPU FAULT Interrupt Enable */

/* NMICLR Register bit definitions */
#define R_ICU_NMICLR_IWDTCLR                      (1 << 0)  /* IWDT Underflow/Refresh Error Interrupt Status Flag Clear */

#define R_ICU_NMICLR_WDTCLR                       (1 << 1)  /* WDT Underflow/Refresh Error Interrupt Status Flag Clear */

#define R_ICU_NMICLR_PVD1CLR                      (1 << 2)  /* Voltage Monitor 1 Interrupt Status Flag Clear */

#define R_ICU_NMICLR_PVD2CLR                      (1 << 3)  /* Voltage Monitor 2 Interrupt Status Flag Clear */

#define R_ICU_NMICLR_SOSTCLR                      (1 << 5)  /* Oscillation Stop Detection Interrupt Status Flag Clear */

#define R_ICU_NMICLR_OSTCLR                       (1 << 6)  /* Oscillation Stop Detection Interrupt Status Flag Clear */

#define R_ICU_NMICLR_NMICLR                       (1 << 7)  /* NMI Pin Interrupt Status Flag Clear */

#define R_ICU_NMICLR_BUSCLR                       (1 << 12)  /*  */

#define R_ICU_NMICLR_CMCLR                        (1 << 13)  /*  */

#define R_ICU_NMICLR_LMCLR                        (1 << 14)  /*  */

#define R_ICU_NMICLR_LUCLR                        (1 << 15)  /*  */

#define R_ICU_NMICLR_FPUEXCCLR                    (1 << 16)  /* FPU Exception Interrupt Status Flag Clear */

#define R_ICU_NMICLR_MRCRDCLR                     (1 << 17)  /* MRAM MRC read Error Interrupt Status Flag Clear */

#define R_ICU_NMICLR_MRERDCLR                     (1 << 18)  /* MRAM MRE read Error Interrupt Status Flag Clear */

#define R_ICU_NMICLR_IPCCLR                       (1 << 20)  /* IPC NMI CPU mutual Interrupt Status Flag Clear */

#define R_ICU_NMICLR_FPUFLTCLR                    (1 << 16)  /* FPU FAULT Clear */

/* NMISR Register bit definitions */
#define R_ICU_NMISR_IWDTST                        (1 << 0)  /* IWDT Underflow/Refresh Error Interrupt Status Flag */

#define R_ICU_NMISR_WDTST                         (1 << 1)  /* WDT Underflow/Refresh Error Interrupt Status Flag */

#define R_ICU_NMISR_PVD1ST                        (1 << 2)  /* Voltage Monitor 1 Interrupt Status Flag */

#define R_ICU_NMISR_PVD2ST                        (1 << 3)  /* Voltage Monitor 2 Interrupt Status Flag */

#define R_ICU_NMISR_SOSTST                        (1 << 5)  /* Sub Oscillation Stop Detection Interrupt Status Flag */

#define R_ICU_NMISR_OSTST                         (1 << 6)  /* Main Clock Oscillation Stop Detection Interrupt Status Flag */

#define R_ICU_NMISR_NMIST                         (1 << 7)  /* NMI Pin Interrupt Status Flag */

#define R_ICU_NMISR_BUSST                         (1 << 12)  /* Bus Error Interrupt Status Flag */

#define R_ICU_NMISR_CMST                          (1 << 13)  /*  */

#define R_ICU_NMISR_LMST                          (1 << 14)  /*  */

#define R_ICU_NMISR_LUST                          (1 << 15)  /*  */

#define R_ICU_NMISR_FPUEXCST                      (1 << 16)  /*  */

#define R_ICU_NMISR_MRCRDST                       (1 << 17)  /*  */

#define R_ICU_NMISR_MRERDST                       (1 << 18)  /*  */

#define R_ICU_NMISR_IPCST                         (1 << 20)  /*  */

#define R_ICU_NMISR_FPUFLTST                      (1 << 16)  /* FPU FAULT Interrupt Status Flag */

/* WUPEN0 Register bit definitions */
#define R_ICU_WUPEN0_IRQWUPEN0                    (1 << 0)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN1                    (1 << 1)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN2                    (1 << 2)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN3                    (1 << 3)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN4                    (1 << 4)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN5                    (1 << 5)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN6                    (1 << 6)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN7                    (1 << 7)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN8                    (1 << 8)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN9                    (1 << 9)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN10                   (1 << 10)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN11                   (1 << 11)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN12                   (1 << 12)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN13                   (1 << 13)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN14                   (1 << 14)  /*  */

#define R_ICU_WUPEN0_IRQWUPEN15                   (1 << 15)  /*  */

#define R_ICU_WUPEN0_IWDTWUPEN                    (1 << 16)  /* IWDT Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_PVD1WUPEN                    (1 << 18)  /* PVD1 Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_PVD2WUPEN                    (1 << 19)  /* PVD2 Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_VBATTWUPEN                   (1 << 20)  /* VBATT Monitor Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_RTCALMWUPEN                  (1 << 24)  /* RTC Alarm Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_RTCPRDWUPEN                  (1 << 25)  /* RTC Period Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_USBHSWUPEN                   (1 << 26)  /* USBHS Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_USBFS0WUPEN                  (1 << 27)  /* USBFS Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_AGT1UDWUPEN                  (1 << 28)  /* AGT1 Underflow Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_AGT1CAWUPEN                  (1 << 29)  /* AGT1 Compare Match A Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_AGT1CBWUPEN                  (1 << 30)  /* AGT1 Compare Match B Interrupt Software Standby Mode Returns Enable bit */

#define R_ICU_WUPEN0_RIIC0WUPEN                   (1 << 31)  /* RIIC0 Address Match Interrupt Software Standby Mode Returns Enable bit */

/* WUPEN1 Register bit definitions */
#define R_ICU_WUPEN1_COMPHS0WUPEN                 (1 << 3)  /* Comparator-HS0 Interrupt Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_SOSCWUPEN                    (1 << 7)  /* Sub Oscillation Stop Detection Interrupt Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_ULP0UWUPEN                   (1 << 8)  /* ULPT0 Underflow Interrupt Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_ULP0AWUPEN                   (1 << 9)  /* ULPT0 Compare Match A Interrupt Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_ULP0BWUPEN                   (1 << 10)  /* ULPT0 Compare Match B Interrupt Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_I3CWUPEN                     (1 << 11)  /* I3C Wakeup Condition Detection Interrupt Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_ULP1UWUPEN                   (1 << 12)  /* ULPT1 Underflow Interrupt Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_ULP1AWUPEN                   (1 << 13)  /* ULPT1 Compare Match A Interrupt Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_ULP1BWUPEN                   (1 << 14)  /* ULPT1 Compare Match B Interrupt Software Standby Mode returns Enable bit */

#define R_ICU_WUPEN1_PDMWUPEN                     (1 << 15)  /* PDMIF Sound Detection Interrupt Software Standby Returns Enable bit */

#define R_ICU_WUPEN1_IRQWUPEN16                   (1 << 16)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN17                   (1 << 17)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN18                   (1 << 18)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN19                   (1 << 19)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN20                   (1 << 20)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN21                   (1 << 21)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN22                   (1 << 22)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN23                   (1 << 23)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN24                   (1 << 24)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN25                   (1 << 25)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN26                   (1 << 26)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN27                   (1 << 27)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN28                   (1 << 28)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN29                   (1 << 29)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN30                   (1 << 30)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

#define R_ICU_WUPEN1_IRQWUPEN31                   (1 << 31)  /* Interrupt Software Standby Returns Enable bits IRQ31 to IRQ16 */

/* DSLPWUPIRQEN0 Register bit definitions */
#define R_ICU_DSLPWUPIRQEN0_IRQ00                 (1 << 0)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ01                 (1 << 1)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ02                 (1 << 2)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ03                 (1 << 3)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ04                 (1 << 4)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ05                 (1 << 5)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ06                 (1 << 6)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ07                 (1 << 7)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ08                 (1 << 8)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ09                 (1 << 9)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ10                 (1 << 10)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ11                 (1 << 11)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ12                 (1 << 12)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ13                 (1 << 13)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ14                 (1 << 14)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ15                 (1 << 15)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ16                 (1 << 16)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ17                 (1 << 17)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ18                 (1 << 18)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ19                 (1 << 19)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ20                 (1 << 20)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ21                 (1 << 21)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ22                 (1 << 22)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ23                 (1 << 23)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ24                 (1 << 24)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ25                 (1 << 25)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ26                 (1 << 26)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ27                 (1 << 27)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ28                 (1 << 28)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ29                 (1 << 29)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ30                 (1 << 30)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN0_IRQ31                 (1 << 31)  /* IRQ Deep Sleep Returns Enable bit. */

/* DSLPWUPIRQEN1 Register bit definitions */
#define R_ICU_DSLPWUPIRQEN1_IRQ32                 (1 << 0)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ33                 (1 << 1)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ34                 (1 << 2)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ35                 (1 << 3)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ36                 (1 << 4)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ37                 (1 << 5)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ38                 (1 << 6)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ39                 (1 << 7)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ40                 (1 << 8)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ41                 (1 << 9)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ42                 (1 << 10)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ43                 (1 << 11)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ44                 (1 << 12)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ45                 (1 << 13)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ46                 (1 << 14)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ47                 (1 << 15)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ48                 (1 << 16)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ49                 (1 << 17)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ50                 (1 << 18)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ51                 (1 << 19)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ52                 (1 << 20)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ53                 (1 << 21)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ54                 (1 << 22)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ55                 (1 << 23)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ56                 (1 << 24)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ57                 (1 << 25)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ58                 (1 << 26)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ59                 (1 << 27)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ60                 (1 << 28)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ61                 (1 << 29)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ62                 (1 << 30)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN1_IRQ63                 (1 << 31)  /* IRQ Deep Sleep Returns Enable bit. */

/* DSLPWUPIRQEN2 Register bit definitions */
#define R_ICU_DSLPWUPIRQEN2_IRQ64                 (1 << 0)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ65                 (1 << 1)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ66                 (1 << 2)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ67                 (1 << 3)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ68                 (1 << 4)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ69                 (1 << 5)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ70                 (1 << 6)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ71                 (1 << 7)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ72                 (1 << 8)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ73                 (1 << 9)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ74                 (1 << 10)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ75                 (1 << 11)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ76                 (1 << 12)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ77                 (1 << 13)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ78                 (1 << 14)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ79                 (1 << 15)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ80                 (1 << 16)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ81                 (1 << 17)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ82                 (1 << 18)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ83                 (1 << 19)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ84                 (1 << 20)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ85                 (1 << 21)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ86                 (1 << 22)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ87                 (1 << 23)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ88                 (1 << 24)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ89                 (1 << 25)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ90                 (1 << 26)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ91                 (1 << 27)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ92                 (1 << 28)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ93                 (1 << 29)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ94                 (1 << 30)  /* IRQ Deep Sleep Returns Enable bit. */

#define R_ICU_DSLPWUPIRQEN2_IRQ95                 (1 << 31)  /* IRQ Deep Sleep Returns Enable bit. */

/* DELSRM Register bit definitions */
#define R_ICU_DELSRM_DELS_SHIFT                   (0)  /* DMAC Event Link Select */
#define R_ICU_DELSRM_DELS_MASK                    0x3ff
#  define R_ICU_DELSRM_DELS_0X00                          (0 << R_ICU_DELSRM_DELS_SHIFT)  /* Disable interrupts to the associated DMAC module */

#define R_ICU_DELSRM_IR                           (1 << 16)  /* DMAC Activation Request Status flag */


/* Maximum number of channels */

#define ICU_MAX_CHANNELS    96

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ICU_H */

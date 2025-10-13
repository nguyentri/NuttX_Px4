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

/* Channel stride for multi-channel peripherals */
#define R_ELC_CH_STRIDE    0x00000004
#define R_ELC_CH_BASE(ch)   (R_ELC_BASE + ((uint32_t)(ch) * R_ELC_CH_STRIDE))

/* ELC Register Offsets */

#define R_ELC_ELCR_OFFSET     0x00000000  /* Event Link Controller Register */
/* ELSEGR%s Registers (0-3) */
#define R_ELC_ELSEGR0_OFFSET     0x00000004  /* Event Link Software Event Generation Register 0 */
#define R_ELC_ELSEGR1_OFFSET     0x00000008  /* Event Link Software Event Generation Register 1 */
#define R_ELC_ELSEGR2_OFFSET     0x0000000c  /* Event Link Software Event Generation Register 2 */
#define R_ELC_ELSEGR3_OFFSET     0x00000010  /* Event Link Software Event Generation Register 3 */
/* ELSR%s Registers (0-52) */
#define R_ELC_ELSR00_OFFSET     0x00000020  /* Event Link Setting Register 00 */
#define R_ELC_ELSR01_OFFSET     0x00000024  /* Event Link Setting Register 01 */
#define R_ELC_ELSR02_OFFSET     0x00000028  /* Event Link Setting Register 02 */
#define R_ELC_ELSR03_OFFSET     0x0000002c  /* Event Link Setting Register 03 */
#define R_ELC_ELSR04_OFFSET     0x00000030  /* Event Link Setting Register 04 */
#define R_ELC_ELSR05_OFFSET     0x00000034  /* Event Link Setting Register 05 */
#define R_ELC_ELSR06_OFFSET     0x00000038  /* Event Link Setting Register 06 */
#define R_ELC_ELSR07_OFFSET     0x0000003c  /* Event Link Setting Register 07 */
#define R_ELC_ELSR08_OFFSET     0x00000040  /* Event Link Setting Register 08 */
#define R_ELC_ELSR09_OFFSET     0x00000044  /* Event Link Setting Register 09 */
#define R_ELC_ELSR10_OFFSET     0x00000048  /* Event Link Setting Register 10 */
#define R_ELC_ELSR11_OFFSET     0x0000004c  /* Event Link Setting Register 11 */
#define R_ELC_ELSR12_OFFSET     0x00000050  /* Event Link Setting Register 12 */
#define R_ELC_ELSR13_OFFSET     0x00000054  /* Event Link Setting Register 13 */
#define R_ELC_ELSR14_OFFSET     0x00000058  /* Event Link Setting Register 14 */
#define R_ELC_ELSR15_OFFSET     0x0000005c  /* Event Link Setting Register 15 */
#define R_ELC_ELSR16_OFFSET     0x00000060  /* Event Link Setting Register 16 */
#define R_ELC_ELSR17_OFFSET     0x00000064  /* Event Link Setting Register 17 */
#define R_ELC_ELSR18_OFFSET     0x00000068  /* Event Link Setting Register 18 */
#define R_ELC_ELSR19_OFFSET     0x0000006c  /* Event Link Setting Register 19 */
#define R_ELC_ELSR20_OFFSET     0x00000070  /* Event Link Setting Register 20 */
#define R_ELC_ELSR21_OFFSET     0x00000074  /* Event Link Setting Register 21 */
#define R_ELC_ELSR22_OFFSET     0x00000078  /* Event Link Setting Register 22 */
#define R_ELC_ELSR23_OFFSET     0x0000007c  /* Event Link Setting Register 23 */
#define R_ELC_ELSR24_OFFSET     0x00000080  /* Event Link Setting Register 24 */
#define R_ELC_ELSR25_OFFSET     0x00000084  /* Event Link Setting Register 25 */
#define R_ELC_ELSR26_OFFSET     0x00000088  /* Event Link Setting Register 26 */
#define R_ELC_ELSR27_OFFSET     0x0000008c  /* Event Link Setting Register 27 */
#define R_ELC_ELSR28_OFFSET     0x00000090  /* Event Link Setting Register 28 */
#define R_ELC_ELSR29_OFFSET     0x00000094  /* Event Link Setting Register 29 */
#define R_ELC_ELSR30_OFFSET     0x00000098  /* Event Link Setting Register 30 */
#define R_ELC_ELSR31_OFFSET     0x0000009c  /* Event Link Setting Register 31 */
#define R_ELC_ELSR32_OFFSET     0x000000a0  /* Event Link Setting Register 32 */
#define R_ELC_ELSR33_OFFSET     0x000000a4  /* Event Link Setting Register 33 */
#define R_ELC_ELSR34_OFFSET     0x000000a8  /* Event Link Setting Register 34 */
#define R_ELC_ELSR35_OFFSET     0x000000ac  /* Event Link Setting Register 35 */
#define R_ELC_ELSR36_OFFSET     0x000000b0  /* Event Link Setting Register 36 */
#define R_ELC_ELSR37_OFFSET     0x000000b4  /* Event Link Setting Register 37 */
#define R_ELC_ELSR38_OFFSET     0x000000b8  /* Event Link Setting Register 38 */
#define R_ELC_ELSR39_OFFSET     0x000000bc  /* Event Link Setting Register 39 */
#define R_ELC_ELSR40_OFFSET     0x000000c0  /* Event Link Setting Register 40 */
#define R_ELC_ELSR41_OFFSET     0x000000c4  /* Event Link Setting Register 41 */
#define R_ELC_ELSR42_OFFSET     0x000000c8  /* Event Link Setting Register 42 */
#define R_ELC_ELSR43_OFFSET     0x000000cc  /* Event Link Setting Register 43 */
#define R_ELC_ELSR44_OFFSET     0x000000d0  /* Event Link Setting Register 44 */
#define R_ELC_ELSR45_OFFSET     0x000000d4  /* Event Link Setting Register 45 */
#define R_ELC_ELSR46_OFFSET     0x000000d8  /* Event Link Setting Register 46 */
#define R_ELC_ELSR47_OFFSET     0x000000dc  /* Event Link Setting Register 47 */
#define R_ELC_ELSR48_OFFSET     0x000000e0  /* Event Link Setting Register 48 */
#define R_ELC_ELSR49_OFFSET     0x000000e4  /* Event Link Setting Register 49 */
#define R_ELC_ELSR50_OFFSET     0x000000e8  /* Event Link Setting Register 50 */
#define R_ELC_ELSR51_OFFSET     0x000000ec  /* Event Link Setting Register 51 */
#define R_ELC_ELSR52_OFFSET     0x000000f0  /* Event Link Setting Register 52 */
#define R_ELC_ELCSARA_OFFSET     0x00000100  /* Event Link Controller Security Attribution Register A */
#define R_ELC_ELCSARB_OFFSET     0x00000104  /* Event Link Controller Security Attribution Register B */
#define R_ELC_ELCSARC_OFFSET     0x00000108  /* Event Link Controller Security Attribution Register C */
#define R_ELC_ELCPARA_OFFSET     0x00000110  /* Event Link Controller Privilege Attribution Register A */
#define R_ELC_ELCPARB_OFFSET     0x00000114  /* Event Link Controller Privilege Attribution Register B */
#define R_ELC_ELCPARC_OFFSET     0x00000118  /* Event Link Controller Privilege Attribution Register C */

/* ELC Register Addresses */

#define R_ELC_ELCR                 (R_ELC_BASE + R_ELC_ELCR_OFFSET)
#define R_ELC_ELSEGR0                 (R_ELC_BASE + R_ELC_ELSEGR0_OFFSET)
#define R_ELC_ELSEGR1                 (R_ELC_BASE + R_ELC_ELSEGR1_OFFSET)
#define R_ELC_ELSEGR2                 (R_ELC_BASE + R_ELC_ELSEGR2_OFFSET)
#define R_ELC_ELSEGR3                 (R_ELC_BASE + R_ELC_ELSEGR3_OFFSET)
#define R_ELC_ELSR00                 (R_ELC_BASE + R_ELC_ELSR00_OFFSET)
#define R_ELC_ELSR01                 (R_ELC_BASE + R_ELC_ELSR01_OFFSET)
#define R_ELC_ELSR02                 (R_ELC_BASE + R_ELC_ELSR02_OFFSET)
#define R_ELC_ELSR03                 (R_ELC_BASE + R_ELC_ELSR03_OFFSET)
#define R_ELC_ELSR04                 (R_ELC_BASE + R_ELC_ELSR04_OFFSET)
#define R_ELC_ELSR05                 (R_ELC_BASE + R_ELC_ELSR05_OFFSET)
#define R_ELC_ELSR06                 (R_ELC_BASE + R_ELC_ELSR06_OFFSET)
#define R_ELC_ELSR07                 (R_ELC_BASE + R_ELC_ELSR07_OFFSET)
#define R_ELC_ELSR08                 (R_ELC_BASE + R_ELC_ELSR08_OFFSET)
#define R_ELC_ELSR09                 (R_ELC_BASE + R_ELC_ELSR09_OFFSET)
#define R_ELC_ELSR10                 (R_ELC_BASE + R_ELC_ELSR10_OFFSET)
#define R_ELC_ELSR11                 (R_ELC_BASE + R_ELC_ELSR11_OFFSET)
#define R_ELC_ELSR12                 (R_ELC_BASE + R_ELC_ELSR12_OFFSET)
#define R_ELC_ELSR13                 (R_ELC_BASE + R_ELC_ELSR13_OFFSET)
#define R_ELC_ELSR14                 (R_ELC_BASE + R_ELC_ELSR14_OFFSET)
#define R_ELC_ELSR15                 (R_ELC_BASE + R_ELC_ELSR15_OFFSET)
#define R_ELC_ELSR16                 (R_ELC_BASE + R_ELC_ELSR16_OFFSET)
#define R_ELC_ELSR17                 (R_ELC_BASE + R_ELC_ELSR17_OFFSET)
#define R_ELC_ELSR18                 (R_ELC_BASE + R_ELC_ELSR18_OFFSET)
#define R_ELC_ELSR19                 (R_ELC_BASE + R_ELC_ELSR19_OFFSET)
#define R_ELC_ELSR20                 (R_ELC_BASE + R_ELC_ELSR20_OFFSET)
#define R_ELC_ELSR21                 (R_ELC_BASE + R_ELC_ELSR21_OFFSET)
#define R_ELC_ELSR22                 (R_ELC_BASE + R_ELC_ELSR22_OFFSET)
#define R_ELC_ELSR23                 (R_ELC_BASE + R_ELC_ELSR23_OFFSET)
#define R_ELC_ELSR24                 (R_ELC_BASE + R_ELC_ELSR24_OFFSET)
#define R_ELC_ELSR25                 (R_ELC_BASE + R_ELC_ELSR25_OFFSET)
#define R_ELC_ELSR26                 (R_ELC_BASE + R_ELC_ELSR26_OFFSET)
#define R_ELC_ELSR27                 (R_ELC_BASE + R_ELC_ELSR27_OFFSET)
#define R_ELC_ELSR28                 (R_ELC_BASE + R_ELC_ELSR28_OFFSET)
#define R_ELC_ELSR29                 (R_ELC_BASE + R_ELC_ELSR29_OFFSET)
#define R_ELC_ELSR30                 (R_ELC_BASE + R_ELC_ELSR30_OFFSET)
#define R_ELC_ELSR31                 (R_ELC_BASE + R_ELC_ELSR31_OFFSET)
#define R_ELC_ELSR32                 (R_ELC_BASE + R_ELC_ELSR32_OFFSET)
#define R_ELC_ELSR33                 (R_ELC_BASE + R_ELC_ELSR33_OFFSET)
#define R_ELC_ELSR34                 (R_ELC_BASE + R_ELC_ELSR34_OFFSET)
#define R_ELC_ELSR35                 (R_ELC_BASE + R_ELC_ELSR35_OFFSET)
#define R_ELC_ELSR36                 (R_ELC_BASE + R_ELC_ELSR36_OFFSET)
#define R_ELC_ELSR37                 (R_ELC_BASE + R_ELC_ELSR37_OFFSET)
#define R_ELC_ELSR38                 (R_ELC_BASE + R_ELC_ELSR38_OFFSET)
#define R_ELC_ELSR39                 (R_ELC_BASE + R_ELC_ELSR39_OFFSET)
#define R_ELC_ELSR40                 (R_ELC_BASE + R_ELC_ELSR40_OFFSET)
#define R_ELC_ELSR41                 (R_ELC_BASE + R_ELC_ELSR41_OFFSET)
#define R_ELC_ELSR42                 (R_ELC_BASE + R_ELC_ELSR42_OFFSET)
#define R_ELC_ELSR43                 (R_ELC_BASE + R_ELC_ELSR43_OFFSET)
#define R_ELC_ELSR44                 (R_ELC_BASE + R_ELC_ELSR44_OFFSET)
#define R_ELC_ELSR45                 (R_ELC_BASE + R_ELC_ELSR45_OFFSET)
#define R_ELC_ELSR46                 (R_ELC_BASE + R_ELC_ELSR46_OFFSET)
#define R_ELC_ELSR47                 (R_ELC_BASE + R_ELC_ELSR47_OFFSET)
#define R_ELC_ELSR48                 (R_ELC_BASE + R_ELC_ELSR48_OFFSET)
#define R_ELC_ELSR49                 (R_ELC_BASE + R_ELC_ELSR49_OFFSET)
#define R_ELC_ELSR50                 (R_ELC_BASE + R_ELC_ELSR50_OFFSET)
#define R_ELC_ELSR51                 (R_ELC_BASE + R_ELC_ELSR51_OFFSET)
#define R_ELC_ELSR52                 (R_ELC_BASE + R_ELC_ELSR52_OFFSET)
#define R_ELC_ELCSARA                 (R_ELC_BASE + R_ELC_ELCSARA_OFFSET)
#define R_ELC_ELCSARB                 (R_ELC_BASE + R_ELC_ELCSARB_OFFSET)
#define R_ELC_ELCSARC                 (R_ELC_BASE + R_ELC_ELCSARC_OFFSET)
#define R_ELC_ELCPARA                 (R_ELC_BASE + R_ELC_ELCPARA_OFFSET)
#define R_ELC_ELCPARB                 (R_ELC_BASE + R_ELC_ELCPARB_OFFSET)
#define R_ELC_ELCPARC                 (R_ELC_BASE + R_ELC_ELCPARC_OFFSET)

/* Register bit definitions */
/* ELCR Register bit definitions */
#define R_ELC_ELCR_ELCON                          (1 << 7)  /* All Event Link Enable */

/* ELSEGR Register bit definitions */
#define R_ELC_ELSEGR_SEG                          (1 << 0)  /* Software Event Generation */

#define R_ELC_ELSEGR_WE                           (1 << 6)  /* SEG Bit Write Enable */

#define R_ELC_ELSEGR_WI                           (1 << 7)  /* ELSEGR Register Write Disable */

/* ELSR Register bit definitions */
#define R_ELC_ELSR_ELS_SHIFT                      (0)  /* Event Link Select */
#define R_ELC_ELSR_ELS_MASK                       0x3ff

/* ELCSARA Register bit definitions */
#define R_ELC_ELCSARA_ELCR                        (1 << 0)  /* Event Link Controller Register Security Attribution */

#define R_ELC_ELCSARA_ELSEGR0                     (1 << 1)  /* Event Link Software Event Generation Register 0 Security Attribution */

#define R_ELC_ELCSARA_ELSEGR1                     (1 << 2)  /* Event Link Software Event Generation Register 1 Security Attribution */

#define R_ELC_ELCSARA_ELSEGR2                     (1 << 3)  /* Event Link Software Event Generation Register 2 Security Attribution */

#define R_ELC_ELCSARA_ELSEGR3                     (1 << 4)  /* Event Link Software Event Generation Register 3 Security Attribution */

/* ELCSARB Register bit definitions */
#define R_ELC_ELCSARB_ELSR0                       (1 << 0)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR1                       (1 << 1)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR2                       (1 << 2)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR3                       (1 << 3)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR4                       (1 << 4)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR5                       (1 << 5)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR6                       (1 << 6)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR7                       (1 << 7)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR12                      (1 << 12)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR13                      (1 << 13)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR14                      (1 << 14)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR15                      (1 << 15)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR16                      (1 << 16)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR17                      (1 << 17)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR19                      (1 << 19)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR20                      (1 << 20)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR21                      (1 << 21)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR22                      (1 << 22)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR23                      (1 << 23)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR24                      (1 << 24)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR25                      (1 << 25)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR26                      (1 << 26)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR27                      (1 << 27)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR30                      (1 << 30)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR31                      (1 << 31)  /* Event Link Setting Register n Security Attribution */

#define R_ELC_ELCSARB_ELSR8                       (1 << 8)  /* Event Link Setting Register 8 Security Attribution */

#define R_ELC_ELCSARB_ELSR9                       (1 << 9)  /* Event Link Setting Register 9 Security Attribution */

#define R_ELC_ELCSARB_ELSR10                      (1 << 10)  /* Event Link Setting Register 10 Security Attribution */

#define R_ELC_ELCSARB_ELSR11                      (1 << 11)  /* Event Link Setting Register 11 Security Attribution */

#define R_ELC_ELCSARB_ELSR18                      (1 << 18)  /* Event Link Setting Register 18 Security Attribution */

#define R_ELC_ELCSARB_ELSR28                      (1 << 28)  /* Event Link Setting Register 28 Security Attribution */

#define R_ELC_ELCSARB_ELSR29                      (1 << 29)  /* Event Link Setting Register 29 Security Attribution */

/* ELCSARC Register bit definitions */
#define R_ELC_ELCSARC_ELSR_SHIFT                  (0)  /* Event Link Setting Register n Security Attribution */
#define R_ELC_ELCSARC_ELSR_MASK                   0x1fffff
#  define R_ELC_ELCSARC_ELSR_0                            (0 << R_ELC_ELCSARC_ELSR_SHIFT)  /* Secure */
#  define R_ELC_ELCSARC_ELSR_1                            (1 << R_ELC_ELCSARC_ELSR_SHIFT)  /* Non-secure */

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

#define R_ELC_ELCPARA_ELSEGR0                     (1 << 1)  /* Event Link Software Event Generation Register 0 Privilege Attribution */

#define R_ELC_ELCPARA_ELSEGR1                     (1 << 2)  /* Event Link Software Event Generation Register 1 Privilege Attribution */

#define R_ELC_ELCPARA_ELSEGR2                     (1 << 3)  /* Event Link Software Event Generation Register 2 Privilege Attribution */

#define R_ELC_ELCPARA_ELSEGR3                     (1 << 4)  /* Event Link Software Event Generation Register 3 Privilege Attribution */

/* ELCPARB Register bit definitions */
#define R_ELC_ELCPARB_ELSR0                       (1 << 0)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR1                       (1 << 1)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR2                       (1 << 2)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR3                       (1 << 3)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR4                       (1 << 4)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR5                       (1 << 5)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR6                       (1 << 6)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR7                       (1 << 7)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR12                      (1 << 12)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR13                      (1 << 13)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR14                      (1 << 14)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR15                      (1 << 15)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR16                      (1 << 16)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR17                      (1 << 17)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR19                      (1 << 19)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR20                      (1 << 20)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR21                      (1 << 21)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR22                      (1 << 22)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR23                      (1 << 23)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR24                      (1 << 24)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR25                      (1 << 25)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR26                      (1 << 26)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR27                      (1 << 27)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR30                      (1 << 30)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR31                      (1 << 31)  /* Event Link Setting Register n Privilege Attribution */

#define R_ELC_ELCPARB_ELSR8                       (1 << 8)  /* Event Link Setting Register 8 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR9                       (1 << 9)  /* Event Link Setting Register 9 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR10                      (1 << 10)  /* Event Link Setting Register 10 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR11                      (1 << 11)  /* Event Link Setting Register 11 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR18                      (1 << 18)  /* Event Link Setting Register 18 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR28                      (1 << 28)  /* Event Link Setting Register 28 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR29                      (1 << 29)  /* Event Link Setting Register 29 Privilege Attribution */

/* ELCPARC Register bit definitions */
#define R_ELC_ELCPARC_ELSR_SHIFT                  (0)  /* Event Link Setting Register n Privilege Attribution */
#define R_ELC_ELCPARC_ELSR_MASK                   0x1fffff
#  define R_ELC_ELCPARC_ELSR_0                            (0 << R_ELC_ELCPARC_ELSR_SHIFT)  /* Privileged */
#  define R_ELC_ELCPARC_ELSR_1                            (1 << R_ELC_ELCPARC_ELSR_SHIFT)  /* Unprivileged */

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


/* Maximum number of channels */

#define ELC_MAX_CHANNELS    53

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ELC_H */

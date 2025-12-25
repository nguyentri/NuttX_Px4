/****************************************************************************
 * arch/arm/include/ra8/ra8p1_irq.h
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

/* This file should never be included directly but, rather,
 * only indirectly through nuttx/irq.h
 */

#ifndef __ARCH_ARM_INCLUDE_RA_RA8P1_IRQ_H
#define __ARCH_ARM_INCLUDE_RA_RA8P1_IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <nuttx/config.h>
#include <nuttx/irq.h>
#include <arch/ra8/chip.h>

/****************************************************************************
 * Pre-processor Prototypes
 ****************************************************************************/

/* Total number of IRQ numbers */
#define RA_IRQ_IELSR0                                (RA_IRQ_FIRST + 0)   /* 0:  Event selected in the ICU.IELSR0 register */
#define RA_IRQ_IELSR1                                (RA_IRQ_FIRST + 1)   /* 1:  Event selected in the ICU.IELSR1 register */
#define RA_IRQ_IELSR2                                (RA_IRQ_FIRST + 2)   /* 2:  Event selected in the ICU.IELSR2 register */
#define RA_IRQ_IELSR3                                (RA_IRQ_FIRST + 3)   /* 3:  Event selected in the ICU.IELSR3 register */
#define RA_IRQ_IELSR4                                (RA_IRQ_FIRST + 4)   /* 4:  Event selected in the ICU.IELSR4 register */
#define RA_IRQ_IELSR5                                (RA_IRQ_FIRST + 5)   /* 5:  Event selected in the ICU.IELSR5 register */
#define RA_IRQ_IELSR6                                (RA_IRQ_FIRST + 6)   /* 6:  Event selected in the ICU.IELSR6 register */
#define RA_IRQ_IELSR7                                (RA_IRQ_FIRST + 7)   /* 7:  Event selected in the ICU.IELSR7 register */
#define RA_IRQ_IELSR8                                (RA_IRQ_FIRST + 8)   /* 8:  Event selected in the ICU.IELSR8 register */
#define RA_IRQ_IELSR9                                (RA_IRQ_FIRST + 9)   /* 9:  Event selected in the ICU.IELSR9 register */
#define RA_IRQ_IELSR10                               (RA_IRQ_FIRST + 10)  /* 10:  Event selected in the ICU.IELSR10 register */
#define RA_IRQ_IELSR11                               (RA_IRQ_FIRST + 11)  /* 11:  Event selected in the ICU.IELSR11 register */
#define RA_IRQ_IELSR12                               (RA_IRQ_FIRST + 12)  /* 12:  Event selected in the ICU.IELSR12 register */
#define RA_IRQ_IELSR13                               (RA_IRQ_FIRST + 13)  /* 13:  Event selected in the ICU.IELSR13 register */
#define RA_IRQ_IELSR14                               (RA_IRQ_FIRST + 14)  /* 14:  Event selected in the ICU.IELSR14 register */
#define RA_IRQ_IELSR15                               (RA_IRQ_FIRST + 15)  /* 15:  Event selected in the ICU.IELSR15 register */
#define RA_IRQ_IELSR16                               (RA_IRQ_FIRST + 16)  /* 16:  Event selected in the ICU.IELSR16 register */
#define RA_IRQ_IELSR17                               (RA_IRQ_FIRST + 17)  /* 17:  Event selected in the ICU.IELSR17 register */
#define RA_IRQ_IELSR18                               (RA_IRQ_FIRST + 18)  /* 18:  Event selected in the ICU.IELSR18 register */
#define RA_IRQ_IELSR19                               (RA_IRQ_FIRST + 19)  /* 19:  Event selected in the ICU.IELSR19 register */
#define RA_IRQ_IELSR20                               (RA_IRQ_FIRST + 20)  /* 20:  Event selected in the ICU.IELSR20 register */
#define RA_IRQ_IELSR21                               (RA_IRQ_FIRST + 21)  /* 21:  Event selected in the ICU.IELSR21 register */
#define RA_IRQ_IELSR22                               (RA_IRQ_FIRST + 22)  /* 22:  Event selected in the ICU.IELSR22 register */
#define RA_IRQ_IELSR23                               (RA_IRQ_FIRST + 23)  /* 23:  Event selected in the ICU.IELSR23 register */
#define RA_IRQ_IELSR24                               (RA_IRQ_FIRST + 24)  /* 24:  Event selected in the ICU.IELSR24 register */
#define RA_IRQ_IELSR25                               (RA_IRQ_FIRST + 25)  /* 25:  Event selected in the ICU.IELSR25 register */
#define RA_IRQ_IELSR26                               (RA_IRQ_FIRST + 26)  /* 26:  Event selected in the ICU.IELSR26 register */
#define RA_IRQ_IELSR27                               (RA_IRQ_FIRST + 27)  /* 27:  Event selected in the ICU.IELSR27 register */
#define RA_IRQ_IELSR28                               (RA_IRQ_FIRST + 28)  /* 28:  Event selected in the ICU.IELSR28 register */
#define RA_IRQ_IELSR29                               (RA_IRQ_FIRST + 29)  /* 29:  Event selected in the ICU.IELSR29 register */
#define RA_IRQ_IELSR30                               (RA_IRQ_FIRST + 30)  /* 30:  Event selected in the ICU.IELSR30 register */
#define RA_IRQ_IELSR31                               (RA_IRQ_FIRST + 31)  /* 31:  Event selected in the ICU.IELSR31 register */
#define RA_IRQ_IELSR32                               (RA_IRQ_FIRST + 32)  /* 32:  Event selected in the ICU.IELSR32 register */
#define RA_IRQ_IELSR33                               (RA_IRQ_FIRST + 33)  /* 33:  Event selected in the ICU.IELSR33 register */
#define RA_IRQ_IELSR34                               (RA_IRQ_FIRST + 34)  /* 34:  Event selected in the ICU.IELSR34 register */
#define RA_IRQ_IELSR35                               (RA_IRQ_FIRST + 35)  /* 35:  Event selected in the ICU.IELSR35 register */
#define RA_IRQ_IELSR36                               (RA_IRQ_FIRST + 36)  /* 36:  Event selected in the ICU.IELSR36 register */
#define RA_IRQ_IELSR37                               (RA_IRQ_FIRST + 37)  /* 37:  Event selected in the ICU.IELSR37 register */
#define RA_IRQ_IELSR38                               (RA_IRQ_FIRST + 38)  /* 38:  Event selected in the ICU.IELSR38 register */
#define RA_IRQ_IELSR39                               (RA_IRQ_FIRST + 39)  /* 39:  Event selected in the ICU.IELSR39 register */
#define RA_IRQ_IELSR40                               (RA_IRQ_FIRST + 40)  /* 40:  Event selected in the ICU.IELSR40 register */
#define RA_IRQ_IELSR41                               (RA_IRQ_FIRST + 41)  /* 41:  Event selected in the ICU.IELSR41 register */
#define RA_IRQ_IELSR42                               (RA_IRQ_FIRST + 42)  /* 42:  Event selected in the ICU.IELSR42 register */
#define RA_IRQ_IELSR43                               (RA_IRQ_FIRST + 43)  /* 43:  Event selected in the ICU.IELSR43 register */
#define RA_IRQ_IELSR44                               (RA_IRQ_FIRST + 44)  /* 44:  Event selected in the ICU.IELSR44 register */
#define RA_IRQ_IELSR45                               (RA_IRQ_FIRST + 45)  /* 45:  Event selected in the ICU.IELSR45 register */
#define RA_IRQ_IELSR46                               (RA_IRQ_FIRST + 46)  /* 46:  Event selected in the ICU.IELSR46 register */
#define RA_IRQ_IELSR47                               (RA_IRQ_FIRST + 47)  /* 47:  Event selected in the ICU.IELSR47 register */
#define RA_IRQ_IELSR48                               (RA_IRQ_FIRST + 48)  /* 48:  Event selected in the ICU.IELSR48 register */
#define RA_IRQ_IELSR49                               (RA_IRQ_FIRST + 49)  /* 49:  Event selected in the ICU.IELSR49 register */
#define RA_IRQ_IELSR50                               (RA_IRQ_FIRST + 50)  /* 50:  Event selected in the ICU.IELSR50 register */
#define RA_IRQ_IELSR51                               (RA_IRQ_FIRST + 51)  /* 51:  Event selected in the ICU.IELSR51 register */
#define RA_IRQ_IELSR52                               (RA_IRQ_FIRST + 52)  /* 52:  Event selected in the ICU.IELSR52 register */
#define RA_IRQ_IELSR53                               (RA_IRQ_FIRST + 53)  /* 53:  Event selected in the ICU.IELSR53 register */
#define RA_IRQ_IELSR54                               (RA_IRQ_FIRST + 54)  /* 54:  Event selected in the ICU.IELSR54 register */
#define RA_IRQ_IELSR55                               (RA_IRQ_FIRST + 55)  /* 55:  Event selected in the ICU.IELSR55 register */
#define RA_IRQ_IELSR56                               (RA_IRQ_FIRST + 56)  /* 56:  Event selected in the ICU.IELSR56 register */
#define RA_IRQ_IELSR57                               (RA_IRQ_FIRST + 57)  /* 57:  Event selected in the ICU.IELSR57 register */
#define RA_IRQ_IELSR58                               (RA_IRQ_FIRST + 58)  /* 58:  Event selected in the ICU.IELSR58 register */
#define RA_IRQ_IELSR59                               (RA_IRQ_FIRST + 59)  /* 59:  Event selected in the ICU.IELSR59 register */
#define RA_IRQ_IELSR60                               (RA_IRQ_FIRST + 60)  /* 60:  Event selected in the ICU.IELSR60 register */
#define RA_IRQ_IELSR61                               (RA_IRQ_FIRST + 61)  /* 61:  Event selected in the ICU.IELSR61 register */
#define RA_IRQ_IELSR62                               (RA_IRQ_FIRST + 62)  /* 62:  Event selected in the ICU.IELSR62 register */
#define RA_IRQ_IELSR63                               (RA_IRQ_FIRST + 63)  /* 63:  Event selected in the ICU.IELSR63 register */
#define RA_IRQ_IELSR64                               (RA_IRQ_FIRST + 64)  /* 64:  Event selected in the ICU.IELSR64 register */
#define RA_IRQ_IELSR65                               (RA_IRQ_FIRST + 65)  /* 65:  Event selected in the ICU.IELSR65 register */
#define RA_IRQ_IELSR66                               (RA_IRQ_FIRST + 66)  /* 66:  Event selected in the ICU.IELSR66 register */
#define RA_IRQ_IELSR67                               (RA_IRQ_FIRST + 67)  /* 67:  Event selected in the ICU.IELSR67 register */
#define RA_IRQ_IELSR68                               (RA_IRQ_FIRST + 68)  /* 68:  Event selected in the ICU.IELSR68 register */
#define RA_IRQ_IELSR69                               (RA_IRQ_FIRST + 69)  /* 69:  Event selected in the ICU.IELSR69 register */
#define RA_IRQ_IELSR70                               (RA_IRQ_FIRST + 70)  /* 70:  Event selected in the ICU.IELSR70 register */
#define RA_IRQ_IELSR71                               (RA_IRQ_FIRST + 71)  /* 71:  Event selected in the ICU.IELSR71 register */
#define RA_IRQ_IELSR72                               (RA_IRQ_FIRST + 72)  /* 72:  Event selected in the ICU.IELSR72 register */
#define RA_IRQ_IELSR73                               (RA_IRQ_FIRST + 73)  /* 73:  Event selected in the ICU.IELSR73 register */
#define RA_IRQ_IELSR74                               (RA_IRQ_FIRST + 74)  /* 74:  Event selected in the ICU.IELSR74 register */
#define RA_IRQ_IELSR75                               (RA_IRQ_FIRST + 75)  /* 75:  Event selected in the ICU.IELSR75 register */
#define RA_IRQ_IELSR76                               (RA_IRQ_FIRST + 76)  /* 76:  Event selected in the ICU.IELSR76 register */
#define RA_IRQ_IELSR77                               (RA_IRQ_FIRST + 77)  /* 77:  Event selected in the ICU.IELSR77 register */
#define RA_IRQ_IELSR78                               (RA_IRQ_FIRST + 78)  /* 78:  Event selected in the ICU.IELSR78 register */
#define RA_IRQ_IELSR79                               (RA_IRQ_FIRST + 79)  /* 79:  Event selected in the ICU.IELSR79 register */
#define RA_IRQ_IELSR80                               (RA_IRQ_FIRST + 80)  /* 80:  Event selected in the ICU.IELSR80 register */
#define RA_IRQ_IELSR81                               (RA_IRQ_FIRST + 81)  /* 81:  Event selected in the ICU.IELSR81 register */
#define RA_IRQ_IELSR82                               (RA_IRQ_FIRST + 82)  /* 82:  Event selected in the ICU.IELSR82 register */
#define RA_IRQ_IELSR83                               (RA_IRQ_FIRST + 83)  /* 83:  Event selected in the ICU.IELSR83 register */
#define RA_IRQ_IELSR84                               (RA_IRQ_FIRST + 84)  /* 84:  Event selected in the ICU.IELSR84 register */
#define RA_IRQ_IELSR85                               (RA_IRQ_FIRST + 85)  /* 85:  Event selected in the ICU.IELSR85 register */
#define RA_IRQ_IELSR86                               (RA_IRQ_FIRST + 86)  /* 86:  Event selected in the ICU.IELSR86 register */
#define RA_IRQ_IELSR87                               (RA_IRQ_FIRST + 87)  /* 87:  Event selected in the ICU.IELSR87 register */
#define RA_IRQ_IELSR88                               (RA_IRQ_FIRST + 88)  /* 88:  Event selected in the ICU.IELSR88 register */
#define RA_IRQ_IELSR89                               (RA_IRQ_FIRST + 89)  /* 89:  Event selected in the ICU.IELSR89 register */
#define RA_IRQ_IELSR90                               (RA_IRQ_FIRST + 90)  /* 90:  Event selected in the ICU.IELSR90 register */
#define RA_IRQ_IELSR91                               (RA_IRQ_FIRST + 91)  /* 91:  Event selected in the ICU.IELSR91 register */
#define RA_IRQ_IELSR92                               (RA_IRQ_FIRST + 92)  /* 92:  Event selected in the ICU.IELSR92 register */
#define RA_IRQ_IELSR93                               (RA_IRQ_FIRST + 93)  /* 93:  Event selected in the ICU.IELSR93 register */
#define RA_IRQ_IELSR94                               (RA_IRQ_FIRST + 94)  /* 94:  Event selected in the ICU.IELSR94 register */
#define RA_IRQ_IELSR95                               (RA_IRQ_FIRST + 95)  /* 95:  Event selected in the ICU.IELSR95 register */
#define RA_IRQ_IELSR_SIZE                96  /* 96: Number of IELSR IRQs */

/* RA8P1 has 96 external interrupt vectors + 16 Cortex-M85 core vectors = 112 total but extend to maximum event */
#define RA_IRQ_NEXTINT                   RA_IRQ_IELSR_SIZE

/* Event number definitions based on RA8P1 HWM Event Table 13.4 */
#define RA_ELC_ICU_IRQ0                              (0x001)  /* External pin interrupt 0 - Event 0x001 */
#define RA_ELC_ICU_IRQ1                              (0x002)  /* External pin interrupt 1 - Event 0x002 */
#define RA_ELC_ICU_IRQ2                              (0x003)  /* External pin interrupt 2 - Event 0x003 */
#define RA_ELC_ICU_IRQ3                              (0x004)  /* External pin interrupt 3 - Event 0x004 */
#define RA_ELC_ICU_IRQ4                              (0x005)  /* External pin interrupt 4 - Event 0x005 */
#define RA_ELC_ICU_IRQ5                              (0x006)  /* External pin interrupt 5 - Event 0x006 */
#define RA_ELC_ICU_IRQ6                              (0x007)  /* External pin interrupt 6 - Event 0x007 */
#define RA_ELC_ICU_IRQ7                              (0x008)  /* External pin interrupt 7 - Event 0x008 */
#define RA_ELC_ICU_IRQ8                              (0x009)  /* External pin interrupt 8 - Event 0x009 */
#define RA_ELC_ICU_IRQ9                              (0x00A)  /* External pin interrupt 9 - Event 0x00A */
#define RA_ELC_ICU_IRQ10                             (0x00B)  /* External pin interrupt 10 - Event 0x00B */
#define RA_ELC_ICU_IRQ11                             (0x00C)  /* External pin interrupt 11 - Event 0x00C */
#define RA_ELC_ICU_IRQ12                             (0x00D)  /* External pin interrupt 12 - Event 0x00D */
#define RA_ELC_ICU_IRQ13                             (0x00E)  /* External pin interrupt 13 - Event 0x00E */
#define RA_ELC_ICU_IRQ14                             (0x00F)  /* External pin interrupt 14 - Event 0x00F */
#define RA_ELC_ICU_IRQ15                             (0x010)  /* External pin interrupt 15 - Event 0x010 */
#define RA_ELC_ICU_IRQ16                             (0x011)  /* External pin interrupt 16 - Event 0x011 */
#define RA_ELC_ICU_IRQ17                             (0x012)  /* External pin interrupt 17 - Event 0x012 */
#define RA_ELC_ICU_IRQ18                             (0x013)  /* External pin interrupt 18 - Event 0x013 */
#define RA_ELC_ICU_IRQ19                             (0x014)  /* External pin interrupt 19 - Event 0x014 */
#define RA_ELC_ICU_IRQ20                             (0x015)  /* External pin interrupt 20 - Event 0x015 */
#define RA_ELC_ICU_IRQ21                             (0x016)  /* External pin interrupt 21 - Event 0x016 */
#define RA_ELC_ICU_IRQ22                             (0x017)  /* External pin interrupt 22 - Event 0x017 */
#define RA_ELC_ICU_IRQ23                             (0x018)  /* External pin interrupt 23 - Event 0x018 */
#define RA_ELC_ICU_IRQ24                             (0x019)  /* External pin interrupt 24 - Event 0x019 */
#define RA_ELC_ICU_IRQ25                             (0x01A)  /* External pin interrupt 25 - Event 0x01A */
#define RA_ELC_ICU_IRQ26                             (0x01B)  /* External pin interrupt 26 - Event 0x01B */
#define RA_ELC_ICU_IRQ27                             (0x01C)  /* External pin interrupt 27 - Event 0x01C */
#define RA_ELC_ICU_IRQ28                             (0x01D)  /* External pin interrupt 28 - Event 0x01D */
#define RA_ELC_ICU_IRQ29                             (0x01E)  /* External pin interrupt 29 - Event 0x01E */
#define RA_ELC_ICU_IRQ30                             (0x01F)  /* External pin interrupt 30 - Event 0x01F */
#define RA_ELC_ICU_IRQ31                             (0x020)  /* External pin interrupt 31 - Event 0x020 */
#define RA_ELC_DMAC0_INT                             (0x040)  /* DMAC0 transfer end - Event 0x040 */
#define RA_ELC_DMAC1_INT                             (0x041)  /* DMAC1 transfer end - Event 0x041 */
#define RA_ELC_DMAC2_INT                             (0x042)  /* DMAC2 transfer end - Event 0x042 */
#define RA_ELC_DMAC3_INT                             (0x043)  /* DMAC3 transfer end - Event 0x043 */
#define RA_ELC_DMAC4_INT                             (0x044)  /* DMAC4 transfer end - Event 0x044 */
#define RA_ELC_DMAC5_INT                             (0x045)  /* DMAC5 transfer end - Event 0x045 */
#define RA_ELC_DMAC6_INT                             (0x046)  /* DMAC6 transfer end - Event 0x046 */
#define RA_ELC_DMAC7_INT                             (0x047)  /* DMAC7 transfer end - Event 0x047 */
#define RA_ELC_DMAC10_INT                            (0x048)  /* DMAC10 transfer end - Event 0x048 */
#define RA_ELC_DMAC11_INT                            (0x049)  /* DMAC11 transfer end - Event 0x049 */
#define RA_ELC_DMAC12_INT                            (0x04A)  /* DMAC12 transfer end - Event 0x04A */
#define RA_ELC_DMAC13_INT                            (0x04B)  /* DMAC13 transfer end - Event 0x04B */
#define RA_ELC_DMAC14_INT                            (0x04C)  /* DMAC14 transfer end - Event 0x04C */
#define RA_ELC_DMAC15_INT                            (0x04D)  /* DMAC15 transfer end - Event 0x04D */
#define RA_ELC_DMAC16_INT                            (0x04E)  /* DMAC16 transfer end - Event 0x04E */
#define RA_ELC_DMAC17_INT                            (0x04F)  /* DMAC17 transfer end - Event 0x04F */
#define RA_ELC_DTC_END                               (0x052)  /* DTC transfer end - Event 0x052 */
#define RA_ELC_DTC1_END                              (0x055)  /* DTC1 transfer end - Event 0x055 */
#define RA_ELC_DMA_TRANSERR                          (0x056)  /* DMA/DTC transfer error - Event 0x056 */
#define RA_ELC_DMA1_TRANSERR                         (0x057)  /* DMA1/DTC1 transfer error - Event 0x057 */
#define RA_ELC_DBG_CTIIRQ0                           (0x058)  /* Coresight Crosstrigger Event - Event 0x058 */
#define RA_ELC_DBG_CTIIRQ1                           (0x059)  /* Coresight Crosstrigger Event - Event 0x059 */
#define RA_ELC_DBG_JBRXI                             (0x05A)  /* JB RXI - Event 0x05A */
#define RA_ELC_IPC_IRQ0                              (0x05B)  /* CPU Mutual Interrupt 0 - Event 0x05B */
#define RA_ELC_IPC_IRQ1                              (0x05C)  /* CPU Mutual Interrupt 1 - Event 0x05C */
#define RA_ELC_LM0_ERR                               (0x05F)  /* Local memory 0 error - Event 0x05F */
#define RA_ELC_LM1_ERR                               (0x060)  /* Local memory 1 error - Event 0x060 */
#define RA_ELC_CPU0_LOCKUP                           (0x061)  /* CPU 0 lockup - Event 0x061 */
#define RA_ELC_CPU1_LOCKUP                           (0x062)  /* CPU 1 lockup - Event 0x062 */
#define RA_ELC_BUS_ERR                               (0x063)  /* BUS error - Event 0x063 */
#define RA_ELC_CM_ERR                                (0x064)  /* Common memory error - Event 0x064 */
#define RA_ELC_FPU_EXC                               (0x065)  /* FPU exception - Event 0x065 */
#define RA_ELC_NPU_IRQ                               (0x067)  /* NPU IRQ - Event 0x067 */
#define RA_ELC_MRAM_MRCRD                            (0x068)  /* MRAM read error interrupt for MRC - Event 0x068 */
#define RA_ELC_MRAM_MRERD                            (0x069)  /* MRAM read error interrupt for MRE - Event 0x069 */
#define RA_ELC_MRAM_MRCPR                            (0x06B)  /* MRAM sequencer error interrupt for MRC - Event 0x06B */
#define RA_ELC_MRAM_MREPR                            (0x06C)  /* MRAM sequencer error interrupt for MRE - Event 0x06C */
#define RA_ELC_MRAM_ENDOFPE                          (0x06D)  /* MRAM sequencer ready - Event 0x06D */
#define RA_ELC_LVD_LVD1                              (0x070)  /* Voltage monitor 1 interrupt - Event 0x070 */
#define RA_ELC_LVD_LVD2                              (0x071)  /* Voltage monitor 2 interrupt - Event 0x071 */
#define RA_ELC_VBATT_TADI                            (0x075)  /* VBATT Tamper Detection - Event 0x075 */
#define RA_ELC_CGC_MOSC_STOP                         (0x076)  /* Main Clock oscillation stop - Event 0x076 */
#define RA_ELC_CGC_SOSC_STOP                         (0x077)  /* Sub oscillation stop - Event 0x077 */
#define RA_ELC_ULPT0_INT                             (0x080)  /* ULPT0 Underflow - Event 0x080 */
#define RA_ELC_ULPT0_COMPARE_A                       (0x081)  /* ULPT0 Compare match A - Event 0x081 */
#define RA_ELC_ULPT0_COMPARE_B                       (0x082)  /* ULPT0 Compare match B - Event 0x082 */
#define RA_ELC_ULPT1_INT                             (0x083)  /* ULPT1 Underflow - Event 0x083 */
#define RA_ELC_ULPT1_COMPARE_A                       (0x084)  /* ULPT1 Compare match A - Event 0x084 */
#define RA_ELC_ULPT1_COMPARE_B                       (0x085)  /* ULPT1 Compare match B - Event 0x085 */
#define RA_ELC_AGT0_INT                              (0x086)  /* AGT interrupt - Event 0x086 */
#define RA_ELC_AGT0_COMPARE_A                        (0x087)  /* Compare match A - Event 0x087 */
#define RA_ELC_AGT0_COMPARE_B                        (0x088)  /* Compare match B - Event 0x088 */
#define RA_ELC_AGT1_INT                              (0x089)  /* AGT interrupt - Event 0x089 */
#define RA_ELC_AGT1_COMPARE_A                        (0x08A)  /* Compare match A - Event 0x08A */
#define RA_ELC_AGT1_COMPARE_B                        (0x08B)  /* Compare match B - Event 0x08B */
#define RA_ELC_IWDT_UNDERFLOW                        (0x092)  /* IWDT underflow - Event 0x092 */
#define RA_ELC_WDT0_UNDERFLOW                        (0x093)  /* WDT0 underflow - Event 0x093 */
#define RA_ELC_WDT1_UNDERFLOW                        (0x094)  /* WDT1 underflow - Event 0x094 */
#define RA_ELC_RTC_ALARM                             (0x095)  /* Alarm interrupt - Event 0x095 */
#define RA_ELC_RTC_PERIOD                            (0x096)  /* Periodic interrupt - Event 0x096 */
#define RA_ELC_RTC_CARRY                             (0x097)  /* Carry interrupt - Event 0x097 */
#define RA_ELC_USBFS_FIFO_0                          (0x098)  /* DMA/DTC transfer request 0 - Event 0x098 */
#define RA_ELC_USBFS_FIFO_1                          (0x099)  /* DMA/DTC transfer request 1 - Event 0x099 */
#define RA_ELC_USBFS_INT                             (0x09A)  /* USBFS interrupt - Event 0x09A */
#define RA_ELC_USBFS_RESUME                          (0x09B)  /* USBFS resume interrupt - Event 0x09B */
#define RA_ELC_IIC0_RXI                              (0x09C)  /* Receive data full - Event 0x09C */
#define RA_ELC_IIC0_TXI                              (0x09D)  /* Transmit data empty - Event 0x09D */
#define RA_ELC_IIC0_TEI                              (0x09E)  /* Transmit end - Event 0x09E */
#define RA_ELC_IIC0_ERI                              (0x09F)  /* Transfer error - Event 0x09F */
#define RA_ELC_IIC0_WUI                              (0x0A0)  /* Wakeup interrupt - Event 0x0A0 */
#define RA_ELC_IIC1_RXI                              (0x0A1)  /* Receive data full - Event 0x0A1 */
#define RA_ELC_IIC1_TXI                              (0x0A2)  /* Transmit data empty - Event 0x0A2 */
#define RA_ELC_IIC1_TEI                              (0x0A3)  /* Transmit end - Event 0x0A3 */
#define RA_ELC_IIC1_ERI                              (0x0A4)  /* Transfer error - Event 0x0A4 */
#define RA_ELC_IIC2_RXI                              (0x0A6)  /* Receive data full - Event 0x0A6 */
#define RA_ELC_IIC2_TXI                              (0x0A7)  /* Transmit data empty - Event 0x0A7 */
#define RA_ELC_IIC2_TEI                              (0x0A8)  /* Transmit end - Event 0x0A8 */
#define RA_ELC_IIC2_ERI                              (0x0A9)  /* Transfer error - Event 0x0A9 */
#define RA_ELC_SDHIMMC0_ACCS                         (0x0AB)  /* Card access - Event 0x0AB */
#define RA_ELC_SDHIMMC0_SDIO                         (0x0AC)  /* SDIO access - Event 0x0AC */
#define RA_ELC_SDHIMMC0_CARD                         (0x0AD)  /* Card detect - Event 0x0AD */
#define RA_ELC_SDHIMMC0_DMA_REQ                      (0x0AE)  /* DMA transfer request - Event 0x0AE */
#define RA_ELC_SDHIMMC1_ACCS                         (0x0AF)  /* Card access - Event 0x0AF */
#define RA_ELC_SDHIMMC1_SDIO                         (0x0B0)  /* SDIO access - Event 0x0B0 */
#define RA_ELC_SDHIMMC1_CARD                         (0x0B1)  /* Card detect - Event 0x0B1 */
#define RA_ELC_SDHIMMC1_DMA_REQ                      (0x0B2)  /* DMA transfer request - Event 0x0B2 */
#define RA_ELC_SSI0_TXI                              (0x0B3)  /* Transmit data empty - Event 0x0B3 */
#define RA_ELC_SSI0_RXI                              (0x0B4)  /* Receive data full - Event 0x0B4 */
#define RA_ELC_SSI0_INT                              (0x0B6)  /* Error interrupt - Event 0x0B6 */
#define RA_ELC_SSI1_TXI                              (0x0B9)  /* Receive data full/Transmit data empty - Event 0x0B9 */
#define RA_ELC_SSI1_RXI                              (0x0B9)  /* Receive data full/Transmit data empty - Event 0x0B9 */
#define RA_ELC_SSI1_INT                              (0x0BA)  /* Error interrupt - Event 0x0BA */
#define RA_ELC_XSPI_ERR                              (0x0BB)  /* xSPI Error - Event 0x0BB */
#define RA_ELC_XSPI_CMP                              (0x0BC)  /* xSPI Complete - Event 0x0BC */
#define RA_ELC_XSPI1_ERR                             (0x0BD)  /* xSPI1 Error - Event 0x0BD */
#define RA_ELC_XSPI1_CMP                             (0x0BE)  /* xSPI1 Complete - Event 0x0BE */
#define RA_ELC_PDM_DAT0                              (0x0BF)  /* Data reception interrupt channel 0 - Event 0x0BF */
#define RA_ELC_PDM_DAT1                              (0x0C0)  /* Data reception interrupt channel 1 - Event 0x0C0 */
#define RA_ELC_PDM_DAT2                              (0x0C1)  /* Data reception interrupt channel 2 - Event 0x0C1 */
#define RA_ELC_PDM_SDET                              (0x0C2)  /* Sound detection interrupt - Event 0x0C2 */
#define RA_ELC_PDM_ERR0                              (0x0C3)  /* Error detection interrupt channel 0 - Event 0x0C3 */
#define RA_ELC_PDM_ERR1                              (0x0C4)  /* Error detection interrupt channel 1 - Event 0x0C4 */
#define RA_ELC_PDM_ERR2                              (0x0C5)  /* Error detection interrupt channel 2 - Event 0x0C5 */
#define RA_ELC_ACMPHS0_INT                           (0x0C6)  /* High Speed Comparator channel 0 interrupt - Event 0x0C6 */
#define RA_ELC_ACMPHS1_INT                           (0x0C7)  /* High Speed Comparator channel 1 interrupt - Event 0x0C7 */
#define RA_ELC_ACMPHS2_INT                           (0x0C8)  /* High Speed Comparator channel 2 interrupt - Event 0x0C8 */
#define RA_ELC_ACMPHS3_INT                           (0x0C9)  /* High Speed Comparator channel 3 interrupt - Event 0x0C9 */
#define RA_ELC_ELC_SOFTWARE_EVENT_0                  (0x0CC)  /* Software event 0 - Event 0x0CC */
#define RA_ELC_ELC_SOFTWARE_EVENT_1                  (0x0CD)  /* Software event 1 - Event 0x0CD */
#define RA_ELC_ELC_SOFTWARE_EVENT_2                  (0x0CE)  /* Software event 2 - Event 0x0CE */
#define RA_ELC_ELC_SOFTWARE_EVENT_3                  (0x0CF)  /* Software event 3 - Event 0x0CF */
#define RA_ELC_IOPORT_EVENT_1                        (0x0D0)  /* Port 1 event - Event 0x0D0 */
#define RA_ELC_IOPORT_EVENT_2                        (0x0D1)  /* Port 2 event - Event 0x0D1 */
#define RA_ELC_IOPORT_EVENT_3                        (0x0D2)  /* Port 3 event - Event 0x0D2 */
#define RA_ELC_IOPORT_EVENT_4                        (0x0D3)  /* Port 4 event - Event 0x0D3 */
#define RA_ELC_CAC_FREQUENCY_ERROR                   (0x0D4)  /* Frequency error interrupt - Event 0x0D4 */
#define RA_ELC_CAC_MEASUREMENT_END                   (0x0D5)  /* Measurement end interrupt - Event 0x0D5 */
#define RA_ELC_CAC_OVERFLOW                          (0x0D6)  /* Overflow interrupt - Event 0x0D6 */
#define RA_ELC_POEG0_EVENT                           (0x0D7)  /* Port Output disable 0 interrupt - Event 0x0D7 */
#define RA_ELC_POEG1_EVENT                           (0x0D8)  /* Port Output disable 1 interrupt - Event 0x0D8 */
#define RA_ELC_POEG2_EVENT                           (0x0D9)  /* Port Output disable 2 interrupt - Event 0x0D9 */
#define RA_ELC_POEG3_EVENT                           (0x0DA)  /* Port Output disable 3 interrupt - Event 0x0DA */
#define RA_ELC_OPS_UVW_EDGE                          (0x180)  /* UVW edge event - Event 0x180 */
#define RA_ELC_GPT0_CAPTURE_COMPARE_A                (0x181)  /* Capture/Compare match A - Event 0x181 */
#define RA_ELC_GPT0_CAPTURE_COMPARE_B                (0x182)  /* Capture/Compare match B - Event 0x182 */
#define RA_ELC_GPT0_COMPARE_C                        (0x183)  /* Compare match C - Event 0x183 */
#define RA_ELC_GPT0_COMPARE_D                        (0x184)  /* Compare match D - Event 0x184 */
#define RA_ELC_GPT0_COMPARE_E                        (0x185)  /* Compare match E - Event 0x185 */
#define RA_ELC_GPT0_COMPARE_F                        (0x186)  /* Compare match F - Event 0x186 */
#define RA_ELC_GPT0_COUNTER_OVERFLOW                 (0x187)  /* Overflow - Event 0x187 */
#define RA_ELC_GPT0_COUNTER_UNDERFLOW                (0x188)  /* Underflow - Event 0x188 */
#define RA_ELC_GPT0_PC                               (0x189)  /* Period count function finish - Event 0x189 */
#define RA_ELC_GPT1_CAPTURE_COMPARE_A                (0x18A)  /* Capture/Compare match A - Event 0x18A */
#define RA_ELC_GPT1_CAPTURE_COMPARE_B                (0x18B)  /* Capture/Compare match B - Event 0x18B */
#define RA_ELC_GPT1_COMPARE_C                        (0x18C)  /* Compare match C - Event 0x18C */
#define RA_ELC_GPT1_COMPARE_D                        (0x18D)  /* Compare match D - Event 0x18D */
#define RA_ELC_GPT1_COMPARE_E                        (0x18E)  /* Compare match E - Event 0x18E */
#define RA_ELC_GPT1_COMPARE_F                        (0x18F)  /* Compare match F - Event 0x18F */
#define RA_ELC_GPT1_COUNTER_OVERFLOW                 (0x190)  /* Overflow - Event 0x190 */
#define RA_ELC_GPT1_COUNTER_UNDERFLOW                (0x191)  /* Underflow - Event 0x191 */
#define RA_ELC_GPT1_PC                               (0x192)  /* Period count function finish - Event 0x192 */
#define RA_ELC_GPT2_CAPTURE_COMPARE_A                (0x193)  /* Capture/Compare match A - Event 0x193 */
#define RA_ELC_GPT2_CAPTURE_COMPARE_B                (0x194)  /* Capture/Compare match B - Event 0x194 */
#define RA_ELC_GPT2_COMPARE_C                        (0x195)  /* Compare match C - Event 0x195 */
#define RA_ELC_GPT2_COMPARE_D                        (0x196)  /* Compare match D - Event 0x196 */
#define RA_ELC_GPT2_COMPARE_E                        (0x197)  /* Compare match E - Event 0x197 */
#define RA_ELC_GPT2_COMPARE_F                        (0x198)  /* Compare match F - Event 0x198 */
#define RA_ELC_GPT2_COUNTER_OVERFLOW                 (0x199)  /* Overflow - Event 0x199 */
#define RA_ELC_GPT2_COUNTER_UNDERFLOW                (0x19A)  /* Underflow - Event 0x19A */
#define RA_ELC_GPT2_PC                               (0x19B)  /* Period count function finish - Event 0x19B */
#define RA_ELC_GPT3_CAPTURE_COMPARE_A                (0x19C)  /* Capture/Compare match A - Event 0x19C */
#define RA_ELC_GPT3_CAPTURE_COMPARE_B                (0x19D)  /* Capture/Compare match B - Event 0x19D */
#define RA_ELC_GPT3_COMPARE_C                        (0x19E)  /* Compare match C - Event 0x19E */
#define RA_ELC_GPT3_COMPARE_D                        (0x19F)  /* Compare match D - Event 0x19F */
#define RA_ELC_GPT3_COMPARE_E                        (0x1A0)  /* Compare match E - Event 0x1A0 */
#define RA_ELC_GPT3_COMPARE_F                        (0x1A1)  /* Compare match F - Event 0x1A1 */
#define RA_ELC_GPT3_COUNTER_OVERFLOW                 (0x1A2)  /* Overflow - Event 0x1A2 */
#define RA_ELC_GPT3_COUNTER_UNDERFLOW                (0x1A3)  /* Underflow - Event 0x1A3 */
#define RA_ELC_GPT3_PC                               (0x1A4)  /* Period count function finish - Event 0x1A4 */
#define RA_ELC_GPT4_CAPTURE_COMPARE_A                (0x1A5)  /* Capture/Compare match A - Event 0x1A5 */
#define RA_ELC_GPT4_CAPTURE_COMPARE_B                (0x1A6)  /* Capture/Compare match B - Event 0x1A6 */
#define RA_ELC_GPT4_COMPARE_C                        (0x1A7)  /* Compare match C - Event 0x1A7 */
#define RA_ELC_GPT4_COMPARE_D                        (0x1A8)  /* Compare match D - Event 0x1A8 */
#define RA_ELC_GPT4_COMPARE_E                        (0x1A9)  /* Compare match E - Event 0x1A9 */
#define RA_ELC_GPT4_COMPARE_F                        (0x1AA)  /* Compare match F - Event 0x1AA */
#define RA_ELC_GPT4_COUNTER_OVERFLOW                 (0x1AB)  /* Overflow - Event 0x1AB */
#define RA_ELC_GPT4_COUNTER_UNDERFLOW                (0x1AC)  /* Underflow - Event 0x1AC */
#define RA_ELC_GPT5_CAPTURE_COMPARE_A                (0x1AE)  /* Capture/Compare match A - Event 0x1AE */
#define RA_ELC_GPT5_CAPTURE_COMPARE_B                (0x1AF)  /* Capture/Compare match B - Event 0x1AF */
#define RA_ELC_GPT5_COMPARE_C                        (0x1B0)  /* Compare match C - Event 0x1B0 */
#define RA_ELC_GPT5_COMPARE_D                        (0x1B1)  /* Compare match D - Event 0x1B1 */
#define RA_ELC_GPT5_COMPARE_E                        (0x1B2)  /* Compare match E - Event 0x1B2 */
#define RA_ELC_GPT5_COMPARE_F                        (0x1B3)  /* Compare match F - Event 0x1B3 */
#define RA_ELC_GPT5_COUNTER_OVERFLOW                 (0x1B4)  /* Overflow - Event 0x1B4 */
#define RA_ELC_GPT5_COUNTER_UNDERFLOW                (0x1B5)  /* Underflow - Event 0x1B5 */
#define RA_ELC_GPT6_CAPTURE_COMPARE_A                (0x1B7)  /* Capture/Compare match A - Event 0x1B7 */
#define RA_ELC_GPT6_CAPTURE_COMPARE_B                (0x1B8)  /* Capture/Compare match B - Event 0x1B8 */
#define RA_ELC_GPT6_COMPARE_C                        (0x1B9)  /* Compare match C - Event 0x1B9 */
#define RA_ELC_GPT6_COMPARE_D                        (0x1BA)  /* Compare match D - Event 0x1BA */
#define RA_ELC_GPT6_COMPARE_E                        (0x1BB)  /* Compare match E - Event 0x1BB */
#define RA_ELC_GPT6_COMPARE_F                        (0x1BC)  /* Compare match F - Event 0x1BC */
#define RA_ELC_GPT6_COUNTER_OVERFLOW                 (0x1BD)  /* Overflow - Event 0x1BD */
#define RA_ELC_GPT6_COUNTER_UNDERFLOW                (0x1BE)  /* Underflow - Event 0x1BE */
#define RA_ELC_GPT7_CAPTURE_COMPARE_A                (0x1C0)  /* Capture/Compare match A - Event 0x1C0 */
#define RA_ELC_GPT7_CAPTURE_COMPARE_B                (0x1C1)  /* Capture/Compare match B - Event 0x1C1 */
#define RA_ELC_GPT7_COMPARE_C                        (0x1C2)  /* Compare match C - Event 0x1C2 */
#define RA_ELC_GPT7_COMPARE_D                        (0x1C3)  /* Compare match D - Event 0x1C3 */
#define RA_ELC_GPT7_COMPARE_E                        (0x1C4)  /* Compare match E - Event 0x1C4 */
#define RA_ELC_GPT7_COMPARE_F                        (0x1C5)  /* Compare match F - Event 0x1C5 */
#define RA_ELC_GPT7_COUNTER_OVERFLOW                 (0x1C6)  /* Overflow - Event 0x1C6 */
#define RA_ELC_GPT7_COUNTER_UNDERFLOW                (0x1C7)  /* Underflow - Event 0x1C7 */
#define RA_ELC_GPT8_CAPTURE_COMPARE_A                (0x1C9)  /* Capture/Compare match A - Event 0x1C9 */
#define RA_ELC_GPT8_CAPTURE_COMPARE_B                (0x1CA)  /* Capture/Compare match B - Event 0x1CA */
#define RA_ELC_GPT8_COMPARE_C                        (0x1CB)  /* Compare match C - Event 0x1CB */
#define RA_ELC_GPT8_COMPARE_D                        (0x1CC)  /* Compare match D - Event 0x1CC */
#define RA_ELC_GPT8_COMPARE_E                        (0x1CD)  /* Compare match E - Event 0x1CD */
#define RA_ELC_GPT8_COMPARE_F                        (0x1CE)  /* Compare match F - Event 0x1CE */
#define RA_ELC_GPT8_COUNTER_OVERFLOW                 (0x1CF)  /* Overflow - Event 0x1CF */
#define RA_ELC_GPT8_COUNTER_UNDERFLOW                (0x1D0)  /* Underflow - Event 0x1D0 */
#define RA_ELC_GPT9_CAPTURE_COMPARE_A                (0x1D2)  /* Capture/Compare match A - Event 0x1D2 */
#define RA_ELC_GPT9_CAPTURE_COMPARE_B                (0x1D3)  /* Capture/Compare match B - Event 0x1D3 */
#define RA_ELC_GPT9_COMPARE_C                        (0x1D4)  /* Compare match C - Event 0x1D4 */
#define RA_ELC_GPT9_COMPARE_D                        (0x1D5)  /* Compare match D - Event 0x1D5 */
#define RA_ELC_GPT9_COMPARE_E                        (0x1D6)  /* Compare match E - Event 0x1D6 */
#define RA_ELC_GPT9_COMPARE_F                        (0x1D7)  /* Compare match F - Event 0x1D7 */
#define RA_ELC_GPT9_COUNTER_OVERFLOW                 (0x1D8)  /* Overflow - Event 0x1D8 */
#define RA_ELC_GPT9_COUNTER_UNDERFLOW                (0x1D9)  /* Underflow - Event 0x1D9 */
#define RA_ELC_GPT10_CAPTURE_COMPARE_A               (0x1DB)  /* Capture/Compare match A - Event 0x1DB */
#define RA_ELC_GPT10_CAPTURE_COMPARE_B               (0x1DC)  /* Capture/Compare match B - Event 0x1DC */
#define RA_ELC_GPT10_COMPARE_C                       (0x1DD)  /* Compare match C - Event 0x1DD */
#define RA_ELC_GPT10_COMPARE_D                       (0x1DE)  /* Compare match D - Event 0x1DE */
#define RA_ELC_GPT10_COMPARE_E                       (0x1DF)  /* Compare match E - Event 0x1DF */
#define RA_ELC_GPT10_COMPARE_F                       (0x1E0)  /* Compare match F - Event 0x1E0 */
#define RA_ELC_GPT10_COUNTER_OVERFLOW                (0x1E1)  /* Overflow - Event 0x1E1 */
#define RA_ELC_GPT10_COUNTER_UNDERFLOW               (0x1E2)  /* Underflow - Event 0x1E2 */
#define RA_ELC_GPT10_PC                              (0x1E3)  /* Period count function finish - Event 0x1E3 */
#define RA_ELC_GPT11_CAPTURE_COMPARE_A               (0x1E4)  /* Capture/Compare match A - Event 0x1E4 */
#define RA_ELC_GPT11_CAPTURE_COMPARE_B               (0x1E5)  /* Capture/Compare match B - Event 0x1E5 */
#define RA_ELC_GPT11_COMPARE_C                       (0x1E6)  /* Compare match C - Event 0x1E6 */
#define RA_ELC_GPT11_COMPARE_D                       (0x1E7)  /* Compare match D - Event 0x1E7 */
#define RA_ELC_GPT11_COMPARE_E                       (0x1E8)  /* Compare match E - Event 0x1E8 */
#define RA_ELC_GPT11_COMPARE_F                       (0x1E9)  /* Compare match F - Event 0x1E9 */
#define RA_ELC_GPT11_COUNTER_OVERFLOW                (0x1EA)  /* Overflow - Event 0x1EA */
#define RA_ELC_GPT11_COUNTER_UNDERFLOW               (0x1EB)  /* Underflow - Event 0x1EB */
#define RA_ELC_GPT11_PC                              (0x1EC)  /* Period count function finish - Event 0x1EC */
#define RA_ELC_GPT12_CAPTURE_COMPARE_A               (0x1ED)  /* Capture/Compare match A - Event 0x1ED */
#define RA_ELC_GPT12_CAPTURE_COMPARE_B               (0x1EE)  /* Capture/Compare match B - Event 0x1EE */
#define RA_ELC_GPT12_COMPARE_C                       (0x1EF)  /* Compare match C - Event 0x1EF */
#define RA_ELC_GPT12_COMPARE_D                       (0x1F0)  /* Compare match D - Event 0x1F0 */
#define RA_ELC_GPT12_COMPARE_E                       (0x1F1)  /* Compare match E - Event 0x1F1 */
#define RA_ELC_GPT12_COMPARE_F                       (0x1F2)  /* Compare match F - Event 0x1F2 */
#define RA_ELC_GPT12_COUNTER_OVERFLOW                (0x1F3)  /* Overflow - Event 0x1F3 */
#define RA_ELC_GPT12_COUNTER_UNDERFLOW               (0x1F4)  /* Underflow - Event 0x1F4 */
#define RA_ELC_GPT12_PC                              (0x1F5)  /* Period count function finish - Event 0x1F5 */
#define RA_ELC_GPT13_CAPTURE_COMPARE_A               (0x1F6)  /* Capture/Compare match A - Event 0x1F6 */
#define RA_ELC_GPT13_CAPTURE_COMPARE_B               (0x1F7)  /* Capture/Compare match B - Event 0x1F7 */
#define RA_ELC_GPT13_COMPARE_C                       (0x1F8)  /* Compare match C - Event 0x1F8 */
#define RA_ELC_GPT13_COMPARE_D                       (0x1F9)  /* Compare match D - Event 0x1F9 */
#define RA_ELC_GPT13_COMPARE_E                       (0x1FA)  /* Compare match E - Event 0x1FA */
#define RA_ELC_GPT13_COMPARE_F                       (0x1FB)  /* Compare match F - Event 0x1FB */
#define RA_ELC_GPT13_COUNTER_OVERFLOW                (0x1FC)  /* Overflow - Event 0x1FC */
#define RA_ELC_GPT13_COUNTER_UNDERFLOW               (0x1FD)  /* Underflow - Event 0x1FD */
#define RA_ELC_GPT13_PC                              (0x1FE)  /* Period count function finish - Event 0x1FE */
#define RA_ELC_ETHER_FWEI                            (0x29A)  /* Forwarding Error Interrupt - Event 0x29A */
#define RA_ELC_ETHER_CAEI                            (0x29B)  /* Common Error Interrupt - Event 0x29B */
#define RA_ELC_ETHER_GWEI                            (0x29C)  /* GWCA0 Error Interrupt - Event 0x29C */
#define RA_ELC_ETHER_EAEI0                           (0x29D)  /* ETHA0 Error Interrupt - Event 0x29D */
#define RA_ELC_ETHER_EAEI1                           (0x29E)  /* ETHA1 Error Interrupt - Event 0x29E */
#define RA_ELC_ETHER_PTPSI0                          (0x29F)  /* gPTP Status Interrupt 0 - Event 0x29F */
#define RA_ELC_ETHER_PTPSI1                          (0x2A0)  /* gPTP Status Interrupt 1 - Event 0x2A0 */
#define RA_ELC_ETHER_FWSI                            (0x2A1)  /* Forwarding Status Interrupt - Event 0x2A1 */
#define RA_ELC_ETHER_SWSI                            (0x2A2)  /* Switch Status Interrupt - Event 0x2A2 */
#define RA_ELC_ETHER_CAMI                            (0x2A3)  /* Common Status Interrupt - Event 0x2A3 */
#define RA_ELC_ETHER_EASI0                           (0x2A4)  /* ETHA0 Status Interrupt - Event 0x2A4 */
#define RA_ELC_ETHER_EASI1                           (0x2A5)  /* ETHA1 Status Interrupt - Event 0x2A5 */
#define RA_ELC_ETHER_GWDI0                           (0x2A6)  /* GWCA Data Interrupt 0 - Event 0x2A6 */
#define RA_ELC_ETHER_GWDI1                           (0x2A7)  /* GWCA Data Interrupt 1 - Event 0x2A7 */
#define RA_ELC_ETHER_GWDI2                           (0x2A8)  /* GWCA Data Interrupt 2 - Event 0x2A8 */
#define RA_ELC_ETHER_GWDI3                           (0x2A9)  /* GWCA Data Interrupt 3 - Event 0x2A9 */
#define RA_ELC_ETHER_GWDI4                           (0x2AA)  /* GWCA Data Interrupt 4 - Event 0x2AA */
#define RA_ELC_ETHER_GWDI5                           (0x2AB)  /* GWCA Data Interrupt 5 - Event 0x2AB */
#define RA_ELC_ETHER_GWDI6                           (0x2AC)  /* GWCA Data Interrupt 6 - Event 0x2AC */
#define RA_ELC_ETHER_GWDI7                           (0x2AD)  /* GWCA Data Interrupt 7 - Event 0x2AD */
#define RA_ELC_ETHER_TSDI0                           (0x2AE)  /* Time Stamp Data Interrupt 0 - Event 0x2AE */
#define RA_ELC_ETHER_TSDI1                           (0x2AF)  /* Time Stamp Data Interrupt 1 - Event 0x2AF */
#define RA_ELC_ETHER_MDIO0                           (0x2B0)  /* MDIO Interrupt 0 - Event 0x2B0 */
#define RA_ELC_ETHER_MDIO1                           (0x2B1)  /* MDIO Interrupt 1 - Event 0x2B1 */
#define RA_ELC_ETHER_RMPI0                           (0x2B2)  /* RMAC0 PHY Interrupt - Event 0x2B2 */
#define RA_ELC_ETHER_RMPI1                           (0x2B3)  /* RMAC1 PHY Interrupt - Event 0x2B3 */
#define RA_ELC_GPTP_PTPOUT0                          (0x2B4)  /* PTP Pulse Out 0 - Event 0x2B4 */
#define RA_ELC_GPTP_PTPOUT1                          (0x2B5)  /* PTP Pulse Out 1 - Event 0x2B5 */
#define RA_ELC_GPTP_PTPOUT2                          (0x2B6)  /* PTP Pulse Out 2 - Event 0x2B6 */
#define RA_ELC_GPTP_PTPOUT3                          (0x2B7)  /* PTP Pulse Out 3 - Event 0x2B7 */
#define RA_ELC_GPTP0_MATCH                           (0x2B8)  /* Media Clock Recovery Match - Event 0x2B8 */
#define RA_ELC_GPTP1_MATCH                           (0x2B9)  /* Media Clock Recovery Match - Event 0x2B9 */
#define RA_ELC_USBHS_FIFO_0                          (0x2C1)  /* DMA transfer request 0 - Event 0x2C1 */
#define RA_ELC_USBHS_FIFO_1                          (0x2C2)  /* DMA transfer request 1 - Event 0x2C2 */
#define RA_ELC_USBHS_USB_INT_RESUME                  (0x2C3)  /* USBHS interrupt - Event 0x2C3 */
#define RA_ELC_SCI0_RXI                              (0x2C4)  /* Receive data full - Event 0x2C4 */
#define RA_ELC_SCI0_TXI                              (0x2C5)  /* Transmit data empty - Event 0x2C5 */
#define RA_ELC_SCI0_TEI                              (0x2C6)  /* Transmit end - Event 0x2C6 */
#define RA_ELC_SCI0_ERI                              (0x2C7)  /* Receive error - Event 0x2C7 */
#define RA_ELC_SCI0_AED                              (0x2C8)  /* Active edge detection - Event 0x2C8 */
#define RA_ELC_SCI0_BFD                              (0x2C9)  /* Break field detection - Event 0x2C9 */
#define RA_ELC_SCI0_AM                               (0x2CA)  /* Address match event - Event 0x2CA */
#define RA_ELC_SCI1_RXI                              (0x2CB)  /* Receive data full - Event 0x2CB */
#define RA_ELC_SCI1_TXI                              (0x2CC)  /* Transmit data empty - Event 0x2CC */
#define RA_ELC_SCI1_TEI                              (0x2CD)  /* Transmit end - Event 0x2CD */
#define RA_ELC_SCI1_ERI                              (0x2CE)  /* Receive error - Event 0x2CE */
#define RA_ELC_SCI1_AED                              (0x2CF)  /* Active edge detection - Event 0x2CF */
#define RA_ELC_SCI1_BFD                              (0x2D0)  /* Break field detection - Event 0x2D0 */
#define RA_ELC_SCI1_AM                               (0x2D1)  /* Address match event - Event 0x2D1 */
#define RA_ELC_SCI2_RXI                              (0x2D2)  /* Receive data full - Event 0x2D2 */
#define RA_ELC_SCI2_TXI                              (0x2D3)  /* Transmit data empty - Event 0x2D3 */
#define RA_ELC_SCI2_TEI                              (0x2D4)  /* Transmit end - Event 0x2D4 */
#define RA_ELC_SCI2_ERI                              (0x2D5)  /* Receive error - Event 0x2D5 */
#define RA_ELC_SCI2_AED                              (0x2D6)  /* Active edge detection - Event 0x2D6 */
#define RA_ELC_SCI2_BFD                              (0x2D7)  /* Break field detection - Event 0x2D7 */
#define RA_ELC_SCI2_AM                               (0x2D8)  /* Address match event - Event 0x2D8 */
#define RA_ELC_SCI3_RXI                              (0x2D9)  /* Receive data full - Event 0x2D9 */
#define RA_ELC_SCI3_TXI                              (0x2DA)  /* Transmit data empty - Event 0x2DA */
#define RA_ELC_SCI3_TEI                              (0x2DB)  /* Transmit end - Event 0x2DB */
#define RA_ELC_SCI3_ERI                              (0x2DC)  /* Receive error - Event 0x2DC */
#define RA_ELC_SCI3_AED                              (0x2DD)  /* Active edge detection - Event 0x2DD */
#define RA_ELC_SCI3_BFD                              (0x2DE)  /* Break field detection - Event 0x2DE */
#define RA_ELC_SCI3_AM                               (0x2DF)  /* Address match event - Event 0x2DF */
#define RA_ELC_SCI4_RXI                              (0x2E0)  /* Receive data full - Event 0x2E0 */
#define RA_ELC_SCI4_TXI                              (0x2E1)  /* Transmit data empty - Event 0x2E1 */
#define RA_ELC_SCI4_TEI                              (0x2E2)  /* Transmit end - Event 0x2E2 */
#define RA_ELC_SCI4_ERI                              (0x2E3)  /* Receive error - Event 0x2E3 */
#define RA_ELC_SCI4_AED                              (0x2E4)  /* Active edge detection - Event 0x2E4 */
#define RA_ELC_SCI4_BFD                              (0x2E5)  /* Break field detection - Event 0x2E5 */
#define RA_ELC_SCI4_AM                               (0x2E6)  /* Address match event - Event 0x2E6 */
#define RA_ELC_SCI5_RXI                              (0x2E7)  /* Receive data full - Event 0x2E7 */
#define RA_ELC_SCI5_TXI                              (0x2E8)  /* Transmit data empty - Event 0x2E8 */
#define RA_ELC_SCI5_TEI                              (0x2E9)  /* Transmit end - Event 0x2E9 */
#define RA_ELC_SCI5_ERI                              (0x2EA)  /* Receive error - Event 0x2EA */
#define RA_ELC_SCI5_AED                              (0x2EB)  /* Active edge detection - Event 0x2EB */
#define RA_ELC_SCI5_BFD                              (0x2EC)  /* Break field detection - Event 0x2EC */
#define RA_ELC_SCI5_AM                               (0x2ED)  /* Address match event - Event 0x2ED */
#define RA_ELC_SCI6_RXI                              (0x2EE)  /* Receive data full - Event 0x2EE */
#define RA_ELC_SCI6_TXI                              (0x2EF)  /* Transmit data empty - Event 0x2EF */
#define RA_ELC_SCI6_TEI                              (0x2F0)  /* Transmit end - Event 0x2F0 */
#define RA_ELC_SCI6_ERI                              (0x2F1)  /* Receive error - Event 0x2F1 */
#define RA_ELC_SCI6_AED                              (0x2F2)  /* Active edge detection - Event 0x2F2 */
#define RA_ELC_SCI6_BFD                              (0x2F3)  /* Break field detection - Event 0x2F3 */
#define RA_ELC_SCI6_AM                               (0x2F4)  /* Address match event - Event 0x2F4 */
#define RA_ELC_SCI7_RXI                              (0x2F5)  /* Receive data full - Event 0x2F5 */
#define RA_ELC_SCI7_TXI                              (0x2F6)  /* Transmit data empty - Event 0x2F6 */
#define RA_ELC_SCI7_TEI                              (0x2F7)  /* Transmit end - Event 0x2F7 */
#define RA_ELC_SCI7_ERI                              (0x2F8)  /* Receive error - Event 0x2F8 */
#define RA_ELC_SCI7_AED                              (0x2F9)  /* Active edge detection - Event 0x2F9 */
#define RA_ELC_SCI7_BFD                              (0x2FA)  /* Break field detection - Event 0x2FA */
#define RA_ELC_SCI7_AM                               (0x2FB)  /* Address match event - Event 0x2FB */
#define RA_ELC_SCI8_RXI                              (0x2FC)  /* Receive data full - Event 0x2FC */
#define RA_ELC_SCI8_TXI                              (0x2FD)  /* Transmit data empty - Event 0x2FD */
#define RA_ELC_SCI8_TEI                              (0x2FE)  /* Transmit end - Event 0x2FE */
#define RA_ELC_SCI8_ERI                              (0x2FF)  /* Receive error - Event 0x2FF */
#define RA_ELC_SCI8_AED                              (0x300)  /* Active edge detection - Event 0x300 */
#define RA_ELC_SCI8_BFD                              (0x301)  /* Break field detection - Event 0x301 */
#define RA_ELC_SCI8_AM                               (0x302)  /* Address match event - Event 0x302 */
#define RA_ELC_SCI9_RXI                              (0x303)  /* Receive data full - Event 0x303 */
#define RA_ELC_SCI9_TXI                              (0x304)  /* Transmit data empty - Event 0x304 */
#define RA_ELC_SCI9_TEI                              (0x305)  /* Transmit end - Event 0x305 */
#define RA_ELC_SCI9_ERI                              (0x306)  /* Receive error - Event 0x306 */
#define RA_ELC_SCI9_AED                              (0x307)  /* Active edge detection - Event 0x307 */
#define RA_ELC_SCI9_BFD                              (0x308)  /* Break field detection - Event 0x308 */
#define RA_ELC_SCI9_AM                               (0x309)  /* Address match event - Event 0x309 */
#define RA_ELC_SCI10_RXI                             (0x30A)  /* Receive data full - Event 0x30A */
#define RA_ELC_SCI10_TXI                             (0x30B)  /* Transmit data empty - Event 0x30B */
#define RA_ELC_SCI10_TEI                             (0x30C)  /* Transmit end - Event 0x30C */
#define RA_ELC_SCI10_ERI                             (0x30D)  /* Receive error - Event 0x30D */
#define RA_ELC_SCI10_AED                             (0x30E)  /* Active edge detection - Event 0x30E */
#define RA_ELC_SCI10_BFD                             (0x30F)  /* Break field detection - Event 0x30F */
#define RA_ELC_SCI10_AM                              (0x310)  /* Address match event - Event 0x310 */
#define RA_ELC_SCI11_RXI                             (0x311)  /* Receive data full - Event 0x311 */
#define RA_ELC_SCI11_TXI                             (0x312)  /* Transmit data empty - Event 0x312 */
#define RA_ELC_SCI11_TEI                             (0x313)  /* Transmit end - Event 0x313 */
#define RA_ELC_SCI11_ERI                             (0x314)  /* Receive error - Event 0x314 */
#define RA_ELC_SCI11_AED                             (0x315)  /* Active edge detection - Event 0x315 */
#define RA_ELC_SCI11_BFD                             (0x316)  /* Break field detection - Event 0x316 */
#define RA_ELC_SCI11_AM                              (0x317)  /* Address match event - Event 0x317 */
#define RA_ELC_SPI0_RXI                              (0x318)  /* Receive buffer full - Event 0x318 */
#define RA_ELC_SPI0_TXI                              (0x319)  /* Transmit buffer empty - Event 0x319 */
#define RA_ELC_SPI0_IDLE                             (0x31A)  /* Idle - Event 0x31A */
#define RA_ELC_SPI0_ERI                              (0x31B)  /* Error - Event 0x31B */
#define RA_ELC_SPI0_TEI                              (0x31C)  /* Transmission complete event - Event 0x31C */
#define RA_ELC_SPI1_RXI                              (0x31D)  /* Receive buffer full - Event 0x31D */
#define RA_ELC_SPI1_TXI                              (0x31E)  /* Transmit buffer empty - Event 0x31E */
#define RA_ELC_SPI1_IDLE                             (0x31F)  /* Idle - Event 0x31F */
#define RA_ELC_SPI1_ERI                              (0x320)  /* Error - Event 0x320 */
#define RA_ELC_SPI1_TEI                              (0x321)  /* Transmission complete event - Event 0x321 */
#define RA_ELC_CAN_RXF                               (0x322)  /* Global receive FIFO interrupt - Event 0x322 */
#define RA_ELC_CAN_GLERR                             (0x323)  /* Global error - Event 0x323 */
#define RA_ELC_CAN0_DMAREQ0                          (0x324)  /* RX fifo DMA request 0 - Event 0x324 */
#define RA_ELC_CAN0_DMAREQ1                          (0x325)  /* RX fifo DMA request 1 - Event 0x325 */
#define RA_ELC_CAN1_DMAREQ0                          (0x328)  /* RX fifo DMA request 0 - Event 0x328 */
#define RA_ELC_CAN1_DMAREQ1                          (0x329)  /* RX fifo DMA request 1 - Event 0x329 */
#define RA_ELC_CAN0_TX                               (0x32C)  /* Transmit interrupt - Event 0x32C */
#define RA_ELC_CAN0_CHERR                            (0x32D)  /* Channel  error - Event 0x32D */
#define RA_ELC_CAN0_COMFRX                           (0x32E)  /* Common FIFO receive interrupt - Event 0x32E */
#define RA_ELC_CAN0_CF_DMAREQ                        (0x32F)  /* Channel  DMA request - Event 0x32F */
#define RA_ELC_CAN0_RXMB                             (0x330)  /* Receive message buffer interrupt - Event 0x330 */
#define RA_ELC_CAN1_TX                               (0x331)  /* Transmit interrupt - Event 0x331 */
#define RA_ELC_CAN1_CHERR                            (0x332)  /* Channel  error - Event 0x332 */
#define RA_ELC_CAN1_COMFRX                           (0x333)  /* Common FIFO receive interrupt - Event 0x333 */
#define RA_ELC_CAN1_CF_DMAREQ                        (0x334)  /* Channel  DMA request - Event 0x334 */
#define RA_ELC_CAN1_RXMB                             (0x335)  /* Receive message buffer interrupt - Event 0x335 */
#define RA_ELC_CAN0_MRAM_ERI                         (0x338)  /* CANFD0 ECC error - Event 0x338 */
#define RA_ELC_CAN1_MRAM_ERI                         (0x339)  /* CANFD1 ECC error - Event 0x339 */
#define RA_ELC_I3C0_RESPONSE                         (0x33A)  /* Response status buffer full - Event 0x33A */
#define RA_ELC_I3C0_COMMAND                          (0x33B)  /* Command buffer empty - Event 0x33B */
#define RA_ELC_I3C0_IBI                              (0x33C)  /* IBI status buffer full - Event 0x33C */
#define RA_ELC_I3C0_RX                               (0x33D)  /* Receive - Event 0x33D */
#define RA_ELC_IICB0_RXI                             (0x33D)  /* Receive - Event 0x33D */
#define RA_ELC_I3C0_TX                               (0x33E)  /* Transmit - Event 0x33E */
#define RA_ELC_IICB0_TXI                             (0x33E)  /* Transmit - Event 0x33E */
#define RA_ELC_I3C0_RCV_STATUS                       (0x33F)  /* Receive status buffer full - Event 0x33F */
#define RA_ELC_I3C0_HRESP                            (0x340)  /* High priority response queue full - Event 0x340 */
#define RA_ELC_I3C0_HCMD                             (0x341)  /* High priority command queue empty - Event 0x341 */
#define RA_ELC_I3C0_HRX                              (0x342)  /* High priority rx data buffer full - Event 0x342 */
#define RA_ELC_I3C0_HTX                              (0x343)  /* High priority tx data buffer empty - Event 0x343 */
#define RA_ELC_I3C0_TEND                             (0x344)  /* Transmit end - Event 0x344 */
#define RA_ELC_IICB0_TEI                             (0x344)  /* Transmit end - Event 0x344 */
#define RA_ELC_I3C0_EEI                              (0x345)  /* Error - Event 0x345 */
#define RA_ELC_IICB0_ERI                             (0x345)  /* Error - Event 0x345 */
#define RA_ELC_I3C0_STEV                             (0x346)  /* Synchronous timing - Event 0x346 */
#define RA_ELC_I3C0_MREFOVF                          (0x347)  /* MREF counter overflow - Event 0x347 */
#define RA_ELC_I3C0_MREFCPT                          (0x348)  /* MREF capture - Event 0x348 */
#define RA_ELC_I3C0_AMEV                             (0x349)  /* Additional master-initiated bus event - Event 0x349 */
#define RA_ELC_I3C0_WU                               (0x34A)  /* Wake-up Condition Detection interrupt - Event 0x34A */
#define RA_ELC_ADC_LIMCLPI                           (0x34B)  /* Limiter clip interrupt with the limit table 0 to 7 - Event 0x34B */
#define RA_ELC_ADC_FIFOOVF                           (0x34C)  /* FIFO data overflow - Event 0x34C */
#define RA_ELC_ADC_ADI0                              (0x34D)  /* End of A/D scanning operation(Gr.0) - Event 0x34D */
#define RA_ELC_ADC_ADI1                              (0x34E)  /* End of A/D scanning operation(Gr.1) - Event 0x34E */
#define RA_ELC_ADC_ADI2                              (0x34F)  /* End of A/D scanning operation(Gr.2) - Event 0x34F */
#define RA_ELC_ADC_ADI3                              (0x350)  /* End of A/D scanning operation(Gr.3) - Event 0x350 */
#define RA_ELC_ADC_ADI4                              (0x351)  /* End of A/D scanning operation(Gr.4) - Event 0x351 */
#define RA_ELC_ADC_ADI5                              (0x352)  /* End of A/D scanning operation(Gr.5) - Event 0x352 */
#define RA_ELC_ADC_ADI6                              (0x353)  /* End of A/D scanning operation(Gr.6) - Event 0x353 */
#define RA_ELC_ADC_ADI7                              (0x354)  /* End of A/D scanning operation(Gr.7) - Event 0x354 */
#define RA_ELC_ADC_ADI8                              (0x355)  /* End of A/D scanning operation(Gr.8) - Event 0x355 */
#define RA_ELC_ADC_FIFOREQ0                          (0x356)  /* FIFO data read request interrupt(Gr.0) - Event 0x356 */
#define RA_ELC_ADC_FIFOREQ1                          (0x357)  /* FIFO data read request interrupt(Gr.1) - Event 0x357 */
#define RA_ELC_ADC_FIFOREQ2                          (0x358)  /* FIFO data read request interrupt(Gr.2) - Event 0x358 */
#define RA_ELC_ADC_FIFOREQ3                          (0x359)  /* FIFO data read request interrupt(Gr.3) - Event 0x359 */
#define RA_ELC_ADC_FIFOREQ4                          (0x35A)  /* FIFO data read request interrupt(Gr.4) - Event 0x35A */
#define RA_ELC_ADC_FIFOREQ5                          (0x35B)  /* FIFO data read request interrupt(Gr.5) - Event 0x35B */
#define RA_ELC_ADC_FIFOREQ6                          (0x35C)  /* FIFO data read request interrupt(Gr.6) - Event 0x35C */
#define RA_ELC_ADC_FIFOREQ7                          (0x35D)  /* FIFO data read request interrupt(Gr.7) - Event 0x35D */
#define RA_ELC_ADC_FIFOREQ8                          (0x35E)  /* FIFO data read request interrupt(Gr.8) - Event 0x35E */
#define RA_ELC_ADC_CMPI0                             (0x35F)  /* Compare match interrupt with compare table 0 - Event 0x35F */
#define RA_ELC_ADC_CMPI1                             (0x360)  /* Compare match interrupt with compare table 1 - Event 0x360 */
#define RA_ELC_ADC_CCMPM0                            (0x361)  /* Composite compare match 0 - Event 0x361 */
#define RA_ELC_ADC_CCMPUM0                           (0x362)  /* Composite condition compare mismatch 0 - Event 0x362 */
#define RA_ELC_ADC_ERR0                              (0x363)  /* A/D converter unit 0 Error - Event 0x363 */
#define RA_ELC_ADC_RESOVF0                           (0x364)  /* A/D conversion overflow on A/D converter unit 0 - Event 0x364 */
#define RA_ELC_ADC_CALREQ0                           (0x365)  /* Calibration request unit 0 - Event 0x365 */
#define RA_ELC_ADC_CALEND0                           (0x366)  /* End of calibration of A/D converter unit 0 - Event 0x366 */
#define RA_ELC_ADC_CMPI2                             (0x367)  /* Compare match interrupt with compare table 2 - Event 0x367 */
#define RA_ELC_ADC_CMPI3                             (0x368)  /* Compare match interrupt with compare table 3 - Event 0x368 */
#define RA_ELC_ADC_CCMPM1                            (0x369)  /* Composite compare match 1 - Event 0x369 */
#define RA_ELC_ADC_CCMPUM1                           (0x36A)  /* Composite condition compare mismatch 1 - Event 0x36A */
#define RA_ELC_ADC_ERR1                              (0x36B)  /* A/D converter unit 1 Error - Event 0x36B */
#define RA_ELC_ADC_RESOVF1                           (0x36C)  /* A/D conversion overflow on A/D converter unit 1 - Event 0x36C */
#define RA_ELC_ADC_CALREQ1                           (0x36D)  /* Calibration request unit 1 - Event 0x36D */
#define RA_ELC_ADC_CALEND1                           (0x36E)  /* End of calibration of A/D converter unit 1 - Event 0x36E */
#define RA_ELC_DOC_INT                               (0x36F)  /* Data operation circuit interrupt - Event 0x36F */
#define RA_ELC_RSIP_TADI                             (0x371)  /* RSIP Tamper Detection - Event 0x371 */
#define RA_ELC_GLCDC_LINE_DETECT                     (0x382)  /* Specified line - Event 0x382 */
#define RA_ELC_GLCDC_UNDERFLOW_1                     (0x383)  /* Graphic 1 underflow - Event 0x383 */
#define RA_ELC_GLCDC_UNDERFLOW_2                     (0x384)  /* Graphic 2 underflow - Event 0x384 */
#define RA_ELC_DRW_INT                               (0x385)  /* DRW interrupt - Event 0x385 */
#define RA_ELC_MIPIDSI_SEQ0                          (0x388)  /* Sequence operation channel 0 interrupt - Event 0x388 */
#define RA_ELC_MIPIDSI_SEQ1                          (0x389)  /* Sequence operation channel 1 interrupt - Event 0x389 */
#define RA_ELC_MIPIDSI_VIN1                          (0x38A)  /* Video-Input operation channel1 interrupt - Event 0x38A */
#define RA_ELC_MIPIDSI_RCV                           (0x38B)  /* DSI packet receive interrupt - Event 0x38B */
#define RA_ELC_MIPIDSI_FERR                          (0x38C)  /* DSI fatal error interrupt - Event 0x38C */
#define RA_ELC_MIPIDSI_PPI                           (0x38D)  /* DSI D-PHY PPI interrupt - Event 0x38D */
#define RA_ELC_MIPICSI_RX                            (0x38F)  /* Receive interrupt - Event 0x38F */
#define RA_ELC_MIPICSI_DL                            (0x390)  /* Data Lane interrupt - Event 0x390 */
#define RA_ELC_MIPICSI_VC                            (0x391)  /* Virtual Channel interrupt - Event 0x391 */
#define RA_ELC_MIPICSI_PM                            (0x392)  /* Power Management interrupt - Event 0x392 */
#define RA_ELC_MIPICSI_GST                           (0x393)  /* Generic Short Packet interrupt - Event 0x393 */
#define RA_ELC_VIN_IRQ                               (0x395)  /* Interrupt Request - Event 0x395 */
#define RA_ELC_VIN_ERR                               (0x396)  /* Interrupt Request for SYNC Error - Event 0x396 */

/* Maximum valid ELC event number for RA8P1 */

#define RA_ELC_EVENT_MAX                             (0x396)

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Inline functions
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifndef __ASSEMBLY__
#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

#undef EXTERN
#ifdef __cplusplus
}
#endif
#endif

#endif /* __ARCH_ARM_INCLUDE_RA_RA8P1_IRQ_H */

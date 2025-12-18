/****************************************************************************
 * arch/arm/include/rzv/rzv2h_irq.h
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

#ifndef __ARCH_ARM_INCLUDE_RZV_RZV2H_IRQ_H
#define __ARCH_ARM_INCLUDE_RZV_RZV2H_IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <nuttx/config.h>
#include <nuttx/irq.h>
#include <arch/rzv/chip.h>

/****************************************************************************
 * Pre-processor Prototypes
 ****************************************************************************/

/* Event number definitions based on RZV2H HWM Event Table 13.4 */
#define RZV_ELC_IRQ0                                  (0x0)  /* External pin interrupt 0 - Event 0x0 */
#define RZV_ELC_IRQ1                                  (0x1)  /* External pin interrupt 1 - Event 0x1 */
#define RZV_ELC_IRQ2                                  (0x2)  /* External pin interrupt 2 - Event 0x2 */
#define RZV_ELC_IRQ3                                  (0x3)  /* External pin interrupt 3 - Event 0x3 */
#define RZV_ELC_IRQ4                                  (0x4)  /* External pin interrupt 4 - Event 0x4 */
#define RZV_ELC_IRQ5                                  (0x5)  /* External pin interrupt 5 - Event 0x5 */
#define RZV_ELC_IRQ6                                  (0x6)  /* External pin interrupt 6 - Event 0x6 */
#define RZV_ELC_IRQ7                                  (0x7)  /* External pin interrupt 7 - Event 0x7 */
#define RZV_ELC_IRQ8                                  (0x8)  /* External pin interrupt 8 - Event 0x8 */
#define RZV_ELC_IRQ9                                  (0x9)  /* External pin interrupt 9 - Event 0x9 */
#define RZV_ELC_IRQ10                                 (0xA)  /* External pin interrupt 10 - Event 0xA */
#define RZV_ELC_IRQ11                                 (0xB)  /* External pin interrupt 11 - Event 0xB */
#define RZV_ELC_IRQ12                                 (0xC)  /* External pin interrupt 12 - Event 0xC */
#define RZV_ELC_IRQ13                                 (0xD)  /* External pin interrupt 13 - Event 0xD */
#define RZV_ELC_IRQ14                                 (0xE)  /* External pin interrupt 14 - Event 0xE */
#define RZV_ELC_IRQ15                                 (0xF)  /* External pin interrupt 15 - Event 0xF */
#define RZV_ELC_IOPORT_GROUP0                         (0x10)  /* Input edge detection of input port group 1 - Event 0x10 */
#define RZV_ELC_IOPORT_GROUP1                         (0x11)  /* Input edge detection of input port group 2 - Event 0x11 */
#define RZV_ELC_IOPORT_SINGLE0                        (0x12)  /* Input edge detection of single input port group 0 - Event 0x12 */
#define RZV_ELC_IOPORT_SINGLE1                        (0x13)  /* Input edge detection of single input port group 1 - Event 0x13 */
#define RZV_ELC_IOPORT_SINGLE2                        (0x14)  /* Input edge detection of single input port group 2 - Event 0x14 */
#define RZV_ELC_IOPORT_SINGLE3                        (0x15)  /* Input edge detection of single input port group 3 - Event 0x15 */
#define RZV_ELC_SW_EVENT_0                            (0x16)  /* Software interrupt 0 - Event 0x16 */
#define RZV_ELC_SW_EVENT_1                            (0x17)  /* Software interrupt 1 - Event 0x17 */
#define RZV_ELC_SW_EVENT_2                            (0x18)  /* Software interrupt 2 - Event 0x18 */
#define RZV_ELC_SW_EVENT_3                            (0x19)  /* Software interrupt 3 - Event 0x19 */
#define RZV_ELC_SW_EVENT_4                            (0x1A)  /* Software interrupt 4 - Event 0x1A */
#define RZV_ELC_SW_EVENT_5                            (0x1B)  /* Software interrupt 5 - Event 0x1B */
#define RZV_ELC_SW_EVENT_6                            (0x1C)  /* Software interrupt 6 - Event 0x1C */
#define RZV_ELC_CMTW_CH0_CMT2_ELCCMP                  (0x1D)  /* CMTW0 compare match event - Event 0x1D */
#define RZV_ELC_CMTW_CH1_CMT2_ELCCMP                  (0x1E)  /* CMTW1 compare match event - Event 0x1E */
#define RZV_ELC_CMTW_CH2_CMT2_ELCCMP                  (0x1F)  /* CMTW2 compare match event - Event 0x1F */
#define RZV_ELC_CMTW_CH3_CMT2_ELCCMP                  (0x20)  /* CMTW3 compare match event - Event 0x20 */
#define RZV_ELC_CMTW_CH4_CMT2_ELCCMP                  (0x21)  /* CMTW4 compare match event - Event 0x21 */
#define RZV_ELC_CMTW_CH5_CMT2_ELCCMP                  (0x22)  /* CMTW5 compare match event - Event 0x22 */
#define RZV_ELC_CMTW_CH6_CMT2_ELCCMP                  (0x23)  /* CMTW6 compare match event - Event 0x23 */
#define RZV_ELC_CMTW_CH7_CMT2_ELCCMP                  (0x24)  /* CMTW7 compare match event - Event 0x24 */
#define RZV_ELC_CMTW_CH0_CMT2_ELCOCP0                 (0x25)  /* CMTW0 Output compare 0 event - Event 0x25 */
#define RZV_ELC_CMTW_CH1_CMT2_ELCOCP0                 (0x26)  /* CMTW1 Output compare 0 event - Event 0x26 */
#define RZV_ELC_CMTW_CH2_CMT2_ELCOCP0                 (0x27)  /* CMTW2 Output compare 0 event - Event 0x27 */
#define RZV_ELC_CMTW_CH3_CMT2_ELCOCP0                 (0x28)  /* CMTW3 Output compare 0 event - Event 0x28 */
#define RZV_ELC_CMTW_CH4_CMT2_ELCOCP0                 (0x29)  /* CMTW4 Output compare 0 event - Event 0x29 */
#define RZV_ELC_CMTW_CH5_CMT2_ELCOCP0                 (0x2A)  /* CMTW5 Output compare 0 event - Event 0x2A */
#define RZV_ELC_CMTW_CH6_CMT2_ELCOCP0                 (0x2B)  /* CMTW6 Output compare 0 event - Event 0x2B */
#define RZV_ELC_CMTW_CH7_CMT2_ELCOCP0                 (0x2C)  /* CMTW7 Output compare 0 event - Event 0x2C */
#define RZV_ELC_CMTW_CH0_CMT2_ELCOCP1                 (0x2D)  /* CMTW0 Output compare 1 event - Event 0x2D */
#define RZV_ELC_CMTW_CH1_CMT2_ELCOCP1                 (0x2E)  /* CMTW1 Output compare 1 event - Event 0x2E */
#define RZV_ELC_CMTW_CH2_CMT2_ELCOCP1                 (0x2F)  /* CMTW2 Output compare 1 event - Event 0x2F */
#define RZV_ELC_CMTW_CH3_CMT2_ELCOCP1                 (0x30)  /* CMTW3 Output compare 1 event - Event 0x30 */
#define RZV_ELC_CMTW_CH4_CMT2_ELCOCP1                 (0x31)  /* CMTW4 Output compare 1 event - Event 0x31 */
#define RZV_ELC_CMTW_CH5_CMT2_ELCOCP1                 (0x32)  /* CMTW5 Output compare 1 event - Event 0x32 */
#define RZV_ELC_CMTW_CH6_CMT2_ELCOCP1                 (0x33)  /* CMTW6 Output compare 1 event - Event 0x33 */
#define RZV_ELC_CMTW_CH7_CMT2_ELCOCP1                 (0x34)  /* CMTW7 Output compare 1 event - Event 0x34 */
#define RZV_ELC_GTM0_GTMTINT                          (0x35)  /* GTM0 interrupt output signal - Event 0x35 */
#define RZV_ELC_GTM1_GTMTINT                          (0x36)  /* GTM1 interrupt output signal - Event 0x36 */
#define RZV_ELC_GTM2_GTMTINT                          (0x37)  /* GTM2 interrupt output signal - Event 0x37 */
#define RZV_ELC_GTM3_GTMTINT                          (0x38)  /* GTM3 interrupt output signal - Event 0x38 */
#define RZV_ELC_GTM4_GTMTINT                          (0x39)  /* GTM4 interrupt output signal - Event 0x39 */
#define RZV_ELC_GTM5_GTMTINT                          (0x3A)  /* GTM5 interrupt output signal - Event 0x3A */
#define RZV_ELC_GTM6_GTMTINT                          (0x3B)  /* GTM6 interrupt output signal - Event 0x3B */
#define RZV_ELC_GTM7_GTMTINT                          (0x3C)  /* GTM7 interrupt output signal - Event 0x3C */
#define RZV_ELC_DMAC1_DMAEND_0                        (0x3D)  /* DMAC1 transfer completion 0 - Event 0x3D */
#define RZV_ELC_DMAC1_DMAEND_1                        (0x3E)  /* DMAC1 transfer completion 1 - Event 0x3E */
#define RZV_ELC_DMAC1_DMAEND_2                        (0x3F)  /* DMAC1 transfer completion 2 - Event 0x3F */
#define RZV_ELC_DMAC1_DMAEND_3                        (0x40)  /* DMAC1 transfer completion 3 - Event 0x40 */
#define RZV_ELC_DMAC1_DMAEND_4                        (0x41)  /* DMAC1 transfer completion 4 - Event 0x41 */
#define RZV_ELC_DMAC1_DMAEND_5                        (0x42)  /* DMAC1 transfer completion 5 - Event 0x42 */
#define RZV_ELC_DMAC1_DMAEND_6                        (0x43)  /* DMAC1 transfer completion 6 - Event 0x43 */
#define RZV_ELC_DMAC1_DMAEND_7                        (0x44)  /* DMAC1 transfer completion 7 - Event 0x44 */
#define RZV_ELC_DMAC1_DMAEND_8                        (0x45)  /* DMAC1 transfer completion 8 - Event 0x45 */
#define RZV_ELC_DMAC1_DMAEND_9                        (0x46)  /* DMAC1 transfer completion 9 - Event 0x46 */
#define RZV_ELC_DMAC1_DMAEND_10                       (0x47)  /* DMAC1 transfer completion 10 - Event 0x47 */
#define RZV_ELC_DMAC1_DMAEND_11                       (0x48)  /* DMAC1 transfer completion 11 - Event 0x48 */
#define RZV_ELC_DMAC1_DMAEND_12                       (0x49)  /* DMAC1 transfer completion 12 - Event 0x49 */
#define RZV_ELC_DMAC1_DMAEND_13                       (0x4A)  /* DMAC1 transfer completion 13 - Event 0x4A */
#define RZV_ELC_DMAC1_DMAEND_14                       (0x4B)  /* DMAC1 transfer completion 14 - Event 0x4B */
#define RZV_ELC_DMAC1_DMAEND_15                       (0x4C)  /* DMAC1 transfer completion 15 - Event 0x4C */
#define RZV_ELC_DMAC2_DMAEND_0                        (0x4D)  /* DMAC2 transfer completion 0 - Event 0x4D */
#define RZV_ELC_DMAC2_DMAEND_1                        (0x4E)  /* DMAC2 transfer completion 1 - Event 0x4E */
#define RZV_ELC_DMAC2_DMAEND_2                        (0x4F)  /* DMAC2 transfer completion 2 - Event 0x4F */
#define RZV_ELC_DMAC2_DMAEND_3                        (0x50)  /* DMAC2 transfer completion 3 - Event 0x50 */
#define RZV_ELC_DMAC2_DMAEND_4                        (0x51)  /* DMAC2 transfer completion 4 - Event 0x51 */
#define RZV_ELC_DMAC2_DMAEND_5                        (0x52)  /* DMAC2 transfer completion 5 - Event 0x52 */
#define RZV_ELC_DMAC2_DMAEND_6                        (0x53)  /* DMAC2 transfer completion 6 - Event 0x53 */
#define RZV_ELC_DMAC2_DMAEND_7                        (0x54)  /* DMAC2 transfer completion 7 - Event 0x54 */
#define RZV_ELC_DMAC2_DMAEND_8                        (0x55)  /* DMAC2 transfer completion 8 - Event 0x55 */
#define RZV_ELC_DMAC2_DMAEND_9                        (0x56)  /* DMAC2 transfer completion 9 - Event 0x56 */
#define RZV_ELC_DMAC2_DMAEND_10                       (0x57)  /* DMAC2 transfer completion 10 - Event 0x57 */
#define RZV_ELC_DMAC2_DMAEND_11                       (0x58)  /* DMAC2 transfer completion 11 - Event 0x58 */
#define RZV_ELC_DMAC2_DMAEND_12                       (0x59)  /* DMAC2 transfer completion 12 - Event 0x59 */
#define RZV_ELC_DMAC2_DMAEND_13                       (0x5A)  /* DMAC2 transfer completion 13 - Event 0x5A */
#define RZV_ELC_DMAC2_DMAEND_14                       (0x5B)  /* DMAC2 transfer completion 14 - Event 0x5B */
#define RZV_ELC_DMAC2_DMAEND_15                       (0x5C)  /* DMAC2 transfer completion 15 - Event 0x5C */
#define RZV_ELC_DMAC3_DMAEND_0                        (0x5D)  /* DMAC3 transfer completion 0 - Event 0x5D */
#define RZV_ELC_DMAC3_DMAEND_1                        (0x5E)  /* DMAC3 transfer completion 1 - Event 0x5E */
#define RZV_ELC_DMAC3_DMAEND_2                        (0x5F)  /* DMAC3 transfer completion 2 - Event 0x5F */
#define RZV_ELC_DMAC3_DMAEND_3                        (0x60)  /* DMAC3 transfer completion 3 - Event 0x60 */
#define RZV_ELC_DMAC3_DMAEND_4                        (0x61)  /* DMAC3 transfer completion 4 - Event 0x61 */
#define RZV_ELC_DMAC3_DMAEND_5                        (0x62)  /* DMAC3 transfer completion 5 - Event 0x62 */
#define RZV_ELC_DMAC3_DMAEND_6                        (0x63)  /* DMAC3 transfer completion 6 - Event 0x63 */
#define RZV_ELC_DMAC3_DMAEND_7                        (0x64)  /* DMAC3 transfer completion 7 - Event 0x64 */
#define RZV_ELC_DMAC3_DMAEND_8                        (0x65)  /* DMAC3 transfer completion 8 - Event 0x65 */
#define RZV_ELC_DMAC3_DMAEND_9                        (0x66)  /* DMAC3 transfer completion 9 - Event 0x66 */
#define RZV_ELC_DMAC3_DMAEND_10                       (0x67)  /* DMAC3 transfer completion 10 - Event 0x67 */
#define RZV_ELC_DMAC3_DMAEND_11                       (0x68)  /* DMAC3 transfer completion 11 - Event 0x68 */
#define RZV_ELC_DMAC3_DMAEND_12                       (0x69)  /* DMAC3 transfer completion 12 - Event 0x69 */
#define RZV_ELC_DMAC3_DMAEND_13                       (0x6A)  /* DMAC3 transfer completion 13 - Event 0x6A */
#define RZV_ELC_DMAC3_DMAEND_14                       (0x6B)  /* DMAC3 transfer completion 14 - Event 0x6B */
#define RZV_ELC_DMAC3_DMAEND_15                       (0x6C)  /* DMAC3 transfer completion 15 - Event 0x6C */
#define RZV_ELC_DMAC4_DMAEND_0                        (0x6D)  /* DMAC4 transfer completion 0 - Event 0x6D */
#define RZV_ELC_DMAC4_DMAEND_1                        (0x6E)  /* DMAC4 transfer completion 1 - Event 0x6E */
#define RZV_ELC_DMAC4_DMAEND_2                        (0x6F)  /* DMAC4 transfer completion 2 - Event 0x6F */
#define RZV_ELC_DMAC4_DMAEND_3                        (0x70)  /* DMAC4 transfer completion 3 - Event 0x70 */
#define RZV_ELC_DMAC4_DMAEND_4                        (0x71)  /* DMAC4 transfer completion 4 - Event 0x71 */
#define RZV_ELC_DMAC4_DMAEND_5                        (0x72)  /* DMAC4 transfer completion 5 - Event 0x72 */
#define RZV_ELC_DMAC4_DMAEND_6                        (0x73)  /* DMAC4 transfer completion 6 - Event 0x73 */
#define RZV_ELC_DMAC4_DMAEND_7                        (0x74)  /* DMAC4 transfer completion 7 - Event 0x74 */
#define RZV_ELC_DMAC4_DMAEND_8                        (0x75)  /* DMAC4 transfer completion 8 - Event 0x75 */
#define RZV_ELC_DMAC4_DMAEND_9                        (0x76)  /* DMAC4 transfer completion 9 - Event 0x76 */
#define RZV_ELC_DMAC4_DMAEND_10                       (0x77)  /* DMAC4 transfer completion 10 - Event 0x77 */
#define RZV_ELC_DMAC4_DMAEND_11                       (0x78)  /* DMAC4 transfer completion 11 - Event 0x78 */
#define RZV_ELC_DMAC4_DMAEND_12                       (0x79)  /* DMAC4 transfer completion 12 - Event 0x79 */
#define RZV_ELC_DMAC4_DMAEND_13                       (0x7A)  /* DMAC4 transfer completion 13 - Event 0x7A */
#define RZV_ELC_DMAC4_DMAEND_14                       (0x7B)  /* DMAC4 transfer completion 14 - Event 0x7B */
#define RZV_ELC_DMAC4_DMAEND_15                       (0x7C)  /* DMAC4 transfer completion 15 - Event 0x7C */
#define RZV_ELC_DMAC0_DMAEND_0                        (0x7D)  /* DMAC0 transfer completion 0 - Event 0x7D */
#define RZV_ELC_DMAC0_DMAEND_1                        (0x7E)  /* DMAC0 transfer completion 1 - Event 0x7E */
#define RZV_ELC_DMAC0_DMAEND_2                        (0x7F)  /* DMAC0 transfer completion 2 - Event 0x7F */
#define RZV_ELC_DMAC0_DMAEND_3                        (0x80)  /* DMAC0 transfer completion 3 - Event 0x80 */
#define RZV_ELC_DMAC0_DMAEND_4                        (0x81)  /* DMAC0 transfer completion 4 - Event 0x81 */
#define RZV_ELC_DMAC0_DMAEND_5                        (0x82)  /* DMAC0 transfer completion 5 - Event 0x82 */
#define RZV_ELC_DMAC0_DMAEND_6                        (0x83)  /* DMAC0 transfer completion 6 - Event 0x83 */
#define RZV_ELC_DMAC0_DMAEND_7                        (0x84)  /* DMAC0 transfer completion 7 - Event 0x84 */
#define RZV_ELC_DMAC0_DMAEND_8                        (0x85)  /* DMAC0 transfer completion 8 - Event 0x85 */
#define RZV_ELC_DMAC0_DMAEND_9                        (0x86)  /* DMAC0 transfer completion 9 - Event 0x86 */
#define RZV_ELC_DMAC0_DMAEND_10                       (0x87)  /* DMAC0 transfer completion 10 - Event 0x87 */
#define RZV_ELC_DMAC0_DMAEND_11                       (0x88)  /* DMAC0 transfer completion 11 - Event 0x88 */
#define RZV_ELC_DMAC0_DMAEND_12                       (0x89)  /* DMAC0 transfer completion 12 - Event 0x89 */
#define RZV_ELC_DMAC0_DMAEND_13                       (0x8A)  /* DMAC0 transfer completion 13 - Event 0x8A */
#define RZV_ELC_DMAC0_DMAEND_14                       (0x8B)  /* DMAC0 transfer completion 14 - Event 0x8B */
#define RZV_ELC_DMAC0_DMAEND_15                       (0x8C)  /* DMAC0 transfer completion 15 - Event 0x8C */
#define RZV_ELC_IWDT_ELCWUN_CA55                      (0x8D)  /* WDT CA55 underflow or refresh error event - Event 0x8D */
#define RZV_ELC_IWDT_ELCWUN_CM33                      (0x8E)  /* WDT CM33 underflow or refresh error event - Event 0x8E */
#define RZV_ELC_IWDT_ELCWUN_CR8_0                     (0x8F)  /* WDT CR8_0 underflow or refresh error event - Event 0x8F */
#define RZV_ELC_IWDT_ELCWUN_CR8_1                     (0x90)  /* WDT CR8_1 underflow or refresh error event - Event 0x90 */
#define RZV_ELC_SP_ELCRDRF_0                          (0x91)  /* RSPI0 Receive buffer full event - Event 0x91 */
#define RZV_ELC_SP_ELCTDRE_0                          (0x92)  /* RSPI0 Transmit buffer empty event - Event 0x92 */
#define RZV_ELC_SP_ELCERR_0                           (0x93)  /* RSPI0 Error event - Event 0x93 */
#define RZV_ELC_SP_ELCID_0                            (0x94)  /* RSPI0 Idle event - Event 0x94 */
#define RZV_ELC_SP_ELCCEND_0                          (0x95)  /* RSPI0 Communications end event - Event 0x95 */
#define RZV_ELC_SP_ELCRDRF_1                          (0x96)  /* RSPI1 Receive buffer full event - Event 0x96 */
#define RZV_ELC_SP_ELCTDRE_1                          (0x97)  /* RSPI1 Transmit buffer empty event - Event 0x97 */
#define RZV_ELC_SP_ELCERR_1                           (0x98)  /* RSPI1 Error event - Event 0x98 */
#define RZV_ELC_SP_ELCID_1                            (0x99)  /* RSPI1 Idle event - Event 0x99 */
#define RZV_ELC_SP_ELCCEND_1                          (0x9A)  /* RSPI1 Communications end event - Event 0x9A */
#define RZV_ELC_SP_ELCRDRF_2                          (0x9B)  /* RSPI2 Receive buffer full event - Event 0x9B */
#define RZV_ELC_SP_ELCTDRE_2                          (0x9C)  /* RSPI2 Transmit buffer empty event - Event 0x9C */
#define RZV_ELC_SP_ELCERR_2                           (0x9D)  /* RSPI2 Error event - Event 0x9D */
#define RZV_ELC_SP_ELCID_2                            (0x9E)  /* RSPI2 Idle event - Event 0x9E */
#define RZV_ELC_SP_ELCCEND_2                          (0x9F)  /* RSPI2 Communications end event - Event 0x9F */
#define RZV_ELC_SC_ELCER_0                            (0xA0)  /* RSCI0 Receive error event - Event 0xA0 */
#define RZV_ELC_SC_ELCRDRF_0                          (0xA1)  /* RSCI0 Receive data full event - Event 0xA1 */
#define RZV_ELC_SC_ELCDCMF_0                          (0xA2)  /* RSCI0 Receive data compare match event - Event 0xA2 */
#define RZV_ELC_SC_ELCTDRE_0                          (0xA3)  /* RSCI0 Transmit data empty event - Event 0xA3 */
#define RZV_ELC_SC_ELCTEND_0                          (0xA4)  /* RSCI0 Transmit end event - Event 0xA4 */
#define RZV_ELC_SC_ELCDCUF_0                          (0xA5)  /* RSCI0 Receive data compare unmatch event - Event 0xA5 */
#define RZV_ELC_SC_ELCER_1                            (0xA6)  /* RSCI1 Receive error event - Event 0xA6 */
#define RZV_ELC_SC_ELCRDRF_1                          (0xA7)  /* RSCI1 Receive data full event - Event 0xA7 */
#define RZV_ELC_SC_ELCDCMF_1                          (0xA8)  /* RSCI1 Receive data compare match event - Event 0xA8 */
#define RZV_ELC_SC_ELCTDRE_1                          (0xA9)  /* RSCI1 Transmit data empty event - Event 0xA9 */
#define RZV_ELC_SC_ELCTEND_1                          (0xAA)  /* RSCI1 Transmit end event - Event 0xAA */
#define RZV_ELC_SC_ELCDCUF_1                          (0xAB)  /* RSCI1 Receive data compare unmatch event - Event 0xAB */
#define RZV_ELC_SC_ELCER_2                            (0xAC)  /* RSCI2 Receive error event - Event 0xAC */
#define RZV_ELC_SC_ELCRDRF_2                          (0xAD)  /* RSCI2 Receive data full event - Event 0xAD */
#define RZV_ELC_SC_ELCDCMF_2                          (0xAE)  /* RSCI2 Receive data compare match event - Event 0xAE */
#define RZV_ELC_SC_ELCTDRE_2                          (0xAF)  /* RSCI2 Transmit data empty event - Event 0xAF */
#define RZV_ELC_SC_ELCTEND_2                          (0xB0)  /* RSCI2 Transmit end event - Event 0xB0 */
#define RZV_ELC_SC_ELCDCUF_2                          (0xB1)  /* RSCI2 Receive data compare unmatch event - Event 0xB1 */
#define RZV_ELC_SC_ELCER_3                            (0xB2)  /* RSCI3 Receive error event - Event 0xB2 */
#define RZV_ELC_SC_ELCRDRF_3                          (0xB3)  /* RSCI3 Receive data full event - Event 0xB3 */
#define RZV_ELC_SC_ELCDCMF_3                          (0xB4)  /* RSCI3 Receive data compare match event - Event 0xB4 */
#define RZV_ELC_SC_ELCTDRE_3                          (0xB5)  /* RSCI3 Transmit data empty event - Event 0xB5 */
#define RZV_ELC_SC_ELCTEND_3                          (0xB6)  /* RSCI3 Transmit end event - Event 0xB6 */
#define RZV_ELC_SC_ELCDCUF_3                          (0xB7)  /* RSCI3 Receive data compare unmatch event - Event 0xB7 */
#define RZV_ELC_SC_ELCER_4                            (0xB8)  /* RSCI4 Receive error event - Event 0xB8 */
#define RZV_ELC_SC_ELCRDRF_4                          (0xB9)  /* RSCI4 Receive data full event - Event 0xB9 */
#define RZV_ELC_SC_ELCDCMF_4                          (0xBA)  /* RSCI4 Receive data compare match event - Event 0xBA */
#define RZV_ELC_SC_ELCTDRE_4                          (0xBB)  /* RSCI4 Transmit data empty event - Event 0xBB */
#define RZV_ELC_SC_ELCTEND_4                          (0xBC)  /* RSCI4 Transmit end event - Event 0xBC */
#define RZV_ELC_SC_ELCDCUF_4                          (0xBD)  /* RSCI4 Receive data compare unmatch event - Event 0xBD */
#define RZV_ELC_SC_ELCER_5                            (0xBE)  /* RSCI5 Receive error event - Event 0xBE */
#define RZV_ELC_SC_ELCRDRF_5                          (0xBF)  /* RSCI5 Receive data full event - Event 0xBF */
#define RZV_ELC_SC_ELCDCMF_5                          (0xC0)  /* RSCI5 Receive data compare match event - Event 0xC0 */
#define RZV_ELC_SC_ELCTDRE_5                          (0xC1)  /* RSCI5 Transmit data empty event - Event 0xC1 */
#define RZV_ELC_SC_ELCTEND_5                          (0xC2)  /* RSCI5 Transmit end event - Event 0xC2 */
#define RZV_ELC_SC_ELCDCUF_5                          (0xC3)  /* RSCI5 Receive data compare unmatch event - Event 0xC3 */
#define RZV_ELC_SC_ELCER_6                            (0xC4)  /* RSCI6 Receive error event - Event 0xC4 */
#define RZV_ELC_SC_ELCRDRF_6                          (0xC5)  /* RSCI6 Receive data full event - Event 0xC5 */
#define RZV_ELC_SC_ELCDCMF_6                          (0xC6)  /* RSCI6 Receive data compare match event - Event 0xC6 */
#define RZV_ELC_SC_ELCTDRE_6                          (0xC7)  /* RSCI6 Transmit data empty event - Event 0xC7 */
#define RZV_ELC_SC_ELCTEND_6                          (0xC8)  /* RSCI6 Transmit end event - Event 0xC8 */
#define RZV_ELC_SC_ELCDCUF_6                          (0xC9)  /* RSCI6 Receive data compare unmatch event - Event 0xC9 */
#define RZV_ELC_SC_ELCER_7                            (0xCA)  /* RSCI7 Receive error event - Event 0xCA */
#define RZV_ELC_SC_ELCRDRF_7                          (0xCB)  /* RSCI7 Receive data full event - Event 0xCB */
#define RZV_ELC_SC_ELCDCMF_7                          (0xCC)  /* RSCI7 Receive data compare match event - Event 0xCC */
#define RZV_ELC_SC_ELCTDRE_7                          (0xCD)  /* RSCI7 Transmit data empty event - Event 0xCD */
#define RZV_ELC_SC_ELCTEND_7                          (0xCE)  /* RSCI7 Transmit end event - Event 0xCE */
#define RZV_ELC_SC_ELCDCUF_7                          (0xCF)  /* RSCI7 Receive data compare unmatch event - Event 0xCF */
#define RZV_ELC_SC_ELCER_8                            (0xD0)  /* RSCI8 Receive error event - Event 0xD0 */
#define RZV_ELC_SC_ELCRDRF_8                          (0xD1)  /* RSCI8 Receive data full event - Event 0xD1 */
#define RZV_ELC_SC_ELCDCMF_8                          (0xD2)  /* RSCI8 Receive data compare match event - Event 0xD2 */
#define RZV_ELC_SC_ELCTDRE_8                          (0xD3)  /* RSCI8 Transmit data empty event - Event 0xD3 */
#define RZV_ELC_SC_ELCTEND_8                          (0xD4)  /* RSCI8 Transmit end event - Event 0xD4 */
#define RZV_ELC_SC_ELCDCUF_8                          (0xD5)  /* RSCI8 Receive data compare unmatch event - Event 0xD5 */
#define RZV_ELC_SC_ELCER_9                            (0xD6)  /* RSCI9 Receive error event - Event 0xD6 */
#define RZV_ELC_SC_ELCRDRF_9                          (0xD7)  /* RSCI9 Receive data full event - Event 0xD7 */
#define RZV_ELC_SC_ELCDCMF_9                          (0xD8)  /* RSCI9 Receive data compare match event - Event 0xD8 */
#define RZV_ELC_SC_ELCTDRE_9                          (0xD9)  /* RSCI9 Transmit data empty event - Event 0xD9 */
#define RZV_ELC_SC_ELCTEND_9                          (0xDA)  /* RSCI9 Transmit end event - Event 0xDA */
#define RZV_ELC_SC_ELCDCUF_9                          (0xDB)  /* RSCI9 Receive data compare unmatch event - Event 0xDB */
#define RZV_ELC_RIIC_CH0_IIC_ELCERRP                  (0xDC)  /* RIIC0 ERRP ELC signal - Event 0xDC */
#define RZV_ELC_RIIC_CH0_IIC_ELCTDREP                 (0xDD)  /* RIIC0 TDREP ELC signal - Event 0xDD */
#define RZV_ELC_RIIC_CH0_IIC_ELCRDRFP                 (0xDE)  /* RIIC0 RDRF ELC signal - Event 0xDE */
#define RZV_ELC_RIIC_CH0_IIC_ELCTENDP                 (0xDF)  /* RIIC0 TEND ELC signal - Event 0xDF */
#define RZV_ELC_RIIC_CH1_IIC_ELCERRP                  (0xE0)  /* RIIC1 ERRP ELC signal - Event 0xE0 */
#define RZV_ELC_RIIC_CH1_IIC_ELCTDREP                 (0xE1)  /* RIIC1 TDREP ELC signal - Event 0xE1 */
#define RZV_ELC_RIIC_CH1_IIC_ELCRDRFP                 (0xE2)  /* RIIC1 RDRF ELC signal - Event 0xE2 */
#define RZV_ELC_RIIC_CH1_IIC_ELCTENDP                 (0xE3)  /* RIIC1 TEND ELC signal - Event 0xE3 */
#define RZV_ELC_RIIC_CH2_IIC_ELCERRP                  (0xE4)  /* RIIC2 ERRP ELC signal - Event 0xE4 */
#define RZV_ELC_RIIC_CH2_IIC_ELCTDREP                 (0xE5)  /* RIIC2 TDREP ELC signal - Event 0xE5 */
#define RZV_ELC_RIIC_CH2_IIC_ELCRDRFP                 (0xE6)  /* RIIC2 RDRF ELC signal - Event 0xE6 */
#define RZV_ELC_RIIC_CH2_IIC_ELCTENDP                 (0xE7)  /* RIIC2 TEND ELC signal - Event 0xE7 */
#define RZV_ELC_RIIC_CH3_IIC_ELCERRP                  (0xE8)  /* RIIC3 ERRP ELC signal - Event 0xE8 */
#define RZV_ELC_RIIC_CH3_IIC_ELCTDREP                 (0xE9)  /* RIIC3 TDREP ELC signal - Event 0xE9 */
#define RZV_ELC_RIIC_CH3_IIC_ELCRDRFP                 (0xEA)  /* RIIC3 RDRF ELC signal - Event 0xEA */
#define RZV_ELC_RIIC_CH3_IIC_ELCTENDP                 (0xEB)  /* RIIC3 TEND ELC signal - Event 0xEB */
#define RZV_ELC_RIIC_CH4_IIC_ELCERRP                  (0xEC)  /* RIIC4 ERRP ELC signal - Event 0xEC */
#define RZV_ELC_RIIC_CH4_IIC_ELCTDREP                 (0xED)  /* RIIC4 TDREP ELC signal - Event 0xED */
#define RZV_ELC_RIIC_CH4_IIC_ELCRDRFP                 (0xEE)  /* RIIC4 RDRF ELC signal - Event 0xEE */
#define RZV_ELC_RIIC_CH4_IIC_ELCTENDP                 (0xEF)  /* RIIC4 TEND ELC signal - Event 0xEF */
#define RZV_ELC_RIIC_CH5_IIC_ELCERRP                  (0xF0)  /* RIIC5 ERRP ELC signal - Event 0xF0 */
#define RZV_ELC_RIIC_CH5_IIC_ELCTDREP                 (0xF1)  /* RIIC5 TDREP ELC signal - Event 0xF1 */
#define RZV_ELC_RIIC_CH5_IIC_ELCRDRFP                 (0xF2)  /* RIIC5 RDRF ELC signal - Event 0xF2 */
#define RZV_ELC_RIIC_CH5_IIC_ELCTENDP                 (0xF3)  /* RIIC5 TEND ELC signal - Event 0xF3 */
#define RZV_ELC_RIIC_CH6_IIC_ELCERRP                  (0xF4)  /* RIIC6 ERRP ELC signal - Event 0xF4 */
#define RZV_ELC_RIIC_CH6_IIC_ELCTDREP                 (0xF5)  /* RIIC6 TDREP ELC signal - Event 0xF5 */
#define RZV_ELC_RIIC_CH6_IIC_ELCRDRFP                 (0xF6)  /* RIIC6 RDRF ELC signal - Event 0xF6 */
#define RZV_ELC_RIIC_CH6_IIC_ELCTENDP                 (0xF7)  /* RIIC6 TEND ELC signal - Event 0xF7 */
#define RZV_ELC_RIIC_CH7_IIC_ELCERRP                  (0xF8)  /* RIIC7 ERRP ELC signal - Event 0xF8 */
#define RZV_ELC_RIIC_CH7_IIC_ELCTDREP                 (0xF9)  /* RIIC7 TDREP ELC signal - Event 0xF9 */
#define RZV_ELC_RIIC_CH7_IIC_ELCRDRFP                 (0xFA)  /* RIIC7 RDRF ELC signal - Event 0xFA */
#define RZV_ELC_RIIC_CH7_IIC_ELCTENDP                 (0xFB)  /* RIIC7 TEND ELC signal - Event 0xFB */
#define RZV_ELC_RIIC_CH8_IIC_ELCERRP                  (0xFC)  /* RIIC8 ERRP ELC signal - Event 0xFC */
#define RZV_ELC_RIIC_CH8_IIC_ELCTDREP                 (0xFD)  /* RIIC8 TDREP ELC signal - Event 0xFD */
#define RZV_ELC_RIIC_CH8_IIC_ELCRDRFP                 (0xFE)  /* RIIC8 RDRF ELC signal - Event 0xFE */
#define RZV_ELC_RIIC_CH8_IIC_ELCTENDP                 (0xFF)  /* RIIC8 TEND ELC signal - Event 0xFF */
#define RZV_ELC_ADC0_ADA_ADELCREQ                     (0x100)  /* ADC0 Scan end event - Event 0x100 */
#define RZV_ELC_ADC0_ADA_ELCCONDMTCH                  (0x101)  /* ADC0 Compare match - Event 0x101 */
#define RZV_ELC_ADC0_ADA_ELCCONDUNMTCH                (0x102)  /* ADC0 Compare mis-match - Event 0x102 */
#define RZV_ELC_RTC_ELCALM                            (0x103)  /* RTC Alarm out signal for event link controller - Event 0x103 */
#define RZV_ELC_RTC_ELCCUP                            (0x104)  /* RTC Carry signal for event link controller - Event 0x104 */
#define RZV_ELC_RTC_ELCPRD                            (0x105)  /* RTC Periodically generated signal for event link controller - Event 0x105 */
#define RZV_ELC_UB1_TEI_N                             (0x106)  /* SCIF transmission end interrupt signal - Event 0x106 */
#define RZV_ELC_UB1_RXI_EDGE_N                        (0x107)  /* SCIF reception data full interrupt signal - Event 0x107 */
#define RZV_ELC_UB1_TXI_EDGE_N                        (0x108)  /* SCIF transmission data empty interrupt signal - Event 0x108 */
#define RZV_ELC_GPT_U0_GPT_GTCIH_N_0                  (0x109)  /* GPT0 A and B both high interrupt 0 - Event 0x109 */
#define RZV_ELC_GPT_U0_GPT_GTCIH_N_1                  (0x10A)  /* GPT0 A and B both high interrupt 1 - Event 0x10A */
#define RZV_ELC_GPT_U0_GPT_GTCIH_N_2                  (0x10B)  /* GPT0 A and B both high interrupt 2 - Event 0x10B */
#define RZV_ELC_GPT_U0_GPT_GTCIH_N_3                  (0x10C)  /* GPT0 A and B both high interrupt 3 - Event 0x10C */
#define RZV_ELC_GPT_U0_GPT_GTCIH_N_4                  (0x10D)  /* GPT0 A and B both high interrupt 4 - Event 0x10D */
#define RZV_ELC_GPT_U0_GPT_GTCIH_N_5                  (0x10E)  /* GPT0 A and B both high interrupt 5 - Event 0x10E */
#define RZV_ELC_GPT_U0_GPT_GTCIH_N_6                  (0x10F)  /* GPT0 A and B both high interrupt 6 - Event 0x10F */
#define RZV_ELC_GPT_U0_GPT_GTCIH_N_7                  (0x110)  /* GPT0 A and B both high interrupt 7 - Event 0x110 */
#define RZV_ELC_GPT_U0_GPT_GTCIL_N_0                  (0x111)  /* GPT0 A and B both low interrupt 0 - Event 0x111 */
#define RZV_ELC_GPT_U0_GPT_GTCIL_N_1                  (0x112)  /* GPT0 A and B both low interrupt 1 - Event 0x112 */
#define RZV_ELC_GPT_U0_GPT_GTCIL_N_2                  (0x113)  /* GPT0 A and B both low interrupt 2 - Event 0x113 */
#define RZV_ELC_GPT_U0_GPT_GTCIL_N_3                  (0x114)  /* GPT0 A and B both low interrupt 3 - Event 0x114 */
#define RZV_ELC_GPT_U0_GPT_GTCIL_N_4                  (0x115)  /* GPT0 A and B both low interrupt 4 - Event 0x115 */
#define RZV_ELC_GPT_U0_GPT_GTCIL_N_5                  (0x116)  /* GPT0 A and B both low interrupt 5 - Event 0x116 */
#define RZV_ELC_GPT_U0_GPT_GTCIL_N_6                  (0x117)  /* GPT0 A and B both low interrupt 6 - Event 0x117 */
#define RZV_ELC_GPT_U0_GPT_GTCIL_N_7                  (0x118)  /* GPT0 A and B both low interrupt 7 - Event 0x118 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPA_0                  (0x119)  /* GPT0 Input capture/compare match 0 of the GTCCRA register - Event 0x119 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPA_1                  (0x11A)  /* GPT0 Input capture/compare match 1 of the GTCCRA register - Event 0x11A */
#define RZV_ELC_GPT_U0_GPT_ELCCMPA_2                  (0x11B)  /* GPT0 Input capture/compare match 2 of the GTCCRA register - Event 0x11B */
#define RZV_ELC_GPT_U0_GPT_ELCCMPA_3                  (0x11C)  /* GPT0 Input capture/compare match 3 of the GTCCRA register - Event 0x11C */
#define RZV_ELC_GPT_U0_GPT_ELCCMPA_4                  (0x11D)  /* GPT0 Input capture/compare match 4 of the GTCCRA register - Event 0x11D */
#define RZV_ELC_GPT_U0_GPT_ELCCMPA_5                  (0x11E)  /* GPT0 Input capture/compare match 5 of the GTCCRA register - Event 0x11E */
#define RZV_ELC_GPT_U0_GPT_ELCCMPA_6                  (0x11F)  /* GPT0 Input capture/compare match 6 of the GTCCRA register - Event 0x11F */
#define RZV_ELC_GPT_U0_GPT_ELCCMPA_7                  (0x120)  /* GPT0 Input capture/compare match 7 of the GTCCRA register - Event 0x120 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPB_0                  (0x121)  /* GPT0 Input capture/compare match 0 of the GTCCRB register - Event 0x121 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPB_1                  (0x122)  /* GPT0 Input capture/compare match 1 of the GTCCRB register - Event 0x122 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPB_2                  (0x123)  /* GPT0 Input capture/compare match 2 of the GTCCRB register - Event 0x123 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPB_3                  (0x124)  /* GPT0 Input capture/compare match 3 of the GTCCRB register - Event 0x124 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPB_4                  (0x125)  /* GPT0 Input capture/compare match 4 of the GTCCRB register - Event 0x125 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPB_5                  (0x126)  /* GPT0 Input capture/compare match 5 of the GTCCRB register - Event 0x126 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPB_6                  (0x127)  /* GPT0 Input capture/compare match 6 of the GTCCRB register - Event 0x127 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPB_7                  (0x128)  /* GPT0 Input capture/compare match 7 of the GTCCRB register - Event 0x128 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPC_0                  (0x129)  /* GPT0 Input capture/compare match 0 of the GTCCRC register - Event 0x129 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPC_1                  (0x12A)  /* GPT0 Input capture/compare match 1 of the GTCCRC register - Event 0x12A */
#define RZV_ELC_GPT_U0_GPT_ELCCMPC_2                  (0x12B)  /* GPT0 Input capture/compare match 2 of the GTCCRC register - Event 0x12B */
#define RZV_ELC_GPT_U0_GPT_ELCCMPC_3                  (0x12C)  /* GPT0 Input capture/compare match 3 of the GTCCRC register - Event 0x12C */
#define RZV_ELC_GPT_U0_GPT_ELCCMPC_4                  (0x12D)  /* GPT0 Input capture/compare match 4 of the GTCCRC register - Event 0x12D */
#define RZV_ELC_GPT_U0_GPT_ELCCMPC_5                  (0x12E)  /* GPT0 Input capture/compare match 5 of the GTCCRC register - Event 0x12E */
#define RZV_ELC_GPT_U0_GPT_ELCCMPC_6                  (0x12F)  /* GPT0 Input capture/compare match 6 of the GTCCRC register - Event 0x12F */
#define RZV_ELC_GPT_U0_GPT_ELCCMPC_7                  (0x130)  /* GPT0 Input capture/compare match 7 of the GTCCRC register - Event 0x130 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPD_0                  (0x131)  /* GPT0 Input capture/compare match 0 of the GTCCRD register - Event 0x131 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPD_1                  (0x132)  /* GPT0 Input capture/compare match 1 of the GTCCRD register - Event 0x132 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPD_2                  (0x133)  /* GPT0 Input capture/compare match 2 of the GTCCRD register - Event 0x133 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPD_3                  (0x134)  /* GPT0 Input capture/compare match 3 of the GTCCRD register - Event 0x134 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPD_4                  (0x135)  /* GPT0 Input capture/compare match 4 of the GTCCRD register - Event 0x135 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPD_5                  (0x136)  /* GPT0 Input capture/compare match 5 of the GTCCRD register - Event 0x136 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPD_6                  (0x137)  /* GPT0 Input capture/compare match 6 of the GTCCRD register - Event 0x137 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPD_7                  (0x138)  /* GPT0 Input capture/compare match 7 of the GTCCRD register - Event 0x138 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPE_0                  (0x139)  /* GPT0 Input capture/compare match 0 of the GTCCRE register - Event 0x139 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPE_1                  (0x13A)  /* GPT0 Input capture/compare match 1 of the GTCCRE register - Event 0x13A */
#define RZV_ELC_GPT_U0_GPT_ELCCMPE_2                  (0x13B)  /* GPT0 Input capture/compare match 2 of the GTCCRE register - Event 0x13B */
#define RZV_ELC_GPT_U0_GPT_ELCCMPE_3                  (0x13C)  /* GPT0 Input capture/compare match 3 of the GTCCRE register - Event 0x13C */
#define RZV_ELC_GPT_U0_GPT_ELCCMPE_4                  (0x13D)  /* GPT0 Input capture/compare match 4 of the GTCCRE register - Event 0x13D */
#define RZV_ELC_GPT_U0_GPT_ELCCMPE_5                  (0x13E)  /* GPT0 Input capture/compare match 5 of the GTCCRE register - Event 0x13E */
#define RZV_ELC_GPT_U0_GPT_ELCCMPE_6                  (0x13F)  /* GPT0 Input capture/compare match 6 of the GTCCRE register - Event 0x13F */
#define RZV_ELC_GPT_U0_GPT_ELCCMPE_7                  (0x140)  /* GPT0 Input capture/compare match 7 of the GTCCRE register - Event 0x140 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPF_0                  (0x141)  /* GPT0 Input capture/compare match 0 of the GTCCRF register - Event 0x141 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPF_1                  (0x142)  /* GPT0 Input capture/compare match 1 of the GTCCRF register - Event 0x142 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPF_2                  (0x143)  /* GPT0 Input capture/compare match 2 of the GTCCRF register - Event 0x143 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPF_3                  (0x144)  /* GPT0 Input capture/compare match 3 of the GTCCRF register - Event 0x144 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPF_4                  (0x145)  /* GPT0 Input capture/compare match 4 of the GTCCRF register - Event 0x145 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPF_5                  (0x146)  /* GPT0 Input capture/compare match 5 of the GTCCRF register - Event 0x146 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPF_6                  (0x147)  /* GPT0 Input capture/compare match 6 of the GTCCRF register - Event 0x147 */
#define RZV_ELC_GPT_U0_GPT_ELCCMPF_7                  (0x148)  /* GPT0 Input capture/compare match 7 of the GTCCRF register - Event 0x148 */
#define RZV_ELC_GPT_U0_GPT_ELCOVF_0                   (0x149)  /* GPT0 Overflow 0 of the GTCNT counter - Event 0x149 */
#define RZV_ELC_GPT_U0_GPT_ELCOVF_1                   (0x14A)  /* GPT0 Overflow 1 of the GTCNT counter - Event 0x14A */
#define RZV_ELC_GPT_U0_GPT_ELCOVF_2                   (0x14B)  /* GPT0 Overflow 2 of the GTCNT counter - Event 0x14B */
#define RZV_ELC_GPT_U0_GPT_ELCOVF_3                   (0x14C)  /* GPT0 Overflow 3 of the GTCNT counter - Event 0x14C */
#define RZV_ELC_GPT_U0_GPT_ELCOVF_4                   (0x14D)  /* GPT0 Overflow 4 of the GTCNT counter - Event 0x14D */
#define RZV_ELC_GPT_U0_GPT_ELCOVF_5                   (0x14E)  /* GPT0 Overflow 5 of the GTCNT counter - Event 0x14E */
#define RZV_ELC_GPT_U0_GPT_ELCOVF_6                   (0x14F)  /* GPT0 Overflow 6 of the GTCNT counter - Event 0x14F */
#define RZV_ELC_GPT_U0_GPT_ELCOVF_7                   (0x150)  /* GPT0 Overflow 7 of the GTCNT counter - Event 0x150 */
#define RZV_ELC_GPT_U0_GPT_ELCUDF_0                   (0x151)  /* GPT0 Underflow 0 of the GTCNT counter - Event 0x151 */
#define RZV_ELC_GPT_U0_GPT_ELCUDF_1                   (0x152)  /* GPT0 Underflow 1 of the GTCNT counter - Event 0x152 */
#define RZV_ELC_GPT_U0_GPT_ELCUDF_2                   (0x153)  /* GPT0 Underflow 2 of the GTCNT counter - Event 0x153 */
#define RZV_ELC_GPT_U0_GPT_ELCUDF_3                   (0x154)  /* GPT0 Underflow 3 of the GTCNT counter - Event 0x154 */
#define RZV_ELC_GPT_U0_GPT_ELCUDF_4                   (0x155)  /* GPT0 Underflow 4 of the GTCNT counter - Event 0x155 */
#define RZV_ELC_GPT_U0_GPT_ELCUDF_5                   (0x156)  /* GPT0 Underflow 5 of the GTCNT counter - Event 0x156 */
#define RZV_ELC_GPT_U0_GPT_ELCUDF_6                   (0x157)  /* GPT0 Underflow 6 of the GTCNT counter - Event 0x157 */
#define RZV_ELC_GPT_U0_GPT_ELCUDF_7                   (0x158)  /* GPT0 Underflow 7 of the GTCNT counter - Event 0x158 */
#define RZV_ELC_GPT_U1_GPT_GTCIH_N_0                  (0x159)  /* GPT1 A and B both high interrupt 0 - Event 0x159 */
#define RZV_ELC_GPT_U1_GPT_GTCIH_N_1                  (0x15A)  /* GPT1 A and B both high interrupt 1 - Event 0x15A */
#define RZV_ELC_GPT_U1_GPT_GTCIH_N_2                  (0x15B)  /* GPT1 A and B both high interrupt 2 - Event 0x15B */
#define RZV_ELC_GPT_U1_GPT_GTCIH_N_3                  (0x15C)  /* GPT1 A and B both high interrupt 3 - Event 0x15C */
#define RZV_ELC_GPT_U1_GPT_GTCIH_N_4                  (0x15D)  /* GPT1 A and B both high interrupt 4 - Event 0x15D */
#define RZV_ELC_GPT_U1_GPT_GTCIH_N_5                  (0x15E)  /* GPT1 A and B both high interrupt 5 - Event 0x15E */
#define RZV_ELC_GPT_U1_GPT_GTCIH_N_6                  (0x15F)  /* GPT1 A and B both high interrupt 6 - Event 0x15F */
#define RZV_ELC_GPT_U1_GPT_GTCIH_N_7                  (0x160)  /* GPT1 A and B both high interrupt 7 - Event 0x160 */
#define RZV_ELC_GPT_U1_GPT_GTCIL_N_0                  (0x161)  /* GPT1 A and B both low interrupt 0 - Event 0x161 */
#define RZV_ELC_GPT_U1_GPT_GTCIL_N_1                  (0x162)  /* GPT1 A and B both low interrupt 1 - Event 0x162 */
#define RZV_ELC_GPT_U1_GPT_GTCIL_N_2                  (0x163)  /* GPT1 A and B both low interrupt 2 - Event 0x163 */
#define RZV_ELC_GPT_U1_GPT_GTCIL_N_3                  (0x164)  /* GPT1 A and B both low interrupt 3 - Event 0x164 */
#define RZV_ELC_GPT_U1_GPT_GTCIL_N_4                  (0x165)  /* GPT1 A and B both low interrupt 4 - Event 0x165 */
#define RZV_ELC_GPT_U1_GPT_GTCIL_N_5                  (0x166)  /* GPT1 A and B both low interrupt 5 - Event 0x166 */
#define RZV_ELC_GPT_U1_GPT_GTCIL_N_6                  (0x167)  /* GPT1 A and B both low interrupt 6 - Event 0x167 */
#define RZV_ELC_GPT_U1_GPT_GTCIL_N_7                  (0x168)  /* GPT1 A and B both low interrupt 7 - Event 0x168 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPA_0                  (0x169)  /* GPT1 Input capture/compare match 0 of the GTCCRA register - Event 0x169 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPA_1                  (0x16A)  /* GPT1 Input capture/compare match 1 of the GTCCRA register - Event 0x16A */
#define RZV_ELC_GPT_U1_GPT_ELCCMPA_2                  (0x16B)  /* GPT1 Input capture/compare match 2 of the GTCCRA register - Event 0x16B */
#define RZV_ELC_GPT_U1_GPT_ELCCMPA_3                  (0x16C)  /* GPT1 Input capture/compare match 3 of the GTCCRA register - Event 0x16C */
#define RZV_ELC_GPT_U1_GPT_ELCCMPA_4                  (0x16D)  /* GPT1 Input capture/compare match 4 of the GTCCRA register - Event 0x16D */
#define RZV_ELC_GPT_U1_GPT_ELCCMPA_5                  (0x16E)  /* GPT1 Input capture/compare match 5 of the GTCCRA register - Event 0x16E */
#define RZV_ELC_GPT_U1_GPT_ELCCMPA_6                  (0x16F)  /* GPT1 Input capture/compare match 6 of the GTCCRA register - Event 0x16F */
#define RZV_ELC_GPT_U1_GPT_ELCCMPA_7                  (0x170)  /* GPT1 Input capture/compare match 7 of the GTCCRA register - Event 0x170 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPB_0                  (0x171)  /* GPT1 Input capture/compare match 0 of the GTCCRB register - Event 0x171 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPB_1                  (0x172)  /* GPT1 Input capture/compare match 1 of the GTCCRB register - Event 0x172 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPB_2                  (0x173)  /* GPT1 Input capture/compare match 2 of the GTCCRB register - Event 0x173 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPB_3                  (0x174)  /* GPT1 Input capture/compare match 3 of the GTCCRB register - Event 0x174 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPB_4                  (0x175)  /* GPT1 Input capture/compare match 4 of the GTCCRB register - Event 0x175 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPB_5                  (0x176)  /* GPT1 Input capture/compare match 5 of the GTCCRB register - Event 0x176 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPB_6                  (0x177)  /* GPT1 Input capture/compare match 6 of the GTCCRB register - Event 0x177 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPB_7                  (0x178)  /* GPT1 Input capture/compare match 7 of the GTCCRB register - Event 0x178 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPC_0                  (0x179)  /* GPT1 Compare match 0 with the GTCCRC register - Event 0x179 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPC_1                  (0x17A)  /* GPT1 Compare match 1 with the GTCCRC register - Event 0x17A */
#define RZV_ELC_GPT_U1_GPT_ELCCMPC_2                  (0x17B)  /* GPT1 Compare match 2 with the GTCCRC register - Event 0x17B */
#define RZV_ELC_GPT_U1_GPT_ELCCMPC_3                  (0x17C)  /* GPT1 Compare match 3 with the GTCCRC register - Event 0x17C */
#define RZV_ELC_GPT_U1_GPT_ELCCMPC_4                  (0x17D)  /* GPT1 Compare match 4 with the GTCCRC register - Event 0x17D */
#define RZV_ELC_GPT_U1_GPT_ELCCMPC_5                  (0x17E)  /* GPT1 Compare match 5 with the GTCCRC register - Event 0x17E */
#define RZV_ELC_GPT_U1_GPT_ELCCMPC_6                  (0x17F)  /* GPT1 Compare match 6 with the GTCCRC register - Event 0x17F */
#define RZV_ELC_GPT_U1_GPT_ELCCMPC_7                  (0x180)  /* GPT1 Compare match 7 with the GTCCRC register - Event 0x180 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPD_0                  (0x181)  /* GPT1 Compare match 0 with the GTCCRD register - Event 0x181 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPD_1                  (0x182)  /* GPT1 Compare match 1 with the GTCCRD register - Event 0x182 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPD_2                  (0x183)  /* GPT1 Compare match 2 with the GTCCRD register - Event 0x183 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPD_3                  (0x184)  /* GPT1 Compare match 3 with the GTCCRD register - Event 0x184 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPD_4                  (0x185)  /* GPT1 Compare match 4 with the GTCCRD register - Event 0x185 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPD_5                  (0x186)  /* GPT1 Compare match 5 with the GTCCRD register - Event 0x186 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPD_6                  (0x187)  /* GPT1 Compare match 6 with the GTCCRD register - Event 0x187 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPD_7                  (0x188)  /* GPT1 Compare match 7 with the GTCCRD register - Event 0x188 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPE_0                  (0x189)  /* GPT1 Compare match 0 with the GTCCRE register - Event 0x189 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPE_1                  (0x18A)  /* GPT1 Compare match 1 with the GTCCRE register - Event 0x18A */
#define RZV_ELC_GPT_U1_GPT_ELCCMPE_2                  (0x18B)  /* GPT1 Compare match 2 with the GTCCRE register - Event 0x18B */
#define RZV_ELC_GPT_U1_GPT_ELCCMPE_3                  (0x18C)  /* GPT1 Compare match 3 with the GTCCRE register - Event 0x18C */
#define RZV_ELC_GPT_U1_GPT_ELCCMPE_4                  (0x18D)  /* GPT1 Compare match 4 with the GTCCRE register - Event 0x18D */
#define RZV_ELC_GPT_U1_GPT_ELCCMPE_5                  (0x18E)  /* GPT1 Compare match 5 with the GTCCRE register - Event 0x18E */
#define RZV_ELC_GPT_U1_GPT_ELCCMPE_6                  (0x18F)  /* GPT1 Compare match 6 with the GTCCRE register - Event 0x18F */
#define RZV_ELC_GPT_U1_GPT_ELCCMPE_7                  (0x190)  /* GPT1 Compare match 7 with the GTCCRE register - Event 0x190 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPF_0                  (0x191)  /* GPT1 Compare match 0 with the GTCCRF register - Event 0x191 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPF_1                  (0x192)  /* GPT1 Compare match 1 with the GTCCRF register - Event 0x192 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPF_2                  (0x193)  /* GPT1 Compare match 2 with the GTCCRF register - Event 0x193 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPF_3                  (0x194)  /* GPT1 Compare match 3 with the GTCCRF register - Event 0x194 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPF_4                  (0x195)  /* GPT1 Compare match 4 with the GTCCRF register - Event 0x195 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPF_5                  (0x196)  /* GPT1 Compare match 5 with the GTCCRF register - Event 0x196 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPF_6                  (0x197)  /* GPT1 Compare match 6 with the GTCCRF register - Event 0x197 */
#define RZV_ELC_GPT_U1_GPT_ELCCMPF_7                  (0x198)  /* GPT1 Compare match 7 with the GTCCRF register - Event 0x198 */
#define RZV_ELC_GPT_U1_GPT_ELCOVF_0                   (0x199)  /* GPT1 Overflow 0 of the GTCNT counter - Event 0x199 */
#define RZV_ELC_GPT_U1_GPT_ELCOVF_1                   (0x19A)  /* GPT1 Overflow 1 of the GTCNT counter - Event 0x19A */
#define RZV_ELC_GPT_U1_GPT_ELCOVF_2                   (0x19B)  /* GPT1 Overflow 2 of the GTCNT counter - Event 0x19B */
#define RZV_ELC_GPT_U1_GPT_ELCOVF_3                   (0x19C)  /* GPT1 Overflow 3 of the GTCNT counter - Event 0x19C */
#define RZV_ELC_GPT_U1_GPT_ELCOVF_4                   (0x19D)  /* GPT1 Overflow 4 of the GTCNT counter - Event 0x19D */
#define RZV_ELC_GPT_U1_GPT_ELCOVF_5                   (0x19E)  /* GPT1 Overflow 5 of the GTCNT counter - Event 0x19E */
#define RZV_ELC_GPT_U1_GPT_ELCOVF_6                   (0x19F)  /* GPT1 Overflow 6 of the GTCNT counter - Event 0x19F */
#define RZV_ELC_GPT_U1_GPT_ELCOVF_7                   (0x1A0)  /* GPT1 Overflow 7 of the GTCNT counter - Event 0x1A0 */
#define RZV_ELC_GPT_U1_GPT_ELCUDF_0                   (0x1A1)  /* GPT1 Underflow 0 of the GTCNT counter - Event 0x1A1 */
#define RZV_ELC_GPT_U1_GPT_ELCUDF_1                   (0x1A2)  /* GPT1 Underflow 1 of the GTCNT counter - Event 0x1A2 */
#define RZV_ELC_GPT_U1_GPT_ELCUDF_2                   (0x1A3)  /* GPT1 Underflow 2 of the GTCNT counter - Event 0x1A3 */
#define RZV_ELC_GPT_U1_GPT_ELCUDF_3                   (0x1A4)  /* GPT1 Underflow 3 of the GTCNT counter - Event 0x1A4 */
#define RZV_ELC_GPT_U1_GPT_ELCUDF_4                   (0x1A5)  /* GPT1 Underflow 4 of the GTCNT counter - Event 0x1A5 */
#define RZV_ELC_GPT_U1_GPT_ELCUDF_5                   (0x1A6)  /* GPT1 Underflow 5 of the GTCNT counter - Event 0x1A6 */
#define RZV_ELC_GPT_U1_GPT_ELCUDF_6                   (0x1A7)  /* GPT1 Underflow 6 of the GTCNT counter - Event 0x1A7 */
#define RZV_ELC_GPT_U1_GPT_ELCUDF_7                   (0x1A8)  /* GPT1 Underflow 7 of the GTCNT counter - Event 0x1A8 */
#define RZV_ELC_RI3C_ELCCOMMU                         (0x1A9)  /* I3C Communication event - Event 0x1A9 */
#define RZV_ELC_RI3C_ELCRESP                          (0x1AA)  /* I3C Response buffer full event - Event 0x1AA */
#define RZV_ELC_RI3C_ELCCMD                           (0x1AB)  /* I3C Command buffer empty event - Event 0x1AB */
#define RZV_ELC_RI3C_ELCIBI                           (0x1AC)  /* I3C IBI status buffer full event - Event 0x1AC */
#define RZV_ELC_RI3C_ELCRX                            (0x1AD)  /* I3C Rx data buffer full event - Event 0x1AD */
#define RZV_ELC_RI3C_ELCTX                            (0x1AE)  /* I3C Tx data buffer empty event - Event 0x1AE */
#define RZV_ELC_RI3C_ELCRCV                           (0x1AF)  /* I3C Receive status buffer full event - Event 0x1AF */
#define RZV_ELC_RI3C_ELCTEND                          (0x1B4)  /* I3C Transmit end event - Event 0x1B4 */
#define RZV_ELC_RI3C_ELCSTEV                          (0x1B5)  /* I3C Synchronous Timing Event - Event 0x1B5 */
#define RZV_ELC_RI3C_MREFOVF                          (0x1B6)  /* I3C MREF Counter Overflow - Event 0x1B6 */
#define RZV_ELC_RI3C_MREFCPT                          (0x1B7)  /* I3C MREF Capture Event - Event 0x1B7 */
#define RZV_ELC_RI3C_ELCAMEV                          (0x1B8)  /* I3C Additional Masterinitiated bus Event - Event 0x1B8 */
#define RZV_ELC_GBETH_PORT1_PTP_PPS_O_0               (0x1B9)  /* GBETH PORT1 Event (INPUT) 0 - Event 0x1B9 */
#define RZV_ELC_GBETH_PORT1_PTP_PPS_O_1               (0x1BA)  /* GBETH PORT1 Event (INPUT) 1 - Event 0x1BA */
#define RZV_ELC_GBETH_PORT1_PTP_PPS_O_2               (0x1BB)  /* GBETH PORT1 Event (INPUT) 2 - Event 0x1BB */
#define RZV_ELC_GBETH_PORT1_PTP_PPS_O_3               (0x1BC)  /* GBETH PORT1 Event (INPUT) 3 - Event 0x1BC */
#define RZV_ELC_GBETH_PORT0_PTP_PPS_O_0               (0x1BD)  /* GBETH PORT0 Event (INPUT) 0 - Event 0x1BD */
#define RZV_ELC_GBETH_PORT0_PTP_PPS_O_1               (0x1BE)  /* GBETH PORT0 Event (INPUT) 1 - Event 0x1BE */
#define RZV_ELC_GBETH_PORT0_PTP_PPS_O_2               (0x1BF)  /* GBETH PORT0 Event (INPUT) 2 - Event 0x1BF */
#define RZV_ELC_GBETH_PORT0_PTP_PPS_O_3               (0x1C0)  /* GBETH PORT0 Event (INPUT) 3 - Event 0x1C0 */
#define RZV_ELC_ISU_INT_FRE0                          (0x1C1)  /* ISU Frame end interrupt 0 - Event 0x1C1 */
#define RZV_ELC_ISU_INT_FRE1                          (0x1C2)  /* ISU Frame end interrupt 1 - Event 0x1C2 */
#define RZV_ELC_ISU_INT_FRE2                          (0x1C3)  /* ISU Frame end interrupt 2 - Event 0x1C3 */
#define RZV_ELC_ISU_INT_FRE3                          (0x1C4)  /* ISU Frame end interrupt 3 - Event 0x1C4 */
#define RZV_ELC_DRP1_ELCO                             (0x1C5)  /* DRP1 Interrupt signal for ELC - Event 0x1C5 */
#define RZV_ELC_DRP_AI_ELCO                           (0x1C6)  /* DRP-AI Interrupt signal for ELC - Event 0x1C6 */
#define RZV_ELC_DRP_AI_MAC_ELCO                       (0x1C7)  /* DRP-AI Interrupt signal for ELC - Event 0x1C7 */

/* INTC INTR8SEL registers provide 96 configurable slots (0-95)
 * mapping to GIC SPI interrupts 32-127 */
#define RZV_IRQ_ICU_SLOTS                             (96)      /* Hardware-limited INTR8SEL slots */
#define RZV_IRQ_GIC_SIZE                              (224)     /* Number of interrupts for RZ/V2H */

/* Total number of IRQ numbers */
#define RZV_IRQ_NEXTINT                             RZV_IRQ_GIC_SIZE

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

#endif /* __ARCH_ARM_INCLUDE_RZV_RZV2H_IRQ_H */

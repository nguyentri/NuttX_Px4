/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv2h/rzv2h_memorymap.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV2H_MEMORYMAP_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV2H_MEMORYMAP_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Registers Base Addresses - Auto-generated from CMSIS headers */

#define RZV_ADC_E0_BASE               0x11C00000UL
#define RZV_CANFD0_BASE               0x12440000UL
#define RZV_CMTW0_BASE                0x11C01800UL
#define RZV_CMTW1_BASE                0x11C01C00UL
#define RZV_CMTW2_BASE                0x11C02000UL
#define RZV_CMTW3_BASE                0x11C02400UL
#define RZV_CMTW4_BASE                0x13000C00UL
#define RZV_CMTW5_BASE                0x13001000UL
#define RZV_CMTW6_BASE                0x13001400UL
#define RZV_CMTW7_BASE                0x13001800UL
#define RZV_CPG0_BASE                 0x10420010UL
#define RZV_CRC0_BASE                 0x13000800UL
#define RZV_DMAC_B0_BASE              0x11400000UL
#define RZV_DMAC_B1_BASE              0x14830000UL
#define RZV_DMAC_B2_BASE              0x14840000UL
#define RZV_DMAC_B3_BASE              0x12000000UL
#define RZV_DMAC_B4_BASE              0x12010000UL
#define RZV_GLOBAL_TIMER0_BASE        0x12C10200UL
#define RZV_GPIO0_BASE                0x10410020UL
#define RZV_GPT0_BASE                 0x13010000UL
#define RZV_GPT1_BASE                 0x13010100UL
#define RZV_GPT10_BASE                0x13020000UL
#define RZV_GPT11_BASE                0x13020100UL
#define RZV_GPT12_BASE                0x13020200UL
#define RZV_GPT13_BASE                0x13020300UL
#define RZV_GPT14_BASE                0x13020400UL
#define RZV_GPT15_BASE                0x13020500UL
#define RZV_GPT16_BASE                0x13020600UL
#define RZV_GPT17_BASE                0x13020700UL
#define RZV_GPT2_BASE                 0x13010200UL
#define RZV_GPT3_BASE                 0x13010300UL
#define RZV_GPT4_BASE                 0x13010400UL
#define RZV_GPT5_BASE                 0x13010500UL
#define RZV_GPT6_BASE                 0x13010600UL
#define RZV_GPT7_BASE                 0x13010700UL
#define RZV_GTM0_BASE                 0x11800000UL
#define RZV_GTM1_BASE                 0x11801000UL
#define RZV_GTM2_BASE                 0x14000000UL
#define RZV_GTM3_BASE                 0x14001000UL
#define RZV_GTM4_BASE                 0x12C00000UL
#define RZV_GTM5_BASE                 0x12C01000UL
#define RZV_GTM6_BASE                 0x12C02000UL
#define RZV_GTM7_BASE                 0x12C03000UL
#define RZV_I3C_B0_BASE               0x12400000UL
#define RZV_INTC0_BASE                0x10400000UL
#define RZV_INTC_GIC0_BASE            0x12C10100UL
#define RZV_MHU_NS0_BASE              0x10480000UL
#define RZV_MHU_NS1_BASE              0x10480020UL
#define RZV_MHU_NS10_BASE             0x10480140UL
#define RZV_MHU_NS11_BASE             0x10480160UL
#define RZV_MHU_NS12_BASE             0x10480180UL
#define RZV_MHU_NS13_BASE             0x104801A0UL
#define RZV_MHU_NS14_BASE             0x104801C0UL
#define RZV_MHU_NS15_BASE             0x104801E0UL
#define RZV_MHU_NS16_BASE             0x10480200UL
#define RZV_MHU_NS17_BASE             0x10480220UL
#define RZV_MHU_NS18_BASE             0x10480240UL
#define RZV_MHU_NS19_BASE             0x10480260UL
#define RZV_MHU_NS2_BASE              0x10480040UL
#define RZV_MHU_NS20_BASE             0x10480280UL
#define RZV_MHU_NS21_BASE             0x104802A0UL
#define RZV_MHU_NS22_BASE             0x104802C0UL
#define RZV_MHU_NS23_BASE             0x104802E0UL
#define RZV_MHU_NS24_BASE             0x10480300UL
#define RZV_MHU_NS25_BASE             0x10480320UL
#define RZV_MHU_NS26_BASE             0x10480340UL
#define RZV_MHU_NS27_BASE             0x10480360UL
#define RZV_MHU_NS28_BASE             0x10480380UL
#define RZV_MHU_NS29_BASE             0x104803A0UL
#define RZV_MHU_NS3_BASE              0x10480060UL
#define RZV_MHU_NS30_BASE             0x104803C0UL
#define RZV_MHU_NS31_BASE             0x104803E0UL
#define RZV_MHU_NS32_BASE             0x10480400UL
#define RZV_MHU_NS33_BASE             0x10480420UL
#define RZV_MHU_NS34_BASE             0x10480440UL
#define RZV_MHU_NS35_BASE             0x10480460UL
#define RZV_MHU_NS36_BASE             0x10480480UL
#define RZV_MHU_NS37_BASE             0x104804A0UL
#define RZV_MHU_NS38_BASE             0x104804C0UL
#define RZV_MHU_NS39_BASE             0x104804E0UL
#define RZV_MHU_NS4_BASE              0x10480080UL
#define RZV_MHU_NS40_BASE             0x10480500UL
#define RZV_MHU_NS41_BASE             0x10480520UL
#define RZV_MHU_NS5_BASE              0x104800A0UL
#define RZV_MHU_NS6_BASE              0x104800C0UL
#define RZV_MHU_NS7_BASE              0x104800E0UL
#define RZV_MHU_NS8_BASE              0x10480100UL
#define RZV_MHU_NS9_BASE              0x10480120UL
#define RZV_MHU_S0_BASE               0x10481000UL
#define RZV_MHU_S1_BASE               0x10481020UL
#define RZV_MHU_S10_BASE              0x10481140UL
#define RZV_MHU_S11_BASE              0x10481160UL
#define RZV_MHU_S12_BASE              0x10481180UL
#define RZV_MHU_S13_BASE              0x104811A0UL
#define RZV_MHU_S14_BASE              0x104811C0UL
#define RZV_MHU_S15_BASE              0x104811E0UL
#define RZV_MHU_S16_BASE              0x10481200UL
#define RZV_MHU_S17_BASE              0x10481220UL
#define RZV_MHU_S18_BASE              0x10481240UL
#define RZV_MHU_S19_BASE              0x10481260UL
#define RZV_MHU_S2_BASE               0x10481040UL
#define RZV_MHU_S20_BASE              0x10481280UL
#define RZV_MHU_S21_BASE              0x104812A0UL
#define RZV_MHU_S22_BASE              0x104812C0UL
#define RZV_MHU_S23_BASE              0x104812E0UL
#define RZV_MHU_S24_BASE              0x10481300UL
#define RZV_MHU_S25_BASE              0x10481320UL
#define RZV_MHU_S26_BASE              0x10481340UL
#define RZV_MHU_S27_BASE              0x10481360UL
#define RZV_MHU_S28_BASE              0x10481380UL
#define RZV_MHU_S29_BASE              0x104813A0UL
#define RZV_MHU_S3_BASE               0x10481060UL
#define RZV_MHU_S30_BASE              0x104813C0UL
#define RZV_MHU_S31_BASE              0x104813E0UL
#define RZV_MHU_S32_BASE              0x10481400UL
#define RZV_MHU_S33_BASE              0x10481420UL
#define RZV_MHU_S34_BASE              0x10481440UL
#define RZV_MHU_S35_BASE              0x10481460UL
#define RZV_MHU_S36_BASE              0x10481480UL
#define RZV_MHU_S37_BASE              0x104814A0UL
#define RZV_MHU_S38_BASE              0x104814C0UL
#define RZV_MHU_S39_BASE              0x104814E0UL
#define RZV_MHU_S4_BASE               0x10481080UL
#define RZV_MHU_S40_BASE              0x10481500UL
#define RZV_MHU_S41_BASE              0x10481520UL
#define RZV_MHU_S5_BASE               0x104810A0UL
#define RZV_MHU_S6_BASE               0x104810C0UL
#define RZV_MHU_S7_BASE               0x104810E0UL
#define RZV_MHU_S8_BASE               0x10481100UL
#define RZV_MHU_S9_BASE               0x10481120UL
#define RZV_MHU_SWINT0_BASE           0x10480800UL
#define RZV_MHU_SWINT1_BASE           0x10480810UL
#define RZV_MHU_SWINT10_BASE          0x104808A0UL
#define RZV_MHU_SWINT11_BASE          0x104808B0UL
#define RZV_MHU_SWINT12_BASE          0x104808C0UL
#define RZV_MHU_SWINT13_BASE          0x104808D0UL
#define RZV_MHU_SWINT14_BASE          0x104808E0UL
#define RZV_MHU_SWINT15_BASE          0x104808F0UL
#define RZV_MHU_SWINT16_BASE          0x10480900UL
#define RZV_MHU_SWINT17_BASE          0x10480910UL
#define RZV_MHU_SWINT18_BASE          0x10480920UL
#define RZV_MHU_SWINT19_BASE          0x10480930UL
#define RZV_MHU_SWINT2_BASE           0x10480820UL
#define RZV_MHU_SWINT20_BASE          0x10480940UL
#define RZV_MHU_SWINT21_BASE          0x10480950UL
#define RZV_MHU_SWINT22_BASE          0x10480960UL
#define RZV_MHU_SWINT23_BASE          0x10480970UL
#define RZV_MHU_SWINT24_BASE          0x10480980UL
#define RZV_MHU_SWINT25_BASE          0x10480990UL
#define RZV_MHU_SWINT26_BASE          0x104809A0UL
#define RZV_MHU_SWINT27_BASE          0x104809B0UL
#define RZV_MHU_SWINT3_BASE           0x10480830UL
#define RZV_MHU_SWINT4_BASE           0x10480840UL
#define RZV_MHU_SWINT5_BASE           0x10480850UL
#define RZV_MHU_SWINT6_BASE           0x10480860UL
#define RZV_MHU_SWINT7_BASE           0x10480870UL
#define RZV_MHU_SWINT8_BASE           0x10480880UL
#define RZV_MHU_SWINT9_BASE           0x10480890UL
#define RZV_PDM0_BASE                 0x11040000UL
#define RZV_PDM1_BASE                 0x11050000UL
#define RZV_POEG0A0_BASE              0x13001C00UL
#define RZV_POEG0B0_BASE              0x13002000UL
#define RZV_POEG0C0_BASE              0x13002400UL
#define RZV_POEG0D0_BASE              0x13002800UL
#define RZV_POEG1A0_BASE              0x13002C00UL
#define RZV_POEG1B0_BASE              0x13003000UL
#define RZV_POEG1C0_BASE              0x13003400UL
#define RZV_POEG1D0_BASE              0x13003800UL
#define RZV_PRIVATE_TIMER0_BASE       0x12C10600UL
#define RZV_RIIC0_BASE                0x14400400UL
#define RZV_RIIC1_BASE                0x14400800UL
#define RZV_RIIC2_BASE                0x14400C00UL
#define RZV_RIIC3_BASE                0x14401000UL
#define RZV_RIIC4_BASE                0x14401400UL
#define RZV_RIIC5_BASE                0x14401800UL
#define RZV_RIIC6_BASE                0x14401C00UL
#define RZV_RIIC7_BASE                0x14402000UL
#define RZV_RIIC8_BASE                0x11C01000UL
#define RZV_RTC0_BASE                 0x11C00800UL
#define RZV_RTC_RO0_BASE              0x11C00C00UL
#define RZV_SCI0_BASE                 0x12800C00UL
#define RZV_SCI1_BASE                 0x12801000UL
#define RZV_SCI2_BASE                 0x12801400UL
#define RZV_SCI3_BASE                 0x12801800UL
#define RZV_SCI4_BASE                 0x12801C00UL
#define RZV_SCI5_BASE                 0x12802000UL
#define RZV_SCI6_BASE                 0x12802400UL
#define RZV_SCI7_BASE                 0x12802800UL
#define RZV_SCI8_BASE                 0x12802C00UL
#define RZV_SCI9_BASE                 0x12803000UL
#define RZV_SCIFA0_BASE               0x11C01400UL
#define RZV_SCU0_BASE                 0x12C10000UL
#define RZV_SPIBSC0_BASE              0x40060000UL
#define RZV_SPI_B0_BASE               0x12800000UL
#define RZV_SPI_B1_BASE               0x12800400UL
#define RZV_SPI_B2_BASE               0x12800800UL
#define RZV_SSI0_BASE                 0x40049C00UL
#define RZV_SSI1_BASE                 0x4004A000UL
#define RZV_SSI2_BASE                 0x4004A400UL
#define RZV_SSI3_BASE                 0x4004A800UL
#define RZV_SYSC0_BASE                0x10430000UL
#define RZV_TSU_B0_BASE               0x11000000UL
#define RZV_TSU_B1_BASE               0x14002000UL
#define RZV_TZC_AXI_RCPU0_BASE        0x13CA0000UL
#define RZV_TZC_DDR00_BASE            0x13C60000UL
#define RZV_TZC_DDR01_BASE            0x13C70000UL
#define RZV_TZC_DDR10_BASE            0x13C80000UL
#define RZV_TZC_DDR11_BASE            0x13C90000UL
#define RZV_TZC_PCIE0_BASE            0x13CC0000UL
#define RZV_TZC_SRAMA0_BASE           0x13CB0000UL
#define RZV_TZC_SRAMM0_BASE           0x10460000UL
#define RZV_TZC_XSPI0_BASE            0x10470000UL
#define RZV_WDT0_BASE                 0x11C00400UL
#define RZV_WDT1_BASE                 0x14400000UL
#define RZV_WDT2_BASE                 0x13000000UL
#define RZV_WDT3_BASE                 0x13000400UL
#define RZV_XSPI0_BASE                0x11030000UL

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV2H_MEMORYMAP_H */

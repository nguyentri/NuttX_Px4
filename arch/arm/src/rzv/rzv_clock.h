/****************************************************************************
 * arch/arm/src/rzv/rzv_clock.h
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

#ifndef __ARCH_ARM_SRC_RZV_CLOCK_H
#define __ARCH_ARM_SRC_RZV_CLOCK_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/* ARM_DSB() for barrier after CLKON/RST writes.
 * Included from arch-specific barriers.h via arm_internal.h if available;
 * provide a fallback inline asm for files that include this header standalone.
 */
#if defined(__GNUC__) && !defined(ARM_DSB)
#  define ARM_DSB()  __asm__ __volatile__ ("dsb" : : : "memory")
#endif

#if defined(__has_include)
#  if __has_include(<nuttx/config.h>)
#    include <nuttx/config.h>
#  endif
#elif !defined(__NuttX__) /* Fallback for toolchains without __has_include */
/* Leave the include out when the build environment does not provide the
 * NuttX configuration header.  The source files that require it should
 * include the header directly when available.
 */
#else
#  include <nuttx/config.h>
#endif

#include "hardware/rzv_cpg.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Clock domains and module IDs *********************************************/
/*
 * Encoding: (CLKON_reg_index << 16) | bit_position
 *   CLKON_reg_index → CPG_CLKON_N  (N in RZV_CPG_CLKON(N))
 *   bit_position    → bit within the 16-bit control field [15:0]
 *
 * NOTE: R9A09G057H uses only numbered CPG_CLKON_N registers (no named
 * aliases like CPG_CLKON_GPIO).  The mapping below is UNVERIFIED against
 * hardware documentation; it needs confirmation from the RZ/V2H HW manual.
 * TODO: validate each entry against RZ/V2H UM Table 9.x.
 * See .
 */

/* CLKON_0 - GPIO, CA55 core clocks */
/* UNVERIFIED: GPIO channel 0; needs RZ/V2H UM confirmation */
#define RZV_CPG_CLK_GPIO            (0 << 16 | 0)
/* ICU clock gate - CPG_CLKON_0 bit 5, reset CPG_RST_3 bit 6.
 * Verified vs FSP r_cpg enum CPG_CLK_ICU_0_PCLK=0x00200600 (CLKON_0, mask
 * 0x0020) and CPG_RST_ICU_0_PRESETN_I=0x0040090C (RST_3, mask 0x0040).
 * Reset applied via the ICU special-case in rzv_module_reset/unreset.
 * (Previous bit 1 fell inside the DMAC 5-bit field in CPG_CLKON_0.)
 */
#define RZV_CPG_CLK_ICU             (0 << 16 | 5)

/* RSCI (SCI-B) UART clock gates — CPG_CLKON_5..8, FIVE gate bits per
 * channel (SCIPCLK, SCITCLK, SCIPS3, SCIPS2, SCIPS1) occupying five
 * CONSECUTIVE bits in the CLKON bit space starting at CLKON_5 bit 13 for
 * channel 0 (global bit 93 + 5*ch).  The span may cross a register
 * boundary (SCI0: CLKON_5[15:13]+CLKON_6[1:0]; SCI3: CLKON_6[15:12]+
 * CLKON_7[0]).
 *
 * The ID encodes the FIRST (SCIPCLK) bit; rzv_clock_enable/disable and
 * rzv_module_reset/unreset special-case SCI IDs to control the full span
 * (see rzv_cpg_sci_channel() in rzv_clock.c).
 *
 * Source: FSP rzv2h bsp_override.h R_BSP_MODULE_START_FSP_IP_SCI +
 * BSP_CLKON_REG/BIT_FSP_IP_SCIP/SCIT/SCIPS1-3.
 * Reset: CPG_RST_8/9, two bits per channel (SCIP=RSTB(1+2ch),
 * SCIT=RSTB(2+2ch)) — also handled by the SCI special-case.
 */
#define RZV_CPG_CLK_SCI0            (5 << 16 | 13)
#define RZV_CPG_CLK_SCI1            (6 << 16 | 2)
#define RZV_CPG_CLK_SCI2            (6 << 16 | 7)
#define RZV_CPG_CLK_SCI3            (6 << 16 | 12)
#define RZV_CPG_CLK_SCI4            (7 << 16 | 1)
#define RZV_CPG_CLK_SCI5            (7 << 16 | 6)
#define RZV_CPG_CLK_SCI6            (7 << 16 | 11)
#define RZV_CPG_CLK_SCI7            (8 << 16 | 0)
#define RZV_CPG_CLK_SCI8            (8 << 16 | 5)
#define RZV_CPG_CLK_SCI9            (8 << 16 | 10)

/* SPI (RSPI) clock gates - CPG_CLKON_5, 3-bit group per channel.
 * Verified vs FSP bsp_override.h BSP_CLKON_REG/BIT_FSP_IP_RSPI (R9A09G057H):
 *   RSPI(ch) = CPG_CLKON_5, 7U << (CLK4_ON_Pos + 3*ch); CLK4_ON_Pos = 4.
 *   SPI0 = bits[6:4], SPI1 = bits[9:7], SPI2 = bits[12:10].
 * The 3-bit enable/disable is handled in rzv_clock_enable/disable.
 * Reset lives in CPG_RST_7 (RSPIP+RSPIT, 2 bits at RSTB(11+2*ch)); applied
 * via the RSPI special-case in rzv_module_reset/unreset.  SPI2's RSPIT
 * spans into CPG_RST_8 and is not covered (SPI0/1 only).
 * (Previous domain 2 bits 0-2, 1-bit, were wrong for both clock and reset.)
 */
#define RZV_CPG_CLK_SPI0            (5 << 16 | 4)
#define RZV_CPG_CLK_SPI1            (5 << 16 | 7)
#define RZV_CPG_CLK_SPI2            (5 << 16 | 10)

/* I2C (RIIC) clock gates - CPG_CLKON_9.
 * Verified vs FSP bsp_override.h BSP_CLKON_REG/BIT_FSP_IP_RIIC (R9A09G057H):
 *   RIIC(ch) = CPG_CLKON_9, bit = CLK4_ON_Pos + ch  (RIIC8 = CLK3).
 *   CLK4_ON_Pos = 4, so RIIC0-3 = bits 4-7.
 * Cross-checked via CLKMON: RIIC0 global 16*9+4=148 -> CLKMON_4 bit20,
 *   matching BSP_CLKMON_BIT_FSP_IP_RIIC (CLK20_MON).
 * (Previous domain 3 bits 0-3 were wrong.)
 */
#define RZV_CPG_CLK_I2C0            (9 << 16 | 4)
#define RZV_CPG_CLK_I2C1            (9 << 16 | 5)
#define RZV_CPG_CLK_I2C2            (9 << 16 | 6)
#define RZV_CPG_CLK_I2C3            (9 << 16 | 7)

/* OSTM timers - UNVERIFIED: needs RZ/V2H UM confirmation.
 * GPT and OSTM likely share CPG_CLKON_4 but bit offsets unknown. */
#define RZV_CPG_CLK_OSTM0           (4 << 16 | 11)
#define RZV_CPG_CLK_OSTM1           (4 << 16 | 12)
#define RZV_CPG_CLK_OSTM2           (4 << 16 | 13)

/* GTM (General Timer Module) clock gates - CPG_CLKON_4.
 * Verified vs FSP bsp_override.h BSP_CLKON_REG/BIT_FSP_IP_GTM (R9A09G057H):
 *   GTM(ch) = CPG_CLKON_4, bit = CLK3_ON_Pos + ch = 3 + ch  (GTM0-7 = 3..10).
 * Cross-checked via CLKMON: GTM7 global 16*4+10=74 -> CLKMON_2 bit10,
 *   matching BSP_CLKMON_BIT_FSP_IP_GTM (CLK3_MON + ch).
 * Reset lives in a DIFFERENT bank (CPG_RST_6/7) and is applied via the GTM
 * special-case in rzv_module_reset/unreset — do NOT assume RST index == 4.
 * (Previous domain 5 bits 0-7 were wrong for both clock and reset.)
 */
#define RZV_CPG_CLK_GTM0            (4 << 16 | 3)
#define RZV_CPG_CLK_GTM1            (4 << 16 | 4)
#define RZV_CPG_CLK_GTM2            (4 << 16 | 5)
#define RZV_CPG_CLK_GTM3            (4 << 16 | 6)
#define RZV_CPG_CLK_GTM4            (4 << 16 | 7)
#define RZV_CPG_CLK_GTM5            (4 << 16 | 8)
#define RZV_CPG_CLK_GTM6            (4 << 16 | 9)
#define RZV_CPG_CLK_GTM7            (4 << 16 | 10)

/* DMAC_B - CPG_CLKON_0 (domain 0), 5-bit mask [4:0] for 5 units.
 *   CLK0_ON_Pos = 0 (cpg_iobitmask.h).
 * D2-fix: domain was 6 (wrong), must be 0 (CPG_CLKON_0).
 * The rzv_clock_enable/disable DMAC special-case uses 0x1F mask (5 units). */
#define RZV_CPG_CLK_DMAC            (0 << 16 | 0)   /* DMAC: CPG_CLKON_0 bits[4:0], 5-unit mask */

/* Legacy per-unit aliases (DMAC driver compatibility).
 * All resolve to the same CLKON entry — there is one gate for all DMAC. */
#define RZV_CPG_CLK_DMAC0           RZV_CPG_CLK_DMAC
#define RZV_CPG_CLK_DMAC1           RZV_CPG_CLK_DMAC
#define RZV_CPG_CLK_DMAC2           RZV_CPG_CLK_DMAC
#define RZV_CPG_CLK_DMAC3           RZV_CPG_CLK_DMAC

/* CANFD - CPG_CLKON_9 bits[14:12] (3-bit mask CLK12/13/14, value 7U<<12)
 * Source: bsp_override.h lines 1692-1693 (R9A09G057H):
 *   BSP_CLKON_REG_FSP_IP_CANFD(ch)  = R_CPG->CPG_CLKON_9
 *   BSP_CLKON_BIT_FSP_IP_CANFD(ch)  = 7U << R_CPG_CPG_CLKON_9_CLK12_ON_Pos
 *   R_CPG_CPG_CLKON_9_CLK12_ON_Pos  = 12 (cpg_iobitmask.h:1319)
 * Encoding: (CLKON_reg_index << 16 | bit_position) = (9 << 16 | 12)
 * CORRECTED from previous wrong value (7 << 16 | 0).
 * Reset: CPG_RST_10 bits[2:1] (3U<<1). Same encoding → (10 << 16 | 1).
 * Module-stop: CPG_BUS_10_MSTOP bit 14 (RZ/V2H UM Table 4.4-38); released
 * via g_rzv_mstop_map in rzv_clock.c.
 */
#define RZV_CPG_CLK_CANFD           (9 << 16 | 12)
#define RZV_CPG_CLK_CAN0            RZV_CPG_CLK_CANFD  /* CAN0 shares CANFD gate */
#define RZV_CPG_CLK_CAN1            RZV_CPG_CLK_CANFD  /* CAN1 shares CANFD gate */

/* Ethernet (GBE) - UNVERIFIED: needs RZ/V2H UM confirmation
 *
 * TODO(rzv2h-eth-clocks): only the GBETH0 module gate is currently exposed.
 * The following additional CPG gate IDs must be added once the CPG_CLKON_N
 * register index and bit position for each are pulled from the RZ/V2H User's
 * Manual (cross-reference bsp_clocks.h, search "ETH"/"GBE"):
 *   RZV_CPG_CLK_ETH1            - GBETH1 module gate
 *   RZV_CPG_CLK_ETHTX0CLK       - GBETH0 TX 125 MHz reference clock gate
 *   RZV_CPG_CLK_ETHRX0CLK       - GBETH0 RX 125 MHz reference clock gate
 *   RZV_CPG_CLK_ETHTX1CLK       - GBETH1 TX 125 MHz reference clock gate
 *   RZV_CPG_CLK_ETHRX1CLK       - GBETH1 RX 125 MHz reference clock gate
 *   RZV_CPG_CLK_ET0_TXC_TXCLK   - GBETH0 RGMII TXC pad clock gate
 *   RZV_CPG_CLK_ET0_RXC_RXCLK   - GBETH0 RGMII RXC pad clock gate
 *   RZV_CPG_CLK_ET1_TXC_TXCLK   - GBETH1 RGMII TXC pad clock gate
 *   RZV_CPG_CLK_ET1_RXC_RXCLK   - GBETH1 RGMII RXC pad clock gate
 * Until these are added, boards/arm/rzv/rdk-rzv2h/src/rzv2h_ether.c can only
 * bring up GBETH0 and the RGMII reference clocks are assumed gated-on by
 * earlier boot stages (TF-A / U-Boot).
 */
#define RZV_CPG_CLK_ETH0            (8 << 16 | 0)

/* ADC - CPG_CLKON_16 bits [8:7] (2-bit pair). */
#define RZV_CPG_CLK_ADC0            (16 << 16 | 7)
#define RZV_CPG_CLK_ADC1            RZV_CPG_CLK_ADC0

/* SDHI clock and reset IDs -- decoded from FSP CPG enum values.
 *
 * FSP source: refs/rzv2h_gb_ether/drivers/r_cpg_api.h
 *   CPG_CLK_SDHI_0_IMCLK = 0x00080628  -> offset=0x0628, mask_val=0x0008
 *   CPG_RST_SDHI_0_IXRST = 0x00800928  -> offset=0x0928, mask_val=0x0080
 *
 * NuttX rzv_clock encoding: ((CLKON_reg_index << 16) | bit_position)
 *   CLKON domain = (0x0628 - 0x05F0) / 4 = 14, bit = 3  (mask 0x0008 -> ffs-1=3)
 *   RST   domain = (0x0928 - 0x08F0) / 4 = 14, bit = 7  (mask 0x0080 -> ffs-1=7)
 *
 * NuttX rzv_module_unreset() uses (domain<<16 | bit) with the same convention.
 * NEEDS_VERIFY: confirm CPG_CLKON_14 bit 3 = SDHI0_IMCLK against RZ/V2H UM.
 */
/* SDHI IMCLK gates - CPG_CLKON_14, decoded from FSP r_cpg CPG_CLK_SDHI_n_IMCLK
 * enum (offset 0x0628 = CLKON_14; upper16 = clock bitmask):
 *   SDHI0 IMCLK 0x00080628 -> mask 0x0008 -> bit 3
 *   SDHI1 IMCLK 0x00800628 -> mask 0x0080 -> bit 7
 *   SDHI2 IMCLK 0x08000628 -> mask 0x0800 -> bit 11
 * (Previous SDHI1 bit 11 / SDHI2 bit 19 were wrong; bit 19 even fell into the
 * write-enable half of the 16-bit control field.)
 */
/* SDHI IMCLK gates - CPG_CLKON_10; reset CPG_RST_10.  Decoded from FSP
 * r_cpg enum with HWM-absolute offsets (CLKON_0=0x600, RST_0=0x900):
 *   CPG_CLK_SDHI_n_IMCLK 0x0628 -> CLKON_10, masks 0x0008/0x0080/0x0800
 *     -> SDHI0/1/2 = bits 3/7/11.
 *   CPG_RST_SDHI_n_IXRST 0x0928 -> RST_10, masks 0x0080/0x0100/0x0200
 *     -> SDHI0/1/2 = bits 7/8/9.
 * (Previous domain 14 used 0x5F0 as the CLKON/RST base, i.e. it ignored the
 *  +0x10 already folded into RZV_CPG_BASE, landing 4 registers too high.)
 * NOTE: only IMCLK is gated here; full SDHI bring-up also needs IMCLK2,
 * CLK_HS and ACLK (CPG_CLKON_10 bits 4-6/8-10/12-14).
 */
#define RZV_CPG_CLK_SDHI0           (10 << 16 | 3)  /* SDHI0 IMCLK gate */
#define RZV_CPG_CLK_SDHI1           (10 << 16 | 7)  /* SDHI1 IMCLK gate */
#define RZV_CPG_CLK_SDHI2           (10 << 16 | 11) /* SDHI2 IMCLK gate */
#define RZV_CPG_RST_SDHI0           (10 << 16 | 7)  /* SDHI0 IXRST deassert */
#define RZV_CPG_RST_SDHI1           (10 << 16 | 8)  /* SDHI1 IXRST */
#define RZV_CPG_RST_SDHI2           (10 << 16 | 9)  /* SDHI2 IXRST */


/* Maximum values ***********************************************************/

#define RZV_CPG_MAX_CLKON     24    /* CLKON0-CLKON24 */
#define RZV_CPG_MAX_CLKMON    10    /* CLKMON0-CLKMON10 */
#define RZV_CPG_MAX_RST       17    /* RST0-RST17 */
#define RZV_CPG_MAX_RSTMON    8     /* RSTMON0-RSTMON8 */

/* Board-specific clock frequencies (Hz) ************************************/
/* These values are based on the RZ/V2H EVK clock configuration.
 * Adjust these for your specific board/configuration.
 */

#define RZV_CLOCK_OSCCLK_HZ           (24000000)    /* OSC 24MHz */
#define RZV_CLOCK_OSC2CLK_HZ          (4800000)     /* OSC2 4.8MHz */

/* PLL output frequencies */
#define RZV_CLOCK_PLLCM33CLK_HZ       (1600000000)  /* PLLCM33 1.6GHz */
#define RZV_CLOCK_PLLCLNCLK_HZ        (1600000000)  /* PLLCLN 1.6GHz */
#define RZV_CLOCK_PLLDTYCLK_HZ        (1600000000)  /* PLLDTY 1.6GHz */
#define RZV_CLOCK_PLLCA55CLK_HZ       (1800000000)  /* PLLCA55 1.8GHz */
#define RZV_CLOCK_PLLDRPCLK_HZ        (1260000000)  /* PLLDRP 1.26GHz */
#define RZV_CLOCK_PLLVDOCLK_HZ        (1260000000)  /* PLLVDO 1.26GHz */
#define RZV_CLOCK_PLLETHCLK_HZ        (1000000000)  /* PLLETH 1GHz */
#define RZV_CLOCK_PLLDSICLK_HZ        (297000000)   /* PLLDSI 297MHz */
#define RZV_CLOCK_PLLGPUCLK_HZ        (1260000000)  /* PLLGPU 1.26GHz */
#define RZV_CLOCK_PLLDDR0CLK_HZ       (800000000)   /* PLLDDR0 800MHz */
#define RZV_CLOCK_PLLDDR1CLK_HZ       (800000000)   /* PLLDDR1 800MHz */

/* Core/CPU clock frequencies */
#define RZV_CLOCK_I0CLK_HZ            (1800000000)  /* Core 0 1.8GHz */
#define RZV_CLOCK_I1CLK_HZ            (1800000000)  /* Core 1 1.8GHz */
#define RZV_CLOCK_I2CLK_HZ            (1800000000)  /* Core 2 1.8GHz */
#define RZV_CLOCK_I3CLK_HZ            (1800000000)  /* Core 3 1.8GHz */
#define RZV_CLOCK_I4CLK_HZ            (450000000)   /* Peripheral bus 450MHz */
#define RZV_CLOCK_I5CLK_HZ            (1260000000)  /* System bus 1.26GHz */
#define RZV_CLOCK_I6CLK_HZ            (800000000)   /* CR8 CPU 800MHz */
#define RZV_CLOCK_I7CLK_HZ            (200000000)   /* System 200MHz */
#define RZV_CLOCK_ICLK_HZ             (1800000000)  /* Internal clock 1.8GHz */

/* Peripheral clock buses */
#define RZV_CLOCK_P0CLK_HZ            (100000000)   /* Peripheral 0 100MHz */
#define RZV_CLOCK_P1CLK_HZ            (100000000)   /* Peripheral 1 100MHz */
#define RZV_CLOCK_P2CLK_HZ            (50000000)    /* Peripheral 2 50MHz */
#define RZV_CLOCK_P3CLK_HZ            (400000000)   /* Peripheral 3 400MHz */
#define RZV_CLOCK_P4CLK_HZ            (200000000)   /* Peripheral 4 200MHz */
#define RZV_CLOCK_P5CLK_HZ            (100000000)   /* Peripheral 5 100MHz */
#define RZV_CLOCK_P6CLK_HZ            (50000000)    /* Peripheral 6 50MHz */
#define RZV_CLOCK_P7CLK_HZ            (400000000)   /* Peripheral 7 400MHz */
#define RZV_CLOCK_P8CLK_HZ            (200000000)   /* Peripheral 8 200MHz */
#define RZV_CLOCK_P9CLK_HZ            (100000000)   /* Peripheral 9 100MHz */
#define RZV_CLOCK_P10CLK_HZ           (200000000)   /* Peripheral 10 200MHz */
#define RZV_CLOCK_P11CLK_HZ           (200000000)   /* Peripheral 11 200MHz */
#define RZV_CLOCK_P12CLK_HZ           (400000000)   /* Peripheral 12 400MHz */

/* Special function clocks */
#define RZV_CLOCK_ATCLK_HZ            (400000000)   /* CoreSight ATB 400MHz */
#define RZV_CLOCK_ZTCLK_HZ            (100000000)   /* ZT clock 100MHz */
#define RZV_CLOCK_HPCLK_HZ            (125000000)   /* HP clock 125MHz */
#define RZV_CLOCK_LPCLK_HZ            (15625000)    /* LP clock 15.625MHz */

/* Video/Display clocks */
#define RZV_CLOCK_M0CLK_HZ            (630000000)   /* Video 0 630MHz */
#define RZV_CLOCK_M1CLK_HZ            (630000000)   /* Video 1 630MHz */
#define RZV_CLOCK_M2CLK_HZ            (630000000)   /* Video 2 630MHz */
#define RZV_CLOCK_M3CLK_HZ            (630000000)   /* Video 3 630MHz */
#define RZV_CLOCK_M4CLK_HZ            (148500000)   /* Video 4 148.5MHz */
#define RZV_CLOCK_ISPCLK_HZ           (630000000)   /* ISP 630MHz */
#define RZV_CLOCK_ISUCLK_HZ           (630000000)   /* ISU 630MHz */
#define RZV_CLOCK_GPUCLK_HZ           (630000000)   /* GPU 630MHz */

/* SPI/SD clocks */
#define RZV_CLOCK_SPI0CLK_HZ          (266666666)   /* SPI 0 266.67MHz */
#define RZV_CLOCK_SPI1CLK_HZ          (133333333)   /* SPI 1 133.33MHz */
#define RZV_CLOCK_SPI2CLK_HZ          (66666666)    /* SPI 2 66.67MHz — UNVERIFIED */
#define RZV_CLOCK_SDCLK_HZ            (800000000)   /* SD base 800MHz */
#define RZV_CLOCK_SD0CLK_HZ           (200000000)   /* SD0 200MHz — UNVERIFIED */
#define RZV_CLOCK_SD1CLK_HZ           (200000000)   /* SD1 200MHz — UNVERIFIED */

/* System bus / fabric clocks */
#define RZV_CLOCK_GCLK_HZ             (200000000)   /* G-bus 200MHz — UNVERIFIED */
#define RZV_CLOCK_S0CLK_HZ            (200000000)   /* S0 clock 200MHz — UNVERIFIED */
#define RZV_CLOCK_S1CLK_HZ            (200000000)   /* S1 clock 200MHz — UNVERIFIED */
#define RZV_CLOCK_S2CLK_HZ            (200000000)   /* S2 clock 200MHz — UNVERIFIED */
#define RZV_CLOCK_S3CLK_HZ            (200000000)   /* S3 clock 200MHz — UNVERIFIED */
#define RZV_CLOCK_M5CLK_HZ            (148500000)   /* Video 5 148.5MHz — UNVERIFIED */
#define RZV_CLOCK_TSUCLK_HZ           (4000000)     /* TSU 4MHz — UNVERIFIED */
#define RZV_CLOCK_P13CLK_HZ           (200000000)   /* Peripheral 13 200MHz — UNVERIFIED */
#define RZV_CLOCK_P14CLK_HZ           (200000000)   /* Peripheral 14 200MHz — UNVERIFIED */
#define RZV_CLOCK_P15CLK_HZ           (200000000)   /* Peripheral 15 200MHz — UNVERIFIED */

/* Communication clocks */
#define RZV_CLOCK_CANCLK_HZ           (80000000)    /* CAN 80MHz */
#define RZV_CLOCK_CANFDCLK_HZ         (80000000)    /* CANFD 80MHz — UNVERIFIED */
#define RZV_CLOCK_ADCCLK_HZ           (50000000)    /* ADC 50MHz */

/* Ethernet clocks */
#define RZV_CLOCK_ETHTX0CLK_HZ        (125000000)   /* ETH0 TX 125MHz */
#define RZV_CLOCK_ETHRX0CLK_HZ        (125000000)   /* ETH0 RX 125MHz */
#define RZV_CLOCK_ETHTX1CLK_HZ        (125000000)   /* ETH1 TX 125MHz */
#define RZV_CLOCK_ETHRX1CLK_HZ        (125000000)   /* ETH1 RX 125MHz */
#define RZV_CLOCK_ET0_TXC_TXCLK_HZ   (125000000)   /* ETH0 TXC TX 125MHz */
#define RZV_CLOCK_ET0_RXC_RXCLK_HZ   (125000000)   /* ETH0 RXC RX 125MHz */
#define RZV_CLOCK_ET1_TXC_TXCLK_HZ   (125000000)   /* ETH1 TXC TX 125MHz */
#define RZV_CLOCK_ET1_RXC_RXCLK_HZ   (125000000)   /* ETH1 RXC RX 125MHz */


/* Clock extraction macros **************************************************/

#define RZV_CPG_DOMAIN(clk)         ((clk) >> 16)
#define RZV_CPG_BIT(clk)            ((clk) & 0xFFFF)

/* Module clock control macros **********************************************/
/* DEPRECATED: prefer rzv_clock_enable/disable and rzv_module_reset/unreset
 * C functions which add retry, diagnostics, and proper critical-section
 * handling.  These macros are kept for legacy boot-path only.
 * — RZV_MODULE_RSTOFF had compile-breaking typo
 * (RZV_CPG_RST_MON) and inverted wait condition; DELETED (see below).
 * — ARM_DSB() added after CLKON/RST write.
 */

/* Start clock supply to a module (boot-path fast path only).
 * Write includes write-enable bits [31:16]; poll CLKMON until bit set.
 * ARM_DSB() after poll ensures subsequent IP register writes are ordered. */
/* CLKMON packs 32 monitor bits per register with the same GLOBAL numbering
 * as the 16-bit-packed CLKON control registers (FSP bsp_override.h anchors:
 * SCI, GTM).  Monitor register/bit therefore derive from the global index
 * g = 16*domain + bit, NOT from the CLKON register index.
 */

#define RZV_CPG_CLKMON_REG(domain, bit)                                      \
  RZV_CPG_CLKMON((16u * (domain) + (bit)) / 32u)
#define RZV_CPG_CLKMON_BIT(domain, bit)                                      \
  (1u << ((16u * (domain) + (bit)) % 32u))

#define RZV_MODULE_CLKON(domain, bit)                                        \
  do {                                                                       \
    putreg32((1 << (bit)) | (1 << ((bit) + 16)),                           \
             RZV_CPG_CLKON(domain));                                         \
    while ((getreg32(RZV_CPG_CLKMON_REG(domain, bit)) &                      \
            RZV_CPG_CLKMON_BIT(domain, bit)) == 0)                           \
      {                                                                      \
      }                                                                      \
    ARM_DSB();                                                               \
  } while (0)

/* Stop clock supply to a module (boot-path fast path only). */
#define RZV_MODULE_CLKOFF(domain, bit)                                       \
  do {                                                                       \
    putreg32((1 << ((bit) + 16)), RZV_CPG_CLKON(domain));                  \
    while ((getreg32(RZV_CPG_CLKMON_REG(domain, bit)) &                      \
            RZV_CPG_CLKMON_BIT(domain, bit)) != 0)                           \
      {                                                                      \
      }                                                                      \
    ARM_DSB();                                                               \
  } while (0)

/* Assert reset (write-enable only, control=0 → reset asserted). */
#define RZV_MODULE_RSTON(domain, bit)                                        \
  do {                                                                       \
    putreg32((1 << ((bit) + 16)), RZV_CPG_RST(domain));                    \
    ARM_DSB();                                                               \
  } while (0)

/* RZV_MODULE_RSTOFF DELETED.
 * Was: referenced RZV_CPG_RST_MON (compile error; correct is RZV_CPG_RSTMON)
 * and polled "!= 0" (inverted; should be "== 0" for reset-asserted wait).
 * Use rzv_module_unreset() instead — it polls RSTMON correctly. */

/* Default clock frequencies ************************************************/
/* Prefer Kconfig overrides (CONFIG_RZV_CPU_CLOCK_HZ etc.) when provided.
 * — Kconfig overrides now consumed here.
 * High — hardcoded HZ used as fallback when divider readback not done.
 */

#ifndef RZV_MAIN_CLOCK_HZ
#  ifdef CONFIG_RZV_XTAL_FREQ
#    define RZV_MAIN_CLOCK_HZ       CONFIG_RZV_XTAL_FREQ
#  else
#    define RZV_MAIN_CLOCK_HZ       RZV_CLOCK_OSCCLK_HZ
#  endif
#endif

#ifndef RZV_PLL_CLOCK_HZ
#  define RZV_PLL_CLOCK_HZ          RZV_CLOCK_PLLCM33CLK_HZ
#endif

#ifndef RZV_CPU_CLOCK_HZ
#  ifdef CONFIG_RZV_CPU_CLOCK_HZ
#    define RZV_CPU_CLOCK_HZ        CONFIG_RZV_CPU_CLOCK_HZ
#  else
#    define RZV_CPU_CLOCK_HZ        RZV_CLOCK_I6CLK_HZ
#  endif
#endif

#ifndef RZV_PCLK_HZ
#  ifdef CONFIG_RZV_PCLK_0_HZ
#    define RZV_PCLK_HZ             CONFIG_RZV_PCLK_0_HZ
#  else
#    define RZV_PCLK_HZ             RZV_CLOCK_P0CLK_HZ
#  endif
#endif

/****************************************************************************
 * Public Types
 ****************************************************************************/

/*
 * Clock status structure - provides comprehensive clock state information
 */

struct rzv_clock_status_s
{
  bool enabled;          /* Clock is enabled */
  bool reset_asserted;   /* Reset is asserted (module held in reset) */
  uint32_t domain;       /* Clock domain number */
  uint32_t bit;          /* Bit position in domain */
};

/*
 * Clock tree frequency identifiers used to populate NuttX's view of the
 * clock tree.
 */

#define RZV_CLOCK_LIST(_)          \
	_(ICLK)                         \
	_(I0CLK)                        \
	_(I1CLK)                        \
	_(I2CLK)                        \
	_(I3CLK)                        \
	_(I4CLK)                        \
	_(I5CLK)                        \
	_(I6CLK)                        \
	_(I7CLK)                        \
	_(GCLK)                         \
	_(S0CLK)                        \
	_(S1CLK)                        \
	_(S2CLK)                        \
	_(S3CLK)                        \
	_(SPI0CLK)                      \
	_(SPI1CLK)                      \
	_(SPI2CLK)                      \
	_(SDCLK)                        \
	_(SD0CLK)                       \
	_(SD1CLK)                       \
	_(M0CLK)                        \
	_(M1CLK)                        \
	_(M2CLK)                        \
	_(M3CLK)                        \
	_(M4CLK)                        \
	_(M5CLK)                        \
	_(HPCLK)                        \
	_(TSUCLK)                       \
	_(ZTCLK)                        \
	_(P0CLK)                        \
	_(P1CLK)                        \
	_(P2CLK)                        \
	_(P3CLK)                        \
	_(P4CLK)                        \
	_(P5CLK)                        \
	_(P6CLK)                        \
	_(P7CLK)                        \
	_(P8CLK)                        \
	_(P9CLK)                        \
	_(P10CLK)                       \
	_(P11CLK)                       \
	_(P12CLK)                       \
	_(P13CLK)                       \
	_(P14CLK)                       \
	_(P15CLK)                       \
	_(ADCCLK)                       \
	_(ATCLK)                        \
	_(CANCLK)                       \
	_(CANFDCLK)                     \
	_(ETHTX0CLK)                    \
	_(ET0_TXC_TXCLK)               \
	_(ETHRX0CLK)                    \
	_(ET0_RXC_RXCLK)               \
	_(ETHTX1CLK)                    \
	_(ET1_TXC_TXCLK)               \
	_(ETHRX1CLK)                    \
	_(ET1_RXC_RXCLK)               \
	_(GPUCLK)                       \
	_(ISPCLK)                       \
	_(ISUCLK)                       \
	_(LPCLK)                        \
	_(OSCCLK)                       \
	_(OSC2CLK)                      \
	_(PLLCM33CLK)                   \
	_(PLLCLNCLK)                    \
	_(PLLDTYCLK)                    \
	_(PLLCA55CLK)                   \
	_(PLLDRPCLK)                    \
	_(PLLVDOCLK)                    \
	_(PLLETHCLK)                    \
	_(PLLDSICLK)                    \
	_(PLLGPUCLK)                    \
	_(PLLDDR0CLK)                   \
	_(PLLDDR1CLK)

enum rzv_clock_id_e
{
#define RZV_CLOCK_ENUM(name) RZV_CLOCK_##name,
	RZV_CLOCK_LIST(RZV_CLOCK_ENUM)
#undef RZV_CLOCK_ENUM
	RZV_CLOCK_MAX
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Name: rzv_clock_enable
 *
 * Description:
 *   Enable clock for a peripheral module
 *
 * Input Parameters:
 *   clk_id - Clock identifier (domain and bit)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure
 *
 ****************************************************************************/

int rzv_clock_enable(uint32_t clk_id);

/****************************************************************************
 * Name: rzv_clock_disable
 *
 * Description:
 *   Disable clock for a peripheral module
 *
 * Input Parameters:
 *   clk_id - Clock identifier (domain and bit)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure
 *
 ****************************************************************************/

int rzv_clock_disable(uint32_t clk_id);

/****************************************************************************
 * Name: rzv_module_reset
 *
 * Description:
 *   Assert reset for a peripheral module
 *
 * Input Parameters:
 *   clk_id - Module identifier (domain and bit)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure
 *
 ****************************************************************************/

int rzv_module_reset(uint32_t clk_id);

/****************************************************************************
 * Name: rzv_module_unreset
 *
 * Description:
 *   Deassert reset for a peripheral module
 *
 * Input Parameters:
 *   clk_id - Module identifier (domain and bit)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure
 *
 ****************************************************************************/

int rzv_module_unreset(uint32_t clk_id);

/****************************************************************************
 * Name: rzv_gpt_module_start
 *
 * Description:
 *   Start the GPT hardware unit containing a logical GPT channel.  The
 *   RZ/V2H CPG controls GPT0-7 and GPT10-17 as two shared units.
 *
 ****************************************************************************/

int rzv_gpt_module_start(unsigned int channel);

/****************************************************************************
 * Name: rzv_gpt_module_stop
 *
 * Description:
 *   Release a GPT channel user. The shared unit clock remains enabled, as
 *   required by the FSP GPT module-stop sequence.
 *
 ****************************************************************************/

int rzv_gpt_module_stop(unsigned int channel);

/****************************************************************************
 * Name: rzv_get_pclk_frequency
 *
 * Description:
 *   Get the peripheral clock frequency
 *
 * Returned Value:
 *   Peripheral clock frequency in Hz
 *
 ****************************************************************************/

uint32_t rzv_get_pclk_frequency(void);

/****************************************************************************
 * Name: rzv_get_cpu_frequency
 *
 * Description:
 *   Get the CPU clock frequency
 *
 * Returned Value:
 *   CPU clock frequency in Hz
 *
 ****************************************************************************/

uint32_t rzv_get_cpu_frequency(void);

/****************************************************************************
 * Name: rzv_get_p4clk_frequency
 *
 * Description:
 *   Get P4CLK frequency (200 MHz default).  Used by SPI and GPT peripherals.
 * rzv_get_pclk_frequency() only returns P0CLK (100 MHz);
 *   callers needing P4CLK must use this function instead.
 *
 * Returned Value:
 *   P4CLK frequency in Hz
 *
 ****************************************************************************/

uint32_t rzv_get_p4clk_frequency(void);

/****************************************************************************
 * Name: rzv_get_gpt_clock_hz
 *
 * Description:
 *   Return the clock frequency fed to the GPT prescaler (GTCR.TPCS divides
 *   this source).  On R9A09G057H the GPT clock source is P4CLK (200 MHz).
 *   GPT clock source is P4CLK (BSP_FEATURE_GPT_CLOCK_SOURCE).
 *   GPTCK is a separate optional source not used by default.
 *
 *   UNVERIFIED: Confirm against RZ/V2H UM Table 9.x if board clock tree
 *   differs from EVK default (BSP_CFG_CLOCK_P4CLK_HZ may vary).
 *
 * Returned Value:
 *   GPT input clock frequency in Hz (P4CLK = 200 MHz compile-time default,
 *   RZV_CLOCK_P4CLK_HZ).
 *
 ****************************************************************************/

uint32_t rzv_get_gpt_clock_hz(void);

/****************************************************************************
 * Name: rzv_clock_get_rate
 *
 * Description:
 *   Look up the frequency stored for a given clock tree node.  Values are
 *   populated from the BSP-generated configuration if available, otherwise
 *   reasonable defaults are used.
 */

uint32_t rzv_clock_get_rate(enum rzv_clock_id_e clock_id);

/****************************************************************************
 * Name: rzv_clock_get_name
 *
 * Description:
 *   Return a constant string for the requested clock identifier.  This is
 *   primarily intended for debug output.
 */

const char *rzv_clock_get_name(enum rzv_clock_id_e clock_id);

/****************************************************************************
 * Name: rzv_clock_set_lowpower_mode
 *
 * Description:\n *   Enable or disable low-power mode for a clock domain.
 *   In low-power mode, the clock may be gated when not actively used.
 *
 * Input Parameters:
 *   clk_id - Clock identifier (domain + bit encoded)
 *   enable - true to enable low-power mode, false to disable
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 ****************************************************************************/

int rzv_clock_set_lowpower_mode(uint32_t clk_id, bool enable);

/****************************************************************************
 * Name: rzv_clock_enable_monitoring
 *
 * Description:
 *   Enable clock monitoring to detect frequency anomalies and failures.
 *
 * Input Parameters:
 *   clock_id - Clock to monitor from rzv_clock_id_e enum
 *   enable   - true to enable monitoring, false to disable
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 ****************************************************************************/

int rzv_clock_enable_monitoring(enum rzv_clock_id_e clock_id, bool enable);

/****************************************************************************
 * Name: rzv_clock_set_frequency
 *
 * Description:
 *   Dynamically change clock frequency for power/performance optimization.
 *
 * Input Parameters:
 *   clock_id     - Clock to modify from rzv_clock_id_e enum
 *   frequency_hz - Target frequency in Hz
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 ****************************************************************************/

int rzv_clock_set_frequency(enum rzv_clock_id_e clock_id,
                            uint32_t frequency_hz);

/****************************************************************************
 * Name: rzv_clock_get_status
 *
 * Description:
 *   Get comprehensive status of a clock domain including enable state,
 *   reset state, domain, and bit position.
 *
 * Input Parameters:
 *   clk_id - Clock identifier (domain + bit encoded)
 *   status - Pointer to status structure to populate
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 ****************************************************************************/

int rzv_clock_get_status(uint32_t clk_id,
                         struct rzv_clock_status_s *status);

/*
 * Initialize early clock configuration for the SoC/board.  This is called
 * very early in the reset path to bring up essential clocks required for
 * serial output and other early peripherals.  Implementations may be
 * provided in board-specific or chip-specific files.
 */
void rzv_clock_config(void);

/****************************************************************************
 * Name: rzv_clock_enable_sdhi / rzv_reset_release_sdhi
 *
 * Description:
 *   Enable the SDHI module clock and release its reset for the given channel.
 *   Wraps rzv_clock_enable(RZV_CPG_CLK_SDHIn) and
 *        rzv_module_unreset(RZV_CPG_RST_SDHIn).
 *
 *   CPG IDs derived from FSP enum values:
 *     CPG_CLK_SDHI_0_IMCLK = 0x00080628 -> domain 14, bit 3
 *     CPG_RST_SDHI_0_IXRST = 0x00800928 -> domain 14, bit 7
 *   (NEEDS_VERIFY: confirm against RZ/V2H UM CPG chapter.)
 *
 * Input Parameters:
 *   ch - SDHI channel (0 = SD0, 1 = SD1, 2 = SD2)
 *
 * Returned Value:
 *   OK on success; negated errno on failure.
 *
 ****************************************************************************/

int rzv_clock_enable_sdhi(int ch);
int rzv_reset_release_sdhi(int ch);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RZV_CLOCK_H */

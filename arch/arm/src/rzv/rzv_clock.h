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

/* ARM_DSB() for barrier after CLKON/RST writes (audit Medium-8).
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
 * TODO(phase-01): validate each entry against RZ/V2H UM Table 9.x.
 * See audit finding Critical-2.
 */

/* CLKON_0 - GPIO, CA55 core clocks */
/* UNVERIFIED: GPIO channel 0; needs RZ/V2H UM confirmation */
#define RZV_CPG_CLK_GPIO            (0 << 16 | 0)
/* UNVERIFIED: ICU channel 0; needs RZ/V2H UM confirmation */
#define RZV_CPG_CLK_ICU             (0 << 16 | 1)

/* CLKON_11 - SCI_B (UART) channels 0-7
 * FSP bsp_clocks.c: CPG_CLKON_11 CLK8=SCI0..CLK15=SCI7
 * bsp_clocks.c:750 R_CPG->CPG_CLKON_11 CLK8_ON = SCI_B channel 0
 * UNVERIFIED: awaiting RZ/V2H UM cross-check */
#define RZV_CPG_CLK_SCI0            (11 << 16 | 8)
#define RZV_CPG_CLK_SCI1            (11 << 16 | 9)
#define RZV_CPG_CLK_SCI2            (11 << 16 | 10)
#define RZV_CPG_CLK_SCI3            (11 << 16 | 11)
#define RZV_CPG_CLK_SCI4            (11 << 16 | 12)
#define RZV_CPG_CLK_SCI5            (11 << 16 | 13)
#define RZV_CPG_CLK_SCI6            (11 << 16 | 14)
#define RZV_CPG_CLK_SCI7            (11 << 16 | 15)
/* CLKON_12 CLK0=SCI8, CLK1=SCI9
 * bsp_clocks.c:804,827 CPG_CLKON_12 CLK0_ON=SCI8, CLK1_ON=SCI9 */
#define RZV_CPG_CLK_SCI8            (12 << 16 | 0)
#define RZV_CPG_CLK_SCI9            (12 << 16 | 1)

/* SPI (RSPI/SPI_B) - UNVERIFIED: needs RZ/V2H UM confirmation */
#define RZV_CPG_CLK_SPI0            (2 << 16 | 0)
#define RZV_CPG_CLK_SPI1            (2 << 16 | 1)
#define RZV_CPG_CLK_SPI2            (2 << 16 | 2)

/* I2C (RIIC) - UNVERIFIED: needs RZ/V2H UM confirmation */
#define RZV_CPG_CLK_I2C0            (3 << 16 | 0)
#define RZV_CPG_CLK_I2C1            (3 << 16 | 1)
#define RZV_CPG_CLK_I2C2            (3 << 16 | 2)
#define RZV_CPG_CLK_I2C3            (3 << 16 | 3)

/* GPT timers - UNVERIFIED: needs RZ/V2H UM confirmation.
 * FSP bsp_clocks.h: BSP_CLKON_REG_FSP_IP_GPT → CPG_CLKON_GPT (named alias
 * not present in R9A09G057H iobitmask → numeric mapping TBD). */
#define RZV_CPG_CLK_GPT0            (4 << 16 | 0)
#define RZV_CPG_CLK_GPT1            (4 << 16 | 1)
#define RZV_CPG_CLK_GPT2            (4 << 16 | 2)
#define RZV_CPG_CLK_GPT3            (4 << 16 | 3)
#define RZV_CPG_CLK_GPT4            (4 << 16 | 4)
#define RZV_CPG_CLK_GPT5            (4 << 16 | 5)
#define RZV_CPG_CLK_GPT6            (4 << 16 | 6)
#define RZV_CPG_CLK_GPT7            (4 << 16 | 7)
/* GPT8 and GPT9 do NOT exist on R9A09G057H — phantom channels removed.
 * Logical driver channels 8-15 map to physical GPT10-17 (unit1).
 * GPT10-17 may share one CPG gate with unit0 or have a separate CLKON_N bit;
 * UNVERIFIED pending RZ/V2H UM. For now, use same domain 4 placeholder. */
#define RZV_CPG_CLK_GPT10           (4 << 16 | 8)
#define RZV_CPG_CLK_GPT11           (4 << 16 | 9)
#define RZV_CPG_CLK_GPT12           (4 << 16 | 10)
#define RZV_CPG_CLK_GPT13           (4 << 16 | 11)  /* UNVERIFIED — placeholder, needs RZ/V2H UM */
#define RZV_CPG_CLK_GPT14           (4 << 16 | 12)  /* UNVERIFIED — placeholder, needs RZ/V2H UM */
#define RZV_CPG_CLK_GPT15           (4 << 16 | 13)  /* UNVERIFIED — placeholder, needs RZ/V2H UM */
#define RZV_CPG_CLK_GPT16           (4 << 16 | 14)  /* UNVERIFIED — placeholder, needs RZ/V2H UM */
#define RZV_CPG_CLK_GPT17           (4 << 16 | 15)  /* UNVERIFIED — placeholder, needs RZ/V2H UM */

/* OSTM timers - UNVERIFIED: needs RZ/V2H UM confirmation.
 * GPT and OSTM likely share CPG_CLKON_4 but bit offsets unknown. */
#define RZV_CPG_CLK_OSTM0           (4 << 16 | 11)
#define RZV_CPG_CLK_OSTM1           (4 << 16 | 12)
#define RZV_CPG_CLK_OSTM2           (4 << 16 | 13)

/* GTM (General Timer Module) clocks.
 * FSP bsp_clocks.h line 92: BSP_CLKON_REG_FSP_IP_GTM → CPG_CLKON_GTM (single
 * register, all 8 GTM channels as bits 0-7).  The named alias CPG_CLKON_GTM
 * is NOT in R9A09G057H iobitmask (only in R9A07G054L).
 * UNVERIFIED: mapping to CPG_CLKON_N pending RZ/V2H UM verification.
 * Previous code erroneously aliased GTM0-2 to OSTM0-2 and put GTM3-7 in
 * domain 4 bits 11-15 (conflicting with OSTM entries above).
 * Corrected: GTM0-7 assigned to domain 5 (placeholder) pending verification.
 * TODO(phase-01): confirm CPG_CLKON_N register for GTM on R9A09G057H. */
#define RZV_CPG_CLK_GTM0            (5 << 16 | 0)
#define RZV_CPG_CLK_GTM1            (5 << 16 | 1)
#define RZV_CPG_CLK_GTM2            (5 << 16 | 2)
#define RZV_CPG_CLK_GTM3            (5 << 16 | 3)
#define RZV_CPG_CLK_GTM4            (5 << 16 | 4)
#define RZV_CPG_CLK_GTM5            (5 << 16 | 5)
#define RZV_CPG_CLK_GTM6            (5 << 16 | 6)
#define RZV_CPG_CLK_GTM7            (5 << 16 | 7)

/* DMAC_B - FSP bsp_override.h:1656-1660:
 *   BSP_CLKON_REG_FSP_IP_DMAC → R_CPG->CPG_CLKON_0 (domain 0)
 *   BSP_CLKON_BIT_FSP_IP_DMAC = 0x1FU << CLK0_ON_Pos(=0) → 5-bit mask [4:0]
 *   CLK0_ON_Pos = 0 per R9A09G057H cpg_iobitmask.h:719.
 * D2-fix: domain was 6 (wrong), must be 0 (CPG_CLKON_0).
 * The rzv_clock_enable/disable DMAC special-case uses 0x1F mask (5 units). */
#define RZV_CPG_CLK_DMAC            (0 << 16 | 0)   /* DMAC: CPG_CLKON_0 bits[4:0], 5-unit mask */

/* Legacy per-unit aliases (Phase 04 DMAC driver compatibility).
 * All resolve to the same CLKON entry — there is one gate for all DMAC. */
#define RZV_CPG_CLK_DMAC0           RZV_CPG_CLK_DMAC
#define RZV_CPG_CLK_DMAC1           RZV_CPG_CLK_DMAC
#define RZV_CPG_CLK_DMAC2           RZV_CPG_CLK_DMAC
#define RZV_CPG_CLK_DMAC3           RZV_CPG_CLK_DMAC

/* CANFD - UNVERIFIED: needs RZ/V2H UM confirmation */
#define RZV_CPG_CLK_CANFD           (7 << 16 | 0)
#define RZV_CPG_CLK_CAN0            RZV_CPG_CLK_CANFD  /* CAN0 shares CANFD gate */
#define RZV_CPG_CLK_CAN1            RZV_CPG_CLK_CANFD  /* CAN1 shares CANFD gate */

/* Ethernet (GBE) - UNVERIFIED: needs RZ/V2H UM confirmation
 *
 * TODO(rzv2h-eth-clocks): only the GBETH0 module gate is currently exposed.
 * The following additional CPG gate IDs must be added once the CPG_CLKON_N
 * register index and bit position for each are pulled from the RZ/V2H User's
 * Manual (cross-reference Renesas FSP bsp_clocks.h, search "ETH"/"GBE"):
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

/* ADC - FSP bsp_clocks.h line 479: 2-bit pair (3U << CLK0_ON_Pos)
 * UNVERIFIED: CPG_CLKON_N index for ADC on R9A09G057H. */
#define RZV_CPG_CLK_ADC0            (9 << 16 | 0)   /* ADC: 2-bit pair [1:0] */
#define RZV_CPG_CLK_ADC1            RZV_CPG_CLK_ADC0


/* Maximum values ***********************************************************/

#define RZV_CPG_MAX_CLKON     24    /* CLKON0-CLKON24 */
#define RZV_CPG_MAX_RST       17    /* RST0-RST17 */
#define RZV_CPG_MAX_RSTMON    8     /* RSTMON0-RSTMON8 */

/* Board-specific clock frequencies (Hz) ************************************/
/* These values are derived from the Renesas FSP clock configuration tool
 * for the RZ/V2H EVK board. Adjust these for your specific board/configuration.
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
 * audit: Critical-1 — RZV_MODULE_RSTOFF had compile-breaking typo
 * (RZV_CPG_RST_MON) and inverted wait condition; DELETED (see below).
 * audit: Medium-8 — ARM_DSB() added after CLKON/RST write.
 */

/* Start clock supply to a module (boot-path fast path only).
 * Write includes write-enable bits [31:16]; poll CLKMON until bit set.
 * ARM_DSB() after poll ensures subsequent IP register writes are ordered. */
#define RZV_MODULE_CLKON(domain, bit)                                        \
  do {                                                                       \
    putreg32((1 << (bit)) | (1 << ((bit) + 16)),                           \
             RZV_CPG_CLKON(domain));                                         \
    while ((getreg32(RZV_CPG_CLKMON(domain)) & (1 << (bit))) == 0)        \
      {                                                                      \
      }                                                                      \
    ARM_DSB();                                                               \
  } while (0)

/* Stop clock supply to a module (boot-path fast path only). */
#define RZV_MODULE_CLKOFF(domain, bit)                                       \
  do {                                                                       \
    putreg32((1 << ((bit) + 16)), RZV_CPG_CLKON(domain));                  \
    while ((getreg32(RZV_CPG_CLKMON(domain)) & (1 << (bit))) != 0)        \
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

/* RZV_MODULE_RSTOFF DELETED — audit Critical-1.
 * Was: referenced RZV_CPG_RST_MON (compile error; correct is RZV_CPG_RSTMON)
 * and polled "!= 0" (inverted; should be "== 0" for reset-asserted wait).
 * Use rzv_module_unreset() instead — it polls RSTMON correctly. */

/* Default clock frequencies ************************************************/
/* Prefer Kconfig overrides (CONFIG_RZV_CPU_CLOCK_HZ etc.) when provided.
 * audit: Low-14 — Kconfig overrides now consumed here.
 * audit: High — hardcoded HZ used as fallback when divider readback not done.
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
 * Clock tree frequency identifiers.  These align with the Renesas FSP
 * frequency table so the BSP-generated configuration headers can be used to
 * populate NuttX's view of the clock tree.
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
 *   audit finding #4: rzv_get_pclk_frequency() only returns P0CLK (100 MHz);
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
 *   FSP BSP_FEATURE_GPT_CLOCK_SOURCE = FSP_PRIV_CLOCK_P4CLK (bsp_feature.h
 *   line 146).  GPTCK is a separate optional source not used by default.
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

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RZV_CLOCK_H */

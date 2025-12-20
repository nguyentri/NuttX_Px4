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

/* Domain 0 - GPIO, ICU */
#define RZV_CPG_CLK_GPIO            (0 << 16 | 0)   /* GPIO clock */
#define RZV_CPG_CLK_ICU             (0 << 16 | 1)   /* ICU clock */

/* Domain 1 - SCI/UART */
#define RZV_CPG_CLK_SCI0            (1 << 16 | 0)   /* SCI0 clock */
#define RZV_CPG_CLK_SCI1            (1 << 16 | 1)   /* SCI1 clock */
#define RZV_CPG_CLK_SCI2            (1 << 16 | 2)   /* SCI2 clock */
#define RZV_CPG_CLK_SCI3            (1 << 16 | 3)   /* SCI3 clock */
#define RZV_CPG_CLK_SCI4            (1 << 16 | 4)   /* SCI4 clock */
#define RZV_CPG_CLK_SCI5            (1 << 16 | 5)   /* SCI5 clock */
#define RZV_CPG_CLK_SCI6            (1 << 16 | 6)   /* SCI6 clock */
#define RZV_CPG_CLK_SCI7            (1 << 16 | 7)   /* SCI7 clock */
#define RZV_CPG_CLK_SCI8            (1 << 16 | 8)   /* SCI8 clock */
#define RZV_CPG_CLK_SCI9            (1 << 16 | 9)   /* SCI9 clock */

/* Domain 2 - SPI */
#define RZV_CPG_CLK_SPI0            (2 << 16 | 0)   /* SPI0 clock */
#define RZV_CPG_CLK_SPI1            (2 << 16 | 1)   /* SPI1 clock */
#define RZV_CPG_CLK_SPI2            (2 << 16 | 2)   /* SPI2 clock */

/* Domain 3 - I2C */
#define RZV_CPG_CLK_I2C0            (3 << 16 | 0)   /* I2C0 clock */
#define RZV_CPG_CLK_I2C1            (3 << 16 | 1)   /* I2C1 clock */
#define RZV_CPG_CLK_I2C2            (3 << 16 | 2)   /* I2C2 clock */
#define RZV_CPG_CLK_I2C3            (3 << 16 | 3)   /* I2C3 clock */

/* Domain 4 - Timers */
#define RZV_CPG_CLK_GPT0            (4 << 16 | 0)   /* GPT0 clock */
#define RZV_CPG_CLK_GPT1            (4 << 16 | 1)   /* GPT1 clock */
#define RZV_CPG_CLK_GPT2            (4 << 16 | 2)   /* GPT2 clock */
#define RZV_CPG_CLK_GPT3            (4 << 16 | 3)   /* GPT3 clock */
#define RZV_CPG_CLK_GPT4            (4 << 16 | 4)   /* GPT4 clock */
#define RZV_CPG_CLK_GPT5            (4 << 16 | 5)   /* GPT5 clock */
#define RZV_CPG_CLK_GPT6            (4 << 16 | 6)   /* GPT6 clock */
#define RZV_CPG_CLK_GPT7            (4 << 16 | 7)   /* GPT7 clock */
#define RZV_CPG_CLK_OSTM0           (4 << 16 | 8)   /* OSTM0 clock */
#define RZV_CPG_CLK_OSTM1           (4 << 16 | 9)   /* OSTM1 clock */
#define RZV_CPG_CLK_OSTM2           (4 << 16 | 10)  /* OSTM2 clock */

/* GTM (OSTM) clocks - aliases for compatibility */
#define RZV_CPG_CLK_GTM0            RZV_CPG_CLK_OSTM0  /* GTM0 = OSTM0 */
#define RZV_CPG_CLK_GTM1            RZV_CPG_CLK_OSTM1  /* GTM1 = OSTM1 */
#define RZV_CPG_CLK_GTM2            RZV_CPG_CLK_OSTM2  /* GTM2 = OSTM2 */
#define RZV_CPG_CLK_GTM3            (4 << 16 | 11)     /* GTM3 clock */
#define RZV_CPG_CLK_GTM4            (4 << 16 | 12)     /* GTM4 clock */
#define RZV_CPG_CLK_GTM5            (4 << 16 | 13)     /* GTM5 clock */
#define RZV_CPG_CLK_GTM6            (4 << 16 | 14)     /* GTM6 clock */
#define RZV_CPG_CLK_GTM7            (4 << 16 | 15)     /* GTM7 clock */

/* Domain 5 - DMA */
#define RZV_CPG_CLK_DMAC0           (5 << 16 | 0)   /* DMAC0 clock */
#define RZV_CPG_CLK_DMAC1           (5 << 16 | 1)   /* DMAC1 clock */
#define RZV_CPG_CLK_DMAC2           (5 << 16 | 2)   /* DMAC2 clock */
#define RZV_CPG_CLK_DMAC3           (5 << 16 | 3)   /* DMAC3 clock */

/* Domain 6 - CAN */
#define RZV_CPG_CLK_CANFD           (6 << 16 | 0)   /* CANFD clock */
#define RZV_CPG_CLK_CAN0            (6 << 16 | 1)   /* CAN0 clock */
#define RZV_CPG_CLK_CAN1            (6 << 16 | 2)   /* CAN1 clock */

/* Domain 7 - Ethernet */
#define RZV_CPG_CLK_ETH0            (7 << 16 | 0)   /* Ethernet0 clock */

/* Domain 8 - ADC */
#define RZV_CPG_CLK_ADC0            (8 << 16 | 0)   /* ADC0 clock */
#define RZV_CPG_CLK_ADC1            (8 << 16 | 1)   /* ADC1 clock */


/* Maximum values ***********************************************************/

#define RZV_CPG_MAX_CLKON     24    /* CLKON0-CLKON24 */
#define RZV_CPG_MAX_RST       17    /* RST0-RST17 */

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
#define RZV_CLOCK_SDCLK_HZ            (800000000)   /* SD base 800MHz */

/* Communication clocks */
#define RZV_CLOCK_CANCLK_HZ           (80000000)    /* CAN 80MHz */
#define RZV_CLOCK_ADCCLK_HZ           (50000000)    /* ADC 50MHz */

/* Ethernet clocks */
#define RZV_CLOCK_ETHTX0CLK_HZ        (125000000)   /* ETH0 TX 125MHz */
#define RZV_CLOCK_ETHRX0CLK_HZ        (125000000)   /* ETH0 RX 125MHz */
#define RZV_CLOCK_ETHTX1CLK_HZ        (125000000)   /* ETH1 TX 125MHz */
#define RZV_CLOCK_ETHRX1CLK_HZ        (125000000)   /* ETH1 RX 125MHz */


/* Clock extraction macros **************************************************/

#define RZV_CPG_DOMAIN(clk)         ((clk) >> 16)
#define RZV_CPG_BIT(clk)            ((clk) & 0xFFFF)

/* Module clock control macros **********************************************/
/* These provide a NuttX-style interface to the CPG clock/reset registers  */

/* Start clock supply to a module */
#define RZV_MODULE_CLKON(domain, bit)                                        \
  do {                                                                       \
    putreg32((1 << (bit)) | (1 << ((bit) + 16)),                           \
             RZV_CPG_CLKON(domain));                                         \
    while ((getreg32(RZV_CPG_CLKMON(domain)) & (1 << (bit))) == 0);        \
  } while (0)

/* Stop clock supply to a module */
#define RZV_MODULE_CLKOFF(domain, bit)                                       \
  do {                                                                       \
    putreg32((1 << ((bit) + 16)), RZV_CPG_CLKON(domain));                  \
    while ((getreg32(RZV_CPG_CLKMON(domain)) & (1 << (bit))) != 0);        \
  } while (0)

/* Assert reset for a module */
#define RZV_MODULE_RSTON(domain, bit)                                        \
  do {                                                                       \
    putreg32((1 << ((bit) + 16)), RZV_CPG_RST(domain));                    \
  } while (0)

/* Deassert reset for a module */
#define RZV_MODULE_RSTOFF(domain, bit)                                       \
  do {                                                                       \
    putreg32((1 << (bit)) | (1 << ((bit) + 16)),                           \
             RZV_CPG_RST(domain));                                           \
    while ((getreg32(RZV_CPG_RST_MON(domain)) & (1 << (bit))) != 0);       \
  } while (0)

/* Default clock frequencies for backwards compatibility ********************/
/* These can be overridden by board configuration but should match hardware */

#ifndef RZV_MAIN_CLOCK_HZ
#  define RZV_MAIN_CLOCK_HZ         RZV_CLOCK_OSCCLK_HZ
#endif

#ifndef RZV_PLL_CLOCK_HZ
#  define RZV_PLL_CLOCK_HZ          RZV_CLOCK_PLLCM33CLK_HZ
#endif

#ifndef RZV_CPU_CLOCK_HZ
#  define RZV_CPU_CLOCK_HZ          RZV_CLOCK_I6CLK_HZ
#endif

#ifndef RZV_PCLK_HZ
#  define RZV_PCLK_HZ               RZV_CLOCK_P0CLK_HZ
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

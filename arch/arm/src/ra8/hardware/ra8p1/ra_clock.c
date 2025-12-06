/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_clock.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/syslog/syslog.h>
#include <arch/spinlock.h>

#include <arch/board/board.h>
#include <arch/irq.h>

#include "barriers.h"
#include "arm_internal.h"
#include "chip.h"

#include <ra_clock.h>
#include "hardware/ra_hardware.h"
#include "hardware/ra_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions (Private Definitions)
 ****************************************************************************/

/* BSP register unlock/lock keys */
#define RA_PRV_PRCR_KEY                        (0xA500U)
#define RA_PRV_PRCR_UNLOCK                     ((RA_PRV_PRCR_KEY) | 0x3U)
#define RA_PRV_PRCR_LOCK                       ((RA_PRV_PRCR_KEY) | 0x0U)

/* Clock frequencies based on BSP reference */
#define RA_HOCO_HZ                             CONFIG_RA_HOCO_FREQUENCY
#define RA_MOCO_FREQ_HZ                        CONFIG_RA_MOCO_FREQUENCY
#define RA_LOCO_FREQ_HZ                        CONFIG_RA_LOCO_FREQUENCY
#define RA_SUBCLOCK_FREQ_HZ                    0U  /* No subclock */

/* Peripheral clock control bit positions */
#define RA_PRV_PERIPHERAL_CLK_REQ_BIT_POS      (6U)
#define RA_PRV_PERIPHERAL_CLK_REQ_BIT_MASK     (1U << RA_PRV_PERIPHERAL_CLK_REQ_BIT_POS)
#define RA_PRV_PERIPHERAL_CLK_RDY_BIT_POS      (7U)
#define RA_PRV_PERIPHERAL_CLK_RDY_BIT_MASK     (1U << RA_PRV_PERIPHERAL_CLK_RDY_BIT_POS)

/* Flash wait states */
#define RA_PRV_ROM_ZERO_WAIT_CYCLES            (0U)
#define RA_PRV_ROM_ONE_WAIT_CYCLES             (1U)
#define RA_PRV_ROM_TWO_WAIT_CYCLES             (2U)
#define RA_PRV_ROM_THREE_WAIT_CYCLES           (3U)

/* SRAM wait states */
#define RA_PRV_SRAM_UNLOCK                     (0xA501U)
#define RA_PRV_SRAM_LOCK                       (0xA500U)
#define RA_PRV_SRAM_WAIT_CYCLES                (0U)  /* No wait states for RA8E1 at startup freq */

/* PLL source select - consolidated definition using CONFIG_RA_PLL_SOURCE */
#if (CONFIG_RA_PLL_SOURCE == RA_CLOCKS_SOURCE_CLOCK_HOCO)
#  define RA_PRV_PLSRCSEL                      (0)
#  define RA_PRV_PLL_USED                      (1)
#elif (CONFIG_RA_PLL_SOURCE == RA_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
#  define RA_PRV_PLSRCSEL                      (1)
#  define RA_PRV_PLL_USED                      (1)
#else
#  define RA_PRV_PLSRCSEL                      (0)
#  define RA_PRV_PLL_USED                      (0)
#endif

/* System clock divider calculations */
/* SCKDIVCR register format (RA8E1):
 * Bits 31-28: FCLK divider    Bits 27-24: ICLK divider    Bits 23-20: PCLKE divider
 * Bits 19-16: BCLK divider    Bits 15-12: PCLKA divider   Bits 11-8:  PCLKB divider
 * Bits 7-4:   PCLKC divider   Bits 3-0:   PCLKD divider
 * Expected value: 0x988a8998
 */
#define RA_PRV_STARTUP_SCKDIVCR_FCLK_BITS        ((CONFIG_RA_FCLK_DIV & 0xFU) << 28U)
#define RA_PRV_STARTUP_SCKDIVCR_ICLK_BITS        ((CONFIG_RA_ICK_DIV & 0xFU) << 24U)
#define RA_PRV_STARTUP_SCKDIVCR_PCLKE_BITS       ((CONFIG_RA_PCKE_DIV & 0xFU) << 20U)
#define RA_PRV_STARTUP_SCKDIVCR_BCLK_BITS        ((CONFIG_RA_BCLK_DIV & 0xFU) << 16U)
#define RA_PRV_STARTUP_SCKDIVCR_PCLKA_BITS       ((CONFIG_RA_PCKA_DIV & 0xFU) << 12U)
#define RA_PRV_STARTUP_SCKDIVCR_PCLKB_BITS       ((CONFIG_RA_PCKB_DIV & 0xFU) << 8U)
#define RA_PRV_STARTUP_SCKDIVCR_PCLKC_BITS       ((CONFIG_RA_PCKC_DIV & 0xFU) << 4U)
#define RA_PRV_STARTUP_SCKDIVCR_PCLKD_BITS       (CONFIG_RA_PCKD_DIV & 0xFU)
#define RA_PRV_STARTUP_SCKDIVCR                  (RA_PRV_STARTUP_SCKDIVCR_FCLK_BITS | \
                                                  RA_PRV_STARTUP_SCKDIVCR_ICLK_BITS | \
                                                  RA_PRV_STARTUP_SCKDIVCR_PCLKE_BITS | \
                                                  RA_PRV_STARTUP_SCKDIVCR_BCLK_BITS | \
                                                  RA_PRV_STARTUP_SCKDIVCR_PCLKA_BITS | \
                                                  RA_PRV_STARTUP_SCKDIVCR_PCLKB_BITS | \
                                                  RA_PRV_STARTUP_SCKDIVCR_PCLKC_BITS | \
                                                  RA_PRV_STARTUP_SCKDIVCR_PCLKD_BITS)

/* SCKDIVCR2 components for RA8P1 (CPUCLK, CPUCLK1, NPUCLK, MRICLK)
 * Note: CONFIG_RA_CPUCLK1_DIV, CONFIG_RA_NPUCLK_DIV, CONFIG_RA_MRICLK_DIV
 * defaults are defined in ra_clock.h to avoid duplication.
 */
#define RA_PRV_STARTUP_SCKDIVCR2_CPUCK_BITS      (CONFIG_RA_CPUCLK_DIV & 0xFU)
#define RA_PRV_STARTUP_SCKDIVCR2_CPUCK1_BITS     ((CONFIG_RA_CPUCLK1_DIV & 0xFU) << 4U)
#define RA_PRV_STARTUP_SCKDIVCR2_NPUCK_BITS      ((CONFIG_RA_NPUCLK_DIV & 0xFU) << 8U)
#define RA_PRV_STARTUP_SCKDIVCR2_MRICK_BITS      ((CONFIG_RA_MRICLK_DIV & 0xFU) << 12U)
#define RA_PRV_STARTUP_SCKDIVCR2                 (RA_PRV_STARTUP_SCKDIVCR2_CPUCK_BITS | \
                                                  RA_PRV_STARTUP_SCKDIVCR2_CPUCK1_BITS | \
                                                  RA_PRV_STARTUP_SCKDIVCR2_NPUCK_BITS | \
                                                  RA_PRV_STARTUP_SCKDIVCR2_MRICK_BITS)

#define RA_PRV_PLL2_MUL_CFG_MACRO_PLLMUL_MASK     (0x3FFU)
#define RA_PRV_PLL2_MUL_CFG_MACRO_PLLMULNF_MASK    (0x003U)
#define RA_PRV_PLL2CCR_PLLMULNF_BIT                (6) // PLLMULNF in PLLCCR starts at bit 6
#define RA_PRV_PLL2CCR_PLSRCSEL_BIT                (4) // PLSRCSEL in PLLCCR starts at bit 4
#if CONFIG_RA_PLL2_SOURCE == RA_CLOCKS_SOURCE_CLOCK_HOCO
#  define RA_PRV_PL2SRCSEL                         (0)
#elif CONFIG_RA_PLL2_SOURCE == RA_CLOCKS_SOURCE_CLOCK_MAIN_OSC
#  define RA_PRV_PL2SRCSEL                         (1)
#else
#  define RA_PRV_PL2SRCSEL                         (0)
#endif
#define RA_PRV_PLL2CCR                             ((((CONFIG_RA_PLL2_MUL & RA_PRV_PLL2_MUL_CFG_MACRO_PLLMUL_MASK) << \
                                                        RA_PRV_PLL2CCR_PLLMULNF_BIT) |                                \
                                                      (RA_PRV_PL2SRCSEL << RA_PRV_PLL2CCR_PLSRCSEL_BIT)) |          \
                                                      CONFIG_RA_PLL2_DIV)
#define RA_PRV_PLL2CCR2_PLL_DIV_MASK               (0x0F) // PLL DIV in PLL2CCR2 is 4 bits wide
#define RA_PRV_PLL2CCR2_PLL_DIV_Q_BIT              (4)    // PLL DIV Q in PLL2CCR2 starts at bit 4
#define RA_PRV_PLL2CCR2_PLL_DIV_R_BIT              (8)    // PLL DIV R in PLL2CCR2 starts at bit 8
#define RA_PRV_PLL2CCR2                            (((CONFIG_RA_PLL2R_DIV & RA_PRV_PLL2CCR2_PLL_DIV_MASK) << \
                                                      RA_PRV_PLL2CCR2_PLL_DIV_R_BIT) |                     \
                                                      ((CONFIG_RA_PLL2Q_DIV & RA_PRV_PLL2CCR2_PLL_DIV_MASK) << \
                                                      RA_PRV_PLL2CCR2_PLL_DIV_Q_BIT) |                     \
                                                      (CONFIG_RA_PLL2P_DIV & RA_PRV_PLL2CCR2_PLL_DIV_MASK))

/* PLL Control Register (PLLCCR) calculations
 * For RA8E1 (PLLCCR_TYPE 3), the PLL multiplier format is:
 * BSP_CLOCKS_PLL_MUL(X,Y) = ((X-1) << 2) | (Y/33), where Y is fractional part
 */
#define RA_PRV_PLL_MUL_CFG_MACRO_PLLMUL_MASK    (0x3FFU)
#define RA_PRV_PLLCCR_PLLMULNF_BIT               (6) // PLLMULNF in PLLCCR starts at bit 6
#define RA_PRV_PLLCCR_PLSRCSEL_BIT               (4) // PLSRCSEL in PLLCCR starts at bit 4
/* Note: RA_PRV_PLSRCSEL is defined above (lines 79-87) based on CONFIG_RA_PLL_SOURCE_* */
/* Convert PLL multiplier to format: BSP_CLOCKS_PLL_MUL(X,Y) = ((X-1) << 2) | (Y/33) */
#define RA_PRV_PLL_MUL_FORMAT                   ((((CONFIG_RA_PLL_MUL) - 1U) << 2UL) | 0U)
#define RA_PRV_PLLCCR                            ((((RA_PRV_PLL_MUL_FORMAT & RA_PRV_PLL_MUL_CFG_MACRO_PLLMUL_MASK) << \
                                                      RA_PRV_PLLCCR_PLLMULNF_BIT) |                               \
                                                    (RA_PRV_PLSRCSEL << RA_PRV_PLLCCR_PLSRCSEL_BIT)) |          \
                                                    CONFIG_RA_PLL_DIV)
#define RA_PRV_PLLCCR2_PLL_DIV_MASK              (0x0F) // PLL DIV in PLLCCR2/PLL2CCR2 is 4 bits wide
#define RA_PRV_PLLCCR2_PLL_DIV_Q_BIT             (4)    // PLL DIV Q in PLLCCR2/PLL2CCR2 starts at bit 4
#define RA_PRV_PLLCCR2_PLL_DIV_R_BIT             (8)    // PLL DIV R in PLLCCR2/PLL2CCR2 starts at bit 8
#define RA_PRV_PLLCCR2                           (((CONFIG_RA_PLL1R_DIV & RA_PRV_PLLCCR2_PLL_DIV_MASK) << \
                                                    RA_PRV_PLLCCR2_PLL_DIV_R_BIT) |                    \
                                                    ((CONFIG_RA_PLL1Q_DIV & RA_PRV_PLLCCR2_PLL_DIV_MASK) << \
                                                    RA_PRV_PLLCCR2_PLL_DIV_Q_BIT) |                    \
                                                    (CONFIG_RA_PLL1P_DIV & RA_PRV_PLLCCR2_PLL_DIV_MASK))

                                                 /* Key codes for MRAM registers. */
#define RA_PRV_MRCFREQ_KEY                      (0x1E000000)
#define RA_PRV_MREFREQ_KEY                      (0xE1000000)
#define RA_PRV_HZ_PER_MHZ                       (1000000)
#define RA_PRV_MRCPFB_LIMIT                     (0x65)
#define RA_PRV_MRFREQ_MIN_HZ                    (32768)

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* g_sys_core_clock variable */
uint32_t g_sys_core_clock = CONFIG_RA_HOCO_FREQUENCY;

/****************************************************************************
 * Private Data
 ****************************************************************************/

static ra_clock_config_t g_ra_clock_config;

/* Clock frequency array */
static uint32_t g_clock_freq[16];  /* Array size to accommodate all clock sources */

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static void ra_update_clock_config(void);

/****************************************************************************
 * Name: ra_sys_core_clock_update
 *
 * Description:
 *   Update the system core clock frequency based on the current clock settings
 *
 ****************************************************************************/

void ra_sys_core_clock_update (void)
{
  uint32_t clock_index = getreg8(R_SYSC_SCKSCR);
  uint8_t cpuck = (getreg8(R_SYSC_SCKDIVCR2) & R_SYSC_SCKDIVCR2_CPUCK_MASK) >> R_SYSC_SCKDIVCR2_CPUCK_SHIFT;
  uint8_t cpuclk_div = cpuck;

 /* Handle special divider cases first */
  if (8U == cpuclk_div)
    {
      g_sys_core_clock = g_clock_freq[clock_index] / 3U;
    }
  else if (9U == cpuclk_div)
    {
      g_sys_core_clock = g_clock_freq[clock_index] / 6U;
    }
  else if (10U == cpuclk_div)
    {
      g_sys_core_clock = g_clock_freq[clock_index] / 12U;
    }
  else if (11U == cpuclk_div)
    {
      g_sys_core_clock = g_clock_freq[clock_index] / 24U;
    }
  else
    {
      /* Standard power-of-2 dividers */
      g_sys_core_clock = g_clock_freq[clock_index] >> cpuclk_div;
    };
}

/****************************************************************************
 * Name: ra_clock_freq_var_init
 *
 * Description:
 *   Initialize clock frequency array
 *
 ****************************************************************************/

static void ra_clock_freq_var_init(void)
{
  g_clock_freq[RA_CLOCKS_SOURCE_CLOCK_HOCO]     = RA_HOCO_HZ;
  g_clock_freq[RA_CLOCKS_SOURCE_CLOCK_MOCO]     = RA_MOCO_FREQ_HZ;
  g_clock_freq[RA_CLOCKS_SOURCE_CLOCK_LOCO]     = RA_LOCO_FREQ_HZ;
  g_clock_freq[RA_CLOCKS_SOURCE_CLOCK_MAIN_OSC] = 0U;  /* Main OSC not populated */
  g_clock_freq[RA_CLOCKS_SOURCE_CLOCK_SUBCLOCK] = RA_SUBCLOCK_FREQ_HZ;
  g_clock_freq[RA_CLOCKS_SOURCE_CLOCK_PLL]      = RA_CFG_PLL1P_FREQUENCY_HZ;
  g_clock_freq[RA_CLOCKS_SOURCE_CLOCK_PLL1Q]    = RA_CFG_PLL1Q_FREQUENCY_HZ;
  g_clock_freq[RA_CLOCKS_SOURCE_CLOCK_PLL1R]    = RA_CFG_PLL1R_FREQUENCY_HZ;

  ra_sys_core_clock_update();
}

/****************************************************************************
 * Name: ra_peripheral_clock_set
 *
 * Description:
 *   Set peripheral clock source and divider
 *
 ****************************************************************************/

static void ra_peripheral_clock_set(volatile uint8_t *p_clk_ctrl_reg,
                                     volatile uint8_t *p_clk_div_reg,
                                     uint8_t peripheral_clk_div,
                                     uint8_t peripheral_clk_source)
{
  /* Request to stop the peripheral clock */
  *p_clk_ctrl_reg |= (uint8_t)RA_PRV_PERIPHERAL_CLK_REQ_BIT_MASK;

  /* Wait for the peripheral clock to stop */
  while (((*p_clk_ctrl_reg & RA_PRV_PERIPHERAL_CLK_RDY_BIT_MASK) >> RA_PRV_PERIPHERAL_CLK_RDY_BIT_POS) != 1U)
    {
      /* Wait for ready bit */
    }

  /* Select the peripheral clock divisor and source. Only write divider if provided */
  if (p_clk_div_reg != NULL)
    {
      *p_clk_div_reg = peripheral_clk_div;
    }

  *p_clk_ctrl_reg = peripheral_clk_source | RA_PRV_PERIPHERAL_CLK_REQ_BIT_MASK |
                    RA_PRV_PERIPHERAL_CLK_RDY_BIT_MASK;

  /* Request to start the peripheral clock */
  *p_clk_ctrl_reg &= (uint8_t)~RA_PRV_PERIPHERAL_CLK_REQ_BIT_MASK;

  /* Wait for the peripheral clock to start */
  while (((*p_clk_ctrl_reg & RA_PRV_PERIPHERAL_CLK_RDY_BIT_MASK) >> RA_PRV_PERIPHERAL_CLK_RDY_BIT_POS) != 0U)
    {
      /* Wait for ready bit to be clear */
    }
}

/****************************************************************************
 * Name: ra_peripheral_clock_init
 *
 * Description:
 *   Set clocks for configured peripherals (simplified for RA8E1)
 *
 ****************************************************************************/

static void ra_peripheral_clock_init(void)
{
  /* Initialize peripheral clocks based on BSP reference implementation */

  /* Set the SCI clock if SCI is enabled */
#if defined(CONFIG_RA_SCI) && defined(R_SYSC_SCICKCR)
  ra_peripheral_clock_set((volatile uint8_t *)R_SYSC_SCICKCR,
                          (volatile uint8_t *)R_SYSC_SCICKDIVCR,
                          CONFIG_RA_SCICLK_DIV,
                          CONFIG_RA_SCICLK_SOURCE);
#endif

  /* Set the SPI clock if SPI is enabled */
#if defined(CONFIG_RA_SPI) && defined(R_SYSC_SPICKCR)
  ra_peripheral_clock_set((volatile uint8_t *)R_SYSC_SPICKCR,
                          (volatile uint8_t *)R_SYSC_SPICKDIVCR,
                          CONFIG_RA_SPICLK_DIV,
                          CONFIG_RA_SPICLK_SOURCE);
#endif

  /* Set the CANFD clock if CAN is enabled */
#if defined(CONFIG_RA_CAN) && defined(R_SYSC_CANFDCKCR)
  ra_peripheral_clock_set((volatile uint8_t *)R_SYSC_CANFDCKCR,
                          (volatile uint8_t *)R_SYSC_CANFDCKDIVCR,
                          CONFIG_RA_CANFDCLK_DIV,
                          CONFIG_RA_CANFDCLK_SOURCE);
#endif

  /* Set the USB clock if USB is enabled */
#if defined(CONFIG_RA_USB) && defined(R_SYSC_USBCKCR)
  /* If the MCU provides a USB divider register, use it; otherwise pass NULL */
#ifdef R_SYSC_USBCKDIVCR
  ra_peripheral_clock_set((volatile uint8_t *)R_SYSC_USBCKCR,
                          (volatile uint8_t *)R_SYSC_USBCKDIVCR,
                          CONFIG_RA_USBCLK_DIV,
                          CONFIG_RA_USBCLK_SOURCE);
#else
  ra_peripheral_clock_set((volatile uint8_t *)R_SYSC_USBCKCR,
                          NULL,  /* No divider register for USB on some MCUs */
                          0,     /* No divider */
                          CONFIG_RA_USBCLK_SOURCE);
#endif
#endif

  /* Set the OCTASPI clock if OSPI is enabled */
#if defined(CONFIG_RA_OSPI) && defined(R_SYSC_OCTACKCR)
  ra_peripheral_clock_set((volatile uint8_t *)R_SYSC_OCTACKCR,
                          (volatile uint8_t *)R_SYSC_OCTACKDIVCR,
                          CONFIG_RA_OCTACLK_DIV,
                          CONFIG_RA_OCTACLK_SOURCE);
#endif

  /* Set the GPT clock if GPT is enabled */
#if defined(CONFIG_RA_GPT) && defined(R_SYSC_GPTCKCR)
  ra_peripheral_clock_set((volatile uint8_t *)R_SYSC_GPTCKCR,
                          (volatile uint8_t *)R_SYSC_GPTCKDIVCR,
                          CONFIG_RA_GPTCLK_DIV,
                          CONFIG_RA_GPTCLK_SOURCE);
#endif

  /* Set the I2C clock if I2C is enabled */
#if defined(CONFIG_RA_I2C) && defined(R_SYSC_IICCKCR)
  ra_peripheral_clock_set((volatile uint8_t *)R_SYSC_IICCKCR,
                          (volatile uint8_t *)R_SYSC_IICCKDIVCR,
                          CONFIG_RA_IICCLK_DIV,
                          CONFIG_RA_IICCLK_SOURCE);
#endif

  /* Set the ADC clock if ADC is enabled */
#if defined(CONFIG_RA_ADC) && defined(R_SYSC_ADCCKCR)
  ra_peripheral_clock_set((volatile uint8_t *)R_SYSC_ADCCKCR,
                          (volatile uint8_t *)R_SYSC_ADCCKDIVCR,
                          CONFIG_RA_ADCCLK_DIV,
                          CONFIG_RA_ADCCLK_SOURCE);
#endif

  /* Set the LCD clock if LCD is enabled */
#if defined(CONFIG_RA_LCD) && defined(R_SYSC_LCDCKCR)
  ra_peripheral_clock_set((volatile uint8_t *)R_SYSC_LCDCKCR,
                          (volatile uint8_t *)R_SYSC_LCDCKDIVCR,
                          RA_CFG_LCDCLK_DIV,
                          RA_CFG_LCDCLK_SOURCE);
#endif

  /* Set the I3C clock if I3C is enabled */
#if defined(CONFIG_RA_I3C) && defined(R_SYSC_I3CCKCR)
  ra_peripheral_clock_set((volatile uint8_t *)R_SYSC_I3CCKCR,
                          (volatile uint8_t *)R_SYSC_I3CCKDIVCR,
                          RA_CFG_I3CCLK_DIV,
                          RA_CFG_I3CCLK_SOURCE);
#endif

  /* Set the USB60 clock if USB60 is enabled */
#if defined(CONFIG_RA_USB60) && defined(R_SYSC_USB60CKCR)
  ra_peripheral_clock_set((volatile uint8_t *)R_SYSC_USB60CKCR,
                          (volatile uint8_t *)R_SYSC_USB60CKDIVCR,
                          RA_CFG_USB60CLK_DIV,
                          RA_CFG_USB60CLK_SOURCE);
#endif

  /* Set the ESW (Ethernet Switch) clock if ESW is enabled */
#if defined(CONFIG_RA_ESWM) && defined(R_SYSC_ESWCKCR)
  ra_peripheral_clock_set((volatile uint8_t *)R_SYSC_ESWCKCR,
                          (volatile uint8_t *)R_SYSC_ESWCKDIVCR,
                          CONFIG_RA_ESWCLK_DIV,
                          CONFIG_RA_ESWCLK_SOURCE);
#endif

  /* Set the ESWPHY clock if ESWPHY is enabled */
#if defined(CONFIG_RA_ESWPHY) && defined(R_SYSC_ESWPCKCR)
  ra_peripheral_clock_set((volatile uint8_t *)R_SYSC_ESWPCKCR,
                          (volatile uint8_t *)R_SYSC_ESWPCKDIVCR,
                          CONFIG_RA_ESWPHYCLK_DIV,
                          CONFIG_RA_ESWPHYCLK_SOURCE);
#endif

  /* Set the ETHPHY clock if ETHPHY is enabled */
#if defined(CONFIG_RA_ETHPHY) && defined(R_SYSC_ETHPCKCR)
  ra_peripheral_clock_set((volatile uint8_t *)R_SYSC_ETHPCKCR,
                          (volatile uint8_t *)R_SYSC_ETHPCKDIVCR,
                          CONFIG_RA_ETHPHYCLK_DIV,
                          CONFIG_RA_ETHPHYCLK_SOURCE);
#endif
}

/*******************************************************************************************************************//**
 * Name: ra_prv_lock_clear_pfb
 * Description:
 *   Clear MRAM PFB
 * Parameters:  none
 * Return:      none
 **********************************************************************************************************************/
static void ra_prv_lock_clear_pfb (void)
{
    /* Clear MRAM PFB */
    putreg8(0x00, R_MRAM_BASE + R_MRAM_MRCPFB_OFFSET);
    (void)getreg8(R_MRAM_BASE + R_MRAM_MRCPFB_OFFSET);
    (void)getreg8(R_MRAM_BASE + R_MRAM_MRCPFB_OFFSET);
    (void)getreg8(R_MRAM_BASE + R_MRAM_MRCPFB_OFFSET);
}

/*******************************************************************************************************************//**
 * Sets the wait states for MRAM.
 **********************************************************************************************************************/
static void ra_prv_set_wait_state_frequency (uint32_t mriclk_frequency_hz, uint32_t mrpclk_frequency_hz)
{
    uint32_t freq_mhz;

    /* Set Code MRAM wait states */
    if (mriclk_frequency_hz <= RA_PRV_MRFREQ_MIN_HZ)
    {
        /* When under the minimum set MRCFREQ to 0 */
        freq_mhz = 0;
    }
    else
    {
        /* Round up the result when converting to MHz */
        freq_mhz = (mriclk_frequency_hz + RA_PRV_HZ_PER_MHZ - 1) / RA_PRV_HZ_PER_MHZ;
    }

    /* Write MRCFREQ */
    while (freq_mhz != getreg32(R_MRAM_BASE + R_MRAM_MRCFREQ_OFFSET))
    {
        putreg32(RA_PRV_MRCFREQ_KEY | freq_mhz, R_MRAM_BASE + R_MRAM_MRCFREQ_OFFSET);
    }

    /* Set Extra MRAM wait states */
    if (mrpclk_frequency_hz <= RA_PRV_MRFREQ_MIN_HZ)
    {
        /* When under the minimum set MREFREQ to 0 */
        freq_mhz = 0;
    }
    else
    {
        /* Round up the result when converting to MHz */
        freq_mhz = (mrpclk_frequency_hz + RA_PRV_HZ_PER_MHZ - 1) / RA_PRV_HZ_PER_MHZ;
    }

    /* Write MREFREQ */
    while (freq_mhz != getreg32(R_MRAM_BASE + R_MRAM_MREFREQ_OFFSET))
    {
        putreg32(RA_PRV_MREFREQ_KEY | freq_mhz, R_MRAM_BASE + R_MRAM_MREFREQ_OFFSET);
    }
}


/****************************************************************************
 * Name: ra_prv_clock_set_hard_reset
 *
 * Description:
 *   Set clocks when coming from hard reset
 *
 ****************************************************************************/

static void ra_prv_clock_set_hard_reset(void)
{
  /* Set flash wait states for safe operation at startup frequency */
#if defined (R_FCACHE_FLWT)
  /* Set flash wait states for high frequency operation */
  putreg8(RA_PRV_ROM_TWO_WAIT_CYCLES, R_FCACHE_FLWT);
#endif

  /* Clear MRAM PFB */
  ra_prv_lock_clear_pfb();
  ra_prv_set_wait_state_frequency(
    RA_PRV_MRICLK_DIV_VALUE, RA_STARTUP_FCLK_HZ);

  /* Set system clock dividers with temporary safe values first */
  putreg32(RA_PRV_STARTUP_SCKDIVCR, R_SYSC_SCKDIVCR);
  putreg16(RA_PRV_STARTUP_SCKDIVCR2, R_SYSC_SCKDIVCR2);

  /* Set the system source clock */
  putreg8(RA_CFG_CLOCK_SOURCE, R_SYSC_SCKSCR);

  /* Wait for settling delay. */
  ra_sys_core_clock_update();
  up_udelay(RA_CFG_CLOCK_SETTLING_DELAY_US);

  /* Continue and set clock to actual target speed. */
  putreg16(RA_PRV_STARTUP_SCKDIVCR2, R_SYSC_SCKDIVCR2);
  putreg32(RA_PRV_STARTUP_SCKDIVCR, R_SYSC_SCKDIVCR);

  /* Wait for settling delay. */
  ra_sys_core_clock_update();
  up_udelay(RA_CFG_CLOCK_SETTLING_DELAY_US);

  /* Set the system source clock again */
  putreg8(RA_CFG_CLOCK_SOURCE, R_SYSC_SCKSCR);

  /* Update the CMSIS core clock variable so that it reflects the new ICLK frequency. */
  ra_sys_core_clock_update();

  /* Configure SRAM wait states if needed */
#ifdef R_SRAM_SRAMPRCR
  putreg16(RA_PRV_SRAM_UNLOCK, R_SRAM_SRAMPRCR);

  /* Execute data memory barrier before and after setting the wait states */
  ARM_DMB();
  putreg8(RA_PRV_SRAM_WAIT_CYCLES, R_SRAM_SRAMWTSC);
  ARM_DMB();

  putreg16(RA_PRV_SRAM_LOCK, R_SRAM_SRAMPRCR);
#endif
}

/****************************************************************************
 * Name: ra_clock_init
 *
 * Description:
 *   Initialize clocks
 *
 ****************************************************************************/

static void ra_clock_init(void)
{
  /* Unlock system registers */
  putreg16(RA_PRV_PRCR_UNLOCK, R_SYSC_PRCR_S);

  /* Initialize clock frequency variables */
  ra_clock_freq_var_init();


  /* If PLL source is main oscillator, enable and wait for MOSC stabilization */
#if defined(CONFIG_RA_PLL_SOURCE_MAIN_OSC)
  /* Configure main oscillator drive strength based on configured main OSC frequency */
#if CONFIG_RA_MAIN_OSC_FREQUENCY <= 8000000
  putreg8(R_SYSC_MOMCR_MODRV0_000, R_SYSC_MOMCR);
#elif CONFIG_RA_MAIN_OSC_FREQUENCY <= 24000000
  putreg8(R_SYSC_MOMCR_MODRV0_011, R_SYSC_MOMCR);
#else
  putreg8(R_SYSC_MOMCR_MODRV0_101, R_SYSC_MOMCR);
#endif

  /* Enable main oscillator (clear stop) */
  putreg8(0U, R_SYSC_MOSCCR);

  /* Set MOSC wait time (use a conservative short wait setting)
   * If longer stabilization is required, change the MSTS value accordingly.
   */
  putreg8(R_SYSC_MOSCWTCR_MSTS_0X1, R_SYSC_MOSCWTCR);

  /* Wait for main oscillator stabilization flag */
  RA_HARDWARE_WAIT((getreg8(R_SYSC_OSCSF) & R_SYSC_OSCSF_MOSCSF), R_SYSC_OSCSF_MOSCSF);
#endif /* CONFIG_RA_PLL_SOURCE_MAIN_OSC */

  /* Start HOCO if used */
#if defined(CONFIG_RA_CLOCK_HOCO)
  putreg8(0U, R_SYSC_HOCOCR);  /* Enable HOCO */
  /* Wait for HOCO to stabilize */
  RA_HARDWARE_WAIT((getreg8(R_SYSC_OSCSF) & R_SYSC_OSCSF_HOCOSF), R_SYSC_OSCSF_HOCOSF);
#endif

#if defined(CONFIG_RA_PLL_SOURCE_MAIN_OSC)
  /* Enable main oscillator (clear stop) */
  putreg8(0U, R_SYSC_MOSCCR);
  /* Wait for main oscillator stabilization flag */
  RA_HARDWARE_WAIT((getreg8(R_SYSC_OSCSF) & R_SYSC_OSCSF_MOSCSF), R_SYSC_OSCSF_MOSCSF);
#endif /* CONFIG_RA_PLL_SOURCE_MAIN_OSC */

  /* Voltage scaling: request higher VSCM before enabling PLLs and wait for transition */
#ifdef R_SYSC_VSCR
  putreg8(R_SYSC_VSCR_VSCM_001, R_SYSC_VSCR);
  /* Wait for transition complete */
  while ((getreg8(R_SYSC_VSCR) & R_SYSC_VSCR_VSCMTSF) != 0U)
    {
      /* spin */
    }
#endif

  /* Start PLL2 first (if PLL2 registers are present/configured) */
#ifdef R_SYSC_PLL2CCR
  putreg16((uint16_t)RA_PRV_PLL2CCR, R_SYSC_PLL2CCR);
  putreg16((uint16_t)RA_PRV_PLL2CCR2, R_SYSC_PLL2CCR2);
  putreg8(0U, R_SYSC_PLL2CR);  /* Enable PLL2 */
  /* Wait for PLL2 to stabilize if status bit exists */
#  if defined(R_SYSC_OSCSF) && defined(R_SYSC_OSCSF_PLL2SF)
  RA_HARDWARE_WAIT((getreg8(R_SYSC_OSCSF) & R_SYSC_OSCSF_PLL2SF), R_SYSC_OSCSF_PLL2SF);
#  endif
#endif

  /* Configure and start PLL1 */
  putreg16((uint16_t)RA_PRV_PLLCCR, R_SYSC_PLLCCR);
  putreg16((uint16_t)RA_PRV_PLLCCR2, R_SYSC_PLLCCR2);
  putreg8(0U, R_SYSC_PLLCR);  /* Enable PLL1 */
  /* Wait for PLL1 to stabilize */
  RA_HARDWARE_WAIT((getreg8(R_SYSC_OSCSF) & R_SYSC_OSCSF_PLLSF), R_SYSC_OSCSF_PLLSF);

  /* Step 5: Set clocks from hard reset state */
  ra_prv_clock_set_hard_reset();

  /* Step 6: Configure peripheral clocks */
  ra_peripheral_clock_init();

  /* Step 7: Lock system registers */
  putreg16(RA_PRV_PRCR_LOCK, R_SYSC_PRCR_S);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_clock
 *
 * Description:
 *   Called to initialize the RA.  This does whatever setup is needed to
 *   put the SoC in a usable state.  This includes the initialization of
 *   clocking using the settings in board.h.
 *
 ****************************************************************************/

void ra_clock(void)
{
  /* Use clock initialization sequence */
  ra_clock_init();

  /* Update internal clock configuration */
  ra_update_clock_config();
}

/****************************************************************************
 * Private Data
 ****************************************************************************/

static ra_clock_config_t g_ra_clock_config;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_update_clock_config
 *
 * Description:
 *   Update Clock configuration from hardware registers
 *
 ****************************************************************************/

static void ra_update_clock_config(void)
{
  uint32_t sckscr;
  uint32_t sckdivcr;
  uint32_t sckdivcr2;
  uint8_t clock_source;
  uint32_t source_freq;

  /* Read current clock source */
  sckscr = getreg8(R_SYSC_SCKSCR);
  clock_source = sckscr & R_SYSC_SCKSCR_CKSEL_MASK;

  /* Read clock dividers */
  sckdivcr = getreg32(R_SYSC_SCKDIVCR);
  sckdivcr2 = getreg16(R_SYSC_SCKDIVCR2);

  /* Update configuration structure */
  g_ra_clock_config.clock_source = clock_source;

  /* Determine source frequency based on clock source */
  switch (clock_source)
    {
      case 0: /* HOCO */
        source_freq = CONFIG_RA_HOCO_FREQUENCY;
        g_ra_clock_config.hoco_enabled = true;
        g_ra_clock_config.moco_enabled = false;
        g_ra_clock_config.pll_enabled = false;
        break;

      case 1: /* MOCO */
        source_freq = CONFIG_RA_MOCO_FREQUENCY;
        g_ra_clock_config.hoco_enabled = false;
        g_ra_clock_config.moco_enabled = true;
        g_ra_clock_config.pll_enabled = false;
        break;

      case 5: /* PLL1P */
        source_freq = RA_SYSTEM_CLOCK_FREQUENCY;
        g_ra_clock_config.hoco_enabled = false;
        g_ra_clock_config.moco_enabled = false;
        g_ra_clock_config.pll_enabled = true;
        break;

      default:
        source_freq = CONFIG_RA_HOCO_FREQUENCY;
        g_ra_clock_config.hoco_enabled = true;
        g_ra_clock_config.moco_enabled = false;
        g_ra_clock_config.pll_enabled = false;
        break;
    }

  /* Calculate CPU clock frequency (CPUCLK) */
  uint8_t cpu_div = sckdivcr2 & 0x0F;
  uint32_t cpu_divisor = RA_DIV_TO_DIVISOR(cpu_div);
  g_ra_clock_config.cpu_clock_freq = source_freq / cpu_divisor;
  g_ra_clock_config.system_clock_freq = g_ra_clock_config.cpu_clock_freq;

  /* Calculate peripheral clock frequencies from SCKDIVCR */
  uint8_t fclk_div = (sckdivcr >> 28) & 0x0F;
  uint8_t ick_div = (sckdivcr >> 24) & 0x0F;
  uint8_t pclke_div = (sckdivcr >> 20) & 0x0F;
  uint8_t bclk_div = (sckdivcr >> 16) & 0x0F;
  uint8_t pclka_div = (sckdivcr >> 12) & 0x0F;
  uint8_t pclkb_div = (sckdivcr >> 8) & 0x0F;
  uint8_t pclkc_div = (sckdivcr >> 4) & 0x0F;
  uint8_t pclkd_div = (sckdivcr >> 0) & 0x0F;

  g_ra_clock_config.fclk_freq = source_freq / RA_DIV_TO_DIVISOR(fclk_div);
  g_ra_clock_config.iclk_freq = source_freq / RA_DIV_TO_DIVISOR(ick_div);
  g_ra_clock_config.pclke_freq = source_freq / RA_DIV_TO_DIVISOR(pclke_div);
  g_ra_clock_config.bclk_freq = source_freq / RA_DIV_TO_DIVISOR(bclk_div);
  g_ra_clock_config.pclka_freq = source_freq / RA_DIV_TO_DIVISOR(pclka_div);
  g_ra_clock_config.pclkb_freq = source_freq / RA_DIV_TO_DIVISOR(pclkb_div);
  g_ra_clock_config.pclkc_freq = source_freq / RA_DIV_TO_DIVISOR(pclkc_div);
  g_ra_clock_config.pclkd_freq = source_freq / RA_DIV_TO_DIVISOR(pclkd_div);

  /* Calculate SCICLK frequency
   * Use predefined macro from ra_clock.h that calculates:
   * RA_PLL1P_FREQUENCY / RA_DIV_TO_DIVISOR(CONFIG_RA_SCICLK_DIV)
   */
  g_ra_clock_config.sciclk_freq = RA_SCICLK_FREQUENCY;

  g_ra_clock_config.hoco_frequency = RA_HOCO_FREQUENCY;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_get_clock_config
 *
 * Description:
 *   Get current clock configuration
 *
 ****************************************************************************/

void ra_get_clock_config(ra_clock_config_t *config)
{
  DEBUGASSERT(config != NULL);

  /* Update configuration from hardware */
  ra_update_clock_config();

  /* Copy to user structure */
  memcpy(config, &g_ra_clock_config, sizeof(ra_clock_config_t));
}

/****************************************************************************
 * Name: ra_print_clock_info
 *
 * Description:
 *   Print clock information for debugging
 *
 ****************************************************************************/

void ra_print_clock_info(void)
{
#ifdef CONFIG_DEBUG_INFO
  ra_clock_config_t config;

  ra_get_clock_config(&config);

  syslog(LOG_INFO, "Clock Configuration:\n");
  syslog(LOG_INFO, "  System Clock: %lu Hz\n", config.system_clock_freq);
  syslog(LOG_INFO, "  CPU Clock: %lu Hz\n", config.cpu_clock_freq);
  syslog(LOG_INFO, "  ICLK: %lu Hz\n", config.iclk_freq);
  syslog(LOG_INFO, "  PCLKA: %lu Hz\n", config.pclka_freq);
  syslog(LOG_INFO, "  PCLKB: %lu Hz\n", config.pclkb_freq);
  syslog(LOG_INFO, "  PCLKC: %lu Hz\n", config.pclkc_freq);
  syslog(LOG_INFO, "  PCLKD: %lu Hz\n", config.pclkd_freq);
  syslog(LOG_INFO, "  PCLKE: %lu Hz\n", config.pclke_freq);
  syslog(LOG_INFO, "  BCLK: %lu Hz\n", config.bclk_freq);
  syslog(LOG_INFO, "  FCLK: %lu Hz\n", config.fclk_freq);
  syslog(LOG_INFO, "  SCICLK: %lu Hz\n", config.sciclk_freq);
  syslog(LOG_INFO, "  Clock Source: %d\n", config.clock_source);
  syslog(LOG_INFO, "  HOCO: %s\n", config.hoco_enabled ? "Enabled" : "Disabled");
  syslog(LOG_INFO, "  MOCO: %s\n", config.moco_enabled ? "Enabled" : "Disabled");
  syslog(LOG_INFO, "  PLL: %s\n", config.pll_enabled ? "Enabled" : "Disabled");
#endif
}

/****************************************************************************
 * Name: ra_get_peripheral_clock
 *
 * Description:
 *   Get peripheral clock frequency
 *
 ****************************************************************************/

uint32_t ra_get_peripheral_clock(int peripheral_id)
{
  ra_clock_config_t config;
  uint32_t source_freq;
  uint8_t divider;

  ra_get_clock_config(&config);

  switch (peripheral_id)
    {
      case RA_PCLK_ICLK:        /* System clock (ICK) */
        return config.iclk_freq;

      case RA_PCLK_PCLKA:       /* Peripheral Clock A */
        return config.pclka_freq;

      case RA_PCLK_PCLKB:       /* Peripheral Clock B */
        return config.pclkb_freq;

      case RA_PCLK_PCLKC:       /* Peripheral Clock C */
        return config.pclkc_freq;

      case RA_PCLK_PCLKD:       /* Peripheral Clock D */
        return config.pclkd_freq;

      case RA_PCLK_PCLKE:       /* Peripheral Clock E */
        return config.pclke_freq;

      case RA_PCLK_BCLK:        /* External bus clock */
        return config.bclk_freq;

      case RA_PCLK_FCLK:        /* Flash interface clock */
        return config.fclk_freq;

      case RA_PCLK_SCICLK:      /* SCI clock */
        return config.sciclk_freq;

      case RA_PCLK_SPICLK:      /* SPI clock */
#if defined(R_SYSC_SPICKCR)
        source_freq = RA_SYSTEM_CLOCK_FREQUENCY;
        divider = getreg8(R_SYSC_SPICKDIVCR) & 0x0F;
        return source_freq / RA_DIV_TO_DIVISOR(divider);
#else
        return 0;
#endif

      case RA_PCLK_CANFDCLK:    /* CANFD clock */
#if defined(R_SYSC_CANFDCKCR)
        source_freq = RA_SYSTEM_CLOCK_FREQUENCY;
        divider = getreg8(R_SYSC_CANFDCKDIVCR) & 0x0F;
        return source_freq / RA_DIV_TO_DIVISOR(divider);
#else
        return 0;
#endif

      case RA_PCLK_GPTCLK:      /* GPT clock */
#if defined(R_SYSC_GPTCKCR)
        source_freq = RA_SYSTEM_CLOCK_FREQUENCY;
        divider = getreg8(R_SYSC_GPTCKDIVCR) & 0x0F;
        return source_freq / RA_DIV_TO_DIVISOR(divider);
#else
        return 0;
#endif

      case RA_PCLK_IICCLK:      /* IIC (I2C) clock - uses PCLKB on RA8P1 */
        return config.pclkb_freq;

      case RA_PCLK_ADCCLK:      /* ADC clock */
#if defined(R_SYSC_ADCCKCR)
        source_freq = RA_SYSTEM_CLOCK_FREQUENCY;
        divider = getreg8(R_SYSC_ADCCKDIVCR) & 0x0F;
        return source_freq / RA_DIV_TO_DIVISOR(divider);
#else
        return 0;
#endif

      case RA_PCLK_OCTACLK:     /* OSPI clock */
#if defined(R_SYSC_OCTACKCR)
        source_freq = RA_SYSTEM_CLOCK_FREQUENCY;
        divider = getreg8(R_SYSC_OCTACKDIVCR) & 0x0F;
        return source_freq / RA_DIV_TO_DIVISOR(divider);
#else
        return 0;
#endif

      case RA_PCLK_LCDCLK:      /* LCD clock */
#if defined(R_SYSC_LCDCKCR)
        /* LCD typically uses PLL2R, need to calculate from configured source */
        source_freq = RA_CFG_PLL2R_FREQUENCY_HZ;
        divider = getreg8(R_SYSC_LCDCKDIVCR) & 0x0F;
        return source_freq / RA_DIV_TO_DIVISOR(divider);
#else
        return 0;
#endif

      case RA_PCLK_I3CCLK:      /* I3C clock */
#if defined(R_SYSC_I3CCKCR)
        /* I3C typically uses PLL2Q, need to calculate from configured source */
        source_freq = RA_CFG_PLL2Q_FREQUENCY_HZ;
        divider = getreg8(R_SYSC_I3CCKDIVCR) & 0x0F;
        return source_freq / RA_DIV_TO_DIVISOR(divider);
#else
        return 0;
#endif

      case RA_PCLK_USB60CLK:    /* USB 60MHz clock */
#if defined(R_SYSC_USB60CKCR)
        /* USB60 typically uses PLL2R, need to calculate from configured source */
        source_freq = RA_CFG_PLL2R_FREQUENCY_HZ;
        divider = getreg8(R_SYSC_USB60CKDIVCR) & 0x0F;
        return source_freq / RA_DIV_TO_DIVISOR(divider);
#else
        return 0;
#endif

      case RA_PCLK_ESWCLK:      /* Ethernet Switch clock */
#if defined(R_SYSC_ESWCKCR)
        source_freq = RA_SYSTEM_CLOCK_FREQUENCY;
        divider = getreg8(R_SYSC_ESWCKDIVCR) & 0x0F;
        return source_freq / RA_DIV_TO_DIVISOR(divider);
#else
        return 0;
#endif

      case RA_PCLK_ESWPHYCLK:   /* Ethernet Switch PHY clock */
#if defined(R_SYSC_ESWPCKCR)
        source_freq = RA_SYSTEM_CLOCK_FREQUENCY;
        divider = getreg8(R_SYSC_ESWPCKDIVCR) & 0x0F;
        return source_freq / RA_DIV_TO_DIVISOR(divider);
#else
        return 0;
#endif

      case RA_PCLK_ETHPHYCLK:   /* Ethernet PHY clock */
#if defined(R_SYSC_ETHPCKCR)
        source_freq = RA_SYSTEM_CLOCK_FREQUENCY;
        divider = getreg8(R_SYSC_ETHPCKDIVCR) & 0x0F;
        return source_freq / RA_DIV_TO_DIVISOR(divider);
#else
        return 0;
#endif

      default:
        return config.system_clock_freq;
    }
}

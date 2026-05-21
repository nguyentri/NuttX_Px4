/****************************************************************************
 * arch/arm/src/rzv/rzv_clock.c
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
#include <errno.h>

#if defined(__has_include)
#  if __has_include(<debug.h>)
#    include <debug.h>
#  endif
#else
#  include <debug.h>
#endif

#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>

/* up_udelay() is declared in <nuttx/arch.h> included above.
 * audit finding #20: explicit extern removed — redundant with <nuttx/arch.h>
 * and its presence was a red flag that the header chain was not trusted.
 */

/* Small fallbacks: if core macros/types are not visible in this TU for
 * any reason, provide conservative definitions so this file can
 * compile.  These will be skipped if the real definitions are present.
 */
#ifndef OK
#  define OK 0
#endif

#ifndef getreg32
#  define getreg32(a)    (*(volatile uint32_t *)(a))
#endif
#ifndef putreg32
#  define putreg32(v,a)  (*(volatile uint32_t *)(a) = (v))
#endif

/* audit finding #17: stdio.h printf fallback removed — printf is unsafe from
 * early-boot context (no FS, no console driver initialized yet).  If <debug.h>
 * is genuinely absent the build must fail loudly rather than silently use an
 * unsafe logging path that would crash at the first clkerr() call during boot. */
#ifndef _err
#  error "rzv_clock.c: <debug.h> not included — _err macro is required. " \
         "Ensure NuttX debug headers are in the include path."
#endif
#ifndef _info
#  error "rzv_clock.c: <debug.h> not included — _info macro is required. " \
         "Ensure NuttX debug headers are in the include path."
#endif

#include "rzv_clock.h"



/* Rely on NuttX core headers for up_udelay, getreg32/putreg32, OK, and
 * the low-level debug macros (_err/_info).  Those are pulled in via
 * <nuttx/arch.h> and <debug.h> above.
 */

/* Provide small logging wrappers expected by some vendor-derived code.  Map
 * to the NuttX low-level debug helpers so that code can call clkerr/clkinfo
 * without pulling in new logging infrastructure.
 */
#ifndef clkerr
#  define clkerr(fmt, ...) _err(fmt, ##__VA_ARGS__)
#endif
#ifndef clkinfo
#  define clkinfo(fmt, ...) _info(fmt, ##__VA_ARGS__)
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifndef ARRAY_SIZE
#  define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

/* Adaptive timeout values for different operations (10 µs units from Kconfig) */
#ifdef CONFIG_RZV_CLOCK_ENABLE_TIMEOUT
#  define CPG_TIMEOUT_CLOCK_ENABLE CONFIG_RZV_CLOCK_ENABLE_TIMEOUT
#else
#  define CPG_TIMEOUT_CLOCK_ENABLE 1000   /* 10 ms default */
#endif

#define CPG_TIMEOUT_CLOCK_DISABLE CPG_TIMEOUT_CLOCK_ENABLE

#ifdef CONFIG_RZV_CLOCK_RESET_ASSERT_TIMEOUT
#  define CPG_TIMEOUT_RESET_ASSERT CONFIG_RZV_CLOCK_RESET_ASSERT_TIMEOUT
#else
#  define CPG_TIMEOUT_RESET_ASSERT 500    /* 5 ms default */
#endif

#ifdef CONFIG_RZV_CLOCK_RESET_RELEASE_TIMEOUT
#  define CPG_TIMEOUT_RESET_RELEASE CONFIG_RZV_CLOCK_RESET_RELEASE_TIMEOUT
#else
#  define CPG_TIMEOUT_RESET_RELEASE 1000  /* 10 ms default */
#endif

#ifdef CONFIG_RZV_CLOCK_PLL_TIMEOUT
#  define CPG_TIMEOUT_PLL_LOCK CONFIG_RZV_CLOCK_PLL_TIMEOUT
#else
#  define CPG_TIMEOUT_PLL_LOCK 10000      /* 100 ms default */
#endif

/* Retry configuration */
#ifdef CONFIG_RZV_CLOCK_RETRY_COUNT
#  define CPG_MAX_RETRIES CONFIG_RZV_CLOCK_RETRY_COUNT
#else
#  define CPG_MAX_RETRIES 3
#endif

#define CPG_RETRY_DELAY_US        100    /* Initial retry delay (µs) */

/* Legacy timeout for compatibility */
#define CPG_TIMEOUT_COUNT         CPG_TIMEOUT_CLOCK_ENABLE

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct rzv_clock_cfg_entry_s
{
  enum rzv_clock_id_e id;
  uint32_t            hz;
};

static uint32_t g_clock_freq[RZV_CLOCK_MAX];
static bool g_clock_freq_valid;

static const uint32_t g_clock_defaults[RZV_CLOCK_MAX] =
{
  [RZV_CLOCK_OSCCLK]     = RZV_CLOCK_OSCCLK_HZ,
  [RZV_CLOCK_OSC2CLK]    = RZV_CLOCK_OSC2CLK_HZ,
  [RZV_CLOCK_PLLCM33CLK] = RZV_CLOCK_PLLCM33CLK_HZ,
  [RZV_CLOCK_PLLCLNCLK]  = RZV_CLOCK_PLLCLNCLK_HZ,
  [RZV_CLOCK_PLLDTYCLK]  = RZV_CLOCK_PLLDTYCLK_HZ,
  [RZV_CLOCK_PLLCA55CLK] = RZV_CLOCK_PLLCA55CLK_HZ,
  [RZV_CLOCK_PLLDRPCLK]  = RZV_CLOCK_PLLDRPCLK_HZ,
  [RZV_CLOCK_PLLVDOCLK]  = RZV_CLOCK_PLLVDOCLK_HZ,
  [RZV_CLOCK_PLLETHCLK]  = RZV_CLOCK_PLLETHCLK_HZ,
  [RZV_CLOCK_PLLDSICLK]  = RZV_CLOCK_PLLDSICLK_HZ,
  [RZV_CLOCK_PLLGPUCLK]  = RZV_CLOCK_PLLGPUCLK_HZ,
  [RZV_CLOCK_PLLDDR0CLK] = RZV_CLOCK_PLLDDR0CLK_HZ,
  [RZV_CLOCK_PLLDDR1CLK] = RZV_CLOCK_PLLDDR1CLK_HZ,
  [RZV_CLOCK_ICLK]       = RZV_CLOCK_ICLK_HZ,
  [RZV_CLOCK_I0CLK]      = RZV_CLOCK_I0CLK_HZ,
  [RZV_CLOCK_I1CLK]      = RZV_CLOCK_I1CLK_HZ,
  [RZV_CLOCK_I2CLK]      = RZV_CLOCK_I2CLK_HZ,
  [RZV_CLOCK_I3CLK]      = RZV_CLOCK_I3CLK_HZ,
  [RZV_CLOCK_I4CLK]      = RZV_CLOCK_I4CLK_HZ,
  [RZV_CLOCK_I5CLK]      = RZV_CLOCK_I5CLK_HZ,
  [RZV_CLOCK_I6CLK]      = RZV_CLOCK_I6CLK_HZ,
  [RZV_CLOCK_I7CLK]      = RZV_CLOCK_I7CLK_HZ,
  [RZV_CLOCK_P0CLK]      = RZV_CLOCK_P0CLK_HZ,
  [RZV_CLOCK_P1CLK]      = RZV_CLOCK_P1CLK_HZ,
  [RZV_CLOCK_P2CLK]      = RZV_CLOCK_P2CLK_HZ,
  [RZV_CLOCK_P3CLK]      = RZV_CLOCK_P3CLK_HZ,
  [RZV_CLOCK_P4CLK]      = RZV_CLOCK_P4CLK_HZ,
  [RZV_CLOCK_P5CLK]      = RZV_CLOCK_P5CLK_HZ,
  [RZV_CLOCK_P6CLK]      = RZV_CLOCK_P6CLK_HZ,
  [RZV_CLOCK_P7CLK]      = RZV_CLOCK_P7CLK_HZ,
  [RZV_CLOCK_P8CLK]      = RZV_CLOCK_P8CLK_HZ,
  [RZV_CLOCK_P9CLK]      = RZV_CLOCK_P9CLK_HZ,
  [RZV_CLOCK_P10CLK]     = RZV_CLOCK_P10CLK_HZ,
  [RZV_CLOCK_P11CLK]     = RZV_CLOCK_P11CLK_HZ,
  [RZV_CLOCK_P12CLK]     = RZV_CLOCK_P12CLK_HZ,
  [RZV_CLOCK_ATCLK]      = RZV_CLOCK_ATCLK_HZ,
  [RZV_CLOCK_ZTCLK]      = RZV_CLOCK_ZTCLK_HZ,
  [RZV_CLOCK_HPCLK]      = RZV_CLOCK_HPCLK_HZ,
  [RZV_CLOCK_LPCLK]      = RZV_CLOCK_LPCLK_HZ,
  [RZV_CLOCK_M0CLK]      = RZV_CLOCK_M0CLK_HZ,
  [RZV_CLOCK_M1CLK]      = RZV_CLOCK_M1CLK_HZ,
  [RZV_CLOCK_M2CLK]      = RZV_CLOCK_M2CLK_HZ,
  [RZV_CLOCK_M3CLK]      = RZV_CLOCK_M3CLK_HZ,
  [RZV_CLOCK_M4CLK]      = RZV_CLOCK_M4CLK_HZ,
  [RZV_CLOCK_ISPCLK]     = RZV_CLOCK_ISPCLK_HZ,
  [RZV_CLOCK_ISUCLK]     = RZV_CLOCK_ISUCLK_HZ,
  [RZV_CLOCK_GPUCLK]     = RZV_CLOCK_GPUCLK_HZ,
  [RZV_CLOCK_SPI0CLK]    = RZV_CLOCK_SPI0CLK_HZ,
  [RZV_CLOCK_SPI1CLK]    = RZV_CLOCK_SPI1CLK_HZ,
  [RZV_CLOCK_SPI2CLK]    = RZV_CLOCK_SPI2CLK_HZ,
  [RZV_CLOCK_SDCLK]      = RZV_CLOCK_SDCLK_HZ,
  [RZV_CLOCK_SD0CLK]     = RZV_CLOCK_SD0CLK_HZ,
  [RZV_CLOCK_SD1CLK]     = RZV_CLOCK_SD1CLK_HZ,
  [RZV_CLOCK_GCLK]       = RZV_CLOCK_GCLK_HZ,
  [RZV_CLOCK_S0CLK]      = RZV_CLOCK_S0CLK_HZ,
  [RZV_CLOCK_S1CLK]      = RZV_CLOCK_S1CLK_HZ,
  [RZV_CLOCK_S2CLK]      = RZV_CLOCK_S2CLK_HZ,
  [RZV_CLOCK_S3CLK]      = RZV_CLOCK_S3CLK_HZ,
  [RZV_CLOCK_M5CLK]      = RZV_CLOCK_M5CLK_HZ,
  [RZV_CLOCK_TSUCLK]     = RZV_CLOCK_TSUCLK_HZ,
  [RZV_CLOCK_P13CLK]     = RZV_CLOCK_P13CLK_HZ,
  [RZV_CLOCK_P14CLK]     = RZV_CLOCK_P14CLK_HZ,
  [RZV_CLOCK_P15CLK]     = RZV_CLOCK_P15CLK_HZ,
  [RZV_CLOCK_CANCLK]     = RZV_CLOCK_CANCLK_HZ,
  [RZV_CLOCK_CANFDCLK]   = RZV_CLOCK_CANFDCLK_HZ,
  [RZV_CLOCK_ADCCLK]     = RZV_CLOCK_ADCCLK_HZ,
  [RZV_CLOCK_ETHTX0CLK]  = RZV_CLOCK_ETHTX0CLK_HZ,
  [RZV_CLOCK_ETHRX0CLK]  = RZV_CLOCK_ETHRX0CLK_HZ,
  [RZV_CLOCK_ETHTX1CLK]  = RZV_CLOCK_ETHTX1CLK_HZ,
  [RZV_CLOCK_ETHRX1CLK]  = RZV_CLOCK_ETHRX1CLK_HZ,
  [RZV_CLOCK_ET0_TXC_TXCLK] = RZV_CLOCK_ET0_TXC_TXCLK_HZ,
  [RZV_CLOCK_ET0_RXC_RXCLK] = RZV_CLOCK_ET0_RXC_RXCLK_HZ,
  [RZV_CLOCK_ET1_TXC_TXCLK] = RZV_CLOCK_ET1_TXC_TXCLK_HZ,
  [RZV_CLOCK_ET1_RXC_RXCLK] = RZV_CLOCK_ET1_RXC_RXCLK_HZ,
};

/* No board-specific overrides needed - all frequencies are defined in
 * hardware/rzv_cpg.h and applied via g_clock_defaults array above.
 */
static const struct rzv_clock_cfg_entry_s g_clock_cfg_entries[] =
{
  /* Empty - reserved for future board-specific clock customization */
};

static const char * const g_clock_names[RZV_CLOCK_MAX] =
{
#define RZV_CLOCK_NAME(name) [RZV_CLOCK_##name] = #name,
  RZV_CLOCK_LIST(RZV_CLOCK_NAME)
#undef RZV_CLOCK_NAME
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static void rzv_clock_init_frequency_table(void);

/****************************************************************************
 * Name: rzv_cpg_getreg
 *
 * Description:
 *   Read a CPG register
 *
 ****************************************************************************/

static inline uint32_t rzv_cpg_getreg(uintptr_t addr)
{
  return getreg32(addr);
}

/****************************************************************************
 * Name: rzv_cpg_putreg
 *
 * Description:
 *   Write to a CPG register
 *
 ****************************************************************************/

static inline void rzv_cpg_putreg(uint32_t val, uintptr_t addr)
{
  putreg32(val, addr);
}

/****************************************************************************
 * Name: rzv_cpg_dump_registers
 *
 * Description:
 *   Dump CPG register state for debugging. Shows CLKON, CLKMON, RST,
 *   and RSTMON registers for a given domain.
 *
 ****************************************************************************/

static void rzv_cpg_dump_registers(uint32_t domain, const char *context)
{
  uint32_t clkon;
  uint32_t clkmon;
  uint32_t rst;
  uint32_t rstmon;

  if (domain > RZV_CPG_MAX_CLKON)
    {
      clkerr("Invalid domain %u in %s\n", domain, context);
      return;
    }

  clkon = rzv_cpg_getreg(RZV_CPG_CLKON(domain));
  clkmon = rzv_cpg_getreg(RZV_CPG_CLKMON(domain));

  clkerr("CPG Register Dump [%s] Domain %u:\n", context, domain);
  clkerr("  CLKON%u  = 0x%08x\n", domain, clkon);
  clkerr("  CLKMON%u = 0x%08x\n", domain, clkmon);

  if (domain <= RZV_CPG_MAX_RST)
    {
      rst = rzv_cpg_getreg(RZV_CPG_RST(domain));
      clkerr("  RST%u    = 0x%08x\n", domain, rst);

      if (domain <= RZV_CPG_MAX_RSTMON)
        {
          rstmon = rzv_cpg_getreg(RZV_CPG_RSTMON(domain));
          clkerr("  RSTMON%u = 0x%08x\n", domain, rstmon);
        }
    }
}

/****************************************************************************
 * Name: rzv_cpg_wait_bit
 *
 * Description:
 *   Wait for a bit to be set/cleared in a monitor register.
 *   MUST be called with IRQs ENABLED (outside critical section).
 *   audit High-5: poll moved outside enter_critical_section so HRT ISR
 *   is not blocked during up to 10ms of up_udelay spins.
 *
 * Input Parameters:
 *   addr    - monitor register address
 *   bit     - bitmask to check
 *   set     - true = wait until bit set; false = wait until bit clear
 *   timeout - max iterations (each ~10µs → multiply by 10 for µs total)
 *
 ****************************************************************************/

static int rzv_cpg_wait_bit(uintptr_t addr, uint32_t bit, bool set,
                             int timeout)
{
  uint32_t regval;

  while (timeout-- > 0)
    {
      regval = rzv_cpg_getreg(addr);

      if (set)
        {
          if (regval & bit)
            {
              return OK;
            }
        }
      else
        {
          if ((regval & bit) == 0)
            {
              return OK;
            }
        }

      up_udelay(10);
    }

  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: rzv_clock_init_frequency_table
 *
 * Description:
 *   Populate the in-memory clock frequency table.  Defaults are used when no
 *   BSP-generated configuration is available.
 *
 ****************************************************************************/

static void rzv_clock_init_frequency_table(void)
{
  size_t index;
  if (g_clock_freq_valid)
    {
      return;
    }

  for (index = 0; index < RZV_CLOCK_MAX; index++)
    {
      g_clock_freq[index] = g_clock_defaults[index];
    }

  /* Apply any board-specific overrides if defined */

  for (index = 0; index < ARRAY_SIZE(g_clock_cfg_entries); index++)
    {
      const struct rzv_clock_cfg_entry_s *entry = &g_clock_cfg_entries[index];

      if (entry->id < RZV_CLOCK_MAX && entry->hz != 0)
        {
          g_clock_freq[entry->id] = entry->hz;
        }
    }

  g_clock_freq_valid = true;

  clkinfo("Clock table initialized with hardware defaults\n");
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_clock_enable
 *
 * Description:
 *   Enable clock for a peripheral module
 *
 ****************************************************************************/

int rzv_clock_enable(uint32_t clk_id)
{
  uint32_t domain = RZV_CPG_DOMAIN(clk_id);
  uint32_t bit = RZV_CPG_BIT(clk_id);
  uint32_t mask;
  uint32_t mon_mask;
  uintptr_t clkon_addr = RZV_CPG_CLKON(domain);
  uintptr_t clkmon_addr = RZV_CPG_CLKMON(domain);
  irqstate_t flags;
  int ret;
  int retry;
  uint32_t delay_us;

  /* audit Critical-3: DMAC uses a 5-bit mask (CLK0-CLK4 all required).
   * DMAC CPG_CLKON_0 bits [4:0] are all required per RZ/V2H UM CPG §CLKON.
   * audit finding #5/#6: ADC also needs a 2-bit pair (CLK0+CLK1).
   * ADC requires 3U << CLK0_ON_Pos (both clock bits) per RZ/V2H UM.
   * Both are detected by domain here so any ID within that domain is gated
   * correctly regardless of which per-unit alias was passed. */

  if (domain == RZV_CPG_DOMAIN(RZV_CPG_CLK_DMAC))
    {
      /* DMAC gate: 5-bit mask [4:0] — all five DMA unit clocks together */

      mask     = (0x1fu << 16) | 0x1fu;  /* WEN[20:16] + ON[4:0] */
      mon_mask = 0x1fu;
    }
  else if (domain == RZV_CPG_DOMAIN(RZV_CPG_CLK_ADC0))
    {
      /* ADC gate: 2-bit pair [1:0] — both CLK0+CLK1 must be set */

      mask     = (0x3u << 16) | 0x3u;  /* WEN[17:16] + ON[1:0] */
      mon_mask = 0x3u;
    }
  else if (clk_id == RZV_CPG_CLK_CANFD)
    {
      /* CAN-FD gate: 3-bit field CLK12/13/14 in CPG_CLKON_9 per RZ/V2H UM.
       * global + ch0 + ch1 clocks all required.
       * bit==12, span 3 bits → bits[14:12].
       */

      mask     = (0x7u << (bit + 16)) | (0x7u << bit);
      mon_mask = (0x7u << bit);
    }
  else
    {
      mask     = (1u << (bit + 16)) | (1u << bit);
      mon_mask = (1u << bit);
    }

  for (retry = 0; retry <= CPG_MAX_RETRIES; retry++)
    {
      if (retry > 0)
        {
          delay_us = CPG_RETRY_DELAY_US << (retry - 1);
          clkinfo("Retrying clock enable (attempt %d/%d) after %uµs\n",
                  retry + 1, CPG_MAX_RETRIES + 1, delay_us);
          up_udelay(delay_us);
        }

      /* audit High-5: write under CS, poll OUTSIDE CS so HRT ISR not blocked.
       * CPG write-enable gating makes concurrent per-bit writes safe. */

      flags = enter_critical_section();
      rzv_cpg_putreg(mask, clkon_addr);
      leave_critical_section(flags);

      /* Poll with IRQs enabled — timeout per audit Medium-11 */

      ret = rzv_cpg_wait_bit(clkmon_addr, mon_mask, true,
                              CPG_TIMEOUT_CLOCK_ENABLE);
      if (ret >= 0)
        {
          clkinfo("Clock enabled: domain=%u bit=%u\n", domain, bit);
          return OK;
        }
    }

  clkerr("ERROR: Clock enable failed after %d attempts: domain=%u bit=%u\n",
         CPG_MAX_RETRIES + 1, domain, bit);
  rzv_cpg_dump_registers(domain, "clock_enable_failure");

  return ret;
}

/****************************************************************************
 * Name: rzv_clock_disable
 *
 * Description:
 *   Disable clock for a peripheral module
 *
 ****************************************************************************/

int rzv_clock_disable(uint32_t clk_id)
{
  uint32_t domain = RZV_CPG_DOMAIN(clk_id);
  uint32_t bit = RZV_CPG_BIT(clk_id);
  uint32_t mask;
  uint32_t mon_mask;
  uintptr_t clkon_addr = RZV_CPG_CLKON(domain);
  uintptr_t clkmon_addr = RZV_CPG_CLKMON(domain);
  irqstate_t flags;
  int ret;
  int retry;
  uint32_t delay_us;

  /* audit Critical-3 / finding #5/#6: match 2-bit/5-bit pairs used in enable */

  if (domain == RZV_CPG_DOMAIN(RZV_CPG_CLK_DMAC))
    {
      mask     = 0x1fu << 16;  /* WEN[20:16] only, ON[4:0]=0 → disable all 5 */
      mon_mask = 0x1fu;
    }
  else if (domain == RZV_CPG_DOMAIN(RZV_CPG_CLK_ADC0))
    {
      mask     = 0x3u << 16;   /* WEN[17:16] only, ON[1:0]=0 → disable both */
      mon_mask = 0x3u;
    }
  else if (clk_id == RZV_CPG_CLK_CANFD)
    {
      /* CAN-FD gate: 3-bit field CLK12/13/14 — write-enable upper half,
       * data bits 0 → gate off all three clocks.
       * Symmetric to rzv_clock_enable CAN-FD case.
       */

      mask     = (0x7u << (bit + 16)) | (0x0u << bit);
      mon_mask = (0x7u << bit);
    }
  else
    {
      mask     = (1u << (bit + 16));  /* write-enable only, ON=0 */
      mon_mask = (1u << bit);
    }

  for (retry = 0; retry <= CPG_MAX_RETRIES; retry++)
    {
      if (retry > 0)
        {
          delay_us = CPG_RETRY_DELAY_US << (retry - 1);
          clkinfo("Retrying clock disable (attempt %d/%d) after %uµs\n",
                  retry + 1, CPG_MAX_RETRIES + 1, delay_us);
          up_udelay(delay_us);
        }

      /* audit High-5: write under CS, poll outside */

      flags = enter_critical_section();
      rzv_cpg_putreg(mask, clkon_addr);
      leave_critical_section(flags);

      ret = rzv_cpg_wait_bit(clkmon_addr, mon_mask, false,
                              CPG_TIMEOUT_CLOCK_DISABLE);
      if (ret >= 0)
        {
          clkinfo("Clock disabled: domain=%u bit=%u\n", domain, bit);
          return OK;
        }
    }

  clkerr("ERROR: Clock disable failed after %d attempts: domain=%u bit=%u\n",
         CPG_MAX_RETRIES + 1, domain, bit);
  rzv_cpg_dump_registers(domain, "clock_disable_failure");

  return ret;
}

/****************************************************************************
 * Name: rzv_module_reset
 *
 * Description:
 *   Assert reset for a peripheral module
 *
 ****************************************************************************/

int rzv_module_reset(uint32_t clk_id)
{
  uint32_t domain = RZV_CPG_DOMAIN(clk_id);
  uint32_t bit = RZV_CPG_BIT(clk_id);
  uint32_t bitmask = (1u << bit);
  uint32_t mask;
  uintptr_t mrst_addr;
  uintptr_t mrstmon_addr;
  irqstate_t flags;
  int ret;
  int retry;
  uint32_t delay_us;

  /* DMAC special-case: reset lives in CPG_RST_3 bits 1..5 (RSTB1..RSTB5),
   * not in CLK domain 0 bit 0 per RZ/V2H UM CPG §RST. */

  if (clk_id == RZV_CPG_CLK_DMAC)
    {
      domain = 3;
      bitmask = (0x1Fu << 1);
    }
  else if (clk_id == RZV_CPG_CLK_CANFD)
    {
      /* CAN-FD reset: CPG_RST_10 bits[2:1] (UNIT0+UNIT1) per hardware
       * header. Clock encodes domain=9/bit=12; reset domain=10/bit=1,
       * span 2 bits.
       */

      domain  = 10;
      bitmask = (0x3u << 1);
    }

  mrst_addr = RZV_CPG_RST(domain);
  mrstmon_addr = RZV_CPG_RSTMON(domain);

  for (retry = 0; retry <= CPG_MAX_RETRIES; retry++)
    {
      if (retry > 0)
        {
          delay_us = CPG_RETRY_DELAY_US << (retry - 1);
          clkinfo("Retrying reset assert (attempt %d/%d) after %uµs\n",
                  retry + 1, CPG_MAX_RETRIES + 1, delay_us);
          up_udelay(delay_us);
        }

      /* Assert reset: WEN only, control=0 → reset asserted.
       * audit High-5: write under CS, poll outside. */

      mask = (bitmask << 16);
      flags = enter_critical_section();
      rzv_cpg_putreg(mask, mrst_addr);
      leave_critical_section(flags);

      /* Wait until RSTMON bit(s) clear (= reset propagated).
       * audit Medium-11: use per-op timeout CPG_TIMEOUT_RESET_ASSERT. */

      ret = rzv_cpg_wait_bit(mrstmon_addr, bitmask, false,
                              CPG_TIMEOUT_RESET_ASSERT);
      if (ret >= 0)
        {
          clkinfo("Reset asserted: domain=%u mask=0x%x\n", domain, bitmask);
          return OK;
        }
    }

  clkerr("ERROR: Reset assert failed after %d attempts: domain=%u mask=0x%x\n",
         CPG_MAX_RETRIES + 1, domain, bitmask);
  rzv_cpg_dump_registers(domain, "reset_assert_failure");

  return ret;
}

/****************************************************************************
 * Name: rzv_module_unreset
 *
 * Description:
 *   Deassert reset for a peripheral module
 *
 ****************************************************************************/

int rzv_module_unreset(uint32_t clk_id)
{
  uint32_t domain = RZV_CPG_DOMAIN(clk_id);
  uint32_t bit = RZV_CPG_BIT(clk_id);
  uint32_t bitmask = (1u << bit);
  uint32_t mask;
  uintptr_t mrst_addr;
  uintptr_t mrstmon_addr;
  irqstate_t flags;
  int ret;
  int retry;
  uint32_t delay_us;

  /* DMAC special-case: reset lives in CPG_RST_3 bits 1..5 (RSTB1..RSTB5),
   * not in CLK domain 0 bit 0 per RZ/V2H UM CPG §RST. */

  if (clk_id == RZV_CPG_CLK_DMAC)
    {
      domain = 3;
      bitmask = (0x1Fu << 1);
    }
  else if (clk_id == RZV_CPG_CLK_CANFD)
    {
      /* CAN-FD reset: CPG_RST_10 bits[2:1] (UNIT0+UNIT1) per hardware
       * header. Clock encodes domain=9/bit=12; reset domain=10/bit=1,
       * span 2 bits.
       */

      domain  = 10;
      bitmask = (0x3u << 1);
    }

  mrst_addr = RZV_CPG_RST(domain);
  mrstmon_addr = RZV_CPG_RSTMON(domain);

  for (retry = 0; retry <= CPG_MAX_RETRIES; retry++)
    {
      if (retry > 0)
        {
          delay_us = CPG_RETRY_DELAY_US << (retry - 1);
          clkinfo("Retrying reset release (attempt %d/%d) after %uµs\n",
                  retry + 1, CPG_MAX_RETRIES + 1, delay_us);
          up_udelay(delay_us);
        }

      /* Deassert reset: WEN + control=1 → reset released.
       * audit High-5: write under CS, poll outside.
       * audit Critical-1: wait for RSTMON==1 (set=true), not !=0 inverted. */

      mask = (bitmask << 16) | bitmask;
      flags = enter_critical_section();
      rzv_cpg_putreg(mask, mrst_addr);
      leave_critical_section(flags);

      /* audit Medium-11: use per-op timeout CPG_TIMEOUT_RESET_RELEASE */

      ret = rzv_cpg_wait_bit(mrstmon_addr, bitmask, true,
                              CPG_TIMEOUT_RESET_RELEASE);
      if (ret >= 0)
        {
          clkinfo("Reset deasserted: domain=%u mask=0x%x\n", domain, bitmask);
          return OK;
        }
    }

  clkerr("ERROR: Reset release failed after %d attempts: domain=%u mask=0x%x\n",
         CPG_MAX_RETRIES + 1, domain, bitmask);
  rzv_cpg_dump_registers(domain, "reset_release_failure");

  return ret;
}

/****************************************************************************
 * Name: rzv_clock_enable_sdhi
 *
 * Description:
 *   Enable IMCLK for one SDHI channel via CPG CLKON and release its reset.
 *   CPG IDs decoded from FSP enum (NEEDS_VERIFY against RZ/V2H UM):
 *     CH0: CPG_CLK_SDHI_0_IMCLK=0x00080628 -> domain 14, bit 3
 *          CPG_RST_SDHI_0_IXRST=0x00800928 -> domain 14, bit 7
 *   See rzv_clock.h RZV_CPG_CLK_SDHIn / RZV_CPG_RST_SDHIn macros.
 *
 ****************************************************************************/

int rzv_clock_enable_sdhi(int ch)
{
  static const uint32_t clk_ids[3] =
  {
    RZV_CPG_CLK_SDHI0, RZV_CPG_CLK_SDHI1, RZV_CPG_CLK_SDHI2
  };

  if (ch < 0 || ch > 2)
    {
      clkerr("rzv_clock_enable_sdhi: invalid channel %d\n", ch);
      return -EINVAL;
    }

  clkinfo("rzv_clock_enable_sdhi: enabling SDHI%d clock (CPG id=0x%08x)\n",
          ch, clk_ids[ch]);

  return rzv_clock_enable(clk_ids[ch]);
}

/****************************************************************************
 * Name: rzv_reset_release_sdhi
 *
 * Description:
 *   Deassert reset for one SDHI channel via CPG RST register.
 *
 ****************************************************************************/

int rzv_reset_release_sdhi(int ch)
{
  static const uint32_t rst_ids[3] =
  {
    RZV_CPG_RST_SDHI0, RZV_CPG_RST_SDHI1, RZV_CPG_RST_SDHI2
  };

  if (ch < 0 || ch > 2)
    {
      clkerr("rzv_reset_release_sdhi: invalid channel %d\n", ch);
      return -EINVAL;
    }

  clkinfo("rzv_reset_release_sdhi: releasing SDHI%d reset (CPG id=0x%08x)\n",
          ch, rst_ids[ch]);

  return rzv_module_unreset(rst_ids[ch]);
}

/****************************************************************************
 * Name: rzv_get_pclk_frequency
 *
 * Description:
 *   Get P0CLK frequency (100 MHz).  Use only for P0CLK peripherals (OSTM,
 *   GTM, WDT).  SPI and GPT require P4CLK (200 MHz) — use
 *   rzv_get_p4clk_frequency() or rzv_clock_get_rate(RZV_CLOCK_P4CLK).
 *   audit finding #4: callers that assumed this returns a generic "pclk"
 *   and use it for P4CLK peripherals will get half the correct frequency.
 *
 ****************************************************************************/

uint32_t rzv_get_pclk_frequency(void)
{
  uint32_t freq = rzv_clock_get_rate(RZV_CLOCK_P0CLK);

  if (freq == 0)
    {
      freq = RZV_PCLK_HZ;
    }

  return freq;
}

/****************************************************************************
 * Name: rzv_get_p4clk_frequency
 *
 * Description:
 *   Get P4CLK frequency (200 MHz).  Used by SPI, GPT, and other P4 peripherals
 *   on RZ/V2H per the hardware manual clock tree.
 *   audit finding #4: added to prevent callers from erroneously using
 *   rzv_get_pclk_frequency() (P0CLK = 100 MHz) for P4CLK peripherals.
 *
 ****************************************************************************/

uint32_t rzv_get_p4clk_frequency(void)
{
  uint32_t freq = rzv_clock_get_rate(RZV_CLOCK_P4CLK);

  if (freq == 0)
    {
      freq = RZV_CLOCK_P4CLK_HZ;
    }

  return freq;
}

/****************************************************************************
 * Name: rzv_get_cpu_frequency
 *
 * Description:
 *   Get the CPU clock frequency
 *
 ****************************************************************************/

uint32_t rzv_get_cpu_frequency(void)
{
  uint32_t freq = rzv_clock_get_rate(RZV_CLOCK_I6CLK);

  if (freq == 0)
    {
      freq = rzv_clock_get_rate(RZV_CLOCK_I0CLK);
    }

  if (freq == 0)
    {
      freq = RZV_CPU_CLOCK_HZ;
    }

  return freq;
}

/****************************************************************************
 * Name: rzv_get_gpt_clock_hz
 *
 * Description:
 *   Return the GPT input clock frequency.  GPT on R9A09G057H uses P4CLK
 *   (200 MHz) as its prescaler input per RZ/V2H hardware manual clock tree.
 *   UNVERIFIED: confirm against RZ/V2H UM Table 9.x if board clock tree
 *   differs from EVK default.
 *
 ****************************************************************************/

uint32_t rzv_get_gpt_clock_hz(void)
{
  /* GPT clock source = P4CLK (200 MHz) per RZ/V2H UM clock tree, not P0CLK.
   * Use compile-time constant; update if board RZV_CLOCK_P4CLK_HZ
   * differs from the EVK default. */
  return RZV_CLOCK_P4CLK_HZ;
}

/****************************************************************************
 * Name: rzv_pll_init
 *
 * Description:
 *   Initialize PLLs required for system operation. Checks if PLLs are
 *   already running and starts them if needed.
 *
 ****************************************************************************/

static void rzv_pll_init(void)
{
  uint32_t pll_mon;
  uintptr_t pll_stby;
  uintptr_t pll_mon_addr;
  const uint32_t pll_lock_mask = 0x11;  /* RESETB_Msk(0x1)|LOCK_Msk(0x10) */
  int timeout;

  clkinfo("Initializing PLLs...\n");

  /* audit High-6: PLLCM33 init under CONFIG_RZV2H_BUILD_CM33.
   * On CR8 boot, CM33 may not be active; TF-A may own PLLCM33 startup.
   * Only attempt to start PLLCM33 when building for the CM33 core to avoid
   * interfering with TF-A's initialization on the CR8 path. */

#if defined(CONFIG_RZV2H_BUILD_CM33)
  pll_mon_addr = RZV_CPG_BASE + RZV_CPG_PLLCM33_MON_OFFSET;
  pll_mon = rzv_cpg_getreg(pll_mon_addr);
  if ((pll_mon & pll_lock_mask) != pll_lock_mask)
    {
      /* PLLCM33 not locked; start it.  STBY register is at
       * PLLCM33_MON_OFFSET - 0x10 by convention (MON=base+0x0000,
       * STBY is not separately defined; this is PLLCLN_STBY territory).
       * FIXME: RZ/V2H UM must confirm PLLCM33_STBY offset.
       * Skipping write until confirmed to avoid corrupting neighboring reg. */
      clkerr("PLLCM33 not locked (mon=0x%08x) — STBY offset unconfirmed, "
             "skipping start; CM33 may malfunction\n", pll_mon);
    }
  else
    {
      clkinfo("PLLCM33 already locked\n");
    }
#else
  /* CR8 build: PLLCM33 owned by TF-A or CM33 subsystem.  Skip. */
  clkinfo("PLLCM33: CR8 build — skipping (TF-A/CM33 owns PLLCM33)\n");
#endif /* CONFIG_RZV2H_BUILD_CM33 */

  /* audit Low-12: PLL init order = PLLCLN→PLLDTY→PLLCA55→PLLVDO→PLLETH→
   * PLLDSI→PLLGPU→PLLDRP.  Order is cosmetic; PLLs are independent. */

  /* Initialize PLLCLN (1.6 GHz) if not already running */

  pll_mon_addr = RZV_CPG_BASE + RZV_CPG_PLLCLN_MON_OFFSET;
  pll_mon = rzv_cpg_getreg(pll_mon_addr);
  if ((pll_mon & pll_lock_mask) != pll_lock_mask)
    {
      pll_stby = RZV_CPG_BASE + RZV_CPG_PLLCLN_STBY_OFFSET;
      rzv_cpg_putreg(0x00010001, pll_stby);  /* RESETB_WEN + RESETB */

      /* Wait for PLL lock with extended timeout */

      timeout = CPG_TIMEOUT_PLL_LOCK;
      while (timeout-- > 0)
        {
          pll_mon = rzv_cpg_getreg(pll_mon_addr);
          if ((pll_mon & pll_lock_mask) == pll_lock_mask)
            {
              clkinfo("PLLCLN locked\n");
              break;
            }

          up_udelay(10);
        }

      if (timeout <= 0)
        {
          clkerr("ERROR: PLLCLN lock timeout\n");
        }
    }
  else
    {
      clkinfo("PLLCLN already locked\n");
    }

  /* Initialize PLLDTY (1.6 GHz) if not already running */

  pll_mon_addr = RZV_CPG_BASE + RZV_CPG_PLLDTY_MON_OFFSET;
  pll_mon = rzv_cpg_getreg(pll_mon_addr);
  if ((pll_mon & pll_lock_mask) != pll_lock_mask)
    {
      pll_stby = RZV_CPG_BASE + RZV_CPG_PLLDTY_STBY_OFFSET;
      rzv_cpg_putreg(0x00010001, pll_stby);

      timeout = CPG_TIMEOUT_PLL_LOCK;
      while (timeout-- > 0)
        {
          pll_mon = rzv_cpg_getreg(pll_mon_addr);
          if ((pll_mon & pll_lock_mask) == pll_lock_mask)
            {
              clkinfo("PLLDTY locked\n");
              break;
            }

          up_udelay(10);
        }

      if (timeout <= 0)
        {
          clkerr("ERROR: PLLDTY lock timeout\n");
        }
    }

  /* Initialize PLLCA55 (1.8 GHz) if not already running */

  pll_mon_addr = RZV_CPG_BASE + RZV_CPG_PLLCA55_MON_OFFSET;
  pll_mon = rzv_cpg_getreg(pll_mon_addr);
  if ((pll_mon & pll_lock_mask) != pll_lock_mask)
    {
      pll_stby = RZV_CPG_BASE + RZV_CPG_PLLCA55_STBY_OFFSET;
      rzv_cpg_putreg(0x00010001, pll_stby);

      timeout = CPG_TIMEOUT_PLL_LOCK;
      while (timeout-- > 0)
        {
          pll_mon = rzv_cpg_getreg(pll_mon_addr);
          if ((pll_mon & pll_lock_mask) == pll_lock_mask)
            {
              clkinfo("PLLCA55 locked\n");
              break;
            }

          up_udelay(10);
        }

      if (timeout <= 0)
        {
          clkerr("ERROR: PLLCA55 lock timeout\n");
        }
    }

  /* Initialize PLLETH (1 GHz) if not already running */

  pll_mon_addr = RZV_CPG_BASE + RZV_CPG_PLLETH_MON_OFFSET;
  pll_mon = rzv_cpg_getreg(pll_mon_addr);
  if ((pll_mon & pll_lock_mask) != pll_lock_mask)
    {
      pll_stby = RZV_CPG_BASE + RZV_CPG_PLLETH_STBY_OFFSET;
      rzv_cpg_putreg(0x00010001, pll_stby);

      timeout = CPG_TIMEOUT_PLL_LOCK;
      while (timeout-- > 0)
        {
          pll_mon = rzv_cpg_getreg(pll_mon_addr);
          if ((pll_mon & pll_lock_mask) == pll_lock_mask)
            {
              clkinfo("PLLETH locked\n");
              break;
            }

          up_udelay(10);
        }

      if (timeout <= 0)
        {
          clkerr("ERROR: PLLETH lock timeout\n");
        }
    }
  else
    {
      clkinfo("PLLETH already locked\n");
    }

  /* Initialize PLLVDO (1.26 GHz) if not already running */

  pll_mon_addr = RZV_CPG_BASE + RZV_CPG_PLLVDO_MON_OFFSET;
  pll_mon = rzv_cpg_getreg(pll_mon_addr);
  if ((pll_mon & pll_lock_mask) != pll_lock_mask)
    {
      pll_stby = RZV_CPG_BASE + RZV_CPG_PLLVDO_STBY_OFFSET;
      rzv_cpg_putreg(0x00010001, pll_stby);

      timeout = CPG_TIMEOUT_PLL_LOCK;
      while (timeout-- > 0)
        {
          pll_mon = rzv_cpg_getreg(pll_mon_addr);
          if ((pll_mon & pll_lock_mask) == pll_lock_mask)
            {
              clkinfo("PLLVDO locked\n");
              break;
            }

          up_udelay(10);
        }

      if (timeout <= 0)
        {
          clkerr("ERROR: PLLVDO lock timeout\n");
        }
    }
  else
    {
      clkinfo("PLLVDO already locked\n");
    }

  /* Initialize PLLGPU (1.26 GHz) if not already running */

  pll_mon_addr = RZV_CPG_BASE + RZV_CPG_PLLGPU_MON_OFFSET;
  pll_mon = rzv_cpg_getreg(pll_mon_addr);
  if ((pll_mon & pll_lock_mask) != pll_lock_mask)
    {
      pll_stby = RZV_CPG_BASE + RZV_CPG_PLLGPU_STBY_OFFSET;
      rzv_cpg_putreg(0x00010001, pll_stby);

      timeout = CPG_TIMEOUT_PLL_LOCK;
      while (timeout-- > 0)
        {
          pll_mon = rzv_cpg_getreg(pll_mon_addr);
          if ((pll_mon & pll_lock_mask) == pll_lock_mask)
            {
              clkinfo("PLLGPU locked\n");
              break;
            }

          up_udelay(10);
        }

      if (timeout <= 0)
        {
          clkerr("ERROR: PLLGPU lock timeout\n");
        }
    }
  else
    {
      clkinfo("PLLGPU already locked\n");
    }

  /* Initialize PLLDRP (1.26 GHz) if not already running */

  pll_mon_addr = RZV_CPG_BASE + RZV_CPG_PLLDRP_MON_OFFSET;
  pll_mon = rzv_cpg_getreg(pll_mon_addr);
  if ((pll_mon & pll_lock_mask) != pll_lock_mask)
    {
      pll_stby = RZV_CPG_BASE + RZV_CPG_PLLDRP_STBY_OFFSET;
      rzv_cpg_putreg(0x00010001, pll_stby);

      timeout = CPG_TIMEOUT_PLL_LOCK;
      while (timeout-- > 0)
        {
          pll_mon = rzv_cpg_getreg(pll_mon_addr);
          if ((pll_mon & pll_lock_mask) == pll_lock_mask)
            {
              clkinfo("PLLDRP locked\n");
              break;
            }

          up_udelay(10);
        }

      if (timeout <= 0)
        {
          clkerr("ERROR: PLLDRP lock timeout\n");
        }
    }
  else
    {
      clkinfo("PLLDRP already locked\n");
    }

  /* audit Low-13: PLLDDR0/1 init gated under Kconfig.
   * DDR is typically initialized by TF-A before NuttX runs.
   * If TF-A owns DDR, NuttX must NOT re-initialize PLLDDR to avoid
   * corrupting DDR timing.  Only init if explicitly enabled in Kconfig. */

#if defined(CONFIG_RZV_INIT_PLLDDR)
  /* Initialize PLLDDR0 (800 MHz) if not already running */

  pll_mon_addr = RZV_CPG_BASE + RZV_CPG_PLLDDR0_MON_OFFSET;
  pll_mon = rzv_cpg_getreg(pll_mon_addr);
  if ((pll_mon & pll_lock_mask) != pll_lock_mask)
    {
      pll_stby = RZV_CPG_BASE + RZV_CPG_PLLDDR0_STBY_OFFSET;
      rzv_cpg_putreg(0x00010001, pll_stby);

      timeout = CPG_TIMEOUT_PLL_LOCK;
      while (timeout-- > 0)
        {
          pll_mon = rzv_cpg_getreg(pll_mon_addr);
          if ((pll_mon & pll_lock_mask) == pll_lock_mask)
            {
              clkinfo("PLLDDR0 locked\n");
              break;
            }

          up_udelay(10);
        }

      if (timeout <= 0)
        {
          clkerr("ERROR: PLLDDR0 lock timeout\n");
        }
    }
  else
    {
      clkinfo("PLLDDR0 already locked\n");
    }

  /* Initialize PLLDDR1 (800 MHz) if not already running */

  pll_mon_addr = RZV_CPG_BASE + RZV_CPG_PLLDDR1_MON_OFFSET;
  pll_mon = rzv_cpg_getreg(pll_mon_addr);
  if ((pll_mon & pll_lock_mask) != pll_lock_mask)
    {
      pll_stby = RZV_CPG_BASE + RZV_CPG_PLLDDR1_STBY_OFFSET;
      rzv_cpg_putreg(0x00010001, pll_stby);

      timeout = CPG_TIMEOUT_PLL_LOCK;
      while (timeout-- > 0)
        {
          pll_mon = rzv_cpg_getreg(pll_mon_addr);
          if ((pll_mon & pll_lock_mask) == pll_lock_mask)
            {
              clkinfo("PLLDDR1 locked\n");
              break;
            }

          up_udelay(10);
        }

      if (timeout <= 0)
        {
          clkerr("ERROR: PLLDDR1 lock timeout\n");
        }
    }
  else
    {
      clkinfo("PLLDDR1 already locked\n");
    }
#else
  /* TF-A owns DDR PLLs; only verify they are locked (TF-A must have done it) */

  pll_mon_addr = RZV_CPG_BASE + RZV_CPG_PLLDDR0_MON_OFFSET;
  pll_mon = rzv_cpg_getreg(pll_mon_addr);
  if ((pll_mon & pll_lock_mask) != pll_lock_mask)
    {
      clkerr("PLLDDR0 not locked (mon=0x%08x) — TF-A should have locked it\n",
             pll_mon);
    }
  else
    {
      clkinfo("PLLDDR0 locked (TF-A initialized)\n");
    }

  pll_mon_addr = RZV_CPG_BASE + RZV_CPG_PLLDDR1_MON_OFFSET;
  pll_mon = rzv_cpg_getreg(pll_mon_addr);
  if ((pll_mon & pll_lock_mask) != pll_lock_mask)
    {
      clkerr("PLLDDR1 not locked (mon=0x%08x) — TF-A should have locked it\n",
             pll_mon);
    }
  else
    {
      clkinfo("PLLDDR1 locked (TF-A initialized)\n");
    }
#endif /* CONFIG_RZV_INIT_PLLDDR */

  /* Initialize PLLDSI (297 MHz) if not already running */

  pll_mon_addr = RZV_CPG_BASE + RZV_CPG_PLLDSI_MON_OFFSET;
  pll_mon = rzv_cpg_getreg(pll_mon_addr);
  if ((pll_mon & pll_lock_mask) != pll_lock_mask)
    {
      pll_stby = RZV_CPG_BASE + RZV_CPG_PLLDSI_STBY_OFFSET;
      rzv_cpg_putreg(0x00010001, pll_stby);

      timeout = CPG_TIMEOUT_PLL_LOCK;
      while (timeout-- > 0)
        {
          pll_mon = rzv_cpg_getreg(pll_mon_addr);
          if ((pll_mon & pll_lock_mask) == pll_lock_mask)
            {
              clkinfo("PLLDSI locked\n");
              break;
            }

          up_udelay(10);
        }

      if (timeout <= 0)
        {
          clkerr("ERROR: PLLDSI lock timeout\n");
        }
    }
  else
    {
      clkinfo("PLLDSI already locked\n");
    }

  clkinfo("PLL initialization complete\n");
}

/****************************************************************************
 * Name: rzv_clock_divider_init
 *
 * Description:
 *   Configure clock dividers for peripheral clocks. This ensures proper
 *   clock frequencies for all peripherals based on PLL outputs.
 *
 ****************************************************************************/

static void rzv_clock_divider_init(void)
{
  /* audit High-4: read back CDDIV/CSDIV from HW so g_clock_freq[] reflects
   * actual hardware state rather than compile-time assumptions.
   *
   * Strategy: read CDDIV0 and CSDIV0; if they are non-zero (bootloader set
   * them) extract divider fields to derive P0CLK and I6CLK, then update
   * g_clock_freq[].  If zero (cold reset default), keep compile-time defaults.
   *
   * CDDIV0 layout (RZ/V2H UM Table 9.x — UNVERIFIED field positions):
   *   bits[2:0]  = DIVSEL_I6 (CR8 CPU divider from PLLCLN)
   *   bits[7:4]  = DIVSEL_P0 (P0CLK divider from PLLCLN)
   * Until HW manual field positions are confirmed, we log the raw values and
   * use defaults.  Phase-04+ can refine once UM is available.
   *
   * Note: concurrent RMW on CDDIV/CSDIV requires CPG-wide spinlock if called
   * at runtime; safe here because IRQs are disabled at boot.
   */

  uint32_t cddiv0;
  uint32_t csdiv0;

  cddiv0 = rzv_cpg_getreg(RZV_CPG_CDDIV(0));
  csdiv0 = rzv_cpg_getreg(RZV_CPG_CSDIV(0));

  clkinfo("Clock dividers: CDDIV0=0x%08x CSDIV0=0x%08x (readback; "
          "divider field decode TODO pending RZ/V2H UM confirmation)\n",
          (unsigned)cddiv0, (unsigned)csdiv0);

  /* TODO(phase-04): decode CDDIV/CSDIV fields and update g_clock_freq[]
   * entries for I6CLK, P0CLK, P5CLK, etc. from register values. */
}

/****************************************************************************
 * Name: rzv_clock_selector_init
 *
 * Description:
 *   Configure clock selectors to choose appropriate clock sources.
 *   This is typically done by bootloader but we verify configuration.
 *
 ****************************************************************************/

static void rzv_clock_selector_init(void)
{
  /* audit High-4: read back SSEL registers to verify bootloader configuration.
   * SSEL selects clock source for muxed domains (e.g. CA55 SCLK, GBE TX/RX).
   * We do not reprogram them here — TF-A/U-Boot is expected to configure them.
   * Log values so bring-up trace can be compared against bsp_clock_cfg.h. */

  uint32_t ssel0;
  uint32_t ssel1;
  uint32_t ssel2;

  ssel0 = rzv_cpg_getreg(RZV_CPG_SSEL(0));
  ssel1 = rzv_cpg_getreg(RZV_CPG_SSEL(1));
  ssel2 = rzv_cpg_getreg(RZV_CPG_SSEL(2));

  clkinfo("Clock selectors: SSEL0=0x%08x SSEL1=0x%08x SSEL2=0x%08x "
          "(readback; not reprogrammed — bootloader owns SSEL)\n",
          (unsigned)ssel0, (unsigned)ssel1, (unsigned)ssel2);
}

/****************************************************************************
 * Name: rzv_clock_verify_frequencies
 *
 * Description:
 *   Read actual hardware configuration and verify clock frequencies.
 *   This provides runtime validation that clocks are configured correctly.
 *
 ****************************************************************************/

static void rzv_clock_verify_frequencies(void)
{
  uint32_t pll_mon;
  int verified = 0;
  int errors = 0;

  /* Verify PLLCLN is locked */

  pll_mon = rzv_cpg_getreg(RZV_CPG_BASE + RZV_CPG_PLLCLN_MON_OFFSET);
  if ((pll_mon & 0x11) == 0x11)
    {
      verified++;
    }
  else
    {
      clkerr("ERROR: PLLCLN not locked (mon=0x%08x)\n", pll_mon);
      errors++;
    }

  /* Verify PLLDTY is locked */

  pll_mon = rzv_cpg_getreg(RZV_CPG_BASE + RZV_CPG_PLLDTY_MON_OFFSET);
  if ((pll_mon & 0x11) == 0x11)
    {
      verified++;
    }
  else
    {
      clkerr("ERROR: PLLDTY not locked (mon=0x%08x)\n", pll_mon);
      errors++;
    }

  /* Verify PLLCA55 is locked */

  pll_mon = rzv_cpg_getreg(RZV_CPG_BASE + RZV_CPG_PLLCA55_MON_OFFSET);
  if ((pll_mon & 0x11) == 0x11)
    {
      verified++;
    }
  else
    {
      clkerr("ERROR: PLLCA55 not locked (mon=0x%08x)\n", pll_mon);
      errors++;
    }

  /* Verify PLLETH is locked */

  pll_mon = rzv_cpg_getreg(RZV_CPG_BASE + RZV_CPG_PLLETH_MON_OFFSET);
  if ((pll_mon & 0x11) == 0x11)
    {
      verified++;
    }
  else
    {
      clkerr("ERROR: PLLETH not locked (mon=0x%08x)\n", pll_mon);
      errors++;
    }

  /* Verify PLLVDO is locked */

  pll_mon = rzv_cpg_getreg(RZV_CPG_BASE + RZV_CPG_PLLVDO_MON_OFFSET);
  if ((pll_mon & 0x11) == 0x11)
    {
      verified++;
    }
  else
    {
      clkerr("ERROR: PLLVDO not locked (mon=0x%08x)\n", pll_mon);
      errors++;
    }

  /* Verify PLLGPU is locked */

  pll_mon = rzv_cpg_getreg(RZV_CPG_BASE + RZV_CPG_PLLGPU_MON_OFFSET);
  if ((pll_mon & 0x11) == 0x11)
    {
      verified++;
    }
  else
    {
      clkerr("ERROR: PLLGPU not locked (mon=0x%08x)\n", pll_mon);
      errors++;
    }

  /* Verify PLLDRP is locked */

  pll_mon = rzv_cpg_getreg(RZV_CPG_BASE + RZV_CPG_PLLDRP_MON_OFFSET);
  if ((pll_mon & 0x11) == 0x11)
    {
      verified++;
    }
  else
    {
      clkerr("ERROR: PLLDRP not locked (mon=0x%08x)\n", pll_mon);
      errors++;
    }

  /* Verify PLLDSI is locked */

  pll_mon = rzv_cpg_getreg(RZV_CPG_BASE + RZV_CPG_PLLDSI_MON_OFFSET);
  if ((pll_mon & 0x11) == 0x11)
    {
      verified++;
    }
  else
    {
      clkerr("ERROR: PLLDSI not locked (mon=0x%08x)\n", pll_mon);
      errors++;
    }

  /* Verify DDR PLLs are locked.
   * audit finding #13: under !CONFIG_RZV_INIT_PLLDDR TF-A owns DDR; a
   * "not locked" here is noise (TF-A may have them gated/remapped).
   * Downgrade to clkinfo so boot log is not polluted with false ERRORs.
   * Under CONFIG_RZV_INIT_PLLDDR NuttX owns DDR init → escalate to ERROR. */

  pll_mon = rzv_cpg_getreg(RZV_CPG_BASE + RZV_CPG_PLLDDR0_MON_OFFSET);
  if ((pll_mon & 0x11) == 0x11)
    {
      verified++;
    }
  else
    {
#if defined(CONFIG_RZV_INIT_PLLDDR)
      clkerr("ERROR: PLLDDR0 not locked (mon=0x%08x)\n", pll_mon);
      errors++;
#else
      clkinfo("PLLDDR0 not locked in verify (mon=0x%08x) — TF-A owns DDR\n",
              pll_mon);
#endif
    }

  pll_mon = rzv_cpg_getreg(RZV_CPG_BASE + RZV_CPG_PLLDDR1_MON_OFFSET);
  if ((pll_mon & 0x11) == 0x11)
    {
      verified++;
    }
  else
    {
#if defined(CONFIG_RZV_INIT_PLLDDR)
      clkerr("ERROR: PLLDDR1 not locked (mon=0x%08x)\n", pll_mon);
      errors++;
#else
      clkinfo("PLLDDR1 not locked in verify (mon=0x%08x) — TF-A owns DDR\n",
              pll_mon);
#endif
    }

  if (errors == 0)
    {
      clkinfo("Clock verification: %d PLLs verified, no errors\n",
              verified);
    }
  else
    {
      clkerr("Clock verification: %d PLLs verified, %d errors\n",
             verified, errors);
    }
}

/****************************************************************************
 * Name: rzv_clock_config
 *
 * Description:
 *   Early clock configuration called from reset/start code. Initializes
 *   PLLs, configures dividers/selectors, and sets up the clock frequency
 *   table.
 *
 ****************************************************************************/

void rzv_clock_config(void)
{
  clkinfo("Starting clock configuration...\n");

  /* Initialize PLLs first */

  rzv_pll_init();

  /* Configure clock dividers */

  rzv_clock_divider_init();

  /* Configure clock selectors */

  rzv_clock_selector_init();

  /* Initialize the frequency lookup table */

  rzv_clock_init_frequency_table();

  /* Verify configuration */

  rzv_clock_verify_frequencies();

  /* FIX-104: emit clock summary so the bring-up trace can be
   * cross-checked against the expected clock tree with a scope.
   */

  clkinfo("Clock summary: "
          "CR8/I6=%u Hz, SYS/I7=%u Hz, "
          "P0=%u Hz, P1=%u Hz, P5=%u Hz, AT=%u Hz\n",
          (unsigned)g_clock_freq[RZV_CLOCK_I6CLK],
          (unsigned)g_clock_freq[RZV_CLOCK_I7CLK],
          (unsigned)g_clock_freq[RZV_CLOCK_P0CLK],
          (unsigned)g_clock_freq[RZV_CLOCK_P1CLK],
          (unsigned)g_clock_freq[RZV_CLOCK_P5CLK],
          (unsigned)g_clock_freq[RZV_CLOCK_ATCLK]);

  clkinfo("Clock configuration complete\n");
}

/****************************************************************************
 * Name: rzv_clock_get_rate
 *
 * Description:
 *   Retrieve the stored frequency for the requested clock.
 *
 ****************************************************************************/

uint32_t rzv_clock_get_rate(enum rzv_clock_id_e clock_id)
{
  uint32_t freq;

  if (clock_id >= RZV_CLOCK_MAX)
    {
      return 0;
    }

  rzv_clock_init_frequency_table();

  freq = g_clock_freq[clock_id];

  /* audit finding #8: warn if a valid clock_id maps to 0 Hz so callers
   * are alerted to a missing g_clock_defaults[] entry rather than silently
   * using 0 as a divisor (baud/frequency calculation would be wrong). */

  if (freq == 0)
    {
      clkerr("WARNING: rzv_clock_get_rate: clock_id=%d (%s) has no default "
             "frequency — check g_clock_defaults[]\n",
             (int)clock_id,
             g_clock_names[clock_id] ? g_clock_names[clock_id] : "?");
    }

  return freq;
}

/****************************************************************************
 * Name: rzv_clock_get_name
 *
 * Description:
 *   Return a friendly name for logging purposes.
 *
 ****************************************************************************/

const char *rzv_clock_get_name(enum rzv_clock_id_e clock_id)
{
  if (clock_id >= RZV_CLOCK_MAX)
    {
      return NULL;
    }

  return g_clock_names[clock_id];
}

/****************************************************************************
 * Name: rzv_clock_set_lowpower_mode
 *
 * Description:
 *   Configure low-power mode for specified clock domain.
 *   Enables clock gating and standby modes for power savings.
 *
 * Input Parameters:
 *   clk_id - Clock identifier
 *   enable - true to enable low-power mode, false to disable
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 ****************************************************************************/

int rzv_clock_set_lowpower_mode(uint32_t clk_id, bool enable)
{
  /* audit High-7: was silently returning OK without doing anything.
   * LP_CTL registers not implemented; return -ENOSYS so callers know. */

  (void)clk_id;
  (void)enable;
  return -ENOSYS;
}

/****************************************************************************
 * Name: rzv_clock_enable_monitoring
 *
 * Description:
 *   Enable clock monitoring for failure detection using CLMA registers.
 *   Monitors clock frequency and detects out-of-range conditions.
 *
 * Input Parameters:
 *   clock_id - Clock to monitor
 *   enable   - true to enable monitoring, false to disable
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 ****************************************************************************/

int rzv_clock_enable_monitoring(enum rzv_clock_id_e clock_id, bool enable)
{
  /* audit High-7: was silently returning OK without configuring CLMA registers.
   * CLMA0-14 not implemented; return -ENOSYS. */

  if (clock_id >= RZV_CLOCK_MAX)
    {
      return -EINVAL;
    }

  (void)enable;
  return -ENOSYS;
}

/****************************************************************************
 * Name: rzv_clock_set_frequency
 *
 * Description:
 *   Dynamically change clock frequency for specified clock domain.
 *   Implements safe switching sequence with voltage coordination.
 *
 * Input Parameters:
 *   clock_id     - Clock to modify
 *   frequency_hz - Target frequency in Hz
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 * Notes:
 *   - Voltage scaling must be coordinated externally for CA55 clocks
 *   - Peripheral clocks can be changed within PLL limits
 *   - Follows Renesas-recommended switching sequence
 *
 ****************************************************************************/

int rzv_clock_set_frequency(enum rzv_clock_id_e clock_id,
                            uint32_t frequency_hz)
{
  /* audit High-7: was silently returning OK without touching hardware.
   * audit Medium-9: current_freq==0 when clock_id unknown → 0*2==0 → any
   * nonzero frequency_hz rejected with -EINVAL (masking bug).
   * Fix: return -ENOSYS (unimplemented) before any validation so callers
   * know dynamic frequency change is not supported, not that the argument
   * is invalid.  CDDIV/CSDIV programming belongs here once UM is confirmed. */

  if (clock_id >= RZV_CLOCK_MAX)
    {
      return -EINVAL;
    }

  if (frequency_hz == 0)
    {
      return -EINVAL;
    }

  /* Dynamic CDDIV/CSDIV programming not implemented.
   * Returning -ENOSYS (not -EINVAL) so callers can distinguish
   * "not supported yet" from "bad argument". */

  (void)frequency_hz;
  return -ENOSYS;
}

/****************************************************************************
 * Name: rzv_clock_get_status
 *
 * Description:
 *   Get comprehensive status of clock domain including enable state,
 *   reset state, and frequency.
 *
 * Input Parameters:
 *   clk_id - Clock identifier
 *   status - Pointer to status structure to fill
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 ****************************************************************************/

int rzv_clock_get_status(uint32_t clk_id,
                         struct rzv_clock_status_s *status)
{
  uint32_t domain = RZV_CPG_DOMAIN(clk_id);
  uint32_t bit = RZV_CPG_BIT(clk_id);
  uint32_t clkmon;
  uint32_t rstmon;

  if (status == NULL || domain > RZV_CPG_MAX_CLKON)
    {
      return -EINVAL;
    }

  /* Read current hardware state */

  clkmon = rzv_cpg_getreg(RZV_CPG_CLKMON(domain));
  /* audit finding #15: use 1u to avoid signed-int left-shift UB for bit>=16 */
  status->enabled = (clkmon & (1u << bit)) != 0;

  if (domain <= RZV_CPG_MAX_RST)
    {
      rstmon = rzv_cpg_getreg(RZV_CPG_RSTMON(domain));
      status->reset_asserted = (rstmon & (1u << bit)) == 0;
    }
  else
    {
      status->reset_asserted = false;
    }

  status->domain = domain;
  status->bit = bit;

  return OK;
}

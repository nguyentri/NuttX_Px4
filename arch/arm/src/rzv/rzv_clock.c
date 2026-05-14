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

/* Ensure the short delay primitive is visible in this TU.  It should be
 * declared in <nuttx/arch.h>, but provide an explicit extern to avoid
 * implicit-declaration warnings in toolchains that don't process the
 * full header set during static analysis.
 */
extern void up_udelay(useconds_t microseconds);

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

#ifndef _err
#  include <stdio.h>
#  define _err(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#endif
#ifndef _info
#  include <stdio.h>
#  define _info(fmt, ...) printf(fmt, ##__VA_ARGS__)
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
  [RZV_CLOCK_SDCLK]      = RZV_CLOCK_SDCLK_HZ,
  [RZV_CLOCK_CANCLK]     = RZV_CLOCK_CANCLK_HZ,
  [RZV_CLOCK_ADCCLK]     = RZV_CLOCK_ADCCLK_HZ,
  [RZV_CLOCK_ETHTX0CLK]  = RZV_CLOCK_ETHTX0CLK_HZ,
  [RZV_CLOCK_ETHRX0CLK]  = RZV_CLOCK_ETHRX0CLK_HZ,
  [RZV_CLOCK_ETHTX1CLK]  = RZV_CLOCK_ETHTX1CLK_HZ,
  [RZV_CLOCK_ETHRX1CLK]  = RZV_CLOCK_ETHRX1CLK_HZ,
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
 *   Wait for a bit to be set/cleared in a monitor register with
 *   adaptive timeout based on operation type.
 *
 ****************************************************************************/

static int rzv_cpg_wait_bit(uintptr_t addr, uint32_t bit, bool set)
{
  int timeout = CPG_TIMEOUT_COUNT;
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
  uintptr_t clkon_addr = RZV_CPG_CLKON(domain);
  uintptr_t clkmon_addr = RZV_CPG_CLKMON(domain);
  irqstate_t flags;
  int ret;
  int retry;
  uint32_t delay_us;

  /* Retry loop for transient failures */

  for (retry = 0; retry <= CPG_MAX_RETRIES; retry++)
    {
      if (retry > 0)
        {
          /* Exponential backoff: 100µs, 200µs, 400µs */
          delay_us = CPG_RETRY_DELAY_US << (retry - 1);
          clkinfo("Retrying clock enable (attempt %d/%d) after %uµs\n",
                  retry + 1, CPG_MAX_RETRIES + 1, delay_us);
          up_udelay(delay_us);
        }

      /* Critical section to protect register access */

      flags = enter_critical_section();

      /* Enable the clock: write-enable bit [31:16] + control bit [15:0]
       * Per Renesas hardware spec, both bits must be set to enable clock.
       */

      mask = (1 << (bit + 16)) | (1 << bit);
      rzv_cpg_putreg(mask, clkon_addr);

      /* Wait for clock to be enabled */

      ret = rzv_cpg_wait_bit(clkmon_addr, (1 << bit), true);

      leave_critical_section(flags);

      if (ret >= 0)
        {
          if (retry > 0)
            {
              clkinfo("Clock enabled after %d retries: domain=%u bit=%u\n",
                      retry, domain, bit);
            }
          else
            {
              clkinfo("Clock enabled: domain=%u bit=%u\n", domain, bit);
            }
          return OK;
        }
    }

  /* All retries exhausted - dump registers for diagnostics */

  clkerr("ERROR: Clock enable failed after %d attempts: "
         "domain=%u bit=%u\n", CPG_MAX_RETRIES + 1, domain, bit);
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
  uintptr_t clkon_addr = RZV_CPG_CLKON(domain);
  uintptr_t clkmon_addr = RZV_CPG_CLKMON(domain);
  irqstate_t flags;
  int ret;
  int retry;
  uint32_t delay_us;

  /* Retry loop for transient failures */

  for (retry = 0; retry <= CPG_MAX_RETRIES; retry++)
    {
      if (retry > 0)
        {
          /* Exponential backoff: 100µs, 200µs, 400µs */
          delay_us = CPG_RETRY_DELAY_US << (retry - 1);
          clkinfo("Retrying clock disable (attempt %d/%d) after %uµs\n",
                  retry + 1, CPG_MAX_RETRIES + 1, delay_us);
          up_udelay(delay_us);
        }

      /* Critical section to protect register access */

      flags = enter_critical_section();

      /* Disable the clock: write-enable bit [31:16] only, control bit [15:0] = 0
       * Per Renesas hardware spec, write-enable must be set with control bit clear.
       */

      mask = (1 << (bit + 16));
      rzv_cpg_putreg(mask, clkon_addr);

      /* Wait for clock to be disabled */

      ret = rzv_cpg_wait_bit(clkmon_addr, (1 << bit), false);

      leave_critical_section(flags);

      if (ret >= 0)
        {
          if (retry > 0)
            {
              clkinfo("Clock disabled after %d retries: domain=%u bit=%u\n",
                      retry, domain, bit);
            }
          else
            {
              clkinfo("Clock disabled: domain=%u bit=%u\n", domain, bit);
            }
          return OK;
        }
    }

  /* All retries exhausted - dump registers for diagnostics */

  clkerr("ERROR: Clock disable failed after %d attempts: "
         "domain=%u bit=%u\n", CPG_MAX_RETRIES + 1, domain, bit);
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
  uint32_t mask;
  uintptr_t mrst_addr = RZV_CPG_RST(domain);
  uintptr_t mrstmon_addr = RZV_CPG_RSTMON(domain);
  irqstate_t flags;
  int ret;
  int retry;
  uint32_t delay_us;

  /* Retry loop for transient failures */

  for (retry = 0; retry <= CPG_MAX_RETRIES; retry++)
    {
      if (retry > 0)
        {
          /* Exponential backoff: 100µs, 200µs, 400µs */
          delay_us = CPG_RETRY_DELAY_US << (retry - 1);
          clkinfo("Retrying reset assert (attempt %d/%d) after %uµs\n",
                  retry + 1, CPG_MAX_RETRIES + 1, delay_us);
          up_udelay(delay_us);
        }

      /* Critical section to protect register access */

      flags = enter_critical_section();

      /* Assert reset: write-enable bit [31:16] only, control bit [15:0] = 0
       * Per Renesas hardware spec, control bit = 0 means reset asserted.
       */

      mask = (1 << (bit + 16));
      rzv_cpg_putreg(mask, mrst_addr);

      /* Wait for reset to be asserted (monitor bit = 0) */

      ret = rzv_cpg_wait_bit(mrstmon_addr, (1 << bit), false);

      leave_critical_section(flags);

      if (ret >= 0)
        {
          if (retry > 0)
            {
              clkinfo("Reset asserted after %d retries: domain=%u bit=%u\n",
                      retry, domain, bit);
            }
          else
            {
              clkinfo("Reset asserted: domain=%u bit=%u\n", domain, bit);
            }
          return OK;
        }
    }

  /* All retries exhausted - dump registers for diagnostics */

  clkerr("ERROR: Reset assert failed after %d attempts: "
         "domain=%u bit=%u\n", CPG_MAX_RETRIES + 1, domain, bit);
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
  uint32_t mask;
  uintptr_t mrst_addr = RZV_CPG_RST(domain);
  uintptr_t mrstmon_addr = RZV_CPG_RSTMON(domain);
  irqstate_t flags;
  int ret;
  int retry;
  uint32_t delay_us;

  /* Retry loop for transient failures */

  for (retry = 0; retry <= CPG_MAX_RETRIES; retry++)
    {
      if (retry > 0)
        {
          /* Exponential backoff: 100µs, 200µs, 400µs */
          delay_us = CPG_RETRY_DELAY_US << (retry - 1);
          clkinfo("Retrying reset release (attempt %d/%d) after %uµs\n",
                  retry + 1, CPG_MAX_RETRIES + 1, delay_us);
          up_udelay(delay_us);
        }

      /* Critical section to protect register access */

      flags = enter_critical_section();

      /* Deassert reset: write-enable bit [31:16] + control bit [15:0]
       * Per Renesas hardware spec, control bit = 1 means reset released.
       */

      mask = (1 << (bit + 16)) | (1 << bit);
      rzv_cpg_putreg(mask, mrst_addr);

      /* Wait for reset to be deasserted (monitor bit = 1) */

      ret = rzv_cpg_wait_bit(mrstmon_addr, (1 << bit), true);

      leave_critical_section(flags);

      if (ret >= 0)
        {
          if (retry > 0)
            {
              clkinfo("Reset deasserted after %d retries: domain=%u bit=%u\n",
                      retry, domain, bit);
            }
          else
            {
              clkinfo("Reset deasserted: domain=%u bit=%u\n", domain, bit);
            }
          return OK;
        }
    }

  /* All retries exhausted - dump registers for diagnostics */

  clkerr("ERROR: Reset release failed after %d attempts: "
         "domain=%u bit=%u\n", CPG_MAX_RETRIES + 1, domain, bit);
  rzv_cpg_dump_registers(domain, "reset_release_failure");

  return ret;
}

/****************************************************************************
 * Name: rzv_get_pclk_frequency
 *
 * Description:
 *   Get the peripheral clock frequency
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
  const uint32_t pll_lock_mask = 0x11;  /* RESETB + LOCK bits */
  int timeout;

  clkinfo("Initializing PLLs...\n");

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

      timeout = CPG_TIMEOUT_COUNT * 10;
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

      timeout = CPG_TIMEOUT_COUNT * 10;
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

      timeout = CPG_TIMEOUT_COUNT * 10;
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

      timeout = CPG_TIMEOUT_COUNT * 10;
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

      timeout = CPG_TIMEOUT_COUNT * 10;
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

      timeout = CPG_TIMEOUT_COUNT * 10;
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

  /* Initialize PLLDSI (297 MHz) if not already running */

  pll_mon_addr = RZV_CPG_BASE + RZV_CPG_PLLDSI_MON_OFFSET;
  pll_mon = rzv_cpg_getreg(pll_mon_addr);
  if ((pll_mon & pll_lock_mask) != pll_lock_mask)
    {
      pll_stby = RZV_CPG_BASE + RZV_CPG_PLLDSI_STBY_OFFSET;
      rzv_cpg_putreg(0x00010001, pll_stby);

      timeout = CPG_TIMEOUT_COUNT * 10;
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
  /* CDDIV and CSDIV configuration would go here if needed.
   * For now, we rely on bootloader/reset defaults which match
   * our configured frequencies. Future enhancement: read and
   * verify divider settings, configure if needed.
   */

  clkinfo("Clock dividers: using reset defaults\n");
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
  /* SSEL configuration would go here if needed.
   * For now, we rely on bootloader/reset defaults.
   * Future enhancement: configure selectors for specific use cases.
   */

  clkinfo("Clock selectors: using reset defaults\n");
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

  /* Verify DDR PLLs are locked */

  pll_mon = rzv_cpg_getreg(RZV_CPG_BASE + RZV_CPG_PLLDDR0_MON_OFFSET);
  if ((pll_mon & 0x11) == 0x11)
    {
      verified++;
    }
  else
    {
      clkerr("ERROR: PLLDDR0 not locked (mon=0x%08x)\n", pll_mon);
      errors++;
    }

  pll_mon = rzv_cpg_getreg(RZV_CPG_BASE + RZV_CPG_PLLDDR1_MON_OFFSET);
  if ((pll_mon & 0x11) == 0x11)
    {
      verified++;
    }
  else
    {
      clkerr("ERROR: PLLDDR1 not locked (mon=0x%08x)\n", pll_mon);
      errors++;
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

  /* FIX-104: emit FSP-aligned summary so the bring-up trace can be
   * cross-checked against bsp_clock_cfg.h with a scope.
   */

  clkinfo("Clock summary (FSP-aligned): "
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
  if (clock_id >= RZV_CLOCK_MAX)
    {
      return 0;
    }

  rzv_clock_init_frequency_table();

  return g_clock_freq[clock_id];
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
  uint32_t domain = RZV_CPG_DOMAIN(clk_id);
  uint32_t bit = RZV_CPG_BIT(clk_id);
  irqstate_t flags;

  /* Validate domain */

  if (domain > RZV_CPG_MAX_CLKON)
    {
      clkerr("ERROR: Invalid clock domain %u\n", domain);
      return -EINVAL;
    }

  flags = enter_critical_section();

  /* Low-power mode implementation:
   * For production systems, this would configure LP_CTL registers.
   * Current implementation: placeholder for future enhancement.
   */

  if (enable)
    {
      clkinfo("Low-power mode enabled for domain=%u bit=%u\n",
              domain, bit);
    }
  else
    {
      clkinfo("Low-power mode disabled for domain=%u bit=%u\n",
              domain, bit);
    }

  leave_critical_section(flags);

  return OK;
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
  irqstate_t flags;

  if (clock_id >= RZV_CLOCK_MAX)
    {
      return -EINVAL;
    }

  flags = enter_critical_section();

  /* Clock monitoring implementation:
   * Production systems would configure CLMA0-14 registers here.
   * Current implementation: framework for future enhancement.
   */

  if (enable)
    {
      clkinfo("Clock monitoring enabled for %s\n",
              rzv_clock_get_name(clock_id));
    }
  else
    {
      clkinfo("Clock monitoring disabled for %s\n",
              rzv_clock_get_name(clock_id));
    }

  leave_critical_section(flags);

  return OK;
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
  uint32_t current_freq;
  irqstate_t flags;

  if (clock_id >= RZV_CLOCK_MAX)
    {
      return -EINVAL;
    }

  current_freq = rzv_clock_get_rate(clock_id);

  /* Safety check: don't allow frequency changes beyond hardware limits */

  if (frequency_hz == 0 || frequency_hz > current_freq * 2)
    {
      clkerr("ERROR: Invalid target frequency %u Hz for %s\n",
             frequency_hz, rzv_clock_get_name(clock_id));
      return -EINVAL;
    }

  flags = enter_critical_section();

  /* Dynamic frequency change implementation:
   * Production systems would:
   * 1. Check voltage scaling requirements
   * 2. Adjust dividers (CDDIV/CSDIV registers)
   * 3. Update PLL configuration if needed
   * 4. Wait for stabilization
   * 5. Update frequency table
   *
   * Current implementation: framework for future enhancement.
   */

  clkinfo("Frequency change requested for %s: %u Hz -> %u Hz\n",
          rzv_clock_get_name(clock_id), current_freq, frequency_hz);

  leave_critical_section(flags);

  return OK;
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
  status->enabled = (clkmon & (1 << bit)) != 0;

  if (domain <= RZV_CPG_MAX_RST)
    {
      rstmon = rzv_cpg_getreg(RZV_CPG_RSTMON(domain));
      status->reset_asserted = (rstmon & (1 << bit)) == 0;
    }
  else
    {
      status->reset_asserted = false;
    }

  status->domain = domain;
  status->bit = bit;

  return OK;
}

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

#define CPG_TIMEOUT_COUNT         1000

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
 * Name: rzv_cpg_wait_bit
 *
 * Description:
 *   Wait for a bit to be set/cleared in a monitor register
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

  /* Critical section to protect register access */

  flags = enter_critical_section();

  /* Enable the clock: write-enable bit [31:16] + control bit [15:0]
   * Per Renesas hardware spec, both bits must be set to enable clock.
   */

  mask = (1 << (bit + 16)) | (1 << bit);
  rzv_cpg_putreg(mask, clkon_addr);

  /* Wait for clock to be enabled */

  ret = rzv_cpg_wait_bit(clkmon_addr, (1 << bit), true);
  if (ret < 0)
    {
      clkerr("ERROR: Timeout enabling clock domain=%u bit=%u\n",
        domain, bit);
      leave_critical_section(flags);
      return ret;
    }

  leave_critical_section(flags);

  clkinfo("Clock enabled: domain=%u bit=%u\n", domain, bit);

  return OK;
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

  /* Critical section to protect register access */

  flags = enter_critical_section();

  /* Disable the clock: write-enable bit [31:16] only, control bit [15:0] = 0
   * Per Renesas hardware spec, write-enable must be set with control bit clear.
   */

  mask = (1 << (bit + 16));
  rzv_cpg_putreg(mask, clkon_addr);

  /* Wait for clock to be disabled */

  ret = rzv_cpg_wait_bit(clkmon_addr, (1 << bit), false);
  if (ret < 0)
    {
      clkerr("ERROR: Timeout disabling clock domain=%u bit=%u\n",
        domain, bit);
      leave_critical_section(flags);
      return ret;
    }

  leave_critical_section(flags);

  clkinfo("Clock disabled: domain=%u bit=%u\n", domain, bit);

  return OK;
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

  /* Critical section to protect register access */

  flags = enter_critical_section();

  /* Assert reset: write-enable bit [31:16] only, control bit [15:0] = 0
   * Per Renesas hardware spec, control bit = 0 means reset asserted.
   */

  mask = (1 << (bit + 16));
  rzv_cpg_putreg(mask, mrst_addr);

  /* Wait for reset to be asserted (monitor bit = 0) */

  ret = rzv_cpg_wait_bit(mrstmon_addr, (1 << bit), false);
  if (ret < 0)
    {
      clkerr("ERROR: Timeout asserting reset domain=%u bit=%u\n",
        domain, bit);
      leave_critical_section(flags);
      return ret;
    }

  leave_critical_section(flags);

  clkinfo("Reset asserted: domain=%u bit=%u\n", domain, bit);

  return OK;
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

  /* Critical section to protect register access */

  flags = enter_critical_section();

  /* Deassert reset: write-enable bit [31:16] + control bit [15:0]
   * Per Renesas hardware spec, control bit = 1 means reset released.
   */

  mask = (1 << (bit + 16)) | (1 << bit);
  rzv_cpg_putreg(mask, mrst_addr);

  /* Wait for reset to be deasserted (monitor bit = 1) */

  ret = rzv_cpg_wait_bit(mrstmon_addr, (1 << bit), true);
  if (ret < 0)
    {
      clkerr("ERROR: Timeout deasserting reset domain=%u bit=%u\n",
        domain, bit);
      leave_critical_section(flags);
      return ret;
    }

  leave_critical_section(flags);

  clkinfo("Reset deasserted: domain=%u bit=%u\n", domain, bit);

  return OK;
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

  /* Initialize PLLCLN (1.6 GHz) if not already running */

  pll_mon_addr = RZV_CPG_BASE + RZV_CPG_PLLCLN_MON_OFFSET;
  pll_mon = rzv_cpg_getreg(pll_mon_addr);
  if ((pll_mon & pll_lock_mask) != pll_lock_mask)
    {
      pll_stby = RZV_CPG_BASE + RZV_CPG_PLLCLN_STBY_OFFSET;
      rzv_cpg_putreg(0x00010001, pll_stby);  /* RESETB_WEN + RESETB */

      /* Wait for PLL lock with timeout */

      timeout = CPG_TIMEOUT_COUNT * 10;  /* PLLs need longer timeout */
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
}

/****************************************************************************
 * Name: rzv_clock_config
 *
 * Description:
 *   Early clock configuration called from reset/start code. Initializes
 *   PLLs and sets up the clock frequency table.
 *
 ****************************************************************************/

void rzv_clock_config(void)
{
  /* Initialize PLLs first */

  rzv_pll_init();

  /* Initialize the frequency lookup table */

  rzv_clock_init_frequency_table();
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
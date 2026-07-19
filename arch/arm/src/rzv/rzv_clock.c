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
 * explicit extern removed — redundant with <nuttx/arch.h>
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

/* stdio.h printf fallback removed — printf is unsafe from
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
#include "hardware/rzv_gpt.h"



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
#define RZV_CPG_DUMP_NONE         UINT32_MAX

#define RZV_GPT_UNIT_COUNT        2u
#define RZV_GPT_CLKON_BIT(unit)   (1u << (1u + (unit)))
#define RZV_GPT_CLKMON_BIT(unit)  (1u << (17u + (unit)))
#define RZV_GPT_MSTOP_BIT(unit)   (1u << (11u + (unit)))
#define RZV_GPT_RST_BIT(unit)     (3u << (9u + ((unit) * 2u)))
#define RZV_GPT_RSTMON_BIT(unit)  (3u << (10u + ((unit) * 2u)))

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
static uint16_t g_rzv_gpt_unit_users[RZV_GPT_UNIT_COUNT];

/* CR8 CPU clock (I6CLK) decoded from CDDIV2.DIVCTL1 at boot; 0 = not decoded,
 * in which case the compile-time default is used.
 */

static uint32_t g_i6clk_actual_hz;

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
 * Name: rzv_cpg_dump_monitor_range
 *
 * Description:
 *   Dump the exact packed monitor range used by a failed CPG operation.
 *
 ****************************************************************************/

static void rzv_cpg_dump_monitor_range(bool reset, uint32_t start,
                                       uint32_t nbits)
{
  uint32_t g;

  if (start == RZV_CPG_DUMP_NONE || nbits == 0)
    {
      return;
    }

  if (reset)
    {
      if (start < 15u)
        {
          clkerr("  RSTMON unavailable for RST g=%u\n", start);
          return;
        }

      g = start - 15u;
    }
  else
    {
      g = start;
    }

  while (nbits > 0)
    {
      uint32_t monitor = g / 32u;
      uint32_t off = g % 32u;
      uint32_t n = (32u - off < nbits) ? (32u - off) : nbits;
      uint32_t value;

      if (monitor > (reset ? RZV_CPG_MAX_RSTMON : RZV_CPG_MAX_CLKMON))
        {
          clkerr("  %sMON%u unavailable\n", reset ? "RST" : "CLK",
                 monitor);
          return;
        }

      value = rzv_cpg_getreg(reset ? RZV_CPG_RSTMON(monitor) :
                                           RZV_CPG_CLKMON(monitor));
      clkerr("  %sMON%u [%u:%u] = 0x%08x\n",
             reset ? "RST" : "CLK", monitor, off + n - 1u, off, value);

      g += n;
      nbits -= n;
    }
}

/****************************************************************************
 * Name: rzv_cpg_dump_registers
 *
 * Description:
 *   Dump CPG control-register state and the exact monitor ranges for a
 *   failed operation.
 *
 ****************************************************************************/

static void rzv_cpg_dump_registers(uint32_t domain, uint32_t clkmon_start,
                                   uint32_t clkmon_nbits,
                                   uint32_t rstmon_start,
                                   uint32_t rstmon_nbits,
                                   const char *context)
{
  uint32_t clkon;
  uint32_t rst;

  if (domain > RZV_CPG_MAX_CLKON)
    {
      clkerr("Invalid domain %u in %s\n", domain, context);
      return;
    }

  clkon = rzv_cpg_getreg(RZV_CPG_CLKON(domain));

  clkerr("CPG Register Dump [%s] Domain %u:\n", context, domain);
  clkerr("  CLKON%u  = 0x%08x\n", domain, clkon);
  rzv_cpg_dump_monitor_range(false, clkmon_start, clkmon_nbits);

  if (domain <= RZV_CPG_MAX_RST)
    {
      rst = rzv_cpg_getreg(RZV_CPG_RST(domain));
      clkerr("  RST%u    = 0x%08x\n", domain, rst);
      rzv_cpg_dump_monitor_range(true, rstmon_start, rstmon_nbits);
    }
}

/****************************************************************************
 * Name: rzv_cpg_wait_bit
 *
 * Description:
 *   Wait for a bit to be set/cleared in a monitor register.
 *   MUST be called with IRQs ENABLED (outside critical section).
 * poll moved outside enter_critical_section so HRT ISR
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
 * Name: rzv_cpg_wait_clkmon / rzv_cpg_wait_rstmon
 *
 * Description:
 *   Poll CPG monitor registers using the FSP-verified register packing,
 *   which DIFFERS from the control registers (anchors: bsp_override.h
 *   SCI/GTM/DMAC macros in refs/px4-freertos-posix-renesas-fsp):
 *
 *   - CLKON_m / RST_m pack 16 control bits + 16 write-enable bits per
 *     register, so the global control index is g = 16*m + b.
 *   - CLKMON_m packs 32 monitor bits per register with the SAME global
 *     numbering: monitor reg = g/32, bit = g%32.
 *     (SCI4 gates CLKON_7[5:1] = g 113..117 -> CLKMON_3[21:17];
 *      GTMn gate CLKON_4[3+n] = g 67+n -> CLKMON_2[3+n].)
 *   - RSTMON_m packs 32 monitor bits with the global numbering OFFSET BY
 *     -15: monitor reg = (r-15)/32, bit = (r-15)%32.
 *     (SCI0 SCIP r=129 -> RSTMON_3.RST18=114; GTM0 r=109 -> RSTMON_2.RST30
 *      =94; DMAC r=49..53 -> RSTMON_1.RST2..RST6=34..38. All -15.)
 *
 *   A monitor span may straddle a 32-bit register boundary (e.g. SCI0
 *   clocks g=93..97 span CLKMON_2/CLKMON_3); both helpers slice on 32-bit
 *   boundaries.  Returns OK or -ETIMEDOUT from the first failing slice.
 *
 ****************************************************************************/

static int rzv_cpg_wait_clkmon(uint32_t g, uint32_t nbits, bool set,
                               int timeout)
{
  int ret = OK;

  while (nbits > 0)
    {
      uint32_t reg  = g / 32u;
      uint32_t off  = g % 32u;
      uint32_t n    = (32u - off < nbits) ? (32u - off) : nbits;
      uint32_t bits = ((1u << n) - 1u) << off;

      ret = rzv_cpg_wait_bit(RZV_CPG_CLKMON(reg), bits, set, timeout);
      if (ret < 0)
        {
          return ret;
        }

      g     += n;
      nbits -= n;
    }

  return ret;
}

static int rzv_cpg_wait_rstmon(uint32_t r, uint32_t nbits, bool set,
                               int timeout)
{
  uint32_t g = r - 15u;  /* RSTMON global numbering = RST global - 15 */
  int ret = OK;

  while (nbits > 0)
    {
      uint32_t reg  = g / 32u;
      uint32_t off  = g % 32u;
      uint32_t n    = (32u - off < nbits) ? (32u - off) : nbits;
      uint32_t bits = ((1u << n) - 1u) << off;

      ret = rzv_cpg_wait_bit(RZV_CPG_RSTMON(reg), bits, set, timeout);
      if (ret < 0)
        {
          return ret;
        }

      g     += n;
      nbits -= n;
    }

  return ret;
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

  /* Override the CR8 CPU clock with the live CDDIV2 divider readback decoded
   * in rzv_clock_divider_init(), so the scheduler tick and any I6CLK consumer
   * track the actual programmed divider instead of the compile-time default.
   */

  if (g_i6clk_actual_hz != 0)
    {
      g_clock_freq[RZV_CLOCK_I6CLK] = g_i6clk_actual_hz;
    }

  g_clock_freq_valid = true;

  clkinfo("Clock table initialized with hardware defaults\n");
}

/****************************************************************************
 * Name: rzv_cpg_sci_channel
 *
 * Description:
 *   Map an SCI clock ID to its RSCI channel number, or -1 if the ID is not
 *   an SCI clock.  RSCI gating needs special handling: five consecutive
 *   CLKON bits per channel spanning CPG_CLKON_5..8 (SCIPCLK, SCITCLK,
 *   SCIPS3/2/1) and two consecutive CPG_RST_8/9 bits (SCIP, SCIT).
 *   Source: FSP rzv2h bsp_override.h BSP_CLKON_*_FSP_IP_SCIP/SCIT/SCIPS*.
 *
 ****************************************************************************/

static int rzv_cpg_sci_channel(uint32_t clk_id)
{
  static const uint32_t sci_ids[10] =
  {
    RZV_CPG_CLK_SCI0, RZV_CPG_CLK_SCI1, RZV_CPG_CLK_SCI2,
    RZV_CPG_CLK_SCI3, RZV_CPG_CLK_SCI4, RZV_CPG_CLK_SCI5,
    RZV_CPG_CLK_SCI6, RZV_CPG_CLK_SCI7, RZV_CPG_CLK_SCI8,
    RZV_CPG_CLK_SCI9
  };

  int ch;

  for (ch = 0; ch < 10; ch++)
    {
      if (sci_ids[ch] == clk_id)
        {
          return ch;
        }
    }

  return -1;
}

/****************************************************************************
 * Name: rzv_cpg_sci_clock_ctrl
 *
 * Description:
 *   Gate all five RSCI clocks of one channel on or off.  The 5-bit span
 *   starts at CLKON global bit (5*16 + 13 + 5*ch) and may cross into the
 *   next CLKON register (SCI0 and SCI3).  Each register slice is written
 *   as WEN[bit+16] | ON[bit] and confirmed via the matching CLKMON.
 *
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_cpg_mstop_write
 *
 * Description:
 *   Release (release=true) or assert the CPG BUS_m_MSTOP bits for a module.
 *   MSTOP gates the module's BUS/REGISTER interface independently of the
 *   CLKON clock gates: while asserted, register reads return zero and
 *   writes are dropped — even with clocks gated on and resets released
 *   (verified on silicon: BUS_11_MSTOP resets to 0x1ffe, leaving every
 *   RSCI register interface dead).  Mirrors FSP R_BSP_MSTP_START/STOP
 *   (bsp_module_stop.h): WEN in [31:16], data 0 = released, 1 = stopped.
 *   No monitor register exists for MSTOP; the readback orders the write.
 *
 ****************************************************************************/

static void rzv_cpg_mstop_write(uintptr_t reg, uint32_t bits, bool release)
{
  irqstate_t flags;

  flags = enter_critical_section();
  rzv_cpg_putreg(release ? (bits << 16) : ((bits << 16) | bits), reg);
  (void)rzv_cpg_getreg(reg);
  leave_critical_section(flags);
}

/* Peripheral bus-interface module-stop (MSTOP) map.
 *
 * MSTOP gates the module BUS/REGISTER interface independently of the CLKON
 * clock gates (see rzv_cpg_mstop_write above).  Per RZ/V2H UM Tables
 * 4.4-36..4.4-38 several of these bits reset to "stopped" (BUS_1 resets to
 * 0xAFFF -> RIIC0-3 stopped; BUS_12 to 0x0201 -> GTM7 stopped; BUS_8 to
 * 0x077D -> SD0-2/GBETH stopped), so the module bus interface must be
 * released once its clock is confirmed or every register read returns 0.
 *
 * DMAC (5-unit mask, rzv_dmac.c), RSCI (5-bit CLKON span, rzv_cpg_sci_*)
 * and GPT (per-unit, rzv_gpt_module_start) own dedicated release paths and
 * are intentionally absent here.  Entries not yet exercised on silicon are
 * spec-derived and need on-target confirmation during bring-up.
 */

struct rzv_mstop_entry_s
{
  uint32_t  clk_id;
  uintptr_t reg;
  uint8_t   bit;
};

static const struct rzv_mstop_entry_s g_rzv_mstop_map[] =
{
  { RZV_CPG_CLK_I2C0,  RZV_CPG_BUS_1_MSTOP,   1 },  /* RIIC0  */
  { RZV_CPG_CLK_I2C1,  RZV_CPG_BUS_1_MSTOP,   2 },  /* RIIC1  */
  { RZV_CPG_CLK_I2C2,  RZV_CPG_BUS_1_MSTOP,   3 },  /* RIIC2  */
  { RZV_CPG_CLK_I2C3,  RZV_CPG_BUS_1_MSTOP,   4 },  /* RIIC3  */
  { RZV_CPG_CLK_SPI0,  RZV_CPG_BUS_11_MSTOP,  0 },  /* RSPI0  */
  { RZV_CPG_CLK_SPI1,  RZV_CPG_BUS_11_MSTOP,  1 },  /* RSPI1  */
  { RZV_CPG_CLK_SPI2,  RZV_CPG_BUS_11_MSTOP,  2 },  /* RSPI2  */
  { RZV_CPG_CLK_ADC0,  RZV_CPG_BUS_3_MSTOP,   9 },  /* ADC    */
  { RZV_CPG_CLK_CANFD, RZV_CPG_BUS_10_MSTOP, 14 },  /* CAN-FD */
  /* GBETH0/1 (BUS_8 MSTOP5/6) intentionally omitted: RZV_CPG_CLK_ETH0
   * currently aliases RZV_CPG_CLK_SCI7 (both (8<<16|0)) so it can never
   * reach this map, and rzv_ether.c does not call rzv_clock_enable().
   * Add once a distinct GBETH clock ID exists (see rzv_clock.h ETH TODO).
   */
  { RZV_CPG_CLK_SDHI0, RZV_CPG_BUS_8_MSTOP,   2 },  /* SD0    */
  { RZV_CPG_CLK_SDHI1, RZV_CPG_BUS_8_MSTOP,   3 },  /* SD1    */
  { RZV_CPG_CLK_SDHI2, RZV_CPG_BUS_8_MSTOP,   4 },  /* SD2    */
  { RZV_CPG_CLK_GTM0,  RZV_CPG_BUS_5_MSTOP,  10 },  /* GTM0   */
  { RZV_CPG_CLK_GTM1,  RZV_CPG_BUS_5_MSTOP,  11 },  /* GTM1   */
  { RZV_CPG_CLK_GTM2,  RZV_CPG_BUS_1_MSTOP,  13 },  /* GTM2   */
  { RZV_CPG_CLK_GTM3,  RZV_CPG_BUS_1_MSTOP,  14 },  /* GTM3   */
  { RZV_CPG_CLK_GTM4,  RZV_CPG_BUS_11_MSTOP, 13 },  /* GTM4   */
  { RZV_CPG_CLK_GTM5,  RZV_CPG_BUS_11_MSTOP, 14 },  /* GTM5   */
  { RZV_CPG_CLK_GTM6,  RZV_CPG_BUS_11_MSTOP, 15 },  /* GTM6   */
  { RZV_CPG_CLK_GTM7,  RZV_CPG_BUS_12_MSTOP,  0 },  /* GTM7   */
};

/* Release the module bus-interface MSTOP for clk_id, if it has a mapping.
 * Release-only: mirrors the pre-existing SPI/ADC behaviour and never
 * re-asserts MSTOP on disable, so a shared-bus module is not gated off
 * from under another user.
 */

static void rzv_cpg_mstop_release(uint32_t clk_id)
{
  unsigned int i;

  for (i = 0; i < sizeof(g_rzv_mstop_map) / sizeof(g_rzv_mstop_map[0]); i++)
    {
      if (g_rzv_mstop_map[i].clk_id == clk_id)
        {
          rzv_cpg_mstop_write(g_rzv_mstop_map[i].reg,
                              1u << g_rzv_mstop_map[i].bit, true);
          return;
        }
    }
}

static int rzv_cpg_sci_clock_ctrl(int ch, bool enable)
{
  uint32_t gstart = 5u * 16u + 13u + 5u * (uint32_t)ch;
  uint32_t g = gstart;
  uint32_t remaining = 5;
  irqstate_t flags;
  int ret;

  /* On disable, stop the bus interface first (mirror of FSP MODULE_STOP:
   * MSTP assert precedes clock gating).
   */

  if (!enable)
    {
      rzv_cpg_mstop_write(RZV_CPG_BUS_11_MSTOP, 1u << (3 + ch), false);
    }

  /* Write all CLKON slices first (16 control + 16 WEN bits per register;
   * a 5-bit channel span may straddle two CLKON registers).
   */

  while (remaining > 0)
    {
      uint32_t domain = g / 16u;
      uint32_t off    = g % 16u;
      uint32_t n      = (16u - off < remaining) ? (16u - off) : remaining;
      uint32_t bits   = ((1u << n) - 1u) << off;
      uint32_t mask   = (bits << 16) | (enable ? bits : 0u);

      flags = enter_critical_section();
      rzv_cpg_putreg(mask, RZV_CPG_CLKON(domain));
      leave_critical_section(flags);

      g         += n;
      remaining -= n;
    }

  /* Then confirm via CLKMON, which is 32-bit packed with the same global
   * numbering (see rzv_cpg_wait_clkmon) — NOT the CLKON register index.
   */

  ret = rzv_cpg_wait_clkmon(gstart, 5, enable,
                            enable ? CPG_TIMEOUT_CLOCK_ENABLE :
                                     CPG_TIMEOUT_CLOCK_DISABLE);
  if (ret < 0)
    {
      clkerr("ERROR: SCI%d clock %s failed: CLKMON g=%u..%u\n",
             ch, enable ? "enable" : "disable",
             (unsigned int)gstart, (unsigned int)(gstart + 4));
      rzv_cpg_dump_registers(gstart / 16u, gstart, 5,
                             RZV_CPG_DUMP_NONE, 0,
                             "sci_clock_ctrl_failure");
      return ret;
    }

  /* Release the RSCI bus-interface module stop: BUS_11_MSTOP bit (3 + ch)
   * (RSPI0-2 own bits 0-2, RSCI0-9 own bits 3-12).  Without this every
   * RSCI register reads as zero and CSR.TDRE never asserts.  FSP parity:
   * R_BSP_MODULE_START_FSP_IP_SCI = 5x CLKON + MSTP_START + 2x RSTOFF.
   */

  if (enable)
    {
      rzv_cpg_mstop_write(RZV_CPG_BUS_11_MSTOP, 1u << (3 + ch), true);
    }

  clkinfo("SCI%d clocks %s\n", ch, enable ? "enabled" : "disabled");
  return OK;
}

/****************************************************************************
 * Name: rzv_cpg_sci_reset_ctrl
 *
 * Description:
 *   Assert (assert_rst=true) or deassert both RSCI resets of one channel.
 *   SCIP reset = CPG_RST global bit (8*16 + 1 + 2*ch), SCIT the next bit;
 *   the pair crosses into CPG_RST_9 for channel 7.
 *   Per FSP bsp_clocks.h (RZ/V2H), RSTMON bit == 1 while held in reset and
 *   == 0 once released: assert writes WEN only (control=0) and waits RSTMON
 *   set; deassert writes WEN|bits (control=1) and waits RSTMON clear.
 *
 ****************************************************************************/

static int rzv_cpg_sci_reset_ctrl(int ch, bool assert_rst)
{
  uint32_t gstart = 8u * 16u + 1u + 2u * (uint32_t)ch;
  uint32_t g = gstart;
  uint32_t remaining = 2;
  irqstate_t flags;
  int ret;

  /* Write all RST slices first (16 control + 16 WEN bits per register;
   * the SCIP/SCIT pair crosses into CPG_RST_9 for channel 7).
   */

  while (remaining > 0)
    {
      uint32_t domain = g / 16u;
      uint32_t off    = g % 16u;
      uint32_t n      = (16u - off < remaining) ? (16u - off) : remaining;
      uint32_t bits   = ((1u << n) - 1u) << off;
      uint32_t mask   = (bits << 16) | (assert_rst ? 0u : bits);

      flags = enter_critical_section();
      rzv_cpg_putreg(mask, RZV_CPG_RST(domain));
      leave_critical_section(flags);

      g         += n;
      remaining -= n;
    }

  /* RSTMON polarity per FSP bsp_clocks.h (RZ/V2H): RSTMON bit == 1 while
   * the module is held in reset, == 0 once the reset is released.
   * RSTMON is 32-bit packed with global numbering = RST global - 15
   * (see rzv_cpg_wait_rstmon) — NOT the RST register index.
   */

  ret = rzv_cpg_wait_rstmon(gstart, 2, assert_rst,
                            assert_rst ? CPG_TIMEOUT_RESET_ASSERT :
                                         CPG_TIMEOUT_RESET_RELEASE);
  if (ret < 0)
    {
      clkerr("ERROR: SCI%d reset %s failed: RSTMON r=%u..%u\n",
             ch, assert_rst ? "assert" : "release",
             (unsigned int)gstart, (unsigned int)(gstart + 1));
      rzv_cpg_dump_registers(gstart / 16u, RZV_CPG_DUMP_NONE, 0,
                             gstart, 2, "sci_reset_ctrl_failure");
      return ret;
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_gpt_clock_ctrl
 ****************************************************************************/

static int rzv_gpt_clock_ctrl(unsigned int unit, bool enable)
{
  uint32_t clkon_bit = RZV_GPT_CLKON_BIT(unit);
  uint32_t clkmon_bit = RZV_GPT_CLKMON_BIT(unit);
  uint32_t mask = (clkon_bit << 16) | (enable ? clkon_bit : 0u);
  irqstate_t flags;
  int ret;
  int retry;

  for (retry = 0; retry <= CPG_MAX_RETRIES; retry++)
    {
      flags = enter_critical_section();
      rzv_cpg_putreg(mask, RZV_CPG_CLKON(3));
      leave_critical_section(flags);

      ret = rzv_cpg_wait_bit(RZV_CPG_CLKMON(1), clkmon_bit, enable,
                             enable ? CPG_TIMEOUT_CLOCK_ENABLE :
                                      CPG_TIMEOUT_CLOCK_DISABLE);
      if (ret >= 0)
        {
          return OK;
        }

      if (retry < CPG_MAX_RETRIES)
        {
          up_udelay(CPG_RETRY_DELAY_US << retry);
        }
    }

  clkerr("ERROR: GPT unit %u clock %s failed\n", unit,
         enable ? "enable" : "disable");
  return ret;
}

/****************************************************************************
 * Name: rzv_gpt_module_start
 ****************************************************************************/

int rzv_gpt_module_start(unsigned int channel)
{
  unsigned int unit;
  uint32_t mstop_bit;
  uint32_t reset_bit;
  irqstate_t flags;
  int ret;
  int retry;

  if (!RZV_GPT_LOGICAL_CHANNEL_VALID(channel))
    {
      return -EINVAL;
    }

  unit = channel / 8u;

  /* Claim the unit before touching CPG so a shutdown of another channel in
   * the same unit cannot gate the clock while this start is in progress. */

  flags = enter_critical_section();
  g_rzv_gpt_unit_users[unit]++;
  leave_critical_section(flags);

  ret = rzv_gpt_clock_ctrl(unit, true);
  if (ret < 0)
    {
      goto errout;
    }

  mstop_bit = RZV_GPT_MSTOP_BIT(unit);
  flags = enter_critical_section();
  rzv_cpg_putreg(mstop_bit << 16, RZV_CPG_BUS_6_MSTOP);
  (void)rzv_cpg_getreg(RZV_CPG_BUS_6_MSTOP);
  leave_critical_section(flags);

  reset_bit = RZV_GPT_RST_BIT(unit);
  for (retry = 0; retry <= CPG_MAX_RETRIES; retry++)
    {
      flags = enter_critical_section();
      rzv_cpg_putreg((reset_bit << 16) | reset_bit, RZV_CPG_RST(5));
      leave_critical_section(flags);

      ret = rzv_cpg_wait_bit(RZV_CPG_RSTMON(2), RZV_GPT_RSTMON_BIT(unit),
                             false, CPG_TIMEOUT_RESET_RELEASE);
      if (ret >= 0)
        {
          return OK;
        }

      if (retry < CPG_MAX_RETRIES)
        {
          up_udelay(CPG_RETRY_DELAY_US << retry);
        }
    }

  clkerr("ERROR: GPT unit %u reset release failed\n", unit);

errout:
  flags = enter_critical_section();
  g_rzv_gpt_unit_users[unit]--;
  leave_critical_section(flags);

  return ret;
}

/****************************************************************************
 * Name: rzv_gpt_module_stop
 ****************************************************************************/

int rzv_gpt_module_stop(unsigned int channel)
{
  unsigned int unit;
  irqstate_t flags;

  if (!RZV_GPT_LOGICAL_CHANNEL_VALID(channel))
    {
      return -EINVAL;
    }

  unit = channel / 8u;
  flags = enter_critical_section();
  if (g_rzv_gpt_unit_users[unit] > 0)
    {
      g_rzv_gpt_unit_users[unit]--;
    }
  leave_critical_section(flags);

  return OK;
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
  uint32_t mon_lsb;
  uint32_t mon_n;
  uintptr_t clkon_addr = RZV_CPG_CLKON(domain);
  irqstate_t flags;
  int ret;
  int retry;
  uint32_t delay_us;
  int sci_ch = rzv_cpg_sci_channel(clk_id);

  /* RSCI: five gate bits spanning CLKON_5..8 — handled by the SCI helper */

  if (sci_ch >= 0)
    {
      return rzv_cpg_sci_clock_ctrl(sci_ch, true);
    }

  /* DMAC uses a 5-bit mask (CLK0-CLK4 all required).
   * DMAC CPG_CLKON_0 bits [4:0] are all required per RZ/V2H UM CPG §CLKON.
   * ADC also needs a 2-bit pair (CLK0+CLK1). */

  if (clk_id == RZV_CPG_CLK_DMAC)
    {
      /* DMAC gate: 5-bit mask [4:0] — all five DMA unit clocks together */

      mask    = (0x1fu << 16) | 0x1fu;  /* WEN[20:16] + ON[4:0] */
      mon_lsb = 0;
      mon_n   = 5;
    }
  else if (clk_id == RZV_CPG_CLK_CANFD)
    {
      /* CAN-FD gate: 3-bit field CLK12/13/14 in CPG_CLKON_9 per RZ/V2H UM.
       * global + ch0 + ch1 clocks all required.
       * bit==12, span 3 bits → bits[14:12].
       */

      mask    = (0x7u << (bit + 16)) | (0x7u << bit);
      mon_lsb = bit;
      mon_n   = 3;
    }
  else if (clk_id == RZV_CPG_CLK_SPI0 ||
           clk_id == RZV_CPG_CLK_SPI1 ||
           clk_id == RZV_CPG_CLK_SPI2)
    {
      /* RSPI gate: 3-bit group in CPG_CLKON_5 (7U << (CLK4 + 3*ch)); all
       * three clocks of the channel are required.  bit is the group base.
       */

      mask    = (0x7u << (bit + 16)) | (0x7u << bit);
      mon_lsb = bit;
      mon_n   = 3;
    }
  else if (domain == RZV_CPG_DOMAIN(RZV_CPG_CLK_ADC0))
    {
      /* ADC gate: 2-bit pair [8:7] — both clocks must be set. */

      mask    = (0x3u << (bit + 16)) | (0x3u << bit);
      mon_lsb = bit;
      mon_n   = 2;
    }
  else
    {
      mask    = (1u << (bit + 16)) | (1u << bit);
      mon_lsb = bit;
      mon_n   = 1;
    }

  for (retry = 0; retry <= CPG_MAX_RETRIES; retry++)
    {
      if (retry > 0)
        {
          delay_us = CPG_RETRY_DELAY_US << (retry - 1);
          clkinfo("Retrying clock enable (attempt %d/%d) after %uµs\n",
                  retry + 1, CPG_MAX_RETRIES + 1, (unsigned int)delay_us);
          up_udelay(delay_us);
        }

      /* write under CS, poll OUTSIDE CS so HRT ISR not blocked.
       * CPG write-enable gating makes concurrent per-bit writes safe. */

      flags = enter_critical_section();
      rzv_cpg_putreg(mask, clkon_addr);
      leave_critical_section(flags);

      /* Poll with IRQs enabled — timeout.  CLKMON is 32-bit packed with
       * the same global numbering as CLKON (16*domain + bit); see
       * rzv_cpg_wait_clkmon.
       */

      ret = rzv_cpg_wait_clkmon(domain * 16u + mon_lsb, mon_n, true,
                                CPG_TIMEOUT_CLOCK_ENABLE);
      if (ret >= 0)
        {
          /* Release the module's bus-interface MSTOP where mapped (see
           * g_rzv_mstop_map).  RSCI/DMAC/GPT own dedicated release paths.
           */

          rzv_cpg_mstop_release(clk_id);

          clkinfo("Clock enabled: domain=%u bit=%u\n", (unsigned int)domain, (unsigned int)bit);
          return OK;
        }
    }

  clkerr("ERROR: Clock enable failed after %d attempts: domain=%u bit=%u\n",
         CPG_MAX_RETRIES + 1, (unsigned int)domain, (unsigned int)bit);
  rzv_cpg_dump_registers(domain, domain * 16u + mon_lsb, mon_n,
                         RZV_CPG_DUMP_NONE, 0, "clock_enable_failure");

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
  uint32_t mon_lsb;
  uint32_t mon_n;
  uintptr_t clkon_addr = RZV_CPG_CLKON(domain);
  irqstate_t flags;
  int ret;
  int retry;
  uint32_t delay_us;
  int sci_ch = rzv_cpg_sci_channel(clk_id);

  /* RSCI: five gate bits spanning CLKON_5..8 — handled by the SCI helper */

  if (sci_ch >= 0)
    {
      return rzv_cpg_sci_clock_ctrl(sci_ch, false);
    }

  /* match 2-bit/5-bit pairs used in enable */

  if (clk_id == RZV_CPG_CLK_DMAC)
    {
      mask    = 0x1fu << 16;  /* WEN[20:16] only, ON[4:0]=0 → disable all 5 */
      mon_lsb = 0;
      mon_n   = 5;
    }
  else if (domain == RZV_CPG_DOMAIN(RZV_CPG_CLK_ADC0))
    {
      mask    = 0x3u << (bit + 16);  /* Disable both ADC clock bits. */
      mon_lsb = bit;
      mon_n   = 2;
    }
  else if (clk_id == RZV_CPG_CLK_CANFD)
    {
      /* CAN-FD gate: 3-bit field CLK12/13/14 — write-enable upper half,
       * data bits 0 → gate off all three clocks.
       * Symmetric to rzv_clock_enable CAN-FD case.
       */

      mask    = (0x7u << (bit + 16)) | (0x0u << bit);
      mon_lsb = bit;
      mon_n   = 3;
    }
  else if (clk_id == RZV_CPG_CLK_SPI0 ||
           clk_id == RZV_CPG_CLK_SPI1 ||
           clk_id == RZV_CPG_CLK_SPI2)
    {
      /* RSPI gate: 3-bit group in CPG_CLKON_5 — write-enable upper half,
       * data 0 → gate off all three channel clocks.  Symmetric to enable.
       */

      mask    = (0x7u << (bit + 16));
      mon_lsb = bit;
      mon_n   = 3;
    }
  else
    {
      mask    = (1u << (bit + 16));  /* write-enable only, ON=0 */
      mon_lsb = bit;
      mon_n   = 1;
    }

  for (retry = 0; retry <= CPG_MAX_RETRIES; retry++)
    {
      if (retry > 0)
        {
          delay_us = CPG_RETRY_DELAY_US << (retry - 1);
          clkinfo("Retrying clock disable (attempt %d/%d) after %uµs\n",
                  retry + 1, CPG_MAX_RETRIES + 1, (unsigned int)delay_us);
          up_udelay(delay_us);
        }

      /* write under CS, poll outside */

      flags = enter_critical_section();
      rzv_cpg_putreg(mask, clkon_addr);
      leave_critical_section(flags);

      ret = rzv_cpg_wait_clkmon(domain * 16u + mon_lsb, mon_n, false,
                                CPG_TIMEOUT_CLOCK_DISABLE);
      if (ret >= 0)
        {
          clkinfo("Clock disabled: domain=%u bit=%u\n", (unsigned int)domain, (unsigned int)bit);
          return OK;
        }
    }

  clkerr("ERROR: Clock disable failed after %d attempts: domain=%u bit=%u\n",
         CPG_MAX_RETRIES + 1, (unsigned int)domain, (unsigned int)bit);
  rzv_cpg_dump_registers(domain, domain * 16u + mon_lsb, mon_n,
                         RZV_CPG_DUMP_NONE, 0, "clock_disable_failure");

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
  irqstate_t flags;
  int ret;
  int retry;
  uint32_t delay_us;
  int sci_ch = rzv_cpg_sci_channel(clk_id);

  /* RSCI: SCIP+SCIT resets in CPG_RST_8/9 — handled by the SCI helper */

  if (sci_ch >= 0)
    {
      return rzv_cpg_sci_reset_ctrl(sci_ch, true);
    }

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
  else if (clk_id == RZV_CPG_CLK_ADC0)
    {
      domain  = 15;
      bitmask = (1u << 6);
    }
  else if (clk_id >= RZV_CPG_CLK_GTM0 && clk_id <= RZV_CPG_CLK_GTM7)
    {
      /* GTM reset bank differs from its CPG_CLKON_4 clock bank.  Per FSP
       * BSP_RST_*_FSP_IP_GTM: ch<3 -> CPG_RST_6 RSTB(13+ch);
       * ch>=3 -> CPG_RST_7 RSTB(ch-3).  ch = CLKON bit - 3 (base CLK3).
       * RSTMON cross-checks under the wait_rstmon global scheme (GTM0 ->
       * RSTMON_2 bit30, GTM7 -> RSTMON_3 bit5).
       */

      uint32_t gch = RZV_CPG_BIT(clk_id) - 3u;
      if (gch < 3u)
        {
          domain  = 6;
          bitmask = 1u << (13u + gch);
        }
      else
        {
          domain  = 7;
          bitmask = 1u << (gch - 3u);
        }
    }
  else if (clk_id == RZV_CPG_CLK_SPI0 || clk_id == RZV_CPG_CLK_SPI1)
    {
      /* RSPI reset: RSPIP + RSPIT are adjacent in CPG_RST_7.  ch =
       * (CLKON bit - 4)/3; bits = RSTB(11+2*ch)..RSTB(12+2*ch).
       * SPI0 -> RST_7 b11-12, SPI1 -> b13-14.  RSTMON cross-checks:
       * SPI0 -> RSTMON_3 b12-13, SPI1 -> b14-15.  (SPI2's RSPIT is in
       * CPG_RST_8 and is not handled by this single-register override.)
       */

      uint32_t sch = (RZV_CPG_BIT(clk_id) - 4u) / 3u;
      domain  = 7;
      bitmask = 0x3u << (11u + 2u * sch);
    }
  else if (clk_id == RZV_CPG_CLK_ICU)
    {
      /* ICU reset bank differs from its CPG_CLKON_0 clock bank: FSP
       * CPG_RST_ICU_0_PRESETN_I = CPG_RST_3 bit 6.  RSTMON cross-check
       * under the wait_rstmon global scheme: RST_3 b6 -> RSTMON_1 b7.
       */

      domain  = 3;
      bitmask = 1u << 6;
    }

  mrst_addr = RZV_CPG_RST(domain);

  for (retry = 0; retry <= CPG_MAX_RETRIES; retry++)
    {
      if (retry > 0)
        {
          delay_us = CPG_RETRY_DELAY_US << (retry - 1);
          clkinfo("Retrying reset assert (attempt %d/%d) after %uµs\n",
                  retry + 1, CPG_MAX_RETRIES + 1, (unsigned int)delay_us);
          up_udelay(delay_us);
        }

      /* Assert reset: WEN only, control=0 → reset asserted.
       * write under CS, poll outside. */

      mask = (bitmask << 16);
      flags = enter_critical_section();
      rzv_cpg_putreg(mask, mrst_addr);
      leave_critical_section(flags);

      /* Wait until RSTMON bit(s) SET (= reset asserted/propagated).
       * RSTMON polarity per FSP bsp_clocks.h (RZ/V2H): 1 = in reset,
       * 0 = released.  (FSP's R_BSP_MODULE_RSTON does not poll; polling for
       * the asserted state here is a harmless, more conservative confirm.)
       * use per-op timeout CPG_TIMEOUT_RESET_ASSERT. */

      ret = rzv_cpg_wait_rstmon(domain * 16u +
                                (uint32_t)__builtin_ctz(bitmask),
                                (uint32_t)__builtin_popcount(bitmask), true,
                                CPG_TIMEOUT_RESET_ASSERT);
      if (ret >= 0)
        {
          clkinfo("Reset asserted: domain=%u mask=0x%x\n",
                  (unsigned int)domain, (unsigned int)bitmask);
          return OK;
        }
    }

  clkerr("ERROR: Reset assert failed after %d attempts: domain=%u mask=0x%x\n",
         CPG_MAX_RETRIES + 1, (unsigned int)domain, (unsigned int)bitmask);
  rzv_cpg_dump_registers(domain, RZV_CPG_DUMP_NONE, 0,
                         domain * 16u + (uint32_t)__builtin_ctz(bitmask),
                         (uint32_t)__builtin_popcount(bitmask),
                         "reset_assert_failure");

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
  irqstate_t flags;
  int ret;
  int retry;
  uint32_t delay_us;
  int sci_ch = rzv_cpg_sci_channel(clk_id);

  /* RSCI: SCIP+SCIT resets in CPG_RST_8/9 — handled by the SCI helper */

  if (sci_ch >= 0)
    {
      return rzv_cpg_sci_reset_ctrl(sci_ch, false);
    }

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
  else if (clk_id == RZV_CPG_CLK_ADC0)
    {
      domain  = 15;
      bitmask = (1u << 6);
    }
  else if (clk_id >= RZV_CPG_CLK_GTM0 && clk_id <= RZV_CPG_CLK_GTM7)
    {
      /* GTM reset bank differs from its CPG_CLKON_4 clock bank.  Per FSP
       * BSP_RST_*_FSP_IP_GTM: ch<3 -> CPG_RST_6 RSTB(13+ch);
       * ch>=3 -> CPG_RST_7 RSTB(ch-3).  ch = CLKON bit - 3 (base CLK3).
       * RSTMON cross-checks under the wait_rstmon global scheme (GTM0 ->
       * RSTMON_2 bit30, GTM7 -> RSTMON_3 bit5).
       */

      uint32_t gch = RZV_CPG_BIT(clk_id) - 3u;
      if (gch < 3u)
        {
          domain  = 6;
          bitmask = 1u << (13u + gch);
        }
      else
        {
          domain  = 7;
          bitmask = 1u << (gch - 3u);
        }
    }
  else if (clk_id == RZV_CPG_CLK_SPI0 || clk_id == RZV_CPG_CLK_SPI1)
    {
      /* RSPI reset: RSPIP + RSPIT are adjacent in CPG_RST_7.  ch =
       * (CLKON bit - 4)/3; bits = RSTB(11+2*ch)..RSTB(12+2*ch).
       * SPI0 -> RST_7 b11-12, SPI1 -> b13-14.  RSTMON cross-checks:
       * SPI0 -> RSTMON_3 b12-13, SPI1 -> b14-15.  (SPI2's RSPIT is in
       * CPG_RST_8 and is not handled by this single-register override.)
       */

      uint32_t sch = (RZV_CPG_BIT(clk_id) - 4u) / 3u;
      domain  = 7;
      bitmask = 0x3u << (11u + 2u * sch);
    }
  else if (clk_id == RZV_CPG_CLK_ICU)
    {
      /* ICU reset bank differs from its CPG_CLKON_0 clock bank: FSP
       * CPG_RST_ICU_0_PRESETN_I = CPG_RST_3 bit 6.  RSTMON cross-check
       * under the wait_rstmon global scheme: RST_3 b6 -> RSTMON_1 b7.
       */

      domain  = 3;
      bitmask = 1u << 6;
    }

  mrst_addr = RZV_CPG_RST(domain);

  for (retry = 0; retry <= CPG_MAX_RETRIES; retry++)
    {
      if (retry > 0)
        {
          delay_us = CPG_RETRY_DELAY_US << (retry - 1);
          clkinfo("Retrying reset release (attempt %d/%d) after %uµs\n",
                  retry + 1, CPG_MAX_RETRIES + 1, (unsigned int)delay_us);
          up_udelay(delay_us);
        }

      /* Deassert reset: WEN + control=1 → reset released.
       * write under CS, poll outside.
       * RSTMON polarity per FSP bsp_clocks.h R_BSP_MODULE_RSTOFF (RZ/V2H):
       * after deassert, wait for RSTMON bit == 0 (released).  The earlier
       * "wait for RSTMON==1" convention was inverted vs the FSP reference and
       * caused a spurious CPG_TIMEOUT_RESET_RELEASE spin on every unreset. */

      mask = (bitmask << 16) | bitmask;
      flags = enter_critical_section();
      rzv_cpg_putreg(mask, mrst_addr);
      leave_critical_section(flags);

      /* use per-op timeout CPG_TIMEOUT_RESET_RELEASE */

      ret = rzv_cpg_wait_rstmon(domain * 16u +
                                (uint32_t)__builtin_ctz(bitmask),
                                (uint32_t)__builtin_popcount(bitmask), false,
                                CPG_TIMEOUT_RESET_RELEASE);
      if (ret >= 0)
        {
          clkinfo("Reset deasserted: domain=%u mask=0x%x\n",
                  (unsigned int)domain, (unsigned int)bitmask);
          return OK;
        }
    }

  clkerr("ERROR: Reset release failed after %d attempts: domain=%u mask=0x%x\n",
         CPG_MAX_RETRIES + 1, (unsigned int)domain, (unsigned int)bitmask);
  rzv_cpg_dump_registers(domain, RZV_CPG_DUMP_NONE, 0,
                         domain * 16u + (uint32_t)__builtin_ctz(bitmask),
                         (uint32_t)__builtin_popcount(bitmask),
                         "reset_release_failure");

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
          ch, (unsigned int)clk_ids[ch]);

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
          ch, (unsigned int)rst_ids[ch]);

  return rzv_module_unreset(rst_ids[ch]);
}

/****************************************************************************
 * Name: rzv_get_pclk_frequency
 *
 * Description:
 *   Get P0CLK frequency (100 MHz).  Use only for P0CLK peripherals (OSTM,
 *   GTM, WDT).  SPI and GPT require P4CLK (200 MHz) — use
 *   rzv_get_p4clk_frequency() or rzv_clock_get_rate(RZV_CLOCK_P4CLK).
 * callers that assumed this returns a generic "pclk"
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
 * added to prevent callers from erroneously using
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

#if defined(CONFIG_RZV2H_BUILD_CM33)
static void rzv_pll_init(void)
{
  uint32_t pll_mon;
  uintptr_t pll_stby;
  uintptr_t pll_mon_addr;
  const uint32_t pll_lock_mask = 0x11;  /* RESETB_Msk(0x1)|LOCK_Msk(0x10) */
  int timeout;

  clkinfo("Initializing PLLs...\n");

  /* PLLCM33 init under CONFIG_RZV2H_BUILD_CM33.
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

  /* PLL init order = PLLCLN→PLLDTY→PLLCA55→PLLVDO→PLLETH→
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

  /* PLLDDR0/1 init gated under Kconfig.
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
#endif

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
  /* Decode the live CR8 CPU-clock (I6CLK) divider so g_clock_freq[] reflects
   * the actual hardware state rather than the compile-time 800 MHz assumption.
   *
   * On R9A09G057H the CR8 clock is PLLDTY (1.6 GHz) divided by CDDIV2.DIVCTL1.
   * Field position and encoding are verified against the RZ/V2H CMSIS headers,
   * not guessed:
   *   - cpg_iodefine.h CPG_CDDIV2_b: DIVCTL1 = bits[6:4]
   *   - bsp_clocks.h BSP_CLOCKS_PLLDTY_CR8_DIV_*: 0=>/2, 1=>/4, 2=>/8,
   *     3=>/16, 4=>/64  (FSP default /2 => 800 MHz)
   * DIVCTL1 == 0 is both the cold-reset value and the FSP /2 setting, so it
   * unambiguously yields 800 MHz.  A reserved code keeps the default.
   *
   * NuttX only reads these dividers (TF-A/the loader programs them), so no RMW
   * or CPG lock is needed here.
   */

  uint32_t cddiv2;
  uint32_t divctl1;
  uint32_t divider;

  cddiv2  = rzv_cpg_getreg(RZV_CPG_CDDIV(2));
  divctl1 = (cddiv2 >> 4) & 0x7;

  switch (divctl1)
    {
      case 0:  divider = 2;  break;
      case 1:  divider = 4;  break;
      case 2:  divider = 8;  break;
      case 3:  divider = 16; break;
      case 4:  divider = 64; break;
      default: divider = 0;  break;  /* reserved -> keep compile-time default */
    }

  if (divider != 0)
    {
      g_i6clk_actual_hz = RZV_CLOCK_PLLDTYCLK_HZ / divider;

      /* If the frequency table was already built (lazy path), update it now;
       * otherwise rzv_clock_init_frequency_table() applies the override.
       */

      if (g_clock_freq_valid)
        {
          g_clock_freq[RZV_CLOCK_I6CLK] = g_i6clk_actual_hz;
        }
    }

  clkinfo("CR8 I6CLK divider: CDDIV2=0x%08x DIVCTL1=%u -> /%u = %u Hz\n",
          (unsigned)cddiv2, (unsigned)divctl1, (unsigned)divider,
          (unsigned)g_i6clk_actual_hz);
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
  /* read back SSEL registers to verify bootloader configuration.
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
   * under !CONFIG_RZV_INIT_PLLDDR TF-A owns DDR; a
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
      clkerr("ERROR: PLLDDR0 not locked (mon=0x%08x)\n",
             (unsigned int)pll_mon);
      errors++;
#else
      clkinfo("PLLDDR0 not locked in verify (mon=0x%08x) — TF-A owns DDR\n",
              (unsigned int)pll_mon);
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
      clkerr("ERROR: PLLDDR1 not locked (mon=0x%08x)\n",
             (unsigned int)pll_mon);
      errors++;
#else
      clkinfo("PLLDDR1 not locked in verify (mon=0x%08x) — TF-A owns DDR\n",
              (unsigned int)pll_mon);
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

  /* Only the CM33 build programs the global PLLs; CR8 cores inherit the PLL
   * state set by the external loader or CM33.  Keep this selector symmetric
   * with the rzv_pll_init() definition guard (CONFIG_RZV2H_BUILD_CM33) so a
   * future build variant cannot fall through to an undefined rzv_pll_init().
   */
#if defined(CONFIG_RZV2H_BUILD_CR8_0) || defined(CONFIG_RZV2H_BUILD_CR8_1)
  clkinfo("CR8 build: global PLL configuration owned by loader/CM33\n");
#elif defined(CONFIG_RZV2H_BUILD_CM33)
  rzv_pll_init();
#else
#  error "RZ/V2H build must select CR8_0, CR8_1, or CM33"
#endif

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

  /* warn if a valid clock_id maps to 0 Hz so callers
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
  /* was silently returning OK without doing anything.
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
  /* was silently returning OK without configuring CLMA registers.
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
  /* was silently returning OK without touching hardware.
   * current_freq==0 when clock_id unknown → 0*2==0 → any
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
  /* use 1u to avoid signed-int left-shift UB for bit>=16 */
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

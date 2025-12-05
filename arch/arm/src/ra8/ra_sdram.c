/****************************************************************************
 * arch/arm/src/ra8/ra_sdram.c
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

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>

#include "arm_internal.h"
#include "chip.h"
#include "hardware/ra_memorymap.h"
#include "hardware/ra_hardware.h"

#include "ra_sdram.h"

#ifdef CONFIG_DEBUG_SDRAM_ERROR
#  define sdramerr       _err
#else
#  define sdramerr      _none
#endif

#ifdef CONFIG_DEBUG_SDRAM_WARN
#  define sdramwarn     _warn
#else
#  define sdramwarn     _none
#endif

#ifdef CONFIG_DEBUG_SDRAM_INFO
#  define sdraminfo     _info
#else
#  define sdraminfo     _none
#endif


/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SDRAM Controller Register Base (within BUS peripheral) */

#define RA_SDRAM_BASE               (R_BUS_SDRAM)

/* SDRAM Register Offsets (relative to R_BUS_SDRAM) */

#define RA_SDRAM_SDCCR_OFFSET       0x00  /* SDC Control Register */
#define RA_SDRAM_SDCMOD_OFFSET      0x01  /* SDC Mode Register */
#define RA_SDRAM_SDAMOD_OFFSET      0x02  /* SDRAM Access Mode Register */
#define RA_SDRAM_SDSELF_OFFSET      0x10  /* SDRAM Self-Refresh Control Register */
#define RA_SDRAM_SDRFCR_OFFSET      0x14  /* SDRAM Refresh Control Register */
#define RA_SDRAM_SDRFEN_OFFSET      0x16  /* SDRAM Auto-Refresh Control Register */
#define RA_SDRAM_SDICR_OFFSET       0x20  /* SDRAM Initialization Control Register */
#define RA_SDRAM_SDIR_OFFSET        0x24  /* SDRAM Initialization Register */
#define RA_SDRAM_SDADR_OFFSET       0x40  /* SDRAM Address Register */
#define RA_SDRAM_SDTR_OFFSET        0x44  /* SDRAM Timing Register */
#define RA_SDRAM_SDMOD_OFFSET       0x48  /* SDRAM Mode Register */
#define RA_SDRAM_SDSR_OFFSET        0x50  /* SDRAM Status Register */

/* Register Addresses */

#define RA_SDRAM_SDCCR              (RA_SDRAM_BASE + RA_SDRAM_SDCCR_OFFSET)
#define RA_SDRAM_SDCMOD             (RA_SDRAM_BASE + RA_SDRAM_SDCMOD_OFFSET)
#define RA_SDRAM_SDAMOD             (RA_SDRAM_BASE + RA_SDRAM_SDAMOD_OFFSET)
#define RA_SDRAM_SDSELF             (RA_SDRAM_BASE + RA_SDRAM_SDSELF_OFFSET)
#define RA_SDRAM_SDRFCR             (RA_SDRAM_BASE + RA_SDRAM_SDRFCR_OFFSET)
#define RA_SDRAM_SDRFEN             (RA_SDRAM_BASE + RA_SDRAM_SDRFEN_OFFSET)
#define RA_SDRAM_SDICR              (RA_SDRAM_BASE + RA_SDRAM_SDICR_OFFSET)
#define RA_SDRAM_SDIR               (RA_SDRAM_BASE + RA_SDRAM_SDIR_OFFSET)
#define RA_SDRAM_SDADR              (RA_SDRAM_BASE + RA_SDRAM_SDADR_OFFSET)
#define RA_SDRAM_SDTR               (RA_SDRAM_BASE + RA_SDRAM_SDTR_OFFSET)
#define RA_SDRAM_SDMOD              (RA_SDRAM_BASE + RA_SDRAM_SDMOD_OFFSET)
#define RA_SDRAM_SDSR               (RA_SDRAM_BASE + RA_SDRAM_SDSR_OFFSET)

/* SDCCR - SDC Control Register */

#define SDCCR_EXENB                 (1 << 0)  /* Operation Enable */
#define SDCCR_BSIZE_SHIFT           4
#define SDCCR_BSIZE_MASK            (3 << SDCCR_BSIZE_SHIFT)
#define SDCCR_BSIZE_16BIT           (0 << SDCCR_BSIZE_SHIFT)
#define SDCCR_BSIZE_32BIT           (1 << SDCCR_BSIZE_SHIFT)
#define SDCCR_BSIZE_8BIT            (2 << SDCCR_BSIZE_SHIFT)

/* SDCMOD - SDC Mode Register */

#define SDCMOD_EMODE                (1 << 0)  /* Endian Mode */

/* SDAMOD - SDRAM Access Mode Register */

#define SDAMOD_BE                   (1 << 0)  /* Continuous Access Enable */

/* SDSELF - SDRAM Self-Refresh Control Register */

#define SDSELF_SFEN                 (1 << 0)  /* Self-Refresh Enable */

/* SDRFCR - SDRAM Refresh Control Register */

#define SDRFCR_RFC_SHIFT            0
#define SDRFCR_RFC_MASK             0xfff
#define SDRFCR_REFW_SHIFT           12
#define SDRFCR_REFW_MASK            (0xf << SDRFCR_REFW_SHIFT)

/* SDRFEN - SDRAM Auto-Refresh Control Register */

#define SDRFEN_RFEN                 (1 << 0)  /* Auto-Refresh Enable */

/* SDICR - SDRAM Initialization Sequence Control Register */

#define SDICR_INIRQ                 (1 << 0)  /* Initialization Sequence Start */

/* SDIR - SDRAM Initialization Register */

#define SDIR_ARFI_SHIFT             0
#define SDIR_ARFI_MASK              0xf
#define SDIR_ARFC_SHIFT             4
#define SDIR_ARFC_MASK              (0xf << SDIR_ARFC_SHIFT)
#define SDIR_PRC_SHIFT              8
#define SDIR_PRC_MASK               (0x7 << SDIR_PRC_SHIFT)

/* SDADR - SDRAM Address Register */

#define SDADR_MXC_SHIFT             0
#define SDADR_MXC_MASK              0x3

/* SDTR - SDRAM Timing Register */

#define SDTR_CL_SHIFT               0
#define SDTR_CL_MASK                0x7
#define SDTR_WR                     (1 << 8)
#define SDTR_RP_SHIFT               9
#define SDTR_RP_MASK                (0x7 << SDTR_RP_SHIFT)
#define SDTR_RCD_SHIFT              12
#define SDTR_RCD_MASK               (0x3 << SDTR_RCD_SHIFT)
#define SDTR_RAS_SHIFT              16
#define SDTR_RAS_MASK               (0x7 << SDTR_RAS_SHIFT)

/* SDMOD - SDRAM Mode Register */

#define SDMOD_MR_SHIFT              0
#define SDMOD_MR_MASK               0x7fff

/* Mode Register bits for SDRAM device */

#define MR_BURST_LENGTH_1           0
#define MR_BURST_TYPE_SEQUENTIAL    (0 << 3)
#define MR_CAS_LATENCY_SHIFT        4
#define MR_OP_MODE_STANDARD         (0 << 7)
#define MR_WB_SINGLE_LOC_ACC        (1 << 9)

/* SDSR - SDRAM Status Register */

#define SDSR_MRSST                  (1 << 0)  /* Mode Register Setting Status */
#define SDSR_INIST                  (1 << 3)  /* Initialization Status */
#define SDSR_SRFST                  (1 << 4)  /* Self-Refresh Status */

/* Register protection key */

#define PRCR_PRC1_UNLOCK            (R_SYSC_PRCR_S_KEY | 0x2)
#define PRCR_LOCK                   (R_SYSC_PRCR_S_KEY | 0x0)

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Default SDRAM configuration */

static const struct ra_sdram_config_s g_sdram_default_config =
{
  .bus_width   = CONFIG_RA_SDRAM_BUS_WIDTH,
  .endian_mode = CONFIG_RA_SDRAM_ENDIAN_MODE,
  .access_mode = CONFIG_RA_SDRAM_ACCESS_MODE,
  .mxc_shift   = CONFIG_RA_SDRAM_MXC_SHIFT,
  .tcl         = CONFIG_RA_SDRAM_TCL,
  .tras        = CONFIG_RA_SDRAM_TRAS,
  .trcd        = CONFIG_RA_SDRAM_TRCD,
  .trp         = CONFIG_RA_SDRAM_TRP,
  .twr         = CONFIG_RA_SDRAM_TWR,
  .trefw       = CONFIG_RA_SDRAM_TREFW,
  .trfc        = CONFIG_RA_SDRAM_TRFC,
  .init_arfi   = CONFIG_RA_SDRAM_INIT_ARFI,
  .init_arfc   = CONFIG_RA_SDRAM_INIT_ARFC,
  .init_prc    = CONFIG_RA_SDRAM_INIT_PRC,
};

/* Cached bus width for self-refresh operations */

static uint8_t g_sdram_bus_width = CONFIG_RA_SDRAM_BUS_WIDTH;

/* Initialization flag */

static bool g_sdram_initialized = false;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_sdram_wait_status_clear
 *
 * Description:
 *   Wait until all status bits in SDSR are cleared.
 *
 ****************************************************************************/

static void ra_sdram_wait_status_clear(void)
{
  while (getreg8(RA_SDRAM_SDSR) != 0)
    {
      /* Wait for all status bits to be cleared */
    }
}

/****************************************************************************
 * Name: ra_sdram_wait_init_complete
 *
 * Description:
 *   Wait until initialization sequence completes.
 *
 ****************************************************************************/

static void ra_sdram_wait_init_complete(void)
{
  while ((getreg8(RA_SDRAM_SDSR) & SDSR_INIST) != 0)
    {
      /* Wait for initialization to complete */
    }
}

/****************************************************************************
 * Name: ra_sdram_wait_mrs_complete
 *
 * Description:
 *   Wait until Mode Register Setting completes.
 *
 ****************************************************************************/

static void ra_sdram_wait_mrs_complete(void)
{
  while ((getreg8(RA_SDRAM_SDSR) & SDSR_MRSST) != 0)
    {
      /* Wait for MRS to complete */
    }
}

/****************************************************************************
 * Name: ra_sdram_enable_clock
 *
 * Description:
 *   Enable SDRAM clock output (SDCLK).
 *
 ****************************************************************************/

static void ra_sdram_enable_clock(void)
{
  /* Unlock register protection for CGC registers */

  putreg16(PRCR_PRC1_UNLOCK, R_SYSC_PRCR_S);

  /* Enable SDCLK output */

  putreg8(R_SYSC_SDCKOCR_SDCKOEN, R_SYSC_SDCKOCR);

  /* Lock register protection */

  putreg16(PRCR_LOCK, R_SYSC_PRCR_S);
}

/****************************************************************************
 * Name: ra_sdram_get_bsize
 *
 * Description:
 *   Convert bus width config to SDCCR BSIZE value.
 *
 ****************************************************************************/

static uint8_t ra_sdram_get_bsize(uint8_t bus_width)
{
  switch (bus_width)
    {
      case RA_SDRAM_BUS_WIDTH_8BIT:
        return SDCCR_BSIZE_8BIT;

      case RA_SDRAM_BUS_WIDTH_16BIT:
        return SDCCR_BSIZE_16BIT;

      case RA_SDRAM_BUS_WIDTH_32BIT:
      default:
        return SDCCR_BSIZE_32BIT;
    }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_sdram_initialize
 *
 * Description:
 *   Initialize the SDRAM controller and external SDRAM memory.
 *
 ****************************************************************************/

int ra_sdram_initialize(const struct ra_sdram_config_s *config,
                        bool init_memory)
{
  const struct ra_sdram_config_s *cfg;
  uint32_t sdir_val;
  uint32_t sdtr_val;
  uint32_t sdrfcr_val;
  uint16_t sdmod_val;
  uint8_t bsize;
  irqstate_t flags;

  /* Use provided config or default */

  cfg = config ? config : &g_sdram_default_config;

  /* Save bus width for later use in self-refresh operations */

  g_sdram_bus_width = cfg->bus_width;
  bsize = ra_sdram_get_bsize(cfg->bus_width);

  /* Disable interrupts during initialization */

  flags = enter_critical_section();

  /* Step 1: Wait for all status bits in SDSR to be 0 */

  ra_sdram_wait_status_clear();

  /* Step 2: Set initialization parameters in SDIR
   * Note: Must only write to SDIR once after reset.
   */

  sdir_val = ((cfg->init_arfi - 3) << SDIR_ARFI_SHIFT) |
             (cfg->init_arfc << SDIR_ARFC_SHIFT) |
             ((cfg->init_prc - 3) << SDIR_PRC_SHIFT);
  putreg16((uint16_t)sdir_val, RA_SDRAM_SDIR);

  /* Step 3: Set SDRAM bus width in SDCCR (without enabling access) */

  putreg8(bsize, RA_SDRAM_SDCCR);

  if (init_memory)
    {
      /* Step 4: Enable SDCLK output */

      ra_sdram_enable_clock();

      /* Step 5: Start SDRAM initialization sequence */

      putreg8(SDICR_INIRQ, RA_SDRAM_SDICR);

      /* Wait for initialization to complete */

      ra_sdram_wait_init_complete();
    }

  /* Step 6: Configure SDRAM controller settings */

  /* Set access mode (continuous/single) */

  putreg8(cfg->access_mode ? SDAMOD_BE : 0, RA_SDRAM_SDAMOD);

  /* Set endian mode */

  putreg8(cfg->endian_mode ? SDCMOD_EMODE : 0, RA_SDRAM_SDCMOD);

  /* Wait for status clear before SDMOD modification */

  ra_sdram_wait_status_clear();

  if (init_memory)
    {
      /* Step 7: Program SDRAM Mode Register via SDMOD
       * Using LMR (Load Mode Register) command
       */

      sdmod_val = (MR_WB_SINGLE_LOC_ACC) |
                  (MR_OP_MODE_STANDARD) |
                  (cfg->tcl << MR_CAS_LATENCY_SHIFT) |
                  (MR_BURST_TYPE_SEQUENTIAL) |
                  (MR_BURST_LENGTH_1);
      putreg16(sdmod_val, RA_SDRAM_SDMOD);

      /* Wait for MRS to complete (tMRD) */

      ra_sdram_wait_mrs_complete();
    }

  /* Step 8: Set timing parameters in SDTR (must do in single write) */

  sdtr_val = ((cfg->tras - 1) << SDTR_RAS_SHIFT) |
             ((cfg->trcd - 1) << SDTR_RCD_SHIFT) |
             ((cfg->trp - 1) << SDTR_RP_SHIFT) |
             ((cfg->twr - 1) ? SDTR_WR : 0) |
             (cfg->tcl << SDTR_CL_SHIFT);
  putreg32(sdtr_val, RA_SDRAM_SDTR);

  /* Step 9: Set row address offset for target SDRAM */

  putreg8(cfg->mxc_shift & SDADR_MXC_MASK, RA_SDRAM_SDADR);

  /* Step 10: Set Auto-Refresh timings */

  sdrfcr_val = ((cfg->trefw - 1) << SDRFCR_REFW_SHIFT) |
               ((cfg->trfc - 1) & SDRFCR_RFC_MASK);
  putreg16((uint16_t)sdrfcr_val, RA_SDRAM_SDRFCR);

  /* Step 11: Start Auto-refresh */

  putreg8(SDRFEN_RFEN, RA_SDRAM_SDRFEN);

  if (init_memory)
    {
      /* Step 12: Enable SDRAM access */

      putreg8(SDCCR_EXENB | bsize, RA_SDRAM_SDCCR);

      g_sdram_initialized = true;

      sdraminfo("SDRAM initialized: bus_width=%d, tcl=%d, tras=%d\n",
              cfg->bus_width == RA_SDRAM_BUS_WIDTH_32BIT ? 32 :
              cfg->bus_width == RA_SDRAM_BUS_WIDTH_16BIT ? 16 : 8,
              cfg->tcl, cfg->tras);
    }
  else
    {
      /* Not initializing memory, enter self-refresh mode */

      while ((getreg8(RA_SDRAM_SDCCR) & SDCCR_EXENB) ||
             (getreg8(RA_SDRAM_SDSR) != 0))
        {
          /* Wait for access to be disabled and no status bits set */
        }

      /* Enable self-refresh mode */

      putreg8(SDSELF_SFEN, RA_SDRAM_SDSELF);
    }

  leave_critical_section(flags);

  return OK;
}

/****************************************************************************
 * Name: ra_sdram_selfrefresh_enable
 *
 * Description:
 *   Enable SDRAM self-refresh mode.
 *
 ****************************************************************************/

int ra_sdram_selfrefresh_enable(void)
{
  irqstate_t flags;
  uint8_t bsize;

  if (!g_sdram_initialized)
    {
      return -ENODEV;
    }

  flags = enter_critical_section();

  bsize = ra_sdram_get_bsize(g_sdram_bus_width);

  /* Disable SDRAM access (clear EXENB, keep BSIZE) */

  putreg8(bsize, RA_SDRAM_SDCCR);

  /* Wait for access to be disabled and all status bits cleared */

  while ((getreg8(RA_SDRAM_SDCCR) & SDCCR_EXENB) ||
         (getreg8(RA_SDRAM_SDSR) != 0))
    {
      /* Wait */
    }

  /* Enable self-refresh mode */

  putreg8(SDSELF_SFEN, RA_SDRAM_SDSELF);

  leave_critical_section(flags);

  sdraminfo("SDRAM entered self-refresh mode\n");

  return OK;
}

/****************************************************************************
 * Name: ra_sdram_selfrefresh_disable
 *
 * Description:
 *   Disable SDRAM self-refresh mode.
 *
 ****************************************************************************/

int ra_sdram_selfrefresh_disable(void)
{
  irqstate_t flags;
  uint8_t bsize;
  uint8_t sdckocr;

  if (!g_sdram_initialized)
    {
      return -ENODEV;
    }

  flags = enter_critical_section();

  /* Check if SDCLK is enabled, re-enable if needed
   * (may not be enabled if recovering from Deep Software Standby)
   */

  sdckocr = getreg8(R_SYSC_SDCKOCR);
  if ((sdckocr & R_SYSC_SDCKOCR_SDCKOEN) == 0)
    {
      ra_sdram_enable_clock();
    }

  /* Wait for all status bits to be cleared */

  ra_sdram_wait_status_clear();

  /* Disable self-refresh mode */

  putreg8(0, RA_SDRAM_SDSELF);

  /* Re-enable SDRAM bus access */

  bsize = ra_sdram_get_bsize(g_sdram_bus_width);
  putreg8(SDCCR_EXENB | bsize, RA_SDRAM_SDCCR);

  leave_critical_section(flags);

  sdraminfo("SDRAM exited self-refresh mode\n");

  return OK;
}

/****************************************************************************
 * Name: ra_sdram_is_initialized
 *
 * Description:
 *   Check if SDRAM has been initialized.
 *
 ****************************************************************************/

bool ra_sdram_is_initialized(void)
{
  return g_sdram_initialized;
}

/****************************************************************************
 * Name: ra_sdram_test
 *
 * Description:
 *   Perform a basic read/write test on SDRAM memory.
 *
 ****************************************************************************/

#ifdef CONFIG_RA_SDRAM_TEST
int ra_sdram_test(uintptr_t base, size_t size)
{
  volatile uint32_t *ptr;
  uint32_t pattern;
  uint32_t readback;
  size_t i;
  size_t count;

  if (!g_sdram_initialized)
    {
      merr("SDRAM not initialized\n");
      return -ENODEV;
    }

  count = size / sizeof(uint32_t);
  ptr = (volatile uint32_t *)base;

  sdraminfo("SDRAM test: base=0x%08lx, size=%zu\n",
          (unsigned long)base, size);

  /* Test 1: Walking ones pattern */

  sdraminfo("  Walking ones test...\n");
  for (i = 0; i < count && i < 32; i++)
    {
      pattern = 1u << i;
      ptr[i] = pattern;
    }

  for (i = 0; i < count && i < 32; i++)
    {
      pattern = 1u << i;
      readback = ptr[i];
      if (readback != pattern)
        {
          merr("SDRAM test failed at offset %zu: "
               "wrote 0x%08lx, read 0x%08lx\n",
               i * sizeof(uint32_t),
               (unsigned long)pattern,
               (unsigned long)readback);
          return -EIO;
        }
    }

  /* Test 2: Address as data pattern */

  sdraminfo("  Address test...\n");
  for (i = 0; i < count; i++)
    {
      ptr[i] = (uint32_t)(base + i * sizeof(uint32_t));
    }

  for (i = 0; i < count; i++)
    {
      pattern = (uint32_t)(base + i * sizeof(uint32_t));
      readback = ptr[i];
      if (readback != pattern)
        {
          merr("SDRAM test failed at offset %zu: "
               "wrote 0x%08lx, read 0x%08lx\n",
               i * sizeof(uint32_t),
               (unsigned long)pattern,
               (unsigned long)readback);
          return -EIO;
        }
    }

  /* Test 3: Inverse address pattern */

  sdraminfo("  Inverse address test...\n");
  for (i = 0; i < count; i++)
    {
      ptr[i] = ~(uint32_t)(base + i * sizeof(uint32_t));
    }

  for (i = 0; i < count; i++)
    {
      pattern = ~(uint32_t)(base + i * sizeof(uint32_t));
      readback = ptr[i];
      if (readback != pattern)
        {
          merr("SDRAM test failed at offset %zu: "
               "wrote 0x%08lx, read 0x%08lx\n",
               i * sizeof(uint32_t),
               (unsigned long)pattern,
               (unsigned long)readback);
          return -EIO;
        }
    }

  sdraminfo("SDRAM test passed!\n");

  return OK;
}
#endif /* CONFIG_RA_SDRAM_TEST */

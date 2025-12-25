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
#include <nuttx/arch.h>
#include <nuttx/semaphore.h>

#include "arm_internal.h"
#include "chip.h"
#include "hardware/ra_memorymap.h"
#include "hardware/ra_hardware.h"
#include "hardware/ra8p1/ra_sdram.h"

#ifdef CONFIG_RA_DMAC
#include "ra_dmac.h"
#endif

#ifdef CONFIG_ARMV8M_DCACHE
#include <nuttx/cache.h>
#endif

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

#ifdef CONFIG_RA_DMAC
/* DMAC transfer state */

static ra_dmac_handle_t g_sdram_dma_handle = NULL;
static volatile bool g_sdram_dma_complete = false;
static sem_t g_sdram_dma_sem;
static bool g_sdram_dma_initialized = false;
static ra_sdram_dma_callback_t g_sdram_dma_user_callback = NULL;
static void *g_sdram_dma_user_arg = NULL;
static int g_sdram_dma_channel = -1;  /* Configured DMA channel */
static void *g_sdram_dma_read_dest = NULL;  /* Read destination for cache invalidation */
static size_t g_sdram_dma_read_length = 0;  /* Read length for cache invalidation */

#endif /* CONFIG_RA_DMAC */

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_sdram_wait_status_clear
 *
 * Description:
 *   Wait until all status bits in SDSR are cleared.
 *
 * Returned Value:
 *   OK on success; -ETIMEDOUT on timeout.
 *
 ****************************************************************************/

static int ra_sdram_wait_status_clear(void)
{
  uint32_t timeout = RA_SDRAM_TIMEOUT_US / RA_SDRAM_POLL_DELAY_US;

  while (getreg8(RA_SDRAM_SDSR) != 0)
    {
      if (--timeout == 0)
        {
          sdramerr("ERROR: Timeout waiting for SDSR clear\n");
          return -ETIMEDOUT;
        }

      up_udelay(RA_SDRAM_POLL_DELAY_US);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_sdram_wait_init_complete
 *
 * Description:
 *   Wait until initialization sequence completes.
 *
 * Returned Value:
 *   OK on success; -ETIMEDOUT on timeout.
 *
 ****************************************************************************/

static int ra_sdram_wait_init_complete(void)
{
  uint32_t timeout = RA_SDRAM_TIMEOUT_US / RA_SDRAM_POLL_DELAY_US;

  while ((getreg8(RA_SDRAM_SDSR) & SDSR_INIST) != 0)
    {
      if (--timeout == 0)
        {
          sdramerr("ERROR: Timeout waiting for init complete\n");
          return -ETIMEDOUT;
        }

      up_udelay(RA_SDRAM_POLL_DELAY_US);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_sdram_wait_mrs_complete
 *
 * Description:
 *   Wait until Mode Register Setting completes.
 *
 * Returned Value:
 *   OK on success; -ETIMEDOUT on timeout.
 *
 ****************************************************************************/

static int ra_sdram_wait_mrs_complete(void)
{
  uint32_t timeout = RA_SDRAM_TIMEOUT_US / RA_SDRAM_POLL_DELAY_US;

  while ((getreg8(RA_SDRAM_SDSR) & SDSR_MRSST) != 0)
    {
      if (--timeout == 0)
        {
          sdramerr("ERROR: Timeout waiting for MRS complete\n");
          return -ETIMEDOUT;
        }

      up_udelay(RA_SDRAM_POLL_DELAY_US);
    }

  return OK;
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
  int ret;

  /* Use provided config or default */

  cfg = config ? config : &g_sdram_default_config;

  /* Save bus width for later use in self-refresh operations */

  g_sdram_bus_width = cfg->bus_width;
  bsize = ra_sdram_get_bsize(cfg->bus_width);

  /* Disable interrupts during initialization */

  flags = enter_critical_section();

  /* Step 1: Wait for all status bits in SDSR to be 0 */

  ret = ra_sdram_wait_status_clear();
  if (ret < 0)
    {
      leave_critical_section(flags);
      return ret;
    }

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

      ret = ra_sdram_wait_init_complete();
      if (ret < 0)
        {
          leave_critical_section(flags);
          return ret;
        }
    }

  /* Step 6: Configure SDRAM controller settings */

  /* Set access mode (continuous/single) */

  putreg8(cfg->access_mode ? SDAMOD_BE : 0, RA_SDRAM_SDAMOD);

  /* Set endian mode */

  putreg8(cfg->endian_mode ? SDCMOD_EMODE : 0, RA_SDRAM_SDCMOD);

  /* Wait for status clear before SDMOD modification */

  ret = ra_sdram_wait_status_clear();
  if (ret < 0)
    {
      leave_critical_section(flags);
      return ret;
    }

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

      ret = ra_sdram_wait_mrs_complete();
      if (ret < 0)
        {
          leave_critical_section(flags);
          return ret;
        }
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
  uint32_t timeout;
  int ret = OK;

  if (!g_sdram_initialized)
    {
      return -ENODEV;
    }

  flags = enter_critical_section();

  bsize = ra_sdram_get_bsize(g_sdram_bus_width);

  /* Disable SDRAM access (clear EXENB, keep BSIZE) */

  putreg8(bsize, RA_SDRAM_SDCCR);

  /* Wait for access to be disabled and all status bits cleared */

  timeout = RA_SDRAM_TIMEOUT_US / RA_SDRAM_POLL_DELAY_US;
  while ((getreg8(RA_SDRAM_SDCCR) & SDCCR_EXENB) ||
         (getreg8(RA_SDRAM_SDSR) != 0))
    {
      if (--timeout == 0)
        {
          sdramerr("ERROR: Timeout entering self-refresh\n");
          ret = -ETIMEDOUT;
          goto errout;
        }

      up_udelay(RA_SDRAM_POLL_DELAY_US);
    }

  /* Enable self-refresh mode */

  putreg8(SDSELF_SFEN, RA_SDRAM_SDSELF);

  sdraminfo("SDRAM entered self-refresh mode\n");

errout:
  leave_critical_section(flags);
  return ret;
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
  int ret;

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

  ret = ra_sdram_wait_status_clear();
  if (ret < 0)
    {
      leave_critical_section(flags);
      return ret;
    }

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

#ifdef CONFIG_RA_DMAC

/****************************************************************************
 * Name: ra_sdram_dma_callback
 *
 * Description:
 *   DMAC transfer completion callback.
 *
 ****************************************************************************/

static void ra_sdram_dma_callback(void *handle, int event, void *arg)
{
  g_sdram_dma_complete = true;
  nxsem_post(&g_sdram_dma_sem);

  /* Call user callback if registered */

  if (g_sdram_dma_user_callback != NULL)
    {
      g_sdram_dma_user_callback(g_sdram_dma_user_arg);
    }
}

/****************************************************************************
 * Name: ra_sdram_dma_init
 *
 * Description:
 *   Initialize DMAC for SDRAM transfers.
 *
 ****************************************************************************/

static int ra_sdram_dma_init(void)
{
  int ret;

  if (g_sdram_dma_initialized)
    {
      return OK;
    }

  /* Get configured DMA channel from Kconfig */

#ifdef CONFIG_RA_DMAC_SDRAM_CHANNEL
  g_sdram_dma_channel = CONFIG_RA_DMAC_SDRAM_CHANNEL;
#else
  g_sdram_dma_channel = -1;  /* Dynamic allocation */
#endif

  if (g_sdram_dma_channel < 0)
    {
      sdraminfo("SDRAM DMA channel not configured, using dynamic allocation\n");
    }
  else
    {
      sdraminfo("SDRAM DMA using channel %d\n", g_sdram_dma_channel);
    }

  /* Initialize DMAC module */

  ret = ra_dmac_initialize();
  if (ret < 0)
    {
      sdramerr("ERROR: DMAC initialization failed: %d\n", ret);
      return ret;
    }

  /* Initialize semaphore for waiting */

  ret = nxsem_init(&g_sdram_dma_sem, 0, 0);
  if (ret < 0)
    {
      sdramerr("ERROR: Semaphore initialization failed: %d\n", ret);
      return ret;
    }

  g_sdram_dma_initialized = true;
  return OK;
}

/****************************************************************************
 * Name: ra_sdram_dma_write
 *
 * Description:
 *   Write data to SDRAM using DMAC transfer.
 *
 ****************************************************************************/

int ra_sdram_dma_write(void *dest, const void *src, size_t length,
                       ra_sdram_dma_callback_t callback, void *arg)
{
  ra_dmac_config_t dma_config;
  int ret;

  if (!g_sdram_initialized)
    {
      return -ENODEV;
    }

  /* Check alignment (must be 4-byte aligned) */

  if (((uintptr_t)dest & 0x3) || ((uintptr_t)src & 0x3) || (length & 0x3))
    {
      sdramerr("ERROR: Address or length not 4-byte aligned\n");
      return -EINVAL;
    }

  /* Initialize DMAC if needed */

  ret = ra_sdram_dma_init();
  if (ret < 0)
    {
      return ret;
    }

#ifdef CONFIG_ARMV8M_DCACHE
  /* Clean cache for source buffer */

  up_clean_dcache((uintptr_t)src, (uintptr_t)src + length);
#endif

  /* Configure DMAC transfer */

  memset(&dma_config, 0, sizeof(dma_config));
  dma_config.src_addr = (uint32_t)src;
  dma_config.dest_addr = (uint32_t)dest;
  dma_config.transfer_count = length / 4;  /* Transfer in 32-bit words */
  dma_config.size = RA_DMAC_SIZE_32BIT;
  dma_config.src_addr_mode = RA_DMAC_ADDR_INCR;
  dma_config.dest_addr_mode = RA_DMAC_ADDR_INCR;
  dma_config.mode = RA_DMAC_MODE_NORMAL;
  dma_config.repeat_area = RA_DMAC_REPEAT_AREA_NONE;
  dma_config.trigger = RA_DMAC_TRIGGER_SW;
  dma_config.callback = ra_sdram_dma_callback;
  dma_config.user_data = NULL;

  /* Save user callback */

  g_sdram_dma_user_callback = callback;
  g_sdram_dma_user_arg = arg;

  /* Open or reopen DMA channel */

  if (g_sdram_dma_handle != NULL)
    {
      ra_dmac_close(g_sdram_dma_handle);
      g_sdram_dma_handle = NULL;
    }

  /* Open with configured channel or dynamic allocation */

  if (g_sdram_dma_channel >= 0)
    {
      ret = ra_dmac_open_channel(&g_sdram_dma_handle, &dma_config,
                                 g_sdram_dma_channel);
    }
  else
    {
      ret = ra_dmac_open(&g_sdram_dma_handle, &dma_config);
    }

  if (ret < 0)
    {
      sdramerr("ERROR: DMAC open failed: %d\n", ret);
      return ret;
    }

  /* Reset transfer complete flag */

  g_sdram_dma_complete = false;

  /* Enable and start transfer */

  ret = ra_dmac_enable(g_sdram_dma_handle);
  if (ret < 0)
    {
      sdramerr("ERROR: DMAC enable failed: %d\n", ret);
      ra_dmac_close(g_sdram_dma_handle);
      g_sdram_dma_handle = NULL;
      return ret;
    }

  ret = ra_dmac_software_start(g_sdram_dma_handle);
  if (ret < 0)
    {
      sdramerr("ERROR: DMAC software start failed: %d\n", ret);
      ra_dmac_close(g_sdram_dma_handle);
      g_sdram_dma_handle = NULL;
      return ret;
    }

  sdraminfo("DMA write started: src=0x%08lx dest=0x%08lx len=%zu\n",
            (unsigned long)src, (unsigned long)dest, length);

  return OK;
}

/****************************************************************************
 * Name: ra_sdram_dma_read
 *
 * Description:
 *   Read data from SDRAM using DMAC transfer.
 *
 ****************************************************************************/

int ra_sdram_dma_read(void *dest, const void *src, size_t length,
                      ra_sdram_dma_callback_t callback, void *arg)
{
  ra_dmac_config_t dma_config;
  int ret;

  if (!g_sdram_initialized)
    {
      return -ENODEV;
    }

  /* Check alignment (must be 4-byte aligned) */

  if (((uintptr_t)dest & 0x3) || ((uintptr_t)src & 0x3) || (length & 0x3))
    {
      sdramerr("ERROR: Address or length not 4-byte aligned\n");
      return -EINVAL;
    }

  /* Initialize DMAC if needed */

  ret = ra_sdram_dma_init();
  if (ret < 0)
    {
      return ret;
    }

  /* Configure DMAC transfer */

  memset(&dma_config, 0, sizeof(dma_config));
  dma_config.src_addr = (uint32_t)src;
  dma_config.dest_addr = (uint32_t)dest;
  dma_config.transfer_count = length / 4;  /* Transfer in 32-bit words */
  dma_config.size = RA_DMAC_SIZE_32BIT;
  dma_config.src_addr_mode = RA_DMAC_ADDR_INCR;
  dma_config.dest_addr_mode = RA_DMAC_ADDR_INCR;
  dma_config.mode = RA_DMAC_MODE_NORMAL;
  dma_config.repeat_area = RA_DMAC_REPEAT_AREA_NONE;
  dma_config.trigger = RA_DMAC_TRIGGER_SW;
  dma_config.callback = ra_sdram_dma_callback;
  dma_config.user_data = NULL;

  /* Save user callback */

  g_sdram_dma_user_callback = callback;
  g_sdram_dma_user_arg = arg;

  /* Open or reopen DMA channel */

  if (g_sdram_dma_handle != NULL)
    {
      ra_dmac_close(g_sdram_dma_handle);
      g_sdram_dma_handle = NULL;
    }

  /* Open with configured channel or dynamic allocation */

  if (g_sdram_dma_channel >= 0)
    {
      ret = ra_dmac_open_channel(&g_sdram_dma_handle, &dma_config,
                                 g_sdram_dma_channel);
    }
  else
    {
      ret = ra_dmac_open(&g_sdram_dma_handle, &dma_config);
    }

  if (ret < 0)
    {
      sdramerr("ERROR: DMAC open failed: %d\n", ret);
      return ret;
    }

  /* Reset transfer complete flag */

  g_sdram_dma_complete = false;

  /* Enable and start transfer */

  ret = ra_dmac_enable(g_sdram_dma_handle);
  if (ret < 0)
    {
      sdramerr("ERROR: DMAC enable failed: %d\n", ret);
      ra_dmac_close(g_sdram_dma_handle);
      g_sdram_dma_handle = NULL;
      return ret;
    }

  ret = ra_dmac_software_start(g_sdram_dma_handle);
  if (ret < 0)
    {
      sdramerr("ERROR: DMAC software start failed: %d\n", ret);
      ra_dmac_close(g_sdram_dma_handle);
      g_sdram_dma_handle = NULL;
      return ret;
    }

  sdraminfo("DMA read started: src=0x%08lx dest=0x%08lx len=%zu\n",
            (unsigned long)src, (unsigned long)dest, length);

#ifdef CONFIG_ARMV8M_DCACHE
  /* Save destination buffer info for cache invalidation after transfer */

  g_sdram_dma_read_dest = dest;
  g_sdram_dma_read_length = length;
#endif

  return OK;
}

/****************************************************************************
 * Name: ra_sdram_dma_wait
 *
 * Description:
 *   Wait for ongoing DMAC transfer to complete.
 *
 ****************************************************************************/

int ra_sdram_dma_wait(uint32_t timeout_ms)
{
  struct timespec abstime;
  int ret;

  if (!g_sdram_initialized)
    {
      return -ENODEV;
    }

  if (g_sdram_dma_handle == NULL)
    {
      return -EINVAL;
    }

  /* Wait with timeout if specified */

  if (timeout_ms > 0)
    {
      ret = clock_gettime(CLOCK_REALTIME, &abstime);
      if (ret < 0)
        {
          return -errno;
        }

      abstime.tv_sec += timeout_ms / 1000;
      abstime.tv_nsec += (timeout_ms % 1000) * 1000000;

      if (abstime.tv_nsec >= 1000000000)
        {
          abstime.tv_sec++;
          abstime.tv_nsec -= 1000000000;
        }

      ret = nxsem_timedwait(&g_sdram_dma_sem, &abstime);
      if (ret < 0)
        {
          if (ret == -ETIMEDOUT)
            {
              sdramerr("ERROR: DMA transfer timeout\n");
            }

          return ret;
        }
    }
  else
    {
      /* Infinite wait */

      ret = nxsem_wait(&g_sdram_dma_sem);
      if (ret < 0)
        {
          return ret;
        }
    }

#ifdef CONFIG_ARMV8M_DCACHE
  /* Invalidate cache for read destination buffer to reflect DMA data */

  if (g_sdram_dma_read_dest != NULL && g_sdram_dma_read_length > 0)
    {
      up_invalidate_dcache((uintptr_t)g_sdram_dma_read_dest,
                          (uintptr_t)g_sdram_dma_read_dest +
                          g_sdram_dma_read_length);
      g_sdram_dma_read_dest = NULL;
      g_sdram_dma_read_length = 0;
    }
#endif

  sdraminfo("DMA transfer complete\n");

  return OK;
}

#endif /* CONFIG_RA_DMAC */

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

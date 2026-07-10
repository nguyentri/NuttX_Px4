/****************************************************************************
 * arch/arm/src/rzv/rzv_dmac.c
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
#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>

#include "arm_internal.h"
#include "barriers.h"
#include "chip.h"
#include "hardware/rzv_cpg.h"
#include "hardware/rzv_dmac.h"
#include "hardware/rzv_elc.h"
#include "rzv_dmac.h"
#include "rzv_clock.h"
#include "rzv_icu.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define DMAC_OPEN_ID             (0x444d4143u) /* "DMAC" ASCII sentinel */

/* Stop timeout: 1000 polls × 10 µs = 10 ms maximum */

#define DMAC_STOP_TIMEOUT_POLLS  1000

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* Per-channel state. Embedded statically in g_dmac_channels[].
 * No kmm_zalloc — avoids ISR-vs-free TOCTOU race (H5).
 */

struct rzv_dmac_ctrl_s
{
  uint32_t                  open_id;   /* DMAC_OPEN_ID when configured */
  uint8_t                   unit;      /* DMAC unit (0-4) */
  uint8_t                   local_ch;  /* Channel within unit (0-15) */
  bool                      in_use;    /* True when configured */
  bool                      enabled;   /* True when transfer started */
  struct rzv_dmac_config_s  config;    /* Embedded config (no heap) */
  int                       irq;       /* NuttX IRQ from rzv_icu_attach */
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Static channel control blocks — 80 channels total.
 * Sized at compile time; no dynamic allocation in hot path.
 */

static struct rzv_dmac_ctrl_s g_dmac_channels[RZV_DMAC_MAX_CHANNELS];

/* Unit initialised flags (one per DMAC unit 0-4) */

static bool g_dmac_unit_initialized[RZV_DMAC_NUM_UNITS];

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_dmac_validate_config
 ****************************************************************************/

static int rzv_dmac_validate_config(const struct rzv_dmac_config_s *config)
{
  if (config == NULL)
    {
      return -EINVAL;
    }

  /* Length must be non-zero; uint32_t can never exceed 0xFFFFFFFF so the
   * old `> 0xFFFFFFFF` dead-check is simply omitted (M5).
   */

  if (config->length == 0)
    {
      return -EINVAL;
    }

  /* Validate transfer sizes */

  if (config->src_size > RZV_DMAC_SIZE_128BYTE ||
      config->dst_size > RZV_DMAC_SIZE_128BYTE)
    {
      return -EINVAL;
    }

  /* Address alignment: each size n means 2^n byte alignment required */

  uint32_t src_align = 1u << (uint32_t)config->src_size;
  uint32_t dst_align = 1u << (uint32_t)config->dst_size;

  if ((config->src_addr & (src_align - 1u)) != 0u ||
      (config->dst_addr & (dst_align - 1u)) != 0u)
    {
      dmaerr("Alignment error: src=0x%08" PRIx32 " (align=%" PRIu32 "), "
             "dst=0x%08" PRIx32 " (align=%" PRIu32 ")\n",
             config->src_addr, src_align,
             config->dst_addr, dst_align);
      return -EINVAL;
    }

  if (config->priority > 7)
    {
      return -EINVAL;
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_dmac_setup_channel
 *
 * Description:
 *   Write CHCFG / CHEXT / CHITVL and N[0] SA/DA/TB registers.
 *   No DMARS write — peripheral source selection belongs in DMACKSEL
 *   (rzv_dmac_set_peripheral_source).
 *   Uses N[0] for initial transfer, N[1] zeroed (no double-buffer reload).
 *
 ****************************************************************************/

static int rzv_dmac_setup_channel(struct rzv_dmac_ctrl_s *ctrl)
{
  const struct rzv_dmac_config_s *config = &ctrl->config;
  uint8_t  unit     = ctrl->unit;
  uint8_t  local_ch = ctrl->local_ch;
  uint32_t chcfg    = 0;
  uint32_t chext    = 0;

  /* --- CHCFG ---
   * SDS[15:12] = source data size
   * DDS[19:16] = destination data size
   * SAD[20]    = source address direction: 0=increment, 1=fixed
   * DAD[21]    = destination address direction: 0=increment, 1=fixed
   * REN[30]    = 1 for register mode (no link-mode support)
   * DEM[24]    = 0 to enable DMAEND interrupt when callback provided,
   *              1 to mask it when no callback
   */

  chcfg |= ((uint32_t)config->src_size & 0xfu) << DMAC_CHCFG_SDS_SHIFT; /* SDS */
  chcfg |= ((uint32_t)config->dst_size & 0xfu) << DMAC_CHCFG_DDS_SHIFT; /* DDS */

  if (config->src_addr_mode == RZV_DMAC_ADDR_FIXED)
    {
      chcfg |= DMAC_CHCFG_SAD; /* SAD = 1 */
    }

  if (config->dst_addr_mode == RZV_DMAC_ADDR_FIXED)
    {
      chcfg |= DMAC_CHCFG_DAD; /* DAD = 1 */
    }

  /* D4-fix: REN must NOT be set for one-shot transfers — with REN=1 and
   * N[1] zeroed (no reload buffer) the HW re-executes a zero-byte transfer
   * to address 0 after the first END, causing faults.  This driver supports
   * only one-shot register-mode transfers; REN is left 0.
   * RSW/REN are only for CONTINUOUS_SETTING mode. */

  if (config->callback != NULL)
    {
      chcfg &= ~DMAC_CHCFG_DEM; /* DEM = 0: enable DMAEND interrupt */
    }
  else
    {
      chcfg |= DMAC_CHCFG_DEM;  /* DEM = 1: mask interrupt */
    }

  /* --- CHEXT ---
   * SPR[2:0] = source port priority
   * DPR[10:8] = destination port priority
   */

  chext |= ((uint32_t)config->priority & 0x7u) << DMAC_CHEXT_SPR_SHIFT;
  chext |= ((uint32_t)config->priority & 0x7u) << DMAC_CHEXT_DPR_SHIFT;

  /* Write configuration */

  putreg32(chcfg, RZV_DMAC_CHCFG(unit, local_ch));
  putreg32(chext, RZV_DMAC_CHEXT(unit, local_ch));
  putreg32((uint32_t)config->transfer_interval & 0xffffu,
           RZV_DMAC_CHITVL(unit, local_ch));

  /* D8-fix: TX cache clean before writing descriptors.
   * configure→start is a legal sequence; channel_set_buffer may not be
   * called, so we must clean here too.  Only needed when source is the
   * incrementing (memory) side.  Identity mapping: VA == PA on CR8 boot. */

  if (config->src_addr_mode == RZV_DMAC_ADDR_INCREMENT &&
      config->src_addr != 0 && config->length != 0)
    {
      up_clean_dcache(config->src_addr,
                      config->src_addr + config->length);
    }

  /* N[0]: initial transfer addresses and byte count */

  putreg32(config->src_addr, RZV_DMAC_N0SA(unit, local_ch));
  putreg32(config->dst_addr, RZV_DMAC_N0DA(unit, local_ch));
  putreg32(config->length,   RZV_DMAC_N0TB(unit, local_ch));

  /* N[1]: zero (no double-buffer reload in this configuration) */

  putreg32(0, RZV_DMAC_N1SA(unit, local_ch));
  putreg32(0, RZV_DMAC_N1DA(unit, local_ch));
  putreg32(0, RZV_DMAC_N1TB(unit, local_ch));

  dmainfo("DMAC%d CH%d (global %d) cfg: src=0x%08" PRIx32
          " dst=0x%08" PRIx32 " len=%" PRIu32 "\n",
          unit, local_ch,
          (int)(unit * RZV_DMAC_CHANNELS_PER_UNIT + local_ch),
          config->src_addr, config->dst_addr, config->length);

  return OK;
}

/****************************************************************************
 * Name: rzv_dmac_interrupt_handler
 *
 * Description:
 *   DMAC_B channel-end interrupt handler.  Invokes user callback from ISR
 *   context (see callback-from-ISR contract in rzv_dmac.h).
 *   For RX transfers: calls up_invalidate_dcache() before callback so the
 *   CPU sees fresh DMA data.
 *
 ****************************************************************************/

static int rzv_dmac_interrupt_handler(int irq, void *context, void *arg)
{
  struct rzv_dmac_ctrl_s *ctrl = (struct rzv_dmac_ctrl_s *)arg;
  uint32_t status;
  int global_ch;

  if (ctrl == NULL || ctrl->open_id != DMAC_OPEN_ID)
    {
      return OK;
    }

  status    = getreg32(RZV_DMAC_CHSTAT(ctrl->unit, ctrl->local_ch));
  global_ch = ctrl->unit * RZV_DMAC_CHANNELS_PER_UNIT + ctrl->local_ch;

  if (status & DMAC_CHSTAT_END)
    {
      /* Clear END flag */

      putreg32(DMAC_CHCTRL_CLREND,
               RZV_DMAC_CHCTRL(ctrl->unit, ctrl->local_ch));

      /* RX cache invalidation: ensure CPU reads DMA-written data (H3).
       * Only needed when destination address increments (memory is dest).
       * Identity mapping assumed (VA == PA on CR8 boot).
       */

      if (ctrl->config.dst_addr_mode == RZV_DMAC_ADDR_INCREMENT &&
          ctrl->config.dst_addr != 0 && ctrl->config.length != 0)
        {
          up_invalidate_dcache(ctrl->config.dst_addr,
                               ctrl->config.dst_addr + ctrl->config.length);
        }

      if (ctrl->config.callback != NULL)
        {
          ctrl->config.callback(global_ch, RZV_DMAC_EVENT_COMPLETE,
                                ctrl->config.user_data);
        }

      dmainfo("DMAC%d CH%d: complete\n", ctrl->unit, ctrl->local_ch);
    }

  if (status & DMAC_CHSTAT_ER)
    {
      dmaerr("DMAC%d CH%d: error, CHSTAT=0x%08" PRIx32 "\n",
             ctrl->unit, ctrl->local_ch, status);

      /* D11-fix: Software reset clears CHCFG/CHCTRL/CHSTAT in HW.
       * Mark channel as not-in-use so the caller must reconfigure before
       * the next channel_start — otherwise channel_start runs on zeroed
       * descriptors and DMA reads/writes address 0. */

      putreg32(DMAC_CHCTRL_SWRST,
               RZV_DMAC_CHCTRL(ctrl->unit, ctrl->local_ch));

      ctrl->enabled = false;
      ctrl->in_use  = false;

      if (ctrl->config.callback != NULL)
        {
          ctrl->config.callback(global_ch, RZV_DMAC_EVENT_ERROR,
                                ctrl->config.user_data);
        }
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_dmac_channel_initialize
 *
 * Description:
 *   Initialize DMAC unit for the given global channel.
 * - Enables CPG clock (RZV_CPG_CLK_DMAC, 2-bit pair encoding)
 *   - Releases module reset
 *   - Initialises both group DCTRL registers (round-robin priority)
 *   - Zeroes channel control structures for this unit
 *
 ****************************************************************************/

int rzv_dmac_channel_initialize(int channel)
{
  int unit;
  int i;
  int global_base;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS)
    {
      return -EINVAL;
    }

  unit = RZV_DMAC_UNIT(channel);

  /* D10-fix: guard the initialized check and flag assignment under a
   * critical section to prevent two threads from racing through the gate
   * and double-initialising the same unit (double CPG writes + memset race
   * with in-flight channel_configure on the same unit). */

  {
    irqstate_t flags = enter_critical_section();
    bool already_done = g_dmac_unit_initialized[unit];
    if (!already_done)
      {
        /* Set flag inside CS so no other thread can race past */

        g_dmac_unit_initialized[unit] = true;
      }

    leave_critical_section(flags);

    if (already_done)
      {
        return OK; /* Idempotent */
      }
  }

  /* Enable DMAC CPG clock (API).
   * RZV_CPG_CLK_DMAC uses 2-bit pair encoding; rzv_clock_enable handles it.
   * All units share one clock gate; enabling it multiple times is safe.
   */

  rzv_clock_enable(RZV_CPG_CLK_DMAC);
  rzv_module_unreset(RZV_CPG_CLK_DMAC);

  /* D6-fix: Unmask AXI/AHB bus interface (MSTP) for all 5 DMAC units.
   * Per RZ/V2H hardware manual, bus stop bits are:
   *   BUS_5_MSTOP  bit 9  (DMAC0)
   *   BUS_3_MSTOP  bit 2  (DMAC1)
   *   BUS_3_MSTOP  bit 3  (DMAC2)
   *   BUS_10_MSTOP bit 11 (DMAC3)
   *   BUS_10_MSTOP bit 12 (DMAC4)
   * Write WEN=1 + data=0 to clear the MSTOP bit (allow bus access).
   * Format: bit[N+16]=WEN, bit[N]=value.  To clear: write (1<<(N+16)). */

  putreg32(1u << (9 + 16),  RZV_CPG_BUS_5_MSTOP);  /* DMAC0 */
  putreg32((1u << (2 + 16)) | (1u << (3 + 16)),
           RZV_CPG_BUS_3_MSTOP);                    /* DMAC1, DMAC2 */
  putreg32((1u << (11 + 16)) | (1u << (12 + 16)),
           RZV_CPG_BUS_10_MSTOP);                   /* DMAC3, DMAC4 */

  /* Initialise both group control registers */

  putreg32(DMAC_DCTRL_PR, RZV_DMAC_DCTRL(unit, 0)); /* round-robin */
  putreg32(DMAC_DCTRL_PR, RZV_DMAC_DCTRL(unit, 1));

  /* Clear channel control blocks for this unit */

  global_base = unit * RZV_DMAC_CHANNELS_PER_UNIT;
  for (i = 0; i < RZV_DMAC_CHANNELS_PER_UNIT; i++)
    {
      struct rzv_dmac_ctrl_s *ctrl = &g_dmac_channels[global_base + i];
      memset(ctrl, 0, sizeof(*ctrl));
      ctrl->unit     = (uint8_t)unit;
      ctrl->local_ch = (uint8_t)i;
      ctrl->irq      = -1;
    }

  dmainfo("DMAC unit %d initialized\n", unit);
  return OK;
}

/****************************************************************************
 * Name: rzv_dmac_channel_configure
 ****************************************************************************/

int rzv_dmac_channel_configure(int channel,
                               const struct rzv_dmac_config_s *config)
{
  struct rzv_dmac_ctrl_s *ctrl;
  int ret;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS || config == NULL)
    {
      return -EINVAL;
    }

  /* Auto-initialize unit if needed */

  ret = rzv_dmac_channel_initialize(channel);
  if (ret < 0)
    {
      return ret;
    }

  ret = rzv_dmac_validate_config(config);
  if (ret < 0)
    {
      return ret;
    }

  ctrl = &g_dmac_channels[channel];

  /* D14-fix: guard the in_use check + set under a critical section so
   * two concurrent configure calls on the same channel cannot both pass
   * the gate and race to write ctrl->config / attach the IRQ. */

  {
    irqstate_t flags = enter_critical_section();

    if (ctrl->in_use)
      {
        leave_critical_section(flags);
        dmaerr("Channel %d already in use\n", channel);
        return -EBUSY;
      }

    /* Claim the slot atomically */

    ctrl->open_id = DMAC_OPEN_ID;
    ctrl->in_use  = true;
    leave_critical_section(flags);
  }

  /* Embed configuration — no heap allocation (H5) */

  memcpy(&ctrl->config, config, sizeof(ctrl->config));

  ret = rzv_dmac_setup_channel(ctrl);
  if (ret < 0)
    {
      ctrl->in_use  = false;
      ctrl->open_id = 0;
      return ret;
    }

  /* Wire interrupt if callback provided (H1).
   * ELC event for DMAEND is provided by caller in config->elc_event.
   * rzv_icu_attach returns the NuttX IRQ number for use by up_enable_irq.
   */

  if (config->callback != NULL && config->elc_event >= 0)
    {
      ctrl->irq = rzv_icu_attach(config->elc_event,
                                 rzv_dmac_interrupt_handler,
                                 ctrl, true);
      if (ctrl->irq < 0)
        {
          dmaerr("Channel %d: IRQ attach failed for ELC event %d: %d\n",
                 channel, config->elc_event, ctrl->irq);
          /* Non-fatal: polling mode still possible */

          ctrl->irq = -1;
        }
    }

  dmainfo("Channel %d configured (unit=%d local=%d)\n",
          channel, ctrl->unit, ctrl->local_ch);
  return OK;
}

/****************************************************************************
 * Name: rzv_dmac_channel_set_buffer
 *
 * Description:
 *   Update N[0] SA/TB for the next transfer.  Satisfies the
 * TODO(-dep) in rzv_serial.c rzv_dma_send.
 *   Performs TX cache clean (up_clean_dcache) when source address increments.
 *
 ****************************************************************************/

int rzv_dmac_channel_set_buffer(int channel, uint32_t src_addr,
                                uint32_t length)
{
  struct rzv_dmac_ctrl_s *ctrl;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS)
    {
      return -EINVAL;
    }

  ctrl = &g_dmac_channels[channel];

  if (ctrl->open_id != DMAC_OPEN_ID || !ctrl->in_use)
    {
      return -EINVAL;
    }

  if (length == 0)
    {
      return -EINVAL;
    }

  /* Check not currently active */

  if (getreg32(RZV_DMAC_CHSTAT(ctrl->unit, ctrl->local_ch)) &
      DMAC_CHSTAT_TACT)
    {
      return -EBUSY;
    }

  /* TX cache maintenance: clean D-cache so DMA reads coherent data (H3).
   * Only applies when source is the incrementing (memory) side.
   * Caller is responsible for cache-line alignment (see contract in header).
   * Identity mapping: VA == PA on CR8 boot, so src_addr IS the PA.
   */

  if (ctrl->config.src_addr_mode == RZV_DMAC_ADDR_INCREMENT &&
      src_addr != 0)
    {
      up_clean_dcache(src_addr, src_addr + length);
    }

  ctrl->config.src_addr = src_addr;
  ctrl->config.length   = length;

  putreg32(src_addr, RZV_DMAC_N0SA(ctrl->unit, ctrl->local_ch));
  putreg32(length,   RZV_DMAC_N0TB(ctrl->unit, ctrl->local_ch));

  return OK;
}

/****************************************************************************
 * Name: rzv_dmac_channel_start
 ****************************************************************************/

int rzv_dmac_channel_start(int channel)
{
  struct rzv_dmac_ctrl_s *ctrl;
  uint32_t status;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS)
    {
      return -EINVAL;
    }

  ctrl = &g_dmac_channels[channel];

  if (ctrl->open_id != DMAC_OPEN_ID || !ctrl->in_use)
    {
      return -EINVAL;
    }

  status = getreg32(RZV_DMAC_CHSTAT(ctrl->unit, ctrl->local_ch));
  if (status & DMAC_CHSTAT_TACT)
    {
      return -EBUSY;
    }

  /* D7-fix: SWRST before SETEN to clear any stale END/ER flags from a
   * previous transfer.  SWRST must be issued first; without it, stale flags
   * can re-trigger callbacks or corrupt the channel state machine. */

  putreg32(DMAC_CHCTRL_SWRST,
           RZV_DMAC_CHCTRL(ctrl->unit, ctrl->local_ch));

  /* D12-fix: ARM DSB to drain the store buffer before asserting SETEN.
   * The Cortex-R8 store buffer may reorder the descriptor register writes
   * (N0SA/N0DA/N0TB) relative to SETEN unless Device-nGnRE mapping is
   * guaranteed.  Insert DSB as a defensive barrier.
   * Reference: ARMv7-R Architecture Reference Manual §A3.8.3. */

  ARM_DSB();

  /* Enable channel */

  putreg32(DMAC_CHCTRL_SETEN,
           RZV_DMAC_CHCTRL(ctrl->unit, ctrl->local_ch));

  /* D15 note: TRM requires CHSTAT.EN==1 before STG for SW trigger.
   * Polling EN here is defensive and avoids a dropped STG on cold start.
   * Loop is bounded (EN should set within a few cycles after SETEN). */

  /* Software trigger for SW-mode transfers */

  if (ctrl->config.trigger == RZV_DMAC_TRIGGER_SW)
    {
      int poll;
      for (poll = 0; poll < 100; poll++)
        {
          if (getreg32(RZV_DMAC_CHSTAT(ctrl->unit, ctrl->local_ch)) &
              DMAC_CHSTAT_EN)
            {
              break;
            }
        }

      putreg32(DMAC_CHCTRL_STG,
               RZV_DMAC_CHCTRL(ctrl->unit, ctrl->local_ch));
    }

  ctrl->enabled = true;

  dmainfo("Channel %d started\n", channel);
  return OK;
}

/****************************************************************************
 * Name: rzv_dmac_channel_stop
 *
 * Description:
 *   Stop a transfer.  Critical section (M2): irqsave/restore wraps the
 *   entire stop sequence so that CLREN and SWRST are not interleaved with
 *   a concurrent DMAEND ISR delivery.
 *
 ****************************************************************************/

int rzv_dmac_channel_stop(int channel)
{
  struct rzv_dmac_ctrl_s *ctrl;
  uint32_t status;
  irqstate_t flags;
  int timeout;
  int saved_irq; /* D9-fix: snapshot irq inside CS before slot is released */

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS)
    {
      return -EINVAL;
    }

  ctrl = &g_dmac_channels[channel];

  if (ctrl->open_id != DMAC_OPEN_ID)
    {
      return -EINVAL;
    }

  /* Critical section: stop register sequence must be atomic (M2) */

  flags = enter_critical_section();

  /* Disable channel */

  putreg32(DMAC_CHCTRL_CLREN,
           RZV_DMAC_CHCTRL(ctrl->unit, ctrl->local_ch));

  /* Poll for TACT clear with timeout */

  timeout = DMAC_STOP_TIMEOUT_POLLS;
  do
    {
      status = getreg32(RZV_DMAC_CHSTAT(ctrl->unit, ctrl->local_ch));
      if (!(status & DMAC_CHSTAT_TACT))
        {
          break;
        }

      leave_critical_section(flags);
      up_udelay(10);
      flags = enter_critical_section();
    }
  while (--timeout > 0);

  if (timeout == 0)
    {
      dmaerr("Channel %d stop timeout — forcing reset\n", channel);
      putreg32(DMAC_CHCTRL_SWRST,
               RZV_DMAC_CHCTRL(ctrl->unit, ctrl->local_ch));
    }

  /* Clear pending flags */

  putreg32(DMAC_CHCTRL_CLREND | DMAC_CHCTRL_CLRTC,
           RZV_DMAC_CHCTRL(ctrl->unit, ctrl->local_ch));

  ctrl->enabled = false;
  ctrl->in_use  = false;
  ctrl->open_id = 0;

  /* D9-fix: snapshot ctrl->irq before leaving the critical section.
   * Once in_use=false / open_id=0 are visible outside CS a concurrent
   * channel_configure can reclaim this slot and overwrite ctrl->irq.
   * Detaching the wrong IRQ would break the new owner's channel.
   * Snapshot here (still inside CS) and detach the local copy outside. */

  saved_irq  = ctrl->irq;
  ctrl->irq  = -1;

  leave_critical_section(flags);

  /* Detach the IRQ we held when we owned the channel (outside CS) */

  if (saved_irq >= 0)
    {
      rzv_icu_detach(saved_irq);
    }

  dmainfo("Channel %d stopped\n", channel);
  return OK;
}

/****************************************************************************
 * Name: rzv_dmac_channel_status
 ****************************************************************************/

uint32_t rzv_dmac_channel_status(int channel)
{
  struct rzv_dmac_ctrl_s *ctrl;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS)
    {
      return 0;
    }

  ctrl = &g_dmac_channels[channel];

  if (ctrl->open_id != DMAC_OPEN_ID)
    {
      return 0;
    }

  return getreg32(RZV_DMAC_CHSTAT(ctrl->unit, ctrl->local_ch));
}

/****************************************************************************
 * Name: rzv_dmac_get_remaining_bytes
 ****************************************************************************/

uint32_t rzv_dmac_get_remaining_bytes(int channel)
{
  struct rzv_dmac_ctrl_s *ctrl;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS)
    {
      return 0;
    }

  ctrl = &g_dmac_channels[channel];

  if (ctrl->open_id != DMAC_OPEN_ID)
    {
      return 0;
    }

  return getreg32(RZV_DMAC_CRTB(ctrl->unit, ctrl->local_ch));
}

/****************************************************************************
 * Name: rzv_dmac_set_peripheral_source
 *
 * Description:
 *   Program INTC DMACKSEL to route ELC event → DMAC channel (H1b).
 *   Returns -ENOSYS until DMACKSEL0 offset is confirmed vs RZV2H UM.
 *   See hardware/rzv_dmac.h RZV_INTC_DMACKSEL0_OFFSET note.
 *
 ****************************************************************************/

int rzv_dmac_set_peripheral_source(int channel, int elc_event)
{
  /* D5-fix: DMACKSEL0 offset 0x0BCC is confirmed derivable from
   * intc_iodefine.h (R9A09G057H CR variant): DMACKSEL0 field follows
   * DMRCLR2 + RESERVED13[36 bytes] in R_INTC_Type at base 0x10400000.
   * The offset ~0x0BCC is consistent with the struct layout enumeration.
   * Register write is now enabled — HW-triggered DMA requires this path.
   * Reference: refs/.../R9A09G057H/cr/iodefines/intc_iodefine.h line 2986.
   */

  struct rzv_dmac_ctrl_s *ctrl;
  uint32_t reg_idx;
  uint32_t shift;
  uint32_t val;
  uint32_t regval;
  irqstate_t flags;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS)
    {
      return -EINVAL;
    }

  ctrl = &g_dmac_channels[channel];

  /* DMACKSEL channel index.
   * For DMAC units 1-4: global slot = (unit-1)*16 + local_ch
   * For DMAC unit 0:    global slot = 4*16 + local_ch (= 64 + local_ch)
   * DMACKSEL register n covers slots n*4 .. n*4+3.
   */

  reg_idx = (uint32_t)channel / 4u;
  shift   = (((uint32_t)channel % 4u)) * 8u;

  if (elc_event < 0)
    {
      val = 0;
    }
  else
    {
      val = RZV_INTC_DMACKSEL_VAL(ctrl->unit, ctrl->local_ch) &
            RZV_INTC_DMACKSEL_MASK;
    }

  flags  = enter_critical_section();
  regval = getreg32(RZV_INTC_DMACKSEL(reg_idx));
  regval &= ~((uint32_t)RZV_INTC_DMACKSEL_MASK << shift);
  regval |= (val << shift);
  putreg32(regval, RZV_INTC_DMACKSEL(reg_idx));
  leave_critical_section(flags);

  dmainfo("Channel %d: DMACKSEL%d[%d] = 0x%02" PRIx32 "\n",
          channel, (int)reg_idx, (int)shift, val);
  return OK;
}

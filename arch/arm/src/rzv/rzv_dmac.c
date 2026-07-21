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
#include "hardware/rzv_intc.h"
#include "rzv_dmac.h"
#include "rzv_clock.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define DMAC_OPEN_ID             (0x444d4143u) /* "DMAC" ASCII sentinel */

/* Stop timeout: 1000 polls × 10 µs = 10 ms maximum */

#define DMAC_START_TIMEOUT_POLLS 100
#define DMAC_STOP_TIMEOUT_POLLS  1000
#define DMAC_CACHE_LINE_SIZE     32u

#define DMAC_CR8_ITCM_CPU_BASE   0x00000000u
#define DMAC_CR8_ITCM_BUS_BASE   0x12040000u
#define DMAC_CR8_DTCM_CPU_BASE   0x00020000u
#define DMAC_CR8_DTCM_BUS_BASE   0x12060000u
#define DMAC_CR8_TCM_SIZE        0x00020000u

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* Per-channel state. Embedded statically in g_dmac_channels[].
 * No kmm_zalloc avoids ownership races during channel reuse.
 */

struct rzv_dmac_ctrl_s
{
  uint32_t                  open_id;   /* DMAC_OPEN_ID when configured */
  uint8_t                   unit;      /* DMAC unit (0-4) */
  uint8_t                   local_ch;  /* Channel within unit (0-15) */
  bool                      in_use;    /* True when configured */
  bool                      configuring;
  bool                      operating; /* Register operation in progress */
  bool                      hw_trigger; /* True: peripheral(ELC)-triggered; no STG */
  struct rzv_dmac_config_s  config;    /* Embedded config (no heap) */
};

enum rzv_dmac_unit_state_e
{
  RZV_DMAC_UNIT_UNINITIALIZED = 0,
  RZV_DMAC_UNIT_INITIALIZING,
  RZV_DMAC_UNIT_READY
};

struct rzv_dmac_address_region_s
{
  uintptr_t cpu_base;
  uint32_t  bus_base;
  uint32_t  size;
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Static channel control blocks — 80 channels total.
 * Sized at compile time; no dynamic allocation in hot path.
 */

static struct rzv_dmac_ctrl_s g_dmac_channels[RZV_DMAC_MAX_CHANNELS];

/* Unit lifecycle state (one per DMAC unit 0-4) */

static uint8_t g_dmac_unit_state[RZV_DMAC_NUM_UNITS];

static const struct rzv_dmac_address_region_s g_dmac_address_regions[] =
{
  {DMAC_CR8_ITCM_CPU_BASE, DMAC_CR8_ITCM_BUS_BASE, DMAC_CR8_TCM_SIZE},
  {DMAC_CR8_DTCM_CPU_BASE, DMAC_CR8_DTCM_BUS_BASE, DMAC_CR8_TCM_SIZE}
};

static int rzv_dmac_clear_peripheral_source(int channel);

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_dmac_convert_cpu_address
 ****************************************************************************/

static int rzv_dmac_convert_cpu_address(uintptr_t cpu_addr, uint32_t length,
                                        uint32_t *bus_addr)
{
  unsigned int i;

  if (bus_addr == NULL || length == 0 ||
      cpu_addr > (uintptr_t)UINT32_MAX - length)
    {
      return -EINVAL;
    }

  for (i = 0; i < sizeof(g_dmac_address_regions) /
       sizeof(g_dmac_address_regions[0]); i++)
    {
      const struct rzv_dmac_address_region_s *region =
        &g_dmac_address_regions[i];
      uintptr_t offset;

      if (cpu_addr < region->cpu_base ||
          cpu_addr >= region->cpu_base + region->size)
        {
          continue;
        }

      offset = cpu_addr - region->cpu_base;
      if (length > region->size - offset)
        {
          return -EINVAL;
        }

      *bus_addr = region->bus_base + (uint32_t)offset;
      return OK;
    }

  *bus_addr = (uint32_t)cpu_addr;
  return OK;
}

/****************************************************************************
 * Name: rzv_dmac_validate_config
 ****************************************************************************/

static int rzv_dmac_validate_config(const struct rzv_dmac_config_s *config)
{
  uint32_t width;
  uint32_t src_bus;
  uint32_t dst_bus;

  if (config == NULL || config->length == 0)
    {
      return -EINVAL;
    }

  /* Polling driver: completion callbacks are not supported in either mode. */
  if (config->callback != NULL)
    {
      return -ENOTSUP;
    }

  bool hw = (config->trigger == RZV_DMAC_TRIGGER_HW);

  if (config->trigger != RZV_DMAC_TRIGGER_SW && !hw)
    {
      return -ENOTSUP;
    }

  /* Software trigger = memory-to-memory (both operands increment, no source).
   * Hardware trigger = peripheral-paced: needs an ELC activation event and a
   * fixed destination (a peripheral register, e.g. GPT GTCCRx for DShot). */
  if (hw)
    {
      if (config->elc_event < 0 ||
          config->src_addr_mode != RZV_DMAC_ADDR_INCREMENT ||
          config->dst_addr_mode != RZV_DMAC_ADDR_FIXED)
        {
          return -ENOTSUP;
        }
    }
  else if (config->elc_event >= 0 ||
           config->src_addr_mode != RZV_DMAC_ADDR_INCREMENT ||
           config->dst_addr_mode != RZV_DMAC_ADDR_INCREMENT)
    {
      return -ENOTSUP;
    }

  if ((int)config->src_size < (int)RZV_DMAC_SIZE_1BYTE ||
      (int)config->dst_size < (int)RZV_DMAC_SIZE_1BYTE ||
      config->src_size > RZV_DMAC_SIZE_128BYTE ||
      config->dst_size > RZV_DMAC_SIZE_128BYTE ||
      config->src_size != config->dst_size)
    {
      return -EINVAL;
    }

  width = 1u << (uint32_t)config->src_size;

  /* Transfer-width alignment applies to both modes. */
  if ((config->src_addr & (width - 1u)) != 0u ||
      (config->dst_addr & (width - 1u)) != 0u ||
      (config->length  & (width - 1u)) != 0u)
    {
      dmaerr("DMAC width alignment error\n");
      return -EINVAL;
    }

  /* Cache-line alignment applies to cached-memory operands only. Source is
   * always memory; destination is memory for mem-to-mem but an uncached
   * peripheral register for hardware-triggered transfers. */
  if ((config->src_addr & (DMAC_CACHE_LINE_SIZE - 1u)) != 0u ||
      (!hw && (((config->dst_addr & (DMAC_CACHE_LINE_SIZE - 1u)) != 0u) ||
               ((config->length   & (DMAC_CACHE_LINE_SIZE - 1u)) != 0u))))
    {
      dmaerr("DMAC cache-line alignment error\n");
      return -EINVAL;
    }

  if (config->priority > 7)
    {
      return -EINVAL;
    }

  if (hw && config->elc_event >= 0x3ff)
    {
      return -EINVAL;
    }

  if (rzv_dmac_convert_cpu_address(config->src_addr, config->length,
                                   &src_bus) < 0 ||
      rzv_dmac_convert_cpu_address(config->dst_addr, config->length,
                                   &dst_bus) < 0)
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
 *   No peripheral source routing is configured in the polling-only path.
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
  uint32_t src_bus;
  uint32_t dst_bus;
  int ret;

  /* --- CHCFG ---
   * SDS[15:12] = source data size
   * DDS[19:16] = destination data size
   * SAD[20]    = source address direction: 0=increment, 1=fixed
   * DAD[21]    = destination address direction: 0=increment, 1=fixed
   * REN[30]    = 0 for the supported one-shot register transfer
   * DEM[24]    = 0 to enable DMAEND interrupt when callback provided,
   *              1 to mask it when no callback
   */

  chcfg |= ((uint32_t)config->src_size & 0xfu) << DMAC_CHCFG_SDS_SHIFT; /* SDS */
  chcfg |= ((uint32_t)config->dst_size & 0xfu) << DMAC_CHCFG_DDS_SHIFT; /* DDS */
  chcfg |= ((uint32_t)local_ch & 0x7u) << DMAC_CHCFG_SEL_SHIFT;

  if (config->src_addr_mode == RZV_DMAC_ADDR_FIXED)
    {
      chcfg |= DMAC_CHCFG_SAD; /* SAD = 1 */
    }

  if (config->dst_addr_mode == RZV_DMAC_ADDR_FIXED)
    {
      chcfg |= DMAC_CHCFG_DAD; /* DAD = 1 */
    }

  /* REN must remain clear for one-shot transfers: with REN=1 and
   * N[1] zeroed (no reload buffer) the HW re-executes a zero-byte transfer
   * to address 0 after the first END, causing faults.  This driver supports
   * only one-shot register-mode transfers; REN is left 0.
   * RSW/REN are only for CONTINUOUS_SETTING mode.
   */

  chcfg |= DMAC_CHCFG_DEM; /* Polling path: mask DMAEND interrupt */

  /* Hardware(ELC)-triggered peripheral transfer (e.g. GPT overflow paces one
   * word into GTCCRx per timer cycle for DShot). TM stays 0 = one transfer
   * unit per activation event. Detect = rising edge (per the FSP
   * DETECTION_RISING_EDGE encoding of the GPT overflow events); the requester
   * is the destination peripheral. Confirm detect/REQD against the manual. */
  ctrl->hw_trigger = (config->trigger == RZV_DMAC_TRIGGER_HW);

  if (ctrl->hw_trigger)
    {
      chcfg |= DMAC_CHCFG_HIEN;   /* rising-edge activation detect */
      chcfg |= DMAC_CHCFG_REQD;   /* destination peripheral is the requester */
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

  /* Route the ELC activation event (e.g. GPT overflow) to this channel. */
  if (ctrl->hw_trigger)
    {
      ret = rzv_dmac_set_peripheral_source(
              (int)(unit * RZV_DMAC_CHANNELS_PER_UNIT + local_ch),
              config->elc_event);
      if (ret < 0)
        {
          return ret;
        }
    }

  ret = rzv_dmac_convert_cpu_address(config->src_addr, config->length,
                                     &src_bus);
  if (ret < 0)
    {
      return ret;
    }

  ret = rzv_dmac_convert_cpu_address(config->dst_addr, config->length,
                                     &dst_bus);
  if (ret < 0)
    {
      return ret;
    }

  up_clean_dcache(config->src_addr, config->src_addr + config->length);

  if (!ctrl->hw_trigger)
    {
      up_invalidate_dcache(config->dst_addr,
                           config->dst_addr + config->length);
    }

  /* N[0]: initial transfer addresses and byte count */

  putreg32(src_bus, RZV_DMAC_N0SA(unit, local_ch));
  putreg32(dst_bus, RZV_DMAC_N0DA(unit, local_ch));
  putreg32(config->length,   RZV_DMAC_N0TB(unit, local_ch));

  /* N[1]: zero (no double-buffer reload in this configuration) */

  putreg32(0, RZV_DMAC_N1SA(unit, local_ch));
  putreg32(0, RZV_DMAC_N1DA(unit, local_ch));
  putreg32(0, RZV_DMAC_N1TB(unit, local_ch));

  dmainfo("DMAC%d CH%d (global %d) src=0x%08" PRIx32
          " dst=0x%08" PRIx32 " len=%" PRIu32 "\n",
          unit, local_ch,
          (int)(unit * RZV_DMAC_CHANNELS_PER_UNIT + local_ch),
          src_bus, dst_bus, config->length);

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
  irqstate_t flags;
  uint8_t state;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS)
    {
      return -EINVAL;
    }

  unit = RZV_DMAC_UNIT(channel);

  flags = enter_critical_section();
  state = g_dmac_unit_state[unit];

  if (state == RZV_DMAC_UNIT_READY)
    {
      leave_critical_section(flags);
      return OK;
    }

  if (state == RZV_DMAC_UNIT_INITIALIZING)
    {
      leave_critical_section(flags);
      return -EBUSY;
    }

  g_dmac_unit_state[unit] = RZV_DMAC_UNIT_INITIALIZING;
  leave_critical_section(flags);

  /* Enable DMAC CPG clock (API).
   * RZV_CPG_CLK_DMAC uses 2-bit pair encoding; rzv_clock_enable handles it.
   * All units share one clock gate; enabling it multiple times is safe.
   */

  rzv_clock_enable(RZV_CPG_CLK_DMAC);
  rzv_module_unreset(RZV_CPG_CLK_DMAC);

  /* Unmask AXI/AHB bus interface (MSTP) for all five DMAC units.
   * Per RZ/V2H hardware manual, bus stop bits are:
   *   BUS_5_MSTOP  bit 9  (DMAC0)
   *   BUS_3_MSTOP  bit 2  (DMAC1)
   *   BUS_3_MSTOP  bit 3  (DMAC2)
   *   BUS_10_MSTOP bit 11 (DMAC3)
   *   BUS_10_MSTOP bit 12 (DMAC4)
   * Write WEN=1 + data=0 to clear the MSTOP bit (allow bus access).
   * Format: bit[N+16]=WEN, bit[N]=value.  To clear: write (1<<(N+16)).
   */

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
    }

  flags = enter_critical_section();
  g_dmac_unit_state[unit] = RZV_DMAC_UNIT_READY;
  leave_critical_section(flags);

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
  irqstate_t flags;
  int ret;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS || config == NULL)
    {
      return -EINVAL;
    }

  ret = rzv_dmac_validate_config(config);
  if (ret < 0)
    {
      return ret;
    }

  /* Auto-initialize only after the request is known to be valid. */

  ret = rzv_dmac_channel_initialize(channel);
  if (ret < 0)
    {
      return ret;
    }

  ctrl = &g_dmac_channels[channel];

  /* Reserve descriptor setup without making a usable channel visible. */

  flags = enter_critical_section();

  if (ctrl->in_use || ctrl->configuring)
    {
      leave_critical_section(flags);
      dmaerr("Channel %d already in use\n", channel);
      return -EBUSY;
    }

  ctrl->configuring = true;
  leave_critical_section(flags);

  /* Embed configuration; no heap allocation. */

  memcpy(&ctrl->config, config, sizeof(ctrl->config));

  ret = rzv_dmac_setup_channel(ctrl);
  if (ret < 0)
    {
      if (ctrl->hw_trigger)
        {
          rzv_dmac_clear_peripheral_source(channel);
        }

      putreg32(DMAC_CHCTRL_SWRST,
               RZV_DMAC_CHCTRL(ctrl->unit, ctrl->local_ch));

      flags = enter_critical_section();
      memset(&ctrl->config, 0, sizeof(ctrl->config));
      ctrl->configuring = false;
      leave_critical_section(flags);

      return ret;
    }

  flags = enter_critical_section();
  ctrl->open_id = DMAC_OPEN_ID;
  ctrl->in_use = true;
  ctrl->configuring = false;
  leave_critical_section(flags);

  dmainfo("Channel %d configured (unit=%d local=%d)\n",
          channel, ctrl->unit, ctrl->local_ch);
  return OK;
}

/****************************************************************************
 * Name: rzv_dmac_channel_set_buffer
 *
 * Description:
 *   Update N[0] SA/TB and clean the source cache range for the next
 *   transfer.
 *
 ****************************************************************************/

int rzv_dmac_channel_set_buffer(int channel, uintptr_t src_addr,
                                uint32_t length)
{
  struct rzv_dmac_ctrl_s *ctrl;
  irqstate_t flags;
  uint32_t src_bus;
  uint32_t width;
  int ret = OK;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS)
    {
      return -EINVAL;
    }

  ctrl = &g_dmac_channels[channel];

  /* Claim the register update before inspecting the saved configuration.
   * start() and stop() use the same claim, so N0SA/N0TB cannot change while
   * a transfer is being armed or released.
   */

  flags = enter_critical_section();
  if (ctrl->open_id != DMAC_OPEN_ID || !ctrl->in_use)
    {
      leave_critical_section(flags);
      return -EINVAL;
    }

  if (ctrl->operating)
    {
      leave_critical_section(flags);
      return -EBUSY;
    }

  ctrl->operating = true;
  leave_critical_section(flags);

  if (length == 0)
    {
      ret = -EINVAL;
      goto out;
    }

  /* N0DA remains configured for the channel lifetime.  Keeping the byte
   * count fixed ensures a replacement source range cannot exceed the
   * destination range validated during configuration.
   */

  if (length != ctrl->config.length)
    {
      ret = -ENOTSUP;
      goto out;
    }

  width = 1u << (uint32_t)ctrl->config.src_size;
  if ((src_addr & (width - 1u)) != 0u ||
      (length & (width - 1u)) != 0u ||
      (src_addr & (DMAC_CACHE_LINE_SIZE - 1u)) != 0u ||
      rzv_dmac_convert_cpu_address(src_addr, length, &src_bus) < 0)
    {
      ret = -EINVAL;
      goto out;
    }

  /* Check not currently active */

  if (getreg32(RZV_DMAC_CHSTAT(ctrl->unit, ctrl->local_ch)) &
      DMAC_CHSTAT_TACT)
    {
      ret = -EBUSY;
      goto out;
    }

  up_clean_dcache(src_addr, src_addr + length);

  ctrl->config.src_addr = src_addr;

  putreg32(src_bus, RZV_DMAC_N0SA(ctrl->unit, ctrl->local_ch));
  putreg32(length,   RZV_DMAC_N0TB(ctrl->unit, ctrl->local_ch));

out:
  flags = enter_critical_section();
  ctrl->operating = false;
  leave_critical_section(flags);
  return ret;
}

/****************************************************************************
 * Name: rzv_dmac_channel_start
 ****************************************************************************/

int rzv_dmac_channel_start(int channel)
{
  struct rzv_dmac_ctrl_s *ctrl;
  irqstate_t flags;
  uint32_t status;
  uint32_t src_bus;
  uint32_t dst_bus;
  int poll;
  int ret;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS)
    {
      return -EINVAL;
    }

  ctrl = &g_dmac_channels[channel];

  /* Claim the one-shot transfer before touching the hardware.  The claim
   * serializes this sequence against buffer replacement and stop().
   */

  flags = enter_critical_section();
  if (ctrl->open_id != DMAC_OPEN_ID || !ctrl->in_use)
    {
      leave_critical_section(flags);
      return -EINVAL;
    }

  if (ctrl->operating)
    {
      leave_critical_section(flags);
      return -EBUSY;
    }

  ctrl->operating = true;
  leave_critical_section(flags);

  status = getreg32(RZV_DMAC_CHSTAT(ctrl->unit, ctrl->local_ch));
  if (status & DMAC_CHSTAT_TACT)
    {
      ret = -EBUSY;
      goto out;
    }

  /* Clean the source buffer from D-cache at start (not configure): the caller
   * may have filled the buffer after configure(). Source is always memory. */
  up_clean_dcache(ctrl->config.src_addr,
                  ctrl->config.src_addr + ctrl->config.length);

  /* Reset before SETEN to clear stale END/ER flags from a
   * previous transfer.  SWRST must be issued first; without it, stale flags
   * can re-trigger callbacks or corrupt the channel state machine.
   */

  putreg32(DMAC_CHCTRL_SWRST,
           RZV_DMAC_CHCTRL(ctrl->unit, ctrl->local_ch));

  ret = rzv_dmac_convert_cpu_address(ctrl->config.src_addr,
                                     ctrl->config.length, &src_bus);
  if (ret < 0)
    {
      goto out;
    }

  ret = rzv_dmac_convert_cpu_address(ctrl->config.dst_addr,
                                     ctrl->config.length, &dst_bus);
  if (ret < 0)
    {
      goto out;
    }

  /* SWRST clears completion state. Reload N[0] so a completed one-shot
   * transfer can be armed again without reconfiguring or releasing it. */

  putreg32(src_bus, RZV_DMAC_N0SA(ctrl->unit, ctrl->local_ch));
  putreg32(dst_bus, RZV_DMAC_N0DA(ctrl->unit, ctrl->local_ch));
  putreg32(ctrl->config.length,
           RZV_DMAC_N0TB(ctrl->unit, ctrl->local_ch));

  /* Drain the store buffer before asserting SETEN.
   * The Cortex-R8 store buffer may reorder the descriptor register writes
   * (N0SA/N0DA/N0TB) relative to SETEN unless Device-nGnRE mapping is
   * guaranteed.  Insert DSB as a defensive barrier.
   */

  ARM_DSB();

  /* Enable channel */

  putreg32(DMAC_CHCTRL_SETEN,
           RZV_DMAC_CHCTRL(ctrl->unit, ctrl->local_ch));

  /* The hardware requires EN before STG.  Do not issue the trigger when
   * SETEN did not take effect; reset leaves the owner available for stop().
   */

  for (poll = 0; poll < DMAC_START_TIMEOUT_POLLS; poll++)
    {
      if (getreg32(RZV_DMAC_CHSTAT(ctrl->unit, ctrl->local_ch)) &
          DMAC_CHSTAT_EN)
        {
          break;
        }
    }

  if (poll == DMAC_START_TIMEOUT_POLLS)
    {
      putreg32(DMAC_CHCTRL_SWRST,
               RZV_DMAC_CHCTRL(ctrl->unit, ctrl->local_ch));
      ret = -ETIMEDOUT;
      goto out;
    }

  /* Software trigger only for memory-to-memory. Hardware(ELC)-triggered
   * channels are now armed and transfer on each peripheral activation event
   * (e.g. GPT overflow); issuing STG would force an extra spurious transfer. */
  if (!ctrl->hw_trigger)
    {
      putreg32(DMAC_CHCTRL_STG,
               RZV_DMAC_CHCTRL(ctrl->unit, ctrl->local_ch));
    }

  flags = enter_critical_section();
  ctrl->operating = false;
  leave_critical_section(flags);

  dmainfo("Channel %d started\n", channel);
  return OK;

out:
  /* Hardware is idle (reset or never enabled); release the claim so the
   * channel is reusable without a mandatory stop(). */
  flags = enter_critical_section();
  ctrl->operating = false;
  leave_critical_section(flags);
  return ret;
}

static int rzv_dmac_channel_disable_internal(int channel, bool release)
{
  struct rzv_dmac_ctrl_s *ctrl;
  uint32_t status;
  irqstate_t flags;
  int timeout;
  int ret = OK;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS)
    {
      return -EINVAL;
    }

  ctrl = &g_dmac_channels[channel];

  /* Claim stop before issuing CLREN.  Do not keep interrupts disabled while
   * polling hardware or maintaining the data cache.
   */

  flags = enter_critical_section();
  if (ctrl->open_id != DMAC_OPEN_ID)
    {
      leave_critical_section(flags);
      return -EINVAL;
    }

  if (ctrl->operating)
    {
      leave_critical_section(flags);
      return -EBUSY;
    }

  ctrl->operating = true;
  leave_critical_section(flags);

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

      up_udelay(10);
    }
  while (--timeout > 0);

  if (timeout == 0)
    {
      dmaerr("Channel %d stop timeout — forcing reset\n", channel);
      ret = -ETIMEDOUT;
    }

  if (status & DMAC_CHSTAT_ER ||
      getreg32(RZV_DMAC_DSTAT_ER(ctrl->unit,
                                 RZV_DMAC_GRP(ctrl->local_ch))) &
      (1u << RZV_DMAC_GRP_CH(ctrl->local_ch)))
    {
      ret = -EIO;
    }

  /* Clear pending flags */

  putreg32(DMAC_CHCTRL_CLREND | DMAC_CHCTRL_CLRTC,
           RZV_DMAC_CHCTRL(ctrl->unit, ctrl->local_ch));

  putreg32(DMAC_CHCTRL_SWRST,
           RZV_DMAC_CHCTRL(ctrl->unit, ctrl->local_ch));

  if (!ctrl->hw_trigger)
    {
      up_invalidate_dcache(ctrl->config.dst_addr,
                           ctrl->config.dst_addr + ctrl->config.length);
    }

  if (release && ctrl->hw_trigger)
    {
      int route_ret = rzv_dmac_clear_peripheral_source(channel);

      if (ret == OK && route_ret < 0)
        {
          ret = route_ret;
        }
    }

  flags = enter_critical_section();
  ctrl->operating = false;

  if (release)
    {
      ctrl->in_use      = false;
      ctrl->configuring = false;
      ctrl->hw_trigger  = false;
      ctrl->open_id     = 0;
      memset(&ctrl->config, 0, sizeof(ctrl->config));
    }

  leave_critical_section(flags);

  dmainfo("Channel %d %s\n", channel,
          release ? "released" : "disabled");
  return ret;
}

/****************************************************************************
 * Name: rzv_dmac_channel_disable
 *
 * Description:
 *   Stop the current transfer but retain ownership and configuration so the
 *   channel can be re-armed.
 *
 ****************************************************************************/

int rzv_dmac_channel_disable(int channel)
{
  return rzv_dmac_channel_disable_internal(channel, false);
}

/****************************************************************************
 * Name: rzv_dmac_channel_stop
 *
 * Description:
 *   Stop the current transfer and release channel ownership and routing.
 *
 ****************************************************************************/

int rzv_dmac_channel_stop(int channel)
{
  return rzv_dmac_channel_disable_internal(channel, true);
}

/****************************************************************************
 * Name: rzv_dmac_channel_status
 ****************************************************************************/

uint32_t rzv_dmac_channel_status(int channel)
{
  struct rzv_dmac_ctrl_s *ctrl;
  uint32_t status;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS)
    {
      return 0;
    }

  ctrl = &g_dmac_channels[channel];

  if (ctrl->open_id != DMAC_OPEN_ID)
    {
      return 0;
    }

  status = getreg32(RZV_DMAC_CHSTAT(ctrl->unit, ctrl->local_ch));
  if (getreg32(RZV_DMAC_DSTAT_ER(ctrl->unit,
                                 RZV_DMAC_GRP(ctrl->local_ch))) &
      (1u << RZV_DMAC_GRP_CH(ctrl->local_ch)))
    {
      status |= DMAC_CHSTAT_ER;
    }

  return status;
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
 *   Route an ELC activation event (e.g. a GPT overflow) to a DMAC channel so
 *   the channel transfers one unit per event (hardware-triggered mode). Mirrors
 *   the FSP r_dmac_b activation-source scheme (bsp_dmac.h
 *   R_BSP_DMAC_ACTIVATION_SOURCE_ENABLE): per-unit INTC DM{k}SEL register block,
 *   2 channels per 32-bit register (16-bit field each), event masked to 10 bits.
 *   Unit -> block order per FSP DMkSELy_TABLE: 0->DM4, 1->DM0, 2->DM1, 3->DM2,
 *   4->DM3. Register offsets match the checked-in R9A09G057H CR CMSIS
 *   R_INTC_Type layout.
 *
 ****************************************************************************/

#define RZV_INTC_DMKSEL_EVENT_MASK   0x3FFu   /* 10-bit activation event field */

static int rzv_dmac_get_dmksel_field(int channel, uintptr_t *reg,
                                    uint32_t *shift)
{
  static const uint32_t dmksel_block_offset[RZV_DMAC_NUM_UNITS] =
  {
    RZV_INTC_DM4SEL0_OFFSET,
    RZV_INTC_DM0SEL0_OFFSET,
    RZV_INTC_DM1SEL0_OFFSET,
    RZV_INTC_DM2SEL0_OFFSET,
    RZV_INTC_DM3SEL0_OFFSET,
  };

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS ||
      reg == NULL || shift == NULL)
    {
      return -EINVAL;
    }

  uint32_t unit     = (uint32_t)channel / RZV_DMAC_CHANNELS_PER_UNIT;
  uint32_t local_ch = (uint32_t)channel % RZV_DMAC_CHANNELS_PER_UNIT;

  *reg = RZV_INTC_BASE + dmksel_block_offset[unit] +
         (uintptr_t)(local_ch / 2u) * 4u;
  *shift = (local_ch % 2u) * 16u;
  return OK;
}

int rzv_dmac_set_peripheral_source(int channel, int elc_event)
{
  uintptr_t reg;
  uint32_t shift;
  uint32_t val;
  irqstate_t flags;
  int ret;

  if (elc_event < 0 || elc_event >= (int)RZV_INTC_DMKSEL_EVENT_MASK)
    {
      return -EINVAL;
    }

  ret = rzv_dmac_get_dmksel_field(channel, &reg, &shift);
  if (ret < 0)
    {
      return ret;
    }

  flags = enter_critical_section();
  val = getreg32(reg);

  val &= ~(RZV_INTC_DMKSEL_EVENT_MASK << shift);
  val |= ((uint32_t)elc_event & RZV_INTC_DMKSEL_EVENT_MASK) << shift;
  putreg32(val, reg);
  leave_critical_section(flags);

  return OK;
}

static int rzv_dmac_clear_peripheral_source(int channel)
{
  uintptr_t reg;
  uint32_t shift;
  irqstate_t flags;
  int ret;

  ret = rzv_dmac_get_dmksel_field(channel, &reg, &shift);
  if (ret < 0)
    {
      return ret;
    }

  flags = enter_critical_section();
  modifyreg32(reg, 0, RZV_INTC_DMKSEL_EVENT_MASK << shift);
  leave_critical_section(flags);
  return OK;
}

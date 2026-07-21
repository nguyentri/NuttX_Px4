/****************************************************************************
 * arch/arm/src/rzv/rzv_dmac.h
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

/* RZV2H DMAC_B driver public API
 *
 * Hardware model: DMAC_B is grouped — 8 channels per group, 2 groups per
 * unit, 5 units total = 80 channels.  Register layout is NOT a flat
 * ch*0x40 array; see hardware/rzv_dmac.h for full decomposition.
 *
 * Supported scope: CR8-0 one-shot register mode with software-triggered
 * memory transfers or INTC-routed hardware-triggered memory-to-peripheral
 * transfers. Callbacks, link mode, and dynamic allocation are unsupported.
 *
 * CPU-address and cache contract:
 *   Callers pass CPU addresses.  The driver converts CR8-0 ITCM/DTCM views
 *   to DMAC bus aliases and maintains cache ranges using the original CPU
 *   addresses.  Buffers must meet the documented cache-line and transfer
 *   width alignment requirements.
 */

#ifndef __ARCH_ARM_SRC_RZV_DMAC_H
#define __ARCH_ARM_SRC_RZV_DMAC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DMA channel IDs (global, 0-79)
 * Channels 0-15  = DMAC unit 0 (group 0: 0-7, group 1: 8-15)
 * Channels 16-31 = DMAC unit 1, etc.
 * API doc: valid range is 0 .. (NR_DMAC_CHANNELS - 1) = 0..79
 */

#define RZV_DMAC_CHANNEL_0          0
#define RZV_DMAC_CHANNEL_1          1
#define RZV_DMAC_CHANNEL_2          2
#define RZV_DMAC_CHANNEL_3          3
#define RZV_DMAC_CHANNEL_4          4
#define RZV_DMAC_CHANNEL_5          5
#define RZV_DMAC_CHANNEL_6          6
#define RZV_DMAC_CHANNEL_7          7
#define RZV_DMAC_CHANNEL_COUNT      80

/* DMAC event codes reserved for a future callback-capable driver. */

#define RZV_DMAC_EVENT_COMPLETE     (0)  /* Transfer complete (END flag) */
#define RZV_DMAC_EVENT_ERROR        (1)  /* Transfer error (ER flag) */

/* DMAC channel status flags (matches CHSTAT register bits) */

#define RZV_DMAC_STATUS_EN          (1u << 0)  /* Channel enabled */
#define RZV_DMAC_STATUS_RQST        (1u << 1)  /* Request pending */
#define RZV_DMAC_STATUS_TACT        (1u << 2)  /* Transfer active */
#define RZV_DMAC_STATUS_SUS         (1u << 3)  /* Suspended */
#define RZV_DMAC_STATUS_ER          (1u << 4)  /* Error */
#define RZV_DMAC_STATUS_END         (1u << 5)  /* Transfer end */
#define RZV_DMAC_STATUS_TC          (1u << 6)  /* Transfer count match */
#define RZV_DMAC_STATUS_SR          (1u << 7)  /* Software request */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* DMAC_B Transfer Size (maps to SDS/DDS CHCFG field, 4-bit log2 encoding) */

typedef enum
{
  RZV_DMAC_SIZE_1BYTE   = 0,  /* 1-byte transfers */
  RZV_DMAC_SIZE_2BYTE   = 1,  /* 2-byte transfers */
  RZV_DMAC_SIZE_4BYTE   = 2,  /* 4-byte transfers */
  RZV_DMAC_SIZE_8BYTE   = 3,  /* 8-byte transfers */
  RZV_DMAC_SIZE_16BYTE  = 4,  /* 16-byte transfers */
  RZV_DMAC_SIZE_32BYTE  = 5,  /* 32-byte transfers */
  RZV_DMAC_SIZE_64BYTE  = 6,  /* 64-byte transfers */
  RZV_DMAC_SIZE_128BYTE = 7   /* 128-byte transfers */
} rzv_dmac_size_t;

/* DMAC_B Address Mode (maps to SAD/DAD bits in CHCFG)
 * Only INCREMENT (0) and FIXED (1) are used on RZV2H.
 * SAD/DAD are single bits: 0 = increment, 1 = fixed.
 */

typedef enum
{
  RZV_DMAC_ADDR_INCREMENT = 0, /* Increment address after each transfer */
  RZV_DMAC_ADDR_FIXED     = 1  /* Fixed address (peripheral FIFO) */
} rzv_dmac_addr_mode_t;

/* DMAC_B Trigger Mode */

typedef enum
{
  RZV_DMAC_TRIGGER_SW = 0,  /* Software trigger (STG bit) */
  RZV_DMAC_TRIGGER_HW = 1   /* Hardware trigger via INTC DMkSEL event route */
} rzv_dmac_trigger_t;

/* DMAC callback function type.
 * Callbacks are not supported by this polling-only driver and must be NULL.
 * Parameters:
 *   channel   - global channel number (0..79)
 *   event     - RZV_DMAC_EVENT_COMPLETE or RZV_DMAC_EVENT_ERROR
 *   user_data - caller-supplied opaque pointer
 */

typedef void (*rzv_dmac_callback_t)(int channel, int event, void *user_data);

/* DMAC_B channel configuration.
 * Embedded in g_dmac_channels[] static array — no heap allocation.
 */

struct rzv_dmac_config_s
{
  rzv_dmac_size_t       src_size;        /* Source transfer width */
  rzv_dmac_size_t       dst_size;        /* Destination transfer width */
  rzv_dmac_addr_mode_t  src_addr_mode;   /* Source address mode */
  rzv_dmac_addr_mode_t  dst_addr_mode;   /* Destination address mode */
  rzv_dmac_trigger_t    trigger;         /* Trigger mode */

  uintptr_t             src_addr;        /* Source CPU address */
  uintptr_t             dst_addr;        /* Destination CPU address */
  uint32_t              length;          /* Transfer length in bytes */

  uint8_t               priority;        /* Channel priority (0-7) */
  uint16_t              transfer_interval;

  int                   elc_event;       /* ELC event for HW trigger (-1=none) */

  rzv_dmac_callback_t   callback;        /* Must be NULL */
  void                 *user_data;       /* Reserved; ignored */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Name: rzv_dmac_channel_initialize
 *
 * Description:
 *   Initialize a DMAC unit.  Enables CPG clock, releases reset, and
 *   initialises both groups' DCTRL registers.  Safe to call multiple times;
 *   subsequent calls on an already-initialized unit are no-ops.
 *
 * Input Parameters:
 *   channel - Any global channel belonging to the target unit (0..79).
 *             The unit is derived as channel / 16.
 *
 * Returned Value:
 *   Zero (OK) on success; negated errno on failure.
 *
 ****************************************************************************/

int rzv_dmac_channel_initialize(int channel);

/****************************************************************************
 * Name: rzv_dmac_channel_configure
 *
 * Description:
 *   Configure a DMAC channel for transfer. Writes CHCFG, CHEXT, CHITVL,
 *   the N[0] address/count registers, and any requested INTC event route.
 *   Completion is polled; no heap allocation is used.
 *
 * Input Parameters:
 *   channel - Global channel (0..79).
 *   config  - Configuration structure; copied during configuration.
 *
 * Returned Value:
 *   Zero (OK) on success; -EINVAL on bad parameters; -EBUSY if already
 *   active.
 *
 ****************************************************************************/

int rzv_dmac_channel_configure(int channel,
                               const struct rzv_dmac_config_s *config);

/****************************************************************************
 * Name: rzv_dmac_channel_set_buffer
 *
 * Description:
 *   Update the source address for the next memory transfer without
 *   reconfiguring the channel.  The byte count must match the configured
 *   transfer length because the destination range is not changed.
 *
 *   Performs up_clean_dcache() on [src_addr, src_addr+length) for TX
 *   channels (i.e., when src_addr_mode == INCREMENT).  Caller is responsible
 *   for alignment to D-cache line size (32 bytes on Cortex-R8).
 *
 * Input Parameters:
 *   channel  - Global channel (0..79); must be configured and not active.
 *   src_addr - New source CPU address.
 *   length   - Configured transfer length in bytes.
 *
 * Returned Value:
 *   Zero (OK) on success; -EINVAL if channel not configured; -EBUSY if
 *   transfer is active; -ENOTSUP if length differs from the configured
 *   transfer length.
 *
 ****************************************************************************/

int rzv_dmac_channel_set_buffer(int channel, uintptr_t src_addr,
                                uint32_t length);

/****************************************************************************
 * Name: rzv_dmac_channel_start
 *
 * Description:
 *   Re-arm the channel and issue STG for software-triggered transfers.
 *   Hardware-triggered transfers wait for the configured peripheral event.
 *
 * Input Parameters:
 *   channel - Global channel (0..79).
 *
 * Returned Value:
 *   Zero (OK) on success; -EBUSY if already active; -EINVAL on bad state.
 *
 ****************************************************************************/

int rzv_dmac_channel_start(int channel);

/****************************************************************************
 * Name: rzv_dmac_channel_disable
 *
 * Description:
 *   Disable a transfer while retaining the configured channel and hardware
 *   trigger route. The channel may be started again without reconfiguration.
 *
 ****************************************************************************/

int rzv_dmac_channel_disable(int channel);

/****************************************************************************
 * Name: rzv_dmac_channel_stop
 *
 * Description:
 *   Disable the channel, clear its trigger route, and release ownership.
 *
 * Input Parameters:
 *   channel - Global channel (0..79).
 *
 * Returned Value:
 *   Zero (OK) on success; -EINVAL on bad channel or not configured.
 *
 ****************************************************************************/

int rzv_dmac_channel_stop(int channel);

/****************************************************************************
 * Name: rzv_dmac_channel_status
 *
 * Description:
 *   Read the raw CHSTAT register for the given channel.
 *
 * Input Parameters:
 *   channel - Global channel (0..79).
 *
 * Returned Value:
 *   CHSTAT value; 0 if channel is invalid or not initialized.
 *
 ****************************************************************************/

uint32_t rzv_dmac_channel_status(int channel);

/****************************************************************************
 * Name: rzv_dmac_get_remaining_bytes
 *
 * Description:
 *   Read the current remaining transfer count (CRTB register).
 *
 * Input Parameters:
 *   channel - Global channel (0..79).
 *
 * Returned Value:
 *   Remaining bytes; 0 if invalid.
 *
 ****************************************************************************/

uint32_t rzv_dmac_get_remaining_bytes(int channel);

/****************************************************************************
 * Name: rzv_dmac_set_peripheral_source
 *
 * Description:
 *   Route a 10-bit DMAC activation-source number to a hardware-triggered
 *   channel through the corresponding INTC DMkSEL field.
 *
 * Input Parameters:
 *   channel   - Global DMAC channel (0..79).
 *   elc_event - DMAC activation-source number (0..1022); 1023 disables a route.
 *
 * Returned Value:
 *   OK on success; -EINVAL for an invalid channel, event, or selector.
 *
 ****************************************************************************/

int rzv_dmac_set_peripheral_source(int channel, int elc_event);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RZV_DMAC_H */

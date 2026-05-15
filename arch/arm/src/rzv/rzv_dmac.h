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
 * Callback-from-ISR contract:
 *   rzv_dmac_callback_t is invoked directly from the DMAC interrupt handler
 *   (hard IRQ context).  Callbacks MUST NOT:
 *     - block or call any sleeping function
 *     - take mutexes or semaphores that could be held by non-ISR code
 *     - call rzv_dmac_channel_configure() or rzv_dmac_channel_stop()
 *   Callbacks MAY:
 *     - post a semaphore or send a work-queue item
 *     - call rzv_dmac_channel_start() to re-arm a prepared channel
 *     - call rzv_dmac_channel_set_buffer() to update addresses then start
 *
 * Cache alignment contract for callers:
 *   TX buffers: caller must ensure the buffer is D-cache line aligned
 *     (32 bytes for Cortex-R8) before calling rzv_dmac_channel_set_buffer().
 *     rzv_dmac_channel_set_buffer() will call up_clean_dcache() internally.
 *   RX buffers: provided buffer must be D-cache line aligned and sized to a
 *     cache line multiple.  The DMAC ISR calls up_invalidate_dcache() on
 *     completion before invoking the user callback.
 *
 * Link mode: NOT supported by this driver.  DMAC_B N[0]/N[1] double-buffer
 *   reload is used instead (register mode with RSEL auto-swap).  The old
 *   RZV_DMAC_MODE_LINK enum has been removed to prevent misuse.
 *
 * VA→PA translation assumption:
 *   CR8 boot on RDK-RZV2H uses identity mapping for DDR (VA == PA).
 *   No up_addrenv_va_to_pa() call is made.  If user-space DMA buffers are
 *   ever required, callers must translate before passing addresses.
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

/* DMAC Event codes passed to callbacks */

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
  RZV_DMAC_TRIGGER_HW = 1   /* Hardware trigger via DMACKSEL peripheral event */
} rzv_dmac_trigger_t;

/* DMAC callback function type.
 * Called from ISR context — see callback-from-ISR contract above.
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

  uint32_t              src_addr;        /* Source address (PA on CR8) */
  uint32_t              dst_addr;        /* Destination address (PA on CR8) */
  uint32_t              length;          /* Transfer length in bytes */

  uint8_t               priority;        /* Channel priority (0-7) */
  uint16_t              transfer_interval; /* Transfer interval (CHITVL) */

  int                   elc_event;       /* ELC event for HW trigger (-1=none) */

  rzv_dmac_callback_t   callback;        /* Transfer complete/error callback */
  void                 *user_data;       /* Opaque pointer passed to callback */
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
 *   Configure a DMAC channel for transfer.  Writes CHCFG, CHEXT, CHITVL
 *   and the N[0] address/count registers.  Attaches the DMAEND interrupt
 *   via rzv_icu_attach() if a callback is provided.  No heap allocation.
 *
 * Input Parameters:
 *   channel - Global channel (0..79).
 *   config  - Configuration structure; must remain valid until channel_stop.
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
 *   Update the source address and byte count for the next transfer without
 *   reconfiguring the channel.  Intended for use by peripheral drivers
 *   (e.g., rzv_serial.c rzv_dma_send) to re-arm a pre-configured channel.
 *
 *   Performs up_clean_dcache() on [src_addr, src_addr+length) for TX
 *   channels (i.e., when src_addr_mode == INCREMENT).  Caller is responsible
 *   for alignment to D-cache line size (32 bytes on Cortex-R8).
 *
 * Input Parameters:
 *   channel  - Global channel (0..79); must be configured and not active.
 *   src_addr - New source physical address.
 *   length   - New transfer length in bytes.
 *
 * Returned Value:
 *   Zero (OK) on success; -EINVAL if channel not configured; -EBUSY if
 *   transfer is active.
 *
 ****************************************************************************/

int rzv_dmac_channel_set_buffer(int channel, uint32_t src_addr,
                                uint32_t length);

/****************************************************************************
 * Name: rzv_dmac_channel_start
 *
 * Description:
 *   Enable the channel (SETEN) and, for software trigger, issue STG.
 *   For hardware trigger the transfer begins when the peripheral event fires.
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
 * Name: rzv_dmac_channel_stop
 *
 * Description:
 *   Disable the channel, wait for TACT to clear (up to 10 ms), and detach
 *   the interrupt.  Runs under enter_critical_section() to prevent
 *   concurrent IRQ delivery during the stop sequence.
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
 *   Program the INTC DMACKSEL register to route an ELC peripheral event to
 *   this DMAC channel.  Required for hardware-triggered DMA (e.g., SCI TXI
 *   event → DMAC channel for UART TX).
 *
 *   DMACKSEL0 offset (0x0BCC) is derived from intc_iodefine.h
 *   (R9A09G057H CR variant) struct layout.  Register write is active.
 *
 * Input Parameters:
 *   channel   - Global DMAC channel (0..79).
 *   elc_event - ELC event number (from hardware/rzv_elc.h ELC_EVENT_* or
 *               RZV_ELC_* values).  Use -1 to clear.
 *
 * Returned Value:
 *   Zero (OK) on success; -EINVAL on bad channel.
 *
 ****************************************************************************/

int rzv_dmac_set_peripheral_source(int channel, int elc_event);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RZV_DMAC_H */

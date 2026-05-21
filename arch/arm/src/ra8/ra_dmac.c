/****************************************************************************
 * arch/arm/src/ra8/ra_dmac.c
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
#include <inttypes.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/kmalloc.h>
#include <nuttx/spinlock.h>

#include <arch/board/board.h>

#include "arm_internal.h"
#include "chip.h"
#include "hardware/ra_memorymap.h"
#include "ra_icu.h"
#include "ra_mstp.h"
#include "ra_dmac.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define DMAC_OPEN_ID             (0x444d4143)  /* "DMAC" in ASCII */
#define DMAC_ALIGNMENT_CHECK(addr, size) \
  (((uint32_t)(addr)) & ((1 << (size)) - 1))

/* DMAC Control Register values */
#define DMAC_DMCNT_DTE           (0x01)
#define DMAC_DMREQ_SWREQ         (0x01)

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* DMAC context control structure */

typedef struct ra_dmac_ctrl_s
{
  uint32_t             open_id;        /* Open ID for validation */
  uint8_t              channel;        /* DMAC channel number */
  bool                 in_use;         /* Channel in use flag */
  bool                 enabled;        /* Channel enabled flag */
  ra_dmac_config_t    *config;         /* Transfer configuration */
  int                  irq_end;        /* IRQ slot number of DMA end */
  int                  irq_err;        /* IRQ slot number of DMA error */
} ra_dmac_ctrl_t;

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* DMAC channel control blocks */
static ra_dmac_ctrl_t g_dmac_channels[DMAC_MAX_CHANNELS];

/* DMAC module initialized flag */
static bool g_dmac_initialized = false;

/* Spinlock for thread-safe channel allocation/deallocation */
static spinlock_t g_dmac_lock = SP_UNLOCKED;

/* MSTP reference count - tracks number of active channels.
 * When this drops to zero, the DMAC module can be powered down.
 */
static uint8_t g_dmac_refcount = 0;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_dmac_validate_config
 *
 * Description:
 *   Validate DMAC configuration
 *
 ****************************************************************************/

static int ra_dmac_validate_config(const ra_dmac_config_t *config)
{
  if (config == NULL)
    {
      return -EINVAL;
    }

  /* Check transfer length based on mode */

  switch (config->mode)
    {
      case RA_DMAC_MODE_NORMAL:
        if (config->transfer_count == 0 ||
            config->transfer_count > RA_DMAC_MAX_NORMAL_LENGTH)
          {
            return -EINVAL;
          }
        break;

      case RA_DMAC_MODE_REPEAT:
        if (config->transfer_count == 0 ||
            config->transfer_count > RA_DMAC_MAX_REPEAT_LENGTH)
          {
            return -EINVAL;
          }
        break;

      case RA_DMAC_MODE_BLOCK:
        if (config->transfer_count == 0 ||
            config->transfer_count > RA_DMAC_MAX_REPEAT_LENGTH)
          {
            return -EINVAL;
          }

        /* Validate block count for block transfer mode */

        if (config->block_count == 0 ||
            config->block_count > RA_DMAC_MAX_BLOCK_COUNT)
          {
            return -EINVAL;
          }
        break;

      default:
        return -EINVAL;
    }

  /* Validate repeat_area setting */

  if (config->repeat_area > RA_DMAC_REPEAT_AREA_NONE)
    {
      return -EINVAL;
    }

  /* Check address alignment */

  if (DMAC_ALIGNMENT_CHECK(config->src_addr, config->size) ||
      DMAC_ALIGNMENT_CHECK(config->dest_addr, config->size))
    {
      return -EINVAL;
    }

  return OK;
}

/****************************************************************************
 * Name: ra_dmac_setup_channel
 *
 * Description:
 *   Setup DMAC channel registers
 *
 ****************************************************************************/

static int ra_dmac_setup_channel(ra_dmac_ctrl_t *ctrl)
{
  ra_dmac_config_t *config = ctrl->config;
  uint8_t channel = ctrl->channel;
  uint32_t dmtmd = 0;
  uint32_t dmamd = 0;
  uint32_t dmint = 0;

  /* Setup Transfer Mode Register (DMTMD)
   * DCTG[1:0] - Transfer request source (SW=0, HW=1)
   * SZ[9:8]   - Transfer data size
   * DTS[13:12]- Repeat/block area select (separate from mode)
   * MD[15:14] - Transfer mode (normal/repeat/block)
   */

  dmtmd |= (config->trigger << R_DMAC_DMTMD_DCTG_SHIFT) &
           R_DMAC_DMTMD_DCTG_MASK;
  dmtmd |= (config->size << R_DMAC_DMTMD_SZ_SHIFT) &
           R_DMAC_DMTMD_SZ_MASK;
  dmtmd |= (config->repeat_area << R_DMAC_DMTMD_DTS_SHIFT) &
           R_DMAC_DMTMD_DTS_MASK;
  dmtmd |= (config->mode << R_DMAC_DMTMD_MD_SHIFT) &
           R_DMAC_DMTMD_MD_MASK;

  /* Setup Address Mode Register (DMAMD) */
  dmamd |= (config->dest_addr_mode << R_DMAC_DMAMD_DM_SHIFT) & R_DMAC_DMAMD_DM_MASK;
  dmamd |= (config->src_addr_mode << R_DMAC_DMAMD_SM_SHIFT) & R_DMAC_DMAMD_SM_MASK;

  /* Setup Interrupt Setting Register (DMINT) */
  if (config->callback != NULL)
    {
      dmint |= R_DMAC_DMINT_DTIE;  /* Enable transfer complete interrupt */
    }

  /* Write registers */
  putreg32(config->src_addr, R_DMAC_DMSAR(channel));
  putreg32(config->dest_addr, R_DMAC_DMDAR(channel));
  putreg32(config->transfer_count, R_DMAC_DMCRA(channel));
  putreg32(config->block_count, R_DMAC_DMCRB(channel));
  putreg32(dmtmd, R_DMAC_DMTMD(channel));
  putreg32(dmamd, R_DMAC_DMAMD(channel));
  putreg8(dmint, R_DMAC_DMINT(channel));

  return OK;
}

/****************************************************************************
 * Name: ra_dmac_interrupt_handler
 *
 * Description:
 *   DMAC interrupt handler
 *
 ****************************************************************************/

static int ra_dmac_interrupt_handler(int irq, void *context, void *arg)
{
  ra_dmac_ctrl_t *ctrl = (ra_dmac_ctrl_t *)arg;
  uint8_t status;

  if (ctrl == NULL || ctrl->open_id != DMAC_OPEN_ID)
    {
      return OK;
    }

  /* Read status (8-bit register) */

  status = getreg8(R_DMAC_DMSTS(ctrl->channel));

  if (status & R_DMAC_DMSTS_DTIF)
    {
      /* Clear interrupt flag by writing 0 to DTIF bit
       * (write 0 to clear, preserve other bits)
       */

      putreg8(status & ~R_DMAC_DMSTS_DTIF, R_DMAC_DMSTS(ctrl->channel));

      /* Call user callback */

      if (ctrl->config && ctrl->config->callback)
        {
          ctrl->config->callback(ctrl, RA_DMAC_EVENT_COMPLETE,
                                 ctrl->config->user_data);
        }
    }

  if (status & R_DMAC_DMSTS_ESIF)
    {
      /* Clear escape end interrupt flag */

      putreg8(status & ~R_DMAC_DMSTS_ESIF, R_DMAC_DMSTS(ctrl->channel));

      /* Read DMECHR to identify error channel and status.
       * DMECHR provides:
       *   - DMECH[3:0]: Error channel number (0-7 within unit)
       *   - DMECHSAM[8]: Security attribution monitor
       *   - DMESTA[16]: Error status (1 = error occurred)
       */

      uint8_t unit = DMAC_GET_UNIT(ctrl->channel);
      uint32_t dmechr = getreg32(R_DMA_DMECHR_UNIT(unit));

      if (dmechr & R_DMA_DMECHR_DMESTA)
        {
          uint8_t error_ch = (dmechr & R_DMA_DMECHR_DMECH_MASK) >>
                             R_DMA_DMECHR_DMECH_SHIFT;
          dmaerr("DMAC Unit %d error on local channel %d (global ch %d)\n",
                 unit, error_ch, ctrl->channel);
        }

      /* Call user callback with error event */

      if (ctrl->config && ctrl->config->callback)
        {
          ctrl->config->callback(ctrl, RA_DMAC_EVENT_ERROR,
                                 ctrl->config->user_data);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_dmac_find_free_channel
 *
 * Description:
 *   Find a free DMAC channel
 *
 ****************************************************************************/

static int ra_dmac_find_free_channel(void)
{
  irqstate_t flags;
  int i;
  int ret = -ENOMEM;

  flags = spin_lock_irqsave(&g_dmac_lock);

  for (i = 0; i <= DMAC_MAX_CHANNEL_NUM; i++)
    {
      /* Skip invalid channels using helper macro */

      if (!DMAC_IS_VALID_CHANNEL(i))
        {
          continue;
        }

      if (!g_dmac_channels[i].in_use)
        {
          g_dmac_channels[i].in_use = true;  /* Reserve immediately */
          ret = i;
          break;
        }
    }

  spin_unlock_irqrestore(&g_dmac_lock, flags);
  return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_dmac_initialize
 *
 * Description:
 *   Initialize the DMAC module
 *
 ****************************************************************************/

int ra_dmac_initialize(void)
{
  int i;

  if (g_dmac_initialized)
    {
      return OK;
    }

  /* Enable DMAC/DTC module clock via MSTP */

  ra_mstp_start(RA_MSTP_DMAC);


  /* Enable DMAC global operation for both units (DMAST.DMST = 1) */

  putreg32(R_DMA_DMAST_DMST, R_DMA_DMAST_UNIT(0));
#if defined (CONFIG_RA8P1_GROUP)
  putreg32(R_DMA_DMAST_DMST, R_DMA_DMAST_UNIT(1));
#endif
  /* Set default priority mode to fixed priority (channel 0 highest)
   * This can be changed later with ra_dmac_set_priority_mode()
   */

  putreg32(0, R_DMA_DMCTL_UNIT(0));  /* PR=0: Fixed priority */
#if defined (CONFIG_RA8P1_GROUP)
  putreg32(0, R_DMA_DMCTL_UNIT(1));  /* PR=0: Fixed priority */
#endif
  /* Initialize channel control blocks for all valid channels */

  for (i = 0; i <= DMAC_MAX_CHANNEL_NUM; i++)
    {
      /* Skip invalid channels in the gap */

      if (!DMAC_IS_VALID_CHANNEL(i))
        {
          continue;
        }

      memset(&g_dmac_channels[i], 0, sizeof(ra_dmac_ctrl_t));
      g_dmac_channels[i].channel = i;
      g_dmac_channels[i].irq_end = -1;
      g_dmac_channels[i].irq_err = -1;
    }

  /* Initialize reference count */

  g_dmac_refcount = 0;
  g_dmac_initialized = true;

  dmainfo("DMAC initialized successfully (both units enabled)\n");
  return OK;
}

/****************************************************************************
 * Name: ra_dmac_set_priority_mode
 *
 * Description:
 *   Set the DMAC priority mode for a specific unit.
 *   - Fixed priority: Lower channel numbers have higher priority
 *   - Round-robin: All channels have equal priority (rotation)
 *
 * Input Parameters:
 *   unit - DMAC unit number (0 or 1)
 *   mode - Priority mode (RA_DMAC_PRIORITY_FIXED or RA_DMAC_PRIORITY_ROUND_ROBIN)
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 ****************************************************************************/

int ra_dmac_set_priority_mode(int unit, ra_dmac_priority_mode_t mode)
{
  uint32_t dmctl;

  if (unit < 0 || unit > 1)
    {
      return -EINVAL;
    }

  dmctl = getreg32(R_DMA_DMCTL_UNIT(unit));

  if (mode == RA_DMAC_PRIORITY_ROUND_ROBIN)
    {
      dmctl |= R_DMA_DMCTL_PR;  /* PR=1: Round-robin */
    }
  else
    {
      dmctl &= ~R_DMA_DMCTL_PR; /* PR=0: Fixed priority */
    }

  putreg32(dmctl, R_DMA_DMCTL_UNIT(unit));

  dmainfo("DMAC Unit %d priority mode set to %s\n",
          unit, mode == RA_DMAC_PRIORITY_ROUND_ROBIN ? "round-robin" : "fixed");

  return OK;
}

/****************************************************************************
 * Name: ra_dmac_open
 *
 * Description:
 *   Open and configure a DMAC transfer
 *
 ****************************************************************************/

int ra_dmac_open(ra_dmac_handle_t *handle, const ra_dmac_config_t *config)
{
  ra_dmac_ctrl_t *ctrl;
  irqstate_t flags;
  int channel;
  int ret;

  if (handle == NULL || config == NULL)
    {
      return -EINVAL;
    }

  /* Validate configuration */
  ret = ra_dmac_validate_config(config);
  if (ret < 0)
    {
      return ret;
    }

  /* Find and reserve a free channel (thread-safe) */
  channel = ra_dmac_find_free_channel();
  if (channel < 0)
    {
      return channel;
    }

  ctrl = &g_dmac_channels[channel];

  /* Allocate and copy configuration */
  ctrl->config = kmm_zalloc(sizeof(ra_dmac_config_t));
  if (ctrl->config == NULL)
    {
      /* Release the reserved channel on allocation failure */

      flags = spin_lock_irqsave(&g_dmac_lock);
      ctrl->in_use = false;
      spin_unlock_irqrestore(&g_dmac_lock, flags);
      return -ENOMEM;
    }

  memcpy(ctrl->config, config, sizeof(ra_dmac_config_t));

  ctrl->open_id = DMAC_OPEN_ID;
  /* in_use already set by ra_dmac_find_free_channel() */

  /* Increment reference count for MSTP tracking */

  flags = spin_lock_irqsave(&g_dmac_lock);
  g_dmac_refcount++;
  spin_unlock_irqrestore(&g_dmac_lock, flags);

  *handle = ctrl;

  dmainfo("DMAC channel %d opened successfully\n", channel);
  return OK;
}

/****************************************************************************
 * Name: ra_dmac_open_channel
 *
 * Description:
 *   Open and configure a DMAC transfer with explicit channel assignment
 *
 ****************************************************************************/

int ra_dmac_open_channel(ra_dmac_handle_t *handle, const ra_dmac_config_t *config, int channel)
{
  ra_dmac_ctrl_t *ctrl;
  irqstate_t flags;
  int ret;

  if (handle == NULL || config == NULL)
    {
      return -EINVAL;
    }

  /* Validate channel number using helper macro */

  if (!DMAC_IS_VALID_CHANNEL(channel))
    {
      dmaerr("Invalid channel number: %d (valid: 0-7, 10-17)\n", channel);
      return -EINVAL;
    }

  /* Thread-safe check and reserve channel */

  flags = spin_lock_irqsave(&g_dmac_lock);

  if (g_dmac_channels[channel].in_use)
    {
      spin_unlock_irqrestore(&g_dmac_lock, flags);
      dmaerr("Channel %d already in use\n", channel);
      return -EBUSY;
    }

  /* Reserve the channel immediately */

  g_dmac_channels[channel].in_use = true;
  spin_unlock_irqrestore(&g_dmac_lock, flags);

  /* Validate configuration */
  ret = ra_dmac_validate_config(config);
  if (ret < 0)
    {
      flags = spin_lock_irqsave(&g_dmac_lock);
      g_dmac_channels[channel].in_use = false;
      spin_unlock_irqrestore(&g_dmac_lock, flags);
      return ret;
    }

  ctrl = &g_dmac_channels[channel];

  /* Allocate and copy configuration */
  ctrl->config = kmm_zalloc(sizeof(ra_dmac_config_t));
  if (ctrl->config == NULL)
    {
      flags = spin_lock_irqsave(&g_dmac_lock);
      ctrl->in_use = false;
      spin_unlock_irqrestore(&g_dmac_lock, flags);
      return -ENOMEM;
    }

  memcpy(ctrl->config, config, sizeof(ra_dmac_config_t));

  ctrl->open_id = DMAC_OPEN_ID;
  /* in_use already set above */

  /* Increment reference count for MSTP tracking */

  flags = spin_lock_irqsave(&g_dmac_lock);
  g_dmac_refcount++;
  spin_unlock_irqrestore(&g_dmac_lock, flags);

  *handle = ctrl;

  dmainfo("DMAC channel %d opened successfully (explicit assignment)\n", channel);
  return OK;
}

/****************************************************************************
 * Name: ra_dmac_enable
 *
 * Description:
 *   Enable DMAC transfer
 *
****************************************************************************/

int ra_dmac_enable(ra_dmac_handle_t handle)
{
  ra_dmac_ctrl_t *ctrl = (ra_dmac_ctrl_t *)handle;
  uint8_t status;
  int ret;

  if (ctrl == NULL || ctrl->open_id != DMAC_OPEN_ID)
    {
      return -EINVAL;
    }

  if (ctrl->config == NULL)
    {
      return -EINVAL;
    }

  /* Check if channel is already active */

  status = getreg8(R_DMAC_DMSTS(ctrl->channel));
  if (status & R_DMAC_DMSTS_ACT)
    {
      return -EBUSY;
    }

  /* Setup channel registers */

  ret = ra_dmac_setup_channel(ctrl);
  if (ret < 0)
    {
      return ret;
    }

  /* Attach and enable interrupt if callback is provided */

  if (ctrl->config->callback != NULL)
    {
      ret = ra_icu_attach(ctrl->config->elc_end,
                          ra_dmac_interrupt_handler, ctrl, true);
      if (ret < 0)
        {
          return ret;
        }
      ctrl->irq_end = ret;  /* Store the assigned IRQ slot number */
    }

  /* Attach and enable error interrupt if error event link is provided */

  if (ctrl->config->elc_err >= 0)
    {
      ret = ra_icu_attach(ctrl->config->elc_err,
                          ra_dmac_interrupt_handler, ctrl, true);
      if (ret < 0)
        {
          if (ctrl->irq_end >= 0)
            {
              ra_icu_detach(ctrl->irq_end); /* Detach end interrupt */
            }
          return ret;
        }
      ctrl->irq_err = ret;  /* Store the assigned IRQ slot number */
    }

  /* Configure DELSR activation source for hardware-triggered DMA */

  if (ctrl->config->trigger != RA_DMAC_TRIGGER_SW && ctrl->config->elc_src >= 0)
    {
      /* Set up the DELSR register with the ELC event source for this channel
       * DELSR[channel].DELS = ELC event number
       */

      ra_icu_enable_dmac(ctrl->config->elc_src, ctrl->channel);
    }

  /* Enable the channel via DMCNT.DTE = 1 (per-channel enable) */

  putreg8(R_DMAC_DMCNT_DTE, R_DMAC_DMCNT(ctrl->channel));

  ctrl->enabled = true;

  dmainfo("DMAC channel %d enabled\n", ctrl->channel);
  return OK;
}

/****************************************************************************
 * Name: ra_dmac_disable
 *
 * Description:
 *   Disable DMAC transfer
 *
 ****************************************************************************/

int ra_dmac_disable(ra_dmac_handle_t handle)
{
  ra_dmac_ctrl_t *ctrl = (ra_dmac_ctrl_t *)handle;
  uint8_t status;
  int timeout;

  if (ctrl == NULL || ctrl->open_id != DMAC_OPEN_ID)
    {
      return -EINVAL;
    }

  /* Disable the channel via DMCNT.DTE = 0 (per-channel disable) */

  putreg8(0, R_DMAC_DMCNT(ctrl->channel));

  /* Wait for transfer to complete (ACT bit to clear) with timeout */

  timeout = 1000;
  do
    {
      status = getreg8(R_DMAC_DMSTS(ctrl->channel));
      if (!(status & R_DMAC_DMSTS_ACT))
        {
          break;
        }
    }
  while (--timeout > 0);

  if (timeout == 0)
    {
      dmaerr("DMAC channel %d disable timeout\n", ctrl->channel);
    }

  /* Clear any pending interrupt flags */

  putreg8(0, R_DMAC_DMSTS(ctrl->channel));

  /* Clear DELSR activation source if hardware trigger was used */

  if (ctrl->config != NULL &&
      ctrl->config->trigger != RA_DMAC_TRIGGER_SW &&
      ctrl->config->elc_src >= 0)
    {
      ra_icu_disable_dmac(ctrl->config->elc_src, ctrl->channel);
    }

  /* Disable and detach interrupts if assigned */

  if (ctrl->irq_end >= 0)
    {
      ra_icu_detach(ctrl->irq_end);  /* Disable the assigned IRQ slot */
      ctrl->irq_end = -1;
    }

  if (ctrl->irq_err >= 0)
    {
      ra_icu_detach(ctrl->irq_err);  /* Disable the assigned IRQ slot */
      ctrl->irq_err = -1;
    }

  ctrl->enabled = false;

  dmainfo("DMAC channel %d disabled\n", ctrl->channel);
  return OK;
}

/****************************************************************************
 * Name: ra_dmac_software_start
 *
 * Description:
 *   Start DMAC transfer by software trigger
 *
 ****************************************************************************/

int ra_dmac_software_start(ra_dmac_handle_t handle)
{
  ra_dmac_ctrl_t *ctrl = (ra_dmac_ctrl_t *)handle;

  if (ctrl == NULL || ctrl->open_id != DMAC_OPEN_ID)
    {
      return -EINVAL;
    }

  if (!ctrl->enabled)
    {
      return -EPERM;
    }

  /* Software start request (DMREQ is 8-bit register) */

  putreg8(R_DMAC_DMREQ_SWREQ, R_DMAC_DMREQ(ctrl->channel));

  dmainfo("DMAC channel %d software start\n", ctrl->channel);
  return OK;
}

/****************************************************************************
 * Name: ra_dmac_reset
 *
 * Description:
 *   Reset DMAC transfer addresses and count
 *
 ****************************************************************************/

int ra_dmac_reset(ra_dmac_handle_t handle, uint32_t src_addr,
                  uint32_t dest_addr, uint32_t transfer_count)
{
  ra_dmac_ctrl_t *ctrl = (ra_dmac_ctrl_t *)handle;
  uint8_t status;

  if (ctrl == NULL || ctrl->open_id != DMAC_OPEN_ID)
    {
      return -EINVAL;
    }

  if (ctrl->config == NULL)
    {
      return -EINVAL;
    }

  /* Check if transfer is active - cannot modify registers while active */

  status = getreg8(R_DMAC_DMSTS(ctrl->channel));
  if (status & R_DMAC_DMSTS_ACT)
    {
      return -EBUSY;
    }

  /* Check address alignment */

  if (DMAC_ALIGNMENT_CHECK(src_addr, ctrl->config->size) ||
      DMAC_ALIGNMENT_CHECK(dest_addr, ctrl->config->size))
    {
      return -EINVAL;
    }

  /* Update registers */

  putreg32(src_addr, R_DMAC_DMSAR(ctrl->channel));
  putreg32(dest_addr, R_DMAC_DMDAR(ctrl->channel));
  putreg32(transfer_count, R_DMAC_DMCRA(ctrl->channel));

  dmainfo("DMAC channel %d reset: src=0x%08lx, dest=0x%08lx, count=%ld\n",
         ctrl->channel, src_addr, dest_addr, transfer_count);
  return OK;
}

/****************************************************************************
 * Name: ra_dmac_close
 *
 * Description:
 *   Close DMAC transfer and free resources
 *
 ****************************************************************************/

int ra_dmac_close(ra_dmac_handle_t handle)
{
  ra_dmac_ctrl_t *ctrl = (ra_dmac_ctrl_t *)handle;
  irqstate_t flags;
  uint8_t channel;
  bool stop_mstp = false;

  if (ctrl == NULL || ctrl->open_id != DMAC_OPEN_ID)
    {
      return -EINVAL;
    }

  channel = ctrl->channel;

  /* Disable transfer first */
  ra_dmac_disable(handle);

  /* Free allocated memory */
  if (ctrl->config != NULL)
    {
      kmm_free(ctrl->config);
      ctrl->config = NULL;
    }

  /* Thread-safe release of channel and refcount decrement */

  flags = spin_lock_irqsave(&g_dmac_lock);

  ctrl->open_id = 0;
  ctrl->enabled = false;
  ctrl->in_use = false;
  ctrl->irq_end = -1;
  ctrl->irq_err = -1;

  /* Decrement reference count and check if MSTP can be stopped */

  if (g_dmac_refcount > 0)
    {
      g_dmac_refcount--;
      if (g_dmac_refcount == 0)
        {
          stop_mstp = true;
        }
    }

  spin_unlock_irqrestore(&g_dmac_lock, flags);

  /* Stop DMAC module clock if no channels are active.
   * This saves power when DMAC is not in use.
   * Note: ra_mstp_stop() must be called outside the spinlock
   * as it may involve register waits.
   */

  if (stop_mstp)
    {
      dmainfo("All DMAC channels closed, stopping module clock\n");
      ra_mstp_stop(RA_MSTP_DMAC);
      g_dmac_initialized = false;  /* Will reinitialize on next open */
    }

  dmainfo("DMAC channel %d closed (refcount=%d)\n", channel, g_dmac_refcount);
  return OK;
}

/****************************************************************************
 * Name: ra_dmac_get_remaining_count
 *
 * Description:
 *   Get remaining transfer count
 *
 ****************************************************************************/

uint32_t ra_dmac_get_remaining_count(ra_dmac_handle_t handle)
{
  ra_dmac_ctrl_t *ctrl = (ra_dmac_ctrl_t *)handle;

  if (ctrl == NULL || ctrl->open_id != DMAC_OPEN_ID)
    {
      return 0;
    }

  return getreg32(R_DMAC_DMCRA(ctrl->channel));
}

/****************************************************************************
 * Debug Interface
 ****************************************************************************/

#ifdef CONFIG_DEBUG_DMA_INFO

/****************************************************************************
 * Name: ra_dmasample
 *
 * Description:
 *   Sample DMA register contents for debugging
 *
 ****************************************************************************/

void ra_dmasample(ra_dmac_handle_t handle, struct ra_dmaregs_s *regs)
{
  ra_dmac_ctrl_t *ctrl = (ra_dmac_ctrl_t *)handle;
  irqstate_t flags;
  uint8_t chan;

  DEBUGASSERT(ctrl != NULL && regs != NULL);

  if (ctrl->open_id != DMAC_OPEN_ID)
    {
      memset(regs, 0, sizeof(struct ra_dmaregs_s));
      return;
    }

  chan = ctrl->channel;
  regs->chan = chan;

  /* Disable interrupts during register sampling for consistency */

  flags = enter_critical_section();

  /* Sample global DMA registers */

  regs->dmast  = getreg32(R_DMA_DMAST);
  regs->dmctl  = getreg32(R_DMA_DMCTL);
  regs->dmechr = getreg32(R_DMA_DMECHR);
  regs->delsr  = getreg32(R_DMA_DELSR(chan));

  /* Sample per-channel registers */

  regs->dmsar  = getreg32(R_DMAC_DMSAR(chan));
  regs->dmdar  = getreg32(R_DMAC_DMDAR(chan));
  regs->dmcra  = getreg32(R_DMAC_DMCRA(chan));
  regs->dmcrb  = getreg32(R_DMAC_DMCRB(chan));
  regs->dmtmd  = getreg32(R_DMAC_DMTMD(chan));
  regs->dmamd  = getreg32(R_DMAC_DMAMD(chan));
  regs->dmint  = getreg8(R_DMAC_DMINT(chan));
  regs->dmcnt  = getreg8(R_DMAC_DMCNT(chan));
  regs->dmreq  = getreg8(R_DMAC_DMREQ(chan));
  regs->dmsts  = getreg8(R_DMAC_DMSTS(chan));

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: ra_dmadump
 *
 * Description:
 *   Dump previously sampled DMA register contents
 *
 ****************************************************************************/

void ra_dmadump(const struct ra_dmaregs_s *regs, const char *msg)
{
  DEBUGASSERT(regs != NULL && msg != NULL);

  dmainfo("%s\n", msg);
  dmainfo("  RA DMAC Channel %u Registers:\n", regs->chan);

  /* Global registers */

  dmainfo("  Global Registers:\n");
  dmainfo("       DMAST: %08" PRIx32 "\n", regs->dmast);
  dmainfo("       DMCTL: %08" PRIx32 "\n", regs->dmctl);
  dmainfo("      DMECHR: %08" PRIx32 "\n", regs->dmechr);
  dmainfo("       DELSR: %08" PRIx32 "\n", regs->delsr);

  /* Per-channel registers */

  dmainfo("  Channel %u Registers:\n", regs->chan);
  dmainfo("       DMSAR: %08" PRIx32 " (Source Address)\n", regs->dmsar);
  dmainfo("       DMDAR: %08" PRIx32 " (Dest Address)\n", regs->dmdar);
  dmainfo("       DMCRA: %08" PRIx32 " (Transfer Count)\n", regs->dmcra);
  dmainfo("       DMCRB: %08" PRIx32 " (Block Count)\n", regs->dmcrb);
  dmainfo("       DMTMD: %08" PRIx32 " (Transfer Mode)\n", regs->dmtmd);
  dmainfo("       DMAMD: %08" PRIx32 " (Address Mode)\n", regs->dmamd);
  dmainfo("       DMINT: %02x (Interrupt Setting)\n", regs->dmint);
  dmainfo("       DMCNT: %02x (Transfer Enable)\n", regs->dmcnt);
  dmainfo("       DMREQ: %02x (Software Start)\n", regs->dmreq);
  dmainfo("       DMSTS: %02x (Status)\n", regs->dmsts);

  /* Decode status bits */

  dmainfo("  Status Decode:\n");
  dmainfo("         ACT: %s\n", (regs->dmsts & R_DMAC_DMSTS_ACT) ?
                                "Active" : "Inactive");
  dmainfo("        DTIF: %s\n", (regs->dmsts & R_DMAC_DMSTS_DTIF) ?
                                "Transfer End" : "No");
  dmainfo("        ESIF: %s\n", (regs->dmsts & R_DMAC_DMSTS_ESIF) ?
                                "Escape End" : "No");

  /* Decode transfer mode */

  dmainfo("  Mode Decode:\n");
  dmainfo("        DCTG: %s\n",
          ((regs->dmtmd & R_DMAC_DMTMD_DCTG_MASK) == 0) ?
          "Software" : "Hardware");
  dmainfo("          SZ: %u-bit\n",
          8 << ((regs->dmtmd >> R_DMAC_DMTMD_SZ_SHIFT) & 0x3));
  dmainfo("          MD: %s\n",
          ((regs->dmtmd >> R_DMAC_DMTMD_MD_SHIFT) & 0x3) == 0 ? "Normal" :
          ((regs->dmtmd >> R_DMAC_DMTMD_MD_SHIFT) & 0x3) == 1 ? "Repeat" :
          ((regs->dmtmd >> R_DMAC_DMTMD_MD_SHIFT) & 0x3) == 2 ? "Block" :
          "Invalid");
  dmainfo("         DTE: %s\n", (regs->dmcnt & R_DMAC_DMCNT_DTE) ?
                                "Enabled" : "Disabled");
}

#endif /* CONFIG_DEBUG_DMA_INFO */
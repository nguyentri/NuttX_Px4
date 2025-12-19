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
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/kmalloc.h>

#include "arm_internal.h"
#include "chip.h"
#include "hardware/rzv_dmac.h"
#include "rzv_dmac.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define DMAC_OPEN_ID             (0x444d4143)  /* "DMAC" in ASCII */
#define DMAC_ALIGNMENT_CHECK(addr, size) \
  (((uint32_t)(addr)) & ((1 << (size)) - 1))

/* DMAC_B Control Register values */
#define DMAC_B_CHCTRL_SETEN      (1 << 0)
#define DMAC_B_CHCTRL_CLREN      (1 << 1)
#define DMAC_B_CHCTRL_STG        (1 << 2)
#define DMAC_B_CHCTRL_SWRST      (1 << 3)
#define DMAC_B_CHCTRL_CLREND     (1 << 5)
#define DMAC_B_CHCTRL_CLRTC      (1 << 6)
#define DMAC_B_CHCTRL_SETSUS     (1 << 8)
#define DMAC_B_CHCTRL_CLRSUS     (1 << 9)

/* DMAC_B Status Register bits */
#define DMAC_B_CHSTAT_EN         (1 << 0)
#define DMAC_B_CHSTAT_RQST       (1 << 1)
#define DMAC_B_CHSTAT_TACT       (1 << 2)
#define DMAC_B_CHSTAT_SUS        (1 << 3)
#define DMAC_B_CHSTAT_ER         (1 << 4)
#define DMAC_B_CHSTAT_END        (1 << 5)
#define DMAC_B_CHSTAT_TC         (1 << 6)
#define DMAC_B_CHSTAT_SR         (1 << 7)

/* DMAC Events */
#define RZV_DMAC_EVENT_COMPLETE  (0)  /* Transfer complete */
#define RZV_DMAC_EVENT_ERROR     (1)  /* Transfer error */

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* DMAC_B context control structure */

typedef struct rzv_dmac_ctrl_s
{
  uint32_t                     open_id;    /* Open ID for validation */
  uint8_t                      unit;       /* DMAC unit number (0-4) */
  uint8_t                      channel;    /* Channel within unit (0-15) */
  uint8_t                      global_ch;  /* Global channel (0-79) */
  bool                         in_use;     /* Channel in use flag */
  bool                         enabled;    /* Channel enabled flag */
  struct rzv_dmac_config_s    *config;     /* Transfer configuration */
  int                          irq_slot;   /* IRQ slot number */
} rzv_dmac_ctrl_t;

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* DMAC channel control blocks - 80 total channels */

static rzv_dmac_ctrl_t g_dmac_channels[RZV_DMAC_MAX_CHANNELS];

/* DMAC module initialized flags per unit */

static bool g_dmac_unit_initialized[RZV_DMAC_NUM_UNITS] =
{
  false, false, false, false, false
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_dmac_validate_config
 *
 * Description:
 *   Validate DMAC configuration
 *
 ****************************************************************************/

static int rzv_dmac_validate_config(const struct rzv_dmac_config_s *config)
{
  if (config == NULL)
    {
      return -EINVAL;
    }

  /* Check transfer length */

  if (config->length == 0 || config->length > 0xFFFFFFFF)
    {
      return -EINVAL;
    }

  /* Validate transfer sizes */

  if (config->src_size > RZV_DMAC_SIZE_128BYTE ||
      config->dst_size > RZV_DMAC_SIZE_128BYTE)
    {
      return -EINVAL;
    }

  /* Check address alignment based on transfer size */

  uint32_t src_align = 1 << config->src_size;
  uint32_t dst_align = 1 << config->dst_size;

  if ((config->src_addr & (src_align - 1)) != 0 ||
      (config->dst_addr & (dst_align - 1)) != 0)
    {
      dmaerr("Address alignment error: src=0x%08lx (align=%lu), "
             "dst=0x%08lx (align=%lu)\n",
             config->src_addr, src_align, config->dst_addr, dst_align);
      return -EINVAL;
    }

  /* Validate priority */

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
 *   Setup DMAC_B channel registers
 *
 ****************************************************************************/

static int rzv_dmac_setup_channel(rzv_dmac_ctrl_t *ctrl)
{
  struct rzv_dmac_config_s *config = ctrl->config;
  uint8_t unit = ctrl->unit;
  uint8_t channel = ctrl->channel;
  uint32_t chcfg = 0;
  uint32_t chext = 0;
  uint32_t chitvl = 0;

  /* Setup Channel Configuration Register (CHCFG)
   * SEL[2:0]   - Peripheral request source
   * REQD[3]    - Request direction
   * LOEN[4]    - Low level output enable
   * HIEN[5]    - High level output enable
   * LVL[6]     - Level output
   * AM[10:8]   - Acknowledge mode
   * SDS[15:12] - Source data size
   * DDS[19:16] - Destination data size
   * SAD[20]    - Source address direction
   * DAD[21]    - Destination address direction
   * TM[22]     - Transfer mode
   * DEM[24]    - DMA end interrupt mask
   * TCM[25]    - Transfer count match interrupt mask
   * SBE[27]    - Secure bit enable
   * RSEL[28]   - Register set select
   * RSW[29]    - Register set swap
   * REN[30]    - Register mode enable
   * DMS[31]    - DMA mode select
   */

  /* Set transfer sizes */

  chcfg |= ((config->src_size & 0xF) << 12);  /* SDS */
  chcfg |= ((config->dst_size & 0xF) << 16);  /* DDS */

  /* Set address modes */

  if (config->src_addr_mode == RZV_DMAC_ADDR_FIXED)
    {
      chcfg |= (1 << 20);  /* SAD = 1 (fixed) */
    }

  if (config->dst_addr_mode == RZV_DMAC_ADDR_FIXED)
    {
      chcfg |= (1 << 21);  /* DAD = 1 (fixed) */
    }

  /* Set transfer mode */

  if (config->mode == RZV_DMAC_MODE_REGISTER)
    {
      chcfg |= (1 << 30);  /* REN = 1 (register mode) */
    }

  /* Enable interrupts if callback provided */

  if (config->callback != NULL)
    {
      chcfg &= ~(1 << 24);  /* DEM = 0 (enable end interrupt) */
    }
  else
    {
      chcfg |= (1 << 24);   /* DEM = 1 (mask end interrupt) */
    }

  /* Setup Channel Extension Register (CHEXT)
   * SPR[2:0]  - Source port
   * SCA[7:4]  - Source cache attribute
   * DPR[10:8] - Destination port
   * DCA[15:12]- Destination cache attribute
   */

  chext |= ((config->priority & 0x7) << 0);   /* Source priority */
  chext |= ((config->priority & 0x7) << 8);   /* Dest priority */

  /* Setup Channel Interval Register (CHITVL) */

  chitvl = config->transfer_interval & 0xFFFF;

  /* Write configuration registers */

  putreg32(chcfg, RZV_DMAC_CHCFG(unit, channel));
  putreg32(chext, RZV_DMAC_CHEXT(unit, channel));
  putreg32(chitvl, RZV_DMAC_CHITVL(unit, channel));

  /* Setup Next0 registers (source, destination, count) */

  putreg32(config->src_addr, RZV_DMAC_NXSA(unit, channel));
  putreg32(config->dst_addr, RZV_DMAC_NXDA(unit, channel));
  putreg32(config->length, RZV_DMAC_NXTB(unit, channel));

  /* Setup DMARS if hardware trigger */

  if (config->trigger == RZV_DMAC_TRIGGER_HW && config->elc_event >= 0)
    {
      uint32_t dmars = config->elc_event & 0xFFF;
      putreg32(dmars, RZV_DMAC_DMARS(unit, channel));
    }

  dmainfo("DMAC%d CH%d configured: src=0x%08lx dst=0x%08lx len=%lu\n",
          unit, channel, config->src_addr, config->dst_addr,
          config->length);

  return OK;
}

/****************************************************************************
 * Name: rzv_dmac_interrupt_handler
 *
 * Description:
 *   DMAC_B interrupt handler
 *
 ****************************************************************************/

static int rzv_dmac_interrupt_handler(int irq, void *context,
                                       void *arg)
{
  rzv_dmac_ctrl_t *ctrl = (rzv_dmac_ctrl_t *)arg;
  uint32_t status;

  if (ctrl == NULL || ctrl->open_id != DMAC_OPEN_ID)
    {
      return OK;
    }

  /* Read channel status */

  status = getreg32(RZV_DMAC_CHSTAT(ctrl->unit, ctrl->channel));

  /* Check for transfer end */

  if (status & DMAC_B_CHSTAT_END)
    {
      /* Clear END flag */

      putreg32(DMAC_B_CHCTRL_CLREND,
               RZV_DMAC_CHCTRL(ctrl->unit, ctrl->channel));

      /* Call user callback */

      if (ctrl->config && ctrl->config->callback)
        {
          ctrl->config->callback(ctrl, RZV_DMAC_EVENT_COMPLETE,
                                 ctrl->config->user_data);
        }

      dmainfo("DMAC%d CH%d: Transfer complete\n", ctrl->unit,
              ctrl->channel);
    }

  /* Check for error */

  if (status & DMAC_B_CHSTAT_ER)
    {
      dmaerr("DMAC%d CH%d: Transfer error, status=0x%08lx\n",
             ctrl->unit, ctrl->channel, status);

      /* Software reset to clear error */

      putreg32(DMAC_B_CHCTRL_SWRST,
               RZV_DMAC_CHCTRL(ctrl->unit, ctrl->channel));

      /* Call user callback with error event */

      if (ctrl->config && ctrl->config->callback)
        {
          ctrl->config->callback(ctrl, RZV_DMAC_EVENT_ERROR,
                                 ctrl->config->user_data);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_dmac_find_free_channel
 *
 * Description:
 *   Find a free DMAC channel
 *
 ****************************************************************************/

static int rzv_dmac_find_free_channel(void)
{
  int i;

  for (i = 0; i < RZV_DMAC_MAX_CHANNELS; i++)
    {
      if (!g_dmac_channels[i].in_use)
        {
          return i;
        }
    }

  return -ENOMEM;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_dmac_channel_initialize
 *
 * Description:
 *   Initialize a DMAC unit (called automatically, can be called explicitly)
 *
 ****************************************************************************/

int rzv_dmac_channel_initialize(int channel)
{
  int unit;
  int ch;
  int i;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS)
    {
      return -EINVAL;
    }

  unit = RZV_DMAC_UNIT(channel);
  ch = RZV_DMAC_CH(channel);

  if (g_dmac_unit_initialized[unit])
    {
      return OK;  /* Already initialized */
    }

  /* TODO: Enable DMAC unit clock via CPG
   * rzv_cpg_module_start(RZV_CPG_MODULE_DMAC0 + unit);
   */

  /* Initialize channel control blocks for this unit */

  for (i = 0; i < RZV_DMAC_CHANNELS_PER_UNIT; i++)
    {
      int global_ch = unit * RZV_DMAC_CHANNELS_PER_UNIT + i;
      memset(&g_dmac_channels[global_ch], 0, sizeof(rzv_dmac_ctrl_t));
      g_dmac_channels[global_ch].unit = unit;
      g_dmac_channels[global_ch].channel = i;
      g_dmac_channels[global_ch].global_ch = global_ch;
      g_dmac_channels[global_ch].irq_slot = -1;
    }

  /* Initialize DCTRL register for priority/scheduling */

  putreg32(0, RZV_DMAC_DCTRL(unit));

  g_dmac_unit_initialized[unit] = true;

  dmainfo("DMAC unit %d initialized successfully\n", unit);
  return OK;
}

/****************************************************************************
 * Name: rzv_dmac_channel_configure
 *
 * Description:
 *   Configure a DMAC channel for transfer
 *
 ****************************************************************************/

int rzv_dmac_channel_configure(int channel,
                                const struct rzv_dmac_config_s *config)
{
  rzv_dmac_ctrl_t *ctrl;
  int ret;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS || config == NULL)
    {
      return -EINVAL;
    }

  /* Initialize unit if not already done */

  ret = rzv_dmac_channel_initialize(channel);
  if (ret < 0)
    {
      return ret;
    }

  /* Validate configuration */

  ret = rzv_dmac_validate_config(config);
  if (ret < 0)
    {
      return ret;
    }

  ctrl = &g_dmac_channels[channel];

  /* Check if channel is already in use */

  if (ctrl->in_use)
    {
      dmaerr("Channel %d already in use\n", channel);
      return -EBUSY;
    }

  /* Allocate and copy configuration */

  ctrl->config = kmm_zalloc(sizeof(struct rzv_dmac_config_s));
  if (ctrl->config == NULL)
    {
      return -ENOMEM;
    }

  memcpy(ctrl->config, config, sizeof(struct rzv_dmac_config_s));

  ctrl->open_id = DMAC_OPEN_ID;
  ctrl->in_use = true;

  /* Setup channel registers */

  ret = rzv_dmac_setup_channel(ctrl);
  if (ret < 0)
    {
      kmm_free(ctrl->config);
      ctrl->config = NULL;
      ctrl->in_use = false;
      return ret;
    }

  dmainfo("DMAC channel %d configured successfully\n", channel);
  return OK;
}

/****************************************************************************
 * Name: rzv_dmac_channel_start
 *
 * Description:
 *   Start a DMAC transfer
 *
 ****************************************************************************/

int rzv_dmac_channel_start(int channel)
{
  rzv_dmac_ctrl_t *ctrl;
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

  if (ctrl->config == NULL)
    {
      return -EINVAL;
    }

  /* Check if already active */

  status = getreg32(RZV_DMAC_CHSTAT(ctrl->unit, ctrl->channel));
  if (status & DMAC_B_CHSTAT_TACT)
    {
      return -EBUSY;
    }

  /* Attach interrupt if callback is provided and not already attached */

  if (ctrl->config->callback != NULL && ctrl->irq_slot < 0)
    {
      /* TODO: Attach interrupt via ICU/GIC
       * For now, we'll skip interrupt attachment
       * ctrl->irq_slot = rzv_icu_attach(ctrl->config->irq_num,
       *                                  rzv_dmac_interrupt_handler,
       *                                  ctrl, true);
       */
    }

  /* Enable the channel */

  putreg32(DMAC_B_CHCTRL_SETEN,
           RZV_DMAC_CHCTRL(ctrl->unit, ctrl->channel));

  /* For software trigger, start immediately */

  if (ctrl->config->trigger == RZV_DMAC_TRIGGER_SW)
    {
      putreg32(DMAC_B_CHCTRL_STG,
               RZV_DMAC_CHCTRL(ctrl->unit, ctrl->channel));
    }

  ctrl->enabled = true;

  dmainfo("DMAC channel %d started\n", channel);
  return OK;
}

/****************************************************************************
 * Name: rzv_dmac_channel_stop
 *
 * Description:
 *   Stop a DMAC transfer
 *
 ****************************************************************************/

int rzv_dmac_channel_stop(int channel)
{
  rzv_dmac_ctrl_t *ctrl;
  uint32_t status;
  int timeout;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS)
    {
      return -EINVAL;
    }

  ctrl = &g_dmac_channels[channel];

  if (ctrl->open_id != DMAC_OPEN_ID)
    {
      return -EINVAL;
    }

  /* Disable the channel */

  putreg32(DMAC_B_CHCTRL_CLREN,
           RZV_DMAC_CHCTRL(ctrl->unit, ctrl->channel));

  /* Wait for transfer to stop with timeout */

  timeout = 1000;
  do
    {
      status = getreg32(RZV_DMAC_CHSTAT(ctrl->unit, ctrl->channel));
      if (!(status & DMAC_B_CHSTAT_TACT))
        {
          break;
        }
      up_udelay(10);
    }
  while (--timeout > 0);

  if (timeout == 0)
    {
      dmaerr("DMAC channel %d stop timeout\n", channel);
      /* Force reset */
      putreg32(DMAC_B_CHCTRL_SWRST,
               RZV_DMAC_CHCTRL(ctrl->unit, ctrl->channel));
    }

  /* Clear any pending flags */

  putreg32(DMAC_B_CHCTRL_CLREND | DMAC_B_CHCTRL_CLRTC,
           RZV_DMAC_CHCTRL(ctrl->unit, ctrl->channel));

  /* Detach interrupt if attached */

  if (ctrl->irq_slot >= 0)
    {
      /* TODO: Detach interrupt via ICU/GIC
       * rzv_icu_detach(ctrl->irq_slot);
       */
      ctrl->irq_slot = -1;
    }

  /* Free configuration and mark channel as free */

  if (ctrl->config != NULL)
    {
      kmm_free(ctrl->config);
      ctrl->config = NULL;
    }

  ctrl->enabled = false;
  ctrl->in_use = false;
  ctrl->open_id = 0;

  dmainfo("DMAC channel %d stopped\n", channel);
  return OK;
}

/****************************************************************************
 * Name: rzv_dmac_channel_status
 *
 * Description:
 *   Get DMA channel status
 *
 ****************************************************************************/

uint32_t rzv_dmac_channel_status(int channel)
{
  rzv_dmac_ctrl_t *ctrl;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS)
    {
      return 0;
    }

  ctrl = &g_dmac_channels[channel];

  if (ctrl->open_id != DMAC_OPEN_ID)
    {
      return 0;
    }

  return getreg32(RZV_DMAC_CHSTAT(ctrl->unit, ctrl->channel));
}

/****************************************************************************
 * Name: rzv_dmac_get_remaining_bytes
 *
 * Description:
 *   Get remaining transfer byte count
 *
 ****************************************************************************/

uint32_t rzv_dmac_get_remaining_bytes(int channel)
{
  rzv_dmac_ctrl_t *ctrl;

  if (channel < 0 || channel >= RZV_DMAC_MAX_CHANNELS)
    {
      return 0;
    }

  ctrl = &g_dmac_channels[channel];

  if (ctrl->open_id != DMAC_OPEN_ID)
    {
      return 0;
    }

  return getreg32(RZV_DMAC_CRTB(ctrl->unit, ctrl->channel));
}

/****************************************************************************
 * arch/arm/src/ra8/ra_sdhi.c
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

#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <debug.h>
#include <errno.h>

#include <nuttx/wdog.h>
#include <nuttx/clock.h>
#include <nuttx/arch.h>
#include <nuttx/sdio.h>
#include <nuttx/wqueue.h>
#include <nuttx/semaphore.h>
#include <nuttx/mmcsd.h>
#include <nuttx/irq.h>
#include <nuttx/syslog/syslog.h>

#include <arch/board/board.h>

#include "chip.h"
#include "arm_internal.h"
#include "ra_sdhi.h"
#include "ra_icu.h"
#include "ra_mstp.h"
#include "ra_gpio.h"
#include "ra_clock.h"
#include "ra_dmac.h"

#ifdef CONFIG_PM
#include <nuttx/power/pm.h>
#endif

#ifdef CONFIG_RA_SDHI

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define RA_SDHI_CMDTIMEOUT      MSEC2TICK(100)
#define RA_SDHI_LONGTIMEOUT     MSEC2TICK(500)

/* Register access macros */

#define ra_getreg32(a)          getreg32(a)
#define ra_putreg32(v,a)        putreg32(v,a)

/* Interrupt masks */

#define RA_SDHI_INFO1_RESP_INTS (R_SDHI_SD_INFO1_RSPEND)
#define RA_SDHI_INFO1_ACCESS_INTS (R_SDHI_SD_INFO1_ACEND)
#define RA_SDHI_INFO1_CARD_INTS (R_SDHI_SD_INFO1_SDCDIN | R_SDHI_SD_INFO1_SDCDRM)

#define RA_SDHI_INFO2_ERR_INTS  (R_SDHI_SD_INFO2_CMDE | R_SDHI_SD_INFO2_CRCE | \
                                 R_SDHI_SD_INFO2_ENDE | R_SDHI_SD_INFO2_DTO | \
                                 R_SDHI_SD_INFO2_ILW | R_SDHI_SD_INFO2_ILR | \
                                 R_SDHI_SD_INFO2_RSPTO | R_SDHI_SD_INFO2_ILA)

#define RA_SDHI_INFO2_XFR_INTS  (R_SDHI_SD_INFO2_BRE | R_SDHI_SD_INFO2_BWE)

#define RA_SDHI_WAITALL_INTS    (RA_SDHI_INFO1_RESP_INTS | RA_SDHI_INFO1_ACCESS_INTS | \
                                 RA_SDHI_INFO2_ERR_INTS | RA_SDHI_INFO2_XFR_INTS)

/* DMA transfer block size */
#define RA_SDHI_DMA_BLOCK_SIZE  512

/* Maximum DMA transfer blocks */
#define RA_SDHI_DMA_MAX_BLOCKS  256

/* Error recovery retry count */
#define RA_SDHI_ERROR_RETRY_MAX 3

/* Timing constraints (from RA8 BSP) */
#define RA_SDHI_RESET_WAIT_US       10      /* Reset wait time in microseconds */
#define RA_SDHI_CLOCK_STABLE_US     100     /* Clock stabilization time */
#define RA_SDHI_CBSY_TIMEOUT_MS     1000    /* CBSY timeout in milliseconds */
#define RA_SDHI_MIN_BLOCK_SIZE      1       /* Minimum block size */
#define RA_SDHI_MAX_BLOCK_SIZE      512     /* Maximum block size */

/* CMD12 automatic issuing modes */
#define RA_SDHI_CMD12_AUTO_ENABLE   0       /* Automatic CMD12 enabled */
#define RA_SDHI_CMD12_AUTO_DISABLE  1       /* Automatic CMD12 disabled */

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct ra_sdhi_dev_s
{
  struct sdio_dev_s  dev;             /* Standard, base SDIO interface */

  /* RA8-specific fields */
  int                channel;         /* SDHI channel number */

  /* Interrupts */
  int                elc_accs;
  int                elc_sdio;
  int                elc_card;
  int                elc_dma;

  /* Events */
  sem_t              waitsem;         /* Semaphore for event waiting */
  sdio_eventset_t    waitevents;      /* Events to wait for */
  sdio_eventset_t    wkupevent;       /* Event that caused wakeup */
  uint32_t           waitmask_info1;  /* Interrupt mask for waiting (INFO1) */
  uint32_t           waitmask_info2;  /* Interrupt mask for waiting (INFO2) */
  struct wdog_s          waitwdog;        /* Watchdog for timeouts */

  /* Callback */
  worker_t           callback;
  void              *cbarg;
  sdio_eventset_t    cbevents;

  /* Transfer state */
  uint32_t           remaining;
  uint32_t          *buffer;
  bool               widebus;
  bool               onebit;
  bool               cd_inverted;
  bool               wp_inverted;

  /* Card status */
  bool               inserted;
  uint8_t            bus_width;     /* Current bus width: 1, 4, or 8 */
  uint8_t            max_bus_width; /* Maximum supported bus width */

  /* DMA support */
#ifdef CONFIG_RA_DMAC
  bool               dma_enabled;   /* DMA is enabled for transfers */
  ra_dmac_handle_t   dma_tx;        /* TX DMA handle */
  ra_dmac_handle_t   dma_rx;        /* RX DMA handle */
  volatile bool      dma_tx_done;   /* TX DMA completion flag */
  volatile bool      dma_rx_done;   /* RX DMA completion flag */
  int                dma_channel;   /* Assigned DMA channel (-1 = dynamic) */
#endif

  /* Error handling */
  uint32_t           err_sts1;      /* Last SD_ERR_STS1 value */
  uint32_t           err_sts2;      /* Last SD_ERR_STS2 value */
  uint8_t            error_retry;   /* Error retry counter */

  /* Multi-block transfer state */
  bool               multiblock;    /* Multi-block transfer in progress */
  uint32_t           blocksize;     /* Current block size */
  uint32_t           nblocks;       /* Number of blocks in transfer */
  bool               autocmd12;     /* Automatic CMD12 enabled */

#ifdef CONFIG_PM
  /* Power management */
  struct pm_callback_s pmcb;        /* PM callbacks */
  bool               suspended;     /* Suspended state */
#endif
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Low-level helpers */
static void ra_sdhi_configwaitints(struct ra_sdhi_dev_s *priv, uint32_t waitmask_info1,
                                   uint32_t waitmask_info2, sdio_eventset_t waitevents);
static void ra_sdhi_enableints(struct ra_sdhi_dev_s *priv);
static void ra_sdhi_disableints(struct ra_sdhi_dev_s *priv);

/* Interrupt Handling */
static int  ra_sdhi_access_isr(int irq, void *context, void *arg);
static int  ra_sdhi_card_isr(int irq, void *context, void *arg);
static int  ra_sdhi_sdio_isr(int irq, void *context, void *arg);
static int  ra_sdhi_dma_req_isr(int irq, void *context, void *arg);
static void ra_sdhi_callback(void *arg);

/* DMA Support */
#ifdef CONFIG_RA_DMAC
static void ra_sdhi_get_dma_channel(struct ra_sdhi_dev_s *priv, int *channel);
static int  ra_sdhi_dma_setup(struct ra_sdhi_dev_s *priv);
static int  ra_sdhi_dma_transfer(struct ra_sdhi_dev_s *priv, const void *txbuffer,
                                 void *rxbuffer, size_t nbytes);
static void ra_sdhi_dma_tx_callback(void *handle, int event, void *arg);
static void ra_sdhi_dma_rx_callback(void *handle, int event, void *arg);
static void ra_sdhi_dma_cleanup(struct ra_sdhi_dev_s *priv);
#endif

/* Error Handling */
static void ra_sdhi_parse_errors(struct ra_sdhi_dev_s *priv);
static int  ra_sdhi_error_recovery(struct ra_sdhi_dev_s *priv);
static int  ra_sdhi_wait_cbsy_clear(struct ra_sdhi_dev_s *priv, uint32_t timeout_ms);

/* Multi-block transfer support */
static void ra_sdhi_setup_cmd12_auto(struct ra_sdhi_dev_s *priv, bool enable);
static int  ra_sdhi_check_transfer_status(struct ra_sdhi_dev_s *priv);

/* Power Management */
#ifdef CONFIG_PM
static int  ra_sdhi_pm_prepare(struct pm_callback_s *cb, int domain,
                               enum pm_state_e pmstate);
static void ra_sdhi_pm_notify(struct pm_callback_s *cb, int domain,
                              enum pm_state_e pmstate);
#endif

/* SDIO interface methods */
static void ra_sdhi_reset(struct sdio_dev_s *dev);
static sdio_capset_t ra_sdhi_capabilities(struct sdio_dev_s *dev);
static sdio_statset_t ra_sdhi_status(struct sdio_dev_s *dev);
static void ra_sdhi_widebus(struct sdio_dev_s *dev, bool enable);
static void ra_sdhi_clock(struct sdio_dev_s *dev, enum sdio_clock_e rate);
static int  ra_sdhi_attach(struct sdio_dev_s *dev);
static int  ra_sdhi_sendcmd(struct sdio_dev_s *dev, uint32_t cmd, uint32_t arg);
static void ra_sdhi_blocksetup(struct sdio_dev_s *dev, unsigned int blocklen,
                               unsigned int nblocks);
static int  ra_sdhi_recvsetup(struct sdio_dev_s *dev, uint8_t *buffer,
                              size_t nbytes);
static int  ra_sdhi_sendsetup(struct sdio_dev_s *dev, const uint8_t *buffer,
                              size_t nbytes);
static int  ra_sdhi_cancel(struct sdio_dev_s *dev);
static int  ra_sdhi_waitresponse(struct sdio_dev_s *dev, uint32_t cmd);
static int  ra_sdhi_recvshortcrc(struct sdio_dev_s *dev, uint32_t cmd,
                                 uint32_t *rshort);
static int  ra_sdhi_recvlong(struct sdio_dev_s *dev, uint32_t cmd,
                             uint32_t rlong[4]);
static int  ra_sdhi_recvshort(struct sdio_dev_s *dev, uint32_t cmd,
                              uint32_t *rshort);
static void ra_sdhi_waitenable(struct sdio_dev_s *dev,
                               sdio_eventset_t eventset, uint32_t timeout);
static sdio_eventset_t ra_sdhi_eventwait(struct sdio_dev_s *dev);
static void ra_sdhi_callbackenable(struct sdio_dev_s *dev,
                                   sdio_eventset_t eventset);
static int  ra_sdhi_registercallback(struct sdio_dev_s *dev,
                                     worker_t callback, void *arg);

/****************************************************************************
 * Private Data
 ****************************************************************************/

static struct ra_sdhi_dev_s g_sdhidev[2];

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static void ra_sdhi_configwaitints(struct ra_sdhi_dev_s *priv, uint32_t waitmask_info1,
                                   uint32_t waitmask_info2, sdio_eventset_t waitevents)
{
  irqstate_t flags;

  flags = enter_critical_section();
  priv->waitevents = waitevents;
  priv->waitmask_info1 = waitmask_info1;
  priv->waitmask_info2 = waitmask_info2;

  /* Enable specified interrupts */
  ra_putreg32(~waitmask_info1 & 0x3FF, R_SDHI_SD_INFO1_MASK(priv->channel));
  ra_putreg32(~waitmask_info2 & 0xFFFF, R_SDHI_SD_INFO2_MASK(priv->channel));

  leave_critical_section(flags);
}

static void ra_sdhi_disableints(struct ra_sdhi_dev_s *priv)
{
  /* Mask all interrupts */
  ra_putreg32(0xFFFFFFFF, R_SDHI_SD_INFO1_MASK(priv->channel));
  ra_putreg32(0xFFFFFFFF, R_SDHI_SD_INFO2_MASK(priv->channel));
}

static void ra_sdhi_enableints(struct ra_sdhi_dev_s *priv)
  __attribute__((unused));
static void ra_sdhi_enableints(struct ra_sdhi_dev_s *priv)
{
  /* Enable default interrupts */
  ra_putreg32(0x00000000, R_SDHI_SD_INFO1_MASK(priv->channel));
  ra_putreg32(0x00000000, R_SDHI_SD_INFO2_MASK(priv->channel));
}

static void ra_sdhi_eventtimeout(wdparm_t arg)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)arg;

  priv->wkupevent = SDIOWAIT_TIMEOUT;
  nxsem_post(&priv->waitsem);
}

static int ra_sdhi_access_isr(int irq, void *context, void *arg)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)arg;
  uint32_t info1;
  uint32_t info2;
  sdio_eventset_t events = 0;

  info1 = ra_getreg32(R_SDHI_SD_INFO1(priv->channel));
  info2 = ra_getreg32(R_SDHI_SD_INFO2(priv->channel));

  /* Clear interrupts */
  ra_putreg32(info1 & ~RA_SDHI_INFO1_ACCESS_INTS & ~RA_SDHI_INFO1_RESP_INTS, R_SDHI_SD_INFO1(priv->channel));
  ra_putreg32(info2 & ~RA_SDHI_INFO2_ERR_INTS & ~RA_SDHI_INFO2_XFR_INTS, R_SDHI_SD_INFO2(priv->channel));

  /* Check for errors */
  if (info2 & RA_SDHI_INFO2_ERR_INTS)
    {
      /* Parse detailed error information */
      ra_sdhi_parse_errors(priv);

      if (info2 & R_SDHI_SD_INFO2_RSPTO)
        {
          events |= SDIOWAIT_TIMEOUT;
        }
      else
        {
          events |= SDIOWAIT_ERROR;
        }

      /* Attempt error recovery */
      ra_sdhi_error_recovery(priv);
    }
  else
    {
      /* Successful operation - reset error retry counter */
      priv->error_retry = 0;
    }

  /* Check for response end */
  if (info1 & R_SDHI_SD_INFO1_RSPEND)
    {
      events |= SDIOWAIT_CMDDONE;
    }

  /* Check for data transfer events */
  if (info2 & R_SDHI_SD_INFO2_BRE)
    {
      /* Buffer Read Enable - PIO Read */
      /* Read data with bounds checking to prevent buffer overflow */
      while ((ra_getreg32(R_SDHI_SD_INFO2(priv->channel)) & R_SDHI_SD_INFO2_BRE) &&
             priv->remaining >= 4)  /* Ensure at least 4 bytes remain */
        {
          if (priv->buffer != NULL)
            {
              *priv->buffer++ = ra_getreg32(R_SDHI_SD_BUF0(priv->channel));
              priv->remaining -= 4;
            }
          else
            {
              /* Buffer is NULL, discard data and log error */
              (void)ra_getreg32(R_SDHI_SD_BUF0(priv->channel));
              events |= SDIOWAIT_ERROR;
              break;
            }
        }

      /* Clear BRE */
      ra_putreg32(info2 & ~R_SDHI_SD_INFO2_BRE, R_SDHI_SD_INFO2(priv->channel));
    }

  if (info2 & R_SDHI_SD_INFO2_BWE)
    {
      /* Buffer Write Enable - PIO Write */
      /* Write data with bounds checking to prevent buffer overflow */
      while ((ra_getreg32(R_SDHI_SD_INFO2(priv->channel)) & R_SDHI_SD_INFO2_BWE) &&
             priv->remaining >= 4)  /* Ensure at least 4 bytes remain */
        {
          if (priv->buffer != NULL)
            {
              ra_putreg32(*priv->buffer++, R_SDHI_SD_BUF0(priv->channel));
              priv->remaining -= 4;
            }
          else
            {
              /* Buffer is NULL, write zeros and log error */
              ra_putreg32(0, R_SDHI_SD_BUF0(priv->channel));
              events |= SDIOWAIT_ERROR;
              break;
            }
        }

      /* Clear BWE */
      ra_putreg32(info2 & ~R_SDHI_SD_INFO2_BWE, R_SDHI_SD_INFO2(priv->channel));
    }

  if (info1 & R_SDHI_SD_INFO1_ACEND)
    {
      events |= SDIOWAIT_TRANSFERDONE;
    }

  if (events & priv->waitevents)
    {
      priv->wkupevent = events;
      nxsem_post(&priv->waitsem);
    }

  return OK;
}

static int ra_sdhi_card_isr(int irq, void *context, void *arg)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)arg;
  uint32_t info1;

  info1 = ra_getreg32(R_SDHI_SD_INFO1(priv->channel));

  /* Clear interrupts */
  ra_putreg32(info1 & ~RA_SDHI_INFO1_CARD_INTS, R_SDHI_SD_INFO1(priv->channel));

  if (info1 & R_SDHI_SD_INFO1_SDCDIN)
    {
      priv->inserted = true;
      if (priv->callback)
        {
          priv->callback(priv->cbarg);
        }
    }

  if (info1 & R_SDHI_SD_INFO1_SDCDRM)
    {
      priv->inserted = false;
      if (priv->callback)
        {
          priv->callback(priv->cbarg);
        }
    }

  return OK;
}

static int ra_sdhi_sdio_isr(int irq, void *context, void *arg)
  __attribute__((unused));
static int ra_sdhi_sdio_isr(int irq, void *context, void *arg)
{
  /* Not implemented yet */
  return OK;
}

static int ra_sdhi_dma_req_isr(int irq, void *context, void *arg)
  __attribute__((unused));
static int ra_sdhi_dma_req_isr(int irq, void *context, void *arg)
{
  /* Not implemented yet */
  return OK;
}

/****************************************************************************
 * Name: ra_sdhi_dma_tx_callback
 *
 * Description:
 *   TX DMA completion callback
 *
 ****************************************************************************/

#ifdef CONFIG_RA_DMAC
static void ra_sdhi_dma_tx_callback(void *handle, int event, void *arg)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)arg;

  if (event == RA_DMAC_EVENT_COMPLETE)
    {
      priv->dma_tx_done = true;

      /* Check if both TX and RX are done */
      if (priv->dma_rx_done || priv->dma_rx == NULL)
        {
          /* Signal transfer completion */
          priv->wkupevent = SDIOWAIT_TRANSFERDONE;
          nxsem_post(&priv->waitsem);
        }
    }
  else if (event == RA_DMAC_EVENT_ERROR)
    {
      priv->dma_tx_done = true;
      priv->wkupevent = SDIOWAIT_ERROR;
      nxsem_post(&priv->waitsem);
    }
}

/****************************************************************************
 * Name: ra_sdhi_dma_rx_callback
 *
 * Description:
 *   RX DMA completion callback
 *
 ****************************************************************************/

static void ra_sdhi_dma_rx_callback(void *handle, int event, void *arg)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)arg;

  if (event == RA_DMAC_EVENT_COMPLETE)
    {
      priv->dma_rx_done = true;

      /* Check if both TX and RX are done */
      if (priv->dma_tx_done || priv->dma_tx == NULL)
        {
          /* Signal transfer completion */
          priv->wkupevent = SDIOWAIT_TRANSFERDONE;
          nxsem_post(&priv->waitsem);
        }
    }
  else if (event == RA_DMAC_EVENT_ERROR)
    {
      priv->dma_rx_done = true;
      priv->wkupevent = SDIOWAIT_ERROR;
      nxsem_post(&priv->waitsem);
    }
}

/****************************************************************************
 * Name: ra_sdhi_get_dma_channel
 *
 * Description:
 *   Get DMA channel assignment from Kconfig for the specified SDHI channel
 *
 ****************************************************************************/

static void ra_sdhi_get_dma_channel(struct ra_sdhi_dev_s *priv, int *channel)
{
  /* Default to dynamic allocation */
  *channel = -1;

  if (priv->channel == 0)
    {
#ifdef CONFIG_RA_DMAC_SDHI0_CHANNEL
      *channel = CONFIG_RA_DMAC_SDHI0_CHANNEL;
#endif
    }
  else if (priv->channel == 1)
    {
#ifdef CONFIG_RA_DMAC_SDHI1_CHANNEL
      *channel = CONFIG_RA_DMAC_SDHI1_CHANNEL;
#endif
    }

  mcinfo("SDHI%d DMA channel: %d\n", priv->channel, *channel);
}

/****************************************************************************
 * Name: ra_sdhi_dma_setup
 *
 * Description:
 *   Setup DMA channels for SDHI transfers
 *
 ****************************************************************************/

static int ra_sdhi_dma_setup(struct ra_sdhi_dev_s *priv)
{
  int ret;

  /* Initialize DMAC module */
  ret = ra_dmac_initialize();
  if (ret < 0)
    {
      return ret;
    }

  /* Get DMA channel assignment from Kconfig */
  ra_sdhi_get_dma_channel(priv, &priv->dma_channel);

#if (defined(CONFIG_RA_SDHI0_USE_DMAC) && priv->channel == 0) || \\
    (defined(CONFIG_RA_SDHI1_USE_DMAC) && priv->channel == 1)
  priv->dma_enabled = true;
#else
  priv->dma_enabled = false;
#endif

  /* If DMA is not enabled for this instance, return early */
  if (!priv->dma_enabled)
    {
      mcinfo("SDHI%d DMA disabled by Kconfig\n", priv->channel);
      return OK;
    }

  priv->dma_tx = NULL;
  priv->dma_rx = NULL;
  priv->dma_tx_done = false;
  priv->dma_rx_done = false;

  mcinfo("SDHI%d DMA setup completed (channel=%d)\n", priv->channel, priv->dma_channel);

  return OK;
}

/****************************************************************************
 * Name: ra_sdhi_dma_transfer
 *
 * Description:
 *   Perform DMA transfer for SDHI
 *
 ****************************************************************************/

static int ra_sdhi_dma_transfer(struct ra_sdhi_dev_s *priv,
                                const void *txbuffer, void *rxbuffer,
                                size_t nbytes)
{
  ra_dmac_config_t config;
  int ret;
  uint32_t nblocks;

  /* Calculate number of blocks */
  nblocks = (nbytes + RA_SDHI_DMA_BLOCK_SIZE - 1) / RA_SDHI_DMA_BLOCK_SIZE;

  if (nblocks > RA_SDHI_DMA_MAX_BLOCKS)
    {
      return -E2BIG;
    }

  /* Reset completion flags */
  priv->dma_tx_done = (txbuffer == NULL);
  priv->dma_rx_done = (rxbuffer == NULL);

  /* Configure TX DMA if transmit buffer provided */
  if (txbuffer != NULL)
    {
      memset(&config, 0, sizeof(config));
      config.mode = (nblocks > 1) ? RA_DMAC_MODE_BLOCK : RA_DMAC_MODE_NORMAL;
      config.repeat_area = RA_DMAC_REPEAT_AREA_NONE;
      config.size = RA_DMAC_SIZE_32BIT;
      config.src_addr_mode = RA_DMAC_ADDR_INCR;
      config.dest_addr_mode = RA_DMAC_ADDR_FIXED;
      config.trigger = RA_DMAC_TRIGGER_HW;
      config.src_addr = (uint32_t)txbuffer;
      config.dest_addr = R_SDHI_SD_BUF0(priv->channel);
      config.transfer_count = RA_SDHI_DMA_BLOCK_SIZE / 4; /* Words per block */
      config.block_count = nblocks;
      config.elc_end = -1; /* Not using end event link */
      config.elc_err = -1; /* Not using error event link */
      config.elc_src = priv->elc_dma; /* Use DMA request event */
      config.callback = ra_sdhi_dma_tx_callback;
      config.user_data = priv;

      /* Use assigned channel if configured, otherwise use dynamic allocation */
      if (priv->dma_channel >= 0)
        {
          ret = ra_dmac_open_channel(&priv->dma_tx, &config, priv->dma_channel);
          mcinfo("SDHI TX DMA using assigned channel %d\n", priv->dma_channel);
        }
      else
        {
          ret = ra_dmac_open(&priv->dma_tx, &config);
          mcinfo("SDHI TX DMA using dynamic channel allocation\n");
        }

      if (ret < 0)
        {
          return ret;
        }

      ret = ra_dmac_enable(priv->dma_tx);
      if (ret < 0)
        {
          ra_dmac_close(priv->dma_tx);
          priv->dma_tx = NULL;
          return ret;
        }
    }

  /* Configure RX DMA if receive buffer provided */
  if (rxbuffer != NULL)
    {
      memset(&config, 0, sizeof(config));
      config.mode = (nblocks > 1) ? RA_DMAC_MODE_BLOCK : RA_DMAC_MODE_NORMAL;
      config.repeat_area = RA_DMAC_REPEAT_AREA_NONE;
      config.size = RA_DMAC_SIZE_32BIT;
      config.src_addr_mode = RA_DMAC_ADDR_FIXED;
      config.dest_addr_mode = RA_DMAC_ADDR_INCR;
      config.trigger = RA_DMAC_TRIGGER_HW;
      config.src_addr = R_SDHI_SD_BUF0(priv->channel);
      config.dest_addr = (uint32_t)rxbuffer;
      config.transfer_count = RA_SDHI_DMA_BLOCK_SIZE / 4; /* Words per block */
      config.block_count = nblocks;
      config.elc_end = -1; /* Not using end event link */
      config.elc_err = -1; /* Not using error event link */
      config.elc_src = priv->elc_dma; /* Use DMA request event */
      config.callback = ra_sdhi_dma_rx_callback;
      config.user_data = priv;

      /* Use assigned channel if configured, otherwise use dynamic allocation */
      if (priv->dma_channel >= 0)
        {
          ret = ra_dmac_open_channel(&priv->dma_rx, &config, priv->dma_channel);
          mcinfo("SDHI RX DMA using assigned channel %d\n", priv->dma_channel);
        }
      else
        {
          ret = ra_dmac_open(&priv->dma_rx, &config);
          mcinfo("SDHI RX DMA using dynamic channel allocation\n");
        }

      if (ret < 0)
        {
          if (priv->dma_tx)
            {
              ra_dmac_disable(priv->dma_tx);
              ra_dmac_close(priv->dma_tx);
              priv->dma_tx = NULL;
            }
          return ret;
        }

      ret = ra_dmac_enable(priv->dma_rx);
      if (ret < 0)
        {
          ra_dmac_close(priv->dma_rx);
          priv->dma_rx = NULL;
          if (priv->dma_tx)
            {
              ra_dmac_disable(priv->dma_tx);
              ra_dmac_close(priv->dma_tx);
              priv->dma_tx = NULL;
            }
          return ret;
        }
    }

  /* Enable DMA in SDHI controller */
  ra_putreg32(R_SDHI_SD_DMAEN_DMAEN, R_SDHI_SD_DMAEN(priv->channel));

  return OK;
}

/****************************************************************************
 * Name: ra_sdhi_dma_cleanup
 *
 * Description:
 *   Cleanup DMA resources after transfer
 *
 ****************************************************************************/

static void ra_sdhi_dma_cleanup(struct ra_sdhi_dev_s *priv)
{
  /* Disable DMA in SDHI controller */
  ra_putreg32(0, R_SDHI_SD_DMAEN(priv->channel));

  /* Clean up TX DMA */
  if (priv->dma_tx != NULL)
    {
      ra_dmac_disable(priv->dma_tx);
      ra_dmac_close(priv->dma_tx);
      priv->dma_tx = NULL;
    }

  /* Clean up RX DMA */
  if (priv->dma_rx != NULL)
    {
      ra_dmac_disable(priv->dma_rx);
      ra_dmac_close(priv->dma_rx);
      priv->dma_rx = NULL;
    }

  priv->dma_tx_done = false;
  priv->dma_rx_done = false;
}
#endif /* CONFIG_RA_DMAC */

/****************************************************************************
 * Name: ra_sdhi_wait_cbsy_clear
 *
 * Description:
 *   Wait for CBSY (Command Type Register Busy) to clear with timeout
 *   Following RA8 BSP timing constraints
 *
 ****************************************************************************/

static int ra_sdhi_wait_cbsy_clear(struct ra_sdhi_dev_s *priv,
                                   uint32_t timeout_ms)
{
  uint32_t start = clock_systime_ticks();
  uint32_t timeout_ticks = MSEC2TICK(timeout_ms);

  while (ra_getreg32(R_SDHI_SD_INFO2(priv->channel)) & R_SDHI_SD_INFO2_CBSY)
    {
      if ((clock_systime_ticks() - start) > timeout_ticks)
        {
          mcerr("SDHI%d: CBSY timeout\n", priv->channel);
          return -ETIMEDOUT;
        }

      /* Small delay to avoid bus contention */
      up_udelay(1);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_sdhi_setup_cmd12_auto
 *
 * Description:
 *   Configure automatic CMD12 issuing for multi-block transfers
 *   Following RA8 BSP patterns for proper multi-block handling
 *
 ****************************************************************************/

static void ra_sdhi_setup_cmd12_auto(struct ra_sdhi_dev_s *priv,
                                     bool enable)
{
  /* CMD12 automatic issuing is controlled by SD_CMD[15:14] bits
   * 00b: CMD12 automatically issued
   * 01b: CMD12 not automatically issued
   * The actual bits are set per-command in sendcmd
   */

  if (enable)
    {
      priv->autocmd12 = true;
      /* Automatic CMD12 will be set per-command in sendcmd */
    }
  else
    {
      priv->autocmd12 = false;
    }
}/****************************************************************************
 * Name: ra_sdhi_check_transfer_status
 *
 * Description:
 *   Check transfer status with enhanced error detection
 *   Examines both INFO2 and ERR_STS registers
 *
 ****************************************************************************/

static int ra_sdhi_check_transfer_status(struct ra_sdhi_dev_s *priv)
  __attribute__((unused));
static int ra_sdhi_check_transfer_status(struct ra_sdhi_dev_s *priv)
{
  uint32_t info2;
  uint32_t err_sts1;
  uint32_t err_sts2;

  info2 = ra_getreg32(R_SDHI_SD_INFO2(priv->channel));

  /* Check for errors in INFO2 */
  if (info2 & RA_SDHI_INFO2_ERR_INTS)
    {
      /* Read detailed error status */
      err_sts1 = ra_getreg32(R_SDHI_SD_ERR_STS1(priv->channel));
      err_sts2 = ra_getreg32(R_SDHI_SD_ERR_STS2(priv->channel));

      priv->err_sts1 = err_sts1;
      priv->err_sts2 = err_sts2;

      /* Parse and log errors */
      ra_sdhi_parse_errors(priv);

      if (info2 & R_SDHI_SD_INFO2_RSPTO)
        {
          return -ETIMEDOUT;
        }
      else if (info2 & R_SDHI_SD_INFO2_CRCE)
        {
          return -EILSEQ;  /* CRC error */
        }
      else if (info2 & R_SDHI_SD_INFO2_DTO)
        {
          return -ETIMEDOUT;  /* Data timeout */
        }

      return -EIO;  /* Generic error */
    }

  return OK;
}

/****************************************************************************
 * Name: ra_sdhi_parse_errors
 *
 * Description:
 *   Parse SD_ERR_STS1/2 registers for detailed error information
 *
 ****************************************************************************/

static void ra_sdhi_parse_errors(struct ra_sdhi_dev_s *priv)
{
  /* Read error status registers */
  priv->err_sts1 = ra_getreg32(R_SDHI_SD_ERR_STS1(priv->channel));
  priv->err_sts2 = ra_getreg32(R_SDHI_SD_ERR_STS2(priv->channel));

  /* Log detailed error information */
  if (priv->err_sts1 != 0)
    {
      mcerr("SDHI%d ERR_STS1: 0x%08" PRIx32 "\n", priv->channel, priv->err_sts1);

      /* Parse SD_ERR_STS1 bits (see hardware manual) */
      if (priv->err_sts1 & (1 << 0))
        {
          mcerr("  Command error\n");
        }
      if (priv->err_sts1 & (1 << 1))
        {
          mcerr("  CRC error\n");
        }
      if (priv->err_sts1 & (1 << 2))
        {
          mcerr("  End bit error\n");
        }
      if (priv->err_sts1 & (1 << 3))
        {
          mcerr("  Data timeout\n");
        }
      if (priv->err_sts1 & (1 << 6))
        {
          mcerr("  Response timeout\n");
        }
    }

  if (priv->err_sts2 != 0)
    {
      mcerr("SDHI%d ERR_STS2: 0x%08" PRIx32 "\n", priv->channel, priv->err_sts2);

      /* Parse SD_ERR_STS2 bits (see hardware manual) */
      if (priv->err_sts2 & (1 << 0))
        {
          mcerr("  Buffer read error\n");
        }
      if (priv->err_sts2 & (1 << 1))
        {
          mcerr("  Buffer write error\n");
        }
    }
}

/****************************************************************************
 * Name: ra_sdhi_error_recovery
 *
 * Description:
 *   Attempt error recovery for SDHI
 *
 ****************************************************************************/

static int ra_sdhi_error_recovery(struct ra_sdhi_dev_s *priv)
{
  int ret;

  /* Increment retry counter */
  priv->error_retry++;

  if (priv->error_retry > RA_SDHI_ERROR_RETRY_MAX)
    {
      mcerr("SDHI%d: Max error retries exceeded\n", priv->channel);
      priv->error_retry = 0;
      return -EIO;
    }

  mcinfo("SDHI%d: Attempting error recovery (retry %d/%d)\n",
         priv->channel, priv->error_retry, RA_SDHI_ERROR_RETRY_MAX);

  /* Clear error flags following RA8 BSP pattern */
  ra_putreg32(0, R_SDHI_SD_INFO1(priv->channel));
  ra_putreg32(0, R_SDHI_SD_INFO2(priv->channel));

  /* Perform soft reset with proper timing constraints */
  ra_putreg32(0, R_SDHI_SOFT_RST(priv->channel));
  up_udelay(RA_SDHI_RESET_WAIT_US);  /* Wait per RA8 BSP timing */
  ra_putreg32(R_SDHI_SOFT_RST_SDRST, R_SDHI_SOFT_RST(priv->channel));

  /* Wait for reset to complete with timeout */
  uint32_t timeout = 1000;  /* 1ms timeout */
  while ((ra_getreg32(R_SDHI_SOFT_RST(priv->channel)) & R_SDHI_SOFT_RST_SDRST) &&
         timeout > 0)
    {
      up_udelay(1);
      timeout--;
    }

  if (timeout == 0)
    {
      mcerr("SDHI%d: Reset timeout during recovery\n", priv->channel);
      return -ETIMEDOUT;
    }

  /* Restore configuration */
  ra_putreg32(0x40E0, R_SDHI_SD_OPTION(priv->channel));

  /* Wait for configuration to stabilize */
  up_udelay(RA_SDHI_CLOCK_STABLE_US);

  /* Re-enable interrupts */
  ra_sdhi_enableints(priv);

  ret = OK;
  return ret;
}

/****************************************************************************
 * Name: ra_sdhi_pm_prepare
 *
 * Description:
 *   PM prepare callback - called before state transition
 *
 ****************************************************************************/

#ifdef CONFIG_PM
static int ra_sdhi_pm_prepare(struct pm_callback_s *cb, int domain,
                              enum pm_state_e pmstate)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)
    ((char *)cb - offsetof(struct ra_sdhi_dev_s, pmcb));

  /* Only handle PM_STANDBY and deeper sleep states */
  if (pmstate >= PM_STANDBY)
    {
      /* Check if we can suspend - don't suspend during active transfers */
      uint32_t info2 = ra_getreg32(R_SDHI_SD_INFO2(priv->channel));
      if (info2 & R_SDHI_SD_INFO2_CBSY)
        {
          /* Transfer in progress, deny suspend */
          return -EBUSY;
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_sdhi_pm_notify
 *
 * Description:
 *   PM notify callback - called after state transition
 *
 ****************************************************************************/

static void ra_sdhi_pm_notify(struct pm_callback_s *cb, int domain,
                              enum pm_state_e pmstate)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)
    ((char *)cb - offsetof(struct ra_sdhi_dev_s, pmcb));

  switch (pmstate)
    {
      case PM_NORMAL:
      case PM_IDLE:
        /* Resume from suspend */
        if (priv->suspended)
          {
            /* Enable module clock */
            ra_mstp_start(priv->channel == 0 ? RA_MSTP_SDHI0 : RA_MSTP_SDHI1);

            /* Re-initialize controller */
            ra_sdhi_reset((struct sdio_dev_s *)priv);

            priv->suspended = false;
          }
        break;

      case PM_STANDBY:
      case PM_SLEEP:
        /* Enter suspend */
        if (!priv->suspended)
          {
            /* Disable interrupts */
            ra_sdhi_disableints(priv);

            /* Disable module clock */
            ra_mstp_stop(priv->channel == 0 ? RA_MSTP_SDHI0 : RA_MSTP_SDHI1);

            priv->suspended = true;
          }
        break;

      default:
        break;
    }
}
#endif /* CONFIG_PM */

/* SDIO Interface Methods */

static void ra_sdhi_reset(struct sdio_dev_s *dev)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;
  uint32_t timeout;

  /* Soft reset following RA8 BSP sequence with proper timing */
  ra_putreg32(0, R_SDHI_SOFT_RST(priv->channel));

  /* Wait before asserting reset per RA8 BSP timing constraints */
  up_udelay(RA_SDHI_RESET_WAIT_US);

  ra_putreg32(R_SDHI_SOFT_RST_SDRST, R_SDHI_SOFT_RST(priv->channel));

  /* Wait for reset to complete with timeout (SDRST clears to 0) */
  timeout = 1000;  /* 1ms timeout */
  while ((ra_getreg32(R_SDHI_SOFT_RST(priv->channel)) & R_SDHI_SOFT_RST_SDRST) &&
         timeout > 0)
    {
      up_udelay(1);
      timeout--;
    }

  if (timeout == 0)
    {
      mcerr("SDHI%d: Reset timeout\n", priv->channel);
    }

  /* Set default options following RA8 BSP pattern
   * Bit 15 (WIDTH): 0 = 4-bit bus width default
   * Bit 14: Reserved
   * Bit 13 (WIDTH8): 0 = not 8-bit mode
   * Bits 7-4 (TOP): Timeout counter setting
   * Default: 0x40E0 provides proper timeout configuration
   */
  ra_putreg32(0x40E0, R_SDHI_SD_OPTION(priv->channel));

  /* Wait for configuration to stabilize per RA8 BSP timing */
  up_udelay(RA_SDHI_CLOCK_STABLE_US);

  /* Clear all interrupt status flags */
  ra_putreg32(0, R_SDHI_SD_INFO1(priv->channel));
  ra_putreg32(0, R_SDHI_SD_INFO2(priv->channel));

  /* Mask all interrupts initially */
  ra_sdhi_disableints(priv);

  /* Reset multi-block state */
  priv->multiblock = false;
  priv->autocmd12 = false;
  priv->blocksize = 512;
  priv->nblocks = 1;
}

static sdio_capset_t ra_sdhi_capabilities(FAR struct sdio_dev_s *dev)
{
  /* RA8P1 SDHI supports up to 4-bit SD cards
   * 8-bit mode is only available for eMMC on some channels
   * NuttX SDIO interface assumes 1-bit support is always present
   * We explicitly report 4-bit capability
   */
  return SDIO_CAPS_4BIT;
}

static sdio_statset_t ra_sdhi_status(struct sdio_dev_s *dev)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;
  sdio_statset_t status = 0;

  /* Check card present */
  /* Note: We use the cached state from ISR or initial check */
  /* Alternatively, read SD_INFO1 SDCDMON bit */
  uint32_t info1 = ra_getreg32(R_SDHI_SD_INFO1(priv->channel));
  bool present = (info1 & R_SDHI_SD_INFO1_SDCDMON) != 0;

  if (priv->cd_inverted)
    {
      present = !present;
    }

  if (present)
    {
      status |= SDIO_STATUS_PRESENT;
    }

  /* Check write protect */
  bool wp = (info1 & R_SDHI_SD_INFO1_SDWPMON) != 0;
  if (priv->wp_inverted)
    {
      wp = !wp;
    }

  if (wp)
    {
      status |= SDIO_STATUS_WRPROTECTED;
    }

  return status;
}

static void ra_sdhi_widebus(struct sdio_dev_s *dev, bool enable)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;
  uint32_t option;

  priv->widebus = enable;

  option = ra_getreg32(R_SDHI_SD_OPTION(priv->channel));

  /* Per FSP specification:
   * 1-bit mode: WIDTH=1 (bit 15), WIDTH8=0 (bit 13)
   * 4-bit mode: WIDTH=0 (bit 15), WIDTH8=0 (bit 13)
   * 8-bit mode: WIDTH=0 (bit 15), WIDTH8=1 (bit 13) - eMMC only
   */
  if (enable)
    {
      /* 4-bit width: Clear both WIDTH and WIDTH8 */
      option &= ~R_SDHI_SD_OPTION_WIDTH;
      option &= ~R_SDHI_SD_OPTION_WIDTH8;
    }
  else
    {
      /* 1-bit width: Set WIDTH, clear WIDTH8 */
      option |= R_SDHI_SD_OPTION_WIDTH;
      option &= ~R_SDHI_SD_OPTION_WIDTH8;
    }

  ra_putreg32(option, R_SDHI_SD_OPTION(priv->channel));

  /* Wait for bus width change to take effect */
  up_mdelay(1);
}

static void ra_sdhi_clock(struct sdio_dev_s *dev, enum sdio_clock_e rate)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;
  uint32_t clk_ctrl;
  uint32_t div = 0;
  uint32_t pclka_freq;
  uint32_t target = 0;
  uint32_t actual_div;

  /* Get PCLKA frequency - SDHI uses PCLKA as clock source */
  pclka_freq = ra_get_peripheral_clock(RA_PCLK_PCLKA);

  /* Validate clock frequency */
  if (pclka_freq == 0)
    {
      syslog(LOG_ERR, "ERROR: PCLKA frequency is 0\n");
      return;
    }

  /* Determine target frequency */
  switch (rate)
    {
      case CLOCK_SD_TRANSFER_1BIT:
      case CLOCK_SD_TRANSFER_4BIT:
        target = RA_SDHI_CLOCK_25MHZ;
        break;
      case CLOCK_IDMODE:
      default:
        target = RA_SDHI_CLOCK_400KHZ;
        break;
    }

  /* Stop clock */
  clk_ctrl = ra_getreg32(R_SDHI_SD_CLK_CTRL(priv->channel));
  clk_ctrl &= ~R_SDHI_SD_CLK_CTRL_CLKEN;
  ra_putreg32(clk_ctrl, R_SDHI_SD_CLK_CTRL(priv->channel));

  /* Calculate required divider: actual_div = pclka_freq / target */
  actual_div = (pclka_freq + target - 1) / target;  /* Round up */

  /* Convert to SDHI clock divider register format:
   * 0xFF: 1/1 (no division)
   * 0x00: 1/2
   * 0x01: 1/4
   * 0x02: 1/8
   * 0x04: 1/16
   * 0x08: 1/32
   * 0x10: 1/64
   * 0x20: 1/128
   * 0x40: 1/256
   * 0x80: 1/512
   */
  if (actual_div <= 1)
    {
      div = 0xFF;  /* No division */
    }
  else if (actual_div <= 2)
    {
      div = 0x00;  /* 1/2 */
    }
  else if (actual_div <= 4)
    {
      div = 0x01;  /* 1/4 */
    }
  else if (actual_div <= 8)
    {
      div = 0x02;  /* 1/8 */
    }
  else if (actual_div <= 16)
    {
      div = 0x04;  /* 1/16 */
    }
  else if (actual_div <= 32)
    {
      div = 0x08;  /* 1/32 */
    }
  else if (actual_div <= 64)
    {
      div = 0x10;  /* 1/64 */
    }
  else if (actual_div <= 128)
    {
      div = 0x20;  /* 1/128 */
    }
  else if (actual_div <= 256)
    {
      div = 0x40;  /* 1/256 */
    }
  else
    {
      div = 0x80;  /* 1/512 */
    }

  /* Set clock divider */
  clk_ctrl &= ~R_SDHI_SD_CLK_CTRL_CLKSEL_MASK;
  if (div != 0xFF)
    {
      clk_ctrl |= (div & R_SDHI_SD_CLK_CTRL_CLKSEL_MASK);
    }

  ra_putreg32(clk_ctrl, R_SDHI_SD_CLK_CTRL(priv->channel));

  /* Log clock configuration for debugging */
  syslog(LOG_INFO, "SDHI%d: PCLKA=%lu Hz, target=%lu Hz, div=0x%02lx\n",
         priv->channel, (unsigned long)pclka_freq, (unsigned long)target,
         (unsigned long)div);

  /* Enable clock */
  clk_ctrl |= R_SDHI_SD_CLK_CTRL_CLKEN;
  ra_putreg32(clk_ctrl, R_SDHI_SD_CLK_CTRL(priv->channel));

  /* Wait for clock to stabilize */
  up_udelay(100);
}

static int ra_sdhi_attach(struct sdio_dev_s *dev)
{
  /* Nothing special to do here */
  return OK;
}

static int ra_sdhi_sendcmd(struct sdio_dev_s *dev, uint32_t cmd, uint32_t arg)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;
  uint32_t cmd_reg = 0;
  uint32_t waitmask1 = 0;
  uint32_t waitmask2 = 0;
  int ret;
  uint8_t cmdidx;

  /* Wait for CBSY to clear with timeout (RA8 BSP pattern) */
  ret = ra_sdhi_wait_cbsy_clear(priv, RA_SDHI_CBSY_TIMEOUT_MS);
  if (ret < 0)
    {
      mcerr("SDHI%d: CBSY timeout before command\n", priv->channel);
      return ret;
    }

  /* Write argument */
  ra_putreg32(arg, R_SDHI_SD_ARG(priv->channel));

  /* Construct command */
  cmd_reg = (cmd & MMCSD_CMDIDX_MASK) >> MMCSD_CMDIDX_SHIFT;

  /* Response type */
  if ((cmd & MMCSD_RESPONSE_MASK) != MMCSD_NO_RESPONSE)
    {
      if ((cmd & MMCSD_RESPONSE_MASK) == MMCSD_R2_RESPONSE)
        {
          /* R2 */
          cmd_reg |= R_SDHI_SD_CMD_RSPTP_110;
        }
      else if ((cmd & MMCSD_RESPONSE_MASK) == MMCSD_R1B_RESPONSE)
        {
          /* R1b */
          cmd_reg |= R_SDHI_SD_CMD_RSPTP_101;
        }
      else
        {
          /* R1, R3, R4, R5, R6, R7 */
          /* FSP uses 100 for R1/R5/R6/R7 and 111 for R3/R4 */
          /* NuttX doesn't distinguish R3/R4 easily in flags, but they are 48-bit */
          cmd_reg |= R_SDHI_SD_CMD_RSPTP_100;
        }
    }
  else
    {
      /* No response */
      cmd_reg |= R_SDHI_SD_CMD_RSPTP_000;
    }

  /* Get command index for CMD12 detection */
  cmdidx = (cmd & MMCSD_CMDIDX_MASK) >> MMCSD_CMDIDX_SHIFT;

  /* Data transfer */
  if (cmd & MMCSD_DATAXFR_MASK)
    {
      cmd_reg |= R_SDHI_SD_CMD_CMDTP; /* Data transfer */

      if (cmd & MMCSD_WRXFR)
        {
          /* Write transfer */
        }
      else
        {
          cmd_reg |= R_SDHI_SD_CMD_CMDRW; /* Read transfer */
        }

      /* Configure CMD12 automatic issuing for multi-block transfers
       * Following RA8 BSP pattern:
       * - CMD18 (READ_MULTIPLE_BLOCK) and CMD25 (WRITE_MULTIPLE_BLOCK)
       *   can use automatic CMD12
       * - CMD53 (IO_RW_EXTENDED) may need manual CMD12
       */
      if (priv->multiblock && priv->autocmd12)
        {
          if (cmdidx == 18 || cmdidx == 25)  /* CMD18 or CMD25 */
            {
              /* Enable automatic CMD12 issuing
               * SD_CMD[15:14] = 00b for automatic CMD12
               */
              cmd_reg |= R_SDHI_SD_CMD_CMD12AT_00;

              mcinfo("SDHI%d: CMD%d with auto-CMD12\n", priv->channel, cmdidx);
            }
          else
            {
              /* Disable automatic CMD12 for other commands
               * SD_CMD[15:14] = 01b to disable automatic CMD12
               */
              cmd_reg |= R_SDHI_SD_CMD_CMD12AT_01;
            }
        }
      else if (priv->multiblock)
        {
          /* Multi-block without auto-CMD12 */
          cmd_reg |= R_SDHI_SD_CMD_CMD12AT_01;
        }

      /* Set TRSTP bit for single/multiple block transfer indication
       * This bit is set for multiple block transfers
       */
      if (priv->multiblock)
        {
          cmd_reg |= R_SDHI_SD_CMD_TRSTP;
        }
    }

  /* Configure interrupts */
  waitmask1 = R_SDHI_SD_INFO1_RSPEND;
  waitmask2 = RA_SDHI_INFO2_ERR_INTS;

  ra_sdhi_configwaitints(priv, waitmask1, waitmask2, SDIOWAIT_CMDDONE | SDIOWAIT_TIMEOUT | SDIOWAIT_ERROR);

  /* Write command */
  ra_putreg32(cmd_reg, R_SDHI_SD_CMD(priv->channel));

  return OK;
}

static void ra_sdhi_blocksetup(struct sdio_dev_s *dev, unsigned int blocklen,
                               unsigned int nblocks)
  __attribute__((unused));
static void ra_sdhi_blocksetup(struct sdio_dev_s *dev, unsigned int blocklen,
                               unsigned int nblocks)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;

  /* Validate block size per RA8 BSP constraints */
  if (blocklen < RA_SDHI_MIN_BLOCK_SIZE || blocklen > RA_SDHI_MAX_BLOCK_SIZE)
    {
      mcerr("SDHI%d: Invalid block size %u\n", priv->channel, blocklen);
      return;
    }

  /* Store multi-block transfer state */
  priv->blocksize = blocklen;
  priv->nblocks = nblocks;
  priv->multiblock = (nblocks > 1);

  /* Set transfer data size */
  ra_putreg32(blocklen, R_SDHI_SD_SIZE(priv->channel));

  if (nblocks > 1)
    {
      /* Multi-block transfer setup following RA8 BSP pattern */

      /* Set block count */
      ra_putreg32(nblocks, R_SDHI_SD_SECCNT(priv->channel));

      /* Enable block count and automatic CMD12 in SD_STOP register
       * SEC bit enables block count feature
       * Automatic CMD12 issuing will be configured per command
       */
      ra_putreg32(R_SDHI_SD_STOP_SEC, R_SDHI_SD_STOP(priv->channel));

      /* Enable automatic CMD12 for standard multi-block read/write */
      ra_sdhi_setup_cmd12_auto(priv, true);

      mcinfo("SDHI%d: Multi-block setup - %u blocks x %u bytes, auto-CMD12\n",
             priv->channel, nblocks, blocklen);
    }
  else
    {
      /* Single block transfer - no automatic CMD12 needed */
      ra_putreg32(0, R_SDHI_SD_STOP(priv->channel));
      ra_sdhi_setup_cmd12_auto(priv, false);

      mcinfo("SDHI%d: Single block setup - %u bytes\n",
             priv->channel, blocklen);
    }
}

static int ra_sdhi_recvsetup(struct sdio_dev_s *dev, uint8_t *buffer,
                             size_t nbytes)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;

  priv->buffer = (uint32_t*)buffer;
  priv->remaining = nbytes;

#ifdef CONFIG_RA_DMAC
  /* Use DMA for multi-block transfers if enabled and aligned */
  if (priv->dma_enabled && nbytes >= RA_SDHI_DMA_BLOCK_SIZE &&
      (nbytes % RA_SDHI_DMA_BLOCK_SIZE) == 0 &&
      ((uintptr_t)buffer % 4) == 0)
    {
      int ret = ra_sdhi_dma_transfer(priv, NULL, buffer, nbytes);
      if (ret == OK)
        {
          /* DMA setup successful - configure for DMA transfer */
          ra_sdhi_configwaitints(priv, RA_SDHI_INFO1_ACCESS_INTS,
                                RA_SDHI_INFO2_ERR_INTS,
                                SDIOWAIT_TRANSFERDONE | SDIOWAIT_TIMEOUT | SDIOWAIT_ERROR);
          return OK;
        }

      /* DMA setup failed - fall through to PIO mode */
      mcerr("SDHI%d: DMA setup failed, using PIO: %d\n", priv->channel, ret);
    }
#endif  /* Enable BRE interrupt for PIO */
  ra_sdhi_configwaitints(priv, RA_SDHI_INFO1_ACCESS_INTS, RA_SDHI_INFO2_ERR_INTS | R_SDHI_SD_INFO2_BRE,
                         SDIOWAIT_TRANSFERDONE | SDIOWAIT_TIMEOUT | SDIOWAIT_ERROR);

  return OK;
}

static int ra_sdhi_sendsetup(struct sdio_dev_s *dev, const uint8_t *buffer,
                             size_t nbytes)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;

  priv->buffer = (uint32_t*)buffer;
  priv->remaining = nbytes;

#ifdef CONFIG_RA_DMAC
  /* Use DMA for multi-block transfers if enabled and aligned */
  if (priv->dma_enabled && nbytes >= RA_SDHI_DMA_BLOCK_SIZE &&
      (nbytes % RA_SDHI_DMA_BLOCK_SIZE) == 0 &&
      ((uintptr_t)buffer % 4) == 0)
    {
      int ret = ra_sdhi_dma_transfer(priv, buffer, NULL, nbytes);
      if (ret == OK)
        {
          /* DMA setup successful - configure for DMA transfer */
          ra_sdhi_configwaitints(priv, RA_SDHI_INFO1_ACCESS_INTS,
                                RA_SDHI_INFO2_ERR_INTS,
                                SDIOWAIT_TRANSFERDONE | SDIOWAIT_TIMEOUT | SDIOWAIT_ERROR);
          return OK;
        }

      /* DMA setup failed - fall through to PIO mode */
      mcerr("SDHI%d: DMA setup failed, using PIO: %d\n", priv->channel, ret);
    }
#endif  /* Enable BWE interrupt for PIO */
  ra_sdhi_configwaitints(priv, RA_SDHI_INFO1_ACCESS_INTS, RA_SDHI_INFO2_ERR_INTS | R_SDHI_SD_INFO2_BWE,
                         SDIOWAIT_TRANSFERDONE | SDIOWAIT_TIMEOUT | SDIOWAIT_ERROR);

  return OK;
}

static int ra_sdhi_cancel(struct sdio_dev_s *dev)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;

#ifdef CONFIG_RA_DMAC
  /* Cleanup DMA if active */
  if (priv->dma_enabled && (priv->dma_tx != NULL || priv->dma_rx != NULL))
    {
      ra_sdhi_dma_cleanup(priv);
    }
#endif

  /* Stop transfer */
  ra_putreg32(R_SDHI_SD_STOP_STP, R_SDHI_SD_STOP(priv->channel));
  return OK;
}

static int ra_sdhi_waitresponse(struct sdio_dev_s *dev, uint32_t cmd)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;
  int ret;

  /* Wait for event */
  ret = nxsem_tickwait_uninterruptible(&priv->waitsem, RA_SDHI_CMDTIMEOUT);

  ra_sdhi_disableints(priv);

  if (ret < 0)
    {
      return ret;
    }

  if (priv->wkupevent & (SDIOWAIT_TIMEOUT | SDIOWAIT_ERROR))
    {
      return -EIO;
    }

  return OK;
}

static int ra_sdhi_recvshortcrc(struct sdio_dev_s *dev, uint32_t cmd,
                                uint32_t *rshort)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;
  *rshort = ra_getreg32(R_SDHI_SD_RSP10(priv->channel));
  return OK;
}

static int ra_sdhi_recvlong(struct sdio_dev_s *dev, uint32_t cmd,
                            uint32_t rlong[4])
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;

  /* R2 response is 128 bits. SDHI stores it in RSP76, RSP54, RSP32, RSP10 */
  /* NuttX expects rlong[0] to be bits 127-96, etc. */
  /* SDHI registers:
     RSP76: [127:96]
     RSP54: [95:64]
     RSP32: [63:32]
     RSP10: [31:0] (actually bits 31-8 are CRC/End, bit 0 is reserved?)
     Wait, FSP says:
     RSP76: 127-96
     RSP54: 95-64
     RSP32: 63-32
     RSP10: 31-0
  */

  rlong[0] = ra_getreg32(R_SDHI_SD_RSP76(priv->channel));
  rlong[1] = ra_getreg32(R_SDHI_SD_RSP54(priv->channel));
  rlong[2] = ra_getreg32(R_SDHI_SD_RSP32(priv->channel));
  rlong[3] = ra_getreg32(R_SDHI_SD_RSP10(priv->channel));

  return OK;
}

static int ra_sdhi_recvshort(struct sdio_dev_s *dev, uint32_t cmd,
                             uint32_t *rshort)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;
  *rshort = ra_getreg32(R_SDHI_SD_RSP10(priv->channel));
  return OK;
}

static void ra_sdhi_waitenable(struct sdio_dev_s *dev,
                               sdio_eventset_t eventset, uint32_t timeout)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;

  priv->waitevents = eventset;
  wd_start(&priv->waitwdog, timeout, ra_sdhi_eventtimeout, (wdparm_t)priv);
}

static sdio_eventset_t ra_sdhi_eventwait(struct sdio_dev_s *dev)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;
  int ret;

  ret = nxsem_wait_uninterruptible(&priv->waitsem);
  wd_cancel(&priv->waitwdog);

  if (ret < 0)
    {
      return SDIOWAIT_ERROR;
    }

  return priv->wkupevent;
}

static void ra_sdhi_callbackenable(struct sdio_dev_s *dev,
                                   sdio_eventset_t eventset)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;

  priv->cbevents = eventset;
  ra_sdhi_callback(priv);
}

static int ra_sdhi_registercallback(struct sdio_dev_s *dev,
                                    worker_t callback, void *arg)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;

  priv->callback = callback;
  priv->cbarg = arg;
  return OK;
}

static void ra_sdhi_callback(void *arg)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)arg;

  if (priv->callback)
    {
      priv->callback(priv->cbarg);
    }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

struct sdio_dev_s *ra_sdhi_initialize(int channel)
{
  struct ra_sdhi_dev_s *priv;
  int ret;

  if (channel < 0 || channel > 1)
    {
      return NULL;
    }

  priv = &g_sdhidev[channel];
  memset(priv, 0, sizeof(struct ra_sdhi_dev_s));
  priv->channel = channel;

  /* Initialize bus width tracking */
  priv->bus_width = 1;      /* Start with 1-bit mode */
  priv->max_bus_width = 4;  /* SD cards support up to 4-bit */

  /* Initialize semaphore */
  nxsem_init(&priv->waitsem, 0, 0);

  /* Enable module clock */
  ra_mstp_start(RA_MSTP_SDHI);

  /* Initialize multi-block state */
  priv->multiblock = false;
  priv->blocksize = 512;
  priv->nblocks = 1;
  priv->autocmd12 = false;

  /* Initialize hardware following RA8 BSP sequence */
  ra_sdhi_reset(&priv->dev);

  /* Register interrupts with proper event routing and priority */
  /* Map channel to IRQs and configure IELSR event sources */
  if (channel == 0)
    {
      priv->elc_accs = RA_ELC_SDHIMMC0_ACCS;
      priv->elc_sdio = RA_ELC_SDHIMMC0_SDIO;
      priv->elc_card = RA_ELC_SDHIMMC0_CARD;
      priv->elc_dma  = RA_ELC_SDHIMMC0_DMA_REQ;
    }
  else
    {
      priv->elc_accs = RA_ELC_SDHIMMC1_ACCS;
      priv->elc_sdio = RA_ELC_SDHIMMC1_SDIO;
      priv->elc_card = RA_ELC_SDHIMMC1_CARD;
      priv->elc_dma  = RA_ELC_SDHIMMC1_DMA_REQ;
    }

  /* Configure interrupts with proper event routing and priority
   * Priority levels: 0 (highest) to 15 (lowest)
   * Storage operations typically use priority 3-5 for good responsiveness
   */
  const int sdhi_priority = 3;

  /* Configure access interrupt with proper event routing */
  ra_icu_set_event(priv->elc_accs, priv->elc_accs);
  ret = ra_icu_attach(priv->elc_accs, ra_sdhi_access_isr, priv, false);
  if (ret >= 0)
    {
      ra_icu_set_priority(ret, sdhi_priority);
      up_enable_irq(ret);
    }

  /* Configure card detect interrupt with proper event routing */
  ra_icu_set_event(priv->elc_card, priv->elc_card);
  ret = ra_icu_attach(priv->elc_card, ra_sdhi_card_isr, priv, false);
  if (ret >= 0)
    {
      ra_icu_set_priority(ret, sdhi_priority);
      up_enable_irq(ret);
    }

  /* SDIO and DMA IRQs configured but not enabled in PIO mode
   * They are available for future DMA implementation
   */
  ra_icu_set_event(priv->elc_sdio, priv->elc_sdio);
  ra_icu_set_event(priv->elc_dma, priv->elc_dma);
  /* These IRQs will be attached and prioritized when DMA mode is implemented */

#ifdef CONFIG_RA_DMAC
  /* Setup DMA if enabled */
  ret = ra_sdhi_dma_setup(priv);
  if (ret < 0)
    {
      mcerr("SDHI%d: Failed to setup DMA: %d\n", channel, ret);
      /* Continue without DMA */
      priv->dma_enabled = false;
    }
#endif

#ifdef CONFIG_PM
  /* Register power management callbacks */
  priv->pmcb.prepare = ra_sdhi_pm_prepare;
  priv->pmcb.notify = ra_sdhi_pm_notify;
  priv->suspended = false;

  ret = pm_register(&priv->pmcb);
  if (ret < 0)
    {
      mcerr("SDHI%d: Failed to register PM callbacks: %d\n", channel, ret);
      /* Continue without PM support */
    }
#endif

  /* Initialize error tracking */
  priv->error_retry = 0;
  priv->err_sts1 = 0;
  priv->err_sts2 = 0;

  /* Initialize dev structure */
  priv->dev.reset            = ra_sdhi_reset;
  priv->dev.capabilities     = ra_sdhi_capabilities;
  priv->dev.status           = ra_sdhi_status;
  priv->dev.widebus          = ra_sdhi_widebus;
  priv->dev.clock            = ra_sdhi_clock;
  priv->dev.attach           = ra_sdhi_attach;
  priv->dev.sendcmd          = ra_sdhi_sendcmd;

  priv->dev.recvsetup        = ra_sdhi_recvsetup;
  priv->dev.sendsetup        = ra_sdhi_sendsetup;
  priv->dev.cancel           = ra_sdhi_cancel;
  priv->dev.waitresponse     = ra_sdhi_waitresponse;
  priv->dev.recv_r1          = ra_sdhi_recvshortcrc;
  priv->dev.recv_r2          = ra_sdhi_recvlong;
  priv->dev.recv_r3          = ra_sdhi_recvshort;
  priv->dev.recv_r4          = ra_sdhi_recvshort;
  priv->dev.recv_r5          = ra_sdhi_recvshortcrc;
  priv->dev.recv_r6          = ra_sdhi_recvshortcrc;
  priv->dev.recv_r7          = ra_sdhi_recvshort;
  priv->dev.waitenable       = ra_sdhi_waitenable;
  priv->dev.eventwait        = ra_sdhi_eventwait;
  priv->dev.callbackenable   = ra_sdhi_callbackenable;
#if defined(CONFIG_SCHED_WORKQUEUE) && defined(CONFIG_SCHED_HPWORK)
  priv->dev.registercallback = ra_sdhi_registercallback;
#endif

  return &priv->dev;
}

void ra_sdhi_set_sdio_card_isr(struct sdio_dev_s *dev,
                               int (*func)(void *), void *arg)
{
  /* Not implemented */
}

void ra_sdhi_mediachange(struct sdio_dev_s *dev, bool inserted)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;
  priv->inserted = inserted;
  ra_sdhi_callback(priv);
}

bool ra_sdhi_wrprotect(struct sdio_dev_s *dev)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;
  uint32_t info1 = ra_getreg32(R_SDHI_SD_INFO1(priv->channel));
  bool wp = (info1 & R_SDHI_SD_INFO1_SDWPMON) != 0;

  if (priv->wp_inverted)
    {
      wp = !wp;
    }

  return wp;
}

#endif /* CONFIG_RA_SDHI */

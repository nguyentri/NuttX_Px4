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

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct ra_sdhi_dev_s
{
  struct sdio_dev_s  dev;             /* Standard, base SDIO interface */

  /* RA8-specific fields */
  int                channel;         /* SDHI channel number */

  /* Interrupts */
  int                irq_accs;
  int                irq_sdio;
  int                irq_card;
  int                irq_dma;

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
      if (info2 & R_SDHI_SD_INFO2_RSPTO)
        {
          events |= SDIOWAIT_TIMEOUT;
        }
      else
        {
          events |= SDIOWAIT_ERROR;
        }
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
      while ((ra_getreg32(R_SDHI_SD_INFO2(priv->channel)) & R_SDHI_SD_INFO2_BRE) &&
             priv->remaining > 0)
        {
          *priv->buffer++ = ra_getreg32(R_SDHI_SD_BUF0(priv->channel));
          priv->remaining -= 4;
        }

      /* Clear BRE */
      ra_putreg32(info2 & ~R_SDHI_SD_INFO2_BRE, R_SDHI_SD_INFO2(priv->channel));
    }

  if (info2 & R_SDHI_SD_INFO2_BWE)
    {
      /* Buffer Write Enable - PIO Write */
      while ((ra_getreg32(R_SDHI_SD_INFO2(priv->channel)) & R_SDHI_SD_INFO2_BWE) &&
             priv->remaining > 0)
        {
          ra_putreg32(*priv->buffer++, R_SDHI_SD_BUF0(priv->channel));
          priv->remaining -= 4;
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
{
  /* Not implemented yet */
  return OK;
}

static int ra_sdhi_dma_req_isr(int irq, void *context, void *arg)
{
  /* Not implemented yet */
  return OK;
}

/* SDIO Interface Methods */

static void ra_sdhi_reset(struct sdio_dev_s *dev)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;

  /* Soft reset */
  ra_putreg32(0, R_SDHI_SOFT_RST(priv->channel));
  ra_putreg32(R_SDHI_SOFT_RST_SDRST, R_SDHI_SOFT_RST(priv->channel));

  /* Wait for reset to complete (SDRST clears to 0) */
  while (ra_getreg32(R_SDHI_SOFT_RST(priv->channel)) & R_SDHI_SOFT_RST_SDRST)
    {
    }

  /* Set default options */
  ra_putreg32(0x40E0, R_SDHI_SD_OPTION(priv->channel));

  /* Clear interrupts */
  ra_putreg32(0, R_SDHI_SD_INFO1(priv->channel));
  ra_putreg32(0, R_SDHI_SD_INFO2(priv->channel));

  ra_sdhi_disableints(priv);
}

static sdio_capset_t ra_sdhi_capabilities(FAR struct sdio_dev_s *dev)
{
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
  if (enable)
    {
      /* 4-bit width */
      option &= ~R_SDHI_SD_OPTION_WIDTH8;
      option &= ~R_SDHI_SD_OPTION_WIDTH; /* 0 = 4-bit if WIDTH8 is 0? No, check manual */
      /* FSP: 1-bit = 1 (WIDTH=1, WIDTH8=0), 4-bit = 0 (WIDTH=0, WIDTH8=0), 8-bit = (WIDTH=0, WIDTH8=1) */
      /* Wait, FSP says:
         SDHI_PRV_SD_OPTION_WIDTH8_BIT = 13
         SDHI_PRV_BUS_WIDTH_1_BIT = 4

         If 1-bit: Set WIDTH (bit 15) to 1.
         If 4-bit: Set WIDTH (bit 15) to 0.
         If 8-bit: Set WIDTH8 (bit 13) to 1.
      */
      option &= ~R_SDHI_SD_OPTION_WIDTH;
      option &= ~R_SDHI_SD_OPTION_WIDTH8;
    }
  else
    {
      /* 1-bit width */
      option |= R_SDHI_SD_OPTION_WIDTH;
      option &= ~R_SDHI_SD_OPTION_WIDTH8;
    }
  ra_putreg32(option, R_SDHI_SD_OPTION(priv->channel));

  /* Wait for bus width change? FSP has a delay. */
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

  /* Wait for CBSY to be 0 */
  while (ra_getreg32(R_SDHI_SD_INFO2(priv->channel)) & R_SDHI_SD_INFO2_CBSY)
    {
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

  /* Data transfer */
  if (cmd & MMCSD_DATAXFR_MASK)
    {
      cmd_reg |= R_SDHI_SD_CMD_CMDTP; /* Data transfer */

      if (cmd & MMCSD_WRXFR)
        {
          /* Write */
        }
      else
        {
          cmd_reg |= R_SDHI_SD_CMD_CMDRW; /* Read */
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
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;

  ra_putreg32(blocklen, R_SDHI_SD_SIZE(priv->channel));

  if (nblocks > 1)
    {
      ra_putreg32(nblocks, R_SDHI_SD_SECCNT(priv->channel));
      /* Enable block count in SD_STOP */
      ra_putreg32(R_SDHI_SD_STOP_SEC, R_SDHI_SD_STOP(priv->channel));
    }
  else
    {
      ra_putreg32(R_SDHI_SD_STOP_SEC, R_SDHI_SD_STOP(priv->channel)); /* Still set SEC? FSP says yes for single block too? No, usually 0. */
      /* FSP: R_SDHI_SD_STOP_SEC is set at multiple block transfer. */
      ra_putreg32(0, R_SDHI_SD_STOP(priv->channel));
    }
}

static int ra_sdhi_recvsetup(struct sdio_dev_s *dev, uint8_t *buffer,
                             size_t nbytes)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;

  priv->buffer = (uint32_t*)buffer;
  priv->remaining = nbytes;

  /* Enable BRE interrupt for PIO */
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

  /* Enable BWE interrupt for PIO */
  ra_sdhi_configwaitints(priv, RA_SDHI_INFO1_ACCESS_INTS, RA_SDHI_INFO2_ERR_INTS | R_SDHI_SD_INFO2_BWE,
                         SDIOWAIT_TRANSFERDONE | SDIOWAIT_TIMEOUT | SDIOWAIT_ERROR);

  return OK;
}

static int ra_sdhi_cancel(struct sdio_dev_s *dev)
{
  struct ra_sdhi_dev_s *priv = (struct ra_sdhi_dev_s *)dev;

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

  if (channel < 0 || channel > 1)
    {
      return NULL;
    }

  priv = &g_sdhidev[channel];
  priv->channel = channel;

  /* Initialize semaphore */
  nxsem_init(&priv->waitsem, 0, 0);

  /* Enable module clock */
  ra_mstp_start(RA_MSTP_SDHI);

  /* Initialize hardware */
  ra_sdhi_reset(&priv->dev);

  /* Register interrupts */
  /* Map channel to IRQs */
  if (channel == 0)
    {
      priv->irq_accs = RA_ELC_SDHIMMC0_ACCS;
      priv->irq_sdio = RA_ELC_SDHIMMC0_SDIO;
      priv->irq_card = RA_ELC_SDHIMMC0_CARD;
      priv->irq_dma  = RA_ELC_SDHIMMC0_DMA_REQ;
    }
  else
    {
      priv->irq_accs = RA_ELC_SDHIMMC1_ACCS;
      priv->irq_sdio = RA_ELC_SDHIMMC1_SDIO;
      priv->irq_card = RA_ELC_SDHIMMC1_CARD;
      priv->irq_dma  = RA_ELC_SDHIMMC1_DMA_REQ;
    }

  ra_icu_attach(priv->irq_accs, ra_sdhi_access_isr, priv, true);
  ra_icu_attach(priv->irq_card, ra_sdhi_card_isr, priv, true);
  /* SDIO and DMA IRQs not used in PIO mode yet */

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

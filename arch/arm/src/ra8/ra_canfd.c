/****************************************************************************
 * arch/arm/src/ra8/ra_canfd.c
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

#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/can/can.h>

#include "arm_internal.h"
#include "chip.h"
#include "ra_icu.h"
#include "ra_canfd.h"
#include "ra_mstp.h"
#include "hardware/ra8p1/ra_canfd.h"

#ifdef CONFIG_RA_CANFD

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Register Access Macros */
#define ra_getreg32(a)      getreg32(a)
#define ra_putreg32(v,a)    putreg32(v,a)

/* TX Message Buffer Count per channel */
#define RA_CANFD_TX_MB_COUNT    4

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct ra_canfd_s
{
  struct can_dev_s dev;           /* NuttX CAN device */
  const struct ra_canfd_config_s *config; /* Configuration */
  uint8_t  channel;               /* Channel number */
  uint32_t base;                  /* Base address */
  int      tx_irq;                /* TX interrupt IRQ */
  int      rx_fifo_irq;           /* RX FIFO interrupt IRQ */
  int      error_irq;             /* Error interrupt IRQ */
  int      global_err_irq;        /* Global error interrupt IRQ */
  bool     initialized;           /* Driver initialized */
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static void ra_canfd_reset(struct can_dev_s *dev);
static int  ra_canfd_setup(struct can_dev_s *dev);
static void ra_canfd_shutdown(struct can_dev_s *dev);
static void ra_canfd_rxint(struct can_dev_s *dev, bool enable);
static void ra_canfd_txint(struct can_dev_s *dev, bool enable);
static int  ra_canfd_ioctl(struct can_dev_s *dev, int cmd, unsigned long arg);
static int  ra_canfd_remoterequest(struct can_dev_s *dev, uint16_t id);
static int  ra_canfd_send(struct can_dev_s *dev, struct can_msg_s *msg);
static bool ra_canfd_txready(struct can_dev_s *dev);
static bool ra_canfd_txempty(struct can_dev_s *dev);

static int  ra_canfd_tx_interrupt(int irq, void *context, void *arg);
static int  ra_canfd_rx_fifo_interrupt(int irq, void *context, void *arg);
static int  ra_canfd_error_interrupt(int irq, void *context, void *arg);
static int  ra_canfd_global_error_interrupt(int irq, void *context, void *arg);

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct can_ops_s g_ra_canfd_ops =
{
  .co_reset         = ra_canfd_reset,
  .co_setup         = ra_canfd_setup,
  .co_shutdown      = ra_canfd_shutdown,
  .co_rxint         = ra_canfd_rxint,
  .co_txint         = ra_canfd_txint,
  .co_ioctl         = ra_canfd_ioctl,
  .co_remoterequest = ra_canfd_remoterequest,
  .co_send          = ra_canfd_send,
  .co_txready       = ra_canfd_txready,
  .co_txempty       = ra_canfd_txempty,
};

#ifdef CONFIG_RA_CANFD0
static const struct ra_canfd_config_s g_ra_canfd0_config =
{
  .base                 = R_CANFD_BASE,
  .channel              = 0,
  .tx_irq_event         = RA_ELC_CAN0_TX,
  .rx_fifo_irq_event    = RA_ELC_CAN_RXF, /* Shared global RX FIFO */
  .error_irq_event      = RA_ELC_CAN0_CHERR,
  .global_err_irq_event = RA_ELC_CAN_GLERR,
  .bitrate              = 500000,
  .dbitrate             = 2000000,
};

static struct ra_canfd_s g_ra_canfd0_priv =
{
  .dev    = { .cd_ops = &g_ra_canfd_ops, .cd_priv = &g_ra_canfd0_priv },
  .config = &g_ra_canfd0_config,
  .base   = R_CANFD_BASE,
  .channel = 0,
};
#endif

#ifdef CONFIG_RA_CANFD1
static const struct ra_canfd_config_s g_ra_canfd1_config =
{
  .base                 = R_CANFD_BASE,
  .channel              = 1,
  .tx_irq_event         = RA_ELC_CAN1_TX,
  .rx_fifo_irq_event    = RA_ELC_CAN_RXF, /* Shared global RX FIFO */
  .error_irq_event      = RA_ELC_CAN1_CHERR,
  .global_err_irq_event = RA_ELC_CAN_GLERR,
  .bitrate              = 500000,
  .dbitrate             = 2000000,
};

static struct ra_canfd_s g_ra_canfd1_priv =
{
  .dev    = { .cd_ops = &g_ra_canfd_ops, .cd_priv = &g_ra_canfd1_priv },
  .config = &g_ra_canfd1_config,
  .base   = R_CANFD_BASE,
  .channel = 1,
};
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static void ra_canfd_reset(struct can_dev_s *dev)
{
  struct ra_canfd_s *priv = (struct ra_canfd_s *)dev->cd_priv;
  uint8_t ch = priv->channel;

  /* Transition to Reset Mode */
  uint32_t ctr = ra_getreg32(R_CANFD_CFDC(ch) + 0x04);
  ctr &= ~R_CANFD_CFDGCTR_GMDC_MASK;
  ctr |= R_CANFD_CFDGCTR_GMDC_01; /* Channel Reset */
  ra_putreg32(ctr, R_CANFD_CFDC(ch) + 0x04);

  /* Wait for reset mode */
  while ((ra_getreg32(R_CANFD_CFDC(ch) + 0x08) & (1 << 0)) == 0);
}

static int ra_canfd_setup(struct can_dev_s *dev)
{
  struct ra_canfd_s *priv = (struct ra_canfd_s *)dev->cd_priv;
  uint8_t ch = priv->channel;

  if (priv->initialized)
    {
      return OK;
    }

  /* Attach Interrupts */
  priv->tx_irq = ra_icu_attach(priv->config->tx_irq_event, ra_canfd_tx_interrupt, priv, true);
  priv->rx_fifo_irq = ra_icu_attach(priv->config->rx_fifo_irq_event, ra_canfd_rx_fifo_interrupt, priv, true);
  priv->error_irq = ra_icu_attach(priv->config->error_irq_event, ra_canfd_error_interrupt, priv, true);
  priv->global_err_irq = ra_icu_attach(priv->config->global_err_irq_event, ra_canfd_global_error_interrupt, priv, true);

  /* Enable Interrupts in CANFD peripheral */
  /* Enable RX FIFO Interrupt */
  uint32_t rfcc = ra_getreg32(R_CANFD_CFDRFCC(0, ch)); /* Use FIFO ch for RX */
  rfcc |= R_CANFD_CFDRFCC_RFIE;
  ra_putreg32(rfcc, R_CANFD_CFDRFCC(0, ch));

  /* Enable TX Interrupts for MBs */
  /* We use MBs ch*4 to ch*4+3 */
  int start_mb = ch * RA_CANFD_TX_MB_COUNT;
  int end_mb = start_mb + RA_CANFD_TX_MB_COUNT;
  int i;
  uint32_t tmiec = ra_getreg32(R_CANFD_CFDTMIEC(0));
  for (i = start_mb; i < end_mb; i++)
    {
      tmiec |= (1 << i);  /* Enable interrupt for this MB */
    }
  ra_putreg32(tmiec, R_CANFD_CFDTMIEC(0));

  /* Configure Bit Timing */
  /* TODO: Calculate these values based on PCLK/CANCLK and requested bitrate */
  /* For now, we assume some defaults or leave them as reset values if they are safe */
  /* But we must set them to something valid for communication to work */

  /* Example for 500kbps Nominal, 2Mbps Data with 40MHz clock */
  /* NCFG: NBRP=0, NSJW=3, NTSEG1=63, NTSEG2=15 -> 80 Tq per bit? 40MHz/80 = 500kHz */
  uint32_t ncfg = (0 << 24) | (3 << 16) | (63 << 8) | (15 << 0); /* NBRP, NSJW, NTSEG1, NTSEG2 */
  ra_putreg32(ncfg, R_CANFD_CFDC(ch));

  /* DCFG: DBRP=0, DSJW=3, DTSEG1=15, DTSEG2=3 -> 20 Tq per bit? 40MHz/20 = 2MHz */
  uint32_t dcfg = (0 << 24) | (3 << 16) | (15 << 8) | (3 << 0);  /* DBRP, DSJW, DTSEG1, DTSEG2 */
  ra_putreg32(dcfg, R_CANFD_CFDC2(ch));

  /* Enable FD Mode in FDCFG */
  /* FDCFG: FDOE=1 (Bit 28) */
  uint32_t fdcfg = (1 << 28);
  ra_putreg32(fdcfg, R_CANFD_CFDC2(ch) + 0x04);

  /* Transition to Operation Mode */
  uint32_t ctr = ra_getreg32(R_CANFD_CFDC(ch) + 0x04);
  ctr &= ~0x3; /* Communication Mode */
  ra_putreg32(ctr, R_CANFD_CFDC(ch) + 0x04);

  /* Wait for operation mode */
  while ((ra_getreg32(R_CANFD_CFDC(ch) + 0x08) & 0x7) != 0)
    {
    }

  priv->initialized = true;
  return OK;
}static void ra_canfd_shutdown(struct can_dev_s *dev)
{
  struct ra_canfd_s *priv = (struct ra_canfd_s *)dev->cd_priv;

  ra_canfd_reset(dev);

  /* Detach Interrupts */
  ra_icu_detach(priv->tx_irq);
  ra_icu_detach(priv->rx_fifo_irq);
  ra_icu_detach(priv->error_irq);
  ra_icu_detach(priv->global_err_irq);

  priv->initialized = false;
}

static void ra_canfd_rxint(struct can_dev_s *dev, bool enable)
{
  struct ra_canfd_s *priv = (struct ra_canfd_s *)dev->cd_priv;
  /* Enable/Disable RX interrupts */
  /* This usually involves enabling/disabling the interrupt in the NVIC or the peripheral */
  if (enable)
    {
      up_enable_irq(priv->rx_fifo_irq);
    }
  else
    {
      up_disable_irq(priv->rx_fifo_irq);
    }
}

static void ra_canfd_txint(struct can_dev_s *dev, bool enable)
{
  struct ra_canfd_s *priv = (struct ra_canfd_s *)dev->cd_priv;
  if (enable)
    {
      up_enable_irq(priv->tx_irq);
    }
  else
    {
      up_disable_irq(priv->tx_irq);
    }
}

static int ra_canfd_ioctl(struct can_dev_s *dev, int cmd, unsigned long arg)
{
  /* Handle IOCTL commands */
  return -ENOTTY;
}

static int ra_canfd_remoterequest(struct can_dev_s *dev, uint16_t id)
{
  return 0;
}

static int ra_canfd_send(struct can_dev_s *dev, struct can_msg_s *msg)
{
  struct ra_canfd_s *priv = (struct ra_canfd_s *)dev->cd_priv;
  uint8_t ch = priv->channel;
  int start_mb = ch * RA_CANFD_TX_MB_COUNT;
  int end_mb = start_mb + RA_CANFD_TX_MB_COUNT;
  int mb = -1;
  int i;

  /* Find an available TX Message Buffer */
  for (i = start_mb; i < end_mb; i++)
    {
      uint32_t tmsts = ra_getreg32(R_CANFD_CFDTMSTS(0, i));
      if ((tmsts & R_CANFD_CFDTMSTS_TMTRM) == 0)
        {
          mb = i;
          break;
        }
    }

  if (mb < 0)
    {
      return -EBUSY;  /* All buffers are busy */
    }

  /* Build ID register */
  uint32_t id_reg = msg->cm_hdr.ch_id & (msg->cm_hdr.ch_extid ? 0x1FFFFFFF : 0x7FF);
  id_reg |= (msg->cm_hdr.ch_rtr ? R_CANFD_CFDTM_ID_TMRTR : 0);
  id_reg |= (msg->cm_hdr.ch_extid ? R_CANFD_CFDTM_ID_TMIDE : 0);

  /* Write ID */
  ra_putreg32(id_reg, R_CANFD_CFDTM(0, mb));

  /* Write DLC in PTR register */
  uint32_t ptr_reg = (msg->cm_hdr.ch_dlc << R_CANFD_CFDTM_PTR_TMDLC);
  ra_putreg32(ptr_reg, R_CANFD_CFDTM(0, mb) + 0x04);

  /* Write data bytes */
  uint8_t *src = msg->cm_data;
  uint32_t *dest = (uint32_t *)(R_CANFD_CFDTM(0, mb) + 0x0C);
  int bytes = msg->cm_hdr.ch_dlc;

  /* Copy data in 32-bit chunks */
  for (i = 0; i < (bytes + 3) / 4; i++)
    {
      uint32_t word = 0;
      int j;
      for (j = 0; j < 4 && (i * 4 + j) < bytes; j++)
        {
          word |= ((uint32_t)src[i * 4 + j]) << (j * 8);
        }
      dest[i] = word;
    }

  /* Request transmission */
  ra_putreg32(R_CANFD_CFDTMC_TMTR, R_CANFD_CFDTMC(0, mb));

  return OK;
}

static bool ra_canfd_txready(struct can_dev_s *dev)
{
  struct ra_canfd_s *priv = (struct ra_canfd_s *)dev->cd_priv;
  uint8_t ch = priv->channel;
  int start_mb = ch * RA_CANFD_TX_MB_COUNT;
  int end_mb = start_mb + RA_CANFD_TX_MB_COUNT;
  int i;

  /* Check if at least one TX buffer is free */
  for (i = start_mb; i < end_mb; i++)
    {
      uint32_t tmsts = ra_getreg32(R_CANFD_CFDTMSTS(0, i));
      if ((tmsts & R_CANFD_CFDTMSTS_TMTRM) == 0)
        {
          return true;  /* Found a free buffer */
        }
    }

  return false;  /* All buffers are busy */
}

static bool ra_canfd_txempty(struct can_dev_s *dev)
{
  struct ra_canfd_s *priv = (struct ra_canfd_s *)dev->cd_priv;
  uint8_t ch = priv->channel;
  int start_mb = ch * RA_CANFD_TX_MB_COUNT;
  int end_mb = start_mb + RA_CANFD_TX_MB_COUNT;
  int i;

  /* Check if all TX buffers are free */
  for (i = start_mb; i < end_mb; i++)
    {
      uint32_t tmsts = ra_getreg32(R_CANFD_CFDTMSTS(0, i));
      if ((tmsts & R_CANFD_CFDTMSTS_TMTRM) != 0)
        {
          return false;  /* Found a busy buffer */
        }
    }

  return true;  /* All buffers are free */
}

static int ra_canfd_tx_interrupt(int irq, void *context, void *arg)
{
  struct ra_canfd_s *priv = (struct ra_canfd_s *)arg;
  uint8_t ch = priv->channel;
  int start_mb = ch * RA_CANFD_TX_MB_COUNT;
  int end_mb = start_mb + RA_CANFD_TX_MB_COUNT;
  uint32_t tmtcsts;
  int i;

  /* Get transmission completion status */
  tmtcsts = ra_getreg32(R_CANFD_CFDTMTCSTS(0));

  /* Check which MB completed transmission */
  for (i = start_mb; i < end_mb; i++)
    {
      if (tmtcsts & (1 << i))
        {
          /* Clear the completion flag */
          uint32_t clear_mask = ~(1 << i);
          ra_putreg32(clear_mask, R_CANFD_CFDTMTCSTS(0));

          /* Notify upper layer */
          can_txdone(&priv->dev);
          break;
        }
    }

  return OK;
}

static int ra_canfd_rx_fifo_interrupt(int irq, void *context, void *arg)
{
  struct ra_canfd_s *priv = (struct ra_canfd_s *)arg;
  uint8_t ch = priv->channel;
  uint32_t rfsts;
  struct can_hdr_s hdr;
  uint8_t data[CAN_MAXDATALEN];

  /* Check RX FIFO status */
  rfsts = ra_getreg32(R_CANFD_CFDRFSTS(0, ch));

  /* Process all messages in the FIFO */
  while ((rfsts & R_CANFD_CFDRFSTS_RFEMP) == 0)
    {
      /* Read ID register */
      uint32_t id_reg = ra_getreg32(R_CANFD_CFDRF(0, ch));

      /* Extract ID and flags */
      hdr.ch_extid = (id_reg & R_CANFD_CFDRM_ID_RMIDE) ? 1 : 0;
      hdr.ch_rtr = (id_reg & R_CANFD_CFDRM_ID_RMRTR) ? 1 : 0;
      hdr.ch_id = (id_reg & R_CANFD_CFDRM_ID_RMID_MASK) >> R_CANFD_CFDRM_ID_RMID;

      /* Read PTR register for DLC */
      uint32_t ptr_reg = ra_getreg32(R_CANFD_CFDRF(0, ch) + 0x04);
      hdr.ch_dlc = (ptr_reg & R_CANFD_CFDRM_PTR_RMDLC_MASK) >> R_CANFD_CFDRM_PTR_RMDLC;

      /* Limit DLC to 8 for classic CAN */
      if (hdr.ch_dlc > 8)
        {
          hdr.ch_dlc = 8;
        }

      /* Read data bytes */
      uint32_t *src = (uint32_t *)(R_CANFD_CFDRF(0, ch) + 0x0C);
      int i;
      for (i = 0; i < (hdr.ch_dlc + 3) / 4; i++)
        {
          uint32_t word = src[i];
          int j;
          for (j = 0; j < 4 && (i * 4 + j) < hdr.ch_dlc; j++)
            {
              data[i * 4 + j] = (word >> (j * 8)) & 0xFF;
            }
        }

      /* Increment FIFO pointer to release the buffer */
      ra_putreg32(0xFF, R_CANFD_CFDRFPCTR(0, ch));

      /* Pass the received frame to the upper layer */
      can_receive(&priv->dev, &hdr, data);

      /* Re-check FIFO status */
      rfsts = ra_getreg32(R_CANFD_CFDRFSTS(0, ch));
    }

  return OK;
}

static int ra_canfd_error_interrupt(int irq, void *context, void *arg)
{
  struct ra_canfd_s *priv = (struct ra_canfd_s *)arg;
  uint8_t ch = priv->channel;
  uint32_t erfl;

  /* Read error flags */
  erfl = ra_getreg32(R_CANFD_CFDC(ch) + 0x0C);  /* CFDCERFL */

  /* Log errors */
  if (erfl != 0)
    {
      canerr("Channel %d error flags: 0x%08" PRIx32 "\n", ch, erfl);

      /* Clear error flags by writing 0 */
      ra_putreg32(0, R_CANFD_CFDC(ch) + 0x0C);
    }

  return OK;
}

static int ra_canfd_global_error_interrupt(int irq, void *context, void *arg)
{
  uint32_t gerfl;

  /* Read global error flags */
  gerfl = ra_getreg32(R_CANFD_CFDGERFL(0));

  if (gerfl != 0)
    {
      canerr("Global error flags: 0x%08" PRIx32 "\n", gerfl);

      /* Clear global error flags */
      ra_putreg32(0, R_CANFD_CFDGERFL(0));
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int ra_canfd_initialize(int channel)
{
  static bool global_initialized = false;
  if (channel == 0)
    {
#ifdef CONFIG_RA_CANFD0
        ra_mstp_start(RA_MSTP_CANFD0);
#else
      return -ENODEV;
#endif
    }
  else if (channel == 1)
    {
#ifdef CONFIG_RA_CANFD1
        ra_mstp_start(RA_MSTP_CANFD1);
#else
      return -ENODEV;
#endif
    }
  else
    {
      return -EINVAL;
    }

  /* Perform global CANFD initialization (only once) */
  if (!global_initialized)
    {
      /* Transition to Global Reset mode */
      uint32_t gctr = ra_getreg32(R_CANFD_CFDGCTR(0));
      gctr &= ~R_CANFD_CFDGCTR_GMDC_MASK;
      gctr |= R_CANFD_CFDGCTR_GMDC_01;  /* Global Reset */
      ra_putreg32(gctr, R_CANFD_CFDGCTR(0));

      /* Wait for Global Reset mode */
      while ((ra_getreg32(R_CANFD_CFDGSTS(0)) & R_CANFD_CFDGSTS_GRSTSTS) == 0);

      /* Configure global settings */
      uint32_t gcfg = 0;
      gcfg |= (1 << R_CANFD_CFDGCFG_TPRI);  /* ID priority transmission */
      gcfg |= (1 << R_CANFD_CFDGCFG_DCE);   /* DLC check enable */
      gcfg |= (1 << R_CANFD_CFDGCFG_DRE);   /* DLC replacement enable */
      gcfg |= (0 << R_CANFD_CFDGCFG_TSP_SHIFT);   /* Timestamp prescaler /1 */
      ra_putreg32(gcfg, R_CANFD_CFDGCFG(0));

      /* Configure RX FIFOs */
      for (int i = 0; i < 2; i++)
        {
          uint32_t rfcc = 0;
          rfcc |= R_CANFD_CFDRFCC_RFE;  /* Enable FIFO */
          rfcc |= (R_CANFD_CFDRFCC_RFDC_011 << R_CANFD_CFDRFCC_RFDC_SHIFT);  /* Depth = 16 */
          rfcc |= (R_CANFD_CFDRFCC_RFPLS_000 << R_CANFD_CFDRFCC_RFPLS_SHIFT);  /* 8 bytes */
          ra_putreg32(rfcc, R_CANFD_CFDRFCC(0, i));
        }

      /* Configure AFL (Acceptance Filter List) - accept all */
      ra_putreg32(1, R_CANFD_CFDGAFLECTR(0));  /* Enable AFL write */

      /* Rule 0: Accept all for channel 0 RX FIFO 0 */
      ra_putreg32(0, R_CANFD_CFDGAFL(0, 0));         /* ID = 0 */
      ra_putreg32(0, R_CANFD_CFDGAFL(0, 0) + 0x04);  /* Mask = 0 (don't care) */
      ra_putreg32(0x00000001, R_CANFD_CFDGAFL(0, 0) + 0x08);  /* Route to FIFO 0 */
      ra_putreg32(0, R_CANFD_CFDGAFL(0, 0) + 0x0C);

      /* Rule 1: Accept all for channel 1 RX FIFO 1 */
      ra_putreg32(0, R_CANFD_CFDGAFL(0, 1));
      ra_putreg32(0, R_CANFD_CFDGAFL(0, 1) + 0x04);
      ra_putreg32(0x00000002, R_CANFD_CFDGAFL(0, 1) + 0x08);  /* Route to FIFO 1 */
      ra_putreg32(0, R_CANFD_CFDGAFL(0, 1) + 0x0C);

      /* Configure AFL page 0 for 2 rules */
      ra_putreg32(0x00010001, R_CANFD_CFDGAFLCFG0(0));  /* 1 rule for ch0, 1 for ch1 */

      ra_putreg32(0, R_CANFD_CFDGAFLECTR(0));  /* Lock AFL */

      /* Transition to Global Operation mode */
      gctr = ra_getreg32(R_CANFD_CFDGCTR(0));
      gctr &= ~R_CANFD_CFDGCTR_GMDC_MASK;
      gctr |= R_CANFD_CFDGCTR_GMDC_00;  /* Global Operation */
      ra_putreg32(gctr, R_CANFD_CFDGCTR(0));

      /* Wait for Global Operation mode */
      while ((ra_getreg32(R_CANFD_CFDGSTS(0)) & (R_CANFD_CFDGSTS_GRSTSTS | R_CANFD_CFDGSTS_GHLTSTS)) != 0);

      global_initialized = true;
    }

  return OK;
}

int ra_canfd_register(const char *devpath, int channel)
{
  struct ra_canfd_s *priv;
  int ret;

  ret = ra_canfd_initialize(channel);
  if (ret < 0)
    {
      return ret;
    }

  if (channel == 0)
    {
#ifdef CONFIG_RA_CANFD0
      priv = &g_ra_canfd0_priv;
#else
      return -ENODEV;
#endif
    }
  else if (channel == 1)
    {
#ifdef CONFIG_RA_CANFD1
      priv = &g_ra_canfd1_priv;
#else
      return -ENODEV;
#endif
    }
  else
    {
      return -EINVAL;
    }

  ret = can_register(devpath, &priv->dev);
  if (ret < 0)
    {
      canerr("ERROR: can_register failed: %d\n", ret);
      return ret;
    }

  return OK;
}

#endif /* CONFIG_RA_CANFD */

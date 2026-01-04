/****************************************************************************
 * arch/arm/src/rzv/rzv_ether.c
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
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <debug.h>
#include <errno.h>

#include <arpa/inet.h>

#include <nuttx/wdog.h>
#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/spinlock.h>
#include <nuttx/wqueue.h>
#include <nuttx/signal.h>
#include <nuttx/net/mii.h>
#include <nuttx/net/arp.h>
#include <nuttx/net/phy.h>
#include <nuttx/net/netdev.h>

#ifdef CONFIG_NET_ARP
#  include <nuttx/net/arp.h>
#endif

#ifdef CONFIG_NET_PKT
#  include <nuttx/net/pkt.h>
#endif

#include "arm_internal.h"
#include "chip.h"
#include "rzv_icu.h"
#include "rzv_ether.h"
#include "rzv_ether_phy.h"
#include "hardware/rzv_ether.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* TODO: Verify these ELC event numbers */
#define RZV_ELC_GBETH0_INT  RZV_ELC_GBETH_PORT1_PTP_PPS_O_0
#define RZV_ELC_GBETH1_INT  RZV_ELC_GBETH_PORT0_PTP_PPS_O_0

#define RZV_ETHER_TX_TIMEOUT (2 * CLOCKS_PER_SEC)

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Common TX logic */

static int  rzv_transmit(struct rzv_eth_s *priv);
static int  rzv_txpoll(struct net_driver_s *dev);

/* Interrupt handling */

static void rzv_receive(struct rzv_eth_s *priv);
static void rzv_txdone(struct rzv_eth_s *priv);
static int  rzv_interrupt(int irq, void *context, void *arg);
static void rzv_work(void *arg);

/* Watchdog timer expirations */

static void rzv_txtimeout_work(void *arg);
static void rzv_txtimeout_expiry(wdparm_t arg);

/* NuttX callback functions */

static int  rzv_ifup(struct net_driver_s *dev);
static int  rzv_ifdown(struct net_driver_s *dev);
static int  rzv_txavail(struct net_driver_s *dev);
#ifdef CONFIG_NET_MCASTGROUP
static int  rzv_addmac(struct net_driver_s *dev, const uint8_t *mac);
static int  rzv_rmmac(struct net_driver_s *dev, const uint8_t *mac);
#endif
#ifdef CONFIG_NETDEV_IOCTL
static int  rzv_ioctl(struct net_driver_s *dev, int cmd, unsigned long arg);
#endif

/* PHY interface */

static int rzv_eth_phy_read(struct rzv_eth_s *priv, int phyaddr, int regaddr,
                            uint16_t *phyval);
static int rzv_eth_phy_write(struct rzv_eth_s *priv, int phyaddr, int regaddr,
                             uint16_t phyval);

/****************************************************************************
 * Private Data
 ****************************************************************************/

static struct rzv_eth_s g_rzv_eth[2];

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static int rzv_transmit(struct rzv_eth_s *priv)
{
  struct rzv_eth_desc_s *txdesc;
  uint32_t *txbuffer;
  unsigned int txhead;

  txhead = priv->txhead;
  txdesc = &priv->txdesc[txhead];

  if (txdesc->des3 & TDES3_OWN)
    {
      return -EBUSY;
    }

  /* Copy data to TX buffer */
  txbuffer = (uint32_t *)(priv->txbuffer + (txhead * RZV_ETHER_BUFSIZE));
  memcpy(txbuffer, priv->dev.d_buf, priv->dev.d_len);

  /* Setup descriptor */
  txdesc->des0 = (uint32_t)(uintptr_t)txbuffer;
  txdesc->des1 = 0;
  txdesc->des2 = (priv->dev.d_len & TDES2_B1L_MASK) | TDES2_IOC | TDES2_TTSE;
  txdesc->des3 = TDES3_OWN | TDES3_FD | TDES3_LD;

  /* Update head */
  priv->txhead++;
  if (priv->txhead >= CONFIG_RZV_ETHER_TXDESC)
    {
      priv->txhead = 0;
    }

  /* Start transmission */
  putreg32(1, priv->base + RZV_ETH_DMA_CH0_TX_CTRL);

  /* Setup the TX timeout watchdog (perhaps restart the timer) */
  wd_start(&priv->txtimeout, RZV_ETHER_TX_TIMEOUT,
           rzv_txtimeout_expiry, (wdparm_t)priv);

  return OK;
}

static int rzv_txpoll(struct net_driver_s *dev)
{
  struct rzv_eth_s *priv = (struct rzv_eth_s *)dev->d_private;

  /* Send the packet */
  rzv_transmit(priv);

  /* If zero is returned, the polling will continue until all connections have
   * been examined.
   */

  return 0;
}

static void rzv_receive(struct rzv_eth_s *priv)
{
  struct rzv_eth_desc_s *rxdesc;
  unsigned int rxndx;

  rxndx = priv->rxndx;
  rxdesc = &priv->rxdesc[rxndx];

  while (!(rxdesc->des3 & RDES3_OWN))
    {
      /* Check for errors */
      if (rxdesc->des3 & (1 << 15)) /* Error summary */
        {
          nerr("RX Error: %08x\n", rxdesc->des3);
        }
      else
        {
          /* Copy data */
          priv->dev.d_len = (rxdesc->des3 & TDES3_FL_MASK) >> TDES3_FL_SHIFT;
          memcpy(priv->dev.d_buf,
                 (void *)(uintptr_t)rxdesc->des0,
                 priv->dev.d_len);

          /* Pass to network */
          ipv4_input(&priv->dev);
        }

      /* Return descriptor to DMA */
      rxdesc->des3 = RDES3_OWN | RDES3_IOC | RDES3_BUF1V;

      /* Update index */
      priv->rxndx++;
      if (priv->rxndx >= CONFIG_RZV_ETHER_RXDESC)
        {
          priv->rxndx = 0;
        }

      rxndx = priv->rxndx;
      rxdesc = &priv->rxdesc[rxndx];
    }
}

static void rzv_txdone(struct rzv_eth_s *priv)
{
  struct rzv_eth_desc_s *txdesc;
  unsigned int txtail;

  txtail = priv->txtail;
  txdesc = &priv->txdesc[txtail];

  while ((txdesc->des3 & TDES3_OWN) == 0 && txtail != priv->txhead)
    {
      /* Check for errors */
      if (txdesc->des3 & (1 << 15)) /* Error summary */
        {
          nerr("TX Error: %08x\n", txdesc->des3);
        }

      /* Update tail */
      priv->txtail++;
      if (priv->txtail >= CONFIG_RZV_ETHER_TXDESC)
        {
          priv->txtail = 0;
        }

      txtail = priv->txtail;
      txdesc = &priv->txdesc[txtail];
    }

  /* Cancel watchdog */
  wd_cancel(&priv->txtimeout);

  /* Poll for new TX data */
  devif_poll(&priv->dev, rzv_txpoll);
}

static int rzv_interrupt(int irq, void *context, void *arg)
{
  struct rzv_eth_s *priv = (struct rzv_eth_s *)arg;
  uint32_t status;

  /* Read status */
  status = getreg32(priv->base + RZV_ETH_DMA_CH0_STATUS);

  /* Clear status */
  putreg32(status, priv->base + RZV_ETH_DMA_CH0_STATUS);

  /* Schedule work */
  if (work_available(&priv->irqwork))
    {
      work_queue(HPWORK, &priv->irqwork, rzv_work, priv, 0);
    }

  return OK;
}

static void rzv_work(void *arg)
{
  struct rzv_eth_s *priv = (struct rzv_eth_s *)arg;

  /* Handle RX */
  rzv_receive(priv);

  /* Handle TX done */
  rzv_txdone(priv);

  /* Re-enable interrupts if needed */
}

static void rzv_txtimeout_work(void *arg)
{
  struct rzv_eth_s *priv = (struct rzv_eth_s *)arg;

  nerr("TX Timeout\n");

  /* Reset hardware or recover */
  UNUSED(priv);
}

static void rzv_txtimeout_expiry(wdparm_t arg)
{
  struct rzv_eth_s *priv = (struct rzv_eth_s *)arg;
  work_queue(HPWORK, &priv->txtimeout_work, rzv_txtimeout_work, priv, 0);
}

static int rzv_ifup(struct net_driver_s *dev)
{
  struct rzv_eth_s *priv = (struct rzv_eth_s *)dev->d_private;
  int ret;

  /* Enable interrupts */
  ret = rzv_icu_attach(priv->irq, rzv_interrupt, priv, true);
  if (ret < 0)
    {
      return ret;
    }

  /* Start DMA */
  putreg32(DMA_CH0_CTRL_SWR, priv->base + RZV_ETH_DMA_CH0_CTRL);
  /* Wait for reset */
  while (getreg32(priv->base + RZV_ETH_DMA_CH0_CTRL) & DMA_CH0_CTRL_SWR);

  /* Configure DMA */
  putreg32((uint32_t)(uintptr_t)priv->txdesc, priv->base + RZV_ETH_DMA_CH0_TXDESC_LIST);
  putreg32((uint32_t)(uintptr_t)priv->rxdesc, priv->base + RZV_ETH_DMA_CH0_RXDESC_LIST);
  putreg32(CONFIG_RZV_ETHER_TXDESC - 1, priv->base + RZV_ETH_DMA_CH0_TXDESC_RING);
  putreg32(CONFIG_RZV_ETHER_RXDESC - 1, priv->base + RZV_ETH_DMA_CH0_RXDESC_RING);

  /* Enable MAC */
  putreg32(MAC_CONF_RE | MAC_CONF_TE, priv->base + RZV_ETH_MAC_CONF);

  /* Enable DMA interrupts */
  putreg32(DMA_CH0_INT_EN_TIE | DMA_CH0_INT_EN_RIE | DMA_CH0_INT_EN_NISE | DMA_CH0_INT_EN_AISE,
           priv->base + RZV_ETH_DMA_CH0_INT_EN);

  /* Start TX/RX */
  putreg32(1, priv->base + RZV_ETH_DMA_CH0_TX_CTRL);
  putreg32(1, priv->base + RZV_ETH_DMA_CH0_RX_CTRL);

  priv->bifup = true;
  return OK;
}

static int rzv_ifdown(struct net_driver_s *dev)
{
  struct rzv_eth_s *priv = (struct rzv_eth_s *)dev->d_private;

  /* Disable interrupts */
  rzv_icu_detach(priv->irq);

  /* Stop DMA/MAC */
  putreg32(0, priv->base + RZV_ETH_MAC_CONF);
  putreg32(0, priv->base + RZV_ETH_DMA_CH0_TX_CTRL);
  putreg32(0, priv->base + RZV_ETH_DMA_CH0_RX_CTRL);

  priv->bifup = false;
  return OK;
}

static int rzv_txavail(struct net_driver_s *dev)
{
  struct rzv_eth_s *priv = (struct rzv_eth_s *)dev->d_private;

  if (priv->bifup)
    {
      devif_poll(&priv->dev, rzv_txpoll);
    }

  return OK;
}

#ifdef CONFIG_NET_MCASTGROUP
static int rzv_addmac(struct net_driver_s *dev, const uint8_t *mac)
{
  return OK;
}

static int rzv_rmmac(struct net_driver_s *dev, const uint8_t *mac)
{
  return OK;
}
#endif

#ifdef CONFIG_NETDEV_IOCTL
static int rzv_ioctl(struct net_driver_s *dev, int cmd, unsigned long arg)
{
  struct rzv_eth_s *priv = (struct rzv_eth_s *)dev->d_private;
  int ret = OK;

  switch (cmd)
    {
#ifdef CONFIG_NETDEV_PHY_IOCTL
      case SIOCGMIIPHY: /* Get PHY address */
        {
          struct mii_ioctl_data_s *req =
            (struct mii_ioctl_data_s *)arg;
          req->phy_id = CONFIG_RZV_ETHER_PHY_ADDR;
        }
        break;

      case SIOCGMIIREG: /* Get PHY register */
        {
          struct mii_ioctl_data_s *req =
            (struct mii_ioctl_data_s *)arg;
          ret = rzv_eth_phy_read(priv, req->phy_id, req->reg_num,
                                 &req->val_out);
        }
        break;

      case SIOCSMIIREG: /* Set PHY register */
        {
          struct mii_ioctl_data_s *req =
            (struct mii_ioctl_data_s *)arg;
          ret = rzv_eth_phy_write(priv, req->phy_id, req->reg_num,
                                  req->val_in);
        }
        break;
#endif /* CONFIG_NETDEV_PHY_IOCTL */

      default:
        ret = -ENOTTY;
        break;
    }

  return ret;
}
#endif

static int rzv_eth_phy_read(struct rzv_eth_s *priv, int phyaddr, int regaddr,
                            uint16_t *phyval)
{
  return rzv_phy_read(priv->base, phyaddr, regaddr, phyval);
}

static int rzv_eth_phy_write(struct rzv_eth_s *priv, int phyaddr, int regaddr,
                             uint16_t phyval)
{
  return rzv_phy_write(priv->base, phyaddr, regaddr, phyval);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int rzv_ether_initialize(int intf)
{
  struct rzv_eth_s *priv;

  if (intf < 0 || intf > 1)
    {
      return -EINVAL;
    }

  priv = &g_rzv_eth[intf];

  /* Initialize state */
  memset(priv, 0, sizeof(struct rzv_eth_s));
  priv->intf = intf;
  priv->base = (intf == 0) ? RZV_ETHER0_BASE : RZV_ETHER1_BASE;
  priv->irq = (intf == 0) ? RZV_ELC_GBETH0_INT : RZV_ELC_GBETH1_INT;

  /* Allocate descriptors and buffers */
  /* TODO: Allocate from non-cached memory or handle cache */
  priv->txdesc = (struct rzv_eth_desc_s *)kmm_zalloc(CONFIG_RZV_ETHER_TXDESC * sizeof(struct rzv_eth_desc_s));
  priv->rxdesc = (struct rzv_eth_desc_s *)kmm_zalloc(CONFIG_RZV_ETHER_RXDESC * sizeof(struct rzv_eth_desc_s));
  priv->txbuffer = (uint8_t *)kmm_zalloc(CONFIG_RZV_ETHER_TXDESC * RZV_ETHER_BUFSIZE);
  priv->rxbuffer = (uint8_t *)kmm_zalloc(CONFIG_RZV_ETHER_RXDESC * RZV_ETHER_BUFSIZE);

  /* Initialize net_driver_s */
  priv->dev.d_ifup = rzv_ifup;
  priv->dev.d_ifdown = rzv_ifdown;
  priv->dev.d_txavail = rzv_txavail;
#ifdef CONFIG_NET_MCASTGROUP
  priv->dev.d_addmac = rzv_addmac;
  priv->dev.d_rmmac = rzv_rmmac;
#endif
#ifdef CONFIG_NETDEV_IOCTL
  priv->dev.d_ioctl = rzv_ioctl;
#endif
  priv->dev.d_private = priv;

  /* Register the device */
  netdev_register(&priv->dev, NET_LL_ETHERNET);

  return OK;
}

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
#include <nuttx/cache.h>
#include <nuttx/kmalloc.h>
#include <nuttx/spinlock.h>
#include <nuttx/wqueue.h>
#include <nuttx/signal.h>
#include <nuttx/net/mii.h>
#include <nuttx/net/arp.h>
#include <nuttx/net/ethernet.h>
#include <nuttx/net/netconfig.h>
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

/* GBETH DMA status interrupt event IDs from the RZ/V2H reference IRQ list.
 * These are INTC event selectors, not PPS events.
 */

#define RZV_ELC_GBETH0_INT  765
#define RZV_ELC_GBETH1_INT  780

#define RZV_ETHER_TX_TIMEOUT (2 * CLOCKS_PER_SEC)
#define RZV_ETHER_PKTSIZE    (MAX_NETDEV_PKTSIZE + CONFIG_NET_GUARDSIZE)

#define BUF ((FAR struct eth_hdr_s *)priv->dev.d_buf)

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Common TX logic */

static int  rzv_transmit(struct rzv_eth_s *priv);
static int  rzv_txpoll(struct net_driver_s *dev);
static int  rzv_alloc_buffers(struct rzv_eth_s *priv);
static void rzv_init_descriptors(struct rzv_eth_s *priv);
static int  rzv_configure_link(struct rzv_eth_s *priv);
static void rzv_set_macaddr(struct rzv_eth_s *priv);
static void rzv_receive_dispatch(struct rzv_eth_s *priv);

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

static inline void rzv_clean_dcache_region(const void *addr, size_t len)
{
  uintptr_t start = (uintptr_t)addr;
  uintptr_t end = start + len;

  up_clean_dcache(start, end);
}

static inline void rzv_invalidate_dcache_region(const void *addr, size_t len)
{
  uintptr_t start = (uintptr_t)addr;
  uintptr_t end = start + len;

  up_invalidate_dcache(start, end);
}

static int rzv_alloc_buffers(struct rzv_eth_s *priv)
{
  size_t txdesc_size;
  size_t rxdesc_size;

  txdesc_size = CONFIG_RZV_ETHER_TXDESC * sizeof(struct rzv_eth_desc_s);
  rxdesc_size = CONFIG_RZV_ETHER_RXDESC * sizeof(struct rzv_eth_desc_s);

  priv->txdesc = kmm_memalign(RZV_ETHER_DMA_ALIGN, txdesc_size);
  priv->rxdesc = kmm_memalign(RZV_ETHER_DMA_ALIGN, rxdesc_size);
  priv->txbuffer = kmm_memalign(RZV_ETHER_DMA_ALIGN,
                                CONFIG_RZV_ETHER_TXDESC *
                                RZV_ETHER_BUFSIZE);
  priv->rxbuffer = kmm_memalign(RZV_ETHER_DMA_ALIGN,
                                CONFIG_RZV_ETHER_RXDESC *
                                RZV_ETHER_BUFSIZE);
  priv->pktbuf = kmm_memalign(RZV_ETHER_DMA_ALIGN, RZV_ETHER_PKTSIZE);

  if (priv->txdesc == NULL || priv->rxdesc == NULL ||
      priv->txbuffer == NULL || priv->rxbuffer == NULL ||
      priv->pktbuf == NULL)
    {
      nerr("ERROR: failed to allocate Ethernet DMA buffers\n");
      return -ENOMEM;
    }

  memset(priv->txdesc, 0, txdesc_size);
  memset(priv->rxdesc, 0, rxdesc_size);
  memset(priv->txbuffer, 0, CONFIG_RZV_ETHER_TXDESC * RZV_ETHER_BUFSIZE);
  memset(priv->rxbuffer, 0, CONFIG_RZV_ETHER_RXDESC * RZV_ETHER_BUFSIZE);
  memset(priv->pktbuf, 0, RZV_ETHER_PKTSIZE);

  priv->dev.d_buf = priv->pktbuf;
  return OK;
}

static void rzv_init_descriptors(struct rzv_eth_s *priv)
{
  struct rzv_eth_desc_s *desc;
  uint8_t *buffer;
  unsigned int i;

  memset(priv->txdesc, 0,
         CONFIG_RZV_ETHER_TXDESC * sizeof(struct rzv_eth_desc_s));
  memset(priv->rxdesc, 0,
         CONFIG_RZV_ETHER_RXDESC * sizeof(struct rzv_eth_desc_s));

  for (i = 0; i < CONFIG_RZV_ETHER_TXDESC; i++)
    {
      desc = &priv->txdesc[i];
      buffer = priv->txbuffer + (i * RZV_ETHER_BUFSIZE);

      desc->des0 = (uint32_t)(uintptr_t)buffer;
      desc->des1 = 0;
      desc->des2 = 0;
      desc->des3 = 0;
    }

  for (i = 0; i < CONFIG_RZV_ETHER_RXDESC; i++)
    {
      desc = &priv->rxdesc[i];
      buffer = priv->rxbuffer + (i * RZV_ETHER_BUFSIZE);

      desc->des0 = (uint32_t)(uintptr_t)buffer;
      desc->des1 = 0;
      desc->des2 = 0;
      desc->des3 = RDES3_OWN | RDES3_IOC | RDES3_BUF1V | RDES3_OSTC;

      rzv_invalidate_dcache_region(buffer, RZV_ETHER_BUFSIZE);
    }

  priv->txhead = 0;
  priv->txtail = 0;
  priv->txinflight = 0;
  priv->rxndx = 0;
  priv->intpending = 0;

  rzv_clean_dcache_region(priv->txdesc,
                          CONFIG_RZV_ETHER_TXDESC *
                          sizeof(struct rzv_eth_desc_s));
  rzv_clean_dcache_region(priv->rxdesc,
                          CONFIG_RZV_ETHER_RXDESC *
                          sizeof(struct rzv_eth_desc_s));
}

static void rzv_set_macaddr(struct rzv_eth_s *priv)
{
  uint8_t *mac = priv->dev.d_mac.ether.ether_addr_octet;
  uint32_t high;
  uint32_t low;

  if ((mac[0] | mac[1] | mac[2] | mac[3] | mac[4] | mac[5]) == 0)
    {
      mac[0] = 0x02;
      mac[1] = 0x52;
      mac[2] = 0x5a;
      mac[3] = 0x56;
      mac[4] = 0x20;
      mac[5] = 0x10 + priv->intf;
    }

  high = ((uint32_t)mac[5] << 8) | mac[4] | (1 << 31);
  low = ((uint32_t)mac[3] << 24) | ((uint32_t)mac[2] << 16) |
        ((uint32_t)mac[1] << 8) | mac[0];

  putreg32(high, priv->base + RZV_ETH_MAC_ADDR0_HI);
  putreg32(low, priv->base + RZV_ETH_MAC_ADDR0_LO);
}

static int rzv_configure_link(struct rzv_eth_s *priv)
{
  uint32_t macconf;
  uint8_t phyaddr;
  uint32_t phyid;
  int link;
  int ret;

  ret = rzv_phy_probe(priv->base, CONFIG_RZV_ETHER_PHY_ADDR, &phyaddr,
                      &phyid);
  if (ret < 0)
    {
      return ret;
    }

  priv->phy_addr = phyaddr;
  priv->phy_id = phyid;

  ret = rzv_phy_reset(priv->base, priv->phy_addr);
  if (ret < 0)
    {
      return ret;
    }

  link = rzv_phy_autonegotiate(priv->base, priv->phy_addr);
  if (link < 0)
    {
      return link;
    }

  priv->linkup = (link != PHY_LINK_DOWN);
  priv->duplex = false;
  priv->speed = 0;

  macconf = getreg32(priv->base + RZV_ETH_MAC_CONF);
  macconf &= ~(MAC_CONF_RE | MAC_CONF_TE | MAC_CONF_DM |
               MAC_CONF_FES | MAC_CONF_PS);

  switch (link)
    {
      case PHY_LINK_1000FD:
        priv->duplex = true;
        priv->speed = 1000;
        macconf |= MAC_CONF_DM;
        break;

      case PHY_LINK_100FD:
        priv->duplex = true;
        priv->speed = 100;
        macconf |= MAC_CONF_DM | MAC_CONF_FES | MAC_CONF_PS;
        break;

      case PHY_LINK_100HD:
        priv->speed = 100;
        macconf |= MAC_CONF_FES | MAC_CONF_PS;
        break;

      case PHY_LINK_10FD:
        priv->duplex = true;
        priv->speed = 10;
        macconf |= MAC_CONF_DM | MAC_CONF_PS;
        break;

      case PHY_LINK_10HD:
        priv->speed = 10;
        macconf |= MAC_CONF_PS;
        break;

      default:
        nwarn("WARNING: Ethernet link is down\n");
        putreg32(macconf, priv->base + RZV_ETH_MAC_CONF);
        return -ENETDOWN;
    }

  putreg32(macconf, priv->base + RZV_ETH_MAC_CONF);
  ninfo("GBETH%d link: phy=%d id=%08" PRIx32 " %dMbps %s-duplex\n",
        priv->intf, priv->phy_addr, priv->phy_id, priv->speed,
        priv->duplex ? "full" : "half");

  return OK;
}

static int rzv_transmit(struct rzv_eth_s *priv)
{
  struct rzv_eth_desc_s *txdesc;
  uint32_t *txbuffer;
  unsigned int txhead;

  txhead = priv->txhead;
  txdesc = &priv->txdesc[txhead];

  rzv_invalidate_dcache_region(txdesc, sizeof(*txdesc));
  if (priv->txinflight >= CONFIG_RZV_ETHER_TXDESC ||
      (txdesc->des3 & TDES3_OWN) != 0)
    {
      return -EBUSY;
    }

  /* Copy data to TX buffer */
  txbuffer = (uint32_t *)(priv->txbuffer + (txhead * RZV_ETHER_BUFSIZE));
  memcpy(txbuffer, priv->dev.d_buf, priv->dev.d_len);
  rzv_clean_dcache_region(txbuffer, priv->dev.d_len);

  /* Setup descriptor */

  txdesc->des0 = (uint32_t)(uintptr_t)txbuffer;
  txdesc->des1 = 0;
  txdesc->des2 = (priv->dev.d_len & TDES2_B1L_MASK) | TDES2_IOC | TDES2_TTSE;
  txdesc->des3 = (priv->dev.d_len << TDES3_FL_SHIFT) |
                 TDES3_OWN | TDES3_FD | TDES3_LD;
  rzv_clean_dcache_region(txdesc, sizeof(*txdesc));

  /* Update head */

  priv->txinflight++;
  priv->txhead++;
  if (priv->txhead >= CONFIG_RZV_ETHER_TXDESC)
    {
      priv->txhead = 0;
    }

  /* Tell DMA that one more descriptor is available and ensure TX runs. */

  putreg32((uint32_t)(uintptr_t)&priv->txdesc[priv->txhead],
           priv->base + RZV_ETH_DMA_CH0_TXDESC_TAIL);
  putreg32(getreg32(priv->base + RZV_ETH_DMA_CH0_TX_CTRL) |
           DMA_CH0_TX_CTRL_ST,
           priv->base + RZV_ETH_DMA_CH0_TX_CTRL);

  /* Setup the TX timeout watchdog (perhaps restart the timer) */
  wd_start(&priv->txtimeout, RZV_ETHER_TX_TIMEOUT,
           rzv_txtimeout_expiry, (wdparm_t)priv);

  return OK;
}

static int rzv_txpoll(struct net_driver_s *dev)
{
  struct rzv_eth_s *priv = (struct rzv_eth_s *)dev->d_private;
  int ret;

  /* Send the packet */

  ret = rzv_transmit(priv);
  if (ret == -EBUSY)
    {
      return 1;
    }

  /* If zero is returned, the polling will continue until all connections have
   * been examined.
   */

  return 0;
}

static void rzv_receive_dispatch(struct rzv_eth_s *priv)
{
#ifdef CONFIG_NET_PKT
  pkt_input(&priv->dev);
#endif

#ifdef CONFIG_NET_IPv4
  if (BUF->type == HTONS(ETHTYPE_IP))
    {
      NETDEV_RXIPV4(&priv->dev);
      arp_ipin(&priv->dev);
      ipv4_input(&priv->dev);

      if (priv->dev.d_len > 0)
        {
#ifdef CONFIG_NET_IPv6
          if (IFF_IS_IPv4(priv->dev.d_flags))
#endif
            {
              arp_out(&priv->dev);
            }
#ifdef CONFIG_NET_IPv6
          else
            {
              neighbor_out(&priv->dev);
            }
#endif

          rzv_transmit(priv);
        }
    }
  else
#endif
#ifdef CONFIG_NET_IPv6
  if (BUF->type == HTONS(ETHTYPE_IP6))
    {
      NETDEV_RXIPV6(&priv->dev);
      ipv6_input(&priv->dev);

      if (priv->dev.d_len > 0)
        {
#ifdef CONFIG_NET_IPv4
          if (IFF_IS_IPv4(priv->dev.d_flags))
            {
              arp_out(&priv->dev);
            }
          else
#endif
            {
              neighbor_out(&priv->dev);
            }

          rzv_transmit(priv);
        }
    }
  else
#endif
#ifdef CONFIG_NET_ARP
  if (BUF->type == HTONS(ETHTYPE_ARP))
    {
      NETDEV_RXARP(&priv->dev);
      arp_arpin(&priv->dev);

      if (priv->dev.d_len > 0)
        {
          rzv_transmit(priv);
        }
    }
  else
#endif
    {
      NETDEV_RXDROPPED(&priv->dev);
    }
}

static void rzv_receive(struct rzv_eth_s *priv)
{
  struct rzv_eth_desc_s *rxdesc;
  unsigned int rxndx;

  rxndx = priv->rxndx;
  rxdesc = &priv->rxdesc[rxndx];
  rzv_invalidate_dcache_region(rxdesc, sizeof(*rxdesc));

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

          priv->dev.d_len = (rxdesc->des3 & RDES3_FL_MASK) >>
                            RDES3_FL_SHIFT;
          if (priv->dev.d_len > RZV_ETHER_PKTSIZE)
            {
              nerr("RX length too large: %" PRIu16 "\n", priv->dev.d_len);
              NETDEV_RXDROPPED(&priv->dev);
            }
          else
            {
              rzv_invalidate_dcache_region((void *)(uintptr_t)rxdesc->des0,
                                            priv->dev.d_len);
              memcpy(priv->dev.d_buf,
                     (void *)(uintptr_t)rxdesc->des0,
                     priv->dev.d_len);

              /* Pass to network */

              rzv_receive_dispatch(priv);
            }
        }

      /* Return descriptor to DMA */

      rzv_invalidate_dcache_region((void *)(uintptr_t)rxdesc->des0,
                                    RZV_ETHER_BUFSIZE);
      rxdesc->des3 = RDES3_OWN | RDES3_IOC | RDES3_BUF1V | RDES3_OSTC;
      rzv_clean_dcache_region(rxdesc, sizeof(*rxdesc));

      /* Update index */

      priv->rxndx++;
      if (priv->rxndx >= CONFIG_RZV_ETHER_RXDESC)
        {
          priv->rxndx = 0;
        }

      if (priv->rxndx == CONFIG_RZV_ETHER_RXDESC - 1)
        {
          putreg32((uint32_t)(uintptr_t)&priv->rxdesc[0],
                   priv->base + RZV_ETH_DMA_CH0_RXDESC_TAIL);
        }
      else
        {
          putreg32((uint32_t)(uintptr_t)&priv->rxdesc[priv->rxndx + 1],
                   priv->base + RZV_ETH_DMA_CH0_RXDESC_TAIL);
        }

      putreg32(getreg32(priv->base + RZV_ETH_DMA_CH0_RX_CTRL) |
               DMA_CH0_RX_CTRL_SR,
               priv->base + RZV_ETH_DMA_CH0_RX_CTRL);

      rxndx = priv->rxndx;
      rxdesc = &priv->rxdesc[rxndx];
      rzv_invalidate_dcache_region(rxdesc, sizeof(*rxdesc));
    }
}

static void rzv_txdone(struct rzv_eth_s *priv)
{
  struct rzv_eth_desc_s *txdesc;
  unsigned int txtail;

  txtail = priv->txtail;
  txdesc = &priv->txdesc[txtail];
  rzv_invalidate_dcache_region(txdesc, sizeof(*txdesc));

  while ((txdesc->des3 & TDES3_OWN) == 0 && priv->txinflight > 0)
    {
      /* Check for errors */
      if (txdesc->des3 & (1 << 15)) /* Error summary */
        {
          nerr("TX Error: %08x\n", txdesc->des3);
        }

      /* Update tail */

      priv->txtail++;
      if (priv->txinflight > 0)
        {
          priv->txinflight--;
        }

      if (priv->txtail >= CONFIG_RZV_ETHER_TXDESC)
        {
          priv->txtail = 0;
        }

      txtail = priv->txtail;
      txdesc = &priv->txdesc[txtail];
      rzv_invalidate_dcache_region(txdesc, sizeof(*txdesc));
    }

  /* Cancel watchdog */

  if (priv->txinflight == 0)
    {
      wd_cancel(&priv->txtimeout);
    }

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
  priv->intpending |= status;

  /* Mask channel interrupts until the bottom half drains pending work. */

  putreg32(0, priv->base + RZV_ETH_DMA_CH0_INT_EN);

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
  uint32_t pending;

  pending = priv->intpending;
  priv->intpending = 0;

  /* Handle RX */

  if (pending & (DMA_CH0_STATUS_RI | DMA_CH0_STATUS_RBU |
                 DMA_CH0_STATUS_RPS))
    {
      rzv_receive(priv);
    }

  /* Handle TX done */

  if (pending & (DMA_CH0_STATUS_TI | DMA_CH0_STATUS_TBU |
                 DMA_CH0_STATUS_TPS))
    {
      rzv_txdone(priv);
    }

  if (pending & DMA_CH0_STATUS_AIS)
    {
      nwarn("WARNING: Ethernet abnormal DMA status: %08" PRIx32 "\n",
            pending);
    }

  /* Re-enable interrupts if needed */

  if (priv->bifup)
    {
      putreg32(DMA_CH0_INT_EN_TIE | DMA_CH0_INT_EN_TBUE |
               DMA_CH0_INT_EN_RIE | DMA_CH0_INT_EN_RBUE |
               DMA_CH0_INT_EN_NISE | DMA_CH0_INT_EN_AISE,
               priv->base + RZV_ETH_DMA_CH0_INT_EN);
    }
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
  uint32_t macconf;
  uint32_t timeout;
  int ret;

  rzv_init_descriptors(priv);
  rzv_set_macaddr(priv);

  ret = rzv_configure_link(priv);
  if (ret < 0)
    {
      return ret;
    }

  /* Reset DMA and wait for reset completion with a bounded timeout. */

  putreg32(DMA_MODE_SWR, priv->base + RZV_ETH_DMA_MODE);
  for (timeout = 100000; timeout > 0; timeout--)
    {
      if ((getreg32(priv->base + RZV_ETH_DMA_MODE) & DMA_MODE_SWR) == 0)
        {
          break;
        }
    }

  if (timeout == 0)
    {
      nerr("ERROR: GBETH DMA reset timeout\n");
      return -ETIMEDOUT;
    }

  /* Configure DMA */

  putreg32(DMA_SYSBUS_MODE_AAL, priv->base + RZV_ETH_DMA_SYSBUS_MODE);
  putreg32(0, priv->base + RZV_ETH_DMA_CH0_TXDESC_HI);
  putreg32(0, priv->base + RZV_ETH_DMA_CH0_RXDESC_HI);
  putreg32((uint32_t)(uintptr_t)priv->txdesc,
           priv->base + RZV_ETH_DMA_CH0_TXDESC_LIST);
  putreg32((uint32_t)(uintptr_t)priv->rxdesc,
           priv->base + RZV_ETH_DMA_CH0_RXDESC_LIST);
  putreg32(CONFIG_RZV_ETHER_TXDESC - 1,
           priv->base + RZV_ETH_DMA_CH0_TXDESC_RING);
  putreg32(CONFIG_RZV_ETHER_RXDESC - 1,
           priv->base + RZV_ETH_DMA_CH0_RX_CTRL2);
  putreg32((uint32_t)(uintptr_t)&priv->txdesc[0],
           priv->base + RZV_ETH_DMA_CH0_TXDESC_TAIL);
  putreg32((uint32_t)(uintptr_t)&priv->rxdesc[CONFIG_RZV_ETHER_RXDESC - 1],
           priv->base + RZV_ETH_DMA_CH0_RXDESC_TAIL);

  putreg32(DMA_CH0_TX_CTRL_TXPBL(32) | DMA_CH0_TX_CTRL_OSP,
           priv->base + RZV_ETH_DMA_CH0_TX_CTRL);
  putreg32(DMA_CH0_RX_CTRL_RBSZ(RZV_ETHER_BUFSIZE) |
           DMA_CH0_RX_CTRL_RXPBL(32),
           priv->base + RZV_ETH_DMA_CH0_RX_CTRL);

  /* Enable MAC */

  macconf = getreg32(priv->base + RZV_ETH_MAC_CONF);
  putreg32(macconf | MAC_CONF_RE | MAC_CONF_TE,
           priv->base + RZV_ETH_MAC_CONF);

  /* Enable interrupts */

  ret = rzv_icu_attach(priv->event, rzv_interrupt, priv, true);
  if (ret < 0)
    {
      putreg32(macconf, priv->base + RZV_ETH_MAC_CONF);
      return ret;
    }

  priv->irq = ret;

  /* Enable DMA interrupts */

  putreg32(DMA_CH0_INT_EN_TIE | DMA_CH0_INT_EN_TBUE |
           DMA_CH0_INT_EN_RIE | DMA_CH0_INT_EN_RBUE |
           DMA_CH0_INT_EN_NISE | DMA_CH0_INT_EN_AISE,
           priv->base + RZV_ETH_DMA_CH0_INT_EN);

  /* Start TX/RX */

  putreg32(getreg32(priv->base + RZV_ETH_DMA_CH0_TX_CTRL) |
           DMA_CH0_TX_CTRL_ST,
           priv->base + RZV_ETH_DMA_CH0_TX_CTRL);
  putreg32(getreg32(priv->base + RZV_ETH_DMA_CH0_RX_CTRL) |
           DMA_CH0_RX_CTRL_SR,
           priv->base + RZV_ETH_DMA_CH0_RX_CTRL);

  priv->bifup = true;
  return OK;
}

static int rzv_ifdown(struct net_driver_s *dev)
{
  struct rzv_eth_s *priv = (struct rzv_eth_s *)dev->d_private;

  /* Disable interrupts */

  if (priv->irq >= 0)
    {
      rzv_icu_detach(priv->irq);
      priv->irq = -1;
    }

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
          req->phy_id = priv->phy_addr >= 0 ? priv->phy_addr :
                        CONFIG_RZV_ETHER_PHY_ADDR;
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
  priv->event = (intf == 0) ? RZV_ELC_GBETH0_INT : RZV_ELC_GBETH1_INT;
  priv->irq = -1;
  priv->phy_addr = -1;

  /* Allocate descriptors and buffers */

  if (rzv_alloc_buffers(priv) < 0)
    {
      return -ENOMEM;
    }

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
  return netdev_register(&priv->dev, NET_LL_ETHERNET);
}

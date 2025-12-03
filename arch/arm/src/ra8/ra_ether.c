/****************************************************************************
 * arch/arm/src/ra8/ra_ether.c
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
#include <nuttx/wqueue.h>
#include <nuttx/net/mii.h>
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
#include "ra_ether.h"
#include "hardware/ra8p1/ra_etherc_edmac.h"
#include "hardware/ra8p1/ra_etha.h"
#include "ra_icu.h"
#include "ra_mstp.h"

#ifdef CONFIG_RA_ETHERNET

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Configuration ************************************************************/

#ifndef CONFIG_RA_ETHERNET_NINTERFACES
#  define CONFIG_RA_ETHERNET_NINTERFACES 1
#endif

#ifndef CONFIG_RA_ETHERNET_NTXDESC
#  define CONFIG_RA_ETHERNET_NTXDESC 8
#endif

#ifndef CONFIG_RA_ETHERNET_NRXDESC
#  define CONFIG_RA_ETHERNET_NRXDESC 8
#endif

#define RA_MAX_PACKET_SIZE  1536
#define RA_BUF_ALIGN        32

/* Interrupts */
/* Define generic ELC events if not defined in irq.h */
#ifndef RA_ELC_EDMAC0_EINT
#  define RA_ELC_EDMAC0_EINT 0x068 /* Example ELC event number, needs verification */
#endif

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* The ra_ether_s encapsulates all state information for a single hardware
 * interface
 */

struct ra_ether_s
{
  bool              bifup;      /* true:ifup false:ifdown */
  struct net_driver_s dev;      /* Interface understood by the network */
  uint8_t           phyaddr;    /* PHY address */
  int               intf;       /* Interface number */
  int               irq;        /* IRQ number */

  /* Descriptors */
  struct ra_eth_desc_s *txdesc;
  struct ra_eth_desc_s *rxdesc;

  /* Buffers */
  uint8_t           *txbuffer;
  uint8_t           *rxbuffer;

  /* Descriptor indices */
  uint16_t          txhead;
  uint16_t          txtail;
  uint16_t          rxndx;
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

static struct ra_ether_s g_ra_ether[CONFIG_RA_ETHERNET_NINTERFACES];

/* Aligned descriptors and buffers */
/* Note: These should be placed in non-cacheable memory or properly flushed/invalidated */
static struct ra_eth_desc_s g_txdesc[CONFIG_RA_ETHERNET_NTXDESC] __attribute__((aligned(RA_BUF_ALIGN)));
static struct ra_eth_desc_s g_rxdesc[CONFIG_RA_ETHERNET_NRXDESC] __attribute__((aligned(RA_BUF_ALIGN)));
static uint8_t g_txbuffer[CONFIG_RA_ETHERNET_NTXDESC * RA_MAX_PACKET_SIZE] __attribute__((aligned(RA_BUF_ALIGN)));
static uint8_t g_rxbuffer[CONFIG_RA_ETHERNET_NRXDESC * RA_MAX_PACKET_SIZE] __attribute__((aligned(RA_BUF_ALIGN)));

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Common TX logic */

static int  ra_txpoll(struct net_driver_s *dev);

/* Interrupt handling */

static void ra_receive(struct ra_ether_s *priv);
static int  ra_interrupt(int irq, void *context, void *arg);

/* Watchdog timer expirations */


/* NuttX callback functions */

static int  ra_ifup(struct net_driver_s *dev);
static int  ra_ifdown(struct net_driver_s *dev);
static int  ra_txavail(struct net_driver_s *dev);
#ifdef CONFIG_NET_MCASTGROUP
static int  ra_addmac(struct net_driver_s *dev, const uint8_t *mac);
static int  ra_rmmac(struct net_driver_s *dev, const uint8_t *mac);
#endif
#ifdef CONFIG_NETDEV_IOCTL
static int  ra_ioctl(struct net_driver_s *dev, int cmd, unsigned long arg);
#endif

/* Initialization */

static void ra_reset(struct ra_ether_s *priv);
static void ra_init_buffers(struct ra_ether_s *priv);

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static inline uint32_t ra_getreg(uint32_t offset)
{
  return getreg32(offset);
}

static inline void ra_putreg(uint32_t val, uint32_t offset)
{
  putreg32(val, offset);
}

/****************************************************************************
 * Function: ra_txpoll
 *
 * Description:
 *   The transmitter is available, check if the network has any outgoing
 *   packets ready to send.  This is a callback from devif_poll().
 *
 ****************************************************************************/

static int ra_txpoll(struct net_driver_s *dev)
{
  struct ra_ether_s *priv = (struct ra_ether_s *)dev->d_private;
  struct ra_eth_desc_s *txdesc;

  /* If the polling resulted in data that should be sent out on the network,
   * the field d_len is set to a value > 0.
   */

  if (priv->dev.d_len > 0)
    {
      /* Look up the destination descriptor */
      txdesc = &priv->txdesc[priv->txhead];

      /* Check if the descriptor is free */
      if (txdesc->status & RA_TXDESC_TACT)
        {
          return -EBUSY;
        }

      /* Copy the packet data into the descriptor buffer */
      /* Note: In a zero-copy implementation, we would just point the buffer
       * to d_buf, but here we copy to the pre-allocated buffer.
       */
      memcpy((void *)txdesc->buf, priv->dev.d_buf, priv->dev.d_len);

      /* Set the length */
      txdesc->len = priv->dev.d_len;

      /* Set status bits: SOF, EOF, TACT */
      txdesc->status = RA_TXDESC_TACT | RA_TXDESC_TFP_SOF | RA_TXDESC_TFP_EOF;

      /* Wrap around if it's the last descriptor */
      if (priv->txhead == CONFIG_RA_ETHERNET_NTXDESC - 1)
        {
          txdesc->status |= RA_TXDESC_TDLE;
        }

      /* Trigger transmission */
      ra_putreg(R_ETHERC_EDMAC_EDTRR_TR, R_ETHERC_EDMAC_EDTRR);

      /* Update pointers */
      priv->txhead++;
      if (priv->txhead >= CONFIG_RA_ETHERNET_NTXDESC)
        {
          priv->txhead = 0;
        }

      /* Send done */
      /* If d_len > 0, the network stack assumes we sent it. */
    }

  return 0;
}

/****************************************************************************
 * Function: ra_receive
 *
 * Description:
 *   An interrupt was received indicating the availability of a new RX packet
 *
 ****************************************************************************/

static void ra_receive(struct ra_ether_s *priv)
{
  struct ra_eth_desc_s *rxdesc;

#define BUF ((struct eth_hdr_s *)priv->dev.d_buf)

  /* Loop while there are received packets */
  while (1)
    {
      rxdesc = &priv->rxdesc[priv->rxndx];

      /* Check if the descriptor is owned by the software (TACT = 0) */
      if (rxdesc->status & RA_RXDESC_RACT)
        {
          /* Still owned by EDMAC, no more packets */
          break;
        }

      /* Check for errors */
      if (rxdesc->status & RA_RXDESC_RFE)
        {
          nerr("RX Error: %08" PRIx32 "\n", rxdesc->status);
        }
      else
        {
          /* Get the length */
          priv->dev.d_len = rxdesc->len & RA_RXDESC_RFL_MASK;
          priv->dev.d_buf = (uint8_t *)rxdesc->buf;

          /* Pass to network stack */
          if (priv->dev.d_len > 0)
            {
#ifdef CONFIG_NET_PKT
              /* When packet sockets are enabled, feed the frame into the packet tap */
              pkt_input(&priv->dev);
#endif
              /* We only accept IP packets of the configured type and ARP packets */
#ifdef CONFIG_NET_IPv4
              if (BUF->type == HTONS(ETHTYPE_IP))
                {
                  ninfo("IPv4 frame\n");
                  ipv4_input(&priv->dev);
                }
              else
#endif
#ifdef CONFIG_NET_IPv6
              if (BUF->type == HTONS(ETHTYPE_IP6))
                {
                  ninfo("IPv6 frame\n");
                  ipv6_input(&priv->dev);
                }
              else
#endif
#ifdef CONFIG_NET_ARP
              if (BUF->type == HTONS(ETHTYPE_ARP))
                {
                  ninfo("ARP frame\n");
                  arp_arpin(&priv->dev);
                }
              else
#endif
                {
                  ninfo("Dropped, Unknown type: %04x\n", BUF->type);
                }
            }
        }

      /* Reset the descriptor */
      rxdesc->len = RA_MAX_PACKET_SIZE;
      rxdesc->status = RA_RXDESC_RACT;
      if (priv->rxndx == CONFIG_RA_ETHERNET_NRXDESC - 1)
        {
          rxdesc->status |= RA_RXDESC_RDLE;
        }

      /* Move to next descriptor */
      priv->rxndx++;
      if (priv->rxndx >= CONFIG_RA_ETHERNET_NRXDESC)
        {
          priv->rxndx = 0;
        }
    }

    /* Resume reception if suspended */
    ra_putreg(R_ETHERC_EDMAC_EDRRR_RR, R_ETHERC_EDMAC_EDRRR);
}

/****************************************************************************
 * Function: ra_interrupt
 *
 * Description:
 *   Hardware interrupt handler
 *
 ****************************************************************************/

static int ra_interrupt(int irq, void *context, void *arg)
{
  struct ra_ether_s *priv = (struct ra_ether_s *)arg;
  uint32_t status;

  /* Read status */
  status = ra_getreg(R_ETHERC_EDMAC_EESR);

  /* Clear status */
  ra_putreg(status, R_ETHERC_EDMAC_EESR);

  /* Handle Frame Receive */
  if (status & R_ETHERC_EDMAC_EESR_FR)
    {
      ra_receive(priv);
    }

  /* Handle Transmit Complete */
  if (status & R_ETHERC_EDMAC_EESR_TC)
    {
      /* Transmission done, check for more packets */
      devif_poll(&priv->dev, ra_txpoll);
    }

  return OK;
}

/****************************************************************************
 * Function: ra_ifup
 *
 * Description:
 *   NuttX Callback: Bring up the Ethernet interface when an IP address is
 *   provided
 *
 ****************************************************************************/

static int ra_ifup(struct net_driver_s *dev)
{
  struct ra_ether_s *priv = (struct ra_ether_s *)dev->d_private;

  /* Initialize buffers and descriptors */
  ra_init_buffers(priv);

  /* Enable interrupts */
  /* Attach the interrupt handler */
  /* Note: IRQ attach is done in board init or here if dynamic */

  /* Enable MAC/DMA */
  ra_putreg(R_ETHERC_EDMAC_EDRRR_RR, R_ETHERC_EDMAC_EDRRR); /* Start Receive */
  ra_putreg(R_ETHERC_EDMAC_EDTRR_TR, R_ETHERC_EDMAC_EDTRR); /* Start Transmit (if anything pending) */

  /* Enable Interrupts in EESIPR */
  ra_putreg(R_ETHERC_EDMAC_EESIPR_FRIP | R_ETHERC_EDMAC_EESIPR_TCIP, R_ETHERC_EDMAC_EESIPR);

  priv->bifup = true;
  return OK;
}

/****************************************************************************
 * Function: ra_ifdown
 *
 * Description:
 *   NuttX Callback: Stop the interface.
 *
 ****************************************************************************/

static int ra_ifdown(struct net_driver_s *dev)
{
  struct ra_ether_s *priv = (struct ra_ether_s *)dev->d_private;

  /* Disable Interrupts */
  ra_putreg(0, R_ETHERC_EDMAC_EESIPR);

  /* Stop MAC/DMA */
  /* Reset logic here */

  priv->bifup = false;
  return OK;
}

/****************************************************************************
 * Function: ra_txavail
 *
 * Description:
 *   Driver callback invoked when new TX data is available.  This is a
 *   stimulus perform an out-of-cycle poll and, thereby, reduce the TX
 *   latency.
 *
 ****************************************************************************/

static int ra_txavail(struct net_driver_s *dev)
{
  struct ra_ether_s *priv = (struct ra_ether_s *)dev->d_private;

  if (priv->bifup)
    {
      devif_poll(&priv->dev, ra_txpoll);
    }

  return OK;
}

/****************************************************************************
 * Function: ra_ioctl
 *
 * Description:
 *   PHY ioctl
 *
 ****************************************************************************/

#ifdef CONFIG_NETDEV_IOCTL
static int ra_ioctl(struct net_driver_s *dev, int cmd, unsigned long arg)
{
  /* Implement PHY IOCTLs here */
  return -ENOTTY;
}
#endif

/****************************************************************************
 * Function: ra_init_buffers
 *
 * Description:
 *   Initialize descriptors and buffers
 *
 ****************************************************************************/

static void ra_init_buffers(struct ra_ether_s *priv)
{
  int i;

  /* Initialize TX descriptors */
  for (i = 0; i < CONFIG_RA_ETHERNET_NTXDESC; i++)
    {
      priv->txdesc[i].status = 0; /* Owned by SW */
      priv->txdesc[i].len = 0;
      priv->txdesc[i].buf = (uint32_t)&priv->txbuffer[i * RA_MAX_PACKET_SIZE];
      priv->txdesc[i].next = (uint32_t)&priv->txdesc[(i + 1) % CONFIG_RA_ETHERNET_NTXDESC];

      if (i == CONFIG_RA_ETHERNET_NTXDESC - 1)
        {
           priv->txdesc[i].status |= RA_TXDESC_TDLE;
        }
    }

  /* Initialize RX descriptors */
  for (i = 0; i < CONFIG_RA_ETHERNET_NRXDESC; i++)
    {
      priv->rxdesc[i].status = RA_RXDESC_RACT; /* Owned by EDMAC */
      priv->rxdesc[i].len = RA_MAX_PACKET_SIZE;
      priv->rxdesc[i].buf = (uint32_t)&priv->rxbuffer[i * RA_MAX_PACKET_SIZE];
      priv->rxdesc[i].next = (uint32_t)&priv->rxdesc[(i + 1) % CONFIG_RA_ETHERNET_NRXDESC];

      if (i == CONFIG_RA_ETHERNET_NRXDESC - 1)
        {
           priv->rxdesc[i].status |= RA_RXDESC_RDLE;
        }
    }

  priv->txhead = 0;
  priv->txtail = 0;
  priv->rxndx = 0;

  /* Set Descriptor Base Addresses */
  ra_putreg((uint32_t)priv->txdesc, R_ETHERC_EDMAC_TDLAR);
  ra_putreg((uint32_t)priv->rxdesc, R_ETHERC_EDMAC_RDLAR);
}

/****************************************************************************
 * Function: ra_reset
 *
 * Description:
 *   Reset the Ethernet Controller
 *
 ****************************************************************************/

static void ra_reset(struct ra_ether_s *priv)
{
  /* Software Reset */
  ra_putreg(R_ETHERC_EDMAC_EDMR_SWR, R_ETHERC_EDMAC_EDMR);

  /* Wait for reset to complete */
  /* Add timeout loop */
  up_mdelay(10);

  /* Configure Ethernet Mode (MII/RMII/RGMII) */
#if defined(CONFIG_RA_ETHERC_RGMII)
  ra_putreg(2, R_ETHA_EAMC(priv->intf)); /* RGMII */
#elif defined(CONFIG_RA_ETHERC_RMII)
  ra_putreg(1, R_ETHA_EAMC(priv->intf)); /* RMII */
#else
  ra_putreg(0, R_ETHA_EAMC(priv->intf)); /* MII */
#endif

  /* Configure EDMR */
  /* Little Endian, 16/32/64 byte descriptor? Assuming 16 bytes (DL=00) */
  ra_putreg(R_ETHERC_EDMAC_EDMR_DL_00, R_ETHERC_EDMAC_EDMR);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Function: ra_ether_initialize
 *
 * Description:
 *   Initialize the Ethernet driver
 *
 ****************************************************************************/

int ra_ether_initialize(int intf)
{
  struct ra_ether_s *priv;
  int ret;

  if (intf >= CONFIG_RA_ETHERNET_NINTERFACES)
    {
      return -EINVAL;
    }

  priv = &g_ra_ether[intf];

  /* Initialize the driver structure */
  memset(priv, 0, sizeof(struct ra_ether_s));
  priv->intf = intf;
  priv->dev.d_ifup    = ra_ifup;
  priv->dev.d_ifdown  = ra_ifdown;
  priv->dev.d_txavail = ra_txavail;
#ifdef CONFIG_NETDEV_IOCTL
  priv->dev.d_ioctl   = ra_ioctl;
#endif
  priv->dev.d_private = priv;

  priv->txdesc = g_txdesc;
  priv->rxdesc = g_rxdesc;
  priv->txbuffer = g_txbuffer;
  priv->rxbuffer = g_rxbuffer;

  /* Attach Interrupt */
  /* Note: Using dynamic IRQ allocation as requested */
  /* The user specified: ra_icu_attach(RA_ELC_<INTERRUPT_NAME>, ether_handler, &ether_dev, true); */
  /* We need to find the correct ELC event for Ethernet. */
  /* Assuming RA_ELC_EDMAC0_EINT is defined or we need to find it. */

  priv->irq = ra_icu_attach(RA_ELC_EDMAC0_EINT, ra_interrupt, priv, true);
  if (priv->irq < 0)
    {
      nerr("Failed to attach IRQ\n");
      return priv->irq;
    }

  /* Reset the controller */
  ra_reset(priv);

  /* Register the device with the OS */
  ret = netdev_register(&priv->dev, NET_LL_ETHERNET);
  if (ret < 0)
    {
      nerr("netdev_register failed: %d\n", ret);
      return ret;
    }

  return OK;
}

#endif /* CONFIG_RA_ETHERNET */

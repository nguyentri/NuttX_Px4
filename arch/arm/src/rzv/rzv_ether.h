/****************************************************************************
 * arch/arm/src/rzv/rzv_ether.h
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

#ifndef __ARCH_ARM_SRC_RZV_RZV_ETHER_H
#define __ARCH_ARM_SRC_RZV_RZV_ETHER_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/net/netdev.h>
#include <nuttx/net/phy.h>
#include <nuttx/spinlock.h>
#include <nuttx/wqueue.h>
#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Configuration ************************************************************/

#ifndef CONFIG_RZV_ETHER_TXDESC
#  define CONFIG_RZV_ETHER_TXDESC 8
#endif

#ifndef CONFIG_RZV_ETHER_RXDESC
#  define CONFIG_RZV_ETHER_RXDESC 8
#endif

#define RZV_ETHER_BUFSIZE CONFIG_RZV_ETHER_BUFSIZE /* MTU + Header + FCS */
#define RZV_ETHER_DMA_ALIGN 64

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* The DMA descriptor structure.
 *
 * Padded and aligned to a full cacheline so each descriptor owns its own
 * line.  Otherwise up_invalidate_dcache() on a 16-byte descriptor discards
 * pending writes to the neighboring descriptors that share the same 64-byte
 * line, corrupting the OWN bookkeeping under DMA traffic.
 */

struct rzv_eth_desc_s
{
  volatile uint32_t des0;
  volatile uint32_t des1;
  volatile uint32_t des2;
  volatile uint32_t des3;
  uint32_t reserved[12]; /* Pad to 64 bytes */
} __attribute__((aligned(RZV_ETHER_DMA_ALIGN)));

/* The driver state structure */

struct rzv_eth_s
{
  /* The net_driver_s must be the first field */
  struct net_driver_s dev;

  /* Driver state */
  bool bifup;               /* true:ifup false:ifdown */
  struct wdog_s txtimeout;  /* TX timeout watchdog */
  struct work_s irqwork;    /* For deferring interrupt work to the work queue */
  struct work_s pollwork;   /* Periodic PHY link polling */
  struct work_s txavail_work; /* Deferred devif poll from txavail */
  struct work_s txtimeout_work; /* For deferring TX timeout work */

  /* Hardware resources */
  uintptr_t base;           /* Base address of the controller */
  int event;                /* INTC event selector */
  int irq;                  /* Allocated NuttX IRQ number */
  int intf;                 /* Interface number (0 or 1) */

  /* Descriptors and buffers */
  struct rzv_eth_desc_s *txdesc; /* TX descriptor list */
  struct rzv_eth_desc_s *rxdesc; /* RX descriptor list */
  uint8_t *txbuffer;             /* TX buffers */
  uint8_t *rxbuffer;             /* RX buffers */
  uint8_t *pktbuf;               /* Network stack packet buffer */

  unsigned int txhead;      /* Next TX descriptor to use */
  unsigned int txtail;      /* Next TX descriptor to clean */
  unsigned int txinflight;   /* Number of TX descriptors owned by DMA */
  unsigned int rxndx;       /* Next RX descriptor to check */
  volatile uint32_t intpending; /* Deferred DMA interrupt status (ISR <-> work) */
  spinlock_t lock;          /* Serializes ISR<->work exchange of intpending */

  /* PHY state */
  int phy_addr;             /* PHY address */
  uint32_t phy_id;          /* PHY identifier */
  bool linkup;              /* Link status */
  bool duplex;              /* true: full duplex */
  int speed;                /* Link speed in Mbps */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_ether_initialize
 *
 * Description:
 *   Initialize the Ethernet driver for a specific interface.
 *
 * Input Parameters:
 *   intf - The interface number (0 or 1).
 *
 * Returned Value:
 *   OK on success; Negated errno on failure.
 *
 ****************************************************************************/

int rzv_ether_initialize(int intf);

/****************************************************************************
 * Name: rzv_ether_board_set_speed
 *
 * Description:
 *   Board-level hook invoked by the arch driver after the PHY resolves a
 *   new link speed. The board implementation programs SYSC_SYS_GBETHx_CFG
 *   MAC_SPEED bits so the RGMII reference clock divider matches link speed.
 *
 * Input Parameters:
 *   intf  - Interface number (0 or 1).
 *   mbps  - Negotiated link speed in Mbps (10 / 100 / 1000).  0 = link down.
 *
 * Returned Value:
 *   None.  Implemented as a weak no-op in the arch driver and overridden in
 *   board-level rzv2h_ether.c.
 *
 ****************************************************************************/

void rzv_ether_board_set_speed(int intf, int mbps);

#endif /* __ARCH_ARM_SRC_RZV_RZV_ETHER_H */

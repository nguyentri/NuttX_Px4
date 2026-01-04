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

#define RZV_ETHER_BUFSIZE 1536 /* MTU + Header + FCS */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* The DMA descriptor structure */

struct rzv_eth_desc_s
{
  volatile uint32_t des0;
  volatile uint32_t des1;
  volatile uint32_t des2;
  volatile uint32_t des3;
};

/* The driver state structure */

struct rzv_eth_s
{
  /* The net_driver_s must be the first field */
  struct net_driver_s dev;

  /* Driver state */
  bool bifup;               /* true:ifup false:ifdown */
  struct wdog_s txtimeout;  /* TX timeout watchdog */
  struct work_s irqwork;    /* For deferring interrupt work to the work queue */
  struct work_s pollwork;   /* For polling PHY status */
  struct work_s txtimeout_work; /* For deferring TX timeout work */

  /* Hardware resources */
  uintptr_t base;           /* Base address of the controller */
  int irq;                  /* Interrupt number */
  int intf;                 /* Interface number (0 or 1) */

  /* Descriptors and buffers */
  struct rzv_eth_desc_s *txdesc; /* TX descriptor list */
  struct rzv_eth_desc_s *rxdesc; /* RX descriptor list */
  uint8_t *txbuffer;             /* TX buffers */
  uint8_t *rxbuffer;             /* RX buffers */

  unsigned int txhead;      /* Next TX descriptor to use */
  unsigned int txtail;      /* Next TX descriptor to clean */
  unsigned int rxndx;       /* Next RX descriptor to check */

  /* PHY state */
  int phy_addr;             /* PHY address */
  bool linkup;              /* Link status */
  bool duplex;              /* Duplex mode */
  bool speed;               /* Speed (100/1000) */
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

#endif /* __ARCH_ARM_SRC_RZV_RZV_ETHER_H */

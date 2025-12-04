/****************************************************************************
 * arch/arm/src/ra8/ra_ether.h
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

#ifndef __ARCH_ARM_SRC_RA_RA8_ETHER_H
#define __ARCH_ARM_SRC_RA_RA8_ETHER_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/net/netdev.h>
#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Descriptor definitions */

/* Transmit Descriptor Status */
#define RA_TXDESC_TACT      (1u << 31)  /* Transmit Active */
#define RA_TXDESC_TDLE      (1u << 30)  /* Transmit Descriptor List End */
#define RA_TXDESC_TFP_SOF   (1u << 29)  /* Transmit Frame Position: Start of Frame */
#define RA_TXDESC_TFP_EOF   (1u << 28)  /* Transmit Frame Position: End of Frame */
#define RA_TXDESC_TFE       (1u << 27)  /* Transmit Frame Error */
#define RA_TXDESC_TWBI      (1u << 26)  /* Transmit Write-Back Interrupt */
#define RA_TXDESC_TFS_MASK  (0x03ff0000) /* Transmit Frame Status Mask */

/* Receive Descriptor Status */
#define RA_RXDESC_RACT      (1u << 31)  /* Receive Active */
#define RA_RXDESC_RDLE      (1u << 30)  /* Receive Descriptor List End */
#define RA_RXDESC_RFP_SOF   (1u << 29)  /* Receive Frame Position: Start of Frame */
#define RA_RXDESC_RFP_EOF   (1u << 28)  /* Receive Frame Position: End of Frame */
#define RA_RXDESC_RFE       (1u << 27)  /* Receive Frame Error */
#define RA_RXDESC_RFS_MASK  (0x03ff0000) /* Receive Frame Status Mask */
#define RA_RXDESC_RFL_MASK  (0x0000ffff) /* Receive Frame Length Mask */

/* Descriptor Structure (Assuming 16-byte descriptor size for simplicity, check EDMR.DL) */
struct ra_eth_desc_s
{
  volatile uint32_t status;
  volatile uint32_t len;      /* Buffer length (TX) or Frame Length (RX) */
  volatile uint32_t buf;      /* Buffer Address */
  volatile uint32_t next;     /* Next Descriptor Address (if used, or padding) */
};

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: ra_ether_initialize
 *
 * Description:
 *   Initialize the Ethernet driver.
 *
 * Input Parameters:
 *   intf - The interface number (0 for ETH0, etc.)
 *
 * Returned Value:
 *   OK on success; Negated errno on failure.
 *
 ****************************************************************************/

int ra_ether_initialize(int intf);

#endif /* __ARCH_ARM_SRC_RA_RA8_ETHER_H */

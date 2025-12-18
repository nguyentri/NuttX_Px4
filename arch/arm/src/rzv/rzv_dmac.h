/****************************************************************************
 * arch/arm/src/rzv/rzv_dmac.h
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

#ifndef __ARCH_ARM_SRC_RZV_DMAC_H
#define __ARCH_ARM_SRC_RZV_DMAC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Transfer size options ****************************************************/

#define RZV_DMAC_WIDTH_8BIT         0
#define RZV_DMAC_WIDTH_16BIT        1
#define RZV_DMAC_WIDTH_32BIT        2
#define RZV_DMAC_WIDTH_64BIT        3

/* Address modes ************************************************************/

#define RZV_DMAC_ADDR_INCREMENT     0
#define RZV_DMAC_ADDR_DECREMENT     1
#define RZV_DMAC_ADDR_FIXED         2

/* Number of DMA channels ***************************************************/

#define RZV_DMAC_NUM_CHANNELS       8

/* DMA channel IDs **********************************************************/

#define RZV_DMAC_CHANNEL_0          0
#define RZV_DMAC_CHANNEL_1          1
#define RZV_DMAC_CHANNEL_2          2
#define RZV_DMAC_CHANNEL_3          3
#define RZV_DMAC_CHANNEL_4          4
#define RZV_DMAC_CHANNEL_5          5
#define RZV_DMAC_CHANNEL_6          6
#define RZV_DMAC_CHANNEL_7          7

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* DMA transfer configuration */

struct rzv_dmac_config_s
{
  uint32_t src_addr;        /* Source address */
  uint32_t dst_addr;        /* Destination address */
  uint32_t count;           /* Transfer count in bytes */
  uint8_t  src_width;       /* Source transfer width */
  uint8_t  dst_width;       /* Destination transfer width */
  uint8_t  src_addr_mode;   /* Source address mode */
  uint8_t  dst_addr_mode;   /* Destination address mode */
  uint8_t  priority;        /* Channel priority */
  bool     mem_to_mem;      /* Memory-to-memory transfer */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Name: rzv_dmac_channel_initialize
 *
 * Description:
 *   Initialize a DMA channel
 *
 * Input Parameters:
 *   channel - DMA channel number (0-7)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure
 *
 ****************************************************************************/

int rzv_dmac_channel_initialize(int channel);

/****************************************************************************
 * Name: rzv_dmac_channel_configure
 *
 * Description:
 *   Configure a DMA channel for transfer
 *
 * Input Parameters:
 *   channel - DMA channel number (0-7)
 *   config  - DMA configuration structure
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure
 *
 ****************************************************************************/

int rzv_dmac_channel_configure(int channel,
                                const struct rzv_dmac_config_s *config);

/****************************************************************************
 * Name: rzv_dmac_channel_start
 *
 * Description:
 *   Start a DMA transfer
 *
 * Input Parameters:
 *   channel - DMA channel number (0-7)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure
 *
 ****************************************************************************/

int rzv_dmac_channel_start(int channel);

/****************************************************************************
 * Name: rzv_dmac_channel_stop
 *
 * Description:
 *   Stop a DMA transfer
 *
 * Input Parameters:
 *   channel - DMA channel number (0-7)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure
 *
 ****************************************************************************/

int rzv_dmac_channel_stop(int channel);

/****************************************************************************
 * Name: rzv_dmac_channel_status
 *
 * Description:
 *   Get DMA channel status
 *
 * Input Parameters:
 *   channel - DMA channel number (0-7)
 *
 * Returned Value:
 *   Channel status flags
 *
 ****************************************************************************/

uint32_t rzv_dmac_channel_status(int channel);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RZV_DMAC_H */

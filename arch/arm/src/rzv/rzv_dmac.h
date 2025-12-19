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

/* Note: Transfer sizes, address modes, and channel counts are now defined
 * as enums below rather than macros to avoid conflicts
 */

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

/* DMAC_B Transfer Mode */

typedef enum
{
  RZV_DMAC_MODE_REGISTER = 0,  /* Register mode */
  RZV_DMAC_MODE_LINK           /* Link mode */
} rzv_dmac_mode_t;

/* DMAC_B Transfer Size */

typedef enum
{
  RZV_DMAC_SIZE_1BYTE = 0,   /* 1-byte transfer */
  RZV_DMAC_SIZE_2BYTE,       /* 2-byte transfer */
  RZV_DMAC_SIZE_4BYTE,       /* 4-byte transfer */
  RZV_DMAC_SIZE_8BYTE,       /* 8-byte transfer */
  RZV_DMAC_SIZE_16BYTE,      /* 16-byte transfer */
  RZV_DMAC_SIZE_32BYTE,      /* 32-byte transfer */
  RZV_DMAC_SIZE_64BYTE,      /* 64-byte transfer */
  RZV_DMAC_SIZE_128BYTE      /* 128-byte transfer */
} rzv_dmac_size_t;

/* DMAC_B Address Mode */

typedef enum
{
  RZV_DMAC_ADDR_INCREMENT = 0, /* Increment address */
  RZV_DMAC_ADDR_FIXED = 2      /* Fixed address */
} rzv_dmac_addr_mode_t;

/* DMAC_B Trigger Mode */

typedef enum
{
  RZV_DMAC_TRIGGER_SW = 0,   /* Software trigger */
  RZV_DMAC_TRIGGER_HW        /* Hardware trigger */
} rzv_dmac_trigger_t;

/* DMAC_B Detection Mode */

typedef enum
{
  RZV_DMAC_DETECT_LOW_LEVEL = 0,    /* Low level detection */
  RZV_DMAC_DETECT_FALLING_EDGE,     /* Falling edge detection */
  RZV_DMAC_DETECT_RISING_EDGE,      /* Rising edge detection */
  RZV_DMAC_DETECT_BOTH_EDGE,        /* Both edge detection */
  RZV_DMAC_DETECT_HIGH_LEVEL = 6    /* High level detection */
} rzv_dmac_detect_t;

/* Forward declaration */

typedef void *rzv_dmac_handle_t;

/* DMAC callback function type */

typedef void (*rzv_dmac_callback_t)(void *handle, int event, void *user_data);

/* DMAC_B transfer configuration */

struct rzv_dmac_config_s
{
  rzv_dmac_mode_t       mode;            /* Transfer mode */
  rzv_dmac_size_t       src_size;        /* Source transfer width */
  rzv_dmac_size_t       dst_size;        /* Destination transfer width */
  rzv_dmac_addr_mode_t  src_addr_mode;   /* Source address mode */
  rzv_dmac_addr_mode_t  dst_addr_mode;   /* Destination address mode */
  rzv_dmac_trigger_t    trigger;         /* Trigger mode */
  rzv_dmac_detect_t     detect_mode;     /* Detection mode */

  uint32_t              src_addr;        /* Source address */
  uint32_t              dst_addr;        /* Destination address */
  uint32_t              length;          /* Transfer length in bytes */

  uint8_t               priority;        /* Channel priority (0-7) */
  uint16_t              transfer_interval; /* Transfer interval */

  int                   elc_event;       /* ELC event number for HW trigger */
  int                   irq_num;         /* IRQ number for interrupt */

  rzv_dmac_callback_t   callback;        /* Transfer callback */
  void                 *user_data;       /* User data for callback */
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
 *   channel - DMA channel number (0-79)
 *
 * Returned Value:
 *   Channel status flags
 *
 ****************************************************************************/

uint32_t rzv_dmac_channel_status(int channel);

/****************************************************************************
 * Name: rzv_dmac_get_remaining_bytes
 *
 * Description:
 *   Get remaining transfer byte count
 *
 * Input Parameters:
 *   channel - DMA channel number (0-79)
 *
 * Returned Value:
 *   Remaining bytes to transfer
 *
 ****************************************************************************/

uint32_t rzv_dmac_get_remaining_bytes(int channel);

/* DMAC Event definitions for callbacks */

#define RZV_DMAC_EVENT_COMPLETE  (0)  /* Transfer complete */
#define RZV_DMAC_EVENT_ERROR     (1)  /* Transfer error */

/* DMAC Channel status bits */

#define RZV_DMAC_STATUS_EN       (1 << 0)  /* Channel enabled */
#define RZV_DMAC_STATUS_RQST     (1 << 1)  /* Request pending */
#define RZV_DMAC_STATUS_TACT     (1 << 2)  /* Transfer active */
#define RZV_DMAC_STATUS_SUS      (1 << 3)  /* Suspended */
#define RZV_DMAC_STATUS_ER       (1 << 4)  /* Error */
#define RZV_DMAC_STATUS_END      (1 << 5)  /* Transfer end */
#define RZV_DMAC_STATUS_TC       (1 << 6)  /* Transfer count match */
#define RZV_DMAC_STATUS_SR       (1 << 7)  /* Soft request */

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RZV_DMAC_H */

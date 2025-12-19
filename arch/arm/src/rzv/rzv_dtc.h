/****************************************************************************
 * arch/arm/src/rzv/rzv_dtc.h
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

#ifndef __ARCH_ARM_SRC_RZV_RZV_DTC_H
#define __ARCH_ARM_SRC_RZV_RZV_DTC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

#include "chip.h"
#include "hardware/rzv_dtc.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DTC Events */

#define RZV_DTC_EVENT_END         (0)  /* Transfer complete */
#define RZV_DTC_EVENT_ERROR       (1)  /* Transfer error */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* DTC Transfer Mode */

typedef enum
{
  RZV_DTC_MODE_NORMAL = 0,  /* Normal mode */
  RZV_DTC_MODE_REPEAT,      /* Repeat mode */
  RZV_DTC_MODE_BLOCK        /* Block mode */
} rzv_dtc_mode_t;

/* DTC Transfer Size */

typedef enum
{
  RZV_DTC_SIZE_BYTE = 0,    /* 8-bit transfer */
  RZV_DTC_SIZE_WORD,        /* 16-bit transfer */
  RZV_DTC_SIZE_LONG         /* 32-bit transfer */
} rzv_dtc_size_t;

/* DTC Address Mode */

typedef enum
{
  RZV_DTC_ADDR_FIXED = 0,   /* Fixed address */
  RZV_DTC_ADDR_INCR,        /* Increment address */
  RZV_DTC_ADDR_DECR         /* Decrement address */
} rzv_dtc_addr_mode_t;

/* DTC Transfer Information Structure (16 bytes)
 * This matches the hardware layout expected by the DTC controller
 */

typedef struct
{
  uint8_t  reserved0[2];  /* Offset 0x00-0x01: Reserved */
  uint8_t  mrb;           /* Offset 0x02: Mode Register B */
  uint8_t  mra;           /* Offset 0x03: Mode Register A */
  uint32_t sar;           /* Offset 0x04: Source Address Register */
  uint32_t dar;           /* Offset 0x08: Destination Address Register */
  uint16_t crb;           /* Offset 0x0C: Transfer Count Register B */
  uint16_t cra;           /* Offset 0x0E: Transfer Count Register A */
} rzv_dtc_info_t;

/* Forward declaration */

typedef void *rzv_dtc_handle_t;

/* DTC callback function type */

typedef void (*rzv_dtc_callback_t)(void *handle, int event, void *user_data);

/* DTC configuration structure */

typedef struct rzv_dtc_config_s
{
  rzv_dtc_mode_t        mode;             /* Transfer mode */
  rzv_dtc_size_t        size;             /* Transfer data size */
  rzv_dtc_addr_mode_t   src_addr_mode;    /* Source address mode */
  rzv_dtc_addr_mode_t   dest_addr_mode;   /* Destination address mode */
  bool                  software_trigger; /* Software trigger mode */

  uint32_t              src_addr;         /* Source address */
  uint32_t              dest_addr;        /* Destination address */
  uint32_t              transfer_count;   /* Number of transfers */
  uint32_t              block_count;      /* Number of blocks (block mode) */

  int                   elc_src;          /* Hardware trigger source (event link) */
  int                   irq_src;          /* Dynamic ICU slot IRQ number (RZV_IRQ_FIRST + slot) */

  rzv_dtc_callback_t    callback;         /* Transfer callback */
  void                 *user_data;        /* User data for callback */
} rzv_dtc_config_t;

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/* DTC module functions */

int rzv_dtc_initialize(void);

/* DTC transfer functions */

int rzv_dtc_open(rzv_dtc_handle_t *handle, const rzv_dtc_config_t *config);
int rzv_dtc_close(rzv_dtc_handle_t handle);
int rzv_dtc_enable(rzv_dtc_handle_t handle);
int rzv_dtc_disable(rzv_dtc_handle_t handle);
int rzv_dtc_software_start(rzv_dtc_handle_t handle);
int rzv_dtc_reset(rzv_dtc_handle_t handle, uint32_t src_addr,
                  uint32_t dest_addr, uint32_t transfer_count);

/* DTC vector table management */

int rzv_dtc_set_vector(int icu_slot, rzv_dtc_info_t *transfer_info);
int rzv_dtc_clear_vector(int icu_slot);

/* DTC status functions */

uint32_t rzv_dtc_get_remaining_count(rzv_dtc_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RZV_RZV_DTC_H */

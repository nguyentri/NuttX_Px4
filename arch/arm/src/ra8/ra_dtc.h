/****************************************************************************
 * arch/arm/src/ra8/ra_dtc.h
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

#ifndef __ARCH_ARM_SRC_RA_RA8_DTC_H
#define __ARCH_ARM_SRC_RA_RA8_DTC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

#include "chip.h"
#include "hardware/ra_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Mode Register A (MRA) bit definitions */
#define RA_DTC_MRA_MD_SHIFT      (6)       /* Transfer Mode */
#define RA_DTC_MRA_MD_MASK       (0x3 << RA_DTC_MRA_MD_SHIFT)
#define RA_DTC_MRA_MD_NORMAL     (0x0 << RA_DTC_MRA_MD_SHIFT)
#define RA_DTC_MRA_MD_REPEAT     (0x1 << RA_DTC_MRA_MD_SHIFT)
#define RA_DTC_MRA_MD_BLOCK      (0x2 << RA_DTC_MRA_MD_SHIFT)

#define RA_DTC_MRA_SZ_SHIFT      (4)       /* Transfer Data Size */
#define RA_DTC_MRA_SZ_MASK       (0x3 << RA_DTC_MRA_SZ_SHIFT)
#define RA_DTC_MRA_SZ_BYTE       (0x0 << RA_DTC_MRA_SZ_SHIFT)
#define RA_DTC_MRA_SZ_WORD       (0x1 << RA_DTC_MRA_SZ_SHIFT)
#define RA_DTC_MRA_SZ_LONG       (0x2 << RA_DTC_MRA_SZ_SHIFT)

#define RA_DTC_MRA_SM_SHIFT      (2)       /* Source Address Mode */
#define RA_DTC_MRA_SM_MASK       (0x3 << RA_DTC_MRA_SM_SHIFT)
#define RA_DTC_MRA_SM_FIXED      (0x0 << RA_DTC_MRA_SM_SHIFT)
#define RA_DTC_MRA_SM_INCREMENT  (0x2 << RA_DTC_MRA_SM_SHIFT)
#define RA_DTC_MRA_SM_DECREMENT  (0x3 << RA_DTC_MRA_SM_SHIFT)

/* Mode Register B (MRB) bit definitions */
#define RA_DTC_MRB_CHNE          (1 << 7)  /* Chain Transfer Enable */
#define RA_DTC_MRB_CHNS          (1 << 6)  /* Chain Transfer Select */
#define RA_DTC_MRB_DISEL         (1 << 5)  /* DTC Interrupt Select */
#define RA_DTC_MRB_DTS           (1 << 4)  /* DTC Transfer Mode Select */

#define RA_DTC_MRB_DM_SHIFT      (2)       /* Destination Address Mode */
#define RA_DTC_MRB_DM_MASK       (0x3 << RA_DTC_MRB_DM_SHIFT)
#define RA_DTC_MRB_DM_FIXED      (0x0 << RA_DTC_MRB_DM_SHIFT)
#define RA_DTC_MRB_DM_INCREMENT  (0x2 << RA_DTC_MRB_DM_SHIFT)
#define RA_DTC_MRB_DM_DECREMENT  (0x3 << RA_DTC_MRB_DM_SHIFT)

/* Transfer size constants */
#define RA_DTC_MAX_NORMAL_LENGTH    (0x10000)  /* 65536 transfers max */
#define RA_DTC_MAX_REPEAT_LENGTH    (0x400)    /* 1024 transfers max */
#define RA_DTC_MAX_BLOCK_LENGTH     (0x400)    /* 1024 transfers max */

/* Vector table alignment */
#define RA_DTC_VECTOR_TABLE_ALIGN   (1024)

/* Transfer info structure size (must be 16 bytes) */
#define RA_DTC_TRANSFER_INFO_SIZE   (16)

/* Vector table size for DTC */
#define RA_DTC_VECTOR_TABLE_ENTRIES  (32)

/* DTC Events */
#define RA_DTC_EVENT_END         (0)  /* Transfer complete */
#define RA_DTC_EVENT_ERROR       (1)  /* Transfer error */

/* DTC Limits */
#define RA_DTC_MAX_TRANSFER_COUNT     (0x10000)  /* Maximum transfers in normal mode */
#define RA_DTC_MAX_BLOCK_COUNT        (0x100)    /* Maximum block count */
#define RA_DTC_MAX_CONTEXTS           (32)       /* Maximum DTC contexts */

/* DTC Transfer Mode */
typedef enum
{
  RA_DTC_MODE_NORMAL = 0,  /* Normal mode */
  RA_DTC_MODE_REPEAT,      /* Repeat mode */
  RA_DTC_MODE_BLOCK        /* Block mode */
} ra_dtc_mode_t;

/* DTC Transfer Size */
typedef enum
{
  RA_DTC_SIZE_BYTE = 0,    /* 8-bit transfer */
  RA_DTC_SIZE_WORD,        /* 16-bit transfer */
  RA_DTC_SIZE_LONG         /* 32-bit transfer */
} ra_dtc_size_t;

/* DTC Address Mode */
typedef enum
{
  RA_DTC_ADDR_FIXED = 0,   /* Fixed address */
  RA_DTC_ADDR_INCR,        /* Increment address */
  RA_DTC_ADDR_DECR         /* Decrement address */
} ra_dtc_addr_mode_t;

/* DTC Transfer Information Structure (16 bytes) */
typedef struct
{
  uint8_t  reserved0[2];  /* Offset 0x00-0x01: Reserved */
  uint8_t  mrb;           /* Offset 0x02: Mode Register B */
  uint8_t  mra;           /* Offset 0x03: Mode Register A */
  uint32_t sar;           /* Offset 0x04: Source Address Register */
  uint32_t dar;           /* Offset 0x08: Destination Address Register */
  uint16_t crb;           /* Offset 0x0C: Transfer Count Register B */
  uint16_t cra;           /* Offset 0x0E: Transfer Count Register A */
} ra_dtc_info_t;

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* Forward declaration */
typedef void *ra_dtc_handle_t;

/* DTC callback function type */
typedef void (*ra_dtc_callback_t)(void *handle, int event, void *user_data);

/* DTC configuration structure */
typedef struct ra_dtc_config_s
{
  ra_dtc_mode_t        mode;             /* Transfer mode */
  ra_dtc_size_t        size;             /* Transfer data size */
  ra_dtc_addr_mode_t   src_addr_mode;    /* Source address mode */
  ra_dtc_addr_mode_t   dest_addr_mode;   /* Destination address mode */
  bool                 software_trigger; /* Software trigger mode */

  uint32_t             src_addr;         /* Source address */
  uint32_t             dest_addr;        /* Destination address */
  uint32_t             transfer_count;   /* Number of transfers */
  uint32_t             block_count;      /* Number of blocks (block mode) */

  int                  elc_src;         /* Hardware trigger source (event link) */
  int                  irq_src;         /* Dynamic ICU slot IRQ number (RA_IRQ_FIRST + slot) */

  ra_dtc_callback_t    callback;         /* Transfer callback */
  void                *user_data;        /* User data for callback */
} ra_dtc_config_t;

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/* DTC module functions */
int ra_dtc_initialize(void);

/* DTC transfer functions */
int ra_dtc_open(ra_dtc_handle_t *handle, const ra_dtc_config_t *config);
int ra_dtc_close(ra_dtc_handle_t handle);
int ra_dtc_enable(ra_dtc_handle_t handle);
int ra_dtc_disable(ra_dtc_handle_t handle);
int ra_dtc_software_start(ra_dtc_handle_t handle);
int ra_dtc_reset(ra_dtc_handle_t handle, uint32_t src_addr,
                 uint32_t dest_addr, uint32_t transfer_count);

/* DTC vector table management */
int ra_dtc_set_vector(int icu_slot, ra_dtc_info_t *transfer_info);
int ra_dtc_clear_vector(int icu_slot);

/* DTC status functions */
uint32_t ra_dtc_get_remaining_count(ra_dtc_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RA_RA8_DTC_H */

/****************************************************************************
 * arch/arm/src/ra8/ra_sdhi.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_SDHI_H
#define __ARCH_ARM_SRC_RA8_RA_SDHI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>
#include <nuttx/sdio.h>

#if defined(CONFIG_RA8E1_GROUP)
#  include "hardware/ra8e1/ra_sdhi.h"
#elif defined(CONFIG_RA8P1_GROUP)
#  include "hardware/ra8p1/ra_sdhi.h"
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SDHI Channel definitions */

#define RA_SDHI_CHANNEL_0       0
#define RA_SDHI_CHANNEL_1       1

/* SDHI maximum block size */

#define RA_SDHI_MAX_BLOCK_SIZE  512

/* SDHI default card detect time */

#define RA_SDHI_CD_TIMEOUT_MS   100

/* Bus width definitions */

#define RA_SDHI_BUS_WIDTH_1BIT  0
#define RA_SDHI_BUS_WIDTH_4BIT  1
#define RA_SDHI_BUS_WIDTH_8BIT  2  /* Only for eMMC */

/* Clock rate definitions */

#define RA_SDHI_CLOCK_400KHZ    400000    /* Identification mode */
#define RA_SDHI_CLOCK_25MHZ     25000000  /* SD Default Speed */
#define RA_SDHI_CLOCK_50MHZ     50000000  /* SD High Speed */
#define RA_SDHI_CLOCK_52MHZ     52000000  /* eMMC High Speed */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Name: ra_sdhi_config_s
 *
 * Description:
 *   SDHI channel configuration structure
 *
 ****************************************************************************/

struct ra_sdhi_config_s
{
  uint8_t channel;              /* SDHI channel number (0 or 1) */
  uint8_t bus_width;            /* Bus width: 1, 4, or 8 bits */
  bool    dma_enable;           /* Enable DMA transfers */
  bool    cd_inverted;          /* Card detect signal inverted */
  bool    wp_inverted;          /* Write protect signal inverted */
  uint8_t irq_priority;         /* Interrupt priority level */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Name: ra_sdhi_initialize
 *
 * Description:
 *   Initialize the SDHI controller for the specified channel.
 *   Returns an SDIO interface reference that can be used with mmcsd_slotinitialize.
 *
 * Input Parameters:
 *   channel - SDHI channel number (0 or 1)
 *
 * Returned Value:
 *   A reference to an SDIO interface structure. NULL is returned on failure.
 *
 ****************************************************************************/

struct sdio_dev_s *ra_sdhi_initialize(int channel);

/****************************************************************************
 * Name: ra_sdhi_set_sdio_card_isr
 *
 * Description:
 *   SDIO card generates interrupt via SDIO_DATA_1 pin.
 *   Called by board-specific logic to register an ISR for SDIO card.
 *
 * Input Parameters:
 *   dev  - An instance of the SDIO device interface
 *   func - callback function
 *   arg  - argument to pass to callback function
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

void ra_sdhi_set_sdio_card_isr(struct sdio_dev_s *dev,
                               int (*func)(void *), void *arg);

/****************************************************************************
 * Name: ra_sdhi_mediachange
 *
 * Description:
 *   Called by board-specific logic when a card is inserted or removed.
 *   This function can be called from interrupt context.
 *
 * Input Parameters:
 *   dev      - An instance of the SDIO device interface
 *   inserted - True if card is inserted
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

void ra_sdhi_mediachange(struct sdio_dev_s *dev, bool inserted);

/****************************************************************************
 * Name: ra_sdhi_wrprotect
 *
 * Description:
 *   Called by board-specific logic to check write-protect status.
 *
 * Input Parameters:
 *   dev - An instance of the SDIO device interface
 *
 * Returned Value:
 *   True if card is write protected
 *
 ****************************************************************************/

bool ra_sdhi_wrprotect(struct sdio_dev_s *dev);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RA8_RA_SDHI_H */

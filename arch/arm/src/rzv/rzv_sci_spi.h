/****************************************************************************
 * arch/arm/src/rzv/rzv_sci_spi.h
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

#ifndef __ARCH_ARM_SRC_RZV_RZV_SCI_SPI_H
#define __ARCH_ARM_SRC_RZV_RZV_SCI_SPI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>
#include <nuttx/spi/spi.h>
#include <nuttx/semaphore.h>
#include "rzv_gpio.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCI_B SPI Configuration */

#define RZV_SCI_SPI_MAX_FREQUENCY     50000000  /* Maximum SPI frequency (50 MHz) */
#define RZV_SCI_SPI_MIN_FREQUENCY     1000      /* Minimum SPI frequency */

/* SCI_B SPI Bus numbers */

#define RZV_SCI_SPI_BUS_0             0
#define RZV_SCI_SPI_BUS_1             1
#define RZV_SCI_SPI_BUS_2             2
#define RZV_SCI_SPI_BUS_3             3
#define RZV_SCI_SPI_BUS_4             4
#define RZV_SCI_SPI_BUS_5             5
#define RZV_SCI_SPI_BUS_6             6
#define RZV_SCI_SPI_BUS_7             7
#define RZV_SCI_SPI_BUS_8             8
#define RZV_SCI_SPI_BUS_9             9

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* SCI_B SPI callback function type */

typedef void (*sci_spi_callback_t)(void *arg);

/* SCI_B SPI chip select type */

typedef enum
{
  RZV_SCI_SPI_CS_GPIO = 0,        /* Use GPIO for chip select */
  RZV_SCI_SPI_CS_HARDWARE = 1     /* Use hardware SSx pin for chip select */
} rzv_sci_spi_cs_type;

/* SCI_B SPI data direction */

typedef enum
{
  RZV_SCI_SPI_DIR_MSB_FIRST = 0,  /* MSB first */
  RZV_SCI_SPI_DIR_LSB_FIRST = 1   /* LSB first */
} rzv_sci_spi_dir_type;

/* SCI_B SPI clock source */

typedef enum
{
  RZV_SCI_SPI_CLOCK_PCLK = 0,      /* Use PCLK */
  RZV_SCI_SPI_CLOCK_PCLK_DIV4 = 1, /* Use PCLK/4 */
  RZV_SCI_SPI_CLOCK_PCLK_DIV16 = 2,/* Use PCLK/16 */
  RZV_SCI_SPI_CLOCK_PCLK_DIV64 = 3 /* Use PCLK/64 */
} rzv_sci_spi_clock_source_t;

/* SCI_B SPI device external configuration
 * Extended configuration for individual devices on the SPI bus
 */

struct rzv_sci_spi_ext_dev_config_s
{
  uint32_t devid;              /* Device ID */
  uint32_t max_frequency;      /* Maximum frequency for this device */
  uint8_t  cur_mode;           /* SPI mode (0-3) */
  uint8_t  cur_bits;           /* Data bits per transfer (8-bit only for SCI_B SPI) */
  rzv_sci_spi_dir_type cur_dir; /* Data direction (MSB/LSB first) */
  gpio_pinset_t cs_gpio;       /* GPIO Chip Select pin definition */
  rzv_sci_spi_cs_type cs_type; /* CS type: GPIO or hardware */
  bool     active_low;         /* CS active low */
  const char *name;            /* Device name for debugging */
  int use_dtc;                 /* Use DTC for transfers (not yet implemented) */
  int use_dma;                 /* Use DMA for transfers (not yet implemented) */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_sci_spibus_initialize
 *
 * Description:
 *   Initialize the selected SCI_B SPI bus
 *
 * Input Parameters:
 *   bus number (for hardware that has multiple SCI_B SPI interfaces)
 *
 * Returned Value:
 *   Valid SPI device structure reference on success; a NULL on failure
 *
 ****************************************************************************/

struct spi_dev_s *rzv_sci_spibus_initialize(int bus);

/****************************************************************************
 * Name: rzv_sci_spibus_uninitialize
 *
 * Description:
 *   Uninitialize the selected SCI_B SPI bus (cleanup for power management)
 *
 * Input Parameters:
 *   dev - SPI device structure
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_sci_spibus_uninitialize(struct spi_dev_s *dev);

/****************************************************************************
 * Name: rzv_sci_spi_register_callback
 *
 * Description:
 *   Register a callback that will be invoked on any SCI_B SPI completion
 *   or error
 *
 ****************************************************************************/

int rzv_sci_spi_register_callback(struct spi_dev_s *dev,
                                  sci_spi_callback_t callback,
                                  void *arg);

/****************************************************************************
 * Name: rzv_sci_spi_select
 *
 * Description:
 *   Control the chip select (weak function, should be overridden by board)
 *
 ****************************************************************************/

void rzv_sci_spi_select(struct spi_dev_s *dev, uint32_t devid,
                        bool selected);

/****************************************************************************
 * Name: rzv_sci_spi_status
 *
 * Description:
 *   Return status information associated with the SCI_B SPI device
 *
 ****************************************************************************/

uint8_t rzv_sci_spi_status(struct spi_dev_s *dev, uint32_t devid);

#ifdef CONFIG_SPI_CMDDATA
/****************************************************************************
 * Name: rzv_sci_spi_cmddata
 *
 * Description:
 *   Control the SCI_B SPI CMD/DATA line if supported by the device
 *
 ****************************************************************************/

int rzv_sci_spi_cmddata(struct spi_dev_s *dev, uint32_t devid, bool cmd);
#endif

/****************************************************************************
 * Name: rzv_sci_spi_get_dev_config
 *
 * Description:
 *   Get CS configuration for a specific device (weak function)
 *
 ****************************************************************************/

const struct rzv_sci_spi_ext_dev_config_s *
rzv_sci_spi_get_dev_config(struct spi_dev_s *dev, uint32_t devid);

/****************************************************************************
 * Name: rzv_sci_spi_setbitorder
 *
 * Description:
 *   Set the SCI_B SPI bit order (MSB-first or LSB-first)
 *
 * Input Parameters:
 *   dev      - The SPI device handle
 *   lsbfirst - true for LSB-first, false for MSB-first
 *
 ****************************************************************************/

void rzv_sci_spi_setbitorder(struct spi_dev_s *dev, bool lsbfirst);

#endif /* __ARCH_ARM_SRC_RZV_RZV_SCI_SPI_H */

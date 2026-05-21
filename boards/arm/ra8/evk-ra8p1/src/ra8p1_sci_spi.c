/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_sci_spi.c
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

#include <stdint.h>
#include <stdbool.h>
#include <debug.h>

#include <nuttx/spi/spi.h>
#include <nuttx/spi/spi_transfer.h>
#include <arch/board/board.h>

#include "arm_internal.h"
#include "chip.h"
#include "ra_gpio.h"
#include "ra_sci_spi.h"

#ifdef CONFIG_RA_SCI_SPI

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCI0_SPI on PMOD2 (J25) */
#define DEVID_SCI0_SPI_MAX31723   0  /* Temperature sensor */

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* SCI0_SPI device configurations */
static const struct ra_sci_spi_ext_dev_config_s g_sci0_spi_devconfig[] =
{
  {
    .devid          = DEVID_SCI0_SPI_MAX31723,
    .max_frequency  = 50000,        /* 50 kHz for MAX31723 */
    .cur_mode       = SPIDEV_MODE0,
    .cur_bits       = 8,
    .cur_dir        = RA_SCI_SPI_DIR_MSB_FIRST,
    .cs_gpio        = GPIO_SCI0_SPI_CS,
    .cs_type        = RA_SCI_SPI_CS_GPIO,
    .active_low     = false,        /* MAX31723 CS is active high */
    .name           = "MAX31723",
    .use_dtc        = 1,
  },
};

#define NSCI0_SPI_DEVICES (sizeof(g_sci0_spi_devconfig) / \
                           sizeof(struct ra_sci_spi_ext_dev_config_s))

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_sci_spi_select
 *
 * Description:
 *   Select or deselect the SPI device
 *
 ****************************************************************************/

void ra_sci_spi_select(struct spi_dev_s *dev, uint32_t devid,
                       bool selected)
{
  const struct ra_sci_spi_ext_dev_config_s *config = NULL;
  int i;

  spiinfo("devid: %lu, selected: %d\n", devid, selected);

  /* Find the device configuration */
#ifdef CONFIG_RA_SCI0_SPI
  for (i = 0; i < NSCI0_SPI_DEVICES; i++)
    {
      if (g_sci0_spi_devconfig[i].devid == devid)
        {
          config = &g_sci0_spi_devconfig[i];
          break;
        }
    }
#endif

  if (config == NULL)
    {
      spierr("ERROR: Device %lu not found\n", devid);
      return;
    }

  /* Handle CS based on configuration */
  if (config->cs_type == RA_SCI_SPI_CS_GPIO)
    {
      /* GPIO CS control */
      bool output_value;

      if (config->active_low)
        {
          output_value = !selected;  /* Active low */
        }
      else
        {
          output_value = selected;   /* Active high */
        }

      ra_gpiowrite(config->cs_gpio, output_value);

      spiinfo("GPIO CS: pin=0x%08lx, value=%d\n",
              config->cs_gpio, output_value);
    }
  else
    {
      /* Hardware CS - not yet implemented */
      spierr("ERROR: Hardware CS not supported yet\n");
    }
}

/****************************************************************************
 * Name: ra_sci_spi_status
 *
 * Description:
 *   Return status information associated with the SPI device
 *
 ****************************************************************************/

uint8_t ra_sci_spi_status(struct spi_dev_s *dev, uint32_t devid)
{
  return 0;
}

/****************************************************************************
 * Name: ra_sci_spi_get_dev_config
 *
 * Description:
 *   Get device-specific configuration
 *
 ****************************************************************************/

const struct ra_sci_spi_ext_dev_config_s *
ra_sci_spi_get_dev_config(struct spi_dev_s *dev, uint32_t devid)
{
  int i;

#ifdef CONFIG_RA_SCI0_SPI
  for (i = 0; i < NSCI0_SPI_DEVICES; i++)
    {
      if (g_sci0_spi_devconfig[i].devid == devid)
        {
          return &g_sci0_spi_devconfig[i];
        }
    }
#endif

  return NULL;
}

/****************************************************************************
 * Name: board_sci_spi_initialize
 *
 * Description:
 *   Initialize SCI_SPI interfaces for the board
 *
 ****************************************************************************/

int board_sci_spi_initialize(void)
{
  struct spi_dev_s *spi;
  int ret = OK;

#ifdef CONFIG_RA_SCI0_SPI
  spiinfo("Initializing SCI0_SPI\n");

  /* Configure GPIO pins for SCI0_SPI (PMOD2) */
  ra_gpioconfig(GPIO_SCI0_SPI_SCK);   /* P601 - SCK */
  ra_gpioconfig(GPIO_SCI0_SPI_MISO);  /* P602 - MISO (RXD0) */
  ra_gpioconfig(GPIO_SCI0_SPI_MOSI);  /* P603 - MOSI (TXD0) */

  /* Configure CS pins as GPIO outputs */
  ra_gpioconfig(GPIO_SCI0_SPI_CS);    /* P604 - CS */
  ra_gpiowrite(GPIO_SCI0_SPI_CS, 0);  /* Deselect (active high device) */

  /* Initialize SCI0_SPI interface */
  spi = ra_sci_spibus_initialize(0);
  if (spi == NULL)
    {
      spierr("ERROR: Failed to initialize SCI0_SPI\n");
      return -ENODEV;
    }

  /* Register the SPI device */
  ret = spi_register(spi, 0);
  if (ret < 0)
    {
      spierr("ERROR: Failed to register SCI0_SPI: %d\n", ret);
      return ret;
    }

  spiinfo("SCI0_SPI initialized successfully\n");
#endif

  return ret;
}

#endif /* CONFIG_RA_SCI_SPI */

/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_sci_spi.c
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
#include <errno.h>
#include <debug.h>

#include <nuttx/spi/spi.h>
#include <nuttx/spi/spi_transfer.h>
#include <arch/board/board.h>

#include "arm_internal.h"
#include "rzv_gpio.h"
#include "rzv_sci_spi.h"
#include "rdk-rzv2h.h"

#ifdef CONFIG_RZV_SCI_SPI

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCI0 SPI Pin Configuration for RDK-RZV2H */

#define RZV_SCI0_MOSI_PIN  (GPIO_TXD0_MOSI0_DA0_P5_0_M1)   /* P5_0 - SCI0 TX (MOSI) */
#define RZV_SCI0_MISO_PIN  (GPIO_RXD0_MISO0_SCL0_P5_1_M1)  /* P5_1 - SCI0 RX (MISO) */
#define RZV_SCI0_SCK_PIN   (GPIO_SCK0_P6_0_M1)             /* P6_0 - SCI0 SCK */
#define RZV_SCI0_CS_PIN    (PORT6 | PIN1 | RZV_GPIO_OUTPUT | RZV_GPIO_DRVSTR_NORMAL | RZV_GPIO_INITIAL_HIGH)  /* P6_1 - GPIO CS */

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_sci0_spi_setup
 *
 * Description:
 *   Setup GPIO pins for SCI0 SPI
 *
 ****************************************************************************/

static void rzv2h_sci0_spi_setup(void)
{
  /* Configure SCI0 pins for SPI mode */

  /* TX (MOSI) - Output, peripheral function */

  rzv_configgpio(RZV_SCI0_MOSI_PIN);

  /* RX (MISO) - Input, peripheral function */

  rzv_configgpio(RZV_SCI0_MISO_PIN);

  /* SCK - Output, peripheral function */

  rzv_configgpio(RZV_SCI0_SCK_PIN);

  /* CS - GPIO output, initially high (inactive) */

  rzv_configgpio(RZV_SCI0_CS_PIN);

  spiinfo("SCI0 SPI pins configured\n");
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_sci_spi_select
 *
 * Description:
 *   Select/deselect the SPI device specified by devid
 *
 * Input Parameters:
 *   dev - SPI device handle
 *   devid - Device ID
 *   selected - true: select device, false: deselect device
 *
 ****************************************************************************/

void rzv_sci_spi_select(struct spi_dev_s *dev, uint32_t devid,
                        bool selected)
{
  spiinfo("devid: %lu selected: %d\n", (unsigned long)devid, selected);

  switch (devid)
    {
#ifdef CONFIG_RZV_SCI0_SPI
      case SPIDEV_NONE(0):
      case SPIDEV_USER(0):
        /* Control CS pin */

        rzv_gpiowrite(RZV_SCI0_CS_PIN, !selected);
        break;
#endif

      default:
        break;
    }
}

/****************************************************************************
 * Name: rzv_sci_spi_status
 *
 * Description:
 *   Return status information associated with the SPI device
 *
 * Input Parameters:
 *   dev - SPI device handle
 *   devid - Device ID
 *
 * Returned Value:
 *   Bit-encoded status byte
 *
 ****************************************************************************/

uint8_t rzv_sci_spi_status(struct spi_dev_s *dev, uint32_t devid)
{
  uint8_t status = 0;

  switch (devid)
    {
#ifdef CONFIG_RZV_SCI0_SPI
      case SPIDEV_NONE(0):
      case SPIDEV_USER(0):
        /* Return SPI_STATUS_PRESENT if device is present */

        status |= SPI_STATUS_PRESENT;
        break;
#endif

      default:
        break;
    }

  return status;
}

#ifdef CONFIG_SPI_CMDDATA
/****************************************************************************
 * Name: rzv_sci_spi_cmddata
 *
 * Description:
 *   Control the SPI CMD/DATA line (if applicable)
 *
 * Input Parameters:
 *   dev - SPI device handle
 *   devid - Device ID
 *   cmd - true: command, false: data
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_sci_spi_cmddata(struct spi_dev_s *dev, uint32_t devid, bool cmd)
{
  /* SCI_B SPI doesn't have hardware CMD/DATA support */

  /* This would need to be implemented using a GPIO pin if required */

  return -ENODEV;
}
#endif

/****************************************************************************
 * Name: board_sci_spi_initialize
 *
 * Description:
 *   Initialize SCI_B SPI buses
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int board_sci_spi_initialize(void)
{
  struct spi_dev_s *spi;
  int ret = OK;

#ifdef CONFIG_RZV_SCI0_SPI
  /* Setup SCI0 SPI pins */

  rzv2h_sci0_spi_setup();

  /* Initialize SCI0 SPI bus */

  spi = rzv_sci_spibus_initialize(0);
  if (spi == NULL)
    {
      spierr("ERROR: Failed to initialize SCI0 SPI bus\n");
      return -ENODEV;
    }

  /* Register the SPI driver for user-space access */

#ifdef CONFIG_SPI_DRIVER
  ret = spi_register(spi, 0);
  if (ret < 0)
    {
      spierr("ERROR: Failed to register SCI0 SPI driver: %d\n", ret);
      return ret;
    }
#endif

  spiinfo("SCI0 SPI bus initialized\n");
#endif

  return ret;
}

#endif /* CONFIG_RZV_SCI_SPI */

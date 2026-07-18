/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_spi.c
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

/* Implement board SPI GPIO MUX for RZ/V2H RDK.
 *
 * SPI0 (RSPI4) on PORT9 — pin assignments from rzv2h_pinmap.h:
 *   MOSA  (MOSI): P9_0  MODE1  GPIO_MOSA_P9_0_M1
 *   MISO4 (MISO): P9_1  MODE1  GPIO_MISO4_P9_1_M1
 *   RSPCK4(SCK) : P9_2  MODE1  GPIO_RSPCK4_P9_2_M1
 *   SSLA0 (CS0) : P9_3  MODE1  GPIO_SSLA0_P9_3_M1
 *
 * NOTE: The pinmap provides "RSPI4" function names (channel 4 = hardware
 * SPI0 at 0x12800000).  UNVERIFIED against RDK-RZV2H schematic — board bring-up
 * engineer must confirm physical routing before enabling.
 *
 * rzv_spi_select() override uses GPIO CS for SPI0.
 * SSLA0 driven manually (GPIO output) rather than hardware-SSL so that
 * the board file can assert different polarity / pre/post delays as needed.
 */

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_SPI

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <debug.h>
#include <syslog.h>

#include <nuttx/spi/spi.h>
#include <nuttx/spi/spi_transfer.h>
#include <arch/board/board.h>

#include "arm_internal.h"
#include "rzv_gpio.h"
#include "rzv_spi.h"
#include "hardware/rzv2h/rzv2h_pinmap.h"
#include "rdk-rzv2h.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SPI0 GPIO pin assignments (RSPI4 function, PORT9)
 * All pins use RZV_GPIO_PERIPH to hand control to the peripheral mux.
 * SSLA0 is configured separately as GPIO output for software CS.
 */

#define SPI0_MOSI_PIN    (GPIO_MOSA_P9_0_M1   | RZV_GPIO_PERIPH)
#define SPI0_MISO_PIN    (GPIO_MISO4_P9_1_M1  | RZV_GPIO_PERIPH)
#define SPI0_SCK_PIN     (GPIO_RSPCK4_P9_2_M1 | RZV_GPIO_PERIPH)

/* CS0 driven as GPIO output, active-low; deasserted (high) at boot.
 * Build the pinset manually to avoid relying on GPIO_OUTPUT_HIGH which may
 * be #ifndef-guarded and shadowed by board.h before rzv_gpio.h is parsed.
 * RZV_GPIO_OUTPUT=bit[17:16]=0b01, RZV_GPIO_INITIAL_HIGH=bit23=1.
 */

#define SPI0_CS0_GPIO    (GPIO_PIN(9, 3) | RZV_GPIO_OUTPUT | \
                          RZV_GPIO_DRVSTR_NORMAL | RZV_GPIO_INITIAL_HIGH)

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Track which SPI devices have been initialised */

#ifdef CONFIG_RZV_SPI0
static struct spi_dev_s *g_spi0_dev;
#endif
#ifdef CONFIG_RZV_SPI1
static struct spi_dev_s *g_spi1_dev;
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_spi_select  (strong override of driver's weak default)
 *
 * Description:
 *   Assert or deassert the chip-select for the given device on SPI0.
 * board file provides GPIO CS rather than hardware SSL.
 *
 *   devid == SPIDEV_USER(0) → SPI0 CS0 (P9_3, active-low).
 *   Other devids: no-op with warning.
 *
 ****************************************************************************/

void rzv_spi_select(struct spi_dev_s *dev, uint32_t devid, bool selected)
{
  UNUSED(dev);

  switch (devid)
    {
      case SPIDEV_USER(0):
        /* Active-low CS: assert = drive low, deassert = drive high */

        rzv_gpiowrite(SPI0_CS0_GPIO, !selected);
        spiinfo("SPI0 CS0 %s\n", selected ? "asserted" : "deasserted");
        break;

      default:
        spiwarn("rzv_spi_select: unknown devid 0x%08lx\n",
                (unsigned long)devid);
        break;
    }
}

/****************************************************************************
 * Name: rzv_spi_status  (strong override)
 *
 * Description:
 *   Return SPI device status. SPI_STATUS_PRESENT for all known devices.
 *
 ****************************************************************************/

uint8_t rzv_spi_status(struct spi_dev_s *dev, uint32_t devid)
{
  UNUSED(dev);
  UNUSED(devid);
  return SPI_STATUS_PRESENT;
}

/****************************************************************************
 * Name: rzv2h_board_spi0_pinmux
 *
 * Description:
 *   Configure PORT9 pin mux for SPI0 (RSPI4 function) MOSI/MISO/SCK and
 *   drive CS0 as an active-low GPIO output.
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_SPI0
static int rzv2h_board_spi0_pinmux(void)
{
  int ret;

  ret = rzv_gpioconfig(SPI0_MOSI_PIN);
  if (ret < 0)
    {
      syslog(LOG_ERR, "SPI0 MOSI pin config failed: %d\n", ret);
      return ret;
    }

  ret = rzv_gpioconfig(SPI0_MISO_PIN);
  if (ret < 0)
    {
      syslog(LOG_ERR, "SPI0 MISO pin config failed: %d\n", ret);
      return ret;
    }

  ret = rzv_gpioconfig(SPI0_SCK_PIN);
  if (ret < 0)
    {
      syslog(LOG_ERR, "SPI0 SCK pin config failed: %d\n", ret);
      return ret;
    }

  ret = rzv_gpioconfig(SPI0_CS0_GPIO);
  if (ret < 0)
    {
      syslog(LOG_ERR, "SPI0 CS0 pin config failed: %d\n", ret);
      return ret;
    }

  rzv_gpiowrite(SPI0_CS0_GPIO, true);  /* Deassert (active-low) */
  return OK;
}
#endif

/****************************************************************************
 * Name: rzv2h_board_spi_bringup
 *
 * Description:
 *   Per-channel SPI bring-up: pin mux (channel-specific), call
 *   rzv_spibus_initialize(port), optionally register /dev/spiN.
 *   SPI1 currently has no external pin routing on RDK-RZV2H so pin mux
 *   is skipped for that channel — it is usable only via internal
 *   loopback (SPCR2.SPLP) until the board provides external routing.
 *
 ****************************************************************************/

static int rzv2h_board_spi_bringup(int port, struct spi_dev_s **out_dev)
{
  struct spi_dev_s *dev;
  int ret;

  switch (port)
    {
#ifdef CONFIG_RZV_SPI0
      case 0:
        ret = rzv2h_board_spi0_pinmux();
        if (ret < 0)
          {
            return ret;
          }
        break;
#endif
#ifdef CONFIG_RZV_SPI1
      case 1:
        /* No external pin routing for SPI1 on RDK-RZV2H — internal
         * loopback (SPCR2.SPLP) is the only usable mode until board
         * routing is added.
         */
        break;
#endif
      default:
        return -EINVAL;
    }

  dev = rzv_spibus_initialize(port);
  if (dev == NULL)
    {
      syslog(LOG_ERR, "rzv_spibus_initialize(%d) failed\n", port);
      return -ENODEV;
    }

  *out_dev = dev;
  syslog(LOG_INFO, "SPI%d initialized\n", port);

#ifdef CONFIG_SPI_DRIVER
  ret = spi_register(dev, port);
  if (ret < 0)
    {
      syslog(LOG_ERR, "spi_register(%d) failed: %d\n", port, ret);
      return ret;
    }

  syslog(LOG_INFO, "Registered /dev/spi%d\n", port);
#endif

  return OK;
}

/****************************************************************************
 * Name: board_spi_initialize
 *
 * Description:
 *   Called by rzv2h_bringup.c under CONFIG_RZV_SPI.  Iterates every
 *   Kconfig-enabled SPI channel and brings it up.  Repeat calls
 *   (e.g., from a sample wrapper) are safe: rzv_spibus_initialize()
 *   is idempotent.
 *
 ****************************************************************************/

int board_spi_initialize(void)
{
  int ret;

#ifdef CONFIG_RZV_SPI0
  ret = rzv2h_board_spi_bringup(0, &g_spi0_dev);
  if (ret < 0)
    {
      return ret;
    }
#endif

#ifdef CONFIG_RZV_SPI1
  ret = rzv2h_board_spi_bringup(1, &g_spi1_dev);
  if (ret < 0)
    {
      return ret;
    }
#endif

  return OK;
}

#endif /* CONFIG_RZV_SPI */

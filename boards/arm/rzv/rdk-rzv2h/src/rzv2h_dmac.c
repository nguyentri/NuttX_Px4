/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_dmac.c
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
#include <errno.h>

#include <nuttx/irq.h>

#include "rzv_dmac.h"
#include "rdk-rzv2h.h"

#ifdef CONFIG_RZV_DMAC

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Channel allocation map - matches Kconfig assignments */

#define DMAC_CHANNEL_UNASSIGNED  (-1)

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Channel assignment tracking */

static struct
{
  int uart0_rx;
  int uart0_tx;
  int uart1_rx;
  int uart1_tx;
  int uart2_rx;
  int uart2_tx;
  int i2c0;
  int i2c1;
  int i2c2;
  int spi0_rx;
  int spi0_tx;
  int spi1_rx;
  int spi1_tx;
  int adc;
  int sdhi;
} g_dmac_channels =
{
#ifdef CONFIG_RZV_DMAC_UART0_RX_CHANNEL
  .uart0_rx = CONFIG_RZV_DMAC_UART0_RX_CHANNEL,
#else
  .uart0_rx = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_UART0_TX_CHANNEL
  .uart0_tx = CONFIG_RZV_DMAC_UART0_TX_CHANNEL,
#else
  .uart0_tx = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_UART1_RX_CHANNEL
  .uart1_rx = CONFIG_RZV_DMAC_UART1_RX_CHANNEL,
#else
  .uart1_rx = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_UART1_TX_CHANNEL
  .uart1_tx = CONFIG_RZV_DMAC_UART1_TX_CHANNEL,
#else
  .uart1_tx = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_UART2_RX_CHANNEL
  .uart2_rx = CONFIG_RZV_DMAC_UART2_RX_CHANNEL,
#else
  .uart2_rx = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_UART2_TX_CHANNEL
  .uart2_tx = CONFIG_RZV_DMAC_UART2_TX_CHANNEL,
#else
  .uart2_tx = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_I2C0_CHANNEL
  .i2c0 = CONFIG_RZV_DMAC_I2C0_CHANNEL,
#else
  .i2c0 = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_I2C1_CHANNEL
  .i2c1 = CONFIG_RZV_DMAC_I2C1_CHANNEL,
#else
  .i2c1 = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_I2C2_CHANNEL
  .i2c2 = CONFIG_RZV_DMAC_I2C2_CHANNEL,
#else
  .i2c2 = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_SPI0_RX_CHANNEL
  .spi0_rx = CONFIG_RZV_DMAC_SPI0_RX_CHANNEL,
#else
  .spi0_rx = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_SPI0_TX_CHANNEL
  .spi0_tx = CONFIG_RZV_DMAC_SPI0_TX_CHANNEL,
#else
  .spi0_tx = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_SPI1_RX_CHANNEL
  .spi1_rx = CONFIG_RZV_DMAC_SPI1_RX_CHANNEL,
#else
  .spi1_rx = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_SPI1_TX_CHANNEL
  .spi1_tx = CONFIG_RZV_DMAC_SPI1_TX_CHANNEL,
#else
  .spi1_tx = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_ADC_CHANNEL
  .adc = CONFIG_RZV_DMAC_ADC_CHANNEL,
#else
  .adc = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_SDHI_CHANNEL
  .sdhi = CONFIG_RZV_DMAC_SDHI_CHANNEL,
#else
  .sdhi = DMAC_CHANNEL_UNASSIGNED,
#endif
};

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_dmac_setup
 *
 * Description:
 *   Initialize the DMAC for the RDK-RZV2H board. This function initializes
 *   all DMAC units that have channels assigned via Kconfig.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int rzv2h_dmac_setup(void)
{
  int ret;
  bool units_used[5] = { false, false, false, false, false };

  dmainfo("RDK-RZV2H: Initializing DMAC\n");

  /* Determine which DMAC units are in use based on channel assignments */

  if (g_dmac_channels.uart0_rx >= 0)
    {
      units_used[g_dmac_channels.uart0_rx / 16] = true;
    }

  if (g_dmac_channels.uart0_tx >= 0)
    {
      units_used[g_dmac_channels.uart0_tx / 16] = true;
    }

  if (g_dmac_channels.uart1_rx >= 0)
    {
      units_used[g_dmac_channels.uart1_rx / 16] = true;
    }

  if (g_dmac_channels.uart1_tx >= 0)
    {
      units_used[g_dmac_channels.uart1_tx / 16] = true;
    }

  if (g_dmac_channels.uart2_rx >= 0)
    {
      units_used[g_dmac_channels.uart2_rx / 16] = true;
    }

  if (g_dmac_channels.uart2_tx >= 0)
    {
      units_used[g_dmac_channels.uart2_tx / 16] = true;
    }

  if (g_dmac_channels.i2c0 >= 0)
    {
      units_used[g_dmac_channels.i2c0 / 16] = true;
    }

  if (g_dmac_channels.i2c1 >= 0)
    {
      units_used[g_dmac_channels.i2c1 / 16] = true;
    }

  if (g_dmac_channels.i2c2 >= 0)
    {
      units_used[g_dmac_channels.i2c2 / 16] = true;
    }

  if (g_dmac_channels.spi0_rx >= 0)
    {
      units_used[g_dmac_channels.spi0_rx / 16] = true;
    }

  if (g_dmac_channels.spi0_tx >= 0)
    {
      units_used[g_dmac_channels.spi0_tx / 16] = true;
    }

  if (g_dmac_channels.spi1_rx >= 0)
    {
      units_used[g_dmac_channels.spi1_rx / 16] = true;
    }

  if (g_dmac_channels.spi1_tx >= 0)
    {
      units_used[g_dmac_channels.spi1_tx / 16] = true;
    }

  if (g_dmac_channels.adc >= 0)
    {
      units_used[g_dmac_channels.adc / 16] = true;
    }

  if (g_dmac_channels.sdhi >= 0)
    {
      units_used[g_dmac_channels.sdhi / 16] = true;
    }

  /* Initialize units that are in use */

  for (int i = 0; i < 5; i++)
    {
      if (units_used[i])
        {
          /* Initialize first channel of each unit to trigger unit init */

          ret = rzv_dmac_channel_initialize(i * 16);
          if (ret < 0)
            {
              dmaerr("Failed to initialize DMAC unit %d: %d\n", i, ret);
              return ret;
            }

          dmainfo("DMAC unit %d initialized\n", i);
        }
    }

  /* Print channel allocation summary */

#ifdef CONFIG_RZV_DMAC_DEBUG
  dmainfo("DMAC Channel Assignments:\n");
  if (g_dmac_channels.uart0_rx >= 0)
    {
      dmainfo("  UART0 RX: Channel %d\n", g_dmac_channels.uart0_rx);
    }

  if (g_dmac_channels.uart0_tx >= 0)
    {
      dmainfo("  UART0 TX: Channel %d\n", g_dmac_channels.uart0_tx);
    }

  if (g_dmac_channels.uart1_rx >= 0)
    {
      dmainfo("  UART1 RX: Channel %d\n", g_dmac_channels.uart1_rx);
    }

  if (g_dmac_channels.uart1_tx >= 0)
    {
      dmainfo("  UART1 TX: Channel %d\n", g_dmac_channels.uart1_tx);
    }

  if (g_dmac_channels.spi0_rx >= 0)
    {
      dmainfo("  SPI0 RX: Channel %d\n", g_dmac_channels.spi0_rx);
    }

  if (g_dmac_channels.spi0_tx >= 0)
    {
      dmainfo("  SPI0 TX: Channel %d\n", g_dmac_channels.spi0_tx);
    }

  if (g_dmac_channels.i2c0 >= 0)
    {
      dmainfo("  I2C0: Channel %d\n", g_dmac_channels.i2c0);
    }

  if (g_dmac_channels.sdhi >= 0)
    {
      dmainfo("  SDHI: Channel %d\n", g_dmac_channels.sdhi);
    }
#endif

  return OK;
}

/****************************************************************************
 * Name: rzv2h_dmac_get_channel
 *
 * Description:
 *   Get the DMA channel assigned to a specific peripheral.
 *
 * Input Parameters:
 *   peripheral - Peripheral identifier (e.g., "uart0_rx", "spi0_tx")
 *
 * Returned Value:
 *   Channel number (0-79) on success; -1 if not assigned or invalid.
 *
 ****************************************************************************/

int rzv2h_dmac_get_channel(const char *peripheral)
{
  if (peripheral == NULL)
    {
      return -1;
    }

  if (strcmp(peripheral, "uart0_rx") == 0)
    {
      return g_dmac_channels.uart0_rx;
    }
  else if (strcmp(peripheral, "uart0_tx") == 0)
    {
      return g_dmac_channels.uart0_tx;
    }
  else if (strcmp(peripheral, "uart1_rx") == 0)
    {
      return g_dmac_channels.uart1_rx;
    }
  else if (strcmp(peripheral, "uart1_tx") == 0)
    {
      return g_dmac_channels.uart1_tx;
    }
  else if (strcmp(peripheral, "uart2_rx") == 0)
    {
      return g_dmac_channels.uart2_rx;
    }
  else if (strcmp(peripheral, "uart2_tx") == 0)
    {
      return g_dmac_channels.uart2_tx;
    }
  else if (strcmp(peripheral, "i2c0") == 0)
    {
      return g_dmac_channels.i2c0;
    }
  else if (strcmp(peripheral, "i2c1") == 0)
    {
      return g_dmac_channels.i2c1;
    }
  else if (strcmp(peripheral, "i2c2") == 0)
    {
      return g_dmac_channels.i2c2;
    }
  else if (strcmp(peripheral, "spi0_rx") == 0)
    {
      return g_dmac_channels.spi0_rx;
    }
  else if (strcmp(peripheral, "spi0_tx") == 0)
    {
      return g_dmac_channels.spi0_tx;
    }
  else if (strcmp(peripheral, "spi1_rx") == 0)
    {
      return g_dmac_channels.spi1_rx;
    }
  else if (strcmp(peripheral, "spi1_tx") == 0)
    {
      return g_dmac_channels.spi1_tx;
    }
  else if (strcmp(peripheral, "adc") == 0)
    {
      return g_dmac_channels.adc;
    }
  else if (strcmp(peripheral, "sdhi") == 0)
    {
      return g_dmac_channels.sdhi;
    }

  return -1;
}

#endif /* CONFIG_RZV_DMAC */

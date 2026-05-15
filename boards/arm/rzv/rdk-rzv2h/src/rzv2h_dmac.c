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
#include <string.h>
#include <assert.h>
#include <debug.h>
#include <errno.h>

#include <nuttx/irq.h>

#include "hardware/rzv_dmac.h"
#include "rzv_dmac.h"
#include "rdk-rzv2h.h"

#ifdef CONFIG_RZV_DMAC

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define DMAC_CHANNEL_UNASSIGNED  (-1)

/* Collision detection (H4): every Kconfig-assigned channel must be unique.
 * We cannot use static_assert with Kconfig values (they may be -1 for
 * "disabled"), so we use runtime panic in rzv2h_dmac_initialize.
 * Build-time check is possible only when all channels are known non-negative.
 *
 * The CHECK_PAIR macro evaluates two assigned channels for equality; both
 * must be >= 0 for a collision to exist.
 */

#define DMAC_COLLISION_CHECK(a, b, na, nb)                    \
  do                                                          \
    {                                                         \
      if ((a) >= 0 && (b) >= 0 && (a) == (b))                \
        {                                                     \
          _alert("DMAC channel collision: %s and %s both on " \
                 "channel %d — fix Kconfig\n", na, nb, (a)); \
          PANIC();                                            \
        }                                                     \
    }                                                         \
  while (0)

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* Peripheral identifier enum replaces runtime strcmp lookup (M7).
 * Compile-time table: g_dmac_channel_map[] indexed by this enum.
 */

typedef enum
{
  DMAC_PERIPH_UART0_RX = 0,
  DMAC_PERIPH_UART0_TX,
  DMAC_PERIPH_UART1_RX,
  DMAC_PERIPH_UART1_TX,
  DMAC_PERIPH_UART2_RX,
  DMAC_PERIPH_UART2_TX,
  DMAC_PERIPH_I2C0,
  DMAC_PERIPH_I2C1,
  DMAC_PERIPH_I2C2,
  DMAC_PERIPH_SPI0_RX,
  DMAC_PERIPH_SPI0_TX,
  DMAC_PERIPH_SPI1_RX,
  DMAC_PERIPH_SPI1_TX,
  DMAC_PERIPH_ADC,
  DMAC_PERIPH_SDHI,
  DMAC_PERIPH_COUNT  /* sentinel — keep last */
} rzv2h_dmac_periph_t;

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Channel assignment table indexed by rzv2h_dmac_periph_t.
 * Populated from Kconfig at init time; -1 means unassigned.
 */

static int g_dmac_channel_map[DMAC_PERIPH_COUNT] =
{
#ifdef CONFIG_RZV_DMAC_UART0_RX_CHANNEL
  [DMAC_PERIPH_UART0_RX] = CONFIG_RZV_DMAC_UART0_RX_CHANNEL,
#else
  [DMAC_PERIPH_UART0_RX] = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_UART0_TX_CHANNEL
  [DMAC_PERIPH_UART0_TX] = CONFIG_RZV_DMAC_UART0_TX_CHANNEL,
#else
  [DMAC_PERIPH_UART0_TX] = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_UART1_RX_CHANNEL
  [DMAC_PERIPH_UART1_RX] = CONFIG_RZV_DMAC_UART1_RX_CHANNEL,
#else
  [DMAC_PERIPH_UART1_RX] = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_UART1_TX_CHANNEL
  [DMAC_PERIPH_UART1_TX] = CONFIG_RZV_DMAC_UART1_TX_CHANNEL,
#else
  [DMAC_PERIPH_UART1_TX] = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_UART2_RX_CHANNEL
  [DMAC_PERIPH_UART2_RX] = CONFIG_RZV_DMAC_UART2_RX_CHANNEL,
#else
  [DMAC_PERIPH_UART2_RX] = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_UART2_TX_CHANNEL
  [DMAC_PERIPH_UART2_TX] = CONFIG_RZV_DMAC_UART2_TX_CHANNEL,
#else
  [DMAC_PERIPH_UART2_TX] = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_I2C0_CHANNEL
  [DMAC_PERIPH_I2C0]     = CONFIG_RZV_DMAC_I2C0_CHANNEL,
#else
  [DMAC_PERIPH_I2C0]     = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_I2C1_CHANNEL
  [DMAC_PERIPH_I2C1]     = CONFIG_RZV_DMAC_I2C1_CHANNEL,
#else
  [DMAC_PERIPH_I2C1]     = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_I2C2_CHANNEL
  [DMAC_PERIPH_I2C2]     = CONFIG_RZV_DMAC_I2C2_CHANNEL,
#else
  [DMAC_PERIPH_I2C2]     = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_SPI0_RX_CHANNEL
  [DMAC_PERIPH_SPI0_RX]  = CONFIG_RZV_DMAC_SPI0_RX_CHANNEL,
#else
  [DMAC_PERIPH_SPI0_RX]  = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_SPI0_TX_CHANNEL
  [DMAC_PERIPH_SPI0_TX]  = CONFIG_RZV_DMAC_SPI0_TX_CHANNEL,
#else
  [DMAC_PERIPH_SPI0_TX]  = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_SPI1_RX_CHANNEL
  [DMAC_PERIPH_SPI1_RX]  = CONFIG_RZV_DMAC_SPI1_RX_CHANNEL,
#else
  [DMAC_PERIPH_SPI1_RX]  = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_SPI1_TX_CHANNEL
  [DMAC_PERIPH_SPI1_TX]  = CONFIG_RZV_DMAC_SPI1_TX_CHANNEL,
#else
  [DMAC_PERIPH_SPI1_TX]  = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_ADC_CHANNEL
  [DMAC_PERIPH_ADC]      = CONFIG_RZV_DMAC_ADC_CHANNEL,
#else
  [DMAC_PERIPH_ADC]      = DMAC_CHANNEL_UNASSIGNED,
#endif
#ifdef CONFIG_RZV_DMAC_SDHI_CHANNEL
  [DMAC_PERIPH_SDHI]     = CONFIG_RZV_DMAC_SDHI_CHANNEL,
#else
  [DMAC_PERIPH_SDHI]     = DMAC_CHANNEL_UNASSIGNED,
#endif
};

/* Peripheral name table for debug messages — indexed by rzv2h_dmac_periph_t */

static const char * const g_dmac_periph_names[DMAC_PERIPH_COUNT] =
{
  [DMAC_PERIPH_UART0_RX] = "uart0_rx",
  [DMAC_PERIPH_UART0_TX] = "uart0_tx",
  [DMAC_PERIPH_UART1_RX] = "uart1_rx",
  [DMAC_PERIPH_UART1_TX] = "uart1_tx",
  [DMAC_PERIPH_UART2_RX] = "uart2_rx",
  [DMAC_PERIPH_UART2_TX] = "uart2_tx",
  [DMAC_PERIPH_I2C0]     = "i2c0",
  [DMAC_PERIPH_I2C1]     = "i2c1",
  [DMAC_PERIPH_I2C2]     = "i2c2",
  [DMAC_PERIPH_SPI0_RX]  = "spi0_rx",
  [DMAC_PERIPH_SPI0_TX]  = "spi0_tx",
  [DMAC_PERIPH_SPI1_RX]  = "spi1_rx",
  [DMAC_PERIPH_SPI1_TX]  = "spi1_tx",
  [DMAC_PERIPH_ADC]      = "adc",
  [DMAC_PERIPH_SDHI]     = "sdhi",
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_dmac_check_collisions
 *
 * Description:
 *   Runtime channel collision detection (H4). Panics if any two peripherals
 *   are assigned the same DMAC channel number.  O(n²) but called once at
 *   board init so cost is negligible.
 *
 ****************************************************************************/

static void rzv2h_dmac_check_collisions(void)
{
  int i;
  int j;

  for (i = 0; i < DMAC_PERIPH_COUNT; i++)
    {
      if (g_dmac_channel_map[i] < 0)
        {
          continue;
        }

      for (j = i + 1; j < DMAC_PERIPH_COUNT; j++)
        {
          DMAC_COLLISION_CHECK(g_dmac_channel_map[i],
                               g_dmac_channel_map[j],
                               g_dmac_periph_names[i],
                               g_dmac_periph_names[j]);
        }
    }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_dmac_setup
 *
 * Description:
 *   Initialize the DMAC for the RDK-RZV2H board.
 *   1. Check for channel collisions (panics on conflict).
 *   2. Initialize each DMAC unit that has at least one assigned channel.
 *
 ****************************************************************************/

int rzv2h_dmac_setup(void)
{
  bool units_used[RZV_DMAC_NUM_UNITS];
  int  i;
  int  ret;

  dmainfo("RDK-RZV2H: initializing DMAC\n");

  /* Step 1: collision detection */

  rzv2h_dmac_check_collisions();

  /* Step 2: determine which units are needed */

  memset(units_used, 0, sizeof(units_used));

  for (i = 0; i < DMAC_PERIPH_COUNT; i++)
    {
      int ch = g_dmac_channel_map[i];
      if (ch >= 0 && ch < RZV_DMAC_MAX_CHANNELS)
        {
          units_used[ch / RZV_DMAC_CHANNELS_PER_UNIT] = true;
        }
    }

  /* Step 3: initialize units that are in use */

  for (i = 0; i < RZV_DMAC_NUM_UNITS; i++)
    {
      if (!units_used[i])
        {
          continue;
        }

      /* Pass first channel of the unit to trigger unit init */

      ret = rzv_dmac_channel_initialize(i * RZV_DMAC_CHANNELS_PER_UNIT);
      if (ret < 0)
        {
          dmaerr("Failed to initialize DMAC unit %d: %d\n", i, ret);
          return ret;
        }

      dmainfo("DMAC unit %d initialized\n", i);
    }

#ifdef CONFIG_RZV_DMAC_DEBUG
  dmainfo("DMAC channel assignments:\n");
  for (i = 0; i < DMAC_PERIPH_COUNT; i++)
    {
      if (g_dmac_channel_map[i] >= 0)
        {
          dmainfo("  %-12s: channel %d\n",
                  g_dmac_periph_names[i], g_dmac_channel_map[i]);
        }
    }
#endif

  return OK;
}

/****************************************************************************
 * Name: rzv2h_dmac_get_channel
 *
 * Description:
 *   Get the DMA channel assigned to a peripheral by enum ID.
 *   Replaces the old runtime strcmp loop (M7).
 *
 * Input Parameters:
 *   periph - Peripheral identifier (rzv2h_dmac_periph_t enum value).
 *
 * Returned Value:
 *   Channel number (0-79) on success; -1 if unassigned.
 *
 ****************************************************************************/

int rzv2h_dmac_get_channel(rzv2h_dmac_periph_t periph)
{
  /* D17-fix: rzv2h_dmac_periph_t is an unsigned enum; `periph < 0` is
   * always false.  Cast to unsigned to make the comparison explicit and
   * suppress any compiler warning about mixed signed/unsigned comparison. */

  if ((unsigned int)periph >= (unsigned int)DMAC_PERIPH_COUNT)
    {
      return DMAC_CHANNEL_UNASSIGNED;
    }

  return g_dmac_channel_map[periph];
}

#endif /* CONFIG_RZV_DMAC */

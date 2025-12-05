/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_sdram.c
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

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <syslog.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/board.h>
#include <arch/board/board.h>

#include "chip.h"
#include "arm_internal.h"
#include "ra_gpio.h"
#include "ra_sdram.h"

#include "evk-ra8p1.h"

#ifdef CONFIG_RA_SDRAM

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* EVK-RA8P1 SDRAM Configuration
 *
 * The EVK-RA8P1 board uses IS42S32800J-6BLI or similar SDRAM:
 * - 32-bit data bus
 * - 256Mb (32MB) capacity
 * - 8192 refresh cycles / 64ms
 * - CAS Latency 3
 *
 * SDRAM is mapped at 0x68000000 (CS space 6)
 */

#define BOARD_SDRAM_BASE        0x68000000
#define BOARD_SDRAM_SIZE        (32 * 1024 * 1024)  /* 32MB */

/* SDRAM Timing for IS42S32800J at 100MHz SDCLK */

#define BOARD_SDRAM_TCL         3     /* CAS Latency = 3 cycles */
#define BOARD_SDRAM_TRAS        5     /* tRAS = 45ns -> 5 cycles @ 100MHz */
#define BOARD_SDRAM_TRCD        2     /* tRCD = 18ns -> 2 cycles @ 100MHz */
#define BOARD_SDRAM_TRP         2     /* tRP = 18ns -> 2 cycles @ 100MHz */
#define BOARD_SDRAM_TWR         2     /* tWR = 2 cycles (auto precharge) */
#define BOARD_SDRAM_TREFW       8     /* Auto-refresh cycle count */
#define BOARD_SDRAM_TRFC        780   /* Refresh interval = 64ms/8192 rows * 100MHz */

/* Initialization Timing */

#define BOARD_SDRAM_INIT_ARFI   7     /* Init auto-refresh interval */
#define BOARD_SDRAM_INIT_ARFC   8     /* Init auto-refresh count */
#define BOARD_SDRAM_INIT_PRC    5     /* Init precharge cycles */

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* SDRAM configuration for EVK-RA8P1 */

static const struct ra_sdram_config_s g_evk_sdram_config =
{
  .bus_width   = RA_SDRAM_BUS_WIDTH_32BIT,
  .endian_mode = RA_SDRAM_ENDIAN_LITTLE,
  .access_mode = RA_SDRAM_ACCESS_BURST,
  .mxc_shift   = RA_SDRAM_MXC_9BIT_SHIFT,  /* 9-bit column address */
  .tcl         = BOARD_SDRAM_TCL,
  .tras        = BOARD_SDRAM_TRAS,
  .trcd        = BOARD_SDRAM_TRCD,
  .trp         = BOARD_SDRAM_TRP,
  .twr         = BOARD_SDRAM_TWR,
  .trefw       = BOARD_SDRAM_TREFW,
  .trfc        = BOARD_SDRAM_TRFC,
  .init_arfi   = BOARD_SDRAM_INIT_ARFI,
  .init_arfc   = BOARD_SDRAM_INIT_ARFC,
  .init_prc    = BOARD_SDRAM_INIT_PRC,
};

/* SDRAM pin configuration array
 * All pins need to be configured for peripheral function
 * Uses BOARD_SDRAM_* macros from board.h which map to GPIO_SDRAM_*_Pxxx
 */

static const gpio_pinset_t g_sdram_pins[] =
{
  /* Address lines A0-A12 for row/column, higher lines for extended addressing */

  BOARD_SDRAM_A0,
  BOARD_SDRAM_A1,
  BOARD_SDRAM_A2,
  BOARD_SDRAM_A3,
  BOARD_SDRAM_A4,
  BOARD_SDRAM_A5,
  BOARD_SDRAM_A6,
  BOARD_SDRAM_A7,
  BOARD_SDRAM_A8,
  BOARD_SDRAM_A9,
  BOARD_SDRAM_A10,
  BOARD_SDRAM_A11,
  BOARD_SDRAM_A12,
  BOARD_SDRAM_A15, /* SDRAM_BA0 */
  BOARD_SDRAM_A16, /* SDRAM_BA1 */

  /* Data lines DQ0-DQ31 (32-bit data bus) */

  BOARD_SDRAM_DQ0,
  BOARD_SDRAM_DQ1,
  BOARD_SDRAM_DQ2,
  BOARD_SDRAM_DQ3,
  BOARD_SDRAM_DQ4,
  BOARD_SDRAM_DQ5,
  BOARD_SDRAM_DQ6,
  BOARD_SDRAM_DQ7,
  BOARD_SDRAM_DQ8,
  BOARD_SDRAM_DQ9,
  BOARD_SDRAM_DQ10,
  BOARD_SDRAM_DQ11,
  BOARD_SDRAM_DQ12,
  BOARD_SDRAM_DQ13,
  BOARD_SDRAM_DQ14,
  BOARD_SDRAM_DQ15,
  BOARD_SDRAM_DQ16,
  BOARD_SDRAM_DQ17,
  BOARD_SDRAM_DQ18,
  BOARD_SDRAM_DQ19,
  BOARD_SDRAM_DQ20,
  BOARD_SDRAM_DQ21,
  BOARD_SDRAM_DQ22,
  BOARD_SDRAM_DQ23,
  BOARD_SDRAM_DQ24,
  BOARD_SDRAM_DQ25,
  BOARD_SDRAM_DQ26,
  BOARD_SDRAM_DQ27,
  BOARD_SDRAM_DQ28,
  BOARD_SDRAM_DQ29,
  BOARD_SDRAM_DQ30,
  BOARD_SDRAM_DQ31,

  /* Data mask lines DQM0-DQM3 */

  BOARD_SDRAM_DQM0,
  BOARD_SDRAM_DQM1,
  BOARD_SDRAM_DQM2,
  BOARD_SDRAM_DQM3,

  /* Control signals */

  BOARD_SDRAM_CKE,     /* Clock Enable */
  BOARD_SDRAM_CLK,     /* Clock */
  BOARD_SDRAM_CS,      /* Chip Select */
  BOARD_SDRAM_WE,      /* Write Enable */
  BOARD_SDRAM_CAS,     /* Column Address Strobe */
  BOARD_SDRAM_RAS,     /* Row Address Strobe */
};

#define NUM_SDRAM_PINS (sizeof(g_sdram_pins) / sizeof(g_sdram_pins[0]))

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra8p1_sdram_pins_configure
 *
 * Description:
 *   Configure all SDRAM interface pins
 *
 ****************************************************************************/

static void ra8p1_sdram_pins_configure(void)
{
  int i;

  syslog(LOG_INFO, "Configuring %d SDRAM pins\n", NUM_SDRAM_PINS);

  for (i = 0; i < NUM_SDRAM_PINS; i++)
    {
      ra_gpioconfig(g_sdram_pins[i]);
    }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_sdram_initialize
 *
 * Description:
 *   Initialize external SDRAM on the EVK-RA8P1 board.
 *   This function configures the SDRAM pins and initializes the SDRAM
 *   controller with appropriate timing parameters.
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/

int board_sdram_initialize(void)
{
  int ret;

  syslog(LOG_INFO, "Initializing SDRAM...\n");

  /* Step 1: Configure SDRAM pins */

  ra8p1_sdram_pins_configure();

  /* Step 2: Initialize SDRAM controller and memory */

  ret = ra_sdram_initialize(&g_evk_sdram_config, true);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: SDRAM initialization failed: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "SDRAM initialized: base=0x%08x, size=%uMB\n",
         BOARD_SDRAM_BASE, BOARD_SDRAM_SIZE / (1024 * 1024));

#ifdef CONFIG_RA_SDRAM_TEST
  /* Perform basic SDRAM test if enabled */

  ret = ra_sdram_test(BOARD_SDRAM_BASE, 4096);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: SDRAM test failed: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "SDRAM test passed\n");
#endif

  return OK;
}

/****************************************************************************
 * Name: board_sdram_selfrefresh_enter
 *
 * Description:
 *   Put SDRAM into self-refresh mode before entering low-power mode.
 *
 ****************************************************************************/

int board_sdram_selfrefresh_enter(void)
{
  return ra_sdram_selfrefresh_enable();
}

/****************************************************************************
 * Name: board_sdram_selfrefresh_exit
 *
 * Description:
 *   Wake SDRAM from self-refresh mode after exiting low-power mode.
 *
 ****************************************************************************/

int board_sdram_selfrefresh_exit(void)
{
  return ra_sdram_selfrefresh_disable();
}

/****************************************************************************
 * Name: board_get_sdram_base
 *
 * Description:
 *   Get the base address of SDRAM.
 *
 ****************************************************************************/

uintptr_t board_get_sdram_base(void)
{
  return BOARD_SDRAM_BASE;
}

/****************************************************************************
 * Name: board_get_sdram_size
 *
 * Description:
 *   Get the size of SDRAM in bytes.
 *
 ****************************************************************************/

size_t board_get_sdram_size(void)
{
  return BOARD_SDRAM_SIZE;
}

#endif /* CONFIG_RA_SDRAM */

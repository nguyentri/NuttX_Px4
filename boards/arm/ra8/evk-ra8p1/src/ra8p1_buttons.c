/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_buttons.c
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
#include <syslog.h>

#include <nuttx/arch.h>
#include <nuttx/board.h>
#include <nuttx/irq.h>
#include <nuttx/clock.h>

#include "ra_gpio.h"
#include "ra_icu.h"

#include <arch/board/board.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define BUTTON_DEBOUNCE_MS  50   /* 50ms debounce time */

/****************************************************************************
 * Private Data
 ****************************************************************************/

static bool g_led1_state = false; /* LED1 Blue - Active high, false = off */
static volatile clock_t g_last_sw1_time = 0;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: sw1_handler_isr
 *
 * Description:
 *   SW1 button interrupt handler - controls LED1 (Blue).
 *
 ****************************************************************************/

static int sw1_handler_isr(int irq, void *context, void *arg)
{
  clock_t current_time;
  clock_t elapsed_ticks;
  uint32_t elapsed_ms;

  /* Get current time in ticks */

  current_time = clock_systime_ticks();

  /* Debounce check for SW1 */

  if (g_last_sw1_time > 0)
    {
      elapsed_ticks = current_time - g_last_sw1_time;
      elapsed_ms = TICK2MSEC(elapsed_ticks);

      if (elapsed_ms < BUTTON_DEBOUNCE_MS)
        {
          return OK;  /* Ignore bounced press */
        }
    }

  /* Update last press time */

  g_last_sw1_time = current_time;

  /* Toggle LED1 (Blue) */

  g_led1_state = !g_led1_state;
  ra_gpiowrite(GPIO_LED1, g_led1_state);

  syslog(LOG_INFO, "SW1 pressed! LED1 (Blue) is now %s\n",
         g_led1_state ? "ON" : "OFF");

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_button_initialize
 *
 * Description:
 *   Initialize button with external interrupt capability.
 *   This demonstrates:
 *   - GPIO configuration for input with pull-up
 *   - External interrupt configuration (falling edge)
 *   - LED initialization for output
 *
 ****************************************************************************/

uint32_t board_button_initialize(void)
{
  int ret;

  /* Configure button with external interrupt
   * SW1 -> LED1 (Blue)
   */

  syslog(LOG_INFO, "Initializing button SW1:\n");
  syslog(LOG_INFO, "  SW1 (0x%08lx) -> controls LED1 (Blue)\n",
         (unsigned long)GPIO_SW1);

  /* Configure SW1 button */

  syslog(LOG_INFO, "Configuring SW1: pinset=0x%08lx\n",
         (unsigned long)GPIO_SW1);

  ret = ra_gpioconfig(GPIO_SW1);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to configure GPIO_SW1: %d\n", ret);
      return ret;
    }

  ret = ra_gpiosetevent(GPIO_SW1, false, true, false,
                        sw1_handler_isr, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to set event for GPIO_SW1: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "SW1 configured successfully\n");
  syslog(LOG_INFO, "Button initialization complete!\n");

  return OK;
}
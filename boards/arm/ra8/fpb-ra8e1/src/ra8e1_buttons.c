/****************************************************************************
 * boards/arm/ra8/fpb-ra8e1/src/ra8e1_buttons.c
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

static bool g_led1_state = false; /* LED1 - Active high, false = off */
static volatile clock_t g_last_sw1_time = 0;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: button_handler_isr
 *
 * Description:
 *   External interrupt handler for button press.
 *   This demonstrates:
 *   - External interrupt handling
 *   - GPIO reading/writing
 *   - LED control from ISR
 *
 ****************************************************************************/

static int button_handler_isr(int irq, void *context, void *arg)
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

  /* Toggle LED1 */

  g_led1_state = !g_led1_state;
  ra_gpiowrite(GPIO_LED1, g_led1_state);

  /* Log button press (keep brief for ISR) */

  syslog(LOG_INFO, "SW1 pressed! LED1 is now %s\n",
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
 *   Initialize SW1 button with external interrupt capability.
 *   SW1 controls LED1 with 50ms debouncing.
 *
 ****************************************************************************/

uint32_t board_button_initialize(void)
{
  int ret;

  /* Configure SW1 button with external interrupt
   * - Input with pull-up resistor
   * - Interrupt on falling edge (button press)
   * - 50ms software debounce
   */

  syslog(LOG_INFO, "Initializing SW1 button\n");

  ret = ra_gpioconfig(GPIO_SW1);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to configure button GPIO: %d\n", ret);
      return ret;
    }
  ret = ra_gpiosetevent(GPIO_SW1, false, true, false,
                        button_handler_isr, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to configure button interrupt: %d\n",
             ret);
      return ret;
    }

  syslog(LOG_INFO, "SW1 configured successfully\n");

  return OK;
}
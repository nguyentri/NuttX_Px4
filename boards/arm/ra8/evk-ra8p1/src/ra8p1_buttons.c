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

#include "ra_gpio.h"
#include "ra_icu.h"

#include <arch/board/board.h>

/****************************************************************************
 * Private Data
 ****************************************************************************/

static bool g_led1_state = true; /* Active low, true = off */
static bool g_led2_state = true; /* Active low, true = off */
static volatile uint32_t g_button_press_count = 0;

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
  /* Increment press counter */

  g_button_press_count++;

  /* Toggle both LEDs to provide visual feedback */

  g_led1_state = !g_led1_state;
  g_led2_state = !g_led2_state;

  ra_gpiowrite(GPIO_LED1, g_led1_state);
  ra_gpiowrite(GPIO_LED2, g_led2_state);

  /* Log button press (keep brief for ISR) */

  syslog(LOG_INFO, "Button pressed! Count: %lu\n", g_button_press_count);

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

  /* Button GPIO is already configured by ra_gpioconfiglist() in board bringup
   * Just setup the interrupt handler here
   */
  ret = ra_gpiosetevent(GPIO_SW1, false, true, false,
                        button_handler_isr, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to configure button interrupt: %d\n",
             ret);
      return ret;
    }

  return OK;
}
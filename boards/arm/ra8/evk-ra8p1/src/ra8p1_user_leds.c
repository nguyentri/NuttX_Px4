/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_user_leds.c
 *
 * SPDX-License-Identifier: Apache-2.0
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
#include <syslog.h>

#include <nuttx/clock.h>
#include <nuttx/wqueue.h>

#include "chip.h"
#include "ra_gpio.h"

#include <arch/board/board.h>

#ifndef CONFIG_ARCH_LEDS

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* This file is only compiled when CONFIG_ARCH_LEDS is NOT set.
 * In this mode, LEDs are controlled by user applications via the userled driver.
 * The auto-blink feature demonstrates background LED control.
 *
 * LED assignments in nsh-leds configuration:
 *   LED1 (Blue/P600)  - Controlled by SW1 button press (toggle)
 *   LED2 (Red/PA07)   - Available for user control via NSH commands
 *   LED3 (Green/P303) - Auto-blink at 1Hz (this file)
 */

#define LED_BLINK_DELAY     1000 /* 1 second LED blink delay (ms) */

/****************************************************************************
 * Private Data
 ****************************************************************************/

static bool g_led3_state = false; /* LED3 Green - Active high, false = off */
static struct work_s g_blink_work;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: led_blink_worker
 *
 * Description:
 *   Work queue handler to blink LED3 (Green) every 1 second.
 *
 ****************************************************************************/

static void led_blink_worker(void *arg)
{
  /* Toggle LED3 (Green) state */

  g_led3_state = !g_led3_state;

  /* Blink LED3 (Green LED on P303) */

  ra_gpiowrite(GPIO_LED3, g_led3_state);

  /* Schedule next blink */

  work_queue(LPWORK, &g_blink_work, led_blink_worker, NULL,
             MSEC2TICK(LED_BLINK_DELAY));
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_userled_initialize
 ****************************************************************************/

uint32_t board_userled_initialize(void)
{
  /* Configure LED GPIOs - active high, initialized to OFF by OUTPUT_LOW */
  ra_gpioconfig(GPIO_LED1);
  ra_gpioconfig(GPIO_LED2);
  ra_gpioconfig(GPIO_LED3);

  /* Start LED3 (Green) automatic blink on work queue */
  syslog(LOG_INFO, "Starting LED3 (Green) auto-blink at 1 Hz\n");
  work_queue(LPWORK, &g_blink_work, led_blink_worker, NULL,
             MSEC2TICK(LED_BLINK_DELAY));

  return NLEDS;
}

/****************************************************************************
 * Name: board_userled
 ****************************************************************************/

void board_userled(int led, bool ledon)
{
  gpio_pinset_t ledcfg;

  /* LEDs are active high on this board */

  if (led == LED_1)
    {
      ledcfg = GPIO_LED1;
    }
  else if (led == LED_2)
    {
      ledcfg = GPIO_LED2;
    }
  else
    {
      return;
    }

  ra_gpiowrite(ledcfg, ledon);
}

/****************************************************************************
 * Name: board_userled_all
 ****************************************************************************/

void board_userled_all(uint32_t ledset)
{
  bool ledon;

  /* Active high: drive high to turn LED on */

  ledon = ((ledset & LED_1_BIT) != 0);
  ra_gpiowrite(GPIO_LED1, ledon);

  ledon = ((ledset & LED_2_BIT) != 0);
  ra_gpiowrite(GPIO_LED2, ledon);

}

#endif /* !CONFIG_ARCH_LEDS */

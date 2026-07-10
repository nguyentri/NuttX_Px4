/****************************************************************************
 * boards/arm/rzv2h/common/src/rzv_autoleds.c
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
#include <assert.h>
#include <debug.h>

#include <nuttx/board.h>
#include <arch/board/board.h>

#include "chip.h"
#include "arm_internal.h"
#include "rzv_gpio.h"

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* This array maps LED numbers to GPIO configurations.
 * Shared by the autoled (CONFIG_ARCH_LEDS) and user-LED variants.
 */

static const gpio_pinset_t g_led_gpio[BOARD_NLEDS] =
{
  BOARD_LED1_GPIO,
  BOARD_LED2_GPIO,
  BOARD_LED3_GPIO,
  BOARD_LED4_GPIO,
};

#ifdef CONFIG_ARCH_LEDS

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: led_dumppins
 ****************************************************************************/

#ifdef LED_VERBOSE
static void led_dumppins(const char *msg)
{
  ledinfo("%s:\n", msg);
  ledinfo("  LED1: %d\n", rzv_gpioread(g_led_gpio[BOARD_LED1]));
  ledinfo("  LED2: %d\n", rzv_gpioread(g_led_gpio[BOARD_LED2]));
  ledinfo("  LED3: %d\n", rzv_gpioread(g_led_gpio[BOARD_LED3]));
  ledinfo("  LED4: %d\n", rzv_gpioread(g_led_gpio[BOARD_LED4]));
}
#else
#  define led_dumppins(m)
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_autoled_initialize
 *
 * Description:
 *   Initialize LED GPIOs so that LEDs can be controlled.
 *
 ****************************************************************************/

void board_autoled_initialize(void)
{
  int i;

  /* Configure LED GPIOs for output */

  for (i = 0; i < BOARD_NLEDS; i++)
    {
      rzv_gpioconfig(g_led_gpio[i]);
    }

  led_dumppins("board_autoled_initialize()");
}

/****************************************************************************
 * Name: board_autoled_on
 *
 * Description:
 *   Set the LED configuration into the ON condition for the state provided
 *   by the led parameter.  This may be one of:
 *
 *   LED_STARTED       - NuttX has been started
 *   LED_HEAPALLOCATE  - Heap has been allocated
 *   LED_IRQSENABLED   - Interrupts enabled
 *   LED_STACKCREATED  - Idle stack created
 *   LED_INIRQ         - In an interrupt handler
 *   LED_SIGNAL        - In a signal handler
 *   LED_ASSERTION     - An assertion failed
 *   LED_PANIC         - The system has crashed
 *
 ****************************************************************************/

void board_autoled_on(int led)
{
  /* Active low LEDs: write 0 to turn ON */

  switch (led)
    {
      case LED_STARTED:
        /* All LEDs off */
        rzv_gpiowrite(g_led_gpio[BOARD_LED1], true);
        rzv_gpiowrite(g_led_gpio[BOARD_LED2], true);
        rzv_gpiowrite(g_led_gpio[BOARD_LED3], true);
        rzv_gpiowrite(g_led_gpio[BOARD_LED4], true);
        break;

      case LED_HEAPALLOCATE:
        /* LED1 on */
        rzv_gpiowrite(g_led_gpio[BOARD_LED1], false);
        break;

      case LED_IRQSENABLED:
        /* LED2 on */
        rzv_gpiowrite(g_led_gpio[BOARD_LED2], false);
        break;

      case LED_STACKCREATED:
        /* LED3 on */
        rzv_gpiowrite(g_led_gpio[BOARD_LED3], false);
        break;

      case LED_INIRQ:
        /* LED4 on */
        rzv_gpiowrite(g_led_gpio[BOARD_LED4], false);
        break;

      case LED_SIGNAL:
        /* No change */
        break;

      case LED_ASSERTION:
      case LED_PANIC:
        /* Toggle LED1 for blinking */
        {
          bool current = rzv_gpioread(g_led_gpio[BOARD_LED1]);
          rzv_gpiowrite(g_led_gpio[BOARD_LED1], !current);
        }
        break;

      default:
        break;
    }

  led_dumppins("board_autoled_on()");
}

/****************************************************************************
 * Name: board_autoled_off
 *
 * Description:
 *   Set the LED configuration into the OFF condition for the state provided
 *   by the led parameter.
 *
 ****************************************************************************/

void board_autoled_off(int led)
{
  /* Active low LEDs: write 1 to turn OFF */

  switch (led)
    {
      case LED_STARTED:
      case LED_HEAPALLOCATE:
      case LED_IRQSENABLED:
      case LED_STACKCREATED:
        /* These states don't turn off LEDs */
        break;

      case LED_INIRQ:
        /* LED4 off */
        rzv_gpiowrite(g_led_gpio[BOARD_LED4], true);
        break;

      case LED_SIGNAL:
        /* No change */
        break;

      case LED_ASSERTION:
      case LED_PANIC:
        /* Blinking is handled in board_autoled_on */
        break;

      default:
        break;
    }

  led_dumppins("board_autoled_off()");
}

#endif /* CONFIG_ARCH_LEDS */

/****************************************************************************
 * Name: board_userled_initialize
 *
 * Description:
 *   If CONFIG_ARCH_LEDS is not defined, then the board can provide
 *   application-controlled LED functionality via these functions.
 *
 ****************************************************************************/

#ifndef CONFIG_ARCH_LEDS
uint32_t board_userled_initialize(void)
{
  int i;

  /* Configure LED GPIOs for output */

  for (i = 0; i < BOARD_NLEDS; i++)
    {
      rzv_gpioconfig(g_led_gpio[i]);
    }

  return BOARD_NLEDS;
}

/****************************************************************************
 * Name: board_userled
 *
 * Description:
 *   Set the LED to the on or off state
 *
 ****************************************************************************/

void board_userled(int led, bool ledon)
{
  if ((unsigned)led < BOARD_NLEDS)
    {
      /* Active low: write inverse of ledon */
      rzv_gpiowrite(g_led_gpio[led], !ledon);
    }
}

/****************************************************************************
 * Name: board_userled_all
 *
 * Description:
 *   Set the state of all LEDs
 *
 ****************************************************************************/

void board_userled_all(uint32_t ledset)
{
  int i;

  /* Active low: write inverse of each bit */

  for (i = 0; i < BOARD_NLEDS; i++)
    {
      bool ledon = ((ledset & (1 << i)) != 0);
      rzv_gpiowrite(g_led_gpio[i], !ledon);
    }
}

#endif /* !CONFIG_ARCH_LEDS */
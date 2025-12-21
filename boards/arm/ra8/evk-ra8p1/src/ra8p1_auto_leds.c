/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_auto_leds.c
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
#include <assert.h>
#include <debug.h>

#include <nuttx/board.h>

#include "chip.h"
#include "ra_gpio.h"

/* The board.h file may override pin configurations defined in <hardware/ra8p1/ra8p1_pinmap.h> */

#include <arch/board/board.h>

#ifdef CONFIG_ARCH_LEDS

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/*  There are three user-controllable LEDs on the EVK-RA8P1 board:
 *
 *     LED              GPIO     Color
 *     ---------------- -----    -----
 *     LED1             P600     Blue
 *     LED2             PA07     Red
 *     LED3             P303     Green
 *
 * LEDs are active HIGH (GPIO high = LED on, GPIO low = LED off).
 *
 * When CONFIG_ARCH_LEDS is defined, these LEDs are controlled by the kernel
 * to indicate system state (see board.h and ra8p1_auto_leds.c).
 * When CONFIG_ARCH_LEDS is not defined, these LEDs can be controlled by
 * user applications via the userled driver (see ra8p1_user_leds.c).
 *
 * The LEDs encode OS-related events as follows:
 *
 *   SYMBOL                MEANING                    LED1(Blue)  LED2(Red)  LED3(Green)
 *   -------------------  -----------------------    ----------  ---------  -----------
 *   LED_STARTED          NuttX has been started        OFF        OFF         OFF
 *   LED_HEAPALLOCATE     Heap has been allocated       OFF        OFF         OFF
 *   LED_IRQSENABLED      Interrupts enabled            OFF        OFF         OFF
 *   LED_STACKCREATED     Idle stack created            ON         OFF         OFF
 *   LED_INIRQ            In an interrupt               N/C        ON          N/C
 *   LED_SIGNAL           In a signal handler           N/C        ON          N/C
 *   LED_ASSERTION        An assertion failed           N/C        ON          N/C
 *   LED_PANIC            The system has crashed        N/C      Blinking      N/C
 *   LED_IDLE             MCU is in sleep mode          N/C        N/C         ON
 */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_autoled_initialize
 ****************************************************************************/

void board_autoled_initialize(void)
{
    /* Configure LED GPIOs for output */
    ra_gpioconfig(GPIO_LED1);
    ra_gpioconfig(GPIO_LED2);
    ra_gpioconfig(GPIO_LED3);
    ra_gpiowrite(GPIO_LED1, true);
    ra_gpiowrite(GPIO_LED2, true);
    ra_gpiowrite(GPIO_LED3, true);
}

/****************************************************************************
 * Name: board_autoled_on
 ****************************************************************************/

void board_autoled_on(int led)
{
  switch (led)
    {
      /* 0: LED_STARTED, LED_HEAPALLOCATE, LED_IRQSENABLED: All OFF */
      default:
      case 0:
        ra_gpiowrite(GPIO_LED1, false);  /* Blue LED off (active high) */
        ra_gpiowrite(GPIO_LED2, false);  /* Red LED off (active high) */
        ra_gpiowrite(GPIO_LED3, false);  /* Green LED off (active high) */
        break;

      /* 1: LED_STACKCREATED: Blue ON, others OFF */
      case 1:
        ra_gpiowrite(GPIO_LED1, true);  /* Blue LED on (active high) */
        ra_gpiowrite(GPIO_LED2, false); /* Red LED off (active high) */
        ra_gpiowrite(GPIO_LED3, false); /* Green LED off (active high) */
        break;

      /* 2: LED_INIRQ, LED_SIGNAL, LED_ASSERTION: Red ON */
      case 2:
        ra_gpiowrite(GPIO_LED2, true);  /* Red LED on (active high) */
        break;

      /* 3: LED_PANIC: Red blinking */
      case 3:
        ra_gpiowrite(GPIO_LED2, true);  /* Red LED on (active high) */
        break;
    }
}

/****************************************************************************
 * Name: board_autoled_off
 ****************************************************************************/

void board_autoled_off(int led)
{
  switch (led)
    {
      /* 0-1: LED_STARTED, LED_HEAPALLOCATE, LED_IRQSENABLED, LED_STACKCREATED */
      default:
      case 0:
      case 1:
        break;

      /* 2: LED_INIRQ, LED_SIGNAL, LED_ASSERTION: Red OFF */
      case 2:
        ra_gpiowrite(GPIO_LED2, false); /* Red LED off (active high) */
        break;

      /* 3: LED_PANIC: Red blinking */
      case 3:
        ra_gpiowrite(GPIO_LED2, false); /* Red LED off (active high) */
        break;
    }
}

#endif /* CONFIG_ARCH_LEDS */

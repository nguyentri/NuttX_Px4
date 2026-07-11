/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_buttons.c
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

/* RDK-RZV2H has no user buttons wired to the GPIO header (see board.h
 * BOARD_HAS_BUTTONS = 0, BOARD_NBUTTONS = 0).  This translation unit exists
 * only so the NuttX board_button_* API contract is satisfied when
 * CONFIG_ARCH_BUTTONS is enabled — every call is a well-behaved no-op that
 * reports "zero buttons present".
 *
 * If a future board revision adds physical buttons, define BOARD_NBUTTONS
 * plus per-button BOARD_BUTTON<n>_GPIO pinsets in board.h (input pull-up,
 * plus either an IRQ0..IRQ15 field via GPIO_IRQ(n) or the RZV_GPIO_TINT
 * flag for TINT routing) and this file's guarded body will pick them up
 * with no further changes.
 */

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <errno.h>

#include <nuttx/board.h>
#include <nuttx/irq.h>
#include <arch/board/board.h>

#include "rzv_gpio.h"
#include "rdk-rzv2h.h"

#ifdef CONFIG_ARCH_BUTTONS

/****************************************************************************
 * Private Data
 ****************************************************************************/

#if BOARD_NBUTTONS > 0

/* Pinset per button (defined in board.h when buttons are present). */

static const gpio_pinset_t g_button_gpio[BOARD_NBUTTONS] =
{
#  ifdef BOARD_BUTTON1_GPIO
  BOARD_BUTTON1_GPIO,
#  endif
#  ifdef BOARD_BUTTON2_GPIO
  BOARD_BUTTON2_GPIO,
#  endif
#  ifdef BOARD_BUTTON3_GPIO
  BOARD_BUTTON3_GPIO,
#  endif
#  ifdef BOARD_BUTTON4_GPIO
  BOARD_BUTTON4_GPIO,
#  endif
};

#  ifdef CONFIG_ARCH_IRQBUTTONS

/* User-registered per-button handler + arg. */

static xcpt_t g_button_handlers[BOARD_NBUTTONS];
static void  *g_button_args[BOARD_NBUTTONS];

/****************************************************************************
 * Name: button_interrupt
 *
 * Description:
 *   Trampoline installed via rzv_gpiosetevent(); dispatches to the
 *   user-registered handler for this button.
 *
 ****************************************************************************/

static int button_interrupt(int irq, void *context, void *arg)
{
  int button = (int)(uintptr_t)arg;

  if ((unsigned)button < BOARD_NBUTTONS &&
      g_button_handlers[button] != NULL)
    {
      return g_button_handlers[button](irq, context, g_button_args[button]);
    }

  return OK;
}

#  endif /* CONFIG_ARCH_IRQBUTTONS */

#endif /* BOARD_NBUTTONS > 0 */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

uint32_t board_button_initialize(void)
{
#if BOARD_NBUTTONS > 0
  int i;

  for (i = 0; i < BOARD_NBUTTONS; i++)
    {
      rzv_gpioconfig(g_button_gpio[i]);
    }
#endif

  return BOARD_NBUTTONS;
}

uint32_t board_buttons(void)
{
#if BOARD_NBUTTONS > 0
  uint32_t ret = 0;
  int i;

  /* Buttons wired active-low with pull-up; invert the reading. */

  for (i = 0; i < BOARD_NBUTTONS; i++)
    {
      if (!rzv_gpioread(g_button_gpio[i]))
        {
          ret |= (1U << i);
        }
    }

  return ret;
#else
  return 0;
#endif
}

#ifdef CONFIG_ARCH_IRQBUTTONS
int board_button_irq(int id, xcpt_t irqhandler, void *arg)
{
#if BOARD_NBUTTONS > 0
  if ((unsigned)id >= BOARD_NBUTTONS)
    {
      return -EINVAL;
    }

  g_button_handlers[id] = irqhandler;
  g_button_args[id]     = arg;

  /* Route through the unified GPIO interrupt API.  Both edges wanted for
   * press+release; rzv_gpiosetevent handles IRQ0-15 lines and TINT channels
   * transparently based on the pinset encoding (GPIO_IRQ field or
   * RZV_GPIO_TINT flag).
   */

  return rzv_gpiosetevent(g_button_gpio[id],
                          true /* rising */, true /* falling */,
                          false /* event */,
                          (irqhandler != NULL) ? button_interrupt : NULL,
                          (void *)(uintptr_t)id);
#else
  (void)id;
  (void)irqhandler;
  (void)arg;
  return -ENOSYS;
#endif
}
#endif /* CONFIG_ARCH_IRQBUTTONS */

#endif /* CONFIG_ARCH_BUTTONS */

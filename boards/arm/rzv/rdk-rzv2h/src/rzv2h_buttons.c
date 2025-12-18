/****************************************************************************
 * boards/arm/rzv2h/common/src/rzv_buttons.c
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
#include <errno.h>

#include <nuttx/board.h>
#include <nuttx/irq.h>
#include <arch/board/board.h>

#include "rzv_gpio.h"
#include "rzv_icu.h"

#ifdef CONFIG_ARCH_BUTTONS

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* This array maps button numbers to GPIO configurations */

static const rzv_pinconfig_t g_button_gpio[BOARD_NBUTTONS] =
{
  BOARD_BUTTON1_GPIO,
  BOARD_BUTTON2_GPIO,
  BOARD_BUTTON3_GPIO,
  BOARD_BUTTON4_GPIO,
};

#ifdef CONFIG_ARCH_IRQBUTTONS
/* Button IRQ handlers */

static xcpt_t g_button_handlers[BOARD_NBUTTONS];
static void *g_button_args[BOARD_NBUTTONS];

/* ICU IRQ numbers for buttons */

static int g_button_irqs[BOARD_NBUTTONS] = {-1, -1, -1, -1};
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

#ifdef CONFIG_ARCH_IRQBUTTONS
/****************************************************************************
 * Name: button_interrupt
 *
 * Description:
 *   Common button interrupt handler
 *
 ****************************************************************************/

static int button_interrupt(int irq, void *context, void *arg)
{
  int button = (int)(uintptr_t)arg;

  DEBUGASSERT(button >= 0 && button < BOARD_NBUTTONS);

  /* Call the registered handler */

  if (g_button_handlers[button] != NULL)
    {
      return g_button_handlers[button](irq, context,
                                      g_button_args[button]);
    }

  return OK;
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_button_initialize
 *
 * Description:
 *   board_button_initialize() must be called to initialize button resources.
 *   After that, board_buttons() may be called to collect the current state
 *   of all buttons or board_button_irq() may be called to register button
 *   interrupt handlers.
 *
 ****************************************************************************/

uint32_t board_button_initialize(void)
{
  int i;

  /* Configure button GPIOs as inputs with pull-ups */

  for (i = 0; i < BOARD_NBUTTONS; i++)
    {
      rzv_gpio_config(g_button_gpio[i]);
    }

  return BOARD_NBUTTONS;
}

/****************************************************************************
 * Name: board_buttons
 *
 * Description:
 *   After board_button_initialize() has been called, board_buttons() may be
 *   called to collect the state of all buttons.  board_buttons() returns an
 *   32-bit bit set with each bit associated with a button.  See the
 *   BUTTON_*_BIT definitions in board.h for the meaning of each bit.
 *
 ****************************************************************************/

uint32_t board_buttons(void)
{
  uint32_t ret = 0;
  int i;

  /* Read each button state
   * Buttons are active low, so invert the reading
   */

  for (i = 0; i < BOARD_NBUTTONS; i++)
    {
      bool pressed = !rzv_gpio_read(g_button_gpio[i]);
      if (pressed)
        {
          ret |= (1 << i);
        }
    }

  return ret;
}

/****************************************************************************
 * Name: board_button_irq
 *
 * Description:
 *   board_button_irq() may be called to register an interrupt handler that
 *   will be called when a button is pressed or released.  The ID value is a
 *   button enumeration value that uniquely identifies a button resource.
 *   See the BUTTON_* definitions in board.h for the meaning of enumeration
 *   value.
 *
 * Input Parameters:
 *   id      - Button ID (see BUTTON_* definitions)
 *   irqhandler - Interrupt handler to call when button is pressed/released
 *   arg     - Argument to pass to interrupt handler
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_ARCH_IRQBUTTONS
int board_button_irq(int id, xcpt_t irqhandler, void *arg)
{
  int ret = -EINVAL;

  /* Validate the button ID */

  if ((unsigned)id < BOARD_NBUTTONS)
    {
      /* Save the handler information */

      g_button_handlers[id] = irqhandler;
      g_button_args[id] = arg;

      if (irqhandler != NULL)
        {
          /* Attach interrupt on both edges (press and release) */
          /* Map button to ICU event (IRQ0-15) */

          int icu_event = ICU_EVENT_PORT_IRQ0 + id;

          /* Attach ICU interrupt */

          int irq = rzv_icu_attach(icu_event, button_interrupt,
                                  (void *)(uintptr_t)id, true);
          if (irq < 0)
            {
              return irq;
            }

          g_button_irqs[id] = irq;

          /* Configure interrupt mode (both edges) */

          ret = rzv_icu_filter_config(id, ICU_IRQCR_IRQMD_BOTH,
                                      true, 0);
        }
      else
        {
          /* Detach interrupt */

          if (g_button_irqs[id] >= 0)
            {
              ret = rzv_icu_detach(g_button_irqs[id]);
              g_button_irqs[id] = -1;
            }
          else
            {
              ret = OK;
            }
        }
    }

  return ret;
}
#endif /* CONFIG_ARCH_IRQBUTTONS */

#endif /* CONFIG_ARCH_BUTTONS */
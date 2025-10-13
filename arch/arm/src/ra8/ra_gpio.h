/****************************************************************************
 * arch/arm/src/ra8/ra_gpio.h
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

#ifndef __ARCH_ARM_SRC_RA_GPIO_H
#define __ARCH_ARM_SRC_RA_GPIO_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <nuttx/irq.h>

#include "chip.h"
#include "hardware/ra_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/* Must be big enough to hold the 32-bit encoding */

typedef uint32_t gpio_pinset_t;


/* Publication GPIO Pin Configuration Macro */

#define GPIO_PIN_CFG(port, pin, cfg)      \
  {                                       \
    .port = (port),                       \
    .pin = (pin),                         \
    .cfg = (cfg)                          \
  }

/* Common GPIO Pin Configurations */

#define GPIO_INPUT_PIN(port, pin)         \
  GPIO_PIN_CFG(port, pin, 0)

#define GPIO_OUTPUT_PIN(port, pin)        \
  GPIO_PIN_CFG(port, pin, GPIO_CFG_OUTPUT)

#define GPIO_INPUT_PULLUP_PIN(port, pin)  \
  GPIO_PIN_CFG(port, pin, GPIO_CFG_PULLUP)

#define GPIO_OUTPUT_OPENDRAIN_PIN(port, pin) \
  GPIO_PIN_CFG(port, pin, GPIO_CFG_OUTPUT | GPIO_CFG_OPENDRAIN)


/****************************************************************************
 * Name: ra_configgpio
 *
 * Description:
 *   Configure a GPIO pin based on bit-encoded description of the pin.
 *
 ****************************************************************************/

int ra_configgpio(gpio_pinset_t cfgset);

/****************************************************************************
 * Name: ra_gpiowrite
 *
 * Description:
 *   Write one or zero to the selected GPIO pin
 *
 ****************************************************************************/

void ra_gpiowrite(gpio_pinset_t pinset, bool value);

/****************************************************************************
 * Name: ra_gpioread
 *
 * Description:
 *   Read one or zero from the selected GPIO pin
 *
 ****************************************************************************/

bool ra_gpioread(gpio_pinset_t pinset);

/****************************************************************************
 * Name: ra_gpio_set_pullup
 *
 * Description:
 *   Enable/disable pull-up resistor on GPIO pin
 *
 * Input Parameters:
 *   pinset - GPIO pin configuration
 *   enable - Enable pull-up (true=enable, false=disable)
 *
 ****************************************************************************/

void ra_gpio_set_pullup(gpio_pinset_t pinset, bool enable);

/****************************************************************************
 * Name: ra_gpio_set_drive_strength
 *
 * Description:
 *   Set GPIO pin drive strength
 *
 * Input Parameters:
 *   pinset   - GPIO pin configuration
 *   strength - Drive strength (0=low, 1=mid, 2=high)
 *
 ****************************************************************************/

void ra_gpio_set_drive_strength(gpio_pinset_t pinset, uint8_t strength);

/****************************************************************************
 * Name: ra_gpiosetevent
 *
 * Description:
 *   Configure GPIO pin for external interrupt/event detection
 *
 * Input Parameters:
 *   pinset  - GPIO pin configuration
 *   rising  - Enable interrupt on rising edge
 *   falling - Enable interrupt on falling edge
 *   event   - Enable event (unused, for compatibility)
 *   func    - Interrupt callback function (NULL to disable)
 *   arg     - Argument passed to callback function
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpiosetevent(uint32_t pinset, bool rising, bool falling,
                    bool event, xcpt_t func, void *arg);

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RA_GPIO_H */

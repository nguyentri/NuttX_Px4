/****************************************************************************
 * arch/arm/src/rzv/rzv_gpio.h
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

#ifndef __ARCH_ARM_SRC_RZV_GPIO_H
#define __ARCH_ARM_SRC_RZV_GPIO_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>
#include <nuttx/irq.h>

/* Include chip-specific hardware definitions */
#include "chip.h"
#include "hardware/rzv_gpio.h"
#include "hardware/rzv_pinmap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPIO pin encoding (compatible with pinmap definitions):
 *
 *   3322 2222 2222 1111 1111 1100 0000 0000
 *   1098 7654 3210 9876 5432 1098 7654 3210
 *   ---- ---- ---- ---- ---- ---- ---- ----
 *   MMMM PPPP PPPP PPPP PPPP OSSS SDDD DPFF
 *
 * Mode (M):     4 bits [31:28] - GPIO mode (input/output/periph/analog)
 * Port (P):     8 bits [31:24] - Port number (0x20-0x2F for RZV2H)
 *                                 Note: Overlays with Mode in upper 4 bits
 * Pin (P):      8 bits [23:16] - Pin number (0-15)
 * Output (O):   1 bit  [19]    - Initial output value
 * PSEL (S):     4 bits [18:15] - Peripheral function select
 * Drive (D):    4 bits [14:11] - Drive strength
 * Pull (P):     2 bits [10:9]  - Pull-up/down configuration
 * Function (F): 9 bits [8:0]   - Extended function bits
 *
 * Extraction note: Pinmap constants define PORT as (port << 24), which places
 * the port value at bits [31:24]. When MODE is OR'd in, it occupies the same
 * [31:28] bits. To extract port correctly, mask bits [27:24] to get the lower
 * nibble, or mask [31:24] and clear MODE bits.
 */

#define GPIO_MODE_SHIFT         28
#define GPIO_MODE_MASK          (0xFU << GPIO_MODE_SHIFT)
#  define RZV_GPIO_INPUT        (0U << GPIO_MODE_SHIFT)
#  define RZV_GPIO_OUTPUT       (1U << GPIO_MODE_SHIFT)
#  define RZV_GPIO_PERIPH       (2U << GPIO_MODE_SHIFT)
#  define RZV_GPIO_ANALOG       (3U << GPIO_MODE_SHIFT)

/* Port extraction: pinmap uses (port << 24), so port is bits [31:24]
 * When MODE is OR'd in (bits [31:28]), we extract port from [27:24].
 * But for pinmap constants without MODE, port is at [31:24].
 * Solution: Extract from [31:24] and mask with 0x0F to get lower 4 bits
 * of port when MODE is present, or full port when MODE is 0.
 */
#define GPIO_PORT_SHIFT         24
#define GPIO_PORT_MASK          (0xFFU << GPIO_PORT_SHIFT)

/* Pin extraction: pinmap uses (pin << 16), so pin is at bits [23:16] */
#define GPIO_PIN_SHIFT          16
#define GPIO_PIN_MASK           (0xFFU << GPIO_PIN_SHIFT)

#define GPIO_OUTPUT_SHIFT       19
#define GPIO_OUTPUT_MASK        (1U << GPIO_OUTPUT_SHIFT)
#  define RZV_GPIO_INITIAL_LOW  (0U << GPIO_OUTPUT_SHIFT)
#  define RZV_GPIO_INITIAL_HIGH (1U << GPIO_OUTPUT_SHIFT)
#  define GPIO_OUTPUT_SET       RZV_GPIO_INITIAL_HIGH

/* PSEL: peripheral function selector (0-15 for RZV2H) */
#define GPIO_PSEL_SHIFT         15
#define GPIO_PSEL_MASK          (0xFU << GPIO_PSEL_SHIFT)

#define GPIO_DRVSTR_SHIFT       11
#define GPIO_DRVSTR_MASK        (0xFU << GPIO_DRVSTR_SHIFT)
#  define RZV_GPIO_DRVSTR_LOW   (0U << GPIO_DRVSTR_SHIFT)
#  define RZV_GPIO_DRVSTR_NORMAL (1U << GPIO_DRVSTR_SHIFT)
#  define RZV_GPIO_DRVSTR_MEDIUM (2U << GPIO_DRVSTR_SHIFT)
#  define RZV_GPIO_DRVSTR_HIGH  (3U << GPIO_DRVSTR_SHIFT)

#define GPIO_PULL_SHIFT         9
#define GPIO_PULL_MASK          (0x3U << GPIO_PULL_SHIFT)
#  define RZV_GPIO_FLOAT        (0U << GPIO_PULL_SHIFT)
#  define RZV_GPIO_PULLUP       (1U << GPIO_PULL_SHIFT)
#  define RZV_GPIO_PULLDOWN     (2U << GPIO_PULL_SHIFT)

#define GPIO_FUNC_SHIFT         0
#define GPIO_FUNC_MASK          (0x1FFU << GPIO_FUNC_SHIFT)
#  define RZV_GPIO_OPENDRAIN    (1U << GPIO_FUNC_SHIFT)

/* Drive strength values */

#define RZV_GPIO_DRIVE_LOW      0
#define RZV_GPIO_DRIVE_MEDIUM   1
#define RZV_GPIO_DRIVE_HIGH     2

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* GPIO pin configuration type */

typedef uint32_t rzv_pinconfig_t;

/* Helper macros to construct rzv_pinconfig_t constants from port/pin
 * These are guarded so that board- or chip-specific pinmap headers may
 * provide their own variants without causing redefinition warnings.
 *
 * Note: Port is placed at bits [31:24] to match pinmap encoding (port << 24).
 * When mode bits [31:28] are added, they overlay the upper 4 bits of port.
 */
#ifndef GPIO_PIN
#  define GPIO_PIN(port,pin) \
	(rzv_pinconfig_t)(((uint32_t)(port) << GPIO_PORT_SHIFT) | \
	                  (((uint32_t)(pin) & 0xFFU) << GPIO_PIN_SHIFT))
#endif

#ifndef GPIO_OUTPUT_HIGH
#  define GPIO_OUTPUT_HIGH(port,pin) \
	(rzv_pinconfig_t)(GPIO_PIN((port),(pin)) | RZV_GPIO_OUTPUT | \
	                  RZV_GPIO_DRVSTR_NORMAL | RZV_GPIO_INITIAL_HIGH)
#endif

#ifndef GPIO_OUTPUT_LOW
#  define GPIO_OUTPUT_LOW(port,pin) \
	(rzv_pinconfig_t)(GPIO_PIN((port),(pin)) | RZV_GPIO_OUTPUT | \
	                  RZV_GPIO_DRVSTR_NORMAL | RZV_GPIO_INITIAL_LOW)
#endif

#ifndef GPIO_INPUT_PULLUP
#  define GPIO_INPUT_PULLUP(port,pin) \
	(rzv_pinconfig_t)(GPIO_PIN((port),(pin)) | RZV_GPIO_INPUT | RZV_GPIO_PULLUP)
#endif

#ifndef GPIO_INPUT
#  define GPIO_INPUT(port,pin) \
	(rzv_pinconfig_t)(GPIO_PIN((port),(pin)) | RZV_GPIO_INPUT)
#endif

#ifndef GPIO_PERIPH_PIN
#  define GPIO_PERIPH_PIN(port,pin,psel) \
	(rzv_pinconfig_t)(GPIO_PIN((port),(pin)) | RZV_GPIO_PERIPH | \
	                  (((uint32_t)(psel) & 0xFU) << GPIO_PSEL_SHIFT))
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Name: rzv_gpio_config
 *
 * Description:
 *   Configure a GPIO pin based on encoded pin configuration
 *
 * Input Parameters:
 *   cfg - GPIO pin configuration
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure
 *
 ****************************************************************************/

int rzv_gpio_config(rzv_pinconfig_t cfg);

/****************************************************************************
 * Name: rzv_gpio_write
 *
 * Description:
 *   Write a value to a GPIO output pin
 *
 * Input Parameters:
 *   cfg   - GPIO pin configuration
 *   value - Output value (true = high, false = low)
 *
 ****************************************************************************/

void rzv_gpio_write(rzv_pinconfig_t cfg, bool value);

/****************************************************************************
 * Name: rzv_gpio_read
 *
 * Description:
 *   Read the value of a GPIO input pin
 *
 * Input Parameters:
 *   cfg - GPIO pin configuration
 *
 * Returned Value:
 *   Pin state (true = high, false = low)
 *
 ****************************************************************************/

bool rzv_gpio_read(rzv_pinconfig_t cfg);

/****************************************************************************
 * Name: rzv_gpio_setdrive
 *
 * Description:
 *   Set the drive strength for a GPIO pin
 *
 * Input Parameters:
 *   cfg   - GPIO pin configuration
 *   drive - Drive strength (RZV_GPIO_DRIVE_LOW/MEDIUM/HIGH)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure
 *
 ****************************************************************************/

int rzv_gpio_setdrive(rzv_pinconfig_t cfg, uint32_t drive);

/****************************************************************************
 * Name: rzv_gpio_set_pullup
 *
 * Description:
 *   Enable/disable pull-up resistor on GPIO pin
 *
 * Input Parameters:
 *   cfg    - GPIO pin configuration
 *   enable - Enable pull-up (true=enable, false=disable)
 *
 ****************************************************************************/

void rzv_gpio_set_pullup(rzv_pinconfig_t cfg, bool enable);

/****************************************************************************
 * Name: rzv_gpio_set_pulldown
 *
 * Description:
 *   Enable/disable pull-down resistor on GPIO pin
 *
 * Input Parameters:
 *   cfg    - GPIO pin configuration
 *   enable - Enable pull-down (true=enable, false=disable)
 *
 ****************************************************************************/

void rzv_gpio_set_pulldown(rzv_pinconfig_t cfg, bool enable);

/****************************************************************************
 * Name: rzv_gpio_set_drive_strength
 *
 * Description:
 *   Set GPIO pin drive strength
 *
 * Input Parameters:
 *   cfg      - GPIO pin configuration
 *   strength - Drive strength (0=low, 1=mid, 2=high)
 *
 ****************************************************************************/

void rzv_gpio_set_drive_strength(rzv_pinconfig_t cfg, uint8_t strength);

/****************************************************************************
 * Name: rzv_gpiosetevent
 *
 * Description:
 *   Configure GPIO pin for external interrupt/event detection
 *
 * Input Parameters:
 *   cfg     - GPIO pin configuration
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

int rzv_gpiosetevent(rzv_pinconfig_t cfg, bool rising, bool falling,
                     bool event, xcpt_t func, void *arg);

/****************************************************************************
 * Name: rzv_gpio_irq_attach
 *
 * Description:
 *   Attach an interrupt handler to a GPIO pin
 *
 * Input Parameters:
 *   irq     - IRQ number
 *   handler - Interrupt handler function
 *   arg     - Argument to pass to handler
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure
 *
 ****************************************************************************/

int rzv_gpio_irq_attach(int irq, xcpt_t handler, void *arg);

/****************************************************************************
 * Name: rzv_gpio_irq_detach
 *
 * Description:
 *   Detach an interrupt handler from a GPIO pin
 *
 * Input Parameters:
 *   irq - IRQ number
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure
 *
 ****************************************************************************/

int rzv_gpio_irq_detach(int irq);

/****************************************************************************
 * Name: rzv_gpio_irq_enable
 *
 * Description:
 *   Enable GPIO pin interrupt
 *
 * Input Parameters:
 *   irq - IRQ number
 *
 ****************************************************************************/

void rzv_gpio_irq_enable(int irq);

/****************************************************************************
 * Name: rzv_gpio_irq_disable
 *
 * Description:
 *   Disable GPIO pin interrupt
 *
 * Input Parameters:
 *   irq - IRQ number
 *
 ****************************************************************************/

void rzv_gpio_irq_disable(int irq);

/****************************************************************************
 * Name: rzv_gpio_irq_initialize
 *
 * Description:
 *   Initialize GPIO interrupt subsystem
 *
 ****************************************************************************/

void rzv_gpio_irq_initialize(void);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RZV_GPIO_H */

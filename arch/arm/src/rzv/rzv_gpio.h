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
#include <stddef.h>
#include <nuttx/irq.h>

/* Include chip-specific hardware definitions */
#include "chip.h"
#include "hardware/rzv_gpio.h"
#include "hardware/rzv_pinmap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPIO pin encoding ABI (single authoritative definition).
 *
 * fix: Unified encoding with pinmap.
 * Pinmap uses PORT=(port<<28) and PIN=(pin<<24); driver decodes identically.
 * All previous header/driver/pinmap disagreements are now resolved here.
 *
 * Bit layout (32-bit gpio_pinset_t):
 *
 *   3322 2222 2222 1111 1111 1100 0000 0000
 *   1098 7654 3210 9876 5432 1098 7654 3210
 *   ---- ---- ---- ---- ---- ---- ---- ----
 *   PPPP qqqq IIII MMMM DDDD LLLL FFFF SSSS
 *
 * Port  (P): bits [31:28] — relative port 0-11 (maps to HW port 0x20-0x2B)
 * Pin   (q): bits [27:24] — pin 0-15 within port
 * Out/IRQ(I):bits [23:20] — role-exclusive nibble:
 *              - OUTPUT-mode pins: bit 23 = initial output level (0=low,1=high)
 *              - interrupt pins:   bits [23:20] = external IRQ line number 0-15
 *                (consumed by rzv_gpiosetevent; interrupt pins are INPUT mode
 *                 so the output-level bit is never read for them, and vice
 *                 versa — the two roles never coexist on one pin)
 * Mode  (M): bits [19:16] — GPIO mode (INPUT/OUTPUT/PERIPH/ANALOG)
 * Drive (D): bits [15:12] — IOLH drive strength (0-3)
 * Pull  (L): bits [11:8]  — PUPD pull config (0=float, 1=up, 2=down)
 * Func  (F): bits [7:4]   — extended function flags (open-drain, etc.)
 * PSEL  (S): bits [3:0]   — peripheral function select (0-15 for RZV2H)
 *                           BSP_FEATURE_IOPORT_PFC_REG_BITFIELD=0xF
 *
 * Note: PSEL lives ONLY at bits [3:0]. The old dead PSEL field at [18:15]
 * is REMOVED. GPIO_PERIPH_PIN() encodes psel into [3:0] only.
 *
 * IRQ-line encoding: the external IRQ line number now has its own dedicated
 * field (GPIO_IRQ_SHIFT/MASK, bits [23:20]).  Previously it was overloaded
 * into the Func field [7:4], where it collided with RZV_GPIO_OPENDRAIN
 * (bit 4): extracting the line as ([7:4] & 0xF) mixed in the open-drain flag,
 * corrupting both.  That collision is resolved — open-drain and IRQ line no
 * longer share any bits.
 */

/* Port field: bits [31:28] — matches pinmap PORT0..(port<<28) */
#define GPIO_PORT_SHIFT         28
#define GPIO_PORT_MASK          (0xFU << GPIO_PORT_SHIFT)

/* Pin field: bits [27:24] — matches pinmap PIN0..(pin<<24) */
#define GPIO_PIN_SHIFT          24
#define GPIO_PIN_MASK           (0xFU << GPIO_PIN_SHIFT)

/* Initial output value: bit 23 (OUTPUT-mode pins only) */
#define GPIO_OUTPUT_SHIFT       23
#define GPIO_OUTPUT_MASK        (1U << GPIO_OUTPUT_SHIFT)
#  define RZV_GPIO_INITIAL_LOW  (0U << GPIO_OUTPUT_SHIFT)
#  define RZV_GPIO_INITIAL_HIGH (1U << GPIO_OUTPUT_SHIFT)
#  define GPIO_OUTPUT_SET       RZV_GPIO_INITIAL_HIGH

/* External IRQ line number: bits [23:20] (interrupt/input pins only).
 * Dedicated field for rzv_gpiosetevent — does NOT overlap the Func/open-drain
 * field [7:4] or the PSEL field [3:0].  Shares the [23:20] nibble with the
 * output-level bit (bit 23), but the two roles are mutually exclusive: an
 * interrupt pin is configured as INPUT (output-level unused) and an output
 * pin never carries an IRQ line number.
 */
#define GPIO_IRQ_SHIFT          20
#define GPIO_IRQ_MASK           (0xFU << GPIO_IRQ_SHIFT)
#  define GPIO_IRQ(n)           (((uint32_t)(n) & 0xFU) << GPIO_IRQ_SHIFT)

/* Mode field: bits [19:16] */
#define GPIO_MODE_SHIFT         16
#define GPIO_MODE_MASK          (0xFU << GPIO_MODE_SHIFT)
#  define RZV_GPIO_INPUT        (0U << GPIO_MODE_SHIFT)
#  define RZV_GPIO_OUTPUT       (1U << GPIO_MODE_SHIFT)
#  define RZV_GPIO_PERIPH       (2U << GPIO_MODE_SHIFT)
#  define RZV_GPIO_ANALOG       (3U << GPIO_MODE_SHIFT)

/* Drive strength field: bits [15:12] */
#define GPIO_DRVSTR_SHIFT       12
#define GPIO_DRVSTR_MASK        (0xFU << GPIO_DRVSTR_SHIFT)
#  define RZV_GPIO_DRVSTR_LOW    (0U << GPIO_DRVSTR_SHIFT)
#  define RZV_GPIO_DRVSTR_NORMAL (1U << GPIO_DRVSTR_SHIFT)
#  define RZV_GPIO_DRVSTR_MEDIUM (2U << GPIO_DRVSTR_SHIFT)
#  define RZV_GPIO_DRVSTR_HIGH   (3U << GPIO_DRVSTR_SHIFT)

/* Pull field: bits [11:8] */
#define GPIO_PULL_SHIFT         8
#define GPIO_PULL_MASK          (0xFU << GPIO_PULL_SHIFT)
#  define RZV_GPIO_FLOAT        (0U << GPIO_PULL_SHIFT)
#  define RZV_GPIO_PULLUP       (1U << GPIO_PULL_SHIFT)
#  define RZV_GPIO_PULLDOWN     (2U << GPIO_PULL_SHIFT)

/* Extended function flags: bits [7:4] */
#define GPIO_FUNC_SHIFT         4
#define GPIO_FUNC_MASK          (0xFU << GPIO_FUNC_SHIFT)
#  define RZV_GPIO_OPENDRAIN    (1U << GPIO_FUNC_SHIFT)  /* NOD open-drain */
#  define RZV_GPIO_TINT         (2U << GPIO_FUNC_SHIFT)  /* rzv_gpiosetevent: use TINT
                                                          * channel path (any GPIO
                                                          * pin) instead of the
                                                          * dedicated IRQ0-15 lines
                                                          * (GPIO_IRQ field). */

/* PSEL field: bits [3:0] — peripheral function select (0x0-0xF for RZV2H)
 * BSP_FEATURE_IOPORT_PFC_REG_BITFIELD=0xF.
 * Only this location is used; the old bits[18:15] PSEL is REMOVED (dead).
 */
#define GPIO_PSEL_SHIFT         0
#define GPIO_PSEL_MASK          (0xFU << GPIO_PSEL_SHIFT)

/* Convenience drive strength aliases */
#define RZV_GPIO_DRIVE_LOW      0
#define RZV_GPIO_DRIVE_MEDIUM   1
#define RZV_GPIO_DRIVE_HIGH     2

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* GPIO pin configuration type */

typedef uint32_t gpio_pinset_t;

/* Helper macros to construct gpio_pinset_t constants.
 * Port is at bits [31:28], pin at [27:24] — matching pinmap PORT/PIN macros.
 * GPIO_PIN and GPIO_PERIPH_PIN now use the canonical
 * shifts. All callers must use PORT0..PORT11 and PIN0..PIN15 from pinmap,
 * not raw hardware port numbers (e.g., 0x20 is wrong; PORT0 is correct).
 */
#ifndef GPIO_PIN
#  define GPIO_PIN(port, pin) \
    (gpio_pinset_t)(((uint32_t)(port) << GPIO_PORT_SHIFT) | \
                    (((uint32_t)(pin) & 0xFU) << GPIO_PIN_SHIFT))
#endif

#ifndef GPIO_OUTPUT_HIGH
#  define GPIO_OUTPUT_HIGH(port, pin) \
    (gpio_pinset_t)(GPIO_PIN((port), (pin)) | RZV_GPIO_OUTPUT | \
                    RZV_GPIO_DRVSTR_NORMAL | RZV_GPIO_INITIAL_HIGH)
#endif

#ifndef GPIO_OUTPUT_LOW
#  define GPIO_OUTPUT_LOW(port, pin) \
    (gpio_pinset_t)(GPIO_PIN((port), (pin)) | RZV_GPIO_OUTPUT | \
                    RZV_GPIO_DRVSTR_NORMAL | RZV_GPIO_INITIAL_LOW)
#endif

#ifndef GPIO_INPUT_PULLUP
#  define GPIO_INPUT_PULLUP(port, pin) \
    (gpio_pinset_t)(GPIO_PIN((port), (pin)) | RZV_GPIO_INPUT | RZV_GPIO_PULLUP)
#endif

#ifndef GPIO_INPUT
#  define GPIO_INPUT(port, pin) \
    (gpio_pinset_t)(GPIO_PIN((port), (pin)) | RZV_GPIO_INPUT)
#endif

/* GPIO_PERIPH_PIN: psel is placed at bits [3:0] ONLY.
 * old PSEL at bits [18:15] (GPIO_PSEL_SHIFT=15) is
 * REMOVED — that field was dead (rzv_gpioconfig read from [3:0] only).
 * Use RZV_PFS_PSEL_MODEx constants from rzv2h_pinmap.h for psel values.
 */
#ifndef GPIO_PERIPH_PIN
#  define GPIO_PERIPH_PIN(port, pin, psel) \
    (gpio_pinset_t)(GPIO_PIN((port), (pin)) | RZV_GPIO_PERIPH | \
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
 * Name: rzv_gpioconfig
 *
 * Description:
 *   Configure a GPIO pin based on encoded pin configuration
 *
 * Input Parameters:
 *   cfgset - GPIO pin configuration
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure
 *
 ****************************************************************************/

int rzv_gpioconfig(gpio_pinset_t cfgset);

/****************************************************************************
 * Name: rzv_unconfiggpio
 *
 * Description:
 *   Release a pin to a safe inert default: GPIO mode, high-impedance, no
 *   peripheral function, no pull, default drive, push-pull, interrupt-input
 *   select disabled.  Inverse of rzv_gpioconfig().
 *
 * Input Parameters:
 *   pinset - GPIO pin configuration (only port/pin are used)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int rzv_unconfiggpio(gpio_pinset_t pinset);

/****************************************************************************
 * Name: rzv_gpiowrite
 *
 * Description:
 *   Write a value to a GPIO output pin.
 * return int so callers see port-validation failures.
 *
 * Input Parameters:
 *   pinset - GPIO pin configuration
 *   value  - Output value (true = high, false = low)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int rzv_gpiowrite(gpio_pinset_t pinset, bool value);

/****************************************************************************
 * Name: rzv_gpioread
 *
 * Description:
 *   Read the value of a GPIO input pin
 *
 * Input Parameters:
 *   pinset - GPIO pin configuration
 *
 * Returned Value:
 *   Pin state (true = high, false = low)
 *
 ****************************************************************************/

bool rzv_gpioread(gpio_pinset_t pinset);

/****************************************************************************
 * Name: rzv_gpiosetpullup
 *
 * Description:
 *   Enable/disable pull-up resistor on GPIO pin
 *
 * Input Parameters:
 *   pinset - GPIO pin configuration
 *   enable - Enable pull-up (true=enable, false=disable)
 *
 ****************************************************************************/

void rzv_gpiosetpullup(gpio_pinset_t pinset, bool enable);

/****************************************************************************
 * Name: rzv_gpiosetpulldown
 *
 * Description:
 *   Enable/disable pull-down resistor on GPIO pin
 *
 * Input Parameters:
 *   pinset - GPIO pin configuration
 *   enable - Enable pull-down (true=enable, false=disable)
 *
 ****************************************************************************/

void rzv_gpiosetpulldown(gpio_pinset_t pinset, bool enable);

/****************************************************************************
 * Name: rzv_gpioconfiglist
 *
 * Description:
 *   Configure a list of GPIO pins based on an array of encoded pin
 *   configurations.
 *
 * Input Parameters:
 *   cfgset - Pointer to an array of GPIO configuration encodings
 *   count  - Number of entries in the cfgset array
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure.
 *
 ****************************************************************************/

int rzv_gpioconfiglist(const gpio_pinset_t *cfgset, size_t count);

/****************************************************************************
 * Name: rzv_gpiosetevent
 *
 * Description:
 *   Configure a GPIO pin for external interrupt/event detection.  Supports
 *   two routing paths:
 *
 *   1. IRQ0-15 direct lines (default): encode the line number in bits
 *      [23:20] of the pinset via GPIO_IRQ(n) or the IRQ0..IRQ15 pinmap
 *      macros.  Supports rising, falling, BOTH-edge, high-level and
 *      low-level triggers (all four IITSR modes).
 *
 *   2. TINT channel (any GPIO pin): set the RZV_GPIO_TINT flag in the
 *      Func field of the pinset.  Supports rising, falling, high-level,
 *      and low-level triggers, but NOT native both-edge — TINT hardware
 *      has no combined-edge mode (per FSP r_intc_tint.h
 *      intc_tint_trigger_t).  Requesting both-edge on the TINT path
 *      returns -EINVAL; callers that need press+release semantics must
 *      either use the IRQ0-15 path or emulate by flipping TITSR between
 *      RISING and FALLING inside their ISR.
 *
 * Input Parameters:
 *   pinset  - GPIO pin configuration.  IRQ path: includes GPIO_IRQ(n)
 *             field.  TINT path: includes RZV_GPIO_TINT flag; the
 *             (port, pin) is resolved to a GPIOINT source number
 *             internally.
 *   rising  - Enable interrupt on rising edge
 *   falling - Enable interrupt on falling edge
 *   event   - IRQ path: unused (compatibility).  TINT path: when both
 *             `rising` and `falling` are false the trigger is level-
 *             sensitive; `event=true` selects LEVEL_LOW, `event=false`
 *             (default) selects LEVEL_HIGH.
 *   func    - Interrupt callback function (NULL to disable)
 *   arg     - Argument passed to callback function
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure.
 *
 ****************************************************************************/

int rzv_gpiosetevent(gpio_pinset_t pinset, bool rising, bool falling,
                     bool event, xcpt_t func, void *arg);

/****************************************************************************
 * Name: rzv_gpio_irq_initialize
 *
 * Description:
 *   Initialize GPIO interrupt subsystem. Must be called from bringup when
 * CONFIG_RZV_GPIO_IRQ=y.
 *
 ****************************************************************************/

void rzv_gpio_irq_initialize(void);

/****************************************************************************
 * Name: rzv_gpio_irq_enable / rzv_gpio_irq_disable
 *
 * Description:
 *   Enable/disable GPIO pin interrupt by IRQ number
 *
 ****************************************************************************/

void rzv_gpio_irq_enable(int irq);
void rzv_gpio_irq_disable(int irq);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RZV_GPIO_H */

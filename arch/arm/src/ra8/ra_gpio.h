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

#include "hardware/ra_memorymap.h"
#include "hardware/ra_pinmap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPIO Configuration Bit Fields for cfg field in gpio_pinset_t struct */
/* These align with the R_PFS_* bit positions for direct use */
/* Note: R_PFS_* macros are already bit masks, not bit positions */

#define GPIO_CFG_OUTPUT                GPIO_OUTPUT         /* Output direction */
#define GPIO_CFG_INPUT                 (0)                 /* Input (default) */
#define GPIO_CFG_PULLUP                GPIO_INPUT          /* Enable pull-up */
#define GPIO_CFG_OPENDRAIN             GPIO_OPENDRAIN      /* Open-drain output */
#define GPIO_CFG_DRIVE_LOW             GPIO_DRIVE_LOW      /* Low drive strength */
#define GPIO_CFG_DRIVE_MID             GPIO_DRIVE_MID      /* Mid drive strength */
#define GPIO_CFG_DRIVE_HIGH            GPIO_DRIVE_HIGH     /* High drive strength */
#define GPIO_CFG_ANALOG                GPIO_ANALOG         /* Analog mode */
#define GPIO_CFG_IRQ                   GPIO_IRQ            /* IRQ input enable */
#define GPIO_CFG_PERIPHERAL            GPIO_PERIPHERAL     /* Peripheral mode (PMR) */
#define GPIO_CFG_OUTPUT_HIGH           GPIO_OUTPUT_HIGH    /* Output high */
#define GPIO_CFG_OUTPUT_LOW            (0)                 /* Output low (default) */

/* Macros to extract fields from gpio_pinset_t */
#define GPIO_PORT_MASK                  (0xF0000000UL)
#define GPIO_PIN_MASK                   (0x0F000000UL)
#define GPIO_CFG_MASK                   (0x00FFFFFFUL)
#if defined(CONFIG_RA8E1_GROUP)
#define GPIO_IRQ_MASK                   (0x0000000FUL) // IRQ number in bits 3-0: Max 16 IRQs
#elif defined(CONFIG_RA8P1_GROUP)
#define GPIO_IRQ_MASK                   (0x0000002FUL) // IRQ number in bits 5, 3-0: Max 32 IRQs
#endif

#define GPIO_PORT_SHIFT                 (28)
#define GPIO_PIN_SHIFT                  (24)
#define GPIO_CFG_SHIFT                  (0)

#define GPIO_GET_PORT(pinset)           (((pinset) & GPIO_PORT_MASK) >> GPIO_PORT_SHIFT)
#define GPIO_GET_PIN(pinset)            (((pinset) & GPIO_PIN_MASK) >> GPIO_PIN_SHIFT)
#define GPIO_GET_CFG(pinset)            ((pinset) & GPIO_CFG_MASK)
#define GPIO_GET_IRQ_NUM(pinset)       ((pinset) & GPIO_IRQ_MASK)


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

/*
 * Pin map definitions:
 * Bits 31-28: Port number (4 bits, supports ports 0-15)
 * Bits 27-24: Pin number (4 bits, supports pins 0-15)
 * Bits 23-0:  Configuration (24 bits for flags and PSEL)
 *  PSEL occupies bits 20-16 (5 bits) in the configuration field
 *  This will be shifted to hardware position 28:24 when writing to PFS register
 *  The following bits are also used in the gpio_pinset_t config field:
 *  Bits 0-15 directly map to PFS register bits 0-15:
 *   0 PODR  Port Output Data
 *   2 PDR   Port Direction
 *   4 PCR   Pull-up Control
 *   6 NCODR N-Channel Open-Drain Control
 *   11:10 DSCR[1:0] Port Drive Capability
 *   13:12 EOFR[1:0] Event on Falling/Event on Rising
 *   14 ISEL IRQ Input Enable
 *   15 ASEL Analog Input Enable
 *  Bit 16 PMR will be set automatically based on PSEL value
 */
typedef uint32_t gpio_pinset_t;

/* Publication GPIO Pin Configuration Macro
 * Encode a 32-bit gpio_pinset_t from port, pin and cfg components.
 */
#define GPIO_PIN_CFG(port, pin, cfg) \
  ((gpio_pinset_t)(((port) & GPIO_PORT_MASK) | ((pin) & GPIO_PIN_MASK) | ((cfg) & GPIO_CFG_MASK)))

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

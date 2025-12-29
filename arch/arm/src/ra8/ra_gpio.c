/****************************************************************************
 * arch/arm/src/ra8/ra_gpio.c
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

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/mutex.h>

#include <arch/board/board.h>
#include <arch/irq.h>

#include "arm_internal.h"
#include "chip.h"
#include "ra_start.h"
#include "ra_gpio.h"
#include "ra_icu.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define R_PFS_PSEL_SHIFT_HW           (24)   /* Hardware PSEL position in PFS register at 28:24 */

/****************************************************************************
 * Private Data
 ****************************************************************************/
#if defined(CONFIG_RA8E1_GROUP)
const static uint32_t g_irq_event[16] = {
    RA_ELC_ICU_IRQ0, RA_ELC_ICU_IRQ1, RA_ELC_ICU_IRQ2, RA_ELC_ICU_IRQ3,
    RA_ELC_ICU_IRQ4, RA_ELC_ICU_IRQ5, RA_ELC_ICU_IRQ6, RA_ELC_ICU_IRQ7,
    RA_ELC_ICU_IRQ8, RA_ELC_ICU_IRQ9, RA_ELC_ICU_IRQ10, RA_ELC_ICU_IRQ11,
    RA_ELC_ICU_IRQ12, RA_ELC_ICU_IRQ13, RA_ELC_ICU_IRQ14, RA_ELC_ICU_IRQ15
};
#elif defined(CONFIG_RA8P1_GROUP)
const static uint32_t g_irq_event[32] = {
    RA_ELC_ICU_IRQ0, RA_ELC_ICU_IRQ1, RA_ELC_ICU_IRQ2, RA_ELC_ICU_IRQ3,
    RA_ELC_ICU_IRQ4, RA_ELC_ICU_IRQ5, RA_ELC_ICU_IRQ6, RA_ELC_ICU_IRQ7,
    RA_ELC_ICU_IRQ8, RA_ELC_ICU_IRQ9, RA_ELC_ICU_IRQ10, RA_ELC_ICU_IRQ11,
    RA_ELC_ICU_IRQ12, RA_ELC_ICU_IRQ13, RA_ELC_ICU_IRQ14, RA_ELC_ICU_IRQ15,
    RA_ELC_ICU_IRQ16, RA_ELC_ICU_IRQ17, RA_ELC_ICU_IRQ18, RA_ELC_ICU_IRQ19,
    RA_ELC_ICU_IRQ20, RA_ELC_ICU_IRQ21, RA_ELC_ICU_IRQ22, RA_ELC_ICU_IRQ23,
    RA_ELC_ICU_IRQ24, RA_ELC_ICU_IRQ25, RA_ELC_ICU_IRQ26, RA_ELC_ICU_IRQ27,
    RA_ELC_ICU_IRQ28, RA_ELC_ICU_IRQ29, RA_ELC_ICU_IRQ30, RA_ELC_ICU_IRQ31
};
#endif
/* PFS protection counter for safe register access */
static volatile uint32_t g_pfs_protect_counter = 0;

/* GPIO interrupt callback information */
struct ra_gpio_irq_s
{
  gpio_pinset_t pinset;     /* GPIO pin configuration */
  xcpt_t        callback;   /* Interrupt callback function */
  void         *arg;        /* Callback argument */
  int           icu_slot;   /* ICU slot number (-1 if unused) */
  bool          allocated;  /* True if this slot is allocated */
};

/* GPIO interrupt table */
static struct ra_gpio_irq_s g_gpio_irqs[MAX_GPIO_IRQS];

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_pin_access_enable
 *
 * Description:
 *   Enable access to PFS registers
 *   Uses reference counter to protect against re-entrancy
 *
 ****************************************************************************/

static void ra_pin_access_enable(void)
{
  irqstate_t flags;

  flags = enter_critical_section();

  /* If this is first entry then allow writing of PFS */
  if (g_pfs_protect_counter == 0)
    {
      /* Clear BOWI bit - writing to PFSWE bit enabled */
      putreg8(0, R_PFS_PWPR);

      /* Set PFSWE bit - writing to PFS register enabled */
      putreg8((1 << R_PWPR_PFSWE), R_PFS_PWPR);
    }

  /* Increment the protect counter */
  g_pfs_protect_counter++;

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: ra_pin_access_disable
 *
 * Description:
 *   Disable access to PFS registers
 *   Uses reference counter to protect against re-entrancy
 *
 ****************************************************************************/

static void ra_pin_access_disable(void)
{
  irqstate_t flags;

  flags = enter_critical_section();

  /* Is it safe to disable PFS register? */
  if (g_pfs_protect_counter != 0)
    {
      g_pfs_protect_counter--;
    }

  /* If counter reaches zero, disable PFS writing */
  if (g_pfs_protect_counter == 0)
    {
      /* Clear PFSWE bit - writing to PFS register disabled */
      putreg8(0, R_PFS_PWPR);

      /* Set BOWI bit - writing to PFSWE bit disabled */
      putreg8((1 << R_PWPR_B0WI), R_PFS_PWPR);
    }

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: ra_gpio_validate_pin
 *
 * Description:
 *   Validate port and pin numbers
 *
 * Input Parameters:
 *   port - Port number (0-14)
 *   pin  - Pin number (0-15)
 *
 * Returned Value:
 *   true if valid, false otherwise
 *
 ****************************************************************************/

static bool ra_gpio_validate_pin(uint8_t port, uint8_t pin)
{
  return (port <= 14 && pin <= 15);
}

/****************************************************************************
 * Name: ra_gpio_pfs_write
 *
 * Description:
 *   Write to PFS register for a specific pin
 *
 * Input Parameters:
 *   port  - Port number (0-14)
 *   pin   - Pin number (0-15)
 *   value - PFS register value to write
 *
 ****************************************************************************/

static void ra_gpio_pfs_write(uint8_t port, uint8_t pin, uint32_t value)
{
  uint32_t pfs_addr;

  /* Validate port and pin parameters */
  if (!ra_gpio_validate_pin(port, pin))
    {
      return;
    }

  /* Calculate PFS register address */
  pfs_addr = R_PFS_BASE + (port * R_PFS_PSEL_PORT_OFFSET) +
             (pin * R_PFS_PSEL_PIN_OFFSET);

  /* For peripheral functions, clear PMR first */
  if ((value & R_PFS_PMR) != 0)
    {
      /* Clear PMR bit first, keeping other settings */
      putreg32(value & ~R_PFS_PMR, pfs_addr);
    }

  /* Write the complete configuration */
  putreg32(value, pfs_addr);
}

/****************************************************************************
 * Name: ra_gpio_get_pfs_config
 *
 * Description:
 *   Convert NuttX GPIO configuration to PFS register value
 *
 * Input Parameters:
 *   cfgset - Encoded GPIO configuration
 *
 * Returned Value:
 *   PFS register value
 *
 ****************************************************************************/

static uint32_t ra_gpio_get_pfs_config(gpio_pinset_t cfgset)
{
  uint32_t pfs_value = 0;
  uint32_t cfg = GPIO_GET_CFG(cfgset);

  /* Extract PSEL field from config bits 20-16 (5 bits) */
  uint32_t psel = (cfg >> R_PFS_PSEL_SHIFT_CFG) & 0x1F;
  if (psel != 0)
    {
      /* Shift to hardware PSEL position at 28:24 */
      pfs_value |= (psel << R_PFS_PSEL_SHIFT_HW);
      /* Set PMR bit for peripheral function */
      pfs_value |= R_PFS_PMR;
    }

  /* Map configuration bits 0-15 directly to PFS register bits 0-15 */
  /* These bits align exactly with the hardware register layout */
  pfs_value |= (cfg & 0x0000FFFF);

  return pfs_value;
}

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_gpio_find_irq
 *
 * Description:
 *   Extract IRQ number from gpio_pinset_t configuration
 *
 * Input Parameters:
 *   pinset - GPIO pin configuration with encoded IRQ number
 *
 * Returned Value:
 *   External IRQ number (0-32) or -1 if pin is not configured for interrupts
 *
 ****************************************************************************/

static int ra_gpio_find_irq(gpio_pinset_t pinset)
{
  uint32_t cfg = GPIO_GET_CFG(pinset);
  /* Get encoded IRQ value from pinset.
   * IRQ 0-15: stored directly in bits 0-3
   * IRQ 16-31: stored as (0x20 | (irq - 16)) in bits 5 + 0-3
   * GPIO_IRQ_MASK = 0x2F uses bits {5, 3, 2, 1, 0}, skipping bit 4 (R_PFS_PCR)
   */
  int encoded = GPIO_GET_IRQ_NUM(pinset);
  int irq;

  /* Check if this pin is configured for IRQ/input-selection */
  if (!(cfg & R_PFS_ISEL))
    {
      /* Pin is not configured for external interrupts */
      return -1;
    }

  if (encoded & 0x20)
    {
      /* IRQ 16-31: decode from (0x20 | (irq - 16)) */
      irq = 16 + (encoded & 0x0F);
    }
  else
    {
      /* IRQ 0-15: direct value */
      irq = encoded;
    }

  return irq;
}

/****************************************************************************
 * Name: ra_gpio_find_free_irq_slot
 *
 * Description:
 *   Find a free GPIO interrupt slot
 *
 * Returned Value:
 *   Slot index or -1 if no free slots
 *
 ****************************************************************************/

static int ra_gpio_find_free_irq_slot(void)
{
  int i;

  for (i = 0; i < MAX_GPIO_IRQS; i++)
    {
      if (!g_gpio_irqs[i].allocated)
        {
          return i;
        }
    }

  return -1;
}

/****************************************************************************
 * Name: ra_gpio_irq_handler
 *
 * Description:
 *   GPIO interrupt handler that routes interrupts to user callbacks
 *
 * Input Parameters:
 *   irq     - IRQ number
 *   context - Interrupt context
 *   arg     - Handler argument (pointer to gpio_irq_s structure)
 *
 * Returned Value:
 *   Zero on success
 *
 ****************************************************************************/

static int ra_gpio_irq_handler(int irq, void *context, void *arg)
{
  struct ra_gpio_irq_s *gpio_irq = (struct ra_gpio_irq_s *)arg;

  if (gpio_irq != NULL && gpio_irq->callback != NULL)
    {
      /* Call the user's callback function */
      return gpio_irq->callback(irq, context, gpio_irq->arg);
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_gpioconfig
 *
 * Description:
 *   Configure a GPIO pin based on encoded pin configuration.
 *
 * Input Parameters:
 *   cfgset - GPIO configuration encoding
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpioconfig(gpio_pinset_t cfgset)
{
  uint8_t port;
  uint8_t pin;
  uint32_t pfs_value;

  /* Extract port and pin from 32-bit value */
  port = GPIO_GET_PORT(cfgset);
  pin = GPIO_GET_PIN(cfgset);

  /* Validate port and pin numbers */
  if (!ra_gpio_validate_pin(port, pin))
    {
      return -EINVAL;
    }

  /* Convert to PFS configuration */
  pfs_value = ra_gpio_get_pfs_config(cfgset);

  /* Configure the pin */
  ra_pin_access_enable();
  ra_gpio_pfs_write(port, pin, pfs_value);
  ra_pin_access_disable();

  return OK;
}

/****************************************************************************
 * Name: ra_gpioconfiglist
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
int ra_gpioconfiglist(const gpio_pinset_t *cfgset, size_t count)
{
  size_t i;
  int ret;

  for (i = 0; i < count; i++)
    {
      ret = ra_gpioconfig(cfgset[i]);
      if (ret < 0)
        {
          return ret;
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_gpiowrite
 *
 * Description:
 *   Write one or zero to the selected GPIO pin
 *
 * Input Parameters:
 *   pinset - GPIO pin configuration (port/pin encoded)
 *   value  - Output value (true=high, false=low)
 *
 ****************************************************************************/

void ra_gpiowrite(gpio_pinset_t pinset, bool value)
{
  uint8_t port;
  uint8_t pin;

  /* Extract port and pin from 32-bit value */
  port = GPIO_GET_PORT(pinset);
  pin = GPIO_GET_PIN(pinset);

  /* Validate port and pin numbers */
  if (!ra_gpio_validate_pin(port, pin))
    {
      return;
    }

  /* Use atomic set/reset registers for thread-safe operation */
  if (value)
    {
      putreg16((1U << pin), R_PORT_POSR(port));
    }
  else
    {
      putreg16((1U << pin), R_PORT_PORR(port));
    }
}

/****************************************************************************
 * Name: ra_gpioread
 *
 * Description:
 *   Read one or zero from the selected GPIO pin
 *
 * Input Parameters:
 *   pinset - GPIO pin configuration (port/pin encoded)
 *
 * Returned Value:
 *   The boolean state of the input pin
 *
 ****************************************************************************/

bool ra_gpioread(gpio_pinset_t pinset)
{
  uint8_t port;
  uint8_t pin;
  uint16_t port_data;

  /* Extract port and pin from 32-bit value */
  port = GPIO_GET_PORT(pinset);
  pin = GPIO_GET_PIN(pinset);

  /* Validate port and pin numbers */
  if (!ra_gpio_validate_pin(port, pin))
    {
      return false;
    }

  /* Read from PIDR register */
  port_data = getreg16(R_PORT_PIDR(port));
  return ((port_data & (1U << pin)) != 0);
}

/****************************************************************************
 * Name: ra_gpio_set_direction
 *
 * Description:
 *   Set GPIO pin direction (input/output)
 *
 * Input Parameters:
 *   pinset    - GPIO pin configuration (port/pin encoded)
 *   direction - Direction (true=output, false=input)
 *
 ****************************************************************************/

void ra_gpio_set_direction(gpio_pinset_t pinset, bool direction)
{
  uint8_t port;
  uint8_t pin;
  uint32_t pfs_addr;
  uint32_t pfs_value;

  /* Extract port and pin from 32-bit value */
  port = GPIO_GET_PORT(pinset);
  pin = GPIO_GET_PIN(pinset);

  /* Validate port and pin numbers */
  if (port > 14 || pin > 15)
    {
      return;
    }

  /* Calculate PFS register address */
  pfs_addr = R_PFS_BASE + (port * R_PFS_PSEL_PORT_OFFSET) +
             (pin * R_PFS_PSEL_PIN_OFFSET);

  /* Modify direction bit */
  ra_pin_access_enable();

  pfs_value = getreg32(pfs_addr);
  if (direction)
    {
      pfs_value |= R_PFS_PDR;  /* Output */
    }
  else
    {
      pfs_value &= ~R_PFS_PDR; /* Input */
    }
  putreg32(pfs_value, pfs_addr);

  ra_pin_access_disable();
}

/****************************************************************************
 * Name: ra_gpiosetpullup
 *
 * Description:
 *   Enable/disable pull-up resistor on GPIO pin
 *
 * Input Parameters:
 *   pinset - GPIO pin configuration (port/pin encoded)
 *   enable - Enable pull-up (true=enable, false=disable)
 *
 ****************************************************************************/

void ra_gpiosetpullup(gpio_pinset_t pinset, bool enable)
{
  uint8_t port;
  uint8_t pin;
  uint32_t pfs_addr;
  uint32_t pfs_value;

  /* Extract port and pin from 32-bit value */
  port = GPIO_GET_PORT(pinset);
  pin = GPIO_GET_PIN(pinset);

  /* Validate port and pin numbers */
  if (port > 14 || pin > 15)
    {
      return;
    }

  /* Calculate PFS register address */
  pfs_addr = R_PFS_BASE + (port * R_PFS_PSEL_PORT_OFFSET) +
             (pin * R_PFS_PSEL_PIN_OFFSET);

  /* Modify pull-up bit */
  ra_pin_access_enable();

  pfs_value = getreg32(pfs_addr);
  if (enable)
    {
      pfs_value |= R_PFS_PCR;  /* Enable pull-up */
    }
  else
    {
      pfs_value &= ~R_PFS_PCR; /* Disable pull-up */
    }
  putreg32(pfs_value, pfs_addr);

  ra_pin_access_disable();
}

/****************************************************************************
 * Name: ra_gpiosetdrivestrength
 *
 * Description:
 *   Set GPIO pin drive strength
 *
 * Input Parameters:
 *   pinset   - GPIO pin configuration (port/pin encoded)
 *   strength - Drive strength (0=low, 1=mid, 2=high)
 *
 ****************************************************************************/

void ra_gpiosetdrivestrength(gpio_pinset_t pinset, uint8_t strength)
{
  uint8_t port;
  uint8_t pin;
  uint32_t pfs_addr;
  uint32_t pfs_value;

  /* Extract port and pin from 32-bit value */
  port = GPIO_GET_PORT(pinset);
  pin = GPIO_GET_PIN(pinset);

  /* Validate port and pin numbers and strength level */
  if (port > 14 || pin > 15 || strength > 2)
    {
      return;
    }

  /* Calculate PFS register address */
  pfs_addr = R_PFS_BASE + (port * R_PFS_PSEL_PORT_OFFSET) +
             (pin * R_PFS_PSEL_PIN_OFFSET);

  /* Modify drive strength bits */
  ra_pin_access_enable();

  pfs_value = getreg32(pfs_addr);

  /* Clear existing drive strength bits (bits 11:10) */
  pfs_value &= ~R_PFS_DSCR_MASK;

  /* Set new drive strength */
  switch (strength)
    {
      case 1: /* Mid */
        pfs_value |= R_PFS_DSCR_01;
        break;

      case 2: /* High */
        pfs_value |= R_PFS_DSCR_11;
        break;

      default: /* Low */
        pfs_value |= R_PFS_DSCR_00;
        break;
    }

  putreg32(pfs_value, pfs_addr);

  ra_pin_access_disable();
}

/****************************************************************************
 * Name: ra_gpiosetevent
 *
 * Description:
 *   Configure GPIO pin to generate an interrupt on rising/falling edge
 *
 * Input Parameters:
 *   pinset   - GPIO pin configuration (port/pin encoded)
 *   rising   - Enable interrupt on rising edge
 *   falling  - Enable interrupt on falling edge
 *   event    - Generate event instead of interrupt
 *   func     - Interrupt callback function
 *   arg      - Argument to pass to callback function
 *
 ****************************************************************************/
int ra_gpiosetevent(uint32_t pinset, bool rising, bool falling,
                         bool event, xcpt_t func, void *arg)
{
  uint8_t port;
  uint8_t pin;
  uint8_t irq_mode;
  uint32_t pfs_addr;
  uint32_t pfs_value;
  int irq_num;
  int icu_event;
  int slot;
  int icu_irq;
  int ret;

  /* Extract port and pin from pinset */
  port = GPIO_GET_PORT(pinset);
  pin = GPIO_GET_PIN(pinset);

  /* Validate port and pin numbers */
  if (!ra_gpio_validate_pin(port, pin))
    {
      return -EINVAL;
    }

  /* Find which external IRQ is encoded in this pin configuration */
  irq_num = ra_gpio_find_irq(pinset);
  if (irq_num < 0)
    {
      /* This pin is not configured for external interrupts */
      return -ENOTSUP;
    }

  /* Get the ICU event number for this external IRQ */
  icu_event = g_irq_event[irq_num];
  if (icu_event < 0)
    {
      return -ENOTSUP;
    }

  /* If callback is NULL, we're disabling the interrupt */
  if (func == NULL)
    {
      /* Find and disable existing interrupt for this pin */
      for (slot = 0; slot < MAX_GPIO_IRQS; slot++)
        {
          if (g_gpio_irqs[slot].allocated &&
              g_gpio_irqs[slot].pinset == pinset)
            {
              /* Disable interrupt in ICU */
              ra_icu_detach(g_gpio_irqs[slot].icu_slot);

              /* Clear the slot */
              g_gpio_irqs[slot].allocated = false;
              g_gpio_irqs[slot].callback = NULL;
              g_gpio_irqs[slot].arg = NULL;
              g_gpio_irqs[slot].icu_slot = -1;

              /* Reset pin to normal GPIO mode */
              pfs_addr = R_PFS_BASE + (port * R_PFS_PSEL_PORT_OFFSET) +
                         (pin * R_PFS_PSEL_PIN_OFFSET);

              ra_pin_access_enable();
              pfs_value = getreg32(pfs_addr);
              /* Clear IRQ and edge detection bits */
              pfs_value &= ~(R_PFS_ISEL | R_PFS_EOFR_MASK);
              putreg32(pfs_value, pfs_addr);
              ra_pin_access_disable();

              return OK;
            }
        }
      return -ENODEV; /* Pin not configured for interrupts */
    }

  /* Find a free interrupt slot */
  slot = ra_gpio_find_free_irq_slot();
  if (slot < 0)
    {
      return -ENOMEM; /* No free interrupt slots */
    }

  /* Calculate PFS register address */
  pfs_addr = R_PFS_BASE + (port * R_PFS_PSEL_PORT_OFFSET) +
             (pin * R_PFS_PSEL_PIN_OFFSET);

  /* Configure the pin for interrupt mode */
  ra_pin_access_enable();

  pfs_value = getreg32(pfs_addr);

  /* Clear existing interrupt configuration bits */
  pfs_value &= ~(R_PFS_ISEL | R_PFS_EOFR_MASK);

  /* Enable IRQ input */
  pfs_value |= R_PFS_ISEL;

  /* Configure edge detection using EOFR field */
  if (rising && falling)
    {
      pfs_value |= R_PFS_EOFR_11;  /* Detect both edges */
    }
  else if (rising)
    {
      pfs_value |= R_PFS_EOFR_01;  /* Detect rising edge */
    }
  else if (falling)
    {
      pfs_value |= R_PFS_EOFR_10;  /* Detect falling edge */
    }
  else
    {
      pfs_value |= R_PFS_EOFR_00;  /* Don't care */
    }

  /* Set pin as input */
  pfs_value &= ~(1 << R_PFS_PDR);

  /* Write the configuration */
  putreg32(pfs_value, pfs_addr);

  ra_pin_access_disable();

  if (rising && falling)
    {
      irq_mode = RA_ICU_IRQ_EDGE_BOTH;
    }
  else if (rising)
    {
      irq_mode = RA_ICU_IRQ_EDGE_RISING;
    }
  else if (falling)
    {
      irq_mode = RA_ICU_IRQ_EDGE_FALLING;
    }
  else
    {
      /* Neither rising nor falling specified - default to both */
      irq_mode = RA_ICU_IRQ_EDGE_BOTH;
    }

  /* Set up ICU interrupt link FIRST (this allocates and clears IELSR slot)
   * The IELSR must be cleared before configuring IRQCR per hardware manual.
   * Pass irq_enable=false to avoid enabling before IRQCR is configured.
   */
  icu_irq = ra_icu_attach(icu_event, ra_gpio_irq_handler,
                          &g_gpio_irqs[slot], false);
  if (icu_irq < 0)
    {
      return icu_irq; /* ICU attach failed */
    }

  /* Store interrupt information BEFORE enabling the interrupt!
   * This prevents a race condition where an interrupt fires before
   * the callback/arg are set, causing an invalid function call.
   */
  g_gpio_irqs[slot].pinset = pinset;
  g_gpio_irqs[slot].callback = func;
  g_gpio_irqs[slot].arg = arg;
  g_gpio_irqs[slot].icu_slot = icu_irq;
  g_gpio_irqs[slot].allocated = true;

  /* Now configure IRQCR (edge detection mode) - IELSR is already cleared */
  ret = ra_icu_filter_config(irq_num, irq_mode, false, RA_ICU_FILTER_PCLK_DIV_1);
  if (ret < 0)
    {
      ra_icu_detach(icu_irq);
      g_gpio_irqs[slot].allocated = false;
      g_gpio_irqs[slot].callback = NULL;
      return ret; /* ICU filter configuration failed */
    }

  /* Now enable the interrupt - callback/arg are already set */
  up_enable_irq(icu_irq);

  return OK;
}
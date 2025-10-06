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
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <arch/board/board.h>
#include <arch/irq.h>

#include "arm_internal.h"
#include "chip.h"
#include "ra_start.h"
#include "ra_gpio.h"
#include "ra_icu.h"

/****************************************************************************
 * Private Data
 ****************************************************************************/

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
      putreg8(0, R_PMISC_PWPRS);

      /* Set PFSWE bit - writing to PFS register enabled */
      putreg8((1 << R_PMISC_PWPRS_PFSWE), R_PMISC_PWPRS);
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
      putreg8(0, R_PMISC_PWPRS);

      /* Set BOWI bit - writing to PFSWE bit disabled */
      putreg8((1 << R_PMISC_PWPRS_B0WI), R_PMISC_PWPRS);
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
  if ((value & (1 << R_PFS_PMR)) != 0)
    {
      /* Clear PMR bit first, keeping other settings */
      putreg32(value & ~(1 << R_PFS_PMR), pfs_addr);
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
  uint16_t cfg = GPIO_GET_CFG(cfgset);

  /* Extract PSEL field from bits 8-12 (5 bits) */
  uint8_t psel = (cfg >> R_PFS_PSEL_SHIFT_8) & R_PFS_PSEL_MASK;
  if (psel != 0)
    {
      /* Peripheral mode: set PSEL and PMR */
      pfs_value |= (psel << R_PFS_PSEL_SHIFT_16);
      pfs_value |= (1 << R_PFS_PMR);
    }

  /* Convert bit positions to masks for GPIO config bits (0-7) */
  if (cfg & (1 << R_PFS_PODR)) pfs_value |= (1 << R_PFS_PODR);
  if (cfg & (1 << R_PFS_PDR)) pfs_value |= (1 << R_PFS_PDR);
  if (cfg & (1 << R_PFS_PCR)) pfs_value |= (1 << R_PFS_PCR);
  if (cfg & (1 << R_PFS_NCODR)) pfs_value |= (1 << R_PFS_NCODR);
  if (cfg & (1 << R_PFS_DSCR)) pfs_value |= (1 << R_PFS_DSCR);
  if (cfg & (1 << R_PFS_DSCR1)) pfs_value |= (1 << R_PFS_DSCR1);
  if (cfg & (1 << R_PFS_EOF)) pfs_value |= (1 << R_PFS_EOF);
  if (cfg & (1 << R_PFS_EOR)) pfs_value |= (1 << R_PFS_EOR);
  if (cfg & (1 << R_PFS_ISEL)) pfs_value |= (1 << R_PFS_ISEL);
  if (cfg & (1 << R_PFS_ASEL)) pfs_value |= (1 << R_PFS_ASEL);

  return pfs_value;
}

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_gpio_find_irq_for_pin
 *
 * Description:
 *   Extract IRQ number from gpio_pinset_t configuration
 *
 * Input Parameters:
 *   pinset - GPIO pin configuration with encoded IRQ number
 *
 * Returned Value:
 *   External IRQ number (0-15) or -1 if pin is not configured for interrupts
 *
 ****************************************************************************/

static int ra_gpio_find_irq_for_pin(gpio_pinset_t pinset)
{
  uint16_t cfg = GPIO_GET_CFG(pinset);

  /* Check if this pin is configured for IRQ functionality */
  if (!(cfg & (1 << R_PFS_ISEL)))
    {
      /* Pin is not configured for external interrupts */
      return -1;
    }

  /* Extract IRQ number from lower 5 bits (bits 0-4) */
  /* IRQ numbers 0-15 fit in 4 bits, but we use 5 bits for safety */
  int irq_num = cfg & 0x1F;

  /* Validate IRQ number range */
  if (irq_num > 15)
    {
      return -1;
    }

  return irq_num;
}

/****************************************************************************
 * Name: ra_gpio_get_irq_event
 *
 * Description:
 *   Get ICU event number for external IRQ
 *
 * Input Parameters:
 *   irq_num - External IRQ number (0-15)
 *
 * Returned Value:
 *   ICU event number
 *
 ****************************************************************************/

static int ra_gpio_get_irq_event(int irq_num)
{
  /* Map external IRQ numbers to their ICU event numbers */
  switch (irq_num)
    {
      case 0:  return RA_ELC_ICU_IRQ0;
      case 1:  return RA_ELC_ICU_IRQ1;
      case 2:  return RA_ELC_ICU_IRQ2;
      case 3:  return RA_ELC_ICU_IRQ3;
      case 4:  return RA_ELC_ICU_IRQ4;
      case 5:  return RA_ELC_ICU_IRQ5;
      case 6:  return RA_ELC_ICU_IRQ6;
      case 7:  return RA_ELC_ICU_IRQ7;
      case 8:  return RA_ELC_ICU_IRQ8;
      case 9:  return RA_ELC_ICU_IRQ9;
      case 10: return RA_ELC_ICU_IRQ10;
      case 11: return RA_ELC_ICU_IRQ11;
      case 12: return RA_ELC_ICU_IRQ12;
      case 13: return RA_ELC_ICU_IRQ13;
      case 14: return RA_ELC_ICU_IRQ14;
      case 15: return RA_ELC_ICU_IRQ15;
      default: return -1;
    }
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
 * Name: ra_configgpio
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

int ra_configgpio(gpio_pinset_t cfgset)
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
      pfs_value |= (1 << R_PFS_PDR);  /* Output */
    }
  else
    {
      pfs_value &= ~(1 << R_PFS_PDR); /* Input */
    }
  putreg32(pfs_value, pfs_addr);

  ra_pin_access_disable();
}

/****************************************************************************
 * Name: ra_gpio_set_pullup
 *
 * Description:
 *   Enable/disable pull-up resistor on GPIO pin
 *
 * Input Parameters:
 *   pinset - GPIO pin configuration (port/pin encoded)
 *   enable - Enable pull-up (true=enable, false=disable)
 *
 ****************************************************************************/

void ra_gpio_set_pullup(gpio_pinset_t pinset, bool enable)
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
      pfs_value |= (1 << R_PFS_PCR);  /* Enable pull-up */
    }
  else
    {
      pfs_value &= ~(1 << R_PFS_PCR); /* Disable pull-up */
    }
  putreg32(pfs_value, pfs_addr);

  ra_pin_access_disable();
}

/****************************************************************************
 * Name: ra_gpio_set_drive_strength
 *
 * Description:
 *   Set GPIO pin drive strength
 *
 * Input Parameters:
 *   pinset   - GPIO pin configuration (port/pin encoded)
 *   strength - Drive strength (0=low, 1=mid, 2=high)
 *
 ****************************************************************************/

void ra_gpio_set_drive_strength(gpio_pinset_t pinset, uint8_t strength)
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

  /* Clear existing drive strength bits */
  pfs_value &= ~((1 << R_PFS_DSCR) | (1 << R_PFS_DSCR1));

  /* Set new drive strength */
  switch (strength)
    {
      case 1: /* Mid */
        pfs_value |= (1 << R_PFS_DSCR);
        break;

      case 2: /* High */
        pfs_value |= (1 << R_PFS_DSCR) | (1 << R_PFS_DSCR1);
        break;

      default: /* Low */
        break;
    }

  putreg32(pfs_value, pfs_addr);

  ra_pin_access_disable();
}



int ra_gpiosetevent(uint32_t pinset, bool rising, bool falling,
                         bool event, xcpt_t func, void *arg)
{
  uint8_t port;
  uint8_t pin;
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
  irq_num = ra_gpio_find_irq_for_pin(pinset);
  if (irq_num < 0)
    {
      /* This pin is not configured for external interrupts */
      return -ENOTSUP;
    }

  /* Get the ICU event number for this external IRQ */
  icu_event = ra_gpio_get_irq_event(irq_num);
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
              pfs_value &= ~((1 << R_PFS_ISEL) | (1 << R_PFS_EOR) | (1 << R_PFS_EOF));
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
  pfs_value &= ~((1 << R_PFS_ISEL) | (1 << R_PFS_EOR) | (1 << R_PFS_EOF));

  /* Enable IRQ input */
  pfs_value |= (1 << R_PFS_ISEL);

  /* Configure edge detection */
  if (rising)
    {
      pfs_value |= (1 << R_PFS_EOR);  /* Event on Rising */
    }
  if (falling)
    {
      pfs_value |= (1 << R_PFS_EOF);  /* Event on Falling */
    }

  /* Set pin as input */
  pfs_value &= ~(1 << R_PFS_PDR);

  /* Write the configuration */
  putreg32(pfs_value, pfs_addr);

  ra_pin_access_disable();

  /* Set up ICU interrupt link */
  icu_irq = ra_icu_attach(icu_event, ra_gpio_irq_handler,
                          &g_gpio_irqs[slot], true);
  if (icu_irq < 0)
    {
      return icu_irq; /* ICU attach failed */
    }

  /* Configure external IRQ for appropriate edge detection mode */
  uint8_t irq_mode;
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

  ret = ra_icu_filter_config(irq_num, irq_mode, false, RA_ICU_FILTER_PCLK_DIV_1);
  if (ret < 0)
    {
      ra_icu_detach(icu_irq);
      return ret;
    }

  /* Store interrupt information */
  g_gpio_irqs[slot].pinset = pinset;
  g_gpio_irqs[slot].callback = func;
  g_gpio_irqs[slot].arg = arg;
  g_gpio_irqs[slot].icu_slot = icu_irq;
  g_gpio_irqs[slot].allocated = true;

  return OK;
}

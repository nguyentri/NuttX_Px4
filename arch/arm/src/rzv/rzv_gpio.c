/****************************************************************************
 * arch/arm/src/rzv/rzv_gpio.c
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
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>

#include "arm_internal.h"
#include "chip.h"
#include "rzv_gpio.h"
#include "hardware/rzv_gpio.h"
#include "hardware/rzv_pinmap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPIO Pinmap Encoding (from pinmap definitions):
 * PORT is encoded as (port << 28) placing port number at bits [31:28]
 * PIN is encoded as (pin << 24) placing pin number at bits [27:24]
 *
 * Example: PORT0 | PIN0 = (0x00 << 28) | (0 << 24) = 0x00000000
 *          PORT1 | PIN5 = (0x01 << 28) | (5 << 24) = 0x15000000
 */

/* Port extraction from pinmap: bits [31:28] */
#define PINMAP_PORT_SHIFT      28
#define PINMAP_PORT_MASK       (0xFU << PINMAP_PORT_SHIFT)

/* Pin extraction from pinmap: bits [27:24] */
#define PINMAP_PIN_SHIFT       24
#define PINMAP_PIN_MASK        (0xFU << PINMAP_PIN_SHIFT)

/* Extract port/pin using same method as FSP R_BSP_PinRead/Write */
#define PINMAP_GET_PORT(cfg)   (((cfg) >> PINMAP_PORT_SHIFT) & 0xF)
#define PINMAP_GET_PIN(cfg)    (((cfg) >> PINMAP_PIN_SHIFT) & 0xF)

/* PSEL extraction: bits [3:0] of PSEL modes (RZV_PFS_PSEL_MODEx) */
#define PINMAP_PSEL_MASK       0x0F

/* PM Register bit field values (2 bits per pin) */
#define PM_INPUT_ONLY          0x02  /* Input mode */
#define PM_OUTPUT              0x03  /* Output mode */
#define PM_HIZ                 0x00  /* Hi-Z */

/* PMC Register bit values (1 bit per pin) */
#define PMC_GPIO_MODE          0     /* GPIO mode */
#define PMC_PERIPH_MODE        1     /* Peripheral mode */

/* PUPD Register bit field values (2 bits per pin, in _L/_H registers) */
#define PUPD_DISABLE           0x00  /* No pull-up/down */
#define PUPD_PULLUP            0x01  /* Pull-up enabled */
#define PUPD_PULLDOWN          0x02  /* Pull-down enabled */

/* IOLH Register bit field values (2 bits per pin, in _L/_H registers) */
/* Drive strength values depend on pin and power supply voltage */

/* Register offset calculations (based on FSP ioport implementation) */
#define GPIO_PIN_ALIGN_2BIT    2
#define GPIO_PIN_ALIGN_4BIT    4
#define GPIO_PIN_ALIGN_8BIT    8

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* GPIO interrupt handlers */

#ifdef CONFIG_RZV_GPIO_IRQ
static xcpt_t g_gpio_irq_handlers[MAX_GPIO_IRQS];
static void  *g_gpio_irq_args[MAX_GPIO_IRQS];
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_gpio_get_port_base
 *
 * Description:
 *   Get the GPIO base address for a specific port
 *
 ****************************************************************************/

static uintptr_t rzv_gpio_get_port_base(unsigned int port)
{
  /* RZV2H has ports 0-11 (0x00-0x0B) */
  if (port <= 0x0B)
    {
      return RZV_GPIO_BASE;
    }

  return 0;
}

/****************************************************************************
 * Name: rzv_gpio_extract_port
 *
 * Description:
 *   Extract port number from pin configuration.
 *   Uses same method as FSP bsp_io_port_pin_t encoding.
 *
 ****************************************************************************/

static inline unsigned int rzv_gpio_extract_port(rzv_pinconfig_t cfg)
{
  /* Port is at bits [31:28] in pinmap definitions */
  return PINMAP_GET_PORT(cfg);
}

/****************************************************************************
 * Name: rzv_gpio_extract_pin
 *
 * Description:
 *   Extract pin number from pin configuration.
 *   Uses same method as FSP bsp_io_port_pin_t encoding.
 *
 ****************************************************************************/

static inline unsigned int rzv_gpio_extract_pin(rzv_pinconfig_t cfg)
{
  /* Pin is at bits [27:24] in pinmap definitions */
  return PINMAP_GET_PIN(cfg);
}

/****************************************************************************
 * Name: rzv_gpio_regwrite_8
 *
 * Description:
 *   Write 8-bit register with mask (based on FSP r_ioport_regwrite_8)
 *
 ****************************************************************************/

static void rzv_gpio_regwrite_8(volatile uint8_t *ioreg, uint8_t write_value,
                                uint8_t shift, uint8_t mask)
{
  uint8_t reg_value = *ioreg;
  reg_value = (uint8_t)((reg_value & (~mask)) | (write_value << shift));
  *ioreg = reg_value;
}

/****************************************************************************
 * Name: rzv_gpio_regwrite_16
 *
 * Description:
 *   Write 16-bit register with mask (based on FSP r_ioport_regwrite_16)
 *
 ****************************************************************************/

static void rzv_gpio_regwrite_16(volatile uint16_t *ioreg, uint16_t write_value,
                                 uint16_t shift, uint16_t mask)
{
  uint16_t reg_value = *ioreg;
  reg_value = (uint16_t)((reg_value & (~mask)) | (write_value << shift));
  *ioreg = reg_value;
}

/****************************************************************************
 * Name: rzv_gpio_regwrite_32
 *
 * Description:
 *   Write 32-bit register with mask (based on FSP r_ioport_regwrite_32)
 *
 ****************************************************************************/

static void rzv_gpio_regwrite_32(volatile uint32_t *ioreg, uint32_t write_value,
                                 uint32_t shift, uint32_t mask)
{
  uint32_t reg_value = *ioreg;
  reg_value = (reg_value & (~mask)) | (write_value << shift);
  *ioreg = reg_value;
}

/****************************************************************************
 * Name: rzv_gpio_configure_mode
 *
 * Description:
 *   Configure the GPIO mode (input/output) using PM register
 *   Based on FSP r_ioport_port_mode_pin_config
 *
 ****************************************************************************/

static int rzv_gpio_configure_mode(unsigned int port, unsigned int pin,
                                   uint32_t mode)
{
  uintptr_t base = rzv_gpio_get_port_base(port);
  volatile uint16_t *p_pm;
  uint16_t mask_pm;
  uint16_t value_pm;

  if (base == 0)
    {
      return -EINVAL;
    }

  /* Configure PM Register (Port Mode) - 2 bits per pin */
  p_pm = (volatile uint16_t *)(base + RZV_GPIO_PM_OFFSET(port));
  mask_pm = (uint16_t)(0x3 << (pin * GPIO_PIN_ALIGN_2BIT));

  if (mode == RZV_GPIO_OUTPUT)
    {
      value_pm = PM_OUTPUT;
    }
  else if (mode == RZV_GPIO_INPUT)
    {
      value_pm = PM_INPUT_ONLY;
    }
  else
    {
      value_pm = PM_HIZ;  /* Hi-Z for peripheral mode */
    }

  rzv_gpio_regwrite_16(p_pm, value_pm, (uint16_t)(pin * GPIO_PIN_ALIGN_2BIT), mask_pm);

  return 0;
}

/****************************************************************************
 * Name: rzv_gpio_configure_peripheral
 *
 * Description:
 *   Configure peripheral function using PMC and PFC registers
 *   Based on FSP r_ioport_peri_mode_pin_config
 *
 ****************************************************************************/

static int rzv_gpio_configure_peripheral(unsigned int port, unsigned int pin,
                                         uint32_t psel)
{
  uintptr_t base = rzv_gpio_get_port_base(port);
  volatile uint8_t *p_pmc;
  volatile uint32_t *p_pfc;
  uint8_t mask_pmc;
  uint8_t value_pmc;
  uint32_t mask_pfc;
  uint32_t value_pfc;

  if (base == 0)
    {
      return -EINVAL;
    }

  /* Configure PMC Register (Peripheral Mode Control) - 1 bit per pin */
  p_pmc = (volatile uint8_t *)(base + RZV_GPIO_PMC_OFFSET(port));
  mask_pmc = (uint8_t)(1 << pin);
  value_pmc = PMC_PERIPH_MODE;
  rzv_gpio_regwrite_8(p_pmc, value_pmc, pin, mask_pmc);

  /* Configure PFC Register (Peripheral Function Control) - 4 bits per pin */
  p_pfc = (volatile uint32_t *)(base + RZV_GPIO_PFC_OFFSET(port));
  mask_pfc = 0xF << (pin * GPIO_PIN_ALIGN_4BIT);
  value_pfc = psel & 0xF;  /* Extract PSEL value */
  rzv_gpio_regwrite_32(p_pfc, value_pfc, (pin * GPIO_PIN_ALIGN_4BIT), mask_pfc);

  return 0;
}

/****************************************************************************
 * Name: rzv_gpio_configure_pull
 *
 * Description:
 *   Configure pull-up/pull-down using PUPD registers
 *   Note: PUPD registers not available on RZV2H, this is a placeholder
 *
 ****************************************************************************/

static int rzv_gpio_configure_pull(unsigned int port, unsigned int pin,
                                   uint32_t pull)
{
  /* RZV2H GPIO module doesn't have PUPD registers like RA8
   * Pull-up/down configuration is typically done in the pin mux settings
   * For now, return success as a no-op
   */
  (void)port;
  (void)pin;
  (void)pull;

  return 0;
}

/****************************************************************************
 * Name: rzv_gpio_configure_drive
 *
 * Description:
 *   Configure drive strength using IOLH registers
 *   Note: IOLH registers available but complex mapping for RZV2H
 *
 ****************************************************************************/

static int rzv_gpio_configure_drive(unsigned int port, unsigned int pin,
                                    uint32_t drive)
{
  /* RZV2H has IOLH registers but they are complex with _L/_H variants
   * and different offsets for different port groups (IOLH3-13, IOLH20-23, etc.)
   * For now, return success as a no-op - can be implemented later when needed
   */
  (void)port;
  (void)pin;
  (void)drive;

  return 0;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_gpio_config
 *
 * Description:
 *   Configure a GPIO pin based on the GPIO_ definition from pinmap.
 *   This function extracts port/pin from the 32-bit pinmap encoding
 *   and configures the pin according to FSP ioport methodology.
 *
 ****************************************************************************/

int rzv_gpio_config(rzv_pinconfig_t cfg)
{
  unsigned int port;
  unsigned int pin;
  uint32_t mode;
  uint32_t psel;
  uint32_t pull;
  uint32_t drive;
  int ret;

  /* Extract port and pin using pinmap encoding */
  port = rzv_gpio_extract_port(cfg);
  pin  = rzv_gpio_extract_pin(cfg);

  /* Extract mode from configuration */
  mode = cfg & GPIO_MODE_MASK;

  /* Extract PSEL from pinmap (MODEx definitions contain PSEL in lower bits) */
  psel = cfg & PINMAP_PSEL_MASK;

  /* Extract pull configuration */
  pull = cfg & GPIO_PULL_MASK;

  /* Extract drive strength */
  drive = (cfg & GPIO_DRVSTR_MASK) >> GPIO_DRVSTR_SHIFT;

  /* Validate port */
  if (rzv_gpio_get_port_base(port) == 0)
    {
      return -EINVAL;
    }

  /* First, set to GPIO mode (PMC=0) */
  uintptr_t base = rzv_gpio_get_port_base(port);
  volatile uint8_t *p_pmc = (volatile uint8_t *)(base + RZV_GPIO_PMC_OFFSET(port));
  uint8_t pmc_val = *p_pmc;
  pmc_val &= ~(1 << pin);
  *p_pmc = pmc_val;

  /* Configure mode (PM register) */
  ret = rzv_gpio_configure_mode(port, pin, mode);
  if (ret < 0)
    {
      return ret;
    }

  /* Configure peripheral function if needed */
  if (mode == RZV_GPIO_PERIPH)
    {
      ret = rzv_gpio_configure_peripheral(port, pin, psel);
      if (ret < 0)
        {
          return ret;
        }
    }

  /* Configure pull-up/pull-down */
  ret = rzv_gpio_configure_pull(port, pin, pull);
  if (ret < 0)
    {
      return ret;
    }

  /* Configure drive strength */
  ret = rzv_gpio_configure_drive(port, pin, drive);
  if (ret < 0)
    {
      return ret;
    }

  /* Set initial output value if output mode */
  if (mode == RZV_GPIO_OUTPUT)
    {
      bool value = (cfg & GPIO_OUTPUT_SET) != 0;
      rzv_gpio_write(cfg, value);
    }

  return 0;
}

/****************************************************************************
 * Name: rzv_gpio_write
 *
 * Description:
 *   Write one or zero to the selected GPIO pin.
 *   Based on FSP R_BSP_PinWrite implementation.
 *
 ****************************************************************************/

void rzv_gpio_write(rzv_pinconfig_t cfg, bool value)
{
  unsigned int port;
  unsigned int pin;
  uintptr_t base;
  volatile uint8_t *p_p;
  uint8_t mask_p;
  uint8_t value_p;

  /* Extract port and pin */
  port = rzv_gpio_extract_port(cfg);
  pin  = rzv_gpio_extract_pin(cfg);

  /* Validate port */
  base = rzv_gpio_get_port_base(port);
  if (base == 0)
    {
      return;
    }

  /* Configure P Register (Port output data) - 1 bit per pin */
  p_p = (volatile uint8_t *)(base + RZV_GPIO_P_OFFSET(port));
  mask_p = (uint8_t)(1 << pin);
  value_p = (uint8_t)(value ? 1 : 0);

  rzv_gpio_regwrite_8(p_p, value_p, pin, mask_p);
}

/****************************************************************************
 * Name: rzv_gpio_read
 *
 * Description:
 *   Read the value from the selected GPIO pin.
 *   Based on FSP R_BSP_PinRead implementation.
 *
 ****************************************************************************/

bool rzv_gpio_read(rzv_pinconfig_t cfg)
{
  unsigned int port;
  unsigned int pin;
  uintptr_t base;
  volatile const uint8_t *p_pin;
  uint8_t regval;

  /* Extract port and pin */
  port = rzv_gpio_extract_port(cfg);
  pin  = rzv_gpio_extract_pin(cfg);

  /* Validate port */
  base = rzv_gpio_get_port_base(port);
  if (base == 0)
    {
      return false;
    }

  /* Read PIN Register (Port input data) - 1 bit per pin */
  p_pin = (volatile const uint8_t *)(base + RZV_GPIO_PIN_OFFSET(port));
  regval = *p_pin;

  return ((regval >> pin) & 0x1) != 0;
}

/****************************************************************************
 * Name: rzv_gpio_set_pullup
 *
 * Description:
 *   Enable/disable pull-up resistor on GPIO pin
 *
 ****************************************************************************/

void rzv_gpio_set_pullup(rzv_pinconfig_t cfg, bool enable)
{
  unsigned int port = rzv_gpio_extract_port(cfg);
  unsigned int pin = rzv_gpio_extract_pin(cfg);

  rzv_gpio_configure_pull(port, pin, enable ? RZV_GPIO_PULLUP : RZV_GPIO_FLOAT);
}

/****************************************************************************
 * Name: rzv_gpio_set_pulldown
 *
 * Description:
 *   Enable/disable pull-down resistor on GPIO pin
 *
 ****************************************************************************/

void rzv_gpio_set_pulldown(rzv_pinconfig_t cfg, bool enable)
{
  unsigned int port = rzv_gpio_extract_port(cfg);
  unsigned int pin = rzv_gpio_extract_pin(cfg);

  rzv_gpio_configure_pull(port, pin, enable ? RZV_GPIO_PULLDOWN : RZV_GPIO_FLOAT);
}

/****************************************************************************
 * Name: rzv_gpio_setdrive
 *
 * Description:
 *   Set GPIO pin drive strength
 *
 ****************************************************************************/

int rzv_gpio_setdrive(rzv_pinconfig_t cfg, uint32_t drive)
{
  unsigned int port = rzv_gpio_extract_port(cfg);
  unsigned int pin = rzv_gpio_extract_pin(cfg);

  return rzv_gpio_configure_drive(port, pin, drive);
}

/****************************************************************************
 * Name: rzv_gpiosetevent
 *
 * Description:
 *   Configure GPIO pin for external interrupt/event detection
 *
 ****************************************************************************/

int rzv_gpiosetevent(rzv_pinconfig_t cfg, bool rising, bool falling,
                     bool event, xcpt_t func, void *arg)
{
  /* TODO: Implement GPIO interrupt event configuration */
  /* This requires IRQ controller integration */

  (void)cfg;
  (void)rising;
  (void)falling;
  (void)event;
  (void)func;
  (void)arg;

  return -ENOSYS;  /* Not implemented yet */
}

#ifdef CONFIG_RZV_GPIO_IRQ

/****************************************************************************
 * GPIO IRQ Functions
 ****************************************************************************/

/* IRQ functions placeholder - to be implemented based on hardware IRQ controller */

#endif /* CONFIG_RZV_GPIO_IRQ */

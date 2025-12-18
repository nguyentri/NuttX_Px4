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
#include "rzv_icu.h"
#include "hardware/rzv_gpio.h"
#include "hardware/rzv_pinmap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPIO Pinmap Encoding (from pinmap definitions):
 * PORT is encoded as (port << 28) placing port number at bits [31:28]
 * PIN is encoded as (pin << 24) placing pin number at bits [27:24]
 *
 * Port numbers in pinmap (PORT0-PORT11) are RELATIVE (0-11)
 * They correspond to hardware ports 0x20-0x2B (PORT20-PORT2B)
 * Register offset macros expect relative port numbers (0-11)
 *
 * Example: PORT0 | PIN0 = (0x00 << 28) | (0 << 24) = 0x00000000
 *          PORT1 | PIN5 = (0x01 << 28) | (5 << 24) = 0x15000000
 */

/* Port extraction from pinmap: bits [31:28] - returns relative port 0-11 */
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

/* PWPR protection counter for safe register access */
static volatile uint32_t g_pwpr_protect_counter = 0;

/* GPIO interrupt callback information */

#ifdef CONFIG_RZV_GPIO_IRQ
struct rzv_gpio_irq_s
{
  gpio_pinset_t pinset;       /* GPIO pin configuration */
  xcpt_t          callback;   /* Interrupt callback function */
  void           *arg;        /* Callback argument */
  int             icu_slot;   /* ICU slot number (-1 if unused) */
  uint8_t         irq_num;    /* External IRQ number (0-15) */
  bool            allocated;  /* True if this slot is allocated */
};

/* GPIO interrupt table */
static struct rzv_gpio_irq_s g_gpio_irqs[MAX_GPIO_IRQS];
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_gpio_pwpr_enable
 *
 * Description:
 *   Enable write access to GPIO registers (PFC, PM, PMC, etc.)
 *   Uses reference counter for re-entrancy protection
 *   Based on FSP R_BSP_PinAccessEnable()
 *
 ****************************************************************************/

static void rzv_gpio_pwpr_enable(void)
{
  irqstate_t flags;

  flags = enter_critical_section();

  /* If this is first entry then allow writing to GPIO registers */
  if (g_pwpr_protect_counter == 0)
    {
      volatile uint8_t *pwpr = (volatile uint8_t *)(RZV_GPIO_BASE + RZV_GPIO_PWPR_OFFSET);

      /* Clear BOWI bit - writing to PFCWE bit enabled */
      *pwpr = 0x00;

      /* Set PFCWE bit (bit 6) - writing to PFC register enabled */
      *pwpr = 0x40;
    }

  /* Increment the protect counter */
  g_pwpr_protect_counter++;

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: rzv_gpio_pwpr_disable
 *
 * Description:
 *   Disable write access to GPIO registers
 *   Uses reference counter for re-entrancy protection
 *   Based on FSP R_BSP_PinAccessDisable()
 *
 ****************************************************************************/

static void rzv_gpio_pwpr_disable(void)
{
  irqstate_t flags;

  flags = enter_critical_section();

  /* Is it safe to disable GPIO register writing? */
  if (g_pwpr_protect_counter != 0)
    {
      g_pwpr_protect_counter--;
    }

  /* If counter reaches zero, disable GPIO register writing */
  if (g_pwpr_protect_counter == 0)
    {
      volatile uint8_t *pwpr = (volatile uint8_t *)(RZV_GPIO_BASE + RZV_GPIO_PWPR_OFFSET);

      /* Clear PFCWE bit - writing to PFC register disabled */
      *pwpr = 0x00;

      /* Set BOWI bit (bit 7) - writing to PFCWE bit disabled */
      *pwpr = 0x80;
    }

  leave_critical_section(flags);
}

#ifdef CONFIG_RZV_GPIO_IRQ

/****************************************************************************
 * Name: rzv_gpio_find_irq_slot
 *
 * Description:
 *   Find GPIO IRQ slot by pinset or find free slot
 *
 ****************************************************************************/

static int rzv_gpio_find_irq_slot(gpio_pinset_t pinset, bool find_free)
{
  int i;

  for (i = 0; i < MAX_GPIO_IRQS; i++)
    {
      if (find_free)
        {
          if (!g_gpio_irqs[i].allocated)
            {
              return i;
            }
        }
      else
        {
          if (g_gpio_irqs[i].allocated && g_gpio_irqs[i].pinset == pinset)
            {
              return i;
            }
        }
    }

  return -1;
}

/****************************************************************************
 * Name: rzv_gpio_irq_handler
 *
 * Description:
 *   GPIO interrupt handler that routes interrupts to user callbacks
 *
 ****************************************************************************/

static int rzv_gpio_irq_handler(int irq, void *context, void *arg)
{
  struct rzv_gpio_irq_s *gpio_irq = (struct rzv_gpio_irq_s *)arg;

  if (gpio_irq != NULL && gpio_irq->callback != NULL)
    {
      /* Call the user's callback function */
      return gpio_irq->callback(irq, context, gpio_irq->arg);
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_gpio_extract_irq_num
 *
 * Description:
 *   Extract IRQ number from GPIO pin configuration
 *   For RZV2H, IRQ pins are mapped through ISEL registers
 *
 ****************************************************************************/

static int rzv_gpio_extract_irq_num(gpio_pinset_t cfg)
{
  /* For RZV2H, IRQ number can be encoded in the configuration
   * or determined by pin mapping. For now, extract from lower bits
   * if ISEL configuration is present.
   */
  unsigned int port = rzv_gpio_extract_port(cfg);
  unsigned int pin = rzv_gpio_extract_pin(cfg);

  /* RZV2H GPIO IRQ mapping is hardware-specific
   * This is a simplified extraction - actual mapping may vary
   * IRQ number should be encoded in cfg or looked up from pin map
   */

  /* Extract IRQ number from bits [8:4] if present */
  int irq_num = (cfg >> 4) & 0x1F;

  /* Validate IRQ range */
  if (irq_num >= 0 && irq_num < MAX_GPIO_IRQS)
    {
      return irq_num;
    }

  return -1;  /* No IRQ associated with this pin */
}

#endif /* CONFIG_RZV_GPIO_IRQ */

/****************************************************************************
 * Name: rzv_gpio_get_port_base
 *
 * Description:
 *   Get the GPIO base address for a specific port
 *
 ****************************************************************************/

static uintptr_t rzv_gpio_get_port_base(unsigned int port)
{
  /* RZV2H has ports 0-11 (relative encoding)
   * Port 0-11 maps to hardware PORT20-PORT2B
   */
  if (port <= 11)
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

static inline unsigned int rzv_gpio_extract_port(gpio_pinset_t cfg)
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

static inline unsigned int rzv_gpio_extract_pin(gpio_pinset_t cfg)
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
 * Name: rzv_gpioconfigure_mode
 *
 * Description:
 *   Configure the GPIO mode (input/output) using PM register
 *   Based on FSP r_ioport_port_mode_pin_config
 *
 ****************************************************************************/

static int rzv_gpioconfigure_mode(unsigned int port, unsigned int pin,
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
 * Name: rzv_gpioconfigure_peripheral
 *
 * Description:
 *   Configure peripheral function using PMC and PFC registers
 *   Based on FSP r_ioport_peri_mode_pin_config
 *
 ****************************************************************************/

static int rzv_gpioconfigure_peripheral(unsigned int port, unsigned int pin,
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
 * Name: rzv_gpioconfigure_pull
 *
 * Description:
 *   Configure pull-up/pull-down using PUPD registers
 *   Note: PUPD registers not available on RZV2H, this is a placeholder
 *
 ****************************************************************************/

static int rzv_gpioconfigure_pull(unsigned int port, unsigned int pin,
                                   uint32_t pull)
{
  uintptr_t base = rzv_gpio_get_port_base(port);
  volatile uint32_t *p_pupd;
  uint32_t pupd_value;
  uint32_t mask;
  uint32_t shift;

  if (base == 0)
    {
      return -EINVAL;
    }

  /* RZV2H PUPD registers: 32-bit with _L/_H variants
   * _L registers handle pins 0-7 (2 bits per pin)
   * _H registers handle pins 8-15 (2 bits per pin)
   * PUPD values: 00=disable, 01=pull-up, 10=pull-down, 11=reserved
   */

  /* Calculate PUPD register offset based on port number
   * PUPD registers start at 0x1C10 for port 5 (PUPD5_L/H)
   * Ports 0-4 don't have PUPD registers
   */
  if (port < 5)
    {
      /* Ports 0-4 don't have PUPD configuration */
      return 0;
    }

  /* Determine if we need _L or _H register variant */
  if (pin < 8)
    {
      /* Use _L register (pins 0-7) */
      p_pupd = (volatile uint32_t *)(base + 0x1C10 + ((port - 5) * 8));
      shift = pin * 2;
    }
  else
    {
      /* Use _H register (pins 8-15) */
      p_pupd = (volatile uint32_t *)(base + 0x1C14 + ((port - 5) * 8));
      shift = (pin - 8) * 2;
    }

  /* Set pull configuration value */
  switch (pull)
    {
      case RZV_GPIO_PULLUP:
        pupd_value = PUPD_PULLUP;
        break;
      case RZV_GPIO_PULLDOWN:
        pupd_value = PUPD_PULLDOWN;
        break;
      default:
        pupd_value = PUPD_DISABLE;
        break;
    }

  /* Apply the configuration with proper masking */
  mask = 0x3 << shift;
  rzv_gpio_regwrite_32(p_pupd, pupd_value, shift, mask);

  return 0;
}

/****************************************************************************
 * Name: rzv_gpioconfigure_drive
 *
 * Description:
 *   Configure drive strength using IOLH registers
 *   Note: IOLH registers available but complex mapping for RZV2H
 *
 ****************************************************************************/

static int rzv_gpioconfigure_drive(unsigned int port, unsigned int pin,
                                    uint32_t drive)
{
  uintptr_t base = rzv_gpio_get_port_base(port);
  volatile uint32_t *p_iolh;
  uint32_t iolh_offset;
  uint32_t mask;
  uint32_t shift;

  if (base == 0 || drive > 3)
    {
      return -EINVAL;
    }

  /* RZV2H IOLH registers: 32-bit with _L/_H variants
   * _L registers handle pins 0-7 (2 bits per pin)
   * _H registers handle pins 8-15 (2 bits per pin)
   * IOLH registers start at different offsets per port
   */

  /* Calculate IOLH base offset for this port
   * IOLH3_L starts at 0x0FFC, subsequent ports increment by 8 bytes
   */
  if (port <= 2)
    {
      /* Ports 0-2 map to IOLH3-5 area */
      iolh_offset = 0x0FFC + ((port + 3) * 8);
    }
  else
    {
      /* Ports 3-11 map to IOLH6-14 and IOLH20-28 areas */
      iolh_offset = 0x1014 + ((port - 3) * 8);
    }

  /* Determine if we need _L or _H register variant */
  if (pin < 8)
    {
      /* Use _L register (pins 0-7) */
      p_iolh = (volatile uint32_t *)(base + iolh_offset);
      shift = pin * 2;
    }
  else
    {
      /* Use _H register (pins 8-15) */
      p_iolh = (volatile uint32_t *)(base + iolh_offset + 4);
      shift = (pin - 8) * 2;
    }

  /* Apply drive strength with proper masking
   * Drive values: 00=low, 01=medium-low, 10=medium-high, 11=high
   */
  mask = 0x3 << shift;
  rzv_gpio_regwrite_32(p_iolh, drive, shift, mask);

  return 0;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_gpioconfig
 *
 * Description:
 *   Configure a GPIO pin based on the GPIO_ definition from pinmap.
 *   This function extracts port/pin from the 32-bit pinmap encoding
 *   and configures the pin according to FSP ioport methodology.
 *
 ****************************************************************************/

int rzv_gpioconfig(gpio_pinset_t cfgset)
{
  unsigned int port;
  unsigned int pin;
  uint32_t mode;
  uint32_t psel;
  uint32_t pull;
  uint32_t drive;
  int ret;

  /* Extract port and pin using pinmap encoding */
  port = rzv_gpio_extract_port(cfgset);
  pin  = rzv_gpio_extract_pin(cfgset);

  /* Extract mode from configuration */
  mode = cfgset & GPIO_MODE_MASK;

  /* Extract PSEL from pinmap (MODEx definitions contain PSEL in lower bits) */
  psel = cfgset & PINMAP_PSEL_MASK;

  /* Extract pull configuration */
  pull = cfgset & GPIO_PULL_MASK;

  /* Extract drive strength */
  drive = (cfgset & GPIO_DRVSTR_MASK) >> GPIO_DRVSTR_SHIFT;

  /* Validate port */
  if (rzv_gpio_get_port_base(port) == 0)
    {
      return -EINVAL;
    }

  /* Enable PWPR protection for register writes */
  rzv_gpio_pwpr_enable();

  /* First, set to GPIO mode (PMC=0) */
  uintptr_t base = rzv_gpio_get_port_base(port);
  volatile uint8_t *p_pmc = (volatile uint8_t *)(base + RZV_GPIO_PMC_OFFSET(port));
  uint8_t pmc_val = *p_pmc;
  pmc_val &= ~(1 << pin);
  *p_pmc = pmc_val;

  /* Configure mode (PM register) */
  ret = rzv_gpioconfigure_mode(port, pin, mode);
  if (ret < 0)
    {
      rzv_gpio_pwpr_disable();
      return ret;
    }

  /* Configure peripheral function if needed */
  if (mode == RZV_GPIO_PERIPH)
    {
      ret = rzv_gpioconfigure_peripheral(port, pin, psel);
      if (ret < 0)
        {
          rzv_gpio_pwpr_disable();
          return ret;
        }
    }

  /* Configure pull-up/pull-down */
  ret = rzv_gpioconfigure_pull(port, pin, pull);
  if (ret < 0)
    {
      rzv_gpio_pwpr_disable();
      return ret;
    }

  /* Configure drive strength */
  ret = rzv_gpioconfigure_drive(port, pin, drive);
  if (ret < 0)
    {
      rzv_gpio_pwpr_disable();
      return ret;
    }

  /* Set initial output value if output mode */
  if (mode == RZV_GPIO_OUTPUT)
    {
      bool value = (cfgset & GPIO_OUTPUT_SET) != 0;
      rzv_gpiowrite(cfgset, value);
    }

  /* Disable PWPR protection */
  rzv_gpio_pwpr_disable();

  return 0;
}

/****************************************************************************
 * Name: rzv_gpiowrite
 *
 * Description:
 *   Write one or zero to the selected GPIO pin.
 *   Based on FSP R_BSP_PinWrite implementation.
 *
 ****************************************************************************/

void rzv_gpiowrite(gpio_pinset_t pinset, bool value)
{
  unsigned int port;
  unsigned int pin;
  uintptr_t base;
  volatile uint8_t *p_p;
  uint8_t mask_p;
  uint8_t value_p;

  /* Extract port and pin */
  port = rzv_gpio_extract_port(pinset);
  pin  = rzv_gpio_extract_pin(pinset);

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
 * Name: rzv_gpioread
 *
 * Description:
 *   Read the value from the selected GPIO pin.
 *   Based on FSP R_BSP_PinRead implementation.
 *
 ****************************************************************************/

bool rzv_gpioread(gpio_pinset_t pinset)
{
  unsigned int port;
  unsigned int pin;
  uintptr_t base;
  volatile const uint8_t *p_pin;
  uint8_t regval;

  /* Extract port and pin */
  port = rzv_gpio_extract_port(pinset);
  pin  = rzv_gpio_extract_pin(pinset);

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
 * Name: rzv_gpioconfiglist
 *
 * Description:
 *   Configure a list of GPIO pins based on an array of encoded pin
 *   configurations.
 *
 ****************************************************************************/

int rzv_gpioconfiglist(const gpio_pinset_t *cfgset, size_t count)
{
  int ret;
  size_t i;

  for (i = 0; i < count; i++)
    {
      ret = rzv_gpioconfig(cfgset[i]);
      if (ret < 0)
        {
          return ret;
        }
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_gpiosetpullup
 *
 * Description:
 *   Enable/disable pull-up resistor on GPIO pin
 *
 ****************************************************************************/

void rzv_gpiosetpullup(gpio_pinset_t pinset, bool enable)
{
  unsigned int port = rzv_gpio_extract_port(pinset);
  unsigned int pin = rzv_gpio_extract_pin(pinset);

  rzv_gpioconfigure_pull(port, pin, enable ? RZV_GPIO_PULLUP : RZV_GPIO_FLOAT);
}

/****************************************************************************
 * Name: rzv_gpio_set_pulldown
 *
 * Description:
 *   Enable/disable pull-down resistor on GPIO pin
 *
 ****************************************************************************/

void rzv_gpiosetpulldown(gpio_pinset_t pinset, bool enable)
{
  unsigned int port = rzv_gpio_extract_port(pinset);
  unsigned int pin = rzv_gpio_extract_pin(pinset);

  rzv_gpioconfigure_pull(port, pin, enable ? RZV_GPIO_PULLDOWN : RZV_GPIO_FLOAT);
}

/****************************************************************************
 * Name: rzv_gpio_setdrive
 *
 * Description:
 *   Set GPIO pin drive strength
 *
 ****************************************************************************/

void rzv_gpiosetdrivestrength(gpio_pinset_t pinset, uint8_t strength)
{
  unsigned int port = rzv_gpio_extract_port(pinset);
  unsigned int pin = rzv_gpio_extract_pin(pinset);

  rzv_gpioconfigure_drive(port, pin, strength);
}

/****************************************************************************
 * Name: rzv_gpiosetevent
 *
 * Description:
 *   Configure GPIO pin for external interrupt/event detection
 *
 ****************************************************************************/

int rzv_gpiosetevent(gpio_pinset_t pinset, bool rising, bool falling,
                     bool event, xcpt_t func, void *arg)
{
#ifdef CONFIG_RZV_GPIO_IRQ
  unsigned int port;
  unsigned int pin;
  uintptr_t base;
  volatile uint32_t *p_isel;
  uint32_t isel_offset;
  uint32_t isel_shift;
  uint32_t isel_mask;
  int irq_num;
  int slot;
  int icu_irq;
  uint8_t irq_mode;
  int ret;

  /* Extract port and pin */
  port = rzv_gpio_extract_port(pinset);
  pin  = rzv_gpio_extract_pin(pinset);

  /* Validate port and pin */
  base = rzv_gpio_get_port_base(port);
  if (base == 0 || pin > 15)
    {
      return -EINVAL;
    }

  /* Extract IRQ number from configuration */
  irq_num = rzv_gpio_extract_irq_num(pinset);
  if (irq_num < 0 || irq_num >= MAX_GPIO_IRQS)
    {
      return -EINVAL;
    }

  /* If callback is NULL, we're disabling the interrupt */
  if (func == NULL)
    {
      /* Find existing interrupt slot for this pin */
      slot = rzv_gpio_find_irq_slot(cfg, false);
      if (slot < 0)
        {
          return -ENODEV;  /* Pin not configured for interrupts */
        }

      /* Disable interrupt in ICU */
      if (g_gpio_irqs[slot].icu_slot >= 0)
        {
          rzv_icu_detach(g_gpio_irqs[slot].icu_slot);
        }

      /* Disable ISEL for this pin */
      rzv_gpio_pwpr_enable();

      /* Calculate ISEL register offset based on port
       * ISEL registers are at different offsets per port group
       */
      if (port >= 0 && port <= 11)
        {
          /* ISEL20-2B registers */
          isel_offset = 0x2CE8 + (port * 8);
        }
      else
        {
          rzv_gpio_pwpr_disable();
          return -EINVAL;
        }

      /* Determine _L or _H register variant and bit position */
      if (pin < 8)
        {
          p_isel = (volatile uint32_t *)(base + isel_offset);
          isel_shift = pin * 2;
        }
      else
        {
          p_isel = (volatile uint32_t *)(base + isel_offset + 4);
          isel_shift = (pin - 8) * 2;
        }

      /* Clear ISEL bits (disable interrupt input) */
      isel_mask = 0x3 << isel_shift;
      rzv_gpio_regwrite_32(p_isel, 0x00, isel_shift, isel_mask);

      rzv_gpio_pwpr_disable();

      /* Clear the slot */
      g_gpio_irqs[slot].allocated = false;
      g_gpio_irqs[slot].callback = NULL;
      g_gpio_irqs[slot].arg = NULL;
      g_gpio_irqs[slot].icu_slot = -1;
      g_gpio_irqs[slot].irq_num = 0;

      return OK;
    }

  /* Find a free interrupt slot */
  slot = rzv_gpio_find_irq_slot(0, true);
  if (slot < 0)
    {
      return -ENOMEM;  /* No free interrupt slots */
    }

  /* Configure pin as input for interrupt */
  ret = rzv_gpioconfigure_mode(port, pin, RZV_GPIO_INPUT);
  if (ret < 0)
    {
      return ret;
    }

  /* Configure ISEL register to enable interrupt input */
  rzv_gpio_pwpr_enable();

  /* Calculate ISEL register offset */
  if (port >= 0 && port <= 11)
    {
      isel_offset = 0x2CE8 + (port * 8);
    }
  else
    {
      rzv_gpio_pwpr_disable();
      return -EINVAL;
    }

  /* Determine _L or _H register variant */
  if (pin < 8)
    {
      p_isel = (volatile uint32_t *)(base + isel_offset);
      isel_shift = pin * 2;
    }
  else
    {
      p_isel = (volatile uint32_t *)(base + isel_offset + 4);
      isel_shift = (pin - 8) * 2;
    }

  /* Set ISEL bits to enable interrupt input
   * ISEL values: 00=disabled, 01=IRQ mode, 10/11=reserved
   */
  isel_mask = 0x3 << isel_shift;
  rzv_gpio_regwrite_32(p_isel, 0x01, isel_shift, isel_mask);

  rzv_gpio_pwpr_disable();

  /* Configure edge detection mode */
  if (rising && falling)
    {
      irq_mode = RZV_ICU_IRQ_EDGE_BOTH;
    }
  else if (rising)
    {
      irq_mode = RZV_ICU_IRQ_EDGE_RISING;
    }
  else if (falling)
    {
      irq_mode = RZV_ICU_IRQ_EDGE_FALLING;
    }
  else
    {
      /* Neither rising nor falling specified - default to both */
      irq_mode = RZV_ICU_IRQ_EDGE_BOTH;
    }

  /* Configure ICU for this external IRQ
   * GPIO IRQs map to GIC interrupts GPIO_IRQ0_IRQn through GPIO_IRQ15_IRQn
   */
  ret = rzv_icu_filter_config(irq_num, irq_mode, false, RZV_ICU_FILTER_PCLK_DIV_1);
  if (ret < 0)
    {
      return ret;
    }

  /* Attach interrupt handler through ICU
   * For RZV2H, GPIO IRQs are hardware IRQ lines, not ELC events
   * Use irq_num directly as the IRQ line
   */
  icu_irq = rzv_icu_attach(irq_num, rzv_gpio_irq_handler,
                           &g_gpio_irqs[slot], true);
  if (icu_irq < 0)
    {
      return icu_irq;
    }

  /* Store interrupt information */
  g_gpio_irqs[slot].pinset = pinset;
  g_gpio_irqs[slot].callback = func;
  g_gpio_irqs[slot].arg = arg;
  g_gpio_irqs[slot].icu_slot = icu_irq;
  g_gpio_irqs[slot].irq_num = irq_num;
  g_gpio_irqs[slot].allocated = true;

  return OK;
#else
  return -ENOSYS;  /* GPIO IRQ support not enabled */
#endif
}

#ifdef CONFIG_RZV_GPIO_IRQ

/****************************************************************************
 * Name: rzv_gpio_irq_initialize
 *
 * Description:
 *   Initialize GPIO interrupt subsystem
 *
 ****************************************************************************/

void rzv_gpio_irq_initialize(void)
{
  int i;

  /* Initialize all GPIO IRQ slots */
  for (i = 0; i < MAX_GPIO_IRQS; i++)
    {
      g_gpio_irqs[i].pinset = 0;
      g_gpio_irqs[i].callback = NULL;
      g_gpio_irqs[i].arg = NULL;
      g_gpio_irqs[i].icu_slot = -1;
      g_gpio_irqs[i].irq_num = 0;
      g_gpio_irqs[i].allocated = false;
    }
}

/****************************************************************************
 * Name: rzv_gpio_irq_attach
 *
 * Description:
 *   Attach an interrupt handler to a GPIO pin
 *
 ****************************************************************************/

int rzv_gpio_irq_attach(int irq, xcpt_t handler, void *arg)
{
  /* IRQ attachment is handled through rzv_gpiosetevent */
  return -ENOSYS;
}

/****************************************************************************
 * Name: rzv_gpio_irq_detach
 *
 * Description:
 *   Detach an interrupt handler from a GPIO pin
 *
 ****************************************************************************/

int rzv_gpio_irq_detach(int irq)
{
  int i;

  /* Find the IRQ slot by IRQ number */
  for (i = 0; i < MAX_GPIO_IRQS; i++)
    {
      if (g_gpio_irqs[i].allocated && g_gpio_irqs[i].irq_num == irq)
        {
          /* Call rzv_gpiosetevent with NULL to disable */
          return rzv_gpiosetevent(g_gpio_irqs[i].pinset, false, false,
                                  false, NULL, NULL);
        }
    }

  return -ENODEV;
}

/****************************************************************************
 * Name: rzv_gpio_irq_enable
 *
 * Description:
 *   Enable GPIO pin interrupt
 *
 ****************************************************************************/

void rzv_gpio_irq_enable(int irq)
{
  int i;

  /* Find the IRQ slot and enable through ICU */
  for (i = 0; i < MAX_GPIO_IRQS; i++)
    {
      if (g_gpio_irqs[i].allocated && g_gpio_irqs[i].irq_num == irq)
        {
          if (g_gpio_irqs[i].icu_slot >= 0)
            {
              up_enable_irq(g_gpio_irqs[i].icu_slot);
            }
          return;
        }
    }
}

/****************************************************************************
 * Name: rzv_gpio_irq_disable
 *
 * Description:
 *   Disable GPIO pin interrupt
 *
 ****************************************************************************/

void rzv_gpio_irq_disable(int irq)
{
  int i;

  /* Find the IRQ slot and disable through ICU */
  for (i = 0; i < MAX_GPIO_IRQS; i++)
    {
      if (g_gpio_irqs[i].allocated && g_gpio_irqs[i].irq_num == irq)
        {
          if (g_gpio_irqs[i].icu_slot >= 0)
            {
              up_disable_irq(g_gpio_irqs[i].icu_slot);
            }
          return;
        }
    }
}

#endif /* CONFIG_RZV_GPIO_IRQ */

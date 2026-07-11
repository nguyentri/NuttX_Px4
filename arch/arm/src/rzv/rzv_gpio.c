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
#include "rzv_clock.h"
#include "hardware/rzv_gpio.h"
#include "hardware/rzv_icu.h"
#include "hardware/rzv_pinmap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPIO Pinmap Encoding — canonical ABI (rzv_gpio.h GPIO_PORT/PIN_SHIFT).
 *
 * Port: bits [31:28] — relative port 0-11 (matches PORT0..PORT11 << 28)
 * Pin:  bits [27:24] — pin 0-15 within port (matches PIN0..PIN15 << 24)
 *
 * unified encoding; rzv_gpio.c and rzv_gpio.h now
 * agree on GPIO_PORT_SHIFT=28, GPIO_PIN_SHIFT=24 matching pinmap macros.
 * Source: rzv2h_pinmap.h PORT0=(0x00<<28), PIN0=(0<<24).
 */
#define PINMAP_GET_PORT(cfg)   (((cfg) >> GPIO_PORT_SHIFT) & 0xFU)
#define PINMAP_GET_PIN(cfg)    (((cfg) >> GPIO_PIN_SHIFT)  & 0xFU)

/* PM Register bit field values (2 bits per pin) */
#define PM_HIZ                 0x00U  /* Hi-Z (peripheral or analog) */
#define PM_INPUT_ONLY          0x02U  /* Input mode */
#define PM_OUTPUT              0x03U  /* Output mode */

/* PMC Register bit values (1 bit per pin) */
#define PMC_GPIO_MODE          0U    /* GPIO mode */
#define PMC_PERIPH_MODE        1U    /* Peripheral mode */

/* PUPD values: 2 bits per pin */
#define PUPD_DISABLE           0x00U
#define PUPD_PULLUP            0x01U
#define PUPD_PULLDOWN          0x02U

/* ISEL values: 2 bits per pin */
#define ISEL_DISABLE           0x00U  /* Interrupt input disabled */
#define ISEL_IRQ_MODE          0x01U  /* IRQ input enabled */

/* Register alignment stride constants */
#define GPIO_PIN_ALIGN_2BIT    2U
#define GPIO_PIN_ALIGN_4BIT    4U

/* Maximum supported ports: NuttX PORT0-PORT11 = HW P20-P2B.
 * Confirmed against FSP CMSIS R9A09G057H gpio_iodefine.h/gpio_iobitmask.h:
 * the R_GPIO_Type struct defines output-data registers P20..P2B only (12
 * ports); there is no P2C (grep of R_GPIO_P2C_ in gpio_iobitmask.h = 0
 * matches). The pin-mapping CSV likewise lists 12 physical ports (P0..PB).
 * So 12 is the true HW port count for this part — no ports 12+ exist.
 */
#define RZV_GPIO_MAX_PORT      12U

/* Per-port maximum pin count.
 * GP ports P20-P2B (NuttX ports 0-11) have varying pin counts.
 * Source: refs/rzv2h_scripts_pinmap/rzv2h_pin_mapping.csv bonded-pin rows
 * per port (verified 2026-07-11): P0=8, P1=6, P2=2, P3=8, P4=8, P5=8, P6=8,
 * P7=8, P8=8, P9=8, PA=8, PB=6 (86 bonded pins total).
 */
static const uint8_t g_rzv_port_pin_count[RZV_GPIO_MAX_PORT] =
{
  8U,  /* PORT0  = P20: 8 pins */
  6U,  /* PORT1  = P21: 6 pins */
  2U,  /* PORT2  = P22: 2 pins */
  8U,  /* PORT3  = P23: 8 pins */
  8U,  /* PORT4  = P24: 8 pins */
  8U,  /* PORT5  = P25: 8 pins */
  8U,  /* PORT6  = P26: 8 pins */
  8U,  /* PORT7  = P27: 8 pins */
  8U,  /* PORT8  = P28: 8 pins */
  8U,  /* PORT9  = P29: 8 pins */
  8U,  /* PORT10 = P2A: 8 pins */
  6U,  /* PORT11 = P2B: 6 pins */
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* PWPR protection counter for re-entrant critical section tracking */
static volatile uint32_t g_pwpr_protect_counter;

/* GPIO interrupt slot table */
#ifdef CONFIG_RZV_GPIO_IRQ

enum rzv_gpio_irq_path_e
{
  RZV_GPIO_IRQ_PATH_NONE = 0,
  RZV_GPIO_IRQ_PATH_IRQ  = 1,  /* Dedicated external IRQ0-15 line */
  RZV_GPIO_IRQ_PATH_TINT = 2,  /* TINT channel (any GPIO pin)     */
};

struct rzv_gpio_irq_s
{
  gpio_pinset_t pinset;       /* GPIO pin configuration */
  xcpt_t        callback;     /* User interrupt callback */
  void         *arg;          /* Callback argument */
  int           icu_slot;     /* NuttX IRQ from rzv_icu_attach() (-1=unused) */
  uint8_t       irq_num;      /* External IRQ line number 0-15 (IRQ path) */
  uint8_t       tint_channel; /* TINT channel 0-31 (TINT path) */
  uint8_t       trigger;      /* Configured trigger (edge/level enum) */
  uint8_t       path;         /* enum rzv_gpio_irq_path_e */
  bool          allocated;    /* Slot in use */
};

/* All icu_slot fields initialised to -1 by rzv_gpio_irq_initialize(). */
static struct rzv_gpio_irq_s g_gpio_irqs[MAX_GPIO_IRQS];

/* Cumulative GPIOINT source index per port for RZ/V2H, matching the FSP pin
 * → gpioint numbering used by the vendor r_intc_tint driver.  Formula:
 *
 *     gpioint(port, pin) = g_rzv_port_gpioint_base[port] + pin
 *
 * where the base is the sum of bonded pin counts for all lower-numbered
 * ports (P0=8, P1=6, P2=2, P3-P4=8 each ⇒ P5 base = 8+6+2+8+8 = 32).  This
 * was cross-verified against FSP hal_data.c:496, which sets
 * ".gpioint = 32" for the P5_0 MPU9250 DRDY input.  Total = 86 valid source
 * numbers, well inside the 7-bit TSSEL field.
 */

static const uint8_t g_rzv_port_gpioint_base[RZV_GPIO_MAX_PORT] =
{
  0U,   /* P0 base (P0=8 pins) */
  8U,   /* P1 base (P1=6 pins) */
  14U,  /* P2 base (P2=2 pins) */
  16U,  /* P3 base */
  24U,  /* P4 base */
  32U,  /* P5 base */
  40U,  /* P6 base */
  48U,  /* P7 base */
  56U,  /* P8 base */
  64U,  /* P9 base */
  72U,  /* PA base */
  80U,  /* PB base */
};

static inline uint8_t rzv_gpio_pin_to_gpioint(unsigned int port,
                                              unsigned int pin)
{
  return (uint8_t)(g_rzv_port_gpioint_base[port] + pin);
}
#endif

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static inline unsigned int rzv_gpio_extract_port(gpio_pinset_t cfg);
static inline unsigned int rzv_gpio_extract_pin(gpio_pinset_t cfg);
static uintptr_t rzv_gpio_get_port_base(unsigned int port);
static bool rzv_gpio_pin_valid(unsigned int port, unsigned int pin);
static void rzv_gpio_regwrite_8(volatile uint8_t *ioreg, uint8_t write_value,
                                uint8_t shift, uint8_t mask);
static void rzv_gpio_regwrite_16(volatile uint16_t *ioreg,
                                 uint16_t write_value, uint16_t shift,
                                 uint16_t mask);
static void rzv_gpio_regwrite_32(volatile uint32_t *ioreg,
                                 uint32_t write_value, uint32_t shift,
                                 uint32_t mask);
static void rzv_gpio_pwpr_enable(void);
static void rzv_gpio_pwpr_disable(void);
static int rzv_gpioconfigure_pull(unsigned int port, unsigned int pin,
                                  uint32_t pull);
static int rzv_gpioconfigure_drive(unsigned int port, unsigned int pin,
                                   uint32_t drive);
static int rzv_gpioconfigure_peripheral(unsigned int port, unsigned int pin,
                                        uint32_t psel, uint32_t func);
#ifdef CONFIG_RZV_GPIO_IRQ
static int rzv_gpioconfigure_mode_input(unsigned int port, unsigned int pin);
static int rzv_gpio_irq_handler_shim(int irq, void *context, void *arg);
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_gpio_extract_port / rzv_gpio_extract_pin
 *
 * Description:
 *   Extract port/pin from canonical 32-bit pinset.
 * use GPIO_PORT_SHIFT=28, GPIO_PIN_SHIFT=24.
 *   Source: rzv_gpio.h unified ABI; pinmap PORT0=(0<<28), PIN0=(0<<24).
 *
 ****************************************************************************/

static inline unsigned int rzv_gpio_extract_port(gpio_pinset_t cfg)
{
  return PINMAP_GET_PORT(cfg);
}

static inline unsigned int rzv_gpio_extract_pin(gpio_pinset_t cfg)
{
  return PINMAP_GET_PIN(cfg);
}

/****************************************************************************
 * Name: rzv_gpio_get_port_base
 *
 * Description:
 *   Validate port number and return GPIO peripheral base address.
 *   Returns 0 on invalid port.
 *
 ****************************************************************************/

static uintptr_t rzv_gpio_get_port_base(unsigned int port)
{
  if (port < RZV_GPIO_MAX_PORT)
    {
      return RZV_GPIO_BASE;
    }

  return 0;
}

/****************************************************************************
 * Name: rzv_gpio_pin_valid
 *
 * Description:
 * validate pin against per-port pin count.
 *   GP ports have varying widths (P20=8, P21=6, P22=2, ...).
 *   PMC is 8-bit (1 bit/pin, max 8 pins) and PM is 16-bit (2 bits/pin,
 *   max 8 pins) so any pin >= 8 is structurally invalid.
 *
 *   Returns true if the pin is valid for the given port.
 *
 ****************************************************************************/

static bool rzv_gpio_pin_valid(unsigned int port, unsigned int pin)
{
  if (port >= RZV_GPIO_MAX_PORT)
    {
      return false;
    }

  /* PMC is 8-bit; pin >= 8 would truncate mask to 0 */
  /* PM is 16-bit; pin*2 >= 16 would overflow the 16-bit shift */

  if (pin >= 8U)
    {
      return false;
    }

  return pin < (unsigned int)g_rzv_port_pin_count[port];
}

/****************************************************************************
 * Name: rzv_gpio_regwrite_8 / _16 / _32
 *
 * Description:
 *   Read-modify-write helpers for GPIO register access.
 *   Apply mask/shift to update only the targeted field without disturbing others.
 *
 ****************************************************************************/

static void rzv_gpio_regwrite_8(volatile uint8_t *ioreg, uint8_t write_value,
                                uint8_t shift, uint8_t mask)
{
  uint8_t reg_value = *ioreg;
  reg_value = (uint8_t)((reg_value & (uint8_t)(~mask)) | (write_value << shift));
  *ioreg = reg_value;
}

static void rzv_gpio_regwrite_16(volatile uint16_t *ioreg, uint16_t write_value,
                                 uint16_t shift, uint16_t mask)
{
  uint16_t reg_value = *ioreg;
  reg_value = (uint16_t)((reg_value & (uint16_t)(~mask)) | (write_value << shift));
  *ioreg = reg_value;
}

static void rzv_gpio_regwrite_32(volatile uint32_t *ioreg, uint32_t write_value,
                                 uint32_t shift, uint32_t mask)
{
  uint32_t reg_value = *ioreg;
  reg_value = (reg_value & ~mask) | (write_value << shift);
  *ioreg = reg_value;
}

/****************************************************************************
 * Name: rzv_gpio_pwpr_enable / rzv_gpio_pwpr_disable
 *
 * Description:
 *   Enable/disable PFC and PMC write protection via PWPR register.
 *
 * fix:
 *   RZV2H PWPR is 32-bit and uses REGWE_A (bit 6) semantics, NOT RA-style
 *   BOWI/PFSWE (bit 7/6 two-phase sequence). The old code wrote 8-bit values
 *   0x00/0x40 (enable) and 0x00/0x80 (disable) which:
 *     - Used 8-bit bus access (may be dropped on AXI)
 *     - Wrote bit 7 (undefined on RZV2H) during disable
 *     - Cleared REGWE_B accidentally during enable via 0x00 write
 *
 *   Correct RZ/V2H PWPR sequence:
 *     enable:  PWPR = (PWPR & REGWE_A_MASK) | REGWE_A_BIT   // RMW, set bit6
 *     disable: PWPR = (PWPR & REGWE_A_MASK)                 // RMW, clear bit6
 *
 *   Per RZ/V2H hardware manual GPIO section:
 *     PWPR REGWE_A bit offset = 6
 *     PWPR REGWE_A mask       = 0xFFFFFFBF
 *
 *   NOTE: caller must already hold a critical section; these functions
 *   additionally take their own critical section for the counter update.
 *
 ****************************************************************************/

static void rzv_gpio_pwpr_enable(void)
{
  irqstate_t flags = enter_critical_section();

  if (g_pwpr_protect_counter == 0)
    {
      volatile uint32_t *pwpr =
        (volatile uint32_t *)(RZV_GPIO_BASE + RZV_GPIO_PWPR_OFFSET);

      /* 32-bit RMW: set REGWE_A (bit 6), preserve REGWE_B (bit 5) and all
       * reserved bits.
       */
      *pwpr = (*pwpr & RZV_GPIO_PWPR_REGWE_A_MASK) | RZV_GPIO_PWPR_REGWE_A_BIT;
    }

  g_pwpr_protect_counter++;
  leave_critical_section(flags);
}

static void rzv_gpio_pwpr_disable(void)
{
  irqstate_t flags = enter_critical_section();

  if (g_pwpr_protect_counter != 0)
    {
      g_pwpr_protect_counter--;
    }

  if (g_pwpr_protect_counter == 0)
    {
      volatile uint32_t *pwpr =
        (volatile uint32_t *)(RZV_GPIO_BASE + RZV_GPIO_PWPR_OFFSET);

      /* 32-bit RMW: clear REGWE_A (bit 6), preserve REGWE_B (bit 5).
       * old code wrote 0x80 to bits[7] — undefined on RZV2H.
       */
      *pwpr = (*pwpr & RZV_GPIO_PWPR_REGWE_A_MASK);
    }

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: rzv_gpioconfigure_pull
 *
 * Description:
 *   Configure pull-up/pull-down via PUPD GP-group registers.
 *
 * fix:
 *   Old code: skipped ports 0-4 (returned early), used formula
 *     0x1C10 + (port-5)*8 for ports 5-11 — wrong for port 5 offset and
 *     wrong uniform-stride assumption (missing gap at PUPDD in SP group).
 *
 *   Correct: NuttX ports 0-11 are GP group (ports 0x20-0x2B per RZ/V2H UM).
 *   All have PUPD registers starting at PUPD20_L (0x1CE8). Formula:
 *     offset = PUPD20_L_OFFSET + port*8 + (pin >= 8 ? 4 : 0)
 *   Bit position within register: (pin % 8) * 2
 *
 *   Per RZ/V2H hardware manual GPIO §PUPD:
 *     adr_offset_pupd = port*2 + pin/4  (with p_pupd base = &R_GPIO->PUPD20_L)
 *     Which equals: PUPD20_L_OFFSET + port*8 + (pin/4)*4
 *     Simplified for _L/_H split: PUPD20_L + port*8, PUPD20_H + port*8
 *   Source: hardware/rzv_gpio.h RZV_GPIO_GP_PUPD_L/H_OFFSET macros.
 *
 ****************************************************************************/

static int rzv_gpioconfigure_pull(unsigned int port, unsigned int pin,
                                  uint32_t pull)
{
  uintptr_t         base = rzv_gpio_get_port_base(port);
  volatile uint32_t *p_pupd;
  uint32_t           pupd_value;
  uint32_t           shift;
  uint32_t           mask;

  /* validate pin against per-port pin count (max 7 for GP ports) */

  if (base == 0 || !rzv_gpio_pin_valid(port, pin))
    {
      return -EINVAL;
    }

  /* 4 pins per 32-bit register, 8 bits per pin (RZ/V2H UM GPIO).
   * _L holds pins 0-3, _H holds pins 4-7.  Shift = (pin % 4) * 8.
   * Old code: split at pin<8 with shift=pin*2 — wrong register AND wrong shift.
   * Source: hardware/rzv_gpio.h GPIO_PUPD20_L_IOLH_SHIFT(n) = n*8.
   * bitpos_align = (pin & 3) * 8 per RZ/V2H UM GPIO §PUPD.
   */
  if (pin < 4U)
    {
      p_pupd = (volatile uint32_t *)(base + RZV_GPIO_GP_PUPD_L_OFFSET(port));
    }
  else
    {
      p_pupd = (volatile uint32_t *)(base + RZV_GPIO_GP_PUPD_H_OFFSET(port));
    }

  shift = (pin & 3U) * 8U;

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

  mask = 0x3U << shift;
  rzv_gpio_regwrite_32(p_pupd, pupd_value, shift, mask);
  return OK;
}

/****************************************************************************
 * Name: rzv_gpioconfigure_drive
 *
 * Description:
 *   Configure drive strength via IOLH GP-group registers.
 *
 * fix:
 *   Old code:
 *     port 0-2: iolh_offset = 0x0FFC + (port+3)*8  → SP-group base (wrong)
 *     port 3-11: iolh_offset = 0x1014 + (port-3)*8 → skips gap at IOLHD
 *   Both paths are wrong for NuttX ports 0-11 which are GP group ports.
 *
 *   Correct: GP ports use IOLH20_L (0x10E4) as base per RZ/V2H UM GPIO.
 *     offset = IOLH20_L_OFFSET + port*8 + (pin >= 8 ? 4 : 0)
 *
 *   Per RZ/V2H hardware manual GPIO §IOLH:
 *     adr_offset_iolh = port*2 + pin/4  (p_iolh base = &R_GPIO->IOLH20_L)
 *   Source: hardware/rzv_gpio.h RZV_GPIO_GP_IOLH_L/H_OFFSET macros.
 *   GP_REG_BASE_NUM = 20 (GP group base port number per RZ/V2H UM).
 *
 ****************************************************************************/

static int rzv_gpioconfigure_drive(unsigned int port, unsigned int pin,
                                   uint32_t drive)
{
  uintptr_t         base = rzv_gpio_get_port_base(port);
  volatile uint32_t *p_iolh;
  uint32_t           shift;
  uint32_t           mask;

  /* validate pin; IOLH is 2-bit field per pin, 4 pins per reg */

  if (base == 0 || drive > 3U || !rzv_gpio_pin_valid(port, pin))
    {
      return -EINVAL;
    }

  /* _L = pins 0-3, _H = pins 4-7, shift = (pin%4)*8.
   * bitpos_align = (pin & 3) * 8 per RZ/V2H UM GPIO §IOLH.
   * Source: hardware/rzv_gpio.h GPIO_IOLH20_L_IOLH_SHIFT(n) = n*8.
   */

  if (pin < 4U)
    {
      p_iolh = (volatile uint32_t *)(base + RZV_GPIO_GP_IOLH_L_OFFSET(port));
    }
  else
    {
      p_iolh = (volatile uint32_t *)(base + RZV_GPIO_GP_IOLH_H_OFFSET(port));
    }

  shift = (pin & 3U) * 8U;
  mask  = 0x3U << shift;
  rzv_gpio_regwrite_32(p_iolh, drive, shift, mask);
  return OK;
}

/****************************************************************************
 * Name: rzv_gpioconfigure_peripheral
 *
 * Description:
 *   Configure peripheral function: PMC=1, PFC=psel, NOD (open-drain).
 *   Slew rate (SR) is not written — caller passes default (keep reset value).
 *
 * fix:
 *   Peripheral mode pin configuration programs PFC, IOLH, PUPD, SR, NOD, IEN.
 *   This implementation adds NOD (open-drain) for I2C compatibility.
 *   SR and IEN are deferred (no pinset encoding yet, safe to leave at reset).
 * TODO: Encode SR/IEN in pinset GPIO_FUNC bits and apply here.
 *
 *   Caller (rzv_gpioconfig) has already written PMC=0 before calling here.
 *   We write PMC=1 inside to complete the PFC programming window.
 *
 * PFC is programmed before PM per RZ/V2H UM ordering.
 *   Caller sets PM=Hi-Z after this function returns.
 *
 ****************************************************************************/

static int rzv_gpioconfigure_peripheral(unsigned int port, unsigned int pin,
                                        uint32_t psel, uint32_t func)
{
  uintptr_t         base = rzv_gpio_get_port_base(port);
  volatile uint8_t  *p_pmc;
  volatile uint32_t *p_pfc;
  volatile uint32_t *p_nod;
  uint32_t           shift;
  uint32_t           mask;

  /* validate pin; PMC is 8-bit, pin>=8 truncates mask */

  if (base == 0 || !rzv_gpio_pin_valid(port, pin))
    {
      return -EINVAL;
    }

  /* PMC=1: enable peripheral mode for this pin */
  p_pmc = (volatile uint8_t *)(base + RZV_GPIO_PMC_OFFSET(port));
  rzv_gpio_regwrite_8(p_pmc, PMC_PERIPH_MODE, (uint8_t)pin,
                      (uint8_t)(1U << pin));

  /* PFC: set peripheral function select (4 bits per pin).
   * Per RZ/V2H UM GPIO §PFC: 4-bit field at pin*4 in 32-bit reg (field mask = 0xF).
   */
  p_pfc = (volatile uint32_t *)(base + RZV_GPIO_PFC_OFFSET(port));
  shift = pin * GPIO_PIN_ALIGN_4BIT;
  mask  = 0xFU << shift;
  rzv_gpio_regwrite_32(p_pfc, psel & 0xFU, shift, mask);

  /* NOD: N-channel open-drain mode for I2C/SMBus pins.
   * same 4-pins-per-reg, 8-bits-per-pin layout as IOLH/PUPD.
   * _L = pins 0-3, _H = pins 4-7, shift = (pin % 4) * 8.
   * Source: hardware/rzv_gpio.h NOD macros (4-pins-per-reg, 8-bits-per-pin layout).
   */
  if (pin < 4U)
    {
      p_nod = (volatile uint32_t *)(base + RZV_GPIO_GP_NOD_L_OFFSET(port));
    }
  else
    {
      p_nod = (volatile uint32_t *)(base + RZV_GPIO_GP_NOD_H_OFFSET(port));
    }

  shift = (pin & 3U) * 8U;
  mask  = 0x3U << shift;
  /* NOD value: 01=open-drain, 00=push-pull (2-bit field per RZ/V2H UM GPIO) */
  rzv_gpio_regwrite_32(p_nod,
                       (func & RZV_GPIO_OPENDRAIN) ? 0x01U : 0x00U,
                       shift, mask);

  return OK;
}

#ifdef CONFIG_RZV_GPIO_IRQ

/****************************************************************************
 * Name: rzv_gpioconfigure_mode_input
 *
 * Description:
 *   Set a pin to GPIO input mode. Helper used by rzv_gpiosetevent.
 *   Acquires its own critical section + PWPR.
 *
 ****************************************************************************/

static int rzv_gpioconfigure_mode_input(unsigned int port, unsigned int pin)
{
  uintptr_t          base = rzv_gpio_get_port_base(port);
  irqstate_t         flags;
  volatile uint8_t  *p_pmc;
  volatile uint16_t *p_pm;
  uint16_t           pm_mask;

  /* validate pin; PM is 16-bit (max shift 14 for pin 7) */

  if (base == 0 || !rzv_gpio_pin_valid(port, pin))
    {
      return -EINVAL;
    }

  flags = enter_critical_section();
  rzv_gpio_pwpr_enable();

  /* Force GPIO mode (PMC=0) */
  p_pmc = (volatile uint8_t *)(base + RZV_GPIO_PMC_OFFSET(port));
  rzv_gpio_regwrite_8(p_pmc, PMC_GPIO_MODE, (uint8_t)pin,
                      (uint8_t)(1U << pin));

  /* Set PM=input */
  p_pm    = (volatile uint16_t *)(base + RZV_GPIO_PM_OFFSET(port));
  pm_mask = (uint16_t)(0x3U << (pin * GPIO_PIN_ALIGN_2BIT));
  rzv_gpio_regwrite_16(p_pm, PM_INPUT_ONLY,
                       (uint16_t)(pin * GPIO_PIN_ALIGN_2BIT), pm_mask);

  rzv_gpio_pwpr_disable();
  leave_critical_section(flags);
  return OK;
}



/****************************************************************************
 * Name: rzv_gpio_irq_handler_shim
 *
 * Description:
 *   Internal IRQ shim that routes a GIC interrupt to the user callback.
 *   Registered as the NuttX ISR via rzv_icu_attach().
 *
 ****************************************************************************/

static int rzv_gpio_irq_handler_shim(int irq, void *context, void *arg)
{
  struct rzv_gpio_irq_s *gpio_irq = (struct rzv_gpio_irq_s *)arg;

  if (gpio_irq == NULL)
    {
      return OK;
    }

  /* TINT edge triggers: clear the TINT status flag BEFORE invoking the user
   * callback, matching FSP r_intc_tint_isr: an edge arriving while the ISR
   * is active must be captured for the next dispatch, not lost.  Level-
   * triggered TINT tracks the pin state directly and does not use TSCLR.
   * IRQ0-15 lines: GIC edge-cleared on ack; no ISCLR walk needed here.
   */

  if (gpio_irq->path == RZV_GPIO_IRQ_PATH_TINT &&
      (gpio_irq->trigger == ICU_TITSR_RISING ||
       gpio_irq->trigger == ICU_TITSR_FALLING))
    {
      rzv_icu_tint_clear_flag(gpio_irq->tint_channel);
    }

  if (gpio_irq->callback != NULL)
    {
      return gpio_irq->callback(irq, context, gpio_irq->arg);
    }

  return OK;
}

#endif /* CONFIG_RZV_GPIO_IRQ */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_gpioconfig
 *
 * Description:
 *   Configure a GPIO pin based on the gpio_pinset_t encoding.
 *
 * fixes applied:
 * GPIO module clock gate before first register access.
 * 32-bit RMW PWPR (REGWE_A semantics).
 * IOLH via GP-group lookup (not hand-rolled formula).
 * PUPD via GP-group lookup.
 * Full PMC/PFC/PM/IOLH/PUPD RMW under critical section.
 * NOD (open-drain) written in peripheral mode.
 * Correct order per RZ/V2H UM: PMC(0) → PFC → IOLH → PUPD → P → PM.
 * P register written BEFORE PM=OUTPUT to avoid glitch.
 *
 ****************************************************************************/

int rzv_gpioconfig(gpio_pinset_t cfgset)
{
  unsigned int       port;
  unsigned int       pin;
  uint32_t           mode;
  uint32_t           psel;
  uint32_t           pull;
  uint32_t           drive;
  uint32_t           func;
  irqstate_t         flags;
  uintptr_t          base;
  volatile uint8_t  *p_pmc;
  volatile uint16_t *p_pm;
  volatile uint8_t  *p_p;
  uint16_t           pm_mask;
  int                ret = OK;

  /* Decode pinset using canonical ABI */
  port  = rzv_gpio_extract_port(cfgset);
  pin   = rzv_gpio_extract_pin(cfgset);
  mode  = cfgset & GPIO_MODE_MASK;
  psel  = cfgset & GPIO_PSEL_MASK;            /* bits [3:0] only */
  pull  = cfgset & GPIO_PULL_MASK;
  drive = (cfgset & GPIO_DRVSTR_MASK) >> GPIO_DRVSTR_SHIFT;
  func  = cfgset & GPIO_FUNC_MASK;

  base = rzv_gpio_get_port_base(port);

  /* validate pin against per-port count; pin>=8 UB */

  if (base == 0 || !rzv_gpio_pin_valid(port, pin))
    {
      return -EINVAL;
    }

  /* Reject out-of-range field values instead of silently degrading.
   * mode: only INPUT/OUTPUT/PERIPH/ANALOG (0-3) are defined; a larger value
   *   previously fell through to PM_HIZ with no diagnostic.
   * pull: only FLOAT/PULLUP/PULLDOWN (0-2) are defined; a larger value
   *   previously mapped silently to PUPD_DISABLE.
   * drive: 0-3, already range-checked in rzv_gpioconfigure_drive().
   * psel:  bits [3:0], every value 0-F is a valid peripheral select, so no
   *   additional check is required.
   */
  if ((mode >> GPIO_MODE_SHIFT) > (RZV_GPIO_ANALOG >> GPIO_MODE_SHIFT))
    {
      return -EINVAL;
    }

  if ((pull >> GPIO_PULL_SHIFT) > (RZV_GPIO_PULLDOWN >> GPIO_PULL_SHIFT))
    {
      return -EINVAL;
    }

  /* No GPIO module clock gate is programmed here.  FSP r_ioport never
   * gates a GPIO/PFC clock on RZ/V2H (bsp_override.h has no
   * FSP_IP_GPIO CLKON mapping); the PFC block is clocked unconditionally.
   * The previous rzv_clock_enable(RZV_CPG_CLK_GPIO) call used the
   * placeholder ID (domain 0, bit 0), which matched the DMAC domain
   * special-case in rzv_clock_enable() and gated all five DMAC clocks
   * on as a side effect.
   */

  /* Critical section wraps the ENTIRE PMC/PFC/IOLH/PUPD/
   * PM RMW sequence to prevent concurrent config on the same port byte.
   */
  flags = enter_critical_section();
  rzv_gpio_pwpr_enable();  /* 32-bit RMW PWPR */

  /* step 1: PMC=0 (force GPIO mode).
   * This must precede PFC programming per RZ/V2H UM GPIO §PMC.
   */
  p_pmc = (volatile uint8_t *)(base + RZV_GPIO_PMC_OFFSET(port));
  rzv_gpio_regwrite_8(p_pmc, PMC_GPIO_MODE, (uint8_t)pin,
                      (uint8_t)(1U << pin));

  /* Step 2: PFC + PMC=1 (only if peripheral mode).
   * PFC written before PM per RZ/V2H UM ordering.
   */
  if (mode == RZV_GPIO_PERIPH)
    {
      ret = rzv_gpioconfigure_peripheral(port, pin, psel, func);
      if (ret < 0)
        {
          goto out;
        }
    }

  /* Step 3: Drive strength (IOLH).
   * GP-group lookup, not SP-group formula.
   */
  ret = rzv_gpioconfigure_drive(port, pin, drive);
  if (ret < 0)
    {
      goto out;
    }

  /* Step 4: Pull configuration (PUPD).
   * GP-group lookup, covers all ports 0-11.
   */
  ret = rzv_gpioconfigure_pull(port, pin, pull);
  if (ret < 0)
    {
      goto out;
    }

  /* Step 5: Set output latch (P register) BEFORE enabling output in PM.
   * avoids glitch on active-high-idle pins (e.g. SPI CS).
   * Writing P before PM avoids output glitch per RZ/V2H GPIO timing requirements.
   */
  if (mode == RZV_GPIO_OUTPUT)
    {
      bool initial_high = (cfgset & GPIO_OUTPUT_SET) != 0;
      p_p = (volatile uint8_t *)(base + RZV_GPIO_P_OFFSET(port));
      rzv_gpio_regwrite_8(p_p, initial_high ? 1U : 0U, (uint8_t)pin,
                          (uint8_t)(1U << pin));
    }

  /* Step 6: Configure PM register (port direction) — written last per RZ/V2H UM.
   * For peripheral mode: PM=Hi-Z (pin driven by peripheral via PFC).
   * PM is set after PFC/PMC/IOLH/PUPD per GPIO initialization sequence.
   */
  p_pm    = (volatile uint16_t *)(base + RZV_GPIO_PM_OFFSET(port));
  pm_mask = (uint16_t)(0x3U << (pin * GPIO_PIN_ALIGN_2BIT));

  {
    uint16_t pm_val;
    if (mode == RZV_GPIO_OUTPUT)
      {
        pm_val = PM_OUTPUT;
      }
    else if (mode == RZV_GPIO_INPUT)
      {
        pm_val = PM_INPUT_ONLY;
      }
    else
      {
        pm_val = PM_HIZ;  /* Peripheral or analog */
      }

    rzv_gpio_regwrite_16(p_pm, pm_val,
                         (uint16_t)(pin * GPIO_PIN_ALIGN_2BIT), pm_mask);
  }

out:
  rzv_gpio_pwpr_disable();
  leave_critical_section(flags);
  return ret;
}

/****************************************************************************
 * Name: rzv_gpiowrite
 *
 * Description:
 *   Write high/low to a GPIO output pin.
 * returns int (OK/-EINVAL) instead of void so that
 * callers can detect invalid port. Source: .
 *
 ****************************************************************************/

int rzv_gpiowrite(gpio_pinset_t pinset, bool value)
{
  unsigned int      port;
  unsigned int      pin;
  uintptr_t         base;
  volatile uint8_t *p_p;
  irqstate_t        flags;

  port = rzv_gpio_extract_port(pinset);
  pin  = rzv_gpio_extract_pin(pinset);

  base = rzv_gpio_get_port_base(port);
  if (base == 0)
    {
      return -EINVAL;
    }

  /* The per-port P (output data) register is a shared byte: one bit per pin.
   * Two threads/ISRs toggling different pins of the same port each do an
   * 8-bit read-modify-write, so without mutual exclusion one update can be
   * lost.  Wrap the RMW in a critical section.
   *
   * No PWPR unlock is used here: the P register is NOT write-protected on
   * RZ/V2H (only PFC/PMC and the pin-config registers are gated by PWPR).
   * Verified against FSP r_ioport.c R_IOPORT_PinWrite/PortWrite, which write
   * the P register directly with no PinAccessEnable/Disable window.
   */
  p_p = (volatile uint8_t *)(base + RZV_GPIO_P_OFFSET(port));

  flags = enter_critical_section();
  rzv_gpio_regwrite_8(p_p, value ? 1U : 0U, (uint8_t)pin,
                      (uint8_t)(1U << pin));
  leave_critical_section(flags);
  return OK;
}

/****************************************************************************
 * Name: rzv_gpioread
 *
 * Description:
 *   Read the value of a GPIO pin via PIN register.
 *   Returns false on invalid port (caller cannot distinguish from low — LOW).
 *
 ****************************************************************************/

bool rzv_gpioread(gpio_pinset_t pinset)
{
  unsigned int            port;
  unsigned int            pin;
  uintptr_t               base;
  volatile const uint8_t *p_pin;

  port = rzv_gpio_extract_port(pinset);
  pin  = rzv_gpio_extract_pin(pinset);

  base = rzv_gpio_get_port_base(port);
  if (base == 0)
    {
      return false;
    }

  p_pin = (volatile const uint8_t *)(base + RZV_GPIO_PIN_OFFSET(port));
  return ((*p_pin >> pin) & 0x1U) != 0;
}

/****************************************************************************
 * Name: rzv_unconfiggpio
 *
 * Description:
 *   Release a pin back to a safe, inert default (NuttX unconfig semantics,
 *   cf. stm32_unconfiggpio): GPIO mode, high-impedance (no input/output
 *   driver), no peripheral function, no pull, default drive, push-pull, and
 *   interrupt-input select disabled.  After this call the pin drives nothing
 *   and generates no interrupt.
 *
 *   The whole sequence runs under one critical section + PWPR window (PMC/PFC
 *   are write-protected by PWPR; the remaining config registers are written
 *   in the same window, matching rzv_gpioconfig()).
 *
 * Input Parameters:
 *   pinset - GPIO pin configuration (only port/pin are used)
 *
 * Returned Value:
 *   Zero (OK) on success; -EINVAL on invalid port/pin.
 *
 ****************************************************************************/

int rzv_unconfiggpio(gpio_pinset_t pinset)
{
  unsigned int       port;
  unsigned int       pin;
  uintptr_t          base;
  irqstate_t         flags;
  volatile uint8_t  *p_pmc;
  volatile uint16_t *p_pm;
  volatile uint32_t *p_pfc;
  volatile uint32_t *p_nod;
  volatile uint32_t *p_isel;
  uint32_t           shift;
  uint32_t           mask;
  uint16_t           pm_mask;

  port = rzv_gpio_extract_port(pinset);
  pin  = rzv_gpio_extract_pin(pinset);

  base = rzv_gpio_get_port_base(port);
  if (base == 0 || !rzv_gpio_pin_valid(port, pin))
    {
      return -EINVAL;
    }

  flags = enter_critical_section();
  rzv_gpio_pwpr_enable();

  /* PM = Hi-Z first: stop driving the pin before anything else changes. */
  p_pm    = (volatile uint16_t *)(base + RZV_GPIO_PM_OFFSET(port));
  pm_mask = (uint16_t)(0x3U << (pin * GPIO_PIN_ALIGN_2BIT));
  rzv_gpio_regwrite_16(p_pm, PM_HIZ,
                       (uint16_t)(pin * GPIO_PIN_ALIGN_2BIT), pm_mask);

  /* PMC = 0: return the pin to GPIO mode (also required before PFC clear). */
  p_pmc = (volatile uint8_t *)(base + RZV_GPIO_PMC_OFFSET(port));
  rzv_gpio_regwrite_8(p_pmc, PMC_GPIO_MODE, (uint8_t)pin,
                      (uint8_t)(1U << pin));

  /* PFC = 0: clear the 4-bit peripheral function select for this pin. */
  p_pfc = (volatile uint32_t *)(base + RZV_GPIO_PFC_OFFSET(port));
  shift = pin * GPIO_PIN_ALIGN_4BIT;
  mask  = 0xFU << shift;
  rzv_gpio_regwrite_32(p_pfc, 0U, shift, mask);

  /* ISEL = 0: disable interrupt-input selection (4-pins/reg, 8-bit/pin). */
  if (pin < 4U)
    {
      p_isel = (volatile uint32_t *)(base + RZV_GPIO_GP_ISEL_L_OFFSET(port));
    }
  else
    {
      p_isel = (volatile uint32_t *)(base + RZV_GPIO_GP_ISEL_H_OFFSET(port));
    }

  shift = (pin & 3U) * 8U;
  mask  = 0x3U << shift;
  rzv_gpio_regwrite_32(p_isel, ISEL_DISABLE, shift, mask);

  /* NOD = 0: push-pull (clear open-drain). */
  if (pin < 4U)
    {
      p_nod = (volatile uint32_t *)(base + RZV_GPIO_GP_NOD_L_OFFSET(port));
    }
  else
    {
      p_nod = (volatile uint32_t *)(base + RZV_GPIO_GP_NOD_H_OFFSET(port));
    }

  rzv_gpio_regwrite_32(p_nod, 0U, shift, mask);

  /* PUPD = float, IOLH = default (0) via the shared helpers.  These are
   * lock-free by design and run inside the critical section + PWPR window
   * already held here, exactly as rzv_gpioconfig() calls them.
   */
  rzv_gpioconfigure_pull(port, pin, RZV_GPIO_FLOAT);
  rzv_gpioconfigure_drive(port, pin, 0U);

  rzv_gpio_pwpr_disable();
  leave_critical_section(flags);
  return OK;
}

/****************************************************************************
 * Name: rzv_gpioconfiglist
 *
 ****************************************************************************/

int rzv_gpioconfiglist(const gpio_pinset_t *cfgset, size_t count)
{
  int    ret;
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
 * Name: rzv_gpiosetpullup / rzv_gpiosetpulldown
 *
 ****************************************************************************/

void rzv_gpiosetpullup(gpio_pinset_t pinset, bool enable)
{
  irqstate_t flags = enter_critical_section();
  rzv_gpio_pwpr_enable();
  rzv_gpioconfigure_pull(rzv_gpio_extract_port(pinset),
                         rzv_gpio_extract_pin(pinset),
                         enable ? RZV_GPIO_PULLUP : RZV_GPIO_FLOAT);
  rzv_gpio_pwpr_disable();
  leave_critical_section(flags);
}

void rzv_gpiosetpulldown(gpio_pinset_t pinset, bool enable)
{
  irqstate_t flags = enter_critical_section();
  rzv_gpio_pwpr_enable();
  rzv_gpioconfigure_pull(rzv_gpio_extract_port(pinset),
                         rzv_gpio_extract_pin(pinset),
                         enable ? RZV_GPIO_PULLDOWN : RZV_GPIO_FLOAT);
  rzv_gpio_pwpr_disable();
  leave_critical_section(flags);
}

/****************************************************************************
 * Name: rzv_gpiosetdrivestrength
 *
 ****************************************************************************/

void rzv_gpiosetdrivestrength(gpio_pinset_t pinset, uint8_t strength)
{
  irqstate_t flags = enter_critical_section();
  rzv_gpio_pwpr_enable();
  rzv_gpioconfigure_drive(rzv_gpio_extract_port(pinset),
                          rzv_gpio_extract_pin(pinset),
                          strength);
  rzv_gpio_pwpr_disable();
  leave_critical_section(flags);
}

/****************************************************************************
 * Name: rzv_gpiosetevent
 *
 * Description:
 *   Attach or detach a GPIO interrupt callback.  Two routing paths:
 *
 *   - IRQ0-15 direct lines (default): dedicated external IRQ lines usable
 *     only on IRQ-capable pins.  Encode the line number in the pinset via
 *     GPIO_IRQ(n) or the IRQ0..IRQ15 pinmap macros (bits [23:20]).
 *
 *   - TINT channel (any GPIO pin): set the RZV_GPIO_TINT flag in the pinset
 *     to route through one of 32 shared TINT channels.  Trigger mode is
 *     rising / falling / high-level / low-level; both-edge is NOT supported
 *     natively by TINT hardware and returns -EINVAL — emulate at the caller
 *     if needed.
 *
 *   The IRQ-line field [23:20] and the open-drain flag [4] no longer share
 *   bits (Phase 1 encoding fix), and TINT selection lives in the Func field
 *   at bit 5 (RZV_GPIO_TINT) so the two routing paths are unambiguous.
 *
 ****************************************************************************/

int rzv_gpiosetevent(gpio_pinset_t pinset, bool rising, bool falling,
                     bool event, xcpt_t func, void *arg)
{
#ifdef CONFIG_RZV_GPIO_IRQ
  unsigned int port;
  unsigned int pin;
  uintptr_t    base;
  int          slot;
  int          icu_irq;
  irqstate_t   flags;
  int          ret;
  int          i;
  bool         use_tint;
  int          irq_num = 0;

  port = rzv_gpio_extract_port(pinset);
  pin  = rzv_gpio_extract_pin(pinset);

  base = rzv_gpio_get_port_base(port);

  /* validate pin against per-port count; pin>=8 UB */

  if (base == 0 || !rzv_gpio_pin_valid(port, pin))
    {
      return -EINVAL;
    }

  use_tint = ((pinset & RZV_GPIO_TINT) != 0U);

  if (!use_tint)
    {
      /* IRQ0-15 direct-line path. Line number from GPIO_IRQ field [23:20]. */
      irq_num = (int)((pinset & GPIO_IRQ_MASK) >> GPIO_IRQ_SHIFT);
      if (irq_num < 0 || irq_num >= MAX_GPIO_IRQS)
        {
          return -EINVAL;
        }
    }

  /* -------------------- DETACH -------------------- */

  if (func == NULL)
    {
      slot = -1;
      for (i = 0; i < MAX_GPIO_IRQS; i++)
        {
          if (g_gpio_irqs[i].allocated && g_gpio_irqs[i].pinset == pinset)
            {
              slot = i;
              break;
            }
        }

      if (slot < 0)
        {
          return -ENODEV;
        }

      /* Tear down GIC first so no interrupt can be delivered into a slot
       * with a NULL callback.  IRQ0-15 use fixed GIC INTIDs (irq_attach);
       * TINT uses dynamic INTR8SEL slots (rzv_icu_attach).
       */
      if (g_gpio_irqs[slot].icu_slot >= 0)
        {
          if (g_gpio_irqs[slot].path == RZV_GPIO_IRQ_PATH_TINT)
            {
              rzv_icu_detach(g_gpio_irqs[slot].icu_slot);
            }
          else
            {
              up_disable_irq(g_gpio_irqs[slot].icu_slot);
              irq_detach(g_gpio_irqs[slot].icu_slot);
            }
        }

      if (g_gpio_irqs[slot].path == RZV_GPIO_IRQ_PATH_TINT)
        {
          /* Disable TIEN before freeing the channel so a late edge cannot
           * latch after the SEL routing is gone.
           */
          rzv_icu_tint_set_source(g_gpio_irqs[slot].tint_channel, 0U, false);
          rzv_icu_tint_clear_flag(g_gpio_irqs[slot].tint_channel);
          rzv_icu_tint_free(g_gpio_irqs[slot].tint_channel);
        }
      else
        {
          /* IRQ path: disable ISEL to release the pin's IRQ input. */
          flags = enter_critical_section();
          rzv_gpio_pwpr_enable();
          {
            volatile uint32_t *p_isel;
            uint32_t isel_shift;
            uint32_t isel_mask;

            if (pin < 4U)
              {
                p_isel = (volatile uint32_t *)(base +
                           RZV_GPIO_GP_ISEL_L_OFFSET(port));
              }
            else
              {
                p_isel = (volatile uint32_t *)(base +
                           RZV_GPIO_GP_ISEL_H_OFFSET(port));
              }

            isel_shift = (pin & 3U) * 8U;
            isel_mask  = 0x3U << isel_shift;
            rzv_gpio_regwrite_32(p_isel, ISEL_DISABLE, isel_shift, isel_mask);
          }

          rzv_gpio_pwpr_disable();
          leave_critical_section(flags);
        }

      g_gpio_irqs[slot].allocated    = false;
      g_gpio_irqs[slot].callback     = NULL;
      g_gpio_irqs[slot].arg          = NULL;
      g_gpio_irqs[slot].icu_slot     = -1;
      g_gpio_irqs[slot].irq_num      = 0;
      g_gpio_irqs[slot].tint_channel = 0;
      g_gpio_irqs[slot].trigger      = 0;
      g_gpio_irqs[slot].path         = RZV_GPIO_IRQ_PATH_NONE;

      return OK;
    }

  /* -------------------- ATTACH -------------------- */

  /* Find free slot */
  slot = -1;
  for (i = 0; i < MAX_GPIO_IRQS; i++)
    {
      if (!g_gpio_irqs[i].allocated)
        {
          slot = i;
          break;
        }
    }

  if (slot < 0)
    {
      return -ENOMEM;
    }

  /* Every path starts by putting the pin into GPIO input mode. */
  ret = rzv_gpioconfigure_mode_input(port, pin);
  if (ret < 0)
    {
      return ret;
    }

  if (!use_tint)
    {
      /* --------------- IRQ0-15 direct-line path --------------- */

      uint8_t irq_mode;

      /* Enable ISEL — GP-group 4-pins-per-reg, 8-bits-per-pin layout. */
      flags = enter_critical_section();
      rzv_gpio_pwpr_enable();
      {
        volatile uint32_t *p_isel;
        uint32_t isel_shift;
        uint32_t isel_mask;

        if (pin < 4U)
          {
            p_isel = (volatile uint32_t *)(base +
                       RZV_GPIO_GP_ISEL_L_OFFSET(port));
          }
        else
          {
            p_isel = (volatile uint32_t *)(base +
                       RZV_GPIO_GP_ISEL_H_OFFSET(port));
          }

        isel_shift = (pin & 3U) * 8U;
        isel_mask  = 0x3U << isel_shift;
        rzv_gpio_regwrite_32(p_isel, ISEL_IRQ_MODE, isel_shift, isel_mask);
      }

      rzv_gpio_pwpr_disable();
      leave_critical_section(flags);

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
          irq_mode = RZV_ICU_IRQ_EDGE_BOTH;
        }

      /* Program IITSR (edge/level trigger) for this IRQ line. */
      ret = rzv_icu_filter_config(irq_num, irq_mode, false,
                                  RZV_ICU_FILTER_PCLK_DIV_1);
      if (ret < 0)
        {
          return ret;
        }

      /* External IRQ0-15 are FIXED GIC INTIDs on RZ/V2H (per FSP
       * bsp_irq_id.h GPIO_IRQ<n>_IRQn = n+1, INTID = RZV_IRQ_FIRST(32)+n+1).
       * They are NOT selectable via INTR8SEL — using rzv_icu_attach() would
       * write the line number into a SEL slot's TSSEL field, which selects
       * TINT<n> (an unrelated, disabled source) and silently drops the
       * interrupt.  Attach directly on the fixed INTID instead.
       */
      icu_irq = RZV_IRQ_EXT_IRQ(irq_num);

      ret = irq_attach(icu_irq, rzv_gpio_irq_handler_shim, &g_gpio_irqs[slot]);
      if (ret < 0)
        {
          return ret;
        }

      /* GIC edge/level sensitivity: LEVEL_LOW is the only level mode this
       * IRQ path supports (mirrors IITSR encoding).
       */
      rzv_gic_set_irq_type(icu_irq, (irq_mode != RZV_ICU_IRQ_LEVEL_LOW));

      up_enable_irq(icu_irq);

      g_gpio_irqs[slot].irq_num      = (uint8_t)irq_num;
      g_gpio_irqs[slot].tint_channel = 0;
      g_gpio_irqs[slot].trigger      = irq_mode;
      g_gpio_irqs[slot].path         = RZV_GPIO_IRQ_PATH_IRQ;
    }
  else
    {
      /* --------------- TINT channel path --------------- */

      int     channel;
      uint8_t gpioint;
      uint8_t trig;
      bool    edge;

      if (rising && falling)
        {
          /* TINT hardware has no native both-edge trigger (FSP
           * r_intc_tint.h intc_tint_trigger_t defines only RISING /
           * FALLING / LEVEL_HIGH / LEVEL_LOW).  Emit a diagnostic so the
           * -EINVAL isn't silent — callers that need press+release on a
           * TINT-only pin must either use the dedicated IRQ0-15 path
           * (which does support both-edge via IITSR=BOTH) or emulate by
           * flipping TITSR between RISING and FALLING inside their ISR.
           */
          gpioerr("ERROR: TINT both-edge unsupported (port=%u pin=%u)\n",
                  port, pin);
          return -EINVAL;
        }

      if (rising)
        {
          trig = ICU_TITSR_RISING;
          edge = true;
        }
      else if (falling)
        {
          trig = ICU_TITSR_FALLING;
          edge = true;
        }
      else
        {
          /* Neither edge requested: default to high-level.  Callers wanting
           * low-level can pass rising=false, falling=false, event=true; the
           * `event` argument is otherwise unused here and doubles as a
           * "prefer LEVEL_LOW over LEVEL_HIGH" hint.
           */
          trig = event ? ICU_TITSR_LEVEL_LOW : ICU_TITSR_LEVEL_HIGH;
          edge = false;
        }

      channel = rzv_icu_tint_alloc();
      if (channel < 0)
        {
          return channel;
        }

      ret = rzv_icu_tint_set_trigger(channel, trig);
      if (ret < 0)
        {
          rzv_icu_tint_free(channel);
          return ret;
        }

      gpioint = rzv_gpio_pin_to_gpioint(port, pin);

      /* The pin→GPIOINT source formula is a cumulative-sum by bonded pin
       * count (P0=[0..7], P1=[8..13], P2=[14..15], P3-PA=8 each, PB=[80..85]).
       * Independently verified against exactly one FSP data point (P5_0 →
       * gpioint 32, hal_data.c:496).  Log the mapping so first-time HW users
       * can cross-check with a scope on the expected pin.
       */
      gpioinfo("TINT attach: port=%u pin=%u -> gpioint=%u channel=%d trig=%u\n",
               port, pin, (unsigned)gpioint, channel, (unsigned)trig);

      ret = rzv_icu_tint_set_source(channel, gpioint, true);
      if (ret < 0)
        {
          rzv_icu_tint_free(channel);
          return ret;
        }

      /* Clear a stale TINT status flag BEFORE routing to the GIC.
       * Programming TITSR + TSSR(TIEN=1) can latch an edge event in TSCTR
       * from the trigger-mode transition or a pin transient; enabling the
       * GIC immediately after would dispatch that stale flag as a spurious
       * first interrupt.  FSP r_intc_tint.c:138-148 clears here for the
       * same reason ("Precaution when Changing Interrupt Settings" per UM).
       * Level triggers track the live pin — no clear needed.
       */
      if (edge)
        {
          rzv_icu_tint_clear_flag(channel);
        }

      /* Route TINT channel N via INTR8SEL as event N (per FSP
       * GPIO_TINT<n>_IRQSELn = n in bsp_irq_id.h).
       */
      icu_irq = rzv_icu_attach(channel, rzv_gpio_irq_handler_shim,
                               &g_gpio_irqs[slot], true);
      if (icu_irq < 0)
        {
          rzv_icu_tint_set_source(channel, 0U, false);
          rzv_icu_tint_free(channel);
          return icu_irq;
        }

      /* GIC line sensitivity: edge for RISING/FALLING, level otherwise. */
      rzv_gic_set_irq_type(icu_irq, edge);

      g_gpio_irqs[slot].irq_num      = 0;
      g_gpio_irqs[slot].tint_channel = (uint8_t)channel;
      g_gpio_irqs[slot].trigger      = trig;
      g_gpio_irqs[slot].path         = RZV_GPIO_IRQ_PATH_TINT;
    }

  g_gpio_irqs[slot].pinset    = pinset;
  g_gpio_irqs[slot].callback  = func;
  g_gpio_irqs[slot].arg       = arg;
  g_gpio_irqs[slot].icu_slot  = icu_irq;
  g_gpio_irqs[slot].allocated = true;

  (void)event;  /* falls through to TINT LEVEL_LOW hint above */
  return OK;

#else  /* !CONFIG_RZV_GPIO_IRQ */
  (void)pinset; (void)rising; (void)falling; (void)event;
  (void)func;   (void)arg;
  return -ENOSYS;
#endif
}

#ifdef CONFIG_RZV_GPIO_IRQ

/****************************************************************************
 * Name: rzv_gpio_irq_initialize
 *
 * Description:
 *   Initialize the GPIO interrupt slot table. Sets icu_slot to -1 sentinel
 *   in all entries so that slot 0 is never mistaken for "valid".
 *
 * BSS zero-init leaves icu_slot=0, which
 *   equals a valid NuttX IRQ, causing false "slot attached" detection.
 *   Must be called from rzv2h_bringup.c under CONFIG_RZV_GPIO_IRQ=y.
 *
 ****************************************************************************/

void rzv_gpio_irq_initialize(void)
{
  int i;

  for (i = 0; i < MAX_GPIO_IRQS; i++)
    {
      g_gpio_irqs[i].pinset       = 0;
      g_gpio_irqs[i].callback     = NULL;
      g_gpio_irqs[i].arg          = NULL;
      g_gpio_irqs[i].icu_slot     = -1;  /* -1 = unallocated sentinel */
      g_gpio_irqs[i].irq_num      = 0;
      g_gpio_irqs[i].tint_channel = 0;
      g_gpio_irqs[i].trigger      = 0;
      g_gpio_irqs[i].path         = RZV_GPIO_IRQ_PATH_NONE;
      g_gpio_irqs[i].allocated    = false;
    }
}

/****************************************************************************
 * Name: rzv_gpio_irq_enable / rzv_gpio_irq_disable
 *
 ****************************************************************************/

void rzv_gpio_irq_enable(int irq)
{
  int i;

  /* `irq` from caller is GIC INTID (returned by
   * rzv_icu_attach and stored in icu_slot).  `irq_num` is the ELC IRQ
   * line 0-15 — a completely different namespace.  Match on icu_slot.
   */

  for (i = 0; i < MAX_GPIO_IRQS; i++)
    {
      if (g_gpio_irqs[i].allocated && g_gpio_irqs[i].icu_slot == irq)
        {
          up_enable_irq(irq);
          return;
        }
    }
}

void rzv_gpio_irq_disable(int irq)
{
  int i;

  /* match on icu_slot (GIC INTID), not irq_num (ELC line) */

  for (i = 0; i < MAX_GPIO_IRQS; i++)
    {
      if (g_gpio_irqs[i].allocated && g_gpio_irqs[i].icu_slot == irq)
        {
          up_disable_irq(irq);
          return;
        }
    }
}

#endif /* CONFIG_RZV_GPIO_IRQ */

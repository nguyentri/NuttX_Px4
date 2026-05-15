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
#include "hardware/rzv_pinmap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPIO Pinmap Encoding — Phase-03 canonical ABI (rzv_gpio.h GPIO_PORT/PIN_SHIFT).
 *
 * Port: bits [31:28] — relative port 0-11 (matches PORT0..PORT11 << 28)
 * Pin:  bits [27:24] — pin 0-15 within port (matches PIN0..PIN15 << 24)
 *
 * Phase-03 [Critical-2]: unified encoding; rzv_gpio.c and rzv_gpio.h now
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
 * TODO(phase-03): True HW port count for R9A09G057H unconfirmed. Ports 12+
 * (P2C..) not verified. Needs RZ/V2H UM datasheet check.
 */
#define RZV_GPIO_MAX_PORT      12U

/* Per-port maximum pin count (HIGH-8 / H-9 fix).
 * GP ports P20-P2B (NuttX ports 0-11) have varying pin counts.
 * Source: FSP iodefine bitfields for each port.
 * P20=8, P21=6, P22=2 confirmed from FSP; remainder set to 8 (safe upper
 * bound — HW ignores writes to non-existent pins but better to reject them).
 * UNVERIFIED for ports 3-11 beyond confirmed FSP data: mark as 8 until UM
 * Table 53.x is checked.
 */
static const uint8_t g_rzv_port_pin_count[RZV_GPIO_MAX_PORT] =
{
  8U,  /* PORT0  = P20: 8 pins */
  6U,  /* PORT1  = P21: 6 pins */
  2U,  /* PORT2  = P22: 2 pins */
  8U,  /* PORT3  = P23: unverified, assume 8 */
  8U,  /* PORT4  = P24: unverified, assume 8 */
  8U,  /* PORT5  = P25: unverified, assume 8 */
  8U,  /* PORT6  = P26: unverified, assume 8 */
  8U,  /* PORT7  = P27: unverified, assume 8 */
  8U,  /* PORT8  = P28: unverified, assume 8 */
  8U,  /* PORT9  = P29: unverified, assume 8 */
  8U,  /* PORT10 = P2A: unverified, assume 8 */
  8U,  /* PORT11 = P2B: unverified, assume 8 */
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* PWPR protection counter for re-entrant critical section tracking */
static volatile uint32_t g_pwpr_protect_counter;

/* GPIO interrupt slot table */
#ifdef CONFIG_RZV_GPIO_IRQ
struct rzv_gpio_irq_s
{
  gpio_pinset_t pinset;       /* GPIO pin configuration */
  xcpt_t        callback;     /* User interrupt callback */
  void         *arg;          /* Callback argument */
  int           icu_slot;     /* NuttX IRQ from rzv_icu_attach() (-1=unused) */
  uint8_t       irq_num;      /* External IRQ line number 0-15 */
  bool          allocated;    /* Slot in use */
};

/* All icu_slot fields initialised to -1 by rzv_gpio_irq_initialize(). */
static struct rzv_gpio_irq_s g_gpio_irqs[MAX_GPIO_IRQS];
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
 *   Phase-03 [Critical-2]: use GPIO_PORT_SHIFT=28, GPIO_PIN_SHIFT=24.
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
 *   HIGH-8 / H-9 fix: validate pin against per-port pin count.
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

  /* HIGH-7: PMC is 8-bit; pin >= 8 would truncate mask to 0 */
  /* HIGH-6: PM is 16-bit; pin*2 >= 16 would overflow the 16-bit shift */

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
 *   Read-modify-write helpers matching FSP r_ioport_regwrite_{8,16,32}.
 *   Source: FSP r_ioport.c lines 135-175.
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
 *   Phase-03 fix [High-5, audit §2/§8]:
 *   RZV2H PWPR is 32-bit and uses REGWE_A (bit 6) semantics, NOT RA-style
 *   BOWI/PFSWE (bit 7/6 two-phase sequence). The old code wrote 8-bit values
 *   0x00/0x40 (enable) and 0x00/0x80 (disable) which:
 *     - Used 8-bit bus access (may be dropped on AXI)
 *     - Wrote bit 7 (undefined on RZV2H) during disable
 *     - Cleared REGWE_B accidentally during enable via 0x00 write
 *
 *   Correct sequence (from FSP bsp_io.h R_BSP_PinAccessEnable, rzv2h path):
 *     enable:  PWPR = (PWPR & REGWE_A_MASK) | REGWE_A_BIT   // RMW, set bit6
 *     disable: PWPR = (PWPR & REGWE_A_MASK)                 // RMW, clear bit6
 *
 *   Source: FSP bsp_feature.h (rzv2h/cr):
 *     BSP_FEATURE_IOPORT_PFC_PWPR_REGWE_A_OFFSET = 6
 *     BSP_FEATURE_IOPORT_PFC_PWPR_REGWE_A_MASK   = 0xFFFFFFBF
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
       * reserved bits. Phase-03 [High-5].
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
       * Phase-03 [High-5]: old code wrote 0x80 to bits[7] — undefined on RZV2H.
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
 *   Phase-03 fix [High-7, audit §2]:
 *   Old code: skipped ports 0-4 (returned early), used formula
 *     0x1C10 + (port-5)*8 for ports 5-11 — wrong for port 5 offset and
 *     wrong uniform-stride assumption (missing gap at PUPDD in SP group).
 *
 *   Correct: NuttX ports 0-11 map to FSP GP group (ports 0x20-0x2B).
 *   All have PUPD registers starting at PUPD20_L (0x1CE8). Formula:
 *     offset = PUPD20_L_OFFSET + port*8 + (pin >= 8 ? 4 : 0)
 *   Bit position within register: (pin % 8) * 2
 *
 *   Source: FSP r_ioport.c line 1450:
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

  /* HIGH-8: validate pin against per-port pin count (max 7 for GP ports) */

  if (base == 0 || !rzv_gpio_pin_valid(port, pin))
    {
      return -EINVAL;
    }

  /* CRIT-2 fix: FSP layout is 4 pins per 32-bit register, 8 bits per pin.
   * _L holds pins 0-3, _H holds pins 4-7.  Shift = (pin % 4) * 8.
   * Old code: split at pin<8 with shift=pin*2 — wrong register AND wrong shift.
   * Source: hardware/rzv_gpio.h GPIO_PUPD20_L_IOLH_SHIFT(n) = n*8.
   * Source: FSP r_ioport.c line ~1450: bitpos_align = (pin & 3) * 8.
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
 *   Phase-03 fix [High-6, audit §2]:
 *   Old code:
 *     port 0-2: iolh_offset = 0x0FFC + (port+3)*8  → SP-group base (wrong)
 *     port 3-11: iolh_offset = 0x1014 + (port-3)*8 → skips gap at IOLHD
 *   Both paths are wrong for NuttX ports 0-11 which are FSP GP group.
 *
 *   Correct: GP ports use IOLH20_L (0x10E4) as base.
 *     offset = IOLH20_L_OFFSET + port*8 + (pin >= 8 ? 4 : 0)
 *
 *   Source: FSP r_ioport.c line 1442:
 *     adr_offset_iolh = port*2 + pin/4  (p_iolh base = &R_GPIO->IOLH20_L)
 *   Source: hardware/rzv_gpio.h RZV_GPIO_GP_IOLH_L/H_OFFSET macros.
 *   Source: bsp_feature.h BSP_FEATURE_IOPORT_GP_REG_BASE_NUM = 20.
 *
 ****************************************************************************/

static int rzv_gpioconfigure_drive(unsigned int port, unsigned int pin,
                                   uint32_t drive)
{
  uintptr_t         base = rzv_gpio_get_port_base(port);
  volatile uint32_t *p_iolh;
  uint32_t           shift;
  uint32_t           mask;

  /* HIGH-8: validate pin; IOLH is 2-bit field per pin, 4 pins per reg */

  if (base == 0 || drive > 3U || !rzv_gpio_pin_valid(port, pin))
    {
      return -EINVAL;
    }

  /* CRIT-2 fix: _L = pins 0-3, _H = pins 4-7, shift = (pin%4)*8.
   * Source: FSP r_ioport.c bitpos_align = (pin & 3) * 8.
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
 *   Phase-03 fix [Medium-13, audit §3]:
 *   FSP r_ioport_peri_mode_pin_config programs PFC, IOLH, PUPD, SR, NOD, IEN.
 *   This implementation adds NOD (open-drain) for I2C compatibility.
 *   SR and IEN are deferred (no pinset encoding yet, safe to leave at reset).
 *   TODO(phase-03): Encode SR/IEN in pinset GPIO_FUNC bits and apply here.
 *   Source: FSP r_ioport.c r_ioport_peri_mode_pin_config (lines 1375-1458).
 *
 *   Caller (rzv_gpioconfig) has already written PMC=0 before calling here.
 *   We write PMC=1 inside to complete the PFC programming window.
 *
 *   Phase-03 [Medium-14]: PFC is programmed before PM per FSP order.
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

  /* HIGH-8: validate pin; HIGH-7: PMC is 8-bit, pin>=8 truncates mask */

  if (base == 0 || !rzv_gpio_pin_valid(port, pin))
    {
      return -EINVAL;
    }

  /* PMC=1: enable peripheral mode for this pin */
  p_pmc = (volatile uint8_t *)(base + RZV_GPIO_PMC_OFFSET(port));
  rzv_gpio_regwrite_8(p_pmc, PMC_PERIPH_MODE, (uint8_t)pin,
                      (uint8_t)(1U << pin));

  /* PFC: set peripheral function select (4 bits per pin).
   * Source: FSP r_ioport.c line 1435: 4-bit field at pin*4 in 32-bit reg.
   * Source: bsp_feature.h BSP_FEATURE_IOPORT_PFC_REG_BITFIELD = 0xF (4-bit).
   */
  p_pfc = (volatile uint32_t *)(base + RZV_GPIO_PFC_OFFSET(port));
  shift = pin * GPIO_PIN_ALIGN_4BIT;
  mask  = 0xFU << shift;
  rzv_gpio_regwrite_32(p_pfc, psel & 0xFU, shift, mask);

  /* NOD: N-channel open-drain mode for I2C/SMBus pins.
   * CRIT-2 fix: same 4-pins-per-reg, 8-bits-per-pin layout as IOLH/PUPD.
   * _L = pins 0-3, _H = pins 4-7, shift = (pin % 4) * 8.
   * Source: FSP r_ioport.c NOD register; hardware/rzv_gpio.h NOD macros.
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
  /* NOD value: 01=open-drain, 00=push-pull (2-bit field per FSP encoding) */
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

  /* HIGH-6/7: validate pin; PM is 16-bit (max shift 14 for pin 7) */

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

  if (gpio_irq != NULL && gpio_irq->callback != NULL)
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
 *   Phase-03 fixes applied:
 *   [Critical-4]: GPIO module clock gate before first register access.
 *   [High-5]:     32-bit RMW PWPR (REGWE_A semantics).
 *   [High-6]:     IOLH via GP-group lookup (not hand-rolled formula).
 *   [High-7]:     PUPD via GP-group lookup.
 *   [High-11]:    Full PMC/PFC/PM/IOLH/PUPD RMW under critical section.
 *   [Medium-13]:  NOD (open-drain) written in peripheral mode.
 *   [Medium-14]:  FSP-correct order: PMC(0) → PFC → IOLH → PUPD → P → PM.
 *   [Low-17]:     P register written BEFORE PM=OUTPUT to avoid glitch.
 *
 *   Source: FSP r_ioport.c + bsp_io.h; referenced inline below.
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

  /* Decode pinset using Phase-03 canonical ABI */
  port  = rzv_gpio_extract_port(cfgset);
  pin   = rzv_gpio_extract_pin(cfgset);
  mode  = cfgset & GPIO_MODE_MASK;
  psel  = cfgset & GPIO_PSEL_MASK;            /* bits [3:0] only */
  pull  = cfgset & GPIO_PULL_MASK;
  drive = (cfgset & GPIO_DRVSTR_MASK) >> GPIO_DRVSTR_SHIFT;
  func  = cfgset & GPIO_FUNC_MASK;

  base = rzv_gpio_get_port_base(port);

  /* HIGH-8: validate pin against per-port count; HIGH-6/7: pin>=8 UB */

  if (base == 0 || !rzv_gpio_pin_valid(port, pin))
    {
      return -EINVAL;
    }

  /* Phase-03 [Critical-4]: Enable GPIO module clock before any register
   * access. Equivalent to FSP R_BSP_MODULE_CLKON(IOPORT, ...).
   * NOTE: RZV_CPG_CLK_GPIO bit index is UNVERIFIED for R9A09G057H.
   * Phase-01 report confirmed mapping is a placeholder — value (domain=0,
   * bit=0) is NOT confirmed against RZ/V2H Hardware User Manual Table 9.x.
   * UNVERIFIED — needs RZ/V2H UM for R9A09G057H GPIO CLKON bit.
   * The call is idempotent if clock already running (TF-A may have enabled).
   * Source: FSP bsp_clocks.h R_BSP_MODULE_CLKON.
   */
  rzv_clock_enable(RZV_CPG_CLK_GPIO);

  /* Phase-03 [High-11]: Critical section wraps the ENTIRE PMC/PFC/IOLH/PUPD/
   * PM RMW sequence to prevent concurrent config on the same port byte.
   * Source: FSP R_BSP_PinAccessEnable wraps the full pin config call.
   */
  flags = enter_critical_section();
  rzv_gpio_pwpr_enable();  /* Phase-03 [High-5]: 32-bit RMW PWPR */

  /* Phase-03 [Medium-14] FSP sequence step 1: PMC=0 (force GPIO mode).
   * This must precede PFC programming per FSP convention.
   * Source: FSP r_ioport.c r_ioport_peri_mode_pin_config line ~1430.
   */
  p_pmc = (volatile uint8_t *)(base + RZV_GPIO_PMC_OFFSET(port));
  rzv_gpio_regwrite_8(p_pmc, PMC_GPIO_MODE, (uint8_t)pin,
                      (uint8_t)(1U << pin));

  /* Step 2: PFC + PMC=1 (only if peripheral mode).
   * Phase-03 [Medium-14]: PFC written before PM per FSP order.
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
   * Phase-03 [High-6]: GP-group lookup, not SP-group formula.
   */
  ret = rzv_gpioconfigure_drive(port, pin, drive);
  if (ret < 0)
    {
      goto out;
    }

  /* Step 4: Pull configuration (PUPD).
   * Phase-03 [High-7]: GP-group lookup, covers all ports 0-11.
   */
  ret = rzv_gpioconfigure_pull(port, pin, pull);
  if (ret < 0)
    {
      goto out;
    }

  /* Step 5: Set output latch (P register) BEFORE enabling output in PM.
   * Phase-03 [Low-17]: avoids glitch on active-high-idle pins (e.g. SPI CS).
   * Source: FSP bsp_io.h BSP_IO_PinWrite sets P then PM simultaneously.
   */
  if (mode == RZV_GPIO_OUTPUT)
    {
      bool initial_high = (cfgset & GPIO_OUTPUT_SET) != 0;
      p_p = (volatile uint8_t *)(base + RZV_GPIO_P_OFFSET(port));
      rzv_gpio_regwrite_8(p_p, initial_high ? 1U : 0U, (uint8_t)pin,
                          (uint8_t)(1U << pin));
    }

  /* Step 6: Configure PM register (port direction) — written last per FSP.
   * For peripheral mode: PM=Hi-Z (pin driven by peripheral via PFC).
   * Source: FSP r_ioport.c: PM set after PFC/PMC/IOLH/PUPD.
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
 *   Phase-03 [Low-16]: returns int (OK/-EINVAL) instead of void so that
 *   callers can detect invalid port. Source: audit §6 Low-16.
 *   Source: FSP bsp_io.h R_BSP_PinWrite.
 *
 ****************************************************************************/

int rzv_gpiowrite(gpio_pinset_t pinset, bool value)
{
  unsigned int      port;
  unsigned int      pin;
  uintptr_t         base;
  volatile uint8_t *p_p;

  port = rzv_gpio_extract_port(pinset);
  pin  = rzv_gpio_extract_pin(pinset);

  base = rzv_gpio_get_port_base(port);
  if (base == 0)
    {
      return -EINVAL;
    }

  p_p = (volatile uint8_t *)(base + RZV_GPIO_P_OFFSET(port));
  rzv_gpio_regwrite_8(p_p, value ? 1U : 0U, (uint8_t)pin,
                      (uint8_t)(1U << pin));
  return OK;
}

/****************************************************************************
 * Name: rzv_gpioread
 *
 * Description:
 *   Read the value of a GPIO pin via PIN register.
 *   Returns false on invalid port (caller cannot distinguish from low — LOW).
 *   Source: FSP bsp_io.h R_BSP_PinRead.
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
 *   Attach or detach a GPIO interrupt callback via IRQ0-15 direct lines.
 *
 *   Phase-03 fixes:
 *   [Critical-1, audit §4]: Fixed undeclared `cfg` at original line 909.
 *     The find-slot call used `cfg` (undefined); correct variable is `pinset`.
 *   [High-8]:  ISEL offset via GP-group lookup (hardware/rzv_gpio.h macro),
 *     not unsourced magic 0x2CE8+port*8 (which was coincidentally correct
 *     but had no traceability to FSP/UM). Source: RZV_GPIO_GP_ISEL_L/H_OFFSET.
 *   [High-9]:  Only IRQ0-15 direct lines supported. TINT routing via TSSR0-7
 *     requires FSP bsp_group_irq.c-style programming and is deferred.
 *     TODO(phase-03): Add TINT if PX4 RC-IN or sensor IRQs require it.
 *   [High-10]: IRQ number extracted from pinset bits [7:4] (GPIO_FUNC field).
 *     This is a defined workaround — bits [3:0] are PSEL, not IRQ number.
 *     TODO(phase-03): Add GPIO_IRQ_SHIFT/GPIO_IRQ_MASK field to rzv_gpio.h
 *     and update call-sites to pass explicit IRQ line number.
 *
 ****************************************************************************/

int rzv_gpiosetevent(gpio_pinset_t pinset, bool rising, bool falling,
                     bool event, xcpt_t func, void *arg)
{
#ifdef CONFIG_RZV_GPIO_IRQ
  unsigned int port;
  unsigned int pin;
  uintptr_t    base;
  int          irq_num;
  int          slot;
  int          icu_irq;
  uint8_t      irq_mode;
  irqstate_t   flags;
  int          ret;
  int          i;

  port = rzv_gpio_extract_port(pinset);
  pin  = rzv_gpio_extract_pin(pinset);

  base = rzv_gpio_get_port_base(port);

  /* HIGH-8: validate pin against per-port count; HIGH-6/7: pin>=8 UB */

  if (base == 0 || !rzv_gpio_pin_valid(port, pin))
    {
      return -EINVAL;
    }

  /* Phase-03 [High-10]: IRQ line number from GPIO_FUNC field bits [7:4].
   * This is the defined workaround for this phase.
   * Callers encode IRQ0-15 as: pinset |= (irq_num << GPIO_FUNC_SHIFT)
   * TODO(phase-03): Replace with dedicated GPIO_IRQ_SHIFT field.
   */
  irq_num = (int)((pinset >> GPIO_FUNC_SHIFT) & 0x0FU);
  if (irq_num < 0 || irq_num >= MAX_GPIO_IRQS)
    {
      return -EINVAL;
    }

  if (func == NULL)
    {
      /* Detach: find existing slot by pinset.
       * Phase-03 [Critical-1]: original code used undeclared `cfg` here.
       * Correct variable is `pinset`. Source: audit §4 Critical-1.
       */
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

      /* Disable GIC/ICU */
      if (g_gpio_irqs[slot].icu_slot >= 0)
        {
          rzv_icu_detach(g_gpio_irqs[slot].icu_slot);
        }

      /* Disable ISEL — CRIT-2 fix: 4-pins-per-reg, 8-bits-per-pin layout.
       * _L = pins 0-3, _H = pins 4-7, shift = (pin % 4) * 8.
       */
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

      g_gpio_irqs[slot].allocated = false;
      g_gpio_irqs[slot].callback  = NULL;
      g_gpio_irqs[slot].arg       = NULL;
      g_gpio_irqs[slot].icu_slot  = -1;
      g_gpio_irqs[slot].irq_num   = 0;

      return OK;
    }

  /* Attach: find free slot */
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

  /* Set pin to GPIO input for interrupt reception */
  ret = rzv_gpioconfigure_mode_input(port, pin);
  if (ret < 0)
    {
      return ret;
    }

  /* Enable ISEL — CRIT-2 fix: 4-pins-per-reg, 8-bits-per-pin layout.
   * _L = pins 0-3, _H = pins 4-7, shift = (pin % 4) * 8.
   * Source: FSP r_ioport.c bitpos_align = (pin & 3) * 8.
   */
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

  /* Determine edge trigger mode */
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

  /* Configure ICU edge detection for this IRQ line */
  ret = rzv_icu_filter_config(irq_num, irq_mode, false,
                              RZV_ICU_FILTER_PCLK_DIV_1);
  if (ret < 0)
    {
      return ret;
    }

  /* Attach handler via ICU dynamic slot allocation.
   * rzv_icu_attach() returns GIC INTID (NuttX IRQ number).
   */
  icu_irq = rzv_icu_attach(irq_num, rzv_gpio_irq_handler_shim,
                           &g_gpio_irqs[slot], true);
  if (icu_irq < 0)
    {
      return icu_irq;
    }

  /* MED-9 fix: configure GIC ICDICFR to match ICU edge/level setting.
   * Edge sources require GIC edge-sensitive mode; level sources need
   * level-sensitive mode.  rzv_gic_set_irq_type operates on GIC INTID
   * which is exactly what rzv_icu_attach() returned.
   */
  rzv_gic_set_irq_type(icu_irq, (irq_mode != RZV_ICU_IRQ_LEVEL_LOW));

  g_gpio_irqs[slot].pinset    = pinset;
  g_gpio_irqs[slot].callback  = func;
  g_gpio_irqs[slot].arg       = arg;
  g_gpio_irqs[slot].icu_slot  = icu_irq;
  g_gpio_irqs[slot].irq_num   = (uint8_t)irq_num;
  g_gpio_irqs[slot].allocated = true;

  (void)event;  /* compatibility parameter — unused */
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
 *   Phase-03 [High-12, audit §4]: BSS zero-init leaves icu_slot=0, which
 *   equals a valid NuttX IRQ, causing false "slot attached" detection.
 *   Must be called from rzv2h_bringup.c under CONFIG_RZV_GPIO_IRQ=y.
 *
 ****************************************************************************/

void rzv_gpio_irq_initialize(void)
{
  int i;

  for (i = 0; i < MAX_GPIO_IRQS; i++)
    {
      g_gpio_irqs[i].pinset    = 0;
      g_gpio_irqs[i].callback  = NULL;
      g_gpio_irqs[i].arg       = NULL;
      g_gpio_irqs[i].icu_slot  = -1;  /* -1 = unallocated sentinel */
      g_gpio_irqs[i].irq_num   = 0;
      g_gpio_irqs[i].allocated = false;
    }
}

/****************************************************************************
 * Name: rzv_gpio_irq_enable / rzv_gpio_irq_disable
 *
 ****************************************************************************/

void rzv_gpio_irq_enable(int irq)
{
  int i;

  /* MED-16 / M-12 fix: `irq` from caller is GIC INTID (returned by
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

  /* MED-16 fix: match on icu_slot (GIC INTID), not irq_num (ELC line) */

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

/****************************************************************************
 * arch/arm/src/rzv/rzv_icu.c
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
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>

#include <arch/board/board.h>
#include <arch/irq.h>

#include "arm_internal.h"
#include "hardware/rzv_intc_gic.h"
#include "hardware/rzv_intc.h"
#include "hardware/rzv_icu.h"
#include "rzv_icu.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Type Definitions
 ****************************************************************************/

typedef struct
{
  int el;           /* Event Link number */
  xcpt_t handler;   /* Handler function */
  void *arg;        /* Argument for handler */
} rzv_icu_handler_t;

/****************************************************************************
 * Private Data
 *
 * Global ICU handler structure - supports both configuration and runtime
 * registration
 ****************************************************************************/

static rzv_icu_handler_t g_icu_handlers[RZV_IRQ_ICU_SLOTS];
static uint32_t g_icu_slot = 0; /* next available slot */

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_icu_interrupt
 *
 * Description:
 *   Common ICU interrupt handler
 *
 ****************************************************************************/

static int rzv_icu_interrupt(int irq, void *context, void *arg)
{
  int icu_slot = (int)(uintptr_t)arg;

  /* Call the registered handler if available */

  if (g_icu_handlers[icu_slot].handler != NULL)
    {
      /* Clear the interrupt */

      rzv_icu_clear_irq(irq);
      return g_icu_handlers[icu_slot].handler(irq, context,
                                              g_icu_handlers[icu_slot].arg);
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_icu_clear_irq
 *
 * Description:
 *   Clear interrupt request status. For RZV2H, interrupt clearing is
 *   handled by the peripheral itself and the GIC. This function is
 *   provided for API compatibility but does not need to modify ICU
 *   registers.
 *
 ****************************************************************************/

void rzv_icu_clear_irq(int irq)
{
  if (irq >= RZV_ELC_IRQ0 && irq <= RZV_ELC_IRQ15) {
    rzv_icu_clear_irq_status(1 << (irq - RZV_ELC_IRQ0));
  }
}

/****************************************************************************
 * Name: rzv_icu_initialize
 *
 * Description:
 *   Initialize the ICU driver and register configuration-time interrupts
 *
 ****************************************************************************/

void rzv_icu_initialize(void)
{
  int i;

  /* Initialize the handlers structure */

  for (i = 0; i < RZV_IRQ_ICU_SLOTS; i++)
    {
      g_icu_handlers[i].el = -1;
      g_icu_handlers[i].handler = NULL;
      g_icu_handlers[i].arg = NULL;
    }

  /* Reset slot counter */

  g_icu_slot = 0;
}

/****************************************************************************
 * Name: rzv_icu_attach
 *
 * Description:
 *   Attach an ICU interrupt handler at runtime
 *   This function handles both event linking and IRQ enabling
 *   This must only be called after a hardware event has been configured
 *
 ****************************************************************************/

int rzv_icu_attach(int event, xcpt_t handler, void *arg, bool irq_enable)
{
  irqstate_t flags;
  int slot;

  /* Critical section to prevent race condition in slot allocation */

  flags = enter_critical_section();

  /* Find next available slot */

  if (g_icu_slot >= RZV_IRQ_ICU_SLOTS)
    {
      leave_critical_section(flags);
      return -ENOMEM;
    }

  slot = g_icu_slot++;

  leave_critical_section(flags);

  /* Set up the ICU event link */

  rzv_icu_set_event(slot, event);

  /* Store the handler information */

  g_icu_handlers[slot].el = event;
  g_icu_handlers[slot].handler = handler;
  g_icu_handlers[slot].arg = arg;

  /* Attach the common interrupt handler */

  irq_attach(RZV_IRQ_FIRST + slot, rzv_icu_interrupt,
             (void *)(uintptr_t)slot);

  /* Enable the interrupt */

  if (irq_enable)
    {
      up_enable_irq(RZV_IRQ_FIRST + slot);
    }

  return RZV_IRQ_FIRST + slot;
}

/****************************************************************************
 * Name: rzv_icu_detach
 *
 * Description:
 *   Detach an ICU interrupt handler (unified API)
 *   This function handles both IRQ disabling and slot deallocation
 *
 ****************************************************************************/

int rzv_icu_detach(int icu_irq)
{
  int slot;
  int i;

  /* Validate IRQ range */

  if (icu_irq < RZV_IRQ_FIRST ||
      icu_irq >= (RZV_IRQ_FIRST + RZV_IRQ_ICU_SLOTS))
    {
      return -EINVAL;
    }

  slot = icu_irq - RZV_IRQ_FIRST;

  /* Validate slot range */

  if (slot < 0 || slot >= RZV_IRQ_ICU_SLOTS)
    {
      return -EINVAL;
    }

  /* Check if slot is actually in use */

  if (g_icu_handlers[slot].handler == NULL)
    {
      return -ENOENT;
    }

  /* Disable the interrupt */

  up_disable_irq(icu_irq);

  /* Detach the interrupt handler */

  irq_detach(icu_irq);

  /* Clear the handler information */

  g_icu_handlers[slot].el = -1;
  g_icu_handlers[slot].handler = NULL;
  g_icu_handlers[slot].arg = NULL;

  /* Clear the ICU event link */

  rzv_icu_set_event(slot, 0);

  /* Compact the slot allocation if this was the last allocated slot */

  if (slot == (g_icu_slot - 1))
    {
      /* Find the highest used slot */

      int highest_used = -1;
      for (i = 0; i < g_icu_slot; i++)
        {
          if (g_icu_handlers[i].handler != NULL)
            {
              highest_used = i;
            }
        }

      /* Update g_icu_slot to the next available slot after highest used */

      g_icu_slot = highest_used + 1;
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_icu_set_event
 *
 * Description:
 *   Set ICU event link using INTR8SEL registers
 *   Routes an ELC event to a GIC interrupt line (SPI)
 *
 * Input Parameters:
 *   icu_slot - Slot number (0-95 for RZV2H, maps to GIC SPI 32-127)
 *   event    - ELC event number (RZV_ELC_* from rzv2h_irq.h)
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure.
 *
 ****************************************************************************/

int rzv_icu_set_event(int icu_slot, int event)
{
  uint32_t regaddr;
  uint32_t regval;
  int reg_num;
  int slot_idx;
  int shift;

  if (icu_slot < 0 || icu_slot >= RZV_IRQ_ICU_SLOTS)
    {
      return -EINVAL;
    }

  /* Calculate which INTR8SEL register and which slot within it
   * Each INTR8SEL register has 3 slots of 10 bits each
   */

  reg_num = RZV_INTC_INTR8SEL_REG(icu_slot);
  slot_idx = RZV_INTC_INTR8SEL_IDX(icu_slot);
  shift = RZV_INTC_INTR8SEL_SHIFT(slot_idx);

  regaddr = RZV_INTC_INTR8SEL(reg_num);
  regval = getreg32(regaddr);

  /* Clear the event field for this slot */

  regval &= ~(RZV_INTC_INTR8SEL_MASK << shift);

  /* Set the new event number */

  regval |= ((event & RZV_INTC_INTR8SEL_MASK) << shift);

  putreg32(regval, regaddr);

  return OK;
}

/****************************************************************************
 * Name: rzv_icu_filter_config
 *
 * Description:
 *   Configure ICU interrupt mode and filtering for external IRQ pins
 *   (TINT0-TINT31)
 *
 * Input Parameters:
 *   icu_irq      - TINT pin number (0-31)
 *   mode         - Interrupt detection mode (edge/level)
 *   filter_enable - Enable digital filter
 *   filter_clock - Filter clock selection
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure.
 *
 * Note:
 *   This function configures the TITSR (trigger type select) registers
 *   for TINT interrupt pins. For RZV2H, these are configured via the
 *   INTC TITSR registers.
 *
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_icu_set_irq_detect
 *
 * Description:
 *   Configure IRQ detection method (edge/level sensitivity)
 *
 * Input Parameters:
 *   irq_num  - IRQ number (0-15 for IRQ0-IRQ15)
 *   mode     - Detection mode (RZV_ICU_LEVEL_LOW, RZV_ICU_EDGE_FALLING,
 *              RZV_ICU_EDGE_RISING, RZV_ICU_EDGE_BOTH)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure
 *
 * Note:
 *   This configures the ICU module's IITSR register to set how IRQ pins
 *   trigger interrupts. This is independent of event routing done by INTC.
 *
 ****************************************************************************/

int rzv_icu_set_irq_detect(int irq_num, uint8_t mode)
{
  uint32_t regval;
  uint32_t shift;

  if (irq_num < 0 || irq_num > 15)
    {
      return -EINVAL;
    }

  if (mode > ICU_IITSR_BOTH)
    {
      return -EINVAL;
    }

  /* Read current IITSR value */

  regval = getreg32(RZV_ICU_IITSR);

  /* Clear the detection bits for this IRQ */

  shift = irq_num * 2;
  regval &= ~(0x3 << shift);

  /* Set new detection mode */

  regval |= (mode << shift);

  /* Write back to register */

  putreg32(regval, RZV_ICU_IITSR);

  return OK;
}

/****************************************************************************
 * Name: rzv_icu_clear_irq_status
 *
 * Description:
 *   Clear IRQ status flags
 *
 * Input Parameters:
 *   irq_mask - Bitmask of IRQ0-15 status flags to clear (bit N = IRQ N)
 *
 * Returned Value:
 *   None
 *
 * Note:
 *   This clears the ICU module's interrupt status flags. This should be
 *   called in interrupt handlers for IRQ0-15 external interrupts.
 *
 ****************************************************************************/

void rzv_icu_clear_irq_status(uint16_t irq_mask)
{
  /* Write 1 to clear status bits */

  putreg32(irq_mask & 0xFFFF, RZV_ICU_ISCLR);
}

/****************************************************************************
 * Name: rzv_icu_get_irq_status
 *
 * Description:
 *   Get IRQ status flags
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   16-bit status register value (bit N = IRQ N status)
 *
 * Note:
 *   Reads the ICU module's ISCTR register to check which IRQ pins have
 *   pending interrupts.
 *
 ****************************************************************************/

uint16_t rzv_icu_get_irq_status(void)
{
  return getreg32(RZV_ICU_ISCTR) & 0xFFFF;
}

/****************************************************************************
 * Name: rzv_icu_set_irq_filter
 *
 * Description:
 *   Configure IRQ digital filter
 *
 * Input Parameters:
 *   irq_num      - IRQ number (0-15)
 *   filter_clock - Filter clock divider (RZV_ICU_FCLK_DIV1, DIV8, DIV32, DIV64)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure
 *
 * Note:
 *   The digital filter can suppress noise on external IRQ pins.
 *
 ****************************************************************************/

int rzv_icu_set_irq_filter(int irq_num, uint8_t filter_clock)
{
  uint32_t regval;
  uint32_t shift;

  if (irq_num < 0 || irq_num > 15)
    {
      return -EINVAL;
    }

  if (filter_clock > ICU_FCLKSEL_PCLKL_DIV64)
    {
      return -EINVAL;
    }

  /* Read current IFLTC value */

  regval = getreg32(RZV_ICU_IFLTC);

  /* Clear the filter clock bits for this IRQ */

  shift = irq_num * 2;
  regval &= ~(0x3 << shift);

  /* Set new filter clock */

  regval |= (filter_clock << shift);

  /* Write back to register */

  putreg32(regval, RZV_ICU_IFLTC);

  return OK;
}

/****************************************************************************
 * Name: rzv_icu_set_priority
 *
 * Description:
 *   Set interrupt priority for a dynamically allocated ICU IRQ.
 *   This function wraps the architecture-specific up_prioritize_irq()
 *   to provide a consistent ICU-level API.
 *
 * Input Parameters:
 *   icu_irq  - ICU IRQ number (RZV_IRQ_FIRST + slot)
 *   priority - Priority level (0-31 for GIC, 0 = highest, 31 = lowest)
 *              GIC uses bits[7:3] for 5-bit priority control
 *              Typical values: 0-7 (high), 8-15 (medium), 16-31 (low)
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure.
 *
 * Notes:
 *   - Priority must be set before enabling the interrupt
 *   - Lower numerical values = higher priority
 *   - Priority 0 is reserved for critical system interrupts
 *   - GIC implements 5 bits of priority in bits[7:3]
 *
 ****************************************************************************/

int rzv_icu_set_priority(int icu_irq, int priority)
{
  /* Validate IRQ range */

  if (icu_irq < RZV_IRQ_FIRST ||
      icu_irq >= (RZV_IRQ_FIRST + RZV_IRQ_ICU_SLOTS))
    {
      return -EINVAL;
    }

  /* Validate priority range (0-31 for GIC 5-bit priority)
   * GIC uses bits[7:3] of the priority byte, so we have 32 levels
   * Priority 0x00 = highest, 0xF8 = lowest
   */

  if (priority < 0 || priority > 31)
    {
      return -EINVAL;
    }

#ifdef CONFIG_ARCH_IRQPRIO
  /* Use the architecture-specific priority function
   * up_prioritize_irq expects priority in the format used by GIC
   * For GIC, priority is in bits [7:3] of the priority byte,
   * so we need to shift left by 3
   */

  return up_prioritize_irq(icu_irq, priority << 3);
#else
  /* Priority control not enabled in configuration */

  return -ENOSYS;
#endif
}

/****************************************************************************
 * Name: rzv_icu_filter_config
 *
 * Description:
 *   Legacy function - use rzv_icu_set_irq_detect and rzv_icu_set_irq_filter
 *
 ****************************************************************************/

int rzv_icu_filter_config(int icu_irq, uint8_t mode, bool filter_enable,
                           uint8_t filter_clock)
{
  /* This legacy function wraps the new API for backward compatibility */

  int ret;

  if (icu_irq < 0 || icu_irq > 15)
    {
      return -EINVAL;
    }

  /* Set detection mode */

  ret = rzv_icu_set_irq_detect(icu_irq, mode);
  if (ret < 0)
    {
      return ret;
    }

  /* Set filter if requested */

  if (filter_enable)
    {
      ret = rzv_icu_set_irq_filter(icu_irq, filter_clock);
    }

  return ret;
}

/****************************************************************************
 * Name: rzv_icu_enable_wakeup
 *
 * Description:
 *   Enable wakeup for specific ICU interrupts
 *
 * Note:
 *   Wakeup functionality is device-specific and may require power
 *   management configuration. This is a placeholder for future
 *   implementation.
 *
 ****************************************************************************/

void rzv_icu_enable_wakeup(uint32_t mask)
{
  /* TODO: Implement wakeup enable if supported by RZV2H */
}

/****************************************************************************
 * Name: rzv_icu_disable_wakeup
 *
 * Description:
 *   Disable wakeup for specific ICU interrupts
 *
 * Note:
 *   Wakeup functionality is device-specific and may require power
 *   management configuration. This is a placeholder for future
 *   implementation.
 *
 ****************************************************************************/

void rzv_icu_disable_wakeup(uint32_t mask)
{
  /* TODO: Implement wakeup disable if supported by RZV2H */
}

/****************************************************************************
 * Name: rzv_icu_clear_nmi_status
 *
 * Description:
 *   Clear NMI status flags
 *
 * Note:
 *   NMI handling on RZV2H is done through the INTC NSCLR register.
 *   This is a placeholder for future implementation.
 *
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_icu_clear_nmi_status
 *
 * Description:
 *   Clear NMI status flag
 *
 * Returned Value:
 *   None
 *
 * Note:
 *   This clears the NMI interrupt status in the ICU module.
 *
 ****************************************************************************/

void rzv_icu_clear_nmi_status(uint16_t mask)
{
  /* Write 1 to clear NMI status bit */

  putreg32(1, RZV_ICU_NSCLR);
}

/****************************************************************************
 * Name: rzv_icu_get_nmi_status
 *
 * Description:
 *   Get NMI status flag
 *
 * Returned Value:
 *   True if NMI is pending, false otherwise
 *
 ****************************************************************************/

bool rzv_icu_get_nmi_status(void)
{
  return (getreg32(RZV_ICU_NSCNT) & ICU_NSCNT_NSTAT) != 0;
}

/****************************************************************************
 * Name: rzv_icu_set_nmi_filter
 *
 * Description:
 *   Configure NMI digital filter
 *
 * Input Parameters:
 *   filter_enable - Enable/disable filter
 *   filter_clock  - Filter clock divider
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure
 *
 ****************************************************************************/

int rzv_icu_set_nmi_filter(bool filter_enable, uint8_t filter_clock)
{
  uint32_t regval;

  if (filter_clock > ICU_FCLKSEL_PCLKL_DIV64)
    {
      return -EINVAL;
    }

  /* Configure filter clock */

  regval = getreg32(RZV_ICU_NMIFLTC);
  regval &= ~ICU_NMIFLTC_FCLKSEL_MASK;
  regval |= (filter_clock << ICU_NMIFLTC_FCLKSEL_SHIFT);
  putreg32(regval, RZV_ICU_NMIFLTC);

  /* Enable/disable filter */

  regval = getreg32(RZV_ICU_NMITR);
  if (filter_enable)
    {
      regval |= ICU_NMITR_NFLTEN;
    }
  else
    {
      regval &= ~ICU_NMITR_NFLTEN;
    }

  putreg32(regval, RZV_ICU_NMITR);

  return OK;
}

/****************************************************************************
 * Name: rzv_icu_enable_nmi
 *
 * Description:
 *   Enable NMI interrupts
 *
 * Note:
 *   NMI configuration on RZV2H is device-specific.
 *   This is a placeholder for future implementation.
 *
 ****************************************************************************/

void rzv_icu_enable_nmi(uint16_t mask)
{
  /* TODO: Implement NMI enable if needed */
}

/****************************************************************************
 * Name: rzv_icu_disable_nmi
 *
 * Description:
 *   Disable NMI interrupts
 *
 * Note:
 *   NMI configuration on RZV2H is device-specific.
 *   This is a placeholder for future implementation.
 *
 ****************************************************************************/

void rzv_icu_disable_nmi(uint16_t mask)
{
  /* TODO: Implement NMI disable if needed */
}

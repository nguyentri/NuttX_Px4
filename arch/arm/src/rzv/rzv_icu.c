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

/* SELECT interrupt (INTR8SEL) -> physical GIC INTID base.
 *
 * FSP computes this base as
 *   BSP_FEATURE_ICU_FIXED_INTSEL_COUNT (353, the count of FIXED SPI sources,
 *   i.e. SPI indices 0..352)
 *   + BSP_SELECT_INT_START_ELEMENT (0)
 *   + BSP_CORTEX_VECTOR_TABLE_ENTRIES (32, the SGI+PPI INTIDs 0..31)
 *   = 385   (bsp_irq.c: irq_num used as the physical INTID subscript).
 *
 * So INTR8SEL slot N is delivered on physical GIC INTID (385 + N).  353 is a
 * SPI-index count, NOT an INTID; adding the +32 SGI/PPI offset is required.
 * NuttX IRQ numbers ARE physical INTIDs (arm_decodeirq dispatches the raw
 * ICCIAR INTID with no translation, and the private timer attaches at raw
 * PPI INTID 29), so the handler must be installed / the GIC line enabled at
 * (385 + N).  Using 353 registered the handler on a line the hardware never
 * raises, leaving every INTR8SEL-routed peripheral IRQ unserviced.
 */

#define RZV_INTC_SEL_SPI_BASE   (385)

/****************************************************************************
 * Type Definitions
 ****************************************************************************/

typedef struct
{
  /* removed unused 'el' field — never consulted after set */
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
  /* Intentional no-op today.  Retained for API compatibility with existing
   * board glue that calls it after up_enable_irq(); safe because every current
   * NuttX IRQ source on this SoC (fixed SPI-B/RSCI/MHU, selectable INTR8SEL
   * SEL slots) is either edge-triggered or level-cleared by peripheral
   * deassert + GIC EOI — none of them need INTC ISCLR.
   *
   * F5 background — the sticky-flag path this function *would* implement if
   * an external-IRQ pin driver ever landed (FSP-verified from
   * refs/intc_irq_rzv2h_evk_cr8_0_ep, not from the RZ/V2H UM Table):
   *
   *   INTID map (fixed, from bsp_irq_id.h:62-77):
   *     external IRQ pin n (0..15) → FSP GPIO_IRQn_IRQn = n+1
   *                                → NuttX INTID = 33 + n  (i.e. +RZV_IRQ_FIRST)
   *   Sticky-flag register (from bsp_override.h:2547):
   *     INTC->ISCLR |= (1u << pin_channel)   -- indexed by pin, NOT INTID
   *   Call-site rules (from r_intc_irq.c:150, 321):
   *     - EDGE pins only (skip for LEVEL_LOW — HWM precaution)
   *     - Written at Open() after IITSR setup AND in the ISR *before* the
   *       user callback (so a re-arm mid-ISR is not lost)
   *
   * So a correct future implementation is not a one-liner in this generic
   * helper — it belongs in a dedicated external-IRQ pin driver, mirroring
   * r_intc_irq.c.  TINT32_00..31 does NOT use ISCLR (selectable via INTR8SEL,
   * covered by rzv_icu_attach).  See plans/rzv2h_interrupt_unification.md §F5.
   */

  (void)irq;
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
  int irq;

  /* Critical section: slot allocation only */

  flags = enter_critical_section();

  if (g_icu_slot >= RZV_IRQ_ICU_SLOTS)
    {
      leave_critical_section(flags);
      return -ENOMEM;
    }

  slot = g_icu_slot++;

  leave_critical_section(flags);

  /* INTR8SEL slot N is delivered on physical GIC INTID
   * (RZV_INTC_SEL_SPI_BASE + N) = 385 + N (see the base macro for the FSP
   * derivation).  NuttX IRQ numbers are physical GIC INTIDs, so this value
   * is what arm_decodeirq will dispatch and what irq_attach/up_enable_irq
   * must use.
   */

  irq = RZV_INTC_SEL_SPI_BASE + slot;

  /* Correct attach order to close handler-NULL race.
   * If the event line is already asserted (level pin held active), the GIC
   * may dispatch immediately between set_event and irq_attach → NULL deref.
   *
   * Safe order:
   *   1. Store handler ptr FIRST (before any routing that could fire)
   *   2. Register with NuttX irq_attach (installs GIC handler shim)
   *   3. Clear any stale GIC pending bit
   *   4. Program INTR8SEL slot → event (last — enables routing)
   *   5. Enable GIC line (only if irq_enable requested)
   */

  /* 1. Store handler before any HW routing can cause dispatch */

  g_icu_handlers[slot].handler = handler;
  g_icu_handlers[slot].arg = arg;

  /* 2. Register NuttX IRQ handler shim */

  irq_attach(irq, rzv_icu_interrupt, (void *)(uintptr_t)slot);

  /* 3. Clear any stale pending bit at GIC distributor */

  putreg32(1u << (irq % 32),
           RZV_INTC_GIC_GICD_ICDICPR(irq >> 5));

  /* 4. Program INTR8SEL (critical section inside rzv_icu_set_event).
   *    After this, a pending event will route to the GIC line. The handler
   *    is already installed so no NULL window exists.
   */

  rzv_icu_set_event(slot, event);

  /* 5. Enable GIC line if requested */

  if (irq_enable)
    {
      up_enable_irq(irq);
    }

  return irq;
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
  irqstate_t flags;
  int slot;
  int i;
  int highest_used;

  /* icu_irq is the physical GIC INTID (RZV_INTC_SEL_SPI_BASE + slot); the
   * base already includes the SGI/PPI offset, so it is not added again.
   */

  if (icu_irq < RZV_INTC_SEL_SPI_BASE ||
      icu_irq >= (RZV_INTC_SEL_SPI_BASE + RZV_IRQ_ICU_SLOTS))
    {
      return -EINVAL;
    }

  slot = icu_irq - RZV_INTC_SEL_SPI_BASE;

  if (slot < 0 || slot >= RZV_IRQ_ICU_SLOTS)
    {
      return -EINVAL;
    }

  if (g_icu_handlers[slot].handler == NULL)
    {
      return -ENOENT;
    }

  /* Disable and detach before clearing handler.  The GIC line is masked
   * FIRST so no interrupt can be dispatched into this slot once teardown
   * begins.
   */

  up_disable_irq(icu_irq);
  irq_detach(icu_irq);

  /* Clear the INTR8SEL routing slot.
   *
   * Writing event 0 here is NOT ambiguous with a live IRQ0 routing, even
   * though ELC event 0 == external IRQ0: slot occupancy is tracked solely by
   * g_icu_handlers[slot].handler (set below to NULL), never by reading back
   * INTR8SEL content, so a residual event-0 selection on a freed slot is
   * never mistaken for "in use".  And because the GIC line was masked above,
   * a residual event-0 route on this slot cannot deliver a spurious
   * interrupt.  A subsequent attach that reuses this slot fully reprograms
   * INTR8SEL via rzv_icu_set_event(), so nothing stale survives reuse.
   */

  rzv_icu_set_event(slot, 0);

  g_icu_handlers[slot].handler = NULL;
  g_icu_handlers[slot].arg = NULL;

  /* slot compaction under critical section.
   * Always re-scan all slots to find true highest-used; never regress
   * g_icu_slot while a higher-numbered slot is still live.
   */

  flags = enter_critical_section();

  highest_used = -1;
  for (i = 0; i < (int)RZV_IRQ_ICU_SLOTS; i++)
    {
      if (g_icu_handlers[i].handler != NULL)
        {
          highest_used = i;
        }
    }

  g_icu_slot = highest_used + 1;

  leave_critical_section(flags);

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
  irqstate_t flags;
  uint32_t regaddr;
  uint32_t regval;
  int reg_num;
  int slot_idx;
  int shift;

  if (icu_slot < 0 || icu_slot >= RZV_IRQ_ICU_SLOTS)
    {
      return -EINVAL;
    }

  if (event < 0 || event > RZV_INTC_INTR8SEL_MASK)
    {
      return -EINVAL;
    }

  /* Each INTR8SEL register holds 3 x 10-bit slot fields.
   * RMW must be under critical section — concurrent writes
   * to different slots sharing the same 32-bit register would clobber each.
   */

  reg_num = RZV_INTC_INTR8SEL_REG(icu_slot);
  slot_idx = RZV_INTC_INTR8SEL_IDX(icu_slot);
  shift = RZV_INTC_INTR8SEL_SHIFT(slot_idx);

  regaddr = RZV_INTC_INTR8SEL(reg_num);

  flags = enter_critical_section();

  regval = getreg32(regaddr);
  regval &= ~(RZV_INTC_INTR8SEL_MASK << shift);
  regval |= ((event & RZV_INTC_INTR8SEL_MASK) << shift);
  putreg32(regval, regaddr);

  leave_critical_section(flags);

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
  irqstate_t flags;
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

  /* IITSR holds a 2-bit detection field for each of IRQ0-15 in one 32-bit
   * register.  The read-modify-write must run under a critical section so a
   * concurrent set on a different IRQ line (or an ISR) cannot clobber this
   * update — same rationale as rzv_icu_set_event()'s INTR8SEL RMW.
   */

  shift = irq_num * 2;

  flags = enter_critical_section();

  /* Read current IITSR value */

  regval = getreg32(RZV_ICU_IITSR);

  /* Clear the detection bits for this IRQ */

  regval &= ~(0x3 << shift);

  /* Set new detection mode */

  regval |= (mode << shift);

  /* Write back to register */

  putreg32(regval, RZV_ICU_IITSR);

  leave_critical_section(flags);

  /* propagate edge/level config to GIC ICDICFR.
   * External IRQ0-15 pins route through ELC; the GIC SPI for each external
   * IRQ line is at a fixed INTID.  We only know the ICU IRQ line number
   * (0-15) here, not the GIC INTID — that mapping requires the UM Table 12.x
   * which is UNVERIFIED.  The call site (rzv_gpio.c) should call
   * rzv_gic_set_irq_type(icu_irq_gic_intid, edge) after rzv_icu_attach()
   * returns the GIC INTID. See rzv_gpiosetevent() for the correct call point.
   */

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
  /* IFLTC at 0x1C is RESERVED in INTC block.
   * IRQ digital filter lives in GPIO peripheral (FILONOFF/FILNUM/FILCLKSEL).
   * This function is a no-op stub; filter must be configured via GPIO driver.
   * Return -ENOSYS to signal that the operation is not available here.
   */

  (void)irq_num;
  (void)filter_clock;
  return -ENOSYS;
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
 *   icu_irq  - ICU IRQ number returned by rzv_icu_attach() (GIC INTID)
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
 *   - GIC implements 4 priority bits in bits[7:4] (0-15 logical levels)
 *
 ****************************************************************************/

int rzv_icu_set_priority(int icu_irq, int priority)
{
  /* Validate IRQ range — SEL INTIDs start at RZV_INTC_SEL_SPI_BASE (385 =
   * FSP FIXED_INTSEL_COUNT 353 + RZV_IRQ_FIRST 32).
   */

  if (icu_irq < RZV_INTC_SEL_SPI_BASE ||
      icu_irq >= (RZV_INTC_SEL_SPI_BASE + RZV_IRQ_ICU_SLOTS))
    {
      return -EINVAL;
    }

  /* Validate priority range (0-15 for the 4 implemented GIC priority bits).
   * R9A09G057H implements priority in bits [7:4] (FSP IRQ_PRIORITY_POS_BIT=4),
   * and the CPU interface binary point (ICCBPR=0x03) uses [7:4] as the group
   * priority for preemption — so 16 distinct preempting levels are available.
   * Priority 0x00 = highest, 0xF0 = lowest.
   */

  if (priority < 0 || priority > 15)
    {
      return -EINVAL;
    }

#ifdef CONFIG_ARCH_IRQPRIO
  /* GIC priority occupies bits [7:4] of the priority byte; shift the logical
   * 0-15 level into place.
   */

  return up_prioritize_irq(icu_irq, priority << 4);
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
  /* wakeup not implemented on RZV2H CR8 target */

  (void)mask;
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
  /* wakeup not implemented on RZV2H CR8 target */

  (void)mask;
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
  /* honor mask parameter.
   * RZV2H NSCLR bit 0 = NCLR (write-1-to-clear).  The NMI is single-bit
   * on this SoC, so only bit 0 of mask is relevant.
   */

  if (mask & 0x1u)
    {
      putreg32(INTC_NSCLR_NCLR, RZV_ICU_NSCLR);
    }
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
  /* 0x0C is RESERVED in the INTC block; the NMI digital filter lives in the
   * GPIO peripheral (FILONOFF/FILNUM/FILCLKSEL).  Only NITSR (0x08) is valid
   * here, and its bit 0 (NTSEL) is a rising/falling edge select, not a
   * filter-enable.  This function is a no-op stub; configure the NMI filter
   * via GPIO.
   */

  (void)filter_enable;
  (void)filter_clock;
  return -ENOSYS;
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
  /* NMI enable unimplemented on RZV2H CR8 (single-bit NMI,
   * always enabled by hardware at reset). No register write needed. */

  (void)mask;
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
  /* NMI disable not supported on RZV2H (NMI is non-maskable). */

  (void)mask;
}

/****************************************************************************
 * TINT (GPIO-source) support
 *
 * Any GPIO-capable pin can raise an interrupt via one of 32 TINT channels.
 * Each channel selects a 7-bit GPIOINT source (pin identity) and one of four
 * trigger modes (rising/falling/high-level/low-level — no native both-edge).
 * The TINT channel's output presents itself to INTR8SEL as ELC event 0-31
 * (see FSP bsp_irq_id.h GPIO_TINT<n>_IRQSELn), so channel N is routed to a
 * GIC line by feeding "event N" into rzv_icu_attach() — the same dynamic
 * slot allocator used for every other selectable source.
 *
 * Register-programming recipe follows FSP r_intc_tint.c exactly (TITSR
 * trigger, TSSR TSSEL|TIEN, TSCLR-with-dummy-reads).
 ****************************************************************************/

/* Bitmap allocator: bit N = channel N in use. */
static uint32_t g_tint_channel_bitmap;

int rzv_icu_tint_alloc(void)
{
  irqstate_t flags;
  int ch;

  flags = enter_critical_section();
  for (ch = 0; ch < (int)RZV_ICU_TINT_CHANNELS; ch++)
    {
      if ((g_tint_channel_bitmap & (1U << ch)) == 0U)
        {
          g_tint_channel_bitmap |= (1U << ch);
          leave_critical_section(flags);
          return ch;
        }
    }

  leave_critical_section(flags);
  return -EBUSY;
}

void rzv_icu_tint_free(int channel)
{
  irqstate_t flags;

  if (channel < 0 || channel >= (int)RZV_ICU_TINT_CHANNELS)
    {
      return;
    }

  flags = enter_critical_section();
  g_tint_channel_bitmap &= ~(1U << channel);
  leave_critical_section(flags);
}

/* Program TITSR trigger for `channel`.  Accepts driver trigger values
 * ICU_TITSR_RISING / _FALLING / _LEVEL_HIGH / _LEVEL_LOW.  Both-edge is not
 * native; caller must reject it before reaching here.
 */

int rzv_icu_tint_set_trigger(int channel, uint8_t trigger)
{
  irqstate_t flags;
  uintptr_t  regaddr;
  uint32_t   regval;
  uint32_t   shift;

  if (channel < 0 || channel >= (int)RZV_ICU_TINT_CHANNELS)
    {
      return -EINVAL;
    }

  if (trigger > ICU_TITSR_LEVEL_LOW)
    {
      return -EINVAL;
    }

  regaddr = (channel < 16) ? RZV_ICU_TITSR0 : RZV_ICU_TITSR1;
  shift   = (channel % 16) * 2U;

  flags = enter_critical_section();
  regval  = getreg32(regaddr);
  regval &= ~(0x3U << shift);
  regval |= ((uint32_t)trigger << shift);
  putreg32(regval, regaddr);
  leave_critical_section(flags);

  return OK;
}

/* Program TSSR for `channel`: TSSEL=gpioint (7-bit), TIEN=enable. */

int rzv_icu_tint_set_source(int channel, uint8_t gpioint, bool enable)
{
  irqstate_t flags;
  uintptr_t  regaddr;
  uint32_t   regval;
  uint32_t   shift;

  if (channel < 0 || channel >= (int)RZV_ICU_TINT_CHANNELS)
    {
      return -EINVAL;
    }

  regaddr = RZV_ICU_TSSR(channel / 4);
  shift   = ICU_TSSR_LANE_SHIFT(channel);

  flags = enter_critical_section();
  regval  = getreg32(regaddr);
  regval &= ~ICU_TSSR_LANE_MASK(channel);
  regval |= (ICU_TSSR_LANE_VAL(gpioint, enable) << shift);
  putreg32(regval, regaddr);
  leave_critical_section(flags);

  return OK;
}

/* Clear TINT status flag for `channel`.  For edge triggers only — level
 * triggers reflect the pin state and do not need clearing.  Matches FSP
 * BSP_INTC_TINT_CLR_STATE_FLAG: read TSCTR (dummy) → write TSCLR bit → read
 * TSCTR (dummy) to guard against a re-fire of the just-cleared source.
 * Source: bsp_override.h:2574-2586.
 */

void rzv_icu_tint_clear_flag(int channel)
{
  volatile uint32_t dummy;

  if (channel < 0 || channel >= (int)RZV_ICU_TINT_CHANNELS)
    {
      return;
    }

  dummy = getreg32(RZV_ICU_TSCTR);
  (void)dummy;

  putreg32(1U << channel, RZV_ICU_TSCLR);

  dummy = getreg32(RZV_ICU_TSCTR);
  (void)dummy;
}

/****************************************************************************
 * arch/arm/src/rzv/rzv_icu_cm33.c
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

/* This file diverged from rzv_icu.c (CR8) to use:
 *   - INTM33SEL registers (base 0x01EC) instead of INTR8SEL (0x012C)
 *   - RZV_INTC_M33SEL_SPI_BASE instead of RZV_INTC_SEL_SPI_BASE
 *
 * INTM33SEL has 43 registers × 3 slots per register = 129 slots.
 * Same 10-bit-per-field, 3-per-reg layout as INTR8SEL (confirmed from
 * hardware/rzv_intc.h INTM33SEL bit definitions).
 *
 * RZV_INTC_M33SEL_SPI_BASE: NVIC INTID for CM33 SEL slot 0 = 385, FSP-verified
 * (CM33 bsp_feature.h SELECT_IRQ_MIN = FIXED_INTSEL_COUNT = 353, same as CR8;
 * NuttX IRQ = RZV_IRQ_FIRST(32) + NVIC index).  See the interrupt-unification
 * plan (Phase 4 / §11a) for the full derivation.  NOT yet exercised on a real
 * CM33 target — validate on hardware/sim before relying on it.
 */

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
#include "hardware/rzv_intc.h"
#include "rzv_icu.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* INTM33SEL register base and helper macros.
 * INTM33SEL0 is at INTC offset 0x01EC (RZV_INTC_INTM33SEL0_OFFSET).
 * Each register holds 3 × 10-bit slots, same layout as INTR8SEL.
 */
#define RZV_INTC_INTM33SEL(m) \
    (RZV_INTC_BASE + RZV_INTC_INTM33SEL0_OFFSET + ((m) * 4))
#define RZV_INTC_INTM33SEL_REG(slot)   ((slot) / 3)
#define RZV_INTC_INTM33SEL_IDX(slot)   ((slot) % 3)
#define RZV_INTC_INTM33SEL_SHIFT(idx)  ((idx) * 10)
#define RZV_INTC_INTM33SEL_MASK        0x3FF

/* NVIC INTID base for CM33 INTM33SEL slot 0 (FSP-verified, see file banner).
 * 385 = FSP FIXED_INTSEL_COUNT(353) + RZV_IRQ_FIRST(32); identical to the CR8
 * RZV_INTC_SEL_SPI_BASE because NuttX numbering is core-independent — only the
 * SEL register block (INTM33SEL vs INTR8SEL) and delivery (NVIC vs GIC) differ.
 */
#ifndef RZV_INTC_M33SEL_SPI_BASE
#  define RZV_INTC_M33SEL_SPI_BASE     (385)
#endif

/* CM33 pending-clear goes through the NVIC (this core has no GIC).
 * NVIC external index = NuttX IRQ - RZV_IRQ_FIRST; ICPR0 @ 0xE000E280
 * (matches rzv_irq_cm33.c NVIC_BASE 0xE000E100 + ICPR offset 0x180).
 */
#define RZV_NVIC_ICPR_BASE  0xE000E280u

static inline void rzv_cm33_nvic_clear_pending(int irq)
{
  uint32_t nvic_irq = (uint32_t)(irq - RZV_IRQ_FIRST);
  putreg32(1u << (nvic_irq & 31u),
           RZV_NVIC_ICPR_BASE + ((nvic_irq >> 5) << 2));
}

/****************************************************************************
 * Type Definitions
 ****************************************************************************/

typedef struct
{
  xcpt_t handler;   /* Handler function */
  void  *arg;       /* Argument for handler */
} rzv_icu_m33_handler_t;

/****************************************************************************
 * Private Data
 ****************************************************************************/

static rzv_icu_m33_handler_t g_icu_m33_handlers[RZV_IRQ_ICU_SLOTS];
static uint32_t g_icu_m33_slot = 0;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_icu_m33_set_event
 *
 * Description:
 *   Route ELC event to CM33 NVIC via INTM33SEL register.
 *
 ****************************************************************************/

static int rzv_icu_m33_set_event(int slot, int event)
{
  irqstate_t flags;
  uint32_t   regaddr;
  uint32_t   regval;
  int        reg_num;
  int        slot_idx;
  int        shift;

  if (slot < 0 || slot >= RZV_IRQ_ICU_SLOTS)
    {
      return -EINVAL;
    }

  reg_num  = RZV_INTC_INTM33SEL_REG(slot);
  slot_idx = RZV_INTC_INTM33SEL_IDX(slot);
  shift    = RZV_INTC_INTM33SEL_SHIFT(slot_idx);
  regaddr  = RZV_INTC_INTM33SEL(reg_num);

  flags  = enter_critical_section();
  regval = getreg32(regaddr);
  regval &= ~(RZV_INTC_INTM33SEL_MASK << shift);
  regval |= ((event & RZV_INTC_INTM33SEL_MASK) << shift);
  putreg32(regval, regaddr);
  leave_critical_section(flags);

  return OK;
}

/****************************************************************************
 * Name: rzv_icu_m33_interrupt
 *
 * Description:
 *   Common CM33 ICU interrupt handler.
 *
 ****************************************************************************/

static int rzv_icu_m33_interrupt(int irq, void *context, void *arg)
{
  int slot = (int)(uintptr_t)arg;

  if (g_icu_m33_handlers[slot].handler != NULL)
    {
      return g_icu_m33_handlers[slot].handler(irq, context,
                                              g_icu_m33_handlers[slot].arg);
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_icu_m33_initialize
 *
 * Description:
 *   Initialize CM33 ICU handler table.
 *
 ****************************************************************************/

void rzv_icu_m33_initialize(void)
{
  int i;

  for (i = 0; i < RZV_IRQ_ICU_SLOTS; i++)
    {
      g_icu_m33_handlers[i].handler = NULL;
      g_icu_m33_handlers[i].arg     = NULL;
    }

  g_icu_m33_slot = 0;
}

/****************************************************************************
 * Name: rzv_icu_m33_attach
 *
 * Description:
 *   Attach a CM33 ICU interrupt handler.
 *   Uses INTM33SEL routing (not INTR8SEL).
 *
 * Returns:
 *   NuttX IRQ number (NVIC INTID) on success, negated errno on failure.
 *
 ****************************************************************************/

int rzv_icu_m33_attach(int event, xcpt_t handler, void *arg, bool irq_enable)
{
  irqstate_t flags;
  int        slot;
  int        irq;

  flags = enter_critical_section();

  if (g_icu_m33_slot >= RZV_IRQ_ICU_SLOTS)
    {
      leave_critical_section(flags);
      return -ENOMEM;
    }

  slot = g_icu_m33_slot++;

  leave_critical_section(flags);

  /* irq = M33SEL SEL base + slot (base 385 already includes RZV_IRQ_FIRST) */

  irq = RZV_INTC_M33SEL_SPI_BASE + slot;

  /* store handler before programming selector */

  g_icu_m33_handlers[slot].handler = handler;
  g_icu_m33_handlers[slot].arg     = arg;

  irq_attach(irq, rzv_icu_m33_interrupt, (void *)(uintptr_t)slot);

  /* Clear stale NVIC pending, then route event */

  rzv_cm33_nvic_clear_pending(irq);

  rzv_icu_m33_set_event(slot, event);

  if (irq_enable)
    {
      up_enable_irq(irq);
    }

  return irq;
}

/****************************************************************************
 * Name: rzv_icu_m33_detach
 *
 * Description:
 *   Detach a CM33 ICU interrupt handler.
 *
 ****************************************************************************/

int rzv_icu_m33_detach(int icu_irq)
{
  irqstate_t flags;
  int        slot;
  int        i;
  int        highest_used;

  if (icu_irq < RZV_INTC_M33SEL_SPI_BASE ||
      icu_irq >= (RZV_INTC_M33SEL_SPI_BASE + RZV_IRQ_ICU_SLOTS))
    {
      return -EINVAL;
    }

  slot = icu_irq - RZV_INTC_M33SEL_SPI_BASE;

  if (g_icu_m33_handlers[slot].handler == NULL)
    {
      return -ENOENT;
    }

  up_disable_irq(icu_irq);
  irq_detach(icu_irq);

  rzv_icu_m33_set_event(slot, 0);

  g_icu_m33_handlers[slot].handler = NULL;
  g_icu_m33_handlers[slot].arg     = NULL;

  flags = enter_critical_section();

  highest_used = -1;
  for (i = 0; i < (int)RZV_IRQ_ICU_SLOTS; i++)
    {
      if (g_icu_m33_handlers[i].handler != NULL)
        {
          highest_used = i;
        }
    }

  g_icu_m33_slot = highest_used + 1;

  leave_critical_section(flags);

  return OK;
}

/****************************************************************************
 * Name: rzv_icu_initialize
 *
 * Description:
 *   Common ICU API wrapper for the CM33 implementation.
 *
 ****************************************************************************/

void rzv_icu_initialize(void)
{
  rzv_icu_m33_initialize();
}

/****************************************************************************
 * Name: rzv_icu_attach
 *
 * Description:
 *   Common ICU API wrapper for the CM33 implementation.
 *
 ****************************************************************************/

int rzv_icu_attach(int event, xcpt_t handler, void *arg, bool irq_enable)
{
  return rzv_icu_m33_attach(event, handler, arg, irq_enable);
}

/****************************************************************************
 * Name: rzv_icu_detach
 *
 * Description:
 *   Common ICU API wrapper for the CM33 implementation.
 *
 ****************************************************************************/

int rzv_icu_detach(int icu_irq)
{
  return rzv_icu_m33_detach(icu_irq);
}

/****************************************************************************
 * Name: rzv_icu_clear_irq
 *
 * Description:
 *   Clear pending CM33 ICU interrupt state.
 *
 ****************************************************************************/

void rzv_icu_clear_irq(int irq)
{
  if (irq >= RZV_INTC_M33SEL_SPI_BASE &&
      irq < (RZV_INTC_M33SEL_SPI_BASE + RZV_IRQ_ICU_SLOTS))
    {
      rzv_cm33_nvic_clear_pending(irq);
    }
}

/****************************************************************************
 * Name: rzv_icu_set_priority
 *
 * Description:
 *   Set CM33 ICU interrupt priority. Not implemented yet for INTM33SEL.
 *
 ****************************************************************************/

int rzv_icu_set_priority(int icu_irq, int priority)
{
  return -ENOSYS;
}

/****************************************************************************
 * Name: rzv_icu_set_event
 *
 * Description:
 *   Common ICU API wrapper for CM33 INTM33SEL routing.
 *
 ****************************************************************************/

int rzv_icu_set_event(int icu_slot, int event)
{
  return rzv_icu_m33_set_event(icu_slot, event);
}

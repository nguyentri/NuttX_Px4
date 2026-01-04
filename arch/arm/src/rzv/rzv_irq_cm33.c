/****************************************************************************
 * arch/arm/src/rzv/rzv_irq_cm33.c
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

#include <stdint.h>
#include <assert.h>
#include <debug.h>
#include <errno.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>

#include "arm_internal.h"
#include "nvic.h"
#include "ram_vectors.h"

#include "rzv_icu_cm33.h"
#include "hardware/rzv_intc.h"

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* g_current_regs[] holds a reference to the current interrupt level
 * register storage structure.  It is non-NULL only during interrupt
 * processing.  Access to g_current_regs[] must be through the
 * CURRENT_REGS macro for portability.
 */

volatile uint32_t *g_current_regs[1];

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* NVIC Base Address for CM33 */
#define NVIC_BASE               0xE000E100

/* NVIC Register Offsets */
#define NVIC_ISER_OFFSET(n)     (0x000 + ((n) << 2))  /* Interrupt Set-Enable */
#define NVIC_ICER_OFFSET(n)     (0x080 + ((n) << 2))  /* Interrupt Clear-Enable */
#define NVIC_ISPR_OFFSET(n)     (0x100 + ((n) << 2))  /* Interrupt Set-Pending */
#define NVIC_ICPR_OFFSET(n)     (0x180 + ((n) << 2))  /* Interrupt Clear-Pending */
#define NVIC_IABR_OFFSET(n)     (0x200 + ((n) << 2))  /* Interrupt Active Bit */
#define NVIC_IPR_OFFSET(n)      (0x300 + (n))         /* Interrupt Priority */

/* NVIC Register Addresses */
#define NVIC_ISER(n)            (NVIC_BASE + NVIC_ISER_OFFSET(n))
#define NVIC_ICER(n)            (NVIC_BASE + NVIC_ICER_OFFSET(n))
#define NVIC_ISPR(n)            (NVIC_BASE + NVIC_ISPR_OFFSET(n))
#define NVIC_ICPR(n)            (NVIC_BASE + NVIC_ICPR_OFFSET(n))
#define NVIC_IABR(n)            (NVIC_BASE + NVIC_IABR_OFFSET(n))
#define NVIC_IPR(n)             (NVIC_BASE + NVIC_IPR_OFFSET(n))

/* Priority grouping */
#define NVIC_PRIGROUP_SHIFT     8
#define NVIC_PRIGROUP_MASK      0x07

/* Priority levels are now defined in chip.h */

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_cm33_nvic_init
 *
 * Description:
 *   Initialize the NVIC. Sets up priority grouping and default priorities.
 *
 ****************************************************************************/

static void rzv_cm33_nvic_init(void)
{
  int i;

  /* Disable all interrupts */
  for (i = 0; i < (NR_IRQS - NVIC_IRQ_FIRST) / 32; i++)
    {
      putreg32(0xFFFFFFFF, NVIC_ICER(i));
    }

  /* Clear all pending interrupts */
  for (i = 0; i < (NR_IRQS - NVIC_IRQ_FIRST) / 32; i++)
    {
      putreg32(0xFFFFFFFF, NVIC_ICPR(i));
    }

  /* Set all interrupt priorities to default */
  for (i = 0; i < (NR_IRQS - NVIC_IRQ_FIRST); i++)
    {
      putreg8(NVIC_SYSH_PRIORITY_DEFAULT, NVIC_IPR(i));
    }

  /* Set priority grouping to 0 (all bits for preemption priority) */
  uint32_t aircr = getreg32(NVIC_AIRCR);
  aircr &= ~(NVIC_PRIGROUP_MASK << NVIC_PRIGROUP_SHIFT);
  aircr |= (0x05FA << 16);  /* VECTKEY */
  putreg32(aircr, NVIC_AIRCR);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_irqinitialize
 *
 * Description:
 *   Initialize the interrupt subsystem for the CM33 core.
 *   This includes:
 *   - NVIC initialization
 *   - ICU (Interrupt Control Unit) initialization
 *   - Setting up exception handlers
 *
 ****************************************************************************/

void up_irqinitialize(void)
{
  /* Disable interrupts during initialization */
  up_irq_save();

#ifdef CONFIG_ARM_MPU
  /* Initialize the MPU (if configured) */
  arm_mpu_initialize();
#endif

  /* Initialize the NVIC */
  rzv_cm33_nvic_init();

  /* Initialize the ICU (Interrupt Control Unit) for dynamic event routing */
  rzv_icu_initialize();

#ifndef CONFIG_SUPPRESS_INTERRUPTS

  /* And finally, enable interrupts globally */
  up_irq_enable();

#endif
}

/****************************************************************************
 * Name: up_disable_irq
 *
 * Description:
 *   Disable the IRQ specified by 'irq'
 *
 ****************************************************************************/

void up_disable_irq(int irq)
{
  int regndx;
  int bit;

  if (irq >= RZV_IRQ_FIRST && irq < NR_IRQS)
    {
      /* IRQ is in the valid range */
      irq -= RZV_IRQ_FIRST;  /* Convert to NVIC IRQ number */

      regndx = irq >> 5;     /* Register index (divide by 32) */
      bit    = irq & 0x1f;   /* Bit position within register */

      /* Disable the interrupt */
      putreg32(1 << bit, NVIC_ICER(regndx));
    }
}

/****************************************************************************
 * Name: up_enable_irq
 *
 * Description:
 *   Enable the IRQ specified by 'irq'
 *
 ****************************************************************************/

void up_enable_irq(int irq)
{
  int regndx;
  int bit;

  if (irq >= RZV_IRQ_FIRST && irq < NR_IRQS)
    {
      /* IRQ is in the valid range */
      irq -= RZV_IRQ_FIRST;  /* Convert to NVIC IRQ number */

      regndx = irq >> 5;     /* Register index (divide by 32) */
      bit    = irq & 0x1f;   /* Bit position within register */

      /* Enable the interrupt */
      putreg32(1 << bit, NVIC_ISER(regndx));
    }
}

/****************************************************************************
 * Name: up_ack_irq
 *
 * Description:
 *   Acknowledge the interrupt. On Cortex-M, this is a no-op as the
 *   hardware automatically acknowledges interrupts.
 *
 ****************************************************************************/

void up_ack_irq(int irq)
{
  /* On Cortex-M, interrupt acknowledgment is automatic.
   * The NVIC hardware clears the pending bit when the ISR is entered.
   * No explicit action needed here.
   */
}

/****************************************************************************
 * Name: up_prioritize_irq
 *
 * Description:
 *   Set the priority of an IRQ.
 *
 * Input Parameters:
 *   irq      - The IRQ number
 *   priority - The new priority (0-255, where 0 is highest priority)
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure
 *
 ****************************************************************************/

#ifdef CONFIG_ARCH_IRQPRIO
int up_prioritize_irq(int irq, int priority)
{
  if (irq >= RZV_IRQ_FIRST && irq < NR_IRQS)
    {
      /* Convert to NVIC IRQ number */
      irq -= RZV_IRQ_FIRST;

      /* Validate priority value (0-255) */
      if (priority < 0 || priority > 255)
        {
          return -EINVAL;
        }

      /* Set the priority in the NVIC IPR register */
      putreg8((uint8_t)priority, NVIC_IPR(irq));

      return OK;
    }

  return -EINVAL;
}
#endif

/****************************************************************************
 * Name: up_irq_save
 *
 * Description:
 *   Disable interrupts and return the previous interrupt state
 *
 ****************************************************************************/

/* up_irq_save, up_irq_restore, and up_irq_enable are provided as
 * inline functions in arch/armv8-m/irq.h
 */

/****************************************************************************
 * Exception Handlers
 ****************************************************************************/

/****************************************************************************
 * Name: exception_common
 *
 * Description:
 *   Common exception handler. This is called for all exceptions that
 *   don't have a specific handler registered.
 *
 ****************************************************************************/

int exception_common(int irq, uint32_t *regs, void *arg)
{
  PANIC();
  return 0;  /* Won't get here */
}

/****************************************************************************
 * Name: arm_hardfault
 *
 * Description:
 *   Hard Fault exception handler
 *
 ****************************************************************************/

int arm_hardfault(int irq, void *context, void *arg)
{
  _alert("HARD FAULT:\n");
  _alert("  IRQ: %d\n", irq);
  up_dump_register(context);
  PANIC();
  return 0;  /* Won't get here */
}

/****************************************************************************
 * Name: arm_memfault
 *
 * Description:
 *   Memory Management Fault handler
 *
 ****************************************************************************/

int arm_memfault(int irq, void *context, void *arg)
{
  _alert("MEMORY MANAGEMENT FAULT:\n");
  _alert("  IRQ: %d\n", irq);
  up_dump_register(context);
  PANIC();
  return 0;  /* Won't get here */
}

/****************************************************************************
 * Name: arm_busfault
 *
 * Description:
 *   Bus Fault exception handler
 *
 ****************************************************************************/

int arm_busfault(int irq, void *context, void *arg)
{
  _alert("BUS FAULT:\n");
  _alert("  IRQ: %d\n", irq);
  up_dump_register(context);
  PANIC();
  return 0;  /* Won't get here */
}

/****************************************************************************
 * Name: arm_usagefault
 *
 * Description:
 *   Usage Fault exception handler
 *
 ****************************************************************************/

int arm_usagefault(int irq, void *context, void *arg)
{
  _alert("USAGE FAULT:\n");
  _alert("  IRQ: %d\n", irq);
  up_dump_register(context);
  PANIC();
  return 0;  /* Won't get here */
}

/****************************************************************************
 * Name: arm_pendsv
 *
 * Description:
 *   PendSV exception handler - used for context switching
 *
 ****************************************************************************/

int arm_pendsv(int irq, void *context, void *arg)
{
  /* Context switch is handled by NuttX core */
  return 0;
}

/****************************************************************************
 * Name: arm_systick
 *
 * Description:
 *   SysTick exception handler - system timer tick
 *
 ****************************************************************************/

int arm_systick(int irq, void *context, void *arg)
{
  /* Process system timer tick */
  nxsched_process_timer();
  return 0;
}

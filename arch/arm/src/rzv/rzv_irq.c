/****************************************************************************
 * arch/arm/src/rzv/rzv_irq.c
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
#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include "gic.h"
#include "chip.h"
#include "arm_internal.h"

#include "rzv_icu.h"
#include "hardware/rzv_intc_gic.h"

/* g_current_regs[] holds a reference to the current interrupt level state.
 * It must be defined by the architecture-specific IRQ implementation.
 */
volatile uint32_t *g_current_regs[1];

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define GIC_NUM_INTERRUPTS    1020
#define GIC_NUM_SGI           16
#define GIC_NUM_PPI           16
#define GIC_NUM_SPI           (GIC_NUM_INTERRUPTS - GIC_NUM_SGI - GIC_NUM_PPI)

/* Default priority for all interrupts */
#ifndef RZV_GIC_DEFAULT_PRIORITY
#  define RZV_GIC_DEFAULT_PRIORITY  0xa0
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/
/****************************************************************************
 * Name: rzv_gic_initialize
 *
 * Description:
 *   Initialize the Generic Interrupt Controller (GIC-400)
 *
 ****************************************************************************/

static void rzv_gic_initialize(void)
{
  uint32_t i;
  uint32_t num_interrupts;

  /* Disable distributor */
  putreg32(0, RZV_INTC_GIC_GICD_ICDDCR);

  /* Get number of interrupt lines */
  num_interrupts = ((getreg32(GIC_ICDICTR) & INTC_GIC_GICD_ICDICTR_IT_MASK) + 1) * 32;

  if (num_interrupts > GIC_NUM_INTERRUPTS)
    {
      num_interrupts = GIC_NUM_INTERRUPTS;
    }

  /* Disable all interrupts and clear all pending bits */
  for (i = 0; i < num_interrupts; i += 32)
    {
      putreg32(0xffffffff, GIC_ICDICER(i / 32));
      putreg32(0xffffffff, GIC_ICDICPR(i / 32));
    }

  /* Set all interrupts to default priority */
  for (i = 0; i < num_interrupts; i += 4)
    {
      putreg32(RZV_GIC_DEFAULT_PRIORITY << 24 |
               RZV_GIC_DEFAULT_PRIORITY << 16 |
               RZV_GIC_DEFAULT_PRIORITY << 8 |
               RZV_GIC_DEFAULT_PRIORITY,
               GIC_ICDIPR(i / 4));
    }

  /* Set all interrupts to target CPU0 */
  for (i = 32; i < num_interrupts; i += 4)
    {
      putreg32(0x01010101, GIC_ICDIPTR(i / 4));
    }

  /* Set all interrupts to level-sensitive */
  for (i = 32; i < num_interrupts; i += 16)
    {
      putreg32(0, GIC_ICDICFR(i / 16));
    }

  /* Enable distributor */
  putreg32(GIC_ICCICR_ENABLE, RZV_INTC_GIC_GICD_ICDDCR);

  /* Initialize CPU interface */

  /* Set priority mask to allow all interrupts */
  putreg32(0xff, GIC_ICCPMR);

  /* Set binary point to 0 (no preemption grouping) */
  putreg32(0, GIC_ICCBPR);

  /* Enable CPU interface */
  putreg32(GIC_ICCICR_ENABLE, GIC_ICCICR);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Function: up_irqinitialize
 *
 * Description:
 *   This function is called by up_initialize() during the bring-up of the
 *   system.  It is the responsibility of this function to but the interrupt
 *   subsystem into the ready-to-run state.
 *
 ****************************************************************************/

void up_irqinitialize(void)
{
  /* Initialize the GIC */
  rzv_gic_initialize();

  /* Initialize the ICU (Interrupt Control Unit) */
  rzv_icu_initialize();

  /* Attach the CPU exception handlers */
  /* Note: These should be implemented in platform-specific code */

#ifndef CONFIG_SUPPRESS_INTERRUPTS
  /* And finally, enable interrupts */
  up_irq_enable();
#endif
}

/****************************************************************************
 * Function: up_disable_irq
 *
 * Description:
 *   Disable the IRQ specified by 'irq'
 *
 ****************************************************************************/

void up_disable_irq(int irq)
{
  uint32_t regaddr;
  uint32_t bit;

  if (irq >= 0 && irq < GIC_NUM_INTERRUPTS)
    {
      /* Calculate register address and bit position */
      regaddr = GIC_ICDICER(irq / 32);
      bit = 1 << (irq % 32);

      /* Disable the interrupt */
      putreg32(bit, regaddr);

      /* Ensure the write completes */
      (void)getreg32(regaddr);
    }
}

/****************************************************************************
 * Function: up_enable_irq
 *
 * Description:
 *   Enable the IRQ specified by 'irq'
 *
 ****************************************************************************/

void up_enable_irq(int irq)
{
  uint32_t regaddr;
  uint32_t bit;

  if (irq >= 0 && irq < GIC_NUM_INTERRUPTS)
    {
      /* Calculate register address and bit position */
      regaddr = GIC_ICDISER(irq / 32);
      bit = 1 << (irq % 32);

      /* Enable the interrupt */
      putreg32(bit, regaddr);

      /* Ensure the write completes */
      (void)getreg32(regaddr);
    }
}

/****************************************************************************
 * Function: up_ack_irq
 *
 * Description:
 *   Acknowledge the interrupt
 *
 ****************************************************************************/

void up_ack_irq(int irq)
{
  /* The GIC automatically acknowledges the interrupt when ICCIAR is read
   * in the interrupt handler. This function writes to ICCEOIR to signal
   * end of interrupt processing.
   */
  if (irq >= 0 && irq < GIC_NUM_INTERRUPTS)
    {
      putreg32(irq, GIC_ICCEOIR);
    }
}

/****************************************************************************
 * Function: up_prioritize_irq
 *
 * Description:
 *   Set the priority of an IRQ.
 *
 ****************************************************************************/

#ifdef CONFIG_ARCH_IRQPRIO
int up_prioritize_irq(int irq, int priority)
{
  uint32_t regaddr;
  uint32_t regval;
  uint32_t shift;

  if (irq >= 0 && irq < GIC_NUM_INTERRUPTS)
    {
      /* Calculate register address and bit shift */
      regaddr = GIC_ICDIPR(irq / 4);
      shift = (irq % 4) * 8;

      /* Validate priority (GIC uses 8 bits, but typically only top bits
       * are implemented)
       */
      if (priority < 0 || priority > 0xff)
        {
          return -EINVAL;
        }

      /* Set the priority */
      regval = getreg32(regaddr);
      regval &= ~(0xff << shift);
      regval |= (priority << shift);
      putreg32(regval, regaddr);

      return OK;
    }

  return -EINVAL;
}
#endif

/****************************************************************************
 * Function: arm_decodeirq
 *
 * Description:
 *   This function is called from the IRQ vector handler in arm_vectors.S.
 *   At this point, the interrupt has been taken and the registers have
 *   been saved on the stack. This function simply needs to determine the
 *   the irq number of the interrupt and then to call arm_doirq to dispatch
 *   the interrupt.
 *
 *  Input Parameters:
 *   regs - A pointer to the register save area on the stack.
 *
 ****************************************************************************/

uint32_t *arm_decodeirq(uint32_t *regs)
{
  uint32_t regval;
  int irq;

  /* Read the interrupt acknowledge register and extract the IRQ number */
  regval = getreg32(GIC_ICCIAR);
  irq = regval & INTC_GIC_GICC_ICCIAR_ACKINTID_MASK;

  /* Check for spurious interrupt */
  if (irq < GIC_NUM_INTERRUPTS)
    {
      /* Dispatch the interrupt */
      regs = arm_doirq(irq, regs);

      /* Write to end of interrupt register */
      putreg32(regval, GIC_ICCEOIR);
    }

  return regs;
}

/****************************************************************************
 * Function: up_irq_save
 *
 * Description:
 *   Disable interrupts and return the previous interrupt state
 *
 ****************************************************************************/

/* The up_irq_save/up_irq_restore/up_irq_enable inline functions are
 * provided by the architecture header include/arch/armv7-r/irq.h.
 * Do not provide alternate definitions here to avoid conflicting
 * multiple definitions. The inline implementations will be used.
 */
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
#include "chip.h"
#include "arm_internal.h"

#include "rzv_icu.h"
#include "rzv_clock.h"
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
#define GIC_SPURIOUS_INTID    1023

/* Default priority for all interrupts */
#ifndef RZV_GIC_DEFAULT_PRIORITY
#  define RZV_GIC_DEFAULT_PRIORITY  0xa0
#endif

#define RZV_GIC_REG_INDEX1(irq)  ((irq) >> 5)
#define RZV_GIC_REG_INDEX4(irq)  ((irq) >> 2)
#define RZV_GIC_REG_INDEX16(irq) ((irq) >> 4)

/****************************************************************************
 * Private Functions
 ****************************************************************************/
/****************************************************************************
 * Name: rzv_gic_initialize
 *
 * Description:
 *   Initialize the Generic Interrupt Controller (GIC-600, GICv2 compat).
 *   All accesses use physical RZV_INTC_GIC_* macros (base 0x12C10100).
 *   CHIP_MPCORE_VBASE / MPCORE_ICD_VBASE are NOT used — no MMU on CR8.
 *
 ****************************************************************************/

static void rzv_gic_initialize(void)
{
  uint32_t i;
  uint32_t num_interrupts;

  /* Disable distributor */
  putreg32(0, RZV_INTC_GIC_GICD_ICDDCR);

  /* Get number of interrupt lines */
  num_interrupts = ((getreg32(RZV_INTC_GIC_GICD_ICDICTR) &
                     INTC_GIC_GICD_ICDICTR_IT_MASK) + 1) * 32;

  if (num_interrupts > GIC_NUM_INTERRUPTS)
    {
      num_interrupts = GIC_NUM_INTERRUPTS;
    }

  /* Disable all interrupts and clear all pending bits */
  for (i = 0; i < num_interrupts; i += 32)
    {
      putreg32(0xffffffff, RZV_INTC_GIC_GICD_ICDICER(RZV_GIC_REG_INDEX1(i)));
      putreg32(0xffffffff, RZV_INTC_GIC_GICD_ICDICPR(RZV_GIC_REG_INDEX1(i)));
    }

  /* Set all interrupts to default priority */
  for (i = 0; i < num_interrupts; i += 4)
    {
      putreg32(RZV_GIC_DEFAULT_PRIORITY << 24 |
               RZV_GIC_DEFAULT_PRIORITY << 16 |
               RZV_GIC_DEFAULT_PRIORITY << 8 |
               RZV_GIC_DEFAULT_PRIORITY,
               RZV_INTC_GIC_GICD_ICDIPR(RZV_GIC_REG_INDEX4(i)));
    }

  /* Set all interrupts to target CPU0 */
  for (i = 32; i < num_interrupts; i += 4)
    {
      putreg32(0x01010101, RZV_INTC_GIC_GICD_ICDIPTR(RZV_GIC_REG_INDEX4(i)));
    }

  /* Set all SPIs to level-sensitive by default.
   * MED-9: edge-triggered IRQs MUST call rzv_gic_set_irq_type(irq, true)
   * after attach; failing to do so hangs the GIC line on first edge.
   */
  for (i = 32; i < num_interrupts; i += 16)
    {
      putreg32(0, RZV_INTC_GIC_GICD_ICDICFR(RZV_GIC_REG_INDEX16(i)));
    }

  /* Initialize CPU interface BEFORE enabling distributor.
   * ARM GIC spec: ICCPMR and ICCBPR must be set before ICCICR.EN=1.
   * Distributor enable (ICDDCR) should come last.
   * audit: Medium-14 — reorder, High-8 — ICCBPR=0x03 for PX4 preemption.
   */

  /* Set priority mask to allow all interrupts */
  putreg32(0xff, RZV_INTC_GIC_GICC_ICCPMR);

  /* Binary point: 0x03 — group priority 4 bits, sub-priority 4 bits.
   * ICCBPR=0 disables preemption entirely; 0x03 enables PX4 nested IRQ. */
  putreg32(0x03, RZV_INTC_GIC_GICC_ICCBPR);

  /* Enable CPU interface */
  putreg32(INTC_GIC_GICC_ICCICR_EN, RZV_INTC_GIC_GICC_ICCICR);

  /* Enable distributor last */
  putreg32(INTC_GIC_GICD_ICDDCR_EN, RZV_INTC_GIC_GICD_ICDDCR);
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
  /* audit High-6: Ensure INTC/ICU clocks are live before GIC init.
   * RZV_CPG_CLK_ICU gates the ICU peripheral (domain 0, bit 1).
   * The INTC block (GIC-600) is clocked by the always-on fabric;
   * no separate CLKON gate found in available headers — verify UM.
   */

  rzv_clock_enable(RZV_CPG_CLK_ICU);
  rzv_module_unreset(RZV_CPG_CLK_ICU);

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

  /* audit Medium-16: bound on NR_IRQS, not GIC_NUM_INTERRUPTS */

  if (irq >= 0 && irq < NR_IRQS)
    {
      /* Calculate register address and bit position */
      regaddr = RZV_INTC_GIC_GICD_ICDICER(RZV_GIC_REG_INDEX1(irq));
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

  /* audit Medium-16: bound on NR_IRQS, not GIC_NUM_INTERRUPTS */

  if (irq >= 0 && irq < NR_IRQS)
    {
      /* Calculate register address and bit position */
      regaddr = RZV_INTC_GIC_GICD_ICDISER(RZV_GIC_REG_INDEX1(irq));
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
  /* audit Medium-12: ICCEOIR must be written with the FULL ICCIAR value
   * (including CPUID bits [12:10]), not just the IRQ number.
   * arm_decodeirq() does this correctly by preserving regval from ICCIAR.
   * This standalone up_ack_irq() should NOT be called from driver ISRs —
   * those should return through arm_decodeirq() which writes ICCEOIR properly.
   * Retained for NuttX arch API compliance; use from outside arm_decodeirq
   * risks premature EOI on the wrong CPU interface lane (SMP risk).
   */
  if (irq >= 0 && irq < NR_IRQS)
    {
      putreg32(irq, RZV_INTC_GIC_GICC_ICCEOIR);
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

  if (irq >= 0 && irq < NR_IRQS)
    {
      /* Calculate register address and bit shift */
      regaddr = RZV_INTC_GIC_GICD_ICDIPR(RZV_GIC_REG_INDEX4(irq));
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
  regval = getreg32(RZV_INTC_GIC_GICC_ICCIAR);
  irq = regval & INTC_GIC_GICC_ICCIAR_ACKINTID_MASK;

  /* Check for spurious interrupt */
  if (irq < GIC_NUM_INTERRUPTS && irq != GIC_SPURIOUS_INTID)
    {
      /* Dispatch the interrupt */
      regs = arm_doirq(irq, regs);

      /* Write to end of interrupt register */
      putreg32(regval, RZV_INTC_GIC_GICC_ICCEOIR);
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

/****************************************************************************
 * Function: rzv_gic_set_irq_type
 *
 * Description:
 *   MED-9 fix: Configure GIC ICDICFR for edge or level sensitivity.
 *   GIC is initialized with all SPIs level-sensitive (ICDICFR=0).
 *   Edge-triggered ICU external IRQ pins require the corresponding GIC
 *   SPI to also be configured edge-sensitive; otherwise GIC waits for
 *   line de-assertion that never comes (edge source) → interrupt stuck.
 *
 *   ICDICFR layout: 2 bits per interrupt.
 *     [1:0] = 0b00 → level-sensitive
 *     [1:0] = 0b10 → edge-triggered
 *   Bit 0 is read-only (model); only bit 1 (type) is writable.
 *
 * Input Parameters:
 *   irq  - NuttX IRQ number (== GIC INTID)
 *   edge - true = configure as edge-triggered, false = level-sensitive
 *
 ****************************************************************************/

void rzv_gic_set_irq_type(int irq, bool edge)
{
  uint32_t regaddr;
  uint32_t regval;
  uint32_t bit_offset;

  if (irq < 0 || irq >= NR_IRQS)
    {
      return;
    }

  /* Each 32-bit ICDICFR register covers 16 interrupts (2 bits each).
   * Bit offset within register: (irq % 16) * 2.
   * Only the upper bit (bit 1 of the 2-bit field) selects edge vs level.
   */

  regaddr    = RZV_INTC_GIC_GICD_ICDICFR(RZV_GIC_REG_INDEX16(irq));
  bit_offset = (irq % 16) * 2;

  regval = getreg32(regaddr);
  if (edge)
    {
      regval |= (2u << bit_offset);   /* set type bit → edge */
    }
  else
    {
      regval &= ~(2u << bit_offset);  /* clear type bit → level */
    }

  putreg32(regval, regaddr);
}

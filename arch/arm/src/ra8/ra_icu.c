/****************************************************************************
 * arch/arm/src/ra8/ra_icu.c
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
#include "chip.h"
#include "hardware/ra_memorymap.h"
#include "ra_icu.h"
#include "ra_dmac.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Type Definitions
 ****************************************************************************/

typedef struct {
  int el; /* Event Link number */
  xcpt_t handler; /* Handler function */
  void *arg; /* Argument for handler */
} ra_icu_handler_t;

/****************************************************************************
 * Private Data
 *
 * Global ICU handler structure - supports both configuration and runtime registration
 */
static ra_icu_handler_t g_icu_handlers[RA_IRQ_IELSR_SIZE];
static uint32_t g_icu_slot = 0; /* next available slot */

/****************************************************************************
 * Configuration-time interrupt definitions
 * These are registered during system initialization
 ****************************************************************************/

typedef struct
{
  int event;
  xcpt_t handler;
  void *arg;
} ra_config_irq_t;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_icu_clear_irq
 *
 * Description:
 *   Clear interrupt request status. For most RA8 peripherals, interrupt
 *   clearing is handled by the peripheral itself (e.g., reading data from
 *   UART, clearing GPT status flags). The ICU IELSR.IR bit is automatically
 *   cleared when the interrupt is acknowledged.
 *
 ****************************************************************************/

void ra_icu_clear_irq(int irq)
{
  uint32_t regaddr;
  regaddr = irq - RA_IRQ_FIRST;
  modifyreg32(R_ICU_IELSR(regaddr), R_ICU_IELSR_IR, 0);
  getreg32(R_ICU_IELSR(regaddr));
}

/****************************************************************************
 * Name: ra_icu_interrupt
 *
 * Description:
 *   Common ICU interrupt handler
 *
 ****************************************************************************/

static int ra_icu_interrupt(int irq, void *context, void *arg)
{
  int icu_slot = (int)(uintptr_t)arg;

  /* Call the registered handler if available */
  if (g_icu_handlers[icu_slot].handler != NULL)
    {
      /* Clear the interrupt  */
      ra_icu_clear_irq(irq);
      return g_icu_handlers[icu_slot].handler(irq, context, g_icu_handlers[icu_slot].arg);
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_icu_initialize
 *
 * Description:
 *   Initialize the ICU driver and register configuration-time interrupts
 *
 ****************************************************************************/

void ra_icu_initialize(void)
{
  int i;

  /* Initialize the handlers structure */
  for (i = 0; i < RA_IRQ_IELSR_SIZE; i++)
    {
      g_icu_handlers[i].el = -1;
      g_icu_handlers[i].handler = NULL;
      g_icu_handlers[i].arg = NULL;
    }

  /* Reset slot counter */
  g_icu_slot = 0;

}

/****************************************************************************
 * Name: ra_icu_attach
 *
 * Description:
 *   Attach an ICU interrupt handler at the runtime
 *   This function handles both event linking and IRQ enabling
 *   This must only be called after a hardware event has been configured
 *
 ****************************************************************************/

int ra_icu_attach(int event, xcpt_t handler, void *arg, bool irq_enable)
{
  int slot;

  /* Find next available slot */
  if (g_icu_slot >= RA_IRQ_IELSR_SIZE)
    {
      return -ENOMEM;
    }

  slot = g_icu_slot++;

  /* Clear the IELSR slot first (required before setting event link) */
  putreg32(0, R_ICU_IELSR(slot));

  /* Set up the ICU event link */
  ra_icu_set_event(slot, event);

  /* Store the handler information */
  g_icu_handlers[slot].el = event;
  g_icu_handlers[slot].handler = handler;
  g_icu_handlers[slot].arg = arg;

  /* Attach the common interrupt handler */
  irq_attach(RA_IRQ_FIRST + slot, ra_icu_interrupt, (void *)(uintptr_t)slot);

  /* Enable the interrupt */
  if (irq_enable)
    {
      up_enable_irq(RA_IRQ_FIRST + slot);
    }

  return RA_IRQ_FIRST + slot;
}

/****************************************************************************
 * Name: ra_icu_detach
 *
 * Description:
 *   Detach an ICU interrupt handler (unified API)
 *   This function handles both IRQ disabling and slot deallocation
 *
 ****************************************************************************/

int ra_icu_detach(int icu_irq)
{
  int slot;
  int i;

  /* Validate IRQ range */
  if (icu_irq < RA_IRQ_FIRST || icu_irq >= 112)
    {
      return -EINVAL;
    }

  slot = icu_irq - RA_IRQ_FIRST;

  /* Validate slot range */
  if (slot < 0 || slot >= RA_IRQ_IELSR_SIZE)
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
  ra_icu_set_event(slot, 0);

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
 * Name: ra_icu_set_event
 *
 * Description:
 *   Set ICU event link
 *
 ****************************************************************************/

int ra_icu_set_event(int icu_slot, int event)
{
  uint32_t regaddr;
  uint32_t regval;

  if (icu_slot < 0 || icu_slot >= RA_IRQ_IELSR_SIZE)
    {
      return -EINVAL;
    }

  regaddr = R_ICU_IELSR(icu_slot);
  regval = getreg32(regaddr);

  regval &= ~(R_ICU_IELSR_IELS_MASK << R_ICU_IELSR_IELS_SHIFT);
  regval |= (event & R_ICU_IELSR_IELS_MASK) << R_ICU_IELSR_IELS_SHIFT;

  putreg32(regval, regaddr);

  return OK;
}

/****************************************************************************
 * Name: ra_icu_set_priority
 *
 * Description:
 *   Set interrupt priority for a dynamically allocated ICU IRQ.
 *   This function wraps the architecture-specific up_prioritize_irq()
 *   to provide a consistent ICU-level API.
 *
 * Input Parameters:
 *   icu_irq  - ICU IRQ number (RA_IRQ_FIRST + slot)
 *   priority - Priority level (0 = highest, 15 = lowest for Cortex-M)
 *              Typical values: 0-3 (high), 4-7 (medium), 8-15 (low)
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure.
 *
 * Notes:
 *   - Priority must be set before enabling the interrupt
 *   - Lower numerical values = higher priority
 *   - Priority 0 is reserved for critical system interrupts
 *   - Recommended: Use 3-5 for storage, 6-8 for communication
 *
 ****************************************************************************/

int ra_icu_set_priority(int icu_irq, int priority)
{
  /* Validate IRQ range */
  if (icu_irq < RA_IRQ_FIRST || icu_irq >= (RA_IRQ_FIRST + RA_IRQ_IELSR_SIZE))
    {
      return -EINVAL;
    }

  /* Validate priority range (0-15 for Cortex-M, per NVIC spec)
   * NVIC_SYSH_PRIORITY_MIN is typically 0xFF (lowest priority)
   * We shift right by 4 to get 0-15 range
   */
  if (priority < 0 || priority > 15)
    {
      return -EINVAL;
    }

#ifdef CONFIG_ARCH_IRQPRIO
  /* Use the architecture-specific priority function
   * up_prioritize_irq expects priority in the format used by NVIC
   * For Cortex-M, priority is in bits [7:4] of the priority byte,
   * so we need to shift left by 4
   */
  return up_prioritize_irq(icu_irq, priority << 4);
#else
  /* Priority control not enabled in configuration */
  return -ENOSYS;
#endif
}

/****************************************************************************
 * Name: ra_icu_filter_config
 *
 * Description:
 *   Configure ICU interrupt mode and filtering
 *
 * Input Parameters:
 *   icu_irq      - ICU IRQ number (0-15 for external interrupts)
 *   mode         - Interrupt detection mode
 *   filter_enable - Enable digital filter
 *   filter_clock - Filter clock selection
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_icu_filter_config(int icu_irq, uint8_t mode, bool filter_enable,
                  uint8_t filter_clock)
{
  uint32_t regval;

  /* Validate IRQ range */
#if defined(CONFIG_RA8E1_GROUP)
  if (icu_irq < 0 || icu_irq > 15)
#elif defined(CONFIG_RA8P1_GROUP)
  if (icu_irq < 0 || icu_irq > 31)
#endif
    {
      return -EINVAL;
    }

  /* NOTE: Do NOT write to IELSR here!
   * IELSR slots are dynamically allocated by ra_icu_attach().
   * The icu_irq parameter here is the external IRQ number (0-31),
   * which is used to select the IRQCR register, NOT the IELSR slot.
   * The IELSR event link is configured separately in ra_icu_attach().
   */

  /* Set interrupt detection mode */
#if defined(CONFIG_RA8E1_GROUP)
  /* RA8E1 uses simple IRQCR register */
  regval = (mode & R_ICU_IRQCR_IRQMD_MASK) << R_ICU_IRQCR_IRQMD_SHIFT;

  /* Set filter configuration if enabled */
  if (filter_enable)
    {
      regval |= R_ICU_IRQCR_FLTEN;
      regval |= (filter_clock & R_ICU_IRQCR_FCLKSEL_MASK) << R_ICU_IRQCR_FCLKSEL_SHIFT;
    }

  /* Write to the IRQCR register */
  putreg8(regval, R_ICU_IRQCR(icu_irq));

#elif defined(CONFIG_RA8P1_GROUP)
  /* RA8P1 has two IRQ control register banks */
  if (icu_irq <= 15)
    {
      /* Use IRQCRA for IRQ0-IRQ15 */
      regval = (mode & R_ICU_IRQCRA_IRQMD_MASK) << R_ICU_IRQCRA_IRQMD_SHIFT;

      /* Set filter configuration if enabled */
      if (filter_enable)
        {
          regval |= R_ICU_IRQCRA_FLTEN;
          regval |= (filter_clock & R_ICU_IRQCRA_FCLKSEL_MASK) << R_ICU_IRQCRA_FCLKSEL_SHIFT;
        }

      /* Write to the IRQCRA register */
      putreg8(regval, R_ICU_IRQCRA(icu_irq));
    }
  else
    {
      /* Use IRQCRB for IRQ16-IRQ31 */
      regval = (mode & R_ICU_IRQCRB_IRQMD_MASK) << R_ICU_IRQCRB_IRQMD_SHIFT;

      /* Set filter configuration if enabled */
      if (filter_enable)
        {
          regval |= R_ICU_IRQCRB_FLTEN;
          regval |= (filter_clock & R_ICU_IRQCRB_FCLKSEL_MASK) << R_ICU_IRQCRB_FCLKSEL_SHIFT;
        }

      /* Write to the IRQCRB register */
      putreg8(regval, R_ICU_IRQCRB(icu_irq - 16));
    }
#endif

  return OK;
}

/****************************************************************************
 * Name: ra_icu_enable_wakeup
 *
 * Description:
 *   Enable wakeup for specific ICU interrupts
 *
 ****************************************************************************/

void ra_icu_enable_wakeup(uint32_t mask)
{
  modifyreg32(R_ICU_WUPEN0, 0, mask);
}

/****************************************************************************
 * Name: ra_icu_disable_wakeup
 *
 * Description:
 *   Disable wakeup for specific ICU interrupts
 *
 ****************************************************************************/

void ra_icu_disable_wakeup(uint32_t mask)
{
  modifyreg32(R_ICU_WUPEN0, mask, 0);
}

/****************************************************************************
 * Name: ra_icu_clear_nmi_status
 *
 * Description:
 *   Clear NMI status flags
 *
 ****************************************************************************/

void ra_icu_clear_nmi_status(uint16_t mask)
{
  putreg16(mask, R_ICU_NMICLR);
}

/****************************************************************************
 * Name: ra_icu_get_nmi_status
 *
 * Description:
 *   Get NMI status flags
 *
 ****************************************************************************/

uint16_t ra_icu_get_nmi_status(void)
{
  return getreg16(R_ICU_NMISR);
}

/****************************************************************************
 * Name: ra_icu_enable_nmi
 *
 * Description:
 *   Enable NMI interrupts
 *
 ****************************************************************************/

void ra_icu_enable_nmi(uint16_t mask)
{
  modifyreg16(R_ICU_NMIER, 0, mask);
}

/****************************************************************************
 * Name: ra_icu_disable_nmi
 *
 * Description:
 *   Disable NMI interrupts
 *
 ****************************************************************************/

void ra_icu_disable_nmi(uint16_t mask)
{
  modifyreg16(R_ICU_NMIER, mask, 0);
}

/****************************************************************************
 * Name: ra_icu_enable_dtc
 *
 * Description:
 *   Enable DTC trigger for a specific ICU IRQ
 *
 ****************************************************************************/

void ra_icu_enable_dtc(int icu_irq)
{
  int slot;
  uint32_t regval;

  /* Validate IRQ range */
  if (icu_irq < RA_IRQ_FIRST || icu_irq >= (RA_IRQ_FIRST + RA_IRQ_IELSR_SIZE))
    {
      return;
    }

  slot = icu_irq - RA_IRQ_FIRST;

  /* Set DTCE bit in IELSRn register using hardware macro */
  regval = getreg32(R_ICU_IELSR(slot));
  regval |= R_ICU_IELSR_DTCE;  /* DTCE bit */
  putreg32(regval, R_ICU_IELSR(slot));
}

/****************************************************************************
 * Name: ra_icu_disable_dtc
 *
 * Description:
 *   Disable DTC trigger for a specific ICU IRQ
 *
 ****************************************************************************/

void ra_icu_disable_dtc(int icu_irq)
{
  int slot;
  uint32_t regval;

  /* Validate IRQ range */
  if (icu_irq < RA_IRQ_FIRST || icu_irq >= (RA_IRQ_FIRST + RA_IRQ_IELSR_SIZE))
    {
      return;
    }

  slot = icu_irq - RA_IRQ_FIRST;

  /* Clear DTCE bit in IELSRn register using hardware macro */
  regval = getreg32(R_ICU_IELSR(slot));
  regval &= ~R_ICU_IELSR_DTCE;  /* Clear DTCE bit */
  putreg32(regval, R_ICU_IELSR(slot));
}

/****************************************************************************
 * Name: ra_icu_enable_dmac
 *
 * Description:
 *   Configure DELSR register to enable DMAC activation by ELC event.
 *   This maps an ELC event number directly to a DMAC channel's activation
 *   source. The ELC event number specifies which peripheral event will
 *   trigger DMA transfers on the specified channel.
 *
 * Inputs:
 *   elc_event - ELC event number (from ELC event table, e.g., SCI0_TXI, etc.)
 *   dmac_ch   - DMAC channel number (0-7) to configure activation for
 *
 ****************************************************************************/

void ra_icu_enable_dmac(int elc_event, int dmac_ch)
{
  uint32_t regval;
  uint8_t local_ch;

  /* Validate DMAC channel:
   * - Unit 0: channels 0-7 are valid
   * - Unit 1: channels 10-17 are valid
   * - Channels 8-9 do not exist (hardware gap)
   */

  if (!DMAC_IS_VALID_CHANNEL(dmac_ch))
    {
      _err("Invalid DMAC channel: %d (valid: 0-7, 10-17)\n", dmac_ch);
      return;
    }

  /* Validate ELC event range */

  if (elc_event < 0 || elc_event > RA_ELC_EVENT_MAX)
    {
      _err("Invalid ELC event: %d (valid: 0-%d)\n", elc_event,
             RA_ELC_EVENT_MAX);
      return;
    }

  /* Extract unit and local channel */
  local_ch = DMAC_GET_LOCAL_CH(dmac_ch);
#if defined(CONFIG_RA8E1_GROUP)
  /* RA8E1: Use R_DMA->DELSR based on DMA0 */
  regval = getreg32(R_DMA_DELSR_UNIT(0, local_ch));
  regval &= ~R_DMA_DELSR_DELS_MASK;
  regval |= (elc_event & R_DMA_DELSR_DELS_MASK);
  putreg32(regval, R_DMA_DELSR_UNIT(0, local_ch));
#elif defined(CONFIG_RA8P1_GROUP)
  /* RA8P1: Use R_ICU->DELSR (shared between units) */
  regval = getreg32(R_ICU_DELSR(local_ch));
  regval &= ~R_ICU_DELSR_DELS_MASK;
  regval |= (elc_event & R_ICU_DELSR_DELS_MASK);
  putreg32(regval, R_ICU_DELSR(local_ch));
#else
#  error "Unsupported RA8 chip for DMAC DELSR"
#endif
}

/****************************************************************************
 * Name: ra_icu_disable_dmac
 *
 * Description:
 *   Disable DMAC event trigger by clearing the DELSR register.
 *   Sets DELSR[dmac_ch].DELS = 0 to disable DMA activation.
 *
 * Inputs:
 *   elc_event - ELC event number (unused, kept for API symmetry)
 *   dmac_ch   - DMAC channel number (0-7) to disable
 *
 ****************************************************************************/

void ra_icu_disable_dmac(int elc_event, int dmac_ch)
{
  uint32_t regval;
  uint8_t local_ch;

  UNUSED(elc_event);

  /* Validate DMAC channel */

  if (!DMAC_IS_VALID_CHANNEL(dmac_ch))
    {
      return;
    }

  /* Extract unit and local channel */
  local_ch = DMAC_GET_LOCAL_CH(dmac_ch);
#if defined(CONFIG_RA8E1_GROUP)
  regval = getreg32(R_DMA_DELSR_UNIT(0, local_ch));
  regval &= ~R_DMA_DELSR_DELS_MASK;
  putreg32(regval, R_DMA_DELSR_UNIT(0, local_ch));
#elif defined(CONFIG_RA8P1_GROUP)
  regval = getreg32(R_ICU_DELSR(local_ch));
  regval &= ~R_ICU_DELSR_DELS_MASK;
  putreg32(regval, R_ICU_DELSR(local_ch));
#endif
}


void ra_icu_clear_dmac_status(int dmac_ch)
{
  uint32_t regval;
  uint8_t local_ch;

  /* Validate DMAC channel */
  if (!DMAC_IS_VALID_CHANNEL(dmac_ch))
    {
      return;
    }

  /* Extract local channel */
  local_ch = DMAC_GET_LOCAL_CH(dmac_ch);
  /* Clear IR flag (write 0 to clear) */
#if defined(CONFIG_RA8E1_GROUP)
  regval = getreg32(R_DMA_DELSR_UNIT(0, local_ch));
  regval &= ~R_DMA_DELSR_IR;
  putreg32(regval, R_DMA_DELSR_UNIT(0, local_ch));
#elif defined(CONFIG_RA8P1_GROUP)
  regval = getreg32(R_ICU_DELSR(local_ch));
  regval &= ~R_ICU_DELSR_IR;
  putreg32(regval, R_ICU_DELSR(local_ch));
#endif
}

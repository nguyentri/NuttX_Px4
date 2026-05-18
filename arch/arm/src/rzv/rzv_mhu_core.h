/****************************************************************************
 * arch/arm/src/rzv/rzv_mhu_core.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Thin, policy-free MHU register helpers for RZ/V2H.
 * Shared by all IPC paths (rptun and raw IPCC).
 * Include rzv_ipc_channels.h first if you need base/channel constants.
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_SRC_RZV_RZV_MHU_CORE_H
#define __ARCH_ARM_SRC_RZV_RZV_MHU_CORE_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <nuttx/irq.h>

#include "hardware/rzv_mhu.h"

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_mhu_reg
 *
 * Description:
 *   Compute the MMIO address of a register within an MHU channel slot.
 *
 * Input Parameters:
 *   base    - MHU window base address (e.g. RZV_MHU0_NS_BASE)
 *   channel - Channel number (0-based)
 *   offset  - Register offset within the channel slot (e.g. RZV_MHU_MSG_SET_OFF)
 *
 * Returned Value:
 *   Physical register address as uintptr_t.
 *
 ****************************************************************************/

static inline uintptr_t rzv_mhu_reg(uintptr_t base, uint32_t channel,
                                     uint32_t offset)
{
  return base + (uintptr_t)(channel * RZV_MHU_CH_STRIDE) + offset;
}

/****************************************************************************
 * Name: rzv_mhu_send
 *
 * Description:
 *   Write a doorbell value to the MSG_SET register of a channel, triggering
 *   an interrupt on the receiving end.  DSB ensures the write is visible
 *   to the MHU hardware before this function returns.
 *
 * Input Parameters:
 *   base    - MHU window base address
 *   channel - TX channel number
 *   val     - Doorbell value (typically 1)
 *
 ****************************************************************************/

void rzv_mhu_send(uintptr_t base, uint32_t channel, uint32_t val);

/****************************************************************************
 * Name: rzv_mhu_ack
 *
 * Description:
 *   Write a response doorbell value to the RSP_SET register (signals
 *   the original sender that the message was consumed).
 *
 ****************************************************************************/

void rzv_mhu_ack(uintptr_t base, uint32_t channel, uint32_t val);

/****************************************************************************
 * Name: rzv_mhu_clear
 *
 * Description:
 *   Clear the MSG interrupt status on a channel (call from RX ISR after
 *   reading the doorbell, before returning from interrupt).
 *
 ****************************************************************************/

void rzv_mhu_clear(uintptr_t base, uint32_t channel);

/****************************************************************************
 * Name: rzv_mhu_rsp_clear
 *
 * Description:
 *   Clear the RSP interrupt status on a channel (call from TX-ACK ISR).
 *
 ****************************************************************************/

void rzv_mhu_rsp_clear(uintptr_t base, uint32_t channel);

/****************************************************************************
 * Name: rzv_mhu_msg_sts
 *
 * Description:
 *   Read the MSG interrupt status register for a channel.
 *
 * Returned Value:
 *   Raw register value; bit 0 set means doorbell is pending.
 *
 ****************************************************************************/

uint32_t rzv_mhu_msg_sts(uintptr_t base, uint32_t channel);

/****************************************************************************
 * Name: rzv_mhu_rsp_sts
 *
 * Description:
 *   Read the RSP interrupt status register for a channel.
 *
 ****************************************************************************/

uint32_t rzv_mhu_rsp_sts(uintptr_t base, uint32_t channel);

/****************************************************************************
 * Name: rzv_mhu_attach_isr
 *
 * Description:
 *   Attach an interrupt handler to the given MHU IRQ and enable it.
 *   Thin wrapper over irq_attach() + up_enable_irq().
 *
 * Input Parameters:
 *   irq     - GIC SPI number (e.g. RZV_IPC_CR8CR8_RX_IRQ)
 *   handler - ISR function pointer (xcpt_t)
 *   arg     - Argument passed to handler
 *
 * Returned Value:
 *   OK on success; negated errno otherwise.
 *
 ****************************************************************************/

int rzv_mhu_attach_isr(int irq, xcpt_t handler, FAR void *arg);

#endif /* __ARCH_ARM_SRC_RZV_RZV_MHU_CORE_H */

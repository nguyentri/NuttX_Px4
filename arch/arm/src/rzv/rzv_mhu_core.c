/****************************************************************************
 * arch/arm/src/rzv/rzv_mhu_core.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Thin, policy-free MHU register helpers for RZ/V2H.
 * Shared by rptun (rzv_rproc.c) and raw IPCC (rzv_ipc_raw.c).
 * No OpenAMP dependency; no NuttX IPCC dependency.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <nuttx/irq.h>

#include "arm_internal.h"
#include "rzv_mhu_core.h"
#include "hardware/rzv_mhu.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_mhu_send
 ****************************************************************************/

void rzv_mhu_send(uintptr_t base, uint32_t channel, uint32_t val)
{
  /* DSB before write: ensure all prior memory accesses (e.g. ring payload
   * clean) are visible to hardware before the doorbell fires.
   */

  __asm__ __volatile__("dsb sy" : : : "memory");
  putreg32(val, rzv_mhu_reg(base, channel, RZV_MHU_MSG_SET_OFF));
}

/****************************************************************************
 * Name: rzv_mhu_ack
 ****************************************************************************/

void rzv_mhu_ack(uintptr_t base, uint32_t channel, uint32_t val)
{
  __asm__ __volatile__("dsb sy" : : : "memory");
  putreg32(val, rzv_mhu_reg(base, channel, RZV_MHU_RSP_SET_OFF));
}

/****************************************************************************
 * Name: rzv_mhu_clear
 ****************************************************************************/

void rzv_mhu_clear(uintptr_t base, uint32_t channel)
{
  putreg32(MHU_MSG_INT_CLRn_CLEAR,
           rzv_mhu_reg(base, channel, RZV_MHU_MSG_CLR_OFF));
  __asm__ __volatile__("dsb sy" : : : "memory");
}

/****************************************************************************
 * Name: rzv_mhu_rsp_clear
 ****************************************************************************/

void rzv_mhu_rsp_clear(uintptr_t base, uint32_t channel)
{
  putreg32(MHU_RSP_INT_CLRn_CLEAR,
           rzv_mhu_reg(base, channel, RZV_MHU_RSP_CLR_OFF));
  __asm__ __volatile__("dsb sy" : : : "memory");
}

/****************************************************************************
 * Name: rzv_mhu_msg_sts
 ****************************************************************************/

uint32_t rzv_mhu_msg_sts(uintptr_t base, uint32_t channel)
{
  return getreg32(rzv_mhu_reg(base, channel, RZV_MHU_MSG_STS_OFF));
}

/****************************************************************************
 * Name: rzv_mhu_rsp_sts
 ****************************************************************************/

uint32_t rzv_mhu_rsp_sts(uintptr_t base, uint32_t channel)
{
  return getreg32(rzv_mhu_reg(base, channel, RZV_MHU_RSP_STS_OFF));
}

/****************************************************************************
 * Name: rzv_mhu_attach_isr
 ****************************************************************************/

int rzv_mhu_attach_isr(int irq, xcpt_t handler, FAR void *arg)
{
  int ret;

  ret = irq_attach(irq, handler, arg);
  if (ret == OK)
    {
      up_enable_irq(irq);
    }

  return ret;
}

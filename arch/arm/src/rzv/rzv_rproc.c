/****************************************************************************
 * arch/arm/src/rzv/rzv_rproc.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Phase 02: bind MHU ISR → rptun notify (RPTUN_NOTIFY_ALL);
 *           remove unbacked shmem-inbox notifyid read (IPC-RPMSG-002,
 *           IPC-IRQ-001).
 *
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_OPENAMP

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

#include <nuttx/irq.h>
#include <nuttx/rptun/rptun.h>   /* RPTUN_NOTIFY_ALL */
#include <arch/irq.h>

#include "arm_internal.h"
#include "hardware/rzv_mhu.h"
#include "rzv_openamp.h"
#include "rzv_rproc.h"

/* Use the canonical IRQ number from rzv2h_irq.h when available.
 * Keep the local fallback as a compile-time safety net.
 * TODO(IPC-IRQ-005): remove local define once rzv2h_irq.h ships
 *                    RZV_IRQ_MHU_MSG3_NS.
 */

#ifndef RZV_IRQ_MHU_MSG3_NS
#  define RZV_IRQ_MHU_MSG3_NS 314
#endif

#define RZV_MHU_OPENAMP_CHANNEL      3u
#define RZV_MHU_CH_STRIDE            0x20u
#define RZV_MHU_MSG_STS_OFFSET       0x00u
#define RZV_MHU_MSG_SET_OFFSET       0x04u
#define RZV_MHU_MSG_CLR_OFFSET       0x08u
#define RZV_MHU_RSP_STS_OFFSET       0x10u
#define RZV_MHU_RSP_SET_OFFSET       0x14u
#define RZV_MHU_RSP_CLR_OFFSET       0x18u
#define RZV_MHU_NOTIFY_TIMEOUT       100000u

/* g_notify / g_notify_arg:
 * Written once at rptun registration time (thread context, dmb after store).
 * Read in ISR (handler mode, single 32-bit load — atomic on ARMv7-R).
 * Marked volatile to prevent the compiler hoisting the load out of the ISR.
 */

static volatile rptun_callback_t g_notify;
static volatile FAR void        *g_notify_arg;
static bool                      g_initialized;

static uintptr_t rzv_mhu_reg(uint32_t channel, uint32_t offset)
{
  return RZV_MHU0_BASE + channel * RZV_MHU_CH_STRIDE + offset;
}

/****************************************************************************
 * Name: rzv_rproc_interrupt
 *
 * Description:
 *   MHU MSG3_NS interrupt handler.  CA55 writes to MSG_SET to kick CR8.
 *   We clear the interrupt then deliver RPTUN_NOTIFY_ALL so the rptun
 *   worker scans both vrings regardless of which vqid CA55 intended.
 *
 *   Using RPTUN_NOTIFY_ALL is conservative but correct; a per-vqid
 *   decode requires knowing whether the MHU doorbell carries vqid in its
 *   data payload (see TODO below).
 *   TODO(IPC-RPMSG-002): if CA55 Linux driver encodes vqid in the MHU
 *   doorbell data register, read it here and pass the decoded value
 *   instead of RPTUN_NOTIFY_ALL.
 *
 ****************************************************************************/

static int rzv_rproc_interrupt(int irq, FAR void *context, FAR void *arg)
{
  rptun_callback_t notify;
  FAR void        *notify_arg;

  UNUSED(irq);
  UNUSED(context);
  UNUSED(arg);

  /* Check MSG_STS bit 0 — if not set, spurious interrupt */

  if ((getreg32(rzv_mhu_reg(RZV_MHU_OPENAMP_CHANNEL,
                            RZV_MHU_MSG_STS_OFFSET)) & 1u) == 0)
    {
      return OK;
    }

  /* Clear the interrupt.  DSB ensures the clear is visible to hardware
   * before we read g_notify (prevents re-entry on weakly-ordered paths).
   */

  putreg32(1u, rzv_mhu_reg(RZV_MHU_OPENAMP_CHANNEL,
                           RZV_MHU_MSG_CLR_OFFSET));
  __asm__ __volatile__("dsb sy" : : : "memory");

  /* Snapshot under volatile read — single 32-bit load, atomic on ARMv7-R */

  notify     = g_notify;
  notify_arg = (FAR void *)g_notify_arg;

  if (notify != NULL)
    {
      /* RPTUN_NOTIFY_ALL lets rptun dispatch to both vrings without
       * needing to decode a per-vqid value from the doorbell.
       */

      notify(notify_arg, RPTUN_NOTIFY_ALL);
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_rproc_initialize
 *
 * Description:
 *   Initialise resource table, attach and enable the MHU MSG3_NS IRQ.
 *   Idempotent — safe to call multiple times.
 *
 ****************************************************************************/

int rzv_rproc_initialize(void)
{
  int ret;

  if (g_initialized)
    {
      return OK;
    }

  rzv_openamp_resource_table_init();

  ret = irq_attach(RZV_IRQ_MHU_MSG3_NS, rzv_rproc_interrupt, NULL);
  if (ret < 0)
    {
      return ret;
    }

  up_enable_irq(RZV_IRQ_MHU_MSG3_NS);
  g_initialized = true;
  return OK;
}

/****************************************************************************
 * Name: rzv_rproc_register_callback
 *
 * Description:
 *   Install the rptun notify callback.  Called by rptun core via the
 *   register_callback op (phase 03).  DMB ensures the ISR sees the new
 *   pointer after this function returns.
 *
 ****************************************************************************/

int rzv_rproc_register_callback(rptun_callback_t callback, FAR void *arg)
{
  irqstate_t flags;

  /* NEW-MEDIUM-2 fix: protect both volatile stores atomically so that an
   * ISR racing a stop/restart never sees new g_notify with stale g_notify_arg
   * or vice versa.  A critical section is the minimal correct approach here
   * because both stores must appear as a single indivisible update to the ISR.
   * The DMB after the stores still ensures memory ordering on SMP paths.
   */

  flags        = enter_critical_section();
  g_notify     = callback;
  g_notify_arg = arg;
  leave_critical_section(flags);

  __asm__ __volatile__("dmb ish" : : : "memory");
  return OK;
}

/****************************************************************************
 * Name: rzv_rproc_notify
 *
 * Description:
 *   Kick CA55 via MHU RSP channel.  Called from the rptun notify op so
 *   CR8 can signal CA55 that a vring has been updated.
 *
 *   Writes notifyid to RSP shmem slot then sets RSP_SET bit 0.
 *   TODO(IPC-RPMSG-002): if CA55 does not read RSP shmem slot, remove
 *   the shmem write and rely solely on the doorbell bit.
 *
 ****************************************************************************/

int rzv_rproc_notify(uint32_t notifyid)
{
  uint32_t timeout = RZV_MHU_NOTIFY_TIMEOUT;

  if (!g_initialized)
    {
      return -ENODEV;
    }

  /* Wait for the previous response to be consumed by CA55 */

  while ((getreg32(rzv_mhu_reg(RZV_MHU_OPENAMP_CHANNEL,
                               RZV_MHU_RSP_STS_OFFSET)) & 1u) != 0)
    {
      if (timeout-- == 0)
        {
          return -EBUSY;
        }
    }

  __asm__ __volatile__("dsb sy" : : : "memory");
  putreg32(1u, rzv_mhu_reg(RZV_MHU_OPENAMP_CHANNEL,
                           RZV_MHU_RSP_SET_OFFSET));

  UNUSED(notifyid); /* vqid not encoded in doorbell for now */

  return OK;
}

#endif /* CONFIG_RZV_OPENAMP */

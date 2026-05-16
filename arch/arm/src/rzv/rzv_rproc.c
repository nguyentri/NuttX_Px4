/****************************************************************************
 * arch/arm/src/rzv/rzv_rproc.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_OPENAMP

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

#include <nuttx/irq.h>
#include <arch/irq.h>

#include "arm_internal.h"
#include "hardware/rzv_mhu.h"
#include "rzv_openamp.h"
#include "rzv_rproc.h"

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
#define RZV_MHU_SHMEM_CH_SIZE        0x08u
#define RZV_MHU_SHMEM_MSG_OFFSET     0x00u
#define RZV_MHU_SHMEM_RSP_OFFSET     0x04u
#define RZV_MHU_NOTIFY_TIMEOUT       100000u

static rzv_rproc_notify_t g_notify;
static FAR void *g_notify_arg;
static bool g_initialized;

static uintptr_t rzv_mhu_reg(uint32_t channel, uint32_t offset)
{
  return RZV_MHU0_BASE + channel * RZV_MHU_CH_STRIDE + offset;
}

static uintptr_t rzv_mhu_shmem(uint32_t channel, uint32_t offset)
{
  return RZV_OPENAMP_MHU_SHMEM_BASE + channel * RZV_MHU_SHMEM_CH_SIZE +
         offset;
}

static int rzv_rproc_interrupt(int irq, FAR void *context, FAR void *arg)
{
  uint32_t notifyid;

  UNUSED(irq);
  UNUSED(context);
  UNUSED(arg);

  if ((getreg32(rzv_mhu_reg(RZV_MHU_OPENAMP_CHANNEL,
                            RZV_MHU_MSG_STS_OFFSET)) & 1u) == 0)
    {
      return OK;
    }

  notifyid = getreg32(rzv_mhu_shmem(RZV_MHU_OPENAMP_CHANNEL,
                                    RZV_MHU_SHMEM_MSG_OFFSET));
  putreg32(1, rzv_mhu_reg(RZV_MHU_OPENAMP_CHANNEL,
                          RZV_MHU_MSG_CLR_OFFSET));
  __asm__ __volatile__ ("dsb sy" : : : "memory");

  if (g_notify != NULL)
    {
      g_notify(g_notify_arg, notifyid);
    }

  return OK;
}

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

int rzv_rproc_register_callback(rzv_rproc_notify_t callback, FAR void *arg)
{
  g_notify = callback;
  g_notify_arg = arg;
  return OK;
}

int rzv_rproc_notify(uint32_t notifyid)
{
  uint32_t timeout = RZV_MHU_NOTIFY_TIMEOUT;

  if (!g_initialized)
    {
      return -ENODEV;
    }

  while ((getreg32(rzv_mhu_reg(RZV_MHU_OPENAMP_CHANNEL,
                               RZV_MHU_RSP_STS_OFFSET)) & 1u) != 0)
    {
      if (timeout-- == 0)
        {
          return -EBUSY;
        }
    }

  putreg32(notifyid, rzv_mhu_shmem(RZV_MHU_OPENAMP_CHANNEL,
                                   RZV_MHU_SHMEM_RSP_OFFSET));
  __asm__ __volatile__ ("dsb sy" : : : "memory");
  putreg32(1, rzv_mhu_reg(RZV_MHU_OPENAMP_CHANNEL,
                          RZV_MHU_RSP_SET_OFFSET));

  return OK;
}

#endif /* CONFIG_RZV_OPENAMP */

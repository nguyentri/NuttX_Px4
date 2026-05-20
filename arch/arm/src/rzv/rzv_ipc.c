/****************************************************************************
 * arch/arm/src/rzv/rzv_ipc.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_OPENAMP

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>

#include <nuttx/rptun/rptun.h>

#include "rzv_openamp.h"
#include "rzv_ipc.h"
#include "rzv_rproc.h"

#ifdef CONFIG_RPTUN
struct rzv_rptun_dev_s
{
  struct rptun_dev_s dev;
};

static const struct rptun_addrenv_s g_rzv_rptun_addrenv[] =
{
  {
    RZV_OPENAMP_RESOURCE_TABLE_BASE,
    RZV_OPENAMP_RESOURCE_TABLE_BASE,
    (RZV_OPENAMP_RPMSG_MEM_BASE + RZV_OPENAMP_RPMSG_MEM_SIZE) -
      RZV_OPENAMP_RESOURCE_TABLE_BASE
  },
  {0, 0, 0}
};

static struct rptun_rsc_s g_rzv_rptun_resource =
{
  {
    1,
    2,
    {0, 0}
  },
  {
    offsetof(struct rptun_rsc_s, log_trace),
    offsetof(struct rptun_rsc_s, rpmsg_vdev)
  },
  {
    RSC_TRACE,
    0,
    0,
    0,
    "rzv-openamp"
  },
  {
    RSC_VDEV,
    RZV_OPENAMP_VIRTIO_ID_RPMSG,
    RZV_OPENAMP_NOTIFYID0,
    RZV_OPENAMP_RPMSG_FEATURES,
    0,
    sizeof(struct fw_rsc_config),
    0,
    RZV_OPENAMP_NUM_VRINGS,
    {0, 0}
  },
  {
    RZV_OPENAMP_VRING0_BASE0,
    RZV_OPENAMP_VRING_ALIGN,
    RZV_OPENAMP_RPMSG_NUM_BUFS,
    RZV_OPENAMP_NOTIFYID0,
    0
  },
  {
    RZV_OPENAMP_VRING1_BASE0,
    RZV_OPENAMP_VRING_ALIGN,
    RZV_OPENAMP_RPMSG_NUM_BUFS,
    RZV_OPENAMP_NOTIFYID0,
    0
  },
  {
    RZV_OPENAMP_RPMSG_BUFFER_SIZE,
    RZV_OPENAMP_RPMSG_BUFFER_SIZE,
    {0}
  }
};

static rptun_callback_t g_rzv_rptun_callback;
static FAR void *g_rzv_rptun_callback_arg;

static const char *rzv_rptun_get_cpuname(FAR struct rptun_dev_s *dev)
{
  return "ca55";
}

static const struct rptun_addrenv_s *
rzv_rptun_get_addrenv(FAR struct rptun_dev_s *dev)
{
  return g_rzv_rptun_addrenv;
}

static FAR struct rptun_rsc_s *
rzv_rptun_get_resource(FAR struct rptun_dev_s *dev)
{
  return &g_rzv_rptun_resource;
}

static bool rzv_rptun_is_autostart(FAR struct rptun_dev_s *dev)
{
  return true;
}

static bool rzv_rptun_is_master(FAR struct rptun_dev_s *dev)
{
  return false;
}

static int rzv_rptun_notify(FAR struct rptun_dev_s *dev, uint32_t vqid)
{
  return rzv_rproc_notify(vqid);
}

static void rzv_rptun_rproc_callback(FAR void *arg, uint32_t notifyid)
{
  if (g_rzv_rptun_callback != NULL)
    {
      g_rzv_rptun_callback(g_rzv_rptun_callback_arg, notifyid);
    }
}

static int rzv_rptun_register_callback(FAR struct rptun_dev_s *dev,
                                       rptun_callback_t callback,
                                       FAR void *arg)
{
  g_rzv_rptun_callback = callback;
  g_rzv_rptun_callback_arg = arg;

  return rzv_rproc_register_callback(callback != NULL ?
                                     rzv_rptun_rproc_callback : NULL,
                                     NULL);
}

static const struct rptun_ops_s g_rzv_rptun_ops =
{
  .get_cpuname       = rzv_rptun_get_cpuname,
  .get_addrenv       = rzv_rptun_get_addrenv,
  .get_resource      = rzv_rptun_get_resource,
  .is_autostart      = rzv_rptun_is_autostart,
  .is_master         = rzv_rptun_is_master,
  .notify            = rzv_rptun_notify,
  .register_callback = rzv_rptun_register_callback,
};

static struct rzv_rptun_dev_s g_rzv_rptun =
{
  {
    &g_rzv_rptun_ops
  }
};

static bool g_rzv_rptun_initialized;
#endif

int rzv_ipc_initialize(void)
{
  int ret;

  ret = rzv_rproc_initialize();
  if (ret < 0)
    {
      return ret;
    }

#ifdef CONFIG_RPTUN
  if (!g_rzv_rptun_initialized)
    {
      ret = rptun_initialize(&g_rzv_rptun.dev);
      if (ret < 0)
        {
          return ret;
        }

      g_rzv_rptun_initialized = true;
    }
#endif

  return OK;
}

#endif /* CONFIG_RZV_OPENAMP */

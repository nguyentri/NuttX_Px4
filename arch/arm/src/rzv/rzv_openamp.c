/****************************************************************************
 * arch/arm/src/rzv/rzv_openamp.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_OPENAMP

#include <string.h>

#include "rzv_openamp.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define RSC_RPROC_MEM 4u
#define RSC_VDEV      3u

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct rzv_rsc_table_s g_rzv_resource_init[2] =
{
  {
    1, RZV_OPENAMP_NUM_TABLE_ENTRIES, {0, 0},
    {
      offsetof(struct rzv_rsc_table_s, rproc_mem),
      offsetof(struct rzv_rsc_table_s, rpmsg_vdev)
    },
    {
      RSC_RPROC_MEM, RZV_OPENAMP_RPMSG_MEM_BASE,
      RZV_OPENAMP_RPMSG_MEM_BASE, RZV_OPENAMP_RPMSG_MEM_SIZE, 0
    },
    {
      RSC_VDEV, RZV_OPENAMP_VIRTIO_ID_RPMSG, RZV_OPENAMP_NOTIFYID0,
      RZV_OPENAMP_RPMSG_FEATURES, 0, 0, 0, RZV_OPENAMP_NUM_VRINGS, {0, 0}
    },
    {
      {RZV_OPENAMP_VRING0_BASE0, RZV_OPENAMP_VRING_ALIGN,
       RZV_OPENAMP_RPMSG_NUM_BUFS, 0, 0},
      {RZV_OPENAMP_VRING1_BASE0, RZV_OPENAMP_VRING_ALIGN,
       RZV_OPENAMP_RPMSG_NUM_BUFS, 0, 0}
    }
  },
  {
    1, RZV_OPENAMP_NUM_TABLE_ENTRIES, {0, 0},
    {
      offsetof(struct rzv_rsc_table_s, rproc_mem),
      offsetof(struct rzv_rsc_table_s, rpmsg_vdev)
    },
    {
      RSC_RPROC_MEM, RZV_OPENAMP_RPMSG_MEM_BASE,
      RZV_OPENAMP_RPMSG_MEM_BASE, RZV_OPENAMP_RPMSG_MEM_SIZE, 0
    },
    {
      RSC_VDEV, RZV_OPENAMP_VIRTIO_ID_RPMSG, RZV_OPENAMP_NOTIFYID1,
      RZV_OPENAMP_RPMSG_FEATURES, 0, 0, 0, RZV_OPENAMP_NUM_VRINGS, {0, 0}
    },
    {
      {RZV_OPENAMP_VRING0_BASE1, RZV_OPENAMP_VRING_ALIGN,
       RZV_OPENAMP_RPMSG_NUM_BUFS, 1, 0},
      {RZV_OPENAMP_VRING1_BASE1, RZV_OPENAMP_VRING_ALIGN,
       RZV_OPENAMP_RPMSG_NUM_BUFS, 1, 0}
    }
  }
};

static struct rzv_rsc_table_s g_rzv_resources[2]
  __attribute__((section(".resource_table"), aligned(4096)));

/****************************************************************************
 * Public Functions
 ****************************************************************************/

void rzv_openamp_resource_table_init(void)
{
  memcpy(g_rzv_resources, g_rzv_resource_init, sizeof(g_rzv_resources));
}

FAR struct rzv_rsc_table_s *rzv_openamp_get_resource_table(int index,
                                                           FAR size_t *len)
{
  if (index < 0 || index >= 2)
    {
      return NULL;
    }

  if (len != NULL)
    {
      *len = sizeof(g_rzv_resources[index]);
    }

  return &g_rzv_resources[index];
}

#endif /* CONFIG_RZV_OPENAMP */

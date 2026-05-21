/****************************************************************************
 * arch/arm/src/rzv/rzv_openamp.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_SRC_RZV_RZV_OPENAMP_H
#define __ARCH_ARM_SRC_RZV_RZV_OPENAMP_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stddef.h>
#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Resource table pinned at DDR0_CR8_0_START + 0x02f00000 = 0x42F00000 */

#define RZV_OPENAMP_RESOURCE_TABLE_BASE  0x42f00000u
#define RZV_OPENAMP_RESOURCE_TABLE_SIZE  0x00001000u

/* RPMSG shared memory region: 0x43000000 - 0x437FFFFF (8 MB) */

#define RZV_OPENAMP_RPMSG_MEM_BASE       0x43000000u
#define RZV_OPENAMP_RPMSG_MEM_SIZE       0x00800000u

/* Vring layout — stride 0x100000 (1 MB) avoids overlap.
 * TODO(IPC-MEM-001): confirm these match CA55 Linux remoteproc DT node.
 */

#define RZV_OPENAMP_VRING0_BASE          0x43000000u
#define RZV_OPENAMP_VRING1_BASE          0x43100000u  /* vring0 + 0x100000 */
#define RZV_OPENAMP_SHM_BASE             0x43200000u

_Static_assert(RZV_OPENAMP_VRING1_BASE - RZV_OPENAMP_VRING0_BASE >= 0x100000u,
               "IPC-MEM-002: vring0/vring1 overlap");
_Static_assert(RZV_OPENAMP_SHM_BASE >= RZV_OPENAMP_VRING1_BASE + 0x100000u,
               "IPC-MEM-002: vring1/shm overlap");

#define RZV_OPENAMP_VRING_ALIGN          0x100u
#define RZV_OPENAMP_RPMSG_NUM_BUFS       256u        /* power-of-two */
#define RZV_OPENAMP_RPMSG_BUFFER_SIZE    512u

#define RZV_OPENAMP_RPC_EPT_NAME         "rpmsg-service-0"
#define RZV_OPENAMP_UXRCE_EPT_NAME       "rpmsg-service-1"
#define RZV_OPENAMP_LOGGER_EPT_NAME      "rpmsg-logger-0"

#define RZV_OPENAMP_APP_EPT_ADDR         0x0u
#define RZV_OPENAMP_VIRTIO_ID_RPMSG      7u

/* VIRTIO_RPMSG_F_NS = bit 0 (name-service announcement) */

#define RZV_OPENAMP_RPMSG_FEATURES       (1U << 0)

#define RZV_OPENAMP_NUM_VRINGS           2u
#define RZV_OPENAMP_NUM_TABLE_ENTRIES    2u
#define RZV_OPENAMP_NOTIFYID_VDEV        0u
#define RZV_OPENAMP_NOTIFYID_VRING0      0u
#define RZV_OPENAMP_NOTIFYID_VRING1      1u

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

void rzv_openamp_resource_table_init(void);
int  rzv_openamp_initialize(void);

#endif /* __ARCH_ARM_SRC_RZV_RZV_OPENAMP_H */

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

#define RZV_OPENAMP_RESOURCE_TABLE_BASE  0x42f00000u
#define RZV_OPENAMP_RESOURCE_TABLE_SIZE  0x00001000u
#define RZV_OPENAMP_MHU_SHMEM_BASE       0x42f01000u
#define RZV_OPENAMP_MHU_SHMEM_SIZE       0x00001000u

#define RZV_OPENAMP_RPMSG_MEM_BASE       0x43000000u
#define RZV_OPENAMP_RPMSG_MEM_SIZE       0x00800000u
#define RZV_OPENAMP_VRING_REGION_SIZE    0x00100000u
#define RZV_OPENAMP_SHM_REGION_SIZE      0x00300000u

#define RZV_OPENAMP_VRING0_BASE0         0x43000000u
#define RZV_OPENAMP_VRING1_BASE0         0x43050000u
#define RZV_OPENAMP_SHM_BASE0            0x43200000u
#define RZV_OPENAMP_VRING0_BASE1         0x43100000u
#define RZV_OPENAMP_VRING1_BASE1         0x43150000u
#define RZV_OPENAMP_SHM_BASE1            0x43500000u

#define RZV_OPENAMP_VRING_ALIGN          0x100u
#define RZV_OPENAMP_RPMSG_NUM_BUFS       1024u
#define RZV_OPENAMP_RPMSG_BUFFER_SIZE    512u

#define RZV_OPENAMP_RPC_EPT_NAME         "rpmsg-service-0"
#define RZV_OPENAMP_UXRCE_EPT_NAME       "rpmsg-service-1"
#define RZV_OPENAMP_LOGGER_EPT_NAME      "rpmsg-logger-0"

#define RZV_OPENAMP_APP_EPT_ADDR         0x0u
#define RZV_OPENAMP_VIRTIO_ID_RPMSG      7u
#define RZV_OPENAMP_RPMSG_FEATURES       1u
#define RZV_OPENAMP_NUM_VRINGS           2u
#define RZV_OPENAMP_NUM_TABLE_ENTRIES    2u
#define RZV_OPENAMP_NOTIFYID0            0u
#define RZV_OPENAMP_NOTIFYID1            1u

/****************************************************************************
 * Public Types
 ****************************************************************************/

struct rzv_rsc_table_s
{
  uint32_t version;
  uint32_t num;
  uint32_t reserved[2];
  uint32_t offset[RZV_OPENAMP_NUM_TABLE_ENTRIES];

  struct
  {
    uint32_t type;
    uint32_t da;
    uint32_t pa;
    uint32_t len;
    uint32_t flags;
  } rproc_mem;

  struct
  {
    uint32_t type;
    uint32_t id;
    uint32_t notifyid;
    uint32_t dfeatures;
    uint32_t gfeatures;
    uint32_t config_len;
    uint8_t  status;
    uint8_t  num_of_vrings;
    uint8_t  reserved[2];
  } rpmsg_vdev;

  struct
  {
    uint32_t da;
    uint32_t align;
    uint32_t num;
    uint32_t notifyid;
    uint32_t reserved;
  } rpmsg_vring[2];
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

void rzv_openamp_resource_table_init(void);
FAR struct rzv_rsc_table_s *rzv_openamp_get_resource_table(int index,
                                                           FAR size_t *len);

#endif /* __ARCH_ARM_SRC_RZV_RZV_OPENAMP_H */

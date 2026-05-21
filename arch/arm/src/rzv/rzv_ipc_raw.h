/****************************************************************************
 * arch/arm/src/rzv/rzv_ipc_raw.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Public interface for the RZ/V2H raw MHU+SHM IPCC lower-half driver.
 * Consumers: rzv2h_ipc.c (board layer, Phases 3–5).
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_SRC_RZV_RZV_IPC_RAW_H
#define __ARCH_ARM_SRC_RZV_RZV_IPC_RAW_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* Link descriptor — caller fills from rzv_ipc_channels.h constants and
 * passes a pointer to rzv_ipc_raw_register().  Must remain valid for the
 * lifetime of the device (typically a static const in rzv2h_ipc.c).
 */

struct rzv_ipc_link_desc
{
  /* MHU doorbell hardware */

  uintptr_t  mhu_base;       /* MHU window base (e.g. RZV_MHU0_NS_BASE)   */
  uint32_t   tx_chan;        /* MHU channel this side writes to             */
  uint32_t   rx_chan;        /* MHU channel this side receives on           */
  int        tx_irq;        /* GIC SPI for TX-ACK (RSP from peer)          */
  int        rx_irq;        /* GIC SPI for RX kick (MSG from peer)         */

  /* Shared memory ring */

  uintptr_t  shm_base;      /* Physical DDR base of shared ring memory      */
  uint32_t   shm_size;      /* Total SHM bytes (both directions combined)  */
  uint32_t   ring_entries;  /* Entries per direction (must be power of two) */
  uint32_t   entry_size;    /* Payload bytes per entry                      */

  /* Role */

  bool       initiator;     /* true: zero ring headers on first open        */

  /* Timeout */

  uint32_t   tx_ack_timeout_ms; /* TX-ACK wait limit; 0 = infinite         */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_ipc_raw_register
 *
 * Description:
 *   Instantiate a raw IPCC lower-half driver for one inter-core link and
 *   register it with the NuttX IPCC upper half as /dev/<path>.
 *
 *   Caller provides a fully populated rzv_ipc_link_desc.  The function
 *   allocates no dynamic memory; all state is embedded in a static pool
 *   indexed by invocation order.
 *
 * Input Parameters:
 *   path - Device path string (e.g. "/dev/ipcc1")
 *   desc - Link descriptor (must outlive the device registration)
 *
 * Returned Value:
 *   OK (0) on success; negated errno on failure.
 *   -ENOMEM if the static instance pool is exhausted.
 *   -EINVAL if desc fields fail validation.
 *
 ****************************************************************************/

int rzv_ipc_raw_register(FAR const char *path,
                          FAR const struct rzv_ipc_link_desc *desc);

#endif /* __ARCH_ARM_SRC_RZV_RZV_IPC_RAW_H */

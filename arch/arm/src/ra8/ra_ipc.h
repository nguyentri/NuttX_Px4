/****************************************************************************
 * arch/arm/src/ra8/ra_ipc.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_IPC_H
#define __ARCH_ARM_SRC_RA8_RA_IPC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>
#include <semaphore.h>

#ifndef __ASSEMBLY__

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* IPC Configuration */

#define RA_IPC_NUM_SEMAPHORES    16
#define RA_IPC_NUM_CHANNELS      4

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* IPC Semaphore handle structure */

struct ra_ipc_semaphore_s
{
  uint8_t semaphore_num;             /* Semaphore number (0-15) */
};

/* IPC NMI callback function type */

typedef void (*ra_ipc_nmi_cb_t)(void);

/* IPC Channel callback function type */

typedef void (*ra_ipc_ch_cb_t)(uint32_t channel, uint32_t data);

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: ra_ipc_initialize
 *
 * Description:
 *   Initialize the IPC subsystem. Must be called before any other IPC
 *   functions.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ipc_initialize(void);

/****************************************************************************
 * Name: ra_ipc_semaphore_take
 *
 * Description:
 *   Attempt to take (lock) an IPC semaphore. This function is non-blocking.
 *
 * Input Parameters:
 *   semaphore_num - Semaphore number (0-15)
 *
 * Returned Value:
 *   Zero (OK) if semaphore was successfully taken;
 *   -EBUSY if semaphore is already locked;
 *   -EINVAL if invalid semaphore number.
 *
 ****************************************************************************/

int ra_ipc_semaphore_take(uint8_t semaphore_num);

/****************************************************************************
 * Name: ra_ipc_semaphore_give
 *
 * Description:
 *   Give (unlock) an IPC semaphore.
 *
 * Input Parameters:
 *   semaphore_num - Semaphore number (0-15)
 *
 * Returned Value:
 *   Zero (OK) on success; -EINVAL if invalid semaphore number.
 *
 ****************************************************************************/

int ra_ipc_semaphore_give(uint8_t semaphore_num);

/****************************************************************************
 * Name: ra_ipc_nmi_enable
 *
 * Description:
 *   Enable NMI for the current core and register a callback function.
 *
 * Input Parameters:
 *   callback - Function to call when NMI is received from other core
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ipc_nmi_enable(ra_ipc_nmi_cb_t callback);

/****************************************************************************
 * Name: ra_ipc_nmi_request_set
 *
 * Description:
 *   Send an NMI request to the opposite core.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success.
 *
 ****************************************************************************/

int ra_ipc_nmi_request_set(void);

/****************************************************************************
 * Name: ra_ipc_channel_write
 *
 * Description:
 *   Write data to an IPC channel to send to the other core.
 *
 * Input Parameters:
 *   channel - Channel number (0-3)
 *   data    - 32-bit data to send
 *
 * Returned Value:
 *   Zero (OK) on success;
 *   -EBUSY if channel is full;
 *   -EINVAL if invalid channel number.
 *
 ****************************************************************************/

int ra_ipc_channel_write(uint8_t channel, uint32_t data);

/****************************************************************************
 * Name: ra_ipc_channel_read
 *
 * Description:
 *   Read data from an IPC channel received from the other core.
 *
 * Input Parameters:
 *   channel - Channel number (0-3)
 *   data    - Pointer to store received 32-bit data
 *
 * Returned Value:
 *   Zero (OK) on success;
 *   -EAGAIN if no data available;
 *   -EINVAL if invalid channel number or NULL pointer.
 *
 ****************************************************************************/

int ra_ipc_channel_read(uint8_t channel, uint32_t *data);

/****************************************************************************
 * Name: ra_ipc_channel_register
 *
 * Description:
 *   Register a callback function for an IPC channel. The callback will
 *   be invoked when data is received on the channel.
 *
 * Input Parameters:
 *   channel  - Channel number (0-3)
 *   callback - Function to call when data is received
 *
 * Returned Value:
 *   Zero (OK) on success; -EINVAL if invalid channel number.
 *
 ****************************************************************************/

int ra_ipc_channel_register(uint8_t channel, ra_ipc_ch_cb_t callback);

/****************************************************************************
 * Name: ra_ipc_channel_unregister
 *
 * Description:
 *   Unregister the callback function for an IPC channel.
 *
 * Input Parameters:
 *   channel - Channel number (0-3)
 *
 * Returned Value:
 *   Zero (OK) on success; -EINVAL if invalid channel number.
 *
 ****************************************************************************/

int ra_ipc_channel_unregister(uint8_t channel);

/****************************************************************************
 * Name: ra_ipc_channel_get_status
 *
 * Description:
 *   Get the status of an IPC channel.
 *
 * Input Parameters:
 *   channel - Channel number (0-3)
 *   status  - Pointer to store status register value
 *
 * Returned Value:
 *   Zero (OK) on success; -EINVAL if invalid parameters.
 *
 ****************************************************************************/

int ra_ipc_channel_get_status(uint8_t channel, uint32_t *status);

/****************************************************************************
 * Name: ra_ipc_channel_clear_errors
 *
 * Description:
 *   Clear error flags for an IPC channel.
 *
 * Input Parameters:
 *   channel - Channel number (0-3)
 *
 * Returned Value:
 *   Zero (OK) on success; -EINVAL if invalid channel number.
 *
 ****************************************************************************/

int ra_ipc_channel_clear_errors(uint8_t channel);

/****************************************************************************
 * Name: ra_ipc_channel_reset
 *
 * Description:
 *   Reset an IPC channel, clearing all pending data and errors.
 *
 * Input Parameters:
 *   channel - Channel number (0-3)
 *
 * Returned Value:
 *   Zero (OK) on success; -EINVAL if invalid channel number.
 *
 ****************************************************************************/

int ra_ipc_channel_reset(uint8_t channel);

/****************************************************************************
 * Name: ra_ipc_channel_is_enabled
 *
 * Description:
 *   Check if an IPC channel is enabled in the configuration.
 *
 * Input Parameters:
 *   channel - Channel number (0-3)
 *
 * Returned Value:
 *   true if enabled; false otherwise
 *
 ****************************************************************************/

bool ra_ipc_channel_is_enabled(uint8_t channel);

/****************************************************************************
 * Multi-Core Synchronization Primitives
 ****************************************************************************/

/* IPC Mutex - Hardware-backed mutual exclusion using IPC semaphores */

typedef struct
{
  uint8_t sem_num;                     /* Hardware semaphore number */
  uint8_t owner_core;                  /* Core ID that owns the lock */
  uint32_t lock_count;                 /* Recursive lock count */
} ra_ipc_mutex_t;

/****************************************************************************
 * Name: ra_ipc_mutex_init
 *
 * Description:
 *   Initialize an IPC mutex using a hardware semaphore.
 *
 * Input Parameters:
 *   mutex   - Pointer to mutex structure
 *   sem_num - Hardware semaphore number (0-15)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ipc_mutex_init(FAR ra_ipc_mutex_t *mutex, uint8_t sem_num);

/****************************************************************************
 * Name: ra_ipc_mutex_lock
 *
 * Description:
 *   Acquire an IPC mutex. Blocks until lock is obtained.
 *
 * Input Parameters:
 *   mutex - Pointer to mutex structure
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ipc_mutex_lock(FAR ra_ipc_mutex_t *mutex);

/****************************************************************************
 * Name: ra_ipc_mutex_trylock
 *
 * Description:
 *   Try to acquire an IPC mutex (non-blocking).
 *
 * Input Parameters:
 *   mutex - Pointer to mutex structure
 *
 * Returned Value:
 *   Zero (OK) if lock acquired; -EBUSY if already locked;
 *   other negated errno on failure.
 *
 ****************************************************************************/

int ra_ipc_mutex_trylock(FAR ra_ipc_mutex_t *mutex);

/****************************************************************************
 * Name: ra_ipc_mutex_unlock
 *
 * Description:
 *   Release an IPC mutex.
 *
 * Input Parameters:
 *   mutex - Pointer to mutex structure
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ipc_mutex_unlock(FAR ra_ipc_mutex_t *mutex);

/* IPC Event Flags - Inter-core event synchronization */

typedef uint32_t ra_ipc_eventflags_t;

/****************************************************************************
 * Name: ra_ipc_eventflags_wait
 *
 * Description:
 *   Wait for event flags on an IPC channel. Blocks until any specified
 *   flag is set or timeout expires.
 *
 * Input Parameters:
 *   channel  - IPC channel number (0-3)
 *   flags    - Flags to wait for (bitmask)
 *   received - Pointer to store received flags (can be NULL)
 *   timeout  - Timeout in ticks (0 = no timeout)
 *
 * Returned Value:
 *   Zero (OK) on success; -ETIMEDOUT on timeout; other negated errno on failure.
 *
 ****************************************************************************/

int ra_ipc_eventflags_wait(uint8_t channel, uint32_t flags,
                            FAR uint32_t *received, uint32_t timeout);

/****************************************************************************
 * Name: ra_ipc_eventflags_set
 *
 * Description:
 *   Set event flags on an IPC channel to notify the other core.
 *
 * Input Parameters:
 *   channel - IPC channel number (0-3)
 *   flags   - Flags to set (bitmask)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ipc_eventflags_set(uint8_t channel, uint32_t flags);

/****************************************************************************
 * Name: ra_ipc_eventflags_clear
 *
 * Description:
 *   Clear event flags on an IPC channel.
 *
 * Input Parameters:
 *   channel - IPC channel number (0-3)
 *   flags   - Flags to clear (bitmask)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ipc_eventflags_clear(uint8_t channel, uint32_t flags);

/* IPC Message Queue - FIFO-based message passing */

typedef struct
{
  uint8_t channel;                     /* IPC channel number */
  uint8_t msg_size;                    /* Message size in words */
  sem_t msgsem;                        /* Message available semaphore */
} ra_ipc_msgq_t;

/****************************************************************************
 * Name: ra_ipc_msgq_init
 *
 * Description:
 *   Initialize an IPC message queue using a channel's FIFO.
 *
 * Input Parameters:
 *   mq       - Pointer to message queue structure
 *   channel  - IPC channel number (0-3)
 *   msg_size - Message size in 32-bit words (1-4)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ipc_msgq_init(FAR ra_ipc_msgq_t *mq, uint8_t channel,
                     uint8_t msg_size);

/****************************************************************************
 * Name: ra_ipc_msgq_send
 *
 * Description:
 *   Send a message via IPC message queue. Blocks if queue is full.
 *
 * Input Parameters:
 *   mq  - Pointer to message queue structure
 *   msg - Pointer to message data
 *   len - Message length in bytes
 *
 * Returned Value:
 *   Number of bytes sent on success; a negated errno value on failure.
 *
 ****************************************************************************/

ssize_t ra_ipc_msgq_send(FAR ra_ipc_msgq_t *mq, FAR const void *msg,
                         size_t len);

/****************************************************************************
 * Name: ra_ipc_msgq_recv
 *
 * Description:
 *   Receive a message from IPC message queue. Blocks if queue is empty.
 *
 * Input Parameters:
 *   mq  - Pointer to message queue structure
 *   msg - Pointer to buffer for message data
 *   len - Buffer length in bytes
 *
 * Returned Value:
 *   Number of bytes received on success; a negated errno value on failure.
 *
 ****************************************************************************/

ssize_t ra_ipc_msgq_recv(FAR ra_ipc_msgq_t *mq, FAR void *msg, size_t len);

/****************************************************************************
 * Name: ra_ipc_msgq_destroy
 *
 * Description:
 *   Destroy an IPC message queue and release resources.
 *
 * Input Parameters:
 *   mq - Pointer to message queue structure
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ipc_msgq_destroy(FAR ra_ipc_msgq_t *mq);

/****************************************************************************
 * Shared Memory and Cache Management (for OpenAMP integration)
 ****************************************************************************/

/****************************************************************************
 * Name: ra_ipc_get_shmem
 *
 * Description:
 *   Get shared memory region information for OpenAMP/RPMsg.
 *
 * Input Parameters:
 *   paddr - Pointer to store physical address (can be NULL)
 *   vaddr - Pointer to store virtual address (can be NULL)
 *   size  - Pointer to store size in bytes (can be NULL)
 *
 * Returned Value:
 *   Zero (OK) on success.
 *
 ****************************************************************************/

int ra_ipc_get_shmem(FAR uintptr_t *paddr, FAR uintptr_t *vaddr,
                     FAR size_t *size);

/****************************************************************************
 * Name: ra_ipc_cache_clean
 *
 * Description:
 *   Clean (flush) data cache for shared memory region.
 *
 * Input Parameters:
 *   addr - Starting address
 *   size - Size in bytes
 *
 ****************************************************************************/

void ra_ipc_cache_clean(FAR void *addr, size_t size);

/****************************************************************************
 * Name: ra_ipc_cache_invalidate
 *
 * Description:
 *   Invalidate data cache for shared memory region.
 *
 * Input Parameters:
 *   addr - Starting address
 *   size - Size in bytes
 *
 ****************************************************************************/

void ra_ipc_cache_invalidate(FAR void *addr, size_t size);

/****************************************************************************
 * IPCC Upper-Half Integration
 ****************************************************************************/

#ifdef CONFIG_RA_IPC_IPCC

/****************************************************************************
 * Name: ra_ipcc_initialize
 *
 * Description:
 *   Initialize IPCC upper-half integration. Registers IPC channels with
 *   NuttX IPCC framework, creating /dev/ipccN character devices.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ipcc_initialize(void);

#endif /* CONFIG_RA_IPC_IPCC */

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RA8_RA_IPC_H */

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

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RA8_RA_IPC_H */

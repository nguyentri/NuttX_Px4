/****************************************************************************
 * arch/arm/src/ra8/ra_ipc.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <debug.h>
#include <string.h>

#include <nuttx/arch.h>
#include <nuttx/irq.h>
#include <nuttx/spinlock.h>

#include <arch/board/board.h>

#include "arm_internal.h"
#include "ra_ipc.h"
#include "ra_icu.h"
#include "hardware/ra_memorymap.h"

#ifdef CONFIG_RA_IPC

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Determine which core we're running on */

#ifndef BSP_CFG_CPU_CORE
#  define BSP_CFG_CPU_CORE 0
#endif

/* Core-specific register selection */

#if (BSP_CFG_CPU_CORE == 0)
#  define IPC_NMI_SET_REG              R_IPC_IPC1NMI_SET
#  define IPC_NMI_CLR_REG              R_IPC_IPC0NMI_CLR
#  define IPC_NMI_STA_REG              R_IPC_IPC0NMI_STA
#  define IPC_TX_BASE                  R_IPC_IPC0_OFFSET
#  define IPC_RX_BASE                  R_IPC_IPC1_OFFSET
#else
#  define IPC_NMI_SET_REG              R_IPC_IPC0NMI_SET
#  define IPC_NMI_CLR_REG              R_IPC_IPC1NMI_CLR
#  define IPC_NMI_STA_REG              R_IPC_IPC1NMI_STA
#  define IPC_TX_BASE                  R_IPC_IPC1_OFFSET
#  define IPC_RX_BASE                  R_IPC_IPC0_OFFSET
#endif

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* IPC driver state */

struct ra_ipc_state_s
{
  bool initialized;                    /* Driver initialized flag */
  ra_ipc_nmi_cb_t nmi_callback;        /* NMI callback function */
  ra_ipc_ch_cb_t ch_callbacks[RA_IPC_NUM_CHANNELS]; /* Channel callbacks */
  spinlock_t lock;                     /* Spinlock for atomic operations */
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

static struct ra_ipc_state_s g_ipc_state =
{
  .initialized = false,
  .nmi_callback = NULL,
  .ch_callbacks = { NULL },
  .lock = SP_UNLOCKED,
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_ipc_getreg32
 *
 * Description:
 *   Read a 32-bit IPC register
 *
 ****************************************************************************/

static inline uint32_t ra_ipc_getreg32(uintptr_t addr)
{
  return getreg32(addr);
}

/****************************************************************************
 * Name: ra_ipc_putreg32
 *
 * Description:
 *   Write a 32-bit IPC register
 *
 ****************************************************************************/

static inline void ra_ipc_putreg32(uint32_t val, uintptr_t addr)
{
  putreg32(val, addr);
}

/****************************************************************************
 * Name: ra_ipc_get_channel_base
 *
 * Description:
 *   Get the base address for a channel's registers
 *
 ****************************************************************************/

static uintptr_t ra_ipc_get_channel_base(uint8_t channel, bool is_tx)
{
  uintptr_t base;
  uint32_t ch_offset;

  /* Select TX or RX base */

  base = R_IPC_BASE + (is_tx ? IPC_TX_BASE : IPC_RX_BASE);

  /* Calculate channel offset (each channel is 0x20 bytes) */

  ch_offset = (channel % 2) ? RA_IPC_CH1_OFFSET : RA_IPC_CH0_OFFSET;

  return base + ch_offset;
}

/****************************************************************************
 * Name: ra_ipc_nmi_interrupt
 *
 * Description:
 *   IPC NMI interrupt handler
 *
 ****************************************************************************/

static int ra_ipc_nmi_interrupt(int irq, void *context, void *arg)
{
  irqstate_t flags;

  /* Clear the NMI request */

  ra_ipc_putreg32(IPC_IPCNMI_CLR_CLR, IPC_NMI_CLR_REG);

  /* Call user callback if registered */

  flags = spin_lock_irqsave(&g_ipc_state.lock);

  if (g_ipc_state.nmi_callback != NULL)
    {
      g_ipc_state.nmi_callback();
    }

  spin_unlock_irqrestore(&g_ipc_state.lock, flags);

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_channel_interrupt
 *
 * Description:
 *   IPC channel interrupt handler
 *
 ****************************************************************************/

static int ra_ipc_channel_interrupt(int irq, void *context, void *arg)
{
  uint8_t channel = (uint8_t)(uintptr_t)arg;
  uintptr_t base;
  uint32_t status;
  uint32_t data;
  irqstate_t flags;

  if (channel >= RA_IPC_NUM_CHANNELS)
    {
      return -EINVAL;
    }

  /* Get channel base address (RX side) */

  base = ra_ipc_get_channel_base(channel, false);

  /* Read status */

  status = ra_ipc_getreg32(base + RA_IPC_CH_STA_OFFSET);

  /* Check if data is ready */

  if (status & IPC_CH_STA_RDY)
    {
      /* Read data */

      data = ra_ipc_getreg32(base + RA_IPC_CH_RXD_OFFSET);

      /* Clear IRQ */

      ra_ipc_putreg32(IPC_CH_CLR_CLR, base + RA_IPC_CH_CLR_OFFSET);

      /* Call user callback if registered */

      flags = spin_lock_irqsave(&g_ipc_state.lock);

      if (g_ipc_state.ch_callbacks[channel] != NULL)
        {
          g_ipc_state.ch_callbacks[channel](channel, data);
        }

      spin_unlock_irqrestore(&g_ipc_state.lock, flags);
    }

  /* Check and clear errors */

  if (status & (IPC_CH_STA_RERR | IPC_CH_STA_FERR))
    {
      uint32_t clr_val = 0;

      if (status & IPC_CH_STA_RERR)
        {
          clr_val |= IPC_CH_CLR_RCLR;
          _err("IPC channel %d: Read error\n", channel);
        }

      if (status & IPC_CH_STA_FERR)
        {
          clr_val |= IPC_CH_CLR_FCLR;
          _err("IPC channel %d: FIFO error\n", channel);
        }

      ra_ipc_putreg32(clr_val, base + RA_IPC_CH_CLR_OFFSET);
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_ipc_initialize
 *
 * Description:
 *   Initialize the IPC subsystem
 *
 ****************************************************************************/

int ra_ipc_initialize(void)
{
  irqstate_t flags;
  int ret = OK;

  flags = spin_lock_irqsave(&g_ipc_state.lock);

  if (g_ipc_state.initialized)
    {
      spin_unlock_irqrestore(&g_ipc_state.lock, flags);
      return OK;
    }

  /* Initialize state */

  g_ipc_state.nmi_callback = NULL;
  memset(g_ipc_state.ch_callbacks, 0, sizeof(g_ipc_state.ch_callbacks));

  g_ipc_state.initialized = true;

  spin_unlock_irqrestore(&g_ipc_state.lock, flags);

  _info("IPC driver initialized for core %d\n", BSP_CFG_CPU_CORE);

  return ret;
}

/****************************************************************************
 * Name: ra_ipc_semaphore_take
 *
 * Description:
 *   Attempt to take an IPC semaphore
 *
 ****************************************************************************/

int ra_ipc_semaphore_take(uint8_t semaphore_num)
{
  uintptr_t addr;
  uint32_t val;

  if (semaphore_num >= RA_IPC_NUM_SEMAPHORES)
    {
      return -EINVAL;
    }

  addr = R_IPC_IPCSEM(semaphore_num);

  /* Try to take the semaphore */

  val = ra_ipc_getreg32(addr);

  if (val & IPC_IPCSEM_LOCK)
    {
      return -EBUSY;
    }

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_semaphore_give
 *
 * Description:
 *   Give an IPC semaphore
 *
 ****************************************************************************/

int ra_ipc_semaphore_give(uint8_t semaphore_num)
{
  uintptr_t addr;

  if (semaphore_num >= RA_IPC_NUM_SEMAPHORES)
    {
      return -EINVAL;
    }

  addr = R_IPC_IPCSEM(semaphore_num);

  /* Clear the semaphore */

  ra_ipc_putreg32(1, addr);

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_nmi_enable
 *
 * Description:
 *   Enable NMI for the current core
 *
 ****************************************************************************/

int ra_ipc_nmi_enable(ra_ipc_nmi_cb_t callback)
{
  irqstate_t flags;
  uint32_t regval;

  if (callback == NULL)
    {
      return -EINVAL;
    }

  flags = spin_lock_irqsave(&g_ipc_state.lock);

  g_ipc_state.nmi_callback = callback;

  spin_unlock_irqrestore(&g_ipc_state.lock, flags);

  /* Enable IPC NMI in ICU
   * Note: Actual IRQ attachment would be done via NuttX IRQ subsystem
   * This is simplified for basic functionality
   */

  regval = getreg32(R_ICU_NMIER);
  regval |= R_ICU_NMIER_IPCEN;
  putreg32(regval, R_ICU_NMIER);

  _info("IPC NMI enabled for core %d\n", BSP_CFG_CPU_CORE);

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_nmi_request_set
 *
 * Description:
 *   Send an NMI request to the opposite core
 *
 ****************************************************************************/

int ra_ipc_nmi_request_set(void)
{
  ra_ipc_putreg32(IPC_IPCNMI_SET_SET, IPC_NMI_SET_REG);
  return OK;
}

/****************************************************************************
 * Name: ra_ipc_channel_write
 *
 * Description:
 *   Write data to an IPC channel
 *
 ****************************************************************************/

int ra_ipc_channel_write(uint8_t channel, uint32_t data)
{
  uintptr_t base;
  uint32_t status;

  if (channel >= RA_IPC_NUM_CHANNELS)
    {
      return -EINVAL;
    }

  /* Get TX channel base */

  base = ra_ipc_get_channel_base(channel, true);

  /* Check if channel is full */

  status = ra_ipc_getreg32(base + RA_IPC_CH_STA_OFFSET);

  if (status & IPC_CH_STA_FULL)
    {
      return -EBUSY;
    }

  /* Write data */

  ra_ipc_putreg32(data, base + RA_IPC_CH_TXD_OFFSET);

  /* Set interrupt to notify other core */

  ra_ipc_putreg32(IPC_CH_SET_SET, base + RA_IPC_CH_SET_OFFSET);

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_channel_read
 *
 * Description:
 *   Read data from an IPC channel
 *
 ****************************************************************************/

int ra_ipc_channel_read(uint8_t channel, uint32_t *data)
{
  uintptr_t base;
  uint32_t status;

  if (channel >= RA_IPC_NUM_CHANNELS || data == NULL)
    {
      return -EINVAL;
    }

  /* Get RX channel base */

  base = ra_ipc_get_channel_base(channel, false);

  /* Check if data is ready */

  status = ra_ipc_getreg32(base + RA_IPC_CH_STA_OFFSET);

  if (!(status & IPC_CH_STA_RDY))
    {
      return -EAGAIN;
    }

  /* Read data */

  *data = ra_ipc_getreg32(base + RA_IPC_CH_RXD_OFFSET);

  /* Clear IRQ */

  ra_ipc_putreg32(IPC_CH_CLR_CLR, base + RA_IPC_CH_CLR_OFFSET);

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_channel_register
 *
 * Description:
 *   Register a callback for an IPC channel
 *
 ****************************************************************************/

int ra_ipc_channel_register(uint8_t channel, ra_ipc_ch_cb_t callback)
{
  irqstate_t flags;

  if (channel >= RA_IPC_NUM_CHANNELS)
    {
      return -EINVAL;
    }

  flags = spin_lock_irqsave(&g_ipc_state.lock);

  g_ipc_state.ch_callbacks[channel] = callback;

  spin_unlock_irqrestore(&g_ipc_state.lock, flags);

  /* Note: Actual IRQ attachment would be configured here
   * This is simplified for basic functionality
   */

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_channel_unregister
 *
 * Description:
 *   Unregister a callback for an IPC channel
 *
 ****************************************************************************/

int ra_ipc_channel_unregister(uint8_t channel)
{
  irqstate_t flags;

  if (channel >= RA_IPC_NUM_CHANNELS)
    {
      return -EINVAL;
    }

  flags = spin_lock_irqsave(&g_ipc_state.lock);

  g_ipc_state.ch_callbacks[channel] = NULL;

  spin_unlock_irqrestore(&g_ipc_state.lock, flags);

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_channel_get_status
 *
 * Description:
 *   Get the status of an IPC channel
 *
 ****************************************************************************/

int ra_ipc_channel_get_status(uint8_t channel, uint32_t *status)
{
  uintptr_t base;

  if (channel >= RA_IPC_NUM_CHANNELS || status == NULL)
    {
      return -EINVAL;
    }

  /* Get RX channel base */

  base = ra_ipc_get_channel_base(channel, false);

  *status = ra_ipc_getreg32(base + RA_IPC_CH_STA_OFFSET);

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_channel_clear_errors
 *
 * Description:
 *   Clear error flags for an IPC channel
 *
 ****************************************************************************/

int ra_ipc_channel_clear_errors(uint8_t channel)
{
  uintptr_t base;
  uint32_t clr_val;

  if (channel >= RA_IPC_NUM_CHANNELS)
    {
      return -EINVAL;
    }

  /* Get RX channel base */

  base = ra_ipc_get_channel_base(channel, false);

  /* Clear all error flags */

  clr_val = IPC_CH_CLR_RCLR | IPC_CH_CLR_FCLR;
  ra_ipc_putreg32(clr_val, base + RA_IPC_CH_CLR_OFFSET);

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_channel_reset
 *
 * Description:
 *   Reset an IPC channel
 *
 ****************************************************************************/

int ra_ipc_channel_reset(uint8_t channel)
{
  uintptr_t base;

  if (channel >= RA_IPC_NUM_CHANNELS)
    {
      return -EINVAL;
    }

  /* Get RX channel base */

  base = ra_ipc_get_channel_base(channel, false);

  /* Reset channel */

  ra_ipc_putreg32(IPC_CH_CLR_RST, base + RA_IPC_CH_CLR_OFFSET);

  return OK;
}

#endif /* CONFIG_RA_IPC */

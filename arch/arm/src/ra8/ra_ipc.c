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

#ifndef CONFIG_RA_CPU_CORE
#  define CONFIG_RA_CPU_CORE 0
#endif

/* IPC0NMI is Core1 -> Core0, IPC1NMI is Core0 -> Core1 (matches FSP) */

#if (CONFIG_RA_CPU_CORE == 0)
#  define IPC_NMI_SET_REG              R_IPC_IPC1NMI_SET  /* Core0 sets Core1's NMI */
#  define IPC_NMI_CLR_REG              R_IPC_IPC0NMI_CLR  /* Core0 clears own NMI */
#  define IPC_NMI_STA_REG              R_IPC_IPC0NMI_STA  /* Core0 reads own status */
#  define IPC_TX_BASE                  R_IPC_IPC0_OFFSET  /* Core0 TX via IPC0 */
#  define IPC_RX_BASE                  R_IPC_IPC1_OFFSET  /* Core0 RX via IPC1 */
#else
#  define IPC_NMI_SET_REG              R_IPC_IPC0NMI_SET  /* Core1 sets Core0's NMI */
#  define IPC_NMI_CLR_REG              R_IPC_IPC1NMI_CLR  /* Core1 clears own NMI */
#  define IPC_NMI_STA_REG              R_IPC_IPC1NMI_STA  /* Core1 reads own status */
#  define IPC_TX_BASE                  R_IPC_IPC1_OFFSET  /* Core1 TX via IPC1 */
#  define IPC_RX_BASE                  R_IPC_IPC0_OFFSET  /* Core1 RX via IPC0 */
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
  int ch_irqs[RA_IPC_NUM_CHANNELS];    /* Channel IRQ numbers */
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
  .ch_irqs = { -1, -1, -1, -1 },
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
 *   IPC NMI interrupt handler (matches FSP ipc_nmi_internal_callback)
 *
 ****************************************************************************/

static int ra_ipc_nmi_interrupt(int irq, void *context, void *arg)
{
  irqstate_t flags;

  /* Clear the NMI request (matches FSP: R_IPC->BSP_IPC_PRV_NMI_REG_CLEAR.CLR = 1) */

  ra_ipc_putreg32(IPC_IPCNMI_CLR_CLR, IPC_NMI_CLR_REG);

  /* Call user callback if registered (matches FSP pattern) */

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
 *   Note: IPC peripheral does not require MSTP enable (always-on system
 *   peripheral, verified from FSP reference code)
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

  /* Initialize IRQ tracking to invalid */

  for (int i = 0; i < RA_IPC_NUM_CHANNELS; i++)
    {
      g_ipc_state.ch_irqs[i] = -1;
    }

  g_ipc_state.initialized = true;

  spin_unlock_irqrestore(&g_ipc_state.lock, flags);

  _info("IPC driver initialized for core %d\n", CONFIG_RA_CPU_CORE);

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
 *   Enable NMI for the current core (matches FSP R_BSP_IpcNmiEnable)
 *
 ****************************************************************************/

int ra_ipc_nmi_enable(ra_ipc_nmi_cb_t callback)
{
  irqstate_t flags;
  uint32_t regval;
  int ret;

  if (callback == NULL)
    {
      return -EINVAL;
    }

  flags = spin_lock_irqsave(&g_ipc_state.lock);

  g_ipc_state.nmi_callback = callback;

  spin_unlock_irqrestore(&g_ipc_state.lock, flags);

  /* Enable IPC NMI in ICU (matches FSP: R_ICU->NMIER = R_ICU_NMIER_IPCEN_Msk)
   * NMI uses special Group IRQ mechanism in ICU, not standard IELSR routing
   * Attach NMI handler - NMI is exception vector 2 on Cortex-M
   */

  ret = irq_attach(RA_IRQ_NMI, ra_ipc_nmi_interrupt, NULL);
  if (ret < 0)
    {
      _err("Failed to attach NMI handler: %d\n", ret);
      return ret;
    }

  /* Set IPCEN bit to enable NMI. NMIER bits cannot be cleared after reset,
   * so no need to read-modify-write (matches FSP comment)
   */

  regval = R_ICU_NMIER_IPCEN;
  putreg32(regval, R_ICU_NMIER);

  /* Enable NMI exception */

  up_enable_irq(RA_IRQ_NMI);

  _info("IPC NMI enabled for core %d\n", CONFIG_RA_CPU_CORE);

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
 *   Register a callback for an IPC channel with dynamic IRQ allocation
 *   Uses ra_icu_attach() for proper ELC event-to-IRQ routing
 *
 ****************************************************************************/

int ra_ipc_channel_register(uint8_t channel, ra_ipc_ch_cb_t callback)
{
  irqstate_t flags;
  int irq;
  uint32_t elc_event;

  if (channel >= RA_IPC_NUM_CHANNELS)
    {
      return -EINVAL;
    }

  /* Determine ELC event for this channel
   * RA8P1 has 2 IPC interrupt events:
   * - RA_ELC_IPC_IRQ0 (0x05B) for IPC0 (channels 0-1)
   * - RA_ELC_IPC_IRQ1 (0x05C) for IPC1 (channels 2-3)
   */

  if (channel < 2)
    {
      elc_event = RA_ELC_IPC_IRQ0;
    }
  else
    {
      elc_event = RA_ELC_IPC_IRQ1;
    }

  /* Dynamically allocate IRQ via ICU and link to ELC event */

  irq = ra_icu_attach(elc_event,
                      ra_ipc_channel_interrupt,
                      (void *)(uintptr_t)channel,
                      true);  /* Enable IRQ immediately */

  if (irq < 0)
    {
      _err("Failed to attach IPC channel %d IRQ: %d\n", channel, irq);
      return irq;
    }

  flags = spin_lock_irqsave(&g_ipc_state.lock);

  g_ipc_state.ch_callbacks[channel] = callback;
  g_ipc_state.ch_irqs[channel] = irq;

  spin_unlock_irqrestore(&g_ipc_state.lock, flags);

  _info("IPC channel %d registered with IRQ %d (ELC 0x%03x)\n",
        channel, irq, elc_event);

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_channel_unregister
 *
 * Description:
 *   Unregister a callback for an IPC channel and detach IRQ
 *
 ****************************************************************************/

int ra_ipc_channel_unregister(uint8_t channel)
{
  irqstate_t flags;
  int irq;
  int ret = OK;

  if (channel >= RA_IPC_NUM_CHANNELS)
    {
      return -EINVAL;
    }

  flags = spin_lock_irqsave(&g_ipc_state.lock);

  irq = g_ipc_state.ch_irqs[channel];
  g_ipc_state.ch_callbacks[channel] = NULL;
  g_ipc_state.ch_irqs[channel] = -1;

  spin_unlock_irqrestore(&g_ipc_state.lock, flags);

  /* Detach IRQ if it was allocated */

  if (irq >= 0)
    {
      ret = ra_icu_detach(irq);
      if (ret < 0)
        {
          _err("Failed to detach IPC channel %d IRQ %d: %d\n",
               channel, irq, ret);
        }
    }

  return ret;
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

/****************************************************************************
 * Name: ra_ipc_channel_is_enabled
 *
 * Description:
 *   Check if an IPC channel is enabled in the configuration
 *
 ****************************************************************************/

bool ra_ipc_channel_is_enabled(uint8_t channel)
{
  if (channel >= RA_IPC_NUM_CHANNELS)
    {
      return false;
    }

  /* Check Kconfig settings for channel enable flags */

#ifdef CONFIG_RA_IPC_CH0_ENABLE
  if (channel == 0) return true;
#endif
#ifdef CONFIG_RA_IPC_CH1_ENABLE
  if (channel == 1) return true;
#endif
#ifdef CONFIG_RA_IPC_CH2_ENABLE
  if (channel == 2) return true;
#endif
#ifdef CONFIG_RA_IPC_CH3_ENABLE
  if (channel == 3) return true;
#endif

  return false;
}

/****************************************************************************
 * Multi-Core Synchronization Primitives
 ****************************************************************************/

/****************************************************************************
 * Name: ra_ipc_mutex_init
 *
 * Description:
 *   Initialize an IPC mutex using a hardware semaphore
 *
 ****************************************************************************/

int ra_ipc_mutex_init(FAR ra_ipc_mutex_t *mutex, uint8_t sem_num)
{
  if (mutex == NULL || sem_num >= RA_IPC_NUM_SEMAPHORES)
    {
      return -EINVAL;
    }

  mutex->sem_num = sem_num;
  mutex->owner_core = 0xFF;  /* No owner */
  mutex->lock_count = 0;

  /* Ensure semaphore starts unlocked */

  ra_ipc_semaphore_give(sem_num);

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_mutex_lock
 *
 * Description:
 *   Acquire an IPC mutex (blocking)
 *
 ****************************************************************************/

int ra_ipc_mutex_lock(FAR ra_ipc_mutex_t *mutex)
{
  int ret;

  if (mutex == NULL)
    {
      return -EINVAL;
    }

  /* Spin until we acquire the hardware semaphore */

  while (true)
    {
      ret = ra_ipc_semaphore_take(mutex->sem_num);
      if (ret == OK)
        {
          /* Successfully acquired lock */

          mutex->owner_core = CONFIG_RA_CPU_CORE;
          mutex->lock_count++;
          return OK;
        }
      else if (ret == -EBUSY)
        {
          /* Lock held by other core, yield and retry */

          up_udelay(1);  /* Brief delay to reduce contention */
          continue;
        }
      else
        {
          /* Error occurred */

          return ret;
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_mutex_trylock
 *
 * Description:
 *   Try to acquire an IPC mutex (non-blocking)
 *
 ****************************************************************************/

int ra_ipc_mutex_trylock(FAR ra_ipc_mutex_t *mutex)
{
  int ret;

  if (mutex == NULL)
    {
      return -EINVAL;
    }

  ret = ra_ipc_semaphore_take(mutex->sem_num);
  if (ret == OK)
    {
      mutex->owner_core = CONFIG_RA_CPU_CORE;
      mutex->lock_count++;
    }

  return ret;
}

/****************************************************************************
 * Name: ra_ipc_mutex_unlock
 *
 * Description:
 *   Release an IPC mutex
 *
 ****************************************************************************/

int ra_ipc_mutex_unlock(FAR ra_ipc_mutex_t *mutex)
{
  if (mutex == NULL)
    {
      return -EINVAL;
    }

  if (mutex->lock_count == 0)
    {
      return -EPERM;  /* Not locked */
    }

  mutex->lock_count--;
  if (mutex->lock_count == 0)
    {
      mutex->owner_core = 0xFF;
      return ra_ipc_semaphore_give(mutex->sem_num);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_eventflags_wait
 *
 * Description:
 *   Wait for event flags on an IPC channel
 *
 ****************************************************************************/

int ra_ipc_eventflags_wait(uint8_t channel, uint32_t flags,
                            FAR uint32_t *received, uint32_t timeout)
{
  uint32_t status;
  uint32_t start_time = 0;
  uint32_t elapsed;
  int ret;

  if (channel >= RA_IPC_NUM_CHANNELS)
    {
      return -EINVAL;
    }

  if (timeout > 0)
    {
      start_time = clock_systime_ticks();
    }

  /* Poll channel status for requested flags */

  while (true)
    {
      ret = ra_ipc_channel_get_status(channel, &status);
      if (ret < 0)
        {
          return ret;
        }

      /* Check if any requested flags are set */

      if (status & flags)
        {
          if (received != NULL)
            {
              *received = status & flags;
            }

          return OK;
        }

      /* Check timeout */

      if (timeout > 0)
        {
          elapsed = clock_systime_ticks() - start_time;
          if (elapsed >= timeout)
            {
              return -ETIMEDOUT;
            }
        }

      /* Brief delay before retry */

      up_udelay(10);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_eventflags_set
 *
 * Description:
 *   Set event flags on an IPC channel
 *
 ****************************************************************************/

int ra_ipc_eventflags_set(uint8_t channel, uint32_t flags)
{
  uintptr_t base;
  uint32_t set_val;

  if (channel >= RA_IPC_NUM_CHANNELS)
    {
      return -EINVAL;
    }

  /* Get TX channel base */

  base = ra_ipc_get_channel_base(channel, true);

  /* Set flags using channel SET register */

  set_val = flags & 0xFF;  /* Use lower 8 bits for IRQ flags */
  ra_ipc_putreg32(set_val, base + RA_IPC_CH_SET_OFFSET);

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_eventflags_clear
 *
 * Description:
 *   Clear event flags on an IPC channel
 *
 ****************************************************************************/

int ra_ipc_eventflags_clear(uint8_t channel, uint32_t flags)
{
  uintptr_t base;
  uint32_t clr_val;

  if (channel >= RA_IPC_NUM_CHANNELS)
    {
      return -EINVAL;
    }

  /* Get RX channel base */

  base = ra_ipc_get_channel_base(channel, false);

  /* Clear flags using channel CLR register */

  clr_val = flags & 0xFF;  /* Use lower 8 bits for IRQ flags */
  ra_ipc_putreg32(clr_val, base + RA_IPC_CH_CLR_OFFSET);

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_msgq_init
 *
 * Description:
 *   Initialize an IPC message queue
 *
 ****************************************************************************/

int ra_ipc_msgq_init(FAR ra_ipc_msgq_t *mq, uint8_t channel,
                     uint8_t msg_size)
{
  if (mq == NULL || channel >= RA_IPC_NUM_CHANNELS)
    {
      return -EINVAL;
    }

  if (msg_size < 1 || msg_size > 4)
    {
      return -EINVAL;  /* FIFO depth is 4 words */
    }

  mq->channel = channel;
  mq->msg_size = msg_size;
  nxsem_init(&mq->msgsem, 0, 0);

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_msgq_send
 *
 * Description:
 *   Send a message via IPC message queue
 *
 ****************************************************************************/

ssize_t ra_ipc_msgq_send(FAR ra_ipc_msgq_t *mq, FAR const void *msg,
                         size_t len)
{
  FAR const uint32_t *words;
  size_t nwords;
  size_t i;
  int ret;

  if (mq == NULL || msg == NULL)
    {
      return -EINVAL;
    }

  /* Calculate number of words to send */

  nwords = (len + sizeof(uint32_t) - 1) / sizeof(uint32_t);
  if (nwords > mq->msg_size)
    {
      nwords = mq->msg_size;
    }

  words = (FAR const uint32_t *)msg;

  /* Send each word */

  for (i = 0; i < nwords; i++)
    {
      /* Wait if FIFO full */

      while ((ret = ra_ipc_channel_write(mq->channel, words[i])) == -EBUSY)
        {
          up_udelay(10);
        }

      if (ret < 0)
        {
          return ret;
        }
    }

  return nwords * sizeof(uint32_t);
}

/****************************************************************************
 * Name: ra_ipc_msgq_recv
 *
 * Description:
 *   Receive a message from IPC message queue
 *
 ****************************************************************************/

ssize_t ra_ipc_msgq_recv(FAR ra_ipc_msgq_t *mq, FAR void *msg, size_t len)
{
  FAR uint32_t *words;
  size_t nwords;
  size_t i;
  int ret;

  if (mq == NULL || msg == NULL)
    {
      return -EINVAL;
    }

  /* Calculate number of words to receive */

  nwords = (len + sizeof(uint32_t) - 1) / sizeof(uint32_t);
  if (nwords > mq->msg_size)
    {
      nwords = mq->msg_size;
    }

  words = (FAR uint32_t *)msg;

  /* Receive each word */

  for (i = 0; i < nwords; i++)
    {
      /* Wait for data if FIFO empty */

      while ((ret = ra_ipc_channel_read(mq->channel, &words[i])) < 0)
        {
          if (ret != -EAGAIN)
            {
              return ret;
            }

          up_udelay(10);
        }
    }

  return nwords * sizeof(uint32_t);
}

/****************************************************************************
 * Name: ra_ipc_msgq_destroy
 *
 * Description:
 *   Destroy an IPC message queue
 *
 ****************************************************************************/

int ra_ipc_msgq_destroy(FAR ra_ipc_msgq_t *mq)
{
  if (mq == NULL)
    {
      return -EINVAL;
    }

  nxsem_destroy(&mq->msgsem);

  return OK;
}

#endif /* CONFIG_RA_IPC */

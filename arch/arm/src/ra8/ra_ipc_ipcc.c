/****************************************************************************
 * arch/arm/src/ra8/ra_ipc_ipcc.c
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

#ifdef CONFIG_RA_IPC_IPCC

#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <debug.h>
#include <string.h>

#include <nuttx/arch.h>
#include <nuttx/ipcc.h>
#include <nuttx/mm/circbuf.h>
#include <nuttx/semaphore.h>

#include <arch/board/board.h>

#include "arm_internal.h"
#include "ra_ipc.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Shared memory configuration */

#ifndef CONFIG_RA_IPC_SHMEM_BASE
#  define CONFIG_RA_IPC_SHMEM_BASE    0x22050000  /* Shared RAM region */
#endif

#ifndef CONFIG_RA_IPC_SHMEM_SIZE
#  define CONFIG_RA_IPC_SHMEM_SIZE    0x00010000  /* 64KB */
#endif

/* Default buffer sizes if not configured */

#ifndef CONFIG_IPCC_RXBUFSIZE
#  define CONFIG_IPCC_RXBUFSIZE       1024
#endif

#ifndef CONFIG_IPCC_TXBUFSIZE
#  define CONFIG_IPCC_TXBUFSIZE       1024
#endif

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* IPCC lower-half driver state */

struct ra_ipcc_state_s
{
  struct ipcc_lower_s lower;           /* Lower-half interface */
  uint8_t channel;                     /* Hardware channel number */
  sem_t rxsem;                         /* RX data available semaphore */
  sem_t txsem;                         /* TX buffer available semaphore */
  bool initialized;                    /* Channel initialized flag */
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* IPCC lower-half instances (one per channel) */

static struct ra_ipcc_state_s g_ra_ipcc[RA_IPC_NUM_CHANNELS];

/* Shared memory pool for inter-core communication */

static uint8_t g_ipc_shmem[CONFIG_RA_IPC_SHMEM_SIZE]
  __attribute__((section(".ipc_shared"), aligned(32)));

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_ipcc_channel_callback
 *
 * Description:
 *   Callback invoked when hardware channel receives data
 *
 ****************************************************************************/

static void ra_ipcc_channel_callback(uint32_t channel, uint32_t data)
{
  FAR struct ra_ipcc_state_s *priv;

  if (channel >= RA_IPC_NUM_CHANNELS)
    {
      return;
    }

  priv = &g_ra_ipcc[channel];

  /* Notify upper half that data is available */

#ifdef CONFIG_IPCC_BUFFERED
  if (priv->lower.upper != NULL)
    {
      ipcc_rxfree_notify(priv->lower.upper);
    }
#endif

  /* Wake up any threads waiting for RX data */

  nxsem_post(&priv->rxsem);
}

/****************************************************************************
 * Name: ra_ipcc_read
 *
 * Description:
 *   Read data directly from IPC channel (non-blocking)
 *
 ****************************************************************************/

static ssize_t ra_ipcc_read(FAR struct ipcc_lower_s *ipcc,
                            FAR char *buffer, size_t buflen)
{
  FAR struct ra_ipcc_state_s *priv =
    (FAR struct ra_ipcc_state_s *)ipcc;
  uint32_t data;
  ssize_t nread = 0;
  int ret;

  if (buffer == NULL || buflen == 0)
    {
      return 0;
    }

  /* Read available 32-bit words from channel */

  while (buflen >= sizeof(uint32_t))
    {
      ret = ra_ipc_channel_read(priv->channel, &data);
      if (ret < 0)
        {
          /* No more data available */
          break;
        }

      memcpy(&buffer[nread], &data, sizeof(uint32_t));
      nread += sizeof(uint32_t);
      buflen -= sizeof(uint32_t);
    }

  return nread;
}

/****************************************************************************
 * Name: ra_ipcc_write
 *
 * Description:
 *   Write data directly to IPC channel (non-blocking)
 *
 ****************************************************************************/

static ssize_t ra_ipcc_write(FAR struct ipcc_lower_s *ipcc,
                             FAR const char *buffer, size_t buflen)
{
  FAR struct ra_ipcc_state_s *priv =
    (FAR struct ra_ipcc_state_s *)ipcc;
  uint32_t data;
  ssize_t nwritten = 0;
  int ret;

  if (buffer == NULL || buflen == 0)
    {
      return 0;
    }

  /* Write 32-bit words to channel */

  while (buflen >= sizeof(uint32_t))
    {
      memcpy(&data, &buffer[nwritten], sizeof(uint32_t));

      ret = ra_ipc_channel_write(priv->channel, data);
      if (ret < 0)
        {
          /* FIFO full, cannot write more */
          break;
        }

      nwritten += sizeof(uint32_t);
      buflen -= sizeof(uint32_t);
    }

  return nwritten;
}

#ifdef CONFIG_IPCC_BUFFERED
/****************************************************************************
 * Name: ra_ipcc_buffer_data
 *
 * Description:
 *   Copy data from IPC FIFO to circular buffer
 *
 ****************************************************************************/

static ssize_t ra_ipcc_buffer_data(FAR struct ipcc_lower_s *ipcc,
                                    FAR struct circbuf_s *rxbuf)
{
  FAR struct ra_ipcc_state_s *priv =
    (FAR struct ra_ipcc_state_s *)ipcc;
  uint32_t data;
  ssize_t buffered = 0;
  int ret;

  /* Keep reading until FIFO empty or buffer full */

  while (circbuf_space(rxbuf) >= sizeof(uint32_t))
    {
      ret = ra_ipc_channel_read(priv->channel, &data);
      if (ret < 0)
        {
          /* No more data available */
          break;
        }

      /* Write to circular buffer */

      ret = circbuf_write(rxbuf, (FAR const void *)&data, sizeof(uint32_t));
      if (ret < 0)
        {
          _err("Failed to write to rxbuf: %d\n", ret);
          break;
        }

      buffered += ret;

      /* Check for overflow */

      if (ret < sizeof(uint32_t))
        {
          priv->lower.overflow = 1;
          break;
        }
    }

  return buffered;
}

/****************************************************************************
 * Name: ra_ipcc_write_notify
 *
 * Description:
 *   Notification from upper half that data is available in TX buffer
 *
 ****************************************************************************/

static ssize_t ra_ipcc_write_notify(FAR struct ipcc_lower_s *ipcc)
{
  FAR struct ra_ipcc_state_s *priv =
    (FAR struct ra_ipcc_state_s *)ipcc;
  FAR struct circbuf_s *txbuf = &ipcc->txbuf;
  uint32_t data;
  ssize_t sent = 0;
  int ret;

  /* Transfer data from circular buffer to hardware FIFO */

  while (circbuf_used(txbuf) >= sizeof(uint32_t))
    {
      ret = circbuf_read(txbuf, (FAR void *)&data, sizeof(uint32_t));
      if (ret < 0)
        {
          break;
        }

      ret = ra_ipc_channel_write(priv->channel, data);
      if (ret < 0)
        {
          /* FIFO full, try again later */
          break;
        }

      sent += sizeof(uint32_t);
    }

  /* If we freed buffer space, notify upper half */

  if (sent > 0 && priv->lower.upper != NULL)
    {
      ipcc_txfree_notify(priv->lower.upper);
    }

  return sent;
}
#endif /* CONFIG_IPCC_BUFFERED */

/****************************************************************************
 * Name: ra_ipcc_cleanup
 *
 * Description:
 *   Cleanup IPCC channel resources
 *
 ****************************************************************************/

static int ra_ipcc_cleanup(FAR struct ipcc_lower_s *ipcc)
{
  FAR struct ra_ipcc_state_s *priv =
    (FAR struct ra_ipcc_state_s *)ipcc;

  if (!priv->initialized)
    {
      return OK;
    }

  /* Unregister channel callback */

  ra_ipc_channel_unregister(priv->channel);

  /* Destroy semaphores */

  nxsem_destroy(&priv->rxsem);
  nxsem_destroy(&priv->txsem);

  priv->initialized = false;

  return OK;
}

/****************************************************************************
 * Private Data - IPCC Operations Structure
 ****************************************************************************/

static const struct ipcc_ops_s g_ra_ipcc_ops =
{
  .read         = ra_ipcc_read,
  .write        = ra_ipcc_write,
#ifdef CONFIG_IPCC_BUFFERED
  .buffer_data  = ra_ipcc_buffer_data,
  .write_notify = ra_ipcc_write_notify,
#endif
  .cleanup      = ra_ipcc_cleanup,
};

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_ipcc_initialize
 *
 * Description:
 *   Initialize IPCC upper-half integration for RA8 IPC driver.
 *   This registers all available IPC channels with the NuttX IPCC
 *   framework, enabling /dev/ipccN character devices.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_ipcc_initialize(void)
{
  int ret;
  int i;

  /* Initialize lower-half IPC driver first */

  ret = ra_ipc_initialize();
  if (ret < 0)
    {
      _err("Failed to initialize IPC driver: %d\n", ret);
      return ret;
    }

  _info("Initializing IPCC upper-half integration\n");
  _info("Shared memory: base=0x%08x size=%u bytes\n",
        CONFIG_RA_IPC_SHMEM_BASE, CONFIG_RA_IPC_SHMEM_SIZE);

  /* Initialize each IPCC channel */

  for (i = 0; i < RA_IPC_NUM_CHANNELS; i++)
    {
      FAR struct ra_ipcc_state_s *priv = &g_ra_ipcc[i];

      /* Skip disabled channels */

      if (!ra_ipc_channel_is_enabled(i))
        {
          continue;
        }

      memset(priv, 0, sizeof(struct ra_ipcc_state_s));

      priv->channel = i;
      priv->lower.ops = g_ra_ipcc_ops;
      priv->lower.chan = i;

      /* Initialize semaphores */

      nxsem_init(&priv->rxsem, 0, 0);
      nxsem_init(&priv->txsem, 0, 1);

      /* Register callback for hardware interrupts */

      ret = ra_ipc_channel_register(i, ra_ipcc_channel_callback);
      if (ret < 0)
        {
          _err("Failed to register channel %d callback: %d\n", i, ret);
          nxsem_destroy(&priv->rxsem);
          nxsem_destroy(&priv->txsem);
          continue;
        }

      /* Register with IPCC upper-half framework */

#ifdef CONFIG_IPCC_BUFFERED
      ret = ipcc_register(&priv->lower,
                         CONFIG_IPCC_RXBUFSIZE,
                         CONFIG_IPCC_TXBUFSIZE);
#else
      ret = ipcc_register(&priv->lower);
#endif

      if (ret < 0)
        {
          _err("Failed to register IPCC channel %d: %d\n", i, ret);
          ra_ipc_channel_unregister(i);
          nxsem_destroy(&priv->rxsem);
          nxsem_destroy(&priv->txsem);
          continue;
        }

      priv->initialized = true;
      _info("Registered IPCC channel %d as /dev/ipcc%d\n", i, i);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_get_shmem
 *
 * Description:
 *   Get shared memory region for OpenAMP/RPMsg usage
 *
 * Input Parameters:
 *   paddr - Pointer to store physical address (can be NULL)
 *   vaddr - Pointer to store virtual address (can be NULL)
 *   size - Pointer to store size (can be NULL)
 *
 * Returned Value:
 *   Zero (OK) on success
 *
 ****************************************************************************/

int ra_ipc_get_shmem(FAR uintptr_t *paddr, FAR uintptr_t *vaddr,
                     FAR size_t *size)
{
  if (paddr != NULL)
    {
      *paddr = (uintptr_t)g_ipc_shmem;
    }

  if (vaddr != NULL)
    {
      *vaddr = (uintptr_t)g_ipc_shmem;
    }

  if (size != NULL)
    {
      *size = CONFIG_RA_IPC_SHMEM_SIZE;
    }

  return OK;
}

/****************************************************************************
 * Name: ra_ipc_cache_clean
 *
 * Description:
 *   Clean (flush) cache for shared memory region
 *
 ****************************************************************************/

void ra_ipc_cache_clean(FAR void *addr, size_t size)
{
#ifdef CONFIG_ARMV8M_DCACHE
  /* For RA8P1 with data cache enabled */
  up_clean_dcache((uintptr_t)addr, (uintptr_t)addr + size);
#else
  /* No cache on this configuration */
  UNUSED(addr);
  UNUSED(size);
#endif
}

/****************************************************************************
 * Name: ra_ipc_cache_invalidate
 *
 * Description:
 *   Invalidate cache for shared memory region
 *
 ****************************************************************************/

void ra_ipc_cache_invalidate(FAR void *addr, size_t size)
{
#ifdef CONFIG_ARMV8M_DCACHE
  /* For RA8P1 with data cache enabled */
  up_invalidate_dcache((uintptr_t)addr, (uintptr_t)addr + size);
#else
  /* No cache on this configuration */
  UNUSED(addr);
  UNUSED(size);
#endif
}

#endif /* CONFIG_RA_IPC_IPCC */

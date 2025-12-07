/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_ipc_test.c
 *
 * IPC Test Application for RA8P1 Dual-Core Communication
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

#ifdef CONFIG_RA8P1_IPC_TEST

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <nuttx/arch.h>
#include "ra_ipc.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define IPC_TEST_CHANNEL       0
#define IPC_TEST_SEMAPHORE     0
#define IPC_TEST_ITERATIONS    100

/****************************************************************************
 * Private Data
 ****************************************************************************/

static volatile uint32_t g_rx_count = 0;
static volatile uint32_t g_last_data = 0;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ipc_test_rx_callback
 *
 * Description:
 *   Callback for receiving IPC channel data
 *
 ****************************************************************************/

static void ipc_test_rx_callback(uint32_t channel, uint32_t data)
{
  g_rx_count++;
  g_last_data = data;

  printf("[CPU%d] RX: channel=%lu data=0x%08lx count=%lu\n",
         CONFIG_RA_CPU_CORE, channel, data, g_rx_count);
}

/****************************************************************************
 * Name: test_semaphore
 *
 * Description:
 *   Test hardware semaphore operations
 *
 ****************************************************************************/

static int test_semaphore(void)
{
  int ret;
  int i;

  printf("\n=== Testing Hardware Semaphores ===\n");

  for (i = 0; i < 10; i++)
    {
      /* Try to take semaphore */

      ret = ra_ipc_semaphore_take(IPC_TEST_SEMAPHORE);
      if (ret == OK)
        {
          printf("[CPU%d] Semaphore %d acquired (iteration %d)\n",
                 CONFIG_RA_CPU_CORE, IPC_TEST_SEMAPHORE, i);

          /* Hold for a moment */

          up_udelay(1000);

          /* Release semaphore */

          ret = ra_ipc_semaphore_give(IPC_TEST_SEMAPHORE);
          if (ret < 0)
            {
              printf("[CPU%d] Failed to release semaphore: %d\n",
                     CONFIG_RA_CPU_CORE, ret);
              return ret;
            }

          printf("[CPU%d] Semaphore %d released\n",
                 CONFIG_RA_CPU_CORE, IPC_TEST_SEMAPHORE);
        }
      else if (ret == -EBUSY)
        {
          printf("[CPU%d] Semaphore %d busy (held by other core)\n",
                 CONFIG_RA_CPU_CORE, IPC_TEST_SEMAPHORE);
        }
      else
        {
          printf("[CPU%d] Semaphore operation failed: %d\n",
                 CONFIG_RA_CPU_CORE, ret);
          return ret;
        }

      up_udelay(10000); /* 10ms delay between iterations */
    }

  return OK;
}

/****************************************************************************
 * Name: test_channel_loopback
 *
 * Description:
 *   Test channel communication with loopback
 *
 ****************************************************************************/

static int test_channel_loopback(void)
{
  int ret;
  int i;
  uint32_t data_out;
  uint32_t data_in;

  printf("\n=== Testing Channel Loopback ===\n");

  for (i = 0; i < 10; i++)
    {
      data_out = 0xDEAD0000 | (CONFIG_RA_CPU_CORE << 8) | i;

      /* Write data */

      ret = ra_ipc_channel_write(IPC_TEST_CHANNEL, data_out);
      if (ret < 0)
        {
          printf("[CPU%d] Channel write failed: %d\n",
                 CONFIG_RA_CPU_CORE, ret);
          continue;
        }

      printf("[CPU%d] TX: 0x%08lx\n", CONFIG_RA_CPU_CORE, data_out);

      /* Small delay */

      up_udelay(1000);

      /* Try to read data (from other core) */

      ret = ra_ipc_channel_read(IPC_TEST_CHANNEL, &data_in);
      if (ret == OK)
        {
          printf("[CPU%d] RX: 0x%08lx\n", CONFIG_RA_CPU_CORE, data_in);
        }
      else if (ret == -EAGAIN)
        {
          printf("[CPU%d] No data available\n", CONFIG_RA_CPU_CORE);
        }

      up_udelay(50000); /* 50ms delay */
    }

  return OK;
}

/****************************************************************************
 * Name: test_channel_interrupt
 *
 * Description:
 *   Test interrupt-driven channel communication
 *
 ****************************************************************************/

static int test_channel_interrupt(void)
{
  int ret;
  int i;
  uint32_t data;

  printf("\n=== Testing Interrupt-Driven Channels ===\n");

  /* Register callback */

  ret = ra_ipc_channel_register(IPC_TEST_CHANNEL, ipc_test_rx_callback);
  if (ret < 0)
    {
      printf("[CPU%d] Failed to register callback: %d\n",
             CONFIG_RA_CPU_CORE, ret);
      return ret;
    }

  printf("[CPU%d] Callback registered for channel %d\n",
         CONFIG_RA_CPU_CORE, IPC_TEST_CHANNEL);

  /* Send messages */

  for (i = 0; i < IPC_TEST_ITERATIONS; i++)
    {
      data = 0xCAFE0000 | (CONFIG_RA_CPU_CORE << 8) | i;

      ret = ra_ipc_channel_write(IPC_TEST_CHANNEL, data);
      if (ret < 0)
        {
          printf("[CPU%d] TX failed: %d\n", CONFIG_RA_CPU_CORE, ret);
        }
      else
        {
          printf("[CPU%d] TX[%d]: 0x%08lx\n",
                 CONFIG_RA_CPU_CORE, i, data);
        }

      up_mdelay(100); /* 100ms between messages */
    }

  /* Wait for remaining callbacks */

  printf("[CPU%d] Waiting for callbacks (received %lu)...\n",
         CONFIG_RA_CPU_CORE, g_rx_count);
  sleep(2);

  printf("[CPU%d] Final RX count: %lu\n", CONFIG_RA_CPU_CORE, g_rx_count);

  /* Unregister callback */

  ra_ipc_channel_unregister(IPC_TEST_CHANNEL);

  return OK;
}

/****************************************************************************
 * Name: test_mutex
 *
 * Description:
 *   Test IPC mutex operations
 *
 ****************************************************************************/

static int test_mutex(void)
{
  ra_ipc_mutex_t mutex;
  int ret;
  int i;

  printf("\n=== Testing IPC Mutex ===\n");

  /* Initialize mutex */

  ret = ra_ipc_mutex_init(&mutex, IPC_TEST_SEMAPHORE);
  if (ret < 0)
    {
      printf("[CPU%d] Mutex init failed: %d\n", CONFIG_RA_CPU_CORE, ret);
      return ret;
    }

  printf("[CPU%d] Mutex initialized\n", CONFIG_RA_CPU_CORE);

  for (i = 0; i < 10; i++)
    {
      /* Try to acquire mutex */

      ret = ra_ipc_mutex_trylock(&mutex);
      if (ret == OK)
        {
          printf("[CPU%d] Mutex acquired (iteration %d)\n",
                 CONFIG_RA_CPU_CORE, i);

          /* Critical section simulation */

          up_udelay(5000);

          /* Release mutex */

          ret = ra_ipc_mutex_unlock(&mutex);
          if (ret < 0)
            {
              printf("[CPU%d] Mutex unlock failed: %d\n",
                     CONFIG_RA_CPU_CORE, ret);
              return ret;
            }

          printf("[CPU%d] Mutex released\n", CONFIG_RA_CPU_CORE);
        }
      else if (ret == -EBUSY)
        {
          printf("[CPU%d] Mutex busy (held by other core)\n",
                 CONFIG_RA_CPU_CORE);
        }

      up_udelay(20000); /* 20ms between iterations */
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra8p1_ipc_test
 *
 * Description:
 *   Main IPC test application
 *
 ****************************************************************************/

int ra8p1_ipc_test(int argc, char *argv[])
{
  int ret;

  printf("\n");
  printf("========================================\n");
  printf("RA8P1 IPC Test Application\n");
  printf("CPU Core: %d (%s)\n", CONFIG_RA_CPU_CORE,
         CONFIG_RA_CPU_CORE == 0 ? "CM85" : "CM33");
  printf("========================================\n");

  /* Test 1: Hardware Semaphores */

  ret = test_semaphore();
  if (ret < 0)
    {
      printf("Semaphore test failed: %d\n", ret);
    }

  /* Test 2: Channel Loopback */

  ret = test_channel_loopback();
  if (ret < 0)
    {
      printf("Channel loopback test failed: %d\n", ret);
    }

  /* Test 3: Interrupt-Driven Channels */

  ret = test_channel_interrupt();
  if (ret < 0)
    {
      printf("Interrupt channel test failed: %d\n", ret);
    }

  /* Test 4: IPC Mutex */

  ret = test_mutex();
  if (ret < 0)
    {
      printf("Mutex test failed: %d\n", ret);
    }

  printf("\n");
  printf("========================================\n");
  printf("IPC Test Complete\n");
  printf("CPU Core: %d\n", CONFIG_RA_CPU_CORE);
  printf("========================================\n");

  return OK;
}

#endif /* CONFIG_RA8P1_IPC_TEST */

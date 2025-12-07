/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_ipc.c
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
#include <syslog.h>
#include <debug.h>

#include <nuttx/board.h>

#include "ra_ipc.h"
#include "evk-ra8p1.h"

#ifdef CONFIG_RA_IPC

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Test Configuration */

#ifdef CONFIG_RA_IPC_TEST
#  define IPC_TEST_CHANNEL          0
#  define IPC_TEST_SEMAPHORE        0
#  define IPC_TEST_ITERATIONS       10
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

#ifdef CONFIG_RA_IPC_TEST
static volatile uint32_t g_ipc_test_count = 0;
static volatile uint32_t g_ipc_test_data = 0;
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

#ifdef CONFIG_RA_IPC_TEST

/****************************************************************************
 * Name: ipc_test_nmi_callback
 *
 * Description:
 *   NMI test callback function
 *
 ****************************************************************************/

static void ipc_test_nmi_callback(void)
{
  syslog(LOG_INFO, "IPC: NMI received from other core\n");
}

/****************************************************************************
 * Name: ipc_test_channel_callback
 *
 * Description:
 *   Channel test callback function
 *
 ****************************************************************************/

static void ipc_test_channel_callback(uint32_t channel, uint32_t data)
{
  g_ipc_test_count++;
  g_ipc_test_data = data;
  syslog(LOG_INFO, "IPC: Channel %u received data: 0x%08lx (count: %lu)\n",
         channel, data, g_ipc_test_count);
}

/****************************************************************************
 * Name: board_ipc_test
 *
 * Description:
 *   Run basic IPC functionality tests
 *
 ****************************************************************************/

static int board_ipc_test(void)
{
  int ret;
  uint32_t test_data = 0x12345678;
  uint32_t read_data;
  uint32_t status;
  int i;

  syslog(LOG_INFO, "IPC: Starting basic functionality test...\n");

  /* Test 1: Semaphore operations */

  syslog(LOG_INFO, "IPC: Test 1 - Semaphore operations\n");

  ret = ra_ipc_semaphore_take(IPC_TEST_SEMAPHORE);
  if (ret == OK)
    {
      syslog(LOG_INFO, "IPC: Semaphore %d taken successfully\n",
             IPC_TEST_SEMAPHORE);

      /* Try to take again (should fail with -EBUSY) */

      ret = ra_ipc_semaphore_take(IPC_TEST_SEMAPHORE);
      if (ret == -EBUSY)
        {
          syslog(LOG_INFO, "IPC: Semaphore correctly shows as busy\n");
        }
      else
        {
          syslog(LOG_ERR, "IPC: ERROR: Semaphore should be busy\n");
        }

      /* Give semaphore back */

      ret = ra_ipc_semaphore_give(IPC_TEST_SEMAPHORE);
      if (ret == OK)
        {
          syslog(LOG_INFO, "IPC: Semaphore %d released successfully\n",
                 IPC_TEST_SEMAPHORE);
        }
    }
  else
    {
      syslog(LOG_ERR, "IPC: ERROR: Failed to take semaphore: %d\n", ret);
    }

  /* Test 2: Channel status check */

  syslog(LOG_INFO, "IPC: Test 2 - Channel status\n");

  ret = ra_ipc_channel_get_status(IPC_TEST_CHANNEL, &status);
  if (ret == OK)
    {
      syslog(LOG_INFO, "IPC: Channel %d status: 0x%08lx\n",
             IPC_TEST_CHANNEL, status);
    }
  else
    {
      syslog(LOG_ERR, "IPC: ERROR: Failed to get channel status: %d\n",
             ret);
    }

  /* Test 3: Channel write/read (loopback if same core) */

  syslog(LOG_INFO, "IPC: Test 3 - Channel communication\n");

  for (i = 0; i < IPC_TEST_ITERATIONS; i++)
    {
      test_data = 0x10000000 + i;

      ret = ra_ipc_channel_write(IPC_TEST_CHANNEL, test_data);
      if (ret == OK)
        {
          syslog(LOG_INFO, "IPC: Sent data: 0x%08lx\n", test_data);
        }
      else if (ret == -EBUSY)
        {
          syslog(LOG_WARN, "IPC: Channel busy, waiting...\n");
          usleep(1000);
          i--;  /* Retry */
          continue;
        }
      else
        {
          syslog(LOG_ERR, "IPC: ERROR: Failed to write to channel: %d\n",
                 ret);
          break;
        }

      usleep(10000);  /* Wait 10ms */
    }

  /* Test 4: Register callback and enable interrupts */

  syslog(LOG_INFO, "IPC: Test 4 - Callback registration\n");

  ret = ra_ipc_channel_register(IPC_TEST_CHANNEL,
                                 ipc_test_channel_callback);
  if (ret == OK)
    {
      syslog(LOG_INFO, "IPC: Channel callback registered successfully\n");
    }
  else
    {
      syslog(LOG_ERR, "IPC: ERROR: Failed to register callback: %d\n",
             ret);
    }

  /* Test 5: NMI callback registration */

#ifdef CONFIG_RA_IPC_USE_NMI
  syslog(LOG_INFO, "IPC: Test 5 - NMI registration\n");

  ret = ra_ipc_nmi_enable(ipc_test_nmi_callback);
  if (ret == OK)
    {
      syslog(LOG_INFO, "IPC: NMI callback registered successfully\n");
    }
  else
    {
      syslog(LOG_ERR, "IPC: ERROR: Failed to register NMI callback: %d\n",
             ret);
    }
#endif

  syslog(LOG_INFO, "IPC: Basic functionality test completed\n");
  syslog(LOG_INFO, "IPC: Total messages received: %lu\n", g_ipc_test_count);

  return OK;
}
#endif /* CONFIG_RA_IPC_TEST */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_ipc_initialize
 *
 * Description:
 *   Initialize the IPC subsystem for the EVK-RA8P1 board
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int board_ipc_initialize(void)
{
  int ret;

  syslog(LOG_INFO, "IPC: Initializing Inter-Processor Communication...\n");

  /* Initialize the RA8 IPC driver */

  ret = ra_ipc_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "IPC: ERROR: Failed to initialize IPC driver: %d\n",
             ret);
      return ret;
    }

  syslog(LOG_INFO, "IPC: Driver initialized successfully\n");

#ifdef CONFIG_RA_IPC_TEST
  /* Run basic tests if enabled */

  ret = board_ipc_test();
  if (ret < 0)
    {
      syslog(LOG_ERR, "IPC: ERROR: Test failed: %d\n", ret);
      return ret;
    }
#endif

  /* Configure IPC channels based on configuration */

#ifdef CONFIG_RA_IPC_CH0_ENABLE
  syslog(LOG_INFO, "IPC: Channel 0 enabled\n");
#endif

#ifdef CONFIG_RA_IPC_CH1_ENABLE
  syslog(LOG_INFO, "IPC: Channel 1 enabled\n");
#endif

#ifdef CONFIG_RA_IPC_CH2_ENABLE
  syslog(LOG_INFO, "IPC: Channel 2 enabled\n");
#endif

#ifdef CONFIG_RA_IPC_CH3_ENABLE
  syslog(LOG_INFO, "IPC: Channel 3 enabled\n");
#endif

  syslog(LOG_INFO, "IPC: Board initialization complete\n");

  return OK;
}

#endif /* CONFIG_RA_IPC */

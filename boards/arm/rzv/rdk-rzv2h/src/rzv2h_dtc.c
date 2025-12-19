/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_dtc.c
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
#include <debug.h>
#include <errno.h>

#include <arch/board/board.h>

#include "rzv_dtc.h"
#include "rdk-rzv2h.h"

#ifdef CONFIG_RZV_DTC

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Example DTC transfer complete flag */

static volatile bool g_dtc_transfer_complete = false;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: dtc_transfer_callback
 *
 * Description:
 *   DTC transfer completion callback
 *
 ****************************************************************************/

static void dtc_transfer_callback(void *handle, int event, void *user_data)
{
  if (event == RZV_DTC_EVENT_END)
    {
      dmainfo("DTC transfer completed\n");
      g_dtc_transfer_complete = true;
    }
  else if (event == RZV_DTC_EVENT_ERROR)
    {
      dmaerr("ERROR: DTC transfer error\n");
    }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_dtc_initialize
 *
 * Description:
 *   Initialize and configure the DTC (Data Transfer Controller)
 *   for the RZV2H RDK board
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv2h_dtc_initialize(void)
{
  int ret;

  dmainfo("Initializing DTC\n");

  /* Initialize DTC module */

  ret = rzv_dtc_initialize();
  if (ret < 0)
    {
      dmaerr("ERROR: Failed to initialize DTC: %d\n", ret);
      return ret;
    }

  dmainfo("DTC initialized successfully\n");

  return OK;
}

/****************************************************************************
 * Name: rzv2h_dtc_setup_example
 *
 * Description:
 *   Setup an example DTC transfer (memory to memory)
 *   This demonstrates how to use the DTC driver
 *
 * Input Parameters:
 *   src_addr - Source address
 *   dest_addr - Destination address
 *   count - Number of transfers
 *   size - Transfer size (byte, word, long)
 *
 * Returned Value:
 *   DTC handle on success; NULL on failure
 *
 ****************************************************************************/

rzv_dtc_handle_t rzv2h_dtc_setup_example(uint32_t src_addr,
                                          uint32_t dest_addr,
                                          uint32_t count,
                                          rzv_dtc_size_t size)
{
  rzv_dtc_config_t config;
  rzv_dtc_handle_t handle = NULL;
  int ret;

  dmainfo("Setting up DTC transfer:\n");
  dmainfo("  Source: 0x%08x\n", src_addr);
  dmainfo("  Dest:   0x%08x\n", dest_addr);
  dmainfo("  Count:  %u\n", count);

  /* Configure DTC transfer */

  memset(&config, 0, sizeof(config));
  config.mode = RZV_DTC_MODE_NORMAL;
  config.size = size;
  config.src_addr_mode = RZV_DTC_ADDR_INCR;
  config.dest_addr_mode = RZV_DTC_ADDR_INCR;
  config.software_trigger = true;  /* Use software trigger for example */
  config.src_addr = src_addr;
  config.dest_addr = dest_addr;
  config.transfer_count = count;
  config.block_count = 0;
  config.elc_src = -1;
  config.irq_src = -1;
  config.callback = dtc_transfer_callback;
  config.user_data = NULL;

  /* Open DTC channel */

  ret = rzv_dtc_open(&handle, &config);
  if (ret < 0)
    {
      dmaerr("ERROR: Failed to open DTC: %d\n", ret);
      return NULL;
    }

  dmainfo("DTC channel opened successfully\n");

  return handle;
}

/****************************************************************************
 * Name: rzv2h_dtc_setup_hardware_trigger
 *
 * Description:
 *   Setup a DTC transfer with hardware trigger
 *   This demonstrates hardware-triggered DTC transfers
 *
 * Input Parameters:
 *   src_addr - Source address
 *   dest_addr - Destination address
 *   count - Number of transfers
 *   size - Transfer size (byte, word, long)
 *   elc_src - ELC event source for triggering
 *
 * Returned Value:
 *   DTC handle on success; NULL on failure
 *
 ****************************************************************************/

rzv_dtc_handle_t rzv2h_dtc_setup_hardware_trigger(uint32_t src_addr,
                                                   uint32_t dest_addr,
                                                   uint32_t count,
                                                   rzv_dtc_size_t size,
                                                   int elc_src)
{
  rzv_dtc_config_t config;
  rzv_dtc_handle_t handle = NULL;
  int ret;

  dmainfo("Setting up hardware-triggered DTC transfer:\n");
  dmainfo("  Source:   0x%08x\n", src_addr);
  dmainfo("  Dest:     0x%08x\n", dest_addr);
  dmainfo("  Count:    %u\n", count);
  dmainfo("  ELC Src:  %d\n", elc_src);

  /* Configure DTC transfer */

  memset(&config, 0, sizeof(config));
  config.mode = RZV_DTC_MODE_NORMAL;
  config.size = size;
  config.src_addr_mode = RZV_DTC_ADDR_INCR;
  config.dest_addr_mode = RZV_DTC_ADDR_INCR;
  config.software_trigger = false;  /* Use hardware trigger */
  config.src_addr = src_addr;
  config.dest_addr = dest_addr;
  config.transfer_count = count;
  config.block_count = 0;
  config.elc_src = elc_src;
  config.irq_src = -1;
  config.callback = dtc_transfer_callback;
  config.user_data = NULL;

  /* Open DTC channel */

  ret = rzv_dtc_open(&handle, &config);
  if (ret < 0)
    {
      dmaerr("ERROR: Failed to open DTC: %d\n", ret);
      return NULL;
    }

  /* Enable the DTC channel */

  ret = rzv_dtc_enable(handle);
  if (ret < 0)
    {
      dmaerr("ERROR: Failed to enable DTC: %d\n", ret);
      rzv_dtc_close(handle);
      return NULL;
    }

  dmainfo("Hardware-triggered DTC channel enabled\n");

  return handle;
}

/****************************************************************************
 * Name: rzv2h_dtc_cleanup
 *
 * Description:
 *   Cleanup and close a DTC channel
 *
 * Input Parameters:
 *   handle - DTC handle to cleanup
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv2h_dtc_cleanup(rzv_dtc_handle_t handle)
{
  int ret;

  if (handle == NULL)
    {
      return -EINVAL;
    }

  /* Disable DTC channel */

  ret = rzv_dtc_disable(handle);
  if (ret < 0)
    {
      dmaerr("ERROR: Failed to disable DTC: %d\n", ret);
    }

  /* Close DTC channel */

  ret = rzv_dtc_close(handle);
  if (ret < 0)
    {
      dmaerr("ERROR: Failed to close DTC: %d\n", ret);
      return ret;
    }

  dmainfo("DTC channel closed\n");

  return OK;
}

#endif /* CONFIG_RZV_DTC */

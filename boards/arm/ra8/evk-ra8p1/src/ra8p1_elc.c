/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_adc_b_hwtrigger.c
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

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <debug.h>
#include <syslog.h>

#include <nuttx/board.h>
#include <arch/board/board.h>
#include <nuttx/analog/adc.h>

#include "ra_elc.h"
#include "evk-ra8p1.h"

/* Include IRQ definitions for ELC event macros */

#include <arch/ra8/ra8p1_irq.h>

#ifdef CONFIG_RA_ELC

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/
/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_elc_initialize
 *
 * Description:
 *   Initialize the Event Link Controller on the EVK-RA8P1 board.
 *   This function sets up event links between peripherals as configured.
 *
 *   Note: For the ADC-ELC example, the ADC driver's built-in functions
 *   (ra8_adc_configure_gpt_trigger, ra8_adc_configure_elc_trigger) handle
 *   the ELC link configuration internally, so manual ELC setup is not
 *   required for ADC triggering.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/
int board_elc_initialize(void)
{
  int ret;

  syslog(LOG_INFO, "ELC: Initializing board ELC configuration\n");

  /* Initialize the ELC module */

  ret = ra_elc_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ELC: Failed to initialize: %d\n", ret);
      return ret;
    }


  /* Enable ELC global operation */

  ret = ra_elc_enable();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ELC: Failed to enable: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "ELC: Initialized successfully\n");

  return OK;
}
#endif /* CONFIG_RA_ELC */

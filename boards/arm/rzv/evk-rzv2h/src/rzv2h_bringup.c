/****************************************************************************
 * boards/arm/rzv/evk-rzv2h/src/rzv2h_bringup.c
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

 #include <stddef.h>

#include <sys/mount.h>
#include <stdbool.h>
#include <syslog.h>

#include <nuttx/fs/fs.h>

#include "evk-rzv2h.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_bringup
 *
 * Description:
 *   Perform architecture-specific initialization
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=y :
 *     Called from board_late_initialize().
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=n && CONFIG_BOARDCTL=y :
 *     Called from the NSH library
 *
 ****************************************************************************/

int rzv2h_bringup(void)
{
  int ret = 0;

#ifdef CONFIG_FS_PROCFS
  /* Mount the procfs file system */

  ret = nx_mount(NULL, "/proc", "procfs", 0, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to mount procfs at /proc: %d\n", ret);
    }
#endif

#ifdef CONFIG_ARCH_BUTTONS
  /* Initialize buttons */

  rzv2h_button_initialize();
#endif

#ifdef CONFIG_RZV_GPT_PWM
  ret = rzv2h_pwm_setup();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize PWM: %d\n", ret);
    }
#endif

#ifdef CONFIG_RZV_ADC
  {
    /* Initialize ADC device for board bringup. Use channel 0 by default. */
    extern int rzv_adc_initialize(const char *devpath, const uint8_t *chanlist,
                                  int nchannels);
    static const uint8_t chanlist[] = { 0 };
    ret = rzv_adc_initialize("/dev/adc0", chanlist, 1);
    if (ret < 0)
      {
        syslog(LOG_ERR, "ERROR: Failed to initialize ADC: %d\n", ret);
      }
  }
#endif

  (void)ret;
  return ret;
}

/****************************************************************************
 * Name: board_late_initialize
 *
 * Description:
 *   If CONFIG_BOARD_LATE_INITIALIZE is selected, then an additional
 *   initialization call will be performed in the boot-up sequence to a
 *   function called board_late_initialize().  board_late_initialize() will
 *   be called immediately after up_initialize() is called and just before
 *   the initial application is started.  This additional initialization
 *   phase may be used, for example, to initialize board-specific device
 *   drivers.
 *
 ****************************************************************************/

#ifdef CONFIG_BOARD_LATE_INITIALIZE
void board_late_initialize(void)
{
  /* Perform board-specific initialization */

  rzv2h_bringup();
}
#endif
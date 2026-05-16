/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_app_examples.c
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
 * Unified example wrappers that provide a single entry point
 * rzv2h_<app>_example() for each board example to simplify calls
 * from board_bringup().
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>

#include "rdk-rzv2h.h"

/****************************************************************************
 * Private Functions
 ****************************************************************************/

#ifdef CONFIG_RZV2H_SPI_LOOPBACK_EXAMPLE
static int rzv2h_spi_loopback_example(void)
{
  int ret = rzv2h_spi_loopback_init();
  if (ret < 0)
    {
      syslog(LOG_ERR, "SPI Loopback init failed: %d\n", ret);
      return ret;
    }

  return rzv2h_spi_loopback_main(0, NULL);
}
#endif

#ifdef CONFIG_RZV2H_PWM_ONESHOT_EXAMPLE
static int rzv2h_pwm_oneshot_example(void)
{
  int ret = rzv2h_pwm_oneshot_init();
  if (ret < 0)
    {
      syslog(LOG_ERR, "PWM Oneshot init failed: %d\n", ret);
      return ret;
    }

  return rzv2h_pwm_oneshot_main(0, NULL);
}
#endif

#ifdef CONFIG_RZV2H_WDT_TEST
static int rzv2h_wdt_test_example(void)
{
  int ret = rzv2h_wdt_test_init();
  if (ret < 0)
    {
      syslog(LOG_ERR, "WDT test init failed: %d\n", ret);
      return ret;
    }

  return wdt_test_main(0, NULL);
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_app_examples
 *
 * Description:
 *   Run all enabled application examples. Returns 0 on success or the
 *   last non-zero error code from any example.
 *
 ****************************************************************************/

int rzv2h_app_examples(void)
{
  int ret = 0;
  int last_err = ret;

  syslog(LOG_INFO, "Starting RDK-RZV2H application examples...\n");

#ifdef CONFIG_RZV2H_SPI_LOOPBACK_EXAMPLE
  ret = rzv2h_spi_loopback_example();
  if (ret < 0)
    {
      syslog(LOG_ERR, "SPI Loopback example failed: %d\n", ret);
      last_err = ret;
    }
  else
    {
      syslog(LOG_INFO, "SPI Loopback example completed successfully\n");
    }
#endif

#ifdef CONFIG_RZV2H_PWM_ONESHOT_EXAMPLE
  ret = rzv2h_pwm_oneshot_example();
  if (ret < 0)
    {
      syslog(LOG_ERR, "PWM Oneshot example failed: %d\n", ret);
      last_err = ret;
    }
  else
    {
      syslog(LOG_INFO, "PWM Oneshot example completed successfully\n");
    }
#endif

#ifdef CONFIG_RZV2H_WDT_TEST
  ret = rzv2h_wdt_test_example();
  if (ret < 0)
    {
      syslog(LOG_ERR, "WDT test example failed: %d\n", ret);
      last_err = ret;
    }
  else
    {
      syslog(LOG_INFO, "WDT test example completed successfully\n");
    }
#endif

  if (last_err == 0)
    {
      syslog(LOG_INFO, "All RDK-RZV2H examples completed successfully\n");
    }
  else
    {
      syslog(LOG_WARNING,
             "Some RDK-RZV2H examples failed (last error: %d)\n",
             last_err);
    }

  return last_err;
}

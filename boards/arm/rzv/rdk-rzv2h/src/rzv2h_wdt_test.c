/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_wdt_test.c
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
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>

#include <nuttx/timers/watchdog.h>
#include <nuttx/clock.h>

#include "rzv_gpio.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define WDT_DEVPATH       "/dev/watchdog0"
#define WDT_TIMEOUT_MS    5000    /* 5 second timeout */
#define REFRESH_PERIOD_MS 2000    /* Refresh every 2 seconds */
#define STATUS_PRINT_INTERVAL 3   /* Print status every 3 refreshes */

/* GPIO definitions for RZV2H - adjust based on actual hardware */
#define GPIO_LED1_PIN     10      /* Example: Port 10, Pin 0 */
#define GPIO_SW1_PIN      11      /* Example: Port 11, Pin 0 */

/****************************************************************************
 * Private Data
 ****************************************************************************/

static int g_wdt_fd = -1;
static bool g_wdt_running = false;
static bool g_refresh_enabled = true;
static volatile uint32_t g_refresh_count = 0;
static timer_t g_timer_id;
static bool g_timer_started = false;

/* LED state */
static bool g_led_state = false; /* false = off */

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: wdt_timer_handler
 *
 * Description:
 *   Timer signal handler - called every REFRESH_PERIOD_MS to refresh WDT
 *
 ****************************************************************************/

static void wdt_timer_handler(int signo, siginfo_t *info, void *context)
{
  int ret;

  UNUSED(signo);
  UNUSED(info);
  UNUSED(context);

  if (!g_wdt_running || !g_refresh_enabled)
    {
      return;
    }

  /* Refresh the watchdog */

  ret = ioctl(g_wdt_fd, WDIOC_KEEPALIVE, 0);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: WDIOC_KEEPALIVE failed: %d\n", errno);
      return;
    }

  /* Increment refresh counter */

  g_refresh_count++;

  /* Toggle LED to indicate activity */

  g_led_state = !g_led_state;
  /* TODO: rzv_gpiowrite(GPIO_LED1_PIN, g_led_state); */

  /* Print status every STATUS_PRINT_INTERVAL refreshes */

  if ((g_refresh_count % STATUS_PRINT_INTERVAL) == 0)
    {
      struct watchdog_status_s status;

      ret = ioctl(g_wdt_fd, WDIOC_GETSTATUS, (unsigned long)&status);
      if (ret == OK)
        {
          syslog(LOG_INFO, "WDT refreshed (count=%lu, timeout=%lu ms, "
                 "timeleft=%lu ms, flags=0x%02lx)\n",
                 (unsigned long)g_refresh_count,
                 (unsigned long)status.timeout,
                 (unsigned long)status.timeleft,
                 status.flags);
        }
      else
        {
          syslog(LOG_INFO, "WDT refreshed (count=%lu)\n",
                 (unsigned long)g_refresh_count);
        }
    }
}

/****************************************************************************
 * Name: wdt_start_timer
 *
 * Description:
 *   Start periodic timer to refresh WDT
 *
 ****************************************************************************/

static int wdt_start_timer(void)
{
  struct sigevent sev;
  struct itimerspec its;
  struct sigaction sa;
  int ret;

  /* Setup signal handler */

  sa.sa_sigaction = wdt_timer_handler;
  sa.sa_flags = SA_SIGINFO;
  sigemptyset(&sa.sa_mask);

  ret = sigaction(SIGALRM, &sa, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: sigaction failed: %d\n", errno);
      return -errno;
    }

  /* Create timer */

  sev.sigev_notify = SIGEV_SIGNAL;
  sev.sigev_signo = SIGALRM;
  sev.sigev_value.sival_ptr = &g_timer_id;

  ret = timer_create(CLOCK_REALTIME, &sev, &g_timer_id);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: timer_create failed: %d\n", errno);
      return -errno;
    }

  /* Start timer - periodic at REFRESH_PERIOD_MS */

  its.it_value.tv_sec = REFRESH_PERIOD_MS / 1000;
  its.it_value.tv_nsec = (REFRESH_PERIOD_MS % 1000) * 1000000;
  its.it_interval.tv_sec = its.it_value.tv_sec;
  its.it_interval.tv_nsec = its.it_value.tv_nsec;

  ret = timer_settime(g_timer_id, 0, &its, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: timer_settime failed: %d\n", errno);
      timer_delete(g_timer_id);
      return -errno;
    }

  g_timer_started = true;
  syslog(LOG_INFO, "Periodic timer started - refreshing WDT every %d ms\n",
         REFRESH_PERIOD_MS);

  return OK;
}

/****************************************************************************
 * Name: wdt_stop_timer
 *
 * Description:
 *   Stop the periodic refresh timer
 *
 ****************************************************************************/

static void wdt_stop_timer(void)
{
  struct itimerspec its;

  if (!g_timer_started)
    {
      return;
    }

  /* Stop timer */

  memset(&its, 0, sizeof(its));
  timer_settime(g_timer_id, 0, &its, NULL);
  timer_delete(g_timer_id);

  g_timer_started = false;
  syslog(LOG_INFO, "Timer stopped - WDT will no longer be refreshed\n");
}

/****************************************************************************
 * Name: wdt_print_info
 *
 * Description:
 *   Print current WDT status information
 *
 ****************************************************************************/

static void wdt_print_info(void)
{
  struct watchdog_status_s status;
  int ret;

  ret = ioctl(g_wdt_fd, WDIOC_GETSTATUS, (unsigned long)&status);
  if (ret == OK)
    {
      syslog(LOG_INFO, "\nWDT Status:\n");
      syslog(LOG_INFO, "  Timeout:   %lu ms\n",
             (unsigned long)status.timeout);
      syslog(LOG_INFO, "  Time Left: %lu ms\n",
             (unsigned long)status.timeleft);
      syslog(LOG_INFO, "  Flags:     0x%02lx ", status.flags);

      if (status.flags & WDFLAGS_ACTIVE)
        syslog(LOG_INFO, "(ACTIVE) ");
      if (status.flags & WDFLAGS_CAPTURE)
        syslog(LOG_INFO, "(CAPTURE) ");

      syslog(LOG_INFO, "\n\n");
    }
  else
    {
      syslog(LOG_ERR, "ERROR: Failed to get WDT status: %d\n", errno);
    }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: wdt_test_main
 *
 * Description:
 *   WDT test application main entry point
 *
 ****************************************************************************/

int wdt_test_main(int argc, char *argv[])
{
  int ret;
  bool stop_refresh = false;

  syslog(LOG_INFO,
         "========================================================\n");
  syslog(LOG_INFO, "RZV2H WDT Test Application\n");
  syslog(LOG_INFO,
         "========================================================\n");
  syslog(LOG_INFO, "This example demonstrates WDT driver functionality.\n");
  syslog(LOG_INFO, "The WDT counter is refreshed periodically every %d ms.\n",
         REFRESH_PERIOD_MS);
  syslog(LOG_INFO, "Refresh status is printed every %d refreshes.\n",
         STATUS_PRINT_INTERVAL);
  syslog(LOG_INFO, "\nOptions:\n");
  syslog(LOG_INFO, "  Run without args: Normal operation (auto-refresh)\n");
  syslog(LOG_INFO, "  Run with 'stop': Stop refresh and trigger reset\n");
  syslog(LOG_INFO,
         "========================================================\n\n");

  /* Check if we should stop refresh to test timeout */

  if (argc > 1 && strcmp(argv[1], "stop") == 0)
    {
      stop_refresh = true;
      syslog(LOG_ALERT,
             "*** STOP mode: WDT will timeout and reset system! ***\n\n");
    }

  /* Open watchdog device */

  g_wdt_fd = open(WDT_DEVPATH, O_RDWR);
  if (g_wdt_fd < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to open %s: %d\n",
             WDT_DEVPATH, errno);
      return -errno;
    }

  syslog(LOG_INFO, "Watchdog device opened: %s\n", WDT_DEVPATH);

  /* Set watchdog timeout */

  ret = ioctl(g_wdt_fd, WDIOC_SETTIMEOUT, (unsigned long)WDT_TIMEOUT_MS);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: WDIOC_SETTIMEOUT failed: %d\n", errno);
      close(g_wdt_fd);
      return -errno;
    }

  syslog(LOG_INFO, "WDT timeout set to %d ms\n", WDT_TIMEOUT_MS);

  /* Get and display initial status */

  wdt_print_info();

  /* Start watchdog */

  ret = ioctl(g_wdt_fd, WDIOC_START, 0);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: WDIOC_START failed: %d\n", errno);
      close(g_wdt_fd);
      return -errno;
    }

  g_wdt_running = true;
  g_refresh_enabled = !stop_refresh;
  g_refresh_count = 0;

  syslog(LOG_INFO, "WDT started successfully\n\n");

  /* Start periodic timer to refresh WDT (if not in stop mode) */

  if (!stop_refresh)
    {
      ret = wdt_start_timer();
      if (ret < 0)
        {
          syslog(LOG_ERR, "ERROR: Failed to start refresh timer: %d\n", ret);
          close(g_wdt_fd);
          return ret;
        }

      syslog(LOG_INFO,
             "WDT auto-refresh enabled. Press CTRL+C to exit.\n\n");

      /* Main loop - just sleep and let timer do the work */

      while (g_wdt_running)
        {
          sleep(10);
          wdt_print_info();
        }

      /* Cleanup */

      wdt_stop_timer();
    }
  else
    {
      /* Stop mode - don't refresh, wait for timeout */

      syslog(LOG_ALERT,
             "WDT refresh DISABLED - system will reset in ~%d ms\n",
             WDT_TIMEOUT_MS);
      syslog(LOG_ALERT, "Waiting for watchdog timeout...\n");

      /* Just wait - system will reset */

      while (1)
        {
          sleep(1);
          syslog(LOG_ALERT, "Still waiting for WDT reset...\n");
        }
    }

  /* Cleanup (will likely never reach here due to WDT reset in stop mode) */

  close(g_wdt_fd);

  return OK;
}

/****************************************************************************
 * Name: rzv2h_wdt_test_init
 *
 * Description:
 *   Initialize WDT test application
 *
 ****************************************************************************/

int rzv2h_wdt_test_init(void)
{
  /* Nothing to initialize, test runs on demand */

  syslog(LOG_INFO, "WDT test application registered as 'wdt_test'\n");
  return OK;
}

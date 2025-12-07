/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_wdg_test.c
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

#include "ra_gpio.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define WDT_DEVPATH       "/dev/watchdog0"
#define WDT_TIMEOUT_MS    2000    /* 2 second timeout */
#define REFRESH_PERIOD_MS 1000    /* Refresh every 1 second */
#define STATUS_PRINT_INTERVAL 3   /* Print status every 3 refreshes */

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
static bool g_led1_state = true; /* Active low, true = off */

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: wdt_timer_handler
 *
 * Description:
 *   Timer signal handler - called every 1 second to refresh WDT
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

  g_led1_state = !g_led1_state;
  ra_gpiowrite(GPIO_LED1, g_led1_state);

  /* Print status every 3 refreshes */

  if ((g_refresh_count % STATUS_PRINT_INTERVAL) == 0)
    {
      struct watchdog_status_s status;

      ret = ioctl(g_wdt_fd, WDIOC_GETSTATUS, (unsigned long)&status);
      if (ret == OK)
        {
          syslog(LOG_INFO, "WDT counter refreshed (count=%lu, timeout=%lu ms, "
                 "timeleft=%lu ms)\n",
                 g_refresh_count, status.timeout, status.timeleft);
        }
      else
        {
          syslog(LOG_INFO, "WDT counter refreshed (count=%lu)\n",
                 g_refresh_count);
        }
    }
}

/****************************************************************************
 * Name: wdt_start_timer
 *
 * Description:
 *   Start periodic timer to refresh WDT every 1 second
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

  /* Start timer - 1 second periodic */

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
  syslog(LOG_INFO, "GPT-like timer started - refreshing WDT every %d ms\n",
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
 * Name: wdt_check_reset_status
 *
 * Description:
 *   Check if the last reset was caused by WDT timeout
 *
 ****************************************************************************/

static void wdt_check_reset_status(void)
{
  uint8_t rstsr1;

  /* Read RSTSR1 register to check for WDT reset */

  rstsr1 = getreg8(0x4001e410); /* R_SYSTEM->RSTSR1 */

  if (rstsr1 & (1 << 0)) /* WDTRF bit */
    {
      syslog(LOG_ALERT,
             "************************ WDT Reset detected ************************\n");
      syslog(LOG_ALERT,
             "System was reset by watchdog timeout!\n");
      syslog(LOG_ALERT,
             "********************************************************************\n");

      /* Turn ON LED1 to indicate WDT reset */

      ra_gpiowrite(GPIO_LED1, false); /* Active low - ON */

      /* Clear the flag */

      putreg8(0, 0x4001e410);

      /* Wait a moment before continuing */

      sleep(2);
    }
}

/****************************************************************************
 * Name: button_press_callback
 *
 * Description:
 *   Callback when SW1 is pressed - stops WDT refresh
 *
 ****************************************************************************/

static int button_press_callback(int irq, void *context, void *arg)
{
  UNUSED(irq);
  UNUSED(context);
  UNUSED(arg);

  if (g_wdt_running && g_refresh_enabled)
    {
      syslog(LOG_ALERT,
             "\n*** Button SW1 pressed - Stopping WDT refresh ***\n");
      syslog(LOG_ALERT,
             "WDT will timeout in approximately 2 seconds and reset MCU\n");

      /* Stop the refresh timer */

      g_refresh_enabled = false;
      wdt_stop_timer();

      /* Turn OFF LED1 to indicate refresh stopped */

      ra_gpiowrite(GPIO_LED1, true); /* Active low - OFF */
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: wdg_test_main
 *
 * Description:
 *   WDT test application main entry point
 *
 ****************************************************************************/

int wdg_test_main(int argc, char *argv[])
{
  int ret;

  UNUSED(argc);
  UNUSED(argv);

  syslog(LOG_INFO,
         "========================================================\n");
  syslog(LOG_INFO, "NuttX WDT Test Application (FSP-style)\n");
  syslog(LOG_INFO,
         "========================================================\n");
  syslog(LOG_INFO,
         "This example demonstrates WDT HAL module functionality.\n");
  syslog(LOG_INFO,
         "The WDT counter is refreshed periodically every 1 second.\n");
  syslog(LOG_INFO, "Refresh status is printed every 3 seconds.\n");
  syslog(LOG_INFO,
         "Press push button SW1 to stop WDT counter from refreshing.\n");
  syslog(LOG_INFO,
         "Approximately after 2 seconds, WDT resets MCU and turns LED ON.\n");
  syslog(LOG_INFO,
         "========================================================\n\n");

  /* Check if last reset was caused by WDT */

  wdt_check_reset_status();

  /* Initialize button GPIO for external interrupt */

  ret = ra_gpioconfig(GPIO_SW1);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to configure button GPIO: %d\n", ret);
      return ret;
    }
  ret = ra_gpiosetevent(GPIO_SW1, false, true, false,
                        button_handler_isr, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to configure button interrupt: %d\n",
             ret);
      return ret;
    }

  syslog(LOG_INFO, "Button SW1 configured for external interrupt\n");

  /* Open watchdog device */

  g_wdt_fd = open(WDT_DEVPATH, O_RDWR);
  if (g_wdt_fd < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to open %s: %d\n",
             WDT_DEVPATH, errno);
      return -errno;
    }

  syslog(LOG_INFO, "Watchdog device opened: %s\n", WDT_DEVPATH);

  /* Set watchdog timeout to 2 seconds */

  ret = ioctl(g_wdt_fd, WDIOC_SETTIMEOUT, (unsigned long)WDT_TIMEOUT_MS);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: WDIOC_SETTIMEOUT failed: %d\n", errno);
      close(g_wdt_fd);
      return -errno;
    }

  syslog(LOG_INFO, "WDT timeout set to %d ms\n", WDT_TIMEOUT_MS);

  /* Start watchdog */

  ret = ioctl(g_wdt_fd, WDIOC_START, 0);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: WDIOC_START failed: %d\n", errno);
      close(g_wdt_fd);
      return -errno;
    }

  g_wdt_running = true;
  g_refresh_enabled = true;
  g_refresh_count = 0;

  syslog(LOG_INFO, "WDT started successfully\n");

  /* Start periodic timer to refresh WDT */

  ret = wdt_start_timer();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to start refresh timer: %d\n", ret);
      close(g_wdt_fd);
      return ret;
    }

  syslog(LOG_INFO,
         "\nWDT initialized and running. Press SW1 to trigger timeout.\n\n");

  /* Main loop - just sleep and let timer do the work */

  while (g_wdt_running)
    {
      sleep(1);

      /* If refresh was stopped and we're still running,
       * we're waiting for WDT reset
       */

      if (!g_refresh_enabled)
        {
          syslog(LOG_ALERT, "Waiting for WDT reset...\n");
        }
    }

  /* Cleanup (will likely never reach here due to WDT reset) */

  wdt_stop_timer();
  close(g_wdt_fd);

  return OK;
}

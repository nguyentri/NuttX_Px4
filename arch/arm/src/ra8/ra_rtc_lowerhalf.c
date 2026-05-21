/****************************************************************************
 * arch/arm/src/ra8/ra_rtc_lowerhalf.c
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
#include <debug.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#include <nuttx/timers/rtc.h>

#include "arm_internal.h"
#include "ra_rtc.h"

#ifdef CONFIG_RTC_DRIVER

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct ra_rtc_lowerhalf_s
{
  /* This is the contained reference to the read-only, lower-half
   * operations vtable (which may lie in FLASH or ROM)
   */

  FAR const struct rtc_ops_s *ops;

#ifdef CONFIG_RTC_ALARM
  /* Alarm callback information */

  struct lower_setalarm_s alarminfo;
#endif
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int ra_lowerhalf_rdtime(FAR struct rtc_lowerhalf_s *lower,
                               FAR struct rtc_time *rtctime);
static int ra_lowerhalf_settime(FAR struct rtc_lowerhalf_s *lower,
                                FAR const struct rtc_time *rtctime);
static bool ra_lowerhalf_havesettime(FAR struct rtc_lowerhalf_s *lower);

#ifdef CONFIG_RTC_ALARM
static int ra_lowerhalf_setalarm(FAR struct rtc_lowerhalf_s *lower,
                                 FAR const struct lower_setalarm_s *alarminfo);
static int ra_lowerhalf_setrelative(FAR struct rtc_lowerhalf_s *lower,
                                    FAR const struct lower_setrelative_s *relinfo);
static int ra_lowerhalf_cancelalarm(FAR struct rtc_lowerhalf_s *lower,
                                    int alarmid);
static int ra_lowerhalf_rdalarm(FAR struct rtc_lowerhalf_s *lower,
                                FAR struct lower_rdalarm_s *alarminfo);
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* RA RTC lower half driver operations */

static const struct rtc_ops_s g_rtc_ops =
{
  .rdtime      = ra_lowerhalf_rdtime,
  .settime     = ra_lowerhalf_settime,
  .havesettime = ra_lowerhalf_havesettime,
#ifdef CONFIG_RTC_ALARM
  .setalarm    = ra_lowerhalf_setalarm,
  .setrelative = ra_lowerhalf_setrelative,
  .cancelalarm = ra_lowerhalf_cancelalarm,
  .rdalarm     = ra_lowerhalf_rdalarm,
#endif
#ifdef CONFIG_RTC_PERIODIC
  .setperiodic    = NULL,
  .cancelperiodic = NULL,
#endif
#ifdef CONFIG_RTC_IOCTL
  .ioctl       = NULL,
#endif
#ifndef CONFIG_DISABLE_PSEUDOFS_OPERATIONS
  .destroy     = NULL,
#endif
};

/* RA RTC device state */

static struct ra_rtc_lowerhalf_s g_rtc_lowerhalf =
{
  .ops = &g_rtc_ops,
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_lowerhalf_rdtime
 *
 * Description:
 *   Implements the rdtime() method of the RTC driver interface
 *
 * Input Parameters:
 *   lower   - A reference to RTC lower half driver state structure
 *   rtctime - The location in which to return the current RTC time.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno on failure
 *
 ****************************************************************************/

static int ra_lowerhalf_rdtime(FAR struct rtc_lowerhalf_s *lower,
                               FAR struct rtc_time *rtctime)
{
#ifdef CONFIG_RTC_DATETIME
  struct tm tm_time;
  int ret;

  ret = up_rtc_getdatetime(&tm_time);
  if (ret < 0)
    {
      rtcerr("ERROR: up_rtc_getdatetime failed: %d\n", ret);
      return ret;
    }

  /* Copy tm structure to rtc_time */
  rtctime->tm_sec   = tm_time.tm_sec;
  rtctime->tm_min   = tm_time.tm_min;
  rtctime->tm_hour  = tm_time.tm_hour;
  rtctime->tm_mday  = tm_time.tm_mday;
  rtctime->tm_mon   = tm_time.tm_mon;
  rtctime->tm_year  = tm_time.tm_year;
  rtctime->tm_wday  = tm_time.tm_wday;
  rtctime->tm_yday  = tm_time.tm_yday;
  rtctime->tm_isdst = tm_time.tm_isdst;

  return OK;
#else
  return -ENOSYS;
#endif
}

/****************************************************************************
 * Name: ra_lowerhalf_settime
 *
 * Description:
 *   Implements the settime() method of the RTC driver interface
 *
 * Input Parameters:
 *   lower   - A reference to RTC lower half driver state structure
 *   rtctime - The new time to set
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno on failure
 *
 ****************************************************************************/

static int ra_lowerhalf_settime(FAR struct rtc_lowerhalf_s *lower,
                                FAR const struct rtc_time *rtctime)
{
#ifdef CONFIG_RTC_DATETIME
  struct timespec ts;
  struct tm tm_time;

  /* Copy rtc_time to tm structure */
  tm_time.tm_sec   = rtctime->tm_sec;
  tm_time.tm_min   = rtctime->tm_min;
  tm_time.tm_hour  = rtctime->tm_hour;
  tm_time.tm_mday  = rtctime->tm_mday;
  tm_time.tm_mon   = rtctime->tm_mon;
  tm_time.tm_year  = rtctime->tm_year;
  tm_time.tm_wday  = rtctime->tm_wday;
  tm_time.tm_yday  = rtctime->tm_yday;
  tm_time.tm_isdst = rtctime->tm_isdst;

  /* Convert to timespec */
  ts.tv_sec = timegm(&tm_time);
  ts.tv_nsec = 0;

  return up_rtc_settime(&ts);
#else
  return -ENOSYS;
#endif
}

/****************************************************************************
 * Name: ra_lowerhalf_havesettime
 *
 * Description:
 *   Implements the havesettime() method of the RTC driver interface
 *
 * Input Parameters:
 *   lower   - A reference to RTC lower half driver state structure
 *
 * Returned Value:
 *   Returns true if RTC date-time have been previously set.
 *
 ****************************************************************************/

static bool ra_lowerhalf_havesettime(FAR struct rtc_lowerhalf_s *lower)
{
  extern volatile bool g_rtc_enabled;
  return g_rtc_enabled;
}

#ifdef CONFIG_RTC_ALARM
/****************************************************************************
 * Name: ra_rtc_alarm_callback
 *
 * Description:
 *   This is the callback function called from the RTC alarm interrupt.
 *
 ****************************************************************************/

static void ra_rtc_alarm_callback(void)
{
  FAR struct ra_rtc_lowerhalf_s *priv = &g_rtc_lowerhalf;
  rtc_alarm_callback_t cb;
  FAR void *arg;

  /* Get and clear the callback */

  cb = priv->alarminfo.cb;
  arg = priv->alarminfo.priv;

  priv->alarminfo.cb = NULL;
  priv->alarminfo.priv = NULL;

  /* Call the callback if set */

  if (cb != NULL)
    {
      cb(arg, 0);
    }
}

/****************************************************************************
 * Name: ra_lowerhalf_setalarm
 *
 * Description:
 *   Set an alarm based on an absolute time.
 *
 ****************************************************************************/

static int ra_lowerhalf_setalarm(FAR struct rtc_lowerhalf_s *lower,
                                 FAR const struct lower_setalarm_s *alarminfo)
{
  FAR struct ra_rtc_lowerhalf_s *priv = (FAR struct ra_rtc_lowerhalf_s *)lower;
  struct ra_rtc_alarm_s alarm;
  int ret;

  if (alarminfo == NULL)
    {
      return -EINVAL;
    }

  /* Only support one alarm (id=0) */

  if (alarminfo->id != 0)
    {
      return -EINVAL;
    }

  rtcinfo("Setting alarm: %04d-%02d-%02d %02d:%02d:%02d\n",
          alarminfo->time.tm_year + 1900,
          alarminfo->time.tm_mon + 1,
          alarminfo->time.tm_mday,
          alarminfo->time.tm_hour,
          alarminfo->time.tm_min,
          alarminfo->time.tm_sec);

  /* Save the callback information */

  priv->alarminfo.id = alarminfo->id;
  priv->alarminfo.cb = alarminfo->cb;
  priv->alarminfo.priv = alarminfo->priv;

  /* Configure the alarm structure */

  memset(&alarm, 0, sizeof(alarm));
  alarm.time.tm_sec  = alarminfo->time.tm_sec;
  alarm.time.tm_min  = alarminfo->time.tm_min;
  alarm.time.tm_hour = alarminfo->time.tm_hour;
  alarm.time.tm_mday = alarminfo->time.tm_mday;
  alarm.time.tm_mon  = alarminfo->time.tm_mon;
  alarm.time.tm_year = alarminfo->time.tm_year;
  alarm.time.tm_wday = alarminfo->time.tm_wday;

  /* Match on all time fields for absolute time alarm */

  alarm.sec_match  = true;
  alarm.min_match  = true;
  alarm.hour_match = true;
  alarm.mday_match = true;
  alarm.mon_match  = true;
  alarm.year_match = true;
  alarm.wday_match = false;  /* Don't match on weekday */

  alarm.cb = ra_rtc_alarm_callback;
  alarm.priv = NULL;

  /* Set the alarm */

  ret = ra_rtc_setalarm(&alarm);
  if (ret < 0)
    {
      rtcerr("ERROR: ra_rtc_setalarm failed: %d\n", ret);
      priv->alarminfo.cb = NULL;
      priv->alarminfo.priv = NULL;
    }

  return ret;
}

/****************************************************************************
 * Name: ra_lowerhalf_setrelative
 *
 * Description:
 *   Set an alarm based on a relative time from now.
 *
 ****************************************************************************/

static int ra_lowerhalf_setrelative(FAR struct rtc_lowerhalf_s *lower,
                                    FAR const struct lower_setrelative_s *relinfo)
{
  struct lower_setalarm_s alarminfo;
  struct tm now;
  time_t alarm_time;
  int ret;

  if (relinfo == NULL)
    {
      return -EINVAL;
    }

  /* Get current time */

  ret = up_rtc_getdatetime(&now);
  if (ret < 0)
    {
      rtcerr("ERROR: up_rtc_getdatetime failed: %d\n", ret);
      return ret;
    }

  /* Convert to time_t and add relative offset */

  alarm_time = timegm(&now) + relinfo->reltime;

  /* Convert back to struct tm (rtc_time is cast-compatible with tm) */

  if (gmtime_r(&alarm_time, (FAR struct tm *)&alarminfo.time) == NULL)
    {
      return -EINVAL;
    }

  /* Copy callback info and set as absolute alarm */

  alarminfo.id = relinfo->id;
  alarminfo.cb = relinfo->cb;
  alarminfo.priv = relinfo->priv;

  return ra_lowerhalf_setalarm(lower, &alarminfo);
}

/****************************************************************************
 * Name: ra_lowerhalf_cancelalarm
 *
 * Description:
 *   Cancel an active alarm.
 *
 ****************************************************************************/

static int ra_lowerhalf_cancelalarm(FAR struct rtc_lowerhalf_s *lower,
                                    int alarmid)
{
  FAR struct ra_rtc_lowerhalf_s *priv = (FAR struct ra_rtc_lowerhalf_s *)lower;

  /* Only support one alarm (id=0) */

  if (alarmid != 0)
    {
      return -EINVAL;
    }

  /* Clear callback */

  priv->alarminfo.cb = NULL;
  priv->alarminfo.priv = NULL;

  /* Cancel hardware alarm */

  return ra_rtc_cancelalarm();
}

/****************************************************************************
 * Name: ra_lowerhalf_rdalarm
 *
 * Description:
 *   Read the current alarm setting.
 *
 ****************************************************************************/

static int ra_lowerhalf_rdalarm(FAR struct rtc_lowerhalf_s *lower,
                                FAR struct lower_rdalarm_s *alarminfo)
{
  struct ra_rtc_alarm_s alarm;
  int ret;

  if (alarminfo == NULL || alarminfo->time == NULL)
    {
      return -EINVAL;
    }

  /* Only support one alarm (id=0) */

  if (alarminfo->id != 0)
    {
      return -EINVAL;
    }

  /* Get the alarm from hardware */

  ret = ra_rtc_getalarm(&alarm);
  if (ret < 0)
    {
      return ret;
    }

  /* Copy to output structure */

  alarminfo->time->tm_sec  = alarm.time.tm_sec;
  alarminfo->time->tm_min  = alarm.time.tm_min;
  alarminfo->time->tm_hour = alarm.time.tm_hour;
  alarminfo->time->tm_mday = alarm.time.tm_mday;
  alarminfo->time->tm_mon  = alarm.time.tm_mon;
  alarminfo->time->tm_year = alarm.time.tm_year;
  alarminfo->time->tm_wday = alarm.time.tm_wday;

  return OK;
}
#endif /* CONFIG_RTC_ALARM */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_rtc_lowerhalf
 *
 * Description:
 *   Instantiate the RTC lower half driver for the RA8. General usage:
 *
 *     #include "ra_rtc_lowerhalf.c"
 *     ...
 *     lower = ra_rtc_lowerhalf();
 *     rtc_initialize(0, lower);
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   On success, a non-NULL RTC lower interface is returned.  NULL is
 *   returned on any failure.
 *
 ****************************************************************************/

FAR struct rtc_lowerhalf_s *ra_rtc_lowerhalf(void)
{
  return (FAR struct rtc_lowerhalf_s *)&g_rtc_lowerhalf;
}

#endif /* CONFIG_RTC_DRIVER */

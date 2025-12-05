/****************************************************************************
 * arch/arm/src/ra8/ra_rtc.c
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

#include <debug.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#include <nuttx/arch.h>
#include <nuttx/irq.h>
#include <nuttx/timers/rtc.h>

#include "arm_internal.h"
#include "chip.h"
#include "hardware/ra_memorymap.h"
#include "ra_rtc.h"
#include "ra_mstp.h"
#include "ra_icu.h"

#ifdef CONFIG_RTC

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* RTC enabled state variable - tracks whether RTC has been initialized */

volatile bool g_rtc_enabled = false;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_rtc_wait_rcr2_start
 *
 * Description:
 *   Wait for RCR2 START bit to reach expected value.
 *   Per RA8 hardware manual, the START bit is updated in synchronization
 *   with the next cycle of the count source.
 *
 ****************************************************************************/

static int ra_rtc_wait_rcr2_start(uint8_t expected)
{
  int timeout = RA_RTC_REGISTER_WAIT_TIMEOUT;

  while (timeout-- > 0)
    {
      if ((getreg8(RA_RTC_RCR2) & RA_RTC_RCR2_START) ==
          (expected & RA_RTC_RCR2_START))
        {
          return OK;
        }
    }

  rtcerr("ERROR: Timeout waiting for RCR2.START\n");
  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: ra_rtc_wait_rcr2_reset
 *
 * Description:
 *   Wait for RCR2 RESET bit to clear (reset complete).
 *
 ****************************************************************************/

static int ra_rtc_wait_rcr2_reset(void)
{
  int timeout = RA_RTC_REGISTER_WAIT_TIMEOUT;

  while (timeout-- > 0)
    {
      if ((getreg8(RA_RTC_RCR2) & RA_RTC_RCR2_RESET) == 0)
        {
          return OK;
        }
    }

  rtcerr("ERROR: Timeout waiting for RCR2.RESET to clear\n");
  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: ra_rtc_wait_rcr2_hr24
 *
 * Description:
 *   Wait for RCR2 HR24 bit to reach expected value.
 *
 ****************************************************************************/

static int ra_rtc_wait_rcr2_hr24(uint8_t expected)
{
  int timeout = RA_RTC_REGISTER_WAIT_TIMEOUT;

  while (timeout-- > 0)
    {
      if ((getreg8(RA_RTC_RCR2) & RA_RTC_RCR2_HR24) ==
          (expected & RA_RTC_RCR2_HR24))
        {
          return OK;
        }
    }

  rtcerr("ERROR: Timeout waiting for RCR2.HR24\n");
  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: ra_rtc_wait_rcr1
 *
 * Description:
 *   Wait for RCR1 register to reach expected value.
 *
 ****************************************************************************/

static int ra_rtc_wait_rcr1(uint8_t expected)
{
  int timeout = RA_RTC_REGISTER_WAIT_TIMEOUT;

  while (timeout-- > 0)
    {
      if (getreg8(RA_RTC_RCR1) == expected)
        {
          return OK;
        }
    }

  rtcerr("ERROR: Timeout waiting for RCR1\n");
  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: ra_rtc_start_bit_update
 *
 * Description:
 *   Update the START bit in RCR2 and wait for it to take effect.
 *
 ****************************************************************************/

static int ra_rtc_start_bit_update(uint8_t value)
{
  uint8_t regval;

  regval = getreg8(RA_RTC_RCR2);

  if (value)
    {
      regval |= RA_RTC_RCR2_START;
    }
  else
    {
      regval &= ~RA_RTC_RCR2_START;
    }

  putreg8(regval, RA_RTC_RCR2);

  return ra_rtc_wait_rcr2_start(value ? RA_RTC_RCR2_START : 0);
}

/****************************************************************************
 * Name: ra_rtc_clear_tcen
 *
 * Description:
 *   Clear Time Capture Enable bits after reset.
 *   Per RA8 hardware manual, RTCCR.TCEN must be cleared after reset.
 *
 ****************************************************************************/

static void ra_rtc_clear_tcen(void)
{
  int i;
  int timeout;

  for (i = 0; i < RA_RTC_TIME_CAPTURE_CHANNELS; i++)
    {
      /* Clear TCEN bit */

      putreg8(0, RA_RTC_RTCCR(i));

      /* Wait for TCEN to clear */

      timeout = RA_RTC_REGISTER_WAIT_TIMEOUT;
      while (timeout-- > 0)
        {
          if ((getreg8(RA_RTC_RTCCR(i)) & RA_RTC_RTCCR_TCEN) == 0)
            {
              break;
            }
        }
    }
}

/****************************************************************************
 * Name: ra_rtc_reset
 *
 * Description:
 *   Reset the RTC hardware following FSP initialization sequence.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno on failure
 *
 ****************************************************************************/

static int ra_rtc_reset(void)
{
  int ret;

  /* Stop RTC first */

  ret = ra_rtc_start_bit_update(0);
  if (ret < 0)
    {
      return ret;
    }

  /* Clear RCR2 (sets count mode to calendar mode) */

  putreg8(0, RA_RTC_RCR2);
  ret = ra_rtc_wait_rcr2_start(0);
  if (ret < 0)
    {
      return ret;
    }

  /* Set the RESET bit in RCR2 */

  putreg8(RA_RTC_RCR2_RESET, RA_RTC_RCR2);

  /* Wait for reset to complete (RESET bit auto-clears) */

  ret = ra_rtc_wait_rcr2_reset();
  if (ret < 0)
    {
      return ret;
    }

  /* Disable all RTC interrupts */

  putreg8(0, RA_RTC_RCR1);
  ret = ra_rtc_wait_rcr1(0);
  if (ret < 0)
    {
      return ret;
    }

  /* Clear time capture enable bits per RA8 HW manual */

  ra_rtc_clear_tcen();

  return OK;
}

/****************************************************************************
 * Name: ra_rtc_bcd_to_bin
 *
 * Description:
 *   Convert BCD to binary
 *
 ****************************************************************************/

#if defined(CONFIG_RTC_DATETIME) || defined(CONFIG_RTC_ALARM)
static uint8_t ra_rtc_bcd_to_bin(uint8_t bcd)
{
  return ((bcd >> 4) * 10) + (bcd & 0x0f);
}
#endif

/****************************************************************************
 * Name: ra_rtc_bin_to_bcd
 *
 * Description:
 *   Convert binary to BCD
 *
 ****************************************************************************/

#if defined(CONFIG_RTC_DATETIME) || defined(CONFIG_RTC_ALARM)
static uint8_t ra_rtc_bin_to_bcd(uint8_t bin)
{
  return ((bin / 10) << 4) | (bin % 10);
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_rtc_initialize
 *
 * Description:
 *   Initialize the hardware RTC per the selected configuration.  This
 *   function is called once during the OS initialization sequence.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno on failure
 *
 ****************************************************************************/

int up_rtc_initialize(void)
{
  int ret;

  rtcinfo("up_rtc_initialize: Initializing RA8 RTC\n");

  /* Enable RTC module clock via MSTP */

  ret = ra_mstp_start(RA_MSTP_RTC);
  if (ret < 0)
    {
      rtcerr("ERROR: Failed to enable RTC module clock: %d\n", ret);
      return ret;
    }

  /* Configure RTC clock source - use SOSC (sub-clock) */

  putreg8(RA_RTC_CLOCK_SOURCE_SUBCLK, RA_RTC_RCR4);  /* RCKSEL = 0: SOSC */

  /* Per FSP: Supply 6 clocks of the count source (LOCO/SOSC, ~183us @ 32kHz)
   * We use a slightly longer delay to ensure stability.
   */

  up_udelay(RA_RTC_CLOCK_STABILIZE_DELAY_US);

  /* Reset RTC following proper initialization sequence */

  ret = ra_rtc_reset();
  if (ret < 0)
    {
      rtcerr("ERROR: Failed to reset RTC: %d\n", ret);
      return ret;
    }

  /* Configure RTC for 24-hour mode */

  putreg8(RA_RTC_RCR2_HR24, RA_RTC_RCR2);
  ret = ra_rtc_wait_rcr2_hr24(RA_RTC_RCR2_HR24);
  if (ret < 0)
    {
      rtcerr("ERROR: Failed to set 24-hour mode: %d\n", ret);
      return ret;
    }

  /* Start RTC */

  ret = ra_rtc_start_bit_update(1);
  if (ret < 0)
    {
      rtcerr("ERROR: Failed to start RTC: %d\n", ret);
      return ret;
    }

  g_rtc_enabled = true;

  rtcinfo("up_rtc_initialize: RTC initialized successfully\n");
  return OK;
}

/****************************************************************************
 * Name: up_rtc_getdatetime
 *
 * Description:
 *   Get the current date and time from the date/time RTC.  This interface
 *   is only supported by the date/time RTC hardware implementation.
 *   It is used to replace the system timer.  It is only used by the RTOS
 *   during initialization to set up the system time when CONFIG_RTC and
 *   CONFIG_RTC_DATETIME are selected (and CONFIG_RTC_HIRES is not).
 *
 * Input Parameters:
 *   tp - The location to return the high resolution time value.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno on failure
 *
 ****************************************************************************/

#ifdef CONFIG_RTC_DATETIME
int up_rtc_getdatetime(FAR struct tm *tp)
{
  uint8_t sec, min, hour, mday, mon, wday;
  uint16_t year;

  if (!g_rtc_enabled)
    {
      rtcerr("RTC not initialized\n");
      return -EAGAIN;
    }

  if (!tp)
    {
      return -EINVAL;
    }

  /* Read current time from RTC registers */
  sec  = getreg8(RA_RTC_RSECCNT);
  min  = getreg8(RA_RTC_RMINCNT);
  hour = getreg8(RA_RTC_RHRCNT);
  wday = getreg8(RA_RTC_RWKCNT);
  mday = getreg8(RA_RTC_RDAYCNT);
  mon  = getreg8(RA_RTC_RMONCNT);
  year = getreg16(RA_RTC_RYRCNT);

  /* Convert BCD to binary */
  tp->tm_sec  = ra_rtc_bcd_to_bin(sec & RA_RTC_SEC_MASK);
  tp->tm_min  = ra_rtc_bcd_to_bin(min & RA_RTC_MIN_MASK);
  tp->tm_hour = ra_rtc_bcd_to_bin(hour & RA_RTC_HOUR_MASK);
  tp->tm_mday = ra_rtc_bcd_to_bin(mday & RA_RTC_MDAY_MASK);
  tp->tm_mon  = ra_rtc_bcd_to_bin(mon & RA_RTC_MON_MASK) - 1; /* 0-11 */
  tp->tm_year = ra_rtc_bcd_to_bin(year & RA_RTC_YEAR_MASK) + 100; /* Years since 1900 */
  tp->tm_wday = wday & RA_RTC_WDAY_MASK;
  tp->tm_yday = 0; /* Not used */
  tp->tm_isdst = 0; /* Not used */

  rtcinfo("RTC read: %04d-%02d-%02d %02d:%02d:%02d\n",
          tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday,
          tp->tm_hour, tp->tm_min, tp->tm_sec);

  return OK;
}
#endif

/****************************************************************************
 * Name: up_rtc_settime
 *
 * Description:
 *   Set the RTC to the provided time.  RTC implementations which provide
 *   up_rtc_getdatetime() (CONFIG_RTC_DATETIME is selected) should provide
 *   this function.
 *
 * Input Parameters:
 *   tp - the time to use
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno on failure
 *
 ****************************************************************************/

#ifdef CONFIG_RTC_DATETIME
int up_rtc_settime(FAR const struct timespec *tp)
{
  struct tm newtime;
  int ret;

  if (!g_rtc_enabled)
    {
      rtcerr("RTC not initialized\n");
      return -EAGAIN;
    }

  if (!tp)
    {
      return -EINVAL;
    }

  /* Convert timestamp to broken-down time */

  if (gmtime_r(&tp->tv_sec, &newtime) == NULL)
    {
      rtcerr("gmtime_r failed\n");
      return -EINVAL;
    }

  rtcinfo("RTC set: %04d-%02d-%02d %02d:%02d:%02d\n",
          newtime.tm_year + 1900, newtime.tm_mon + 1, newtime.tm_mday,
          newtime.tm_hour, newtime.tm_min, newtime.tm_sec);

  /* Stop RTC before setting time */

  ret = ra_rtc_start_bit_update(0);
  if (ret < 0)
    {
      rtcerr("ERROR: Failed to stop RTC: %d\n", ret);
      return ret;
    }

  /* Set time registers in BCD format */

  putreg8(ra_rtc_bin_to_bcd(newtime.tm_sec), RA_RTC_RSECCNT);
  putreg8(ra_rtc_bin_to_bcd(newtime.tm_min), RA_RTC_RMINCNT);
  putreg8(ra_rtc_bin_to_bcd(newtime.tm_hour), RA_RTC_RHRCNT);
  putreg8(newtime.tm_wday & RA_RTC_WDAY_MASK, RA_RTC_RWKCNT);
  putreg8(ra_rtc_bin_to_bcd(newtime.tm_mday), RA_RTC_RDAYCNT);
  putreg8(ra_rtc_bin_to_bcd(newtime.tm_mon + 1), RA_RTC_RMONCNT);  /* 1-12 */
  putreg16(ra_rtc_bin_to_bcd(newtime.tm_year - RA_RTC_YEAR_OFFSET),
           RA_RTC_RYRCNT);  /* Years since 2000 */

  /* Restart RTC */

  ret = ra_rtc_start_bit_update(1);
  if (ret < 0)
    {
      rtcerr("ERROR: Failed to restart RTC: %d\n", ret);
      return ret;
    }

  return OK;
}
#endif

/****************************************************************************
 * Alarm Support Functions
 ****************************************************************************/

#ifdef CONFIG_RTC_ALARM

/* IRQ number for alarm interrupt */

static int g_rtc_alarm_irq = -1;

/* Alarm callback information */

static ra_rtc_alarm_callback_t g_rtc_alarm_callback = NULL;
static void *g_rtc_alarm_priv = NULL;

/****************************************************************************
 * Name: ra_rtc_alarm_interrupt
 *
 * Description:
 *   RTC alarm interrupt handler.
 *
 ****************************************************************************/

static int ra_rtc_alarm_interrupt(int irq, void *context, void *arg)
{
  ra_rtc_alarm_callback_t callback;

  UNUSED(irq);
  UNUSED(context);
  UNUSED(arg);

  /* Save and clear callback info atomically */

  callback = g_rtc_alarm_callback;
  g_rtc_alarm_callback = NULL;
  g_rtc_alarm_priv = NULL;

  /* Disable alarm interrupt */

  ra_rtc_cancelalarm();

  /* Clear the interrupt */

  if (g_rtc_alarm_irq >= 0)
    {
      ra_icu_clear_irq(g_rtc_alarm_irq);
    }

  /* Call the callback if set */

  if (callback != NULL)
    {
      callback();
    }

  return OK;
}

/****************************************************************************
 * Name: ra_rtc_setalarm
 *
 * Description:
 *   Set an RTC alarm.
 *
 ****************************************************************************/

int ra_rtc_setalarm(FAR const struct ra_rtc_alarm_s *alarm)
{
  uint8_t regval;
  int ret;

  if (!g_rtc_enabled)
    {
      return -EAGAIN;
    }

  if (alarm == NULL)
    {
      return -EINVAL;
    }

  /* Attach alarm interrupt if not already attached */

  if (g_rtc_alarm_irq < 0)
    {
      g_rtc_alarm_irq = ra_icu_attach(RA_ELC_RTC_ALARM,
                                       ra_rtc_alarm_interrupt,
                                       NULL, false);
      if (g_rtc_alarm_irq < 0)
        {
          rtcerr("ERROR: Could not attach alarm interrupt: %d\n",
                 g_rtc_alarm_irq);
          return -ENOSYS;
        }
    }

  /* Disable alarm interrupt while configuring */

  regval = getreg8(RA_RTC_RCR1);
  regval &= ~RA_RTC_RCR1_AIE;
  putreg8(regval, RA_RTC_RCR1);
  ret = ra_rtc_wait_rcr1(regval);
  if (ret < 0)
    {
      return ret;
    }

  up_disable_irq(g_rtc_alarm_irq);

  /* Set alarm registers */

  if (alarm->sec_match)
    {
      putreg8(ra_rtc_bin_to_bcd(alarm->time.tm_sec) | RA_RTC_ALARM_ENB,
              RA_RTC_RSECAR);
    }
  else
    {
      putreg8(0, RA_RTC_RSECAR);
    }

  if (alarm->min_match)
    {
      putreg8(ra_rtc_bin_to_bcd(alarm->time.tm_min) | RA_RTC_ALARM_ENB,
              RA_RTC_RMINAR);
    }
  else
    {
      putreg8(0, RA_RTC_RMINAR);
    }

  if (alarm->hour_match)
    {
      putreg8(ra_rtc_bin_to_bcd(alarm->time.tm_hour) | RA_RTC_ALARM_ENB,
              RA_RTC_RHRAR);
    }
  else
    {
      putreg8(0, RA_RTC_RHRAR);
    }

  if (alarm->wday_match)
    {
      putreg8((alarm->time.tm_wday & RA_RTC_WDAY_MASK) | RA_RTC_ALARM_ENB,
              RA_RTC_RWKAR);
    }
  else
    {
      putreg8(0, RA_RTC_RWKAR);
    }

  if (alarm->mday_match)
    {
      putreg8(ra_rtc_bin_to_bcd(alarm->time.tm_mday) | RA_RTC_ALARM_ENB,
              RA_RTC_RDAYAR);
    }
  else
    {
      putreg8(1, RA_RTC_RDAYAR);  /* FSP sets 1 when not matching */
    }

  if (alarm->mon_match)
    {
      putreg8(ra_rtc_bin_to_bcd(alarm->time.tm_mon + 1) | RA_RTC_ALARM_ENB,
              RA_RTC_RMONAR);
    }
  else
    {
      putreg8(0, RA_RTC_RMONAR);
    }

  if (alarm->year_match)
    {
      putreg16(ra_rtc_bin_to_bcd(alarm->time.tm_year - RA_RTC_YEAR_OFFSET),
               RA_RTC_RYRAR);
      putreg8(RA_RTC_ALARM_ENB, RA_RTC_RYRAREN);
    }
  else
    {
      putreg16(0, RA_RTC_RYRAR);
      putreg8(0, RA_RTC_RYRAREN);
    }

  /* Save callback information */

  g_rtc_alarm_callback = alarm->cb;
  g_rtc_alarm_priv = alarm->priv;

  /* Enable alarm interrupt */

  regval = getreg8(RA_RTC_RCR1);
  regval |= RA_RTC_RCR1_AIE;
  putreg8(regval, RA_RTC_RCR1);
  ret = ra_rtc_wait_rcr1(regval);
  if (ret < 0)
    {
      return ret;
    }

  up_enable_irq(g_rtc_alarm_irq);

  return OK;
}

/****************************************************************************
 * Name: ra_rtc_cancelalarm
 *
 * Description:
 *   Cancel the current alarm.
 *
 ****************************************************************************/

int ra_rtc_cancelalarm(void)
{
  uint8_t regval;

  /* Disable alarm interrupt */

  regval = getreg8(RA_RTC_RCR1);
  regval &= ~RA_RTC_RCR1_AIE;
  putreg8(regval, RA_RTC_RCR1);
  ra_rtc_wait_rcr1(regval);

  if (g_rtc_alarm_irq >= 0)
    {
      up_disable_irq(g_rtc_alarm_irq);
    }

  /* Clear callback */

  g_rtc_alarm_callback = NULL;
  g_rtc_alarm_priv = NULL;

  return OK;
}

/****************************************************************************
 * Name: ra_rtc_getalarm
 *
 * Description:
 *   Get the current alarm setting.
 *
 ****************************************************************************/

int ra_rtc_getalarm(FAR struct ra_rtc_alarm_s *alarm)
{
  uint8_t regval;

  if (alarm == NULL)
    {
      return -EINVAL;
    }

  memset(alarm, 0, sizeof(struct ra_rtc_alarm_s));

  /* Read alarm registers */

  regval = getreg8(RA_RTC_RSECAR);
  alarm->sec_match = (regval & RA_RTC_ALARM_ENB) != 0;
  alarm->time.tm_sec = ra_rtc_bcd_to_bin(regval & 0x7f);

  regval = getreg8(RA_RTC_RMINAR);
  alarm->min_match = (regval & RA_RTC_ALARM_ENB) != 0;
  alarm->time.tm_min = ra_rtc_bcd_to_bin(regval & 0x7f);

  regval = getreg8(RA_RTC_RHRAR);
  alarm->hour_match = (regval & RA_RTC_ALARM_ENB) != 0;
  alarm->time.tm_hour = ra_rtc_bcd_to_bin(regval & 0x3f);

  regval = getreg8(RA_RTC_RWKAR);
  alarm->wday_match = (regval & RA_RTC_ALARM_ENB) != 0;
  alarm->time.tm_wday = regval & 0x07;

  regval = getreg8(RA_RTC_RDAYAR);
  alarm->mday_match = (regval & RA_RTC_ALARM_ENB) != 0;
  alarm->time.tm_mday = ra_rtc_bcd_to_bin(regval & 0x3f);

  regval = getreg8(RA_RTC_RMONAR);
  alarm->mon_match = (regval & RA_RTC_ALARM_ENB) != 0;
  alarm->time.tm_mon = ra_rtc_bcd_to_bin(regval & 0x1f) - 1;

  alarm->year_match = (getreg8(RA_RTC_RYRAREN) & RA_RTC_ALARM_ENB) != 0;
  alarm->time.tm_year = ra_rtc_bcd_to_bin(getreg16(RA_RTC_RYRAR) & 0xff) +
                        RA_RTC_YEAR_OFFSET;

  return OK;
}
#endif /* CONFIG_RTC_ALARM */

/****************************************************************************
 * Error Adjustment Support Functions
 ****************************************************************************/

#ifdef CONFIG_RA_RTC_ERROR_ADJUSTMENT
/****************************************************************************
 * Name: ra_rtc_set_error_adjustment
 *
 * Description:
 *   Configure automatic error adjustment for the RTC.
 *
 * Input Parameters:
 *   adjustment_type  - RA_RTC_RADJ_NONE, RA_RTC_RADJ_ADD, or RA_RTC_RADJ_SUB
 *   adjustment_value - Number of clock cycles to add/subtract (0-63)
 *
 * Returned Value:
 *   Zero (OK) on success; negative errno on failure.
 *
 ****************************************************************************/

int ra_rtc_set_error_adjustment(uint8_t adjustment_type, uint8_t adjustment_value)
{
  uint8_t rcr2_val;
  uint8_t radj_val;
  int ret;

  if (!g_rtc_enabled)
    {
      return -EAGAIN;
    }

  if (adjustment_type > RA_RTC_RADJ_SUB || adjustment_value > 63)
    {
      return -EINVAL;
    }

  /* Disable automatic adjustment while configuring */

  rcr2_val = getreg8(RA_RTC_RCR2);
  rcr2_val &= ~RA_RTC_RCR2_AADJE;
  putreg8(rcr2_val, RA_RTC_RCR2);

  /* Wait for register update */

  ret = ra_rtc_wait_rcr2_start(rcr2_val & RA_RTC_RCR2_START);
  if (ret < 0)
    {
      return ret;
    }

  if (adjustment_type == RA_RTC_RADJ_NONE)
    {
      /* Just disable adjustment */

      return OK;
    }

  /* Configure RADJ register:
   * Bits 7:6 - PMADJ: Plus/Minus adjustment selection
   *   00 = No adjustment
   *   01 = Add to prescaler (speed up clock)
   *   10 = Subtract from prescaler (slow down clock)
   * Bits 5:0 - ADJ: Adjustment value (0-63)
   */

  radj_val = ((adjustment_type & 0x03) << RA_RTC_RADJ_PMADJ_SHIFT) |
             (adjustment_value & RA_RTC_RADJ_ADJ_MASK);

  putreg8(radj_val, RA_RTC_RADJ);

  /* Configure adjustment period and enable automatic adjustment */

#ifdef CONFIG_RA_RTC_ERROR_PERIOD
  /* Set 10-second or 1-minute period based on CONFIG_RA_RTC_ERROR_PERIOD */

#if CONFIG_RA_RTC_ERROR_PERIOD >= 10
  /* Use 1-minute period */

  rcr2_val &= ~RA_RTC_RCR2_AADJP;  /* AADJP = 0: 1-minute */
#else
  /* Use 10-second period */

  rcr2_val |= RA_RTC_RCR2_AADJP;   /* AADJP = 1: 10-second */
#endif
#endif

  /* Enable automatic adjustment */

  rcr2_val |= RA_RTC_RCR2_AADJE;
  putreg8(rcr2_val, RA_RTC_RCR2);

  return OK;
}

/****************************************************************************
 * Name: ra_rtc_get_error_adjustment
 *
 * Description:
 *   Get current error adjustment settings.
 *
 * Input Parameters:
 *   adjustment_type  - Pointer to receive adjustment type
 *   adjustment_value - Pointer to receive adjustment value
 *
 * Returned Value:
 *   Zero (OK) on success; negative errno on failure.
 *
 ****************************************************************************/

int ra_rtc_get_error_adjustment(FAR uint8_t *adjustment_type,
                                 FAR uint8_t *adjustment_value)
{
  uint8_t radj_val;

  if (adjustment_type == NULL || adjustment_value == NULL)
    {
      return -EINVAL;
    }

  radj_val = getreg8(RA_RTC_RADJ);

  *adjustment_type = (radj_val >> RA_RTC_RADJ_PMADJ_SHIFT) & 0x03;
  *adjustment_value = radj_val & RA_RTC_RADJ_ADJ_MASK;

  return OK;
}
#endif /* CONFIG_RA_RTC_ERROR_ADJUSTMENT */

#endif /* CONFIG_RTC */

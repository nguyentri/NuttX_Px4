/****************************************************************************
 * arch/arm/src/ra8/ra_rtc.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_RTC_H
#define __ARCH_ARM_SRC_RA8_RA_RTC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdbool.h>
#include <nuttx/timers/rtc.h>

#include "chip.h"
#include "hardware/ra_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Clock source initialization delay in microseconds
 * Per FSP: 6 clock cycles at 32kHz = 183us
 */

#define RA_RTC_CLOCK_STABILIZE_DELAY_US  200

/* RTC Clock Source Selection */

#define RA_RTC_CLOCK_SOURCE_SUBCLK       0  /* Sub-clock oscillator (32.768 kHz) */
#define RA_RTC_CLOCK_SOURCE_LOCO         1  /* Low-power On-Chip Oscillator */
#define RA_RTC_CLOCK_SOURCE_MAINCLK      2  /* Main clock oscillator */

/* Time offset for year calculation
 * RTC hardware stores years 00-99 representing 2000-2099
 * C standard tm_year is years since 1900
 * So offset is 100 (2000 - 1900)
 */

#define RA_RTC_YEAR_OFFSET               100

/* Maximum timeout for register wait loops (iterations) */

#define RA_RTC_REGISTER_WAIT_TIMEOUT     10000

/* Number of time capture channels */

#define RA_RTC_TIME_CAPTURE_CHANNELS     3

/****************************************************************************
 * Register Address Compatibility Macros
 * Map RA_RTC_* to R_RTC_* from hardware header
 ****************************************************************************/

/* Control Registers */

#define RA_RTC_RCR1                      R_RTC_RCR1
#define RA_RTC_RCR2                      R_RTC_RCR2
#define RA_RTC_RCR4                      R_RTC_RCR4

/* Counter Registers */

#define RA_RTC_R64CNT                    R_RTC_R64CNT
#define RA_RTC_RSECCNT                   R_RTC_RSECCNT
#define RA_RTC_RMINCNT                   R_RTC_RMINCNT
#define RA_RTC_RHRCNT                    R_RTC_RHRCNT
#define RA_RTC_RWKCNT                    R_RTC_RWKCNT
#define RA_RTC_RDAYCNT                   R_RTC_RDAYCNT
#define RA_RTC_RMONCNT                   R_RTC_RMONCNT
#define RA_RTC_RYRCNT                    R_RTC_RYRCNT

/* Alarm Registers */

#define RA_RTC_RSECAR                    R_RTC_RSECAR
#define RA_RTC_RMINAR                    R_RTC_RMINAR
#define RA_RTC_RHRAR                     R_RTC_RHRAR
#define RA_RTC_RWKAR                     R_RTC_RWKAR
#define RA_RTC_RDAYAR                    R_RTC_RDAYAR
#define RA_RTC_RMONAR                    R_RTC_RMONAR
#define RA_RTC_RYRAR                     R_RTC_RYRAR
#define RA_RTC_RYRAREN                   R_RTC_RYRAREN

/* Frequency and Adjustment Registers */

#define RA_RTC_RFRH                      R_RTC_RFRH
#define RA_RTC_RFRL                      R_RTC_RFRL
#define RA_RTC_RADJ                      R_RTC_RADJ

/* Time Capture Control Registers */

#define RA_RTC_RTCCR(n)                  R_RTC_RTCCR(n)
#define RA_RTC_RTCCR_TCEN                (1 << 7)   /* Time Capture Enable */
#define RA_RTC_RTCCR_TCST                (1 << 0)   /* Time Capture Status */

/****************************************************************************
 * RCR1 Register Bit Definitions
 ****************************************************************************/

#define RA_RTC_RCR1_AIE                  R_RTC_RCR1_AIE   /* Alarm Interrupt Enable */
#define RA_RTC_RCR1_CIE                  R_RTC_RCR1_CIE   /* Carry Interrupt Enable */
#define RA_RTC_RCR1_PIE                  R_RTC_RCR1_PIE   /* Periodic Interrupt Enable */
#define RA_RTC_RCR1_RTCOS                R_RTC_RCR1_RTCOS /* RTCOUT Output Select */
#define RA_RTC_RCR1_PES_MASK             R_RTC_RCR1_PES_MASK
#define RA_RTC_RCR1_PES_SHIFT            R_RTC_RCR1_PES_SHIFT

/****************************************************************************
 * RCR2 Register Bit Definitions
 ****************************************************************************/

#define RA_RTC_RCR2_START                R_RTC_RCR2_START  /* RTC Start */
#define RA_RTC_RCR2_RESET                R_RTC_RCR2_RESET  /* RTC Software Reset */
#define RA_RTC_RCR2_ADJ30                R_RTC_RCR2_ADJ30  /* 30-Second Adjustment */
#define RA_RTC_RCR2_RTCOE                R_RTC_RCR2_RTCOE  /* RTCOUT Output Enable */
#define RA_RTC_RCR2_AADJE                R_RTC_RCR2_AADJE  /* Automatic Adjustment Enable */
#define RA_RTC_RCR2_AADJP                R_RTC_RCR2_AADJP  /* Automatic Adjustment Period */
#define RA_RTC_RCR2_HR24                 R_RTC_RCR2_HR24   /* 24-Hour Mode */
#define RA_RTC_RCR2_CNTMD                R_RTC_RCR2_CNTMD  /* Count Mode Select */

/****************************************************************************
 * RCR4 Register Bit Definitions
 ****************************************************************************/

#define RA_RTC_RCR4_RCKSEL               R_RTC_RCR4_RCKSEL /* Count Source Select */
#define RA_RTC_RCR4_ROPSEL               R_RTC_RCR4_ROPSEL /* RTC Operation Mode Select */

/****************************************************************************
 * Counter Register Masks
 * These are combined masks for the full BCD value in each counter register
 ****************************************************************************/

/* Second counter: 0-59 BCD (SEC10[6:4] + SEC1[3:0]) = 0x7F */

#define RA_RTC_SEC_MASK                  0x7f

/* Minute counter: 0-59 BCD (MIN10[6:4] + MIN1[3:0]) = 0x7F */

#define RA_RTC_MIN_MASK                  0x7f

/* Hour counter: 0-23 BCD (HR10[5:4] + HR1[3:0]) = 0x3F in 24-hour mode */

#define RA_RTC_HOUR_MASK                 0x3f

/* Day counter: 1-31 BCD (DATE10[5:4] + DATE1[3:0]) = 0x3F */

#define RA_RTC_MDAY_MASK                 0x3f

/* Month counter: 1-12 BCD (MON10[4] + MON1[3:0]) = 0x1F */

#define RA_RTC_MON_MASK                  0x1f

/* Year counter: 0-99 BCD (YR10[7:4] + YR1[3:0]) = 0xFF */

#define RA_RTC_YEAR_MASK                 0xff

/* Day of week: 0-6 (DAYW[2:0]) = 0x07 */

#define RA_RTC_WDAY_MASK                 0x07

/****************************************************************************
 * Alarm Register Enable Bits
 ****************************************************************************/

#define RA_RTC_ALARM_ENB                 (1 << 7)  /* Compare enable bit */

/****************************************************************************
 * RADJ Register Bit Definitions
 ****************************************************************************/

#define RA_RTC_RADJ_PMADJ_SHIFT          R_RTC_RADJ_PMADJ_SHIFT
#define RA_RTC_RADJ_PMADJ_MASK           R_RTC_RADJ_PMADJ_MASK
#define RA_RTC_RADJ_ADJ_SHIFT            R_RTC_RADJ_ADJ_SHIFT
#define RA_RTC_RADJ_ADJ_MASK             R_RTC_RADJ_ADJ_MASK

/* Error adjustment types */

#define RA_RTC_RADJ_NONE                 0  /* No adjustment */
#define RA_RTC_RADJ_ADD                  1  /* Add to prescaler */
#define RA_RTC_RADJ_SUB                  2  /* Subtract from prescaler */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* RTC alarm callback function type */

typedef void (*ra_rtc_alarm_callback_t)(void);

/* RTC configuration structure */

struct ra_rtc_config_s
{
  uint8_t clock_source;         /* Clock source selection */
  uint16_t freq_compare_value;  /* Frequency comparison value for LOCO */
  bool auto_adjustment;         /* Enable automatic time adjustment */
  uint8_t adjustment_period;    /* Adjustment period (0=1min, 1=10sec) */
  uint8_t adjustment_type;      /* Adjustment type (add/subtract) */
  uint8_t adjustment_value;     /* Adjustment value */
};

/* RTC alarm configuration structure */

struct ra_rtc_alarm_s
{
  struct tm time;               /* Alarm time */
  bool sec_match;               /* Match seconds */
  bool min_match;               /* Match minutes */
  bool hour_match;              /* Match hours */
  bool mday_match;              /* Match day of month */
  bool mon_match;               /* Match month */
  bool year_match;              /* Match year */
  bool wday_match;              /* Match day of week */
  ra_rtc_alarm_callback_t cb;   /* Alarm callback */
  void *priv;                   /* Private callback argument */
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/* RTC enabled state - defined in ra_rtc.c */

EXTERN volatile bool g_rtc_enabled;

/* Carry ISR triggered flag - for safe time reads */

EXTERN volatile bool g_rtc_carry_pending;

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: up_rtc_initialize
 *
 * Description:
 *   Initialize the RTC hardware.
 *
 * Returned Value:
 *   Zero (OK) on success; negative errno on failure.
 *
 ****************************************************************************/

int up_rtc_initialize(void);

/****************************************************************************
 * Name: up_rtc_getdatetime
 *
 * Description:
 *   Get the current date and time from the RTC.
 *
 * Input Parameters:
 *   tp - Pointer to tm structure to receive time
 *
 * Returned Value:
 *   Zero (OK) on success; negative errno on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_RTC_DATETIME
int up_rtc_getdatetime(FAR struct tm *tp);
#endif

/****************************************************************************
 * Name: up_rtc_settime
 *
 * Description:
 *   Set the RTC to the provided time.
 *
 * Input Parameters:
 *   tp - Pointer to timespec with the time to set
 *
 * Returned Value:
 *   Zero (OK) on success; negative errno on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_RTC_DATETIME
int up_rtc_settime(FAR const struct timespec *tp);
#endif

/****************************************************************************
 * Name: ra_rtc_setalarm
 *
 * Description:
 *   Set an RTC alarm.
 *
 * Input Parameters:
 *   alarm - Pointer to alarm configuration
 *
 * Returned Value:
 *   Zero (OK) on success; negative errno on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_RTC_ALARM
int ra_rtc_setalarm(FAR const struct ra_rtc_alarm_s *alarm);
#endif

/****************************************************************************
 * Name: ra_rtc_cancelalarm
 *
 * Description:
 *   Cancel the current alarm.
 *
 * Returned Value:
 *   Zero (OK) on success; negative errno on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_RTC_ALARM
int ra_rtc_cancelalarm(void);
#endif

/****************************************************************************
 * Name: ra_rtc_getalarm
 *
 * Description:
 *   Get the current alarm setting.
 *
 * Input Parameters:
 *   alarm - Pointer to receive alarm configuration
 *
 * Returned Value:
 *   Zero (OK) on success; negative errno on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_RTC_ALARM
int ra_rtc_getalarm(FAR struct ra_rtc_alarm_s *alarm);
#endif

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

#ifdef CONFIG_RA_RTC_ERROR_ADJUSTMENT
int ra_rtc_set_error_adjustment(uint8_t adjustment_type,
                                 uint8_t adjustment_value);
#endif

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

#ifdef CONFIG_RA_RTC_ERROR_ADJUSTMENT
int ra_rtc_get_error_adjustment(FAR uint8_t *adjustment_type,
                                 FAR uint8_t *adjustment_value);
#endif

/****************************************************************************
 * Name: ra_rtc_lowerhalf
 *
 * Description:
 *   Get the RTC lower half driver instance.
 *
 * Returned Value:
 *   Pointer to RTC lower half driver, or NULL on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_RTC_DRIVER
FAR struct rtc_lowerhalf_s *ra_rtc_lowerhalf(void);
#endif

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RA8_RA_RTC_H */

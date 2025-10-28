/****************************************************************************
 * arch/arm/src/ra8/hardware/ra_adc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA_ADC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA_ADC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Types
 ****************************************************************************/

#ifndef __ASSEMBLY__

/* ADC Resolution enumeration */

enum ra8_adc_resolution_e
{
  RA_ADC_RESOLUTION_12BIT = 0,  /* 12-bit resolution */
  RA_ADC_RESOLUTION_10BIT = 1,  /* 10-bit resolution */
  RA_ADC_RESOLUTION_8BIT  = 2,  /* 8-bit resolution */
  RA_ADC_RESOLUTION_14BIT = 3,  /* 14-bit resolution */
  RA_ADC_RESOLUTION_16BIT = 4,  /* 16-bit resolution */
};

/* ADC Scan Mode enumeration */

enum ra8_adc_mode_e
{
  RA_ADC_MODE_SINGLE_SCAN = 0,  /* Single scan mode */
  RA_ADC_MODE_GROUP_SCAN  = 1,  /* Group scan mode */
  RA_ADC_MODE_CONTINUOUS  = 2,  /* Continuous scan mode */
};

/* ADC Trigger Source enumeration */

enum ra8_adc_trigger_e
{
  RA_ADC_TRIGGER_SOFTWARE = 0,    /* Software trigger */
  RA_ADC_TRIGGER_SYNC_ELC = 2,    /* Synchronous trigger via ELC */
  RA_ADC_TRIGGER_ASYNC_EXT = 3,   /* External asynchronous trigger */
};

/* ADC Data Alignment enumeration */

enum ra8_adc_alignment_e
{
  RA_ADC_ALIGNMENT_RIGHT = 0,  /* Right-aligned data */
  RA_ADC_ALIGNMENT_LEFT  = 1,  /* Left-aligned data */
};


/* ADC channel definitions for RA8P1 */
#define RA_ADC_CHANNEL_AN000        0    /* AN000 - Battery voltage */
#define RA_ADC_CHANNEL_AN001        1    /* AN001 */
#define RA_ADC_CHANNEL_AN002        2    /* AN002 */
#define RA_ADC_CHANNEL_AN003        3    /* AN003 */
#define RA_ADC_CHANNEL_AN004        4    /* AN004 */
#define RA_ADC_CHANNEL_AN005        5    /* AN005 */
#define RA_ADC_CHANNEL_AN104        104  /* AN104 - Battery current (ACS712) */

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA_ADC_H */

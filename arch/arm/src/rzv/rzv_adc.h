/****************************************************************************
 * arch/arm/src/rzv/rzv_adc.h
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

#ifndef __ARCH_ARM_SRC_RZV_RZV_ADC_H
#define __ARCH_ARM_SRC_RZV_RZV_ADC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ADC resolution options for RZV2H ADC_E */

#define RZV_ADC_RESOLUTION_12BIT    0   /* 12-bit resolution (default) */
#define RZV_ADC_RESOLUTION_10BIT    1   /* 10-bit resolution */
#define RZV_ADC_RESOLUTION_8BIT     2   /* 8-bit resolution */

/* ADC scan mode options */

#define RZV_ADC_MODE_SINGLE         0   /* Single scan mode */
#define RZV_ADC_MODE_CONTINUOUS     1   /* Continuous scan mode */
#define RZV_ADC_MODE_GROUP_SCAN     2   /* Group scan mode */

/* ADC trigger source */

#define RZV_ADC_TRIGGER_SOFTWARE    0   /* Software trigger */
#define RZV_ADC_TRIGGER_SYNC_TRGA   1   /* Synchronous trigger A */
#define RZV_ADC_TRIGGER_SYNC_TRGB   2   /* Synchronous trigger B */
#define RZV_ADC_TRIGGER_ELC         3   /* ELC event trigger */

/* Maximum ADC channels for RZV2H ADC_E */

#define RZV_ADC_MAX_CHANNELS        8   /* Channels 0-7 */

/****************************************************************************
 * Public Types
 ****************************************************************************/

#ifndef __ASSEMBLY__

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Name: rzv_adc_initialize
 *
 * Description:
 *   Initialize the ADC peripheral and register it with the upper-half
 *   ADC driver.
 *
 * Input Parameters:
 *   devpath   - The device path (e.g., "/dev/adc0")
 *   chanlist  - Array of channel numbers to enable
 *   nchannels - Number of channels in the list
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int rzv_adc_initialize(const char *devpath, const uint8_t *chanlist,
                       int nchannels);

#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RZV_RZV_ADC_H */

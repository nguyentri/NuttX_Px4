/****************************************************************************
 * arch/arm/src/ra8/ra_adc.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_ADC_H
#define __ARCH_ARM_SRC_RA8_RA_ADC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>
#include <stdint.h>
#include <stdbool.h>
#include <nuttx/analog/adc.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ADC resolution enumeration for type safety */
#define RA_ADC_RESOLUTION_16BIT     0
#define RA_ADC_RESOLUTION_14BIT     1
#define RA_ADC_RESOLUTION_12BIT     2
#define RA_ADC_RESOLUTION_10BIT     3

/* ADC scan mode enumeration */
#define RA_ADC_MODE_SINGLE_SCAN     0
#define RA_ADC_MODE_CONTINUOUS_SCAN 1
#define RA_ADC_MODE_BACKGROUND_SCAN 2

/* ADC conversion method */
#define RA_ADC_METHOD_SAR           0
#define RA_ADC_METHOD_OVERSAMPLE    1
#define RA_ADC_METHOD_HYBRID        2

/* ADC trigger source */
#define RA_ADC_TRIGGER_SOFTWARE     0
#define RA_ADC_TRIGGER_SYNC_ELC     1
#define RA_ADC_TRIGGER_ASYNC_EXT    2
#define RA_ADC_TRIGGER_GPT          3

/* ADC data alignment */
#define RA_ADC_ALIGNMENT_RIGHT      0
#define RA_ADC_ALIGNMENT_LEFT       1

/* ADC channel definitions for RA8P1 */
#define RA_ADC_CHANNEL_AN000        0    /* AN000 - Battery voltage */
#define RA_ADC_CHANNEL_AN001        1    /* AN001 */
#define RA_ADC_CHANNEL_AN002        2    /* AN002 */
#define RA_ADC_CHANNEL_AN003        3    /* AN003 */
#define RA_ADC_CHANNEL_AN004        4    /* AN004 */
#define RA_ADC_CHANNEL_AN005        5    /* AN005 */
#define RA_ADC_CHANNEL_AN104        104  /* AN104 - Battery current (ACS712) */

/****************************************************************************
 * Public Types
 ****************************************************************************/

#ifndef __ASSEMBLY__

/* ADC channel configuration */
struct ra8_adc_chan_cfg_s
{
  uint8_t  vchannel;        /* Virtual channel number (0-95) */
  uint8_t  pchannel;        /* Physical channel number (0-47) */
  uint8_t  scan_group_id;   /* Scan group ID (0-8) */
  uint8_t  sampling_table;  /* Sampling state table ID (0-7) */
  uint16_t resolution;      /* ADC resolution */
  bool     differential;    /* Differential mode */
};
/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Name: ra8_adc_b_initialize
 *
 * Description:
 *   Initialize the ADC-B subsystem for RA8P1
 *
 * Input Parameters:
 *   chanlist - Bit mask of channels to enable
 *   nchannels - Number of configured channels
 *
 * Returned Value:
 *   Valid ADC device structure reference on success; NULL on failure
 *
 ****************************************************************************/

FAR struct adc_dev_s *ra8_adc_b_initialize(uint32_t chanlist,
                                           int nchannels);

#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RA8_RA_ADC_H */

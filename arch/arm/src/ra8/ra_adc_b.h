/****************************************************************************
 * arch/arm/src/ra8/ra_adc_b.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_ADC_B_H
#define __ARCH_ARM_SRC_RA8_RA_ADC_B_H

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

/* ADC-B resolution options */

#define RA_ADC_RESOLUTION_16BIT     0   /* 16-bit resolution */
#define RA_ADC_RESOLUTION_14BIT     1   /* 14-bit resolution */
#define RA_ADC_RESOLUTION_12BIT     2   /* 12-bit resolution */
#define RA_ADC_RESOLUTION_10BIT     3   /* 10-bit resolution */

/* ADC-B scan mode options */

#define RA_ADC_MODE_SINGLE_SCAN     0   /* Single scan mode */
#define RA_ADC_MODE_CONTINUOUS_SCAN 1   /* Continuous scan mode */
#define RA_ADC_MODE_BACKGROUND_SCAN 2   /* Background continuous scan */

/* ADC-B conversion method */

#define RA_ADC_METHOD_SAR           0   /* SAR (Successive Approximation) */
#define RA_ADC_METHOD_OVERSAMPLE    1   /* Oversampling mode */
#define RA_ADC_METHOD_HYBRID        2   /* Hybrid mode */

/* ADC-B trigger source */

#define RA_ADC_TRIGGER_SOFTWARE     0   /* Software trigger */
#define RA_ADC_TRIGGER_SYNC_ELC     1   /* Synchronous ELC trigger */
#define RA_ADC_TRIGGER_ASYNC_EXT    2   /* Asynchronous external trigger */
#define RA_ADC_TRIGGER_GPT          3   /* GPT trigger */

/* ADC-B data alignment */

#define RA_ADC_ALIGNMENT_RIGHT      0   /* Right-aligned data */
#define RA_ADC_ALIGNMENT_LEFT       1   /* Left-aligned data */

/* ADC-B maximum values */

#define RA_ADC_B_MAX_CHANNELS       33  /* Maximum virtual channels */
#define RA_ADC_B_MAX_SCAN_GROUPS    9   /* Maximum scan groups (0-8) */
#define RA_ADC_B_FIFO_DEPTH         16  /* FIFO depth per scan group */

/* ADC-B physical channel definitions for RA8P1
 * These correspond to ANxxx pins on the device
 */

/* ADC Unit 0 Channels (AN000-AN022) */

#define RA_ADC_CHANNEL_AN000        0    /* AN000 - P004 */
#define RA_ADC_CHANNEL_AN001        1    /* AN001 - P003 */
#define RA_ADC_CHANNEL_AN002        2    /* AN002 - P002 */
#define RA_ADC_CHANNEL_AN003        3    /* AN003 - P001 */
#define RA_ADC_CHANNEL_AN004        4    /* AN004 - P000 */
#define RA_ADC_CHANNEL_AN005        5    /* AN005 - P015 */
#define RA_ADC_CHANNEL_AN006        6    /* AN006 - P014 */
#define RA_ADC_CHANNEL_AN007        7    /* AN007 - P013 */
#define RA_ADC_CHANNEL_AN008        8    /* AN008 - P012 */
#define RA_ADC_CHANNEL_AN009        9    /* AN009 - P011 */
#define RA_ADC_CHANNEL_AN010        10   /* AN010 - P010 */
#define RA_ADC_CHANNEL_AN011        11   /* AN011 - P508 */
#define RA_ADC_CHANNEL_AN012        12   /* AN012 - P507 */
#define RA_ADC_CHANNEL_AN013        13   /* AN013 - P506 */
#define RA_ADC_CHANNEL_AN014        14   /* AN014 - P505 */
#define RA_ADC_CHANNEL_AN015        15   /* AN015 - P504 */
#define RA_ADC_CHANNEL_AN016        16   /* AN016 - P503 */
#define RA_ADC_CHANNEL_AN017        17   /* AN017 - P502 */
#define RA_ADC_CHANNEL_AN018        18   /* AN018 - P501 */
#define RA_ADC_CHANNEL_AN019        19   /* AN019 - P500 */
#define RA_ADC_CHANNEL_AN020        20   /* AN020 - P915 */
#define RA_ADC_CHANNEL_AN021        21   /* AN021 - P914 */
#define RA_ADC_CHANNEL_AN022        22   /* AN022 - P913 */

/* ADC Unit 1 Channels (AN100-AN122) - mapped to virtual channels 100+ */

#define RA_ADC_CHANNEL_AN100        100  /* AN100 - P004 (shared) */
#define RA_ADC_CHANNEL_AN101        101  /* AN101 - P003 (shared) */
#define RA_ADC_CHANNEL_AN102        102  /* AN102 - P002 (shared) */
#define RA_ADC_CHANNEL_AN103        103  /* AN103 - P001 (shared) */
#define RA_ADC_CHANNEL_AN104        104  /* AN104 - P000 (shared) */

/* Extended analog channels */

#define RA_ADC_CHANNEL_TEMP_SENSOR  32   /* Temperature sensor */
#define RA_ADC_CHANNEL_VREF         33   /* Internal reference voltage */

/****************************************************************************
 * Public Types
 ****************************************************************************/

#ifndef __ASSEMBLY__

/* ADC-B resolution enumeration */

enum ra_adc_b_resolution_e
{
  ADC_B_RESOLUTION_16BIT = RA_ADC_RESOLUTION_16BIT,
  ADC_B_RESOLUTION_14BIT = RA_ADC_RESOLUTION_14BIT,
  ADC_B_RESOLUTION_12BIT = RA_ADC_RESOLUTION_12BIT,
  ADC_B_RESOLUTION_10BIT = RA_ADC_RESOLUTION_10BIT,
};

/* ADC-B scan mode enumeration */

enum ra_adc_b_mode_e
{
  ADC_B_MODE_SINGLE     = RA_ADC_MODE_SINGLE_SCAN,
  ADC_B_MODE_CONTINUOUS = RA_ADC_MODE_CONTINUOUS_SCAN,
  ADC_B_MODE_BACKGROUND = RA_ADC_MODE_BACKGROUND_SCAN,
};

/* ADC-B trigger source enumeration */

enum ra_adc_b_trigger_e
{
  ADC_B_TRIGGER_SOFTWARE = RA_ADC_TRIGGER_SOFTWARE,
  ADC_B_TRIGGER_ELC      = RA_ADC_TRIGGER_SYNC_ELC,
  ADC_B_TRIGGER_EXT      = RA_ADC_TRIGGER_ASYNC_EXT,
  ADC_B_TRIGGER_GPT      = RA_ADC_TRIGGER_GPT,
};

/* ADC-B channel configuration structure */

struct ra_adc_b_chan_cfg_s
{
  uint8_t  vchannel;        /* Virtual channel number (0-32) */
  uint8_t  pchannel;        /* Physical channel number (AN pin) */
  uint8_t  scan_group_id;   /* Scan group ID (0-8) */
  uint8_t  sampling_table;  /* Sampling state table ID (0-15) */
  uint8_t  resolution;      /* ADC resolution (RA_ADC_RESOLUTION_*) */
  bool     differential;    /* Differential mode flag */
  bool     sample_hold;     /* Use sample-and-hold circuit */
};

/* ADC-B extended configuration structure */

struct ra_adc_b_config_s
{
  uint8_t  resolution;      /* Default resolution */
  uint8_t  scan_mode;       /* Scan mode (single/continuous) */
  uint8_t  trigger_source;  /* Trigger source */
  uint8_t  adc_unit;        /* ADC unit (0 or 1) */
  uint16_t sampling_time;   /* Sampling time in ADCLK cycles */
  uint16_t conversion_time; /* Conversion time in ADCLK cycles */
  bool     calibrate;       /* Perform calibration on setup */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Name: ra8_adc_initialize
 *
 * Description:
 *   Initialize the ADC-B subsystem for RA8P1
 *
 * Input Parameters:
 *   channels  - Array of channel configuration structures
 *   nchannels - Number of configured channels
 *
 * Returned Value:
 *   Valid ADC device structure reference on success; NULL on failure
 *
 ****************************************************************************/

FAR struct adc_dev_s *ra8_adc_initialize(
    FAR const struct ra_adc_b_chan_cfg_s *channels, int nchannels);

/****************************************************************************
 * Name: ra8_adc_set_resolution
 *
 * Description:
 *   Set the ADC resolution
 *
 * Input Parameters:
 *   dev        - ADC device structure
 *   resolution - Resolution setting (RA_ADC_RESOLUTION_*)
 *
 * Returned Value:
 *   OK on success; negative errno on failure
 *
 ****************************************************************************/

int ra8_adc_set_resolution(FAR struct adc_dev_s *dev, uint8_t resolution);

/****************************************************************************
 * Name: ra8_adc_set_scan_mode
 *
 * Description:
 *   Set the ADC scan mode
 *
 * Input Parameters:
 *   dev  - ADC device structure
 *   mode - Scan mode (RA_ADC_MODE_*)
 *
 * Returned Value:
 *   OK on success; negative errno on failure
 *
 ****************************************************************************/

int ra8_adc_set_scan_mode(FAR struct adc_dev_s *dev, uint8_t mode);

/****************************************************************************
 * Name: ra8_adc_set_averaging
 *
 * Description:
 *   Set the number of samples to average
 *
 * Input Parameters:
 *   dev   - ADC device structure
 *   count - Number of samples to average (1, 2, 4, 8, 16, 32, 64, etc.)
 *
 * Returned Value:
 *   OK on success; negative errno on failure
 *
 ****************************************************************************/

int ra8_adc_set_averaging(FAR struct adc_dev_s *dev, uint16_t count);

/****************************************************************************
 * Name: ra8_adc_enable_fifo
 *
 * Description:
 *   Enable FIFO mode for burst sampling
 *
 * Input Parameters:
 *   dev    - ADC device structure
 *   enable - true to enable, false to disable
 *
 * Returned Value:
 *   OK on success; negative errno on failure
 *
 ****************************************************************************/

int ra8_adc_enable_fifo(FAR struct adc_dev_s *dev, bool enable);

/****************************************************************************
 * Name: ra8_adc_configure_gpt_trigger
 *
 * Description:
 *   Configure GPT (timer) hardware trigger for PWM-synchronized sampling
 *
 * Input Parameters:
 *   dev         - ADC device structure
 *   gpt_channel - GPT channel number (0-13)
 *   use_cmpb    - Use Compare Match B instead of A
 *
 * Returned Value:
 *   OK on success; negative errno on failure
 *
 ****************************************************************************/

int ra8_adc_configure_gpt_trigger(FAR struct adc_dev_s *dev,
                                  uint8_t gpt_channel, bool use_cmpb);

/****************************************************************************
 * Name: ra8_adc_configure_elc_trigger
 *
 * Description:
 *   Configure ELC (Event Link Controller) hardware trigger
 *
 * Input Parameters:
 *   dev       - ADC device structure
 *   elc_event - ELC event number to trigger on
 *
 * Returned Value:
 *   OK on success; negative errno on failure
 *
 ****************************************************************************/

int ra8_adc_configure_elc_trigger(FAR struct adc_dev_s *dev,
                                  uint16_t elc_event);

/****************************************************************************
 * Name: ra8_adc_enable_hw_trigger
 *
 * Description:
 *   Enable hardware triggering (must configure trigger source first)
 *
 * Input Parameters:
 *   dev    - ADC device structure
 *   enable - true to enable, false to disable
 *
 * Returned Value:
 *   OK on success; negative errno on failure
 *
 ****************************************************************************/

int ra8_adc_enable_hw_trigger(FAR struct adc_dev_s *dev, bool enable);

/****************************************************************************
 * Name: ra8_adc_read_sync
 *
 * Description:
 *   Perform a synchronous (blocking) ADC read
 *
 * Input Parameters:
 *   dev     - ADC device structure
 *   channel - Physical channel to read
 *   value   - Pointer to store the result
 *
 * Returned Value:
 *   OK on success; negative errno on failure
 *
 ****************************************************************************/

int ra8_adc_read_sync(FAR struct adc_dev_s *dev, uint8_t channel,
                      FAR int32_t *value);

/****************************************************************************
 * Name: ra8_adc_get_fullcount
 *
 * Description:
 *   Get the full-scale count for the configured resolution
 *
 * Input Parameters:
 *   dev - ADC device structure
 *
 * Returned Value:
 *   Full-scale count value
 *
 ****************************************************************************/

uint32_t ra8_adc_get_fullcount(FAR struct adc_dev_s *dev);

#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RA8_RA_ADC_B_H */

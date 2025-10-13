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

#ifndef __ARCH_ARM_SRC_RA_RA8_ADC_B_H
#define __ARCH_ARM_SRC_RA_RA8_ADC_B_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* ADC channel configuration */

struct ra8_adc_b_chan_cfg_s
{
  uint8_t  vchannel;        /* Virtual channel number (0-95) */
  uint8_t  pchannel;        /* Physical channel number (0-47) */
  uint8_t  scan_group_id;   /* Scan group ID (0-8) */
  uint8_t  sampling_table;  /* Sampling state table ID (0-7) */
  uint32_t resolution;      /* ADC resolution */
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
 * Public Types
 ****************************************************************************/

#ifndef __ASSEMBLY__

/* ADC_B Resolution enumeration */

enum ra8_adc_b_resolution_e
{
  RA_ADC_B_RESOLUTION_16BIT = 0,  /* 16-bit resolution */
  RA_ADC_B_RESOLUTION_14BIT = 1,  /* 14-bit resolution */
  RA_ADC_B_RESOLUTION_12BIT = 2,  /* 12-bit resolution */
  RA_ADC_B_RESOLUTION_10BIT = 3,  /* 10-bit resolution */
};

/* ADC_B Scan Mode enumeration */

enum ra8_adc_b_mode_e
{
  RA_ADC_B_MODE_SINGLE_SCAN = 0,     /* Single scan mode */
  RA_ADC_B_MODE_CONTINUOUS_SCAN = 1, /* Continuous scan mode */
  RA_ADC_B_MODE_BACKGROUND_SCAN = 2, /* Background scan mode (Hybrid only) */
};

/* ADC_B Conversion Method enumeration */

enum ra8_adc_b_method_e
{
  RA_ADC_B_METHOD_SAR = 0,        /* SAR conversion method */
  RA_ADC_B_METHOD_OVERSAMPLE = 1, /* Oversampling conversion method */
  RA_ADC_B_METHOD_HYBRID = 2,     /* Hybrid conversion method */
};

/* ADC_B Trigger Source enumeration */

enum ra8_adc_b_trigger_e
{
  RA_ADC_B_TRIGGER_SOFTWARE = 0,  /* Software trigger */
  RA_ADC_B_TRIGGER_SYNC_ELC = 1,  /* Synchronous trigger via ELC */
  RA_ADC_B_TRIGGER_ASYNC_EXT = 2, /* External asynchronous trigger */
  RA_ADC_B_TRIGGER_GPT = 3,       /* GPT trigger */
};

#endif /* __ASSEMBLY__ */

/****************************************************************************
 * Name: ra8_adc_b_initialize
 *
 * Description:
 *   Initialize the ADC_B subsystem for RA8P1
 *
 * Input Parameters:
 *   chanlist - Bit mask of channels to enable
 *   nchannels - Number of channels enabled
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

#endif /* __ARCH_ARM_SRC_RA_RA8_ADC_B_H */

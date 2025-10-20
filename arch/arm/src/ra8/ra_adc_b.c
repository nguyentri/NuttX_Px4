/****************************************************************************
 * arch/arm/src/ra8/ra_adc.c
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
#include <nuttx/analog/adc.h>

#ifdef CONFIG_RA_ADC_B

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Minimal stub file - board-level ADC setup in ra8p1_adc_b.c handles
 * the actual ADC-B initialization and device registration.
 */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra8_adc_b_initialize
 *
 * Description:
 *   Initialize the ADC-B subsystem for RA8P1. This is a compatibility
 *   stub that delegates to board-level implementation.
 *
 * Input Parameters:
 *   chanlist  - Bit mask of channels to enable
 *   nchannels - Number of configured channels
 *
 * Returned Value:
 *   Valid ADC device structure reference on success; NULL on failure
 *
 ****************************************************************************/

FAR struct adc_dev_s *ra8_adc_b_initialize(uint32_t chanlist,
                                           int nchannels)
{
  ainfo("ADC-B: ra8_adc_b_initialize called (chanlist=0x%08lx, nchannels=%d)\n",
        chanlist, nchannels);

  /* Note: The actual ADC-B device initialization and registration is
   * performed by board_adc_initialize() in ra8p1_adc_b.c, which is called
   * during board startup from ra8p1_bringup.c. This function exists to
   * provide a standard architecture-level interface point.
   */

  return NULL;
}

#endif /* CONFIG_RA_ADC_B */


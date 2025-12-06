/****************************************************************************
 * arch/arm/src/ra8/ra_clock.h
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

#ifndef __ARCH_ARM_SRC_RA_CLOCK_H
#define __ARCH_ARM_SRC_RA_CLOCK_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

#include "hardware/ra_clock.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Peripheral Clock IDs for ra_get_peripheral_clock() */

#define RA_PCLK_ICLK        0   /* System clock (ICK) */
#define RA_PCLK_PCLKA       1   /* Peripheral Clock A */
#define RA_PCLK_PCLKB       2   /* Peripheral Clock B */
#define RA_PCLK_PCLKC       3   /* Peripheral Clock C */
#define RA_PCLK_PCLKD       4   /* Peripheral Clock D */
#define RA_PCLK_PCLKE       5   /* Peripheral Clock E */
#define RA_PCLK_BCLK        6   /* External bus clock */
#define RA_PCLK_FCLK        7   /* Flash interface clock */
#define RA_PCLK_SCICLK      8   /* SCI clock */
#define RA_PCLK_SPICLK      9   /* SPI clock */
#define RA_PCLK_CANFDCLK    10  /* CANFD clock */
#define RA_PCLK_GPTCLK      11  /* GPT clock */
#define RA_PCLK_IICCLK      12  /* IIC (I2C) clock */
#define RA_PCLK_ADCCLK      13  /* ADC clock */
#define RA_PCLK_OCTACLK     14  /* OSPI clock */
#define RA_PCLK_LCDCLK      15  /* LCD clock */
#define RA_PCLK_I3CCLK      16  /* I3C clock */
#define RA_PCLK_USB60CLK    17  /* USB 60MHz clock */
#define RA_PCLK_ESWCLK      18  /* Ethernet Switch clock */
#define RA_PCLK_ESWPHYCLK   19  /* Ethernet Switch PHY clock */
#define RA_PCLK_ETHPHYCLK   20  /* Ethernet PHY clock */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* Clock Configuration Structure */

typedef struct
{
  uint32_t system_clock_freq;
  uint32_t cpu_clock_freq;
  uint32_t iclk_freq;
  uint32_t pclka_freq;
  uint32_t pclkb_freq;
  uint32_t pclkc_freq;
  uint32_t pclkd_freq;
  uint32_t pclke_freq;
  uint32_t bclk_freq;
  uint32_t fclk_freq;
  uint32_t sciclk_freq;
  uint32_t hoco_frequency;
  uint8_t clock_source;
  bool hoco_enabled;
  bool moco_enabled;
  bool pll_enabled;
} ra_clock_config_t;

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* System core clock variable */
extern uint32_t g_sys_core_clock;

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifndef __ASSEMBLY__

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Name: ra_clock
 *
 * Description:
 *   Called to initialize the RA clocks. This does whatever setup is needed
 *   to put the SoC in a usable state using clock initialization sequence.
 *   initialization sequence.
 *
 ****************************************************************************/

void ra_clock(void);

/****************************************************************************
 * Name: ra_sys_core_clock_update
 *
 * Description:
 *   Update the system core clock frequency based on current clock settings.
 *
 ****************************************************************************/

void ra_sys_core_clock_update(void);

/****************************************************************************
 * Name: ra_get_clock_config
 *
 * Description:
 *   Get current clock configuration
 *
 ****************************************************************************/

void ra_get_clock_config(ra_clock_config_t *config);

/****************************************************************************
 * Name: ra_print_clock_info
 *
 * Description:
 *   Print Clock information for debugging
 *
 ****************************************************************************/

void ra_print_clock_info(void);

/****************************************************************************
 * Name: ra_get_peripheral_clock
 *
 * Description:
 *   Get peripheral clock frequency
 *
 ****************************************************************************/

uint32_t ra_get_peripheral_clock(int peripheral_id);

#ifdef __cplusplus
}
#endif
#undef EXTERN

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RA_CLOCK_H */

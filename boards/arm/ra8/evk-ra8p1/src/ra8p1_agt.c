/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_agt.c
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
#include <stdint.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/timers/timer.h>

#include "ra_agt.h"
#include "hardware/ra_memorymap.h"
#include <arch/ra8/ra8p1_irq.h>

#ifdef CONFIG_RA8_AGT

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* AGT base addresses for RA8P1 */

#define RA8P1_AGT0_BASE   0x40221000
#define RA8P1_AGT1_BASE   0x40221100
#define RA8P1_AGT2_BASE   0x40221200
#define RA8P1_AGT3_BASE   0x40221300
#define RA8P1_AGT4_BASE   0x40221400
#define RA8P1_AGT5_BASE   0x40221500
#define RA8P1_AGT6_BASE   0x40221600

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* AGT channel configurations for EVK-RA8P1 */

#ifdef CONFIG_RA8_AGT0
static const struct ra_agt_config_s g_agt0_config =
{
  .channel = 0,
  .base    = RA8P1_AGT0_BASE,
  .clock   = RA_AGT_CLOCK_PCLKB,
  .divider = 3,  /* /8 divider for ~15 MHz from 120 MHz PCLKB */
  .is_agtw = false,
  .elc_int = RA_ELC_AGT0_INT,
};
#endif

#ifdef CONFIG_RA8_AGT1
static const struct ra_agt_config_s g_agt1_config =
{
  .channel = 1,
  .base    = RA8P1_AGT1_BASE,
  .clock   = RA_AGT_CLOCK_LOCO,
  .divider = 5,  /* /32 divider for ~1 kHz from 32 kHz LOCO */
  .is_agtw = false,
  .elc_int = RA_ELC_AGT1_INT,
};
#endif

#ifdef CONFIG_RA8_AGT2
static const struct ra_agt_config_s g_agt2_config =
{
  .channel = 2,
  .base    = RA8P1_AGT2_BASE,
  .clock   = RA_AGT_CLOCK_PCLKB,
  .divider = 3,  /* /8 divider */
  .is_agtw = false,
  .elc_int = 0x08C,  /* AGT2_INT event */
};
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_agt_board_initialize
 *
 * Description:
 *   Initialize AGT timers for the board
 *
 ****************************************************************************/

int ra_agt_board_initialize(void)
{
  struct ra_agt_priv_s *priv;
  int ret = OK;

#ifdef CONFIG_RA8_AGT0
  tmrinfo("Initializing AGT0\n");
  priv = ra_agt_initialize(&g_agt0_config);
  if (priv == NULL)
    {
      tmrerr("ERROR: Failed to initialize AGT0\n");
      ret = -ENODEV;
    }
  else
    {
      tmrinfo("AGT0 initialized successfully\n");
    }
#endif

#ifdef CONFIG_RA8_AGT1
  tmrinfo("Initializing AGT1\n");
  priv = ra_agt_initialize(&g_agt1_config);
  if (priv == NULL)
    {
      tmrerr("ERROR: Failed to initialize AGT1\n");
      ret = -ENODEV;
    }
  else
    {
      tmrinfo("AGT1 initialized successfully\n");
    }
#endif

#ifdef CONFIG_RA8_AGT2
  tmrinfo("Initializing AGT2\n");
  priv = ra_agt_initialize(&g_agt2_config);
  if (priv == NULL)
    {
      tmrerr("ERROR: Failed to initialize AGT2\n");
      ret = -ENODEV;
    }
  else
    {
      tmrinfo("AGT2 initialized successfully\n");
    }
#endif

  return ret;
}

#endif /* CONFIG_RA8_AGT */

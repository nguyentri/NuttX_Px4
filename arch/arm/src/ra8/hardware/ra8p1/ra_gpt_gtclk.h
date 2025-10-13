/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_gpt_gtclk.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_GTCLK_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_GTCLK_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPT_GTCLK Base Address */
#ifndef R_GPT_GTCLK_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_GPT_GTCLK_BASE           0x40323f10
#else
#define R_GPT_GTCLK_BASE           0x50323f10
#endif
#endif

/* GPT_GTCLK Register Offsets */

#define R_GPT_GTCLK_GTCLKCR_OFFSET     0x00000000  /* General PWM Timer Clock Control Register */

/* GPT_GTCLK Register Addresses */

#define R_GPT_GTCLK_GTCLKCR                 (R_GPT_GTCLK_BASE + R_GPT_GTCLK_GTCLKCR_OFFSET)

/* Register bit definitions */
/* GTCLKCR Register bit definitions */
#define R_GPT_GTCLK_GTCLKCR_BPEN                  (1 << 0)  /* Synchronization Circuit Bypass Enable */


/* Maximum number of channels */

#define GPT_GTCLK_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_GTCLK_H */

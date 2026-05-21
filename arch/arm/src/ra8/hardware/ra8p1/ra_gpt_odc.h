/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_gpt_odc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_ODC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_ODC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPT_ODC Base Address */
#ifndef R_GPT_ODC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_GPT_ODC_BASE           0x40324000
#else
#define R_GPT_ODC_BASE           0x50324000
#endif
#endif

/* GPT_ODC Register Offsets */

#define R_GPT_ODC_GTDLYCR1_OFFSET                 0x00000000  /* PWM Output Delay Control Register1 */
#define R_GPT_ODC_GTDLYCR2_OFFSET                 0x00000002  /* PWM Output Delay Control Register2 */
/* GTDLYR[%s] Registers () */
#define R_GPT_ODC_GTDLYR_OFFSET(m)                (0x00000018 + ((m) * 0x00000004))  /* PWM DELAY RISING */
#define R_GPT_ODC_GTDLYF_OFFSET                   0x00000028  /* PWM DELAY FALLING */

/* GPT_ODC Register Addresses */

#define R_GPT_ODC_GTDLYCR1                        (R_GPT_ODC_BASE + R_GPT_ODC_GTDLYCR1_OFFSET)
#define R_GPT_ODC_GTDLYCR2                        (R_GPT_ODC_BASE + R_GPT_ODC_GTDLYCR2_OFFSET)
#define R_GPT_ODC_GTDLYR(m)                       (R_GPT_ODC_BASE + R_GPT_ODC_GTDLYR_OFFSET(m))
#define R_GPT_ODC_GTDLYF                          (R_GPT_ODC_BASE + R_GPT_ODC_GTDLYF_OFFSET)

/* Register bit definitions */
/* GTDLYCR1 Register bit definitions */
#define R_GPT_ODC_GTDLYCR1_FRANGE_SHIFT           (8)  /* GPT core clock Frequency Range */
#define R_GPT_ODC_GTDLYCR1_FRANGE_MASK            0x300

#define R_GPT_ODC_GTDLYCR1_DLYRST                 (1 << 1)  /* PWM Delay Generation Circuit Reset */

#define R_GPT_ODC_GTDLYCR1_DLLEN                  (1 << 0)  /* DLL Operation Enable */

/* GTDLYCR2 Register bit definitions */
#define R_GPT_ODC_GTDLYCR2_DLYDENB_S              (1 << 12)  /* PWM Delay Generation Circuit Disenable for GTIOCB */

#define R_GPT_ODC_GTDLYCR2_DLYEN_S                (1 << 8)  /* PWM Delay Generation Circuit enable */

#define R_GPT_ODC_GTDLYCR2_DLYBS_S                (1 << 0)  /* PWM Delay Generation Circuit bypass */

#define R_GPT_ODC_GTDLYCR2_DLYBS0                 (1 << 0)  /* PWM Delay Generation Circuit bypass */

#define R_GPT_ODC_GTDLYCR2_DLYBS1                 (1 << 1)  /* PWM Delay Generation Circuit bypass */

#define R_GPT_ODC_GTDLYCR2_DLYBS2                 (1 << 2)  /* PWM Delay Generation Circuit bypass */

#define R_GPT_ODC_GTDLYCR2_DLYBS3                 (1 << 3)  /* PWM Delay Generation Circuit bypass */

#define R_GPT_ODC_GTDLYCR2_DLYEN0                 (1 << 8)  /* PWM Delay Generation Circuit enable */

#define R_GPT_ODC_GTDLYCR2_DLYEN1                 (1 << 9)  /* PWM Delay Generation Circuit enable */

#define R_GPT_ODC_GTDLYCR2_DLYEN2                 (1 << 10)  /* PWM Delay Generation Circuit enable */

#define R_GPT_ODC_GTDLYCR2_DLYEN3                 (1 << 11)  /* PWM Delay Generation Circuit enable */

#define R_GPT_ODC_GTDLYCR2_DLYDENB0               (1 << 12)  /* PWM Delay Generation Circuit Disenable for GTIOCB */


/* Maximum number of channels */

#define GPT_ODC_MAX_CHANNELS    4

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_ODC_H */

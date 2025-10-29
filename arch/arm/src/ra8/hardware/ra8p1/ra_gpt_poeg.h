/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_gpt_poeg.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_POEG_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_POEG_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPT_POEG Base Address */
#ifndef R_GPT_POEG_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_GPT_POEG_BASE           0x40212000
#else
#define R_GPT_POEG_BASE           0x50212000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_GPT_POEG_CH_STRIDE    0x00000100
#define R_GPT_POEG_CH_BASE(ch)   (R_GPT_POEG_BASE + ((uint32_t)(ch) * R_GPT_POEG_CH_STRIDE))

/* GPT_POEG Register Offsets */

#define R_GPT_POEG_POEGG_OFFSET                   0x00000000  /* POEG Group Setting Register */
#define R_GPT_POEG_GTONCWP_OFFSET                 0x00000040  /* GPT Output Stopping Control Group Write Protection Register */
#define R_GPT_POEG_GTONCCR_OFFSET                 0x00000044  /* GPT Output Stopping Control Group Controlling Register */

/* GPT_POEG Register Addresses */

#define R_GPT_POEG_POEGG(n)                       (R_GPT_POEG_CH_BASE(n) + R_GPT_POEG_POEGG_OFFSET)
#define R_GPT_POEG_GTONCWP(n)                     (R_GPT_POEG_CH_BASE(n) + R_GPT_POEG_GTONCWP_OFFSET)
#define R_GPT_POEG_GTONCCR(n)                     (R_GPT_POEG_CH_BASE(n) + R_GPT_POEG_GTONCCR_OFFSET)

/* Register bit definitions */
/* POEGG Register bit definitions */
#define R_GPT_POEG_POEGG_NFCS_SHIFT               (30)  /* Noise Filter Clock Select */
#define R_GPT_POEG_POEGG_NFCS_MASK                0xc0000000
#  define R_GPT_POEG_POEGG_NFCS_00                        (0 << R_GPT_POEG_POEGG_NFCS_SHIFT)  /* Sampling GTETRG pin input level for three times in every PCLKB.  */
#  define R_GPT_POEG_POEGG_NFCS_01                        (1 << R_GPT_POEG_POEGG_NFCS_SHIFT)  /* Sampling GTETRG pin input level for three times in every PCLKB /8. */
#  define R_GPT_POEG_POEGG_NFCS_10                        (2 << R_GPT_POEG_POEGG_NFCS_SHIFT)  /* Sampling GTETRG pin input level for three times in every PCLKB /32. */
#  define R_GPT_POEG_POEGG_NFCS_11                        (3 << R_GPT_POEG_POEGG_NFCS_SHIFT)  /* Sampling GTETRG pin input level for three times in every PCLKB /128.  */

#define R_GPT_POEG_POEGG_NFEN                     (1 << 29)  /* Noise Filter Enable */

#define R_GPT_POEG_POEGG_INV                      (1 << 28)  /* GTETRG Input Reverse */

#define R_GPT_POEG_POEGG_ST                       (1 << 16)  /* GTETRG Input Status Flag */

#define R_GPT_POEG_POEGG_CDRE_S                   (1 << 8)  /* Comparator Disable Request Enable. Note: Can be modified only once after a reset. */

#define R_GPT_POEG_POEGG_OSTPE                    (1 << 6)  /* Oscillation Stop Detection Enable. Note: Can be modified only once after a reset. */

#define R_GPT_POEG_POEGG_IOCE                     (1 << 5)  /* Enable for GPT Output-Disable Request. Note: Can be modified only once after a reset. */

#define R_GPT_POEG_POEGG_PIDE                     (1 << 4)  /* Port Input Detection Enable. Note: Can be modified only once after a reset. */

#define R_GPT_POEG_POEGG_SSF                      (1 << 3)  /* Software Stop Flag */

#define R_GPT_POEG_POEGG_OSTPF                    (1 << 2)  /* Oscillation Stop Detection Flag */

#define R_GPT_POEG_POEGG_IOCF                     (1 << 1)  /* Real Time Overcurrent Detection Flag */

#define R_GPT_POEG_POEGG_PIDF                     (1 << 0)  /* Port Input Detection Flag */

#define R_GPT_POEG_POEGG_CDRE0                    (1 << 8)  /* Comparator Disable Request Enable. Note: Can be modified only once after a reset. */

#define R_GPT_POEG_POEGG_CDRE1                    (1 << 9)  /* Comparator Disable Request Enable. Note: Can be modified only once after a reset. */

#define R_GPT_POEG_POEGG_CDRE2                    (1 << 10)  /* Comparator Disable Request Enable. Note: Can be modified only once after a reset. */

#define R_GPT_POEG_POEGG_CDRE3                    (1 << 11)  /* Comparator Disable Request Enable. Note: Can be modified only once after a reset. */

#define R_GPT_POEG_POEGG_CDRE4                    (1 << 12)  /* Comparator Disable Request Enable. Note: Can be modified only once after a reset. */

#define R_GPT_POEG_POEGG_CDRE5                    (1 << 13)  /* Comparator Disable Request Enable. Note: Can be modified only once after a reset. */

/* GTONCWP Register bit definitions */
#define R_GPT_POEG_GTONCWP_WP                     (1 << 0)  /* Register Writing Disable */

#define R_GPT_POEG_GTONCWP_PRKEY_SHIFT            (8)  /* Key Code */
#define R_GPT_POEG_GTONCWP_PRKEY_MASK             0xff00

/* GTONCCR Register bit definitions */
#define R_GPT_POEG_GTONCCR_NE                     (1 << 0)  /* Direct Stopping Request Setting */

#define R_GPT_POEG_GTONCCR_NFS_SHIFT              (4)  /* Direct Stopping Request Selection */
#define R_GPT_POEG_GTONCCR_NFS_MASK               0xf0

#define R_GPT_POEG_GTONCCR_NFV                    (1 << 8)  /* Direct Stopping Request Active Sense */


/* Maximum number of channels */

#define GPT_POEG_MAX_CHANNELS    4

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_POEG_H */

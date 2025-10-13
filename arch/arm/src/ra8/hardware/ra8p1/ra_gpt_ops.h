/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_gpt_ops.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_OPS_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_OPS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPT_OPS Base Address */
#ifndef R_GPT_OPS_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_GPT_OPS_BASE           0x40323f00
#else
#define R_GPT_OPS_BASE           0x50323f00
#endif
#endif

/* GPT_OPS Register Offsets */

#define R_GPT_OPS_OPSCR_OFFSET                    0x00000000  /* Output Phase Switching Control Register */

/* GPT_OPS Register Addresses */

#define R_GPT_OPS_OPSCR                           (R_GPT_OPS_BASE + R_GPT_OPS_OPSCR_OFFSET)

/* Register bit definitions */
/* OPSCR Register bit definitions */
#define R_GPT_OPS_OPSCR_UF                        (1 << 0)  /*  */

#define R_GPT_OPS_OPSCR_VF                        (1 << 1)  /*  */

#define R_GPT_OPS_OPSCR_WF                        (1 << 2)  /*  */

#define R_GPT_OPS_OPSCR_U                         (1 << 4)  /* Input U-Phase Monitor */

#define R_GPT_OPS_OPSCR_V                         (1 << 5)  /* Input V-Phase Monitor */

#define R_GPT_OPS_OPSCR_W                         (1 << 6)  /* Input W-Phase Monitor */

#define R_GPT_OPS_OPSCR_EN                        (1 << 8)  /* Output Phase Enable */

#define R_GPT_OPS_OPSCR_FB                        (1 << 16)  /* External Feedback Signal Enable */

#define R_GPT_OPS_OPSCR_P                         (1 << 17)  /* Positive-Phase Output (P) Control */

#define R_GPT_OPS_OPSCR_N                         (1 << 18)  /* Negative-Phase Output (N) Control */

#define R_GPT_OPS_OPSCR_INV                       (1 << 19)  /* Output Phase Invert Control */

#define R_GPT_OPS_OPSCR_RV                        (1 << 20)  /* Output Phase Rotation Direction Reversal Control */

#define R_GPT_OPS_OPSCR_ALIGN                     (1 << 21)  /* Input Phase Alignment */

#define R_GPT_OPS_OPSCR_GRP_SHIFT                 (24)  /* Output Disabled Source Selection */
#define R_GPT_OPS_OPSCR_GRP_MASK                  0x3000000

#define R_GPT_OPS_OPSCR_GODF                      (1 << 26)  /* Group Output Disable Function */

#define R_GPT_OPS_OPSCR_NFEN                      (1 << 29)  /* External Input Noise Filter Enable */

#define R_GPT_OPS_OPSCR_NFCS_SHIFT                (30)  /* External Input Noise Filter Clock Selection */
#define R_GPT_OPS_OPSCR_NFCS_MASK                 0xc0000000
#  define R_GPT_OPS_OPSCR_NFCS_00                         (0 << R_GPT_OPS_OPSCR_NFCS_SHIFT)  /* GTCLK/1 */
#  define R_GPT_OPS_OPSCR_NFCS_01                         (1 << R_GPT_OPS_OPSCR_NFCS_SHIFT)  /* GTCLK/4 */
#  define R_GPT_OPS_OPSCR_NFCS_10                         (2 << R_GPT_OPS_OPSCR_NFCS_SHIFT)  /* GTCLK/16 */
#  define R_GPT_OPS_OPSCR_NFCS_11                         (3 << R_GPT_OPS_OPSCR_NFCS_SHIFT)  /* GTCLK/64 */


/* Maximum number of channels */

#define GPT_OPS_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_OPS_H */

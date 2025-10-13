/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_pdg.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PDG_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PDG_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* PDG Base Address */
#ifndef R_PDG_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_PDG_BASE           0x40324000
#else
#define R_PDG_BASE           0x50324000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_PDG_CH_STRIDE    0x00000004
#define R_PDG_CH_BASE(ch)   (R_PDG_BASE + ((uint32_t)(ch) * R_PDG_CH_STRIDE))

/* PDG Register Offsets */

#define R_PDG_GTDLYCR_OFFSET     0x00000000  /* PWM Output Delay Control Register */
#define R_PDG_GTDLYCR2_OFFSET     0x00000002  /* PWM Output Delay Control Register 2 */
/* GTDLYR%sA Registers (0-3) */
#define R_PDG_GTDLYR0A_OFFSET     0x00000018  /* GTIOCnA Rising Output Delay Register */
#define R_PDG_GTDLYR1A_OFFSET     0x0000001c  /* GTIOCnA Rising Output Delay Register */
#define R_PDG_GTDLYR2A_OFFSET     0x00000020  /* GTIOCnA Rising Output Delay Register */
#define R_PDG_GTDLYR3A_OFFSET     0x00000024  /* GTIOCnA Rising Output Delay Register */
/* GTDLYR%sB Registers (0-3) */
#define R_PDG_GTDLYR0B_OFFSET     0x0000001a  /* GTIOCnB Rising Output Delay Register */
#define R_PDG_GTDLYR1B_OFFSET     0x0000001e  /* GTIOCnB Rising Output Delay Register */
#define R_PDG_GTDLYR2B_OFFSET     0x00000022  /* GTIOCnB Rising Output Delay Register */
#define R_PDG_GTDLYR3B_OFFSET     0x00000026  /* GTIOCnB Rising Output Delay Register */
/* GTDLYF%sA Registers (0-3) */
#define R_PDG_GTDLYF0A_OFFSET     0x00000028  /* GTIOCnA Falling Output Delay Register */
#define R_PDG_GTDLYF1A_OFFSET     0x0000002c  /* GTIOCnA Falling Output Delay Register */
#define R_PDG_GTDLYF2A_OFFSET     0x00000030  /* GTIOCnA Falling Output Delay Register */
#define R_PDG_GTDLYF3A_OFFSET     0x00000034  /* GTIOCnA Falling Output Delay Register */
/* GTDLYF%sB Registers (0-3) */
#define R_PDG_GTDLYF0B_OFFSET     0x0000002a  /* GTIOCnB Falling Output Delay Register */
#define R_PDG_GTDLYF1B_OFFSET     0x0000002e  /* GTIOCnB Falling Output Delay Register */
#define R_PDG_GTDLYF2B_OFFSET     0x00000032  /* GTIOCnB Falling Output Delay Register */
#define R_PDG_GTDLYF3B_OFFSET     0x00000036  /* GTIOCnB Falling Output Delay Register */

/* PDG Register Addresses */

#define R_PDG_GTDLYCR                 (R_PDG_BASE + R_PDG_GTDLYCR_OFFSET)
#define R_PDG_GTDLYCR2                 (R_PDG_BASE + R_PDG_GTDLYCR2_OFFSET)
#define R_PDG_GTDLYR0A                 (R_PDG_BASE + R_PDG_GTDLYR0A_OFFSET)
#define R_PDG_GTDLYR1A                 (R_PDG_BASE + R_PDG_GTDLYR1A_OFFSET)
#define R_PDG_GTDLYR2A                 (R_PDG_BASE + R_PDG_GTDLYR2A_OFFSET)
#define R_PDG_GTDLYR3A                 (R_PDG_BASE + R_PDG_GTDLYR3A_OFFSET)
#define R_PDG_GTDLYR0B                 (R_PDG_BASE + R_PDG_GTDLYR0B_OFFSET)
#define R_PDG_GTDLYR1B                 (R_PDG_BASE + R_PDG_GTDLYR1B_OFFSET)
#define R_PDG_GTDLYR2B                 (R_PDG_BASE + R_PDG_GTDLYR2B_OFFSET)
#define R_PDG_GTDLYR3B                 (R_PDG_BASE + R_PDG_GTDLYR3B_OFFSET)
#define R_PDG_GTDLYF0A                 (R_PDG_BASE + R_PDG_GTDLYF0A_OFFSET)
#define R_PDG_GTDLYF1A                 (R_PDG_BASE + R_PDG_GTDLYF1A_OFFSET)
#define R_PDG_GTDLYF2A                 (R_PDG_BASE + R_PDG_GTDLYF2A_OFFSET)
#define R_PDG_GTDLYF3A                 (R_PDG_BASE + R_PDG_GTDLYF3A_OFFSET)
#define R_PDG_GTDLYF0B                 (R_PDG_BASE + R_PDG_GTDLYF0B_OFFSET)
#define R_PDG_GTDLYF1B                 (R_PDG_BASE + R_PDG_GTDLYF1B_OFFSET)
#define R_PDG_GTDLYF2B                 (R_PDG_BASE + R_PDG_GTDLYF2B_OFFSET)
#define R_PDG_GTDLYF3B                 (R_PDG_BASE + R_PDG_GTDLYF3B_OFFSET)

/* Register bit definitions */
/* GTDLYCR Register bit definitions */
#define R_PDG_GTDLYCR_DLLEN                       (1 << 0)  /* DLL Operation Enable */

#define R_PDG_GTDLYCR_DLYRST                      (1 << 1)  /* PWM Delay Generation Circuit Reset */

#define R_PDG_GTDLYCR_FRANGE_SHIFT                (8)  /* GPT core clock Frequency Range */
#define R_PDG_GTDLYCR_FRANGE_MASK                 0x300
#  define R_PDG_GTDLYCR_FRANGE_00                         (0 << R_PDG_GTDLYCR_FRANGE_SHIFT)  /* GPT core clock frequency is 80 MHz to 160 MHz */
#  define R_PDG_GTDLYCR_FRANGE_01                         (1 << R_PDG_GTDLYCR_FRANGE_SHIFT)  /* GPT core clock frequency is 155 MHz to 300 MHz */

/* GTDLYCR2 Register bit definitions */
#define R_PDG_GTDLYCR2_DLYBS0                     (1 << 0)  /* PWM Delay Generation Circuit bypass for channel 0 */

#define R_PDG_GTDLYCR2_DLYBS1                     (1 << 1)  /* PWM Delay Generation Circuit bypass for channel 1 */

#define R_PDG_GTDLYCR2_DLYBS2                     (1 << 2)  /* PWM Delay Generation Circuit bypass for channel 2 */

#define R_PDG_GTDLYCR2_DLYBS3                     (1 << 3)  /* PWM Delay Generation Circuit bypass for channel 3 */

#define R_PDG_GTDLYCR2_DLYEN0                     (1 << 8)  /* PWM Delay Generation Circuit enable for channel 0 */

#define R_PDG_GTDLYCR2_DLYEN1                     (1 << 9)  /* PWM Delay Generation Circuit enable for channel 1 */

#define R_PDG_GTDLYCR2_DLYEN2                     (1 << 10)  /* PWM Delay Generation Circuit enable for channel 2 */

#define R_PDG_GTDLYCR2_DLYEN3                     (1 << 11)  /* PWM Delay Generation Circuit enable for channel 3 */

/* GTDLYRA Register bit definitions */
#define R_PDG_GTDLYRA_DLY_SHIFT                   (0)  /* GTIOCnA Output Rising Edge Delay Setting */
#define R_PDG_GTDLYRA_DLY_MASK                    0x7f

/* GTDLYRB Register bit definitions */
#define R_PDG_GTDLYRB_DLY_SHIFT                   (0)  /* GTIOCnB Output Rising Edge Delay Setting */
#define R_PDG_GTDLYRB_DLY_MASK                    0x7f

/* GTDLYFA Register bit definitions */
#define R_PDG_GTDLYFA_DLY_SHIFT                   (0)  /* GTIOCnA Output Falling Edge Delay Setting */
#define R_PDG_GTDLYFA_DLY_MASK                    0x7f

/* GTDLYFB Register bit definitions */
#define R_PDG_GTDLYFB_DLY_SHIFT                   (0)  /* GTIOCnB Output Falling Edge Delay Setting */
#define R_PDG_GTDLYFB_DLY_MASK                    0x7f


/* Maximum number of channels */

#define PDG_MAX_CHANNELS    4

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PDG_H */

/****************************************************************************
 * arch/arm/src/ra8/hardware/ra_dac.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA_DAC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA_DAC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DAC Base Address */
#ifndef RA_DAC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define RA_DAC_BASE           0x40333000
#else
#define RA_DAC_BASE           0x50333000
#endif
#endif

#define RA_DAC_CH_BASE(ch)   (RA_DAC_BASE + ((uint32_t)(ch) * RA_DAC_CH_STRIDE))

/* DAC Register Offsets */

/* DADR%s Registers (0) */
#define RA_DAC_DADR0_OFFSET     0x00000000  /* D/A Data Register 0 */
#define RA_DAC_DACR_OFFSET     0x00000004  /* D/A Control Register */
#define RA_DAC_DADPR_OFFSET     0x00000005  /* DADRn Format Select Register */
#define RA_DAC_DAADSCR_OFFSET     0x00000006  /* D/A A/D Synchronous Start Control Register */
#define RA_DAC_DAAMPCR_OFFSET     0x00000008  /* D/A Output Amplifier Control Register */
#define RA_DAC_DAASWCR_OFFSET     0x0000001c  /* D/A Amplifier Stabilization Wait Control Register */
#define RA_DAC_DAADUSR_OFFSET     0x000010c0  /* D/A A/D Synchronous Unit Select Register */

/* Register bit definitions */
/* DACR Register bit definitions */
#define DAC_DACR_DAOE0          (1 << 6)  /* D/A Output Enable 0 */

/* DADPR Register bit definitions */
#define DAC_DADPR_DPSEL          (1 << 7)  /* DADRn Format Select */

/* DAADSCR Register bit definitions */
#define DAC_DAADSCR_DAADST          (1 << 7)  /* D/A A/D Synchronous Conversion */

/* DAAMPCR Register bit definitions */
#define DAC_DAAMPCR_DAAMP0          (1 << 6)  /* Amplifier Control 0 */

/* DAASWCR Register bit definitions */
#define DAC_DAASWCR_DAASW0          (1 << 6)  /* D/A Amplifier Stabilization Wait 0 and D/A internal output control */

/* DAADUSR Register bit definitions */
#define DAC_DAADUSR_AMADSEL1          (1 << 1)  /* A/D Unit 1 Select */


/* Maximum number of channels */

#define DAC_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA_DAC_H */

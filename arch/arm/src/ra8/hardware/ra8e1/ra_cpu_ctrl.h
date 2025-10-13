/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_cpu_ctrl.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CPU_CTRL_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CPU_CTRL_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CPU_CTRL Base Address */
#ifndef R_CPU_CTRL_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_CPU_CTRL_BASE           0x4000f000
#else
#define R_CPU_CTRL_BASE           0x5000f000
#endif
#endif

/* CPU_CTRL Register Offsets */

#define R_CPU_CTRL_CPULCKUPCR_OFFSET              0x00000030  /* CPU Lockup Control Register */
#define R_CPU_CTRL_CPULOCKCR_OFFSET               0x00000400  /* CPU Function Lock Control Register */
#define R_CPU_CTRL_CPUCRPT_OFFSET                 0x00000840  /* CPU Control Register Protection Register */

/* CPU_CTRL Register Addresses */

#define R_CPU_CTRL_CPULCKUPCR                     (R_CPU_CTRL_BASE + R_CPU_CTRL_CPULCKUPCR_OFFSET)
#define R_CPU_CTRL_CPULOCKCR                      (R_CPU_CTRL_BASE + R_CPU_CTRL_CPULOCKCR_OFFSET)
#define R_CPU_CTRL_CPUCRPT                        (R_CPU_CTRL_BASE + R_CPU_CTRL_CPUCRPT_OFFSET)

/* Register bit definitions */
/* CPULCKUPCR Register bit definitions */
#define R_CPU_CTRL_CPULCKUPCR_OAD                 (1 << 0)  /* Operation after detection of CPU lockup */

/* CPULOCKCR Register bit definitions */
#define R_CPU_CTRL_CPULOCKCR_LCKSVTAIR            (1 << 0)  /* Disable writes to the following secure registers from software or from a debug agent that is connected to the processor: */

#define R_CPU_CTRL_CPULOCKCR_LCKSMPU              (1 << 1)  /* Disable writes to registers that are associated with the Secure MPU region from software or from a debug agent connected to the processor: */

#define R_CPU_CTRL_CPULOCKCR_LCKSAU               (1 << 2)  /* Disable writes to registers that are associated with the SAU region from software or from a debug agent connected to the processor: */

#define R_CPU_CTRL_CPULOCKCR_LCKITGU              (1 << 3)  /* Disable writes to registers that are associated with the ITCM interface security gating from software or from a debug agent connected to the processor: */

#define R_CPU_CTRL_CPULOCKCR_LCKDTGU              (1 << 4)  /* Disable writes to registers that are associated with the DTCM interface security gating from software or from a debug agent connected to the processor: */

#define R_CPU_CTRL_CPULOCKCR_LCKDCAIC             (1 << 5)  /*  */

/* CPUCRPT Register bit definitions */
#define R_CPU_CTRL_CPUCRPT_PROTECT                (1 << 0)  /* Protection of register */

#define R_CPU_CTRL_CPUCRPT_KEY_SHIFT              (8)  /* The KEY[7:0] bits enable or disable writing to the PROTECT bit. */
#define R_CPU_CTRL_CPUCRPT_KEY_MASK               0xff00


/* Maximum number of channels */

#define CPU_CTRL_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CPU_CTRL_H */

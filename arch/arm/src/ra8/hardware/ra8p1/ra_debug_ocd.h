/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_debug_ocd.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DEBUG_OCD_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DEBUG_OCD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DEBUG_OCD Base Address */
#ifndef R_DEBUG_OCD_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_DEBUG_OCD_BASE           0x40011000
#else
#define R_DEBUG_OCD_BASE           0x50011000
#endif
#endif

/* DEBUG_OCD Register Offsets */

#define R_DEBUG_OCD_MCUERRSTAT_OFFSET             0x00000000  /* MCU Error Status Register */
#define R_DEBUG_OCD_MCUCTRL_OFFSET                0x00000004  /* MCU Control Register */
#define R_DEBUG_OCD_JBMDR_OFFSET                  0x00000100  /* JTAG Boot Mode Entry Register */
#define R_DEBUG_OCD_JBRDR_OFFSET                  0x00000120  /* JTAG Boot Receive Data Register */
#define R_DEBUG_OCD_JBTDR_OFFSET                  0x00000130  /* JTAG Boot Transmit Data Register */
#define R_DEBUG_OCD_JBSTR_OFFSET                  0x00000140  /* JTAG Boot Status Register */
#define R_DEBUG_OCD_JBICR_OFFSET                  0x00000150  /* JTAG Boot Interrupt Control Register */
#define R_DEBUG_OCD_FSBLSTATM_OFFSET              0x00000300  /* First Stage Boot Loader Status Monitor Register */

/* DEBUG_OCD Register Addresses */

#define R_DEBUG_OCD_MCUERRSTAT                    (R_DEBUG_OCD_BASE + R_DEBUG_OCD_MCUERRSTAT_OFFSET)
#define R_DEBUG_OCD_MCUCTRL                       (R_DEBUG_OCD_BASE + R_DEBUG_OCD_MCUCTRL_OFFSET)
#define R_DEBUG_OCD_JBMDR                         (R_DEBUG_OCD_BASE + R_DEBUG_OCD_JBMDR_OFFSET)
#define R_DEBUG_OCD_JBRDR                         (R_DEBUG_OCD_BASE + R_DEBUG_OCD_JBRDR_OFFSET)
#define R_DEBUG_OCD_JBTDR                         (R_DEBUG_OCD_BASE + R_DEBUG_OCD_JBTDR_OFFSET)
#define R_DEBUG_OCD_JBSTR                         (R_DEBUG_OCD_BASE + R_DEBUG_OCD_JBSTR_OFFSET)
#define R_DEBUG_OCD_JBICR                         (R_DEBUG_OCD_BASE + R_DEBUG_OCD_JBICR_OFFSET)
#define R_DEBUG_OCD_FSBLSTATM                     (R_DEBUG_OCD_BASE + R_DEBUG_OCD_FSBLSTATM_OFFSET)

/* Register bit definitions */
/* MCUERRSTAT Register bit definitions */
#define R_DEBUG_OCD_MCUERRSTAT_ZERO               (1 << 0)  /* Zeroization status flag */

/* MCUCTRL Register bit definitions */
#define R_DEBUG_OCD_MCUCTRL_EDBGRQ0               (1 << 0)  /* External Debug Request for CPU0 */

#define R_DEBUG_OCD_MCUCTRL_EDBGRQ1               (1 << 1)  /* External Debug Request for CPU1 */

#define R_DEBUG_OCD_MCUCTRL_DBIRQ0                (1 << 8)  /* Writing 1 to the bit wakes up the CPU0 from Deep Sleep mode or the MCU from Software Standby Mode or Deep Software Standby mode */

#define R_DEBUG_OCD_MCUCTRL_DBIRQ1                (1 << 9)  /* Writing 1 to the bit wakes up the CPU1 from Deep Sleep mode or the MCU from Software Standby Mode or Deep Software Standby mode */

#define R_DEBUG_OCD_MCUCTRL_CPUWAIT0              (1 << 16)  /* CPU0 WAIT SETTING */

#define R_DEBUG_OCD_MCUCTRL_CPUWAIT1              (1 << 17)  /* CPU1 WAIT SETTING */

/* JBMDR Register bit definitions */
#define R_DEBUG_OCD_JBMDR_KEY_SHIFT               (0)  /* Mode entry key */
#define R_DEBUG_OCD_JBMDR_KEY_MASK                0xff

/* JBRDR Register bit definitions */
#define R_DEBUG_OCD_JBRDR_RDAT_SHIFT              (0)  /* Received data register */
#define R_DEBUG_OCD_JBRDR_RDAT_MASK               0xffffffff

/* JBTDR Register bit definitions */
#define R_DEBUG_OCD_JBTDR_TDAT_SHIFT              (0)  /* Transmitted data register */
#define R_DEBUG_OCD_JBTDR_TDAT_MASK               0xffffffff

/* JBSTR Register bit definitions */
#define R_DEBUG_OCD_JBSTR_RDF                     (1 << 0)  /* Receive buffer full */

#define R_DEBUG_OCD_JBSTR_TDE                     (1 << 1)  /* Transmit data empty */

/* JBICR Register bit definitions */
#define R_DEBUG_OCD_JBICR_RDFIE                   (1 << 0)  /* Receive buffer full interrupt enabled */

/* FSBLSTATM Register bit definitions */
#define R_DEBUG_OCD_FSBLSTATM_CS                  (1 << 0)  /* FSBL completion status */

#define R_DEBUG_OCD_FSBLSTATM_RS                  (1 << 1)  /* FSBL result status */


/* Maximum number of channels */

#define DEBUG_OCD_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DEBUG_OCD_H */

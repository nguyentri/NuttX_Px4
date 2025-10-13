/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_ocd_cpu.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_OCD_CPU_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_OCD_CPU_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* OCD_CPU Base Address */
#ifndef R_OCD_CPU_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_OCD_CPU_BASE           0x40011000
#else
#define R_OCD_CPU_BASE           0x50011000
#endif
#endif

/* OCD_CPU Register Offsets */

#define R_OCD_CPU_MCUCTRL_OFFSET                  0x00000004  /* MCU Control Register */
#define R_OCD_CPU_JBMDR_OFFSET                    0x00000100  /* JTAG Boot Mode Entry Register */
#define R_OCD_CPU_JBRDR_OFFSET                    0x00000120  /* JTAG Boot Receive Data Register */
#define R_OCD_CPU_JBTDR_OFFSET                    0x00000130  /* JTAG Boot Transmit Data Register */
#define R_OCD_CPU_JBSTR_OFFSET                    0x00000140  /* JTAG Boot Status Register */
#define R_OCD_CPU_JBICR_OFFSET                    0x00000150  /* JTAG Boot Interrupt Control Register */

/* OCD_CPU Register Addresses */

#define R_OCD_CPU_MCUCTRL                         (R_OCD_CPU_BASE + R_OCD_CPU_MCUCTRL_OFFSET)
#define R_OCD_CPU_JBMDR                           (R_OCD_CPU_BASE + R_OCD_CPU_JBMDR_OFFSET)
#define R_OCD_CPU_JBRDR                           (R_OCD_CPU_BASE + R_OCD_CPU_JBRDR_OFFSET)
#define R_OCD_CPU_JBTDR                           (R_OCD_CPU_BASE + R_OCD_CPU_JBTDR_OFFSET)
#define R_OCD_CPU_JBSTR                           (R_OCD_CPU_BASE + R_OCD_CPU_JBSTR_OFFSET)
#define R_OCD_CPU_JBICR                           (R_OCD_CPU_BASE + R_OCD_CPU_JBICR_OFFSET)

/* Register bit definitions */
/* MCUCTRL Register bit definitions */
#define R_OCD_CPU_MCUCTRL_EDBGRQ                  (1 << 0)  /* External Debug Request. Writing 1 to the bit causes a CPU Halt or Debug Monitor exception request. */

#define R_OCD_CPU_MCUCTRL_CPUWAIT                 (1 << 16)  /*  */

/* JBMDR Register bit definitions */
#define R_OCD_CPU_JBMDR_KEY_SHIFT                 (0)  /* Mode entry key */
#define R_OCD_CPU_JBMDR_KEY_MASK                  0xff

/* JBRDR Register bit definitions */
#define R_OCD_CPU_JBRDR_RDAT_SHIFT                (0)  /* Received data register */
#define R_OCD_CPU_JBRDR_RDAT_MASK                 0xffffffff

/* JBTDR Register bit definitions */
#define R_OCD_CPU_JBTDR_TDAT_SHIFT                (0)  /* Transmitted data register */
#define R_OCD_CPU_JBTDR_TDAT_MASK                 0xffffffff

/* JBSTR Register bit definitions */
#define R_OCD_CPU_JBSTR_RDF                       (1 << 0)  /* Receive buffer full */

#define R_OCD_CPU_JBSTR_TDE                       (1 << 1)  /* Transmit data empty */

/* JBICR Register bit definitions */
#define R_OCD_CPU_JBICR_RDFIE                     (1 << 0)  /* Receive buffer full interrupt enabled */


/* Maximum number of channels */

#define OCD_CPU_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_OCD_CPU_H */

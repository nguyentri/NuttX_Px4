/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_pmisc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PMISC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PMISC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* PMISC Base Address */
#ifndef R_PMISC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_PMISC_BASE           0x40400d00
#else
#define R_PMISC_BASE           0x50400d00
#endif
#endif

/* PMISC Register Offsets */

#define R_PMISC_PFENET_OFFSET                     0x00000000  /* Ethernet Control Register */
#define R_PMISC_PWPR_OFFSET                       0x0000000c  /* Write-Protect Register  */
#define R_PMISC_PWPRS_OFFSET                      0x00000014  /* Write-Protect Register for Secure  */
/* PMSAR[%s] Registers () */
#define R_PMISC_PMSAR_OFFSET(m)                   (0x00000030 + ((m) * 0x00000004))  /* Port Security Attribution Register */

/* PMISC Register Addresses */

#define R_PMISC_PFENET                            (R_PMISC_BASE + R_PMISC_PFENET_OFFSET)
#define R_PMISC_PWPR                              (R_PMISC_BASE + R_PMISC_PWPR_OFFSET)
#define R_PMISC_PWPRS                             (R_PMISC_BASE + R_PMISC_PWPRS_OFFSET)
#define R_PMISC_PMSAR(m)                          (R_PMISC_BASE + R_PMISC_PMSAR_OFFSET(m))

/* Register bit definitions */
/* PFENET Register bit definitions */
#define R_PMISC_PFENET_PHYMODE0                   (1 << 4)  /* Ethernet Mode Setting ch0 */

#define R_PMISC_PFENET_PHYMODE1                   (1 << 5)  /* Ethernet Mode Setting ch1 */

/* PWPR Register bit definitions */
#define R_PMISC_PWPR_PFSWE                        (1 << 6)  /* PmnPFS Register Write */

#define R_PMISC_PWPR_B0WI                         (1 << 7)  /* PFSWE Bit Write Disable */

/* PWPRS Register bit definitions */
#define R_PMISC_PWPRS_PFSWE                       (1 << 6)  /* PmnPFS Register Write */

#define R_PMISC_PWPRS_B0WI                        (1 << 7)  /* PFSWE Bit Write Disable */


/* Maximum number of channels */

#define PMISC_MAX_CHANNELS    15

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PMISC_H */

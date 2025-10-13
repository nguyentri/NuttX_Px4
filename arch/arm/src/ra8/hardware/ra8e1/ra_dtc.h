/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8e1/ra_dtc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_DTC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_DTC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DTC Base Address */
#ifndef R_DTC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_DTC_BASE           0x4000ac00
#else
#define R_DTC_BASE           0x5000ac00
#endif
#endif

/* DTC Register Offsets */

#define R_DTC_DTCST_OFFSET                        0x0000000c  /* DTC Module Start Register */
#define R_DTC_DTCSTS_OFFSET                       0x0000000e  /* DTC Status Register */
#define R_DTC_DTCCR_SEC_OFFSET                    0x00000010  /* DTC Control Register for Secure Region */
#define R_DTC_DTCVBR_SEC_OFFSET                   0x00000014  /* DTC Vector Base Register for Secure Region */
#define R_DTC_DTEVR_OFFSET                        0x00000020  /* DTC Error Vector Register */

/* DTC Register Addresses */

#define R_DTC_DTCST                               (R_DTC_BASE + R_DTC_DTCST_OFFSET)
#define R_DTC_DTCSTS                              (R_DTC_BASE + R_DTC_DTCSTS_OFFSET)
#define R_DTC_DTCCR_SEC                           (R_DTC_BASE + R_DTC_DTCCR_SEC_OFFSET)
#define R_DTC_DTCVBR_SEC                          (R_DTC_BASE + R_DTC_DTCVBR_SEC_OFFSET)
#define R_DTC_DTEVR                               (R_DTC_BASE + R_DTC_DTEVR_OFFSET)

/* Register bit definitions */
/* DTCST Register bit definitions */
#define R_DTC_DTCST_DTCST                         (1 << 0)  /* DTC Module Start */

/* DTCSTS Register bit definitions */
#define R_DTC_DTCSTS_VECN_SHIFT                   (0)  /* DTC-Activating Vector Number Monitoring */
#define R_DTC_DTCSTS_VECN_MASK                    0xff

#define R_DTC_DTCSTS_ACT                          (1 << 15)  /* DTC Active Flag */

/* DTCCR_SEC Register bit definitions */
#define R_DTC_DTCCR_SEC_RRSS                      (1 << 4)  /* DTC Transfer Information Read Skip Enable for Secure */

#define R_DTC_DTCCR_SEC_RRS                       (1 << 4)  /* DTC Transfer Information Read Skip Enable. */

/* DTCVBR_SEC Register bit definitions */
#define R_DTC_DTCVBR_SEC_DTCVBR_SHIFT             (0)  /* DTC Vector Base Address. */
#define R_DTC_DTCVBR_SEC_DTCVBR_MASK              0xffffffff

/* DTEVR Register bit definitions */
#define R_DTC_DTEVR_DTEV_SHIFT                    (0)  /* DTC Error Vector Number */
#define R_DTC_DTEVR_DTEV_MASK                     0xff

#define R_DTC_DTEVR_DTEVSAM                       (1 << 8)  /* DTC Error Vector Number SA Monitor */

#define R_DTC_DTEVR_DTESTA                        (1 << 16)  /* DTC Error Status Flag */


/* Maximum number of channels */

#define DTC_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_DTC_H */

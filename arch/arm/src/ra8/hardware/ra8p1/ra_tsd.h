/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_tsd.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_TSD_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_TSD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* TSD Base Address */
#ifndef R_TSD_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_TSD_BASE           0x02c1eda0
#else
#define R_TSD_BASE           0x12c1eda0
#endif
#endif

/* TSD Register Offsets */

#define R_TSD_TSCDR_OFFSET                        0x00000000  /* Temperature Sensor Calibration Data Register */
#define R_TSD_TSCDR2_OFFSET                       0x00000004  /* Temperature Sensor Calibration Data Register 2 */

/* TSD Register Addresses */

#define R_TSD_TSCDR                               (R_TSD_BASE + R_TSD_TSCDR_OFFSET)
#define R_TSD_TSCDR2                              (R_TSD_BASE + R_TSD_TSCDR2_OFFSET)

/* Register bit definitions */
/* TSCDR Register bit definitions */
#define R_TSD_TSCDR_TSCD_SHIFT                    (0)  /* Temperature Sensor Calibration Data */
#define R_TSD_TSCDR_TSCD_MASK                     0xffff

/* TSCDR2 Register bit definitions */
#define R_TSD_TSCDR2_TSCD_SHIFT                   (0)  /* Temperature Sensor Calibration Data */
#define R_TSD_TSCDR2_TSCD_MASK                    0xffff


/* Maximum number of channels */

#define TSD_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_TSD_H */

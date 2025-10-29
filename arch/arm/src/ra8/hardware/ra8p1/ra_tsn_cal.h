/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_tsn_cal.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_TSN_CAL_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_TSN_CAL_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* TSN_CAL Base Address */
#ifndef R_TSN_CAL_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_TSN_CAL_BASE           0x02c1eda0
#else
#define R_TSN_CAL_BASE           0x12c1eda0
#endif
#endif

/* TSN_CAL Register Offsets */

#define R_TSN_CAL_TSCDR_OFFSET                    0x00000000  /* Temperature Sensor 32 bit Calibration Data Register */

/* TSN_CAL Register Addresses */

#define R_TSN_CAL_TSCDR                           (R_TSN_CAL_BASE + R_TSN_CAL_TSCDR_OFFSET)

/* Register bit definitions */
/* TSCDR Register bit definitions */
#define R_TSN_CAL_TSCDR_TSCDR_SHIFT               (0)  /* The 32 bit TSCDR register stores temperature sensor calibration converted value. */
#define R_TSN_CAL_TSCDR_TSCDR_MASK                0xffffffff


/* Maximum number of channels */

#define TSN_CAL_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_TSN_CAL_H */

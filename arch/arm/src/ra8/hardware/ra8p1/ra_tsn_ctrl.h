/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_tsn_ctrl.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_TSN_CTRL_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_TSN_CTRL_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* TSN_CTRL Base Address */
#ifndef R_TSN_CTRL_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_TSN_CTRL_BASE           0x40235000
#else
#define R_TSN_CTRL_BASE           0x50235000
#endif
#endif

/* TSN_CTRL Register Offsets */

#define R_TSN_CTRL_TSCR_OFFSET                    0x00000000  /* Temperature Sensor Control Register */

/* TSN_CTRL Register Addresses */

#define R_TSN_CTRL_TSCR                           (R_TSN_CTRL_BASE + R_TSN_CTRL_TSCR_OFFSET)

/* Register bit definitions */
/* TSCR Register bit definitions */
#define R_TSN_CTRL_TSCR_TSEN                      (1 << 7)  /* Temperature Sensor Output Enable */

#define R_TSN_CTRL_TSCR_TSOE                      (1 << 4)  /* Temperature Sensor Enable */


/* Maximum number of channels */

#define TSN_CTRL_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_TSN_CTRL_H */

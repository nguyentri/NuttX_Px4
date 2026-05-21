/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8e1/ra_flad.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_FLAD_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_FLAD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* FLAD Base Address */
#ifndef R_FLAD_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_FLAD_BASE           0x4011c000
#else
#define R_FLAD_BASE           0x5011c000
#endif
#endif

/* FLAD Register Offsets */

#define R_FLAD_FCKMHZ_OFFSET                      0x00000040  /* Data Flash Access Frequency Register */

/* FLAD Register Addresses */

#define R_FLAD_FCKMHZ                             (R_FLAD_BASE + R_FLAD_FCKMHZ_OFFSET)

/* Register bit definitions */
/* FCKMHZ Register bit definitions */
#define R_FLAD_FCKMHZ_FCKMHZ_SHIFT                (0)  /* Data Flash Access Frequency Register */
#define R_FLAD_FCKMHZ_FCKMHZ_MASK                 0xff


/* Maximum number of channels */

#define FLAD_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_FLAD_H */

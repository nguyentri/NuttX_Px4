/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_faci.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_FACI_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_FACI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* FACI Base Address */
#ifndef R_FACI_BASE
#define R_FACI_BASE           0x4011e000
#endif

/* FACI Register Offsets */

#define R_FACI_FBPROT0_OFFSET                     0x00000078  /* Flash Block Protection Register */
#define R_FACI_FBPROT1_OFFSET                     0x0000007c  /* Flash Block Protection for Secure Register */

/* FACI Register Addresses */

#define R_FACI_FBPROT0                            (R_FACI_BASE + R_FACI_FBPROT0_OFFSET)
#define R_FACI_FBPROT1                            (R_FACI_BASE + R_FACI_FBPROT1_OFFSET)

/* Register bit definitions */
/* FBPROT0 Register bit definitions */
#define R_FACI_FBPROT0_BPCN0                      (1 << 0)  /* Block Protection for Non-secure Cancel */

#define R_FACI_FBPROT0_KEY_SHIFT                  (8)  /* Key Code */
#define R_FACI_FBPROT0_KEY_MASK                   0xff00

/* FBPROT1 Register bit definitions */
#define R_FACI_FBPROT1_BPCN1                      (1 << 0)  /* Block Protection for Secure Cancel */

#define R_FACI_FBPROT1_KEY_SHIFT                  (8)  /* Key Code */
#define R_FACI_FBPROT1_KEY_MASK                   0xff00


/* Maximum number of channels */

#define FACI_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_FACI_H */

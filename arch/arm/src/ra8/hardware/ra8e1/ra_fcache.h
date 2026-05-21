/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8e1/ra_fcache.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_FCACHE_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_FCACHE_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* FCACHE Base Address */
#ifndef R_FCACHE_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_FCACHE_BASE           0x4001c100
#else
#define R_FCACHE_BASE           0x5001c100
#endif
#endif

/* FCACHE Register Offsets */

#define R_FCACHE_FCACHEE_OFFSET                   0x00000000  /* Flash Cache Enable Register */
#define R_FCACHE_FCACHEIV_OFFSET                  0x00000004  /* Flash Cache Invalidate Register */
#define R_FCACHE_FLWT_OFFSET                      0x0000001c  /* Flash Wait Cycle Register */
#define R_FCACHE_FSAR_OFFSET                      0x00000040  /* Flash Security Attribution Register */

/* FCACHE Register Addresses */

#define R_FCACHE_FCACHEE                          (R_FCACHE_BASE + R_FCACHE_FCACHEE_OFFSET)
#define R_FCACHE_FCACHEIV                         (R_FCACHE_BASE + R_FCACHE_FCACHEIV_OFFSET)
#define R_FCACHE_FLWT                             (R_FCACHE_BASE + R_FCACHE_FLWT_OFFSET)
#define R_FCACHE_FSAR                             (R_FCACHE_BASE + R_FCACHE_FSAR_OFFSET)

/* Register bit definitions */
/* FCACHEE Register bit definitions */
#define R_FCACHE_FCACHEE_FCACHEEN                 (1 << 0)  /* Flash Cache Enable */

/* FCACHEIV Register bit definitions */
#define R_FCACHE_FCACHEIV_FCACHEIV                (1 << 0)  /* Flash Cache Invalidate */

/* FLWT Register bit definitions */
#define R_FCACHE_FLWT_FLWT_SHIFT                  (0)  /* Flash Wait Cycle */
#define R_FCACHE_FLWT_FLWT_MASK                   0x7

/* FSAR Register bit definitions */
#define R_FCACHE_FSAR_FLWTSA                      (1 << 0)  /* FLWT Security Attribution */

#define R_FCACHE_FSAR_FCACHESA                    (1 << 1)  /* FCHACHEEN Security Attribution */

#define R_FCACHE_FSAR_FCKMHZSA                    (1 << 8)  /* FCKMHZ Security Attribution */

#define R_FCACHE_FSAR_FACICMISA                   (1 << 9)  /* FACI command Issuing Security Attribution */

#define R_FCACHE_FSAR_FACICMRSA                   (1 << 10)  /* FACI command Registers Security Attribution */

#define R_FCACHE_FSAR_FCACHEENSA                  (1 << 1)  /* FCHACHEEN Security Attribution */

#define R_FCACHE_FSAR_FACICOMISA                  (1 << 9)  /* FACI command Issuing Security Attribution */

#define R_FCACHE_FSAR_FACICOMRSA                  (1 << 10)  /* FACI command Registers Security Attribution */

#define R_FCACHE_FSAR_FACITRSA                    (1 << 11)  /* FACI transfer Security Attribution */


/* Maximum number of channels */

#define FCACHE_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_FCACHE_H */

/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_agtx.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_AGTX_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_AGTX_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* AGTX Base Address */
#ifndef R_AGTX_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_AGTX_BASE           0x40221000
#else
#define R_AGTX_BASE           0x50221000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_AGTX_CH_STRIDE    0x00000100
#define R_AGTX_CH_BASE(ch)   (R_AGTX_BASE + ((uint32_t)(ch) * R_AGTX_CH_STRIDE))

/* AGTX Register Offsets */

#define R_AGTX_AGT16_OFFSET                       0x00000000  /* AGT (16-bit) peripheral registers */
#define R_AGTX_AGT32_OFFSET                       0x00000000  /* AGTW (32-bit) peripheral registers */

/* AGTX Register Addresses */

#define R_AGTX_AGT16(n)                           (R_AGTX_CH_BASE(n) + R_AGTX_AGT16_OFFSET)
#define R_AGTX_AGT32(n)                           (R_AGTX_CH_BASE(n) + R_AGTX_AGT32_OFFSET)

/* Register bit definitions */

/* Maximum number of channels */

#define AGTX_MAX_CHANNELS    10

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_AGTX_H */

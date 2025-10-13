/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_dotf.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DOTF_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DOTF_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DOTF Base Address */
#ifndef R_DOTF_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_DOTF_BASE           0x40268800
#else
#define R_DOTF_BASE           0x50268800
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_DOTF_CH_STRIDE    0x00000100
#define R_DOTF_CH_BASE(ch)   (R_DOTF_BASE + ((uint32_t)(ch) * R_DOTF_CH_STRIDE))

/* DOTF Register Offsets */

#define R_DOTF_CONVAREAST_OFFSET                  0x00000000  /* DOTF Conversion Area Start Address Register */
#define R_DOTF_CONVAREAD_OFFSET                   0x00000004  /* DOTF Conversion Area End Address Register */

/* DOTF Register Addresses */

#define R_DOTF_CONVAREAST(n)                      (R_DOTF_CH_BASE(n) + R_DOTF_CONVAREAST_OFFSET)
#define R_DOTF_CONVAREAD(n)                       (R_DOTF_CH_BASE(n) + R_DOTF_CONVAREAD_OFFSET)

/* Register bit definitions */
/* CONVAREAST Register bit definitions */
#define R_DOTF_CONVAREAST_CONVAREAST_SHIFT        (12)  /* The first address of the decryption processing area. The actual address is CONVAREAST[31:12] × 0x1000. */
#define R_DOTF_CONVAREAST_CONVAREAST_MASK         0xfffff000

/* CONVAREAD Register bit definitions */
#define R_DOTF_CONVAREAD_CONVAREAED_SHIFT         (12)  /* The end address of the decryption processing area. The actual address is CONVAREAED[31:12] ×0x1000. */
#define R_DOTF_CONVAREAD_CONVAREAED_MASK          0xfffff000

#define R_DOTF_CONVAREAD_CONVAREAD_SHIFT          (12)  /* End address of decryption processing area */
#define R_DOTF_CONVAREAD_CONVAREAD_MASK           0xfffff000


/* Maximum number of channels */

#define DOTF_MAX_CHANNELS    2

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DOTF_H */

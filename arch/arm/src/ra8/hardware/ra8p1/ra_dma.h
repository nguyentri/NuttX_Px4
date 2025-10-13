/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_dma.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DMA_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DMA_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DMA Base Address */
#ifndef R_DMA_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_DMA_BASE           0x4000a800
#else
#define R_DMA_BASE           0x5000a800
#endif
#endif

/* DMA Register Offsets */

#define R_DMA_DMAST_OFFSET                        0x00000000  /* DMA Module Activation Register */
#define R_DMA_DMCTL_OFFSET                        0x00000010  /* DMAC Control Register */
#define R_DMA_DMECHR_OFFSET                       0x00000040  /* DMAC Error Channel Register */

/* DMA Register Addresses */

#define R_DMA_DMAST                               (R_DMA_BASE + R_DMA_DMAST_OFFSET)
#define R_DMA_DMCTL                               (R_DMA_BASE + R_DMA_DMCTL_OFFSET)
#define R_DMA_DMECHR                              (R_DMA_BASE + R_DMA_DMECHR_OFFSET)

/* Register bit definitions */
/* DMAST Register bit definitions */
#define R_DMA_DMAST_DMST                          (1 << 0)  /* DMAC Operation Enable */

/* DMCTL Register bit definitions */
#define R_DMA_DMCTL_PR                            (1 << 0)  /* Priority Control Select */

#define R_DMA_DMCTL_ERCH                          (1 << 4)  /* Clear Channel Select */

/* DMECHR Register bit definitions */
#define R_DMA_DMECHR_DMECH_SHIFT                  (0)  /* DMAC Error Channel */
#define R_DMA_DMECHR_DMECH_MASK                   0xf

#define R_DMA_DMECHR_DMECHSAM                     (1 << 8)  /* DMAC Error Channel Security Attribution Monitor */

#define R_DMA_DMECHR_DMESTA                       (1 << 16)  /* DMAC Error Status */


/* Maximum number of channels */

#define DMA_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DMA_H */

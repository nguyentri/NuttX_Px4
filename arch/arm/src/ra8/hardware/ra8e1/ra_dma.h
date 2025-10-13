/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8e1/ra_dma.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_DMA_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_DMA_H

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
#define R_DMA_DMECHR_OFFSET                       0x00000040  /* DMAC Error Channel Register */
/* DELSR%s Registers (0-7) */
#define R_DMA_DELSR_OFFSET(m)                     (0x00000080 + ((m) * 0x00000004))  /* DMAC Event Link Setting Register %s */

/* DMA Register Addresses */

#define R_DMA_DMAST                               (R_DMA_BASE + R_DMA_DMAST_OFFSET)
#define R_DMA_DMECHR                              (R_DMA_BASE + R_DMA_DMECHR_OFFSET)
#define R_DMA_DELSR(m)                            (R_DMA_BASE + R_DMA_DELSR_OFFSET(m))

/* Register bit definitions */
/* DMAST Register bit definitions */
#define R_DMA_DMAST_DMST                          (1 << 0)  /* DMAC Operation Enable */

/* DMECHR Register bit definitions */
#define R_DMA_DMECHR_DMECH_SHIFT                  (0)  /* DMAC Error channel */
#define R_DMA_DMECHR_DMECH_MASK                   0xf

#define R_DMA_DMECHR_DMECHSAM                     (1 << 8)  /* DMAC Error channel Security Attribution Monitor */

#define R_DMA_DMECHR_DMESTA                       (1 << 16)  /* DMAC Error Status */

/* DELSR Register bit definitions */
#define R_DMA_DELSR_DELS_SHIFT                    (0)  /* DMAC Event Link Select */
#define R_DMA_DELSR_DELS_MASK                     0x1ff
#  define R_DMA_DELSR_DELS_0X00                           (0 << R_DMA_DELSR_DELS_SHIFT)  /* Disable interrupts to the associated DMAC module */

#define R_DMA_DELSR_IR                            (1 << 16)  /* DMAC Activation Request Status flag */


/* Maximum number of channels */

#define DMA_MAX_CHANNELS    8

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_DMA_H */

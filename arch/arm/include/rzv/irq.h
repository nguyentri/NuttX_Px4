/****************************************************************************
 * arch/arm/include/rzv/irq.h
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

/* This file should never be included directly but, rather,
 * only indirectly through nuttx/irq.h
 */

#ifndef __ARCH_ARM_INCLUDE_RZV_IRQ_H
#define __ARCH_ARM_INCLUDE_RZV_IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <arch/rzv/chip.h>

/****************************************************************************
 * Pre-processor Prototypes
 ****************************************************************************/

/* IRQ numbers.
 * The IRQ number corresponds vector number and hence map directly to
 * bits in the GIC.  This does, however, waste several words of memory in
 * the IRQ to handle mapping tables.
 */

/* Common Processor Exceptions (vectors 0-15) for ARMv7-R */

#define RZV_IRQ_RESERVED       (0) /* Reserved vector (only used with CONFIG_DEBUG_FEATURES) */
                                   /* Vector  0: Reset stack pointer value */
                                   /* Vector  1: Reset (not handler as an IRQ) */
#define RZV_IRQ_UNDEF          (1) /* Vector  1: Undefined instruction */
#define RZV_IRQ_SVC            (2) /* Vector  2: Software interrupt / SVC call */
#define RZV_IRQ_PREFETCH       (3) /* Vector  3: Prefetch abort */
#define RZV_IRQ_DATA           (4) /* Vector  4: Data abort */
                                   /* Vector  5: Reserved */
#define RZV_IRQ_IRQ            (6) /* Vector  6: IRQ interrupt */
#define RZV_IRQ_FIQ            (7) /* Vector  7: FIQ interrupt */

/* Chip-Specific External interrupts */

#define RZV_IRQ_FIRST        (32) /* Vector number of the first external interrupt */

#if defined(CONFIG_ARCH_CHIP_R9A09G057) || defined(CONFIG_RZV2H_GROUP)
#  include <arch/rzv/rzv2h_irq.h>
#else
#  error Unrecognized RZV architecture
#endif

#define NR_IRQS               (RZV_IRQ_FIRST + RZV_IRQ_NEXTINT)

/****************************************************************************
 * Public Types
 ****************************************************************************/

#ifndef __ASSEMBLY__

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#undef EXTERN
#ifdef __cplusplus
}
#endif
#endif

#endif /* __ARCH_ARM_INCLUDE_RZV_IRQ_H */

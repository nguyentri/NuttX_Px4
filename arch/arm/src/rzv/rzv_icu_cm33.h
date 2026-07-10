/****************************************************************************
 * arch/arm/src/rzv/rzv_icu_cm33.h
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

/* RZV2H CM33 (Cortex-M33 / NVIC) ICU driver interface.
 *
 * Counterpart to the CR8/GIC driver in rzv_icu.h.  The CM33 core routes
 * selectable peripheral events through the INTM33SEL register block (not the
 * CR8 INTR8SEL block) and delivers them via the NVIC (not the GIC):
 *
 *   Peripheral event → INTC INTM33SEL[slot] → NVIC IRQ → CPU → Handler
 *
 * NuttX IRQ number == RZV_IRQ_FIRST(32) + NVIC external index.  The selectable
 * SEL base (INTID for slot 0) is defined in rzv_icu_cm33.c as
 * RZV_INTC_M33SEL_SPI_BASE; see the design doc / Phase 4 of the interrupt-
 * unification plan for the FSP-verified value.  Enable/disable/priority/pending
 * are handled through the NVIC (rzv_irq_cm33.c), never the GIC.
 *
 * This header declares only the CM33 public API.  It intentionally uses a
 * CM33-specific include guard so it can never collide with the CR8 rzv_icu.h.
 */

#ifndef __ARCH_ARM_SRC_RZV_ICU_CM33_H
#define __ARCH_ARM_SRC_RZV_ICU_CM33_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>
#include <nuttx/irq.h>

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/* CM33-specific INTM33SEL/NVIC implementation.
 * These are the concrete CM33 routines; the rzv_icu_* wrappers below forward
 * to them so board/driver code can use one common API across cores.
 */

void rzv_icu_m33_initialize(void);
int  rzv_icu_m33_attach(int event, xcpt_t handler, void *arg, bool irq_enable);
int  rzv_icu_m33_detach(int icu_irq);

/* Common ICU API (core-agnostic names, CM33 implementation).
 * Mirrors the CR8 surface in rzv_icu.h so callers are portable; on a CM33
 * build these resolve to the INTM33SEL/NVIC path.
 */

void rzv_icu_initialize(void);
int  rzv_icu_attach(int event, xcpt_t handler, void *arg, bool irq_enable);
int  rzv_icu_detach(int icu_irq);
void rzv_icu_clear_irq(int irq);
int  rzv_icu_set_priority(int icu_irq, int priority);
int  rzv_icu_set_event(int icu_slot, int event);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RZV_ICU_CM33_H */

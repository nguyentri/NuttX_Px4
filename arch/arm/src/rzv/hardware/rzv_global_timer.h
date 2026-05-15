/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_global_timer.h
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

/* DORMANT — DO NOT USE in rdk-rzv2h builds.
 * The ARM Cortex-R8 global timer is not used as a clock source in this port.
 * The NuttX scheduler tick uses the CR8 ARM private timer (rzv_timerisr.c).
 * HRT uses GTM7 (rzv_hrt.c).  This header is kept for reference; do not
 * wire it into any driver without a deliberate design decision.
 */

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_GLOBAL_TIMER_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_GLOBAL_TIMER_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GLOBAL_TIMER Base Address **********************************************/

#ifndef RZV_GLOBAL_TIMER_BASE
#  define RZV_GLOBAL_TIMER_BASE                         0x12C10200
#endif

/* GLOBAL_TIMER Register Offsets ******************************************/

#define RZV_GLOBAL_TIMER_GTCR_L_OFFSET                  0x0000  /* Counter low */
#define RZV_GLOBAL_TIMER_GTCR_H_OFFSET                  0x0004  /* Counter high */
#define RZV_GLOBAL_TIMER_GTCTLR_OFFSET                  0x0008  /* Control */
#define RZV_GLOBAL_TIMER_GTISR_OFFSET                   0x000C  /* Interrupt status */
#define RZV_GLOBAL_TIMER_CVR_L_OFFSET                   0x0010  /* Compare low */
#define RZV_GLOBAL_TIMER_CVR_H_OFFSET                   0x0014  /* Compare high */
#define RZV_GLOBAL_TIMER_AUTO_INCR_OFFSET               0x0018  /* Auto increment */

#define RZV_GLOBAL_TIMER_GTCR_L                         (RZV_GLOBAL_TIMER_BASE + RZV_GLOBAL_TIMER_GTCR_L_OFFSET)
#define RZV_GLOBAL_TIMER_GTCR_H                         (RZV_GLOBAL_TIMER_BASE + RZV_GLOBAL_TIMER_GTCR_H_OFFSET)
#define RZV_GLOBAL_TIMER_GTCTLR                         (RZV_GLOBAL_TIMER_BASE + RZV_GLOBAL_TIMER_GTCTLR_OFFSET)
#define RZV_GLOBAL_TIMER_GTISR                          (RZV_GLOBAL_TIMER_BASE + RZV_GLOBAL_TIMER_GTISR_OFFSET)
#define RZV_GLOBAL_TIMER_CVR_L                          (RZV_GLOBAL_TIMER_BASE + RZV_GLOBAL_TIMER_CVR_L_OFFSET)
#define RZV_GLOBAL_TIMER_CVR_H                          (RZV_GLOBAL_TIMER_BASE + RZV_GLOBAL_TIMER_CVR_H_OFFSET)
#define RZV_GLOBAL_TIMER_AUTO_INCR                      (RZV_GLOBAL_TIMER_BASE + RZV_GLOBAL_TIMER_AUTO_INCR_OFFSET)

/* Backward-compatible names. */

#define RZV_GLOBAL_TIMETYPE_GTCTLR_OFFSET               RZV_GLOBAL_TIMER_GTCTLR_OFFSET
#define RZV_GLOBAL_TIMETYPE_GTISR_OFFSET                RZV_GLOBAL_TIMER_GTISR_OFFSET

/* GLOBAL_TIMETYPE GTCTLR Register Bit Definitions *******************/

#define GLOBAL_TIMETYPE_GTCTLR_TE               (1 << 0)  /* Te */

#define GLOBAL_TIMETYPE_GTCTLR_CE               (1 << 1)  /* Ce */

#define GLOBAL_TIMETYPE_GTCTLR_IRQE             (1 << 2)  /* Irqe */

#define GLOBAL_TIMETYPE_GTCTLR_AI               (1 << 3)  /* Ai */

#define GLOBAL_TIMETYPE_GTCTLR_PRESCALER_SHIFT  (8)      /* Bits 8-15: Prescaler */
#define GLOBAL_TIMETYPE_GTCTLR_PRESCALER_MASK   (0xff << GLOBAL_TIMETYPE_GTCTLR_PRESCALER_SHIFT)

/* GLOBAL_TIMETYPE GTISR Register Bit Definitions ********************/

#define GLOBAL_TIMETYPE_GTISR_EF                (1 << 0)  /* Ef */

/* GLOBAL_TIMETYPE TIMER Register Bit Definitions ********************/

#define GLOBAL_TIMETYPE_TIMER_GTCR_L_SHIFT      (0)      /* Bits 0-31: Gtcr L */
#define GLOBAL_TIMETYPE_TIMER_GTCR_L_MASK       (0xffffffff << GLOBAL_TIMETYPE_TIMER_GTCR_L_SHIFT)

#define GLOBAL_TIMETYPE_TIMER_GTCR_H_SHIFT      (0)      /* Bits 0-31: Gtcr H */
#define GLOBAL_TIMETYPE_TIMER_GTCR_H_MASK       (0xffffffff << GLOBAL_TIMETYPE_TIMER_GTCR_H_SHIFT)

#define GLOBAL_TIMETYPE_TIMER_CVR_L_SHIFT       (0)      /* Bits 0-31: Cvr L */
#define GLOBAL_TIMETYPE_TIMER_CVR_L_MASK        (0xffffffff << GLOBAL_TIMETYPE_TIMER_CVR_L_SHIFT)

#define GLOBAL_TIMETYPE_TIMER_CVR_H_SHIFT       (0)      /* Bits 0-31: Cvr H */
#define GLOBAL_TIMETYPE_TIMER_CVR_H_MASK        (0xffffffff << GLOBAL_TIMETYPE_TIMER_CVR_H_SHIFT)

/* GLOBAL_TIMETYPE TIMER_AUTO Register Bit Definitions ***************/

#define GLOBAL_TIMETYPE_TIMER_AUTO_INCR_SHIFT   (0)      /* Bits 0-31: Incr */
#define GLOBAL_TIMETYPE_TIMER_AUTO_INCR_MASK    (0xffffffff << GLOBAL_TIMETYPE_TIMER_AUTO_INCR_SHIFT)

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_GLOBAL_TIMER_H */

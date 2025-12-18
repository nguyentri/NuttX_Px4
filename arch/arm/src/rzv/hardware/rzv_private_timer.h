/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_private_timer.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_PRIVATE_TIMER_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_PRIVATE_TIMER_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ARM Cortex-R8 Private Timer Base Address for RZV2H *********************/
/* Note: This is the RZV2H-specific address from CMSIS, not the generic
 * ARM private peripheral space address (0xF0000600).
 */

#ifndef RZV_PRIVATE_TIMER_BASE
#  define RZV_PRIVATE_TIMER_BASE                         0x12C10600
#endif

/* PRIVATE_TIMER Register Offsets **************************************/

#define RZV_PRIVATE_TIMER_PTLR_OFFSET                    0x0000  /* Private Timer Load Register */
#define RZV_PRIVATE_TIMER_PTCR_OFFSET                    0x0004  /* Private Timer Counter Register */
#define RZV_PRIVATE_TIMER_PTCTLR_OFFSET                  0x0008  /* Private Timer Control Register */
#define RZV_PRIVATE_TIMER_PTISR_OFFSET                   0x000C  /* Private Timer Interrupt Status Register */
#define RZV_PRIVATE_TIMER_WDWLR_OFFSET                   0x0020  /* Watchdog Load Register */
#define RZV_PRIVATE_TIMER_WDWCR_OFFSET                   0x0024  /* Watchdog Counter Register */
#define RZV_PRIVATE_TIMER_WDCTLR_OFFSET                  0x0028  /* Watchdog Control Register */
#define RZV_PRIVATE_TIMER_WDISR_OFFSET                   0x002C  /* Watchdog Interrupt Status Register */
#define RZV_PRIVATE_TIMER_WDRSR_OFFSET                   0x0030  /* Watchdog Reset Status Register */
#define RZV_PRIVATE_TIMER_WDDR_OFFSET                    0x0034  /* Watchdog Disable Register */

/* PRIVATE_TIMER Register Addresses *****************************************/

#define RZV_PRIVATE_TIMER_PTLR                           (RZV_PRIVATE_TIMER_BASE + RZV_PRIVATE_TIMER_PTLR_OFFSET)
#define RZV_PRIVATE_TIMER_PTCR                           (RZV_PRIVATE_TIMER_BASE + RZV_PRIVATE_TIMER_PTCR_OFFSET)
#define RZV_PRIVATE_TIMER_PTCTLR                         (RZV_PRIVATE_TIMER_BASE + RZV_PRIVATE_TIMER_PTCTLR_OFFSET)
#define RZV_PRIVATE_TIMER_PTISR                          (RZV_PRIVATE_TIMER_BASE + RZV_PRIVATE_TIMER_PTISR_OFFSET)
#define RZV_PRIVATE_TIMER_WDWLR                          (RZV_PRIVATE_TIMER_BASE + RZV_PRIVATE_TIMER_WDWLR_OFFSET)
#define RZV_PRIVATE_TIMER_WDWCR                          (RZV_PRIVATE_TIMER_BASE + RZV_PRIVATE_TIMER_WDWCR_OFFSET)
#define RZV_PRIVATE_TIMER_WDCTLR                         (RZV_PRIVATE_TIMER_BASE + RZV_PRIVATE_TIMER_WDCTLR_OFFSET)
#define RZV_PRIVATE_TIMER_WDISR                          (RZV_PRIVATE_TIMER_BASE + RZV_PRIVATE_TIMER_WDISR_OFFSET)
#define RZV_PRIVATE_TIMER_WDRSR                          (RZV_PRIVATE_TIMER_BASE + RZV_PRIVATE_TIMER_WDRSR_OFFSET)
#define RZV_PRIVATE_TIMER_WDDR                           (RZV_PRIVATE_TIMER_BASE + RZV_PRIVATE_TIMER_WDDR_OFFSET)

/* PRIVATE_TIMER Load Register (PTLR) ***************************************/

#define PRIVATE_TIMER_PTLR_SHIFT                         (0)      /* Bits 0-31: Timer load value */
#define PRIVATE_TIMER_PTLR_MASK                          (0xffffffff << PRIVATE_TIMER_PTLR_SHIFT)

/* PRIVATE_TIMER Counter Register (PTCR) ************************************/

#define PRIVATE_TIMER_PTCR_SHIFT                         (0)      /* Bits 0-31: Timer counter value */
#define PRIVATE_TIMER_PTCR_MASK                          (0xffffffff << PRIVATE_TIMER_PTCR_SHIFT)

/* PRIVATE_TIMER Control Register (PTCTLR) **********************************/

#define PRIVATE_TIMER_PTCTLR_TE                          (1 << 0)  /* Timer Enable */
#define PRIVATE_TIMER_PTCTLR_AR                          (1 << 1)  /* Auto Reload */
#define PRIVATE_TIMER_PTCTLR_IRQE                        (1 << 2)  /* Interrupt Request Enable */
#define PRIVATE_TIMER_PTCTLR_PRESCALER_SHIFT             (8)      /* Bits 8-15: Prescaler */
#define PRIVATE_TIMER_PTCTLR_PRESCALER_MASK              (0xff << PRIVATE_TIMER_PTCTLR_PRESCALER_SHIFT)

/* PRIVATE_TIMER Interrupt Status Register (PTISR) **************************/

#define PRIVATE_TIMER_PTISR_FLAG                         (1 << 0)  /* Event Flag (read) */
#define PRIVATE_TIMER_PTISR_CLR                          (1 << 0)  /* Clear Event Flag (write) */

/* PRIVATE_TIMER Watchdog Load Register (WDWLR) *****************************/

#define PRIVATE_TIMER_WDWLR_SHIFT                        (0)      /* Bits 0-31: Watchdog load value */
#define PRIVATE_TIMER_WDWLR_MASK                         (0xffffffff << PRIVATE_TIMER_WDWLR_SHIFT)

/* PRIVATE_TIMER Watchdog Counter Register (WDWCR) **************************/

#define PRIVATE_TIMER_WDWCR_SHIFT                        (0)      /* Bits 0-31: Watchdog counter value */
#define PRIVATE_TIMER_WDWCR_MASK                         (0xffffffff << PRIVATE_TIMER_WDWCR_SHIFT)

/* PRIVATE_TIMER Watchdog Control Register (WDCTLR) *************************/

#define PRIVATE_TIMER_WDCTLR_WE                          (1 << 0)  /* Watchdog Enable */
#define PRIVATE_TIMER_WDCTLR_AR                          (1 << 1)  /* Auto Reload */
#define PRIVATE_TIMER_WDCTLR_ITE                         (1 << 2)  /* Interrupt Timer Enable */
#define PRIVATE_TIMER_WDCTLR_WM                          (1 << 3)  /* Watchdog Mode */
#define PRIVATE_TIMER_WDCTLR_PRESCALER_SHIFT             (8)      /* Bits 8-15: Prescaler */
#define PRIVATE_TIMER_WDCTLR_PRESCALER_MASK              (0xff << PRIVATE_TIMER_WDCTLR_PRESCALER_SHIFT)

/* PRIVATE_TIMER Watchdog Interrupt Status Register (WDISR) *****************/

#define PRIVATE_TIMER_WDISR_FLAG                         (1 << 0)  /* Watchdog Event Flag (read) */
#define PRIVATE_TIMER_WDISR_CLR                          (1 << 0)  /* Clear Watchdog Event Flag (write) */

/* PRIVATE_TIMER Watchdog Reset Status Register (WDRSR) *********************/

#define PRIVATE_TIMER_WDRSR_RESET                        (1 << 0)  /* Watchdog Reset Event */

/* PRIVATE_TIMER Watchdog Disable Register (WDDR) ***************************/

#define PRIVATE_TIMER_WDDR_SHIFT                         (0)      /* Bits 0-31: Watchdog disable sequence */
#define PRIVATE_TIMER_WDDR_MASK                          (0xffffffff << PRIVATE_TIMER_WDDR_SHIFT)
#define PRIVATE_TIMER_WDDR_KEY1                          0x12345678  /* First key for watchdog disable */
#define PRIVATE_TIMER_WDDR_KEY2                          0x87654321  /* Second key for watchdog disable */

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_PRIVATE_TIMER_H */

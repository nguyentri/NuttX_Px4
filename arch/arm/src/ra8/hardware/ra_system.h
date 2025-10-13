/****************************************************************************
 * arch/arm/src/ra8/hardware/ra_system.h
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
#ifndef __ARCH_ARM_SRC_RA_HARDWARE_RA8_SYSTEM_H
#define __ARCH_ARM_SRC_RA_HARDWARE_RA8_SYSTEM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <arch/ra8/chip.h>
#include "hardware/ra_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define RENESAS_CORTEX_M85


/* SYSTEM Control Register Bits */
#define R_SYSC_PRCR_PRKEY               (0xA500)      /* Protection Key */
#define R_SYSC_PRCR_PRC0                (1 << 0)      /* Protect bit 0 */
#define R_SYSC_PRCR_PRC1                (1 << 1)      /* Protect bit 1 */
#define R_SYSC_PRCR_PRC3                (1 << 3)      /* Protect bit 3 */
#define R_SYSC_PRCR_PRC4                (1 << 4)      /* Protect bit 4 */

/* Hardware register wait macro */
#define RA_HARDWARE_REGISTER_WAIT(reg, expected) \
  do { \
    while ((reg) != (expected)) \
      { \
        /* Wait for register to reach expected value */ \
      } \
  } while (0)


/* Software delay loop */
inline void ra_delay_loop (__attribute__((unused)) uint32_t loop_cnt)
{
    __asm volatile (
#if defined(RENESAS_CORTEX_M85) && (defined(__ARMCC_VERSION) || defined(__GNUC__))

        /* Align the branch target to a 64-bit boundary, a CM85 specific optimization. */
        /* IAR does not support alignment control within inline assembly. */
        ".balign 8\n"
#endif
        "sw_delay_loop:         \n"
#if defined(__ICCARM__) || defined(__ARMCC_VERSION) || (defined(__llvm__) && !defined(__CLANG_TIDY__))
        "   subs r0, #1         \n"    ///< 1 cycle
#elif defined(__GNUC__)
        "   sub r0, r0, #1      \n"    ///< 1 cycle
#endif

        "   cmp r0, #0          \n"    ///< 1 cycle

/* CM0 and CM23 have a different instruction set */
#if defined(__CORE_CM0PLUS_H_GENERIC) || defined(__CORE_CM23_H_GENERIC)
        "   bne sw_delay_loop   \n"    ///< 2 cycles
#else
        "   bne.n sw_delay_loop \n"    ///< 2 cycles
#endif
        "   bx lr               \n");  ///< 2 cycles
}


/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Public Functions Prototypes
 ****************************************************************************/

#endif /* __ARCH_ARM_SRC_RA_HARDWARE_RA8_SYSTEM_H */

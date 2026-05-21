/****************************************************************************
 * arch/arm/src/ra8/hardware/ra_hardware.h
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

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define R_SYSC_PRCR_S_KEY                         (0xA500U)

/* Hardware register wait macro */
#define RA_HARDWARE_WAIT(reg, expected) \
  do { \
    while ((reg) != (expected)) \
      { \
        /* Wait for register to reach expected value */ \
      } \
  } while (0)


/* Software delay loop */
inline void ra_hardware_loop (__attribute__((unused)) uint32_t loop_cnt)
{
    __asm volatile (

        /* Align the branch target to a 64-bit boundary, a CM85 specific optimization. */
        /* IAR does not support alignment control within inline assembly. */
        ".balign 8\n"
        "sw_delay_loop:         \n"
        "   sub r0, r0, #1      \n"    ///< 1 cycle

        "   cmp r0, #0          \n"
    );    ///< 1 cycle
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

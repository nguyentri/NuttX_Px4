/****************************************************************************
 * arch/arm/src/rzv/rzv_start.h
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

#ifndef __ARCH_ARM_SRC_RZV_START_H
#define __ARCH_ARM_SRC_RZV_START_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Compiler-specific macros */
#if defined(__ARMCC_VERSION)
  #define RZV_UNINIT_SECTION_PREFIX         ".bss"
  #define RZV_DONT_REMOVE                   __attribute__((used))
  #define RZV_FORCE_INLINE                  __attribute__((always_inline))
#elif defined(__GNUC__)
  #define RZV_UNINIT_SECTION_PREFIX
  #define RZV_DONT_REMOVE                   __attribute__((used))
  #define RZV_ATTRIBUTE_STACKLESS           __attribute__((naked))
  #define RZV_FORCE_INLINE                  __attribute__((always_inline))
#elif defined(__ICCARM__)
  #define RZV_UNINIT_SECTION_PREFIX
  #define RZV_DONT_REMOVE                   __root
  #define RZV_FORCE_INLINE                  _Pragma("inline=forced")
#endif

/* Linker section macros */
#define RZV_PLACE_IN_SECTION(x)              __attribute__((section(x))) __attribute__((__used__))
#define RZV_ALIGN_VARIABLE(x)                __attribute__((aligned(x)))

/* Stack and heap alignment */
#define RZV_STACK_ALIGNMENT        (8)

/* Register Protection Types */
typedef enum
{
    RZV_REG_PROTECT_SYSC = 0,          /* System control registers */
    RZV_REG_PROTECT_CPG,               /* Clock pulse generator */
    RZV_REG_PROTECT_GPIO,              /* GPIO control (PWPR) */
} rzv_reg_protect_t;

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Name: rzv_board_initialize
 *
 * Description:
 *   All RZV architectures must provide the following entry point. This
 *   entry point is called early in the initialization after clocks and
 *   memory have been configured but before any devices have been
 *   initialized.
 *
 ****************************************************************************/

void rzv_board_initialize(void);

/****************************************************************************
 * Name: rzv_ram_init
 *
 * Description:
 *   Initialize RAM sections (BSS and DATA)
 *
 ****************************************************************************/

void rzv_ram_init(void);

/****************************************************************************
 * Name: rzv_register_protect_enable
 *
 * Description:
 *   Enable register protection for critical system registers
 *
 ****************************************************************************/

void rzv_register_protect_enable(rzv_reg_protect_t regs_to_protect);

/****************************************************************************
 * Name: rzv_register_protect_disable
 *
 * Description:
 *   Disable register protection for critical system registers
 *
 ****************************************************************************/

void rzv_register_protect_disable(rzv_reg_protect_t regs_to_unprotect);

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RZV_START_H */
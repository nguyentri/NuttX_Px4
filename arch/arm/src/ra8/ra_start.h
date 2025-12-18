/****************************************************************************
 * arch/arm/src/ra8/ra_start.h
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

#ifndef __ARCH_ARM_SRC_RA_START_H
#define __ARCH_ARM_SRC_RA_START_H

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
  #define RA_UNINIT_SECTION_PREFIX         ".bss"
  #define RA_DONT_REMOVE                   __attribute__((used))
  #define RA_FORCE_INLINE                  __attribute__((always_inline))
#elif defined(__GNUC__)
  #define RA_UNINIT_SECTION_PREFIX
  #define RA_DONT_REMOVE                   __attribute__((used))
  #define RA_ATTRIBUTE_STACKLESS           __attribute__((naked))
  #define RA_FORCE_INLINE                  __attribute__((always_inline))
#elif defined(__ICCARM__)
  #define RA_UNINIT_SECTION_PREFIX
  #define RA_DONT_REMOVE                   __root
  #define RA_FORCE_INLINE                  _Pragma("inline=forced")
#endif

/* Linker section macros */
#define RA_PLACE_IN_SECTION(x)              __attribute__((section(x))) __attribute__((__used__))
#define RA_ALIGN_VARIABLE(x)                __attribute__((aligned(x)))

/* Stack and heap alignment */
#define RA_STACK_ALIGNMENT        (8)

/* TrustZone build configuration macros */
#ifndef CONFIG_RA_TZ_SECURE_BUILD
#  define CONFIG_RA_TZ_SECURE_BUILD 0
#endif

#ifndef CONFIG_RA_TZ_NONSECURE_BUILD
#  define CONFIG_RA_TZ_NONSECURE_BUILD 0
#endif

/* Register Protection Types */
typedef enum
{
    RA_REG_PROTECT_CGC = 0,            /* PRC0: Clock generation circuit */
    RA_REG_PROTECT_OM_LPC_BATT,        /* PRC1: Operating mode, LPC, battery backup */
    RA_REG_PROTECT_LVD,                /* PRC3: LVD */
    RA_REG_PROTECT_SAR                 /* PRC4: SAR registers */
} ra_reg_protect_t;

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

void ra_board_initialize(void);
void ra_trustzone_init(void);
void ra_ram_init (const uint32_t external);

/****************************************************************************
 * Name: ra_register_protect_enable
 *
 * Description:
 *   Enable register protection
 *
 ****************************************************************************/

void ra_register_protect_enable(ra_reg_protect_t regs_to_protect);

/****************************************************************************
 * Name: ra_register_protect_disable
 *
 * Description:
 *   Disable register protection
 *
 ****************************************************************************/

void ra_register_protect_disable(ra_reg_protect_t regs_to_unprotect);


/****************************************************************************
 * Name: ra_gpio_security_init
 *
 * Description:
 *   Initialize PMSAR and PSCU registers to their default values.
 *   Sets all port pins to secure mode (0)
 *   Must be called before configuring any port pins.
 *
 ****************************************************************************/

void ra_gpio_security_init(void);


#endif /* __ARCH_ARM_SRC_RA_START_H */

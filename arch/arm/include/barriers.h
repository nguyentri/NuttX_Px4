/****************************************************************************
 * arch/arm/include/barriers.h
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

#ifndef __ARCH_ARM_INCLUDE_BARRIERS_H
#define __ARCH_ARM_INCLUDE_BARRIERS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#if defined(CONFIG_ARCH_ARMV8M)
#  include "../src/armv8-m/barriers.h"
#elif defined(CONFIG_ARCH_ARMV7M)
#  include "../src/armv7-m/barriers.h"
#elif defined(CONFIG_ARCH_ARMV7A)
#  include "../src/armv7-a/barriers.h"
#elif defined(CONFIG_ARCH_ARMV7R)
#  include "../src/armv7-r/barriers.h"
#else
  /* For other ARM architectures, provide basic barrier macros */
#  define ARM_DSB()  __asm__ __volatile__ ("" : : : "memory")
#  define ARM_ISB()  __asm__ __volatile__ ("" : : : "memory")
#  define ARM_DMB()  __asm__ __volatile__ ("" : : : "memory")
#endif

#endif /* __ARCH_ARM_INCLUDE_BARRIERS_H */
/****************************************************************************
 * arch/arm/src/ra8/hardware/ra_clock.h
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

#ifndef __ARCH_ARM_SRC_RA_HARDWARE_RA8_CLOCK_H
#define __ARCH_ARM_SRC_RA_HARDWARE_RA8_CLOCK_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include "chip.h"

/* Include all hardware-dependent headers for the RA8 families here so
 * driver sources can simply include "chip.h" and get the correct
 * register offsets and bit definitions for the selected group.
 */
#if defined(CONFIG_RA8E1_GROUP)
#  include "hardware/ra8e1/ra_clock.h"
#elif defined(CONFIG_RA8P1_GROUP)
#  include "hardware/ra8p1/ra_clock.h"
#else
#  error "Unsupported RA8 Device"
#endif

#endif /* __ARCH_ARM_SRC_RA_HARDWARE_RA8_CLOCK_H */

/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_poeg.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_POEG_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_POEG_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* POEG Base Addresses — R9A09G057H (RZ/V2H)
 * Source: poeg_iodefine.h, confirmed addresses.
 * Unit 0 serves GPT0-7 (unit0); Unit 1 serves GPT10-17 (unit1).
 *
 * Each unit has 4 POEG channels (A/B/C/D) corresponding to GPT groups.
 * POEGGn register is a single 32-bit register at offset 0 in each block. */

/* POEG Unit 0 (covers GPT0-7) */
#define RZV_POEG0A_BASE             0x13001C00u  /* POEGGnA for unit0 */
#define RZV_POEG0B_BASE             0x13002000u  /* POEGGnB for unit0 */
#define RZV_POEG0C_BASE             0x13002400u  /* POEGGnC for unit0 */
#define RZV_POEG0D_BASE             0x13002800u  /* POEGGnD for unit0 */

/* POEG Unit 1 (covers GPT10-17) */
#define RZV_POEG1A_BASE             0x13002C00u  /* POEGGnA for unit1 */
#define RZV_POEG1B_BASE             0x13003000u  /* POEGGnB for unit1 */
#define RZV_POEG1C_BASE             0x13003400u  /* POEGGnC for unit1 */
#define RZV_POEG1D_BASE             0x13003800u  /* POEGGnD for unit1 */

/* POEGGn Register Offset (only one 32-bit register per POEG block) */
#define RZV_POEG_POEGGn_OFFSET      0x0000u

/* POEGGn Register Bit Definitions
 * Source: poeg_iodefine.h POEGGn_b struct fields. */
#define POEG_POEGGn_PIDF            (1u << 0)   /* Port input detect flag (R/W, write 0 to clear) */
#define POEG_POEGGn_IOCF            (1u << 1)   /* I/O short-circuit detect flag */
#define POEG_POEGGn_SSF             (1u << 3)   /* Software stop flag */
#define POEG_POEGGn_PIDE            (1u << 4)   /* Port input detect enable */
#define POEG_POEGGn_IOCE            (1u << 5)   /* I/O short-circuit detect enable */
#define POEG_POEGGn_ST              (1u << 16)  /* GPT output stopped (read-only) */
#define POEG_POEGGn_INV             (1u << 28)  /* Invert port input polarity */
#define POEG_POEGGn_NFEN            (1u << 29)  /* Noise filter enable */
#define POEG_POEGGn_NFCS_SHIFT      (30u)
#define POEG_POEGGn_NFCS_MASK       (0x3u << POEG_POEGGn_NFCS_SHIFT)  /* Noise filter clock select */

/* Convenience: clear all status flags (write 0 to PIDF, IOCF, SSF) */
#define POEG_POEGGn_CLEAR_FLAGS     (0u)

/* POEG channel index (logical, per unit) */
#define RZV_POEG_CHANNEL_A          0u
#define RZV_POEG_CHANNEL_B          1u
#define RZV_POEG_CHANNEL_C          2u
#define RZV_POEG_CHANNEL_D          3u
#define RZV_POEG_MAX_CHANNELS       4u

/* Number of POEG units on R9A09G057H */
#define RZV_POEG_MAX_UNITS          2u

/* Event detection enable flags (for rzv_poeg_configure event bitmask) */
#define POEG_EVENT_PORT_INPUT       POEG_POEGGn_PIDE
#define POEG_EVENT_SHORT_CIRCUIT    POEG_POEGGn_IOCE

/* Status flag check masks */
#define POEG_STATUS_ANY_FAULT       (POEG_POEGGn_PIDF | POEG_POEGGn_IOCF | POEG_POEGGn_SSF)

/* Register address accessor (unit 0 or 1, channel A-D) */
#define RZV_POEG_BASE(unit, ch) \
  (((unit) == 0u) \
    ? (RZV_POEG0A_BASE + (uintptr_t)(ch) * 0x400u) \
    : (RZV_POEG1A_BASE + (uintptr_t)(ch) * 0x400u))

#define RZV_POEG_POEGGn(unit, ch)  (RZV_POEG_BASE(unit, ch) + RZV_POEG_POEGGn_OFFSET)

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_POEG_H */

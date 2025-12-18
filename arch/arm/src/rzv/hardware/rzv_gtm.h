/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_gtm.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_GTM_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_GTM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GTM Base Addresses ****************************************************/

#ifndef RZV_GTM0_BASE
#  define RZV_GTM0_BASE               0x11800000
#endif
#ifndef RZV_GTM1_BASE
#  define RZV_GTM1_BASE               0x11801000
#endif
#ifndef RZV_GTM2_BASE
#  define RZV_GTM2_BASE               0x14000000
#endif
#ifndef RZV_GTM3_BASE
#  define RZV_GTM3_BASE               0x14001000
#endif
#ifndef RZV_GTM4_BASE
#  define RZV_GTM4_BASE               0x12C00000
#endif
#ifndef RZV_GTM5_BASE
#  define RZV_GTM5_BASE               0x12C01000
#endif
#ifndef RZV_GTM6_BASE
#  define RZV_GTM6_BASE               0x12C02000
#endif
#ifndef RZV_GTM7_BASE
#  define RZV_GTM7_BASE               0x12C03000
#endif

/* GTM Channel definitions */
#define RZV_GTM_CHANNEL_0          0
#define RZV_GTM_CHANNEL_1          1
#define RZV_GTM_CHANNEL_2          2
#define RZV_GTM_CHANNEL_3          3
#define RZV_GTM_CHANNEL_4          4
#define RZV_GTM_CHANNEL_5          5
#define RZV_GTM_CHANNEL_6          6
#define RZV_GTM_CHANNEL_7          7

/* Maximum number of GTM channels */
#define RZV_GTM_MAX_CHANNELS       8

/* Convenience/compatibility aliases used by driver code */
/* Offsets derived from the Renesas OSTM I/O layout (per-channel) */
#define RZV_GTM_OSTMCMP_OFFSET    (0x00) /* OSTMnCMP */
#define RZV_GTM_OSTMCNT_OFFSET    (0x04) /* OSTMnCNT */
#define RZV_GTM_OSTMTE_OFFSET     (0x10) /* OSTMnTE */
#define RZV_GTM_OSTMTS_OFFSET     (0x14) /* OSTMnTS */
#define RZV_GTM_OSTMTT_OFFSET     (0x18) /* OSTMnTT */
#define RZV_GTM_OSTMCTL_OFFSET    (0x20) /* OSTMnCTL */

/* Parameterized offsets: per-OSTM channel. Use these when computing
 * addresses for a given channel index 'n'. The per-channel stride
 * follows the Renesas OSTM layout (0x24 bytes per channel).
 */
#define RZV_GTM_OSTM_CHANNEL_STRIDE    (0x24)
#define RZV_GTM_OSTMCMP_OFFSET_N(n)    (0x00 + ((n) * RZV_GTM_OSTM_CHANNEL_STRIDE))
#define RZV_GTM_OSTMCNT_OFFSET_N(n)    (0x04 + ((n) * RZV_GTM_OSTM_CHANNEL_STRIDE))
#define RZV_GTM_OSTMTE_OFFSET_N(n)     (0x10 + ((n) * RZV_GTM_OSTM_CHANNEL_STRIDE))
#define RZV_GTM_OSTMTS_OFFSET_N(n)     (0x14 + ((n) * RZV_GTM_OSTM_CHANNEL_STRIDE))
#define RZV_GTM_OSTMTT_OFFSET_N(n)     (0x18 + ((n) * RZV_GTM_OSTM_CHANNEL_STRIDE))
#define RZV_GTM_OSTMCTL_OFFSET_N(n)    (0x20 + ((n) * RZV_GTM_OSTM_CHANNEL_STRIDE))

/* Bitmask  */
#  define GTM_OSTMTT_OSTMTT       (1 << 0)
#  define GTM_OSTMTS_OSTMTS       (1 << 0)
#  define GTM_OSTMCMP_MASK        (0xffffffffu)


#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_GTM_H */

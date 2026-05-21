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

/* GTM has NO prescaler — counter runs directly from the GTM source clock
 * (P1CLK = 100 MHz on RZ/V2H, BSP_FEATURE_GTM_SOURCE_CLOCK).
 * Do not add prescaler divider
 * stubs; they are not backed by hardware registers.
 */

/* GTM Base Addresses — each GTM instance has its own 4 KiB region.
 * Addresses verified against R9A09G057H/cr/iodefines/gtm_iodefine.h.
 * Use the per-instance base table (g_gtm_base[] in rzv_gtm.c) — do NOT
 * compute addresses via stride arithmetic from a single base.
 ************************************************************************/

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

/* Register Offsets within each GTM instance (verified vs gtm_iodefine.h) */

#define RZV_GTM_OSTMCMP_OFFSET    (0x00) /* OSTMnCMP: compare/period (RW 32-bit) */
#define RZV_GTM_OSTMCNT_OFFSET    (0x04) /* OSTMnCNT: counter (RO 32-bit) */
#define RZV_GTM_OSTMTE_OFFSET     (0x10) /* OSTMnTE:  timer enable status (RO 8-bit) */
#define RZV_GTM_OSTMTS_OFFSET     (0x14) /* OSTMnTS:  timer start (WO 8-bit) */
#define RZV_GTM_OSTMTT_OFFSET     (0x18) /* OSTMnTT:  timer stop  (WO 8-bit) */
#define RZV_GTM_OSTMCTL_OFFSET    (0x20) /* OSTMnCTL: control     (RW 8-bit) */

/* NOTE: Stride-based macros (*_OFFSET_N(n)) are intentionally removed.
 * Each GTM has its own 4 KiB base; stride arithmetic is WRONG across
 * channels.  Always use per-channel base from g_gtm_base[] + the offsets
 * above.
 */

/* Register Bit Definitions */

/* OSTMnCTL Register Bit Definitions */
#define GTM_OSTMCTL_MD0         (1 << 0)  /* Interrupt on start enable */
#define GTM_OSTMCTL_MD1         (1 << 1)  /* Timer mode: 1=free-run, 0=interval */

/* OSTMnTE Register Bit Definitions */
#define GTM_OSTMTE_TE           (1 << 0)  /* Timer enable status (read-only) */

/* OSTMnTS Register Bit Definitions */
#define GTM_OSTMTS_OSTMTS       (1 << 0)  /* Start timer */

/* OSTMnTT Register Bit Definitions */
#define GTM_OSTMTT_OSTMTT       (1 << 0)  /* Stop timer */

/* OSTMnCMP Register Bit Definitions */
#define GTM_OSTMCMP_MASK        (0xffffffffu)  /* 32-bit compare value */

/* Timer Modes */
#define GTM_MODE_INTERVAL       (0)                      /* MD1=0: interval — auto-reload OSTMCMP, periodic IRQ */
#define GTM_MODE_FREERUN        (GTM_OSTMCTL_MD1)        /* MD1=1: free-run — compare fires once, counter continues */


#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_GTM_H */

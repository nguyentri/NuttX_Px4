/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_wdt.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_WDT_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_WDT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* WDT Base Addresses ****************************************************/

#ifndef RZV_WDT0_BASE
#  define RZV_WDT0_BASE               0x11C00400
#endif
#ifndef RZV_WDT1_BASE
#  define RZV_WDT1_BASE               0x14400000
#endif
#ifndef RZV_WDT2_BASE
#  define RZV_WDT2_BASE               0x13000000
#endif
#ifndef RZV_WDT3_BASE
#  define RZV_WDT3_BASE               0x13000400
#endif

/* WDT Register Offsets ***************************************************/

#define RZV_WDT_WDTRR_OFFSET                             0x0000  /* Watchdog Timer Refresh Register */
#define RZV_WDT_WDTCR_OFFSET                             0x0002  /* Watchdog Timer Control Register */
#define RZV_WDT_WDTSR_OFFSET                             0x0004  /* Watchdog Timer Status Register */
#define RZV_WDT_WDTRCR_OFFSET                            0x0006  /* Watchdog Timer Reset Control Register */

/* WDT Register Addresses **************************************************/

#define RZV_WDT_WDTRR(ch)                            (RZV_WDT##ch##_BASE + RZV_WDT_WDTRR_OFFSET)
#define RZV_WDT_WDTCR(ch)                            (RZV_WDT##ch##_BASE + RZV_WDT_WDTCR_OFFSET)
#define RZV_WDT_WDTSR(ch)                            (RZV_WDT##ch##_BASE + RZV_WDT_WDTSR_OFFSET)
#define RZV_WDT_WDTRCR(ch)                           (RZV_WDT##ch##_BASE + RZV_WDT_WDTRCR_OFFSET)

/* WDT WDTCR Register Bit Definitions ********************************/

#define WDT_WDTCR_TOPS_SHIFT                    (0)      /* Bits 0-1: Tops */
#define WDT_WDTCR_TOPS_MASK                     (0x3 << WDT_WDTCR_TOPS_SHIFT)

#define WDT_WDTCR_CKS_SHIFT                     (4)      /* Bits 4-7: Cks */
#define WDT_WDTCR_CKS_MASK                      (0xf << WDT_WDTCR_CKS_SHIFT)

#define WDT_WDTCR_RPES_SHIFT                    (8)      /* Bits 8-9: Rpes */
#define WDT_WDTCR_RPES_MASK                     (0x3 << WDT_WDTCR_RPES_SHIFT)

#define WDT_WDTCR_RPSS_SHIFT                    (12)      /* Bits 12-13: Rpss */
#define WDT_WDTCR_RPSS_MASK                     (0x3 << WDT_WDTCR_RPSS_SHIFT)

/* WDT WDTRCR Register Bit Definitions: see WDTRCR section below */

/* WDT WDTRR Register Bit Definitions ********************************/

#define WDT_WDTRR_REFRESH_SHIFT                 (0)      /* Bits 0-7: Refresh */
#define WDT_WDTRR_REFRESH_MASK                  (0xff << WDT_WDTRR_REFRESH_SHIFT)

/* WDT WDTSR Register Bit Definitions ********************************/

#define WDT_WDTSR_CNTVAL_SHIFT  (0)      /* Bits 0-13: Counter Value */
#define WDT_WDTSR_CNTVAL_MASK   (0x3fff << WDT_WDTSR_CNTVAL_SHIFT)
#define WDT_WDTSR_UNDFF         (1 << 14) /* Underflow Flag */
#define WDT_WDTSR_REFEF         (1 << 15) /* Refresh Error Flag */

/* WDT Reset Control Register (WDTRCR) *************************************/

#define WDT_WDTRCR_RSTIRQS                      (1 << 7)  /* Reset Interrupt Request Select */
#  define WDT_WDTRCR_RSTIRQS_RESET_REQ          (0 << 7)  /* Reset request */
#  define WDT_WDTRCR_RSTIRQS_INT_REQ            (1 << 7)  /* Interrupt request */

/* WDT Channel definitions */
#define RZV_WDT_CHANNEL_0          0
#define RZV_WDT_CHANNEL_1          1
#define RZV_WDT_CHANNEL_2          2
#define RZV_WDT_CHANNEL_3          3

/* Maximum number of WDT channels */
#define RZV_WDT_MAX_CHANNELS       4

/* CPG bring-up helpers for RZ/V2H (R9A09G057H).
 *
 * Derived from FSP bsp_override.h lines 1745-1772:
 *   - WDT_CLKP: ch=0..2 in CPG_CLKON_4 (bits 11/13/15), ch=3 in CPG_CLKON_5 (bit 1)
 *   - WDT_LOCO: ch=0,1 in CPG_CLKON_4 (bits 12/14), ch=2,3 in CPG_CLKON_5 (bits 0/2)
 *   - Reset:    CPG_RST_7 bits 5..8 = WDT ch 0..3
 *   - Monitor:  CPG_RSTMON_3 bits 6..9 = WDT ch 0..3
 *   - Underflow→system-reset routing: CPG_ERRORRST_SEL2 bits 0..3 = WDT ch 0..3,
 *     WEN companions at +16.
 * MSTOP is intentionally absent — FSP leaves it undefined for WDT on this MCU.
 */

#define RZV_CPG_CLK_WEN_SHIFT                  16

#define RZV_CPG_CLKON_WDT_CLKP_M(ch)           ((ch) < 3 ? 4 : 5)
#define RZV_CPG_CLKON_WDT_LOCO_M(ch)           ((ch) < 2 ? 4 : 5)

#define RZV_CPG_CLKON_WDT_CLKP_BIT(ch)         ((ch) < 3 ? (1u << (11 + 2 * (ch))) : (1u << 1))
#define RZV_CPG_CLKON_WDT_LOCO_BIT(ch)         ((ch) < 2 ? (1u << (12 + 2 * (ch))) \
                                                         : (1u << (2 * ((ch) - 2))))

/* CLKMON: per FSP all WDT monitor bits live in CLKMON_2 at CLK11/CLK12 base */
#define RZV_CPG_CLKMON_WDT_M                   2

#define RZV_CPG_RST_WDT_M                      7
#define RZV_CPG_RST_WDT_BIT(ch)                (1u << (5 + (ch)))
#define RZV_CPG_RSTMON_WDT_M                   3
#define RZV_CPG_RSTMON_WDT_BIT(ch)             (1u << (6 + (ch)))

#define RZV_CPG_ERRORRST_SEL2_M                2
#define RZV_CPG_ERRORRST_SEL2_BIT(ch)          (1u << (ch))
#define RZV_CPG_ERRORRST_SEL2_WEN(ch)          (1u << (16 + (ch)))

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_WDT_H */

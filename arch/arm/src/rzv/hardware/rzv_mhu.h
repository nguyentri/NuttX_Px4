/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_mhu.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_MHU_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_MHU_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* MHU Base Addresses — three access-window aliases per MHU instance.
 *
 * RZ/V2H has one MHU block with channels accessible from three security
 * domains (offsets within the 0x10480000 block):
 *   NS    (Non-Secure):        base + 0x000000
 *   S_CR8 (Secure, CR8):       base + 0x000800
 *   S_CM33 (Secure, CM33):     base + 0x001000
 *
 * Bug fix: the original header wrapped each alias in
 *   #ifndef RZV_MHU<n>_BASE ... #endif
 * using the SAME symbol name for all three, so only the first definition
 * ever survived.  This rewrite names each domain alias distinctly and
 * selects one canonical RZV_MHU<n>_BASE via CONFIG_RZV_MHU_DOMAIN_*.
 * The default (NS) matches the address resolved by the original header
 * for the CA55 rptun path — no behavioral change for :ipcc / :nsh builds.
 *
 * Consumers that legitimately need a non-default domain alias include the
 * alias macro directly (e.g. RZV_MHU0_S_CR8_BASE) rather than the
 * generic RZV_MHU0_BASE.
 *
 ****************************************************************************/

/* Per-domain aliases — MHU0 */
#define RZV_MHU0_NS_BASE             0x10480000u
#define RZV_MHU0_S_CR8_BASE          0x10480800u
#define RZV_MHU0_S_CM33_BASE         0x10481000u

/* Per-domain aliases — MHU1 through MHU9 (channels at stride 0x20) */
#define RZV_MHU1_NS_BASE             0x10480020u
#define RZV_MHU1_S_CR8_BASE          0x10480820u  /* corrected from 0x810 */
#define RZV_MHU1_S_CM33_BASE         0x10481020u

#define RZV_MHU2_NS_BASE             0x10480040u
#define RZV_MHU2_S_CR8_BASE          0x10480840u  /* corrected from 0x820 */
#define RZV_MHU2_S_CM33_BASE         0x10481040u

#define RZV_MHU3_NS_BASE             0x10480060u
#define RZV_MHU3_S_CR8_BASE          0x10480860u  /* corrected from 0x830 */
#define RZV_MHU3_S_CM33_BASE         0x10481060u

#define RZV_MHU4_NS_BASE             0x10480080u
#define RZV_MHU4_S_CR8_BASE          0x10480880u  /* corrected from 0x840 */
#define RZV_MHU4_S_CM33_BASE         0x10481080u

#define RZV_MHU5_NS_BASE             0x104800a0u
#define RZV_MHU5_S_CR8_BASE          0x104808a0u  /* corrected from 0x850 */
#define RZV_MHU5_S_CM33_BASE         0x104810a0u

#define RZV_MHU6_NS_BASE             0x104800c0u
#define RZV_MHU6_S_CR8_BASE          0x104808c0u  /* corrected from 0x860 */
#define RZV_MHU6_S_CM33_BASE         0x104810c0u

#define RZV_MHU7_NS_BASE             0x104800e0u
#define RZV_MHU7_S_CR8_BASE          0x104808e0u  /* corrected from 0x870 */
#define RZV_MHU7_S_CM33_BASE         0x104810e0u

#define RZV_MHU8_NS_BASE             0x10480100u
#define RZV_MHU8_S_CR8_BASE          0x10480900u  /* corrected from 0x880 */
#define RZV_MHU8_S_CM33_BASE         0x10481100u

#define RZV_MHU9_NS_BASE             0x10480120u
#define RZV_MHU9_S_CR8_BASE          0x10480920u  /* corrected from 0x890 */
#define RZV_MHU9_S_CM33_BASE         0x10481120u

/* Per-domain aliases — MHU10 through MHU19 */
#define RZV_MHU10_NS_BASE            0x10480140u
#define RZV_MHU10_S_CR8_BASE         0x10480940u
#define RZV_MHU10_S_CM33_BASE        0x10481140u

#define RZV_MHU11_NS_BASE            0x10480160u
#define RZV_MHU11_S_CR8_BASE         0x10480960u
#define RZV_MHU11_S_CM33_BASE        0x10481160u

#define RZV_MHU12_NS_BASE            0x10480180u
#define RZV_MHU12_S_CR8_BASE         0x10480980u
#define RZV_MHU12_S_CM33_BASE        0x10481180u

#define RZV_MHU13_NS_BASE            0x104801a0u
#define RZV_MHU13_S_CR8_BASE         0x104809a0u
#define RZV_MHU13_S_CM33_BASE        0x104811a0u

#define RZV_MHU14_NS_BASE            0x104801c0u
#define RZV_MHU14_S_CR8_BASE         0x104809c0u
#define RZV_MHU14_S_CM33_BASE        0x104811c0u

#define RZV_MHU15_NS_BASE            0x104801e0u
#define RZV_MHU15_S_CR8_BASE         0x104809e0u
#define RZV_MHU15_S_CM33_BASE        0x104811e0u

#define RZV_MHU16_NS_BASE            0x10480200u
#define RZV_MHU16_S_CR8_BASE         0x10480a00u
#define RZV_MHU16_S_CM33_BASE        0x10481200u

#define RZV_MHU17_NS_BASE            0x10480220u
#define RZV_MHU17_S_CR8_BASE         0x10480a20u
#define RZV_MHU17_S_CM33_BASE        0x10481220u

#define RZV_MHU18_NS_BASE            0x10480240u
#define RZV_MHU18_S_CR8_BASE         0x10480a40u
#define RZV_MHU18_S_CM33_BASE        0x10481240u

#define RZV_MHU19_NS_BASE            0x10480260u
#define RZV_MHU19_S_CR8_BASE         0x10480a60u
#define RZV_MHU19_S_CM33_BASE        0x10481260u

/* Per-domain aliases — MHU20 through MHU29 */
#define RZV_MHU20_NS_BASE            0x10480280u
#define RZV_MHU20_S_CR8_BASE         0x10480a80u
#define RZV_MHU20_S_CM33_BASE        0x10481280u

#define RZV_MHU21_NS_BASE            0x104802a0u
#define RZV_MHU21_S_CR8_BASE         0x10480aa0u
#define RZV_MHU21_S_CM33_BASE        0x104812a0u

#define RZV_MHU22_NS_BASE            0x104802c0u
#define RZV_MHU22_S_CR8_BASE         0x10480ac0u
#define RZV_MHU22_S_CM33_BASE        0x104812c0u

#define RZV_MHU23_NS_BASE            0x104802e0u
#define RZV_MHU23_S_CR8_BASE         0x10480ae0u
#define RZV_MHU23_S_CM33_BASE        0x104812e0u

#define RZV_MHU24_NS_BASE            0x10480300u
#define RZV_MHU24_S_CR8_BASE         0x10480b00u
#define RZV_MHU24_S_CM33_BASE        0x10481300u

#define RZV_MHU25_NS_BASE            0x10480320u
#define RZV_MHU25_S_CR8_BASE         0x10480b20u
#define RZV_MHU25_S_CM33_BASE        0x10481320u

#define RZV_MHU26_NS_BASE            0x10480340u
#define RZV_MHU26_S_CR8_BASE         0x10480b40u
#define RZV_MHU26_S_CM33_BASE        0x10481340u

#define RZV_MHU27_NS_BASE            0x10480360u
#define RZV_MHU27_S_CR8_BASE         0x10480b60u
#define RZV_MHU27_S_CM33_BASE        0x10481360u

#define RZV_MHU28_NS_BASE            0x10480380u
#define RZV_MHU28_S_CM33_BASE        0x10481380u

#define RZV_MHU29_NS_BASE            0x104803a0u
#define RZV_MHU29_S_CM33_BASE        0x104813a0u

/* Per-domain aliases — MHU30 through MHU41 */
#define RZV_MHU30_NS_BASE            0x104803c0u
#define RZV_MHU30_S_CM33_BASE        0x104813c0u

#define RZV_MHU31_NS_BASE            0x104803e0u
#define RZV_MHU31_S_CM33_BASE        0x104813e0u

#define RZV_MHU32_NS_BASE            0x10480400u
#define RZV_MHU32_S_CM33_BASE        0x10481400u

#define RZV_MHU33_NS_BASE            0x10480420u
#define RZV_MHU33_S_CM33_BASE        0x10481420u

#define RZV_MHU34_NS_BASE            0x10480440u
#define RZV_MHU34_S_CM33_BASE        0x10481440u

#define RZV_MHU35_NS_BASE            0x10480460u
#define RZV_MHU35_S_CM33_BASE        0x10481460u

#define RZV_MHU36_NS_BASE            0x10480480u
#define RZV_MHU36_S_CM33_BASE        0x10481480u

#define RZV_MHU37_NS_BASE            0x104804a0u
#define RZV_MHU37_S_CM33_BASE        0x104814a0u

#define RZV_MHU38_NS_BASE            0x104804c0u
#define RZV_MHU38_S_CM33_BASE        0x104814c0u

#define RZV_MHU39_NS_BASE            0x104804e0u
#define RZV_MHU39_S_CM33_BASE        0x104814e0u

#define RZV_MHU40_NS_BASE            0x10480500u
#define RZV_MHU40_S_CM33_BASE        0x10481500u

#define RZV_MHU41_NS_BASE            0x10480520u
#define RZV_MHU41_S_CM33_BASE        0x10481520u

/* Canonical RZV_MHU<n>_BASE selection by domain.
 *
 * Default: NS (Non-Secure) — matches the value the original buggy header
 * resolved to for the CA55 rptun path (ch3 of MHU0 NS at 0x10480000).
 * Override per-target via Kconfig CONFIG_RZV_MHU_DOMAIN_*.
 *
 * Only MHU0–MHU27 have an S_CR8 window; MHU28+ are NS or CM33 only.
 * Only MHU0–MHU9 have all three windows.
 *
 * TODO(IPC-NEXT): when the S_CR8 window is needed for raw CR8↔CR8 path,
 *                 select RZV_MHU_DOMAIN_S_CR8 in ipcc-multi defconfig and
 *                 verify MPU permissions cover 0x10480800 range.
 *
 ****************************************************************************/

#if defined(CONFIG_RZV_MHU_DOMAIN_S_CR8)

#  define RZV_MHU0_BASE    RZV_MHU0_S_CR8_BASE
#  define RZV_MHU1_BASE    RZV_MHU1_S_CR8_BASE
#  define RZV_MHU2_BASE    RZV_MHU2_S_CR8_BASE
#  define RZV_MHU3_BASE    RZV_MHU3_S_CR8_BASE
#  define RZV_MHU4_BASE    RZV_MHU4_S_CR8_BASE
#  define RZV_MHU5_BASE    RZV_MHU5_S_CR8_BASE
#  define RZV_MHU6_BASE    RZV_MHU6_S_CR8_BASE
#  define RZV_MHU7_BASE    RZV_MHU7_S_CR8_BASE
#  define RZV_MHU8_BASE    RZV_MHU8_S_CR8_BASE
#  define RZV_MHU9_BASE    RZV_MHU9_S_CR8_BASE
#  define RZV_MHU10_BASE   RZV_MHU10_S_CR8_BASE
#  define RZV_MHU11_BASE   RZV_MHU11_S_CR8_BASE
#  define RZV_MHU12_BASE   RZV_MHU12_S_CR8_BASE
#  define RZV_MHU13_BASE   RZV_MHU13_S_CR8_BASE
#  define RZV_MHU14_BASE   RZV_MHU14_S_CR8_BASE
#  define RZV_MHU15_BASE   RZV_MHU15_S_CR8_BASE
#  define RZV_MHU16_BASE   RZV_MHU16_S_CR8_BASE
#  define RZV_MHU17_BASE   RZV_MHU17_S_CR8_BASE
#  define RZV_MHU18_BASE   RZV_MHU18_S_CR8_BASE
#  define RZV_MHU19_BASE   RZV_MHU19_S_CR8_BASE
#  define RZV_MHU20_BASE   RZV_MHU20_S_CR8_BASE
#  define RZV_MHU21_BASE   RZV_MHU21_S_CR8_BASE
#  define RZV_MHU22_BASE   RZV_MHU22_S_CR8_BASE
#  define RZV_MHU23_BASE   RZV_MHU23_S_CR8_BASE
#  define RZV_MHU24_BASE   RZV_MHU24_S_CR8_BASE
#  define RZV_MHU25_BASE   RZV_MHU25_S_CR8_BASE
#  define RZV_MHU26_BASE   RZV_MHU26_S_CR8_BASE
#  define RZV_MHU27_BASE   RZV_MHU27_S_CR8_BASE
/* MHU28+ have no S_CR8 window; fall back to NS */
#  define RZV_MHU28_BASE   RZV_MHU28_NS_BASE
#  define RZV_MHU29_BASE   RZV_MHU29_NS_BASE
#  define RZV_MHU30_BASE   RZV_MHU30_NS_BASE
#  define RZV_MHU31_BASE   RZV_MHU31_NS_BASE
#  define RZV_MHU32_BASE   RZV_MHU32_NS_BASE
#  define RZV_MHU33_BASE   RZV_MHU33_NS_BASE
#  define RZV_MHU34_BASE   RZV_MHU34_NS_BASE
#  define RZV_MHU35_BASE   RZV_MHU35_NS_BASE
#  define RZV_MHU36_BASE   RZV_MHU36_NS_BASE
#  define RZV_MHU37_BASE   RZV_MHU37_NS_BASE
#  define RZV_MHU38_BASE   RZV_MHU38_NS_BASE
#  define RZV_MHU39_BASE   RZV_MHU39_NS_BASE
#  define RZV_MHU40_BASE   RZV_MHU40_NS_BASE
#  define RZV_MHU41_BASE   RZV_MHU41_NS_BASE

#elif defined(CONFIG_RZV_MHU_DOMAIN_S_CM33)

#  define RZV_MHU0_BASE    RZV_MHU0_S_CM33_BASE
#  define RZV_MHU1_BASE    RZV_MHU1_S_CM33_BASE
#  define RZV_MHU2_BASE    RZV_MHU2_S_CM33_BASE
#  define RZV_MHU3_BASE    RZV_MHU3_S_CM33_BASE
#  define RZV_MHU4_BASE    RZV_MHU4_S_CM33_BASE
#  define RZV_MHU5_BASE    RZV_MHU5_S_CM33_BASE
#  define RZV_MHU6_BASE    RZV_MHU6_S_CM33_BASE
#  define RZV_MHU7_BASE    RZV_MHU7_S_CM33_BASE
#  define RZV_MHU8_BASE    RZV_MHU8_S_CM33_BASE
#  define RZV_MHU9_BASE    RZV_MHU9_S_CM33_BASE
#  define RZV_MHU10_BASE   RZV_MHU10_S_CM33_BASE
#  define RZV_MHU11_BASE   RZV_MHU11_S_CM33_BASE
#  define RZV_MHU12_BASE   RZV_MHU12_S_CM33_BASE
#  define RZV_MHU13_BASE   RZV_MHU13_S_CM33_BASE
#  define RZV_MHU14_BASE   RZV_MHU14_S_CM33_BASE
#  define RZV_MHU15_BASE   RZV_MHU15_S_CM33_BASE
#  define RZV_MHU16_BASE   RZV_MHU16_S_CM33_BASE
#  define RZV_MHU17_BASE   RZV_MHU17_S_CM33_BASE
#  define RZV_MHU18_BASE   RZV_MHU18_S_CM33_BASE
#  define RZV_MHU19_BASE   RZV_MHU19_S_CM33_BASE
#  define RZV_MHU20_BASE   RZV_MHU20_S_CM33_BASE
#  define RZV_MHU21_BASE   RZV_MHU21_S_CM33_BASE
#  define RZV_MHU22_BASE   RZV_MHU22_S_CM33_BASE
#  define RZV_MHU23_BASE   RZV_MHU23_S_CM33_BASE
#  define RZV_MHU24_BASE   RZV_MHU24_S_CM33_BASE
#  define RZV_MHU25_BASE   RZV_MHU25_S_CM33_BASE
#  define RZV_MHU26_BASE   RZV_MHU26_S_CM33_BASE
#  define RZV_MHU27_BASE   RZV_MHU27_S_CM33_BASE
#  define RZV_MHU28_BASE   RZV_MHU28_S_CM33_BASE
#  define RZV_MHU29_BASE   RZV_MHU29_S_CM33_BASE
#  define RZV_MHU30_BASE   RZV_MHU30_S_CM33_BASE
#  define RZV_MHU31_BASE   RZV_MHU31_S_CM33_BASE
#  define RZV_MHU32_BASE   RZV_MHU32_S_CM33_BASE
#  define RZV_MHU33_BASE   RZV_MHU33_S_CM33_BASE
#  define RZV_MHU34_BASE   RZV_MHU34_S_CM33_BASE
#  define RZV_MHU35_BASE   RZV_MHU35_S_CM33_BASE
#  define RZV_MHU36_BASE   RZV_MHU36_S_CM33_BASE
#  define RZV_MHU37_BASE   RZV_MHU37_S_CM33_BASE
#  define RZV_MHU38_BASE   RZV_MHU38_S_CM33_BASE
#  define RZV_MHU39_BASE   RZV_MHU39_S_CM33_BASE
#  define RZV_MHU40_BASE   RZV_MHU40_S_CM33_BASE
#  define RZV_MHU41_BASE   RZV_MHU41_S_CM33_BASE

#else /* default: NS (Non-Secure) — preserves existing CA55 rptun behavior */

#  define RZV_MHU0_BASE    RZV_MHU0_NS_BASE
#  define RZV_MHU1_BASE    RZV_MHU1_NS_BASE
#  define RZV_MHU2_BASE    RZV_MHU2_NS_BASE
#  define RZV_MHU3_BASE    RZV_MHU3_NS_BASE
#  define RZV_MHU4_BASE    RZV_MHU4_NS_BASE
#  define RZV_MHU5_BASE    RZV_MHU5_NS_BASE
#  define RZV_MHU6_BASE    RZV_MHU6_NS_BASE
#  define RZV_MHU7_BASE    RZV_MHU7_NS_BASE
#  define RZV_MHU8_BASE    RZV_MHU8_NS_BASE
#  define RZV_MHU9_BASE    RZV_MHU9_NS_BASE
#  define RZV_MHU10_BASE   RZV_MHU10_NS_BASE
#  define RZV_MHU11_BASE   RZV_MHU11_NS_BASE
#  define RZV_MHU12_BASE   RZV_MHU12_NS_BASE
#  define RZV_MHU13_BASE   RZV_MHU13_NS_BASE
#  define RZV_MHU14_BASE   RZV_MHU14_NS_BASE
#  define RZV_MHU15_BASE   RZV_MHU15_NS_BASE
#  define RZV_MHU16_BASE   RZV_MHU16_NS_BASE
#  define RZV_MHU17_BASE   RZV_MHU17_NS_BASE
#  define RZV_MHU18_BASE   RZV_MHU18_NS_BASE
#  define RZV_MHU19_BASE   RZV_MHU19_NS_BASE
#  define RZV_MHU20_BASE   RZV_MHU20_NS_BASE
#  define RZV_MHU21_BASE   RZV_MHU21_NS_BASE
#  define RZV_MHU22_BASE   RZV_MHU22_NS_BASE
#  define RZV_MHU23_BASE   RZV_MHU23_NS_BASE
#  define RZV_MHU24_BASE   RZV_MHU24_NS_BASE
#  define RZV_MHU25_BASE   RZV_MHU25_NS_BASE
#  define RZV_MHU26_BASE   RZV_MHU26_NS_BASE
#  define RZV_MHU27_BASE   RZV_MHU27_NS_BASE
#  define RZV_MHU28_BASE   RZV_MHU28_NS_BASE
#  define RZV_MHU29_BASE   RZV_MHU29_NS_BASE
#  define RZV_MHU30_BASE   RZV_MHU30_NS_BASE
#  define RZV_MHU31_BASE   RZV_MHU31_NS_BASE
#  define RZV_MHU32_BASE   RZV_MHU32_NS_BASE
#  define RZV_MHU33_BASE   RZV_MHU33_NS_BASE
#  define RZV_MHU34_BASE   RZV_MHU34_NS_BASE
#  define RZV_MHU35_BASE   RZV_MHU35_NS_BASE
#  define RZV_MHU36_BASE   RZV_MHU36_NS_BASE
#  define RZV_MHU37_BASE   RZV_MHU37_NS_BASE
#  define RZV_MHU38_BASE   RZV_MHU38_NS_BASE
#  define RZV_MHU39_BASE   RZV_MHU39_NS_BASE
#  define RZV_MHU40_BASE   RZV_MHU40_NS_BASE
#  define RZV_MHU41_BASE   RZV_MHU41_NS_BASE

#endif /* CONFIG_RZV_MHU_DOMAIN_* */

/* MHU Register Offsets (per channel; stride = 0x20)
 *
 * Within each MHU "channel slot" (0x20 bytes):
 *   MSG (incoming to receiver):
 *     +0x00  MSG_INT_STSn  — status (read)
 *     +0x04  MSG_INT_SETn  — set (write)
 *     +0x08  MSG_INT_CLRn  — clear (write)
 *   RSP (response, outgoing from receiver):
 *     +0x10  RSP_INT_STSn
 *     +0x14  RSP_INT_SETn
 *     +0x18  RSP_INT_CLRn
 *   SW (software interrupt):
 *     +0x20  SW_INT_STSn
 *     +0x24  SW_INT_SETn
 *     +0x28  SW_INT_CLRn
 *
 * rzv_rproc.c uses its own local offset constants; keep these here for
 * consumers that include this header without rzv_mhu_core.h.
 *
 ****************************************************************************/

#define RZV_MHU_CH_STRIDE            0x20u
#define RZV_MHU_MSG_STS_OFF          0x00u
#define RZV_MHU_MSG_SET_OFF          0x04u
#define RZV_MHU_MSG_CLR_OFF          0x08u
#define RZV_MHU_RSP_STS_OFF          0x10u
#define RZV_MHU_RSP_SET_OFF          0x14u
#define RZV_MHU_RSP_CLR_OFF          0x18u
#define RZV_MHU_SW_STS_OFF           0x20u
#define RZV_MHU_SW_SET_OFF           0x24u
#define RZV_MHU_SW_CLR_OFF           0x28u

/* MHU MSG_INT_CLRn Register Bit Definitions */
#define MHU_MSG_INT_CLRn_CLEAR       (1 << 0)

/* MHU MSG_INT_SETn Register Bit Definitions */
#define MHU_MSG_INT_SETn_SET         (1 << 0)

/* MHU MSG_INT_STSn Register Bit Definitions */
#define MHU_MSG_INT_STSn_STAT        (1 << 0)

/* MHU RSP_INT_CLRn Register Bit Definitions */
#define MHU_RSP_INT_CLRn_CLEAR       (1 << 0)

/* MHU RSP_INT_SETn Register Bit Definitions */
#define MHU_RSP_INT_SETn_SET         (1 << 0)

/* MHU RSP_INT_STSn Register Bit Definitions */
#define MHU_RSP_INT_STSn_STAT        (1 << 0)

/* MHU SW_INT_CLRn Register Bit Definitions */
#define MHU_SW_INT_CLRn_CLEAR        (1 << 0)

/* MHU SW_INT_SETn Register Bit Definitions */
#define MHU_SW_INT_SETn_SET          (1 << 0)

/* MHU SW_INT_STSn Register Bit Definitions */
#define MHU_SW_INT_STSn_STAT         (1 << 0)

/* Maximum number of MHU channels (42 total per window) */
#define RZV_MHU_MAX_CHANNELS         42u

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_MHU_H */

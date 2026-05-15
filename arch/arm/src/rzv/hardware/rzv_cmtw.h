/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_cmtw.h
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

/* DORMANT — DO NOT USE in rdk-rzv2h builds.
 * CMTW is present on some RZ variants but is not wired into the
 * RZ/V2H (R9A09G057H) NuttX port.  The GTM channels (rzv_gtm.c)
 * and ARM private timer (rzv_timerisr.c) are the active timer paths.
 * This header is retained so future RZ variants that require CMTW can
 * extend it without losing register layout knowledge from the FSP.
 */

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_CMTW_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_CMTW_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CMTW Base Addresses ***************************************************/

#ifndef RZV_CMTW0_BASE
#  define RZV_CMTW0_BASE              0x11C01800
#endif
#ifndef RZV_CMTW1_BASE
#  define RZV_CMTW1_BASE              0x11C01C00
#endif
#ifndef RZV_CMTW2_BASE
#  define RZV_CMTW2_BASE              0x11C02000
#endif
#ifndef RZV_CMTW3_BASE
#  define RZV_CMTW3_BASE              0x11C02400
#endif
#ifndef RZV_CMTW4_BASE
#  define RZV_CMTW4_BASE              0x13000C00
#endif
#ifndef RZV_CMTW5_BASE
#  define RZV_CMTW5_BASE              0x13001000
#endif
#ifndef RZV_CMTW6_BASE
#  define RZV_CMTW6_BASE              0x13001400
#endif
#ifndef RZV_CMTW7_BASE
#  define RZV_CMTW7_BASE              0x13001800
#endif

/* CMTW Register Offsets **************************************************/

/* CMWICR%s Registers (0-1) */
#define RZV_CMTW_CMWICR_OFFSET(m)               (0x00000018 + ((m) * 0x00000004))  /* CMWICR Register %s */
/* CMWOCR%s Registers (0-1) */
#define RZV_CMTW_CMWOCR_OFFSET(m)               (0x00000020 + ((m) * 0x00000004))  /* CMWOCR Register %s */
#define RZV_CMTW_CMWSTR_OFFSET                           0x0000  /* Compare Match Timer W Start Register */
#define RZV_CMTW_CMWCR_OFFSET                            0x0004  /* Compare Match Timer W Control Register */
#define RZV_CMTW_CMWIOR_OFFSET                           0x0008  /* Compare Match Timer W I/O Control Register */
#define RZV_CMTW_CMWCNT_OFFSET                           0x0010  /* Compare Match Timer W Counter */
#define RZV_CMTW_CMWCOR_OFFSET                           0x0014  /* Compare Match Timer W Compare Register */

/* CMTW Register Addresses *************************************************/

#define RZV_CMTW_CMWICR(ch,m)                   (RZV_CMTW##ch##_BASE + RZV_CMTW_CMWICR_OFFSET(m))
#define RZV_CMTW_CMWOCR(ch,m)                   (RZV_CMTW##ch##_BASE + RZV_CMTW_CMWOCR_OFFSET(m))
#define RZV_CMTW_CMWSTR(ch)                          (RZV_CMTW##ch##_BASE + RZV_CMTW_CMWSTR_OFFSET)
#define RZV_CMTW_CMWCR(ch)                           (RZV_CMTW##ch##_BASE + RZV_CMTW_CMWCR_OFFSET)
#define RZV_CMTW_CMWIOR(ch)                          (RZV_CMTW##ch##_BASE + RZV_CMTW_CMWIOR_OFFSET)
#define RZV_CMTW_CMWCNT(ch)                          (RZV_CMTW##ch##_BASE + RZV_CMTW_CMWCNT_OFFSET)
#define RZV_CMTW_CMWCOR(ch)                          (RZV_CMTW##ch##_BASE + RZV_CMTW_CMWCOR_OFFSET)

/* CMTW CMWICR Register Bit Definitions (Parameterized) ********************/

#define CMTW_CMWICR_ICR_SHIFT                             (0)      /* Bits 0-31: Icr */
#define CMTW_CMWICR_ICR_MASK(m)                           (0xffffffff << CMTW_CMWICR_ICR_SHIFT)
#define CMTW_CMWICR_ICR(m,val)                            (((val) << CMTW_CMWICR_ICR_SHIFT) & CMTW_CMWICR_ICR_MASK(m))

/* CMTW CMWOCR Register Bit Definitions (Parameterized) ********************/

#define CMTW_CMWOCR_OCR_SHIFT                             (0)      /* Bits 0-31: Ocr */
#define CMTW_CMWOCR_OCR_MASK(m)                           (0xffffffff << CMTW_CMWOCR_OCR_SHIFT)
#define CMTW_CMWOCR_OCR(m,val)                            (((val) << CMTW_CMWOCR_OCR_SHIFT) & CMTW_CMWOCR_OCR_MASK(m))

/* CMTW CMWCNT Register Bit Definitions ******************************/

#define CMTW_CMWCNT_CNT_SHIFT                   (0)      /* Bits 0-31: Cnt */
#define CMTW_CMWCNT_CNT_MASK                    (0xffffffff << CMTW_CMWCNT_CNT_SHIFT)

/* CMTW CMWCOR Register Bit Definitions ******************************/

#define CMTW_CMWCOR_COR_SHIFT                   (0)      /* Bits 0-31: Cor */
#define CMTW_CMWCOR_COR_MASK                    (0xffffffff << CMTW_CMWCOR_COR_SHIFT)

/* CMTW CMWCR Register Bit Definitions *******************************/

#define CMTW_CMWCR_CKS_SHIFT                    (0)      /* Bits 0-1: Cks */
#define CMTW_CMWCR_CKS_MASK                     (0x3 << CMTW_CMWCR_CKS_SHIFT)

#define CMTW_CMWCR_CMWIE                        (1 << 3)  /* Cmwie */

#define CMTW_CMWCR_IC0IE                        (1 << 4)  /* Ic0Ie */

#define CMTW_CMWCR_IC1IE                        (1 << 5)  /* Ic1Ie */

#define CMTW_CMWCR_OC0IE                        (1 << 6)  /* Oc0Ie */

#define CMTW_CMWCR_OC1IE                        (1 << 7)  /* Oc1Ie */

#define CMTW_CMWCR_CMS                          (1 << 9)  /* Cms */

#define CMTW_CMWCR_CCLR_SHIFT                   (13)      /* Bits 13-15: Cclr */
#define CMTW_CMWCR_CCLR_MASK                    (0x7 << CMTW_CMWCR_CCLR_SHIFT)

/* CMTW CMWIOR Register Bit Definitions ******************************/

#define CMTW_CMWIOR_IC0_SHIFT                   (0)      /* Bits 0-1: Ic0 */
#define CMTW_CMWIOR_IC0_MASK                    (0x3 << CMTW_CMWIOR_IC0_SHIFT)

#define CMTW_CMWIOR_IC1_SHIFT                   (2)      /* Bits 2-3: Ic1 */
#define CMTW_CMWIOR_IC1_MASK                    (0x3 << CMTW_CMWIOR_IC1_SHIFT)

#define CMTW_CMWIOR_IC0E                        (1 << 4)  /* Ic0E */

#define CMTW_CMWIOR_IC1E                        (1 << 5)  /* Ic1E */

#define CMTW_CMWIOR_OC0_SHIFT                   (8)      /* Bits 8-9: Oc0 */
#define CMTW_CMWIOR_OC0_MASK                    (0x3 << CMTW_CMWIOR_OC0_SHIFT)

#define CMTW_CMWIOR_OC1_SHIFT                   (10)      /* Bits 10-11: Oc1 */
#define CMTW_CMWIOR_OC1_MASK                    (0x3 << CMTW_CMWIOR_OC1_SHIFT)

#define CMTW_CMWIOR_OC0E                        (1 << 12)  /* Oc0E */

#define CMTW_CMWIOR_OC1E                        (1 << 13)  /* Oc1E */

#define CMTW_CMWIOR_CMWE                        (1 << 15)  /* Cmwe */

/* CMTW CMWSTR Register Bit Definitions ******************************/

#define CMTW_CMWSTR_STR                         (1 << 0)  /* Str */

/* CMTW Channel definitions */
#define RZV_CMTW_CHANNEL_0         0
#define RZV_CMTW_CHANNEL_1         1
#define RZV_CMTW_CHANNEL_2         2
#define RZV_CMTW_CHANNEL_3         3
#define RZV_CMTW_CHANNEL_4         4
#define RZV_CMTW_CHANNEL_5         5
#define RZV_CMTW_CHANNEL_6         6
#define RZV_CMTW_CHANNEL_7         7

/* Maximum number of CMTW channels */
#define RZV_CMTW_MAX_CHANNELS      8

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_CMTW_H */

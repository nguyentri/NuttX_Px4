/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_dmac.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_DMAC_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_DMAC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DMAC Base Addresses ***************************************************/

#ifndef RZV_DMAC0_BASE
#  define RZV_DMAC0_BASE              0x11400000
#endif
#ifndef RZV_DMAC1_BASE
#  define RZV_DMAC1_BASE              0x14830000
#endif
#ifndef RZV_DMAC2_BASE
#  define RZV_DMAC2_BASE              0x14840000
#endif
#ifndef RZV_DMAC3_BASE
#  define RZV_DMAC3_BASE              0x12000000
#endif
#ifndef RZV_DMAC4_BASE
#  define RZV_DMAC4_BASE              0x12010000
#endif

/* DMAC Register Offsets **************************************************/

#define RZV_DMAC_CHSTAT_OFFSET                           0x0000  /* Channel Status Register */
#define RZV_DMAC_CHCTRL_OFFSET                           0x0004  /* Channel Control Register */
#define RZV_DMAC_CHCFG_OFFSET                            0x0008  /* Channel Configuration Register */
#define RZV_DMAC_CHITVL_OFFSET                           0x000C  /* Channel Interval Register */
#define RZV_DMAC_CHEXT_OFFSET                            0x0010  /* Channel Extension Register */
#define RZV_DMAC_DCTRL_OFFSET                            0x0114  /* DCTRL */
#define RZV_DMAC_DSTAT_EN_OFFSET                         0x0124  /* DSTAT_EN */
#define RZV_DMAC_DSTAT_ER_OFFSET                         0x0128  /* DSTAT_ER */
#define RZV_DMAC_DSTAT_END_OFFSET                        0x012C  /* DSTAT_END */
#define RZV_DMAC_DST_TC_OFFSET                           0x0130  /* DST_TC */
#define RZV_DMAC_DSTAT_SUS_OFFSET                        0x0134  /* DSTAT_SUS */

/* DMAC Register Addresses *************************************************/

#define RZV_DMAC_CHSTAT(ch)                          (RZV_DMAC##ch##_BASE + RZV_DMAC_CHSTAT_OFFSET)
#define RZV_DMAC_CHCTRL(ch)                          (RZV_DMAC##ch##_BASE + RZV_DMAC_CHCTRL_OFFSET)
#define RZV_DMAC_CHCFG(ch)                           (RZV_DMAC##ch##_BASE + RZV_DMAC_CHCFG_OFFSET)
#define RZV_DMAC_CHITVL(ch)                          (RZV_DMAC##ch##_BASE + RZV_DMAC_CHITVL_OFFSET)
#define RZV_DMAC_CHEXT(ch)                           (RZV_DMAC##ch##_BASE + RZV_DMAC_CHEXT_OFFSET)
#define RZV_DMAC_DCTRL(ch)                           (RZV_DMAC##ch##_BASE + RZV_DMAC_DCTRL_OFFSET)
#define RZV_DMAC_DSTAT_EN(ch)                        (RZV_DMAC##ch##_BASE + RZV_DMAC_DSTAT_EN_OFFSET)
#define RZV_DMAC_DSTAT_ER(ch)                        (RZV_DMAC##ch##_BASE + RZV_DMAC_DSTAT_ER_OFFSET)
#define RZV_DMAC_DSTAT_END(ch)                       (RZV_DMAC##ch##_BASE + RZV_DMAC_DSTAT_END_OFFSET)
#define RZV_DMAC_DST_TC(ch)                          (RZV_DMAC##ch##_BASE + RZV_DMAC_DST_TC_OFFSET)
#define RZV_DMAC_DSTAT_SUS(ch)                       (RZV_DMAC##ch##_BASE + RZV_DMAC_DSTAT_SUS_OFFSET)

/* DMAC B0_GRP_DST_EN Register Bit Definitions ***********************/

/* EN fields (parameterized for indices 0-7) */
#define DMAC_B0_GRP_DST_EN_EN(n)                          (1u << (0 + ((unsigned)(n) * 1)))  /* En0 */

/* DMAC B0_GRP_DST_END Register Bit Definitions **********************/

/* END fields (parameterized for indices 0-7) */
#define DMAC_B0_GRP_DST_END_END(n)                        (1u << (0 + ((unsigned)(n) * 1)))  /* End0 */

/* DMAC B0_GRP_DST_ER Register Bit Definitions ***********************/

/* ER fields (parameterized for indices 0-7) */
#define DMAC_B0_GRP_DST_ER_ER(n)                          (1u << (0 + ((unsigned)(n) * 1)))  /* Er0 */

/* DMAC B0_GRP_DST_SUS Register Bit Definitions **********************/

/* SUS fields (parameterized for indices 0-7) */
#define DMAC_B0_GRP_DST_SUS_SUS(n)                        (1u << (0 + ((unsigned)(n) * 1)))  /* Sus0 */

/* DMAC CHCFG Register Bit Definitions *******************************/

#define DMAC_CHCFG_SEL_SHIFT                    (0)      /* Bits 0-2: Sel */
#define DMAC_CHCFG_SEL_MASK                     (0x7 << DMAC_CHCFG_SEL_SHIFT)

#define DMAC_CHCFG_REQD                         (1 << 3)  /* Reqd */

#define DMAC_CHCFG_LOEN                         (1 << 4)  /* Loen */

#define DMAC_CHCFG_HIEN                         (1 << 5)  /* Hien */

#define DMAC_CHCFG_LVL                          (1 << 6)  /* Lvl */

#define DMAC_CHCFG_AM_SHIFT                     (8)      /* Bits 8-10: Am */
#define DMAC_CHCFG_AM_MASK                      (0x7 << DMAC_CHCFG_AM_SHIFT)

#define DMAC_CHCFG_SDS_SHIFT                    (12)      /* Bits 12-15: Sds */
#define DMAC_CHCFG_SDS_MASK                     (0xf << DMAC_CHCFG_SDS_SHIFT)

#define DMAC_CHCFG_DDS_SHIFT                    (16)      /* Bits 16-19: Dds */
#define DMAC_CHCFG_DDS_MASK                     (0xf << DMAC_CHCFG_DDS_SHIFT)

#define DMAC_CHCFG_SAD                          (1 << 20)  /* Sad */

#define DMAC_CHCFG_DAD                          (1 << 21)  /* Dad */

#define DMAC_CHCFG_TM                           (1 << 22)  /* Tm */

#define DMAC_CHCFG_DEM                          (1 << 24)  /* Dem */

#define DMAC_CHCFG_TCM                          (1 << 25)  /* Tcm */

#define DMAC_CHCFG_SBE                          (1 << 27)  /* Sbe */

#define DMAC_CHCFG_RSEL                         (1 << 28)  /* Rsel */

#define DMAC_CHCFG_RSW                          (1 << 29)  /* Rsw */

#define DMAC_CHCFG_REN                          (1 << 30)  /* Ren */

#define DMAC_CHCFG_DMS                          (1 << 31)  /* Dms */

/* DMAC CHCTRL Register Bit Definitions ******************************/

#define DMAC_CHCTRL_SETEN                       (1 << 0)  /* Seten */

#define DMAC_CHCTRL_CLREN                       (1 << 1)  /* Clren */

#define DMAC_CHCTRL_STG                         (1 << 2)  /* Stg */

#define DMAC_CHCTRL_SWRST                       (1 << 3)  /* Swrst */

#define DMAC_CHCTRL_CLRRQ                       (1 << 4)  /* Clrrq */

#define DMAC_CHCTRL_CLREND                      (1 << 5)  /* Clrend */

#define DMAC_CHCTRL_CLRTC                       (1 << 6)  /* Clrtc */

#define DMAC_CHCTRL_SETSUS                      (1 << 8)  /* Setsus */

#define DMAC_CHCTRL_CLRSUS                      (1 << 9)  /* Clrsus */

#define DMAC_CHCTRL_SETINTMSK                   (1 << 16)  /* Setintmsk */

#define DMAC_CHCTRL_CLRINTMSK                   (1 << 17)  /* Clrintmsk */

/* DMAC CHEXT Register Bit Definitions *******************************/

#define DMAC_CHEXT_SPR_SHIFT                    (0)      /* Bits 0-2: Spr */
#define DMAC_CHEXT_SPR_MASK                     (0x7 << DMAC_CHEXT_SPR_SHIFT)

#define DMAC_CHEXT_SCA_SHIFT                    (4)      /* Bits 4-7: Sca */
#define DMAC_CHEXT_SCA_MASK                     (0xf << DMAC_CHEXT_SCA_SHIFT)

#define DMAC_CHEXT_DPR_SHIFT                    (8)      /* Bits 8-10: Dpr */
#define DMAC_CHEXT_DPR_MASK                     (0x7 << DMAC_CHEXT_DPR_SHIFT)

#define DMAC_CHEXT_DCA_SHIFT                    (12)      /* Bits 12-15: Dca */
#define DMAC_CHEXT_DCA_MASK                     (0xf << DMAC_CHEXT_DCA_SHIFT)

/* DMAC CHITVL Register Bit Definitions ******************************/

#define DMAC_CHITVL_ITVL_SHIFT                  (0)      /* Bits 0-15: Itvl */
#define DMAC_CHITVL_ITVL_MASK                   (0xffff << DMAC_CHITVL_ITVL_SHIFT)

/* DMAC CHSTAT Register Bit Definitions ******************************/

#define DMAC_CHSTAT_EN                          (1 << 0)  /* En */

#define DMAC_CHSTAT_RQST                        (1 << 1)  /* Rqst */

#define DMAC_CHSTAT_TACT                        (1 << 2)  /* Tact */

#define DMAC_CHSTAT_SUS                         (1 << 3)  /* Sus */

#define DMAC_CHSTAT_ER                          (1 << 4)  /* Er */

#define DMAC_CHSTAT_END                         (1 << 5)  /* End */

#define DMAC_CHSTAT_TC                          (1 << 6)  /* Tc */

#define DMAC_CHSTAT_SR                          (1 << 7)  /* Sr */

#define DMAC_CHSTAT_DL                          (1 << 8)  /* Dl */

#define DMAC_CHSTAT_DW                          (1 << 9)  /* Dw */

#define DMAC_CHSTAT_DER                         (1 << 10)  /* Der */

#define DMAC_CHSTAT_MODE                        (1 << 11)  /* Mode */

#define DMAC_CHSTAT_INTMSK                      (1 << 16)  /* Intmsk */

/* DMAC DCTRL Register Bit Definitions *******************************/

#define DMAC_DCTRL_PR                           (1 << 0)  /* Pr */

#define DMAC_DCTRL_LVINT                        (1 << 1)  /* Lvint */

#define DMAC_DCTRL_LDPR_SHIFT                   (16)      /* Bits 16-18: Ldpr */
#define DMAC_DCTRL_LDPR_MASK                    (0x7 << DMAC_DCTRL_LDPR_SHIFT)

#define DMAC_DCTRL_LDCA_SHIFT                   (20)      /* Bits 20-23: Ldca */
#define DMAC_DCTRL_LDCA_MASK                    (0xf << DMAC_DCTRL_LDCA_SHIFT)

#define DMAC_DCTRL_LWPR_SHIFT                   (24)      /* Bits 24-26: Lwpr */
#define DMAC_DCTRL_LWPR_MASK                    (0x7 << DMAC_DCTRL_LWPR_SHIFT)

#define DMAC_DCTRL_LWCA_SHIFT                   (28)      /* Bits 28-31: Lwca */
#define DMAC_DCTRL_LWCA_MASK                    (0xf << DMAC_DCTRL_LWCA_SHIFT)

/* DMAC DST_TC Register Bit Definitions ******************************/

/* TC fields (parameterized for indices 0-7) */
#define DMAC_DST_TC_TC(n)                                 (1u << (0 + ((unsigned)(n) * 1)))  /* Tc0 */

/* DMAC Channel definitions */
#define RZV_DMAC_CHANNEL_0         0
#define RZV_DMAC_CHANNEL_1         1
#define RZV_DMAC_CHANNEL_2         2
#define RZV_DMAC_CHANNEL_3         3
#define RZV_DMAC_CHANNEL_4         4

/* Maximum number of DMAC channels */
#define RZV_DMAC_MAX_CHANNELS      5

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_DMAC_H */

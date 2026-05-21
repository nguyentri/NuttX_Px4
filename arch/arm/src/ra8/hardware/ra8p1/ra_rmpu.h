/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_rmpu.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_RMPU_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_RMPU_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* RMPU Base Address */
#ifndef R_RMPU_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_RMPU_BASE           0x40000000
#else
#define R_RMPU_BASE           0x50000000
#endif
#endif

/* RMPU Register Offsets */

#define R_RMPU_MMPUOAD_OFFSET                     0x00000000  /* MMPU Operation After Detection Register */
#define R_RMPU_MMPUOADPT_OFFSET                   0x00000004  /* MMPU Operation After Detection Protect Register */
/* MMPUENDMAC%s Registers (0-1) */
#define R_RMPU_MMPUENDMAC_OFFSET(m)               (0x00000100 + ((m) * 0x00000200))  /* MMPU Enable Register for DMAC */
/* MMPUENPTDMAC%s Registers (0-1) */
#define R_RMPU_MMPUENPTDMAC_OFFSET(m)             (0x00000104 + ((m) * 0x00000200))  /* MMPU Enable Protect Register for DMAC %s */
/* MMPURPTDMAC_SEC%s Registers (0-1) */
#define R_RMPU_MMPURPTDMAC_SEC_OFFSET(m)          (0x0000010c + ((m) * 0x00000200))  /* MMPU Regions Protect Register for DMAC Secure %s */
/* MMPUACDMAC0%s Registers (00-07) */
#define R_RMPU_MMPUACDMAC0_OFFSET(m)              (0x00000200 + ((m) * 0x00000010))  /* MMPU Access Control Register for DMAC */
/* MMPUSDMAC0%s Registers (00-07) */
#define R_RMPU_MMPUSDMAC0_OFFSET(m)               (0x00000204 + ((m) * 0x00000010))  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
/* MMPUEDMAC0%s Registers (00-07) */
#define R_RMPU_MMPUEDMAC0_OFFSET(m)               (0x00000208 + ((m) * 0x00000010))  /* MMPU End Address Register for DMAC (n = 00 to 07) */
/* MMPUACDMAC1%s Registers (00-07) */
#define R_RMPU_MMPUACDMAC1_OFFSET(m)              (0x00000400 + ((m) * 0x00000010))  /* MMPU Access Control Register for DMAC */
/* MMPUSDMAC1%s Registers (00-07) */
#define R_RMPU_MMPUSDMAC1_OFFSET(m)               (0x00000404 + ((m) * 0x00000010))  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
/* MMPUEDMAC1%s Registers (00-07) */
#define R_RMPU_MMPUEDMAC1_OFFSET(m)               (0x00000408 + ((m) * 0x00000010))  /* MMPU End Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUENEDMAC_OFFSET                 0x00000500  /* MMPU Enable Register for EDMAC */
#define R_RMPU_MMPUENPTEDMAC_OFFSET               0x00000504  /* MMPU Enable Protect Register for EDMAC */
#define R_RMPU_MMPURPTEDMAC_OFFSET                0x00000508  /* MMPU Regions Protect Register for EDMAC */
/* MMPUACEDMAC%s Registers (0-4) */
#define R_RMPU_MMPUACEDMAC_OFFSET(m)              (0x00000600 + ((m) * 0x00000010))  /* MMPU Access Control Register for EDMAC */
/* MMPUSEDMAC%s Registers (0-4) */
#define R_RMPU_MMPUSEDMAC_OFFSET(m)               (0x00000604 + ((m) * 0x00000010))  /* MMPU Start Address Register for EDMAC (n = 0 to 4) */
/* MMPUEEDMAC%s Registers (0-4) */
#define R_RMPU_MMPUEEDMAC_OFFSET(m)               (0x00000608 + ((m) * 0x00000010))  /* MMPU End Address Register for EDMAC */
#define R_RMPU_MMPUENGLCDC_OFFSET                 0x00000700  /* MMPU Enable Register for GLCDC */
#define R_RMPU_MMPUENPTGLCDC_OFFSET               0x00000704  /* MMPU Enable Protect Register for GLCDC */
#define R_RMPU_MMPURPTGLCDC_OFFSET                0x00000708  /* MMPU Regions Protect Register for GLCDC */
/* MMPUACGLCDC%s Registers (0-1) */
#define R_RMPU_MMPUACGLCDC_OFFSET(m)              (0x00000800 + ((m) * 0x00000010))  /* MMPU Access Control Register for GLCDC (n = 0, 1) */
/* MMPUSGLCDC%s Registers (0-1) */
#define R_RMPU_MMPUSGLCDC_OFFSET(m)               (0x00000804 + ((m) * 0x00000010))  /* MMPU Start Address Register for GLCDC (n = 0, 1) */
/* MMPUEGLCDC%s Registers (0-1) */
#define R_RMPU_MMPUEGLCDC_OFFSET(m)               (0x00000808 + ((m) * 0x00000010))  /* MMPU End Address Register for GLCDC (n = 0, 1) */
#define R_RMPU_MMPUENDRW_OFFSET                   0x00000900  /* MMPU Enable Register for DRW */
#define R_RMPU_MMPUENPDRW_OFFSET                  0x00000904  /* MMPU Enable Protect Register for DRW */
#define R_RMPU_MMPURPTDRW_OFFSET                  0x00000908  /* MMPU Regions Protect Register for DRW */
/* MMPUACDRW%s Registers (0-2) */
#define R_RMPU_MMPUACDRW_OFFSET(m)                (0x00000a00 + ((m) * 0x00000010))  /* MMPU Access Control Register for DRW (n = 0 to 2) */
/* MMPUSDRW%s Registers (0-2) */
#define R_RMPU_MMPUSDRW_OFFSET(m)                 (0x00000a04 + ((m) * 0x00000010))  /* MMPU Start Address Register for DRW (n = 0 to 2) */
/* MMPUEDRW%s Registers (0-2) */
#define R_RMPU_MMPUEDRW_OFFSET(m)                 (0x00000a08 + ((m) * 0x00000010))  /* MMPU End Address Register for DRW (n = 0 to 2) */
#define R_RMPU_MMPUENMIPID_OFFSET                 0x00000b00  /* MMPU Enable Register for MIPI-DSI */
#define R_RMPU_MMPUENPTMIPID_OFFSET               0x00000b04  /* MMPU Enable Protect Register for MIPI-DSI */
#define R_RMPU_MMPURPTMIPID_OFFSET                0x00000b08  /* MMPU Regions Protect Register for MIPI-DSI */
#define R_RMPU_MMPUACMIPID_OFFSET                 0x00000c00  /* MMPU Access Control Register for MIPI-DSI */
#define R_RMPU_MMPUSMIPID_OFFSET                  0x00000c04  /* MMPU Start Address Register for MIPI-DSI */
#define R_RMPU_MMPUEMIPID_OFFSET                  0x00000c08  /* MMPU End Address Register for MIPI-DSI */
#define R_RMPU_MMPUENCEU_OFFSET                   0x00000d00  /* MMPU Enable Register for CEU */
#define R_RMPU_MMPUENPTCEU_OFFSET                 0x00000d04  /* MMPU Enable Protect Register for CEU */
#define R_RMPU_MMPURPTCEU_OFFSET                  0x00000d08  /* MMPU Regions Protect Register for CEU */
/* MMPUACCEU%s Registers (0-1) */
#define R_RMPU_MMPUACCEU_OFFSET(m)                (0x00000e00 + ((m) * 0x00000010))  /* MMPU Access Control Register for CEU (n = 0, 1) */
/* MMPUSCEU%s Registers (0-1) */
#define R_RMPU_MMPUSCEU_OFFSET(m)                 (0x00000e04 + ((m) * 0x00000010))  /* MMPU Start Address Register for CEU (n = 0, 1) */
/* MMPUECEU%s Registers (0-1) */
#define R_RMPU_MMPUECEU_OFFSET(m)                 (0x00000e08 + ((m) * 0x00000010))  /* MMPU End Address Register for CEU (n = 0, 1) */
#define R_RMPU_MMPUENMIPIC_OFFSET                 0x00000f00  /* MMPU Enable Register for MIPI-CSI by VIN */
#define R_RMPU_MMPUENPTMIPIC_OFFSET               0x00000f04  /* MMPU Enable Protect Register for MIPI-CSI by VIN */
#define R_RMPU_MMPURPTMIPIC_OFFSET                0x00000f08  /* MMPU Regions Protect Register for MIPI-CSI by VIN */
/* MMPUACMIPIC%s Registers (0-2) */
#define R_RMPU_MMPUACMIPIC_OFFSET(m)              (0x00001000 + ((m) * 0x00000010))  /* MMPU Access Control Register for MIPI-CSI via VIN (n = 0 to 2) */
/* MMPUSMIPIC%s Registers (0-2) */
#define R_RMPU_MMPUSMIPIC_OFFSET(m)               (0x00001004 + ((m) * 0x00000010))  /* MMPU Start Address Register for MIPI-CSI via VIN (n = 0 to 2) */
/* MMPUEMIPIC%s Registers (0-2) */
#define R_RMPU_MMPUEMIPIC_OFFSET(m)               (0x00001008 + ((m) * 0x00000010))  /* MMPU End Address Register for MIPI-CSI via VIN (n = 0 to 2) */
#define R_RMPU_MMPUENNPU_OFFSET                   0x00001100  /* MMPU Enable Register for NPU */
#define R_RMPU_MMPUENPTNPU_OFFSET                 0x00001104  /* MMPU Enable Protect Register for NPU */
#define R_RMPU_MMPURPTNPU_OFFSET                  0x00001108  /* MMPU Regions Protect Register for NPU */
/* MMPUACNPU%s Registers (0-4) */
#define R_RMPU_MMPUACNPU_OFFSET(m)                (0x00001200 + ((m) * 0x00000010))  /* MMPU Access Control Register for NPU (n = 0 to 4) */
/* MMPUSNPU%s Registers (0-4) */
#define R_RMPU_MMPUSNPU_OFFSET(m)                 (0x00001204 + ((m) * 0x00000010))  /* MMPU Start Address Register for NPU (n = 0 to 4) */
/* MMPUENPU%s Registers (0-4) */
#define R_RMPU_MMPUENPU_OFFSET(m)                 (0x00001208 + ((m) * 0x00000010))  /* MMPU End Address Register for NPU (n = 0 to 4) */

/* RMPU Register Addresses */

#define R_RMPU_MMPUOAD                            (R_RMPU_BASE + R_RMPU_MMPUOAD_OFFSET)
#define R_RMPU_MMPUOADPT                          (R_RMPU_BASE + R_RMPU_MMPUOADPT_OFFSET)
#define R_RMPU_MMPUENDMAC(m)                      (R_RMPU_BASE + R_RMPU_MMPUENDMAC_OFFSET(m))
#define R_RMPU_MMPUENPTDMAC(m)                    (R_RMPU_BASE + R_RMPU_MMPUENPTDMAC_OFFSET(m))
#define R_RMPU_MMPURPTDMAC_SEC(m)                 (R_RMPU_BASE + R_RMPU_MMPURPTDMAC_SEC_OFFSET(m))
#define R_RMPU_MMPUACDMAC0(m)                     (R_RMPU_BASE + R_RMPU_MMPUACDMAC0_OFFSET(m))
#define R_RMPU_MMPUSDMAC0(m)                      (R_RMPU_BASE + R_RMPU_MMPUSDMAC0_OFFSET(m))
#define R_RMPU_MMPUEDMAC0(m)                      (R_RMPU_BASE + R_RMPU_MMPUEDMAC0_OFFSET(m))
#define R_RMPU_MMPUACDMAC1(m)                     (R_RMPU_BASE + R_RMPU_MMPUACDMAC1_OFFSET(m))
#define R_RMPU_MMPUSDMAC1(m)                      (R_RMPU_BASE + R_RMPU_MMPUSDMAC1_OFFSET(m))
#define R_RMPU_MMPUEDMAC1(m)                      (R_RMPU_BASE + R_RMPU_MMPUEDMAC1_OFFSET(m))
#define R_RMPU_MMPUENEDMAC                        (R_RMPU_BASE + R_RMPU_MMPUENEDMAC_OFFSET)
#define R_RMPU_MMPUENPTEDMAC                      (R_RMPU_BASE + R_RMPU_MMPUENPTEDMAC_OFFSET)
#define R_RMPU_MMPURPTEDMAC                       (R_RMPU_BASE + R_RMPU_MMPURPTEDMAC_OFFSET)
#define R_RMPU_MMPUACEDMAC(m)                     (R_RMPU_BASE + R_RMPU_MMPUACEDMAC_OFFSET(m))
#define R_RMPU_MMPUSEDMAC(m)                      (R_RMPU_BASE + R_RMPU_MMPUSEDMAC_OFFSET(m))
#define R_RMPU_MMPUEEDMAC(m)                      (R_RMPU_BASE + R_RMPU_MMPUEEDMAC_OFFSET(m))
#define R_RMPU_MMPUENGLCDC                        (R_RMPU_BASE + R_RMPU_MMPUENGLCDC_OFFSET)
#define R_RMPU_MMPUENPTGLCDC                      (R_RMPU_BASE + R_RMPU_MMPUENPTGLCDC_OFFSET)
#define R_RMPU_MMPURPTGLCDC                       (R_RMPU_BASE + R_RMPU_MMPURPTGLCDC_OFFSET)
#define R_RMPU_MMPUACGLCDC(m)                     (R_RMPU_BASE + R_RMPU_MMPUACGLCDC_OFFSET(m))
#define R_RMPU_MMPUSGLCDC(m)                      (R_RMPU_BASE + R_RMPU_MMPUSGLCDC_OFFSET(m))
#define R_RMPU_MMPUEGLCDC(m)                      (R_RMPU_BASE + R_RMPU_MMPUEGLCDC_OFFSET(m))
#define R_RMPU_MMPUENDRW                          (R_RMPU_BASE + R_RMPU_MMPUENDRW_OFFSET)
#define R_RMPU_MMPUENPDRW                         (R_RMPU_BASE + R_RMPU_MMPUENPDRW_OFFSET)
#define R_RMPU_MMPURPTDRW                         (R_RMPU_BASE + R_RMPU_MMPURPTDRW_OFFSET)
#define R_RMPU_MMPUACDRW(m)                       (R_RMPU_BASE + R_RMPU_MMPUACDRW_OFFSET(m))
#define R_RMPU_MMPUSDRW(m)                        (R_RMPU_BASE + R_RMPU_MMPUSDRW_OFFSET(m))
#define R_RMPU_MMPUEDRW(m)                        (R_RMPU_BASE + R_RMPU_MMPUEDRW_OFFSET(m))
#define R_RMPU_MMPUENMIPID                        (R_RMPU_BASE + R_RMPU_MMPUENMIPID_OFFSET)
#define R_RMPU_MMPUENPTMIPID                      (R_RMPU_BASE + R_RMPU_MMPUENPTMIPID_OFFSET)
#define R_RMPU_MMPURPTMIPID                       (R_RMPU_BASE + R_RMPU_MMPURPTMIPID_OFFSET)
#define R_RMPU_MMPUACMIPID                        (R_RMPU_BASE + R_RMPU_MMPUACMIPID_OFFSET)
#define R_RMPU_MMPUSMIPID                         (R_RMPU_BASE + R_RMPU_MMPUSMIPID_OFFSET)
#define R_RMPU_MMPUEMIPID                         (R_RMPU_BASE + R_RMPU_MMPUEMIPID_OFFSET)
#define R_RMPU_MMPUENCEU                          (R_RMPU_BASE + R_RMPU_MMPUENCEU_OFFSET)
#define R_RMPU_MMPUENPTCEU                        (R_RMPU_BASE + R_RMPU_MMPUENPTCEU_OFFSET)
#define R_RMPU_MMPURPTCEU                         (R_RMPU_BASE + R_RMPU_MMPURPTCEU_OFFSET)
#define R_RMPU_MMPUACCEU(m)                       (R_RMPU_BASE + R_RMPU_MMPUACCEU_OFFSET(m))
#define R_RMPU_MMPUSCEU(m)                        (R_RMPU_BASE + R_RMPU_MMPUSCEU_OFFSET(m))
#define R_RMPU_MMPUECEU(m)                        (R_RMPU_BASE + R_RMPU_MMPUECEU_OFFSET(m))
#define R_RMPU_MMPUENMIPIC                        (R_RMPU_BASE + R_RMPU_MMPUENMIPIC_OFFSET)
#define R_RMPU_MMPUENPTMIPIC                      (R_RMPU_BASE + R_RMPU_MMPUENPTMIPIC_OFFSET)
#define R_RMPU_MMPURPTMIPIC                       (R_RMPU_BASE + R_RMPU_MMPURPTMIPIC_OFFSET)
#define R_RMPU_MMPUACMIPIC(m)                     (R_RMPU_BASE + R_RMPU_MMPUACMIPIC_OFFSET(m))
#define R_RMPU_MMPUSMIPIC(m)                      (R_RMPU_BASE + R_RMPU_MMPUSMIPIC_OFFSET(m))
#define R_RMPU_MMPUEMIPIC(m)                      (R_RMPU_BASE + R_RMPU_MMPUEMIPIC_OFFSET(m))
#define R_RMPU_MMPUENNPU                          (R_RMPU_BASE + R_RMPU_MMPUENNPU_OFFSET)
#define R_RMPU_MMPUENPTNPU                        (R_RMPU_BASE + R_RMPU_MMPUENPTNPU_OFFSET)
#define R_RMPU_MMPURPTNPU                         (R_RMPU_BASE + R_RMPU_MMPURPTNPU_OFFSET)
#define R_RMPU_MMPUACNPU(m)                       (R_RMPU_BASE + R_RMPU_MMPUACNPU_OFFSET(m))
#define R_RMPU_MMPUSNPU(m)                        (R_RMPU_BASE + R_RMPU_MMPUSNPU_OFFSET(m))
#define R_RMPU_MMPUENPU(m)                        (R_RMPU_BASE + R_RMPU_MMPUENPU_OFFSET(m))

/* Register bit definitions */
/* MMPUOAD Register bit definitions */
#define R_RMPU_MMPUOAD_OAD                        (1 << 0)  /* Operation after detection */

#define R_RMPU_MMPUOAD_KEY_SHIFT                  (8)  /* Key Code */
#define R_RMPU_MMPUOAD_KEY_MASK                   0xff00

/* MMPUOADPT Register bit definitions */
#define R_RMPU_MMPUOADPT_PROTECT                  (1 << 0)  /* Protection of register */

#define R_RMPU_MMPUOADPT_KEY_SHIFT                (8)  /* Key Code */
#define R_RMPU_MMPUOADPT_KEY_MASK                 0xff00

/* MMPUENDMAC Register bit definitions */
#define R_RMPU_MMPUENDMAC_ENABLE                  (1 << 0)  /* Bus master MPU of DMAC Enable */

#define R_RMPU_MMPUENDMAC_KEY_SHIFT               (8)  /* Key Code */
#define R_RMPU_MMPUENDMAC_KEY_MASK                0xff00

/* MMPUENPTDMAC Register bit definitions */
#define R_RMPU_MMPUENPTDMAC_PROTECT               (1 << 0)  /* Protection of register */

#define R_RMPU_MMPUENPTDMAC_KEY_SHIFT             (8)  /* Key Code */
#define R_RMPU_MMPUENPTDMAC_KEY_MASK              0xff00

/* MMPURPTDMAC_SEC Register bit definitions */
#define R_RMPU_MMPURPTDMAC_SEC_PROTECT            (1 << 0)  /* Protection of register */

#define R_RMPU_MMPURPTDMAC_SEC_KEY_SHIFT          (8)  /* Key Code */
#define R_RMPU_MMPURPTDMAC_SEC_KEY_MASK           0xff00

/* MMPUACDMAC Register bit definitions */
#define R_RMPU_MMPUACDMAC_ENABLE                  (1 << 0)  /* Region Enable */

#define R_RMPU_MMPUACDMAC_RP                      (1 << 1)  /* Read protection */

#define R_RMPU_MMPUACDMAC_WP                      (1 << 2)  /* Write protection */

#define R_RMPU_MMPUACDMAC_PP                      (1 << 3)  /* Privilege protection */

/* MMPUACDMAC Register bit definitions */
#define R_RMPU_MMPUACDMAC_ENABLE                  (1 << 0)  /* Region Enable */

#define R_RMPU_MMPUACDMAC_RP                      (1 << 1)  /* Read protection */

#define R_RMPU_MMPUACDMAC_WP                      (1 << 2)  /* Write protection */

#define R_RMPU_MMPUACDMAC_PP                      (1 << 3)  /* Privilege protection */

/* MMPUENEDMAC Register bit definitions */
#define R_RMPU_MMPUENEDMAC_ENABLE                 (1 << 0)  /* Bus master MPU of EDMAC Enable */

#define R_RMPU_MMPUENEDMAC_KEY_SHIFT              (8)  /* Key Code */
#define R_RMPU_MMPUENEDMAC_KEY_MASK               0xff00

/* MMPUENPTEDMAC Register bit definitions */
#define R_RMPU_MMPUENPTEDMAC_PROTECT              (1 << 0)  /* Protection of register */

#define R_RMPU_MMPUENPTEDMAC_KEY_SHIFT            (8)  /* Key Code */
#define R_RMPU_MMPUENPTEDMAC_KEY_MASK             0xff00

/* MMPURPTEDMAC Register bit definitions */
#define R_RMPU_MMPURPTEDMAC_PROTECT               (1 << 0)  /* Protection of register */

#define R_RMPU_MMPURPTEDMAC_KEY_SHIFT             (8)  /* Key Code */
#define R_RMPU_MMPURPTEDMAC_KEY_MASK              0xff00

/* MMPUACEDMAC Register bit definitions */
#define R_RMPU_MMPUACEDMAC_ENABLE                 (1 << 0)  /* Region Enable */

#define R_RMPU_MMPUACEDMAC_RP                     (1 << 1)  /* Read protection */

#define R_RMPU_MMPUACEDMAC_WP                     (1 << 2)  /* Write protection */

/* MMPUENGLCDC Register bit definitions */
#define R_RMPU_MMPUENGLCDC_ENABLE                 (1 << 0)  /* Bus master MPU of GLCDC Enable */

#define R_RMPU_MMPUENGLCDC_KEY_SHIFT              (8)  /* Key Code */
#define R_RMPU_MMPUENGLCDC_KEY_MASK               0xff00

/* MMPUENPTGLCDC Register bit definitions */
#define R_RMPU_MMPUENPTGLCDC_PROTECT              (1 << 0)  /* Protection of register */

#define R_RMPU_MMPUENPTGLCDC_KEY_SHIFT            (8)  /* Key Code */
#define R_RMPU_MMPUENPTGLCDC_KEY_MASK             0xff00

/* MMPURPTGLCDC Register bit definitions */
#define R_RMPU_MMPURPTGLCDC_PROTECT               (1 << 0)  /* Protection of register */

#define R_RMPU_MMPURPTGLCDC_KEY_SHIFT             (8)  /* Key Code */
#define R_RMPU_MMPURPTGLCDC_KEY_MASK              0xff00

/* MMPUACGLCDC Register bit definitions */
#define R_RMPU_MMPUACGLCDC_ENABLE                 (1 << 0)  /* Region Enable */

#define R_RMPU_MMPUACGLCDC_RP                     (1 << 1)  /* Read protection */

#define R_RMPU_MMPUACGLCDC_WP                     (1 << 2)  /* Write protection */

/* MMPUENDRW Register bit definitions */
#define R_RMPU_MMPUENDRW_ENABLE                   (1 << 0)  /* Bus master MPU of DRW Enable */

#define R_RMPU_MMPUENDRW_KEY_SHIFT                (8)  /* Key Code */
#define R_RMPU_MMPUENDRW_KEY_MASK                 0xff00

/* MMPUENPDRW Register bit definitions */
#define R_RMPU_MMPUENPDRW_PROTECT                 (1 << 0)  /* Protection of register */

#define R_RMPU_MMPUENPDRW_KEY_SHIFT               (8)  /* Key Code */
#define R_RMPU_MMPUENPDRW_KEY_MASK                0xff00

/* MMPURPTDRW Register bit definitions */
#define R_RMPU_MMPURPTDRW_PROTECT                 (1 << 0)  /* Protection of register */

#define R_RMPU_MMPURPTDRW_KEY_SHIFT               (8)  /* Key Code */
#define R_RMPU_MMPURPTDRW_KEY_MASK                0xff00

/* MMPUACDRW Register bit definitions */
#define R_RMPU_MMPUACDRW_ENABLE                   (1 << 0)  /* Region Enable */

#define R_RMPU_MMPUACDRW_RP                       (1 << 1)  /* Read protection */

#define R_RMPU_MMPUACDRW_WP                       (1 << 2)  /* Write protection */

/* MMPUENMIPID Register bit definitions */
#define R_RMPU_MMPUENMIPID_ENABLE                 (1 << 0)  /* Bus master MPU of MIPI-DSI Enable */

#define R_RMPU_MMPUENMIPID_KEY_SHIFT              (8)  /* Key Code */
#define R_RMPU_MMPUENMIPID_KEY_MASK               0xff00

/* MMPUENPTMIPID Register bit definitions */
#define R_RMPU_MMPUENPTMIPID_PROTECT              (1 << 0)  /* Protection of register */

#define R_RMPU_MMPUENPTMIPID_KEY_SHIFT            (8)  /* Key Code */
#define R_RMPU_MMPUENPTMIPID_KEY_MASK             0xff00

/* MMPURPTMIPID Register bit definitions */
#define R_RMPU_MMPURPTMIPID_PROTECT               (1 << 0)  /* Protection of register */

#define R_RMPU_MMPURPTMIPID_KEY_SHIFT             (8)  /* Key Code */
#define R_RMPU_MMPURPTMIPID_KEY_MASK              0xff00

/* MMPUACMIPID Register bit definitions */
#define R_RMPU_MMPUACMIPID_ENABLE                 (1 << 0)  /* Region Enable */

#define R_RMPU_MMPUACMIPID_RP                     (1 << 1)  /* Read protection */

#define R_RMPU_MMPUACMIPID_WP                     (1 << 2)  /* Write protection */

/* MMPUENCEU Register bit definitions */
#define R_RMPU_MMPUENCEU_ENABLE                   (1 << 0)  /* Bus master MPU of CEU Enable */

#define R_RMPU_MMPUENCEU_KEY_SHIFT                (8)  /* Key Code */
#define R_RMPU_MMPUENCEU_KEY_MASK                 0xff00

/* MMPUENPTCEU Register bit definitions */
#define R_RMPU_MMPUENPTCEU_PROTECT                (1 << 0)  /* Protection of register */

#define R_RMPU_MMPUENPTCEU_KEY_SHIFT              (8)  /* Key Code */
#define R_RMPU_MMPUENPTCEU_KEY_MASK               0xff00

/* MMPURPTCEU Register bit definitions */
#define R_RMPU_MMPURPTCEU_PROTECT                 (1 << 0)  /* Protection of register */

#define R_RMPU_MMPURPTCEU_KEY_SHIFT               (8)  /* Key Code */
#define R_RMPU_MMPURPTCEU_KEY_MASK                0xff00

/* MMPUACCEU Register bit definitions */
#define R_RMPU_MMPUACCEU_ENABLE                   (1 << 0)  /* Region Enable */

#define R_RMPU_MMPUACCEU_RP                       (1 << 1)  /* Read protection */

#define R_RMPU_MMPUACCEU_WP                       (1 << 2)  /* Write protection */

/* MMPUENMIPIC Register bit definitions */
#define R_RMPU_MMPUENMIPIC_ENABLE                 (1 << 0)  /* Bus master MPU of MIPI-CSI Enable */

#define R_RMPU_MMPUENMIPIC_KEY_SHIFT              (8)  /* Key Code */
#define R_RMPU_MMPUENMIPIC_KEY_MASK               0xff00

/* MMPUENPTMIPIC Register bit definitions */
#define R_RMPU_MMPUENPTMIPIC_PROTECT              (1 << 0)  /* Protection of register */

#define R_RMPU_MMPUENPTMIPIC_KEY_SHIFT            (8)  /* Key Code */
#define R_RMPU_MMPUENPTMIPIC_KEY_MASK             0xff00

/* MMPURPTMIPIC Register bit definitions */
#define R_RMPU_MMPURPTMIPIC_PROTECT               (1 << 0)  /* Protection of register */

#define R_RMPU_MMPURPTMIPIC_KEY_SHIFT             (8)  /* Key Code */
#define R_RMPU_MMPURPTMIPIC_KEY_MASK              0xff00

/* MMPUACMIPIC Register bit definitions */
#define R_RMPU_MMPUACMIPIC_ENABLE                 (1 << 0)  /* Region Enable */

#define R_RMPU_MMPUACMIPIC_RP                     (1 << 1)  /* Read protection */

#define R_RMPU_MMPUACMIPIC_WP                     (1 << 2)  /* Write protection */

/* MMPUENNPU Register bit definitions */
#define R_RMPU_MMPUENNPU_ENABLE                   (1 << 0)  /* Bus master MPU of NPU Enable */

#define R_RMPU_MMPUENNPU_KEY_SHIFT                (8)  /* Key Code */
#define R_RMPU_MMPUENNPU_KEY_MASK                 0xff00

/* MMPUENPTNPU Register bit definitions */
#define R_RMPU_MMPUENPTNPU_PROTECT                (1 << 0)  /* Protection of register */

#define R_RMPU_MMPUENPTNPU_KEY_SHIFT              (8)  /* Key Code */
#define R_RMPU_MMPUENPTNPU_KEY_MASK               0xff00

/* MMPURPTNPU Register bit definitions */
#define R_RMPU_MMPURPTNPU_PROTECT                 (1 << 0)  /* Protection of register */

#define R_RMPU_MMPURPTNPU_KEY_SHIFT               (8)  /* Key Code */
#define R_RMPU_MMPURPTNPU_KEY_MASK                0xff00

/* MMPUACNPU Register bit definitions */
#define R_RMPU_MMPUACNPU_ENABLE                   (1 << 0)  /* Region Enable */

#define R_RMPU_MMPUACNPU_RP                       (1 << 1)  /* Read protection */

#define R_RMPU_MMPUACNPU_WP                       (1 << 2)  /* Write protection */


/* Maximum number of channels */

#define RMPU_MAX_CHANNELS    8

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_RMPU_H */

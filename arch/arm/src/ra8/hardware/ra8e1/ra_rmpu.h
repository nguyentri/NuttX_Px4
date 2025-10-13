/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8e1/ra_rmpu.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_RMPU_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_RMPU_H

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
#define R_RMPU_MMPUENDMAC_OFFSET                  0x00000100  /* MMPU Enable Register for DMAC */
#define R_RMPU_MMPUENPTDMAC_OFFSET                0x00000104  /* MMPU Enable Protect Register for DMAC */
#define R_RMPU_MMPURPTDMAC_SEC_OFFSET             0x0000010c  /* MMPU Regions Protect register for DMAC Secure */
/* MMPUACDMAC%s Registers (0-7) */
#define R_RMPU_MMPUACDMAC_OFFSET(m)               (0x00000200 + ((m) * 0x00000010))  /* MMPU Access Control Register for DMAC (n = 0 to 7) */
/* MMPUSDMAC%s Registers (0-7) */
#define R_RMPU_MMPUSDMAC_OFFSET(m)                (0x00000204 + ((m) * 0x00000010))  /* MMPU Start Address Register for DMAC (n = 0 to 7) */
/* MMPUEDMAC%s Registers (0-7) */
#define R_RMPU_MMPUEDMAC_OFFSET(m)                (0x00000208 + ((m) * 0x00000010))  /* MMPU End Address Register for DMAC (n = 0 to 7) */
#define R_RMPU_MMPUENEDMAC_OFFSET                 0x00000500  /* MMPU Enable Register for EDMAC */
#define R_RMPU_MMPUENPTEDMAC_OFFSET               0x00000504  /* MMPU Enable Protect Register for EDMAC */
#define R_RMPU_MMPURPTEDMAC_OFFSET                0x00000508  /* MMPU Regions Protect Register for EDMAC */
/* MMPUACEDMAC%s Registers (0-3) */
#define R_RMPU_MMPUACEDMAC_OFFSET(m)              (0x00000600 + ((m) * 0x00000010))  /* MMPU Access Control Register for EDMAC (n = 0 to 3) */
/* MMPUSEDMAC%s Registers (0-3) */
#define R_RMPU_MMPUSEDMAC_OFFSET(m)               (0x00000604 + ((m) * 0x00000010))  /* MMPU Start Address Register for EDMAC (n = 0 to 3) */
/* MMPUEEDMAC%s Registers (0-3) */
#define R_RMPU_MMPUEEDMAC_OFFSET(m)               (0x00000608 + ((m) * 0x00000010))  /* MMPU End Address Register for EDMAC (n = 0 to 3) */
#define R_RMPU_MMPUENCEU_OFFSET                   0x00000d00  /* MMPU Enable Register for CEU */
#define R_RMPU_MMPUENPTCEU_OFFSET                 0x00000d04  /* MMPU Enable Protect Register for CEU */
#define R_RMPU_MMPURPTCEU_OFFSET                  0x00000d08  /* MMPU Regions Protect Register for CEU */
/* MMPUACCEU%s Registers (0-1) */
#define R_RMPU_MMPUACCEU_OFFSET(m)                (0x00000e00 + ((m) * 0x00000010))  /* MMPU Access Control Register for CEU (n = 0, 1) */
/* MMPUSCEU%s Registers (0-1) */
#define R_RMPU_MMPUSCEU_OFFSET(m)                 (0x00000e04 + ((m) * 0x00000010))  /* MMPU Start Address Register for CEU (n = 0 to 1) */
/* MMPUECEU%s Registers (0-1) */
#define R_RMPU_MMPUECEU_OFFSET(m)                 (0x00000e08 + ((m) * 0x00000010))  /* MMPU End Address Register for CEU (n = 0 to 1) */

/* RMPU Register Addresses */

#define R_RMPU_MMPUOAD                            (R_RMPU_BASE + R_RMPU_MMPUOAD_OFFSET)
#define R_RMPU_MMPUOADPT                          (R_RMPU_BASE + R_RMPU_MMPUOADPT_OFFSET)
#define R_RMPU_MMPUENDMAC                         (R_RMPU_BASE + R_RMPU_MMPUENDMAC_OFFSET)
#define R_RMPU_MMPUENPTDMAC                       (R_RMPU_BASE + R_RMPU_MMPUENPTDMAC_OFFSET)
#define R_RMPU_MMPURPTDMAC_SEC                    (R_RMPU_BASE + R_RMPU_MMPURPTDMAC_SEC_OFFSET)
#define R_RMPU_MMPUACDMAC(m)                      (R_RMPU_BASE + R_RMPU_MMPUACDMAC_OFFSET(m))
#define R_RMPU_MMPUSDMAC(m)                       (R_RMPU_BASE + R_RMPU_MMPUSDMAC_OFFSET(m))
#define R_RMPU_MMPUEDMAC(m)                       (R_RMPU_BASE + R_RMPU_MMPUEDMAC_OFFSET(m))
#define R_RMPU_MMPUENEDMAC                        (R_RMPU_BASE + R_RMPU_MMPUENEDMAC_OFFSET)
#define R_RMPU_MMPUENPTEDMAC                      (R_RMPU_BASE + R_RMPU_MMPUENPTEDMAC_OFFSET)
#define R_RMPU_MMPURPTEDMAC                       (R_RMPU_BASE + R_RMPU_MMPURPTEDMAC_OFFSET)
#define R_RMPU_MMPUACEDMAC(m)                     (R_RMPU_BASE + R_RMPU_MMPUACEDMAC_OFFSET(m))
#define R_RMPU_MMPUSEDMAC(m)                      (R_RMPU_BASE + R_RMPU_MMPUSEDMAC_OFFSET(m))
#define R_RMPU_MMPUEEDMAC(m)                      (R_RMPU_BASE + R_RMPU_MMPUEEDMAC_OFFSET(m))
#define R_RMPU_MMPUENCEU                          (R_RMPU_BASE + R_RMPU_MMPUENCEU_OFFSET)
#define R_RMPU_MMPUENPTCEU                        (R_RMPU_BASE + R_RMPU_MMPUENPTCEU_OFFSET)
#define R_RMPU_MMPURPTCEU                         (R_RMPU_BASE + R_RMPU_MMPURPTCEU_OFFSET)
#define R_RMPU_MMPUACCEU(m)                       (R_RMPU_BASE + R_RMPU_MMPUACCEU_OFFSET(m))
#define R_RMPU_MMPUSCEU(m)                        (R_RMPU_BASE + R_RMPU_MMPUSCEU_OFFSET(m))
#define R_RMPU_MMPUECEU(m)                        (R_RMPU_BASE + R_RMPU_MMPUECEU_OFFSET(m))

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


/* Maximum number of channels */

#define RMPU_MAX_CHANNELS    8

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_RMPU_H */

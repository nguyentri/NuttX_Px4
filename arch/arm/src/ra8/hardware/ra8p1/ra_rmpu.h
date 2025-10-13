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

/* Channel stride for multi-channel peripherals */
#define R_RMPU_CH_STRIDE    0x00000200
#define R_RMPU_CH_BASE(ch)   (R_RMPU_BASE + ((uint32_t)(ch) * R_RMPU_CH_STRIDE))

/* RMPU Register Offsets */

#define R_RMPU_MMPUOAD_OFFSET     0x00000000  /* MMPU Operation After Detection Register */
#define R_RMPU_MMPUOADPT_OFFSET     0x00000004  /* MMPU Operation After Detection Protect Register */
/* MMPUENDMAC%s Registers (0-1) */
#define R_RMPU_MMPUENDMAC0_OFFSET     0x00000100  /* MMPU Enable Register for DMAC */
#define R_RMPU_MMPUENDMAC1_OFFSET     0x00000300  /* MMPU Enable Register for DMAC */
/* MMPUENPTDMAC%s Registers (0-1) */
#define R_RMPU_MMPUENPTDMAC0_OFFSET     0x00000104  /* MMPU Enable Protect Register for DMAC 0 */
#define R_RMPU_MMPUENPTDMAC1_OFFSET     0x00000304  /* MMPU Enable Protect Register for DMAC 1 */
/* MMPURPTDMAC_SEC%s Registers (0-1) */
#define R_RMPU_MMPURPTDMAC_SEC0_OFFSET     0x0000010c  /* MMPU Regions Protect Register for DMAC Secure 0 */
#define R_RMPU_MMPURPTDMAC_SEC1_OFFSET     0x0000030c  /* MMPU Regions Protect Register for DMAC Secure 1 */
/* MMPUACDMAC0%s Registers (00-07) */
#define R_RMPU_MMPUACDMAC000_OFFSET     0x00000200  /* MMPU Access Control Register for DMAC */
#define R_RMPU_MMPUACDMAC001_OFFSET     0x00000210  /* MMPU Access Control Register for DMAC */
#define R_RMPU_MMPUACDMAC002_OFFSET     0x00000220  /* MMPU Access Control Register for DMAC */
#define R_RMPU_MMPUACDMAC003_OFFSET     0x00000230  /* MMPU Access Control Register for DMAC */
#define R_RMPU_MMPUACDMAC004_OFFSET     0x00000240  /* MMPU Access Control Register for DMAC */
#define R_RMPU_MMPUACDMAC005_OFFSET     0x00000250  /* MMPU Access Control Register for DMAC */
#define R_RMPU_MMPUACDMAC006_OFFSET     0x00000260  /* MMPU Access Control Register for DMAC */
#define R_RMPU_MMPUACDMAC007_OFFSET     0x00000270  /* MMPU Access Control Register for DMAC */
/* MMPUSDMAC0%s Registers (00-07) */
#define R_RMPU_MMPUSDMAC000_OFFSET     0x00000204  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUSDMAC001_OFFSET     0x00000214  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUSDMAC002_OFFSET     0x00000224  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUSDMAC003_OFFSET     0x00000234  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUSDMAC004_OFFSET     0x00000244  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUSDMAC005_OFFSET     0x00000254  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUSDMAC006_OFFSET     0x00000264  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUSDMAC007_OFFSET     0x00000274  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
/* MMPUEDMAC0%s Registers (00-07) */
#define R_RMPU_MMPUEDMAC000_OFFSET     0x00000208  /* MMPU End Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUEDMAC001_OFFSET     0x00000218  /* MMPU End Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUEDMAC002_OFFSET     0x00000228  /* MMPU End Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUEDMAC003_OFFSET     0x00000238  /* MMPU End Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUEDMAC004_OFFSET     0x00000248  /* MMPU End Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUEDMAC005_OFFSET     0x00000258  /* MMPU End Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUEDMAC006_OFFSET     0x00000268  /* MMPU End Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUEDMAC007_OFFSET     0x00000278  /* MMPU End Address Register for DMAC (n = 00 to 07) */
/* MMPUACDMAC1%s Registers (00-07) */
#define R_RMPU_MMPUACDMAC100_OFFSET     0x00000400  /* MMPU Access Control Register for DMAC */
#define R_RMPU_MMPUACDMAC101_OFFSET     0x00000410  /* MMPU Access Control Register for DMAC */
#define R_RMPU_MMPUACDMAC102_OFFSET     0x00000420  /* MMPU Access Control Register for DMAC */
#define R_RMPU_MMPUACDMAC103_OFFSET     0x00000430  /* MMPU Access Control Register for DMAC */
#define R_RMPU_MMPUACDMAC104_OFFSET     0x00000440  /* MMPU Access Control Register for DMAC */
#define R_RMPU_MMPUACDMAC105_OFFSET     0x00000450  /* MMPU Access Control Register for DMAC */
#define R_RMPU_MMPUACDMAC106_OFFSET     0x00000460  /* MMPU Access Control Register for DMAC */
#define R_RMPU_MMPUACDMAC107_OFFSET     0x00000470  /* MMPU Access Control Register for DMAC */
/* MMPUSDMAC1%s Registers (00-07) */
#define R_RMPU_MMPUSDMAC100_OFFSET     0x00000404  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUSDMAC101_OFFSET     0x00000414  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUSDMAC102_OFFSET     0x00000424  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUSDMAC103_OFFSET     0x00000434  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUSDMAC104_OFFSET     0x00000444  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUSDMAC105_OFFSET     0x00000454  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUSDMAC106_OFFSET     0x00000464  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUSDMAC107_OFFSET     0x00000474  /* MMPU Start Address Register for DMAC (n = 00 to 07) */
/* MMPUEDMAC1%s Registers (00-07) */
#define R_RMPU_MMPUEDMAC100_OFFSET     0x00000408  /* MMPU End Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUEDMAC101_OFFSET     0x00000418  /* MMPU End Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUEDMAC102_OFFSET     0x00000428  /* MMPU End Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUEDMAC103_OFFSET     0x00000438  /* MMPU End Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUEDMAC104_OFFSET     0x00000448  /* MMPU End Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUEDMAC105_OFFSET     0x00000458  /* MMPU End Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUEDMAC106_OFFSET     0x00000468  /* MMPU End Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUEDMAC107_OFFSET     0x00000478  /* MMPU End Address Register for DMAC (n = 00 to 07) */
#define R_RMPU_MMPUENEDMAC_OFFSET     0x00000500  /* MMPU Enable Register for EDMAC */
#define R_RMPU_MMPUENPTEDMAC_OFFSET     0x00000504  /* MMPU Enable Protect Register for EDMAC */
#define R_RMPU_MMPURPTEDMAC_OFFSET     0x00000508  /* MMPU Regions Protect Register for EDMAC */
/* MMPUACEDMAC%s Registers (0-4) */
#define R_RMPU_MMPUACEDMAC0_OFFSET     0x00000600  /* MMPU Access Control Register for EDMAC */
#define R_RMPU_MMPUACEDMAC1_OFFSET     0x00000610  /* MMPU Access Control Register for EDMAC */
#define R_RMPU_MMPUACEDMAC2_OFFSET     0x00000620  /* MMPU Access Control Register for EDMAC */
#define R_RMPU_MMPUACEDMAC3_OFFSET     0x00000630  /* MMPU Access Control Register for EDMAC */
#define R_RMPU_MMPUACEDMAC4_OFFSET     0x00000640  /* MMPU Access Control Register for EDMAC */
/* MMPUSEDMAC%s Registers (0-4) */
#define R_RMPU_MMPUSEDMAC0_OFFSET     0x00000604  /* MMPU Start Address Register for EDMAC (n = 0 to 4) */
#define R_RMPU_MMPUSEDMAC1_OFFSET     0x00000614  /* MMPU Start Address Register for EDMAC (n = 0 to 4) */
#define R_RMPU_MMPUSEDMAC2_OFFSET     0x00000624  /* MMPU Start Address Register for EDMAC (n = 0 to 4) */
#define R_RMPU_MMPUSEDMAC3_OFFSET     0x00000634  /* MMPU Start Address Register for EDMAC (n = 0 to 4) */
#define R_RMPU_MMPUSEDMAC4_OFFSET     0x00000644  /* MMPU Start Address Register for EDMAC (n = 0 to 4) */
/* MMPUEEDMAC%s Registers (0-4) */
#define R_RMPU_MMPUEEDMAC0_OFFSET     0x00000608  /* MMPU End Address Register for EDMAC */
#define R_RMPU_MMPUEEDMAC1_OFFSET     0x00000618  /* MMPU End Address Register for EDMAC */
#define R_RMPU_MMPUEEDMAC2_OFFSET     0x00000628  /* MMPU End Address Register for EDMAC */
#define R_RMPU_MMPUEEDMAC3_OFFSET     0x00000638  /* MMPU End Address Register for EDMAC */
#define R_RMPU_MMPUEEDMAC4_OFFSET     0x00000648  /* MMPU End Address Register for EDMAC */
#define R_RMPU_MMPUENGLCDC_OFFSET     0x00000700  /* MMPU Enable Register for GLCDC */
#define R_RMPU_MMPUENPTGLCDC_OFFSET     0x00000704  /* MMPU Enable Protect Register for GLCDC */
#define R_RMPU_MMPURPTGLCDC_OFFSET     0x00000708  /* MMPU Regions Protect Register for GLCDC */
/* MMPUACGLCDC%s Registers (0-1) */
#define R_RMPU_MMPUACGLCDC0_OFFSET     0x00000800  /* MMPU Access Control Register for GLCDC (n = 0, 1) */
#define R_RMPU_MMPUACGLCDC1_OFFSET     0x00000810  /* MMPU Access Control Register for GLCDC (n = 0, 1) */
/* MMPUSGLCDC%s Registers (0-1) */
#define R_RMPU_MMPUSGLCDC0_OFFSET     0x00000804  /* MMPU Start Address Register for GLCDC (n = 0, 1) */
#define R_RMPU_MMPUSGLCDC1_OFFSET     0x00000814  /* MMPU Start Address Register for GLCDC (n = 0, 1) */
/* MMPUEGLCDC%s Registers (0-1) */
#define R_RMPU_MMPUEGLCDC0_OFFSET     0x00000808  /* MMPU End Address Register for GLCDC (n = 0, 1) */
#define R_RMPU_MMPUEGLCDC1_OFFSET     0x00000818  /* MMPU End Address Register for GLCDC (n = 0, 1) */
#define R_RMPU_MMPUENDRW_OFFSET     0x00000900  /* MMPU Enable Register for DRW */
#define R_RMPU_MMPUENPDRW_OFFSET     0x00000904  /* MMPU Enable Protect Register for DRW */
#define R_RMPU_MMPURPTDRW_OFFSET     0x00000908  /* MMPU Regions Protect Register for DRW */
/* MMPUACDRW%s Registers (0-2) */
#define R_RMPU_MMPUACDRW0_OFFSET     0x00000a00  /* MMPU Access Control Register for DRW (n = 0 to 2) */
#define R_RMPU_MMPUACDRW1_OFFSET     0x00000a10  /* MMPU Access Control Register for DRW (n = 0 to 2) */
#define R_RMPU_MMPUACDRW2_OFFSET     0x00000a20  /* MMPU Access Control Register for DRW (n = 0 to 2) */
/* MMPUSDRW%s Registers (0-2) */
#define R_RMPU_MMPUSDRW0_OFFSET     0x00000a04  /* MMPU Start Address Register for DRW (n = 0 to 2) */
#define R_RMPU_MMPUSDRW1_OFFSET     0x00000a14  /* MMPU Start Address Register for DRW (n = 0 to 2) */
#define R_RMPU_MMPUSDRW2_OFFSET     0x00000a24  /* MMPU Start Address Register for DRW (n = 0 to 2) */
/* MMPUEDRW%s Registers (0-2) */
#define R_RMPU_MMPUEDRW0_OFFSET     0x00000a08  /* MMPU End Address Register for DRW (n = 0 to 2) */
#define R_RMPU_MMPUEDRW1_OFFSET     0x00000a18  /* MMPU End Address Register for DRW (n = 0 to 2) */
#define R_RMPU_MMPUEDRW2_OFFSET     0x00000a28  /* MMPU End Address Register for DRW (n = 0 to 2) */
#define R_RMPU_MMPUENMIPID_OFFSET     0x00000b00  /* MMPU Enable Register for MIPI-DSI */
#define R_RMPU_MMPUENPTMIPID_OFFSET     0x00000b04  /* MMPU Enable Protect Register for MIPI-DSI */
#define R_RMPU_MMPURPTMIPID_OFFSET     0x00000b08  /* MMPU Regions Protect Register for MIPI-DSI */
#define R_RMPU_MMPUACMIPID_OFFSET     0x00000c00  /* MMPU Access Control Register for MIPI-DSI */
#define R_RMPU_MMPUSMIPID_OFFSET     0x00000c04  /* MMPU Start Address Register for MIPI-DSI */
#define R_RMPU_MMPUEMIPID_OFFSET     0x00000c08  /* MMPU End Address Register for MIPI-DSI */
#define R_RMPU_MMPUENCEU_OFFSET     0x00000d00  /* MMPU Enable Register for CEU */
#define R_RMPU_MMPUENPTCEU_OFFSET     0x00000d04  /* MMPU Enable Protect Register for CEU */
#define R_RMPU_MMPURPTCEU_OFFSET     0x00000d08  /* MMPU Regions Protect Register for CEU */
/* MMPUACCEU%s Registers (0-1) */
#define R_RMPU_MMPUACCEU0_OFFSET     0x00000e00  /* MMPU Access Control Register for CEU (n = 0, 1) */
#define R_RMPU_MMPUACCEU1_OFFSET     0x00000e10  /* MMPU Access Control Register for CEU (n = 0, 1) */
/* MMPUSCEU%s Registers (0-1) */
#define R_RMPU_MMPUSCEU0_OFFSET     0x00000e04  /* MMPU Start Address Register for CEU (n = 0, 1) */
#define R_RMPU_MMPUSCEU1_OFFSET     0x00000e14  /* MMPU Start Address Register for CEU (n = 0, 1) */
/* MMPUECEU%s Registers (0-1) */
#define R_RMPU_MMPUECEU0_OFFSET     0x00000e08  /* MMPU End Address Register for CEU (n = 0, 1) */
#define R_RMPU_MMPUECEU1_OFFSET     0x00000e18  /* MMPU End Address Register for CEU (n = 0, 1) */
#define R_RMPU_MMPUENMIPIC_OFFSET     0x00000f00  /* MMPU Enable Register for MIPI-CSI by VIN */
#define R_RMPU_MMPUENPTMIPIC_OFFSET     0x00000f04  /* MMPU Enable Protect Register for MIPI-CSI by VIN */
#define R_RMPU_MMPURPTMIPIC_OFFSET     0x00000f08  /* MMPU Regions Protect Register for MIPI-CSI by VIN */
/* MMPUACMIPIC%s Registers (0-2) */
#define R_RMPU_MMPUACMIPIC0_OFFSET     0x00001000  /* MMPU Access Control Register for MIPI-CSI via VIN (n = 0 to 2) */
#define R_RMPU_MMPUACMIPIC1_OFFSET     0x00001010  /* MMPU Access Control Register for MIPI-CSI via VIN (n = 0 to 2) */
#define R_RMPU_MMPUACMIPIC2_OFFSET     0x00001020  /* MMPU Access Control Register for MIPI-CSI via VIN (n = 0 to 2) */
/* MMPUSMIPIC%s Registers (0-2) */
#define R_RMPU_MMPUSMIPIC0_OFFSET     0x00001004  /* MMPU Start Address Register for MIPI-CSI via VIN (n = 0 to 2) */
#define R_RMPU_MMPUSMIPIC1_OFFSET     0x00001014  /* MMPU Start Address Register for MIPI-CSI via VIN (n = 0 to 2) */
#define R_RMPU_MMPUSMIPIC2_OFFSET     0x00001024  /* MMPU Start Address Register for MIPI-CSI via VIN (n = 0 to 2) */
/* MMPUEMIPIC%s Registers (0-2) */
#define R_RMPU_MMPUEMIPIC0_OFFSET     0x00001008  /* MMPU End Address Register for MIPI-CSI via VIN (n = 0 to 2) */
#define R_RMPU_MMPUEMIPIC1_OFFSET     0x00001018  /* MMPU End Address Register for MIPI-CSI via VIN (n = 0 to 2) */
#define R_RMPU_MMPUEMIPIC2_OFFSET     0x00001028  /* MMPU End Address Register for MIPI-CSI via VIN (n = 0 to 2) */
#define R_RMPU_MMPUENNPU_OFFSET     0x00001100  /* MMPU Enable Register for NPU */
#define R_RMPU_MMPUENPTNPU_OFFSET     0x00001104  /* MMPU Enable Protect Register for NPU */
#define R_RMPU_MMPURPTNPU_OFFSET     0x00001108  /* MMPU Regions Protect Register for NPU */
/* MMPUACNPU%s Registers (0-4) */
#define R_RMPU_MMPUACNPU0_OFFSET     0x00001200  /* MMPU Access Control Register for NPU (n = 0 to 4) */
#define R_RMPU_MMPUACNPU1_OFFSET     0x00001210  /* MMPU Access Control Register for NPU (n = 0 to 4) */
#define R_RMPU_MMPUACNPU2_OFFSET     0x00001220  /* MMPU Access Control Register for NPU (n = 0 to 4) */
#define R_RMPU_MMPUACNPU3_OFFSET     0x00001230  /* MMPU Access Control Register for NPU (n = 0 to 4) */
#define R_RMPU_MMPUACNPU4_OFFSET     0x00001240  /* MMPU Access Control Register for NPU (n = 0 to 4) */
/* MMPUSNPU%s Registers (0-4) */
#define R_RMPU_MMPUSNPU0_OFFSET     0x00001204  /* MMPU Start Address Register for NPU (n = 0 to 4) */
#define R_RMPU_MMPUSNPU1_OFFSET     0x00001214  /* MMPU Start Address Register for NPU (n = 0 to 4) */
#define R_RMPU_MMPUSNPU2_OFFSET     0x00001224  /* MMPU Start Address Register for NPU (n = 0 to 4) */
#define R_RMPU_MMPUSNPU3_OFFSET     0x00001234  /* MMPU Start Address Register for NPU (n = 0 to 4) */
#define R_RMPU_MMPUSNPU4_OFFSET     0x00001244  /* MMPU Start Address Register for NPU (n = 0 to 4) */
/* MMPUENPU%s Registers (0-4) */
#define R_RMPU_MMPUENPU0_OFFSET     0x00001208  /* MMPU End Address Register for NPU (n = 0 to 4) */
#define R_RMPU_MMPUENPU1_OFFSET     0x00001218  /* MMPU End Address Register for NPU (n = 0 to 4) */
#define R_RMPU_MMPUENPU2_OFFSET     0x00001228  /* MMPU End Address Register for NPU (n = 0 to 4) */
#define R_RMPU_MMPUENPU3_OFFSET     0x00001238  /* MMPU End Address Register for NPU (n = 0 to 4) */
#define R_RMPU_MMPUENPU4_OFFSET     0x00001248  /* MMPU End Address Register for NPU (n = 0 to 4) */

/* RMPU Register Addresses */

#define R_RMPU_MMPUOAD                 (R_RMPU_BASE + R_RMPU_MMPUOAD_OFFSET)
#define R_RMPU_MMPUOADPT                 (R_RMPU_BASE + R_RMPU_MMPUOADPT_OFFSET)
#define R_RMPU_MMPUENDMAC0                 (R_RMPU_BASE + R_RMPU_MMPUENDMAC0_OFFSET)
#define R_RMPU_MMPUENDMAC1                 (R_RMPU_BASE + R_RMPU_MMPUENDMAC1_OFFSET)
#define R_RMPU_MMPUENPTDMAC0                 (R_RMPU_BASE + R_RMPU_MMPUENPTDMAC0_OFFSET)
#define R_RMPU_MMPUENPTDMAC1                 (R_RMPU_BASE + R_RMPU_MMPUENPTDMAC1_OFFSET)
#define R_RMPU_MMPURPTDMAC_SEC0                 (R_RMPU_BASE + R_RMPU_MMPURPTDMAC_SEC0_OFFSET)
#define R_RMPU_MMPURPTDMAC_SEC1                 (R_RMPU_BASE + R_RMPU_MMPURPTDMAC_SEC1_OFFSET)
#define R_RMPU_MMPUACDMAC000                 (R_RMPU_BASE + R_RMPU_MMPUACDMAC000_OFFSET)
#define R_RMPU_MMPUACDMAC001                 (R_RMPU_BASE + R_RMPU_MMPUACDMAC001_OFFSET)
#define R_RMPU_MMPUACDMAC002                 (R_RMPU_BASE + R_RMPU_MMPUACDMAC002_OFFSET)
#define R_RMPU_MMPUACDMAC003                 (R_RMPU_BASE + R_RMPU_MMPUACDMAC003_OFFSET)
#define R_RMPU_MMPUACDMAC004                 (R_RMPU_BASE + R_RMPU_MMPUACDMAC004_OFFSET)
#define R_RMPU_MMPUACDMAC005                 (R_RMPU_BASE + R_RMPU_MMPUACDMAC005_OFFSET)
#define R_RMPU_MMPUACDMAC006                 (R_RMPU_BASE + R_RMPU_MMPUACDMAC006_OFFSET)
#define R_RMPU_MMPUACDMAC007                 (R_RMPU_BASE + R_RMPU_MMPUACDMAC007_OFFSET)
#define R_RMPU_MMPUSDMAC000                 (R_RMPU_BASE + R_RMPU_MMPUSDMAC000_OFFSET)
#define R_RMPU_MMPUSDMAC001                 (R_RMPU_BASE + R_RMPU_MMPUSDMAC001_OFFSET)
#define R_RMPU_MMPUSDMAC002                 (R_RMPU_BASE + R_RMPU_MMPUSDMAC002_OFFSET)
#define R_RMPU_MMPUSDMAC003                 (R_RMPU_BASE + R_RMPU_MMPUSDMAC003_OFFSET)
#define R_RMPU_MMPUSDMAC004                 (R_RMPU_BASE + R_RMPU_MMPUSDMAC004_OFFSET)
#define R_RMPU_MMPUSDMAC005                 (R_RMPU_BASE + R_RMPU_MMPUSDMAC005_OFFSET)
#define R_RMPU_MMPUSDMAC006                 (R_RMPU_BASE + R_RMPU_MMPUSDMAC006_OFFSET)
#define R_RMPU_MMPUSDMAC007                 (R_RMPU_BASE + R_RMPU_MMPUSDMAC007_OFFSET)
#define R_RMPU_MMPUEDMAC000                 (R_RMPU_BASE + R_RMPU_MMPUEDMAC000_OFFSET)
#define R_RMPU_MMPUEDMAC001                 (R_RMPU_BASE + R_RMPU_MMPUEDMAC001_OFFSET)
#define R_RMPU_MMPUEDMAC002                 (R_RMPU_BASE + R_RMPU_MMPUEDMAC002_OFFSET)
#define R_RMPU_MMPUEDMAC003                 (R_RMPU_BASE + R_RMPU_MMPUEDMAC003_OFFSET)
#define R_RMPU_MMPUEDMAC004                 (R_RMPU_BASE + R_RMPU_MMPUEDMAC004_OFFSET)
#define R_RMPU_MMPUEDMAC005                 (R_RMPU_BASE + R_RMPU_MMPUEDMAC005_OFFSET)
#define R_RMPU_MMPUEDMAC006                 (R_RMPU_BASE + R_RMPU_MMPUEDMAC006_OFFSET)
#define R_RMPU_MMPUEDMAC007                 (R_RMPU_BASE + R_RMPU_MMPUEDMAC007_OFFSET)
#define R_RMPU_MMPUACDMAC100                 (R_RMPU_BASE + R_RMPU_MMPUACDMAC100_OFFSET)
#define R_RMPU_MMPUACDMAC101                 (R_RMPU_BASE + R_RMPU_MMPUACDMAC101_OFFSET)
#define R_RMPU_MMPUACDMAC102                 (R_RMPU_BASE + R_RMPU_MMPUACDMAC102_OFFSET)
#define R_RMPU_MMPUACDMAC103                 (R_RMPU_BASE + R_RMPU_MMPUACDMAC103_OFFSET)
#define R_RMPU_MMPUACDMAC104                 (R_RMPU_BASE + R_RMPU_MMPUACDMAC104_OFFSET)
#define R_RMPU_MMPUACDMAC105                 (R_RMPU_BASE + R_RMPU_MMPUACDMAC105_OFFSET)
#define R_RMPU_MMPUACDMAC106                 (R_RMPU_BASE + R_RMPU_MMPUACDMAC106_OFFSET)
#define R_RMPU_MMPUACDMAC107                 (R_RMPU_BASE + R_RMPU_MMPUACDMAC107_OFFSET)
#define R_RMPU_MMPUSDMAC100                 (R_RMPU_BASE + R_RMPU_MMPUSDMAC100_OFFSET)
#define R_RMPU_MMPUSDMAC101                 (R_RMPU_BASE + R_RMPU_MMPUSDMAC101_OFFSET)
#define R_RMPU_MMPUSDMAC102                 (R_RMPU_BASE + R_RMPU_MMPUSDMAC102_OFFSET)
#define R_RMPU_MMPUSDMAC103                 (R_RMPU_BASE + R_RMPU_MMPUSDMAC103_OFFSET)
#define R_RMPU_MMPUSDMAC104                 (R_RMPU_BASE + R_RMPU_MMPUSDMAC104_OFFSET)
#define R_RMPU_MMPUSDMAC105                 (R_RMPU_BASE + R_RMPU_MMPUSDMAC105_OFFSET)
#define R_RMPU_MMPUSDMAC106                 (R_RMPU_BASE + R_RMPU_MMPUSDMAC106_OFFSET)
#define R_RMPU_MMPUSDMAC107                 (R_RMPU_BASE + R_RMPU_MMPUSDMAC107_OFFSET)
#define R_RMPU_MMPUEDMAC100                 (R_RMPU_BASE + R_RMPU_MMPUEDMAC100_OFFSET)
#define R_RMPU_MMPUEDMAC101                 (R_RMPU_BASE + R_RMPU_MMPUEDMAC101_OFFSET)
#define R_RMPU_MMPUEDMAC102                 (R_RMPU_BASE + R_RMPU_MMPUEDMAC102_OFFSET)
#define R_RMPU_MMPUEDMAC103                 (R_RMPU_BASE + R_RMPU_MMPUEDMAC103_OFFSET)
#define R_RMPU_MMPUEDMAC104                 (R_RMPU_BASE + R_RMPU_MMPUEDMAC104_OFFSET)
#define R_RMPU_MMPUEDMAC105                 (R_RMPU_BASE + R_RMPU_MMPUEDMAC105_OFFSET)
#define R_RMPU_MMPUEDMAC106                 (R_RMPU_BASE + R_RMPU_MMPUEDMAC106_OFFSET)
#define R_RMPU_MMPUEDMAC107                 (R_RMPU_BASE + R_RMPU_MMPUEDMAC107_OFFSET)
#define R_RMPU_MMPUENEDMAC                 (R_RMPU_BASE + R_RMPU_MMPUENEDMAC_OFFSET)
#define R_RMPU_MMPUENPTEDMAC                 (R_RMPU_BASE + R_RMPU_MMPUENPTEDMAC_OFFSET)
#define R_RMPU_MMPURPTEDMAC                 (R_RMPU_BASE + R_RMPU_MMPURPTEDMAC_OFFSET)
#define R_RMPU_MMPUACEDMAC0                 (R_RMPU_BASE + R_RMPU_MMPUACEDMAC0_OFFSET)
#define R_RMPU_MMPUACEDMAC1                 (R_RMPU_BASE + R_RMPU_MMPUACEDMAC1_OFFSET)
#define R_RMPU_MMPUACEDMAC2                 (R_RMPU_BASE + R_RMPU_MMPUACEDMAC2_OFFSET)
#define R_RMPU_MMPUACEDMAC3                 (R_RMPU_BASE + R_RMPU_MMPUACEDMAC3_OFFSET)
#define R_RMPU_MMPUACEDMAC4                 (R_RMPU_BASE + R_RMPU_MMPUACEDMAC4_OFFSET)
#define R_RMPU_MMPUSEDMAC0                 (R_RMPU_BASE + R_RMPU_MMPUSEDMAC0_OFFSET)
#define R_RMPU_MMPUSEDMAC1                 (R_RMPU_BASE + R_RMPU_MMPUSEDMAC1_OFFSET)
#define R_RMPU_MMPUSEDMAC2                 (R_RMPU_BASE + R_RMPU_MMPUSEDMAC2_OFFSET)
#define R_RMPU_MMPUSEDMAC3                 (R_RMPU_BASE + R_RMPU_MMPUSEDMAC3_OFFSET)
#define R_RMPU_MMPUSEDMAC4                 (R_RMPU_BASE + R_RMPU_MMPUSEDMAC4_OFFSET)
#define R_RMPU_MMPUEEDMAC0                 (R_RMPU_BASE + R_RMPU_MMPUEEDMAC0_OFFSET)
#define R_RMPU_MMPUEEDMAC1                 (R_RMPU_BASE + R_RMPU_MMPUEEDMAC1_OFFSET)
#define R_RMPU_MMPUEEDMAC2                 (R_RMPU_BASE + R_RMPU_MMPUEEDMAC2_OFFSET)
#define R_RMPU_MMPUEEDMAC3                 (R_RMPU_BASE + R_RMPU_MMPUEEDMAC3_OFFSET)
#define R_RMPU_MMPUEEDMAC4                 (R_RMPU_BASE + R_RMPU_MMPUEEDMAC4_OFFSET)
#define R_RMPU_MMPUENGLCDC                 (R_RMPU_BASE + R_RMPU_MMPUENGLCDC_OFFSET)
#define R_RMPU_MMPUENPTGLCDC                 (R_RMPU_BASE + R_RMPU_MMPUENPTGLCDC_OFFSET)
#define R_RMPU_MMPURPTGLCDC                 (R_RMPU_BASE + R_RMPU_MMPURPTGLCDC_OFFSET)
#define R_RMPU_MMPUACGLCDC0                 (R_RMPU_BASE + R_RMPU_MMPUACGLCDC0_OFFSET)
#define R_RMPU_MMPUACGLCDC1                 (R_RMPU_BASE + R_RMPU_MMPUACGLCDC1_OFFSET)
#define R_RMPU_MMPUSGLCDC0                 (R_RMPU_BASE + R_RMPU_MMPUSGLCDC0_OFFSET)
#define R_RMPU_MMPUSGLCDC1                 (R_RMPU_BASE + R_RMPU_MMPUSGLCDC1_OFFSET)
#define R_RMPU_MMPUEGLCDC0                 (R_RMPU_BASE + R_RMPU_MMPUEGLCDC0_OFFSET)
#define R_RMPU_MMPUEGLCDC1                 (R_RMPU_BASE + R_RMPU_MMPUEGLCDC1_OFFSET)
#define R_RMPU_MMPUENDRW                 (R_RMPU_BASE + R_RMPU_MMPUENDRW_OFFSET)
#define R_RMPU_MMPUENPDRW                 (R_RMPU_BASE + R_RMPU_MMPUENPDRW_OFFSET)
#define R_RMPU_MMPURPTDRW                 (R_RMPU_BASE + R_RMPU_MMPURPTDRW_OFFSET)
#define R_RMPU_MMPUACDRW0                 (R_RMPU_BASE + R_RMPU_MMPUACDRW0_OFFSET)
#define R_RMPU_MMPUACDRW1                 (R_RMPU_BASE + R_RMPU_MMPUACDRW1_OFFSET)
#define R_RMPU_MMPUACDRW2                 (R_RMPU_BASE + R_RMPU_MMPUACDRW2_OFFSET)
#define R_RMPU_MMPUSDRW0                 (R_RMPU_BASE + R_RMPU_MMPUSDRW0_OFFSET)
#define R_RMPU_MMPUSDRW1                 (R_RMPU_BASE + R_RMPU_MMPUSDRW1_OFFSET)
#define R_RMPU_MMPUSDRW2                 (R_RMPU_BASE + R_RMPU_MMPUSDRW2_OFFSET)
#define R_RMPU_MMPUEDRW0                 (R_RMPU_BASE + R_RMPU_MMPUEDRW0_OFFSET)
#define R_RMPU_MMPUEDRW1                 (R_RMPU_BASE + R_RMPU_MMPUEDRW1_OFFSET)
#define R_RMPU_MMPUEDRW2                 (R_RMPU_BASE + R_RMPU_MMPUEDRW2_OFFSET)
#define R_RMPU_MMPUENMIPID                 (R_RMPU_BASE + R_RMPU_MMPUENMIPID_OFFSET)
#define R_RMPU_MMPUENPTMIPID                 (R_RMPU_BASE + R_RMPU_MMPUENPTMIPID_OFFSET)
#define R_RMPU_MMPURPTMIPID                 (R_RMPU_BASE + R_RMPU_MMPURPTMIPID_OFFSET)
#define R_RMPU_MMPUACMIPID                 (R_RMPU_BASE + R_RMPU_MMPUACMIPID_OFFSET)
#define R_RMPU_MMPUSMIPID                 (R_RMPU_BASE + R_RMPU_MMPUSMIPID_OFFSET)
#define R_RMPU_MMPUEMIPID                 (R_RMPU_BASE + R_RMPU_MMPUEMIPID_OFFSET)
#define R_RMPU_MMPUENCEU                 (R_RMPU_BASE + R_RMPU_MMPUENCEU_OFFSET)
#define R_RMPU_MMPUENPTCEU                 (R_RMPU_BASE + R_RMPU_MMPUENPTCEU_OFFSET)
#define R_RMPU_MMPURPTCEU                 (R_RMPU_BASE + R_RMPU_MMPURPTCEU_OFFSET)
#define R_RMPU_MMPUACCEU0                 (R_RMPU_BASE + R_RMPU_MMPUACCEU0_OFFSET)
#define R_RMPU_MMPUACCEU1                 (R_RMPU_BASE + R_RMPU_MMPUACCEU1_OFFSET)
#define R_RMPU_MMPUSCEU0                 (R_RMPU_BASE + R_RMPU_MMPUSCEU0_OFFSET)
#define R_RMPU_MMPUSCEU1                 (R_RMPU_BASE + R_RMPU_MMPUSCEU1_OFFSET)
#define R_RMPU_MMPUECEU0                 (R_RMPU_BASE + R_RMPU_MMPUECEU0_OFFSET)
#define R_RMPU_MMPUECEU1                 (R_RMPU_BASE + R_RMPU_MMPUECEU1_OFFSET)
#define R_RMPU_MMPUENMIPIC                 (R_RMPU_BASE + R_RMPU_MMPUENMIPIC_OFFSET)
#define R_RMPU_MMPUENPTMIPIC                 (R_RMPU_BASE + R_RMPU_MMPUENPTMIPIC_OFFSET)
#define R_RMPU_MMPURPTMIPIC                 (R_RMPU_BASE + R_RMPU_MMPURPTMIPIC_OFFSET)
#define R_RMPU_MMPUACMIPIC0                 (R_RMPU_BASE + R_RMPU_MMPUACMIPIC0_OFFSET)
#define R_RMPU_MMPUACMIPIC1                 (R_RMPU_BASE + R_RMPU_MMPUACMIPIC1_OFFSET)
#define R_RMPU_MMPUACMIPIC2                 (R_RMPU_BASE + R_RMPU_MMPUACMIPIC2_OFFSET)
#define R_RMPU_MMPUSMIPIC0                 (R_RMPU_BASE + R_RMPU_MMPUSMIPIC0_OFFSET)
#define R_RMPU_MMPUSMIPIC1                 (R_RMPU_BASE + R_RMPU_MMPUSMIPIC1_OFFSET)
#define R_RMPU_MMPUSMIPIC2                 (R_RMPU_BASE + R_RMPU_MMPUSMIPIC2_OFFSET)
#define R_RMPU_MMPUEMIPIC0                 (R_RMPU_BASE + R_RMPU_MMPUEMIPIC0_OFFSET)
#define R_RMPU_MMPUEMIPIC1                 (R_RMPU_BASE + R_RMPU_MMPUEMIPIC1_OFFSET)
#define R_RMPU_MMPUEMIPIC2                 (R_RMPU_BASE + R_RMPU_MMPUEMIPIC2_OFFSET)
#define R_RMPU_MMPUENNPU                 (R_RMPU_BASE + R_RMPU_MMPUENNPU_OFFSET)
#define R_RMPU_MMPUENPTNPU                 (R_RMPU_BASE + R_RMPU_MMPUENPTNPU_OFFSET)
#define R_RMPU_MMPURPTNPU                 (R_RMPU_BASE + R_RMPU_MMPURPTNPU_OFFSET)
#define R_RMPU_MMPUACNPU0                 (R_RMPU_BASE + R_RMPU_MMPUACNPU0_OFFSET)
#define R_RMPU_MMPUACNPU1                 (R_RMPU_BASE + R_RMPU_MMPUACNPU1_OFFSET)
#define R_RMPU_MMPUACNPU2                 (R_RMPU_BASE + R_RMPU_MMPUACNPU2_OFFSET)
#define R_RMPU_MMPUACNPU3                 (R_RMPU_BASE + R_RMPU_MMPUACNPU3_OFFSET)
#define R_RMPU_MMPUACNPU4                 (R_RMPU_BASE + R_RMPU_MMPUACNPU4_OFFSET)
#define R_RMPU_MMPUSNPU0                 (R_RMPU_BASE + R_RMPU_MMPUSNPU0_OFFSET)
#define R_RMPU_MMPUSNPU1                 (R_RMPU_BASE + R_RMPU_MMPUSNPU1_OFFSET)
#define R_RMPU_MMPUSNPU2                 (R_RMPU_BASE + R_RMPU_MMPUSNPU2_OFFSET)
#define R_RMPU_MMPUSNPU3                 (R_RMPU_BASE + R_RMPU_MMPUSNPU3_OFFSET)
#define R_RMPU_MMPUSNPU4                 (R_RMPU_BASE + R_RMPU_MMPUSNPU4_OFFSET)
#define R_RMPU_MMPUENPU0                 (R_RMPU_BASE + R_RMPU_MMPUENPU0_OFFSET)
#define R_RMPU_MMPUENPU1                 (R_RMPU_BASE + R_RMPU_MMPUENPU1_OFFSET)
#define R_RMPU_MMPUENPU2                 (R_RMPU_BASE + R_RMPU_MMPUENPU2_OFFSET)
#define R_RMPU_MMPUENPU3                 (R_RMPU_BASE + R_RMPU_MMPUENPU3_OFFSET)
#define R_RMPU_MMPUENPU4                 (R_RMPU_BASE + R_RMPU_MMPUENPU4_OFFSET)

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

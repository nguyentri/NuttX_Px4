/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_mipi_csi.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MIPI_CSI_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MIPI_CSI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* MIPI_CSI Base Address */
#ifndef R_MIPI_CSI_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_MIPI_CSI_BASE           0x40347000
#else
#define R_MIPI_CSI_BASE           0x50347000
#endif
#endif

/* MIPI_CSI Register Offsets */

#define R_MIPI_CSI_MCG_OFFSET                     0x00000000  /* Module Configuration Register */
#define R_MIPI_CSI_MCT0_OFFSET                    0x00000010  /* Module Control Register 0 */
#define R_MIPI_CSI_MCT2_OFFSET                    0x00000018  /* Module Control Register 2 */
#define R_MIPI_CSI_MCT3_OFFSET                    0x0000001c  /* Module Control Register 3 */
#define R_MIPI_CSI_RTCT_OFFSET                    0x00000028  /* Reset Control Register */
#define R_MIPI_CSI_RTST_OFFSET                    0x0000002c  /* Reset Status Register */
#define R_MIPI_CSI_EPCT_OFFSET                    0x00000040  /* EPD Option Control Register */
#define R_MIPI_CSI_EMCT_OFFSET                    0x00000044  /* EPD Misc Option Control Register */
#define R_MIPI_CSI_MIST_OFFSET                    0x00000050  /* Module Interrupt Status Register */
#define R_MIPI_CSI_DTEL_OFFSET                    0x00000060  /* Receive Data Type Enable Low Register */
#define R_MIPI_CSI_DTEH_OFFSET                    0x00000064  /* Receive Data Type Enable High Register */
#define R_MIPI_CSI_RXST_OFFSET                    0x00000070  /* Receive Status Register */
#define R_MIPI_CSI_RXSC_OFFSET                    0x00000074  /* Receive Status Clear Register */
#define R_MIPI_CSI_RXIE_OFFSET                    0x00000078  /* Receive Interrupt Enable Register */
/* DLST%s Registers (0-1) */
#define R_MIPI_CSI_DLST_OFFSET(m)                 (0x00000080 + ((m) * 0x00000010))  /* Data Lane (N) Status Register */
/* DLSC%s Registers (0-1) */
#define R_MIPI_CSI_DLSC_OFFSET(m)                 (0x00000084 + ((m) * 0x00000010))  /* Data Lane (N) Status Clear Register */
/* DLIE%s Registers (0-1) */
#define R_MIPI_CSI_DLIE_OFFSET(m)                 (0x00000088 + ((m) * 0x00000010))  /* Data Lane (N) Interrupt Enable Register */
/* VCST%s Registers (0-15) */
#define R_MIPI_CSI_VCST_OFFSET(m)                 (0x00000100 + ((m) * 0x00000010))  /* Virtual Channel (M) Status Register */
/* VCSC%s Registers (0-15) */
#define R_MIPI_CSI_VCSC_OFFSET(m)                 (0x00000104 + ((m) * 0x00000010))  /* Virtual Channel (M) Status Clear Register */
/* VCIE%s Registers (0-15) */
#define R_MIPI_CSI_VCIE_OFFSET(m)                 (0x00000108 + ((m) * 0x00000010))  /* Virtual Channel (M) Interrupt Enable Register */
#define R_MIPI_CSI_PMST_OFFSET                    0x00000200  /* Power Management Status Register */
#define R_MIPI_CSI_PMSC_OFFSET                    0x00000204  /* Power Management Status Clear Register */
#define R_MIPI_CSI_PMIE_OFFSET                    0x00000208  /* Power Management Interrupt Enable Register */
#define R_MIPI_CSI_GSCT_OFFSET                    0x00000280  /* Generic Short Packet Control Register */
#define R_MIPI_CSI_GSST_OFFSET                    0x00000284  /* Generic Short Packet Status Register */
#define R_MIPI_CSI_GSSC_OFFSET                    0x00000288  /* Generic Short Packet Status Clear Register */
#define R_MIPI_CSI_GSIE_OFFSET                    0x0000028c  /* Generic Short Packet Interrupt Enable Register */
#define R_MIPI_CSI_GSHT_OFFSET                    0x00000290  /* Generic Short Packet Register */
#define R_MIPI_CSI_GSIU_OFFSET                    0x00000294  /* Generic Short Packet Information Update Register */

/* MIPI_CSI Register Addresses */

#define R_MIPI_CSI_MCG                            (R_MIPI_CSI_BASE + R_MIPI_CSI_MCG_OFFSET)
#define R_MIPI_CSI_MCT0                           (R_MIPI_CSI_BASE + R_MIPI_CSI_MCT0_OFFSET)
#define R_MIPI_CSI_MCT2                           (R_MIPI_CSI_BASE + R_MIPI_CSI_MCT2_OFFSET)
#define R_MIPI_CSI_MCT3                           (R_MIPI_CSI_BASE + R_MIPI_CSI_MCT3_OFFSET)
#define R_MIPI_CSI_RTCT                           (R_MIPI_CSI_BASE + R_MIPI_CSI_RTCT_OFFSET)
#define R_MIPI_CSI_RTST                           (R_MIPI_CSI_BASE + R_MIPI_CSI_RTST_OFFSET)
#define R_MIPI_CSI_EPCT                           (R_MIPI_CSI_BASE + R_MIPI_CSI_EPCT_OFFSET)
#define R_MIPI_CSI_EMCT                           (R_MIPI_CSI_BASE + R_MIPI_CSI_EMCT_OFFSET)
#define R_MIPI_CSI_MIST                           (R_MIPI_CSI_BASE + R_MIPI_CSI_MIST_OFFSET)
#define R_MIPI_CSI_DTEL                           (R_MIPI_CSI_BASE + R_MIPI_CSI_DTEL_OFFSET)
#define R_MIPI_CSI_DTEH                           (R_MIPI_CSI_BASE + R_MIPI_CSI_DTEH_OFFSET)
#define R_MIPI_CSI_RXST                           (R_MIPI_CSI_BASE + R_MIPI_CSI_RXST_OFFSET)
#define R_MIPI_CSI_RXSC                           (R_MIPI_CSI_BASE + R_MIPI_CSI_RXSC_OFFSET)
#define R_MIPI_CSI_RXIE                           (R_MIPI_CSI_BASE + R_MIPI_CSI_RXIE_OFFSET)
#define R_MIPI_CSI_DLST(m)                        (R_MIPI_CSI_BASE + R_MIPI_CSI_DLST_OFFSET(m))
#define R_MIPI_CSI_DLSC(m)                        (R_MIPI_CSI_BASE + R_MIPI_CSI_DLSC_OFFSET(m))
#define R_MIPI_CSI_DLIE(m)                        (R_MIPI_CSI_BASE + R_MIPI_CSI_DLIE_OFFSET(m))
#define R_MIPI_CSI_VCST(m)                        (R_MIPI_CSI_BASE + R_MIPI_CSI_VCST_OFFSET(m))
#define R_MIPI_CSI_VCSC(m)                        (R_MIPI_CSI_BASE + R_MIPI_CSI_VCSC_OFFSET(m))
#define R_MIPI_CSI_VCIE(m)                        (R_MIPI_CSI_BASE + R_MIPI_CSI_VCIE_OFFSET(m))
#define R_MIPI_CSI_PMST                           (R_MIPI_CSI_BASE + R_MIPI_CSI_PMST_OFFSET)
#define R_MIPI_CSI_PMSC                           (R_MIPI_CSI_BASE + R_MIPI_CSI_PMSC_OFFSET)
#define R_MIPI_CSI_PMIE                           (R_MIPI_CSI_BASE + R_MIPI_CSI_PMIE_OFFSET)
#define R_MIPI_CSI_GSCT                           (R_MIPI_CSI_BASE + R_MIPI_CSI_GSCT_OFFSET)
#define R_MIPI_CSI_GSST                           (R_MIPI_CSI_BASE + R_MIPI_CSI_GSST_OFFSET)
#define R_MIPI_CSI_GSSC                           (R_MIPI_CSI_BASE + R_MIPI_CSI_GSSC_OFFSET)
#define R_MIPI_CSI_GSIE                           (R_MIPI_CSI_BASE + R_MIPI_CSI_GSIE_OFFSET)
#define R_MIPI_CSI_GSHT                           (R_MIPI_CSI_BASE + R_MIPI_CSI_GSHT_OFFSET)
#define R_MIPI_CSI_GSIU                           (R_MIPI_CSI_BASE + R_MIPI_CSI_GSIU_OFFSET)

/* Register bit definitions */
/* MCG Register bit definitions */
#define R_MIPI_CSI_MCG_VER_SHIFT                  (0)  /* VERsion of this ip */
#define R_MIPI_CSI_MCG_VER_MASK                   0xf

#define R_MIPI_CSI_MCG_SDLN_SHIFT                 (8)  /* Number of Supported Data Lanes */
#define R_MIPI_CSI_MCG_SDLN_MASK                  0xf00
#  define R_MIPI_CSI_MCG_SDLN_0X2                         (2 << R_MIPI_CSI_MCG_SDLN_SHIFT)  /* Operable with 2 lanes or 1 lane. */

#define R_MIPI_CSI_MCG_GSNM_SHIFT                 (16)  /* NuMber of Generic Short packt FIFO */
#define R_MIPI_CSI_MCG_GSNM_MASK                  0xff0000

/* MCT0 Register bit definitions */
#define R_MIPI_CSI_MCT0_VDLN_SHIFT                (0)  /* Numer of Valid Data Lanes */
#define R_MIPI_CSI_MCT0_VDLN_MASK                 0xf
#  define R_MIPI_CSI_MCT0_VDLN_0X1                        (1 << R_MIPI_CSI_MCT0_VDLN_SHIFT)  /* Operation with one lane */
#  define R_MIPI_CSI_MCT0_VDLN_0X2                        (2 << R_MIPI_CSI_MCT0_VDLN_SHIFT)  /* Operation with two lanes */

#define R_MIPI_CSI_MCT0_ZLMD                      (1 << 16)  /* Zero Length long packet output MoDe */

#define R_MIPI_CSI_MCT0_EDMD                      (1 << 17)  /* ErrframeData notification MoDe */

#define R_MIPI_CSI_MCT0_RVMD                      (1 << 19)  /* ReserVed packet reception MoDe */

#define R_MIPI_CSI_MCT0_GRMD                      (1 << 20)  /* Generic csi-2 Rule MoDe */

#define R_MIPI_CSI_MCT0_ECCV13                    (1 << 24)  /* ECC check csi-2 Ver 1.3 mode */

#define R_MIPI_CSI_MCT0_LFSREN                    (1 << 25)  /* LFSR Enable mode */

/* MCT2 Register bit definitions */
#define R_MIPI_CSI_MCT2_FRRCLK_SHIFT              (0)  /* clock FRequency Rate to judge packet reception end */
#define R_MIPI_CSI_MCT2_FRRCLK_MASK               0x1ff

#define R_MIPI_CSI_MCT2_FRRSKW_SHIFT              (16)  /* clock FRequency Rate to adjust data lane SKew */
#define R_MIPI_CSI_MCT2_FRRSKW_MASK               0x1ff0000

/* MCT3 Register bit definitions */
#define R_MIPI_CSI_MCT3_RXEN                      (1 << 0)  /* RX (reception) Enable */

/* RTCT Register bit definitions */
#define R_MIPI_CSI_RTCT_VSRST                     (1 << 0)  /* Video pixel interface Software ReSeT */

/* RTST Register bit definitions */
#define R_MIPI_CSI_RTST_VSRSTS                    (1 << 0)  /* Video pixel interface Software ReSeT Status */

/* EPCT Register bit definitions */
#define R_MIPI_CSI_EPCT_SLP_SHIFT                 (0)  /* Long Packet Spacers */
#define R_MIPI_CSI_EPCT_SLP_MASK                  0x7fff

#define R_MIPI_CSI_EPCT_EPDOP                     (1 << 15)  /* EPD OPtion select */

#define R_MIPI_CSI_EPCT_SSP_SHIFT                 (16)  /* epd Short Packet Spacers */
#define R_MIPI_CSI_EPCT_SSP_MASK                  0x7fff0000

#define R_MIPI_CSI_EPCT_EPDEN                     (1 << 31)  /* ENable EPD operation */

/* EMCT Register bit definitions */
#define R_MIPI_CSI_EMCT_VLSIEN_SHIFT              (4)  /* ENable Variable-Length Spacer Insertions */
#define R_MIPI_CSI_EMCT_VLSIEN_MASK               0x30
#  define R_MIPI_CSI_EMCT_VLSIEN_00                       (0 << R_MIPI_CSI_EMCT_VLSIEN_SHIFT)  /* Variable length Spacer invalid (Spacer number is fixed length) */
#  define R_MIPI_CSI_EMCT_VLSIEN_01                       (1 << R_MIPI_CSI_EMCT_VLSIEN_SHIFT)  /* Variable length Spacer valid (Spacer number is 1xn/Lane) */
#  define R_MIPI_CSI_EMCT_VLSIEN_10                       (2 << R_MIPI_CSI_EMCT_VLSIEN_SHIFT)  /* Variable length Spacer valid (Spacer number is 2xn/Lane) */
#  define R_MIPI_CSI_EMCT_VLSIEN_11                       (3 << R_MIPI_CSI_EMCT_VLSIEN_SHIFT)  /* Variable length Spacer valid (Spacer number is 4xn/Lane) */

#define R_MIPI_CSI_EMCT_EOTPEN                    (1 << 6)  /* ENable EOTP */

/* MIST Register bit definitions */
#define R_MIPI_CSI_MIST_DL0S                      (1 << 0)  /* interrupt Status related to Data Lane 0 */

#define R_MIPI_CSI_MIST_DL1S                      (1 << 1)  /* interrupt Status related to Data Lane 1 */

#define R_MIPI_CSI_MIST_PMS                       (1 << 8)  /* interrupt Status related to Power Management */

#define R_MIPI_CSI_MIST_GSTS                      (1 << 9)  /* interrupt Status related to Generic ShorT packet */

#define R_MIPI_CSI_MIST_RXS                       (1 << 10)  /* interrupt Status related to RX (Reception) */

#define R_MIPI_CSI_MIST_VC0S                      (1 << 16)  /* interrupt Status related to Vitrtual Channel 0 */

#define R_MIPI_CSI_MIST_VC1S                      (1 << 17)  /* interrupt Status related to Vitrtual Channel 1 */

#define R_MIPI_CSI_MIST_VC2S                      (1 << 18)  /* interrupt Status related to Vitrtual Channel 2 */

#define R_MIPI_CSI_MIST_VC3S                      (1 << 19)  /* interrupt Status related to Vitrtual Channel 3 */

#define R_MIPI_CSI_MIST_VC4S                      (1 << 20)  /* interrupt Status related to Vitrtual Channel 4 */

#define R_MIPI_CSI_MIST_VC5S                      (1 << 21)  /* interrupt Status related to Vitrtual Channel 5 */

#define R_MIPI_CSI_MIST_VC6S                      (1 << 22)  /* interrupt Status related to Vitrtual Channel 6 */

#define R_MIPI_CSI_MIST_VC7S                      (1 << 23)  /* interrupt Status related to Vitrtual Channel 7 */

#define R_MIPI_CSI_MIST_VC8S                      (1 << 24)  /* interrupt Status related to Vitrtual Channel 8 */

#define R_MIPI_CSI_MIST_VC9S                      (1 << 25)  /* interrupt Status related to Vitrtual Channel 9 */

#define R_MIPI_CSI_MIST_VC10S                     (1 << 26)  /* interrupt Status related to Vitrtual Channel 10 */

#define R_MIPI_CSI_MIST_VC11S                     (1 << 27)  /* interrupt Status related to Vitrtual Channel 11 */

#define R_MIPI_CSI_MIST_VC12S                     (1 << 28)  /* interrupt Status related to Vitrtual Channel 12 */

#define R_MIPI_CSI_MIST_VC13S                     (1 << 29)  /* interrupt Status related to Vitrtual Channel 13 */

#define R_MIPI_CSI_MIST_VC14S                     (1 << 30)  /* interrupt Status related to Vitrtual Channel 14 */

#define R_MIPI_CSI_MIST_VC15S                     (1 << 31)  /* interrupt Status related to Vitrtual Channel 15 */

/* DTEL Register bit definitions */
#define R_MIPI_CSI_DTEL_DTEN_SHIFT                (0)  /* Data Type ENable (DT = 0x00 to 0x1F) */
#define R_MIPI_CSI_DTEL_DTEN_MASK                 0xffffffff
#  define R_MIPI_CSI_DTEL_DTEN_0                          (0 << R_MIPI_CSI_DTEL_DTEN_SHIFT)  /* Does not receive data. */
#  define R_MIPI_CSI_DTEL_DTEN_1                          (1 << R_MIPI_CSI_DTEL_DTEN_SHIFT)  /* Receives data. */

/* DTEH Register bit definitions */
#define R_MIPI_CSI_DTEH_DTEN_SHIFT                (0)  /* Data Type ENable (DT = 0x20 to 0x3F) */
#define R_MIPI_CSI_DTEH_DTEN_MASK                 0xffffffff
#  define R_MIPI_CSI_DTEH_DTEN_0                          (0 << R_MIPI_CSI_DTEH_DTEN_SHIFT)  /* Does not receive data. */
#  define R_MIPI_CSI_DTEH_DTEN_1                          (1 << R_MIPI_CSI_DTEH_DTEN_SHIFT)  /* Receives data. */

/* RXST Register bit definitions */
#define R_MIPI_CSI_RXST_FRM0                      (1 << 0)  /* FRaMe of virtual channel 0 active */

#define R_MIPI_CSI_RXST_FRM1                      (1 << 1)  /* FRaMe of virtual channel 1 active */

#define R_MIPI_CSI_RXST_FRM2                      (1 << 2)  /* FRaMe of virtual channel 2 active */

#define R_MIPI_CSI_RXST_FRM3                      (1 << 3)  /* FRaMe of virtual channel 3 active */

#define R_MIPI_CSI_RXST_FRM4                      (1 << 4)  /* FRaMe of virtual channel 4 active */

#define R_MIPI_CSI_RXST_FRM5                      (1 << 5)  /* FRaMe of virtual channel 5 active */

#define R_MIPI_CSI_RXST_FRM6                      (1 << 6)  /* FRaMe of virtual channel 6 active */

#define R_MIPI_CSI_RXST_FRM7                      (1 << 7)  /* FRaMe of virtual channel 7 active */

#define R_MIPI_CSI_RXST_FRM8                      (1 << 8)  /* FRaMe of virtual channel 8 active */

#define R_MIPI_CSI_RXST_FRM9                      (1 << 9)  /* FRaMe of virtual channel 9 active */

#define R_MIPI_CSI_RXST_FRM10                     (1 << 10)  /* FRaMe of virtual channel 10 active */

#define R_MIPI_CSI_RXST_FRM11                     (1 << 11)  /* FRaMe of virtual channel 11 active */

#define R_MIPI_CSI_RXST_FRM12                     (1 << 12)  /* FRaMe of virtual channel 12 active */

#define R_MIPI_CSI_RXST_FRM13                     (1 << 13)  /* FRaMe of virtual channel 13 active */

#define R_MIPI_CSI_RXST_FRM14                     (1 << 14)  /* FRaMe of virtual channel 14 active */

#define R_MIPI_CSI_RXST_FRM15                     (1 << 15)  /* FRaMe of virtual channel 15 active */

#define R_MIPI_CSI_RXST_RACT                      (1 << 16)  /* Rx (Reception) ACTive status */

#define R_MIPI_CSI_RXST_RACTDET                   (1 << 17)  /* Rx (Reception) ACTive DETect */

/* RXSC Register bit definitions */
#define R_MIPI_CSI_RXSC_RACTDETC                  (1 << 17)  /* Rx (Reception) ACTive DETect status Clear */

/* RXIE Register bit definitions */
#define R_MIPI_CSI_RXIE_RACTDETE                  (1 << 17)  /* Rx (Reception) ACTive DETect interrupt Enable */

/* DLST Register bit definitions */
#define R_MIPI_CSI_DLST_ESH                       (1 << 0)  /* ErrSotHs detect on data lane (N) status */

#define R_MIPI_CSI_DLST_ESS                       (1 << 1)  /* ErrSotSynchs detect on data lane (N) status */

#define R_MIPI_CSI_DLST_ECT                       (1 << 2)  /* ErrConTrol detect on data lane (N) status */

#define R_MIPI_CSI_DLST_EES                       (1 << 3)  /* ErrESc detect on data lane (N) status */

#define R_MIPI_CSI_DLST_EUL                       (1 << 16)  /* Exit from ULps detect on data lane (N) status */

#define R_MIPI_CSI_DLST_RUL                       (1 << 17)  /* entry to ULps detect on data lane (N) status */

#define R_MIPI_CSI_DLST_ULP                       (1 << 24)  /* rxULPsesc of data lane (N) status */

/* DLSC Register bit definitions */
#define R_MIPI_CSI_DLSC_ESHC                      (1 << 0)  /* ErrSotHs detect on data lane (N) status Clear */

#define R_MIPI_CSI_DLSC_ESSC                      (1 << 1)  /* ErrSotSynchs detect on data lane (N) status Clear */

#define R_MIPI_CSI_DLSC_ECTC                      (1 << 2)  /* ErrConTrol detect on data lane (N) status Clear */

#define R_MIPI_CSI_DLSC_EESC                      (1 << 3)  /* ErrESc detect on data lane (N) status Clear */

#define R_MIPI_CSI_DLSC_EULC                      (1 << 16)  /* Exit from ULps detect on data lane (N) status Clear */

#define R_MIPI_CSI_DLSC_RULC                      (1 << 17)  /* Entry to ULps detect on data lane (N) status Clear */

/* DLIE Register bit definitions */
#define R_MIPI_CSI_DLIE_ESHE                      (1 << 0)  /* ErrSotHs detect on data lane (N) interrupt Enable */

#define R_MIPI_CSI_DLIE_ESSE                      (1 << 1)  /* ErrSotSynchs detect on data lane (N) interrupt Enable */

#define R_MIPI_CSI_DLIE_ECTE                      (1 << 2)  /* ErrConTrol detect on data lane (N) interrupt Enable */

#define R_MIPI_CSI_DLIE_EESE                      (1 << 3)  /* ErrESc detect on data lane (N) interrupt Enable */

#define R_MIPI_CSI_DLIE_EULE                      (1 << 16)  /* Exit to ULps detect on data lane (N) interrupt Enable */

#define R_MIPI_CSI_DLIE_RULE                      (1 << 17)  /* Entry to ULps detect on data lane (N) interrupt Enable */

/* VCST Register bit definitions */
#define R_MIPI_CSI_VCST_MLF                       (1 << 0)  /* MaLFormed packet with virtual channel (M) detect status */

#define R_MIPI_CSI_VCST_ECD                       (1 << 1)  /* ECc 2-bit (Double) error packet with virtual channel (M) Detect status */

#define R_MIPI_CSI_VCST_CRC                       (1 << 2)  /* CRC error packet with virtual channel (M) detect status */

#define R_MIPI_CSI_VCST_IDE                       (1 << 3)  /* ErrID packet with virtual channel (M) detect status */

#define R_MIPI_CSI_VCST_WCE                       (1 << 4)  /* Word Count Error packet with virtual channel (M) detect status */

#define R_MIPI_CSI_VCST_ECC                       (1 << 5)  /* ECc 1-bit error (Corrected) packet with virtual channel (M) detect status */

#define R_MIPI_CSI_VCST_ECN                       (1 << 6)  /* ECc No-error packet with virtual channel (M) detect status */

#define R_MIPI_CSI_VCST_FRS                       (1 << 8)  /* errFRameSync of virtual channel (M) detect status */

#define R_MIPI_CSI_VCST_FRD                       (1 << 9)  /* errFRameData of virtual channel (M) detect status */

#define R_MIPI_CSI_VCST_OVF                       (1 << 16)  /* generic short packet with virtual channel (M) discard by fifo OVerFlow status */

#define R_MIPI_CSI_VCST_FSR                       (1 << 24)  /* Frame Start packet with virtual channel (M) Reception status */

#define R_MIPI_CSI_VCST_FER                       (1 << 25)  /* Frame End packet with virtual channel (M) Reception status */

#define R_MIPI_CSI_VCST_LSR                       (1 << 26)  /* Line Start packet with virtual channel (M) Reception status */

#define R_MIPI_CSI_VCST_LER                       (1 << 27)  /* Line End packet with virtual channel (M) Reception status */

#define R_MIPI_CSI_VCST_ETR                       (1 << 28)  /* EoTp packet with virtual channel (M) Reception status */

/* VCSC Register bit definitions */
#define R_MIPI_CSI_VCSC_MLFC                      (1 << 0)  /* MaLFormed packet with virtual channel (M) detect status Clear */

#define R_MIPI_CSI_VCSC_ECDC                      (1 << 1)  /* ECc 2-bit (Double) error packet with virtual channel (M) Detect status Clear */

#define R_MIPI_CSI_VCSC_CRCC                      (1 << 2)  /* CRC error packet with virtual channel (M) detect status Clear */

#define R_MIPI_CSI_VCSC_IDEC                      (1 << 3)  /* ErrID packet with virtual channel (M) detect status Clear */

#define R_MIPI_CSI_VCSC_WCEC                      (1 << 4)  /* Word Count Error packet with virtual channel (M) detect status Clear */

#define R_MIPI_CSI_VCSC_ECCC                      (1 << 5)  /* ECc 1-bit error (Corrected) packet with virtual channel (M) detect status Clear */

#define R_MIPI_CSI_VCSC_ECNC                      (1 << 6)  /* ECc No-error packet with virtual channel (M) detect status Clear */

#define R_MIPI_CSI_VCSC_FRSC                      (1 << 8)  /* errFRameSync of virtual channel (M) detect status Clear */

#define R_MIPI_CSI_VCSC_FRDC                      (1 << 9)  /* errFRameData of virtual channel (M) detect status Clear */

#define R_MIPI_CSI_VCSC_AMLFC                     (1 << 14)  /* MaLFormed packet with any virtual channels detect status Clear */

#define R_MIPI_CSI_VCSC_AECDC                     (1 << 15)  /* ECc 2-bit (Double) error packet with any virtual channels Detect status Clear */

#define R_MIPI_CSI_VCSC_OVFC                      (1 << 16)  /* generic short packet with virtual channel (M) discard by fifo OVerFlow status Clear */

#define R_MIPI_CSI_VCSC_FSRC                      (1 << 24)  /* Frame Start packet with virtual channel (M) Reception status Clear */

#define R_MIPI_CSI_VCSC_FERC                      (1 << 25)  /* Frame End packet with virtual channel (M) Reception status Clear */

#define R_MIPI_CSI_VCSC_LSRC                      (1 << 26)  /* Line Start packet with virtual channel (M) Reception status Clear */

#define R_MIPI_CSI_VCSC_LERC                      (1 << 27)  /* Line End packet with virtual channel (M) Reception status Clear */

#define R_MIPI_CSI_VCSC_ETRC                      (1 << 28)  /* EoTp packet with virtual channel (M) Reception status Clear */

/* VCIE Register bit definitions */
#define R_MIPI_CSI_VCIE_MLFE                      (1 << 0)  /* MaLFormed packet with virtual channel (M) detect interrupt Enable */

#define R_MIPI_CSI_VCIE_ECDE                      (1 << 1)  /* ECc 2-bit (Double) error packet with virtual channel (M) Detect interrupt Enable */

#define R_MIPI_CSI_VCIE_CRCE                      (1 << 2)  /* CRC error packet with virtual channel (M) detect interrupt Enable */

#define R_MIPI_CSI_VCIE_IDEE                      (1 << 3)  /* ErrID packet with virtual channel (M) detect interrupt Enable */

#define R_MIPI_CSI_VCIE_WCEE                      (1 << 4)  /* Word Count Error packet with virtual channel (M) detect interrupt Enable */

#define R_MIPI_CSI_VCIE_ECCE                      (1 << 5)  /* ECc 1-bit error (Corrected) packet with virtual channel (M) detect interrupt Enable */

#define R_MIPI_CSI_VCIE_ECNE                      (1 << 6)  /* ECc No-error packet with virtual channel (M) detect interrupt Enable */

#define R_MIPI_CSI_VCIE_FRSE                      (1 << 8)  /* errFRameSync of virtual channel (M) detect interrupt Enable */

#define R_MIPI_CSI_VCIE_FRDE                      (1 << 9)  /* errFRameData of virtual channel (M) detect interrupt Enable */

#define R_MIPI_CSI_VCIE_OVFE                      (1 << 16)  /* generic short packet with virtual channel (M) discard by fifo OVerFlow interrupt Enable */

#define R_MIPI_CSI_VCIE_FSRE                      (1 << 24)  /* Frame Start packet with virtual channel (M) Reception interrupt Enable */

#define R_MIPI_CSI_VCIE_FERE                      (1 << 25)  /* Frame End packet with virtual channel (M) Reception interrupt Enable */

#define R_MIPI_CSI_VCIE_LSRE                      (1 << 26)  /* Line Start packet with virtual channel (M) Reception interrupt Enable */

#define R_MIPI_CSI_VCIE_LERE                      (1 << 27)  /* Line End packet with virtual channel (M) Reception interrupt Enable */

#define R_MIPI_CSI_VCIE_ETRE                      (1 << 28)  /* EoTp packet with virtual channel (M) Reception interrupt Enable */

/* PMST Register bit definitions */
#define R_MIPI_CSI_PMST_DSX                       (1 << 0)  /* eXit from Stop state detect on all valid Data lanes status */

#define R_MIPI_CSI_PMST_DSN                       (1 << 1)  /* eNtry to Stop state detect on all valid Data lanes status */

#define R_MIPI_CSI_PMST_CSX                       (1 << 2)  /* eXit from Stop state detect on Clock lane status */

#define R_MIPI_CSI_PMST_CSN                       (1 << 3)  /* eNtry to Stop state detect on Clock lane status */

#define R_MIPI_CSI_PMST_DUX                       (1 << 4)  /* eXit from Ulps detect on all valid Data lanes status */

#define R_MIPI_CSI_PMST_DUN                       (1 << 5)  /* eNtry to Ulps detect on all valid Data lanes status */

#define R_MIPI_CSI_PMST_CUX                       (1 << 6)  /* eXit frum Ulps detect on Clock lane status */

#define R_MIPI_CSI_PMST_CUN                       (1 << 7)  /* eNtry to Ulps detect on Clock lane status */

#define R_MIPI_CSI_PMST_CLSS                      (1 << 14)  /* Stop State of Clock Lane status */

#define R_MIPI_CSI_PMST_CLUL                      (1 << 15)  /* rxULpsclknot (inverted) of Clock Lane status */

#define R_MIPI_CSI_PMST_DLSS_SHIFT                (16)  /* Stop State of Data Lanes status */
#define R_MIPI_CSI_PMST_DLSS_MASK                 0x30000
#  define R_MIPI_CSI_PMST_DLSS_0                          (0 << R_MIPI_CSI_PMST_DLSS_SHIFT)  /* Stop state of lane 0 */
#  define R_MIPI_CSI_PMST_DLSS_1                          (1 << R_MIPI_CSI_PMST_DLSS_SHIFT)  /* Stop state of lane 1 */

#define R_MIPI_CSI_PMST_DLUL_SHIFT                (24)  /* rxULpsesc of Data Lanes status */
#define R_MIPI_CSI_PMST_DLUL_MASK                 0x3000000
#  define R_MIPI_CSI_PMST_DLUL_0                          (0 << R_MIPI_CSI_PMST_DLUL_SHIFT)  /* RxUlpsEsc of lane 0 */
#  define R_MIPI_CSI_PMST_DLUL_1                          (1 << R_MIPI_CSI_PMST_DLUL_SHIFT)  /* RxUlpsEsc of lane 1 */

/* PMSC Register bit definitions */
#define R_MIPI_CSI_PMSC_DSXC                      (1 << 0)  /* eXit from Stop state detect on all valid Data lanes status Clear */

#define R_MIPI_CSI_PMSC_DSNC                      (1 << 1)  /* eNtry to Stop state detect on all valid Data lanes status Clear */

#define R_MIPI_CSI_PMSC_CSXC                      (1 << 2)  /* eXit from Stop state detect on Clock lane status Clear */

#define R_MIPI_CSI_PMSC_CSNC                      (1 << 3)  /* eNtry to Stop state detect on Clock lane status Clear */

#define R_MIPI_CSI_PMSC_DUXC                      (1 << 4)  /* eXit from Ulps detect on all valid Data lanes status Clear */

#define R_MIPI_CSI_PMSC_DUNC                      (1 << 5)  /* eNtry to Ulps detect on all valid Data lanes status Clear */

#define R_MIPI_CSI_PMSC_CUXC                      (1 << 6)  /* eXit frum Ulps detect on Clock lane status Clear */

#define R_MIPI_CSI_PMSC_CUNC                      (1 << 7)  /* eNtry to Ulps detect on Clock lane status Clear */

/* PMIE Register bit definitions */
#define R_MIPI_CSI_PMIE_DSXE                      (1 << 0)  /* eXit from Stop state detect on all valid Data lanes interrupt Enable */

#define R_MIPI_CSI_PMIE_DSNE                      (1 << 1)  /* eNtry to Stop state detect on all valid Data lanes interrupt Enable */

#define R_MIPI_CSI_PMIE_CSXE                      (1 << 2)  /* eXit from Stop state detect on Clock lane interrupt Enable */

#define R_MIPI_CSI_PMIE_CSNE                      (1 << 3)  /* eNtry to Stop state detect on Clock lane interrupt Enable */

#define R_MIPI_CSI_PMIE_DUXE                      (1 << 4)  /* eXit from Ulps detect on all valid Data lanes interrupt Enable */

#define R_MIPI_CSI_PMIE_DUNE                      (1 << 5)  /* eNtry to Ulps detect on all valid Data lanes interrupt Enable */

#define R_MIPI_CSI_PMIE_CUXE                      (1 << 6)  /* eXit from Ulps detect on Clock lane interrupt Enable */

#define R_MIPI_CSI_PMIE_CUNE                      (1 << 7)  /* eNtry to Ulps detect on Clock lane interrupt Enable */

/* GSCT Register bit definitions */
#define R_MIPI_CSI_GSCT_SHTH_SHIFT                (0)  /* Stored generic short packet THreshold */
#define R_MIPI_CSI_GSCT_SHTH_MASK                 0x7f

#define R_MIPI_CSI_GSCT_GFIF                      (1 << 16)  /* Generic short packet store in FIFo */

/* GSST Register bit definitions */
#define R_MIPI_CSI_GSST_GNE                       (1 << 0)  /* Generic short packet fifo Not Empty */

#define R_MIPI_CSI_GSST_GTH                       (1 << 1)  /* more than THreshold Generic short packets existed in fifo */

#define R_MIPI_CSI_GSST_GOV                       (1 << 4)  /* Generic short packet fifo OVerflow status */

#define R_MIPI_CSI_GSST_PNUM_SHIFT                (8)  /* NUMber of stored generic short Packets in fifo */
#define R_MIPI_CSI_GSST_PNUM_MASK                 0xff00

#define R_MIPI_CSI_GSST_GCD                       (1 << 16)  /* Generic short packet fifo Clear status */

#define R_MIPI_CSI_GSST_STRDS                     (1 << 17)  /* generic short packet SToRe DiSable */

/* GSSC Register bit definitions */
#define R_MIPI_CSI_GSSC_GOVC                      (1 << 4)  /* Generic short packet fifo OVerflow status Clear */

/* GSIE Register bit definitions */
#define R_MIPI_CSI_GSIE_GNEE                      (1 << 0)  /* Generic short packet fifo Not Empty interrupt Enable */

#define R_MIPI_CSI_GSIE_GTHE                      (1 << 1)  /* more than THreshold Generic short packets existed in fifo interrupt Enable */

#define R_MIPI_CSI_GSIE_GOVE                      (1 << 4)  /* Generic short packet fifo OVerflow interrupt Enable */

/* GSHT Register bit definitions */
#define R_MIPI_CSI_GSHT_SPDT_SHIFT                (0)  /* Stored Packet DaTa */
#define R_MIPI_CSI_GSHT_SPDT_MASK                 0xffff

#define R_MIPI_CSI_GSHT_DTYP_SHIFT                (16)  /* Stored packet Data TYPe */
#define R_MIPI_CSI_GSHT_DTYP_MASK                 0x3f0000

#define R_MIPI_CSI_GSHT_SPVC_SHIFT                (24)  /* Stored Packet Virtual Channel */
#define R_MIPI_CSI_GSHT_SPVC_MASK                 0xf000000

/* GSIU Register bit definitions */
#define R_MIPI_CSI_GSIU_FINC                      (1 << 0)  /* generic short packet Fifo update (INCrement internal pointer) */

#define R_MIPI_CSI_GSIU_GFCLR                     (1 << 8)  /* Generic short packet Fifo CLeaR */

#define R_MIPI_CSI_GSIU_GFEN                      (1 << 16)  /* Generic short packet Fifo ENable */


/* Maximum number of channels */

#define MIPI_CSI_MAX_CHANNELS    16

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MIPI_CSI_H */

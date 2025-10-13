/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_vin.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_VIN_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_VIN_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* VIN Base Address */
#ifndef R_VIN_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_VIN_BASE           0x40347400
#else
#define R_VIN_BASE           0x50347400
#endif
#endif

/* VIN Register Offsets */

#define R_VIN_MC_OFFSET     0x00000000  /* Main Control Register */
#define R_VIN_MS_OFFSET     0x00000004  /* Module Status Register */
#define R_VIN_FC_OFFSET     0x00000008  /* Frame Capture Register */
#define R_VIN_SLPRC_OFFSET     0x0000000c  /* Start Line Pre-Clip Register */
#define R_VIN_ELPRC_OFFSET     0x00000010  /* End Line Pre-Clip Register */
#define R_VIN_SPPRC_OFFSET     0x00000014  /* Start Pixel Pre-Clip Register */
#define R_VIN_EPPRC_OFFSET     0x00000018  /* End Pixel Pre-Clip Register */
#define R_VIN_CSI_IFMD_OFFSET     0x00000020  /* CSI2 Interface Mode Register */
#define R_VIN_CSIFLD_OFFSET     0x00000024  /* Field Detection Control Register */
#define R_VIN_IS_OFFSET     0x0000002c  /* Image Stride Register */
#define R_VIN_MB1_OFFSET     0x00000030  /* Memory Base 1 Register */
#define R_VIN_MB2_OFFSET     0x00000034  /* Memory Base 2 Register */
#define R_VIN_MB3_OFFSET     0x00000038  /* Memory Base 3 Register */
#define R_VIN_LC_OFFSET     0x0000003c  /* Line Count Register */
#define R_VIN_IE_OFFSET     0x00000040  /* Interrupt Enable Register */
#define R_VIN_INTS_OFFSET     0x00000044  /* Interrupt Status Register */
#define R_VIN_SI_OFFSET     0x00000048  /* Scanline Interrupt Register */
#define R_VIN_MTCSTOP_OFFSET     0x00000054  /* AXI Transfer Stop Control Register */
#define R_VIN_DMR_OFFSET     0x00000058  /* Data Mode Register */
#define R_VIN_UVAOF_OFFSET     0x00000060  /* UV Address Offset Register */
#define R_VIN_UDS_CTRL_OFFSET     0x00000080  /* Scaling Control Registers */
#define R_VIN_UDS_SCALE_OFFSET     0x00000084  /* Scaling Factor Registers */
#define R_VIN_UDS_PASS_BWIDTH_OFFSET     0x00000090  /* Passband Registers */
#define R_VIN_UDS_CLIP_SIZE_OFFSET     0x000000a4  /* UDS Output Size Clipping Registers */
#define R_VIN_LUTP_OFFSET     0x00000100  /* Lookup Table Pointer Register */
#define R_VIN_LUTD_OFFSET     0x00000104  /* Lookup Table Data Register */
#define R_VIN_YCCR1_OFFSET     0x00000228  /* RGB to Y Calculation Setting Register 1 */
#define R_VIN_YCCR2_OFFSET     0x0000022c  /* RGB to Y Calculation Setting Register 2 */
#define R_VIN_YCCR3_OFFSET     0x00000230  /* RGB to Y Calculation Setting Register 3 */
#define R_VIN_CBCCR1_OFFSET     0x00000234  /* RGB to Cb Calculation Setting Register 1 */
#define R_VIN_CBCCR2_OFFSET     0x00000238  /* RGB to Cb Calculation Setting Register 2 */
#define R_VIN_CBCCR3_OFFSET     0x0000023c  /* RGB to Cb Calculation Setting Register 3 */
#define R_VIN_CRCCR1_OFFSET     0x00000240  /* RGB to Cr Calculation Setting Register 1 */
#define R_VIN_CRCCR2_OFFSET     0x00000244  /* RGB to Cr Calculation Setting Register 2 */
#define R_VIN_CRCCR3_OFFSET     0x00000248  /* RGB to Cr Calculation Setting Register 3 */
#define R_VIN_CSCE1_OFFSET     0x00000300  /* YC to RGB Calculation Setting Extension Register 1 */
#define R_VIN_CSCE2_OFFSET     0x00000304  /* YC to RGB Calculation Setting Extension Register 2 */
#define R_VIN_CSCE3_OFFSET     0x00000308  /* YC to RGB Calculation Setting Extension Register 3 */
#define R_VIN_CSCE4_OFFSET     0x0000030c  /* YC to RGB Calculation Setting Extension Register 4 */

/* VIN Register Addresses */

#define R_VIN_MC                 (R_VIN_BASE + R_VIN_MC_OFFSET)
#define R_VIN_MS                 (R_VIN_BASE + R_VIN_MS_OFFSET)
#define R_VIN_FC                 (R_VIN_BASE + R_VIN_FC_OFFSET)
#define R_VIN_SLPRC                 (R_VIN_BASE + R_VIN_SLPRC_OFFSET)
#define R_VIN_ELPRC                 (R_VIN_BASE + R_VIN_ELPRC_OFFSET)
#define R_VIN_SPPRC                 (R_VIN_BASE + R_VIN_SPPRC_OFFSET)
#define R_VIN_EPPRC                 (R_VIN_BASE + R_VIN_EPPRC_OFFSET)
#define R_VIN_CSI_IFMD                 (R_VIN_BASE + R_VIN_CSI_IFMD_OFFSET)
#define R_VIN_CSIFLD                 (R_VIN_BASE + R_VIN_CSIFLD_OFFSET)
#define R_VIN_IS                 (R_VIN_BASE + R_VIN_IS_OFFSET)
#define R_VIN_MB1                 (R_VIN_BASE + R_VIN_MB1_OFFSET)
#define R_VIN_MB2                 (R_VIN_BASE + R_VIN_MB2_OFFSET)
#define R_VIN_MB3                 (R_VIN_BASE + R_VIN_MB3_OFFSET)
#define R_VIN_LC                 (R_VIN_BASE + R_VIN_LC_OFFSET)
#define R_VIN_IE                 (R_VIN_BASE + R_VIN_IE_OFFSET)
#define R_VIN_INTS                 (R_VIN_BASE + R_VIN_INTS_OFFSET)
#define R_VIN_SI                 (R_VIN_BASE + R_VIN_SI_OFFSET)
#define R_VIN_MTCSTOP                 (R_VIN_BASE + R_VIN_MTCSTOP_OFFSET)
#define R_VIN_DMR                 (R_VIN_BASE + R_VIN_DMR_OFFSET)
#define R_VIN_UVAOF                 (R_VIN_BASE + R_VIN_UVAOF_OFFSET)
#define R_VIN_UDS_CTRL                 (R_VIN_BASE + R_VIN_UDS_CTRL_OFFSET)
#define R_VIN_UDS_SCALE                 (R_VIN_BASE + R_VIN_UDS_SCALE_OFFSET)
#define R_VIN_UDS_PASS_BWIDTH                 (R_VIN_BASE + R_VIN_UDS_PASS_BWIDTH_OFFSET)
#define R_VIN_UDS_CLIP_SIZE                 (R_VIN_BASE + R_VIN_UDS_CLIP_SIZE_OFFSET)
#define R_VIN_LUTP                 (R_VIN_BASE + R_VIN_LUTP_OFFSET)
#define R_VIN_LUTD                 (R_VIN_BASE + R_VIN_LUTD_OFFSET)
#define R_VIN_YCCR1                 (R_VIN_BASE + R_VIN_YCCR1_OFFSET)
#define R_VIN_YCCR2                 (R_VIN_BASE + R_VIN_YCCR2_OFFSET)
#define R_VIN_YCCR3                 (R_VIN_BASE + R_VIN_YCCR3_OFFSET)
#define R_VIN_CBCCR1                 (R_VIN_BASE + R_VIN_CBCCR1_OFFSET)
#define R_VIN_CBCCR2                 (R_VIN_BASE + R_VIN_CBCCR2_OFFSET)
#define R_VIN_CBCCR3                 (R_VIN_BASE + R_VIN_CBCCR3_OFFSET)
#define R_VIN_CRCCR1                 (R_VIN_BASE + R_VIN_CRCCR1_OFFSET)
#define R_VIN_CRCCR2                 (R_VIN_BASE + R_VIN_CRCCR2_OFFSET)
#define R_VIN_CRCCR3                 (R_VIN_BASE + R_VIN_CRCCR3_OFFSET)
#define R_VIN_CSCE1                 (R_VIN_BASE + R_VIN_CSCE1_OFFSET)
#define R_VIN_CSCE2                 (R_VIN_BASE + R_VIN_CSCE2_OFFSET)
#define R_VIN_CSCE3                 (R_VIN_BASE + R_VIN_CSCE3_OFFSET)
#define R_VIN_CSCE4                 (R_VIN_BASE + R_VIN_CSCE4_OFFSET)

/* Register bit definitions */
/* MC Register bit definitions */
#define R_VIN_MC_ME                               (1 << 0)  /* Module Enable */

#define R_VIN_MC_BPS                              (1 << 1)  /* Color Space Conversion Bypass Mode */

#define R_VIN_MC_IM_SHIFT                         (3)  /* Interlace Mode */
#define R_VIN_MC_IM_MASK                          0x18
#  define R_VIN_MC_IM_00                                  (0 << R_VIN_MC_IM_SHIFT)  /* Odd-field (field 1) capture mode Handles only odd fields as frames and stores them in external memory.  */
#  define R_VIN_MC_IM_01                                  (1 << R_VIN_MC_IM_SHIFT)  /* Odd-/even-field capture mode Handles odd and even fields as separate frames and stores them in external memory. This mode is available only in continuous frame capture mode. For progressive input and continuous frame capture mode, set 01b.  */
#  define R_VIN_MC_IM_10                                  (2 << R_VIN_MC_IM_SHIFT)  /* Even-field (field 2) capture mode Handles only even fields as frames and stores them in external memory.  */
#  define R_VIN_MC_IM_11                                  (3 << R_VIN_MC_IM_SHIFT)  /* Setting prohibited */

#define R_VIN_MC_EN                               (1 << 6)  /* Endian Type */

#define R_VIN_MC_DC_SHIFT                         (14)  /* Dithering Mode Control */
#define R_VIN_MC_DC_MASK                          0xc000
#  define R_VIN_MC_DC_00                                  (0 << R_VIN_MC_DC_SHIFT)  /* Dithering with cumulative addition */
#  define R_VIN_MC_DC_01                                  (1 << R_VIN_MC_DC_SHIFT)  /* Ordered dithering 1 */
#  define R_VIN_MC_DC_10                                  (2 << R_VIN_MC_DC_SHIFT)  /* Setting prohibited */
#  define R_VIN_MC_DC_11                                  (3 << R_VIN_MC_DC_SHIFT)  /* Ordered dithering 2 */

#define R_VIN_MC_INF_SHIFT                        (16)  /* Input Interface Format */
#define R_VIN_MC_INF_MASK                         0x70000
#  define R_VIN_MC_INF_000                                (0 << R_VIN_MC_INF_SHIFT)  /* Setting prohibited */
#  define R_VIN_MC_INF_001                                (1 << R_VIN_MC_INF_SHIFT)  /* 8-bit YCbCr-422 */
#  define R_VIN_MC_INF_010                                (2 << R_VIN_MC_INF_SHIFT)  /* Setting prohibited */
#  define R_VIN_MC_INF_011                                (3 << R_VIN_MC_INF_SHIFT)  /* 10-bit YCbCr-422 */
#  define R_VIN_MC_INF_100                                (4 << R_VIN_MC_INF_SHIFT)  /* 8-bit user defined data (RAW8) */
#  define R_VIN_MC_INF_101                                (5 << R_VIN_MC_INF_SHIFT)  /* Setting prohibited */
#  define R_VIN_MC_INF_110                                (6 << R_VIN_MC_INF_SHIFT)  /* 24-bit RGB-888 */
#  define R_VIN_MC_INF_111                                (7 << R_VIN_MC_INF_SHIFT)  /* Setting prohibited */

#define R_VIN_MC_LUTE                             (1 << 20)  /* Lookup Table Enable */

#define R_VIN_MC_ST                               (1 << 22)  /* Initialization control at STartup */

#define R_VIN_MC_DC2                              (1 << 24)  /* Dithering mode Control 2 */

#define R_VIN_MC_YUV444                           (1 << 25)  /* YUV444 conversion */

#define R_VIN_MC_SCLE                             (1 << 26)  /* This bit is used to enable or disable scaling by the UDS. */

#define R_VIN_MC_CLP_SHIFT                        (28)  /* Pixel Data Clipping */
#define R_VIN_MC_CLP_MASK                         0x30000000

/* MS Register bit definitions */
#define R_VIN_MS_CA                               (1 << 0)  /* Video Capture Active Status */

#define R_VIN_MS_AV                               (1 << 1)  /* Active Video Status */

#define R_VIN_MS_FS                               (1 << 2)  /* Field Status */

#define R_VIN_MS_FBS_SHIFT                        (3)  /* Frame Buffer Status */
#define R_VIN_MS_FBS_MASK                         0x18
#  define R_VIN_MS_FBS_00                                 (0 << R_VIN_MS_FBS_SHIFT)  /* The latest valid frame buffer has the base address defined by the memory base 1 register. */
#  define R_VIN_MS_FBS_01                                 (1 << R_VIN_MS_FBS_SHIFT)  /* The latest valid frame buffer has the base address defined by the memory base 2 register. */
#  define R_VIN_MS_FBS_10                                 (2 << R_VIN_MS_FBS_SHIFT)  /* The latest valid frame buffer has the base address defined by the memory base 3 register. */
#  define R_VIN_MS_FBS_11                                 (3 << R_VIN_MS_FBS_SHIFT)  /* There is no valid frame buffer. */

#define R_VIN_MS_MA                               (1 << 16)  /* External frame Memory capture Active status */

#define R_VIN_MS_FMS_SHIFT                        (19)  /* External Frame Memory buffer Status */
#define R_VIN_MS_FMS_MASK                         0x180000
#  define R_VIN_MS_FMS_00                                 (0 << R_VIN_MS_FMS_SHIFT)  /* The latest valid frame buffer has the base address defined by the memory base 1 register. */
#  define R_VIN_MS_FMS_01                                 (1 << R_VIN_MS_FMS_SHIFT)  /* The latest valid frame buffer has the base address defined by the memory base 2 register. */
#  define R_VIN_MS_FMS_10                                 (2 << R_VIN_MS_FMS_SHIFT)  /* The latest valid frame buffer has the base address defined by the memory base 3 register. */
#  define R_VIN_MS_FMS_11                                 (3 << R_VIN_MS_FMS_SHIFT)  /* There is no valid frame buffer. */

/* FC Register bit definitions */
#define R_VIN_FC_CC                               (1 << 1)  /* Continuous Frame Capture Mode */

/* SLPRC Register bit definitions */
#define R_VIN_SLPRC_SLPRC_SHIFT                   (0)  /* Start Line PRe-Clip */
#define R_VIN_SLPRC_SLPRC_MASK                    0xfff

/* ELPRC Register bit definitions */
#define R_VIN_ELPRC_ELPRC_SHIFT                   (0)  /* End Line PRe-Clip */
#define R_VIN_ELPRC_ELPRC_MASK                    0xfff

/* SPPRC Register bit definitions */
#define R_VIN_SPPRC_SPPRC_SHIFT                   (0)  /* Start Pixel Pre-Clip */
#define R_VIN_SPPRC_SPPRC_MASK                    0xfff

/* EPPRC Register bit definitions */
#define R_VIN_EPPRC_EPPRC_SHIFT                   (0)  /* End Pixel PRe-Clip */
#define R_VIN_EPPRC_EPPRC_MASK                    0xfff

/* CSI_IFMD Register bit definitions */
#define R_VIN_CSI_IFMD_VC_SEL_SHIFT               (0)  /* Virtual Channel SELect */
#define R_VIN_CSI_IFMD_VC_SEL_MASK                0xf

#define R_VIN_CSI_IFMD_DT_SHIFT                   (8)  /* Data Type select */
#define R_VIN_CSI_IFMD_DT_MASK                    0x3f00
#  define R_VIN_CSI_IFMD_DT_0X1E                          (0 << R_VIN_CSI_IFMD_DT_SHIFT)  /* YUV422 8-bit */
#  define R_VIN_CSI_IFMD_DT_0X1F                          (0 << R_VIN_CSI_IFMD_DT_SHIFT)  /* YUV422 10-bit */
#  define R_VIN_CSI_IFMD_DT_0X24                          (0 << R_VIN_CSI_IFMD_DT_SHIFT)  /* RGB888 */
#  define R_VIN_CSI_IFMD_DT_0X2A                          (0 << R_VIN_CSI_IFMD_DT_SHIFT)  /* RAW 8-bit */

#define R_VIN_CSI_IFMD_DES0                       (1 << 25)  /* Data Extension Select */

/* CSIFLD Register bit definitions */
#define R_VIN_CSIFLD_FLD_EN                       (1 << 0)  /* FieLD detect ENable */

#define R_VIN_CSIFLD_FLD_SEL_SHIFT                (4)  /* even FieLD DETect SELect */
#define R_VIN_CSIFLD_FLD_SEL_MASK                 0x30
#  define R_VIN_CSIFLD_FLD_SEL_00                         (0 << R_VIN_CSIFLD_FLD_SEL_SHIFT)  /* Setting is prohibited. */
#  define R_VIN_CSIFLD_FLD_SEL_01                         (1 << R_VIN_CSIFLD_FLD_SEL_SHIFT)  /* When FLD_NUM matches the field number [0] bit, the field is detected as an even field. */
#  define R_VIN_CSIFLD_FLD_SEL_10                         (2 << R_VIN_CSIFLD_FLD_SEL_SHIFT)  /* Setting is prohibited. */
#  define R_VIN_CSIFLD_FLD_SEL_11                         (3 << R_VIN_CSIFLD_FLD_SEL_SHIFT)  /* Setting is prohibited. */

#define R_VIN_CSIFLD_FLD_NUM                      (1 << 16)  /* even FieLD NUMber setting */

/* IS Register bit definitions */
#define R_VIN_IS_IS_SHIFT                         (0)  /* Image Stride (Setting unit: pixel) */
#define R_VIN_IS_IS_MASK                          0x1fff

/* MB1 Register bit definitions */
#define R_VIN_MB1_MB1_SHIFT                       (7)  /* Memory Base Address 1 */
#define R_VIN_MB1_MB1_MASK                        0xffffff80

/* MB2 Register bit definitions */
#define R_VIN_MB2_MB2_SHIFT                       (7)  /* Memory Base Address 2 */
#define R_VIN_MB2_MB2_MASK                        0xffffff80

/* MB3 Register bit definitions */
#define R_VIN_MB3_MB3_SHIFT                       (7)  /* Memory Base Address 3 */
#define R_VIN_MB3_MB3_MASK                        0xffffff80

/* LC Register bit definitions */
#define R_VIN_LC_LC_SHIFT                         (0)  /* Line Count */
#define R_VIN_LC_LC_MASK                          0xfff

/* IE Register bit definitions */
#define R_VIN_IE_FOE                              (1 << 0)  /* FIFO Overflow Interrupt Enable */

#define R_VIN_IE_EFE                              (1 << 1)  /* End of Frame Interrupt Enable */

#define R_VIN_IE_SIE                              (1 << 2)  /* Scanline Interrupt Enable */

#define R_VIN_IE_FIE                              (1 << 4)  /* Field Interrupt Enable */

#define R_VIN_IE_FME                              (1 << 5)  /* Frame Memory write completion interrupt Enable */

#define R_VIN_IE_PRCLIPHEE                        (1 << 8)  /* PRCLIPH Error interrupt Enable */

#define R_VIN_IE_PRCLIPVEE                        (1 << 9)  /* PRCLIPV Error interrupt Enable */

#define R_VIN_IE_ROE                              (1 << 14)  /* Response Overflow interrupt Enable */

#define R_VIN_IE_AREE                             (1 << 15)  /* Axi Resp Error interrupt Enable */

#define R_VIN_IE_VRE                              (1 << 16)  /* VSYNC Deasserting Detect Interrupt Enable */

#define R_VIN_IE_VFE                              (1 << 17)  /* Vsync asserting detect interrupt Enable */

#define R_VIN_IE_FIE2                             (1 << 31)  /* Field Interrupt Enable 2 */

/* INTS Register bit definitions */
#define R_VIN_INTS_FOS                            (1 << 0)  /* FIFO Overflow Interrupt Status */

#define R_VIN_INTS_EFS                            (1 << 1)  /* End of Frame Interrupt Status */

#define R_VIN_INTS_SIS                            (1 << 2)  /* Scanline Interrupt Status */

#define R_VIN_INTS_FIS                            (1 << 4)  /* Field Interrupt Status */

#define R_VIN_INTS_FMS                            (1 << 5)  /* Frame Memory write completion interrupt Status */

#define R_VIN_INTS_PRCLIPHES                      (1 << 8)  /* PRCLIPH Error interrupt Status */

#define R_VIN_INTS_PRCLIPVES                      (1 << 9)  /* PRCLIPV Error interrupt Status */

#define R_VIN_INTS_ROS                            (1 << 14)  /* Response Overflow interrupt Status */

#define R_VIN_INTS_ARES                           (1 << 15)  /* Axi Resp Error interrupt Status */

#define R_VIN_INTS_VRS                            (1 << 16)  /* VSYNC Deasserting Detect Interrupt Status */

#define R_VIN_INTS_VFS                            (1 << 17)  /* VSYNC Asserting Detect Interrupt Status */

#define R_VIN_INTS_FIS2                           (1 << 31)  /* Field Interrupt Status 2 */

/* SI Register bit definitions */
#define R_VIN_SI_SI_SHIFT                         (0)  /* Scanline Interrupt Setting */
#define R_VIN_SI_SI_MASK                          0xfff

/* MTCSTOP Register bit definitions */
#define R_VIN_MTCSTOP_STOPREQ                     (1 << 0)  /* axi forced STOP REQuest */

#define R_VIN_MTCSTOP_STOPACK                     (1 << 1)  /* for axi forced STOP request, ACKnowledgement */

#define R_VIN_MTCSTOP_OUTSTAND_SHIFT              (16)  /* OUTSTANDing current number */
#define R_VIN_MTCSTOP_OUTSTAND_MASK               0x3f0000

/* DMR Register bit definitions */
#define R_VIN_DMR_DTMD_SHIFT                      (0)  /* Data Conversion Mode */
#define R_VIN_DMR_DTMD_MASK                       0x3
#  define R_VIN_DMR_DTMD_00                               (0 << R_VIN_DMR_DTMD_SHIFT)  /* Data is not converted. */
#  define R_VIN_DMR_DTMD_01                               (1 << R_VIN_DMR_DTMD_SHIFT)  /* RGB is converted to ARGB before output. */
#  define R_VIN_DMR_DTMD_10                               (2 << R_VIN_DMR_DTMD_SHIFT)  /* YC is separated before output. */
#  define R_VIN_DMR_DTMD_11                               (3 << R_VIN_DMR_DTMD_SHIFT)  /* Setting prohibited */

#define R_VIN_DMR_ABIT                            (1 << 2)  /* Alpha Bit */

#define R_VIN_DMR_BPSM                            (1 << 4)  /* Output Data Byte Swap Mode */

#define R_VIN_DMR_EXRGB                           (1 << 8)  /* Extension RGB Conversion Mode */

#define R_VIN_DMR_YC_THR                          (1 << 11)  /* YC Data Through Mode */

#define R_VIN_DMR_YMODE_SHIFT                     (12)  /* YC Data Transfer Mode */
#define R_VIN_DMR_YMODE_MASK                      0x7000
#  define R_VIN_DMR_YMODE_000                             (0 << R_VIN_DMR_YMODE_SHIFT)  /* Both Y and CbCr data are transferred to memory. */
#  define R_VIN_DMR_YMODE_001                             (1 << R_VIN_DMR_YMODE_SHIFT)  /* Only Y data is transferred to memory as 8-bit data. */
#  define R_VIN_DMR_YMODE_010                             (2 << R_VIN_DMR_YMODE_SHIFT)  /* 10-bit Y data and 8-bit CbCr data are transferred to memory */
#  define R_VIN_DMR_YMODE_011                             (3 << R_VIN_DMR_YMODE_SHIFT)  /* Only Y data is transferred to memory as 10-bit data */
#  define R_VIN_DMR_YMODE_100                             (4 << R_VIN_DMR_YMODE_SHIFT)  /* Setting prohibited */
#  define R_VIN_DMR_YMODE_101                             (5 << R_VIN_DMR_YMODE_SHIFT)  /* Setting prohibited */
#  define R_VIN_DMR_YMODE_110                             (6 << R_VIN_DMR_YMODE_SHIFT)  /* Setting prohibited */
#  define R_VIN_DMR_YMODE_111                             (7 << R_VIN_DMR_YMODE_SHIFT)  /* Setting prohibited */

#define R_VIN_DMR_A8BIT_SHIFT                     (24)  /* Alpha 8 */
#define R_VIN_DMR_A8BIT_MASK                      0xff000000

/* UVAOF Register bit definitions */
#define R_VIN_UVAOF_UVAOF_SHIFT                   (7)  /* UV Data Address Offset */
#define R_VIN_UVAOF_UVAOF_MASK                    0xffffff80

/* UDS_CTRL Register bit definitions */
#define R_VIN_UDS_CTRL_NE_BCB                     (1 << 16)  /* B/Cb Interpolation Method When Bilinear/Nearest Neighbor Interpolation is Selected */

#define R_VIN_UDS_CTRL_NE_GY                      (1 << 17)  /* G/Y Interpolation Method When Bilinear/Nearest Neighbor Interpolation is Selected */

#define R_VIN_UDS_CTRL_NE_RCR                     (1 << 18)  /* R/Cr Interpolation Method When Bilinear/Nearest Neighbor Interpolation is Selected */

#define R_VIN_UDS_CTRL_BC                         (1 << 20)  /* Pixel Component Interpolation Method at Scale-Up/Down */

#define R_VIN_UDS_CTRL_BLADV                      (1 << 28)  /* BiLinear or nearest neighbor interpolation characteristic ADVanced mode */

#define R_VIN_UDS_CTRL_AMD                        (1 << 30)  /* Advanced MoDe: Pixel Count at Scale-Up */

/* UDS_SCALE Register bit definitions */
#define R_VIN_UDS_SCALE_VFRAC_SHIFT               (0)  /* Multiplier (Fractional Part) of Vertical Scaling Factor */
#define R_VIN_UDS_SCALE_VFRAC_MASK                0xfff

#define R_VIN_UDS_SCALE_VMANT_SHIFT               (12)  /* Multiplier (Integral Part) of Vertical Scaling Factor */
#define R_VIN_UDS_SCALE_VMANT_MASK                0xf000

#define R_VIN_UDS_SCALE_HFRAC_SHIFT               (16)  /* Multiplier (Fractional Part) of Horizontal Scaling Factor */
#define R_VIN_UDS_SCALE_HFRAC_MASK                0xfff0000

#define R_VIN_UDS_SCALE_HMANT_SHIFT               (28)  /* Multiplier (Integral Part) of Horizontal Scaling Factor */
#define R_VIN_UDS_SCALE_HMANT_MASK                0xf0000000

/* UDS_PASS_BWIDTH Register bit definitions */
#define R_VIN_UDS_PASS_BWIDTH_BWIDTH_V_SHIFT      (0)  /* Vertical Signal Passband at Image Scale-Up/Down */
#define R_VIN_UDS_PASS_BWIDTH_BWIDTH_V_MASK       0x7f

#define R_VIN_UDS_PASS_BWIDTH_BWIDTH_H_SHIFT      (16)  /* Horizontal Signal Passband at Image Scale-Up/Down */
#define R_VIN_UDS_PASS_BWIDTH_BWIDTH_H_MASK       0x7f0000

/* UDS_CLIP_SIZE Register bit definitions */
#define R_VIN_UDS_CLIP_SIZE_CL_VSIZE_SHIFT        (0)  /* Clipping Size of Vertical Pixel Count after Scale-Up/-Down */
#define R_VIN_UDS_CLIP_SIZE_CL_VSIZE_MASK         0xfff

#define R_VIN_UDS_CLIP_SIZE_CL_HSIZE_SHIFT        (16)  /* Clipping Size of Horizontal Pixel Count after Scale-Up/-Down */
#define R_VIN_UDS_CLIP_SIZE_CL_HSIZE_MASK         0xfff0000

/* LUTP Register bit definitions */
#define R_VIN_LUTP_LTCRPR_SHIFT                   (0)  /* Lookup Table Cr Pointer */
#define R_VIN_LUTP_LTCRPR_MASK                    0x3ff

#define R_VIN_LUTP_LTCBPR_SHIFT                   (10)  /* Lookup Table Cb Pointer */
#define R_VIN_LUTP_LTCBPR_MASK                    0xffc00

#define R_VIN_LUTP_LTYPR_SHIFT                    (20)  /* Lookup Table Y Pointer */
#define R_VIN_LUTP_LTYPR_MASK                     0x3ff00000

/* LUTD Register bit definitions */
#define R_VIN_LUTD_LTCRDT_SHIFT                   (0)  /* Lookup Table Cr Data */
#define R_VIN_LUTD_LTCRDT_MASK                    0xff

#define R_VIN_LUTD_LTCBDT_SHIFT                   (8)  /* Lookup Table Cb Data */
#define R_VIN_LUTD_LTCBDT_MASK                    0xff00

#define R_VIN_LUTD_LTYDT_SHIFT                    (16)  /* Lookup Table Y Data */
#define R_VIN_LUTD_LTYDT_MASK                     0xff0000

/* YCCR1 Register bit definitions */
#define R_VIN_YCCR1_YCLRP_SHIFT                   (0)  /* R Multiplication Coefficient for Y Calculation */
#define R_VIN_YCCR1_YCLRP_MASK                    0x1fff

/* YCCR2 Register bit definitions */
#define R_VIN_YCCR2_YCLGP_SHIFT                   (0)  /* G Multiplication Coefficient for Y Calculation */
#define R_VIN_YCCR2_YCLGP_MASK                    0x1fff

#define R_VIN_YCCR2_YCLBP_SHIFT                   (16)  /* B Multiplication Coefficient for Y Calculation */
#define R_VIN_YCCR2_YCLBP_MASK                    0x1fff0000

/* YCCR3 Register bit definitions */
#define R_VIN_YCCR3_YCLAP_SHIFT                   (0)  /* Y Calculation Data Normalized Additional Value */
#define R_VIN_YCCR3_YCLAP_MASK                    0xfff

#define R_VIN_YCCR3_YCLHEN                        (1 << 23)  /* Y Calculation Shift Down Result Round-Off Enable */

#define R_VIN_YCCR3_YCLSFT_SHIFT                  (24)  /* Y Calculation Shift Down Volume */
#define R_VIN_YCCR3_YCLSFT_MASK                   0x1f000000

/* CBCCR1 Register bit definitions */
#define R_VIN_CBCCR1_CBCLRP_SHIFT                 (0)  /* R Multiplication Coefficient for Cb Calculation */
#define R_VIN_CBCCR1_CBCLRP_MASK                  0x1fff

/* CBCCR2 Register bit definitions */
#define R_VIN_CBCCR2_CBCLGP_SHIFT                 (0)  /* G Multiplication Coefficient for Cb Calculation */
#define R_VIN_CBCCR2_CBCLGP_MASK                  0x1fff

#define R_VIN_CBCCR2_CBCLBP_SHIFT                 (16)  /* B Multiplication Coefficient for Cb Calculation */
#define R_VIN_CBCCR2_CBCLBP_MASK                  0x1fff0000

/* CBCCR3 Register bit definitions */
#define R_VIN_CBCCR3_CBCLAP_SHIFT                 (0)  /* Cb Calculation Data Normalized Additional Value */
#define R_VIN_CBCCR3_CBCLAP_MASK                  0xfff

#define R_VIN_CBCCR3_CBCLHEN                      (1 << 23)  /* Cb Calculation Shift Down Result Round-Off Enable */

#define R_VIN_CBCCR3_CBCLSFT_SHIFT                (24)  /* Cb Calculation Shift Down Volume */
#define R_VIN_CBCCR3_CBCLSFT_MASK                 0x1f000000

/* CRCCR1 Register bit definitions */
#define R_VIN_CRCCR1_CRCLRP_SHIFT                 (0)  /* R Multiplication Coefficient for Cr Calculation */
#define R_VIN_CRCCR1_CRCLRP_MASK                  0x1fff

/* CRCCR2 Register bit definitions */
#define R_VIN_CRCCR2_CRCLGP_SHIFT                 (0)  /* G Multiplication Coefficient for Cr Calculation */
#define R_VIN_CRCCR2_CRCLGP_MASK                  0x1fff

#define R_VIN_CRCCR2_CRCLBP_SHIFT                 (16)  /* B Multiplication Coefficient for Cr Calculation */
#define R_VIN_CRCCR2_CRCLBP_MASK                  0x1fff0000

/* CRCCR3 Register bit definitions */
#define R_VIN_CRCCR3_CRCLAP_SHIFT                 (0)  /* Cr Calculation Data Normalized Additional Value */
#define R_VIN_CRCCR3_CRCLAP_MASK                  0xfff

#define R_VIN_CRCCR3_CRCLHEN                      (1 << 23)  /* Cr Calculation Shift Down Result Round-Off Enable */

#define R_VIN_CRCCR3_CRCLSFT_SHIFT                (24)  /* Cr Calculation Shift Down Volume */
#define R_VIN_CRCCR3_CRCLSFT_MASK                 0x1f000000

/* CSCE1 Register bit definitions */
#define R_VIN_CSCE1_YMUL2_SHIFT                   (0)  /* Y Multiplication Coefficient 2 for RGB Calculation */
#define R_VIN_CSCE1_YMUL2_MASK                    0x3fff

#define R_VIN_CSCE1_ROUND                         (1 << 16)  /* ROUND off enable */

/* CSCE2 Register bit definitions */
#define R_VIN_CSCE2_CSUB2_SHIFT                   (0)  /* CbCr Subtraction Coefficient 2 for RGB Calculation */
#define R_VIN_CSCE2_CSUB2_MASK                    0xfff

#define R_VIN_CSCE2_YSUB2_SHIFT                   (16)  /* Y Subtraction Coefficient 2 for RGB Calculation */
#define R_VIN_CSCE2_YSUB2_MASK                    0xfff0000

/* CSCE3 Register bit definitions */
#define R_VIN_CSCE3_GCRMUL2_SHIFT                 (0)  /* Cr Multiplication Coefficient 2 for G Calculation */
#define R_VIN_CSCE3_GCRMUL2_MASK                  0x3fff

#define R_VIN_CSCE3_RCRMUL2_SHIFT                 (16)  /* Cr Multiplication Coefficient 2 for R Calculation */
#define R_VIN_CSCE3_RCRMUL2_MASK                  0x3fff0000

/* CSCE4 Register bit definitions */
#define R_VIN_CSCE4_BCBMUL2_SHIFT                 (0)  /* Cb Multiplication Coefficient 2 for B Calculation */
#define R_VIN_CSCE4_BCBMUL2_MASK                  0x3fff

#define R_VIN_CSCE4_GCBMUL2_SHIFT                 (16)  /* Cb Multiplication Coefficient 2 for G Calculation */
#define R_VIN_CSCE4_GCBMUL2_MASK                  0x3fff0000


/* Maximum number of channels */

#define VIN_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_VIN_H */

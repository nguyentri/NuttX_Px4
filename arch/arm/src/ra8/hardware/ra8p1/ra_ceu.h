/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_ceu.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CEU_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CEU_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CEU Base Address */
#ifndef R_CEU_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_CEU_BASE           0x40348000
#else
#define R_CEU_BASE           0x50348000
#endif
#endif

/* CEU Register Offsets */

#define R_CEU_CAPSR_OFFSET     0x00000000  /* Capture Start Register */
#define R_CEU_CAPCR_OFFSET     0x00000004  /* Capture Control Register */
#define R_CEU_CAMCR_OFFSET     0x00000008  /* Capture Interface Control Register */
#define R_CEU_CMCYR_OFFSET     0x0000000c  /* Capture Interface Cycle Register */
#define R_CEU_CAMOR_OFFSET     0x00000010  /* Capture Interface Offset Register */
#define R_CEU_CAPWR_OFFSET     0x00000014  /* Capture Interface Width Register */
#define R_CEU_CAIFR_OFFSET     0x00000018  /* Capture Interface Input Format Register */
#define R_CEU_CRCNTR_OFFSET     0x00000028  /* CEU Register Control Register */
#define R_CEU_CRCMPR_OFFSET     0x0000002c  /* CEU Register Forcible Control Register */
#define R_CEU_CFLCR_OFFSET     0x00000030  /* Capture Filter Control Register */
#define R_CEU_CFSZR_OFFSET     0x00000034  /* Capture Filter Size Clip Register */
#define R_CEU_CDWDR_OFFSET     0x00000038  /* Capture Destination Width Register */
#define R_CEU_CDAYR_OFFSET     0x0000003c  /* Capture Data Address Y Register */
#define R_CEU_CDACR_OFFSET     0x00000040  /* Capture Data Address C Register */
#define R_CEU_CDBYR_OFFSET     0x00000044  /* Capture Data Bottom-Field Address Y Register */
#define R_CEU_CDBCR_OFFSET     0x00000048  /* Capture Data Bottom-Field Address C Register */
#define R_CEU_CBDSR_OFFSET     0x0000004c  /* Capture Bundle Destination Size Register */
#define R_CEU_CFWCR_OFFSET     0x0000005c  /* Firewall Operation Control Register */
#define R_CEU_CLFCR_OFFSET     0x00000060  /* Capture Low-Pass Filter Control Register */
#define R_CEU_CDOCR_OFFSET     0x00000064  /* Capture Data Output Control Register */
#define R_CEU_CEIER_OFFSET     0x00000070  /* Capture Event Interrupt Enable Register */
#define R_CEU_CETCR_OFFSET     0x00000074  /* Capture Event Flag Clear Register */
#define R_CEU_CSTSR_OFFSET     0x0000007c  /* Capture Status Register */
#define R_CEU_CDSSR_OFFSET     0x00000084  /* Capture Data Size Register */
#define R_CEU_CDAYR2_OFFSET     0x00000090  /* Capture Data Address Y Register 2 */
#define R_CEU_CDACR2_OFFSET     0x00000094  /* Capture Data Address C Register 2 */
#define R_CEU_CDBYR2_OFFSET     0x00000098  /* Capture Data Bottom-Field Address Y Register 2 */
#define R_CEU_CDBCR2_OFFSET     0x0000009c  /* Capture Data Bottom-Field Address C Register 2 */
#define R_CEU_CBWER_OFFSET     0x000000a0  /* CEU Bufferable Write Enable Register */
#define R_CEU_CAMOR_B_OFFSET     0x00001010  /* Capture Interface Offset Register */
#define R_CEU_CAPWR_B_OFFSET     0x00001014  /* Capture Interface Width Register */
#define R_CEU_CFLCR_B_OFFSET     0x00001030  /* Capture Filter Control Register */
#define R_CEU_CFSZR_B_OFFSET     0x00001034  /* Capture Filter Size Clip Register */
#define R_CEU_CDWDR_B_OFFSET     0x00001038  /* Capture Destination Width Register */
#define R_CEU_CDAYR_B_OFFSET     0x0000103c  /* Capture Data Address Y Register */
#define R_CEU_CDACR_B_OFFSET     0x00001040  /* Capture Data Address C Register */
#define R_CEU_CDBYR_B_OFFSET     0x00001044  /* Capture Data Bottom-Field Address Y Register */
#define R_CEU_CDBCR_B_OFFSET     0x00001048  /* Capture Data Bottom-Field Address C Register */
#define R_CEU_CBDSR_B_OFFSET     0x0000104c  /* Capture Bundle Destination Size Register */
#define R_CEU_CLFCR_B_OFFSET     0x00001060  /* Capture Low-Pass Filter Control Register */
#define R_CEU_CDOCR_B_OFFSET     0x00001064  /* Capture Data Output Control Register */
#define R_CEU_CDAYR2_B_OFFSET     0x00001090  /* Capture Data Address Y Register 2 */
#define R_CEU_CDACR2_B_OFFSET     0x00001094  /* Capture Data Address C Register 2 */
#define R_CEU_CDBYR2_B_OFFSET     0x00001098  /* Capture Data Bottom-Field Address Y Register 2 */
#define R_CEU_CDBCR2_B_OFFSET     0x0000109c  /* Capture Data Bottom-Field Address C Register 2 */
#define R_CEU_CAMOR_M_OFFSET     0x00002010  /* Capture Interface Offset Register */
#define R_CEU_CAPWR_M_OFFSET     0x00002014  /* Capture Interface Width Register */
#define R_CEU_CFLCR_M_OFFSET     0x00002030  /* Capture Filter Control Register */
#define R_CEU_CFSZR_M_OFFSET     0x00002034  /* Capture Filter Size Clip Register */
#define R_CEU_CDWDR_M_OFFSET     0x00002038  /* Capture Destination Width Register */
#define R_CEU_CDAYR_M_OFFSET     0x0000203c  /* Capture Data Address Y Register */
#define R_CEU_CDACR_M_OFFSET     0x00002040  /* Capture Data Address C Register */
#define R_CEU_CDBYR_M_OFFSET     0x00002044  /* Capture Data Bottom-Field Address Y Register */
#define R_CEU_CDBCR_M_OFFSET     0x00002048  /* Capture Data Bottom-Field Address C Register */
#define R_CEU_CBDSR_M_OFFSET     0x0000204c  /* Capture Bundle Destination Size Register */
#define R_CEU_CLFCR_M_OFFSET     0x00002060  /* Capture Low-Pass Filter Control Register */
#define R_CEU_CDOCR_M_OFFSET     0x00002064  /* Capture Data Output Control Register */
#define R_CEU_CDAYR2_M_OFFSET     0x00002090  /* Capture Data Address Y Register 2 */
#define R_CEU_CDACR2_M_OFFSET     0x00002094  /* Capture Data Address C Register 2 */
#define R_CEU_CDBYR2_M_OFFSET     0x00002098  /* Capture Data Bottom-Field Address Y Register 2 */
#define R_CEU_CDBCR2_M_OFFSET     0x0000209c  /* Capture Data Bottom-Field Address C Register 2 */

/* CEU Register Addresses */

#define R_CEU_CAPSR                 (R_CEU_BASE + R_CEU_CAPSR_OFFSET)
#define R_CEU_CAPCR                 (R_CEU_BASE + R_CEU_CAPCR_OFFSET)
#define R_CEU_CAMCR                 (R_CEU_BASE + R_CEU_CAMCR_OFFSET)
#define R_CEU_CMCYR                 (R_CEU_BASE + R_CEU_CMCYR_OFFSET)
#define R_CEU_CAMOR                 (R_CEU_BASE + R_CEU_CAMOR_OFFSET)
#define R_CEU_CAPWR                 (R_CEU_BASE + R_CEU_CAPWR_OFFSET)
#define R_CEU_CAIFR                 (R_CEU_BASE + R_CEU_CAIFR_OFFSET)
#define R_CEU_CRCNTR                 (R_CEU_BASE + R_CEU_CRCNTR_OFFSET)
#define R_CEU_CRCMPR                 (R_CEU_BASE + R_CEU_CRCMPR_OFFSET)
#define R_CEU_CFLCR                 (R_CEU_BASE + R_CEU_CFLCR_OFFSET)
#define R_CEU_CFSZR                 (R_CEU_BASE + R_CEU_CFSZR_OFFSET)
#define R_CEU_CDWDR                 (R_CEU_BASE + R_CEU_CDWDR_OFFSET)
#define R_CEU_CDAYR                 (R_CEU_BASE + R_CEU_CDAYR_OFFSET)
#define R_CEU_CDACR                 (R_CEU_BASE + R_CEU_CDACR_OFFSET)
#define R_CEU_CDBYR                 (R_CEU_BASE + R_CEU_CDBYR_OFFSET)
#define R_CEU_CDBCR                 (R_CEU_BASE + R_CEU_CDBCR_OFFSET)
#define R_CEU_CBDSR                 (R_CEU_BASE + R_CEU_CBDSR_OFFSET)
#define R_CEU_CFWCR                 (R_CEU_BASE + R_CEU_CFWCR_OFFSET)
#define R_CEU_CLFCR                 (R_CEU_BASE + R_CEU_CLFCR_OFFSET)
#define R_CEU_CDOCR                 (R_CEU_BASE + R_CEU_CDOCR_OFFSET)
#define R_CEU_CEIER                 (R_CEU_BASE + R_CEU_CEIER_OFFSET)
#define R_CEU_CETCR                 (R_CEU_BASE + R_CEU_CETCR_OFFSET)
#define R_CEU_CSTSR                 (R_CEU_BASE + R_CEU_CSTSR_OFFSET)
#define R_CEU_CDSSR                 (R_CEU_BASE + R_CEU_CDSSR_OFFSET)
#define R_CEU_CDAYR2                 (R_CEU_BASE + R_CEU_CDAYR2_OFFSET)
#define R_CEU_CDACR2                 (R_CEU_BASE + R_CEU_CDACR2_OFFSET)
#define R_CEU_CDBYR2                 (R_CEU_BASE + R_CEU_CDBYR2_OFFSET)
#define R_CEU_CDBCR2                 (R_CEU_BASE + R_CEU_CDBCR2_OFFSET)
#define R_CEU_CBWER                 (R_CEU_BASE + R_CEU_CBWER_OFFSET)
#define R_CEU_CAMOR_B                 (R_CEU_BASE + R_CEU_CAMOR_B_OFFSET)
#define R_CEU_CAPWR_B                 (R_CEU_BASE + R_CEU_CAPWR_B_OFFSET)
#define R_CEU_CFLCR_B                 (R_CEU_BASE + R_CEU_CFLCR_B_OFFSET)
#define R_CEU_CFSZR_B                 (R_CEU_BASE + R_CEU_CFSZR_B_OFFSET)
#define R_CEU_CDWDR_B                 (R_CEU_BASE + R_CEU_CDWDR_B_OFFSET)
#define R_CEU_CDAYR_B                 (R_CEU_BASE + R_CEU_CDAYR_B_OFFSET)
#define R_CEU_CDACR_B                 (R_CEU_BASE + R_CEU_CDACR_B_OFFSET)
#define R_CEU_CDBYR_B                 (R_CEU_BASE + R_CEU_CDBYR_B_OFFSET)
#define R_CEU_CDBCR_B                 (R_CEU_BASE + R_CEU_CDBCR_B_OFFSET)
#define R_CEU_CBDSR_B                 (R_CEU_BASE + R_CEU_CBDSR_B_OFFSET)
#define R_CEU_CLFCR_B                 (R_CEU_BASE + R_CEU_CLFCR_B_OFFSET)
#define R_CEU_CDOCR_B                 (R_CEU_BASE + R_CEU_CDOCR_B_OFFSET)
#define R_CEU_CDAYR2_B                 (R_CEU_BASE + R_CEU_CDAYR2_B_OFFSET)
#define R_CEU_CDACR2_B                 (R_CEU_BASE + R_CEU_CDACR2_B_OFFSET)
#define R_CEU_CDBYR2_B                 (R_CEU_BASE + R_CEU_CDBYR2_B_OFFSET)
#define R_CEU_CDBCR2_B                 (R_CEU_BASE + R_CEU_CDBCR2_B_OFFSET)
#define R_CEU_CAMOR_M                 (R_CEU_BASE + R_CEU_CAMOR_M_OFFSET)
#define R_CEU_CAPWR_M                 (R_CEU_BASE + R_CEU_CAPWR_M_OFFSET)
#define R_CEU_CFLCR_M                 (R_CEU_BASE + R_CEU_CFLCR_M_OFFSET)
#define R_CEU_CFSZR_M                 (R_CEU_BASE + R_CEU_CFSZR_M_OFFSET)
#define R_CEU_CDWDR_M                 (R_CEU_BASE + R_CEU_CDWDR_M_OFFSET)
#define R_CEU_CDAYR_M                 (R_CEU_BASE + R_CEU_CDAYR_M_OFFSET)
#define R_CEU_CDACR_M                 (R_CEU_BASE + R_CEU_CDACR_M_OFFSET)
#define R_CEU_CDBYR_M                 (R_CEU_BASE + R_CEU_CDBYR_M_OFFSET)
#define R_CEU_CDBCR_M                 (R_CEU_BASE + R_CEU_CDBCR_M_OFFSET)
#define R_CEU_CBDSR_M                 (R_CEU_BASE + R_CEU_CBDSR_M_OFFSET)
#define R_CEU_CLFCR_M                 (R_CEU_BASE + R_CEU_CLFCR_M_OFFSET)
#define R_CEU_CDOCR_M                 (R_CEU_BASE + R_CEU_CDOCR_M_OFFSET)
#define R_CEU_CDAYR2_M                 (R_CEU_BASE + R_CEU_CDAYR2_M_OFFSET)
#define R_CEU_CDACR2_M                 (R_CEU_BASE + R_CEU_CDACR2_M_OFFSET)
#define R_CEU_CDBYR2_M                 (R_CEU_BASE + R_CEU_CDBYR2_M_OFFSET)
#define R_CEU_CDBCR2_M                 (R_CEU_BASE + R_CEU_CDBCR2_M_OFFSET)

/* Register bit definitions */
/* CAPSR Register bit definitions */
#define R_CEU_CAPSR_CE                            (1 << 0)  /* Capture enable */

#define R_CEU_CAPSR_CPKIL                         (1 << 16)  /* Software reset of capturing */

/* CAPCR Register bit definitions */
#define R_CEU_CAPCR_CTNCP                         (1 << 16)  /* Continuous capture */

#define R_CEU_CAPCR_MTCM_SHIFT                    (20)  /* Specify the unit for transferring data to a bus bridge module. */
#define R_CEU_CAPCR_MTCM_MASK                     0x300000
#  define R_CEU_CAPCR_MTCM_00                             (0 << R_CEU_CAPCR_MTCM_SHIFT)  /* Image capture: Y data and C data are transferred in 32-byte units Data fetch : Data is transferred in 32-byte units  */
#  define R_CEU_CAPCR_MTCM_01                             (1 << R_CEU_CAPCR_MTCM_SHIFT)  /* Image capture: Y data and C data are transferred in 64-byte units Data fetch : Data is transferred in 64-byte  */
#  define R_CEU_CAPCR_MTCM_10                             (2 << R_CEU_CAPCR_MTCM_SHIFT)  /* Image capture: Y data and C data are transferred in 128-byte units Data fetch : Data is transferred in 128-byte  */
#  define R_CEU_CAPCR_MTCM_11                             (3 << R_CEU_CAPCR_MTCM_SHIFT)  /* Image capture: Y data and C data are transferred in 256-byte units Data fetch : Data is transferred in 256-byte  */

#define R_CEU_CAPCR_FDRP_SHIFT                    (24)  /* Set the frame drop interval in continuous-frame capture. */
#define R_CEU_CAPCR_FDRP_MASK                     0xff000000

/* CAMCR Register bit definitions */
#define R_CEU_CAMCR_HDPOL                         (1 << 0)  /* Sets the polarity for detection of the horizontal sync signal (HD) input from an external module. */

#define R_CEU_CAMCR_VDPOL                         (1 << 1)  /* Sets the polarity for detection of the vertical sync signal (VD) input from an external module. */

#define R_CEU_CAMCR_JPG_SHIFT                     (4)  /* These bits select the fetched data type. */
#define R_CEU_CAMCR_JPG_MASK                      0x30
#  define R_CEU_CAMCR_JPG_00                              (0 << R_CEU_CAMCR_JPG_SHIFT)  /* Image capture mode (input data are separated into the luminance component data (Y) and the chrominance component data (CbCr) for output to the memory)  */
#  define R_CEU_CAMCR_JPG_01                              (1 << R_CEU_CAMCR_JPG_SHIFT)  /* Data synchronous fetch mode (specified size of input data are output to the specified memory addresses in order of input and in synchronization with the sync signal)  */
#  define R_CEU_CAMCR_JPG_10                              (2 << R_CEU_CAMCR_JPG_SHIFT)  /* Data enable fetch mode (input data are fetched with HD as an enable signal and output to the specified addresses in memory in order of input)  */
#  define R_CEU_CAMCR_JPG_11                              (3 << R_CEU_CAMCR_JPG_SHIFT)  /* Setting prohibited */

#define R_CEU_CAMCR_DTARY_SHIFT                   (8)  /* Set the input order of the luminance component and chrominance component. */
#define R_CEU_CAMCR_DTARY_MASK                    0x300
#  define R_CEU_CAMCR_DTARY_00                            (0 << R_CEU_CAMCR_DTARY_SHIFT)  /* 8-bit interface: Image input data is fetched in the order of Cb0, Y0, Cr0, and Y1 16-bit interface: Image input data is fetched in the order of {Cb0, Y0} and {Cr0, Y1}  */
#  define R_CEU_CAMCR_DTARY_01                            (1 << R_CEU_CAMCR_DTARY_SHIFT)  /* 8-bit interface: Image input data is fetched in the order of Cr0, Y0, Cb0, and Y1 16-bit interface: Image input data is fetched in the order of {Cr0, Y0} and {Cb0, Y1}  */
#  define R_CEU_CAMCR_DTARY_10                            (2 << R_CEU_CAMCR_DTARY_SHIFT)  /* 8-bit interface: Image input data is fetched in the order of Y0, Cb0, Y1, and Cr0 16-bit interface: Image input data is fetched in the order of {Y0, Cb0} and {Y1, Cr0}  */
#  define R_CEU_CAMCR_DTARY_11                            (3 << R_CEU_CAMCR_DTARY_SHIFT)  /* 8-bit interface: Image input data is fetched in the order of Y0, Cr0, Y1, and Cb0 16-bit interface: Image input data is fetched in the order of {Y0, Cr0} and {Y1, Cb0}  */

#define R_CEU_CAMCR_DTIF                          (1 << 12)  /* Sets the digital image input pins from which data is to be captured. */

#define R_CEU_CAMCR_FLDPOL                        (1 << 16)  /* Sets the polarity of the field identification signal (FLD) from an external module. */

#define R_CEU_CAMCR_DSEL                          (1 << 24)  /* Sets the edge for fetching the image data (D15 to D0) from an external module. */

#define R_CEU_CAMCR_FLDSEL                        (1 << 25)  /* Sets the edge for capturing FLD from an external module. */

#define R_CEU_CAMCR_HDSEL                         (1 << 26)  /* Sets the edge for capturing HD from an external module. */

#define R_CEU_CAMCR_VDSEL                         (1 << 27)  /* Sets the edge for capturing VD from an external module. */

/* CMCYR Register bit definitions */
#define R_CEU_CMCYR_HCYL_SHIFT                    (0)  /* Horizontal Cycle Count of External Module */
#define R_CEU_CMCYR_HCYL_MASK                     0x3fff

#define R_CEU_CMCYR_VCYL_SHIFT                    (16)  /* Vertical HD Count of External Module */
#define R_CEU_CMCYR_VCYL_MASK                     0x3fff0000

/* CAMOR Register bit definitions */
#define R_CEU_CAMOR_HOFST_SHIFT                   (0)  /* Specify the capture start location in terms of the number of clock cycles from a horizontal sync signal (1-cycle units). */
#define R_CEU_CAMOR_HOFST_MASK                    0x1fff

#define R_CEU_CAMOR_VOFST_SHIFT                   (16)  /* Specify the capture start location in terms of the HD count from a vertical sync signal (1-HD units). */
#define R_CEU_CAMOR_VOFST_MASK                    0xfff0000

/* CAPWR Register bit definitions */
#define R_CEU_CAPWR_HWDTH_SHIFT                   (0)  /* Specify the horizontal capture period. */
#define R_CEU_CAPWR_HWDTH_MASK                    0x1fff

#define R_CEU_CAPWR_VWDTH_SHIFT                   (16)  /* Specify the vertical capture period (4-HD units). */
#define R_CEU_CAPWR_VWDTH_MASK                    0xfff0000

/* CAIFR Register bit definitions */
#define R_CEU_CAIFR_FCI_SHIFT                     (0)  /* Set the timing to start capturing. */
#define R_CEU_CAIFR_FCI_MASK                      0x3
#  define R_CEU_CAIFR_FCI_00                              (0 << R_CEU_CAIFR_FCI_SHIFT)  /* Capture starts from the VD input immediately after the CEU activation regardless of it being a top or bottom field  */
#  define R_CEU_CAIFR_FCI_01                              (1 << R_CEU_CAIFR_FCI_SHIFT)  /* After the CEU activation, input of a top-field image is waited, and then capture starts from the top field  */
#  define R_CEU_CAIFR_FCI_10                              (2 << R_CEU_CAIFR_FCI_SHIFT)  /* After the CEU activation, input of a bottom-field image is waited, and then capture starts from the bottom field  */
#  define R_CEU_CAIFR_FCI_11                              (3 << R_CEU_CAIFR_FCI_SHIFT)  /* Setting prohibited */

#define R_CEU_CAIFR_CIM                           (1 << 4)  /* Sets the images to be captured. */

#define R_CEU_CAIFR_IFS                           (1 << 8)  /* Sets the input mode for capturing images. */

/* CRCNTR Register bit definitions */
#define R_CEU_CRCNTR_RC                           (1 << 0)  /* Specifies switching of the register plane used by the CEU in synchronization with VD. */

#define R_CEU_CRCNTR_RS                           (1 << 1)  /* Specifies which register plane is used by the CEU in synchronization with VD. */

#define R_CEU_CRCNTR_RVS                          (1 << 4)  /* Sets the timing to switch the register plane in both-field capture. */

/* CRCMPR Register bit definitions */
#define R_CEU_CRCMPR_RA                           (1 << 0)  /* Indicates the register plane currently specified. */

/* CFLCR Register bit definitions */
#define R_CEU_CFLCR_HFRAC_SHIFT                   (0)  /* Fraction Part of Horizontal Scale-Down Factor */
#define R_CEU_CFLCR_HFRAC_MASK                    0xfff

#define R_CEU_CFLCR_HMANT_SHIFT                   (12)  /* Mantissa Part of Horizontal Scale-Down Factor */
#define R_CEU_CFLCR_HMANT_MASK                    0xf000

#define R_CEU_CFLCR_VFRAC_SHIFT                   (16)  /* Fraction Part of Vertical Scale-Down Factor */
#define R_CEU_CFLCR_VFRAC_MASK                    0xfff0000

#define R_CEU_CFLCR_VMANT_SHIFT                   (28)  /* Mantissa Part of Vertical Scale-Down Factor */
#define R_CEU_CFLCR_VMANT_MASK                    0xf0000000

/* CFSZR Register bit definitions */
#define R_CEU_CFSZR_HFCLP_SHIFT                   (0)  /* Specify the horizontal clipping value of the filter output size (8-pixel units). */
#define R_CEU_CFSZR_HFCLP_MASK                    0xfff

#define R_CEU_CFSZR_VFCLP_SHIFT                   (16)  /* Specify the vertical clipping value of the filter output size (4-pixel units). */
#define R_CEU_CFSZR_VFCLP_MASK                    0xfff0000

/* CDWDR Register bit definitions */
#define R_CEU_CDWDR_CHDW_SHIFT                    (0)  /* Specify the horizontal image size in the memory area where the captured image is to be stored (8-byte units). */
#define R_CEU_CDWDR_CHDW_MASK                     0x1fff

/* CDAYR Register bit definitions */
#define R_CEU_CDAYR_CAYR_SHIFT                    (0)  /* Capture Data Address Y */
#define R_CEU_CDAYR_CAYR_MASK                     0xffffffff

/* CDACR Register bit definitions */
#define R_CEU_CDACR_CACR_SHIFT                    (0)  /* Capture Data Address C */
#define R_CEU_CDACR_CACR_MASK                     0xffffffff

/* CDBYR Register bit definitions */
#define R_CEU_CDBYR_CBYR_SHIFT                    (0)  /* Set the address for storing the luminance component data of the captured bottom-field data (8-pixel units). */
#define R_CEU_CDBYR_CBYR_MASK                     0xffffffff

/* CDBCR Register bit definitions */
#define R_CEU_CDBCR_CBCR_SHIFT                    (0)  /* Set the address for storing the chrominance component data of the captured bottom-field data (8-pixel units). */
#define R_CEU_CDBCR_CBCR_MASK                     0xffffffff

/* CBDSR Register bit definitions */
#define R_CEU_CBDSR_CBVS_SHIFT                    (0)  /* Select the number of lines or number of bytes for output to the memory in a bundle write. */
#define R_CEU_CBDSR_CBVS_MASK                     0x7fffff

/* CFWCR Register bit definitions */
#define R_CEU_CFWCR_FWE                           (1 << 0)  /* Firewall Operation */

#define R_CEU_CFWCR_FWV_SHIFT                     (5)  /* Specify the upper limit of a write address. */
#define R_CEU_CFWCR_FWV_MASK                      0xffffffe0

/* CLFCR Register bit definitions */
#define R_CEU_CLFCR_LPF                           (1 << 0)  /* Enables or disables operation of the low-pass filter. */

/* CDOCR Register bit definitions */
#define R_CEU_CDOCR_COBS                          (1 << 0)  /* Controls swapping in 8-bit units for data output from the CEU. */

#define R_CEU_CDOCR_COWS                          (1 << 1)  /* Controls swapping in 16-bit units for data output from the CEU. */

#define R_CEU_CDOCR_COLS                          (1 << 2)  /* Controls swapping in 32-bit units for data output from the CEU. */

#define R_CEU_CDOCR_CDS                           (1 << 4)  /* Sets the image format when outputting the image data captured in the YCbCr422 format to the memory. */

#define R_CEU_CDOCR_CBE                           (1 << 16)  /*  Controls the number of lines of captured data to be written to the memory. */

/* CEIER Register bit definitions */
#define R_CEU_CEIER_CPEIE                         (1 << 0)  /* One-Frame Capture End Interrupt Enable */

#define R_CEU_CEIER_CFEIE                         (1 << 1)  /* CFE Interrupt Enable */

#define R_CEU_CEIER_IGRWIE                        (1 << 4)  /* Register-Access-During-Capture Interrupt Enable */

#define R_CEU_CEIER_HDIE                          (1 << 8)  /* HD Interrupt Enable */

#define R_CEU_CEIER_VDIE                          (1 << 9)  /* VD Interrupt Enable */

#define R_CEU_CEIER_CPBE1IE                       (1 << 12)  /* CPBE1 Interrupt Enable */

#define R_CEU_CEIER_CPBE2IE                       (1 << 13)  /* CPBE2 Interrupt Enable */

#define R_CEU_CEIER_CPBE3IE                       (1 << 14)  /* CPBE3 Interrupt Enable */

#define R_CEU_CEIER_CPBE4IE                       (1 << 15)  /* CPBE4 Interrupt Enable */

#define R_CEU_CEIER_CDTOFIE                       (1 << 16)  /* CDTOF Interrupt Enable */

#define R_CEU_CEIER_IGHSIE                        (1 << 17)  /* IGHS Interrupt Enable */

#define R_CEU_CEIER_IGVSIE                        (1 << 18)  /* IGVS Interrupt Enable */

#define R_CEU_CEIER_VBPIE                         (1 << 20)  /* VBP Interrupt Enable */

#define R_CEU_CEIER_FWFIE                         (1 << 23)  /* FWF Interrupt Enable */

#define R_CEU_CEIER_NHDIE                         (1 << 24)  /* Non-HD Interrupt Enable */

#define R_CEU_CEIER_NVDIE                         (1 << 25)  /* Non-VD Interrupt Enable */

/* CETCR Register bit definitions */
#define R_CEU_CETCR_CPE                           (1 << 0)  /* An interrupt indicating that capturing of one frame from an external module has finished. */

#define R_CEU_CETCR_CFE                           (1 << 1)  /* An interrupt indicating that capturing of one field from an external module has finished. */

#define R_CEU_CETCR_IGRW                          (1 << 4)  /* An interrupt indicating that during capturing, access was attempted to a register to which writing during operation is prohibited. */

#define R_CEU_CETCR_HD                            (1 << 8)  /* An interrupt indicating that HD (horizontal sync signal) was input from an external module. */

#define R_CEU_CETCR_VD                            (1 << 9)  /* An interrupt indicating that VD (vertical sync signal) was input from an external module. */

#define R_CEU_CETCR_CPBE1                         (1 << 12)  /* An interrupt indicating that writing to CDAYR and CDACR in a bundle write has finished. */

#define R_CEU_CETCR_CPBE2                         (1 << 13)  /* An interrupt indicating that writing to CDAYR2 and CDACR2 in a bundle write has finished. */

#define R_CEU_CETCR_CPBE3                         (1 << 14)  /* An interrupt indicating that writing to CDBYR and CDBCR in a bundle write has finished. */

#define R_CEU_CETCR_CPBE4                         (1 << 15)  /* An interrupt indicating that writing to CDBYR2 and CDBCR2 in a bundle write has finished. */

#define R_CEU_CETCR_CDTOF                         (1 << 16)  /* An interrupt indicating that data overflowed in the CRAM of the write buffer */

#define R_CEU_CETCR_IGHS                          (1 << 17)  /* An interrupt generated when the number of HD cycles set in CMCYR differ from the number of HD cycles input from an external module. */

#define R_CEU_CETCR_IGVS                          (1 << 18)  /* An interrupt generated when the number of VD cycles set in CMCYR differ from the number of VD cycles input from an external module. */

#define R_CEU_CETCR_VBP                           (1 << 20)  /* An interrupt indicating that VD has been input while the CEU holds data (insufficient vertical-sync front porch). */

#define R_CEU_CETCR_FWF                           (1 << 23)  /* The interrupt is generated when data is written to the address that exceeds the value specified with CFWCR.FMV. */

#define R_CEU_CETCR_NHD                           (1 << 24)  /* An interrupt indicating that no HD was input. */

#define R_CEU_CETCR_NVD                           (1 << 25)  /* An interrupt indicating that no VD was input. */

/* CSTSR Register bit definitions */
#define R_CEU_CSTSR_CPTON                         (1 << 0)  /* Indicates that the CEU is operating. */

#define R_CEU_CSTSR_CPFLD                         (1 << 16)  /* Indicates which field is being captured. */

#define R_CEU_CSTSR_CRST                          (1 << 24)  /* Indicates which register plane is currently used. */

/* CDSSR Register bit definitions */
#define R_CEU_CDSSR_CDSS_SHIFT                    (0)  /* Indicate the size of data written to the memory in data enable fetch. */
#define R_CEU_CDSSR_CDSS_MASK                     0xffffffff

/* CDAYR2 Register bit definitions */
#define R_CEU_CDAYR2_CAYR2_SHIFT                  (0)  /* Capture Data Address Y */
#define R_CEU_CDAYR2_CAYR2_MASK                   0xffffffff

/* CDACR2 Register bit definitions */
#define R_CEU_CDACR2_CACR2_SHIFT                  (0)  /* Capture Data Address C */
#define R_CEU_CDACR2_CACR2_MASK                   0xffffffff

/* CDBYR2 Register bit definitions */
#define R_CEU_CDBYR2_CBYR2_SHIFT                  (0)  /* Set the address for storing the luminance component data of the captured bottom-field data (8-pixel units). */
#define R_CEU_CDBYR2_CBYR2_MASK                   0xffffffff

/* CDBCR2 Register bit definitions */
#define R_CEU_CDBCR2_CBCR2_SHIFT                  (0)  /* Set the address for storing the chrominance component data of the captured bottom-field data (8-pixel units). */
#define R_CEU_CDBCR2_CBCR2_MASK                   0xffffffff

/* CBWER Register bit definitions */
#define R_CEU_CBWER_BWE                           (1 << 0)  /*  */

/* CAMOR_B Register bit definitions */
#define R_CEU_CAMOR_B_HOFST_SHIFT                 (0)  /* Specify the capture start location in terms of the number of clock cycles from a horizontal sync signal (1-cycle units). */
#define R_CEU_CAMOR_B_HOFST_MASK                  0x1fff

#define R_CEU_CAMOR_B_VOFST_SHIFT                 (16)  /* Specify the capture start location in terms of the HD count from a vertical sync signal (1-HD units). */
#define R_CEU_CAMOR_B_VOFST_MASK                  0xfff0000

/* CAPWR_B Register bit definitions */
#define R_CEU_CAPWR_B_HWDTH_SHIFT                 (0)  /* Specify the horizontal capture period. */
#define R_CEU_CAPWR_B_HWDTH_MASK                  0x1fff

#define R_CEU_CAPWR_B_VWDTH_SHIFT                 (16)  /* Specify the vertical capture period (4-HD units). */
#define R_CEU_CAPWR_B_VWDTH_MASK                  0xfff0000

/* CFLCR_B Register bit definitions */
#define R_CEU_CFLCR_B_HFRAC_SHIFT                 (0)  /* Fraction Part of Horizontal Scale-Down Factor */
#define R_CEU_CFLCR_B_HFRAC_MASK                  0xfff

#define R_CEU_CFLCR_B_HMANT_SHIFT                 (12)  /* Mantissa Part of Horizontal Scale-Down Factor */
#define R_CEU_CFLCR_B_HMANT_MASK                  0xf000

#define R_CEU_CFLCR_B_VFRAC_SHIFT                 (16)  /* Fraction Part of Vertical Scale-Down Factor */
#define R_CEU_CFLCR_B_VFRAC_MASK                  0xfff0000

#define R_CEU_CFLCR_B_VMANT_SHIFT                 (28)  /* Mantissa Part of Vertical Scale-Down Factor */
#define R_CEU_CFLCR_B_VMANT_MASK                  0xf0000000

/* CFSZR_B Register bit definitions */
#define R_CEU_CFSZR_B_HFCLP_SHIFT                 (0)  /* Specify the horizontal clipping value of the filter output size (8-pixel units). */
#define R_CEU_CFSZR_B_HFCLP_MASK                  0xfff

#define R_CEU_CFSZR_B_VFCLP_SHIFT                 (16)  /* Specify the vertical clipping value of the filter output size (4-pixel units). */
#define R_CEU_CFSZR_B_VFCLP_MASK                  0xfff0000

/* CDWDR_B Register bit definitions */
#define R_CEU_CDWDR_B_CHDW_SHIFT                  (0)  /* Specify the horizontal image size in the memory area where the captured image is to be stored (8-byte units). */
#define R_CEU_CDWDR_B_CHDW_MASK                   0x1fff

/* CDAYR_B Register bit definitions */
#define R_CEU_CDAYR_B_CAYR_SHIFT                  (0)  /* Capture Data Address Y */
#define R_CEU_CDAYR_B_CAYR_MASK                   0xffffffff

/* CDACR_B Register bit definitions */
#define R_CEU_CDACR_B_CACR_SHIFT                  (0)  /* Capture Data Address C */
#define R_CEU_CDACR_B_CACR_MASK                   0xffffffff

/* CDBYR_B Register bit definitions */
#define R_CEU_CDBYR_B_CBYR_SHIFT                  (0)  /* Set the address for storing the luminance component data of the captured bottom-field data (8-pixel units). */
#define R_CEU_CDBYR_B_CBYR_MASK                   0xffffffff

/* CDBCR_B Register bit definitions */
#define R_CEU_CDBCR_B_CBCR_SHIFT                  (0)  /* Set the address for storing the chrominance component data of the captured bottom-field data (8-pixel units). */
#define R_CEU_CDBCR_B_CBCR_MASK                   0xffffffff

/* CBDSR_B Register bit definitions */
#define R_CEU_CBDSR_B_CBVS_SHIFT                  (0)  /* Select the number of lines or number of bytes for output to the memory in a bundle write. */
#define R_CEU_CBDSR_B_CBVS_MASK                   0x7fffff

/* CLFCR_B Register bit definitions */
#define R_CEU_CLFCR_B_LPF                         (1 << 0)  /* Enables or disables operation of the low-pass filter. */

/* CDOCR_B Register bit definitions */
#define R_CEU_CDOCR_B_COBS                        (1 << 0)  /* Controls swapping in 8-bit units for data output from the CEU. */

#define R_CEU_CDOCR_B_COWS                        (1 << 1)  /* Controls swapping in 16-bit units for data output from the CEU. */

#define R_CEU_CDOCR_B_COLS                        (1 << 2)  /* Controls swapping in 32-bit units for data output from the CEU. */

#define R_CEU_CDOCR_B_CDS                         (1 << 4)  /* Sets the image format when outputting the image data captured in the YCbCr422 format to the memory. */

#define R_CEU_CDOCR_B_CBE                         (1 << 16)  /*  Controls the number of lines of captured data to be written to the memory. */

/* CDAYR2_B Register bit definitions */
#define R_CEU_CDAYR2_B_CAYR2_SHIFT                (0)  /* Capture Data Address Y */
#define R_CEU_CDAYR2_B_CAYR2_MASK                 0xffffffff

/* CDACR2_B Register bit definitions */
#define R_CEU_CDACR2_B_CACR2_SHIFT                (0)  /* Capture Data Address C */
#define R_CEU_CDACR2_B_CACR2_MASK                 0xffffffff

/* CDBYR2_B Register bit definitions */
#define R_CEU_CDBYR2_B_CBYR2_SHIFT                (0)  /* Set the address for storing the luminance component data of the captured bottom-field data (8-pixel units). */
#define R_CEU_CDBYR2_B_CBYR2_MASK                 0xffffffff

/* CDBCR2_B Register bit definitions */
#define R_CEU_CDBCR2_B_CBCR2_SHIFT                (0)  /* Set the address for storing the chrominance component data of the captured bottom-field data (8-pixel units). */
#define R_CEU_CDBCR2_B_CBCR2_MASK                 0xffffffff

/* CAMOR_M Register bit definitions */
#define R_CEU_CAMOR_M_HOFST_SHIFT                 (0)  /* Specify the capture start location in terms of the number of clock cycles from a horizontal sync signal (1-cycle units). */
#define R_CEU_CAMOR_M_HOFST_MASK                  0x1fff

#define R_CEU_CAMOR_M_VOFST_SHIFT                 (16)  /* Specify the capture start location in terms of the HD count from a vertical sync signal (1-HD units). */
#define R_CEU_CAMOR_M_VOFST_MASK                  0xfff0000

/* CAPWR_M Register bit definitions */
#define R_CEU_CAPWR_M_HWDTH_SHIFT                 (0)  /* Specify the horizontal capture period. */
#define R_CEU_CAPWR_M_HWDTH_MASK                  0x1fff

#define R_CEU_CAPWR_M_VWDTH_SHIFT                 (16)  /* Specify the vertical capture period (4-HD units). */
#define R_CEU_CAPWR_M_VWDTH_MASK                  0xfff0000

/* CFLCR_M Register bit definitions */
#define R_CEU_CFLCR_M_HFRAC_SHIFT                 (0)  /* Fraction Part of Horizontal Scale-Down Factor */
#define R_CEU_CFLCR_M_HFRAC_MASK                  0xfff

#define R_CEU_CFLCR_M_HMANT_SHIFT                 (12)  /* Mantissa Part of Horizontal Scale-Down Factor */
#define R_CEU_CFLCR_M_HMANT_MASK                  0xf000

#define R_CEU_CFLCR_M_VFRAC_SHIFT                 (16)  /* Fraction Part of Vertical Scale-Down Factor */
#define R_CEU_CFLCR_M_VFRAC_MASK                  0xfff0000

#define R_CEU_CFLCR_M_VMANT_SHIFT                 (28)  /* Mantissa Part of Vertical Scale-Down Factor */
#define R_CEU_CFLCR_M_VMANT_MASK                  0xf0000000

/* CFSZR_M Register bit definitions */
#define R_CEU_CFSZR_M_HFCLP_SHIFT                 (0)  /* Specify the horizontal clipping value of the filter output size (8-pixel units). */
#define R_CEU_CFSZR_M_HFCLP_MASK                  0xfff

#define R_CEU_CFSZR_M_VFCLP_SHIFT                 (16)  /* Specify the vertical clipping value of the filter output size (4-pixel units). */
#define R_CEU_CFSZR_M_VFCLP_MASK                  0xfff0000

/* CDWDR_M Register bit definitions */
#define R_CEU_CDWDR_M_CHDW_SHIFT                  (0)  /* Specify the horizontal image size in the memory area where the captured image is to be stored (8-byte units). */
#define R_CEU_CDWDR_M_CHDW_MASK                   0x1fff

/* CDAYR_M Register bit definitions */
#define R_CEU_CDAYR_M_CAYR_SHIFT                  (0)  /* Capture Data Address Y */
#define R_CEU_CDAYR_M_CAYR_MASK                   0xffffffff

/* CDACR_M Register bit definitions */
#define R_CEU_CDACR_M_CACR_SHIFT                  (0)  /* Capture Data Address C */
#define R_CEU_CDACR_M_CACR_MASK                   0xffffffff

/* CDBYR_M Register bit definitions */
#define R_CEU_CDBYR_M_CBYR_SHIFT                  (0)  /* Set the address for storing the luminance component data of the captured bottom-field data (8-pixel units). */
#define R_CEU_CDBYR_M_CBYR_MASK                   0xffffffff

/* CDBCR_M Register bit definitions */
#define R_CEU_CDBCR_M_CBCR_SHIFT                  (0)  /* Set the address for storing the chrominance component data of the captured bottom-field data (8-pixel units). */
#define R_CEU_CDBCR_M_CBCR_MASK                   0xffffffff

/* CBDSR_M Register bit definitions */
#define R_CEU_CBDSR_M_CBVS_SHIFT                  (0)  /* Select the number of lines or number of bytes for output to the memory in a bundle write. */
#define R_CEU_CBDSR_M_CBVS_MASK                   0x7fffff

/* CLFCR_M Register bit definitions */
#define R_CEU_CLFCR_M_LPF                         (1 << 0)  /* Enables or disables operation of the low-pass filter. */

/* CDOCR_M Register bit definitions */
#define R_CEU_CDOCR_M_COBS                        (1 << 0)  /* Controls swapping in 8-bit units for data output from the CEU. */

#define R_CEU_CDOCR_M_COWS                        (1 << 1)  /* Controls swapping in 16-bit units for data output from the CEU. */

#define R_CEU_CDOCR_M_COLS                        (1 << 2)  /* Controls swapping in 32-bit units for data output from the CEU. */

#define R_CEU_CDOCR_M_CDS                         (1 << 4)  /* Sets the image format when outputting the image data captured in the YCbCr422 format to the memory. */

#define R_CEU_CDOCR_M_CBE                         (1 << 16)  /*  Controls the number of lines of captured data to be written to the memory. */

/* CDAYR2_M Register bit definitions */
#define R_CEU_CDAYR2_M_CAYR2_SHIFT                (0)  /* Capture Data Address Y */
#define R_CEU_CDAYR2_M_CAYR2_MASK                 0xffffffff

/* CDACR2_M Register bit definitions */
#define R_CEU_CDACR2_M_CACR2_SHIFT                (0)  /* Capture Data Address C */
#define R_CEU_CDACR2_M_CACR2_MASK                 0xffffffff

/* CDBYR2_M Register bit definitions */
#define R_CEU_CDBYR2_M_CBYR2_SHIFT                (0)  /* Set the address for storing the luminance component data of the captured bottom-field data (8-pixel units). */
#define R_CEU_CDBYR2_M_CBYR2_MASK                 0xffffffff

/* CDBCR2_M Register bit definitions */
#define R_CEU_CDBCR2_M_CBCR2_SHIFT                (0)  /* Set the address for storing the chrominance component data of the captured bottom-field data (8-pixel units). */
#define R_CEU_CDBCR2_M_CBCR2_MASK                 0xffffffff


/* Maximum number of channels */

#define CEU_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CEU_H */

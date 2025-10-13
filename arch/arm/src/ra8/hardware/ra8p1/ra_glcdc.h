/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_glcdc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GLCDC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GLCDC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GLCDC Base Address */
#ifndef R_GLCDC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_GLCDC_BASE           0x40342000
#else
#define R_GLCDC_BASE           0x50342000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_GLCDC_CH_STRIDE    0x00000004
#define R_GLCDC_CH_BASE(ch)   (R_GLCDC_BASE + ((uint32_t)(ch) * R_GLCDC_CH_STRIDE))

/* GLCDC Register Offsets */

/* GR1_CLUT0%s Registers (0-255) */
#define R_GLCDC_GR1_CLUT0000_OFFSET     0x00000000  /* Color Palette */
#define R_GLCDC_GR1_CLUT0001_OFFSET     0x00000004  /* Color Palette */
#define R_GLCDC_GR1_CLUT0002_OFFSET     0x00000008  /* Color Palette */
#define R_GLCDC_GR1_CLUT0003_OFFSET     0x0000000c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0004_OFFSET     0x00000010  /* Color Palette */
#define R_GLCDC_GR1_CLUT0005_OFFSET     0x00000014  /* Color Palette */
#define R_GLCDC_GR1_CLUT0006_OFFSET     0x00000018  /* Color Palette */
#define R_GLCDC_GR1_CLUT0007_OFFSET     0x0000001c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0008_OFFSET     0x00000020  /* Color Palette */
#define R_GLCDC_GR1_CLUT0009_OFFSET     0x00000024  /* Color Palette */
#define R_GLCDC_GR1_CLUT0010_OFFSET     0x00000028  /* Color Palette */
#define R_GLCDC_GR1_CLUT0011_OFFSET     0x0000002c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0012_OFFSET     0x00000030  /* Color Palette */
#define R_GLCDC_GR1_CLUT0013_OFFSET     0x00000034  /* Color Palette */
#define R_GLCDC_GR1_CLUT0014_OFFSET     0x00000038  /* Color Palette */
#define R_GLCDC_GR1_CLUT0015_OFFSET     0x0000003c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0016_OFFSET     0x00000040  /* Color Palette */
#define R_GLCDC_GR1_CLUT0017_OFFSET     0x00000044  /* Color Palette */
#define R_GLCDC_GR1_CLUT0018_OFFSET     0x00000048  /* Color Palette */
#define R_GLCDC_GR1_CLUT0019_OFFSET     0x0000004c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0020_OFFSET     0x00000050  /* Color Palette */
#define R_GLCDC_GR1_CLUT0021_OFFSET     0x00000054  /* Color Palette */
#define R_GLCDC_GR1_CLUT0022_OFFSET     0x00000058  /* Color Palette */
#define R_GLCDC_GR1_CLUT0023_OFFSET     0x0000005c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0024_OFFSET     0x00000060  /* Color Palette */
#define R_GLCDC_GR1_CLUT0025_OFFSET     0x00000064  /* Color Palette */
#define R_GLCDC_GR1_CLUT0026_OFFSET     0x00000068  /* Color Palette */
#define R_GLCDC_GR1_CLUT0027_OFFSET     0x0000006c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0028_OFFSET     0x00000070  /* Color Palette */
#define R_GLCDC_GR1_CLUT0029_OFFSET     0x00000074  /* Color Palette */
#define R_GLCDC_GR1_CLUT0030_OFFSET     0x00000078  /* Color Palette */
#define R_GLCDC_GR1_CLUT0031_OFFSET     0x0000007c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0032_OFFSET     0x00000080  /* Color Palette */
#define R_GLCDC_GR1_CLUT0033_OFFSET     0x00000084  /* Color Palette */
#define R_GLCDC_GR1_CLUT0034_OFFSET     0x00000088  /* Color Palette */
#define R_GLCDC_GR1_CLUT0035_OFFSET     0x0000008c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0036_OFFSET     0x00000090  /* Color Palette */
#define R_GLCDC_GR1_CLUT0037_OFFSET     0x00000094  /* Color Palette */
#define R_GLCDC_GR1_CLUT0038_OFFSET     0x00000098  /* Color Palette */
#define R_GLCDC_GR1_CLUT0039_OFFSET     0x0000009c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0040_OFFSET     0x000000a0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0041_OFFSET     0x000000a4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0042_OFFSET     0x000000a8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0043_OFFSET     0x000000ac  /* Color Palette */
#define R_GLCDC_GR1_CLUT0044_OFFSET     0x000000b0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0045_OFFSET     0x000000b4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0046_OFFSET     0x000000b8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0047_OFFSET     0x000000bc  /* Color Palette */
#define R_GLCDC_GR1_CLUT0048_OFFSET     0x000000c0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0049_OFFSET     0x000000c4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0050_OFFSET     0x000000c8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0051_OFFSET     0x000000cc  /* Color Palette */
#define R_GLCDC_GR1_CLUT0052_OFFSET     0x000000d0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0053_OFFSET     0x000000d4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0054_OFFSET     0x000000d8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0055_OFFSET     0x000000dc  /* Color Palette */
#define R_GLCDC_GR1_CLUT0056_OFFSET     0x000000e0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0057_OFFSET     0x000000e4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0058_OFFSET     0x000000e8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0059_OFFSET     0x000000ec  /* Color Palette */
#define R_GLCDC_GR1_CLUT0060_OFFSET     0x000000f0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0061_OFFSET     0x000000f4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0062_OFFSET     0x000000f8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0063_OFFSET     0x000000fc  /* Color Palette */
#define R_GLCDC_GR1_CLUT0064_OFFSET     0x00000100  /* Color Palette */
#define R_GLCDC_GR1_CLUT0065_OFFSET     0x00000104  /* Color Palette */
#define R_GLCDC_GR1_CLUT0066_OFFSET     0x00000108  /* Color Palette */
#define R_GLCDC_GR1_CLUT0067_OFFSET     0x0000010c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0068_OFFSET     0x00000110  /* Color Palette */
#define R_GLCDC_GR1_CLUT0069_OFFSET     0x00000114  /* Color Palette */
#define R_GLCDC_GR1_CLUT0070_OFFSET     0x00000118  /* Color Palette */
#define R_GLCDC_GR1_CLUT0071_OFFSET     0x0000011c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0072_OFFSET     0x00000120  /* Color Palette */
#define R_GLCDC_GR1_CLUT0073_OFFSET     0x00000124  /* Color Palette */
#define R_GLCDC_GR1_CLUT0074_OFFSET     0x00000128  /* Color Palette */
#define R_GLCDC_GR1_CLUT0075_OFFSET     0x0000012c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0076_OFFSET     0x00000130  /* Color Palette */
#define R_GLCDC_GR1_CLUT0077_OFFSET     0x00000134  /* Color Palette */
#define R_GLCDC_GR1_CLUT0078_OFFSET     0x00000138  /* Color Palette */
#define R_GLCDC_GR1_CLUT0079_OFFSET     0x0000013c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0080_OFFSET     0x00000140  /* Color Palette */
#define R_GLCDC_GR1_CLUT0081_OFFSET     0x00000144  /* Color Palette */
#define R_GLCDC_GR1_CLUT0082_OFFSET     0x00000148  /* Color Palette */
#define R_GLCDC_GR1_CLUT0083_OFFSET     0x0000014c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0084_OFFSET     0x00000150  /* Color Palette */
#define R_GLCDC_GR1_CLUT0085_OFFSET     0x00000154  /* Color Palette */
#define R_GLCDC_GR1_CLUT0086_OFFSET     0x00000158  /* Color Palette */
#define R_GLCDC_GR1_CLUT0087_OFFSET     0x0000015c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0088_OFFSET     0x00000160  /* Color Palette */
#define R_GLCDC_GR1_CLUT0089_OFFSET     0x00000164  /* Color Palette */
#define R_GLCDC_GR1_CLUT0090_OFFSET     0x00000168  /* Color Palette */
#define R_GLCDC_GR1_CLUT0091_OFFSET     0x0000016c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0092_OFFSET     0x00000170  /* Color Palette */
#define R_GLCDC_GR1_CLUT0093_OFFSET     0x00000174  /* Color Palette */
#define R_GLCDC_GR1_CLUT0094_OFFSET     0x00000178  /* Color Palette */
#define R_GLCDC_GR1_CLUT0095_OFFSET     0x0000017c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0096_OFFSET     0x00000180  /* Color Palette */
#define R_GLCDC_GR1_CLUT0097_OFFSET     0x00000184  /* Color Palette */
#define R_GLCDC_GR1_CLUT0098_OFFSET     0x00000188  /* Color Palette */
#define R_GLCDC_GR1_CLUT0099_OFFSET     0x0000018c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0100_OFFSET     0x00000190  /* Color Palette */
#define R_GLCDC_GR1_CLUT0101_OFFSET     0x00000194  /* Color Palette */
#define R_GLCDC_GR1_CLUT0102_OFFSET     0x00000198  /* Color Palette */
#define R_GLCDC_GR1_CLUT0103_OFFSET     0x0000019c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0104_OFFSET     0x000001a0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0105_OFFSET     0x000001a4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0106_OFFSET     0x000001a8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0107_OFFSET     0x000001ac  /* Color Palette */
#define R_GLCDC_GR1_CLUT0108_OFFSET     0x000001b0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0109_OFFSET     0x000001b4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0110_OFFSET     0x000001b8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0111_OFFSET     0x000001bc  /* Color Palette */
#define R_GLCDC_GR1_CLUT0112_OFFSET     0x000001c0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0113_OFFSET     0x000001c4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0114_OFFSET     0x000001c8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0115_OFFSET     0x000001cc  /* Color Palette */
#define R_GLCDC_GR1_CLUT0116_OFFSET     0x000001d0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0117_OFFSET     0x000001d4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0118_OFFSET     0x000001d8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0119_OFFSET     0x000001dc  /* Color Palette */
#define R_GLCDC_GR1_CLUT0120_OFFSET     0x000001e0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0121_OFFSET     0x000001e4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0122_OFFSET     0x000001e8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0123_OFFSET     0x000001ec  /* Color Palette */
#define R_GLCDC_GR1_CLUT0124_OFFSET     0x000001f0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0125_OFFSET     0x000001f4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0126_OFFSET     0x000001f8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0127_OFFSET     0x000001fc  /* Color Palette */
#define R_GLCDC_GR1_CLUT0128_OFFSET     0x00000200  /* Color Palette */
#define R_GLCDC_GR1_CLUT0129_OFFSET     0x00000204  /* Color Palette */
#define R_GLCDC_GR1_CLUT0130_OFFSET     0x00000208  /* Color Palette */
#define R_GLCDC_GR1_CLUT0131_OFFSET     0x0000020c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0132_OFFSET     0x00000210  /* Color Palette */
#define R_GLCDC_GR1_CLUT0133_OFFSET     0x00000214  /* Color Palette */
#define R_GLCDC_GR1_CLUT0134_OFFSET     0x00000218  /* Color Palette */
#define R_GLCDC_GR1_CLUT0135_OFFSET     0x0000021c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0136_OFFSET     0x00000220  /* Color Palette */
#define R_GLCDC_GR1_CLUT0137_OFFSET     0x00000224  /* Color Palette */
#define R_GLCDC_GR1_CLUT0138_OFFSET     0x00000228  /* Color Palette */
#define R_GLCDC_GR1_CLUT0139_OFFSET     0x0000022c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0140_OFFSET     0x00000230  /* Color Palette */
#define R_GLCDC_GR1_CLUT0141_OFFSET     0x00000234  /* Color Palette */
#define R_GLCDC_GR1_CLUT0142_OFFSET     0x00000238  /* Color Palette */
#define R_GLCDC_GR1_CLUT0143_OFFSET     0x0000023c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0144_OFFSET     0x00000240  /* Color Palette */
#define R_GLCDC_GR1_CLUT0145_OFFSET     0x00000244  /* Color Palette */
#define R_GLCDC_GR1_CLUT0146_OFFSET     0x00000248  /* Color Palette */
#define R_GLCDC_GR1_CLUT0147_OFFSET     0x0000024c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0148_OFFSET     0x00000250  /* Color Palette */
#define R_GLCDC_GR1_CLUT0149_OFFSET     0x00000254  /* Color Palette */
#define R_GLCDC_GR1_CLUT0150_OFFSET     0x00000258  /* Color Palette */
#define R_GLCDC_GR1_CLUT0151_OFFSET     0x0000025c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0152_OFFSET     0x00000260  /* Color Palette */
#define R_GLCDC_GR1_CLUT0153_OFFSET     0x00000264  /* Color Palette */
#define R_GLCDC_GR1_CLUT0154_OFFSET     0x00000268  /* Color Palette */
#define R_GLCDC_GR1_CLUT0155_OFFSET     0x0000026c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0156_OFFSET     0x00000270  /* Color Palette */
#define R_GLCDC_GR1_CLUT0157_OFFSET     0x00000274  /* Color Palette */
#define R_GLCDC_GR1_CLUT0158_OFFSET     0x00000278  /* Color Palette */
#define R_GLCDC_GR1_CLUT0159_OFFSET     0x0000027c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0160_OFFSET     0x00000280  /* Color Palette */
#define R_GLCDC_GR1_CLUT0161_OFFSET     0x00000284  /* Color Palette */
#define R_GLCDC_GR1_CLUT0162_OFFSET     0x00000288  /* Color Palette */
#define R_GLCDC_GR1_CLUT0163_OFFSET     0x0000028c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0164_OFFSET     0x00000290  /* Color Palette */
#define R_GLCDC_GR1_CLUT0165_OFFSET     0x00000294  /* Color Palette */
#define R_GLCDC_GR1_CLUT0166_OFFSET     0x00000298  /* Color Palette */
#define R_GLCDC_GR1_CLUT0167_OFFSET     0x0000029c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0168_OFFSET     0x000002a0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0169_OFFSET     0x000002a4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0170_OFFSET     0x000002a8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0171_OFFSET     0x000002ac  /* Color Palette */
#define R_GLCDC_GR1_CLUT0172_OFFSET     0x000002b0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0173_OFFSET     0x000002b4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0174_OFFSET     0x000002b8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0175_OFFSET     0x000002bc  /* Color Palette */
#define R_GLCDC_GR1_CLUT0176_OFFSET     0x000002c0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0177_OFFSET     0x000002c4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0178_OFFSET     0x000002c8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0179_OFFSET     0x000002cc  /* Color Palette */
#define R_GLCDC_GR1_CLUT0180_OFFSET     0x000002d0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0181_OFFSET     0x000002d4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0182_OFFSET     0x000002d8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0183_OFFSET     0x000002dc  /* Color Palette */
#define R_GLCDC_GR1_CLUT0184_OFFSET     0x000002e0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0185_OFFSET     0x000002e4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0186_OFFSET     0x000002e8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0187_OFFSET     0x000002ec  /* Color Palette */
#define R_GLCDC_GR1_CLUT0188_OFFSET     0x000002f0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0189_OFFSET     0x000002f4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0190_OFFSET     0x000002f8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0191_OFFSET     0x000002fc  /* Color Palette */
#define R_GLCDC_GR1_CLUT0192_OFFSET     0x00000300  /* Color Palette */
#define R_GLCDC_GR1_CLUT0193_OFFSET     0x00000304  /* Color Palette */
#define R_GLCDC_GR1_CLUT0194_OFFSET     0x00000308  /* Color Palette */
#define R_GLCDC_GR1_CLUT0195_OFFSET     0x0000030c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0196_OFFSET     0x00000310  /* Color Palette */
#define R_GLCDC_GR1_CLUT0197_OFFSET     0x00000314  /* Color Palette */
#define R_GLCDC_GR1_CLUT0198_OFFSET     0x00000318  /* Color Palette */
#define R_GLCDC_GR1_CLUT0199_OFFSET     0x0000031c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0200_OFFSET     0x00000320  /* Color Palette */
#define R_GLCDC_GR1_CLUT0201_OFFSET     0x00000324  /* Color Palette */
#define R_GLCDC_GR1_CLUT0202_OFFSET     0x00000328  /* Color Palette */
#define R_GLCDC_GR1_CLUT0203_OFFSET     0x0000032c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0204_OFFSET     0x00000330  /* Color Palette */
#define R_GLCDC_GR1_CLUT0205_OFFSET     0x00000334  /* Color Palette */
#define R_GLCDC_GR1_CLUT0206_OFFSET     0x00000338  /* Color Palette */
#define R_GLCDC_GR1_CLUT0207_OFFSET     0x0000033c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0208_OFFSET     0x00000340  /* Color Palette */
#define R_GLCDC_GR1_CLUT0209_OFFSET     0x00000344  /* Color Palette */
#define R_GLCDC_GR1_CLUT0210_OFFSET     0x00000348  /* Color Palette */
#define R_GLCDC_GR1_CLUT0211_OFFSET     0x0000034c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0212_OFFSET     0x00000350  /* Color Palette */
#define R_GLCDC_GR1_CLUT0213_OFFSET     0x00000354  /* Color Palette */
#define R_GLCDC_GR1_CLUT0214_OFFSET     0x00000358  /* Color Palette */
#define R_GLCDC_GR1_CLUT0215_OFFSET     0x0000035c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0216_OFFSET     0x00000360  /* Color Palette */
#define R_GLCDC_GR1_CLUT0217_OFFSET     0x00000364  /* Color Palette */
#define R_GLCDC_GR1_CLUT0218_OFFSET     0x00000368  /* Color Palette */
#define R_GLCDC_GR1_CLUT0219_OFFSET     0x0000036c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0220_OFFSET     0x00000370  /* Color Palette */
#define R_GLCDC_GR1_CLUT0221_OFFSET     0x00000374  /* Color Palette */
#define R_GLCDC_GR1_CLUT0222_OFFSET     0x00000378  /* Color Palette */
#define R_GLCDC_GR1_CLUT0223_OFFSET     0x0000037c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0224_OFFSET     0x00000380  /* Color Palette */
#define R_GLCDC_GR1_CLUT0225_OFFSET     0x00000384  /* Color Palette */
#define R_GLCDC_GR1_CLUT0226_OFFSET     0x00000388  /* Color Palette */
#define R_GLCDC_GR1_CLUT0227_OFFSET     0x0000038c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0228_OFFSET     0x00000390  /* Color Palette */
#define R_GLCDC_GR1_CLUT0229_OFFSET     0x00000394  /* Color Palette */
#define R_GLCDC_GR1_CLUT0230_OFFSET     0x00000398  /* Color Palette */
#define R_GLCDC_GR1_CLUT0231_OFFSET     0x0000039c  /* Color Palette */
#define R_GLCDC_GR1_CLUT0232_OFFSET     0x000003a0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0233_OFFSET     0x000003a4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0234_OFFSET     0x000003a8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0235_OFFSET     0x000003ac  /* Color Palette */
#define R_GLCDC_GR1_CLUT0236_OFFSET     0x000003b0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0237_OFFSET     0x000003b4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0238_OFFSET     0x000003b8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0239_OFFSET     0x000003bc  /* Color Palette */
#define R_GLCDC_GR1_CLUT0240_OFFSET     0x000003c0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0241_OFFSET     0x000003c4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0242_OFFSET     0x000003c8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0243_OFFSET     0x000003cc  /* Color Palette */
#define R_GLCDC_GR1_CLUT0244_OFFSET     0x000003d0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0245_OFFSET     0x000003d4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0246_OFFSET     0x000003d8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0247_OFFSET     0x000003dc  /* Color Palette */
#define R_GLCDC_GR1_CLUT0248_OFFSET     0x000003e0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0249_OFFSET     0x000003e4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0250_OFFSET     0x000003e8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0251_OFFSET     0x000003ec  /* Color Palette */
#define R_GLCDC_GR1_CLUT0252_OFFSET     0x000003f0  /* Color Palette */
#define R_GLCDC_GR1_CLUT0253_OFFSET     0x000003f4  /* Color Palette */
#define R_GLCDC_GR1_CLUT0254_OFFSET     0x000003f8  /* Color Palette */
#define R_GLCDC_GR1_CLUT0255_OFFSET     0x000003fc  /* Color Palette */
/* GR1_CLUT1%s Registers (0-255) */
#define R_GLCDC_GR1_CLUT1000_OFFSET     0x00000400  /* Color Palette */
#define R_GLCDC_GR1_CLUT1001_OFFSET     0x00000404  /* Color Palette */
#define R_GLCDC_GR1_CLUT1002_OFFSET     0x00000408  /* Color Palette */
#define R_GLCDC_GR1_CLUT1003_OFFSET     0x0000040c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1004_OFFSET     0x00000410  /* Color Palette */
#define R_GLCDC_GR1_CLUT1005_OFFSET     0x00000414  /* Color Palette */
#define R_GLCDC_GR1_CLUT1006_OFFSET     0x00000418  /* Color Palette */
#define R_GLCDC_GR1_CLUT1007_OFFSET     0x0000041c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1008_OFFSET     0x00000420  /* Color Palette */
#define R_GLCDC_GR1_CLUT1009_OFFSET     0x00000424  /* Color Palette */
#define R_GLCDC_GR1_CLUT1010_OFFSET     0x00000428  /* Color Palette */
#define R_GLCDC_GR1_CLUT1011_OFFSET     0x0000042c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1012_OFFSET     0x00000430  /* Color Palette */
#define R_GLCDC_GR1_CLUT1013_OFFSET     0x00000434  /* Color Palette */
#define R_GLCDC_GR1_CLUT1014_OFFSET     0x00000438  /* Color Palette */
#define R_GLCDC_GR1_CLUT1015_OFFSET     0x0000043c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1016_OFFSET     0x00000440  /* Color Palette */
#define R_GLCDC_GR1_CLUT1017_OFFSET     0x00000444  /* Color Palette */
#define R_GLCDC_GR1_CLUT1018_OFFSET     0x00000448  /* Color Palette */
#define R_GLCDC_GR1_CLUT1019_OFFSET     0x0000044c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1020_OFFSET     0x00000450  /* Color Palette */
#define R_GLCDC_GR1_CLUT1021_OFFSET     0x00000454  /* Color Palette */
#define R_GLCDC_GR1_CLUT1022_OFFSET     0x00000458  /* Color Palette */
#define R_GLCDC_GR1_CLUT1023_OFFSET     0x0000045c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1024_OFFSET     0x00000460  /* Color Palette */
#define R_GLCDC_GR1_CLUT1025_OFFSET     0x00000464  /* Color Palette */
#define R_GLCDC_GR1_CLUT1026_OFFSET     0x00000468  /* Color Palette */
#define R_GLCDC_GR1_CLUT1027_OFFSET     0x0000046c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1028_OFFSET     0x00000470  /* Color Palette */
#define R_GLCDC_GR1_CLUT1029_OFFSET     0x00000474  /* Color Palette */
#define R_GLCDC_GR1_CLUT1030_OFFSET     0x00000478  /* Color Palette */
#define R_GLCDC_GR1_CLUT1031_OFFSET     0x0000047c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1032_OFFSET     0x00000480  /* Color Palette */
#define R_GLCDC_GR1_CLUT1033_OFFSET     0x00000484  /* Color Palette */
#define R_GLCDC_GR1_CLUT1034_OFFSET     0x00000488  /* Color Palette */
#define R_GLCDC_GR1_CLUT1035_OFFSET     0x0000048c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1036_OFFSET     0x00000490  /* Color Palette */
#define R_GLCDC_GR1_CLUT1037_OFFSET     0x00000494  /* Color Palette */
#define R_GLCDC_GR1_CLUT1038_OFFSET     0x00000498  /* Color Palette */
#define R_GLCDC_GR1_CLUT1039_OFFSET     0x0000049c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1040_OFFSET     0x000004a0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1041_OFFSET     0x000004a4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1042_OFFSET     0x000004a8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1043_OFFSET     0x000004ac  /* Color Palette */
#define R_GLCDC_GR1_CLUT1044_OFFSET     0x000004b0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1045_OFFSET     0x000004b4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1046_OFFSET     0x000004b8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1047_OFFSET     0x000004bc  /* Color Palette */
#define R_GLCDC_GR1_CLUT1048_OFFSET     0x000004c0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1049_OFFSET     0x000004c4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1050_OFFSET     0x000004c8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1051_OFFSET     0x000004cc  /* Color Palette */
#define R_GLCDC_GR1_CLUT1052_OFFSET     0x000004d0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1053_OFFSET     0x000004d4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1054_OFFSET     0x000004d8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1055_OFFSET     0x000004dc  /* Color Palette */
#define R_GLCDC_GR1_CLUT1056_OFFSET     0x000004e0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1057_OFFSET     0x000004e4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1058_OFFSET     0x000004e8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1059_OFFSET     0x000004ec  /* Color Palette */
#define R_GLCDC_GR1_CLUT1060_OFFSET     0x000004f0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1061_OFFSET     0x000004f4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1062_OFFSET     0x000004f8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1063_OFFSET     0x000004fc  /* Color Palette */
#define R_GLCDC_GR1_CLUT1064_OFFSET     0x00000500  /* Color Palette */
#define R_GLCDC_GR1_CLUT1065_OFFSET     0x00000504  /* Color Palette */
#define R_GLCDC_GR1_CLUT1066_OFFSET     0x00000508  /* Color Palette */
#define R_GLCDC_GR1_CLUT1067_OFFSET     0x0000050c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1068_OFFSET     0x00000510  /* Color Palette */
#define R_GLCDC_GR1_CLUT1069_OFFSET     0x00000514  /* Color Palette */
#define R_GLCDC_GR1_CLUT1070_OFFSET     0x00000518  /* Color Palette */
#define R_GLCDC_GR1_CLUT1071_OFFSET     0x0000051c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1072_OFFSET     0x00000520  /* Color Palette */
#define R_GLCDC_GR1_CLUT1073_OFFSET     0x00000524  /* Color Palette */
#define R_GLCDC_GR1_CLUT1074_OFFSET     0x00000528  /* Color Palette */
#define R_GLCDC_GR1_CLUT1075_OFFSET     0x0000052c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1076_OFFSET     0x00000530  /* Color Palette */
#define R_GLCDC_GR1_CLUT1077_OFFSET     0x00000534  /* Color Palette */
#define R_GLCDC_GR1_CLUT1078_OFFSET     0x00000538  /* Color Palette */
#define R_GLCDC_GR1_CLUT1079_OFFSET     0x0000053c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1080_OFFSET     0x00000540  /* Color Palette */
#define R_GLCDC_GR1_CLUT1081_OFFSET     0x00000544  /* Color Palette */
#define R_GLCDC_GR1_CLUT1082_OFFSET     0x00000548  /* Color Palette */
#define R_GLCDC_GR1_CLUT1083_OFFSET     0x0000054c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1084_OFFSET     0x00000550  /* Color Palette */
#define R_GLCDC_GR1_CLUT1085_OFFSET     0x00000554  /* Color Palette */
#define R_GLCDC_GR1_CLUT1086_OFFSET     0x00000558  /* Color Palette */
#define R_GLCDC_GR1_CLUT1087_OFFSET     0x0000055c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1088_OFFSET     0x00000560  /* Color Palette */
#define R_GLCDC_GR1_CLUT1089_OFFSET     0x00000564  /* Color Palette */
#define R_GLCDC_GR1_CLUT1090_OFFSET     0x00000568  /* Color Palette */
#define R_GLCDC_GR1_CLUT1091_OFFSET     0x0000056c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1092_OFFSET     0x00000570  /* Color Palette */
#define R_GLCDC_GR1_CLUT1093_OFFSET     0x00000574  /* Color Palette */
#define R_GLCDC_GR1_CLUT1094_OFFSET     0x00000578  /* Color Palette */
#define R_GLCDC_GR1_CLUT1095_OFFSET     0x0000057c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1096_OFFSET     0x00000580  /* Color Palette */
#define R_GLCDC_GR1_CLUT1097_OFFSET     0x00000584  /* Color Palette */
#define R_GLCDC_GR1_CLUT1098_OFFSET     0x00000588  /* Color Palette */
#define R_GLCDC_GR1_CLUT1099_OFFSET     0x0000058c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1100_OFFSET     0x00000590  /* Color Palette */
#define R_GLCDC_GR1_CLUT1101_OFFSET     0x00000594  /* Color Palette */
#define R_GLCDC_GR1_CLUT1102_OFFSET     0x00000598  /* Color Palette */
#define R_GLCDC_GR1_CLUT1103_OFFSET     0x0000059c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1104_OFFSET     0x000005a0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1105_OFFSET     0x000005a4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1106_OFFSET     0x000005a8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1107_OFFSET     0x000005ac  /* Color Palette */
#define R_GLCDC_GR1_CLUT1108_OFFSET     0x000005b0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1109_OFFSET     0x000005b4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1110_OFFSET     0x000005b8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1111_OFFSET     0x000005bc  /* Color Palette */
#define R_GLCDC_GR1_CLUT1112_OFFSET     0x000005c0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1113_OFFSET     0x000005c4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1114_OFFSET     0x000005c8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1115_OFFSET     0x000005cc  /* Color Palette */
#define R_GLCDC_GR1_CLUT1116_OFFSET     0x000005d0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1117_OFFSET     0x000005d4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1118_OFFSET     0x000005d8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1119_OFFSET     0x000005dc  /* Color Palette */
#define R_GLCDC_GR1_CLUT1120_OFFSET     0x000005e0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1121_OFFSET     0x000005e4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1122_OFFSET     0x000005e8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1123_OFFSET     0x000005ec  /* Color Palette */
#define R_GLCDC_GR1_CLUT1124_OFFSET     0x000005f0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1125_OFFSET     0x000005f4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1126_OFFSET     0x000005f8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1127_OFFSET     0x000005fc  /* Color Palette */
#define R_GLCDC_GR1_CLUT1128_OFFSET     0x00000600  /* Color Palette */
#define R_GLCDC_GR1_CLUT1129_OFFSET     0x00000604  /* Color Palette */
#define R_GLCDC_GR1_CLUT1130_OFFSET     0x00000608  /* Color Palette */
#define R_GLCDC_GR1_CLUT1131_OFFSET     0x0000060c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1132_OFFSET     0x00000610  /* Color Palette */
#define R_GLCDC_GR1_CLUT1133_OFFSET     0x00000614  /* Color Palette */
#define R_GLCDC_GR1_CLUT1134_OFFSET     0x00000618  /* Color Palette */
#define R_GLCDC_GR1_CLUT1135_OFFSET     0x0000061c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1136_OFFSET     0x00000620  /* Color Palette */
#define R_GLCDC_GR1_CLUT1137_OFFSET     0x00000624  /* Color Palette */
#define R_GLCDC_GR1_CLUT1138_OFFSET     0x00000628  /* Color Palette */
#define R_GLCDC_GR1_CLUT1139_OFFSET     0x0000062c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1140_OFFSET     0x00000630  /* Color Palette */
#define R_GLCDC_GR1_CLUT1141_OFFSET     0x00000634  /* Color Palette */
#define R_GLCDC_GR1_CLUT1142_OFFSET     0x00000638  /* Color Palette */
#define R_GLCDC_GR1_CLUT1143_OFFSET     0x0000063c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1144_OFFSET     0x00000640  /* Color Palette */
#define R_GLCDC_GR1_CLUT1145_OFFSET     0x00000644  /* Color Palette */
#define R_GLCDC_GR1_CLUT1146_OFFSET     0x00000648  /* Color Palette */
#define R_GLCDC_GR1_CLUT1147_OFFSET     0x0000064c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1148_OFFSET     0x00000650  /* Color Palette */
#define R_GLCDC_GR1_CLUT1149_OFFSET     0x00000654  /* Color Palette */
#define R_GLCDC_GR1_CLUT1150_OFFSET     0x00000658  /* Color Palette */
#define R_GLCDC_GR1_CLUT1151_OFFSET     0x0000065c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1152_OFFSET     0x00000660  /* Color Palette */
#define R_GLCDC_GR1_CLUT1153_OFFSET     0x00000664  /* Color Palette */
#define R_GLCDC_GR1_CLUT1154_OFFSET     0x00000668  /* Color Palette */
#define R_GLCDC_GR1_CLUT1155_OFFSET     0x0000066c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1156_OFFSET     0x00000670  /* Color Palette */
#define R_GLCDC_GR1_CLUT1157_OFFSET     0x00000674  /* Color Palette */
#define R_GLCDC_GR1_CLUT1158_OFFSET     0x00000678  /* Color Palette */
#define R_GLCDC_GR1_CLUT1159_OFFSET     0x0000067c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1160_OFFSET     0x00000680  /* Color Palette */
#define R_GLCDC_GR1_CLUT1161_OFFSET     0x00000684  /* Color Palette */
#define R_GLCDC_GR1_CLUT1162_OFFSET     0x00000688  /* Color Palette */
#define R_GLCDC_GR1_CLUT1163_OFFSET     0x0000068c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1164_OFFSET     0x00000690  /* Color Palette */
#define R_GLCDC_GR1_CLUT1165_OFFSET     0x00000694  /* Color Palette */
#define R_GLCDC_GR1_CLUT1166_OFFSET     0x00000698  /* Color Palette */
#define R_GLCDC_GR1_CLUT1167_OFFSET     0x0000069c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1168_OFFSET     0x000006a0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1169_OFFSET     0x000006a4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1170_OFFSET     0x000006a8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1171_OFFSET     0x000006ac  /* Color Palette */
#define R_GLCDC_GR1_CLUT1172_OFFSET     0x000006b0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1173_OFFSET     0x000006b4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1174_OFFSET     0x000006b8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1175_OFFSET     0x000006bc  /* Color Palette */
#define R_GLCDC_GR1_CLUT1176_OFFSET     0x000006c0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1177_OFFSET     0x000006c4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1178_OFFSET     0x000006c8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1179_OFFSET     0x000006cc  /* Color Palette */
#define R_GLCDC_GR1_CLUT1180_OFFSET     0x000006d0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1181_OFFSET     0x000006d4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1182_OFFSET     0x000006d8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1183_OFFSET     0x000006dc  /* Color Palette */
#define R_GLCDC_GR1_CLUT1184_OFFSET     0x000006e0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1185_OFFSET     0x000006e4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1186_OFFSET     0x000006e8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1187_OFFSET     0x000006ec  /* Color Palette */
#define R_GLCDC_GR1_CLUT1188_OFFSET     0x000006f0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1189_OFFSET     0x000006f4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1190_OFFSET     0x000006f8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1191_OFFSET     0x000006fc  /* Color Palette */
#define R_GLCDC_GR1_CLUT1192_OFFSET     0x00000700  /* Color Palette */
#define R_GLCDC_GR1_CLUT1193_OFFSET     0x00000704  /* Color Palette */
#define R_GLCDC_GR1_CLUT1194_OFFSET     0x00000708  /* Color Palette */
#define R_GLCDC_GR1_CLUT1195_OFFSET     0x0000070c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1196_OFFSET     0x00000710  /* Color Palette */
#define R_GLCDC_GR1_CLUT1197_OFFSET     0x00000714  /* Color Palette */
#define R_GLCDC_GR1_CLUT1198_OFFSET     0x00000718  /* Color Palette */
#define R_GLCDC_GR1_CLUT1199_OFFSET     0x0000071c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1200_OFFSET     0x00000720  /* Color Palette */
#define R_GLCDC_GR1_CLUT1201_OFFSET     0x00000724  /* Color Palette */
#define R_GLCDC_GR1_CLUT1202_OFFSET     0x00000728  /* Color Palette */
#define R_GLCDC_GR1_CLUT1203_OFFSET     0x0000072c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1204_OFFSET     0x00000730  /* Color Palette */
#define R_GLCDC_GR1_CLUT1205_OFFSET     0x00000734  /* Color Palette */
#define R_GLCDC_GR1_CLUT1206_OFFSET     0x00000738  /* Color Palette */
#define R_GLCDC_GR1_CLUT1207_OFFSET     0x0000073c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1208_OFFSET     0x00000740  /* Color Palette */
#define R_GLCDC_GR1_CLUT1209_OFFSET     0x00000744  /* Color Palette */
#define R_GLCDC_GR1_CLUT1210_OFFSET     0x00000748  /* Color Palette */
#define R_GLCDC_GR1_CLUT1211_OFFSET     0x0000074c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1212_OFFSET     0x00000750  /* Color Palette */
#define R_GLCDC_GR1_CLUT1213_OFFSET     0x00000754  /* Color Palette */
#define R_GLCDC_GR1_CLUT1214_OFFSET     0x00000758  /* Color Palette */
#define R_GLCDC_GR1_CLUT1215_OFFSET     0x0000075c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1216_OFFSET     0x00000760  /* Color Palette */
#define R_GLCDC_GR1_CLUT1217_OFFSET     0x00000764  /* Color Palette */
#define R_GLCDC_GR1_CLUT1218_OFFSET     0x00000768  /* Color Palette */
#define R_GLCDC_GR1_CLUT1219_OFFSET     0x0000076c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1220_OFFSET     0x00000770  /* Color Palette */
#define R_GLCDC_GR1_CLUT1221_OFFSET     0x00000774  /* Color Palette */
#define R_GLCDC_GR1_CLUT1222_OFFSET     0x00000778  /* Color Palette */
#define R_GLCDC_GR1_CLUT1223_OFFSET     0x0000077c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1224_OFFSET     0x00000780  /* Color Palette */
#define R_GLCDC_GR1_CLUT1225_OFFSET     0x00000784  /* Color Palette */
#define R_GLCDC_GR1_CLUT1226_OFFSET     0x00000788  /* Color Palette */
#define R_GLCDC_GR1_CLUT1227_OFFSET     0x0000078c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1228_OFFSET     0x00000790  /* Color Palette */
#define R_GLCDC_GR1_CLUT1229_OFFSET     0x00000794  /* Color Palette */
#define R_GLCDC_GR1_CLUT1230_OFFSET     0x00000798  /* Color Palette */
#define R_GLCDC_GR1_CLUT1231_OFFSET     0x0000079c  /* Color Palette */
#define R_GLCDC_GR1_CLUT1232_OFFSET     0x000007a0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1233_OFFSET     0x000007a4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1234_OFFSET     0x000007a8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1235_OFFSET     0x000007ac  /* Color Palette */
#define R_GLCDC_GR1_CLUT1236_OFFSET     0x000007b0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1237_OFFSET     0x000007b4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1238_OFFSET     0x000007b8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1239_OFFSET     0x000007bc  /* Color Palette */
#define R_GLCDC_GR1_CLUT1240_OFFSET     0x000007c0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1241_OFFSET     0x000007c4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1242_OFFSET     0x000007c8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1243_OFFSET     0x000007cc  /* Color Palette */
#define R_GLCDC_GR1_CLUT1244_OFFSET     0x000007d0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1245_OFFSET     0x000007d4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1246_OFFSET     0x000007d8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1247_OFFSET     0x000007dc  /* Color Palette */
#define R_GLCDC_GR1_CLUT1248_OFFSET     0x000007e0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1249_OFFSET     0x000007e4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1250_OFFSET     0x000007e8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1251_OFFSET     0x000007ec  /* Color Palette */
#define R_GLCDC_GR1_CLUT1252_OFFSET     0x000007f0  /* Color Palette */
#define R_GLCDC_GR1_CLUT1253_OFFSET     0x000007f4  /* Color Palette */
#define R_GLCDC_GR1_CLUT1254_OFFSET     0x000007f8  /* Color Palette */
#define R_GLCDC_GR1_CLUT1255_OFFSET     0x000007fc  /* Color Palette */
/* GR2_CLUT0%s Registers (0-255) */
#define R_GLCDC_GR2_CLUT0000_OFFSET     0x00000800  /* Color Palette */
#define R_GLCDC_GR2_CLUT0001_OFFSET     0x00000804  /* Color Palette */
#define R_GLCDC_GR2_CLUT0002_OFFSET     0x00000808  /* Color Palette */
#define R_GLCDC_GR2_CLUT0003_OFFSET     0x0000080c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0004_OFFSET     0x00000810  /* Color Palette */
#define R_GLCDC_GR2_CLUT0005_OFFSET     0x00000814  /* Color Palette */
#define R_GLCDC_GR2_CLUT0006_OFFSET     0x00000818  /* Color Palette */
#define R_GLCDC_GR2_CLUT0007_OFFSET     0x0000081c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0008_OFFSET     0x00000820  /* Color Palette */
#define R_GLCDC_GR2_CLUT0009_OFFSET     0x00000824  /* Color Palette */
#define R_GLCDC_GR2_CLUT0010_OFFSET     0x00000828  /* Color Palette */
#define R_GLCDC_GR2_CLUT0011_OFFSET     0x0000082c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0012_OFFSET     0x00000830  /* Color Palette */
#define R_GLCDC_GR2_CLUT0013_OFFSET     0x00000834  /* Color Palette */
#define R_GLCDC_GR2_CLUT0014_OFFSET     0x00000838  /* Color Palette */
#define R_GLCDC_GR2_CLUT0015_OFFSET     0x0000083c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0016_OFFSET     0x00000840  /* Color Palette */
#define R_GLCDC_GR2_CLUT0017_OFFSET     0x00000844  /* Color Palette */
#define R_GLCDC_GR2_CLUT0018_OFFSET     0x00000848  /* Color Palette */
#define R_GLCDC_GR2_CLUT0019_OFFSET     0x0000084c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0020_OFFSET     0x00000850  /* Color Palette */
#define R_GLCDC_GR2_CLUT0021_OFFSET     0x00000854  /* Color Palette */
#define R_GLCDC_GR2_CLUT0022_OFFSET     0x00000858  /* Color Palette */
#define R_GLCDC_GR2_CLUT0023_OFFSET     0x0000085c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0024_OFFSET     0x00000860  /* Color Palette */
#define R_GLCDC_GR2_CLUT0025_OFFSET     0x00000864  /* Color Palette */
#define R_GLCDC_GR2_CLUT0026_OFFSET     0x00000868  /* Color Palette */
#define R_GLCDC_GR2_CLUT0027_OFFSET     0x0000086c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0028_OFFSET     0x00000870  /* Color Palette */
#define R_GLCDC_GR2_CLUT0029_OFFSET     0x00000874  /* Color Palette */
#define R_GLCDC_GR2_CLUT0030_OFFSET     0x00000878  /* Color Palette */
#define R_GLCDC_GR2_CLUT0031_OFFSET     0x0000087c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0032_OFFSET     0x00000880  /* Color Palette */
#define R_GLCDC_GR2_CLUT0033_OFFSET     0x00000884  /* Color Palette */
#define R_GLCDC_GR2_CLUT0034_OFFSET     0x00000888  /* Color Palette */
#define R_GLCDC_GR2_CLUT0035_OFFSET     0x0000088c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0036_OFFSET     0x00000890  /* Color Palette */
#define R_GLCDC_GR2_CLUT0037_OFFSET     0x00000894  /* Color Palette */
#define R_GLCDC_GR2_CLUT0038_OFFSET     0x00000898  /* Color Palette */
#define R_GLCDC_GR2_CLUT0039_OFFSET     0x0000089c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0040_OFFSET     0x000008a0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0041_OFFSET     0x000008a4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0042_OFFSET     0x000008a8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0043_OFFSET     0x000008ac  /* Color Palette */
#define R_GLCDC_GR2_CLUT0044_OFFSET     0x000008b0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0045_OFFSET     0x000008b4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0046_OFFSET     0x000008b8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0047_OFFSET     0x000008bc  /* Color Palette */
#define R_GLCDC_GR2_CLUT0048_OFFSET     0x000008c0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0049_OFFSET     0x000008c4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0050_OFFSET     0x000008c8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0051_OFFSET     0x000008cc  /* Color Palette */
#define R_GLCDC_GR2_CLUT0052_OFFSET     0x000008d0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0053_OFFSET     0x000008d4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0054_OFFSET     0x000008d8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0055_OFFSET     0x000008dc  /* Color Palette */
#define R_GLCDC_GR2_CLUT0056_OFFSET     0x000008e0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0057_OFFSET     0x000008e4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0058_OFFSET     0x000008e8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0059_OFFSET     0x000008ec  /* Color Palette */
#define R_GLCDC_GR2_CLUT0060_OFFSET     0x000008f0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0061_OFFSET     0x000008f4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0062_OFFSET     0x000008f8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0063_OFFSET     0x000008fc  /* Color Palette */
#define R_GLCDC_GR2_CLUT0064_OFFSET     0x00000900  /* Color Palette */
#define R_GLCDC_GR2_CLUT0065_OFFSET     0x00000904  /* Color Palette */
#define R_GLCDC_GR2_CLUT0066_OFFSET     0x00000908  /* Color Palette */
#define R_GLCDC_GR2_CLUT0067_OFFSET     0x0000090c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0068_OFFSET     0x00000910  /* Color Palette */
#define R_GLCDC_GR2_CLUT0069_OFFSET     0x00000914  /* Color Palette */
#define R_GLCDC_GR2_CLUT0070_OFFSET     0x00000918  /* Color Palette */
#define R_GLCDC_GR2_CLUT0071_OFFSET     0x0000091c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0072_OFFSET     0x00000920  /* Color Palette */
#define R_GLCDC_GR2_CLUT0073_OFFSET     0x00000924  /* Color Palette */
#define R_GLCDC_GR2_CLUT0074_OFFSET     0x00000928  /* Color Palette */
#define R_GLCDC_GR2_CLUT0075_OFFSET     0x0000092c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0076_OFFSET     0x00000930  /* Color Palette */
#define R_GLCDC_GR2_CLUT0077_OFFSET     0x00000934  /* Color Palette */
#define R_GLCDC_GR2_CLUT0078_OFFSET     0x00000938  /* Color Palette */
#define R_GLCDC_GR2_CLUT0079_OFFSET     0x0000093c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0080_OFFSET     0x00000940  /* Color Palette */
#define R_GLCDC_GR2_CLUT0081_OFFSET     0x00000944  /* Color Palette */
#define R_GLCDC_GR2_CLUT0082_OFFSET     0x00000948  /* Color Palette */
#define R_GLCDC_GR2_CLUT0083_OFFSET     0x0000094c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0084_OFFSET     0x00000950  /* Color Palette */
#define R_GLCDC_GR2_CLUT0085_OFFSET     0x00000954  /* Color Palette */
#define R_GLCDC_GR2_CLUT0086_OFFSET     0x00000958  /* Color Palette */
#define R_GLCDC_GR2_CLUT0087_OFFSET     0x0000095c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0088_OFFSET     0x00000960  /* Color Palette */
#define R_GLCDC_GR2_CLUT0089_OFFSET     0x00000964  /* Color Palette */
#define R_GLCDC_GR2_CLUT0090_OFFSET     0x00000968  /* Color Palette */
#define R_GLCDC_GR2_CLUT0091_OFFSET     0x0000096c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0092_OFFSET     0x00000970  /* Color Palette */
#define R_GLCDC_GR2_CLUT0093_OFFSET     0x00000974  /* Color Palette */
#define R_GLCDC_GR2_CLUT0094_OFFSET     0x00000978  /* Color Palette */
#define R_GLCDC_GR2_CLUT0095_OFFSET     0x0000097c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0096_OFFSET     0x00000980  /* Color Palette */
#define R_GLCDC_GR2_CLUT0097_OFFSET     0x00000984  /* Color Palette */
#define R_GLCDC_GR2_CLUT0098_OFFSET     0x00000988  /* Color Palette */
#define R_GLCDC_GR2_CLUT0099_OFFSET     0x0000098c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0100_OFFSET     0x00000990  /* Color Palette */
#define R_GLCDC_GR2_CLUT0101_OFFSET     0x00000994  /* Color Palette */
#define R_GLCDC_GR2_CLUT0102_OFFSET     0x00000998  /* Color Palette */
#define R_GLCDC_GR2_CLUT0103_OFFSET     0x0000099c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0104_OFFSET     0x000009a0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0105_OFFSET     0x000009a4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0106_OFFSET     0x000009a8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0107_OFFSET     0x000009ac  /* Color Palette */
#define R_GLCDC_GR2_CLUT0108_OFFSET     0x000009b0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0109_OFFSET     0x000009b4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0110_OFFSET     0x000009b8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0111_OFFSET     0x000009bc  /* Color Palette */
#define R_GLCDC_GR2_CLUT0112_OFFSET     0x000009c0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0113_OFFSET     0x000009c4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0114_OFFSET     0x000009c8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0115_OFFSET     0x000009cc  /* Color Palette */
#define R_GLCDC_GR2_CLUT0116_OFFSET     0x000009d0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0117_OFFSET     0x000009d4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0118_OFFSET     0x000009d8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0119_OFFSET     0x000009dc  /* Color Palette */
#define R_GLCDC_GR2_CLUT0120_OFFSET     0x000009e0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0121_OFFSET     0x000009e4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0122_OFFSET     0x000009e8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0123_OFFSET     0x000009ec  /* Color Palette */
#define R_GLCDC_GR2_CLUT0124_OFFSET     0x000009f0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0125_OFFSET     0x000009f4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0126_OFFSET     0x000009f8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0127_OFFSET     0x000009fc  /* Color Palette */
#define R_GLCDC_GR2_CLUT0128_OFFSET     0x00000a00  /* Color Palette */
#define R_GLCDC_GR2_CLUT0129_OFFSET     0x00000a04  /* Color Palette */
#define R_GLCDC_GR2_CLUT0130_OFFSET     0x00000a08  /* Color Palette */
#define R_GLCDC_GR2_CLUT0131_OFFSET     0x00000a0c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0132_OFFSET     0x00000a10  /* Color Palette */
#define R_GLCDC_GR2_CLUT0133_OFFSET     0x00000a14  /* Color Palette */
#define R_GLCDC_GR2_CLUT0134_OFFSET     0x00000a18  /* Color Palette */
#define R_GLCDC_GR2_CLUT0135_OFFSET     0x00000a1c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0136_OFFSET     0x00000a20  /* Color Palette */
#define R_GLCDC_GR2_CLUT0137_OFFSET     0x00000a24  /* Color Palette */
#define R_GLCDC_GR2_CLUT0138_OFFSET     0x00000a28  /* Color Palette */
#define R_GLCDC_GR2_CLUT0139_OFFSET     0x00000a2c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0140_OFFSET     0x00000a30  /* Color Palette */
#define R_GLCDC_GR2_CLUT0141_OFFSET     0x00000a34  /* Color Palette */
#define R_GLCDC_GR2_CLUT0142_OFFSET     0x00000a38  /* Color Palette */
#define R_GLCDC_GR2_CLUT0143_OFFSET     0x00000a3c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0144_OFFSET     0x00000a40  /* Color Palette */
#define R_GLCDC_GR2_CLUT0145_OFFSET     0x00000a44  /* Color Palette */
#define R_GLCDC_GR2_CLUT0146_OFFSET     0x00000a48  /* Color Palette */
#define R_GLCDC_GR2_CLUT0147_OFFSET     0x00000a4c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0148_OFFSET     0x00000a50  /* Color Palette */
#define R_GLCDC_GR2_CLUT0149_OFFSET     0x00000a54  /* Color Palette */
#define R_GLCDC_GR2_CLUT0150_OFFSET     0x00000a58  /* Color Palette */
#define R_GLCDC_GR2_CLUT0151_OFFSET     0x00000a5c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0152_OFFSET     0x00000a60  /* Color Palette */
#define R_GLCDC_GR2_CLUT0153_OFFSET     0x00000a64  /* Color Palette */
#define R_GLCDC_GR2_CLUT0154_OFFSET     0x00000a68  /* Color Palette */
#define R_GLCDC_GR2_CLUT0155_OFFSET     0x00000a6c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0156_OFFSET     0x00000a70  /* Color Palette */
#define R_GLCDC_GR2_CLUT0157_OFFSET     0x00000a74  /* Color Palette */
#define R_GLCDC_GR2_CLUT0158_OFFSET     0x00000a78  /* Color Palette */
#define R_GLCDC_GR2_CLUT0159_OFFSET     0x00000a7c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0160_OFFSET     0x00000a80  /* Color Palette */
#define R_GLCDC_GR2_CLUT0161_OFFSET     0x00000a84  /* Color Palette */
#define R_GLCDC_GR2_CLUT0162_OFFSET     0x00000a88  /* Color Palette */
#define R_GLCDC_GR2_CLUT0163_OFFSET     0x00000a8c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0164_OFFSET     0x00000a90  /* Color Palette */
#define R_GLCDC_GR2_CLUT0165_OFFSET     0x00000a94  /* Color Palette */
#define R_GLCDC_GR2_CLUT0166_OFFSET     0x00000a98  /* Color Palette */
#define R_GLCDC_GR2_CLUT0167_OFFSET     0x00000a9c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0168_OFFSET     0x00000aa0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0169_OFFSET     0x00000aa4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0170_OFFSET     0x00000aa8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0171_OFFSET     0x00000aac  /* Color Palette */
#define R_GLCDC_GR2_CLUT0172_OFFSET     0x00000ab0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0173_OFFSET     0x00000ab4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0174_OFFSET     0x00000ab8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0175_OFFSET     0x00000abc  /* Color Palette */
#define R_GLCDC_GR2_CLUT0176_OFFSET     0x00000ac0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0177_OFFSET     0x00000ac4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0178_OFFSET     0x00000ac8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0179_OFFSET     0x00000acc  /* Color Palette */
#define R_GLCDC_GR2_CLUT0180_OFFSET     0x00000ad0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0181_OFFSET     0x00000ad4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0182_OFFSET     0x00000ad8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0183_OFFSET     0x00000adc  /* Color Palette */
#define R_GLCDC_GR2_CLUT0184_OFFSET     0x00000ae0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0185_OFFSET     0x00000ae4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0186_OFFSET     0x00000ae8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0187_OFFSET     0x00000aec  /* Color Palette */
#define R_GLCDC_GR2_CLUT0188_OFFSET     0x00000af0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0189_OFFSET     0x00000af4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0190_OFFSET     0x00000af8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0191_OFFSET     0x00000afc  /* Color Palette */
#define R_GLCDC_GR2_CLUT0192_OFFSET     0x00000b00  /* Color Palette */
#define R_GLCDC_GR2_CLUT0193_OFFSET     0x00000b04  /* Color Palette */
#define R_GLCDC_GR2_CLUT0194_OFFSET     0x00000b08  /* Color Palette */
#define R_GLCDC_GR2_CLUT0195_OFFSET     0x00000b0c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0196_OFFSET     0x00000b10  /* Color Palette */
#define R_GLCDC_GR2_CLUT0197_OFFSET     0x00000b14  /* Color Palette */
#define R_GLCDC_GR2_CLUT0198_OFFSET     0x00000b18  /* Color Palette */
#define R_GLCDC_GR2_CLUT0199_OFFSET     0x00000b1c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0200_OFFSET     0x00000b20  /* Color Palette */
#define R_GLCDC_GR2_CLUT0201_OFFSET     0x00000b24  /* Color Palette */
#define R_GLCDC_GR2_CLUT0202_OFFSET     0x00000b28  /* Color Palette */
#define R_GLCDC_GR2_CLUT0203_OFFSET     0x00000b2c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0204_OFFSET     0x00000b30  /* Color Palette */
#define R_GLCDC_GR2_CLUT0205_OFFSET     0x00000b34  /* Color Palette */
#define R_GLCDC_GR2_CLUT0206_OFFSET     0x00000b38  /* Color Palette */
#define R_GLCDC_GR2_CLUT0207_OFFSET     0x00000b3c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0208_OFFSET     0x00000b40  /* Color Palette */
#define R_GLCDC_GR2_CLUT0209_OFFSET     0x00000b44  /* Color Palette */
#define R_GLCDC_GR2_CLUT0210_OFFSET     0x00000b48  /* Color Palette */
#define R_GLCDC_GR2_CLUT0211_OFFSET     0x00000b4c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0212_OFFSET     0x00000b50  /* Color Palette */
#define R_GLCDC_GR2_CLUT0213_OFFSET     0x00000b54  /* Color Palette */
#define R_GLCDC_GR2_CLUT0214_OFFSET     0x00000b58  /* Color Palette */
#define R_GLCDC_GR2_CLUT0215_OFFSET     0x00000b5c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0216_OFFSET     0x00000b60  /* Color Palette */
#define R_GLCDC_GR2_CLUT0217_OFFSET     0x00000b64  /* Color Palette */
#define R_GLCDC_GR2_CLUT0218_OFFSET     0x00000b68  /* Color Palette */
#define R_GLCDC_GR2_CLUT0219_OFFSET     0x00000b6c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0220_OFFSET     0x00000b70  /* Color Palette */
#define R_GLCDC_GR2_CLUT0221_OFFSET     0x00000b74  /* Color Palette */
#define R_GLCDC_GR2_CLUT0222_OFFSET     0x00000b78  /* Color Palette */
#define R_GLCDC_GR2_CLUT0223_OFFSET     0x00000b7c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0224_OFFSET     0x00000b80  /* Color Palette */
#define R_GLCDC_GR2_CLUT0225_OFFSET     0x00000b84  /* Color Palette */
#define R_GLCDC_GR2_CLUT0226_OFFSET     0x00000b88  /* Color Palette */
#define R_GLCDC_GR2_CLUT0227_OFFSET     0x00000b8c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0228_OFFSET     0x00000b90  /* Color Palette */
#define R_GLCDC_GR2_CLUT0229_OFFSET     0x00000b94  /* Color Palette */
#define R_GLCDC_GR2_CLUT0230_OFFSET     0x00000b98  /* Color Palette */
#define R_GLCDC_GR2_CLUT0231_OFFSET     0x00000b9c  /* Color Palette */
#define R_GLCDC_GR2_CLUT0232_OFFSET     0x00000ba0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0233_OFFSET     0x00000ba4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0234_OFFSET     0x00000ba8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0235_OFFSET     0x00000bac  /* Color Palette */
#define R_GLCDC_GR2_CLUT0236_OFFSET     0x00000bb0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0237_OFFSET     0x00000bb4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0238_OFFSET     0x00000bb8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0239_OFFSET     0x00000bbc  /* Color Palette */
#define R_GLCDC_GR2_CLUT0240_OFFSET     0x00000bc0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0241_OFFSET     0x00000bc4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0242_OFFSET     0x00000bc8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0243_OFFSET     0x00000bcc  /* Color Palette */
#define R_GLCDC_GR2_CLUT0244_OFFSET     0x00000bd0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0245_OFFSET     0x00000bd4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0246_OFFSET     0x00000bd8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0247_OFFSET     0x00000bdc  /* Color Palette */
#define R_GLCDC_GR2_CLUT0248_OFFSET     0x00000be0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0249_OFFSET     0x00000be4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0250_OFFSET     0x00000be8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0251_OFFSET     0x00000bec  /* Color Palette */
#define R_GLCDC_GR2_CLUT0252_OFFSET     0x00000bf0  /* Color Palette */
#define R_GLCDC_GR2_CLUT0253_OFFSET     0x00000bf4  /* Color Palette */
#define R_GLCDC_GR2_CLUT0254_OFFSET     0x00000bf8  /* Color Palette */
#define R_GLCDC_GR2_CLUT0255_OFFSET     0x00000bfc  /* Color Palette */
/* GR2_CLUT1%s Registers (0-255) */
#define R_GLCDC_GR2_CLUT1000_OFFSET     0x00000c00  /* Color Palette */
#define R_GLCDC_GR2_CLUT1001_OFFSET     0x00000c04  /* Color Palette */
#define R_GLCDC_GR2_CLUT1002_OFFSET     0x00000c08  /* Color Palette */
#define R_GLCDC_GR2_CLUT1003_OFFSET     0x00000c0c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1004_OFFSET     0x00000c10  /* Color Palette */
#define R_GLCDC_GR2_CLUT1005_OFFSET     0x00000c14  /* Color Palette */
#define R_GLCDC_GR2_CLUT1006_OFFSET     0x00000c18  /* Color Palette */
#define R_GLCDC_GR2_CLUT1007_OFFSET     0x00000c1c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1008_OFFSET     0x00000c20  /* Color Palette */
#define R_GLCDC_GR2_CLUT1009_OFFSET     0x00000c24  /* Color Palette */
#define R_GLCDC_GR2_CLUT1010_OFFSET     0x00000c28  /* Color Palette */
#define R_GLCDC_GR2_CLUT1011_OFFSET     0x00000c2c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1012_OFFSET     0x00000c30  /* Color Palette */
#define R_GLCDC_GR2_CLUT1013_OFFSET     0x00000c34  /* Color Palette */
#define R_GLCDC_GR2_CLUT1014_OFFSET     0x00000c38  /* Color Palette */
#define R_GLCDC_GR2_CLUT1015_OFFSET     0x00000c3c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1016_OFFSET     0x00000c40  /* Color Palette */
#define R_GLCDC_GR2_CLUT1017_OFFSET     0x00000c44  /* Color Palette */
#define R_GLCDC_GR2_CLUT1018_OFFSET     0x00000c48  /* Color Palette */
#define R_GLCDC_GR2_CLUT1019_OFFSET     0x00000c4c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1020_OFFSET     0x00000c50  /* Color Palette */
#define R_GLCDC_GR2_CLUT1021_OFFSET     0x00000c54  /* Color Palette */
#define R_GLCDC_GR2_CLUT1022_OFFSET     0x00000c58  /* Color Palette */
#define R_GLCDC_GR2_CLUT1023_OFFSET     0x00000c5c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1024_OFFSET     0x00000c60  /* Color Palette */
#define R_GLCDC_GR2_CLUT1025_OFFSET     0x00000c64  /* Color Palette */
#define R_GLCDC_GR2_CLUT1026_OFFSET     0x00000c68  /* Color Palette */
#define R_GLCDC_GR2_CLUT1027_OFFSET     0x00000c6c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1028_OFFSET     0x00000c70  /* Color Palette */
#define R_GLCDC_GR2_CLUT1029_OFFSET     0x00000c74  /* Color Palette */
#define R_GLCDC_GR2_CLUT1030_OFFSET     0x00000c78  /* Color Palette */
#define R_GLCDC_GR2_CLUT1031_OFFSET     0x00000c7c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1032_OFFSET     0x00000c80  /* Color Palette */
#define R_GLCDC_GR2_CLUT1033_OFFSET     0x00000c84  /* Color Palette */
#define R_GLCDC_GR2_CLUT1034_OFFSET     0x00000c88  /* Color Palette */
#define R_GLCDC_GR2_CLUT1035_OFFSET     0x00000c8c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1036_OFFSET     0x00000c90  /* Color Palette */
#define R_GLCDC_GR2_CLUT1037_OFFSET     0x00000c94  /* Color Palette */
#define R_GLCDC_GR2_CLUT1038_OFFSET     0x00000c98  /* Color Palette */
#define R_GLCDC_GR2_CLUT1039_OFFSET     0x00000c9c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1040_OFFSET     0x00000ca0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1041_OFFSET     0x00000ca4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1042_OFFSET     0x00000ca8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1043_OFFSET     0x00000cac  /* Color Palette */
#define R_GLCDC_GR2_CLUT1044_OFFSET     0x00000cb0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1045_OFFSET     0x00000cb4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1046_OFFSET     0x00000cb8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1047_OFFSET     0x00000cbc  /* Color Palette */
#define R_GLCDC_GR2_CLUT1048_OFFSET     0x00000cc0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1049_OFFSET     0x00000cc4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1050_OFFSET     0x00000cc8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1051_OFFSET     0x00000ccc  /* Color Palette */
#define R_GLCDC_GR2_CLUT1052_OFFSET     0x00000cd0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1053_OFFSET     0x00000cd4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1054_OFFSET     0x00000cd8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1055_OFFSET     0x00000cdc  /* Color Palette */
#define R_GLCDC_GR2_CLUT1056_OFFSET     0x00000ce0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1057_OFFSET     0x00000ce4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1058_OFFSET     0x00000ce8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1059_OFFSET     0x00000cec  /* Color Palette */
#define R_GLCDC_GR2_CLUT1060_OFFSET     0x00000cf0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1061_OFFSET     0x00000cf4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1062_OFFSET     0x00000cf8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1063_OFFSET     0x00000cfc  /* Color Palette */
#define R_GLCDC_GR2_CLUT1064_OFFSET     0x00000d00  /* Color Palette */
#define R_GLCDC_GR2_CLUT1065_OFFSET     0x00000d04  /* Color Palette */
#define R_GLCDC_GR2_CLUT1066_OFFSET     0x00000d08  /* Color Palette */
#define R_GLCDC_GR2_CLUT1067_OFFSET     0x00000d0c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1068_OFFSET     0x00000d10  /* Color Palette */
#define R_GLCDC_GR2_CLUT1069_OFFSET     0x00000d14  /* Color Palette */
#define R_GLCDC_GR2_CLUT1070_OFFSET     0x00000d18  /* Color Palette */
#define R_GLCDC_GR2_CLUT1071_OFFSET     0x00000d1c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1072_OFFSET     0x00000d20  /* Color Palette */
#define R_GLCDC_GR2_CLUT1073_OFFSET     0x00000d24  /* Color Palette */
#define R_GLCDC_GR2_CLUT1074_OFFSET     0x00000d28  /* Color Palette */
#define R_GLCDC_GR2_CLUT1075_OFFSET     0x00000d2c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1076_OFFSET     0x00000d30  /* Color Palette */
#define R_GLCDC_GR2_CLUT1077_OFFSET     0x00000d34  /* Color Palette */
#define R_GLCDC_GR2_CLUT1078_OFFSET     0x00000d38  /* Color Palette */
#define R_GLCDC_GR2_CLUT1079_OFFSET     0x00000d3c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1080_OFFSET     0x00000d40  /* Color Palette */
#define R_GLCDC_GR2_CLUT1081_OFFSET     0x00000d44  /* Color Palette */
#define R_GLCDC_GR2_CLUT1082_OFFSET     0x00000d48  /* Color Palette */
#define R_GLCDC_GR2_CLUT1083_OFFSET     0x00000d4c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1084_OFFSET     0x00000d50  /* Color Palette */
#define R_GLCDC_GR2_CLUT1085_OFFSET     0x00000d54  /* Color Palette */
#define R_GLCDC_GR2_CLUT1086_OFFSET     0x00000d58  /* Color Palette */
#define R_GLCDC_GR2_CLUT1087_OFFSET     0x00000d5c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1088_OFFSET     0x00000d60  /* Color Palette */
#define R_GLCDC_GR2_CLUT1089_OFFSET     0x00000d64  /* Color Palette */
#define R_GLCDC_GR2_CLUT1090_OFFSET     0x00000d68  /* Color Palette */
#define R_GLCDC_GR2_CLUT1091_OFFSET     0x00000d6c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1092_OFFSET     0x00000d70  /* Color Palette */
#define R_GLCDC_GR2_CLUT1093_OFFSET     0x00000d74  /* Color Palette */
#define R_GLCDC_GR2_CLUT1094_OFFSET     0x00000d78  /* Color Palette */
#define R_GLCDC_GR2_CLUT1095_OFFSET     0x00000d7c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1096_OFFSET     0x00000d80  /* Color Palette */
#define R_GLCDC_GR2_CLUT1097_OFFSET     0x00000d84  /* Color Palette */
#define R_GLCDC_GR2_CLUT1098_OFFSET     0x00000d88  /* Color Palette */
#define R_GLCDC_GR2_CLUT1099_OFFSET     0x00000d8c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1100_OFFSET     0x00000d90  /* Color Palette */
#define R_GLCDC_GR2_CLUT1101_OFFSET     0x00000d94  /* Color Palette */
#define R_GLCDC_GR2_CLUT1102_OFFSET     0x00000d98  /* Color Palette */
#define R_GLCDC_GR2_CLUT1103_OFFSET     0x00000d9c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1104_OFFSET     0x00000da0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1105_OFFSET     0x00000da4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1106_OFFSET     0x00000da8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1107_OFFSET     0x00000dac  /* Color Palette */
#define R_GLCDC_GR2_CLUT1108_OFFSET     0x00000db0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1109_OFFSET     0x00000db4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1110_OFFSET     0x00000db8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1111_OFFSET     0x00000dbc  /* Color Palette */
#define R_GLCDC_GR2_CLUT1112_OFFSET     0x00000dc0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1113_OFFSET     0x00000dc4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1114_OFFSET     0x00000dc8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1115_OFFSET     0x00000dcc  /* Color Palette */
#define R_GLCDC_GR2_CLUT1116_OFFSET     0x00000dd0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1117_OFFSET     0x00000dd4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1118_OFFSET     0x00000dd8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1119_OFFSET     0x00000ddc  /* Color Palette */
#define R_GLCDC_GR2_CLUT1120_OFFSET     0x00000de0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1121_OFFSET     0x00000de4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1122_OFFSET     0x00000de8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1123_OFFSET     0x00000dec  /* Color Palette */
#define R_GLCDC_GR2_CLUT1124_OFFSET     0x00000df0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1125_OFFSET     0x00000df4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1126_OFFSET     0x00000df8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1127_OFFSET     0x00000dfc  /* Color Palette */
#define R_GLCDC_GR2_CLUT1128_OFFSET     0x00000e00  /* Color Palette */
#define R_GLCDC_GR2_CLUT1129_OFFSET     0x00000e04  /* Color Palette */
#define R_GLCDC_GR2_CLUT1130_OFFSET     0x00000e08  /* Color Palette */
#define R_GLCDC_GR2_CLUT1131_OFFSET     0x00000e0c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1132_OFFSET     0x00000e10  /* Color Palette */
#define R_GLCDC_GR2_CLUT1133_OFFSET     0x00000e14  /* Color Palette */
#define R_GLCDC_GR2_CLUT1134_OFFSET     0x00000e18  /* Color Palette */
#define R_GLCDC_GR2_CLUT1135_OFFSET     0x00000e1c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1136_OFFSET     0x00000e20  /* Color Palette */
#define R_GLCDC_GR2_CLUT1137_OFFSET     0x00000e24  /* Color Palette */
#define R_GLCDC_GR2_CLUT1138_OFFSET     0x00000e28  /* Color Palette */
#define R_GLCDC_GR2_CLUT1139_OFFSET     0x00000e2c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1140_OFFSET     0x00000e30  /* Color Palette */
#define R_GLCDC_GR2_CLUT1141_OFFSET     0x00000e34  /* Color Palette */
#define R_GLCDC_GR2_CLUT1142_OFFSET     0x00000e38  /* Color Palette */
#define R_GLCDC_GR2_CLUT1143_OFFSET     0x00000e3c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1144_OFFSET     0x00000e40  /* Color Palette */
#define R_GLCDC_GR2_CLUT1145_OFFSET     0x00000e44  /* Color Palette */
#define R_GLCDC_GR2_CLUT1146_OFFSET     0x00000e48  /* Color Palette */
#define R_GLCDC_GR2_CLUT1147_OFFSET     0x00000e4c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1148_OFFSET     0x00000e50  /* Color Palette */
#define R_GLCDC_GR2_CLUT1149_OFFSET     0x00000e54  /* Color Palette */
#define R_GLCDC_GR2_CLUT1150_OFFSET     0x00000e58  /* Color Palette */
#define R_GLCDC_GR2_CLUT1151_OFFSET     0x00000e5c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1152_OFFSET     0x00000e60  /* Color Palette */
#define R_GLCDC_GR2_CLUT1153_OFFSET     0x00000e64  /* Color Palette */
#define R_GLCDC_GR2_CLUT1154_OFFSET     0x00000e68  /* Color Palette */
#define R_GLCDC_GR2_CLUT1155_OFFSET     0x00000e6c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1156_OFFSET     0x00000e70  /* Color Palette */
#define R_GLCDC_GR2_CLUT1157_OFFSET     0x00000e74  /* Color Palette */
#define R_GLCDC_GR2_CLUT1158_OFFSET     0x00000e78  /* Color Palette */
#define R_GLCDC_GR2_CLUT1159_OFFSET     0x00000e7c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1160_OFFSET     0x00000e80  /* Color Palette */
#define R_GLCDC_GR2_CLUT1161_OFFSET     0x00000e84  /* Color Palette */
#define R_GLCDC_GR2_CLUT1162_OFFSET     0x00000e88  /* Color Palette */
#define R_GLCDC_GR2_CLUT1163_OFFSET     0x00000e8c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1164_OFFSET     0x00000e90  /* Color Palette */
#define R_GLCDC_GR2_CLUT1165_OFFSET     0x00000e94  /* Color Palette */
#define R_GLCDC_GR2_CLUT1166_OFFSET     0x00000e98  /* Color Palette */
#define R_GLCDC_GR2_CLUT1167_OFFSET     0x00000e9c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1168_OFFSET     0x00000ea0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1169_OFFSET     0x00000ea4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1170_OFFSET     0x00000ea8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1171_OFFSET     0x00000eac  /* Color Palette */
#define R_GLCDC_GR2_CLUT1172_OFFSET     0x00000eb0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1173_OFFSET     0x00000eb4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1174_OFFSET     0x00000eb8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1175_OFFSET     0x00000ebc  /* Color Palette */
#define R_GLCDC_GR2_CLUT1176_OFFSET     0x00000ec0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1177_OFFSET     0x00000ec4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1178_OFFSET     0x00000ec8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1179_OFFSET     0x00000ecc  /* Color Palette */
#define R_GLCDC_GR2_CLUT1180_OFFSET     0x00000ed0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1181_OFFSET     0x00000ed4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1182_OFFSET     0x00000ed8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1183_OFFSET     0x00000edc  /* Color Palette */
#define R_GLCDC_GR2_CLUT1184_OFFSET     0x00000ee0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1185_OFFSET     0x00000ee4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1186_OFFSET     0x00000ee8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1187_OFFSET     0x00000eec  /* Color Palette */
#define R_GLCDC_GR2_CLUT1188_OFFSET     0x00000ef0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1189_OFFSET     0x00000ef4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1190_OFFSET     0x00000ef8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1191_OFFSET     0x00000efc  /* Color Palette */
#define R_GLCDC_GR2_CLUT1192_OFFSET     0x00000f00  /* Color Palette */
#define R_GLCDC_GR2_CLUT1193_OFFSET     0x00000f04  /* Color Palette */
#define R_GLCDC_GR2_CLUT1194_OFFSET     0x00000f08  /* Color Palette */
#define R_GLCDC_GR2_CLUT1195_OFFSET     0x00000f0c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1196_OFFSET     0x00000f10  /* Color Palette */
#define R_GLCDC_GR2_CLUT1197_OFFSET     0x00000f14  /* Color Palette */
#define R_GLCDC_GR2_CLUT1198_OFFSET     0x00000f18  /* Color Palette */
#define R_GLCDC_GR2_CLUT1199_OFFSET     0x00000f1c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1200_OFFSET     0x00000f20  /* Color Palette */
#define R_GLCDC_GR2_CLUT1201_OFFSET     0x00000f24  /* Color Palette */
#define R_GLCDC_GR2_CLUT1202_OFFSET     0x00000f28  /* Color Palette */
#define R_GLCDC_GR2_CLUT1203_OFFSET     0x00000f2c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1204_OFFSET     0x00000f30  /* Color Palette */
#define R_GLCDC_GR2_CLUT1205_OFFSET     0x00000f34  /* Color Palette */
#define R_GLCDC_GR2_CLUT1206_OFFSET     0x00000f38  /* Color Palette */
#define R_GLCDC_GR2_CLUT1207_OFFSET     0x00000f3c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1208_OFFSET     0x00000f40  /* Color Palette */
#define R_GLCDC_GR2_CLUT1209_OFFSET     0x00000f44  /* Color Palette */
#define R_GLCDC_GR2_CLUT1210_OFFSET     0x00000f48  /* Color Palette */
#define R_GLCDC_GR2_CLUT1211_OFFSET     0x00000f4c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1212_OFFSET     0x00000f50  /* Color Palette */
#define R_GLCDC_GR2_CLUT1213_OFFSET     0x00000f54  /* Color Palette */
#define R_GLCDC_GR2_CLUT1214_OFFSET     0x00000f58  /* Color Palette */
#define R_GLCDC_GR2_CLUT1215_OFFSET     0x00000f5c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1216_OFFSET     0x00000f60  /* Color Palette */
#define R_GLCDC_GR2_CLUT1217_OFFSET     0x00000f64  /* Color Palette */
#define R_GLCDC_GR2_CLUT1218_OFFSET     0x00000f68  /* Color Palette */
#define R_GLCDC_GR2_CLUT1219_OFFSET     0x00000f6c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1220_OFFSET     0x00000f70  /* Color Palette */
#define R_GLCDC_GR2_CLUT1221_OFFSET     0x00000f74  /* Color Palette */
#define R_GLCDC_GR2_CLUT1222_OFFSET     0x00000f78  /* Color Palette */
#define R_GLCDC_GR2_CLUT1223_OFFSET     0x00000f7c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1224_OFFSET     0x00000f80  /* Color Palette */
#define R_GLCDC_GR2_CLUT1225_OFFSET     0x00000f84  /* Color Palette */
#define R_GLCDC_GR2_CLUT1226_OFFSET     0x00000f88  /* Color Palette */
#define R_GLCDC_GR2_CLUT1227_OFFSET     0x00000f8c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1228_OFFSET     0x00000f90  /* Color Palette */
#define R_GLCDC_GR2_CLUT1229_OFFSET     0x00000f94  /* Color Palette */
#define R_GLCDC_GR2_CLUT1230_OFFSET     0x00000f98  /* Color Palette */
#define R_GLCDC_GR2_CLUT1231_OFFSET     0x00000f9c  /* Color Palette */
#define R_GLCDC_GR2_CLUT1232_OFFSET     0x00000fa0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1233_OFFSET     0x00000fa4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1234_OFFSET     0x00000fa8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1235_OFFSET     0x00000fac  /* Color Palette */
#define R_GLCDC_GR2_CLUT1236_OFFSET     0x00000fb0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1237_OFFSET     0x00000fb4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1238_OFFSET     0x00000fb8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1239_OFFSET     0x00000fbc  /* Color Palette */
#define R_GLCDC_GR2_CLUT1240_OFFSET     0x00000fc0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1241_OFFSET     0x00000fc4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1242_OFFSET     0x00000fc8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1243_OFFSET     0x00000fcc  /* Color Palette */
#define R_GLCDC_GR2_CLUT1244_OFFSET     0x00000fd0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1245_OFFSET     0x00000fd4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1246_OFFSET     0x00000fd8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1247_OFFSET     0x00000fdc  /* Color Palette */
#define R_GLCDC_GR2_CLUT1248_OFFSET     0x00000fe0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1249_OFFSET     0x00000fe4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1250_OFFSET     0x00000fe8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1251_OFFSET     0x00000fec  /* Color Palette */
#define R_GLCDC_GR2_CLUT1252_OFFSET     0x00000ff0  /* Color Palette */
#define R_GLCDC_GR2_CLUT1253_OFFSET     0x00000ff4  /* Color Palette */
#define R_GLCDC_GR2_CLUT1254_OFFSET     0x00000ff8  /* Color Palette */
#define R_GLCDC_GR2_CLUT1255_OFFSET     0x00000ffc  /* Color Palette */
#define R_GLCDC_BG_EN_OFFSET     0x00001000  /* Background Plane Setting Operation Control Register */
#define R_GLCDC_BG_PERI_OFFSET     0x00001004  /* Background Plane Setting Free-Running Period Register */
#define R_GLCDC_BG_SYNC_OFFSET     0x00001008  /* Background Plane Setting Synchronization Position Register */
#define R_GLCDC_BG_VSIZE_OFFSET     0x0000100c  /* Background Plane Setting Full Image Vertical Size Register */
#define R_GLCDC_BG_HSIZE_OFFSET     0x00001010  /* Background Plane Setting Full Image Horizontal Size Register */
#define R_GLCDC_BG_BGC_OFFSET     0x00001014  /* Background Plane Setting Background Color Register */
#define R_GLCDC_BG_MON_OFFSET     0x00001018  /* Background Plane Setting Status Monitor Register */
/* GR%s_VEN Registers (1-2) */
#define R_GLCDC_GR1_VEN_OFFSET     0x00001100  /* Graphics 1 Register Update Control Register */
#define R_GLCDC_GR2_VEN_OFFSET     0x00001200  /* Graphics 2 Register Update Control Register */
/* GR%s_FLMRD Registers (1-2) */
#define R_GLCDC_GR1_FLMRD_OFFSET     0x00001104  /* Graphics 1 Frame Buffer Read Control Register */
#define R_GLCDC_GR2_FLMRD_OFFSET     0x00001204  /* Graphics 2 Frame Buffer Read Control Register */
/* GR%s_FLM1 Registers (1-2) */
#define R_GLCDC_GR1_FLM1_OFFSET     0x00001108  /* Graphics 1 Frame Buffer Control Register 1 */
#define R_GLCDC_GR2_FLM1_OFFSET     0x00001208  /* Graphics 2 Frame Buffer Control Register 1 */
/* GR%s_FLM2 Registers (1-2) */
#define R_GLCDC_GR1_FLM2_OFFSET     0x0000110c  /* Graphics 1 Frame Buffer Control Register 2 */
#define R_GLCDC_GR2_FLM2_OFFSET     0x0000120c  /* Graphics 2 Frame Buffer Control Register 2 */
/* GR%s_FLM3 Registers (1-2) */
#define R_GLCDC_GR1_FLM3_OFFSET     0x00001110  /* Graphics 1 Frame Buffer Control Register 3 */
#define R_GLCDC_GR2_FLM3_OFFSET     0x00001210  /* Graphics 2 Frame Buffer Control Register 3 */
/* GR%s_FLM5 Registers (1-2) */
#define R_GLCDC_GR1_FLM5_OFFSET     0x00001118  /* Graphics 1 Frame Buffer Control Register 5 */
#define R_GLCDC_GR2_FLM5_OFFSET     0x00001218  /* Graphics 2 Frame Buffer Control Register 5 */
/* GR%s_FLM6 Registers (1-2) */
#define R_GLCDC_GR1_FLM6_OFFSET     0x0000111c  /* Graphics 1 Frame Buffer Control Register 6 */
#define R_GLCDC_GR2_FLM6_OFFSET     0x0000121c  /* Graphics 2 Frame Buffer Control Register 6 */
/* GR%s_AB1 Registers (1-2) */
#define R_GLCDC_GR1_AB1_OFFSET     0x00001120  /* Graphics 1 Alpha Blending Control Register 1 */
#define R_GLCDC_GR2_AB1_OFFSET     0x00001220  /* Graphics 2 Alpha Blending Control Register 1 */
/* GR%s_AB2 Registers (1-2) */
#define R_GLCDC_GR1_AB2_OFFSET     0x00001124  /* Graphics 1 Alpha Blending Control Register 2 */
#define R_GLCDC_GR2_AB2_OFFSET     0x00001224  /* Graphics 2 Alpha Blending Control Register 2 */
/* GR%s_AB3 Registers (1-2) */
#define R_GLCDC_GR1_AB3_OFFSET     0x00001128  /* Graphics 1 Alpha Blending Control Register 3 */
#define R_GLCDC_GR2_AB3_OFFSET     0x00001228  /* Graphics 2 Alpha Blending Control Register 3 */
/* GR%s_AB4 Registers (1-2) */
#define R_GLCDC_GR1_AB4_OFFSET     0x0000112c  /* Graphics 1 Alpha Blending Control Register 4 */
#define R_GLCDC_GR2_AB4_OFFSET     0x0000122c  /* Graphics 2 Alpha Blending Control Register 4 */
/* GR%s_AB5 Registers (1-2) */
#define R_GLCDC_GR1_AB5_OFFSET     0x00001130  /* Graphics 1 Alpha Blending Control Register 5 */
#define R_GLCDC_GR2_AB5_OFFSET     0x00001230  /* Graphics 2 Alpha Blending Control Register 5 */
/* GR%s_AB6 Registers (1-2) */
#define R_GLCDC_GR1_AB6_OFFSET     0x00001134  /* Graphics 1 Alpha Blending Control Register 6 */
#define R_GLCDC_GR2_AB6_OFFSET     0x00001234  /* Graphics 2 Alpha Blending Control Register 6 */
/* GR%s_AB7 Registers (1-2) */
#define R_GLCDC_GR1_AB7_OFFSET     0x00001138  /* Graphics 1 Alpha Blending Control Register 7 */
#define R_GLCDC_GR2_AB7_OFFSET     0x00001238  /* Graphics 2 Alpha Blending Control Register 7 */
/* GR%s_AB8 Registers (1-2) */
#define R_GLCDC_GR1_AB8_OFFSET     0x0000113c  /* Graphics 1 Alpha Blending Control Register 8 */
#define R_GLCDC_GR2_AB8_OFFSET     0x0000123c  /* Graphics 2 Alpha Blending Control Register 8 */
/* GR%s_AB9 Registers (1-2) */
#define R_GLCDC_GR1_AB9_OFFSET     0x00001140  /* Graphics 1 Alpha Blending Control Register 9 */
#define R_GLCDC_GR2_AB9_OFFSET     0x00001240  /* Graphics 2 Alpha Blending Control Register 9 */
/* GR%s_BASE Registers (1-2) */
#define R_GLCDC_GR1_BASE_OFFSET     0x0000114c  /* Graphics 1 Background Color Control Register */
#define R_GLCDC_GR2_BASE_OFFSET     0x0000124c  /* Graphics 2 Background Color Control Register */
/* GR%s_CLUTINT Registers (1-2) */
#define R_GLCDC_GR1_CLUTINT_OFFSET     0x00001150  /* Graphics 1 CLUT Table Interrupt Control Register */
#define R_GLCDC_GR2_CLUTINT_OFFSET     0x00001250  /* Graphics 2 CLUT Table Interrupt Control Register */
/* GR%s_MON Registers (1-2) */
#define R_GLCDC_GR1_MON_OFFSET     0x00001154  /* Graphics 1 Status Monitor Register */
#define R_GLCDC_GR2_MON_OFFSET     0x00001254  /* Graphics 2 Status Monitor Register */
#define R_GLCDC_GAMG_LATCH_OFFSET     0x00001300  /* Gamma G Register Update Control Register */
#define R_GLCDC_GAM_SW_OFFSET     0x00001304  /* Gamma Correction Block Function Switch Register */
#define R_GLCDC_GAMG_LUT1_OFFSET     0x00001308  /* Gamma G Correction Block Table Setting Register 1 */
#define R_GLCDC_GAMG_LUT2_OFFSET     0x0000130c  /* Gamma G Correction Block Table Setting Register 2 */
#define R_GLCDC_GAMG_LUT3_OFFSET     0x00001310  /* Gamma G Correction Block Table Setting Register 3 */
#define R_GLCDC_GAMG_LUT4_OFFSET     0x00001314  /* Gamma G Correction Block Table Setting Register 4 */
#define R_GLCDC_GAMG_LUT5_OFFSET     0x00001318  /* Gamma G Correction Block Table Setting Register 5 */
#define R_GLCDC_GAMG_LUT6_OFFSET     0x0000131c  /* Gamma G Correction Block Table Setting Register 6 */
#define R_GLCDC_GAMG_LUT7_OFFSET     0x00001320  /* Gamma G Correction Block Table Setting Register 7 */
#define R_GLCDC_GAMG_LUT8_OFFSET     0x00001324  /* Gamma G Correction Block Table Setting Register 8 */
#define R_GLCDC_GAMG_AREA1_OFFSET     0x00001328  /* Gamma G Correction Block Area Setting Register 1 */
#define R_GLCDC_GAMG_AREA2_OFFSET     0x0000132c  /* Gamma G Correction Block Area Setting Register 2 */
#define R_GLCDC_GAMG_AREA3_OFFSET     0x00001330  /* Gamma G Correction Block Area Setting Register 3 */
#define R_GLCDC_GAMG_AREA4_OFFSET     0x00001334  /* Gamma G Correction Block Area Setting Register 4 */
#define R_GLCDC_GAMG_AREA5_OFFSET     0x00001338  /* Gamma G Correction Block Area Setting Register 5 */
#define R_GLCDC_GAMB_LATCH_OFFSET     0x00001340  /* Gamma B Register Update Control Register */
#define R_GLCDC_GAMB_LUT1_OFFSET     0x00001348  /* Gamma B Correction Block Table Setting Register 1 */
#define R_GLCDC_GAMB_LUT2_OFFSET     0x0000134c  /* Gamma B Correction Block Table Setting Register 2 */
#define R_GLCDC_GAMB_LUT3_OFFSET     0x00001350  /* Gamma B Correction Block Table Setting Register 3 */
#define R_GLCDC_GAMB_LUT4_OFFSET     0x00001354  /* Gamma B Correction Block Table Setting Register 4 */
#define R_GLCDC_GAMB_LUT5_OFFSET     0x00001358  /* Gamma B Correction Block Table Setting Register 5 */
#define R_GLCDC_GAMB_LUT6_OFFSET     0x0000135c  /* Gamma B Correction Block Table Setting Register 6 */
#define R_GLCDC_GAMB_LUT7_OFFSET     0x00001360  /* Gamma B Correction Block Table Setting Register 7 */
#define R_GLCDC_GAMB_LUT8_OFFSET     0x00001364  /* Gamma B Correction Block Table Setting Register 8 */
#define R_GLCDC_GAMB_AREA1_OFFSET     0x00001368  /* Gamma B Correction Block Area Setting Register 1 */
#define R_GLCDC_GAMB_AREA2_OFFSET     0x0000136c  /* Gamma B Correction Block Area Setting Register 2 */
#define R_GLCDC_GAMB_AREA3_OFFSET     0x00001370  /* Gamma B Correction Block Area Setting Register 3 */
#define R_GLCDC_GAMB_AREA4_OFFSET     0x00001374  /* Gamma B Correction Block Area Setting Register 4 */
#define R_GLCDC_GAMB_AREA5_OFFSET     0x00001378  /* Gamma B Correction Block Area Setting Register 5 */
#define R_GLCDC_GAMR_LATCH_OFFSET     0x00001380  /* Gamma R Register Update Control Register */
#define R_GLCDC_GAMR_LUT1_OFFSET     0x00001388  /* Gamma R Correction Block Table Setting Register 1 */
#define R_GLCDC_GAMR_LUT2_OFFSET     0x0000138c  /* Gamma R Correction Block Table Setting Register 2 */
#define R_GLCDC_GAMR_LUT3_OFFSET     0x00001390  /* Gamma R Correction Block Table Setting Register 3 */
#define R_GLCDC_GAMR_LUT4_OFFSET     0x00001394  /* Gamma R Correction Block Table Setting Register 4 */
#define R_GLCDC_GAMR_LUT5_OFFSET     0x00001398  /* Gamma R Correction Block Table Setting Register 5 */
#define R_GLCDC_GAMR_LUT6_OFFSET     0x0000139c  /* Gamma R Correction Block Table Setting Register 6 */
#define R_GLCDC_GAMR_LUT7_OFFSET     0x000013a0  /* Gamma R Correction Block Table Setting Register 7 */
#define R_GLCDC_GAMR_LUT8_OFFSET     0x000013a4  /* Gamma R Correction Block Table Setting Register 8 */
#define R_GLCDC_GAMR_AREA1_OFFSET     0x000013a8  /* Gamma R Correction Block Area Setting Register 1 */
#define R_GLCDC_GAMR_AREA2_OFFSET     0x000013ac  /* Gamma R Correction Block Area Setting Register 2 */
#define R_GLCDC_GAMR_AREA3_OFFSET     0x000013b0  /* Gamma R Correction Block Area Setting Register 3 */
#define R_GLCDC_GAMR_AREA4_OFFSET     0x000013b4  /* Gamma R Correction Block Area Setting Register 4 */
#define R_GLCDC_GAMR_AREA5_OFFSET     0x000013b8  /* Gamma R Correction Block Area Setting Register 5 */
#define R_GLCDC_OUT_VLATCH_OFFSET     0x000013c0  /* Output Control Block Register Update Control Register */
#define R_GLCDC_OUT_SET_OFFSET     0x000013c4  /* Output Control Block Output Interface Register */
#define R_GLCDC_OUT_BRIGHT1_OFFSET     0x000013c8  /* Output Control Block Brightness Correction Register 1 */
#define R_GLCDC_OUT_BRIGHT2_OFFSET     0x000013cc  /* Output Control Block Brightness Correction Register 2 */
#define R_GLCDC_OUT_CONTRAST_OFFSET     0x000013d0  /* Output Control Block Contrast Correction Register */
#define R_GLCDC_OUT_PDTHA_OFFSET     0x000013d4  /* Output Control Block Panel Dither Correction Register */
#define R_GLCDC_OUT_CLKPHASE_OFFSET     0x000013e4  /* Output Control Block Output Phase Control Register */
#define R_GLCDC_TCON_TIM_OFFSET     0x00001404  /* TCON Reference Timing Setting Register */
#define R_GLCDC_TCON_STVA1_OFFSET     0x00001408  /* TCON Vertical Timing Setting Register x1 */
#define R_GLCDC_TCON_STVA2_OFFSET     0x0000140c  /* TCON Vertical Timing Setting Register x2 */
#define R_GLCDC_TCON_STVB1_OFFSET     0x00001410  /* TCON Vertical Timing Setting Register x1 */
#define R_GLCDC_TCON_STVB2_OFFSET     0x00001414  /* TCON Vertical Timing Setting Register x2 */
#define R_GLCDC_TCON_STHA1_OFFSET     0x00001418  /* TCON Horizontal Timing Setting Register x1 */
#define R_GLCDC_TCON_STHA2_OFFSET     0x0000141c  /* TCON Horizontal Timing Setting Register x2 */
#define R_GLCDC_TCON_STHB1_OFFSET     0x00001420  /* TCON Horizontal Timing Setting Register x1 */
#define R_GLCDC_TCON_STHB2_OFFSET     0x00001424  /* TCON Horizontal Timing Setting Register x2 */
#define R_GLCDC_TCON_DE_OFFSET     0x00001428  /* TCON Data Enable Polarity Setting Register */
#define R_GLCDC_SYSCNT_DTCTEN_OFFSET     0x00001440  /* System Control Block State Detection Control Register */
#define R_GLCDC_SYSCNT_INTEN_OFFSET     0x00001444  /* System Control Block Interrupt Request Enable Control Register */
#define R_GLCDC_SYSCNT_STCLR_OFFSET     0x00001448  /* System Control Block Status Clear Register */
#define R_GLCDC_SYSCNT_STMON_OFFSET     0x0000144c  /* System Control Block Status Monitor Register */
#define R_GLCDC_SYSCNT_PANEL_CLK_OFFSET     0x00001450  /* System Control Block Version and Panel Clock Control Register */

/* GLCDC Register Addresses */

#define R_GLCDC_GR1_CLUT0000                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0000_OFFSET)
#define R_GLCDC_GR1_CLUT0001                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0001_OFFSET)
#define R_GLCDC_GR1_CLUT0002                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0002_OFFSET)
#define R_GLCDC_GR1_CLUT0003                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0003_OFFSET)
#define R_GLCDC_GR1_CLUT0004                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0004_OFFSET)
#define R_GLCDC_GR1_CLUT0005                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0005_OFFSET)
#define R_GLCDC_GR1_CLUT0006                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0006_OFFSET)
#define R_GLCDC_GR1_CLUT0007                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0007_OFFSET)
#define R_GLCDC_GR1_CLUT0008                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0008_OFFSET)
#define R_GLCDC_GR1_CLUT0009                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0009_OFFSET)
#define R_GLCDC_GR1_CLUT0010                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0010_OFFSET)
#define R_GLCDC_GR1_CLUT0011                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0011_OFFSET)
#define R_GLCDC_GR1_CLUT0012                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0012_OFFSET)
#define R_GLCDC_GR1_CLUT0013                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0013_OFFSET)
#define R_GLCDC_GR1_CLUT0014                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0014_OFFSET)
#define R_GLCDC_GR1_CLUT0015                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0015_OFFSET)
#define R_GLCDC_GR1_CLUT0016                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0016_OFFSET)
#define R_GLCDC_GR1_CLUT0017                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0017_OFFSET)
#define R_GLCDC_GR1_CLUT0018                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0018_OFFSET)
#define R_GLCDC_GR1_CLUT0019                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0019_OFFSET)
#define R_GLCDC_GR1_CLUT0020                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0020_OFFSET)
#define R_GLCDC_GR1_CLUT0021                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0021_OFFSET)
#define R_GLCDC_GR1_CLUT0022                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0022_OFFSET)
#define R_GLCDC_GR1_CLUT0023                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0023_OFFSET)
#define R_GLCDC_GR1_CLUT0024                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0024_OFFSET)
#define R_GLCDC_GR1_CLUT0025                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0025_OFFSET)
#define R_GLCDC_GR1_CLUT0026                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0026_OFFSET)
#define R_GLCDC_GR1_CLUT0027                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0027_OFFSET)
#define R_GLCDC_GR1_CLUT0028                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0028_OFFSET)
#define R_GLCDC_GR1_CLUT0029                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0029_OFFSET)
#define R_GLCDC_GR1_CLUT0030                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0030_OFFSET)
#define R_GLCDC_GR1_CLUT0031                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0031_OFFSET)
#define R_GLCDC_GR1_CLUT0032                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0032_OFFSET)
#define R_GLCDC_GR1_CLUT0033                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0033_OFFSET)
#define R_GLCDC_GR1_CLUT0034                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0034_OFFSET)
#define R_GLCDC_GR1_CLUT0035                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0035_OFFSET)
#define R_GLCDC_GR1_CLUT0036                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0036_OFFSET)
#define R_GLCDC_GR1_CLUT0037                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0037_OFFSET)
#define R_GLCDC_GR1_CLUT0038                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0038_OFFSET)
#define R_GLCDC_GR1_CLUT0039                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0039_OFFSET)
#define R_GLCDC_GR1_CLUT0040                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0040_OFFSET)
#define R_GLCDC_GR1_CLUT0041                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0041_OFFSET)
#define R_GLCDC_GR1_CLUT0042                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0042_OFFSET)
#define R_GLCDC_GR1_CLUT0043                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0043_OFFSET)
#define R_GLCDC_GR1_CLUT0044                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0044_OFFSET)
#define R_GLCDC_GR1_CLUT0045                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0045_OFFSET)
#define R_GLCDC_GR1_CLUT0046                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0046_OFFSET)
#define R_GLCDC_GR1_CLUT0047                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0047_OFFSET)
#define R_GLCDC_GR1_CLUT0048                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0048_OFFSET)
#define R_GLCDC_GR1_CLUT0049                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0049_OFFSET)
#define R_GLCDC_GR1_CLUT0050                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0050_OFFSET)
#define R_GLCDC_GR1_CLUT0051                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0051_OFFSET)
#define R_GLCDC_GR1_CLUT0052                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0052_OFFSET)
#define R_GLCDC_GR1_CLUT0053                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0053_OFFSET)
#define R_GLCDC_GR1_CLUT0054                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0054_OFFSET)
#define R_GLCDC_GR1_CLUT0055                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0055_OFFSET)
#define R_GLCDC_GR1_CLUT0056                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0056_OFFSET)
#define R_GLCDC_GR1_CLUT0057                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0057_OFFSET)
#define R_GLCDC_GR1_CLUT0058                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0058_OFFSET)
#define R_GLCDC_GR1_CLUT0059                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0059_OFFSET)
#define R_GLCDC_GR1_CLUT0060                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0060_OFFSET)
#define R_GLCDC_GR1_CLUT0061                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0061_OFFSET)
#define R_GLCDC_GR1_CLUT0062                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0062_OFFSET)
#define R_GLCDC_GR1_CLUT0063                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0063_OFFSET)
#define R_GLCDC_GR1_CLUT0064                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0064_OFFSET)
#define R_GLCDC_GR1_CLUT0065                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0065_OFFSET)
#define R_GLCDC_GR1_CLUT0066                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0066_OFFSET)
#define R_GLCDC_GR1_CLUT0067                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0067_OFFSET)
#define R_GLCDC_GR1_CLUT0068                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0068_OFFSET)
#define R_GLCDC_GR1_CLUT0069                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0069_OFFSET)
#define R_GLCDC_GR1_CLUT0070                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0070_OFFSET)
#define R_GLCDC_GR1_CLUT0071                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0071_OFFSET)
#define R_GLCDC_GR1_CLUT0072                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0072_OFFSET)
#define R_GLCDC_GR1_CLUT0073                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0073_OFFSET)
#define R_GLCDC_GR1_CLUT0074                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0074_OFFSET)
#define R_GLCDC_GR1_CLUT0075                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0075_OFFSET)
#define R_GLCDC_GR1_CLUT0076                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0076_OFFSET)
#define R_GLCDC_GR1_CLUT0077                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0077_OFFSET)
#define R_GLCDC_GR1_CLUT0078                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0078_OFFSET)
#define R_GLCDC_GR1_CLUT0079                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0079_OFFSET)
#define R_GLCDC_GR1_CLUT0080                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0080_OFFSET)
#define R_GLCDC_GR1_CLUT0081                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0081_OFFSET)
#define R_GLCDC_GR1_CLUT0082                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0082_OFFSET)
#define R_GLCDC_GR1_CLUT0083                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0083_OFFSET)
#define R_GLCDC_GR1_CLUT0084                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0084_OFFSET)
#define R_GLCDC_GR1_CLUT0085                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0085_OFFSET)
#define R_GLCDC_GR1_CLUT0086                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0086_OFFSET)
#define R_GLCDC_GR1_CLUT0087                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0087_OFFSET)
#define R_GLCDC_GR1_CLUT0088                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0088_OFFSET)
#define R_GLCDC_GR1_CLUT0089                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0089_OFFSET)
#define R_GLCDC_GR1_CLUT0090                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0090_OFFSET)
#define R_GLCDC_GR1_CLUT0091                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0091_OFFSET)
#define R_GLCDC_GR1_CLUT0092                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0092_OFFSET)
#define R_GLCDC_GR1_CLUT0093                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0093_OFFSET)
#define R_GLCDC_GR1_CLUT0094                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0094_OFFSET)
#define R_GLCDC_GR1_CLUT0095                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0095_OFFSET)
#define R_GLCDC_GR1_CLUT0096                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0096_OFFSET)
#define R_GLCDC_GR1_CLUT0097                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0097_OFFSET)
#define R_GLCDC_GR1_CLUT0098                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0098_OFFSET)
#define R_GLCDC_GR1_CLUT0099                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0099_OFFSET)
#define R_GLCDC_GR1_CLUT0100                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0100_OFFSET)
#define R_GLCDC_GR1_CLUT0101                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0101_OFFSET)
#define R_GLCDC_GR1_CLUT0102                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0102_OFFSET)
#define R_GLCDC_GR1_CLUT0103                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0103_OFFSET)
#define R_GLCDC_GR1_CLUT0104                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0104_OFFSET)
#define R_GLCDC_GR1_CLUT0105                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0105_OFFSET)
#define R_GLCDC_GR1_CLUT0106                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0106_OFFSET)
#define R_GLCDC_GR1_CLUT0107                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0107_OFFSET)
#define R_GLCDC_GR1_CLUT0108                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0108_OFFSET)
#define R_GLCDC_GR1_CLUT0109                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0109_OFFSET)
#define R_GLCDC_GR1_CLUT0110                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0110_OFFSET)
#define R_GLCDC_GR1_CLUT0111                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0111_OFFSET)
#define R_GLCDC_GR1_CLUT0112                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0112_OFFSET)
#define R_GLCDC_GR1_CLUT0113                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0113_OFFSET)
#define R_GLCDC_GR1_CLUT0114                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0114_OFFSET)
#define R_GLCDC_GR1_CLUT0115                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0115_OFFSET)
#define R_GLCDC_GR1_CLUT0116                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0116_OFFSET)
#define R_GLCDC_GR1_CLUT0117                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0117_OFFSET)
#define R_GLCDC_GR1_CLUT0118                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0118_OFFSET)
#define R_GLCDC_GR1_CLUT0119                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0119_OFFSET)
#define R_GLCDC_GR1_CLUT0120                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0120_OFFSET)
#define R_GLCDC_GR1_CLUT0121                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0121_OFFSET)
#define R_GLCDC_GR1_CLUT0122                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0122_OFFSET)
#define R_GLCDC_GR1_CLUT0123                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0123_OFFSET)
#define R_GLCDC_GR1_CLUT0124                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0124_OFFSET)
#define R_GLCDC_GR1_CLUT0125                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0125_OFFSET)
#define R_GLCDC_GR1_CLUT0126                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0126_OFFSET)
#define R_GLCDC_GR1_CLUT0127                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0127_OFFSET)
#define R_GLCDC_GR1_CLUT0128                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0128_OFFSET)
#define R_GLCDC_GR1_CLUT0129                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0129_OFFSET)
#define R_GLCDC_GR1_CLUT0130                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0130_OFFSET)
#define R_GLCDC_GR1_CLUT0131                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0131_OFFSET)
#define R_GLCDC_GR1_CLUT0132                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0132_OFFSET)
#define R_GLCDC_GR1_CLUT0133                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0133_OFFSET)
#define R_GLCDC_GR1_CLUT0134                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0134_OFFSET)
#define R_GLCDC_GR1_CLUT0135                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0135_OFFSET)
#define R_GLCDC_GR1_CLUT0136                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0136_OFFSET)
#define R_GLCDC_GR1_CLUT0137                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0137_OFFSET)
#define R_GLCDC_GR1_CLUT0138                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0138_OFFSET)
#define R_GLCDC_GR1_CLUT0139                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0139_OFFSET)
#define R_GLCDC_GR1_CLUT0140                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0140_OFFSET)
#define R_GLCDC_GR1_CLUT0141                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0141_OFFSET)
#define R_GLCDC_GR1_CLUT0142                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0142_OFFSET)
#define R_GLCDC_GR1_CLUT0143                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0143_OFFSET)
#define R_GLCDC_GR1_CLUT0144                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0144_OFFSET)
#define R_GLCDC_GR1_CLUT0145                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0145_OFFSET)
#define R_GLCDC_GR1_CLUT0146                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0146_OFFSET)
#define R_GLCDC_GR1_CLUT0147                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0147_OFFSET)
#define R_GLCDC_GR1_CLUT0148                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0148_OFFSET)
#define R_GLCDC_GR1_CLUT0149                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0149_OFFSET)
#define R_GLCDC_GR1_CLUT0150                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0150_OFFSET)
#define R_GLCDC_GR1_CLUT0151                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0151_OFFSET)
#define R_GLCDC_GR1_CLUT0152                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0152_OFFSET)
#define R_GLCDC_GR1_CLUT0153                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0153_OFFSET)
#define R_GLCDC_GR1_CLUT0154                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0154_OFFSET)
#define R_GLCDC_GR1_CLUT0155                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0155_OFFSET)
#define R_GLCDC_GR1_CLUT0156                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0156_OFFSET)
#define R_GLCDC_GR1_CLUT0157                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0157_OFFSET)
#define R_GLCDC_GR1_CLUT0158                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0158_OFFSET)
#define R_GLCDC_GR1_CLUT0159                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0159_OFFSET)
#define R_GLCDC_GR1_CLUT0160                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0160_OFFSET)
#define R_GLCDC_GR1_CLUT0161                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0161_OFFSET)
#define R_GLCDC_GR1_CLUT0162                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0162_OFFSET)
#define R_GLCDC_GR1_CLUT0163                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0163_OFFSET)
#define R_GLCDC_GR1_CLUT0164                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0164_OFFSET)
#define R_GLCDC_GR1_CLUT0165                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0165_OFFSET)
#define R_GLCDC_GR1_CLUT0166                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0166_OFFSET)
#define R_GLCDC_GR1_CLUT0167                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0167_OFFSET)
#define R_GLCDC_GR1_CLUT0168                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0168_OFFSET)
#define R_GLCDC_GR1_CLUT0169                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0169_OFFSET)
#define R_GLCDC_GR1_CLUT0170                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0170_OFFSET)
#define R_GLCDC_GR1_CLUT0171                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0171_OFFSET)
#define R_GLCDC_GR1_CLUT0172                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0172_OFFSET)
#define R_GLCDC_GR1_CLUT0173                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0173_OFFSET)
#define R_GLCDC_GR1_CLUT0174                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0174_OFFSET)
#define R_GLCDC_GR1_CLUT0175                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0175_OFFSET)
#define R_GLCDC_GR1_CLUT0176                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0176_OFFSET)
#define R_GLCDC_GR1_CLUT0177                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0177_OFFSET)
#define R_GLCDC_GR1_CLUT0178                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0178_OFFSET)
#define R_GLCDC_GR1_CLUT0179                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0179_OFFSET)
#define R_GLCDC_GR1_CLUT0180                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0180_OFFSET)
#define R_GLCDC_GR1_CLUT0181                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0181_OFFSET)
#define R_GLCDC_GR1_CLUT0182                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0182_OFFSET)
#define R_GLCDC_GR1_CLUT0183                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0183_OFFSET)
#define R_GLCDC_GR1_CLUT0184                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0184_OFFSET)
#define R_GLCDC_GR1_CLUT0185                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0185_OFFSET)
#define R_GLCDC_GR1_CLUT0186                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0186_OFFSET)
#define R_GLCDC_GR1_CLUT0187                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0187_OFFSET)
#define R_GLCDC_GR1_CLUT0188                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0188_OFFSET)
#define R_GLCDC_GR1_CLUT0189                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0189_OFFSET)
#define R_GLCDC_GR1_CLUT0190                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0190_OFFSET)
#define R_GLCDC_GR1_CLUT0191                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0191_OFFSET)
#define R_GLCDC_GR1_CLUT0192                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0192_OFFSET)
#define R_GLCDC_GR1_CLUT0193                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0193_OFFSET)
#define R_GLCDC_GR1_CLUT0194                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0194_OFFSET)
#define R_GLCDC_GR1_CLUT0195                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0195_OFFSET)
#define R_GLCDC_GR1_CLUT0196                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0196_OFFSET)
#define R_GLCDC_GR1_CLUT0197                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0197_OFFSET)
#define R_GLCDC_GR1_CLUT0198                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0198_OFFSET)
#define R_GLCDC_GR1_CLUT0199                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0199_OFFSET)
#define R_GLCDC_GR1_CLUT0200                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0200_OFFSET)
#define R_GLCDC_GR1_CLUT0201                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0201_OFFSET)
#define R_GLCDC_GR1_CLUT0202                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0202_OFFSET)
#define R_GLCDC_GR1_CLUT0203                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0203_OFFSET)
#define R_GLCDC_GR1_CLUT0204                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0204_OFFSET)
#define R_GLCDC_GR1_CLUT0205                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0205_OFFSET)
#define R_GLCDC_GR1_CLUT0206                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0206_OFFSET)
#define R_GLCDC_GR1_CLUT0207                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0207_OFFSET)
#define R_GLCDC_GR1_CLUT0208                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0208_OFFSET)
#define R_GLCDC_GR1_CLUT0209                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0209_OFFSET)
#define R_GLCDC_GR1_CLUT0210                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0210_OFFSET)
#define R_GLCDC_GR1_CLUT0211                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0211_OFFSET)
#define R_GLCDC_GR1_CLUT0212                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0212_OFFSET)
#define R_GLCDC_GR1_CLUT0213                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0213_OFFSET)
#define R_GLCDC_GR1_CLUT0214                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0214_OFFSET)
#define R_GLCDC_GR1_CLUT0215                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0215_OFFSET)
#define R_GLCDC_GR1_CLUT0216                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0216_OFFSET)
#define R_GLCDC_GR1_CLUT0217                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0217_OFFSET)
#define R_GLCDC_GR1_CLUT0218                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0218_OFFSET)
#define R_GLCDC_GR1_CLUT0219                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0219_OFFSET)
#define R_GLCDC_GR1_CLUT0220                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0220_OFFSET)
#define R_GLCDC_GR1_CLUT0221                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0221_OFFSET)
#define R_GLCDC_GR1_CLUT0222                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0222_OFFSET)
#define R_GLCDC_GR1_CLUT0223                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0223_OFFSET)
#define R_GLCDC_GR1_CLUT0224                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0224_OFFSET)
#define R_GLCDC_GR1_CLUT0225                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0225_OFFSET)
#define R_GLCDC_GR1_CLUT0226                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0226_OFFSET)
#define R_GLCDC_GR1_CLUT0227                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0227_OFFSET)
#define R_GLCDC_GR1_CLUT0228                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0228_OFFSET)
#define R_GLCDC_GR1_CLUT0229                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0229_OFFSET)
#define R_GLCDC_GR1_CLUT0230                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0230_OFFSET)
#define R_GLCDC_GR1_CLUT0231                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0231_OFFSET)
#define R_GLCDC_GR1_CLUT0232                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0232_OFFSET)
#define R_GLCDC_GR1_CLUT0233                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0233_OFFSET)
#define R_GLCDC_GR1_CLUT0234                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0234_OFFSET)
#define R_GLCDC_GR1_CLUT0235                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0235_OFFSET)
#define R_GLCDC_GR1_CLUT0236                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0236_OFFSET)
#define R_GLCDC_GR1_CLUT0237                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0237_OFFSET)
#define R_GLCDC_GR1_CLUT0238                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0238_OFFSET)
#define R_GLCDC_GR1_CLUT0239                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0239_OFFSET)
#define R_GLCDC_GR1_CLUT0240                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0240_OFFSET)
#define R_GLCDC_GR1_CLUT0241                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0241_OFFSET)
#define R_GLCDC_GR1_CLUT0242                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0242_OFFSET)
#define R_GLCDC_GR1_CLUT0243                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0243_OFFSET)
#define R_GLCDC_GR1_CLUT0244                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0244_OFFSET)
#define R_GLCDC_GR1_CLUT0245                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0245_OFFSET)
#define R_GLCDC_GR1_CLUT0246                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0246_OFFSET)
#define R_GLCDC_GR1_CLUT0247                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0247_OFFSET)
#define R_GLCDC_GR1_CLUT0248                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0248_OFFSET)
#define R_GLCDC_GR1_CLUT0249                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0249_OFFSET)
#define R_GLCDC_GR1_CLUT0250                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0250_OFFSET)
#define R_GLCDC_GR1_CLUT0251                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0251_OFFSET)
#define R_GLCDC_GR1_CLUT0252                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0252_OFFSET)
#define R_GLCDC_GR1_CLUT0253                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0253_OFFSET)
#define R_GLCDC_GR1_CLUT0254                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0254_OFFSET)
#define R_GLCDC_GR1_CLUT0255                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0255_OFFSET)
#define R_GLCDC_GR1_CLUT1000                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1000_OFFSET)
#define R_GLCDC_GR1_CLUT1001                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1001_OFFSET)
#define R_GLCDC_GR1_CLUT1002                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1002_OFFSET)
#define R_GLCDC_GR1_CLUT1003                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1003_OFFSET)
#define R_GLCDC_GR1_CLUT1004                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1004_OFFSET)
#define R_GLCDC_GR1_CLUT1005                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1005_OFFSET)
#define R_GLCDC_GR1_CLUT1006                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1006_OFFSET)
#define R_GLCDC_GR1_CLUT1007                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1007_OFFSET)
#define R_GLCDC_GR1_CLUT1008                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1008_OFFSET)
#define R_GLCDC_GR1_CLUT1009                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1009_OFFSET)
#define R_GLCDC_GR1_CLUT1010                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1010_OFFSET)
#define R_GLCDC_GR1_CLUT1011                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1011_OFFSET)
#define R_GLCDC_GR1_CLUT1012                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1012_OFFSET)
#define R_GLCDC_GR1_CLUT1013                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1013_OFFSET)
#define R_GLCDC_GR1_CLUT1014                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1014_OFFSET)
#define R_GLCDC_GR1_CLUT1015                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1015_OFFSET)
#define R_GLCDC_GR1_CLUT1016                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1016_OFFSET)
#define R_GLCDC_GR1_CLUT1017                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1017_OFFSET)
#define R_GLCDC_GR1_CLUT1018                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1018_OFFSET)
#define R_GLCDC_GR1_CLUT1019                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1019_OFFSET)
#define R_GLCDC_GR1_CLUT1020                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1020_OFFSET)
#define R_GLCDC_GR1_CLUT1021                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1021_OFFSET)
#define R_GLCDC_GR1_CLUT1022                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1022_OFFSET)
#define R_GLCDC_GR1_CLUT1023                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1023_OFFSET)
#define R_GLCDC_GR1_CLUT1024                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1024_OFFSET)
#define R_GLCDC_GR1_CLUT1025                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1025_OFFSET)
#define R_GLCDC_GR1_CLUT1026                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1026_OFFSET)
#define R_GLCDC_GR1_CLUT1027                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1027_OFFSET)
#define R_GLCDC_GR1_CLUT1028                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1028_OFFSET)
#define R_GLCDC_GR1_CLUT1029                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1029_OFFSET)
#define R_GLCDC_GR1_CLUT1030                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1030_OFFSET)
#define R_GLCDC_GR1_CLUT1031                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1031_OFFSET)
#define R_GLCDC_GR1_CLUT1032                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1032_OFFSET)
#define R_GLCDC_GR1_CLUT1033                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1033_OFFSET)
#define R_GLCDC_GR1_CLUT1034                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1034_OFFSET)
#define R_GLCDC_GR1_CLUT1035                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1035_OFFSET)
#define R_GLCDC_GR1_CLUT1036                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1036_OFFSET)
#define R_GLCDC_GR1_CLUT1037                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1037_OFFSET)
#define R_GLCDC_GR1_CLUT1038                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1038_OFFSET)
#define R_GLCDC_GR1_CLUT1039                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1039_OFFSET)
#define R_GLCDC_GR1_CLUT1040                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1040_OFFSET)
#define R_GLCDC_GR1_CLUT1041                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1041_OFFSET)
#define R_GLCDC_GR1_CLUT1042                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1042_OFFSET)
#define R_GLCDC_GR1_CLUT1043                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1043_OFFSET)
#define R_GLCDC_GR1_CLUT1044                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1044_OFFSET)
#define R_GLCDC_GR1_CLUT1045                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1045_OFFSET)
#define R_GLCDC_GR1_CLUT1046                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1046_OFFSET)
#define R_GLCDC_GR1_CLUT1047                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1047_OFFSET)
#define R_GLCDC_GR1_CLUT1048                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1048_OFFSET)
#define R_GLCDC_GR1_CLUT1049                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1049_OFFSET)
#define R_GLCDC_GR1_CLUT1050                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1050_OFFSET)
#define R_GLCDC_GR1_CLUT1051                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1051_OFFSET)
#define R_GLCDC_GR1_CLUT1052                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1052_OFFSET)
#define R_GLCDC_GR1_CLUT1053                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1053_OFFSET)
#define R_GLCDC_GR1_CLUT1054                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1054_OFFSET)
#define R_GLCDC_GR1_CLUT1055                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1055_OFFSET)
#define R_GLCDC_GR1_CLUT1056                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1056_OFFSET)
#define R_GLCDC_GR1_CLUT1057                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1057_OFFSET)
#define R_GLCDC_GR1_CLUT1058                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1058_OFFSET)
#define R_GLCDC_GR1_CLUT1059                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1059_OFFSET)
#define R_GLCDC_GR1_CLUT1060                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1060_OFFSET)
#define R_GLCDC_GR1_CLUT1061                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1061_OFFSET)
#define R_GLCDC_GR1_CLUT1062                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1062_OFFSET)
#define R_GLCDC_GR1_CLUT1063                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1063_OFFSET)
#define R_GLCDC_GR1_CLUT1064                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1064_OFFSET)
#define R_GLCDC_GR1_CLUT1065                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1065_OFFSET)
#define R_GLCDC_GR1_CLUT1066                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1066_OFFSET)
#define R_GLCDC_GR1_CLUT1067                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1067_OFFSET)
#define R_GLCDC_GR1_CLUT1068                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1068_OFFSET)
#define R_GLCDC_GR1_CLUT1069                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1069_OFFSET)
#define R_GLCDC_GR1_CLUT1070                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1070_OFFSET)
#define R_GLCDC_GR1_CLUT1071                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1071_OFFSET)
#define R_GLCDC_GR1_CLUT1072                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1072_OFFSET)
#define R_GLCDC_GR1_CLUT1073                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1073_OFFSET)
#define R_GLCDC_GR1_CLUT1074                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1074_OFFSET)
#define R_GLCDC_GR1_CLUT1075                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1075_OFFSET)
#define R_GLCDC_GR1_CLUT1076                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1076_OFFSET)
#define R_GLCDC_GR1_CLUT1077                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1077_OFFSET)
#define R_GLCDC_GR1_CLUT1078                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1078_OFFSET)
#define R_GLCDC_GR1_CLUT1079                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1079_OFFSET)
#define R_GLCDC_GR1_CLUT1080                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1080_OFFSET)
#define R_GLCDC_GR1_CLUT1081                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1081_OFFSET)
#define R_GLCDC_GR1_CLUT1082                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1082_OFFSET)
#define R_GLCDC_GR1_CLUT1083                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1083_OFFSET)
#define R_GLCDC_GR1_CLUT1084                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1084_OFFSET)
#define R_GLCDC_GR1_CLUT1085                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1085_OFFSET)
#define R_GLCDC_GR1_CLUT1086                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1086_OFFSET)
#define R_GLCDC_GR1_CLUT1087                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1087_OFFSET)
#define R_GLCDC_GR1_CLUT1088                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1088_OFFSET)
#define R_GLCDC_GR1_CLUT1089                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1089_OFFSET)
#define R_GLCDC_GR1_CLUT1090                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1090_OFFSET)
#define R_GLCDC_GR1_CLUT1091                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1091_OFFSET)
#define R_GLCDC_GR1_CLUT1092                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1092_OFFSET)
#define R_GLCDC_GR1_CLUT1093                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1093_OFFSET)
#define R_GLCDC_GR1_CLUT1094                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1094_OFFSET)
#define R_GLCDC_GR1_CLUT1095                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1095_OFFSET)
#define R_GLCDC_GR1_CLUT1096                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1096_OFFSET)
#define R_GLCDC_GR1_CLUT1097                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1097_OFFSET)
#define R_GLCDC_GR1_CLUT1098                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1098_OFFSET)
#define R_GLCDC_GR1_CLUT1099                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1099_OFFSET)
#define R_GLCDC_GR1_CLUT1100                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1100_OFFSET)
#define R_GLCDC_GR1_CLUT1101                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1101_OFFSET)
#define R_GLCDC_GR1_CLUT1102                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1102_OFFSET)
#define R_GLCDC_GR1_CLUT1103                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1103_OFFSET)
#define R_GLCDC_GR1_CLUT1104                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1104_OFFSET)
#define R_GLCDC_GR1_CLUT1105                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1105_OFFSET)
#define R_GLCDC_GR1_CLUT1106                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1106_OFFSET)
#define R_GLCDC_GR1_CLUT1107                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1107_OFFSET)
#define R_GLCDC_GR1_CLUT1108                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1108_OFFSET)
#define R_GLCDC_GR1_CLUT1109                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1109_OFFSET)
#define R_GLCDC_GR1_CLUT1110                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1110_OFFSET)
#define R_GLCDC_GR1_CLUT1111                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1111_OFFSET)
#define R_GLCDC_GR1_CLUT1112                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1112_OFFSET)
#define R_GLCDC_GR1_CLUT1113                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1113_OFFSET)
#define R_GLCDC_GR1_CLUT1114                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1114_OFFSET)
#define R_GLCDC_GR1_CLUT1115                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1115_OFFSET)
#define R_GLCDC_GR1_CLUT1116                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1116_OFFSET)
#define R_GLCDC_GR1_CLUT1117                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1117_OFFSET)
#define R_GLCDC_GR1_CLUT1118                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1118_OFFSET)
#define R_GLCDC_GR1_CLUT1119                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1119_OFFSET)
#define R_GLCDC_GR1_CLUT1120                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1120_OFFSET)
#define R_GLCDC_GR1_CLUT1121                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1121_OFFSET)
#define R_GLCDC_GR1_CLUT1122                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1122_OFFSET)
#define R_GLCDC_GR1_CLUT1123                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1123_OFFSET)
#define R_GLCDC_GR1_CLUT1124                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1124_OFFSET)
#define R_GLCDC_GR1_CLUT1125                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1125_OFFSET)
#define R_GLCDC_GR1_CLUT1126                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1126_OFFSET)
#define R_GLCDC_GR1_CLUT1127                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1127_OFFSET)
#define R_GLCDC_GR1_CLUT1128                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1128_OFFSET)
#define R_GLCDC_GR1_CLUT1129                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1129_OFFSET)
#define R_GLCDC_GR1_CLUT1130                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1130_OFFSET)
#define R_GLCDC_GR1_CLUT1131                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1131_OFFSET)
#define R_GLCDC_GR1_CLUT1132                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1132_OFFSET)
#define R_GLCDC_GR1_CLUT1133                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1133_OFFSET)
#define R_GLCDC_GR1_CLUT1134                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1134_OFFSET)
#define R_GLCDC_GR1_CLUT1135                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1135_OFFSET)
#define R_GLCDC_GR1_CLUT1136                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1136_OFFSET)
#define R_GLCDC_GR1_CLUT1137                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1137_OFFSET)
#define R_GLCDC_GR1_CLUT1138                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1138_OFFSET)
#define R_GLCDC_GR1_CLUT1139                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1139_OFFSET)
#define R_GLCDC_GR1_CLUT1140                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1140_OFFSET)
#define R_GLCDC_GR1_CLUT1141                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1141_OFFSET)
#define R_GLCDC_GR1_CLUT1142                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1142_OFFSET)
#define R_GLCDC_GR1_CLUT1143                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1143_OFFSET)
#define R_GLCDC_GR1_CLUT1144                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1144_OFFSET)
#define R_GLCDC_GR1_CLUT1145                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1145_OFFSET)
#define R_GLCDC_GR1_CLUT1146                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1146_OFFSET)
#define R_GLCDC_GR1_CLUT1147                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1147_OFFSET)
#define R_GLCDC_GR1_CLUT1148                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1148_OFFSET)
#define R_GLCDC_GR1_CLUT1149                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1149_OFFSET)
#define R_GLCDC_GR1_CLUT1150                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1150_OFFSET)
#define R_GLCDC_GR1_CLUT1151                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1151_OFFSET)
#define R_GLCDC_GR1_CLUT1152                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1152_OFFSET)
#define R_GLCDC_GR1_CLUT1153                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1153_OFFSET)
#define R_GLCDC_GR1_CLUT1154                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1154_OFFSET)
#define R_GLCDC_GR1_CLUT1155                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1155_OFFSET)
#define R_GLCDC_GR1_CLUT1156                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1156_OFFSET)
#define R_GLCDC_GR1_CLUT1157                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1157_OFFSET)
#define R_GLCDC_GR1_CLUT1158                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1158_OFFSET)
#define R_GLCDC_GR1_CLUT1159                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1159_OFFSET)
#define R_GLCDC_GR1_CLUT1160                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1160_OFFSET)
#define R_GLCDC_GR1_CLUT1161                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1161_OFFSET)
#define R_GLCDC_GR1_CLUT1162                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1162_OFFSET)
#define R_GLCDC_GR1_CLUT1163                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1163_OFFSET)
#define R_GLCDC_GR1_CLUT1164                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1164_OFFSET)
#define R_GLCDC_GR1_CLUT1165                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1165_OFFSET)
#define R_GLCDC_GR1_CLUT1166                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1166_OFFSET)
#define R_GLCDC_GR1_CLUT1167                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1167_OFFSET)
#define R_GLCDC_GR1_CLUT1168                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1168_OFFSET)
#define R_GLCDC_GR1_CLUT1169                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1169_OFFSET)
#define R_GLCDC_GR1_CLUT1170                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1170_OFFSET)
#define R_GLCDC_GR1_CLUT1171                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1171_OFFSET)
#define R_GLCDC_GR1_CLUT1172                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1172_OFFSET)
#define R_GLCDC_GR1_CLUT1173                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1173_OFFSET)
#define R_GLCDC_GR1_CLUT1174                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1174_OFFSET)
#define R_GLCDC_GR1_CLUT1175                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1175_OFFSET)
#define R_GLCDC_GR1_CLUT1176                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1176_OFFSET)
#define R_GLCDC_GR1_CLUT1177                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1177_OFFSET)
#define R_GLCDC_GR1_CLUT1178                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1178_OFFSET)
#define R_GLCDC_GR1_CLUT1179                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1179_OFFSET)
#define R_GLCDC_GR1_CLUT1180                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1180_OFFSET)
#define R_GLCDC_GR1_CLUT1181                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1181_OFFSET)
#define R_GLCDC_GR1_CLUT1182                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1182_OFFSET)
#define R_GLCDC_GR1_CLUT1183                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1183_OFFSET)
#define R_GLCDC_GR1_CLUT1184                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1184_OFFSET)
#define R_GLCDC_GR1_CLUT1185                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1185_OFFSET)
#define R_GLCDC_GR1_CLUT1186                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1186_OFFSET)
#define R_GLCDC_GR1_CLUT1187                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1187_OFFSET)
#define R_GLCDC_GR1_CLUT1188                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1188_OFFSET)
#define R_GLCDC_GR1_CLUT1189                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1189_OFFSET)
#define R_GLCDC_GR1_CLUT1190                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1190_OFFSET)
#define R_GLCDC_GR1_CLUT1191                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1191_OFFSET)
#define R_GLCDC_GR1_CLUT1192                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1192_OFFSET)
#define R_GLCDC_GR1_CLUT1193                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1193_OFFSET)
#define R_GLCDC_GR1_CLUT1194                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1194_OFFSET)
#define R_GLCDC_GR1_CLUT1195                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1195_OFFSET)
#define R_GLCDC_GR1_CLUT1196                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1196_OFFSET)
#define R_GLCDC_GR1_CLUT1197                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1197_OFFSET)
#define R_GLCDC_GR1_CLUT1198                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1198_OFFSET)
#define R_GLCDC_GR1_CLUT1199                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1199_OFFSET)
#define R_GLCDC_GR1_CLUT1200                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1200_OFFSET)
#define R_GLCDC_GR1_CLUT1201                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1201_OFFSET)
#define R_GLCDC_GR1_CLUT1202                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1202_OFFSET)
#define R_GLCDC_GR1_CLUT1203                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1203_OFFSET)
#define R_GLCDC_GR1_CLUT1204                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1204_OFFSET)
#define R_GLCDC_GR1_CLUT1205                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1205_OFFSET)
#define R_GLCDC_GR1_CLUT1206                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1206_OFFSET)
#define R_GLCDC_GR1_CLUT1207                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1207_OFFSET)
#define R_GLCDC_GR1_CLUT1208                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1208_OFFSET)
#define R_GLCDC_GR1_CLUT1209                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1209_OFFSET)
#define R_GLCDC_GR1_CLUT1210                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1210_OFFSET)
#define R_GLCDC_GR1_CLUT1211                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1211_OFFSET)
#define R_GLCDC_GR1_CLUT1212                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1212_OFFSET)
#define R_GLCDC_GR1_CLUT1213                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1213_OFFSET)
#define R_GLCDC_GR1_CLUT1214                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1214_OFFSET)
#define R_GLCDC_GR1_CLUT1215                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1215_OFFSET)
#define R_GLCDC_GR1_CLUT1216                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1216_OFFSET)
#define R_GLCDC_GR1_CLUT1217                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1217_OFFSET)
#define R_GLCDC_GR1_CLUT1218                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1218_OFFSET)
#define R_GLCDC_GR1_CLUT1219                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1219_OFFSET)
#define R_GLCDC_GR1_CLUT1220                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1220_OFFSET)
#define R_GLCDC_GR1_CLUT1221                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1221_OFFSET)
#define R_GLCDC_GR1_CLUT1222                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1222_OFFSET)
#define R_GLCDC_GR1_CLUT1223                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1223_OFFSET)
#define R_GLCDC_GR1_CLUT1224                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1224_OFFSET)
#define R_GLCDC_GR1_CLUT1225                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1225_OFFSET)
#define R_GLCDC_GR1_CLUT1226                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1226_OFFSET)
#define R_GLCDC_GR1_CLUT1227                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1227_OFFSET)
#define R_GLCDC_GR1_CLUT1228                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1228_OFFSET)
#define R_GLCDC_GR1_CLUT1229                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1229_OFFSET)
#define R_GLCDC_GR1_CLUT1230                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1230_OFFSET)
#define R_GLCDC_GR1_CLUT1231                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1231_OFFSET)
#define R_GLCDC_GR1_CLUT1232                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1232_OFFSET)
#define R_GLCDC_GR1_CLUT1233                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1233_OFFSET)
#define R_GLCDC_GR1_CLUT1234                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1234_OFFSET)
#define R_GLCDC_GR1_CLUT1235                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1235_OFFSET)
#define R_GLCDC_GR1_CLUT1236                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1236_OFFSET)
#define R_GLCDC_GR1_CLUT1237                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1237_OFFSET)
#define R_GLCDC_GR1_CLUT1238                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1238_OFFSET)
#define R_GLCDC_GR1_CLUT1239                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1239_OFFSET)
#define R_GLCDC_GR1_CLUT1240                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1240_OFFSET)
#define R_GLCDC_GR1_CLUT1241                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1241_OFFSET)
#define R_GLCDC_GR1_CLUT1242                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1242_OFFSET)
#define R_GLCDC_GR1_CLUT1243                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1243_OFFSET)
#define R_GLCDC_GR1_CLUT1244                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1244_OFFSET)
#define R_GLCDC_GR1_CLUT1245                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1245_OFFSET)
#define R_GLCDC_GR1_CLUT1246                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1246_OFFSET)
#define R_GLCDC_GR1_CLUT1247                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1247_OFFSET)
#define R_GLCDC_GR1_CLUT1248                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1248_OFFSET)
#define R_GLCDC_GR1_CLUT1249                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1249_OFFSET)
#define R_GLCDC_GR1_CLUT1250                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1250_OFFSET)
#define R_GLCDC_GR1_CLUT1251                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1251_OFFSET)
#define R_GLCDC_GR1_CLUT1252                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1252_OFFSET)
#define R_GLCDC_GR1_CLUT1253                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1253_OFFSET)
#define R_GLCDC_GR1_CLUT1254                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1254_OFFSET)
#define R_GLCDC_GR1_CLUT1255                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1255_OFFSET)
#define R_GLCDC_GR2_CLUT0000                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0000_OFFSET)
#define R_GLCDC_GR2_CLUT0001                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0001_OFFSET)
#define R_GLCDC_GR2_CLUT0002                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0002_OFFSET)
#define R_GLCDC_GR2_CLUT0003                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0003_OFFSET)
#define R_GLCDC_GR2_CLUT0004                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0004_OFFSET)
#define R_GLCDC_GR2_CLUT0005                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0005_OFFSET)
#define R_GLCDC_GR2_CLUT0006                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0006_OFFSET)
#define R_GLCDC_GR2_CLUT0007                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0007_OFFSET)
#define R_GLCDC_GR2_CLUT0008                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0008_OFFSET)
#define R_GLCDC_GR2_CLUT0009                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0009_OFFSET)
#define R_GLCDC_GR2_CLUT0010                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0010_OFFSET)
#define R_GLCDC_GR2_CLUT0011                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0011_OFFSET)
#define R_GLCDC_GR2_CLUT0012                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0012_OFFSET)
#define R_GLCDC_GR2_CLUT0013                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0013_OFFSET)
#define R_GLCDC_GR2_CLUT0014                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0014_OFFSET)
#define R_GLCDC_GR2_CLUT0015                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0015_OFFSET)
#define R_GLCDC_GR2_CLUT0016                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0016_OFFSET)
#define R_GLCDC_GR2_CLUT0017                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0017_OFFSET)
#define R_GLCDC_GR2_CLUT0018                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0018_OFFSET)
#define R_GLCDC_GR2_CLUT0019                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0019_OFFSET)
#define R_GLCDC_GR2_CLUT0020                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0020_OFFSET)
#define R_GLCDC_GR2_CLUT0021                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0021_OFFSET)
#define R_GLCDC_GR2_CLUT0022                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0022_OFFSET)
#define R_GLCDC_GR2_CLUT0023                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0023_OFFSET)
#define R_GLCDC_GR2_CLUT0024                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0024_OFFSET)
#define R_GLCDC_GR2_CLUT0025                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0025_OFFSET)
#define R_GLCDC_GR2_CLUT0026                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0026_OFFSET)
#define R_GLCDC_GR2_CLUT0027                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0027_OFFSET)
#define R_GLCDC_GR2_CLUT0028                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0028_OFFSET)
#define R_GLCDC_GR2_CLUT0029                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0029_OFFSET)
#define R_GLCDC_GR2_CLUT0030                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0030_OFFSET)
#define R_GLCDC_GR2_CLUT0031                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0031_OFFSET)
#define R_GLCDC_GR2_CLUT0032                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0032_OFFSET)
#define R_GLCDC_GR2_CLUT0033                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0033_OFFSET)
#define R_GLCDC_GR2_CLUT0034                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0034_OFFSET)
#define R_GLCDC_GR2_CLUT0035                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0035_OFFSET)
#define R_GLCDC_GR2_CLUT0036                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0036_OFFSET)
#define R_GLCDC_GR2_CLUT0037                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0037_OFFSET)
#define R_GLCDC_GR2_CLUT0038                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0038_OFFSET)
#define R_GLCDC_GR2_CLUT0039                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0039_OFFSET)
#define R_GLCDC_GR2_CLUT0040                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0040_OFFSET)
#define R_GLCDC_GR2_CLUT0041                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0041_OFFSET)
#define R_GLCDC_GR2_CLUT0042                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0042_OFFSET)
#define R_GLCDC_GR2_CLUT0043                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0043_OFFSET)
#define R_GLCDC_GR2_CLUT0044                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0044_OFFSET)
#define R_GLCDC_GR2_CLUT0045                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0045_OFFSET)
#define R_GLCDC_GR2_CLUT0046                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0046_OFFSET)
#define R_GLCDC_GR2_CLUT0047                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0047_OFFSET)
#define R_GLCDC_GR2_CLUT0048                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0048_OFFSET)
#define R_GLCDC_GR2_CLUT0049                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0049_OFFSET)
#define R_GLCDC_GR2_CLUT0050                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0050_OFFSET)
#define R_GLCDC_GR2_CLUT0051                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0051_OFFSET)
#define R_GLCDC_GR2_CLUT0052                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0052_OFFSET)
#define R_GLCDC_GR2_CLUT0053                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0053_OFFSET)
#define R_GLCDC_GR2_CLUT0054                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0054_OFFSET)
#define R_GLCDC_GR2_CLUT0055                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0055_OFFSET)
#define R_GLCDC_GR2_CLUT0056                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0056_OFFSET)
#define R_GLCDC_GR2_CLUT0057                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0057_OFFSET)
#define R_GLCDC_GR2_CLUT0058                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0058_OFFSET)
#define R_GLCDC_GR2_CLUT0059                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0059_OFFSET)
#define R_GLCDC_GR2_CLUT0060                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0060_OFFSET)
#define R_GLCDC_GR2_CLUT0061                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0061_OFFSET)
#define R_GLCDC_GR2_CLUT0062                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0062_OFFSET)
#define R_GLCDC_GR2_CLUT0063                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0063_OFFSET)
#define R_GLCDC_GR2_CLUT0064                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0064_OFFSET)
#define R_GLCDC_GR2_CLUT0065                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0065_OFFSET)
#define R_GLCDC_GR2_CLUT0066                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0066_OFFSET)
#define R_GLCDC_GR2_CLUT0067                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0067_OFFSET)
#define R_GLCDC_GR2_CLUT0068                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0068_OFFSET)
#define R_GLCDC_GR2_CLUT0069                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0069_OFFSET)
#define R_GLCDC_GR2_CLUT0070                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0070_OFFSET)
#define R_GLCDC_GR2_CLUT0071                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0071_OFFSET)
#define R_GLCDC_GR2_CLUT0072                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0072_OFFSET)
#define R_GLCDC_GR2_CLUT0073                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0073_OFFSET)
#define R_GLCDC_GR2_CLUT0074                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0074_OFFSET)
#define R_GLCDC_GR2_CLUT0075                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0075_OFFSET)
#define R_GLCDC_GR2_CLUT0076                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0076_OFFSET)
#define R_GLCDC_GR2_CLUT0077                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0077_OFFSET)
#define R_GLCDC_GR2_CLUT0078                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0078_OFFSET)
#define R_GLCDC_GR2_CLUT0079                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0079_OFFSET)
#define R_GLCDC_GR2_CLUT0080                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0080_OFFSET)
#define R_GLCDC_GR2_CLUT0081                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0081_OFFSET)
#define R_GLCDC_GR2_CLUT0082                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0082_OFFSET)
#define R_GLCDC_GR2_CLUT0083                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0083_OFFSET)
#define R_GLCDC_GR2_CLUT0084                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0084_OFFSET)
#define R_GLCDC_GR2_CLUT0085                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0085_OFFSET)
#define R_GLCDC_GR2_CLUT0086                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0086_OFFSET)
#define R_GLCDC_GR2_CLUT0087                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0087_OFFSET)
#define R_GLCDC_GR2_CLUT0088                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0088_OFFSET)
#define R_GLCDC_GR2_CLUT0089                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0089_OFFSET)
#define R_GLCDC_GR2_CLUT0090                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0090_OFFSET)
#define R_GLCDC_GR2_CLUT0091                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0091_OFFSET)
#define R_GLCDC_GR2_CLUT0092                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0092_OFFSET)
#define R_GLCDC_GR2_CLUT0093                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0093_OFFSET)
#define R_GLCDC_GR2_CLUT0094                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0094_OFFSET)
#define R_GLCDC_GR2_CLUT0095                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0095_OFFSET)
#define R_GLCDC_GR2_CLUT0096                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0096_OFFSET)
#define R_GLCDC_GR2_CLUT0097                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0097_OFFSET)
#define R_GLCDC_GR2_CLUT0098                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0098_OFFSET)
#define R_GLCDC_GR2_CLUT0099                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0099_OFFSET)
#define R_GLCDC_GR2_CLUT0100                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0100_OFFSET)
#define R_GLCDC_GR2_CLUT0101                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0101_OFFSET)
#define R_GLCDC_GR2_CLUT0102                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0102_OFFSET)
#define R_GLCDC_GR2_CLUT0103                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0103_OFFSET)
#define R_GLCDC_GR2_CLUT0104                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0104_OFFSET)
#define R_GLCDC_GR2_CLUT0105                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0105_OFFSET)
#define R_GLCDC_GR2_CLUT0106                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0106_OFFSET)
#define R_GLCDC_GR2_CLUT0107                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0107_OFFSET)
#define R_GLCDC_GR2_CLUT0108                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0108_OFFSET)
#define R_GLCDC_GR2_CLUT0109                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0109_OFFSET)
#define R_GLCDC_GR2_CLUT0110                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0110_OFFSET)
#define R_GLCDC_GR2_CLUT0111                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0111_OFFSET)
#define R_GLCDC_GR2_CLUT0112                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0112_OFFSET)
#define R_GLCDC_GR2_CLUT0113                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0113_OFFSET)
#define R_GLCDC_GR2_CLUT0114                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0114_OFFSET)
#define R_GLCDC_GR2_CLUT0115                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0115_OFFSET)
#define R_GLCDC_GR2_CLUT0116                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0116_OFFSET)
#define R_GLCDC_GR2_CLUT0117                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0117_OFFSET)
#define R_GLCDC_GR2_CLUT0118                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0118_OFFSET)
#define R_GLCDC_GR2_CLUT0119                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0119_OFFSET)
#define R_GLCDC_GR2_CLUT0120                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0120_OFFSET)
#define R_GLCDC_GR2_CLUT0121                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0121_OFFSET)
#define R_GLCDC_GR2_CLUT0122                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0122_OFFSET)
#define R_GLCDC_GR2_CLUT0123                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0123_OFFSET)
#define R_GLCDC_GR2_CLUT0124                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0124_OFFSET)
#define R_GLCDC_GR2_CLUT0125                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0125_OFFSET)
#define R_GLCDC_GR2_CLUT0126                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0126_OFFSET)
#define R_GLCDC_GR2_CLUT0127                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0127_OFFSET)
#define R_GLCDC_GR2_CLUT0128                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0128_OFFSET)
#define R_GLCDC_GR2_CLUT0129                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0129_OFFSET)
#define R_GLCDC_GR2_CLUT0130                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0130_OFFSET)
#define R_GLCDC_GR2_CLUT0131                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0131_OFFSET)
#define R_GLCDC_GR2_CLUT0132                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0132_OFFSET)
#define R_GLCDC_GR2_CLUT0133                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0133_OFFSET)
#define R_GLCDC_GR2_CLUT0134                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0134_OFFSET)
#define R_GLCDC_GR2_CLUT0135                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0135_OFFSET)
#define R_GLCDC_GR2_CLUT0136                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0136_OFFSET)
#define R_GLCDC_GR2_CLUT0137                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0137_OFFSET)
#define R_GLCDC_GR2_CLUT0138                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0138_OFFSET)
#define R_GLCDC_GR2_CLUT0139                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0139_OFFSET)
#define R_GLCDC_GR2_CLUT0140                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0140_OFFSET)
#define R_GLCDC_GR2_CLUT0141                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0141_OFFSET)
#define R_GLCDC_GR2_CLUT0142                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0142_OFFSET)
#define R_GLCDC_GR2_CLUT0143                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0143_OFFSET)
#define R_GLCDC_GR2_CLUT0144                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0144_OFFSET)
#define R_GLCDC_GR2_CLUT0145                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0145_OFFSET)
#define R_GLCDC_GR2_CLUT0146                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0146_OFFSET)
#define R_GLCDC_GR2_CLUT0147                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0147_OFFSET)
#define R_GLCDC_GR2_CLUT0148                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0148_OFFSET)
#define R_GLCDC_GR2_CLUT0149                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0149_OFFSET)
#define R_GLCDC_GR2_CLUT0150                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0150_OFFSET)
#define R_GLCDC_GR2_CLUT0151                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0151_OFFSET)
#define R_GLCDC_GR2_CLUT0152                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0152_OFFSET)
#define R_GLCDC_GR2_CLUT0153                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0153_OFFSET)
#define R_GLCDC_GR2_CLUT0154                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0154_OFFSET)
#define R_GLCDC_GR2_CLUT0155                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0155_OFFSET)
#define R_GLCDC_GR2_CLUT0156                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0156_OFFSET)
#define R_GLCDC_GR2_CLUT0157                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0157_OFFSET)
#define R_GLCDC_GR2_CLUT0158                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0158_OFFSET)
#define R_GLCDC_GR2_CLUT0159                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0159_OFFSET)
#define R_GLCDC_GR2_CLUT0160                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0160_OFFSET)
#define R_GLCDC_GR2_CLUT0161                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0161_OFFSET)
#define R_GLCDC_GR2_CLUT0162                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0162_OFFSET)
#define R_GLCDC_GR2_CLUT0163                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0163_OFFSET)
#define R_GLCDC_GR2_CLUT0164                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0164_OFFSET)
#define R_GLCDC_GR2_CLUT0165                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0165_OFFSET)
#define R_GLCDC_GR2_CLUT0166                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0166_OFFSET)
#define R_GLCDC_GR2_CLUT0167                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0167_OFFSET)
#define R_GLCDC_GR2_CLUT0168                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0168_OFFSET)
#define R_GLCDC_GR2_CLUT0169                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0169_OFFSET)
#define R_GLCDC_GR2_CLUT0170                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0170_OFFSET)
#define R_GLCDC_GR2_CLUT0171                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0171_OFFSET)
#define R_GLCDC_GR2_CLUT0172                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0172_OFFSET)
#define R_GLCDC_GR2_CLUT0173                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0173_OFFSET)
#define R_GLCDC_GR2_CLUT0174                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0174_OFFSET)
#define R_GLCDC_GR2_CLUT0175                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0175_OFFSET)
#define R_GLCDC_GR2_CLUT0176                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0176_OFFSET)
#define R_GLCDC_GR2_CLUT0177                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0177_OFFSET)
#define R_GLCDC_GR2_CLUT0178                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0178_OFFSET)
#define R_GLCDC_GR2_CLUT0179                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0179_OFFSET)
#define R_GLCDC_GR2_CLUT0180                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0180_OFFSET)
#define R_GLCDC_GR2_CLUT0181                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0181_OFFSET)
#define R_GLCDC_GR2_CLUT0182                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0182_OFFSET)
#define R_GLCDC_GR2_CLUT0183                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0183_OFFSET)
#define R_GLCDC_GR2_CLUT0184                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0184_OFFSET)
#define R_GLCDC_GR2_CLUT0185                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0185_OFFSET)
#define R_GLCDC_GR2_CLUT0186                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0186_OFFSET)
#define R_GLCDC_GR2_CLUT0187                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0187_OFFSET)
#define R_GLCDC_GR2_CLUT0188                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0188_OFFSET)
#define R_GLCDC_GR2_CLUT0189                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0189_OFFSET)
#define R_GLCDC_GR2_CLUT0190                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0190_OFFSET)
#define R_GLCDC_GR2_CLUT0191                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0191_OFFSET)
#define R_GLCDC_GR2_CLUT0192                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0192_OFFSET)
#define R_GLCDC_GR2_CLUT0193                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0193_OFFSET)
#define R_GLCDC_GR2_CLUT0194                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0194_OFFSET)
#define R_GLCDC_GR2_CLUT0195                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0195_OFFSET)
#define R_GLCDC_GR2_CLUT0196                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0196_OFFSET)
#define R_GLCDC_GR2_CLUT0197                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0197_OFFSET)
#define R_GLCDC_GR2_CLUT0198                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0198_OFFSET)
#define R_GLCDC_GR2_CLUT0199                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0199_OFFSET)
#define R_GLCDC_GR2_CLUT0200                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0200_OFFSET)
#define R_GLCDC_GR2_CLUT0201                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0201_OFFSET)
#define R_GLCDC_GR2_CLUT0202                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0202_OFFSET)
#define R_GLCDC_GR2_CLUT0203                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0203_OFFSET)
#define R_GLCDC_GR2_CLUT0204                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0204_OFFSET)
#define R_GLCDC_GR2_CLUT0205                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0205_OFFSET)
#define R_GLCDC_GR2_CLUT0206                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0206_OFFSET)
#define R_GLCDC_GR2_CLUT0207                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0207_OFFSET)
#define R_GLCDC_GR2_CLUT0208                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0208_OFFSET)
#define R_GLCDC_GR2_CLUT0209                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0209_OFFSET)
#define R_GLCDC_GR2_CLUT0210                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0210_OFFSET)
#define R_GLCDC_GR2_CLUT0211                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0211_OFFSET)
#define R_GLCDC_GR2_CLUT0212                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0212_OFFSET)
#define R_GLCDC_GR2_CLUT0213                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0213_OFFSET)
#define R_GLCDC_GR2_CLUT0214                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0214_OFFSET)
#define R_GLCDC_GR2_CLUT0215                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0215_OFFSET)
#define R_GLCDC_GR2_CLUT0216                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0216_OFFSET)
#define R_GLCDC_GR2_CLUT0217                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0217_OFFSET)
#define R_GLCDC_GR2_CLUT0218                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0218_OFFSET)
#define R_GLCDC_GR2_CLUT0219                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0219_OFFSET)
#define R_GLCDC_GR2_CLUT0220                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0220_OFFSET)
#define R_GLCDC_GR2_CLUT0221                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0221_OFFSET)
#define R_GLCDC_GR2_CLUT0222                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0222_OFFSET)
#define R_GLCDC_GR2_CLUT0223                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0223_OFFSET)
#define R_GLCDC_GR2_CLUT0224                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0224_OFFSET)
#define R_GLCDC_GR2_CLUT0225                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0225_OFFSET)
#define R_GLCDC_GR2_CLUT0226                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0226_OFFSET)
#define R_GLCDC_GR2_CLUT0227                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0227_OFFSET)
#define R_GLCDC_GR2_CLUT0228                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0228_OFFSET)
#define R_GLCDC_GR2_CLUT0229                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0229_OFFSET)
#define R_GLCDC_GR2_CLUT0230                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0230_OFFSET)
#define R_GLCDC_GR2_CLUT0231                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0231_OFFSET)
#define R_GLCDC_GR2_CLUT0232                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0232_OFFSET)
#define R_GLCDC_GR2_CLUT0233                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0233_OFFSET)
#define R_GLCDC_GR2_CLUT0234                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0234_OFFSET)
#define R_GLCDC_GR2_CLUT0235                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0235_OFFSET)
#define R_GLCDC_GR2_CLUT0236                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0236_OFFSET)
#define R_GLCDC_GR2_CLUT0237                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0237_OFFSET)
#define R_GLCDC_GR2_CLUT0238                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0238_OFFSET)
#define R_GLCDC_GR2_CLUT0239                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0239_OFFSET)
#define R_GLCDC_GR2_CLUT0240                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0240_OFFSET)
#define R_GLCDC_GR2_CLUT0241                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0241_OFFSET)
#define R_GLCDC_GR2_CLUT0242                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0242_OFFSET)
#define R_GLCDC_GR2_CLUT0243                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0243_OFFSET)
#define R_GLCDC_GR2_CLUT0244                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0244_OFFSET)
#define R_GLCDC_GR2_CLUT0245                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0245_OFFSET)
#define R_GLCDC_GR2_CLUT0246                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0246_OFFSET)
#define R_GLCDC_GR2_CLUT0247                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0247_OFFSET)
#define R_GLCDC_GR2_CLUT0248                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0248_OFFSET)
#define R_GLCDC_GR2_CLUT0249                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0249_OFFSET)
#define R_GLCDC_GR2_CLUT0250                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0250_OFFSET)
#define R_GLCDC_GR2_CLUT0251                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0251_OFFSET)
#define R_GLCDC_GR2_CLUT0252                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0252_OFFSET)
#define R_GLCDC_GR2_CLUT0253                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0253_OFFSET)
#define R_GLCDC_GR2_CLUT0254                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0254_OFFSET)
#define R_GLCDC_GR2_CLUT0255                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0255_OFFSET)
#define R_GLCDC_GR2_CLUT1000                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1000_OFFSET)
#define R_GLCDC_GR2_CLUT1001                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1001_OFFSET)
#define R_GLCDC_GR2_CLUT1002                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1002_OFFSET)
#define R_GLCDC_GR2_CLUT1003                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1003_OFFSET)
#define R_GLCDC_GR2_CLUT1004                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1004_OFFSET)
#define R_GLCDC_GR2_CLUT1005                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1005_OFFSET)
#define R_GLCDC_GR2_CLUT1006                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1006_OFFSET)
#define R_GLCDC_GR2_CLUT1007                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1007_OFFSET)
#define R_GLCDC_GR2_CLUT1008                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1008_OFFSET)
#define R_GLCDC_GR2_CLUT1009                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1009_OFFSET)
#define R_GLCDC_GR2_CLUT1010                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1010_OFFSET)
#define R_GLCDC_GR2_CLUT1011                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1011_OFFSET)
#define R_GLCDC_GR2_CLUT1012                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1012_OFFSET)
#define R_GLCDC_GR2_CLUT1013                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1013_OFFSET)
#define R_GLCDC_GR2_CLUT1014                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1014_OFFSET)
#define R_GLCDC_GR2_CLUT1015                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1015_OFFSET)
#define R_GLCDC_GR2_CLUT1016                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1016_OFFSET)
#define R_GLCDC_GR2_CLUT1017                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1017_OFFSET)
#define R_GLCDC_GR2_CLUT1018                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1018_OFFSET)
#define R_GLCDC_GR2_CLUT1019                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1019_OFFSET)
#define R_GLCDC_GR2_CLUT1020                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1020_OFFSET)
#define R_GLCDC_GR2_CLUT1021                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1021_OFFSET)
#define R_GLCDC_GR2_CLUT1022                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1022_OFFSET)
#define R_GLCDC_GR2_CLUT1023                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1023_OFFSET)
#define R_GLCDC_GR2_CLUT1024                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1024_OFFSET)
#define R_GLCDC_GR2_CLUT1025                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1025_OFFSET)
#define R_GLCDC_GR2_CLUT1026                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1026_OFFSET)
#define R_GLCDC_GR2_CLUT1027                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1027_OFFSET)
#define R_GLCDC_GR2_CLUT1028                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1028_OFFSET)
#define R_GLCDC_GR2_CLUT1029                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1029_OFFSET)
#define R_GLCDC_GR2_CLUT1030                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1030_OFFSET)
#define R_GLCDC_GR2_CLUT1031                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1031_OFFSET)
#define R_GLCDC_GR2_CLUT1032                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1032_OFFSET)
#define R_GLCDC_GR2_CLUT1033                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1033_OFFSET)
#define R_GLCDC_GR2_CLUT1034                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1034_OFFSET)
#define R_GLCDC_GR2_CLUT1035                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1035_OFFSET)
#define R_GLCDC_GR2_CLUT1036                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1036_OFFSET)
#define R_GLCDC_GR2_CLUT1037                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1037_OFFSET)
#define R_GLCDC_GR2_CLUT1038                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1038_OFFSET)
#define R_GLCDC_GR2_CLUT1039                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1039_OFFSET)
#define R_GLCDC_GR2_CLUT1040                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1040_OFFSET)
#define R_GLCDC_GR2_CLUT1041                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1041_OFFSET)
#define R_GLCDC_GR2_CLUT1042                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1042_OFFSET)
#define R_GLCDC_GR2_CLUT1043                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1043_OFFSET)
#define R_GLCDC_GR2_CLUT1044                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1044_OFFSET)
#define R_GLCDC_GR2_CLUT1045                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1045_OFFSET)
#define R_GLCDC_GR2_CLUT1046                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1046_OFFSET)
#define R_GLCDC_GR2_CLUT1047                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1047_OFFSET)
#define R_GLCDC_GR2_CLUT1048                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1048_OFFSET)
#define R_GLCDC_GR2_CLUT1049                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1049_OFFSET)
#define R_GLCDC_GR2_CLUT1050                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1050_OFFSET)
#define R_GLCDC_GR2_CLUT1051                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1051_OFFSET)
#define R_GLCDC_GR2_CLUT1052                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1052_OFFSET)
#define R_GLCDC_GR2_CLUT1053                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1053_OFFSET)
#define R_GLCDC_GR2_CLUT1054                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1054_OFFSET)
#define R_GLCDC_GR2_CLUT1055                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1055_OFFSET)
#define R_GLCDC_GR2_CLUT1056                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1056_OFFSET)
#define R_GLCDC_GR2_CLUT1057                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1057_OFFSET)
#define R_GLCDC_GR2_CLUT1058                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1058_OFFSET)
#define R_GLCDC_GR2_CLUT1059                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1059_OFFSET)
#define R_GLCDC_GR2_CLUT1060                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1060_OFFSET)
#define R_GLCDC_GR2_CLUT1061                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1061_OFFSET)
#define R_GLCDC_GR2_CLUT1062                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1062_OFFSET)
#define R_GLCDC_GR2_CLUT1063                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1063_OFFSET)
#define R_GLCDC_GR2_CLUT1064                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1064_OFFSET)
#define R_GLCDC_GR2_CLUT1065                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1065_OFFSET)
#define R_GLCDC_GR2_CLUT1066                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1066_OFFSET)
#define R_GLCDC_GR2_CLUT1067                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1067_OFFSET)
#define R_GLCDC_GR2_CLUT1068                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1068_OFFSET)
#define R_GLCDC_GR2_CLUT1069                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1069_OFFSET)
#define R_GLCDC_GR2_CLUT1070                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1070_OFFSET)
#define R_GLCDC_GR2_CLUT1071                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1071_OFFSET)
#define R_GLCDC_GR2_CLUT1072                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1072_OFFSET)
#define R_GLCDC_GR2_CLUT1073                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1073_OFFSET)
#define R_GLCDC_GR2_CLUT1074                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1074_OFFSET)
#define R_GLCDC_GR2_CLUT1075                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1075_OFFSET)
#define R_GLCDC_GR2_CLUT1076                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1076_OFFSET)
#define R_GLCDC_GR2_CLUT1077                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1077_OFFSET)
#define R_GLCDC_GR2_CLUT1078                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1078_OFFSET)
#define R_GLCDC_GR2_CLUT1079                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1079_OFFSET)
#define R_GLCDC_GR2_CLUT1080                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1080_OFFSET)
#define R_GLCDC_GR2_CLUT1081                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1081_OFFSET)
#define R_GLCDC_GR2_CLUT1082                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1082_OFFSET)
#define R_GLCDC_GR2_CLUT1083                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1083_OFFSET)
#define R_GLCDC_GR2_CLUT1084                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1084_OFFSET)
#define R_GLCDC_GR2_CLUT1085                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1085_OFFSET)
#define R_GLCDC_GR2_CLUT1086                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1086_OFFSET)
#define R_GLCDC_GR2_CLUT1087                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1087_OFFSET)
#define R_GLCDC_GR2_CLUT1088                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1088_OFFSET)
#define R_GLCDC_GR2_CLUT1089                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1089_OFFSET)
#define R_GLCDC_GR2_CLUT1090                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1090_OFFSET)
#define R_GLCDC_GR2_CLUT1091                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1091_OFFSET)
#define R_GLCDC_GR2_CLUT1092                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1092_OFFSET)
#define R_GLCDC_GR2_CLUT1093                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1093_OFFSET)
#define R_GLCDC_GR2_CLUT1094                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1094_OFFSET)
#define R_GLCDC_GR2_CLUT1095                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1095_OFFSET)
#define R_GLCDC_GR2_CLUT1096                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1096_OFFSET)
#define R_GLCDC_GR2_CLUT1097                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1097_OFFSET)
#define R_GLCDC_GR2_CLUT1098                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1098_OFFSET)
#define R_GLCDC_GR2_CLUT1099                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1099_OFFSET)
#define R_GLCDC_GR2_CLUT1100                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1100_OFFSET)
#define R_GLCDC_GR2_CLUT1101                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1101_OFFSET)
#define R_GLCDC_GR2_CLUT1102                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1102_OFFSET)
#define R_GLCDC_GR2_CLUT1103                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1103_OFFSET)
#define R_GLCDC_GR2_CLUT1104                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1104_OFFSET)
#define R_GLCDC_GR2_CLUT1105                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1105_OFFSET)
#define R_GLCDC_GR2_CLUT1106                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1106_OFFSET)
#define R_GLCDC_GR2_CLUT1107                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1107_OFFSET)
#define R_GLCDC_GR2_CLUT1108                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1108_OFFSET)
#define R_GLCDC_GR2_CLUT1109                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1109_OFFSET)
#define R_GLCDC_GR2_CLUT1110                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1110_OFFSET)
#define R_GLCDC_GR2_CLUT1111                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1111_OFFSET)
#define R_GLCDC_GR2_CLUT1112                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1112_OFFSET)
#define R_GLCDC_GR2_CLUT1113                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1113_OFFSET)
#define R_GLCDC_GR2_CLUT1114                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1114_OFFSET)
#define R_GLCDC_GR2_CLUT1115                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1115_OFFSET)
#define R_GLCDC_GR2_CLUT1116                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1116_OFFSET)
#define R_GLCDC_GR2_CLUT1117                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1117_OFFSET)
#define R_GLCDC_GR2_CLUT1118                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1118_OFFSET)
#define R_GLCDC_GR2_CLUT1119                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1119_OFFSET)
#define R_GLCDC_GR2_CLUT1120                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1120_OFFSET)
#define R_GLCDC_GR2_CLUT1121                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1121_OFFSET)
#define R_GLCDC_GR2_CLUT1122                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1122_OFFSET)
#define R_GLCDC_GR2_CLUT1123                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1123_OFFSET)
#define R_GLCDC_GR2_CLUT1124                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1124_OFFSET)
#define R_GLCDC_GR2_CLUT1125                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1125_OFFSET)
#define R_GLCDC_GR2_CLUT1126                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1126_OFFSET)
#define R_GLCDC_GR2_CLUT1127                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1127_OFFSET)
#define R_GLCDC_GR2_CLUT1128                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1128_OFFSET)
#define R_GLCDC_GR2_CLUT1129                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1129_OFFSET)
#define R_GLCDC_GR2_CLUT1130                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1130_OFFSET)
#define R_GLCDC_GR2_CLUT1131                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1131_OFFSET)
#define R_GLCDC_GR2_CLUT1132                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1132_OFFSET)
#define R_GLCDC_GR2_CLUT1133                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1133_OFFSET)
#define R_GLCDC_GR2_CLUT1134                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1134_OFFSET)
#define R_GLCDC_GR2_CLUT1135                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1135_OFFSET)
#define R_GLCDC_GR2_CLUT1136                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1136_OFFSET)
#define R_GLCDC_GR2_CLUT1137                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1137_OFFSET)
#define R_GLCDC_GR2_CLUT1138                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1138_OFFSET)
#define R_GLCDC_GR2_CLUT1139                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1139_OFFSET)
#define R_GLCDC_GR2_CLUT1140                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1140_OFFSET)
#define R_GLCDC_GR2_CLUT1141                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1141_OFFSET)
#define R_GLCDC_GR2_CLUT1142                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1142_OFFSET)
#define R_GLCDC_GR2_CLUT1143                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1143_OFFSET)
#define R_GLCDC_GR2_CLUT1144                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1144_OFFSET)
#define R_GLCDC_GR2_CLUT1145                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1145_OFFSET)
#define R_GLCDC_GR2_CLUT1146                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1146_OFFSET)
#define R_GLCDC_GR2_CLUT1147                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1147_OFFSET)
#define R_GLCDC_GR2_CLUT1148                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1148_OFFSET)
#define R_GLCDC_GR2_CLUT1149                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1149_OFFSET)
#define R_GLCDC_GR2_CLUT1150                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1150_OFFSET)
#define R_GLCDC_GR2_CLUT1151                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1151_OFFSET)
#define R_GLCDC_GR2_CLUT1152                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1152_OFFSET)
#define R_GLCDC_GR2_CLUT1153                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1153_OFFSET)
#define R_GLCDC_GR2_CLUT1154                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1154_OFFSET)
#define R_GLCDC_GR2_CLUT1155                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1155_OFFSET)
#define R_GLCDC_GR2_CLUT1156                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1156_OFFSET)
#define R_GLCDC_GR2_CLUT1157                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1157_OFFSET)
#define R_GLCDC_GR2_CLUT1158                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1158_OFFSET)
#define R_GLCDC_GR2_CLUT1159                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1159_OFFSET)
#define R_GLCDC_GR2_CLUT1160                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1160_OFFSET)
#define R_GLCDC_GR2_CLUT1161                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1161_OFFSET)
#define R_GLCDC_GR2_CLUT1162                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1162_OFFSET)
#define R_GLCDC_GR2_CLUT1163                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1163_OFFSET)
#define R_GLCDC_GR2_CLUT1164                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1164_OFFSET)
#define R_GLCDC_GR2_CLUT1165                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1165_OFFSET)
#define R_GLCDC_GR2_CLUT1166                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1166_OFFSET)
#define R_GLCDC_GR2_CLUT1167                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1167_OFFSET)
#define R_GLCDC_GR2_CLUT1168                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1168_OFFSET)
#define R_GLCDC_GR2_CLUT1169                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1169_OFFSET)
#define R_GLCDC_GR2_CLUT1170                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1170_OFFSET)
#define R_GLCDC_GR2_CLUT1171                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1171_OFFSET)
#define R_GLCDC_GR2_CLUT1172                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1172_OFFSET)
#define R_GLCDC_GR2_CLUT1173                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1173_OFFSET)
#define R_GLCDC_GR2_CLUT1174                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1174_OFFSET)
#define R_GLCDC_GR2_CLUT1175                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1175_OFFSET)
#define R_GLCDC_GR2_CLUT1176                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1176_OFFSET)
#define R_GLCDC_GR2_CLUT1177                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1177_OFFSET)
#define R_GLCDC_GR2_CLUT1178                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1178_OFFSET)
#define R_GLCDC_GR2_CLUT1179                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1179_OFFSET)
#define R_GLCDC_GR2_CLUT1180                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1180_OFFSET)
#define R_GLCDC_GR2_CLUT1181                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1181_OFFSET)
#define R_GLCDC_GR2_CLUT1182                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1182_OFFSET)
#define R_GLCDC_GR2_CLUT1183                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1183_OFFSET)
#define R_GLCDC_GR2_CLUT1184                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1184_OFFSET)
#define R_GLCDC_GR2_CLUT1185                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1185_OFFSET)
#define R_GLCDC_GR2_CLUT1186                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1186_OFFSET)
#define R_GLCDC_GR2_CLUT1187                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1187_OFFSET)
#define R_GLCDC_GR2_CLUT1188                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1188_OFFSET)
#define R_GLCDC_GR2_CLUT1189                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1189_OFFSET)
#define R_GLCDC_GR2_CLUT1190                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1190_OFFSET)
#define R_GLCDC_GR2_CLUT1191                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1191_OFFSET)
#define R_GLCDC_GR2_CLUT1192                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1192_OFFSET)
#define R_GLCDC_GR2_CLUT1193                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1193_OFFSET)
#define R_GLCDC_GR2_CLUT1194                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1194_OFFSET)
#define R_GLCDC_GR2_CLUT1195                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1195_OFFSET)
#define R_GLCDC_GR2_CLUT1196                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1196_OFFSET)
#define R_GLCDC_GR2_CLUT1197                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1197_OFFSET)
#define R_GLCDC_GR2_CLUT1198                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1198_OFFSET)
#define R_GLCDC_GR2_CLUT1199                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1199_OFFSET)
#define R_GLCDC_GR2_CLUT1200                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1200_OFFSET)
#define R_GLCDC_GR2_CLUT1201                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1201_OFFSET)
#define R_GLCDC_GR2_CLUT1202                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1202_OFFSET)
#define R_GLCDC_GR2_CLUT1203                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1203_OFFSET)
#define R_GLCDC_GR2_CLUT1204                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1204_OFFSET)
#define R_GLCDC_GR2_CLUT1205                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1205_OFFSET)
#define R_GLCDC_GR2_CLUT1206                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1206_OFFSET)
#define R_GLCDC_GR2_CLUT1207                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1207_OFFSET)
#define R_GLCDC_GR2_CLUT1208                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1208_OFFSET)
#define R_GLCDC_GR2_CLUT1209                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1209_OFFSET)
#define R_GLCDC_GR2_CLUT1210                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1210_OFFSET)
#define R_GLCDC_GR2_CLUT1211                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1211_OFFSET)
#define R_GLCDC_GR2_CLUT1212                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1212_OFFSET)
#define R_GLCDC_GR2_CLUT1213                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1213_OFFSET)
#define R_GLCDC_GR2_CLUT1214                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1214_OFFSET)
#define R_GLCDC_GR2_CLUT1215                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1215_OFFSET)
#define R_GLCDC_GR2_CLUT1216                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1216_OFFSET)
#define R_GLCDC_GR2_CLUT1217                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1217_OFFSET)
#define R_GLCDC_GR2_CLUT1218                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1218_OFFSET)
#define R_GLCDC_GR2_CLUT1219                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1219_OFFSET)
#define R_GLCDC_GR2_CLUT1220                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1220_OFFSET)
#define R_GLCDC_GR2_CLUT1221                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1221_OFFSET)
#define R_GLCDC_GR2_CLUT1222                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1222_OFFSET)
#define R_GLCDC_GR2_CLUT1223                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1223_OFFSET)
#define R_GLCDC_GR2_CLUT1224                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1224_OFFSET)
#define R_GLCDC_GR2_CLUT1225                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1225_OFFSET)
#define R_GLCDC_GR2_CLUT1226                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1226_OFFSET)
#define R_GLCDC_GR2_CLUT1227                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1227_OFFSET)
#define R_GLCDC_GR2_CLUT1228                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1228_OFFSET)
#define R_GLCDC_GR2_CLUT1229                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1229_OFFSET)
#define R_GLCDC_GR2_CLUT1230                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1230_OFFSET)
#define R_GLCDC_GR2_CLUT1231                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1231_OFFSET)
#define R_GLCDC_GR2_CLUT1232                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1232_OFFSET)
#define R_GLCDC_GR2_CLUT1233                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1233_OFFSET)
#define R_GLCDC_GR2_CLUT1234                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1234_OFFSET)
#define R_GLCDC_GR2_CLUT1235                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1235_OFFSET)
#define R_GLCDC_GR2_CLUT1236                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1236_OFFSET)
#define R_GLCDC_GR2_CLUT1237                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1237_OFFSET)
#define R_GLCDC_GR2_CLUT1238                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1238_OFFSET)
#define R_GLCDC_GR2_CLUT1239                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1239_OFFSET)
#define R_GLCDC_GR2_CLUT1240                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1240_OFFSET)
#define R_GLCDC_GR2_CLUT1241                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1241_OFFSET)
#define R_GLCDC_GR2_CLUT1242                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1242_OFFSET)
#define R_GLCDC_GR2_CLUT1243                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1243_OFFSET)
#define R_GLCDC_GR2_CLUT1244                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1244_OFFSET)
#define R_GLCDC_GR2_CLUT1245                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1245_OFFSET)
#define R_GLCDC_GR2_CLUT1246                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1246_OFFSET)
#define R_GLCDC_GR2_CLUT1247                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1247_OFFSET)
#define R_GLCDC_GR2_CLUT1248                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1248_OFFSET)
#define R_GLCDC_GR2_CLUT1249                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1249_OFFSET)
#define R_GLCDC_GR2_CLUT1250                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1250_OFFSET)
#define R_GLCDC_GR2_CLUT1251                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1251_OFFSET)
#define R_GLCDC_GR2_CLUT1252                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1252_OFFSET)
#define R_GLCDC_GR2_CLUT1253                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1253_OFFSET)
#define R_GLCDC_GR2_CLUT1254                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1254_OFFSET)
#define R_GLCDC_GR2_CLUT1255                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1255_OFFSET)
#define R_GLCDC_BG_EN                 (R_GLCDC_BASE + R_GLCDC_BG_EN_OFFSET)
#define R_GLCDC_BG_PERI                 (R_GLCDC_BASE + R_GLCDC_BG_PERI_OFFSET)
#define R_GLCDC_BG_SYNC                 (R_GLCDC_BASE + R_GLCDC_BG_SYNC_OFFSET)
#define R_GLCDC_BG_VSIZE                 (R_GLCDC_BASE + R_GLCDC_BG_VSIZE_OFFSET)
#define R_GLCDC_BG_HSIZE                 (R_GLCDC_BASE + R_GLCDC_BG_HSIZE_OFFSET)
#define R_GLCDC_BG_BGC                 (R_GLCDC_BASE + R_GLCDC_BG_BGC_OFFSET)
#define R_GLCDC_BG_MON                 (R_GLCDC_BASE + R_GLCDC_BG_MON_OFFSET)
#define R_GLCDC_GR1_VEN                 (R_GLCDC_BASE + R_GLCDC_GR1_VEN_OFFSET)
#define R_GLCDC_GR2_VEN                 (R_GLCDC_BASE + R_GLCDC_GR2_VEN_OFFSET)
#define R_GLCDC_GR1_FLMRD                 (R_GLCDC_BASE + R_GLCDC_GR1_FLMRD_OFFSET)
#define R_GLCDC_GR2_FLMRD                 (R_GLCDC_BASE + R_GLCDC_GR2_FLMRD_OFFSET)
#define R_GLCDC_GR1_FLM1                 (R_GLCDC_BASE + R_GLCDC_GR1_FLM1_OFFSET)
#define R_GLCDC_GR2_FLM1                 (R_GLCDC_BASE + R_GLCDC_GR2_FLM1_OFFSET)
#define R_GLCDC_GR1_FLM2                 (R_GLCDC_BASE + R_GLCDC_GR1_FLM2_OFFSET)
#define R_GLCDC_GR2_FLM2                 (R_GLCDC_BASE + R_GLCDC_GR2_FLM2_OFFSET)
#define R_GLCDC_GR1_FLM3                 (R_GLCDC_BASE + R_GLCDC_GR1_FLM3_OFFSET)
#define R_GLCDC_GR2_FLM3                 (R_GLCDC_BASE + R_GLCDC_GR2_FLM3_OFFSET)
#define R_GLCDC_GR1_FLM5                 (R_GLCDC_BASE + R_GLCDC_GR1_FLM5_OFFSET)
#define R_GLCDC_GR2_FLM5                 (R_GLCDC_BASE + R_GLCDC_GR2_FLM5_OFFSET)
#define R_GLCDC_GR1_FLM6                 (R_GLCDC_BASE + R_GLCDC_GR1_FLM6_OFFSET)
#define R_GLCDC_GR2_FLM6                 (R_GLCDC_BASE + R_GLCDC_GR2_FLM6_OFFSET)
#define R_GLCDC_GR1_AB1                 (R_GLCDC_BASE + R_GLCDC_GR1_AB1_OFFSET)
#define R_GLCDC_GR2_AB1                 (R_GLCDC_BASE + R_GLCDC_GR2_AB1_OFFSET)
#define R_GLCDC_GR1_AB2                 (R_GLCDC_BASE + R_GLCDC_GR1_AB2_OFFSET)
#define R_GLCDC_GR2_AB2                 (R_GLCDC_BASE + R_GLCDC_GR2_AB2_OFFSET)
#define R_GLCDC_GR1_AB3                 (R_GLCDC_BASE + R_GLCDC_GR1_AB3_OFFSET)
#define R_GLCDC_GR2_AB3                 (R_GLCDC_BASE + R_GLCDC_GR2_AB3_OFFSET)
#define R_GLCDC_GR1_AB4                 (R_GLCDC_BASE + R_GLCDC_GR1_AB4_OFFSET)
#define R_GLCDC_GR2_AB4                 (R_GLCDC_BASE + R_GLCDC_GR2_AB4_OFFSET)
#define R_GLCDC_GR1_AB5                 (R_GLCDC_BASE + R_GLCDC_GR1_AB5_OFFSET)
#define R_GLCDC_GR2_AB5                 (R_GLCDC_BASE + R_GLCDC_GR2_AB5_OFFSET)
#define R_GLCDC_GR1_AB6                 (R_GLCDC_BASE + R_GLCDC_GR1_AB6_OFFSET)
#define R_GLCDC_GR2_AB6                 (R_GLCDC_BASE + R_GLCDC_GR2_AB6_OFFSET)
#define R_GLCDC_GR1_AB7                 (R_GLCDC_BASE + R_GLCDC_GR1_AB7_OFFSET)
#define R_GLCDC_GR2_AB7                 (R_GLCDC_BASE + R_GLCDC_GR2_AB7_OFFSET)
#define R_GLCDC_GR1_AB8                 (R_GLCDC_BASE + R_GLCDC_GR1_AB8_OFFSET)
#define R_GLCDC_GR2_AB8                 (R_GLCDC_BASE + R_GLCDC_GR2_AB8_OFFSET)
#define R_GLCDC_GR1_AB9                 (R_GLCDC_BASE + R_GLCDC_GR1_AB9_OFFSET)
#define R_GLCDC_GR2_AB9                 (R_GLCDC_BASE + R_GLCDC_GR2_AB9_OFFSET)
#define R_GLCDC_GR1_BASE                 (R_GLCDC_BASE + R_GLCDC_GR1_BASE_OFFSET)
#define R_GLCDC_GR2_BASE                 (R_GLCDC_BASE + R_GLCDC_GR2_BASE_OFFSET)
#define R_GLCDC_GR1_CLUTINT                 (R_GLCDC_BASE + R_GLCDC_GR1_CLUTINT_OFFSET)
#define R_GLCDC_GR2_CLUTINT                 (R_GLCDC_BASE + R_GLCDC_GR2_CLUTINT_OFFSET)
#define R_GLCDC_GR1_MON                 (R_GLCDC_BASE + R_GLCDC_GR1_MON_OFFSET)
#define R_GLCDC_GR2_MON                 (R_GLCDC_BASE + R_GLCDC_GR2_MON_OFFSET)
#define R_GLCDC_GAMG_LATCH                 (R_GLCDC_BASE + R_GLCDC_GAMG_LATCH_OFFSET)
#define R_GLCDC_GAM_SW                 (R_GLCDC_BASE + R_GLCDC_GAM_SW_OFFSET)
#define R_GLCDC_GAMG_LUT1                 (R_GLCDC_BASE + R_GLCDC_GAMG_LUT1_OFFSET)
#define R_GLCDC_GAMG_LUT2                 (R_GLCDC_BASE + R_GLCDC_GAMG_LUT2_OFFSET)
#define R_GLCDC_GAMG_LUT3                 (R_GLCDC_BASE + R_GLCDC_GAMG_LUT3_OFFSET)
#define R_GLCDC_GAMG_LUT4                 (R_GLCDC_BASE + R_GLCDC_GAMG_LUT4_OFFSET)
#define R_GLCDC_GAMG_LUT5                 (R_GLCDC_BASE + R_GLCDC_GAMG_LUT5_OFFSET)
#define R_GLCDC_GAMG_LUT6                 (R_GLCDC_BASE + R_GLCDC_GAMG_LUT6_OFFSET)
#define R_GLCDC_GAMG_LUT7                 (R_GLCDC_BASE + R_GLCDC_GAMG_LUT7_OFFSET)
#define R_GLCDC_GAMG_LUT8                 (R_GLCDC_BASE + R_GLCDC_GAMG_LUT8_OFFSET)
#define R_GLCDC_GAMG_AREA1                 (R_GLCDC_BASE + R_GLCDC_GAMG_AREA1_OFFSET)
#define R_GLCDC_GAMG_AREA2                 (R_GLCDC_BASE + R_GLCDC_GAMG_AREA2_OFFSET)
#define R_GLCDC_GAMG_AREA3                 (R_GLCDC_BASE + R_GLCDC_GAMG_AREA3_OFFSET)
#define R_GLCDC_GAMG_AREA4                 (R_GLCDC_BASE + R_GLCDC_GAMG_AREA4_OFFSET)
#define R_GLCDC_GAMG_AREA5                 (R_GLCDC_BASE + R_GLCDC_GAMG_AREA5_OFFSET)
#define R_GLCDC_GAMB_LATCH                 (R_GLCDC_BASE + R_GLCDC_GAMB_LATCH_OFFSET)
#define R_GLCDC_GAMB_LUT1                 (R_GLCDC_BASE + R_GLCDC_GAMB_LUT1_OFFSET)
#define R_GLCDC_GAMB_LUT2                 (R_GLCDC_BASE + R_GLCDC_GAMB_LUT2_OFFSET)
#define R_GLCDC_GAMB_LUT3                 (R_GLCDC_BASE + R_GLCDC_GAMB_LUT3_OFFSET)
#define R_GLCDC_GAMB_LUT4                 (R_GLCDC_BASE + R_GLCDC_GAMB_LUT4_OFFSET)
#define R_GLCDC_GAMB_LUT5                 (R_GLCDC_BASE + R_GLCDC_GAMB_LUT5_OFFSET)
#define R_GLCDC_GAMB_LUT6                 (R_GLCDC_BASE + R_GLCDC_GAMB_LUT6_OFFSET)
#define R_GLCDC_GAMB_LUT7                 (R_GLCDC_BASE + R_GLCDC_GAMB_LUT7_OFFSET)
#define R_GLCDC_GAMB_LUT8                 (R_GLCDC_BASE + R_GLCDC_GAMB_LUT8_OFFSET)
#define R_GLCDC_GAMB_AREA1                 (R_GLCDC_BASE + R_GLCDC_GAMB_AREA1_OFFSET)
#define R_GLCDC_GAMB_AREA2                 (R_GLCDC_BASE + R_GLCDC_GAMB_AREA2_OFFSET)
#define R_GLCDC_GAMB_AREA3                 (R_GLCDC_BASE + R_GLCDC_GAMB_AREA3_OFFSET)
#define R_GLCDC_GAMB_AREA4                 (R_GLCDC_BASE + R_GLCDC_GAMB_AREA4_OFFSET)
#define R_GLCDC_GAMB_AREA5                 (R_GLCDC_BASE + R_GLCDC_GAMB_AREA5_OFFSET)
#define R_GLCDC_GAMR_LATCH                 (R_GLCDC_BASE + R_GLCDC_GAMR_LATCH_OFFSET)
#define R_GLCDC_GAMR_LUT1                 (R_GLCDC_BASE + R_GLCDC_GAMR_LUT1_OFFSET)
#define R_GLCDC_GAMR_LUT2                 (R_GLCDC_BASE + R_GLCDC_GAMR_LUT2_OFFSET)
#define R_GLCDC_GAMR_LUT3                 (R_GLCDC_BASE + R_GLCDC_GAMR_LUT3_OFFSET)
#define R_GLCDC_GAMR_LUT4                 (R_GLCDC_BASE + R_GLCDC_GAMR_LUT4_OFFSET)
#define R_GLCDC_GAMR_LUT5                 (R_GLCDC_BASE + R_GLCDC_GAMR_LUT5_OFFSET)
#define R_GLCDC_GAMR_LUT6                 (R_GLCDC_BASE + R_GLCDC_GAMR_LUT6_OFFSET)
#define R_GLCDC_GAMR_LUT7                 (R_GLCDC_BASE + R_GLCDC_GAMR_LUT7_OFFSET)
#define R_GLCDC_GAMR_LUT8                 (R_GLCDC_BASE + R_GLCDC_GAMR_LUT8_OFFSET)
#define R_GLCDC_GAMR_AREA1                 (R_GLCDC_BASE + R_GLCDC_GAMR_AREA1_OFFSET)
#define R_GLCDC_GAMR_AREA2                 (R_GLCDC_BASE + R_GLCDC_GAMR_AREA2_OFFSET)
#define R_GLCDC_GAMR_AREA3                 (R_GLCDC_BASE + R_GLCDC_GAMR_AREA3_OFFSET)
#define R_GLCDC_GAMR_AREA4                 (R_GLCDC_BASE + R_GLCDC_GAMR_AREA4_OFFSET)
#define R_GLCDC_GAMR_AREA5                 (R_GLCDC_BASE + R_GLCDC_GAMR_AREA5_OFFSET)
#define R_GLCDC_OUT_VLATCH                 (R_GLCDC_BASE + R_GLCDC_OUT_VLATCH_OFFSET)
#define R_GLCDC_OUT_SET                 (R_GLCDC_BASE + R_GLCDC_OUT_SET_OFFSET)
#define R_GLCDC_OUT_BRIGHT1                 (R_GLCDC_BASE + R_GLCDC_OUT_BRIGHT1_OFFSET)
#define R_GLCDC_OUT_BRIGHT2                 (R_GLCDC_BASE + R_GLCDC_OUT_BRIGHT2_OFFSET)
#define R_GLCDC_OUT_CONTRAST                 (R_GLCDC_BASE + R_GLCDC_OUT_CONTRAST_OFFSET)
#define R_GLCDC_OUT_PDTHA                 (R_GLCDC_BASE + R_GLCDC_OUT_PDTHA_OFFSET)
#define R_GLCDC_OUT_CLKPHASE                 (R_GLCDC_BASE + R_GLCDC_OUT_CLKPHASE_OFFSET)
#define R_GLCDC_TCON_TIM                 (R_GLCDC_BASE + R_GLCDC_TCON_TIM_OFFSET)
#define R_GLCDC_TCON_STVA1                 (R_GLCDC_BASE + R_GLCDC_TCON_STVA1_OFFSET)
#define R_GLCDC_TCON_STVA2                 (R_GLCDC_BASE + R_GLCDC_TCON_STVA2_OFFSET)
#define R_GLCDC_TCON_STVB1                 (R_GLCDC_BASE + R_GLCDC_TCON_STVB1_OFFSET)
#define R_GLCDC_TCON_STVB2                 (R_GLCDC_BASE + R_GLCDC_TCON_STVB2_OFFSET)
#define R_GLCDC_TCON_STHA1                 (R_GLCDC_BASE + R_GLCDC_TCON_STHA1_OFFSET)
#define R_GLCDC_TCON_STHA2                 (R_GLCDC_BASE + R_GLCDC_TCON_STHA2_OFFSET)
#define R_GLCDC_TCON_STHB1                 (R_GLCDC_BASE + R_GLCDC_TCON_STHB1_OFFSET)
#define R_GLCDC_TCON_STHB2                 (R_GLCDC_BASE + R_GLCDC_TCON_STHB2_OFFSET)
#define R_GLCDC_TCON_DE                 (R_GLCDC_BASE + R_GLCDC_TCON_DE_OFFSET)
#define R_GLCDC_SYSCNT_DTCTEN                 (R_GLCDC_BASE + R_GLCDC_SYSCNT_DTCTEN_OFFSET)
#define R_GLCDC_SYSCNT_INTEN                 (R_GLCDC_BASE + R_GLCDC_SYSCNT_INTEN_OFFSET)
#define R_GLCDC_SYSCNT_STCLR                 (R_GLCDC_BASE + R_GLCDC_SYSCNT_STCLR_OFFSET)
#define R_GLCDC_SYSCNT_STMON                 (R_GLCDC_BASE + R_GLCDC_SYSCNT_STMON_OFFSET)
#define R_GLCDC_SYSCNT_PANEL_CLK                 (R_GLCDC_BASE + R_GLCDC_SYSCNT_PANEL_CLK_OFFSET)

/* Register bit definitions */
/* GR1_CLUT Register bit definitions */
#define R_GLCDC_GR1_CLUT_B_SHIFT                  (0)  /* B value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR1_CLUT_B_MASK                   0xff

#define R_GLCDC_GR1_CLUT_G_SHIFT                  (8)  /* G value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR1_CLUT_G_MASK                   0xff00

#define R_GLCDC_GR1_CLUT_R_SHIFT                  (16)  /* R value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR1_CLUT_R_MASK                   0xff0000

#define R_GLCDC_GR1_CLUT_A_SHIFT                  (24)  /* Alpha blending value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR1_CLUT_A_MASK                   0xff000000

/* GR1_CLUT Register bit definitions */
#define R_GLCDC_GR1_CLUT_B_SHIFT                  (0)  /* B value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR1_CLUT_B_MASK                   0xff

#define R_GLCDC_GR1_CLUT_G_SHIFT                  (8)  /* G value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR1_CLUT_G_MASK                   0xff00

#define R_GLCDC_GR1_CLUT_R_SHIFT                  (16)  /* R value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR1_CLUT_R_MASK                   0xff0000

#define R_GLCDC_GR1_CLUT_A_SHIFT                  (24)  /* Alpha blending value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR1_CLUT_A_MASK                   0xff000000

/* GR2_CLUT Register bit definitions */
#define R_GLCDC_GR2_CLUT_B_SHIFT                  (0)  /* B value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR2_CLUT_B_MASK                   0xff

#define R_GLCDC_GR2_CLUT_G_SHIFT                  (8)  /* G value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR2_CLUT_G_MASK                   0xff00

#define R_GLCDC_GR2_CLUT_R_SHIFT                  (16)  /* R value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR2_CLUT_R_MASK                   0xff0000

#define R_GLCDC_GR2_CLUT_A_SHIFT                  (24)  /* Alpha blending value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR2_CLUT_A_MASK                   0xff000000

/* GR2_CLUT Register bit definitions */
#define R_GLCDC_GR2_CLUT_B_SHIFT                  (0)  /* B value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR2_CLUT_B_MASK                   0xff

#define R_GLCDC_GR2_CLUT_G_SHIFT                  (8)  /* G value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR2_CLUT_G_MASK                   0xff00

#define R_GLCDC_GR2_CLUT_R_SHIFT                  (16)  /* R value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR2_CLUT_R_MASK                   0xff0000

#define R_GLCDC_GR2_CLUT_A_SHIFT                  (24)  /* Alpha blending value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR2_CLUT_A_MASK                   0xff000000

/* BG_EN Register bit definitions */
#define R_GLCDC_BG_EN_EN                          (1 << 0)  /* Background Plane Operation Enable */

#define R_GLCDC_BG_EN_VEN                         (1 << 8)  /* Control of GLCDC Internal Register Value Reflection to Internal Operations */

#define R_GLCDC_BG_EN_SWRST                       (1 << 16)  /* Software Reset Control */

/* BG_PERI Register bit definitions */
#define R_GLCDC_BG_PERI_FH_SHIFT                  (0)  /* Background Plane Horizontal Synchronization Signal Period */
#define R_GLCDC_BG_PERI_FH_MASK                   0x7ff
#  define R_GLCDC_BG_PERI_FH_0X017                        (0 << R_GLCDC_BG_PERI_FH_SHIFT)  /* 24 cycles (pixels) */
#  define R_GLCDC_BG_PERI_FH_0X3FF                        (0 << R_GLCDC_BG_PERI_FH_SHIFT)  /* 1024 cycles (pixels) */
#  define R_GLCDC_BG_PERI_FH_0X7FF                        (0 << R_GLCDC_BG_PERI_FH_SHIFT)  /* 2048 cycles (pixels) */

#define R_GLCDC_BG_PERI_FV_SHIFT                  (16)  /* Background Plane Vertical Synchronization Signal Period */
#define R_GLCDC_BG_PERI_FV_MASK                   0x7ff0000
#  define R_GLCDC_BG_PERI_FV_0X013                        (0 << R_GLCDC_BG_PERI_FV_SHIFT)  /* 20 lines */
#  define R_GLCDC_BG_PERI_FV_0X3FF                        (0 << R_GLCDC_BG_PERI_FV_SHIFT)  /* 1024 lines */
#  define R_GLCDC_BG_PERI_FV_0X7FF                        (0 << R_GLCDC_BG_PERI_FV_SHIFT)  /* 2048 lines */

/* BG_SYNC Register bit definitions */
#define R_GLCDC_BG_SYNC_HP_SHIFT                  (0)  /* Background Plane Horizontal Synchronization Signal Assertion Position */
#define R_GLCDC_BG_SYNC_HP_MASK                   0xf
#  define R_GLCDC_BG_SYNC_HP_0X0                          (0 << R_GLCDC_BG_SYNC_HP_SHIFT)  /* Setting prohibited */

#define R_GLCDC_BG_SYNC_VP_SHIFT                  (16)  /* Background Plane Vertical Synchronization Assertion Position */
#define R_GLCDC_BG_SYNC_VP_MASK                   0xf0000
#  define R_GLCDC_BG_SYNC_VP_0X0                          (0 << R_GLCDC_BG_SYNC_VP_SHIFT)  /* Setting prohibited */

/* BG_VSIZE Register bit definitions */
#define R_GLCDC_BG_VSIZE_VW_SHIFT                 (0)  /* Background Plane Vertical Valid Pixel Width */
#define R_GLCDC_BG_VSIZE_VW_MASK                  0x7ff

#define R_GLCDC_BG_VSIZE_VP_SHIFT                 (16)  /* Background Plane Vertical Valid Pixel Start Position */
#define R_GLCDC_BG_VSIZE_VP_MASK                  0x7ff0000

/* BG_HSIZE Register bit definitions */
#define R_GLCDC_BG_HSIZE_HW_SHIFT                 (0)  /* Background Plane Horizontal Valid Pixel Width */
#define R_GLCDC_BG_HSIZE_HW_MASK                  0x7ff

#define R_GLCDC_BG_HSIZE_HP_SHIFT                 (16)  /* Background Plane Horizontal Valid Pixel Start Position */
#define R_GLCDC_BG_HSIZE_HP_MASK                  0x7ff0000

/* BG_BGC Register bit definitions */
#define R_GLCDC_BG_BGC_B_SHIFT                    (0)  /* Background Plane Valid Pixel Area B Value */
#define R_GLCDC_BG_BGC_B_MASK                     0xff

#define R_GLCDC_BG_BGC_G_SHIFT                    (8)  /* Background Plane Valid Pixel Area G Value */
#define R_GLCDC_BG_BGC_G_MASK                     0xff00

#define R_GLCDC_BG_BGC_R_SHIFT                    (16)  /* Background Plane Valid Pixel Area R Value */
#define R_GLCDC_BG_BGC_R_MASK                     0xff0000

/* BG_MON Register bit definitions */
#define R_GLCDC_BG_MON_EN                         (1 << 0)  /* Background Plane Operation Monitor */

#define R_GLCDC_BG_MON_VEN                        (1 << 8)  /* Entire Module Internal Operation Reflection Control Signal Monitor */

#define R_GLCDC_BG_MON_SWRST                      (1 << 16)  /* Entire Module SW Reset State Monitor */

/* GR_VEN Register bit definitions */
#define R_GLCDC_GR_VEN_PVEN                       (1 << 0)  /* This bit is cleared to 0 by an internal source. */

/* GR_FLMRD Register bit definitions */
#define R_GLCDC_GR_FLMRD_RENB                     (1 << 0)  /* Graphics Data Read Enable */

/* GR_FLM Register bit definitions */
#define R_GLCDC_GR_FLM_BSTMD_SHIFT                (0)  /* Burst Transfer Control for Graphics Data Access */
#define R_GLCDC_GR_FLM_BSTMD_MASK                 0x3
#  define R_GLCDC_GR_FLM_BSTMD_11                         (3 << R_GLCDC_GR_FLM_BSTMD_SHIFT)  /* 16-beat increment burst transfer (64-byte boundary) */

/* GR_FLM Register bit definitions */
#define R_GLCDC_GR_FLM_BASE_SHIFT                 (0)  /* Base Address for Accessing Graphics Data */
#define R_GLCDC_GR_FLM_BASE_MASK                  0xffffffff

/* GR_FLM Register bit definitions */
#define R_GLCDC_GR_FLM_LNOFF_SHIFT                (16)  /* Macro Line Offset Address for Accessing Graphics Data */
#define R_GLCDC_GR_FLM_LNOFF_MASK                 0xffff0000

/* GR_FLM Register bit definitions */
#define R_GLCDC_GR_FLM_DATANUM_SHIFT              (0)  /* Number of Data Transfer Times Per Line for Accessing Graphics Data */
#define R_GLCDC_GR_FLM_DATANUM_MASK               0xffff

#define R_GLCDC_GR_FLM_LNNUM_SHIFT                (16)  /* Number of Lines Per Frame for Accessing Graphics Data */
#define R_GLCDC_GR_FLM_LNNUM_MASK                 0x7ff0000

/* GR_FLM Register bit definitions */
#define R_GLCDC_GR_FLM_FORMAT_SHIFT               (28)  /* Data Format for Accessing Graphics Data */
#define R_GLCDC_GR_FLM_FORMAT_MASK                0x70000000
#  define R_GLCDC_GR_FLM_FORMAT_000                       (0 << R_GLCDC_GR_FLM_FORMAT_SHIFT)  /* RGB565 (16 bits/pixel) */
#  define R_GLCDC_GR_FLM_FORMAT_001                       (1 << R_GLCDC_GR_FLM_FORMAT_SHIFT)  /* RGB888 (32 bits/pixel, 8 bits on the MSB side are invalid) */
#  define R_GLCDC_GR_FLM_FORMAT_010                       (2 << R_GLCDC_GR_FLM_FORMAT_SHIFT)  /* ARGB1555 (16 bits/pixel, 1 bit of A is LUT data) */
#  define R_GLCDC_GR_FLM_FORMAT_011                       (3 << R_GLCDC_GR_FLM_FORMAT_SHIFT)  /* ARGB4444 (16 bits/pixel) */
#  define R_GLCDC_GR_FLM_FORMAT_100                       (4 << R_GLCDC_GR_FLM_FORMAT_SHIFT)  /* ARGB8888 (32 bits/pixel) */
#  define R_GLCDC_GR_FLM_FORMAT_101                       (5 << R_GLCDC_GR_FLM_FORMAT_SHIFT)  /* CLUT8 (8 bits/pixel) */
#  define R_GLCDC_GR_FLM_FORMAT_110                       (6 << R_GLCDC_GR_FLM_FORMAT_SHIFT)  /* CLUT4 (4 bits/pixel) */
#  define R_GLCDC_GR_FLM_FORMAT_111                       (7 << R_GLCDC_GR_FLM_FORMAT_SHIFT)  /* CLUT1 (1 bit/pixel) */

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_DISPSEL_SHIFT               (0)  /* Graphics Display Plane Control */
#define R_GLCDC_GR_AB_DISPSEL_MASK                0x3
#  define R_GLCDC_GR_AB_DISPSEL_00                        (0 << R_GLCDC_GR_AB_DISPSEL_SHIFT)  /* Background color display (value set in the GRn_BASE register) */
#  define R_GLCDC_GR_AB_DISPSEL_01                        (1 << R_GLCDC_GR_AB_DISPSEL_SHIFT)  /* Lower-layer graphics display */
#  define R_GLCDC_GR_AB_DISPSEL_10                        (2 << R_GLCDC_GR_AB_DISPSEL_SHIFT)  /* Current graphics display */
#  define R_GLCDC_GR_AB_DISPSEL_11                        (3 << R_GLCDC_GR_AB_DISPSEL_SHIFT)  /* Blended display of lower-layer graphics (input image from the previous stage) and current graphics (data read from the GLCDC0 and GLCDC1 bus) */

#define R_GLCDC_GR_AB_GRCDISPON                   (1 << 4)  /* Graphics Image Area Border Display Control */

#define R_GLCDC_GR_AB_ARCDISPON                   (1 << 8)  /* Image Area Border Display Control for Rectangular Area Alpha Blending */

#define R_GLCDC_GR_AB_ARCON                       (1 << 12)  /* Rectangular Area Alpha Blending Control */

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_GRCVW_SHIFT                 (0)  /* Vertical Width of Graphics Image Area */
#define R_GLCDC_GR_AB_GRCVW_MASK                  0x7ff

#define R_GLCDC_GR_AB_GRCVS_SHIFT                 (16)  /* Vertical Start Position of Graphics Image Area */
#define R_GLCDC_GR_AB_GRCVS_MASK                  0x7ff0000

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_GRCHW_SHIFT                 (0)  /* Horizontal Width of Graphics Image Area */
#define R_GLCDC_GR_AB_GRCHW_MASK                  0x7ff

#define R_GLCDC_GR_AB_GRCHS_SHIFT                 (16)  /* Horizontal Start Position of Graphics Image Area */
#define R_GLCDC_GR_AB_GRCHS_MASK                  0x7ff0000

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_ARCVW_SHIFT                 (0)  /* Vertical Width of Rectangular Area Alpha Blending Image Area */
#define R_GLCDC_GR_AB_ARCVW_MASK                  0x7ff

#define R_GLCDC_GR_AB_ARCVS_SHIFT                 (16)  /* Vertical Start Position of Rectangular Area Alpha Blending Image Area */
#define R_GLCDC_GR_AB_ARCVS_MASK                  0x7ff0000

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_ARCHW_SHIFT                 (0)  /* Horizontal Width of Rectangular Area Alpha Blending Image Area */
#define R_GLCDC_GR_AB_ARCHW_MASK                  0x7ff

#define R_GLCDC_GR_AB_ARCHS_SHIFT                 (16)  /* Horizontal Start Position of Rectangular Area Alpha Blending Image Area */
#define R_GLCDC_GR_AB_ARCHS_MASK                  0x7ff0000

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_ARCRATE_SHIFT               (0)  /* Frame Rate for Alpha Blending in Rectangular Area */
#define R_GLCDC_GR_AB_ARCRATE_MASK                0xff

#define R_GLCDC_GR_AB_ARCCOEF_SHIFT               (16)  /* Alpha Coefficient for Alpha Blending in Rectangular Area */
#define R_GLCDC_GR_AB_ARCCOEF_MASK                0x1ff0000

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_CKON                        (1 << 0)  /* RGB-Index Chroma-Key Processing Control */

#define R_GLCDC_GR_AB_ARCDEF_SHIFT                (16)  /* Initial Alpha Value for Alpha Blending in Rectangular Area */
#define R_GLCDC_GR_AB_ARCDEF_MASK                 0xff0000

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_CKKR_SHIFT                  (0)  /* R Signal for RGB-Index Chroma-Key Processing */
#define R_GLCDC_GR_AB_CKKR_MASK                   0xff

#define R_GLCDC_GR_AB_CKKB_SHIFT                  (8)  /* B Signal for RGB-Index Chroma-Key Processing */
#define R_GLCDC_GR_AB_CKKB_MASK                   0xff00

#define R_GLCDC_GR_AB_CKKG_SHIFT                  (16)  /* G Signal for RGB-Index Chroma-Key Processing */
#define R_GLCDC_GR_AB_CKKG_MASK                   0xff0000

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_CKR_SHIFT                   (0)  /* R Value after RGB-Index Chroma-Key Processing Replacement */
#define R_GLCDC_GR_AB_CKR_MASK                    0xff

#define R_GLCDC_GR_AB_CKB_SHIFT                   (8)  /* B Value after RGB-Index Chroma-Key Processing Replacement */
#define R_GLCDC_GR_AB_CKB_MASK                    0xff00

#define R_GLCDC_GR_AB_CKG_SHIFT                   (16)  /* G Value after RGB-Index Chroma-Key Processing Replacement */
#define R_GLCDC_GR_AB_CKG_MASK                    0xff0000

#define R_GLCDC_GR_AB_CKA_SHIFT                   (24)  /* A Value after RGB-Index Chroma-Key Processing Replacement */
#define R_GLCDC_GR_AB_CKA_MASK                    0xff000000

/* GR_BASE Register bit definitions */
#define R_GLCDC_GR_BASE_R_SHIFT                   (0)  /* Background Color R Value */
#define R_GLCDC_GR_BASE_R_MASK                    0xff

#define R_GLCDC_GR_BASE_B_SHIFT                   (8)  /* Background Color B Value */
#define R_GLCDC_GR_BASE_B_MASK                    0xff00

#define R_GLCDC_GR_BASE_G_SHIFT                   (16)  /* Background Color G Value */
#define R_GLCDC_GR_BASE_G_MASK                    0xff0000

/* GR_CLUTINT Register bit definitions */
#define R_GLCDC_GR_CLUTINT_LINE_SHIFT             (0)  /* Number of Detection Lines */
#define R_GLCDC_GR_CLUTINT_LINE_MASK              0x7ff

#define R_GLCDC_GR_CLUTINT_SEL                    (1 << 16)  /* CLUT Table Control */

/* GR_MON Register bit definitions */
#define R_GLCDC_GR_MON_ARCST                      (1 << 0)  /* Status Monitor for Alpha Blending in Rectangular Area */

#define R_GLCDC_GR_MON_UNDFLST                    (1 << 16)  /* Underflow Status Monitor */

/* GAMG_LATCH Register bit definitions */
#define R_GLCDC_GAMG_LATCH_VEN                    (1 << 0)  /* Control of Gamma Correction × Module Register Value Reflection to Internal Operations */

/* GAM_SW Register bit definitions */
#define R_GLCDC_GAM_SW_GAMON                      (1 << 0)  /* Gamma Correction On/Off Control */

/* GAMG_LUT1 Register bit definitions */
#define R_GLCDC_GAMG_LUT1_GAIN01_SHIFT            (0)  /* Gain Value of Area 1 */
#define R_GLCDC_GAMG_LUT1_GAIN01_MASK             0x7ff

#define R_GLCDC_GAMG_LUT1_GAIN00_SHIFT            (16)  /* Gain Value of Area 0 */
#define R_GLCDC_GAMG_LUT1_GAIN00_MASK             0x7ff0000

/* GAMG_LUT2 Register bit definitions */
#define R_GLCDC_GAMG_LUT2_GAIN03_SHIFT            (0)  /* Gain Value of Area 3 */
#define R_GLCDC_GAMG_LUT2_GAIN03_MASK             0x7ff

#define R_GLCDC_GAMG_LUT2_GAIN02_SHIFT            (16)  /* Gain Value of Area 2 */
#define R_GLCDC_GAMG_LUT2_GAIN02_MASK             0x7ff0000

/* GAMG_LUT3 Register bit definitions */
#define R_GLCDC_GAMG_LUT3_GAIN05_SHIFT            (0)  /* Gain Value of Area 5 */
#define R_GLCDC_GAMG_LUT3_GAIN05_MASK             0x7ff

#define R_GLCDC_GAMG_LUT3_GAIN04_SHIFT            (16)  /* Gain Value of Area 4 */
#define R_GLCDC_GAMG_LUT3_GAIN04_MASK             0x7ff0000

/* GAMG_LUT4 Register bit definitions */
#define R_GLCDC_GAMG_LUT4_GAIN07_SHIFT            (0)  /* Gain Value of Area 7 */
#define R_GLCDC_GAMG_LUT4_GAIN07_MASK             0x7ff

#define R_GLCDC_GAMG_LUT4_GAIN06_SHIFT            (16)  /* Gain Value of Area 6 */
#define R_GLCDC_GAMG_LUT4_GAIN06_MASK             0x7ff0000

/* GAMG_LUT5 Register bit definitions */
#define R_GLCDC_GAMG_LUT5_GAIN09_SHIFT            (0)  /* Gain Value of Area 9 */
#define R_GLCDC_GAMG_LUT5_GAIN09_MASK             0x7ff

#define R_GLCDC_GAMG_LUT5_GAIN08_SHIFT            (16)  /* Gain Value of Area 8 */
#define R_GLCDC_GAMG_LUT5_GAIN08_MASK             0x7ff0000

/* GAMG_LUT6 Register bit definitions */
#define R_GLCDC_GAMG_LUT6_GAIN11_SHIFT            (0)  /* Gain Value of Area 11 */
#define R_GLCDC_GAMG_LUT6_GAIN11_MASK             0x7ff

#define R_GLCDC_GAMG_LUT6_GAIN10_SHIFT            (16)  /* Gain Value of Area 10 */
#define R_GLCDC_GAMG_LUT6_GAIN10_MASK             0x7ff0000

/* GAMG_LUT7 Register bit definitions */
#define R_GLCDC_GAMG_LUT7_GAIN13_SHIFT            (0)  /* Gain Value of Area 13 */
#define R_GLCDC_GAMG_LUT7_GAIN13_MASK             0x7ff

#define R_GLCDC_GAMG_LUT7_GAIN012_SHIFT           (16)  /* Gain Value of Area 12 */
#define R_GLCDC_GAMG_LUT7_GAIN012_MASK            0x7ff0000

/* GAMG_LUT8 Register bit definitions */
#define R_GLCDC_GAMG_LUT8_GAIN15_SHIFT            (0)  /* Gain Value of Area 15 */
#define R_GLCDC_GAMG_LUT8_GAIN15_MASK             0x7ff

#define R_GLCDC_GAMG_LUT8_GAIN14_SHIFT            (16)  /* Gain Value of Area 14 */
#define R_GLCDC_GAMG_LUT8_GAIN14_MASK             0x7ff0000

/* GAMG_AREA1 Register bit definitions */
#define R_GLCDC_GAMG_AREA1_TH03_SHIFT             (0)  /* Start Threshold of Area 3 */
#define R_GLCDC_GAMG_AREA1_TH03_MASK              0x3ff

#define R_GLCDC_GAMG_AREA1_TH02_SHIFT             (10)  /* Start Threshold of Area 2 */
#define R_GLCDC_GAMG_AREA1_TH02_MASK              0xffc00

#define R_GLCDC_GAMG_AREA1_TH01_SHIFT             (20)  /* Start Threshold of Area 1 */
#define R_GLCDC_GAMG_AREA1_TH01_MASK              0x3ff00000

/* GAMG_AREA2 Register bit definitions */
#define R_GLCDC_GAMG_AREA2_TH06_SHIFT             (0)  /* Start Threshold of Area 6 */
#define R_GLCDC_GAMG_AREA2_TH06_MASK              0x3ff

#define R_GLCDC_GAMG_AREA2_TH05_SHIFT             (10)  /* Start Threshold of Area 5 */
#define R_GLCDC_GAMG_AREA2_TH05_MASK              0xffc00

#define R_GLCDC_GAMG_AREA2_TH04_SHIFT             (20)  /* Start Threshold of Area 4 */
#define R_GLCDC_GAMG_AREA2_TH04_MASK              0x3ff00000

/* GAMG_AREA3 Register bit definitions */
#define R_GLCDC_GAMG_AREA3_TH09_SHIFT             (0)  /* Start Threshold of Area 9 */
#define R_GLCDC_GAMG_AREA3_TH09_MASK              0x3ff

#define R_GLCDC_GAMG_AREA3_TH08_SHIFT             (10)  /* Start Threshold of Area 8 */
#define R_GLCDC_GAMG_AREA3_TH08_MASK              0xffc00

#define R_GLCDC_GAMG_AREA3_TH07_SHIFT             (20)  /* Start Threshold of Area 7 */
#define R_GLCDC_GAMG_AREA3_TH07_MASK              0x3ff00000

/* GAMG_AREA4 Register bit definitions */
#define R_GLCDC_GAMG_AREA4_TH12_SHIFT             (0)  /* Start Threshold of Area 12 */
#define R_GLCDC_GAMG_AREA4_TH12_MASK              0x3ff

#define R_GLCDC_GAMG_AREA4_TH11_SHIFT             (10)  /* Start Threshold of Area 11 */
#define R_GLCDC_GAMG_AREA4_TH11_MASK              0xffc00

#define R_GLCDC_GAMG_AREA4_TH10_SHIFT             (20)  /* Start Threshold of Area 10 */
#define R_GLCDC_GAMG_AREA4_TH10_MASK              0x3ff00000

/* GAMG_AREA5 Register bit definitions */
#define R_GLCDC_GAMG_AREA5_TH15_SHIFT             (0)  /* Start Threshold of Area 15 */
#define R_GLCDC_GAMG_AREA5_TH15_MASK              0x3ff

#define R_GLCDC_GAMG_AREA5_TH14_SHIFT             (10)  /* Start Threshold of Area 14 */
#define R_GLCDC_GAMG_AREA5_TH14_MASK              0xffc00

#define R_GLCDC_GAMG_AREA5_TH13_SHIFT             (20)  /* Start Threshold of Area 13 */
#define R_GLCDC_GAMG_AREA5_TH13_MASK              0x3ff00000

/* GAMB_LATCH Register bit definitions */
#define R_GLCDC_GAMB_LATCH_VEN                    (1 << 0)  /* Control of Gamma Correction × Module Register Value Reflection to Internal Operations */

/* GAMB_LUT1 Register bit definitions */
#define R_GLCDC_GAMB_LUT1_GAIN01_SHIFT            (0)  /* Gain Value of Area 1 */
#define R_GLCDC_GAMB_LUT1_GAIN01_MASK             0x7ff

#define R_GLCDC_GAMB_LUT1_GAIN00_SHIFT            (16)  /* Gain Value of Area 0 */
#define R_GLCDC_GAMB_LUT1_GAIN00_MASK             0x7ff0000

/* GAMB_LUT2 Register bit definitions */
#define R_GLCDC_GAMB_LUT2_GAIN03_SHIFT            (0)  /* Gain Value of Area 3 */
#define R_GLCDC_GAMB_LUT2_GAIN03_MASK             0x7ff

#define R_GLCDC_GAMB_LUT2_GAIN02_SHIFT            (16)  /* Gain Value of Area 2 */
#define R_GLCDC_GAMB_LUT2_GAIN02_MASK             0x7ff0000

/* GAMB_LUT3 Register bit definitions */
#define R_GLCDC_GAMB_LUT3_GAIN05_SHIFT            (0)  /* Gain Value of Area 5 */
#define R_GLCDC_GAMB_LUT3_GAIN05_MASK             0x7ff

#define R_GLCDC_GAMB_LUT3_GAIN04_SHIFT            (16)  /* Gain Value of Area 4 */
#define R_GLCDC_GAMB_LUT3_GAIN04_MASK             0x7ff0000

/* GAMB_LUT4 Register bit definitions */
#define R_GLCDC_GAMB_LUT4_GAIN07_SHIFT            (0)  /* Gain Value of Area 7 */
#define R_GLCDC_GAMB_LUT4_GAIN07_MASK             0x7ff

#define R_GLCDC_GAMB_LUT4_GAIN06_SHIFT            (16)  /* Gain Value of Area 6 */
#define R_GLCDC_GAMB_LUT4_GAIN06_MASK             0x7ff0000

/* GAMB_LUT5 Register bit definitions */
#define R_GLCDC_GAMB_LUT5_GAIN09_SHIFT            (0)  /* Gain Value of Area 9 */
#define R_GLCDC_GAMB_LUT5_GAIN09_MASK             0x7ff

#define R_GLCDC_GAMB_LUT5_GAIN08_SHIFT            (16)  /* Gain Value of Area 8 */
#define R_GLCDC_GAMB_LUT5_GAIN08_MASK             0x7ff0000

/* GAMB_LUT6 Register bit definitions */
#define R_GLCDC_GAMB_LUT6_GAIN11_SHIFT            (0)  /* Gain Value of Area 11 */
#define R_GLCDC_GAMB_LUT6_GAIN11_MASK             0x7ff

#define R_GLCDC_GAMB_LUT6_GAIN10_SHIFT            (16)  /* Gain Value of Area 10 */
#define R_GLCDC_GAMB_LUT6_GAIN10_MASK             0x7ff0000

/* GAMB_LUT7 Register bit definitions */
#define R_GLCDC_GAMB_LUT7_GAIN13_SHIFT            (0)  /* Gain Value of Area 13 */
#define R_GLCDC_GAMB_LUT7_GAIN13_MASK             0x7ff

#define R_GLCDC_GAMB_LUT7_GAIN012_SHIFT           (16)  /* Gain Value of Area 12 */
#define R_GLCDC_GAMB_LUT7_GAIN012_MASK            0x7ff0000

/* GAMB_LUT8 Register bit definitions */
#define R_GLCDC_GAMB_LUT8_GAIN15_SHIFT            (0)  /* Gain Value of Area 15 */
#define R_GLCDC_GAMB_LUT8_GAIN15_MASK             0x7ff

#define R_GLCDC_GAMB_LUT8_GAIN14_SHIFT            (16)  /* Gain Value of Area 14 */
#define R_GLCDC_GAMB_LUT8_GAIN14_MASK             0x7ff0000

/* GAMB_AREA1 Register bit definitions */
#define R_GLCDC_GAMB_AREA1_TH03_SHIFT             (0)  /* Start Threshold of Area 3 */
#define R_GLCDC_GAMB_AREA1_TH03_MASK              0x3ff

#define R_GLCDC_GAMB_AREA1_TH02_SHIFT             (10)  /* Start Threshold of Area 2 */
#define R_GLCDC_GAMB_AREA1_TH02_MASK              0xffc00

#define R_GLCDC_GAMB_AREA1_TH01_SHIFT             (20)  /* Start Threshold of Area 1 */
#define R_GLCDC_GAMB_AREA1_TH01_MASK              0x3ff00000

/* GAMB_AREA2 Register bit definitions */
#define R_GLCDC_GAMB_AREA2_TH06_SHIFT             (0)  /* Start Threshold of Area 6 */
#define R_GLCDC_GAMB_AREA2_TH06_MASK              0x3ff

#define R_GLCDC_GAMB_AREA2_TH05_SHIFT             (10)  /* Start Threshold of Area 5 */
#define R_GLCDC_GAMB_AREA2_TH05_MASK              0xffc00

#define R_GLCDC_GAMB_AREA2_TH04_SHIFT             (20)  /* Start Threshold of Area 4 */
#define R_GLCDC_GAMB_AREA2_TH04_MASK              0x3ff00000

/* GAMB_AREA3 Register bit definitions */
#define R_GLCDC_GAMB_AREA3_TH09_SHIFT             (0)  /* Start Threshold of Area 9 */
#define R_GLCDC_GAMB_AREA3_TH09_MASK              0x3ff

#define R_GLCDC_GAMB_AREA3_TH08_SHIFT             (10)  /* Start Threshold of Area 8 */
#define R_GLCDC_GAMB_AREA3_TH08_MASK              0xffc00

#define R_GLCDC_GAMB_AREA3_TH07_SHIFT             (20)  /* Start Threshold of Area 7 */
#define R_GLCDC_GAMB_AREA3_TH07_MASK              0x3ff00000

/* GAMB_AREA4 Register bit definitions */
#define R_GLCDC_GAMB_AREA4_TH12_SHIFT             (0)  /* Start Threshold of Area 12 */
#define R_GLCDC_GAMB_AREA4_TH12_MASK              0x3ff

#define R_GLCDC_GAMB_AREA4_TH11_SHIFT             (10)  /* Start Threshold of Area 11 */
#define R_GLCDC_GAMB_AREA4_TH11_MASK              0xffc00

#define R_GLCDC_GAMB_AREA4_TH10_SHIFT             (20)  /* Start Threshold of Area 10 */
#define R_GLCDC_GAMB_AREA4_TH10_MASK              0x3ff00000

/* GAMB_AREA5 Register bit definitions */
#define R_GLCDC_GAMB_AREA5_TH15_SHIFT             (0)  /* Start Threshold of Area 15 */
#define R_GLCDC_GAMB_AREA5_TH15_MASK              0x3ff

#define R_GLCDC_GAMB_AREA5_TH14_SHIFT             (10)  /* Start Threshold of Area 14 */
#define R_GLCDC_GAMB_AREA5_TH14_MASK              0xffc00

#define R_GLCDC_GAMB_AREA5_TH13_SHIFT             (20)  /* Start Threshold of Area 13 */
#define R_GLCDC_GAMB_AREA5_TH13_MASK              0x3ff00000

/* GAMR_LATCH Register bit definitions */
#define R_GLCDC_GAMR_LATCH_VEN                    (1 << 0)  /* Control of Gamma Correction × Module Register Value Reflection to Internal Operations */

/* GAMR_LUT1 Register bit definitions */
#define R_GLCDC_GAMR_LUT1_GAIN01_SHIFT            (0)  /* Gain Value of Area 1 */
#define R_GLCDC_GAMR_LUT1_GAIN01_MASK             0x7ff

#define R_GLCDC_GAMR_LUT1_GAIN00_SHIFT            (16)  /* Gain Value of Area 0 */
#define R_GLCDC_GAMR_LUT1_GAIN00_MASK             0x7ff0000

/* GAMR_LUT2 Register bit definitions */
#define R_GLCDC_GAMR_LUT2_GAIN03_SHIFT            (0)  /* Gain Value of Area 3 */
#define R_GLCDC_GAMR_LUT2_GAIN03_MASK             0x7ff

#define R_GLCDC_GAMR_LUT2_GAIN02_SHIFT            (16)  /* Gain Value of Area 2 */
#define R_GLCDC_GAMR_LUT2_GAIN02_MASK             0x7ff0000

/* GAMR_LUT3 Register bit definitions */
#define R_GLCDC_GAMR_LUT3_GAIN05_SHIFT            (0)  /* Gain Value of Area 5 */
#define R_GLCDC_GAMR_LUT3_GAIN05_MASK             0x7ff

#define R_GLCDC_GAMR_LUT3_GAIN04_SHIFT            (16)  /* Gain Value of Area 4 */
#define R_GLCDC_GAMR_LUT3_GAIN04_MASK             0x7ff0000

/* GAMR_LUT4 Register bit definitions */
#define R_GLCDC_GAMR_LUT4_GAIN07_SHIFT            (0)  /* Gain Value of Area 7 */
#define R_GLCDC_GAMR_LUT4_GAIN07_MASK             0x7ff

#define R_GLCDC_GAMR_LUT4_GAIN06_SHIFT            (16)  /* Gain Value of Area 6 */
#define R_GLCDC_GAMR_LUT4_GAIN06_MASK             0x7ff0000

/* GAMR_LUT5 Register bit definitions */
#define R_GLCDC_GAMR_LUT5_GAIN09_SHIFT            (0)  /* Gain Value of Area 9 */
#define R_GLCDC_GAMR_LUT5_GAIN09_MASK             0x7ff

#define R_GLCDC_GAMR_LUT5_GAIN08_SHIFT            (16)  /* Gain Value of Area 8 */
#define R_GLCDC_GAMR_LUT5_GAIN08_MASK             0x7ff0000

/* GAMR_LUT6 Register bit definitions */
#define R_GLCDC_GAMR_LUT6_GAIN11_SHIFT            (0)  /* Gain Value of Area 11 */
#define R_GLCDC_GAMR_LUT6_GAIN11_MASK             0x7ff

#define R_GLCDC_GAMR_LUT6_GAIN10_SHIFT            (16)  /* Gain Value of Area 10 */
#define R_GLCDC_GAMR_LUT6_GAIN10_MASK             0x7ff0000

/* GAMR_LUT7 Register bit definitions */
#define R_GLCDC_GAMR_LUT7_GAIN13_SHIFT            (0)  /* Gain Value of Area 13 */
#define R_GLCDC_GAMR_LUT7_GAIN13_MASK             0x7ff

#define R_GLCDC_GAMR_LUT7_GAIN012_SHIFT           (16)  /* Gain Value of Area 12 */
#define R_GLCDC_GAMR_LUT7_GAIN012_MASK            0x7ff0000

/* GAMR_LUT8 Register bit definitions */
#define R_GLCDC_GAMR_LUT8_GAIN15_SHIFT            (0)  /* Gain Value of Area 15 */
#define R_GLCDC_GAMR_LUT8_GAIN15_MASK             0x7ff

#define R_GLCDC_GAMR_LUT8_GAIN14_SHIFT            (16)  /* Gain Value of Area 14 */
#define R_GLCDC_GAMR_LUT8_GAIN14_MASK             0x7ff0000

/* GAMR_AREA1 Register bit definitions */
#define R_GLCDC_GAMR_AREA1_TH03_SHIFT             (0)  /* Start Threshold of Area 3 */
#define R_GLCDC_GAMR_AREA1_TH03_MASK              0x3ff

#define R_GLCDC_GAMR_AREA1_TH02_SHIFT             (10)  /* Start Threshold of Area 2 */
#define R_GLCDC_GAMR_AREA1_TH02_MASK              0xffc00

#define R_GLCDC_GAMR_AREA1_TH01_SHIFT             (20)  /* Start Threshold of Area 1 */
#define R_GLCDC_GAMR_AREA1_TH01_MASK              0x3ff00000

/* GAMR_AREA2 Register bit definitions */
#define R_GLCDC_GAMR_AREA2_TH06_SHIFT             (0)  /* Start Threshold of Area 6 */
#define R_GLCDC_GAMR_AREA2_TH06_MASK              0x3ff

#define R_GLCDC_GAMR_AREA2_TH05_SHIFT             (10)  /* Start Threshold of Area 5 */
#define R_GLCDC_GAMR_AREA2_TH05_MASK              0xffc00

#define R_GLCDC_GAMR_AREA2_TH04_SHIFT             (20)  /* Start Threshold of Area 4 */
#define R_GLCDC_GAMR_AREA2_TH04_MASK              0x3ff00000

/* GAMR_AREA3 Register bit definitions */
#define R_GLCDC_GAMR_AREA3_TH09_SHIFT             (0)  /* Start Threshold of Area 9 */
#define R_GLCDC_GAMR_AREA3_TH09_MASK              0x3ff

#define R_GLCDC_GAMR_AREA3_TH08_SHIFT             (10)  /* Start Threshold of Area 8 */
#define R_GLCDC_GAMR_AREA3_TH08_MASK              0xffc00

#define R_GLCDC_GAMR_AREA3_TH07_SHIFT             (20)  /* Start Threshold of Area 7 */
#define R_GLCDC_GAMR_AREA3_TH07_MASK              0x3ff00000

/* GAMR_AREA4 Register bit definitions */
#define R_GLCDC_GAMR_AREA4_TH12_SHIFT             (0)  /* Start Threshold of Area 12 */
#define R_GLCDC_GAMR_AREA4_TH12_MASK              0x3ff

#define R_GLCDC_GAMR_AREA4_TH11_SHIFT             (10)  /* Start Threshold of Area 11 */
#define R_GLCDC_GAMR_AREA4_TH11_MASK              0xffc00

#define R_GLCDC_GAMR_AREA4_TH10_SHIFT             (20)  /* Start Threshold of Area 10 */
#define R_GLCDC_GAMR_AREA4_TH10_MASK              0x3ff00000

/* GAMR_AREA5 Register bit definitions */
#define R_GLCDC_GAMR_AREA5_TH15_SHIFT             (0)  /* Start Threshold of Area 15 */
#define R_GLCDC_GAMR_AREA5_TH15_MASK              0x3ff

#define R_GLCDC_GAMR_AREA5_TH14_SHIFT             (10)  /* Start Threshold of Area 14 */
#define R_GLCDC_GAMR_AREA5_TH14_MASK              0xffc00

#define R_GLCDC_GAMR_AREA5_TH13_SHIFT             (20)  /* Start Threshold of Area 13 */
#define R_GLCDC_GAMR_AREA5_TH13_MASK              0x3ff00000

/* OUT_VLATCH Register bit definitions */
#define R_GLCDC_OUT_VLATCH_VEN                    (1 << 0)  /* Control of Output Control Module Register Value Reflection to Internal Operations */

/* OUT_SET Register bit definitions */
#define R_GLCDC_OUT_SET_PHASE_SHIFT               (0)  /* Data Output Delay Control in Serial RGB Format */
#define R_GLCDC_OUT_SET_PHASE_MASK                0x3
#  define R_GLCDC_OUT_SET_PHASE_00                        (0 << R_GLCDC_OUT_SET_PHASE_SHIFT)  /* 0 cycle */
#  define R_GLCDC_OUT_SET_PHASE_01                        (1 << R_GLCDC_OUT_SET_PHASE_SHIFT)  /* 1 cycle */
#  define R_GLCDC_OUT_SET_PHASE_10                        (2 << R_GLCDC_OUT_SET_PHASE_SHIFT)  /* 2 cycles */
#  define R_GLCDC_OUT_SET_PHASE_11                        (3 << R_GLCDC_OUT_SET_PHASE_SHIFT)  /* 3 cycles */

#define R_GLCDC_OUT_SET_DIRSEL                    (1 << 4)  /* Scan Direction Select of Serial RGB Format */

#define R_GLCDC_OUT_SET_FRQSEL_SHIFT              (8)  /* Clock Frequency Division Control */
#define R_GLCDC_OUT_SET_FRQSEL_MASK               0x300
#  define R_GLCDC_OUT_SET_FRQSEL_00                       (0 << R_GLCDC_OUT_SET_FRQSEL_SHIFT)  /* No frequency division, parallel RGB */
#  define R_GLCDC_OUT_SET_FRQSEL_01                       (1 << R_GLCDC_OUT_SET_FRQSEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_OUT_SET_FRQSEL_10                       (2 << R_GLCDC_OUT_SET_FRQSEL_SHIFT)  /* Quarter frequency (serial RGB) */
#  define R_GLCDC_OUT_SET_FRQSEL_11                       (3 << R_GLCDC_OUT_SET_FRQSEL_SHIFT)  /* Setting prohibited */

#define R_GLCDC_OUT_SET_FORMAT_SHIFT              (12)  /* Output Format Select */
#define R_GLCDC_OUT_SET_FORMAT_MASK               0x3000
#  define R_GLCDC_OUT_SET_FORMAT_00                       (0 << R_GLCDC_OUT_SET_FORMAT_SHIFT)  /* RGB888 — select RGB888 as dither output format */
#  define R_GLCDC_OUT_SET_FORMAT_01                       (1 << R_GLCDC_OUT_SET_FORMAT_SHIFT)  /* RGB666 — select RGB666 as dither output format */
#  define R_GLCDC_OUT_SET_FORMAT_10                       (2 << R_GLCDC_OUT_SET_FORMAT_SHIFT)  /* RGB565 — select RGB565 as dither output format */
#  define R_GLCDC_OUT_SET_FORMAT_11                       (3 << R_GLCDC_OUT_SET_FORMAT_SHIFT)  /* Serial RGB — select RGB888 as dither output format. Select dither output format in OUT_PDTHA.FORM[1:0]  */

#define R_GLCDC_OUT_SET_SWAPON                    (1 << 24)  /* Pixel Order Control */

#define R_GLCDC_OUT_SET_ENDIANON                  (1 << 28)  /* Bit Endian Control */

/* OUT_BRIGHT1 Register bit definitions */
#define R_GLCDC_OUT_BRIGHT1_BRTG_SHIFT            (0)  /* Brightness Adjustment of G Signal */
#define R_GLCDC_OUT_BRIGHT1_BRTG_MASK             0x3ff

/* OUT_BRIGHT2 Register bit definitions */
#define R_GLCDC_OUT_BRIGHT2_BRTR_SHIFT            (0)  /* Brightness Adjustment of R Signal */
#define R_GLCDC_OUT_BRIGHT2_BRTR_MASK             0x3ff

#define R_GLCDC_OUT_BRIGHT2_BRTB_SHIFT            (16)  /* Brightness Adjustment of B Signal */
#define R_GLCDC_OUT_BRIGHT2_BRTB_MASK             0x3ff0000

/* OUT_CONTRAST Register bit definitions */
#define R_GLCDC_OUT_CONTRAST_CONTR_SHIFT          (0)  /* Contrast Adjustment of R Signal */
#define R_GLCDC_OUT_CONTRAST_CONTR_MASK           0xff

#define R_GLCDC_OUT_CONTRAST_CONTB_SHIFT          (8)  /* Contrast Adjustment of B Signal */
#define R_GLCDC_OUT_CONTRAST_CONTB_MASK           0xff00

#define R_GLCDC_OUT_CONTRAST_CONTG_SHIFT          (16)  /* Contrast Adjustment of G Signal */
#define R_GLCDC_OUT_CONTRAST_CONTG_MASK           0xff0000

/* OUT_PDTHA Register bit definitions */
#define R_GLCDC_OUT_PDTHA_PD_SHIFT                (0)  /* Pattern Value (D) of 2×2 Pattern Dither */
#define R_GLCDC_OUT_PDTHA_PD_MASK                 0x3

#define R_GLCDC_OUT_PDTHA_PC_SHIFT                (4)  /* Pattern Value (C) of 2×2 Pattern Dither */
#define R_GLCDC_OUT_PDTHA_PC_MASK                 0x30

#define R_GLCDC_OUT_PDTHA_PB_SHIFT                (8)  /* Pattern Value (B) of 2×2 Pattern Dither */
#define R_GLCDC_OUT_PDTHA_PB_MASK                 0x300

#define R_GLCDC_OUT_PDTHA_PA_SHIFT                (12)  /* Pattern Value (A) of 2×2 Pattern Dither */
#define R_GLCDC_OUT_PDTHA_PA_MASK                 0x3000

#define R_GLCDC_OUT_PDTHA_FORM_SHIFT              (16)  /* Output Format Select */
#define R_GLCDC_OUT_PDTHA_FORM_MASK               0x30000
#  define R_GLCDC_OUT_PDTHA_FORM_00                       (0 << R_GLCDC_OUT_PDTHA_FORM_SHIFT)  /* RGB888; select RGB888 or serial RGB as output interface format */
#  define R_GLCDC_OUT_PDTHA_FORM_01                       (1 << R_GLCDC_OUT_PDTHA_FORM_SHIFT)  /* RGB666; select RGB666 as output interface format */
#  define R_GLCDC_OUT_PDTHA_FORM_10                       (2 << R_GLCDC_OUT_PDTHA_FORM_SHIFT)  /* RGB565; select RGB565 as output interface format */
#  define R_GLCDC_OUT_PDTHA_FORM_11                       (3 << R_GLCDC_OUT_PDTHA_FORM_SHIFT)  /* Setting prohibited Select output interface format in OUT_SET.FORMAT[1:0].  */

#define R_GLCDC_OUT_PDTHA_SEL_SHIFT               (20)  /* Operation Mode */
#define R_GLCDC_OUT_PDTHA_SEL_MASK                0x300000
#  define R_GLCDC_OUT_PDTHA_SEL_00                        (0 << R_GLCDC_OUT_PDTHA_SEL_SHIFT)  /* Truncate */
#  define R_GLCDC_OUT_PDTHA_SEL_01                        (1 << R_GLCDC_OUT_PDTHA_SEL_SHIFT)  /* Round-off */
#  define R_GLCDC_OUT_PDTHA_SEL_10                        (2 << R_GLCDC_OUT_PDTHA_SEL_SHIFT)  /* 2×2 pattern dither */
#  define R_GLCDC_OUT_PDTHA_SEL_11                        (3 << R_GLCDC_OUT_PDTHA_SEL_SHIFT)  /* Setting prohibited  */

/* OUT_CLKPHASE Register bit definitions */
#define R_GLCDC_OUT_CLKPHASE_TCON3EDGE            (1 << 3)  /* LCD_TCON3 Output Phase Control */

#define R_GLCDC_OUT_CLKPHASE_TCON2EDGE            (1 << 4)  /* LCD_TCON2 Output Phase Control */

#define R_GLCDC_OUT_CLKPHASE_TCON1EDGE            (1 << 5)  /* LCD_TCON1 Output Phase Control */

#define R_GLCDC_OUT_CLKPHASE_TCON0EDGE            (1 << 6)  /* LCD_TCON0 Output Phase Control */

#define R_GLCDC_OUT_CLKPHASE_LCDEDGE              (1 << 8)  /* LCD_DATA Output Phase Control */

#define R_GLCDC_OUT_CLKPHASE_FRONTGAM             (1 << 12)  /* Correction Control */

/* TCON_TIM Register bit definitions */
#define R_GLCDC_TCON_TIM_OFFSET_SHIFT             (0)  /* Horizontal Synchronization Signal Generation Reference Timing */
#define R_GLCDC_TCON_TIM_OFFSET_MASK              0x7ff

#define R_GLCDC_TCON_TIM_HALF_SHIFT               (16)  /* Vertical Synchronization Signal Generation Change Timing */
#define R_GLCDC_TCON_TIM_HALF_MASK                0x7ff0000

/* TCON_STVA1 Register bit definitions */
#define R_GLCDC_TCON_STVA1_VW_SHIFT               (0)  /* Vertical Synchronization Signal STVx1 Second Change Timing */
#define R_GLCDC_TCON_STVA1_VW_MASK                0x7ff

#define R_GLCDC_TCON_STVA1_VS_SHIFT               (16)  /* Vertical Synchronization Signal STVx1 First Change Timing */
#define R_GLCDC_TCON_STVA1_VS_MASK                0x7ff0000

/* TCON_STVA2 Register bit definitions */
#define R_GLCDC_TCON_STVA2_SEL_SHIFT              (0)  /* Output Signal Select Control for VSOUT/VEOUT Pin */
#define R_GLCDC_TCON_STVA2_SEL_MASK               0x7
#  define R_GLCDC_TCON_STVA2_SEL_000                      (0 << R_GLCDC_TCON_STVA2_SEL_SHIFT)  /* STVA */
#  define R_GLCDC_TCON_STVA2_SEL_001                      (1 << R_GLCDC_TCON_STVA2_SEL_SHIFT)  /* STVB */
#  define R_GLCDC_TCON_STVA2_SEL_010                      (2 << R_GLCDC_TCON_STVA2_SEL_SHIFT)  /* STHA */
#  define R_GLCDC_TCON_STVA2_SEL_011                      (3 << R_GLCDC_TCON_STVA2_SEL_SHIFT)  /* STHB */
#  define R_GLCDC_TCON_STVA2_SEL_100                      (4 << R_GLCDC_TCON_STVA2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STVA2_SEL_101                      (5 << R_GLCDC_TCON_STVA2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STVA2_SEL_110                      (6 << R_GLCDC_TCON_STVA2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STVA2_SEL_111                      (7 << R_GLCDC_TCON_STVA2_SEL_SHIFT)  /* DE */

#define R_GLCDC_TCON_STVA2_INV                    (1 << 4)  /* Vertical Synchronization Signal STVx Polarity Inversion Control */

/* TCON_STVB1 Register bit definitions */
#define R_GLCDC_TCON_STVB1_VW_SHIFT               (0)  /* Vertical Synchronization Signal STVx1 Second Change Timing */
#define R_GLCDC_TCON_STVB1_VW_MASK                0x7ff

#define R_GLCDC_TCON_STVB1_VS_SHIFT               (16)  /* Vertical Synchronization Signal STVx1 First Change Timing */
#define R_GLCDC_TCON_STVB1_VS_MASK                0x7ff0000

/* TCON_STVB2 Register bit definitions */
#define R_GLCDC_TCON_STVB2_SEL_SHIFT              (0)  /* Output Signal Select Control for VSOUT/VEOUT Pin */
#define R_GLCDC_TCON_STVB2_SEL_MASK               0x7
#  define R_GLCDC_TCON_STVB2_SEL_000                      (0 << R_GLCDC_TCON_STVB2_SEL_SHIFT)  /* STVA */
#  define R_GLCDC_TCON_STVB2_SEL_001                      (1 << R_GLCDC_TCON_STVB2_SEL_SHIFT)  /* STVB */
#  define R_GLCDC_TCON_STVB2_SEL_010                      (2 << R_GLCDC_TCON_STVB2_SEL_SHIFT)  /* STHA */
#  define R_GLCDC_TCON_STVB2_SEL_011                      (3 << R_GLCDC_TCON_STVB2_SEL_SHIFT)  /* STHB */
#  define R_GLCDC_TCON_STVB2_SEL_100                      (4 << R_GLCDC_TCON_STVB2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STVB2_SEL_101                      (5 << R_GLCDC_TCON_STVB2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STVB2_SEL_110                      (6 << R_GLCDC_TCON_STVB2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STVB2_SEL_111                      (7 << R_GLCDC_TCON_STVB2_SEL_SHIFT)  /* DE */

#define R_GLCDC_TCON_STVB2_INV                    (1 << 4)  /* Vertical Synchronization Signal STVx Polarity Inversion Control */

/* TCON_STHA1 Register bit definitions */
#define R_GLCDC_TCON_STHA1_HW_SHIFT               (0)  /* Horizontal Synchronization Signal STHx1 Second Change Timing */
#define R_GLCDC_TCON_STHA1_HW_MASK                0x7ff

#define R_GLCDC_TCON_STHA1_HS_SHIFT               (16)  /* Horizontal Synchronization Signal STHx1 First Change Timing */
#define R_GLCDC_TCON_STHA1_HS_MASK                0x7ff0000

/* TCON_STHA2 Register bit definitions */
#define R_GLCDC_TCON_STHA2_SEL_SHIFT              (0)  /* Output Signal Select Control for LCD_TCON2/LCD_TCON3 Pin */
#define R_GLCDC_TCON_STHA2_SEL_MASK               0x7
#  define R_GLCDC_TCON_STHA2_SEL_000                      (0 << R_GLCDC_TCON_STHA2_SEL_SHIFT)  /* STVA */
#  define R_GLCDC_TCON_STHA2_SEL_001                      (1 << R_GLCDC_TCON_STHA2_SEL_SHIFT)  /* STVB */
#  define R_GLCDC_TCON_STHA2_SEL_010                      (2 << R_GLCDC_TCON_STHA2_SEL_SHIFT)  /* STHA */
#  define R_GLCDC_TCON_STHA2_SEL_011                      (3 << R_GLCDC_TCON_STHA2_SEL_SHIFT)  /* STHB */
#  define R_GLCDC_TCON_STHA2_SEL_100                      (4 << R_GLCDC_TCON_STHA2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STHA2_SEL_101                      (5 << R_GLCDC_TCON_STHA2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STHA2_SEL_110                      (6 << R_GLCDC_TCON_STHA2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STHA2_SEL_111                      (7 << R_GLCDC_TCON_STHA2_SEL_SHIFT)  /* DE */

#define R_GLCDC_TCON_STHA2_INV                    (1 << 4)  /* Horizontal Synchronization Signal STHx Polarity Inversion Control */

#define R_GLCDC_TCON_STHA2_HSSEL                  (1 << 8)  /* Horizontal Synchronization Signal STHx Reference Timing Control */

/* TCON_STHB1 Register bit definitions */
#define R_GLCDC_TCON_STHB1_HW_SHIFT               (0)  /* Horizontal Synchronization Signal STHx1 Second Change Timing */
#define R_GLCDC_TCON_STHB1_HW_MASK                0x7ff

#define R_GLCDC_TCON_STHB1_HS_SHIFT               (16)  /* Horizontal Synchronization Signal STHx1 First Change Timing */
#define R_GLCDC_TCON_STHB1_HS_MASK                0x7ff0000

/* TCON_STHB2 Register bit definitions */
#define R_GLCDC_TCON_STHB2_SEL_SHIFT              (0)  /* Output Signal Select Control for LCD_TCON2/LCD_TCON3 Pin */
#define R_GLCDC_TCON_STHB2_SEL_MASK               0x7
#  define R_GLCDC_TCON_STHB2_SEL_000                      (0 << R_GLCDC_TCON_STHB2_SEL_SHIFT)  /* STVA */
#  define R_GLCDC_TCON_STHB2_SEL_001                      (1 << R_GLCDC_TCON_STHB2_SEL_SHIFT)  /* STVB */
#  define R_GLCDC_TCON_STHB2_SEL_010                      (2 << R_GLCDC_TCON_STHB2_SEL_SHIFT)  /* STHA */
#  define R_GLCDC_TCON_STHB2_SEL_011                      (3 << R_GLCDC_TCON_STHB2_SEL_SHIFT)  /* STHB */
#  define R_GLCDC_TCON_STHB2_SEL_100                      (4 << R_GLCDC_TCON_STHB2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STHB2_SEL_101                      (5 << R_GLCDC_TCON_STHB2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STHB2_SEL_110                      (6 << R_GLCDC_TCON_STHB2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STHB2_SEL_111                      (7 << R_GLCDC_TCON_STHB2_SEL_SHIFT)  /* DE */

#define R_GLCDC_TCON_STHB2_INV                    (1 << 4)  /* Horizontal Synchronization Signal STHx Polarity Inversion Control */

#define R_GLCDC_TCON_STHB2_HSSEL                  (1 << 8)  /* Horizontal Synchronization Signal STHx Reference Timing Control */

/* TCON_DE Register bit definitions */
#define R_GLCDC_TCON_DE_INV                       (1 << 0)  /* Data Enable Signal DE Polarity Inversion Control */

/* SYSCNT_DTCTEN Register bit definitions */
#define R_GLCDC_SYSCNT_DTCTEN_VPOSDTC             (1 << 0)  /* Specified Line Detection Control */

#define R_GLCDC_SYSCNT_DTCTEN_L1UNDFDTC           (1 << 1)  /* Graphics 1 Underflow Detection Control */

#define R_GLCDC_SYSCNT_DTCTEN_L2UNDFDTC           (1 << 2)  /* Graphics 2 Underflow Detection Control */

/* SYSCNT_INTEN Register bit definitions */
#define R_GLCDC_SYSCNT_INTEN_VPOSINTEN            (1 << 0)  /* Interrupt Request Signal GLCDC_VPOS Enable Control */

#define R_GLCDC_SYSCNT_INTEN_L1UNDFINTEN          (1 << 1)  /* Interrupt Request Signal GLCDC_L1UNDF Enable Control */

#define R_GLCDC_SYSCNT_INTEN_L2UNDFINTEN          (1 << 2)  /* Interrupt Request Signal GLCDC_L2UNDF Enable Control */

/* SYSCNT_STCLR Register bit definitions */
#define R_GLCDC_SYSCNT_STCLR_VPOSCLR              (1 << 0)  /* Graphics 2 Specified Line Detection Flag Clear */

#define R_GLCDC_SYSCNT_STCLR_L1UNDFCLR            (1 << 1)  /* Graphics 1 Underflow Detection Flag Clear */

#define R_GLCDC_SYSCNT_STCLR_L2UNDFCLR            (1 << 2)  /* Graphics 2 Underflow Detection Flag Clear */

/* SYSCNT_STMON Register bit definitions */
#define R_GLCDC_SYSCNT_STMON_VPOS                 (1 << 0)  /* Graphics 2 Specified Line Detection Flag */

#define R_GLCDC_SYSCNT_STMON_L1UNDF               (1 << 1)  /* Graphics 1 Underflow Detection Flag */

#define R_GLCDC_SYSCNT_STMON_L2UNDF               (1 << 2)  /* Graphics 2 Underflow Detection Flag */

/* SYSCNT_PANEL_CLK Register bit definitions */
#define R_GLCDC_SYSCNT_PANEL_CLK_DCDR_SHIFT       (0)  /* Clock Division Ratio Setting Control */
#define R_GLCDC_SYSCNT_PANEL_CLK_DCDR_MASK        0x3f

#define R_GLCDC_SYSCNT_PANEL_CLK_CLKEN            (1 << 6)  /* Panel Clock Output Enable Control */

#define R_GLCDC_SYSCNT_PANEL_CLK_CLKSEL           (1 << 8)  /* Panel Clock Supply Source Control */

#define R_GLCDC_SYSCNT_PANEL_CLK_PIXSEL           (1 << 12)  /* Pixel Clock Select Control */

#define R_GLCDC_SYSCNT_PANEL_CLK_VER_SHIFT        (16)  /* Version Information */
#define R_GLCDC_SYSCNT_PANEL_CLK_VER_MASK         0xffff0000


/* Maximum number of channels */

#define GLCDC_MAX_CHANNELS    256

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GLCDC_H */

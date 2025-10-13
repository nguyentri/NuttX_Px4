/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_mfwd.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MFWD_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MFWD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* MFWD Base Address */
#ifndef R_MFWD_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_MFWD_BASE           0x403c0000
#else
#define R_MFWD_BASE           0x503c0000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_MFWD_CH_STRIDE    0x00000004
#define R_MFWD_CH_BASE(ch)   (R_MFWD_BASE + ((uint32_t)(ch) * R_MFWD_CH_STRIDE))

/* MFWD Register Offsets */

#define R_MFWD_FWGC_OFFSET     0x00000000  /* General Configuration Register */
#define R_MFWD_FWTTC0_OFFSET     0x00000010  /* TAG TPID Configuration Register 0 */
#define R_MFWD_FWTTC1_OFFSET     0x00000014  /* TAG TPID Configuration Register 1 */
#define R_MFWD_FWCEPTC_OFFSET     0x00000020  /* CPU Exceptional Path Target Configuration Register */
#define R_MFWD_FWCEPRC0_OFFSET     0x00000024  /* CPU Exceptional Path Reason Configuration Register 0 */
#define R_MFWD_FWCEPRC1_OFFSET     0x00000028  /* CPU Exceptional Path Reason Configuration Register 1 */
#define R_MFWD_FWCEPRC2_OFFSET     0x0000002c  /* CPU Exceptional Path Reason Configuration Register 2 */
#define R_MFWD_FWCLPTC_OFFSET     0x00000030  /* CPU Learning Path Target Configuration Register */
#define R_MFWD_FWCLPRC_OFFSET     0x00000034  /* CPU Learning Path Reason Configuration Register */
#define R_MFWD_FWCMPTC_OFFSET     0x00000040  /* CPU Mirroring Path Target Configuration Register */
#define R_MFWD_FWEMPTC_OFFSET     0x00000044  /* Ethernet Mirroring Path Target Configuration Register */
#define R_MFWD_FWSDMPTC_OFFSET     0x00000050  /* Source-Destination Mirroring Path Target Configuration Register */
#define R_MFWD_FWSDMPVC_OFFSET     0x00000054  /* Source-Destination Mirroring Path Vector Configuration Register */
/* FWLBWMC%s Registers (0-2) */
#define R_MFWD_FWLBWMC0_OFFSET     0x00000080  /* Port 0 Level Based Watermark Configuration Register */
#define R_MFWD_FWLBWMC1_OFFSET     0x00000084  /* Port 1 Level Based Watermark Configuration Register */
#define R_MFWD_FWLBWMC2_OFFSET     0x00000088  /* Port 2 Level Based Watermark Configuration Register */
/* FWPC%s0 Registers (0-2) */
#define R_MFWD_FWPC00_OFFSET     0x00000100  /* Port 0 Configuration Register 0 */
#define R_MFWD_FWPC10_OFFSET     0x00000110  /* Port 1 Configuration Register 0 */
#define R_MFWD_FWPC20_OFFSET     0x00000120  /* Port 2 Configuration Register 0 */
/* FWPC%s1 Registers (0-2) */
#define R_MFWD_FWPC01_OFFSET     0x00000104  /* Port 0 Configuration Register 1 */
#define R_MFWD_FWPC11_OFFSET     0x00000114  /* Port 1 Configuration Register 1 */
#define R_MFWD_FWPC21_OFFSET     0x00000124  /* Port 2 Configuration Register 1 */
/* FWPC%s2 Registers (0-2) */
#define R_MFWD_FWPC02_OFFSET     0x00000108  /* Port 0 Configuration Register 2 */
#define R_MFWD_FWPC12_OFFSET     0x00000118  /* Port 1 Configuration Register 2 */
#define R_MFWD_FWPC22_OFFSET     0x00000128  /* Port 2 Configuration Register 2 */
/* FWCTGC%s0 Registers (0-7) */
#define R_MFWD_FWCTGC00_OFFSET     0x00000400  /* Cut-Through General Configuration Register i0 */
#define R_MFWD_FWCTGC10_OFFSET     0x00000440  /* Cut-Through General Configuration Register i0 */
#define R_MFWD_FWCTGC20_OFFSET     0x00000480  /* Cut-Through General Configuration Register i0 */
#define R_MFWD_FWCTGC30_OFFSET     0x000004c0  /* Cut-Through General Configuration Register i0 */
#define R_MFWD_FWCTGC40_OFFSET     0x00000500  /* Cut-Through General Configuration Register i0 */
#define R_MFWD_FWCTGC50_OFFSET     0x00000540  /* Cut-Through General Configuration Register i0 */
#define R_MFWD_FWCTGC60_OFFSET     0x00000580  /* Cut-Through General Configuration Register i0 */
#define R_MFWD_FWCTGC70_OFFSET     0x000005c0  /* Cut-Through General Configuration Register i0 */
/* FWCTGC%s1 Registers (0-7) */
#define R_MFWD_FWCTGC01_OFFSET     0x00000404  /* Cut-Through General Configuration Register i1 */
#define R_MFWD_FWCTGC11_OFFSET     0x00000444  /* Cut-Through General Configuration Register i1 */
#define R_MFWD_FWCTGC21_OFFSET     0x00000484  /* Cut-Through General Configuration Register i1 */
#define R_MFWD_FWCTGC31_OFFSET     0x000004c4  /* Cut-Through General Configuration Register i1 */
#define R_MFWD_FWCTGC41_OFFSET     0x00000504  /* Cut-Through General Configuration Register i1 */
#define R_MFWD_FWCTGC51_OFFSET     0x00000544  /* Cut-Through General Configuration Register i1 */
#define R_MFWD_FWCTGC61_OFFSET     0x00000584  /* Cut-Through General Configuration Register i1 */
#define R_MFWD_FWCTGC71_OFFSET     0x000005c4  /* Cut-Through General Configuration Register i1 */
/* FWCTTC%s0 Registers (0-7) */
#define R_MFWD_FWCTTC00_OFFSET     0x00000408  /* Cut-Through Target Configuration Register i0 */
#define R_MFWD_FWCTTC10_OFFSET     0x00000448  /* Cut-Through Target Configuration Register i0 */
#define R_MFWD_FWCTTC20_OFFSET     0x00000488  /* Cut-Through Target Configuration Register i0 */
#define R_MFWD_FWCTTC30_OFFSET     0x000004c8  /* Cut-Through Target Configuration Register i0 */
#define R_MFWD_FWCTTC40_OFFSET     0x00000508  /* Cut-Through Target Configuration Register i0 */
#define R_MFWD_FWCTTC50_OFFSET     0x00000548  /* Cut-Through Target Configuration Register i0 */
#define R_MFWD_FWCTTC60_OFFSET     0x00000588  /* Cut-Through Target Configuration Register i0 */
#define R_MFWD_FWCTTC70_OFFSET     0x000005c8  /* Cut-Through Target Configuration Register i0 */
/* FWCTTC%s1 Registers (0-7) */
#define R_MFWD_FWCTTC01_OFFSET     0x0000040c  /* Cut-Through Target Configuration Register i1 */
#define R_MFWD_FWCTTC11_OFFSET     0x0000044c  /* Cut-Through Target Configuration Register i1 */
#define R_MFWD_FWCTTC21_OFFSET     0x0000048c  /* Cut-Through Target Configuration Register i1 */
#define R_MFWD_FWCTTC31_OFFSET     0x000004cc  /* Cut-Through Target Configuration Register i1 */
#define R_MFWD_FWCTTC41_OFFSET     0x0000050c  /* Cut-Through Target Configuration Register i1 */
#define R_MFWD_FWCTTC51_OFFSET     0x0000054c  /* Cut-Through Target Configuration Register i1 */
#define R_MFWD_FWCTTC61_OFFSET     0x0000058c  /* Cut-Through Target Configuration Register i1 */
#define R_MFWD_FWCTTC71_OFFSET     0x000005cc  /* Cut-Through Target Configuration Register i1 */
/* FWCTTC%s20 Registers (0-7) */
#define R_MFWD_FWCTTC020_OFFSET     0x00000410  /* Cut-Through Target Configuration Register i20 */
#define R_MFWD_FWCTTC120_OFFSET     0x00000450  /* Cut-Through Target Configuration Register i20 */
#define R_MFWD_FWCTTC220_OFFSET     0x00000490  /* Cut-Through Target Configuration Register i20 */
#define R_MFWD_FWCTTC320_OFFSET     0x000004d0  /* Cut-Through Target Configuration Register i20 */
#define R_MFWD_FWCTTC420_OFFSET     0x00000510  /* Cut-Through Target Configuration Register i20 */
#define R_MFWD_FWCTTC520_OFFSET     0x00000550  /* Cut-Through Target Configuration Register i20 */
#define R_MFWD_FWCTTC620_OFFSET     0x00000590  /* Cut-Through Target Configuration Register i20 */
#define R_MFWD_FWCTTC720_OFFSET     0x000005d0  /* Cut-Through Target Configuration Register i20 */
/* FWCTSC%s0 Registers (0-7) */
#define R_MFWD_FWCTSC00_OFFSET     0x00000420  /* Cut-Through Separation Configuration Register i0 */
#define R_MFWD_FWCTSC10_OFFSET     0x00000460  /* Cut-Through Separation Configuration Register i0 */
#define R_MFWD_FWCTSC20_OFFSET     0x000004a0  /* Cut-Through Separation Configuration Register i0 */
#define R_MFWD_FWCTSC30_OFFSET     0x000004e0  /* Cut-Through Separation Configuration Register i0 */
#define R_MFWD_FWCTSC40_OFFSET     0x00000520  /* Cut-Through Separation Configuration Register i0 */
#define R_MFWD_FWCTSC50_OFFSET     0x00000560  /* Cut-Through Separation Configuration Register i0 */
#define R_MFWD_FWCTSC60_OFFSET     0x000005a0  /* Cut-Through Separation Configuration Register i0 */
#define R_MFWD_FWCTSC70_OFFSET     0x000005e0  /* Cut-Through Separation Configuration Register i0 */
/* FWCTSC%s1 Registers (0-7) */
#define R_MFWD_FWCTSC01_OFFSET     0x00000424  /* Cut-Through Separation Configuration Register i1 */
#define R_MFWD_FWCTSC11_OFFSET     0x00000464  /* Cut-Through Separation Configuration Register i1 */
#define R_MFWD_FWCTSC21_OFFSET     0x000004a4  /* Cut-Through Separation Configuration Register i1 */
#define R_MFWD_FWCTSC31_OFFSET     0x000004e4  /* Cut-Through Separation Configuration Register i1 */
#define R_MFWD_FWCTSC41_OFFSET     0x00000524  /* Cut-Through Separation Configuration Register i1 */
#define R_MFWD_FWCTSC51_OFFSET     0x00000564  /* Cut-Through Separation Configuration Register i1 */
#define R_MFWD_FWCTSC61_OFFSET     0x000005a4  /* Cut-Through Separation Configuration Register i1 */
#define R_MFWD_FWCTSC71_OFFSET     0x000005e4  /* Cut-Through Separation Configuration Register i1 */
/* FWCTSC%s2 Registers (0-7) */
#define R_MFWD_FWCTSC02_OFFSET     0x00000428  /* Cut-Through Separation Configuration Register i2 */
#define R_MFWD_FWCTSC12_OFFSET     0x00000468  /* Cut-Through Separation Configuration Register i2 */
#define R_MFWD_FWCTSC22_OFFSET     0x000004a8  /* Cut-Through Separation Configuration Register i2 */
#define R_MFWD_FWCTSC32_OFFSET     0x000004e8  /* Cut-Through Separation Configuration Register i2 */
#define R_MFWD_FWCTSC42_OFFSET     0x00000528  /* Cut-Through Separation Configuration Register i2 */
#define R_MFWD_FWCTSC52_OFFSET     0x00000568  /* Cut-Through Separation Configuration Register i2 */
#define R_MFWD_FWCTSC62_OFFSET     0x000005a8  /* Cut-Through Separation Configuration Register i2 */
#define R_MFWD_FWCTSC72_OFFSET     0x000005e8  /* Cut-Through Separation Configuration Register i2 */
/* FWCTSC%s3 Registers (0-7) */
#define R_MFWD_FWCTSC03_OFFSET     0x0000042c  /* Cut-Through Separation Configuration Register i3 */
#define R_MFWD_FWCTSC13_OFFSET     0x0000046c  /* Cut-Through Separation Configuration Register i3 */
#define R_MFWD_FWCTSC23_OFFSET     0x000004ac  /* Cut-Through Separation Configuration Register i3 */
#define R_MFWD_FWCTSC33_OFFSET     0x000004ec  /* Cut-Through Separation Configuration Register i3 */
#define R_MFWD_FWCTSC43_OFFSET     0x0000052c  /* Cut-Through Separation Configuration Register i3 */
#define R_MFWD_FWCTSC53_OFFSET     0x0000056c  /* Cut-Through Separation Configuration Register i3 */
#define R_MFWD_FWCTSC63_OFFSET     0x000005ac  /* Cut-Through Separation Configuration Register i3 */
#define R_MFWD_FWCTSC73_OFFSET     0x000005ec  /* Cut-Through Separation Configuration Register i3 */
/* FWCTSC%s4 Registers (0-7) */
#define R_MFWD_FWCTSC04_OFFSET     0x00000430  /* Cut-Through Separation Configuration Register i4 */
#define R_MFWD_FWCTSC14_OFFSET     0x00000470  /* Cut-Through Separation Configuration Register i4 */
#define R_MFWD_FWCTSC24_OFFSET     0x000004b0  /* Cut-Through Separation Configuration Register i4 */
#define R_MFWD_FWCTSC34_OFFSET     0x000004f0  /* Cut-Through Separation Configuration Register i4 */
#define R_MFWD_FWCTSC44_OFFSET     0x00000530  /* Cut-Through Separation Configuration Register i4 */
#define R_MFWD_FWCTSC54_OFFSET     0x00000570  /* Cut-Through Separation Configuration Register i4 */
#define R_MFWD_FWCTSC64_OFFSET     0x000005b0  /* Cut-Through Separation Configuration Register i4 */
#define R_MFWD_FWCTSC74_OFFSET     0x000005f0  /* Cut-Through Separation Configuration Register i4 */
/* FWTWBFC%s Registers (0-15) */
#define R_MFWD_FWTWBFC00_OFFSET     0x00001000  /* Two-Byte Filter Configuration Register 00 */
#define R_MFWD_FWTWBFC01_OFFSET     0x00001010  /* Two-Byte Filter Configuration Register 01 */
#define R_MFWD_FWTWBFC02_OFFSET     0x00001020  /* Two-Byte Filter Configuration Register 02 */
#define R_MFWD_FWTWBFC03_OFFSET     0x00001030  /* Two-Byte Filter Configuration Register 03 */
#define R_MFWD_FWTWBFC04_OFFSET     0x00001040  /* Two-Byte Filter Configuration Register 04 */
#define R_MFWD_FWTWBFC05_OFFSET     0x00001050  /* Two-Byte Filter Configuration Register 05 */
#define R_MFWD_FWTWBFC06_OFFSET     0x00001060  /* Two-Byte Filter Configuration Register 06 */
#define R_MFWD_FWTWBFC07_OFFSET     0x00001070  /* Two-Byte Filter Configuration Register 07 */
#define R_MFWD_FWTWBFC08_OFFSET     0x00001080  /* Two-Byte Filter Configuration Register 08 */
#define R_MFWD_FWTWBFC09_OFFSET     0x00001090  /* Two-Byte Filter Configuration Register 09 */
#define R_MFWD_FWTWBFC10_OFFSET     0x000010a0  /* Two-Byte Filter Configuration Register 10 */
#define R_MFWD_FWTWBFC11_OFFSET     0x000010b0  /* Two-Byte Filter Configuration Register 11 */
#define R_MFWD_FWTWBFC12_OFFSET     0x000010c0  /* Two-Byte Filter Configuration Register 12 */
#define R_MFWD_FWTWBFC13_OFFSET     0x000010d0  /* Two-Byte Filter Configuration Register 13 */
#define R_MFWD_FWTWBFC14_OFFSET     0x000010e0  /* Two-Byte Filter Configuration Register 14 */
#define R_MFWD_FWTWBFC15_OFFSET     0x000010f0  /* Two-Byte Filter Configuration Register 15 */
/* FWTWBFVC%s Registers (0-15) */
#define R_MFWD_FWTWBFVC00_OFFSET     0x00001004  /* Two-Byte Filter Value Configuration Register 00 */
#define R_MFWD_FWTWBFVC01_OFFSET     0x00001014  /* Two-Byte Filter Value Configuration Register 01 */
#define R_MFWD_FWTWBFVC02_OFFSET     0x00001024  /* Two-Byte Filter Value Configuration Register 02 */
#define R_MFWD_FWTWBFVC03_OFFSET     0x00001034  /* Two-Byte Filter Value Configuration Register 03 */
#define R_MFWD_FWTWBFVC04_OFFSET     0x00001044  /* Two-Byte Filter Value Configuration Register 04 */
#define R_MFWD_FWTWBFVC05_OFFSET     0x00001054  /* Two-Byte Filter Value Configuration Register 05 */
#define R_MFWD_FWTWBFVC06_OFFSET     0x00001064  /* Two-Byte Filter Value Configuration Register 06 */
#define R_MFWD_FWTWBFVC07_OFFSET     0x00001074  /* Two-Byte Filter Value Configuration Register 07 */
#define R_MFWD_FWTWBFVC08_OFFSET     0x00001084  /* Two-Byte Filter Value Configuration Register 08 */
#define R_MFWD_FWTWBFVC09_OFFSET     0x00001094  /* Two-Byte Filter Value Configuration Register 09 */
#define R_MFWD_FWTWBFVC10_OFFSET     0x000010a4  /* Two-Byte Filter Value Configuration Register 10 */
#define R_MFWD_FWTWBFVC11_OFFSET     0x000010b4  /* Two-Byte Filter Value Configuration Register 11 */
#define R_MFWD_FWTWBFVC12_OFFSET     0x000010c4  /* Two-Byte Filter Value Configuration Register 12 */
#define R_MFWD_FWTWBFVC13_OFFSET     0x000010d4  /* Two-Byte Filter Value Configuration Register 13 */
#define R_MFWD_FWTWBFVC14_OFFSET     0x000010e4  /* Two-Byte Filter Value Configuration Register 14 */
#define R_MFWD_FWTWBFVC15_OFFSET     0x000010f4  /* Two-Byte Filter Value Configuration Register 15 */
/* FWTHBFC%s Registers (0-15) */
#define R_MFWD_FWTHBFC00_OFFSET     0x00001400  /* Three-Byte Filter Configuration Register 00 */
#define R_MFWD_FWTHBFC01_OFFSET     0x00001410  /* Three-Byte Filter Configuration Register 01 */
#define R_MFWD_FWTHBFC02_OFFSET     0x00001420  /* Three-Byte Filter Configuration Register 02 */
#define R_MFWD_FWTHBFC03_OFFSET     0x00001430  /* Three-Byte Filter Configuration Register 03 */
#define R_MFWD_FWTHBFC04_OFFSET     0x00001440  /* Three-Byte Filter Configuration Register 04 */
#define R_MFWD_FWTHBFC05_OFFSET     0x00001450  /* Three-Byte Filter Configuration Register 05 */
#define R_MFWD_FWTHBFC06_OFFSET     0x00001460  /* Three-Byte Filter Configuration Register 06 */
#define R_MFWD_FWTHBFC07_OFFSET     0x00001470  /* Three-Byte Filter Configuration Register 07 */
#define R_MFWD_FWTHBFC08_OFFSET     0x00001480  /* Three-Byte Filter Configuration Register 08 */
#define R_MFWD_FWTHBFC09_OFFSET     0x00001490  /* Three-Byte Filter Configuration Register 09 */
#define R_MFWD_FWTHBFC10_OFFSET     0x000014a0  /* Three-Byte Filter Configuration Register 10 */
#define R_MFWD_FWTHBFC11_OFFSET     0x000014b0  /* Three-Byte Filter Configuration Register 11 */
#define R_MFWD_FWTHBFC12_OFFSET     0x000014c0  /* Three-Byte Filter Configuration Register 12 */
#define R_MFWD_FWTHBFC13_OFFSET     0x000014d0  /* Three-Byte Filter Configuration Register 13 */
#define R_MFWD_FWTHBFC14_OFFSET     0x000014e0  /* Three-Byte Filter Configuration Register 14 */
#define R_MFWD_FWTHBFC15_OFFSET     0x000014f0  /* Three-Byte Filter Configuration Register 15 */
/* FWTHBFV0C%s Registers (0-15) */
#define R_MFWD_FWTHBFV0C00_OFFSET     0x00001404  /* Three-Byte Filter Value 0 Configuration Register 00 */
#define R_MFWD_FWTHBFV0C01_OFFSET     0x00001414  /* Three-Byte Filter Value 0 Configuration Register 01 */
#define R_MFWD_FWTHBFV0C02_OFFSET     0x00001424  /* Three-Byte Filter Value 0 Configuration Register 02 */
#define R_MFWD_FWTHBFV0C03_OFFSET     0x00001434  /* Three-Byte Filter Value 0 Configuration Register 03 */
#define R_MFWD_FWTHBFV0C04_OFFSET     0x00001444  /* Three-Byte Filter Value 0 Configuration Register 04 */
#define R_MFWD_FWTHBFV0C05_OFFSET     0x00001454  /* Three-Byte Filter Value 0 Configuration Register 05 */
#define R_MFWD_FWTHBFV0C06_OFFSET     0x00001464  /* Three-Byte Filter Value 0 Configuration Register 06 */
#define R_MFWD_FWTHBFV0C07_OFFSET     0x00001474  /* Three-Byte Filter Value 0 Configuration Register 07 */
#define R_MFWD_FWTHBFV0C08_OFFSET     0x00001484  /* Three-Byte Filter Value 0 Configuration Register 08 */
#define R_MFWD_FWTHBFV0C09_OFFSET     0x00001494  /* Three-Byte Filter Value 0 Configuration Register 09 */
#define R_MFWD_FWTHBFV0C10_OFFSET     0x000014a4  /* Three-Byte Filter Value 0 Configuration Register 10 */
#define R_MFWD_FWTHBFV0C11_OFFSET     0x000014b4  /* Three-Byte Filter Value 0 Configuration Register 11 */
#define R_MFWD_FWTHBFV0C12_OFFSET     0x000014c4  /* Three-Byte Filter Value 0 Configuration Register 12 */
#define R_MFWD_FWTHBFV0C13_OFFSET     0x000014d4  /* Three-Byte Filter Value 0 Configuration Register 13 */
#define R_MFWD_FWTHBFV0C14_OFFSET     0x000014e4  /* Three-Byte Filter Value 0 Configuration Register 14 */
#define R_MFWD_FWTHBFV0C15_OFFSET     0x000014f4  /* Three-Byte Filter Value 0 Configuration Register 15 */
/* FWTHBFV1C%s Registers (0-15) */
#define R_MFWD_FWTHBFV1C00_OFFSET     0x00001408  /* Three-Byte Filter Value 1 Configuration Register 00 */
#define R_MFWD_FWTHBFV1C01_OFFSET     0x00001418  /* Three-Byte Filter Value 1 Configuration Register 01 */
#define R_MFWD_FWTHBFV1C02_OFFSET     0x00001428  /* Three-Byte Filter Value 1 Configuration Register 02 */
#define R_MFWD_FWTHBFV1C03_OFFSET     0x00001438  /* Three-Byte Filter Value 1 Configuration Register 03 */
#define R_MFWD_FWTHBFV1C04_OFFSET     0x00001448  /* Three-Byte Filter Value 1 Configuration Register 04 */
#define R_MFWD_FWTHBFV1C05_OFFSET     0x00001458  /* Three-Byte Filter Value 1 Configuration Register 05 */
#define R_MFWD_FWTHBFV1C06_OFFSET     0x00001468  /* Three-Byte Filter Value 1 Configuration Register 06 */
#define R_MFWD_FWTHBFV1C07_OFFSET     0x00001478  /* Three-Byte Filter Value 1 Configuration Register 07 */
#define R_MFWD_FWTHBFV1C08_OFFSET     0x00001488  /* Three-Byte Filter Value 1 Configuration Register 08 */
#define R_MFWD_FWTHBFV1C09_OFFSET     0x00001498  /* Three-Byte Filter Value 1 Configuration Register 09 */
#define R_MFWD_FWTHBFV1C10_OFFSET     0x000014a8  /* Three-Byte Filter Value 1 Configuration Register 10 */
#define R_MFWD_FWTHBFV1C11_OFFSET     0x000014b8  /* Three-Byte Filter Value 1 Configuration Register 11 */
#define R_MFWD_FWTHBFV1C12_OFFSET     0x000014c8  /* Three-Byte Filter Value 1 Configuration Register 12 */
#define R_MFWD_FWTHBFV1C13_OFFSET     0x000014d8  /* Three-Byte Filter Value 1 Configuration Register 13 */
#define R_MFWD_FWTHBFV1C14_OFFSET     0x000014e8  /* Three-Byte Filter Value 1 Configuration Register 14 */
#define R_MFWD_FWTHBFV1C15_OFFSET     0x000014f8  /* Three-Byte Filter Value 1 Configuration Register 15 */
/* FWFOBFC%s Registers (0-15) */
#define R_MFWD_FWFOBFC00_OFFSET     0x00001800  /* Four-Byte Filter Configuration Register 00 */
#define R_MFWD_FWFOBFC01_OFFSET     0x00001810  /* Four-Byte Filter Configuration Register 01 */
#define R_MFWD_FWFOBFC02_OFFSET     0x00001820  /* Four-Byte Filter Configuration Register 02 */
#define R_MFWD_FWFOBFC03_OFFSET     0x00001830  /* Four-Byte Filter Configuration Register 03 */
#define R_MFWD_FWFOBFC04_OFFSET     0x00001840  /* Four-Byte Filter Configuration Register 04 */
#define R_MFWD_FWFOBFC05_OFFSET     0x00001850  /* Four-Byte Filter Configuration Register 05 */
#define R_MFWD_FWFOBFC06_OFFSET     0x00001860  /* Four-Byte Filter Configuration Register 06 */
#define R_MFWD_FWFOBFC07_OFFSET     0x00001870  /* Four-Byte Filter Configuration Register 07 */
#define R_MFWD_FWFOBFC08_OFFSET     0x00001880  /* Four-Byte Filter Configuration Register 08 */
#define R_MFWD_FWFOBFC09_OFFSET     0x00001890  /* Four-Byte Filter Configuration Register 09 */
#define R_MFWD_FWFOBFC10_OFFSET     0x000018a0  /* Four-Byte Filter Configuration Register 10 */
#define R_MFWD_FWFOBFC11_OFFSET     0x000018b0  /* Four-Byte Filter Configuration Register 11 */
#define R_MFWD_FWFOBFC12_OFFSET     0x000018c0  /* Four-Byte Filter Configuration Register 12 */
#define R_MFWD_FWFOBFC13_OFFSET     0x000018d0  /* Four-Byte Filter Configuration Register 13 */
#define R_MFWD_FWFOBFC14_OFFSET     0x000018e0  /* Four-Byte Filter Configuration Register 14 */
#define R_MFWD_FWFOBFC15_OFFSET     0x000018f0  /* Four-Byte Filter Configuration Register 15 */
/* FWFOBFV0C%s Registers (0-15) */
#define R_MFWD_FWFOBFV0C00_OFFSET     0x00001804  /* Four-Byte Filter Value 0 Configuration Register 00 */
#define R_MFWD_FWFOBFV0C01_OFFSET     0x00001814  /* Four-Byte Filter Value 0 Configuration Register 01 */
#define R_MFWD_FWFOBFV0C02_OFFSET     0x00001824  /* Four-Byte Filter Value 0 Configuration Register 02 */
#define R_MFWD_FWFOBFV0C03_OFFSET     0x00001834  /* Four-Byte Filter Value 0 Configuration Register 03 */
#define R_MFWD_FWFOBFV0C04_OFFSET     0x00001844  /* Four-Byte Filter Value 0 Configuration Register 04 */
#define R_MFWD_FWFOBFV0C05_OFFSET     0x00001854  /* Four-Byte Filter Value 0 Configuration Register 05 */
#define R_MFWD_FWFOBFV0C06_OFFSET     0x00001864  /* Four-Byte Filter Value 0 Configuration Register 06 */
#define R_MFWD_FWFOBFV0C07_OFFSET     0x00001874  /* Four-Byte Filter Value 0 Configuration Register 07 */
#define R_MFWD_FWFOBFV0C08_OFFSET     0x00001884  /* Four-Byte Filter Value 0 Configuration Register 08 */
#define R_MFWD_FWFOBFV0C09_OFFSET     0x00001894  /* Four-Byte Filter Value 0 Configuration Register 09 */
#define R_MFWD_FWFOBFV0C10_OFFSET     0x000018a4  /* Four-Byte Filter Value 0 Configuration Register 10 */
#define R_MFWD_FWFOBFV0C11_OFFSET     0x000018b4  /* Four-Byte Filter Value 0 Configuration Register 11 */
#define R_MFWD_FWFOBFV0C12_OFFSET     0x000018c4  /* Four-Byte Filter Value 0 Configuration Register 12 */
#define R_MFWD_FWFOBFV0C13_OFFSET     0x000018d4  /* Four-Byte Filter Value 0 Configuration Register 13 */
#define R_MFWD_FWFOBFV0C14_OFFSET     0x000018e4  /* Four-Byte Filter Value 0 Configuration Register 14 */
#define R_MFWD_FWFOBFV0C15_OFFSET     0x000018f4  /* Four-Byte Filter Value 0 Configuration Register 15 */
/* FWFOBFV1C%s Registers (0-15) */
#define R_MFWD_FWFOBFV1C00_OFFSET     0x00001808  /* Four-Byte Filter Value 1 Configuration Register 00 */
#define R_MFWD_FWFOBFV1C01_OFFSET     0x00001818  /* Four-Byte Filter Value 1 Configuration Register 01 */
#define R_MFWD_FWFOBFV1C02_OFFSET     0x00001828  /* Four-Byte Filter Value 1 Configuration Register 02 */
#define R_MFWD_FWFOBFV1C03_OFFSET     0x00001838  /* Four-Byte Filter Value 1 Configuration Register 03 */
#define R_MFWD_FWFOBFV1C04_OFFSET     0x00001848  /* Four-Byte Filter Value 1 Configuration Register 04 */
#define R_MFWD_FWFOBFV1C05_OFFSET     0x00001858  /* Four-Byte Filter Value 1 Configuration Register 05 */
#define R_MFWD_FWFOBFV1C06_OFFSET     0x00001868  /* Four-Byte Filter Value 1 Configuration Register 06 */
#define R_MFWD_FWFOBFV1C07_OFFSET     0x00001878  /* Four-Byte Filter Value 1 Configuration Register 07 */
#define R_MFWD_FWFOBFV1C08_OFFSET     0x00001888  /* Four-Byte Filter Value 1 Configuration Register 08 */
#define R_MFWD_FWFOBFV1C09_OFFSET     0x00001898  /* Four-Byte Filter Value 1 Configuration Register 09 */
#define R_MFWD_FWFOBFV1C10_OFFSET     0x000018a8  /* Four-Byte Filter Value 1 Configuration Register 10 */
#define R_MFWD_FWFOBFV1C11_OFFSET     0x000018b8  /* Four-Byte Filter Value 1 Configuration Register 11 */
#define R_MFWD_FWFOBFV1C12_OFFSET     0x000018c8  /* Four-Byte Filter Value 1 Configuration Register 12 */
#define R_MFWD_FWFOBFV1C13_OFFSET     0x000018d8  /* Four-Byte Filter Value 1 Configuration Register 13 */
#define R_MFWD_FWFOBFV1C14_OFFSET     0x000018e8  /* Four-Byte Filter Value 1 Configuration Register 14 */
#define R_MFWD_FWFOBFV1C15_OFFSET     0x000018f8  /* Four-Byte Filter Value 1 Configuration Register 15 */
/* FWRFC%s Registers (0-15) */
#define R_MFWD_FWRFC00_OFFSET     0x00001c00  /* Range Filter Configuration Register 00 */
#define R_MFWD_FWRFC01_OFFSET     0x00001c10  /* Range Filter Configuration Register 01 */
#define R_MFWD_FWRFC02_OFFSET     0x00001c20  /* Range Filter Configuration Register 02 */
#define R_MFWD_FWRFC03_OFFSET     0x00001c30  /* Range Filter Configuration Register 03 */
#define R_MFWD_FWRFC04_OFFSET     0x00001c40  /* Range Filter Configuration Register 04 */
#define R_MFWD_FWRFC05_OFFSET     0x00001c50  /* Range Filter Configuration Register 05 */
#define R_MFWD_FWRFC06_OFFSET     0x00001c60  /* Range Filter Configuration Register 06 */
#define R_MFWD_FWRFC07_OFFSET     0x00001c70  /* Range Filter Configuration Register 07 */
#define R_MFWD_FWRFC08_OFFSET     0x00001c80  /* Range Filter Configuration Register 08 */
#define R_MFWD_FWRFC09_OFFSET     0x00001c90  /* Range Filter Configuration Register 09 */
#define R_MFWD_FWRFC10_OFFSET     0x00001ca0  /* Range Filter Configuration Register 10 */
#define R_MFWD_FWRFC11_OFFSET     0x00001cb0  /* Range Filter Configuration Register 11 */
#define R_MFWD_FWRFC12_OFFSET     0x00001cc0  /* Range Filter Configuration Register 12 */
#define R_MFWD_FWRFC13_OFFSET     0x00001cd0  /* Range Filter Configuration Register 13 */
#define R_MFWD_FWRFC14_OFFSET     0x00001ce0  /* Range Filter Configuration Register 14 */
#define R_MFWD_FWRFC15_OFFSET     0x00001cf0  /* Range Filter Configuration Register 15 */
/* FWRFVC%s Registers (0-15) */
#define R_MFWD_FWRFVC00_OFFSET     0x00001c04  /* Range Filter Value Configuration Register 00 */
#define R_MFWD_FWRFVC01_OFFSET     0x00001c14  /* Range Filter Value Configuration Register 01 */
#define R_MFWD_FWRFVC02_OFFSET     0x00001c24  /* Range Filter Value Configuration Register 02 */
#define R_MFWD_FWRFVC03_OFFSET     0x00001c34  /* Range Filter Value Configuration Register 03 */
#define R_MFWD_FWRFVC04_OFFSET     0x00001c44  /* Range Filter Value Configuration Register 04 */
#define R_MFWD_FWRFVC05_OFFSET     0x00001c54  /* Range Filter Value Configuration Register 05 */
#define R_MFWD_FWRFVC06_OFFSET     0x00001c64  /* Range Filter Value Configuration Register 06 */
#define R_MFWD_FWRFVC07_OFFSET     0x00001c74  /* Range Filter Value Configuration Register 07 */
#define R_MFWD_FWRFVC08_OFFSET     0x00001c84  /* Range Filter Value Configuration Register 08 */
#define R_MFWD_FWRFVC09_OFFSET     0x00001c94  /* Range Filter Value Configuration Register 09 */
#define R_MFWD_FWRFVC10_OFFSET     0x00001ca4  /* Range Filter Value Configuration Register 10 */
#define R_MFWD_FWRFVC11_OFFSET     0x00001cb4  /* Range Filter Value Configuration Register 11 */
#define R_MFWD_FWRFVC12_OFFSET     0x00001cc4  /* Range Filter Value Configuration Register 12 */
#define R_MFWD_FWRFVC13_OFFSET     0x00001cd4  /* Range Filter Value Configuration Register 13 */
#define R_MFWD_FWRFVC14_OFFSET     0x00001ce4  /* Range Filter Value Configuration Register 14 */
#define R_MFWD_FWRFVC15_OFFSET     0x00001cf4  /* Range Filter Value Configuration Register 15 */
/* FWCFC%s Registers (0-15) */
#define R_MFWD_FWCFC00_OFFSET     0x00002000  /* Cascade Filter Configuration Register 00 */
#define R_MFWD_FWCFC01_OFFSET     0x00002040  /* Cascade Filter Configuration Register 01 */
#define R_MFWD_FWCFC02_OFFSET     0x00002080  /* Cascade Filter Configuration Register 02 */
#define R_MFWD_FWCFC03_OFFSET     0x000020c0  /* Cascade Filter Configuration Register 03 */
#define R_MFWD_FWCFC04_OFFSET     0x00002100  /* Cascade Filter Configuration Register 04 */
#define R_MFWD_FWCFC05_OFFSET     0x00002140  /* Cascade Filter Configuration Register 05 */
#define R_MFWD_FWCFC06_OFFSET     0x00002180  /* Cascade Filter Configuration Register 06 */
#define R_MFWD_FWCFC07_OFFSET     0x000021c0  /* Cascade Filter Configuration Register 07 */
#define R_MFWD_FWCFC08_OFFSET     0x00002200  /* Cascade Filter Configuration Register 08 */
#define R_MFWD_FWCFC09_OFFSET     0x00002240  /* Cascade Filter Configuration Register 09 */
#define R_MFWD_FWCFC10_OFFSET     0x00002280  /* Cascade Filter Configuration Register 10 */
#define R_MFWD_FWCFC11_OFFSET     0x000022c0  /* Cascade Filter Configuration Register 11 */
#define R_MFWD_FWCFC12_OFFSET     0x00002300  /* Cascade Filter Configuration Register 12 */
#define R_MFWD_FWCFC13_OFFSET     0x00002340  /* Cascade Filter Configuration Register 13 */
#define R_MFWD_FWCFC14_OFFSET     0x00002380  /* Cascade Filter Configuration Register 14 */
#define R_MFWD_FWCFC15_OFFSET     0x000023c0  /* Cascade Filter Configuration Register 15 */
/* FWCFMC%s0 Registers (0-15) */
#define R_MFWD_FWCFMC000_OFFSET     0x00002004  /* Cascade Filter Mapping Configuration Register i0 */
#define R_MFWD_FWCFMC010_OFFSET     0x00002044  /* Cascade Filter Mapping Configuration Register i0 */
#define R_MFWD_FWCFMC020_OFFSET     0x00002084  /* Cascade Filter Mapping Configuration Register i0 */
#define R_MFWD_FWCFMC030_OFFSET     0x000020c4  /* Cascade Filter Mapping Configuration Register i0 */
#define R_MFWD_FWCFMC040_OFFSET     0x00002104  /* Cascade Filter Mapping Configuration Register i0 */
#define R_MFWD_FWCFMC050_OFFSET     0x00002144  /* Cascade Filter Mapping Configuration Register i0 */
#define R_MFWD_FWCFMC060_OFFSET     0x00002184  /* Cascade Filter Mapping Configuration Register i0 */
#define R_MFWD_FWCFMC070_OFFSET     0x000021c4  /* Cascade Filter Mapping Configuration Register i0 */
#define R_MFWD_FWCFMC080_OFFSET     0x00002204  /* Cascade Filter Mapping Configuration Register i0 */
#define R_MFWD_FWCFMC090_OFFSET     0x00002244  /* Cascade Filter Mapping Configuration Register i0 */
#define R_MFWD_FWCFMC100_OFFSET     0x00002284  /* Cascade Filter Mapping Configuration Register i0 */
#define R_MFWD_FWCFMC110_OFFSET     0x000022c4  /* Cascade Filter Mapping Configuration Register i0 */
#define R_MFWD_FWCFMC120_OFFSET     0x00002304  /* Cascade Filter Mapping Configuration Register i0 */
#define R_MFWD_FWCFMC130_OFFSET     0x00002344  /* Cascade Filter Mapping Configuration Register i0 */
#define R_MFWD_FWCFMC140_OFFSET     0x00002384  /* Cascade Filter Mapping Configuration Register i0 */
#define R_MFWD_FWCFMC150_OFFSET     0x000023c4  /* Cascade Filter Mapping Configuration Register i0 */
/* FWCFMC%s1 Registers (0-15) */
#define R_MFWD_FWCFMC001_OFFSET     0x00002008  /* Cascade Filter Mapping Configuration Register i1 */
#define R_MFWD_FWCFMC011_OFFSET     0x00002048  /* Cascade Filter Mapping Configuration Register i1 */
#define R_MFWD_FWCFMC021_OFFSET     0x00002088  /* Cascade Filter Mapping Configuration Register i1 */
#define R_MFWD_FWCFMC031_OFFSET     0x000020c8  /* Cascade Filter Mapping Configuration Register i1 */
#define R_MFWD_FWCFMC041_OFFSET     0x00002108  /* Cascade Filter Mapping Configuration Register i1 */
#define R_MFWD_FWCFMC051_OFFSET     0x00002148  /* Cascade Filter Mapping Configuration Register i1 */
#define R_MFWD_FWCFMC061_OFFSET     0x00002188  /* Cascade Filter Mapping Configuration Register i1 */
#define R_MFWD_FWCFMC071_OFFSET     0x000021c8  /* Cascade Filter Mapping Configuration Register i1 */
#define R_MFWD_FWCFMC081_OFFSET     0x00002208  /* Cascade Filter Mapping Configuration Register i1 */
#define R_MFWD_FWCFMC091_OFFSET     0x00002248  /* Cascade Filter Mapping Configuration Register i1 */
#define R_MFWD_FWCFMC101_OFFSET     0x00002288  /* Cascade Filter Mapping Configuration Register i1 */
#define R_MFWD_FWCFMC111_OFFSET     0x000022c8  /* Cascade Filter Mapping Configuration Register i1 */
#define R_MFWD_FWCFMC121_OFFSET     0x00002308  /* Cascade Filter Mapping Configuration Register i1 */
#define R_MFWD_FWCFMC131_OFFSET     0x00002348  /* Cascade Filter Mapping Configuration Register i1 */
#define R_MFWD_FWCFMC141_OFFSET     0x00002388  /* Cascade Filter Mapping Configuration Register i1 */
#define R_MFWD_FWCFMC151_OFFSET     0x000023c8  /* Cascade Filter Mapping Configuration Register i1 */
/* FWCFMC%s2 Registers (0-15) */
#define R_MFWD_FWCFMC002_OFFSET     0x0000200c  /* Cascade Filter Mapping Configuration Register i2 */
#define R_MFWD_FWCFMC012_OFFSET     0x0000204c  /* Cascade Filter Mapping Configuration Register i2 */
#define R_MFWD_FWCFMC022_OFFSET     0x0000208c  /* Cascade Filter Mapping Configuration Register i2 */
#define R_MFWD_FWCFMC032_OFFSET     0x000020cc  /* Cascade Filter Mapping Configuration Register i2 */
#define R_MFWD_FWCFMC042_OFFSET     0x0000210c  /* Cascade Filter Mapping Configuration Register i2 */
#define R_MFWD_FWCFMC052_OFFSET     0x0000214c  /* Cascade Filter Mapping Configuration Register i2 */
#define R_MFWD_FWCFMC062_OFFSET     0x0000218c  /* Cascade Filter Mapping Configuration Register i2 */
#define R_MFWD_FWCFMC072_OFFSET     0x000021cc  /* Cascade Filter Mapping Configuration Register i2 */
#define R_MFWD_FWCFMC082_OFFSET     0x0000220c  /* Cascade Filter Mapping Configuration Register i2 */
#define R_MFWD_FWCFMC092_OFFSET     0x0000224c  /* Cascade Filter Mapping Configuration Register i2 */
#define R_MFWD_FWCFMC102_OFFSET     0x0000228c  /* Cascade Filter Mapping Configuration Register i2 */
#define R_MFWD_FWCFMC112_OFFSET     0x000022cc  /* Cascade Filter Mapping Configuration Register i2 */
#define R_MFWD_FWCFMC122_OFFSET     0x0000230c  /* Cascade Filter Mapping Configuration Register i2 */
#define R_MFWD_FWCFMC132_OFFSET     0x0000234c  /* Cascade Filter Mapping Configuration Register i2 */
#define R_MFWD_FWCFMC142_OFFSET     0x0000238c  /* Cascade Filter Mapping Configuration Register i2 */
#define R_MFWD_FWCFMC152_OFFSET     0x000023cc  /* Cascade Filter Mapping Configuration Register i2 */
/* FWCFMC%s3 Registers (0-15) */
#define R_MFWD_FWCFMC003_OFFSET     0x00002010  /* Cascade Filter Mapping Configuration Register i3 */
#define R_MFWD_FWCFMC013_OFFSET     0x00002050  /* Cascade Filter Mapping Configuration Register i3 */
#define R_MFWD_FWCFMC023_OFFSET     0x00002090  /* Cascade Filter Mapping Configuration Register i3 */
#define R_MFWD_FWCFMC033_OFFSET     0x000020d0  /* Cascade Filter Mapping Configuration Register i3 */
#define R_MFWD_FWCFMC043_OFFSET     0x00002110  /* Cascade Filter Mapping Configuration Register i3 */
#define R_MFWD_FWCFMC053_OFFSET     0x00002150  /* Cascade Filter Mapping Configuration Register i3 */
#define R_MFWD_FWCFMC063_OFFSET     0x00002190  /* Cascade Filter Mapping Configuration Register i3 */
#define R_MFWD_FWCFMC073_OFFSET     0x000021d0  /* Cascade Filter Mapping Configuration Register i3 */
#define R_MFWD_FWCFMC083_OFFSET     0x00002210  /* Cascade Filter Mapping Configuration Register i3 */
#define R_MFWD_FWCFMC093_OFFSET     0x00002250  /* Cascade Filter Mapping Configuration Register i3 */
#define R_MFWD_FWCFMC103_OFFSET     0x00002290  /* Cascade Filter Mapping Configuration Register i3 */
#define R_MFWD_FWCFMC113_OFFSET     0x000022d0  /* Cascade Filter Mapping Configuration Register i3 */
#define R_MFWD_FWCFMC123_OFFSET     0x00002310  /* Cascade Filter Mapping Configuration Register i3 */
#define R_MFWD_FWCFMC133_OFFSET     0x00002350  /* Cascade Filter Mapping Configuration Register i3 */
#define R_MFWD_FWCFMC143_OFFSET     0x00002390  /* Cascade Filter Mapping Configuration Register i3 */
#define R_MFWD_FWCFMC153_OFFSET     0x000023d0  /* Cascade Filter Mapping Configuration Register i3 */
/* FWCFMC%s4 Registers (0-15) */
#define R_MFWD_FWCFMC004_OFFSET     0x00002014  /* Cascade Filter Mapping Configuration Register i4 */
#define R_MFWD_FWCFMC014_OFFSET     0x00002054  /* Cascade Filter Mapping Configuration Register i4 */
#define R_MFWD_FWCFMC024_OFFSET     0x00002094  /* Cascade Filter Mapping Configuration Register i4 */
#define R_MFWD_FWCFMC034_OFFSET     0x000020d4  /* Cascade Filter Mapping Configuration Register i4 */
#define R_MFWD_FWCFMC044_OFFSET     0x00002114  /* Cascade Filter Mapping Configuration Register i4 */
#define R_MFWD_FWCFMC054_OFFSET     0x00002154  /* Cascade Filter Mapping Configuration Register i4 */
#define R_MFWD_FWCFMC064_OFFSET     0x00002194  /* Cascade Filter Mapping Configuration Register i4 */
#define R_MFWD_FWCFMC074_OFFSET     0x000021d4  /* Cascade Filter Mapping Configuration Register i4 */
#define R_MFWD_FWCFMC084_OFFSET     0x00002214  /* Cascade Filter Mapping Configuration Register i4 */
#define R_MFWD_FWCFMC094_OFFSET     0x00002254  /* Cascade Filter Mapping Configuration Register i4 */
#define R_MFWD_FWCFMC104_OFFSET     0x00002294  /* Cascade Filter Mapping Configuration Register i4 */
#define R_MFWD_FWCFMC114_OFFSET     0x000022d4  /* Cascade Filter Mapping Configuration Register i4 */
#define R_MFWD_FWCFMC124_OFFSET     0x00002314  /* Cascade Filter Mapping Configuration Register i4 */
#define R_MFWD_FWCFMC134_OFFSET     0x00002354  /* Cascade Filter Mapping Configuration Register i4 */
#define R_MFWD_FWCFMC144_OFFSET     0x00002394  /* Cascade Filter Mapping Configuration Register i4 */
#define R_MFWD_FWCFMC154_OFFSET     0x000023d4  /* Cascade Filter Mapping Configuration Register i4 */
/* FWCFMC%s5 Registers (0-15) */
#define R_MFWD_FWCFMC005_OFFSET     0x00002018  /* Cascade Filter Mapping Configuration Register i5 */
#define R_MFWD_FWCFMC015_OFFSET     0x00002058  /* Cascade Filter Mapping Configuration Register i5 */
#define R_MFWD_FWCFMC025_OFFSET     0x00002098  /* Cascade Filter Mapping Configuration Register i5 */
#define R_MFWD_FWCFMC035_OFFSET     0x000020d8  /* Cascade Filter Mapping Configuration Register i5 */
#define R_MFWD_FWCFMC045_OFFSET     0x00002118  /* Cascade Filter Mapping Configuration Register i5 */
#define R_MFWD_FWCFMC055_OFFSET     0x00002158  /* Cascade Filter Mapping Configuration Register i5 */
#define R_MFWD_FWCFMC065_OFFSET     0x00002198  /* Cascade Filter Mapping Configuration Register i5 */
#define R_MFWD_FWCFMC075_OFFSET     0x000021d8  /* Cascade Filter Mapping Configuration Register i5 */
#define R_MFWD_FWCFMC085_OFFSET     0x00002218  /* Cascade Filter Mapping Configuration Register i5 */
#define R_MFWD_FWCFMC095_OFFSET     0x00002258  /* Cascade Filter Mapping Configuration Register i5 */
#define R_MFWD_FWCFMC105_OFFSET     0x00002298  /* Cascade Filter Mapping Configuration Register i5 */
#define R_MFWD_FWCFMC115_OFFSET     0x000022d8  /* Cascade Filter Mapping Configuration Register i5 */
#define R_MFWD_FWCFMC125_OFFSET     0x00002318  /* Cascade Filter Mapping Configuration Register i5 */
#define R_MFWD_FWCFMC135_OFFSET     0x00002358  /* Cascade Filter Mapping Configuration Register i5 */
#define R_MFWD_FWCFMC145_OFFSET     0x00002398  /* Cascade Filter Mapping Configuration Register i5 */
#define R_MFWD_FWCFMC155_OFFSET     0x000023d8  /* Cascade Filter Mapping Configuration Register i5 */
/* FWCFMC%s6 Registers (0-15) */
#define R_MFWD_FWCFMC006_OFFSET     0x0000201c  /* Cascade Filter Mapping Configuration Register i6 */
#define R_MFWD_FWCFMC016_OFFSET     0x0000205c  /* Cascade Filter Mapping Configuration Register i6 */
#define R_MFWD_FWCFMC026_OFFSET     0x0000209c  /* Cascade Filter Mapping Configuration Register i6 */
#define R_MFWD_FWCFMC036_OFFSET     0x000020dc  /* Cascade Filter Mapping Configuration Register i6 */
#define R_MFWD_FWCFMC046_OFFSET     0x0000211c  /* Cascade Filter Mapping Configuration Register i6 */
#define R_MFWD_FWCFMC056_OFFSET     0x0000215c  /* Cascade Filter Mapping Configuration Register i6 */
#define R_MFWD_FWCFMC066_OFFSET     0x0000219c  /* Cascade Filter Mapping Configuration Register i6 */
#define R_MFWD_FWCFMC076_OFFSET     0x000021dc  /* Cascade Filter Mapping Configuration Register i6 */
#define R_MFWD_FWCFMC086_OFFSET     0x0000221c  /* Cascade Filter Mapping Configuration Register i6 */
#define R_MFWD_FWCFMC096_OFFSET     0x0000225c  /* Cascade Filter Mapping Configuration Register i6 */
#define R_MFWD_FWCFMC106_OFFSET     0x0000229c  /* Cascade Filter Mapping Configuration Register i6 */
#define R_MFWD_FWCFMC116_OFFSET     0x000022dc  /* Cascade Filter Mapping Configuration Register i6 */
#define R_MFWD_FWCFMC126_OFFSET     0x0000231c  /* Cascade Filter Mapping Configuration Register i6 */
#define R_MFWD_FWCFMC136_OFFSET     0x0000235c  /* Cascade Filter Mapping Configuration Register i6 */
#define R_MFWD_FWCFMC146_OFFSET     0x0000239c  /* Cascade Filter Mapping Configuration Register i6 */
#define R_MFWD_FWCFMC156_OFFSET     0x000023dc  /* Cascade Filter Mapping Configuration Register i6 */
#define R_MFWD_FWIP4SC_OFFSET     0x00004008  /* IPv4 Stream Configuration Register */
#define R_MFWD_FWIP6SC_OFFSET     0x00004018  /* IPv6 Stream Configuration Register */
#define R_MFWD_FWIP6OC_OFFSET     0x0000401c  /* IPv6 Offset Configuration Register */
#define R_MFWD_FWL2SC_OFFSET     0x00004020  /* Layer 2 Stream Configuration Register */
#define R_MFWD_FWSFHEC_OFFSET     0x00004030  /* Stream Filter Hash Equation Configuration Register */
#define R_MFWD_FWSHCR0_OFFSET     0x00004040  /* Software Hash Calculation Request Register 0 */
#define R_MFWD_FWSHCR1_OFFSET     0x00004044  /* Software Hash Calculation Request Register 1 */
#define R_MFWD_FWSHCR2_OFFSET     0x00004048  /* Software Hash Calculation Request Register 2 */
#define R_MFWD_FWSHCR3_OFFSET     0x0000404c  /* Software Hash Calculation Request Register 3 */
#define R_MFWD_FWSHCR4_OFFSET     0x00004050  /* Software Hash Calculation Request Register 4 */
#define R_MFWD_FWSHCR5_OFFSET     0x00004054  /* Software Hash Calculation Request Register 5 */
#define R_MFWD_FWSHCR6_OFFSET     0x00004058  /* Software Hash Calculation Request Register 6 */
#define R_MFWD_FWSHCR7_OFFSET     0x0000405c  /* Software Hash Calculation Request Register 7 */
#define R_MFWD_FWSHCR8_OFFSET     0x00004060  /* Software Hash Calculation Request Register 8 */
#define R_MFWD_FWSHCR9_OFFSET     0x00004064  /* Software Hash Calculation Request Register 9 */
#define R_MFWD_FWSHCR10_OFFSET     0x00004068  /* Software Hash Calculation Request Register 10 */
#define R_MFWD_FWSHCR11_OFFSET     0x0000406c  /* Software Hash Calculation Request Register 11 */
#define R_MFWD_FWSHCR12_OFFSET     0x00004070  /* Software Hash Calculation Request Register 12 */
#define R_MFWD_FWSHCR13_OFFSET     0x00004074  /* Software Hash Calculation Request Register 13 */
#define R_MFWD_FWSHCRR_OFFSET     0x00004078  /* Software Hash Calculation Request Result Register */
#define R_MFWD_FWLTHHEC_OFFSET     0x00004090  /* L3 Hash Entry Configuration Register */
#define R_MFWD_FWLTHHC_OFFSET     0x00004094  /* L3 Hash Configuration Register */
#define R_MFWD_FWLTHTL0_OFFSET     0x000040a0  /* L3 Table Learn Register 0 */
#define R_MFWD_FWLTHTL1_OFFSET     0x000040a4  /* L3 Table Learn Register 1 */
#define R_MFWD_FWLTHTL2_OFFSET     0x000040a8  /* L3 Table Learn Register 2 */
#define R_MFWD_FWLTHTL3_OFFSET     0x000040ac  /* L3 Table Learn Register 3 */
#define R_MFWD_FWLTHTL4_OFFSET     0x000040b0  /* L3 Table Learn Register 4 */
#define R_MFWD_FWLTHTL5_OFFSET     0x000040b4  /* L3 Table Learn Register 5 */
#define R_MFWD_FWLTHTL6_OFFSET     0x000040b8  /* L3 Table Learn Register 6 */
#define R_MFWD_FWLTHTL7_OFFSET     0x000040bc  /* L3 Table Learn Register 7 */
#define R_MFWD_FWLTHTL80_OFFSET     0x000040c0  /* L3 Table Learn Register 80 */
#define R_MFWD_FWLTHTL9_OFFSET     0x000040d0  /* L3 Table Learn Register 9 */
#define R_MFWD_FWLTHTLR_OFFSET     0x000040d4  /* L3 Table Learn Result Register */
#define R_MFWD_FWLTHTIM_OFFSET     0x000040e0  /* L3 Table Initialization Monitoring Register */
#define R_MFWD_FWLTHTEM_OFFSET     0x000040e4  /* L3 Table Entry Monitoring Register */
#define R_MFWD_FWLTHTS0_OFFSET     0x00004100  /* L3 Table Search Register 0 */
#define R_MFWD_FWLTHTS1_OFFSET     0x00004104  /* L3 Table Search Register 1 */
#define R_MFWD_FWLTHTS2_OFFSET     0x00004108  /* L3 Table Search Register 2 */
#define R_MFWD_FWLTHTS3_OFFSET     0x0000410c  /* L3 Table Search Register 3 */
#define R_MFWD_FWLTHTS4_OFFSET     0x00004110  /* L3 Table Search Register 4 */
#define R_MFWD_FWLTHTSR0_OFFSET     0x00004120  /* L3 Table Search Result Register 0 */
#define R_MFWD_FWLTHTSR1_OFFSET     0x00004124  /* L3 Table Search Result Register 1 */
#define R_MFWD_FWLTHTSR2_OFFSET     0x00004128  /* L3 Table Search Result Register 2 */
#define R_MFWD_FWLTHTSR3_OFFSET     0x0000412c  /* L3 Table Search Result Register 3 */
#define R_MFWD_FWLTHTSR40_OFFSET     0x00004130  /* L3 Table Search Result Register 40 */
#define R_MFWD_FWLTHTSR5_OFFSET     0x00004140  /* L3 Table Search Result Register 5 */
#define R_MFWD_FWLTHTR_OFFSET     0x00004150  /* L3 Table Read Register */
#define R_MFWD_FWLTHTRR0_OFFSET     0x00004154  /* L3 Table Read Result Register 0 */
#define R_MFWD_FWLTHTRR1_OFFSET     0x00004158  /* L3 Table Read Result Register 1 */
#define R_MFWD_FWLTHTRR2_OFFSET     0x0000415c  /* L3 Table Read Result Register 2 */
#define R_MFWD_FWLTHTRR3_OFFSET     0x00004160  /* L3 Table Read Result Register 3 */
#define R_MFWD_FWLTHTRR4_OFFSET     0x00004164  /* L3 Table Read Result Register 4 */
#define R_MFWD_FWLTHTRR5_OFFSET     0x00004168  /* L3 Table Read Result Register 5 */
#define R_MFWD_FWLTHTRR6_OFFSET     0x0000416c  /* L3 Table Read Result Register 6 */
#define R_MFWD_FWLTHTRR7_OFFSET     0x00004170  /* L3 Table Read Result Register 7 */
#define R_MFWD_FWLTHTRR8_OFFSET     0x00004174  /* L3 Table Read Result Register 8 */
#define R_MFWD_FWLTHTRR90_OFFSET     0x00004180  /* L3 Table Read Result Register 90 */
#define R_MFWD_FWLTHTRR10_OFFSET     0x00004190  /* L3 Table Read Result Register 10 */
#define R_MFWD_FWMACHEC_OFFSET     0x00004620  /* MAC Hash Entry Configuration Register */
#define R_MFWD_FWMACHC_OFFSET     0x00004624  /* MAC Hash Configuration Register */
#define R_MFWD_FWMACTL0_OFFSET     0x00004630  /* MAC Table Learn Register 0 */
#define R_MFWD_FWMACTL1_OFFSET     0x00004634  /* MAC Table Learn Register 1 */
#define R_MFWD_FWMACTL2_OFFSET     0x00004638  /* MAC Table Learn Register 2 */
#define R_MFWD_FWMACTL3_OFFSET     0x0000463c  /* MAC Table Learn Register 3 */
#define R_MFWD_FWMACTL40_OFFSET     0x00004640  /* MAC Table Learn Register 40 */
#define R_MFWD_FWMACTL5_OFFSET     0x00004650  /* MAC Table Learn Register 5 */
#define R_MFWD_FWMACTLR_OFFSET     0x00004654  /* MAC Table Learn Result Register */
#define R_MFWD_FWMACTIM_OFFSET     0x00004660  /* MAC Table Initialization Monitoring Register */
#define R_MFWD_FWMACTEM_OFFSET     0x00004664  /* MAC Table Entry Monitoring Register */
#define R_MFWD_FWMACTS0_OFFSET     0x00004670  /* MAC Table Search Register 0 */
#define R_MFWD_FWMACTS1_OFFSET     0x00004674  /* MAC Table Search Register 1 */
#define R_MFWD_FWMACTSR0_OFFSET     0x00004678  /* MAC Table Search Result Register 0 */
#define R_MFWD_FWMACTSR1_OFFSET     0x0000467c  /* MAC Table Search Result Register 1 */
#define R_MFWD_FWMACTSR20_OFFSET     0x00004680  /* MAC Table Search Result Register 20 */
#define R_MFWD_FWMACTSR3_OFFSET     0x00004690  /* MAC Table Search Result Register 3 */
#define R_MFWD_FWMACTR_OFFSET     0x000046a0  /* MAC Table Read Register */
#define R_MFWD_FWMACTRR0_OFFSET     0x000046a4  /* MAC Table Read Result Register 0 */
#define R_MFWD_FWMACTRR1_OFFSET     0x000046a8  /* MAC Table Read Result Register 1 */
#define R_MFWD_FWMACTRR2_OFFSET     0x000046ac  /* MAC Table Read Result Register 2 */
#define R_MFWD_FWMACTRR3_OFFSET     0x000046b0  /* MAC Table Read Result Register 3 */
#define R_MFWD_FWMACTRR4_OFFSET     0x000046b4  /* MAC Table Read Result Register 4 */
#define R_MFWD_FWMACTRR50_OFFSET     0x000046c0  /* MAC Table Read Result Register 50 */
#define R_MFWD_FWMACTRR6_OFFSET     0x000046d0  /* MAC Table Read Result Register 6 */
#define R_MFWD_FWMACAGUSPC_OFFSET     0x00004880  /* MAC Aging US Prescaler Configuration Register */
#define R_MFWD_FWMACAGC_OFFSET     0x00004884  /* MAC Aging Configuration Register */
#define R_MFWD_FWMACAGM0_OFFSET     0x00004888  /* MAC Aging Monitoring Register 0 */
#define R_MFWD_FWMACAGM1_OFFSET     0x0000488c  /* MAC Aging Monitoring Register 1 */
#define R_MFWD_FWVLANTEC_OFFSET     0x00004900  /* VLAN Table Entry Configuration Register */
#define R_MFWD_FWVLANTL0_OFFSET     0x00004910  /* VLAN Table Learn Register 0 */
#define R_MFWD_FWVLANTL1_OFFSET     0x00004914  /* VLAN Table Learn Register 1 */
#define R_MFWD_FWVLANTL2_OFFSET     0x00004918  /* VLAN Table Learn Register 2 */
#define R_MFWD_FWVLANTL30_OFFSET     0x00004920  /* VLAN Table Learn Register 30 */
#define R_MFWD_FWVLANTL4_OFFSET     0x00004930  /* VLAN Table Learn Register 4 */
#define R_MFWD_FWVLANTLR_OFFSET     0x00004934  /* VLAN Table Learn Result Register */
#define R_MFWD_FWVLANTIM_OFFSET     0x00004940  /* VLAN Table Initialization Monitoring Register */
#define R_MFWD_FWVLANTEM_OFFSET     0x00004944  /* VLAN Table Entry Monitoring Register */
#define R_MFWD_FWVLANTS_OFFSET     0x00004950  /* VLAN Table Search Register */
#define R_MFWD_FWVLANTSR0_OFFSET     0x00004954  /* VLAN Table Search Result Register 0 */
#define R_MFWD_FWVLANTSR1_OFFSET     0x00004958  /* VLAN Table Search Result Register 1 */
#define R_MFWD_FWVLANTSR20_OFFSET     0x00004960  /* VLAN Table Search Result Register 20 */
#define R_MFWD_FWVLANTSR3_OFFSET     0x00004970  /* VLAN Table Search Result Register 3 */
/* FWPBFC%s Registers (0-2) */
#define R_MFWD_FWPBFC0_OFFSET     0x00004a00  /* Port 0 Port Based Forwarding Configuration Register */
#define R_MFWD_FWPBFC1_OFFSET     0x00004a10  /* Port 1 Port Based Forwarding Configuration Register */
#define R_MFWD_FWPBFC2_OFFSET     0x00004a20  /* Port 2 Port Based Forwarding Configuration Register */
/* FWPBFCSDC%s0 Registers (0-2) */
#define R_MFWD_FWPBFCSDC00_OFFSET     0x00004a04  /* Port 0 Port Based Forwarding CSD Configuration Register 0 */
#define R_MFWD_FWPBFCSDC10_OFFSET     0x00004a14  /* Port 1 Port Based Forwarding CSD Configuration Register 0 */
#define R_MFWD_FWPBFCSDC20_OFFSET     0x00004a24  /* Port 2 Port Based Forwarding CSD Configuration Register 0 */
#define R_MFWD_FWL23URL0_OFFSET     0x00004e00  /* Layer 2/Layer 3 Update Rule Learn Register 0 */
#define R_MFWD_FWL23URL1_OFFSET     0x00004e04  /* Layer 2/Layer 3 Update Rule Learn Register 1 */
#define R_MFWD_FWL23URL2_OFFSET     0x00004e08  /* Layer 2/Layer 3 Update Rule Learn Register 2 */
#define R_MFWD_FWL23URL3_OFFSET     0x00004e0c  /* Layer 2/Layer 3 Update Rule Learn Register 3 */
#define R_MFWD_FWL23URLR_OFFSET     0x00004e10  /* Layer 2/Layer 3 Update Rule Learn Result Register */
#define R_MFWD_FWL23UTIM_OFFSET     0x00004e20  /* Layer 2/Layer 3 Update Table Initialization Monitoring Register */
#define R_MFWD_FWL23URR_OFFSET     0x00004e30  /* Layer 2/Layer 3 Update Rule Read Register */
#define R_MFWD_FWL23URRR0_OFFSET     0x00004e34  /* Layer 2/Layer 3 Update Rule Read Result Register 0 */
#define R_MFWD_FWL23URRR1_OFFSET     0x00004e38  /* Layer 2/Layer 3 Update Rule Read Result Register 1 */
#define R_MFWD_FWL23URRR2_OFFSET     0x00004e3c  /* Layer 2/Layer 3 Update Rule Read Result Register 2 */
#define R_MFWD_FWL23URRR3_OFFSET     0x00004e40  /* Layer 2/Layer 3 Update Rule Read Result Register 3 */
/* FWL23URMC%s Registers (0-31) */
#define R_MFWD_FWL23URMC00_OFFSET     0x00004f00  /* Layer 2/Layer 3 Update Remapping Configuration Register 00 */
#define R_MFWD_FWL23URMC01_OFFSET     0x00004f04  /* Layer 2/Layer 3 Update Remapping Configuration Register 01 */
#define R_MFWD_FWL23URMC02_OFFSET     0x00004f08  /* Layer 2/Layer 3 Update Remapping Configuration Register 02 */
#define R_MFWD_FWL23URMC03_OFFSET     0x00004f0c  /* Layer 2/Layer 3 Update Remapping Configuration Register 03 */
#define R_MFWD_FWL23URMC04_OFFSET     0x00004f10  /* Layer 2/Layer 3 Update Remapping Configuration Register 04 */
#define R_MFWD_FWL23URMC05_OFFSET     0x00004f14  /* Layer 2/Layer 3 Update Remapping Configuration Register 05 */
#define R_MFWD_FWL23URMC06_OFFSET     0x00004f18  /* Layer 2/Layer 3 Update Remapping Configuration Register 06 */
#define R_MFWD_FWL23URMC07_OFFSET     0x00004f1c  /* Layer 2/Layer 3 Update Remapping Configuration Register 07 */
#define R_MFWD_FWL23URMC08_OFFSET     0x00004f20  /* Layer 2/Layer 3 Update Remapping Configuration Register 08 */
#define R_MFWD_FWL23URMC09_OFFSET     0x00004f24  /* Layer 2/Layer 3 Update Remapping Configuration Register 09 */
#define R_MFWD_FWL23URMC10_OFFSET     0x00004f28  /* Layer 2/Layer 3 Update Remapping Configuration Register 10 */
#define R_MFWD_FWL23URMC11_OFFSET     0x00004f2c  /* Layer 2/Layer 3 Update Remapping Configuration Register 11 */
#define R_MFWD_FWL23URMC12_OFFSET     0x00004f30  /* Layer 2/Layer 3 Update Remapping Configuration Register 12 */
#define R_MFWD_FWL23URMC13_OFFSET     0x00004f34  /* Layer 2/Layer 3 Update Remapping Configuration Register 13 */
#define R_MFWD_FWL23URMC14_OFFSET     0x00004f38  /* Layer 2/Layer 3 Update Remapping Configuration Register 14 */
#define R_MFWD_FWL23URMC15_OFFSET     0x00004f3c  /* Layer 2/Layer 3 Update Remapping Configuration Register 15 */
#define R_MFWD_FWL23URMC16_OFFSET     0x00004f40  /* Layer 2/Layer 3 Update Remapping Configuration Register 16 */
#define R_MFWD_FWL23URMC17_OFFSET     0x00004f44  /* Layer 2/Layer 3 Update Remapping Configuration Register 17 */
#define R_MFWD_FWL23URMC18_OFFSET     0x00004f48  /* Layer 2/Layer 3 Update Remapping Configuration Register 18 */
#define R_MFWD_FWL23URMC19_OFFSET     0x00004f4c  /* Layer 2/Layer 3 Update Remapping Configuration Register 19 */
#define R_MFWD_FWL23URMC20_OFFSET     0x00004f50  /* Layer 2/Layer 3 Update Remapping Configuration Register 20 */
#define R_MFWD_FWL23URMC21_OFFSET     0x00004f54  /* Layer 2/Layer 3 Update Remapping Configuration Register 21 */
#define R_MFWD_FWL23URMC22_OFFSET     0x00004f58  /* Layer 2/Layer 3 Update Remapping Configuration Register 22 */
#define R_MFWD_FWL23URMC23_OFFSET     0x00004f5c  /* Layer 2/Layer 3 Update Remapping Configuration Register 23 */
#define R_MFWD_FWL23URMC24_OFFSET     0x00004f60  /* Layer 2/Layer 3 Update Remapping Configuration Register 24 */
#define R_MFWD_FWL23URMC25_OFFSET     0x00004f64  /* Layer 2/Layer 3 Update Remapping Configuration Register 25 */
#define R_MFWD_FWL23URMC26_OFFSET     0x00004f68  /* Layer 2/Layer 3 Update Remapping Configuration Register 26 */
#define R_MFWD_FWL23URMC27_OFFSET     0x00004f6c  /* Layer 2/Layer 3 Update Remapping Configuration Register 27 */
#define R_MFWD_FWL23URMC28_OFFSET     0x00004f70  /* Layer 2/Layer 3 Update Remapping Configuration Register 28 */
#define R_MFWD_FWL23URMC29_OFFSET     0x00004f74  /* Layer 2/Layer 3 Update Remapping Configuration Register 29 */
#define R_MFWD_FWL23URMC30_OFFSET     0x00004f78  /* Layer 2/Layer 3 Update Remapping Configuration Register 30 */
#define R_MFWD_FWL23URMC31_OFFSET     0x00004f7c  /* Layer 2/Layer 3 Update Remapping Configuration Register 31 */
/* FWPMFGC%s Registers (0-15) */
#define R_MFWD_FWPMFGC00_OFFSET     0x00005000  /* PSFP MSDU Filter Global Configuration Register 00 */
#define R_MFWD_FWPMFGC01_OFFSET     0x00005004  /* PSFP MSDU Filter Global Configuration Register 01 */
#define R_MFWD_FWPMFGC02_OFFSET     0x00005008  /* PSFP MSDU Filter Global Configuration Register 02 */
#define R_MFWD_FWPMFGC03_OFFSET     0x0000500c  /* PSFP MSDU Filter Global Configuration Register 03 */
#define R_MFWD_FWPMFGC04_OFFSET     0x00005010  /* PSFP MSDU Filter Global Configuration Register 04 */
#define R_MFWD_FWPMFGC05_OFFSET     0x00005014  /* PSFP MSDU Filter Global Configuration Register 05 */
#define R_MFWD_FWPMFGC06_OFFSET     0x00005018  /* PSFP MSDU Filter Global Configuration Register 06 */
#define R_MFWD_FWPMFGC07_OFFSET     0x0000501c  /* PSFP MSDU Filter Global Configuration Register 07 */
#define R_MFWD_FWPMFGC08_OFFSET     0x00005020  /* PSFP MSDU Filter Global Configuration Register 08 */
#define R_MFWD_FWPMFGC09_OFFSET     0x00005024  /* PSFP MSDU Filter Global Configuration Register 09 */
#define R_MFWD_FWPMFGC10_OFFSET     0x00005028  /* PSFP MSDU Filter Global Configuration Register 10 */
#define R_MFWD_FWPMFGC11_OFFSET     0x0000502c  /* PSFP MSDU Filter Global Configuration Register 11 */
#define R_MFWD_FWPMFGC12_OFFSET     0x00005030  /* PSFP MSDU Filter Global Configuration Register 12 */
#define R_MFWD_FWPMFGC13_OFFSET     0x00005034  /* PSFP MSDU Filter Global Configuration Register 13 */
#define R_MFWD_FWPMFGC14_OFFSET     0x00005038  /* PSFP MSDU Filter Global Configuration Register 14 */
#define R_MFWD_FWPMFGC15_OFFSET     0x0000503c  /* PSFP MSDU Filter Global Configuration Register 15 */
/* FWPMTRFC%s Registers (0-31) */
#define R_MFWD_FWPMTRFC00_OFFSET     0x00005600  /* PSFP Meter 00 Filter Configuration Register */
#define R_MFWD_FWPMTRFC01_OFFSET     0x00005620  /* PSFP Meter 01 Filter Configuration Register */
#define R_MFWD_FWPMTRFC02_OFFSET     0x00005640  /* PSFP Meter 02 Filter Configuration Register */
#define R_MFWD_FWPMTRFC03_OFFSET     0x00005660  /* PSFP Meter 03 Filter Configuration Register */
#define R_MFWD_FWPMTRFC04_OFFSET     0x00005680  /* PSFP Meter 04 Filter Configuration Register */
#define R_MFWD_FWPMTRFC05_OFFSET     0x000056a0  /* PSFP Meter 05 Filter Configuration Register */
#define R_MFWD_FWPMTRFC06_OFFSET     0x000056c0  /* PSFP Meter 06 Filter Configuration Register */
#define R_MFWD_FWPMTRFC07_OFFSET     0x000056e0  /* PSFP Meter 07 Filter Configuration Register */
#define R_MFWD_FWPMTRFC08_OFFSET     0x00005700  /* PSFP Meter 08 Filter Configuration Register */
#define R_MFWD_FWPMTRFC09_OFFSET     0x00005720  /* PSFP Meter 09 Filter Configuration Register */
#define R_MFWD_FWPMTRFC10_OFFSET     0x00005740  /* PSFP Meter 10 Filter Configuration Register */
#define R_MFWD_FWPMTRFC11_OFFSET     0x00005760  /* PSFP Meter 11 Filter Configuration Register */
#define R_MFWD_FWPMTRFC12_OFFSET     0x00005780  /* PSFP Meter 12 Filter Configuration Register */
#define R_MFWD_FWPMTRFC13_OFFSET     0x000057a0  /* PSFP Meter 13 Filter Configuration Register */
#define R_MFWD_FWPMTRFC14_OFFSET     0x000057c0  /* PSFP Meter 14 Filter Configuration Register */
#define R_MFWD_FWPMTRFC15_OFFSET     0x000057e0  /* PSFP Meter 15 Filter Configuration Register */
#define R_MFWD_FWPMTRFC16_OFFSET     0x00005800  /* PSFP Meter 16 Filter Configuration Register */
#define R_MFWD_FWPMTRFC17_OFFSET     0x00005820  /* PSFP Meter 17 Filter Configuration Register */
#define R_MFWD_FWPMTRFC18_OFFSET     0x00005840  /* PSFP Meter 18 Filter Configuration Register */
#define R_MFWD_FWPMTRFC19_OFFSET     0x00005860  /* PSFP Meter 19 Filter Configuration Register */
#define R_MFWD_FWPMTRFC20_OFFSET     0x00005880  /* PSFP Meter 20 Filter Configuration Register */
#define R_MFWD_FWPMTRFC21_OFFSET     0x000058a0  /* PSFP Meter 21 Filter Configuration Register */
#define R_MFWD_FWPMTRFC22_OFFSET     0x000058c0  /* PSFP Meter 22 Filter Configuration Register */
#define R_MFWD_FWPMTRFC23_OFFSET     0x000058e0  /* PSFP Meter 23 Filter Configuration Register */
#define R_MFWD_FWPMTRFC24_OFFSET     0x00005900  /* PSFP Meter 24 Filter Configuration Register */
#define R_MFWD_FWPMTRFC25_OFFSET     0x00005920  /* PSFP Meter 25 Filter Configuration Register */
#define R_MFWD_FWPMTRFC26_OFFSET     0x00005940  /* PSFP Meter 26 Filter Configuration Register */
#define R_MFWD_FWPMTRFC27_OFFSET     0x00005960  /* PSFP Meter 27 Filter Configuration Register */
#define R_MFWD_FWPMTRFC28_OFFSET     0x00005980  /* PSFP Meter 28 Filter Configuration Register */
#define R_MFWD_FWPMTRFC29_OFFSET     0x000059a0  /* PSFP Meter 29 Filter Configuration Register */
#define R_MFWD_FWPMTRFC30_OFFSET     0x000059c0  /* PSFP Meter 30 Filter Configuration Register */
#define R_MFWD_FWPMTRFC31_OFFSET     0x000059e0  /* PSFP Meter 31 Filter Configuration Register */
/* FWPMTRCBSC%s Registers (0-31) */
#define R_MFWD_FWPMTRCBSC00_OFFSET     0x00005604  /* PSFP Meter 00 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC01_OFFSET     0x00005624  /* PSFP Meter 01 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC02_OFFSET     0x00005644  /* PSFP Meter 02 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC03_OFFSET     0x00005664  /* PSFP Meter 03 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC04_OFFSET     0x00005684  /* PSFP Meter 04 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC05_OFFSET     0x000056a4  /* PSFP Meter 05 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC06_OFFSET     0x000056c4  /* PSFP Meter 06 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC07_OFFSET     0x000056e4  /* PSFP Meter 07 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC08_OFFSET     0x00005704  /* PSFP Meter 08 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC09_OFFSET     0x00005724  /* PSFP Meter 09 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC10_OFFSET     0x00005744  /* PSFP Meter 10 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC11_OFFSET     0x00005764  /* PSFP Meter 11 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC12_OFFSET     0x00005784  /* PSFP Meter 12 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC13_OFFSET     0x000057a4  /* PSFP Meter 13 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC14_OFFSET     0x000057c4  /* PSFP Meter 14 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC15_OFFSET     0x000057e4  /* PSFP Meter 15 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC16_OFFSET     0x00005804  /* PSFP Meter 16 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC17_OFFSET     0x00005824  /* PSFP Meter 17 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC18_OFFSET     0x00005844  /* PSFP Meter 18 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC19_OFFSET     0x00005864  /* PSFP Meter 19 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC20_OFFSET     0x00005884  /* PSFP Meter 20 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC21_OFFSET     0x000058a4  /* PSFP Meter 21 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC22_OFFSET     0x000058c4  /* PSFP Meter 22 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC23_OFFSET     0x000058e4  /* PSFP Meter 23 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC24_OFFSET     0x00005904  /* PSFP Meter 24 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC25_OFFSET     0x00005924  /* PSFP Meter 25 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC26_OFFSET     0x00005944  /* PSFP Meter 26 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC27_OFFSET     0x00005964  /* PSFP Meter 27 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC28_OFFSET     0x00005984  /* PSFP Meter 28 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC29_OFFSET     0x000059a4  /* PSFP Meter 29 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC30_OFFSET     0x000059c4  /* PSFP Meter 30 CBS Configuration Register */
#define R_MFWD_FWPMTRCBSC31_OFFSET     0x000059e4  /* PSFP Meter 31 CBS Configuration Register */
/* FWPMTRCIRC%s Registers (0-31) */
#define R_MFWD_FWPMTRCIRC00_OFFSET     0x00005608  /* PSFP Meter 00 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC01_OFFSET     0x00005628  /* PSFP Meter 01 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC02_OFFSET     0x00005648  /* PSFP Meter 02 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC03_OFFSET     0x00005668  /* PSFP Meter 03 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC04_OFFSET     0x00005688  /* PSFP Meter 04 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC05_OFFSET     0x000056a8  /* PSFP Meter 05 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC06_OFFSET     0x000056c8  /* PSFP Meter 06 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC07_OFFSET     0x000056e8  /* PSFP Meter 07 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC08_OFFSET     0x00005708  /* PSFP Meter 08 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC09_OFFSET     0x00005728  /* PSFP Meter 09 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC10_OFFSET     0x00005748  /* PSFP Meter 10 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC11_OFFSET     0x00005768  /* PSFP Meter 11 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC12_OFFSET     0x00005788  /* PSFP Meter 12 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC13_OFFSET     0x000057a8  /* PSFP Meter 13 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC14_OFFSET     0x000057c8  /* PSFP Meter 14 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC15_OFFSET     0x000057e8  /* PSFP Meter 15 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC16_OFFSET     0x00005808  /* PSFP Meter 16 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC17_OFFSET     0x00005828  /* PSFP Meter 17 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC18_OFFSET     0x00005848  /* PSFP Meter 18 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC19_OFFSET     0x00005868  /* PSFP Meter 19 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC20_OFFSET     0x00005888  /* PSFP Meter 20 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC21_OFFSET     0x000058a8  /* PSFP Meter 21 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC22_OFFSET     0x000058c8  /* PSFP Meter 22 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC23_OFFSET     0x000058e8  /* PSFP Meter 23 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC24_OFFSET     0x00005908  /* PSFP Meter 24 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC25_OFFSET     0x00005928  /* PSFP Meter 25 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC26_OFFSET     0x00005948  /* PSFP Meter 26 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC27_OFFSET     0x00005968  /* PSFP Meter 27 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC28_OFFSET     0x00005988  /* PSFP Meter 28 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC29_OFFSET     0x000059a8  /* PSFP Meter 29 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC30_OFFSET     0x000059c8  /* PSFP Meter 30 CIR Configuration Register */
#define R_MFWD_FWPMTRCIRC31_OFFSET     0x000059e8  /* PSFP Meter 31 CIR Configuration Register */
/* FWPMTREBSC%s Registers (0-7) */
#define R_MFWD_FWPMTREBSC0_OFFSET     0x0000560c  /* PSFP Meter 0 EBS Configuration Register */
#define R_MFWD_FWPMTREBSC1_OFFSET     0x0000562c  /* PSFP Meter 1 EBS Configuration Register */
#define R_MFWD_FWPMTREBSC2_OFFSET     0x0000564c  /* PSFP Meter 2 EBS Configuration Register */
#define R_MFWD_FWPMTREBSC3_OFFSET     0x0000566c  /* PSFP Meter 3 EBS Configuration Register */
#define R_MFWD_FWPMTREBSC4_OFFSET     0x0000568c  /* PSFP Meter 4 EBS Configuration Register */
#define R_MFWD_FWPMTREBSC5_OFFSET     0x000056ac  /* PSFP Meter 5 EBS Configuration Register */
#define R_MFWD_FWPMTREBSC6_OFFSET     0x000056cc  /* PSFP Meter 6 EBS Configuration Register */
#define R_MFWD_FWPMTREBSC7_OFFSET     0x000056ec  /* PSFP Meter 7 EBS Configuration Register */
/* FWPMTREIRC%s Registers (0-7) */
#define R_MFWD_FWPMTREIRC0_OFFSET     0x00005610  /* PSFP Meter 0 EIR Configuration Register */
#define R_MFWD_FWPMTREIRC1_OFFSET     0x00005630  /* PSFP Meter 1 EIR Configuration Register */
#define R_MFWD_FWPMTREIRC2_OFFSET     0x00005650  /* PSFP Meter 2 EIR Configuration Register */
#define R_MFWD_FWPMTREIRC3_OFFSET     0x00005670  /* PSFP Meter 3 EIR Configuration Register */
#define R_MFWD_FWPMTREIRC4_OFFSET     0x00005690  /* PSFP Meter 4 EIR Configuration Register */
#define R_MFWD_FWPMTREIRC5_OFFSET     0x000056b0  /* PSFP Meter 5 EIR Configuration Register */
#define R_MFWD_FWPMTREIRC6_OFFSET     0x000056d0  /* PSFP Meter 6 EIR Configuration Register */
#define R_MFWD_FWPMTREIRC7_OFFSET     0x000056f0  /* PSFP Meter 7 EIR Configuration Register */
/* FWPMTRFM%s Registers (0-31) */
#define R_MFWD_FWPMTRFM00_OFFSET     0x00005614  /* PSFP Meter 00 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM01_OFFSET     0x00005634  /* PSFP Meter 01 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM02_OFFSET     0x00005654  /* PSFP Meter 02 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM03_OFFSET     0x00005674  /* PSFP Meter 03 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM04_OFFSET     0x00005694  /* PSFP Meter 04 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM05_OFFSET     0x000056b4  /* PSFP Meter 05 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM06_OFFSET     0x000056d4  /* PSFP Meter 06 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM07_OFFSET     0x000056f4  /* PSFP Meter 07 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM08_OFFSET     0x00005714  /* PSFP Meter 08 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM09_OFFSET     0x00005734  /* PSFP Meter 09 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM10_OFFSET     0x00005754  /* PSFP Meter 10 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM11_OFFSET     0x00005774  /* PSFP Meter 11 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM12_OFFSET     0x00005794  /* PSFP Meter 12 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM13_OFFSET     0x000057b4  /* PSFP Meter 13 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM14_OFFSET     0x000057d4  /* PSFP Meter 14 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM15_OFFSET     0x000057f4  /* PSFP Meter 15 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM16_OFFSET     0x00005814  /* PSFP Meter 16 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM17_OFFSET     0x00005834  /* PSFP Meter 17 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM18_OFFSET     0x00005854  /* PSFP Meter 18 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM19_OFFSET     0x00005874  /* PSFP Meter 19 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM20_OFFSET     0x00005894  /* PSFP Meter 20 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM21_OFFSET     0x000058b4  /* PSFP Meter 21 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM22_OFFSET     0x000058d4  /* PSFP Meter 22 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM23_OFFSET     0x000058f4  /* PSFP Meter 23 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM24_OFFSET     0x00005914  /* PSFP Meter 24 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM25_OFFSET     0x00005934  /* PSFP Meter 25 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM26_OFFSET     0x00005954  /* PSFP Meter 26 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM27_OFFSET     0x00005974  /* PSFP Meter 27 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM28_OFFSET     0x00005994  /* PSFP Meter 28 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM29_OFFSET     0x000059b4  /* PSFP Meter 29 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM30_OFFSET     0x000059d4  /* PSFP Meter 30 Filter Monitoring Register */
#define R_MFWD_FWPMTRFM31_OFFSET     0x000059f4  /* PSFP Meter 31 Filter Monitoring Register */
#define R_MFWD_FWFTL0_OFFSET     0x00006000  /* FRER Table Learn Register 0 */
#define R_MFWD_FWFTL1_OFFSET     0x00006004  /* FRER Table Learn Register 1 */
#define R_MFWD_FWFTLR_OFFSET     0x00006008  /* FRER Table Learn Result Register */
#define R_MFWD_FWFTOC_OFFSET     0x00006010  /* FRER Timeout Configuration Register */
#define R_MFWD_FWFTOPC_OFFSET     0x00006014  /* FRER Timeout Prescaler Configuration Register 0 */
#define R_MFWD_FWFTIM_OFFSET     0x00006020  /* FRER Table Initialization Monitoring Register */
#define R_MFWD_FWFTR_OFFSET     0x00006030  /* FRER Table Read Register */
#define R_MFWD_FWFTRR0_OFFSET     0x00006034  /* FRER Table Read Result Register 0 */
#define R_MFWD_FWFTRR1_OFFSET     0x00006038  /* FRER Table Read Result Register 1 */
#define R_MFWD_FWFTRR2_OFFSET     0x0000603c  /* FRER Table Read Result Register 2 */
/* FWSEQNGC%s Registers (0-31) */
#define R_MFWD_FWSEQNGC00_OFFSET     0x00006100  /* Sequence Number Generation 00 Configuration Register */
#define R_MFWD_FWSEQNGC01_OFFSET     0x00006108  /* Sequence Number Generation 01 Configuration Register */
#define R_MFWD_FWSEQNGC02_OFFSET     0x00006110  /* Sequence Number Generation 02 Configuration Register */
#define R_MFWD_FWSEQNGC03_OFFSET     0x00006118  /* Sequence Number Generation 03 Configuration Register */
#define R_MFWD_FWSEQNGC04_OFFSET     0x00006120  /* Sequence Number Generation 04 Configuration Register */
#define R_MFWD_FWSEQNGC05_OFFSET     0x00006128  /* Sequence Number Generation 05 Configuration Register */
#define R_MFWD_FWSEQNGC06_OFFSET     0x00006130  /* Sequence Number Generation 06 Configuration Register */
#define R_MFWD_FWSEQNGC07_OFFSET     0x00006138  /* Sequence Number Generation 07 Configuration Register */
#define R_MFWD_FWSEQNGC08_OFFSET     0x00006140  /* Sequence Number Generation 08 Configuration Register */
#define R_MFWD_FWSEQNGC09_OFFSET     0x00006148  /* Sequence Number Generation 09 Configuration Register */
#define R_MFWD_FWSEQNGC10_OFFSET     0x00006150  /* Sequence Number Generation 10 Configuration Register */
#define R_MFWD_FWSEQNGC11_OFFSET     0x00006158  /* Sequence Number Generation 11 Configuration Register */
#define R_MFWD_FWSEQNGC12_OFFSET     0x00006160  /* Sequence Number Generation 12 Configuration Register */
#define R_MFWD_FWSEQNGC13_OFFSET     0x00006168  /* Sequence Number Generation 13 Configuration Register */
#define R_MFWD_FWSEQNGC14_OFFSET     0x00006170  /* Sequence Number Generation 14 Configuration Register */
#define R_MFWD_FWSEQNGC15_OFFSET     0x00006178  /* Sequence Number Generation 15 Configuration Register */
#define R_MFWD_FWSEQNGC16_OFFSET     0x00006180  /* Sequence Number Generation 16 Configuration Register */
#define R_MFWD_FWSEQNGC17_OFFSET     0x00006188  /* Sequence Number Generation 17 Configuration Register */
#define R_MFWD_FWSEQNGC18_OFFSET     0x00006190  /* Sequence Number Generation 18 Configuration Register */
#define R_MFWD_FWSEQNGC19_OFFSET     0x00006198  /* Sequence Number Generation 19 Configuration Register */
#define R_MFWD_FWSEQNGC20_OFFSET     0x000061a0  /* Sequence Number Generation 20 Configuration Register */
#define R_MFWD_FWSEQNGC21_OFFSET     0x000061a8  /* Sequence Number Generation 21 Configuration Register */
#define R_MFWD_FWSEQNGC22_OFFSET     0x000061b0  /* Sequence Number Generation 22 Configuration Register */
#define R_MFWD_FWSEQNGC23_OFFSET     0x000061b8  /* Sequence Number Generation 23 Configuration Register */
#define R_MFWD_FWSEQNGC24_OFFSET     0x000061c0  /* Sequence Number Generation 24 Configuration Register */
#define R_MFWD_FWSEQNGC25_OFFSET     0x000061c8  /* Sequence Number Generation 25 Configuration Register */
#define R_MFWD_FWSEQNGC26_OFFSET     0x000061d0  /* Sequence Number Generation 26 Configuration Register */
#define R_MFWD_FWSEQNGC27_OFFSET     0x000061d8  /* Sequence Number Generation 27 Configuration Register */
#define R_MFWD_FWSEQNGC28_OFFSET     0x000061e0  /* Sequence Number Generation 28 Configuration Register */
#define R_MFWD_FWSEQNGC29_OFFSET     0x000061e8  /* Sequence Number Generation 29 Configuration Register */
#define R_MFWD_FWSEQNGC30_OFFSET     0x000061f0  /* Sequence Number Generation 30 Configuration Register */
#define R_MFWD_FWSEQNGC31_OFFSET     0x000061f8  /* Sequence Number Generation 31 Configuration Register */
/* FWSEQNGM%s Registers (0-31) */
#define R_MFWD_FWSEQNGM00_OFFSET     0x00006104  /* Sequence Number Generation 00 Monitoring Register */
#define R_MFWD_FWSEQNGM01_OFFSET     0x0000610c  /* Sequence Number Generation 01 Monitoring Register */
#define R_MFWD_FWSEQNGM02_OFFSET     0x00006114  /* Sequence Number Generation 02 Monitoring Register */
#define R_MFWD_FWSEQNGM03_OFFSET     0x0000611c  /* Sequence Number Generation 03 Monitoring Register */
#define R_MFWD_FWSEQNGM04_OFFSET     0x00006124  /* Sequence Number Generation 04 Monitoring Register */
#define R_MFWD_FWSEQNGM05_OFFSET     0x0000612c  /* Sequence Number Generation 05 Monitoring Register */
#define R_MFWD_FWSEQNGM06_OFFSET     0x00006134  /* Sequence Number Generation 06 Monitoring Register */
#define R_MFWD_FWSEQNGM07_OFFSET     0x0000613c  /* Sequence Number Generation 07 Monitoring Register */
#define R_MFWD_FWSEQNGM08_OFFSET     0x00006144  /* Sequence Number Generation 08 Monitoring Register */
#define R_MFWD_FWSEQNGM09_OFFSET     0x0000614c  /* Sequence Number Generation 09 Monitoring Register */
#define R_MFWD_FWSEQNGM10_OFFSET     0x00006154  /* Sequence Number Generation 10 Monitoring Register */
#define R_MFWD_FWSEQNGM11_OFFSET     0x0000615c  /* Sequence Number Generation 11 Monitoring Register */
#define R_MFWD_FWSEQNGM12_OFFSET     0x00006164  /* Sequence Number Generation 12 Monitoring Register */
#define R_MFWD_FWSEQNGM13_OFFSET     0x0000616c  /* Sequence Number Generation 13 Monitoring Register */
#define R_MFWD_FWSEQNGM14_OFFSET     0x00006174  /* Sequence Number Generation 14 Monitoring Register */
#define R_MFWD_FWSEQNGM15_OFFSET     0x0000617c  /* Sequence Number Generation 15 Monitoring Register */
#define R_MFWD_FWSEQNGM16_OFFSET     0x00006184  /* Sequence Number Generation 16 Monitoring Register */
#define R_MFWD_FWSEQNGM17_OFFSET     0x0000618c  /* Sequence Number Generation 17 Monitoring Register */
#define R_MFWD_FWSEQNGM18_OFFSET     0x00006194  /* Sequence Number Generation 18 Monitoring Register */
#define R_MFWD_FWSEQNGM19_OFFSET     0x0000619c  /* Sequence Number Generation 19 Monitoring Register */
#define R_MFWD_FWSEQNGM20_OFFSET     0x000061a4  /* Sequence Number Generation 20 Monitoring Register */
#define R_MFWD_FWSEQNGM21_OFFSET     0x000061ac  /* Sequence Number Generation 21 Monitoring Register */
#define R_MFWD_FWSEQNGM22_OFFSET     0x000061b4  /* Sequence Number Generation 22 Monitoring Register */
#define R_MFWD_FWSEQNGM23_OFFSET     0x000061bc  /* Sequence Number Generation 23 Monitoring Register */
#define R_MFWD_FWSEQNGM24_OFFSET     0x000061c4  /* Sequence Number Generation 24 Monitoring Register */
#define R_MFWD_FWSEQNGM25_OFFSET     0x000061cc  /* Sequence Number Generation 25 Monitoring Register */
#define R_MFWD_FWSEQNGM26_OFFSET     0x000061d4  /* Sequence Number Generation 26 Monitoring Register */
#define R_MFWD_FWSEQNGM27_OFFSET     0x000061dc  /* Sequence Number Generation 27 Monitoring Register */
#define R_MFWD_FWSEQNGM28_OFFSET     0x000061e4  /* Sequence Number Generation 28 Monitoring Register */
#define R_MFWD_FWSEQNGM29_OFFSET     0x000061ec  /* Sequence Number Generation 29 Monitoring Register */
#define R_MFWD_FWSEQNGM30_OFFSET     0x000061f4  /* Sequence Number Generation 30 Monitoring Register */
#define R_MFWD_FWSEQNGM31_OFFSET     0x000061fc  /* Sequence Number Generation 31 Monitoring Register */
#define R_MFWD_FWSEQNRC_OFFSET     0x00006200  /* Sequence Number Reset Configuration Register */
/* FWCTFDCN%s Registers (0-1) */
#define R_MFWD_FWCTFDCN0_OFFSET     0x00006300  /* Port 0 Cut-Through Forwarded Descriptor Counter Register */
#define R_MFWD_FWCTFDCN1_OFFSET     0x00006320  /* Port 1 Cut-Through Forwarded Descriptor Counter Register */
/* FWLTHFDCN%s Registers (0-2) */
#define R_MFWD_FWLTHFDCN0_OFFSET     0x00006304  /* Port 0 Layer 3 Forwarded Descriptor Counter Register */
#define R_MFWD_FWLTHFDCN1_OFFSET     0x00006324  /* Port 1 Layer 3 Forwarded Descriptor Counter Register */
#define R_MFWD_FWLTHFDCN2_OFFSET     0x00006344  /* Port 2 Layer 3 Forwarded Descriptor Counter Register */
/* FWLTWFDCN%s Registers (0-2) */
#define R_MFWD_FWLTWFDCN0_OFFSET     0x0000630c  /* Port 0 Layer 2 Forwarded Descriptor Counter Register */
#define R_MFWD_FWLTWFDCN1_OFFSET     0x0000632c  /* Port 1 Layer 2 Forwarded Descriptor Counter Register */
#define R_MFWD_FWLTWFDCN2_OFFSET     0x0000634c  /* Port 2 Layer 2 Forwarded Descriptor Counter Register */
/* FWPBFDCN%s Registers (0-2) */
#define R_MFWD_FWPBFDCN0_OFFSET     0x00006310  /* Port 0 Port Based Forwarded Descriptor Counter Register */
#define R_MFWD_FWPBFDCN1_OFFSET     0x00006330  /* Port 1 Port Based Forwarded Descriptor Counter Register */
#define R_MFWD_FWPBFDCN2_OFFSET     0x00006350  /* Port 2 Port Based Forwarded Descriptor Counter Register */
/* FWMHLCN%s Registers (0-2) */
#define R_MFWD_FWMHLCN0_OFFSET     0x00006314  /* Port 0 MAC Hardware Learn Counter Register */
#define R_MFWD_FWMHLCN1_OFFSET     0x00006334  /* Port 1 MAC Hardware Learn Counter Register */
#define R_MFWD_FWMHLCN2_OFFSET     0x00006354  /* Port 2 MAC Hardware Learn Counter Register */
#define R_MFWD_FWDDFDCN2_OFFSET     0x00006340  /* Port 2 Direct Descriptor Forwarded Descriptor Counter Register */
/* FWWMRDCN%s Registers (0-2) */
#define R_MFWD_FWWMRDCN0_OFFSET     0x00006504  /* Port 0 Watermark Rejected Descriptor Counter Register */
#define R_MFWD_FWWMRDCN1_OFFSET     0x00006524  /* Port 1 Watermark Rejected Descriptor Counter Register */
#define R_MFWD_FWWMRDCN2_OFFSET     0x00006544  /* Port 2 Watermark Rejected Descriptor Counter Register */
/* FWCTRDCN%s Registers (0-1) */
#define R_MFWD_FWCTRDCN0_OFFSET     0x00006508  /* Port 0 Cut-Through Rejected Descriptor Counter Register */
#define R_MFWD_FWCTRDCN1_OFFSET     0x00006528  /* Port 1 Cut-Through Rejected Descriptor Counter Register */
/* FWLTHRDCN%s Registers (0-2) */
#define R_MFWD_FWLTHRDCN0_OFFSET     0x0000650c  /* Port 0 Layer 3 Rejected Descriptor Counter Register */
#define R_MFWD_FWLTHRDCN1_OFFSET     0x0000652c  /* Port 1 Layer 3 Rejected Descriptor Counter Register */
#define R_MFWD_FWLTHRDCN2_OFFSET     0x0000654c  /* Port 2 Layer 3 Rejected Descriptor Counter Register */
/* FWLTWRDCN%s Registers (0-2) */
#define R_MFWD_FWLTWRDCN0_OFFSET     0x00006514  /* Port 0 Layer 2 Rejected Descriptor Counter Register */
#define R_MFWD_FWLTWRDCN1_OFFSET     0x00006534  /* Port 1 Layer 2 Rejected Descriptor Counter Register */
#define R_MFWD_FWLTWRDCN2_OFFSET     0x00006554  /* Port 2 Layer 2 Rejected Descriptor Counter Register */
/* FWPBRDCN%s Registers (0-2) */
#define R_MFWD_FWPBRDCN0_OFFSET     0x00006518  /* Port 0 Port Based Rejected Descriptor Counter Register */
#define R_MFWD_FWPBRDCN1_OFFSET     0x00006538  /* Port 1 Port Based Rejected Descriptor Counter Register */
#define R_MFWD_FWPBRDCN2_OFFSET     0x00006558  /* Port 2 Port Based Rejected Descriptor Counter Register */
#define R_MFWD_FWDDRDCN2_OFFSET     0x00006548  /* Port 2 Direct Descriptor Rejected Descriptor Counter Register */
/* FWPMFDCN%s Registers (0-15) */
#define R_MFWD_FWPMFDCN00_OFFSET     0x00006700  /* PSFP MSDU 00 Filtered Descriptor Counter Register */
#define R_MFWD_FWPMFDCN01_OFFSET     0x00006704  /* PSFP MSDU 01 Filtered Descriptor Counter Register */
#define R_MFWD_FWPMFDCN02_OFFSET     0x00006708  /* PSFP MSDU 02 Filtered Descriptor Counter Register */
#define R_MFWD_FWPMFDCN03_OFFSET     0x0000670c  /* PSFP MSDU 03 Filtered Descriptor Counter Register */
#define R_MFWD_FWPMFDCN04_OFFSET     0x00006710  /* PSFP MSDU 04 Filtered Descriptor Counter Register */
#define R_MFWD_FWPMFDCN05_OFFSET     0x00006714  /* PSFP MSDU 05 Filtered Descriptor Counter Register */
#define R_MFWD_FWPMFDCN06_OFFSET     0x00006718  /* PSFP MSDU 06 Filtered Descriptor Counter Register */
#define R_MFWD_FWPMFDCN07_OFFSET     0x0000671c  /* PSFP MSDU 07 Filtered Descriptor Counter Register */
#define R_MFWD_FWPMFDCN08_OFFSET     0x00006720  /* PSFP MSDU 08 Filtered Descriptor Counter Register */
#define R_MFWD_FWPMFDCN09_OFFSET     0x00006724  /* PSFP MSDU 09 Filtered Descriptor Counter Register */
#define R_MFWD_FWPMFDCN10_OFFSET     0x00006728  /* PSFP MSDU 10 Filtered Descriptor Counter Register */
#define R_MFWD_FWPMFDCN11_OFFSET     0x0000672c  /* PSFP MSDU 11 Filtered Descriptor Counter Register */
#define R_MFWD_FWPMFDCN12_OFFSET     0x00006730  /* PSFP MSDU 12 Filtered Descriptor Counter Register */
#define R_MFWD_FWPMFDCN13_OFFSET     0x00006734  /* PSFP MSDU 13 Filtered Descriptor Counter Register */
#define R_MFWD_FWPMFDCN14_OFFSET     0x00006738  /* PSFP MSDU 14 Filtered Descriptor Counter Register */
#define R_MFWD_FWPMFDCN15_OFFSET     0x0000673c  /* PSFP MSDU 15 Filtered Descriptor Counter Register */
/* FWPMGDCN%s Registers (0-31) */
#define R_MFWD_FWPMGDCN00_OFFSET     0x00006800  /* PSFP Meter 00 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN01_OFFSET     0x00006810  /* PSFP Meter 01 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN02_OFFSET     0x00006820  /* PSFP Meter 02 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN03_OFFSET     0x00006830  /* PSFP Meter 03 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN04_OFFSET     0x00006840  /* PSFP Meter 04 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN05_OFFSET     0x00006850  /* PSFP Meter 05 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN06_OFFSET     0x00006860  /* PSFP Meter 06 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN07_OFFSET     0x00006870  /* PSFP Meter 07 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN08_OFFSET     0x00006880  /* PSFP Meter 08 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN09_OFFSET     0x00006890  /* PSFP Meter 09 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN10_OFFSET     0x000068a0  /* PSFP Meter 10 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN11_OFFSET     0x000068b0  /* PSFP Meter 11 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN12_OFFSET     0x000068c0  /* PSFP Meter 12 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN13_OFFSET     0x000068d0  /* PSFP Meter 13 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN14_OFFSET     0x000068e0  /* PSFP Meter 14 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN15_OFFSET     0x000068f0  /* PSFP Meter 15 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN16_OFFSET     0x00006900  /* PSFP Meter 16 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN17_OFFSET     0x00006910  /* PSFP Meter 17 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN18_OFFSET     0x00006920  /* PSFP Meter 18 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN19_OFFSET     0x00006930  /* PSFP Meter 19 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN20_OFFSET     0x00006940  /* PSFP Meter 20 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN21_OFFSET     0x00006950  /* PSFP Meter 21 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN22_OFFSET     0x00006960  /* PSFP Meter 22 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN23_OFFSET     0x00006970  /* PSFP Meter 23 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN24_OFFSET     0x00006980  /* PSFP Meter 24 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN25_OFFSET     0x00006990  /* PSFP Meter 25 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN26_OFFSET     0x000069a0  /* PSFP Meter 26 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN27_OFFSET     0x000069b0  /* PSFP Meter 27 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN28_OFFSET     0x000069c0  /* PSFP Meter 28 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN29_OFFSET     0x000069d0  /* PSFP Meter 29 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN30_OFFSET     0x000069e0  /* PSFP Meter 30 Green Descriptor Counter Register */
#define R_MFWD_FWPMGDCN31_OFFSET     0x000069f0  /* PSFP Meter 31 Green Descriptor Counter Register */
/* FWPMYDCN%s Registers (0-7) */
#define R_MFWD_FWPMYDCN0_OFFSET     0x00006804  /* PSFP Meter 0 Yellow Descriptor Counter Register */
#define R_MFWD_FWPMYDCN1_OFFSET     0x00006814  /* PSFP Meter 1 Yellow Descriptor Counter Register */
#define R_MFWD_FWPMYDCN2_OFFSET     0x00006824  /* PSFP Meter 2 Yellow Descriptor Counter Register */
#define R_MFWD_FWPMYDCN3_OFFSET     0x00006834  /* PSFP Meter 3 Yellow Descriptor Counter Register */
#define R_MFWD_FWPMYDCN4_OFFSET     0x00006844  /* PSFP Meter 4 Yellow Descriptor Counter Register */
#define R_MFWD_FWPMYDCN5_OFFSET     0x00006854  /* PSFP Meter 5 Yellow Descriptor Counter Register */
#define R_MFWD_FWPMYDCN6_OFFSET     0x00006864  /* PSFP Meter 6 Yellow Descriptor Counter Register */
#define R_MFWD_FWPMYDCN7_OFFSET     0x00006874  /* PSFP Meter 7 Yellow Descriptor Counter Register */
/* FWPMRDCN%s Registers (0-31) */
#define R_MFWD_FWPMRDCN00_OFFSET     0x00006808  /* PSFP Meter 00 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN01_OFFSET     0x00006818  /* PSFP Meter 01 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN02_OFFSET     0x00006828  /* PSFP Meter 02 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN03_OFFSET     0x00006838  /* PSFP Meter 03 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN04_OFFSET     0x00006848  /* PSFP Meter 04 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN05_OFFSET     0x00006858  /* PSFP Meter 05 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN06_OFFSET     0x00006868  /* PSFP Meter 06 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN07_OFFSET     0x00006878  /* PSFP Meter 07 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN08_OFFSET     0x00006888  /* PSFP Meter 08 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN09_OFFSET     0x00006898  /* PSFP Meter 09 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN10_OFFSET     0x000068a8  /* PSFP Meter 10 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN11_OFFSET     0x000068b8  /* PSFP Meter 11 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN12_OFFSET     0x000068c8  /* PSFP Meter 12 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN13_OFFSET     0x000068d8  /* PSFP Meter 13 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN14_OFFSET     0x000068e8  /* PSFP Meter 14 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN15_OFFSET     0x000068f8  /* PSFP Meter 15 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN16_OFFSET     0x00006908  /* PSFP Meter 16 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN17_OFFSET     0x00006918  /* PSFP Meter 17 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN18_OFFSET     0x00006928  /* PSFP Meter 18 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN19_OFFSET     0x00006938  /* PSFP Meter 19 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN20_OFFSET     0x00006948  /* PSFP Meter 20 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN21_OFFSET     0x00006958  /* PSFP Meter 21 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN22_OFFSET     0x00006968  /* PSFP Meter 22 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN23_OFFSET     0x00006978  /* PSFP Meter 23 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN24_OFFSET     0x00006988  /* PSFP Meter 24 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN25_OFFSET     0x00006998  /* PSFP Meter 25 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN26_OFFSET     0x000069a8  /* PSFP Meter 26 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN27_OFFSET     0x000069b8  /* PSFP Meter 27 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN28_OFFSET     0x000069c8  /* PSFP Meter 28 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN29_OFFSET     0x000069d8  /* PSFP Meter 29 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN30_OFFSET     0x000069e8  /* PSFP Meter 30 Red Descriptor Counter Register */
#define R_MFWD_FWPMRDCN31_OFFSET     0x000069f8  /* PSFP Meter 31 Red Descriptor Counter Register */
/* FWFRPPCN%s Registers (0-127) */
#define R_MFWD_FWFRPPCN000_OFFSET     0x00006a00  /* FRER 000 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN001_OFFSET     0x00006a08  /* FRER 001 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN002_OFFSET     0x00006a10  /* FRER 002 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN003_OFFSET     0x00006a18  /* FRER 003 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN004_OFFSET     0x00006a20  /* FRER 004 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN005_OFFSET     0x00006a28  /* FRER 005 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN006_OFFSET     0x00006a30  /* FRER 006 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN007_OFFSET     0x00006a38  /* FRER 007 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN008_OFFSET     0x00006a40  /* FRER 008 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN009_OFFSET     0x00006a48  /* FRER 009 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN010_OFFSET     0x00006a50  /* FRER 010 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN011_OFFSET     0x00006a58  /* FRER 011 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN012_OFFSET     0x00006a60  /* FRER 012 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN013_OFFSET     0x00006a68  /* FRER 013 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN014_OFFSET     0x00006a70  /* FRER 014 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN015_OFFSET     0x00006a78  /* FRER 015 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN016_OFFSET     0x00006a80  /* FRER 016 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN017_OFFSET     0x00006a88  /* FRER 017 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN018_OFFSET     0x00006a90  /* FRER 018 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN019_OFFSET     0x00006a98  /* FRER 019 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN020_OFFSET     0x00006aa0  /* FRER 020 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN021_OFFSET     0x00006aa8  /* FRER 021 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN022_OFFSET     0x00006ab0  /* FRER 022 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN023_OFFSET     0x00006ab8  /* FRER 023 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN024_OFFSET     0x00006ac0  /* FRER 024 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN025_OFFSET     0x00006ac8  /* FRER 025 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN026_OFFSET     0x00006ad0  /* FRER 026 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN027_OFFSET     0x00006ad8  /* FRER 027 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN028_OFFSET     0x00006ae0  /* FRER 028 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN029_OFFSET     0x00006ae8  /* FRER 029 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN030_OFFSET     0x00006af0  /* FRER 030 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN031_OFFSET     0x00006af8  /* FRER 031 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN032_OFFSET     0x00006b00  /* FRER 032 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN033_OFFSET     0x00006b08  /* FRER 033 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN034_OFFSET     0x00006b10  /* FRER 034 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN035_OFFSET     0x00006b18  /* FRER 035 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN036_OFFSET     0x00006b20  /* FRER 036 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN037_OFFSET     0x00006b28  /* FRER 037 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN038_OFFSET     0x00006b30  /* FRER 038 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN039_OFFSET     0x00006b38  /* FRER 039 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN040_OFFSET     0x00006b40  /* FRER 040 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN041_OFFSET     0x00006b48  /* FRER 041 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN042_OFFSET     0x00006b50  /* FRER 042 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN043_OFFSET     0x00006b58  /* FRER 043 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN044_OFFSET     0x00006b60  /* FRER 044 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN045_OFFSET     0x00006b68  /* FRER 045 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN046_OFFSET     0x00006b70  /* FRER 046 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN047_OFFSET     0x00006b78  /* FRER 047 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN048_OFFSET     0x00006b80  /* FRER 048 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN049_OFFSET     0x00006b88  /* FRER 049 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN050_OFFSET     0x00006b90  /* FRER 050 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN051_OFFSET     0x00006b98  /* FRER 051 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN052_OFFSET     0x00006ba0  /* FRER 052 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN053_OFFSET     0x00006ba8  /* FRER 053 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN054_OFFSET     0x00006bb0  /* FRER 054 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN055_OFFSET     0x00006bb8  /* FRER 055 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN056_OFFSET     0x00006bc0  /* FRER 056 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN057_OFFSET     0x00006bc8  /* FRER 057 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN058_OFFSET     0x00006bd0  /* FRER 058 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN059_OFFSET     0x00006bd8  /* FRER 059 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN060_OFFSET     0x00006be0  /* FRER 060 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN061_OFFSET     0x00006be8  /* FRER 061 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN062_OFFSET     0x00006bf0  /* FRER 062 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN063_OFFSET     0x00006bf8  /* FRER 063 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN064_OFFSET     0x00006c00  /* FRER 064 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN065_OFFSET     0x00006c08  /* FRER 065 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN066_OFFSET     0x00006c10  /* FRER 066 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN067_OFFSET     0x00006c18  /* FRER 067 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN068_OFFSET     0x00006c20  /* FRER 068 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN069_OFFSET     0x00006c28  /* FRER 069 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN070_OFFSET     0x00006c30  /* FRER 070 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN071_OFFSET     0x00006c38  /* FRER 071 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN072_OFFSET     0x00006c40  /* FRER 072 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN073_OFFSET     0x00006c48  /* FRER 073 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN074_OFFSET     0x00006c50  /* FRER 074 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN075_OFFSET     0x00006c58  /* FRER 075 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN076_OFFSET     0x00006c60  /* FRER 076 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN077_OFFSET     0x00006c68  /* FRER 077 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN078_OFFSET     0x00006c70  /* FRER 078 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN079_OFFSET     0x00006c78  /* FRER 079 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN080_OFFSET     0x00006c80  /* FRER 080 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN081_OFFSET     0x00006c88  /* FRER 081 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN082_OFFSET     0x00006c90  /* FRER 082 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN083_OFFSET     0x00006c98  /* FRER 083 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN084_OFFSET     0x00006ca0  /* FRER 084 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN085_OFFSET     0x00006ca8  /* FRER 085 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN086_OFFSET     0x00006cb0  /* FRER 086 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN087_OFFSET     0x00006cb8  /* FRER 087 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN088_OFFSET     0x00006cc0  /* FRER 088 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN089_OFFSET     0x00006cc8  /* FRER 089 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN090_OFFSET     0x00006cd0  /* FRER 090 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN091_OFFSET     0x00006cd8  /* FRER 091 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN092_OFFSET     0x00006ce0  /* FRER 092 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN093_OFFSET     0x00006ce8  /* FRER 093 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN094_OFFSET     0x00006cf0  /* FRER 094 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN095_OFFSET     0x00006cf8  /* FRER 095 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN096_OFFSET     0x00006d00  /* FRER 096 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN097_OFFSET     0x00006d08  /* FRER 097 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN098_OFFSET     0x00006d10  /* FRER 098 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN099_OFFSET     0x00006d18  /* FRER 099 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN100_OFFSET     0x00006d20  /* FRER 100 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN101_OFFSET     0x00006d28  /* FRER 101 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN102_OFFSET     0x00006d30  /* FRER 102 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN103_OFFSET     0x00006d38  /* FRER 103 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN104_OFFSET     0x00006d40  /* FRER 104 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN105_OFFSET     0x00006d48  /* FRER 105 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN106_OFFSET     0x00006d50  /* FRER 106 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN107_OFFSET     0x00006d58  /* FRER 107 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN108_OFFSET     0x00006d60  /* FRER 108 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN109_OFFSET     0x00006d68  /* FRER 109 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN110_OFFSET     0x00006d70  /* FRER 110 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN111_OFFSET     0x00006d78  /* FRER 111 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN112_OFFSET     0x00006d80  /* FRER 112 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN113_OFFSET     0x00006d88  /* FRER 113 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN114_OFFSET     0x00006d90  /* FRER 114 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN115_OFFSET     0x00006d98  /* FRER 115 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN116_OFFSET     0x00006da0  /* FRER 116 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN117_OFFSET     0x00006da8  /* FRER 117 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN118_OFFSET     0x00006db0  /* FRER 118 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN119_OFFSET     0x00006db8  /* FRER 119 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN120_OFFSET     0x00006dc0  /* FRER 120 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN121_OFFSET     0x00006dc8  /* FRER 121 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN122_OFFSET     0x00006dd0  /* FRER 122 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN123_OFFSET     0x00006dd8  /* FRER 123 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN124_OFFSET     0x00006de0  /* FRER 124 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN125_OFFSET     0x00006de8  /* FRER 125 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN126_OFFSET     0x00006df0  /* FRER 126 Passed Packet Counter Register */
#define R_MFWD_FWFRPPCN127_OFFSET     0x00006df8  /* FRER 127 Passed Packet Counter Register */
/* FWFRDPCN%s Registers (0-127) */
#define R_MFWD_FWFRDPCN000_OFFSET     0x00006a04  /* FRER 000 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN001_OFFSET     0x00006a0c  /* FRER 001 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN002_OFFSET     0x00006a14  /* FRER 002 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN003_OFFSET     0x00006a1c  /* FRER 003 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN004_OFFSET     0x00006a24  /* FRER 004 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN005_OFFSET     0x00006a2c  /* FRER 005 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN006_OFFSET     0x00006a34  /* FRER 006 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN007_OFFSET     0x00006a3c  /* FRER 007 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN008_OFFSET     0x00006a44  /* FRER 008 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN009_OFFSET     0x00006a4c  /* FRER 009 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN010_OFFSET     0x00006a54  /* FRER 010 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN011_OFFSET     0x00006a5c  /* FRER 011 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN012_OFFSET     0x00006a64  /* FRER 012 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN013_OFFSET     0x00006a6c  /* FRER 013 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN014_OFFSET     0x00006a74  /* FRER 014 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN015_OFFSET     0x00006a7c  /* FRER 015 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN016_OFFSET     0x00006a84  /* FRER 016 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN017_OFFSET     0x00006a8c  /* FRER 017 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN018_OFFSET     0x00006a94  /* FRER 018 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN019_OFFSET     0x00006a9c  /* FRER 019 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN020_OFFSET     0x00006aa4  /* FRER 020 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN021_OFFSET     0x00006aac  /* FRER 021 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN022_OFFSET     0x00006ab4  /* FRER 022 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN023_OFFSET     0x00006abc  /* FRER 023 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN024_OFFSET     0x00006ac4  /* FRER 024 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN025_OFFSET     0x00006acc  /* FRER 025 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN026_OFFSET     0x00006ad4  /* FRER 026 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN027_OFFSET     0x00006adc  /* FRER 027 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN028_OFFSET     0x00006ae4  /* FRER 028 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN029_OFFSET     0x00006aec  /* FRER 029 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN030_OFFSET     0x00006af4  /* FRER 030 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN031_OFFSET     0x00006afc  /* FRER 031 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN032_OFFSET     0x00006b04  /* FRER 032 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN033_OFFSET     0x00006b0c  /* FRER 033 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN034_OFFSET     0x00006b14  /* FRER 034 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN035_OFFSET     0x00006b1c  /* FRER 035 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN036_OFFSET     0x00006b24  /* FRER 036 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN037_OFFSET     0x00006b2c  /* FRER 037 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN038_OFFSET     0x00006b34  /* FRER 038 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN039_OFFSET     0x00006b3c  /* FRER 039 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN040_OFFSET     0x00006b44  /* FRER 040 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN041_OFFSET     0x00006b4c  /* FRER 041 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN042_OFFSET     0x00006b54  /* FRER 042 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN043_OFFSET     0x00006b5c  /* FRER 043 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN044_OFFSET     0x00006b64  /* FRER 044 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN045_OFFSET     0x00006b6c  /* FRER 045 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN046_OFFSET     0x00006b74  /* FRER 046 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN047_OFFSET     0x00006b7c  /* FRER 047 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN048_OFFSET     0x00006b84  /* FRER 048 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN049_OFFSET     0x00006b8c  /* FRER 049 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN050_OFFSET     0x00006b94  /* FRER 050 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN051_OFFSET     0x00006b9c  /* FRER 051 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN052_OFFSET     0x00006ba4  /* FRER 052 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN053_OFFSET     0x00006bac  /* FRER 053 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN054_OFFSET     0x00006bb4  /* FRER 054 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN055_OFFSET     0x00006bbc  /* FRER 055 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN056_OFFSET     0x00006bc4  /* FRER 056 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN057_OFFSET     0x00006bcc  /* FRER 057 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN058_OFFSET     0x00006bd4  /* FRER 058 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN059_OFFSET     0x00006bdc  /* FRER 059 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN060_OFFSET     0x00006be4  /* FRER 060 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN061_OFFSET     0x00006bec  /* FRER 061 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN062_OFFSET     0x00006bf4  /* FRER 062 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN063_OFFSET     0x00006bfc  /* FRER 063 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN064_OFFSET     0x00006c04  /* FRER 064 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN065_OFFSET     0x00006c0c  /* FRER 065 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN066_OFFSET     0x00006c14  /* FRER 066 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN067_OFFSET     0x00006c1c  /* FRER 067 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN068_OFFSET     0x00006c24  /* FRER 068 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN069_OFFSET     0x00006c2c  /* FRER 069 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN070_OFFSET     0x00006c34  /* FRER 070 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN071_OFFSET     0x00006c3c  /* FRER 071 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN072_OFFSET     0x00006c44  /* FRER 072 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN073_OFFSET     0x00006c4c  /* FRER 073 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN074_OFFSET     0x00006c54  /* FRER 074 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN075_OFFSET     0x00006c5c  /* FRER 075 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN076_OFFSET     0x00006c64  /* FRER 076 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN077_OFFSET     0x00006c6c  /* FRER 077 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN078_OFFSET     0x00006c74  /* FRER 078 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN079_OFFSET     0x00006c7c  /* FRER 079 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN080_OFFSET     0x00006c84  /* FRER 080 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN081_OFFSET     0x00006c8c  /* FRER 081 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN082_OFFSET     0x00006c94  /* FRER 082 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN083_OFFSET     0x00006c9c  /* FRER 083 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN084_OFFSET     0x00006ca4  /* FRER 084 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN085_OFFSET     0x00006cac  /* FRER 085 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN086_OFFSET     0x00006cb4  /* FRER 086 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN087_OFFSET     0x00006cbc  /* FRER 087 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN088_OFFSET     0x00006cc4  /* FRER 088 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN089_OFFSET     0x00006ccc  /* FRER 089 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN090_OFFSET     0x00006cd4  /* FRER 090 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN091_OFFSET     0x00006cdc  /* FRER 091 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN092_OFFSET     0x00006ce4  /* FRER 092 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN093_OFFSET     0x00006cec  /* FRER 093 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN094_OFFSET     0x00006cf4  /* FRER 094 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN095_OFFSET     0x00006cfc  /* FRER 095 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN096_OFFSET     0x00006d04  /* FRER 096 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN097_OFFSET     0x00006d0c  /* FRER 097 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN098_OFFSET     0x00006d14  /* FRER 098 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN099_OFFSET     0x00006d1c  /* FRER 099 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN100_OFFSET     0x00006d24  /* FRER 100 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN101_OFFSET     0x00006d2c  /* FRER 101 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN102_OFFSET     0x00006d34  /* FRER 102 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN103_OFFSET     0x00006d3c  /* FRER 103 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN104_OFFSET     0x00006d44  /* FRER 104 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN105_OFFSET     0x00006d4c  /* FRER 105 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN106_OFFSET     0x00006d54  /* FRER 106 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN107_OFFSET     0x00006d5c  /* FRER 107 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN108_OFFSET     0x00006d64  /* FRER 108 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN109_OFFSET     0x00006d6c  /* FRER 109 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN110_OFFSET     0x00006d74  /* FRER 110 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN111_OFFSET     0x00006d7c  /* FRER 111 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN112_OFFSET     0x00006d84  /* FRER 112 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN113_OFFSET     0x00006d8c  /* FRER 113 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN114_OFFSET     0x00006d94  /* FRER 114 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN115_OFFSET     0x00006d9c  /* FRER 115 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN116_OFFSET     0x00006da4  /* FRER 116 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN117_OFFSET     0x00006dac  /* FRER 117 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN118_OFFSET     0x00006db4  /* FRER 118 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN119_OFFSET     0x00006dbc  /* FRER 119 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN120_OFFSET     0x00006dc4  /* FRER 120 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN121_OFFSET     0x00006dcc  /* FRER 121 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN122_OFFSET     0x00006dd4  /* FRER 122 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN123_OFFSET     0x00006ddc  /* FRER 123 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN124_OFFSET     0x00006de4  /* FRER 124 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN125_OFFSET     0x00006dec  /* FRER 125 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN126_OFFSET     0x00006df4  /* FRER 126 Discarded Packet Counter Register */
#define R_MFWD_FWFRDPCN127_OFFSET     0x00006dfc  /* FRER 127 Discarded Packet Counter Register */
/* FWEIS0%s Registers (0-2) */
#define R_MFWD_FWEIS00_OFFSET     0x00007900  /* Port 0 Error Interrupt Status Register 0 */
#define R_MFWD_FWEIS01_OFFSET     0x00007910  /* Port 1 Error Interrupt Status Register 0 */
#define R_MFWD_FWEIS02_OFFSET     0x00007920  /* Port 2 Error Interrupt Status Register 0 */
/* FWEIE0%s Registers (0-2) */
#define R_MFWD_FWEIE00_OFFSET     0x00007904  /* Port 0 Error Interrupt Enable Register 0 */
#define R_MFWD_FWEIE01_OFFSET     0x00007914  /* Port 1 Error Interrupt Enable Register 0 */
#define R_MFWD_FWEIE02_OFFSET     0x00007924  /* Port 2 Error Interrupt Enable Register 0 */
/* FWEID0%s Registers (0-2) */
#define R_MFWD_FWEID00_OFFSET     0x00007908  /* Port 0 Error Interrupt Disable Register 0 */
#define R_MFWD_FWEID01_OFFSET     0x00007918  /* Port 1 Error Interrupt Disable Register 0 */
#define R_MFWD_FWEID02_OFFSET     0x00007928  /* Port 2 Error Interrupt Disable Register 0 */
#define R_MFWD_FWEIS1_OFFSET     0x00007a00  /* Error Interrupt Status Register 1 */
#define R_MFWD_FWEIE1_OFFSET     0x00007a04  /* Error Interrupt Enable Register 1 */
#define R_MFWD_FWEID1_OFFSET     0x00007a08  /* Error Interrupt Disable Register 1 */
#define R_MFWD_FWEIS2_OFFSET     0x00007a10  /* Error Interrupt Status Register 2 */
#define R_MFWD_FWEIE2_OFFSET     0x00007a14  /* Error Interrupt Enable Register 2 */
#define R_MFWD_FWEID2_OFFSET     0x00007a18  /* Error Interrupt Disable Register 2 */
#define R_MFWD_FWEIS5_OFFSET     0x00007a40  /* Error Interrupt Status Register 5 */
#define R_MFWD_FWEIE5_OFFSET     0x00007a44  /* Error Interrupt Enable Register 5 */
#define R_MFWD_FWEID5_OFFSET     0x00007a48  /* Error Interrupt Disable Register 5 */
#define R_MFWD_FWEIS60_OFFSET     0x00007a50  /* Error Interrupt Status Register 60 */
#define R_MFWD_FWEIE60_OFFSET     0x00007a54  /* Error Interrupt Enable Register 60 */
#define R_MFWD_FWEID60_OFFSET     0x00007a58  /* Error Interrupt Disable Register 60 */
#define R_MFWD_FWEIS61_OFFSET     0x00007a60  /* Error Interrupt Status Register 61 */
#define R_MFWD_FWEIE61_OFFSET     0x00007a64  /* Error Interrupt Enable Register 61 */
#define R_MFWD_FWEID61_OFFSET     0x00007a68  /* Error Interrupt Disable Register 61 */
#define R_MFWD_FWEIS62_OFFSET     0x00007a70  /* Error Interrupt Status Register 62 */
#define R_MFWD_FWEIE62_OFFSET     0x00007a74  /* Error Interrupt Enable Register 62 */
#define R_MFWD_FWEID62_OFFSET     0x00007a78  /* Error Interrupt Disable Register 62 */
#define R_MFWD_FWEIS63_OFFSET     0x00007a80  /* Error Interrupt Status Register 63 */
#define R_MFWD_FWEIE63_OFFSET     0x00007a84  /* Error Interrupt Enable Register 63 */
#define R_MFWD_FWEID63_OFFSET     0x00007a88  /* Error Interrupt Disable Register 63 */
#define R_MFWD_FWEIS70_OFFSET     0x00007a90  /* Error Interrupt Status Register 70 */
#define R_MFWD_FWEIE70_OFFSET     0x00007a94  /* Error Interrupt Enable Register 70 */
#define R_MFWD_FWEID70_OFFSET     0x00007a98  /* Error Interrupt Disable Register 70 */
#define R_MFWD_FWEIS71_OFFSET     0x00007aa0  /* Error Interrupt Status Register 71 */
#define R_MFWD_FWEIE71_OFFSET     0x00007aa4  /* Error Interrupt Enable Register 71 */
#define R_MFWD_FWEID71_OFFSET     0x00007aa8  /* Error Interrupt Disable Register 71 */
#define R_MFWD_FWEIS72_OFFSET     0x00007ab0  /* Error Interrupt Status Register 72 */
#define R_MFWD_FWEIE72_OFFSET     0x00007ab4  /* Error Interrupt Enable Register 72 */
#define R_MFWD_FWEID72_OFFSET     0x00007ab8  /* Error Interrupt Disable Register 72 */
#define R_MFWD_FWEIS73_OFFSET     0x00007ac0  /* Error Interrupt Status Register 73 */
#define R_MFWD_FWEIE73_OFFSET     0x00007ac4  /* Error Interrupt Enable Register 73 */
#define R_MFWD_FWEID73_OFFSET     0x00007ac8  /* Forwarding Engine Error Interrupt Disable 73 */
#define R_MFWD_FWEIS80_OFFSET     0x00007ad0  /* Error Interrupt Status Register 80 */
#define R_MFWD_FWEIE80_OFFSET     0x00007ad4  /* Error Interrupt Enable Register 80 */
#define R_MFWD_FWEID80_OFFSET     0x00007ad8  /* Error Interrupt Disable Register 80 */
#define R_MFWD_FWEIS81_OFFSET     0x00007ae0  /* Error Interrupt Status Register 81 */
#define R_MFWD_FWEIE81_OFFSET     0x00007ae4  /* Error Interrupt Enable Register 81 */
#define R_MFWD_FWEID81_OFFSET     0x00007ae8  /* Error Interrupt Disable Register 81 */
#define R_MFWD_FWEIS82_OFFSET     0x00007af0  /* Error Interrupt Status Register 82 */
#define R_MFWD_FWEIE82_OFFSET     0x00007af4  /* Error Interrupt Enable Register 82 */
#define R_MFWD_FWEID82_OFFSET     0x00007af8  /* Error Interrupt Disable Register 82 */
#define R_MFWD_FWEIS83_OFFSET     0x00007b00  /* Error Interrupt Status Register 83 */
#define R_MFWD_FWEIE83_OFFSET     0x00007b04  /* Error Interrupt Enable Register 83 */
#define R_MFWD_FWEID83_OFFSET     0x00007b08  /* Error Interrupt Disable Register 83 */
#define R_MFWD_FWMIS0_OFFSET     0x00007c00  /* Monitoring Interrupt Status Register 0 */
#define R_MFWD_FWMIE0_OFFSET     0x00007c04  /* Monitoring Interrupt Enable Register 0 */
#define R_MFWD_FWMID0_OFFSET     0x00007c08  /* Monitoring Interrupt Disable Register 0 */

/* MFWD Register Addresses */

#define R_MFWD_FWGC                 (R_MFWD_BASE + R_MFWD_FWGC_OFFSET)
#define R_MFWD_FWTTC0                 (R_MFWD_BASE + R_MFWD_FWTTC0_OFFSET)
#define R_MFWD_FWTTC1                 (R_MFWD_BASE + R_MFWD_FWTTC1_OFFSET)
#define R_MFWD_FWCEPTC                 (R_MFWD_BASE + R_MFWD_FWCEPTC_OFFSET)
#define R_MFWD_FWCEPRC0                 (R_MFWD_BASE + R_MFWD_FWCEPRC0_OFFSET)
#define R_MFWD_FWCEPRC1                 (R_MFWD_BASE + R_MFWD_FWCEPRC1_OFFSET)
#define R_MFWD_FWCEPRC2                 (R_MFWD_BASE + R_MFWD_FWCEPRC2_OFFSET)
#define R_MFWD_FWCLPTC                 (R_MFWD_BASE + R_MFWD_FWCLPTC_OFFSET)
#define R_MFWD_FWCLPRC                 (R_MFWD_BASE + R_MFWD_FWCLPRC_OFFSET)
#define R_MFWD_FWCMPTC                 (R_MFWD_BASE + R_MFWD_FWCMPTC_OFFSET)
#define R_MFWD_FWEMPTC                 (R_MFWD_BASE + R_MFWD_FWEMPTC_OFFSET)
#define R_MFWD_FWSDMPTC                 (R_MFWD_BASE + R_MFWD_FWSDMPTC_OFFSET)
#define R_MFWD_FWSDMPVC                 (R_MFWD_BASE + R_MFWD_FWSDMPVC_OFFSET)
#define R_MFWD_FWLBWMC0                 (R_MFWD_BASE + R_MFWD_FWLBWMC0_OFFSET)
#define R_MFWD_FWLBWMC1                 (R_MFWD_BASE + R_MFWD_FWLBWMC1_OFFSET)
#define R_MFWD_FWLBWMC2                 (R_MFWD_BASE + R_MFWD_FWLBWMC2_OFFSET)
#define R_MFWD_FWPC00                 (R_MFWD_BASE + R_MFWD_FWPC00_OFFSET)
#define R_MFWD_FWPC10                 (R_MFWD_BASE + R_MFWD_FWPC10_OFFSET)
#define R_MFWD_FWPC20                 (R_MFWD_BASE + R_MFWD_FWPC20_OFFSET)
#define R_MFWD_FWPC01                 (R_MFWD_BASE + R_MFWD_FWPC01_OFFSET)
#define R_MFWD_FWPC11                 (R_MFWD_BASE + R_MFWD_FWPC11_OFFSET)
#define R_MFWD_FWPC21                 (R_MFWD_BASE + R_MFWD_FWPC21_OFFSET)
#define R_MFWD_FWPC02                 (R_MFWD_BASE + R_MFWD_FWPC02_OFFSET)
#define R_MFWD_FWPC12                 (R_MFWD_BASE + R_MFWD_FWPC12_OFFSET)
#define R_MFWD_FWPC22                 (R_MFWD_BASE + R_MFWD_FWPC22_OFFSET)
#define R_MFWD_FWCTGC00                 (R_MFWD_BASE + R_MFWD_FWCTGC00_OFFSET)
#define R_MFWD_FWCTGC10                 (R_MFWD_BASE + R_MFWD_FWCTGC10_OFFSET)
#define R_MFWD_FWCTGC20                 (R_MFWD_BASE + R_MFWD_FWCTGC20_OFFSET)
#define R_MFWD_FWCTGC30                 (R_MFWD_BASE + R_MFWD_FWCTGC30_OFFSET)
#define R_MFWD_FWCTGC40                 (R_MFWD_BASE + R_MFWD_FWCTGC40_OFFSET)
#define R_MFWD_FWCTGC50                 (R_MFWD_BASE + R_MFWD_FWCTGC50_OFFSET)
#define R_MFWD_FWCTGC60                 (R_MFWD_BASE + R_MFWD_FWCTGC60_OFFSET)
#define R_MFWD_FWCTGC70                 (R_MFWD_BASE + R_MFWD_FWCTGC70_OFFSET)
#define R_MFWD_FWCTGC01                 (R_MFWD_BASE + R_MFWD_FWCTGC01_OFFSET)
#define R_MFWD_FWCTGC11                 (R_MFWD_BASE + R_MFWD_FWCTGC11_OFFSET)
#define R_MFWD_FWCTGC21                 (R_MFWD_BASE + R_MFWD_FWCTGC21_OFFSET)
#define R_MFWD_FWCTGC31                 (R_MFWD_BASE + R_MFWD_FWCTGC31_OFFSET)
#define R_MFWD_FWCTGC41                 (R_MFWD_BASE + R_MFWD_FWCTGC41_OFFSET)
#define R_MFWD_FWCTGC51                 (R_MFWD_BASE + R_MFWD_FWCTGC51_OFFSET)
#define R_MFWD_FWCTGC61                 (R_MFWD_BASE + R_MFWD_FWCTGC61_OFFSET)
#define R_MFWD_FWCTGC71                 (R_MFWD_BASE + R_MFWD_FWCTGC71_OFFSET)
#define R_MFWD_FWCTTC00                 (R_MFWD_BASE + R_MFWD_FWCTTC00_OFFSET)
#define R_MFWD_FWCTTC10                 (R_MFWD_BASE + R_MFWD_FWCTTC10_OFFSET)
#define R_MFWD_FWCTTC20                 (R_MFWD_BASE + R_MFWD_FWCTTC20_OFFSET)
#define R_MFWD_FWCTTC30                 (R_MFWD_BASE + R_MFWD_FWCTTC30_OFFSET)
#define R_MFWD_FWCTTC40                 (R_MFWD_BASE + R_MFWD_FWCTTC40_OFFSET)
#define R_MFWD_FWCTTC50                 (R_MFWD_BASE + R_MFWD_FWCTTC50_OFFSET)
#define R_MFWD_FWCTTC60                 (R_MFWD_BASE + R_MFWD_FWCTTC60_OFFSET)
#define R_MFWD_FWCTTC70                 (R_MFWD_BASE + R_MFWD_FWCTTC70_OFFSET)
#define R_MFWD_FWCTTC01                 (R_MFWD_BASE + R_MFWD_FWCTTC01_OFFSET)
#define R_MFWD_FWCTTC11                 (R_MFWD_BASE + R_MFWD_FWCTTC11_OFFSET)
#define R_MFWD_FWCTTC21                 (R_MFWD_BASE + R_MFWD_FWCTTC21_OFFSET)
#define R_MFWD_FWCTTC31                 (R_MFWD_BASE + R_MFWD_FWCTTC31_OFFSET)
#define R_MFWD_FWCTTC41                 (R_MFWD_BASE + R_MFWD_FWCTTC41_OFFSET)
#define R_MFWD_FWCTTC51                 (R_MFWD_BASE + R_MFWD_FWCTTC51_OFFSET)
#define R_MFWD_FWCTTC61                 (R_MFWD_BASE + R_MFWD_FWCTTC61_OFFSET)
#define R_MFWD_FWCTTC71                 (R_MFWD_BASE + R_MFWD_FWCTTC71_OFFSET)
#define R_MFWD_FWCTTC020                 (R_MFWD_BASE + R_MFWD_FWCTTC020_OFFSET)
#define R_MFWD_FWCTTC120                 (R_MFWD_BASE + R_MFWD_FWCTTC120_OFFSET)
#define R_MFWD_FWCTTC220                 (R_MFWD_BASE + R_MFWD_FWCTTC220_OFFSET)
#define R_MFWD_FWCTTC320                 (R_MFWD_BASE + R_MFWD_FWCTTC320_OFFSET)
#define R_MFWD_FWCTTC420                 (R_MFWD_BASE + R_MFWD_FWCTTC420_OFFSET)
#define R_MFWD_FWCTTC520                 (R_MFWD_BASE + R_MFWD_FWCTTC520_OFFSET)
#define R_MFWD_FWCTTC620                 (R_MFWD_BASE + R_MFWD_FWCTTC620_OFFSET)
#define R_MFWD_FWCTTC720                 (R_MFWD_BASE + R_MFWD_FWCTTC720_OFFSET)
#define R_MFWD_FWCTSC00                 (R_MFWD_BASE + R_MFWD_FWCTSC00_OFFSET)
#define R_MFWD_FWCTSC10                 (R_MFWD_BASE + R_MFWD_FWCTSC10_OFFSET)
#define R_MFWD_FWCTSC20                 (R_MFWD_BASE + R_MFWD_FWCTSC20_OFFSET)
#define R_MFWD_FWCTSC30                 (R_MFWD_BASE + R_MFWD_FWCTSC30_OFFSET)
#define R_MFWD_FWCTSC40                 (R_MFWD_BASE + R_MFWD_FWCTSC40_OFFSET)
#define R_MFWD_FWCTSC50                 (R_MFWD_BASE + R_MFWD_FWCTSC50_OFFSET)
#define R_MFWD_FWCTSC60                 (R_MFWD_BASE + R_MFWD_FWCTSC60_OFFSET)
#define R_MFWD_FWCTSC70                 (R_MFWD_BASE + R_MFWD_FWCTSC70_OFFSET)
#define R_MFWD_FWCTSC01                 (R_MFWD_BASE + R_MFWD_FWCTSC01_OFFSET)
#define R_MFWD_FWCTSC11                 (R_MFWD_BASE + R_MFWD_FWCTSC11_OFFSET)
#define R_MFWD_FWCTSC21                 (R_MFWD_BASE + R_MFWD_FWCTSC21_OFFSET)
#define R_MFWD_FWCTSC31                 (R_MFWD_BASE + R_MFWD_FWCTSC31_OFFSET)
#define R_MFWD_FWCTSC41                 (R_MFWD_BASE + R_MFWD_FWCTSC41_OFFSET)
#define R_MFWD_FWCTSC51                 (R_MFWD_BASE + R_MFWD_FWCTSC51_OFFSET)
#define R_MFWD_FWCTSC61                 (R_MFWD_BASE + R_MFWD_FWCTSC61_OFFSET)
#define R_MFWD_FWCTSC71                 (R_MFWD_BASE + R_MFWD_FWCTSC71_OFFSET)
#define R_MFWD_FWCTSC02                 (R_MFWD_BASE + R_MFWD_FWCTSC02_OFFSET)
#define R_MFWD_FWCTSC12                 (R_MFWD_BASE + R_MFWD_FWCTSC12_OFFSET)
#define R_MFWD_FWCTSC22                 (R_MFWD_BASE + R_MFWD_FWCTSC22_OFFSET)
#define R_MFWD_FWCTSC32                 (R_MFWD_BASE + R_MFWD_FWCTSC32_OFFSET)
#define R_MFWD_FWCTSC42                 (R_MFWD_BASE + R_MFWD_FWCTSC42_OFFSET)
#define R_MFWD_FWCTSC52                 (R_MFWD_BASE + R_MFWD_FWCTSC52_OFFSET)
#define R_MFWD_FWCTSC62                 (R_MFWD_BASE + R_MFWD_FWCTSC62_OFFSET)
#define R_MFWD_FWCTSC72                 (R_MFWD_BASE + R_MFWD_FWCTSC72_OFFSET)
#define R_MFWD_FWCTSC03                 (R_MFWD_BASE + R_MFWD_FWCTSC03_OFFSET)
#define R_MFWD_FWCTSC13                 (R_MFWD_BASE + R_MFWD_FWCTSC13_OFFSET)
#define R_MFWD_FWCTSC23                 (R_MFWD_BASE + R_MFWD_FWCTSC23_OFFSET)
#define R_MFWD_FWCTSC33                 (R_MFWD_BASE + R_MFWD_FWCTSC33_OFFSET)
#define R_MFWD_FWCTSC43                 (R_MFWD_BASE + R_MFWD_FWCTSC43_OFFSET)
#define R_MFWD_FWCTSC53                 (R_MFWD_BASE + R_MFWD_FWCTSC53_OFFSET)
#define R_MFWD_FWCTSC63                 (R_MFWD_BASE + R_MFWD_FWCTSC63_OFFSET)
#define R_MFWD_FWCTSC73                 (R_MFWD_BASE + R_MFWD_FWCTSC73_OFFSET)
#define R_MFWD_FWCTSC04                 (R_MFWD_BASE + R_MFWD_FWCTSC04_OFFSET)
#define R_MFWD_FWCTSC14                 (R_MFWD_BASE + R_MFWD_FWCTSC14_OFFSET)
#define R_MFWD_FWCTSC24                 (R_MFWD_BASE + R_MFWD_FWCTSC24_OFFSET)
#define R_MFWD_FWCTSC34                 (R_MFWD_BASE + R_MFWD_FWCTSC34_OFFSET)
#define R_MFWD_FWCTSC44                 (R_MFWD_BASE + R_MFWD_FWCTSC44_OFFSET)
#define R_MFWD_FWCTSC54                 (R_MFWD_BASE + R_MFWD_FWCTSC54_OFFSET)
#define R_MFWD_FWCTSC64                 (R_MFWD_BASE + R_MFWD_FWCTSC64_OFFSET)
#define R_MFWD_FWCTSC74                 (R_MFWD_BASE + R_MFWD_FWCTSC74_OFFSET)
#define R_MFWD_FWTWBFC00                 (R_MFWD_BASE + R_MFWD_FWTWBFC00_OFFSET)
#define R_MFWD_FWTWBFC01                 (R_MFWD_BASE + R_MFWD_FWTWBFC01_OFFSET)
#define R_MFWD_FWTWBFC02                 (R_MFWD_BASE + R_MFWD_FWTWBFC02_OFFSET)
#define R_MFWD_FWTWBFC03                 (R_MFWD_BASE + R_MFWD_FWTWBFC03_OFFSET)
#define R_MFWD_FWTWBFC04                 (R_MFWD_BASE + R_MFWD_FWTWBFC04_OFFSET)
#define R_MFWD_FWTWBFC05                 (R_MFWD_BASE + R_MFWD_FWTWBFC05_OFFSET)
#define R_MFWD_FWTWBFC06                 (R_MFWD_BASE + R_MFWD_FWTWBFC06_OFFSET)
#define R_MFWD_FWTWBFC07                 (R_MFWD_BASE + R_MFWD_FWTWBFC07_OFFSET)
#define R_MFWD_FWTWBFC08                 (R_MFWD_BASE + R_MFWD_FWTWBFC08_OFFSET)
#define R_MFWD_FWTWBFC09                 (R_MFWD_BASE + R_MFWD_FWTWBFC09_OFFSET)
#define R_MFWD_FWTWBFC10                 (R_MFWD_BASE + R_MFWD_FWTWBFC10_OFFSET)
#define R_MFWD_FWTWBFC11                 (R_MFWD_BASE + R_MFWD_FWTWBFC11_OFFSET)
#define R_MFWD_FWTWBFC12                 (R_MFWD_BASE + R_MFWD_FWTWBFC12_OFFSET)
#define R_MFWD_FWTWBFC13                 (R_MFWD_BASE + R_MFWD_FWTWBFC13_OFFSET)
#define R_MFWD_FWTWBFC14                 (R_MFWD_BASE + R_MFWD_FWTWBFC14_OFFSET)
#define R_MFWD_FWTWBFC15                 (R_MFWD_BASE + R_MFWD_FWTWBFC15_OFFSET)
#define R_MFWD_FWTWBFVC00                 (R_MFWD_BASE + R_MFWD_FWTWBFVC00_OFFSET)
#define R_MFWD_FWTWBFVC01                 (R_MFWD_BASE + R_MFWD_FWTWBFVC01_OFFSET)
#define R_MFWD_FWTWBFVC02                 (R_MFWD_BASE + R_MFWD_FWTWBFVC02_OFFSET)
#define R_MFWD_FWTWBFVC03                 (R_MFWD_BASE + R_MFWD_FWTWBFVC03_OFFSET)
#define R_MFWD_FWTWBFVC04                 (R_MFWD_BASE + R_MFWD_FWTWBFVC04_OFFSET)
#define R_MFWD_FWTWBFVC05                 (R_MFWD_BASE + R_MFWD_FWTWBFVC05_OFFSET)
#define R_MFWD_FWTWBFVC06                 (R_MFWD_BASE + R_MFWD_FWTWBFVC06_OFFSET)
#define R_MFWD_FWTWBFVC07                 (R_MFWD_BASE + R_MFWD_FWTWBFVC07_OFFSET)
#define R_MFWD_FWTWBFVC08                 (R_MFWD_BASE + R_MFWD_FWTWBFVC08_OFFSET)
#define R_MFWD_FWTWBFVC09                 (R_MFWD_BASE + R_MFWD_FWTWBFVC09_OFFSET)
#define R_MFWD_FWTWBFVC10                 (R_MFWD_BASE + R_MFWD_FWTWBFVC10_OFFSET)
#define R_MFWD_FWTWBFVC11                 (R_MFWD_BASE + R_MFWD_FWTWBFVC11_OFFSET)
#define R_MFWD_FWTWBFVC12                 (R_MFWD_BASE + R_MFWD_FWTWBFVC12_OFFSET)
#define R_MFWD_FWTWBFVC13                 (R_MFWD_BASE + R_MFWD_FWTWBFVC13_OFFSET)
#define R_MFWD_FWTWBFVC14                 (R_MFWD_BASE + R_MFWD_FWTWBFVC14_OFFSET)
#define R_MFWD_FWTWBFVC15                 (R_MFWD_BASE + R_MFWD_FWTWBFVC15_OFFSET)
#define R_MFWD_FWTHBFC00                 (R_MFWD_BASE + R_MFWD_FWTHBFC00_OFFSET)
#define R_MFWD_FWTHBFC01                 (R_MFWD_BASE + R_MFWD_FWTHBFC01_OFFSET)
#define R_MFWD_FWTHBFC02                 (R_MFWD_BASE + R_MFWD_FWTHBFC02_OFFSET)
#define R_MFWD_FWTHBFC03                 (R_MFWD_BASE + R_MFWD_FWTHBFC03_OFFSET)
#define R_MFWD_FWTHBFC04                 (R_MFWD_BASE + R_MFWD_FWTHBFC04_OFFSET)
#define R_MFWD_FWTHBFC05                 (R_MFWD_BASE + R_MFWD_FWTHBFC05_OFFSET)
#define R_MFWD_FWTHBFC06                 (R_MFWD_BASE + R_MFWD_FWTHBFC06_OFFSET)
#define R_MFWD_FWTHBFC07                 (R_MFWD_BASE + R_MFWD_FWTHBFC07_OFFSET)
#define R_MFWD_FWTHBFC08                 (R_MFWD_BASE + R_MFWD_FWTHBFC08_OFFSET)
#define R_MFWD_FWTHBFC09                 (R_MFWD_BASE + R_MFWD_FWTHBFC09_OFFSET)
#define R_MFWD_FWTHBFC10                 (R_MFWD_BASE + R_MFWD_FWTHBFC10_OFFSET)
#define R_MFWD_FWTHBFC11                 (R_MFWD_BASE + R_MFWD_FWTHBFC11_OFFSET)
#define R_MFWD_FWTHBFC12                 (R_MFWD_BASE + R_MFWD_FWTHBFC12_OFFSET)
#define R_MFWD_FWTHBFC13                 (R_MFWD_BASE + R_MFWD_FWTHBFC13_OFFSET)
#define R_MFWD_FWTHBFC14                 (R_MFWD_BASE + R_MFWD_FWTHBFC14_OFFSET)
#define R_MFWD_FWTHBFC15                 (R_MFWD_BASE + R_MFWD_FWTHBFC15_OFFSET)
#define R_MFWD_FWTHBFV0C00                 (R_MFWD_BASE + R_MFWD_FWTHBFV0C00_OFFSET)
#define R_MFWD_FWTHBFV0C01                 (R_MFWD_BASE + R_MFWD_FWTHBFV0C01_OFFSET)
#define R_MFWD_FWTHBFV0C02                 (R_MFWD_BASE + R_MFWD_FWTHBFV0C02_OFFSET)
#define R_MFWD_FWTHBFV0C03                 (R_MFWD_BASE + R_MFWD_FWTHBFV0C03_OFFSET)
#define R_MFWD_FWTHBFV0C04                 (R_MFWD_BASE + R_MFWD_FWTHBFV0C04_OFFSET)
#define R_MFWD_FWTHBFV0C05                 (R_MFWD_BASE + R_MFWD_FWTHBFV0C05_OFFSET)
#define R_MFWD_FWTHBFV0C06                 (R_MFWD_BASE + R_MFWD_FWTHBFV0C06_OFFSET)
#define R_MFWD_FWTHBFV0C07                 (R_MFWD_BASE + R_MFWD_FWTHBFV0C07_OFFSET)
#define R_MFWD_FWTHBFV0C08                 (R_MFWD_BASE + R_MFWD_FWTHBFV0C08_OFFSET)
#define R_MFWD_FWTHBFV0C09                 (R_MFWD_BASE + R_MFWD_FWTHBFV0C09_OFFSET)
#define R_MFWD_FWTHBFV0C10                 (R_MFWD_BASE + R_MFWD_FWTHBFV0C10_OFFSET)
#define R_MFWD_FWTHBFV0C11                 (R_MFWD_BASE + R_MFWD_FWTHBFV0C11_OFFSET)
#define R_MFWD_FWTHBFV0C12                 (R_MFWD_BASE + R_MFWD_FWTHBFV0C12_OFFSET)
#define R_MFWD_FWTHBFV0C13                 (R_MFWD_BASE + R_MFWD_FWTHBFV0C13_OFFSET)
#define R_MFWD_FWTHBFV0C14                 (R_MFWD_BASE + R_MFWD_FWTHBFV0C14_OFFSET)
#define R_MFWD_FWTHBFV0C15                 (R_MFWD_BASE + R_MFWD_FWTHBFV0C15_OFFSET)
#define R_MFWD_FWTHBFV1C00                 (R_MFWD_BASE + R_MFWD_FWTHBFV1C00_OFFSET)
#define R_MFWD_FWTHBFV1C01                 (R_MFWD_BASE + R_MFWD_FWTHBFV1C01_OFFSET)
#define R_MFWD_FWTHBFV1C02                 (R_MFWD_BASE + R_MFWD_FWTHBFV1C02_OFFSET)
#define R_MFWD_FWTHBFV1C03                 (R_MFWD_BASE + R_MFWD_FWTHBFV1C03_OFFSET)
#define R_MFWD_FWTHBFV1C04                 (R_MFWD_BASE + R_MFWD_FWTHBFV1C04_OFFSET)
#define R_MFWD_FWTHBFV1C05                 (R_MFWD_BASE + R_MFWD_FWTHBFV1C05_OFFSET)
#define R_MFWD_FWTHBFV1C06                 (R_MFWD_BASE + R_MFWD_FWTHBFV1C06_OFFSET)
#define R_MFWD_FWTHBFV1C07                 (R_MFWD_BASE + R_MFWD_FWTHBFV1C07_OFFSET)
#define R_MFWD_FWTHBFV1C08                 (R_MFWD_BASE + R_MFWD_FWTHBFV1C08_OFFSET)
#define R_MFWD_FWTHBFV1C09                 (R_MFWD_BASE + R_MFWD_FWTHBFV1C09_OFFSET)
#define R_MFWD_FWTHBFV1C10                 (R_MFWD_BASE + R_MFWD_FWTHBFV1C10_OFFSET)
#define R_MFWD_FWTHBFV1C11                 (R_MFWD_BASE + R_MFWD_FWTHBFV1C11_OFFSET)
#define R_MFWD_FWTHBFV1C12                 (R_MFWD_BASE + R_MFWD_FWTHBFV1C12_OFFSET)
#define R_MFWD_FWTHBFV1C13                 (R_MFWD_BASE + R_MFWD_FWTHBFV1C13_OFFSET)
#define R_MFWD_FWTHBFV1C14                 (R_MFWD_BASE + R_MFWD_FWTHBFV1C14_OFFSET)
#define R_MFWD_FWTHBFV1C15                 (R_MFWD_BASE + R_MFWD_FWTHBFV1C15_OFFSET)
#define R_MFWD_FWFOBFC00                 (R_MFWD_BASE + R_MFWD_FWFOBFC00_OFFSET)
#define R_MFWD_FWFOBFC01                 (R_MFWD_BASE + R_MFWD_FWFOBFC01_OFFSET)
#define R_MFWD_FWFOBFC02                 (R_MFWD_BASE + R_MFWD_FWFOBFC02_OFFSET)
#define R_MFWD_FWFOBFC03                 (R_MFWD_BASE + R_MFWD_FWFOBFC03_OFFSET)
#define R_MFWD_FWFOBFC04                 (R_MFWD_BASE + R_MFWD_FWFOBFC04_OFFSET)
#define R_MFWD_FWFOBFC05                 (R_MFWD_BASE + R_MFWD_FWFOBFC05_OFFSET)
#define R_MFWD_FWFOBFC06                 (R_MFWD_BASE + R_MFWD_FWFOBFC06_OFFSET)
#define R_MFWD_FWFOBFC07                 (R_MFWD_BASE + R_MFWD_FWFOBFC07_OFFSET)
#define R_MFWD_FWFOBFC08                 (R_MFWD_BASE + R_MFWD_FWFOBFC08_OFFSET)
#define R_MFWD_FWFOBFC09                 (R_MFWD_BASE + R_MFWD_FWFOBFC09_OFFSET)
#define R_MFWD_FWFOBFC10                 (R_MFWD_BASE + R_MFWD_FWFOBFC10_OFFSET)
#define R_MFWD_FWFOBFC11                 (R_MFWD_BASE + R_MFWD_FWFOBFC11_OFFSET)
#define R_MFWD_FWFOBFC12                 (R_MFWD_BASE + R_MFWD_FWFOBFC12_OFFSET)
#define R_MFWD_FWFOBFC13                 (R_MFWD_BASE + R_MFWD_FWFOBFC13_OFFSET)
#define R_MFWD_FWFOBFC14                 (R_MFWD_BASE + R_MFWD_FWFOBFC14_OFFSET)
#define R_MFWD_FWFOBFC15                 (R_MFWD_BASE + R_MFWD_FWFOBFC15_OFFSET)
#define R_MFWD_FWFOBFV0C00                 (R_MFWD_BASE + R_MFWD_FWFOBFV0C00_OFFSET)
#define R_MFWD_FWFOBFV0C01                 (R_MFWD_BASE + R_MFWD_FWFOBFV0C01_OFFSET)
#define R_MFWD_FWFOBFV0C02                 (R_MFWD_BASE + R_MFWD_FWFOBFV0C02_OFFSET)
#define R_MFWD_FWFOBFV0C03                 (R_MFWD_BASE + R_MFWD_FWFOBFV0C03_OFFSET)
#define R_MFWD_FWFOBFV0C04                 (R_MFWD_BASE + R_MFWD_FWFOBFV0C04_OFFSET)
#define R_MFWD_FWFOBFV0C05                 (R_MFWD_BASE + R_MFWD_FWFOBFV0C05_OFFSET)
#define R_MFWD_FWFOBFV0C06                 (R_MFWD_BASE + R_MFWD_FWFOBFV0C06_OFFSET)
#define R_MFWD_FWFOBFV0C07                 (R_MFWD_BASE + R_MFWD_FWFOBFV0C07_OFFSET)
#define R_MFWD_FWFOBFV0C08                 (R_MFWD_BASE + R_MFWD_FWFOBFV0C08_OFFSET)
#define R_MFWD_FWFOBFV0C09                 (R_MFWD_BASE + R_MFWD_FWFOBFV0C09_OFFSET)
#define R_MFWD_FWFOBFV0C10                 (R_MFWD_BASE + R_MFWD_FWFOBFV0C10_OFFSET)
#define R_MFWD_FWFOBFV0C11                 (R_MFWD_BASE + R_MFWD_FWFOBFV0C11_OFFSET)
#define R_MFWD_FWFOBFV0C12                 (R_MFWD_BASE + R_MFWD_FWFOBFV0C12_OFFSET)
#define R_MFWD_FWFOBFV0C13                 (R_MFWD_BASE + R_MFWD_FWFOBFV0C13_OFFSET)
#define R_MFWD_FWFOBFV0C14                 (R_MFWD_BASE + R_MFWD_FWFOBFV0C14_OFFSET)
#define R_MFWD_FWFOBFV0C15                 (R_MFWD_BASE + R_MFWD_FWFOBFV0C15_OFFSET)
#define R_MFWD_FWFOBFV1C00                 (R_MFWD_BASE + R_MFWD_FWFOBFV1C00_OFFSET)
#define R_MFWD_FWFOBFV1C01                 (R_MFWD_BASE + R_MFWD_FWFOBFV1C01_OFFSET)
#define R_MFWD_FWFOBFV1C02                 (R_MFWD_BASE + R_MFWD_FWFOBFV1C02_OFFSET)
#define R_MFWD_FWFOBFV1C03                 (R_MFWD_BASE + R_MFWD_FWFOBFV1C03_OFFSET)
#define R_MFWD_FWFOBFV1C04                 (R_MFWD_BASE + R_MFWD_FWFOBFV1C04_OFFSET)
#define R_MFWD_FWFOBFV1C05                 (R_MFWD_BASE + R_MFWD_FWFOBFV1C05_OFFSET)
#define R_MFWD_FWFOBFV1C06                 (R_MFWD_BASE + R_MFWD_FWFOBFV1C06_OFFSET)
#define R_MFWD_FWFOBFV1C07                 (R_MFWD_BASE + R_MFWD_FWFOBFV1C07_OFFSET)
#define R_MFWD_FWFOBFV1C08                 (R_MFWD_BASE + R_MFWD_FWFOBFV1C08_OFFSET)
#define R_MFWD_FWFOBFV1C09                 (R_MFWD_BASE + R_MFWD_FWFOBFV1C09_OFFSET)
#define R_MFWD_FWFOBFV1C10                 (R_MFWD_BASE + R_MFWD_FWFOBFV1C10_OFFSET)
#define R_MFWD_FWFOBFV1C11                 (R_MFWD_BASE + R_MFWD_FWFOBFV1C11_OFFSET)
#define R_MFWD_FWFOBFV1C12                 (R_MFWD_BASE + R_MFWD_FWFOBFV1C12_OFFSET)
#define R_MFWD_FWFOBFV1C13                 (R_MFWD_BASE + R_MFWD_FWFOBFV1C13_OFFSET)
#define R_MFWD_FWFOBFV1C14                 (R_MFWD_BASE + R_MFWD_FWFOBFV1C14_OFFSET)
#define R_MFWD_FWFOBFV1C15                 (R_MFWD_BASE + R_MFWD_FWFOBFV1C15_OFFSET)
#define R_MFWD_FWRFC00                 (R_MFWD_BASE + R_MFWD_FWRFC00_OFFSET)
#define R_MFWD_FWRFC01                 (R_MFWD_BASE + R_MFWD_FWRFC01_OFFSET)
#define R_MFWD_FWRFC02                 (R_MFWD_BASE + R_MFWD_FWRFC02_OFFSET)
#define R_MFWD_FWRFC03                 (R_MFWD_BASE + R_MFWD_FWRFC03_OFFSET)
#define R_MFWD_FWRFC04                 (R_MFWD_BASE + R_MFWD_FWRFC04_OFFSET)
#define R_MFWD_FWRFC05                 (R_MFWD_BASE + R_MFWD_FWRFC05_OFFSET)
#define R_MFWD_FWRFC06                 (R_MFWD_BASE + R_MFWD_FWRFC06_OFFSET)
#define R_MFWD_FWRFC07                 (R_MFWD_BASE + R_MFWD_FWRFC07_OFFSET)
#define R_MFWD_FWRFC08                 (R_MFWD_BASE + R_MFWD_FWRFC08_OFFSET)
#define R_MFWD_FWRFC09                 (R_MFWD_BASE + R_MFWD_FWRFC09_OFFSET)
#define R_MFWD_FWRFC10                 (R_MFWD_BASE + R_MFWD_FWRFC10_OFFSET)
#define R_MFWD_FWRFC11                 (R_MFWD_BASE + R_MFWD_FWRFC11_OFFSET)
#define R_MFWD_FWRFC12                 (R_MFWD_BASE + R_MFWD_FWRFC12_OFFSET)
#define R_MFWD_FWRFC13                 (R_MFWD_BASE + R_MFWD_FWRFC13_OFFSET)
#define R_MFWD_FWRFC14                 (R_MFWD_BASE + R_MFWD_FWRFC14_OFFSET)
#define R_MFWD_FWRFC15                 (R_MFWD_BASE + R_MFWD_FWRFC15_OFFSET)
#define R_MFWD_FWRFVC00                 (R_MFWD_BASE + R_MFWD_FWRFVC00_OFFSET)
#define R_MFWD_FWRFVC01                 (R_MFWD_BASE + R_MFWD_FWRFVC01_OFFSET)
#define R_MFWD_FWRFVC02                 (R_MFWD_BASE + R_MFWD_FWRFVC02_OFFSET)
#define R_MFWD_FWRFVC03                 (R_MFWD_BASE + R_MFWD_FWRFVC03_OFFSET)
#define R_MFWD_FWRFVC04                 (R_MFWD_BASE + R_MFWD_FWRFVC04_OFFSET)
#define R_MFWD_FWRFVC05                 (R_MFWD_BASE + R_MFWD_FWRFVC05_OFFSET)
#define R_MFWD_FWRFVC06                 (R_MFWD_BASE + R_MFWD_FWRFVC06_OFFSET)
#define R_MFWD_FWRFVC07                 (R_MFWD_BASE + R_MFWD_FWRFVC07_OFFSET)
#define R_MFWD_FWRFVC08                 (R_MFWD_BASE + R_MFWD_FWRFVC08_OFFSET)
#define R_MFWD_FWRFVC09                 (R_MFWD_BASE + R_MFWD_FWRFVC09_OFFSET)
#define R_MFWD_FWRFVC10                 (R_MFWD_BASE + R_MFWD_FWRFVC10_OFFSET)
#define R_MFWD_FWRFVC11                 (R_MFWD_BASE + R_MFWD_FWRFVC11_OFFSET)
#define R_MFWD_FWRFVC12                 (R_MFWD_BASE + R_MFWD_FWRFVC12_OFFSET)
#define R_MFWD_FWRFVC13                 (R_MFWD_BASE + R_MFWD_FWRFVC13_OFFSET)
#define R_MFWD_FWRFVC14                 (R_MFWD_BASE + R_MFWD_FWRFVC14_OFFSET)
#define R_MFWD_FWRFVC15                 (R_MFWD_BASE + R_MFWD_FWRFVC15_OFFSET)
#define R_MFWD_FWCFC00                 (R_MFWD_BASE + R_MFWD_FWCFC00_OFFSET)
#define R_MFWD_FWCFC01                 (R_MFWD_BASE + R_MFWD_FWCFC01_OFFSET)
#define R_MFWD_FWCFC02                 (R_MFWD_BASE + R_MFWD_FWCFC02_OFFSET)
#define R_MFWD_FWCFC03                 (R_MFWD_BASE + R_MFWD_FWCFC03_OFFSET)
#define R_MFWD_FWCFC04                 (R_MFWD_BASE + R_MFWD_FWCFC04_OFFSET)
#define R_MFWD_FWCFC05                 (R_MFWD_BASE + R_MFWD_FWCFC05_OFFSET)
#define R_MFWD_FWCFC06                 (R_MFWD_BASE + R_MFWD_FWCFC06_OFFSET)
#define R_MFWD_FWCFC07                 (R_MFWD_BASE + R_MFWD_FWCFC07_OFFSET)
#define R_MFWD_FWCFC08                 (R_MFWD_BASE + R_MFWD_FWCFC08_OFFSET)
#define R_MFWD_FWCFC09                 (R_MFWD_BASE + R_MFWD_FWCFC09_OFFSET)
#define R_MFWD_FWCFC10                 (R_MFWD_BASE + R_MFWD_FWCFC10_OFFSET)
#define R_MFWD_FWCFC11                 (R_MFWD_BASE + R_MFWD_FWCFC11_OFFSET)
#define R_MFWD_FWCFC12                 (R_MFWD_BASE + R_MFWD_FWCFC12_OFFSET)
#define R_MFWD_FWCFC13                 (R_MFWD_BASE + R_MFWD_FWCFC13_OFFSET)
#define R_MFWD_FWCFC14                 (R_MFWD_BASE + R_MFWD_FWCFC14_OFFSET)
#define R_MFWD_FWCFC15                 (R_MFWD_BASE + R_MFWD_FWCFC15_OFFSET)
#define R_MFWD_FWCFMC000                 (R_MFWD_BASE + R_MFWD_FWCFMC000_OFFSET)
#define R_MFWD_FWCFMC010                 (R_MFWD_BASE + R_MFWD_FWCFMC010_OFFSET)
#define R_MFWD_FWCFMC020                 (R_MFWD_BASE + R_MFWD_FWCFMC020_OFFSET)
#define R_MFWD_FWCFMC030                 (R_MFWD_BASE + R_MFWD_FWCFMC030_OFFSET)
#define R_MFWD_FWCFMC040                 (R_MFWD_BASE + R_MFWD_FWCFMC040_OFFSET)
#define R_MFWD_FWCFMC050                 (R_MFWD_BASE + R_MFWD_FWCFMC050_OFFSET)
#define R_MFWD_FWCFMC060                 (R_MFWD_BASE + R_MFWD_FWCFMC060_OFFSET)
#define R_MFWD_FWCFMC070                 (R_MFWD_BASE + R_MFWD_FWCFMC070_OFFSET)
#define R_MFWD_FWCFMC080                 (R_MFWD_BASE + R_MFWD_FWCFMC080_OFFSET)
#define R_MFWD_FWCFMC090                 (R_MFWD_BASE + R_MFWD_FWCFMC090_OFFSET)
#define R_MFWD_FWCFMC100                 (R_MFWD_BASE + R_MFWD_FWCFMC100_OFFSET)
#define R_MFWD_FWCFMC110                 (R_MFWD_BASE + R_MFWD_FWCFMC110_OFFSET)
#define R_MFWD_FWCFMC120                 (R_MFWD_BASE + R_MFWD_FWCFMC120_OFFSET)
#define R_MFWD_FWCFMC130                 (R_MFWD_BASE + R_MFWD_FWCFMC130_OFFSET)
#define R_MFWD_FWCFMC140                 (R_MFWD_BASE + R_MFWD_FWCFMC140_OFFSET)
#define R_MFWD_FWCFMC150                 (R_MFWD_BASE + R_MFWD_FWCFMC150_OFFSET)
#define R_MFWD_FWCFMC001                 (R_MFWD_BASE + R_MFWD_FWCFMC001_OFFSET)
#define R_MFWD_FWCFMC011                 (R_MFWD_BASE + R_MFWD_FWCFMC011_OFFSET)
#define R_MFWD_FWCFMC021                 (R_MFWD_BASE + R_MFWD_FWCFMC021_OFFSET)
#define R_MFWD_FWCFMC031                 (R_MFWD_BASE + R_MFWD_FWCFMC031_OFFSET)
#define R_MFWD_FWCFMC041                 (R_MFWD_BASE + R_MFWD_FWCFMC041_OFFSET)
#define R_MFWD_FWCFMC051                 (R_MFWD_BASE + R_MFWD_FWCFMC051_OFFSET)
#define R_MFWD_FWCFMC061                 (R_MFWD_BASE + R_MFWD_FWCFMC061_OFFSET)
#define R_MFWD_FWCFMC071                 (R_MFWD_BASE + R_MFWD_FWCFMC071_OFFSET)
#define R_MFWD_FWCFMC081                 (R_MFWD_BASE + R_MFWD_FWCFMC081_OFFSET)
#define R_MFWD_FWCFMC091                 (R_MFWD_BASE + R_MFWD_FWCFMC091_OFFSET)
#define R_MFWD_FWCFMC101                 (R_MFWD_BASE + R_MFWD_FWCFMC101_OFFSET)
#define R_MFWD_FWCFMC111                 (R_MFWD_BASE + R_MFWD_FWCFMC111_OFFSET)
#define R_MFWD_FWCFMC121                 (R_MFWD_BASE + R_MFWD_FWCFMC121_OFFSET)
#define R_MFWD_FWCFMC131                 (R_MFWD_BASE + R_MFWD_FWCFMC131_OFFSET)
#define R_MFWD_FWCFMC141                 (R_MFWD_BASE + R_MFWD_FWCFMC141_OFFSET)
#define R_MFWD_FWCFMC151                 (R_MFWD_BASE + R_MFWD_FWCFMC151_OFFSET)
#define R_MFWD_FWCFMC002                 (R_MFWD_BASE + R_MFWD_FWCFMC002_OFFSET)
#define R_MFWD_FWCFMC012                 (R_MFWD_BASE + R_MFWD_FWCFMC012_OFFSET)
#define R_MFWD_FWCFMC022                 (R_MFWD_BASE + R_MFWD_FWCFMC022_OFFSET)
#define R_MFWD_FWCFMC032                 (R_MFWD_BASE + R_MFWD_FWCFMC032_OFFSET)
#define R_MFWD_FWCFMC042                 (R_MFWD_BASE + R_MFWD_FWCFMC042_OFFSET)
#define R_MFWD_FWCFMC052                 (R_MFWD_BASE + R_MFWD_FWCFMC052_OFFSET)
#define R_MFWD_FWCFMC062                 (R_MFWD_BASE + R_MFWD_FWCFMC062_OFFSET)
#define R_MFWD_FWCFMC072                 (R_MFWD_BASE + R_MFWD_FWCFMC072_OFFSET)
#define R_MFWD_FWCFMC082                 (R_MFWD_BASE + R_MFWD_FWCFMC082_OFFSET)
#define R_MFWD_FWCFMC092                 (R_MFWD_BASE + R_MFWD_FWCFMC092_OFFSET)
#define R_MFWD_FWCFMC102                 (R_MFWD_BASE + R_MFWD_FWCFMC102_OFFSET)
#define R_MFWD_FWCFMC112                 (R_MFWD_BASE + R_MFWD_FWCFMC112_OFFSET)
#define R_MFWD_FWCFMC122                 (R_MFWD_BASE + R_MFWD_FWCFMC122_OFFSET)
#define R_MFWD_FWCFMC132                 (R_MFWD_BASE + R_MFWD_FWCFMC132_OFFSET)
#define R_MFWD_FWCFMC142                 (R_MFWD_BASE + R_MFWD_FWCFMC142_OFFSET)
#define R_MFWD_FWCFMC152                 (R_MFWD_BASE + R_MFWD_FWCFMC152_OFFSET)
#define R_MFWD_FWCFMC003                 (R_MFWD_BASE + R_MFWD_FWCFMC003_OFFSET)
#define R_MFWD_FWCFMC013                 (R_MFWD_BASE + R_MFWD_FWCFMC013_OFFSET)
#define R_MFWD_FWCFMC023                 (R_MFWD_BASE + R_MFWD_FWCFMC023_OFFSET)
#define R_MFWD_FWCFMC033                 (R_MFWD_BASE + R_MFWD_FWCFMC033_OFFSET)
#define R_MFWD_FWCFMC043                 (R_MFWD_BASE + R_MFWD_FWCFMC043_OFFSET)
#define R_MFWD_FWCFMC053                 (R_MFWD_BASE + R_MFWD_FWCFMC053_OFFSET)
#define R_MFWD_FWCFMC063                 (R_MFWD_BASE + R_MFWD_FWCFMC063_OFFSET)
#define R_MFWD_FWCFMC073                 (R_MFWD_BASE + R_MFWD_FWCFMC073_OFFSET)
#define R_MFWD_FWCFMC083                 (R_MFWD_BASE + R_MFWD_FWCFMC083_OFFSET)
#define R_MFWD_FWCFMC093                 (R_MFWD_BASE + R_MFWD_FWCFMC093_OFFSET)
#define R_MFWD_FWCFMC103                 (R_MFWD_BASE + R_MFWD_FWCFMC103_OFFSET)
#define R_MFWD_FWCFMC113                 (R_MFWD_BASE + R_MFWD_FWCFMC113_OFFSET)
#define R_MFWD_FWCFMC123                 (R_MFWD_BASE + R_MFWD_FWCFMC123_OFFSET)
#define R_MFWD_FWCFMC133                 (R_MFWD_BASE + R_MFWD_FWCFMC133_OFFSET)
#define R_MFWD_FWCFMC143                 (R_MFWD_BASE + R_MFWD_FWCFMC143_OFFSET)
#define R_MFWD_FWCFMC153                 (R_MFWD_BASE + R_MFWD_FWCFMC153_OFFSET)
#define R_MFWD_FWCFMC004                 (R_MFWD_BASE + R_MFWD_FWCFMC004_OFFSET)
#define R_MFWD_FWCFMC014                 (R_MFWD_BASE + R_MFWD_FWCFMC014_OFFSET)
#define R_MFWD_FWCFMC024                 (R_MFWD_BASE + R_MFWD_FWCFMC024_OFFSET)
#define R_MFWD_FWCFMC034                 (R_MFWD_BASE + R_MFWD_FWCFMC034_OFFSET)
#define R_MFWD_FWCFMC044                 (R_MFWD_BASE + R_MFWD_FWCFMC044_OFFSET)
#define R_MFWD_FWCFMC054                 (R_MFWD_BASE + R_MFWD_FWCFMC054_OFFSET)
#define R_MFWD_FWCFMC064                 (R_MFWD_BASE + R_MFWD_FWCFMC064_OFFSET)
#define R_MFWD_FWCFMC074                 (R_MFWD_BASE + R_MFWD_FWCFMC074_OFFSET)
#define R_MFWD_FWCFMC084                 (R_MFWD_BASE + R_MFWD_FWCFMC084_OFFSET)
#define R_MFWD_FWCFMC094                 (R_MFWD_BASE + R_MFWD_FWCFMC094_OFFSET)
#define R_MFWD_FWCFMC104                 (R_MFWD_BASE + R_MFWD_FWCFMC104_OFFSET)
#define R_MFWD_FWCFMC114                 (R_MFWD_BASE + R_MFWD_FWCFMC114_OFFSET)
#define R_MFWD_FWCFMC124                 (R_MFWD_BASE + R_MFWD_FWCFMC124_OFFSET)
#define R_MFWD_FWCFMC134                 (R_MFWD_BASE + R_MFWD_FWCFMC134_OFFSET)
#define R_MFWD_FWCFMC144                 (R_MFWD_BASE + R_MFWD_FWCFMC144_OFFSET)
#define R_MFWD_FWCFMC154                 (R_MFWD_BASE + R_MFWD_FWCFMC154_OFFSET)
#define R_MFWD_FWCFMC005                 (R_MFWD_BASE + R_MFWD_FWCFMC005_OFFSET)
#define R_MFWD_FWCFMC015                 (R_MFWD_BASE + R_MFWD_FWCFMC015_OFFSET)
#define R_MFWD_FWCFMC025                 (R_MFWD_BASE + R_MFWD_FWCFMC025_OFFSET)
#define R_MFWD_FWCFMC035                 (R_MFWD_BASE + R_MFWD_FWCFMC035_OFFSET)
#define R_MFWD_FWCFMC045                 (R_MFWD_BASE + R_MFWD_FWCFMC045_OFFSET)
#define R_MFWD_FWCFMC055                 (R_MFWD_BASE + R_MFWD_FWCFMC055_OFFSET)
#define R_MFWD_FWCFMC065                 (R_MFWD_BASE + R_MFWD_FWCFMC065_OFFSET)
#define R_MFWD_FWCFMC075                 (R_MFWD_BASE + R_MFWD_FWCFMC075_OFFSET)
#define R_MFWD_FWCFMC085                 (R_MFWD_BASE + R_MFWD_FWCFMC085_OFFSET)
#define R_MFWD_FWCFMC095                 (R_MFWD_BASE + R_MFWD_FWCFMC095_OFFSET)
#define R_MFWD_FWCFMC105                 (R_MFWD_BASE + R_MFWD_FWCFMC105_OFFSET)
#define R_MFWD_FWCFMC115                 (R_MFWD_BASE + R_MFWD_FWCFMC115_OFFSET)
#define R_MFWD_FWCFMC125                 (R_MFWD_BASE + R_MFWD_FWCFMC125_OFFSET)
#define R_MFWD_FWCFMC135                 (R_MFWD_BASE + R_MFWD_FWCFMC135_OFFSET)
#define R_MFWD_FWCFMC145                 (R_MFWD_BASE + R_MFWD_FWCFMC145_OFFSET)
#define R_MFWD_FWCFMC155                 (R_MFWD_BASE + R_MFWD_FWCFMC155_OFFSET)
#define R_MFWD_FWCFMC006                 (R_MFWD_BASE + R_MFWD_FWCFMC006_OFFSET)
#define R_MFWD_FWCFMC016                 (R_MFWD_BASE + R_MFWD_FWCFMC016_OFFSET)
#define R_MFWD_FWCFMC026                 (R_MFWD_BASE + R_MFWD_FWCFMC026_OFFSET)
#define R_MFWD_FWCFMC036                 (R_MFWD_BASE + R_MFWD_FWCFMC036_OFFSET)
#define R_MFWD_FWCFMC046                 (R_MFWD_BASE + R_MFWD_FWCFMC046_OFFSET)
#define R_MFWD_FWCFMC056                 (R_MFWD_BASE + R_MFWD_FWCFMC056_OFFSET)
#define R_MFWD_FWCFMC066                 (R_MFWD_BASE + R_MFWD_FWCFMC066_OFFSET)
#define R_MFWD_FWCFMC076                 (R_MFWD_BASE + R_MFWD_FWCFMC076_OFFSET)
#define R_MFWD_FWCFMC086                 (R_MFWD_BASE + R_MFWD_FWCFMC086_OFFSET)
#define R_MFWD_FWCFMC096                 (R_MFWD_BASE + R_MFWD_FWCFMC096_OFFSET)
#define R_MFWD_FWCFMC106                 (R_MFWD_BASE + R_MFWD_FWCFMC106_OFFSET)
#define R_MFWD_FWCFMC116                 (R_MFWD_BASE + R_MFWD_FWCFMC116_OFFSET)
#define R_MFWD_FWCFMC126                 (R_MFWD_BASE + R_MFWD_FWCFMC126_OFFSET)
#define R_MFWD_FWCFMC136                 (R_MFWD_BASE + R_MFWD_FWCFMC136_OFFSET)
#define R_MFWD_FWCFMC146                 (R_MFWD_BASE + R_MFWD_FWCFMC146_OFFSET)
#define R_MFWD_FWCFMC156                 (R_MFWD_BASE + R_MFWD_FWCFMC156_OFFSET)
#define R_MFWD_FWIP4SC                 (R_MFWD_BASE + R_MFWD_FWIP4SC_OFFSET)
#define R_MFWD_FWIP6SC                 (R_MFWD_BASE + R_MFWD_FWIP6SC_OFFSET)
#define R_MFWD_FWIP6OC                 (R_MFWD_BASE + R_MFWD_FWIP6OC_OFFSET)
#define R_MFWD_FWL2SC                 (R_MFWD_BASE + R_MFWD_FWL2SC_OFFSET)
#define R_MFWD_FWSFHEC                 (R_MFWD_BASE + R_MFWD_FWSFHEC_OFFSET)
#define R_MFWD_FWSHCR0                 (R_MFWD_BASE + R_MFWD_FWSHCR0_OFFSET)
#define R_MFWD_FWSHCR1                 (R_MFWD_BASE + R_MFWD_FWSHCR1_OFFSET)
#define R_MFWD_FWSHCR2                 (R_MFWD_BASE + R_MFWD_FWSHCR2_OFFSET)
#define R_MFWD_FWSHCR3                 (R_MFWD_BASE + R_MFWD_FWSHCR3_OFFSET)
#define R_MFWD_FWSHCR4                 (R_MFWD_BASE + R_MFWD_FWSHCR4_OFFSET)
#define R_MFWD_FWSHCR5                 (R_MFWD_BASE + R_MFWD_FWSHCR5_OFFSET)
#define R_MFWD_FWSHCR6                 (R_MFWD_BASE + R_MFWD_FWSHCR6_OFFSET)
#define R_MFWD_FWSHCR7                 (R_MFWD_BASE + R_MFWD_FWSHCR7_OFFSET)
#define R_MFWD_FWSHCR8                 (R_MFWD_BASE + R_MFWD_FWSHCR8_OFFSET)
#define R_MFWD_FWSHCR9                 (R_MFWD_BASE + R_MFWD_FWSHCR9_OFFSET)
#define R_MFWD_FWSHCR10                 (R_MFWD_BASE + R_MFWD_FWSHCR10_OFFSET)
#define R_MFWD_FWSHCR11                 (R_MFWD_BASE + R_MFWD_FWSHCR11_OFFSET)
#define R_MFWD_FWSHCR12                 (R_MFWD_BASE + R_MFWD_FWSHCR12_OFFSET)
#define R_MFWD_FWSHCR13                 (R_MFWD_BASE + R_MFWD_FWSHCR13_OFFSET)
#define R_MFWD_FWSHCRR                 (R_MFWD_BASE + R_MFWD_FWSHCRR_OFFSET)
#define R_MFWD_FWLTHHEC                 (R_MFWD_BASE + R_MFWD_FWLTHHEC_OFFSET)
#define R_MFWD_FWLTHHC                 (R_MFWD_BASE + R_MFWD_FWLTHHC_OFFSET)
#define R_MFWD_FWLTHTL0                 (R_MFWD_BASE + R_MFWD_FWLTHTL0_OFFSET)
#define R_MFWD_FWLTHTL1                 (R_MFWD_BASE + R_MFWD_FWLTHTL1_OFFSET)
#define R_MFWD_FWLTHTL2                 (R_MFWD_BASE + R_MFWD_FWLTHTL2_OFFSET)
#define R_MFWD_FWLTHTL3                 (R_MFWD_BASE + R_MFWD_FWLTHTL3_OFFSET)
#define R_MFWD_FWLTHTL4                 (R_MFWD_BASE + R_MFWD_FWLTHTL4_OFFSET)
#define R_MFWD_FWLTHTL5                 (R_MFWD_BASE + R_MFWD_FWLTHTL5_OFFSET)
#define R_MFWD_FWLTHTL6                 (R_MFWD_BASE + R_MFWD_FWLTHTL6_OFFSET)
#define R_MFWD_FWLTHTL7                 (R_MFWD_BASE + R_MFWD_FWLTHTL7_OFFSET)
#define R_MFWD_FWLTHTL80                 (R_MFWD_BASE + R_MFWD_FWLTHTL80_OFFSET)
#define R_MFWD_FWLTHTL9                 (R_MFWD_BASE + R_MFWD_FWLTHTL9_OFFSET)
#define R_MFWD_FWLTHTLR                 (R_MFWD_BASE + R_MFWD_FWLTHTLR_OFFSET)
#define R_MFWD_FWLTHTIM                 (R_MFWD_BASE + R_MFWD_FWLTHTIM_OFFSET)
#define R_MFWD_FWLTHTEM                 (R_MFWD_BASE + R_MFWD_FWLTHTEM_OFFSET)
#define R_MFWD_FWLTHTS0                 (R_MFWD_BASE + R_MFWD_FWLTHTS0_OFFSET)
#define R_MFWD_FWLTHTS1                 (R_MFWD_BASE + R_MFWD_FWLTHTS1_OFFSET)
#define R_MFWD_FWLTHTS2                 (R_MFWD_BASE + R_MFWD_FWLTHTS2_OFFSET)
#define R_MFWD_FWLTHTS3                 (R_MFWD_BASE + R_MFWD_FWLTHTS3_OFFSET)
#define R_MFWD_FWLTHTS4                 (R_MFWD_BASE + R_MFWD_FWLTHTS4_OFFSET)
#define R_MFWD_FWLTHTSR0                 (R_MFWD_BASE + R_MFWD_FWLTHTSR0_OFFSET)
#define R_MFWD_FWLTHTSR1                 (R_MFWD_BASE + R_MFWD_FWLTHTSR1_OFFSET)
#define R_MFWD_FWLTHTSR2                 (R_MFWD_BASE + R_MFWD_FWLTHTSR2_OFFSET)
#define R_MFWD_FWLTHTSR3                 (R_MFWD_BASE + R_MFWD_FWLTHTSR3_OFFSET)
#define R_MFWD_FWLTHTSR40                 (R_MFWD_BASE + R_MFWD_FWLTHTSR40_OFFSET)
#define R_MFWD_FWLTHTSR5                 (R_MFWD_BASE + R_MFWD_FWLTHTSR5_OFFSET)
#define R_MFWD_FWLTHTR                 (R_MFWD_BASE + R_MFWD_FWLTHTR_OFFSET)
#define R_MFWD_FWLTHTRR0                 (R_MFWD_BASE + R_MFWD_FWLTHTRR0_OFFSET)
#define R_MFWD_FWLTHTRR1                 (R_MFWD_BASE + R_MFWD_FWLTHTRR1_OFFSET)
#define R_MFWD_FWLTHTRR2                 (R_MFWD_BASE + R_MFWD_FWLTHTRR2_OFFSET)
#define R_MFWD_FWLTHTRR3                 (R_MFWD_BASE + R_MFWD_FWLTHTRR3_OFFSET)
#define R_MFWD_FWLTHTRR4                 (R_MFWD_BASE + R_MFWD_FWLTHTRR4_OFFSET)
#define R_MFWD_FWLTHTRR5                 (R_MFWD_BASE + R_MFWD_FWLTHTRR5_OFFSET)
#define R_MFWD_FWLTHTRR6                 (R_MFWD_BASE + R_MFWD_FWLTHTRR6_OFFSET)
#define R_MFWD_FWLTHTRR7                 (R_MFWD_BASE + R_MFWD_FWLTHTRR7_OFFSET)
#define R_MFWD_FWLTHTRR8                 (R_MFWD_BASE + R_MFWD_FWLTHTRR8_OFFSET)
#define R_MFWD_FWLTHTRR90                 (R_MFWD_BASE + R_MFWD_FWLTHTRR90_OFFSET)
#define R_MFWD_FWLTHTRR10                 (R_MFWD_BASE + R_MFWD_FWLTHTRR10_OFFSET)
#define R_MFWD_FWMACHEC                 (R_MFWD_BASE + R_MFWD_FWMACHEC_OFFSET)
#define R_MFWD_FWMACHC                 (R_MFWD_BASE + R_MFWD_FWMACHC_OFFSET)
#define R_MFWD_FWMACTL0                 (R_MFWD_BASE + R_MFWD_FWMACTL0_OFFSET)
#define R_MFWD_FWMACTL1                 (R_MFWD_BASE + R_MFWD_FWMACTL1_OFFSET)
#define R_MFWD_FWMACTL2                 (R_MFWD_BASE + R_MFWD_FWMACTL2_OFFSET)
#define R_MFWD_FWMACTL3                 (R_MFWD_BASE + R_MFWD_FWMACTL3_OFFSET)
#define R_MFWD_FWMACTL40                 (R_MFWD_BASE + R_MFWD_FWMACTL40_OFFSET)
#define R_MFWD_FWMACTL5                 (R_MFWD_BASE + R_MFWD_FWMACTL5_OFFSET)
#define R_MFWD_FWMACTLR                 (R_MFWD_BASE + R_MFWD_FWMACTLR_OFFSET)
#define R_MFWD_FWMACTIM                 (R_MFWD_BASE + R_MFWD_FWMACTIM_OFFSET)
#define R_MFWD_FWMACTEM                 (R_MFWD_BASE + R_MFWD_FWMACTEM_OFFSET)
#define R_MFWD_FWMACTS0                 (R_MFWD_BASE + R_MFWD_FWMACTS0_OFFSET)
#define R_MFWD_FWMACTS1                 (R_MFWD_BASE + R_MFWD_FWMACTS1_OFFSET)
#define R_MFWD_FWMACTSR0                 (R_MFWD_BASE + R_MFWD_FWMACTSR0_OFFSET)
#define R_MFWD_FWMACTSR1                 (R_MFWD_BASE + R_MFWD_FWMACTSR1_OFFSET)
#define R_MFWD_FWMACTSR20                 (R_MFWD_BASE + R_MFWD_FWMACTSR20_OFFSET)
#define R_MFWD_FWMACTSR3                 (R_MFWD_BASE + R_MFWD_FWMACTSR3_OFFSET)
#define R_MFWD_FWMACTR                 (R_MFWD_BASE + R_MFWD_FWMACTR_OFFSET)
#define R_MFWD_FWMACTRR0                 (R_MFWD_BASE + R_MFWD_FWMACTRR0_OFFSET)
#define R_MFWD_FWMACTRR1                 (R_MFWD_BASE + R_MFWD_FWMACTRR1_OFFSET)
#define R_MFWD_FWMACTRR2                 (R_MFWD_BASE + R_MFWD_FWMACTRR2_OFFSET)
#define R_MFWD_FWMACTRR3                 (R_MFWD_BASE + R_MFWD_FWMACTRR3_OFFSET)
#define R_MFWD_FWMACTRR4                 (R_MFWD_BASE + R_MFWD_FWMACTRR4_OFFSET)
#define R_MFWD_FWMACTRR50                 (R_MFWD_BASE + R_MFWD_FWMACTRR50_OFFSET)
#define R_MFWD_FWMACTRR6                 (R_MFWD_BASE + R_MFWD_FWMACTRR6_OFFSET)
#define R_MFWD_FWMACAGUSPC                 (R_MFWD_BASE + R_MFWD_FWMACAGUSPC_OFFSET)
#define R_MFWD_FWMACAGC                 (R_MFWD_BASE + R_MFWD_FWMACAGC_OFFSET)
#define R_MFWD_FWMACAGM0                 (R_MFWD_BASE + R_MFWD_FWMACAGM0_OFFSET)
#define R_MFWD_FWMACAGM1                 (R_MFWD_BASE + R_MFWD_FWMACAGM1_OFFSET)
#define R_MFWD_FWVLANTEC                 (R_MFWD_BASE + R_MFWD_FWVLANTEC_OFFSET)
#define R_MFWD_FWVLANTL0                 (R_MFWD_BASE + R_MFWD_FWVLANTL0_OFFSET)
#define R_MFWD_FWVLANTL1                 (R_MFWD_BASE + R_MFWD_FWVLANTL1_OFFSET)
#define R_MFWD_FWVLANTL2                 (R_MFWD_BASE + R_MFWD_FWVLANTL2_OFFSET)
#define R_MFWD_FWVLANTL30                 (R_MFWD_BASE + R_MFWD_FWVLANTL30_OFFSET)
#define R_MFWD_FWVLANTL4                 (R_MFWD_BASE + R_MFWD_FWVLANTL4_OFFSET)
#define R_MFWD_FWVLANTLR                 (R_MFWD_BASE + R_MFWD_FWVLANTLR_OFFSET)
#define R_MFWD_FWVLANTIM                 (R_MFWD_BASE + R_MFWD_FWVLANTIM_OFFSET)
#define R_MFWD_FWVLANTEM                 (R_MFWD_BASE + R_MFWD_FWVLANTEM_OFFSET)
#define R_MFWD_FWVLANTS                 (R_MFWD_BASE + R_MFWD_FWVLANTS_OFFSET)
#define R_MFWD_FWVLANTSR0                 (R_MFWD_BASE + R_MFWD_FWVLANTSR0_OFFSET)
#define R_MFWD_FWVLANTSR1                 (R_MFWD_BASE + R_MFWD_FWVLANTSR1_OFFSET)
#define R_MFWD_FWVLANTSR20                 (R_MFWD_BASE + R_MFWD_FWVLANTSR20_OFFSET)
#define R_MFWD_FWVLANTSR3                 (R_MFWD_BASE + R_MFWD_FWVLANTSR3_OFFSET)
#define R_MFWD_FWPBFC0                 (R_MFWD_BASE + R_MFWD_FWPBFC0_OFFSET)
#define R_MFWD_FWPBFC1                 (R_MFWD_BASE + R_MFWD_FWPBFC1_OFFSET)
#define R_MFWD_FWPBFC2                 (R_MFWD_BASE + R_MFWD_FWPBFC2_OFFSET)
#define R_MFWD_FWPBFCSDC00                 (R_MFWD_BASE + R_MFWD_FWPBFCSDC00_OFFSET)
#define R_MFWD_FWPBFCSDC10                 (R_MFWD_BASE + R_MFWD_FWPBFCSDC10_OFFSET)
#define R_MFWD_FWPBFCSDC20                 (R_MFWD_BASE + R_MFWD_FWPBFCSDC20_OFFSET)
#define R_MFWD_FWL23URL0                 (R_MFWD_BASE + R_MFWD_FWL23URL0_OFFSET)
#define R_MFWD_FWL23URL1                 (R_MFWD_BASE + R_MFWD_FWL23URL1_OFFSET)
#define R_MFWD_FWL23URL2                 (R_MFWD_BASE + R_MFWD_FWL23URL2_OFFSET)
#define R_MFWD_FWL23URL3                 (R_MFWD_BASE + R_MFWD_FWL23URL3_OFFSET)
#define R_MFWD_FWL23URLR                 (R_MFWD_BASE + R_MFWD_FWL23URLR_OFFSET)
#define R_MFWD_FWL23UTIM                 (R_MFWD_BASE + R_MFWD_FWL23UTIM_OFFSET)
#define R_MFWD_FWL23URR                 (R_MFWD_BASE + R_MFWD_FWL23URR_OFFSET)
#define R_MFWD_FWL23URRR0                 (R_MFWD_BASE + R_MFWD_FWL23URRR0_OFFSET)
#define R_MFWD_FWL23URRR1                 (R_MFWD_BASE + R_MFWD_FWL23URRR1_OFFSET)
#define R_MFWD_FWL23URRR2                 (R_MFWD_BASE + R_MFWD_FWL23URRR2_OFFSET)
#define R_MFWD_FWL23URRR3                 (R_MFWD_BASE + R_MFWD_FWL23URRR3_OFFSET)
#define R_MFWD_FWL23URMC00                 (R_MFWD_BASE + R_MFWD_FWL23URMC00_OFFSET)
#define R_MFWD_FWL23URMC01                 (R_MFWD_BASE + R_MFWD_FWL23URMC01_OFFSET)
#define R_MFWD_FWL23URMC02                 (R_MFWD_BASE + R_MFWD_FWL23URMC02_OFFSET)
#define R_MFWD_FWL23URMC03                 (R_MFWD_BASE + R_MFWD_FWL23URMC03_OFFSET)
#define R_MFWD_FWL23URMC04                 (R_MFWD_BASE + R_MFWD_FWL23URMC04_OFFSET)
#define R_MFWD_FWL23URMC05                 (R_MFWD_BASE + R_MFWD_FWL23URMC05_OFFSET)
#define R_MFWD_FWL23URMC06                 (R_MFWD_BASE + R_MFWD_FWL23URMC06_OFFSET)
#define R_MFWD_FWL23URMC07                 (R_MFWD_BASE + R_MFWD_FWL23URMC07_OFFSET)
#define R_MFWD_FWL23URMC08                 (R_MFWD_BASE + R_MFWD_FWL23URMC08_OFFSET)
#define R_MFWD_FWL23URMC09                 (R_MFWD_BASE + R_MFWD_FWL23URMC09_OFFSET)
#define R_MFWD_FWL23URMC10                 (R_MFWD_BASE + R_MFWD_FWL23URMC10_OFFSET)
#define R_MFWD_FWL23URMC11                 (R_MFWD_BASE + R_MFWD_FWL23URMC11_OFFSET)
#define R_MFWD_FWL23URMC12                 (R_MFWD_BASE + R_MFWD_FWL23URMC12_OFFSET)
#define R_MFWD_FWL23URMC13                 (R_MFWD_BASE + R_MFWD_FWL23URMC13_OFFSET)
#define R_MFWD_FWL23URMC14                 (R_MFWD_BASE + R_MFWD_FWL23URMC14_OFFSET)
#define R_MFWD_FWL23URMC15                 (R_MFWD_BASE + R_MFWD_FWL23URMC15_OFFSET)
#define R_MFWD_FWL23URMC16                 (R_MFWD_BASE + R_MFWD_FWL23URMC16_OFFSET)
#define R_MFWD_FWL23URMC17                 (R_MFWD_BASE + R_MFWD_FWL23URMC17_OFFSET)
#define R_MFWD_FWL23URMC18                 (R_MFWD_BASE + R_MFWD_FWL23URMC18_OFFSET)
#define R_MFWD_FWL23URMC19                 (R_MFWD_BASE + R_MFWD_FWL23URMC19_OFFSET)
#define R_MFWD_FWL23URMC20                 (R_MFWD_BASE + R_MFWD_FWL23URMC20_OFFSET)
#define R_MFWD_FWL23URMC21                 (R_MFWD_BASE + R_MFWD_FWL23URMC21_OFFSET)
#define R_MFWD_FWL23URMC22                 (R_MFWD_BASE + R_MFWD_FWL23URMC22_OFFSET)
#define R_MFWD_FWL23URMC23                 (R_MFWD_BASE + R_MFWD_FWL23URMC23_OFFSET)
#define R_MFWD_FWL23URMC24                 (R_MFWD_BASE + R_MFWD_FWL23URMC24_OFFSET)
#define R_MFWD_FWL23URMC25                 (R_MFWD_BASE + R_MFWD_FWL23URMC25_OFFSET)
#define R_MFWD_FWL23URMC26                 (R_MFWD_BASE + R_MFWD_FWL23URMC26_OFFSET)
#define R_MFWD_FWL23URMC27                 (R_MFWD_BASE + R_MFWD_FWL23URMC27_OFFSET)
#define R_MFWD_FWL23URMC28                 (R_MFWD_BASE + R_MFWD_FWL23URMC28_OFFSET)
#define R_MFWD_FWL23URMC29                 (R_MFWD_BASE + R_MFWD_FWL23URMC29_OFFSET)
#define R_MFWD_FWL23URMC30                 (R_MFWD_BASE + R_MFWD_FWL23URMC30_OFFSET)
#define R_MFWD_FWL23URMC31                 (R_MFWD_BASE + R_MFWD_FWL23URMC31_OFFSET)
#define R_MFWD_FWPMFGC00                 (R_MFWD_BASE + R_MFWD_FWPMFGC00_OFFSET)
#define R_MFWD_FWPMFGC01                 (R_MFWD_BASE + R_MFWD_FWPMFGC01_OFFSET)
#define R_MFWD_FWPMFGC02                 (R_MFWD_BASE + R_MFWD_FWPMFGC02_OFFSET)
#define R_MFWD_FWPMFGC03                 (R_MFWD_BASE + R_MFWD_FWPMFGC03_OFFSET)
#define R_MFWD_FWPMFGC04                 (R_MFWD_BASE + R_MFWD_FWPMFGC04_OFFSET)
#define R_MFWD_FWPMFGC05                 (R_MFWD_BASE + R_MFWD_FWPMFGC05_OFFSET)
#define R_MFWD_FWPMFGC06                 (R_MFWD_BASE + R_MFWD_FWPMFGC06_OFFSET)
#define R_MFWD_FWPMFGC07                 (R_MFWD_BASE + R_MFWD_FWPMFGC07_OFFSET)
#define R_MFWD_FWPMFGC08                 (R_MFWD_BASE + R_MFWD_FWPMFGC08_OFFSET)
#define R_MFWD_FWPMFGC09                 (R_MFWD_BASE + R_MFWD_FWPMFGC09_OFFSET)
#define R_MFWD_FWPMFGC10                 (R_MFWD_BASE + R_MFWD_FWPMFGC10_OFFSET)
#define R_MFWD_FWPMFGC11                 (R_MFWD_BASE + R_MFWD_FWPMFGC11_OFFSET)
#define R_MFWD_FWPMFGC12                 (R_MFWD_BASE + R_MFWD_FWPMFGC12_OFFSET)
#define R_MFWD_FWPMFGC13                 (R_MFWD_BASE + R_MFWD_FWPMFGC13_OFFSET)
#define R_MFWD_FWPMFGC14                 (R_MFWD_BASE + R_MFWD_FWPMFGC14_OFFSET)
#define R_MFWD_FWPMFGC15                 (R_MFWD_BASE + R_MFWD_FWPMFGC15_OFFSET)
#define R_MFWD_FWPMTRFC00                 (R_MFWD_BASE + R_MFWD_FWPMTRFC00_OFFSET)
#define R_MFWD_FWPMTRFC01                 (R_MFWD_BASE + R_MFWD_FWPMTRFC01_OFFSET)
#define R_MFWD_FWPMTRFC02                 (R_MFWD_BASE + R_MFWD_FWPMTRFC02_OFFSET)
#define R_MFWD_FWPMTRFC03                 (R_MFWD_BASE + R_MFWD_FWPMTRFC03_OFFSET)
#define R_MFWD_FWPMTRFC04                 (R_MFWD_BASE + R_MFWD_FWPMTRFC04_OFFSET)
#define R_MFWD_FWPMTRFC05                 (R_MFWD_BASE + R_MFWD_FWPMTRFC05_OFFSET)
#define R_MFWD_FWPMTRFC06                 (R_MFWD_BASE + R_MFWD_FWPMTRFC06_OFFSET)
#define R_MFWD_FWPMTRFC07                 (R_MFWD_BASE + R_MFWD_FWPMTRFC07_OFFSET)
#define R_MFWD_FWPMTRFC08                 (R_MFWD_BASE + R_MFWD_FWPMTRFC08_OFFSET)
#define R_MFWD_FWPMTRFC09                 (R_MFWD_BASE + R_MFWD_FWPMTRFC09_OFFSET)
#define R_MFWD_FWPMTRFC10                 (R_MFWD_BASE + R_MFWD_FWPMTRFC10_OFFSET)
#define R_MFWD_FWPMTRFC11                 (R_MFWD_BASE + R_MFWD_FWPMTRFC11_OFFSET)
#define R_MFWD_FWPMTRFC12                 (R_MFWD_BASE + R_MFWD_FWPMTRFC12_OFFSET)
#define R_MFWD_FWPMTRFC13                 (R_MFWD_BASE + R_MFWD_FWPMTRFC13_OFFSET)
#define R_MFWD_FWPMTRFC14                 (R_MFWD_BASE + R_MFWD_FWPMTRFC14_OFFSET)
#define R_MFWD_FWPMTRFC15                 (R_MFWD_BASE + R_MFWD_FWPMTRFC15_OFFSET)
#define R_MFWD_FWPMTRFC16                 (R_MFWD_BASE + R_MFWD_FWPMTRFC16_OFFSET)
#define R_MFWD_FWPMTRFC17                 (R_MFWD_BASE + R_MFWD_FWPMTRFC17_OFFSET)
#define R_MFWD_FWPMTRFC18                 (R_MFWD_BASE + R_MFWD_FWPMTRFC18_OFFSET)
#define R_MFWD_FWPMTRFC19                 (R_MFWD_BASE + R_MFWD_FWPMTRFC19_OFFSET)
#define R_MFWD_FWPMTRFC20                 (R_MFWD_BASE + R_MFWD_FWPMTRFC20_OFFSET)
#define R_MFWD_FWPMTRFC21                 (R_MFWD_BASE + R_MFWD_FWPMTRFC21_OFFSET)
#define R_MFWD_FWPMTRFC22                 (R_MFWD_BASE + R_MFWD_FWPMTRFC22_OFFSET)
#define R_MFWD_FWPMTRFC23                 (R_MFWD_BASE + R_MFWD_FWPMTRFC23_OFFSET)
#define R_MFWD_FWPMTRFC24                 (R_MFWD_BASE + R_MFWD_FWPMTRFC24_OFFSET)
#define R_MFWD_FWPMTRFC25                 (R_MFWD_BASE + R_MFWD_FWPMTRFC25_OFFSET)
#define R_MFWD_FWPMTRFC26                 (R_MFWD_BASE + R_MFWD_FWPMTRFC26_OFFSET)
#define R_MFWD_FWPMTRFC27                 (R_MFWD_BASE + R_MFWD_FWPMTRFC27_OFFSET)
#define R_MFWD_FWPMTRFC28                 (R_MFWD_BASE + R_MFWD_FWPMTRFC28_OFFSET)
#define R_MFWD_FWPMTRFC29                 (R_MFWD_BASE + R_MFWD_FWPMTRFC29_OFFSET)
#define R_MFWD_FWPMTRFC30                 (R_MFWD_BASE + R_MFWD_FWPMTRFC30_OFFSET)
#define R_MFWD_FWPMTRFC31                 (R_MFWD_BASE + R_MFWD_FWPMTRFC31_OFFSET)
#define R_MFWD_FWPMTRCBSC00                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC00_OFFSET)
#define R_MFWD_FWPMTRCBSC01                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC01_OFFSET)
#define R_MFWD_FWPMTRCBSC02                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC02_OFFSET)
#define R_MFWD_FWPMTRCBSC03                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC03_OFFSET)
#define R_MFWD_FWPMTRCBSC04                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC04_OFFSET)
#define R_MFWD_FWPMTRCBSC05                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC05_OFFSET)
#define R_MFWD_FWPMTRCBSC06                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC06_OFFSET)
#define R_MFWD_FWPMTRCBSC07                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC07_OFFSET)
#define R_MFWD_FWPMTRCBSC08                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC08_OFFSET)
#define R_MFWD_FWPMTRCBSC09                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC09_OFFSET)
#define R_MFWD_FWPMTRCBSC10                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC10_OFFSET)
#define R_MFWD_FWPMTRCBSC11                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC11_OFFSET)
#define R_MFWD_FWPMTRCBSC12                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC12_OFFSET)
#define R_MFWD_FWPMTRCBSC13                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC13_OFFSET)
#define R_MFWD_FWPMTRCBSC14                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC14_OFFSET)
#define R_MFWD_FWPMTRCBSC15                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC15_OFFSET)
#define R_MFWD_FWPMTRCBSC16                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC16_OFFSET)
#define R_MFWD_FWPMTRCBSC17                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC17_OFFSET)
#define R_MFWD_FWPMTRCBSC18                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC18_OFFSET)
#define R_MFWD_FWPMTRCBSC19                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC19_OFFSET)
#define R_MFWD_FWPMTRCBSC20                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC20_OFFSET)
#define R_MFWD_FWPMTRCBSC21                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC21_OFFSET)
#define R_MFWD_FWPMTRCBSC22                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC22_OFFSET)
#define R_MFWD_FWPMTRCBSC23                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC23_OFFSET)
#define R_MFWD_FWPMTRCBSC24                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC24_OFFSET)
#define R_MFWD_FWPMTRCBSC25                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC25_OFFSET)
#define R_MFWD_FWPMTRCBSC26                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC26_OFFSET)
#define R_MFWD_FWPMTRCBSC27                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC27_OFFSET)
#define R_MFWD_FWPMTRCBSC28                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC28_OFFSET)
#define R_MFWD_FWPMTRCBSC29                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC29_OFFSET)
#define R_MFWD_FWPMTRCBSC30                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC30_OFFSET)
#define R_MFWD_FWPMTRCBSC31                 (R_MFWD_BASE + R_MFWD_FWPMTRCBSC31_OFFSET)
#define R_MFWD_FWPMTRCIRC00                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC00_OFFSET)
#define R_MFWD_FWPMTRCIRC01                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC01_OFFSET)
#define R_MFWD_FWPMTRCIRC02                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC02_OFFSET)
#define R_MFWD_FWPMTRCIRC03                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC03_OFFSET)
#define R_MFWD_FWPMTRCIRC04                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC04_OFFSET)
#define R_MFWD_FWPMTRCIRC05                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC05_OFFSET)
#define R_MFWD_FWPMTRCIRC06                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC06_OFFSET)
#define R_MFWD_FWPMTRCIRC07                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC07_OFFSET)
#define R_MFWD_FWPMTRCIRC08                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC08_OFFSET)
#define R_MFWD_FWPMTRCIRC09                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC09_OFFSET)
#define R_MFWD_FWPMTRCIRC10                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC10_OFFSET)
#define R_MFWD_FWPMTRCIRC11                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC11_OFFSET)
#define R_MFWD_FWPMTRCIRC12                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC12_OFFSET)
#define R_MFWD_FWPMTRCIRC13                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC13_OFFSET)
#define R_MFWD_FWPMTRCIRC14                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC14_OFFSET)
#define R_MFWD_FWPMTRCIRC15                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC15_OFFSET)
#define R_MFWD_FWPMTRCIRC16                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC16_OFFSET)
#define R_MFWD_FWPMTRCIRC17                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC17_OFFSET)
#define R_MFWD_FWPMTRCIRC18                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC18_OFFSET)
#define R_MFWD_FWPMTRCIRC19                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC19_OFFSET)
#define R_MFWD_FWPMTRCIRC20                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC20_OFFSET)
#define R_MFWD_FWPMTRCIRC21                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC21_OFFSET)
#define R_MFWD_FWPMTRCIRC22                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC22_OFFSET)
#define R_MFWD_FWPMTRCIRC23                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC23_OFFSET)
#define R_MFWD_FWPMTRCIRC24                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC24_OFFSET)
#define R_MFWD_FWPMTRCIRC25                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC25_OFFSET)
#define R_MFWD_FWPMTRCIRC26                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC26_OFFSET)
#define R_MFWD_FWPMTRCIRC27                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC27_OFFSET)
#define R_MFWD_FWPMTRCIRC28                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC28_OFFSET)
#define R_MFWD_FWPMTRCIRC29                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC29_OFFSET)
#define R_MFWD_FWPMTRCIRC30                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC30_OFFSET)
#define R_MFWD_FWPMTRCIRC31                 (R_MFWD_BASE + R_MFWD_FWPMTRCIRC31_OFFSET)
#define R_MFWD_FWPMTREBSC0                 (R_MFWD_BASE + R_MFWD_FWPMTREBSC0_OFFSET)
#define R_MFWD_FWPMTREBSC1                 (R_MFWD_BASE + R_MFWD_FWPMTREBSC1_OFFSET)
#define R_MFWD_FWPMTREBSC2                 (R_MFWD_BASE + R_MFWD_FWPMTREBSC2_OFFSET)
#define R_MFWD_FWPMTREBSC3                 (R_MFWD_BASE + R_MFWD_FWPMTREBSC3_OFFSET)
#define R_MFWD_FWPMTREBSC4                 (R_MFWD_BASE + R_MFWD_FWPMTREBSC4_OFFSET)
#define R_MFWD_FWPMTREBSC5                 (R_MFWD_BASE + R_MFWD_FWPMTREBSC5_OFFSET)
#define R_MFWD_FWPMTREBSC6                 (R_MFWD_BASE + R_MFWD_FWPMTREBSC6_OFFSET)
#define R_MFWD_FWPMTREBSC7                 (R_MFWD_BASE + R_MFWD_FWPMTREBSC7_OFFSET)
#define R_MFWD_FWPMTREIRC0                 (R_MFWD_BASE + R_MFWD_FWPMTREIRC0_OFFSET)
#define R_MFWD_FWPMTREIRC1                 (R_MFWD_BASE + R_MFWD_FWPMTREIRC1_OFFSET)
#define R_MFWD_FWPMTREIRC2                 (R_MFWD_BASE + R_MFWD_FWPMTREIRC2_OFFSET)
#define R_MFWD_FWPMTREIRC3                 (R_MFWD_BASE + R_MFWD_FWPMTREIRC3_OFFSET)
#define R_MFWD_FWPMTREIRC4                 (R_MFWD_BASE + R_MFWD_FWPMTREIRC4_OFFSET)
#define R_MFWD_FWPMTREIRC5                 (R_MFWD_BASE + R_MFWD_FWPMTREIRC5_OFFSET)
#define R_MFWD_FWPMTREIRC6                 (R_MFWD_BASE + R_MFWD_FWPMTREIRC6_OFFSET)
#define R_MFWD_FWPMTREIRC7                 (R_MFWD_BASE + R_MFWD_FWPMTREIRC7_OFFSET)
#define R_MFWD_FWPMTRFM00                 (R_MFWD_BASE + R_MFWD_FWPMTRFM00_OFFSET)
#define R_MFWD_FWPMTRFM01                 (R_MFWD_BASE + R_MFWD_FWPMTRFM01_OFFSET)
#define R_MFWD_FWPMTRFM02                 (R_MFWD_BASE + R_MFWD_FWPMTRFM02_OFFSET)
#define R_MFWD_FWPMTRFM03                 (R_MFWD_BASE + R_MFWD_FWPMTRFM03_OFFSET)
#define R_MFWD_FWPMTRFM04                 (R_MFWD_BASE + R_MFWD_FWPMTRFM04_OFFSET)
#define R_MFWD_FWPMTRFM05                 (R_MFWD_BASE + R_MFWD_FWPMTRFM05_OFFSET)
#define R_MFWD_FWPMTRFM06                 (R_MFWD_BASE + R_MFWD_FWPMTRFM06_OFFSET)
#define R_MFWD_FWPMTRFM07                 (R_MFWD_BASE + R_MFWD_FWPMTRFM07_OFFSET)
#define R_MFWD_FWPMTRFM08                 (R_MFWD_BASE + R_MFWD_FWPMTRFM08_OFFSET)
#define R_MFWD_FWPMTRFM09                 (R_MFWD_BASE + R_MFWD_FWPMTRFM09_OFFSET)
#define R_MFWD_FWPMTRFM10                 (R_MFWD_BASE + R_MFWD_FWPMTRFM10_OFFSET)
#define R_MFWD_FWPMTRFM11                 (R_MFWD_BASE + R_MFWD_FWPMTRFM11_OFFSET)
#define R_MFWD_FWPMTRFM12                 (R_MFWD_BASE + R_MFWD_FWPMTRFM12_OFFSET)
#define R_MFWD_FWPMTRFM13                 (R_MFWD_BASE + R_MFWD_FWPMTRFM13_OFFSET)
#define R_MFWD_FWPMTRFM14                 (R_MFWD_BASE + R_MFWD_FWPMTRFM14_OFFSET)
#define R_MFWD_FWPMTRFM15                 (R_MFWD_BASE + R_MFWD_FWPMTRFM15_OFFSET)
#define R_MFWD_FWPMTRFM16                 (R_MFWD_BASE + R_MFWD_FWPMTRFM16_OFFSET)
#define R_MFWD_FWPMTRFM17                 (R_MFWD_BASE + R_MFWD_FWPMTRFM17_OFFSET)
#define R_MFWD_FWPMTRFM18                 (R_MFWD_BASE + R_MFWD_FWPMTRFM18_OFFSET)
#define R_MFWD_FWPMTRFM19                 (R_MFWD_BASE + R_MFWD_FWPMTRFM19_OFFSET)
#define R_MFWD_FWPMTRFM20                 (R_MFWD_BASE + R_MFWD_FWPMTRFM20_OFFSET)
#define R_MFWD_FWPMTRFM21                 (R_MFWD_BASE + R_MFWD_FWPMTRFM21_OFFSET)
#define R_MFWD_FWPMTRFM22                 (R_MFWD_BASE + R_MFWD_FWPMTRFM22_OFFSET)
#define R_MFWD_FWPMTRFM23                 (R_MFWD_BASE + R_MFWD_FWPMTRFM23_OFFSET)
#define R_MFWD_FWPMTRFM24                 (R_MFWD_BASE + R_MFWD_FWPMTRFM24_OFFSET)
#define R_MFWD_FWPMTRFM25                 (R_MFWD_BASE + R_MFWD_FWPMTRFM25_OFFSET)
#define R_MFWD_FWPMTRFM26                 (R_MFWD_BASE + R_MFWD_FWPMTRFM26_OFFSET)
#define R_MFWD_FWPMTRFM27                 (R_MFWD_BASE + R_MFWD_FWPMTRFM27_OFFSET)
#define R_MFWD_FWPMTRFM28                 (R_MFWD_BASE + R_MFWD_FWPMTRFM28_OFFSET)
#define R_MFWD_FWPMTRFM29                 (R_MFWD_BASE + R_MFWD_FWPMTRFM29_OFFSET)
#define R_MFWD_FWPMTRFM30                 (R_MFWD_BASE + R_MFWD_FWPMTRFM30_OFFSET)
#define R_MFWD_FWPMTRFM31                 (R_MFWD_BASE + R_MFWD_FWPMTRFM31_OFFSET)
#define R_MFWD_FWFTL0                 (R_MFWD_BASE + R_MFWD_FWFTL0_OFFSET)
#define R_MFWD_FWFTL1                 (R_MFWD_BASE + R_MFWD_FWFTL1_OFFSET)
#define R_MFWD_FWFTLR                 (R_MFWD_BASE + R_MFWD_FWFTLR_OFFSET)
#define R_MFWD_FWFTOC                 (R_MFWD_BASE + R_MFWD_FWFTOC_OFFSET)
#define R_MFWD_FWFTOPC                 (R_MFWD_BASE + R_MFWD_FWFTOPC_OFFSET)
#define R_MFWD_FWFTIM                 (R_MFWD_BASE + R_MFWD_FWFTIM_OFFSET)
#define R_MFWD_FWFTR                 (R_MFWD_BASE + R_MFWD_FWFTR_OFFSET)
#define R_MFWD_FWFTRR0                 (R_MFWD_BASE + R_MFWD_FWFTRR0_OFFSET)
#define R_MFWD_FWFTRR1                 (R_MFWD_BASE + R_MFWD_FWFTRR1_OFFSET)
#define R_MFWD_FWFTRR2                 (R_MFWD_BASE + R_MFWD_FWFTRR2_OFFSET)
#define R_MFWD_FWSEQNGC00                 (R_MFWD_BASE + R_MFWD_FWSEQNGC00_OFFSET)
#define R_MFWD_FWSEQNGC01                 (R_MFWD_BASE + R_MFWD_FWSEQNGC01_OFFSET)
#define R_MFWD_FWSEQNGC02                 (R_MFWD_BASE + R_MFWD_FWSEQNGC02_OFFSET)
#define R_MFWD_FWSEQNGC03                 (R_MFWD_BASE + R_MFWD_FWSEQNGC03_OFFSET)
#define R_MFWD_FWSEQNGC04                 (R_MFWD_BASE + R_MFWD_FWSEQNGC04_OFFSET)
#define R_MFWD_FWSEQNGC05                 (R_MFWD_BASE + R_MFWD_FWSEQNGC05_OFFSET)
#define R_MFWD_FWSEQNGC06                 (R_MFWD_BASE + R_MFWD_FWSEQNGC06_OFFSET)
#define R_MFWD_FWSEQNGC07                 (R_MFWD_BASE + R_MFWD_FWSEQNGC07_OFFSET)
#define R_MFWD_FWSEQNGC08                 (R_MFWD_BASE + R_MFWD_FWSEQNGC08_OFFSET)
#define R_MFWD_FWSEQNGC09                 (R_MFWD_BASE + R_MFWD_FWSEQNGC09_OFFSET)
#define R_MFWD_FWSEQNGC10                 (R_MFWD_BASE + R_MFWD_FWSEQNGC10_OFFSET)
#define R_MFWD_FWSEQNGC11                 (R_MFWD_BASE + R_MFWD_FWSEQNGC11_OFFSET)
#define R_MFWD_FWSEQNGC12                 (R_MFWD_BASE + R_MFWD_FWSEQNGC12_OFFSET)
#define R_MFWD_FWSEQNGC13                 (R_MFWD_BASE + R_MFWD_FWSEQNGC13_OFFSET)
#define R_MFWD_FWSEQNGC14                 (R_MFWD_BASE + R_MFWD_FWSEQNGC14_OFFSET)
#define R_MFWD_FWSEQNGC15                 (R_MFWD_BASE + R_MFWD_FWSEQNGC15_OFFSET)
#define R_MFWD_FWSEQNGC16                 (R_MFWD_BASE + R_MFWD_FWSEQNGC16_OFFSET)
#define R_MFWD_FWSEQNGC17                 (R_MFWD_BASE + R_MFWD_FWSEQNGC17_OFFSET)
#define R_MFWD_FWSEQNGC18                 (R_MFWD_BASE + R_MFWD_FWSEQNGC18_OFFSET)
#define R_MFWD_FWSEQNGC19                 (R_MFWD_BASE + R_MFWD_FWSEQNGC19_OFFSET)
#define R_MFWD_FWSEQNGC20                 (R_MFWD_BASE + R_MFWD_FWSEQNGC20_OFFSET)
#define R_MFWD_FWSEQNGC21                 (R_MFWD_BASE + R_MFWD_FWSEQNGC21_OFFSET)
#define R_MFWD_FWSEQNGC22                 (R_MFWD_BASE + R_MFWD_FWSEQNGC22_OFFSET)
#define R_MFWD_FWSEQNGC23                 (R_MFWD_BASE + R_MFWD_FWSEQNGC23_OFFSET)
#define R_MFWD_FWSEQNGC24                 (R_MFWD_BASE + R_MFWD_FWSEQNGC24_OFFSET)
#define R_MFWD_FWSEQNGC25                 (R_MFWD_BASE + R_MFWD_FWSEQNGC25_OFFSET)
#define R_MFWD_FWSEQNGC26                 (R_MFWD_BASE + R_MFWD_FWSEQNGC26_OFFSET)
#define R_MFWD_FWSEQNGC27                 (R_MFWD_BASE + R_MFWD_FWSEQNGC27_OFFSET)
#define R_MFWD_FWSEQNGC28                 (R_MFWD_BASE + R_MFWD_FWSEQNGC28_OFFSET)
#define R_MFWD_FWSEQNGC29                 (R_MFWD_BASE + R_MFWD_FWSEQNGC29_OFFSET)
#define R_MFWD_FWSEQNGC30                 (R_MFWD_BASE + R_MFWD_FWSEQNGC30_OFFSET)
#define R_MFWD_FWSEQNGC31                 (R_MFWD_BASE + R_MFWD_FWSEQNGC31_OFFSET)
#define R_MFWD_FWSEQNGM00                 (R_MFWD_BASE + R_MFWD_FWSEQNGM00_OFFSET)
#define R_MFWD_FWSEQNGM01                 (R_MFWD_BASE + R_MFWD_FWSEQNGM01_OFFSET)
#define R_MFWD_FWSEQNGM02                 (R_MFWD_BASE + R_MFWD_FWSEQNGM02_OFFSET)
#define R_MFWD_FWSEQNGM03                 (R_MFWD_BASE + R_MFWD_FWSEQNGM03_OFFSET)
#define R_MFWD_FWSEQNGM04                 (R_MFWD_BASE + R_MFWD_FWSEQNGM04_OFFSET)
#define R_MFWD_FWSEQNGM05                 (R_MFWD_BASE + R_MFWD_FWSEQNGM05_OFFSET)
#define R_MFWD_FWSEQNGM06                 (R_MFWD_BASE + R_MFWD_FWSEQNGM06_OFFSET)
#define R_MFWD_FWSEQNGM07                 (R_MFWD_BASE + R_MFWD_FWSEQNGM07_OFFSET)
#define R_MFWD_FWSEQNGM08                 (R_MFWD_BASE + R_MFWD_FWSEQNGM08_OFFSET)
#define R_MFWD_FWSEQNGM09                 (R_MFWD_BASE + R_MFWD_FWSEQNGM09_OFFSET)
#define R_MFWD_FWSEQNGM10                 (R_MFWD_BASE + R_MFWD_FWSEQNGM10_OFFSET)
#define R_MFWD_FWSEQNGM11                 (R_MFWD_BASE + R_MFWD_FWSEQNGM11_OFFSET)
#define R_MFWD_FWSEQNGM12                 (R_MFWD_BASE + R_MFWD_FWSEQNGM12_OFFSET)
#define R_MFWD_FWSEQNGM13                 (R_MFWD_BASE + R_MFWD_FWSEQNGM13_OFFSET)
#define R_MFWD_FWSEQNGM14                 (R_MFWD_BASE + R_MFWD_FWSEQNGM14_OFFSET)
#define R_MFWD_FWSEQNGM15                 (R_MFWD_BASE + R_MFWD_FWSEQNGM15_OFFSET)
#define R_MFWD_FWSEQNGM16                 (R_MFWD_BASE + R_MFWD_FWSEQNGM16_OFFSET)
#define R_MFWD_FWSEQNGM17                 (R_MFWD_BASE + R_MFWD_FWSEQNGM17_OFFSET)
#define R_MFWD_FWSEQNGM18                 (R_MFWD_BASE + R_MFWD_FWSEQNGM18_OFFSET)
#define R_MFWD_FWSEQNGM19                 (R_MFWD_BASE + R_MFWD_FWSEQNGM19_OFFSET)
#define R_MFWD_FWSEQNGM20                 (R_MFWD_BASE + R_MFWD_FWSEQNGM20_OFFSET)
#define R_MFWD_FWSEQNGM21                 (R_MFWD_BASE + R_MFWD_FWSEQNGM21_OFFSET)
#define R_MFWD_FWSEQNGM22                 (R_MFWD_BASE + R_MFWD_FWSEQNGM22_OFFSET)
#define R_MFWD_FWSEQNGM23                 (R_MFWD_BASE + R_MFWD_FWSEQNGM23_OFFSET)
#define R_MFWD_FWSEQNGM24                 (R_MFWD_BASE + R_MFWD_FWSEQNGM24_OFFSET)
#define R_MFWD_FWSEQNGM25                 (R_MFWD_BASE + R_MFWD_FWSEQNGM25_OFFSET)
#define R_MFWD_FWSEQNGM26                 (R_MFWD_BASE + R_MFWD_FWSEQNGM26_OFFSET)
#define R_MFWD_FWSEQNGM27                 (R_MFWD_BASE + R_MFWD_FWSEQNGM27_OFFSET)
#define R_MFWD_FWSEQNGM28                 (R_MFWD_BASE + R_MFWD_FWSEQNGM28_OFFSET)
#define R_MFWD_FWSEQNGM29                 (R_MFWD_BASE + R_MFWD_FWSEQNGM29_OFFSET)
#define R_MFWD_FWSEQNGM30                 (R_MFWD_BASE + R_MFWD_FWSEQNGM30_OFFSET)
#define R_MFWD_FWSEQNGM31                 (R_MFWD_BASE + R_MFWD_FWSEQNGM31_OFFSET)
#define R_MFWD_FWSEQNRC                 (R_MFWD_BASE + R_MFWD_FWSEQNRC_OFFSET)
#define R_MFWD_FWCTFDCN0                 (R_MFWD_BASE + R_MFWD_FWCTFDCN0_OFFSET)
#define R_MFWD_FWCTFDCN1                 (R_MFWD_BASE + R_MFWD_FWCTFDCN1_OFFSET)
#define R_MFWD_FWLTHFDCN0                 (R_MFWD_BASE + R_MFWD_FWLTHFDCN0_OFFSET)
#define R_MFWD_FWLTHFDCN1                 (R_MFWD_BASE + R_MFWD_FWLTHFDCN1_OFFSET)
#define R_MFWD_FWLTHFDCN2                 (R_MFWD_BASE + R_MFWD_FWLTHFDCN2_OFFSET)
#define R_MFWD_FWLTWFDCN0                 (R_MFWD_BASE + R_MFWD_FWLTWFDCN0_OFFSET)
#define R_MFWD_FWLTWFDCN1                 (R_MFWD_BASE + R_MFWD_FWLTWFDCN1_OFFSET)
#define R_MFWD_FWLTWFDCN2                 (R_MFWD_BASE + R_MFWD_FWLTWFDCN2_OFFSET)
#define R_MFWD_FWPBFDCN0                 (R_MFWD_BASE + R_MFWD_FWPBFDCN0_OFFSET)
#define R_MFWD_FWPBFDCN1                 (R_MFWD_BASE + R_MFWD_FWPBFDCN1_OFFSET)
#define R_MFWD_FWPBFDCN2                 (R_MFWD_BASE + R_MFWD_FWPBFDCN2_OFFSET)
#define R_MFWD_FWMHLCN0                 (R_MFWD_BASE + R_MFWD_FWMHLCN0_OFFSET)
#define R_MFWD_FWMHLCN1                 (R_MFWD_BASE + R_MFWD_FWMHLCN1_OFFSET)
#define R_MFWD_FWMHLCN2                 (R_MFWD_BASE + R_MFWD_FWMHLCN2_OFFSET)
#define R_MFWD_FWDDFDCN2                 (R_MFWD_BASE + R_MFWD_FWDDFDCN2_OFFSET)
#define R_MFWD_FWWMRDCN0                 (R_MFWD_BASE + R_MFWD_FWWMRDCN0_OFFSET)
#define R_MFWD_FWWMRDCN1                 (R_MFWD_BASE + R_MFWD_FWWMRDCN1_OFFSET)
#define R_MFWD_FWWMRDCN2                 (R_MFWD_BASE + R_MFWD_FWWMRDCN2_OFFSET)
#define R_MFWD_FWCTRDCN0                 (R_MFWD_BASE + R_MFWD_FWCTRDCN0_OFFSET)
#define R_MFWD_FWCTRDCN1                 (R_MFWD_BASE + R_MFWD_FWCTRDCN1_OFFSET)
#define R_MFWD_FWLTHRDCN0                 (R_MFWD_BASE + R_MFWD_FWLTHRDCN0_OFFSET)
#define R_MFWD_FWLTHRDCN1                 (R_MFWD_BASE + R_MFWD_FWLTHRDCN1_OFFSET)
#define R_MFWD_FWLTHRDCN2                 (R_MFWD_BASE + R_MFWD_FWLTHRDCN2_OFFSET)
#define R_MFWD_FWLTWRDCN0                 (R_MFWD_BASE + R_MFWD_FWLTWRDCN0_OFFSET)
#define R_MFWD_FWLTWRDCN1                 (R_MFWD_BASE + R_MFWD_FWLTWRDCN1_OFFSET)
#define R_MFWD_FWLTWRDCN2                 (R_MFWD_BASE + R_MFWD_FWLTWRDCN2_OFFSET)
#define R_MFWD_FWPBRDCN0                 (R_MFWD_BASE + R_MFWD_FWPBRDCN0_OFFSET)
#define R_MFWD_FWPBRDCN1                 (R_MFWD_BASE + R_MFWD_FWPBRDCN1_OFFSET)
#define R_MFWD_FWPBRDCN2                 (R_MFWD_BASE + R_MFWD_FWPBRDCN2_OFFSET)
#define R_MFWD_FWDDRDCN2                 (R_MFWD_BASE + R_MFWD_FWDDRDCN2_OFFSET)
#define R_MFWD_FWPMFDCN00                 (R_MFWD_BASE + R_MFWD_FWPMFDCN00_OFFSET)
#define R_MFWD_FWPMFDCN01                 (R_MFWD_BASE + R_MFWD_FWPMFDCN01_OFFSET)
#define R_MFWD_FWPMFDCN02                 (R_MFWD_BASE + R_MFWD_FWPMFDCN02_OFFSET)
#define R_MFWD_FWPMFDCN03                 (R_MFWD_BASE + R_MFWD_FWPMFDCN03_OFFSET)
#define R_MFWD_FWPMFDCN04                 (R_MFWD_BASE + R_MFWD_FWPMFDCN04_OFFSET)
#define R_MFWD_FWPMFDCN05                 (R_MFWD_BASE + R_MFWD_FWPMFDCN05_OFFSET)
#define R_MFWD_FWPMFDCN06                 (R_MFWD_BASE + R_MFWD_FWPMFDCN06_OFFSET)
#define R_MFWD_FWPMFDCN07                 (R_MFWD_BASE + R_MFWD_FWPMFDCN07_OFFSET)
#define R_MFWD_FWPMFDCN08                 (R_MFWD_BASE + R_MFWD_FWPMFDCN08_OFFSET)
#define R_MFWD_FWPMFDCN09                 (R_MFWD_BASE + R_MFWD_FWPMFDCN09_OFFSET)
#define R_MFWD_FWPMFDCN10                 (R_MFWD_BASE + R_MFWD_FWPMFDCN10_OFFSET)
#define R_MFWD_FWPMFDCN11                 (R_MFWD_BASE + R_MFWD_FWPMFDCN11_OFFSET)
#define R_MFWD_FWPMFDCN12                 (R_MFWD_BASE + R_MFWD_FWPMFDCN12_OFFSET)
#define R_MFWD_FWPMFDCN13                 (R_MFWD_BASE + R_MFWD_FWPMFDCN13_OFFSET)
#define R_MFWD_FWPMFDCN14                 (R_MFWD_BASE + R_MFWD_FWPMFDCN14_OFFSET)
#define R_MFWD_FWPMFDCN15                 (R_MFWD_BASE + R_MFWD_FWPMFDCN15_OFFSET)
#define R_MFWD_FWPMGDCN00                 (R_MFWD_BASE + R_MFWD_FWPMGDCN00_OFFSET)
#define R_MFWD_FWPMGDCN01                 (R_MFWD_BASE + R_MFWD_FWPMGDCN01_OFFSET)
#define R_MFWD_FWPMGDCN02                 (R_MFWD_BASE + R_MFWD_FWPMGDCN02_OFFSET)
#define R_MFWD_FWPMGDCN03                 (R_MFWD_BASE + R_MFWD_FWPMGDCN03_OFFSET)
#define R_MFWD_FWPMGDCN04                 (R_MFWD_BASE + R_MFWD_FWPMGDCN04_OFFSET)
#define R_MFWD_FWPMGDCN05                 (R_MFWD_BASE + R_MFWD_FWPMGDCN05_OFFSET)
#define R_MFWD_FWPMGDCN06                 (R_MFWD_BASE + R_MFWD_FWPMGDCN06_OFFSET)
#define R_MFWD_FWPMGDCN07                 (R_MFWD_BASE + R_MFWD_FWPMGDCN07_OFFSET)
#define R_MFWD_FWPMGDCN08                 (R_MFWD_BASE + R_MFWD_FWPMGDCN08_OFFSET)
#define R_MFWD_FWPMGDCN09                 (R_MFWD_BASE + R_MFWD_FWPMGDCN09_OFFSET)
#define R_MFWD_FWPMGDCN10                 (R_MFWD_BASE + R_MFWD_FWPMGDCN10_OFFSET)
#define R_MFWD_FWPMGDCN11                 (R_MFWD_BASE + R_MFWD_FWPMGDCN11_OFFSET)
#define R_MFWD_FWPMGDCN12                 (R_MFWD_BASE + R_MFWD_FWPMGDCN12_OFFSET)
#define R_MFWD_FWPMGDCN13                 (R_MFWD_BASE + R_MFWD_FWPMGDCN13_OFFSET)
#define R_MFWD_FWPMGDCN14                 (R_MFWD_BASE + R_MFWD_FWPMGDCN14_OFFSET)
#define R_MFWD_FWPMGDCN15                 (R_MFWD_BASE + R_MFWD_FWPMGDCN15_OFFSET)
#define R_MFWD_FWPMGDCN16                 (R_MFWD_BASE + R_MFWD_FWPMGDCN16_OFFSET)
#define R_MFWD_FWPMGDCN17                 (R_MFWD_BASE + R_MFWD_FWPMGDCN17_OFFSET)
#define R_MFWD_FWPMGDCN18                 (R_MFWD_BASE + R_MFWD_FWPMGDCN18_OFFSET)
#define R_MFWD_FWPMGDCN19                 (R_MFWD_BASE + R_MFWD_FWPMGDCN19_OFFSET)
#define R_MFWD_FWPMGDCN20                 (R_MFWD_BASE + R_MFWD_FWPMGDCN20_OFFSET)
#define R_MFWD_FWPMGDCN21                 (R_MFWD_BASE + R_MFWD_FWPMGDCN21_OFFSET)
#define R_MFWD_FWPMGDCN22                 (R_MFWD_BASE + R_MFWD_FWPMGDCN22_OFFSET)
#define R_MFWD_FWPMGDCN23                 (R_MFWD_BASE + R_MFWD_FWPMGDCN23_OFFSET)
#define R_MFWD_FWPMGDCN24                 (R_MFWD_BASE + R_MFWD_FWPMGDCN24_OFFSET)
#define R_MFWD_FWPMGDCN25                 (R_MFWD_BASE + R_MFWD_FWPMGDCN25_OFFSET)
#define R_MFWD_FWPMGDCN26                 (R_MFWD_BASE + R_MFWD_FWPMGDCN26_OFFSET)
#define R_MFWD_FWPMGDCN27                 (R_MFWD_BASE + R_MFWD_FWPMGDCN27_OFFSET)
#define R_MFWD_FWPMGDCN28                 (R_MFWD_BASE + R_MFWD_FWPMGDCN28_OFFSET)
#define R_MFWD_FWPMGDCN29                 (R_MFWD_BASE + R_MFWD_FWPMGDCN29_OFFSET)
#define R_MFWD_FWPMGDCN30                 (R_MFWD_BASE + R_MFWD_FWPMGDCN30_OFFSET)
#define R_MFWD_FWPMGDCN31                 (R_MFWD_BASE + R_MFWD_FWPMGDCN31_OFFSET)
#define R_MFWD_FWPMYDCN0                 (R_MFWD_BASE + R_MFWD_FWPMYDCN0_OFFSET)
#define R_MFWD_FWPMYDCN1                 (R_MFWD_BASE + R_MFWD_FWPMYDCN1_OFFSET)
#define R_MFWD_FWPMYDCN2                 (R_MFWD_BASE + R_MFWD_FWPMYDCN2_OFFSET)
#define R_MFWD_FWPMYDCN3                 (R_MFWD_BASE + R_MFWD_FWPMYDCN3_OFFSET)
#define R_MFWD_FWPMYDCN4                 (R_MFWD_BASE + R_MFWD_FWPMYDCN4_OFFSET)
#define R_MFWD_FWPMYDCN5                 (R_MFWD_BASE + R_MFWD_FWPMYDCN5_OFFSET)
#define R_MFWD_FWPMYDCN6                 (R_MFWD_BASE + R_MFWD_FWPMYDCN6_OFFSET)
#define R_MFWD_FWPMYDCN7                 (R_MFWD_BASE + R_MFWD_FWPMYDCN7_OFFSET)
#define R_MFWD_FWPMRDCN00                 (R_MFWD_BASE + R_MFWD_FWPMRDCN00_OFFSET)
#define R_MFWD_FWPMRDCN01                 (R_MFWD_BASE + R_MFWD_FWPMRDCN01_OFFSET)
#define R_MFWD_FWPMRDCN02                 (R_MFWD_BASE + R_MFWD_FWPMRDCN02_OFFSET)
#define R_MFWD_FWPMRDCN03                 (R_MFWD_BASE + R_MFWD_FWPMRDCN03_OFFSET)
#define R_MFWD_FWPMRDCN04                 (R_MFWD_BASE + R_MFWD_FWPMRDCN04_OFFSET)
#define R_MFWD_FWPMRDCN05                 (R_MFWD_BASE + R_MFWD_FWPMRDCN05_OFFSET)
#define R_MFWD_FWPMRDCN06                 (R_MFWD_BASE + R_MFWD_FWPMRDCN06_OFFSET)
#define R_MFWD_FWPMRDCN07                 (R_MFWD_BASE + R_MFWD_FWPMRDCN07_OFFSET)
#define R_MFWD_FWPMRDCN08                 (R_MFWD_BASE + R_MFWD_FWPMRDCN08_OFFSET)
#define R_MFWD_FWPMRDCN09                 (R_MFWD_BASE + R_MFWD_FWPMRDCN09_OFFSET)
#define R_MFWD_FWPMRDCN10                 (R_MFWD_BASE + R_MFWD_FWPMRDCN10_OFFSET)
#define R_MFWD_FWPMRDCN11                 (R_MFWD_BASE + R_MFWD_FWPMRDCN11_OFFSET)
#define R_MFWD_FWPMRDCN12                 (R_MFWD_BASE + R_MFWD_FWPMRDCN12_OFFSET)
#define R_MFWD_FWPMRDCN13                 (R_MFWD_BASE + R_MFWD_FWPMRDCN13_OFFSET)
#define R_MFWD_FWPMRDCN14                 (R_MFWD_BASE + R_MFWD_FWPMRDCN14_OFFSET)
#define R_MFWD_FWPMRDCN15                 (R_MFWD_BASE + R_MFWD_FWPMRDCN15_OFFSET)
#define R_MFWD_FWPMRDCN16                 (R_MFWD_BASE + R_MFWD_FWPMRDCN16_OFFSET)
#define R_MFWD_FWPMRDCN17                 (R_MFWD_BASE + R_MFWD_FWPMRDCN17_OFFSET)
#define R_MFWD_FWPMRDCN18                 (R_MFWD_BASE + R_MFWD_FWPMRDCN18_OFFSET)
#define R_MFWD_FWPMRDCN19                 (R_MFWD_BASE + R_MFWD_FWPMRDCN19_OFFSET)
#define R_MFWD_FWPMRDCN20                 (R_MFWD_BASE + R_MFWD_FWPMRDCN20_OFFSET)
#define R_MFWD_FWPMRDCN21                 (R_MFWD_BASE + R_MFWD_FWPMRDCN21_OFFSET)
#define R_MFWD_FWPMRDCN22                 (R_MFWD_BASE + R_MFWD_FWPMRDCN22_OFFSET)
#define R_MFWD_FWPMRDCN23                 (R_MFWD_BASE + R_MFWD_FWPMRDCN23_OFFSET)
#define R_MFWD_FWPMRDCN24                 (R_MFWD_BASE + R_MFWD_FWPMRDCN24_OFFSET)
#define R_MFWD_FWPMRDCN25                 (R_MFWD_BASE + R_MFWD_FWPMRDCN25_OFFSET)
#define R_MFWD_FWPMRDCN26                 (R_MFWD_BASE + R_MFWD_FWPMRDCN26_OFFSET)
#define R_MFWD_FWPMRDCN27                 (R_MFWD_BASE + R_MFWD_FWPMRDCN27_OFFSET)
#define R_MFWD_FWPMRDCN28                 (R_MFWD_BASE + R_MFWD_FWPMRDCN28_OFFSET)
#define R_MFWD_FWPMRDCN29                 (R_MFWD_BASE + R_MFWD_FWPMRDCN29_OFFSET)
#define R_MFWD_FWPMRDCN30                 (R_MFWD_BASE + R_MFWD_FWPMRDCN30_OFFSET)
#define R_MFWD_FWPMRDCN31                 (R_MFWD_BASE + R_MFWD_FWPMRDCN31_OFFSET)
#define R_MFWD_FWFRPPCN000                 (R_MFWD_BASE + R_MFWD_FWFRPPCN000_OFFSET)
#define R_MFWD_FWFRPPCN001                 (R_MFWD_BASE + R_MFWD_FWFRPPCN001_OFFSET)
#define R_MFWD_FWFRPPCN002                 (R_MFWD_BASE + R_MFWD_FWFRPPCN002_OFFSET)
#define R_MFWD_FWFRPPCN003                 (R_MFWD_BASE + R_MFWD_FWFRPPCN003_OFFSET)
#define R_MFWD_FWFRPPCN004                 (R_MFWD_BASE + R_MFWD_FWFRPPCN004_OFFSET)
#define R_MFWD_FWFRPPCN005                 (R_MFWD_BASE + R_MFWD_FWFRPPCN005_OFFSET)
#define R_MFWD_FWFRPPCN006                 (R_MFWD_BASE + R_MFWD_FWFRPPCN006_OFFSET)
#define R_MFWD_FWFRPPCN007                 (R_MFWD_BASE + R_MFWD_FWFRPPCN007_OFFSET)
#define R_MFWD_FWFRPPCN008                 (R_MFWD_BASE + R_MFWD_FWFRPPCN008_OFFSET)
#define R_MFWD_FWFRPPCN009                 (R_MFWD_BASE + R_MFWD_FWFRPPCN009_OFFSET)
#define R_MFWD_FWFRPPCN010                 (R_MFWD_BASE + R_MFWD_FWFRPPCN010_OFFSET)
#define R_MFWD_FWFRPPCN011                 (R_MFWD_BASE + R_MFWD_FWFRPPCN011_OFFSET)
#define R_MFWD_FWFRPPCN012                 (R_MFWD_BASE + R_MFWD_FWFRPPCN012_OFFSET)
#define R_MFWD_FWFRPPCN013                 (R_MFWD_BASE + R_MFWD_FWFRPPCN013_OFFSET)
#define R_MFWD_FWFRPPCN014                 (R_MFWD_BASE + R_MFWD_FWFRPPCN014_OFFSET)
#define R_MFWD_FWFRPPCN015                 (R_MFWD_BASE + R_MFWD_FWFRPPCN015_OFFSET)
#define R_MFWD_FWFRPPCN016                 (R_MFWD_BASE + R_MFWD_FWFRPPCN016_OFFSET)
#define R_MFWD_FWFRPPCN017                 (R_MFWD_BASE + R_MFWD_FWFRPPCN017_OFFSET)
#define R_MFWD_FWFRPPCN018                 (R_MFWD_BASE + R_MFWD_FWFRPPCN018_OFFSET)
#define R_MFWD_FWFRPPCN019                 (R_MFWD_BASE + R_MFWD_FWFRPPCN019_OFFSET)
#define R_MFWD_FWFRPPCN020                 (R_MFWD_BASE + R_MFWD_FWFRPPCN020_OFFSET)
#define R_MFWD_FWFRPPCN021                 (R_MFWD_BASE + R_MFWD_FWFRPPCN021_OFFSET)
#define R_MFWD_FWFRPPCN022                 (R_MFWD_BASE + R_MFWD_FWFRPPCN022_OFFSET)
#define R_MFWD_FWFRPPCN023                 (R_MFWD_BASE + R_MFWD_FWFRPPCN023_OFFSET)
#define R_MFWD_FWFRPPCN024                 (R_MFWD_BASE + R_MFWD_FWFRPPCN024_OFFSET)
#define R_MFWD_FWFRPPCN025                 (R_MFWD_BASE + R_MFWD_FWFRPPCN025_OFFSET)
#define R_MFWD_FWFRPPCN026                 (R_MFWD_BASE + R_MFWD_FWFRPPCN026_OFFSET)
#define R_MFWD_FWFRPPCN027                 (R_MFWD_BASE + R_MFWD_FWFRPPCN027_OFFSET)
#define R_MFWD_FWFRPPCN028                 (R_MFWD_BASE + R_MFWD_FWFRPPCN028_OFFSET)
#define R_MFWD_FWFRPPCN029                 (R_MFWD_BASE + R_MFWD_FWFRPPCN029_OFFSET)
#define R_MFWD_FWFRPPCN030                 (R_MFWD_BASE + R_MFWD_FWFRPPCN030_OFFSET)
#define R_MFWD_FWFRPPCN031                 (R_MFWD_BASE + R_MFWD_FWFRPPCN031_OFFSET)
#define R_MFWD_FWFRPPCN032                 (R_MFWD_BASE + R_MFWD_FWFRPPCN032_OFFSET)
#define R_MFWD_FWFRPPCN033                 (R_MFWD_BASE + R_MFWD_FWFRPPCN033_OFFSET)
#define R_MFWD_FWFRPPCN034                 (R_MFWD_BASE + R_MFWD_FWFRPPCN034_OFFSET)
#define R_MFWD_FWFRPPCN035                 (R_MFWD_BASE + R_MFWD_FWFRPPCN035_OFFSET)
#define R_MFWD_FWFRPPCN036                 (R_MFWD_BASE + R_MFWD_FWFRPPCN036_OFFSET)
#define R_MFWD_FWFRPPCN037                 (R_MFWD_BASE + R_MFWD_FWFRPPCN037_OFFSET)
#define R_MFWD_FWFRPPCN038                 (R_MFWD_BASE + R_MFWD_FWFRPPCN038_OFFSET)
#define R_MFWD_FWFRPPCN039                 (R_MFWD_BASE + R_MFWD_FWFRPPCN039_OFFSET)
#define R_MFWD_FWFRPPCN040                 (R_MFWD_BASE + R_MFWD_FWFRPPCN040_OFFSET)
#define R_MFWD_FWFRPPCN041                 (R_MFWD_BASE + R_MFWD_FWFRPPCN041_OFFSET)
#define R_MFWD_FWFRPPCN042                 (R_MFWD_BASE + R_MFWD_FWFRPPCN042_OFFSET)
#define R_MFWD_FWFRPPCN043                 (R_MFWD_BASE + R_MFWD_FWFRPPCN043_OFFSET)
#define R_MFWD_FWFRPPCN044                 (R_MFWD_BASE + R_MFWD_FWFRPPCN044_OFFSET)
#define R_MFWD_FWFRPPCN045                 (R_MFWD_BASE + R_MFWD_FWFRPPCN045_OFFSET)
#define R_MFWD_FWFRPPCN046                 (R_MFWD_BASE + R_MFWD_FWFRPPCN046_OFFSET)
#define R_MFWD_FWFRPPCN047                 (R_MFWD_BASE + R_MFWD_FWFRPPCN047_OFFSET)
#define R_MFWD_FWFRPPCN048                 (R_MFWD_BASE + R_MFWD_FWFRPPCN048_OFFSET)
#define R_MFWD_FWFRPPCN049                 (R_MFWD_BASE + R_MFWD_FWFRPPCN049_OFFSET)
#define R_MFWD_FWFRPPCN050                 (R_MFWD_BASE + R_MFWD_FWFRPPCN050_OFFSET)
#define R_MFWD_FWFRPPCN051                 (R_MFWD_BASE + R_MFWD_FWFRPPCN051_OFFSET)
#define R_MFWD_FWFRPPCN052                 (R_MFWD_BASE + R_MFWD_FWFRPPCN052_OFFSET)
#define R_MFWD_FWFRPPCN053                 (R_MFWD_BASE + R_MFWD_FWFRPPCN053_OFFSET)
#define R_MFWD_FWFRPPCN054                 (R_MFWD_BASE + R_MFWD_FWFRPPCN054_OFFSET)
#define R_MFWD_FWFRPPCN055                 (R_MFWD_BASE + R_MFWD_FWFRPPCN055_OFFSET)
#define R_MFWD_FWFRPPCN056                 (R_MFWD_BASE + R_MFWD_FWFRPPCN056_OFFSET)
#define R_MFWD_FWFRPPCN057                 (R_MFWD_BASE + R_MFWD_FWFRPPCN057_OFFSET)
#define R_MFWD_FWFRPPCN058                 (R_MFWD_BASE + R_MFWD_FWFRPPCN058_OFFSET)
#define R_MFWD_FWFRPPCN059                 (R_MFWD_BASE + R_MFWD_FWFRPPCN059_OFFSET)
#define R_MFWD_FWFRPPCN060                 (R_MFWD_BASE + R_MFWD_FWFRPPCN060_OFFSET)
#define R_MFWD_FWFRPPCN061                 (R_MFWD_BASE + R_MFWD_FWFRPPCN061_OFFSET)
#define R_MFWD_FWFRPPCN062                 (R_MFWD_BASE + R_MFWD_FWFRPPCN062_OFFSET)
#define R_MFWD_FWFRPPCN063                 (R_MFWD_BASE + R_MFWD_FWFRPPCN063_OFFSET)
#define R_MFWD_FWFRPPCN064                 (R_MFWD_BASE + R_MFWD_FWFRPPCN064_OFFSET)
#define R_MFWD_FWFRPPCN065                 (R_MFWD_BASE + R_MFWD_FWFRPPCN065_OFFSET)
#define R_MFWD_FWFRPPCN066                 (R_MFWD_BASE + R_MFWD_FWFRPPCN066_OFFSET)
#define R_MFWD_FWFRPPCN067                 (R_MFWD_BASE + R_MFWD_FWFRPPCN067_OFFSET)
#define R_MFWD_FWFRPPCN068                 (R_MFWD_BASE + R_MFWD_FWFRPPCN068_OFFSET)
#define R_MFWD_FWFRPPCN069                 (R_MFWD_BASE + R_MFWD_FWFRPPCN069_OFFSET)
#define R_MFWD_FWFRPPCN070                 (R_MFWD_BASE + R_MFWD_FWFRPPCN070_OFFSET)
#define R_MFWD_FWFRPPCN071                 (R_MFWD_BASE + R_MFWD_FWFRPPCN071_OFFSET)
#define R_MFWD_FWFRPPCN072                 (R_MFWD_BASE + R_MFWD_FWFRPPCN072_OFFSET)
#define R_MFWD_FWFRPPCN073                 (R_MFWD_BASE + R_MFWD_FWFRPPCN073_OFFSET)
#define R_MFWD_FWFRPPCN074                 (R_MFWD_BASE + R_MFWD_FWFRPPCN074_OFFSET)
#define R_MFWD_FWFRPPCN075                 (R_MFWD_BASE + R_MFWD_FWFRPPCN075_OFFSET)
#define R_MFWD_FWFRPPCN076                 (R_MFWD_BASE + R_MFWD_FWFRPPCN076_OFFSET)
#define R_MFWD_FWFRPPCN077                 (R_MFWD_BASE + R_MFWD_FWFRPPCN077_OFFSET)
#define R_MFWD_FWFRPPCN078                 (R_MFWD_BASE + R_MFWD_FWFRPPCN078_OFFSET)
#define R_MFWD_FWFRPPCN079                 (R_MFWD_BASE + R_MFWD_FWFRPPCN079_OFFSET)
#define R_MFWD_FWFRPPCN080                 (R_MFWD_BASE + R_MFWD_FWFRPPCN080_OFFSET)
#define R_MFWD_FWFRPPCN081                 (R_MFWD_BASE + R_MFWD_FWFRPPCN081_OFFSET)
#define R_MFWD_FWFRPPCN082                 (R_MFWD_BASE + R_MFWD_FWFRPPCN082_OFFSET)
#define R_MFWD_FWFRPPCN083                 (R_MFWD_BASE + R_MFWD_FWFRPPCN083_OFFSET)
#define R_MFWD_FWFRPPCN084                 (R_MFWD_BASE + R_MFWD_FWFRPPCN084_OFFSET)
#define R_MFWD_FWFRPPCN085                 (R_MFWD_BASE + R_MFWD_FWFRPPCN085_OFFSET)
#define R_MFWD_FWFRPPCN086                 (R_MFWD_BASE + R_MFWD_FWFRPPCN086_OFFSET)
#define R_MFWD_FWFRPPCN087                 (R_MFWD_BASE + R_MFWD_FWFRPPCN087_OFFSET)
#define R_MFWD_FWFRPPCN088                 (R_MFWD_BASE + R_MFWD_FWFRPPCN088_OFFSET)
#define R_MFWD_FWFRPPCN089                 (R_MFWD_BASE + R_MFWD_FWFRPPCN089_OFFSET)
#define R_MFWD_FWFRPPCN090                 (R_MFWD_BASE + R_MFWD_FWFRPPCN090_OFFSET)
#define R_MFWD_FWFRPPCN091                 (R_MFWD_BASE + R_MFWD_FWFRPPCN091_OFFSET)
#define R_MFWD_FWFRPPCN092                 (R_MFWD_BASE + R_MFWD_FWFRPPCN092_OFFSET)
#define R_MFWD_FWFRPPCN093                 (R_MFWD_BASE + R_MFWD_FWFRPPCN093_OFFSET)
#define R_MFWD_FWFRPPCN094                 (R_MFWD_BASE + R_MFWD_FWFRPPCN094_OFFSET)
#define R_MFWD_FWFRPPCN095                 (R_MFWD_BASE + R_MFWD_FWFRPPCN095_OFFSET)
#define R_MFWD_FWFRPPCN096                 (R_MFWD_BASE + R_MFWD_FWFRPPCN096_OFFSET)
#define R_MFWD_FWFRPPCN097                 (R_MFWD_BASE + R_MFWD_FWFRPPCN097_OFFSET)
#define R_MFWD_FWFRPPCN098                 (R_MFWD_BASE + R_MFWD_FWFRPPCN098_OFFSET)
#define R_MFWD_FWFRPPCN099                 (R_MFWD_BASE + R_MFWD_FWFRPPCN099_OFFSET)
#define R_MFWD_FWFRPPCN100                 (R_MFWD_BASE + R_MFWD_FWFRPPCN100_OFFSET)
#define R_MFWD_FWFRPPCN101                 (R_MFWD_BASE + R_MFWD_FWFRPPCN101_OFFSET)
#define R_MFWD_FWFRPPCN102                 (R_MFWD_BASE + R_MFWD_FWFRPPCN102_OFFSET)
#define R_MFWD_FWFRPPCN103                 (R_MFWD_BASE + R_MFWD_FWFRPPCN103_OFFSET)
#define R_MFWD_FWFRPPCN104                 (R_MFWD_BASE + R_MFWD_FWFRPPCN104_OFFSET)
#define R_MFWD_FWFRPPCN105                 (R_MFWD_BASE + R_MFWD_FWFRPPCN105_OFFSET)
#define R_MFWD_FWFRPPCN106                 (R_MFWD_BASE + R_MFWD_FWFRPPCN106_OFFSET)
#define R_MFWD_FWFRPPCN107                 (R_MFWD_BASE + R_MFWD_FWFRPPCN107_OFFSET)
#define R_MFWD_FWFRPPCN108                 (R_MFWD_BASE + R_MFWD_FWFRPPCN108_OFFSET)
#define R_MFWD_FWFRPPCN109                 (R_MFWD_BASE + R_MFWD_FWFRPPCN109_OFFSET)
#define R_MFWD_FWFRPPCN110                 (R_MFWD_BASE + R_MFWD_FWFRPPCN110_OFFSET)
#define R_MFWD_FWFRPPCN111                 (R_MFWD_BASE + R_MFWD_FWFRPPCN111_OFFSET)
#define R_MFWD_FWFRPPCN112                 (R_MFWD_BASE + R_MFWD_FWFRPPCN112_OFFSET)
#define R_MFWD_FWFRPPCN113                 (R_MFWD_BASE + R_MFWD_FWFRPPCN113_OFFSET)
#define R_MFWD_FWFRPPCN114                 (R_MFWD_BASE + R_MFWD_FWFRPPCN114_OFFSET)
#define R_MFWD_FWFRPPCN115                 (R_MFWD_BASE + R_MFWD_FWFRPPCN115_OFFSET)
#define R_MFWD_FWFRPPCN116                 (R_MFWD_BASE + R_MFWD_FWFRPPCN116_OFFSET)
#define R_MFWD_FWFRPPCN117                 (R_MFWD_BASE + R_MFWD_FWFRPPCN117_OFFSET)
#define R_MFWD_FWFRPPCN118                 (R_MFWD_BASE + R_MFWD_FWFRPPCN118_OFFSET)
#define R_MFWD_FWFRPPCN119                 (R_MFWD_BASE + R_MFWD_FWFRPPCN119_OFFSET)
#define R_MFWD_FWFRPPCN120                 (R_MFWD_BASE + R_MFWD_FWFRPPCN120_OFFSET)
#define R_MFWD_FWFRPPCN121                 (R_MFWD_BASE + R_MFWD_FWFRPPCN121_OFFSET)
#define R_MFWD_FWFRPPCN122                 (R_MFWD_BASE + R_MFWD_FWFRPPCN122_OFFSET)
#define R_MFWD_FWFRPPCN123                 (R_MFWD_BASE + R_MFWD_FWFRPPCN123_OFFSET)
#define R_MFWD_FWFRPPCN124                 (R_MFWD_BASE + R_MFWD_FWFRPPCN124_OFFSET)
#define R_MFWD_FWFRPPCN125                 (R_MFWD_BASE + R_MFWD_FWFRPPCN125_OFFSET)
#define R_MFWD_FWFRPPCN126                 (R_MFWD_BASE + R_MFWD_FWFRPPCN126_OFFSET)
#define R_MFWD_FWFRPPCN127                 (R_MFWD_BASE + R_MFWD_FWFRPPCN127_OFFSET)
#define R_MFWD_FWFRDPCN000                 (R_MFWD_BASE + R_MFWD_FWFRDPCN000_OFFSET)
#define R_MFWD_FWFRDPCN001                 (R_MFWD_BASE + R_MFWD_FWFRDPCN001_OFFSET)
#define R_MFWD_FWFRDPCN002                 (R_MFWD_BASE + R_MFWD_FWFRDPCN002_OFFSET)
#define R_MFWD_FWFRDPCN003                 (R_MFWD_BASE + R_MFWD_FWFRDPCN003_OFFSET)
#define R_MFWD_FWFRDPCN004                 (R_MFWD_BASE + R_MFWD_FWFRDPCN004_OFFSET)
#define R_MFWD_FWFRDPCN005                 (R_MFWD_BASE + R_MFWD_FWFRDPCN005_OFFSET)
#define R_MFWD_FWFRDPCN006                 (R_MFWD_BASE + R_MFWD_FWFRDPCN006_OFFSET)
#define R_MFWD_FWFRDPCN007                 (R_MFWD_BASE + R_MFWD_FWFRDPCN007_OFFSET)
#define R_MFWD_FWFRDPCN008                 (R_MFWD_BASE + R_MFWD_FWFRDPCN008_OFFSET)
#define R_MFWD_FWFRDPCN009                 (R_MFWD_BASE + R_MFWD_FWFRDPCN009_OFFSET)
#define R_MFWD_FWFRDPCN010                 (R_MFWD_BASE + R_MFWD_FWFRDPCN010_OFFSET)
#define R_MFWD_FWFRDPCN011                 (R_MFWD_BASE + R_MFWD_FWFRDPCN011_OFFSET)
#define R_MFWD_FWFRDPCN012                 (R_MFWD_BASE + R_MFWD_FWFRDPCN012_OFFSET)
#define R_MFWD_FWFRDPCN013                 (R_MFWD_BASE + R_MFWD_FWFRDPCN013_OFFSET)
#define R_MFWD_FWFRDPCN014                 (R_MFWD_BASE + R_MFWD_FWFRDPCN014_OFFSET)
#define R_MFWD_FWFRDPCN015                 (R_MFWD_BASE + R_MFWD_FWFRDPCN015_OFFSET)
#define R_MFWD_FWFRDPCN016                 (R_MFWD_BASE + R_MFWD_FWFRDPCN016_OFFSET)
#define R_MFWD_FWFRDPCN017                 (R_MFWD_BASE + R_MFWD_FWFRDPCN017_OFFSET)
#define R_MFWD_FWFRDPCN018                 (R_MFWD_BASE + R_MFWD_FWFRDPCN018_OFFSET)
#define R_MFWD_FWFRDPCN019                 (R_MFWD_BASE + R_MFWD_FWFRDPCN019_OFFSET)
#define R_MFWD_FWFRDPCN020                 (R_MFWD_BASE + R_MFWD_FWFRDPCN020_OFFSET)
#define R_MFWD_FWFRDPCN021                 (R_MFWD_BASE + R_MFWD_FWFRDPCN021_OFFSET)
#define R_MFWD_FWFRDPCN022                 (R_MFWD_BASE + R_MFWD_FWFRDPCN022_OFFSET)
#define R_MFWD_FWFRDPCN023                 (R_MFWD_BASE + R_MFWD_FWFRDPCN023_OFFSET)
#define R_MFWD_FWFRDPCN024                 (R_MFWD_BASE + R_MFWD_FWFRDPCN024_OFFSET)
#define R_MFWD_FWFRDPCN025                 (R_MFWD_BASE + R_MFWD_FWFRDPCN025_OFFSET)
#define R_MFWD_FWFRDPCN026                 (R_MFWD_BASE + R_MFWD_FWFRDPCN026_OFFSET)
#define R_MFWD_FWFRDPCN027                 (R_MFWD_BASE + R_MFWD_FWFRDPCN027_OFFSET)
#define R_MFWD_FWFRDPCN028                 (R_MFWD_BASE + R_MFWD_FWFRDPCN028_OFFSET)
#define R_MFWD_FWFRDPCN029                 (R_MFWD_BASE + R_MFWD_FWFRDPCN029_OFFSET)
#define R_MFWD_FWFRDPCN030                 (R_MFWD_BASE + R_MFWD_FWFRDPCN030_OFFSET)
#define R_MFWD_FWFRDPCN031                 (R_MFWD_BASE + R_MFWD_FWFRDPCN031_OFFSET)
#define R_MFWD_FWFRDPCN032                 (R_MFWD_BASE + R_MFWD_FWFRDPCN032_OFFSET)
#define R_MFWD_FWFRDPCN033                 (R_MFWD_BASE + R_MFWD_FWFRDPCN033_OFFSET)
#define R_MFWD_FWFRDPCN034                 (R_MFWD_BASE + R_MFWD_FWFRDPCN034_OFFSET)
#define R_MFWD_FWFRDPCN035                 (R_MFWD_BASE + R_MFWD_FWFRDPCN035_OFFSET)
#define R_MFWD_FWFRDPCN036                 (R_MFWD_BASE + R_MFWD_FWFRDPCN036_OFFSET)
#define R_MFWD_FWFRDPCN037                 (R_MFWD_BASE + R_MFWD_FWFRDPCN037_OFFSET)
#define R_MFWD_FWFRDPCN038                 (R_MFWD_BASE + R_MFWD_FWFRDPCN038_OFFSET)
#define R_MFWD_FWFRDPCN039                 (R_MFWD_BASE + R_MFWD_FWFRDPCN039_OFFSET)
#define R_MFWD_FWFRDPCN040                 (R_MFWD_BASE + R_MFWD_FWFRDPCN040_OFFSET)
#define R_MFWD_FWFRDPCN041                 (R_MFWD_BASE + R_MFWD_FWFRDPCN041_OFFSET)
#define R_MFWD_FWFRDPCN042                 (R_MFWD_BASE + R_MFWD_FWFRDPCN042_OFFSET)
#define R_MFWD_FWFRDPCN043                 (R_MFWD_BASE + R_MFWD_FWFRDPCN043_OFFSET)
#define R_MFWD_FWFRDPCN044                 (R_MFWD_BASE + R_MFWD_FWFRDPCN044_OFFSET)
#define R_MFWD_FWFRDPCN045                 (R_MFWD_BASE + R_MFWD_FWFRDPCN045_OFFSET)
#define R_MFWD_FWFRDPCN046                 (R_MFWD_BASE + R_MFWD_FWFRDPCN046_OFFSET)
#define R_MFWD_FWFRDPCN047                 (R_MFWD_BASE + R_MFWD_FWFRDPCN047_OFFSET)
#define R_MFWD_FWFRDPCN048                 (R_MFWD_BASE + R_MFWD_FWFRDPCN048_OFFSET)
#define R_MFWD_FWFRDPCN049                 (R_MFWD_BASE + R_MFWD_FWFRDPCN049_OFFSET)
#define R_MFWD_FWFRDPCN050                 (R_MFWD_BASE + R_MFWD_FWFRDPCN050_OFFSET)
#define R_MFWD_FWFRDPCN051                 (R_MFWD_BASE + R_MFWD_FWFRDPCN051_OFFSET)
#define R_MFWD_FWFRDPCN052                 (R_MFWD_BASE + R_MFWD_FWFRDPCN052_OFFSET)
#define R_MFWD_FWFRDPCN053                 (R_MFWD_BASE + R_MFWD_FWFRDPCN053_OFFSET)
#define R_MFWD_FWFRDPCN054                 (R_MFWD_BASE + R_MFWD_FWFRDPCN054_OFFSET)
#define R_MFWD_FWFRDPCN055                 (R_MFWD_BASE + R_MFWD_FWFRDPCN055_OFFSET)
#define R_MFWD_FWFRDPCN056                 (R_MFWD_BASE + R_MFWD_FWFRDPCN056_OFFSET)
#define R_MFWD_FWFRDPCN057                 (R_MFWD_BASE + R_MFWD_FWFRDPCN057_OFFSET)
#define R_MFWD_FWFRDPCN058                 (R_MFWD_BASE + R_MFWD_FWFRDPCN058_OFFSET)
#define R_MFWD_FWFRDPCN059                 (R_MFWD_BASE + R_MFWD_FWFRDPCN059_OFFSET)
#define R_MFWD_FWFRDPCN060                 (R_MFWD_BASE + R_MFWD_FWFRDPCN060_OFFSET)
#define R_MFWD_FWFRDPCN061                 (R_MFWD_BASE + R_MFWD_FWFRDPCN061_OFFSET)
#define R_MFWD_FWFRDPCN062                 (R_MFWD_BASE + R_MFWD_FWFRDPCN062_OFFSET)
#define R_MFWD_FWFRDPCN063                 (R_MFWD_BASE + R_MFWD_FWFRDPCN063_OFFSET)
#define R_MFWD_FWFRDPCN064                 (R_MFWD_BASE + R_MFWD_FWFRDPCN064_OFFSET)
#define R_MFWD_FWFRDPCN065                 (R_MFWD_BASE + R_MFWD_FWFRDPCN065_OFFSET)
#define R_MFWD_FWFRDPCN066                 (R_MFWD_BASE + R_MFWD_FWFRDPCN066_OFFSET)
#define R_MFWD_FWFRDPCN067                 (R_MFWD_BASE + R_MFWD_FWFRDPCN067_OFFSET)
#define R_MFWD_FWFRDPCN068                 (R_MFWD_BASE + R_MFWD_FWFRDPCN068_OFFSET)
#define R_MFWD_FWFRDPCN069                 (R_MFWD_BASE + R_MFWD_FWFRDPCN069_OFFSET)
#define R_MFWD_FWFRDPCN070                 (R_MFWD_BASE + R_MFWD_FWFRDPCN070_OFFSET)
#define R_MFWD_FWFRDPCN071                 (R_MFWD_BASE + R_MFWD_FWFRDPCN071_OFFSET)
#define R_MFWD_FWFRDPCN072                 (R_MFWD_BASE + R_MFWD_FWFRDPCN072_OFFSET)
#define R_MFWD_FWFRDPCN073                 (R_MFWD_BASE + R_MFWD_FWFRDPCN073_OFFSET)
#define R_MFWD_FWFRDPCN074                 (R_MFWD_BASE + R_MFWD_FWFRDPCN074_OFFSET)
#define R_MFWD_FWFRDPCN075                 (R_MFWD_BASE + R_MFWD_FWFRDPCN075_OFFSET)
#define R_MFWD_FWFRDPCN076                 (R_MFWD_BASE + R_MFWD_FWFRDPCN076_OFFSET)
#define R_MFWD_FWFRDPCN077                 (R_MFWD_BASE + R_MFWD_FWFRDPCN077_OFFSET)
#define R_MFWD_FWFRDPCN078                 (R_MFWD_BASE + R_MFWD_FWFRDPCN078_OFFSET)
#define R_MFWD_FWFRDPCN079                 (R_MFWD_BASE + R_MFWD_FWFRDPCN079_OFFSET)
#define R_MFWD_FWFRDPCN080                 (R_MFWD_BASE + R_MFWD_FWFRDPCN080_OFFSET)
#define R_MFWD_FWFRDPCN081                 (R_MFWD_BASE + R_MFWD_FWFRDPCN081_OFFSET)
#define R_MFWD_FWFRDPCN082                 (R_MFWD_BASE + R_MFWD_FWFRDPCN082_OFFSET)
#define R_MFWD_FWFRDPCN083                 (R_MFWD_BASE + R_MFWD_FWFRDPCN083_OFFSET)
#define R_MFWD_FWFRDPCN084                 (R_MFWD_BASE + R_MFWD_FWFRDPCN084_OFFSET)
#define R_MFWD_FWFRDPCN085                 (R_MFWD_BASE + R_MFWD_FWFRDPCN085_OFFSET)
#define R_MFWD_FWFRDPCN086                 (R_MFWD_BASE + R_MFWD_FWFRDPCN086_OFFSET)
#define R_MFWD_FWFRDPCN087                 (R_MFWD_BASE + R_MFWD_FWFRDPCN087_OFFSET)
#define R_MFWD_FWFRDPCN088                 (R_MFWD_BASE + R_MFWD_FWFRDPCN088_OFFSET)
#define R_MFWD_FWFRDPCN089                 (R_MFWD_BASE + R_MFWD_FWFRDPCN089_OFFSET)
#define R_MFWD_FWFRDPCN090                 (R_MFWD_BASE + R_MFWD_FWFRDPCN090_OFFSET)
#define R_MFWD_FWFRDPCN091                 (R_MFWD_BASE + R_MFWD_FWFRDPCN091_OFFSET)
#define R_MFWD_FWFRDPCN092                 (R_MFWD_BASE + R_MFWD_FWFRDPCN092_OFFSET)
#define R_MFWD_FWFRDPCN093                 (R_MFWD_BASE + R_MFWD_FWFRDPCN093_OFFSET)
#define R_MFWD_FWFRDPCN094                 (R_MFWD_BASE + R_MFWD_FWFRDPCN094_OFFSET)
#define R_MFWD_FWFRDPCN095                 (R_MFWD_BASE + R_MFWD_FWFRDPCN095_OFFSET)
#define R_MFWD_FWFRDPCN096                 (R_MFWD_BASE + R_MFWD_FWFRDPCN096_OFFSET)
#define R_MFWD_FWFRDPCN097                 (R_MFWD_BASE + R_MFWD_FWFRDPCN097_OFFSET)
#define R_MFWD_FWFRDPCN098                 (R_MFWD_BASE + R_MFWD_FWFRDPCN098_OFFSET)
#define R_MFWD_FWFRDPCN099                 (R_MFWD_BASE + R_MFWD_FWFRDPCN099_OFFSET)
#define R_MFWD_FWFRDPCN100                 (R_MFWD_BASE + R_MFWD_FWFRDPCN100_OFFSET)
#define R_MFWD_FWFRDPCN101                 (R_MFWD_BASE + R_MFWD_FWFRDPCN101_OFFSET)
#define R_MFWD_FWFRDPCN102                 (R_MFWD_BASE + R_MFWD_FWFRDPCN102_OFFSET)
#define R_MFWD_FWFRDPCN103                 (R_MFWD_BASE + R_MFWD_FWFRDPCN103_OFFSET)
#define R_MFWD_FWFRDPCN104                 (R_MFWD_BASE + R_MFWD_FWFRDPCN104_OFFSET)
#define R_MFWD_FWFRDPCN105                 (R_MFWD_BASE + R_MFWD_FWFRDPCN105_OFFSET)
#define R_MFWD_FWFRDPCN106                 (R_MFWD_BASE + R_MFWD_FWFRDPCN106_OFFSET)
#define R_MFWD_FWFRDPCN107                 (R_MFWD_BASE + R_MFWD_FWFRDPCN107_OFFSET)
#define R_MFWD_FWFRDPCN108                 (R_MFWD_BASE + R_MFWD_FWFRDPCN108_OFFSET)
#define R_MFWD_FWFRDPCN109                 (R_MFWD_BASE + R_MFWD_FWFRDPCN109_OFFSET)
#define R_MFWD_FWFRDPCN110                 (R_MFWD_BASE + R_MFWD_FWFRDPCN110_OFFSET)
#define R_MFWD_FWFRDPCN111                 (R_MFWD_BASE + R_MFWD_FWFRDPCN111_OFFSET)
#define R_MFWD_FWFRDPCN112                 (R_MFWD_BASE + R_MFWD_FWFRDPCN112_OFFSET)
#define R_MFWD_FWFRDPCN113                 (R_MFWD_BASE + R_MFWD_FWFRDPCN113_OFFSET)
#define R_MFWD_FWFRDPCN114                 (R_MFWD_BASE + R_MFWD_FWFRDPCN114_OFFSET)
#define R_MFWD_FWFRDPCN115                 (R_MFWD_BASE + R_MFWD_FWFRDPCN115_OFFSET)
#define R_MFWD_FWFRDPCN116                 (R_MFWD_BASE + R_MFWD_FWFRDPCN116_OFFSET)
#define R_MFWD_FWFRDPCN117                 (R_MFWD_BASE + R_MFWD_FWFRDPCN117_OFFSET)
#define R_MFWD_FWFRDPCN118                 (R_MFWD_BASE + R_MFWD_FWFRDPCN118_OFFSET)
#define R_MFWD_FWFRDPCN119                 (R_MFWD_BASE + R_MFWD_FWFRDPCN119_OFFSET)
#define R_MFWD_FWFRDPCN120                 (R_MFWD_BASE + R_MFWD_FWFRDPCN120_OFFSET)
#define R_MFWD_FWFRDPCN121                 (R_MFWD_BASE + R_MFWD_FWFRDPCN121_OFFSET)
#define R_MFWD_FWFRDPCN122                 (R_MFWD_BASE + R_MFWD_FWFRDPCN122_OFFSET)
#define R_MFWD_FWFRDPCN123                 (R_MFWD_BASE + R_MFWD_FWFRDPCN123_OFFSET)
#define R_MFWD_FWFRDPCN124                 (R_MFWD_BASE + R_MFWD_FWFRDPCN124_OFFSET)
#define R_MFWD_FWFRDPCN125                 (R_MFWD_BASE + R_MFWD_FWFRDPCN125_OFFSET)
#define R_MFWD_FWFRDPCN126                 (R_MFWD_BASE + R_MFWD_FWFRDPCN126_OFFSET)
#define R_MFWD_FWFRDPCN127                 (R_MFWD_BASE + R_MFWD_FWFRDPCN127_OFFSET)
#define R_MFWD_FWEIS00                 (R_MFWD_BASE + R_MFWD_FWEIS00_OFFSET)
#define R_MFWD_FWEIS01                 (R_MFWD_BASE + R_MFWD_FWEIS01_OFFSET)
#define R_MFWD_FWEIS02                 (R_MFWD_BASE + R_MFWD_FWEIS02_OFFSET)
#define R_MFWD_FWEIE00                 (R_MFWD_BASE + R_MFWD_FWEIE00_OFFSET)
#define R_MFWD_FWEIE01                 (R_MFWD_BASE + R_MFWD_FWEIE01_OFFSET)
#define R_MFWD_FWEIE02                 (R_MFWD_BASE + R_MFWD_FWEIE02_OFFSET)
#define R_MFWD_FWEID00                 (R_MFWD_BASE + R_MFWD_FWEID00_OFFSET)
#define R_MFWD_FWEID01                 (R_MFWD_BASE + R_MFWD_FWEID01_OFFSET)
#define R_MFWD_FWEID02                 (R_MFWD_BASE + R_MFWD_FWEID02_OFFSET)
#define R_MFWD_FWEIS1                 (R_MFWD_BASE + R_MFWD_FWEIS1_OFFSET)
#define R_MFWD_FWEIE1                 (R_MFWD_BASE + R_MFWD_FWEIE1_OFFSET)
#define R_MFWD_FWEID1                 (R_MFWD_BASE + R_MFWD_FWEID1_OFFSET)
#define R_MFWD_FWEIS2                 (R_MFWD_BASE + R_MFWD_FWEIS2_OFFSET)
#define R_MFWD_FWEIE2                 (R_MFWD_BASE + R_MFWD_FWEIE2_OFFSET)
#define R_MFWD_FWEID2                 (R_MFWD_BASE + R_MFWD_FWEID2_OFFSET)
#define R_MFWD_FWEIS5                 (R_MFWD_BASE + R_MFWD_FWEIS5_OFFSET)
#define R_MFWD_FWEIE5                 (R_MFWD_BASE + R_MFWD_FWEIE5_OFFSET)
#define R_MFWD_FWEID5                 (R_MFWD_BASE + R_MFWD_FWEID5_OFFSET)
#define R_MFWD_FWEIS60                 (R_MFWD_BASE + R_MFWD_FWEIS60_OFFSET)
#define R_MFWD_FWEIE60                 (R_MFWD_BASE + R_MFWD_FWEIE60_OFFSET)
#define R_MFWD_FWEID60                 (R_MFWD_BASE + R_MFWD_FWEID60_OFFSET)
#define R_MFWD_FWEIS61                 (R_MFWD_BASE + R_MFWD_FWEIS61_OFFSET)
#define R_MFWD_FWEIE61                 (R_MFWD_BASE + R_MFWD_FWEIE61_OFFSET)
#define R_MFWD_FWEID61                 (R_MFWD_BASE + R_MFWD_FWEID61_OFFSET)
#define R_MFWD_FWEIS62                 (R_MFWD_BASE + R_MFWD_FWEIS62_OFFSET)
#define R_MFWD_FWEIE62                 (R_MFWD_BASE + R_MFWD_FWEIE62_OFFSET)
#define R_MFWD_FWEID62                 (R_MFWD_BASE + R_MFWD_FWEID62_OFFSET)
#define R_MFWD_FWEIS63                 (R_MFWD_BASE + R_MFWD_FWEIS63_OFFSET)
#define R_MFWD_FWEIE63                 (R_MFWD_BASE + R_MFWD_FWEIE63_OFFSET)
#define R_MFWD_FWEID63                 (R_MFWD_BASE + R_MFWD_FWEID63_OFFSET)
#define R_MFWD_FWEIS70                 (R_MFWD_BASE + R_MFWD_FWEIS70_OFFSET)
#define R_MFWD_FWEIE70                 (R_MFWD_BASE + R_MFWD_FWEIE70_OFFSET)
#define R_MFWD_FWEID70                 (R_MFWD_BASE + R_MFWD_FWEID70_OFFSET)
#define R_MFWD_FWEIS71                 (R_MFWD_BASE + R_MFWD_FWEIS71_OFFSET)
#define R_MFWD_FWEIE71                 (R_MFWD_BASE + R_MFWD_FWEIE71_OFFSET)
#define R_MFWD_FWEID71                 (R_MFWD_BASE + R_MFWD_FWEID71_OFFSET)
#define R_MFWD_FWEIS72                 (R_MFWD_BASE + R_MFWD_FWEIS72_OFFSET)
#define R_MFWD_FWEIE72                 (R_MFWD_BASE + R_MFWD_FWEIE72_OFFSET)
#define R_MFWD_FWEID72                 (R_MFWD_BASE + R_MFWD_FWEID72_OFFSET)
#define R_MFWD_FWEIS73                 (R_MFWD_BASE + R_MFWD_FWEIS73_OFFSET)
#define R_MFWD_FWEIE73                 (R_MFWD_BASE + R_MFWD_FWEIE73_OFFSET)
#define R_MFWD_FWEID73                 (R_MFWD_BASE + R_MFWD_FWEID73_OFFSET)
#define R_MFWD_FWEIS80                 (R_MFWD_BASE + R_MFWD_FWEIS80_OFFSET)
#define R_MFWD_FWEIE80                 (R_MFWD_BASE + R_MFWD_FWEIE80_OFFSET)
#define R_MFWD_FWEID80                 (R_MFWD_BASE + R_MFWD_FWEID80_OFFSET)
#define R_MFWD_FWEIS81                 (R_MFWD_BASE + R_MFWD_FWEIS81_OFFSET)
#define R_MFWD_FWEIE81                 (R_MFWD_BASE + R_MFWD_FWEIE81_OFFSET)
#define R_MFWD_FWEID81                 (R_MFWD_BASE + R_MFWD_FWEID81_OFFSET)
#define R_MFWD_FWEIS82                 (R_MFWD_BASE + R_MFWD_FWEIS82_OFFSET)
#define R_MFWD_FWEIE82                 (R_MFWD_BASE + R_MFWD_FWEIE82_OFFSET)
#define R_MFWD_FWEID82                 (R_MFWD_BASE + R_MFWD_FWEID82_OFFSET)
#define R_MFWD_FWEIS83                 (R_MFWD_BASE + R_MFWD_FWEIS83_OFFSET)
#define R_MFWD_FWEIE83                 (R_MFWD_BASE + R_MFWD_FWEIE83_OFFSET)
#define R_MFWD_FWEID83                 (R_MFWD_BASE + R_MFWD_FWEID83_OFFSET)
#define R_MFWD_FWMIS0                 (R_MFWD_BASE + R_MFWD_FWMIS0_OFFSET)
#define R_MFWD_FWMIE0                 (R_MFWD_BASE + R_MFWD_FWMIE0_OFFSET)
#define R_MFWD_FWMID0                 (R_MFWD_BASE + R_MFWD_FWMID0_OFFSET)

/* Register bit definitions */
/* FWGC Register bit definitions */
#define R_MFWD_FWGC_SVM_SHIFT                     (0)  /* Switch VLAN Mode */
#define R_MFWD_FWGC_SVM_MASK                      0x3
#  define R_MFWD_FWGC_SVM_00                              (0 << R_MFWD_FWGC_SVM_SHIFT)  /* No VLAN mode (VLAN not used for forwarding) */
#  define R_MFWD_FWGC_SVM_01                              (1 << R_MFWD_FWGC_SVM_SHIFT)  /* C-TAG mode (C-TAG used for forwarding) */
#  define R_MFWD_FWGC_SVM_10                              (2 << R_MFWD_FWGC_SVM_SHIFT)  /* SC-TAG mode (S-TAG used for forwarding) */
#  define R_MFWD_FWGC_SVM_11                              (3 << R_MFWD_FWGC_SVM_SHIFT)  /* Reserved */

/* FWTTC0 Register bit definitions */
#define R_MFWD_FWTTC0_CTT_SHIFT                   (0)  /* C-TAG TPID [801.2Q] */
#define R_MFWD_FWTTC0_CTT_MASK                    0xffff

#define R_MFWD_FWTTC0_STT_SHIFT                   (16)  /* S-TAG TPID [801.2Q] */
#define R_MFWD_FWTTC0_STT_MASK                    0xffff0000

/* FWTTC1 Register bit definitions */
#define R_MFWD_FWTTC1_RTT_SHIFT                   (0)  /* R-TAG TPID [801.2CB] */
#define R_MFWD_FWTTC1_RTT_MASK                    0xffff

/* FWCEPTC Register bit definitions */
#define R_MFWD_FWCEPTC_EPCSD_SHIFT                (0)  /* Exceptional Path CPU Sub Destination */
#define R_MFWD_FWCEPTC_EPCSD_MASK                 0x3f

#define R_MFWD_FWCEPTC_EPIPV_SHIFT                (12)  /* Exceptional Path Internal Priority Value */
#define R_MFWD_FWCEPTC_EPIPV_MASK                 0x7000

#define R_MFWD_FWCEPTC_EPCS                       (1 << 16)  /* Exceptional Path CPU Select */

#define R_MFWD_FWCEPTC_EPSL                       (1 << 24)  /* Exceptional Path Security Level */

/* FWCEPRC0 Register bit definitions */
#define R_MFWD_FWCEPRC0_EPHYEEF                   (1 << 0)  /* Ethernet PHY Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_EPCRCEEF                  (1 << 1)  /* Ethernet PCH CRC Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_ENIBEEF                   (1 << 2)  /* Ethernet Nibble Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_EFCSEEF                   (1 << 3)  /* Ethernet FCS Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_EFFMEEF                   (1 << 4)  /* Ethernet Final Fragment Missing Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_ECFSEEF                   (1 << 5)  /* Ethernet C-Fragment SMD Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_ECFFCEEF                  (1 << 6)  /* Ethernet C-Fragment FRAG_COUNT Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_ERFFEF                    (1 << 7)  /* Ethernet RMAC Frame Filtered Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_ERPOOEF                   (1 << 8)  /* Ethernet Reception Partially Out of Operation Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_EBOEEF                    (1 << 9)  /* Ethernet Buffer Overflow Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_EUEEF                     (1 << 10)  /* Ethernet Undersize Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_EOEEF                     (1 << 11)  /* Ethernet Oversize Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_ETFEF                     (1 << 12)  /* Ethernet TAG Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_GAXEEF                    (1 << 17)  /* GWCA AXI Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_GSEQEEF                   (1 << 18)  /* GWCA Sequence Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_GTFEF                     (1 << 20)  /* GWCA TAG Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_GDNEEF                    (1 << 21)  /* GWCA Descriptor Number Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_DDEEF                     (1 << 24)  /* Direct Descriptor Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_DDFSFEF                   (1 << 26)  /* Direct Descriptor Format Security Filtering Exceptional Forwarding */

/* FWCEPRC1 Register bit definitions */
#define R_MFWD_FWCEPRC1_FMSDUFEF                  (1 << 0)  /* MSDU Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC1_FMTRFEF                   (1 << 2)  /* Meter Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC1_FIFFEF                    (1 << 8)  /* Individual FRER Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC1_FSFFEF                    (1 << 9)  /* Sequence FRER Filtering Exceptional Forwarding */

/* FWCEPRC2 Register bit definitions */
#define R_MFWD_FWCEPRC2_FLTHUFEF                  (1 << 0)  /* Layer 3 Unknown Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FDMACUFEF                 (1 << 3)  /* Destination MAC Unknown Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FSMACUFEF                 (1 << 4)  /* Source MAC Unknown Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FVLANUFEF                 (1 << 5)  /* VLAN Unknown Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FDDNTFEF                  (1 << 8)  /* Direct Descriptor No Target Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FLTHNTFEF                 (1 << 9)  /* Layer 3 No Target Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FLTWNTFEF                 (1 << 11)  /* Layer 2 No Target Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FPBNTFEF                  (1 << 12)  /* Port Based No Target Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FLTHSLFEF                 (1 << 16)  /* Layer 3 Source Lock Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FDMACSLFEF                (1 << 19)  /* Destination MAC Source Lock Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FSMACSLFEF                (1 << 20)  /* Source MAC Source Lock Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FVLANSLFEF                (1 << 21)  /* VLAN Source Lock Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FWMFEF                    (1 << 26)  /* Watermark Filtering Exceptional Forwarding */

/* FWCLPTC Register bit definitions */
#define R_MFWD_FWCLPTC_LPCSD_SHIFT                (0)  /* Learning Path CPU Sub Destination */
#define R_MFWD_FWCLPTC_LPCSD_MASK                 0x3f

#define R_MFWD_FWCLPTC_LPIPV_SHIFT                (12)  /* Learning Path Internal Priority Value */
#define R_MFWD_FWCLPTC_LPIPV_MASK                 0x7000

#define R_MFWD_FWCLPTC_LPCS                       (1 << 16)  /* Learning Path CPU Select */

#define R_MFWD_FWCLPTC_LPSL                       (1 << 24)  /* Learning Path Security Level */

/* FWCLPRC Register bit definitions */
#define R_MFWD_FWCLPRC_USIDLF                     (1 << 0)  /* Unknown Stream ID Learning Forwarding */

#define R_MFWD_FWCLPRC_UDMACLF                    (1 << 4)  /* Unknown Destination MAC Learning Forwarding */

#define R_MFWD_FWCLPRC_USMACLF                    (1 << 5)  /* Unknown Source MAC Learning Forwarding */

#define R_MFWD_FWCLPRC_UPSMACLF                   (1 << 6)  /* Unknown Port for Source MAC Learning Forwarding */

#define R_MFWD_FWCLPRC_UVLANLF                    (1 << 7)  /* Unknown VLAN Learning Forwarding */

/* FWCMPTC Register bit definitions */
#define R_MFWD_FWCMPTC_CMPCSD_SHIFT               (0)  /* CPU Mirroring Path CPU Sub Destination */
#define R_MFWD_FWCMPTC_CMPCSD_MASK                0x3f

#define R_MFWD_FWCMPTC_CMPIPV_SHIFT               (12)  /* CPU Mirroring Path Internal Priority Value */
#define R_MFWD_FWCMPTC_CMPIPV_MASK                0x7000

#define R_MFWD_FWCMPTC_CMPIPU                     (1 << 15)  /* CPU Mirroring Path Internal Priority Update */

#define R_MFWD_FWCMPTC_CMPCS                      (1 << 16)  /* CPU Mirroring Path CPU Select */

#define R_MFWD_FWCMPTC_CMPSL                      (1 << 24)  /* CPU Mirroring Path Security Level */

/* FWEMPTC Register bit definitions */
#define R_MFWD_FWEMPTC_EMPIPV_SHIFT               (12)  /* Ethernet Mirroring Path Internal Priority Value */
#define R_MFWD_FWEMPTC_EMPIPV_MASK                0x7000

#define R_MFWD_FWEMPTC_EMPIPU                     (1 << 15)  /* Ethernet Mirroring Path Internal Priority Update */

#define R_MFWD_FWEMPTC_EMPPS                      (1 << 16)  /* Ethernet Mirroring Path Port Select */

#define R_MFWD_FWEMPTC_EMPSL                      (1 << 24)  /* Ethernet Mirroring Path Security Level */

/* FWSDMPTC Register bit definitions */
#define R_MFWD_FWSDMPTC_SDMPCSD_SHIFT             (0)  /* Source-Destination Mirroring Path CPU Sub Destination */
#define R_MFWD_FWSDMPTC_SDMPCSD_MASK              0x3f

#define R_MFWD_FWSDMPTC_SDMPIPV_SHIFT             (12)  /* Source-Destination Mirroring Path Internal Priority Value */
#define R_MFWD_FWSDMPTC_SDMPIPV_MASK              0x7000

#define R_MFWD_FWSDMPTC_SDMPIPU                   (1 << 15)  /* Source-Destination Mirroring Path Internal Priority Update */

#define R_MFWD_FWSDMPTC_SDMPPS_SHIFT              (16)  /* Source-Destination Mirroring Path Port Select */
#define R_MFWD_FWSDMPTC_SDMPPS_MASK               0x30000

#define R_MFWD_FWSDMPTC_SDMPSL                    (1 << 24)  /* Source-Destination Mirroring Path Security Level */

/* FWSDMPVC Register bit definitions */
#define R_MFWD_FWSDMPVC_SDMDV_SHIFT               (0)  /* Source-Destination Mirroring Destination Vector */
#define R_MFWD_FWSDMPVC_SDMDV_MASK                0x7

#define R_MFWD_FWSDMPVC_SDMSV_SHIFT               (16)  /* Source-Destination Mirroring Source Vector */
#define R_MFWD_FWSDMPVC_SDMSV_MASK                0x70000

/* FWLBWMC Register bit definitions */
#define R_MFWD_FWLBWMC_WMCLPR0                    (1 << 0)  /* Watermark Critical Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMCLPR1                    (1 << 1)  /* Watermark Critical Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMCLPR2                    (1 << 2)  /* Watermark Critical Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMCLPR3                    (1 << 3)  /* Watermark Critical Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMCLPR4                    (1 << 4)  /* Watermark Critical Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMCLPR5                    (1 << 5)  /* Watermark Critical Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMCLPR6                    (1 << 6)  /* Watermark Critical Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMCLPR7                    (1 << 7)  /* Watermark Critical Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMCLPR8                    (1 << 8)  /* Watermark Critical Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMCLPR9                    (1 << 9)  /* Watermark Critical Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMCLPR10                   (1 << 10)  /* Watermark Critical Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMCLPR11                   (1 << 11)  /* Watermark Critical Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMCLPR12                   (1 << 12)  /* Watermark Critical Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMCLPR13                   (1 << 13)  /* Watermark Critical Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMCLPR14                   (1 << 14)  /* Watermark Critical Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMCLPR15                   (1 << 15)  /* Watermark Critical Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMFLPR0                    (1 << 16)  /* Watermark Flush Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMFLPR1                    (1 << 17)  /* Watermark Flush Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMFLPR2                    (1 << 18)  /* Watermark Flush Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMFLPR3                    (1 << 19)  /* Watermark Flush Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMFLPR4                    (1 << 20)  /* Watermark Flush Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMFLPR5                    (1 << 21)  /* Watermark Flush Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMFLPR6                    (1 << 22)  /* Watermark Flush Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMFLPR7                    (1 << 23)  /* Watermark Flush Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMFLPR8                    (1 << 24)  /* Watermark Flush Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMFLPR9                    (1 << 25)  /* Watermark Flush Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMFLPR10                   (1 << 26)  /* Watermark Flush Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMFLPR11                   (1 << 27)  /* Watermark Flush Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMFLPR12                   (1 << 28)  /* Watermark Flush Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMFLPR13                   (1 << 29)  /* Watermark Flush Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMFLPR14                   (1 << 30)  /* Watermark Flush Level Priority n Reject (n = 0 to 15) */

#define R_MFWD_FWLBWMC_WMFLPR15                   (1 << 31)  /* Watermark Flush Level Priority n Reject (n = 0 to 15) */

/* FWPC Register bit definitions */
#define R_MFWD_FWPC_LTHTA                         (1 << 0)  /* L3 Table Active */

#define R_MFWD_FWPC_LTHRUS                        (1 << 1)  /* L3 Reject Unknown Streams */

#define R_MFWD_FWPC_LTHRUSS                       (1 << 2)  /* L3 Reject Unknown Secure Streams */

#define R_MFWD_FWPC_IP4UE                         (1 << 3)  /* IPv4 UDP Enable */

#define R_MFWD_FWPC_IP4TE                         (1 << 4)  /* IPv4 TCP Enable */

#define R_MFWD_FWPC_IP4OE                         (1 << 5)  /* IPv4 Other Enable */

#define R_MFWD_FWPC_IP6UE                         (1 << 6)  /* IPv6 UDP Enable */

#define R_MFWD_FWPC_IP6TE                         (1 << 7)  /* IPv6 TCP Enable */

#define R_MFWD_FWPC_IP6OE                         (1 << 8)  /* IPv6 Other Enable */

#define R_MFWD_FWPC_L2SE                          (1 << 9)  /* L2 Stream Enable */

#define R_MFWD_FWPC_MACDSA                        (1 << 20)  /* MAC Destination Search Active */

#define R_MFWD_FWPC_MACRUDA                       (1 << 21)  /* MAC Reject Unknown Destination Addresses */

#define R_MFWD_FWPC_MACRUDSA                      (1 << 22)  /* MAC Reject Unknown Destination Secure Addresses */

#define R_MFWD_FWPC_MACSSA                        (1 << 23)  /* MAC Source Search Active */

#define R_MFWD_FWPC_MACRUSA                       (1 << 24)  /* MAC Reject Unknown Source Addresses */

#define R_MFWD_FWPC_MACRUSSA                      (1 << 25)  /* MAC Reject Unknown Source Secure Addresses */

#define R_MFWD_FWPC_MACHLA                        (1 << 26)  /* MAC Hardware Learning Active */

#define R_MFWD_FWPC_MACHMA                        (1 << 27)  /* MAC Hardware Migration Active */

#define R_MFWD_FWPC_VLANSA                        (1 << 28)  /* VLAN Search Active */

#define R_MFWD_FWPC_VLANRU                        (1 << 29)  /* VLAN Reject Unknown */

#define R_MFWD_FWPC_VLANRUS                       (1 << 30)  /* VLAN Reject Unknown Secure */

/* FWPC Register bit definitions */
#define R_MFWD_FWPC_DDE                           (1 << 0)  /* Direct Descriptor Enable */

#define R_MFWD_FWPC_DDSL                          (1 << 1)  /* Direct Descriptor Security Level */

#define R_MFWD_FWPC_LTHFM0                        (1 << 16)  /* Layer 3 Forwarding Mask n (n = 0 to 2) */

#define R_MFWD_FWPC_LTHFM1                        (1 << 17)  /* Layer 3 Forwarding Mask n (n = 0 to 2) */

#define R_MFWD_FWPC_LTHFM2                        (1 << 18)  /* Layer 3 Forwarding Mask n (n = 0 to 2) */

/* FWPC Register bit definitions */
#define R_MFWD_FWPC_LTWFM0                        (1 << 16)  /* Layer 2 Forwarding Mask n (n = 0 to 2) */

#define R_MFWD_FWPC_LTWFM1                        (1 << 17)  /* Layer 2 Forwarding Mask n (n = 0 to 2) */

#define R_MFWD_FWPC_LTWFM2                        (1 << 18)  /* Layer 2 Forwarding Mask n (n = 0 to 2) */

/* FWCTGC Register bit definitions */
#define R_MFWD_FWCTGC_CTMDE                       (1 << 0)  /* Cut-Through MAC Destination Enable */

#define R_MFWD_FWCTGC_CTMSE                       (1 << 1)  /* Cut-Through MAC Source Enable */

#define R_MFWD_FWCTGC_CTCVE                       (1 << 2)  /* Cut-Through C-TAG VLAN Enable */

#define R_MFWD_FWCTGC_CTCPE                       (1 << 3)  /* Cut-Through C-TAG PCP Enable */

#define R_MFWD_FWCTGC_CTCDE                       (1 << 4)  /* Cut-Through C-TAG DEI Enable */

#define R_MFWD_FWCTGC_CTSVE                       (1 << 5)  /* Cut-Through S-TAG VLAN Enable */

#define R_MFWD_FWCTGC_CTSPE                       (1 << 6)  /* Cut-Through S-TAG PCP Enable */

#define R_MFWD_FWCTGC_CTSDE                       (1 << 7)  /* Cut-Through S-TAG DEI Enable */

#define R_MFWD_FWCTGC_CTETE                       (1 << 8)  /* Cut-Through Ethernet Type Enable */

#define R_MFWD_FWCTGC_CTFI                        (1 << 11)  /* Cut-Through FCS In */

#define R_MFWD_FWCTGC_CTVCTRL_SHIFT               (12)  /* Cut-Through VLAN Control [GWCA] [ETHA] */
#define R_MFWD_FWCTGC_CTVCTRL_MASK                0x3000
#  define R_MFWD_FWCTGC_CTVCTRL_00                        (0 << R_MFWD_FWCTGC_CTVCTRL_SHIFT)  /* The ingress matching separation rule i frame is a No TAG frame. */
#  define R_MFWD_FWCTGC_CTVCTRL_01                        (1 << R_MFWD_FWCTGC_CTVCTRL_SHIFT)  /* The ingress matching separation rule i frame is a C-TAG frame. */
#  define R_MFWD_FWCTGC_CTVCTRL_10                        (2 << R_MFWD_FWCTGC_CTVCTRL_SHIFT)  /* The ingress matching separation rule i frame is an SC-TAG frame. */
#  define R_MFWD_FWCTGC_CTVCTRL_11                        (3 << R_MFWD_FWCTGC_CTVCTRL_SHIFT)  /* The ingress matching separation rule i frame is a CoS TAG frame. */

#define R_MFWD_FWCTGC_CTRTGI                      (1 << 14)  /* Cut-Through R-TAG In [GWCA] [ETHA] */

/* FWCTGC Register bit definitions */
#define R_MFWD_FWCTGC_CTMT_SHIFT                  (0)  /* Cut-Through Maximum time */
#define R_MFWD_FWCTGC_CTMT_MASK                   0x3ffffff

/* FWCTTC Register bit definitions */
#define R_MFWD_FWCTTC_CTDV_SHIFT                  (0)  /* Cut-through Destination Vector */
#define R_MFWD_FWCTTC_CTDV_MASK                   0x7

#define R_MFWD_FWCTTC_CTDFM0                      (1 << 16)  /* Cut-Through Destination n Forwarding Mode (n = 0 to 1) */

#define R_MFWD_FWCTTC_CTDFM1                      (1 << 17)  /* Cut-Through Destination n Forwarding Mode (n = 0 to 1) */

/* FWCTTC Register bit definitions */
#define R_MFWD_FWCTTC_CTIPV_SHIFT                 (12)  /* Cut-through Internal Priority Value */
#define R_MFWD_FWCTTC_CTIPV_MASK                  0x7000

#define R_MFWD_FWCTTC_CTIPU                       (1 << 15)  /* Cut-through Internal Priority Update */

#define R_MFWD_FWCTTC_CTCME                       (1 << 16)  /* Cut-through CPU Mirroring Enable */

#define R_MFWD_FWCTTC_CTEME                       (1 << 17)  /* Cut-through Ethernet Mirroring Enable */

/* FWCTTC Register bit definitions */
#define R_MFWD_FWCTTC_CTCSD_SHIFT                 (0)  /* Cut-Through CPU Sub Destination */
#define R_MFWD_FWCTTC_CTCSD_MASK                  0x3f

/* FWCTSC Register bit definitions */
#define R_MFWD_FWCTSC_CTDMAU_SHIFT                (0)  /* Cut-Through Destination MAC Address Upper Part */
#define R_MFWD_FWCTSC_CTDMAU_MASK                 0xffffffff

/* FWCTSC Register bit definitions */
#define R_MFWD_FWCTSC_CTSMAU_SHIFT                (0)  /* Cut-Through Source MAC Address Upper Part */
#define R_MFWD_FWCTSC_CTSMAU_MASK                 0xffff

#define R_MFWD_FWCTSC_CTDMAL_SHIFT                (16)  /* Cut-Through Destination MAC Address Lower Part */
#define R_MFWD_FWCTSC_CTDMAL_MASK                 0xffff0000

/* FWCTSC Register bit definitions */
#define R_MFWD_FWCTSC_CTSMAL_SHIFT                (0)  /* Cut-Through Source MAC Address Lower Part */
#define R_MFWD_FWCTSC_CTSMAL_MASK                 0xffffffff

/* FWCTSC Register bit definitions */
#define R_MFWD_FWCTSC_CTCV_SHIFT                  (0)  /* Cut-Through C-TAG VLAN */
#define R_MFWD_FWCTSC_CTCV_MASK                   0xfff

#define R_MFWD_FWCTSC_CTCP_SHIFT                  (12)  /* Cut-Through C-TAG PCP */
#define R_MFWD_FWCTSC_CTCP_MASK                   0x7000

#define R_MFWD_FWCTSC_CTCD                        (1 << 15)  /* Cut-Through C-TAG DEI */

#define R_MFWD_FWCTSC_CTSV_SHIFT                  (16)  /* Cut-Through S-TAG VLAN */
#define R_MFWD_FWCTSC_CTSV_MASK                   0xfff0000

#define R_MFWD_FWCTSC_CTSP_SHIFT                  (28)  /* Cut-Through S-TAG PCP */
#define R_MFWD_FWCTSC_CTSP_MASK                   0x70000000

#define R_MFWD_FWCTSC_CTSD                        (1 << 31)  /* Cut-Through S-TAG DEI */

/* FWCTSC Register bit definitions */
#define R_MFWD_FWCTSC_CTET_SHIFT                  (0)  /* Cut-Through Ethernet Type */
#define R_MFWD_FWCTSC_CTET_MASK                   0xffff

#define R_MFWD_FWCTSC_CTSPN                       (1 << 16)  /* Cut-Through Source Port Number */

/* FWTWBFC Register bit definitions */
#define R_MFWD_FWTWBFC_TWBFUM_SHIFT               (0)  /* Two-Byte Filter Unit Mode */
#define R_MFWD_FWTWBFC_TWBFUM_MASK                0x3
#  define R_MFWD_FWTWBFC_TWBFUM_00                        (0 << R_MFWD_FWTWBFC_TWBFUM_SHIFT)  /* Mask mode */
#  define R_MFWD_FWTWBFC_TWBFUM_01                        (1 << R_MFWD_FWTWBFC_TWBFUM_SHIFT)  /* Expand mode */
#  define R_MFWD_FWTWBFC_TWBFUM_10                        (2 << R_MFWD_FWTWBFC_TWBFUM_SHIFT)  /* Precise mode */
#  define R_MFWD_FWTWBFC_TWBFUM_11                        (3 << R_MFWD_FWTWBFC_TWBFUM_SHIFT)  /* Reserved */

#define R_MFWD_FWTWBFC_TWBFM                      (1 << 8)  /* Two-Byte Filtering Mode */

#define R_MFWD_FWTWBFC_TWBFOV_SHIFT               (16)  /* Two-Byte Filter Offset Value */
#define R_MFWD_FWTWBFC_TWBFOV_MASK                0xff0000

/* FWTWBFVC Register bit definitions */
#define R_MFWD_FWTWBFVC_TWBFV0_SHIFT              (0)  /* Two-Byte Filter Value 0 */
#define R_MFWD_FWTWBFVC_TWBFV0_MASK               0xffff

#define R_MFWD_FWTWBFVC_TWBFV1_SHIFT              (16)  /* Two-Byte Filter Value 1 */
#define R_MFWD_FWTWBFVC_TWBFV1_MASK               0xffff0000

/* FWTHBFC Register bit definitions */
#define R_MFWD_FWTHBFC_THBFUM_SHIFT               (0)  /* Three-Byte Filter Unit Mode */
#define R_MFWD_FWTHBFC_THBFUM_MASK                0x3
#  define R_MFWD_FWTHBFC_THBFUM_00                        (0 << R_MFWD_FWTHBFC_THBFUM_SHIFT)  /* Mask mode */
#  define R_MFWD_FWTHBFC_THBFUM_01                        (1 << R_MFWD_FWTHBFC_THBFUM_SHIFT)  /* Expand mode */
#  define R_MFWD_FWTHBFC_THBFUM_10                        (2 << R_MFWD_FWTHBFC_THBFUM_SHIFT)  /* Precise mode */
#  define R_MFWD_FWTHBFC_THBFUM_11                        (3 << R_MFWD_FWTHBFC_THBFUM_SHIFT)  /* Reserved */

#define R_MFWD_FWTHBFC_THBFOV_SHIFT               (16)  /* Three-Byte Filter Offset Value */
#define R_MFWD_FWTHBFC_THBFOV_MASK                0xff0000

/* FWTHBFV0C Register bit definitions */
#define R_MFWD_FWTHBFV0C_THBFV0_SHIFT             (0)  /* Three-Byte Filter Value 0 */
#define R_MFWD_FWTHBFV0C_THBFV0_MASK              0xffffff

/* FWTHBFV1C Register bit definitions */
#define R_MFWD_FWTHBFV1C_THBFV1_SHIFT             (0)  /* Three-Byte Filter Value 1 */
#define R_MFWD_FWTHBFV1C_THBFV1_MASK              0xffffff

/* FWFOBFC Register bit definitions */
#define R_MFWD_FWFOBFC_FOBFUM_SHIFT               (0)  /* Four-Byte Filter Unit Mode */
#define R_MFWD_FWFOBFC_FOBFUM_MASK                0x3
#  define R_MFWD_FWFOBFC_FOBFUM_00                        (0 << R_MFWD_FWFOBFC_FOBFUM_SHIFT)  /* Mask mode */
#  define R_MFWD_FWFOBFC_FOBFUM_01                        (1 << R_MFWD_FWFOBFC_FOBFUM_SHIFT)  /* Expand mode */
#  define R_MFWD_FWFOBFC_FOBFUM_10                        (2 << R_MFWD_FWFOBFC_FOBFUM_SHIFT)  /* Precise mode */
#  define R_MFWD_FWFOBFC_FOBFUM_11                        (3 << R_MFWD_FWFOBFC_FOBFUM_SHIFT)  /* Reserved */

#define R_MFWD_FWFOBFC_FOBFOV_SHIFT               (16)  /* Four-Byte Filter Offset Value */
#define R_MFWD_FWFOBFC_FOBFOV_MASK                0xff0000

/* FWFOBFV0C Register bit definitions */
#define R_MFWD_FWFOBFV0C_FOBFV0_SHIFT             (0)  /* Four-Byte Filter Value 0 */
#define R_MFWD_FWFOBFV0C_FOBFV0_MASK              0xffffffff

/* FWFOBFV1C Register bit definitions */
#define R_MFWD_FWFOBFV1C_FOBFV1_SHIFT             (0)  /* Four-Byte Filter Value 1 */
#define R_MFWD_FWFOBFV1C_FOBFV1_MASK              0xffffffff

/* FWRFC Register bit definitions */
#define R_MFWD_FWRFC_RFM                          (1 << 8)  /* Range Filtering Mode */

#define R_MFWD_FWRFC_RFOV_SHIFT                   (16)  /* Range Filter Offset Value */
#define R_MFWD_FWRFC_RFOV_MASK                    0xff0000

/* FWRFVC Register bit definitions */
#define R_MFWD_FWRFVC_RFSV0_SHIFT                 (0)  /* Range Filter Start Value 0 */
#define R_MFWD_FWRFVC_RFSV0_MASK                  0xff

#define R_MFWD_FWRFVC_RFSV1_SHIFT                 (8)  /* Range Filter Start Value 1 */
#define R_MFWD_FWRFVC_RFSV1_MASK                  0xff00

#define R_MFWD_FWRFVC_RFRV_SHIFT                  (16)  /* Range Filter Range Value */
#define R_MFWD_FWRFVC_RFRV_MASK                   0xf0000

/* FWCFC Register bit definitions */
#define R_MFWD_FWCFC_CFEFFV2 TO CFEFFV0_SHIFT     (0)  /* Cascade Filter E-Frame Filter Valid n (n = 0 to 2) */
#define R_MFWD_FWCFC_CFEFFV2 TO CFEFFV0_MASK      0x7

#define R_MFWD_FWCFC_CFPFFV1 TO CFPFFV0_SHIFT     (16)  /* Cascade Filter E-Frame Filter Valid n (n = 0 to 1) */
#define R_MFWD_FWCFC_CFPFFV1 TO CFPFFV0_MASK      0x30000

/* FWCFMC Register bit definitions */
#define R_MFWD_FWCFMC_CFFN_SHIFT                  (0)  /* Cascade Filter Filter Number */
#define R_MFWD_FWCFMC_CFFN_MASK                   0x7f

#define R_MFWD_FWCFMC_CFFV                        (1 << 15)  /* Cascade Filter Valid */

/* FWCFMC Register bit definitions */
#define R_MFWD_FWCFMC_CFFN_SHIFT                  (0)  /* Cascade Filter Filter Number */
#define R_MFWD_FWCFMC_CFFN_MASK                   0x7f

#define R_MFWD_FWCFMC_CFFV                        (1 << 15)  /* Cascade Filter Valid */

/* FWCFMC Register bit definitions */
#define R_MFWD_FWCFMC_CFFN_SHIFT                  (0)  /* Cascade Filter Filter Number */
#define R_MFWD_FWCFMC_CFFN_MASK                   0x7f

#define R_MFWD_FWCFMC_CFFV                        (1 << 15)  /* Cascade Filter Valid */

/* FWCFMC Register bit definitions */
#define R_MFWD_FWCFMC_CFFN_SHIFT                  (0)  /* Cascade Filter Filter Number */
#define R_MFWD_FWCFMC_CFFN_MASK                   0x7f

#define R_MFWD_FWCFMC_CFFV                        (1 << 15)  /* Cascade Filter Valid */

/* FWCFMC Register bit definitions */
#define R_MFWD_FWCFMC_CFFN_SHIFT                  (0)  /* Cascade Filter Filter Number */
#define R_MFWD_FWCFMC_CFFN_MASK                   0x7f

#define R_MFWD_FWCFMC_CFFV                        (1 << 15)  /* Cascade Filter Valid */

/* FWCFMC Register bit definitions */
#define R_MFWD_FWCFMC_CFFN_SHIFT                  (0)  /* Cascade Filter Filter Number */
#define R_MFWD_FWCFMC_CFFN_MASK                   0x7f

#define R_MFWD_FWCFMC_CFFV                        (1 << 15)  /* Cascade Filter Valid */

/* FWCFMC Register bit definitions */
#define R_MFWD_FWCFMC_CFFN_SHIFT                  (0)  /* Cascade Filter Filter Number */
#define R_MFWD_FWCFMC_CFFN_MASK                   0x7f

#define R_MFWD_FWCFMC_CFFV                        (1 << 15)  /* Cascade Filter Valid */

/* FWIP4SC Register bit definitions */
#define R_MFWD_FWIP4SC_IP4IMDH                    (1 << 0)  /* IPv4 Include MAC Destination in Hash */

#define R_MFWD_FWIP4SC_IP4IMSH                    (1 << 1)  /* IPv4 Include MAC Source in Hash */

#define R_MFWD_FWIP4SC_IP4ISVH                    (1 << 2)  /* IPv4 Include S-TAG VLAN ID in Hash */

#define R_MFWD_FWIP4SC_IP4ISPH                    (1 << 3)  /* IPv4 Include S-TAG PCP in Hash */

#define R_MFWD_FWIP4SC_IP4ISDH                    (1 << 4)  /* IPv4 Include S-TAG DEI in Hash */

#define R_MFWD_FWIP4SC_IP4ICVH                    (1 << 5)  /* IPv4 Include C-TAG VLAN ID in Hash */

#define R_MFWD_FWIP4SC_IP4ICPH                    (1 << 6)  /* IPv4 Include C-TAG PCP in Hash */

#define R_MFWD_FWIP4SC_IP4ICDH                    (1 << 7)  /* IPv4 Include C-TAG DEI in Hash */

#define R_MFWD_FWIP4SC_IP4IISH                    (1 << 8)  /* IPv4 Include IP Source in Hash */

#define R_MFWD_FWIP4SC_IP4IIDH                    (1 << 9)  /* IPv4 Include IP Destination in Hash */

#define R_MFWD_FWIP4SC_IP4IPH                     (1 << 10)  /* IPv4 Include Protocol in Hash */

#define R_MFWD_FWIP4SC_IP4ISPTH                   (1 << 11)  /* IPv4 Include Source Port in Hash */

#define R_MFWD_FWIP4SC_IP4IDPTH                   (1 << 12)  /* IPv4 Include Destination Port in Hash */

#define R_MFWD_FWIP4SC_IP4ISVS                    (1 << 16)  /* IPv4 Include S-TAG VLAN ID in Stream */

#define R_MFWD_FWIP4SC_IP4ISPS                    (1 << 17)  /* IPv4 Include S-TAG PCP in Stream */

#define R_MFWD_FWIP4SC_IP4ISDS                    (1 << 18)  /* IPv4 Include S-TAG DEI in Stream */

#define R_MFWD_FWIP4SC_IP4ICVS                    (1 << 19)  /* IPv4 Include C-TAG VLAN ID in Stream */

#define R_MFWD_FWIP4SC_IP4ICPS                    (1 << 20)  /* IPv4 Include C-TAG PCP in Stream */

#define R_MFWD_FWIP4SC_IP4ICDS                    (1 << 21)  /* IPv4 Include C-TAG DEI in Stream */

#define R_MFWD_FWIP4SC_IP4IISS                    (1 << 22)  /* IPv4 Include IP Source in Stream */

#define R_MFWD_FWIP4SC_IP4IIDS                    (1 << 23)  /* IPv4 Include IP Destination in Stream */

#define R_MFWD_FWIP4SC_IP4IDPTS                   (1 << 24)  /* IPv4 Include Destination Port in Stream */

/* FWIP6SC Register bit definitions */
#define R_MFWD_FWIP6SC_IP6IMDH                    (1 << 0)  /* IPv6 Include MAC Destination in Hash */

#define R_MFWD_FWIP6SC_IP6IMSH                    (1 << 1)  /* IPv6 Include MAC Source in Hash */

#define R_MFWD_FWIP6SC_IP6ISVH                    (1 << 2)  /* IPv6 Include S-TAG VLAN ID in Hash */

#define R_MFWD_FWIP6SC_IP6ISPH                    (1 << 3)  /* IPv6 Include S-TAG PCP in Hash */

#define R_MFWD_FWIP6SC_IP6ISDH                    (1 << 4)  /* IPv6 Include S-TAG DEI in Hash */

#define R_MFWD_FWIP6SC_IP6ICVH                    (1 << 5)  /* IPv6 Include C-TAG VLAN ID in Hash */

#define R_MFWD_FWIP6SC_IP6ICPH                    (1 << 6)  /* IPv6 Include C-TAG PCP in Hash */

#define R_MFWD_FWIP6SC_IP6ICDH                    (1 << 7)  /* IPv6 Include C-TAG DEI in Hash */

#define R_MFWD_FWIP6SC_IP6IISH                    (1 << 8)  /* IPv6 Include IP Source in Hash */

#define R_MFWD_FWIP6SC_IP6IIDH                    (1 << 9)  /* IPv6 Include IP Destination in Hash */

#define R_MFWD_FWIP6SC_IP6IPH                     (1 << 10)  /* IPv6 Include Protocol in Hash (Next Header) */

#define R_MFWD_FWIP6SC_IP6ISPTH                   (1 << 11)  /* IPv6 Include Source Port in Hash */

#define R_MFWD_FWIP6SC_IP6IDPTH                   (1 << 12)  /* IPv6 Include Destination Port in Hash */

#define R_MFWD_FWIP6SC_IP6ISVS                    (1 << 16)  /* IPv6 Include S-TAG VLAN ID in Stream */

#define R_MFWD_FWIP6SC_IP6ISPS                    (1 << 17)  /* IPv6 Include S-TAG PCP in Stream */

#define R_MFWD_FWIP6SC_IP6ISDS                    (1 << 18)  /* IPv6 Include S-TAG DEI in Stream */

#define R_MFWD_FWIP6SC_IP6ICVS                    (1 << 19)  /* IPv6 Include C-TAG VLAN ID in Stream */

#define R_MFWD_FWIP6SC_IP6ICPS                    (1 << 20)  /* IPv6 Include C-TAG PCP in Stream */

#define R_MFWD_FWIP6SC_IP6ICDS                    (1 << 21)  /* IPv6 Include C-TAG DEI in Stream */

#define R_MFWD_FWIP6SC_IP6II0S                    (1 << 22)  /* IPv6 Include IP 0 in Stream */

#define R_MFWD_FWIP6SC_IP6II1S                    (1 << 23)  /* IPv6 Include IP 1 in Stream */

#define R_MFWD_FWIP6SC_IP6IDPTS                   (1 << 24)  /* IPv6 Include Destination Port in Stream */

/* FWIP6OC Register bit definitions */
#define R_MFWD_FWIP6OC_IP6IPOM0                   (1 << 0)  /* IPv6 IP Offset mode 0 */

#define R_MFWD_FWIP6OC_IP6IPO0_SHIFT              (4)  /* IPv6 IP Offset 0 */
#define R_MFWD_FWIP6OC_IP6IPO0_MASK               0xf0

#define R_MFWD_FWIP6OC_IP6IPOM1                   (1 << 16)  /* IPv6 IP Offset mode 1 */

#define R_MFWD_FWIP6OC_IP6IPO1_SHIFT              (20)  /* IPv6 IP Offset 1 */
#define R_MFWD_FWIP6OC_IP6IPO1_MASK               0xf00000

/* FWL2SC Register bit definitions */
#define R_MFWD_FWL2SC_L2IMDS                      (1 << 0)  /* Layer 2 Include MAC Destination in Stream */

#define R_MFWD_FWL2SC_L2IMSS                      (1 << 1)  /* Layer 2 Include MAC Source in Stream */

#define R_MFWD_FWL2SC_L2ISVS                      (1 << 2)  /* Layer 2 Include S-TAG VLAN ID in Stream */

#define R_MFWD_FWL2SC_L2ISPS                      (1 << 3)  /* Layer 2 Include S-TAG PCP ID in Stream */

#define R_MFWD_FWL2SC_L2ISDS                      (1 << 4)  /* Layer 2 Include S-TAG DEI in Stream */

#define R_MFWD_FWL2SC_L2ICVS                      (1 << 5)  /* Layer 2 Include C-TAG VLAN ID in Stream */

#define R_MFWD_FWL2SC_L2ICPS                      (1 << 6)  /* Layer 2 Include C-TAG PCP ID in Stream */

#define R_MFWD_FWL2SC_L2ICDS                      (1 << 7)  /* Layer 2 Include C-TAG DEI in Stream */

/* FWSFHEC Register bit definitions */
#define R_MFWD_FWSFHEC_IP4HE15 TO IP4HE0_SHIFT    (0)  /* IPv4 Stream Filter Hash Equation n (n = 0 to 15) */
#define R_MFWD_FWSFHEC_IP4HE15 TO IP4HE0_MASK     0xffff

#define R_MFWD_FWSFHEC_IP6HE15 TO IP6HE0_SHIFT    (16)  /* IPv6 Stream Filter Hash Equation n (n = 0 to 15) */
#define R_MFWD_FWSFHEC_IP6HE15 TO IP6HE0_MASK     0xffff0000

/* FWSHCR0 Register bit definitions */
#define R_MFWD_FWSHCR0_SHCMDP0_SHIFT              (0)  /* Software Hash Calculation MAC Destination Part 0 */
#define R_MFWD_FWSHCR0_SHCMDP0_MASK               0xffffffff

/* FWSHCR1 Register bit definitions */
#define R_MFWD_FWSHCR1_SHCMSP0_SHIFT              (0)  /* Software Hash Calculation MAC Source Part 0 */
#define R_MFWD_FWSHCR1_SHCMSP0_MASK               0xffff

#define R_MFWD_FWSHCR1_SHCMDP1_SHIFT              (16)  /* Software Hash Calculation MAC Destination Part 1 */
#define R_MFWD_FWSHCR1_SHCMDP1_MASK               0xffff0000

/* FWSHCR2 Register bit definitions */
#define R_MFWD_FWSHCR2_SHCMSP1_SHIFT              (0)  /* Software Hash Calculation MAC Source Part 1 */
#define R_MFWD_FWSHCR2_SHCMSP1_MASK               0xffffffff

/* FWSHCR3 Register bit definitions */
#define R_MFWD_FWSHCR3_SHCCV_SHIFT                (0)  /* Software Hash Calculation C-TAG VLAN */
#define R_MFWD_FWSHCR3_SHCCV_MASK                 0xfff

#define R_MFWD_FWSHCR3_SHCCD                      (1 << 12)  /* Software Hash Calculation C-TAG DEI */

#define R_MFWD_FWSHCR3_SHCCP_SHIFT                (13)  /* Software Hash Calculation C-TAG PCP */
#define R_MFWD_FWSHCR3_SHCCP_MASK                 0xe000

#define R_MFWD_FWSHCR3_SHCSV_SHIFT                (16)  /* Software Hash Calculation S-TAG VLANs */
#define R_MFWD_FWSHCR3_SHCSV_MASK                 0xfff0000

#define R_MFWD_FWSHCR3_SHCSD                      (1 << 28)  /* Software Hash Calculation S-TAG DEI */

#define R_MFWD_FWSHCR3_SHCSP_SHIFT                (29)  /* Software Hash Calculation S-TAG PCP */
#define R_MFWD_FWSHCR3_SHCSP_MASK                 0xe0000000

/* FWSHCR4 Register bit definitions */
#define R_MFWD_FWSHCR4_SHCP_SHIFT                 (0)  /* Software Hash Calculation Protocol (NextHeader for IPv6) */
#define R_MFWD_FWSHCR4_SHCP_MASK                  0xff

#define R_MFWD_FWSHCR4_SHCFF                      (1 << 16)  /* Software Hash Calculation Frame Format */

/* FWSHCR5 Register bit definitions */
#define R_MFWD_FWSHCR5_SHCISP0_SHIFT              (0)  /* Software Hash Calculation IP Source Part 0 */
#define R_MFWD_FWSHCR5_SHCISP0_MASK               0xffffffff

/* FWSHCR6 Register bit definitions */
#define R_MFWD_FWSHCR6_SHCISP1_SHIFT              (0)  /* Software Hash Calculation IP Source Part 1 */
#define R_MFWD_FWSHCR6_SHCISP1_MASK               0xffffffff

/* FWSHCR7 Register bit definitions */
#define R_MFWD_FWSHCR7_SHCISP2_SHIFT              (0)  /* Software Hash Calculation IP Source Part 2 */
#define R_MFWD_FWSHCR7_SHCISP2_MASK               0xffffffff

/* FWSHCR8 Register bit definitions */
#define R_MFWD_FWSHCR8_SHCISP3_SHIFT              (0)  /* Software Hash Calculation IP Source Part 3 */
#define R_MFWD_FWSHCR8_SHCISP3_MASK               0xffffffff

/* FWSHCR9 Register bit definitions */
#define R_MFWD_FWSHCR9_SHCIDP0_SHIFT              (0)  /* Software Hash Calculation IP Destination Part 0 */
#define R_MFWD_FWSHCR9_SHCIDP0_MASK               0xffffffff

/* FWSHCR10 Register bit definitions */
#define R_MFWD_FWSHCR10_SHCIDP1_SHIFT             (0)  /* Software Hash Calculation IP Source Destination Part 1 */
#define R_MFWD_FWSHCR10_SHCIDP1_MASK              0xffffffff

/* FWSHCR11 Register bit definitions */
#define R_MFWD_FWSHCR11_SHCIDP2_SHIFT             (0)  /* Software Hash Calculation IP Destination Part 2 */
#define R_MFWD_FWSHCR11_SHCIDP2_MASK              0xffffffff

/* FWSHCR12 Register bit definitions */
#define R_MFWD_FWSHCR12_SHCIDP3_SHIFT             (0)  /* Software Hash Calculation IP Destination Part 3 */
#define R_MFWD_FWSHCR12_SHCIDP3_MASK              0xffffffff

/* FWSHCR13 Register bit definitions */
#define R_MFWD_FWSHCR13_SHCDP_SHIFT               (0)  /* Software Hash Calculation Destination Port */
#define R_MFWD_FWSHCR13_SHCDP_MASK                0xffff

#define R_MFWD_FWSHCR13_SHCSP_SHIFT               (16)  /* Software Hash Calculation Source Port */
#define R_MFWD_FWSHCR13_SHCSP_MASK                0xffff0000

/* FWSHCRR Register bit definitions */
#define R_MFWD_FWSHCRR_SHCR_SHIFT                 (0)  /* Software Hash Calculation Result */
#define R_MFWD_FWSHCRR_SHCR_MASK                  0xffff

#define R_MFWD_FWSHCRR_SHC                        (1 << 31)  /* Software Hash Calculation */

/* FWLTHHEC Register bit definitions */
#define R_MFWD_FWLTHHEC_LTHHMC_SHIFT              (0)  /* L3 Hash Maximum Collision */
#define R_MFWD_FWLTHHEC_LTHHMC_MASK               0xff

#define R_MFWD_FWLTHHEC_LTHHMUE_SHIFT             (16)  /* L3 Hash Maximum Unsecure Entry */
#define R_MFWD_FWLTHHEC_LTHHMUE_MASK              0x1ff0000

/* FWLTHHC Register bit definitions */
#define R_MFWD_FWLTHHC_LTHHE7 TO LTHHE0_SHIFT     (0)  /* L3 Hash Equation n (n = 0 to 7) */
#define R_MFWD_FWLTHHC_LTHHE7 TO LTHHE0_MASK      0xff

/* FWLTHTL0 Register bit definitions */
#define R_MFWD_FWLTHTL0_LTHSLP0_SHIFT             (0)  /* L3 Stream Learn Part 0 */
#define R_MFWD_FWLTHTL0_LTHSLP0_MASK              0x7

#define R_MFWD_FWLTHTL0_LTHSLL                    (1 << 8)  /* L3 Security Level Learn */

#define R_MFWD_FWLTHTL0_LTHED                     (1 << 16)  /* L3 Entry Delete */

/* FWLTHTL1 Register bit definitions */
#define R_MFWD_FWLTHTL1_LTHSLP1_SHIFT             (0)  /* L3 Stream Learn Part 1 */
#define R_MFWD_FWLTHTL1_LTHSLP1_MASK              0xffffffff

/* FWLTHTL2 Register bit definitions */
#define R_MFWD_FWLTHTL2_LTHSLP2_SHIFT             (0)  /* L3 Stream Learn Part 2 */
#define R_MFWD_FWLTHTL2_LTHSLP2_MASK              0xffffffff

/* FWLTHTL3 Register bit definitions */
#define R_MFWD_FWLTHTL3_LTHSLP3_SHIFT             (0)  /* L3 Stream Learn Part 3 */
#define R_MFWD_FWLTHTL3_LTHSLP3_MASK              0xffffffff

/* FWLTHTL4 Register bit definitions */
#define R_MFWD_FWLTHTL4_LTHSLP4_SHIFT             (0)  /* L3 Stream Learn Part 4 */
#define R_MFWD_FWLTHTL4_LTHSLP4_MASK              0xffffffff

/* FWLTHTL5 Register bit definitions */
#define R_MFWD_FWLTHTL5_LTHMSDUNL_SHIFT           (16)  /* L3 MSDU Number Learn */
#define R_MFWD_FWLTHTL5_LTHMSDUNL_MASK            0xf0000

#define R_MFWD_FWLTHTL5_LTHMSDUVL                 (1 << 31)  /* L3 MSDU Valid Learn */

/* FWLTHTL6 Register bit definitions */
#define R_MFWD_FWLTHTL6_LTHFRERNL_SHIFT           (0)  /* L3 FRER Number Learn */
#define R_MFWD_FWLTHTL6_LTHFRERNL_MASK            0x7f

#define R_MFWD_FWLTHTL6_LTHFRERVL                 (1 << 15)  /* L3 FRER Valid Learn */

#define R_MFWD_FWLTHTL6_LTHMTRNL_SHIFT            (16)  /* L3 Meter Number Learn */
#define R_MFWD_FWLTHTL6_LTHMTRNL_MASK             0x1f0000

#define R_MFWD_FWLTHTL6_LTHMTRVL                  (1 << 31)  /* L3 Meter Valid Learn */

/* FWLTHTL7 Register bit definitions */
#define R_MFWD_FWLTHTL7_LTHRNL_SHIFT              (0)  /* L3 Routing Number Learn */
#define R_MFWD_FWLTHTL7_LTHRNL_MASK               0xff

#define R_MFWD_FWLTHTL7_LTHRVL                    (1 << 15)  /* L3 Routing Valid Learn */

#define R_MFWD_FWLTHTL7_LTHSLVL_SHIFT             (16)  /* L3 Source Lock Vector Learn */
#define R_MFWD_FWLTHTL7_LTHSLVL_MASK              0x70000

/* FWLTHTL80 Register bit definitions */
#define R_MFWD_FWLTHTL80_LTHCSDL_SHIFT            (0)  /* L3 CPU Sub-Destination Learn */
#define R_MFWD_FWLTHTL80_LTHCSDL_MASK             0x3f

/* FWLTHTL9 Register bit definitions */
#define R_MFWD_FWLTHTL9_LTHDVL_SHIFT              (0)  /* L3 Destination Vector Learn */
#define R_MFWD_FWLTHTL9_LTHDVL_MASK               0x7

#define R_MFWD_FWLTHTL9_LTHIPVL_SHIFT             (16)  /* L3 Internal Priority Value Learn */
#define R_MFWD_FWLTHTL9_LTHIPVL_MASK              0x70000

#define R_MFWD_FWLTHTL9_LTHIPUL                   (1 << 19)  /* L3 Internal Priority Update Learn */

#define R_MFWD_FWLTHTL9_LTHEMEL                   (1 << 20)  /* L3 Ethernet Mirroring Enable Learn */

#define R_MFWD_FWLTHTL9_LTHCMEL                   (1 << 21)  /* L3 CPU Mirroring Enable Learn */

/* FWLTHTLR Register bit definitions */
#define R_MFWD_FWLTHTLR_LTHLF                     (1 << 0)  /* L3 Learn Fail */

#define R_MFWD_FWLTHTLR_LTHLSF                    (1 << 1)  /* L3 Learn Security Fail */

#define R_MFWD_FWLTHTLR_LTHLO                     (1 << 3)  /* L3 Learn Overwrite */

#define R_MFWD_FWLTHTLR_LTHLCN_SHIFT              (16)  /* L3 Learn Collision Number */
#define R_MFWD_FWLTHTLR_LTHLCN_MASK               0xff0000

#define R_MFWD_FWLTHTLR_LTHTL                     (1 << 31)  /* L3 Table Learn */

/* FWLTHTIM Register bit definitions */
#define R_MFWD_FWLTHTIM_LTHTIOG                   (1 << 0)  /* L3 Table Initialization Ongoing */

#define R_MFWD_FWLTHTIM_LTHTR                     (1 << 1)  /* L3 Table Ready */

/* FWLTHTEM Register bit definitions */
#define R_MFWD_FWLTHTEM_LTHTEN_SHIFT              (0)  /* L3 Table Entry Number */
#define R_MFWD_FWLTHTEM_LTHTEN_MASK               0x1ff

#define R_MFWD_FWLTHTEM_LTHTUEN_SHIFT             (16)  /* L3 Table Unsecure Entry Number */
#define R_MFWD_FWLTHTEM_LTHTUEN_MASK              0x1ff0000

/* FWLTHTS0 Register bit definitions */
#define R_MFWD_FWLTHTS0_LTHSSP0_SHIFT             (0)  /* L3 Stream Search Part 0 */
#define R_MFWD_FWLTHTS0_LTHSSP0_MASK              0x7

/* FWLTHTS1 Register bit definitions */
#define R_MFWD_FWLTHTS1_LTHSSP1_SHIFT             (0)  /* L3 Stream Search Part 1 */
#define R_MFWD_FWLTHTS1_LTHSSP1_MASK              0xffffffff

/* FWLTHTS2 Register bit definitions */
#define R_MFWD_FWLTHTS2_LTHSSP2_SHIFT             (0)  /* L3 Stream Search Part 2 */
#define R_MFWD_FWLTHTS2_LTHSSP2_MASK              0xffffffff

/* FWLTHTS3 Register bit definitions */
#define R_MFWD_FWLTHTS3_LTHSSP3_SHIFT             (0)  /* L3 Stream Search Part 3 */
#define R_MFWD_FWLTHTS3_LTHSSP3_MASK              0xffffffff

/* FWLTHTS4 Register bit definitions */
#define R_MFWD_FWLTHTS4_LTHSSP4_SHIFT             (0)  /* L3 Stream Search Part 4 */
#define R_MFWD_FWLTHTS4_LTHSSP4_MASK              0xffffffff

/* FWLTHTSR0 Register bit definitions */
#define R_MFWD_FWLTHTSR0_LTHSNF                   (1 << 1)  /* L3 Search Not found */

#define R_MFWD_FWLTHTSR0_LTHSLS                   (1 << 8)  /* L3 Security Level Search */

#define R_MFWD_FWLTHTSR0_LTHSCN_SHIFT             (16)  /* L3 Search Collision Number */
#define R_MFWD_FWLTHTSR0_LTHSCN_MASK              0xff0000

#define R_MFWD_FWLTHTSR0_LTHTS                    (1 << 31)  /* L3 Table Search */

/* FWLTHTSR1 Register bit definitions */
#define R_MFWD_FWLTHTSR1_LTHMSDUNS_SHIFT          (16)  /* L3 MSDU Number Search */
#define R_MFWD_FWLTHTSR1_LTHMSDUNS_MASK           0xf0000

#define R_MFWD_FWLTHTSR1_LTHMSDUVS                (1 << 31)  /* L3 MSDU Valid Search */

/* FWLTHTSR2 Register bit definitions */
#define R_MFWD_FWLTHTSR2_LTHFRERNS_SHIFT          (0)  /* L3 FRER Number Search */
#define R_MFWD_FWLTHTSR2_LTHFRERNS_MASK           0x7f

#define R_MFWD_FWLTHTSR2_LTHFRERVS                (1 << 15)  /* L3 FRER Valid Search */

#define R_MFWD_FWLTHTSR2_LTHMTRNS_SHIFT           (16)  /* L3 Meter Number Search */
#define R_MFWD_FWLTHTSR2_LTHMTRNS_MASK            0x1f0000

#define R_MFWD_FWLTHTSR2_LTHMTRVS                 (1 << 31)  /* L3 Meter Valid Search */

/* FWLTHTSR3 Register bit definitions */
#define R_MFWD_FWLTHTSR3_LTHRNS_SHIFT             (0)  /* L3 Routing Number Search */
#define R_MFWD_FWLTHTSR3_LTHRNS_MASK              0x7

#define R_MFWD_FWLTHTSR3_LTHRVS                   (1 << 15)  /* L3 Routing Valid Search */

#define R_MFWD_FWLTHTSR3_LTHSLVS_SHIFT            (16)  /* L3 Source Lock Vector Search */
#define R_MFWD_FWLTHTSR3_LTHSLVS_MASK             0x70000

/* FWLTHTSR40 Register bit definitions */
#define R_MFWD_FWLTHTSR40_LTHCSDS_SHIFT           (0)  /* L3 CPU Sub-Destination Search */
#define R_MFWD_FWLTHTSR40_LTHCSDS_MASK            0x3f

/* FWLTHTSR5 Register bit definitions */
#define R_MFWD_FWLTHTSR5_LTHDVS_SHIFT             (0)  /* L3 Destination Vector Search */
#define R_MFWD_FWLTHTSR5_LTHDVS_MASK              0x7

#define R_MFWD_FWLTHTSR5_LTHIPVS_SHIFT            (16)  /* L3 Internal Priority Value Search */
#define R_MFWD_FWLTHTSR5_LTHIPVS_MASK             0x70000

#define R_MFWD_FWLTHTSR5_LTHIPUS                  (1 << 19)  /* L3 Internal Priority Update Search */

#define R_MFWD_FWLTHTSR5_LTHEMES                  (1 << 20)  /* L3 Ethernet Mirroring Enable Search */

#define R_MFWD_FWLTHTSR5_LTHCMES                  (1 << 21)  /* L3 CPU Mirroring Enable Search */

/* FWLTHTR Register bit definitions */
#define R_MFWD_FWLTHTR_LTHAR_SHIFT                (0)  /* L3 Address Read */
#define R_MFWD_FWLTHTR_LTHAR_MASK                 0xff

/* FWLTHTRR0 Register bit definitions */
#define R_MFWD_FWLTHTRR0_LTHEVR                   (1 << 1)  /* L3 Entry Valid Read */

#define R_MFWD_FWLTHTRR0_LTHTR                    (1 << 31)  /* L3 Table Read */

/* FWLTHTRR1 Register bit definitions */
#define R_MFWD_FWLTHTRR1_LTHSRP0_SHIFT            (0)  /* L3 Stream Read Part 0 */
#define R_MFWD_FWLTHTRR1_LTHSRP0_MASK             0x7

#define R_MFWD_FWLTHTRR1_LTHSLR                   (1 << 8)  /* L3 Security Level Read */

/* FWLTHTRR2 Register bit definitions */
#define R_MFWD_FWLTHTRR2_LTHSRP1_SHIFT            (0)  /* L3 Stream Read Part 1 */
#define R_MFWD_FWLTHTRR2_LTHSRP1_MASK             0xffffffff

/* FWLTHTRR3 Register bit definitions */
#define R_MFWD_FWLTHTRR3_LTHSRP2_SHIFT            (0)  /* L3 Stream Read Part 2 */
#define R_MFWD_FWLTHTRR3_LTHSRP2_MASK             0xffffffff

/* FWLTHTRR4 Register bit definitions */
#define R_MFWD_FWLTHTRR4_LTHSRP3_SHIFT            (0)  /* L3 Stream Read Part 3 */
#define R_MFWD_FWLTHTRR4_LTHSRP3_MASK             0xffffffff

/* FWLTHTRR5 Register bit definitions */
#define R_MFWD_FWLTHTRR5_LTHSRP4_SHIFT            (0)  /* L3 Stream Read Part 4 */
#define R_MFWD_FWLTHTRR5_LTHSRP4_MASK             0xffffffff

/* FWLTHTRR6 Register bit definitions */
#define R_MFWD_FWLTHTRR6_LTHMSDUNR_SHIFT          (16)  /* L3 MSDU Number Read */
#define R_MFWD_FWLTHTRR6_LTHMSDUNR_MASK           0xf0000

#define R_MFWD_FWLTHTRR6_LTHMSDUVR                (1 << 31)  /* L3 MSDU Valid Read */

/* FWLTHTRR7 Register bit definitions */
#define R_MFWD_FWLTHTRR7_LTHFRERNR_SHIFT          (0)  /* L3 FRER Number Read */
#define R_MFWD_FWLTHTRR7_LTHFRERNR_MASK           0x7f

#define R_MFWD_FWLTHTRR7_LTHFRERVR                (1 << 15)  /* L3 FRER Valid Read */

#define R_MFWD_FWLTHTRR7_LTHMTRNR_SHIFT           (16)  /* L3 Meter Number Read */
#define R_MFWD_FWLTHTRR7_LTHMTRNR_MASK            0x1f0000

#define R_MFWD_FWLTHTRR7_LTHMTRVR                 (1 << 31)  /* L3 Meter Valid Read */

/* FWLTHTRR8 Register bit definitions */
#define R_MFWD_FWLTHTRR8_LTHRNR_SHIFT             (0)  /* L3 Routing Number Read */
#define R_MFWD_FWLTHTRR8_LTHRNR_MASK              0xff

#define R_MFWD_FWLTHTRR8_LTHRVR                   (1 << 15)  /* L3 Routing Valid Read */

#define R_MFWD_FWLTHTRR8_LTHSLVR_SHIFT            (16)  /* L3 Source Lock Vector Read */
#define R_MFWD_FWLTHTRR8_LTHSLVR_MASK             0x70000

/* FWLTHTRR90 Register bit definitions */
#define R_MFWD_FWLTHTRR90_LTHCSDR_SHIFT           (0)  /* L3 CPU Sub-Destination Read */
#define R_MFWD_FWLTHTRR90_LTHCSDR_MASK            0x3f

/* FWLTHTRR10 Register bit definitions */
#define R_MFWD_FWLTHTRR10_LTHDVR_SHIFT            (0)  /* L3 Destination Vector Read */
#define R_MFWD_FWLTHTRR10_LTHDVR_MASK             0x7

#define R_MFWD_FWLTHTRR10_LTHIPVR_SHIFT           (16)  /* L3 Internal Priority Value Read */
#define R_MFWD_FWLTHTRR10_LTHIPVR_MASK            0x70000

#define R_MFWD_FWLTHTRR10_LTHIPUR                 (1 << 19)  /* L3 Internal Priority Update Read */

#define R_MFWD_FWLTHTRR10_LTHEMER                 (1 << 20)  /* L3 Ethernet Mirroring Enable Read */

#define R_MFWD_FWLTHTRR10_LTHCMER                 (1 << 21)  /* L3 CPU Mirroring Enable Read */

/* FWMACHEC Register bit definitions */
#define R_MFWD_FWMACHEC_MACHMC_SHIFT              (0)  /* MAC Hash Maximum Collision */
#define R_MFWD_FWMACHEC_MACHMC_MASK               0x7ff

#define R_MFWD_FWMACHEC_MACHMUE_SHIFT             (16)  /* MAC Hash Maximum Unsecure Entry */
#define R_MFWD_FWMACHEC_MACHMUE_MASK              0xfff0000

/* FWMACHC Register bit definitions */
#define R_MFWD_FWMACHC_MACHE10 TO MACHE0_SHIFT    (0)  /* MAC Hash Equation n (n = 0 to 10) */
#define R_MFWD_FWMACHC_MACHE10 TO MACHE0_MASK     0x7ff

/* FWMACTL0 Register bit definitions */
#define R_MFWD_FWMACTL0_MACSLL                    (1 << 8)  /* MAC Security Level Learn */

#define R_MFWD_FWMACTL0_MACDEL                    (1 << 9)  /* MAC Dynamic Entry Learn */

#define R_MFWD_FWMACTL0_MACHLDL                   (1 << 10)  /* MAC Hardware Learning Disable Learn */

#define R_MFWD_FWMACTL0_MACED                     (1 << 16)  /* MAC Entry Delete */

/* FWMACTL1 Register bit definitions */
#define R_MFWD_FWMACTL1_MACMALP0_SHIFT            (0)  /* MAC MAC address Learn Part 0 */
#define R_MFWD_FWMACTL1_MACMALP0_MASK             0xffff

/* FWMACTL2 Register bit definitions */
#define R_MFWD_FWMACTL2_MACMALP1_SHIFT            (0)  /* MAC MAC address Learn Part 1 */
#define R_MFWD_FWMACTL2_MACMALP1_MASK             0xffffffff

/* FWMACTL3 Register bit definitions */
#define R_MFWD_FWMACTL3_MACSSLVL_SHIFT            (0)  /* MAC Source Source Lock Vector Learn */
#define R_MFWD_FWMACTL3_MACSSLVL_MASK             0x7

#define R_MFWD_FWMACTL3_MACDSLVL_SHIFT            (16)  /* MAC Destination Source Lock Vector Learn */
#define R_MFWD_FWMACTL3_MACDSLVL_MASK             0x70000

/* FWMACTL40 Register bit definitions */
#define R_MFWD_FWMACTL40_MACCSDL_SHIFT            (0)  /* MAC CPU Sub-Destination Learn */
#define R_MFWD_FWMACTL40_MACCSDL_MASK             0x3f

/* FWMACTL5 Register bit definitions */
#define R_MFWD_FWMACTL5_MACDVL_SHIFT              (0)  /* MAC Destination Vector Learn */
#define R_MFWD_FWMACTL5_MACDVL_MASK               0x7

#define R_MFWD_FWMACTL5_MACIPVL_SHIFT             (16)  /* MAC Internal Priority Value Learn */
#define R_MFWD_FWMACTL5_MACIPVL_MASK              0x70000

#define R_MFWD_FWMACTL5_MACIPUL                   (1 << 19)  /* MAC Internal Priority Update Learn */

#define R_MFWD_FWMACTL5_MACEMEL                   (1 << 20)  /* MAC Ethernet Mirroring Enable Learn */

#define R_MFWD_FWMACTL5_MACCMEL                   (1 << 21)  /* MAC CPU Mirroring Enable Learn */

/* FWMACTLR Register bit definitions */
#define R_MFWD_FWMACTLR_MACLF                     (1 << 0)  /* MAC Learn Fail */

#define R_MFWD_FWMACTLR_MACLSF                    (1 << 1)  /* MAC Learn Security Fail */

#define R_MFWD_FWMACTLR_MACLO                     (1 << 3)  /* MAC Learn Overwrite */

#define R_MFWD_FWMACTLR_MACLCN_SHIFT              (16)  /* MAC Learn Collision Number */
#define R_MFWD_FWMACTLR_MACLCN_MASK               0x7ff0000

#define R_MFWD_FWMACTLR_MACTL                     (1 << 31)  /* MAC Table Learn */

/* FWMACTIM Register bit definitions */
#define R_MFWD_FWMACTIM_MACTIOG                   (1 << 0)  /* MAC Table Initialization Ongoing */

#define R_MFWD_FWMACTIM_MACTR                     (1 << 1)  /* MAC Table Ready */

/* FWMACTEM Register bit definitions */
#define R_MFWD_FWMACTEM_MACTEN_SHIFT              (0)  /* MAC Table Entry Number */
#define R_MFWD_FWMACTEM_MACTEN_MASK               0xfff

#define R_MFWD_FWMACTEM_MACTUEN_SHIFT             (16)  /* MAC Table Unsecure Entry Number */
#define R_MFWD_FWMACTEM_MACTUEN_MASK              0xfff0000

/* FWMACTS0 Register bit definitions */
#define R_MFWD_FWMACTS0_MACMASP0_SHIFT            (0)  /* MAC MAC Address Search Part 0 */
#define R_MFWD_FWMACTS0_MACMASP0_MASK             0xffff

/* FWMACTS1 Register bit definitions */
#define R_MFWD_FWMACTS1_MACMASP1_SHIFT            (0)  /* MAC MAC Address Search Part 1 */
#define R_MFWD_FWMACTS1_MACMASP1_MASK             0xffffffff

/* FWMACTSR0 Register bit definitions */
#define R_MFWD_FWMACTSR0_MACSNF                   (1 << 1)  /* MAC Search Not found */

#define R_MFWD_FWMACTSR0_MACSLS                   (1 << 8)  /* MAC Security Level Search */

#define R_MFWD_FWMACTSR0_MACDES                   (1 << 9)  /* MAC Dynamic Entry Search */

#define R_MFWD_FWMACTSR0_MACHLDS                  (1 << 10)  /* MAC Hardware Learning Disable Search */

#define R_MFWD_FWMACTSR0_MACSCN_SHIFT             (16)  /* MAC Search Collision Number */
#define R_MFWD_FWMACTSR0_MACSCN_MASK              0x7ff0000

#define R_MFWD_FWMACTSR0_MACTS                    (1 << 31)  /* MAC Table Search */

/* FWMACTSR1 Register bit definitions */
#define R_MFWD_FWMACTSR1_MACSSLVS_SHIFT           (0)  /* MAC Source Source Lock Vector Search */
#define R_MFWD_FWMACTSR1_MACSSLVS_MASK            0x7

#define R_MFWD_FWMACTSR1_MACDSLVS_SHIFT           (16)  /* MAC Destination Source Lock Vector Search */
#define R_MFWD_FWMACTSR1_MACDSLVS_MASK            0x70000

/* FWMACTSR20 Register bit definitions */
#define R_MFWD_FWMACTSR20_MACCSDS_SHIFT           (0)  /* MAC CPU Sub-Destination Search */
#define R_MFWD_FWMACTSR20_MACCSDS_MASK            0x3f

/* FWMACTSR3 Register bit definitions */
#define R_MFWD_FWMACTSR3_MACDVS_SHIFT             (0)  /* MAC Destination Vector Search */
#define R_MFWD_FWMACTSR3_MACDVS_MASK              0x7

#define R_MFWD_FWMACTSR3_MACIPVS_SHIFT            (16)  /* MAC Internal Priority Value Search */
#define R_MFWD_FWMACTSR3_MACIPVS_MASK             0x70000

#define R_MFWD_FWMACTSR3_MACIPUS                  (1 << 19)  /* MAC Internal Priority Update Search */

#define R_MFWD_FWMACTSR3_MACEMES                  (1 << 20)  /* MAC Ethernet Mirroring Enable Search */

#define R_MFWD_FWMACTSR3_MACCMES                  (1 << 21)  /* MAC CPU Mirroring Enable Search */

/* FWMACTR Register bit definitions */
#define R_MFWD_FWMACTR_MACAR_SHIFT                (0)  /* MAC Address Read */
#define R_MFWD_FWMACTR_MACAR_MASK                 0x7ff

/* FWMACTRR0 Register bit definitions */
#define R_MFWD_FWMACTRR0_MACEVR                   (1 << 0)  /* MAC Entry Valid Read */

#define R_MFWD_FWMACTRR0_MACTR                    (1 << 31)  /* MAC Table Read */

/* FWMACTRR1 Register bit definitions */
#define R_MFWD_FWMACTRR1_MACSLR                   (1 << 8)  /* MAC Security Level Read */

#define R_MFWD_FWMACTRR1_MACDER                   (1 << 9)  /* MAC Dynamic Entry Read */

#define R_MFWD_FWMACTRR1_MACHLDR                  (1 << 10)  /* MAC Hardware Learn Disable Read */

#define R_MFWD_FWMACTRR1_MACABR                   (1 << 11)  /* MAC Aging Bit Read */

/* FWMACTRR2 Register bit definitions */
#define R_MFWD_FWMACTRR2_MACMARP0_SHIFT           (0)  /* MAC MAC address Read Part 0 */
#define R_MFWD_FWMACTRR2_MACMARP0_MASK            0xffff

/* FWMACTRR3 Register bit definitions */
#define R_MFWD_FWMACTRR3_MACMARP1_SHIFT           (0)  /* MAC MAC Address Read Part 1 */
#define R_MFWD_FWMACTRR3_MACMARP1_MASK            0xffffffff

/* FWMACTRR4 Register bit definitions */
#define R_MFWD_FWMACTRR4_MACSSLVR_SHIFT           (0)  /* MAC Source Source Lock Vector Read */
#define R_MFWD_FWMACTRR4_MACSSLVR_MASK            0x7

#define R_MFWD_FWMACTRR4_MACDSLVR_SHIFT           (16)  /* MAC Destination Source Lock Vector Read */
#define R_MFWD_FWMACTRR4_MACDSLVR_MASK            0x70000

/* FWMACTRR50 Register bit definitions */
#define R_MFWD_FWMACTRR50_MACCSDR_SHIFT           (0)  /* MAC CPU Sub-Destination Read */
#define R_MFWD_FWMACTRR50_MACCSDR_MASK            0x3f

/* FWMACTRR6 Register bit definitions */
#define R_MFWD_FWMACTRR6_MACDVR_SHIFT             (0)  /* MAC Destination Vector Read */
#define R_MFWD_FWMACTRR6_MACDVR_MASK              0x7

#define R_MFWD_FWMACTRR6_MACIPVR_SHIFT            (16)  /* MAC Internal Priority Value Read */
#define R_MFWD_FWMACTRR6_MACIPVR_MASK             0x70000

#define R_MFWD_FWMACTRR6_MACIPUR                  (1 << 19)  /* MAC Internal Priority Update Read */

#define R_MFWD_FWMACTRR6_MACEMER                  (1 << 20)  /* MAC Ethernet Mirroring Enable Read */

#define R_MFWD_FWMACTRR6_MACCMER                  (1 << 21)  /* MAC CPU Mirroring Enable Read */

/* FWMACAGUSPC Register bit definitions */
#define R_MFWD_FWMACAGUSPC_MACAGUSP_SHIFT         (0)  /* MAC Aging US prescaler */
#define R_MFWD_FWMACAGUSPC_MACAGUSP_MASK          0x3ff

/* FWMACAGC Register bit definitions */
#define R_MFWD_FWMACAGC_MACAGT_SHIFT              (0)  /* MAC Aging Time */
#define R_MFWD_FWMACAGC_MACAGT_MASK               0xffff

#define R_MFWD_FWMACAGC_MACAGE                    (1 << 16)  /* MAC Aging Enable */

#define R_MFWD_FWMACAGC_MACAGSL                   (1 << 17)  /* MAC Aging Security Level */

#define R_MFWD_FWMACAGC_MACAGPM                   (1 << 18)  /* MAC Aging Polling Mode */

#define R_MFWD_FWMACAGC_MACDES                    (1 << 24)  /* MAC Dynamic Entry Suppression */

#define R_MFWD_FWMACAGC_MACAGOG                   (1 << 28)  /* MAC Aging Ongoing */

#define R_MFWD_FWMACAGC_MACDESOG                  (1 << 29)  /* MAC Dynamic Entry Suppression Ongoing */

/* FWMACAGM0 Register bit definitions */
#define R_MFWD_FWMACAGM0_AGMACAP0_SHIFT           (0)  /* Aged MAC Address Part 0 */
#define R_MFWD_FWMACAGM0_AGMACAP0_MASK            0xffff

/* FWMACAGM1 Register bit definitions */
#define R_MFWD_FWMACAGM1_AGMACAP1_SHIFT           (0)  /* Aged MAC Address Part 1 */
#define R_MFWD_FWMACAGM1_AGMACAP1_MASK            0xffffffff

/* FWVLANTEC Register bit definitions */
#define R_MFWD_FWVLANTEC_VLANTMUE_SHIFT           (16)  /* VLAN Table Maximum Unsecure Entry */
#define R_MFWD_FWVLANTEC_VLANTMUE_MASK            0x1fff0000

/* FWVLANTL0 Register bit definitions */
#define R_MFWD_FWVLANTL0_VLANSLL                  (1 << 8)  /* VLAN Security Level Learn */

#define R_MFWD_FWVLANTL0_VLANHLDL                 (1 << 10)  /* VLAN Hardware Learning Disable Learn */

#define R_MFWD_FWVLANTL0_VLANED                   (1 << 16)  /* VLAN Entry Delete */

/* FWVLANTL1 Register bit definitions */
#define R_MFWD_FWVLANTL1_VLANVIDL_SHIFT           (0)  /* VLAN VID Learn */
#define R_MFWD_FWVLANTL1_VLANVIDL_MASK            0xfff

/* FWVLANTL2 Register bit definitions */
#define R_MFWD_FWVLANTL2_VLANSLVL_SHIFT           (0)  /* VLAN Source Lock Vector Learn */
#define R_MFWD_FWVLANTL2_VLANSLVL_MASK            0x7

/* FWVLANTL30 Register bit definitions */
#define R_MFWD_FWVLANTL30_VLANCSDL_SHIFT          (0)  /* VLAN CPU Sub-Destination Learn */
#define R_MFWD_FWVLANTL30_VLANCSDL_MASK           0x3f

/* FWVLANTL4 Register bit definitions */
#define R_MFWD_FWVLANTL4_VLANDVL_SHIFT            (0)  /* VLAN Destination Vector Learn */
#define R_MFWD_FWVLANTL4_VLANDVL_MASK             0x7

#define R_MFWD_FWVLANTL4_VLANIPVL_SHIFT           (16)  /* VLAN Internal Priority Value Learn */
#define R_MFWD_FWVLANTL4_VLANIPVL_MASK            0x70000

#define R_MFWD_FWVLANTL4_VLANIPUL                 (1 << 19)  /* VLAN Internal Priority Update Learn */

#define R_MFWD_FWVLANTL4_VLANEMEL                 (1 << 20)  /* VLAN Ethernet Mirroring Enable Learn */

#define R_MFWD_FWVLANTL4_VLANCMEL                 (1 << 21)  /* VLAN CPU Mirroring Enable Learn */

/* FWVLANTLR Register bit definitions */
#define R_MFWD_FWVLANTLR_VLANLF                   (1 << 0)  /* VLAN Learn Fail */

#define R_MFWD_FWVLANTLR_VLANLSF                  (1 << 1)  /* VLAN Learn Security Fail */

#define R_MFWD_FWVLANTLR_VLANLO                   (1 << 3)  /* VLAN Learn Overwrite */

#define R_MFWD_FWVLANTLR_VLANTL                   (1 << 31)  /* VLAN Table Learn */

/* FWVLANTIM Register bit definitions */
#define R_MFWD_FWVLANTIM_VLANTIOG                 (1 << 0)  /* VLAN Table Initialization Ongoing */

#define R_MFWD_FWVLANTIM_VLANTR                   (1 << 1)  /* VLAN Table Ready */

/* FWVLANTEM Register bit definitions */
#define R_MFWD_FWVLANTEM_VLANTEN_SHIFT            (0)  /* VLAN Table Entry Number */
#define R_MFWD_FWVLANTEM_VLANTEN_MASK             0x1fff

#define R_MFWD_FWVLANTEM_VLANTUEN_SHIFT           (16)  /* VLAN Table Unsecure Entry Number */
#define R_MFWD_FWVLANTEM_VLANTUEN_MASK            0x1fff0000

/* FWVLANTS Register bit definitions */
#define R_MFWD_FWVLANTS_VLANVIDS_SHIFT            (0)  /* VLAN VID Search */
#define R_MFWD_FWVLANTS_VLANVIDS_MASK             0xfff

/* FWVLANTSR0 Register bit definitions */
#define R_MFWD_FWVLANTSR0_VLANSNF                 (1 << 1)  /* VLAN Search Not found */

#define R_MFWD_FWVLANTSR0_VLANSLS                 (1 << 8)  /* VLAN Security Level Search */

#define R_MFWD_FWVLANTSR0_VLANHLDS                (1 << 10)  /* VLAN Hardware Learning Disable Search */

#define R_MFWD_FWVLANTSR0_VLANTS                  (1 << 31)  /* VLAN Table Search */

/* FWVLANTSR1 Register bit definitions */
#define R_MFWD_FWVLANTSR1_VLANSLVS_SHIFT          (0)  /* VLAN Source Lock Vector Search */
#define R_MFWD_FWVLANTSR1_VLANSLVS_MASK           0x7

/* FWVLANTSR20 Register bit definitions */
#define R_MFWD_FWVLANTSR20_VLANCSDS_SHIFT         (0)  /* VLAN CPU Sub-Destination Search */
#define R_MFWD_FWVLANTSR20_VLANCSDS_MASK          0x3f

/* FWVLANTSR3 Register bit definitions */
#define R_MFWD_FWVLANTSR3_VLANDVS_SHIFT           (0)  /* VLAN Destination Vector Search */
#define R_MFWD_FWVLANTSR3_VLANDVS_MASK            0x7

#define R_MFWD_FWVLANTSR3_VLANIPVS_SHIFT          (16)  /* VLAN Internal Priority Value Search */
#define R_MFWD_FWVLANTSR3_VLANIPVS_MASK           0x70000

#define R_MFWD_FWVLANTSR3_VLANIPUS                (1 << 19)  /* VLAN Internal Priority Update Search */

#define R_MFWD_FWVLANTSR3_VLANEMES                (1 << 20)  /* VLAN Ethernet Mirroring Enable Search */

#define R_MFWD_FWVLANTSR3_VLANCMES                (1 << 21)  /* VLAN CPU Mirroring Enable Search */

/* FWPBFC Register bit definitions */
#define R_MFWD_FWPBFC_PBDV_SHIFT                  (0)  /* Port Based Destination Vector */
#define R_MFWD_FWPBFC_PBDV_MASK                   0x7

#define R_MFWD_FWPBFC_PBIPV_SHIFT                 (16)  /* Port Based Internal Priority Value */
#define R_MFWD_FWPBFC_PBIPV_MASK                  0x70000

#define R_MFWD_FWPBFC_PBIPU                       (1 << 19)  /* Port Based Internal Priority Update */

#define R_MFWD_FWPBFC_PBEME                       (1 << 20)  /* Port Based Ethernet Mirroring Enabled */

#define R_MFWD_FWPBFC_PBCME                       (1 << 21)  /* Port Based CPU Mirroring Enabled */

#define R_MFWD_FWPBFC_PBSL                        (1 << 22)  /* Port Based Security Level */

#define R_MFWD_FWPBFC_IP4PDE                      (1 << 23)  /* IPv4 Priority Decode Enable */

#define R_MFWD_FWPBFC_IP4PDM                      (1 << 24)  /* IPv4 Priority Decode Mode */

#define R_MFWD_FWPBFC_IP6PDE                      (1 << 25)  /* IPv6 Priority Decode Enable */

#define R_MFWD_FWPBFC_FAIFP                       (1 << 26)  /* Force All Input Frame Priority Enable */

/* FWPBFCSDC Register bit definitions */
#define R_MFWD_FWPBFCSDC_PBCSD_SHIFT              (0)  /* Port Based CPU Sub Destination */
#define R_MFWD_FWPBFCSDC_PBCSD_MASK               0x3f

/* FWL23URL0 Register bit definitions */
#define R_MFWD_FWL23URL0_L23URNL_SHIFT            (0)  /* Layer 2/Layer 3 Update Routing Number Learn */
#define R_MFWD_FWL23URL0_L23URNL_MASK             0xff

#define R_MFWD_FWL23URL0_L23URPVL_SHIFT           (16)  /* Layer 2/Layer 3 Update Routing Port Valid Learn */
#define R_MFWD_FWL23URL0_L23URPVL_MASK            0x70000

/* FWL23URL1 Register bit definitions */
#define R_MFWD_FWL23URL1_L23UMDALP0_SHIFT         (0)  /* Layer 2/Layer 3 Update MAC Destination Address Learn Part 0 */
#define R_MFWD_FWL23URL1_L23UMDALP0_MASK          0xffff

#define R_MFWD_FWL23URL1_L23UTTLUL                (1 << 16)  /* Layer 2/Layer 3 Update Time To Live Update Learn */

#define R_MFWD_FWL23URL1_L23UMDAUL                (1 << 17)  /* Layer 2/Layer 3 Update MAC Destination Address Update Learn */

#define R_MFWD_FWL23URL1_L23UMSAUL                (1 << 18)  /* Layer 2/Layer 3 Update MAC Source Address Update Learn */

#define R_MFWD_FWL23URL1_L23UCVIDUL               (1 << 19)  /* Layer 2/Layer 3 Update C-TAG VID Update Learn */

#define R_MFWD_FWL23URL1_L23UCPCPUL               (1 << 20)  /* Layer 2/Layer 3 Update C-TAG PCP Update Learn */

#define R_MFWD_FWL23URL1_L23UCDEIUL               (1 << 21)  /* Layer 2/Layer 3 Update C-TAG DEI Update Learn */

#define R_MFWD_FWL23URL1_L23USVIDUL               (1 << 22)  /* Layer 2/Layer 3 Update S-TAG VID Update Learn */

#define R_MFWD_FWL23URL1_L23USPCPUL               (1 << 23)  /* Layer 2/Layer 3 Update S-TAG PCP Update Learn */

#define R_MFWD_FWL23URL1_L23USDEIUL               (1 << 24)  /* Layer 2/Layer 3 Update S-TAG DEI Update Learn */

#define R_MFWD_FWL23URL1_L23URTUL_SHIFT           (25)  /* Layer 2/Layer 3 Update R-TAG Update Learn */
#define R_MFWD_FWL23URL1_L23URTUL_MASK            0x6000000

/* FWL23URL2 Register bit definitions */
#define R_MFWD_FWL23URL2_L23UMDALP1_SHIFT         (0)  /* Layer 2/Layer 3 Update MAC Destination Address Learn Part 1 */
#define R_MFWD_FWL23URL2_L23UMDALP1_MASK          0xffffffff

/* FWL23URL3 Register bit definitions */
#define R_MFWD_FWL23URL3_L23UCVIDL_SHIFT          (0)  /* Layer 2/Layer 3 Update C-TAG VID Learn */
#define R_MFWD_FWL23URL3_L23UCVIDL_MASK           0xfff

#define R_MFWD_FWL23URL3_L23UCPCPL_SHIFT          (12)  /* Layer 2/Layer 3 Update C-TAG PCP Learn */
#define R_MFWD_FWL23URL3_L23UCPCPL_MASK           0x7000

#define R_MFWD_FWL23URL3_L23UCDEIL                (1 << 15)  /* Layer 2/Layer 3 Update C-TAG DEI Learn */

#define R_MFWD_FWL23URL3_L23USVIDL_SHIFT          (16)  /* Layer 2/Layer 3 Update S-TAG VID Learn */
#define R_MFWD_FWL23URL3_L23USVIDL_MASK           0xfff0000

#define R_MFWD_FWL23URL3_L23USPCPL_SHIFT          (28)  /* Layer 2/Layer 3 Update S-TAG PCP Learn */
#define R_MFWD_FWL23URL3_L23USPCPL_MASK           0x70000000

#define R_MFWD_FWL23URL3_L23USDEIL                (1 << 31)  /* Layer 2/Layer 3 Update S-TAG DEI Learn */

/* FWL23URLR Register bit definitions */
#define R_MFWD_FWL23URLR_L23ULF                   (1 << 0)  /* Layer 2/Layer 3 Update Learn Fail */

#define R_MFWD_FWL23URLR_L23URL                   (1 << 31)  /* Layer 2/Layer 3 Update Rule Learn */

/* FWL23UTIM Register bit definitions */
#define R_MFWD_FWL23UTIM_L23UTIOG                 (1 << 0)  /* Layer 2/Layer 3 Update Table Initialization Ongoing */

#define R_MFWD_FWL23UTIM_L23UTR                   (1 << 1)  /* Layer 2/Layer 3 Update Table Ready */

/* FWL23URR Register bit definitions */
#define R_MFWD_FWL23URR_L23RNR_SHIFT              (0)  /* Layer 2/Layer 3 Routing Number Read */
#define R_MFWD_FWL23URR_L23RNR_MASK               0xff

/* FWL23URRR0 Register bit definitions */
#define R_MFWD_FWL23URRR0_L23URPVR_SHIFT          (0)  /* Layer 2/Layer 3 Update Routing Port Valid Read */
#define R_MFWD_FWL23URRR0_L23URPVR_MASK           0x7

#define R_MFWD_FWL23URRR0_L23URR                  (1 << 31)  /* Layer 2/Layer 3 Update Rule Read */

/* FWL23URRR1 Register bit definitions */
#define R_MFWD_FWL23URRR1_L23UMDARP0_SHIFT        (0)  /* Layer 2/Layer 3 MAC Destination Address Read Part 0 */
#define R_MFWD_FWL23URRR1_L23UMDARP0_MASK         0xffff

#define R_MFWD_FWL23URRR1_L23UTTLUR               (1 << 16)  /* Layer 2/Layer 3 Time To Live Update Read */

#define R_MFWD_FWL23URRR1_L23UMDAUR               (1 << 17)  /* Layer 2/Layer 3 MAC Destination Address Update Read */

#define R_MFWD_FWL23URRR1_L23UMSAUR               (1 << 18)  /* Layer 2/Layer 3 MAC Source Address Update Read */

#define R_MFWD_FWL23URRR1_L23UCVIDUR              (1 << 19)  /* Layer 2/Layer 3 C-TAG VID Update Read */

#define R_MFWD_FWL23URRR1_L23UCPCPUR              (1 << 20)  /* Layer 2/Layer 3 C-TAG PCP Update Read */

#define R_MFWD_FWL23URRR1_L23UCDEIUR              (1 << 21)  /* Layer 2/Layer 3 C-TAG DEI Update Read */

#define R_MFWD_FWL23URRR1_L23USVIDUR              (1 << 22)  /* Layer 2/Layer 3 S-TAG VID Update Read */

#define R_MFWD_FWL23URRR1_L23USPCPUR              (1 << 23)  /* Layer 2/Layer 3 S-TAG PCP Update Read */

#define R_MFWD_FWL23URRR1_L23USDEIUR              (1 << 24)  /* Layer 2/Layer 3 S-TAG DEI Update Read */

#define R_MFWD_FWL23URRR1_L23URTUR_SHIFT          (25)  /* Layer 2/Layer 3 R-TAG Update Read */
#define R_MFWD_FWL23URRR1_L23URTUR_MASK           0x6000000

/* FWL23URRR2 Register bit definitions */
#define R_MFWD_FWL23URRR2_L23UMDARP1_SHIFT        (0)  /* Layer 2/Layer 3 Update MAC Destination Address Read Part 1 */
#define R_MFWD_FWL23URRR2_L23UMDARP1_MASK         0xffffffff

/* FWL23URRR3 Register bit definitions */
#define R_MFWD_FWL23URRR3_L23UCVIDR_SHIFT         (0)  /* Layer 2/Layer 3 Update MAC C-TAG VID Read */
#define R_MFWD_FWL23URRR3_L23UCVIDR_MASK          0xfff

#define R_MFWD_FWL23URRR3_L23UCPCPR_SHIFT         (12)  /* Layer 2/Layer 3 Update MAC C-TAG PCP Read */
#define R_MFWD_FWL23URRR3_L23UCPCPR_MASK          0x7000

#define R_MFWD_FWL23URRR3_L23UCDEIR               (1 << 15)  /* Layer 2/Layer 3 Update MAC C-TAG DEI Read */

#define R_MFWD_FWL23URRR3_L23USVIDR_SHIFT         (16)  /* Layer 2/Layer 3 Update MAC S-TAG VID Read */
#define R_MFWD_FWL23URRR3_L23USVIDR_MASK          0xfff0000

#define R_MFWD_FWL23URRR3_L23USPCPR_SHIFT         (28)  /* Layer 2/Layer 3 Update MAC S-TAG PCP Read */
#define R_MFWD_FWL23URRR3_L23USPCPR_MASK          0x70000000

#define R_MFWD_FWL23URRR3_L23USDEIR               (1 << 31)  /* Layer 2/Layer 3 Update MAC S-TAG DEI Read */

/* FWL23URMC Register bit definitions */
#define R_MFWD_FWL23URMC_RMRN_SHIFT               (0)  /* Remapping Rule Number */
#define R_MFWD_FWL23URMC_RMRN_MASK                0xff

#define R_MFWD_FWL23URMC_RMDPN_SHIFT              (12)  /* Remapping Destination Port Number */
#define R_MFWD_FWL23URMC_RMDPN_MASK               0x3000

#define R_MFWD_FWL23URMC_RMNRN_SHIFT              (16)  /* Remapping New Rule Number */
#define R_MFWD_FWL23URMC_RMNRN_MASK               0xff0000

#define R_MFWD_FWL23URMC_RME                      (1 << 28)  /* Remapping Enable */

/* FWPMFGC Register bit definitions */
#define R_MFWD_FWPMFGC_MSDUV_SHIFT                (0)  /* MSDU Value */
#define R_MFWD_FWPMFGC_MSDUV_MASK                 0xffff

#define R_MFWD_FWPMFGC_MFM                        (1 << 31)  /* MSDU Filter Mode */

/* FWPMTRFC Register bit definitions */
#define R_MFWD_FWPMTRFC_MTRFE                     (1 << 0)  /* Meter Filter Enable */

#define R_MFWD_FWPMTRFC_MTRFM_SHIFT               (1)  /* Meter Filter Mode */
#define R_MFWD_FWPMTRFC_MTRFM_MASK                0x6
#  define R_MFWD_FWPMTRFC_MTRFM_00                        (0 << R_MFWD_FWPMTRFC_MTRFM_SHIFT)  /* Normal mode: Any frame linked to Meter filter i thanks to L3 table received when not enough token is available will be red. */
#  define R_MFWD_FWPMTRFC_MTRFM_01                        (1 << R_MFWD_FWPMTRFC_MTRFM_SHIFT)  /* Throttle mode: Any frame linked to Meter filter i thanks to L3 table received when not enough token is available or when FWEIS5.PMRFSi is set will be red. */
#  define R_MFWD_FWPMTRFC_MTRFM_10                        (2 << R_MFWD_FWPMTRFC_MTRFM_SHIFT)  /* ATS mode: Any frame linked to Meter filter i thanks to L3 table received when not enough token is available will be stored in ATS RAM until enough tokens are available. When enough tokens are available, frame will be forwarded as yellow or green. */
#  define R_MFWD_FWPMTRFC_MTRFM_11                        (3 << R_MFWD_FWPMTRFC_MTRFM_SHIFT)  /* ATS throttle mode: Any frame linked to Meter filter i thanks to L3 table received when not enough token is available will be stored in ATS RAM until enough tokens are available. When enough tokens are available, frame will be forwarded as yellow or green if FWEIS5.PMRFSi is not set and will be red if FWEIS5.PMRFSi is set. */

#define R_MFWD_FWPMTRFC_MTRFRFD                   (1 << 3)  /* Meter Filter Red Frame Drop */

#define R_MFWD_FWPMTRFC_MTRCF                     (1 << 4)  /* Meter Coupling Flag */

#define R_MFWD_FWPMTRFC_MTRCM15 TO MTRCM0_SHIFT   (16)  /* Meter Color Mode n (n = 0 to 15) */
#define R_MFWD_FWPMTRFC_MTRCM15 TO MTRCM0_MASK    0xffff0000

/* FWPMTRCBSC Register bit definitions */
#define R_MFWD_FWPMTRCBSC_CBS_SHIFT               (0)  /* CBS */
#define R_MFWD_FWPMTRCBSC_CBS_MASK                0x3ffff

/* FWPMTRCIRC Register bit definitions */
#define R_MFWD_FWPMTRCIRC_CIR_SHIFT               (0)  /* CIR */
#define R_MFWD_FWPMTRCIRC_CIR_MASK                0xfffff

/* FWPMTREBSC Register bit definitions */
#define R_MFWD_FWPMTREBSC_EBS_SHIFT               (0)  /* EBS */
#define R_MFWD_FWPMTREBSC_EBS_MASK                0x3ffff

/* FWPMTREIRC Register bit definitions */
#define R_MFWD_FWPMTREIRC_EIR_SHIFT               (0)  /* EIR */
#define R_MFWD_FWPMTREIRC_EIR_MASK                0xfffff

/* FWPMTRFM Register bit definitions */
#define R_MFWD_FWPMTRFM_MTRARDN_SHIFT             (0)  /* Meter ATS RAM Descriptor Number */
#define R_MFWD_FWPMTRFM_MTRARDN_MASK              0x1f

#define R_MFWD_FWPMTRFM_MTRARDNMN_SHIFT           (16)  /* Meter ATS RAM Descriptor Number Maximum Number */
#define R_MFWD_FWPMTRFM_MTRARDNMN_MASK            0x1f0000

/* FWFTL0 Register bit definitions */
#define R_MFWD_FWFTL0_FEAL_SHIFT                  (0)  /* FRER Entry Address Learn */
#define R_MFWD_FWFTL0_FEAL_MASK                   0x7f

#define R_MFWD_FWFTL0_FSRPL_SHIFT                 (16)  /* FRER Sequence Recovery Pointer Learn */
#define R_MFWD_FWFTL0_FSRPL_MASK                  0x7f0000

/* FWFTL1 Register bit definitions */
#define R_MFWD_FWFTL1_FSHLL_SHIFT                 (0)  /* FRER Sequence History Length Learn */
#define R_MFWD_FWFTL1_FSHLL_MASK                  0xf

#define R_MFWD_FWFTL1_FTNSL                       (1 << 8)  /* FRER Take No Sequence Learn */

#define R_MFWD_FWFTL1_FSRPVL                      (1 << 9)  /* FRER Sequence Recovery Pointer Valid Learn */

#define R_MFWD_FWFTL1_FSRRTL_SHIFT                (16)  /* FRER Sequence Recovery Remaining Ticks Learn */
#define R_MFWD_FWFTL1_FSRRTL_MASK                 0x3ff0000

/* FWFTLR Register bit definitions */
#define R_MFWD_FWFTLR_FLF                         (1 << 0)  /* FRER Learn Fail */

#define R_MFWD_FWFTLR_FTL                         (1 << 31)  /* FRER Table Learn */

/* FWFTOC Register bit definitions */
#define R_MFWD_FWFTOC_TOT_SHIFT                   (0)  /* Timeout Time (ms) */
#define R_MFWD_FWFTOC_TOT_MASK                    0xffff

#define R_MFWD_FWFTOC_TOCE                        (1 << 16)  /* Timeout Check Enable */

#define R_MFWD_FWFTOC_TOOG                        (1 << 17)  /* Timeout Ongoing */

/* FWFTOPC Register bit definitions */
#define R_MFWD_FWFTOPC_USP_SHIFT                  (0)  /* Microsecond Prescaler */
#define R_MFWD_FWFTOPC_USP_MASK                   0x3ff

/* FWFTIM Register bit definitions */
#define R_MFWD_FWFTIM_FTIOG                       (1 << 0)  /* FRER Table Initialization Ongoing */

#define R_MFWD_FWFTIM_FTR                         (1 << 1)  /* FRER Table Ready */

/* FWFTR Register bit definitions */
#define R_MFWD_FWFTR_FEAR_SHIFT                   (0)  /* FRER Entry Address Read */
#define R_MFWD_FWFTR_FEAR_MASK                    0x7f

/* FWFTRR0 Register bit definitions */
#define R_MFWD_FWFTRR0_FSHLR_SHIFT                (0)  /* FRER Sequence History Length Read */
#define R_MFWD_FWFTRR0_FSHLR_MASK                 0xf

#define R_MFWD_FWFTRR0_FTNSR                      (1 << 8)  /* FRER Take No Sequence Read */

#define R_MFWD_FWFTRR0_FSRPVR                     (1 << 9)  /* FRER Sequence Recovery Pointer Valid Read */

#define R_MFWD_FWFTRR0_FSRRTR_SHIFT               (16)  /* FRER Set Recovery Remaining Ticks Read */
#define R_MFWD_FWFTRR0_FSRRTR_MASK                0x3ff0000

#define R_MFWD_FWFTRR0_FTR                        (1 << 31)  /* FRER Table Read */

/* FWFTRR1 Register bit definitions */
#define R_MFWD_FWFTRR1_FSHR_SHIFT                 (0)  /* FRER Sequence History Read */
#define R_MFWD_FWFTRR1_FSHR_MASK                  0x7fff

#define R_MFWD_FWFTRR1_FSRPR_SHIFT                (16)  /* FRER Sequence Recovery Pointer Read */
#define R_MFWD_FWFTRR1_FSRPR_MASK                 0x7f0000

/* FWFTRR2 Register bit definitions */
#define R_MFWD_FWFTRR2_FRSNR_SHIFT                (0)  /* FRER Recovery Sequence Number Read */
#define R_MFWD_FWFTRR2_FRSNR_MASK                 0xffff

#define R_MFWD_FWFTRR2_FRRTR_SHIFT                (16)  /* FRER Recovery Remaining Ticks Read */
#define R_MFWD_FWFTRR2_FRRTR_MASK                 0x3ff0000

/* FWSEQNGC Register bit definitions */
#define R_MFWD_FWSEQNGC_SEQNGRN_SHIFT             (0)  /* SEQuence Number Generation Routing Number */
#define R_MFWD_FWSEQNGC_SEQNGRN_MASK              0xff

#define R_MFWD_FWSEQNGC_SEQNGE                    (1 << 16)  /* SEQuence Number Generation Enable */

/* FWSEQNGM Register bit definitions */
#define R_MFWD_FWSEQNGM_SEQN_SHIFT                (0)  /* SEQuence Number */
#define R_MFWD_FWSEQNGM_SEQN_MASK                 0xffff

/* FWSEQNRC Register bit definitions */
#define R_MFWD_FWSEQNRC_SEQNR00                   (1 << 0)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR01                   (1 << 1)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR02                   (1 << 2)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR03                   (1 << 3)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR04                   (1 << 4)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR05                   (1 << 5)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR06                   (1 << 6)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR07                   (1 << 7)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR08                   (1 << 8)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR09                   (1 << 9)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR10                   (1 << 10)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR11                   (1 << 11)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR12                   (1 << 12)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR13                   (1 << 13)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR14                   (1 << 14)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR15                   (1 << 15)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR16                   (1 << 16)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR17                   (1 << 17)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR18                   (1 << 18)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR19                   (1 << 19)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR20                   (1 << 20)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR21                   (1 << 21)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR22                   (1 << 22)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR23                   (1 << 23)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR24                   (1 << 24)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR25                   (1 << 25)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR26                   (1 << 26)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR27                   (1 << 27)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR28                   (1 << 28)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR29                   (1 << 29)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR30                   (1 << 30)  /* Sequence Number Generation Reset n (n = 0 to 31) */

#define R_MFWD_FWSEQNRC_SEQNR31                   (1 << 31)  /* Sequence Number Generation Reset n (n = 0 to 31) */

/* FWCTFDCN Register bit definitions */
#define R_MFWD_FWCTFDCN_CTFDN_SHIFT               (0)  /* Cut-Through Forwarded Descriptor Number */
#define R_MFWD_FWCTFDCN_CTFDN_MASK                0xffffffff

/* FWLTHFDCN Register bit definitions */
#define R_MFWD_FWLTHFDCN_LTHFDN_SHIFT             (0)  /* Layer 3 Forwarded Descriptor Number */
#define R_MFWD_FWLTHFDCN_LTHFDN_MASK              0xffffffff

/* FWLTWFDCN Register bit definitions */
#define R_MFWD_FWLTWFDCN_LTWFDN_SHIFT             (0)  /* Layer 2 Forwarded Descriptor Number */
#define R_MFWD_FWLTWFDCN_LTWFDN_MASK              0xffffffff

/* FWPBFDCN Register bit definitions */
#define R_MFWD_FWPBFDCN_PBFDN_SHIFT               (0)  /* Port Based Forwarded Descriptor Number */
#define R_MFWD_FWPBFDCN_PBFDN_MASK                0xffffffff

/* FWMHLCN Register bit definitions */
#define R_MFWD_FWMHLCN_MHLN_SHIFT                 (0)  /* MAC Hardware Learn Number */
#define R_MFWD_FWMHLCN_MHLN_MASK                  0xffffffff

/* FWDDFDCN2 Register bit definitions */
#define R_MFWD_FWDDFDCN2_DDFDN_SHIFT              (0)  /* Direct Descriptor Forwarded Descriptor Number */
#define R_MFWD_FWDDFDCN2_DDFDN_MASK               0xffffffff

/* FWWMRDCN Register bit definitions */
#define R_MFWD_FWWMRDCN_WMRDN_SHIFT               (0)  /* Watermark rejected Descriptor Number */
#define R_MFWD_FWWMRDCN_WMRDN_MASK                0xffff

/* FWCTRDCN Register bit definitions */
#define R_MFWD_FWCTRDCN_CTRDN_SHIFT               (0)  /* Cut-through rejected Descriptor Number */
#define R_MFWD_FWCTRDCN_CTRDN_MASK                0xffff

/* FWLTHRDCN Register bit definitions */
#define R_MFWD_FWLTHRDCN_LTHRDN_SHIFT             (0)  /* Layer 3 rejected Descriptor Number */
#define R_MFWD_FWLTHRDCN_LTHRDN_MASK              0xffff

/* FWLTWRDCN Register bit definitions */
#define R_MFWD_FWLTWRDCN_LTWRDN_SHIFT             (0)  /* Layer 2 rejected Descriptor Number */
#define R_MFWD_FWLTWRDCN_LTWRDN_MASK              0xffff

/* FWPBRDCN Register bit definitions */
#define R_MFWD_FWPBRDCN_PBRDN_SHIFT               (0)  /* Port Based rejected Descriptor Number */
#define R_MFWD_FWPBRDCN_PBRDN_MASK                0xffff

/* FWDDRDCN2 Register bit definitions */
#define R_MFWD_FWDDRDCN2_DDRDN_SHIFT              (0)  /* Direct Descriptor rejected Descriptor Number */
#define R_MFWD_FWDDRDCN2_DDRDN_MASK               0xffff

/* FWPMFDCN Register bit definitions */
#define R_MFWD_FWPMFDCN_PMFDN_SHIFT               (0)  /* PSFP MSDU Filtered Descriptor Number */
#define R_MFWD_FWPMFDCN_PMFDN_MASK                0xffff

/* FWPMGDCN Register bit definitions */
#define R_MFWD_FWPMGDCN_PMGDN_SHIFT               (0)  /* PSFP Meter Green Descriptor Number */
#define R_MFWD_FWPMGDCN_PMGDN_MASK                0xffff

/* FWPMYDCN Register bit definitions */
#define R_MFWD_FWPMYDCN_PMYDN_SHIFT               (0)  /* PSFP Meter Yellow Descriptor Number */
#define R_MFWD_FWPMYDCN_PMYDN_MASK                0xffff

/* FWPMRDCN Register bit definitions */
#define R_MFWD_FWPMRDCN_PMRDN_SHIFT               (0)  /* PSFP Meter Red Descriptor Number */
#define R_MFWD_FWPMRDCN_PMRDN_MASK                0xffff

/* FWFRPPCN Register bit definitions */
#define R_MFWD_FWFRPPCN_PPC_SHIFT                 (0)  /* Passed Packet Count */
#define R_MFWD_FWFRPPCN_PPC_MASK                  0xffff

/* FWFRDPCN Register bit definitions */
#define R_MFWD_FWFRDPCN_DPC_SHIFT                 (0)  /* Discarded Packet Count */
#define R_MFWD_FWFRDPCN_DPC_MASK                  0xffff

/* FWEIS Register bit definitions */
#define R_MFWD_FWEIS_LTHSPFS                      (1 << 0)  /* Layer 3 Source Port Filtering Status Flag */

#define R_MFWD_FWEIS_LTHNTFS                      (1 << 2)  /* Layer 3 No Target Filtering Status Flag */

#define R_MFWD_FWEIS_LTHUFS                       (1 << 3)  /* Layer 3 Unknown Filtering Status Flag */

#define R_MFWD_FWEIS_LTWDSPFS                     (1 << 10)  /* Layer 2 Destination Source Port Filtering Status Flag */

#define R_MFWD_FWEIS_LTWSSPFS                     (1 << 11)  /* Layer 2 Source Source Port Filtering Status Flag */

#define R_MFWD_FWEIS_LTWVSPFS                     (1 << 12)  /* Layer 2 VLAN Source Port Filtering Status Flag */

#define R_MFWD_FWEIS_LTWNTFS                      (1 << 13)  /* Layer 2 No Target Filtering Status Flag */

#define R_MFWD_FWEIS_LTWSUFS                      (1 << 14)  /* Layer 2 Source Unknown Filtering Status Flag */

#define R_MFWD_FWEIS_LTWDUFS                      (1 << 15)  /* Layer 2 Destination Unknown Filtering Status Flag */

#define R_MFWD_FWEIS_LTWVUFS                      (1 << 16)  /* Layer 2 VLAN Unknown Filtering Status Flag */

#define R_MFWD_FWEIS_PBNTFS                       (1 << 17)  /* Port Based No Target Filtering Status Flag */

#define R_MFWD_FWEIS_SMHLFS                       (1 << 18)  /* Source MAC Hardware Learning Fail Status Flag */

#define R_MFWD_FWEIS_SMHMFS                       (1 << 19)  /* Source MAC Hardware Migration Fail Status Flag */

#define R_MFWD_FWEIS_WMCFS                        (1 << 22)  /* Watermark Critical Filtering Status Flag */

#define R_MFWD_FWEIS_WMFFS                        (1 << 23)  /* Watermark Flush Filtering Status Flag */

#define R_MFWD_FWEIS_WMISFS                       (1 << 24)  /* Watermark IPV Secure Filtering Status Flag */

#define R_MFWD_FWEIS_WMIUFS                       (1 << 25)  /* Watermark IPV Unsecure Filtering Status Flag */

#define R_MFWD_FWEIS_DDES                         (1 << 26)  /* Direct Descriptor Error Status Flag */

#define R_MFWD_FWEIS_DDSES                        (1 << 28)  /* Direct Descriptor Security Error Status Flag */

#define R_MFWD_FWEIS_DDNTFS                       (1 << 29)  /* Direct Descriptor No Target Filtering Status Flag */

/* FWEIE Register bit definitions */
#define R_MFWD_FWEIE_LTHSPFE                      (1 << 0)  /* Layer 3 Source Port Filtering Enable */

#define R_MFWD_FWEIE_LTHNTFE                      (1 << 2)  /* Layer 3 No Target Filtering Enable */

#define R_MFWD_FWEIE_LTHUFE                       (1 << 3)  /* Layer 3 Unknown Filtering Enable */

#define R_MFWD_FWEIE_LTWDSPFE                     (1 << 10)  /* Layer 2 Destination Source Port Filtering Enable */

#define R_MFWD_FWEIE_LTWSSPFE                     (1 << 11)  /* Layer 2 Source Source Port Filtering Enable */

#define R_MFWD_FWEIE_LTWVSPFE                     (1 << 12)  /* Layer 2 VLAN Source Port Filtering Enable */

#define R_MFWD_FWEIE_LTWNTFE                      (1 << 13)  /* Layer 2 No Target Filtering Enable */

#define R_MFWD_FWEIE_LTWSUFE                      (1 << 14)  /* Layer 2 Source Unknown Filtering Enable */

#define R_MFWD_FWEIE_LTWDUFE                      (1 << 15)  /* Layer 2 Destination Unknown Filtering Enable */

#define R_MFWD_FWEIE_LTWVUFE                      (1 << 16)  /* Layer 2 VLAN Unknown Filtering Enable */

#define R_MFWD_FWEIE_PBNTFE                       (1 << 17)  /* Port Based No Target Filtering Enable */

#define R_MFWD_FWEIE_SMHLFE                       (1 << 18)  /* Source MAC Hardware Learning Fail Enable */

#define R_MFWD_FWEIE_SMHMFE                       (1 << 19)  /* Source MAC Hardware Migration Fail Enable */

#define R_MFWD_FWEIE_WMCFE                        (1 << 22)  /* Watermark Critical Filtering Enable */

#define R_MFWD_FWEIE_WMFFE                        (1 << 23)  /* Watermark Flush Filtering Enable */

#define R_MFWD_FWEIE_WMISFE                       (1 << 24)  /* Watermark IPV Secure Filtering Enable */

#define R_MFWD_FWEIE_WMIUFE                       (1 << 25)  /* Watermark IPV Unsecure Filtering Enable */

#define R_MFWD_FWEIE_DDEE                         (1 << 26)  /* Direct Descriptor Error Enable */

#define R_MFWD_FWEIE_DDFEE                        (1 << 27)  /* Direct Descriptor Format Error Enable */

#define R_MFWD_FWEIE_DDSEE                        (1 << 28)  /* Direct Descriptor Security Error Enable */

#define R_MFWD_FWEIE_DDNTFE                       (1 << 29)  /* Direct Descriptor No Target Filtering Enable */

/* FWEID Register bit definitions */
#define R_MFWD_FWEID_LTHSPFD                      (1 << 0)  /* Layer 3 Source Port Filtering Disable */

#define R_MFWD_FWEID_LTHNTFD                      (1 << 2)  /* Layer 3 No Target Filtering Disable */

#define R_MFWD_FWEID_LTHUFD                       (1 << 3)  /* Layer 3 Unknown Filtering Disable */

#define R_MFWD_FWEID_LTWDSPFD                     (1 << 10)  /* Layer 2 Destination Source Port Filtering Disable */

#define R_MFWD_FWEID_LTWSSPFD                     (1 << 11)  /* Layer 2 Source Source Port Filtering Disable */

#define R_MFWD_FWEID_LTWVSPFD                     (1 << 12)  /* Layer 2 VLAN Source Port Filtering Disable */

#define R_MFWD_FWEID_LTWNTFD                      (1 << 13)  /* Layer 2 No Target Filtering Disable */

#define R_MFWD_FWEID_LTWSUFD                      (1 << 14)  /* Layer 2 Source Unknown Filtering Disable */

#define R_MFWD_FWEID_LTWDUFD                      (1 << 15)  /* Layer 2 Destination Unknown Filtering Disable */

#define R_MFWD_FWEID_LTWVUFD                      (1 << 16)  /* Layer 2 VLAN Unknown Filtering Disable */

#define R_MFWD_FWEID_PBNTFD                       (1 << 17)  /* Port Based No Target Filtering Disable */

#define R_MFWD_FWEID_SMHLFD                       (1 << 18)  /* Source MAC Hardware Learning Fail Disable */

#define R_MFWD_FWEID_SMHMFD                       (1 << 19)  /* Source MAC Hardware Migration Fail Disable */

#define R_MFWD_FWEID_WMCFD                        (1 << 22)  /* Watermark Critical Filtering Disable */

#define R_MFWD_FWEID_WMFFD                        (1 << 23)  /* Watermark Flush Filtering Disable */

#define R_MFWD_FWEID_WMISFD                       (1 << 24)  /* Watermark IPV Secure Filtering Disable */

#define R_MFWD_FWEID_WMIUFD                       (1 << 25)  /* Watermark IPV Unsecure Filtering Disable */

#define R_MFWD_FWEID_DDED                         (1 << 26)  /* Direct Descriptor Error Disable */

#define R_MFWD_FWEID_DDFED                        (1 << 27)  /* Direct Descriptor Format Error Disable */

#define R_MFWD_FWEID_DDSED                        (1 << 28)  /* Direct Descriptor Security Error Disable */

#define R_MFWD_FWEID_DDNTFD                       (1 << 29)  /* Direct Descriptor No Target Filtering Disable */

/* FWEIS1 Register bit definitions */
#define R_MFWD_FWEIS1_LTHTSES                     (1 << 1)  /* L3 Table Security Error Status Flag */

#define R_MFWD_FWEIS1_MACTSES                     (1 << 5)  /* MAC Table Security Error Status Flag */

#define R_MFWD_FWEIS1_VLANTSES                    (1 << 7)  /* VLAN Table Security Error Status Flag */

/* FWEIE1 Register bit definitions */
#define R_MFWD_FWEIE1_LTHTSEE                     (1 << 1)  /* L3 Table Security Error Enable */

#define R_MFWD_FWEIE1_MACTSEE                     (1 << 5)  /* MAC Table Security Error Enable */

#define R_MFWD_FWEIE1_VLANTSEE                    (1 << 7)  /* VLAN Table Security Error Enable */

/* FWEID1 Register bit definitions */
#define R_MFWD_FWEID1_LTHTSED                     (1 << 1)  /* L3 Table Security Error Disable */

#define R_MFWD_FWEID1_MACTSED                     (1 << 5)  /* MAC Table Security Error Disable */

#define R_MFWD_FWEID1_VLANTSED                    (1 << 7)  /* VLAN Table Security Error Disable */

#define R_MFWD_FWEID1_L23UEED                     (1 << 8)  /* Layer 2/Layer 3 Update Error Disable */

/* FWEIS2 Register bit definitions */
#define R_MFWD_FWEIS2_PMFS15 TO PMFS0_SHIFT       (0)  /* PSFP MSDU n Filtering Status Flag (n = 0 to 15) */
#define R_MFWD_FWEIS2_PMFS15 TO PMFS0_MASK        0xffff

/* FWEIE2 Register bit definitions */
#define R_MFWD_FWEIE2_PMFE15 TO PMFE0_SHIFT       (0)  /* PSFP MSDU n Filtering Enable (n = 0 to 15) */
#define R_MFWD_FWEIE2_PMFE15 TO PMFE0_MASK        0xffff
#  define R_MFWD_FWEIE2_PMFE15 TO PMFE0_0                 (0 << R_MFWD_FWEIE2_PMFE15 TO PMFE0_SHIFT)  /* Interrupt disabled. */
#  define R_MFWD_FWEIE2_PMFE15 TO PMFE0_1                 (1 << R_MFWD_FWEIE2_PMFE15 TO PMFE0_SHIFT)  /* Interrupt Enabled. */

/* FWEID2 Register bit definitions */
#define R_MFWD_FWEID2_PMFD15 TO PMFD0_SHIFT       (0)  /* PSFP MSDU n Filtering Disable (n = 0 to 15) */
#define R_MFWD_FWEID2_PMFD15 TO PMFD0_MASK        0xffff

/* FWEIS5 Register bit definitions */
#define R_MFWD_FWEIS5_PMRFS31 TO PMRFS0_SHIFT     (0)  /* PSFP Meter n Filtering Status Flag (n = 0 to 31) */
#define R_MFWD_FWEIS5_PMRFS31 TO PMRFS0_MASK      0xffffffff

/* FWEIE5 Register bit definitions */
#define R_MFWD_FWEIE5_PMRFE31 TO PMRFE0_SHIFT     (0)  /* PSFP Meter n Filtering Enable (n = 0 to 31) */
#define R_MFWD_FWEIE5_PMRFE31 TO PMRFE0_MASK      0xffffffff

/* FWEID5 Register bit definitions */
#define R_MFWD_FWEID5_PMRFD31 TO PMRFD0_SHIFT     (0)  /* PSFP Meter n Filtering Disable (n = 0 to 31) */
#define R_MFWD_FWEID5_PMRFD31 TO PMRFD0_MASK      0xffffffff

/* FWEIS60 Register bit definitions */
#define R_MFWD_FWEIS60_FFS31 TO FFS0_SHIFT        (0)  /* FRER n Filtering Status Flag (n = 96 to 127) */
#define R_MFWD_FWEIS60_FFS31 TO FFS0_MASK         0xffffffff

/* FWEIE60 Register bit definitions */
#define R_MFWD_FWEIE60_FFE31 TO FFE0_SHIFT        (0)  /* FRER n Filtering Enable (n = 96 to 127) */
#define R_MFWD_FWEIE60_FFE31 TO FFE0_MASK         0xffffffff

/* FWEID60 Register bit definitions */
#define R_MFWD_FWEID60_FFD31 TO FFD0_SHIFT        (0)  /* FRER n Filtering Disable (n = 96 to 127) */
#define R_MFWD_FWEID60_FFD31 TO FFD0_MASK         0xffffffff

/* FWEIS61 Register bit definitions */
#define R_MFWD_FWEIS61_FFS31 TO FFS0_SHIFT        (0)  /* FRER n Filtering Status Flag (n = 64 to 95) */
#define R_MFWD_FWEIS61_FFS31 TO FFS0_MASK         0xffffffff

/* FWEIE61 Register bit definitions */
#define R_MFWD_FWEIE61_FFE31 TO FFE0_SHIFT        (0)  /* FRER n Filtering Enable (n = 64 to 95) */
#define R_MFWD_FWEIE61_FFE31 TO FFE0_MASK         0xffffffff

/* FWEID61 Register bit definitions */
#define R_MFWD_FWEID61_FFD31 TO FFD0_SHIFT        (0)  /* FRER n Filtering Disable (n = 64 to 95) */
#define R_MFWD_FWEID61_FFD31 TO FFD0_MASK         0xffffffff

/* FWEIS62 Register bit definitions */
#define R_MFWD_FWEIS62_FFS31 TO FFS0_SHIFT        (0)  /* FRER n Filtering Status Flag (n = 32 to 63) */
#define R_MFWD_FWEIS62_FFS31 TO FFS0_MASK         0xffffffff

/* FWEIE62 Register bit definitions */
#define R_MFWD_FWEIE62_FFE31 TO FFE0_SHIFT        (0)  /* FRER n Filtering Enable (n = 32 to 63) */
#define R_MFWD_FWEIE62_FFE31 TO FFE0_MASK         0xffffffff

/* FWEID62 Register bit definitions */
#define R_MFWD_FWEID62_FFD31 TO FFD0_SHIFT        (0)  /* FRER n Filtering Disable (n = 32 to 63) */
#define R_MFWD_FWEID62_FFD31 TO FFD0_MASK         0xffffffff

/* FWEIS63 Register bit definitions */
#define R_MFWD_FWEIS63_FFS31 TO FFS0_SHIFT        (0)  /* FRER n Filtering Status Flag (n = 0 to 31) */
#define R_MFWD_FWEIS63_FFS31 TO FFS0_MASK         0xffffffff

/* FWEIE63 Register bit definitions */
#define R_MFWD_FWEIE63_FFE31 TO FFE0_SHIFT        (0)  /* FRER n Filtering Enable (n = 0 to 31) */
#define R_MFWD_FWEIE63_FFE31 TO FFE0_MASK         0xffffffff

/* FWEID63 Register bit definitions */
#define R_MFWD_FWEID63_FFD31 TO FFD0_SHIFT        (0)  /* FRER n Filtering Disable (n = 0 to 31) */
#define R_MFWD_FWEID63_FFD31 TO FFD0_MASK         0xffffffff

/* FWEIS70 Register bit definitions */
#define R_MFWD_FWEIS70_FOORS31 TO FOORS0_SHIFT    (0)  /* FRER n Out Of Range Status Flag (n = 96 to 127) */
#define R_MFWD_FWEIS70_FOORS31 TO FOORS0_MASK     0xffffffff

/* FWEIE70 Register bit definitions */
#define R_MFWD_FWEIE70_FOORE31 TO FOORE0_SHIFT    (0)  /* FRER n Out Of Range Enable (n = 96 to 127) */
#define R_MFWD_FWEIE70_FOORE31 TO FOORE0_MASK     0xffffffff

/* FWEID70 Register bit definitions */
#define R_MFWD_FWEID70_FOORD31 TO FOORD0_SHIFT    (0)  /* FRER n Out Of Range Disable (n = 96 to 127) */
#define R_MFWD_FWEID70_FOORD31 TO FOORD0_MASK     0xffffffff

/* FWEIS71 Register bit definitions */
#define R_MFWD_FWEIS71_FOORS31 TO FOORS0_SHIFT    (0)  /* FRER n Out Of Range Status Flag (n = 64 to 95) */
#define R_MFWD_FWEIS71_FOORS31 TO FOORS0_MASK     0xffffffff

/* FWEIE71 Register bit definitions */
#define R_MFWD_FWEIE71_FOORE31 TO FOORE0_SHIFT    (0)  /* FRER n Out Of Range Enable (n = 64 to 95) */
#define R_MFWD_FWEIE71_FOORE31 TO FOORE0_MASK     0xffffffff

/* FWEID71 Register bit definitions */
#define R_MFWD_FWEID71_FOORD31 TO FOORD0_SHIFT    (0)  /* FRER n Out Of Range Disable (n = 64 to 95) */
#define R_MFWD_FWEID71_FOORD31 TO FOORD0_MASK     0xffffffff

/* FWEIS72 Register bit definitions */
#define R_MFWD_FWEIS72_FOORS31 TO FOORS0_SHIFT    (0)  /* FRER n Out Of Range Status Flag (n = 32 to 63) */
#define R_MFWD_FWEIS72_FOORS31 TO FOORS0_MASK     0xffffffff

/* FWEIE72 Register bit definitions */
#define R_MFWD_FWEIE72_FOORE31 TO FOORE0_SHIFT    (0)  /* FRER n Out Of Range Enable (n = 32 to 63) */
#define R_MFWD_FWEIE72_FOORE31 TO FOORE0_MASK     0xffffffff

/* FWEID72 Register bit definitions */
#define R_MFWD_FWEID72_FOORD31 TO FOORD0_SHIFT    (0)  /* FRER n Out Of Range Disable (n = 32 to 63) */
#define R_MFWD_FWEID72_FOORD31 TO FOORD0_MASK     0xffffffff

/* FWEIS73 Register bit definitions */
#define R_MFWD_FWEIS73_FOORS31 TO FOORS0_SHIFT    (0)  /* FRER n Out Of Range Status Flag (n = 0 to 31) */
#define R_MFWD_FWEIS73_FOORS31 TO FOORS0_MASK     0xffffffff

/* FWEIE73 Register bit definitions */
#define R_MFWD_FWEIE73_FOORE31 TO FOORE0_SHIFT    (0)  /* FRER n Out Of Range Enable (n = 0 to 31) */
#define R_MFWD_FWEIE73_FOORE31 TO FOORE0_MASK     0xffffffff

/* FWEID73 Register bit definitions */
#define R_MFWD_FWEID73_FOORD31 TO FOORD0_SHIFT    (0)  /* FRER n Out Of Range Disable (n = 0 to 31) */
#define R_MFWD_FWEID73_FOORD31 TO FOORD0_MASK     0xffffffff

/* FWEIS80 Register bit definitions */
#define R_MFWD_FWEIS80_TOS31 TO TOS0_SHIFT        (0)  /* Timeout Status Flag n (n = 96 to 127) */
#define R_MFWD_FWEIS80_TOS31 TO TOS0_MASK         0xffffffff

/* FWEIE80 Register bit definitions */
#define R_MFWD_FWEIE80_TOE31 TO TOE0_SHIFT        (0)  /* Timeout Enable n (n = 96 to 127) */
#define R_MFWD_FWEIE80_TOE31 TO TOE0_MASK         0xffffffff

/* FWEID80 Register bit definitions */
#define R_MFWD_FWEID80_TOD31 TO TOD0_SHIFT        (0)  /* Timeout Disable n (n = 96 to 127) */
#define R_MFWD_FWEID80_TOD31 TO TOD0_MASK         0xffffffff

/* FWEIS81 Register bit definitions */
#define R_MFWD_FWEIS81_TOS31 TO TOS0_SHIFT        (0)  /* Timeout Status Flag n (n = 64 to 95) */
#define R_MFWD_FWEIS81_TOS31 TO TOS0_MASK         0xffffffff

/* FWEIE81 Register bit definitions */
#define R_MFWD_FWEIE81_TOE31 TO TOE0_SHIFT        (0)  /* Timeout Enable n (n = 64 to 95) */
#define R_MFWD_FWEIE81_TOE31 TO TOE0_MASK         0xffffffff

/* FWEID81 Register bit definitions */
#define R_MFWD_FWEID81_TOD31 TO TOD0_SHIFT        (0)  /* Timeout Disable n (n = 64 to 95) */
#define R_MFWD_FWEID81_TOD31 TO TOD0_MASK         0xffffffff

/* FWEIS82 Register bit definitions */
#define R_MFWD_FWEIS82_TOS31 TO TOS0_SHIFT        (0)  /* Timeout Status Flag n (n = 32 to 63) */
#define R_MFWD_FWEIS82_TOS31 TO TOS0_MASK         0xffffffff

/* FWEIE82 Register bit definitions */
#define R_MFWD_FWEIE82_TOE31 TO TOE0_SHIFT        (0)  /* Timeout Enable n (n = 32 to 63) */
#define R_MFWD_FWEIE82_TOE31 TO TOE0_MASK         0xffffffff

/* FWEID82 Register bit definitions */
#define R_MFWD_FWEID82_TOD31 TO TOD0_SHIFT        (0)  /* Timeout Disable n (n = 32 to 63) */
#define R_MFWD_FWEID82_TOD31 TO TOD0_MASK         0xffffffff

/* FWEIS83 Register bit definitions */
#define R_MFWD_FWEIS83_TOS31 TO TOS0_SHIFT        (0)  /* Timeout Status Flag n (n = 0 to 31) */
#define R_MFWD_FWEIS83_TOS31 TO TOS0_MASK         0xffffffff

/* FWEIE83 Register bit definitions */
#define R_MFWD_FWEIE83_TOE31 TO TOE0_SHIFT        (0)  /* Timeout Enable n (n = 0 to 31) */
#define R_MFWD_FWEIE83_TOE31 TO TOE0_MASK         0xffffffff

/* FWEID83 Register bit definitions */
#define R_MFWD_FWEID83_TOD31 TO TOD0_SHIFT        (0)  /* Timeout Disable n (n = 0 to 31) */
#define R_MFWD_FWEID83_TOD31 TO TOD0_MASK         0xffffffff

/* FWMIS0 Register bit definitions */
#define R_MFWD_FWMIS0_LTHTFS                      (1 << 0)  /* L3 Table Full Status Flag */

#define R_MFWD_FWMIS0_MACTFS                      (1 << 2)  /* MAC Table Full Status Flag */

#define R_MFWD_FWMIS0_VLANTFS                     (1 << 3)  /* VLAN Table Full Status Flag */

#define R_MFWD_FWMIS0_MACADAS                     (1 << 17)  /* MAC Address Deleted Aging Status Flag */

/* FWMIE0 Register bit definitions */
#define R_MFWD_FWMIE0_LTHTFE                      (1 << 0)  /* L3 Table Full Enable */

#define R_MFWD_FWMIE0_MACTFE                      (1 << 2)  /* MAC Table Full Enable */

#define R_MFWD_FWMIE0_VLANTFE                     (1 << 3)  /* VLAN Table Full Enable */

#define R_MFWD_FWMIE0_MACADAE                     (1 << 17)  /* MAC Address Deleted Aging Enable */

/* FWMID0 Register bit definitions */
#define R_MFWD_FWMID0_LTHTFD                      (1 << 0)  /* L3 Table Full Disable */

#define R_MFWD_FWMID0_MACTFD                      (1 << 2)  /* MAC Table Full Disable */

#define R_MFWD_FWMID0_VLANTFD                     (1 << 3)  /* VLAN Table Full Disable */

#define R_MFWD_FWMID0_MACADAD                     (1 << 17)  /* MAC Address Deleted Aging Disable */


/* Maximum number of channels */

#define MFWD_MAX_CHANNELS    128

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MFWD_H */

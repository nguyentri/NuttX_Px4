/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_canfd.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CANFD_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CANFD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CANFD Base Address */
#ifndef R_CANFD_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_CANFD_BASE           0x40380000
#else
#define R_CANFD_BASE           0x50380000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_CANFD_CH_STRIDE    0x00000004
#define R_CANFD_CH_BASE(ch)   (R_CANFD_BASE + ((uint32_t)(ch) * R_CANFD_CH_STRIDE))

/* CANFD Register Offsets */

#define R_CANFD_CFDC0NCFG_OFFSET     0x00000000  /* Nominal Bitrate Configuration Register */
#define R_CANFD_CFDC0CTR_OFFSET     0x00000004  /* Control Register */
#define R_CANFD_CFDC0STS_OFFSET     0x00000008  /* Status Register */
#define R_CANFD_CFDC0ERFL_OFFSET     0x0000000c  /* Error Flag Register */
#define R_CANFD_CFDGCFG_OFFSET     0x00000014  /* Global Configuration Register */
#define R_CANFD_CFDGCTR_OFFSET     0x00000018  /* Global Control Register */
#define R_CANFD_CFDGSTS_OFFSET     0x0000001c  /* Global Status Register */
#define R_CANFD_CFDGERFL_OFFSET     0x00000020  /* Global Error Flag Register */
#define R_CANFD_CFDGTSC_OFFSET     0x00000024  /* Global Timestamp Counter Register */
#define R_CANFD_CFDGAFLECTR_OFFSET     0x00000028  /* Global Acceptance Filter List Entry Control Register */
#define R_CANFD_CFDGAFLCFG_OFFSET     0x0000002c  /* Global Acceptance Filter List Configuration Register */
#define R_CANFD_CFDRMNB_OFFSET     0x00000030  /* RX Message Buffer Number Register */
#define R_CANFD_CFDRMND_OFFSET     0x00000034  /* RX Message Buffer New Data Register */
#define R_CANFD_CFDRMIEC_OFFSET     0x00000038  /* RX Message Buffer Interrupt Enable Configuration Register */
/* CFDRFCC%s Registers (0-1) */
#define R_CANFD_CFDRFCC0_OFFSET     0x0000003c  /* RX FIFO Configuration/Control Registers 0 */
#define R_CANFD_CFDRFCC1_OFFSET     0x00000040  /* RX FIFO Configuration/Control Registers 1 */
/* CFDRFSTS%s Registers (0-1) */
#define R_CANFD_CFDRFSTS0_OFFSET     0x00000044  /* RX FIFO Status Registers 0 */
#define R_CANFD_CFDRFSTS1_OFFSET     0x00000048  /* RX FIFO Status Registers 1 */
/* CFDRFPCTR%s Registers (0-1) */
#define R_CANFD_CFDRFPCTR0_OFFSET     0x0000004c  /* RX FIFO Pointer Control Registers 0 */
#define R_CANFD_CFDRFPCTR1_OFFSET     0x00000050  /* RX FIFO Pointer Control Registers 1 */
#define R_CANFD_CFDCFCC_OFFSET     0x00000054  /* Common FIFO Configuration/Control Register */
#define R_CANFD_CFDCFSTS_OFFSET     0x00000058  /* Common FIFO Status Register */
#define R_CANFD_CFDCFPCTR_OFFSET     0x0000005c  /* Common FIFO Pointer Control Register */
#define R_CANFD_CFDFESTS_OFFSET     0x00000060  /* FIFO Empty Status Register */
#define R_CANFD_CFDFFSTS_OFFSET     0x00000064  /* FIFO Full Status Register */
#define R_CANFD_CFDFMSTS_OFFSET     0x00000068  /* FIFO Message Lost Status Register */
#define R_CANFD_CFDRFISTS_OFFSET     0x0000006c  /* RX FIFO Interrupt Flag Status Register */
/* CFDTMC%s Registers (0-3) */
#define R_CANFD_CFDTMC0_OFFSET     0x00000070  /* TX Message Buffer Control Registers 0 */
#define R_CANFD_CFDTMC1_OFFSET     0x00000071  /* TX Message Buffer Control Registers 1 */
#define R_CANFD_CFDTMC2_OFFSET     0x00000072  /* TX Message Buffer Control Registers 2 */
#define R_CANFD_CFDTMC3_OFFSET     0x00000073  /* TX Message Buffer Control Registers 3 */
/* CFDTMSTS%s Registers (0-3) */
#define R_CANFD_CFDTMSTS0_OFFSET     0x00000074  /* TX Message Buffer Status Registers 0 */
#define R_CANFD_CFDTMSTS1_OFFSET     0x00000075  /* TX Message Buffer Status Registers 1 */
#define R_CANFD_CFDTMSTS2_OFFSET     0x00000076  /* TX Message Buffer Status Registers 2 */
#define R_CANFD_CFDTMSTS3_OFFSET     0x00000077  /* TX Message Buffer Status Registers 3 */
#define R_CANFD_CFDTMTRSTS_OFFSET     0x00000078  /* TX Message Buffer Transmission Request Status Register */
#define R_CANFD_CFDTMTARSTS_OFFSET     0x0000007c  /* TX Message Buffer Transmission Abort Request Status Register */
#define R_CANFD_CFDTMTCSTS_OFFSET     0x00000080  /* TX Message Buffer Transmission Completion Status Register */
#define R_CANFD_CFDTMTASTS_OFFSET     0x00000084  /* TX Message Buffer Transmission Abort Status Register */
#define R_CANFD_CFDTMIEC_OFFSET     0x00000088  /* TX Message Buffer Interrupt Enable Configuration Register */
#define R_CANFD_CFDTXQCC_OFFSET     0x0000008c  /* TX Queue Configuration/Control Register */
#define R_CANFD_CFDTXQSTS_OFFSET     0x00000090  /* TX Queue Status Register */
#define R_CANFD_CFDTXQPCTR_OFFSET     0x00000094  /* TX Queue Pointer Control Register */
#define R_CANFD_CFDTHLCC_OFFSET     0x00000098  /* TX History List Configuration/Control Register */
#define R_CANFD_CFDTHLSTS_OFFSET     0x0000009c  /* TX History List Status Register */
#define R_CANFD_CFDTHLPCTR_OFFSET     0x000000a0  /* TX History List Pointer Control Register */
#define R_CANFD_CFDGTINTSTS_OFFSET     0x000000a4  /* Global TX Interrupt Status Register */
#define R_CANFD_CFDGTSTCFG_OFFSET     0x000000a8  /* Global Test Configuration Register */
#define R_CANFD_CFDGTSTCTR_OFFSET     0x000000ac  /* Global Test Control Register */
#define R_CANFD_CFDGFDCFG_OFFSET     0x000000b0  /* Global FD Configuration Register */
#define R_CANFD_CFDGLOCKK_OFFSET     0x000000b8  /* Global Lock Key Register */
#define R_CANFD_CFDGAFLIGNENT_OFFSET     0x000000c0  /* Global AFL Ignore Entry Register */
#define R_CANFD_CFDGAFLIGNCTR_OFFSET     0x000000c4  /* Global AFL Ignore Control Register */
#define R_CANFD_CFDCDTCT_OFFSET     0x000000c8  /* DMA Transfer Control Register */
#define R_CANFD_CFDCDTSTS_OFFSET     0x000000cc  /* DMA Transfer Status Register */
#define R_CANFD_CFDGRSTC_OFFSET     0x000000d8  /* Global SW reset Register */
#define R_CANFD_CFDC0DCFG_OFFSET     0x00000100  /*  Data Bitrate Configuration Register */
#define R_CANFD_CFDC0FDCFG_OFFSET     0x00000104  /* CANFD Configuration Register */
#define R_CANFD_CFDC0FDCTR_OFFSET     0x00000108  /* CANFD Control Register */
#define R_CANFD_CFDC0FDSTS_OFFSET     0x0000010c  /* CANFD Status Register */
#define R_CANFD_CFDC0FDCRC_OFFSET     0x00000110  /* CANFD CRC Register */
/* CFDGAFLID%s Registers (1-16) */
#define R_CANFD_CFDGAFLID01_OFFSET     0x00000120  /* Global Acceptance Filter List ID Registers */
#define R_CANFD_CFDGAFLID02_OFFSET     0x00000130  /* Global Acceptance Filter List ID Registers */
#define R_CANFD_CFDGAFLID03_OFFSET     0x00000140  /* Global Acceptance Filter List ID Registers */
#define R_CANFD_CFDGAFLID04_OFFSET     0x00000150  /* Global Acceptance Filter List ID Registers */
#define R_CANFD_CFDGAFLID05_OFFSET     0x00000160  /* Global Acceptance Filter List ID Registers */
#define R_CANFD_CFDGAFLID06_OFFSET     0x00000170  /* Global Acceptance Filter List ID Registers */
#define R_CANFD_CFDGAFLID07_OFFSET     0x00000180  /* Global Acceptance Filter List ID Registers */
#define R_CANFD_CFDGAFLID08_OFFSET     0x00000190  /* Global Acceptance Filter List ID Registers */
#define R_CANFD_CFDGAFLID09_OFFSET     0x000001a0  /* Global Acceptance Filter List ID Registers */
#define R_CANFD_CFDGAFLID10_OFFSET     0x000001b0  /* Global Acceptance Filter List ID Registers */
#define R_CANFD_CFDGAFLID11_OFFSET     0x000001c0  /* Global Acceptance Filter List ID Registers */
#define R_CANFD_CFDGAFLID12_OFFSET     0x000001d0  /* Global Acceptance Filter List ID Registers */
#define R_CANFD_CFDGAFLID13_OFFSET     0x000001e0  /* Global Acceptance Filter List ID Registers */
#define R_CANFD_CFDGAFLID14_OFFSET     0x000001f0  /* Global Acceptance Filter List ID Registers */
#define R_CANFD_CFDGAFLID15_OFFSET     0x00000200  /* Global Acceptance Filter List ID Registers */
#define R_CANFD_CFDGAFLID16_OFFSET     0x00000210  /* Global Acceptance Filter List ID Registers */
/* CFDGAFLM%s Registers (1-16) */
#define R_CANFD_CFDGAFLM01_OFFSET     0x00000124  /* Global Acceptance Filter List Mask Registers */
#define R_CANFD_CFDGAFLM02_OFFSET     0x00000134  /* Global Acceptance Filter List Mask Registers */
#define R_CANFD_CFDGAFLM03_OFFSET     0x00000144  /* Global Acceptance Filter List Mask Registers */
#define R_CANFD_CFDGAFLM04_OFFSET     0x00000154  /* Global Acceptance Filter List Mask Registers */
#define R_CANFD_CFDGAFLM05_OFFSET     0x00000164  /* Global Acceptance Filter List Mask Registers */
#define R_CANFD_CFDGAFLM06_OFFSET     0x00000174  /* Global Acceptance Filter List Mask Registers */
#define R_CANFD_CFDGAFLM07_OFFSET     0x00000184  /* Global Acceptance Filter List Mask Registers */
#define R_CANFD_CFDGAFLM08_OFFSET     0x00000194  /* Global Acceptance Filter List Mask Registers */
#define R_CANFD_CFDGAFLM09_OFFSET     0x000001a4  /* Global Acceptance Filter List Mask Registers */
#define R_CANFD_CFDGAFLM10_OFFSET     0x000001b4  /* Global Acceptance Filter List Mask Registers */
#define R_CANFD_CFDGAFLM11_OFFSET     0x000001c4  /* Global Acceptance Filter List Mask Registers */
#define R_CANFD_CFDGAFLM12_OFFSET     0x000001d4  /* Global Acceptance Filter List Mask Registers */
#define R_CANFD_CFDGAFLM13_OFFSET     0x000001e4  /* Global Acceptance Filter List Mask Registers */
#define R_CANFD_CFDGAFLM14_OFFSET     0x000001f4  /* Global Acceptance Filter List Mask Registers */
#define R_CANFD_CFDGAFLM15_OFFSET     0x00000204  /* Global Acceptance Filter List Mask Registers */
#define R_CANFD_CFDGAFLM16_OFFSET     0x00000214  /* Global Acceptance Filter List Mask Registers */
/* CFDGAFLP0%s Registers (1-16) */
#define R_CANFD_CFDGAFLP001_OFFSET     0x00000128  /* Global Acceptance Filter List Pointer 0 Registers */
#define R_CANFD_CFDGAFLP002_OFFSET     0x00000138  /* Global Acceptance Filter List Pointer 0 Registers */
#define R_CANFD_CFDGAFLP003_OFFSET     0x00000148  /* Global Acceptance Filter List Pointer 0 Registers */
#define R_CANFD_CFDGAFLP004_OFFSET     0x00000158  /* Global Acceptance Filter List Pointer 0 Registers */
#define R_CANFD_CFDGAFLP005_OFFSET     0x00000168  /* Global Acceptance Filter List Pointer 0 Registers */
#define R_CANFD_CFDGAFLP006_OFFSET     0x00000178  /* Global Acceptance Filter List Pointer 0 Registers */
#define R_CANFD_CFDGAFLP007_OFFSET     0x00000188  /* Global Acceptance Filter List Pointer 0 Registers */
#define R_CANFD_CFDGAFLP008_OFFSET     0x00000198  /* Global Acceptance Filter List Pointer 0 Registers */
#define R_CANFD_CFDGAFLP009_OFFSET     0x000001a8  /* Global Acceptance Filter List Pointer 0 Registers */
#define R_CANFD_CFDGAFLP010_OFFSET     0x000001b8  /* Global Acceptance Filter List Pointer 0 Registers */
#define R_CANFD_CFDGAFLP011_OFFSET     0x000001c8  /* Global Acceptance Filter List Pointer 0 Registers */
#define R_CANFD_CFDGAFLP012_OFFSET     0x000001d8  /* Global Acceptance Filter List Pointer 0 Registers */
#define R_CANFD_CFDGAFLP013_OFFSET     0x000001e8  /* Global Acceptance Filter List Pointer 0 Registers */
#define R_CANFD_CFDGAFLP014_OFFSET     0x000001f8  /* Global Acceptance Filter List Pointer 0 Registers */
#define R_CANFD_CFDGAFLP015_OFFSET     0x00000208  /* Global Acceptance Filter List Pointer 0 Registers */
#define R_CANFD_CFDGAFLP016_OFFSET     0x00000218  /* Global Acceptance Filter List Pointer 0 Registers */
/* CFDGAFLP1%s Registers (1-16) */
#define R_CANFD_CFDGAFLP101_OFFSET     0x0000012c  /* Global Acceptance Filter List Pointer 1 Registers */
#define R_CANFD_CFDGAFLP102_OFFSET     0x0000013c  /* Global Acceptance Filter List Pointer 1 Registers */
#define R_CANFD_CFDGAFLP103_OFFSET     0x0000014c  /* Global Acceptance Filter List Pointer 1 Registers */
#define R_CANFD_CFDGAFLP104_OFFSET     0x0000015c  /* Global Acceptance Filter List Pointer 1 Registers */
#define R_CANFD_CFDGAFLP105_OFFSET     0x0000016c  /* Global Acceptance Filter List Pointer 1 Registers */
#define R_CANFD_CFDGAFLP106_OFFSET     0x0000017c  /* Global Acceptance Filter List Pointer 1 Registers */
#define R_CANFD_CFDGAFLP107_OFFSET     0x0000018c  /* Global Acceptance Filter List Pointer 1 Registers */
#define R_CANFD_CFDGAFLP108_OFFSET     0x0000019c  /* Global Acceptance Filter List Pointer 1 Registers */
#define R_CANFD_CFDGAFLP109_OFFSET     0x000001ac  /* Global Acceptance Filter List Pointer 1 Registers */
#define R_CANFD_CFDGAFLP110_OFFSET     0x000001bc  /* Global Acceptance Filter List Pointer 1 Registers */
#define R_CANFD_CFDGAFLP111_OFFSET     0x000001cc  /* Global Acceptance Filter List Pointer 1 Registers */
#define R_CANFD_CFDGAFLP112_OFFSET     0x000001dc  /* Global Acceptance Filter List Pointer 1 Registers */
#define R_CANFD_CFDGAFLP113_OFFSET     0x000001ec  /* Global Acceptance Filter List Pointer 1 Registers */
#define R_CANFD_CFDGAFLP114_OFFSET     0x000001fc  /* Global Acceptance Filter List Pointer 1 Registers */
#define R_CANFD_CFDGAFLP115_OFFSET     0x0000020c  /* Global Acceptance Filter List Pointer 1 Registers */
#define R_CANFD_CFDGAFLP116_OFFSET     0x0000021c  /* Global Acceptance Filter List Pointer 1 Registers */
/* CFDRPGACC%s Registers (0-63) */
#define R_CANFD_CFDRPGACC00_OFFSET     0x00000280  /* RAM Test Page Access Registers 00 */
#define R_CANFD_CFDRPGACC01_OFFSET     0x00000284  /* RAM Test Page Access Registers 01 */
#define R_CANFD_CFDRPGACC02_OFFSET     0x00000288  /* RAM Test Page Access Registers 02 */
#define R_CANFD_CFDRPGACC03_OFFSET     0x0000028c  /* RAM Test Page Access Registers 03 */
#define R_CANFD_CFDRPGACC04_OFFSET     0x00000290  /* RAM Test Page Access Registers 04 */
#define R_CANFD_CFDRPGACC05_OFFSET     0x00000294  /* RAM Test Page Access Registers 05 */
#define R_CANFD_CFDRPGACC06_OFFSET     0x00000298  /* RAM Test Page Access Registers 06 */
#define R_CANFD_CFDRPGACC07_OFFSET     0x0000029c  /* RAM Test Page Access Registers 07 */
#define R_CANFD_CFDRPGACC08_OFFSET     0x000002a0  /* RAM Test Page Access Registers 08 */
#define R_CANFD_CFDRPGACC09_OFFSET     0x000002a4  /* RAM Test Page Access Registers 09 */
#define R_CANFD_CFDRPGACC10_OFFSET     0x000002a8  /* RAM Test Page Access Registers 10 */
#define R_CANFD_CFDRPGACC11_OFFSET     0x000002ac  /* RAM Test Page Access Registers 11 */
#define R_CANFD_CFDRPGACC12_OFFSET     0x000002b0  /* RAM Test Page Access Registers 12 */
#define R_CANFD_CFDRPGACC13_OFFSET     0x000002b4  /* RAM Test Page Access Registers 13 */
#define R_CANFD_CFDRPGACC14_OFFSET     0x000002b8  /* RAM Test Page Access Registers 14 */
#define R_CANFD_CFDRPGACC15_OFFSET     0x000002bc  /* RAM Test Page Access Registers 15 */
#define R_CANFD_CFDRPGACC16_OFFSET     0x000002c0  /* RAM Test Page Access Registers 16 */
#define R_CANFD_CFDRPGACC17_OFFSET     0x000002c4  /* RAM Test Page Access Registers 17 */
#define R_CANFD_CFDRPGACC18_OFFSET     0x000002c8  /* RAM Test Page Access Registers 18 */
#define R_CANFD_CFDRPGACC19_OFFSET     0x000002cc  /* RAM Test Page Access Registers 19 */
#define R_CANFD_CFDRPGACC20_OFFSET     0x000002d0  /* RAM Test Page Access Registers 20 */
#define R_CANFD_CFDRPGACC21_OFFSET     0x000002d4  /* RAM Test Page Access Registers 21 */
#define R_CANFD_CFDRPGACC22_OFFSET     0x000002d8  /* RAM Test Page Access Registers 22 */
#define R_CANFD_CFDRPGACC23_OFFSET     0x000002dc  /* RAM Test Page Access Registers 23 */
#define R_CANFD_CFDRPGACC24_OFFSET     0x000002e0  /* RAM Test Page Access Registers 24 */
#define R_CANFD_CFDRPGACC25_OFFSET     0x000002e4  /* RAM Test Page Access Registers 25 */
#define R_CANFD_CFDRPGACC26_OFFSET     0x000002e8  /* RAM Test Page Access Registers 26 */
#define R_CANFD_CFDRPGACC27_OFFSET     0x000002ec  /* RAM Test Page Access Registers 27 */
#define R_CANFD_CFDRPGACC28_OFFSET     0x000002f0  /* RAM Test Page Access Registers 28 */
#define R_CANFD_CFDRPGACC29_OFFSET     0x000002f4  /* RAM Test Page Access Registers 29 */
#define R_CANFD_CFDRPGACC30_OFFSET     0x000002f8  /* RAM Test Page Access Registers 30 */
#define R_CANFD_CFDRPGACC31_OFFSET     0x000002fc  /* RAM Test Page Access Registers 31 */
#define R_CANFD_CFDRPGACC32_OFFSET     0x00000300  /* RAM Test Page Access Registers 32 */
#define R_CANFD_CFDRPGACC33_OFFSET     0x00000304  /* RAM Test Page Access Registers 33 */
#define R_CANFD_CFDRPGACC34_OFFSET     0x00000308  /* RAM Test Page Access Registers 34 */
#define R_CANFD_CFDRPGACC35_OFFSET     0x0000030c  /* RAM Test Page Access Registers 35 */
#define R_CANFD_CFDRPGACC36_OFFSET     0x00000310  /* RAM Test Page Access Registers 36 */
#define R_CANFD_CFDRPGACC37_OFFSET     0x00000314  /* RAM Test Page Access Registers 37 */
#define R_CANFD_CFDRPGACC38_OFFSET     0x00000318  /* RAM Test Page Access Registers 38 */
#define R_CANFD_CFDRPGACC39_OFFSET     0x0000031c  /* RAM Test Page Access Registers 39 */
#define R_CANFD_CFDRPGACC40_OFFSET     0x00000320  /* RAM Test Page Access Registers 40 */
#define R_CANFD_CFDRPGACC41_OFFSET     0x00000324  /* RAM Test Page Access Registers 41 */
#define R_CANFD_CFDRPGACC42_OFFSET     0x00000328  /* RAM Test Page Access Registers 42 */
#define R_CANFD_CFDRPGACC43_OFFSET     0x0000032c  /* RAM Test Page Access Registers 43 */
#define R_CANFD_CFDRPGACC44_OFFSET     0x00000330  /* RAM Test Page Access Registers 44 */
#define R_CANFD_CFDRPGACC45_OFFSET     0x00000334  /* RAM Test Page Access Registers 45 */
#define R_CANFD_CFDRPGACC46_OFFSET     0x00000338  /* RAM Test Page Access Registers 46 */
#define R_CANFD_CFDRPGACC47_OFFSET     0x0000033c  /* RAM Test Page Access Registers 47 */
#define R_CANFD_CFDRPGACC48_OFFSET     0x00000340  /* RAM Test Page Access Registers 48 */
#define R_CANFD_CFDRPGACC49_OFFSET     0x00000344  /* RAM Test Page Access Registers 49 */
#define R_CANFD_CFDRPGACC50_OFFSET     0x00000348  /* RAM Test Page Access Registers 50 */
#define R_CANFD_CFDRPGACC51_OFFSET     0x0000034c  /* RAM Test Page Access Registers 51 */
#define R_CANFD_CFDRPGACC52_OFFSET     0x00000350  /* RAM Test Page Access Registers 52 */
#define R_CANFD_CFDRPGACC53_OFFSET     0x00000354  /* RAM Test Page Access Registers 53 */
#define R_CANFD_CFDRPGACC54_OFFSET     0x00000358  /* RAM Test Page Access Registers 54 */
#define R_CANFD_CFDRPGACC55_OFFSET     0x0000035c  /* RAM Test Page Access Registers 55 */
#define R_CANFD_CFDRPGACC56_OFFSET     0x00000360  /* RAM Test Page Access Registers 56 */
#define R_CANFD_CFDRPGACC57_OFFSET     0x00000364  /* RAM Test Page Access Registers 57 */
#define R_CANFD_CFDRPGACC58_OFFSET     0x00000368  /* RAM Test Page Access Registers 58 */
#define R_CANFD_CFDRPGACC59_OFFSET     0x0000036c  /* RAM Test Page Access Registers 59 */
#define R_CANFD_CFDRPGACC60_OFFSET     0x00000370  /* RAM Test Page Access Registers 60 */
#define R_CANFD_CFDRPGACC61_OFFSET     0x00000374  /* RAM Test Page Access Registers 61 */
#define R_CANFD_CFDRPGACC62_OFFSET     0x00000378  /* RAM Test Page Access Registers 62 */
#define R_CANFD_CFDRPGACC63_OFFSET     0x0000037c  /* RAM Test Page Access Registers 63 */
/* CFDRFID%s Registers (0-1) */
#define R_CANFD_CFDRFID0_OFFSET     0x00000520  /* RX FIFO Access ID Register 0 */
#define R_CANFD_CFDRFID1_OFFSET     0x0000056c  /* RX FIFO Access ID Register 1 */
/* CFDRFPTR%s Registers (0-1) */
#define R_CANFD_CFDRFPTR0_OFFSET     0x00000524  /* RX FIFO Access Pointer Register 0 */
#define R_CANFD_CFDRFPTR1_OFFSET     0x00000570  /* RX FIFO Access Pointer Register 1 */
/* CFDRFFDSTS%s Registers (0-1) */
#define R_CANFD_CFDRFFDSTS0_OFFSET     0x00000528  /* RX FIFO Access CANFD Status Register 0 */
#define R_CANFD_CFDRFFDSTS1_OFFSET     0x00000574  /* RX FIFO Access CANFD Status Register 1 */
/* CFDRFDF%s_0 Registers (0-1) */
#define R_CANFD_CFDRFDF0_0_OFFSET     0x0000052c  /* RX FIFO Access Data Field 0 Register 0 */
#define R_CANFD_CFDRFDF1_0_OFFSET     0x00000578  /* RX FIFO Access Data Field 0 Register 1 */
/* CFDRFDF%s_1 Registers (0-1) */
#define R_CANFD_CFDRFDF0_1_OFFSET     0x00000530  /* RX FIFO Access Data Field 1 Register 0 */
#define R_CANFD_CFDRFDF1_1_OFFSET     0x0000057c  /* RX FIFO Access Data Field 1 Register 1 */
/* CFDRFDF%s_2 Registers (0-1) */
#define R_CANFD_CFDRFDF0_2_OFFSET     0x00000534  /* RX FIFO Access Data Field 2 Register 0 */
#define R_CANFD_CFDRFDF1_2_OFFSET     0x00000580  /* RX FIFO Access Data Field 2 Register 1 */
/* CFDRFDF%s_3 Registers (0-1) */
#define R_CANFD_CFDRFDF0_3_OFFSET     0x00000538  /* RX FIFO Access Data Field 3 Register 0 */
#define R_CANFD_CFDRFDF1_3_OFFSET     0x00000584  /* RX FIFO Access Data Field 3 Register 1 */
/* CFDRFDF%s_4 Registers (0-1) */
#define R_CANFD_CFDRFDF0_4_OFFSET     0x0000053c  /* RX FIFO Access Data Field 4 Register 0 */
#define R_CANFD_CFDRFDF1_4_OFFSET     0x00000588  /* RX FIFO Access Data Field 4 Register 1 */
/* CFDRFDF%s_5 Registers (0-1) */
#define R_CANFD_CFDRFDF0_5_OFFSET     0x00000540  /* RX FIFO Access Data Field 5 Register 0 */
#define R_CANFD_CFDRFDF1_5_OFFSET     0x0000058c  /* RX FIFO Access Data Field 5 Register 1 */
/* CFDRFDF%s_6 Registers (0-1) */
#define R_CANFD_CFDRFDF0_6_OFFSET     0x00000544  /* RX FIFO Access Data Field 6 Register 0 */
#define R_CANFD_CFDRFDF1_6_OFFSET     0x00000590  /* RX FIFO Access Data Field 6 Register 1 */
/* CFDRFDF%s_7 Registers (0-1) */
#define R_CANFD_CFDRFDF0_7_OFFSET     0x00000548  /* RX FIFO Access Data Field 7 Register 0 */
#define R_CANFD_CFDRFDF1_7_OFFSET     0x00000594  /* RX FIFO Access Data Field 7 Register 1 */
/* CFDRFDF%s_8 Registers (0-1) */
#define R_CANFD_CFDRFDF0_8_OFFSET     0x0000054c  /* RX FIFO Access Data Field 8 Register 0 */
#define R_CANFD_CFDRFDF1_8_OFFSET     0x00000598  /* RX FIFO Access Data Field 8 Register 1 */
/* CFDRFDF%s_9 Registers (0-1) */
#define R_CANFD_CFDRFDF0_9_OFFSET     0x00000550  /* RX FIFO Access Data Field 9 Register 0 */
#define R_CANFD_CFDRFDF1_9_OFFSET     0x0000059c  /* RX FIFO Access Data Field 9 Register 1 */
/* CFDRFDF%s_10 Registers (0-1) */
#define R_CANFD_CFDRFDF0_10_OFFSET     0x00000554  /* RX FIFO Access Data Field 10 Register 0 */
#define R_CANFD_CFDRFDF1_10_OFFSET     0x000005a0  /* RX FIFO Access Data Field 10 Register 1 */
/* CFDRFDF%s_11 Registers (0-1) */
#define R_CANFD_CFDRFDF0_11_OFFSET     0x00000558  /* RX FIFO Access Data Field 11 Register 0 */
#define R_CANFD_CFDRFDF1_11_OFFSET     0x000005a4  /* RX FIFO Access Data Field 11 Register 1 */
/* CFDRFDF%s_12 Registers (0-1) */
#define R_CANFD_CFDRFDF0_12_OFFSET     0x0000055c  /* RX FIFO Access Data Field 12 Register 0 */
#define R_CANFD_CFDRFDF1_12_OFFSET     0x000005a8  /* RX FIFO Access Data Field 12 Register 1 */
/* CFDRFDF%s_13 Registers (0-1) */
#define R_CANFD_CFDRFDF0_13_OFFSET     0x00000560  /* RX FIFO Access Data Field 13 Register 0 */
#define R_CANFD_CFDRFDF1_13_OFFSET     0x000005ac  /* RX FIFO Access Data Field 13 Register 1 */
/* CFDRFDF%s_14 Registers (0-1) */
#define R_CANFD_CFDRFDF0_14_OFFSET     0x00000564  /* RX FIFO Access Data Field 14 Register 0 */
#define R_CANFD_CFDRFDF1_14_OFFSET     0x000005b0  /* RX FIFO Access Data Field 14 Register 1 */
/* CFDRFDF%s_15 Registers (0-1) */
#define R_CANFD_CFDRFDF0_15_OFFSET     0x00000568  /* RX FIFO Access Data Field 15 Register 0 */
#define R_CANFD_CFDRFDF1_15_OFFSET     0x000005b4  /* RX FIFO Access Data Field 15 Register 1 */
#define R_CANFD_CFDCFID_OFFSET     0x000005b8  /* Common FIFO Access ID Register */
#define R_CANFD_CFDCFPTR_OFFSET     0x000005bc  /* Common FIFO Access Pointer Register */
#define R_CANFD_CFDCFFDCSTS_OFFSET     0x000005c0  /* Common FIFO Access CANFD Control/Status Register */
/* CFDCFDF%s Registers (0-15) */
#define R_CANFD_CFDCFDF00_OFFSET     0x000005c4  /* Common FIFO Access Data Field 00 Registers */
#define R_CANFD_CFDCFDF01_OFFSET     0x000005c8  /* Common FIFO Access Data Field 01 Registers */
#define R_CANFD_CFDCFDF02_OFFSET     0x000005cc  /* Common FIFO Access Data Field 02 Registers */
#define R_CANFD_CFDCFDF03_OFFSET     0x000005d0  /* Common FIFO Access Data Field 03 Registers */
#define R_CANFD_CFDCFDF04_OFFSET     0x000005d4  /* Common FIFO Access Data Field 04 Registers */
#define R_CANFD_CFDCFDF05_OFFSET     0x000005d8  /* Common FIFO Access Data Field 05 Registers */
#define R_CANFD_CFDCFDF06_OFFSET     0x000005dc  /* Common FIFO Access Data Field 06 Registers */
#define R_CANFD_CFDCFDF07_OFFSET     0x000005e0  /* Common FIFO Access Data Field 07 Registers */
#define R_CANFD_CFDCFDF08_OFFSET     0x000005e4  /* Common FIFO Access Data Field 08 Registers */
#define R_CANFD_CFDCFDF09_OFFSET     0x000005e8  /* Common FIFO Access Data Field 09 Registers */
#define R_CANFD_CFDCFDF10_OFFSET     0x000005ec  /* Common FIFO Access Data Field 10 Registers */
#define R_CANFD_CFDCFDF11_OFFSET     0x000005f0  /* Common FIFO Access Data Field 11 Registers */
#define R_CANFD_CFDCFDF12_OFFSET     0x000005f4  /* Common FIFO Access Data Field 12 Registers */
#define R_CANFD_CFDCFDF13_OFFSET     0x000005f8  /* Common FIFO Access Data Field 13 Registers */
#define R_CANFD_CFDCFDF14_OFFSET     0x000005fc  /* Common FIFO Access Data Field 14 Registers */
#define R_CANFD_CFDCFDF15_OFFSET     0x00000600  /* Common FIFO Access Data Field 15 Registers */
/* CFDTMID%s Registers (0-3) */
#define R_CANFD_CFDTMID0_OFFSET     0x00000604  /* TX Message Buffer ID Registers */
#define R_CANFD_CFDTMID1_OFFSET     0x00000650  /* TX Message Buffer ID Registers */
#define R_CANFD_CFDTMID2_OFFSET     0x0000069c  /* TX Message Buffer ID Registers */
#define R_CANFD_CFDTMID3_OFFSET     0x000006e8  /* TX Message Buffer ID Registers */
/* CFDTMPTR%s Registers (0-3) */
#define R_CANFD_CFDTMPTR0_OFFSET     0x00000608  /* TX Message Buffer Pointer Register */
#define R_CANFD_CFDTMPTR1_OFFSET     0x00000654  /* TX Message Buffer Pointer Register */
#define R_CANFD_CFDTMPTR2_OFFSET     0x000006a0  /* TX Message Buffer Pointer Register */
#define R_CANFD_CFDTMPTR3_OFFSET     0x000006ec  /* TX Message Buffer Pointer Register */
/* CFDTMFDCTR%s Registers (0-3) */
#define R_CANFD_CFDTMFDCTR0_OFFSET     0x0000060c  /* TX Message Buffer CANFD Control Register */
#define R_CANFD_CFDTMFDCTR1_OFFSET     0x00000658  /* TX Message Buffer CANFD Control Register */
#define R_CANFD_CFDTMFDCTR2_OFFSET     0x000006a4  /* TX Message Buffer CANFD Control Register */
#define R_CANFD_CFDTMFDCTR3_OFFSET     0x000006f0  /* TX Message Buffer CANFD Control Register */
/* CFDTMDF%s_0 Registers (0-3) */
#define R_CANFD_CFDTMDF0_0_OFFSET     0x00000610  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF1_0_OFFSET     0x0000065c  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF2_0_OFFSET     0x000006a8  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF3_0_OFFSET     0x000006f4  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_1 Registers (0-3) */
#define R_CANFD_CFDTMDF0_1_OFFSET     0x00000614  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF1_1_OFFSET     0x00000660  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF2_1_OFFSET     0x000006ac  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF3_1_OFFSET     0x000006f8  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_2 Registers (0-3) */
#define R_CANFD_CFDTMDF0_2_OFFSET     0x00000618  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF1_2_OFFSET     0x00000664  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF2_2_OFFSET     0x000006b0  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF3_2_OFFSET     0x000006fc  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_3 Registers (0-3) */
#define R_CANFD_CFDTMDF0_3_OFFSET     0x0000061c  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF1_3_OFFSET     0x00000668  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF2_3_OFFSET     0x000006b4  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF3_3_OFFSET     0x00000700  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_4 Registers (0-3) */
#define R_CANFD_CFDTMDF0_4_OFFSET     0x00000620  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF1_4_OFFSET     0x0000066c  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF2_4_OFFSET     0x000006b8  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF3_4_OFFSET     0x00000704  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_5 Registers (0-3) */
#define R_CANFD_CFDTMDF0_5_OFFSET     0x00000624  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF1_5_OFFSET     0x00000670  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF2_5_OFFSET     0x000006bc  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF3_5_OFFSET     0x00000708  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_6 Registers (0-3) */
#define R_CANFD_CFDTMDF0_6_OFFSET     0x00000628  /* TX Message Buffer Data Field Register  */
#define R_CANFD_CFDTMDF1_6_OFFSET     0x00000674  /* TX Message Buffer Data Field Register  */
#define R_CANFD_CFDTMDF2_6_OFFSET     0x000006c0  /* TX Message Buffer Data Field Register  */
#define R_CANFD_CFDTMDF3_6_OFFSET     0x0000070c  /* TX Message Buffer Data Field Register  */
/* CFDTMDF%s_7 Registers (0-3) */
#define R_CANFD_CFDTMDF0_7_OFFSET     0x0000062c  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF1_7_OFFSET     0x00000678  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF2_7_OFFSET     0x000006c4  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF3_7_OFFSET     0x00000710  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_8 Registers (0-3) */
#define R_CANFD_CFDTMDF0_8_OFFSET     0x00000630  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF1_8_OFFSET     0x0000067c  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF2_8_OFFSET     0x000006c8  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF3_8_OFFSET     0x00000714  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_9 Registers (0-3) */
#define R_CANFD_CFDTMDF0_9_OFFSET     0x00000634  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF1_9_OFFSET     0x00000680  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF2_9_OFFSET     0x000006cc  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF3_9_OFFSET     0x00000718  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_10 Registers (0-3) */
#define R_CANFD_CFDTMDF0_10_OFFSET     0x00000638  /* TX Message Buffer Data Field Register  */
#define R_CANFD_CFDTMDF1_10_OFFSET     0x00000684  /* TX Message Buffer Data Field Register  */
#define R_CANFD_CFDTMDF2_10_OFFSET     0x000006d0  /* TX Message Buffer Data Field Register  */
#define R_CANFD_CFDTMDF3_10_OFFSET     0x0000071c  /* TX Message Buffer Data Field Register  */
/* CFDTMDF%s_11 Registers (0-3) */
#define R_CANFD_CFDTMDF0_11_OFFSET     0x0000063c  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF1_11_OFFSET     0x00000688  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF2_11_OFFSET     0x000006d4  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF3_11_OFFSET     0x00000720  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_12 Registers (0-3) */
#define R_CANFD_CFDTMDF0_12_OFFSET     0x00000640  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF1_12_OFFSET     0x0000068c  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF2_12_OFFSET     0x000006d8  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF3_12_OFFSET     0x00000724  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_13 Registers (0-3) */
#define R_CANFD_CFDTMDF0_13_OFFSET     0x00000644  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF1_13_OFFSET     0x00000690  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF2_13_OFFSET     0x000006dc  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF3_13_OFFSET     0x00000728  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_14 Registers (0-3) */
#define R_CANFD_CFDTMDF0_14_OFFSET     0x00000648  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF1_14_OFFSET     0x00000694  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF2_14_OFFSET     0x000006e0  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF3_14_OFFSET     0x0000072c  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_15 Registers (0-3) */
#define R_CANFD_CFDTMDF0_15_OFFSET     0x0000064c  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF1_15_OFFSET     0x00000698  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF2_15_OFFSET     0x000006e4  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTMDF3_15_OFFSET     0x00000730  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTHLACC0_OFFSET     0x00000740  /* TX History List Access Register 0 */
#define R_CANFD_CFDTHLACC1_OFFSET     0x00000744  /* TX History List Access Register 1 */
/* CFDRMID%s Registers (0-7) */
#define R_CANFD_CFDRMID0_OFFSET     0x00000920  /* RX Message Buffer ID Registers */
#define R_CANFD_CFDRMID1_OFFSET     0x0000096c  /* RX Message Buffer ID Registers */
#define R_CANFD_CFDRMID2_OFFSET     0x000009b8  /* RX Message Buffer ID Registers */
#define R_CANFD_CFDRMID3_OFFSET     0x00000a04  /* RX Message Buffer ID Registers */
#define R_CANFD_CFDRMID4_OFFSET     0x00000a50  /* RX Message Buffer ID Registers */
#define R_CANFD_CFDRMID5_OFFSET     0x00000a9c  /* RX Message Buffer ID Registers */
#define R_CANFD_CFDRMID6_OFFSET     0x00000ae8  /* RX Message Buffer ID Registers */
#define R_CANFD_CFDRMID7_OFFSET     0x00000b34  /* RX Message Buffer ID Registers */
/* CFDRMPTR%s Registers (0-7) */
#define R_CANFD_CFDRMPTR0_OFFSET     0x00000924  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR1_OFFSET     0x00000970  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR2_OFFSET     0x000009bc  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR3_OFFSET     0x00000a08  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR4_OFFSET     0x00000a54  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR5_OFFSET     0x00000aa0  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR6_OFFSET     0x00000aec  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR7_OFFSET     0x00000b38  /* RX Message Buffer Pointer Registers */
/* CFDRMFDSTS%s Registers (0-7) */
#define R_CANFD_CFDRMFDSTS0_OFFSET     0x00000928  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS1_OFFSET     0x00000974  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS2_OFFSET     0x000009c0  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS3_OFFSET     0x00000a0c  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS4_OFFSET     0x00000a58  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS5_OFFSET     0x00000aa4  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS6_OFFSET     0x00000af0  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS7_OFFSET     0x00000b3c  /* RX Message Buffer CANFD Status Registers */
/* CFDRMDF%s_0 Registers (0-7) */
#define R_CANFD_CFDRMDF0_0_OFFSET     0x0000092c  /* RX Message Buffer Data Field 0 Registers */
#define R_CANFD_CFDRMDF1_0_OFFSET     0x00000978  /* RX Message Buffer Data Field 0 Registers */
#define R_CANFD_CFDRMDF2_0_OFFSET     0x000009c4  /* RX Message Buffer Data Field 0 Registers */
#define R_CANFD_CFDRMDF3_0_OFFSET     0x00000a10  /* RX Message Buffer Data Field 0 Registers */
#define R_CANFD_CFDRMDF4_0_OFFSET     0x00000a5c  /* RX Message Buffer Data Field 0 Registers */
#define R_CANFD_CFDRMDF5_0_OFFSET     0x00000aa8  /* RX Message Buffer Data Field 0 Registers */
#define R_CANFD_CFDRMDF6_0_OFFSET     0x00000af4  /* RX Message Buffer Data Field 0 Registers */
#define R_CANFD_CFDRMDF7_0_OFFSET     0x00000b40  /* RX Message Buffer Data Field 0 Registers */
/* CFDRMDF%s_1 Registers (0-7) */
#define R_CANFD_CFDRMDF0_1_OFFSET     0x00000930  /* RX Message Buffer Data Field 1 Registers */
#define R_CANFD_CFDRMDF1_1_OFFSET     0x0000097c  /* RX Message Buffer Data Field 1 Registers */
#define R_CANFD_CFDRMDF2_1_OFFSET     0x000009c8  /* RX Message Buffer Data Field 1 Registers */
#define R_CANFD_CFDRMDF3_1_OFFSET     0x00000a14  /* RX Message Buffer Data Field 1 Registers */
#define R_CANFD_CFDRMDF4_1_OFFSET     0x00000a60  /* RX Message Buffer Data Field 1 Registers */
#define R_CANFD_CFDRMDF5_1_OFFSET     0x00000aac  /* RX Message Buffer Data Field 1 Registers */
#define R_CANFD_CFDRMDF6_1_OFFSET     0x00000af8  /* RX Message Buffer Data Field 1 Registers */
#define R_CANFD_CFDRMDF7_1_OFFSET     0x00000b44  /* RX Message Buffer Data Field 1 Registers */
/* CFDRMDF%s_2 Registers (0-7) */
#define R_CANFD_CFDRMDF0_2_OFFSET     0x00000934  /* RX Message Buffer Data Field 2 Registers */
#define R_CANFD_CFDRMDF1_2_OFFSET     0x00000980  /* RX Message Buffer Data Field 2 Registers */
#define R_CANFD_CFDRMDF2_2_OFFSET     0x000009cc  /* RX Message Buffer Data Field 2 Registers */
#define R_CANFD_CFDRMDF3_2_OFFSET     0x00000a18  /* RX Message Buffer Data Field 2 Registers */
#define R_CANFD_CFDRMDF4_2_OFFSET     0x00000a64  /* RX Message Buffer Data Field 2 Registers */
#define R_CANFD_CFDRMDF5_2_OFFSET     0x00000ab0  /* RX Message Buffer Data Field 2 Registers */
#define R_CANFD_CFDRMDF6_2_OFFSET     0x00000afc  /* RX Message Buffer Data Field 2 Registers */
#define R_CANFD_CFDRMDF7_2_OFFSET     0x00000b48  /* RX Message Buffer Data Field 2 Registers */
/* CFDRMDF%s_3 Registers (0-7) */
#define R_CANFD_CFDRMDF0_3_OFFSET     0x00000938  /* RX Message Buffer Data Field 3 Registers */
#define R_CANFD_CFDRMDF1_3_OFFSET     0x00000984  /* RX Message Buffer Data Field 3 Registers */
#define R_CANFD_CFDRMDF2_3_OFFSET     0x000009d0  /* RX Message Buffer Data Field 3 Registers */
#define R_CANFD_CFDRMDF3_3_OFFSET     0x00000a1c  /* RX Message Buffer Data Field 3 Registers */
#define R_CANFD_CFDRMDF4_3_OFFSET     0x00000a68  /* RX Message Buffer Data Field 3 Registers */
#define R_CANFD_CFDRMDF5_3_OFFSET     0x00000ab4  /* RX Message Buffer Data Field 3 Registers */
#define R_CANFD_CFDRMDF6_3_OFFSET     0x00000b00  /* RX Message Buffer Data Field 3 Registers */
#define R_CANFD_CFDRMDF7_3_OFFSET     0x00000b4c  /* RX Message Buffer Data Field 3 Registers */
/* CFDRMDF%s_4 Registers (0-7) */
#define R_CANFD_CFDRMDF0_4_OFFSET     0x0000093c  /* RX Message Buffer Data Field 4 Registers */
#define R_CANFD_CFDRMDF1_4_OFFSET     0x00000988  /* RX Message Buffer Data Field 4 Registers */
#define R_CANFD_CFDRMDF2_4_OFFSET     0x000009d4  /* RX Message Buffer Data Field 4 Registers */
#define R_CANFD_CFDRMDF3_4_OFFSET     0x00000a20  /* RX Message Buffer Data Field 4 Registers */
#define R_CANFD_CFDRMDF4_4_OFFSET     0x00000a6c  /* RX Message Buffer Data Field 4 Registers */
#define R_CANFD_CFDRMDF5_4_OFFSET     0x00000ab8  /* RX Message Buffer Data Field 4 Registers */
#define R_CANFD_CFDRMDF6_4_OFFSET     0x00000b04  /* RX Message Buffer Data Field 4 Registers */
#define R_CANFD_CFDRMDF7_4_OFFSET     0x00000b50  /* RX Message Buffer Data Field 4 Registers */
/* CFDRMDF%s_5 Registers (0-7) */
#define R_CANFD_CFDRMDF0_5_OFFSET     0x00000940  /* RX Message Buffer Data Field 5 Registers */
#define R_CANFD_CFDRMDF1_5_OFFSET     0x0000098c  /* RX Message Buffer Data Field 5 Registers */
#define R_CANFD_CFDRMDF2_5_OFFSET     0x000009d8  /* RX Message Buffer Data Field 5 Registers */
#define R_CANFD_CFDRMDF3_5_OFFSET     0x00000a24  /* RX Message Buffer Data Field 5 Registers */
#define R_CANFD_CFDRMDF4_5_OFFSET     0x00000a70  /* RX Message Buffer Data Field 5 Registers */
#define R_CANFD_CFDRMDF5_5_OFFSET     0x00000abc  /* RX Message Buffer Data Field 5 Registers */
#define R_CANFD_CFDRMDF6_5_OFFSET     0x00000b08  /* RX Message Buffer Data Field 5 Registers */
#define R_CANFD_CFDRMDF7_5_OFFSET     0x00000b54  /* RX Message Buffer Data Field 5 Registers */
/* CFDRMDF%s_6 Registers (0-7) */
#define R_CANFD_CFDRMDF0_6_OFFSET     0x00000944  /* RX Message Buffer Data Field 6 Registers */
#define R_CANFD_CFDRMDF1_6_OFFSET     0x00000990  /* RX Message Buffer Data Field 6 Registers */
#define R_CANFD_CFDRMDF2_6_OFFSET     0x000009dc  /* RX Message Buffer Data Field 6 Registers */
#define R_CANFD_CFDRMDF3_6_OFFSET     0x00000a28  /* RX Message Buffer Data Field 6 Registers */
#define R_CANFD_CFDRMDF4_6_OFFSET     0x00000a74  /* RX Message Buffer Data Field 6 Registers */
#define R_CANFD_CFDRMDF5_6_OFFSET     0x00000ac0  /* RX Message Buffer Data Field 6 Registers */
#define R_CANFD_CFDRMDF6_6_OFFSET     0x00000b0c  /* RX Message Buffer Data Field 6 Registers */
#define R_CANFD_CFDRMDF7_6_OFFSET     0x00000b58  /* RX Message Buffer Data Field 6 Registers */
/* CFDRMDF%s_7 Registers (0-7) */
#define R_CANFD_CFDRMDF0_7_OFFSET     0x00000948  /* RX Message Buffer Data Field 7 Registers */
#define R_CANFD_CFDRMDF1_7_OFFSET     0x00000994  /* RX Message Buffer Data Field 7 Registers */
#define R_CANFD_CFDRMDF2_7_OFFSET     0x000009e0  /* RX Message Buffer Data Field 7 Registers */
#define R_CANFD_CFDRMDF3_7_OFFSET     0x00000a2c  /* RX Message Buffer Data Field 7 Registers */
#define R_CANFD_CFDRMDF4_7_OFFSET     0x00000a78  /* RX Message Buffer Data Field 7 Registers */
#define R_CANFD_CFDRMDF5_7_OFFSET     0x00000ac4  /* RX Message Buffer Data Field 7 Registers */
#define R_CANFD_CFDRMDF6_7_OFFSET     0x00000b10  /* RX Message Buffer Data Field 7 Registers */
#define R_CANFD_CFDRMDF7_7_OFFSET     0x00000b5c  /* RX Message Buffer Data Field 7 Registers */
/* CFDRMDF%s_8 Registers (0-7) */
#define R_CANFD_CFDRMDF0_8_OFFSET     0x0000094c  /* RX Message Buffer Data Field 8 Registers */
#define R_CANFD_CFDRMDF1_8_OFFSET     0x00000998  /* RX Message Buffer Data Field 8 Registers */
#define R_CANFD_CFDRMDF2_8_OFFSET     0x000009e4  /* RX Message Buffer Data Field 8 Registers */
#define R_CANFD_CFDRMDF3_8_OFFSET     0x00000a30  /* RX Message Buffer Data Field 8 Registers */
#define R_CANFD_CFDRMDF4_8_OFFSET     0x00000a7c  /* RX Message Buffer Data Field 8 Registers */
#define R_CANFD_CFDRMDF5_8_OFFSET     0x00000ac8  /* RX Message Buffer Data Field 8 Registers */
#define R_CANFD_CFDRMDF6_8_OFFSET     0x00000b14  /* RX Message Buffer Data Field 8 Registers */
#define R_CANFD_CFDRMDF7_8_OFFSET     0x00000b60  /* RX Message Buffer Data Field 8 Registers */
/* CFDRMDF%s_9 Registers (0-7) */
#define R_CANFD_CFDRMDF0_9_OFFSET     0x00000950  /* RX Message Buffer Data Field 9 Registers */
#define R_CANFD_CFDRMDF1_9_OFFSET     0x0000099c  /* RX Message Buffer Data Field 9 Registers */
#define R_CANFD_CFDRMDF2_9_OFFSET     0x000009e8  /* RX Message Buffer Data Field 9 Registers */
#define R_CANFD_CFDRMDF3_9_OFFSET     0x00000a34  /* RX Message Buffer Data Field 9 Registers */
#define R_CANFD_CFDRMDF4_9_OFFSET     0x00000a80  /* RX Message Buffer Data Field 9 Registers */
#define R_CANFD_CFDRMDF5_9_OFFSET     0x00000acc  /* RX Message Buffer Data Field 9 Registers */
#define R_CANFD_CFDRMDF6_9_OFFSET     0x00000b18  /* RX Message Buffer Data Field 9 Registers */
#define R_CANFD_CFDRMDF7_9_OFFSET     0x00000b64  /* RX Message Buffer Data Field 9 Registers */
/* CFDRMDF%s_10 Registers (0-7) */
#define R_CANFD_CFDRMDF0_10_OFFSET     0x00000954  /* RX Message Buffer Data Field 10 Registers */
#define R_CANFD_CFDRMDF1_10_OFFSET     0x000009a0  /* RX Message Buffer Data Field 10 Registers */
#define R_CANFD_CFDRMDF2_10_OFFSET     0x000009ec  /* RX Message Buffer Data Field 10 Registers */
#define R_CANFD_CFDRMDF3_10_OFFSET     0x00000a38  /* RX Message Buffer Data Field 10 Registers */
#define R_CANFD_CFDRMDF4_10_OFFSET     0x00000a84  /* RX Message Buffer Data Field 10 Registers */
#define R_CANFD_CFDRMDF5_10_OFFSET     0x00000ad0  /* RX Message Buffer Data Field 10 Registers */
#define R_CANFD_CFDRMDF6_10_OFFSET     0x00000b1c  /* RX Message Buffer Data Field 10 Registers */
#define R_CANFD_CFDRMDF7_10_OFFSET     0x00000b68  /* RX Message Buffer Data Field 10 Registers */
/* CFDRMDF%s_11 Registers (0-7) */
#define R_CANFD_CFDRMDF0_11_OFFSET     0x00000958  /* RX Message Buffer Data Field 11 Registers */
#define R_CANFD_CFDRMDF1_11_OFFSET     0x000009a4  /* RX Message Buffer Data Field 11 Registers */
#define R_CANFD_CFDRMDF2_11_OFFSET     0x000009f0  /* RX Message Buffer Data Field 11 Registers */
#define R_CANFD_CFDRMDF3_11_OFFSET     0x00000a3c  /* RX Message Buffer Data Field 11 Registers */
#define R_CANFD_CFDRMDF4_11_OFFSET     0x00000a88  /* RX Message Buffer Data Field 11 Registers */
#define R_CANFD_CFDRMDF5_11_OFFSET     0x00000ad4  /* RX Message Buffer Data Field 11 Registers */
#define R_CANFD_CFDRMDF6_11_OFFSET     0x00000b20  /* RX Message Buffer Data Field 11 Registers */
#define R_CANFD_CFDRMDF7_11_OFFSET     0x00000b6c  /* RX Message Buffer Data Field 11 Registers */
/* CFDRMDF%s_12 Registers (0-7) */
#define R_CANFD_CFDRMDF0_12_OFFSET     0x0000095c  /* RX Message Buffer Data Field 12 Registers */
#define R_CANFD_CFDRMDF1_12_OFFSET     0x000009a8  /* RX Message Buffer Data Field 12 Registers */
#define R_CANFD_CFDRMDF2_12_OFFSET     0x000009f4  /* RX Message Buffer Data Field 12 Registers */
#define R_CANFD_CFDRMDF3_12_OFFSET     0x00000a40  /* RX Message Buffer Data Field 12 Registers */
#define R_CANFD_CFDRMDF4_12_OFFSET     0x00000a8c  /* RX Message Buffer Data Field 12 Registers */
#define R_CANFD_CFDRMDF5_12_OFFSET     0x00000ad8  /* RX Message Buffer Data Field 12 Registers */
#define R_CANFD_CFDRMDF6_12_OFFSET     0x00000b24  /* RX Message Buffer Data Field 12 Registers */
#define R_CANFD_CFDRMDF7_12_OFFSET     0x00000b70  /* RX Message Buffer Data Field 12 Registers */
/* CFDRMDF%s_13 Registers (0-7) */
#define R_CANFD_CFDRMDF0_13_OFFSET     0x00000960  /* RX Message Buffer Data Field 13 Registers */
#define R_CANFD_CFDRMDF1_13_OFFSET     0x000009ac  /* RX Message Buffer Data Field 13 Registers */
#define R_CANFD_CFDRMDF2_13_OFFSET     0x000009f8  /* RX Message Buffer Data Field 13 Registers */
#define R_CANFD_CFDRMDF3_13_OFFSET     0x00000a44  /* RX Message Buffer Data Field 13 Registers */
#define R_CANFD_CFDRMDF4_13_OFFSET     0x00000a90  /* RX Message Buffer Data Field 13 Registers */
#define R_CANFD_CFDRMDF5_13_OFFSET     0x00000adc  /* RX Message Buffer Data Field 13 Registers */
#define R_CANFD_CFDRMDF6_13_OFFSET     0x00000b28  /* RX Message Buffer Data Field 13 Registers */
#define R_CANFD_CFDRMDF7_13_OFFSET     0x00000b74  /* RX Message Buffer Data Field 13 Registers */
/* CFDRMDF%s_14 Registers (0-7) */
#define R_CANFD_CFDRMDF0_14_OFFSET     0x00000964  /* RX Message Buffer Data Field 14 Registers */
#define R_CANFD_CFDRMDF1_14_OFFSET     0x000009b0  /* RX Message Buffer Data Field 14 Registers */
#define R_CANFD_CFDRMDF2_14_OFFSET     0x000009fc  /* RX Message Buffer Data Field 14 Registers */
#define R_CANFD_CFDRMDF3_14_OFFSET     0x00000a48  /* RX Message Buffer Data Field 14 Registers */
#define R_CANFD_CFDRMDF4_14_OFFSET     0x00000a94  /* RX Message Buffer Data Field 14 Registers */
#define R_CANFD_CFDRMDF5_14_OFFSET     0x00000ae0  /* RX Message Buffer Data Field 14 Registers */
#define R_CANFD_CFDRMDF6_14_OFFSET     0x00000b2c  /* RX Message Buffer Data Field 14 Registers */
#define R_CANFD_CFDRMDF7_14_OFFSET     0x00000b78  /* RX Message Buffer Data Field 14 Registers */
/* CFDRMDF%s_15 Registers (0-7) */
#define R_CANFD_CFDRMDF0_15_OFFSET     0x00000968  /* RX Message Buffer Data Field 15 Registers */
#define R_CANFD_CFDRMDF1_15_OFFSET     0x000009b4  /* RX Message Buffer Data Field 15 Registers */
#define R_CANFD_CFDRMDF2_15_OFFSET     0x00000a00  /* RX Message Buffer Data Field 15 Registers */
#define R_CANFD_CFDRMDF3_15_OFFSET     0x00000a4c  /* RX Message Buffer Data Field 15 Registers */
#define R_CANFD_CFDRMDF4_15_OFFSET     0x00000a98  /* RX Message Buffer Data Field 15 Registers */
#define R_CANFD_CFDRMDF5_15_OFFSET     0x00000ae4  /* RX Message Buffer Data Field 15 Registers */
#define R_CANFD_CFDRMDF6_15_OFFSET     0x00000b30  /* RX Message Buffer Data Field 15 Registers */
#define R_CANFD_CFDRMDF7_15_OFFSET     0x00000b7c  /* RX Message Buffer Data Field 15 Registers */
/* CFDRMID%s Registers (8-15) */
#define R_CANFD_CFDRMID08_OFFSET     0x00000d20  /* RX Message Buffer ID Registers */
#define R_CANFD_CFDRMID09_OFFSET     0x00000d6c  /* RX Message Buffer ID Registers */
#define R_CANFD_CFDRMID10_OFFSET     0x00000db8  /* RX Message Buffer ID Registers */
#define R_CANFD_CFDRMID11_OFFSET     0x00000e04  /* RX Message Buffer ID Registers */
#define R_CANFD_CFDRMID12_OFFSET     0x00000e50  /* RX Message Buffer ID Registers */
#define R_CANFD_CFDRMID13_OFFSET     0x00000e9c  /* RX Message Buffer ID Registers */
#define R_CANFD_CFDRMID14_OFFSET     0x00000ee8  /* RX Message Buffer ID Registers */
#define R_CANFD_CFDRMID15_OFFSET     0x00000f34  /* RX Message Buffer ID Registers */
/* CFDRMPTR%s Registers (8-15) */
#define R_CANFD_CFDRMPTR08_OFFSET     0x00000d24  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR09_OFFSET     0x00000d70  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR10_OFFSET     0x00000dbc  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR11_OFFSET     0x00000e08  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR12_OFFSET     0x00000e54  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR13_OFFSET     0x00000ea0  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR14_OFFSET     0x00000eec  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR15_OFFSET     0x00000f38  /* RX Message Buffer Pointer Registers */
/* CFDRMFDSTS%s Registers (8-15) */
#define R_CANFD_CFDRMFDSTS08_OFFSET     0x00000d28  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS09_OFFSET     0x00000d74  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS10_OFFSET     0x00000dc0  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS11_OFFSET     0x00000e0c  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS12_OFFSET     0x00000e58  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS13_OFFSET     0x00000ea4  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS14_OFFSET     0x00000ef0  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS15_OFFSET     0x00000f3c  /* RX Message Buffer CANFD Status Registers */
/* CFDRMDF%s_0 Registers (8-15) */
#define R_CANFD_CFDRMDF08_0_OFFSET     0x00000d2c  /* RX Message Buffer Data Field 0 Registers */
#define R_CANFD_CFDRMDF09_0_OFFSET     0x00000d78  /* RX Message Buffer Data Field 0 Registers */
#define R_CANFD_CFDRMDF10_0_OFFSET     0x00000dc4  /* RX Message Buffer Data Field 0 Registers */
#define R_CANFD_CFDRMDF11_0_OFFSET     0x00000e10  /* RX Message Buffer Data Field 0 Registers */
#define R_CANFD_CFDRMDF12_0_OFFSET     0x00000e5c  /* RX Message Buffer Data Field 0 Registers */
#define R_CANFD_CFDRMDF13_0_OFFSET     0x00000ea8  /* RX Message Buffer Data Field 0 Registers */
#define R_CANFD_CFDRMDF14_0_OFFSET     0x00000ef4  /* RX Message Buffer Data Field 0 Registers */
#define R_CANFD_CFDRMDF15_0_OFFSET     0x00000f40  /* RX Message Buffer Data Field 0 Registers */
/* CFDRMDF%s_1 Registers (8-15) */
#define R_CANFD_CFDRMDF08_1_OFFSET     0x00000d30  /* RX Message Buffer Data Field 1 Registers */
#define R_CANFD_CFDRMDF09_1_OFFSET     0x00000d7c  /* RX Message Buffer Data Field 1 Registers */
#define R_CANFD_CFDRMDF10_1_OFFSET     0x00000dc8  /* RX Message Buffer Data Field 1 Registers */
#define R_CANFD_CFDRMDF11_1_OFFSET     0x00000e14  /* RX Message Buffer Data Field 1 Registers */
#define R_CANFD_CFDRMDF12_1_OFFSET     0x00000e60  /* RX Message Buffer Data Field 1 Registers */
#define R_CANFD_CFDRMDF13_1_OFFSET     0x00000eac  /* RX Message Buffer Data Field 1 Registers */
#define R_CANFD_CFDRMDF14_1_OFFSET     0x00000ef8  /* RX Message Buffer Data Field 1 Registers */
#define R_CANFD_CFDRMDF15_1_OFFSET     0x00000f44  /* RX Message Buffer Data Field 1 Registers */
/* CFDRMDF%s_2 Registers (8-15) */
#define R_CANFD_CFDRMDF08_2_OFFSET     0x00000d34  /* RX Message Buffer Data Field 2 Registers */
#define R_CANFD_CFDRMDF09_2_OFFSET     0x00000d80  /* RX Message Buffer Data Field 2 Registers */
#define R_CANFD_CFDRMDF10_2_OFFSET     0x00000dcc  /* RX Message Buffer Data Field 2 Registers */
#define R_CANFD_CFDRMDF11_2_OFFSET     0x00000e18  /* RX Message Buffer Data Field 2 Registers */
#define R_CANFD_CFDRMDF12_2_OFFSET     0x00000e64  /* RX Message Buffer Data Field 2 Registers */
#define R_CANFD_CFDRMDF13_2_OFFSET     0x00000eb0  /* RX Message Buffer Data Field 2 Registers */
#define R_CANFD_CFDRMDF14_2_OFFSET     0x00000efc  /* RX Message Buffer Data Field 2 Registers */
#define R_CANFD_CFDRMDF15_2_OFFSET     0x00000f48  /* RX Message Buffer Data Field 2 Registers */
/* CFDRMDF%s_3 Registers (8-15) */
#define R_CANFD_CFDRMDF08_3_OFFSET     0x00000d38  /* RX Message Buffer Data Field 3 Registers */
#define R_CANFD_CFDRMDF09_3_OFFSET     0x00000d84  /* RX Message Buffer Data Field 3 Registers */
#define R_CANFD_CFDRMDF10_3_OFFSET     0x00000dd0  /* RX Message Buffer Data Field 3 Registers */
#define R_CANFD_CFDRMDF11_3_OFFSET     0x00000e1c  /* RX Message Buffer Data Field 3 Registers */
#define R_CANFD_CFDRMDF12_3_OFFSET     0x00000e68  /* RX Message Buffer Data Field 3 Registers */
#define R_CANFD_CFDRMDF13_3_OFFSET     0x00000eb4  /* RX Message Buffer Data Field 3 Registers */
#define R_CANFD_CFDRMDF14_3_OFFSET     0x00000f00  /* RX Message Buffer Data Field 3 Registers */
#define R_CANFD_CFDRMDF15_3_OFFSET     0x00000f4c  /* RX Message Buffer Data Field 3 Registers */
/* CFDRMDF%s_4 Registers (8-15) */
#define R_CANFD_CFDRMDF08_4_OFFSET     0x00000d3c  /* RX Message Buffer Data Field 4 Registers */
#define R_CANFD_CFDRMDF09_4_OFFSET     0x00000d88  /* RX Message Buffer Data Field 4 Registers */
#define R_CANFD_CFDRMDF10_4_OFFSET     0x00000dd4  /* RX Message Buffer Data Field 4 Registers */
#define R_CANFD_CFDRMDF11_4_OFFSET     0x00000e20  /* RX Message Buffer Data Field 4 Registers */
#define R_CANFD_CFDRMDF12_4_OFFSET     0x00000e6c  /* RX Message Buffer Data Field 4 Registers */
#define R_CANFD_CFDRMDF13_4_OFFSET     0x00000eb8  /* RX Message Buffer Data Field 4 Registers */
#define R_CANFD_CFDRMDF14_4_OFFSET     0x00000f04  /* RX Message Buffer Data Field 4 Registers */
#define R_CANFD_CFDRMDF15_4_OFFSET     0x00000f50  /* RX Message Buffer Data Field 4 Registers */
/* CFDRMDF%s_5 Registers (8-15) */
#define R_CANFD_CFDRMDF08_5_OFFSET     0x00000d40  /* RX Message Buffer Data Field 5 Registers */
#define R_CANFD_CFDRMDF09_5_OFFSET     0x00000d8c  /* RX Message Buffer Data Field 5 Registers */
#define R_CANFD_CFDRMDF10_5_OFFSET     0x00000dd8  /* RX Message Buffer Data Field 5 Registers */
#define R_CANFD_CFDRMDF11_5_OFFSET     0x00000e24  /* RX Message Buffer Data Field 5 Registers */
#define R_CANFD_CFDRMDF12_5_OFFSET     0x00000e70  /* RX Message Buffer Data Field 5 Registers */
#define R_CANFD_CFDRMDF13_5_OFFSET     0x00000ebc  /* RX Message Buffer Data Field 5 Registers */
#define R_CANFD_CFDRMDF14_5_OFFSET     0x00000f08  /* RX Message Buffer Data Field 5 Registers */
#define R_CANFD_CFDRMDF15_5_OFFSET     0x00000f54  /* RX Message Buffer Data Field 5 Registers */
/* CFDRMDF%s_6 Registers (8-15) */
#define R_CANFD_CFDRMDF08_6_OFFSET     0x00000d44  /* RX Message Buffer Data Field 6 Registers */
#define R_CANFD_CFDRMDF09_6_OFFSET     0x00000d90  /* RX Message Buffer Data Field 6 Registers */
#define R_CANFD_CFDRMDF10_6_OFFSET     0x00000ddc  /* RX Message Buffer Data Field 6 Registers */
#define R_CANFD_CFDRMDF11_6_OFFSET     0x00000e28  /* RX Message Buffer Data Field 6 Registers */
#define R_CANFD_CFDRMDF12_6_OFFSET     0x00000e74  /* RX Message Buffer Data Field 6 Registers */
#define R_CANFD_CFDRMDF13_6_OFFSET     0x00000ec0  /* RX Message Buffer Data Field 6 Registers */
#define R_CANFD_CFDRMDF14_6_OFFSET     0x00000f0c  /* RX Message Buffer Data Field 6 Registers */
#define R_CANFD_CFDRMDF15_6_OFFSET     0x00000f58  /* RX Message Buffer Data Field 6 Registers */
/* CFDRMDF%s_7 Registers (8-15) */
#define R_CANFD_CFDRMDF08_7_OFFSET     0x00000d48  /* RX Message Buffer Data Field 7 Registers */
#define R_CANFD_CFDRMDF09_7_OFFSET     0x00000d94  /* RX Message Buffer Data Field 7 Registers */
#define R_CANFD_CFDRMDF10_7_OFFSET     0x00000de0  /* RX Message Buffer Data Field 7 Registers */
#define R_CANFD_CFDRMDF11_7_OFFSET     0x00000e2c  /* RX Message Buffer Data Field 7 Registers */
#define R_CANFD_CFDRMDF12_7_OFFSET     0x00000e78  /* RX Message Buffer Data Field 7 Registers */
#define R_CANFD_CFDRMDF13_7_OFFSET     0x00000ec4  /* RX Message Buffer Data Field 7 Registers */
#define R_CANFD_CFDRMDF14_7_OFFSET     0x00000f10  /* RX Message Buffer Data Field 7 Registers */
#define R_CANFD_CFDRMDF15_7_OFFSET     0x00000f5c  /* RX Message Buffer Data Field 7 Registers */
/* CFDRMDF%s_8 Registers (8-15) */
#define R_CANFD_CFDRMDF08_8_OFFSET     0x00000d4c  /* RX Message Buffer Data Field 8 Registers */
#define R_CANFD_CFDRMDF09_8_OFFSET     0x00000d98  /* RX Message Buffer Data Field 8 Registers */
#define R_CANFD_CFDRMDF10_8_OFFSET     0x00000de4  /* RX Message Buffer Data Field 8 Registers */
#define R_CANFD_CFDRMDF11_8_OFFSET     0x00000e30  /* RX Message Buffer Data Field 8 Registers */
#define R_CANFD_CFDRMDF12_8_OFFSET     0x00000e7c  /* RX Message Buffer Data Field 8 Registers */
#define R_CANFD_CFDRMDF13_8_OFFSET     0x00000ec8  /* RX Message Buffer Data Field 8 Registers */
#define R_CANFD_CFDRMDF14_8_OFFSET     0x00000f14  /* RX Message Buffer Data Field 8 Registers */
#define R_CANFD_CFDRMDF15_8_OFFSET     0x00000f60  /* RX Message Buffer Data Field 8 Registers */
/* CFDRMDF%s_9 Registers (8-15) */
#define R_CANFD_CFDRMDF08_9_OFFSET     0x00000d50  /* RX Message Buffer Data Field 9 Registers */
#define R_CANFD_CFDRMDF09_9_OFFSET     0x00000d9c  /* RX Message Buffer Data Field 9 Registers */
#define R_CANFD_CFDRMDF10_9_OFFSET     0x00000de8  /* RX Message Buffer Data Field 9 Registers */
#define R_CANFD_CFDRMDF11_9_OFFSET     0x00000e34  /* RX Message Buffer Data Field 9 Registers */
#define R_CANFD_CFDRMDF12_9_OFFSET     0x00000e80  /* RX Message Buffer Data Field 9 Registers */
#define R_CANFD_CFDRMDF13_9_OFFSET     0x00000ecc  /* RX Message Buffer Data Field 9 Registers */
#define R_CANFD_CFDRMDF14_9_OFFSET     0x00000f18  /* RX Message Buffer Data Field 9 Registers */
#define R_CANFD_CFDRMDF15_9_OFFSET     0x00000f64  /* RX Message Buffer Data Field 9 Registers */
/* CFDRMDF%s_10 Registers (8-15) */
#define R_CANFD_CFDRMDF08_10_OFFSET     0x00000d54  /* RX Message Buffer Data Field 10 Registers */
#define R_CANFD_CFDRMDF09_10_OFFSET     0x00000da0  /* RX Message Buffer Data Field 10 Registers */
#define R_CANFD_CFDRMDF10_10_OFFSET     0x00000dec  /* RX Message Buffer Data Field 10 Registers */
#define R_CANFD_CFDRMDF11_10_OFFSET     0x00000e38  /* RX Message Buffer Data Field 10 Registers */
#define R_CANFD_CFDRMDF12_10_OFFSET     0x00000e84  /* RX Message Buffer Data Field 10 Registers */
#define R_CANFD_CFDRMDF13_10_OFFSET     0x00000ed0  /* RX Message Buffer Data Field 10 Registers */
#define R_CANFD_CFDRMDF14_10_OFFSET     0x00000f1c  /* RX Message Buffer Data Field 10 Registers */
#define R_CANFD_CFDRMDF15_10_OFFSET     0x00000f68  /* RX Message Buffer Data Field 10 Registers */
/* CFDRMDF%s_11 Registers (8-15) */
#define R_CANFD_CFDRMDF08_11_OFFSET     0x00000d58  /* RX Message Buffer Data Field 11 Registers */
#define R_CANFD_CFDRMDF09_11_OFFSET     0x00000da4  /* RX Message Buffer Data Field 11 Registers */
#define R_CANFD_CFDRMDF10_11_OFFSET     0x00000df0  /* RX Message Buffer Data Field 11 Registers */
#define R_CANFD_CFDRMDF11_11_OFFSET     0x00000e3c  /* RX Message Buffer Data Field 11 Registers */
#define R_CANFD_CFDRMDF12_11_OFFSET     0x00000e88  /* RX Message Buffer Data Field 11 Registers */
#define R_CANFD_CFDRMDF13_11_OFFSET     0x00000ed4  /* RX Message Buffer Data Field 11 Registers */
#define R_CANFD_CFDRMDF14_11_OFFSET     0x00000f20  /* RX Message Buffer Data Field 11 Registers */
#define R_CANFD_CFDRMDF15_11_OFFSET     0x00000f6c  /* RX Message Buffer Data Field 11 Registers */
/* CFDRMDF%s_12 Registers (8-15) */
#define R_CANFD_CFDRMDF08_12_OFFSET     0x00000d5c  /* RX Message Buffer Data Field 12 Registers */
#define R_CANFD_CFDRMDF09_12_OFFSET     0x00000da8  /* RX Message Buffer Data Field 12 Registers */
#define R_CANFD_CFDRMDF10_12_OFFSET     0x00000df4  /* RX Message Buffer Data Field 12 Registers */
#define R_CANFD_CFDRMDF11_12_OFFSET     0x00000e40  /* RX Message Buffer Data Field 12 Registers */
#define R_CANFD_CFDRMDF12_12_OFFSET     0x00000e8c  /* RX Message Buffer Data Field 12 Registers */
#define R_CANFD_CFDRMDF13_12_OFFSET     0x00000ed8  /* RX Message Buffer Data Field 12 Registers */
#define R_CANFD_CFDRMDF14_12_OFFSET     0x00000f24  /* RX Message Buffer Data Field 12 Registers */
#define R_CANFD_CFDRMDF15_12_OFFSET     0x00000f70  /* RX Message Buffer Data Field 12 Registers */
/* CFDRMDF%s_13 Registers (8-15) */
#define R_CANFD_CFDRMDF08_13_OFFSET     0x00000d60  /* RX Message Buffer Data Field 13 Registers */
#define R_CANFD_CFDRMDF09_13_OFFSET     0x00000dac  /* RX Message Buffer Data Field 13 Registers */
#define R_CANFD_CFDRMDF10_13_OFFSET     0x00000df8  /* RX Message Buffer Data Field 13 Registers */
#define R_CANFD_CFDRMDF11_13_OFFSET     0x00000e44  /* RX Message Buffer Data Field 13 Registers */
#define R_CANFD_CFDRMDF12_13_OFFSET     0x00000e90  /* RX Message Buffer Data Field 13 Registers */
#define R_CANFD_CFDRMDF13_13_OFFSET     0x00000edc  /* RX Message Buffer Data Field 13 Registers */
#define R_CANFD_CFDRMDF14_13_OFFSET     0x00000f28  /* RX Message Buffer Data Field 13 Registers */
#define R_CANFD_CFDRMDF15_13_OFFSET     0x00000f74  /* RX Message Buffer Data Field 13 Registers */
/* CFDRMDF%s_14 Registers (8-15) */
#define R_CANFD_CFDRMDF08_14_OFFSET     0x00000d64  /* RX Message Buffer Data Field 14 Registers */
#define R_CANFD_CFDRMDF09_14_OFFSET     0x00000db0  /* RX Message Buffer Data Field 14 Registers */
#define R_CANFD_CFDRMDF10_14_OFFSET     0x00000dfc  /* RX Message Buffer Data Field 14 Registers */
#define R_CANFD_CFDRMDF11_14_OFFSET     0x00000e48  /* RX Message Buffer Data Field 14 Registers */
#define R_CANFD_CFDRMDF12_14_OFFSET     0x00000e94  /* RX Message Buffer Data Field 14 Registers */
#define R_CANFD_CFDRMDF13_14_OFFSET     0x00000ee0  /* RX Message Buffer Data Field 14 Registers */
#define R_CANFD_CFDRMDF14_14_OFFSET     0x00000f2c  /* RX Message Buffer Data Field 14 Registers */
#define R_CANFD_CFDRMDF15_14_OFFSET     0x00000f78  /* RX Message Buffer Data Field 14 Registers */
/* CFDRMDF%s_15 Registers (8-15) */
#define R_CANFD_CFDRMDF08_15_OFFSET     0x00000d68  /* RX Message Buffer Data Field 15 Registers */
#define R_CANFD_CFDRMDF09_15_OFFSET     0x00000db4  /* RX Message Buffer Data Field 15 Registers */
#define R_CANFD_CFDRMDF10_15_OFFSET     0x00000e00  /* RX Message Buffer Data Field 15 Registers */
#define R_CANFD_CFDRMDF11_15_OFFSET     0x00000e4c  /* RX Message Buffer Data Field 15 Registers */
#define R_CANFD_CFDRMDF12_15_OFFSET     0x00000e98  /* RX Message Buffer Data Field 15 Registers */
#define R_CANFD_CFDRMDF13_15_OFFSET     0x00000ee4  /* RX Message Buffer Data Field 15 Registers */
#define R_CANFD_CFDRMDF14_15_OFFSET     0x00000f30  /* RX Message Buffer Data Field 15 Registers */
#define R_CANFD_CFDRMDF15_15_OFFSET     0x00000f7c  /* RX Message Buffer Data Field 15 Registers */
/* CFDRMPTR%s Registers (16-23) */
#define R_CANFD_CFDRMPTR16_OFFSET     0x00001124  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR17_OFFSET     0x00001170  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR18_OFFSET     0x000011bc  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR19_OFFSET     0x00001208  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR20_OFFSET     0x00001254  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR21_OFFSET     0x000012a0  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR22_OFFSET     0x000012ec  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR23_OFFSET     0x00001338  /* RX Message Buffer Pointer Registers */
/* CFDRMFDSTS%s Registers (16-23) */
#define R_CANFD_CFDRMFDSTS16_OFFSET     0x00001128  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS17_OFFSET     0x00001174  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS18_OFFSET     0x000011c0  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS19_OFFSET     0x0000120c  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS20_OFFSET     0x00001258  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS21_OFFSET     0x000012a4  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS22_OFFSET     0x000012f0  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS23_OFFSET     0x0000133c  /* RX Message Buffer CANFD Status Registers */
/* CFDRMPTR%s Registers (24-31) */
#define R_CANFD_CFDRMPTR24_OFFSET     0x00001524  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR25_OFFSET     0x00001570  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR26_OFFSET     0x000015bc  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR27_OFFSET     0x00001608  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR28_OFFSET     0x00001654  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR29_OFFSET     0x000016a0  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR30_OFFSET     0x000016ec  /* RX Message Buffer Pointer Registers */
#define R_CANFD_CFDRMPTR31_OFFSET     0x00001738  /* RX Message Buffer Pointer Registers */
/* CFDRMFDSTS%s Registers (24-31) */
#define R_CANFD_CFDRMFDSTS24_OFFSET     0x00001528  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS25_OFFSET     0x00001574  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS26_OFFSET     0x000015c0  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS27_OFFSET     0x0000160c  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS28_OFFSET     0x00001658  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS29_OFFSET     0x000016a4  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS30_OFFSET     0x000016f0  /* RX Message Buffer CANFD Status Registers */
#define R_CANFD_CFDRMFDSTS31_OFFSET     0x0000173c  /* RX Message Buffer CANFD Status Registers */

/* CANFD Register Addresses */

#define R_CANFD_CFDC0NCFG                 (R_CANFD_BASE + R_CANFD_CFDC0NCFG_OFFSET)
#define R_CANFD_CFDC0CTR                 (R_CANFD_BASE + R_CANFD_CFDC0CTR_OFFSET)
#define R_CANFD_CFDC0STS                 (R_CANFD_BASE + R_CANFD_CFDC0STS_OFFSET)
#define R_CANFD_CFDC0ERFL                 (R_CANFD_BASE + R_CANFD_CFDC0ERFL_OFFSET)
#define R_CANFD_CFDGCFG                 (R_CANFD_BASE + R_CANFD_CFDGCFG_OFFSET)
#define R_CANFD_CFDGCTR                 (R_CANFD_BASE + R_CANFD_CFDGCTR_OFFSET)
#define R_CANFD_CFDGSTS                 (R_CANFD_BASE + R_CANFD_CFDGSTS_OFFSET)
#define R_CANFD_CFDGERFL                 (R_CANFD_BASE + R_CANFD_CFDGERFL_OFFSET)
#define R_CANFD_CFDGTSC                 (R_CANFD_BASE + R_CANFD_CFDGTSC_OFFSET)
#define R_CANFD_CFDGAFLECTR                 (R_CANFD_BASE + R_CANFD_CFDGAFLECTR_OFFSET)
#define R_CANFD_CFDGAFLCFG                 (R_CANFD_BASE + R_CANFD_CFDGAFLCFG_OFFSET)
#define R_CANFD_CFDRMNB                 (R_CANFD_BASE + R_CANFD_CFDRMNB_OFFSET)
#define R_CANFD_CFDRMND                 (R_CANFD_BASE + R_CANFD_CFDRMND_OFFSET)
#define R_CANFD_CFDRMIEC                 (R_CANFD_BASE + R_CANFD_CFDRMIEC_OFFSET)
#define R_CANFD_CFDRFCC0                 (R_CANFD_BASE + R_CANFD_CFDRFCC0_OFFSET)
#define R_CANFD_CFDRFCC1                 (R_CANFD_BASE + R_CANFD_CFDRFCC1_OFFSET)
#define R_CANFD_CFDRFSTS0                 (R_CANFD_BASE + R_CANFD_CFDRFSTS0_OFFSET)
#define R_CANFD_CFDRFSTS1                 (R_CANFD_BASE + R_CANFD_CFDRFSTS1_OFFSET)
#define R_CANFD_CFDRFPCTR0                 (R_CANFD_BASE + R_CANFD_CFDRFPCTR0_OFFSET)
#define R_CANFD_CFDRFPCTR1                 (R_CANFD_BASE + R_CANFD_CFDRFPCTR1_OFFSET)
#define R_CANFD_CFDCFCC                 (R_CANFD_BASE + R_CANFD_CFDCFCC_OFFSET)
#define R_CANFD_CFDCFSTS                 (R_CANFD_BASE + R_CANFD_CFDCFSTS_OFFSET)
#define R_CANFD_CFDCFPCTR                 (R_CANFD_BASE + R_CANFD_CFDCFPCTR_OFFSET)
#define R_CANFD_CFDFESTS                 (R_CANFD_BASE + R_CANFD_CFDFESTS_OFFSET)
#define R_CANFD_CFDFFSTS                 (R_CANFD_BASE + R_CANFD_CFDFFSTS_OFFSET)
#define R_CANFD_CFDFMSTS                 (R_CANFD_BASE + R_CANFD_CFDFMSTS_OFFSET)
#define R_CANFD_CFDRFISTS                 (R_CANFD_BASE + R_CANFD_CFDRFISTS_OFFSET)
#define R_CANFD_CFDTMC0                 (R_CANFD_BASE + R_CANFD_CFDTMC0_OFFSET)
#define R_CANFD_CFDTMC1                 (R_CANFD_BASE + R_CANFD_CFDTMC1_OFFSET)
#define R_CANFD_CFDTMC2                 (R_CANFD_BASE + R_CANFD_CFDTMC2_OFFSET)
#define R_CANFD_CFDTMC3                 (R_CANFD_BASE + R_CANFD_CFDTMC3_OFFSET)
#define R_CANFD_CFDTMSTS0                 (R_CANFD_BASE + R_CANFD_CFDTMSTS0_OFFSET)
#define R_CANFD_CFDTMSTS1                 (R_CANFD_BASE + R_CANFD_CFDTMSTS1_OFFSET)
#define R_CANFD_CFDTMSTS2                 (R_CANFD_BASE + R_CANFD_CFDTMSTS2_OFFSET)
#define R_CANFD_CFDTMSTS3                 (R_CANFD_BASE + R_CANFD_CFDTMSTS3_OFFSET)
#define R_CANFD_CFDTMTRSTS                 (R_CANFD_BASE + R_CANFD_CFDTMTRSTS_OFFSET)
#define R_CANFD_CFDTMTARSTS                 (R_CANFD_BASE + R_CANFD_CFDTMTARSTS_OFFSET)
#define R_CANFD_CFDTMTCSTS                 (R_CANFD_BASE + R_CANFD_CFDTMTCSTS_OFFSET)
#define R_CANFD_CFDTMTASTS                 (R_CANFD_BASE + R_CANFD_CFDTMTASTS_OFFSET)
#define R_CANFD_CFDTMIEC                 (R_CANFD_BASE + R_CANFD_CFDTMIEC_OFFSET)
#define R_CANFD_CFDTXQCC                 (R_CANFD_BASE + R_CANFD_CFDTXQCC_OFFSET)
#define R_CANFD_CFDTXQSTS                 (R_CANFD_BASE + R_CANFD_CFDTXQSTS_OFFSET)
#define R_CANFD_CFDTXQPCTR                 (R_CANFD_BASE + R_CANFD_CFDTXQPCTR_OFFSET)
#define R_CANFD_CFDTHLCC                 (R_CANFD_BASE + R_CANFD_CFDTHLCC_OFFSET)
#define R_CANFD_CFDTHLSTS                 (R_CANFD_BASE + R_CANFD_CFDTHLSTS_OFFSET)
#define R_CANFD_CFDTHLPCTR                 (R_CANFD_BASE + R_CANFD_CFDTHLPCTR_OFFSET)
#define R_CANFD_CFDGTINTSTS                 (R_CANFD_BASE + R_CANFD_CFDGTINTSTS_OFFSET)
#define R_CANFD_CFDGTSTCFG                 (R_CANFD_BASE + R_CANFD_CFDGTSTCFG_OFFSET)
#define R_CANFD_CFDGTSTCTR                 (R_CANFD_BASE + R_CANFD_CFDGTSTCTR_OFFSET)
#define R_CANFD_CFDGFDCFG                 (R_CANFD_BASE + R_CANFD_CFDGFDCFG_OFFSET)
#define R_CANFD_CFDGLOCKK                 (R_CANFD_BASE + R_CANFD_CFDGLOCKK_OFFSET)
#define R_CANFD_CFDGAFLIGNENT                 (R_CANFD_BASE + R_CANFD_CFDGAFLIGNENT_OFFSET)
#define R_CANFD_CFDGAFLIGNCTR                 (R_CANFD_BASE + R_CANFD_CFDGAFLIGNCTR_OFFSET)
#define R_CANFD_CFDCDTCT                 (R_CANFD_BASE + R_CANFD_CFDCDTCT_OFFSET)
#define R_CANFD_CFDCDTSTS                 (R_CANFD_BASE + R_CANFD_CFDCDTSTS_OFFSET)
#define R_CANFD_CFDGRSTC                 (R_CANFD_BASE + R_CANFD_CFDGRSTC_OFFSET)
#define R_CANFD_CFDC0DCFG                 (R_CANFD_BASE + R_CANFD_CFDC0DCFG_OFFSET)
#define R_CANFD_CFDC0FDCFG                 (R_CANFD_BASE + R_CANFD_CFDC0FDCFG_OFFSET)
#define R_CANFD_CFDC0FDCTR                 (R_CANFD_BASE + R_CANFD_CFDC0FDCTR_OFFSET)
#define R_CANFD_CFDC0FDSTS                 (R_CANFD_BASE + R_CANFD_CFDC0FDSTS_OFFSET)
#define R_CANFD_CFDC0FDCRC                 (R_CANFD_BASE + R_CANFD_CFDC0FDCRC_OFFSET)
#define R_CANFD_CFDGAFLID01                 (R_CANFD_BASE + R_CANFD_CFDGAFLID01_OFFSET)
#define R_CANFD_CFDGAFLID02                 (R_CANFD_BASE + R_CANFD_CFDGAFLID02_OFFSET)
#define R_CANFD_CFDGAFLID03                 (R_CANFD_BASE + R_CANFD_CFDGAFLID03_OFFSET)
#define R_CANFD_CFDGAFLID04                 (R_CANFD_BASE + R_CANFD_CFDGAFLID04_OFFSET)
#define R_CANFD_CFDGAFLID05                 (R_CANFD_BASE + R_CANFD_CFDGAFLID05_OFFSET)
#define R_CANFD_CFDGAFLID06                 (R_CANFD_BASE + R_CANFD_CFDGAFLID06_OFFSET)
#define R_CANFD_CFDGAFLID07                 (R_CANFD_BASE + R_CANFD_CFDGAFLID07_OFFSET)
#define R_CANFD_CFDGAFLID08                 (R_CANFD_BASE + R_CANFD_CFDGAFLID08_OFFSET)
#define R_CANFD_CFDGAFLID09                 (R_CANFD_BASE + R_CANFD_CFDGAFLID09_OFFSET)
#define R_CANFD_CFDGAFLID10                 (R_CANFD_BASE + R_CANFD_CFDGAFLID10_OFFSET)
#define R_CANFD_CFDGAFLID11                 (R_CANFD_BASE + R_CANFD_CFDGAFLID11_OFFSET)
#define R_CANFD_CFDGAFLID12                 (R_CANFD_BASE + R_CANFD_CFDGAFLID12_OFFSET)
#define R_CANFD_CFDGAFLID13                 (R_CANFD_BASE + R_CANFD_CFDGAFLID13_OFFSET)
#define R_CANFD_CFDGAFLID14                 (R_CANFD_BASE + R_CANFD_CFDGAFLID14_OFFSET)
#define R_CANFD_CFDGAFLID15                 (R_CANFD_BASE + R_CANFD_CFDGAFLID15_OFFSET)
#define R_CANFD_CFDGAFLID16                 (R_CANFD_BASE + R_CANFD_CFDGAFLID16_OFFSET)
#define R_CANFD_CFDGAFLM01                 (R_CANFD_BASE + R_CANFD_CFDGAFLM01_OFFSET)
#define R_CANFD_CFDGAFLM02                 (R_CANFD_BASE + R_CANFD_CFDGAFLM02_OFFSET)
#define R_CANFD_CFDGAFLM03                 (R_CANFD_BASE + R_CANFD_CFDGAFLM03_OFFSET)
#define R_CANFD_CFDGAFLM04                 (R_CANFD_BASE + R_CANFD_CFDGAFLM04_OFFSET)
#define R_CANFD_CFDGAFLM05                 (R_CANFD_BASE + R_CANFD_CFDGAFLM05_OFFSET)
#define R_CANFD_CFDGAFLM06                 (R_CANFD_BASE + R_CANFD_CFDGAFLM06_OFFSET)
#define R_CANFD_CFDGAFLM07                 (R_CANFD_BASE + R_CANFD_CFDGAFLM07_OFFSET)
#define R_CANFD_CFDGAFLM08                 (R_CANFD_BASE + R_CANFD_CFDGAFLM08_OFFSET)
#define R_CANFD_CFDGAFLM09                 (R_CANFD_BASE + R_CANFD_CFDGAFLM09_OFFSET)
#define R_CANFD_CFDGAFLM10                 (R_CANFD_BASE + R_CANFD_CFDGAFLM10_OFFSET)
#define R_CANFD_CFDGAFLM11                 (R_CANFD_BASE + R_CANFD_CFDGAFLM11_OFFSET)
#define R_CANFD_CFDGAFLM12                 (R_CANFD_BASE + R_CANFD_CFDGAFLM12_OFFSET)
#define R_CANFD_CFDGAFLM13                 (R_CANFD_BASE + R_CANFD_CFDGAFLM13_OFFSET)
#define R_CANFD_CFDGAFLM14                 (R_CANFD_BASE + R_CANFD_CFDGAFLM14_OFFSET)
#define R_CANFD_CFDGAFLM15                 (R_CANFD_BASE + R_CANFD_CFDGAFLM15_OFFSET)
#define R_CANFD_CFDGAFLM16                 (R_CANFD_BASE + R_CANFD_CFDGAFLM16_OFFSET)
#define R_CANFD_CFDGAFLP001                 (R_CANFD_BASE + R_CANFD_CFDGAFLP001_OFFSET)
#define R_CANFD_CFDGAFLP002                 (R_CANFD_BASE + R_CANFD_CFDGAFLP002_OFFSET)
#define R_CANFD_CFDGAFLP003                 (R_CANFD_BASE + R_CANFD_CFDGAFLP003_OFFSET)
#define R_CANFD_CFDGAFLP004                 (R_CANFD_BASE + R_CANFD_CFDGAFLP004_OFFSET)
#define R_CANFD_CFDGAFLP005                 (R_CANFD_BASE + R_CANFD_CFDGAFLP005_OFFSET)
#define R_CANFD_CFDGAFLP006                 (R_CANFD_BASE + R_CANFD_CFDGAFLP006_OFFSET)
#define R_CANFD_CFDGAFLP007                 (R_CANFD_BASE + R_CANFD_CFDGAFLP007_OFFSET)
#define R_CANFD_CFDGAFLP008                 (R_CANFD_BASE + R_CANFD_CFDGAFLP008_OFFSET)
#define R_CANFD_CFDGAFLP009                 (R_CANFD_BASE + R_CANFD_CFDGAFLP009_OFFSET)
#define R_CANFD_CFDGAFLP010                 (R_CANFD_BASE + R_CANFD_CFDGAFLP010_OFFSET)
#define R_CANFD_CFDGAFLP011                 (R_CANFD_BASE + R_CANFD_CFDGAFLP011_OFFSET)
#define R_CANFD_CFDGAFLP012                 (R_CANFD_BASE + R_CANFD_CFDGAFLP012_OFFSET)
#define R_CANFD_CFDGAFLP013                 (R_CANFD_BASE + R_CANFD_CFDGAFLP013_OFFSET)
#define R_CANFD_CFDGAFLP014                 (R_CANFD_BASE + R_CANFD_CFDGAFLP014_OFFSET)
#define R_CANFD_CFDGAFLP015                 (R_CANFD_BASE + R_CANFD_CFDGAFLP015_OFFSET)
#define R_CANFD_CFDGAFLP016                 (R_CANFD_BASE + R_CANFD_CFDGAFLP016_OFFSET)
#define R_CANFD_CFDGAFLP101                 (R_CANFD_BASE + R_CANFD_CFDGAFLP101_OFFSET)
#define R_CANFD_CFDGAFLP102                 (R_CANFD_BASE + R_CANFD_CFDGAFLP102_OFFSET)
#define R_CANFD_CFDGAFLP103                 (R_CANFD_BASE + R_CANFD_CFDGAFLP103_OFFSET)
#define R_CANFD_CFDGAFLP104                 (R_CANFD_BASE + R_CANFD_CFDGAFLP104_OFFSET)
#define R_CANFD_CFDGAFLP105                 (R_CANFD_BASE + R_CANFD_CFDGAFLP105_OFFSET)
#define R_CANFD_CFDGAFLP106                 (R_CANFD_BASE + R_CANFD_CFDGAFLP106_OFFSET)
#define R_CANFD_CFDGAFLP107                 (R_CANFD_BASE + R_CANFD_CFDGAFLP107_OFFSET)
#define R_CANFD_CFDGAFLP108                 (R_CANFD_BASE + R_CANFD_CFDGAFLP108_OFFSET)
#define R_CANFD_CFDGAFLP109                 (R_CANFD_BASE + R_CANFD_CFDGAFLP109_OFFSET)
#define R_CANFD_CFDGAFLP110                 (R_CANFD_BASE + R_CANFD_CFDGAFLP110_OFFSET)
#define R_CANFD_CFDGAFLP111                 (R_CANFD_BASE + R_CANFD_CFDGAFLP111_OFFSET)
#define R_CANFD_CFDGAFLP112                 (R_CANFD_BASE + R_CANFD_CFDGAFLP112_OFFSET)
#define R_CANFD_CFDGAFLP113                 (R_CANFD_BASE + R_CANFD_CFDGAFLP113_OFFSET)
#define R_CANFD_CFDGAFLP114                 (R_CANFD_BASE + R_CANFD_CFDGAFLP114_OFFSET)
#define R_CANFD_CFDGAFLP115                 (R_CANFD_BASE + R_CANFD_CFDGAFLP115_OFFSET)
#define R_CANFD_CFDGAFLP116                 (R_CANFD_BASE + R_CANFD_CFDGAFLP116_OFFSET)
#define R_CANFD_CFDRPGACC00                 (R_CANFD_BASE + R_CANFD_CFDRPGACC00_OFFSET)
#define R_CANFD_CFDRPGACC01                 (R_CANFD_BASE + R_CANFD_CFDRPGACC01_OFFSET)
#define R_CANFD_CFDRPGACC02                 (R_CANFD_BASE + R_CANFD_CFDRPGACC02_OFFSET)
#define R_CANFD_CFDRPGACC03                 (R_CANFD_BASE + R_CANFD_CFDRPGACC03_OFFSET)
#define R_CANFD_CFDRPGACC04                 (R_CANFD_BASE + R_CANFD_CFDRPGACC04_OFFSET)
#define R_CANFD_CFDRPGACC05                 (R_CANFD_BASE + R_CANFD_CFDRPGACC05_OFFSET)
#define R_CANFD_CFDRPGACC06                 (R_CANFD_BASE + R_CANFD_CFDRPGACC06_OFFSET)
#define R_CANFD_CFDRPGACC07                 (R_CANFD_BASE + R_CANFD_CFDRPGACC07_OFFSET)
#define R_CANFD_CFDRPGACC08                 (R_CANFD_BASE + R_CANFD_CFDRPGACC08_OFFSET)
#define R_CANFD_CFDRPGACC09                 (R_CANFD_BASE + R_CANFD_CFDRPGACC09_OFFSET)
#define R_CANFD_CFDRPGACC10                 (R_CANFD_BASE + R_CANFD_CFDRPGACC10_OFFSET)
#define R_CANFD_CFDRPGACC11                 (R_CANFD_BASE + R_CANFD_CFDRPGACC11_OFFSET)
#define R_CANFD_CFDRPGACC12                 (R_CANFD_BASE + R_CANFD_CFDRPGACC12_OFFSET)
#define R_CANFD_CFDRPGACC13                 (R_CANFD_BASE + R_CANFD_CFDRPGACC13_OFFSET)
#define R_CANFD_CFDRPGACC14                 (R_CANFD_BASE + R_CANFD_CFDRPGACC14_OFFSET)
#define R_CANFD_CFDRPGACC15                 (R_CANFD_BASE + R_CANFD_CFDRPGACC15_OFFSET)
#define R_CANFD_CFDRPGACC16                 (R_CANFD_BASE + R_CANFD_CFDRPGACC16_OFFSET)
#define R_CANFD_CFDRPGACC17                 (R_CANFD_BASE + R_CANFD_CFDRPGACC17_OFFSET)
#define R_CANFD_CFDRPGACC18                 (R_CANFD_BASE + R_CANFD_CFDRPGACC18_OFFSET)
#define R_CANFD_CFDRPGACC19                 (R_CANFD_BASE + R_CANFD_CFDRPGACC19_OFFSET)
#define R_CANFD_CFDRPGACC20                 (R_CANFD_BASE + R_CANFD_CFDRPGACC20_OFFSET)
#define R_CANFD_CFDRPGACC21                 (R_CANFD_BASE + R_CANFD_CFDRPGACC21_OFFSET)
#define R_CANFD_CFDRPGACC22                 (R_CANFD_BASE + R_CANFD_CFDRPGACC22_OFFSET)
#define R_CANFD_CFDRPGACC23                 (R_CANFD_BASE + R_CANFD_CFDRPGACC23_OFFSET)
#define R_CANFD_CFDRPGACC24                 (R_CANFD_BASE + R_CANFD_CFDRPGACC24_OFFSET)
#define R_CANFD_CFDRPGACC25                 (R_CANFD_BASE + R_CANFD_CFDRPGACC25_OFFSET)
#define R_CANFD_CFDRPGACC26                 (R_CANFD_BASE + R_CANFD_CFDRPGACC26_OFFSET)
#define R_CANFD_CFDRPGACC27                 (R_CANFD_BASE + R_CANFD_CFDRPGACC27_OFFSET)
#define R_CANFD_CFDRPGACC28                 (R_CANFD_BASE + R_CANFD_CFDRPGACC28_OFFSET)
#define R_CANFD_CFDRPGACC29                 (R_CANFD_BASE + R_CANFD_CFDRPGACC29_OFFSET)
#define R_CANFD_CFDRPGACC30                 (R_CANFD_BASE + R_CANFD_CFDRPGACC30_OFFSET)
#define R_CANFD_CFDRPGACC31                 (R_CANFD_BASE + R_CANFD_CFDRPGACC31_OFFSET)
#define R_CANFD_CFDRPGACC32                 (R_CANFD_BASE + R_CANFD_CFDRPGACC32_OFFSET)
#define R_CANFD_CFDRPGACC33                 (R_CANFD_BASE + R_CANFD_CFDRPGACC33_OFFSET)
#define R_CANFD_CFDRPGACC34                 (R_CANFD_BASE + R_CANFD_CFDRPGACC34_OFFSET)
#define R_CANFD_CFDRPGACC35                 (R_CANFD_BASE + R_CANFD_CFDRPGACC35_OFFSET)
#define R_CANFD_CFDRPGACC36                 (R_CANFD_BASE + R_CANFD_CFDRPGACC36_OFFSET)
#define R_CANFD_CFDRPGACC37                 (R_CANFD_BASE + R_CANFD_CFDRPGACC37_OFFSET)
#define R_CANFD_CFDRPGACC38                 (R_CANFD_BASE + R_CANFD_CFDRPGACC38_OFFSET)
#define R_CANFD_CFDRPGACC39                 (R_CANFD_BASE + R_CANFD_CFDRPGACC39_OFFSET)
#define R_CANFD_CFDRPGACC40                 (R_CANFD_BASE + R_CANFD_CFDRPGACC40_OFFSET)
#define R_CANFD_CFDRPGACC41                 (R_CANFD_BASE + R_CANFD_CFDRPGACC41_OFFSET)
#define R_CANFD_CFDRPGACC42                 (R_CANFD_BASE + R_CANFD_CFDRPGACC42_OFFSET)
#define R_CANFD_CFDRPGACC43                 (R_CANFD_BASE + R_CANFD_CFDRPGACC43_OFFSET)
#define R_CANFD_CFDRPGACC44                 (R_CANFD_BASE + R_CANFD_CFDRPGACC44_OFFSET)
#define R_CANFD_CFDRPGACC45                 (R_CANFD_BASE + R_CANFD_CFDRPGACC45_OFFSET)
#define R_CANFD_CFDRPGACC46                 (R_CANFD_BASE + R_CANFD_CFDRPGACC46_OFFSET)
#define R_CANFD_CFDRPGACC47                 (R_CANFD_BASE + R_CANFD_CFDRPGACC47_OFFSET)
#define R_CANFD_CFDRPGACC48                 (R_CANFD_BASE + R_CANFD_CFDRPGACC48_OFFSET)
#define R_CANFD_CFDRPGACC49                 (R_CANFD_BASE + R_CANFD_CFDRPGACC49_OFFSET)
#define R_CANFD_CFDRPGACC50                 (R_CANFD_BASE + R_CANFD_CFDRPGACC50_OFFSET)
#define R_CANFD_CFDRPGACC51                 (R_CANFD_BASE + R_CANFD_CFDRPGACC51_OFFSET)
#define R_CANFD_CFDRPGACC52                 (R_CANFD_BASE + R_CANFD_CFDRPGACC52_OFFSET)
#define R_CANFD_CFDRPGACC53                 (R_CANFD_BASE + R_CANFD_CFDRPGACC53_OFFSET)
#define R_CANFD_CFDRPGACC54                 (R_CANFD_BASE + R_CANFD_CFDRPGACC54_OFFSET)
#define R_CANFD_CFDRPGACC55                 (R_CANFD_BASE + R_CANFD_CFDRPGACC55_OFFSET)
#define R_CANFD_CFDRPGACC56                 (R_CANFD_BASE + R_CANFD_CFDRPGACC56_OFFSET)
#define R_CANFD_CFDRPGACC57                 (R_CANFD_BASE + R_CANFD_CFDRPGACC57_OFFSET)
#define R_CANFD_CFDRPGACC58                 (R_CANFD_BASE + R_CANFD_CFDRPGACC58_OFFSET)
#define R_CANFD_CFDRPGACC59                 (R_CANFD_BASE + R_CANFD_CFDRPGACC59_OFFSET)
#define R_CANFD_CFDRPGACC60                 (R_CANFD_BASE + R_CANFD_CFDRPGACC60_OFFSET)
#define R_CANFD_CFDRPGACC61                 (R_CANFD_BASE + R_CANFD_CFDRPGACC61_OFFSET)
#define R_CANFD_CFDRPGACC62                 (R_CANFD_BASE + R_CANFD_CFDRPGACC62_OFFSET)
#define R_CANFD_CFDRPGACC63                 (R_CANFD_BASE + R_CANFD_CFDRPGACC63_OFFSET)
#define R_CANFD_CFDRFID0                 (R_CANFD_BASE + R_CANFD_CFDRFID0_OFFSET)
#define R_CANFD_CFDRFID1                 (R_CANFD_BASE + R_CANFD_CFDRFID1_OFFSET)
#define R_CANFD_CFDRFPTR0                 (R_CANFD_BASE + R_CANFD_CFDRFPTR0_OFFSET)
#define R_CANFD_CFDRFPTR1                 (R_CANFD_BASE + R_CANFD_CFDRFPTR1_OFFSET)
#define R_CANFD_CFDRFFDSTS0                 (R_CANFD_BASE + R_CANFD_CFDRFFDSTS0_OFFSET)
#define R_CANFD_CFDRFFDSTS1                 (R_CANFD_BASE + R_CANFD_CFDRFFDSTS1_OFFSET)
#define R_CANFD_CFDRFDF0_0                 (R_CANFD_BASE + R_CANFD_CFDRFDF0_0_OFFSET)
#define R_CANFD_CFDRFDF1_0                 (R_CANFD_BASE + R_CANFD_CFDRFDF1_0_OFFSET)
#define R_CANFD_CFDRFDF0_1                 (R_CANFD_BASE + R_CANFD_CFDRFDF0_1_OFFSET)
#define R_CANFD_CFDRFDF1_1                 (R_CANFD_BASE + R_CANFD_CFDRFDF1_1_OFFSET)
#define R_CANFD_CFDRFDF0_2                 (R_CANFD_BASE + R_CANFD_CFDRFDF0_2_OFFSET)
#define R_CANFD_CFDRFDF1_2                 (R_CANFD_BASE + R_CANFD_CFDRFDF1_2_OFFSET)
#define R_CANFD_CFDRFDF0_3                 (R_CANFD_BASE + R_CANFD_CFDRFDF0_3_OFFSET)
#define R_CANFD_CFDRFDF1_3                 (R_CANFD_BASE + R_CANFD_CFDRFDF1_3_OFFSET)
#define R_CANFD_CFDRFDF0_4                 (R_CANFD_BASE + R_CANFD_CFDRFDF0_4_OFFSET)
#define R_CANFD_CFDRFDF1_4                 (R_CANFD_BASE + R_CANFD_CFDRFDF1_4_OFFSET)
#define R_CANFD_CFDRFDF0_5                 (R_CANFD_BASE + R_CANFD_CFDRFDF0_5_OFFSET)
#define R_CANFD_CFDRFDF1_5                 (R_CANFD_BASE + R_CANFD_CFDRFDF1_5_OFFSET)
#define R_CANFD_CFDRFDF0_6                 (R_CANFD_BASE + R_CANFD_CFDRFDF0_6_OFFSET)
#define R_CANFD_CFDRFDF1_6                 (R_CANFD_BASE + R_CANFD_CFDRFDF1_6_OFFSET)
#define R_CANFD_CFDRFDF0_7                 (R_CANFD_BASE + R_CANFD_CFDRFDF0_7_OFFSET)
#define R_CANFD_CFDRFDF1_7                 (R_CANFD_BASE + R_CANFD_CFDRFDF1_7_OFFSET)
#define R_CANFD_CFDRFDF0_8                 (R_CANFD_BASE + R_CANFD_CFDRFDF0_8_OFFSET)
#define R_CANFD_CFDRFDF1_8                 (R_CANFD_BASE + R_CANFD_CFDRFDF1_8_OFFSET)
#define R_CANFD_CFDRFDF0_9                 (R_CANFD_BASE + R_CANFD_CFDRFDF0_9_OFFSET)
#define R_CANFD_CFDRFDF1_9                 (R_CANFD_BASE + R_CANFD_CFDRFDF1_9_OFFSET)
#define R_CANFD_CFDRFDF0_10                 (R_CANFD_BASE + R_CANFD_CFDRFDF0_10_OFFSET)
#define R_CANFD_CFDRFDF1_10                 (R_CANFD_BASE + R_CANFD_CFDRFDF1_10_OFFSET)
#define R_CANFD_CFDRFDF0_11                 (R_CANFD_BASE + R_CANFD_CFDRFDF0_11_OFFSET)
#define R_CANFD_CFDRFDF1_11                 (R_CANFD_BASE + R_CANFD_CFDRFDF1_11_OFFSET)
#define R_CANFD_CFDRFDF0_12                 (R_CANFD_BASE + R_CANFD_CFDRFDF0_12_OFFSET)
#define R_CANFD_CFDRFDF1_12                 (R_CANFD_BASE + R_CANFD_CFDRFDF1_12_OFFSET)
#define R_CANFD_CFDRFDF0_13                 (R_CANFD_BASE + R_CANFD_CFDRFDF0_13_OFFSET)
#define R_CANFD_CFDRFDF1_13                 (R_CANFD_BASE + R_CANFD_CFDRFDF1_13_OFFSET)
#define R_CANFD_CFDRFDF0_14                 (R_CANFD_BASE + R_CANFD_CFDRFDF0_14_OFFSET)
#define R_CANFD_CFDRFDF1_14                 (R_CANFD_BASE + R_CANFD_CFDRFDF1_14_OFFSET)
#define R_CANFD_CFDRFDF0_15                 (R_CANFD_BASE + R_CANFD_CFDRFDF0_15_OFFSET)
#define R_CANFD_CFDRFDF1_15                 (R_CANFD_BASE + R_CANFD_CFDRFDF1_15_OFFSET)
#define R_CANFD_CFDCFID                 (R_CANFD_BASE + R_CANFD_CFDCFID_OFFSET)
#define R_CANFD_CFDCFPTR                 (R_CANFD_BASE + R_CANFD_CFDCFPTR_OFFSET)
#define R_CANFD_CFDCFFDCSTS                 (R_CANFD_BASE + R_CANFD_CFDCFFDCSTS_OFFSET)
#define R_CANFD_CFDCFDF00                 (R_CANFD_BASE + R_CANFD_CFDCFDF00_OFFSET)
#define R_CANFD_CFDCFDF01                 (R_CANFD_BASE + R_CANFD_CFDCFDF01_OFFSET)
#define R_CANFD_CFDCFDF02                 (R_CANFD_BASE + R_CANFD_CFDCFDF02_OFFSET)
#define R_CANFD_CFDCFDF03                 (R_CANFD_BASE + R_CANFD_CFDCFDF03_OFFSET)
#define R_CANFD_CFDCFDF04                 (R_CANFD_BASE + R_CANFD_CFDCFDF04_OFFSET)
#define R_CANFD_CFDCFDF05                 (R_CANFD_BASE + R_CANFD_CFDCFDF05_OFFSET)
#define R_CANFD_CFDCFDF06                 (R_CANFD_BASE + R_CANFD_CFDCFDF06_OFFSET)
#define R_CANFD_CFDCFDF07                 (R_CANFD_BASE + R_CANFD_CFDCFDF07_OFFSET)
#define R_CANFD_CFDCFDF08                 (R_CANFD_BASE + R_CANFD_CFDCFDF08_OFFSET)
#define R_CANFD_CFDCFDF09                 (R_CANFD_BASE + R_CANFD_CFDCFDF09_OFFSET)
#define R_CANFD_CFDCFDF10                 (R_CANFD_BASE + R_CANFD_CFDCFDF10_OFFSET)
#define R_CANFD_CFDCFDF11                 (R_CANFD_BASE + R_CANFD_CFDCFDF11_OFFSET)
#define R_CANFD_CFDCFDF12                 (R_CANFD_BASE + R_CANFD_CFDCFDF12_OFFSET)
#define R_CANFD_CFDCFDF13                 (R_CANFD_BASE + R_CANFD_CFDCFDF13_OFFSET)
#define R_CANFD_CFDCFDF14                 (R_CANFD_BASE + R_CANFD_CFDCFDF14_OFFSET)
#define R_CANFD_CFDCFDF15                 (R_CANFD_BASE + R_CANFD_CFDCFDF15_OFFSET)
#define R_CANFD_CFDTMID0                 (R_CANFD_BASE + R_CANFD_CFDTMID0_OFFSET)
#define R_CANFD_CFDTMID1                 (R_CANFD_BASE + R_CANFD_CFDTMID1_OFFSET)
#define R_CANFD_CFDTMID2                 (R_CANFD_BASE + R_CANFD_CFDTMID2_OFFSET)
#define R_CANFD_CFDTMID3                 (R_CANFD_BASE + R_CANFD_CFDTMID3_OFFSET)
#define R_CANFD_CFDTMPTR0                 (R_CANFD_BASE + R_CANFD_CFDTMPTR0_OFFSET)
#define R_CANFD_CFDTMPTR1                 (R_CANFD_BASE + R_CANFD_CFDTMPTR1_OFFSET)
#define R_CANFD_CFDTMPTR2                 (R_CANFD_BASE + R_CANFD_CFDTMPTR2_OFFSET)
#define R_CANFD_CFDTMPTR3                 (R_CANFD_BASE + R_CANFD_CFDTMPTR3_OFFSET)
#define R_CANFD_CFDTMFDCTR0                 (R_CANFD_BASE + R_CANFD_CFDTMFDCTR0_OFFSET)
#define R_CANFD_CFDTMFDCTR1                 (R_CANFD_BASE + R_CANFD_CFDTMFDCTR1_OFFSET)
#define R_CANFD_CFDTMFDCTR2                 (R_CANFD_BASE + R_CANFD_CFDTMFDCTR2_OFFSET)
#define R_CANFD_CFDTMFDCTR3                 (R_CANFD_BASE + R_CANFD_CFDTMFDCTR3_OFFSET)
#define R_CANFD_CFDTMDF0_0                 (R_CANFD_BASE + R_CANFD_CFDTMDF0_0_OFFSET)
#define R_CANFD_CFDTMDF1_0                 (R_CANFD_BASE + R_CANFD_CFDTMDF1_0_OFFSET)
#define R_CANFD_CFDTMDF2_0                 (R_CANFD_BASE + R_CANFD_CFDTMDF2_0_OFFSET)
#define R_CANFD_CFDTMDF3_0                 (R_CANFD_BASE + R_CANFD_CFDTMDF3_0_OFFSET)
#define R_CANFD_CFDTMDF0_1                 (R_CANFD_BASE + R_CANFD_CFDTMDF0_1_OFFSET)
#define R_CANFD_CFDTMDF1_1                 (R_CANFD_BASE + R_CANFD_CFDTMDF1_1_OFFSET)
#define R_CANFD_CFDTMDF2_1                 (R_CANFD_BASE + R_CANFD_CFDTMDF2_1_OFFSET)
#define R_CANFD_CFDTMDF3_1                 (R_CANFD_BASE + R_CANFD_CFDTMDF3_1_OFFSET)
#define R_CANFD_CFDTMDF0_2                 (R_CANFD_BASE + R_CANFD_CFDTMDF0_2_OFFSET)
#define R_CANFD_CFDTMDF1_2                 (R_CANFD_BASE + R_CANFD_CFDTMDF1_2_OFFSET)
#define R_CANFD_CFDTMDF2_2                 (R_CANFD_BASE + R_CANFD_CFDTMDF2_2_OFFSET)
#define R_CANFD_CFDTMDF3_2                 (R_CANFD_BASE + R_CANFD_CFDTMDF3_2_OFFSET)
#define R_CANFD_CFDTMDF0_3                 (R_CANFD_BASE + R_CANFD_CFDTMDF0_3_OFFSET)
#define R_CANFD_CFDTMDF1_3                 (R_CANFD_BASE + R_CANFD_CFDTMDF1_3_OFFSET)
#define R_CANFD_CFDTMDF2_3                 (R_CANFD_BASE + R_CANFD_CFDTMDF2_3_OFFSET)
#define R_CANFD_CFDTMDF3_3                 (R_CANFD_BASE + R_CANFD_CFDTMDF3_3_OFFSET)
#define R_CANFD_CFDTMDF0_4                 (R_CANFD_BASE + R_CANFD_CFDTMDF0_4_OFFSET)
#define R_CANFD_CFDTMDF1_4                 (R_CANFD_BASE + R_CANFD_CFDTMDF1_4_OFFSET)
#define R_CANFD_CFDTMDF2_4                 (R_CANFD_BASE + R_CANFD_CFDTMDF2_4_OFFSET)
#define R_CANFD_CFDTMDF3_4                 (R_CANFD_BASE + R_CANFD_CFDTMDF3_4_OFFSET)
#define R_CANFD_CFDTMDF0_5                 (R_CANFD_BASE + R_CANFD_CFDTMDF0_5_OFFSET)
#define R_CANFD_CFDTMDF1_5                 (R_CANFD_BASE + R_CANFD_CFDTMDF1_5_OFFSET)
#define R_CANFD_CFDTMDF2_5                 (R_CANFD_BASE + R_CANFD_CFDTMDF2_5_OFFSET)
#define R_CANFD_CFDTMDF3_5                 (R_CANFD_BASE + R_CANFD_CFDTMDF3_5_OFFSET)
#define R_CANFD_CFDTMDF0_6                 (R_CANFD_BASE + R_CANFD_CFDTMDF0_6_OFFSET)
#define R_CANFD_CFDTMDF1_6                 (R_CANFD_BASE + R_CANFD_CFDTMDF1_6_OFFSET)
#define R_CANFD_CFDTMDF2_6                 (R_CANFD_BASE + R_CANFD_CFDTMDF2_6_OFFSET)
#define R_CANFD_CFDTMDF3_6                 (R_CANFD_BASE + R_CANFD_CFDTMDF3_6_OFFSET)
#define R_CANFD_CFDTMDF0_7                 (R_CANFD_BASE + R_CANFD_CFDTMDF0_7_OFFSET)
#define R_CANFD_CFDTMDF1_7                 (R_CANFD_BASE + R_CANFD_CFDTMDF1_7_OFFSET)
#define R_CANFD_CFDTMDF2_7                 (R_CANFD_BASE + R_CANFD_CFDTMDF2_7_OFFSET)
#define R_CANFD_CFDTMDF3_7                 (R_CANFD_BASE + R_CANFD_CFDTMDF3_7_OFFSET)
#define R_CANFD_CFDTMDF0_8                 (R_CANFD_BASE + R_CANFD_CFDTMDF0_8_OFFSET)
#define R_CANFD_CFDTMDF1_8                 (R_CANFD_BASE + R_CANFD_CFDTMDF1_8_OFFSET)
#define R_CANFD_CFDTMDF2_8                 (R_CANFD_BASE + R_CANFD_CFDTMDF2_8_OFFSET)
#define R_CANFD_CFDTMDF3_8                 (R_CANFD_BASE + R_CANFD_CFDTMDF3_8_OFFSET)
#define R_CANFD_CFDTMDF0_9                 (R_CANFD_BASE + R_CANFD_CFDTMDF0_9_OFFSET)
#define R_CANFD_CFDTMDF1_9                 (R_CANFD_BASE + R_CANFD_CFDTMDF1_9_OFFSET)
#define R_CANFD_CFDTMDF2_9                 (R_CANFD_BASE + R_CANFD_CFDTMDF2_9_OFFSET)
#define R_CANFD_CFDTMDF3_9                 (R_CANFD_BASE + R_CANFD_CFDTMDF3_9_OFFSET)
#define R_CANFD_CFDTMDF0_10                 (R_CANFD_BASE + R_CANFD_CFDTMDF0_10_OFFSET)
#define R_CANFD_CFDTMDF1_10                 (R_CANFD_BASE + R_CANFD_CFDTMDF1_10_OFFSET)
#define R_CANFD_CFDTMDF2_10                 (R_CANFD_BASE + R_CANFD_CFDTMDF2_10_OFFSET)
#define R_CANFD_CFDTMDF3_10                 (R_CANFD_BASE + R_CANFD_CFDTMDF3_10_OFFSET)
#define R_CANFD_CFDTMDF0_11                 (R_CANFD_BASE + R_CANFD_CFDTMDF0_11_OFFSET)
#define R_CANFD_CFDTMDF1_11                 (R_CANFD_BASE + R_CANFD_CFDTMDF1_11_OFFSET)
#define R_CANFD_CFDTMDF2_11                 (R_CANFD_BASE + R_CANFD_CFDTMDF2_11_OFFSET)
#define R_CANFD_CFDTMDF3_11                 (R_CANFD_BASE + R_CANFD_CFDTMDF3_11_OFFSET)
#define R_CANFD_CFDTMDF0_12                 (R_CANFD_BASE + R_CANFD_CFDTMDF0_12_OFFSET)
#define R_CANFD_CFDTMDF1_12                 (R_CANFD_BASE + R_CANFD_CFDTMDF1_12_OFFSET)
#define R_CANFD_CFDTMDF2_12                 (R_CANFD_BASE + R_CANFD_CFDTMDF2_12_OFFSET)
#define R_CANFD_CFDTMDF3_12                 (R_CANFD_BASE + R_CANFD_CFDTMDF3_12_OFFSET)
#define R_CANFD_CFDTMDF0_13                 (R_CANFD_BASE + R_CANFD_CFDTMDF0_13_OFFSET)
#define R_CANFD_CFDTMDF1_13                 (R_CANFD_BASE + R_CANFD_CFDTMDF1_13_OFFSET)
#define R_CANFD_CFDTMDF2_13                 (R_CANFD_BASE + R_CANFD_CFDTMDF2_13_OFFSET)
#define R_CANFD_CFDTMDF3_13                 (R_CANFD_BASE + R_CANFD_CFDTMDF3_13_OFFSET)
#define R_CANFD_CFDTMDF0_14                 (R_CANFD_BASE + R_CANFD_CFDTMDF0_14_OFFSET)
#define R_CANFD_CFDTMDF1_14                 (R_CANFD_BASE + R_CANFD_CFDTMDF1_14_OFFSET)
#define R_CANFD_CFDTMDF2_14                 (R_CANFD_BASE + R_CANFD_CFDTMDF2_14_OFFSET)
#define R_CANFD_CFDTMDF3_14                 (R_CANFD_BASE + R_CANFD_CFDTMDF3_14_OFFSET)
#define R_CANFD_CFDTMDF0_15                 (R_CANFD_BASE + R_CANFD_CFDTMDF0_15_OFFSET)
#define R_CANFD_CFDTMDF1_15                 (R_CANFD_BASE + R_CANFD_CFDTMDF1_15_OFFSET)
#define R_CANFD_CFDTMDF2_15                 (R_CANFD_BASE + R_CANFD_CFDTMDF2_15_OFFSET)
#define R_CANFD_CFDTMDF3_15                 (R_CANFD_BASE + R_CANFD_CFDTMDF3_15_OFFSET)
#define R_CANFD_CFDTHLACC0                 (R_CANFD_BASE + R_CANFD_CFDTHLACC0_OFFSET)
#define R_CANFD_CFDTHLACC1                 (R_CANFD_BASE + R_CANFD_CFDTHLACC1_OFFSET)
#define R_CANFD_CFDRMID0                 (R_CANFD_BASE + R_CANFD_CFDRMID0_OFFSET)
#define R_CANFD_CFDRMID1                 (R_CANFD_BASE + R_CANFD_CFDRMID1_OFFSET)
#define R_CANFD_CFDRMID2                 (R_CANFD_BASE + R_CANFD_CFDRMID2_OFFSET)
#define R_CANFD_CFDRMID3                 (R_CANFD_BASE + R_CANFD_CFDRMID3_OFFSET)
#define R_CANFD_CFDRMID4                 (R_CANFD_BASE + R_CANFD_CFDRMID4_OFFSET)
#define R_CANFD_CFDRMID5                 (R_CANFD_BASE + R_CANFD_CFDRMID5_OFFSET)
#define R_CANFD_CFDRMID6                 (R_CANFD_BASE + R_CANFD_CFDRMID6_OFFSET)
#define R_CANFD_CFDRMID7                 (R_CANFD_BASE + R_CANFD_CFDRMID7_OFFSET)
#define R_CANFD_CFDRMPTR0                 (R_CANFD_BASE + R_CANFD_CFDRMPTR0_OFFSET)
#define R_CANFD_CFDRMPTR1                 (R_CANFD_BASE + R_CANFD_CFDRMPTR1_OFFSET)
#define R_CANFD_CFDRMPTR2                 (R_CANFD_BASE + R_CANFD_CFDRMPTR2_OFFSET)
#define R_CANFD_CFDRMPTR3                 (R_CANFD_BASE + R_CANFD_CFDRMPTR3_OFFSET)
#define R_CANFD_CFDRMPTR4                 (R_CANFD_BASE + R_CANFD_CFDRMPTR4_OFFSET)
#define R_CANFD_CFDRMPTR5                 (R_CANFD_BASE + R_CANFD_CFDRMPTR5_OFFSET)
#define R_CANFD_CFDRMPTR6                 (R_CANFD_BASE + R_CANFD_CFDRMPTR6_OFFSET)
#define R_CANFD_CFDRMPTR7                 (R_CANFD_BASE + R_CANFD_CFDRMPTR7_OFFSET)
#define R_CANFD_CFDRMFDSTS0                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS0_OFFSET)
#define R_CANFD_CFDRMFDSTS1                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS1_OFFSET)
#define R_CANFD_CFDRMFDSTS2                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS2_OFFSET)
#define R_CANFD_CFDRMFDSTS3                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS3_OFFSET)
#define R_CANFD_CFDRMFDSTS4                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS4_OFFSET)
#define R_CANFD_CFDRMFDSTS5                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS5_OFFSET)
#define R_CANFD_CFDRMFDSTS6                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS6_OFFSET)
#define R_CANFD_CFDRMFDSTS7                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS7_OFFSET)
#define R_CANFD_CFDRMDF0_0                 (R_CANFD_BASE + R_CANFD_CFDRMDF0_0_OFFSET)
#define R_CANFD_CFDRMDF1_0                 (R_CANFD_BASE + R_CANFD_CFDRMDF1_0_OFFSET)
#define R_CANFD_CFDRMDF2_0                 (R_CANFD_BASE + R_CANFD_CFDRMDF2_0_OFFSET)
#define R_CANFD_CFDRMDF3_0                 (R_CANFD_BASE + R_CANFD_CFDRMDF3_0_OFFSET)
#define R_CANFD_CFDRMDF4_0                 (R_CANFD_BASE + R_CANFD_CFDRMDF4_0_OFFSET)
#define R_CANFD_CFDRMDF5_0                 (R_CANFD_BASE + R_CANFD_CFDRMDF5_0_OFFSET)
#define R_CANFD_CFDRMDF6_0                 (R_CANFD_BASE + R_CANFD_CFDRMDF6_0_OFFSET)
#define R_CANFD_CFDRMDF7_0                 (R_CANFD_BASE + R_CANFD_CFDRMDF7_0_OFFSET)
#define R_CANFD_CFDRMDF0_1                 (R_CANFD_BASE + R_CANFD_CFDRMDF0_1_OFFSET)
#define R_CANFD_CFDRMDF1_1                 (R_CANFD_BASE + R_CANFD_CFDRMDF1_1_OFFSET)
#define R_CANFD_CFDRMDF2_1                 (R_CANFD_BASE + R_CANFD_CFDRMDF2_1_OFFSET)
#define R_CANFD_CFDRMDF3_1                 (R_CANFD_BASE + R_CANFD_CFDRMDF3_1_OFFSET)
#define R_CANFD_CFDRMDF4_1                 (R_CANFD_BASE + R_CANFD_CFDRMDF4_1_OFFSET)
#define R_CANFD_CFDRMDF5_1                 (R_CANFD_BASE + R_CANFD_CFDRMDF5_1_OFFSET)
#define R_CANFD_CFDRMDF6_1                 (R_CANFD_BASE + R_CANFD_CFDRMDF6_1_OFFSET)
#define R_CANFD_CFDRMDF7_1                 (R_CANFD_BASE + R_CANFD_CFDRMDF7_1_OFFSET)
#define R_CANFD_CFDRMDF0_2                 (R_CANFD_BASE + R_CANFD_CFDRMDF0_2_OFFSET)
#define R_CANFD_CFDRMDF1_2                 (R_CANFD_BASE + R_CANFD_CFDRMDF1_2_OFFSET)
#define R_CANFD_CFDRMDF2_2                 (R_CANFD_BASE + R_CANFD_CFDRMDF2_2_OFFSET)
#define R_CANFD_CFDRMDF3_2                 (R_CANFD_BASE + R_CANFD_CFDRMDF3_2_OFFSET)
#define R_CANFD_CFDRMDF4_2                 (R_CANFD_BASE + R_CANFD_CFDRMDF4_2_OFFSET)
#define R_CANFD_CFDRMDF5_2                 (R_CANFD_BASE + R_CANFD_CFDRMDF5_2_OFFSET)
#define R_CANFD_CFDRMDF6_2                 (R_CANFD_BASE + R_CANFD_CFDRMDF6_2_OFFSET)
#define R_CANFD_CFDRMDF7_2                 (R_CANFD_BASE + R_CANFD_CFDRMDF7_2_OFFSET)
#define R_CANFD_CFDRMDF0_3                 (R_CANFD_BASE + R_CANFD_CFDRMDF0_3_OFFSET)
#define R_CANFD_CFDRMDF1_3                 (R_CANFD_BASE + R_CANFD_CFDRMDF1_3_OFFSET)
#define R_CANFD_CFDRMDF2_3                 (R_CANFD_BASE + R_CANFD_CFDRMDF2_3_OFFSET)
#define R_CANFD_CFDRMDF3_3                 (R_CANFD_BASE + R_CANFD_CFDRMDF3_3_OFFSET)
#define R_CANFD_CFDRMDF4_3                 (R_CANFD_BASE + R_CANFD_CFDRMDF4_3_OFFSET)
#define R_CANFD_CFDRMDF5_3                 (R_CANFD_BASE + R_CANFD_CFDRMDF5_3_OFFSET)
#define R_CANFD_CFDRMDF6_3                 (R_CANFD_BASE + R_CANFD_CFDRMDF6_3_OFFSET)
#define R_CANFD_CFDRMDF7_3                 (R_CANFD_BASE + R_CANFD_CFDRMDF7_3_OFFSET)
#define R_CANFD_CFDRMDF0_4                 (R_CANFD_BASE + R_CANFD_CFDRMDF0_4_OFFSET)
#define R_CANFD_CFDRMDF1_4                 (R_CANFD_BASE + R_CANFD_CFDRMDF1_4_OFFSET)
#define R_CANFD_CFDRMDF2_4                 (R_CANFD_BASE + R_CANFD_CFDRMDF2_4_OFFSET)
#define R_CANFD_CFDRMDF3_4                 (R_CANFD_BASE + R_CANFD_CFDRMDF3_4_OFFSET)
#define R_CANFD_CFDRMDF4_4                 (R_CANFD_BASE + R_CANFD_CFDRMDF4_4_OFFSET)
#define R_CANFD_CFDRMDF5_4                 (R_CANFD_BASE + R_CANFD_CFDRMDF5_4_OFFSET)
#define R_CANFD_CFDRMDF6_4                 (R_CANFD_BASE + R_CANFD_CFDRMDF6_4_OFFSET)
#define R_CANFD_CFDRMDF7_4                 (R_CANFD_BASE + R_CANFD_CFDRMDF7_4_OFFSET)
#define R_CANFD_CFDRMDF0_5                 (R_CANFD_BASE + R_CANFD_CFDRMDF0_5_OFFSET)
#define R_CANFD_CFDRMDF1_5                 (R_CANFD_BASE + R_CANFD_CFDRMDF1_5_OFFSET)
#define R_CANFD_CFDRMDF2_5                 (R_CANFD_BASE + R_CANFD_CFDRMDF2_5_OFFSET)
#define R_CANFD_CFDRMDF3_5                 (R_CANFD_BASE + R_CANFD_CFDRMDF3_5_OFFSET)
#define R_CANFD_CFDRMDF4_5                 (R_CANFD_BASE + R_CANFD_CFDRMDF4_5_OFFSET)
#define R_CANFD_CFDRMDF5_5                 (R_CANFD_BASE + R_CANFD_CFDRMDF5_5_OFFSET)
#define R_CANFD_CFDRMDF6_5                 (R_CANFD_BASE + R_CANFD_CFDRMDF6_5_OFFSET)
#define R_CANFD_CFDRMDF7_5                 (R_CANFD_BASE + R_CANFD_CFDRMDF7_5_OFFSET)
#define R_CANFD_CFDRMDF0_6                 (R_CANFD_BASE + R_CANFD_CFDRMDF0_6_OFFSET)
#define R_CANFD_CFDRMDF1_6                 (R_CANFD_BASE + R_CANFD_CFDRMDF1_6_OFFSET)
#define R_CANFD_CFDRMDF2_6                 (R_CANFD_BASE + R_CANFD_CFDRMDF2_6_OFFSET)
#define R_CANFD_CFDRMDF3_6                 (R_CANFD_BASE + R_CANFD_CFDRMDF3_6_OFFSET)
#define R_CANFD_CFDRMDF4_6                 (R_CANFD_BASE + R_CANFD_CFDRMDF4_6_OFFSET)
#define R_CANFD_CFDRMDF5_6                 (R_CANFD_BASE + R_CANFD_CFDRMDF5_6_OFFSET)
#define R_CANFD_CFDRMDF6_6                 (R_CANFD_BASE + R_CANFD_CFDRMDF6_6_OFFSET)
#define R_CANFD_CFDRMDF7_6                 (R_CANFD_BASE + R_CANFD_CFDRMDF7_6_OFFSET)
#define R_CANFD_CFDRMDF0_7                 (R_CANFD_BASE + R_CANFD_CFDRMDF0_7_OFFSET)
#define R_CANFD_CFDRMDF1_7                 (R_CANFD_BASE + R_CANFD_CFDRMDF1_7_OFFSET)
#define R_CANFD_CFDRMDF2_7                 (R_CANFD_BASE + R_CANFD_CFDRMDF2_7_OFFSET)
#define R_CANFD_CFDRMDF3_7                 (R_CANFD_BASE + R_CANFD_CFDRMDF3_7_OFFSET)
#define R_CANFD_CFDRMDF4_7                 (R_CANFD_BASE + R_CANFD_CFDRMDF4_7_OFFSET)
#define R_CANFD_CFDRMDF5_7                 (R_CANFD_BASE + R_CANFD_CFDRMDF5_7_OFFSET)
#define R_CANFD_CFDRMDF6_7                 (R_CANFD_BASE + R_CANFD_CFDRMDF6_7_OFFSET)
#define R_CANFD_CFDRMDF7_7                 (R_CANFD_BASE + R_CANFD_CFDRMDF7_7_OFFSET)
#define R_CANFD_CFDRMDF0_8                 (R_CANFD_BASE + R_CANFD_CFDRMDF0_8_OFFSET)
#define R_CANFD_CFDRMDF1_8                 (R_CANFD_BASE + R_CANFD_CFDRMDF1_8_OFFSET)
#define R_CANFD_CFDRMDF2_8                 (R_CANFD_BASE + R_CANFD_CFDRMDF2_8_OFFSET)
#define R_CANFD_CFDRMDF3_8                 (R_CANFD_BASE + R_CANFD_CFDRMDF3_8_OFFSET)
#define R_CANFD_CFDRMDF4_8                 (R_CANFD_BASE + R_CANFD_CFDRMDF4_8_OFFSET)
#define R_CANFD_CFDRMDF5_8                 (R_CANFD_BASE + R_CANFD_CFDRMDF5_8_OFFSET)
#define R_CANFD_CFDRMDF6_8                 (R_CANFD_BASE + R_CANFD_CFDRMDF6_8_OFFSET)
#define R_CANFD_CFDRMDF7_8                 (R_CANFD_BASE + R_CANFD_CFDRMDF7_8_OFFSET)
#define R_CANFD_CFDRMDF0_9                 (R_CANFD_BASE + R_CANFD_CFDRMDF0_9_OFFSET)
#define R_CANFD_CFDRMDF1_9                 (R_CANFD_BASE + R_CANFD_CFDRMDF1_9_OFFSET)
#define R_CANFD_CFDRMDF2_9                 (R_CANFD_BASE + R_CANFD_CFDRMDF2_9_OFFSET)
#define R_CANFD_CFDRMDF3_9                 (R_CANFD_BASE + R_CANFD_CFDRMDF3_9_OFFSET)
#define R_CANFD_CFDRMDF4_9                 (R_CANFD_BASE + R_CANFD_CFDRMDF4_9_OFFSET)
#define R_CANFD_CFDRMDF5_9                 (R_CANFD_BASE + R_CANFD_CFDRMDF5_9_OFFSET)
#define R_CANFD_CFDRMDF6_9                 (R_CANFD_BASE + R_CANFD_CFDRMDF6_9_OFFSET)
#define R_CANFD_CFDRMDF7_9                 (R_CANFD_BASE + R_CANFD_CFDRMDF7_9_OFFSET)
#define R_CANFD_CFDRMDF0_10                 (R_CANFD_BASE + R_CANFD_CFDRMDF0_10_OFFSET)
#define R_CANFD_CFDRMDF1_10                 (R_CANFD_BASE + R_CANFD_CFDRMDF1_10_OFFSET)
#define R_CANFD_CFDRMDF2_10                 (R_CANFD_BASE + R_CANFD_CFDRMDF2_10_OFFSET)
#define R_CANFD_CFDRMDF3_10                 (R_CANFD_BASE + R_CANFD_CFDRMDF3_10_OFFSET)
#define R_CANFD_CFDRMDF4_10                 (R_CANFD_BASE + R_CANFD_CFDRMDF4_10_OFFSET)
#define R_CANFD_CFDRMDF5_10                 (R_CANFD_BASE + R_CANFD_CFDRMDF5_10_OFFSET)
#define R_CANFD_CFDRMDF6_10                 (R_CANFD_BASE + R_CANFD_CFDRMDF6_10_OFFSET)
#define R_CANFD_CFDRMDF7_10                 (R_CANFD_BASE + R_CANFD_CFDRMDF7_10_OFFSET)
#define R_CANFD_CFDRMDF0_11                 (R_CANFD_BASE + R_CANFD_CFDRMDF0_11_OFFSET)
#define R_CANFD_CFDRMDF1_11                 (R_CANFD_BASE + R_CANFD_CFDRMDF1_11_OFFSET)
#define R_CANFD_CFDRMDF2_11                 (R_CANFD_BASE + R_CANFD_CFDRMDF2_11_OFFSET)
#define R_CANFD_CFDRMDF3_11                 (R_CANFD_BASE + R_CANFD_CFDRMDF3_11_OFFSET)
#define R_CANFD_CFDRMDF4_11                 (R_CANFD_BASE + R_CANFD_CFDRMDF4_11_OFFSET)
#define R_CANFD_CFDRMDF5_11                 (R_CANFD_BASE + R_CANFD_CFDRMDF5_11_OFFSET)
#define R_CANFD_CFDRMDF6_11                 (R_CANFD_BASE + R_CANFD_CFDRMDF6_11_OFFSET)
#define R_CANFD_CFDRMDF7_11                 (R_CANFD_BASE + R_CANFD_CFDRMDF7_11_OFFSET)
#define R_CANFD_CFDRMDF0_12                 (R_CANFD_BASE + R_CANFD_CFDRMDF0_12_OFFSET)
#define R_CANFD_CFDRMDF1_12                 (R_CANFD_BASE + R_CANFD_CFDRMDF1_12_OFFSET)
#define R_CANFD_CFDRMDF2_12                 (R_CANFD_BASE + R_CANFD_CFDRMDF2_12_OFFSET)
#define R_CANFD_CFDRMDF3_12                 (R_CANFD_BASE + R_CANFD_CFDRMDF3_12_OFFSET)
#define R_CANFD_CFDRMDF4_12                 (R_CANFD_BASE + R_CANFD_CFDRMDF4_12_OFFSET)
#define R_CANFD_CFDRMDF5_12                 (R_CANFD_BASE + R_CANFD_CFDRMDF5_12_OFFSET)
#define R_CANFD_CFDRMDF6_12                 (R_CANFD_BASE + R_CANFD_CFDRMDF6_12_OFFSET)
#define R_CANFD_CFDRMDF7_12                 (R_CANFD_BASE + R_CANFD_CFDRMDF7_12_OFFSET)
#define R_CANFD_CFDRMDF0_13                 (R_CANFD_BASE + R_CANFD_CFDRMDF0_13_OFFSET)
#define R_CANFD_CFDRMDF1_13                 (R_CANFD_BASE + R_CANFD_CFDRMDF1_13_OFFSET)
#define R_CANFD_CFDRMDF2_13                 (R_CANFD_BASE + R_CANFD_CFDRMDF2_13_OFFSET)
#define R_CANFD_CFDRMDF3_13                 (R_CANFD_BASE + R_CANFD_CFDRMDF3_13_OFFSET)
#define R_CANFD_CFDRMDF4_13                 (R_CANFD_BASE + R_CANFD_CFDRMDF4_13_OFFSET)
#define R_CANFD_CFDRMDF5_13                 (R_CANFD_BASE + R_CANFD_CFDRMDF5_13_OFFSET)
#define R_CANFD_CFDRMDF6_13                 (R_CANFD_BASE + R_CANFD_CFDRMDF6_13_OFFSET)
#define R_CANFD_CFDRMDF7_13                 (R_CANFD_BASE + R_CANFD_CFDRMDF7_13_OFFSET)
#define R_CANFD_CFDRMDF0_14                 (R_CANFD_BASE + R_CANFD_CFDRMDF0_14_OFFSET)
#define R_CANFD_CFDRMDF1_14                 (R_CANFD_BASE + R_CANFD_CFDRMDF1_14_OFFSET)
#define R_CANFD_CFDRMDF2_14                 (R_CANFD_BASE + R_CANFD_CFDRMDF2_14_OFFSET)
#define R_CANFD_CFDRMDF3_14                 (R_CANFD_BASE + R_CANFD_CFDRMDF3_14_OFFSET)
#define R_CANFD_CFDRMDF4_14                 (R_CANFD_BASE + R_CANFD_CFDRMDF4_14_OFFSET)
#define R_CANFD_CFDRMDF5_14                 (R_CANFD_BASE + R_CANFD_CFDRMDF5_14_OFFSET)
#define R_CANFD_CFDRMDF6_14                 (R_CANFD_BASE + R_CANFD_CFDRMDF6_14_OFFSET)
#define R_CANFD_CFDRMDF7_14                 (R_CANFD_BASE + R_CANFD_CFDRMDF7_14_OFFSET)
#define R_CANFD_CFDRMDF0_15                 (R_CANFD_BASE + R_CANFD_CFDRMDF0_15_OFFSET)
#define R_CANFD_CFDRMDF1_15                 (R_CANFD_BASE + R_CANFD_CFDRMDF1_15_OFFSET)
#define R_CANFD_CFDRMDF2_15                 (R_CANFD_BASE + R_CANFD_CFDRMDF2_15_OFFSET)
#define R_CANFD_CFDRMDF3_15                 (R_CANFD_BASE + R_CANFD_CFDRMDF3_15_OFFSET)
#define R_CANFD_CFDRMDF4_15                 (R_CANFD_BASE + R_CANFD_CFDRMDF4_15_OFFSET)
#define R_CANFD_CFDRMDF5_15                 (R_CANFD_BASE + R_CANFD_CFDRMDF5_15_OFFSET)
#define R_CANFD_CFDRMDF6_15                 (R_CANFD_BASE + R_CANFD_CFDRMDF6_15_OFFSET)
#define R_CANFD_CFDRMDF7_15                 (R_CANFD_BASE + R_CANFD_CFDRMDF7_15_OFFSET)
#define R_CANFD_CFDRMID08                 (R_CANFD_BASE + R_CANFD_CFDRMID08_OFFSET)
#define R_CANFD_CFDRMID09                 (R_CANFD_BASE + R_CANFD_CFDRMID09_OFFSET)
#define R_CANFD_CFDRMID10                 (R_CANFD_BASE + R_CANFD_CFDRMID10_OFFSET)
#define R_CANFD_CFDRMID11                 (R_CANFD_BASE + R_CANFD_CFDRMID11_OFFSET)
#define R_CANFD_CFDRMID12                 (R_CANFD_BASE + R_CANFD_CFDRMID12_OFFSET)
#define R_CANFD_CFDRMID13                 (R_CANFD_BASE + R_CANFD_CFDRMID13_OFFSET)
#define R_CANFD_CFDRMID14                 (R_CANFD_BASE + R_CANFD_CFDRMID14_OFFSET)
#define R_CANFD_CFDRMID15                 (R_CANFD_BASE + R_CANFD_CFDRMID15_OFFSET)
#define R_CANFD_CFDRMPTR08                 (R_CANFD_BASE + R_CANFD_CFDRMPTR08_OFFSET)
#define R_CANFD_CFDRMPTR09                 (R_CANFD_BASE + R_CANFD_CFDRMPTR09_OFFSET)
#define R_CANFD_CFDRMPTR10                 (R_CANFD_BASE + R_CANFD_CFDRMPTR10_OFFSET)
#define R_CANFD_CFDRMPTR11                 (R_CANFD_BASE + R_CANFD_CFDRMPTR11_OFFSET)
#define R_CANFD_CFDRMPTR12                 (R_CANFD_BASE + R_CANFD_CFDRMPTR12_OFFSET)
#define R_CANFD_CFDRMPTR13                 (R_CANFD_BASE + R_CANFD_CFDRMPTR13_OFFSET)
#define R_CANFD_CFDRMPTR14                 (R_CANFD_BASE + R_CANFD_CFDRMPTR14_OFFSET)
#define R_CANFD_CFDRMPTR15                 (R_CANFD_BASE + R_CANFD_CFDRMPTR15_OFFSET)
#define R_CANFD_CFDRMFDSTS08                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS08_OFFSET)
#define R_CANFD_CFDRMFDSTS09                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS09_OFFSET)
#define R_CANFD_CFDRMFDSTS10                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS10_OFFSET)
#define R_CANFD_CFDRMFDSTS11                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS11_OFFSET)
#define R_CANFD_CFDRMFDSTS12                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS12_OFFSET)
#define R_CANFD_CFDRMFDSTS13                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS13_OFFSET)
#define R_CANFD_CFDRMFDSTS14                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS14_OFFSET)
#define R_CANFD_CFDRMFDSTS15                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS15_OFFSET)
#define R_CANFD_CFDRMDF08_0                 (R_CANFD_BASE + R_CANFD_CFDRMDF08_0_OFFSET)
#define R_CANFD_CFDRMDF09_0                 (R_CANFD_BASE + R_CANFD_CFDRMDF09_0_OFFSET)
#define R_CANFD_CFDRMDF10_0                 (R_CANFD_BASE + R_CANFD_CFDRMDF10_0_OFFSET)
#define R_CANFD_CFDRMDF11_0                 (R_CANFD_BASE + R_CANFD_CFDRMDF11_0_OFFSET)
#define R_CANFD_CFDRMDF12_0                 (R_CANFD_BASE + R_CANFD_CFDRMDF12_0_OFFSET)
#define R_CANFD_CFDRMDF13_0                 (R_CANFD_BASE + R_CANFD_CFDRMDF13_0_OFFSET)
#define R_CANFD_CFDRMDF14_0                 (R_CANFD_BASE + R_CANFD_CFDRMDF14_0_OFFSET)
#define R_CANFD_CFDRMDF15_0                 (R_CANFD_BASE + R_CANFD_CFDRMDF15_0_OFFSET)
#define R_CANFD_CFDRMDF08_1                 (R_CANFD_BASE + R_CANFD_CFDRMDF08_1_OFFSET)
#define R_CANFD_CFDRMDF09_1                 (R_CANFD_BASE + R_CANFD_CFDRMDF09_1_OFFSET)
#define R_CANFD_CFDRMDF10_1                 (R_CANFD_BASE + R_CANFD_CFDRMDF10_1_OFFSET)
#define R_CANFD_CFDRMDF11_1                 (R_CANFD_BASE + R_CANFD_CFDRMDF11_1_OFFSET)
#define R_CANFD_CFDRMDF12_1                 (R_CANFD_BASE + R_CANFD_CFDRMDF12_1_OFFSET)
#define R_CANFD_CFDRMDF13_1                 (R_CANFD_BASE + R_CANFD_CFDRMDF13_1_OFFSET)
#define R_CANFD_CFDRMDF14_1                 (R_CANFD_BASE + R_CANFD_CFDRMDF14_1_OFFSET)
#define R_CANFD_CFDRMDF15_1                 (R_CANFD_BASE + R_CANFD_CFDRMDF15_1_OFFSET)
#define R_CANFD_CFDRMDF08_2                 (R_CANFD_BASE + R_CANFD_CFDRMDF08_2_OFFSET)
#define R_CANFD_CFDRMDF09_2                 (R_CANFD_BASE + R_CANFD_CFDRMDF09_2_OFFSET)
#define R_CANFD_CFDRMDF10_2                 (R_CANFD_BASE + R_CANFD_CFDRMDF10_2_OFFSET)
#define R_CANFD_CFDRMDF11_2                 (R_CANFD_BASE + R_CANFD_CFDRMDF11_2_OFFSET)
#define R_CANFD_CFDRMDF12_2                 (R_CANFD_BASE + R_CANFD_CFDRMDF12_2_OFFSET)
#define R_CANFD_CFDRMDF13_2                 (R_CANFD_BASE + R_CANFD_CFDRMDF13_2_OFFSET)
#define R_CANFD_CFDRMDF14_2                 (R_CANFD_BASE + R_CANFD_CFDRMDF14_2_OFFSET)
#define R_CANFD_CFDRMDF15_2                 (R_CANFD_BASE + R_CANFD_CFDRMDF15_2_OFFSET)
#define R_CANFD_CFDRMDF08_3                 (R_CANFD_BASE + R_CANFD_CFDRMDF08_3_OFFSET)
#define R_CANFD_CFDRMDF09_3                 (R_CANFD_BASE + R_CANFD_CFDRMDF09_3_OFFSET)
#define R_CANFD_CFDRMDF10_3                 (R_CANFD_BASE + R_CANFD_CFDRMDF10_3_OFFSET)
#define R_CANFD_CFDRMDF11_3                 (R_CANFD_BASE + R_CANFD_CFDRMDF11_3_OFFSET)
#define R_CANFD_CFDRMDF12_3                 (R_CANFD_BASE + R_CANFD_CFDRMDF12_3_OFFSET)
#define R_CANFD_CFDRMDF13_3                 (R_CANFD_BASE + R_CANFD_CFDRMDF13_3_OFFSET)
#define R_CANFD_CFDRMDF14_3                 (R_CANFD_BASE + R_CANFD_CFDRMDF14_3_OFFSET)
#define R_CANFD_CFDRMDF15_3                 (R_CANFD_BASE + R_CANFD_CFDRMDF15_3_OFFSET)
#define R_CANFD_CFDRMDF08_4                 (R_CANFD_BASE + R_CANFD_CFDRMDF08_4_OFFSET)
#define R_CANFD_CFDRMDF09_4                 (R_CANFD_BASE + R_CANFD_CFDRMDF09_4_OFFSET)
#define R_CANFD_CFDRMDF10_4                 (R_CANFD_BASE + R_CANFD_CFDRMDF10_4_OFFSET)
#define R_CANFD_CFDRMDF11_4                 (R_CANFD_BASE + R_CANFD_CFDRMDF11_4_OFFSET)
#define R_CANFD_CFDRMDF12_4                 (R_CANFD_BASE + R_CANFD_CFDRMDF12_4_OFFSET)
#define R_CANFD_CFDRMDF13_4                 (R_CANFD_BASE + R_CANFD_CFDRMDF13_4_OFFSET)
#define R_CANFD_CFDRMDF14_4                 (R_CANFD_BASE + R_CANFD_CFDRMDF14_4_OFFSET)
#define R_CANFD_CFDRMDF15_4                 (R_CANFD_BASE + R_CANFD_CFDRMDF15_4_OFFSET)
#define R_CANFD_CFDRMDF08_5                 (R_CANFD_BASE + R_CANFD_CFDRMDF08_5_OFFSET)
#define R_CANFD_CFDRMDF09_5                 (R_CANFD_BASE + R_CANFD_CFDRMDF09_5_OFFSET)
#define R_CANFD_CFDRMDF10_5                 (R_CANFD_BASE + R_CANFD_CFDRMDF10_5_OFFSET)
#define R_CANFD_CFDRMDF11_5                 (R_CANFD_BASE + R_CANFD_CFDRMDF11_5_OFFSET)
#define R_CANFD_CFDRMDF12_5                 (R_CANFD_BASE + R_CANFD_CFDRMDF12_5_OFFSET)
#define R_CANFD_CFDRMDF13_5                 (R_CANFD_BASE + R_CANFD_CFDRMDF13_5_OFFSET)
#define R_CANFD_CFDRMDF14_5                 (R_CANFD_BASE + R_CANFD_CFDRMDF14_5_OFFSET)
#define R_CANFD_CFDRMDF15_5                 (R_CANFD_BASE + R_CANFD_CFDRMDF15_5_OFFSET)
#define R_CANFD_CFDRMDF08_6                 (R_CANFD_BASE + R_CANFD_CFDRMDF08_6_OFFSET)
#define R_CANFD_CFDRMDF09_6                 (R_CANFD_BASE + R_CANFD_CFDRMDF09_6_OFFSET)
#define R_CANFD_CFDRMDF10_6                 (R_CANFD_BASE + R_CANFD_CFDRMDF10_6_OFFSET)
#define R_CANFD_CFDRMDF11_6                 (R_CANFD_BASE + R_CANFD_CFDRMDF11_6_OFFSET)
#define R_CANFD_CFDRMDF12_6                 (R_CANFD_BASE + R_CANFD_CFDRMDF12_6_OFFSET)
#define R_CANFD_CFDRMDF13_6                 (R_CANFD_BASE + R_CANFD_CFDRMDF13_6_OFFSET)
#define R_CANFD_CFDRMDF14_6                 (R_CANFD_BASE + R_CANFD_CFDRMDF14_6_OFFSET)
#define R_CANFD_CFDRMDF15_6                 (R_CANFD_BASE + R_CANFD_CFDRMDF15_6_OFFSET)
#define R_CANFD_CFDRMDF08_7                 (R_CANFD_BASE + R_CANFD_CFDRMDF08_7_OFFSET)
#define R_CANFD_CFDRMDF09_7                 (R_CANFD_BASE + R_CANFD_CFDRMDF09_7_OFFSET)
#define R_CANFD_CFDRMDF10_7                 (R_CANFD_BASE + R_CANFD_CFDRMDF10_7_OFFSET)
#define R_CANFD_CFDRMDF11_7                 (R_CANFD_BASE + R_CANFD_CFDRMDF11_7_OFFSET)
#define R_CANFD_CFDRMDF12_7                 (R_CANFD_BASE + R_CANFD_CFDRMDF12_7_OFFSET)
#define R_CANFD_CFDRMDF13_7                 (R_CANFD_BASE + R_CANFD_CFDRMDF13_7_OFFSET)
#define R_CANFD_CFDRMDF14_7                 (R_CANFD_BASE + R_CANFD_CFDRMDF14_7_OFFSET)
#define R_CANFD_CFDRMDF15_7                 (R_CANFD_BASE + R_CANFD_CFDRMDF15_7_OFFSET)
#define R_CANFD_CFDRMDF08_8                 (R_CANFD_BASE + R_CANFD_CFDRMDF08_8_OFFSET)
#define R_CANFD_CFDRMDF09_8                 (R_CANFD_BASE + R_CANFD_CFDRMDF09_8_OFFSET)
#define R_CANFD_CFDRMDF10_8                 (R_CANFD_BASE + R_CANFD_CFDRMDF10_8_OFFSET)
#define R_CANFD_CFDRMDF11_8                 (R_CANFD_BASE + R_CANFD_CFDRMDF11_8_OFFSET)
#define R_CANFD_CFDRMDF12_8                 (R_CANFD_BASE + R_CANFD_CFDRMDF12_8_OFFSET)
#define R_CANFD_CFDRMDF13_8                 (R_CANFD_BASE + R_CANFD_CFDRMDF13_8_OFFSET)
#define R_CANFD_CFDRMDF14_8                 (R_CANFD_BASE + R_CANFD_CFDRMDF14_8_OFFSET)
#define R_CANFD_CFDRMDF15_8                 (R_CANFD_BASE + R_CANFD_CFDRMDF15_8_OFFSET)
#define R_CANFD_CFDRMDF08_9                 (R_CANFD_BASE + R_CANFD_CFDRMDF08_9_OFFSET)
#define R_CANFD_CFDRMDF09_9                 (R_CANFD_BASE + R_CANFD_CFDRMDF09_9_OFFSET)
#define R_CANFD_CFDRMDF10_9                 (R_CANFD_BASE + R_CANFD_CFDRMDF10_9_OFFSET)
#define R_CANFD_CFDRMDF11_9                 (R_CANFD_BASE + R_CANFD_CFDRMDF11_9_OFFSET)
#define R_CANFD_CFDRMDF12_9                 (R_CANFD_BASE + R_CANFD_CFDRMDF12_9_OFFSET)
#define R_CANFD_CFDRMDF13_9                 (R_CANFD_BASE + R_CANFD_CFDRMDF13_9_OFFSET)
#define R_CANFD_CFDRMDF14_9                 (R_CANFD_BASE + R_CANFD_CFDRMDF14_9_OFFSET)
#define R_CANFD_CFDRMDF15_9                 (R_CANFD_BASE + R_CANFD_CFDRMDF15_9_OFFSET)
#define R_CANFD_CFDRMDF08_10                 (R_CANFD_BASE + R_CANFD_CFDRMDF08_10_OFFSET)
#define R_CANFD_CFDRMDF09_10                 (R_CANFD_BASE + R_CANFD_CFDRMDF09_10_OFFSET)
#define R_CANFD_CFDRMDF10_10                 (R_CANFD_BASE + R_CANFD_CFDRMDF10_10_OFFSET)
#define R_CANFD_CFDRMDF11_10                 (R_CANFD_BASE + R_CANFD_CFDRMDF11_10_OFFSET)
#define R_CANFD_CFDRMDF12_10                 (R_CANFD_BASE + R_CANFD_CFDRMDF12_10_OFFSET)
#define R_CANFD_CFDRMDF13_10                 (R_CANFD_BASE + R_CANFD_CFDRMDF13_10_OFFSET)
#define R_CANFD_CFDRMDF14_10                 (R_CANFD_BASE + R_CANFD_CFDRMDF14_10_OFFSET)
#define R_CANFD_CFDRMDF15_10                 (R_CANFD_BASE + R_CANFD_CFDRMDF15_10_OFFSET)
#define R_CANFD_CFDRMDF08_11                 (R_CANFD_BASE + R_CANFD_CFDRMDF08_11_OFFSET)
#define R_CANFD_CFDRMDF09_11                 (R_CANFD_BASE + R_CANFD_CFDRMDF09_11_OFFSET)
#define R_CANFD_CFDRMDF10_11                 (R_CANFD_BASE + R_CANFD_CFDRMDF10_11_OFFSET)
#define R_CANFD_CFDRMDF11_11                 (R_CANFD_BASE + R_CANFD_CFDRMDF11_11_OFFSET)
#define R_CANFD_CFDRMDF12_11                 (R_CANFD_BASE + R_CANFD_CFDRMDF12_11_OFFSET)
#define R_CANFD_CFDRMDF13_11                 (R_CANFD_BASE + R_CANFD_CFDRMDF13_11_OFFSET)
#define R_CANFD_CFDRMDF14_11                 (R_CANFD_BASE + R_CANFD_CFDRMDF14_11_OFFSET)
#define R_CANFD_CFDRMDF15_11                 (R_CANFD_BASE + R_CANFD_CFDRMDF15_11_OFFSET)
#define R_CANFD_CFDRMDF08_12                 (R_CANFD_BASE + R_CANFD_CFDRMDF08_12_OFFSET)
#define R_CANFD_CFDRMDF09_12                 (R_CANFD_BASE + R_CANFD_CFDRMDF09_12_OFFSET)
#define R_CANFD_CFDRMDF10_12                 (R_CANFD_BASE + R_CANFD_CFDRMDF10_12_OFFSET)
#define R_CANFD_CFDRMDF11_12                 (R_CANFD_BASE + R_CANFD_CFDRMDF11_12_OFFSET)
#define R_CANFD_CFDRMDF12_12                 (R_CANFD_BASE + R_CANFD_CFDRMDF12_12_OFFSET)
#define R_CANFD_CFDRMDF13_12                 (R_CANFD_BASE + R_CANFD_CFDRMDF13_12_OFFSET)
#define R_CANFD_CFDRMDF14_12                 (R_CANFD_BASE + R_CANFD_CFDRMDF14_12_OFFSET)
#define R_CANFD_CFDRMDF15_12                 (R_CANFD_BASE + R_CANFD_CFDRMDF15_12_OFFSET)
#define R_CANFD_CFDRMDF08_13                 (R_CANFD_BASE + R_CANFD_CFDRMDF08_13_OFFSET)
#define R_CANFD_CFDRMDF09_13                 (R_CANFD_BASE + R_CANFD_CFDRMDF09_13_OFFSET)
#define R_CANFD_CFDRMDF10_13                 (R_CANFD_BASE + R_CANFD_CFDRMDF10_13_OFFSET)
#define R_CANFD_CFDRMDF11_13                 (R_CANFD_BASE + R_CANFD_CFDRMDF11_13_OFFSET)
#define R_CANFD_CFDRMDF12_13                 (R_CANFD_BASE + R_CANFD_CFDRMDF12_13_OFFSET)
#define R_CANFD_CFDRMDF13_13                 (R_CANFD_BASE + R_CANFD_CFDRMDF13_13_OFFSET)
#define R_CANFD_CFDRMDF14_13                 (R_CANFD_BASE + R_CANFD_CFDRMDF14_13_OFFSET)
#define R_CANFD_CFDRMDF15_13                 (R_CANFD_BASE + R_CANFD_CFDRMDF15_13_OFFSET)
#define R_CANFD_CFDRMDF08_14                 (R_CANFD_BASE + R_CANFD_CFDRMDF08_14_OFFSET)
#define R_CANFD_CFDRMDF09_14                 (R_CANFD_BASE + R_CANFD_CFDRMDF09_14_OFFSET)
#define R_CANFD_CFDRMDF10_14                 (R_CANFD_BASE + R_CANFD_CFDRMDF10_14_OFFSET)
#define R_CANFD_CFDRMDF11_14                 (R_CANFD_BASE + R_CANFD_CFDRMDF11_14_OFFSET)
#define R_CANFD_CFDRMDF12_14                 (R_CANFD_BASE + R_CANFD_CFDRMDF12_14_OFFSET)
#define R_CANFD_CFDRMDF13_14                 (R_CANFD_BASE + R_CANFD_CFDRMDF13_14_OFFSET)
#define R_CANFD_CFDRMDF14_14                 (R_CANFD_BASE + R_CANFD_CFDRMDF14_14_OFFSET)
#define R_CANFD_CFDRMDF15_14                 (R_CANFD_BASE + R_CANFD_CFDRMDF15_14_OFFSET)
#define R_CANFD_CFDRMDF08_15                 (R_CANFD_BASE + R_CANFD_CFDRMDF08_15_OFFSET)
#define R_CANFD_CFDRMDF09_15                 (R_CANFD_BASE + R_CANFD_CFDRMDF09_15_OFFSET)
#define R_CANFD_CFDRMDF10_15                 (R_CANFD_BASE + R_CANFD_CFDRMDF10_15_OFFSET)
#define R_CANFD_CFDRMDF11_15                 (R_CANFD_BASE + R_CANFD_CFDRMDF11_15_OFFSET)
#define R_CANFD_CFDRMDF12_15                 (R_CANFD_BASE + R_CANFD_CFDRMDF12_15_OFFSET)
#define R_CANFD_CFDRMDF13_15                 (R_CANFD_BASE + R_CANFD_CFDRMDF13_15_OFFSET)
#define R_CANFD_CFDRMDF14_15                 (R_CANFD_BASE + R_CANFD_CFDRMDF14_15_OFFSET)
#define R_CANFD_CFDRMDF15_15                 (R_CANFD_BASE + R_CANFD_CFDRMDF15_15_OFFSET)
#define R_CANFD_CFDRMPTR16                 (R_CANFD_BASE + R_CANFD_CFDRMPTR16_OFFSET)
#define R_CANFD_CFDRMPTR17                 (R_CANFD_BASE + R_CANFD_CFDRMPTR17_OFFSET)
#define R_CANFD_CFDRMPTR18                 (R_CANFD_BASE + R_CANFD_CFDRMPTR18_OFFSET)
#define R_CANFD_CFDRMPTR19                 (R_CANFD_BASE + R_CANFD_CFDRMPTR19_OFFSET)
#define R_CANFD_CFDRMPTR20                 (R_CANFD_BASE + R_CANFD_CFDRMPTR20_OFFSET)
#define R_CANFD_CFDRMPTR21                 (R_CANFD_BASE + R_CANFD_CFDRMPTR21_OFFSET)
#define R_CANFD_CFDRMPTR22                 (R_CANFD_BASE + R_CANFD_CFDRMPTR22_OFFSET)
#define R_CANFD_CFDRMPTR23                 (R_CANFD_BASE + R_CANFD_CFDRMPTR23_OFFSET)
#define R_CANFD_CFDRMFDSTS16                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS16_OFFSET)
#define R_CANFD_CFDRMFDSTS17                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS17_OFFSET)
#define R_CANFD_CFDRMFDSTS18                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS18_OFFSET)
#define R_CANFD_CFDRMFDSTS19                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS19_OFFSET)
#define R_CANFD_CFDRMFDSTS20                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS20_OFFSET)
#define R_CANFD_CFDRMFDSTS21                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS21_OFFSET)
#define R_CANFD_CFDRMFDSTS22                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS22_OFFSET)
#define R_CANFD_CFDRMFDSTS23                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS23_OFFSET)
#define R_CANFD_CFDRMPTR24                 (R_CANFD_BASE + R_CANFD_CFDRMPTR24_OFFSET)
#define R_CANFD_CFDRMPTR25                 (R_CANFD_BASE + R_CANFD_CFDRMPTR25_OFFSET)
#define R_CANFD_CFDRMPTR26                 (R_CANFD_BASE + R_CANFD_CFDRMPTR26_OFFSET)
#define R_CANFD_CFDRMPTR27                 (R_CANFD_BASE + R_CANFD_CFDRMPTR27_OFFSET)
#define R_CANFD_CFDRMPTR28                 (R_CANFD_BASE + R_CANFD_CFDRMPTR28_OFFSET)
#define R_CANFD_CFDRMPTR29                 (R_CANFD_BASE + R_CANFD_CFDRMPTR29_OFFSET)
#define R_CANFD_CFDRMPTR30                 (R_CANFD_BASE + R_CANFD_CFDRMPTR30_OFFSET)
#define R_CANFD_CFDRMPTR31                 (R_CANFD_BASE + R_CANFD_CFDRMPTR31_OFFSET)
#define R_CANFD_CFDRMFDSTS24                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS24_OFFSET)
#define R_CANFD_CFDRMFDSTS25                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS25_OFFSET)
#define R_CANFD_CFDRMFDSTS26                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS26_OFFSET)
#define R_CANFD_CFDRMFDSTS27                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS27_OFFSET)
#define R_CANFD_CFDRMFDSTS28                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS28_OFFSET)
#define R_CANFD_CFDRMFDSTS29                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS29_OFFSET)
#define R_CANFD_CFDRMFDSTS30                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS30_OFFSET)
#define R_CANFD_CFDRMFDSTS31                 (R_CANFD_BASE + R_CANFD_CFDRMFDSTS31_OFFSET)

/* Register bit definitions */
/* CFDC0NCFG Register bit definitions */
#define R_CANFD_CFDC0NCFG_NBRP_SHIFT              (0)  /* Channel Nominal Baud Rate Prescaler */
#define R_CANFD_CFDC0NCFG_NBRP_MASK               0x3ff

#define R_CANFD_CFDC0NCFG_NSJW_SHIFT              (10)  /* Resynchronization Jump Width */
#define R_CANFD_CFDC0NCFG_NSJW_MASK               0x1fc00

#define R_CANFD_CFDC0NCFG_NTSEG1_SHIFT            (17)  /* Timing Segment 1 */
#define R_CANFD_CFDC0NCFG_NTSEG1_MASK             0x1fe0000

#define R_CANFD_CFDC0NCFG_NTSEG2_SHIFT            (25)  /* Timing Segment 2 */
#define R_CANFD_CFDC0NCFG_NTSEG2_MASK             0xfe000000

/* CFDC0CTR Register bit definitions */
#define R_CANFD_CFDC0CTR_CHMDC_SHIFT              (0)  /* Channel Mode Control */
#define R_CANFD_CFDC0CTR_CHMDC_MASK               0x3
#  define R_CANFD_CFDC0CTR_CHMDC_00                       (0 << R_CANFD_CFDC0CTR_CHMDC_SHIFT)  /* Channel operation mode request */
#  define R_CANFD_CFDC0CTR_CHMDC_01                       (1 << R_CANFD_CFDC0CTR_CHMDC_SHIFT)  /* Channel reset request */
#  define R_CANFD_CFDC0CTR_CHMDC_10                       (2 << R_CANFD_CFDC0CTR_CHMDC_SHIFT)  /* Channel halt request */
#  define R_CANFD_CFDC0CTR_CHMDC_11                       (3 << R_CANFD_CFDC0CTR_CHMDC_SHIFT)  /* Keep current value */

#define R_CANFD_CFDC0CTR_CSLPR                    (1 << 2)  /* Channel Sleep Request */

#define R_CANFD_CFDC0CTR_RTBO                     (1 << 3)  /* Return from Bus-Off */

#define R_CANFD_CFDC0CTR_BEIE                     (1 << 8)  /* Bus Error Interrupt Enable */

#define R_CANFD_CFDC0CTR_EWIE                     (1 << 9)  /* Error Warning Interrupt Enable */

#define R_CANFD_CFDC0CTR_EPIE                     (1 << 10)  /* Error Passive Interrupt Enable */

#define R_CANFD_CFDC0CTR_BOEIE                    (1 << 11)  /* Bus-Off Entry Interrupt Enable */

#define R_CANFD_CFDC0CTR_BORIE                    (1 << 12)  /* Bus-Off Recovery Interrupt Enable */

#define R_CANFD_CFDC0CTR_OLIE                     (1 << 13)  /* Overload Interrupt Enable */

#define R_CANFD_CFDC0CTR_BLIE                     (1 << 14)  /* Bus Lock Interrupt Enable */

#define R_CANFD_CFDC0CTR_ALIE                     (1 << 15)  /* Arbitration Lost Interrupt Enable */

#define R_CANFD_CFDC0CTR_TAIE                     (1 << 16)  /* Transmission Abort Interrupt Enable */

#define R_CANFD_CFDC0CTR_EOCOIE                   (1 << 17)  /* Error Occurrence Counter Overflow Interrupt Enable */

#define R_CANFD_CFDC0CTR_SOCOIE                   (1 << 18)  /* Successful Occurrence Counter Overflow Interrupt Enable */

#define R_CANFD_CFDC0CTR_TDCVFIE                  (1 << 19)  /* Transceiver Delay Compensation Violation Interrupt Enable */

#define R_CANFD_CFDC0CTR_BOM_SHIFT                (21)  /* Channel Bus-Off Mode */
#define R_CANFD_CFDC0CTR_BOM_MASK                 0x600000
#  define R_CANFD_CFDC0CTR_BOM_00                         (0 << R_CANFD_CFDC0CTR_BOM_SHIFT)  /* Normal mode (comply with ISO 11898-1) */
#  define R_CANFD_CFDC0CTR_BOM_01                         (1 << R_CANFD_CFDC0CTR_BOM_SHIFT)  /* Entry to Halt mode automatically at bus-off start */
#  define R_CANFD_CFDC0CTR_BOM_10                         (2 << R_CANFD_CFDC0CTR_BOM_SHIFT)  /* Entry to Halt mode automatically at bus-off end */
#  define R_CANFD_CFDC0CTR_BOM_11                         (3 << R_CANFD_CFDC0CTR_BOM_SHIFT)  /* Entry to Halt mode (during bus-off recovery period) by software */

#define R_CANFD_CFDC0CTR_ERRD                     (1 << 23)  /* Channel Error Display */

#define R_CANFD_CFDC0CTR_CTME                     (1 << 24)  /* Channel Test Mode Enable */

#define R_CANFD_CFDC0CTR_CTMS_SHIFT               (25)  /* Channel Test Mode Select */
#define R_CANFD_CFDC0CTR_CTMS_MASK                0x6000000
#  define R_CANFD_CFDC0CTR_CTMS_00                        (0 << R_CANFD_CFDC0CTR_CTMS_SHIFT)  /* Basic test mode */
#  define R_CANFD_CFDC0CTR_CTMS_01                        (1 << R_CANFD_CFDC0CTR_CTMS_SHIFT)  /* Listen-only mode */
#  define R_CANFD_CFDC0CTR_CTMS_10                        (2 << R_CANFD_CFDC0CTR_CTMS_SHIFT)  /* Self-test mode 0 (External loopback mode) */
#  define R_CANFD_CFDC0CTR_CTMS_11                        (3 << R_CANFD_CFDC0CTR_CTMS_SHIFT)  /* Self-test mode 1 (Internal loopback mode) */

#define R_CANFD_CFDC0CTR_BFT                      (1 << 30)  /* Bit Flip Test */

#define R_CANFD_CFDC0CTR_ROM                      (1 << 31)  /* Restricted Operation Mode */

/* CFDC0STS Register bit definitions */
#define R_CANFD_CFDC0STS_CRSTSTS                  (1 << 0)  /* Channel Reset Status */

#define R_CANFD_CFDC0STS_CHLTSTS                  (1 << 1)  /* Channel Halt Status */

#define R_CANFD_CFDC0STS_CSLPSTS                  (1 << 2)  /* Channel Sleep Status */

#define R_CANFD_CFDC0STS_EPSTS                    (1 << 3)  /* Channel Error Passive Status */

#define R_CANFD_CFDC0STS_BOSTS                    (1 << 4)  /* Channel Bus-Off Status */

#define R_CANFD_CFDC0STS_TRMSTS                   (1 << 5)  /* Channel Transmit Status */

#define R_CANFD_CFDC0STS_RECSTS                   (1 << 6)  /* Channel Receive Status */

#define R_CANFD_CFDC0STS_COMSTS                   (1 << 7)  /* Channel Communication Status */

#define R_CANFD_CFDC0STS_ESIF                     (1 << 8)  /* Error State Indication Flag */

#define R_CANFD_CFDC0STS_REC_SHIFT                (16)  /* Reception Error Count */
#define R_CANFD_CFDC0STS_REC_MASK                 0xff0000

#define R_CANFD_CFDC0STS_TEC_SHIFT                (24)  /* Transmission Error Count */
#define R_CANFD_CFDC0STS_TEC_MASK                 0xff000000

/* CFDC0ERFL Register bit definitions */
#define R_CANFD_CFDC0ERFL_BEF                     (1 << 0)  /* Bus Error Flag */

#define R_CANFD_CFDC0ERFL_EWF                     (1 << 1)  /* Error Warning Flag */

#define R_CANFD_CFDC0ERFL_EPF                     (1 << 2)  /* Error Passive Flag */

#define R_CANFD_CFDC0ERFL_BOEF                    (1 << 3)  /* Bus-Off Entry Flag */

#define R_CANFD_CFDC0ERFL_BORF                    (1 << 4)  /* Bus-Off Recovery Flag */

#define R_CANFD_CFDC0ERFL_OVLF                    (1 << 5)  /* Overload Flag */

#define R_CANFD_CFDC0ERFL_BLF                     (1 << 6)  /* Bus Lock Flag */

#define R_CANFD_CFDC0ERFL_ALF                     (1 << 7)  /* Arbitration Lost Flag */

#define R_CANFD_CFDC0ERFL_SERR                    (1 << 8)  /* Stuff Error */

#define R_CANFD_CFDC0ERFL_FERR                    (1 << 9)  /* Form Error */

#define R_CANFD_CFDC0ERFL_AERR                    (1 << 10)  /* Acknowledge Error */

#define R_CANFD_CFDC0ERFL_CERR                    (1 << 11)  /* CRC Error */

#define R_CANFD_CFDC0ERFL_B1ERR                   (1 << 12)  /* Bit 1 Error */

#define R_CANFD_CFDC0ERFL_B0ERR                   (1 << 13)  /* Bit 0 Error */

#define R_CANFD_CFDC0ERFL_ADERR                   (1 << 14)  /* Acknowledge Delimiter Error */

#define R_CANFD_CFDC0ERFL_CRCREG_SHIFT            (16)  /* CRC Register value */
#define R_CANFD_CFDC0ERFL_CRCREG_MASK             0x7fff0000

/* CFDGCFG Register bit definitions */
#define R_CANFD_CFDGCFG_TPRI                      (1 << 0)  /* Transmission Priority */

#define R_CANFD_CFDGCFG_DCE                       (1 << 1)  /* DLC Check Enable */

#define R_CANFD_CFDGCFG_DRE                       (1 << 2)  /* DLC Replacement Enable */

#define R_CANFD_CFDGCFG_MME                       (1 << 3)  /* Mirror Mode Enable */

#define R_CANFD_CFDGCFG_DCS                       (1 << 4)  /* Data Link Controller Clock Select */

#define R_CANFD_CFDGCFG_CMPOC                     (1 << 5)  /* CANFD Message Payload Overflow Configuration */

#define R_CANFD_CFDGCFG_TSP_SHIFT                 (8)  /* Timestamp Prescaler */
#define R_CANFD_CFDGCFG_TSP_MASK                  0xf00

#define R_CANFD_CFDGCFG_TSSS                      (1 << 12)  /* Timestamp Source Select */

#define R_CANFD_CFDGCFG_ITRCP_SHIFT               (16)  /* Interval Timer Reference Clock Prescaler */
#define R_CANFD_CFDGCFG_ITRCP_MASK                0xffff0000

/* CFDGCTR Register bit definitions */
#define R_CANFD_CFDGCTR_GMDC_SHIFT                (0)  /* Global Mode Control */
#define R_CANFD_CFDGCTR_GMDC_MASK                 0x3
#  define R_CANFD_CFDGCTR_GMDC_00                         (0 << R_CANFD_CFDGCTR_GMDC_SHIFT)  /* Global operation mode request */
#  define R_CANFD_CFDGCTR_GMDC_01                         (1 << R_CANFD_CFDGCTR_GMDC_SHIFT)  /* Global reset mode request */
#  define R_CANFD_CFDGCTR_GMDC_10                         (2 << R_CANFD_CFDGCTR_GMDC_SHIFT)  /* Global halt mode request */
#  define R_CANFD_CFDGCTR_GMDC_11                         (3 << R_CANFD_CFDGCTR_GMDC_SHIFT)  /* Keep current value */

#define R_CANFD_CFDGCTR_GSLPR                     (1 << 2)  /* Global Sleep Request */

#define R_CANFD_CFDGCTR_DEIE                      (1 << 8)  /* DLC Check Interrupt Enable */

#define R_CANFD_CFDGCTR_MEIE                      (1 << 9)  /* Message Lost Error Interrupt Enable */

#define R_CANFD_CFDGCTR_THLEIE                    (1 << 10)  /* TX History List Entry Lost Interrupt Enable */

#define R_CANFD_CFDGCTR_CMPOFIE                   (1 << 11)  /* CANFD Message Payload Overflow Flag Interrupt Enable */

#define R_CANFD_CFDGCTR_TSRST                     (1 << 16)  /* Timestamp Reset */

/* CFDGSTS Register bit definitions */
#define R_CANFD_CFDGSTS_GRSTSTS                   (1 << 0)  /* Global Reset Status */

#define R_CANFD_CFDGSTS_GHLTSTS                   (1 << 1)  /* Global Halt Status */

#define R_CANFD_CFDGSTS_GSLPSTS                   (1 << 2)  /* Global Sleep Status */

#define R_CANFD_CFDGSTS_GRAMINIT                  (1 << 3)  /* Global RAM Initialization */

/* CFDGERFL Register bit definitions */
#define R_CANFD_CFDGERFL_DEF                      (1 << 0)  /* DLC Error Flag */

#define R_CANFD_CFDGERFL_MES                      (1 << 1)  /* Message Lost Error Status */

#define R_CANFD_CFDGERFL_THLES                    (1 << 2)  /* TX History List Entry Lost Error Status */

#define R_CANFD_CFDGERFL_CMPOF                    (1 << 3)  /* CANFD Message Payload Overflow Flag */

#define R_CANFD_CFDGERFL_EEF0                     (1 << 16)  /* ECC Error Flag */

/* CFDGTSC Register bit definitions */
#define R_CANFD_CFDGTSC_TS_SHIFT                  (0)  /* Timestamp value */
#define R_CANFD_CFDGTSC_TS_MASK                   0xffff

/* CFDGAFLECTR Register bit definitions */
#define R_CANFD_CFDGAFLECTR_AFLDAE                (1 << 8)  /* Acceptance Filter List Data Access Enable */

#define R_CANFD_CFDGAFLECTR_AFLPN_SHIFT           (0)  /* Acceptance Filter List Page Number */
#define R_CANFD_CFDGAFLECTR_AFLPN_MASK            0xf

/* CFDGAFLCFG Register bit definitions */
#define R_CANFD_CFDGAFLCFG_RNC0_SHIFT             (16)  /* Rule Number */
#define R_CANFD_CFDGAFLCFG_RNC0_MASK              0x1f0000

/* CFDRMNB Register bit definitions */
#define R_CANFD_CFDRMNB_NRXMB_SHIFT               (0)  /* Number of RX Message Buffers */
#define R_CANFD_CFDRMNB_NRXMB_MASK                0xff

#define R_CANFD_CFDRMNB_RMPLS_SHIFT               (8)  /* Reception Message Buffer Payload Data Size */
#define R_CANFD_CFDRMNB_RMPLS_MASK                0x700
#  define R_CANFD_CFDRMNB_RMPLS_000                       (0 << R_CANFD_CFDRMNB_RMPLS_SHIFT)  /* 8 bytes */
#  define R_CANFD_CFDRMNB_RMPLS_001                       (1 << R_CANFD_CFDRMNB_RMPLS_SHIFT)  /* 12 bytes */
#  define R_CANFD_CFDRMNB_RMPLS_010                       (2 << R_CANFD_CFDRMNB_RMPLS_SHIFT)  /* 16 bytes */
#  define R_CANFD_CFDRMNB_RMPLS_011                       (3 << R_CANFD_CFDRMNB_RMPLS_SHIFT)  /* 20 bytes */
#  define R_CANFD_CFDRMNB_RMPLS_100                       (4 << R_CANFD_CFDRMNB_RMPLS_SHIFT)  /* 24 bytes */
#  define R_CANFD_CFDRMNB_RMPLS_101                       (5 << R_CANFD_CFDRMNB_RMPLS_SHIFT)  /* 32 bytes */
#  define R_CANFD_CFDRMNB_RMPLS_110                       (6 << R_CANFD_CFDRMNB_RMPLS_SHIFT)  /* 48 bytes */
#  define R_CANFD_CFDRMNB_RMPLS_111                       (7 << R_CANFD_CFDRMNB_RMPLS_SHIFT)  /* 64 bytes */

/* CFDRMND Register bit definitions */
#define R_CANFD_CFDRMND_RMNS_SHIFT                (0)  /* RX Message Buffer New Data Status */
#define R_CANFD_CFDRMND_RMNS_MASK                 0xffff
#  define R_CANFD_CFDRMND_RMNS_0                          (0 << R_CANFD_CFDRMND_RMNS_SHIFT)  /* New data not stored in corresponding RX message buffer */
#  define R_CANFD_CFDRMND_RMNS_1                          (1 << R_CANFD_CFDRMND_RMNS_SHIFT)  /* New data stored in corresponding RX message buffer */

/* CFDRMIEC Register bit definitions */
#define R_CANFD_CFDRMIEC_RMIE_SHIFT               (0)  /* RX Message Buffer Interrupt Enable */
#define R_CANFD_CFDRMIEC_RMIE_MASK                0xffffffff
#  define R_CANFD_CFDRMIEC_RMIE_0                         (0 << R_CANFD_CFDRMIEC_RMIE_SHIFT)  /* RX Message Buffer Interrupt disabled for corresponding RX message buffer */
#  define R_CANFD_CFDRMIEC_RMIE_1                         (1 << R_CANFD_CFDRMIEC_RMIE_SHIFT)  /* RX Message Buffer Interrupt enabled for corresponding RX message buffer */

/* CFDRFCC Register bit definitions */
#define R_CANFD_CFDRFCC_RFE                       (1 << 0)  /* RX FIFO Enable */

#define R_CANFD_CFDRFCC_RFIE                      (1 << 1)  /* RX FIFO Interrupt Enable */

#define R_CANFD_CFDRFCC_RFPLS_SHIFT               (4)  /* Rx FIFO Payload Data Size Configuration */
#define R_CANFD_CFDRFCC_RFPLS_MASK                0x70
#  define R_CANFD_CFDRFCC_RFPLS_000                       (0 << R_CANFD_CFDRFCC_RFPLS_SHIFT)  /* 8 bytes */
#  define R_CANFD_CFDRFCC_RFPLS_001                       (1 << R_CANFD_CFDRFCC_RFPLS_SHIFT)  /* 12 bytes */
#  define R_CANFD_CFDRFCC_RFPLS_010                       (2 << R_CANFD_CFDRFCC_RFPLS_SHIFT)  /* 16 bytes */
#  define R_CANFD_CFDRFCC_RFPLS_011                       (3 << R_CANFD_CFDRFCC_RFPLS_SHIFT)  /* 20 bytes */
#  define R_CANFD_CFDRFCC_RFPLS_100                       (4 << R_CANFD_CFDRFCC_RFPLS_SHIFT)  /* 24 bytes */
#  define R_CANFD_CFDRFCC_RFPLS_101                       (5 << R_CANFD_CFDRFCC_RFPLS_SHIFT)  /* 32 bytes */
#  define R_CANFD_CFDRFCC_RFPLS_110                       (6 << R_CANFD_CFDRFCC_RFPLS_SHIFT)  /* 48 bytes */
#  define R_CANFD_CFDRFCC_RFPLS_111                       (7 << R_CANFD_CFDRFCC_RFPLS_SHIFT)  /* 64 bytes */

#define R_CANFD_CFDRFCC_RFDC_SHIFT                (8)  /* RX FIFO Depth Configuration */
#define R_CANFD_CFDRFCC_RFDC_MASK                 0x700
#  define R_CANFD_CFDRFCC_RFDC_000                        (0 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* FIFO Depth = 0 message */
#  define R_CANFD_CFDRFCC_RFDC_001                        (1 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* FIFO Depth = 4 messages */
#  define R_CANFD_CFDRFCC_RFDC_010                        (2 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* FIFO Depth = 8 messages */
#  define R_CANFD_CFDRFCC_RFDC_011                        (3 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* FIFO Depth = 16 messages */
#  define R_CANFD_CFDRFCC_RFDC_100                        (4 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* FIFO Depth = 32 messages */
#  define R_CANFD_CFDRFCC_RFDC_101                        (5 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* FIFO Depth = 48 messages */
#  define R_CANFD_CFDRFCC_RFDC_110                        (6 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* Reserved */
#  define R_CANFD_CFDRFCC_RFDC_111                        (7 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* Reserved */

#define R_CANFD_CFDRFCC_RFIM                      (1 << 12)  /* RX FIFO Interrupt Mode */

#define R_CANFD_CFDRFCC_RFIGCV_SHIFT              (13)  /* RX FIFO Interrupt Generation Counter Value */
#define R_CANFD_CFDRFCC_RFIGCV_MASK               0xe000
#  define R_CANFD_CFDRFCC_RFIGCV_000                      (0 << R_CANFD_CFDRFCC_RFIGCV_SHIFT)  /* Interrupt generated when FIFO is 1/8th full */
#  define R_CANFD_CFDRFCC_RFIGCV_001                      (1 << R_CANFD_CFDRFCC_RFIGCV_SHIFT)  /* Interrupt generated when FIFO is 1/4th full */
#  define R_CANFD_CFDRFCC_RFIGCV_010                      (2 << R_CANFD_CFDRFCC_RFIGCV_SHIFT)  /* Interrupt generated when FIFO is 3/8th full */
#  define R_CANFD_CFDRFCC_RFIGCV_011                      (3 << R_CANFD_CFDRFCC_RFIGCV_SHIFT)  /* Interrupt generated when FIFO is 1/2 full */
#  define R_CANFD_CFDRFCC_RFIGCV_100                      (4 << R_CANFD_CFDRFCC_RFIGCV_SHIFT)  /* Interrupt generated when FIFO is 5/8th full */
#  define R_CANFD_CFDRFCC_RFIGCV_101                      (5 << R_CANFD_CFDRFCC_RFIGCV_SHIFT)  /* Interrupt generated when FIFO is 3/4th full */
#  define R_CANFD_CFDRFCC_RFIGCV_110                      (6 << R_CANFD_CFDRFCC_RFIGCV_SHIFT)  /* Interrupt generated when FIFO is 7/8th full */
#  define R_CANFD_CFDRFCC_RFIGCV_111                      (7 << R_CANFD_CFDRFCC_RFIGCV_SHIFT)  /* Interrupt generated when FIFO is full */

/* CFDRFSTS Register bit definitions */
#define R_CANFD_CFDRFSTS_RFEMP                    (1 << 0)  /* RX FIFO Empty */

#define R_CANFD_CFDRFSTS_RFFLL                    (1 << 1)  /* RX FIFO Full */

#define R_CANFD_CFDRFSTS_RFMLT                    (1 << 2)  /* RX FIFO Message Lost */

#define R_CANFD_CFDRFSTS_RFIF                     (1 << 3)  /* RX FIFO Interrupt Flag */

#define R_CANFD_CFDRFSTS_RFMC_SHIFT               (8)  /* RX FIFO Message Count */
#define R_CANFD_CFDRFSTS_RFMC_MASK                0x3f00

/* CFDRFPCTR Register bit definitions */
#define R_CANFD_CFDRFPCTR_RFPC_SHIFT              (0)  /* RX FIFO Pointer Control */
#define R_CANFD_CFDRFPCTR_RFPC_MASK               0xff

/* CFDCFCC Register bit definitions */
#define R_CANFD_CFDCFCC_CFE                       (1 << 0)  /* Common FIFO Enable */

#define R_CANFD_CFDCFCC_CFRXIE                    (1 << 1)  /* Common FIFO RX Interrupt Enable */

#define R_CANFD_CFDCFCC_CFTXIE                    (1 << 2)  /* Common FIFO TX Interrupt Enable */

#define R_CANFD_CFDCFCC_CFPLS_SHIFT               (4)  /* Common FIFO Payload Data Size Configuration */
#define R_CANFD_CFDCFCC_CFPLS_MASK                0x70
#  define R_CANFD_CFDCFCC_CFPLS_000                       (0 << R_CANFD_CFDCFCC_CFPLS_SHIFT)  /* 8 bytes */
#  define R_CANFD_CFDCFCC_CFPLS_001                       (1 << R_CANFD_CFDCFCC_CFPLS_SHIFT)  /* 12 bytes */
#  define R_CANFD_CFDCFCC_CFPLS_010                       (2 << R_CANFD_CFDCFCC_CFPLS_SHIFT)  /* 16 bytes */
#  define R_CANFD_CFDCFCC_CFPLS_011                       (3 << R_CANFD_CFDCFCC_CFPLS_SHIFT)  /* 20 bytes */
#  define R_CANFD_CFDCFCC_CFPLS_100                       (4 << R_CANFD_CFDCFCC_CFPLS_SHIFT)  /* 24 bytes */
#  define R_CANFD_CFDCFCC_CFPLS_101                       (5 << R_CANFD_CFDCFCC_CFPLS_SHIFT)  /* 32 bytes */
#  define R_CANFD_CFDCFCC_CFPLS_110                       (6 << R_CANFD_CFDCFCC_CFPLS_SHIFT)  /* 48 bytes */
#  define R_CANFD_CFDCFCC_CFPLS_111                       (7 << R_CANFD_CFDCFCC_CFPLS_SHIFT)  /* 64 bytes */

#define R_CANFD_CFDCFCC_CFM                       (1 << 8)  /* Common FIFO Mode */

#define R_CANFD_CFDCFCC_CFITSS                    (1 << 10)  /* Common FIFO Interval Timer Source Select */

#define R_CANFD_CFDCFCC_CFITR                     (1 << 11)  /* Common FIFO Interval Timer Resolution */

#define R_CANFD_CFDCFCC_CFIM                      (1 << 12)  /* Common FIFO Interrupt Mode */

#define R_CANFD_CFDCFCC_CFIGCV_SHIFT              (13)  /* Common FIFO Interrupt Generation Counter Value */
#define R_CANFD_CFDCFCC_CFIGCV_MASK               0xe000
#  define R_CANFD_CFDCFCC_CFIGCV_000                      (0 << R_CANFD_CFDCFCC_CFIGCV_SHIFT)  /* Interrupt generated when FIFO is 1/8th full */
#  define R_CANFD_CFDCFCC_CFIGCV_001                      (1 << R_CANFD_CFDCFCC_CFIGCV_SHIFT)  /* Interrupt generated when FIFO is 1/4th full */
#  define R_CANFD_CFDCFCC_CFIGCV_010                      (2 << R_CANFD_CFDCFCC_CFIGCV_SHIFT)  /* Interrupt generated when FIFO is 3/8th full */
#  define R_CANFD_CFDCFCC_CFIGCV_011                      (3 << R_CANFD_CFDCFCC_CFIGCV_SHIFT)  /* Interrupt generated when FIFO is 1/2 full */
#  define R_CANFD_CFDCFCC_CFIGCV_100                      (4 << R_CANFD_CFDCFCC_CFIGCV_SHIFT)  /* Interrupt generated when FIFO is 5/8th full */
#  define R_CANFD_CFDCFCC_CFIGCV_101                      (5 << R_CANFD_CFDCFCC_CFIGCV_SHIFT)  /* Interrupt generated when FIFO is 3/4th full */
#  define R_CANFD_CFDCFCC_CFIGCV_110                      (6 << R_CANFD_CFDCFCC_CFIGCV_SHIFT)  /* Interrupt generated when FIFO is 7/8th full */
#  define R_CANFD_CFDCFCC_CFIGCV_111                      (7 << R_CANFD_CFDCFCC_CFIGCV_SHIFT)  /* Interrupt generated when FIFO is full */

#define R_CANFD_CFDCFCC_CFTML_SHIFT               (16)  /* Common FIFO TX Message Buffer Link */
#define R_CANFD_CFDCFCC_CFTML_MASK                0x30000

#define R_CANFD_CFDCFCC_CFDC_SHIFT                (21)  /* Common FIFO Depth Configuration */
#define R_CANFD_CFDCFCC_CFDC_MASK                 0xe00000
#  define R_CANFD_CFDCFCC_CFDC_000                        (0 << R_CANFD_CFDCFCC_CFDC_SHIFT)  /* FIFO Depth = 0 message */
#  define R_CANFD_CFDCFCC_CFDC_001                        (1 << R_CANFD_CFDCFCC_CFDC_SHIFT)  /* FIFO Depth = 4 messages */
#  define R_CANFD_CFDCFCC_CFDC_010                        (2 << R_CANFD_CFDCFCC_CFDC_SHIFT)  /* FIFO Depth = 8 messages */
#  define R_CANFD_CFDCFCC_CFDC_011                        (3 << R_CANFD_CFDCFCC_CFDC_SHIFT)  /* FIFO Depth = 16 messages */
#  define R_CANFD_CFDCFCC_CFDC_100                        (4 << R_CANFD_CFDCFCC_CFDC_SHIFT)  /* FIFO Depth = 32 messages */
#  define R_CANFD_CFDCFCC_CFDC_101                        (5 << R_CANFD_CFDCFCC_CFDC_SHIFT)  /* FIFO Depth = 48 messages */
#  define R_CANFD_CFDCFCC_CFDC_110                        (6 << R_CANFD_CFDCFCC_CFDC_SHIFT)  /* FIFO Depth = Reserved */
#  define R_CANFD_CFDCFCC_CFDC_111                        (7 << R_CANFD_CFDCFCC_CFDC_SHIFT)  /* FIFO Depth = Reserved */

#define R_CANFD_CFDCFCC_CFITT_SHIFT               (24)  /* Common FIFO Interval Transmission Time */
#define R_CANFD_CFDCFCC_CFITT_MASK                0xff000000

/* CFDCFSTS Register bit definitions */
#define R_CANFD_CFDCFSTS_CFEMP                    (1 << 0)  /* Common FIFO Empty */

#define R_CANFD_CFDCFSTS_CFFLL                    (1 << 1)  /* Common FIFO Full */

#define R_CANFD_CFDCFSTS_CFMLT                    (1 << 2)  /* Common FIFO Message Lost */

#define R_CANFD_CFDCFSTS_CFRXIF                   (1 << 3)  /* Common RX FIFO Interrupt Flag */

#define R_CANFD_CFDCFSTS_CFTXIF                   (1 << 4)  /* Common TX FIFO Interrupt Flag */

#define R_CANFD_CFDCFSTS_CFMC_SHIFT               (8)  /* Common FIFO Message Count */
#define R_CANFD_CFDCFSTS_CFMC_MASK                0x3f00

/* CFDCFPCTR Register bit definitions */
#define R_CANFD_CFDCFPCTR_CFPC_SHIFT              (0)  /* Common FIFO Pointer Control */
#define R_CANFD_CFDCFPCTR_CFPC_MASK               0xff

/* CFDFESTS Register bit definitions */
#define R_CANFD_CFDFESTS_RFXEMP_SHIFT             (0)  /* RX FIFO Empty Status */
#define R_CANFD_CFDFESTS_RFXEMP_MASK              0x3
#  define R_CANFD_CFDFESTS_RFXEMP_0                       (0 << R_CANFD_CFDFESTS_RFXEMP_SHIFT)  /* Corresponding FIFO not empty */
#  define R_CANFD_CFDFESTS_RFXEMP_1                       (1 << R_CANFD_CFDFESTS_RFXEMP_SHIFT)  /* Corresponding FIFO empty */

#define R_CANFD_CFDFESTS_CFEMP                    (1 << 8)  /* Common FIFO Empty Status */

#define R_CANFD_CFDFESTS_CFXEMP                   (1 << 8)  /* Common FIF0 Empty Status */

/* CFDFFSTS Register bit definitions */
#define R_CANFD_CFDFFSTS_RFXFLL_SHIFT             (0)  /* RX FIF0 Full Status */
#define R_CANFD_CFDFFSTS_RFXFLL_MASK              0x3
#  define R_CANFD_CFDFFSTS_RFXFLL_0                       (0 << R_CANFD_CFDFFSTS_RFXFLL_SHIFT)  /* Corresponding FIFO not full */
#  define R_CANFD_CFDFFSTS_RFXFLL_1                       (1 << R_CANFD_CFDFFSTS_RFXFLL_SHIFT)  /* Corresponding FIFO full */

#define R_CANFD_CFDFFSTS_CFFLL                    (1 << 8)  /* Common FIF0 Full Status */

#define R_CANFD_CFDFFSTS_CFXFLL                   (1 << 8)  /* Common FIF0 Full Status */

/* CFDFMSTS Register bit definitions */
#define R_CANFD_CFDFMSTS_RFXMLT_SHIFT             (0)  /* RX FIFO Message Lost Status */
#define R_CANFD_CFDFMSTS_RFXMLT_MASK              0x3
#  define R_CANFD_CFDFMSTS_RFXMLT_0                       (0 << R_CANFD_CFDFMSTS_RFXMLT_SHIFT)  /* Corresponding FIFO Message Lost flag not set */
#  define R_CANFD_CFDFMSTS_RFXMLT_1                       (1 << R_CANFD_CFDFMSTS_RFXMLT_SHIFT)  /* Corresponding FIFO Message Lost flag set */

#define R_CANFD_CFDFMSTS_CFMLT                    (1 << 8)  /* Common FIFO Message Lost Status */

#define R_CANFD_CFDFMSTS_CFXMLT                   (1 << 8)  /* Common FIFO Msg Lost Status */

/* CFDRFISTS Register bit definitions */
#define R_CANFD_CFDRFISTS_RFXIF_SHIFT             (0)  /* RX FIFO[x] Interrupt Flag Status */
#define R_CANFD_CFDRFISTS_RFXIF_MASK              0x3
#  define R_CANFD_CFDRFISTS_RFXIF_0                       (0 << R_CANFD_CFDRFISTS_RFXIF_SHIFT)  /* Corresponding RX FIFO Interrupt flag not set */
#  define R_CANFD_CFDRFISTS_RFXIF_1                       (1 << R_CANFD_CFDRFISTS_RFXIF_SHIFT)  /* Corresponding RX FIFO Interrupt flag set */

/* CFDTMC Register bit definitions */
#define R_CANFD_CFDTMC_TMTR                       (1 << 0)  /* TX Message Buffer Transmission Request */

#define R_CANFD_CFDTMC_TMTAR                      (1 << 1)  /* TX Message Buffer Transmission Abort Request */

#define R_CANFD_CFDTMC_TMOM                       (1 << 2)  /* TX Message Buffer One-shot Mode */

/* CFDTMSTS Register bit definitions */
#define R_CANFD_CFDTMSTS_TMTSTS                   (1 << 0)  /* TX Message Buffer Transmission Status */

#define R_CANFD_CFDTMSTS_TMTRF_SHIFT              (1)  /* TX Message Buffer Transmission Result Flag */
#define R_CANFD_CFDTMSTS_TMTRF_MASK               0x6
#  define R_CANFD_CFDTMSTS_TMTRF_00                       (0 << R_CANFD_CFDTMSTS_TMTRF_SHIFT)  /* No result */
#  define R_CANFD_CFDTMSTS_TMTRF_01                       (1 << R_CANFD_CFDTMSTS_TMTRF_SHIFT)  /* Transmission aborted from the TX message buffer */
#  define R_CANFD_CFDTMSTS_TMTRF_10                       (2 << R_CANFD_CFDTMSTS_TMTRF_SHIFT)  /* Transmission successful from the TX message buffer and transmission abort was not requested */
#  define R_CANFD_CFDTMSTS_TMTRF_11                       (3 << R_CANFD_CFDTMSTS_TMTRF_SHIFT)  /* Transmission successful from the TX message buffer and transmission abort was requested */

#define R_CANFD_CFDTMSTS_TMTRM                    (1 << 3)  /* TX Message Buffer Transmission Request Mirrored */

#define R_CANFD_CFDTMSTS_TMTARM                   (1 << 4)  /* TX Message Buffer Transmission Abort Request Mirrored */

/* CFDTMTRSTS Register bit definitions */
#define R_CANFD_CFDTMTRSTS_CFDTMTRSTS_SHIFT       (0)  /* TX Message Buffer Transmission Request Status */
#define R_CANFD_CFDTMTRSTS_CFDTMTRSTS_MASK        0xf
#  define R_CANFD_CFDTMTRSTS_CFDTMTRSTS_0                 (0 << R_CANFD_CFDTMTRSTS_CFDTMTRSTS_SHIFT)  /* Transmission not requested for corresponding TX message buffer */
#  define R_CANFD_CFDTMTRSTS_CFDTMTRSTS_1                 (1 << R_CANFD_CFDTMTRSTS_CFDTMTRSTS_SHIFT)  /* Transmission requested for corresponding TX message buffer */

/* CFDTMTARSTS Register bit definitions */
#define R_CANFD_CFDTMTARSTS_CFDTMTARSTS_SHIFT     (0)  /* TX Message Buffer Transmission Abort Request Status */
#define R_CANFD_CFDTMTARSTS_CFDTMTARSTS_MASK      0xf
#  define R_CANFD_CFDTMTARSTS_CFDTMTARSTS_0               (0 << R_CANFD_CFDTMTARSTS_CFDTMTARSTS_SHIFT)  /* Transmission abort not requested for corresponding TX message buffer */
#  define R_CANFD_CFDTMTARSTS_CFDTMTARSTS_1               (1 << R_CANFD_CFDTMTARSTS_CFDTMTARSTS_SHIFT)  /* Transmission abort requested for corresponding TX message buffer */

/* CFDTMTCSTS Register bit definitions */
#define R_CANFD_CFDTMTCSTS_CFDTMTCSTS_SHIFT       (0)  /* TX Message Buffer Transmission Completion Status */
#define R_CANFD_CFDTMTCSTS_CFDTMTCSTS_MASK        0xf
#  define R_CANFD_CFDTMTCSTS_CFDTMTCSTS_0                 (0 << R_CANFD_CFDTMTCSTS_CFDTMTCSTS_SHIFT)  /* Transmission not complete for corresponding TX message buffer */
#  define R_CANFD_CFDTMTCSTS_CFDTMTCSTS_1                 (1 << R_CANFD_CFDTMTCSTS_CFDTMTCSTS_SHIFT)  /* Transmission completed for corresponding TX message buffer */

/* CFDTMTASTS Register bit definitions */
#define R_CANFD_CFDTMTASTS_CFDTMTASTS_SHIFT       (0)  /* TX Message Buffer Transmission Abort Status */
#define R_CANFD_CFDTMTASTS_CFDTMTASTS_MASK        0xf
#  define R_CANFD_CFDTMTASTS_CFDTMTASTS_0                 (0 << R_CANFD_CFDTMTASTS_CFDTMTASTS_SHIFT)  /* Transmission not aborted for corresponding TX message buffer */
#  define R_CANFD_CFDTMTASTS_CFDTMTASTS_1                 (1 << R_CANFD_CFDTMTASTS_CFDTMTASTS_SHIFT)  /* Transmission aborted for corresponding TX message buffer */

/* CFDTMIEC Register bit definitions */
#define R_CANFD_CFDTMIEC_TMIEG_SHIFT              (0)  /* TX Message Buffer Interrupt Enable */
#define R_CANFD_CFDTMIEC_TMIEG_MASK               0xf
#  define R_CANFD_CFDTMIEC_TMIEG_0                        (0 << R_CANFD_CFDTMIEC_TMIEG_SHIFT)  /* TX message buffer interrupt disabled for corresponding TX message buffer */
#  define R_CANFD_CFDTMIEC_TMIEG_1                        (1 << R_CANFD_CFDTMIEC_TMIEG_SHIFT)  /* TX message buffer interrupt enabled for corresponding TX message buffer */

/* CFDTXQCC Register bit definitions */
#define R_CANFD_CFDTXQCC_TXQE                     (1 << 0)  /* TX Queue Enable */

#define R_CANFD_CFDTXQCC_TXQTXIE                  (1 << 5)  /* TX Queue TX Interrupt Enable */

#define R_CANFD_CFDTXQCC_TXQIM                    (1 << 7)  /* TX Queue Interrupt Mode */

#define R_CANFD_CFDTXQCC_TXQDC_SHIFT              (8)  /* TX Queue Depth Configuration */
#define R_CANFD_CFDTXQCC_TXQDC_MASK               0x300
#  define R_CANFD_CFDTXQCC_TXQDC_0X00                     (0 << R_CANFD_CFDTXQCC_TXQDC_SHIFT)  /* 0 messages */
#  define R_CANFD_CFDTXQCC_TXQDC_0X01                     (0 << R_CANFD_CFDTXQCC_TXQDC_SHIFT)  /* Reserved */
#  define R_CANFD_CFDTXQCC_TXQDC_0X10                     (0 << R_CANFD_CFDTXQCC_TXQDC_SHIFT)  /* 3 messages */
#  define R_CANFD_CFDTXQCC_TXQDC_0X11                     (0 << R_CANFD_CFDTXQCC_TXQDC_SHIFT)  /* 4 messages */

/* CFDTXQSTS Register bit definitions */
#define R_CANFD_CFDTXQSTS_TXQEMP                  (1 << 0)  /* TX Queue Empty */

#define R_CANFD_CFDTXQSTS_TXQFLL                  (1 << 1)  /* TX Queue Full */

#define R_CANFD_CFDTXQSTS_TXQTXIF                 (1 << 2)  /* TX Queue TX Interrupt Flag */

#define R_CANFD_CFDTXQSTS_TXQMC_SHIFT             (8)  /* TX Queue Message Count */
#define R_CANFD_CFDTXQSTS_TXQMC_MASK              0x700

/* CFDTXQPCTR Register bit definitions */
#define R_CANFD_CFDTXQPCTR_TXQPC_SHIFT            (0)  /* TX Queue Pointer Control */
#define R_CANFD_CFDTXQPCTR_TXQPC_MASK             0xff

/* CFDTHLCC Register bit definitions */
#define R_CANFD_CFDTHLCC_THLE                     (1 << 0)  /* TX History List Enable */

#define R_CANFD_CFDTHLCC_THLIE                    (1 << 8)  /* TX History List Interrupt Enable */

#define R_CANFD_CFDTHLCC_THLIM                    (1 << 9)  /* TX History List Interrupt Mode */

#define R_CANFD_CFDTHLCC_THLDTE                   (1 << 10)  /* TX History List Dedicated TX Enable */

/* CFDTHLSTS Register bit definitions */
#define R_CANFD_CFDTHLSTS_THLEMP                  (1 << 0)  /* TX History List Empty */

#define R_CANFD_CFDTHLSTS_THLFLL                  (1 << 1)  /* TX History List Full */

#define R_CANFD_CFDTHLSTS_THLELT                  (1 << 2)  /* TX History List Entry Lost */

#define R_CANFD_CFDTHLSTS_THLIF                   (1 << 3)  /* TX History List Interrupt Flag */

#define R_CANFD_CFDTHLSTS_THLMC_SHIFT             (8)  /* TX History List Message Count */
#define R_CANFD_CFDTHLSTS_THLMC_MASK              0xf00

/* CFDTHLPCTR Register bit definitions */
#define R_CANFD_CFDTHLPCTR_THLPC_SHIFT            (0)  /* TX History List Pointer Control */
#define R_CANFD_CFDTHLPCTR_THLPC_MASK             0xff

/* CFDGTINTSTS Register bit definitions */
#define R_CANFD_CFDGTINTSTS_TSIF0                 (1 << 0)  /* TX Successful Interrupt Flag */

#define R_CANFD_CFDGTINTSTS_TAI0                  (1 << 1)  /* TX Abort Interrupt Flag */

#define R_CANFD_CFDGTINTSTS_TQIF0                 (1 << 2)  /* TX Queue Interrupt Flag */

#define R_CANFD_CFDGTINTSTS_CFTIF0                (1 << 3)  /* COM FIFO TX Mode Interrupt Flag */

#define R_CANFD_CFDGTINTSTS_THIF0                 (1 << 4)  /* TX History List Interrupt */

/* CFDGTSTCFG Register bit definitions */
#define R_CANFD_CFDGTSTCFG_RTMPS_SHIFT            (16)  /* RAM Test Mode Page Select */
#define R_CANFD_CFDGTSTCFG_RTMPS_MASK             0x3ff0000

/* CFDGTSTCTR Register bit definitions */
#define R_CANFD_CFDGTSTCTR_RTME                   (1 << 2)  /* RAM Test Mode Enable */

/* CFDGFDCFG Register bit definitions */
#define R_CANFD_CFDGFDCFG_RPED                    (1 << 0)  /* RES Bit Protocol Exception Disable */

#define R_CANFD_CFDGFDCFG_TSCCFG_SHIFT            (8)  /* Timestamp Capture Configuration */
#define R_CANFD_CFDGFDCFG_TSCCFG_MASK             0x300
#  define R_CANFD_CFDGFDCFG_TSCCFG_00                     (0 << R_CANFD_CFDGFDCFG_TSCCFG_SHIFT)  /* Timestamp capture at the sample point of SOF (start of frame) */
#  define R_CANFD_CFDGFDCFG_TSCCFG_01                     (1 << R_CANFD_CFDGFDCFG_TSCCFG_SHIFT)  /* Timestamp capture at frame valid indication */
#  define R_CANFD_CFDGFDCFG_TSCCFG_10                     (2 << R_CANFD_CFDGFDCFG_TSCCFG_SHIFT)  /* Timestamp capture at the sample point of RES bit */
#  define R_CANFD_CFDGFDCFG_TSCCFG_11                     (3 << R_CANFD_CFDGFDCFG_TSCCFG_SHIFT)  /* Reserved */

/* CFDGLOCKK Register bit definitions */
#define R_CANFD_CFDGLOCKK_LOCK_SHIFT              (0)  /* Lock Key */
#define R_CANFD_CFDGLOCKK_LOCK_MASK               0xffff

/* CFDGAFLIGNENT Register bit definitions */
#define R_CANFD_CFDGAFLIGNENT_IRN_SHIFT           (0)  /* Ignore Rule Number */
#define R_CANFD_CFDGAFLIGNENT_IRN_MASK            0x1f

/* CFDGAFLIGNCTR Register bit definitions */
#define R_CANFD_CFDGAFLIGNCTR_IREN                (1 << 0)  /* Ignore Rule Enable */

#define R_CANFD_CFDGAFLIGNCTR_KEY_SHIFT           (8)  /* Key Code */
#define R_CANFD_CFDGAFLIGNCTR_KEY_MASK            0xff00

/* CFDCDTCT Register bit definitions */
#define R_CANFD_CFDCDTCT_RFDMAE0                  (1 << 0)  /* DMA Transfer Enable for RXFIFO 0 */

#define R_CANFD_CFDCDTCT_RFDMAE1                  (1 << 1)  /* DMA Transfer Enable for RXFIFO 1 */

#define R_CANFD_CFDCDTCT_CFDMAE                   (1 << 8)  /* DMA Transfer Enable for Common FIFO 0 */

#define R_CANFD_CFDCDTCT_CFDMAE0                  (1 << 8)  /* DMA Transfer Enable for Common FIFO 0 of channel 0 */

/* CFDCDTSTS Register bit definitions */
#define R_CANFD_CFDCDTSTS_RFDMASTS0               (1 << 0)  /* DMA Transfer Status for RX FIFO 0 */

#define R_CANFD_CFDCDTSTS_RFDMASTS1               (1 << 1)  /* DMA Transfer Status for RX FIFO 1 */

#define R_CANFD_CFDCDTSTS_CFDMASTS                (1 << 8)  /* DMA Transfer Status only for Common FIFO */

/* CFDGRSTC Register bit definitions */
#define R_CANFD_CFDGRSTC_SRST                     (1 << 0)  /* SW Reset */

#define R_CANFD_CFDGRSTC_KEY_SHIFT                (8)  /* Key Code */
#define R_CANFD_CFDGRSTC_KEY_MASK                 0xff00

/* CFDC0DCFG Register bit definitions */
#define R_CANFD_CFDC0DCFG_DBRP_SHIFT              (0)  /* Channel Data Baud Rate Prescaler */
#define R_CANFD_CFDC0DCFG_DBRP_MASK               0xff

#define R_CANFD_CFDC0DCFG_DTSEG1_SHIFT            (8)  /* Timing Segment 1 */
#define R_CANFD_CFDC0DCFG_DTSEG1_MASK             0x1f00

#define R_CANFD_CFDC0DCFG_DTSEG2_SHIFT            (16)  /* Timing Segment 2 */
#define R_CANFD_CFDC0DCFG_DTSEG2_MASK             0xf0000

#define R_CANFD_CFDC0DCFG_DSJW_SHIFT              (24)  /* Resynchronization Jump Width */
#define R_CANFD_CFDC0DCFG_DSJW_MASK               0xf000000

/* CFDC0FDCFG Register bit definitions */
#define R_CANFD_CFDC0FDCFG_EOCCFG_SHIFT           (0)  /* Error Occurrence Counter Configuration */
#define R_CANFD_CFDC0FDCFG_EOCCFG_MASK            0x7
#  define R_CANFD_CFDC0FDCFG_EOCCFG_000                   (0 << R_CANFD_CFDC0FDCFG_EOCCFG_SHIFT)  /* All transmitter or receiver CAN frames */
#  define R_CANFD_CFDC0FDCFG_EOCCFG_001                   (1 << R_CANFD_CFDC0FDCFG_EOCCFG_SHIFT)  /* All transmitter CAN frames */
#  define R_CANFD_CFDC0FDCFG_EOCCFG_010                   (2 << R_CANFD_CFDC0FDCFG_EOCCFG_SHIFT)  /* All receiver CAN frames */
#  define R_CANFD_CFDC0FDCFG_EOCCFG_011                   (3 << R_CANFD_CFDC0FDCFG_EOCCFG_SHIFT)  /* Reserved */
#  define R_CANFD_CFDC0FDCFG_EOCCFG_100                   (4 << R_CANFD_CFDC0FDCFG_EOCCFG_SHIFT)  /* Only transmitter or receiver CANFD data-phase (fast bits) */
#  define R_CANFD_CFDC0FDCFG_EOCCFG_101                   (5 << R_CANFD_CFDC0FDCFG_EOCCFG_SHIFT)  /* Only transmitter CANFD data-phase (fast bits) */
#  define R_CANFD_CFDC0FDCFG_EOCCFG_110                   (6 << R_CANFD_CFDC0FDCFG_EOCCFG_SHIFT)  /* Only receiver CANFD data-phase (fast bits) */
#  define R_CANFD_CFDC0FDCFG_EOCCFG_111                   (7 << R_CANFD_CFDC0FDCFG_EOCCFG_SHIFT)  /* Reserved */

#define R_CANFD_CFDC0FDCFG_TDCOC                  (1 << 8)  /* Transceiver Delay Compensation Offset Configuration */

#define R_CANFD_CFDC0FDCFG_TDCE                   (1 << 9)  /* Transceiver Delay Compensation Enable */

#define R_CANFD_CFDC0FDCFG_ESIC                   (1 << 10)  /* Error State Indication Configuration */

#define R_CANFD_CFDC0FDCFG_TDCO_SHIFT             (16)  /* Transceiver Delay Compensation Offset */
#define R_CANFD_CFDC0FDCFG_TDCO_MASK              0xff0000

#define R_CANFD_CFDC0FDCFG_FDOE                   (1 << 28)  /* FD-Only Enable */

#define R_CANFD_CFDC0FDCFG_REFE                   (1 << 29)  /* RX Edge Filter Enable */

#define R_CANFD_CFDC0FDCFG_CLOE                   (1 << 30)  /* Classical CAN Enable */

/* CFDC0FDCTR Register bit definitions */
#define R_CANFD_CFDC0FDCTR_EOCCLR                 (1 << 0)  /* Error Occurrence Counter Clear */

#define R_CANFD_CFDC0FDCTR_SOCCLR                 (1 << 1)  /* Successful Occurrence Counter Clear */

/* CFDC0FDSTS Register bit definitions */
#define R_CANFD_CFDC0FDSTS_TDCR_SHIFT             (0)  /* Transceiver Delay Compensation Result */
#define R_CANFD_CFDC0FDSTS_TDCR_MASK              0xff

#define R_CANFD_CFDC0FDSTS_EOCO                   (1 << 8)  /* Error Occurrence Counter Overflow */

#define R_CANFD_CFDC0FDSTS_SOCO                   (1 << 9)  /* Successful Occurrence Counter Overflow */

#define R_CANFD_CFDC0FDSTS_TDCVF                  (1 << 15)  /* Transceiver Delay Compensation Violation Flag */

#define R_CANFD_CFDC0FDSTS_EOC_SHIFT              (16)  /* Error Occurrence Counter */
#define R_CANFD_CFDC0FDSTS_EOC_MASK               0xff0000

#define R_CANFD_CFDC0FDSTS_SOC_SHIFT              (24)  /* Successful occurrence counter */
#define R_CANFD_CFDC0FDSTS_SOC_MASK               0xff000000

/* CFDC0FDCRC Register bit definitions */
#define R_CANFD_CFDC0FDCRC_CRCREG_SHIFT           (0)  /* CRC Register value */
#define R_CANFD_CFDC0FDCRC_CRCREG_MASK            0x1fffff

#define R_CANFD_CFDC0FDCRC_SCNT_SHIFT             (24)  /* Stuff bit count */
#define R_CANFD_CFDC0FDCRC_SCNT_MASK              0xf000000

/* CFDGAFLID Register bit definitions */
#define R_CANFD_CFDGAFLID_GAFLID_SHIFT            (0)  /* Global Acceptance Filter List Entry ID Field */
#define R_CANFD_CFDGAFLID_GAFLID_MASK             0x1fffffff

#define R_CANFD_CFDGAFLID_GAFLLB                  (1 << 29)  /* Global Acceptance Filter List Entry Loopback Configuration */

#define R_CANFD_CFDGAFLID_GAFLRTR                 (1 << 30)  /* Global Acceptance Filter List Entry RTR Field */

#define R_CANFD_CFDGAFLID_GAFLIDE                 (1 << 31)  /* Global Acceptance Filter List Entry IDE Field */

/* CFDGAFLM Register bit definitions */
#define R_CANFD_CFDGAFLM_GAFLIDM_SHIFT            (0)  /* Global Acceptance Filter List ID Mask Field */
#define R_CANFD_CFDGAFLM_GAFLIDM_MASK             0x1fffffff

#define R_CANFD_CFDGAFLM_GAFLIFL1                 (1 << 29)  /* Global Acceptance Filter List Information Label 1 */

#define R_CANFD_CFDGAFLM_GAFLRTRM                 (1 << 30)  /* Global Acceptance Filter List Entry RTR Mask */

#define R_CANFD_CFDGAFLM_GAFLIDEM                 (1 << 31)  /* Global Acceptance Filter List IDE Mask */

/* CFDGAFLP Register bit definitions */
#define R_CANFD_CFDGAFLP_GAFLDLC_SHIFT            (0)  /* Global Acceptance Filter List DLC Field */
#define R_CANFD_CFDGAFLP_GAFLDLC_MASK             0xf

#define R_CANFD_CFDGAFLP_GAFLIFL0                 (1 << 7)  /* Global Acceptance Filter List Information Label 0 */

#define R_CANFD_CFDGAFLP_GAFLRMDP_SHIFT           (8)  /* Global Acceptance Filter List RX Message Buffer Direction Pointer */
#define R_CANFD_CFDGAFLP_GAFLRMDP_MASK            0x1f00

#define R_CANFD_CFDGAFLP_GAFLRMV                  (1 << 15)  /* Global Acceptance Filter List RX Message Buffer Valid */

#define R_CANFD_CFDGAFLP_GAFLPTR_SHIFT            (16)  /* Global Acceptance Filter List Pointer */
#define R_CANFD_CFDGAFLP_GAFLPTR_MASK             0xffff0000

/* CFDGAFLP Register bit definitions */
#define R_CANFD_CFDGAFLP_GAFLFDP0                 (1 << 0)  /* Global Acceptance Filter List FIFO Direction Pointer */

#define R_CANFD_CFDGAFLP_GAFLFDP1                 (1 << 1)  /* Global Acceptance Filter List FIFO Direction Pointer */

#define R_CANFD_CFDGAFLP_GAFLFDP8                 (1 << 8)  /* Global Acceptance Filter List FIFO Direction Pointer */

/* CFDRPGACC Register bit definitions */
#define R_CANFD_CFDRPGACC_RDTA_SHIFT              (0)  /* RAM Data Test Access */
#define R_CANFD_CFDRPGACC_RDTA_MASK               0xffffffff

/* CFDRFID Register bit definitions */
#define R_CANFD_CFDRFID_RFID_SHIFT                (0)  /* RX FIFO Buffer ID Field */
#define R_CANFD_CFDRFID_RFID_MASK                 0x1fffffff

#define R_CANFD_CFDRFID_RFRTR                     (1 << 30)  /* RX FIFO Buffer RTR bit */

#define R_CANFD_CFDRFID_RFIDE                     (1 << 31)  /* RX FIFO Buffer IDE bit */

/* CFDRFPTR Register bit definitions */
#define R_CANFD_CFDRFPTR_RFTS_SHIFT               (0)  /* RX FIFO Timestamp Value */
#define R_CANFD_CFDRFPTR_RFTS_MASK                0xffff

#define R_CANFD_CFDRFPTR_RFDLC_SHIFT              (28)  /* RX FIFO Buffer DLC Field */
#define R_CANFD_CFDRFPTR_RFDLC_MASK               0xf0000000

/* CFDRFFDSTS Register bit definitions */
#define R_CANFD_CFDRFFDSTS_RFESI                  (1 << 0)  /* Error State Indicator bit */

#define R_CANFD_CFDRFFDSTS_RFBRS                  (1 << 1)  /* Bit Rate Switch bit */

#define R_CANFD_CFDRFFDSTS_RFFDF                  (1 << 2)  /* CAN FD Format bit */

#define R_CANFD_CFDRFFDSTS_RFIFL_SHIFT            (8)  /* RX FIFO Buffer Information Label Field */
#define R_CANFD_CFDRFFDSTS_RFIFL_MASK             0x300

#define R_CANFD_CFDRFFDSTS_CFDRFPTR_SHIFT         (16)  /* RX FIFO Buffer Pointer Field */
#define R_CANFD_CFDRFFDSTS_CFDRFPTR_MASK          0xffff0000

/* CFDRFDF_ Register bit definitions */
#define R_CANFD_CFDRFDF__RFDB_LL_SHIFT            (0)  /* RX FIFO Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRFDF__RFDB_LL_MASK             0xff

#define R_CANFD_CFDRFDF__RFDB_LH_SHIFT            (8)  /* RX FIFO Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRFDF__RFDB_LH_MASK             0xff00

#define R_CANFD_CFDRFDF__RFDB_HL_SHIFT            (16)  /* RX FIFO Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRFDF__RFDB_HL_MASK             0xff0000

#define R_CANFD_CFDRFDF__RFDB_HH_SHIFT            (24)  /* RX FIFO Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRFDF__RFDB_HH_MASK             0xff000000

/* CFDRFDF_ Register bit definitions */
#define R_CANFD_CFDRFDF__RFDB_LL_SHIFT            (0)  /* RX FIFO Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRFDF__RFDB_LL_MASK             0xff

#define R_CANFD_CFDRFDF__RFDB_LH_SHIFT            (8)  /* RX FIFO Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRFDF__RFDB_LH_MASK             0xff00

#define R_CANFD_CFDRFDF__RFDB_HL_SHIFT            (16)  /* RX FIFO Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRFDF__RFDB_HL_MASK             0xff0000

#define R_CANFD_CFDRFDF__RFDB_HH_SHIFT            (24)  /* RX FIFO Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRFDF__RFDB_HH_MASK             0xff000000

/* CFDRFDF_ Register bit definitions */
#define R_CANFD_CFDRFDF__RFDB_LL_SHIFT            (0)  /* RX FIFO Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRFDF__RFDB_LL_MASK             0xff

#define R_CANFD_CFDRFDF__RFDB_LH_SHIFT            (8)  /* RX FIFO Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRFDF__RFDB_LH_MASK             0xff00

#define R_CANFD_CFDRFDF__RFDB_HL_SHIFT            (16)  /* RX FIFO Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRFDF__RFDB_HL_MASK             0xff0000

#define R_CANFD_CFDRFDF__RFDB_HH_SHIFT            (24)  /* RX FIFO Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRFDF__RFDB_HH_MASK             0xff000000

/* CFDRFDF_ Register bit definitions */
#define R_CANFD_CFDRFDF__RFDB_LL_SHIFT            (0)  /* RX FIFO Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRFDF__RFDB_LL_MASK             0xff

#define R_CANFD_CFDRFDF__RFDB_LH_SHIFT            (8)  /* RX FIFO Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRFDF__RFDB_LH_MASK             0xff00

#define R_CANFD_CFDRFDF__RFDB_HL_SHIFT            (16)  /* RX FIFO Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRFDF__RFDB_HL_MASK             0xff0000

#define R_CANFD_CFDRFDF__RFDB_HH_SHIFT            (24)  /* RX FIFO Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRFDF__RFDB_HH_MASK             0xff000000

/* CFDRFDF_ Register bit definitions */
#define R_CANFD_CFDRFDF__RFDB_LL_SHIFT            (0)  /* RX FIFO Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRFDF__RFDB_LL_MASK             0xff

#define R_CANFD_CFDRFDF__RFDB_LH_SHIFT            (8)  /* RX FIFO Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRFDF__RFDB_LH_MASK             0xff00

#define R_CANFD_CFDRFDF__RFDB_HL_SHIFT            (16)  /* RX FIFO Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRFDF__RFDB_HL_MASK             0xff0000

#define R_CANFD_CFDRFDF__RFDB_HH_SHIFT            (24)  /* RX FIFO Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRFDF__RFDB_HH_MASK             0xff000000

/* CFDRFDF_ Register bit definitions */
#define R_CANFD_CFDRFDF__RFDB_LL_SHIFT            (0)  /* RX FIFO Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRFDF__RFDB_LL_MASK             0xff

#define R_CANFD_CFDRFDF__RFDB_LH_SHIFT            (8)  /* RX FIFO Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRFDF__RFDB_LH_MASK             0xff00

#define R_CANFD_CFDRFDF__RFDB_HL_SHIFT            (16)  /* RX FIFO Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRFDF__RFDB_HL_MASK             0xff0000

#define R_CANFD_CFDRFDF__RFDB_HH_SHIFT            (24)  /* RX FIFO Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRFDF__RFDB_HH_MASK             0xff000000

/* CFDRFDF_ Register bit definitions */
#define R_CANFD_CFDRFDF__RFDB_LL_SHIFT            (0)  /* RX FIFO Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRFDF__RFDB_LL_MASK             0xff

#define R_CANFD_CFDRFDF__RFDB_LH_SHIFT            (8)  /* RX FIFO Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRFDF__RFDB_LH_MASK             0xff00

#define R_CANFD_CFDRFDF__RFDB_HL_SHIFT            (16)  /* RX FIFO Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRFDF__RFDB_HL_MASK             0xff0000

#define R_CANFD_CFDRFDF__RFDB_HH_SHIFT            (24)  /* RX FIFO Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRFDF__RFDB_HH_MASK             0xff000000

/* CFDRFDF_ Register bit definitions */
#define R_CANFD_CFDRFDF__RFDB_LL_SHIFT            (0)  /* RX FIFO Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRFDF__RFDB_LL_MASK             0xff

#define R_CANFD_CFDRFDF__RFDB_LH_SHIFT            (8)  /* RX FIFO Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRFDF__RFDB_LH_MASK             0xff00

#define R_CANFD_CFDRFDF__RFDB_HL_SHIFT            (16)  /* RX FIFO Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRFDF__RFDB_HL_MASK             0xff0000

#define R_CANFD_CFDRFDF__RFDB_HH_SHIFT            (24)  /* RX FIFO Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRFDF__RFDB_HH_MASK             0xff000000

/* CFDRFDF_ Register bit definitions */
#define R_CANFD_CFDRFDF__RFDB_LL_SHIFT            (0)  /* RX FIFO Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRFDF__RFDB_LL_MASK             0xff

#define R_CANFD_CFDRFDF__RFDB_LH_SHIFT            (8)  /* RX FIFO Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRFDF__RFDB_LH_MASK             0xff00

#define R_CANFD_CFDRFDF__RFDB_HL_SHIFT            (16)  /* RX FIFO Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRFDF__RFDB_HL_MASK             0xff0000

#define R_CANFD_CFDRFDF__RFDB_HH_SHIFT            (24)  /* RX FIFO Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRFDF__RFDB_HH_MASK             0xff000000

/* CFDRFDF_ Register bit definitions */
#define R_CANFD_CFDRFDF__RFDB_LL_SHIFT            (0)  /* RX FIFO Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRFDF__RFDB_LL_MASK             0xff

#define R_CANFD_CFDRFDF__RFDB_LH_SHIFT            (8)  /* RX FIFO Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRFDF__RFDB_LH_MASK             0xff00

#define R_CANFD_CFDRFDF__RFDB_HL_SHIFT            (16)  /* RX FIFO Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRFDF__RFDB_HL_MASK             0xff0000

#define R_CANFD_CFDRFDF__RFDB_HH_SHIFT            (24)  /* RX FIFO Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRFDF__RFDB_HH_MASK             0xff000000

/* CFDRFDF_ Register bit definitions */
#define R_CANFD_CFDRFDF__RFDB_LL_SHIFT            (0)  /* RX FIFO Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRFDF__RFDB_LL_MASK             0xff

#define R_CANFD_CFDRFDF__RFDB_LH_SHIFT            (8)  /* RX FIFO Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRFDF__RFDB_LH_MASK             0xff00

#define R_CANFD_CFDRFDF__RFDB_HL_SHIFT            (16)  /* RX FIFO Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRFDF__RFDB_HL_MASK             0xff0000

#define R_CANFD_CFDRFDF__RFDB_HH_SHIFT            (24)  /* RX FIFO Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRFDF__RFDB_HH_MASK             0xff000000

/* CFDRFDF_ Register bit definitions */
#define R_CANFD_CFDRFDF__RFDB_LL_SHIFT            (0)  /* RX FIFO Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRFDF__RFDB_LL_MASK             0xff

#define R_CANFD_CFDRFDF__RFDB_LH_SHIFT            (8)  /* RX FIFO Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRFDF__RFDB_LH_MASK             0xff00

#define R_CANFD_CFDRFDF__RFDB_HL_SHIFT            (16)  /* RX FIFO Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRFDF__RFDB_HL_MASK             0xff0000

#define R_CANFD_CFDRFDF__RFDB_HH_SHIFT            (24)  /* RX FIFO Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRFDF__RFDB_HH_MASK             0xff000000

/* CFDRFDF_ Register bit definitions */
#define R_CANFD_CFDRFDF__RFDB_LL_SHIFT            (0)  /* RX FIFO Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRFDF__RFDB_LL_MASK             0xff

#define R_CANFD_CFDRFDF__RFDB_LH_SHIFT            (8)  /* RX FIFO Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRFDF__RFDB_LH_MASK             0xff00

#define R_CANFD_CFDRFDF__RFDB_HL_SHIFT            (16)  /* RX FIFO Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRFDF__RFDB_HL_MASK             0xff0000

#define R_CANFD_CFDRFDF__RFDB_HH_SHIFT            (24)  /* RX FIFO Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRFDF__RFDB_HH_MASK             0xff000000

/* CFDRFDF_ Register bit definitions */
#define R_CANFD_CFDRFDF__RFDB_LL_SHIFT            (0)  /* RX FIFO Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRFDF__RFDB_LL_MASK             0xff

#define R_CANFD_CFDRFDF__RFDB_LH_SHIFT            (8)  /* RX FIFO Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRFDF__RFDB_LH_MASK             0xff00

#define R_CANFD_CFDRFDF__RFDB_HL_SHIFT            (16)  /* RX FIFO Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRFDF__RFDB_HL_MASK             0xff0000

#define R_CANFD_CFDRFDF__RFDB_HH_SHIFT            (24)  /* RX FIFO Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRFDF__RFDB_HH_MASK             0xff000000

/* CFDRFDF_ Register bit definitions */
#define R_CANFD_CFDRFDF__RFDB_LL_SHIFT            (0)  /* RX FIFO Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRFDF__RFDB_LL_MASK             0xff

#define R_CANFD_CFDRFDF__RFDB_LH_SHIFT            (8)  /* RX FIFO Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRFDF__RFDB_LH_MASK             0xff00

#define R_CANFD_CFDRFDF__RFDB_HL_SHIFT            (16)  /* RX FIFO Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRFDF__RFDB_HL_MASK             0xff0000

#define R_CANFD_CFDRFDF__RFDB_HH_SHIFT            (24)  /* RX FIFO Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRFDF__RFDB_HH_MASK             0xff000000

/* CFDRFDF_ Register bit definitions */
#define R_CANFD_CFDRFDF__RFDB_LL_SHIFT            (0)  /* RX FIFO Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRFDF__RFDB_LL_MASK             0xff

#define R_CANFD_CFDRFDF__RFDB_LH_SHIFT            (8)  /* RX FIFO Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRFDF__RFDB_LH_MASK             0xff00

#define R_CANFD_CFDRFDF__RFDB_HL_SHIFT            (16)  /* RX FIFO Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRFDF__RFDB_HL_MASK             0xff0000

#define R_CANFD_CFDRFDF__RFDB_HH_SHIFT            (24)  /* RX FIFO Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRFDF__RFDB_HH_MASK             0xff000000

/* CFDCFID Register bit definitions */
#define R_CANFD_CFDCFID_CFID_SHIFT                (0)  /* Common FIFO Buffer ID Field */
#define R_CANFD_CFDCFID_CFID_MASK                 0x1fffffff

#define R_CANFD_CFDCFID_THLEN                     (1 << 29)  /* THL Entry enable */

#define R_CANFD_CFDCFID_CFRTR                     (1 << 30)  /* Common FIFO Buffer RTR Bit */

#define R_CANFD_CFDCFID_CFIDE                     (1 << 31)  /* Common FIFO Buffer IDE Bit */

/* CFDCFPTR Register bit definitions */
#define R_CANFD_CFDCFPTR_CFTS_SHIFT               (0)  /* Common FIFO Timestamp Value */
#define R_CANFD_CFDCFPTR_CFTS_MASK                0xffff

#define R_CANFD_CFDCFPTR_CFDLC_SHIFT              (28)  /* Common FIFO Buffer DLC Field */
#define R_CANFD_CFDCFPTR_CFDLC_MASK               0xf0000000

/* CFDCFFDCSTS Register bit definitions */
#define R_CANFD_CFDCFFDCSTS_CFESI                 (1 << 0)  /* Error State Indicator bit */

#define R_CANFD_CFDCFFDCSTS_CFBRS                 (1 << 1)  /* Bit Rate Switch bit */

#define R_CANFD_CFDCFFDCSTS_CFFDF                 (1 << 2)  /* CAN FD Format bit */

#define R_CANFD_CFDCFFDCSTS_CFIFL_SHIFT           (8)  /* COMMON FIFO Buffer Information Label Field */
#define R_CANFD_CFDCFFDCSTS_CFIFL_MASK            0x300

#define R_CANFD_CFDCFFDCSTS_CFPTR_SHIFT           (16)  /* Common FIFO Buffer Pointer Field */
#define R_CANFD_CFDCFFDCSTS_CFPTR_MASK            0xffff0000

/* CFDCFDF Register bit definitions */
#define R_CANFD_CFDCFDF_CFDB_LL_SHIFT             (0)  /* Common FIFO Buffer Data Bytes (p × 4) */
#define R_CANFD_CFDCFDF_CFDB_LL_MASK              0xff

#define R_CANFD_CFDCFDF_CFDB_LH_SHIFT             (8)  /* Common FIFO Buffer Data Bytes ((p × 4) + 1) */
#define R_CANFD_CFDCFDF_CFDB_LH_MASK              0xff00

#define R_CANFD_CFDCFDF_CFDB_HL_SHIFT             (16)  /* Common FIFO Buffer Data Bytes ((p × 4) + 2) */
#define R_CANFD_CFDCFDF_CFDB_HL_MASK              0xff0000

#define R_CANFD_CFDCFDF_CFDB_HH_SHIFT             (24)  /* Common FIFO Buffer Data Bytes ((p × 4) + 3) */
#define R_CANFD_CFDCFDF_CFDB_HH_MASK              0xff000000

/* CFDTMID Register bit definitions */
#define R_CANFD_CFDTMID_TMID_SHIFT                (0)  /* TX Message Buffer ID Field */
#define R_CANFD_CFDTMID_TMID_MASK                 0x1fffffff

#define R_CANFD_CFDTMID_THLEN                     (1 << 29)  /* Tx History List Entry */

#define R_CANFD_CFDTMID_TMRTR                     (1 << 30)  /* TX Message Buffer RTR bit */

#define R_CANFD_CFDTMID_TMIDE                     (1 << 31)  /* TX Message Buffer IDE bit */

/* CFDTMPTR Register bit definitions */
#define R_CANFD_CFDTMPTR_TMDLC_SHIFT              (28)  /* TX Message Buffer DLC Field */
#define R_CANFD_CFDTMPTR_TMDLC_MASK               0xf0000000

/* CFDTMFDCTR Register bit definitions */
#define R_CANFD_CFDTMFDCTR_TMESI                  (1 << 0)  /* Error State Indicator bit */

#define R_CANFD_CFDTMFDCTR_TMBRS                  (1 << 1)  /* Bit Rate Switch bit */

#define R_CANFD_CFDTMFDCTR_TMFDF                  (1 << 2)  /* CAN FD Format bit */

#define R_CANFD_CFDTMFDCTR_TMIFL_SHIFT            (8)  /* TX Message Buffer Information Label Field */
#define R_CANFD_CFDTMFDCTR_TMIFL_MASK             0x300

#define R_CANFD_CFDTMFDCTR_TMPTR_SHIFT            (16)  /* TX Message Buffer Pointer Field */
#define R_CANFD_CFDTMFDCTR_TMPTR_MASK             0xffff0000

/* CFDTMDF_ Register bit definitions */
#define R_CANFD_CFDTMDF__TMDB_LL_SHIFT            (0)  /* TX Message Buffer Data Byte ((p × 4) */
#define R_CANFD_CFDTMDF__TMDB_LL_MASK             0xff

#define R_CANFD_CFDTMDF__TMDB_LH_SHIFT            (8)  /* TX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDTMDF__TMDB_LH_MASK             0xff00

#define R_CANFD_CFDTMDF__TMDB_HL_SHIFT            (16)  /* TX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDTMDF__TMDB_HL_MASK             0xff0000

#define R_CANFD_CFDTMDF__TMDB_HH_SHIFT            (24)  /* TX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDTMDF__TMDB_HH_MASK             0xff000000

/* CFDTMDF_ Register bit definitions */
#define R_CANFD_CFDTMDF__TMDB_LL_SHIFT            (0)  /* TX Message Buffer Data Byte ((p × 4) */
#define R_CANFD_CFDTMDF__TMDB_LL_MASK             0xff

#define R_CANFD_CFDTMDF__TMDB_LH_SHIFT            (8)  /* TX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDTMDF__TMDB_LH_MASK             0xff00

#define R_CANFD_CFDTMDF__TMDB_HL_SHIFT            (16)  /* TX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDTMDF__TMDB_HL_MASK             0xff0000

#define R_CANFD_CFDTMDF__TMDB_HH_SHIFT            (24)  /* TX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDTMDF__TMDB_HH_MASK             0xff000000

/* CFDTMDF_ Register bit definitions */
#define R_CANFD_CFDTMDF__TMDB_LL_SHIFT            (0)  /* TX Message Buffer Data Byte ((p × 4) */
#define R_CANFD_CFDTMDF__TMDB_LL_MASK             0xff

#define R_CANFD_CFDTMDF__TMDB_LH_SHIFT            (8)  /* TX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDTMDF__TMDB_LH_MASK             0xff00

#define R_CANFD_CFDTMDF__TMDB_HL_SHIFT            (16)  /* TX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDTMDF__TMDB_HL_MASK             0xff0000

#define R_CANFD_CFDTMDF__TMDB_HH_SHIFT            (24)  /* TX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDTMDF__TMDB_HH_MASK             0xff000000

/* CFDTMDF_ Register bit definitions */
#define R_CANFD_CFDTMDF__TMDB_LL_SHIFT            (0)  /* TX Message Buffer Data Byte ((p × 4) */
#define R_CANFD_CFDTMDF__TMDB_LL_MASK             0xff

#define R_CANFD_CFDTMDF__TMDB_LH_SHIFT            (8)  /* TX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDTMDF__TMDB_LH_MASK             0xff00

#define R_CANFD_CFDTMDF__TMDB_HL_SHIFT            (16)  /* TX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDTMDF__TMDB_HL_MASK             0xff0000

#define R_CANFD_CFDTMDF__TMDB_HH_SHIFT            (24)  /* TX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDTMDF__TMDB_HH_MASK             0xff000000

/* CFDTMDF_ Register bit definitions */
#define R_CANFD_CFDTMDF__TMDB_LL_SHIFT            (0)  /* TX Message Buffer Data Byte ((p × 4) */
#define R_CANFD_CFDTMDF__TMDB_LL_MASK             0xff

#define R_CANFD_CFDTMDF__TMDB_LH_SHIFT            (8)  /* TX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDTMDF__TMDB_LH_MASK             0xff00

#define R_CANFD_CFDTMDF__TMDB_HL_SHIFT            (16)  /* TX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDTMDF__TMDB_HL_MASK             0xff0000

#define R_CANFD_CFDTMDF__TMDB_HH_SHIFT            (24)  /* TX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDTMDF__TMDB_HH_MASK             0xff000000

/* CFDTMDF_ Register bit definitions */
#define R_CANFD_CFDTMDF__TMDB_LL_SHIFT            (0)  /* TX Message Buffer Data Byte ((p × 4) */
#define R_CANFD_CFDTMDF__TMDB_LL_MASK             0xff

#define R_CANFD_CFDTMDF__TMDB_LH_SHIFT            (8)  /* TX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDTMDF__TMDB_LH_MASK             0xff00

#define R_CANFD_CFDTMDF__TMDB_HL_SHIFT            (16)  /* TX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDTMDF__TMDB_HL_MASK             0xff0000

#define R_CANFD_CFDTMDF__TMDB_HH_SHIFT            (24)  /* TX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDTMDF__TMDB_HH_MASK             0xff000000

/* CFDTMDF_ Register bit definitions */
#define R_CANFD_CFDTMDF__TMDB_LL_SHIFT            (0)  /* TX Message Buffer Data Byte ((p × 4) */
#define R_CANFD_CFDTMDF__TMDB_LL_MASK             0xff

#define R_CANFD_CFDTMDF__TMDB_LH_SHIFT            (8)  /* TX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDTMDF__TMDB_LH_MASK             0xff00

#define R_CANFD_CFDTMDF__TMDB_HL_SHIFT            (16)  /* TX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDTMDF__TMDB_HL_MASK             0xff0000

#define R_CANFD_CFDTMDF__TMDB_HH_SHIFT            (24)  /* TX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDTMDF__TMDB_HH_MASK             0xff000000

/* CFDTMDF_ Register bit definitions */
#define R_CANFD_CFDTMDF__TMDB_LL_SHIFT            (0)  /* TX Message Buffer Data Byte ((p × 4) */
#define R_CANFD_CFDTMDF__TMDB_LL_MASK             0xff

#define R_CANFD_CFDTMDF__TMDB_LH_SHIFT            (8)  /* TX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDTMDF__TMDB_LH_MASK             0xff00

#define R_CANFD_CFDTMDF__TMDB_HL_SHIFT            (16)  /* TX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDTMDF__TMDB_HL_MASK             0xff0000

#define R_CANFD_CFDTMDF__TMDB_HH_SHIFT            (24)  /* TX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDTMDF__TMDB_HH_MASK             0xff000000

/* CFDTMDF_ Register bit definitions */
#define R_CANFD_CFDTMDF__TMDB_LL_SHIFT            (0)  /* TX Message Buffer Data Byte ((p × 4) */
#define R_CANFD_CFDTMDF__TMDB_LL_MASK             0xff

#define R_CANFD_CFDTMDF__TMDB_LH_SHIFT            (8)  /* TX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDTMDF__TMDB_LH_MASK             0xff00

#define R_CANFD_CFDTMDF__TMDB_HL_SHIFT            (16)  /* TX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDTMDF__TMDB_HL_MASK             0xff0000

#define R_CANFD_CFDTMDF__TMDB_HH_SHIFT            (24)  /* TX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDTMDF__TMDB_HH_MASK             0xff000000

/* CFDTMDF_ Register bit definitions */
#define R_CANFD_CFDTMDF__TMDB_LL_SHIFT            (0)  /* TX Message Buffer Data Byte ((p × 4) */
#define R_CANFD_CFDTMDF__TMDB_LL_MASK             0xff

#define R_CANFD_CFDTMDF__TMDB_LH_SHIFT            (8)  /* TX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDTMDF__TMDB_LH_MASK             0xff00

#define R_CANFD_CFDTMDF__TMDB_HL_SHIFT            (16)  /* TX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDTMDF__TMDB_HL_MASK             0xff0000

#define R_CANFD_CFDTMDF__TMDB_HH_SHIFT            (24)  /* TX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDTMDF__TMDB_HH_MASK             0xff000000

/* CFDTMDF_ Register bit definitions */
#define R_CANFD_CFDTMDF__TMDB_LL_SHIFT            (0)  /* TX Message Buffer Data Byte ((p × 4) */
#define R_CANFD_CFDTMDF__TMDB_LL_MASK             0xff

#define R_CANFD_CFDTMDF__TMDB_LH_SHIFT            (8)  /* TX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDTMDF__TMDB_LH_MASK             0xff00

#define R_CANFD_CFDTMDF__TMDB_HL_SHIFT            (16)  /* TX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDTMDF__TMDB_HL_MASK             0xff0000

#define R_CANFD_CFDTMDF__TMDB_HH_SHIFT            (24)  /* TX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDTMDF__TMDB_HH_MASK             0xff000000

/* CFDTMDF_ Register bit definitions */
#define R_CANFD_CFDTMDF__TMDB_LL_SHIFT            (0)  /* TX Message Buffer Data Byte ((p × 4) */
#define R_CANFD_CFDTMDF__TMDB_LL_MASK             0xff

#define R_CANFD_CFDTMDF__TMDB_LH_SHIFT            (8)  /* TX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDTMDF__TMDB_LH_MASK             0xff00

#define R_CANFD_CFDTMDF__TMDB_HL_SHIFT            (16)  /* TX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDTMDF__TMDB_HL_MASK             0xff0000

#define R_CANFD_CFDTMDF__TMDB_HH_SHIFT            (24)  /* TX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDTMDF__TMDB_HH_MASK             0xff000000

/* CFDTMDF_ Register bit definitions */
#define R_CANFD_CFDTMDF__TMDB_LL_SHIFT            (0)  /* TX Message Buffer Data Byte ((p × 4) */
#define R_CANFD_CFDTMDF__TMDB_LL_MASK             0xff

#define R_CANFD_CFDTMDF__TMDB_LH_SHIFT            (8)  /* TX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDTMDF__TMDB_LH_MASK             0xff00

#define R_CANFD_CFDTMDF__TMDB_HL_SHIFT            (16)  /* TX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDTMDF__TMDB_HL_MASK             0xff0000

#define R_CANFD_CFDTMDF__TMDB_HH_SHIFT            (24)  /* TX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDTMDF__TMDB_HH_MASK             0xff000000

/* CFDTMDF_ Register bit definitions */
#define R_CANFD_CFDTMDF__TMDB_LL_SHIFT            (0)  /* TX Message Buffer Data Byte ((p × 4) */
#define R_CANFD_CFDTMDF__TMDB_LL_MASK             0xff

#define R_CANFD_CFDTMDF__TMDB_LH_SHIFT            (8)  /* TX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDTMDF__TMDB_LH_MASK             0xff00

#define R_CANFD_CFDTMDF__TMDB_HL_SHIFT            (16)  /* TX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDTMDF__TMDB_HL_MASK             0xff0000

#define R_CANFD_CFDTMDF__TMDB_HH_SHIFT            (24)  /* TX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDTMDF__TMDB_HH_MASK             0xff000000

/* CFDTMDF_ Register bit definitions */
#define R_CANFD_CFDTMDF__TMDB_LL_SHIFT            (0)  /* TX Message Buffer Data Byte ((p × 4) */
#define R_CANFD_CFDTMDF__TMDB_LL_MASK             0xff

#define R_CANFD_CFDTMDF__TMDB_LH_SHIFT            (8)  /* TX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDTMDF__TMDB_LH_MASK             0xff00

#define R_CANFD_CFDTMDF__TMDB_HL_SHIFT            (16)  /* TX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDTMDF__TMDB_HL_MASK             0xff0000

#define R_CANFD_CFDTMDF__TMDB_HH_SHIFT            (24)  /* TX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDTMDF__TMDB_HH_MASK             0xff000000

/* CFDTMDF_ Register bit definitions */
#define R_CANFD_CFDTMDF__TMDB_LL_SHIFT            (0)  /* TX Message Buffer Data Byte ((p × 4) */
#define R_CANFD_CFDTMDF__TMDB_LL_MASK             0xff

#define R_CANFD_CFDTMDF__TMDB_LH_SHIFT            (8)  /* TX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDTMDF__TMDB_LH_MASK             0xff00

#define R_CANFD_CFDTMDF__TMDB_HL_SHIFT            (16)  /* TX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDTMDF__TMDB_HL_MASK             0xff0000

#define R_CANFD_CFDTMDF__TMDB_HH_SHIFT            (24)  /* TX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDTMDF__TMDB_HH_MASK             0xff000000

/* CFDTHLACC0 Register bit definitions */
#define R_CANFD_CFDTHLACC0_BT_SHIFT               (0)  /* Buffer Type */
#define R_CANFD_CFDTHLACC0_BT_MASK                0x7
#  define R_CANFD_CFDTHLACC0_BT_001                       (1 << R_CANFD_CFDTHLACC0_BT_SHIFT)  /* Flat TX message buffer */
#  define R_CANFD_CFDTHLACC0_BT_010                       (2 << R_CANFD_CFDTHLACC0_BT_SHIFT)  /* TX FIFO message buffer number */
#  define R_CANFD_CFDTHLACC0_BT_100                       (4 << R_CANFD_CFDTHLACC0_BT_SHIFT)  /* TX Queue message buffer number */

#define R_CANFD_CFDTHLACC0_BN_SHIFT               (3)  /* Buffer Number */
#define R_CANFD_CFDTHLACC0_BN_MASK                0x18

#define R_CANFD_CFDTHLACC0_TMTS_SHIFT             (16)  /* Transmit Timestamp */
#define R_CANFD_CFDTHLACC0_TMTS_MASK              0xffff0000

/* CFDTHLACC1 Register bit definitions */
#define R_CANFD_CFDTHLACC1_TID_SHIFT              (0)  /* Transmit ID */
#define R_CANFD_CFDTHLACC1_TID_MASK               0xffff

#define R_CANFD_CFDTHLACC1_TIFL_SHIFT             (16)  /* Transmit Information Label */
#define R_CANFD_CFDTHLACC1_TIFL_MASK              0x30000

/* CFDRMID Register bit definitions */
#define R_CANFD_CFDRMID_RMID_SHIFT                (0)  /* RX Message Buffer ID Field */
#define R_CANFD_CFDRMID_RMID_MASK                 0x1fffffff

#define R_CANFD_CFDRMID_RMRTR                     (1 << 30)  /* RX Message Buffer RTR Bit */

#define R_CANFD_CFDRMID_RMIDE                     (1 << 31)  /* RX Message Buffer IDE Bit */

/* CFDRMPTR Register bit definitions */
#define R_CANFD_CFDRMPTR_RMTS_SHIFT               (0)  /* RX Message Buffer Timestamp Field */
#define R_CANFD_CFDRMPTR_RMTS_MASK                0xffff

#define R_CANFD_CFDRMPTR_RMDLC_SHIFT              (28)  /* RX Message Buffer DLC Field */
#define R_CANFD_CFDRMPTR_RMDLC_MASK               0xf0000000

/* CFDRMFDSTS Register bit definitions */
#define R_CANFD_CFDRMFDSTS_RMESI                  (1 << 0)  /* Error State Indicator bit */

#define R_CANFD_CFDRMFDSTS_RMBRS                  (1 << 1)  /* Bit Rate Switch bit */

#define R_CANFD_CFDRMFDSTS_RMFDF                  (1 << 2)  /* CAN FD Format bit */

#define R_CANFD_CFDRMFDSTS_RMIFL_SHIFT            (8)  /* RX Message Buffer Information Label Field */
#define R_CANFD_CFDRMFDSTS_RMIFL_MASK             0x300

#define R_CANFD_CFDRMFDSTS_RMPTR_SHIFT            (16)  /* RX Message Buffer Pointer Field */
#define R_CANFD_CFDRMFDSTS_RMPTR_MASK             0xffff0000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMID Register bit definitions */
#define R_CANFD_CFDRMID_RMID_SHIFT                (0)  /* RX Message Buffer ID Field */
#define R_CANFD_CFDRMID_RMID_MASK                 0x1fffffff

#define R_CANFD_CFDRMID_RMRTR                     (1 << 30)  /* RX Message Buffer RTR Bit */

#define R_CANFD_CFDRMID_RMIDE                     (1 << 31)  /* RX Message Buffer IDE Bit */

/* CFDRMPTR Register bit definitions */
#define R_CANFD_CFDRMPTR_RMTS_SHIFT               (0)  /* RX Message Buffer Timestamp Field */
#define R_CANFD_CFDRMPTR_RMTS_MASK                0xffff

#define R_CANFD_CFDRMPTR_RMDLC_SHIFT              (28)  /* RX Message Buffer DLC Field */
#define R_CANFD_CFDRMPTR_RMDLC_MASK               0xf0000000

/* CFDRMFDSTS Register bit definitions */
#define R_CANFD_CFDRMFDSTS_RMESI                  (1 << 0)  /* Error State Indicator bit */

#define R_CANFD_CFDRMFDSTS_RMBRS                  (1 << 1)  /* Bit Rate Switch bit */

#define R_CANFD_CFDRMFDSTS_RMFDF                  (1 << 2)  /* CAN FD Format bit */

#define R_CANFD_CFDRMFDSTS_RMIFL_SHIFT            (8)  /* RX Message Buffer Information Label Field */
#define R_CANFD_CFDRMFDSTS_RMIFL_MASK             0x300

#define R_CANFD_CFDRMFDSTS_RMPTR_SHIFT            (16)  /* RX Message Buffer Pointer Field */
#define R_CANFD_CFDRMFDSTS_RMPTR_MASK             0xffff0000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMDF_ Register bit definitions */
#define R_CANFD_CFDRMDF__RMDB_LL_SHIFT            (0)  /* RX Message Buffer Data Byte (p × 4) */
#define R_CANFD_CFDRMDF__RMDB_LL_MASK             0xff

#define R_CANFD_CFDRMDF__RMDB_LH_SHIFT            (8)  /* RX Message Buffer Data Byte ((p × 4) + 1) */
#define R_CANFD_CFDRMDF__RMDB_LH_MASK             0xff00

#define R_CANFD_CFDRMDF__RMDB_HL_SHIFT            (16)  /* RX Message Buffer Data Byte ((p × 4) + 2) */
#define R_CANFD_CFDRMDF__RMDB_HL_MASK             0xff0000

#define R_CANFD_CFDRMDF__RMDB_HH_SHIFT            (24)  /* RX Message Buffer Data Byte ((p × 4) + 3) */
#define R_CANFD_CFDRMDF__RMDB_HH_MASK             0xff000000

/* CFDRMPTR Register bit definitions */
#define R_CANFD_CFDRMPTR_RMTS_SHIFT               (0)  /* RX Message Buffer Timestamp Field */
#define R_CANFD_CFDRMPTR_RMTS_MASK                0xffff

#define R_CANFD_CFDRMPTR_RMDLC_SHIFT              (28)  /* RX Message Buffer DLC Field */
#define R_CANFD_CFDRMPTR_RMDLC_MASK               0xf0000000

/* CFDRMFDSTS Register bit definitions */
#define R_CANFD_CFDRMFDSTS_RMESI                  (1 << 0)  /* Error State Indicator bit */

#define R_CANFD_CFDRMFDSTS_RMBRS                  (1 << 1)  /* Bit Rate Switch bit */

#define R_CANFD_CFDRMFDSTS_RMFDF                  (1 << 2)  /* CAN FD Format bit */

#define R_CANFD_CFDRMFDSTS_RMIFL_SHIFT            (8)  /* RX Message Buffer Information Label Field */
#define R_CANFD_CFDRMFDSTS_RMIFL_MASK             0x300

#define R_CANFD_CFDRMFDSTS_RMPTR_SHIFT            (16)  /* RX Message Buffer Pointer Field */
#define R_CANFD_CFDRMFDSTS_RMPTR_MASK             0xffff0000

/* CFDRMPTR Register bit definitions */
#define R_CANFD_CFDRMPTR_RMTS_SHIFT               (0)  /* RX Message Buffer Timestamp Field */
#define R_CANFD_CFDRMPTR_RMTS_MASK                0xffff

#define R_CANFD_CFDRMPTR_RMDLC_SHIFT              (28)  /* RX Message Buffer DLC Field */
#define R_CANFD_CFDRMPTR_RMDLC_MASK               0xf0000000

/* CFDRMFDSTS Register bit definitions */
#define R_CANFD_CFDRMFDSTS_RMESI                  (1 << 0)  /* Error State Indicator bit */

#define R_CANFD_CFDRMFDSTS_RMBRS                  (1 << 1)  /* Bit Rate Switch bit */

#define R_CANFD_CFDRMFDSTS_RMFDF                  (1 << 2)  /* CAN FD Format bit */

#define R_CANFD_CFDRMFDSTS_RMIFL_SHIFT            (8)  /* RX Message Buffer Information Label Field */
#define R_CANFD_CFDRMFDSTS_RMIFL_MASK             0x300

#define R_CANFD_CFDRMFDSTS_RMPTR_SHIFT            (16)  /* RX Message Buffer Pointer Field */
#define R_CANFD_CFDRMFDSTS_RMPTR_MASK             0xffff0000


/* Maximum number of channels */

#define CANFD_MAX_CHANNELS    64

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CANFD_H */

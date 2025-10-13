/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8e1/ra_canfd.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_CANFD_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_CANFD_H

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
#define R_CANFD_CH_STRIDE    0x00002000
#define R_CANFD_CH_BASE(ch)   (R_CANFD_BASE + ((uint32_t)(ch) * R_CANFD_CH_STRIDE))

/* CANFD Register Offsets */

#define R_CANFD_CFDC0NCFG_OFFSET                  0x00000000  /* Nominal Bitrate Configuration Register */
#define R_CANFD_CFDC0CTR_OFFSET                   0x00000004  /* Control Register */
#define R_CANFD_CFDC0STS_OFFSET                   0x00000008  /* Status Register */
#define R_CANFD_CFDC0ERFL_OFFSET                  0x0000000c  /*  Error Flag Register */
#define R_CANFD_CFDGCFG_OFFSET                    0x00000014  /* Global Configuration Register */
#define R_CANFD_CFDGCTR_OFFSET                    0x00000018  /* Global Control Register */
#define R_CANFD_CFDGSTS_OFFSET                    0x0000001c  /* Global Status Register */
#define R_CANFD_CFDGERFL_OFFSET                   0x00000020  /* Global Error Flag Register */
#define R_CANFD_CFDGTSC_OFFSET                    0x00000024  /* Global Timestamp Counter Register */
#define R_CANFD_CFDGAFLECTR_OFFSET                0x00000028  /* Global Acceptance Filter List Entry Control Register */
#define R_CANFD_CFDGAFLCFG_OFFSET                 0x0000002c  /* Global Acceptance Filter List Configuration Register */
#define R_CANFD_CFDRMNB_OFFSET                    0x00000030  /* RX Message Buffer Number Register */
#define R_CANFD_CFDRMND_OFFSET                    0x00000034  /* RX Message Buffer New Data Register */
#define R_CANFD_CFDRMIEC_OFFSET                   0x00000038  /* RX Message Buffer Interrupt Enable Configuration Register */
/* CFDRFCC%s Registers (0-1) */
#define R_CANFD_CFDRFCC_OFFSET(m)                 (0x0000003c + ((m) * 0x00000004))  /* RX FIFO Configuration/Control Registers %s */
/* CFDRFSTS%s Registers (0-1) */
#define R_CANFD_CFDRFSTS_OFFSET(m)                (0x00000044 + ((m) * 0x00000004))  /* RX FIFO Status Registers %s */
/* CFDRFPCTR%s Registers (0-1) */
#define R_CANFD_CFDRFPCTR_OFFSET(m)               (0x0000004c + ((m) * 0x00000004))  /* RX FIFO Pointer Control Registers %s */
#define R_CANFD_CFDCFCC_OFFSET                    0x00000054  /* Common FIFO Configuration/Control Register */
#define R_CANFD_CFDCFSTS_OFFSET                   0x00000058  /* Common FIFO Status Register */
#define R_CANFD_CFDCFPCTR_OFFSET                  0x0000005c  /* Common FIFO Pointer Control Register */
#define R_CANFD_CFDFESTS_OFFSET                   0x00000060  /* FIFO Empty Status Register */
#define R_CANFD_CFDFFSTS_OFFSET                   0x00000064  /* FIFO Full Status Register */
#define R_CANFD_CFDFMSTS_OFFSET                   0x00000068  /* FIFO Message Lost Status Register */
#define R_CANFD_CFDRFISTS_OFFSET                  0x0000006c  /* RX FIFO Interrupt Flag Status Register */
/* CFDTMC%s Registers (0-3) */
#define R_CANFD_CFDTMC_OFFSET(m)                  (0x00000070 + ((m) * 0x00000001))  /* TX Message Buffer Control Registers %s */
/* CFDTMSTS%s Registers (0-3) */
#define R_CANFD_CFDTMSTS_OFFSET(m)                (0x00000074 + ((m) * 0x00000001))  /* TX Message Buffer Status Registers %s */
#define R_CANFD_CFDTMTRSTS_OFFSET                 0x00000078  /* TX Message Buffer Transmission Request Status Register */
#define R_CANFD_CFDTMTARSTS_OFFSET                0x0000007c  /* TX Message Buffer Transmission Abort Request Status Register */
#define R_CANFD_CFDTMTCSTS_OFFSET                 0x00000080  /* TX Message Buffer Transmission Completion Status Register */
#define R_CANFD_CFDTMTASTS_OFFSET                 0x00000084  /* TX Message Buffer Transmission Abort Status Register */
#define R_CANFD_CFDTMIEC_OFFSET                   0x00000088  /* TX Message Buffer Interrupt Enable Configuration Register */
#define R_CANFD_CFDTXQCC_OFFSET                   0x0000008c  /* TX Queue Configuration/Control Register */
#define R_CANFD_CFDTXQSTS_OFFSET                  0x00000090  /* TX Queue Status Register */
#define R_CANFD_CFDTXQPCTR_OFFSET                 0x00000094  /* TX Queue Pointer Control Register */
#define R_CANFD_CFDTHLCC_OFFSET                   0x00000098  /* TX History List Configuration/Control Register */
#define R_CANFD_CFDTHLSTS_OFFSET                  0x0000009c  /* TX History List Status Register */
#define R_CANFD_CFDTHLPCTR_OFFSET                 0x000000a0  /* TX History List Pointer Control Register */
#define R_CANFD_CFDGTINTSTS_OFFSET                0x000000a4  /* Global TX Interrupt Status Register */
#define R_CANFD_CFDGTSTCFG_OFFSET                 0x000000a8  /* Global Test Configuration Register */
#define R_CANFD_CFDGTSTCTR_OFFSET                 0x000000ac  /* Global Test Control Register */
#define R_CANFD_CFDGFDCFG_OFFSET                  0x000000b0  /* Global FD Configuration Register */
#define R_CANFD_CFDGLOCKK_OFFSET                  0x000000b8  /* Global Lock Key Register */
#define R_CANFD_CFDGAFLIGNENT_OFFSET              0x000000c0  /* Global AFL Ignore Entry Register */
#define R_CANFD_CFDGAFLIGNCTR_OFFSET              0x000000c4  /* Global AFL Ignore Control Register */
#define R_CANFD_CFDCDTCT_OFFSET                   0x000000c8  /* DMA Transfer Control Register */
#define R_CANFD_CFDCDTSTS_OFFSET                  0x000000cc  /* DMA Transfer Status Register */
#define R_CANFD_CFDGRSTC_OFFSET                   0x000000d8  /* Global SW reset Register */
#define R_CANFD_CFDC0DCFG_OFFSET                  0x00000100  /*  Data Bitrate Configuration Register */
#define R_CANFD_CFDC0FDCFG_OFFSET                 0x00000104  /* CANFD Configuration Register */
#define R_CANFD_CFDC0FDCTR_OFFSET                 0x00000108  /* CANFD Control Register */
#define R_CANFD_CFDC0FDSTS_OFFSET                 0x0000010c  /* CANFD Status Register */
#define R_CANFD_CFDC0FDCRC_OFFSET                 0x00000110  /* CANFD CRC Register */
/* CFDGAFLID%s Registers (1-16) */
#define R_CANFD_CFDGAFLID_OFFSET(m)               (0x00000120 + ((m) * 0x00000010))  /* Global Acceptance Filter List ID Registers */
/* CFDGAFLM%s Registers (1-16) */
#define R_CANFD_CFDGAFLM_OFFSET(m)                (0x00000124 + ((m) * 0x00000010))  /* Global Acceptance Filter List Mask Registers */
/* CFDGAFLP0%s Registers (1-16) */
#define R_CANFD_CFDGAFLP0_OFFSET(m)               (0x00000128 + ((m) * 0x00000010))  /* Global Acceptance Filter List Pointer 0 Registers */
/* CFDGAFLP1%s Registers (1-16) */
#define R_CANFD_CFDGAFLP1_OFFSET(m)               (0x0000012c + ((m) * 0x00000010))  /* Global Acceptance Filter List Pointer 1 Registers */
/* CFDRPGACC%s Registers (0-63) */
#define R_CANFD_CFDRPGACC_OFFSET(m)               (0x00000280 + ((m) * 0x00000004))  /* RAM Test Page Access Registers %s */
/* CFDRFID%s Registers (0-1) */
#define R_CANFD_CFDRFID_OFFSET(m)                 (0x00000520 + ((m) * 0x0000004c))  /* RX FIFO Access ID Register %s */
/* CFDRFPTR%s Registers (0-1) */
#define R_CANFD_CFDRFPTR_OFFSET(m)                (0x00000524 + ((m) * 0x0000004c))  /* RX FIFO Access Pointer Register %s */
/* CFDRFFDSTS%s Registers (0-1) */
#define R_CANFD_CFDRFFDSTS_OFFSET(m)              (0x00000528 + ((m) * 0x0000004c))  /* RX FIFO Access CANFD Status Register %s */
/* CFDRFDF%s_0 Registers (0-1) */
#define R_CANFD_CFDRFDF_0_OFFSET(m)               (0x0000052c + ((m) * 0x0000004c))  /* RX FIFO Access Data Field 0 Register %s */
/* CFDRFDF%s_1 Registers (0-1) */
#define R_CANFD_CFDRFDF_1_OFFSET(m)               (0x00000530 + ((m) * 0x0000004c))  /* RX FIFO Access Data Field 1 Register %s */
/* CFDRFDF%s_2 Registers (0-1) */
#define R_CANFD_CFDRFDF_2_OFFSET(m)               (0x00000534 + ((m) * 0x0000004c))  /* RX FIFO Access Data Field 2 Register %s */
/* CFDRFDF%s_3 Registers (0-1) */
#define R_CANFD_CFDRFDF_3_OFFSET(m)               (0x00000538 + ((m) * 0x0000004c))  /* RX FIFO Access Data Field 3 Register %s */
/* CFDRFDF%s_4 Registers (0-1) */
#define R_CANFD_CFDRFDF_4_OFFSET(m)               (0x0000053c + ((m) * 0x0000004c))  /* RX FIFO Access Data Field 4 Register %s */
/* CFDRFDF%s_5 Registers (0-1) */
#define R_CANFD_CFDRFDF_5_OFFSET(m)               (0x00000540 + ((m) * 0x0000004c))  /* RX FIFO Access Data Field 5 Register %s */
/* CFDRFDF%s_6 Registers (0-1) */
#define R_CANFD_CFDRFDF_6_OFFSET(m)               (0x00000544 + ((m) * 0x0000004c))  /* RX FIFO Access Data Field 6 Register %s */
/* CFDRFDF%s_7 Registers (0-1) */
#define R_CANFD_CFDRFDF_7_OFFSET(m)               (0x00000548 + ((m) * 0x0000004c))  /* RX FIFO Access Data Field 7 Register %s */
/* CFDRFDF%s_8 Registers (0-1) */
#define R_CANFD_CFDRFDF_8_OFFSET(m)               (0x0000054c + ((m) * 0x0000004c))  /* RX FIFO Access Data Field 8 Register %s */
/* CFDRFDF%s_9 Registers (0-1) */
#define R_CANFD_CFDRFDF_9_OFFSET(m)               (0x00000550 + ((m) * 0x0000004c))  /* RX FIFO Access Data Field 9 Register %s */
/* CFDRFDF%s_10 Registers (0-1) */
#define R_CANFD_CFDRFDF_10_OFFSET(m)              (0x00000554 + ((m) * 0x0000004c))  /* RX FIFO Access Data Field 10 Register %s */
/* CFDRFDF%s_11 Registers (0-1) */
#define R_CANFD_CFDRFDF_11_OFFSET(m)              (0x00000558 + ((m) * 0x0000004c))  /* RX FIFO Access Data Field 11 Register %s */
/* CFDRFDF%s_12 Registers (0-1) */
#define R_CANFD_CFDRFDF_12_OFFSET(m)              (0x0000055c + ((m) * 0x0000004c))  /* RX FIFO Access Data Field 12 Register %s */
/* CFDRFDF%s_13 Registers (0-1) */
#define R_CANFD_CFDRFDF_13_OFFSET(m)              (0x00000560 + ((m) * 0x0000004c))  /* RX FIFO Access Data Field 13 Register %s */
/* CFDRFDF%s_14 Registers (0-1) */
#define R_CANFD_CFDRFDF_14_OFFSET(m)              (0x00000564 + ((m) * 0x0000004c))  /* RX FIFO Access Data Field 14 Register %s */
/* CFDRFDF%s_15 Registers (0-1) */
#define R_CANFD_CFDRFDF_15_OFFSET(m)              (0x00000568 + ((m) * 0x0000004c))  /* RX FIFO Access Data Field 15 Register %s */
#define R_CANFD_CFDCFID_OFFSET                    0x000005b8  /* Common FIFO Access ID Register */
#define R_CANFD_CFDCFPTR_OFFSET                   0x000005bc  /* Common FIFO Access Pointer Register */
#define R_CANFD_CFDCFFDCSTS_OFFSET                0x000005c0  /* Common FIFO Access CANFD Control/Status Register */
/* CFDCFDF%s Registers (0-15) */
#define R_CANFD_CFDCFDF_OFFSET(m)                 (0x000005c4 + ((m) * 0x00000004))  /* Common FIFO Access Data Field %s Registers */
/* CFDTMID%s Registers (0-3) */
#define R_CANFD_CFDTMID_OFFSET(m)                 (0x00000604 + ((m) * 0x0000004c))  /* TX Message Buffer ID Registers */
/* CFDTMPTR%s Registers (0-3) */
#define R_CANFD_CFDTMPTR_OFFSET(m)                (0x00000608 + ((m) * 0x0000004c))  /* TX Message Buffer Pointer Register  */
/* CFDTMFDCTR%s Registers (0-3) */
#define R_CANFD_CFDTMFDCTR_OFFSET(m)              (0x0000060c + ((m) * 0x0000004c))  /* TX Message Buffer CANFD Control Register  */
/* CFDTMDF%s_0 Registers (0-3) */
#define R_CANFD_CFDTMDF_0_OFFSET(m)               (0x00000610 + ((m) * 0x0000004c))  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_1 Registers (0-3) */
#define R_CANFD_CFDTMDF_1_OFFSET(m)               (0x00000614 + ((m) * 0x0000004c))  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_2 Registers (0-3) */
#define R_CANFD_CFDTMDF_2_OFFSET(m)               (0x00000618 + ((m) * 0x0000004c))  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_3 Registers (0-3) */
#define R_CANFD_CFDTMDF_3_OFFSET(m)               (0x0000061c + ((m) * 0x0000004c))  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_4 Registers (0-3) */
#define R_CANFD_CFDTMDF_4_OFFSET(m)               (0x00000620 + ((m) * 0x0000004c))  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_5 Registers (0-3) */
#define R_CANFD_CFDTMDF_5_OFFSET(m)               (0x00000624 + ((m) * 0x0000004c))  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_6 Registers (0-3) */
#define R_CANFD_CFDTMDF_6_OFFSET(m)               (0x00000628 + ((m) * 0x0000004c))  /* TX Message Buffer Data Field Register  */
/* CFDTMDF%s_7 Registers (0-3) */
#define R_CANFD_CFDTMDF_7_OFFSET(m)               (0x0000062c + ((m) * 0x0000004c))  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_8 Registers (0-3) */
#define R_CANFD_CFDTMDF_8_OFFSET(m)               (0x00000630 + ((m) * 0x0000004c))  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_9 Registers (0-3) */
#define R_CANFD_CFDTMDF_9_OFFSET(m)               (0x00000634 + ((m) * 0x0000004c))  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_10 Registers (0-3) */
#define R_CANFD_CFDTMDF_10_OFFSET(m)              (0x00000638 + ((m) * 0x0000004c))  /* TX Message Buffer Data Field Register  */
/* CFDTMDF%s_11 Registers (0-3) */
#define R_CANFD_CFDTMDF_11_OFFSET(m)              (0x0000063c + ((m) * 0x0000004c))  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_12 Registers (0-3) */
#define R_CANFD_CFDTMDF_12_OFFSET(m)              (0x00000640 + ((m) * 0x0000004c))  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_13 Registers (0-3) */
#define R_CANFD_CFDTMDF_13_OFFSET(m)              (0x00000644 + ((m) * 0x0000004c))  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_14 Registers (0-3) */
#define R_CANFD_CFDTMDF_14_OFFSET(m)              (0x00000648 + ((m) * 0x0000004c))  /* TX Message Buffer Data Field Register */
/* CFDTMDF%s_15 Registers (0-3) */
#define R_CANFD_CFDTMDF_15_OFFSET(m)              (0x0000064c + ((m) * 0x0000004c))  /* TX Message Buffer Data Field Register */
#define R_CANFD_CFDTHLACC0_OFFSET                 0x00000740  /* TX History List Access Register 0 */
#define R_CANFD_CFDTHLACC1_OFFSET                 0x00000744  /* TX History List Access Register 1 */
/* CFDRMID%s Registers (0-7) */
#define R_CANFD_CFDRMID_OFFSET(m)                 (0x00000920 + ((m) * 0x0000004c))  /* RX Message Buffer ID Registers */
/* CFDRMPTR%s Registers (0-7) */
#define R_CANFD_CFDRMPTR_OFFSET(m)                (0x00000924 + ((m) * 0x0000004c))  /* RX Message Buffer Pointer Registers */
/* CFDRMFDSTS%s Registers (0-7) */
#define R_CANFD_CFDRMFDSTS_OFFSET(m)              (0x00000928 + ((m) * 0x0000004c))  /* RX Message Buffer CANFD Status Registers */
/* CFDRMDF%s_0 Registers (0-7) */
#define R_CANFD_CFDRMDF_0_OFFSET(m)               (0x0000092c + ((m) * 0x0000004c))  /* RX Message Buffer Data Field 0 Registers */
/* CFDRMDF%s_1 Registers (0-7) */
#define R_CANFD_CFDRMDF_1_OFFSET(m)               (0x00000930 + ((m) * 0x0000004c))  /* RX Message Buffer Data Field 1 Registers */
/* CFDRMDF%s_2 Registers (0-7) */
#define R_CANFD_CFDRMDF_2_OFFSET(m)               (0x00000934 + ((m) * 0x0000004c))  /* RX Message Buffer Data Field 2 Registers */
/* CFDRMDF%s_3 Registers (0-7) */
#define R_CANFD_CFDRMDF_3_OFFSET(m)               (0x00000938 + ((m) * 0x0000004c))  /* RX Message Buffer Data Field 3 Registers */
/* CFDRMDF%s_4 Registers (0-7) */
#define R_CANFD_CFDRMDF_4_OFFSET(m)               (0x0000093c + ((m) * 0x0000004c))  /* RX Message Buffer Data Field 4 Registers */
/* CFDRMDF%s_5 Registers (0-7) */
#define R_CANFD_CFDRMDF_5_OFFSET(m)               (0x00000940 + ((m) * 0x0000004c))  /* RX Message Buffer Data Field 5 Registers */
/* CFDRMDF%s_6 Registers (0-7) */
#define R_CANFD_CFDRMDF_6_OFFSET(m)               (0x00000944 + ((m) * 0x0000004c))  /* RX Message Buffer Data Field 6 Registers */
/* CFDRMDF%s_7 Registers (0-7) */
#define R_CANFD_CFDRMDF_7_OFFSET(m)               (0x00000948 + ((m) * 0x0000004c))  /* RX Message Buffer Data Field 7 Registers */
/* CFDRMDF%s_8 Registers (0-7) */
#define R_CANFD_CFDRMDF_8_OFFSET(m)               (0x0000094c + ((m) * 0x0000004c))  /* RX Message Buffer Data Field 8 Registers */
/* CFDRMDF%s_9 Registers (0-7) */
#define R_CANFD_CFDRMDF_9_OFFSET(m)               (0x00000950 + ((m) * 0x0000004c))  /* RX Message Buffer Data Field 9 Registers */
/* CFDRMDF%s_10 Registers (0-7) */
#define R_CANFD_CFDRMDF_10_OFFSET(m)              (0x00000954 + ((m) * 0x0000004c))  /* RX Message Buffer Data Field 10 Registers */
/* CFDRMDF%s_11 Registers (0-7) */
#define R_CANFD_CFDRMDF_11_OFFSET(m)              (0x00000958 + ((m) * 0x0000004c))  /* RX Message Buffer Data Field 11 Registers */
/* CFDRMDF%s_12 Registers (0-7) */
#define R_CANFD_CFDRMDF_12_OFFSET(m)              (0x0000095c + ((m) * 0x0000004c))  /* RX Message Buffer Data Field 12 Registers */
/* CFDRMDF%s_13 Registers (0-7) */
#define R_CANFD_CFDRMDF_13_OFFSET(m)              (0x00000960 + ((m) * 0x0000004c))  /* RX Message Buffer Data Field 13 Registers */
/* CFDRMDF%s_14 Registers (0-7) */
#define R_CANFD_CFDRMDF_14_OFFSET(m)              (0x00000964 + ((m) * 0x0000004c))  /* RX Message Buffer Data Field 14 Registers */
/* CFDRMDF%s_15 Registers (0-7) */
#define R_CANFD_CFDRMDF_15_OFFSET(m)              (0x00000968 + ((m) * 0x0000004c))  /* RX Message Buffer Data Field 15 Registers */
/* CFDRMID%s Registers (8-15) */
/* CFDRMPTR%s Registers (8-15) */
/* CFDRMFDSTS%s Registers (8-15) */
/* CFDRMDF%s_0 Registers (8-15) */
/* CFDRMDF%s_1 Registers (8-15) */
/* CFDRMDF%s_2 Registers (8-15) */
/* CFDRMDF%s_3 Registers (8-15) */
/* CFDRMDF%s_4 Registers (8-15) */
/* CFDRMDF%s_5 Registers (8-15) */
/* CFDRMDF%s_6 Registers (8-15) */
/* CFDRMDF%s_7 Registers (8-15) */
/* CFDRMDF%s_8 Registers (8-15) */
/* CFDRMDF%s_9 Registers (8-15) */
/* CFDRMDF%s_10 Registers (8-15) */
/* CFDRMDF%s_11 Registers (8-15) */
/* CFDRMDF%s_12 Registers (8-15) */
/* CFDRMDF%s_13 Registers (8-15) */
/* CFDRMDF%s_14 Registers (8-15) */
/* CFDRMDF%s_15 Registers (8-15) */
/* CFDRMPTR%s Registers (16-23) */
/* CFDRMFDSTS%s Registers (16-23) */
/* CFDRMDF%s_0 Registers (16-23) */
/* CFDRMDF%s_1 Registers (16-23) */
/* CFDRMDF%s_2 Registers (16-23) */
/* CFDRMDF%s_3 Registers (16-23) */
/* CFDRMDF%s_4 Registers (16-23) */
/* CFDRMDF%s_5 Registers (16-23) */
/* CFDRMDF%s_6 Registers (16-23) */
/* CFDRMDF%s_7 Registers (16-23) */
/* CFDRMDF%s_8 Registers (16-23) */
/* CFDRMDF%s_9 Registers (16-23) */
/* CFDRMDF%s_10 Registers (16-23) */
/* CFDRMDF%s_11 Registers (16-23) */
/* CFDRMDF%s_12 Registers (16-23) */
/* CFDRMDF%s_13 Registers (16-23) */
/* CFDRMDF%s_14 Registers (16-23) */
/* CFDRMDF%s_15 Registers (16-23) */
/* CFDRMPTR%s Registers (24-31) */
/* CFDRMFDSTS%s Registers (24-31) */
/* CFDRMDF%s_0 Registers (24-31) */
/* CFDRMDF%s_1 Registers (24-31) */
/* CFDRMDF%s_2 Registers (24-31) */
/* CFDRMDF%s_3 Registers (24-31) */
/* CFDRMDF%s_4 Registers (24-31) */
/* CFDRMDF%s_5 Registers (24-31) */
/* CFDRMDF%s_6 Registers (24-31) */
/* CFDRMDF%s_7 Registers (24-31) */
/* CFDRMDF%s_8 Registers (24-31) */
/* CFDRMDF%s_9 Registers (24-31) */
/* CFDRMDF%s_10 Registers (24-31) */
/* CFDRMDF%s_11 Registers (24-31) */
/* CFDRMDF%s_12 Registers (24-31) */
/* CFDRMDF%s_13 Registers (24-31) */
/* CFDRMDF%s_14 Registers (24-31) */
/* CFDRMDF%s_15 Registers (24-31) */

/* CANFD Register Addresses */

#define R_CANFD_CFDC0NCFG(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDC0NCFG_OFFSET)
#define R_CANFD_CFDC0CTR(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDC0CTR_OFFSET)
#define R_CANFD_CFDC0STS(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDC0STS_OFFSET)
#define R_CANFD_CFDC0ERFL(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDC0ERFL_OFFSET)
#define R_CANFD_CFDGCFG(n)                        (R_CANFD_CH_BASE(n) + R_CANFD_CFDGCFG_OFFSET)
#define R_CANFD_CFDGCTR(n)                        (R_CANFD_CH_BASE(n) + R_CANFD_CFDGCTR_OFFSET)
#define R_CANFD_CFDGSTS(n)                        (R_CANFD_CH_BASE(n) + R_CANFD_CFDGSTS_OFFSET)
#define R_CANFD_CFDGERFL(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDGERFL_OFFSET)
#define R_CANFD_CFDGTSC(n)                        (R_CANFD_CH_BASE(n) + R_CANFD_CFDGTSC_OFFSET)
#define R_CANFD_CFDGAFLECTR(n)                    (R_CANFD_CH_BASE(n) + R_CANFD_CFDGAFLECTR_OFFSET)
#define R_CANFD_CFDGAFLCFG(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDGAFLCFG_OFFSET)
#define R_CANFD_CFDRMNB(n)                        (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMNB_OFFSET)
#define R_CANFD_CFDRMND(n)                        (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMND_OFFSET)
#define R_CANFD_CFDRMIEC(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMIEC_OFFSET)
#define R_CANFD_CFDRFCC(n, m)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFCC_OFFSET(m))
#define R_CANFD_CFDRFSTS(n, m)                    (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFSTS_OFFSET(m))
#define R_CANFD_CFDRFPCTR(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFPCTR_OFFSET(m))
#define R_CANFD_CFDCFCC(n)                        (R_CANFD_CH_BASE(n) + R_CANFD_CFDCFCC_OFFSET)
#define R_CANFD_CFDCFSTS(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDCFSTS_OFFSET)
#define R_CANFD_CFDCFPCTR(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDCFPCTR_OFFSET)
#define R_CANFD_CFDFESTS(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDFESTS_OFFSET)
#define R_CANFD_CFDFFSTS(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDFFSTS_OFFSET)
#define R_CANFD_CFDFMSTS(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDFMSTS_OFFSET)
#define R_CANFD_CFDRFISTS(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFISTS_OFFSET)
#define R_CANFD_CFDTMC(n, m)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMC_OFFSET(m))
#define R_CANFD_CFDTMSTS(n, m)                    (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMSTS_OFFSET(m))
#define R_CANFD_CFDTMTRSTS(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMTRSTS_OFFSET)
#define R_CANFD_CFDTMTARSTS(n)                    (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMTARSTS_OFFSET)
#define R_CANFD_CFDTMTCSTS(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMTCSTS_OFFSET)
#define R_CANFD_CFDTMTASTS(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMTASTS_OFFSET)
#define R_CANFD_CFDTMIEC(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMIEC_OFFSET)
#define R_CANFD_CFDTXQCC(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDTXQCC_OFFSET)
#define R_CANFD_CFDTXQSTS(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDTXQSTS_OFFSET)
#define R_CANFD_CFDTXQPCTR(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDTXQPCTR_OFFSET)
#define R_CANFD_CFDTHLCC(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDTHLCC_OFFSET)
#define R_CANFD_CFDTHLSTS(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDTHLSTS_OFFSET)
#define R_CANFD_CFDTHLPCTR(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDTHLPCTR_OFFSET)
#define R_CANFD_CFDGTINTSTS(n)                    (R_CANFD_CH_BASE(n) + R_CANFD_CFDGTINTSTS_OFFSET)
#define R_CANFD_CFDGTSTCFG(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDGTSTCFG_OFFSET)
#define R_CANFD_CFDGTSTCTR(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDGTSTCTR_OFFSET)
#define R_CANFD_CFDGFDCFG(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDGFDCFG_OFFSET)
#define R_CANFD_CFDGLOCKK(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDGLOCKK_OFFSET)
#define R_CANFD_CFDGAFLIGNENT(n)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDGAFLIGNENT_OFFSET)
#define R_CANFD_CFDGAFLIGNCTR(n)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDGAFLIGNCTR_OFFSET)
#define R_CANFD_CFDCDTCT(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDCDTCT_OFFSET)
#define R_CANFD_CFDCDTSTS(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDCDTSTS_OFFSET)
#define R_CANFD_CFDGRSTC(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDGRSTC_OFFSET)
#define R_CANFD_CFDC0DCFG(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDC0DCFG_OFFSET)
#define R_CANFD_CFDC0FDCFG(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDC0FDCFG_OFFSET)
#define R_CANFD_CFDC0FDCTR(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDC0FDCTR_OFFSET)
#define R_CANFD_CFDC0FDSTS(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDC0FDSTS_OFFSET)
#define R_CANFD_CFDC0FDCRC(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDC0FDCRC_OFFSET)
#define R_CANFD_CFDGAFLID(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDGAFLID_OFFSET(m))
#define R_CANFD_CFDGAFLM(n, m)                    (R_CANFD_CH_BASE(n) + R_CANFD_CFDGAFLM_OFFSET(m))
#define R_CANFD_CFDGAFLP0(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDGAFLP0_OFFSET(m))
#define R_CANFD_CFDGAFLP1(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDGAFLP1_OFFSET(m))
#define R_CANFD_CFDRPGACC(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRPGACC_OFFSET(m))
#define R_CANFD_CFDRFID(n, m)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFID_OFFSET(m))
#define R_CANFD_CFDRFPTR(n, m)                    (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFPTR_OFFSET(m))
#define R_CANFD_CFDRFFDSTS(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFFDSTS_OFFSET(m))
#define R_CANFD_CFDRFDF_0(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFDF_0_OFFSET(m))
#define R_CANFD_CFDRFDF_1(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFDF_1_OFFSET(m))
#define R_CANFD_CFDRFDF_2(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFDF_2_OFFSET(m))
#define R_CANFD_CFDRFDF_3(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFDF_3_OFFSET(m))
#define R_CANFD_CFDRFDF_4(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFDF_4_OFFSET(m))
#define R_CANFD_CFDRFDF_5(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFDF_5_OFFSET(m))
#define R_CANFD_CFDRFDF_6(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFDF_6_OFFSET(m))
#define R_CANFD_CFDRFDF_7(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFDF_7_OFFSET(m))
#define R_CANFD_CFDRFDF_8(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFDF_8_OFFSET(m))
#define R_CANFD_CFDRFDF_9(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFDF_9_OFFSET(m))
#define R_CANFD_CFDRFDF_10(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFDF_10_OFFSET(m))
#define R_CANFD_CFDRFDF_11(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFDF_11_OFFSET(m))
#define R_CANFD_CFDRFDF_12(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFDF_12_OFFSET(m))
#define R_CANFD_CFDRFDF_13(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFDF_13_OFFSET(m))
#define R_CANFD_CFDRFDF_14(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFDF_14_OFFSET(m))
#define R_CANFD_CFDRFDF_15(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFDF_15_OFFSET(m))
#define R_CANFD_CFDCFID(n)                        (R_CANFD_CH_BASE(n) + R_CANFD_CFDCFID_OFFSET)
#define R_CANFD_CFDCFPTR(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDCFPTR_OFFSET)
#define R_CANFD_CFDCFFDCSTS(n)                    (R_CANFD_CH_BASE(n) + R_CANFD_CFDCFFDCSTS_OFFSET)
#define R_CANFD_CFDCFDF(n, m)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDCFDF_OFFSET(m))
#define R_CANFD_CFDTMID(n, m)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMID_OFFSET(m))
#define R_CANFD_CFDTMPTR(n, m)                    (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMPTR_OFFSET(m))
#define R_CANFD_CFDTMFDCTR(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMFDCTR_OFFSET(m))
#define R_CANFD_CFDTMDF_0(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMDF_0_OFFSET(m))
#define R_CANFD_CFDTMDF_1(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMDF_1_OFFSET(m))
#define R_CANFD_CFDTMDF_2(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMDF_2_OFFSET(m))
#define R_CANFD_CFDTMDF_3(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMDF_3_OFFSET(m))
#define R_CANFD_CFDTMDF_4(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMDF_4_OFFSET(m))
#define R_CANFD_CFDTMDF_5(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMDF_5_OFFSET(m))
#define R_CANFD_CFDTMDF_6(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMDF_6_OFFSET(m))
#define R_CANFD_CFDTMDF_7(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMDF_7_OFFSET(m))
#define R_CANFD_CFDTMDF_8(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMDF_8_OFFSET(m))
#define R_CANFD_CFDTMDF_9(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMDF_9_OFFSET(m))
#define R_CANFD_CFDTMDF_10(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMDF_10_OFFSET(m))
#define R_CANFD_CFDTMDF_11(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMDF_11_OFFSET(m))
#define R_CANFD_CFDTMDF_12(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMDF_12_OFFSET(m))
#define R_CANFD_CFDTMDF_13(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMDF_13_OFFSET(m))
#define R_CANFD_CFDTMDF_14(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMDF_14_OFFSET(m))
#define R_CANFD_CFDTMDF_15(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMDF_15_OFFSET(m))
#define R_CANFD_CFDTHLACC0(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDTHLACC0_OFFSET)
#define R_CANFD_CFDTHLACC1(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDTHLACC1_OFFSET)
#define R_CANFD_CFDRMID(n, m)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMID_OFFSET(m))
#define R_CANFD_CFDRMPTR(n, m)                    (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMPTR_OFFSET(m))
#define R_CANFD_CFDRMFDSTS(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMFDSTS_OFFSET(m))
#define R_CANFD_CFDRMDF_0(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMDF_0_OFFSET(m))
#define R_CANFD_CFDRMDF_1(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMDF_1_OFFSET(m))
#define R_CANFD_CFDRMDF_2(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMDF_2_OFFSET(m))
#define R_CANFD_CFDRMDF_3(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMDF_3_OFFSET(m))
#define R_CANFD_CFDRMDF_4(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMDF_4_OFFSET(m))
#define R_CANFD_CFDRMDF_5(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMDF_5_OFFSET(m))
#define R_CANFD_CFDRMDF_6(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMDF_6_OFFSET(m))
#define R_CANFD_CFDRMDF_7(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMDF_7_OFFSET(m))
#define R_CANFD_CFDRMDF_8(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMDF_8_OFFSET(m))
#define R_CANFD_CFDRMDF_9(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMDF_9_OFFSET(m))
#define R_CANFD_CFDRMDF_10(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMDF_10_OFFSET(m))
#define R_CANFD_CFDRMDF_11(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMDF_11_OFFSET(m))
#define R_CANFD_CFDRMDF_12(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMDF_12_OFFSET(m))
#define R_CANFD_CFDRMDF_13(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMDF_13_OFFSET(m))
#define R_CANFD_CFDRMDF_14(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMDF_14_OFFSET(m))
#define R_CANFD_CFDRMDF_15(n, m)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMDF_15_OFFSET(m))

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
#  define R_CANFD_CFDRFCC_RFDC_100                        (4 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* FIFO Depth = 32 essages */
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
#define R_CANFD_CFDRFSTS_RFMC_MASK                0xff00

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

#define R_CANFD_CFDCFCC_CFM_SHIFT                 (8)  /* Common FIFO Mode */
#define R_CANFD_CFDCFCC_CFM_MASK                  0x300
#  define R_CANFD_CFDCFCC_CFM_0                           (0 << R_CANFD_CFDCFCC_CFM_SHIFT)  /* RX FIFO mode */
#  define R_CANFD_CFDCFCC_CFM_1                           (1 << R_CANFD_CFDCFCC_CFM_SHIFT)  /* TX FIFO mode */

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
#define R_CANFD_CFDCFCC_CFTML_MASK                0x1f0000

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
#define R_CANFD_CFDCFSTS_CFMC_MASK                0xff00

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

#define R_CANFD_CFDTMTRSTS_CFDTMTRSTSG_SHIFT      (0)  /* TX Message Buffer Transmission Request Status */
#define R_CANFD_CFDTMTRSTS_CFDTMTRSTSG_MASK       0xf

/* CFDTMTARSTS Register bit definitions */
#define R_CANFD_CFDTMTARSTS_CFDTMTARSTS_SHIFT     (0)  /* TX Message Buffer Transmission Abort Request Status */
#define R_CANFD_CFDTMTARSTS_CFDTMTARSTS_MASK      0xf
#  define R_CANFD_CFDTMTARSTS_CFDTMTARSTS_0               (0 << R_CANFD_CFDTMTARSTS_CFDTMTARSTS_SHIFT)  /* Transmission abort not requested for corresponding TX message buffer */
#  define R_CANFD_CFDTMTARSTS_CFDTMTARSTS_1               (1 << R_CANFD_CFDTMTARSTS_CFDTMTARSTS_SHIFT)  /* Transmission abort requested for corresponding TX message buffer */

#define R_CANFD_CFDTMTARSTS_CFDTMTARSTSG_SHIFT    (0)  /* TX Message Buffer Transmission abort Request Status */
#define R_CANFD_CFDTMTARSTS_CFDTMTARSTSG_MASK     0xf

/* CFDTMTCSTS Register bit definitions */
#define R_CANFD_CFDTMTCSTS_CFDTMTCSTS_SHIFT       (0)  /* TX Message Buffer Transmission Completion Status */
#define R_CANFD_CFDTMTCSTS_CFDTMTCSTS_MASK        0xf
#  define R_CANFD_CFDTMTCSTS_CFDTMTCSTS_0                 (0 << R_CANFD_CFDTMTCSTS_CFDTMTCSTS_SHIFT)  /* Transmission not complete for corresponding TX message buffer */
#  define R_CANFD_CFDTMTCSTS_CFDTMTCSTS_1                 (1 << R_CANFD_CFDTMTCSTS_CFDTMTCSTS_SHIFT)  /* Transmission completed for corresponding TX message buffer */

#define R_CANFD_CFDTMTCSTS_CFDTMTCSTSG_SHIFT      (0)  /* TX Message Buffer Transmission Completion Status */
#define R_CANFD_CFDTMTCSTS_CFDTMTCSTSG_MASK       0xf

/* CFDTMTASTS Register bit definitions */
#define R_CANFD_CFDTMTASTS_CFDTMTASTS_SHIFT       (0)  /* TX Message Buffer Transmission Abort Status */
#define R_CANFD_CFDTMTASTS_CFDTMTASTS_MASK        0xf
#  define R_CANFD_CFDTMTASTS_CFDTMTASTS_0                 (0 << R_CANFD_CFDTMTASTS_CFDTMTASTS_SHIFT)  /* Transmission not aborted for corresponding TX message buffer */
#  define R_CANFD_CFDTMTASTS_CFDTMTASTS_1                 (1 << R_CANFD_CFDTMTASTS_CFDTMTASTS_SHIFT)  /* Transmission aborted for corresponding TX message buffer */

#define R_CANFD_CFDTMTASTS_CFDTMTASTSG_SHIFT      (0)  /* TX Message Buffer Transmission abort Status */
#define R_CANFD_CFDTMTASTS_CFDTMTASTSG_MASK       0xf

/* CFDTMIEC Register bit definitions */
#define R_CANFD_CFDTMIEC_TMIEG_SHIFT              (0)  /* TX Message Buffer Interrupt Enable */
#define R_CANFD_CFDTMIEC_TMIEG_MASK               0xf
#  define R_CANFD_CFDTMIEC_TMIEG_0                        (0 << R_CANFD_CFDTMIEC_TMIEG_SHIFT)  /* TX message buffer interrupt disabled for corresponding TX message buffer */
#  define R_CANFD_CFDTMIEC_TMIEG_1                        (1 << R_CANFD_CFDTMIEC_TMIEG_SHIFT)  /* TX message buffer interrupt enabled for corresponding TX message buffer */

#define R_CANFD_CFDTMIEC_TMIEG_SHIFT              (0)  /* TX Message Buffer Interrupt Enable */
#define R_CANFD_CFDTMIEC_TMIEG_MASK               0xf

/* CFDTXQCC Register bit definitions */
#define R_CANFD_CFDTXQCC_TXQE                     (1 << 0)  /* TX Queue Enable */

#define R_CANFD_CFDTXQCC_TXQTXIE                  (1 << 5)  /* TX Queue TX Interrupt Enable */

#define R_CANFD_CFDTXQCC_TXQIM                    (1 << 7)  /* TX Queue Interrupt Mode */

#define R_CANFD_CFDTXQCC_TXQDC_SHIFT              (8)  /* TX Queue Depth Configuration */
#define R_CANFD_CFDTXQCC_TXQDC_MASK               0x300
#  define R_CANFD_CFDTXQCC_TXQDC_0X00                     (0 << R_CANFD_CFDTXQCC_TXQDC_SHIFT)  /* 0 messages */
#  define R_CANFD_CFDTXQCC_TXQDC_0X01                     (1 << R_CANFD_CFDTXQCC_TXQDC_SHIFT)  /* Reserved */
#  define R_CANFD_CFDTXQCC_TXQDC_0X10                     (2 << R_CANFD_CFDTXQCC_TXQDC_SHIFT)  /* 3 messages */
#  define R_CANFD_CFDTXQCC_TXQDC_0X11                     (3 << R_CANFD_CFDTXQCC_TXQDC_SHIFT)  /* 4 messages */

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
#define R_CANFD_CFDTHLSTS_THLMC_MASK              0x3f00

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

#define R_CANFD_CFDCDTSTS_CFDMASTS0               (1 << 8)  /* DMA Transfer Status only for Common FIFO 0 of channel 0 */

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


/* Maximum number of channels */

#define CANFD_MAX_CHANNELS    64

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_CANFD_H */

/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_sdhi.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SDHI_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SDHI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SDHI Base Address */
#ifndef R_SDHI_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_SDHI_BASE           0x40252000
#else
#define R_SDHI_BASE           0x50252000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_SDHI_CH_STRIDE    0x00000400
#define R_SDHI_CH_BASE(ch)   (R_SDHI_BASE + ((uint32_t)(ch) * R_SDHI_CH_STRIDE))

/* SDHI Register Offsets */

#define R_SDHI_SD_CMD_OFFSET                      0x00000000  /* Command Type Register */
#define R_SDHI_SD_ARG_OFFSET                      0x00000008  /* SD Command Argument Register */
#define R_SDHI_SD_ARG1_OFFSET                     0x0000000c  /* SD Command Argument Register 1 */
#define R_SDHI_SD_STOP_OFFSET                     0x00000010  /* Data Stop Register */
#define R_SDHI_SD_SECCNT_OFFSET                   0x00000014  /* Block Count Register */
#define R_SDHI_SD_RSP10_OFFSET                    0x00000018  /* SD Card Response Register 10 */
#define R_SDHI_SD_RSP1_OFFSET                     0x0000001c  /* SD Card Response Register 1 */
#define R_SDHI_SD_RSP32_OFFSET                    0x00000020  /* SD Card Response Register 32 */
#define R_SDHI_SD_RSP3_OFFSET                     0x00000024  /* SD Card Response Register 3 */
#define R_SDHI_SD_RSP54_OFFSET                    0x00000028  /* SD Card Response Register 54 */
#define R_SDHI_SD_RSP5_OFFSET                     0x0000002c  /* SD Card Response Register 5 */
#define R_SDHI_SD_RSP76_OFFSET                    0x00000030  /* SD Card Response Register 76 */
#define R_SDHI_SD_RSP7_OFFSET                     0x00000034  /* SD Card Response Register 7 */
#define R_SDHI_SD_INFO1_OFFSET                    0x00000038  /* SD Card Interrupt Flag Register 1 */
#define R_SDHI_SD_INFO2_OFFSET                    0x0000003c  /* SD Card Interrupt Flag Register 2 */
#define R_SDHI_SD_INFO1_MASK_OFFSET               0x00000040  /* SD_INFO1 Interrupt Mask Register */
#define R_SDHI_SD_INFO2_MASK_OFFSET               0x00000044  /* SD_INFO2 Interrupt Mask Register */
#define R_SDHI_SD_CLK_CTRL_OFFSET                 0x00000048  /* SD Clock Control Register */
#define R_SDHI_SD_SIZE_OFFSET                     0x0000004c  /* Transfer Data Length Register */
#define R_SDHI_SD_OPTION_OFFSET                   0x00000050  /* SD Card Access Control Option Register */
#define R_SDHI_SD_ERR_STS1_OFFSET                 0x00000058  /* SD Error Status Register 1 */
#define R_SDHI_SD_ERR_STS2_OFFSET                 0x0000005c  /* SD Error Status Register 2 */
#define R_SDHI_SD_BUF0_OFFSET                     0x00000060  /* SD Buffer Register */
#define R_SDHI_SDIO_MODE_OFFSET                   0x00000068  /* SDIO Mode Control Register */
#define R_SDHI_SDIO_INFO1_OFFSET                  0x0000006c  /* SDIO Interrupt Flag Register 1 */
#define R_SDHI_SDIO_INFO1_MASK_OFFSET             0x00000070  /* SDIO_INFO1 Interrupt Mask Register */
#define R_SDHI_SD_DMAEN_OFFSET                    0x000001b0  /* DMA Mode Enable Register */
#define R_SDHI_SOFT_RST_OFFSET                    0x000001c0  /* Software Reset Register */
#define R_SDHI_SDIF_MODE_OFFSET                   0x000001cc  /* SD Interface Mode Setting Register */
#define R_SDHI_EXT_SWAP_OFFSET                    0x000001e0  /* Swap Control Register */

/* SDHI Register Addresses */

#define R_SDHI_SD_CMD(n)                          (R_SDHI_CH_BASE(n) + R_SDHI_SD_CMD_OFFSET)
#define R_SDHI_SD_ARG(n)                          (R_SDHI_CH_BASE(n) + R_SDHI_SD_ARG_OFFSET)
#define R_SDHI_SD_ARG1(n)                         (R_SDHI_CH_BASE(n) + R_SDHI_SD_ARG1_OFFSET)
#define R_SDHI_SD_STOP(n)                         (R_SDHI_CH_BASE(n) + R_SDHI_SD_STOP_OFFSET)
#define R_SDHI_SD_SECCNT(n)                       (R_SDHI_CH_BASE(n) + R_SDHI_SD_SECCNT_OFFSET)
#define R_SDHI_SD_RSP10(n)                        (R_SDHI_CH_BASE(n) + R_SDHI_SD_RSP10_OFFSET)
#define R_SDHI_SD_RSP1(n)                         (R_SDHI_CH_BASE(n) + R_SDHI_SD_RSP1_OFFSET)
#define R_SDHI_SD_RSP32(n)                        (R_SDHI_CH_BASE(n) + R_SDHI_SD_RSP32_OFFSET)
#define R_SDHI_SD_RSP3(n)                         (R_SDHI_CH_BASE(n) + R_SDHI_SD_RSP3_OFFSET)
#define R_SDHI_SD_RSP54(n)                        (R_SDHI_CH_BASE(n) + R_SDHI_SD_RSP54_OFFSET)
#define R_SDHI_SD_RSP5(n)                         (R_SDHI_CH_BASE(n) + R_SDHI_SD_RSP5_OFFSET)
#define R_SDHI_SD_RSP76(n)                        (R_SDHI_CH_BASE(n) + R_SDHI_SD_RSP76_OFFSET)
#define R_SDHI_SD_RSP7(n)                         (R_SDHI_CH_BASE(n) + R_SDHI_SD_RSP7_OFFSET)
#define R_SDHI_SD_INFO1(n)                        (R_SDHI_CH_BASE(n) + R_SDHI_SD_INFO1_OFFSET)
#define R_SDHI_SD_INFO2(n)                        (R_SDHI_CH_BASE(n) + R_SDHI_SD_INFO2_OFFSET)
#define R_SDHI_SD_INFO1_MASK(n)                   (R_SDHI_CH_BASE(n) + R_SDHI_SD_INFO1_MASK_OFFSET)
#define R_SDHI_SD_INFO2_MASK(n)                   (R_SDHI_CH_BASE(n) + R_SDHI_SD_INFO2_MASK_OFFSET)
#define R_SDHI_SD_CLK_CTRL(n)                     (R_SDHI_CH_BASE(n) + R_SDHI_SD_CLK_CTRL_OFFSET)
#define R_SDHI_SD_SIZE(n)                         (R_SDHI_CH_BASE(n) + R_SDHI_SD_SIZE_OFFSET)
#define R_SDHI_SD_OPTION(n)                       (R_SDHI_CH_BASE(n) + R_SDHI_SD_OPTION_OFFSET)
#define R_SDHI_SD_ERR_STS1(n)                     (R_SDHI_CH_BASE(n) + R_SDHI_SD_ERR_STS1_OFFSET)
#define R_SDHI_SD_ERR_STS2(n)                     (R_SDHI_CH_BASE(n) + R_SDHI_SD_ERR_STS2_OFFSET)
#define R_SDHI_SD_BUF0(n)                         (R_SDHI_CH_BASE(n) + R_SDHI_SD_BUF0_OFFSET)
#define R_SDHI_SDIO_MODE(n)                       (R_SDHI_CH_BASE(n) + R_SDHI_SDIO_MODE_OFFSET)
#define R_SDHI_SDIO_INFO1(n)                      (R_SDHI_CH_BASE(n) + R_SDHI_SDIO_INFO1_OFFSET)
#define R_SDHI_SDIO_INFO1_MASK(n)                 (R_SDHI_CH_BASE(n) + R_SDHI_SDIO_INFO1_MASK_OFFSET)
#define R_SDHI_SD_DMAEN(n)                        (R_SDHI_CH_BASE(n) + R_SDHI_SD_DMAEN_OFFSET)
#define R_SDHI_SOFT_RST(n)                        (R_SDHI_CH_BASE(n) + R_SDHI_SOFT_RST_OFFSET)
#define R_SDHI_SDIF_MODE(n)                       (R_SDHI_CH_BASE(n) + R_SDHI_SDIF_MODE_OFFSET)
#define R_SDHI_EXT_SWAP(n)                        (R_SDHI_CH_BASE(n) + R_SDHI_EXT_SWAP_OFFSET)

/* Register bit definitions */
/* SD_CMD Register bit definitions */
#define R_SDHI_SD_CMD_CMD12AT_SHIFT               (14)  /* Multiple Block Transfer Mode (enabled at multiple block transfer) */
#define R_SDHI_SD_CMD_CMD12AT_MASK                0xc000
#  define R_SDHI_SD_CMD_CMD12AT_00                        (0 << R_SDHI_SD_CMD_CMD12AT_SHIFT)  /* CMD12 is automatically issued at multiple block transfer. */
#  define R_SDHI_SD_CMD_CMD12AT_01                        (1 << R_SDHI_SD_CMD_CMD12AT_SHIFT)  /* CMD12 is not automatically issued at multiple block transfer. */
#  define R_SDHI_SD_CMD_CMD12AT_10                        (2 << R_SDHI_SD_CMD_CMD12AT_SHIFT)  /* Setting prohibited */
#  define R_SDHI_SD_CMD_CMD12AT_11                        (3 << R_SDHI_SD_CMD_CMD12AT_SHIFT)  /* Setting prohibited */

#define R_SDHI_SD_CMD_TRSTP                       (1 << 13)  /* Single/Multiple Block Transfer (enabled when the command with data is handled) */

#define R_SDHI_SD_CMD_CMDRW                       (1 << 12)  /* Write/Read Mode (enabled when the command with data is handled) */

#define R_SDHI_SD_CMD_CMDTP                       (1 << 11)  /* Data Mode (Command Type) */

#define R_SDHI_SD_CMD_RSPTP_SHIFT                 (8)  /* Mode/Response TypeNOTE: As some commands cannot be used in normal mode, see section 1.4.10, Example of SD_CMD Register Setting to select mode/response type. */
#define R_SDHI_SD_CMD_RSPTP_MASK                  0x700
#  define R_SDHI_SD_CMD_RSPTP_000                         (0 << R_SDHI_SD_CMD_RSPTP_SHIFT)  /* Normal mode The response type and the transfer mode are selected by SD_CMD[7:0], and the SD_CMD[15:11] setting is disabled.  */
#  define R_SDHI_SD_CMD_RSPTP_011                         (3 << R_SDHI_SD_CMD_RSPTP_SHIFT)  /* Expansion mode and no response */
#  define R_SDHI_SD_CMD_RSPTP_100                         (4 << R_SDHI_SD_CMD_RSPTP_SHIFT)  /* Expansion mode and R1, R5, R6, or R7 response */
#  define R_SDHI_SD_CMD_RSPTP_101                         (5 << R_SDHI_SD_CMD_RSPTP_SHIFT)  /* Expansion mode and R1b response */
#  define R_SDHI_SD_CMD_RSPTP_110                         (6 << R_SDHI_SD_CMD_RSPTP_SHIFT)  /* Expansion mode and R2 response */
#  define R_SDHI_SD_CMD_RSPTP_111                         (7 << R_SDHI_SD_CMD_RSPTP_SHIFT)  /* Expansion mode and R3 or R4 response */

#define R_SDHI_SD_CMD_ACMD_SHIFT                  (6)  /* Command Type Select */
#define R_SDHI_SD_CMD_ACMD_MASK                   0xc0
#  define R_SDHI_SD_CMD_ACMD_00                           (0 << R_SDHI_SD_CMD_ACMD_SHIFT)  /* CMD */
#  define R_SDHI_SD_CMD_ACMD_01                           (1 << R_SDHI_SD_CMD_ACMD_SHIFT)  /* ACMD */

#define R_SDHI_SD_CMD_CMDIDX_SHIFT                (0)  /* Command IndexThese bits specify Command Format[45:40] (command index).[Examples]CMD6: SD_CMD[7:0] = 8'b00_000110CMD18: SD_CMD[7:0] = 8'b00_010010ACMD13: SD_CMD[7:0] = 8'b01_001101 */
#define R_SDHI_SD_CMD_CMDIDX_MASK                 0x3f

/* SD_ARG Register bit definitions */
#define R_SDHI_SD_ARG_SD_ARG_SHIFT                (0)  /* Argument RegisterSet command format[39:8] (argument) */
#define R_SDHI_SD_ARG_SD_ARG_MASK                 0xffffffff

/* SD_ARG1 Register bit definitions */
#define R_SDHI_SD_ARG1_SD_ARG1_SHIFT              (0)  /* Argument Register 1Set command format[39:24] (argument) */
#define R_SDHI_SD_ARG1_SD_ARG1_MASK               0xffff

/* SD_STOP Register bit definitions */
#define R_SDHI_SD_STOP_SEC                        (1 << 8)  /* Block Count EnableSet SEC to 1 at multiple block transfer.When SD_CMD is set as follows to start the command sequence while SEC is set to 1, CMD12 is automatically issued to stop multi-block transfer with the number of blocks which is set to SD_SECCNT.1. CMD18 or CMD25 in normal mode (SD_CMD[10:8] = 000)2. SD_CMD[15:13] = 001 in extended mode (CMD12 is automatically issued, multiple block transfer)When the command sequence is halted because of a communications error or timeout, CMD12 is not automatically issued.NOTE: Do not change the value of this bit when the CBSY bit in SD_INFO2 is set to 1. */

#define R_SDHI_SD_STOP_STP                        (1 << 0)  /* Stop- When STP is set to 1 during multiple block transfer, CMD12 is issued to halt the transfer through the SD host interface.However, if a command sequence is halted because of a communications error or timeout, CMD12 is not issued. Although continued buffer access is possible even after STP has been set to 1, the buffer access error bit (ERR5 or ERR4) in SD_INFO2 will be set accordingly.- When STP has been set to 1 during transfer for single block write, the access end flag is set when SD_BUF becomes empty, and CMD12 is not issued. If SD_BUF does contain data, the access end flag is set on completion of reception of the busy state without CMD12 having been issued.- When STP has been set to 1 during transfer for single block read, the access end flag is set immediately after setting of the STP bit and CMD12 is not issued.- When STP is set to 1 during reception of the busy state after an R1b response, the access end flag is set on completion of reception of the busy state without CMD12 having been issued.- When STP is set to 1 after a command sequence has been completed, CMD12 is not issued and the access end flag is not set.- Set STP to 1 after the response end flag has been set.- Set STP to 0 after the response end flag has been set. */

/* SD_SECCNT Register bit definitions */
#define R_SDHI_SD_SECCNT_SD_SECCNT_SHIFT          (0)  /* Number of Transfer BlocksNOTE: Do not change the value of this bit when the CBSY bit in SD_INFO2 is set to 1. */
#define R_SDHI_SD_SECCNT_SD_SECCNT_MASK           0xffffffff

/* SD_RSP10 Register bit definitions */
#define R_SDHI_SD_RSP10_SD_RSP10_SHIFT            (0)  /* Store the response from the SD card/MMC */
#define R_SDHI_SD_RSP10_SD_RSP10_MASK             0xffffffff

/* SD_RSP1 Register bit definitions */
#define R_SDHI_SD_RSP1_SD_RSP1_SHIFT              (0)  /* Store the response from the SD card/MMC */
#define R_SDHI_SD_RSP1_SD_RSP1_MASK               0xffff

/* SD_RSP32 Register bit definitions */
#define R_SDHI_SD_RSP32_SD_RSP32_SHIFT            (0)  /* Store the response from the SD card/MMC */
#define R_SDHI_SD_RSP32_SD_RSP32_MASK             0xffffffff

/* SD_RSP3 Register bit definitions */
#define R_SDHI_SD_RSP3_SD_RSP3_SHIFT              (0)  /* Store the response from the SD card/MMC */
#define R_SDHI_SD_RSP3_SD_RSP3_MASK               0xffff

/* SD_RSP54 Register bit definitions */
#define R_SDHI_SD_RSP54_SD_RSP54_SHIFT            (0)  /* Store the response from the SD card/MMC */
#define R_SDHI_SD_RSP54_SD_RSP54_MASK             0xffffffff

/* SD_RSP5 Register bit definitions */
#define R_SDHI_SD_RSP5_SD_RSP5_SHIFT              (0)  /* Store the response from the SD card/MMC */
#define R_SDHI_SD_RSP5_SD_RSP5_MASK               0xffff

/* SD_RSP76 Register bit definitions */
#define R_SDHI_SD_RSP76_SD_RSP76_SHIFT            (0)  /* Store the response from the SD card/MMC */
#define R_SDHI_SD_RSP76_SD_RSP76_MASK             0xffffff

/* SD_RSP7 Register bit definitions */
#define R_SDHI_SD_RSP7_SD_RSP7_SHIFT              (0)  /* Store the response from the SD card/MMC */
#define R_SDHI_SD_RSP7_SD_RSP7_MASK               0xff

/* SD_INFO1 Register bit definitions */
#define R_SDHI_SD_INFO1_SDD3MON                   (1 << 10)  /* Inticates the SDnDAT3 State */

#define R_SDHI_SD_INFO1_SDD3IN                    (1 << 9)  /* SDnDAT3 Card Insertion */

#define R_SDHI_SD_INFO1_SDD3RM                    (1 << 8)  /* SDnDAT3 Card Removal */

#define R_SDHI_SD_INFO1_SDWPMON                   (1 << 7)  /* Indicates the SDnWP state */

#define R_SDHI_SD_INFO1_SDCDMON                   (1 << 5)  /* Indicates the SDnCD state */

#define R_SDHI_SD_INFO1_SDCDIN                    (1 << 4)  /* SDnCD Card Insertion */

#define R_SDHI_SD_INFO1_SDCDRM                    (1 << 3)  /* SDnCD  Card Removal */

#define R_SDHI_SD_INFO1_ACEND                     (1 << 2)  /* Access End */

#define R_SDHI_SD_INFO1_RSPEND                    (1 << 0)  /* Response End Detection */

/* SD_INFO2 Register bit definitions */
#define R_SDHI_SD_INFO2_ILA                       (1 << 15)  /* Illegal Access Error */

#define R_SDHI_SD_INFO2_CBSY                      (1 << 14)  /* Command Type Register Busy */

#define R_SDHI_SD_INFO2_SD_CLK_CTRLEN             (1 << 13)  /* When a command sequence is started by writing to SD_CMD, the CBSY bit is set to 1 and, at the same time, the SCLKDIVEN bit is set to 0. The SCLKDIVEN bit is set to 1 after 8 cycles of SDCLK have elapsed after setting of the CBSY bit to 0 due to completion of the command sequence. */

#define R_SDHI_SD_INFO2_BWE                       (1 << 9)  /* SD_BUF Write Enable */

#define R_SDHI_SD_INFO2_BRE                       (1 << 8)  /* SD_BUF Read Enable */

#define R_SDHI_SD_INFO2_SDD0MON                   (1 << 7)  /* SDDAT0Indicates the SDDAT0 state of the port specified by SD_PORTSEL. */

#define R_SDHI_SD_INFO2_RSPTO                     (1 << 6)  /* Response Timeout */

#define R_SDHI_SD_INFO2_ILR                       (1 << 5)  /* SD_BUF Illegal Read Access */

#define R_SDHI_SD_INFO2_ILW                       (1 << 4)  /* SD_BUF Illegal Write Access */

#define R_SDHI_SD_INFO2_DTO                       (1 << 3)  /* Data Timeout  */

#define R_SDHI_SD_INFO2_ENDE                      (1 << 2)  /* END Error */

#define R_SDHI_SD_INFO2_CRCE                      (1 << 1)  /* CRC Error */

#define R_SDHI_SD_INFO2_CMDE                      (1 << 0)  /* Command Error */

/* SD_INFO1_MASK Register bit definitions */
#define R_SDHI_SD_INFO1_MASK_SDD3INM              (1 << 9)  /* SDnDAT3 Card Insertion Interrupt Request Mask */

#define R_SDHI_SD_INFO1_MASK_SDD3RMM              (1 << 8)  /* SDnDAT3 Card Removal Interrupt Request Mask */

#define R_SDHI_SD_INFO1_MASK_SDCDINM              (1 << 4)  /* SDnCD card Insertion Interrupt Request Mask */

#define R_SDHI_SD_INFO1_MASK_SDCDRMM              (1 << 3)  /* SDnCD card Removal Interrupt Request Mask */

#define R_SDHI_SD_INFO1_MASK_ACENDM               (1 << 2)  /*  Access End Interrupt Request Mask */

#define R_SDHI_SD_INFO1_MASK_RSPENDM              (1 << 0)  /*  Response End Interrupt Request Mask */

/* SD_INFO2_MASK Register bit definitions */
#define R_SDHI_SD_INFO2_MASK_ILAM                 (1 << 15)  /* Illegal Access Error Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_BWEM                 (1 << 9)  /* BWE Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_BREM                 (1 << 8)  /* BRE Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_RSPTOM               (1 << 6)  /*  Response Timeout Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_ILRM                 (1 << 5)  /* SD_BUF Register Illegal Read Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_ILWM                 (1 << 4)  /* SD_BUF Register Illegal Write Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_DTOM                 (1 << 3)  /*  Data Timeout Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_ENDEM                (1 << 2)  /*  End Bit Error Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_CRCEM                (1 << 1)  /* CRC Error Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_CMDEM                (1 << 0)  /* Command Error Interrupt Request Mask */

/* SD_CLK_CTRL Register bit definitions */
#define R_SDHI_SD_CLK_CTRL_CLKCTRLEN              (1 << 9)  /* SD/MMC Clock Output Automatic Control Enable */

#define R_SDHI_SD_CLK_CTRL_CLKEN                  (1 << 8)  /* SD/MMC Clock Output Control Enable */

#define R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT           (0)  /* SDHI Clock Frequency Select */
#define R_SDHI_SD_CLK_CTRL_CLKSEL_MASK            0xff
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X00                  (0 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKA divided by 2 */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X01                  (1 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKA divided by 4 */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X02                  (2 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKA divided by 8 */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X04                  (4 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKA divided by 16 */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X08                  (8 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKA divided by 32 */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X10                  (16 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKA divided by 64 */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X20                  (32 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKA divided by 128 */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X40                  (64 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKA divided by 256 */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X80                  (128 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKA divided by 512 */

/* SD_SIZE Register bit definitions */
#define R_SDHI_SD_SIZE_LEN_SHIFT                  (0)  /* Transfer Data SizeThese bits specify a size between 1 and 512 bytes for the transfer of single blocks.In cases of multiple block transfer with automatic issuing of CMD12 (CMD18 and CMD25), the only specifiable transfer data size is 512 bytes. Furthermore, in cases of multiple block transfer without automatic issuing of CMD12, as well as 512 bytes, 32, 64, 128, and 256 bytes are specifiable. However, in the reading of 32, 64, 128, and 256 bytes for the transfer of multiple blocks, this is restricted to multiple block transfer by CMD53.Additionally, if a command accompanies data transfer, do not set these bits to 0. */
#define R_SDHI_SD_SIZE_LEN_MASK                   0x3ff

/* SD_OPTION Register bit definitions */
#define R_SDHI_SD_OPTION_WIDTH                    (1 << 15)  /* Bus WidthNOTE: The initial value is applied at a reset and when the SOFT_RST.SDRST flag is 0. */

#define R_SDHI_SD_OPTION_WIDTH8                   (1 << 13)  /* Bus Widthsee b15, WIDTH bit */

#define R_SDHI_SD_OPTION_TOUTMASK                 (1 << 8)  /* Timeout MASKWhen timeout occurs in case of inactivating timeout, software reset should be executed to terminate command sequence. */

#define R_SDHI_SD_OPTION_TOP_SHIFT                (4)  /* Timeout Counter */
#define R_SDHI_SD_OPTION_TOP_MASK                 0xf0
#  define R_SDHI_SD_OPTION_TOP_1111                       (15 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* Setting prohibited */

#define R_SDHI_SD_OPTION_CTOP_SHIFT               (0)  /* Card Detect Time Counter */
#define R_SDHI_SD_OPTION_CTOP_MASK                0xf
#  define R_SDHI_SD_OPTION_CTOP_1111                      (15 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* Setting prohibited */

/* SD_ERR_STS1 Register bit definitions */
#define R_SDHI_SD_ERR_STS1_CRCTK_SHIFT            (12)  /* CRC Status TokenStore the CRC status token value (normal value is 010b) */
#define R_SDHI_SD_ERR_STS1_CRCTK_MASK             0x7000

#define R_SDHI_SD_ERR_STS1_CRCTKE                 (1 << 11)  /*  CRC Status Token Error */

#define R_SDHI_SD_ERR_STS1_RDCRCE                 (1 << 10)  /*  Read Data CRC Error */

#define R_SDHI_SD_ERR_STS1_RSPCRCE1               (1 << 9)  /*  Response CRC Error 1NOTE: In cases where CMD12 is issued by setting a command index in SD_CMD, this is indicated in RSPCRCE0. */

#define R_SDHI_SD_ERR_STS1_RSPCRCE0               (1 << 8)  /*  Response CRC Error 0NOTE: other than a response to a command issued within a command sequence */

#define R_SDHI_SD_ERR_STS1_CRCLENE                (1 << 5)  /*  CRC Status Token Length Error */

#define R_SDHI_SD_ERR_STS1_RDLENE                 (1 << 4)  /*  Read Data Length Error */

#define R_SDHI_SD_ERR_STS1_RSPLENE1               (1 << 3)  /*  Response Length Error 1NOTE: In cases where CMD12 is issued by setting a command index in SD_CMD, this is indicated in RSPLENE0. */

#define R_SDHI_SD_ERR_STS1_RSPLENE0               (1 << 2)  /*  Response Length Error 0NOTE: other than a response to a command issued within a command sequence */

#define R_SDHI_SD_ERR_STS1_CMDE1                  (1 << 1)  /* Command Error 1NOTE: In cases where CMD12 is issued by setting a command index in SD_CMD, this is Indicated in CMDE0. */

#define R_SDHI_SD_ERR_STS1_CMDE0                  (1 << 0)  /* Command Error 0NOTE: other than a response to a command issued within a command sequence */

/* SD_ERR_STS2 Register bit definitions */
#define R_SDHI_SD_ERR_STS2_CRCBSYTO               (1 << 6)  /* CRC Status Token Busy Timeout */

#define R_SDHI_SD_ERR_STS2_CRCTO                  (1 << 5)  /* CRC Status Token Timeout */

#define R_SDHI_SD_ERR_STS2_RDTO                   (1 << 4)  /* Read Data Timeout  */

#define R_SDHI_SD_ERR_STS2_BSYTO1                 (1 << 3)  /*  Busy Timeout 1 */

#define R_SDHI_SD_ERR_STS2_BSYTO0                 (1 << 2)  /*  Busy Timeout 0 */

#define R_SDHI_SD_ERR_STS2_RSPTO1                 (1 << 1)  /* Response Timeout 1  */

#define R_SDHI_SD_ERR_STS2_RSPTO0                 (1 << 0)  /* Response Timeout 0 */

/* SD_BUF0 Register bit definitions */
#define R_SDHI_SD_BUF0_SD_BUF_SHIFT               (0)  /* SD Buffer RegisterWhen writing to the SD card, the write data is written to this register. When reading from the SD card, the read data is read from this register. This register is internally connected to two 512-byte buffers.If both buffers are not empty when executing multiple block read, SD/MMC clock is stopped to suspend receiving data. When one of buffers is empty, SD/MMC clock is supplied to resume receiving data.   */
#define R_SDHI_SD_BUF0_SD_BUF_MASK                0xffffffff

/* SDIO_MODE Register bit definitions */
#define R_SDHI_SDIO_MODE_C52PUB                   (1 << 9)  /* SDIO None AbortNOTE: See manual  */

#define R_SDHI_SDIO_MODE_IOABT                    (1 << 8)  /* SDIO AbortNOTE: See manual */

#define R_SDHI_SDIO_MODE_RWREQ                    (1 << 2)  /* Read Wait Request */

#define R_SDHI_SDIO_MODE_INTEN                    (1 << 0)  /*  SDIO Mode */

/* SDIO_INFO1 Register bit definitions */
#define R_SDHI_SDIO_INFO1_EXWT                    (1 << 15)  /* EXWT Status FlagNOTE: See manual */

#define R_SDHI_SDIO_INFO1_EXPUB52                 (1 << 14)  /* EXPUB52 Status FlagNOTE: See manual */

#define R_SDHI_SDIO_INFO1_IOIRQ                   (1 << 0)  /* SDIO Interrupt Status */

/* SDIO_INFO1_MASK Register bit definitions */
#define R_SDHI_SDIO_INFO1_MASK_EXWTM              (1 << 15)  /* EXWT Interrupt Request Mask Control */

#define R_SDHI_SDIO_INFO1_MASK_EXPUB52M           (1 << 14)  /* EXPUB52 Interrupt Request Mask Control */

#define R_SDHI_SDIO_INFO1_MASK_IOIRQM             (1 << 0)  /* IOIRQ Interrupt Mask Control */

/* SD_DMAEN Register bit definitions */
#define R_SDHI_SD_DMAEN_DMAEN                     (1 << 1)  /* SD_BUF Read/Write DMA Transfer */

/* SOFT_RST Register bit definitions */
#define R_SDHI_SOFT_RST_SDRST                     (1 << 0)  /* Software Reset of SD I/F Unit */

/* SDIF_MODE Register bit definitions */
#define R_SDHI_SDIF_MODE_NOCHKCR                  (1 << 8)  /* CRC Check Mask (for MMC test commands) */

/* EXT_SWAP Register bit definitions */
#define R_SDHI_EXT_SWAP_BRSWP                     (1 << 7)  /* SD_BUF0 Swap Read */

#define R_SDHI_EXT_SWAP_BWSWP                     (1 << 6)  /* SD_BUF0 Swap Write */


/* Maximum number of channels */

#define SDHI_MAX_CHANNELS    2

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SDHI_H */

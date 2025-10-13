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
#define R_SDHI_SD_INFO1_MASK_OFFSET               0x00000040  /* SD INFO1 Interrupt Mask Register */
#define R_SDHI_SD_INFO2_MASK_OFFSET               0x00000044  /* SD INFO2 Interrupt Mask Register */
#define R_SDHI_SD_CLK_CTRL_OFFSET                 0x00000048  /* SD Clock Control Register */
#define R_SDHI_SD_SIZE_OFFSET                     0x0000004c  /* Transfer Data Length Register */
#define R_SDHI_SD_OPTION_OFFSET                   0x00000050  /* SD Card Access Control Option Register */
#define R_SDHI_SD_ERR_STS1_OFFSET                 0x00000058  /* SD Error Status Register 1 */
#define R_SDHI_SD_ERR_STS2_OFFSET                 0x0000005c  /* SD Error Status Register 2 */
#define R_SDHI_SD_BUF0_OFFSET                     0x00000060  /* SD Buffer Register */
#define R_SDHI_SDIO_MODE_OFFSET                   0x00000068  /* SDIO Mode Control Register */
#define R_SDHI_SDIO_INFO1_OFFSET                  0x0000006c  /* SDIO Interrupt Flag Register */
#define R_SDHI_SDIO_INFO1_MASK_OFFSET             0x00000070  /* SDIO INFO1 Interrupt Mask Register */
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
#define R_SDHI_SD_CMD_CMDIDX_SHIFT                (0)  /* Command Index Field Value Select */
#define R_SDHI_SD_CMD_CMDIDX_MASK                 0x3f
#  define R_SDHI_SD_CMD_CMDIDX_0X06                       (6 << R_SDHI_SD_CMD_CMDIDX_SHIFT)  /* CMD6 */
#  define R_SDHI_SD_CMD_CMDIDX_0X12                       (18 << R_SDHI_SD_CMD_CMDIDX_SHIFT)  /* CMD18 */
#  define R_SDHI_SD_CMD_CMDIDX_0X4D                       (77 << R_SDHI_SD_CMD_CMDIDX_SHIFT)  /* ACMD13 */

#define R_SDHI_SD_CMD_ACMD_SHIFT                  (6)  /* Command Type Select */
#define R_SDHI_SD_CMD_ACMD_MASK                   0xc0
#  define R_SDHI_SD_CMD_ACMD_00                           (0 << R_SDHI_SD_CMD_ACMD_SHIFT)  /* CMD */
#  define R_SDHI_SD_CMD_ACMD_01                           (1 << R_SDHI_SD_CMD_ACMD_SHIFT)  /* ACMD */

#define R_SDHI_SD_CMD_RSPTP_SHIFT                 (8)  /* Response Type Select */
#define R_SDHI_SD_CMD_RSPTP_MASK                  0x700
#  define R_SDHI_SD_CMD_RSPTP_000                         (0 << R_SDHI_SD_CMD_RSPTP_SHIFT)  /* Normal mode Depending on the command, the response type and transfer method are selected in the ACMD[1:0] and CMDIDX[5:0] bits. At this time, the values for bits 15 to 11 in this register are invalid.  */
#  define R_SDHI_SD_CMD_RSPTP_011                         (3 << R_SDHI_SD_CMD_RSPTP_SHIFT)  /* Extended mode and no response */
#  define R_SDHI_SD_CMD_RSPTP_100                         (4 << R_SDHI_SD_CMD_RSPTP_SHIFT)  /* Extended mode and R1, R5, R6, or R7 response */
#  define R_SDHI_SD_CMD_RSPTP_101                         (5 << R_SDHI_SD_CMD_RSPTP_SHIFT)  /* Extended mode and R1b response */
#  define R_SDHI_SD_CMD_RSPTP_110                         (6 << R_SDHI_SD_CMD_RSPTP_SHIFT)  /* Extended mode and R2 response */
#  define R_SDHI_SD_CMD_RSPTP_111                         (7 << R_SDHI_SD_CMD_RSPTP_SHIFT)  /* Extended mode and R3 or R4 response */

#define R_SDHI_SD_CMD_CMDTP                       (1 << 11)  /* Data Transfer Select */

#define R_SDHI_SD_CMD_CMDRW                       (1 << 12)  /* Data Transfer Direction Select */

#define R_SDHI_SD_CMD_TRSTP                       (1 << 13)  /* Block Transfer Select */

#define R_SDHI_SD_CMD_CMD12AT_SHIFT               (14)  /* CMD12 Automatic Issue Select */
#define R_SDHI_SD_CMD_CMD12AT_MASK                0xc000
#  define R_SDHI_SD_CMD_CMD12AT_00                        (0 << R_SDHI_SD_CMD_CMD12AT_SHIFT)  /* Automatically issue CMD12 during multiblock transfer */
#  define R_SDHI_SD_CMD_CMD12AT_01                        (1 << R_SDHI_SD_CMD_CMD12AT_SHIFT)  /* Do not automatically issue CMD12 during multiblock transfer */

/* SD_ARG Register bit definitions */
#define R_SDHI_SD_ARG_SD_ARG_SHIFT                (0)  /* Argument RegisterSet command format[39:8] (argument) */
#define R_SDHI_SD_ARG_SD_ARG_MASK                 0xffffffff

/* SD_ARG1 Register bit definitions */
#define R_SDHI_SD_ARG1_SD_ARG1_SHIFT              (0)  /* Argument Register 1Set command format[39:24] (argument) */
#define R_SDHI_SD_ARG1_SD_ARG1_MASK               0xffff

/* SD_STOP Register bit definitions */
#define R_SDHI_SD_STOP_STP                        (1 << 0)  /* Transfer Stop */

#define R_SDHI_SD_STOP_SEC                        (1 << 8)  /* Block Count Register Value Select */

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
#define R_SDHI_SD_RSP76_SD_RSP76_SHIFT            (0)  /* These bits store the response from the SD card/MMC. */
#define R_SDHI_SD_RSP76_SD_RSP76_MASK             0xffffff

/* SD_RSP7 Register bit definitions */
#define R_SDHI_SD_RSP7_SD_RSP7_SHIFT              (0)  /* These bits store the response from the SD card/MMC. */
#define R_SDHI_SD_RSP7_SD_RSP7_MASK               0xff

/* SD_INFO1 Register bit definitions */
#define R_SDHI_SD_INFO1_RSPEND                    (1 << 0)  /* Response End Detection Flag */

#define R_SDHI_SD_INFO1_ACEND                     (1 << 2)  /* Access End Detection Flag */

#define R_SDHI_SD_INFO1_SDCDRM                    (1 << 3)  /* SDnCD Removal Flag */

#define R_SDHI_SD_INFO1_SDCDIN                    (1 << 4)  /* SDnCD Insertion Flag */

#define R_SDHI_SD_INFO1_SDCDMON                   (1 << 5)  /* SDnCD Pin Monitor Flag */

#define R_SDHI_SD_INFO1_SDWPMON                   (1 << 7)  /* SDnWP Pin Monitor Flag */

#define R_SDHI_SD_INFO1_SDD3RM                    (1 << 8)  /* SDnDAT3 Removal Flag */

#define R_SDHI_SD_INFO1_SDD3IN                    (1 << 9)  /* SDnDAT3 Insertion Flag */

#define R_SDHI_SD_INFO1_SDD3MON                   (1 << 10)  /* SDnDAT3 Pin Monitor Flag */

/* SD_INFO2 Register bit definitions */
#define R_SDHI_SD_INFO2_CMDE                      (1 << 0)  /* Command Error Detection Flag */

#define R_SDHI_SD_INFO2_CRCE                      (1 << 1)  /* CRC Error Detection Flag */

#define R_SDHI_SD_INFO2_ENDE                      (1 << 2)  /* End Bit Error Detection Flag */

#define R_SDHI_SD_INFO2_DTO                       (1 << 3)  /* Data Timeout Detection Flag */

#define R_SDHI_SD_INFO2_ILW                       (1 << 4)  /* SD_BUF0 Illegal Write Access Detection Flag */

#define R_SDHI_SD_INFO2_ILR                       (1 << 5)  /* SD_BUF0 Illegal Read Access Detection Flag */

#define R_SDHI_SD_INFO2_RSPTO                     (1 << 6)  /* Response Timeout Detection Flag */

#define R_SDHI_SD_INFO2_SDD0MON                   (1 << 7)  /* SDnDAT0 Pin Status Flag */

#define R_SDHI_SD_INFO2_BRE                       (1 << 8)  /* SD_BUF0 Read Enable Flag */

#define R_SDHI_SD_INFO2_BWE                       (1 << 9)  /* SD_BUF0 Write Enable Flag */

#define R_SDHI_SD_INFO2_SD_CLK_CTRLEN             (1 << 13)  /* SD_CLK_CTRL Write Enable Flag */

#define R_SDHI_SD_INFO2_CBSY                      (1 << 14)  /* Command Sequence Status Flag */

#define R_SDHI_SD_INFO2_ILA                       (1 << 15)  /* Illegal Access Error Detection Flag */

/* SD_INFO1_MASK Register bit definitions */
#define R_SDHI_SD_INFO1_MASK_RSPENDM              (1 << 0)  /* Response End Interrupt Request Mask */

#define R_SDHI_SD_INFO1_MASK_ACENDM               (1 << 2)  /* Access End Interrupt Request Mask */

#define R_SDHI_SD_INFO1_MASK_SDCDRMM              (1 << 3)  /* SDnCD Removal Interrupt Request Mask */

#define R_SDHI_SD_INFO1_MASK_SDCDINM              (1 << 4)  /* SDnCD Insertion Interrupt Request Mask */

#define R_SDHI_SD_INFO1_MASK_SDD3RMM              (1 << 8)  /* SDnDAT3 Removal Interrupt Request Mask */

#define R_SDHI_SD_INFO1_MASK_SDD3INM              (1 << 9)  /* SDnDAT3 Insertion Interrupt Request Mask */

/* SD_INFO2_MASK Register bit definitions */
#define R_SDHI_SD_INFO2_MASK_CMDEM                (1 << 0)  /* Command Error Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_CRCEM                (1 << 1)  /* CRC Error Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_ENDEM                (1 << 2)  /* End Bit Error Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_DTOM                 (1 << 3)  /* Data Timeout Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_ILWM                 (1 << 4)  /* SD_BUF0 Register Illegal Write Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_ILRM                 (1 << 5)  /* SD_BUF0 Register Illegal Read Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_RSPTOM               (1 << 6)  /* Response Timeout Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_BREM                 (1 << 8)  /* BRE Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_BWEM                 (1 << 9)  /* BWE Interrupt Request Mask */

#define R_SDHI_SD_INFO2_MASK_ILAM                 (1 << 15)  /* Illegal Access Error Interrupt Request Mask */

/* SD_CLK_CTRL Register bit definitions */
#define R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT           (0)  /* SDHI Clock Frequency Select */
#define R_SDHI_SD_CLK_CTRL_CLKSEL_MASK            0xff
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0XFF                  (255 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKB */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X00                  (0 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKB/2 */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X01                  (1 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKB/4 */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X02                  (2 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X04                  (4 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKB/16 */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X08                  (8 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X10                  (16 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKB/64 */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X20                  (32 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKB/128 */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X40                  (64 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKB/256 */
#  define R_SDHI_SD_CLK_CTRL_CLKSEL_0X80                  (128 << R_SDHI_SD_CLK_CTRL_CLKSEL_SHIFT)  /* PCLKB/512 */

#define R_SDHI_SD_CLK_CTRL_CLKEN                  (1 << 8)  /* SD/MMC Clock Output Control */

#define R_SDHI_SD_CLK_CTRL_CLKCTRLEN              (1 << 9)  /* SD/MMC Clock Output Automatic Control Select */

/* SD_SIZE Register bit definitions */
#define R_SDHI_SD_SIZE_LEN_SHIFT                  (0)  /* Transfer Data Size Setting */
#define R_SDHI_SD_SIZE_LEN_MASK                   0x3ff

/* SD_OPTION Register bit definitions */
#define R_SDHI_SD_OPTION_CTOP_SHIFT               (0)  /* Card Detection Time Counter */
#define R_SDHI_SD_OPTION_CTOP_MASK                0xf
#  define R_SDHI_SD_OPTION_CTOP_0X0                       (0 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* PCLKB × 210 */
#  define R_SDHI_SD_OPTION_CTOP_0X1                       (1 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* PCLKB × 211 */
#  define R_SDHI_SD_OPTION_CTOP_0X2                       (2 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* PCLKB × 212 */
#  define R_SDHI_SD_OPTION_CTOP_0X3                       (3 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* PCLKB × 213 */
#  define R_SDHI_SD_OPTION_CTOP_0X4                       (4 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* PCLKB × 214 */
#  define R_SDHI_SD_OPTION_CTOP_0X5                       (5 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* PCLKB × 215 */
#  define R_SDHI_SD_OPTION_CTOP_0X6                       (6 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* PCLKB × 216 */
#  define R_SDHI_SD_OPTION_CTOP_0X7                       (7 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* PCLKB × 217 */
#  define R_SDHI_SD_OPTION_CTOP_0X8                       (8 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* PCLKB × 218 */
#  define R_SDHI_SD_OPTION_CTOP_0X9                       (9 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* PCLKB × 219 */
#  define R_SDHI_SD_OPTION_CTOP_0XA                       (10 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* PCLKB × 220 */
#  define R_SDHI_SD_OPTION_CTOP_0XB                       (11 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* PCLKB × 221 */
#  define R_SDHI_SD_OPTION_CTOP_0XC                       (12 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* PCLKB × 222 */
#  define R_SDHI_SD_OPTION_CTOP_0XD                       (13 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* PCLKB × 223 */
#  define R_SDHI_SD_OPTION_CTOP_0XE                       (14 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* PCLKB × 224 */
#  define R_SDHI_SD_OPTION_CTOP_0XF                       (15 << R_SDHI_SD_OPTION_CTOP_SHIFT)  /* Setting prohibited */

#define R_SDHI_SD_OPTION_TOP_SHIFT                (4)  /* Timeout Counter */
#define R_SDHI_SD_OPTION_TOP_MASK                 0xf0
#  define R_SDHI_SD_OPTION_TOP_0X0                        (0 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* SDHI clock × 213 */
#  define R_SDHI_SD_OPTION_TOP_0X1                        (1 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* SDHI clock × 214 */
#  define R_SDHI_SD_OPTION_TOP_0X2                        (2 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* SDHI clock × 215 */
#  define R_SDHI_SD_OPTION_TOP_0X3                        (3 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* SDHI clock × 216 */
#  define R_SDHI_SD_OPTION_TOP_0X4                        (4 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* SDHI clock × 217 */
#  define R_SDHI_SD_OPTION_TOP_0X5                        (5 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* SDHI clock × 218 */
#  define R_SDHI_SD_OPTION_TOP_0X6                        (6 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* SDHI clock × 219 */
#  define R_SDHI_SD_OPTION_TOP_0X7                        (7 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* SDHI clock × 220 */
#  define R_SDHI_SD_OPTION_TOP_0X8                        (8 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* SDHI clock × 221 */
#  define R_SDHI_SD_OPTION_TOP_0X9                        (9 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* SDHI clock × 222 */
#  define R_SDHI_SD_OPTION_TOP_0XA                        (10 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* SDHI clock × 223 */
#  define R_SDHI_SD_OPTION_TOP_0XB                        (11 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* SDHI clock × 224 */
#  define R_SDHI_SD_OPTION_TOP_0XC                        (12 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* SDHI clock × 225 */
#  define R_SDHI_SD_OPTION_TOP_0XD                        (13 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* SDHI clock × 226 */
#  define R_SDHI_SD_OPTION_TOP_0XE                        (14 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* SDHI clock × 227 */
#  define R_SDHI_SD_OPTION_TOP_0XF                        (15 << R_SDHI_SD_OPTION_TOP_SHIFT)  /* Setting prohibited */

#define R_SDHI_SD_OPTION_TOUTMASK                 (1 << 8)  /* Timeout Mask */

#define R_SDHI_SD_OPTION_WIDTH8                   (1 << 13)  /* Bus Width */

#define R_SDHI_SD_OPTION_WIDTH                    (1 << 15)  /* Bus Width */

/* SD_ERR_STS1 Register bit definitions */
#define R_SDHI_SD_ERR_STS1_CMDE0                  (1 << 0)  /* Command Error Flag 0 */

#define R_SDHI_SD_ERR_STS1_CMDE1                  (1 << 1)  /* Command Error Flag 1 */

#define R_SDHI_SD_ERR_STS1_RSPLENE0               (1 << 2)  /* Response Length Error Flag 0 */

#define R_SDHI_SD_ERR_STS1_RSPLENE1               (1 << 3)  /* Response Length Error Flag 1 */

#define R_SDHI_SD_ERR_STS1_RDLENE                 (1 << 4)  /* Read Data Length Error Flag */

#define R_SDHI_SD_ERR_STS1_CRCLENE                (1 << 5)  /* CRC Status Token Length Error Flag */

#define R_SDHI_SD_ERR_STS1_RSPCRCE0               (1 << 8)  /* Response CRC Error Flag 0 */

#define R_SDHI_SD_ERR_STS1_RSPCRCE1               (1 << 9)  /* Response CRC Error Flag 1 */

#define R_SDHI_SD_ERR_STS1_RDCRCE                 (1 << 10)  /* Read Data CRC Error Flag */

#define R_SDHI_SD_ERR_STS1_CRCTKE                 (1 << 11)  /* CRC Status Token Error Flag */

#define R_SDHI_SD_ERR_STS1_CRCTK_SHIFT            (12)  /* CRC Status Token */
#define R_SDHI_SD_ERR_STS1_CRCTK_MASK             0x7000

/* SD_ERR_STS2 Register bit definitions */
#define R_SDHI_SD_ERR_STS2_RSPTO0                 (1 << 0)  /* Response Timeout Flag 0 */

#define R_SDHI_SD_ERR_STS2_RSPTO1                 (1 << 1)  /* Response Timeout Flag 1 */

#define R_SDHI_SD_ERR_STS2_BSYTO0                 (1 << 2)  /* Busy Timeout Flag 0 */

#define R_SDHI_SD_ERR_STS2_BSYTO1                 (1 << 3)  /* Busy Timeout Flag 1 */

#define R_SDHI_SD_ERR_STS2_RDTO                   (1 << 4)  /* Read Data Timeout Flag */

#define R_SDHI_SD_ERR_STS2_CRCTO                  (1 << 5)  /* CRC Status Token Timeout Flag */

#define R_SDHI_SD_ERR_STS2_CRCBSYTO               (1 << 6)  /* CRC Status Token Busy Timeout Flag */

/* SD_BUF0 Register bit definitions */
#define R_SDHI_SD_BUF0_SD_BUF_SHIFT               (0)  /* SD Buffer RegisterWhen writing to the SD card, the write data is written to this register. When reading from the SD card, the read data is read from this register. This register is internally connected to two 512-byte buffers.If both buffers are not empty when executing multiple block read, SD/MMC clock is stopped to suspend receiving data. When one of buffers is empty, SD/MMC clock is supplied to resume receiving data. */
#define R_SDHI_SD_BUF0_SD_BUF_MASK                0xffffffff

/* SDIO_MODE Register bit definitions */
#define R_SDHI_SDIO_MODE_INTEN                    (1 << 0)  /* SDIO Interrupt Acceptance Enable */

#define R_SDHI_SDIO_MODE_RWREQ                    (1 << 2)  /* Read Wait Request */

#define R_SDHI_SDIO_MODE_IOABT                    (1 << 8)  /* SDIO Abort */

#define R_SDHI_SDIO_MODE_C52PUB                   (1 << 9)  /* SDIO None Abort */

/* SDIO_INFO1 Register bit definitions */
#define R_SDHI_SDIO_INFO1_IOIRQ                   (1 << 0)  /* SDIO Interrupt Status Flag */

#define R_SDHI_SDIO_INFO1_EXPUB52                 (1 << 14)  /* EXPUB52 Status Flag */

#define R_SDHI_SDIO_INFO1_EXWT                    (1 << 15)  /* EXWT Status Flag */

/* SDIO_INFO1_MASK Register bit definitions */
#define R_SDHI_SDIO_INFO1_MASK_IOIRQM             (1 << 0)  /* IOIRQ Interrupt Mask Control */

#define R_SDHI_SDIO_INFO1_MASK_EXPUB52M           (1 << 14)  /* EXPUB52 Interrupt Request Mask Control */

#define R_SDHI_SDIO_INFO1_MASK_EXWTM              (1 << 15)  /* EXWT Interrupt Request Mask Control */

/* SD_DMAEN Register bit definitions */
#define R_SDHI_SD_DMAEN_DMAEN                     (1 << 1)  /* DMA Transfer Enable */

/* SOFT_RST Register bit definitions */
#define R_SDHI_SOFT_RST_SDRST                     (1 << 0)  /* Software Reset Control */

/* SDIF_MODE Register bit definitions */
#define R_SDHI_SDIF_MODE_NOCHKCR                  (1 << 8)  /* CRC Check Mask */

/* EXT_SWAP Register bit definitions */
#define R_SDHI_EXT_SWAP_BWSWP                     (1 << 6)  /* SD_BUF0 Swap Write */

#define R_SDHI_EXT_SWAP_BRSWP                     (1 << 7)  /* SD_BUF0 Swap Read */


/* Maximum number of channels */

#define SDHI_MAX_CHANNELS    2

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SDHI_H */

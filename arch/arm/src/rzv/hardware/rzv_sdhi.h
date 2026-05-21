/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_sdhi.h
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

/* Register offsets and bitmasks for the RZ/V2H (R9A09G057H) SDHI/eMMC IP.
 * Source: RZ/V2H Hardware User Manual s6.2 (Table 6.2-2, s6.2.2.1).
 * NOTE: 8-byte stride layout -- differs from sibling R9A07G063U (4-byte).
 * DO NOT replace these offsets with values from a sibling SoC header.
 */

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SDHI_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SDHI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Base Addresses (CA55 / default view) -- UM Table 6.2-2 *******************/

#define RZV_SDHI0_BASE          0x15c00000u  /* SD0 -- RDK slot (QSD0_*) */
#define RZV_SDHI1_BASE          0x15c10000u  /* SD1 */
#define RZV_SDHI2_BASE          0x15c20000u  /* SD2 */

/* Register Offsets (8-byte stride, UM s6.2.2.1) ****************************
 * All offsets relative to RZV_SDHIn_BASE.
 * Access width: 16-bit for most registers; 32-bit for BUF0, RSP, DM_CM.
 */

#define RZV_SDHI_SD_CMD_OFFSET          0x000  /* Command index + response type */
                                               /* gap: 0x008 */
#define RZV_SDHI_SD_ARG_OFFSET          0x010  /* Argument bits [15:0] */
#define RZV_SDHI_SD_ARG1_OFFSET         0x018  /* Argument bits [31:16] */
#define RZV_SDHI_SD_STOP_OFFSET         0x020  /* Auto-CMD12 / stop control */
#define RZV_SDHI_SD_SECCNT_OFFSET       0x028  /* Block count */
#define RZV_SDHI_SD_RSP10_OFFSET        0x030  /* Response[31:0]   (32-bit) */
#define RZV_SDHI_SD_RSP1_OFFSET         0x038  /* Response[31:16] alias */
#define RZV_SDHI_SD_RSP32_OFFSET        0x040  /* Response[63:32]  (32-bit) */
#define RZV_SDHI_SD_RSP3_OFFSET         0x048  /* Response[63:48] alias */
#define RZV_SDHI_SD_RSP54_OFFSET        0x050  /* Response[95:64]  (32-bit) */
#define RZV_SDHI_SD_RSP5_OFFSET         0x058  /* Response[95:80] alias */
#define RZV_SDHI_SD_RSP76_OFFSET        0x060  /* Response[127:96] (32-bit) */
#define RZV_SDHI_SD_RSP7_OFFSET         0x068  /* Response[127:112] alias */
#define RZV_SDHI_SD_INFO1_OFFSET        0x070  /* Card-access + card-detect IRQ flags */
#define RZV_SDHI_SD_INFO2_OFFSET        0x078  /* Buffer + error IRQ flags (init=0x2000) */
#define RZV_SDHI_SD_INFO1_MASK_OFFSET   0x080  /* INFO1 interrupt mask (init=0x0001031d) */
#define RZV_SDHI_SD_INFO2_MASK_OFFSET   0x088  /* INFO2 interrupt mask (init=0x00008b7f) */
#define RZV_SDHI_SD_CLK_CTRL_OFFSET     0x090  /* Clock divider + SCLKEN + SDCLKOFFEN */
#define RZV_SDHI_SD_SIZE_OFFSET         0x098  /* Block size (init=0x0200 = 512) */
#define RZV_SDHI_SD_OPTION_OFFSET       0x0a0  /* Bus width + timeout (init=0x40ee) */
#define RZV_SDHI_SD_ERR_STS1_OFFSET     0x0b0  /* Detailed error status 1 */
#define RZV_SDHI_SD_ERR_STS2_OFFSET     0x0b8  /* Detailed error status 2 (init=0) */
#define RZV_SDHI_SD_BUF0_OFFSET         0x0c0  /* PIO data port (32/64-bit) */
                                               /* gap: 0x0c8 */
#define RZV_SDHI_SDIO_MODE_OFFSET       0x0d0  /* SDIO enable (init=0) */
#define RZV_SDHI_SDIO_INFO1_OFFSET      0x0d8  /* SDIO IRQ flags (init=0) */
#define RZV_SDHI_SDIO_INFO1_MASK_OFFSET 0x0e0  /* SDIO IRQ mask (init=0xc007) */
                                               /* gap: 0x0e8 to 0x358 */
#define RZV_SDHI_CC_EXT_MODE_OFFSET     0x360  /* DMA mode enable (init=0x1010) */
                                               /* Note: replaces SD_DMACR naming */
                                               /* gap: 0x368 to 0x378 */
#define RZV_SDHI_SOFT_RST_OFFSET        0x380  /* Soft reset (SDRST bit, active-low) */
#define RZV_SDHI_VERSION_OFFSET         0x388  /* IP version (ro, 0xcc10) */
#define RZV_SDHI_HOST_MODE_OFFSET       0x390  /* Host interface mode (8-bit eMMC) */
#define RZV_SDHI_SDIF_MODE_OFFSET       0x398  /* DDR / interface mode */
                                               /* gap: 0x3a0 to 0x3c0 */
#define RZV_SDHI_SD_STATUS_OFFSET       0x3c8  /* Status (CBSY check before CLK write) */
                                               /* gap: 0x3d0 to 0x81f */

/* Integrated DMAC sub-block (Phase 6 only -- not used in MVP PIO path) */

#define RZV_SDHI_DM_CM_DTRAN_MODE_OFFSET  0x820  /* DMAC mode (init=0x0030) */
#define RZV_SDHI_DM_CM_DTRAN_CTRL_OFFSET  0x828  /* DMAC control (init=0) */
#define RZV_SDHI_DM_CM_RST_OFFSET         0x830  /* DMAC reset (init=0xffffffff) */
#define RZV_SDHI_DM_CM_INFO1_OFFSET       0x840  /* DMAC IRQ1 (init=0) */
#define RZV_SDHI_DM_CM_INFO1_MASK_OFFSET  0x848  /* DMAC IRQ1 mask (init=0xffffffff) */
#define RZV_SDHI_DM_CM_INFO2_OFFSET       0x850  /* DMAC IRQ2 (init=0) */
#define RZV_SDHI_DM_CM_INFO2_MASK_OFFSET  0x858  /* DMAC IRQ2 mask (init=0xffffffff) */

/* Register Address Helper **************************************************
 * Usage: getreg32(RZV_SDHI_REG(base, OFFSET))
 */

#define RZV_SDHI_REG(base, off)  ((base) + (off))

/* SD_CMD -- offset 0x000 ****************************************************
 * Bits [5:0]: command index
 * Bit  [6]:   ACMD flag (application-specific command)   NEEDS_VERIFY
 * Bits [10:8]: response type
 *   000 = no response, 011 = R1/R1b/R6/R7, 100 = R2, 101 = R3
 * Bit  [11]: data transfer (1 = data present)
 * Bit  [12]: transfer direction (0 = write, 1 = read)
 * Bit  [13]: multi-block (0 = single, 1 = multi)
 * Bit  [14]: CMD12 auto-stop (1 = enable)                NEEDS_VERIFY
 */

#define RZV_SDHI_SD_CMD_CMDIDX_MASK    (0x003f)  /* Command index [5:0] */
#define RZV_SDHI_SD_CMD_ACMD           (1u << 6) /* ACMD prefix flag */
#define RZV_SDHI_SD_CMD_RSP_NONE       (0u << 8) /* No response */
#define RZV_SDHI_SD_CMD_RSP_R1         (3u << 8) /* R1/R1b/R6/R7 */
#define RZV_SDHI_SD_CMD_RSP_R2         (4u << 8) /* R2 (136-bit) */
#define RZV_SDHI_SD_CMD_RSP_R3         (5u << 8) /* R3 (OCR) */
#define RZV_SDHI_SD_CMD_RSP_MASK       (7u << 8)
#define RZV_SDHI_SD_CMD_DATA           (1u << 11) /* Data transfer present */
#define RZV_SDHI_SD_CMD_READ           (1u << 12) /* Direction: 1=read */
#define RZV_SDHI_SD_CMD_MULTI          (1u << 13) /* Multi-block transfer */
#define RZV_SDHI_SD_CMD_CMD12          (1u << 14) /* Auto CMD12 stop */

/* SD_CLK_CTRL -- offset 0x090 ***********************************************
 * Bits [7:0]: DIV -- one-hot encoded divider (see plan s4 table).
 *   SDCLK = (SDHI_x_IMCLK / 4) / N
 *   0x80=N512  0x40=N256  0x20=N128(init)  0x10=N64  0x08=N32
 *   0x04=N16   0x02=N8    0x01=N4          0x00=N2   0xFF=bypass
 * Bit  [8]:   SCLKEN     -- 1 = enable SDCLK output; clear before changing DIV
 * Bit  [9]:   SDCLKOFFEN -- 1 = auto-gate SDCLK between commands (8-cycle tail)
 */

#define RZV_SDHI_SD_CLK_CTRL_DIV_MASK   (0xff)      /* DIV[7:0] one-hot */
#define RZV_SDHI_SD_CLK_CTRL_DIV_512    (0x80)      /* approx 391 kHz init */
#define RZV_SDHI_SD_CLK_CTRL_DIV_256    (0x40)
#define RZV_SDHI_SD_CLK_CTRL_DIV_128    (0x20)      /* reset default */
#define RZV_SDHI_SD_CLK_CTRL_DIV_64     (0x10)
#define RZV_SDHI_SD_CLK_CTRL_DIV_32     (0x08)
#define RZV_SDHI_SD_CLK_CTRL_DIV_16     (0x04)
#define RZV_SDHI_SD_CLK_CTRL_DIV_8      (0x02)
#define RZV_SDHI_SD_CLK_CTRL_DIV_4      (0x01)
#define RZV_SDHI_SD_CLK_CTRL_DIV_2      (0x00)      /* 25 MHz at IMCLK=200 MHz */
#define RZV_SDHI_SD_CLK_CTRL_DIV_BYPASS (0xff)      /* bypass -- DDR FORBIDDEN */
#define RZV_SDHI_SD_CLK_CTRL_SCLKEN     (1u << 8)   /* Enable SDCLK output */
#define RZV_SDHI_SD_CLK_CTRL_SDCLKOFFEN (1u << 9)   /* Auto-gate SDCLK */

/* SD_OPTION -- offset 0x0a0 *************************************************
 * Bits [3:0]: timeout counter (0xE = max)
 * Bit  [15]:  WIDTH -- 0 = 4-bit bus, 1 = 1-bit bus
 */

#define RZV_SDHI_SD_OPTION_TIMEOUT_MASK (0x000f)    /* Timeout counter [3:0] */
#define RZV_SDHI_SD_OPTION_TIMEOUT_MAX  (0x000e)    /* Max timeout value */
#define RZV_SDHI_SD_OPTION_WIDTH1       (1u << 15)  /* 1-bit bus (default) */
                                                    /* 0 = 4-bit bus */

/* SOFT_RST -- offset 0x380 **************************************************
 * Bit [0]: SDRST -- 0 = assert reset, 1 = release (active low)
 * Init value = 0x0007 (reset released)
 */

#define RZV_SDHI_SOFT_RST_SDRST         (1u << 0)   /* Reset bit (active low) */
#define RZV_SDHI_SOFT_RST_RESERVED_MASK (0x0007)    /* All reset bits (init value) */

/* SD_INFO1 -- offset 0x070 **************************************************
 * Clear rule: write 0 to bit being cleared, 1 to all other bits (UM s6.2.3.3).
 * Bit [0]: INFO0 -- response received (RESP_END)
 * Bit [2]: INFO2 -- card access complete (ACCESS_END)
 * Bit [3]: INFO3 -- card detect (inserted)
 * Bit [4]: INFO4 -- card detect (removed)
 * Bit [8]: INFO8 -- DAT3 card detect (inserted)   NEEDS_VERIFY
 * Bit [9]: INFO9 -- DAT3 card detect (removed)    NEEDS_VERIFY
 */

#define RZV_SDHI_SD_INFO1_RSPEND        (1u << 0)   /* Response received */
#define RZV_SDHI_SD_INFO1_ACEND         (1u << 2)   /* Access (data) complete */
#define RZV_SDHI_SD_INFO1_SDCDIN        (1u << 3)   /* Card inserted */
#define RZV_SDHI_SD_INFO1_SDCDRM        (1u << 4)   /* Card removed */
#define RZV_SDHI_SD_INFO1_DAT3IN        (1u << 8)   /* DAT3 card inserted NEEDS_VERIFY */
#define RZV_SDHI_SD_INFO1_DAT3RM        (1u << 9)   /* DAT3 card removed  NEEDS_VERIFY */

/* SD_INFO2 -- offset 0x078 **************************************************
 * Bit [0]:  ERR0 -- CMD error
 * Bit [1]:  ERR1 -- CRC error
 * Bit [2]:  ERR2 -- END bit error
 * Bit [3]:  ERR3 -- data timeout
 * Bit [4]:  ERR4 -- bus drive width illegal (ILW)
 * Bit [5]:  ERR5 -- bus drive read width illegal (ILR)
 * Bit [6]:  ERR6 -- response timeout (RSPTO)
 * Bit [9]:  BRE  -- buffer read enable (RX data ready)
 * Bit [10]: BWE  -- buffer write enable (TX buffer empty)
 * Bit [13]: CBSY -- command busy (check before CLK write)
 * Bit [15]: ILA  -- illegal access error
 */

#define RZV_SDHI_SD_INFO2_ERR0          (1u << 0)
#define RZV_SDHI_SD_INFO2_ERR1          (1u << 1)
#define RZV_SDHI_SD_INFO2_ERR2          (1u << 2)
#define RZV_SDHI_SD_INFO2_ERR3          (1u << 3)
#define RZV_SDHI_SD_INFO2_ILW           (1u << 4)
#define RZV_SDHI_SD_INFO2_ILR           (1u << 5)
#define RZV_SDHI_SD_INFO2_RSPTO         (1u << 6)
#define RZV_SDHI_SD_INFO2_BRE           (1u << 9)
#define RZV_SDHI_SD_INFO2_BWE           (1u << 10)
#define RZV_SDHI_SD_INFO2_CBSY          (1u << 13)
#define RZV_SDHI_SD_INFO2_ILA           (1u << 15)

/* Composite error / transfer masks */

#define RZV_SDHI_SD_INFO2_ERR_ALL \
  (RZV_SDHI_SD_INFO2_ERR0 | RZV_SDHI_SD_INFO2_ERR1 | \
   RZV_SDHI_SD_INFO2_ERR2 | RZV_SDHI_SD_INFO2_ERR3 | \
   RZV_SDHI_SD_INFO2_ILW  | RZV_SDHI_SD_INFO2_ILR  | \
   RZV_SDHI_SD_INFO2_RSPTO | RZV_SDHI_SD_INFO2_ILA)

#define RZV_SDHI_SD_INFO2_XFR_ALL \
  (RZV_SDHI_SD_INFO2_BRE | RZV_SDHI_SD_INFO2_BWE)

/* INFO1/INFO2 mask reset values (all interrupts masked) */

#define RZV_SDHI_SD_INFO1_MASK_INIT     0x0001031du
#define RZV_SDHI_SD_INFO2_MASK_INIT     0x00008b7fu

/* IRQ numbers (GIC SPI base = 32) -- rzv2h_irq.h + UM s6.2.3.3
 * CH0 OXMNIRQ:   GIC SPI 735 -> NuttX IRQ 767  NEEDS_VERIFY (rzv_icu.c)
 * CH0 OXASIOIRQ: GIC SPI 736 -> NuttX IRQ 768  NEEDS_VERIFY
 * CH1 OXMNIRQ:   GIC SPI 737 -> NuttX IRQ 769  NEEDS_VERIFY
 * CH2 OXMNIRQ:   GIC SPI 739 -> NuttX IRQ 771  NEEDS_VERIFY
 * These are the canonical definitions -- do NOT duplicate in rzv_sdhi.c.
 */

#define RZV_SDHI_CH0_OXMN_IRQ          767   /* NEEDS_VERIFY */
#define RZV_SDHI_CH0_OXASIO_IRQ        768   /* NEEDS_VERIFY */
#define RZV_SDHI_CH1_OXMN_IRQ          769   /* NEEDS_VERIFY */
#define RZV_SDHI_CH2_OXMN_IRQ          771   /* NEEDS_VERIFY */

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SDHI_H */

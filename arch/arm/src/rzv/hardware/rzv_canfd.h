/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_canfd.h
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

/* RZ/V2H (R9A09G057H) CAN-FD hardware register definitions.
 *
 * SOURCE / CROSS-CHECK VERDICTS
 * ==============================
 * Primary source:  R9A09G057H canfd_iodefine.h
 * Secondary:       NuttX RA8 header
 *   arch/arm/src/ra8/hardware/ra8e1/ra_canfd.h  (RSCAN-FD same IP family)
 *
 * BASE ADDRESS
 * ============
 * 0x12440000 — confirmed from canfd_iodefine.h:1818 (#define R_CANFD_BASE)
 *   The stub header had the right base but wrong channel stride (0x10).
 *   The RZ/V2H has a single unified register block; channels are NOT
 *   stride-separated.  Per-channel control registers (CFDC) are a 6-entry
 *   array at offset 0 (each entry 16 bytes), followed by global registers.
 *
 * RA8 vs RZ/V2H CROSS-CHECK (5 critical registers)
 * ==================================================
 * Register        RA8 offset  RZ/V2H offset  Verdict
 * -------         ----------  -------------  -------
 * CFDCnNCFG       CH_BASE+0   BASE+n*0x10+0  MATCH (per-ch, same bit layout)
 * CFDCnCTR        CH_BASE+4   BASE+n*0x10+4  MATCH (CHMDC, BEIE, etc.)
 * CFDCnSTS        CH_BASE+8   BASE+n*0x10+8  MATCH
 * CFDCnERFL       CH_BASE+C   BASE+n*0x10+C  MATCH
 * CFDGCFG         CH_BASE+14  BASE+0x84      DIVERGE — see note 1
 * CFDGCTR         CH_BASE+18  BASE+0x88      DIVERGE — see note 1
 * CFDGSTS         CH_BASE+1C  BASE+0x8C      DIVERGE — see note 1
 * CFDGERFL        CH_BASE+20  BASE+0x90      DIVERGE — see note 1
 * CFDRFCC0        CH_BASE+3C  BASE+0xC0      DIVERGE — see note 2
 * CFDCFCC0        CH_BASE+54  BASE+0x120     DIVERGE — see note 2
 * CFDTMC0         CH_BASE+70  BASE+0x2D0     DIVERGE — see note 3
 * CFDTMSTS0       CH_BASE+74  BASE+0x7D0     DIVERGE — see note 3
 * CFDTMTRSTS      CH_BASE+78  BASE+0xCD0     DIVERGE — see note 3
 * CFDTMTCSTS      CH_BASE+80  BASE+0xE10     DIVERGE — see note 3
 * CFDRMID0        BASE+920    BASE+DATA_RAM  DIVERGE — see note 4
 *
 * Note 1: RA8 places global registers immediately after the single-channel
 *   CFDC block (offset 0x10) — only 1 channel on RA8E1.  RZ/V2H has 6
 *   CFDC entries (6×16=0x60) + 32 bytes reserved = globals start at 0x80.
 *   RZ/V2H iodefine offsets are authoritative.
 *
 * Note 2: RZ/V2H has 8 RX FIFOs (CFDRFCC[8] at 0xC0) and 18 common FIFOs
 *   (CFDCFCC[18] at 0x120).  RA8E1 has 2 RX FIFOs and 1 common FIFO.
 *   Only FIFO 0 (RX) and common FIFO 0 are used by the v1 driver.
 *
 * Note 3: TX mailbox control is an 8-bit byte-addressable array of 384
 *   entries on RZ/V2H (one byte per TX mailbox); TX mailbox status similarly
 *   384 bytes starting at 0x7D0.  RA8 used 4 entries at byte offsets 0-3.
 *
 * Note 4: RX message buffer access area is outside the main register block
 *   (at BASE+large offset); for v1 driver only RX FIFO path is used, so
 *   CFDRMID/CFDRMPTR offsets are not needed here.
 *
 * CHANNEL STRIDE
 * ==============
 * Channels 0..5 each occupy 16 bytes at BASE + ch*0x10.
 * There is NO large per-channel stride (RA8 used 0x2000 because its IP
 * variant had a per-channel copy of ALL registers — the RZ/V2H variant uses
 * a single global block shared by all channels).
 *
 * CPG CLOCK GATE
 * ==============
 * Clock:  CPG_CLKON_9 bits[14:12] (3-bit mask, 7U << 12)
 *   Source: bsp_override.h:1692-1693
 *   RZV_CPG_CLK_CANFD encoding: (9 << 16 | 12)
 *   The previous value (7 << 16 | 0) was WRONG.
 *
 * Reset:  CPG_RST_10 bits[2:1] (2-bit mask, 3U << 1)
 *   Source: bsp_override.h:1698-1699
 *   Separate from clock: UNIT0_RSTB and UNIT1_RSTB.
 */

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_CANFD_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_CANFD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CAN-FD Base Address (single unified block for all 6 channels)
 * Source: canfd_iodefine.h line 1818 — #define R_CANFD_BASE 0x12440000
 */

#define RZV_CANFD_BASE                    0x12440000u

/* Per-channel control register base (CFDC[n], n=0..5)
 * Each channel occupies 16 bytes at BASE + ch*0x10.
 * IMPORTANT: channel 1 is at BASE+0x10, NOT a separate peripheral block.
 */

#define RZV_CANFD_CH_OFFSET(ch)           ((uint32_t)(ch) * 0x0010u)
#define RZV_CANFD_CH_BASE(ch)             (RZV_CANFD_BASE + RZV_CANFD_CH_OFFSET(ch))

/* Convenience aliases for channels 0 and 1 */

#define RZV_CANFD_CH0_BASE                RZV_CANFD_CH_BASE(0)  /* 0x12440000 */
#define RZV_CANFD_CH1_BASE                RZV_CANFD_CH_BASE(1)  /* 0x12440010 */

/****************************************************************************
 * Per-Channel Register Offsets (relative to RZV_CANFD_CH_BASE(n))
 * Source: canfd_iodefine.h R_CANFD_CFDC_Type (size=16 / 0x10)
 ****************************************************************************/

#define RZV_CANFD_CFDC_NCFG_OFFSET        0x0000  /* Nominal Bitrate Config */
#define RZV_CANFD_CFDC_CTR_OFFSET         0x0004  /* Channel Control */
#define RZV_CANFD_CFDC_STS_OFFSET         0x0008  /* Channel Status */
#define RZV_CANFD_CFDC_ERFL_OFFSET        0x000c  /* Channel Error Flag */

/* Per-channel FD configuration (R_CANFD_CFDC2_Type), starts at BASE+0x60
 * after 6 CFDC entries.  Each CFDC2 entry is 0x20 bytes.
 * BASE + 0x60 + ch*0x20 + subfield_offset
 */

#define RZV_CANFD_CFDC2_BASE_OFFSET       0x0060  /* Start of CFDC2 array */
#define RZV_CANFD_CFDC2_CH_STRIDE         0x0020  /* Each CFDC2 entry = 32B */
#define RZV_CANFD_CFDC2_CH_BASE(ch)       (RZV_CANFD_BASE + \
                                           RZV_CANFD_CFDC2_BASE_OFFSET + \
                                           ((uint32_t)(ch) * RZV_CANFD_CFDC2_CH_STRIDE))
#define RZV_CANFD_CFDC2_DCFG_OFFSET       0x0000  /* Data Bitrate Config */
#define RZV_CANFD_CFDC2_FDCFG_OFFSET      0x0004  /* CAN-FD Config */
#define RZV_CANFD_CFDC2_FDCTR_OFFSET      0x0008  /* CAN-FD Control */
#define RZV_CANFD_CFDC2_FDSTS_OFFSET      0x000c  /* CAN-FD Status */
#define RZV_CANFD_CFDC2_FDCRC_OFFSET      0x0010  /* CAN-FD CRC */

/****************************************************************************
 * Per-Channel Register Absolute Addresses
 ****************************************************************************/

#define RZV_CANFD_CFDC_NCFG(ch)           (RZV_CANFD_CH_BASE(ch) + RZV_CANFD_CFDC_NCFG_OFFSET)
#define RZV_CANFD_CFDC_CTR(ch)            (RZV_CANFD_CH_BASE(ch) + RZV_CANFD_CFDC_CTR_OFFSET)
#define RZV_CANFD_CFDC_STS(ch)            (RZV_CANFD_CH_BASE(ch) + RZV_CANFD_CFDC_STS_OFFSET)
#define RZV_CANFD_CFDC_ERFL(ch)           (RZV_CANFD_CH_BASE(ch) + RZV_CANFD_CFDC_ERFL_OFFSET)

/* CFDC2 per-channel FD config */

#define RZV_CANFD_CFDC2_DCFG(ch)          (RZV_CANFD_CFDC2_CH_BASE(ch) + RZV_CANFD_CFDC2_DCFG_OFFSET)
#define RZV_CANFD_CFDC2_FDCFG(ch)         (RZV_CANFD_CFDC2_CH_BASE(ch) + RZV_CANFD_CFDC2_FDCFG_OFFSET)
#define RZV_CANFD_CFDC2_FDCTR(ch)         (RZV_CANFD_CFDC2_CH_BASE(ch) + RZV_CANFD_CFDC2_FDCTR_OFFSET)
#define RZV_CANFD_CFDC2_FDSTS(ch)         (RZV_CANFD_CFDC2_CH_BASE(ch) + RZV_CANFD_CFDC2_FDSTS_OFFSET)

/****************************************************************************
 * Global Register Offsets (relative to RZV_CANFD_BASE)
 * Source: canfd_iodefine.h R_CANFD_Type struct, globals start at 0x0080
 * (6 × CFDC=0x60 + 0x20 reserved = 0x80)
 *
 * DIVERGENCE from RA8: RA8 places these at BASE+0x14 (1 ch × 16B = 0x10
 * + 4 pad). RZ/V2H has 6 channels so globals are at BASE+0x80.
 ****************************************************************************/

#define RZV_CANFD_CFDGIPV_OFFSET          0x0080  /* Global IP Version */
#define RZV_CANFD_CFDGCFG_OFFSET          0x0084  /* Global Config */
#define RZV_CANFD_CFDGCTR_OFFSET          0x0088  /* Global Control */
#define RZV_CANFD_CFDGSTS_OFFSET          0x008c  /* Global Status */
#define RZV_CANFD_CFDGERFL_OFFSET         0x0090  /* Global Error Flag */
#define RZV_CANFD_CFDGTSC_OFFSET          0x0094  /* Global Timestamp Counter */
#define RZV_CANFD_CFDGAFLECTR_OFFSET      0x0098  /* AFL Entry Control */
#define RZV_CANFD_CFDGAFLCFG0_OFFSET      0x009c  /* AFL Config ch0/ch1 */
#define RZV_CANFD_CFDGAFLCFG1_OFFSET      0x00a0  /* AFL Config ch2/ch3 */
#define RZV_CANFD_CFDGAFLCFG2_OFFSET      0x00a4  /* AFL Config ch4/ch5 */
/* 4 bytes reserved at 0x00A8 */
#define RZV_CANFD_CFDRMNB_OFFSET          0x00ac  /* RX MB Number/Payload */
#define RZV_CANFD_CFDRMND0_OFFSET         0x00b0  /* RX MB New Data [31:0] */
#define RZV_CANFD_CFDRMND1_OFFSET         0x00b4  /* RX MB New Data [63:32] */
#define RZV_CANFD_CFDRMND2_OFFSET         0x00b8  /* RX MB New Data [95:64] */
/* 4 bytes reserved at 0x00BC */
#define RZV_CANFD_CFDRFCC_OFFSET(n)       (0x00c0 + ((uint32_t)(n)) * 4u)  /* RX FIFO n CC, n=0..7 */
#define RZV_CANFD_CFDRFSTS_OFFSET(n)      (0x00e0 + ((uint32_t)(n)) * 4u)  /* RX FIFO n Status */
#define RZV_CANFD_CFDRFPCTR_OFFSET(n)     (0x0100 + ((uint32_t)(n)) * 4u)  /* RX FIFO n Pointer Ctrl */
#define RZV_CANFD_CFDCFCC_OFFSET(n)       (0x0120 + ((uint32_t)(n)) * 4u)  /* Common FIFO n CC, n=0..17 */
#define RZV_CANFD_CFDCFSTS_OFFSET(n)      (0x01e0 + ((uint32_t)(n)) * 4u)  /* Common FIFO n Status */
#define RZV_CANFD_CFDCFPCTR_OFFSET(n)     (0x0240 + ((uint32_t)(n)) * 4u)  /* Common FIFO n Ptr Ctrl */
/* 24 reserved bytes before FIFO status at 0x02A0 */
#define RZV_CANFD_CFDFESTS_OFFSET         0x02a0  /* FIFO Empty Status */
#define RZV_CANFD_CFDFFSTS_OFFSET         0x02a4  /* FIFO Full Status */
#define RZV_CANFD_CFDFMSTS_OFFSET         0x02a8  /* FIFO Msg Lost Status */
#define RZV_CANFD_CFDRFISTS_OFFSET        0x02ac  /* RX FIFO Int Flag Status */
#define RZV_CANFD_CFDCFRISTS_OFFSET       0x02b0  /* Common FIFO RX Int Flag */
#define RZV_CANFD_CFDCFTISTS_OFFSET       0x02b4  /* Common FIFO TX Int Flag */

/* TX Message Buffer Control (byte array, 384 entries, 1 byte each) */

#define RZV_CANFD_CFDTMC_OFFSET(n)        (0x02d0 + (uint32_t)(n))         /* TX MB n Control (byte) */
#define RZV_CANFD_CFDTMSTS_OFFSET(n)      (0x07d0 + (uint32_t)(n))         /* TX MB n Status (byte) */

/* TX MB group status registers (32-bit, 16 mailboxes per word) */

#define RZV_CANFD_CFDTMTRSTS0_OFFSET      0x0cd0  /* TX Transmission Req Status [15:0] */
#define RZV_CANFD_CFDTMTRSTS1_OFFSET      0x0cd4  /* TX Transmission Req Status [31:16] */
#define RZV_CANFD_CFDTMTARSTS0_OFFSET     0x0d70  /* TX Abort Req Status [15:0] */
#define RZV_CANFD_CFDTMTARSTS1_OFFSET     0x0d74  /* TX Abort Req Status [31:16] */
#define RZV_CANFD_CFDTMTCSTS0_OFFSET      0x0e10  /* TX Completion Status [15:0] */
#define RZV_CANFD_CFDTMTCSTS1_OFFSET      0x0e14  /* TX Completion Status [31:16] */
#define RZV_CANFD_CFDTMTASTS0_OFFSET      0x0eb0  /* TX Abort Status [15:0] */
#define RZV_CANFD_CFDTMTASTS1_OFFSET      0x0eb4  /* TX Abort Status [31:16] */
#define RZV_CANFD_CFDTMIEC0_OFFSET        0x0f50  /* TX MB Interrupt Enable [15:0] */
#define RZV_CANFD_CFDTMIEC1_OFFSET        0x0f54  /* TX MB Interrupt Enable [31:16] */

/* TX Queue registers (per-channel, 6 entries, stride 4 bytes) */

#define RZV_CANFD_CFDTXQCC0_OFFSET(ch)   (0x1000 + ((uint32_t)(ch)) * 4u)  /* TXQ0 CC per ch */
#define RZV_CANFD_CFDTXQSTS0_OFFSET(ch)  (0x1020 + ((uint32_t)(ch)) * 4u)  /* TXQ0 Status per ch */
#define RZV_CANFD_CFDTXQPCTR0_OFFSET(ch) (0x1040 + ((uint32_t)(ch)) * 4u)  /* TXQ0 Ptr Ctrl per ch */

/* AFL entry registers (page-based, 16 entries per page, 16B each) */

#define RZV_CANFD_CFDGAFL_ID_OFFSET(n)   (0x1800 + ((uint32_t)(n)) * 0x10u)  /* AFL n ID */
#define RZV_CANFD_CFDGAFL_M_OFFSET(n)    (0x1804 + ((uint32_t)(n)) * 0x10u)  /* AFL n Mask */
#define RZV_CANFD_CFDGAFL_P0_OFFSET(n)   (0x1808 + ((uint32_t)(n)) * 0x10u)  /* AFL n Ptr0 */
#define RZV_CANFD_CFDGAFL_P1_OFFSET(n)   (0x180c + ((uint32_t)(n)) * 0x10u)  /* AFL n Ptr1 */

/* RX FIFO access area (R_CANFD_CFDRF_Type, 128 bytes each, n=0..7) */

#define RZV_CANFD_CFDRF_BASE_OFFSET       0x6000  /* Start of RX FIFO access area */
#define RZV_CANFD_CFDRF_STRIDE            0x0080  /* 128 bytes per FIFO entry */
#define RZV_CANFD_CFDRFID_OFFSET(n)       (RZV_CANFD_CFDRF_BASE_OFFSET + \
                                           ((uint32_t)(n)) * RZV_CANFD_CFDRF_STRIDE + 0x00)
#define RZV_CANFD_CFDRFPTR_OFFSET(n)      (RZV_CANFD_CFDRF_BASE_OFFSET + \
                                           ((uint32_t)(n)) * RZV_CANFD_CFDRF_STRIDE + 0x04)
#define RZV_CANFD_CFDRFFDSTS_OFFSET(n)    (RZV_CANFD_CFDRF_BASE_OFFSET + \
                                           ((uint32_t)(n)) * RZV_CANFD_CFDRF_STRIDE + 0x08)
#define RZV_CANFD_CFDRFDF_OFFSET(n, b)    (RZV_CANFD_CFDRF_BASE_OFFSET + \
                                           ((uint32_t)(n)) * RZV_CANFD_CFDRF_STRIDE + \
                                           0x0c + ((uint32_t)(b)) * 4u)

/* Common FIFO access area (R_CANFD_CFDCF_Type, 128 bytes each, n=0..17) */

#define RZV_CANFD_CFDCF_BASE_OFFSET       0x6400  /* Start of CF access area */
#define RZV_CANFD_CFDCF_STRIDE            0x0080  /* 128 bytes per CF entry */
#define RZV_CANFD_CFDCFID_OFFSET(n)       (RZV_CANFD_CFDCF_BASE_OFFSET + \
                                           ((uint32_t)(n)) * RZV_CANFD_CFDCF_STRIDE + 0x00)
#define RZV_CANFD_CFDCFPTR_OFFSET(n)      (RZV_CANFD_CFDCF_BASE_OFFSET + \
                                           ((uint32_t)(n)) * RZV_CANFD_CFDCF_STRIDE + 0x04)
#define RZV_CANFD_CFDCFFDSTS_OFFSET(n)    (RZV_CANFD_CFDCF_BASE_OFFSET + \
                                           ((uint32_t)(n)) * RZV_CANFD_CFDCF_STRIDE + 0x08)
#define RZV_CANFD_CFDCFDF_OFFSET(n, b)    (RZV_CANFD_CFDCF_BASE_OFFSET + \
                                           ((uint32_t)(n)) * RZV_CANFD_CFDCF_STRIDE + \
                                           0x0c + ((uint32_t)(b)) * 4u)

/* TX Message Buffer access area (R_CANFD_CFDTM_Type, 128 bytes each)
 * Each channel has a group of TX mailboxes.
 * v1 driver uses mailbox 0 per channel.
 * Absolute address = BASE + offset_below
 */

#define RZV_CANFD_CFDTM_BASE_OFFSET       0x7000  /* Start of TM access area */
#define RZV_CANFD_CFDTM_STRIDE            0x0080  /* 128 bytes per TM entry */
#define RZV_CANFD_CFDTMID_OFFSET(n)       (RZV_CANFD_CFDTM_BASE_OFFSET + \
                                           ((uint32_t)(n)) * RZV_CANFD_CFDTM_STRIDE + 0x00)
#define RZV_CANFD_CFDTMPTR_OFFSET(n)      (RZV_CANFD_CFDTM_BASE_OFFSET + \
                                           ((uint32_t)(n)) * RZV_CANFD_CFDTM_STRIDE + 0x04)
#define RZV_CANFD_CFDTMFDCTR_OFFSET(n)    (RZV_CANFD_CFDTM_BASE_OFFSET + \
                                           ((uint32_t)(n)) * RZV_CANFD_CFDTM_STRIDE + 0x08)
#define RZV_CANFD_CFDTMDF_OFFSET(n, b)    (RZV_CANFD_CFDTM_BASE_OFFSET + \
                                           ((uint32_t)(n)) * RZV_CANFD_CFDTM_STRIDE + \
                                           0x0c + ((uint32_t)(b)) * 4u)

/****************************************************************************
 * Global Register Absolute Addresses
 ****************************************************************************/

#define RZV_CANFD_CFDGCFG                 (RZV_CANFD_BASE + RZV_CANFD_CFDGCFG_OFFSET)
#define RZV_CANFD_CFDGCTR                 (RZV_CANFD_BASE + RZV_CANFD_CFDGCTR_OFFSET)
#define RZV_CANFD_CFDGSTS                 (RZV_CANFD_BASE + RZV_CANFD_CFDGSTS_OFFSET)
#define RZV_CANFD_CFDGERFL                (RZV_CANFD_BASE + RZV_CANFD_CFDGERFL_OFFSET)
#define RZV_CANFD_CFDGTSC                 (RZV_CANFD_BASE + RZV_CANFD_CFDGTSC_OFFSET)
#define RZV_CANFD_CFDGAFLECTR             (RZV_CANFD_BASE + RZV_CANFD_CFDGAFLECTR_OFFSET)
#define RZV_CANFD_CFDGAFLCFG0             (RZV_CANFD_BASE + RZV_CANFD_CFDGAFLCFG0_OFFSET)
#define RZV_CANFD_CFDRMNB                 (RZV_CANFD_BASE + RZV_CANFD_CFDRMNB_OFFSET)
#define RZV_CANFD_CFDRFCC(n)              (RZV_CANFD_BASE + RZV_CANFD_CFDRFCC_OFFSET(n))
#define RZV_CANFD_CFDRFSTS(n)             (RZV_CANFD_BASE + RZV_CANFD_CFDRFSTS_OFFSET(n))
#define RZV_CANFD_CFDRFPCTR(n)            (RZV_CANFD_BASE + RZV_CANFD_CFDRFPCTR_OFFSET(n))
#define RZV_CANFD_CFDCFCC(n)              (RZV_CANFD_BASE + RZV_CANFD_CFDCFCC_OFFSET(n))
#define RZV_CANFD_CFDCFSTS(n)             (RZV_CANFD_BASE + RZV_CANFD_CFDCFSTS_OFFSET(n))
#define RZV_CANFD_CFDCFPCTR(n)            (RZV_CANFD_BASE + RZV_CANFD_CFDCFPCTR_OFFSET(n))
#define RZV_CANFD_CFDFESTS                (RZV_CANFD_BASE + RZV_CANFD_CFDFESTS_OFFSET)
#define RZV_CANFD_CFDFFSTS                (RZV_CANFD_BASE + RZV_CANFD_CFDFFSTS_OFFSET)
#define RZV_CANFD_CFDFMSTS                (RZV_CANFD_BASE + RZV_CANFD_CFDFMSTS_OFFSET)
#define RZV_CANFD_CFDRFISTS               (RZV_CANFD_BASE + RZV_CANFD_CFDRFISTS_OFFSET)
#define RZV_CANFD_CFDCFRISTS              (RZV_CANFD_BASE + RZV_CANFD_CFDCFRISTS_OFFSET)
#define RZV_CANFD_CFDCFTISTS              (RZV_CANFD_BASE + RZV_CANFD_CFDCFTISTS_OFFSET)
#define RZV_CANFD_CFDTMC(n)               (RZV_CANFD_BASE + RZV_CANFD_CFDTMC_OFFSET(n))
#define RZV_CANFD_CFDTMSTS(n)             (RZV_CANFD_BASE + RZV_CANFD_CFDTMSTS_OFFSET(n))
#define RZV_CANFD_CFDTMTRSTS0             (RZV_CANFD_BASE + RZV_CANFD_CFDTMTRSTS0_OFFSET)
#define RZV_CANFD_CFDTMTCSTS0             (RZV_CANFD_BASE + RZV_CANFD_CFDTMTCSTS0_OFFSET)
#define RZV_CANFD_CFDTMTASTS0             (RZV_CANFD_BASE + RZV_CANFD_CFDTMTASTS0_OFFSET)
#define RZV_CANFD_CFDTMIEC0               (RZV_CANFD_BASE + RZV_CANFD_CFDTMIEC0_OFFSET)

/****************************************************************************
 * CFDCnNCFG — Channel Nominal Bitrate Configuration Register
 * (per-channel, same layout on RA8 and RZ/V2H: MATCHED)
 ****************************************************************************/

#define CANFD_CFDC_NCFG_NBRP_SHIFT        (0)
#define CANFD_CFDC_NCFG_NBRP_MASK         (0x3ffu << CANFD_CFDC_NCFG_NBRP_SHIFT)
#define CANFD_CFDC_NCFG_NSJW_SHIFT        (10)
#define CANFD_CFDC_NCFG_NSJW_MASK         (0x7fu << CANFD_CFDC_NCFG_NSJW_SHIFT)
#define CANFD_CFDC_NCFG_NTSEG1_SHIFT      (17)
#define CANFD_CFDC_NCFG_NTSEG1_MASK       (0xffu << CANFD_CFDC_NCFG_NTSEG1_SHIFT)
#define CANFD_CFDC_NCFG_NTSEG2_SHIFT      (25)
#define CANFD_CFDC_NCFG_NTSEG2_MASK       (0x7fu << CANFD_CFDC_NCFG_NTSEG2_SHIFT)

/****************************************************************************
 * CFDCnCTR — Channel Control Register
 * Source: canfd_iodefine.h R_CANFD_CFDC_Type.CTR_b
 ****************************************************************************/

#define CANFD_CFDC_CTR_CHMDC_SHIFT        (0)
#define CANFD_CFDC_CTR_CHMDC_MASK         (0x3u << CANFD_CFDC_CTR_CHMDC_SHIFT)
#  define CANFD_CFDC_CTR_CHMDC_COMM       (0u << CANFD_CFDC_CTR_CHMDC_SHIFT) /* Comm mode */
#  define CANFD_CFDC_CTR_CHMDC_RESET      (1u << CANFD_CFDC_CTR_CHMDC_SHIFT) /* Reset mode */
#  define CANFD_CFDC_CTR_CHMDC_HALT       (2u << CANFD_CFDC_CTR_CHMDC_SHIFT) /* Halt mode */
#define CANFD_CFDC_CTR_CSLPR              (1u << 2)   /* Channel Sleep Request */
#define CANFD_CFDC_CTR_RTBO               (1u << 3)   /* Return from Bus-Off */
#define CANFD_CFDC_CTR_BEIE               (1u << 8)   /* Bus Error Interrupt Enable */
#define CANFD_CFDC_CTR_EWIE               (1u << 9)   /* Error Warning Interrupt Enable */
#define CANFD_CFDC_CTR_EPIE               (1u << 10)  /* Error Passive Interrupt Enable */
#define CANFD_CFDC_CTR_BOEIE              (1u << 11)  /* Bus-Off Entry Interrupt Enable */
#define CANFD_CFDC_CTR_BORIE              (1u << 12)  /* Bus-Off Recovery Interrupt Enable */
#define CANFD_CFDC_CTR_OLIE               (1u << 13)  /* Overload Interrupt Enable */
#define CANFD_CFDC_CTR_BLIE               (1u << 14)  /* Bus Lock Interrupt Enable */
#define CANFD_CFDC_CTR_ALIE               (1u << 15)  /* Arbitration Lost Interrupt Enable */
#define CANFD_CFDC_CTR_TAIE               (1u << 16)  /* Transmission Abort Interrupt Enable */
#define CANFD_CFDC_CTR_EOCOIE             (1u << 17)  /* Error Counter Overflow Interrupt Enable */
#define CANFD_CFDC_CTR_SOCOIE             (1u << 18)  /* Success Counter Overflow Interrupt Enable */
#define CANFD_CFDC_CTR_TDCVFIE            (1u << 19)  /* TDC Violation Interrupt Enable */
#define CANFD_CFDC_CTR_BOM_SHIFT          (21)
#define CANFD_CFDC_CTR_BOM_MASK           (0x3u << CANFD_CFDC_CTR_BOM_SHIFT)
#  define CANFD_CFDC_CTR_BOM_NORMAL       (0u << CANFD_CFDC_CTR_BOM_SHIFT)  /* ISO 11898-1 */
#  define CANFD_CFDC_CTR_BOM_HALT_ENTER   (1u << CANFD_CFDC_CTR_BOM_SHIFT)  /* Halt at entry */
#  define CANFD_CFDC_CTR_BOM_HALT_END     (2u << CANFD_CFDC_CTR_BOM_SHIFT)  /* Halt at end */
#  define CANFD_CFDC_CTR_BOM_HALT_SW      (3u << CANFD_CFDC_CTR_BOM_SHIFT)  /* Halt by SW */
#define CANFD_CFDC_CTR_ERRD               (1u << 23)  /* Channel Error Display */
#define CANFD_CFDC_CTR_CTME               (1u << 24)  /* Channel Test Mode Enable */
#define CANFD_CFDC_CTR_CTMS_SHIFT         (25)
#define CANFD_CFDC_CTR_CTMS_MASK          (0x3u << CANFD_CFDC_CTR_CTMS_SHIFT)
#  define CANFD_CFDC_CTR_CTMS_BASIC       (0u << CANFD_CFDC_CTR_CTMS_SHIFT) /* Basic test */
#  define CANFD_CFDC_CTR_CTMS_LISTEN      (1u << CANFD_CFDC_CTR_CTMS_SHIFT) /* Listen-only */
#  define CANFD_CFDC_CTR_CTMS_EXT_LOOP    (2u << CANFD_CFDC_CTR_CTMS_SHIFT) /* External loopback */
#  define CANFD_CFDC_CTR_CTMS_INT_LOOP    (3u << CANFD_CFDC_CTR_CTMS_SHIFT) /* Internal loopback */
#define CANFD_CFDC_CTR_CRCT               (1u << 30)  /* CRC Error Test */
#define CANFD_CFDC_CTR_ROM                (1u << 31)  /* Restricted Operation Mode */

/****************************************************************************
 * CFDCnSTS — Channel Status Register
 ****************************************************************************/

#define CANFD_CFDC_STS_CRSTSTS            (1u << 0)   /* Channel Reset Status */
#define CANFD_CFDC_STS_CHLTSTS            (1u << 1)   /* Channel Halt Status */
#define CANFD_CFDC_STS_CSLPSTS            (1u << 2)   /* Channel Sleep Status */
#define CANFD_CFDC_STS_EPSTS              (1u << 3)   /* Channel Error Passive Status */
#define CANFD_CFDC_STS_BOSTS              (1u << 4)   /* Channel Bus-Off Status */
#define CANFD_CFDC_STS_TRMSTS             (1u << 5)   /* Channel Transmit Status */
#define CANFD_CFDC_STS_RECSTS             (1u << 6)   /* Channel Receive Status */
#define CANFD_CFDC_STS_COMSTS             (1u << 7)   /* Channel Communication Status */
#define CANFD_CFDC_STS_ESIF               (1u << 8)   /* Error State Indication Flag */
#define CANFD_CFDC_STS_REC_SHIFT          (16)
#define CANFD_CFDC_STS_REC_MASK           (0xffu << CANFD_CFDC_STS_REC_SHIFT)
#define CANFD_CFDC_STS_TEC_SHIFT          (24)
#define CANFD_CFDC_STS_TEC_MASK           (0xffu << CANFD_CFDC_STS_TEC_SHIFT)

/****************************************************************************
 * CFDCnERFL — Channel Error Flag Register
 ****************************************************************************/

#define CANFD_CFDC_ERFL_BEF               (1u << 0)   /* Bus Error Flag */
#define CANFD_CFDC_ERFL_EWF               (1u << 1)   /* Error Warning Flag */
#define CANFD_CFDC_ERFL_EPF               (1u << 2)   /* Error Passive Flag */
#define CANFD_CFDC_ERFL_BOEF              (1u << 3)   /* Bus-Off Entry Flag */
#define CANFD_CFDC_ERFL_BORF              (1u << 4)   /* Bus-Off Recovery Flag */
#define CANFD_CFDC_ERFL_OVLF              (1u << 5)   /* Overload Flag */
#define CANFD_CFDC_ERFL_BLF               (1u << 6)   /* Bus Lock Flag */
#define CANFD_CFDC_ERFL_ALF               (1u << 7)   /* Arbitration Lost Flag */
#define CANFD_CFDC_ERFL_SERR              (1u << 8)   /* Stuff Error */
#define CANFD_CFDC_ERFL_FERR              (1u << 9)   /* Form Error */
#define CANFD_CFDC_ERFL_AERR              (1u << 10)  /* Acknowledge Error */
#define CANFD_CFDC_ERFL_CERR              (1u << 11)  /* CRC Error */
#define CANFD_CFDC_ERFL_B1ERR             (1u << 12)  /* Bit 1 Error */
#define CANFD_CFDC_ERFL_B0ERR             (1u << 13)  /* Bit 0 Error */
#define CANFD_CFDC_ERFL_ADERR             (1u << 14)  /* Acknowledge Delimiter Error */
#define CANFD_CFDC_ERFL_CRCREG_SHIFT      (16)
#define CANFD_CFDC_ERFL_CRCREG_MASK       (0x7fffu << CANFD_CFDC_ERFL_CRCREG_SHIFT)

/****************************************************************************
 * CFDC2nDCFG — Channel Data Bitrate Configuration Register
 * Source: canfd_iodefine.h R_CANFD_CFDC2_Type.DCFG_b
 ****************************************************************************/

#define CANFD_CFDC2_DCFG_DBRP_SHIFT       (0)
#define CANFD_CFDC2_DCFG_DBRP_MASK        (0xffu << CANFD_CFDC2_DCFG_DBRP_SHIFT)
#define CANFD_CFDC2_DCFG_DTSEG1_SHIFT     (8)
#define CANFD_CFDC2_DCFG_DTSEG1_MASK      (0x1fu << CANFD_CFDC2_DCFG_DTSEG1_SHIFT)
#define CANFD_CFDC2_DCFG_DTSEG2_SHIFT     (16)
#define CANFD_CFDC2_DCFG_DTSEG2_MASK      (0x0fu << CANFD_CFDC2_DCFG_DTSEG2_SHIFT)
#define CANFD_CFDC2_DCFG_DSJW_SHIFT       (24)
#define CANFD_CFDC2_DCFG_DSJW_MASK        (0x0fu << CANFD_CFDC2_DCFG_DSJW_SHIFT)

/****************************************************************************
 * CFDC2nFDCFG — Channel CAN-FD Configuration Register
 ****************************************************************************/

#define CANFD_CFDC2_FDCFG_EOCCFG_SHIFT    (0)
#define CANFD_CFDC2_FDCFG_EOCCFG_MASK     (0x7u << CANFD_CFDC2_FDCFG_EOCCFG_SHIFT)
#define CANFD_CFDC2_FDCFG_TDCOC           (1u << 8)   /* TDC Offset Config */
#define CANFD_CFDC2_FDCFG_TDCE            (1u << 9)   /* TDC Enable */
#define CANFD_CFDC2_FDCFG_ESIC            (1u << 10)  /* Error State Indication Config */
#define CANFD_CFDC2_FDCFG_TDCO_SHIFT      (16)
#define CANFD_CFDC2_FDCFG_TDCO_MASK       (0xffu << CANFD_CFDC2_FDCFG_TDCO_SHIFT)
#define CANFD_CFDC2_FDCFG_FDOE            (1u << 28)  /* FD-Only Enable */
#define CANFD_CFDC2_FDCFG_REFE            (1u << 29)  /* RX Edge Filter Enable */
#define CANFD_CFDC2_FDCFG_CLOE            (1u << 30)  /* Classical CAN-Only Enable */
#define CANFD_CFDC2_FDCFG_CFDTE           (1u << 31)  /* CAN-FD Frame Distinction Enable */

/****************************************************************************
 * CFDGCFG — Global Configuration Register
 * Source: canfd_iodefine.h CFDGCFG_b  (offset 0x84 on RZ/V2H; 0x14 on RA8)
 * BIT LAYOUT: MATCHED between RA8 and RZ/V2H (confirmed from struct fields)
 ****************************************************************************/

#define CANFD_GCFG_TPRI                   (1u << 0)   /* Transmission Priority */
#define CANFD_GCFG_DCE                    (1u << 1)   /* DLC Check Enable */
#define CANFD_GCFG_DRE                    (1u << 2)   /* DLC Replacement Enable */
#define CANFD_GCFG_MME                    (1u << 3)   /* Mirror Mode Enable */
#define CANFD_GCFG_DCS                    (1u << 4)   /* Clock Select (0=clkc, 1=canfdclk) */
#define CANFD_GCFG_CMPOC                  (1u << 5)   /* CAN-FD Payload Overflow Config */
#define CANFD_GCFG_TSP_SHIFT              (8)
#define CANFD_GCFG_TSP_MASK               (0xfu << CANFD_GCFG_TSP_SHIFT)
#define CANFD_GCFG_TSSS                   (1u << 12)  /* Timestamp Source Select */
#define CANFD_GCFG_ITRCP_SHIFT            (16)
#define CANFD_GCFG_ITRCP_MASK             (0xffffu << CANFD_GCFG_ITRCP_SHIFT)

/****************************************************************************
 * CFDGCTR — Global Control Register
 * Source: canfd_iodefine.h CFDGCTR_b  (offset 0x88 on RZ/V2H; 0x18 on RA8)
 * BIT LAYOUT: MATCHED (GMDC/GSLPR/DEIE/MEIE/THLEIE/CMPOFIE/TSRST confirmed)
 * NOTE: RZ/V2H adds QOWEIE(12), QMEIE(14), MOWEIE(15) — RA8 does not have.
 ****************************************************************************/

#define CANFD_GCTR_GMDC_SHIFT             (0)
#define CANFD_GCTR_GMDC_MASK              (0x3u << CANFD_GCTR_GMDC_SHIFT)
#  define CANFD_GCTR_GMDC_COMM            (0u << CANFD_GCTR_GMDC_SHIFT) /* Global operation mode */
#  define CANFD_GCTR_GMDC_RESET           (1u << CANFD_GCTR_GMDC_SHIFT) /* Global reset mode */
#  define CANFD_GCTR_GMDC_HALT            (2u << CANFD_GCTR_GMDC_SHIFT) /* Global halt mode */
#define CANFD_GCTR_GSLPR                  (1u << 2)   /* Global Sleep Request */
#define CANFD_GCTR_DEIE                   (1u << 8)   /* DLC Check Interrupt Enable */
#define CANFD_GCTR_MEIE                   (1u << 9)   /* Message Lost Error Interrupt Enable */
#define CANFD_GCTR_THLEIE                 (1u << 10)  /* TX History List Entry Lost IE */
#define CANFD_GCTR_CMPOFIE                (1u << 11)  /* Payload Overflow Flag IE */
#define CANFD_GCTR_QOWEIE                 (1u << 12)  /* TXQ Overwrite Error IE (RZ/V2H only) */
#define CANFD_GCTR_QMEIE                  (1u << 14)  /* TXQ Message Lost Error IE (RZ/V2H only) */
#define CANFD_GCTR_MOWEIE                 (1u << 15)  /* GW FIFO Overwrite Error IE (RZ/V2H only) */
#define CANFD_GCTR_TSRST                  (1u << 16)  /* Timestamp Reset */

/****************************************************************************
 * CFDGSTS — Global Status Register
 ****************************************************************************/

#define CANFD_GSTS_GRSTSTS                (1u << 0)   /* Global Reset Status */
#define CANFD_GSTS_GHLTSTS                (1u << 1)   /* Global Halt Status */
#define CANFD_GSTS_GSLPSTS                (1u << 2)   /* Global Sleep Status */
#define CANFD_GSTS_GRAMINIT               (1u << 3)   /* Global RAM Initialization */

/****************************************************************************
 * CFDGERFL — Global Error Flag Register
 * NOTE: RZ/V2H has EEF0..EEF5 (bits 16-21); RA8 only EEF0 (bit 16).
 ****************************************************************************/

#define CANFD_GERFL_DEF                   (1u << 0)   /* DLC Error Flag */
#define CANFD_GERFL_MES                   (1u << 1)   /* Message Lost Error Status */
#define CANFD_GERFL_THLES                 (1u << 2)   /* TX History List Entry Lost */
#define CANFD_GERFL_CMPOF                 (1u << 3)   /* Payload Overflow Flag */
#define CANFD_GERFL_QOWES                 (1u << 4)   /* TXQ Overwrite Error Status */
#define CANFD_GERFL_QMES                  (1u << 6)   /* TXQ Message Lost Error Status */
#define CANFD_GERFL_MOWES                 (1u << 7)   /* Message Overwrite Error Status */
#define CANFD_GERFL_EEF0                  (1u << 16)  /* ECC Error Flag ch0 */
#define CANFD_GERFL_EEF1                  (1u << 17)  /* ECC Error Flag ch1 */

/****************************************************************************
 * CFDGAFLECTR — AFL Entry Control Register  (offset 0x98 on RZ/V2H)
 * NOTE: AFLPN field is 6 bits on RZ/V2H vs 4 bits on RA8 (more pages).
 ****************************************************************************/

#define CANFD_GAFLECTR_AFLPN_SHIFT        (0)
#define CANFD_GAFLECTR_AFLPN_MASK         (0x3fu << CANFD_GAFLECTR_AFLPN_SHIFT)
#define CANFD_GAFLECTR_AFLDAE             (1u << 8)   /* AFL Data Access Enable */

/****************************************************************************
 * CFDGAFLCFG0 — AFL Configuration Register  (offset 0x9C on RZ/V2H)
 * Fields: RNC1[8:0] = ch1 rule count, RNC0[24:16] = ch0 rule count
 * Source: canfd_iodefine.h CFDGAFLCFG_b (RNC0 and RNC1 swap vs RA8!)
 * DIVERGENCE from RA8: RA8 only has RNC0[20:16] (5 bits). RZ/V2H has
 * 9-bit rule count fields and the word layout is RNC1 in [8:0], RNC0 in
 * [24:16] — reversed field positions vs RA8 which has RNC0 in [20:16].
 ****************************************************************************/

#define CANFD_GAFLCFG_RNC1_SHIFT          (0)
#define CANFD_GAFLCFG_RNC1_MASK           (0x1ffu << CANFD_GAFLCFG_RNC1_SHIFT)
#define CANFD_GAFLCFG_RNC0_SHIFT          (16)
#define CANFD_GAFLCFG_RNC0_MASK           (0x1ffu << CANFD_GAFLCFG_RNC0_SHIFT)

/****************************************************************************
 * CFDRMNB — RX Message Buffer Number Register  (offset 0xAC on RZ/V2H)
 ****************************************************************************/

#define CANFD_RMNB_NRXMB_SHIFT            (0)
#define CANFD_RMNB_NRXMB_MASK             (0xffu << CANFD_RMNB_NRXMB_SHIFT)
#define CANFD_RMNB_RMPLS_SHIFT            (8)
#define CANFD_RMNB_RMPLS_MASK             (0x7u << CANFD_RMNB_RMPLS_SHIFT)
#  define CANFD_RMNB_RMPLS_8B             (0u << CANFD_RMNB_RMPLS_SHIFT)
#  define CANFD_RMNB_RMPLS_12B            (1u << CANFD_RMNB_RMPLS_SHIFT)
#  define CANFD_RMNB_RMPLS_16B            (2u << CANFD_RMNB_RMPLS_SHIFT)
#  define CANFD_RMNB_RMPLS_20B            (3u << CANFD_RMNB_RMPLS_SHIFT)
#  define CANFD_RMNB_RMPLS_24B            (4u << CANFD_RMNB_RMPLS_SHIFT)
#  define CANFD_RMNB_RMPLS_32B            (5u << CANFD_RMNB_RMPLS_SHIFT)
#  define CANFD_RMNB_RMPLS_48B            (6u << CANFD_RMNB_RMPLS_SHIFT)
#  define CANFD_RMNB_RMPLS_64B            (7u << CANFD_RMNB_RMPLS_SHIFT)

/****************************************************************************
 * CFDRFCCn — RX FIFO Configuration/Control Register  (CFDRFCCn, n=0..7)
 * Offset: 0xC0 + n*4 on RZ/V2H  (0x3C + n*4 on RA8, only 2 FIFOs)
 * BIT LAYOUT: bit definitions MATCHED.  RFFIE(16) is new in RZ/V2H.
 ****************************************************************************/

#define CANFD_RFCC_RFE                    (1u << 0)   /* RX FIFO Enable */
#define CANFD_RFCC_RFIE                   (1u << 1)   /* RX FIFO Interrupt Enable */
#define CANFD_RFCC_RFPLS_SHIFT            (4)
#define CANFD_RFCC_RFPLS_MASK             (0x7u << CANFD_RFCC_RFPLS_SHIFT)
#  define CANFD_RFCC_RFPLS_8B             (0u << CANFD_RFCC_RFPLS_SHIFT)
#  define CANFD_RFCC_RFPLS_12B            (1u << CANFD_RFCC_RFPLS_SHIFT)
#  define CANFD_RFCC_RFPLS_16B            (2u << CANFD_RFCC_RFPLS_SHIFT)
#  define CANFD_RFCC_RFPLS_20B            (3u << CANFD_RFCC_RFPLS_SHIFT)
#  define CANFD_RFCC_RFPLS_24B            (4u << CANFD_RFCC_RFPLS_SHIFT)
#  define CANFD_RFCC_RFPLS_32B            (5u << CANFD_RFCC_RFPLS_SHIFT)
#  define CANFD_RFCC_RFPLS_48B            (6u << CANFD_RFCC_RFPLS_SHIFT)
#  define CANFD_RFCC_RFPLS_64B            (7u << CANFD_RFCC_RFPLS_SHIFT)
#define CANFD_RFCC_RFDC_SHIFT             (8)
#define CANFD_RFCC_RFDC_MASK              (0x7u << CANFD_RFCC_RFDC_SHIFT)
#  define CANFD_RFCC_RFDC_0               (0u << CANFD_RFCC_RFDC_SHIFT)  /* depth=0 */
#  define CANFD_RFCC_RFDC_4               (1u << CANFD_RFCC_RFDC_SHIFT)  /* depth=4 */
#  define CANFD_RFCC_RFDC_8               (2u << CANFD_RFCC_RFDC_SHIFT)  /* depth=8 */
#  define CANFD_RFCC_RFDC_16              (3u << CANFD_RFCC_RFDC_SHIFT)  /* depth=16 */
#  define CANFD_RFCC_RFDC_32              (4u << CANFD_RFCC_RFDC_SHIFT)  /* depth=32 */
#  define CANFD_RFCC_RFDC_48              (5u << CANFD_RFCC_RFDC_SHIFT)  /* depth=48 */
#define CANFD_RFCC_RFIM                   (1u << 12)  /* RX FIFO Interrupt Mode */
#define CANFD_RFCC_RFIGCV_SHIFT           (13)
#define CANFD_RFCC_RFIGCV_MASK            (0x7u << CANFD_RFCC_RFIGCV_SHIFT)
#define CANFD_RFCC_RFFIE                  (1u << 16)  /* RX FIFO Full Interrupt Enable (RZ/V2H only) */

/****************************************************************************
 * CFDRFSTSn — RX FIFO Status Register
 ****************************************************************************/

#define CANFD_RFSTS_RFEMP                 (1u << 0)   /* RX FIFO Empty */
#define CANFD_RFSTS_RFFLL                 (1u << 1)   /* RX FIFO Full */
#define CANFD_RFSTS_RFMLT                 (1u << 2)   /* RX FIFO Message Lost */
#define CANFD_RFSTS_RFIF                  (1u << 3)   /* RX FIFO Interrupt Flag */
#define CANFD_RFSTS_RFMC_SHIFT            (8)
#define CANFD_RFSTS_RFMC_MASK             (0xffu << CANFD_RFSTS_RFMC_SHIFT)

/****************************************************************************
 * CFDCFCCn — Common FIFO Configuration/Control Register  (n=0..17)
 * Offset: 0x120 + n*4 on RZ/V2H  (0x54 on RA8, 1 entry)
 * BIT LAYOUT: MATCHED.  Additional CFTML/CFDC/CFITT fields confirmed.
 ****************************************************************************/

#define CANFD_CFCC_CFE                    (1u << 0)   /* Common FIFO Enable */
#define CANFD_CFCC_CFRXIE                 (1u << 1)   /* Common FIFO RX Interrupt Enable */
#define CANFD_CFCC_CFTXIE                 (1u << 2)   /* Common FIFO TX Interrupt Enable */
#define CANFD_CFCC_CFPLS_SHIFT            (4)
#define CANFD_CFCC_CFPLS_MASK             (0x7u << CANFD_CFCC_CFPLS_SHIFT)
#  define CANFD_CFCC_CFPLS_8B             (0u << CANFD_CFCC_CFPLS_SHIFT)
#  define CANFD_CFCC_CFPLS_12B            (1u << CANFD_CFCC_CFPLS_SHIFT)
#  define CANFD_CFCC_CFPLS_16B            (2u << CANFD_CFCC_CFPLS_SHIFT)
#  define CANFD_CFCC_CFPLS_20B            (3u << CANFD_CFCC_CFPLS_SHIFT)
#  define CANFD_CFCC_CFPLS_24B            (4u << CANFD_CFCC_CFPLS_SHIFT)
#  define CANFD_CFCC_CFPLS_32B            (5u << CANFD_CFCC_CFPLS_SHIFT)
#  define CANFD_CFCC_CFPLS_48B            (6u << CANFD_CFCC_CFPLS_SHIFT)
#  define CANFD_CFCC_CFPLS_64B            (7u << CANFD_CFCC_CFPLS_SHIFT)
#define CANFD_CFCC_CFM_SHIFT              (8)
#define CANFD_CFCC_CFM_MASK               (0x3u << CANFD_CFCC_CFM_SHIFT)
#  define CANFD_CFCC_CFM_RX               (0u << CANFD_CFCC_CFM_SHIFT)  /* RX FIFO mode */
#  define CANFD_CFCC_CFM_TX               (1u << CANFD_CFCC_CFM_SHIFT)  /* TX FIFO mode */
#define CANFD_CFCC_CFITSS                 (1u << 10)  /* Interval Timer Source Select */
#define CANFD_CFCC_CFITR                  (1u << 11)  /* Interval Timer Resolution */
#define CANFD_CFCC_CFIM                   (1u << 12)  /* Common FIFO Interrupt Mode */
#define CANFD_CFCC_CFIGCV_SHIFT           (13)
#define CANFD_CFCC_CFIGCV_MASK            (0x7u << CANFD_CFCC_CFIGCV_SHIFT)
#define CANFD_CFCC_CFTML_SHIFT            (16)
#define CANFD_CFCC_CFTML_MASK             (0x1fu << CANFD_CFCC_CFTML_SHIFT)
#define CANFD_CFCC_CFDC_SHIFT             (21)
#define CANFD_CFCC_CFDC_MASK              (0x7u << CANFD_CFCC_CFDC_SHIFT)
#define CANFD_CFCC_CFITT_SHIFT            (24)
#define CANFD_CFCC_CFITT_MASK             (0xffu << CANFD_CFCC_CFITT_SHIFT)

/****************************************************************************
 * CFDCFSTSn — Common FIFO Status Register
 ****************************************************************************/

#define CANFD_CFSTS_CFEMP                 (1u << 0)   /* Common FIFO Empty */
#define CANFD_CFSTS_CFFLL                 (1u << 1)   /* Common FIFO Full */
#define CANFD_CFSTS_CFMLT                 (1u << 2)   /* Common FIFO Message Lost */
#define CANFD_CFSTS_CFRXIF                (1u << 3)   /* Common RX FIFO Interrupt Flag */
#define CANFD_CFSTS_CFTXIF                (1u << 4)   /* Common TX FIFO Interrupt Flag */
#define CANFD_CFSTS_CFMC_SHIFT            (8)
#define CANFD_CFSTS_CFMC_MASK             (0xffu << CANFD_CFSTS_CFMC_SHIFT)

/****************************************************************************
 * CFDTMC — TX Message Buffer Control Register (byte, one per mailbox)
 * Offset: 0x2D0 + mailbox_n  (mailbox_n = 0..383)
 ****************************************************************************/

#define CANFD_TMC_TMTR                    (1u << 0)   /* TX MB Transmission Request */
#define CANFD_TMC_TMTAR                   (1u << 1)   /* TX MB Transmission Abort Request */
#define CANFD_TMC_TMOM                    (1u << 2)   /* TX MB One-shot Mode */

/****************************************************************************
 * CFDTMSTS — TX Message Buffer Status Register (byte, one per mailbox)
 * Offset: 0x7D0 + mailbox_n
 ****************************************************************************/

#define CANFD_TMSTS_TMTSTS                (1u << 0)   /* TX MB Transmission Status */
#define CANFD_TMSTS_TMTRF_SHIFT           (1)
#define CANFD_TMSTS_TMTRF_MASK            (0x3u << CANFD_TMSTS_TMTRF_SHIFT)
#  define CANFD_TMSTS_TMTRF_NONE          (0u << CANFD_TMSTS_TMTRF_SHIFT)
#  define CANFD_TMSTS_TMTRF_ABORT         (1u << CANFD_TMSTS_TMTRF_SHIFT)
#  define CANFD_TMSTS_TMTRF_TX_OK         (2u << CANFD_TMSTS_TMTRF_SHIFT)
#define CANFD_TMSTS_TMTRM                 (1u << 3)   /* TX Request Mirrored */
#define CANFD_TMSTS_TMTARM                (1u << 4)   /* TX Abort Request Mirrored */

/****************************************************************************
 * TX Message Buffer ID Register (CFDTMIDn, in TM access area)
 ****************************************************************************/

#define CANFD_TMID_TMID_SHIFT             (0)
#define CANFD_TMID_TMID_MASK              (0x1fffffffu)
#define CANFD_TMID_THLEN                  (1u << 29)  /* THL Entry Enable */
#define CANFD_TMID_TMRTR                  (1u << 30)  /* RTR Frame */
#define CANFD_TMID_TMIDE                  (1u << 31)  /* IDE Bit (extended ID) */

/****************************************************************************
 * TX Message Buffer Pointer Register (CFDTMPTRn)
 ****************************************************************************/

#define CANFD_TMPTR_TMDLC_SHIFT           (28)
#define CANFD_TMPTR_TMDLC_MASK            (0xfu << CANFD_TMPTR_TMDLC_SHIFT)

/****************************************************************************
 * TX Message Buffer FD Control Register (CFDTMFDCTRn)
 ****************************************************************************/

#define CANFD_TMFDCTR_TMESI               (1u << 0)   /* Error State Indicator */
#define CANFD_TMFDCTR_TMBRS               (1u << 1)   /* Bit Rate Switch */
#define CANFD_TMFDCTR_TMFDF               (1u << 2)   /* CAN FD Format */
#define CANFD_TMFDCTR_TMIFL_SHIFT         (8)
#define CANFD_TMFDCTR_TMIFL_MASK          (0x3u << CANFD_TMFDCTR_TMIFL_SHIFT)
#define CANFD_TMFDCTR_TMPTR_SHIFT         (16)
#define CANFD_TMFDCTR_TMPTR_MASK          (0xffffu << CANFD_TMFDCTR_TMPTR_SHIFT)

/****************************************************************************
 * RX FIFO Access Registers (CFDRFxx, in RF access area)
 ****************************************************************************/

#define CANFD_RFID_RFID_MASK              (0x1fffffffu)
#define CANFD_RFID_RFRTR                  (1u << 30)  /* RTR Frame */
#define CANFD_RFID_RFIDE                  (1u << 31)  /* IDE Bit */

#define CANFD_RFPTR_RFTS_SHIFT            (0)
#define CANFD_RFPTR_RFTS_MASK             (0xffffu)
#define CANFD_RFPTR_RFDLC_SHIFT           (28)
#define CANFD_RFPTR_RFDLC_MASK            (0xfu << CANFD_RFPTR_RFDLC_SHIFT)

#define CANFD_RFFDSTS_RFESI               (1u << 0)   /* Error State Indicator */
#define CANFD_RFFDSTS_RFBRS               (1u << 1)   /* Bit Rate Switch */
#define CANFD_RFFDSTS_RFFDF               (1u << 2)   /* CAN FD Format */
#define CANFD_RFFDSTS_RFIFL_SHIFT         (8)
#define CANFD_RFFDSTS_RFIFL_MASK          (0x3u << CANFD_RFFDSTS_RFIFL_SHIFT)
#define CANFD_RFFDSTS_RFPTR_SHIFT         (16)
#define CANFD_RFFDSTS_RFPTR_MASK          (0xffffu << CANFD_RFFDSTS_RFPTR_SHIFT)

/****************************************************************************
 * Common FIFO Access Registers (CFDCFxx)
 ****************************************************************************/

#define CANFD_CFID_CFID_MASK              (0x1fffffffu)
#define CANFD_CFID_THLEN                  (1u << 29)  /* THL Entry Enable */
#define CANFD_CFID_CFRTR                  (1u << 30)  /* RTR Frame */
#define CANFD_CFID_CFIDE                  (1u << 31)  /* IDE Bit */

#define CANFD_CFPTR_CFTS_SHIFT            (0)
#define CANFD_CFPTR_CFTS_MASK             (0xffffu)
#define CANFD_CFPTR_CFDLC_SHIFT           (28)
#define CANFD_CFPTR_CFDLC_MASK            (0xfu << CANFD_CFPTR_CFDLC_SHIFT)

#define CANFD_CFFDSTS_CFESI               (1u << 0)
#define CANFD_CFFDSTS_CFBRS               (1u << 1)
#define CANFD_CFFDSTS_CFFDF               (1u << 2)
#define CANFD_CFFDSTS_CFIFL_SHIFT         (8)
#define CANFD_CFFDSTS_CFIFL_MASK          (0x3u << CANFD_CFFDSTS_CFIFL_SHIFT)

/****************************************************************************
 * AFL Entry Registers (CFDGAFL, in AFL area at offset 0x1800)
 ****************************************************************************/

#define CANFD_AFL_ID_GAFLID_SHIFT         (0)
#define CANFD_AFL_ID_GAFLID_MASK          (0x1fffffffu)
#define CANFD_AFL_ID_GAFLLB               (1u << 29)  /* Loopback Configuration */
#define CANFD_AFL_ID_GAFLRTR              (1u << 30)  /* RTR Field */
#define CANFD_AFL_ID_GAFLIDE              (1u << 31)  /* IDE Field */

#define CANFD_AFL_M_GAFLIDM_SHIFT         (0)
#define CANFD_AFL_M_GAFLIDM_MASK          (0x1fffffffu)
#define CANFD_AFL_M_GAFLIFL1              (1u << 29)
#define CANFD_AFL_M_GAFLRTRM              (1u << 30)
#define CANFD_AFL_M_GAFLIDEM              (1u << 31)

#define CANFD_AFL_P0_GAFLDLC_SHIFT        (0)
#define CANFD_AFL_P0_GAFLDLC_MASK         (0xfu)
#define CANFD_AFL_P0_GAFLRMDP_SHIFT       (8)
#define CANFD_AFL_P0_GAFLRMDP_MASK        (0x1fu << CANFD_AFL_P0_GAFLRMDP_SHIFT)
#define CANFD_AFL_P0_GAFLRMV              (1u << 15)  /* RX MB Direction Valid */
#define CANFD_AFL_P0_GAFLPTR_SHIFT        (16)
#define CANFD_AFL_P0_GAFLPTR_MASK         (0xffffu << CANFD_AFL_P0_GAFLPTR_SHIFT)

#define CANFD_AFL_P1_GAFLFDP_SHIFT        (0)
#define CANFD_AFL_P1_GAFLFDP_MASK         (0x3ffffffu)  /* FIFO Direction Pointer */

/****************************************************************************
 * FIFO Status Register helpers
 ****************************************************************************/

#define CANFD_FESTS_RFXEMP_SHIFT          (0)
#define CANFD_FESTS_RFXEMP_MASK           (0xffu)      /* RX FIFO 0..7 empty bits */
#define CANFD_FESTS_CFXEMP_SHIFT          (8)
#define CANFD_FESTS_CFXEMP_MASK           (0x3ffffu << CANFD_FESTS_CFXEMP_SHIFT) /* CF 0..17 empty */

/****************************************************************************
 * CPG Clock / Reset gate identifiers for RZ/V2H CAN-FD
 *
 * CORRECTION from previous stub:
 *   Old (WRONG): RZV_CPG_CLK_CANFD = (7 << 16 | 0)
 *   New: (9 << 16 | 12) — CPG_CLKON_9 bits [14:12] (3-bit mask, 7U<<12)
 *   Source: bsp_override.h line 1692-1693 for R9A09G057H (RZ/V2H)
 *     #define BSP_CLKON_REG_FSP_IP_CANFD(ch)  (R_CPG->CPG_CLKON_9)
 *     #define BSP_CLKON_BIT_FSP_IP_CANFD(ch)  (7U << R_CPG_CPG_CLKON_9_CLK12_ON_Pos)
 *     R_CPG_CPG_CLKON_9_CLK12_ON_Pos = 12 (cpg_iobitmask.h:1319)
 *
 * Module stop:  CPG_BUS_MCPU2_MSTOP bit 9 (MSTOP9_ON_Pos)
 *   Source: bsp_module_stop.h line 165-168
 *
 * Reset:  CPG_RST_10 bits [2:1] (3U<<1, both UNIT0_RSTB and UNIT1_RSTB)
 *   Source: bsp_override.h line 1698-1699
 *     #define BSP_RST_REG_FSP_IP_CANFD(ch)  (R_CPG->CPG_RST_10)
 *     #define BSP_RST_BIT_FSP_IP_CANFD(ch)  (3U << R_CPG_CPG_RST_10_RSTB1_Pos)
 *     R_CPG_CPG_RST_10_RSTB1_Pos = 1 (cpg_iobitmask.h:3703)
 *
 * The RZV_CPG_CLK_CANFD encoding (CLKON_reg_index << 16 | bit_position):
 *   CLKON_reg = 9, bit_pos = 12  → (9 << 16 | 12)
 *
 * IMPORTANT: the rzv_clock.h file MUST be updated to fix this.
 *   See rzv_clock.h update in same phase.
 ****************************************************************************/

/* These are informational — the actual CPG control is in rzv_clock.h */

#define RZV_CANFD_CLKON_REG_INDEX         9    /* CPG_CLKON_9 */
#define RZV_CANFD_CLKON_BIT_POS           12   /* CLK12_ON_Pos */
#define RZV_CANFD_CLKON_BITS              7u   /* 3-bit mask (CLK12/13/14) */

#define RZV_CANFD_RST_REG_INDEX           10   /* CPG_RST_10 */
#define RZV_CANFD_RST_BIT_POS             1    /* RSTB1_Pos */
#define RZV_CANFD_RST_BITS                3u   /* 2-bit mask (UNIT0+UNIT1) */

/****************************************************************************
 * Convenience: mailbox index for ch0 / ch1 TX mailbox 0
 * On RZ/V2H the per-channel TX mailbox 0 is at global mailbox index:
 *   ch0 → mailbox 0
 *   ch1 → mailbox 16  (each channel has 16 mailboxes in the 384-entry array)
 *   General: ch_n → n * 16
 ****************************************************************************/

#define RZV_CANFD_TXMB_CH(ch)             ((uint32_t)(ch) * 16u)
#define RZV_CANFD_TXMB_CH0_MB0            0    /* Channel 0, mailbox 0 */
#define RZV_CANFD_TXMB_CH1_MB0            16   /* Channel 1, mailbox 0 */

/****************************************************************************
 * Common FIFO index: CH0 uses common FIFO 0, CH1 uses common FIFO 3
 * (CFIFO_CHANNEL_OFFSET=3 for non-LITE mode).
 ****************************************************************************/

#define RZV_CANFD_CFIFO_CH_OFFSET         3u   /* Common FIFO index = ch * 3 */
#define RZV_CANFD_CFIFO_CH(ch)            ((uint32_t)(ch) * RZV_CANFD_CFIFO_CH_OFFSET)

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_CANFD_H */

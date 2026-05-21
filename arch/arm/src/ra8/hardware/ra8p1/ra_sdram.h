/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_sdram.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SDRAM_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SDRAM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SDRAM Controller Register Base (within BUS peripheral) */

#define RA_SDRAM_BASE               (R_BUS_SDRAM)

/* SDRAM Register Offsets (relative to R_BUS_SDRAM) */

#define RA_SDRAM_SDCCR_OFFSET       0x00  /* SDC Control Register */
#define RA_SDRAM_SDCMOD_OFFSET      0x01  /* SDC Mode Register */
#define RA_SDRAM_SDAMOD_OFFSET      0x02  /* SDRAM Access Mode Register */
#define RA_SDRAM_SDSELF_OFFSET      0x10  /* SDRAM Self-Refresh Control Register */
#define RA_SDRAM_SDRFCR_OFFSET      0x14  /* SDRAM Refresh Control Register */
#define RA_SDRAM_SDRFEN_OFFSET      0x16  /* SDRAM Auto-Refresh Control Register */
#define RA_SDRAM_SDICR_OFFSET       0x20  /* SDRAM Initialization Control Register */
#define RA_SDRAM_SDIR_OFFSET        0x24  /* SDRAM Initialization Register */
#define RA_SDRAM_SDADR_OFFSET       0x40  /* SDRAM Address Register */
#define RA_SDRAM_SDTR_OFFSET        0x44  /* SDRAM Timing Register */
#define RA_SDRAM_SDMOD_OFFSET       0x48  /* SDRAM Mode Register */
#define RA_SDRAM_SDSR_OFFSET        0x50  /* SDRAM Status Register */

/* Register Addresses */

#define RA_SDRAM_SDCCR              (RA_SDRAM_BASE + RA_SDRAM_SDCCR_OFFSET)
#define RA_SDRAM_SDCMOD             (RA_SDRAM_BASE + RA_SDRAM_SDCMOD_OFFSET)
#define RA_SDRAM_SDAMOD             (RA_SDRAM_BASE + RA_SDRAM_SDAMOD_OFFSET)
#define RA_SDRAM_SDSELF             (RA_SDRAM_BASE + RA_SDRAM_SDSELF_OFFSET)
#define RA_SDRAM_SDRFCR             (RA_SDRAM_BASE + RA_SDRAM_SDRFCR_OFFSET)
#define RA_SDRAM_SDRFEN             (RA_SDRAM_BASE + RA_SDRAM_SDRFEN_OFFSET)
#define RA_SDRAM_SDICR              (RA_SDRAM_BASE + RA_SDRAM_SDICR_OFFSET)
#define RA_SDRAM_SDIR               (RA_SDRAM_BASE + RA_SDRAM_SDIR_OFFSET)
#define RA_SDRAM_SDADR              (RA_SDRAM_BASE + RA_SDRAM_SDADR_OFFSET)
#define RA_SDRAM_SDTR               (RA_SDRAM_BASE + RA_SDRAM_SDTR_OFFSET)
#define RA_SDRAM_SDMOD              (RA_SDRAM_BASE + RA_SDRAM_SDMOD_OFFSET)
#define RA_SDRAM_SDSR               (RA_SDRAM_BASE + RA_SDRAM_SDSR_OFFSET)

/* SDCCR - SDC Control Register */

#define SDCCR_EXENB                 (1 << 0)  /* Operation Enable */
#define SDCCR_BSIZE_SHIFT           4
#define SDCCR_BSIZE_MASK            (3 << SDCCR_BSIZE_SHIFT)
#define SDCCR_BSIZE_16BIT           (0 << SDCCR_BSIZE_SHIFT)
#define SDCCR_BSIZE_32BIT           (1 << SDCCR_BSIZE_SHIFT)
#define SDCCR_BSIZE_8BIT            (2 << SDCCR_BSIZE_SHIFT)

/* SDCMOD - SDC Mode Register */

#define SDCMOD_EMODE                (1 << 0)  /* Endian Mode */

/* SDAMOD - SDRAM Access Mode Register */

#define SDAMOD_BE                   (1 << 0)  /* Continuous Access Enable */

/* SDSELF - SDRAM Self-Refresh Control Register */

#define SDSELF_SFEN                 (1 << 0)  /* Self-Refresh Enable */

/* SDRFCR - SDRAM Refresh Control Register */

#define SDRFCR_RFC_SHIFT            0
#define SDRFCR_RFC_MASK             0xfff
#define SDRFCR_REFW_SHIFT           12
#define SDRFCR_REFW_MASK            (0xf << SDRFCR_REFW_SHIFT)

/* SDRFEN - SDRAM Auto-Refresh Control Register */

#define SDRFEN_RFEN                 (1 << 0)  /* Auto-Refresh Enable */

/* SDICR - SDRAM Initialization Sequence Control Register */

#define SDICR_INIRQ                 (1 << 0)  /* Initialization Sequence Start */

/* SDIR - SDRAM Initialization Register */

#define SDIR_ARFI_SHIFT             0
#define SDIR_ARFI_MASK              0xf
#define SDIR_ARFC_SHIFT             4
#define SDIR_ARFC_MASK              (0xf << SDIR_ARFC_SHIFT)
#define SDIR_PRC_SHIFT              8
#define SDIR_PRC_MASK               (0x7 << SDIR_PRC_SHIFT)

/* SDADR - SDRAM Address Register */

#define SDADR_MXC_SHIFT             0
#define SDADR_MXC_MASK              0x3

/* SDTR - SDRAM Timing Register */

#define SDTR_CL_SHIFT               0
#define SDTR_CL_MASK                0x7
#define SDTR_WR                     (1 << 8)
#define SDTR_RP_SHIFT               9
#define SDTR_RP_MASK                (0x7 << SDTR_RP_SHIFT)
#define SDTR_RCD_SHIFT              12
#define SDTR_RCD_MASK               (0x3 << SDTR_RCD_SHIFT)
#define SDTR_RAS_SHIFT              16
#define SDTR_RAS_MASK               (0x7 << SDTR_RAS_SHIFT)

/* SDMOD - SDRAM Mode Register */

#define SDMOD_MR_SHIFT              0
#define SDMOD_MR_MASK               0x7fff

/* Mode Register bits for SDRAM device */

#define MR_BURST_LENGTH_1           0
#define MR_BURST_TYPE_SEQUENTIAL    (0 << 3)
#define MR_CAS_LATENCY_SHIFT        4
#define MR_OP_MODE_STANDARD         (0 << 7)
#define MR_WB_SINGLE_LOC_ACC        (1 << 9)

/* SDSR - SDRAM Status Register */

#define SDSR_MRSST                  (1 << 0)  /* Mode Register Setting Status */
#define SDSR_INIST                  (1 << 3)  /* Initialization Status */
#define SDSR_SRFST                  (1 << 4)  /* Self-Refresh Status */

/* Timeout values for SDRAM operations (in microseconds) */

#define RA_SDRAM_TIMEOUT_US         1000000   /* 1 second timeout */
#define RA_SDRAM_POLL_DELAY_US      1         /* 1 microsecond poll delay */

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SDRAM_H */

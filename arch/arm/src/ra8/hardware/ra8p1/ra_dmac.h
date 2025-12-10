/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_dmac.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DMAC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DMAC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DMAC Base Addresses - Two DMAC units, each with 8 channels */
/* DMAC Unit 0: Channels 0-7  (DMAC0-DMAC7)   at 0x4000A000-0x4000A1C0 */
/* DMAC Unit 1: Channels 10-17 (DMAC10-DMAC17) at 0x4000A200-0x4000A3C0 */
#ifndef R_DMAC0_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_DMAC0_BASE          0x4000a000  /* DMAC Unit 0 base */
#define R_DMAC1_BASE          0x4000a200  /* DMAC Unit 1 base */
#else
#define R_DMAC0_BASE          0x5000a000  /* DMAC Unit 0 base (Non-secure) */
#define R_DMAC1_BASE          0x5000a200  /* DMAC Unit 1 base (Non-secure) */
#endif
#endif

/* Legacy compatibility: R_DMAC_BASE maps to DMAC Unit 0 */
#ifndef R_DMAC_BASE
#define R_DMAC_BASE           R_DMAC0_BASE
#endif

/* Channel stride within a DMAC unit */
#define R_DMAC_CH_STRIDE      0x00000040

/* Channel base address calculation:
 * - Channels 0-7:   DMAC Unit 0, ch = 0-7
 * - Channels 10-17: DMAC Unit 1, ch = 10-17 (unit 1, local ch 0-7)
 */
#define R_DMAC_CH_BASE(ch)    (((ch) < 10) ? \
                               (R_DMAC0_BASE + ((uint32_t)(ch) * R_DMAC_CH_STRIDE)) : \
                               (R_DMAC1_BASE + ((uint32_t)((ch) - 10) * R_DMAC_CH_STRIDE)))

/* DMAC Register Offsets */

#define R_DMAC_DMSAR_OFFSET                       0x00000000  /* DMA Source Address Register */
#define R_DMAC_DMDAR_OFFSET                       0x00000004  /* DMA Destination Address Register */
#define R_DMAC_DMCRA_OFFSET                       0x00000008  /* DMA Transfer Count Register */
#define R_DMAC_DMCRB_OFFSET                       0x0000000c  /* DMA Block Transfer Count Register */
#define R_DMAC_DMTMD_OFFSET                       0x00000010  /* DMA Transfer Mode Register */
#define R_DMAC_DMINT_OFFSET                       0x00000013  /* DMA Interrupt Setting Register */
#define R_DMAC_DMAMD_OFFSET                       0x00000014  /* DMA Address Mode Register */
#define R_DMAC_DMOFR_OFFSET                       0x00000018  /* DMA Offset Register */
#define R_DMAC_DMCNT_OFFSET                       0x0000001c  /* DMA Transfer Enable Register */
#define R_DMAC_DMREQ_OFFSET                       0x0000001d  /* DMA Software Start Register */
#define R_DMAC_DMSTS_OFFSET                       0x0000001e  /* DMA Status Register */
#define R_DMAC_DMSRR_OFFSET                       0x00000020  /* DMA Source Reload Address Register */
#define R_DMAC_DMDRR_OFFSET                       0x00000024  /* DMA Destination Reload Address Register */
#define R_DMAC_DMSBS_OFFSET                       0x00000028  /* DMA Source Buffer Size Register */
#define R_DMAC_DMDBS_OFFSET                       0x0000002c  /* DMA Destination Buffer Size Register */
#define R_DMAC_DMBWR_OFFSET                       0x00000030  /* DMA Bufferable Write Enable Register */

/* DMAC Register Addresses */

#define R_DMAC_DMSAR(n)                           (R_DMAC_CH_BASE(n) + R_DMAC_DMSAR_OFFSET)
#define R_DMAC_DMDAR(n)                           (R_DMAC_CH_BASE(n) + R_DMAC_DMDAR_OFFSET)
#define R_DMAC_DMCRA(n)                           (R_DMAC_CH_BASE(n) + R_DMAC_DMCRA_OFFSET)
#define R_DMAC_DMCRB(n)                           (R_DMAC_CH_BASE(n) + R_DMAC_DMCRB_OFFSET)
#define R_DMAC_DMTMD(n)                           (R_DMAC_CH_BASE(n) + R_DMAC_DMTMD_OFFSET)
#define R_DMAC_DMINT(n)                           (R_DMAC_CH_BASE(n) + R_DMAC_DMINT_OFFSET)
#define R_DMAC_DMAMD(n)                           (R_DMAC_CH_BASE(n) + R_DMAC_DMAMD_OFFSET)
#define R_DMAC_DMOFR(n)                           (R_DMAC_CH_BASE(n) + R_DMAC_DMOFR_OFFSET)
#define R_DMAC_DMCNT(n)                           (R_DMAC_CH_BASE(n) + R_DMAC_DMCNT_OFFSET)
#define R_DMAC_DMREQ(n)                           (R_DMAC_CH_BASE(n) + R_DMAC_DMREQ_OFFSET)
#define R_DMAC_DMSTS(n)                           (R_DMAC_CH_BASE(n) + R_DMAC_DMSTS_OFFSET)
#define R_DMAC_DMSRR(n)                           (R_DMAC_CH_BASE(n) + R_DMAC_DMSRR_OFFSET)
#define R_DMAC_DMDRR(n)                           (R_DMAC_CH_BASE(n) + R_DMAC_DMDRR_OFFSET)
#define R_DMAC_DMSBS(n)                           (R_DMAC_CH_BASE(n) + R_DMAC_DMSBS_OFFSET)
#define R_DMAC_DMDBS(n)                           (R_DMAC_CH_BASE(n) + R_DMAC_DMDBS_OFFSET)
#define R_DMAC_DMBWR(n)                           (R_DMAC_CH_BASE(n) + R_DMAC_DMBWR_OFFSET)

/* Register bit definitions */
/* DMSAR Register bit definitions */
#define R_DMAC_DMSAR_DMSAR_SHIFT                  (0)  /* Specifies the transfer source start address. */
#define R_DMAC_DMSAR_DMSAR_MASK                   0xffffffff

/* DMDAR Register bit definitions */
#define R_DMAC_DMDAR_DMDAR_SHIFT                  (0)  /* Specifies the transfer destination start address. */
#define R_DMAC_DMDAR_DMDAR_MASK                   0xffffffff

/* DMCRA Register bit definitions */
#define R_DMAC_DMCRA_DMCRAH_SHIFT                 (16)  /* Upper bits of transfer count */
#define R_DMAC_DMCRA_DMCRAH_MASK                  0x3ff0000

#define R_DMAC_DMCRA_DMCRAL_SHIFT                 (0)  /* Lower bits of transfer count */
#define R_DMAC_DMCRA_DMCRAL_MASK                  0xffff

/* DMCRB Register bit definitions */
#define R_DMAC_DMCRB_DMCRBL_SHIFT                 (0)  /* Functions as a number of block, repeat or repeat-block transfer counter. */
#define R_DMAC_DMCRB_DMCRBL_MASK                  0xffff
#  define R_DMAC_DMCRB_DMCRBL_0000                        (0 << R_DMAC_DMCRB_DMCRBL_SHIFT)  /* 65,536 blocks */

#define R_DMAC_DMCRB_DMCRBH_SHIFT                 (16)  /* Specifies the number of block transfer operations or repeat transfer operations. */
#define R_DMAC_DMCRB_DMCRBH_MASK                  0xffff0000
#  define R_DMAC_DMCRB_DMCRBH_0000                        (0 << R_DMAC_DMCRB_DMCRBH_SHIFT)  /* 65,536 blocks */

/* DMTMD Register bit definitions */
#define R_DMAC_DMTMD_MD_SHIFT                     (14)  /* Transfer Mode Select */
#define R_DMAC_DMTMD_MD_MASK                      0xc000
#  define R_DMAC_DMTMD_MD_00                              (0 << R_DMAC_DMTMD_MD_SHIFT)  /* Normal transfer */
#  define R_DMAC_DMTMD_MD_01                              (1 << R_DMAC_DMTMD_MD_SHIFT)  /* Repeat transfer */
#  define R_DMAC_DMTMD_MD_10                              (2 << R_DMAC_DMTMD_MD_SHIFT)  /* Block transfer */
#  define R_DMAC_DMTMD_MD_11                              (3 << R_DMAC_DMTMD_MD_SHIFT)  /* Setting prohibited */

#define R_DMAC_DMTMD_DTS_SHIFT                    (12)  /* Repeat Area Select */
#define R_DMAC_DMTMD_DTS_MASK                     0x3000
#  define R_DMAC_DMTMD_DTS_00                             (0 << R_DMAC_DMTMD_DTS_SHIFT)  /* The destination is specified as the repeat area or block area. */
#  define R_DMAC_DMTMD_DTS_01                             (1 << R_DMAC_DMTMD_DTS_SHIFT)  /* The source is specified as the repeat area or block area. */
#  define R_DMAC_DMTMD_DTS_10                             (2 << R_DMAC_DMTMD_DTS_SHIFT)  /* The repeat area or block area is not specified. */
#  define R_DMAC_DMTMD_DTS_11                             (3 << R_DMAC_DMTMD_DTS_SHIFT)  /* Setting prohibited */

#define R_DMAC_DMTMD_SZ_SHIFT                     (8)  /* Transfer Data Size Select */
#define R_DMAC_DMTMD_SZ_MASK                      0x300
#  define R_DMAC_DMTMD_SZ_00                              (0 << R_DMAC_DMTMD_SZ_SHIFT)  /* 8 bits */
#  define R_DMAC_DMTMD_SZ_01                              (1 << R_DMAC_DMTMD_SZ_SHIFT)  /* 16 bits */
#  define R_DMAC_DMTMD_SZ_10                              (2 << R_DMAC_DMTMD_SZ_SHIFT)  /* 32 bits */
#  define R_DMAC_DMTMD_SZ_11                              (3 << R_DMAC_DMTMD_SZ_SHIFT)  /* Setting prohibited */

#define R_DMAC_DMTMD_DCTG_SHIFT                   (0)  /* Transfer Request Source Select */
#define R_DMAC_DMTMD_DCTG_MASK                    0x3
#  define R_DMAC_DMTMD_DCTG_00                            (0 << R_DMAC_DMTMD_DCTG_SHIFT)  /* Software */
#  define R_DMAC_DMTMD_DCTG_01                            (1 << R_DMAC_DMTMD_DCTG_SHIFT)  /* Interrupts*1 from peripheral modules or external interrupt input pins */
#  define R_DMAC_DMTMD_DCTG_10                            (2 << R_DMAC_DMTMD_DCTG_SHIFT)  /* Setting prohibited */
#  define R_DMAC_DMTMD_DCTG_11                            (3 << R_DMAC_DMTMD_DCTG_SHIFT)  /* Setting prohibited */

#define R_DMAC_DMTMD_TKP                          (1 << 10)  /* Transfer Keeping */

/* DMINT Register bit definitions */
#define R_DMAC_DMINT_DTIE                         (1 << 4)  /* Transfer End Interrupt Enable */

#define R_DMAC_DMINT_ESIE                         (1 << 3)  /* Transfer Escape End Interrupt Enable */

#define R_DMAC_DMINT_RPTIE                        (1 << 2)  /* Repeat Size End Interrupt Enable */

#define R_DMAC_DMINT_SARIE                        (1 << 1)  /* Source Address Extended Repeat Area Overflow Interrupt Enable */

#define R_DMAC_DMINT_DARIE                        (1 << 0)  /* Destination Address Extended Repeat Area Overflow Interrupt Enable */

/* DMAMD Register bit definitions */
#define R_DMAC_DMAMD_SM_SHIFT                     (14)  /* Source Address Update Mode */
#define R_DMAC_DMAMD_SM_MASK                      0xc000
#  define R_DMAC_DMAMD_SM_00                              (0 << R_DMAC_DMAMD_SM_SHIFT)  /* Fixed address */
#  define R_DMAC_DMAMD_SM_01                              (1 << R_DMAC_DMAMD_SM_SHIFT)  /* Offset addition */
#  define R_DMAC_DMAMD_SM_10                              (2 << R_DMAC_DMAMD_SM_SHIFT)  /* Incremented address */
#  define R_DMAC_DMAMD_SM_11                              (3 << R_DMAC_DMAMD_SM_SHIFT)  /* Decremented address. */

#define R_DMAC_DMAMD_SARA_SHIFT                   (8)  /* Source Address Extended Repeat Area Specifies the extended repeat area on the source address. For details on the settings. */
#define R_DMAC_DMAMD_SARA_MASK                    0x1f00

#define R_DMAC_DMAMD_DM_SHIFT                     (6)  /* Destination Address Update Mode */
#define R_DMAC_DMAMD_DM_MASK                      0xc0
#  define R_DMAC_DMAMD_DM_00                              (0 << R_DMAC_DMAMD_DM_SHIFT)  /* Fixed address */
#  define R_DMAC_DMAMD_DM_01                              (1 << R_DMAC_DMAMD_DM_SHIFT)  /* Offset addition */
#  define R_DMAC_DMAMD_DM_10                              (2 << R_DMAC_DMAMD_DM_SHIFT)  /* Incremented address */
#  define R_DMAC_DMAMD_DM_11                              (3 << R_DMAC_DMAMD_DM_SHIFT)  /* Decremented address. */

#define R_DMAC_DMAMD_DARA_SHIFT                   (0)  /* Destination Address Extended Repeat Area Specifies the extended repeat area on the destination address. For details on the settings. */
#define R_DMAC_DMAMD_DARA_MASK                    0x1f

#define R_DMAC_DMAMD_DADR                         (1 << 5)  /* Destination Address Update Select After Reload */

#define R_DMAC_DMAMD_SADR                         (1 << 13)  /* Source Address Update Select After Reload */

/* DMOFR Register bit definitions */
#define R_DMAC_DMOFR_DMOFR_SHIFT                  (0)  /* Specifies the offset when offset addition is selected as the address update mode for transfer source or destination. */
#define R_DMAC_DMOFR_DMOFR_MASK                   0xffffffff

/* DMCNT Register bit definitions */
#define R_DMAC_DMCNT_DTE                          (1 << 0)  /* DMA Transfer Enable */

/* DMREQ Register bit definitions */
#define R_DMAC_DMREQ_CLRS                         (1 << 4)  /* DMA Software Start Bit Auto Clear Select */

#define R_DMAC_DMREQ_SWREQ                        (1 << 0)  /* DMA Software Start */

/* DMSTS Register bit definitions */
#define R_DMAC_DMSTS_ACT                          (1 << 7)  /* DMA Active Flag */

#define R_DMAC_DMSTS_DTIF                         (1 << 4)  /* Transfer End Interrupt Flag */

#define R_DMAC_DMSTS_ESIF                         (1 << 0)  /* Transfer Escape End Interrupt Flag */

/* DMSBS Register bit definitions */
#define R_DMAC_DMSBS_DMSBSL_SHIFT                 (0)  /* Functions as data transfer counter in repeat-block transfer mode */
#define R_DMAC_DMSBS_DMSBSL_MASK                  0xffff

#define R_DMAC_DMSBS_DMSBSH_SHIFT                 (16)  /* Specifies the repeat-area size in repeat-block transfer mode */
#define R_DMAC_DMSBS_DMSBSH_MASK                  0xffff0000

/* DMDBS Register bit definitions */
#define R_DMAC_DMDBS_DMDBSL_SHIFT                 (0)  /* Functions as data transfer counter in repeat-block transfer mode */
#define R_DMAC_DMDBS_DMDBSL_MASK                  0xffff

#define R_DMAC_DMDBS_DMDBSH_SHIFT                 (16)  /* Specifies the repeat-area size in repeat-block transfer mode */
#define R_DMAC_DMDBS_DMDBSH_MASK                  0xffff0000

/* DMBWR Register bit definitions */
#define R_DMAC_DMBWR_BWE                          (1 << 0)  /* Bufferable Write Enable */


/* Maximum number of channels */

#define DMAC_MAX_CHANNELS        16  /* Total: 8 channels per unit × 2 units */
#define DMAC_CHANNELS_PER_UNIT   8   /* Channels per DMAC unit */
#define DMAC_NUM_UNITS           2   /* Number of DMAC units */

/* Channel ID definitions for both DMAC units:
 * Unit 0: Channels 0-7
 * Unit 1: Channels 10-17 (decimal notation)
 */
#define DMAC_UNIT0_CH0           0
#define DMAC_UNIT0_CH1           1
#define DMAC_UNIT0_CH2           2
#define DMAC_UNIT0_CH3           3
#define DMAC_UNIT0_CH4           4
#define DMAC_UNIT0_CH5           5
#define DMAC_UNIT0_CH6           6
#define DMAC_UNIT0_CH7           7
#define DMAC_UNIT1_CH0           10
#define DMAC_UNIT1_CH1           11
#define DMAC_UNIT1_CH2           12
#define DMAC_UNIT1_CH3           13
#define DMAC_UNIT1_CH4           14
#define DMAC_UNIT1_CH5           15
#define DMAC_UNIT1_CH6           16
#define DMAC_UNIT1_CH7           17

/* Helper macros to extract unit and local channel from channel ID */
#define DMAC_GET_UNIT(ch)        (((ch) < 10) ? 0 : 1)
#define DMAC_GET_LOCAL_CH(ch)    (((ch) < 10) ? (ch) : ((ch) - 10))

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DMAC_H */

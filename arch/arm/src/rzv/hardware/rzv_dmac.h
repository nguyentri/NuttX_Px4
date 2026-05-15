/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_dmac.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_DMAC_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_DMAC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DMAC_B Unit Base Addresses
 * Source: FSP dmac_b_iodefine.h R_DMAC_B{0-4}_BASE
 * R_DMAC_B0_BASE = 0x11400000  (Cortex-R8 secure DMAC, 2 groups × 8 ch)
 * R_DMAC_B1_BASE = 0x14830000  (CM33/CA55 shared, 2 groups × 8 ch)
 * R_DMAC_B2_BASE = 0x14840000
 * R_DMAC_B3_BASE = 0x12000000
 * R_DMAC_B4_BASE = 0x12010000
 */

#define RZV_DMAC0_BASE              0x11400000UL
#define RZV_DMAC1_BASE              0x14830000UL
#define RZV_DMAC2_BASE              0x14840000UL
#define RZV_DMAC3_BASE              0x12000000UL
#define RZV_DMAC4_BASE              0x12010000UL

/* DMAC_B topology:
 *   Each unit = 2 groups (GRP[0], GRP[1])
 *   Each group = 8 channels (CH[0]..CH[7])
 *   Total per unit = 16 channels
 *   Total across 5 units = 80 channels
 *
 * Global channel numbering: ch = unit*16 + group*8 + local_ch
 *   unit      = ch / 16
 *   group     = (ch % 16) / 8   = (ch / 8) % 2
 *   local_ch  = ch % 8
 */

#define RZV_DMAC_NUM_UNITS          5   /* Number of DMAC units */
#define RZV_DMAC_CHANNELS_PER_UNIT  16  /* 2 groups × 8 channels */
#define RZV_DMAC_MAX_CHANNELS       80  /* 5 units × 16 channels */

/* DMAC_B Channel Register Offsets within R_DMAC_B0_GRP_CH_Type (64 bytes)
 *
 * Layout derived from FSP dmac_b_iodefine.h R_DMAC_B0_GRP_CH_Type:
 *   N[0].SA  @ 0x00  — Next0 source address (initial)
 *   N[0].DA  @ 0x04  — Next0 destination address (initial)
 *   N[0].TB  @ 0x08  — Next0 transfer byte count (initial)
 *   N[1].SA  @ 0x0C  — Next1 source address (reload)
 *   N[1].DA  @ 0x10  — Next1 destination address (reload)
 *   N[1].TB  @ 0x14  — Next1 transfer byte count (reload)
 *   CRSA     @ 0x18  — Current source address (RO)
 *   CRDA     @ 0x1C  — Current destination address (RO)
 *   CRTB     @ 0x20  — Current transfer byte count (RO)
 *   CHSTAT   @ 0x24  — Channel status (RO)
 *   CHCTRL   @ 0x28  — Channel control
 *   CHCFG    @ 0x2C  — Channel configuration
 *   CHITVL   @ 0x30  — Channel interval
 *   CHEXT    @ 0x34  — Channel extension (port/cache attrs)
 *   NXLA     @ 0x38  — Next link address
 *   CRLA     @ 0x3C  — Current link address (RO)
 */

#define RZV_DMAC_N0SA_OFFSET         0x0000  /* Next0 source address */
#define RZV_DMAC_N0DA_OFFSET         0x0004  /* Next0 destination address */
#define RZV_DMAC_N0TB_OFFSET         0x0008  /* Next0 transfer byte count */
#define RZV_DMAC_N1SA_OFFSET         0x000C  /* Next1 source address (reload) */
#define RZV_DMAC_N1DA_OFFSET         0x0010  /* Next1 destination address (reload) */
#define RZV_DMAC_N1TB_OFFSET         0x0014  /* Next1 transfer byte count (reload) */
#define RZV_DMAC_CRSA_OFFSET         0x0018  /* Current source address */
#define RZV_DMAC_CRDA_OFFSET         0x001C  /* Current destination address */
#define RZV_DMAC_CRTB_OFFSET         0x0020  /* Current transfer byte count */
#define RZV_DMAC_CHSTAT_OFFSET       0x0024  /* Channel status register */
#define RZV_DMAC_CHCTRL_OFFSET       0x0028  /* Channel control register */
#define RZV_DMAC_CHCFG_OFFSET        0x002C  /* Channel configuration register */
#define RZV_DMAC_CHITVL_OFFSET       0x0030  /* Channel interval register */
#define RZV_DMAC_CHEXT_OFFSET        0x0034  /* Channel extension register */
#define RZV_DMAC_NXLA_OFFSET         0x0038  /* Next link address */
#define RZV_DMAC_CRLA_OFFSET         0x003C  /* Current link address */

/* DMAC_B Group Register Offsets within R_DMAC_B0_GRP_Type
 *
 * R_DMAC_B0_GRP_Type layout (from FSP iodefine):
 *   CH[8]        @ 0x000  — 8 channels × 0x40 = 0x200 bytes
 *   RESERVED[64] @ 0x200  — 64 × 4 = 0x100 bytes
 *   DCTRL        @ 0x300  — DMA group control
 *   RESERVED1[3] @ 0x304  — 3 × 4 = 0x0C bytes
 *   DSTAT_EN     @ 0x310  — Enable status
 *   DSTAT_ER     @ 0x314  — Error status
 *   DSTAT_END    @ 0x318  — End status
 *   DST_TC       @ 0x31C  — Transfer count match status
 *   DSTAT_SUS    @ 0x320  — Suspend status
 *   RESERVED3[55]@ 0x324  — pad to 0x400
 *
 * sizeof(R_DMAC_B0_GRP_Type) = 0x400 (1 KB per group)
 */

#define RZV_DMAC_CHANNEL_STRIDE      0x0040  /* 64 bytes per channel */
#define RZV_DMAC_GROUP_STRIDE        0x0400  /* 1 KB per group */

#define RZV_DMAC_DCTRL_OFFSET        0x0300  /* Group control register */
#define RZV_DMAC_DSTAT_EN_OFFSET     0x0310  /* Enable status */
#define RZV_DMAC_DSTAT_ER_OFFSET     0x0314  /* Error status */
#define RZV_DMAC_DSTAT_END_OFFSET    0x0318  /* End status */
#define RZV_DMAC_DST_TC_OFFSET       0x031C  /* Transfer count status */
#define RZV_DMAC_DSTAT_SUS_OFFSET    0x0320  /* Suspend status */

/* DMAC_B Address Calculation Macros
 *
 * group = (ch / 8) % 2  — which group within the unit (0 or 1)
 * local = ch % 8        — which channel within the group
 *
 * Per-channel register: UNIT_BASE + (ch/8)*GROUP_STRIDE + (ch%8)*CH_STRIDE + offset
 * Group register:       UNIT_BASE + (ch/8)*GROUP_STRIDE + DCTRL_OFFSET
 *
 * For the group-level registers we take 'ch' as the group index (0 or 1).
 * Call RZV_DMAC_DCTRL(unit, group) with group = global_ch / 8.
 */

/* Unit derivation from global channel */
#define RZV_DMAC_UNIT(ch)           ((ch) / RZV_DMAC_CHANNELS_PER_UNIT)
/* Local channel within unit (0..15) */
#define RZV_DMAC_LOCAL_CH(ch)       ((ch) % RZV_DMAC_CHANNELS_PER_UNIT)
/* Group within unit (0 or 1) */
#define RZV_DMAC_GRP(ch)            (RZV_DMAC_LOCAL_CH(ch) / 8)
/* Channel within group (0..7) */
#define RZV_DMAC_GRP_CH(ch)         (RZV_DMAC_LOCAL_CH(ch) % 8)

/* Base address inline lookup */
static inline uintptr_t rzv_dmac_get_base(int unit)
{
  static const uintptr_t dmac_bases[RZV_DMAC_NUM_UNITS] =
  {
    RZV_DMAC0_BASE,
    RZV_DMAC1_BASE,
    RZV_DMAC2_BASE,
    RZV_DMAC3_BASE,
    RZV_DMAC4_BASE
  };

  return (unit >= 0 && unit < RZV_DMAC_NUM_UNITS) ? dmac_bases[unit] : 0;
}

#define RZV_DMAC_BASE(unit)         rzv_dmac_get_base(unit)

/* Per-channel register addresses
 * ch = global channel (0..79), unit derived internally
 */
#define RZV_DMAC_CH_BASE(unit, ch) \
  (RZV_DMAC_BASE(unit) + \
   (uintptr_t)RZV_DMAC_GRP(ch) * RZV_DMAC_GROUP_STRIDE + \
   (uintptr_t)RZV_DMAC_GRP_CH(ch) * RZV_DMAC_CHANNEL_STRIDE)

#define RZV_DMAC_N0SA(unit, ch)  (RZV_DMAC_CH_BASE(unit, ch) + RZV_DMAC_N0SA_OFFSET)
#define RZV_DMAC_N0DA(unit, ch)  (RZV_DMAC_CH_BASE(unit, ch) + RZV_DMAC_N0DA_OFFSET)
#define RZV_DMAC_N0TB(unit, ch)  (RZV_DMAC_CH_BASE(unit, ch) + RZV_DMAC_N0TB_OFFSET)
#define RZV_DMAC_N1SA(unit, ch)  (RZV_DMAC_CH_BASE(unit, ch) + RZV_DMAC_N1SA_OFFSET)
#define RZV_DMAC_N1DA(unit, ch)  (RZV_DMAC_CH_BASE(unit, ch) + RZV_DMAC_N1DA_OFFSET)
#define RZV_DMAC_N1TB(unit, ch)  (RZV_DMAC_CH_BASE(unit, ch) + RZV_DMAC_N1TB_OFFSET)
#define RZV_DMAC_CRSA(unit, ch)  (RZV_DMAC_CH_BASE(unit, ch) + RZV_DMAC_CRSA_OFFSET)
#define RZV_DMAC_CRDA(unit, ch)  (RZV_DMAC_CH_BASE(unit, ch) + RZV_DMAC_CRDA_OFFSET)
#define RZV_DMAC_CRTB(unit, ch)  (RZV_DMAC_CH_BASE(unit, ch) + RZV_DMAC_CRTB_OFFSET)
#define RZV_DMAC_CHSTAT(unit, ch)(RZV_DMAC_CH_BASE(unit, ch) + RZV_DMAC_CHSTAT_OFFSET)
#define RZV_DMAC_CHCTRL(unit, ch)(RZV_DMAC_CH_BASE(unit, ch) + RZV_DMAC_CHCTRL_OFFSET)
#define RZV_DMAC_CHCFG(unit, ch) (RZV_DMAC_CH_BASE(unit, ch) + RZV_DMAC_CHCFG_OFFSET)
#define RZV_DMAC_CHITVL(unit, ch)(RZV_DMAC_CH_BASE(unit, ch) + RZV_DMAC_CHITVL_OFFSET)
#define RZV_DMAC_CHEXT(unit, ch) (RZV_DMAC_CH_BASE(unit, ch) + RZV_DMAC_CHEXT_OFFSET)
#define RZV_DMAC_NXLA(unit, ch)  (RZV_DMAC_CH_BASE(unit, ch) + RZV_DMAC_NXLA_OFFSET)
#define RZV_DMAC_CRLA(unit, ch)  (RZV_DMAC_CH_BASE(unit, ch) + RZV_DMAC_CRLA_OFFSET)

/* Group-level registers.
 * grp = group index within unit (0 or 1).
 * For unit-init: use RZV_DMAC_DCTRL(unit, 0) and RZV_DMAC_DCTRL(unit, 1).
 */
#define RZV_DMAC_GRP_BASE(unit, grp) \
  (RZV_DMAC_BASE(unit) + (uintptr_t)(grp) * RZV_DMAC_GROUP_STRIDE)

#define RZV_DMAC_DCTRL(unit, grp) \
  (RZV_DMAC_GRP_BASE(unit, grp) + RZV_DMAC_DCTRL_OFFSET)
#define RZV_DMAC_DSTAT_EN(unit, grp) \
  (RZV_DMAC_GRP_BASE(unit, grp) + RZV_DMAC_DSTAT_EN_OFFSET)
#define RZV_DMAC_DSTAT_ER(unit, grp) \
  (RZV_DMAC_GRP_BASE(unit, grp) + RZV_DMAC_DSTAT_ER_OFFSET)
#define RZV_DMAC_DSTAT_END(unit, grp) \
  (RZV_DMAC_GRP_BASE(unit, grp) + RZV_DMAC_DSTAT_END_OFFSET)
#define RZV_DMAC_DST_TC(unit, grp) \
  (RZV_DMAC_GRP_BASE(unit, grp) + RZV_DMAC_DST_TC_OFFSET)
#define RZV_DMAC_DSTAT_SUS(unit, grp) \
  (RZV_DMAC_GRP_BASE(unit, grp) + RZV_DMAC_DSTAT_SUS_OFFSET)

/****************************************************************************
 * CHCFG Register Bit Definitions
 * Source: FSP dmac_b_iodefine.h CHCFG_b
 ****************************************************************************/

#define DMAC_CHCFG_SEL_SHIFT        (0)       /* Bits 2:0 - peripheral sel */
#define DMAC_CHCFG_SEL_MASK         (0x7u << DMAC_CHCFG_SEL_SHIFT)
#define DMAC_CHCFG_REQD             (1u << 3) /* Request direction */
#define DMAC_CHCFG_LOEN             (1u << 4) /* Low-enable output */
#define DMAC_CHCFG_HIEN             (1u << 5) /* High-enable output */
#define DMAC_CHCFG_LVL              (1u << 6) /* Level output */
#define DMAC_CHCFG_AM_SHIFT         (8)       /* Bits 10:8 - ack mode */
#define DMAC_CHCFG_AM_MASK          (0x7u << DMAC_CHCFG_AM_SHIFT)
#define DMAC_CHCFG_SDS_SHIFT        (12)      /* Bits 15:12 - src data size */
#define DMAC_CHCFG_SDS_MASK         (0xfu << DMAC_CHCFG_SDS_SHIFT)
#define DMAC_CHCFG_DDS_SHIFT        (16)      /* Bits 19:16 - dst data size */
#define DMAC_CHCFG_DDS_MASK         (0xfu << DMAC_CHCFG_DDS_SHIFT)
#define DMAC_CHCFG_SAD              (1u << 20) /* Source address dir: 0=incr, 1=fixed */
#define DMAC_CHCFG_DAD              (1u << 21) /* Dest address dir: 0=incr, 1=fixed */
#define DMAC_CHCFG_TM               (1u << 22) /* Transfer mode: 0=single, 1=block */
#define DMAC_CHCFG_DEM              (1u << 24) /* DMA-end interrupt mask */
#define DMAC_CHCFG_TCM              (1u << 25) /* Transfer-count match mask */
#define DMAC_CHCFG_SBE              (1u << 27) /* Secure bit enable */
#define DMAC_CHCFG_RSEL             (1u << 28) /* Register set select */
#define DMAC_CHCFG_RSW              (1u << 29) /* Register set swap */
#define DMAC_CHCFG_REN              (1u << 30) /* Register mode enable */
#define DMAC_CHCFG_DMS              (1u << 31) /* DMA mode: 0=register, (no link mode) */

/****************************************************************************
 * CHCTRL Register Bit Definitions
 ****************************************************************************/

#define DMAC_CHCTRL_SETEN           (1u << 0)  /* Set enable */
#define DMAC_CHCTRL_CLREN           (1u << 1)  /* Clear enable */
#define DMAC_CHCTRL_STG             (1u << 2)  /* Software trigger */
#define DMAC_CHCTRL_SWRST           (1u << 3)  /* Software reset */
#define DMAC_CHCTRL_CLRRQ           (1u << 4)  /* Clear request */
#define DMAC_CHCTRL_CLREND          (1u << 5)  /* Clear END flag */
#define DMAC_CHCTRL_CLRTC           (1u << 6)  /* Clear TC flag */
#define DMAC_CHCTRL_SETSUS          (1u << 8)  /* Set suspend */
#define DMAC_CHCTRL_CLRSUS          (1u << 9)  /* Clear suspend */
#define DMAC_CHCTRL_SETINTMSK       (1u << 16) /* Set interrupt mask */
#define DMAC_CHCTRL_CLRINTMSK       (1u << 17) /* Clear interrupt mask */

/****************************************************************************
 * CHSTAT Register Bit Definitions
 ****************************************************************************/

#define DMAC_CHSTAT_EN              (1u << 0)  /* Channel enabled */
#define DMAC_CHSTAT_RQST            (1u << 1)  /* Request pending */
#define DMAC_CHSTAT_TACT            (1u << 2)  /* Transfer active */
#define DMAC_CHSTAT_SUS             (1u << 3)  /* Suspended */
#define DMAC_CHSTAT_ER              (1u << 4)  /* Error */
#define DMAC_CHSTAT_END             (1u << 5)  /* Transfer end */
#define DMAC_CHSTAT_TC              (1u << 6)  /* Transfer count match */
#define DMAC_CHSTAT_SR              (1u << 7)  /* Software request */
#define DMAC_CHSTAT_DL              (1u << 8)  /* Descriptor load */
#define DMAC_CHSTAT_DW              (1u << 9)  /* Descriptor write */
#define DMAC_CHSTAT_DER             (1u << 10) /* Descriptor error */
#define DMAC_CHSTAT_MODE            (1u << 11) /* Operating mode */
#define DMAC_CHSTAT_INTMSK          (1u << 16) /* Interrupt masked */

/****************************************************************************
 * CHEXT Register Bit Definitions
 ****************************************************************************/

#define DMAC_CHEXT_SPR_SHIFT        (0)        /* Bits 2:0 - source port */
#define DMAC_CHEXT_SPR_MASK         (0x7u << DMAC_CHEXT_SPR_SHIFT)
#define DMAC_CHEXT_SCA_SHIFT        (4)        /* Bits 7:4 - src cache attrs */
#define DMAC_CHEXT_SCA_MASK         (0xfu << DMAC_CHEXT_SCA_SHIFT)
#define DMAC_CHEXT_DPR_SHIFT        (8)        /* Bits 10:8 - dest port */
#define DMAC_CHEXT_DPR_MASK         (0x7u << DMAC_CHEXT_DPR_SHIFT)
#define DMAC_CHEXT_DCA_SHIFT        (12)       /* Bits 15:12 - dst cache attrs */
#define DMAC_CHEXT_DCA_MASK         (0xfu << DMAC_CHEXT_DCA_SHIFT)

/****************************************************************************
 * CHITVL Register Bit Definitions
 ****************************************************************************/

#define DMAC_CHITVL_ITVL_SHIFT      (0)
#define DMAC_CHITVL_ITVL_MASK       (0xffffu << DMAC_CHITVL_ITVL_SHIFT)

/****************************************************************************
 * DCTRL Register Bit Definitions
 ****************************************************************************/

#define DMAC_DCTRL_PR               (1u << 0)  /* Priority mode: 0=fixed, 1=round-robin */
#define DMAC_DCTRL_LVINT            (1u << 1)  /* Level interrupt output */
#define DMAC_DCTRL_LDPR_SHIFT       (16)
#define DMAC_DCTRL_LDPR_MASK        (0x7u << DMAC_DCTRL_LDPR_SHIFT)
#define DMAC_DCTRL_LDCA_SHIFT       (20)
#define DMAC_DCTRL_LDCA_MASK        (0xfu << DMAC_DCTRL_LDCA_SHIFT)
#define DMAC_DCTRL_LWPR_SHIFT       (24)
#define DMAC_DCTRL_LWPR_MASK        (0x7u << DMAC_DCTRL_LWPR_SHIFT)
#define DMAC_DCTRL_LWCA_SHIFT       (28)
#define DMAC_DCTRL_LWCA_MASK        (0xfu << DMAC_DCTRL_LWCA_SHIFT)

/****************************************************************************
 * INTC DMACKSEL Register Support
 *
 * RZV2H INTC (base 0x10400000) has DMACKSEL0..DMACKSELn registers.
 * Each DMACKSEL register packs 4 channels, 8 bits per channel (7 bits val
 * + 1 reserved). Each 7-bit field selects which peripheral event drives
 * the DMAC channel's hardware request (DREQ).
 *
 * DMACKSEL_n covers channels: n*4 to n*4+3
 * Channel k maps to DMACKSEL register n=k/4, bit shift = (k%4)*8
 *
 * The offset of DMACKSEL0 (0x0BCC) is derived from the R_INTC_Type struct
 * in intc_iodefine.h (R9A09G057H CR variant): DMACKSEL0 follows DMRCLR2 +
 * RESERVED13[36 bytes].  This offset is consistent with the field layout
 * enumeration in refs/.../R9A09G057H/cr/iodefines/intc_iodefine.h:2986.
 * rzv_dmac_set_peripheral_source() uses this offset to route ELC events.
 *
 * Reference: refs/.../R9A09G057H/cr/iodefines/intc_iodefine.h DMACKSEL0_b
 *   Each DACK_SEL field is 7 bits. Value = (unit-1)*16 + local_ch
 *   for units 1-4; unit 0: value = (0+4)*16 + local_ch (FSP bsp_dmac.h).
 ****************************************************************************/

#define RZV_INTC_BASE               0x10400000UL  /* Same as RZV_ICU_BASE */

/* DMACKSEL offset within INTC - UNVERIFIED (see note above) */
#define RZV_INTC_DMACKSEL0_OFFSET   0x0BCC  /* Derived from intc_iodefine.h R9A09G057H struct */

#define RZV_INTC_DMACKSEL(n) \
  (RZV_INTC_BASE + RZV_INTC_DMACKSEL0_OFFSET + (uintptr_t)(n) * 4)

/* DMACKSEL field shift for channel k within its register */
#define RZV_INTC_DMACKSEL_SHIFT(ch) (((ch) % 4) * 8)
#define RZV_INTC_DMACKSEL_MASK      0x7fu     /* 7-bit field */

/* Compute the DACK_SEL value for a given DMAC global channel:
 * FSP bsp_dmac.h R_BSP_DMAC_DACK_OUTPUT_PIN_SET logic:
 *   unit==0: write_value = (0+4)*16 + local_ch  = 64 + local_ch
 *   unit>0 : write_value = (unit-1)*16 + local_ch
 */
#define RZV_INTC_DMACKSEL_VAL(unit, local_ch) \
  ((uint32_t)(((unit) == 0) ? \
   (4 * 16 + (local_ch)) : \
   ((unit) - 1) * 16 + (local_ch)))

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_DMAC_H */

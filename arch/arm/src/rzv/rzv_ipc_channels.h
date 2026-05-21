/****************************************************************************
 * arch/arm/src/rzv/rzv_ipc_channels.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * AUTHORITATIVE SOURCE for all RZ/V2H inter-core IPC channel definitions.
 *
 * This is the SINGLE source of truth for MHU instance, TX/RX channel
 * numbers, interrupt IDs, SHM base addresses, and ring sizes.
 * No other file shall define these constants.
 *
 * Channel allocation (audited against rzv_rproc.c — Phase 01):
 *   Channel 3 (NS window, MHU0): consumed by CA55↔CR8 rptun/OpenAMP.
 *   Channels 0–2, 4–9: free in MHU0 NS window.
 *   We allocate ch4/ch5 for CR8↔CR8 and ch6/ch7 for CR8↔CM33 within
 *   the same MHU0 NS window to keep all raw IPC in one base address.
 *   This avoids needing a second MHU instance mapping in the MPU.
 *
 *   TODO(IPC-NEXT): if CR8↔CR8 or CR8↔CM33 need Secure-window access
 *                   switch to RZV_MHU0_S_CR8_BASE by adding
 *                   CONFIG_RZV_MHU_DOMAIN_S_CR8 to the defconfig.
 *
 ****************************************************************************/

/* =========================================================================
 * CM33 FIRMWARE ABI (FROZEN — see Phase 04)
 *
 * Ring header layout (little-endian, located at SHM_BASE):
 *
 *   offset  0: uint32_t head      — consumer read pointer (modulo entries)
 *   offset  4: uint32_t tail      — producer write pointer (modulo entries)
 *   offset  8: uint32_t mask      — entries - 1 (power of two)
 *   offset 12: uint32_t flags     — ABI version in bits[7:0]; reserved[31:8]
 *   offset 16–63: uint8_t pad[48] — cacheline pad (total header = 64 bytes)
 *
 * Ring data starts at SHM_BASE + 64 bytes.
 * Each entry is RING_ENTRY_SIZE bytes (default 64).
 * Total ring size = 64 (header) + RING_ENTRIES * RING_ENTRY_SIZE.
 *
 * Kick semantics:
 *   TX: producer writes entry, updates tail (with dmb ish), calls
 *       up_clean_dcache on entry, then writes 0x1 to
 *       MHU_MSG_SET_OFF of the TX channel.
 *   RX: receiver gets MHU IRQ, calls up_invalidate_dcache on ring
 *       header + entry range, reads entry[head], increments head,
 *       writes 0x1 to MHU_RSP_SET_OFF (ACK) of the TX channel.
 *
 * ABI version: flags bits[7:0] = 0x01 (this revision).
 * Byte order: little-endian (matches all RZ/V2H cores).
 * =========================================================================
 */

#ifndef __ARCH_ARM_SRC_RZV_RZV_IPC_CHANNELS_H
#define __ARCH_ARM_SRC_RZV_RZV_IPC_CHANNELS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>

#include "hardware/rzv_mhu.h"
#include <arch/rzv/rzv2h_irq.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* -------------------------------------------------------------------------
 * Link 0: CA55 ↔ CR8_0  (rptun/OpenAMP — read-only reference; DO NOT edit)
 * Owner: rzv_rproc.c / rzv_openamp.c
 * MHU0 NS, channel 3, IRQ 314 (RZV_IRQ_MHU_MSG3_NS)
 * Device: /dev/ipcc0
 * -------------------------------------------------------------------------
 */
#define RZV_IPC_CA55_MHU_BASE        RZV_MHU0_NS_BASE
#define RZV_IPC_CA55_TX_CHAN         3u    /* CR8 RSP → CA55 */
#define RZV_IPC_CA55_RX_CHAN         3u    /* CA55 MSG → CR8 */
#define RZV_IPC_CA55_RX_IRQ          314   /* RZV_IRQ_MHU_MSG3_NS */

/* -------------------------------------------------------------------------
 * Link 1: CR8_0 ↔ CR8_1  (raw MHU + SHM ring)
 * MHU0 NS, TX channel 4 (CR8_0→CR8_1), RX channel 9 (CR8_1→CR8_0)
 * Device: /dev/ipcc1
 *
 * Channel selection rationale:
 *   BSP_FEATURE_MHU_B_NS_VALID_CHANNEL_MASK = 0x030410618618 lists valid
 *   MHU-B-NS channels as: 3,4,9,10,15,16,21,22,28,34,40,41.
 *   Channels 5–8 are NOT valid; original assignment (ch5 RX) was wrong.
 *   TX_IRQ is the RSP (response/ACK) interrupt on the TX channel (ch4).
 *   RX_IRQ is the MSG interrupt on the RX channel (ch9).
 *   Both IRQ values verified against the RZ/V2H hardware manual.
 * -------------------------------------------------------------------------
 */
#define RZV_IPC_CR8CR8_MHU_BASE      RZV_MHU0_NS_BASE
#define RZV_IPC_CR8CR8_TX_CHAN       4u    /* CR8_0 → CR8_1 (initiator TX) */
#define RZV_IPC_CR8CR8_RX_CHAN       9u    /* CR8_1 → CR8_0 (initiator RX) */
#define RZV_IPC_CR8CR8_TX_IRQ        RZV_IRQ_MHU_RSP4_NS   /* RSP ACK on ch4 = 327 */
#define RZV_IPC_CR8CR8_RX_IRQ        RZV_IRQ_MHU_MSG9_NS   /* MSG kick on ch9 = 316 */

/* SHM for CR8↔CR8: DDR carveout at 0x43800000, 64 KiB total
 * (TX ring = low 32 KiB from initiator's perspective;
 *  RX ring = high 32 KiB)
 */
#define RZV_IPC_CR8CR8_SHM_BASE      0x43800000u
#define RZV_IPC_CR8CR8_SHM_SIZE      0x00010000u  /* 64 KiB */
#define RZV_IPC_CR8CR8_RING_ENTRIES  16u
#define RZV_IPC_CR8CR8_RING_ENTRY_SZ 64u

/* -------------------------------------------------------------------------
 * Link 2: CR8_0 ↔ CM33  (raw MHU + SHM ring; CR8 side only)
 * MHU0 NS, TX channel 10 (CR8_0→CM33), RX channel 15 (CM33→CR8_0)
 * Device: /dev/ipcc2
 *
 * Channel selection: ch10 and ch15 are valid MHU-B-NS channels per
 * BSP_FEATURE_MHU_B_NS_VALID_CHANNEL_MASK.  Original ch6/ch7 were invalid.
 * TX_IRQ = RSP ACK on ch10; RX_IRQ = MSG kick on ch15.
 * IRQ values: MHU_RSP10_NS_IRQn / MHU_MSG15_NS_IRQn per RZ/V2H hardware manual.
 * -------------------------------------------------------------------------
 */
#define RZV_IPC_CR8CM33_MHU_BASE     RZV_MHU0_NS_BASE
#define RZV_IPC_CR8CM33_TX_CHAN      10u   /* CR8_0 → CM33 */
#define RZV_IPC_CR8CM33_RX_CHAN      15u   /* CM33 → CR8_0 */
#define RZV_IPC_CR8CM33_TX_IRQ       RZV_IRQ_MHU_RSP10_NS  /* RSP ACK on ch10 = 329 */
#define RZV_IPC_CR8CM33_RX_IRQ       RZV_IRQ_MHU_MSG15_NS  /* MSG kick on ch15 = 318 */

/* SHM for CR8↔CM33: DDR carveout at 0x43810000, 32 KiB
 * (separate from CR8↔CR8 region; no overlap)
 */
#define RZV_IPC_CR8CM33_SHM_BASE     0x43810000u
#define RZV_IPC_CR8CM33_SHM_SIZE     0x00008000u  /* 32 KiB */
#define RZV_IPC_CR8CM33_RING_ENTRIES 8u
#define RZV_IPC_CR8CM33_RING_ENTRY_SZ 64u

/* -------------------------------------------------------------------------
 * Loopback (CR8_0 self-test, no CR8_1 required)
 * MHU0 NS, TX channel 16 → RX channel 16 (same channel, self-kick)
 * Device: /dev/ipccLB
 *
 * Channel 16 is a valid MHU-B-NS channel per VALID_CHANNEL_MASK.
 * Original channel 8 was NOT valid.
 * RX_IRQ = MSG kick on ch16; TX_IRQ = RSP ACK on ch16.
 * In loopback mode tx_irq == rx_irq; rzv_ipc_raw_register handles this
 * by using the combined loopback ISR that posts both rxsem and txsem.
 * -------------------------------------------------------------------------
 */
#define RZV_IPC_LOOPBACK_MHU_BASE    RZV_MHU0_NS_BASE
#define RZV_IPC_LOOPBACK_TX_CHAN     16u
#define RZV_IPC_LOOPBACK_RX_CHAN     16u
#define RZV_IPC_LOOPBACK_TX_IRQ      RZV_IRQ_MHU_RSP16_NS  /* RSP ACK on ch16 = 331 */
#define RZV_IPC_LOOPBACK_RX_IRQ      RZV_IRQ_MHU_MSG16_NS  /* MSG kick on ch16 = 319 */
#define RZV_IPC_LOOPBACK_SHM_BASE    0x43818000u
#define RZV_IPC_LOOPBACK_SHM_SIZE    0x00004000u  /* 16 KiB */
#define RZV_IPC_LOOPBACK_RING_ENTRIES 8u
#define RZV_IPC_LOOPBACK_RING_ENTRY_SZ 64u

/* -------------------------------------------------------------------------
 * Compile-time sanity checks (pulled in by any TU that includes this header)
 * -------------------------------------------------------------------------
 */
/* HIGH-2 fix: compile-time channel validity check.
 * BSP_FEATURE_MHU_B_NS_VALID_CHANNEL_MASK = 0x030410618618 (48-bit).
 * Macro expands to 1 if channel N is a valid MHU-B-NS channel, 0 otherwise.
 * Valid set: 3,4,9,10,15,16,21,22,28,34,40,41.
 */
#define RZV_MHU_B_NS_CH_VALID(n) \
  (((0x030410618618ULL >> (n)) & 1ULL) != 0ULL)

#ifdef __STDC_VERSION__
/* RING_ENTRIES must be power of two (mask = entries - 1) */
_Static_assert((RZV_IPC_CR8CR8_RING_ENTRIES  & (RZV_IPC_CR8CR8_RING_ENTRIES  - 1)) == 0,
               "CR8CR8 ring entries must be power of two");
_Static_assert((RZV_IPC_CR8CM33_RING_ENTRIES & (RZV_IPC_CR8CM33_RING_ENTRIES - 1)) == 0,
               "CR8CM33 ring entries must be power of two");

/* TX and RX channels must differ for non-loopback links */
_Static_assert(RZV_IPC_CR8CR8_TX_CHAN != RZV_IPC_CR8CR8_RX_CHAN,
               "CR8CR8 TX and RX channels must differ");
_Static_assert(RZV_IPC_CR8CM33_TX_CHAN != RZV_IPC_CR8CM33_RX_CHAN,
               "CR8CM33 TX and RX channels must differ");

/* Channel 3 must not be reused by raw IPC (owned by rptun) */
_Static_assert(RZV_IPC_CR8CR8_TX_CHAN  != RZV_IPC_CA55_TX_CHAN, "ch3 reserved for rptun");
_Static_assert(RZV_IPC_CR8CR8_RX_CHAN  != RZV_IPC_CA55_RX_CHAN, "ch3 reserved for rptun");
_Static_assert(RZV_IPC_CR8CM33_TX_CHAN != RZV_IPC_CA55_TX_CHAN, "ch3 reserved for rptun");
_Static_assert(RZV_IPC_CR8CM33_RX_CHAN != RZV_IPC_CA55_RX_CHAN, "ch3 reserved for rptun");
_Static_assert(RZV_IPC_LOOPBACK_TX_CHAN != RZV_IPC_CA55_TX_CHAN, "ch3 reserved for rptun");

/* HIGH-2: all channels must be valid MHU-B-NS channels */
_Static_assert(RZV_MHU_B_NS_CH_VALID(RZV_IPC_CR8CR8_TX_CHAN),
               "CR8CR8 TX channel not valid in MHU-B-NS");
_Static_assert(RZV_MHU_B_NS_CH_VALID(RZV_IPC_CR8CR8_RX_CHAN),
               "CR8CR8 RX channel not valid in MHU-B-NS");
_Static_assert(RZV_MHU_B_NS_CH_VALID(RZV_IPC_CR8CM33_TX_CHAN),
               "CR8CM33 TX channel not valid in MHU-B-NS");
_Static_assert(RZV_MHU_B_NS_CH_VALID(RZV_IPC_CR8CM33_RX_CHAN),
               "CR8CM33 RX channel not valid in MHU-B-NS");
_Static_assert(RZV_MHU_B_NS_CH_VALID(RZV_IPC_LOOPBACK_TX_CHAN),
               "Loopback channel not valid in MHU-B-NS");

/* SHM regions must not overlap */
_Static_assert(RZV_IPC_CR8CR8_SHM_BASE + RZV_IPC_CR8CR8_SHM_SIZE
               <= RZV_IPC_CR8CM33_SHM_BASE, "CR8CR8 and CR8CM33 SHM overlap");
_Static_assert(RZV_IPC_CR8CM33_SHM_BASE + RZV_IPC_CR8CM33_SHM_SIZE
               <= RZV_IPC_LOOPBACK_SHM_BASE, "CR8CM33 and LB SHM overlap");

/* SHM sizes must be power of two */
_Static_assert((RZV_IPC_CR8CR8_SHM_SIZE  & (RZV_IPC_CR8CR8_SHM_SIZE  - 1)) == 0,
               "CR8CR8 SHM size must be power of two");
_Static_assert((RZV_IPC_CR8CM33_SHM_SIZE & (RZV_IPC_CR8CM33_SHM_SIZE - 1)) == 0,
               "CR8CM33 SHM size must be power of two");
#endif /* __STDC_VERSION__ */

#endif /* __ARCH_ARM_SRC_RZV_RZV_IPC_CHANNELS_H */

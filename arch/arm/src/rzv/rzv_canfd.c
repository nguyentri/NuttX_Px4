/****************************************************************************
 * arch/arm/src/rzv/rzv_canfd.c
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

/* RZ/V2H CAN-FD lower-half driver (arch-level).
 *
 * Uses one global RX FIFO per channel, one TX mailbox per channel, and
 * internal loopback as the boot default.
 *
 * TIMING (CANFDCLK=80MHz)
 * =======================
 * Nominal : BRP=2 → 40MHz tq, TSEG1=74, TSEG2=25, SJW=25 → 400 kbps
 * Data    : BRP=1 → 80MHz tq, TSEG1=16, TSEG2=8,  SJW=8  → 3.2 Mbps
 *
 * INIT SEQUENCE
 * =============
 * 1.  CPG clock enable + module unreset
 * 2.  Global → Reset mode (CFDGCTR.GMDC=1)
 * 3.  Global config (CFDGCFG)
 * 4.  RX MB count/payload = 0 (RX FIFO path only)
 * 5.  RX FIFO 0 config  (CFDRFCC[0])
 * 6.  Channel → Reset mode (CFDCnCTR.CHMDC=1)
 * 7.  Nominal + Data bit timing (CFDCnNCFG, CFDC2nDCFG)
 * 8.  AFL: one accept-all rule per channel
 * 9.  Channel interrupt enables (CFDCnCTR)
 * 10. TX MB 0 interrupt enable (CFDTMIEC0)
 * 11. Channel → Comm mode; Global → Op mode
 * 12. Internal loopback (CTME=1, CTMS=INT_LOOP) — toggle via ioctl
 * 13. ICU attach shared RX/global-error plus per-channel TX/error IRQs
 *
 * HARDWARE HEADER
 * ===============
 * All register addresses and bit masks from hardware/rzv_canfd.h
 * (820 LOC, deliverable — DO NOT modify here).
 */

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/can/can.h>

#include "arm_internal.h"
#include "chip.h"
#include "rzv_icu.h"
#include "rzv_clock.h"
#include "rzv_canfd.h"
#include "hardware/rzv_canfd.h"

#ifdef CONFIG_RZV_CANFD

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Register access helpers */

#define rzv_rd32(a)       getreg32(a)
#define rzv_wr32(v, a)    putreg32(v, a)

/* Byte-wide register access for CFDTMC / CFDTMSTS arrays */

#define rzv_rd8(a)        getreg8(a)
#define rzv_wr8(v, a)     putreg8(v, a)

/* Per-channel TX mailbox 0 global index */

#define TXMB0(ch)         RZV_CANFD_TXMB_CH(ch)   /* ch*16 */

/* Watchdog spin limit for mode transitions (iterations, not timed) */

#define MODE_SPIN_LIMIT   10000u

/* Loopback toggle ioctl — RZV-private command in the CAN_A vendor namespace */

#define CANIOC_RZV_LOOPBACK  _CANIOC(CAN_FIRST + CAN_NCMDS + 0)

/* Nominal bit-timing constants (CANFDCLK=80MHz, 400 kbps)
 * Tq = 1/40MHz = 25 ns; bit = 100 Tq = 2.5 µs = 400 kbps
 * Register value = field_value - 1 where hardware adds 1.
 * nominal_bitrate=400000, BRP=2, TSEG1=74, TSEG2=25, SJW=25
 */

#define NCFG_NBRP         (2u  - 1u)  /* prescaler = 2    → 40 MHz tq  */
#define NCFG_NTSEG1       (74u - 1u)  /* tseg1 = 74 tq                 */
#define NCFG_NTSEG2       (25u - 1u)  /* tseg2 = 25 tq                 */
#define NCFG_NSJW         (25u - 1u)  /* sjw   = 25 tq                 */

/* Data-phase bit-timing constants (80 MHz tq, 3.2 Mbps)
 * Tq = 1/80MHz = 12.5 ns; bit = 25 Tq = 312.5 ns = 3.2 Mbps
 * data_bitrate=3200000, BRP=1, TSEG1=16, TSEG2=8, SJW=8
 */

#define DCFG_DBRP         (1u  - 1u)  /* prescaler = 1    → 80 MHz tq  */
#define DCFG_DTSEG1       (16u - 1u)  /* tseg1 = 16 tq                 */
#define DCFG_DTSEG2       (8u  - 1u)  /* tseg2 =  8 tq                 */
#define DCFG_DSJW         (8u  - 1u)  /* sjw   =  8 tq                 */

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* Per-channel driver state */

struct rzv_canfd_s
{
  struct can_dev_s dev;                    /* NuttX CAN upper-half device */
  const struct rzv_canfd_config_s *config; /* Immutable channel config    */
  uint8_t  channel;                        /* Channel index (0 or 1)      */
  int      tx_irq;                         /* IRQ from rzv_icu_attach TX  */
  int      err_irq;                        /* IRQ from rzv_icu_attach ERR */
  bool     initialized;                    /* True after first setup()    */
  bool     loopback;                       /* True = internal loopback    */
};

/* Immutable per-channel configuration */

struct rzv_canfd_config_s
{
  uint8_t  channel;           /* 0 or 1                             */
  int      elc_tx;            /* ELC event: channel TX              */
  int      elc_err;           /* ELC event: channel error           */
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* NuttX CAN lower-half ops */

static void rzv_canfd_reset(struct can_dev_s *dev);
static int  rzv_canfd_setup(struct can_dev_s *dev);
static void rzv_canfd_shutdown(struct can_dev_s *dev);
static void rzv_canfd_rxint(struct can_dev_s *dev, bool enable);
static void rzv_canfd_txint(struct can_dev_s *dev, bool enable);
static int  rzv_canfd_ioctl(struct can_dev_s *dev, int cmd,
                             unsigned long arg);
static int  rzv_canfd_remoterequest(struct can_dev_s *dev, uint16_t id);
static int  rzv_canfd_send(struct can_dev_s *dev, struct can_msg_s *msg);
static bool rzv_canfd_txready(struct can_dev_s *dev);
static bool rzv_canfd_txempty(struct can_dev_s *dev);

/* Interrupt service routines */

static int rzv_canfd_tx_isr(int irq, void *context, void *arg);
static int rzv_canfd_rx_isr(int irq, void *context, void *arg);
static int rzv_canfd_err_isr(int irq, void *context, void *arg);
static int rzv_canfd_glerr_isr(int irq, void *context, void *arg);

/* Internal helpers */

static int  rzv_canfd_global_init(void);
static int  rzv_canfd_ch_init(struct rzv_canfd_s *priv);
static int  rzv_canfd_set_loopback(struct rzv_canfd_s *priv, bool enable);

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* CAN-FD DLC to byte-count lookup table.
 * DLC 0-8 are linear; DLC 9-15 encode 12,16,20,24,32,48,64 bytes.
 * Used in both TX (memcpy length) and RX (frame length) paths.
 * Raw DLC nibble is still written to the hardware DLC field unchanged.
 */

static const uint8_t g_dlc_to_bytes[16] =
{
  0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64
};

static const struct can_ops_s g_rzv_canfd_ops =
{
  .co_reset         = rzv_canfd_reset,
  .co_setup         = rzv_canfd_setup,
  .co_shutdown      = rzv_canfd_shutdown,
  .co_rxint         = rzv_canfd_rxint,
  .co_txint         = rzv_canfd_txint,
  .co_ioctl         = rzv_canfd_ioctl,
  .co_remoterequest = rzv_canfd_remoterequest,
  .co_send          = rzv_canfd_send,
  .co_txready       = rzv_canfd_txready,
  .co_txempty       = rzv_canfd_txempty,
};

/* Shared global IRQs — attached once by rzv_canfd_global_init().
 * Per-FIFO dispatch: FIFO k -> channel k (identity mapping).
 */

static int g_rxf_irq  = -1;                   /* attached once in global_init */
static int g_glerr_irq = -1;                  /* attached once in global_init */
static struct rzv_canfd_s *g_priv_by_fifo[2]; /* fifo 0..1 -> priv           */

#ifdef CONFIG_RZV_CANFD0

static const struct rzv_canfd_config_s g_rzv_canfd0_config =
{
  .channel  = 0,
  .elc_tx   = RZV_ELC_CANFD_CH0_TRX,
  .elc_err  = RZV_ELC_CANFD_CH0_ERR,
};

static struct rzv_canfd_s g_rzv_canfd0_priv =
{
  .dev      =
  {
    .cd_ops  = &g_rzv_canfd_ops,
    .cd_priv = &g_rzv_canfd0_priv,
  },
  .config   = &g_rzv_canfd0_config,
  .channel  = 0,
  .tx_irq   = -1,
  .err_irq  = -1,
  .initialized = false,
  .loopback = true,  /* boot default: internal loopback */
};

#endif /* CONFIG_RZV_CANFD0 */

#ifdef CONFIG_RZV_CANFD1

static const struct rzv_canfd_config_s g_rzv_canfd1_config =
{
  .channel  = 1,
  .elc_tx   = RZV_ELC_CANFD_CH1_TRX,
  .elc_err  = RZV_ELC_CANFD_CH1_ERR,
};

static struct rzv_canfd_s g_rzv_canfd1_priv =
{
  .dev      =
  {
    .cd_ops  = &g_rzv_canfd_ops,
    .cd_priv = &g_rzv_canfd1_priv,
  },
  .config   = &g_rzv_canfd1_config,
  .channel  = 1,
  .tx_irq   = -1,
  .err_irq  = -1,
  .initialized = false,
  .loopback = true,
};

#endif /* CONFIG_RZV_CANFD1 */

/****************************************************************************
 * Private Functions — helpers
 ****************************************************************************/

/* rzv_canfd_wait_mode: spin-wait for a status bit pattern.
 * Returns 0 on success, -ETIMEDOUT if limit exceeded.
 */

static int rzv_canfd_wait_mode(uint32_t reg, uint32_t mask,
                                uint32_t expected)
{
  uint32_t limit = MODE_SPIN_LIMIT;

  while ((rzv_rd32(reg) & mask) != expected)
    {
      if (--limit == 0)
        {
          return -ETIMEDOUT;
        }
    }

  return OK;
}

/* rzv_canfd_global_init: one-time global IP initialization.
 * Called from rzv_canfd_initialize(); protected by static flag.
 */

static int rzv_canfd_global_init(void)
{
  uint32_t val;
  int ret;

  /* Step 1: CPG clock enable + module unreset (shared gate for all CAN-FD) */

  ret = rzv_clock_enable(RZV_CPG_CLK_CANFD);
  if (ret < 0)
    {
      canerr("CANFD clock enable failed: %d\n", ret);
      return ret;
    }

  ret = rzv_module_unreset(RZV_CPG_CLK_CANFD);
  if (ret < 0)
    {
      canerr("CANFD module unreset failed: %d\n", ret);
      return ret;
    }

  /* Step 2: Global → Reset mode */

  val = rzv_rd32(RZV_CANFD_CFDGCTR);
  val = (val & ~CANFD_GCTR_GMDC_MASK) | CANFD_GCTR_GMDC_RESET;
  rzv_wr32(val, RZV_CANFD_CFDGCTR);

  ret = rzv_canfd_wait_mode(RZV_CANFD_CFDGSTS,
                             CANFD_GSTS_GRSTSTS, CANFD_GSTS_GRSTSTS);
  if (ret < 0)
    {
      canerr("CANFD global reset mode timeout\n");
      return ret;
    }

  /* Step 3: Global config — CANFDCLK source, ID priority, DLC check */

  val = CANFD_GCFG_DCS;   /* Use CANFDCLK (80 MHz) as clock source */
  val |= CANFD_GCFG_TPRI; /* Transmission priority: ID-based        */
  val |= CANFD_GCFG_DCE;  /* DLC check enable                       */
  val |= CANFD_GCFG_DRE;  /* DLC replacement enable                 */
  rzv_wr32(val, RZV_CANFD_CFDGCFG);

  /* Step 4: RX MB count = 0 (we only use RX FIFO path) */

  rzv_wr32(0, RZV_CANFD_CFDRMNB);

  /* Step 5a: RX FIFO 0 config (channel 0 destination)
   * depth=8, payload=64B, threshold=3.  co_rxint enables RFIE on open.
   */

  val = CANFD_RFCC_RFE                                    /* FIFO enable */
      | CANFD_RFCC_RFPLS_64B                              /* 64-byte payload */
      | CANFD_RFCC_RFDC_8                                 /* depth = 8 */
      | CANFD_RFCC_RFIM                                   /* threshold mode */
      | (2u << CANFD_RFCC_RFIGCV_SHIFT);                 /* threshold = 3 */
  rzv_wr32(val, RZV_CANFD_CFDRFCC(0));

#ifdef CONFIG_RZV_CANFD1
  /* Step 5b: RX FIFO 1 config (channel 1 destination) — same settings */

  rzv_wr32(val, RZV_CANFD_CFDRFCC(1));
#endif

  /* Step 6: AFL — per-channel slice.
   *   ch0 slice: 1 rule  (page-relative rule 0)         -> FIFO 0
   *   ch1 slice: 1 rule  (page-relative rule 1 globally) -> FIFO 1
   * CFDGAFLCFG0: RNC1[8:0] = ch1 count, RNC0[24:16] = ch0 count.
   * Note swapped field positions vs RA8 — verified in rzv_canfd.h:523-526.
   */

  val = (1u << CANFD_GAFLCFG_RNC0_SHIFT);     /* ch0 = 1 rule */
#ifdef CONFIG_RZV_CANFD1
  val |= (1u << CANFD_GAFLCFG_RNC1_SHIFT);    /* ch1 = 1 rule */
#endif
  rzv_wr32(val, RZV_CANFD_CFDGAFLCFG0);

  /* Unlock AFL for write (AFLDAE=1, page 0) */

  rzv_wr32(CANFD_GAFLECTR_AFLDAE | (0u << CANFD_GAFLECTR_AFLPN_SHIFT),
           RZV_CANFD_CFDGAFLECTR);

  /* Rule 0: ch0 slice, accept-all -> FIFO 0 */

  rzv_wr32(0, RZV_CANFD_BASE + RZV_CANFD_CFDGAFL_ID_OFFSET(0));
  rzv_wr32(0, RZV_CANFD_BASE + RZV_CANFD_CFDGAFL_M_OFFSET(0));
  rzv_wr32(0, RZV_CANFD_BASE + RZV_CANFD_CFDGAFL_P0_OFFSET(0));
  rzv_wr32((1u << 0), RZV_CANFD_BASE + RZV_CANFD_CFDGAFL_P1_OFFSET(0));

#ifdef CONFIG_RZV_CANFD1
  /* Rule 1: ch1 slice, accept-all -> FIFO 1.
   * AFL rule index is global across slices; ch1's first rule sits at
   * global index = RNC0 = 1.
   */

  rzv_wr32(0, RZV_CANFD_BASE + RZV_CANFD_CFDGAFL_ID_OFFSET(1));
  rzv_wr32(0, RZV_CANFD_BASE + RZV_CANFD_CFDGAFL_M_OFFSET(1));
  rzv_wr32(0, RZV_CANFD_BASE + RZV_CANFD_CFDGAFL_P0_OFFSET(1));
  rzv_wr32((1u << 1), RZV_CANFD_BASE + RZV_CANFD_CFDGAFL_P1_OFFSET(1));
#endif

  /* Lock AFL */

  rzv_wr32(0, RZV_CANFD_CFDGAFLECTR);

  /* Attach shared global IRQs once. arg=NULL — ISRs read globals. */

  g_glerr_irq = rzv_icu_attach(RZV_ELC_CANFD_GLERR,
                                rzv_canfd_glerr_isr, NULL, true);
  if (g_glerr_irq < 0)
    {
      canerr("CANFD: glerr icu_attach failed %d\n", g_glerr_irq);
      /* non-fatal: continue */
    }

  g_rxf_irq = rzv_icu_attach(RZV_ELC_CANFD_RXFINT,
                              rzv_canfd_rx_isr, NULL, true);
  if (g_rxf_irq < 0)
    {
      canerr("CANFD: rxf icu_attach failed %d\n", g_rxf_irq);
      ret = g_rxf_irq;
      if (g_glerr_irq >= 0)
        {
          rzv_icu_detach(g_glerr_irq);
          g_glerr_irq = -1;
        }

      return ret;
    }

  /* Global error interrupt enables */

  val = rzv_rd32(RZV_CANFD_CFDGCTR);
  val |= CANFD_GCTR_DEIE | CANFD_GCTR_MEIE | CANFD_GCTR_CMPOFIE;
  rzv_wr32(val, RZV_CANFD_CFDGCTR);

  /* Step 7 (global part): Global → Operation mode */

  val = rzv_rd32(RZV_CANFD_CFDGCTR);
  val = (val & ~CANFD_GCTR_GMDC_MASK) | CANFD_GCTR_GMDC_COMM;
  rzv_wr32(val, RZV_CANFD_CFDGCTR);

  ret = rzv_canfd_wait_mode(RZV_CANFD_CFDGSTS,
                             CANFD_GSTS_GRSTSTS | CANFD_GSTS_GHLTSTS, 0);
  if (ret < 0)
    {
      canerr("CANFD global op mode timeout\n");
      return ret;
    }

  return OK;
}

/* rzv_canfd_ch_init: per-channel initialization.
 * Called from rzv_canfd_setup(); channel must not be in comm mode.
 */

static int rzv_canfd_ch_init(struct rzv_canfd_s *priv)
{
  uint8_t ch = priv->channel;
  uint32_t val;
  int ret;

  /* Channel → Reset mode */

  val = rzv_rd32(RZV_CANFD_CFDC_CTR(ch));
  val = (val & ~CANFD_CFDC_CTR_CHMDC_MASK) | CANFD_CFDC_CTR_CHMDC_RESET;
  rzv_wr32(val, RZV_CANFD_CFDC_CTR(ch));

  ret = rzv_canfd_wait_mode(RZV_CANFD_CFDC_STS(ch),
                            CANFD_CFDC_STS_CRSTSTS,
                            CANFD_CFDC_STS_CRSTSTS);
  if (ret < 0)
    {
      return ret;
    }

  /* Nominal bit timing — NBRP, NSJW, NTSEG1, NTSEG2
   * NCFG register: bits[9:0]=NBRP, [16:10]=NSJW, [24:17]=NTSEG1,
   *                [31:25]=NTSEG2
   */

  val = ((uint32_t)NCFG_NBRP   << CANFD_CFDC_NCFG_NBRP_SHIFT)
      | ((uint32_t)NCFG_NSJW   << CANFD_CFDC_NCFG_NSJW_SHIFT)
      | ((uint32_t)NCFG_NTSEG1 << CANFD_CFDC_NCFG_NTSEG1_SHIFT)
      | ((uint32_t)NCFG_NTSEG2 << CANFD_CFDC_NCFG_NTSEG2_SHIFT);
  rzv_wr32(val, RZV_CANFD_CFDC_NCFG(ch));

  /* Data-phase bit timing — DBRP, DSJW, DTSEG1, DTSEG2 */

  val = ((uint32_t)DCFG_DBRP   << CANFD_CFDC2_DCFG_DBRP_SHIFT)
      | ((uint32_t)DCFG_DTSEG1 << CANFD_CFDC2_DCFG_DTSEG1_SHIFT)
      | ((uint32_t)DCFG_DTSEG2 << CANFD_CFDC2_DCFG_DTSEG2_SHIFT)
      | ((uint32_t)DCFG_DSJW   << CANFD_CFDC2_DCFG_DSJW_SHIFT);
  rzv_wr32(val, RZV_CANFD_CFDC2_DCFG(ch));

  /* Permit both Classical CAN and CAN-FD frames. */

  val = rzv_rd32(RZV_CANFD_CFDC2_FDCFG(ch));
  val &= ~CANFD_CFDC2_FDCFG_FDOE;
  rzv_wr32(val, RZV_CANFD_CFDC2_FDCFG(ch));

  /* TX mailbox 0 interrupt enable */

  val = rzv_rd32(RZV_CANFD_CFDTMIEC0);
  val |= (1u << (uint32_t)TXMB0(ch));
  rzv_wr32(val, RZV_CANFD_CFDTMIEC0);

  /* Channel interrupt enables: bus error, error warning, error passive,
   * bus-off entry, overload
   */

  val = rzv_rd32(RZV_CANFD_CFDC_CTR(ch));
  val |= CANFD_CFDC_CTR_BEIE
       | CANFD_CFDC_CTR_EWIE
       | CANFD_CFDC_CTR_EPIE
       | CANFD_CFDC_CTR_BOEIE
       | CANFD_CFDC_CTR_OLIE;
  rzv_wr32(val, RZV_CANFD_CFDC_CTR(ch));

  /* Clear any stale error flags */

  rzv_wr32(0, RZV_CANFD_CFDC_ERFL(ch));
  rzv_wr32(0, RZV_CANFD_CFDGERFL);

  /* Channel → Communication mode */

  val = rzv_rd32(RZV_CANFD_CFDC_CTR(ch));
  val = (val & ~CANFD_CFDC_CTR_CHMDC_MASK) | CANFD_CFDC_CTR_CHMDC_COMM;
  rzv_wr32(val, RZV_CANFD_CFDC_CTR(ch));

  return rzv_canfd_wait_mode(RZV_CANFD_CFDC_STS(ch),
                              CANFD_CFDC_STS_CRSTSTS
                              | CANFD_CFDC_STS_CHLTSTS, 0);
}

/* rzv_canfd_set_loopback: enable/disable internal loopback test mode.
 * Per RZ/V2H UM, CTME/CTMS are writable only in Channel Reset mode
 * (CHMDC=01).  We transition Comm → Reset → set bits → Comm.
 */

static int rzv_canfd_set_loopback(struct rzv_canfd_s *priv, bool enable)
{
  uint8_t ch = priv->channel;
  uint32_t ctr;
  int ret;

  /* Enter Reset mode (CTME/CTMS require Reset mode per RSCAN-FD spec) */

  ctr = rzv_rd32(RZV_CANFD_CFDC_CTR(ch));
  ctr = (ctr & ~CANFD_CFDC_CTR_CHMDC_MASK) | CANFD_CFDC_CTR_CHMDC_RESET;
  rzv_wr32(ctr, RZV_CANFD_CFDC_CTR(ch));
  ret = rzv_canfd_wait_mode(RZV_CANFD_CFDC_STS(ch),
                            CANFD_CFDC_STS_CRSTSTS,
                            CANFD_CFDC_STS_CRSTSTS);
  if (ret < 0)
    {
      return ret;
    }

  ctr = rzv_rd32(RZV_CANFD_CFDC_CTR(ch));

  if (enable)
    {
      ctr |= CANFD_CFDC_CTR_CTME;  /* test mode enable */
      ctr = (ctr & ~CANFD_CFDC_CTR_CTMS_MASK)
          | CANFD_CFDC_CTR_CTMS_INT_LOOP;
    }
  else
    {
      ctr &= ~CANFD_CFDC_CTR_CTME;
      ctr &= ~CANFD_CFDC_CTR_CTMS_MASK;
    }

  rzv_wr32(ctr, RZV_CANFD_CFDC_CTR(ch));

  /* Back to Comm mode */

  ctr = rzv_rd32(RZV_CANFD_CFDC_CTR(ch));
  ctr = (ctr & ~CANFD_CFDC_CTR_CHMDC_MASK) | CANFD_CFDC_CTR_CHMDC_COMM;
  rzv_wr32(ctr, RZV_CANFD_CFDC_CTR(ch));
  ret = rzv_canfd_wait_mode(RZV_CANFD_CFDC_STS(ch),
                            CANFD_CFDC_STS_CRSTSTS
                            | CANFD_CFDC_STS_CHLTSTS, 0);
  if (ret < 0)
    {
      return ret;
    }

  priv->loopback = enable;
  return OK;
}

/****************************************************************************
 * Private Functions — NuttX CAN lower-half ops
 ****************************************************************************/

static void rzv_canfd_reset(struct can_dev_s *dev)
{
  struct rzv_canfd_s *priv = (struct rzv_canfd_s *)dev->cd_priv;
  uint8_t ch = priv->channel;
  uint32_t ctr;

  /* Transition channel to Reset mode */

  ctr = rzv_rd32(RZV_CANFD_CFDC_CTR(ch));
  ctr = (ctr & ~CANFD_CFDC_CTR_CHMDC_MASK) | CANFD_CFDC_CTR_CHMDC_RESET;
  rzv_wr32(ctr, RZV_CANFD_CFDC_CTR(ch));

  if (rzv_canfd_wait_mode(RZV_CANFD_CFDC_STS(ch),
                           CANFD_CFDC_STS_CRSTSTS,
                           CANFD_CFDC_STS_CRSTSTS) < 0)
    {
      canerr("CAN%d: reset mode timeout\n", ch);
    }
}

static int rzv_canfd_setup(struct can_dev_s *dev)
{
  struct rzv_canfd_s *priv = (struct rzv_canfd_s *)dev->cd_priv;
  const struct rzv_canfd_config_s *cfg = priv->config;
  int ret;

  if (priv->initialized)
    {
      return OK;
    }

  /* Per-channel hardware init */

  ret = rzv_canfd_ch_init(priv);
  if (ret < 0)
    {
      return ret;
    }

  /* Apply boot-default loopback mode */

  if (priv->loopback)
    {
      ret = rzv_canfd_set_loopback(priv, true);
      if (ret < 0)
        {
          return ret;
        }
    }

  /* Attach interrupt handlers via ICU */

  priv->tx_irq = rzv_icu_attach(cfg->elc_tx,
                                  rzv_canfd_tx_isr, priv, true);
  if (priv->tx_irq < 0)
    {
      canerr("CAN%d: tx icu_attach failed %d\n",
             priv->channel, priv->tx_irq);
      return priv->tx_irq;
    }

  priv->err_irq = rzv_icu_attach(cfg->elc_err,
                                   rzv_canfd_err_isr, priv, true);
  if (priv->err_irq < 0)
    {
      canerr("CAN%d: err icu_attach failed %d\n",
             priv->channel, priv->err_irq);
      rzv_icu_detach(priv->tx_irq);
      priv->tx_irq = -1;
      return priv->err_irq;
    }

  /* The shared RX ISR needs this mapping before the upper half enables RFIE. */

  g_priv_by_fifo[priv->channel] = priv;
  priv->initialized = true;
  return OK;
}

static void rzv_canfd_shutdown(struct can_dev_s *dev)
{
  struct rzv_canfd_s *priv = (struct rzv_canfd_s *)dev->cd_priv;

  /* Ensure the shared RX ISR cannot dispatch this FIFO during teardown. */

  rzv_canfd_rxint(dev, false);
  rzv_canfd_reset(dev);

  if (priv->tx_irq >= 0)
    {
      rzv_icu_detach(priv->tx_irq);
      priv->tx_irq = -1;
    }

  if (priv->err_irq >= 0)
    {
      rzv_icu_detach(priv->err_irq);
      priv->err_irq = -1;
    }

  /* Global IRQs (g_glerr_irq, g_rxf_irq) outlive any single channel —
   * leave attached for the driver lifetime.
   */

  g_priv_by_fifo[priv->channel] = NULL;

  priv->initialized = false;
}

static void rzv_canfd_rxint(struct can_dev_s *dev, bool enable)
{
  struct rzv_canfd_s *priv = (struct rzv_canfd_s *)dev->cd_priv;

  uint32_t val = rzv_rd32(RZV_CANFD_CFDRFCC(priv->channel));

  if (enable)
    {
      val |= CANFD_RFCC_RFIE;
    }
  else
    {
      val &= ~CANFD_RFCC_RFIE;
    }

  rzv_wr32(val, RZV_CANFD_CFDRFCC(priv->channel));
}

static void rzv_canfd_txint(struct can_dev_s *dev, bool enable)
{
  struct rzv_canfd_s *priv = (struct rzv_canfd_s *)dev->cd_priv;

  if (priv->tx_irq >= 0)
    {
      if (enable)
        {
          up_enable_irq(priv->tx_irq);
        }
      else
        {
          up_disable_irq(priv->tx_irq);
        }
    }
}

static int rzv_canfd_ioctl(struct can_dev_s *dev, int cmd,
                            unsigned long arg)
{
  struct rzv_canfd_s *priv = (struct rzv_canfd_s *)dev->cd_priv;

  switch (cmd)
    {
      case CANIOC_SET_BITTIMING:
        /* TODO: dynamic bitrate change (out-of-scope v1 per design) */
        return -ENOTTY;

      case CANIOC_RZV_LOOPBACK:
        /* Enable (arg=1) or disable (arg=0) internal loopback mode */

        return rzv_canfd_set_loopback(priv, arg != 0);

      default:
        return -ENOTTY;
    }
}

static int rzv_canfd_remoterequest(struct can_dev_s *dev, uint16_t id)
{
  /* Remote frames not implemented at v1 */

  return -ENOSYS;
}

static int rzv_canfd_send(struct can_dev_s *dev, struct can_msg_s *msg)
{
  struct rzv_canfd_s *priv = (struct rzv_canfd_s *)dev->cd_priv;
  uint8_t ch = priv->channel;
  uint32_t mb = TXMB0(ch);  /* Use TX mailbox 0 for this channel */
  uint32_t id_reg;
  uint32_t ptr_reg;
  uint32_t fdctr_reg;
  uint8_t  dlc;
  uint8_t  bytes;
  int      i;

  /* Check mailbox is not busy (TMTRM=transmission request mirrored) */

  if (rzv_rd8(RZV_CANFD_CFDTMSTS(mb)) & CANFD_TMSTS_TMTRM)
    {
      return -EBUSY;
    }

  dlc = msg->cm_hdr.ch_dlc;

  /* Build ID register */

#ifdef CONFIG_CAN_EXTID
  if (msg->cm_hdr.ch_extid)
    {
      id_reg = (uint32_t)msg->cm_hdr.ch_id & 0x1fffffffu;
      id_reg |= CANFD_TMID_TMIDE;
    }
  else
#endif
    {
      id_reg = ((uint32_t)msg->cm_hdr.ch_id & 0x7ffu) << 18;
    }

  if (msg->cm_hdr.ch_rtr)
    {
      id_reg |= CANFD_TMID_TMRTR;
    }

  rzv_wr32(id_reg, RZV_CANFD_BASE + RZV_CANFD_CFDTMID_OFFSET(mb));

  /* DLC in TMPTR[31:28] */

  ptr_reg = (uint32_t)dlc << CANFD_TMPTR_TMDLC_SHIFT;
  rzv_wr32(ptr_reg, RZV_CANFD_BASE + RZV_CANFD_CFDTMPTR_OFFSET(mb));

  /* Frame format follows the upper-half header. */

  fdctr_reg = 0;
#ifdef CONFIG_CAN_FD
  if ((!msg->cm_hdr.ch_edl && dlc > 8)
      || (msg->cm_hdr.ch_brs && !msg->cm_hdr.ch_edl))
    {
      return -EINVAL;
    }

  if (msg->cm_hdr.ch_edl)
    {
      fdctr_reg |= CANFD_TMFDCTR_TMFDF;
      if (msg->cm_hdr.ch_brs)
        {
          fdctr_reg |= CANFD_TMFDCTR_TMBRS;
        }
    }
#endif
  rzv_wr32(fdctr_reg, RZV_CANFD_BASE + RZV_CANFD_CFDTMFDCTR_OFFSET(mb));

  /* Write data bytes — hardware expects 32-bit little-endian words */

  /* DLC is the raw 4-bit field written to hardware unchanged.
   * Byte count is non-linear for DLC > 8 (CAN-FD): use LUT.
   */

  bytes = g_dlc_to_bytes[dlc & 0xfu];

  for (i = 0; i < (bytes + 3) / 4; i++)
    {
      uint32_t word = 0;
      int j;
      for (j = 0; j < 4 && (i * 4 + j) < bytes; j++)
        {
          word |= (uint32_t)msg->cm_data[i * 4 + j] << (j * 8);
        }

      rzv_wr32(word,
               RZV_CANFD_BASE + RZV_CANFD_CFDTMDF_OFFSET(mb, (uint32_t)i));
    }

  /* Request transmission */

  rzv_wr8(CANFD_TMC_TMTR, RZV_CANFD_CFDTMC(mb));

  return OK;
}

static bool rzv_canfd_txready(struct can_dev_s *dev)
{
  struct rzv_canfd_s *priv = (struct rzv_canfd_s *)dev->cd_priv;
  uint32_t mb = TXMB0(priv->channel);

  return (rzv_rd8(RZV_CANFD_CFDTMSTS(mb)) & CANFD_TMSTS_TMTRM) == 0;
}

static bool rzv_canfd_txempty(struct can_dev_s *dev)
{
  return rzv_canfd_txready(dev);
}

/****************************************************************************
 * Private Functions — Interrupt Service Routines
 ****************************************************************************/

static int rzv_canfd_tx_isr(int irq, void *context, void *arg)
{
  struct rzv_canfd_s *priv = (struct rzv_canfd_s *)arg;
  uint32_t mb = TXMB0(priv->channel);
  uint8_t  sts;

  sts = rzv_rd8(RZV_CANFD_CFDTMSTS(mb));

  if ((sts & CANFD_TMSTS_TMTRF_MASK) == CANFD_TMSTS_TMTRF_TX_OK)
    {
      /* Acknowledge the writable per-mailbox result flag. */

      rzv_wr8(sts & ~CANFD_TMSTS_TMTRF_MASK,
              RZV_CANFD_CFDTMSTS(mb));

      /* Notify NuttX upper half: TX done */

      can_txdone(&priv->dev);
    }
  else if ((sts & CANFD_TMSTS_TMTRF_MASK) == CANFD_TMSTS_TMTRF_ABORT)
    {
      rzv_wr8(sts & ~CANFD_TMSTS_TMTRF_MASK,
              RZV_CANFD_CFDTMSTS(mb));
      canerr("CAN%d: TX aborted\n", priv->channel);
      can_txdone(&priv->dev);
    }

  return OK;
}

/* rzv_canfd_rx_isr: global RX FIFO dispatcher.
 * Loops over all enabled FIFOs (k = 0 .. nfifos-1); each FIFO k
 * belongs to channel k via identity mapping.  g_priv_by_fifo[k] is
 * NULL-guarded for channels not yet registered.
 */

static int rzv_canfd_rx_isr(int irq, void *context, void *arg)
{
  const int nfifos =
#ifdef CONFIG_RZV_CANFD1
    2;
#else
    1;
#endif
  int k;

  for (k = 0; k < nfifos; k++)
    {
      struct rzv_canfd_s *priv = g_priv_by_fifo[k];
      struct can_hdr_s hdr;
      uint8_t  data[CAN_MAXDATALEN];
      uint32_t rfsts;
      uint32_t id_reg;
      uint32_t ptr_reg;
      uint32_t fdsts_reg;
      int      dw;
      int      bytes;

      if (priv == NULL)
        {
          continue;   /* channel not registered yet */
        }

      rfsts = rzv_rd32(RZV_CANFD_CFDRFSTS(k));

      while ((rfsts & CANFD_RFSTS_RFEMP) == 0)
        {
          memset(&hdr, 0, sizeof(hdr));

          id_reg    = rzv_rd32(RZV_CANFD_BASE + RZV_CANFD_CFDRFID_OFFSET(k));
          ptr_reg   = rzv_rd32(RZV_CANFD_BASE + RZV_CANFD_CFDRFPTR_OFFSET(k));
          fdsts_reg = rzv_rd32(RZV_CANFD_BASE
                               + RZV_CANFD_CFDRFFDSTS_OFFSET(k));

          hdr.ch_rtr = (id_reg & CANFD_RFID_RFRTR) ? 1 : 0;
          hdr.ch_dlc = (uint8_t)((ptr_reg & CANFD_RFPTR_RFDLC_MASK)
                                  >> CANFD_RFPTR_RFDLC_SHIFT);

#ifdef CONFIG_CAN_EXTID
          hdr.ch_extid = (id_reg & CANFD_RFID_RFIDE) ? 1 : 0;
          if (hdr.ch_extid)
            {
              hdr.ch_id = id_reg & 0x1fffffffu;  /* 29-bit extended ID */
            }
          else
            {
              hdr.ch_id = (id_reg >> 18) & 0x7ffu;  /* 11-bit standard ID */
            }
#else
          hdr.ch_id = (uint16_t)((id_reg >> 18) & 0x7ffu);  /* std ID only */
#endif

#ifdef CONFIG_CAN_FD
          hdr.ch_edl = (fdsts_reg & CANFD_RFFDSTS_RFFDF) ? 1 : 0;
          hdr.ch_brs = (fdsts_reg & CANFD_RFFDSTS_RFBRS) ? 1 : 0;
#endif

          /* Decode DLC to byte count; clamp to buffer size.
           * DLC > 8 is non-linear for CAN-FD frames — use LUT.
           */

          bytes = (int)g_dlc_to_bytes[hdr.ch_dlc & 0xfu];
          if (bytes > CAN_MAXDATALEN)
            {
              bytes = CAN_MAXDATALEN;
            }

          for (dw = 0; dw < (bytes + 3) / 4; dw++)
            {
              uint32_t word;
              int b;

              word = rzv_rd32(RZV_CANFD_BASE
                              + RZV_CANFD_CFDRFDF_OFFSET(k, (uint32_t)dw));
              for (b = 0; b < 4 && (dw * 4 + b) < bytes; b++)
                {
                  data[dw * 4 + b] = (uint8_t)(word >> (b * 8));
                }
            }

          /* Increment RX FIFO read pointer to release slot */

          rzv_wr32(0xffu, RZV_CANFD_CFDRFPCTR(k));

          /* Deliver frame to upper half */

          can_receive(&priv->dev, &hdr, data);

          rfsts = rzv_rd32(RZV_CANFD_CFDRFSTS(k));
        }

      /* Write-zero/RMW clear of RFIF; preserve other status bits. */

      rzv_wr32(rzv_rd32(RZV_CANFD_CFDRFSTS(k)) & ~CANFD_RFSTS_RFIF,
               RZV_CANFD_CFDRFSTS(k));
    }

  return OK;
}

static int rzv_canfd_err_isr(int irq, void *context, void *arg)
{
  struct rzv_canfd_s *priv = (struct rzv_canfd_s *)arg;
  uint8_t ch = priv->channel;
  uint32_t erfl;

  erfl = rzv_rd32(RZV_CANFD_CFDC_ERFL(ch));

  if (erfl != 0)
    {
      canerr("CAN%d: channel error flags 0x%08" PRIx32 "\n", ch, erfl);

      if (erfl & CANFD_CFDC_ERFL_BOEF)
        {
          canerr("CAN%d: bus-off entered\n", ch);
        }

      if (erfl & CANFD_CFDC_ERFL_EPF)
        {
          canerr("CAN%d: error-passive\n", ch);
        }

      /* Clear all error flags by writing 0 */

      rzv_wr32(0, RZV_CANFD_CFDC_ERFL(ch));
    }

  return OK;
}

static int rzv_canfd_glerr_isr(int irq, void *context, void *arg)
{
  uint32_t gerfl;

  gerfl = rzv_rd32(RZV_CANFD_CFDGERFL);

  if (gerfl != 0)
    {
      canerr("CANFD: global error flags 0x%08" PRIx32 "\n", gerfl);
      rzv_wr32(0, RZV_CANFD_CFDGERFL);
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int rzv_canfd_initialize(int channel)
{
  static bool global_done = false;
  int ret;

  /* Validate channel */

  if (channel < 0 || channel >= RZV_CANFD_NUM_CHANNELS)
    {
      return -EINVAL;
    }

  /* CFDTMIEC0 covers mailboxes 0-31 (ch0 MB0=bit0, ch1 MB0=bit16).
   * Channels >= 2 require CFDTMIEC1 which is not wired — guard here.
   * RX FIFO per-channel ownership resolved: g_priv_by_fifo[] dispatcher.
   */

  DEBUGASSERT(channel < 2);

#ifdef CONFIG_RZV_CANFD0
  if (channel == 0)
    {
      /* OK — channel 0 supported */
    }
  else
#endif
#ifdef CONFIG_RZV_CANFD1
  if (channel == 1)
    {
      /* OK — channel 1 supported */
    }
  else
#endif
    {
      return -ENODEV;
    }

  /* One-time global initialization */

  if (!global_done)
    {
      ret = rzv_canfd_global_init();
      if (ret < 0)
        {
          return ret;
        }

      global_done = true;
    }

  return OK;
}

int rzv_canfd_register(const char *devpath, int channel)
{
  struct rzv_canfd_s *priv;
  int ret;

  ret = rzv_canfd_initialize(channel);
  if (ret < 0)
    {
      canerr("CAN%d: initialize failed %d\n", channel, ret);
      return ret;
    }

  switch (channel)
    {
#ifdef CONFIG_RZV_CANFD0
      case 0:
        priv = &g_rzv_canfd0_priv;
        break;
#endif

#ifdef CONFIG_RZV_CANFD1
      case 1:
        priv = &g_rzv_canfd1_priv;
        break;
#endif

      default:
        return -ENODEV;
    }

  ret = can_register(devpath, &priv->dev);
  if (ret < 0)
    {
      canerr("CAN%d: can_register(%s) failed %d\n", channel, devpath, ret);
      return ret;
    }

  caninfo("CAN%d registered as %s (loopback=%d)\n",
          channel, devpath, (int)priv->loopback);

  return OK;
}

#endif /* CONFIG_RZV_CANFD */

/****************************************************************************
 * arch/arm/src/rzv/rzv_serial.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_UART_SCIF

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>

#ifdef CONFIG_SERIAL_TERMIOS
#  include <termios.h>
#endif

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/fs/ioctl.h>
#include <nuttx/serial/serial.h>

#include "chip.h"
#include "arm_internal.h"
#include "rzv_icu.h"
#include "rzv_clock.h"
#include "hardware/rzv_scifa.h"

/* RZ/V2H R9A09G057H exposes a single SCIFA channel (SCIFA0). CMSIS device
 * header defines only R_SCIFA0_BASE; subsequent peripheral slots (e.g.
 * 0x11C01800) belong to CMTW0. Enabling SCIF1..4 is a config error.
 */
#if defined(CONFIG_RZV_SCIF1) || defined(CONFIG_RZV_SCIF2) || \
    defined(CONFIG_RZV_SCIF3) || defined(CONFIG_RZV_SCIF4)
#  error "RZ/V2H has only SCIFA0; CONFIG_RZV_SCIF1..4 are not supported"
#endif

/* SCIFA has no modem-control-enable bit; HW flow control unsupported. */
#if defined(CONFIG_SERIAL_IFLOWCONTROL) || defined(CONFIG_SERIAL_OFLOWCONTROL)
#  if defined(CONFIG_SCIF0_IFLOWCONTROL) || defined(CONFIG_SCIF0_OFLOWCONTROL)
#    error "SCIFA on RZ/V2H does not support hardware flow control (no MCE bit)"
#  endif
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Which UART will be configured as the console. RZ/V2H has only SCIFA0. */

#if defined(CONFIG_SCIF0_SERIAL_CONSOLE)
#  define CONSOLE_DEV     g_scif0port  /* SCIF0 is console */
#  define TTYS0_DEV       g_scif0port  /* SCIF0 is ttyS0 */
#elif defined(CONFIG_RZV_SCIF0)
#  define TTYS0_DEV       g_scif0port  /* SCIF0 is ttyS0 (no console) */
#endif

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct rzv_scif_s
{
  uintptr_t base;        /* SCIFA register base address */
  uint32_t  baud;        /* Configured baud rate */
  uint32_t  clk_id;      /* Clock ID for this SCIFA channel */
  uint8_t   channel;     /* Channel number (0-4) */
  uint8_t   irq_rxi;     /* RX interrupt number */
  uint8_t   irq_txi;     /* TX interrupt number */
  uint8_t   irq_tei;     /* TX end interrupt number */
  uint8_t   irq_eri;     /* Error interrupt number */
  uint8_t   parity;      /* 0=none, 1=odd, 2=even */
  uint8_t   bits;        /* Number of data bits (7 or 8) */
  uint8_t   stopbits2;   /* True: Configure 2 stop bits instead of 1 */
#ifdef CONFIG_SERIAL_IFLOWCONTROL
  bool      iflow;       /* Input flow control (RTS) enabled */
#endif
#ifdef CONFIG_SERIAL_OFLOWCONTROL
  bool      oflow;       /* Output flow control (CTS) enabled */
#endif
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Serial driver methods */

static int  rzv_scif_setup(struct uart_dev_s *dev);
static void rzv_scif_shutdown(struct uart_dev_s *dev);
static int  rzv_scif_attach(struct uart_dev_s *dev);
static void rzv_scif_detach(struct uart_dev_s *dev);
static int  rzv_scif_ioctl(struct file *filep, int cmd, unsigned long arg);
static int  rzv_scif_receive(struct uart_dev_s *dev, unsigned int *status);
static void rzv_scif_rxint(struct uart_dev_s *dev, bool enable);
static bool rzv_scif_rxavailable(struct uart_dev_s *dev);
static void rzv_scif_send(struct uart_dev_s *dev, int ch);
static void rzv_scif_txint(struct uart_dev_s *dev, bool enable);
static bool rzv_scif_txready(struct uart_dev_s *dev);
static bool rzv_scif_txempty(struct uart_dev_s *dev);

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct uart_ops_s g_scif_ops =
{
  .setup          = rzv_scif_setup,
  .shutdown       = rzv_scif_shutdown,
  .attach         = rzv_scif_attach,
  .detach         = rzv_scif_detach,
  .ioctl          = rzv_scif_ioctl,
  .receive        = rzv_scif_receive,
  .rxint          = rzv_scif_rxint,
  .rxavailable    = rzv_scif_rxavailable,
#ifdef CONFIG_SERIAL_IFLOWCONTROL
  .rxflowcontrol  = NULL,
#endif
  .send           = rzv_scif_send,
  .txint          = rzv_scif_txint,
  .txready        = rzv_scif_txready,
  .txempty        = rzv_scif_txempty,
};

/* I/O buffers */

#ifdef CONFIG_RZV_SCIF0
static char g_scif0rxbuffer[CONFIG_SCIF0_RXBUFSIZE];
static char g_scif0txbuffer[CONFIG_SCIF0_TXBUFSIZE];
#endif

/* SCIF device structures */

#ifdef CONFIG_RZV_SCIF0
static struct rzv_scif_s g_scif0priv =
{
  .base           = RZV_SCIFA0_BASE,
  .baud           = CONFIG_SCIF0_BAUD,
  .clk_id         = RZV_CPG_CLK_SCI0,
  .channel        = 0,
  .irq_rxi        = 0,  /* Set dynamically via ICU */
  .irq_txi        = 0,
  .irq_tei        = 0,
  .irq_eri        = 0,
  .parity         = CONFIG_SCIF0_PARITY,
  .bits           = CONFIG_SCIF0_BITS,
  .stopbits2      = CONFIG_SCIF0_2STOP,
#ifdef CONFIG_SCIF0_IFLOWCONTROL
  .iflow          = true,
#endif
#ifdef CONFIG_SCIF0_OFLOWCONTROL
  .oflow          = true,
#endif
};

static uart_dev_t g_scif0port =
{
  .recv     =
  {
    .size   = CONFIG_SCIF0_RXBUFSIZE,
    .buffer = g_scif0rxbuffer,
  },
  .xmit     =
  {
    .size   = CONFIG_SCIF0_TXBUFSIZE,
    .buffer = g_scif0txbuffer,
  },
  .ops      = &g_scif_ops,
  .priv     = &g_scif0priv,
};
#endif


/****************************************************************************
 * Private Functions
 ****************************************************************************/

/* FSR / LSR bits are write-0-to-clear. To clear a specific bit safely we
 * write a value where the target bit is 0 and all other bits are 1 (W0C
 * write-1 = no-op). A read-modify-write of the read-back value can race
 * with HW reasserting the flag (BUG-05).
 */

static inline void rzv_scif_fsr_clear(uintptr_t base, uint16_t bits)
{
  putreg16((uint16_t)~bits, base + RZV_SCIF_FSR_OFFSET);
}

static inline void rzv_scif_lsr_clear(uintptr_t base, uint16_t bits)
{
  putreg16((uint16_t)~bits, base + RZV_SCIF_LSR_OFFSET);
}

/****************************************************************************
 * Name: rzv_scif_setbaud
 ****************************************************************************/

/* Divisor table (g_async_baud + g_div_coefficient).
 * Entry semantics: { bgdm, abcs, cks }; div coefficient = 8 * 2^bgdm * 2^abcs * 4^cks
 */

struct scif_baud_div_s
{
  uint8_t  bgdm;
  uint8_t  abcs;
  uint8_t  cks;
  uint16_t div_coef;
};

static const struct scif_baud_div_s g_scif_async_baud[] =
{
  { 1, 1, 0,    8 },
  { 1, 0, 0,   16 },
  { 0, 0, 0,   32 },
  { 1, 0, 1,   64 },
  { 0, 0, 1,  128 },
  { 1, 0, 2,  256 },
  { 0, 0, 2,  512 },
  { 1, 0, 3, 1024 },
  { 0, 0, 3, 2048 },
};

#define SCIF_BAUD_MAX_ERR_X1000  10000   /* 10% max allowed error */
#define SCIF_BRR_MAX             255U
#define SCIF_MDDR_MIN            128U
#define SCIF_MDDR_MAX            256U

static void rzv_scif_setbaud(struct rzv_scif_s *priv)
{
  const uint32_t pclk = RZV_CLOCK_P0CLK_HZ;
  const uint32_t baud = priv->baud;
  uint32_t best_brr = SCIF_BRR_MAX;
  uint32_t best_mddr = 0;
  uint8_t  best_cks = 0;
  uint8_t  best_bgdm = 0;
  uint8_t  best_abcs = 0;
  bool     best_brme = false;
  int32_t  best_err = 100000;   /* 100% scaled by 1000 */
  uint16_t smr;
  uint8_t  semr;
  unsigned i;

  /* Iterate divisor table; pick lowest |error|. Bit-rate modulation
   * (MDDR) tried for every candidate.
   */

  for (i = 0; i < (sizeof(g_scif_async_baud) / sizeof(g_scif_async_baud[0])); i++)
    {
      uint32_t divisor = (uint32_t)g_scif_async_baud[i].div_coef * baud;
      uint32_t temp_brr;

      if (divisor == 0)
        {
          continue;
        }

      temp_brr = pclk / divisor;

      if (temp_brr == 0 || temp_brr > (SCIF_BRR_MAX + 1U))
        {
          continue;
        }

      while (temp_brr > 0U)
        {
          temp_brr -= 1U;

          uint32_t err_divisor = divisor * (temp_brr + 1U);
          int32_t  bit_err =
            (int32_t)(((int64_t)pclk * 100000) / err_divisor) - 100000;

          /* Try with bitrate modulation (MDDR). */

          uint32_t mddr = err_divisor / (pclk / SCIF_MDDR_MAX);

          if (mddr >= SCIF_MDDR_MIN && mddr <= SCIF_MDDR_MAX)
            {
              int32_t mod_err = (((bit_err + 100000) * (int32_t)mddr) / 256)
                                - 100000;
              int32_t abs_mod = mod_err < 0 ? -mod_err : mod_err;
              if (abs_mod < best_err)
                {
                  best_err = abs_mod;
                  best_brr = temp_brr;
                  best_mddr = mddr;
                  best_brme = true;
                  best_bgdm = g_scif_async_baud[i].bgdm;
                  best_abcs = g_scif_async_baud[i].abcs;
                  best_cks  = g_scif_async_baud[i].cks;
                }
            }

          /* Try without modulation (baseline). */

          int32_t abs_err = bit_err < 0 ? -bit_err : bit_err;
          if (abs_err < best_err)
            {
              best_err = abs_err;
              best_brr = temp_brr;
              best_mddr = 0;
              best_brme = false;
              best_bgdm = g_scif_async_baud[i].bgdm;
              best_abcs = g_scif_async_baud[i].abcs;
              best_cks  = g_scif_async_baud[i].cks;
            }

          /* Early exit only on perfect match; otherwise FSP iterates the
           * full BRR range so smaller divisors with lower error can win.
           */
          if (best_err == 0)
            {
              break;
            }
        }
    }

  if (best_err > SCIF_BAUD_MAX_ERR_X1000)
    {
      _err("SCIF%d: cannot achieve baud %lu (pclk=%lu, best err=%ld permil)\n",
           priv->channel, baud, pclk, best_err);
      best_brr = 0;
      best_cks = 0;
      best_brme = false;
    }

  /* Write order:
   *   1. Clear SEMR baud bits (MDDRS, ABCS0, BGDM, BRME).
   *   2. Write BRR (MDDRS=0 maps BRR at offset 0x02).
   *   3. Write SMR.CKS.
   *   4. If BRME: set SEMR.MDDRS, write MDDR (now mapped at 0x02), then BRME.
   *   5. Final SEMR with ABCS0/BGDM/BRME set.
   */

  semr = getreg8(priv->base + RZV_SCIF_SEMR_OFFSET);
  semr &= (uint8_t)~(SCIF_SEMR_MDDRS | SCIF_SEMR_ABCS0 |
                     SCIF_SEMR_BGDM  | SCIF_SEMR_BRME);
  putreg8(semr, priv->base + RZV_SCIF_SEMR_OFFSET);

  putreg8((uint8_t)best_brr, priv->base + RZV_SCIF_BRR_OFFSET);

  /* SMR is declared __IOM uint16_t in CMSIS and FSP writes it 16-bit;
   * use 16-bit access to match the bus contract.
   */
  smr = getreg16(priv->base + RZV_SCIF_SMR_OFFSET);
  smr = (smr & (uint16_t)~SCIF_SMR_CKS_MASK) |
        (uint16_t)(best_cks & SCIF_SMR_CKS_MASK);
  putreg16(smr, priv->base + RZV_SCIF_SMR_OFFSET);

  if (best_brme && best_mddr >= SCIF_MDDR_MIN)
    {
      putreg8(semr | SCIF_SEMR_MDDRS, priv->base + RZV_SCIF_SEMR_OFFSET);
      putreg8((uint8_t)best_mddr, priv->base + RZV_SCIF_MDDR_OFFSET);
      /* Keep MDDRS=1 in the final SEMR write while BRME is active. Some
       * silicon revs in this family require MDDRS to remain set once
       * modulation is engaged, else MDDR reverts to the unmodulated div.
       */
      semr |= SCIF_SEMR_BRME | SCIF_SEMR_MDDRS;
    }

  if (best_abcs)
    {
      semr |= SCIF_SEMR_ABCS0;
    }

  if (best_bgdm)
    {
      semr |= SCIF_SEMR_BGDM;
    }

  putreg8(semr, priv->base + RZV_SCIF_SEMR_OFFSET);

  /* Wait at least 1 bit time before re-enabling TX/RX. */

  up_udelay((1000000U / baud) + 1U);

  _info("SCIF%d: baud=%lu BRR=%lu CKS=%u BGDM=%u ABCS=%u BRME=%u MDDR=%lu err=%ld\n",
        priv->channel, baud, best_brr, best_cks, best_bgdm, best_abcs,
        best_brme, best_mddr, best_err);
}

/****************************************************************************
 * Name: rzv_scif_setup
 ****************************************************************************/

static int rzv_scif_setup(struct uart_dev_s *dev)
{
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;
  uint16_t smr;
  uint16_t scr;
  uint16_t fcr;
  uint16_t ftcr;
  int timeout;
  int ret;

  /* TODO: Resolve SCIF_RXD/SCIF_TXD pin setup later. Main risk: current
   * rzv_gpioconfig() likely cannot configure 0xffff0600/0xffff0601 unless
   * special-purpose port handling already exists or is added.
   */

  /* CRITICAL: Enable peripheral clock first */
  ret = rzv_clock_enable(priv->clk_id);
  if (ret < 0)
    {
      _err("SCIF%d: Failed to enable clock: %d\n", priv->channel, ret);
      return ret;
    }

  /* If TX was previously enabled and a frame is mid-flight, drain it
   * (bounded poll) before disabling SCR — otherwise a re-open during
   * active output may chop the trailing byte. If TE is off, skip the
   * drain entirely so the loop cannot hang (BUG-01).
   */

  scr = getreg16(priv->base + RZV_SCIF_SCR_OFFSET);
  if ((scr & SCIF_SCR_TE) &&
      !(getreg16(priv->base + RZV_SCIF_FSR_OFFSET) & SCIF_FSR_TEND))
    {
      for (timeout = 5000; timeout > 0; timeout--)
        {
          if (getreg16(priv->base + RZV_SCIF_FSR_OFFSET) & SCIF_FSR_TEND)
            {
              break;
            }

          up_udelay(10);
        }
    }

  /* Disable transmit and receive plus all interrupt enables in one write.
   * Read FSR/LSR after to acknowledge stale flags.
   */

  putreg16(0, priv->base + RZV_SCIF_SCR_OFFSET);

  /* Read FSR/LSR to acknowledge any stale error/RX/TX flags before reconfig. */

  (void)getreg16(priv->base + RZV_SCIF_FSR_OFFSET);
  (void)getreg16(priv->base + RZV_SCIF_LSR_OFFSET);

  /* Reset FIFOs */
  fcr = SCIF_FCR_TFRST | SCIF_FCR_RFRST;
  putreg16(fcr, priv->base + RZV_SCIF_FCR_OFFSET);
  up_udelay(100);

  /* Use FTCR (extended 5-bit thresholds) exclusively. Keep FCR.TTRG/RTRG
   * cleared to 0 to avoid two trigger systems firing simultaneously
   * (BUG-04). RTRGS/TTRGS in FTCR select FTCR-based triggering.
   */

  fcr = 0;
  putreg16(fcr, priv->base + RZV_SCIF_FCR_OFFSET);

  ftcr = ((uint16_t)1 << SCIF_FTCR_RFTC_SHIFT) |  /* RX trigger 1 byte */
         ((uint16_t)8 << SCIF_FTCR_TFTC_SHIFT) |  /* TX trigger 8 bytes */
         SCIF_FTCR_RTRGS | SCIF_FTCR_TTRGS;
  putreg16(ftcr, priv->base + RZV_SCIF_FTCR_OFFSET);

  /* Configure serial mode register */
  smr = 0;

  if (priv->bits == 7)
    {
      smr |= SCIF_SMR_CHR;
    }

  if (priv->parity == 1)
    {
      smr |= SCIF_SMR_PE | SCIF_SMR_PM;  /* Odd parity */
    }
  else if (priv->parity == 2)
    {
      smr |= SCIF_SMR_PE;  /* Even parity */
    }

  if (priv->stopbits2)
    {
      smr |= SCIF_SMR_STOP;
    }

  putreg16(smr, priv->base + RZV_SCIF_SMR_OFFSET);

  /* Set baud rate */
  rzv_scif_setbaud(priv);

  /* Clear all status flags */
  putreg16(0, priv->base + RZV_SCIF_FSR_OFFSET);
  putreg16(0, priv->base + RZV_SCIF_LSR_OFFSET);

  /* SCIFA has no MCE bit; HW flow control unsupported (see compile-time
   * #error at top of TU if CONFIG_SCIF0_*FLOWCONTROL is set).
   */

  /* Enable transmit and receive */
  scr = SCIF_SCR_TE | SCIF_SCR_RE;
  putreg16(scr, priv->base + RZV_SCIF_SCR_OFFSET);

  _info("SCIF%d: Setup complete (base=0x%08lx, baud=%lu)\n",
        priv->channel, priv->base, priv->baud);

  return OK;
}

/****************************************************************************
 * Name: rzv_scif_shutdown
 ****************************************************************************/

static void rzv_scif_shutdown(struct uart_dev_s *dev)
{
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;
  uint16_t scr;
  int timeout;

  /* Drain TX (bounded) before disabling: TEND is meaningful here because
   * TE was still enabled when shutdown was called. Worst case 16 bytes
   * @ 9600 baud ~= 17ms; cap at 50ms.
   */

  scr = getreg16(priv->base + RZV_SCIF_SCR_OFFSET);
  if (scr & SCIF_SCR_TE)
    {
      for (timeout = 5000; timeout > 0; timeout--)
        {
          if (getreg16(priv->base + RZV_SCIF_FSR_OFFSET) & SCIF_FSR_TEND)
            {
              break;
            }

          up_udelay(10);
        }
    }

  /* Disable TE/RE and all interrupt enables atomically. */

  putreg16(0, priv->base + RZV_SCIF_SCR_OFFSET);

  /* Ack residual flags so a subsequent reopen sees a clean state. */

  (void)getreg16(priv->base + RZV_SCIF_FSR_OFFSET);
  (void)getreg16(priv->base + RZV_SCIF_LSR_OFFSET);

  /* Disable peripheral clock to stop spurious interrupts and save power. */

  rzv_clock_disable(priv->clk_id);
}

/****************************************************************************
 * Name: rzv_scif_rxi_interrupt
 ****************************************************************************/

static int rzv_scif_rxi_interrupt(int irq, void *context, void *arg)
{
  struct uart_dev_s *dev = (struct uart_dev_s *)arg;
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;
  uint16_t fsr;
  uint16_t lsr;

  /* Read status registers. RZ/V2H ICU does not expose separate ERI/BRI
   * events for SCIF (only TEI/RXI/TXI), so error/break/overrun bits must
   * be polled from the RXI handler alongside RX data.
   */
  fsr = getreg16(priv->base + RZV_SCIF_FSR_OFFSET);
  lsr = getreg16(priv->base + RZV_SCIF_LSR_OFFSET);

  /* Handle receive */
  if (fsr & (SCIF_FSR_RDF | SCIF_FSR_DR))
    {
      uart_recvchars(dev);
      rzv_scif_fsr_clear(priv->base, SCIF_FSR_RDF | SCIF_FSR_DR);
    }

  /* Handle frame / parity / break errors (no separate ERI vector).
   *
   * FSR.PER (bit 2) and FSR.FER (bit 3) are READ-ONLY in CMSIS — HW
   * clears them only when the errored byte is dequeued from FRDR. Drain
   * one byte to flush the bad frame, then W0C-clear the write-clearable
   * error bits (ER, BRK).
   */
  if (fsr & (SCIF_FSR_ER | SCIF_FSR_BRK | SCIF_FSR_FER | SCIF_FSR_PER))
    {
      _info("SCIF%d: Frame error FSR=0x%04x\n", priv->channel, fsr);

      if (fsr & (SCIF_FSR_FER | SCIF_FSR_PER))
        {
          (void)getreg8(priv->base + RZV_SCIF_FRDR_OFFSET);
        }

      rzv_scif_fsr_clear(priv->base, SCIF_FSR_ER | SCIF_FSR_BRK);
    }

  /* Handle overrun - clear LSR.ORER only; do NOT reset RX FIFO */
  if (lsr & SCIF_LSR_ORER)
    {
      _info("SCIF%d: Overrun\n", priv->channel);
      rzv_scif_lsr_clear(priv->base, SCIF_LSR_ORER);
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_scif_txi_interrupt
 ****************************************************************************/

static int rzv_scif_txi_interrupt(int irq, void *context, void *arg)
{
  struct uart_dev_s *dev = (struct uart_dev_s *)arg;
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;
  uint16_t fsr;

  /* Read status register */
  fsr = getreg16(priv->base + RZV_SCIF_FSR_OFFSET);

  /* Handle transmit */
  if (fsr & SCIF_FSR_TDFE)
    {
      uart_xmitchars(dev);
      rzv_scif_fsr_clear(priv->base, SCIF_FSR_TDFE);
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_scif_tei_interrupt
 *
 * Description:
 *   Transmit-end interrupt. Fires after the last byte has fully clocked out
 *   of the TX shifter. Clear FSR.TEND (W0C) and disable TEIE so the
 *   interrupt does not re-assert until the next transmission completes.
 ****************************************************************************/

static int rzv_scif_tei_interrupt(int irq, void *context, void *arg)
{
  struct uart_dev_s *dev = (struct uart_dev_s *)arg;
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;
  uint16_t scr;

  rzv_scif_fsr_clear(priv->base, SCIF_FSR_TEND);

  scr = getreg16(priv->base + RZV_SCIF_SCR_OFFSET);
  scr &= ~SCIF_SCR_TEIE;
  putreg16(scr, priv->base + RZV_SCIF_SCR_OFFSET);

  return OK;
}

/****************************************************************************
 * Name: rzv_scif_attach
 ****************************************************************************/

static int rzv_scif_attach(struct uart_dev_s *dev)
{
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;

  /* Map ELC event 0x107 (UB1_RXI_EDGE_N) to RXI interrupt via ICU */
  priv->irq_rxi = rzv_icu_attach(RZV_ELC_UB1_RXI_EDGE_N,
                                  rzv_scif_rxi_interrupt, dev, true);
  if (priv->irq_rxi < 0)
    {
      _err("SCIF%d: Failed to attach RXI interrupt\n", priv->channel);
      return priv->irq_rxi;
    }

  /* Map ELC event 0x108 (UB1_TXI_EDGE_N) to TXI interrupt via ICU */
  priv->irq_txi = rzv_icu_attach(RZV_ELC_UB1_TXI_EDGE_N,
                                  rzv_scif_txi_interrupt, dev, true);
  if (priv->irq_txi < 0)
    {
      _err("SCIF%d: Failed to attach TXI interrupt\n", priv->channel);
      rzv_icu_detach(priv->irq_rxi);
      return priv->irq_txi;
    }

  /* Map ELC event 0x106 (UB1_TEI_N) to TEI (transmit end) interrupt.
   * Required for clean shutdown drain; failure here is non-fatal — the
   * driver still functions without TEND notification, just less precise
   * about TX completion.
   */
  priv->irq_tei = rzv_icu_attach(RZV_ELC_UB1_TEI_N,
                                  rzv_scif_tei_interrupt, dev, true);
  if (priv->irq_tei < 0)
    {
      _warn("SCIF%d: TEI attach failed (%d); continuing\n",
            priv->channel, priv->irq_tei);
      priv->irq_tei = 0;
    }

  _info("SCIF%d: Interrupts attached (RXI=%d, TXI=%d, TEI=%d)\n",
        priv->channel, priv->irq_rxi, priv->irq_txi, priv->irq_tei);

  return OK;
}

/****************************************************************************
 * Name: rzv_scif_detach
 ****************************************************************************/

static void rzv_scif_detach(struct uart_dev_s *dev)
{
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;

  /* Detach interrupts via ICU */
  if (priv->irq_rxi > 0)
    {
      rzv_icu_detach(priv->irq_rxi);
      priv->irq_rxi = 0;
    }

  if (priv->irq_txi > 0)
    {
      rzv_icu_detach(priv->irq_txi);
      priv->irq_txi = 0;
    }

  if (priv->irq_tei > 0)
    {
      rzv_icu_detach(priv->irq_tei);
      priv->irq_tei = 0;
    }

  _info("SCIF%d: Interrupts detached\n", priv->channel);
}



/****************************************************************************
 * Name: rzv_scif_ioctl
 ****************************************************************************/

static int rzv_scif_ioctl(struct file *filep, int cmd, unsigned long arg)
{
#ifdef CONFIG_SERIAL_TERMIOS
  struct inode *inode = filep->f_inode;
  struct uart_dev_s *dev = inode->i_private;
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;
#endif

  switch (cmd)
    {
#ifdef CONFIG_SERIAL_TERMIOS
    case TCGETS:
      {
        struct termios *termiosp = (struct termios *)arg;

        if (!termiosp)
          {
            return -EINVAL;
          }

        /* Return baud rate */
        cfsetispeed(termiosp, priv->baud);

        /* Return parity */
        termiosp->c_cflag = (priv->parity != 0) ? PARENB : 0;
        termiosp->c_cflag |= (priv->parity == 1) ? PARODD : 0;

        /* Return stop bits */
        termiosp->c_cflag |= (priv->stopbits2) ? CSTOPB : 0;

        /* Return data bits */
        switch (priv->bits)
          {
            case 5:
              termiosp->c_cflag |= CS5;
              break;

            case 6:
              termiosp->c_cflag |= CS6;
              break;

            case 7:
              termiosp->c_cflag |= CS7;
              break;

            default:
            case 8:
              termiosp->c_cflag |= CS8;
              break;
          }

        return OK;
      }

    case TCSETS:
      {
        struct termios *termiosp = (struct termios *)arg;

        if (!termiosp)
          {
            return -EINVAL;
          }

        /* Update baud rate */
        priv->baud = cfgetispeed(termiosp);

        /* Update parity */
        if (termiosp->c_cflag & PARENB)
          {
            priv->parity = (termiosp->c_cflag & PARODD) ? 1 : 2;
          }
        else
          {
            priv->parity = 0;
          }

        /* Update stop bits */
        priv->stopbits2 = (termiosp->c_cflag & CSTOPB) != 0;

        /* Update data bits */
        switch (termiosp->c_cflag & CSIZE)
          {
            case CS5:
              priv->bits = 5;
              break;

            case CS6:
              priv->bits = 6;
              break;

            case CS7:
              priv->bits = 7;
              break;

            default:
            case CS8:
              priv->bits = 8;
              break;
          }

        /* Reconfigure the UART */
        return rzv_scif_setup(dev);
      }
#endif

    default:
      return -ENOTTY;
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_scif_receive
 ****************************************************************************/

static int rzv_scif_receive(struct uart_dev_s *dev, unsigned int *status)
{
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;
  uint16_t fsr;
  uint8_t ch;

  /* Get status */
  fsr = getreg16(priv->base + RZV_SCIF_FSR_OFFSET);
  *status = fsr;

  /* Read character */
  ch = getreg8(priv->base + RZV_SCIF_FRDR_OFFSET);

  /* Clear DR/RDF via W0C-safe write */
  rzv_scif_fsr_clear(priv->base, SCIF_FSR_DR | SCIF_FSR_RDF);

  return ch;
}

/****************************************************************************
 * Name: rzv_scif_rxint
 ****************************************************************************/

static void rzv_scif_rxint(struct uart_dev_s *dev, bool enable)
{
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;
  uint16_t scr;
  irqstate_t flags;

  flags = enter_critical_section();

  scr = getreg16(priv->base + RZV_SCIF_SCR_OFFSET);

  if (enable)
    {
      scr |= SCIF_SCR_RIE;
    }
  else
    {
      scr &= ~SCIF_SCR_RIE;
    }

  putreg16(scr, priv->base + RZV_SCIF_SCR_OFFSET);

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: rzv_scif_rxavailable
 ****************************************************************************/

static bool rzv_scif_rxavailable(struct uart_dev_s *dev)
{
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;
  uint16_t fsr;

  fsr = getreg16(priv->base + RZV_SCIF_FSR_OFFSET);
  return (fsr & (SCIF_FSR_DR | SCIF_FSR_RDF)) != 0;
}

/****************************************************************************
 * Name: rzv_scif_send
 ****************************************************************************/

static void rzv_scif_send(struct uart_dev_s *dev, int ch)
{
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;

  /* Write character */
  putreg8((uint8_t)ch, priv->base + RZV_SCIF_FTDR_OFFSET);

  /* Clear TDFE via W0C-safe write */
  rzv_scif_fsr_clear(priv->base, SCIF_FSR_TDFE);
}

/****************************************************************************
 * Name: rzv_scif_txint
 ****************************************************************************/

static void rzv_scif_txint(struct uart_dev_s *dev, bool enable)
{
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;
  uint16_t scr;
  irqstate_t flags;

  flags = enter_critical_section();

  scr = getreg16(priv->base + RZV_SCIF_SCR_OFFSET);

  if (enable)
    {
      scr |= SCIF_SCR_TIE;
    }
  else
    {
      scr &= ~SCIF_SCR_TIE;
    }

  putreg16(scr, priv->base + RZV_SCIF_SCR_OFFSET);

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: rzv_scif_txready
 ****************************************************************************/

static bool rzv_scif_txready(struct uart_dev_s *dev)
{
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;
  uint16_t fsr;

  fsr = getreg16(priv->base + RZV_SCIF_FSR_OFFSET);
  return (fsr & SCIF_FSR_TDFE) != 0;
}

/****************************************************************************
 * Name: rzv_scif_txempty
 ****************************************************************************/

static bool rzv_scif_txempty(struct uart_dev_s *dev)
{
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;
  uint16_t fsr;

  fsr = getreg16(priv->base + RZV_SCIF_FSR_OFFSET);
  return (fsr & SCIF_FSR_TEND) != 0;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: arm_serialinit
 ****************************************************************************/

void arm_serialinit(void)
{
  /* Register console device */

#ifdef CONSOLE_DEV
  uart_register("/dev/console", &CONSOLE_DEV);
#endif

  /* Register ttyS devices */

#ifdef TTYS0_DEV
  uart_register("/dev/ttyS0", &TTYS0_DEV);
#endif
}

/****************************************************************************
 * Name: up_putc
 ****************************************************************************/

int up_putc(int ch)
{
#ifdef CONSOLE_DEV
  struct uart_dev_s *dev = &CONSOLE_DEV;
  uint16_t scr;
  irqstate_t flags;

  /* Disable UART interrupts */

  flags = enter_critical_section();
  scr = getreg16(((struct rzv_scif_s *)dev->priv)->base +
                 RZV_SCIF_SCR_OFFSET);
  putreg16(scr & ~(SCIF_SCR_TIE | SCIF_SCR_RIE),
           ((struct rzv_scif_s *)dev->priv)->base + RZV_SCIF_SCR_OFFSET);

  /* Check for LF */

  if (ch == '\n')
    {
      /* Add CR before LF */

      rzv_scif_send(dev, '\r');
    }

  /* Output the character */

  rzv_scif_send(dev, ch);

  /* Wait for the character to be sent before re-enabling interrupts */

  while (!rzv_scif_txready(dev))
    {
    }

  /* Restore UART interrupts */

  putreg16(scr, ((struct rzv_scif_s *)dev->priv)->base +
           RZV_SCIF_SCR_OFFSET);
  leave_critical_section(flags);
#endif

  return ch;
}

#endif /* CONFIG_RZV_UART_SCIF */
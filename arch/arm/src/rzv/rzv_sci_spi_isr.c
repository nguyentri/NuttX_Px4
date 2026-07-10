/****************************************************************************
 * arch/arm/src/rzv/rzv_sci_spi_isr.c
 *
 * TXI / RXI / TEI / ERI interrupt service routines for SCI-B SPI.
 *
 * ISR roles:
 *   TXI — TDR empty: feed next byte from txbuffer (or 0xFF for recv-only).
 *          When ntxwords hits 0: mask TIE, enable TEIE to catch end-of-frame.
 *   RXI — RDRF set: drain RDR into rxbuffer; when nrxwords hits 0 post done.
 *   TEI — TEND set: all bytes shifted out; mask TIE|TEIE, post completion.
 *   ERI — error: mask all IRQs first, log, clear, post error.
 * Licensed under Apache License 2.0 — see top-level NOTICE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>

#include "arm_internal.h"
#include "hardware/rzv_sci.h"
#include "rzv_sci_spi_internal.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Convenience accessors parameterised on private struct base address */

#define REG(p, off)         ((p)->base + (off))
#define CSR_VAL(p)          getreg32(REG(p, RZV_SCI_CSR_OFFSET))
#define CCR0_VAL(p)         getreg32(REG(p, RZV_SCI_CCR0_OFFSET))
#define CCR0_SET(p, v)      putreg32((v), REG(p, RZV_SCI_CCR0_OFFSET))
#define TDR_WR(p, v)        putreg32((uint32_t)(v) & 0xffu, \
                                     REG(p, RZV_SCI_TDR_OFFSET))
#define RDR_RD(p)           ((uint8_t)(getreg32(REG(p, RZV_SCI_RDR_OFFSET)) \
                                       & 0xffu))
#define CFCLR_WR(p, v)      putreg32((v), REG(p, RZV_SCI_CFCLR_OFFSET))
#define FFCLR_WR(p)         putreg32(SCI_FFCLR_DRC, REG(p, RZV_SCI_FFCLR_OFFSET))

/* Shorthand masks for CCR0 interrupt-enable bits */

#define CCR0_IRQ_ALL  (SCI_CCR0_TIE | SCI_CCR0_RIE | SCI_CCR0_TEIE)
#define CCR0_TRXEN    (SCI_CCR0_TE  | SCI_CCR0_RE)

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: spi_post_done
 *
 * Description:
 *   Called from ISR context to signal transfer completion or error.
 *   Masks all interrupt-enable bits (TIE|RIE|TEIE) before posting so the
 *   ISR cannot fire again after exchange() has returned.
 *
 ****************************************************************************/

static void spi_post_done(struct rzv_sci_spi_priv_s *priv,
                          enum rzv_sci_spi_state_e result)
{
  /* Mask all IRQs, leave TE|RE — exchange() disables TE|RE after sem_post */

  uint32_t ccr0 = CCR0_VAL(priv) & ~CCR0_IRQ_ALL;
  CCR0_SET(priv, ccr0);

  priv->state = result;
  nxsem_post(&priv->sem_isr);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_sci_spi_txi_isr
 *
 * Description:
 *   TXI: TDR empty — feed next TX byte.
 *   When ntxwords reaches 0: mask TIE, enable TEIE so TEI signals end-of-frame.
 *   (#6 fix: TIE was never cleared → perpetual interrupt storm at end of xfer)
 *
 ****************************************************************************/

int rzv_sci_spi_txi_isr(int irq, void *context, void *arg)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)arg;
  uint32_t ccr0;
  uint8_t  data;

  (void)irq;
  (void)context;

  if (priv == NULL)
    {
      /* Cannot touch registers without a valid instance — return. */

      return OK;
    }

  if (priv->state != SCI_SPI_STATE_BUSY)
    {
      /* Clear flag and return — spurious or after timeout recovery */

      CFCLR_WR(priv, SCI_CFCLR_TDREC);
      return OK;
    }

  /* Write bytes while TDR empty and we have data to send */

  while ((CSR_VAL(priv) & SCI_CSR_TDRE) && priv->ntxwords > 0)
    {
      data = priv->txbuffer ? *priv->txbuffer++ : 0xffu;
      priv->ntxwords--;
      TDR_WR(priv, data);
    }

  /* Acknowledge TXI flag (W1C) */

  CFCLR_WR(priv, SCI_CFCLR_TDREC);

  if (priv->ntxwords == 0)
    {
      /* All bytes written to TDR — disable TIE to stop TX-empty storm.
       * TEIE was already enabled by exchange() at transfer start so no
       * need to set it here; this mask-only RMW is safe.  (#6 fix, A9 fix)
       */

      ccr0  = CCR0_VAL(priv);
      ccr0 &= ~SCI_CCR0_TIE;
      CCR0_SET(priv, ccr0);
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_sci_spi_rxi_isr
 *
 * Description:
 *   RXI: RDRF set — drain RDR into rxbuffer.
 *   (#5 fix: ack CFCLR first, then loop to drain FIFO; old code read one
 *   byte then cleared — missed bytes when FIFO depth > 1)
 *   When nrxwords reaches 0: post done (TEI also posts; first one wins
 *   because state is checked in spi_post_done via the mask).
 *
 ****************************************************************************/

int rzv_sci_spi_rxi_isr(int irq, void *context, void *arg)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)arg;
  uint8_t data;

  (void)irq;
  (void)context;

  if (priv == NULL)
    {
      /* Cannot touch registers without a valid instance — return. */

      return OK;
    }

  if (priv->state != SCI_SPI_STATE_BUSY)
    {
      CFCLR_WR(priv, SCI_CFCLR_RDRFC);
      return OK;
    }

  /* Ack RDRF first (#5 fix: clear before read to minimise re-assert window) */

  CFCLR_WR(priv, SCI_CFCLR_RDRFC);

  /* Drain all available bytes from RDR / FIFO (#5 fix: loop).
   * The pre-loop CFCLR_WR above already acked RDRFC; per-byte ack
   * inside the loop is redundant W1C on a clear bit — removed (A23 fix).
   */

  while ((CSR_VAL(priv) & SCI_CSR_RDRF) && priv->nrxwords > 0)
    {
      data = RDR_RD(priv);
      if (priv->rxbuffer != NULL)
        {
          *priv->rxbuffer++ = data;
        }

      priv->nrxwords--;
    }

  /* If RX done and TX also done: signal completion */

  if (priv->nrxwords == 0 && priv->ntxwords == 0)
    {
      spi_post_done(priv, SCI_SPI_STATE_DONE);
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_sci_spi_tei_isr
 *
 * Description:
 *   TEI: TEND set — last byte has finished shifting out.
 *   (#19 fix: old handler only logged; never cleared TEND, never posted.
 *   TEIE kept firing → interrupt storm at end of every transfer.)
 *
 *   Order: clear TEND first, then mask TIE|TEIE, then post done.
 *
 ****************************************************************************/

int rzv_sci_spi_tei_isr(int irq, void *context, void *arg)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)arg;

  (void)irq;
  (void)context;

  if (priv == NULL)
    {
      return OK;
    }

  /* No CFCLR write needed here.
   * TEND clears automatically when a new byte is written to TDR; at
   * end-of-frame that never happens.  There is no SCI_CFCLR_TENDC bit
   * in the RSCI-B HW manual (TDREC clears TDRE, not TEND — writing it
   * here was incorrect and misleading).  The interrupt storm is prevented
   * solely by spi_post_done disabling TEIE in CCR0 below.  (A4 fix)
   */

  if (priv->state != SCI_SPI_STATE_BUSY)
    {
      return OK;
    }

  /* Drain any remainder bytes in RX FIFO before declaring done.
   * With RTRG=8, the last (nwords % 8) received bytes do not trigger RXI;
   * they sit in the FIFO until we drain them here.  (A9 fix)
   * CFCLR.RDRFC is acked inside the loop after each byte per RSCI-B manual
   * (FIFO-mode: one ack per FIFO pop).
   */

  while ((CSR_VAL(priv) & SCI_CSR_RDRF) && priv->nrxwords > 0)
    {
      uint8_t rxbyte = RDR_RD(priv);
      if (priv->rxbuffer != NULL)
        {
          *priv->rxbuffer++ = rxbyte;
        }

      priv->nrxwords--;
      CFCLR_WR(priv, SCI_CFCLR_RDRFC);
    }

  /* TEIE has been disabled by spi_post_done; TEND clears automatically on
   * next TDR write.  Post done — all bytes shifted out and RX remainder
   * drained above.  If RXI already posted (race), spi_post_done masks IRQs
   * so only the first posting matters.
   */

  spi_post_done(priv, SCI_SPI_STATE_DONE);
  return OK;
}

/****************************************************************************
 * Name: rzv_sci_spi_eri_isr
 *
 * Description:
 *   ERI: receive/frame/overrun error.
 *   (#17 fix: old handler left TIE|RIE|TEIE enabled → ISR continued firing
 *   into stale priv->txbuffer/rxbuffer after exchange() had returned.)
 *
 *   Order: mask ALL IRQs FIRST, then read diagnostics, clear, post error.
 *
 ****************************************************************************/

int rzv_sci_spi_eri_isr(int irq, void *context, void *arg)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)arg;
  uint32_t csr;

  (void)irq;
  (void)context;

  if (priv == NULL)
    {
      return OK;
    }

  /* (#17 fix) Mask TIE|RIE|TEIE immediately — stops any subsequent
   * TXI/RXI from touching priv->txbuffer/rxbuffer after we return.
   */

  {
    uint32_t ccr0 = CCR0_VAL(priv) & ~CCR0_IRQ_ALL;
    CCR0_SET(priv, ccr0);
  }

  /* Read error status for diagnostics */

  csr = CSR_VAL(priv);
  spierr("SCI%u: error CSR=0x%08" PRIx32 " (ORER=%u FER=%u PER=%u MFF=%u)\n",
         priv->channel, csr,
         (csr & SCI_CSR_ORER) ? 1u : 0u,
         (csr & SCI_CSR_FER)  ? 1u : 0u,
         (csr & SCI_CSR_PER)  ? 1u : 0u,
         (csr & SCI_CSR_MFF)  ? 1u : 0u);

  /* Clear error flags (W1C) */

  CFCLR_WR(priv, SCI_CFCLR_ORERC | SCI_CFCLR_FERC |
                 SCI_CFCLR_PERC  | SCI_CFCLR_MFFC);

  /* Post error only if a transfer was in progress */

  if (priv->state == SCI_SPI_STATE_BUSY)
    {
      priv->state = SCI_SPI_STATE_ERROR;
      nxsem_post(&priv->sem_isr);
    }

  return OK;
}

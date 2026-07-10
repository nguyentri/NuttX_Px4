/****************************************************************************
 * arch/arm/src/rzv/rzv_sci_i2c_isr.c
 *
 * TXI / TEI / RXI interrupt service routines for SCI-B Simple-I2C.
 * TXI / TEI / RXI interrupt service routines for SCI-B Simple-I2C.
 *
 * Interrupt roles (CPU-mode only, no DMAC):
 *   TXI  – NACK/ACK detected after address or data write; drive next byte.
 *           In CPU-mode, RX data is read here (not in RXI).
 *   TEI  – START/RESTART/STOP condition complete (IICSTIF flag)
 *   RXI  – Not used in CPU-mode (RIE never enabled). Kept for future DTC
 *           support. Handler is a no-op if fired spuriously.
 *
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
#include "rzv_sci_i2c_internal.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Register accessors parameterised on private struct base address */

#define REG(p, off)   ((p)->base + (off))

#define ICR_VAL(p)    getreg32(REG(p, RZV_SCI_ICR_OFFSET))
#define ICR_SET(p, v) putreg32((v), REG(p, RZV_SCI_ICR_OFFSET))
#define ISR_VAL(p)    getreg32(REG(p, RZV_SCI_ISR_OFFSET))
#define TDR_WR(p, v)  putreg32(SCI_I2C_TDR_UPPER_MASK | (uint8_t)(v), \
                               REG(p, RZV_SCI_TDR_OFFSET))
#define RDR_RD(p)     ((uint8_t)(getreg32(REG(p, RZV_SCI_RDR_OFFSET)) \
                                 & 0xffu))
#define CFCLR_WR(p, v) putreg32((v), REG(p, RZV_SCI_CFCLR_OFFSET))
#define ICFCLR_WR(p)   putreg32(SCI_ICFCLR_IICSTIFC, \
                                REG(p, RZV_SCI_ICFCLR_OFFSET))
#define CCR0_SET(p, v) putreg32((v), REG(p, RZV_SCI_CCR0_OFFSET))

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: sci_i2c_post_done
 *
 * Description:
 *   Mark transfer done and post the completion semaphore.
 *   Called from ISR context — must not sleep.
 *
 ****************************************************************************/

static void sci_i2c_post_done(struct rzv_sci_i2c_priv_s *priv, int result)
{
  priv->result = result;
  priv->state  = SCI_I2C_STATE_DONE;
  nxsem_post(&priv->sem_isr);
}

/****************************************************************************
 * Name: sci_i2c_issue_stop
 *
 * Description:
 *   Atomically set IICSTPREQ + SDAS=1 + SCLS=1 in ICR.
 *
 ****************************************************************************/

static void sci_i2c_issue_stop(struct rzv_sci_i2c_priv_s *priv)
{
  uint32_t icr = ICR_VAL(priv);
  ICR_SET(priv, SCI_I2C_REQ(icr, 1, 1, SCI_ICR_IICSTPREQ));
  priv->state = SCI_I2C_STATE_STOP;
}

/****************************************************************************
 * Name: sci_i2c_issue_restart
 *
 * Description:
 *   Atomically set IICRSTAREQ + SDAS=1 + SCLS=1.
 *   Uses STATE_RESTART_PENDING to disambiguate from STOP in TEI (#16 fix).
 *
 ****************************************************************************/

static void sci_i2c_issue_restart(struct rzv_sci_i2c_priv_s *priv)
{
  uint32_t icr = ICR_VAL(priv);
  ICR_SET(priv, SCI_I2C_REQ(icr, 1, 1, SCI_ICR_IICRSTAREQ));
  priv->state = SCI_I2C_STATE_RESTART_PENDING; /* #16 fix: not STATE_STOP */
}

/****************************************************************************
 * Name: sci_i2c_next_msg
 *
 * Description:
 *   Advance to the next message in the transfer array.
 *   Returns true if there is a next message, false if done.
 *
 *   Invariant (#13): HW serialises STIF→TXI, so TEI handler sets
 *   msg_idx/do_read before the subsequent TXI that processes data.
 *   This is documented, not enforced by SW barrier.
 *
 ****************************************************************************/

static bool sci_i2c_next_msg(struct rzv_sci_i2c_priv_s *priv)
{
  priv->msg_idx++;
  if (priv->msg_idx >= priv->msg_count)
    {
      return false;
    }

  priv->byte_idx      = 0;
  priv->do_read       = (priv->msgs[priv->msg_idx].flags & I2C_M_READ) != 0;
  priv->do_dummy_read = priv->do_read; /* Reset dummy-read flag for new msg */
  return true;
}

/****************************************************************************
 * Public Functions — ISR entry points
 ****************************************************************************/

/****************************************************************************
 * Name: sci_i2c_txi_isr
 *
 * Description:
 *   TXI interrupt: ACK/NACK received from slave after address or data write.
 *   In CPU-mode, RX bytes are read HERE from RDR.
 *   Drive the next byte or issue RESTART/STOP.
 *
 *   #1 fix: RX data read inside TXI (do_dummy_read pattern)
 *   #2 fix: RXDATA state handled here; first TXI after addr ACK skips RDR
 *   #4 fix: NACK during read = end-of-read; read last RDR then stop/restart
 *   dim 10: flag clear via CFCLR.TDREC, not legacy SSR
 *
 ****************************************************************************/

int sci_i2c_txi_isr(int irq, void *context, void *arg)
{
  struct rzv_sci_i2c_priv_s *priv = (struct rzv_sci_i2c_priv_s *)arg;

  /* Clear TDR empty flag (CFCLR.TDREC — write-1-clear) */

  CFCLR_WR(priv, SCI_CFCLR_TDREC);

  if (priv->state == SCI_I2C_STATE_DONE ||
      priv->state == SCI_I2C_STATE_IDLE)
    {
      return OK;
    }

  /* Check for NACK */

  if (ISR_VAL(priv) & SCI_ISR_IICACKR)
    {
      /* NACK from slave.
       * #4 fix: distinguish NACK-during-write (error) from
       * NACK-during-read (normal end-of-transaction per I2C spec):
       *   if (!read || do_dummy_read) → error
       *   else                        → read last RDR, then stop/restart
       */

      if (!priv->do_read || priv->do_dummy_read)
        {
          /* Write NACK or address NACK — abort */

          priv->result = -ENXIO;
          sci_i2c_issue_stop(priv);
        }
      else
        {
          /* Read NACK = master-sent NACK for last byte (IICACKT=1).
           * Read the final byte from RDR before issuing stop/restart.
           */

          struct i2c_msg_s *msg = &priv->msgs[priv->msg_idx];
          uint8_t data = RDR_RD(priv);
          if (priv->byte_idx < msg->length)
            {
              msg->buffer[priv->byte_idx++] = data;
            }

          bool more = sci_i2c_next_msg(priv);
          if (more)
            {
              sci_i2c_issue_restart(priv);
            }
          else
            {
              sci_i2c_issue_stop(priv);
            }
        }

      return OK;
    }

  /* Address phase — TEI ISR sent the address byte; TXI fires on addr ACK */

  if (priv->state == SCI_I2C_STATE_ADDR)
    {
      struct i2c_msg_s *msg = &priv->msgs[priv->msg_idx];
      if (priv->do_read)
        {
          /* For read: configure SDA/SCL as serial output, write 0xFF
           * to generate SCL and allow slave to drive first data bit.
           * do_dummy_read=true: this first TXI is the addr ACK — skip RDR.
           */

          irqstate_t flags = enter_critical_section();
          uint32_t icr = ICR_VAL(priv);
          ICR_SET(priv,
                  icr & ~(SCI_ICR_IICSDAS_MASK | SCI_ICR_IICSCLS_MASK));
          leave_critical_section(flags);

          priv->state = SCI_I2C_STATE_RXDATA;

          /* Set IICACKT=0 (ACK) unless only 1 byte to receive */

          irqstate_t f2 = enter_critical_section();
          uint32_t icr2 = ICR_VAL(priv);
          if (msg->length > 1u)
            {
              ICR_SET(priv, icr2 & ~SCI_ICR_IICACKT); /* ACK */
            }
          else
            {
              ICR_SET(priv, icr2 | SCI_ICR_IICACKT); /* NACK last byte */
            }

          leave_critical_section(f2);

          /* do_dummy_read is already true; set false after this TXI
           * so next TXI will read RDR (#1 fix: no separate RXI needed).
           */

          priv->do_dummy_read = false;
          TDR_WR(priv, 0xffu); /* Dummy write to clock out first byte */
        }
      else
        {
          /* Write first data byte */

          priv->state = SCI_I2C_STATE_TXDATA;
          if (priv->byte_idx < msg->length)
            {
              TDR_WR(priv, msg->buffer[priv->byte_idx++]);
            }
          else
            {
              /* Zero-length write — issue stop or restart */

              bool more = sci_i2c_next_msg(priv);
              if (more)
                {
                  sci_i2c_issue_restart(priv);
                }
              else
                {
                  sci_i2c_issue_stop(priv);
                }
            }
        }

      return OK;
    }

  /* TX data phase */

  if (priv->state == SCI_I2C_STATE_TXDATA)
    {
      struct i2c_msg_s *msg = &priv->msgs[priv->msg_idx];
      if (priv->byte_idx < msg->length)
        {
          TDR_WR(priv, msg->buffer[priv->byte_idx++]);
        }
      else
        {
          /* Message complete — check for more messages */

          bool more = sci_i2c_next_msg(priv);
          if (more)
            {
              sci_i2c_issue_restart(priv);
            }
          else
            {
              sci_i2c_issue_stop(priv);
            }
        }

      return OK;
    }

  /* RX data phase — CPU-mode: RDR read happens in TXI (#1 fix).
   * Each TXI after address ACK signals one byte has been clocked out by HW.
   */

  if (priv->state == SCI_I2C_STATE_RXDATA)
    {
      struct i2c_msg_s *msg = &priv->msgs[priv->msg_idx];

      /* do_dummy_read was cleared in ADDR phase above; all TXIs here are data */

      uint8_t data = RDR_RD(priv);
      if (priv->byte_idx < msg->length)
        {
          msg->buffer[priv->byte_idx++] = data;
        }

      if (priv->byte_idx >= msg->length)
        {
          /* All bytes received — NACK path handled above; this branch
           * should not normally be reached since NACK fires before here,
           * but handle gracefully.
           */

          bool more = sci_i2c_next_msg(priv);
          if (more)
            {
              sci_i2c_issue_restart(priv);
            }
          else
            {
              sci_i2c_issue_stop(priv);
            }
        }
      else
        {
          /* Enable NACK before last byte */

          irqstate_t flags = enter_critical_section();
          uint32_t icr = ICR_VAL(priv);
          if ((msg->length - priv->byte_idx) == 1u)
            {
              ICR_SET(priv, icr | SCI_ICR_IICACKT);  /* NACK last byte */
            }
          else
            {
              ICR_SET(priv, icr & ~SCI_ICR_IICACKT); /* ACK non-last */
            }

          leave_critical_section(flags);

          /* Write 0xFF to clock out next byte */

          TDR_WR(priv, 0xffu);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: sci_i2c_tei_isr
 *
 * Description:
 *   TEI interrupt: START/RESTART/STOP condition detected (IICSTIF).
 *   Send address byte after START; post completion after STOP.
 *   TEI handler for START/RESTART/STOP condition detection.
 *
 *   #7 fix: read ISR BEFORE clearing ICFCLR (prevents spurious-clear race).
 *   #16 fix: use STATE_RESTART_PENDING to identify RESTART vs STOP.
 *   dim 10: write ICFCLR.IICSTIFC to clear flag (not legacy SSR)
 *
 ****************************************************************************/

int sci_i2c_tei_isr(int irq, void *context, void *arg)
{
  struct rzv_sci_i2c_priv_s *priv = (struct rzv_sci_i2c_priv_s *)arg;

  /* #7 fix: read ISR FIRST, then clear STIF.
   * Old code cleared before checking — if spurious, flag was lost.
   */

  uint32_t isr = ISR_VAL(priv);

  if (!(isr & SCI_ISR_IICSTIF))
    {
      return OK; /* Spurious — do not clear the flag */
    }

  /* Clear STIF flag (write-1-clear) after confirming it was set */

  ICFCLR_WR(priv);

  if (priv->state == SCI_I2C_STATE_RESTART_PENDING)
    {
      /* RESTART complete — send address of next message (#16 fix).
       * Invariant (#13): HW serialises STIF→TXI, so msg_idx set by
       * sci_i2c_next_msg (called from prior TXI) is stable here.
       */

      struct i2c_msg_s *msg = &priv->msgs[priv->msg_idx];
      priv->do_read       = (msg->flags & I2C_M_READ) != 0;
      priv->do_dummy_read = priv->do_read;
      priv->state         = SCI_I2C_STATE_ADDR;

      /* Configure SDA/SCL as serial output then write address */

      irqstate_t flags = enter_critical_section();
      uint32_t icr = ICR_VAL(priv);
      ICR_SET(priv,
              icr & ~(SCI_ICR_IICSDAS_MASK | SCI_ICR_IICSCLS_MASK));
      leave_critical_section(flags);

      uint8_t addr_byte = (uint8_t)((msg->addr << 1) |
                                    (priv->do_read ?
                                     SCI_I2C_READ_BIT :
                                     SCI_I2C_WRITE_BIT));
      TDR_WR(priv, addr_byte);
      return OK;
    }

  if (priv->state == SCI_I2C_STATE_STOP)
    {
      /* STOP complete — transfer done */

      /* Drive SDA/SCL to high-Z */

      irqstate_t flags = enter_critical_section();
      uint32_t icr = ICR_VAL(priv);
      ICR_SET(priv, icr | SCI_ICR_IICSDAS_MASK | SCI_ICR_IICSCLS_MASK);
      leave_critical_section(flags);

      /* Disable TE/RE */

      CCR0_SET(priv, 0u);

      sci_i2c_post_done(priv, priv->result);
      return OK;
    }

  /* START condition complete — send first address byte */

  if (priv->state == SCI_I2C_STATE_ADDR)
    {
      struct i2c_msg_s *msg = &priv->msgs[priv->msg_idx];

      /* Configure SDA/SCL as serial output */

      irqstate_t flags = enter_critical_section();
      uint32_t icr = ICR_VAL(priv);
      ICR_SET(priv, icr & ~(SCI_ICR_IICSDAS_MASK | SCI_ICR_IICSCLS_MASK));
      leave_critical_section(flags);

      uint8_t addr_byte = (uint8_t)((msg->addr << 1) |
                                    (priv->do_read ?
                                     SCI_I2C_READ_BIT :
                                     SCI_I2C_WRITE_BIT));
      TDR_WR(priv, addr_byte);
    }

  return OK;
}

/****************************************************************************
 * Name: sci_i2c_rxi_isr
 *
 * Description:
 *   RXI interrupt handler.
 *
 *   NOTE: In CPU-mode, CCR0.RIE is never set so this ISR is effectively
 *   unreachable (#17). The ICU slot is kept allocated for future DTC/DMAC
 *   support (RIE would be enabled in that path).
 *   If fired spuriously, clear the flag and return.
 *
 *   #14 fix: dead duplicate branch (read vs write restart) removed.
 *
 ****************************************************************************/

int sci_i2c_rxi_isr(int irq, void *context, void *arg)
{
  struct rzv_sci_i2c_priv_s *priv = (struct rzv_sci_i2c_priv_s *)arg;

  /* Clear RDR full flag (CFCLR.RDRFC write-1-clear) */

  CFCLR_WR(priv, SCI_CFCLR_RDRFC);

  /* CPU-mode: RXI is not enabled; return immediately.
   * Data is read in txi_isr (CPU-mode pattern, #1, #17).
   */

  (void)priv;
  return OK;
}

/****************************************************************************
 * arch/arm/src/rzv/rzv_i2c.c
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

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <debug.h>
#include <assert.h>
#include <stddef.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/semaphore.h>
#include <nuttx/i2c/i2c_master.h>

#include "arm_internal.h"

#include "hardware/rzv_i2c.h"
#include "rzv_i2c.h"
#include "rzv_icu.h"
#include "rzv_clock.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define RIIC_TIMEOUT_MS       1000  /* Transfer timeout in milliseconds */

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* Transfer state */

enum rzv_i2c_state_e
{
  RIIC_STATE_IDLE = 0,
  RIIC_STATE_START,
  RIIC_STATE_ADDR_WRITE,
  RIIC_STATE_DATA_WRITE,
  RIIC_STATE_RESTART,
  RIIC_STATE_ADDR_READ,
  RIIC_STATE_DATA_READ,
  RIIC_STATE_STOP,
  RIIC_STATE_ERROR
};

/* Private data structure for RZV RIIC device */

struct rzv_i2c_priv_s
{
  struct i2c_master_s dev;        /* Must be first */
  int refs;                       /* Reference count */
  int port;                       /* Port number (0-3) */
  uint32_t base;                  /* Base address */
  uint32_t frequency;             /* Current bus frequency */

  /* IRQ slots */

  int irq_rxi;                    /* RX interrupt */
  int irq_txi;                    /* TX interrupt */
  int irq_tei;                    /* Transfer end interrupt */
  int irq_err;                    /* Error interrupt */
  int irq_stp;                    /* Stop interrupt */

  /* Module clock control */

  uint32_t mstp;                  /* Module stop control ID */

  /* Transfer state */

  sem_t sem_excl;                 /* Mutual exclusion semaphore */
  sem_t sem_isr;                  /* Wait for ISR semaphore */
  volatile enum rzv_i2c_state_e state;
  volatile int result;            /* Transfer result */

  /* Current message */

  struct i2c_msg_s *msgs;         /* Message array */
  int msgc;                       /* Number of messages */
  int msgid;                      /* Current message index */

  /* Current transfer */

  uint8_t *ptr;                   /* Buffer pointer */
  int dcnt;                       /* Data count */
  uint16_t flags;                 /* Message flags */
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int rzv_i2c_transfer(struct i2c_master_s *dev,
                            struct i2c_msg_s *msgs, int count);

#ifdef CONFIG_I2C_RESET
static int rzv_i2c_reset(struct i2c_master_s *dev);
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct i2c_ops_s rzv_i2c_ops =
{
  .transfer = rzv_i2c_transfer
#ifdef CONFIG_I2C_RESET
  , .reset  = rzv_i2c_reset
#endif
};

/* Device instances */

static struct rzv_i2c_priv_s g_riic_priv[RZV_RIIC_MAX_CHANNELS] =
{
  {
    .dev = { .ops = &rzv_i2c_ops },
    .refs = 0,
    .port = 0,
    .base = RZV_RIIC0_BASE,
    .irq_rxi = -1,
    .irq_txi = -1,
    .irq_tei = -1,
    .irq_err = -1
  },
  {
    .dev = { .ops = &rzv_i2c_ops },
    .refs = 0,
    .port = 1,
    .base = RZV_RIIC1_BASE,
    .irq_rxi = -1,
    .irq_txi = -1,
    .irq_tei = -1,
    .irq_err = -1,
    .irq_stp = -1,
    .mstp = RZV_CPG_CLK_I2C1
  },
  {
    .dev = { .ops = &rzv_i2c_ops },
    .refs = 0,
    .port = 2,
    .base = RZV_RIIC2_BASE,
    .irq_rxi = -1,
    .irq_txi = -1,
    .irq_tei = -1,
    .irq_err = -1,
    .irq_stp = -1,
    .mstp = RZV_CPG_CLK_I2C2
  },
  {
    .dev = { .ops = &rzv_i2c_ops },
    .refs = 0,
    .port = 3,
    .base = RZV_RIIC3_BASE,
    .irq_rxi = -1,
    .irq_txi = -1,
    .irq_tei = -1,
    .irq_err = -1,
    .irq_stp = -1,
    .mstp = RZV_CPG_CLK_I2C3
  }
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_i2c_getreg / rzv_i2c_putreg
 ****************************************************************************/

static inline uint8_t rzv_i2c_getreg(struct rzv_i2c_priv_s *priv,
                                      unsigned int offset)
{
  return getreg8(priv->base + offset);
}

static inline void rzv_i2c_putreg(struct rzv_i2c_priv_s *priv,
                                  unsigned int offset, uint8_t value)
{
  putreg8(value, priv->base + offset);
}

/****************************************************************************
 * Name: rzv_i2c_set_frequency
 ****************************************************************************/

static void rzv_i2c_set_frequency(struct rzv_i2c_priv_s *priv,
                                  uint32_t frequency)
{
  uint8_t cks, brh, brl;

  /* Select bit rate settings based on frequency */

  if (frequency <= 100000)
    {
      /* Standard mode: 100 kHz */

      cks = RIIC_CKS_100K;
      brh = RIIC_BRH_100K;
      brl = RIIC_BRL_100K;
    }
  else if (frequency <= 400000)
    {
      /* Fast mode: 400 kHz */

      cks = RIIC_CKS_400K;
      brh = RIIC_BRH_400K;
      brl = RIIC_BRL_400K;
    }
  else
    {
      /* Fast mode plus: 1 MHz */

      cks = RIIC_CKS_1M;
      brh = RIIC_BRH_1M;
      brl = RIIC_BRL_1M;
    }

  /* Configure ICMR1: Set clock source */

  uint8_t icmr1 = rzv_i2c_getreg(priv, RZV_RIIC_ICMR1_OFFSET);
  icmr1 &= ~RIIC_ICMR1_CKS_MASK;
  icmr1 |= (cks << RIIC_ICMR1_CKS_SHIFT);
  rzv_i2c_putreg(priv, RZV_RIIC_ICMR1_OFFSET, icmr1);

  /* Configure bit rate */

  rzv_i2c_putreg(priv, RZV_RIIC_ICBRH_OFFSET, brh);
  rzv_i2c_putreg(priv, RZV_RIIC_ICBRL_OFFSET, brl);

  priv->frequency = frequency;
}

/****************************************************************************
 * Name: rzv_i2c_sendstart
 ****************************************************************************/

static void rzv_i2c_sendstart(struct rzv_i2c_priv_s *priv)
{
  /* Set master transmit mode and issue start condition */

  uint8_t iccr2 = rzv_i2c_getreg(priv, RZV_RIIC_ICCR2_OFFSET);
  iccr2 |= RIIC_ICCR2_MST | RIIC_ICCR2_TRS | RIIC_ICCR2_ST;
  rzv_i2c_putreg(priv, RZV_RIIC_ICCR2_OFFSET, iccr2);
}

/****************************************************************************
 * Name: rzv_i2c_sendstop
 ****************************************************************************/

static void rzv_i2c_sendstop(struct rzv_i2c_priv_s *priv)
{
  /* Issue stop condition - MST and TRS will be cleared by hardware after
   * STOP completes. Do NOT clear them manually before STOP or it will
   * cause arbitration loss.
   */

  uint8_t iccr2 = rzv_i2c_getreg(priv, RZV_RIIC_ICCR2_OFFSET);
  iccr2 |= RIIC_ICCR2_SP;  /* Set STOP bit only */
  rzv_i2c_putreg(priv, RZV_RIIC_ICCR2_OFFSET, iccr2);
}

/****************************************************************************
 * Name: rzv_i2c_sendaddr
 ****************************************************************************/

static void rzv_i2c_sendaddr(struct rzv_i2c_priv_s *priv, uint16_t addr,
                             uint16_t flags)
{
  uint8_t data;

  /* Format address byte with R/W bit */

  if (flags & I2C_M_READ)
    {
      data = (addr << 1) | 0x01;  /* Read */
    }
  else
    {
      data = (addr << 1) | 0x00;  /* Write */
    }

  /* Send address */

  rzv_i2c_putreg(priv, RZV_RIIC_ICDRT_OFFSET, data);
}

/****************************************************************************
 * Name: rzv_i2c_irq_nextmsg
 ****************************************************************************/

static void rzv_i2c_irq_nextmsg(struct rzv_i2c_priv_s *priv)
{
  priv->msgid++;

  if (priv->msgid >= priv->msgc)
    {
      /* All messages complete - send stop */

      priv->state = RIIC_STATE_STOP;
      rzv_i2c_sendstop(priv);
    }
  else
    {
      /* Setup next message */

      struct i2c_msg_s *msg = &priv->msgs[priv->msgid];
      priv->ptr = msg->buffer;
      priv->dcnt = msg->length;
      priv->flags = msg->flags;

      if (msg->flags & I2C_M_NOSTART)
        {
          /* Continue without restart */

          if (msg->flags & I2C_M_READ)
            {
              priv->state = RIIC_STATE_DATA_READ;
            }
          else
            {
              priv->state = RIIC_STATE_DATA_WRITE;
            }
        }
      else
        {
          /* Issue restart - clear STOP bit first, then set RESTART and START */

          priv->state = RIIC_STATE_RESTART;
          uint8_t iccr2 = rzv_i2c_getreg(priv, RZV_RIIC_ICCR2_OFFSET);
          iccr2 &= ~RIIC_ICCR2_SP;  /* Clear any pending STOP */
          iccr2 |= RIIC_ICCR2_RS | RIIC_ICCR2_ST;  /* Set RESTART and START */
          rzv_i2c_putreg(priv, RZV_RIIC_ICCR2_OFFSET, iccr2);
        }
    }
}

/****************************************************************************
 * Name: rzv_i2c_rxi_interrupt
 ****************************************************************************/

static int rzv_i2c_rxi_interrupt(int irq, void *context, void *arg)
{
  struct rzv_i2c_priv_s *priv = (struct rzv_i2c_priv_s *)arg;

  /* Clear interrupt */

  rzv_icu_clear_irq(irq);

  /* Read data */

  if (priv->state == RIIC_STATE_DATA_READ && priv->dcnt > 0)
    {
      *priv->ptr++ = rzv_i2c_getreg(priv, RZV_RIIC_ICDRR_OFFSET);
      priv->dcnt--;

      /* Check if this is the penultimate byte - must set NACK before
       * the last byte is received (not at the last byte)
       */

      if (priv->dcnt == 2)
        {
          /* Set NACK before last byte */

          uint8_t icmr3 = rzv_i2c_getreg(priv, RZV_RIIC_ICMR3_OFFSET);
          icmr3 |= RIIC_ICMR3_ACKBT;  /* Send NACK */
          rzv_i2c_putreg(priv, RZV_RIIC_ICMR3_OFFSET, icmr3);
        }

      if (priv->dcnt == 0)
        {
          /* Message complete */

          rzv_i2c_irq_nextmsg(priv);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_i2c_txi_interrupt
 ****************************************************************************/

static int rzv_i2c_txi_interrupt(int irq, void *context, void *arg)
{
  struct rzv_i2c_priv_s *priv = (struct rzv_i2c_priv_s *)arg;

  /* Clear interrupt */

  rzv_icu_clear_irq(irq);

  switch (priv->state)
    {
      case RIIC_STATE_START:
      case RIIC_STATE_RESTART:
        /* Send address */

        rzv_i2c_sendaddr(priv, priv->msgs[priv->msgid].addr,
                        priv->msgs[priv->msgid].flags);

        if (priv->flags & I2C_M_READ)
          {
            priv->state = RIIC_STATE_ADDR_READ;
          }
        else
          {
            priv->state = RIIC_STATE_ADDR_WRITE;
          }
        break;

      case RIIC_STATE_ADDR_WRITE:
        /* Address sent, start data transfer */

        priv->state = RIIC_STATE_DATA_WRITE;
        /* Fall through */

      case RIIC_STATE_DATA_WRITE:
        if (priv->dcnt > 0)
          {
            /* Send next data byte */

            rzv_i2c_putreg(priv, RZV_RIIC_ICDRT_OFFSET, *priv->ptr++);
            priv->dcnt--;
          }

        if (priv->dcnt == 0)
          {
            /* Disable TXI, wait for TEI */

            uint8_t icier = rzv_i2c_getreg(priv, RZV_RIIC_ICIER_OFFSET);
            icier &= ~RIIC_ICIER_TIE;
            rzv_i2c_putreg(priv, RZV_RIIC_ICIER_OFFSET, icier);
          }
        break;

      case RIIC_STATE_ADDR_READ:
        /* Address sent for read, enable WAIT mode and switch to receive */

        /* Enable WAIT mode for synchronization */
        uint8_t icmr3 = rzv_i2c_getreg(priv, RZV_RIIC_ICMR3_OFFSET);
        icmr3 |= RIIC_ICMR3_WAIT;
        rzv_i2c_putreg(priv, RZV_RIIC_ICMR3_OFFSET, icmr3);

        /* Switch to receive mode */
        uint8_t iccr2 = rzv_i2c_getreg(priv, RZV_RIIC_ICCR2_OFFSET);
        iccr2 &= ~RIIC_ICCR2_TRS;  /* Receive mode */
        rzv_i2c_putreg(priv, RZV_RIIC_ICCR2_OFFSET, iccr2);

        priv->state = RIIC_STATE_DATA_READ;

        /* Disable TXI, enable RXI */

        uint8_t icier = rzv_i2c_getreg(priv, RZV_RIIC_ICIER_OFFSET);
        icier &= ~RIIC_ICIER_TIE;
        icier |= RIIC_ICIER_RIE;
        rzv_i2c_putreg(priv, RZV_RIIC_ICIER_OFFSET, icier);

        /* Dummy read to trigger first RXI */

        (void)rzv_i2c_getreg(priv, RZV_RIIC_ICDRR_OFFSET);
        break;

      default:
        break;
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_i2c_tei_interrupt
 ****************************************************************************/

static int rzv_i2c_tei_interrupt(int irq, void *context, void *arg)
{
  struct rzv_i2c_priv_s *priv = (struct rzv_i2c_priv_s *)arg;

  /* Clear interrupt */

  rzv_icu_clear_irq(irq);

  /* Transmit end - check for STOP condition or move to next message */

  if (priv->state == RIIC_STATE_DATA_WRITE)
    {
      rzv_i2c_irq_nextmsg(priv);
    }
  else if (priv->state == RIIC_STATE_STOP)
    {
      /* Check if STOP condition completed */
      uint8_t icsr2 = rzv_i2c_getreg(priv, RZV_RIIC_ICSR2_OFFSET);
      if (icsr2 & RIIC_ICSR2_STOP)
        {
          /* Clear STOP flag */
          rzv_i2c_putreg(priv, RZV_RIIC_ICSR2_OFFSET,
                         icsr2 & ~RIIC_ICSR2_STOP);

          priv->state = RIIC_STATE_IDLE;

          if (priv->result == 0)
            {
              priv->result = OK;
            }

          /* Wake up waiting thread */
          nxsem_post(&priv->sem_isr);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_i2c_err_interrupt
 ****************************************************************************/

static int rzv_i2c_err_interrupt(int irq, void *context, void *arg)
{
  struct rzv_i2c_priv_s *priv = (struct rzv_i2c_priv_s *)arg;

  /* Clear interrupt */

  rzv_icu_clear_irq(irq);

  /* Check error flags */

  uint8_t icsr2 = rzv_i2c_getreg(priv, RZV_RIIC_ICSR2_OFFSET);

  if (icsr2 & RIIC_ICSR2_NACKF)
    {
      /* NACK received */

      priv->result = -ENXIO;
      i2cerr("NACK detected\n");
    }
  else if (icsr2 & RIIC_ICSR2_AL)
    {
      /* Arbitration lost - try to recover bus */

      priv->result = -EAGAIN;
      i2cerr("Arbitration lost - attempting recovery\n");

      /* Reset and reinitialize peripheral */
      rzv_i2c_putreg(priv, RZV_RIIC_ICCR1_OFFSET, RIIC_ICCR1_IICRST);
      up_udelay(10);
      rzv_i2c_putreg(priv, RZV_RIIC_ICCR1_OFFSET, 0);
      up_udelay(10);
      rzv_i2c_putreg(priv, RZV_RIIC_ICCR1_OFFSET, RIIC_ICCR1_ICE);
    }
  else if (icsr2 & RIIC_ICSR2_TMOF)
    {
      /* Timeout */

      priv->result = -ETIMEDOUT;
      i2cerr("Timeout\n");
    }

  /* Clear error flags */

  rzv_i2c_putreg(priv, RZV_RIIC_ICSR2_OFFSET,
                icsr2 & ~(RIIC_ICSR2_NACKF | RIIC_ICSR2_AL | RIIC_ICSR2_TMOF));

  /* Abort transfer */

  priv->state = RIIC_STATE_ERROR;
  rzv_i2c_sendstop(priv);

  /* Wake up waiting thread */

  nxsem_post(&priv->sem_isr);

  return OK;
}

/****************************************************************************
 * Name: rzv_i2c_stp_interrupt
 ****************************************************************************/

static int rzv_i2c_stp_interrupt(int irq, void *context, void *arg)
{
  struct rzv_i2c_priv_s *priv = (struct rzv_i2c_priv_s *)arg;

  /* Clear interrupt */

  rzv_icu_clear_irq(irq);

  /* Stop condition detected - transfer complete */

  uint8_t icsr2 = rzv_i2c_getreg(priv, RZV_RIIC_ICSR2_OFFSET);
  rzv_i2c_putreg(priv, RZV_RIIC_ICSR2_OFFSET, icsr2 & ~RIIC_ICSR2_STOP);

  priv->state = RIIC_STATE_IDLE;

  if (priv->result == 0)
    {
      priv->result = OK;
    }

  /* Wake up waiting thread */

  nxsem_post(&priv->sem_isr);

  return OK;
}

/****************************************************************************
 * Name: rzv_i2c_init
 ****************************************************************************/

static int rzv_i2c_init(struct rzv_i2c_priv_s *priv)
{
  int ret;

  /* CRITICAL: Enable module clock before accessing peripheral registers */

  uint32_t domain = RZV_CPG_DOMAIN(priv->mstp);
  uint32_t bit = RZV_CPG_BIT(priv->mstp);
  RZV_MODULE_CLKON(domain, bit);

  /* Small delay for clock stabilization */

  up_udelay(10);

  /* Reset RIIC */

  rzv_i2c_putreg(priv, RZV_RIIC_ICCR1_OFFSET, RIIC_ICCR1_IICRST);
  rzv_i2c_putreg(priv, RZV_RIIC_ICCR1_OFFSET, 0);

  /* Enable RIIC */

  rzv_i2c_putreg(priv, RZV_RIIC_ICCR1_OFFSET, RIIC_ICCR1_ICE);

  /* Configure noise filter and mode */

  rzv_i2c_putreg(priv, RZV_RIIC_ICMR3_OFFSET,
                RIIC_ICMR3_NF_MASK | RIIC_ICMR3_WAIT);

  /* Enable necessary functions */

  rzv_i2c_putreg(priv, RZV_RIIC_ICFER_OFFSET,
                RIIC_ICFER_MALE | RIIC_ICFER_NACKE |
                RIIC_ICFER_NFE | RIIC_ICFER_SCLE);

  /* Set default frequency to 400 kHz */

  rzv_i2c_set_frequency(priv, 400000);

  /* Attach interrupts
   * Note: STOP condition is detected via ICSR2.STOP flag polling in
   * interrupt handlers, not as a separate interrupt event.
   */

  int events[4];
  xcpt_t handlers[4];
  int *irq_slots[4];

  /* Map event numbers based on channel */

  switch (priv->port)
    {
      case 0:
        events[0] = RZV_ELC_RIIC_CH0_IIC_ELCRDRFP;  /* RXI */
        events[1] = RZV_ELC_RIIC_CH0_IIC_ELCTDREP;  /* TXI */
        events[2] = RZV_ELC_RIIC_CH0_IIC_ELCTENDP;  /* TEI */
        events[3] = RZV_ELC_RIIC_CH0_IIC_ELCERRP;   /* ERR */
        break;

      case 1:
        events[0] = RZV_ELC_RIIC_CH1_IIC_ELCRDRFP;
        events[1] = RZV_ELC_RIIC_CH1_IIC_ELCTDREP;
        events[2] = RZV_ELC_RIIC_CH1_IIC_ELCTENDP;
        events[3] = RZV_ELC_RIIC_CH1_IIC_ELCERRP;
        break;

      case 2:
        events[0] = RZV_ELC_RIIC_CH2_IIC_ELCRDRFP;
        events[1] = RZV_ELC_RIIC_CH2_IIC_ELCTDREP;
        events[2] = RZV_ELC_RIIC_CH2_IIC_ELCTENDP;
        events[3] = RZV_ELC_RIIC_CH2_IIC_ELCERRP;
        break;

      case 3:
        events[0] = RZV_ELC_RIIC_CH3_IIC_ELCRDRFP;
        events[1] = RZV_ELC_RIIC_CH3_IIC_ELCTDREP;
        events[2] = RZV_ELC_RIIC_CH3_IIC_ELCTENDP;
        events[3] = RZV_ELC_RIIC_CH3_IIC_ELCERRP;
        break;

      default:
        return -EINVAL;
    }

  handlers[0] = rzv_i2c_rxi_interrupt;
  handlers[1] = rzv_i2c_txi_interrupt;
  handlers[2] = rzv_i2c_tei_interrupt;
  handlers[3] = rzv_i2c_err_interrupt;

  irq_slots[0] = &priv->irq_rxi;
  irq_slots[1] = &priv->irq_txi;
  irq_slots[2] = &priv->irq_tei;
  irq_slots[3] = &priv->irq_err;
  /* Note: irq_stp field exists for future use but STOP is currently
   * handled via ICSR2.STOP polling */

  /* Attach all interrupts */

  for (int i = 0; i < 4; i++)
    {
      ret = rzv_icu_attach(events[i], handlers[i], priv, true);
      if (ret < 0)
        {
          i2cerr("Failed to attach IRQ %d: %d\n", i, ret);

          /* Detach previously attached interrupts */

          for (int j = 0; j < i; j++)
            {
              if (*irq_slots[j] >= 0)
                {
                  rzv_icu_detach(*irq_slots[j]);
                  *irq_slots[j] = -1;
                }
            }

          return ret;
        }

      *irq_slots[i] = ret;
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_i2c_deinit
 ****************************************************************************/

static void rzv_i2c_deinit(struct rzv_i2c_priv_s *priv)
{
  /* Disable interrupts */

  rzv_i2c_putreg(priv, RZV_RIIC_ICIER_OFFSET, 0);

  /* Detach interrupts */

  if (priv->irq_err >= 0)
    {
      rzv_icu_detach(priv->irq_err);
      priv->irq_err = -1;
    }

  if (priv->irq_tei >= 0)
    {
      rzv_icu_detach(priv->irq_tei);
      priv->irq_tei = -1;
    }

  if (priv->irq_txi >= 0)
    {
      rzv_icu_detach(priv->irq_txi);
      priv->irq_txi = -1;
    }

  if (priv->irq_rxi >= 0)
    {
      rzv_icu_detach(priv->irq_rxi);
      priv->irq_rxi = -1;
    }

  /* Disable RIIC */

  rzv_i2c_putreg(priv, RZV_RIIC_ICCR1_OFFSET, 0);

  /* Disable module clock */

  uint32_t domain = RZV_CPG_DOMAIN(priv->mstp);
  uint32_t bit = RZV_CPG_BIT(priv->mstp);
  RZV_MODULE_CLKOFF(domain, bit);
}

/****************************************************************************
 * Name: rzv_i2c_transfer
 ****************************************************************************/

static int rzv_i2c_transfer(struct i2c_master_s *dev,
                            struct i2c_msg_s *msgs, int count)
{
  struct rzv_i2c_priv_s *priv = (struct rzv_i2c_priv_s *)dev;
  int ret;

  DEBUGASSERT(dev != NULL && msgs != NULL && count > 0);

  /* Get exclusive access */

  ret = nxsem_wait_uninterruptible(&priv->sem_excl);
  if (ret < 0)
    {
      return ret;
    }

  /* Setup transfer */

  priv->msgs = msgs;
  priv->msgc = count;
  priv->msgid = 0;
  priv->ptr = msgs[0].buffer;
  priv->dcnt = msgs[0].length;
  priv->flags = msgs[0].flags;
  priv->result = 0;
  priv->state = RIIC_STATE_START;

  /* Enable interrupts - note SPIE for STOP condition detection */

  uint8_t icier = RIIC_ICIER_TIE | RIIC_ICIER_TEIE |
                  RIIC_ICIER_NAKIE | RIIC_ICIER_ALIE |
                  RIIC_ICIER_SPIE | RIIC_ICIER_TMOIE;
  rzv_i2c_putreg(priv, RZV_RIIC_ICIER_OFFSET, icier);

  /* Start transfer */

  rzv_i2c_sendstart(priv);

  /* Wait for completion with timeout */

  struct timespec abstime;
  clock_gettime(CLOCK_REALTIME, &abstime);
  abstime.tv_sec += (RIIC_TIMEOUT_MS / 1000);
  abstime.tv_nsec += (RIIC_TIMEOUT_MS % 1000) * 1000000;

  if (abstime.tv_nsec >= 1000000000)
    {
      abstime.tv_sec++;
      abstime.tv_nsec -= 1000000000;
    }

  ret = nxsem_timedwait_uninterruptible(&priv->sem_isr, &abstime);

  if (ret < 0)
    {
      i2cerr("Transfer timeout or interrupted: %d\n", ret);

      /* Force stop */

      rzv_i2c_sendstop(priv);
      priv->state = RIIC_STATE_IDLE;
      ret = -ETIMEDOUT;
    }
  else
    {
      ret = priv->result;
    }

  /* Disable interrupts */

  rzv_i2c_putreg(priv, RZV_RIIC_ICIER_OFFSET, 0);

  /* Release exclusive access */

  nxsem_post(&priv->sem_excl);

  return ret;
}

/****************************************************************************
 * Name: rzv_i2c_reset
 ****************************************************************************/

#ifdef CONFIG_I2C_RESET
static int rzv_i2c_reset(struct i2c_master_s *dev)
{
  struct rzv_i2c_priv_s *priv = (struct rzv_i2c_priv_s *)dev;
  int ret;

  DEBUGASSERT(dev != NULL);

  /* Get exclusive access */

  ret = nxsem_wait_uninterruptible(&priv->sem_excl);
  if (ret < 0)
    {
      return ret;
    }

  /* Deinitialize and reinitialize */

  rzv_i2c_deinit(priv);
  ret = rzv_i2c_init(priv);

  /* Release exclusive access */

  nxsem_post(&priv->sem_excl);

  return ret;
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_i2c_initialize
 ****************************************************************************/

struct i2c_master_s *rzv_i2c_initialize(int port)
{
  struct rzv_i2c_priv_s *priv;
  int ret;

  /* Validate port */

  if (port < 0 || port >= RZV_RIIC_MAX_CHANNELS)
    {
      i2cerr("Invalid port: %d\n", port);
      return NULL;
    }

  priv = &g_riic_priv[port];

  /* Initialize on first use */

  if (priv->refs == 0)
    {
      /* Initialize semaphores */

      nxsem_init(&priv->sem_excl, 0, 1);
      nxsem_init(&priv->sem_isr, 0, 0);
      nxsem_set_protocol(&priv->sem_isr, SEM_PRIO_NONE);

      /* Initialize hardware */

      ret = rzv_i2c_init(priv);
      if (ret < 0)
        {
          i2cerr("Hardware init failed: %d\n", ret);
          nxsem_destroy(&priv->sem_excl);
          nxsem_destroy(&priv->sem_isr);
          return NULL;
        }

      priv->state = RIIC_STATE_IDLE;
    }

  priv->refs++;

  return &priv->dev;
}

/****************************************************************************
 * Name: rzv_i2c_uninitialize
 ****************************************************************************/

int rzv_i2c_uninitialize(struct i2c_master_s *dev)
{
  struct rzv_i2c_priv_s *priv = (struct rzv_i2c_priv_s *)dev;

  DEBUGASSERT(dev != NULL);

  if (priv->refs == 0)
    {
      return -EINVAL;
    }

  priv->refs--;

  if (priv->refs == 0)
    {
      /* Deinitialize hardware */

      rzv_i2c_deinit(priv);

      /* Destroy semaphores */

      nxsem_destroy(&priv->sem_excl);
      nxsem_destroy(&priv->sem_isr);
    }

  return OK;
}

/****************************************************************************
 * arch/arm/src/rzv/rzv_sci_i2c.c
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
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/irq.h>
#include <nuttx/clock.h>
#include <nuttx/semaphore.h>
#include <nuttx/i2c/i2c_master.h>

#include <arch/board/board.h>

#include "arm_internal.h"
#include "hardware/rzv_sci_i2c.h"
#include "rzv_sci_i2c.h"
#include "rzv_clock.h"

#ifdef CONFIG_RZV_SCI_I2C

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Default timeout for operations (in milliseconds) */

#define RZV_SCI_I2C_TIMEOUT_MS    1000

/* I2C state machine states */

#define RZV_SCI_I2C_STATE_IDLE    0
#define RZV_SCI_I2C_STATE_SEND    1
#define RZV_SCI_I2C_STATE_RECEIVE 2
#define RZV_SCI_I2C_STATE_ERROR   3

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* SCI I2C Device Structure */

struct rzv_sci_i2c_priv_s
{
  const struct i2c_ops_s *ops;     /* Standard I2C operations */
  uint32_t  base;                  /* SCI base address */
  uint32_t  frequency;             /* Current bus frequency */
  uint32_t  mstp;                  /* Module stop/clock ID */
  uint16_t  slave_addr;            /* Current slave address */
  uint8_t   channel;               /* SCI channel number (0-3) */
  uint8_t   state;                 /* Current transfer state */

  sem_t     mutex;                 /* Mutual exclusion */
  sem_t     wait;                  /* Wait for transfer completion */

  struct i2c_msg_s *msgs;          /* Message list */
  int       msg_count;             /* Number of messages */
  int       msg_idx;               /* Current message index */

  uint8_t  *buffer;                /* Current buffer pointer */
  int       buflen;                /* Remaining buffer length */
  int       xfrd;                  /* Bytes transferred */

  bool      restart;               /* Generate restart condition */
  int       error;                 /* Last error code */

  int       txi_irq;               /* TXI interrupt number */
  int       tei_irq;               /* TEI interrupt number */
  int       rxi_irq;               /* RXI interrupt number */
  int       eri_irq;               /* ERI interrupt number */
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* I2C device operations */

static int  rzv_sci_i2c_transfer(struct i2c_master_s *dev,
                                  struct i2c_msg_s *msgs, int count);
#ifdef CONFIG_I2C_RESET
static int  rzv_sci_i2c_reset(struct i2c_master_s *dev);
#endif

/* Interrupt handling */

static int  rzv_sci_i2c_txi_interrupt(int irq, void *context, void *arg);
static int  rzv_sci_i2c_tei_interrupt(int irq, void *context, void *arg);
static int  rzv_sci_i2c_rxi_interrupt(int irq, void *context, void *arg);
static int  rzv_sci_i2c_eri_interrupt(int irq, void *context, void *arg);

/* Hardware control */

static void rzv_sci_i2c_hw_initialize(struct rzv_sci_i2c_priv_s *priv);
static void rzv_sci_i2c_hw_enable(struct rzv_sci_i2c_priv_s *priv);
static void rzv_sci_i2c_hw_disable(struct rzv_sci_i2c_priv_s *priv);
static void rzv_sci_i2c_set_frequency(struct rzv_sci_i2c_priv_s *priv,
                                       uint32_t frequency);
static void rzv_sci_i2c_start_transfer(struct rzv_sci_i2c_priv_s *priv);
static void rzv_sci_i2c_stop_transfer(struct rzv_sci_i2c_priv_s *priv);

/* Register access helpers */

static inline uint8_t rzv_sci_i2c_getreg(struct rzv_sci_i2c_priv_s *priv,
                                         uint32_t offset);
static inline void rzv_sci_i2c_putreg(struct rzv_sci_i2c_priv_s *priv,
                                      uint32_t offset, uint8_t value);
static inline void rzv_sci_i2c_modifyreg(struct rzv_sci_i2c_priv_s *priv,
                                         uint32_t offset, uint8_t clrbits,
                                         uint8_t setbits);

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* I2C device operations */

static const struct i2c_ops_s g_sci_i2c_ops =
{
  .transfer = rzv_sci_i2c_transfer,
#ifdef CONFIG_I2C_RESET
  .reset    = rzv_sci_i2c_reset,
#endif
};

/* SCI I2C device structures */

static struct rzv_sci_i2c_priv_s g_sci_i2c_priv[RZV_SCI_I2C_MAX_CHANNELS] =
{
#ifdef CONFIG_RZV_SCI0_I2C
  {
    .ops     = &g_sci_i2c_ops,
    .base    = RZV_SCI0_BASE,
    .mstp    = RZV_CPG_CLK_SCI0,
    .channel = 0,
  },
#endif
#ifdef CONFIG_RZV_SCI1_I2C
  {
    .ops     = &g_sci_i2c_ops,
    .base    = RZV_SCI1_BASE,
    .mstp    = RZV_CPG_CLK_SCI1,
    .channel = 1,
  },
#endif
#ifdef CONFIG_RZV_SCI2_I2C
  {
    .ops     = &g_sci_i2c_ops,
    .base    = RZV_SCI2_BASE,
    .mstp    = RZV_CPG_CLK_SCI2,
    .channel = 2,
  },
#endif
#ifdef CONFIG_RZV_SCI3_I2C
  {
    .ops     = &g_sci_i2c_ops,
    .base    = RZV_SCI3_BASE,
    .mstp    = RZV_CPG_CLK_SCI3,
    .channel = 3,
  },
#endif
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_sci_i2c_getreg
 *
 * Description:
 *   Read an 8-bit register value
 *
 ****************************************************************************/

static inline uint8_t rzv_sci_i2c_getreg(struct rzv_sci_i2c_priv_s *priv,
                                         uint32_t offset)
{
  return getreg8(priv->base + offset);
}

/****************************************************************************
 * Name: rzv_sci_i2c_putreg
 *
 * Description:
 *   Write an 8-bit register value
 *
 ****************************************************************************/

static inline void rzv_sci_i2c_putreg(struct rzv_sci_i2c_priv_s *priv,
                                      uint32_t offset, uint8_t value)
{
  putreg8(value, priv->base + offset);
}

/****************************************************************************
 * Name: rzv_sci_i2c_modifyreg
 *
 * Description:
 *   Modify an 8-bit register value
 *
 ****************************************************************************/

static inline void rzv_sci_i2c_modifyreg(struct rzv_sci_i2c_priv_s *priv,
                                         uint32_t offset, uint8_t clrbits,
                                         uint8_t setbits)
{
  uint8_t regval = rzv_sci_i2c_getreg(priv, offset);
  regval &= ~clrbits;
  regval |= setbits;
  rzv_sci_i2c_putreg(priv, offset, regval);
}

/****************************************************************************
 * Name: rzv_sci_i2c_set_frequency
 *
 * Description:
 *   Set the I2C bus frequency
 *
 ****************************************************************************/

static void rzv_sci_i2c_set_frequency(struct rzv_sci_i2c_priv_s *priv,
                                       uint32_t frequency)
{
  uint32_t pclk = RZV_SCI_I2C_PCLK;
  uint32_t brr;
  uint8_t cks = 0;
  uint8_t smr;

  /* Calculate bit rate register value
   * BRR = (PCLK / (64 * 2^(2n-1) * frequency)) - 1
   * where n is CKS value (0-3)
   */

  /* Try different clock dividers */

  for (cks = 0; cks < 4; cks++)
    {
      uint32_t divisor = (64 << (2 * cks - 1));
      brr = (pclk / (divisor * frequency)) - 1;

      if (brr <= 255)
        {
          break;
        }
    }

  if (cks >= 4)
    {
      i2cerr("ERROR: Cannot achieve frequency %lu Hz\n", (unsigned long)frequency);
      cks = 3;
      brr = 255;
    }

  /* Disable transmit/receive before changing clock */

  rzv_sci_i2c_modifyreg(priv, RZV_SCI_SCR_OFFSET,
                        SCI_SCR_TE | SCI_SCR_RE, 0);

  /* Set clock source in SMR */

  smr = rzv_sci_i2c_getreg(priv, RZV_SCI_SMR_OFFSET);
  smr &= ~SCI_SMR_CKS_MASK;
  smr |= (cks << SCI_SMR_CKS_SHIFT);
  rzv_sci_i2c_putreg(priv, RZV_SCI_SMR_OFFSET, smr);

  /* Set bit rate */

  rzv_sci_i2c_putreg(priv, RZV_SCI_BRR_OFFSET, (uint8_t)brr);

  /* Wait for at least 1 bit time */

  up_udelay(1000000 / frequency);

  /* Re-enable transmit/receive */

  rzv_sci_i2c_modifyreg(priv, RZV_SCI_SCR_OFFSET, 0,
                        SCI_SCR_TE | SCI_SCR_RE);

  priv->frequency = frequency;

  i2cinfo("SCI%d I2C: Set frequency to %u Hz (CKS=%u, BRR=%u)\n",
          priv->channel, frequency, cks, brr);
}

/****************************************************************************
 * Name: rzv_sci_i2c_hw_initialize
 *
 * Description:
 *   Initialize SCI hardware for I2C mode
 *
 ****************************************************************************/

static void rzv_sci_i2c_hw_initialize(struct rzv_sci_i2c_priv_s *priv)
{
  i2cinfo("Initializing SCI%d for I2C mode\n", priv->channel);

  /* Enable SCI module clock */

  uint32_t domain = RZV_CPG_DOMAIN(priv->mstp);
  uint32_t bit = RZV_CPG_BIT(priv->mstp);
  RZV_MODULE_CLKON(domain, bit);

  /* Small delay for clock stabilization */

  up_udelay(10);

  /* Disable all interrupts and transmit/receive */

  rzv_sci_i2c_putreg(priv, RZV_SCI_SCR_OFFSET, 0);

  /* Clear status flags */

  rzv_sci_i2c_putreg(priv, RZV_SCI_SSR_OFFSET, 0);

  /* Configure for Simple I2C mode:
   * - SMR: Set communication mode
   * - SCMR: Configure smart card mode register
   * - SEMR: Set extended mode
   * - SIMR1: Enable Simple I2C mode with SDA delay
   */

  /* SMR: Clock select (will be set by frequency function) */

  rzv_sci_i2c_putreg(priv, RZV_SCI_SMR_OFFSET, 0);

  /* SCMR: Normal (not smart card mode) */

  rzv_sci_i2c_putreg(priv, RZV_SCI_SCMR_OFFSET, 0);

  /* SEMR: No noise filter, normal speed */

  rzv_sci_i2c_putreg(priv, RZV_SCI_SEMR_OFFSET, 0);

  /* SIMR1: Enable Simple I2C mode with default SDA delay (5 cycles) */

  rzv_sci_i2c_putreg(priv, RZV_SCI_SIMR1_OFFSET,
                     SCI_SIMR1_IICM | SCI_SIMR1_IICDL(5));

  /* SIMR2: Standard interrupt mode, no clock sync, send ACK */

  rzv_sci_i2c_putreg(priv, RZV_SCI_SIMR2_OFFSET, 0);

  /* SIMR3: Clear any pending condition requests */

  rzv_sci_i2c_putreg(priv, RZV_SCI_SIMR3_OFFSET, 0);

  /* Set default frequency (100 kHz) */

  rzv_sci_i2c_set_frequency(priv, RZV_SCI_I2C_FREQ_100KHZ);

  /* Enable transmit and receive */

  rzv_sci_i2c_modifyreg(priv, RZV_SCI_SCR_OFFSET, 0,
                        SCI_SCR_TE | SCI_SCR_RE);
}

/****************************************************************************
 * Name: rzv_sci_i2c_hw_enable
 *
 * Description:
 *   Enable SCI I2C interrupts
 *
 ****************************************************************************/

static void rzv_sci_i2c_hw_enable(struct rzv_sci_i2c_priv_s *priv)
{
  /* Enable transmit, receive, and error interrupts */

  rzv_sci_i2c_modifyreg(priv, RZV_SCI_SCR_OFFSET, 0,
                        SCI_SCR_TIE | SCI_SCR_RIE | SCI_SCR_TEIE);
}

/****************************************************************************
 * Name: rzv_sci_i2c_hw_disable
 *
 * Description:
 *   Disable SCI I2C interrupts
 *
 ****************************************************************************/

static void rzv_sci_i2c_hw_disable(struct rzv_sci_i2c_priv_s *priv)
{
  /* Disable all interrupts */

  rzv_sci_i2c_modifyreg(priv, RZV_SCI_SCR_OFFSET,
                        SCI_SCR_TIE | SCI_SCR_RIE | SCI_SCR_TEIE, 0);
}

/****************************************************************************
 * Name: rzv_sci_i2c_start_transfer
 *
 * Description:
 *   Start an I2C transfer with START or RESTART condition
 *
 ****************************************************************************/

static void rzv_sci_i2c_start_transfer(struct rzv_sci_i2c_priv_s *priv)
{
  uint8_t addr_byte;
  struct i2c_msg_s *msg = &priv->msgs[priv->msg_idx];

  i2cinfo("Starting transfer: addr=0x%02x, flags=0x%04x, len=%d\n",
          msg->addr, msg->flags, msg->length);

  /* Prepare address byte with R/W bit */

  addr_byte = (msg->addr << 1);
  if (msg->flags & I2C_M_READ)
    {
      addr_byte |= 0x01;  /* Read operation */
      priv->state = RZV_SCI_I2C_STATE_RECEIVE;
    }
  else
    {
      priv->state = RZV_SCI_I2C_STATE_SEND;
    }

  /* Generate START or RESTART condition */

  if (priv->restart)
    {
      /* Generate RESTART condition */

      rzv_sci_i2c_modifyreg(priv, RZV_SCI_SIMR3_OFFSET, 0,
                            SCI_SIMR3_IICRSTAREQ);
      priv->restart = false;
    }
  else
    {
      /* Generate START condition */

      rzv_sci_i2c_modifyreg(priv, RZV_SCI_SIMR3_OFFSET, 0,
                            SCI_SIMR3_IICSTAREQ);
    }

  /* Wait for START/RESTART condition to complete */

  while (!(rzv_sci_i2c_getreg(priv, RZV_SCI_SIMR3_OFFSET) &
           SCI_SIMR3_IICSTIF))
    {
      /* Busy wait - should be very short */
    }

  /* Clear the START/RESTART complete flag */

  rzv_sci_i2c_modifyreg(priv, RZV_SCI_SIMR3_OFFSET, SCI_SIMR3_IICSTIF, 0);

  /* Send address byte */

  rzv_sci_i2c_putreg(priv, RZV_SCI_TDR_OFFSET, addr_byte);

  /* Clear TDRE flag */

  rzv_sci_i2c_modifyreg(priv, RZV_SCI_SSR_OFFSET, SCI_SSR_TDRE, 0);
}

/****************************************************************************
 * Name: rzv_sci_i2c_stop_transfer
 *
 * Description:
 *   Generate STOP condition to end transfer
 *
 ****************************************************************************/

static void rzv_sci_i2c_stop_transfer(struct rzv_sci_i2c_priv_s *priv)
{
  i2cinfo("Generating STOP condition\n");

  /* Wait for transmit end */

  while (!(rzv_sci_i2c_getreg(priv, RZV_SCI_SSR_OFFSET) & SCI_SSR_TEND))
    {
      /* Wait */
    }

  /* Generate STOP condition */

  rzv_sci_i2c_modifyreg(priv, RZV_SCI_SIMR3_OFFSET, 0,
                        SCI_SIMR3_IICSTPREQ);

  /* Wait for STOP condition to complete */

  while (!(rzv_sci_i2c_getreg(priv, RZV_SCI_SIMR3_OFFSET) &
           SCI_SIMR3_IICSTIF))
    {
      /* Wait */
    }

  /* Clear the STOP complete flag */

  rzv_sci_i2c_modifyreg(priv, RZV_SCI_SIMR3_OFFSET, SCI_SIMR3_IICSTIF, 0);

  priv->state = RZV_SCI_I2C_STATE_IDLE;
}

/****************************************************************************
 * Name: rzv_sci_i2c_txi_interrupt
 *
 * Description:
 *   Transmit Data Empty (TXI) interrupt handler
 *
 ****************************************************************************/

static int rzv_sci_i2c_txi_interrupt(int irq, void *context, void *arg)
{
  struct rzv_sci_i2c_priv_s *priv = (struct rzv_sci_i2c_priv_s *)arg;
  struct i2c_msg_s *msg = &priv->msgs[priv->msg_idx];

  DEBUGASSERT(priv != NULL);

  /* Check for ACK/NACK from slave */

  if (rzv_sci_i2c_getreg(priv, RZV_SCI_SISR_OFFSET) & SCI_SISR_IICACKR)
    {
      /* NACK received - abort transfer */

      i2cerr("ERROR: NACK received\n");
      priv->error = -EIO;
      priv->state = RZV_SCI_I2C_STATE_ERROR;
      nxsem_post(&priv->wait);
      return OK;
    }

  if (priv->state == RZV_SCI_I2C_STATE_SEND && priv->buflen > 0)
    {
      /* Send next data byte */

      rzv_sci_i2c_putreg(priv, RZV_SCI_TDR_OFFSET, *priv->buffer++);
      priv->buflen--;
      priv->xfrd++;

      /* Clear TDRE flag */

      rzv_sci_i2c_modifyreg(priv, RZV_SCI_SSR_OFFSET, SCI_SSR_TDRE, 0);

      if (priv->buflen == 0)
        {
          /* Current message complete */

          priv->msg_idx++;

          if (priv->msg_idx < priv->msg_count)
            {
              /* More messages to process */

              msg = &priv->msgs[priv->msg_idx];
              priv->buffer = msg->buffer;
              priv->buflen = msg->length;
              priv->restart = true;

              /* Start next message */

              rzv_sci_i2c_start_transfer(priv);
            }
          else
            {
              /* All messages complete - signal completion */

              nxsem_post(&priv->wait);
            }
        }
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_sci_i2c_tei_interrupt
 *
 * Description:
 *   Transmit End (TEI) interrupt handler
 *
 ****************************************************************************/

static int rzv_sci_i2c_tei_interrupt(int irq, void *context, void *arg)
{
  struct rzv_sci_i2c_priv_s *priv = (struct rzv_sci_i2c_priv_s *)arg;

  DEBUGASSERT(priv != NULL);

  /* Transmit complete - handle based on current state */

  if (priv->state == RZV_SCI_I2C_STATE_SEND && priv->buflen == 0)
    {
      /* All data sent */

      if (priv->msg_idx >= priv->msg_count - 1)
        {
          /* No more messages - generate STOP */

          rzv_sci_i2c_stop_transfer(priv);
          nxsem_post(&priv->wait);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_sci_i2c_rxi_interrupt
 *
 * Description:
 *   Receive Data Full (RXI) interrupt handler
 *
 ****************************************************************************/

static int rzv_sci_i2c_rxi_interrupt(int irq, void *context, void *arg)
{
  struct rzv_sci_i2c_priv_s *priv = (struct rzv_sci_i2c_priv_s *)arg;
  struct i2c_msg_s *msg;

  DEBUGASSERT(priv != NULL);

  if (priv->state == RZV_SCI_I2C_STATE_RECEIVE && priv->buflen > 0)
    {
      /* Read received byte */

      *priv->buffer++ = rzv_sci_i2c_getreg(priv, RZV_SCI_RDR_OFFSET);
      priv->buflen--;
      priv->xfrd++;

      /* Clear RDRF flag */

      rzv_sci_i2c_modifyreg(priv, RZV_SCI_SSR_OFFSET, SCI_SSR_RDRF, 0);

      if (priv->buflen == 1)
        {
          /* Next byte is last - send NACK */

          rzv_sci_i2c_modifyreg(priv, RZV_SCI_SIMR2_OFFSET, 0,
                                SCI_SIMR2_IICACKT);
        }

      if (priv->buflen == 0)
        {
          /* Current message complete */

          priv->msg_idx++;

          if (priv->msg_idx < priv->msg_count)
            {
              /* More messages to process */

              msg = &priv->msgs[priv->msg_idx];
              priv->buffer = msg->buffer;
              priv->buflen = msg->length;
              priv->restart = true;

              /* Restore ACK mode */

              rzv_sci_i2c_modifyreg(priv, RZV_SCI_SIMR2_OFFSET,
                                    SCI_SIMR2_IICACKT, 0);

              /* Start next message */

              rzv_sci_i2c_start_transfer(priv);
            }
          else
            {
              /* All messages complete */

              rzv_sci_i2c_stop_transfer(priv);
              nxsem_post(&priv->wait);
            }
        }
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_sci_i2c_eri_interrupt
 *
 * Description:
 *   Error (ERI) interrupt handler
 *
 ****************************************************************************/

static int rzv_sci_i2c_eri_interrupt(int irq, void *context, void *arg)
{
  struct rzv_sci_i2c_priv_s *priv = (struct rzv_sci_i2c_priv_s *)arg;
  uint8_t ssr;

  DEBUGASSERT(priv != NULL);

  ssr = rzv_sci_i2c_getreg(priv, RZV_SCI_SSR_OFFSET);

  if (ssr & SCI_SSR_ORER)
    {
      i2cerr("ERROR: Overrun error\n");
      priv->error = -EIO;
    }

  if (ssr & SCI_SSR_FER)
    {
      i2cerr("ERROR: Framing error\n");
      priv->error = -EIO;
    }

  if (ssr & SCI_SSR_PER)
    {
      i2cerr("ERROR: Parity error\n");
      priv->error = -EIO;
    }

  /* Clear error flags */

  rzv_sci_i2c_modifyreg(priv, RZV_SCI_SSR_OFFSET,
                        SCI_SSR_ORER | SCI_SSR_FER | SCI_SSR_PER, 0);

  priv->state = RZV_SCI_I2C_STATE_ERROR;
  nxsem_post(&priv->wait);

  return OK;
}

/****************************************************************************
 * Name: rzv_sci_i2c_transfer
 *
 * Description:
 *   Generic I2C transfer method
 *
 ****************************************************************************/

static int rzv_sci_i2c_transfer(struct i2c_master_s *dev,
                                 struct i2c_msg_s *msgs, int count)
{
  struct rzv_sci_i2c_priv_s *priv = (struct rzv_sci_i2c_priv_s *)dev;
  struct timespec abstime;
  int ret = OK;

  DEBUGASSERT(dev != NULL && msgs != NULL && count > 0);

  i2cinfo("Transfer: count=%d\n", count);

  /* Get exclusive access */

  ret = nxsem_wait(&priv->mutex);
  if (ret < 0)
    {
      return ret;
    }

  /* Setup transfer */

  priv->msgs = msgs;
  priv->msg_count = count;
  priv->msg_idx = 0;
  priv->buffer = msgs[0].buffer;
  priv->buflen = msgs[0].length;
  priv->xfrd = 0;
  priv->error = 0;
  priv->restart = false;

  /* Set bus frequency if specified */

  if (msgs[0].frequency > 0 && msgs[0].frequency != priv->frequency)
    {
      rzv_sci_i2c_set_frequency(priv, msgs[0].frequency);
    }

  /* Enable interrupts */

  rzv_sci_i2c_hw_enable(priv);

  /* Start the transfer */

  rzv_sci_i2c_start_transfer(priv);

  /* Wait for transfer completion with timeout */

  clock_gettime(CLOCK_REALTIME, &abstime);
  abstime.tv_sec += RZV_SCI_I2C_TIMEOUT_MS / 1000;
  abstime.tv_nsec += (RZV_SCI_I2C_TIMEOUT_MS % 1000) * 1000000;

  if (abstime.tv_nsec >= 1000000000)
    {
      abstime.tv_sec++;
      abstime.tv_nsec -= 1000000000;
    }

  ret = nxsem_timedwait(&priv->wait, &abstime);

  /* Disable interrupts */

  rzv_sci_i2c_hw_disable(priv);

  if (ret < 0)
    {
      i2cerr("ERROR: Transfer timeout\n");
      ret = -ETIMEDOUT;
    }
  else if (priv->error != 0)
    {
      ret = priv->error;
    }
  else
    {
      ret = OK;
    }

  /* Release exclusive access */

  nxsem_post(&priv->mutex);

  return ret;
}

/****************************************************************************
 * Name: rzv_sci_i2c_reset
 *
 * Description:
 *   Reset the I2C controller
 *
 ****************************************************************************/

#ifdef CONFIG_I2C_RESET
static int rzv_sci_i2c_reset(struct i2c_master_s *dev)
{
  struct rzv_sci_i2c_priv_s *priv = (struct rzv_sci_i2c_priv_s *)dev;

  DEBUGASSERT(dev != NULL);

  i2cinfo("Resetting SCI%d I2C\n", priv->channel);

  /* Disable hardware */

  rzv_sci_i2c_hw_disable(priv);

  /* Reset state */

  priv->state = RZV_SCI_I2C_STATE_IDLE;
  priv->msg_idx = 0;
  priv->buflen = 0;
  priv->error = 0;

  /* Re-initialize hardware */

  rzv_sci_i2c_hw_initialize(priv);

  return OK;
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_sci_i2c_initialize
 *
 * Description:
 *   Initialize one SCI I2C port
 *
 ****************************************************************************/

struct i2c_master_s *rzv_sci_i2c_initialize(int port)
{
  struct rzv_sci_i2c_priv_s *priv;
  int ret;

  i2cinfo("Initializing SCI%d I2C\n", port);

  /* Validate port number */

  if (port < 0 || port >= RZV_SCI_I2C_MAX_CHANNELS)
    {
      i2cerr("ERROR: Invalid port %d\n", port);
      return NULL;
    }

  /* Get device structure */

  priv = &g_sci_i2c_priv[port];

  /* Initialize semaphores */

  nxsem_init(&priv->mutex, 0, 1);
  nxsem_init(&priv->wait, 0, 0);

  /* Initialize hardware */

  rzv_sci_i2c_hw_initialize(priv);

  /* Attach interrupts - Note: Actual IRQ numbers need to be configured
   * based on the system's interrupt controller configuration
   */

  /* For now, we'll use polling mode if interrupts aren't configured */

#ifdef CONFIG_RZV_SCI_I2C_INTERRUPTS
  ret = irq_attach(priv->txi_irq, rzv_sci_i2c_txi_interrupt, priv);
  if (ret < 0)
    {
      i2cerr("ERROR: Failed to attach TXI interrupt\n");
      goto errout;
    }

  ret = irq_attach(priv->tei_irq, rzv_sci_i2c_tei_interrupt, priv);
  if (ret < 0)
    {
      i2cerr("ERROR: Failed to attach TEI interrupt\n");
      goto errout;
    }

  ret = irq_attach(priv->rxi_irq, rzv_sci_i2c_rxi_interrupt, priv);
  if (ret < 0)
    {
      i2cerr("ERROR: Failed to attach RXI interrupt\n");
      goto errout;
    }

  ret = irq_attach(priv->eri_irq, rzv_sci_i2c_eri_interrupt, priv);
  if (ret < 0)
    {
      i2cerr("ERROR: Failed to attach ERI interrupt\n");
      goto errout;
    }

  /* Enable interrupts at NVIC */

  up_enable_irq(priv->txi_irq);
  up_enable_irq(priv->tei_irq);
  up_enable_irq(priv->rxi_irq);
  up_enable_irq(priv->eri_irq);
#endif

  i2cinfo("SCI%d I2C initialized successfully\n", port);

  return (struct i2c_master_s *)priv;

#ifdef CONFIG_RZV_SCI_I2C_INTERRUPTS
errout:
  nxsem_destroy(&priv->mutex);
  nxsem_destroy(&priv->wait);
  return NULL;
#endif
}

/****************************************************************************
 * Name: rzv_sci_i2c_uninitialize
 *
 * Description:
 *   Uninitialize an SCI I2C port
 *
 ****************************************************************************/

int rzv_sci_i2c_uninitialize(struct i2c_master_s *dev)
{
  struct rzv_sci_i2c_priv_s *priv = (struct rzv_sci_i2c_priv_s *)dev;

  DEBUGASSERT(dev != NULL);

  i2cinfo("Uninitializing SCI%d I2C\n", priv->channel);

  /* Disable hardware */

  rzv_sci_i2c_hw_disable(priv);

  /* Disable module clock */

  uint32_t domain = RZV_CPG_DOMAIN(priv->mstp);
  uint32_t bit = RZV_CPG_BIT(priv->mstp);
  RZV_MODULE_CLKOFF(domain, bit);

  /* Detach interrupts */

#ifdef CONFIG_RZV_SCI_I2C_INTERRUPTS
  up_disable_irq(priv->txi_irq);
  up_disable_irq(priv->tei_irq);
  up_disable_irq(priv->rxi_irq);
  up_disable_irq(priv->eri_irq);

  irq_detach(priv->txi_irq);
  irq_detach(priv->tei_irq);
  irq_detach(priv->rxi_irq);
  irq_detach(priv->eri_irq);
#endif

  /* Destroy semaphores */

  nxsem_destroy(&priv->mutex);
  nxsem_destroy(&priv->wait);

  return OK;
}

#endif /* CONFIG_RZV_SCI_I2C */

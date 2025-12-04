/****************************************************************************
 * arch/arm/src/ra8/ra_i2c.c
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
#include <errno.h>
#include <assert.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/mutex.h>
#include <nuttx/semaphore.h>
#include <nuttx/i2c/i2c_master.h>
#include <nuttx/i2c/i2c_slave.h>
#include <nuttx/power/pm.h>

#include <arch/board/board.h>

#include "arm_internal.h"
#include "chip.h"
#include "hardware/ra_memorymap.h"
#include "ra_icu.h"
#include "ra_mstp.h"
#include "ra_i2c.h"
#include "ra_clock.h"

#ifdef CONFIG_RA_DTC
#include "ra_dtc.h"
#include <nuttx/cache.h>
#endif

#ifdef CONFIG_RA_DMA
#include "ra_dmac.h"
#include <nuttx/cache.h>
#endif

#ifdef CONFIG_RA_I2C

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Debug ********************************************************************/

/* DTC timeout */
#define DTC_TIMEOUT_MS          1000

/* I2C timeout */
#define I2C_TIMEOUT_MS          1000

/* I2C State timeout */
#define I2C_STATE_TIMEOUT_US    100000

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* The device-private structure is declared in the public header
 * (arch/arm/src/ra8/ra_i2c.h). Do not duplicate that definition here.
 */

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* I2C operations */
static uint32_t ra_i2c_setfrequency(struct i2c_master_s *dev, uint32_t frequency);
static int ra_i2c_write(struct i2c_master_s *dev, const uint8_t *buffer, int buflen);
static int ra_i2c_read(struct i2c_master_s *dev, uint8_t *buffer, int buflen);
#ifdef CONFIG_I2C_WRITEREAD
static int ra_i2c_writeread(struct i2c_master_s *dev, const uint8_t *wbuffer,
                           int wbuflen, uint8_t *rbuffer, int rbuflen);
#endif
static int ra_i2c_transfer(struct i2c_master_s *dev, struct i2c_msg_s *msgs, int count);
#ifdef CONFIG_I2C_RESET
static int ra_i2c_reset(struct i2c_master_s *dev);
#endif

/* I2C helper functions */
static int ra_i2c_start(struct ra_i2c_priv_s *priv);
static int ra_i2c_stop(struct ra_i2c_priv_s *priv);
static int ra_i2c_sendaddr(struct ra_i2c_priv_s *priv, uint8_t addr, bool readmode);
static int ra_i2c_senddata(struct ra_i2c_priv_s *priv);
static int ra_i2c_readdata(struct ra_i2c_priv_s *priv);
static int ra_i2c_wait_event(struct ra_i2c_priv_s *priv, uint32_t timeout_us);

/* I2C interrupt service routines */
#ifndef CONFIG_I2C_POLLED
static int ra_i2c_isr_rxi(int irq, void *context, void *arg);
static int ra_i2c_isr_txi(int irq, void *context, void *arg);
static int ra_i2c_isr_tei(int irq, void *context, void *arg);
static int ra_i2c_isr_eri(int irq, void *context, void *arg);
#endif

/* I2C initialization */
static int ra_i2c_init(struct ra_i2c_priv_s *priv);
static int ra_i2c_deinit(struct ra_i2c_priv_s *priv);

/* DTC functions */
#ifdef CONFIG_RA_DTC
static bool g_i2c_dtc_initialized = false;
static int ra_i2c_dtc_setup(struct ra_i2c_priv_s *priv);
static int ra_i2c_dtc_start_rx(struct ra_i2c_priv_s *priv, uint8_t *buffer, uint32_t len);
static int ra_i2c_dtc_start_tx(struct ra_i2c_priv_s *priv, const uint8_t *buffer, uint32_t len);
static void ra_i2c_dtc_stop(struct ra_i2c_priv_s *priv);
static void ra_i2c_dtc_cleanup(struct ra_i2c_priv_s *priv);
#endif

/* DMA functions */
#ifdef CONFIG_RA_DMA
static int ra_i2c_dma_setup(struct ra_i2c_priv_s *priv);
static int ra_i2c_dma_start_rx(struct ra_i2c_priv_s *priv, uint8_t *buffer, uint32_t len);
static int ra_i2c_dma_start_tx(struct ra_i2c_priv_s *priv, const uint8_t *buffer, uint32_t len);
static void ra_i2c_dma_stop(struct ra_i2c_priv_s *priv);
static void ra_i2c_dma_tx_callback(void *handle, int event, void *arg);
static void ra_i2c_dma_rx_callback(void *handle, int event, void *arg);
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Modern NuttX I2C interface uses only transfer and reset operations */

static int ra_i2c_transfer_wrapper(FAR struct i2c_master_s *dev,
                                   FAR struct i2c_msg_s *msgs, int count)
{
#ifdef CONFIG_I2C_TRANSFER
  return ra_i2c_transfer(dev, msgs, count);
#else
  /* If the generic transfer API is not enabled, emulate it using the
   * per-operation helpers (write/read) for each message. This avoids
   * an undefined reference to ra_i2c_transfer when CONFIG_I2C_TRANSFER
   * is not set in the build configuration.
   */
  int ret = OK;
  int i;

  for (i = 0; i < count && ret == OK; i++)
    {
      if (msgs[i].flags & I2C_M_READ)
        {
          ret = ra_i2c_read(dev, msgs[i].buffer, msgs[i].length);
        }
      else
        {
          ret = ra_i2c_write(dev, msgs[i].buffer, msgs[i].length);
        }
    }

  return ret;
#endif
}

/* I2C Interface */
static const struct i2c_ops_s ra_i2c_ops =
{
  .transfer = ra_i2c_transfer_wrapper,
#ifdef CONFIG_I2C_RESET
  .reset    = ra_i2c_reset,
#endif
};

/* I2C device configuration */
#ifdef CONFIG_RA_I2C0
static const struct ra_i2c_config_s ra_i2c0_config =
{
  .base         = R_IIC_CH_BASE(0),
  .mstp         = RA_MSTP_IIC0,
  .clk_freq     = RA_PCLKB_FREQUENCY,
  .bus          = 0,
  .rxi_elc      = RA_ELC_IIC0_RXI,  /* EVENT_IIC0_RXI */
  .txi_elc      = RA_ELC_IIC0_TXI,  /* EVENT_IIC0_TXI */
  .tei_elc      = RA_ELC_IIC0_TEI,  /* EVENT_IIC0_TEI */
  .eri_elc      = RA_ELC_IIC0_ERI,  /* EVENT_IIC0_ERI */
};

static struct ra_i2c_priv_s ra_i2c0_priv =
{
  .ops          = &ra_i2c_ops,
  .config       = &ra_i2c0_config,
  .refs         = 0,
  .lock         = NXMUTEX_INITIALIZER,
#ifndef CONFIG_I2C_POLLED
  .sem_isr      = SEM_INITIALIZER(0),
#endif
  .state        = I2CSTATE_IDLE,
};
#endif

#ifdef CONFIG_RA_I2C1
static const struct ra_i2c_config_s ra_i2c1_config =
{
  .base         = R_IIC_CH_BASE(1),
  .mstp         = RA_MSTP_IIC1,
  .clk_freq     = RA_PCLKB_FREQUENCY,
  .bus          = 1,
  .rxi_elc      = RA_ELC_IIC1_RXI,  /* EVENT_IIC1_RXI */
  .txi_elc      = RA_ELC_IIC1_TXI,  /* EVENT_IIC1_TXI */
  .tei_elc      = RA_ELC_IIC1_TEI,  /* EVENT_IIC1_TEI */
  .eri_elc      = RA_ELC_IIC1_ERI,  /* EVENT_IIC1_ERI */
};

static struct ra_i2c_priv_s ra_i2c1_priv =
{
  .ops          = &ra_i2c_ops,
  .config       = &ra_i2c1_config,
  .refs         = 0,
  .lock         = NXMUTEX_INITIALIZER,
#ifndef CONFIG_I2C_POLLED
  .sem_isr      = SEM_INITIALIZER(0),
#endif
  .state        = I2CSTATE_IDLE,
};
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_i2c_getreg
 *
 * Description:
 *   Get a 8-bit register value by offset
 *
 ****************************************************************************/

static inline uint8_t ra_i2c_getreg(struct ra_i2c_priv_s *priv, uint8_t offset)
{
  return getreg8(priv->config->base + offset);
}

/****************************************************************************
 * Name: ra_i2c_putreg
 *
 * Description:
 *   Put a 8-bit register value by offset
 *
 ****************************************************************************/

static inline void ra_i2c_putreg(struct ra_i2c_priv_s *priv, uint8_t offset, uint8_t value)
{
  putreg8(value, priv->config->base + offset);
}

/****************************************************************************
 * Name: ra_i2c_modifyreg
 *
 * Description:
 *   Modify a 8-bit register value by offset
 *
 ****************************************************************************/

static inline void ra_i2c_modifyreg(struct ra_i2c_priv_s *priv, uint8_t offset,
                                   uint8_t clearbits, uint8_t setbits)
{
  modifyreg8(priv->config->base + offset, clearbits, setbits);
}

/****************************************************************************
 * Name: ra_i2c_setfrequency
 *
 * Description:
 *   Set the I2C frequency
 *
 ****************************************************************************/

static uint32_t ra_i2c_setfrequency(struct i2c_master_s *dev, uint32_t frequency)
{
  struct ra_i2c_priv_s *priv = (struct ra_i2c_priv_s *)dev;
  uint32_t pclkb_freq;
  uint32_t cks;
  uint32_t brh, brl;
  uint32_t actual_freq;

  DEBUGASSERT(priv != NULL);

  /* Check if frequency has changed */
  if (frequency == priv->frequency)
    {
      return priv->frequency;
    }

  /* Get PCLKB frequency */
  pclkb_freq = priv->config->clk_freq;

  /* Calculate clock source divider and bit rate registers
   * I2C frequency = PCLKB / (2^(CKS+1) * (BRH + BRL + 2))
   */

  /* Start with CKS = 0 (PCLKB/1) */
  for (cks = 0; cks <= 7; cks++)
    {
      uint32_t divisor = 1 << (cks + 1);
      uint32_t scl_freq = pclkb_freq / divisor;
      uint32_t total_count = scl_freq / frequency;

      if (total_count >= 4 && total_count <= 514) /* BRH + BRL + 2 can be 4 to 514 */
        {
          /* Split total count between BRH and BRL */
          uint32_t bit_rate = total_count - 2;
          brh = bit_rate / 2;
          brl = bit_rate - brh;

          /* Ensure BRH and BRL are in valid range (0-255) */
          if (brh <= 255 && brl <= 255)
            {
              break;
            }
        }
    }

  if (cks > 7)
    {
      /* Cannot achieve requested frequency, use minimum */
      cks = 7;
      brh = 255;
      brl = 255;
    }

  /* Calculate actual frequency */
  actual_freq = pclkb_freq / ((1 << (cks + 1)) * (brh + brl + 2));

  i2cinfo("I2C%d frequency: requested=%lu, actual=%lu, cks=%lu, brh=%lu, brl=%lu\n",
          priv->config->bus, frequency, actual_freq, cks, brh, brl);

  /* Disable I2C while changing settings */
  ra_i2c_modifyreg(priv, R_IIC_ICCR1_OFFSET, R_IIC_ICCR1_ICE, 0);

  /* Set clock source */
  ra_i2c_modifyreg(priv, R_IIC_ICMR1_OFFSET, R_IIC_ICMR1_CKS_MASK,
                  (cks << R_IIC_ICMR1_CKS_SHIFT) & R_IIC_ICMR1_CKS_MASK);

  /* Set bit rate registers */
  /* Mask bit-rate fields with their valid-bit masks */
  ra_i2c_putreg(priv, R_IIC_ICBRH_OFFSET, (uint8_t)(brh & R_IIC_ICBRH_BRH_MASK));
  ra_i2c_putreg(priv, R_IIC_ICBRL_OFFSET, (uint8_t)(brl & R_IIC_ICBRL_BRL_MASK));

  /* Re-enable I2C */
  ra_i2c_modifyreg(priv, R_IIC_ICCR1_OFFSET, 0, R_IIC_ICCR1_ICE);

  priv->frequency = actual_freq;
  return actual_freq;
}

/****************************************************************************
 * Name: ra_i2c_setaddress
 *
 * Description:
 *   Set the I2C slave address for a subsequent read/write
 *
 ****************************************************************************/

int ra_i2c_setaddress(struct i2c_master_s *dev, int addr, int nbits)
{
  struct ra_i2c_priv_s *priv = (struct ra_i2c_priv_s *)dev;

  DEBUGASSERT(priv != NULL);
  DEBUGASSERT(nbits == 7 || nbits == 10);

  priv->addr = addr;

  /* Note: The actual address will be sent when starting the transfer */
  return OK;
}

/****************************************************************************
 * Name: ra_i2c_write
 *
 * Description:
 *   Send a block of data on I2C using the previously selected I2C
 *   frequency and slave address.
 *
 ****************************************************************************/

static int ra_i2c_write(struct i2c_master_s *dev, const uint8_t *buffer, int buflen)
{
  struct ra_i2c_priv_s *priv = (struct ra_i2c_priv_s *)dev;
  struct i2c_msg_s msg;
  int ret;

  DEBUGASSERT(priv != NULL && buffer != NULL && buflen > 0);

  /* Setup message */
  msg.frequency = priv->frequency;
  msg.addr      = priv->addr;
  msg.flags     = 0;
  msg.buffer    = (uint8_t *)buffer;
  msg.length    = buflen;

  /* Perform the transfer */
  ret = ra_i2c_transfer(dev, &msg, 1);

  return ret;
}

/****************************************************************************
 * Name: ra_i2c_read
 *
 * Description:
 *   Receive a block of data from I2C using the previously selected I2C
 *   frequency and slave address.
 *
 ****************************************************************************/

static int ra_i2c_read(struct i2c_master_s *dev, uint8_t *buffer, int buflen)
{
  struct ra_i2c_priv_s *priv = (struct ra_i2c_priv_s *)dev;
  struct i2c_msg_s msg;
  int ret;

  DEBUGASSERT(priv != NULL && buffer != NULL && buflen > 0);

  /* Setup message */
  msg.frequency = priv->frequency;
  msg.addr      = priv->addr;
  msg.flags     = I2C_M_READ;
  msg.buffer    = buffer;
  msg.length    = buflen;

  /* Perform the transfer */
  ret = ra_i2c_transfer(dev, &msg, 1);

  return ret;
}

#ifdef CONFIG_I2C_WRITEREAD
/****************************************************************************
 * Name: ra_i2c_writeread
 *
 * Description:
 *   Write then read data
 *
 ****************************************************************************/

static int ra_i2c_writeread(struct i2c_master_s *dev, const uint8_t *wbuffer,
                           int wbuflen, uint8_t *rbuffer, int rbuflen)
{
  struct ra_i2c_priv_s *priv = (struct ra_i2c_priv_s *)dev;
  struct i2c_msg_s msgs[2];
  int ret;

  DEBUGASSERT(priv != NULL && wbuffer != NULL && wbuflen > 0 &&
              rbuffer != NULL && rbuflen > 0);

  /* Setup write message */
  msgs[0].frequency = priv->frequency;
  msgs[0].addr      = priv->addr;
  msgs[0].flags     = 0;
  msgs[0].buffer    = (uint8_t *)wbuffer;
  msgs[0].length    = wbuflen;

  /* Setup read message */
  msgs[1].frequency = priv->frequency;
  msgs[1].addr      = priv->addr;
  msgs[1].flags     = I2C_M_READ;
  msgs[1].buffer    = rbuffer;
  msgs[1].length    = rbuflen;

  /* Perform the transfer */
  ret = ra_i2c_transfer(dev, msgs, 2);

  return ret;
}
#endif

/****************************************************************************
 * Name: ra_i2c_start
 *
 * Description:
 *   Generate I2C start condition
 *
 ****************************************************************************/

static int ra_i2c_start(struct ra_i2c_priv_s *priv)
{
  uint32_t timeout = I2C_STATE_TIMEOUT_US;

  /* Wait for bus to be free */
  while ((ra_i2c_getreg(priv, R_IIC_ICCR2_OFFSET) & R_IIC_ICCR2_BBSY) && timeout--)
    {
      up_udelay(1);
    }

  if (timeout == 0)
    {
      i2cerr("I2C%d: Bus busy timeout\n", priv->config->bus);
      return -EBUSY;
    }

  /* Set master mode and transmit mode */
  ra_i2c_modifyreg(priv, R_IIC_ICCR2_OFFSET, 0, R_IIC_ICCR2_MST | R_IIC_ICCR2_TRS);

  /* Generate start condition */
  ra_i2c_modifyreg(priv, R_IIC_ICCR2_OFFSET, 0, R_IIC_ICCR2_ST);

  priv->state = I2CSTATE_START;

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_stop
 *
 * Description:
 *   Generate I2C stop condition
 *
 ****************************************************************************/

static int ra_i2c_stop(struct ra_i2c_priv_s *priv)
{
  uint32_t timeout = I2C_STATE_TIMEOUT_US;

  /* Generate stop condition */
  ra_i2c_modifyreg(priv, R_IIC_ICCR2_OFFSET, 0, R_IIC_ICCR2_SP);

  /* Wait for stop condition to complete */
  while ((ra_i2c_getreg(priv, R_IIC_ICSR2_OFFSET) & R_IIC_ICSR2_STOP) == 0 && timeout--)
    {
      up_udelay(1);
    }

  /* Clear stop flag */
  ra_i2c_modifyreg(priv, R_IIC_ICSR2_OFFSET, R_IIC_ICSR2_STOP, 0);

  /* Clear master mode */
  ra_i2c_modifyreg(priv, R_IIC_ICCR2_OFFSET, R_IIC_ICCR2_MST, 0);

  priv->state = I2CSTATE_IDLE;

  return (timeout > 0) ? OK : -ETIMEDOUT;
}

/****************************************************************************
 * Name: ra_i2c_sendaddr
 *
 * Description:
 *   Send I2C address
 *
 ****************************************************************************/

static int ra_i2c_sendaddr(struct ra_i2c_priv_s *priv, uint8_t addr, bool readmode)
{
  uint8_t addr_byte;

  /* Prepare address byte */
  addr_byte = (addr << 1) | (readmode ? 1 : 0);

  /* Send address */
  ra_i2c_putreg(priv, R_IIC_ICDRT_OFFSET, addr_byte);

  priv->state = readmode ? I2CSTATE_ADDR_READ : I2CSTATE_ADDR_WRITE;

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_senddata
 *
 * Description:
 *   Send data byte
 *
 ****************************************************************************/

static int ra_i2c_senddata(struct ra_i2c_priv_s *priv)
{
  if (priv->dcnt > 0)
    {
      /* Send data byte */
  ra_i2c_putreg(priv, R_IIC_ICDRT_OFFSET, *priv->ptr++);
      priv->dcnt--;
      priv->state = I2CSTATE_WRITE;
    }

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_readdata
 *
 * Description:
 *   Read data byte
 *
 ****************************************************************************/

static int ra_i2c_readdata(struct ra_i2c_priv_s *priv)
{
  if (priv->dcnt > 0)
    {
      /* Read data byte */
  *priv->ptr++ = ra_i2c_getreg(priv, R_IIC_ICDRR_OFFSET);
      priv->dcnt--;
      priv->state = I2CSTATE_READ;

      /* If this is the last byte, send NACK */
      if (priv->dcnt == 1)
        {
          ra_i2c_modifyreg(priv, R_IIC_ICMR3_OFFSET, 0, R_IIC_ICMR3_ACKBT);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_wait_event
 *
 * Description:
 *   Wait for I2C event
 *
 ****************************************************************************/

static int ra_i2c_wait_event(struct ra_i2c_priv_s *priv, uint32_t timeout_us)
{
#ifdef CONFIG_I2C_POLLED
  uint32_t timeout = timeout_us;
  uint8_t sr2;

  /* Poll for events */
  while (timeout--)
    {
      sr2 = ra_i2c_getreg(priv, R_IIC_ICSR2_OFFSET);

      /* Check for errors */
  if (sr2 & (R_IIC_ICSR2_AL | R_IIC_ICSR2_TMOF))
        {
          priv->status = sr2;
          return -EIO;
        }

      /* Check for NACK */
  if (sr2 & R_IIC_ICSR2_NACKF)
        {
          priv->status = sr2;
          return -ENXIO;
        }

      /* Check for events based on current state */
      switch (priv->state)
        {
          case I2CSTATE_START:
            if (sr2 & R_IIC_ICSR2_START)
              {
                ra_i2c_modifyreg(priv, R_IIC_ICSR2_OFFSET, R_IIC_ICSR2_START, 0);
                return OK;
              }
            break;

          case I2CSTATE_ADDR_WRITE:
          case I2CSTATE_WRITE:
            if (sr2 & R_IIC_ICSR2_TDRE)
              {
                return OK;
              }
            break;

          case I2CSTATE_ADDR_READ:
            if (sr2 & R_IIC_ICSR2_TDRE)
              {
                /* Switch to receive mode */
                ra_i2c_modifyreg(priv, R_IIC_ICCR2_OFFSET, R_IIC_ICCR2_TRS, 0);
                /* Dummy read to start reception */
                (void)ra_i2c_getreg(priv, R_IIC_ICDRR_OFFSET);
                return OK;
              }
            break;

          case I2CSTATE_READ:
            if (sr2 & R_IIC_ICSR2_RDRF)
              {
                return OK;
              }
            break;

          case I2CSTATE_STOP:
            if (sr2 & R_IIC_ICSR2_STOP)
              {
                ra_i2c_modifyreg(priv, R_IIC_ICSR2_OFFSET, R_IIC_ICSR2_STOP, 0);
                return OK;
              }
            break;

          default:
            break;
        }

      up_udelay(1);
    }

  return -ETIMEDOUT;
#else
  /* Wait for interrupt */
  return nxsem_tickwait_uninterruptible(&priv->sem_isr, USEC2TICK(timeout_us));
#endif
}

/****************************************************************************
 * Name: ra_i2c_transfer
 *
 * Description:
 *   Generic I2C transfer function with optional DTC/DMA support
 *
 ****************************************************************************/

static int ra_i2c_transfer(struct i2c_master_s *dev, struct i2c_msg_s *msgs, int count)
{
  struct ra_i2c_priv_s *priv = (struct ra_i2c_priv_s *)dev;
  int ret = OK;
  int i;
#if defined(CONFIG_RA_DTC) || defined(CONFIG_RA_DMA)
  bool use_dma_transfer = false;
#endif

  DEBUGASSERT(priv != NULL && msgs != NULL && count > 0);

  /* Get exclusive access to the I2C bus */

  ret = nxmutex_lock(&priv->lock);
  if (ret < 0)
    {
      return ret;
    }

  /* Set the frequency if it has changed */

  if (msgs[0].frequency != priv->frequency)
    {
      ra_i2c_setfrequency(dev, msgs[0].frequency);
    }

  /* Process each message */

  for (i = 0; i < count && ret == OK; i++)
    {
      priv->msgs = &msgs[i];
      priv->msgc = 1;
      priv->ptr = msgs[i].buffer;
      priv->dcnt = msgs[i].length;
      priv->flags = msgs[i].flags;
      priv->addr = msgs[i].addr;

#if defined(CONFIG_RA_DTC) || defined(CONFIG_RA_DMA)
      /* Determine if we should use DTC/DMA for this transfer
       * Use DMA for larger transfers to reduce CPU overhead
       */

      use_dma_transfer = false;

#ifdef CONFIG_RA_DMA
      if (priv->use_dma && msgs[i].length >= RA_I2C_DMA_THRESHOLD)
        {
          use_dma_transfer = true;
        }
#endif
#ifdef CONFIG_RA_DTC
      if (!use_dma_transfer && priv->use_dtc &&
          msgs[i].length >= RA_I2C_DTC_THRESHOLD)
        {
          use_dma_transfer = true;
        }
#endif
#endif /* CONFIG_RA_DTC || CONFIG_RA_DMA */

      /* Generate start condition (or repeated start) */

      ret = ra_i2c_start(priv);
      if (ret != OK)
        {
          break;
        }

      /* Wait for start condition */

      ret = ra_i2c_wait_event(priv, I2C_STATE_TIMEOUT_US);
      if (ret != OK)
        {
          break;
        }

      /* Send address */

      ret = ra_i2c_sendaddr(priv, msgs[i].addr,
                            (msgs[i].flags & I2C_M_READ) != 0);
      if (ret != OK)
        {
          break;
        }

      /* Wait for address ACK */

      ret = ra_i2c_wait_event(priv, I2C_STATE_TIMEOUT_US);
      if (ret != OK)
        {
          break;
        }

      /* Transfer data */

      if (msgs[i].flags & I2C_M_READ)
        {
          /* Reading - switch to receive mode after address */

          ra_i2c_modifyreg(priv, R_IIC_ICCR2_OFFSET, R_IIC_ICCR2_TRS, 0);

          /* Dummy read to start reception */

          (void)ra_i2c_getreg(priv, R_IIC_ICDRR_OFFSET);

#if defined(CONFIG_RA_DMA) || defined(CONFIG_RA_DTC)
          if (use_dma_transfer)
            {
              /* Use DMA/DTC for bulk read */

#ifdef CONFIG_RA_DMA
              if (priv->use_dma)
                {
                  ret = ra_i2c_dma_start_rx(priv, msgs[i].buffer,
                                            msgs[i].length);
                  if (ret == OK)
                    {
                      /* Wait for DMA completion */

                      ret = ra_i2c_wait_event(priv,
                              I2C_STATE_TIMEOUT_US * msgs[i].length);
                      ra_i2c_dma_stop(priv);

                      /* Invalidate cache for RX buffer */

                      up_invalidate_dcache((uintptr_t)msgs[i].buffer,
                          (uintptr_t)msgs[i].buffer + msgs[i].length);

                      priv->dcnt = 0;
                    }
                }
              else
#endif
#ifdef CONFIG_RA_DTC
              if (priv->use_dtc)
                {
                  ret = ra_i2c_dtc_start_rx(priv, msgs[i].buffer,
                                            msgs[i].length);
                  if (ret == OK)
                    {
                      /* Wait for DTC completion */

                      ret = ra_i2c_wait_event(priv,
                              I2C_STATE_TIMEOUT_US * msgs[i].length);
                      ra_i2c_dtc_stop(priv);

                      /* Invalidate cache for RX buffer */

                      up_invalidate_dcache((uintptr_t)msgs[i].buffer,
                          (uintptr_t)msgs[i].buffer + msgs[i].length);

                      priv->dcnt = 0;
                    }
                }
              else
#endif
                {
                  /* Fall through to polled transfer */

                  use_dma_transfer = false;
                }
            }

          if (!use_dma_transfer)
#endif /* CONFIG_RA_DMA || CONFIG_RA_DTC */
            {
              /* Read all bytes using polled/interrupt method */

              while (priv->dcnt > 0 && ret == OK)
                {
                  ret = ra_i2c_wait_event(priv, I2C_STATE_TIMEOUT_US);
                  if (ret == OK)
                    {
                      ret = ra_i2c_readdata(priv);
                    }
                }
            }
        }
      else
        {
          /* Writing */

#if defined(CONFIG_RA_DMA) || defined(CONFIG_RA_DTC)
          if (use_dma_transfer)
            {
              /* Use DMA/DTC for bulk write */

#ifdef CONFIG_RA_DMA
              if (priv->use_dma)
                {
                  ret = ra_i2c_dma_start_tx(priv, msgs[i].buffer,
                                            msgs[i].length);
                  if (ret == OK)
                    {
                      /* Wait for DMA completion */

                      ret = ra_i2c_wait_event(priv,
                              I2C_STATE_TIMEOUT_US * msgs[i].length);
                      ra_i2c_dma_stop(priv);
                      priv->dcnt = 0;
                    }
                }
              else
#endif
#ifdef CONFIG_RA_DTC
              if (priv->use_dtc)
                {
                  ret = ra_i2c_dtc_start_tx(priv, msgs[i].buffer,
                                            msgs[i].length);
                  if (ret == OK)
                    {
                      /* Wait for DTC completion */

                      ret = ra_i2c_wait_event(priv,
                              I2C_STATE_TIMEOUT_US * msgs[i].length);
                      ra_i2c_dtc_stop(priv);
                      priv->dcnt = 0;
                    }
                }
              else
#endif
                {
                  /* Fall through to polled transfer */

                  use_dma_transfer = false;
                }
            }

          if (!use_dma_transfer)
#endif /* CONFIG_RA_DMA || CONFIG_RA_DTC */
            {
              /* Writing - send all bytes using polled/interrupt method */

              while (priv->dcnt > 0 && ret == OK)
                {
                  ret = ra_i2c_wait_event(priv, I2C_STATE_TIMEOUT_US);
                  if (ret == OK)
                    {
                      ret = ra_i2c_senddata(priv);
                    }
                }
            }
        }

      /* Generate stop condition for last message or if I2C_M_NOSTOP
       * is not set
       */

      if (ret == OK && (i == count - 1 || !(msgs[i].flags & I2C_M_NOSTOP)))
        {
          ret = ra_i2c_stop(priv);
        }
    }

  /* Generate stop condition if transfer failed */

  if (ret != OK && priv->state != I2CSTATE_IDLE)
    {
      ra_i2c_stop(priv);
    }

#ifdef CONFIG_RA_DTC
  /* Ensure DTC is stopped on error */

  if (priv->dtc_active)
    {
      ra_i2c_dtc_stop(priv);
    }
#endif

#ifdef CONFIG_RA_DMA
  /* Ensure DMA is stopped on error */

  if (priv->dma_active)
    {
      ra_i2c_dma_stop(priv);
    }
#endif

  nxmutex_unlock(&priv->lock);

  return ret;
}

#ifdef CONFIG_I2C_RESET
/****************************************************************************
 * Name: ra_i2c_reset
 *
 * Description:
 *   Reset the I2C bus
 *
 ****************************************************************************/

static int ra_i2c_reset(struct i2c_master_s *dev)
{
  struct ra_i2c_priv_s *priv = (struct ra_i2c_priv_s *)dev;
  int ret;

  DEBUGASSERT(priv != NULL);

  /* Get exclusive access to the I2C bus */
  ret = nxmutex_lock(&priv->lock);
  if (ret < 0)
    {
      return ret;
    }

  /* Disable and re-enable I2C to reset state */
  ra_i2c_modifyreg(priv, R_IIC_ICCR1_OFFSET, R_IIC_ICCR1_ICE, 0);
  up_udelay(10);
  ra_i2c_modifyreg(priv, R_IIC_ICCR1_OFFSET, 0, R_IIC_ICCR1_ICE);

  priv->state = I2CSTATE_IDLE;

  nxmutex_unlock(&priv->lock);

  return OK;
}
#endif

/****************************************************************************
 * Name: ra_i2c_init
 *
 * Description:
 *   Initialize the I2C hardware
 *
 ****************************************************************************/

static int ra_i2c_init(struct ra_i2c_priv_s *priv)
{
  const struct ra_i2c_config_s *config = priv->config;

  /* Enable I2C module clock */

  ra_mstp_start(config->mstp);

  /* Reset I2C peripheral */

  ra_i2c_modifyreg(priv, R_IIC_ICCR1_OFFSET, 0, R_IIC_ICCR1_IICRST);
  up_udelay(10);
  ra_i2c_modifyreg(priv, R_IIC_ICCR1_OFFSET, R_IIC_ICCR1_IICRST, 0);

  /* Configure I2C mode registers */

  /* ICMR1: Set internal reference clock select and bit counter */

  ra_i2c_putreg(priv, R_IIC_ICMR1_OFFSET, 0);

  /* ICMR2: Configure delays and timeout */

  ra_i2c_putreg(priv, R_IIC_ICMR2_OFFSET, 0);

  /* ICMR3: Configure SMBus/I2C selection and noise filter */

  ra_i2c_putreg(priv, R_IIC_ICMR3_OFFSET, R_IIC_ICMR3_NF_MASK); /* Enable noise filter */

  /* ICFER: Configure function enables */

  ra_i2c_putreg(priv, R_IIC_ICFER_OFFSET,
                R_IIC_ICFER_TMOE |    /* Enable timeout */
                R_IIC_ICFER_MALE |    /* Enable master arbitration-lost detection */
                R_IIC_ICFER_NALE |    /* Enable NACK arbitration-lost detection */
                R_IIC_ICFER_SALE |    /* Enable slave arbitration-lost detection */
                R_IIC_ICFER_NACKE |   /* Enable NACK transmission arbitration-lost detection */
                R_IIC_ICFER_NFE |     /* Enable digital noise filter */
                R_IIC_ICFER_SCLE);    /* Enable SCL synchronous circuit */

  /* ICSER: Disable slave address detection */

  ra_i2c_putreg(priv, R_IIC_ICSER_OFFSET, 0);

  /* Enable I2C peripheral */

  ra_i2c_modifyreg(priv, R_IIC_ICCR1_OFFSET, 0, R_IIC_ICCR1_ICE);

  /* Set default frequency */

  priv->frequency = 0;  /* Force frequency setting */
  ra_i2c_setfrequency((struct i2c_master_s *)priv, I2C_SPEED_STANDARD);

#ifndef CONFIG_I2C_POLLED
  /* Configure and enable interrupts AFTER peripheral is configured */

  ra_i2c_putreg(priv, R_IIC_ICIER_OFFSET,
                R_IIC_ICIER_TIE |     /* Transmit data empty interrupt */
                R_IIC_ICIER_TEIE |    /* Transmit end interrupt */
                R_IIC_ICIER_RIE |     /* Receive data full interrupt */
                R_IIC_ICIER_NAKIE |   /* NACK detection interrupt */
                R_IIC_ICIER_SPIE |    /* Stop condition detection interrupt */
                R_IIC_ICIER_STIE |    /* Start condition detection interrupt */
                R_IIC_ICIER_ALIE |    /* Arbitration-lost detection interrupt */
                R_IIC_ICIER_TMOIE);   /* Timeout detection interrupt */

  /* Attach interrupt handlers */

  priv->rxi_irq = ra_icu_attach(config->rxi_elc, ra_i2c_isr_rxi, priv, true);
  priv->txi_irq = ra_icu_attach(config->txi_elc, ra_i2c_isr_txi, priv, true);
  priv->tei_irq = ra_icu_attach(config->tei_elc, ra_i2c_isr_tei, priv, true);
  priv->eri_irq = ra_icu_attach(config->eri_elc, ra_i2c_isr_eri, priv, true);
#endif

#ifdef CONFIG_RA_DTC
  /* Setup DTC if enabled */

  ra_i2c_dtc_setup(priv);
#endif

#ifdef CONFIG_RA_DMA
  /* Setup DMA if enabled */

  ra_i2c_dma_setup(priv);
#endif

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_deinit
 *
 * Description:
 *   Deinitialize the I2C hardware
 *
 ****************************************************************************/

static int ra_i2c_deinit(struct ra_i2c_priv_s *priv)
{
  const struct ra_i2c_config_s *config = priv->config;

  /* Disable I2C peripheral */

  ra_i2c_modifyreg(priv, R_IIC_ICCR1_OFFSET, R_IIC_ICCR1_ICE, 0);

#ifndef CONFIG_I2C_POLLED
  /* Disable interrupts */

  ra_icu_detach(priv->rxi_irq);
  ra_icu_detach(priv->txi_irq);
  ra_icu_detach(priv->tei_irq);
  ra_icu_detach(priv->eri_irq);
#endif

#ifdef CONFIG_RA_DTC
  /* Cleanup DTC */

  ra_i2c_dtc_cleanup(priv);
#endif

#ifdef CONFIG_RA_DMA
  /* Cleanup DMA */

  ra_i2c_dma_stop(priv);
  priv->use_dma = false;
#endif

  /* Disable I2C module clock */

  ra_mstp_stop(config->mstp);

  return OK;
}

#ifndef CONFIG_I2C_POLLED
/****************************************************************************
 * Name: ra_i2c_isr_rxi
 *
 * Description:
 *   I2C RX interrupt service routine
 *
 ****************************************************************************/

static int ra_i2c_isr_rxi(int irq, void *context, void *arg)
{
  struct ra_i2c_priv_s *priv = (struct ra_i2c_priv_s *)arg;

  DEBUGASSERT(priv != NULL);

  /* Signal semaphore to wake up waiting thread */
  nxsem_post(&priv->sem_isr);

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_isr_txi
 *
 * Description:
 *   I2C TX interrupt service routine
 *
 ****************************************************************************/

static int ra_i2c_isr_txi(int irq, void *context, void *arg)
{
  struct ra_i2c_priv_s *priv = (struct ra_i2c_priv_s *)arg;

  DEBUGASSERT(priv != NULL);

  /* Signal semaphore to wake up waiting thread */
  nxsem_post(&priv->sem_isr);

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_isr_tei
 *
 * Description:
 *   I2C transfer end interrupt service routine
 *
 ****************************************************************************/

static int ra_i2c_isr_tei(int irq, void *context, void *arg)
{
  struct ra_i2c_priv_s *priv = (struct ra_i2c_priv_s *)arg;

  DEBUGASSERT(priv != NULL);

  /* Signal semaphore to wake up waiting thread */
  nxsem_post(&priv->sem_isr);

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_isr_eri
 *
 * Description:
 *   I2C error interrupt service routine
 *
 ****************************************************************************/

static int ra_i2c_isr_eri(int irq, void *context, void *arg)
{
  struct ra_i2c_priv_s *priv = (struct ra_i2c_priv_s *)arg;
  uint8_t sr2;

  DEBUGASSERT(priv != NULL);

  /* Read status to determine error type */
  sr2 = ra_i2c_getreg(priv, R_IIC_ICSR2_OFFSET);
  priv->status = sr2;

  /* Clear error flags */
  ra_i2c_modifyreg(priv, R_IIC_ICSR2_OFFSET,
                  R_IIC_ICSR2_AL | R_IIC_ICSR2_TMOF | R_IIC_ICSR2_NACKF, 0);

  /* Signal semaphore to wake up waiting thread */
  nxsem_post(&priv->sem_isr);

  return OK;
}

#endif /* !CONFIG_I2C_POLLED */

#ifdef CONFIG_RA_DTC
/****************************************************************************
 * Name: ra_i2c_dtc_setup
 *
 * Description:
 *   Setup DTC for I2C transfers
 *
 ****************************************************************************/

static int ra_i2c_dtc_setup(struct ra_i2c_priv_s *priv)
{
  i2cinfo("DTC setup for I2C%d\n", priv->config->bus);

  /* Initialize DTC module once (global initialization) */

  if (!g_i2c_dtc_initialized)
    {
      irqstate_t flags = enter_critical_section();

      if (!g_i2c_dtc_initialized)
        {
          /* Enable DTC module clock */

          ra_mstp_start(RA_MSTP_DMAC_DTC);

          /* Initialize DTC module - this will set up the vector table */

          ra_dtc_initialize();

          g_i2c_dtc_initialized = true;

          i2cinfo("DTC module initialized\n");
        }

      leave_critical_section(flags);
    }

  /* DTC active state is per-transfer, initialize to false */

  priv->dtc_active = false;
  priv->use_dtc = true;

  /* Clear DTC transfer info structures */

  memset(&priv->dtc_tx_info, 0, sizeof(priv->dtc_tx_info));
  memset(&priv->dtc_rx_info, 0, sizeof(priv->dtc_rx_info));

  i2cinfo("DTC setup completed for I2C%d\n", priv->config->bus);

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_dtc_start_rx
 *
 * Description:
 *   Start DTC for I2C RX transfer
 *
 ****************************************************************************/

static int ra_i2c_dtc_start_rx(struct ra_i2c_priv_s *priv,
                               uint8_t *buffer, uint32_t len)
{
  int slot;

  i2cinfo("DTC RX start: buffer=%p len=%lu\n", buffer, (unsigned long)len);

  if (buffer == NULL || len == 0)
    {
      return -EINVAL;
    }

  /* Configure RX DTC: source fixed (ICDRR), dest increment, normal mode */

  priv->dtc_rx_info.mra = RA_DTC_MRA_MD_NORMAL |
                          RA_DTC_MRA_SZ_BYTE |
                          RA_DTC_MRA_SM_FIXED;
  priv->dtc_rx_info.mrb = RA_DTC_MRB_DM_INCREMENT |
                          RA_DTC_MRB_DISEL;  /* IRQ at end */
  priv->dtc_rx_info.sar = priv->config->base + R_IIC_ICDRR_OFFSET;
  priv->dtc_rx_info.dar = (uint32_t)buffer;
  priv->dtc_rx_info.cra = (uint16_t)len;
  priv->dtc_rx_info.crb = 0;

  /* Flush DTC transfer info to memory */

  up_clean_dcache((uintptr_t)&priv->dtc_rx_info,
                  (uintptr_t)&priv->dtc_rx_info + sizeof(priv->dtc_rx_info));

  /* Configure DTC vector table entry using ICU-assigned slot */

  slot = priv->rxi_irq - RA_IRQ_FIRST;
  ra_icu_disable_dtc(priv->rxi_irq);
  ra_dtc_set_vector(slot, &priv->dtc_rx_info);

  /* Enable DTC trigger in ICU */

  ra_icu_enable_dtc(priv->rxi_irq);

  priv->dtc_active = true;

  i2cinfo("RX DTC configured: SAR=0x%08lx DAR=0x%08lx CRA=%d slot=%d\n",
          (unsigned long)priv->dtc_rx_info.sar,
          (unsigned long)priv->dtc_rx_info.dar,
          priv->dtc_rx_info.cra, slot);

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_dtc_start_tx
 *
 * Description:
 *   Start DTC for I2C TX transfer
 *
 ****************************************************************************/

static int ra_i2c_dtc_start_tx(struct ra_i2c_priv_s *priv,
                               const uint8_t *buffer, uint32_t len)
{
  int slot;

  i2cinfo("DTC TX start: buffer=%p len=%lu\n", buffer, (unsigned long)len);

  if (buffer == NULL || len == 0)
    {
      return -EINVAL;
    }

  /* Clean D-cache for TX buffer before DTC reads it */

  up_clean_dcache((uintptr_t)buffer, (uintptr_t)buffer + len);

  /* Configure TX DTC: source increment, dest fixed (ICDRT), normal mode */

  priv->dtc_tx_info.mra = RA_DTC_MRA_MD_NORMAL |
                          RA_DTC_MRA_SZ_BYTE |
                          RA_DTC_MRA_SM_INCREMENT;
  priv->dtc_tx_info.mrb = RA_DTC_MRB_DM_FIXED |
                          RA_DTC_MRB_DISEL;  /* IRQ at end */
  priv->dtc_tx_info.sar = (uint32_t)buffer;
  priv->dtc_tx_info.dar = priv->config->base + R_IIC_ICDRT_OFFSET;
  priv->dtc_tx_info.cra = (uint16_t)len;
  priv->dtc_tx_info.crb = 0;

  /* Flush DTC transfer info to memory */

  up_clean_dcache((uintptr_t)&priv->dtc_tx_info,
                  (uintptr_t)&priv->dtc_tx_info + sizeof(priv->dtc_tx_info));

  /* Configure DTC vector table entry using ICU-assigned slot */

  slot = priv->txi_irq - RA_IRQ_FIRST;
  ra_icu_disable_dtc(priv->txi_irq);
  ra_dtc_set_vector(slot, &priv->dtc_tx_info);

  /* Enable DTC trigger in ICU */

  ra_icu_enable_dtc(priv->txi_irq);

  priv->dtc_active = true;

  i2cinfo("TX DTC configured: SAR=0x%08lx DAR=0x%08lx CRA=%d slot=%d\n",
          (unsigned long)priv->dtc_tx_info.sar,
          (unsigned long)priv->dtc_tx_info.dar,
          priv->dtc_tx_info.cra, slot);

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_dtc_stop
 *
 * Description:
 *   Stop DTC transfer
 *
 ****************************************************************************/

static void ra_i2c_dtc_stop(struct ra_i2c_priv_s *priv)
{
  i2cinfo("DTC stop for I2C%d\n", priv->config->bus);

  /* Disable DTC triggers */

  if (priv->txi_irq >= 0)
    {
      ra_icu_disable_dtc(priv->txi_irq);
    }

  if (priv->rxi_irq >= 0)
    {
      ra_icu_disable_dtc(priv->rxi_irq);
    }

  priv->dtc_active = false;
}

/****************************************************************************
 * Name: ra_i2c_dtc_cleanup
 *
 * Description:
 *   Cleanup DTC resources
 *
 ****************************************************************************/

static void ra_i2c_dtc_cleanup(struct ra_i2c_priv_s *priv)
{
  i2cinfo("DTC cleanup for I2C%d\n", priv->config->bus);

  ra_i2c_dtc_stop(priv);
  priv->use_dtc = false;
}
#endif /* CONFIG_RA_DTC */

#ifdef CONFIG_RA_DMA
/****************************************************************************
 * Name: ra_i2c_dma_tx_callback
 *
 * Description:
 *   DMA TX completion callback
 *
 ****************************************************************************/

static void ra_i2c_dma_tx_callback(void *handle, int event, void *arg)
{
  struct ra_i2c_priv_s *priv = (struct ra_i2c_priv_s *)arg;

  DEBUGASSERT(priv != NULL);

  if (event == RA_DMAC_EVENT_COMPLETE)
    {
      priv->dma_tx_done = true;
      i2cinfo("I2C%d DMA TX complete\n", priv->config->bus);
    }
  else
    {
      i2cerr("I2C%d DMA TX error: event=%d\n", priv->config->bus, event);
      priv->state = I2CSTATE_ERROR;
    }

#ifndef CONFIG_I2C_POLLED
  /* Signal completion */

  nxsem_post(&priv->sem_isr);
#endif
}

/****************************************************************************
 * Name: ra_i2c_dma_rx_callback
 *
 * Description:
 *   DMA RX completion callback
 *
 ****************************************************************************/

static void ra_i2c_dma_rx_callback(void *handle, int event, void *arg)
{
  struct ra_i2c_priv_s *priv = (struct ra_i2c_priv_s *)arg;

  DEBUGASSERT(priv != NULL);

  if (event == RA_DMAC_EVENT_COMPLETE)
    {
      priv->dma_rx_done = true;
      i2cinfo("I2C%d DMA RX complete\n", priv->config->bus);

      /* Invalidate D-cache for RX buffer after DMA writes it */

      if (priv->ptr != NULL && priv->dcnt > 0)
        {
          up_invalidate_dcache((uintptr_t)priv->ptr,
                               (uintptr_t)priv->ptr + priv->dcnt);
        }
    }
  else
    {
      i2cerr("I2C%d DMA RX error: event=%d\n", priv->config->bus, event);
      priv->state = I2CSTATE_ERROR;
    }

#ifndef CONFIG_I2C_POLLED
  /* Signal completion */

  nxsem_post(&priv->sem_isr);
#endif
}

/****************************************************************************
 * Name: ra_i2c_dma_setup
 *
 * Description:
 *   Setup DMA for I2C transfers
 *
 ****************************************************************************/

static int ra_i2c_dma_setup(struct ra_i2c_priv_s *priv)
{
  int ret;

  i2cinfo("DMA setup for I2C%d\n", priv->config->bus);

  /* Initialize DMAC module */

  ret = ra_dmac_initialize();
  if (ret < 0)
    {
      i2cerr("Failed to initialize DMAC: %d\n", ret);
      return ret;
    }

  /* DMA active state is per-transfer, initialize to false */

  priv->dma_active = false;
  priv->dma_tx = NULL;
  priv->dma_rx = NULL;
  priv->dma_tx_done = false;
  priv->dma_rx_done = false;
  priv->use_dma = true;

  i2cinfo("DMA setup completed for I2C%d\n", priv->config->bus);

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_dma_start_tx
 *
 * Description:
 *   Start DMA for I2C TX transfer
 *
 ****************************************************************************/

static int ra_i2c_dma_start_tx(struct ra_i2c_priv_s *priv,
                               const uint8_t *buffer, uint32_t len)
{
  ra_dmac_config_t config;
  int ret;

  i2cinfo("DMA TX start: buffer=%p len=%lu\n", buffer, (unsigned long)len);

  if (buffer == NULL || len == 0)
    {
      return -EINVAL;
    }

  /* Clean D-cache for TX buffer before DMA reads it */

  up_clean_dcache((uintptr_t)buffer, (uintptr_t)buffer + len);

  /* Configure TX DMA */

  memset(&config, 0, sizeof(config));
  config.mode = RA_DMAC_MODE_NORMAL;
  config.repeat_area = RA_DMAC_REPEAT_AREA_NONE;
  config.size = RA_DMAC_SIZE_8BIT;
  config.src_addr_mode = RA_DMAC_ADDR_INCR;    /* Source increments */
  config.dest_addr_mode = RA_DMAC_ADDR_FIXED;  /* Dest fixed (ICDRT) */
  config.trigger = RA_DMAC_TRIGGER_HW;         /* Hardware trigger */
  config.src_addr = (uint32_t)buffer;
  config.dest_addr = priv->config->base + R_IIC_ICDRT_OFFSET;
  config.transfer_count = len;
  config.block_count = 0;
  config.elc_src = priv->config->txi_elc;      /* I2C TXI event */
  config.elc_end = -1;
  config.elc_err = -1;
  config.callback = ra_i2c_dma_tx_callback;
  config.user_data = priv;

  ret = ra_dmac_open(&priv->dma_tx, &config);
  if (ret < 0)
    {
      i2cerr("Failed to open TX DMA: %d\n", ret);
      return ret;
    }

  ret = ra_dmac_enable(priv->dma_tx);
  if (ret < 0)
    {
      i2cerr("Failed to enable TX DMA: %d\n", ret);
      ra_dmac_close(priv->dma_tx);
      priv->dma_tx = NULL;
      return ret;
    }

  priv->dma_tx_done = false;
  priv->dma_active = true;

  i2cinfo("TX DMA configured: src=0x%08lx dst=0x%08lx count=%lu\n",
          (unsigned long)buffer,
          (unsigned long)(priv->config->base + R_IIC_ICDRT_OFFSET),
          (unsigned long)len);

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_dma_start_rx
 *
 * Description:
 *   Start DMA for I2C RX transfer
 *
 ****************************************************************************/

static int ra_i2c_dma_start_rx(struct ra_i2c_priv_s *priv,
                               uint8_t *buffer, uint32_t len)
{
  ra_dmac_config_t config;
  int ret;

  i2cinfo("DMA RX start: buffer=%p len=%lu\n", buffer, (unsigned long)len);

  if (buffer == NULL || len == 0)
    {
      return -EINVAL;
    }

  /* Configure RX DMA */

  memset(&config, 0, sizeof(config));
  config.mode = RA_DMAC_MODE_NORMAL;
  config.repeat_area = RA_DMAC_REPEAT_AREA_NONE;
  config.size = RA_DMAC_SIZE_8BIT;
  config.src_addr_mode = RA_DMAC_ADDR_FIXED;   /* Source fixed (ICDRR) */
  config.dest_addr_mode = RA_DMAC_ADDR_INCR;   /* Dest increments */
  config.trigger = RA_DMAC_TRIGGER_HW;         /* Hardware trigger */
  config.src_addr = priv->config->base + R_IIC_ICDRR_OFFSET;
  config.dest_addr = (uint32_t)buffer;
  config.transfer_count = len;
  config.block_count = 0;
  config.elc_src = priv->config->rxi_elc;      /* I2C RXI event */
  config.elc_end = -1;
  config.elc_err = -1;
  config.callback = ra_i2c_dma_rx_callback;
  config.user_data = priv;

  ret = ra_dmac_open(&priv->dma_rx, &config);
  if (ret < 0)
    {
      i2cerr("Failed to open RX DMA: %d\n", ret);
      return ret;
    }

  ret = ra_dmac_enable(priv->dma_rx);
  if (ret < 0)
    {
      i2cerr("Failed to enable RX DMA: %d\n", ret);
      ra_dmac_close(priv->dma_rx);
      priv->dma_rx = NULL;
      return ret;
    }

  priv->dma_rx_done = false;
  priv->dma_active = true;

  i2cinfo("RX DMA configured: src=0x%08lx dst=0x%08lx count=%lu\n",
          (unsigned long)(priv->config->base + R_IIC_ICDRR_OFFSET),
          (unsigned long)buffer,
          (unsigned long)len);

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_dma_stop
 *
 * Description:
 *   Stop DMA transfer and release resources
 *
 ****************************************************************************/

static void ra_i2c_dma_stop(struct ra_i2c_priv_s *priv)
{
  i2cinfo("DMA stop for I2C%d\n", priv->config->bus);

  /* Disable and close TX DMA */

  if (priv->dma_tx != NULL)
    {
      ra_dmac_disable(priv->dma_tx);
      ra_dmac_close(priv->dma_tx);
      priv->dma_tx = NULL;
      i2cinfo("TX DMA stopped\n");
    }

  /* Disable and close RX DMA */

  if (priv->dma_rx != NULL)
    {
      ra_dmac_disable(priv->dma_rx);
      ra_dmac_close(priv->dma_rx);
      priv->dma_rx = NULL;
      i2cinfo("RX DMA stopped\n");
    }

  priv->dma_active = false;
  priv->dma_tx_done = false;
  priv->dma_rx_done = false;
}
#endif /* CONFIG_RA_DMA */

/****************************************************************************
 * Name: ra_i2cbus_initialize
 *
 * Description:
 *   Initialize the selected I2C port. And return a unique instance of struct
 *   struct i2c_master_s.  This function may be called to obtain multiple
 *   instances of the interface, each of which may be set up with a
 *   different frequency and slave address.
 *
 * Input Parameters:
 *   Port number (for hardware that has multiple I2C interfaces)
 *
 * Returned Value:
 *   Valid I2C device structure reference on success; a NULL on failure
 *
 ****************************************************************************/

struct i2c_master_s *ra_i2cbus_initialize(int port)
{
  struct ra_i2c_priv_s *priv = NULL;

  i2cinfo("I2C%d: Initialize\n", port);

  /* Get I2C private structure */
  switch (port)
    {
#ifdef CONFIG_RA_I2C0
      case 0:
        priv = &ra_i2c0_priv;
        break;
#endif

#ifdef CONFIG_RA_I2C1
      case 1:
        priv = &ra_i2c1_priv;
        break;
#endif

#ifdef CONFIG_RA_I2C2
      case 2:
        priv = &ra_i2c2_priv;
        break;
#endif

      default:
        i2cerr("I2C%d: Invalid port\n", port);
        return NULL;
    }

  /* Initialize the device structure */
  if (priv->refs++ == 0)
    {
      /* Initialize the I2C hardware */
      ra_i2c_init(priv);
    }

  return (struct i2c_master_s *)priv;
}

/****************************************************************************
 * Name: ra_i2cbus_uninitialize
 *
 * Description:
 *   De-initialize the selected I2C port, and power down the device.
 *
 * Input Parameters:
 *   Device structure as returned by ra_i2cbus_initialize()
 *
 * Returned Value:
 *   OK on success, ERROR when internal reference count mismatch or dev
 *   points to invalid hardware device.
 *
 ****************************************************************************/

int ra_i2cbus_uninitialize(struct i2c_master_s *dev)
{
  struct ra_i2c_priv_s *priv = (struct ra_i2c_priv_s *)dev;

  DEBUGASSERT(priv != NULL);

  /* Decrement reference count and check if we should disable the peripheral */
  if (--priv->refs == 0)
    {
      /* Disable the I2C hardware */
      ra_i2c_deinit(priv);
    }

  return OK;
}

#endif /* CONFIG_RA_I2C */

/****************************************************************************
 * arch/arm/src/ra8/ra_i2c_slave.c
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
#include <nuttx/i2c/i2c_slave.h>

#include <arch/board/board.h>

#include "arm_internal.h"
#include "chip.h"
#include "hardware/ra_memorymap.h"
#include "ra_i2c.h"
#include "ra_icu.h"
#include "ra_mstp.h"

#ifdef CONFIG_RA_I2C_SLAVE

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Debug ********************************************************************/

#ifdef CONFIG_DEBUG_I2C_INFO
#  define i2cs_dumpgpio(m) ra_dumpgpio(m)
#else
#  define i2cs_dumpgpio(m)
#endif

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* I2C Slave Device Private Data */
struct ra_i2c_slave_priv_s
{
  /* Standard I2C slave operations */
  const struct i2c_slave_ops_s *ops;

  /* Port configuration */
  const struct ra_i2c_config_s *config;

  int      refs;          /* Reference count */
  mutex_t  lock;          /* Mutual exclusion mutex */

#ifndef CONFIG_I2C_POLLED
  sem_t    sem_isr;       /* Interrupt wait semaphore */
  sem_t    sem_tx;        /* TX completion semaphore */
  sem_t    sem_rx;        /* RX completion semaphore */
#endif

  /* I2C slave state */
  volatile uint8_t state;

  /* I2C slave address */
  uint16_t slave_addr;    /* Own slave address */

  /* I2C transfer state */
  uint8_t *rx_buffer;     /* RX transfer buffer */
  uint32_t rx_buflen;     /* RX buffer length */
  uint32_t rx_nbytes;     /* Number of bytes received */

  const uint8_t *tx_buffer; /* TX transfer buffer */
  uint32_t tx_buflen;     /* TX buffer length */
  uint32_t tx_nbytes;     /* Number of bytes transmitted */

  /* Callback function */
  i2c_slave_callback_t callback;
  void *callback_arg;

  /* Interrupt numbers assigned at runtime */
  int      rxi_irq;       /* RX interrupt number */
  int      txi_irq;       /* TX interrupt number */
  int      tei_irq;       /* TE interrupt number */
  int      eri_irq;       /* ER interrupt number */

  uint32_t status;        /* End of transfer status */
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* I2C slave operations */
static int ra_i2c_slave_setaddress(struct i2c_slave_s *dev, int addr);
static int ra_i2c_slave_write(struct i2c_slave_s *dev, const uint8_t *buffer, int buflen);
static int ra_i2c_slave_read(struct i2c_slave_s *dev, uint8_t *buffer, int buflen);
static int ra_i2c_slave_registercallback(struct i2c_slave_s *dev,
                                        i2c_slave_callback_t callback, void *arg);

/* I2C slave helper functions */
static int ra_i2c_slave_init(struct ra_i2c_slave_priv_s *priv);
static int ra_i2c_slave_deinit(struct ra_i2c_slave_priv_s *priv);

/* I2C slave interrupt service routines */
#ifndef CONFIG_I2C_POLLED
static int ra_i2c_slave_isr_rxi(int irq, void *context, void *arg);
static int ra_i2c_slave_isr_txi(int irq, void *context, void *arg);
static int ra_i2c_slave_isr_tei(int irq, void *context, void *arg);
static int ra_i2c_slave_isr_eri(int irq, void *context, void *arg);
static int ra_i2c_slave_isr_start(int irq, void *context, void *arg);
static int ra_i2c_slave_isr_stop(int irq, void *context, void *arg);
static int ra_i2c_slave_isr_address(int irq, void *context, void *arg);
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* I2C Slave Interface */
static const struct i2c_slave_ops_s ra_i2c_slave_ops =
{
  .setaddress       = ra_i2c_slave_setaddress,
  .write            = ra_i2c_slave_write,
  .read             = ra_i2c_slave_read,
  .registercallback = ra_i2c_slave_registercallback,
};

/* I2C slave device configuration */
#ifdef CONFIG_RA_I2C0_SLAVE
static const struct ra_i2c_config_s ra_i2c0_slave_config =
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

static struct ra_i2c_slave_priv_s ra_i2c0_slave_priv =
{
  .ops          = &ra_i2c_slave_ops,
  .config       = &ra_i2c0_slave_config,
  .refs         = 0,
  .lock         = NXMUTEX_INITIALIZER,
#ifndef CONFIG_I2C_POLLED
  .sem_isr      = SEM_INITIALIZER(0),
  .sem_tx       = SEM_INITIALIZER(0),
  .sem_rx       = SEM_INITIALIZER(0),
#endif
  .state        = I2CSTATE_IDLE,
};
#endif

#ifdef CONFIG_RA_I2C1_SLAVE
static const struct ra_i2c_config_s ra_i2c1_slave_config =
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

static struct ra_i2c_slave_priv_s ra_i2c1_slave_priv =
{
  .ops          = &ra_i2c_slave_ops,
  .config       = &ra_i2c1_slave_config,
  .refs         = 0,
  .lock         = NXMUTEX_INITIALIZER,
#ifndef CONFIG_I2C_POLLED
  .sem_isr      = SEM_INITIALIZER(0),
  .sem_tx       = SEM_INITIALIZER(0),
  .sem_rx       = SEM_INITIALIZER(0),
#endif
  .state        = I2CSTATE_IDLE,
};
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_i2c_slave_getreg
 *
 * Description:
 *   Get a 8-bit register value by offset
 *
 ****************************************************************************/

static inline uint8_t ra_i2c_slave_getreg(struct ra_i2c_slave_priv_s *priv, uint8_t offset)
{
  return getreg8(priv->config->base + offset);
}

/****************************************************************************
 * Name: ra_i2c_slave_putreg
 *
 * Description:
 *   Put a 8-bit register value by offset
 *
 ****************************************************************************/

static inline void ra_i2c_slave_putreg(struct ra_i2c_slave_priv_s *priv, uint8_t offset, uint8_t value)
{
  putreg8(value, priv->config->base + offset);
}

/****************************************************************************
 * Name: ra_i2c_slave_modifyreg
 *
 * Description:
 *   Modify a 8-bit register value by offset
 *
 ****************************************************************************/

static inline void ra_i2c_slave_modifyreg(struct ra_i2c_slave_priv_s *priv, uint8_t offset,
                                         uint8_t clearbits, uint8_t setbits)
{
  modifyreg8(priv->config->base + offset, clearbits, setbits);
}

/****************************************************************************
 * Name: ra_i2c_slave_setaddress
 *
 * Description:
 *   Set the I2C slave address
 *
 ****************************************************************************/

static int ra_i2c_slave_setaddress(struct i2c_slave_s *dev, int addr)
{
  struct ra_i2c_slave_priv_s *priv = (struct ra_i2c_slave_priv_s *)dev;
  uint8_t sar_low;
  uint8_t sar_high;

  DEBUGASSERT(priv != NULL);
  DEBUGASSERT(addr >= 0 && addr <= 0x7F);

  priv->slave_addr = addr;

  /* SAR register structure (per hardware manual):
   * SAR is a 16-bit register accessed as two 8-bit registers
   * SAR[0] offset 0x0A: Lower byte
   *   Bits [7:1]: SVA[6:0] - Slave Address bits 6-0 (7-bit mode)
   *   Bit [0]: FS - Format Select (0 = 7-bit mode, 1 = 10-bit mode)
   * SAR[0] offset 0x0B: Upper byte
   *   Bits [2:0]: SVA[9:7] - Upper slave address bits (10-bit mode only)
   *
   * For 7-bit address: address goes in bits [7:1] of lower byte, FS=0
   */

  sar_low = (uint8_t)((addr << 1) & 0xFE);  /* SVA[6:0] in bits [7:1], FS=0 */
  sar_high = 0;  /* Not used for 7-bit addressing */

  /* Write to SAR0 register (using offset macro) */

  ra_i2c_slave_putreg(priv, R_IIC_SAR_OFFSET(0), sar_low);
  ra_i2c_slave_putreg(priv, R_IIC_SAR_OFFSET(0) + 1, sar_high);

  /* Enable slave address 0 detection */

  ra_i2c_slave_modifyreg(priv, R_IIC_ICSER_OFFSET, 0, R_IIC_ICSER_SAR0E);

  i2cinfo("I2C%d slave address set to 0x%02X\n", priv->config->bus, addr);

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_slave_write
 *
 * Description:
 *   Send data to I2C master (slave transmit mode)
 *   This function prepares the TX buffer. Actual transmission happens
 *   when master requests data via TXI interrupt.
 *
 ****************************************************************************/

static int ra_i2c_slave_write(struct i2c_slave_s *dev,
                              const uint8_t *buffer, int buflen)
{
  struct ra_i2c_slave_priv_s *priv = (struct ra_i2c_slave_priv_s *)dev;
  int ret = OK;

  DEBUGASSERT(priv != NULL && buffer != NULL && buflen > 0);

  /* Get exclusive access */

  ret = nxmutex_lock(&priv->lock);
  if (ret < 0)
    {
      return ret;
    }

  /* Setup TX transfer buffer */

  priv->tx_buffer = buffer;
  priv->tx_buflen = buflen;
  priv->tx_nbytes = 0;

  /* Enable TX interrupt to respond when master requests data */

  ra_i2c_slave_modifyreg(priv, R_IIC_ICIER_OFFSET, 0, R_IIC_ICIER_TIE);

#ifndef CONFIG_I2C_POLLED
  /* Wait for transmission to complete or master to issue stop */

  ret = nxsem_wait(&priv->sem_tx);
  if (ret < 0)
    {
      i2cerr("I2C%d slave TX wait failed: %d\n", priv->config->bus, ret);
    }
#endif

  /* Return number of bytes transmitted */

  if (ret == OK)
    {
      ret = priv->tx_nbytes;
    }

  nxmutex_unlock(&priv->lock);

  return ret;
}

/****************************************************************************
 * Name: ra_i2c_slave_read
 *
 * Description:
 *   Receive data from I2C master (slave receive mode)
 *   This function prepares the RX buffer. Actual reception happens
 *   via RXI interrupt when master sends data.
 *
 ****************************************************************************/

static int ra_i2c_slave_read(struct i2c_slave_s *dev, uint8_t *buffer, int buflen)
{
  struct ra_i2c_slave_priv_s *priv = (struct ra_i2c_slave_priv_s *)dev;
  int ret = OK;

  DEBUGASSERT(priv != NULL && buffer != NULL && buflen > 0);

  /* Get exclusive access */

  ret = nxmutex_lock(&priv->lock);
  if (ret < 0)
    {
      return ret;
    }

  /* Setup RX transfer buffer */

  priv->rx_buffer = buffer;
  priv->rx_buflen = buflen;
  priv->rx_nbytes = 0;

  /* Enable RX interrupt to receive data from master */

  ra_i2c_slave_modifyreg(priv, R_IIC_ICIER_OFFSET, 0, R_IIC_ICIER_RIE);

#ifndef CONFIG_I2C_POLLED
  /* Wait for reception to complete or master to issue stop */

  ret = nxsem_wait(&priv->sem_rx);
  if (ret < 0)
    {
      i2cerr("I2C%d slave RX wait failed: %d\n", priv->config->bus, ret);
    }
#endif

  /* Return number of bytes received */

  if (ret == OK)
    {
      ret = priv->rx_nbytes;
    }

  nxmutex_unlock(&priv->lock);

  return ret;
}

/****************************************************************************
 * Name: ra_i2c_slave_registercallback
 *
 * Description:
 *   Register a callback function for I2C slave events
 *
 ****************************************************************************/

static int ra_i2c_slave_registercallback(struct i2c_slave_s *dev,
                                        i2c_slave_callback_t callback, void *arg)
{
  struct ra_i2c_slave_priv_s *priv = (struct ra_i2c_slave_priv_s *)dev;

  DEBUGASSERT(priv != NULL);

  priv->callback = callback;
  priv->callback_arg = arg;

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_slave_init
 *
 * Description:
 *   Initialize the I2C slave hardware
 *
 ****************************************************************************/

static int ra_i2c_slave_init(struct ra_i2c_slave_priv_s *priv)
{
  const struct ra_i2c_config_s *config = priv->config;
  int ret;

  /* Enable I2C module clock */

  ra_mstp_start(config->mstp);

  /* Reset I2C peripheral */

  ra_i2c_slave_modifyreg(priv, R_IIC_ICCR1_OFFSET, 0, R_IIC_ICCR1_IICRST);
  up_udelay(10);
  ra_i2c_slave_modifyreg(priv, R_IIC_ICCR1_OFFSET, R_IIC_ICCR1_IICRST, 0);

  /* Configure I2C mode registers for slave mode */
  /* ICMR1: Set internal reference clock select and bit counter */

  ra_i2c_slave_putreg(priv, R_IIC_ICMR1_OFFSET, 0);

  /* ICMR2: Configure delays and timeout */

  ra_i2c_slave_putreg(priv, R_IIC_ICMR2_OFFSET, 0);

  /* ICMR3: Configure SMBus/I2C selection and noise filter */

  ra_i2c_slave_putreg(priv, R_IIC_ICMR3_OFFSET, R_IIC_ICMR3_NF_MASK); /* Enable noise filter */

  /* ICFER: Configure function enables */

  ra_i2c_slave_putreg(priv, R_IIC_ICFER_OFFSET,
                      R_IIC_ICFER_TMOE |    /* Enable timeout */
                      R_IIC_ICFER_SALE |    /* Enable slave arbitration-lost detection */
                      R_IIC_ICFER_NFE |     /* Enable digital noise filter */
                      R_IIC_ICFER_SCLE);    /* Enable SCL synchronous circuit */

  /* ICSER: Configure slave address detection - will be set by setaddress */

  ra_i2c_slave_putreg(priv, R_IIC_ICSER_OFFSET, 0);

#ifndef CONFIG_I2C_POLLED
  /* Attach interrupt handlers via ICU using ELC events
   * ra_icu_attach returns the IRQ number assigned to the ELC event
   */

  priv->rxi_irq = ra_icu_attach(config->rxi_elc, ra_i2c_slave_isr_rxi, priv, true);
  if (priv->rxi_irq < 0)
    {
      i2cerr("I2C%d: Failed to attach RXI interrupt\n", config->bus);
      goto errout;
    }

  priv->txi_irq = ra_icu_attach(config->txi_elc, ra_i2c_slave_isr_txi, priv, true);
  if (priv->txi_irq < 0)
    {
      i2cerr("I2C%d: Failed to attach TXI interrupt\n", config->bus);
      goto errout_rxi;
    }

  priv->tei_irq = ra_icu_attach(config->tei_elc, ra_i2c_slave_isr_tei, priv, true);
  if (priv->tei_irq < 0)
    {
      i2cerr("I2C%d: Failed to attach TEI interrupt\n", config->bus);
      goto errout_txi;
    }

  priv->eri_irq = ra_icu_attach(config->eri_elc, ra_i2c_slave_isr_eri, priv, true);
  if (priv->eri_irq < 0)
    {
      i2cerr("I2C%d: Failed to attach ERI interrupt\n", config->bus);
      goto errout_tei;
    }

  /* Configure and enable interrupts for slave mode */

  ra_i2c_slave_putreg(priv, R_IIC_ICIER_OFFSET,
                      R_IIC_ICIER_TIE |     /* Transmit data empty interrupt */
                      R_IIC_ICIER_TEIE |    /* Transmit end interrupt */
                      R_IIC_ICIER_RIE |     /* Receive data full interrupt */
                      R_IIC_ICIER_NAKIE |   /* NACK detection interrupt */
                      R_IIC_ICIER_SPIE |    /* Stop condition detection interrupt */
                      R_IIC_ICIER_STIE |    /* Start condition detection interrupt */
                      R_IIC_ICIER_ALIE |    /* Arbitration-lost detection interrupt */
                      R_IIC_ICIER_TMOIE);   /* Timeout detection interrupt */
#endif

  /* Enable I2C peripheral in slave mode */

  ra_i2c_slave_modifyreg(priv, R_IIC_ICCR1_OFFSET, 0, R_IIC_ICCR1_ICE);

  /* Clear master mode bit to ensure slave mode */

  ra_i2c_slave_modifyreg(priv, R_IIC_ICCR2_OFFSET, R_IIC_ICCR2_MST, 0);

  return OK;

#ifndef CONFIG_I2C_POLLED
errout_tei:
  ra_icu_detach(config->tei_elc);
errout_txi:
  ra_icu_detach(config->txi_elc);
errout_rxi:
  ra_icu_detach(config->rxi_elc);
errout:
  ra_mstp_stop(config->mstp);
  return -EIO;
#endif
}

/****************************************************************************
 * Name: ra_i2c_slave_deinit
 *
 * Description:
 *   Deinitialize the I2C slave hardware
 *
 ****************************************************************************/

static int ra_i2c_slave_deinit(struct ra_i2c_slave_priv_s *priv)
{
  const struct ra_i2c_config_s *config = priv->config;

  /* Disable I2C peripheral */

  ra_i2c_slave_modifyreg(priv, R_IIC_ICCR1_OFFSET, R_IIC_ICCR1_ICE, 0);

  /* Disable all interrupts */

  ra_i2c_slave_putreg(priv, R_IIC_ICIER_OFFSET, 0);

#ifndef CONFIG_I2C_POLLED
  /* Detach interrupt handlers via ICU using ELC events */

  ra_icu_detach(config->eri_elc);
  ra_icu_detach(config->tei_elc);
  ra_icu_detach(config->txi_elc);
  ra_icu_detach(config->rxi_elc);

  /* Clear runtime IRQ numbers */

  priv->rxi_irq = 0;
  priv->txi_irq = 0;
  priv->tei_irq = 0;
  priv->eri_irq = 0;
#endif

  /* Disable I2C module clock */

  ra_mstp_stop(config->mstp);

  return OK;
}

#ifndef CONFIG_I2C_POLLED
/****************************************************************************
 * Name: ra_i2c_slave_isr_rxi
 *
 * Description:
 *   I2C slave RX interrupt service routine
 *   Called when master sends data to slave (slave receive mode)
 *
 ****************************************************************************/

static int ra_i2c_slave_isr_rxi(int irq, void *context, void *arg)
{
  struct ra_i2c_slave_priv_s *priv = (struct ra_i2c_slave_priv_s *)arg;
  uint8_t data;

  DEBUGASSERT(priv != NULL);

  /* Read received data from ICDRR register */

  data = ra_i2c_slave_getreg(priv, R_IIC_ICDRR_OFFSET);

  /* Store in RX buffer if available */

  if (priv->rx_buffer != NULL && priv->rx_nbytes < priv->rx_buflen)
    {
      priv->rx_buffer[priv->rx_nbytes++] = data;
    }

  /* Call callback if registered */

  if (priv->callback != NULL)
    {
      priv->callback(priv->callback_arg, I2C_SLAVE_READ);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_slave_isr_txi
 *
 * Description:
 *   I2C slave TX interrupt service routine
 *   Called when master requests data from slave (slave transmit mode)
 *
 ****************************************************************************/

static int ra_i2c_slave_isr_txi(int irq, void *context, void *arg)
{
  struct ra_i2c_slave_priv_s *priv = (struct ra_i2c_slave_priv_s *)arg;

  DEBUGASSERT(priv != NULL);

  /* Send data from TX buffer if available */

  if (priv->tx_buffer != NULL && priv->tx_nbytes < priv->tx_buflen)
    {
      ra_i2c_slave_putreg(priv, R_IIC_ICDRT_OFFSET,
                          priv->tx_buffer[priv->tx_nbytes++]);
    }
  else
    {
      /* No more data - send dummy byte (0xFF is common for no data) */

      ra_i2c_slave_putreg(priv, R_IIC_ICDRT_OFFSET, 0xff);
    }

  /* Call callback if registered */

  if (priv->callback != NULL)
    {
      priv->callback(priv->callback_arg, I2C_SLAVE_WRITE);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_slave_isr_tei
 *
 * Description:
 *   I2C slave transfer end interrupt service routine
 *   Called when transmit data has been sent (TEND flag set)
 *
 ****************************************************************************/

static int ra_i2c_slave_isr_tei(int irq, void *context, void *arg)
{
  struct ra_i2c_slave_priv_s *priv = (struct ra_i2c_slave_priv_s *)arg;

  DEBUGASSERT(priv != NULL);

  /* Wake up TX waiting thread - transmission complete */

  nxsem_post(&priv->sem_tx);

  /* Call callback if registered */

  if (priv->callback != NULL)
    {
      priv->callback(priv->callback_arg, I2C_SLAVE_STOP);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_slave_isr_eri
 *
 * Description:
 *   I2C slave error interrupt service routine
 *   Handles: Stop condition (SP), NACK, Arbitration Lost (AL), Timeout
 *
 ****************************************************************************/

static int ra_i2c_slave_isr_eri(int irq, void *context, void *arg)
{
  struct ra_i2c_slave_priv_s *priv = (struct ra_i2c_slave_priv_s *)arg;
  uint8_t sr2;

  DEBUGASSERT(priv != NULL);

  /* Read status to determine event/error type */

  sr2 = ra_i2c_slave_getreg(priv, R_IIC_ICSR2_OFFSET);
  priv->status = sr2;

  /* Check for stop condition - this is normal end of transfer */

  if (sr2 & R_IIC_ICSR2_STOP)
    {
      /* Clear stop flag */

      ra_i2c_slave_modifyreg(priv, R_IIC_ICSR2_OFFSET, R_IIC_ICSR2_STOP, 0);

      /* Wake up RX and TX waiting threads */

      nxsem_post(&priv->sem_rx);
      nxsem_post(&priv->sem_tx);

      /* Call callback if registered */

      if (priv->callback != NULL)
        {
          priv->callback(priv->callback_arg, I2C_SLAVE_STOP);
        }
    }

  /* Check for NACK from master (normal for last byte in read) */

  if (sr2 & R_IIC_ICSR2_NACKF)
    {
      /* Clear NACK flag */

      ra_i2c_slave_modifyreg(priv, R_IIC_ICSR2_OFFSET, R_IIC_ICSR2_NACKF, 0);

      /* This is typically the end of a slave transmit transfer */

      nxsem_post(&priv->sem_tx);
    }

  /* Check for arbitration lost */

  if (sr2 & R_IIC_ICSR2_AL)
    {
      /* Clear AL flag */

      ra_i2c_slave_modifyreg(priv, R_IIC_ICSR2_OFFSET, R_IIC_ICSR2_AL, 0);

      /* Wake up waiting threads with error */

      nxsem_post(&priv->sem_rx);
      nxsem_post(&priv->sem_tx);

      /* Call callback if registered */

      if (priv->callback != NULL)
        {
          priv->callback(priv->callback_arg, I2C_SLAVE_ERROR);
        }
    }

  /* Check for timeout */

  if (sr2 & R_IIC_ICSR2_TMOF)
    {
      /* Clear timeout flag */

      ra_i2c_slave_modifyreg(priv, R_IIC_ICSR2_OFFSET, R_IIC_ICSR2_TMOF, 0);

      /* Wake up waiting threads with error */

      nxsem_post(&priv->sem_rx);
      nxsem_post(&priv->sem_tx);

      /* Call callback if registered */

      if (priv->callback != NULL)
        {
          priv->callback(priv->callback_arg, I2C_SLAVE_ERROR);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_slave_isr_start
 *
 * Description:
 *   I2C slave start condition detection handler
 *   Note: This is called from ERI handler when start condition is detected.
 *   Not a separate interrupt on RA8 IIC peripheral.
 *
 ****************************************************************************/

static int ra_i2c_slave_isr_start(int irq, void *context, void *arg)
{
  struct ra_i2c_slave_priv_s *priv = (struct ra_i2c_slave_priv_s *)arg;

  DEBUGASSERT(priv != NULL);

  /* Clear start flag */

  ra_i2c_slave_modifyreg(priv, R_IIC_ICSR2_OFFSET, R_IIC_ICSR2_START, 0);

  /* Reset transfer counters for new transfer */

  priv->rx_nbytes = 0;
  priv->tx_nbytes = 0;

  /* Call callback if registered */

  if (priv->callback != NULL)
    {
      priv->callback(priv->callback_arg, I2C_SLAVE_START);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_slave_isr_stop
 *
 * Description:
 *   I2C slave stop condition detection handler
 *   Note: This is called from ERI handler when stop condition is detected.
 *   Not a separate interrupt on RA8 IIC peripheral.
 *
 ****************************************************************************/

static int ra_i2c_slave_isr_stop(int irq, void *context, void *arg)
{
  struct ra_i2c_slave_priv_s *priv = (struct ra_i2c_slave_priv_s *)arg;

  DEBUGASSERT(priv != NULL);

  /* Clear stop flag */

  ra_i2c_slave_modifyreg(priv, R_IIC_ICSR2_OFFSET, R_IIC_ICSR2_STOP, 0);

  /* Call callback if registered */

  if (priv->callback != NULL)
    {
      priv->callback(priv->callback_arg, I2C_SLAVE_STOP);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_i2c_slave_isr_address
 *
 * Description:
 *   I2C slave address match handler
 *   Note: Called when slave address is matched (AAS flag).
 *
 ****************************************************************************/

static int ra_i2c_slave_isr_address(int irq, void *context, void *arg)
{
  struct ra_i2c_slave_priv_s *priv = (struct ra_i2c_slave_priv_s *)arg;
  uint8_t sr1;

  DEBUGASSERT(priv != NULL);

  /* Read status to determine which address matched */

  sr1 = ra_i2c_slave_getreg(priv, R_IIC_ICSR1_OFFSET);

  /* Clear address match flags */

  ra_i2c_slave_modifyreg(priv, R_IIC_ICSR1_OFFSET,
                        R_IIC_ICSR1_AAS0 | R_IIC_ICSR1_AAS1 | R_IIC_ICSR1_AAS2, 0);

  /* Reset transfer counters for new transfer */

  priv->rx_nbytes = 0;
  priv->tx_nbytes = 0;

  /* Call callback if registered */

  if (priv->callback != NULL)
    {
      priv->callback(priv->callback_arg, I2C_SLAVE_ADDRESS);
    }

  return OK;
}
#endif /* !CONFIG_I2C_POLLED */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_i2c_slave_initialize
 *
 * Description:
 *   Initialize the selected I2C port in slave mode. And return a unique
 *   instance of struct i2c_slave_s.
 *
 * Input Parameters:
 *   Port number (for hardware that has multiple I2C interfaces)
 *
 * Returned Value:
 *   Valid I2C slave device structure reference on success; a NULL on failure
 *
 ****************************************************************************/

struct i2c_slave_s *ra_i2c_slave_initialize(int port)
{
  struct ra_i2c_slave_priv_s *priv = NULL;

  i2cinfo("I2C%d slave: Initialize\n", port);

  /* Get I2C slave private structure */
  switch (port)
    {
#ifdef CONFIG_RA_I2C0_SLAVE
      case 0:
        priv = &ra_i2c0_slave_priv;
        break;
#endif

#ifdef CONFIG_RA_I2C1_SLAVE
      case 1:
        priv = &ra_i2c1_slave_priv;
        break;
#endif

      default:
        i2cerr("I2C%d slave: Invalid port\n", port);
        return NULL;
    }

  /* Initialize the device structure */
  if (priv->refs++ == 0)
    {
      /* Initialize the I2C slave hardware */
      ra_i2c_slave_init(priv);
    }

  return (struct i2c_slave_s *)priv;
}

/****************************************************************************
 * Name: ra_i2c_slave_uninitialize
 *
 * Description:
 *   De-initialize the selected I2C port in slave mode, and power down the device.
 *
 * Input Parameters:
 *   Device structure as returned by ra_i2c_slave_initialize()
 *
 * Returned Value:
 *   OK on success, ERROR when internal reference count mismatch or dev
 *   points to invalid hardware device.
 *
 ****************************************************************************/

int ra_i2c_slave_uninitialize(struct i2c_slave_s *dev)
{
  struct ra_i2c_slave_priv_s *priv = (struct ra_i2c_slave_priv_s *)dev;

  DEBUGASSERT(priv != NULL);

  /* Decrement reference count and check if we should disable the peripheral */
  if (--priv->refs == 0)
    {
      /* Disable the I2C slave hardware */
      ra_i2c_slave_deinit(priv);
    }

  return OK;
}

#endif /* CONFIG_RA_I2C_SLAVE */

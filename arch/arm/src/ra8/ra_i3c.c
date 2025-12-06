/****************************************************************************
 * arch/arm/src/ra8/ra_i3c.c
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

#include <nuttx/arch.h>
#include <nuttx/irq.h>
#include <nuttx/mutex.h>
#include <nuttx/semaphore.h>
#include <nuttx/fs/fs.h>

#include "arm_internal.h"
#include "chip.h"
#include "ra_i3c.h"
#include "ra_mstp.h"
#include "ra_icu.h"
#include "hardware/ra8p1/ra_i3c.h"

#ifdef CONFIG_RA_I3C

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define I3C_TIMEOUT_MS 1000
#define I3C_STATE_TIMEOUT_US 100000

/* Debug macros */

#ifdef CONFIG_DEBUG_I3C_ERROR
#  define i3cerr(format, ...)  _err(format, ##__VA_ARGS__)
#else
#  define i3cerr(format, ...)
#endif

#ifdef CONFIG_DEBUG_I3C_WARN
#  define i3cwarn(format, ...) _warn(format, ##__VA_ARGS__)
#else
#  define i3cwarn(format, ...)
#endif

#ifdef CONFIG_DEBUG_I3C_INFO
#  define i3cinfo(format, ...) _info(format, ##__VA_ARGS__)
#else
#  define i3cinfo(format, ...)
#endif

/* I3C State Machine States */
enum ra_i3cstate_e
{
  I3CSTATE_IDLE = 0,      /* No I3C activity */
  I3CSTATE_CMD_QUEUE,     /* Command queued */
  I3CSTATE_TRANSFER,      /* Transfer in progress */
  I3CSTATE_WAIT_RESP,     /* Waiting for response */
  I3CSTATE_ERROR,         /* Error occurred */
  I3CSTATE_FINISH         /* Transfer finished */
};

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* I3C Device hardware configuration */
struct ra_i3c_config_s
{
  uint32_t base;          /* I3C base address */
  uint32_t mstp;          /* Module stop control (mstp) */
  uint8_t  bus;           /* I3C bus number */
  uint32_t resp_elc;      /* Response Queue ELC event */
  uint32_t rx_elc;        /* Receive Queue ELC event */
  uint32_t tx_elc;        /* Transmit Queue ELC event */
  uint32_t ibi_elc;       /* IBI Queue ELC event */
  uint32_t rcv_elc;       /* Receive Status Queue ELC event */
  uint32_t terr_elc;      /* Transfer Error ELC event */
};

/* I3C Device Private Data */
struct ra_i3c_priv_s
{
  const struct ra_i3c_config_s *config; /* Port configuration */
  int      refs;                      /* Reference count */
  mutex_t  lock;                      /* Mutual exclusion mutex */
  sem_t    sem_isr;                   /* Interrupt wait semaphore */
  int      bus;                       /* Bus number */

  /* I3C work state */
  volatile uint8_t state;

  /* I3C current message */
  struct i3c_msg_s *msgs;             /* Remaining transfers */
  int      msgc;                      /* Number of transfers remaining */

  /* I3C transfer state */
  uint8_t *ptr;                       /* Current message buffer */
  uint32_t dcnt;                      /* Current message length */
  uint16_t flags;                     /* Current message flags */

  /* I3C address */
  uint8_t  addr;                      /* Current message address */

  /* Interrupt numbers assigned at runtime */
  int      resp_irq;
  int      rx_irq;
  int      tx_irq;
  int      ibi_irq;
  int      rcv_irq;
  int      terr_irq;

  volatile uint32_t status;           /* Transfer status */
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int ra_i3c_transfer(struct ra_i3c_priv_s *priv,
                           struct i3c_msg_s *msgs, int count);
static int ra_i3c_init(struct ra_i3c_priv_s *priv);
static int ra_i3c_deinit(struct ra_i3c_priv_s *priv);

/* I3C helper functions */
static int ra_i3c_sendcmd(struct ra_i3c_priv_s *priv, uint8_t addr,
                          bool readmode, uint32_t len);
static int ra_i3c_wait_event(struct ra_i3c_priv_s *priv, uint32_t timeout_us);

/* I3C interrupt service routines */
static int ra_i3c_isr_resp(int irq, void *context, void *arg);
static int ra_i3c_isr_rx(int irq, void *context, void *arg);
static int ra_i3c_isr_tx(int irq, void *context, void *arg);
static int ra_i3c_isr_rcv(int irq, void *context, void *arg);
static int ra_i3c_isr_terr(int irq, void *context, void *arg);

/****************************************************************************
 * Private Data
 ****************************************************************************/

#ifdef CONFIG_RA_I3C0
static const struct ra_i3c_config_s ra_i3c0_config =
{
  .base     = R_I3C_CH_BASE(0),
  .mstp     = RA_MSTP_I3C0,
  .bus      = 0,
  .resp_elc = RA_ELC_I3C0_RESP,
  .rx_elc   = RA_ELC_I3C0_RX,
  .tx_elc   = RA_ELC_I3C0_TX,
  .ibi_elc  = RA_ELC_I3C0_IBI,
  .rcv_elc  = RA_ELC_I3C0_RCV,
  .terr_elc = RA_ELC_I3C0_TERR,
};

static struct ra_i3c_priv_s ra_i3c0_priv =
{
  .config   = &ra_i3c0_config,
  .refs     = 0,
  .lock     = NXMUTEX_INITIALIZER,
  .sem_isr  = SEM_INITIALIZER(0),
  .bus      = 0,
  .state    = I3CSTATE_IDLE,
};
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static inline uint32_t ra_i3c_getreg(struct ra_i3c_priv_s *priv, uint32_t offset)
{
  return getreg32(priv->config->base + offset);
}

static inline void ra_i3c_putreg(struct ra_i3c_priv_s *priv, uint32_t offset, uint32_t value)
{
  putreg32(value, priv->config->base + offset);
}

/****************************************************************************
 * Name: ra_i3c_wait_event
 *
 * Description:
 *   Wait for I3C event
 *
 ****************************************************************************/

static int ra_i3c_wait_event(struct ra_i3c_priv_s *priv, uint32_t timeout_us)
{
  /* Wait for interrupt */
  return nxsem_tickwait_uninterruptible(&priv->sem_isr, USEC2TICK(timeout_us));
}

/****************************************************************************
 * Name: ra_i3c_sendcmd
 *
 * Description:
 *   Send I3C command to command queue
 *
 ****************************************************************************/

static int ra_i3c_sendcmd(struct ra_i3c_priv_s *priv, uint8_t addr,
                          bool readmode, uint32_t len)
{
  uint32_t cmd = 0;

  /* Build command word for Normal Command Queue
   * Simplified command format:
   * - Bits [7:0]: Device address (7-bit address shifted)
   * - Bit 8: RnW (1=read, 0=write)
   * - Bits [31:16]: Transfer length
   */

  cmd = (addr << 1) | (readmode ? 1 : 0);
  cmd |= (len << 16);

  /* Write to Normal Command Queue Port */
  ra_i3c_putreg(priv, R_I3C_NCMDQP_OFFSET, cmd);

  priv->state = I3CSTATE_CMD_QUEUE;

  return OK;
}

/****************************************************************************
 * Name: ra_i3c_isr_resp
 *
 * Description:
 *   I3C Response Queue interrupt service routine
 *
 ****************************************************************************/

static int ra_i3c_isr_resp(int irq, void *context, void *arg)
{
  struct ra_i3c_priv_s *priv = (struct ra_i3c_priv_s *)arg;
  uint32_t response;

  /* Read response from queue */
  response = ra_i3c_getreg(priv, R_I3C_NRSPQP_OFFSET);

  /* Store status */
  priv->status = response;

  /* Signal semaphore to wake up waiting thread */
  nxsem_post(&priv->sem_isr);

  return OK;
}

/****************************************************************************
 * Name: ra_i3c_isr_rx
 *
 * Description:
 *   I3C RX Data Buffer interrupt service routine
 *
 ****************************************************************************/

static int ra_i3c_isr_rx(int irq, void *context, void *arg)
{
  struct ra_i3c_priv_s *priv = (struct ra_i3c_priv_s *)arg;

  /* Read data from RX buffer */
  if (priv->ptr && priv->dcnt > 0)
    {
      uint32_t data = ra_i3c_getreg(priv, R_I3C_NTDTBP0_OFFSET);

      /* Copy bytes from data word */
      for (int i = 0; i < 4 && priv->dcnt > 0; i++)
        {
          *priv->ptr++ = (data >> (i * 8)) & 0xFF;
          priv->dcnt--;
        }
    }

  /* Signal semaphore if transfer complete */
  if (priv->dcnt == 0)
    {
      nxsem_post(&priv->sem_isr);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_i3c_isr_tx
 *
 * Description:
 *   I3C TX Data Buffer interrupt service routine
 *
 ****************************************************************************/

static int ra_i3c_isr_tx(int irq, void *context, void *arg)
{
  struct ra_i3c_priv_s *priv = (struct ra_i3c_priv_s *)arg;

  /* Write data to TX buffer */
  if (priv->ptr && priv->dcnt > 0)
    {
      uint32_t data = 0;

      /* Pack bytes into data word */
      for (int i = 0; i < 4 && priv->dcnt > 0; i++)
        {
          data |= (*priv->ptr++) << (i * 8);
          priv->dcnt--;
        }

      ra_i3c_putreg(priv, R_I3C_NTDTBP0_OFFSET, data);
    }

  /* Signal semaphore if transfer complete */
  if (priv->dcnt == 0)
    {
      nxsem_post(&priv->sem_isr);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_i3c_isr_rcv
 *
 * Description:
 *   I3C Receive Status Queue interrupt service routine
 *
 ****************************************************************************/

static int ra_i3c_isr_rcv(int irq, void *context, void *arg)
{
  struct ra_i3c_priv_s *priv = (struct ra_i3c_priv_s *)arg;
  uint32_t status;

  /* Read receive status from queue */
  status = ra_i3c_getreg(priv, R_I3C_NRSQP_OFFSET);
  priv->status = status;

  nxsem_post(&priv->sem_isr);

  return OK;
}

/****************************************************************************
 * Name: ra_i3c_isr_terr
 *
 * Description:
 *   I3C Transfer Error interrupt service routine
 *
 ****************************************************************************/

static int ra_i3c_isr_terr(int irq, void *context, void *arg)
{
  struct ra_i3c_priv_s *priv = (struct ra_i3c_priv_s *)arg;
  uint32_t status;

  /* Read and clear error status */
  status = ra_i3c_getreg(priv, R_I3C_NTST_OFFSET);
  priv->status = status;
  ra_i3c_putreg(priv, R_I3C_NTST_OFFSET, status);

  priv->state = I3CSTATE_ERROR;

  nxsem_post(&priv->sem_isr);

  return OK;
}

/****************************************************************************
 * Name: ra_i3c_transfer
 *
 * Description:
 *   Generic I3C transfer function
 *
 ****************************************************************************/

static int ra_i3c_transfer(struct ra_i3c_priv_s *priv,
                           struct i3c_msg_s *msgs, int count)
{
  int ret = OK;
  int i;

  DEBUGASSERT(priv != NULL && msgs != NULL && count > 0);

  /* Get exclusive access to the I3C bus */
  ret = nxmutex_lock(&priv->lock);
  if (ret < 0)
    {
      return ret;
    }

  /* Process each message */
  for (i = 0; i < count && ret == OK; i++)
    {
      /* Setup transfer state */
      priv->msgs = &msgs[i];
      priv->msgc = 1;
      priv->ptr = msgs[i].buffer;
      priv->dcnt = msgs[i].length;
      priv->flags = msgs[i].flags;
      priv->addr = msgs[i].addr;

      /* Send command to command queue */
      ret = ra_i3c_sendcmd(priv, msgs[i].addr,
                           (msgs[i].flags & I3C_M_READ) != 0,
                           msgs[i].length);
      if (ret != OK)
        {
          i3cerr("ERROR: Failed to send command\n");
          break;
        }

      /* Wait for command to be accepted */
      ret = ra_i3c_wait_event(priv, I3C_STATE_TIMEOUT_US);
      if (ret != OK)
        {
          i3cerr("ERROR: Command timeout\n");
          break;
        }

      /* For write transfers, wait for TX completion */
      if (!(msgs[i].flags & I3C_M_READ))
        {
          ret = ra_i3c_wait_event(priv, I3C_STATE_TIMEOUT_US);
          if (ret != OK)
            {
              i3cerr("ERROR: TX timeout\n");
              break;
            }
        }
      else
        {
          /* For read transfers, wait for RX completion */
          ret = ra_i3c_wait_event(priv, I3C_STATE_TIMEOUT_US);
          if (ret != OK)
            {
              i3cerr("ERROR: RX timeout\n");
              break;
            }
        }

      /* Wait for response */
      ret = ra_i3c_wait_event(priv, I3C_STATE_TIMEOUT_US);
      if (ret != OK)
        {
          i3cerr("ERROR: Response timeout\n");
          break;
        }

      /* Check for errors */
      if (priv->state == I3CSTATE_ERROR)
        {
          i3cerr("ERROR: Transfer error, status=0x%08lx\n",
                 (unsigned long)priv->status);
          ret = -EIO;
          break;
        }
    }

  /* Reset state */
  priv->state = I3CSTATE_IDLE;

  nxmutex_unlock(&priv->lock);

  return ret;
}

static int ra_i3c_init(struct ra_i3c_priv_s *priv)
{
  const struct ra_i3c_config_s *config = priv->config;

  i3cinfo("Initializing I3C%d\n", config->bus);

  /* Enable I3C module clock */
  ra_mstp_start(config->mstp);

  /* Reset I3C peripheral */
  ra_i3c_putreg(priv, R_I3C_RSTCTL_OFFSET, R_I3C_RSTCTL_PDRST);
  up_udelay(10);
  ra_i3c_putreg(priv, R_I3C_RSTCTL_OFFSET, 0);

  /* Enable clock */
  ra_i3c_putreg(priv, R_I3C_CECTL_OFFSET, R_I3C_CECTL_CLKE);

  /* Configure bus control - Enable bus in master mode */
  ra_i3c_putreg(priv, R_I3C_BCTL_OFFSET, R_I3C_BCTL_BUSE);

  /* Set master device address (if needed) */
  ra_i3c_putreg(priv, R_I3C_MSDVAD_OFFSET, 0);

  /* Configure protocol selection for I3C mode */
  ra_i3c_putreg(priv, R_I3C_PRTS_OFFSET, R_I3C_PRTS_PRTMD);

  /* Configure bit rates (use default values for now) */
  ra_i3c_putreg(priv, R_I3C_STDBR_OFFSET, 0);
  ra_i3c_putreg(priv, R_I3C_EXTBR_OFFSET, 0);

  /* Configure queue thresholds */
  ra_i3c_putreg(priv, R_I3C_NQTHCTL_OFFSET, 0);
  ra_i3c_putreg(priv, R_I3C_NTBTHCTL0_OFFSET, 0);

  /* Attach interrupt handlers */
  priv->resp_irq = ra_icu_attach(config->resp_elc, ra_i3c_isr_resp, priv, true);
  priv->rx_irq = ra_icu_attach(config->rx_elc, ra_i3c_isr_rx, priv, true);
  priv->tx_irq = ra_icu_attach(config->tx_elc, ra_i3c_isr_tx, priv, true);
  priv->rcv_irq = ra_icu_attach(config->rcv_elc, ra_i3c_isr_rcv, priv, true);
  priv->terr_irq = ra_icu_attach(config->terr_elc, ra_i3c_isr_terr, priv, true);

  if (priv->resp_irq < 0 || priv->rx_irq < 0 || priv->tx_irq < 0 ||
      priv->rcv_irq < 0 || priv->terr_irq < 0)
    {
      i3cerr("ERROR: Failed to attach interrupts\n");
      return -EIO;
    }

  /* Enable Normal Transfer interrupts */
  ra_i3c_putreg(priv, R_I3C_NTIE_OFFSET, 0xFFFFFFFF);

  /* Enable Normal Transfer Status */
  ra_i3c_putreg(priv, R_I3C_NTSTE_OFFSET, 0xFFFFFFFF);

  priv->state = I3CSTATE_IDLE;

  i3cinfo("I3C%d initialization complete\n", config->bus);

  return OK;
}

static int ra_i3c_deinit(struct ra_i3c_priv_s *priv)
{
  const struct ra_i3c_config_s *config = priv->config;

  i3cinfo("De-initializing I3C%d\n", config->bus);

  /* Disable interrupts */
  ra_i3c_putreg(priv, R_I3C_NTIE_OFFSET, 0);
  ra_i3c_putreg(priv, R_I3C_NTSTE_OFFSET, 0);

  /* Detach interrupt handlers */
  if (priv->resp_irq >= 0)
    {
      ra_icu_detach(priv->resp_irq);
    }
  if (priv->rx_irq >= 0)
    {
      ra_icu_detach(priv->rx_irq);
    }
  if (priv->tx_irq >= 0)
    {
      ra_icu_detach(priv->tx_irq);
    }
  if (priv->rcv_irq >= 0)
    {
      ra_icu_detach(priv->rcv_irq);
    }
  if (priv->terr_irq >= 0)
    {
      ra_icu_detach(priv->terr_irq);
    }

  /* Disable bus */
  ra_i3c_putreg(priv, R_I3C_BCTL_OFFSET, 0);

  /* Reset I3C peripheral */
  ra_i3c_putreg(priv, R_I3C_RSTCTL_OFFSET, R_I3C_RSTCTL_PDRST);
  up_udelay(10);
  ra_i3c_putreg(priv, R_I3C_RSTCTL_OFFSET, 0);

  /* Disable I3C module clock */
  ra_mstp_stop(config->mstp);

  priv->state = I3CSTATE_IDLE;

  i3cinfo("I3C%d de-initialization complete\n", config->bus);

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int ra_i3cbus_initialize(int port)
{
  struct ra_i3c_priv_s *priv = NULL;
  int ret;

#ifdef CONFIG_RA_I3C0
  if (port == 0)
    {
      priv = &ra_i3c0_priv;
    }
  else
#endif
    {
      i3cerr("ERROR: Unsupported I3C port %d\n", port);
      return -ENODEV;
    }

  ret = nxmutex_lock(&priv->lock);
  if (ret < 0)
    {
      return ret;
    }

  if (priv->refs++ == 0)
    {
      ret = ra_i3c_init(priv);
      if (ret < 0)
        {
          priv->refs--;
          nxmutex_unlock(&priv->lock);
          return ret;
        }
    }

  nxmutex_unlock(&priv->lock);

  return OK;
}

int ra_i3cbus_uninitialize(int port)
{
  struct ra_i3c_priv_s *priv = NULL;
  int ret;

#ifdef CONFIG_RA_I3C0
  if (port == 0)
    {
      priv = &ra_i3c0_priv;
    }
  else
#endif
    {
      return -ENODEV;
    }

  ret = nxmutex_lock(&priv->lock);
  if (ret < 0)
    {
      return ret;
    }

  if (--priv->refs == 0)
    {
      ret = ra_i3c_deinit(priv);
    }

  nxmutex_unlock(&priv->lock);

  return ret;
}

int ra_i3cbus_transfer(int port, struct i3c_msg_s *msgs, int count)
{
  struct ra_i3c_priv_s *priv = NULL;

#ifdef CONFIG_RA_I3C0
  if (port == 0)
    {
      priv = &ra_i3c0_priv;
    }
  else
#endif
    {
      return -ENODEV;
    }

  if (priv == NULL || msgs == NULL || count <= 0)
    {
      return -EINVAL;
    }

  return ra_i3c_transfer(priv, msgs, count);
}

#endif /* CONFIG_RA_I3C */


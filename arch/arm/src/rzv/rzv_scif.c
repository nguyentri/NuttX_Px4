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

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCIF Register Offsets (same as in rzv_lowputc.c) */
#define RZV_SCIF_SMR_OFFSET      0x00
#define RZV_SCIF_BRR_OFFSET      0x02
#define RZV_SCIF_SCR_OFFSET      0x04
#define RZV_SCIF_FTDR_OFFSET     0x06
#define RZV_SCIF_FSR_OFFSET      0x08
#define RZV_SCIF_FRDR_OFFSET     0x0A
#define RZV_SCIF_FCR_OFFSET      0x0C
#define RZV_SCIF_FDR_OFFSET      0x0E
#define RZV_SCIF_SPTR_OFFSET     0x10
#define RZV_SCIF_LSR_OFFSET      0x12

/* Register bit definitions */
#define SCIF_SMR_CKS_MASK        0x0003
#define SCIF_SMR_STOP            0x0008
#define SCIF_SMR_PM              0x0010
#define SCIF_SMR_PE              0x0020
#define SCIF_SMR_CHR             0x0040

#define SCIF_SCR_RE              0x0010
#define SCIF_SCR_TE              0x0020
#define SCIF_SCR_RIE             0x0040
#define SCIF_SCR_TIE             0x0080
#define SCIF_SCR_REIE            0x0008
#define SCIF_SCR_TEIE            0x0004

#define SCIF_FSR_DR              0x0001
#define SCIF_FSR_RDF             0x0002
#define SCIF_FSR_PER             0x0004
#define SCIF_FSR_FER             0x0008
#define SCIF_FSR_BRK             0x0010
#define SCIF_FSR_TDFE            0x0020
#define SCIF_FSR_TEND            0x0040
#define SCIF_FSR_ER              0x0080

#define SCIF_FCR_LOOP            0x0001
#define SCIF_FCR_RFRST           0x0002
#define SCIF_FCR_TFRST           0x0004
#define SCIF_FCR_MCE             0x0008
#define SCIF_FCR_TTRG_MASK       0x0030
#define SCIF_FCR_RTRG_MASK       0x00C0

#define SCIF_LSR_ORER            0x0001

/* Which UART with be configured as the console */
#if defined(CONFIG_SCIF0_SERIAL_CONSOLE)
#  define CONSOLE_DEV     g_scif0port  /* SCIF0 is console */
#  define TTYS0_DEV       g_scif0port  /* SCIF0 is ttyS0 */
#  define SCIF0_ASSIGNED  1
#elif defined(CONFIG_SCIF1_SERIAL_CONSOLE)
#  define CONSOLE_DEV     g_scif1port  /* SCIF1 is console */
#  define TTYS0_DEV       g_scif1port  /* SCIF1 is ttyS0 */
#  define SCIF1_ASSIGNED  1
#elif defined(CONFIG_SCIF2_SERIAL_CONSOLE)
#  define CONSOLE_DEV     g_scif2port  /* SCIF2 is console */
#  define TTYS0_DEV       g_scif2port  /* SCIF2 is ttyS0 */
#  define SCIF2_ASSIGNED  1
#elif defined(CONFIG_SCIF3_SERIAL_CONSOLE)
#  define CONSOLE_DEV     g_scif3port  /* SCIF3 is console */
#  define TTYS0_DEV       g_scif3port  /* SCIF3 is ttyS0 */
#  define SCIF3_ASSIGNED  1
#else
#  undef CONSOLE_DEV                    /* No console */
#  if defined(CONFIG_RZV_SCIF0)
#    define TTYS0_DEV     g_scif0port  /* SCIF0 is ttyS0 */
#    define SCIF0_ASSIGNED  1
#  elif defined(CONFIG_RZV_SCIF1)
#    define TTYS0_DEV     g_scif1port  /* SCIF1 is ttyS0 */
#    define SCIF1_ASSIGNED  1
#  elif defined(CONFIG_RZV_SCIF2)
#    define TTYS0_DEV     g_scif2port  /* SCIF2 is ttyS0 */
#    define SCIF2_ASSIGNED  1
#  elif defined(CONFIG_RZV_SCIF3)
#    define TTYS0_DEV     g_scif3port  /* SCIF3 is ttyS0 */
#    define SCIF3_ASSIGNED  1
#  endif
#endif

/* Pick ttys1 */
#if defined(CONFIG_RZV_SCIF0) && !defined(SCIF0_ASSIGNED)
#  define TTYS1_DEV       g_scif0port  /* SCIF0 is ttyS1 */
#  define SCIF0_ASSIGNED  1
#elif defined(CONFIG_RZV_SCIF1) && !defined(SCIF1_ASSIGNED)
#  define TTYS1_DEV       g_scif1port  /* SCIF1 is ttyS1 */
#  define SCIF1_ASSIGNED  1
#elif defined(CONFIG_RZV_SCIF2) && !defined(SCIF2_ASSIGNED)
#  define TTYS1_DEV       g_scif2port  /* SCIF2 is ttyS1 */
#  define SCIF2_ASSIGNED  1
#elif defined(CONFIG_RZV_SCIF3) && !defined(SCIF3_ASSIGNED)
#  define TTYS1_DEV       g_scif3port  /* SCIF3 is ttyS1 */
#  define SCIF3_ASSIGNED  1
#endif

/* Pick ttys2 */
#if defined(CONFIG_RZV_SCIF0) && !defined(SCIF0_ASSIGNED)
#  define TTYS2_DEV       g_scif0port  /* SCIF0 is ttyS2 */
#  define SCIF0_ASSIGNED  1
#elif defined(CONFIG_RZV_SCIF1) && !defined(SCIF1_ASSIGNED)
#  define TTYS2_DEV       g_scif1port  /* SCIF1 is ttyS2 */
#  define SCIF1_ASSIGNED  1
#elif defined(CONFIG_RZV_SCIF2) && !defined(SCIF2_ASSIGNED)
#  define TTYS2_DEV       g_scif2port  /* SCIF2 is ttyS2 */
#  define SCIF2_ASSIGNED  1
#elif defined(CONFIG_RZV_SCIF3) && !defined(SCIF3_ASSIGNED)
#  define TTYS2_DEV       g_scif3port  /* SCIF3 is ttyS2 */
#  define SCIF3_ASSIGNED  1
#endif

/* Pick ttys3 */
#if defined(CONFIG_RZV_SCIF0) && !defined(SCIF0_ASSIGNED)
#  define TTYS3_DEV       g_scif0port  /* SCIF0 is ttyS3 */
#  define SCIF0_ASSIGNED  1
#elif defined(CONFIG_RZV_SCIF1) && !defined(SCIF1_ASSIGNED)
#  define TTYS3_DEV       g_scif1port  /* SCIF1 is ttyS3 */
#  define SCIF1_ASSIGNED  1
#elif defined(CONFIG_RZV_SCIF2) && !defined(SCIF2_ASSIGNED)
#  define TTYS3_DEV       g_scif2port  /* SCIF2 is ttyS3 */
#  define SCIF2_ASSIGNED  1
#elif defined(CONFIG_RZV_SCIF3) && !defined(SCIF3_ASSIGNED)
#  define TTYS3_DEV       g_scif3port  /* SCIF3 is ttyS3 */
#  define SCIF3_ASSIGNED  1
#endif

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct rzv_scif_s
{
  uintptr_t base;        /* SCIF register base address */
  uint32_t  baud;        /* Configured baud rate */
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
static int  rzv_scif_interrupt(int irq, void *context, void *arg);
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

#ifdef CONFIG_RZV_SCIF1
static char g_scif1rxbuffer[CONFIG_SCIF1_RXBUFSIZE];
static char g_scif1txbuffer[CONFIG_SCIF1_TXBUFSIZE];
#endif

#ifdef CONFIG_RZV_SCIF2
static char g_scif2rxbuffer[CONFIG_SCIF2_RXBUFSIZE];
static char g_scif2txbuffer[CONFIG_SCIF2_TXBUFSIZE];
#endif

#ifdef CONFIG_RZV_SCIF3
static char g_scif3rxbuffer[CONFIG_SCIF3_RXBUFSIZE];
static char g_scif3txbuffer[CONFIG_SCIF3_TXBUFSIZE];
#endif

/* SCIF device structures */

#ifdef CONFIG_RZV_SCIF0
static struct rzv_scif_s g_scif0priv =
{
  .base           = RZV_SCI0_BASE,
  .baud           = CONFIG_SCIF0_BAUD,
  .irq_rxi        = 0,  /* To be set via ICU */
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

#ifdef CONFIG_RZV_SCIF1
static struct rzv_scif_s g_scif1priv =
{
  .base           = RZV_SCI1_BASE,
  .baud           = CONFIG_SCIF1_BAUD,
  .irq_rxi        = 0,
  .irq_txi        = 0,
  .irq_tei        = 0,
  .irq_eri        = 0,
  .parity         = CONFIG_SCIF1_PARITY,
  .bits           = CONFIG_SCIF1_BITS,
  .stopbits2      = CONFIG_SCIF1_2STOP,
#ifdef CONFIG_SCIF1_IFLOWCONTROL
  .iflow          = true,
#endif
#ifdef CONFIG_SCIF1_OFLOWCONTROL
  .oflow          = true,
#endif
};

static uart_dev_t g_scif1port =
{
  .recv     =
  {
    .size   = CONFIG_SCIF1_RXBUFSIZE,
    .buffer = g_scif1rxbuffer,
  },
  .xmit     =
  {
    .size   = CONFIG_SCIF1_TXBUFSIZE,
    .buffer = g_scif1txbuffer,
  },
  .ops      = &g_scif_ops,
  .priv     = &g_scif1priv,
};
#endif

/* Additional SCIF2 and SCIF3 structures would follow same pattern */

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_scif_setbaud
 ****************************************************************************/

static void rzv_scif_setbaud(struct rzv_scif_s *priv)
{
  uint32_t pclk;
  uint32_t divisor;
  uint8_t brr;
  uint8_t cks;
  uint8_t smr;

  /* Get peripheral clock frequency */
  pclk = rzv_get_pclk_frequency();

  /* Calculate divisor */
  for (cks = 0; cks <= 3; cks++)
    {
      divisor = pclk / (32 * (1 << (2 * cks)) * priv->baud);
      if (divisor > 0 && divisor <= 256)
        {
          brr = (uint8_t)(divisor - 1);
          break;
        }
    }

  if (cks > 3)
    {
      cks = 0;
      brr = 0;
    }

  /* Set bit rate register */
  putreg8(brr, priv->base + RZV_SCIF_BRR_OFFSET);

  /* Update SMR clock select */
  smr = getreg8(priv->base + RZV_SCIF_SMR_OFFSET);
  smr = (smr & ~SCIF_SMR_CKS_MASK) | (cks & SCIF_SMR_CKS_MASK);
  putreg8(smr, priv->base + RZV_SCIF_SMR_OFFSET);

  /* Wait for at least 1 bit time */
  up_udelay((1000000 / priv->baud) + 1);
}

/****************************************************************************
 * Name: rzv_scif_setup
 ****************************************************************************/

static int rzv_scif_setup(struct uart_dev_s *dev)
{
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;
  uint8_t smr;
  uint16_t scr;
  uint16_t fcr;

  /* Disable transmit and receive */
  putreg16(0, priv->base + RZV_SCIF_SCR_OFFSET);

  /* Reset FIFOs */
  fcr = SCIF_FCR_TFRST | SCIF_FCR_RFRST;
  putreg16(fcr, priv->base + RZV_SCIF_FCR_OFFSET);
  up_udelay(100);

  /* Configure FIFO control register */
  fcr = 0x0030 | 0x0000;  /* TTRG=8 bytes, RTRG=1 byte */
  putreg16(fcr, priv->base + RZV_SCIF_FCR_OFFSET);

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

  putreg8(smr, priv->base + RZV_SCIF_SMR_OFFSET);

  /* Set baud rate */
  rzv_scif_setbaud(priv);

  /* Clear all status flags */
  putreg16(0, priv->base + RZV_SCIF_FSR_OFFSET);
  putreg16(0, priv->base + RZV_SCIF_LSR_OFFSET);

  /* Enable transmit and receive */
  scr = SCIF_SCR_TE | SCIF_SCR_RE;
  putreg16(scr, priv->base + RZV_SCIF_SCR_OFFSET);

  return OK;
}

/****************************************************************************
 * Name: rzv_scif_shutdown
 ****************************************************************************/

static void rzv_scif_shutdown(struct uart_dev_s *dev)
{
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;

  /* Disable transmit and receive */
  putreg16(0, priv->base + RZV_SCIF_SCR_OFFSET);
}

/****************************************************************************
 * Name: rzv_scif_attach
 ****************************************************************************/

static int rzv_scif_attach(struct uart_dev_s *dev)
{
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;
  int ret;

  /* Attach RXI interrupt */
  ret = irq_attach(priv->irq_rxi, rzv_scif_interrupt, dev);
  if (ret == OK)
    {
      /* Attach TXI interrupt */
      ret = irq_attach(priv->irq_txi, rzv_scif_interrupt, dev);
    }

  if (ret == OK)
    {
      /* Enable interrupts at the GIC level */
      up_enable_irq(priv->irq_rxi);
      up_enable_irq(priv->irq_txi);
    }

  return ret;
}

/****************************************************************************
 * Name: rzv_scif_detach
 ****************************************************************************/

static void rzv_scif_detach(struct uart_dev_s *dev)
{
  struct rzv_scif_s *priv = (struct rzv_scif_s *)dev->priv;

  /* Disable interrupts */
  up_disable_irq(priv->irq_rxi);
  up_disable_irq(priv->irq_txi);

  /* Detach interrupts */
  irq_detach(priv->irq_rxi);
  irq_detach(priv->irq_txi);
}

/****************************************************************************
 * Name: rzv_scif_interrupt
 ****************************************************************************/

static int rzv_scif_interrupt(int irq, void *context, void *arg)
{
  struct uart_dev_s *dev = (struct uart_dev_s *)arg;
  struct rzv_scif_s *priv;
  uint16_t fsr;

  DEBUGASSERT(dev != NULL && dev->priv != NULL);
  priv = (struct rzv_scif_s *)dev->priv;

  /* Get status register */
  fsr = getreg16(priv->base + RZV_SCIF_FSR_OFFSET);

  /* Handle receive interrupt */
  if (fsr & SCIF_FSR_RDF)
    {
      uart_recvchars(dev);

      /* Clear RDF flag */
      fsr &= ~SCIF_FSR_RDF;
      putreg16(fsr, priv->base + RZV_SCIF_FSR_OFFSET);
    }

  /* Handle transmit interrupt */
  if (fsr & SCIF_FSR_TDFE)
    {
      uart_xmitchars(dev);

      /* Clear TDFE flag */
      fsr &= ~SCIF_FSR_TDFE;
      putreg16(fsr, priv->base + RZV_SCIF_FSR_OFFSET);
    }

  /* Handle errors */
  if (fsr & (SCIF_FSR_ER | SCIF_FSR_BRK | SCIF_FSR_FER | SCIF_FSR_PER))
    {
      /* Clear error flags */
      fsr &= ~(SCIF_FSR_ER | SCIF_FSR_BRK | SCIF_FSR_FER | SCIF_FSR_PER);
      putreg16(fsr, priv->base + RZV_SCIF_FSR_OFFSET);
    }

  return OK;
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

  /* Clear DR flag */
  fsr &= ~SCIF_FSR_DR;
  putreg16(fsr, priv->base + RZV_SCIF_FSR_OFFSET);

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
  uint16_t fsr;

  /* Write character */
  putreg8((uint8_t)ch, priv->base + RZV_SCIF_FTDR_OFFSET);

  /* Clear TDFE flag */
  fsr = getreg16(priv->base + RZV_SCIF_FSR_OFFSET);
  fsr &= ~SCIF_FSR_TDFE;
  putreg16(fsr, priv->base + RZV_SCIF_FSR_OFFSET);
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

#ifdef TTYS1_DEV
  uart_register("/dev/ttyS1", &TTYS1_DEV);
#endif

#ifdef TTYS2_DEV
  uart_register("/dev/ttyS2", &TTYS2_DEV);
#endif

#ifdef TTYS3_DEV
  uart_register("/dev/ttyS3", &TTYS3_DEV);
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
/****************************************************************************
 * arch/arm/src/ra8/ra_spi.c
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
#include <nuttx/spi/spi.h>
#include <nuttx/power/pm.h>

#include <arch/board/board.h>
#include <arch/ra8/irq.h>

#include "arm_internal.h"
#include "chip.h"
#include "hardware/ra_memorymap.h"

#include "ra_clock.h"
#include "ra_dtc.h"
#include "ra_dmac.h"
#include "ra_mstp.h"
#include "ra_spi.h"
#include "ra_icu.h"

#include <nuttx/cache.h>

#ifdef CONFIG_RA_SPI

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Compatibility macros for SPB field values (data length) */
/* In RA SPI_B, SPB field is the actual bit count minus 1 */
#define R_SPI_B_SPCMD_SPB_4              (3 << R_SPI_B_SPCMD_SPB_SHIFT)    /* 4 bits */
#define R_SPI_B_SPCMD_SPB_8              (7 << R_SPI_B_SPCMD_SPB_SHIFT)    /* 8 bits */
#define R_SPI_B_SPCMD_SPB_16             (15 << R_SPI_B_SPCMD_SPB_SHIFT)   /* 16 bits */
#define R_SPI_B_SPCMD_SPB_20             (19 << R_SPI_B_SPCMD_SPB_SHIFT)   /* 20 bits */
#define R_SPI_B_SPCMD_SPB_24             (23 << R_SPI_B_SPCMD_SPB_SHIFT)   /* 24 bits */
#define R_SPI_B_SPCMD_SPB_32             (31 << R_SPI_B_SPCMD_SPB_SHIFT)   /* 32 bits */

/* Compatibility macros for BRDV field values */
#define R_SPI_B_SPCMD_BRDV_1             R_SPI_B_SPCMD_BRDV_01
#define R_SPI_B_SPCMD_BRDV_2             R_SPI_B_SPCMD_BRDV_10
#define R_SPI_B_SPCMD_BRDV_4             R_SPI_B_SPCMD_BRDV_11

/* Compatibility macros for SSLA field values */
#define R_SPI_B_SPCMD_SSLA_0             R_SPI_B_SPCMD_SSLA_000

/* SPCMD0 offset macro */
#define R_SPI_B_SPCMD0_OFFSET            R_SPI_B_SPCMD_OFFSET(0)

/* CS type compatibility (from ra_spi.h) */
#define R_SPI_B_CS_CLK_SYS               0    /* Clock synchronous operation (3-wire) */
#define R_SPI_B_CS_GPIO                  1    /* Use GPIO for chip select */
#define R_SPI_B_CS_HARDWARE              2    /* Use hardware SSx pin for chip select */

/* Max frequency (20 MHz) */
#define R_SPI_B_MAX_FREQUENCY            20000000
#define R_SPI_B_DEFAULT_FREQUENCY        1000000

/* Check if divider is out of range */
#define R_SPI_B_CLK_MAX_DIV (4096U)
#define R_SPI_B_CLK_MIN_DIV (2U)
#define R_SPI_B_CLK_N_DIV_MULTIPLIER (512U)

/* All clear flags for SPSRC register */
#define R_SPI_B_SPSRC_ALL_CLEAR          (R_SPI_B_SPSRC_SPDRFC | R_SPI_B_SPSRC_OVRFC | \
                    R_SPI_B_SPSRC_MODFC | R_SPI_B_SPSRC_PERFC | \
                    R_SPI_B_SPSRC_UDRFC | R_SPI_B_SPSRC_SPTEFC | \
                    R_SPI_B_SPSRC_CENDFC | R_SPI_B_SPSRC_SPRFC)

/* SPI timeout */
#define R_SPI_B_TIMEOUT_MS          1000

/* Default CS timing values */
#define R_SPI_B_CS_SETUP_DELAY          2         /* Default CS setup delay cycles */
#define R_SPI_B_CS_HOLD_DELAY           2         /* Default CS hold delay cycles */
#define R_SPI_B_CS_NEGATION_DELAY       0         /* Default CS negation delay cycles */

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* Note: CS management is now handled by application-specific */
/* ra_spi_select() function implementations that override the weak */
/* functions in this driver. Each application defines its own */
/* device configurations and CS handling logic. */

/* SPI Device hardware configuration */
struct ra_spi_config_s
{
  uint32_t base;          /* SPI peripheral base address */
  int bus;                /* SPI bus number */

  int  rxi_elc;           /* Event Link for RX interrupt */
  int  txi_elc;           /* Event Link for TX interrupt */
  int  tei_elc;           /* Event Link for Transfer end interrupt */
  int  eri_elc;           /* Event Link for Error interrupt */

  uint32_t mstpcrb_bit;   /* Module stop control bit */

  uint8_t ssl_select;  /* Valid values: 0, 1, 2, 3: CS control by Hardware; > 3: control by GPIO e.g: 0xFF */
  bool master_mode;       /* true: master, false: slave */
  bool use_dtc;           /* DTC channels and configuration */
  bool use_dma;           /* DMAC channels and configuration */
};

/* SPI Device Private Data */
struct ra_spi_priv_s
{
  /* Externally visible part of the SPI interface */
  struct spi_dev_s  spidev;

  /* Static configuration */
  const struct ra_spi_config_s *config;

  uint32_t devid;         /* Currently selected external device ID */

  /* Runtime IRQ numbers assigned by ICU */
  int                    rxi_irq;    /* RX interrupt number */
  int                    txi_irq;    /* TX interrupt number */
  int                    tei_irq;    /* Transfer end interrupt number */
  int                    eri_irq;    /* Error interrupt number */

  int                    refs;       /* Reference count */
  mutex_t                lock;       /* Held while chip is selected for mutual exclusion */

  /* Transfer state */
  sem_t                  waitsem;    /* Wait for transfer completion */
  const void            *txbuffer;   /* Source data */
  void                  *rxbuffer;   /* Destination data */
  size_t                 ntxwords;   /* Number of words to transfer */
  size_t                 nrxwords;   /* Number of words to receive */
  bool                   error;      /* Transfer error flag */

  /* Current transfer parameters */
  uint32_t               frequency;  /* Requested clock frequency */
  enum spi_mode_e        mode;       /* Current SPI mode */
  int                    nbits;      /* Number of bits per word */

#ifdef CONFIG_RA_DTC
  /* DTC transfer state */
  bool                   dtc_active; /* DTC transfer in progress */
  ra_dtc_info_t          dtc_tx_info; /* TX DTC transfer info */
  ra_dtc_info_t          dtc_rx_info; /* RX DTC transfer info */
#endif

#ifdef CONFIG_RA_DMAC
  /* DMA transfer state */
  bool                   dma_active;   /* DMA transfer in progress */
  ra_dmac_handle_t       dma_tx;       /* TX DMA handle */
  ra_dmac_handle_t       dma_rx;       /* RX DMA handle */
  volatile bool          dma_tx_done;  /* TX DMA completion flag */
  volatile bool          dma_rx_done;  /* RX DMA completion flag */
  int                    dma_tx_channel; /* Assigned TX DMA channel (-1 = dynamic) */
  int                    dma_rx_channel; /* Assigned RX DMA channel (-1 = dynamic) */
#endif

#ifdef CONFIG_PM
  struct pm_callback_s   pmcb;       /* PM callbacks */
#endif
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Low-level helpers */
static void ra_spi_putreg32(struct ra_spi_priv_s *priv, uint8_t offset, uint32_t value);
static uint32_t ra_spi_getreg32(struct ra_spi_priv_s *priv, uint8_t offset);

#ifdef CONFIG_RA_DTC
/* DTC support */
static int ra_spi_dtc_setup(struct ra_spi_priv_s *priv);
static void ra_spi_dtc_stop(struct ra_spi_priv_s *priv);
static int ra_spi_dtc_configure_transfer(struct ra_spi_priv_s *priv,
                    const void *txbuffer, void *rxbuffer,
                    size_t nwords);
static int ra_spi_dtc_reconfigure(struct ra_spi_priv_s *priv);
#endif

#ifdef CONFIG_RA_DMAC
/* DMAC support */
static int ra_spi_dma_setup(struct ra_spi_priv_s *priv);
static int ra_spi_dma_transfer(struct ra_spi_priv_s *priv,
                    const void *txbuffer, void *rxbuffer,
                    size_t nwords);
static void ra_spi_dma_stop(struct ra_spi_priv_s *priv);
static void ra_spi_dma_tx_callback(void *handle, int event, void *arg);
static void ra_spi_dma_rx_callback(void *handle, int event, void *arg);
#endif

/* Transfer helpers */
static void ra_spi_start_transfer(struct ra_spi_priv_s *priv);
static void ra_spi_transmit(struct ra_spi_priv_s *priv);
static void ra_spi_writeword(struct ra_spi_priv_s *priv, uint32_t word);
static uint32_t ra_spi_readword(struct ra_spi_priv_s *priv);
static int ra_spi_get_transfer_size(struct ra_spi_priv_s *priv);

/* Interrupt handling */
#ifdef CONFIG_RA_DMAC
static int ra_spi_rxi_interrupt(int irq, void *context, void *arg);
static int ra_spi_txi_interrupt(int irq, void *context, void *arg);
#endif
static int ra_spi_tei_interrupt(int irq, void *context, void *arg);
static int ra_spi_eri_interrupt(int irq, void *context, void *arg);

/* SPI methods */
static int ra_spi_lock(struct spi_dev_s *dev, bool lock);
static uint32_t ra_spi_setfrequency(struct spi_dev_s *dev, uint32_t frequency);
static void ra_spi_setmode(struct spi_dev_s *dev, enum spi_mode_e mode);
static void ra_spi_setbits(struct spi_dev_s *dev, int nbits);
#ifdef CONFIG_SPI_HWFEATURES
static int ra_spi_hwfeatures(struct spi_dev_s *dev,
                    spi_hwfeatures_t features);
#endif
static uint32_t ra_spi_send(struct spi_dev_s *dev, uint32_t wd);
static void ra_spi_exchange(struct spi_dev_s *dev, const void *txbuffer,
                    void *rxbuffer, size_t nwords);
#ifndef CONFIG_SPI_EXCHANGE
static void ra_spi_sndblock(struct spi_dev_s *dev, const void *txbuffer,
                    size_t nwords);
static void ra_spi_recvblock(struct spi_dev_s *dev, void *rxbuffer,
                    size_t nwords);
#endif
#ifdef CONFIG_SPI_TRIGGER
static int ra_spi_trigger(struct spi_dev_s *dev);
#endif

/* Initialization */
static void ra_spi_bus_initialize(struct ra_spi_priv_s *priv);

/****************************************************************************
 * Private Data
 ****************************************************************************/

#ifdef CONFIG_RA_DTC
/* DTC initialization flag */
static bool g_dtc_initialized = false;
#endif

/* SPI operations */
static const struct spi_ops_s ra_spi_ops =
{
  .lock              = ra_spi_lock,
  .select            = ra_spi_select,           /* Provided externally */
  .setfrequency      = ra_spi_setfrequency,
  .setmode           = ra_spi_setmode,
  .setbits           = ra_spi_setbits,
#ifdef CONFIG_SPI_HWFEATURES
  .hwfeatures        = ra_spi_hwfeatures,
#endif
  .status            = ra_spi_status,           /* Provided externally */
#ifdef CONFIG_SPI_CMDDATA
  .cmddata           = ra_spi_cmddata,          /* Provided externally */
#endif
  .send              = ra_spi_send,
#ifdef CONFIG_SPI_EXCHANGE
  .exchange          = ra_spi_exchange,
#else
  .sndblock          = ra_spi_sndblock,
  .recvblock         = ra_spi_recvblock,
#endif
#ifdef CONFIG_SPI_TRIGGER
  .trigger           = ra_spi_trigger,
#endif
#ifdef CONFIG_SPI_CALLBACK
  .registercallback  = ra_spi_register_callback, /* Provided externally */
#endif
};

#ifdef CONFIG_RA_SPI0
static const struct ra_spi_config_s ra_spi0_config =
{
  .base        = R_SPI_B_CH_BASE(0),
  .bus         = 0,

  .rxi_elc     = RA_ELC_SPI0_RXI,
  .txi_elc     = RA_ELC_SPI0_TXI,
  .tei_elc     = RA_ELC_SPI0_TEI,
  .eri_elc     = RA_ELC_SPI0_ERI,

  .mstpcrb_bit = R_MSTP_MSTPCRB_SPI0,

  .ssl_select  = 0,  /* Default SSL mapping */
  .master_mode = true,            /* Default to master mode */

#ifdef CONFIG_RA_SPI0_USE_DMAC
  .use_dma = true,
#else
  .use_dma = false,
#endif

#ifdef CONFIG_RA_SPI0_USE_DTC
  .use_dtc = true
#else
  .use_dtc = false
#endif
};

static struct ra_spi_priv_s ra_spi0_priv =
{
  .spidev   =
    {
      .ops    = &ra_spi_ops,
    },
  .config   = &ra_spi0_config,
  .refs     = 0,
  .lock     = NXMUTEX_INITIALIZER,
  .waitsem  = SEM_INITIALIZER(0),
  .devid    = 0xffff,
};
#endif

#ifdef CONFIG_RA_SPI1
static const struct ra_spi_config_s ra_spi1_config =
{
  .base        = R_SPI_B_CH_BASE(1),
  .bus         = 1,

  .rxi_elc     = RA_ELC_SPI1_RXI,
  .txi_elc     = RA_ELC_SPI1_TXI,
  .tei_elc     = RA_ELC_SPI1_TEI,
  .eri_elc     = RA_ELC_SPI1_ERI,

  .mstpcrb_bit = R_MSTP_MSTPCRB_SPI1,

  .ssl_select  = 0,  /* Default CS GPIO is used */
  .master_mode = true,            /* Default to master mode */

#ifdef CONFIG_RA_SPI1_USE_DMAC
  .use_dma = true,
#else
  .use_dma = false,
#endif

#ifdef CONFIG_RA_SPI1_USE_DTC
  .use_dtc = true
#else
  .use_dtc = false
#endif
};

static struct ra_spi_priv_s ra_spi1_priv =
{
  .spidev   =
    {
      .ops    = &ra_spi_ops,
    },
  .config   = &ra_spi1_config,
  .refs     = 0,
  .lock     = NXMUTEX_INITIALIZER,
  .waitsem  = SEM_INITIALIZER(0),
  .devid    = 0xffff,
};
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_spi_putreg32
 *
 * Description:
 *   Put a 32-bit register value by offset
 *
 ****************************************************************************/

static void ra_spi_putreg32(struct ra_spi_priv_s *priv, uint8_t offset,
                    uint32_t value)
{
  putreg32(value, priv->config->base + offset);
}

/****************************************************************************
 * Name: ra_spi_getreg32
 *
 * Description:
 *   Get a 32-bit register value by offset
 *
 ****************************************************************************/

static uint32_t ra_spi_getreg32(struct ra_spi_priv_s *priv, uint8_t offset)
{
  return getreg32(priv->config->base + offset);
}

/****************************************************************************
 * Name: ra_spi_writeword
 *
 * Description:
 *   Write one word to SPI
 *
 ****************************************************************************/

static void ra_spi_writeword(struct ra_spi_priv_s *priv, uint32_t word)
{
  /* Write the data using 32-bit register access regardless of data width */
  /* The hardware will use only the relevant bits based on the configured nbits */
  ra_spi_putreg32(priv, R_SPI_B_SPDR_OFFSET, word);

  /* SPI Status Clear Register */
  ra_spi_putreg32(priv, R_SPI_B_SPSRC_OFFSET, R_SPI_B_SPSRC_SPTEFC);
}

/****************************************************************************
 * Name: ra_spi_readword
 *
 * Description:
 *   Read one word from SPI
 *
 ****************************************************************************/

static uint32_t ra_spi_readword(struct ra_spi_priv_s *priv)
{
  /* Read the data using 32-bit register access regardless of data width */
  /* The hardware will provide only the relevant bits based on the configured nbits */
  uint32_t val = ra_spi_getreg32(priv, R_SPI_B_SPDR_OFFSET);

  /* Clear Receive Full flag */
  ra_spi_putreg32(priv, R_SPI_B_SPSRC_OFFSET, R_SPI_B_SPSRC_SPRFC);

  return val;
}

/****************************************************************************
 * Name: ra_spi_get_transfer_size
 *
 * Description:
 *   Get the appropriate transfer size in bytes based on SPB field value
 *
 ****************************************************************************/

static int ra_spi_get_transfer_size(struct ra_spi_priv_s *priv)
{
  /* Read SPB field from SPCMD0 register */
  uint32_t spcmd0 = ra_spi_getreg32(priv, R_SPI_B_SPCMD0_OFFSET);
  uint32_t spb = spcmd0 & R_SPI_B_SPCMD_SPB_MASK;

  /* Decode SPB field value to bit count */
  switch (spb)
    {
      case R_SPI_B_SPCMD_SPB_4:
      case R_SPI_B_SPCMD_SPB_8:
        return 1;  /* 4-bit or 8-bit transfers */

      case R_SPI_B_SPCMD_SPB_16:
        return 2;  /* 16-bit transfers */

      case R_SPI_B_SPCMD_SPB_20:
      case R_SPI_B_SPCMD_SPB_24:
      case R_SPI_B_SPCMD_SPB_32:
        return 4;  /* 20-bit, 24-bit, or 32-bit transfers */

      default:
        return 1;  /* Default to 8-bit */
    }
}

/****************************************************************************
 * Name: ra_spi_transmit
 *
 * Description:
 *   Write the word to the hardware to start shifting
 *
 ****************************************************************************/
static void ra_spi_transmit(struct ra_spi_priv_s *priv)
{
  uint32_t data = 0xffffU;

  if (priv->txbuffer)
    {
      int transfer_size = ra_spi_get_transfer_size(priv);

      if (transfer_size == 4)
        {
          data = *((uint32_t *)priv->txbuffer);
          priv->txbuffer = (uint8_t *)priv->txbuffer + 4;
        }
      else if (transfer_size == 2)
        {
          data = (uint32_t)*((uint16_t *)priv->txbuffer);
          priv->txbuffer = (uint8_t *)priv->txbuffer + 2;
        }
      else
        {
          data = (uint32_t)*((uint8_t *)priv->txbuffer);
          priv->txbuffer = (uint8_t *)priv->txbuffer + 1;
        }
    }

  /* Write the word to the hardware to start shifting */
  ra_spi_writeword(priv, data);
  priv->ntxwords--;
}

/****************************************************************************
 * Name: ra_spi_start_transfer
 *
 * Description:
 *   Start SPI transfer (works with DTC, DMAC, or PIO)
 *
 ****************************************************************************/

static void ra_spi_start_transfer(struct ra_spi_priv_s *priv)
{
  uint32_t spcr;

  spiinfo("Transfer start for SPI%d - TX IRQ=%d, RX IRQ=%d, TEI IRQ=%d, ERI IRQ=%d\n",
          priv->config->bus, priv->txi_irq, priv->rxi_irq, priv->tei_irq, priv->eri_irq);

  /* Clear FIFOs to ensure a clean start */
  ra_spi_putreg32(priv, R_SPI_B_SPFCR_OFFSET, R_SPI_B_SPFCR_SPFRST);

  /* Get SPCR and enable appropriate interrupts */
  spcr = ra_spi_getreg32(priv, R_SPI_B_SPCR_OFFSET);

  /* Enable Transmit Empty interrupt if transmitting */
  if (priv->txbuffer)
    {
      spcr |= R_SPI_B_SPCR_SPTIE;
    }

  /* Enable Receive Buffer Full interrupt if receiving */
  if (priv->rxbuffer)
    {
      spcr |= R_SPI_B_SPCR_SPRIE;
    }

  /* For non-DTC/DMA transfers with TX buffer, preload FIFO before enabling IRQs */
#if defined(CONFIG_RA_DTC) || defined(CONFIG_RA_DMAC)
  bool dma_dtc_active = false;
#ifdef CONFIG_RA_DTC
  dma_dtc_active = dma_dtc_active || priv->dtc_active;
#endif
#ifdef CONFIG_RA_DMAC
  dma_dtc_active = dma_dtc_active || priv->dma_active;
#endif

  if (!dma_dtc_active && priv->txbuffer)
#else
  if (priv->txbuffer)
#endif
    {
      /* Temporarily disable TXI IRQ so we can preload without racing the ISR */
      up_disable_irq(priv->txi_irq);

      /* Enable SPI transfer */
      ra_spi_putreg32(priv, R_SPI_B_SPCR_OFFSET, spcr | R_SPI_B_SPCR_SPE);

      /* Prefill up to two transmit words to start the pipeline */
      ra_spi_transmit(priv);
      if (priv->ntxwords > 0)
        {
          ra_spi_transmit(priv);
        }

      /* Clear pending TXI and re-enable the IRQ */
      ra_icu_clear_irq(priv->txi_irq);
      up_enable_irq(priv->txi_irq);
    }
  else
    {
      /* Default: enable SPE and let ISR or DTC/DMA handle transmit */
      ra_spi_putreg32(priv, R_SPI_B_SPCR_OFFSET, spcr | R_SPI_B_SPCR_SPE);
    }

  spiinfo("SPI transfer started: SPCR=0x%08lx\n", spcr);
}

#ifdef CONFIG_RA_DTC

/****************************************************************************
 * Name: ra_spi_dtc_setup
 *
 * Description:
 *   Setup DTC for the SPI
 *
 ****************************************************************************/

static int ra_spi_dtc_setup(struct ra_spi_priv_s *priv)
{
  spiinfo("DTC setup for SPI%d\n", priv->config->bus);

  /* Initialize DTC module once (global initialization) */
  if (!g_dtc_initialized)
    {
      irqstate_t flags = enter_critical_section();

      if (!g_dtc_initialized)
        {
          /* Enable DTC module clock */
          ra_mstp_start(RA_MSTP_DTC);

          /* Initialize DTC module - this will set up the vector table */
          ra_dtc_initialize();

          g_dtc_initialized = true;

          spiinfo("DTC module initialized\n");
        }

      leave_critical_section(flags);
    }

  /* DTC active state is per-transfer, initialize to false */
  priv->dtc_active = false;

  spiinfo("DTC setup completed for SPI%d\n", priv->config->bus);

  return OK;
}

/****************************************************************************
 * Name: ra_spi_dtc_configure_transfer
 *
 * Description:
 *   Configure DTC transfer information
 *
 ****************************************************************************/

static int ra_spi_dtc_configure_transfer(struct ra_spi_priv_s *priv,
                    const void *txbuffer, void *rxbuffer,
                    size_t nwords)
{
  uint8_t transfer_size;

  spiinfo("Configuring DTC transfer: tx=%p rx=%p nwords=%zu\n",
          txbuffer, rxbuffer, nwords);

  /* Read SPB field from SPCMD0 register */
  uint32_t spcmd0 = ra_spi_getreg32(priv, R_SPI_B_SPCMD0_OFFSET);
  uint32_t spb = spcmd0 & R_SPI_B_SPCMD_SPB_MASK;

  /* Determine transfer size based on SPI bit width (SPB field) */
  switch (spb)
    {
      case R_SPI_B_SPCMD_SPB_4:
      case R_SPI_B_SPCMD_SPB_8:
        transfer_size = RA_DTC_MRA_SZ_BYTE; /* 8-bit transfers for 4-8 bits */
        break;

      case R_SPI_B_SPCMD_SPB_16:
        transfer_size = RA_DTC_MRA_SZ_WORD; /* 16-bit transfers for 16 bits */
        break;

      case R_SPI_B_SPCMD_SPB_20:
      case R_SPI_B_SPCMD_SPB_24:
      case R_SPI_B_SPCMD_SPB_32:
        transfer_size = RA_DTC_MRA_SZ_LONG; /* 32-bit transfers for 17-32 bits */
        break;

      default:
        transfer_size = RA_DTC_MRA_SZ_BYTE; /* Default to 8-bit */
        break;
    }

  /* Clear DTC transfer info structures */
  memset(&priv->dtc_tx_info, 0, sizeof(priv->dtc_tx_info));
  memset(&priv->dtc_rx_info, 0, sizeof(priv->dtc_rx_info));

  /* Configure TX DTC if transmit buffer provided */
  if (txbuffer)
    {
      /* Configure TX DTC: source increment, dest fixed, normal mode
       * DISEL=0: Interrupt only at END of all DTC transfers
       */
      priv->dtc_tx_info.mra = RA_DTC_MRA_MD_NORMAL | transfer_size | RA_DTC_MRA_SM_INCREMENT;
      //priv->dtc_tx_info.mrb = RA_DTC_MRB_DM_FIXED | RA_DTC_MRB_DISEL; /* IRQ at end */
      priv->dtc_tx_info.mrb = RA_DTC_MRB_DM_FIXED; /* DISEL=0: IRQ at end of all transfers */
      priv->dtc_tx_info.sar = (uint32_t)txbuffer;
      priv->dtc_tx_info.dar = priv->config->base + R_SPI_B_SPDR_OFFSET;
      priv->dtc_tx_info.cra = (uint16_t)nwords;
      priv->dtc_tx_info.crb = 0;

      spiinfo("TX DTC: MRA=0x%02x MRB=0x%02x SAR=0x%08lx DAR=0x%08lx CRA=%d\n",
              priv->dtc_tx_info.mra, priv->dtc_tx_info.mrb,
              (unsigned long)priv->dtc_tx_info.sar, (unsigned long)priv->dtc_tx_info.dar, priv->dtc_tx_info.cra);
    }

  /* Configure RX DTC if receive buffer provided */
  if (rxbuffer)
    {
      /* Configure RX DTC: source fixed, dest increment, normal mode
       * DISEL=0: Interrupt only at END of all DTC transfers
       */
      priv->dtc_rx_info.mra = RA_DTC_MRA_MD_NORMAL | transfer_size | RA_DTC_MRA_SM_FIXED;
      //priv->dtc_rx_info.mrb = RA_DTC_MRB_DM_INCREMENT | RA_DTC_MRB_DISEL; /* IRQ at end */
      priv->dtc_rx_info.mrb = RA_DTC_MRB_DM_INCREMENT; /* DISEL=0: IRQ at end of all transfers */
      priv->dtc_rx_info.sar = priv->config->base + R_SPI_B_SPDR_OFFSET;
      priv->dtc_rx_info.dar = (uint32_t)rxbuffer;
      priv->dtc_rx_info.cra = (uint16_t)nwords;
      priv->dtc_rx_info.crb = 0;

      spiinfo("RX DTC: MRA=0x%02x MRB=0x%02x SAR=0x%08lx DAR=0x%08lx CRA=%d\n",
              priv->dtc_rx_info.mra, priv->dtc_rx_info.mrb,
              (unsigned long)priv->dtc_rx_info.sar, (unsigned long)priv->dtc_rx_info.dar, priv->dtc_rx_info.cra);
    }

  /* Ensure DTC transfer info structures are flushed to memory before DTC reads them.
   * The Cortex-M85 has a data cache that may delay writes to SRAM, but DTC
   * hardware reads from SRAM directly. Without this flush, DTC may read
   * stale/uninitialized data from the transfer info structures.
   */
  up_clean_dcache((uintptr_t)&priv->dtc_tx_info,
                  (uintptr_t)&priv->dtc_tx_info + sizeof(priv->dtc_tx_info));
  up_clean_dcache((uintptr_t)&priv->dtc_rx_info,
                  (uintptr_t)&priv->dtc_rx_info + sizeof(priv->dtc_rx_info));

  return OK;
}

/****************************************************************************
 * Name: ra_spi_dtc_reconfigure
 *
 * Description:
 *   Commit the previously prepared DTC transfer_info structures into the
 *   DTC/vector table and enable ICU triggers.
 *
 *   NOTE: This function does not modify SPI registers (SPCMD0/SPCR/etc.).
 *
 ****************************************************************************/

static int ra_spi_dtc_reconfigure(struct ra_spi_priv_s *priv)
{
  /* Configure DTC vector table entries using ICU-assigned slot numbers */
  if (priv->txbuffer && priv->txi_irq >= 0)
    {
      int slot = priv->txi_irq - RA_IRQ_FIRST;
      ra_icu_disable_dtc(priv->txi_irq);  /* Disable before setting */
      ra_dtc_set_vector(slot, &priv->dtc_tx_info);
      spiinfo("Committed TX DTC vector for slot %d (IRQ %d)\n", slot, priv->txi_irq);
    }

  if (priv->rxbuffer && priv->rxi_irq >= 0)
    {
      int slot = priv->rxi_irq - RA_IRQ_FIRST;
      ra_icu_disable_dtc(priv->rxi_irq);  /* Disable before setting */
      ra_dtc_set_vector(slot, &priv->dtc_rx_info);
      spiinfo("Committed RX DTC vector for slot %d (IRQ %d)\n", slot, priv->rxi_irq);
    }

  /* Enable DTC triggers for buffers that exist.
   *
   * IMPORTANT: With DISEL=0, DTC generates an interrupt through the normal
   * SPI IRQ vector (TXI/RXI) after the LAST transfer completes. This means
   * the NVIC must have TXI/RXI interrupts enabled for the completion
   * interrupt to reach the CPU.
   *
   * The flow is:
   * 1. DTCE=1 routes TXI/RXI events to trigger DTC hardware
   * 2. DTC handles each data transfer without CPU involvement
   * 3. After the last transfer, DISEL=0 causes DTC to generate an IRQ
   *    through the normal SPI interrupt vector (not a DTC-specific vector)
   * 4. CPU receives IRQ through NVIC and RXI/TXI ISR runs to signal completion
   *
   */
  if (priv->txbuffer && priv->txi_irq >= 0)
    {
      /* Ensure TXI is enabled in NVIC before enabling DTC trigger.
       * Clear pending first like FSP's R_BSP_IrqEnable() does.
       */
      ra_icu_clear_irq(priv->txi_irq);
      up_enable_irq(priv->txi_irq);
      ra_icu_enable_dtc(priv->txi_irq);
      spiinfo("Enabled DTC trigger for TXI IRQ %d\n", priv->txi_irq);
    }

  if (priv->rxbuffer && priv->rxi_irq >= 0)
    {
      /* Ensure RXI is enabled in NVIC before enabling DTC trigger.
       * Clear pending first like FSP's R_BSP_IrqEnable() does.
       */
      ra_icu_clear_irq(priv->rxi_irq);
      up_enable_irq(priv->rxi_irq);
      ra_icu_enable_dtc(priv->rxi_irq);
      spiinfo("Enabled DTC trigger for RXI IRQ %d\n", priv->rxi_irq);
    }

  /* Mark DTC as active with the current transfer */
  priv->dtc_active = true;

  return OK;
}

/****************************************************************************
 * Name: ra_spi_dtc_stop
 *
 * Description:
 *   Stop DTC transfer safely by waiting for any in-progress transfer to
 *   complete before disabling DTC triggers.
 *
 ****************************************************************************/

static void ra_spi_dtc_stop(struct ra_spi_priv_s *priv)
{
  spiinfo("DTC stop for SPI%d\n", priv->config->bus);

  /* Wait for any in-progress DTC transfer to complete before disabling.
   * Check both TX and RX slots to ensure all DTC activity is done.
   * This prevents corruption if DTC is mid-transfer.
   */
  if (priv->txi_irq >= 0)
    {
      int slot = priv->txi_irq - RA_IRQ_FIRST;
      int timeout = 10000;

      while (timeout-- > 0)
        {
          uint32_t dtcsts = getreg16(R_DTC_DTCSTS);
          if (!(dtcsts & R_DTC_DTCSTS_ACT) ||
              (dtcsts & R_DTC_DTCSTS_VECN_MASK) != (uint32_t)slot)
            {
              break;
            }
          up_udelay(1);
        }

      if (timeout == 0)
        {
          spierr("DTC stop timeout for TXI slot %d\n", slot);
        }

      ra_icu_disable_dtc(priv->txi_irq);

      /* Clear vector table entry to prevent stale pointer access.
       * This ensures the DTC vector table doesn't point to potentially
       * invalid transfer_info structures between transfers.
       */
      ra_dtc_clear_vector(slot);
      /* Re-enable CPU ISR for next transfer */
      up_enable_irq(priv->txi_irq);

      spiinfo("Disabled DTC trigger for TXI IRQ %d\n", priv->txi_irq);
    }

  if (priv->rxi_irq >= 0)
    {
      int slot = priv->rxi_irq - RA_IRQ_FIRST;
      int timeout = 10000;

      while (timeout-- > 0)
        {
          uint32_t dtcsts = getreg16(R_DTC_DTCSTS);
          if (!(dtcsts & R_DTC_DTCSTS_ACT) ||
              (dtcsts & R_DTC_DTCSTS_VECN_MASK) != (uint32_t)slot)
            {
              break;
            }
          up_udelay(1);
        }

      if (timeout == 0)
        {
          spierr("DTC stop timeout for RXI slot %d\n", slot);
        }

      ra_icu_disable_dtc(priv->rxi_irq);

      /* Clear vector table entry for RX as well */
      ra_dtc_clear_vector(slot);

      /* Re-enable CPU ISR for next transfer */
      up_enable_irq(priv->rxi_irq);

      spiinfo("Disabled DTC trigger and re-enabled CPU ISR for RXI IRQ %d\n", priv->rxi_irq);
    }

  /* Mark DTC as no longer active */
  priv->dtc_active = false;
}

#endif /* CONFIG_RA_DTC */

/****************************************************************************
 * DMAC Support Functions
 ****************************************************************************/

#ifdef CONFIG_RA_DMAC

/****************************************************************************
 * Name: ra_spi_get_dma_channels
 *
 * Description:
 *   Get DMA channel assignments from Kconfig for the specified SPI bus
 *
 ****************************************************************************/

static void ra_spi_get_dma_channels(struct ra_spi_priv_s *priv,
                    int *tx_channel, int *rx_channel)
{
  /* Default to dynamic allocation */
  *tx_channel = -1;
  *rx_channel = -1;

#ifdef CONFIG_RA_SPI0
  if (priv->config->bus == 0)
    {
#ifdef CONFIG_RA_DMAC_SPI0_TX_CHANNEL
      *tx_channel = CONFIG_RA_DMAC_SPI0_TX_CHANNEL;
#endif
#ifdef CONFIG_RA_DMAC_SPI0_RX_CHANNEL
      *rx_channel = CONFIG_RA_DMAC_SPI0_RX_CHANNEL;
#endif
    }
#endif

#ifdef CONFIG_RA_SPI1
  if (priv->config->bus == 1)
    {
#ifdef CONFIG_RA_DMAC_SPI1_TX_CHANNEL
      *tx_channel = CONFIG_RA_DMAC_SPI1_TX_CHANNEL;
#endif
#ifdef CONFIG_RA_DMAC_SPI1_RX_CHANNEL
      *rx_channel = CONFIG_RA_DMAC_SPI1_RX_CHANNEL;
#endif
    }
#endif

  spiinfo("SPI%d DMA channels: TX=%d, RX=%d\n",
          priv->config->bus, *tx_channel, *rx_channel);
}

/****************************************************************************
 * Name: ra_spi_dma_tx_callback
 *
 * Description:
 *   TX DMA completion callback
 *
 ****************************************************************************/

static void ra_spi_dma_tx_callback(void *handle, int event, void *arg)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)arg;

  DEBUGASSERT(priv != NULL);

  if (event == RA_DMAC_EVENT_COMPLETE)
    {
      spiinfo("SPI%d TX DMA complete\n", priv->config->bus);
      priv->dma_tx_done = true;

      /* Only enable TEI for TX-only mode */
      if (priv->dma_rx == NULL)
        {
          /* TX-only mode - enable TEI now.
           * TEI ISR will wait for TEND flag before clearing SPE.
           */
          up_enable_irq(priv->tei_irq);
        }
      /* For full-duplex: do nothing here, RX callback will enable TEI */
    }
  else if (event == RA_DMAC_EVENT_ERROR)
    {
      spierr("SPI%d TX DMA error\n", priv->config->bus);
      priv->error = true;
      priv->dma_tx_done = true;
      nxsem_post(&priv->waitsem);
    }
}

/****************************************************************************
 * Name: ra_spi_dma_rx_callback
 *
 * Description:
 *   RX DMA completion callback
 *
 ****************************************************************************/

static void ra_spi_dma_rx_callback(void *handle, int event, void *arg)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)arg;

  DEBUGASSERT(priv != NULL);

  if (event == RA_DMAC_EVENT_COMPLETE)
    {
      spiinfo("SPI%d RX DMA complete\n", priv->config->bus);
      priv->dma_rx_done = true;

      /* Invalidate D-cache for RX buffer after DMA completes */
      if (priv->rxbuffer != NULL)
        {
          int transfer_size = ra_spi_get_transfer_size(priv);
          up_invalidate_dcache((uintptr_t)priv->rxbuffer,
                    (uintptr_t)priv->rxbuffer +
                    (priv->nrxwords * transfer_size));
        }

      /* RX completion always enables TEI for full-duplex.
       * This means the transfer is almost complete - just waiting for
       * the last byte to finish shifting out
       */
      up_enable_irq(priv->tei_irq);
    }
  else if (event == RA_DMAC_EVENT_ERROR)
    {
      spierr("SPI%d RX DMA error\n", priv->config->bus);
      priv->error = true;
      priv->dma_rx_done = true;
      nxsem_post(&priv->waitsem);
    }
}

/****************************************************************************
 * Name: ra_spi_dma_setup
 *
 * Description:
 *   Setup DMA for SPI transfers
 *
 ****************************************************************************/

static int ra_spi_dma_setup(struct ra_spi_priv_s *priv)
{
  int ret;

  spiinfo("DMA setup for SPI%d\n", priv->config->bus);

  /* Initialize DMAC module */
  ret = ra_dmac_initialize();
  if (ret < 0)
    {
      spierr("Failed to initialize DMAC: %d\n", ret);
      return ret;
    }

  /* Get DMA channel assignments from Kconfig */
  ra_spi_get_dma_channels(priv, &priv->dma_tx_channel, &priv->dma_rx_channel);

  /* DMA active state is per-transfer, initialize to false */
  priv->dma_active = false;
  priv->dma_tx = NULL;
  priv->dma_rx = NULL;
  priv->dma_tx_done = false;
  priv->dma_rx_done = false;

  spiinfo("DMA setup completed for SPI%d (TX ch=%d, RX ch=%d)\n",
          priv->config->bus, priv->dma_tx_channel, priv->dma_rx_channel);

  return OK;
}

/****************************************************************************
 * Name: ra_spi_dma_transfer
 *
 * Description:
 *   Configure and start a DMA transfer for SPI
 *
 ****************************************************************************/

static int ra_spi_dma_transfer(struct ra_spi_priv_s *priv,
                    const void *txbuffer, void *rxbuffer,
                    size_t nwords)
{
  ra_dmac_config_t tx_config;
  ra_dmac_config_t rx_config;
  int transfer_size;
  ra_dmac_size_t dma_size;
  int ret;

  spiinfo("DMA transfer: tx=%p rx=%p nwords=%zu\n", txbuffer, rxbuffer, nwords);

  /* Determine transfer size based on SPI bit width */
  transfer_size = ra_spi_get_transfer_size(priv);
  switch (transfer_size)
    {
      case 1:
        dma_size = RA_DMAC_SIZE_8BIT;
        break;
      case 2:
        dma_size = RA_DMAC_SIZE_16BIT;
        break;
      case 4:
      default:
        dma_size = RA_DMAC_SIZE_32BIT;
        break;
    }

  /* Reset completion flags */
  priv->dma_tx_done = (txbuffer == NULL);
  priv->dma_rx_done = (rxbuffer == NULL);
  priv->dma_active = true;

  /* Configure TX DMA if transmit buffer provided */
  if (txbuffer != NULL)
    {
      /* Clean D-cache for TX buffer before DMA reads it */
      up_clean_dcache((uintptr_t)txbuffer,
                    (uintptr_t)txbuffer + (nwords * transfer_size));

      memset(&tx_config, 0, sizeof(tx_config));
      tx_config.mode = RA_DMAC_MODE_NORMAL;
      tx_config.repeat_area = RA_DMAC_REPEAT_AREA_NONE;
      tx_config.size = dma_size;
      tx_config.src_addr_mode = RA_DMAC_ADDR_INCR;    /* Source increments */
      tx_config.dest_addr_mode = RA_DMAC_ADDR_FIXED;  /* Dest fixed (SPI DR) */
      tx_config.trigger = RA_DMAC_TRIGGER_HW;         /* Hardware trigger */
      tx_config.src_addr = (uint32_t)txbuffer;
      tx_config.dest_addr = priv->config->base + R_SPI_B_SPDR_OFFSET;
      tx_config.transfer_count = nwords;
      tx_config.block_count = 0;
      tx_config.elc_src = priv->config->txi_elc;      /* SPI TXI event */
      tx_config.elc_end = -1;                         /* No separate end event */
      tx_config.elc_err = -1;                         /* No separate error event */
      tx_config.callback = ra_spi_dma_tx_callback;
      tx_config.user_data = priv;

      /* Use assigned channel if configured, otherwise use dynamic allocation */
      if (priv->dma_tx_channel >= 0)
        {
          ret = ra_dmac_open_channel(&priv->dma_tx, &tx_config, priv->dma_tx_channel);
          spiinfo("TX DMA using assigned channel %d\n", priv->dma_tx_channel);
        }
      else
        {
          ret = ra_dmac_open(&priv->dma_tx, &tx_config);
          spiinfo("TX DMA using dynamic channel allocation\n");
        }

      if (ret < 0)
        {
          spierr("Failed to open TX DMA: %d\n", ret);
          priv->dma_active = false;
          return ret;
        }

      ret = ra_dmac_enable(priv->dma_tx);
      if (ret < 0)
        {
          spierr("Failed to enable TX DMA: %d\n", ret);
          ra_dmac_close(priv->dma_tx);
          priv->dma_tx = NULL;
          priv->dma_active = false;
          return ret;
        }

      spiinfo("TX DMA configured: src=0x%08lx dst=0x%08lx count=%zu\n",
              (unsigned long)txbuffer,
              (unsigned long)(priv->config->base + R_SPI_B_SPDR_OFFSET),
              nwords);
    }

  /* Configure RX DMA if receive buffer provided */
  if (rxbuffer != NULL)
    {
      memset(&rx_config, 0, sizeof(rx_config));
      rx_config.mode = RA_DMAC_MODE_NORMAL;
      rx_config.repeat_area = RA_DMAC_REPEAT_AREA_NONE;
      rx_config.size = dma_size;
      rx_config.src_addr_mode = RA_DMAC_ADDR_FIXED;   /* Source fixed (SPI DR) */
      rx_config.dest_addr_mode = RA_DMAC_ADDR_INCR;   /* Dest increments */
      rx_config.trigger = RA_DMAC_TRIGGER_HW;         /* Hardware trigger */
      rx_config.src_addr = priv->config->base + R_SPI_B_SPDR_OFFSET;
      rx_config.dest_addr = (uint32_t)rxbuffer;
      rx_config.transfer_count = nwords;
      rx_config.block_count = 0;
      rx_config.elc_src = priv->config->rxi_elc;      /* SPI RXI event */
      rx_config.elc_end = -1;                         /* No separate end event */
      rx_config.elc_err = -1;                         /* No separate error event */
      rx_config.callback = ra_spi_dma_rx_callback;
      rx_config.user_data = priv;

      /* Use assigned channel if configured, otherwise use dynamic allocation */
      if (priv->dma_rx_channel >= 0)
        {
          ret = ra_dmac_open_channel(&priv->dma_rx, &rx_config, priv->dma_rx_channel);
          spiinfo("RX DMA using assigned channel %d\n", priv->dma_rx_channel);
        }
      else
        {
          ret = ra_dmac_open(&priv->dma_rx, &rx_config);
          spiinfo("RX DMA using dynamic channel allocation\n");
        }

      if (ret < 0)
        {
          spierr("Failed to open RX DMA: %d\n", ret);
          if (priv->dma_tx != NULL)
            {
              ra_dmac_disable(priv->dma_tx);
              ra_dmac_close(priv->dma_tx);
              priv->dma_tx = NULL;
            }
          priv->dma_active = false;
          return ret;
        }

      ret = ra_dmac_enable(priv->dma_rx);
      if (ret < 0)
        {
          spierr("Failed to enable RX DMA: %d\n", ret);
          ra_dmac_close(priv->dma_rx);
          priv->dma_rx = NULL;
          if (priv->dma_tx != NULL)
            {
              ra_dmac_disable(priv->dma_tx);
              ra_dmac_close(priv->dma_tx);
              priv->dma_tx = NULL;
            }
          priv->dma_active = false;
          return ret;
        }

      spiinfo("RX DMA configured: src=0x%08lx dst=0x%08lx count=%zu\n",
              (unsigned long)(priv->config->base + R_SPI_B_SPDR_OFFSET),
              (unsigned long)rxbuffer,
              nwords);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_spi_dma_stop
 *
 * Description:
 *   Stop DMA transfer and release resources
 *
 ****************************************************************************/

static void ra_spi_dma_stop(struct ra_spi_priv_s *priv)
{
  spiinfo("DMA stop for SPI%d\n", priv->config->bus);

  /* Disable and close TX DMA */
  if (priv->dma_tx != NULL)
    {
      ra_dmac_disable(priv->dma_tx);
      ra_dmac_close(priv->dma_tx);
      priv->dma_tx = NULL;
      spiinfo("TX DMA stopped\n");
    }

  /* Disable and close RX DMA */
  if (priv->dma_rx != NULL)
    {
      ra_dmac_disable(priv->dma_rx);
      ra_dmac_close(priv->dma_rx);
      priv->dma_rx = NULL;
      spiinfo("RX DMA stopped\n");
    }

  priv->dma_active = false;
  priv->dma_tx_done = false;
  priv->dma_rx_done = false;
}

#endif /* CONFIG_RA_DMAC */

/****************************************************************************
 * Name: ra_spi_rxi_interrupt
 *
 * Description:
 *   RX interrupt handler
 *
 ****************************************************************************/

#ifdef CONFIG_RA_DMAC
static int ra_spi_rxi_interrupt(int irq, void *context, void *arg)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)arg;
  uint32_t data;

  DEBUGASSERT(priv != NULL);

  /* When DMA is active, the CPU must NOT touch SPDR to prevent data corruption. */
#ifdef CONFIG_RA_DMAC
  if (priv->dma_active)
    {
      return OK;
    }
#endif

#ifdef CONFIG_RA_DTC
  /* When DTC is active with DISEL=0, this ISR is called ONCE after DTC completes ALL RX transfers */
  if (priv->dtc_active)
    {
      /* Wait for DTC to finish any in-progress transfer */
      int slot = priv->rxi_irq - RA_IRQ_FIRST;
      int timeout = 1000;

      while (timeout-- > 0)
        {
          uint32_t dtcsts = getreg16(R_DTC_DTCSTS);
          if (!(dtcsts & R_DTC_DTCSTS_ACT) ||
              ((dtcsts & R_DTC_DTCSTS_VECN_MASK) != (uint32_t)slot))
            {
              break;
            }
          up_udelay(1);
        }

      /* Invalidate D-cache for RX buffer after DTC completes */
      if (priv->rxbuffer != NULL)
        {
          int transfer_size = ra_spi_get_transfer_size(priv);
          size_t total_bytes = priv->nrxwords * transfer_size;
          uintptr_t start = (uintptr_t)priv->rxbuffer;
          up_invalidate_dcache(start, start + total_bytes);
        }

      /* DTC transfer complete for RX - enable TEI to signal completion */
      up_enable_irq(priv->tei_irq);
      return OK;
    }
#endif

  /* Normal PIO path: read received data */
  data = ra_spi_readword(priv);

  if (priv->rxbuffer)
    {
      int transfer_size = ra_spi_get_transfer_size(priv);
      if (transfer_size == 4)
        {
          *((uint32_t *)priv->rxbuffer) = data;
          priv->rxbuffer = (uint8_t *)priv->rxbuffer + 4;
        }
      else if (transfer_size == 2)
        {
          *((uint16_t *)priv->rxbuffer) = (uint16_t)data;
          priv->rxbuffer = (uint8_t *)priv->rxbuffer + 2;
        }
      else
        {
          *((uint8_t *)priv->rxbuffer) = (uint8_t)data;
          priv->rxbuffer = (uint8_t *)priv->rxbuffer + 1;
        }
    }

  if (priv->nrxwords > 0)
    {
      priv->nrxwords--;
    }

  /* After last RX byte, enable TEI to detect transfer completion */
  if (priv->nrxwords == 0)
    {
      up_enable_irq(priv->tei_irq);
    }

  return OK;
}
#endif

/****************************************************************************
 * Name: ra_spi_txi_interrupt
 *
 * Description:
 *   TX interrupt handler
 *
 ****************************************************************************/

#ifdef CONFIG_RA_DMAC
static int ra_spi_txi_interrupt(int irq, void *context, void *arg)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)arg;

  DEBUGASSERT(priv != NULL);

  /* CRITICAL FIX: Guard against concurrent CPU/DMA access to SPDR.
   * When DMA is active, the CPU must NOT touch SPDR to prevent data corruption.
   */
#ifdef CONFIG_RA_DMAC
  if (priv->dma_active)
    {
      return OK;
    }
#endif

#ifdef CONFIG_RA_DTC
  /* When DTC is active with DISEL=0, this ISR is called ONCE after DTC completes ALL transfers */
  if (priv->dtc_active)
    {
      /* Check if this is TX-only (no RX buffer) */
      if (priv->rxbuffer == NULL)
        {
          /* TX-only mode - enable TEI now */
          up_enable_irq(priv->tei_irq);
        }
      /* For full-duplex, RXI ISR will enable TEI */
      return OK;
    }
#endif

  /* Normal PIO path: transmit next word */
  if (priv->ntxwords > 0)
    {
      ra_spi_transmit(priv);

      /* Enable TEI when last byte is written */
      if (priv->ntxwords == 0)
        {
          up_enable_irq(priv->tei_irq);
        }
    }

  return OK;
}
#endif

/****************************************************************************
 * Name: ra_spi_tei_interrupt
 *
 * Description:
 *   Transfer end interrupt handler
 *
 ****************************************************************************/

static int ra_spi_tei_interrupt(int irq, void *context, void *arg)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)arg;
  uint32_t spcr;
  uint32_t spsr;
  int timeout;

  DEBUGASSERT(priv != NULL);

  spiinfo("SPI%d transfer end interrupt\n", priv->config->bus);

  /* Wait for CENDF (Communication End Flag) to ensure shift register has finished */
  timeout = 1000;
  do
    {
      spsr = ra_spi_getreg32(priv, R_SPI_B_SPSR_OFFSET);
      if (spsr & R_SPI_B_SPSR_CENDF)
        {
          break;
        }
      up_udelay(1);
    }
  while (timeout-- > 0);

  if (timeout == 0)
    {
      spierr("SPI%d CENDF timeout (SPSR=0x%08lx)\n",
             priv->config->bus, (unsigned long)spsr);
    }

  /* Disable TXI IRQ before clearing SPE */
  up_disable_irq(priv->txi_irq);

  /* Disable End IRQ */
  up_disable_irq(priv->tei_irq);

  /* Disable the SPI Transfer */
  spcr = ra_spi_getreg32(priv, R_SPI_B_SPCR_OFFSET);
  ra_spi_putreg32(priv, R_SPI_B_SPCR_OFFSET, spcr & ~R_SPI_B_SPCR_SPE);

  /* Clear pending and re-enable TXI IRQ */
  ra_icu_clear_irq(priv->txi_irq);
  up_enable_irq(priv->txi_irq);

#ifdef CONFIG_RA_DTC
  /* Clean up DTC in normal completion path */
  if (priv->dtc_active)
    {
      ra_spi_dtc_stop(priv);
    }
#endif

#ifdef CONFIG_RA_DMAC
  /* Clean up DMA in normal completion path */
  if (priv->dma_active)
    {
      ra_spi_dma_stop(priv);
    }
#endif

  /* Signal completion to waiting thread */
  nxsem_post(&priv->waitsem);

  return OK;
}

/****************************************************************************
 * Name: ra_spi_eri_interrupt
 *
 * Description:
 *   Error interrupt handler
 *
 ****************************************************************************/

static int ra_spi_eri_interrupt(int irq, void *context, void *arg)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)arg;
  uint32_t spsr;
  uint32_t spcr;

  DEBUGASSERT(priv != NULL);

  /* Read SPSR before clearing */
  spsr = ra_spi_getreg32(priv, R_SPI_B_SPSR_OFFSET);
  spierr("SPI%d error interrupt: SPSR=%08lx\n", priv->config->bus, (unsigned long)spsr);

  /* Log specific errors */
  if (spsr & R_SPI_B_SPSR_OVRF)
    {
      spierr("SPI%d overrun error\n", priv->config->bus);
    }
  if (spsr & R_SPI_B_SPSR_MODF)
    {
      spierr("SPI%d mode fault error\n", priv->config->bus);
    }
  if (spsr & R_SPI_B_SPSR_PERF)
    {
      spierr("SPI%d parity error\n", priv->config->bus);
    }
  if (spsr & R_SPI_B_SPSR_UDRF)
    {
      spierr("SPI%d underrun error\n", priv->config->bus);
    }

  /* Stop transfer immediately */
  up_disable_irq(priv->txi_irq);
  spcr = ra_spi_getreg32(priv, R_SPI_B_SPCR_OFFSET);
  ra_spi_putreg32(priv, R_SPI_B_SPCR_OFFSET, spcr & ~R_SPI_B_SPCR_SPE);

  /* Stop DTC/DMAC if active */
#ifdef CONFIG_RA_DTC
  if (priv->dtc_active)
    {
      ra_spi_dtc_stop(priv);
    }
#endif
#ifdef CONFIG_RA_DMAC
  if (priv->dma_active)
    {
      ra_spi_dma_stop(priv);
    }
#endif

  /* Clear error flags in SPSRC */
  ra_spi_putreg32(priv, R_SPI_B_SPSRC_OFFSET,
                  R_SPI_B_SPSRC_OVRFC | R_SPI_B_SPSRC_MODFC |
                  R_SPI_B_SPSRC_PERFC | R_SPI_B_SPSRC_UDRFC);

  /* Re-enable TXI IRQ for next transfer */
  ra_icu_clear_irq(priv->txi_irq);
  up_enable_irq(priv->txi_irq);

  /* Set error flag and wake up waiting thread */
  priv->error = true;
  nxsem_post(&priv->waitsem);

  return OK;
}

/****************************************************************************
 * Name: ra_spi_lock
 *
 * Description:
 *   On SPI buses where there are multiple devices, it will be necessary to
 *   lock SPI to have exclusive access to the buses for a sequence of
 *   transfers.  The bus should be locked before the chip is selected. After
 *   locking the SPI bus, the caller should then also call the setfrequency,
 *   setbits, and setmode methods to make sure that the SPI is properly
 *   configured for the device.  If the SPI buss is being shared, then it
 *   may have been left in an incompatible state.
 *
 * Input Parameters:
 *   dev  - Device-specific state data
 *   lock - true: Lock spi bus, false: unlock SPI bus
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

static int ra_spi_lock(struct spi_dev_s *dev, bool lock)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)dev;
  int ret;

  if (lock)
    {
      ret = nxmutex_lock(&priv->lock);
    }
  else
    {
      ret = nxmutex_unlock(&priv->lock);
    }

  return ret;
}

/****************************************************************************
 * Name: ra_spi_setfrequency
 *
 * Description:
 *   Set the SPI frequency with device-specific limits
 *
 * Input Parameters:
 *   dev -       Device-specific state data
 *   frequency - The SPI frequency requested
 *
 * Returned Value:
 *   Returns the actual frequency selected
 *
 ****************************************************************************/

static uint32_t ra_spi_setfrequency(struct spi_dev_s *dev, uint32_t frequency)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)dev;
  uint32_t src_clk = ra_get_peripheral_clock(RA_PCLK_SPICLK);
  uint32_t desired_divider;
  uint8_t spbr;
  uint8_t brdv = 0;
  uint32_t actual;

  spiinfo("SPI%d frequency %lu\n", priv->config->bus, (unsigned long)frequency);

  /* Skip reprogramming if requested frequency equals current setting */
  if (priv && priv->frequency == frequency)
    {
      spiinfo("SPI%d frequency unchanged (%lu) - skip\n",
              priv->config->bus, (unsigned long)frequency);
      return priv->frequency;
    }

  /* Limit to maximum frequency */
  if (frequency > R_SPI_B_MAX_FREQUENCY)
    {
      frequency = R_SPI_B_MAX_FREQUENCY;
    }

  /* Calculate desired divider (round up to ensure we don't exceed requested frequency)
   * The SPI bit rate is calculated as:
   * Bit rate = src_clk / (2 * (SPBR + 1) * 2^BRDV)
   * Therefore: desired_divider = src_clk / frequency
   */
  desired_divider = (src_clk + frequency - 1) / frequency;

  if (desired_divider > R_SPI_B_CLK_MAX_DIV)
    {
      /* Can't achieve bitrate slower than maximum divider allows */
      desired_divider = R_SPI_B_CLK_MAX_DIV;
    }

  if (desired_divider < R_SPI_B_CLK_MIN_DIV)
    {
      /* Configure max bitrate (src_clk / 2) */
      brdv = 0;
      spbr = 0;
    }
  else
    {
      /* Find the smallest value for BRDV (N) possible
       * Possible dividers for values of BRDV:
       *   BRDV = 0; div = [2,4,6,..,512]
       *   BRDV = 1; div = [4,8,12,..,1024]
       *   BRDV = 2; div = [8,16,24,..,2048]
       *   BRDV = 3; div = [16,32,48,..,4096]
       */
      uint8_t i;
      for (i = 0; i < 4; i++)
        {
          if (desired_divider <= (R_SPI_B_CLK_N_DIV_MULTIPLIER << i))
            {
              break;
            }
        }

      brdv = i & 0x03U;

      /* Calculate SPBR value
       * desired_divider = 2 * (spbr + 1) * 2^brdv
       * Therefore: spbr = (desired_divider / (2 * 2^brdv)) - 1
       */
      uint32_t spbr_divisor = (2U * (1U << brdv));

      /* Round up to ensure we don't exceed requested frequency */
      spbr = (uint8_t)(((desired_divider + spbr_divisor - 1U) / spbr_divisor) - 1U);

      /* Ensure SPBR doesn't overflow */
      if (spbr > 255)
        {
          spbr = 255;
        }
    }

  /* Calculate actual frequency based on the selected SPBR and BRDV
   * Bit rate = src_clk / (2 * (SPBR + 1) * 2^BRDV)
   */
  actual = src_clk / (2 * (spbr + 1) * (1U << brdv));

  spiinfo("SPI%d SPBR=%d BRDV=%d actual=%lu\n",
          priv->config->bus, spbr, brdv, (unsigned long)actual);

  /* Write to SPCR3 register */
  uint32_t spcr3 = ra_spi_getreg32(priv, R_SPI_B_SPCR3_OFFSET);
  spcr3 &= ~R_SPI_B_SPCR3_SPBR_MASK;
  spcr3 |= ((spbr & 0xFF) << R_SPI_B_SPCR3_SPBR_SHIFT);
  ra_spi_putreg32(priv, R_SPI_B_SPCR3_OFFSET, spcr3);

  /* Write BRDV to SPCMD0 */
  uint32_t spcmd0 = ra_spi_getreg32(priv, R_SPI_B_SPCMD0_OFFSET);
  spcmd0 &= ~R_SPI_B_SPCMD_BRDV_MASK;
  spcmd0 |= (brdv << R_SPI_B_SPCMD_BRDV_SHIFT);
  ra_spi_putreg32(priv, R_SPI_B_SPCMD0_OFFSET, spcmd0);

  /* Update current configured frequency */
  if (priv)
    {
      priv->frequency = actual;
    }

  return actual;
}

/****************************************************************************
 * Name: ra_spi_setmode
 *
 * Description:
 *   Set the SPI mode.  see enum spi_mode_e for mode definitions
 *
 * Input Parameters:
 *   dev  - Device-specific state data
 *   mode - The SPI mode requested
 *
 * Returned Value:
 *   Returns the actual frequency selected
 *
 ****************************************************************************/

static void ra_spi_setmode(struct spi_dev_s *dev, enum spi_mode_e mode)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)dev;
  uint8_t cpol = 0;
  uint8_t cpha = 0;

  spiinfo("SPI%d mode %d\n", priv->config->bus, mode);

  /* Skip reprogramming if mode unchanged */
  if (priv && priv->mode == mode)
    {
      spiinfo("SPI%d mode unchanged (%d) - skip\n", priv->config->bus, mode);
      return;
    }

  switch (mode)
    {
      case SPIDEV_MODE0: /* CPOL=0; CPHA=0 */
        cpol = 0;
        cpha = 0;
        break;

      case SPIDEV_MODE1: /* CPOL=0; CPHA=1 */
        cpol = 0;
        cpha = 1;
        break;

      case SPIDEV_MODE2: /* CPOL=1; CPHA=0 */
        cpol = 1;
        cpha = 0;
        break;

      case SPIDEV_MODE3: /* CPOL=1; CPHA=1 */
        cpol = 1;
        cpha = 1;
        break;

      default:
        spierr("SPI%d bad mode %d\n", priv->config->bus, mode);
        DEBUGASSERT(false);
        return;
    }

  spiinfo("SPI%d mode %d -> CPOL=%d CPHA=%d\n",
    priv->config->bus, mode, cpol, cpha);

  /* Write to SPCMD0 register */
  uint16_t spcmd0 = ra_spi_getreg32(priv, R_SPI_B_SPCMD0_OFFSET);
  spcmd0 &= ~(R_SPI_B_SPCMD_CPOL | R_SPI_B_SPCMD_CPHA);

  if (cpol)
    {
      spcmd0 |= R_SPI_B_SPCMD_CPOL;
    }
  if (cpha)
    {
      spcmd0 |= R_SPI_B_SPCMD_CPHA;
    }

  ra_spi_putreg32(priv, R_SPI_B_SPCMD0_OFFSET, spcmd0);

  /* Cache current mode */
  if (priv)
    {
      priv->mode = mode;
    }
}

/****************************************************************************
 * Name: ra_spi_setbits
 *
 * Description:
 *   Set the number of bits per word.
 *
 * Input Parameters:
 *   dev   - Device-specific state data
 *   nbits - The number of bits per word
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

static void ra_spi_setbits(struct spi_dev_s *dev, int nbits)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)dev;
  uint32_t spb_bits;

  spiinfo("SPI%d nbits %d\n", priv->config->bus, nbits);

  /* Skip reprogramming if bit width unchanged */
  if (priv && priv->nbits == nbits)
    {
      spiinfo("SPI%d nbits unchanged (%d) - skip\n", priv->config->bus, nbits);
      return;
    }

  /* Convert nbits to SPB field value */
  switch (nbits)
    {
      case 4:
        spb_bits = R_SPI_B_SPCMD_SPB_4;
        break;
      case 8:
        spb_bits = R_SPI_B_SPCMD_SPB_8;
        break;
      case 16:
        spb_bits = R_SPI_B_SPCMD_SPB_16;
        break;
      case 20:
        spb_bits = R_SPI_B_SPCMD_SPB_20;
        break;
      case 24:
        spb_bits = R_SPI_B_SPCMD_SPB_24;
        break;
      case 32:
        spb_bits = R_SPI_B_SPCMD_SPB_32;
        break;
      default:
        spierr("SPI%d bad nbits %d\n", priv->config->bus, nbits);
        return;
    }

  spiinfo("SPI%d nbits %d -> SPB=0x%08lx\n",
    priv->config->bus, nbits, (unsigned long)spb_bits);

  /* Write to SPCMD0 register */
  uint32_t spcmd0 = ra_spi_getreg32(priv, R_SPI_B_SPCMD0_OFFSET);
  spcmd0 &= ~R_SPI_B_SPCMD_SPB_MASK;
  spcmd0 |= spb_bits;
  ra_spi_putreg32(priv, R_SPI_B_SPCMD0_OFFSET, spcmd0);

  /* Cache current bits-per-word */
  if (priv)
    {
      priv->nbits = nbits;
    }
}

#ifdef CONFIG_SPI_HWFEATURES
/****************************************************************************
 * Name: ra_spi_hwfeatures
 *
 * Description:
 *   Set hardware-specific feature flags.
 *
 * Input Parameters:
 *   dev      - Device-specific state data
 *   features - H/W feature flags
 *
 * Returned Value:
 *   Zero (OK) if the selected H/W features are enabled; A negated errno
 *   value if any H/W feature is not supportable.
 *
 ****************************************************************************/

static int ra_spi_hwfeatures(struct spi_dev_s *dev, spi_hwfeatures_t features)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)dev;

  spiinfo("SPI%d features %08lx\n", priv->config->bus, (unsigned long)features);

  /* Other H/W features are not supported */
  return ((features & ~HWFEAT_FORCE_CS) == 0) ? OK : -ENOSYS;
}
#endif

/****************************************************************************
 * Name: ra_spi_send
 *
 * Description:
 *   Exchange one word on SPI
 *
 * Input Parameters:
 *   dev - Device-specific state data
 *   wd  - The word to send.  the size of the data is determined by the
 *         number of bits selected for the SPI interface.
 *
 * Returned Value:
 *   response
 *
 ****************************************************************************/

static uint32_t ra_spi_send(struct spi_dev_s *dev, uint32_t wd)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)dev;
  uint32_t ret;

  DEBUGASSERT(priv != NULL);

  /* Write the word to transmit */
  ra_spi_writeword(priv, wd);

  /* Read the received word */
  ret = ra_spi_readword(priv);

  spiinfo("SPI%d sent %08lx received %08lx\n",
    priv->config->bus, (unsigned long)wd, (unsigned long)ret);

  return (uint32_t)ret;
}

/****************************************************************************
 * Name: ra_spi_exchange
 *
 * Description:
 *   Exchange a block of data from SPI with enhanced DTC support
 *
 * Input Parameters:
 *   dev      - Device-specific state data
 *   txbuffer - A pointer to the buffer of data to be sent
 *   rxbuffer - A pointer to the buffer in which to receive data
 *   nwords   - the length of data that to be exchanged in units of words.
 *              The wordsize is determined by the number of bits-per-word
 *              selected for the SPI interface.  If nbits <= 8, the data is
 *              packed into uint8_t's; if nbits >8, the data is packed into
 *              uint16_t's
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

static void ra_spi_exchange(struct spi_dev_s *dev, const void *txbuffer,
                    void *rxbuffer, size_t nwords)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)dev;
#ifdef CONFIG_RA_DMAC
  bool use_dma = priv->config->use_dma;
#endif
#ifdef CONFIG_RA_DTC
  bool use_dtc = priv->config->use_dtc;
#endif

  DEBUGASSERT(priv != NULL);

  spiinfo("SPI%d txbuffer=%p rxbuffer=%p nwords=%zu\n",
          priv->config->bus, txbuffer, rxbuffer, nwords);

  if (nwords == 0)
    {
      return;
    }

  /* Setup the transfer */
  priv->txbuffer = txbuffer;
  priv->rxbuffer = rxbuffer;
  priv->ntxwords = nwords;
  priv->nrxwords = nwords;
  priv->error = false;

#ifdef CONFIG_RA_DMAC
  /* Use DMAC if enabled and transfer size meets threshold */
#ifndef CONFIG_RA_SPI_DMAC_THRESHOLD
#  define CONFIG_RA_SPI_DMAC_THRESHOLD 8
#endif
  if (use_dma && nwords >= CONFIG_RA_SPI_DMAC_THRESHOLD)
    {
      int ret;

      spiinfo("SPI%d using DMA for transfer\n", priv->config->bus);

      /* Configure and start DMA transfer */
      ret = ra_spi_dma_transfer(priv, txbuffer, rxbuffer, nwords);
      if (ret < 0)
        {
          spierr("SPI%d DMA setup failed: %d, falling back to DTC/PIO\n",
                 priv->config->bus, ret);
        }
      else
        {
          /* Start SPI transfer */
          ra_spi_start_transfer(priv);

          /* Wait for completion */
          nxsem_wait_uninterruptible(&priv->waitsem);

          /* Stop DMA and release resources */
          ra_spi_dma_stop(priv);

          if (priv->error)
            {
              spierr("SPI%d DMA transfer error\n", priv->config->bus);
            }
          return;
        }
    }
#endif /* CONFIG_RA_DMAC */

#ifdef CONFIG_RA_DTC
  /* Use DTC if enabled and transfer size meets threshold */
#ifndef CONFIG_RA_SPI_DTC_THRESHOLD
#  define CONFIG_RA_SPI_DTC_THRESHOLD 4
#endif
  if (use_dtc && nwords >= CONFIG_RA_SPI_DTC_THRESHOLD)
    {
      /* Prepare DTC transfer_info structures */
      ra_spi_dtc_configure_transfer(priv, txbuffer, rxbuffer, nwords);

      /* Commit transfer_info into DTC vector table and enable ICU triggers */
      ra_spi_dtc_reconfigure(priv);
    }
#endif /* CONFIG_RA_DTC */

  /* Start transfer */
  ra_spi_start_transfer(priv);

  /* Wait for completion */
  nxsem_wait_uninterruptible(&priv->waitsem);

  if (priv->error)
    {
      spierr("SPI%d transfer error\n", priv->config->bus);
    }
}

#ifndef CONFIG_SPI_EXCHANGE

/****************************************************************************
 * Name: ra_spi_sndblock
 *
 * Description:
 *   Send a block of data on SPI
 *
 * Input Parameters:
 *   dev      - Device-specific state data
 *   txbuffer - A pointer to the buffer of data to be sent
 *   nwords   - the length of data to send from the buffer in number of words.
 *              The wordsize is determined by the number of bits-per-word
 *              selected for the SPI interface.
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

static void ra_spi_sndblock(struct spi_dev_s *dev, const void *txbuffer,
                    size_t nwords)
{
  spiinfo("txbuffer=%p nwords=%zu\n", txbuffer, nwords);
  return ra_spi_exchange(dev, txbuffer, NULL, nwords);
}

/****************************************************************************
 * Name: ra_spi_recvblock
 *
 * Description:
 *   Receive a block of data from SPI
 *
 * Input Parameters:
 *   dev      - Device-specific state data
 *   rxbuffer - A pointer to the buffer in which to receive data
 *   nwords   - the length of data that can be received in the buffer in number
 *              of words.  The wordsize is determined by the number of bits-per-word
 *              selected for the SPI interface.
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

static void ra_spi_recvblock(struct spi_dev_s *dev, void *rxbuffer,
                    size_t nwords)
{
  spiinfo("rxbuffer=%p nwords=%zu\n", rxbuffer, nwords);
  return ra_spi_exchange(dev, NULL, rxbuffer, nwords);
}

#endif /* !CONFIG_SPI_EXCHANGE */

#ifdef CONFIG_SPI_TRIGGER
/****************************************************************************
 * Name: ra_spi_trigger
 *
 * Description:
 *   Trigger a previously configured DMA transfer.
 *
 * Input Parameters:
 *   dev      - Device-specific state data
 *
 * Returned Value:
 *   OK       - Trigger was fired
 *   -ENOSYS  - Trigger not fired due to lack of DMA or low level support
 *   -EIO     - Trigger not fired because not previously primed
 *
 ****************************************************************************/

static int ra_spi_trigger(struct spi_dev_s *dev)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)dev;
  bool use_dma_dtc = false;

  /* Check if DTC or DMA is enabled at bus level */
#ifdef CONFIG_RA_DTC
  if (priv->config->use_dtc)
    {
      use_dma_dtc = true;
    }
#endif
#ifdef CONFIG_RA_DMAC
  if (priv->config->use_dma)
    {
      use_dma_dtc = true;
    }
#endif

  if (!use_dma_dtc)
    {
      return -ENOSYS;
    }

  /* TODO: Implement trigger */
  return -ENOSYS;
}
#endif

/****************************************************************************
 * Name: ra_spi_bus_initialize
 *
 * Description:
 *   Initialize the selected SPI bus in its default state (Master, 8-bit,
 *   mode 0, etc.)
 *
 * Input Parameters:
 *   priv   - private SPI device structure
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

static void ra_spi_bus_initialize(struct ra_spi_priv_s *priv)
{
  uint32_t spcr   = 0;
  uint32_t spcr2  = 0;
  uint32_t spcr3  = 0;
  uint32_t spdecr = 0;
  uint32_t spcmd0 = 0;
  uint32_t spdcr  = 0;
  /* SPCMD0 default */
  uint32_t ssla = R_SPI_B_SPCMD_SSLA_0;

  /* Enable SPI module via MSTP */
#if defined(CONFIG_RA_SPI0)
  if (priv->config->base == R_SPI_B_CH_BASE(0))
    {
      ra_mstp_start(RA_MSTP_SPI0);
    }
  else
#endif
#if defined(CONFIG_RA_SPI1)
  if (priv->config->base == R_SPI_B_CH_BASE(1))
    {
      ra_mstp_start(RA_MSTP_SPI1);
    }
  else
#endif
    {
      spierr("SPI%d invalid module\n", priv->config->bus);
      return;
    }

  /* Disable SPI before configuration */
  ra_spi_putreg32(priv, R_SPI_B_SPCR_OFFSET, 0);

  /* Clear status flags */
  ra_spi_putreg32(priv, R_SPI_B_SPSRC_OFFSET, R_SPI_B_SPSRC_ALL_CLEAR);

  /* Configure SPCR */
  spcr |= R_SPI_B_SPCR_SPEIE | R_SPI_B_SPCR_CENDIE;

  if (priv->config->master_mode)
    {
      spcr |= R_SPI_B_SPCR_MSTR;
      spcr |= R_SPI_B_SPCR_SCKASE;

      /* Configure delays */
      uint32_t setup = R_SPI_B_CS_SETUP_DELAY;
      uint32_t neg   = R_SPI_B_CS_NEGATION_DELAY;
      uint32_t hold  = R_SPI_B_CS_HOLD_DELAY;

      spdecr = ((setup & 0x07) << R_SPI_B_SPDECR_SCKDL_SHIFT) |
               ((neg & 0x07) << R_SPI_B_SPDECR_SLNDL_SHIFT) |
               ((hold & 0x07) << R_SPI_B_SPDECR_SPNDL_SHIFT);
      ra_spi_putreg32(priv, R_SPI_B_SPDECR_OFFSET, spdecr);

      if (priv->config->ssl_select != 0xFF) {
        ssla = (priv->config->ssl_select & 0x7) << R_SPI_B_SPCMD_SSLA_SHIFT;
      }
      spcmd0 = R_SPI_B_SPCMD_SPB_8 | R_SPI_B_SPCMD_BRDV_1 | ssla |
               R_SPI_B_SPCMD_SCKDEN | R_SPI_B_SPCMD_SLNDEN | R_SPI_B_SPCMD_SPNDEN;
      ra_spi_putreg32(priv, R_SPI_B_SPCMD0_OFFSET, spcmd0);
    }
  else
    {
      spcr |= R_SPI_B_SPCR_MODFEN;
    }

  /* SPCR2 default */
  ra_spi_putreg32(priv, R_SPI_B_SPCR2_OFFSET, spcr2);

  /* Enable interrupts */
  spcr |= R_SPI_B_SPCR_SPTIE | R_SPI_B_SPCR_SPRIE;

  /* Bit-rate switch enabled (BPEN) */
  spcr |= R_SPI_B_SPCR_BPEN;

  /* Write SPCR without SPE first */
  ra_spi_putreg32(priv, R_SPI_B_SPCR_OFFSET, spcr & ~R_SPI_B_SPCR_SPE);
  ra_spi_putreg32(priv, R_SPI_B_SPCR_OFFSET, spcr);

  /* Configure SPCR3
   * - SSL polarity defaults (active low)
   * - bit rate field will be set by ra_spi_setfrequency
   */
  ra_spi_putreg32(priv, R_SPI_B_SPCR3_OFFSET, spcr3);

  /* Configure SPDCR default */
  ra_spi_putreg32(priv, R_SPI_B_SPDCR_OFFSET, spdcr);

  /* Set default bit rate to 1MHz and mode 3 with 8 bits */
  ra_spi_setfrequency(&priv->spidev, R_SPI_B_DEFAULT_FREQUENCY);
  ra_spi_setmode(&priv->spidev, SPIDEV_MODE3);
  ra_spi_setbits(&priv->spidev, 8);

  /* Current transfer parameters */
  priv->frequency = R_SPI_B_DEFAULT_FREQUENCY;  /* Requested clock frequency */
  priv->mode = SPIDEV_MODE3;       /* Current SPI mode */
  priv->nbits = 8;      /* Number of bits per word */

#ifdef CONFIG_RA_DTC
  /* Setup DTC if bus config enables it */
  if (priv->config->use_dtc)
    {
      ra_spi_dtc_setup(priv);
    }
#endif

#ifdef CONFIG_RA_DMAC
  /* Setup DMA if bus config enables it */
  if (priv->config->use_dma)
    {
      ra_spi_dma_setup(priv);
    }
#endif
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_spibus_initialize
 *
 * Description:
 *   Initialize the selected SPI bus
 *
 * Input Parameters:
 *   bus number (for hardware that has multiple SPI interfaces)
 *
 * Returned Value:
 *   Valid SPI device structure reference on success; a NULL on failure
 *
 ****************************************************************************/

struct spi_dev_s *ra_spibus_initialize(int bus)
{
  struct ra_spi_priv_s *priv = NULL;
  int ret;

  spiinfo("Initializing SPI%d\n", bus);

#ifdef CONFIG_RA_SPI0
  if (bus == 0)
    {
      priv = &ra_spi0_priv;
    }
#endif
#ifdef CONFIG_RA_SPI1
  if (bus == 1)
    {
      priv = &ra_spi1_priv;
    }
#endif

  if (priv == NULL)
    {
      spierr("SPI%d not configured\n", bus);
      return NULL;
    }

  /* Has the SPI hardware been initialized? */
  if (priv->refs == 0)
    {
      /* Initialize hardware first */
      ra_spi_bus_initialize(priv);

      /* Attach interrupts */
#if (CONFIG_RA_DMAC)
      if (!priv->config->use_dma)
        {
          ret = ra_icu_attach(priv->config->rxi_elc, ra_spi_rxi_interrupt, priv, true);
          if (ret < 0)
            {
              return NULL;
            }
          priv->rxi_irq = ret;

          ret = ra_icu_attach(priv->config->txi_elc, ra_spi_txi_interrupt, priv, true);
          if (ret < 0)
            {
              return NULL;
            }
          priv->txi_irq = ret;
        }
#endif
      ret = ra_icu_attach(priv->config->tei_elc, ra_spi_tei_interrupt, priv, false);
      if (ret < 0)
        {
          return NULL;
        }
      priv->tei_irq = ret;

      ret = ra_icu_attach(priv->config->eri_elc, ra_spi_eri_interrupt, priv, true);
      if (ret < 0)
        {
          return NULL;
        }
      priv->eri_irq = ret;

      spiinfo("SPI%d interrupts attached: RXI=%d TXI=%d TEI=%d ERI=%d\n",
              priv->config->bus, priv->rxi_irq, priv->txi_irq, priv->tei_irq, priv->eri_irq);
    }

  /* Increment reference count */
  priv->refs++;

  return (struct spi_dev_s *)priv;
}

/****************************************************************************
 * Name: ra_spi_setbitorder
 *
 * Description:
 *   Set the SPI bit order (MSB-first or LSB-first)
 *
 * Input Parameters:
 *   dev      - SPI device structure
 *   lsbfirst - true for LSB-first, false for MSB-first
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

void ra_spi_setbitorder(struct spi_dev_s *dev, bool lsbfirst)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)dev;
  uint32_t spcmd0;

  spiinfo("SPI%d bit order %s\n", priv->config->bus, lsbfirst ? "LSB-first" : "MSB-first");

  /* Read SPCMD0 register */
  spcmd0 = ra_spi_getreg32(priv, R_SPI_B_SPCMD0_OFFSET);

  /* Set or clear LSBF bit */
  if (lsbfirst)
    {
      spcmd0 |= R_SPI_B_SPCMD_LSBF;
    }
  else
    {
      spcmd0 &= ~R_SPI_B_SPCMD_LSBF;
    }

  /* Write back to SPCMD0 */
  ra_spi_putreg32(priv, R_SPI_B_SPCMD0_OFFSET, spcmd0);
}

/****************************************************************************
 * Name: ra_spi_setssl
 *
 * Description:
 *   Set the hardware chip select (SSL) for the SPI device.
 *   This function updates the SSLA field in SPCMD0 to select which
 *   hardware SSL pin (SSL0-SSL3) to use for the current transfer.
 *
 * Input Parameters:
 *   dev        - SPI device structure
 *   ssl_select - Slave selection ID (0-3 for SSL0-SSL3, 0xFF for GPIO CS)
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

void ra_spi_setssl(struct spi_dev_s *dev, uint8_t ssl_select)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)dev;
  uint32_t spcmd0;
  uint32_t ssla;

  DEBUGASSERT(priv != NULL);

  /* Only update if using hardware CS (ssl_select 0-3) */
  if (ssl_select > 3 || priv->config->ssl_select == ssl_select)
    {
      /* 0xFF or other values indicate GPIO CS - no hardware SSL update needed */
      spiinfo("SPI%d: GPIO CS mode (ssl_select=0x%02x), skipping SSLA update\n",
              priv->config->bus, ssl_select);
      return;
    }

  /* Read current SPCMD0 register */
  spcmd0 = ra_spi_getreg32(priv, R_SPI_B_SPCMD0_OFFSET);

  /* Clear existing SSLA field */
  spcmd0 &= ~R_SPI_B_SPCMD_SSLA_MASK;

  /* Set new SSLA value (0-3 maps to SSL0-SSL3) */
  ssla = (ssl_select & 0x7) << R_SPI_B_SPCMD_SSLA_SHIFT;
  spcmd0 |= ssla;

  /* Write back to SPCMD0 */
  ra_spi_putreg32(priv, R_SPI_B_SPCMD0_OFFSET, spcmd0);

  spiinfo("SPI%d: Hardware SSL%d selected (SPCMD0=0x%08lx)\n",
          priv->config->bus, ssl_select, (unsigned long)spcmd0);
}

/****************************************************************************
 * Name: ra_spi_set_loopback
 *
 * Description:
 *   Enable/disable SPI loopback2 (SPLP2) and optional MOSI idle settings
 *   for a given SPI device. This function will clear SPE while changing
 *   control bits and restore the previous SPE state.
 ****************************************************************************/

int ra_spi_set_loopback(FAR struct spi_dev_s *dev, bool loopback2,
                    bool moifv, bool moife)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)dev;
  uint32_t spcr;
  volatile uint32_t spcr2;

  if (!priv || !priv->config)
    {
      return -EINVAL;
    }

  /* Read current SPCR/SPCR2 via driver helpers */
  spcr  = ra_spi_getreg32(priv, R_SPI_B_SPCR_OFFSET);
  spcr2 = ra_spi_getreg32(priv, R_SPI_B_SPCR2_OFFSET);

  /* Disable SPI while changing control bits */
  if (spcr & R_SPI_B_SPCR_SPE)
    {
      ra_spi_putreg32(priv, R_SPI_B_SPCR_OFFSET, spcr & ~R_SPI_B_SPCR_SPE);
      (void)ra_spi_getreg32(priv, R_SPI_B_SPCR_OFFSET);
    }

  /* Update SPCR2 pin control bits: SPLP2, MOIFV, MOIFE */
  if (loopback2)
    {
      spcr2 |= R_SPI_B_SPCR2_SPLP2;
    }
  else
    {
      spcr2 &= ~R_SPI_B_SPCR2_SPLP2;
    }

  if (moifv)
    {
      spcr2 |= R_SPI_B_SPCR2_MOIFV;
      if (moife)
        {
          spcr2 |= R_SPI_B_SPCR2_MOIFE;
        }
    }
  else
    {
      spcr2 &= ~R_SPI_B_SPCR2_MOIFV;
      spcr2 &= ~R_SPI_B_SPCR2_MOIFE;
    }

  /* Write back SPCR2 */
  ra_spi_putreg32(priv, R_SPI_B_SPCR2_OFFSET, spcr2);
  spcr2 = ra_spi_getreg32(priv, R_SPI_B_SPCR2_OFFSET);
  (void)spcr2;

  /* Restore SPE if it was previously enabled */
  if (spcr & R_SPI_B_SPCR_SPE)
    {
      ra_spi_putreg32(priv, R_SPI_B_SPCR_OFFSET, spcr | R_SPI_B_SPCR_SPE);
      (void)ra_spi_getreg32(priv, R_SPI_B_SPCR_OFFSET);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_spi_select
 *
 * Description:
 *   Board-specific SPI device select function called by the SPI driver.
 *   This is a weak function that can be overridden by board-specific
 *   implementations.
 *
 ****************************************************************************/

void weak_function ra_spi_select(struct spi_dev_s *dev, uint32_t devid,
                    bool selected)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)dev;

  DEBUGASSERT(priv != NULL);

  spiinfo("SPI%d devid=0x%08lx selected=%d\n", priv->config->bus, (unsigned long)devid, selected);

  priv->devid = devid;
}

/****************************************************************************
 * Name: ra_spi_status
 *
 * Description:
 *   Board-specific SPI device status function called by the SPI driver.
 *   This is a weak function that can be overridden by board-specific
 *   implementations.
 *
 ****************************************************************************/

uint8_t weak_function ra_spi_status(struct spi_dev_s *dev, uint32_t devid)
{
  UNUSED(dev);
  UNUSED(devid);
  return 0;
}

/****************************************************************************
 * Name: ra_spi_cmddata
 *
 * Description:
 *   Board-specific SPI command/data function called by the SPI driver.
 *   This is a weak function that can be overridden by board-specific
 *   implementations.
 *
 ****************************************************************************/

#ifdef CONFIG_SPI_CMDDATA
int weak_function ra_spi_cmddata(struct spi_dev_s *dev, uint32_t devid,
                    bool cmd)
{
  UNUSED(dev);
  UNUSED(devid);
  UNUSED(cmd);
  return OK;
}
#endif
/****************************************************************************
 * Name: ra_spi_register_callback
 *
 * Description:
 *   Board-specific SPI register callback function called by the SPI driver.
 *   This is a weak function that can be overridden by board-specific
 *   implementations.
 *
 ****************************************************************************/

#ifdef CONFIG_SPI_CALLBACK
int weak_function ra_spi_register_callback(struct spi_dev_s *dev,
                    spi_callback_t callback, void *arg)
{
  UNUSED(dev);
  UNUSED(callback);
  UNUSED(arg);
  return OK;
}
#endif

#endif /* CONFIG_RA_SPI */

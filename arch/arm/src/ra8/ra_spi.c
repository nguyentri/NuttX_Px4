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

#include "ra_gpio.h"
#include "ra_clock.h"
#include "ra_dtc.h"
#include "ra_mstp.h"
#include "ra_spi.h"

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

/* Max frequency (8 MHz) */
#define R_SPI_B_MAX_FREQUENCY            8000000

/* All clear flags for SPSRC register */
#define R_SPI_B_SPSRC_ALL_CLEAR          (R_SPI_B_SPSRC_SPDRFC | R_SPI_B_SPSRC_OVRFC | \
                                          R_SPI_B_SPSRC_MODFC | R_SPI_B_SPSRC_PERFC | \
                                          R_SPI_B_SPSRC_UDRFC | R_SPI_B_SPSRC_SPTEFC | \
                                          R_SPI_B_SPSRC_CENDFC | R_SPI_B_SPSRC_SPRFC)

/* SPI timeout */
#define R_SPI_B_TIMEOUT_MS          1000

/* Default CS timing values     */
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

  uint8_t  bus;           /* SPI bus number */
  int  rxi_elc;            /* Even Link for RX interrupt */
  int  txi_elc;            /* Even Link for TX interrupt */
  int  tei_elc;            /* Even Link for Transfer end interrupt */
  int  eri_elc;            /* Even Link for Error interrupt */
  uint32_t mstpcrb_bit;   /* Module stop control bit */

  /* Pin configuration - hardware specific */
  gpio_pinset_t sck_pin;       /* SCK pin configuration */
  gpio_pinset_t miso_pin;      /* MISO pin configuration */
  gpio_pinset_t mosi_pin;      /* MOSI pin configuration */

  bool     master_mode;        /* true: master, false: slave */
  struct ra_spi_ext_dev_config_s *dev_config;  /* Array of external device configurations */
  int num_cs;                     /* Number of external device configurations */
};

/* SPI Device Private Data */
struct ra_spi_priv_s
{
  /* Externally visible part of the SPI interface */
  struct spi_dev_s         spidev;

  uint32_t                 devid; /* Currently selected external device ID */

  /* SPI hardware unit configuration */
  const struct ra_spi_config_s *config;

  int                      refs;       /* Reference count */
  mutex_t                  lock;       /* Held while chip is selected for mutual exclusion */

  /* Runtime IRQ numbers assigned by ICU */
  int                      rxi_irq;    /* RX interrupt number */
  int                      txi_irq;    /* TX interrupt number */
  int                      tei_irq;    /* Transfer end interrupt number */
  int                      eri_irq;    /* Error interrupt number */

  /* Transfer state */
  sem_t                    waitsem;    /* Wait for transfer completion */
  const void              *txbuffer;   /* Source data */
  void                    *rxbuffer;   /* Destination data */
  size_t                   ntxwords;   /* Number of words to transfer */
  size_t                   nrxwords;   /* Number of words to receive */
  bool                     error;      /* Transfer error flag */

  /* DTC channels and configuration */
  bool                     use_dtc;
  bool                     dtc_active; /* DTC transfer in progress */
  int                      dtc_tx;     /* TX DTC channel */
  int                      dtc_rx;     /* RX DTC channel */
  ra_dtc_info_t            dtc_tx_info; /* TX DTC transfer info */
  ra_dtc_info_t            dtc_rx_info; /* RX DTC transfer info */

#ifdef CONFIG_PM
  struct pm_callback_s     pmcb;       /* PM callbacks */
#endif
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Low-level helpers */
static void ra_spi_putreg32(struct ra_spi_priv_s *priv, uint8_t offset, uint32_t value);
static uint32_t ra_spi_getreg32(struct ra_spi_priv_s *priv, uint8_t offset);

/* DTC support */
static int ra_spi_dtc_setup(struct ra_spi_priv_s *priv);
static void ra_spi_start_transfer(struct ra_spi_priv_s *priv);
static void ra_spi_dtc_stop(struct ra_spi_priv_s *priv);
static int ra_spi_dtc_configure_transfer(struct ra_spi_priv_s *priv,
                                         const void *txbuffer, void *rxbuffer,
                                         size_t nwords);
static int ra_spi_dtc_reconfigure(struct ra_spi_priv_s *priv);

/* Transfer helpers */
static void ra_spi_writeword(struct ra_spi_priv_s *priv, uint32_t word);
static uint32_t ra_spi_readword(struct ra_spi_priv_s *priv);
static int ra_spi_get_transfer_size(struct ra_spi_priv_s *priv);

/* Interrupt handling */
static int ra_spi_rxi_interrupt(int irq, void *context, void *arg);
static int ra_spi_txi_interrupt(int irq, void *context, void *arg);
static int ra_spi_tei_interrupt(int irq, void *context, void *arg);
static int ra_spi_eri_interrupt(int irq, void *context, void *arg);

/* external device configuration */
const struct ra_spi_ext_dev_config_s * weak_function ra_spi_get_dev_config(struct spi_dev_s *dev, uint32_t devid);

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

/* DTC initialization flag */
static bool g_dtc_initialized = false;
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

 /* Pin configuration - uses board-specific definitions from board.h */
  .sck_pin     = GPIO_SPI0_SCK,     /* SPI Clock pin */
  .miso_pin    = GPIO_SPI0_MISO,    /* SPI MISO pin */
  .mosi_pin    = GPIO_SPI0_MOSI,    /* SPI MOSI pin */

  .master_mode = true,  /* Default to master mode */

  .dev_config = NULL,  /* Application-specific external device configurations will be initialized by the runtime */

  .num_cs = 0,        /* Number of external device configurations will be set at runtime */
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
  .devid    = 0xffffffff,
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

  /* Pin configuration - uses board-specific definitions from board.h */
  .sck_pin     = GPIO_SPI1_SCK,     /* SPI Clock pin */
  .miso_pin    = GPIO_SPI1_MISO,    /* SPI MISO pin */
  .mosi_pin    = GPIO_SPI1_MOSI,    /* SPI MOSI pin */

  .master_mode = true,  /* Default to master mode */

  .dev_config  = NULL,  /* Application-specific external device configurations will be initialized by the runtime */

  .num_cs      = 0,        /* Number of external device configurations will be set at runtime */
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
  .devid    = 0xffffffff,
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
  /* Wait until the transmit buffer is empty */
  //while ((ra_spi_getreg32(priv, R_SPI_B_SPSR_OFFSET) & R_SPI_B_SPSR_SPTEF) == 0);

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
  /* Wait until receive buffer is full */
  //while ((ra_spi_getreg32(priv, R_SPI_B_SPSR_OFFSET) & R_SPI_B_SPSR_SPRF) == 0);

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
}/****************************************************************************
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
          ra_mstp_start(RA_MSTP_DMAC_DTC);

          /* Initialize DTC module - this will set up the vector table */
          ra_dtc_initialize();

          g_dtc_initialized = true;

          spiinfo("DTC module initialized\n");
        }

      leave_critical_section(flags);
    }

  /* Should be configurable but currently hardcoded */
  priv->use_dtc = false;

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
      /* Configure TX DTC: source increment, dest fixed, normal mode */
      priv->dtc_tx_info.mra = RA_DTC_MRA_MD_NORMAL | transfer_size | RA_DTC_MRA_SM_INCREMENT;
      priv->dtc_tx_info.mrb = RA_DTC_MRB_DM_FIXED | RA_DTC_MRB_DISEL; /* IRQ at end */
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
      /* Configure RX DTC: source fixed, dest increment, normal mode */
      priv->dtc_rx_info.mra = RA_DTC_MRA_MD_NORMAL | transfer_size | RA_DTC_MRA_SM_FIXED;
      priv->dtc_rx_info.mrb = RA_DTC_MRB_DM_INCREMENT | RA_DTC_MRB_DISEL; /* IRQ at end */
      priv->dtc_rx_info.sar = priv->config->base + R_SPI_B_SPDR_OFFSET;
      priv->dtc_rx_info.dar = (uint32_t)rxbuffer;
      priv->dtc_rx_info.cra = (uint16_t)nwords;
      priv->dtc_rx_info.crb = 0;

      spiinfo("RX DTC: MRA=0x%02x MRB=0x%02x SAR=0x%08lx DAR=0x%08lx CRA=%d\n",
              priv->dtc_rx_info.mra, priv->dtc_rx_info.mrb,
              (unsigned long)priv->dtc_rx_info.sar, (unsigned long)priv->dtc_rx_info.dar, priv->dtc_rx_info.cra);
    }

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

  /* Enable DTC triggers in ICU using ICU API instead of direct register access */
  if (priv->txi_irq >= 0)
    {
      ra_icu_enable_dtc(priv->txi_irq);
      spiinfo("Enabled DTC trigger for TXI IRQ %d\n", priv->txi_irq);
    }

  if (priv->rxi_irq >= 0)
    {
      ra_icu_enable_dtc(priv->rxi_irq);
      spiinfo("Enabled DTC trigger for RXI IRQ %d\n", priv->rxi_irq);
    }

  /* Mark DTC as active with the current transfer */
  priv->dtc_active = true;

  return OK;
}

static void ra_spi_transmit(struct ra_spi_priv_s *priv)
{
  /* Prefill up to two transmit words to start the pipeline */
  uint32_t data = 0xffffffffU;

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
 *   Start DTC transfer
 *
 ****************************************************************************/

static void ra_spi_start_transfer(struct ra_spi_priv_s *priv)
{
  uint32_t spcr;

  spiinfo("Transfer start for SPI%d - TX IRQ=%d, RX IRQ=%d, TEI IRQ=%d, ERI IRQ=%d\n",
          priv->config->bus, priv->txi_irq, priv->rxi_irq, priv->tei_irq, priv->eri_irq);

  /* Clear any existing interrupt flags before enabling interrupts */
  ra_spi_putreg32(priv, R_SPI_B_SPSRC_OFFSET, R_SPI_B_SPSRC_ALL_CLEAR);

  /* Clear FIFOs to ensure a clean start */
  ra_spi_putreg32(priv, R_SPI_B_SPFCR_OFFSET, R_SPI_B_SPFCR_SPFRST);

  /* Get SPCR and enable appropriate interrupts for DTC-driven transfer */
  spcr = ra_spi_getreg32(priv, R_SPI_B_SPCR_OFFSET);

  /* Enable Transmit Empty interrupt if transmitting (DTC TX or TX buffer present) */
  if (priv->txbuffer)
    {
      spcr |= R_SPI_B_SPCR_SPTIE;
    }

  /* Enable Receive Buffer Full interrupt if receiving */
  if (priv->rxbuffer)
    {
      spcr |= R_SPI_B_SPCR_SPRIE;
    }

  /* Now set SPE to start the transfer. For non-DTC full-duplex transfers we
   * should preload the first one or two transmit words to fill the hardware
   * shift register and buffer.
   */
  if (!priv->dtc_active && priv->txbuffer)
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
      /* Default: enable SPE and let ISR handle transmit */
      ra_spi_putreg32(priv, R_SPI_B_SPCR_OFFSET, spcr | R_SPI_B_SPCR_SPE);
    }

  spiinfo("SPI transfer started: SPCR=0x%08lx\n", spcr);
}

/****************************************************************************
 * Name: ra_spi_dtc_stop
 *
 * Description:
 *   Stop DTC transfer
 *
 ****************************************************************************/

static void ra_spi_dtc_stop(struct ra_spi_priv_s *priv)
{
  spiinfo("DTC stop for SPI%d\n", priv->config->bus);

  /* Disable DTC triggers in ICU using assigned slot numbers */
  if (priv->txi_irq >= 0)
    {
      ra_icu_disable_dtc(priv->txi_irq);
      spiinfo("Disabled DTC trigger for TXI IRQ %d\n", priv->txi_irq);
    }

  if (priv->rxi_irq >= 0)
    {
      ra_icu_disable_dtc(priv->rxi_irq);
      spiinfo("Disabled DTC trigger for RXI IRQ %d\n", priv->rxi_irq);
    }

  /* Mark DTC as no longer active */
  priv->dtc_active = false;
}

/****************************************************************************
 * Name: ra_spi_rxi_interrupt
 *
 * Description:
 *   RX interrupt handler
 *
 ****************************************************************************/

static int ra_spi_rxi_interrupt(int irq, void *context, void *arg)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)arg;
  uint32_t data;

  DEBUGASSERT(priv != NULL);

    /* RXI should not occur in DTC mode? */
  if (priv->dtc_active)
    {
      /* DTC is handling the transfer, just check for completion */
      if (priv->dtc_rx_info.cra == 1)
        {
          /* DTC transfer complete */
          ra_spi_dtc_stop(priv);
          //nxsem_post(&priv->waitsem);
          //up_enable_irq(priv->tei_irq);
          ra_spi_tei_interrupt(priv->tei_irq, NULL, priv);
          priv->dtc_active = false;
        }
      return OK;
    }
  else {
    /* Read received data */
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

    /* After last RX, enable TEI IRQ (NoClear semantics if available) */
    if (priv->nrxwords == 0)
      {
        up_enable_irq(priv->tei_irq);
        //nxsem_post(&priv->waitsem);
      }
  }

  return OK;
}

/****************************************************************************
 * Name: ra_spi_txi_interrupt
 *
 * Description:
 *   TX interrupt handler
 *
 ****************************************************************************/

static int ra_spi_txi_interrupt(int irq, void *context, void *arg)
{
  struct ra_spi_priv_s *priv = (struct ra_spi_priv_s *)arg;

  DEBUGASSERT(priv != NULL);

  if (priv->dtc_active)
    {
      /* DTC is handling the transfer, just check for completion */
      if (priv->dtc_tx_info.cra == 1)
        {
          /* DTC transfer complete */
          ra_spi_dtc_stop(priv);
          //nxsem_post(&priv->waitsem);
          //up_enable_irq(priv->tei_irq);
          ra_spi_tei_interrupt(priv->tei_irq, NULL, priv);
          priv->dtc_active = false;
        }
      return OK;
    }
  else {
    if (priv->ntxwords > 0)
      {
        /* Transmit next word */
        ra_spi_transmit(priv);
        if (priv->ntxwords == 0)
          {
              up_enable_irq(priv->tei_irq);
          }
      }
  }
  return OK;
}

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

  DEBUGASSERT(priv != NULL);

  spiinfo("SPI%d transfer end interrupt\n", priv->config->bus);

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

  /* Disable TXI IRQ before clearing SPE */
  up_disable_irq(priv->txi_irq);

  spcr = ra_spi_getreg32(priv, R_SPI_B_SPCR_OFFSET);
  ra_spi_putreg32(priv, R_SPI_B_SPCR_OFFSET, spcr & ~R_SPI_B_SPCR_SPE);

  /* Clear pending and re-enable TXI IRQ */
  ra_icu_clear_irq(priv->txi_irq);
  up_enable_irq(priv->txi_irq);

  spierr("SPI%d error interrupt: SPSR=%08lx\n", priv->config->bus, spsr);
  spsr = ra_spi_getreg32(priv, R_SPI_B_SPSR_OFFSET);
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
  /* Set error flag and wake up waiting thread */
  priv->error = true;
  if (priv->dtc_active)
    {
      ra_spi_dtc_stop(priv);
    }
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
  uint32_t src_clk = RA_PCLKA_FREQUENCY;
  uint32_t divisor;
  uint8_t spbr;
  uint8_t brdv = 0;
  uint32_t actual;

  spiinfo("SPI%d frequency %lu\n", priv->config->bus, (unsigned long)frequency);

  /* Limit to maximum frequency */
  if (frequency > R_SPI_B_MAX_FREQUENCY)
    {
      frequency = R_SPI_B_MAX_FREQUENCY;
    }

  /* Calculate the best divisor */
  /* The SPI bit rate is calculated as:
   * Bit rate = PCLKA / (2 * (SPBR + 1) * 2^BRDV)
   */

  divisor = (src_clk + frequency - 1) / frequency;

  /* Find best BRDV and SPBR combination */
  for (brdv = 0; brdv < 4; brdv++)
    {
      uint32_t div_factor = 2 << brdv;  /* 2^(brdv+1) */
      uint32_t spbr_calc = (divisor + div_factor - 1) / (2 * div_factor) - 1;

      if (spbr_calc <= 255)
        {
          spbr = (uint8_t)spbr_calc;
          break;
        }
    }

  if (brdv >= 4)
    {
      /* Use maximum divisor */
      brdv = 3;
      spbr = 255;
    }

  /* Calculate actual frequency */
  actual = src_clk / (2 * (spbr + 1) * (2 << brdv));

  spiinfo("SPI%d SPBR=%d BRDV=%d actual=%lu\n",
    priv->config->bus, spbr, brdv, (unsigned long)actual);

  /* Write to SPCR3 register (bit rate) */
  uint32_t spcr3 = ra_spi_getreg32(priv, R_SPI_B_SPCR3_OFFSET);
  spcr3 &= ~R_SPI_B_SPCR3_SPBR_MASK;
  spcr3 |= ((spbr & 0xFF) << R_SPI_B_SPCR3_SPBR_SHIFT);
  ra_spi_putreg32(priv, R_SPI_B_SPCR3_OFFSET, spcr3);

  /* Write BRDV to SPCMD0 */
  uint32_t spcmd0 = ra_spi_getreg32(priv, R_SPI_B_SPCMD0_OFFSET);
  spcmd0 &= ~R_SPI_B_SPCMD_BRDV_MASK;
  spcmd0 |= (brdv << R_SPI_B_SPCMD_BRDV_SHIFT);
  ra_spi_putreg32(priv, R_SPI_B_SPCMD0_OFFSET, spcmd0);

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

  /* Use DTC if enabled and transfer size is large enough */
  if (priv->use_dtc && nwords >= 4)
    {
      /* Prepare DTC transfer_info structures */
      ra_spi_dtc_configure_transfer(priv, txbuffer, rxbuffer, nwords);

      /* Commit transfer_info into DTC vector table and enable ICU triggers */
      ra_spi_dtc_reconfigure(priv);
    }

  /* Start transfer (clear FIFOs, enable interrupts and set SPE) */
  /* Note: SPCR3/SPCMD0 already configured by SPI_SETFREQUENCY/SETMODE/SETBITS */
  ra_spi_start_transfer(priv);

  /* Wait for completion (TEI interrupt will signal completion) */
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

  if (!priv->use_dtc)
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

  /* Configure GPIO pins for SPI */
  ra_configgpio(priv->config->sck_pin);
  ra_configgpio(priv->config->miso_pin);
  ra_configgpio(priv->config->mosi_pin);

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

  /* Disable SPI (clear SPCR) before configuration */
  ra_spi_putreg32(priv, R_SPI_B_SPCR_OFFSET, 0);

  /* Clear status flags */
  ra_spi_putreg32(priv, R_SPI_B_SPSRC_OFFSET, R_SPI_B_SPSRC_ALL_CLEAR);

  /* Configure basic SPCR bits from configuration
   * - enable error interrupt and communication end interrupt
   * - set master mode and auto-stop when master
   */
  spcr |= R_SPI_B_SPCR_SPEIE | R_SPI_B_SPCR_CENDIE;

  if (priv->config->master_mode)
    {
      spcr |= R_SPI_B_SPCR_MSTR;
      spcr |= R_SPI_B_SPCR_SCKASE; /* SCK Auto Stop for master */

      /* Configure SPDECR delays using defaults or external device configuration if available */
      uint32_t setup = R_SPI_B_CS_SETUP_DELAY;
      uint32_t neg   = R_SPI_B_CS_NEGATION_DELAY;
      uint32_t hold  = R_SPI_B_CS_HOLD_DELAY;

      if (priv->config->dev_config && priv->config->num_cs > 0)
        {
          /* Use first CS entry for defaults; application may override per-device */
          setup = priv->config->dev_config[0].setup_delay;
          neg   = priv->config->dev_config[0].negation_delay;
          hold  = priv->config->dev_config[0].hold_delay;
        }

      spdecr = ((setup & 0x07) << R_SPI_B_SPDECR_SCKDL_SHIFT) |
               ((neg & 0x07) << R_SPI_B_SPDECR_SLNDL_SHIFT) |
               ((hold & 0x07) << R_SPI_B_SPDECR_SPNDL_SHIFT);
      ra_spi_putreg32(priv, R_SPI_B_SPDECR_OFFSET, spdecr);

      /* SPCMD0 default: 8-bit, BRDV=1 (no div), use SSL0 and enable delays */
      spcmd0 = R_SPI_B_SPCMD_SPB_8 | R_SPI_B_SPCMD_BRDV_1 | R_SPI_B_SPCMD_SSLA_0 |
               R_SPI_B_SPCMD_SCKDEN | R_SPI_B_SPCMD_SLNDEN | R_SPI_B_SPCMD_SPNDEN;
      ra_spi_putreg32(priv, R_SPI_B_SPCMD0_OFFSET, spcmd0);
    }
  else
    {
      /* Slave mode: enable mode-fault detection */
      spcr |= R_SPI_B_SPCR_MODFEN;
    }

  /* SPCR2 default = 0 (pin control and MOSI idle/byte swap disabled) */
  ra_spi_putreg32(priv, R_SPI_B_SPCR2_OFFSET, spcr2);

  /* SPTIE must be enabled for DTC even if transmitting from RXI */
  if (priv->use_dtc || priv->txbuffer)
    {
      spcr |= R_SPI_B_SPCR_SPTIE;
    }

  /* SPRIE only for full-duplex (when both TX and RX are active) */
  if (priv->use_dtc || (priv->txbuffer && priv->rxbuffer))
    {
      spcr |= R_SPI_B_SPCR_SPRIE;
    }

  /* SPI Mode Select: 3-wire if CS is clock-synchronous */
  if (priv->config->dev_config == NULL ||
      (priv->config->num_cs > 0 && priv->config->dev_config[0].cs_type == R_SPI_B_CS_CLK_SYS))
    {
      spcr |= R_SPI_B_SPCR_SPMS;
    }

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

  /* Set default bit rate to 1MHz and mode 0 with 8 bits */
  ra_spi_setfrequency(&priv->spidev, 1000000);
  ra_spi_setmode(&priv->spidev, SPIDEV_MODE0);
  ra_spi_setbits(&priv->spidev, 8);

  /* Setup DTC if configured */
  ra_spi_dtc_setup(priv);
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
      /* Initialize hardware first, before attaching interrupts */
      ra_spi_bus_initialize(priv);

      /* Attach interrupts but immediately disable them to prevent spurious interrupts */
      ret = ra_icu_attach(priv->config->rxi_elc, ra_spi_rxi_interrupt, priv, true);
      if (ret < 0)
        {
          return NULL;
        }
      priv->rxi_irq = ret; /* Store the assigned IRQ number */
      ret = ra_icu_attach(priv->config->txi_elc, ra_spi_txi_interrupt, priv, true);
      if (ret < 0)
        {
          return NULL;
        }
      priv->txi_irq = ret; /* Store the assigned IRQ number */

      ret = ra_icu_attach(priv->config->tei_elc, ra_spi_tei_interrupt, priv, false);
      if (ret < 0)
        {
          return NULL;
        }
      priv->tei_irq = ret; /* Store the assigned IRQ number */

      ret = ra_icu_attach(priv->config->eri_elc, ra_spi_eri_interrupt, priv, true);
      if (ret < 0)
        {
          return NULL;
        }
      priv->eri_irq = ret; /* Store the assigned IRQ number */
      spiinfo("SPI%d interrupts attached: RXI=%d TXI=%d TEI=%d ERI=%d (all disabled until transfer)\n",
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

    const struct ra_spi_ext_dev_config_s *dev_config = ra_spi_get_dev_config((struct spi_dev_s *)priv, devid);

    spiinfo("SPI%d devid=0x%08lx selected=%d\n", priv->config->bus, (unsigned long)devid, selected);

    /* Store current device ID for frequency limiting */
    priv->devid = devid;

    /* Assert CS */
    if (dev_config->cs_type == R_SPI_B_CS_GPIO)
      {
        DEBUGASSERT(dev_config->cs_gpio != 0);
        ra_gpiowrite(dev_config->cs_gpio, !selected);
      }
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
  /* Default implementation returns no status */
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
  /* Default implementation does nothing */
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

/****************************************************************************
 * Name: ra_spi_get_dev_config
 *
 * Description:
 *   Board-specific function to get external device configuration for a device.
 *   This is a weak function that can be overridden by board-specific
 *   implementations to provide device-specific external device configurations.
 *
 ****************************************************************************/

const struct ra_spi_ext_dev_config_s * weak_function ra_spi_get_dev_config(struct spi_dev_s *dev, uint32_t devid)
{
  /* Default implementation returns NULL - use default settings */
  UNUSED(dev);
  UNUSED(devid);
  return NULL;
}

#ifdef CONFIG_SPI_CALLBACK
int weak_function ra_spi_register_callback(struct spi_dev_s *dev,
                                           spi_callback_t callback, void *arg)
{
  /* Default implementation does nothing */
  UNUSED(dev);
  UNUSED(callback);
  UNUSED(arg);
  return OK;
}
#endif

#endif /* CONFIG_RA_SPI */

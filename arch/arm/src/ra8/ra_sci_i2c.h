/****************************************************************************
 * arch/arm/src/ra8/ra_sci_i2c.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_SCI_I2C_H
#define __ARCH_ARM_SRC_RA8_RA_SCI_I2C_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include <nuttx/irq.h>
#include <nuttx/mutex.h>
#include <nuttx/semaphore.h>
#include <nuttx/i2c/i2c_master.h>

#ifdef CONFIG_RA_DTC
#include "ra_dtc.h"
#endif

#ifdef CONFIG_RA_DMAC
#include "ra_dmac.h"
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Configuration ************************************************************/

/* SCI I2C Rate Modes */

#define RA_SCI_I2C_RATE_STANDARD       100000   /* 100 kHz Standard mode */
#define RA_SCI_I2C_RATE_FAST           400000   /* 400 kHz Fast mode */
#define RA_SCI_I2C_RATE_FASTPLUS       1000000  /* 1 MHz Fast-mode Plus */

/* SCI I2C Timeout values */

#define RA_SCI_I2C_TIMEOUT_US          100000   /* 100ms default timeout */
#define RA_SCI_I2C_DTC_THRESHOLD       8        /* Minimum bytes for DTC */
#define RA_SCI_I2C_DMA_THRESHOLD       16       /* Minimum bytes for DMA */

/* Maximum number of SCI channels that support I2C mode */

#define RA_SCI_I2C_MAX_CHANNELS        10

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* SCI I2C Clock Source Selection */

enum ra_sci_i2c_clksrc_e
{
  RA_SCI_I2C_CLKSRC_PCLK = 0,       /* Peripheral clock (PCLKA) */
  RA_SCI_I2C_CLKSRC_SCISPICLK = 1,  /* SCI/SPI dedicated clock */
};

/* SCI I2C State Machine States */

enum ra_sci_i2cstate_e
{
  SCI_I2CSTATE_IDLE = 0,        /* No I2C activity */
  SCI_I2CSTATE_START,           /* Generating START condition */
  SCI_I2CSTATE_RESTART,         /* Generating RESTART condition */
  SCI_I2CSTATE_ADDR_SEND,       /* Sending slave address */
  SCI_I2CSTATE_ADDR_WAIT_ACK,   /* Waiting for address ACK */
  SCI_I2CSTATE_WRITE,           /* Transmitting data bytes */
  SCI_I2CSTATE_READ,            /* Receiving data bytes */
  SCI_I2CSTATE_WAIT_ACK,        /* Waiting for data ACK */
  SCI_I2CSTATE_STOP,            /* Generating STOP condition */
  SCI_I2CSTATE_ERROR,           /* Error state */
};

/* SCI I2C Clock Settings (matching FSP sci_b_i2c_clock_settings_t) */

struct ra_sci_i2c_clock_settings_s
{
  bool     bitrate_modulation;   /* MDDR enable (BRME bit) */
  uint8_t  brr_value;            /* Bit Rate Register value */
  uint8_t  clk_divisor_value;    /* Clock divider (CKS: 0-3) */
  uint8_t  mddr_value;           /* Modulation Duty Register (0x80-0xFF) */
  uint8_t  cycles_value;         /* SDA Delay Output Cycles (IICDL: 0-31) */
  uint8_t  snfr_value;           /* Noise Filter Setting (NFCS) */
  uint8_t  clock_source;         /* SCISPICLK or PCLK (BPEN bit) */
};

/* SCI I2C Device hardware configuration (const, per-channel) */

struct ra_sci_i2c_config_s
{
  uint32_t base;                 /* SCI_B base address */
  uint8_t  channel;              /* SCI channel number (0-9) */
  uint8_t  bus;                  /* I2C bus number for NuttX API */
  uint32_t rxi_elc;              /* RXI ELC event number */
  uint32_t txi_elc;              /* TXI ELC event number */
  uint32_t tei_elc;              /* TEI ELC event number */
  uint32_t eri_elc;              /* ERI ELC event number */
  uint32_t mstp;                 /* MSTP module enum (RA_MSTP_SCIn) */
};

/* SCI I2C Device Private Data (runtime state) */

struct ra_sci_i2c_priv_s
{
  /* Standard I2C operations - must be first member */

  const struct i2c_ops_s *ops;

  /* Port configuration (const) */

  const struct ra_sci_i2c_config_s *config;

  /* Reference counting and locking */

  int      refs;                 /* Reference count */
  mutex_t  lock;                 /* Mutual exclusion mutex */

#ifndef CONFIG_I2C_POLLED
  sem_t    sem_isr;              /* Interrupt wait semaphore */
#endif

  /* Initialization state */

  bool     initialized;          /* Driver initialized flag */

  /* I2C State machine */

  volatile uint8_t state;        /* Current state (ra_sci_i2cstate_e) */

  /* Current I2C transfer */

  struct i2c_msg_s *msgs;        /* Current message array */
  int      msgc;                 /* Number of messages remaining */
  int      msgidx;               /* Current message index */

  /* I2C Bus frequency */

  uint32_t frequency;            /* Current I2C frequency */
  struct ra_sci_i2c_clock_settings_s clk_settings; /* Calculated clock settings */

  /* Current message transfer state */

  uint8_t *ptr;                  /* Current message buffer pointer */
  uint32_t dcnt;                 /* Remaining byte count */
  uint16_t flags;                /* Current message flags */

  /* I2C Address handling */

  uint8_t  addr;                 /* Current 7-bit slave address */
  uint8_t  addr_10bit_high;      /* High byte for 10-bit addressing */
  uint8_t  addr_total;           /* Total address bytes to send */
  uint8_t  addr_loaded;          /* Address bytes already sent */
  bool     read_mode;            /* Current transfer direction */

  /* Interrupt numbers assigned at runtime via ICU */

  int      rxi_irq;              /* RX interrupt number */
  int      txi_irq;              /* TX interrupt number */
  int      tei_irq;              /* TE interrupt number */
  int      eri_irq;              /* ER interrupt number (optional) */

  /* Transfer status */

  uint32_t status;               /* End of transfer status */
  bool     error;                /* Error flag */
  bool     restart_pending;      /* Restart requested for next msg */
  bool     do_dummy_read;        /* Skip first RX (address ACK byte) */

#ifdef CONFIG_I2C_TRACE
  /* I2C trace support */

  int      tndx;                 /* Trace array index */
  uint32_t start_time;           /* Time when trace started */
  struct i2c_trace_s trace[CONFIG_I2C_NTRACE];
#endif

#ifdef CONFIG_RA_DTC
  /* DTC support for high-performance transfers */

  bool     use_dtc;              /* DTC enable flag */
  bool     dtc_active;           /* DTC transfer in progress */
  ra_dtc_info_t dtc_tx_info;     /* TX DTC transfer info */
  ra_dtc_info_t dtc_rx_info;     /* RX DTC transfer info */
#endif

#ifdef CONFIG_RA_DMAC
  /* DMAC support for even higher performance */

  void    *dma_tx_handle;        /* TX DMA channel handle */
  void    *dma_rx_handle;        /* RX DMA channel handle */
  int      dma_tx_channel;       /* Assigned TX DMA channel */
  int      dma_rx_channel;       /* Assigned RX DMA channel */
  bool     use_dma;              /* DMAC enable flag */
  bool     dma_active;           /* DMA transfer in progress */
#endif
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: ra_sci_i2cbus_initialize
 *
 * Description:
 *   Initialize the selected SCI I2C bus for I2C operation.
 *
 * Input Parameters:
 *   port - Port number (corresponds to SCI channel, 0-9)
 *
 * Returned Value:
 *   Valid I2C device structure reference on success; NULL on failure
 *
 ****************************************************************************/

struct i2c_master_s *ra_sci_i2cbus_initialize(int port);

/****************************************************************************
 * Name: ra_sci_i2cbus_uninitialize
 *
 * Description:
 *   De-initialize the selected SCI I2C bus.
 *
 * Input Parameters:
 *   dev - Device structure as returned by ra_sci_i2cbus_initialize()
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure
 *
 ****************************************************************************/

int ra_sci_i2cbus_uninitialize(struct i2c_master_s *dev);

/****************************************************************************
 * Name: ra_sci_i2c_setfrequency
 *
 * Description:
 *   Set the I2C bus frequency. Called internally by the driver, but may
 *   also be called externally to pre-configure frequency before transfer.
 *
 * Input Parameters:
 *   priv      - Private SCI I2C device structure
 *   frequency - I2C bus frequency in Hz (100000, 400000, or 1000000)
 *
 * Returned Value:
 *   The actual frequency set (may differ due to clock divider granularity)
 *
 ****************************************************************************/

uint32_t ra_sci_i2c_setfrequency(struct ra_sci_i2c_priv_s *priv,
                                  uint32_t frequency);

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RA8_RA_SCI_I2C_H */

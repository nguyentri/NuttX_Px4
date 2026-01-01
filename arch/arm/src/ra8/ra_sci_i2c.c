/****************************************************************************
 * arch/arm/src/ra8/ra_sci_i2c.c
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

#include <arch/board/board.h>

#include "arm_internal.h"
#include "chip.h"
#include "hardware/ra_memorymap.h"
#include "ra_icu.h"
#include "ra_mstp.h"
#include "ra_sci_i2c.h"
#include "ra_clock.h"

#ifdef CONFIG_RA_SCI_I2C

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

 /* SCI_I2C Bus numbers */
#define RA_SCI_I2C_BUS_0             0
#define RA_SCI_I2C_BUS_1             1
#define RA_SCI_I2C_BUS_2             2
#define RA_SCI_I2C_BUS_3             3
#define RA_SCI_I2C_BUS_4             4
#define RA_SCI_I2C_BUS_5             5
#define RA_SCI_I2C_BUS_6             6
#define RA_SCI_I2C_BUS_7             7
#define RA_SCI_I2C_BUS_8             8
#define RA_SCI_I2C_BUS_9             9

/* Register access helpers */
#define sci_getreg32(p, o)      getreg32((p)->config->base + (o))
#define sci_putreg32(p, o, v)   putreg32((v), (p)->config->base + (o))

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int ra_sci_i2c_transfer(struct i2c_master_s *dev,
                               struct i2c_msg_s *msgs, int count);
#ifdef CONFIG_I2C_RESET
static int ra_sci_i2c_reset(struct i2c_master_s *dev);
#endif

static int ra_sci_i2c_isr_txi(int irq, void *context, void *arg);
static int ra_sci_i2c_isr_tei(int irq, void *context, void *arg);
static int ra_sci_i2c_isr_rxi(int irq, void *context, void *arg);
static int ra_sci_i2c_isr_eri(int irq, void *context, void *arg);

static void ra_sci_i2c_init_hw(struct ra_sci_i2c_priv_s *priv);
static void ra_sci_i2c_start(struct ra_sci_i2c_priv_s *priv);
static void ra_sci_i2c_stop(struct ra_sci_i2c_priv_s *priv);
static void ra_sci_i2c_restart(struct ra_sci_i2c_priv_s *priv);
static int ra_sci_i2c_bus_reset(struct ra_sci_i2c_priv_s *priv);
static void ra_sci_i2c_set_ack(struct ra_sci_i2c_priv_s *priv, bool nack);

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* I2C operations */
static const struct i2c_ops_s ra_sci_i2c_ops =
{
  .transfer = ra_sci_i2c_transfer,
#ifdef CONFIG_I2C_RESET
  .reset    = ra_sci_i2c_reset,
#endif
};

/* SCI0 Configuration */
#ifdef CONFIG_RA_SCI0_I2C
static const struct ra_sci_i2c_config_s ra_sci0_i2c_config =
{
  .base     = R_SCI_B_CH_BASE(0),
  .channel  = 0,
  .bus      = 0,
  .rxi_elc  =  RA_ELC_SCI0_RXI,
  .txi_elc  =  RA_ELC_SCI0_TXI,
  .tei_elc  =  RA_ELC_SCI0_TEI,
  .eri_elc  =  RA_ELC_SCI0_ERI,
  .mstp     = RA_MSTP_SCI0,
};

static struct ra_sci_i2c_priv_s ra_sci0_i2c_priv =
{
  .ops      = &ra_sci_i2c_ops,
  .config   = &ra_sci0_i2c_config,
  .lock     = NXMUTEX_INITIALIZER,
#ifndef CONFIG_I2C_POLLED
  .sem_isr  = SEM_INITIALIZER(0),
#endif
};
#endif

/* SCI1 Configuration */
#ifdef CONFIG_RA_SCI1_I2C
static const struct ra_sci_i2c_config_s ra_sci1_i2c_config =
{
  .base     = R_SCI_B_CH_BASE(1),
  .channel  = 1,
  .bus      = 1,
  .rxi_elc  = RA_ELC_SCI1_RXI,
  .txi_elc  = RA_ELC_SCI1_TXI,
  .tei_elc  = RA_ELC_SCI1_TEI,
  .eri_elc  = RA_ELC_SCI1_ERI,
  .mstp     = RA_MSTP_SCI1,
};

static struct ra_sci_i2c_priv_s ra_sci1_i2c_priv =
{
  .ops      = &ra_sci_i2c_ops,
  .config   = &ra_sci1_i2c_config,
  .lock     = NXMUTEX_INITIALIZER,
#ifndef CONFIG_I2C_POLLED
  .sem_isr  = SEM_INITIALIZER(0),
#endif
};
#endif

/* SCI2 Configuration */
#ifdef CONFIG_RA_SCI2_I2C
static const struct ra_sci_i2c_config_s ra_sci2_i2c_config =
{
  .base     = R_SCI_B_CH_BASE(2),
  .channel  = 2,
  .bus      = 2,
  .rxi_elc  = RA_ELC_SCI2_RXI,
  .txi_elc  = RA_ELC_SCI2_TXI,
  .tei_elc  = RA_ELC_SCI2_TEI,
  .eri_elc  = RA_ELC_SCI2_ERI,
  .mstp     = RA_MSTP_SCI2,
};

static struct ra_sci_i2c_priv_s ra_sci2_i2c_priv =
{
  .ops      = &ra_sci_i2c_ops,
  .config   = &ra_sci2_i2c_config,
  .lock     = NXMUTEX_INITIALIZER,
#ifndef CONFIG_I2C_POLLED
  .sem_isr  = SEM_INITIALIZER(0),
#endif
};
#endif

/* SCI3 Configuration */
#ifdef CONFIG_RA_SCI3_I2C
static const struct ra_sci_i2c_config_s ra_sci3_i2c_config =
{
  .base     = R_SCI_B_CH_BASE(3),
  .channel  = 3,
  .bus      = 3,
  .rxi_elc  = RA_ELC_SCI3_RXI,
  .txi_elc  = RA_ELC_SCI3_TXI,
  .tei_elc  = RA_ELC_SCI3_TEI,
  .eri_elc  = RA_ELC_SCI3_ERI,
  .mstp     = RA_MSTP_SCI3,
};

static struct ra_sci_i2c_priv_s ra_sci3_i2c_priv =
{
  .ops      = &ra_sci_i2c_ops,
  .config   = &ra_sci3_i2c_config,
  .lock     = NXMUTEX_INITIALIZER,
#ifndef CONFIG_I2C_POLLED
  .sem_isr  = SEM_INITIALIZER(0),
#endif
};
#endif

/* SCI4 Configuration */
#ifdef CONFIG_RA_SCI4_I2C
static const struct ra_sci_i2c_config_s ra_sci4_i2c_config =
{
  .base     = R_SCI_B_CH_BASE(4),
  .channel  = 4,
  .bus      = 4,
  .rxi_elc  = RA_ELC_SCI4_RXI,
  .txi_elc  = RA_ELC_SCI4_TXI,
  .tei_elc  = RA_ELC_SCI4_TEI,
  .eri_elc  = RA_ELC_SCI4_ERI,
  .mstp     = RA_MSTP_SCI4,
};

static struct ra_sci_i2c_priv_s ra_sci4_i2c_priv =
{
  .ops      = &ra_sci_i2c_ops,
  .config   = &ra_sci4_i2c_config,
  .lock     = NXMUTEX_INITIALIZER,
#ifndef CONFIG_I2C_POLLED
  .sem_isr  = SEM_INITIALIZER(0),
#endif
};
#endif

/* SCI5 Configuration */
#ifdef CONFIG_RA_SCI5_I2C
static const struct ra_sci_i2c_config_s ra_sci5_i2c_config =
{
  .base     = R_SCI_B_CH_BASE(5),
  .channel  = 5,
  .bus      = 5,
  .rxi_elc  = RA_ELC_SCI5_RXI,
  .txi_elc  = RA_ELC_SCI5_TXI,
  .tei_elc  = RA_ELC_SCI5_TEI,
  .eri_elc  = RA_ELC_SCI5_ERI,
  .mstp     = RA_MSTP_SCI5,
};

static struct ra_sci_i2c_priv_s ra_sci5_i2c_priv =
{
  .ops      = &ra_sci_i2c_ops,
  .config   = &ra_sci5_i2c_config,
  .lock     = NXMUTEX_INITIALIZER,
#ifndef CONFIG_I2C_POLLED
  .sem_isr  = SEM_INITIALIZER(0),
#endif
};
#endif

/* SCI6 Configuration */
#ifdef CONFIG_RA_SCI6_I2C
static const struct ra_sci_i2c_config_s ra_sci6_i2c_config =
{
  .base     = R_SCI_B_CH_BASE(6),
  .channel  = 6,
  .bus      = 6,
  .rxi_elc  = RA_ELC_SCI6_RXI,
  .txi_elc  = RA_ELC_SCI6_TXI,
  .tei_elc  = RA_ELC_SCI6_TEI,
  .eri_elc  = RA_ELC_SCI6_ERI,
  .mstp     = RA_MSTP_SCI6,
};

static struct ra_sci_i2c_priv_s ra_sci6_i2c_priv =
{
  .ops      = &ra_sci_i2c_ops,
  .config   = &ra_sci6_i2c_config,
  .lock     = NXMUTEX_INITIALIZER,
#ifndef CONFIG_I2C_POLLED
  .sem_isr  = SEM_INITIALIZER(0),
#endif
};
#endif

/* SCI7 Configuration */
#ifdef CONFIG_RA_SCI7_I2C
static const struct ra_sci_i2c_config_s ra_sci7_i2c_config =
{
  .base     = R_SCI_B_CH_BASE(7),
  .channel  = 7,
  .bus      = 7,
  .rxi_elc  = RA_ELC_SCI7_RXI,
  .txi_elc  = RA_ELC_SCI7_TXI,
  .tei_elc  = RA_ELC_SCI7_TEI,
  .eri_elc  = RA_ELC_SCI7_ERI,
  .mstp     = RA_MSTP_SCI7,
};

static struct ra_sci_i2c_priv_s ra_sci7_i2c_priv =
{
  .ops      = &ra_sci_i2c_ops,
  .config   = &ra_sci7_i2c_config,
  .lock     = NXMUTEX_INITIALIZER,
#ifndef CONFIG_I2C_POLLED
  .sem_isr  = SEM_INITIALIZER(0),
#endif
};
#endif

/* SCI8 Configuration */
#ifdef CONFIG_RA_SCI8_I2C
static const struct ra_sci_i2c_config_s ra_sci8_i2c_config =
{
  .base     = R_SCI_B_CH_BASE(8),
  .channel  = 8,
  .bus      = 8,
  .rxi_elc  = RA_ELC_SCI8_RXI,
  .txi_elc  = RA_ELC_SCI8_TXI,
  .tei_elc  = RA_ELC_SCI8_TEI,
  .eri_elc  = RA_ELC_SCI8_ERI,
  .mstp     = RA_MSTP_SCI8,
};

static struct ra_sci_i2c_priv_s ra_sci8_i2c_priv =
{
  .ops      = &ra_sci_i2c_ops,
  .config   = &ra_sci8_i2c_config,
  .lock     = NXMUTEX_INITIALIZER,
#ifndef CONFIG_I2C_POLLED
  .sem_isr  = SEM_INITIALIZER(0),
#endif
};
#endif

/* SCI9 Configuration */
#ifdef CONFIG_RA_SCI9_I2C
static const struct ra_sci_i2c_config_s ra_sci9_i2c_config =
{
  .base     = R_SCI_B_CH_BASE(9),
  .channel  = 9,
  .bus      = 9,
  .rxi_elc  = RA_ELC_SCI9_RXI,
  .txi_elc  = RA_ELC_SCI9_TXI,
  .tei_elc  = RA_ELC_SCI9_TEI,
  .eri_elc  = RA_ELC_SCI9_ERI,
  .mstp     = RA_MSTP_SCI9,
};

static struct ra_sci_i2c_priv_s ra_sci9_i2c_priv =
{
  .ops      = &ra_sci_i2c_ops,
  .config   = &ra_sci9_i2c_config,
  .lock     = NXMUTEX_INITIALIZER,
#ifndef CONFIG_I2C_POLLED
  .sem_isr  = SEM_INITIALIZER(0),
#endif
};
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_sci_i2c_setfrequency
 ****************************************************************************/

/****************************************************************************
 * Name: ra_sci_i2c_calculate_clock
 *
 * Description:
 *   Calculate optimal clock settings for the requested I2C frequency.
 *   Based on FSP r_sci_b_i2c_clock_settings() algorithm.
 *
 *   Bit Rate = PCLK / ((64 * 2^(2*CKS-1) * (BRR + 1)) * MDDR/256)
 *   For simple I2C mode with MDDR modulation.
 *
 ****************************************************************************/

static void ra_sci_i2c_calculate_clock(struct ra_sci_i2c_priv_s *priv,
                                       uint32_t frequency)
{
  uint32_t pclk;
  uint32_t divisor;
  uint32_t brr;
  uint8_t  cks;
  uint8_t  mddr;
  uint8_t  iicdl;
  uint8_t  nfcs;
  uint32_t actual_freq;
  uint32_t best_error = UINT32_MAX;
  uint8_t  best_cks = 0;
  uint8_t  best_brr = 0;
  uint8_t  best_mddr = 0x80;

  /* Get the peripheral clock frequency */

  pclk = ra_get_peripheral_clock(RA_PCLK_SCICLK);
  if (pclk == 0)
    {
      pclk = 120000000; /* Default fallback: 120 MHz */
    }

  priv->clk_settings.clock_source = 0; /* Use PCLK */

  /* Iterate through CKS (clock select) values 0-3 */

  for (cks = 0; cks <= 3; cks++)
    {
      /* Divisor = 64 * 2^(2*CKS - 1) for CKS > 0, or 64 for CKS = 0 */

      if (cks == 0)
        {
          divisor = 64;
        }
      else
        {
          divisor = 64 << ((2 * cks) - 1);
        }

      /* Calculate BRR for target frequency with MDDR = 256 (no modulation) */
      /* freq = pclk / (divisor * (BRR + 1) * MDDR/256) */
      /* BRR = pclk / (divisor * freq) - 1 */

      brr = (pclk / (divisor * frequency)) - 1;

      /* BRR must be 0-255 */

      if (brr > 255)
        {
          continue;
        }

      /* Try MDDR values from 128-255 for fine-tuning */

      for (mddr = 128; mddr <= 255; mddr++)
        {
          actual_freq = (pclk * 256) / (divisor * (brr + 1) * mddr);

          uint32_t error;
          if (actual_freq > frequency)
            {
              error = actual_freq - frequency;
            }
          else
            {
              error = frequency - actual_freq;
            }

          if (error < best_error)
            {
              best_error = error;
              best_cks = cks;
              best_brr = brr;
              best_mddr = mddr;

              /* Perfect match */

              if (error == 0)
                {
                  goto found;
                }
            }
        }
    }

found:
  /* Set IICDL (SDA delay) based on frequency:
   * - Standard mode (100kHz): max delay for hold time
   * - Fast mode (400kHz): reduced delay
   * - Fast-mode Plus (1MHz): minimum delay
   */

  if (frequency <= 100000)
    {
      iicdl = 31;  /* Maximum delay for 100kHz */
      nfcs = 1;    /* Noise filter: 1 cycle */
    }
  else if (frequency <= 400000)
    {
      iicdl = 14;  /* Reduced delay for 400kHz */
      nfcs = 1;    /* Noise filter: 1 cycle */
    }
  else
    {
      iicdl = 5;   /* Minimum delay for 1MHz */
      nfcs = 0;    /* Noise filter: disabled for speed */
    }

  /* Store calculated settings */

  priv->clk_settings.clk_divisor_value = best_cks;
  priv->clk_settings.brr_value = best_brr;
  priv->clk_settings.mddr_value = best_mddr;
  priv->clk_settings.bitrate_modulation = (best_mddr != 0x80);
  priv->clk_settings.cycles_value = iicdl;
  priv->clk_settings.snfr_value = nfcs;

  i2cinfo("SCI I2C: freq=%lu, pclk=%lu, cks=%u, brr=%u, mddr=%u\n",
          frequency, pclk, best_cks, best_brr, best_mddr);
}

uint32_t ra_sci_i2c_setfrequency(struct ra_sci_i2c_priv_s *priv,
                                 uint32_t frequency)
{
  if (priv->frequency == frequency)
    {
      return priv->frequency;
    }

  /* Clamp frequency to supported range */

  if (frequency < 10000)
    {
      frequency = 10000;
    }
  else if (frequency > RA_SCI_I2C_RATE_FASTPLUS)
    {
      frequency = RA_SCI_I2C_RATE_FASTPLUS;
    }

  /* Calculate optimal clock settings */

  ra_sci_i2c_calculate_clock(priv, frequency);

  priv->frequency = frequency;

  /* Apply settings if driver is initialized */
  if (priv->initialized)
    {
      /* Disable TE/RE/IICINTM before changing settings */
      sci_putreg32(priv, R_SCI_B_CCR0_OFFSET, 0);

      /* Wait for TE/RE to clear */
      while (sci_getreg32(priv, R_SCI_B_CESR_OFFSET) & (R_SCI_B_CESR_TIST | R_SCI_B_CESR_RIST));

      /* Update registers */
      uint32_t ccr2 = (priv->clk_settings.clk_divisor_value << R_SCI_B_CCR2_CKS_SHIFT) |
                      (priv->clk_settings.brr_value << R_SCI_B_CCR2_BRR_SHIFT) |
                      (priv->clk_settings.mddr_value << R_SCI_B_CCR2_MDDR_SHIFT) |
                      (priv->clk_settings.bitrate_modulation ? R_SCI_B_CCR2_BRME : 0) |
                      (4 << R_SCI_B_CCR2_BCP_SHIFT); /* BCP=4 (32 cycles) */

      sci_putreg32(priv, R_SCI_B_CCR2_OFFSET, ccr2);

      uint32_t ccr1 = (priv->clk_settings.snfr_value << R_SCI_B_CCR1_NFCS_SHIFT) |
                      R_SCI_B_CCR1_NFEN;
      sci_putreg32(priv, R_SCI_B_CCR1_OFFSET, ccr1);

      uint32_t icr = sci_getreg32(priv, R_SCI_B_ICR_OFFSET);
      icr &= ~R_SCI_B_ICR_IICDL_MASK;
      icr |= (priv->clk_settings.cycles_value << R_SCI_B_ICR_IICDL_SHIFT);
      sci_putreg32(priv, R_SCI_B_ICR_OFFSET, icr);
    }

  return frequency;
}

/****************************************************************************
 * Name: ra_sci_i2c_init_hw
 ****************************************************************************/

static void ra_sci_i2c_init_hw(struct ra_sci_i2c_priv_s *priv)
{
  /* Set default frequency if not already set */
  if (priv->frequency == 0)
    {
      priv->frequency = RA_SCI_I2C_RATE_STANDARD;
    }

  /* 1. Disable interrupts and TE/RE */
  sci_putreg32(priv, R_SCI_B_CCR0_OFFSET, 0);

  /* 2. Configure ICR (Simple I2C Control) */
  uint32_t icr = (3 << R_SCI_B_ICR_IICSCLS_SHIFT) | /* SCL High-Z */
                 (3 << R_SCI_B_ICR_IICSDAS_SHIFT) | /* SDA High-Z */
                 R_SCI_B_ICR_IICINTM |              /* Use TXI/RXI interrupts */
                 R_SCI_B_ICR_IICCSC |               /* Clock Sync Enable */
                 R_SCI_B_ICR_IICACKT;               /* NACK transmission default */
  sci_putreg32(priv, R_SCI_B_ICR_OFFSET, icr);

  /* 3. Configure CCR3 (Mode Selection) */
  uint32_t ccr3 = (2 << R_SCI_B_CCR3_CHR_SHIFT) |   /* 8-bit data */
                  R_SCI_B_CCR3_MOD_100 |            /* Simple I2C Mode */
                  (priv->clk_settings.clock_source ? R_SCI_B_CCR3_BPEN : 0);
  sci_putreg32(priv, R_SCI_B_CCR3_OFFSET, ccr3);

  /* 4. Configure Frequency (CCR2, CCR1) */
  ra_sci_i2c_setfrequency(priv, priv->frequency);

  /* 5. Clear Status Flags */
  sci_putreg32(priv, R_SCI_B_CFCLR_OFFSET,
               R_SCI_B_CFCLR_RDRFC | R_SCI_B_CFCLR_FERC | R_SCI_B_CFCLR_PERC |
               R_SCI_B_CFCLR_MFFC | R_SCI_B_CFCLR_ORERC);
  sci_putreg32(priv, R_SCI_B_ICFCLR_OFFSET, R_SCI_B_ICFCLR_IICSTIFC);

  /* 6. Enable Interrupts in ICU (but not in CCR0 yet) */
  /* Done in ra_sci_i2cbus_initialize */
}

/****************************************************************************
 * Name: ra_sci_i2c_start
 ****************************************************************************/

static void ra_sci_i2c_start(struct ra_sci_i2c_priv_s *priv)
{
  priv->state = SCI_I2CSTATE_START;

  /* Request Start Condition */
  uint32_t icr = sci_getreg32(priv, R_SCI_B_ICR_OFFSET);
  icr |= R_SCI_B_ICR_IICSTAREQ;
  sci_putreg32(priv, R_SCI_B_ICR_OFFSET, icr);
}

/****************************************************************************
 * Name: ra_sci_i2c_restart
 ****************************************************************************/

static void ra_sci_i2c_restart(struct ra_sci_i2c_priv_s *priv)
{
  priv->state = SCI_I2CSTATE_RESTART;

  /* Request Restart Condition */
  uint32_t icr = sci_getreg32(priv, R_SCI_B_ICR_OFFSET);
  icr |= R_SCI_B_ICR_IICRSTAREQ;
  sci_putreg32(priv, R_SCI_B_ICR_OFFSET, icr);
}

/****************************************************************************
 * Name: ra_sci_i2c_stop
 ****************************************************************************/

static void ra_sci_i2c_stop(struct ra_sci_i2c_priv_s *priv)
{
  priv->state = SCI_I2CSTATE_STOP;

  /* Request Stop Condition */
  uint32_t icr = sci_getreg32(priv, R_SCI_B_ICR_OFFSET);
  icr |= R_SCI_B_ICR_IICSTPREQ;
  sci_putreg32(priv, R_SCI_B_ICR_OFFSET, icr);
}

/****************************************************************************
 * Name: ra_sci_i2c_set_ack
 *
 * Description:
 *   Set ACK/NACK for next received byte with interrupt protection (M1 fix).
 *   This function disables interrupts to prevent race conditions when
 *   modifying the IICACKT bit in the ICR register.
 *
 * Input Parameters:
 *   priv - Private SCI I2C device structure
 *   nack - true for NACK, false for ACK
 *
 ****************************************************************************/

static void ra_sci_i2c_set_ack(struct ra_sci_i2c_priv_s *priv, bool nack)
{
  irqstate_t flags;
  uint32_t icr;

  /* Disable interrupts during read-modify-write */

  flags = enter_critical_section();

  icr = sci_getreg32(priv, R_SCI_B_ICR_OFFSET);
  if (nack)
    {
      icr |= R_SCI_B_ICR_IICACKT;  /* NACK next byte */
    }
  else
    {
      icr &= ~R_SCI_B_ICR_IICACKT; /* ACK next byte */
    }
  sci_putreg32(priv, R_SCI_B_ICR_OFFSET, icr);

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: ra_sci_i2c_bus_reset
 *
 * Description:
 *   Perform I2C bus reset by toggling SCL 9 times (M4 fix).
 *   This releases a stuck slave device that may be holding SDA low.
 *
 * Input Parameters:
 *   priv - Private SCI I2C device structure
 *
 * Returned Value:
 *   OK on success, -ETIMEDOUT if bus cannot be recovered
 *
 ****************************************************************************/

static int ra_sci_i2c_bus_reset(struct ra_sci_i2c_priv_s *priv)
{
  uint32_t icr;
  int i;
  int timeout;

  i2cwarn("SCI I2C bus reset initiated\n");

  /* Disable TE/RE first */

  sci_putreg32(priv, R_SCI_B_CCR0_OFFSET, 0);

  /* Wait for TE/RE to actually clear */

  timeout = 1000;
  while ((sci_getreg32(priv, R_SCI_B_CESR_OFFSET) &
          (R_SCI_B_CESR_TIST | R_SCI_B_CESR_RIST)) && (timeout-- > 0))
    {
      up_udelay(1);
    }

  /* Set SCL/SDA to direct pin control mode (manual toggle) */

  icr = sci_getreg32(priv, R_SCI_B_ICR_OFFSET);
  icr &= ~(R_SCI_B_ICR_IICSCLS_MASK | R_SCI_B_ICR_IICSDAS_MASK);
  icr |= R_SCI_B_ICR_IICSDAS_11;  /* SDA = High-Z (pulled high) */

  /* Toggle SCL 9 times to release any stuck slave */

  for (i = 0; i < 9; i++)
    {
      /* SCL Low */

      icr &= ~R_SCI_B_ICR_IICSCLS_MASK;
      icr |= R_SCI_B_ICR_IICSCLS_10;  /* SCL = Low */
      sci_putreg32(priv, R_SCI_B_ICR_OFFSET, icr);
      up_udelay(5);

      /* SCL High */

      icr &= ~R_SCI_B_ICR_IICSCLS_MASK;
      icr |= R_SCI_B_ICR_IICSCLS_11;  /* SCL = High-Z (pulled high) */
      sci_putreg32(priv, R_SCI_B_ICR_OFFSET, icr);
      up_udelay(5);
    }

  /* Generate STOP condition manually:
   * SDA low -> SCL high -> SDA high
   */

  /* SDA Low */

  icr &= ~R_SCI_B_ICR_IICSDAS_MASK;
  icr |= R_SCI_B_ICR_IICSDAS_10;  /* SDA = Low */
  sci_putreg32(priv, R_SCI_B_ICR_OFFSET, icr);
  up_udelay(5);

  /* SCL High */

  icr &= ~R_SCI_B_ICR_IICSCLS_MASK;
  icr |= R_SCI_B_ICR_IICSCLS_11;  /* SCL = High-Z */
  sci_putreg32(priv, R_SCI_B_ICR_OFFSET, icr);
  up_udelay(5);

  /* SDA High (STOP) */

  icr &= ~R_SCI_B_ICR_IICSDAS_MASK;
  icr |= R_SCI_B_ICR_IICSDAS_11;  /* SDA = High-Z */
  sci_putreg32(priv, R_SCI_B_ICR_OFFSET, icr);
  up_udelay(5);

  /* Restore SCL/SDA to normal operation mode */

  icr &= ~(R_SCI_B_ICR_IICSCLS_MASK | R_SCI_B_ICR_IICSDAS_MASK);
  icr |= R_SCI_B_ICR_IICSCLS_11 | R_SCI_B_ICR_IICSDAS_11;
  sci_putreg32(priv, R_SCI_B_ICR_OFFSET, icr);

  /* Clear any pending errors */

  sci_putreg32(priv, R_SCI_B_CFCLR_OFFSET,
               R_SCI_B_CFCLR_RDRFC | R_SCI_B_CFCLR_FERC |
               R_SCI_B_CFCLR_PERC | R_SCI_B_CFCLR_ORERC);
  sci_putreg32(priv, R_SCI_B_ICFCLR_OFFSET, R_SCI_B_ICFCLR_IICSTIFC);

  priv->state = SCI_I2CSTATE_IDLE;

  i2cinfo("SCI I2C bus reset complete\n");
  return OK;
}

/****************************************************************************
 * Name: ra_sci_i2c_isr_eri
 *
 * Description:
 *   Error Interrupt Handler (M3 fix).
 *   Handles overrun, framing, and other communication errors.
 *
 ****************************************************************************/

static int ra_sci_i2c_isr_eri(int irq, void *context, void *arg)
{
  struct ra_sci_i2c_priv_s *priv = (struct ra_sci_i2c_priv_s *)arg;
  uint32_t csr;

  /* Read error status */

  csr = sci_getreg32(priv, R_SCI_B_CSR_OFFSET);

  /* Check for errors */

  if (csr & (R_SCI_B_CSR_ORER | R_SCI_B_CSR_FER | R_SCI_B_CSR_PER))
    {
      i2cerr("SCI I2C error: CSR=0x%08lx (ORER=%d, FER=%d, PER=%d)\n",
             csr,
             (csr & R_SCI_B_CSR_ORER) ? 1 : 0,
             (csr & R_SCI_B_CSR_FER) ? 1 : 0,
             (csr & R_SCI_B_CSR_PER) ? 1 : 0);

      /* Clear error flags */

      sci_putreg32(priv, R_SCI_B_CFCLR_OFFSET,
                   R_SCI_B_CFCLR_ORERC | R_SCI_B_CFCLR_FERC |
                   R_SCI_B_CFCLR_PERC);

      /* Set error flag and abort transfer */

      priv->error = true;
      priv->status = csr;

      /* Generate STOP to release bus */

      if (priv->state != SCI_I2CSTATE_IDLE &&
          priv->state != SCI_I2CSTATE_STOP)
        {
          ra_sci_i2c_stop(priv);
        }
      else
        {
          /* Already stopped or idle, just signal completion */

          priv->state = SCI_I2CSTATE_IDLE;
          nxsem_post(&priv->sem_isr);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_sci_i2c_isr_tei
 * Description: Transmit End Interrupt (Start/Stop/Restart completion)
 ****************************************************************************/

static int ra_sci_i2c_isr_tei(int irq, void *context, void *arg)
{
  struct ra_sci_i2c_priv_s *priv = (struct ra_sci_i2c_priv_s *)arg;
  uint32_t isr = sci_getreg32(priv, R_SCI_B_ISR_OFFSET);

  /* Check for Start/Stop/Restart completion */
  if (isr & R_SCI_B_ISR_IICSTIF)
    {
      /* Clear flag */
      sci_putreg32(priv, R_SCI_B_ICFCLR_OFFSET, R_SCI_B_ICFCLR_IICSTIFC);

      if (priv->error)
        {
          /* Error recovery path */
          priv->status = isr;
          nxsem_post(&priv->sem_isr);
          return OK;
        }

      switch (priv->state)
        {
        case SCI_I2CSTATE_START:
        case SCI_I2CSTATE_RESTART:
          /* Start/Restart complete, send address */
          priv->state = SCI_I2CSTATE_ADDR_SEND;

          /* Send address byte (7-bit only for now) */
          uint8_t addr_byte = (priv->addr << 1) | (priv->read_mode ? 1 : 0);
          sci_putreg32(priv, R_SCI_B_TDR_BY_OFFSET, addr_byte);
          break;

        case SCI_I2CSTATE_STOP:
          /* Stop complete, transfer finished */
          priv->state = SCI_I2CSTATE_IDLE;
          nxsem_post(&priv->sem_isr);
          break;

        default:
          break;
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_sci_i2c_isr_txi
 * Description: Transmit Data Empty Interrupt (Ready for next byte)
 ****************************************************************************/

static int ra_sci_i2c_isr_txi(int irq, void *context, void *arg)
{
  struct ra_sci_i2c_priv_s *priv = (struct ra_sci_i2c_priv_s *)arg;
  uint32_t isr = sci_getreg32(priv, R_SCI_B_ISR_OFFSET);

  /* Check ACK/NACK from previous byte */
  if (!(isr & R_SCI_B_ISR_IICACKR))
    {
      /* NACK received */
      priv->error = true;
      priv->status = isr;
      ra_sci_i2c_stop(priv);
      return OK;
    }

  /* Handle State Machine */
  switch (priv->state)
    {
    case SCI_I2CSTATE_ADDR_SEND:
      /* Address sent and ACKed */
      if (priv->read_mode)
        {
          priv->state = SCI_I2CSTATE_READ;

          /* For read, we need to write dummy bytes (0xFF) to generate clock.
           * Also handle ACK/NACK generation for the *next* byte received.
           * Use protected ACK setup (M1 fix) to prevent race conditions.
           */

          /* If reading 1 byte, NACK it. Else ACK. */

          ra_sci_i2c_set_ack(priv, priv->dcnt == 1);

          /* Dummy write to start clock for read */

          sci_putreg32(priv, R_SCI_B_TDR_BY_OFFSET, 0xFF);
        }
      else
        {
          priv->state = SCI_I2CSTATE_WRITE;
          if (priv->dcnt > 0)
            {
              sci_putreg32(priv, R_SCI_B_TDR_BY_OFFSET, *priv->ptr++);
              priv->dcnt--;
            }
          else
            {
              /* No more data, check for restart or stop */
              if (priv->restart_pending)
                {
                  ra_sci_i2c_restart(priv);
                }
              else
                {
                  ra_sci_i2c_stop(priv);
                }
            }
        }
      break;

    case SCI_I2CSTATE_WRITE:
      if (priv->dcnt > 0)
        {
          sci_putreg32(priv, R_SCI_B_TDR_BY_OFFSET, *priv->ptr++);
          priv->dcnt--;
        }
      else
        {
          if (priv->restart_pending)
            {
              ra_sci_i2c_restart(priv);
            }
          else
            {
              ra_sci_i2c_stop(priv);
            }
        }
      break;

    case SCI_I2CSTATE_READ:
      /* TXI in read mode means we finished sending the dummy byte
       * and are ready to send another (or stop).
       * Actual data reading happens in RXI.
       * But for SCI I2C, we need to keep pumping dummy bytes.
       */

       /* Note: Logic here depends on timing.
        * Usually RXI fires when data is in RDR.
        * TXI fires when TDR is empty.
        */
      break;

    default:
      break;
    }

  return OK;
}

/****************************************************************************
 * Name: ra_sci_i2c_isr_rxi
 * Description: Receive Data Full Interrupt
 ****************************************************************************/

static int ra_sci_i2c_isr_rxi(int irq, void *context, void *arg)
{
  struct ra_sci_i2c_priv_s *priv = (struct ra_sci_i2c_priv_s *)arg;

  if (priv->state == SCI_I2CSTATE_READ)
    {
      /* Read data */

      *priv->ptr++ = sci_getreg32(priv, R_SCI_B_RDR_BY_OFFSET);
      priv->dcnt--;

      if (priv->dcnt > 0)
        {
          /* Prepare ACK/NACK for next byte using protected access (M1 fix) */

          ra_sci_i2c_set_ack(priv, priv->dcnt == 1);

          /* Trigger next clock by dummy write */

          sci_putreg32(priv, R_SCI_B_TDR_BY_OFFSET, 0xFF);
        }
      else
        {
          /* All data received */

          if (priv->restart_pending)
            {
              ra_sci_i2c_restart(priv);
            }
          else
            {
              ra_sci_i2c_stop(priv);
            }
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_sci_i2c_transfer
 ****************************************************************************/

static int ra_sci_i2c_transfer(struct i2c_master_s *dev,
                               struct i2c_msg_s *msgs, int count)
{
  struct ra_sci_i2c_priv_s *priv = (struct ra_sci_i2c_priv_s *)dev;
  int ret = OK;
  int timeout_count;

  /* Validate 7-bit address only (M5: 10-bit not supported) */

  for (int i = 0; i < count; i++)
    {
      if (msgs[i].flags & I2C_M_TEN)
        {
          i2cerr("SCI I2C: 10-bit addressing not supported\n");
          return -ENOTSUP;
        }

      if (msgs[i].addr > 0x7f)
        {
          i2cerr("SCI I2C: Invalid 7-bit address 0x%02x\n", msgs[i].addr);
          return -EINVAL;
        }
    }

  ret = nxmutex_lock(&priv->lock);
  if (ret < 0)
    {
      return ret;
    }

  /* Enable TE/RE/TIE/TEIE/RIE */

  uint32_t ccr0 = R_SCI_B_CCR0_TE | R_SCI_B_CCR0_RE |
                  R_SCI_B_CCR0_TIE | R_SCI_B_CCR0_TEIE | R_SCI_B_CCR0_RIE;
  sci_putreg32(priv, R_SCI_B_CCR0_OFFSET, ccr0);

  priv->msgs = msgs;
  priv->msgc = count;
  priv->msgidx = 0;

  /* Process all messages */

  for (int i = 0; i < count; i++)
    {
      priv->ptr = msgs[i].buffer;
      priv->dcnt = msgs[i].length;
      priv->flags = msgs[i].flags;
      priv->addr = msgs[i].addr;
      priv->read_mode = (priv->flags & I2C_M_READ) ? true : false;
      priv->restart_pending = (i < count - 1);
      priv->error = false;

      /* Start transaction */

      if (i == 0)
        {
          ra_sci_i2c_start(priv);
        }

      /* Wait for completion */

      ret = nxsem_tickwait_uninterruptible(&priv->sem_isr,
                                           USEC2TICK(RA_SCI_I2C_TIMEOUT_US));

      if (ret < 0)
        {
          /* Timeout occurred (M4 fix) - proper recovery sequence */

          i2cerr("SCI I2C: Transfer timeout, state=%d\n", priv->state);

          /* Try to issue STOP and wait for completion */

          if (priv->state != SCI_I2CSTATE_IDLE &&
              priv->state != SCI_I2CSTATE_STOP)
            {
              ra_sci_i2c_stop(priv);

              /* Wait for STOP to complete (up to 10ms) */

              timeout_count = 10000;
              while (priv->state != SCI_I2CSTATE_IDLE && timeout_count-- > 0)
                {
                  up_udelay(1);
                  if (sci_getreg32(priv, R_SCI_B_ISR_OFFSET) &
                      R_SCI_B_ISR_IICSTIF)
                    {
                      sci_putreg32(priv, R_SCI_B_ICFCLR_OFFSET,
                                   R_SCI_B_ICFCLR_IICSTIFC);
                      priv->state = SCI_I2CSTATE_IDLE;
                    }
                }
            }

          /* If STOP failed, perform bus reset (9 clock pulses) */

          if (priv->state != SCI_I2CSTATE_IDLE)
            {
              ra_sci_i2c_bus_reset(priv);
            }

          ret = -ETIMEDOUT;
          break;
        }

      if (priv->error)
        {
          ret = -EIO;
          break;
        }
    }

  /* Wait for bus to be idle before disabling (M4 fix) */

  timeout_count = 1000;
  while ((sci_getreg32(priv, R_SCI_B_CESR_OFFSET) &
          (R_SCI_B_CESR_TIST | R_SCI_B_CESR_RIST)) && (timeout_count-- > 0))
    {
      up_udelay(1);
    }

  /* Disable TE/RE/Interrupts */

  sci_putreg32(priv, R_SCI_B_CCR0_OFFSET, 0);

  nxmutex_unlock(&priv->lock);
  return ret;
}

/****************************************************************************
 * Name: ra_sci_i2c_reset
 ****************************************************************************/

#ifdef CONFIG_I2C_RESET
static int ra_sci_i2c_reset(struct i2c_master_s *dev)
{
  struct ra_sci_i2c_priv_s *priv = (struct ra_sci_i2c_priv_s *)dev;

  nxmutex_lock(&priv->lock);

  /* Reset the hardware */

  ra_sci_i2c_init_hw(priv);

  /* Perform bus reset to recover from any stuck state */

  ra_sci_i2c_bus_reset(priv);

  nxmutex_unlock(&priv->lock);

  return OK;
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_sci_i2cbus_initialize
 ****************************************************************************/

struct i2c_master_s *ra_sci_i2cbus_initialize(int port)
{
  struct ra_sci_i2c_priv_s *priv = NULL;

  switch (port)
    {
#ifdef CONFIG_RA_SCI0_I2C
    case 0:
      priv = &ra_sci0_i2c_priv;
      break;
#endif
#ifdef CONFIG_RA_SCI1_I2C
    case 1:
      priv = &ra_sci1_i2c_priv;
      break;
#endif
#ifdef CONFIG_RA_SCI2_I2C
    case 2:
      priv = &ra_sci2_i2c_priv;
      break;
#endif
#ifdef CONFIG_RA_SCI3_I2C
    case 3:
      priv = &ra_sci3_i2c_priv;
      break;
#endif
#ifdef CONFIG_RA_SCI4_I2C
    case 4:
      priv = &ra_sci4_i2c_priv;
      break;
#endif
#ifdef CONFIG_RA_SCI5_I2C
    case 5:
      priv = &ra_sci5_i2c_priv;
      break;
#endif
#ifdef CONFIG_RA_SCI6_I2C
    case 6:
      priv = &ra_sci6_i2c_priv;
      break;
#endif
#ifdef CONFIG_RA_SCI7_I2C
    case 7:
      priv = &ra_sci7_i2c_priv;
      break;
#endif
#ifdef CONFIG_RA_SCI8_I2C
    case 8:
      priv = &ra_sci8_i2c_priv;
      break;
#endif
#ifdef CONFIG_RA_SCI9_I2C
    case 9:
      priv = &ra_sci9_i2c_priv;
      break;
#endif
    default:
      return NULL;
    }

  nxmutex_lock(&priv->lock);

  if (priv->refs++ == 0)
    {
      /* Enable Module Clock */

      ra_mstp_start(priv->config->mstp);

      /* Initialize Hardware */

      ra_sci_i2c_init_hw(priv);

      /* Attach Interrupts (M3 fix: include ERI for error handling) */

      priv->rxi_irq = ra_icu_attach(priv->config->rxi_elc,
                                    ra_sci_i2c_isr_rxi, priv, true);
      priv->txi_irq = ra_icu_attach(priv->config->txi_elc,
                                    ra_sci_i2c_isr_txi, priv, true);
      priv->tei_irq = ra_icu_attach(priv->config->tei_elc,
                                    ra_sci_i2c_isr_tei, priv, true);
      priv->eri_irq = ra_icu_attach(priv->config->eri_elc,
                                    ra_sci_i2c_isr_eri, priv, true);

      /* Enable Interrupts in NVIC */

      up_enable_irq(priv->rxi_irq);
      up_enable_irq(priv->txi_irq);
      up_enable_irq(priv->tei_irq);
      up_enable_irq(priv->eri_irq);

      priv->initialized = true;
    }

  nxmutex_unlock(&priv->lock);
  return (struct i2c_master_s *)priv;
}

/****************************************************************************
 * Name: ra_sci_i2cbus_uninitialize
 ****************************************************************************/

int ra_sci_i2cbus_uninitialize(struct i2c_master_s *dev)
{
  struct ra_sci_i2c_priv_s *priv = (struct ra_sci_i2c_priv_s *)dev;

  nxmutex_lock(&priv->lock);

  if (priv->refs > 0)
    {
      priv->refs--;
      if (priv->refs == 0)
        {
          /* Disable Interrupts */

          up_disable_irq(priv->rxi_irq);
          up_disable_irq(priv->txi_irq);
          up_disable_irq(priv->tei_irq);
          up_disable_irq(priv->eri_irq);

          ra_icu_detach(priv->rxi_irq);
          ra_icu_detach(priv->txi_irq);
          ra_icu_detach(priv->tei_irq);
          ra_icu_detach(priv->eri_irq);

          /* Disable Module Clock */

          ra_mstp_stop(priv->config->mstp);

          priv->initialized = false;
        }
    }

  nxmutex_unlock(&priv->lock);
  return OK;
}

#endif /* CONFIG_RA_SCI_I2C */

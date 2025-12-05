/****************************************************************************
 * arch/arm/src/ra8/ra_adc_b.c
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
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <arch/board/board.h>
#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/kmalloc.h>
#include <nuttx/analog/adc.h>
#include <nuttx/analog/ioctl.h>

#include "arm_internal.h"
#include "chip.h"
#include "hardware/ra_memorymap.h"
#include "hardware/ra8p1/ra_adc_b.h"
#include "ra_mstp.h"
#include "ra_icu.h"
#include "ra_adc_b.h"

#ifdef CONFIG_RA_ADC_B

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ADC-B configuration constants */

#define ADC_B_MAX_CHANNELS       33       /* Maximum virtual channels */
#define ADC_B_MAX_SCAN_GROUPS    9        /* Scan groups 0-8 */
#define ADC_B_FIFO_DEPTH         16       /* FIFO depth per scan group */

/* Timeout values */

#define ADC_B_CLOCK_TIMEOUT_US   1000     /* Clock stabilization timeout */
#define ADC_B_CAL_TIMEOUT_US     100000   /* Calibration timeout (100ms) */

/* Default sampling time (in ADCLK cycles) */

#define ADC_B_DEFAULT_SAMPLING   24       /* Minimum 24 cycles for 16-bit */

/* Default conversion time (in ADCLK cycles) */

#define ADC_B_DEFAULT_CONVERSION 18       /* Minimum 18 cycles */

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* ADC-B private data structure */

struct ra_adc_b_priv_s
{
  const struct adc_callback_s *cb;    /* Upper half callback */
  sem_t sem_excl;                     /* Mutual exclusion semaphore */
  int irq;                            /* Dynamically assigned IRQ number */
  uint8_t nchannels;                  /* Number of configured channels */
  uint8_t current;                    /* Current channel being processed */
  uint8_t chanlist[ADC_B_MAX_CHANNELS]; /* List of enabled channels */
  uint8_t resolution;                 /* ADC resolution setting */
  uint8_t scan_mode;                  /* Scan mode (single/continuous) */
  bool calibrated;                    /* Calibration complete flag */
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Register access functions */

static inline void adc_b_putreg(uint32_t offset, uint32_t value);
static inline uint32_t adc_b_getreg(uint32_t offset);
static inline void adc_b_modifyreg(uint32_t offset, uint32_t clearbits,
                                   uint32_t setbits);

/* ADC lower-half operations */

static int  adc_b_bind(FAR struct adc_dev_s *dev,
                       FAR const struct adc_callback_s *callback);
static void adc_b_reset(FAR struct adc_dev_s *dev);
static int  adc_b_setup(FAR struct adc_dev_s *dev);
static void adc_b_shutdown(FAR struct adc_dev_s *dev);
static void adc_b_rxint(FAR struct adc_dev_s *dev, bool enable);
static int  adc_b_ioctl(FAR struct adc_dev_s *dev, int cmd,
                        unsigned long arg);

/* Internal functions */

static int  adc_b_clock_enable(void);
static int  adc_b_calibrate(void);
static void adc_b_configure_channel(uint8_t vchannel, uint8_t pchannel,
                                    uint8_t scan_group);
static int  adc_b_start_conversion(FAR struct ra_adc_b_priv_s *priv);
static int  adc_b_interrupt(int irq, FAR void *context, FAR void *arg);

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* ADC lower-half operations */

static const struct adc_ops_s g_adc_b_ops =
{
  .ao_bind     = adc_b_bind,
  .ao_reset    = adc_b_reset,
  .ao_setup    = adc_b_setup,
  .ao_shutdown = adc_b_shutdown,
  .ao_rxint    = adc_b_rxint,
  .ao_ioctl    = adc_b_ioctl,
};

/* ADC-B private data */

static struct ra_adc_b_priv_s g_adc_b_priv =
{
  .cb          = NULL,
  .irq         = -1,
  .nchannels   = 0,
  .current     = 0,
  .resolution  = RA_ADC_RESOLUTION_12BIT,
  .scan_mode   = RA_ADC_MODE_SINGLE_SCAN,
  .calibrated  = false,
};

/* ADC-B device structure */

static struct adc_dev_s g_adc_b_dev =
{
  .ad_ops  = &g_adc_b_ops,
  .ad_priv = &g_adc_b_priv,
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: adc_b_putreg
 *
 * Description:
 *   Write a value to an ADC-B register
 *
 ****************************************************************************/

static inline void adc_b_putreg(uint32_t offset, uint32_t value)
{
  putreg32(value, R_ADC_B_BASE + offset);
}

/****************************************************************************
 * Name: adc_b_getreg
 *
 * Description:
 *   Read a value from an ADC-B register
 *
 ****************************************************************************/

static inline uint32_t adc_b_getreg(uint32_t offset)
{
  return getreg32(R_ADC_B_BASE + offset);
}

/****************************************************************************
 * Name: adc_b_modifyreg
 *
 * Description:
 *   Modify an ADC-B register
 *
 ****************************************************************************/

static inline void adc_b_modifyreg(uint32_t offset, uint32_t clearbits,
                                   uint32_t setbits)
{
  modifyreg32(R_ADC_B_BASE + offset, clearbits, setbits);
}

/****************************************************************************
 * Name: adc_b_clock_enable
 *
 * Description:
 *   Enable the ADC-B conversion clock (ADCLK)
 *
 ****************************************************************************/

static int adc_b_clock_enable(void)
{
  uint32_t timeout;
  uint32_t regval;

  /* Configure clock source and divider (PCLKC / 1) */

  adc_b_putreg(R_ADC_B_ADCLKCR_OFFSET,
               R_ADC_B_ADCLKCR_CLKSEL_00 | R_ADC_B_ADCLKCR_DIVR_000);

  /* Enable ADCLK */

  adc_b_putreg(R_ADC_B_ADCLKENR_OFFSET, R_ADC_B_ADCLKENR_CLKEN);

  /* Wait for clock to stabilize */

  timeout = ADC_B_CLOCK_TIMEOUT_US;
  do
    {
      regval = adc_b_getreg(R_ADC_B_ADCLKSR_OFFSET);
      if (regval & R_ADC_B_ADCLKSR_CLKSR)
        {
          ainfo("ADC-B: Clock enabled successfully\n");
          return OK;
        }

      up_udelay(1);
    }
  while (--timeout > 0);

  aerr("ERROR: ADC-B clock enable timeout\n");
  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: adc_b_calibrate
 *
 * Description:
 *   Perform ADC-B calibration for both ADC units
 *
 ****************************************************************************/

static int adc_b_calibrate(void)
{
  uint32_t timeout;
  uint32_t regval;

  /* Configure calibration timing */

  adc_b_putreg(R_ADC_B_ADCALSTCR_OFFSET,
               (ADC_B_DEFAULT_SAMPLING << R_ADC_B_ADCALSTCR_CALADSST_SHIFT) |
               (ADC_B_DEFAULT_CONVERSION << R_ADC_B_ADCALSTCR_CALADCST_SHIFT));

  /* Start calibration for both ADC units */

  adc_b_putreg(R_ADC_B_ADCALSTR_OFFSET,
               R_ADC_B_ADCALSTR_ADCALST0_1 | R_ADC_B_ADCALSTR_ADCALST1_1);

  /* Wait for calibration to complete */

  timeout = ADC_B_CAL_TIMEOUT_US;
  do
    {
      regval = adc_b_getreg(R_ADC_B_ADCALENDSR_OFFSET);
      if ((regval & (R_ADC_B_ADCALENDSR_CALENDF0 |
                     R_ADC_B_ADCALENDSR_CALENDF1)) ==
          (R_ADC_B_ADCALENDSR_CALENDF0 | R_ADC_B_ADCALENDSR_CALENDF1))
        {
          /* Clear calibration end flags */

          adc_b_putreg(R_ADC_B_ADCALENDSCR_OFFSET,
                       R_ADC_B_ADCALENDSCR_CALENDC0 |
                       R_ADC_B_ADCALENDSCR_CALENDC1);

          ainfo("ADC-B: Calibration complete\n");
          return OK;
        }

      up_udelay(1);
    }
  while (--timeout > 0);

  aerr("ERROR: ADC-B calibration timeout\n");
  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: adc_b_configure_channel
 *
 * Description:
 *   Configure a virtual channel for conversion
 *
 ****************************************************************************/

static void adc_b_configure_channel(uint8_t vchannel, uint8_t pchannel,
                                    uint8_t scan_group)
{
  uint32_t regval;

  /* Configure channel control register (ADCHCR) */

  regval = (scan_group << R_ADC_B_ADCHCR_SGSEL_SHIFT) |
           (pchannel << R_ADC_B_ADCHCR_CNVCS_SHIFT) |
           (0 << R_ADC_B_ADCHCR_SSTSEL_SHIFT);  /* Use sampling table 0 */

  adc_b_putreg(R_ADC_B_ADCHCR_OFFSET(vchannel), regval);

  /* Configure data operation control A (ADDOPCRA) - no digital filter */

  adc_b_putreg(R_ADC_B_ADDOPCRA_OFFSET(vchannel), 0);

  /* Configure data operation control B (ADDOPCRB) - no averaging */

  adc_b_putreg(R_ADC_B_ADDOPCRB_OFFSET(vchannel), 0);

  /* Configure data operation control C (ADDOPCRC) - 12-bit format */

  adc_b_putreg(R_ADC_B_ADDOPCRC_OFFSET(vchannel),
               R_ADC_B_ADDOPCRC_ADPRC_10);  /* 12-bit resolution */

  ainfo("ADC-B: Channel %d configured (phys=%d, group=%d)\n",
        vchannel, pchannel, scan_group);
}

/****************************************************************************
 * Name: adc_b_start_conversion
 *
 * Description:
 *   Start an ADC conversion
 *
 ****************************************************************************/

static int adc_b_start_conversion(FAR struct ra_adc_b_priv_s *priv)
{
  /* Start conversion for scan group 0 using software trigger */

  adc_b_putreg(R_ADC_B_ADSTR_OFFSET(0), R_ADC_B_ADSTR_ADST);

  return OK;
}

/****************************************************************************
 * Name: adc_b_interrupt
 *
 * Description:
 *   ADC-B scan end interrupt handler
 *
 ****************************************************************************/

static int adc_b_interrupt(int irq, FAR void *context, FAR void *arg)
{
  FAR struct adc_dev_s *dev = (FAR struct adc_dev_s *)arg;
  FAR struct ra_adc_b_priv_s *priv =
    (FAR struct ra_adc_b_priv_s *)dev->ad_priv;
  uint32_t regval;
  int32_t data;
  int i;

  /* Check scan end status */

  regval = adc_b_getreg(R_ADC_B_ADSCANENDSR_OFFSET);
  if (regval & (1 << 0))  /* Scan group 0 complete */
    {
      /* Clear scan end flag */

      adc_b_putreg(R_ADC_B_ADSCANENDSCR_OFFSET, (1 << 0));

      /* Read conversion results for all configured channels */

      for (i = 0; i < priv->nchannels; i++)
        {
          uint8_t channel = priv->chanlist[i];

          /* Read data register */

          data = adc_b_getreg(R_ADC_B_ADDR_OFFSET(i)) & R_ADC_B_ADDR_DATA_MASK;

          /* Report to upper half */

          if (priv->cb && priv->cb->au_receive)
            {
              priv->cb->au_receive(dev, channel, data);
            }
        }

      /* For continuous mode, restart conversion */

      if (priv->scan_mode == RA_ADC_MODE_CONTINUOUS_SCAN)
        {
          adc_b_start_conversion(priv);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: adc_b_bind
 *
 * Description:
 *   Bind the upper-half driver callbacks to the lower-half implementation
 *
 ****************************************************************************/

static int adc_b_bind(FAR struct adc_dev_s *dev,
                      FAR const struct adc_callback_s *callback)
{
  FAR struct ra_adc_b_priv_s *priv =
    (FAR struct ra_adc_b_priv_s *)dev->ad_priv;

  DEBUGASSERT(priv != NULL);
  priv->cb = callback;
  return OK;
}

/****************************************************************************
 * Name: adc_b_reset
 *
 * Description:
 *   Reset the ADC device
 *
 ****************************************************************************/

static void adc_b_reset(FAR struct adc_dev_s *dev)
{
  FAR struct ra_adc_b_priv_s *priv =
    (FAR struct ra_adc_b_priv_s *)dev->ad_priv;
  irqstate_t flags;

  ainfo("ADC-B: Reset\n");

  flags = enter_critical_section();

  /* Stop any ongoing conversion */

  adc_b_putreg(R_ADC_B_ADSTOPR_OFFSET,
               R_ADC_B_ADSTOPR_ADSTOP0 | R_ADC_B_ADSTOPR_ADSTOP1);

  /* Disable all scan groups */

  adc_b_putreg(R_ADC_B_ADSGER_OFFSET, 0);

  /* Disable all interrupts */

  adc_b_putreg(R_ADC_B_ADINTCR_OFFSET, 0);
  adc_b_putreg(R_ADC_B_ADERINTCR_OFFSET, 0);
  adc_b_putreg(R_ADC_B_ADOVFINTCR_OFFSET, 0);

  /* Clear calibration flag */

  priv->calibrated = false;

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: adc_b_setup
 *
 * Description:
 *   Configure the ADC. Called the first time the ADC device is opened.
 *
 ****************************************************************************/

static int adc_b_setup(FAR struct adc_dev_s *dev)
{
  FAR struct ra_adc_b_priv_s *priv =
    (FAR struct ra_adc_b_priv_s *)dev->ad_priv;
  int ret;
  int i;

  ainfo("ADC-B: Setup\n");

  /* Initialize semaphore */

  nxsem_init(&priv->sem_excl, 0, 1);

  /* Enable module clocks via MSTP - use both ADC0 and ADC1 for ADC-B */

  ret = ra_mstp_start(RA_MSTP_ADC0);
  if (ret < 0)
    {
      aerr("ERROR: Failed to start ADC0 module: %d\n", ret);
      return ret;
    }

  ret = ra_mstp_start(RA_MSTP_ADC1);
  if (ret < 0)
    {
      aerr("ERROR: Failed to start ADC1 module: %d\n", ret);
      return ret;
    }

  /* Enable ADC clock */

  ret = adc_b_clock_enable();
  if (ret < 0)
    {
      aerr("ERROR: Failed to enable ADC-B clock: %d\n", ret);
      return ret;
    }

  /* Set ADC mode (SAR single scan) */

  adc_b_putreg(R_ADC_B_ADMDR_OFFSET, R_ADC_B_ADMDR_ADMD0_0X0);

  /* Configure sampling state table 0 */

  adc_b_putreg(R_ADC_B_ADSSTR0_OFFSET,
               (ADC_B_DEFAULT_SAMPLING << R_ADC_B_ADSSTR0_SST0_SHIFT));

  /* Configure conversion state */

  adc_b_putreg(R_ADC_B_ADCNVSTR_OFFSET,
               (ADC_B_DEFAULT_CONVERSION << R_ADC_B_ADCNVSTR_CST0_SHIFT));

  /* Perform calibration if not already done */

  if (!priv->calibrated)
    {
      ret = adc_b_calibrate();
      if (ret < 0)
        {
          aerr("ERROR: ADC-B calibration failed: %d\n", ret);
          return ret;
        }

      priv->calibrated = true;
    }

  /* Configure all enabled channels (use scan group 0, ADC unit 0) */

  for (i = 0; i < priv->nchannels; i++)
    {
      adc_b_configure_channel(i, priv->chanlist[i], 0);
    }

  /* Enable scan group 0 */

  adc_b_putreg(R_ADC_B_ADSGER_OFFSET, (1 << 0));

  /* Configure scan group 0 to use ADC0 */

  adc_b_putreg(R_ADC_B_ADSGCR0_OFFSET, R_ADC_B_ADSGCR0_SGADS0_00);

  /* Attach interrupt handler using ICU */

  priv->irq = ra_icu_attach(RA_ELC_ADC_ADI0, adc_b_interrupt, dev, true);
  if (priv->irq < 0)
    {
      aerr("ERROR: Failed to attach ADC-B interrupt: %d\n", priv->irq);
      return priv->irq;
    }

  ainfo("ADC-B: Setup complete, IRQ=%d\n", priv->irq);
  return OK;
}

/****************************************************************************
 * Name: adc_b_shutdown
 *
 * Description:
 *   Disable the ADC. Called when the ADC device is closed.
 *
 ****************************************************************************/

static void adc_b_shutdown(FAR struct adc_dev_s *dev)
{
  FAR struct ra_adc_b_priv_s *priv =
    (FAR struct ra_adc_b_priv_s *)dev->ad_priv;

  ainfo("ADC-B: Shutdown\n");

  /* Disable interrupt */

  if (priv->irq >= 0)
    {
      up_disable_irq(priv->irq);
      irq_detach(priv->irq);
      priv->irq = -1;
    }

  /* Stop any ongoing conversion */

  adc_b_putreg(R_ADC_B_ADSTOPR_OFFSET,
               R_ADC_B_ADSTOPR_ADSTOP0 | R_ADC_B_ADSTOPR_ADSTOP1);

  /* Disable all scan groups */

  adc_b_putreg(R_ADC_B_ADSGER_OFFSET, 0);

  /* Disable ADC clock */

  adc_b_putreg(R_ADC_B_ADCLKENR_OFFSET, 0);

  /* Stop module clocks */

  ra_mstp_stop(RA_MSTP_ADC1);
  ra_mstp_stop(RA_MSTP_ADC0);

  /* Destroy semaphore */

  nxsem_destroy(&priv->sem_excl);
}

/****************************************************************************
 * Name: adc_b_rxint
 *
 * Description:
 *   Enable or disable RX interrupts
 *
 ****************************************************************************/

static void adc_b_rxint(FAR struct adc_dev_s *dev, bool enable)
{
  ainfo("ADC-B: RX interrupt %s\n", enable ? "enable" : "disable");

  if (enable)
    {
      /* Enable scan end interrupt for scan group 0 */

      adc_b_modifyreg(R_ADC_B_ADINTCR_OFFSET, 0, (1 << 0));
    }
  else
    {
      /* Disable scan end interrupt for scan group 0 */

      adc_b_modifyreg(R_ADC_B_ADINTCR_OFFSET, (1 << 0), 0);
    }
}

/****************************************************************************
 * Name: adc_b_ioctl
 *
 * Description:
 *   Handle ioctl commands
 *
 ****************************************************************************/

static int adc_b_ioctl(FAR struct adc_dev_s *dev, int cmd, unsigned long arg)
{
  FAR struct ra_adc_b_priv_s *priv =
    (FAR struct ra_adc_b_priv_s *)dev->ad_priv;
  int ret = OK;

  ainfo("ADC-B: ioctl cmd=0x%02x arg=%lu\n", cmd, arg);

  switch (cmd)
    {
      case ANIOC_TRIGGER:
        {
          /* Start a conversion */

          ret = adc_b_start_conversion(priv);
        }
        break;

      case ANIOC_GET_NCHANNELS:
        {
          /* Return number of configured channels */

          ret = priv->nchannels;
        }
        break;

      default:
        aerr("ERROR: Unknown ioctl cmd: %d\n", cmd);
        ret = -ENOTTY;
        break;
    }

  return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra8_adc_initialize
 *
 * Description:
 *   Initialize the ADC-B subsystem for RA8P1
 *
 * Input Parameters:
 *   chanlist  - Bit mask of channels to enable
 *   nchannels - Number of configured channels
 *
 * Returned Value:
 *   Valid ADC device structure reference on success; NULL on failure
 *
 ****************************************************************************/

FAR struct adc_dev_s *ra8_adc_initialize(uint32_t chanlist, int nchannels)
{
  FAR struct ra_adc_b_priv_s *priv = &g_adc_b_priv;
  int i;
  int chan_idx = 0;

  ainfo("ADC-B: Initializing (chanlist=0x%08lx, nchannels=%d)\n",
        (unsigned long)chanlist, nchannels);

  if (nchannels <= 0 || nchannels > ADC_B_MAX_CHANNELS)
    {
      aerr("ERROR: Invalid number of channels: %d\n", nchannels);
      return NULL;
    }

  /* Build channel list from bitmask */

  for (i = 0; i < 32 && chan_idx < nchannels; i++)
    {
      if (chanlist & (1 << i))
        {
          priv->chanlist[chan_idx++] = i;
        }
    }

  priv->nchannels = chan_idx;
  priv->current = 0;

  ainfo("ADC-B: Configured %d channels\n", priv->nchannels);

  return &g_adc_b_dev;
}

#endif /* CONFIG_RA_ADC_B */


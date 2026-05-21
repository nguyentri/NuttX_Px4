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
#include "ra_elc.h"
#include "ra_adc_b.h"

#ifdef CONFIG_RA_DTC
#include "ra_dtc.h"
#endif

#ifdef CONFIG_RA_DMAC
#include "ra_dmac.h"
#endif

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
#define ADC_B_CONV_TIMEOUT_US    10000    /* Conversion timeout (10ms) */

/* Default sampling time (in ADCLK cycles) */

#define ADC_B_DEFAULT_SAMPLING   24       /* Minimum 24 cycles for 16-bit */

/* Default conversion time (in ADCLK cycles) */

#define ADC_B_DEFAULT_CONVERSION 18       /* Minimum 18 cycles */

/* Resolution to data format mapping */

#define ADC_B_RESOLUTION_TO_ADPRC(res) \
  ((res) == RA_ADC_RESOLUTION_16BIT ? R_ADC_B_ADDOPCRC_ADPRC_00 : \
   (res) == RA_ADC_RESOLUTION_14BIT ? R_ADC_B_ADDOPCRC_ADPRC_01 : \
   (res) == RA_ADC_RESOLUTION_12BIT ? R_ADC_B_ADDOPCRC_ADPRC_10 : \
   R_ADC_B_ADDOPCRC_ADPRC_11)

/* Resolution to full count mapping */

#define ADC_B_RESOLUTION_TO_FULLCOUNT(res) \
  ((res) == RA_ADC_RESOLUTION_16BIT ? 65535 : \
   (res) == RA_ADC_RESOLUTION_14BIT ? 16383 : \
   (res) == RA_ADC_RESOLUTION_12BIT ? 4095 : 1023)

/* Averaging count mapping */

#define ADC_B_AVG_COUNT_TO_ADC(cnt) \
  ((cnt) <= 1 ? R_ADC_B_ADDOPCRB_ADC_0X0 : \
   (cnt) <= 2 ? R_ADC_B_ADDOPCRB_ADC_0X1 : \
   (cnt) <= 4 ? R_ADC_B_ADDOPCRB_ADC_0X3 : \
   (cnt) <= 8 ? R_ADC_B_ADDOPCRB_ADC_0X4 : \
   (cnt) <= 16 ? R_ADC_B_ADDOPCRB_ADC_0X5 : \
   (cnt) <= 32 ? R_ADC_B_ADDOPCRB_ADC_0X6 : \
   (cnt) <= 64 ? R_ADC_B_ADDOPCRB_ADC_0X7 : \
   (cnt) <= 128 ? R_ADC_B_ADDOPCRB_ADC_0X8 : \
   (cnt) <= 256 ? R_ADC_B_ADDOPCRB_ADC_0X9 : \
   (cnt) <= 512 ? R_ADC_B_ADDOPCRB_ADC_0XA : R_ADC_B_ADDOPCRB_ADC_0XB)

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* Trigger source types */

enum adc_b_trigger_e
{
  ADC_B_TRIG_SOFTWARE = 0,      /* Software trigger */
  ADC_B_TRIG_ELC,               /* ELC (Event Link Controller) trigger */
  ADC_B_TRIG_GPT_A,             /* GPT Compare Match A trigger */
  ADC_B_TRIG_GPT_B,             /* GPT Compare Match B trigger */
  ADC_B_TRIG_EXTERNAL,          /* External pin trigger */
};

/* ADC-B private data structure */

struct ra_adc_b_priv_s
{
  struct adc_dev_s dev;               /* Public ADC device structure */
  const struct adc_callback_s *cb;    /* Upper half callback */
  sem_t sem_excl;                     /* Mutual exclusion semaphore */
  int irq;                            /* Dynamically assigned IRQ number */
  int fifo_irq;                       /* FIFO interrupt number */
  uint8_t nchannels;                  /* Number of configured channels */
  uint8_t current;                    /* Current channel being processed */
  struct ra_adc_b_chan_cfg_s *chan_cfg; /* Channel configuration */
  uint8_t resolution;                 /* ADC resolution setting */
  uint8_t scan_mode;                  /* Scan mode (single/continuous) */
  uint8_t trigger_source;             /* Trigger source type */
  uint8_t avg_count;                  /* Averaging count (1,2,4,8,16...) */
  uint8_t scan_group;                 /* Scan group number (0-8) */
  bool calibrated;                    /* Calibration complete flag */
  bool fifo_enabled;                  /* FIFO mode enabled */
  bool hw_trigger_enabled;            /* Hardware trigger enabled */

#ifdef CONFIG_RA_DTC
  ra_dtc_handle_t dtc_handle;         /* DTC handle for data transfer */
  uint16_t *dma_buffer;               /* DMA buffer for results */
  bool dtc_enabled;                   /* DTC transfer enabled */
#endif
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
static void adc_b_clock_disable(void);
static int  adc_b_calibrate(void);
static void adc_b_configure_channel(FAR struct ra_adc_b_priv_s *priv,
                                    FAR const struct ra_adc_b_chan_cfg_s *cfg);
static int  adc_b_start_conversion(FAR struct ra_adc_b_priv_s *priv);
static int  adc_b_stop_conversion(FAR struct ra_adc_b_priv_s *priv);
static int  adc_b_interrupt(int irq, FAR void *context, FAR void *arg);

/* FIFO functions */

static int  adc_b_fifo_enable(FAR struct ra_adc_b_priv_s *priv);
static void adc_b_fifo_disable(FAR struct ra_adc_b_priv_s *priv);
static int  adc_b_fifo_read(FAR struct ra_adc_b_priv_s *priv);
static int  adc_b_fifo_interrupt(int irq, FAR void *context, FAR void *arg);

/* Hardware trigger functions */

static int  adc_b_configure_gpt_trigger(FAR struct ra_adc_b_priv_s *priv,
                                        uint8_t gpt_channel, bool use_cmpb);
static int  adc_b_configure_elc_trigger(FAR struct ra_adc_b_priv_s *priv,
                                        uint16_t elc_event);
static int  adc_b_enable_hw_trigger(FAR struct ra_adc_b_priv_s *priv);
static void adc_b_disable_hw_trigger(FAR struct ra_adc_b_priv_s *priv);

/* Synchronous read function */

static int  adc_b_read_sync(FAR struct ra_adc_b_priv_s *priv,
                            uint8_t channel, FAR int32_t *value);

#ifdef CONFIG_RA_DTC
/* DTC functions */

static int  adc_b_dtc_setup(FAR struct ra_adc_b_priv_s *priv);
static void adc_b_dtc_cleanup(FAR struct ra_adc_b_priv_s *priv);
#endif

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

/* ADC-B device structure */

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
 * Name: adc_b_clock_disable
 *
 * Description:
 *   Disable the ADC-B conversion clock
 *
 ****************************************************************************/

static void adc_b_clock_disable(void)
{
  /* Disable ADCLK */

  adc_b_putreg(R_ADC_B_ADCLKENR_OFFSET, 0);
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

static void adc_b_configure_channel(FAR struct ra_adc_b_priv_s *priv,
                                    FAR const struct ra_adc_b_chan_cfg_s *cfg)
{
  uint32_t regval;
  uint32_t adprc;
  uint32_t avemd;
  uint32_t adc_cnt;
  uint8_t vchannel = cfg->vchannel;
  uint8_t pchannel = cfg->pchannel;
  uint8_t scan_group = cfg->scan_group_id;

  /* Configure channel control register (ADCHCR) */

  regval = (scan_group << R_ADC_B_ADCHCR_SGSEL_SHIFT) |
           (pchannel << R_ADC_B_ADCHCR_CNVCS_SHIFT) |
           (cfg->sampling_table << R_ADC_B_ADCHCR_SSTSEL_SHIFT);

  adc_b_putreg(R_ADC_B_ADCHCR_OFFSET(vchannel), regval);

  /* Configure data operation control A (ADDOPCRA) - no digital filter */

  adc_b_putreg(R_ADC_B_ADDOPCRA_OFFSET(vchannel), 0);

  /* Configure data operation control B (ADDOPCRB) - averaging if enabled */

  if (priv->avg_count > 1)
    {
      avemd = R_ADC_B_ADDOPCRB_AVEMD_10;  /* Averaging mode */
      adc_cnt = ADC_B_AVG_COUNT_TO_ADC(priv->avg_count);
    }
  else
    {
      avemd = R_ADC_B_ADDOPCRB_AVEMD_00;  /* No averaging */
      adc_cnt = 0;
    }

  adc_b_putreg(R_ADC_B_ADDOPCRB_OFFSET(vchannel), avemd | adc_cnt);

  /* Configure data operation control C (ADDOPCRC) - resolution */
  /* Use per-channel resolution if specified, otherwise global */

  uint8_t res = (cfg->resolution != 0) ? cfg->resolution : priv->resolution;
  adprc = ADC_B_RESOLUTION_TO_ADPRC(res);
  adc_b_putreg(R_ADC_B_ADDOPCRC_OFFSET(vchannel), adprc);

  ainfo("ADC-B: Channel %d configured (phys=%d, group=%d, res=%d, avg=%d)\n",
        vchannel, pchannel, scan_group, res, priv->avg_count);
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
  uint8_t group = priv->scan_group;

  /* Start conversion for the configured scan group using software trigger */

  adc_b_putreg(R_ADC_B_ADSTR_OFFSET(group), R_ADC_B_ADSTR_ADST);

  return OK;
}

/****************************************************************************
 * Name: adc_b_stop_conversion
 *
 * Description:
 *   Stop any ongoing ADC conversion
 *
 ****************************************************************************/

static int adc_b_stop_conversion(FAR struct ra_adc_b_priv_s *priv)
{
  /* Force stop both ADC units */

  adc_b_putreg(R_ADC_B_ADSTOPR_OFFSET,
               R_ADC_B_ADSTOPR_ADSTOP0 | R_ADC_B_ADSTOPR_ADSTOP1);

  return OK;
}

/****************************************************************************
 * Name: adc_b_fifo_enable
 *
 * Description:
 *   Enable FIFO mode for the configured scan group
 *
 ****************************************************************************/

static int adc_b_fifo_enable(FAR struct ra_adc_b_priv_s *priv)
{
  uint8_t group = priv->scan_group;
  uint32_t fifo_en_bit = (1U << group);

  /* Enable FIFO for the scan group */

  adc_b_modifyreg(R_ADC_B_ADFIFOCR_OFFSET, 0, fifo_en_bit);

  /* Set FIFO interrupt level to trigger when half full (8 entries) */

  if (group <= 1)
    {
      adc_b_modifyreg(R_ADC_B_ADFIFOINTLR0_OFFSET, 0xf << (group * 16),
                      8U << (group * 16));
    }
  else if (group <= 3)
    {
      adc_b_modifyreg(R_ADC_B_ADFIFOINTLR1_OFFSET, 0xf << ((group - 2) * 16),
                      8U << ((group - 2) * 16));
    }

  /* Attach FIFO interrupt */

  if (priv->fifo_irq < 0)
    {
      priv->fifo_irq = ra_icu_attach(RA_ELC_ADC_FIFOREQ0 + group,
                                     adc_b_fifo_interrupt,
                                     &priv->dev, true);
      if (priv->fifo_irq < 0)
        {
          aerr("ERROR: Failed to attach FIFO interrupt: %d\n", priv->fifo_irq);
          return priv->fifo_irq;
        }
    }

  /* Enable FIFO interrupt for the scan group */

  adc_b_modifyreg(R_ADC_B_ADFIFOINTCR_OFFSET, 0, fifo_en_bit);

  priv->fifo_enabled = true;

  ainfo("ADC-B: FIFO enabled for scan group %d\n", group);
  return OK;
}

/****************************************************************************
 * Name: adc_b_fifo_disable
 *
 * Description:
 *   Disable FIFO mode for the configured scan group
 *
 ****************************************************************************/

static void adc_b_fifo_disable(FAR struct ra_adc_b_priv_s *priv)
{
  uint8_t group = priv->scan_group;
  uint32_t fifo_en_bit = (1U << group);

  /* Disable FIFO interrupt */

  adc_b_modifyreg(R_ADC_B_ADFIFOINTCR_OFFSET, fifo_en_bit, 0);

  /* Detach FIFO interrupt */

  if (priv->fifo_irq >= 0)
    {
      ra_icu_detach(priv->fifo_irq);
      priv->fifo_irq = -1;
    }

  /* Clear FIFO data */

  adc_b_putreg(R_ADC_B_ADFIFODCR_OFFSET, fifo_en_bit);

  /* Disable FIFO */

  adc_b_modifyreg(R_ADC_B_ADFIFOCR_OFFSET, fifo_en_bit, 0);

  priv->fifo_enabled = false;
}

/****************************************************************************
 * Name: adc_b_fifo_read
 *
 * Description:
 *   Read all available data from FIFO
 *
 ****************************************************************************/

static int adc_b_fifo_read(FAR struct ra_adc_b_priv_s *priv)
{
  uint8_t group = priv->scan_group;
  uint32_t fifo_status;
  uint32_t fifo_data;
  uint8_t fifo_count;
  uint8_t channel;
  int32_t data;
  int i;

  /* Get FIFO status to determine number of available entries */

  switch (group)
    {
      case 0:
      case 1:
        fifo_status = adc_b_getreg(R_ADC_B_ADFIFOSR0_OFFSET);
        fifo_count = (group == 0) ?
                     (fifo_status & R_ADC_B_ADFIFOSR0_FIFOST0_MASK) :
                     ((fifo_status >> 16) & 0xf);
        break;
      case 2:
      case 3:
        fifo_status = adc_b_getreg(R_ADC_B_ADFIFOSR1_OFFSET);
        fifo_count = (group == 2) ?
                     (fifo_status & 0xf) :
                     ((fifo_status >> 16) & 0xf);
        break;
      default:
        fifo_count = 0;
        break;
    }

  /* Read all available FIFO entries */

  for (i = 0; i < fifo_count; i++)
    {
      fifo_data = adc_b_getreg(R_ADC_B_ADFIFODR_OFFSET(group));

      /* Extract channel and data from FIFO entry */

      channel = (fifo_data >> 24) & 0x7f;
      data = fifo_data & R_ADC_B_ADFIFODR_DATA_MASK;

      /* Check for error flag */

      if (fifo_data & R_ADC_B_ADFIFODR_ERR)
        {
          awarn("ADC-B: FIFO data error on channel %d\n", channel);
          continue;
        }

      /* Report to upper half */

      if (priv->cb && priv->cb->au_receive)
        {
          priv->cb->au_receive(&priv->dev, channel, data);
        }
    }

  return fifo_count;
}

/****************************************************************************
 * Name: adc_b_fifo_interrupt
 *
 * Description:
 *   FIFO interrupt handler
 *
 ****************************************************************************/

static int adc_b_fifo_interrupt(int irq, FAR void *context, FAR void *arg)
{
  FAR struct adc_dev_s *dev = (FAR struct adc_dev_s *)arg;
  FAR struct ra_adc_b_priv_s *priv =
    (FAR struct ra_adc_b_priv_s *)dev->ad_priv;

  /* Read FIFO data */

  adc_b_fifo_read(priv);

  /* Clear FIFO overflow flag if set */

  adc_b_putreg(R_ADC_B_ADFIFOERSCR_OFFSET, (1U << priv->scan_group));

  return OK;
}

/****************************************************************************
 * Name: adc_b_configure_gpt_trigger
 *
 * Description:
 *   Configure GPT (General Purpose Timer) hardware trigger for ADC
 *
 ****************************************************************************/

static int adc_b_configure_gpt_trigger(FAR struct ra_adc_b_priv_s *priv,
                                       uint8_t gpt_channel, bool use_cmpb)
{
  uint8_t group = priv->scan_group;
  uint32_t trgval;

  if (gpt_channel >= 14)
    {
      aerr("ERROR: Invalid GPT channel %d\n", gpt_channel);
      return -EINVAL;
    }

  /* Configure GPT trigger for the scan group */

  if (use_cmpb)
    {
      /* Use GPT Compare Match B */

      trgval = (1U << (gpt_channel + 16));
      priv->trigger_source = ADC_B_TRIG_GPT_B;
    }
  else
    {
      /* Use GPT Compare Match A */

      trgval = (1U << gpt_channel);
      priv->trigger_source = ADC_B_TRIG_GPT_A;
    }

  adc_b_putreg(R_ADC_B_ADTRGGPT_OFFSET(group), trgval);

  ainfo("ADC-B: GPT%d %s trigger configured for group %d\n",
        gpt_channel, use_cmpb ? "CMPB" : "CMPA", group);

  return OK;
}

/****************************************************************************
 * Name: adc_b_configure_elc_trigger
 *
 * Description:
 *   Configure ELC (Event Link Controller) hardware trigger for ADC
 *
 ****************************************************************************/

static int adc_b_configure_elc_trigger(FAR struct ra_adc_b_priv_s *priv,
                                       uint16_t elc_event)
{
  uint8_t group = priv->scan_group;
  ra_elc_peripheral_t elc_peripheral;
  int ret;

  /* Map scan group to ELC peripheral */

  switch (group)
    {
      case 0:
        elc_peripheral = RA_ELC_PERIPHERAL_ADC0;
        break;
      case 1:
        elc_peripheral = RA_ELC_PERIPHERAL_ADC0_B;
        break;
      case 2:
        elc_peripheral = RA_ELC_PERIPHERAL_ADC0_C;
        break;
      default:
        aerr("ERROR: ELC trigger not supported for group %d\n", group);
        return -EINVAL;
    }

  /* Configure ELC link */

  ret = ra_elc_link_set(elc_peripheral, elc_event);
  if (ret < 0)
    {
      aerr("ERROR: Failed to set ELC link: %d\n", ret);
      return ret;
    }

  /* Enable ELC trigger for the scan group */

  adc_b_putreg(R_ADC_B_ADTRGELC_OFFSET(group), 0x3f);  /* Enable all ELC triggers */

  priv->trigger_source = ADC_B_TRIG_ELC;

  ainfo("ADC-B: ELC trigger (event=0x%04x) configured for group %d\n",
        elc_event, group);

  return OK;
}

/****************************************************************************
 * Name: adc_b_enable_hw_trigger
 *
 * Description:
 *   Enable hardware triggering for ADC conversions
 *
 ****************************************************************************/

static int adc_b_enable_hw_trigger(FAR struct ra_adc_b_priv_s *priv)
{
  uint8_t group = priv->scan_group;
  uint32_t trgval;

  /* Enable trigger for the scan group */

  trgval = (1U << group);
  adc_b_modifyreg(R_ADC_B_ADTRGENR_OFFSET, 0, trgval);

  priv->hw_trigger_enabled = true;

  ainfo("ADC-B: Hardware trigger enabled for group %d\n", group);
  return OK;
}

/****************************************************************************
 * Name: adc_b_disable_hw_trigger
 *
 * Description:
 *   Disable hardware triggering for ADC conversions
 *
 ****************************************************************************/

static void adc_b_disable_hw_trigger(FAR struct ra_adc_b_priv_s *priv)
{
  uint8_t group = priv->scan_group;
  uint32_t trgval;

  /* Disable trigger for the scan group */

  trgval = (1U << group);
  adc_b_modifyreg(R_ADC_B_ADTRGENR_OFFSET, trgval, 0);

  /* Clear GPT and ELC triggers */

  adc_b_putreg(R_ADC_B_ADTRGGPT_OFFSET(group), 0);
  adc_b_putreg(R_ADC_B_ADTRGELC_OFFSET(group), 0);

  priv->hw_trigger_enabled = false;
  priv->trigger_source = ADC_B_TRIG_SOFTWARE;
}

/****************************************************************************
 * Name: adc_b_read_sync
 *
 * Description:
 *   Perform a synchronous ADC read on a single channel
 *
 ****************************************************************************/

static int adc_b_read_sync(FAR struct ra_adc_b_priv_s *priv,
                           uint8_t channel, FAR int32_t *value)
{
  uint32_t timeout;
  uint32_t regval;
  int vchannel;
  int i;
  int ret;

  /* Get exclusive access */
  ret = nxsem_wait(&priv->sem_excl);
  if (ret < 0)
    {
      return ret;
    }

  /* Find the virtual channel for the physical channel */

  vchannel = -1;
  for (i = 0; i < priv->nchannels; i++)
    {
      if (priv->chan_cfg[i].pchannel == channel)
        {
          vchannel = priv->chan_cfg[i].vchannel;
          break;
        }
    }

  if (vchannel < 0)
    {
      aerr("ERROR: Channel %d not configured\n", channel);
      nxsem_post(&priv->sem_excl);
      return -EINVAL;
    }

  /* Start conversion */

  adc_b_start_conversion(priv);

  /* Wait for conversion to complete */

  timeout = ADC_B_CONV_TIMEOUT_US;
  do
    {
      regval = adc_b_getreg(R_ADC_B_ADSCANENDSR_OFFSET);
      if (regval & (1U << priv->scan_group))
        {
          /* Clear scan end flag */

          adc_b_putreg(R_ADC_B_ADSCANENDSCR_OFFSET, (1U << priv->scan_group));

          /* Read conversion result */

          regval = adc_b_getreg(R_ADC_B_ADDR_OFFSET(vchannel));
          *value = regval & R_ADC_B_ADDR_DATA_MASK;

          /* Check for error */

          if (regval & R_ADC_B_ADDR_ERR)
            {
              awarn("ADC-B: Conversion error on channel %d\n", channel);
              nxsem_post(&priv->sem_excl);
              return -EIO;
            }

          nxsem_post(&priv->sem_excl);
          return OK;
        }

      up_udelay(1);
    }
  while (--timeout > 0);

  aerr("ERROR: ADC-B conversion timeout\n");
  nxsem_post(&priv->sem_excl);
  return -ETIMEDOUT;
}

#ifdef CONFIG_RA_DTC
/****************************************************************************
 * Name: adc_b_dtc_setup
 *
 * Description:
 *   Setup DTC for ADC data transfer
 *
 ****************************************************************************/

static int adc_b_dtc_setup(FAR struct ra_adc_b_priv_s *priv)
{
  ra_dtc_config_t config;
  int ret;

  /* Allocate DMA buffer */

  priv->dma_buffer = kmm_malloc(priv->nchannels * sizeof(uint16_t));
  if (priv->dma_buffer == NULL)
    {
      aerr("ERROR: Failed to allocate DMA buffer\n");
      return -ENOMEM;
    }

  memset(priv->dma_buffer, 0, priv->nchannels * sizeof(uint16_t));

  /* Configure DTC */

  memset(&config, 0, sizeof(config));
  config.mode = RA_DTC_MODE_REPEAT;
  config.size = RA_DTC_SIZE_WORD;
  config.src_addr_mode = RA_DTC_ADDR_FIXED;
  config.dest_addr_mode = RA_DTC_ADDR_INCR;
  config.src_addr = R_ADC_B_BASE + R_ADC_B_ADFIFODR_OFFSET(priv->scan_group);
  config.dest_addr = (uint32_t)priv->dma_buffer;
  config.transfer_count = priv->nchannels;

  /* Open DTC channel */

  ret = ra_dtc_open(&priv->dtc_handle, &config);
  if (ret < 0)
    {
      aerr("ERROR: Failed to open DTC: %d\n", ret);
      kmm_free(priv->dma_buffer);
      priv->dma_buffer = NULL;
      return ret;
    }

  /* Enable DTC */

  ret = ra_dtc_enable(priv->dtc_handle);
  if (ret < 0)
    {
      aerr("ERROR: Failed to enable DTC: %d\n", ret);
      ra_dtc_close(priv->dtc_handle);
      kmm_free(priv->dma_buffer);
      priv->dma_buffer = NULL;
      priv->dtc_handle = NULL;
      return ret;
    }

  priv->dtc_enabled = true;

  ainfo("ADC-B: DTC configured for %d channels\n", priv->nchannels);
  return OK;
}

/****************************************************************************
 * Name: adc_b_dtc_cleanup
 *
 * Description:
 *   Cleanup DTC resources
 *
 ****************************************************************************/

static void adc_b_dtc_cleanup(FAR struct ra_adc_b_priv_s *priv)
{
  if (priv->dtc_handle != NULL)
    {
      ra_dtc_disable(priv->dtc_handle);
      ra_dtc_close(priv->dtc_handle);
      priv->dtc_handle = NULL;
    }

  if (priv->dma_buffer != NULL)
    {
      kmm_free(priv->dma_buffer);
      priv->dma_buffer = NULL;
    }

  priv->dtc_enabled = false;
}
#endif /* CONFIG_RA_DTC */

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
  uint8_t group = priv->scan_group;

  /* Check scan end status */

  regval = adc_b_getreg(R_ADC_B_ADSCANENDSR_OFFSET);
  if (regval & (1U << group))
    {
      /* Clear scan end flag */

      adc_b_putreg(R_ADC_B_ADSCANENDSCR_OFFSET, (1U << group));

      /* If FIFO is enabled, read from FIFO */

      if (priv->fifo_enabled)
        {
          adc_b_fifo_read(priv);
        }
      else
        {
          /* Read conversion results for all configured channels */

          for (i = 0; i < priv->nchannels; i++)
            {
              uint8_t vchannel = priv->chan_cfg[i].vchannel;
              uint8_t pchannel = priv->chan_cfg[i].pchannel;

              /* Read data register */

              regval = adc_b_getreg(R_ADC_B_ADDR_OFFSET(vchannel));
              data = regval & R_ADC_B_ADDR_DATA_MASK;

              /* Check for error flag */

              if (regval & R_ADC_B_ADDR_ERR)
                {
                  awarn("ADC-B: Data error on channel %d\n", pchannel);
                  continue;
                }

              /* Report to upper half */

              if (priv->cb && priv->cb->au_receive)
                {
                  priv->cb->au_receive(dev, pchannel, data);
                }
            }
        }

      /* For continuous mode, conversion restarts automatically */
    }

  /* Check for overflow errors */

  regval = adc_b_getreg(R_ADC_B_ADOVFERSR_OFFSET);
  if (regval & (R_ADC_B_ADOVFERSR_ADOVFEF0 | R_ADC_B_ADOVFERSR_ADOVFEF1))
    {
      awarn("ADC-B: Overflow error detected: 0x%08lx\n",
            (unsigned long)regval);

      /* Clear overflow error flags */

      adc_b_putreg(R_ADC_B_ADOVFERSCR_OFFSET,
                   R_ADC_B_ADOVFERSCR_ADOVFEC0 | R_ADC_B_ADOVFERSCR_ADOVFEC1);
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
  uint8_t group = priv->scan_group;

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

  /* Set ADC mode based on scan mode configuration */

  switch (priv->scan_mode)
    {
      case RA_ADC_MODE_CONTINUOUS_SCAN:
        adc_b_putreg(R_ADC_B_ADMDR_OFFSET, R_ADC_B_ADMDR_ADMD0_0X1);
        break;
      case RA_ADC_MODE_BACKGROUND_SCAN:
        adc_b_putreg(R_ADC_B_ADMDR_OFFSET, R_ADC_B_ADMDR_ADMD0_0XA);
        break;
      case RA_ADC_MODE_SINGLE_SCAN:
      default:
        adc_b_putreg(R_ADC_B_ADMDR_OFFSET, R_ADC_B_ADMDR_ADMD0_0X0);
        break;
    }

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

  /* Configure all enabled channels */

  for (i = 0; i < priv->nchannels; i++)
    {
      adc_b_configure_channel(priv, &priv->chan_cfg[i]);
    }

  /* Enable the scan group */

  adc_b_putreg(R_ADC_B_ADSGER_OFFSET, (1U << group));

  /* Configure scan group to use ADC0 */

  if (group <= 3)
    {
      adc_b_modifyreg(R_ADC_B_ADSGCR0_OFFSET,
                      (0x3U << (group * 8)), 0);  /* Select ADC0 */
    }

  /* Attach interrupt handler using ICU */

  priv->irq = ra_icu_attach(RA_ELC_ADC_ADI0 + group, adc_b_interrupt,
                            dev, true);
  if (priv->irq < 0)
    {
      aerr("ERROR: Failed to attach ADC-B interrupt: %d\n", priv->irq);
      return priv->irq;
    }

#ifdef CONFIG_RA_DTC
  /* Setup DTC if enabled */

  if (priv->dtc_enabled)
    {
      ret = adc_b_dtc_setup(priv);
      if (ret < 0)
        {
          awarn("ADC-B: DTC setup failed, using interrupt mode\n");
          priv->dtc_enabled = false;
        }
    }
#endif

  ainfo("ADC-B: Setup complete, IRQ=%d, group=%d, resolution=%d\n",
        priv->irq, group, priv->resolution);
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

#ifdef CONFIG_RA_DTC
  /* Cleanup DTC */

  if (priv->dtc_enabled)
    {
      adc_b_dtc_cleanup(priv);
    }
#endif

  /* Disable hardware trigger if enabled */

  if (priv->hw_trigger_enabled)
    {
      adc_b_disable_hw_trigger(priv);
    }

  /* Disable FIFO if enabled */

  if (priv->fifo_enabled)
    {
      adc_b_fifo_disable(priv);
    }

  /* Disable interrupts */

  if (priv->irq >= 0)
    {
      ra_icu_detach(priv->irq);
      priv->irq = -1;
    }

  if (priv->fifo_irq >= 0)
    {
      ra_icu_detach(priv->fifo_irq);
      priv->fifo_irq = -1;
    }

  /* Stop any ongoing conversion */

  adc_b_stop_conversion(priv);

  /* Disable all scan groups */

  adc_b_putreg(R_ADC_B_ADSGER_OFFSET, 0);

  /* Disable ADC clock */

  adc_b_clock_disable();

  /* Stop module clocks */

  ra_mstp_stop(RA_MSTP_ADC1);
  ra_mstp_stop(RA_MSTP_ADC0);

  /* Clear calibration flag */

  priv->calibrated = false;

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
  FAR struct ra_adc_b_priv_s *priv =
    (FAR struct ra_adc_b_priv_s *)dev->ad_priv;
  uint8_t group = priv->scan_group;
  uint32_t int_bit = (1U << group);

  ainfo("ADC-B: RX interrupt %s for group %d\n",
        enable ? "enable" : "disable", group);

  if (enable)
    {
      /* Enable scan end interrupt for the scan group */

      adc_b_modifyreg(R_ADC_B_ADINTCR_OFFSET, 0, int_bit);

      /* Enable error interrupts */

      adc_b_modifyreg(R_ADC_B_ADERINTCR_OFFSET, 0,
                      R_ADC_B_ADERINTCR_ADEIE0 | R_ADC_B_ADERINTCR_ADEIE1);
      adc_b_modifyreg(R_ADC_B_ADOVFINTCR_OFFSET, 0,
                      R_ADC_B_ADOVFINTCR_ADOVFIE0 | R_ADC_B_ADOVFINTCR_ADOVFIE1);
    }
  else
    {
      /* Disable scan end interrupt for the scan group */

      adc_b_modifyreg(R_ADC_B_ADINTCR_OFFSET, int_bit, 0);

      /* Disable error interrupts */

      adc_b_modifyreg(R_ADC_B_ADERINTCR_OFFSET,
                      R_ADC_B_ADERINTCR_ADEIE0 | R_ADC_B_ADERINTCR_ADEIE1, 0);
      adc_b_modifyreg(R_ADC_B_ADOVFINTCR_OFFSET,
                      R_ADC_B_ADOVFINTCR_ADOVFIE0 | R_ADC_B_ADOVFINTCR_ADOVFIE1, 0);
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

  ret = nxsem_wait(&priv->sem_excl);
  if (ret < 0)
    {
      return ret;
    }

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
          FAR int *count = (FAR int *)((uintptr_t)arg);
          if (count)
            {
              *count = priv->nchannels;
              ret = OK;
            }
          else
            {
              ret = -EINVAL;
            }
        }
        break;

      case ANIOC_RESET_FIFO:
        {
          /* Clear FIFO data */

          adc_b_putreg(R_ADC_B_ADFIFODCR_OFFSET, (1U << priv->scan_group));
          ret = OK;
        }
        break;

      case ANIOC_SAMPLES_ON_READ:
        {
          /* Configure number of samples to read (averaging) */

          if (arg > 0 && arg <= 1024)
            {
              priv->avg_count = (uint8_t)arg;
              /* Reconfigure channels to apply averaging */
              int i;
              for (i = 0; i < priv->nchannels; i++)
                {
                  adc_b_configure_channel(priv, &priv->chan_cfg[i]);
                }
              ret = OK;
            }
          else
            {
              ret = -EINVAL;
            }
        }
        break;

      default:
        aerr("ERROR: Unknown ioctl cmd: %d\n", cmd);
        ret = -ENOTTY;
        break;
    }

  nxsem_post(&priv->sem_excl);
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

FAR struct adc_dev_s *ra8_adc_initialize(
    FAR const struct ra_adc_b_chan_cfg_s *channels, int nchannels)
{
  FAR struct ra_adc_b_priv_s *priv;

  ainfo("ADC-B: Initializing (nchannels=%d)\n", nchannels);

  if (nchannels <= 0 || nchannels > ADC_B_MAX_CHANNELS)
    {
      aerr("ERROR: Invalid number of channels: %d\n", nchannels);
      return NULL;
    }

  /* Allocate private data structure */

  priv = (FAR struct ra_adc_b_priv_s *)
    kmm_zalloc(sizeof(struct ra_adc_b_priv_s));

  if (!priv)
    {
      aerr("ERROR: Failed to allocate ADC private data\n");
      return NULL;
    }

  /* Allocate channel configuration array */

  priv->chan_cfg = (FAR struct ra_adc_b_chan_cfg_s *)
    kmm_malloc(nchannels * sizeof(struct ra_adc_b_chan_cfg_s));

  if (!priv->chan_cfg)
    {
      aerr("ERROR: Failed to allocate channel configuration\n");
      kmm_free(priv);
      return NULL;
    }

  /* Copy channel configuration */

  memcpy(priv->chan_cfg, channels,
         nchannels * sizeof(struct ra_adc_b_chan_cfg_s));

  /* Initialize private data */

  priv->nchannels = nchannels;
  priv->irq = -1;
  priv->fifo_irq = -1;
  priv->resolution = RA_ADC_RESOLUTION_12BIT;
  priv->scan_mode = RA_ADC_MODE_SINGLE_SCAN;
  priv->trigger_source = ADC_B_TRIG_SOFTWARE;
  priv->avg_count = 1;

  /* Use the scan group from the first channel as the primary group */
  priv->scan_group = channels[0].scan_group_id;

  /* Initialize device structure */

  priv->dev.ad_ops = &g_adc_b_ops;
  priv->dev.ad_priv = priv;

  ainfo("ADC-B: Configured %d channels, group %d\n",
        priv->nchannels, priv->scan_group);

  return &priv->dev;
}

/****************************************************************************
 * Name: ra8_adc_set_resolution
 ****************************************************************************/

int ra8_adc_set_resolution(FAR struct adc_dev_s *dev, uint8_t resolution)
{
  FAR struct ra_adc_b_priv_s *priv;

  if (dev == NULL)
    {
      return -EINVAL;
    }

  priv = (FAR struct ra_adc_b_priv_s *)dev->ad_priv;
  priv->resolution = resolution;
  return OK;
}

/****************************************************************************
 * Name: ra8_adc_set_scan_mode
 ****************************************************************************/

int ra8_adc_set_scan_mode(FAR struct adc_dev_s *dev, uint8_t mode)
{
  FAR struct ra_adc_b_priv_s *priv;

  if (dev == NULL)
    {
      return -EINVAL;
    }

  priv = (FAR struct ra_adc_b_priv_s *)dev->ad_priv;
  priv->scan_mode = mode;
  return OK;
}

/****************************************************************************
 * Name: ra8_adc_set_averaging
 ****************************************************************************/

int ra8_adc_set_averaging(FAR struct adc_dev_s *dev, uint16_t count)
{
  FAR struct ra_adc_b_priv_s *priv;

  if (dev == NULL)
    {
      return -EINVAL;
    }

  priv = (FAR struct ra_adc_b_priv_s *)dev->ad_priv;
  priv->avg_count = (uint8_t)count;
  return OK;
}

/****************************************************************************
 * Name: ra8_adc_enable_fifo
 ****************************************************************************/

int ra8_adc_enable_fifo(FAR struct adc_dev_s *dev, bool enable)
{
  FAR struct ra_adc_b_priv_s *priv;

  if (dev == NULL)
    {
      return -EINVAL;
    }

  priv = (FAR struct ra_adc_b_priv_s *)dev->ad_priv;

  if (enable)
    {
      return adc_b_fifo_enable(priv);
    }
  else
    {
      adc_b_fifo_disable(priv);
      return OK;
    }
}

/****************************************************************************
 * Name: ra8_adc_configure_gpt_trigger
 ****************************************************************************/

int ra8_adc_configure_gpt_trigger(FAR struct adc_dev_s *dev,
                                  uint8_t gpt_channel, bool use_cmpb)
{
  FAR struct ra_adc_b_priv_s *priv;

  if (dev == NULL)
    {
      return -EINVAL;
    }

  priv = (FAR struct ra_adc_b_priv_s *)dev->ad_priv;
  return adc_b_configure_gpt_trigger(priv, gpt_channel, use_cmpb);
}

/****************************************************************************
 * Name: ra8_adc_configure_elc_trigger
 ****************************************************************************/

int ra8_adc_configure_elc_trigger(FAR struct adc_dev_s *dev,
                                  uint16_t elc_event)
{
  FAR struct ra_adc_b_priv_s *priv;

  if (dev == NULL)
    {
      return -EINVAL;
    }

  priv = (FAR struct ra_adc_b_priv_s *)dev->ad_priv;
  return adc_b_configure_elc_trigger(priv, elc_event);
}

/****************************************************************************
 * Name: ra8_adc_enable_hw_trigger
 ****************************************************************************/

int ra8_adc_enable_hw_trigger(FAR struct adc_dev_s *dev, bool enable)
{
  FAR struct ra_adc_b_priv_s *priv;

  if (dev == NULL)
    {
      return -EINVAL;
    }

  priv = (FAR struct ra_adc_b_priv_s *)dev->ad_priv;

  if (enable)
    {
      return adc_b_enable_hw_trigger(priv);
    }
  else
    {
      adc_b_disable_hw_trigger(priv);
      return OK;
    }
}

/****************************************************************************
 * Name: ra8_adc_read_sync
 ****************************************************************************/

int ra8_adc_read_sync(FAR struct adc_dev_s *dev, uint8_t channel,
                      FAR int32_t *value)
{
  FAR struct ra_adc_b_priv_s *priv;

  if (dev == NULL)
    {
      return -EINVAL;
    }

  priv = (FAR struct ra_adc_b_priv_s *)dev->ad_priv;
  return adc_b_read_sync(priv, channel, value);
}

/****************************************************************************
 * Name: ra8_adc_get_fullcount
 ****************************************************************************/

uint32_t ra8_adc_get_fullcount(FAR struct adc_dev_s *dev)
{
  FAR struct ra_adc_b_priv_s *priv;

  if (dev == NULL)
    {
      return 0;
    }

  priv = (FAR struct ra_adc_b_priv_s *)dev->ad_priv;
  return ADC_B_RESOLUTION_TO_FULLCOUNT(priv->resolution);
}

#endif /* CONFIG_RA_ADC_B */


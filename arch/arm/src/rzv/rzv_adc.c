/*
 * arch/arm/src/rzv/rzv_adc.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 */

#include <nuttx/config.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <nuttx/compiler.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>
#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/semaphore.h>
#include <nuttx/analog/adc.h>
#include <nuttx/analog/ioctl.h>
#include "arm_internal.h"
#include "chip.h"
#include "rzv_clock.h"
#include "hardware/rzv_memorymap.h"
#include "hardware/rzv_adc.h"
/* ICU API for dynamic event -> IRQ routing */
#include "rzv_icu.h"
/* Maximum number of ADC channels */
#define ADC_MAX_CHANNELS        8

/* ADC register bit definitions (map to ADC_E bits) */
#define ADC_ADCSR_ADST          ADC_E_ADCSR_ADST
#define ADC_ADCSR_ADIE          ADC_E_ADCSR_ADIE
#define ADC_ADCER_ADPRC_12BIT   (0x00 << ADC_E_ADCER_ADPRC_SHIFT)  /* 12-bit resolution */

/* ADC Device Hardware Configuration */
struct rzv_adc_config_s
{
  uintptr_t base;         /* ADC base address */
  uint8_t   irq;          /* ADC interrupt number */
  int       elc_event;    /* ELC event number for ICU attachment */
  uint8_t   resolution;   /* ADC resolution (bits) */
};

/* ADC Device Private Data */
struct rzv_adc_priv_s
{
  FAR struct adc_dev_s *dev;          /* ADC device structure */
  const struct adc_callback_s *cb;    /* ADC callbacks */
  const struct rzv_adc_config_s *config; /* Hardware configuration */
  int icu_irq;                        /* Allocated ICU IRQ (RZV_IRQ_FIRST + slot) or -1 */

  sem_t exclsem;                      /* Mutual exclusion semaphore */
  sem_t waitsem;                      /* Wait for conversion complete */

  uint32_t chanmask;                  /* Enabled channel mask */
  uint8_t  nchannels;                 /* Number of enabled channels */
  bool     running;                   /* ADC running flag */
};

/* ADC Register Access (forward declarations) */
static inline uint16_t rzv_adc_getreg(struct rzv_adc_priv_s *priv,
                                      unsigned int offset);
static inline void rzv_adc_putreg(struct rzv_adc_priv_s *priv,
                                  unsigned int offset, uint16_t value);
static inline void rzv_adc_modifyreg(struct rzv_adc_priv_s *priv,
                                     unsigned int offset,
                                     uint16_t clearbits, uint16_t setbits);

/* ADC Helpers (forward) */
static void rzv_adc_reset(struct rzv_adc_priv_s *priv);
static int rzv_adc_interrupt(int irq, void *context, void *arg);

/* ADC Operations (forward) */
static int rzv_adc_bind(struct adc_dev_s *dev,
                        const struct adc_callback_s *callback);
static void rzv_adc_reset_dev(struct adc_dev_s *dev);
static int rzv_adc_setup(struct adc_dev_s *dev);
static void rzv_adc_shutdown(struct adc_dev_s *dev);
static void rzv_adc_rxint(struct adc_dev_s *dev, bool enable);
static int rzv_adc_ioctl(struct adc_dev_s *dev, int cmd, unsigned long arg);

#ifdef CONFIG_RZV_ADC

/* Provide defaults for ADC base addresses if not provided in board headers */
#ifndef RZV_ADC0_BASE
#  define RZV_ADC0_BASE         RZV_ADC_E_BASE
#endif
#ifndef RZV_ADC1_BASE
#  define RZV_ADC1_BASE         RZV_ADC_E_BASE
#endif

static const struct adc_ops_s g_adc_ops =
{
  .ao_bind     = rzv_adc_bind,
  .ao_reset    = rzv_adc_reset_dev,
  .ao_setup    = rzv_adc_setup,
  .ao_shutdown = rzv_adc_shutdown,
  .ao_rxint    = rzv_adc_rxint,
  .ao_ioctl    = rzv_adc_ioctl,
};

/* ADC0 */
static const struct rzv_adc_config_s g_adc0_config =
{
  .base       = RZV_ADC0_BASE,
  .irq        = 0,  /* Legacy IRQ field (unused when elc_event is set) */
  .elc_event  = RZV_ELC_ADC0_ADA_ADELCREQ,
  .resolution = 12,
};

static struct rzv_adc_priv_s g_adc0_priv =
{
  .config = &g_adc0_config,
  .icu_irq = -1,
};

static struct adc_dev_s g_adc0_dev =
{
  .ad_ops  = &g_adc_ops,
  .ad_priv = &g_adc0_priv,
};

/* ADC1 Configuration */

#ifdef CONFIG_RZV_ADC1
/* ADC1 (optional) */
static const struct rzv_adc_config_s g_adc1_config =
{
  .base       = RZV_ADC1_BASE,
  .irq        = 0,
  .resolution = 12,
};

static struct rzv_adc_priv_s g_adc1_priv =
{
  .config = &g_adc1_config,
};

static struct adc_dev_s g_adc1_dev =
{
  .ad_ops  = &g_adc_ops,
  .ad_priv = &g_adc1_priv,
};
#endif

#endif /* CONFIG_RZV_ADC */

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_adc_getreg
 ****************************************************************************/

static inline uint16_t rzv_adc_getreg(struct rzv_adc_priv_s *priv,
                                      unsigned int offset)
{
  return getreg16(priv->config->base + offset);
}

/****************************************************************************
 * Name: rzv_adc_putreg
 ****************************************************************************/

static inline void rzv_adc_putreg(struct rzv_adc_priv_s *priv,
                                  unsigned int offset, uint16_t value)
{
  putreg16(value, priv->config->base + offset);
}

/****************************************************************************
 * Name: rzv_adc_modifyreg
 ****************************************************************************/

static inline void rzv_adc_modifyreg(struct rzv_adc_priv_s *priv,
                                     unsigned int offset,
                                     uint16_t clearbits, uint16_t setbits)
{
  uint16_t regval = rzv_adc_getreg(priv, offset);
  regval &= ~clearbits;
  regval |= setbits;
  rzv_adc_putreg(priv, offset, regval);
}

/****************************************************************************
 * Name: rzv_adc_reset
 ****************************************************************************/
static void rzv_adc_reset(struct rzv_adc_priv_s *priv)
{
  /* Stop any ongoing conversion */
  rzv_adc_modifyreg(priv, RZV_ADC_E_ADCSR_OFFSET, ADC_ADCSR_ADST, 0);

  /* Reset control registers */
  rzv_adc_putreg(priv, RZV_ADC_E_ADCSR_OFFSET, 0);
  rzv_adc_putreg(priv, RZV_ADC_E_ADCER_OFFSET, 0);
  rzv_adc_putreg(priv, RZV_ADC_E_ADSTRGR_OFFSET, 0);

  /* Clear channel selections */
  rzv_adc_putreg(priv, RZV_ADC_E_ADANSA0_OFFSET, 0);

  /* Reset addition/average */
  rzv_adc_putreg(priv, RZV_ADC_E_ADADC_OFFSET, 0);
  rzv_adc_putreg(priv, RZV_ADC_E_ADADS0_OFFSET, 0);

  priv->running = false;
}

static int rzv_adc_interrupt(int irq, void *context, void *arg)
{
  struct rzv_adc_priv_s *priv = (struct rzv_adc_priv_s *)arg;
  struct adc_msg_s msg;
  unsigned int offset;
  int i;

  DEBUGASSERT(priv != NULL && priv->dev != NULL && priv->cb != NULL);

  /* Read converted values for each enabled channel */
  for (i = 0; i < ADC_MAX_CHANNELS; i++)
    {
      if ((priv->chanmask & (1 << i)) != 0)
        {
          /* Read conversion result from ADDR register */
          offset = RZV_ADC_E_ADDR_OFFSET(i);
          msg.am_channel = i;
          msg.am_data = rzv_adc_getreg(priv, offset);
          priv->cb->au_receive(priv->dev, msg.am_channel, msg.am_data);
        }
    }

  /* Signal completion */
  nxsem_post(&priv->waitsem);

  return OK;
}

static int rzv_adc_bind(struct adc_dev_s *dev,
                        const struct adc_callback_s *callback)
{
  struct rzv_adc_priv_s *priv = (struct rzv_adc_priv_s *)dev->ad_priv;

  DEBUGASSERT(priv != NULL);
  priv->dev = dev;
  priv->cb = callback;
  return OK;
}

static void rzv_adc_reset_dev(struct adc_dev_s *dev)
{
  struct rzv_adc_priv_s *priv = (struct rzv_adc_priv_s *)dev->ad_priv;
  irqstate_t flags;

  flags = enter_critical_section();
  rzv_adc_reset(priv);
  leave_critical_section(flags);
}

static int rzv_adc_setup(struct adc_dev_s *dev)
{
  struct rzv_adc_priv_s *priv = (struct rzv_adc_priv_s *)dev->ad_priv;
  int ret;

  /* Initialize semaphores */
  nxsem_init(&priv->exclsem, 0, 1);
  nxsem_init(&priv->waitsem, 0, 0);

  /* Reset ADC */
  rzv_adc_reset(priv);

  /* Configure resolution (12-bit) */
  rzv_adc_putreg(priv, RZV_ADC_E_ADCER_OFFSET, ADC_ADCER_ADPRC_12BIT);

  /* Attach interrupt handler */
  /* Prefer dynamic ICU attachment via ELC event if provided */
  if (priv->config->elc_event >= 0)
    {
      int icu = rzv_icu_attach(priv->config->elc_event,
                               (xcpt_t)rzv_adc_interrupt,
                               priv, true);
      if (icu < 0)
        {
          aerr("ERROR: rzv_icu_attach failed: %d\n", icu);
          return icu;
        }

      priv->icu_irq = icu;
    }
  else if (priv->config->irq)
    {
      /* Fallback to legacy IRQ attach */
      ret = irq_attach(priv->config->irq, rzv_adc_interrupt, priv);
      if (ret < 0)
        {
          aerr("ERROR: Failed to attach ADC interrupt: %d\n", ret);
          return ret;
        }

      up_enable_irq(priv->config->irq);
    }

  ainfo("ADC setup complete\n");
  return OK;
}

static void rzv_adc_shutdown(struct adc_dev_s *dev)
{
  struct rzv_adc_priv_s *priv = (struct rzv_adc_priv_s *)dev->ad_priv;

  /* Disable and detach interrupt */
  if (priv->icu_irq >= 0)
    {
      rzv_icu_detach(priv->icu_irq);
      priv->icu_irq = -1;
    }
  else if (priv->config->irq)
    {
      up_disable_irq(priv->config->irq);
      irq_detach(priv->config->irq);
    }

  /* Reset ADC */
  rzv_adc_reset(priv);

  /* Destroy semaphores */
  nxsem_destroy(&priv->exclsem);
  nxsem_destroy(&priv->waitsem);

  ainfo("ADC shutdown complete\n");
}

static void rzv_adc_rxint(struct adc_dev_s *dev, bool enable)
{
  struct rzv_adc_priv_s *priv = (struct rzv_adc_priv_s *)dev->ad_priv;

  if (enable)
    {
      /* Enable Group A scan end interrupt (ADIE bit) */
      rzv_adc_modifyreg(priv, RZV_ADC_E_ADCSR_OFFSET, 0, ADC_ADCSR_ADIE);
    }
  else
    {
      /* Disable Group A scan end interrupt */
      rzv_adc_modifyreg(priv, RZV_ADC_E_ADCSR_OFFSET, ADC_ADCSR_ADIE, 0);
    }
}

static int rzv_adc_ioctl(struct adc_dev_s *dev, int cmd, unsigned long arg)
{
  struct rzv_adc_priv_s *priv = (struct rzv_adc_priv_s *)dev->ad_priv;
  int ret = OK;

  switch (cmd)
    {
      case ANIOC_TRIGGER:
        {
          /* Start A/D conversion */
          rzv_adc_modifyreg(priv, RZV_ADC_E_ADCSR_OFFSET, 0, ADC_ADCSR_ADST);
          priv->running = true;
        }
        break;

      case ANIOC_GET_NCHANNELS:
        {
          /* Return number of ADC channels */
          ret = ADC_MAX_CHANNELS;
        }
        break;

      default:
        aerr("ERROR: Unknown command: %d\n", cmd);
        ret = -ENOTTY;
        break;
    }

  return ret;
}

int rzv_adc_initialize(const char *devpath, const uint8_t *chanlist,
                      int nchannels)
{
  struct adc_dev_s *dev;
  struct rzv_adc_priv_s *priv;
  uint32_t chanmask = 0;
  int ret;
  int i;

#ifdef CONFIG_RZV_ADC0
  dev = &g_adc0_dev;
  priv = &g_adc0_priv;
#else
  return -ENODEV;
#endif

  /* Validate number of channels */
  if (nchannels < 1 || nchannels > ADC_MAX_CHANNELS)
    {
      aerr("ERROR: Invalid number of channels: %d\n", nchannels);
      return -EINVAL;
    }

  /* Build channel mask */
  for (i = 0; i < nchannels; i++)
    {
      if (chanlist[i] >= ADC_MAX_CHANNELS)
        {
          aerr("ERROR: Invalid channel number: %d\n", chanlist[i]);
          return -EINVAL;
        }

      chanmask |= (1 << chanlist[i]);
    }

  priv->chanmask = chanmask;
  priv->nchannels = nchannels;

  /* Configure channel selection - RZV2H ADC_E only supports 8 channels (0-7) */
  if (chanmask & 0xFF)
    {
      rzv_adc_putreg(priv, RZV_ADC_E_ADANSA0_OFFSET, chanmask & 0xFF);
    }

  /* Register ADC device */
  ret = adc_register(devpath, dev);
  if (ret < 0)
    {
      aerr("ERROR: Failed to register ADC device: %d\n", ret);
      return ret;
    }

  ainfo("ADC initialized: %s (channels=0x%08lx)\n", devpath, (unsigned long)chanmask);
  return OK;
}
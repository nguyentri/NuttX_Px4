/****************************************************************************
 * arch/arm/src/rzv/rzv_adc.c
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
#include "rzv_adc.h"
#include "hardware/rzv_adc.h"
#include "hardware/rzv_sysc.h"
/* ICU API for dynamic event -> IRQ routing */
#include "rzv_icu.h"
/* ADC register bit definitions (map to ADC_E bits) */
#define ADC_ADCSR_ADST          ADC_E_ADCSR_ADST
#define ADC_ADCSR_ADIE          ADC_E_ADCSR_ADIE
#define ADC_ADCER_ADPRC_12BIT   (0x00 << ADC_E_ADCER_ADPRC_SHIFT)  /* 12-bit resolution */

/* ADC Device Hardware Configuration */
struct rzv_adc_config_s
{
  uintptr_t base;         /* ADC base address */
  int       elc_event;    /* ELC event number for ICU attachment */
  uint8_t   resolution;   /* ADC resolution (bits) */
  uint32_t  clk;          /* CPG clock identifier (RZV_CPG_CLK_ADCx) */
};

/* ADC Device Private Data */
struct rzv_adc_priv_s
{
  FAR struct adc_dev_s *dev;          /* ADC device structure */
  const struct adc_callback_s *cb;    /* ADC callbacks */
  const struct rzv_adc_config_s *config; /* Hardware configuration */
  int icu_irq;                        /* Allocated ICU IRQ or -1 */

  sem_t exclsem;                      /* Trigger serialization */

  uint32_t chanmask;                  /* Enabled channel mask */
  uint8_t  nchannels;                 /* Number of enabled channels */
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
#ifdef CONFIG_RZV_ADC0
static void rzv_adc_reset(struct rzv_adc_priv_s *priv);
static int rzv_adc_interrupt(int irq, void *context, void *arg);
#endif

/* ADC Operations (forward) */
#ifdef CONFIG_RZV_ADC0
static int rzv_adc_bind(struct adc_dev_s *dev,
                        const struct adc_callback_s *callback);
static void rzv_adc_reset_dev(struct adc_dev_s *dev);
static int rzv_adc_setup(struct adc_dev_s *dev);
static void rzv_adc_shutdown(struct adc_dev_s *dev);
static void rzv_adc_rxint(struct adc_dev_s *dev, bool enable);
static int rzv_adc_ioctl(struct adc_dev_s *dev, int cmd, unsigned long arg);
#endif


#ifdef CONFIG_RZV_ADC

/* Provide defaults for ADC base addresses if not provided in board headers */
#ifndef RZV_ADC0_BASE
#  define RZV_ADC0_BASE         RZV_ADC_E_BASE
#endif

/* Define operations only if at least one ADC instance is enabled */
#ifdef CONFIG_RZV_ADC0
static const struct adc_ops_s g_adc_ops =
{
  .ao_bind     = rzv_adc_bind,
  .ao_reset    = rzv_adc_reset_dev,
  .ao_setup    = rzv_adc_setup,
  .ao_shutdown = rzv_adc_shutdown,
  .ao_rxint    = rzv_adc_rxint,
  .ao_ioctl    = rzv_adc_ioctl,
};
#endif

#ifdef CONFIG_RZV_ADC0
/* ADC0 */
static const struct rzv_adc_config_s g_adc0_config =
{
  .base       = RZV_ADC0_BASE,
  .elc_event  = RZV_ELC_ADC0_ADA_ADELCREQ,
  .resolution = 12,
  .clk        = RZV_CPG_CLK_ADC0,
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
#endif

/* NOTE: RZ/V2H has a single ADC_E instance. No ADC1 block is defined here
 * until a second physical instance exists.
 */

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

#ifdef CONFIG_RZV_ADC0
/****************************************************************************
 * Name: rzv_adc_reset
 ****************************************************************************/
static void rzv_adc_reset(struct rzv_adc_priv_s *priv)
{
  /* Stop any ongoing conversion before touching other registers */
  rzv_adc_modifyreg(priv, RZV_ADC_E_ADCSR_OFFSET, ADC_ADCSR_ADST, 0);

  /* Reset control / trigger registers */
  rzv_adc_putreg(priv, RZV_ADC_E_ADCSR_OFFSET, 0);
  rzv_adc_putreg(priv, RZV_ADC_E_ADCER_OFFSET, 0);
  rzv_adc_putreg(priv, RZV_ADC_E_ADSTRGR_OFFSET, 0);

  /* Clear channel selections for all groups */
  rzv_adc_putreg(priv, RZV_ADC_E_ADANSA0_OFFSET, 0);
  rzv_adc_putreg(priv, RZV_ADC_E_ADANSB0_OFFSET, 0);
  rzv_adc_putreg(priv, RZV_ADC_E_ADANSC0_OFFSET, 0);

  /* Reset addition/average */
  rzv_adc_putreg(priv, RZV_ADC_E_ADADC_OFFSET, 0);
  rzv_adc_putreg(priv, RZV_ADC_E_ADADS0_OFFSET, 0);

  /* Disable group priority and compare windows; clear ELC output gating.
   * If a previous owner (bootloader, prior firmware) left these enabled,
   * scan behavior on reopen would be undefined.
   */

  rzv_adc_putreg(priv, RZV_ADC_E_ADGSPCR_OFFSET, 0);
  rzv_adc_putreg(priv, RZV_ADC_E_ADCMPCR_OFFSET, 0);
  rzv_adc_putreg(priv, RZV_ADC_E_ADELCCR_OFFSET, 0);
}

static int rzv_adc_interrupt(int irq, void *context, void *arg)
{
  struct rzv_adc_priv_s *priv = (struct rzv_adc_priv_s *)arg;
  unsigned int offset;
  int i;

  DEBUGASSERT(priv != NULL && priv->dev != NULL);

  /* No ADREF.ADF software ack needed: ADF is RO and tracks ADST; the
   * scan-end edge is delivered via ELC->ICU->GIC and acknowledged at GIC
   * EOI by the NuttX dispatcher.
   */

  /* If userspace has not bound a callback yet, mask further interrupts and
   * bail.  Without this guard the next conversion would NULL-deref cb.
   */

  if (priv->cb == NULL || priv->cb->au_receive == NULL)
    {
      rzv_adc_modifyreg(priv, RZV_ADC_E_ADCSR_OFFSET, ADC_ADCSR_ADIE, 0);
      return OK;
    }

  /* Deliver every enabled channel result. Walk the channel mask, not the
   * full 0..RZV_ADC_MAX_CHANNELS range, so disabled-channel results are not
   * fabricated from stale ADDR shadows.
   */

  for (i = 0; i < RZV_ADC_MAX_CHANNELS; i++)
    {
      if ((priv->chanmask & (1u << i)) != 0)
        {
          offset = RZV_ADC_E_ADDR_OFFSET(i);
          priv->cb->au_receive(priv->dev, i, rzv_adc_getreg(priv, offset));
        }
    }

  return OK;
}
#endif

#ifdef CONFIG_RZV_ADC0
static int rzv_adc_bind(struct adc_dev_s *dev,
                        const struct adc_callback_s *callback)
{
  struct rzv_adc_priv_s *priv = (struct rzv_adc_priv_s *)dev->ad_priv;

  DEBUGASSERT(priv != NULL);
  priv->dev = dev;

  /* Publish callback pointer with a barrier so the ISR (potentially on
   * another CPU under SMP / weakly-ordered ARMv8-R) never observes a
   * partially-initialized cb after seeing cb != NULL.
   */

  __sync_synchronize();
  priv->cb = callback;
  __sync_synchronize();
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
  int icu;

  /* Clock is already gated on in rzv_adc_initialize(); MMIO is safe. */

  rzv_adc_reset(priv);

  /* 12-bit resolution and enable channel mask now that device is open. */

  rzv_adc_putreg(priv, RZV_ADC_E_ADCER_OFFSET, ADC_ADCER_ADPRC_12BIT);
  rzv_adc_putreg(priv, RZV_ADC_E_ADANSA0_OFFSET, priv->chanmask & 0xff);

  /* Route the ADC scan-end ELC event through the ICU to a GIC SPI. */

  icu = rzv_icu_attach(priv->config->elc_event,
                       rzv_adc_interrupt, priv, true);
  if (icu < 0)
    {
      aerr("ERROR: rzv_icu_attach failed: %d\n", icu);
      return icu;
    }

  priv->icu_irq = icu;

  ainfo("ADC setup complete\n");
  return OK;
}

static void rzv_adc_shutdown(struct adc_dev_s *dev)
{
  struct rzv_adc_priv_s *priv = (struct rzv_adc_priv_s *)dev->ad_priv;

  /* Mask the scan-end interrupt and stop any conversion in flight BEFORE
   * tearing down the ICU/GIC routing — otherwise a late edge could fire
   * after detach with a stale handler.
   */

  rzv_adc_modifyreg(priv, RZV_ADC_E_ADCSR_OFFSET,
                    ADC_ADCSR_ADIE | ADC_ADCSR_ADST, 0);
  rzv_adc_putreg(priv, RZV_ADC_E_ADANSA0_OFFSET, 0);

  if (priv->icu_irq >= 0)
    {
      rzv_icu_detach(priv->icu_irq);
      priv->icu_irq = -1;
    }

  rzv_adc_reset(priv);

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
          ret = nxsem_wait_uninterruptible(&priv->exclsem);
          if (ret < 0)
            {
              break;
            }

          /* If a conversion is already in flight, refuse rather than racing
           * the hardware. ADST self-clears on completion.
           */

          if ((rzv_adc_getreg(priv, RZV_ADC_E_ADCSR_OFFSET) &
               ADC_ADCSR_ADST) != 0)
            {
              ret = -EBUSY;
            }
          else
            {
              rzv_adc_modifyreg(priv, RZV_ADC_E_ADCSR_OFFSET, 0,
                                ADC_ADCSR_ADST);
            }

          nxsem_post(&priv->exclsem);
        }
        break;

      case ANIOC_GET_NCHANNELS:
        ret = priv->nchannels;
        break;

      default:
        aerr("ERROR: Unknown command: %d\n", cmd);
        ret = -ENOTTY;
        break;
    }

  return ret;
}
#endif

int rzv_adc_initialize(const char *devpath, const uint8_t *chanlist,
                      int nchannels)
{
#ifdef CONFIG_RZV_ADC0
  struct adc_dev_s *dev = &g_adc0_dev;
  struct rzv_adc_priv_s *priv = &g_adc0_priv;
  uint32_t chanmask = 0;
  int ret;
  int i;

  if (nchannels < 1 || nchannels > RZV_ADC_MAX_CHANNELS)
    {
      aerr("ERROR: Invalid number of channels: %d\n", nchannels);
      return -EINVAL;
    }

  for (i = 0; i < nchannels; i++)
    {
      if (chanlist[i] >= RZV_ADC_MAX_CHANNELS)
        {
          aerr("ERROR: Invalid channel number: %d\n", chanlist[i]);
          return -EINVAL;
        }

      chanmask |= (1u << chanlist[i]);
    }

  priv->chanmask = chanmask;
  priv->nchannels = nchannels;

  /* Gate the ADC module clock ON before any other MMIO touches the block.
   * Upper-half adc_register() will call ao_reset() during registration,
   * which writes ADCSR/ADCER/etc. — without the clock those writes bus
   * fault.
   *
   * Use rzv_clock_enable() rather than the deprecated single-bit
   * RZV_MODULE_CLKON macro: the RZ/V2H ADC gate requires BOTH CPG clock
   * bits [8:7], which only the C path sets and monitors (see the ADC
   * branch in rzv_clock_enable()).  The macro drives/monitors one bit
   * only, leaving the block half-clocked.
   */

  ret = rzv_clock_enable(priv->config->clk);
  if (ret < 0)
    {
      aerr("ERROR: Failed to enable ADC clock: %d\n", ret);
      return ret;
    }

  ret = rzv_module_unreset(priv->config->clk);
  if (ret < 0)
    {
      aerr("ERROR: Failed to release ADC reset: %d\n", ret);
      return ret;
    }

  putreg32(getreg32(RZV_SYSC_SYS_ADC_CFG) & ~SYSC_SYS_ADC_CFG_sy_mstp_ada,
           RZV_SYSC_SYS_ADC_CFG);
  up_udelay(20);

  /* One-shot semaphore init (ao_setup/ao_shutdown may be invoked multiple
   * times across open/close; the semaphore must persist).
   */

  nxsem_init(&priv->exclsem, 0, 1);

  ret = adc_register(devpath, dev);
  if (ret < 0)
    {
      aerr("ERROR: Failed to register ADC device: %d\n", ret);
      nxsem_destroy(&priv->exclsem);
      return ret;
    }

  ainfo("ADC initialized: %s (channels=0x%08lx)\n", devpath,
        (unsigned long)chanmask);
  return OK;
#else
  UNUSED(devpath);
  UNUSED(chanlist);
  UNUSED(nchannels);
  return -ENODEV;
#endif
}

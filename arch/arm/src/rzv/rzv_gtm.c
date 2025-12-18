/****************************************************************************
 * arch/arm/src/rzv/rzv_gtm.c
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
#include <errno.h>

#include <nuttx/irq.h>
#include <stddef.h>
#include "chip.h"
#include <nuttx/arch.h>

#include "arm_internal.h"

#include "hardware/rzv_gtm.h"
#include "rzv_icu.h"
#include "../../include/rzv/rzv2h_irq.h"

/* Small helpers for register access to match platform conventions */
static inline uint32_t rzv_gtm_getreg32(uintptr_t base, unsigned int offset)
{

#ifndef getreg32
#  define getreg32(a)    (*(volatile uint32_t *)(a))
#endif

  return getreg32(base + offset);
}

static inline void rzv_gtm_putreg32(uint32_t val, uintptr_t base, unsigned int offset)
{

#ifndef putreg32
#  define putreg32(v,a)  (*(volatile uint32_t *)(a) = (v))
#endif

  putreg32(val, base + offset);
}

static inline uintptr_t rzv_gtm_base(int ch)
{
	switch (ch)
		{
			case 0: return RZV_GTM0_BASE;
			case 1: return RZV_GTM1_BASE;
			case 2: return RZV_GTM2_BASE;
			case 3: return RZV_GTM3_BASE;
			case 4: return RZV_GTM4_BASE;
			case 5: return RZV_GTM5_BASE;
			case 6: return RZV_GTM6_BASE;
			case 7: return RZV_GTM7_BASE;
			default: return 0;
		}
}

/* Per-channel control structure */
struct rzv_gtm_priv_s
{
	int channel;
	int irq; /* allocated ICU IRQ slot (RZV IRQ number) or -1 */

	/* Handler signature matches NuttX IRQ handlers used elsewhere: int handler(int, void*, void*) */
	int (*handler)(int, void *, void *);
	void *arg;      /* handler argument */
};

/* Static instances for channels */
static struct rzv_gtm_priv_s g_gtm_priv[RZV_GTM_MAX_CHANNELS] =
{
	{ .channel = 0, .irq = -1, .handler = NULL, .arg = NULL },
	{ .channel = 1, .irq = -1, .handler = NULL, .arg = NULL },
	{ .channel = 2, .irq = -1, .handler = NULL, .arg = NULL },
	{ .channel = 3, .irq = -1, .handler = NULL, .arg = NULL },
	{ .channel = 4, .irq = -1, .handler = NULL, .arg = NULL },
	{ .channel = 5, .irq = -1, .handler = NULL, .arg = NULL },
	{ .channel = 6, .irq = -1, .handler = NULL, .arg = NULL },
	{ .channel = 7, .irq = -1, .handler = NULL, .arg = NULL },
};

/* Forward declarations */
static int rzv_gtm_handler(int irq, void *context, void *arg);
static int rzv_gtm_attach_irq(struct rzv_gtm_priv_s *priv);
static void rzv_gtm_detach_irq(struct rzv_gtm_priv_s *priv);

/* Map channel to ELC event constant */
static int rzv_gtm_event_for_channel(int ch)
{
	switch (ch)
		{
			case 0: return RZV_ELC_GTM0_GTMTINT;
			case 1: return RZV_ELC_GTM1_GTMTINT;
			case 2: return RZV_ELC_GTM2_GTMTINT;
			case 3: return RZV_ELC_GTM3_GTMTINT;
			case 4: return RZV_ELC_GTM4_GTMTINT;
			case 5: return RZV_ELC_GTM5_GTMTINT;
			case 6: return RZV_ELC_GTM6_GTMTINT;
			case 7: return RZV_ELC_GTM7_GTMTINT;
			default: return -EINVAL;
		}
}

/* IRQ handler invoked by ICU for GTM events */
static int rzv_gtm_handler(int irq, void *context, void *arg)
{
	struct rzv_gtm_priv_s *priv = (struct rzv_gtm_priv_s *)arg;
	/* Clear ICU IRQ state for this allocated slot */
	rzv_icu_clear_irq(irq);

	/* If user provided a handler, call it. We pass the stored arg. */
	if (priv->handler)
		{
			priv->handler(irq, context, priv->arg);
		}

		return 0;
}

static int rzv_gtm_attach_irq(struct rzv_gtm_priv_s *priv)
{
	int evt = rzv_gtm_event_for_channel(priv->channel);
	int ret;

	if (evt < 0)
		return -EINVAL;

	/* Attach using rzv_icu_attach(event, handler, arg, enable) */
	ret = rzv_icu_attach(evt, rzv_gtm_handler, priv, true);
	if (ret < 0)
		{
			return ret;
		}

		priv->irq = ret;
		return 0;
}

static void rzv_gtm_detach_irq(struct rzv_gtm_priv_s *priv)
{
	if (priv->irq >= 0)
		{
			rzv_icu_detach(priv->irq);
			priv->irq = -1;
		}
}

/* Public simplified API: initialize a channel and register a handler */
int rzv_gtm_init_channel(int ch, int (*handler)(int, void *, void *), void *arg)
{
	struct rzv_gtm_priv_s *priv;

	if (ch < 0 || ch >= RZV_GTM_MAX_CHANNELS)
		return -EINVAL;

	priv = &g_gtm_priv[ch];
	priv->handler = handler;
	priv->arg = arg;

		/* Stop timer and attach ICU IRQ */
		{
			uintptr_t base = rzv_gtm_base(priv->channel);
			if (!base)
				return -EINVAL;
			rzv_gtm_putreg32(GTM_OSTMTT_OSTMTT, base, RZV_GTM_OSTMTT_OFFSET);
		}
		return rzv_gtm_attach_irq(priv);
}

int rzv_gtm_deinit_channel(int ch)
{
	struct rzv_gtm_priv_s *priv;

	if (ch < 0 || ch >= RZV_GTM_MAX_CHANNELS)
		return -EINVAL;

	priv = &g_gtm_priv[ch];
	rzv_gtm_detach_irq(priv);
	priv->handler = NULL;
	priv->arg = NULL;
		return 0;
}

/* Basic timer control helpers using OSTM registers */
int rzv_gtm_set_period(int ch, uint32_t period)
{
	if (ch < 0 || ch >= RZV_GTM_MAX_CHANNELS)
		return -EINVAL;
	uintptr_t base = rzv_gtm_base(ch);
	if (!base)
		return -EINVAL;
	rzv_gtm_putreg32(period & GTM_OSTMCMP_MASK, base, RZV_GTM_OSTMCMP_OFFSET);
		return 0;
}

int rzv_gtm_start(int ch)
{
	if (ch < 0 || ch >= RZV_GTM_MAX_CHANNELS)
		return -EINVAL;
	uintptr_t base = rzv_gtm_base(ch);
	if (!base)
		return -EINVAL;
	rzv_gtm_putreg32(GTM_OSTMTS_OSTMTS, base, RZV_GTM_OSTMTS_OFFSET);
		return 0;
}

int rzv_gtm_stop(int ch)
{
	if (ch < 0 || ch >= RZV_GTM_MAX_CHANNELS)
		return -EINVAL;
	uintptr_t base = rzv_gtm_base(ch);
	if (!base)
		return -EINVAL;
	rzv_gtm_putreg32(GTM_OSTMTT_OSTMTT, base, RZV_GTM_OSTMTT_OFFSET);
		return 0;
}

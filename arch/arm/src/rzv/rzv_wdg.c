/****************************************************************************
 * arch/arm/src/rzv/rzv_wdt.c
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

#include <stdint.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/clock.h>
#include <nuttx/timers/watchdog.h>

#include "arm_internal.h"
#include "chip.h"
#include "rzv_clock.h"
#include "hardware/rzv_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* WDT Register Offsets *****************************************************/

#define RZV_WDT_WDTCNT_OFFSET     0x00  /* WDT Counter Register */
#define RZV_WDT_WDTSET_OFFSET     0x02  /* WDT Counter Setting Register */
#define RZV_WDT_WDTTIM_OFFSET     0x04  /* WDT Time Setting Register */
#define RZV_WDT_WDTINT_OFFSET     0x06  /* WDT Interrupt Interval Register */
#define RZV_WDT_WDTCNT_U_OFFSET   0x08  /* WDT Counter Upper Byte */
#define RZV_WDT_WDTSET_U_OFFSET   0x0A  /* WDT Counter Setting Upper Byte */

/* WDT Control Register Offsets *********************************************/

#define RZV_WDT_WDTCR_OFFSET      0x10  /* WDT Control Register */
#define RZV_WDT_WDTSR_OFFSET      0x12  /* WDT Status Register */
#define RZV_WDT_WDTRCR_OFFSET     0x14  /* WDT Reset Control Register */

/* WDT Control Register (WDTCR) bit definitions *****************************/

#define WDT_WDTCR_TOPS_SHIFT      (0)       /* Timeout Period Select */
#define WDT_WDTCR_TOPS_MASK       (0x3 << WDT_WDTCR_TOPS_SHIFT)
#  define WDT_WDTCR_TOPS_1024    (0x0 << WDT_WDTCR_TOPS_SHIFT)   /* 1024 cycles */
#  define WDT_WDTCR_TOPS_4096    (0x1 << WDT_WDTCR_TOPS_SHIFT)   /* 4096 cycles */
#  define WDT_WDTCR_TOPS_8192    (0x2 << WDT_WDTCR_TOPS_SHIFT)   /* 8192 cycles */
#  define WDT_WDTCR_TOPS_16384   (0x3 << WDT_WDTCR_TOPS_SHIFT)   /* 16384 cycles */

#define WDT_WDTCR_CKS_SHIFT       (4)       /* Clock Select */
#define WDT_WDTCR_CKS_MASK        (0xF << WDT_WDTCR_CKS_SHIFT)
#  define WDT_WDTCR_CKS_DIV4     (0x2 << WDT_WDTCR_CKS_SHIFT)    /* PCLK/4 */
#  define WDT_WDTCR_CKS_DIV64    (0x4 << WDT_WDTCR_CKS_SHIFT)    /* PCLK/64 */
#  define WDT_WDTCR_CKS_DIV128   (0x5 << WDT_WDTCR_CKS_SHIFT)    /* PCLK/128 */
#  define WDT_WDTCR_CKS_DIV512   (0x7 << WDT_WDTCR_CKS_SHIFT)    /* PCLK/512 */
#  define WDT_WDTCR_CKS_DIV2048  (0x9 << WDT_WDTCR_CKS_SHIFT)    /* PCLK/2048 */
#  define WDT_WDTCR_CKS_DIV8192  (0xB << WDT_WDTCR_CKS_SHIFT)    /* PCLK/8192 */

#define WDT_WDTCR_RPES_SHIFT      (8)       /* Window Period Select */
#define WDT_WDTCR_RPES_MASK       (0x3 << WDT_WDTCR_RPES_SHIFT)
#  define WDT_WDTCR_RPES_25      (0x0 << WDT_WDTCR_RPES_SHIFT)   /* 25% */
#  define WDT_WDTCR_RPES_50      (0x1 << WDT_WDTCR_RPES_SHIFT)   /* 50% */
#  define WDT_WDTCR_RPES_75      (0x2 << WDT_WDTCR_RPES_SHIFT)   /* 75% */
#  define WDT_WDTCR_RPES_100     (0x3 << WDT_WDTCR_RPES_SHIFT)   /* 100% (no window) */

#define WDT_WDTCR_RPSS_SHIFT      (12)      /* Window Start Position Select */
#define WDT_WDTCR_RPSS_MASK       (0x3 << WDT_WDTCR_RPSS_SHIFT)

/* WDT Status Register (WDTSR) bit definitions ******************************/

#define WDT_WDTSR_CNTVAL_MASK     (0x3FFF)  /* Counter Value */
#define WDT_WDTSR_UNDFF           (1 << 14) /* Underflow Flag */
#define WDT_WDTSR_REFEF           (1 << 15) /* Refresh Error Flag */

/* WDT Reset Control Register (WDTRCR) bit definitions **********************/

#define WDT_WDTRCR_RSTIRQS        (1 << 7)  /* Reset Interrupt Request Select */

/* Default timeout values ***************************************************/

#define WDT_MAXTIMEOUT            60000     /* 60 seconds max timeout (ms) */
#define WDT_MINTIMEOUT            1         /* 1 ms min timeout */

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* WDT Device State */

struct rzv_wdt_priv_s
{
  const struct watchdog_ops_s *ops;   /* Standard watchdog operations */
  uintptr_t base;                     /* WDT register base address */
  uint32_t  timeout;                  /* Timeout value (ms) */
  uint32_t  frequency;                /* WDT clock frequency */
  xcpt_t    handler;                  /* Watchdog interrupt handler */
  void      *arg;                     /* Handler argument */
  bool      started;                  /* Watchdog started flag */
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Register access */

static inline uint16_t rzv_wdt_getreg(struct rzv_wdt_priv_s *priv,
                                      unsigned int offset);
static inline void rzv_wdt_putreg(struct rzv_wdt_priv_s *priv,
                                  unsigned int offset, uint16_t value);

/* WDT Operations */

static int rzv_wdt_start(struct watchdog_lowerhalf_s *lower);
static int rzv_wdt_stop(struct watchdog_lowerhalf_s *lower);
static int rzv_wdt_keepalive(struct watchdog_lowerhalf_s *lower);
static int rzv_wdt_getstatus(struct watchdog_lowerhalf_s *lower,
                             struct watchdog_status_s *status);
static int rzv_wdt_settimeout(struct watchdog_lowerhalf_s *lower,
                              uint32_t timeout);
static xcpt_t rzv_wdt_capture(struct watchdog_lowerhalf_s *lower,
                              xcpt_t handler);
static int rzv_wdt_ioctl(struct watchdog_lowerhalf_s *lower,
                         int cmd, unsigned long arg);

/* Interrupt handling */

static int rzv_wdt_interrupt(int irq, void *context, void *arg);

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Watchdog Operations */

static const struct watchdog_ops_s g_wdt_ops =
{
  .start      = rzv_wdt_start,
  .stop       = rzv_wdt_stop,
  .keepalive  = rzv_wdt_keepalive,
  .getstatus  = rzv_wdt_getstatus,
  .settimeout = rzv_wdt_settimeout,
  .capture    = rzv_wdt_capture,
  .ioctl      = rzv_wdt_ioctl,
};

/* WDT0 Device */

#ifdef CONFIG_RZV_WDT0
static struct rzv_wdt_priv_s g_wdt0_priv =
{
  .ops     = &g_wdt_ops,
  .base    = RZV_WDT0_BASE,
  .timeout = CONFIG_RZV_WDT0_TIMEOUT,
  .started = false,
};

static struct watchdog_lowerhalf_s g_wdt0_dev =
{
  .ops = &g_wdt_ops,
};
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_wdt_getreg
 ****************************************************************************/

static inline uint16_t rzv_wdt_getreg(struct rzv_wdt_priv_s *priv,
                                      unsigned int offset)
{
  return getreg16(priv->base + offset);
}

/****************************************************************************
 * Name: rzv_wdt_putreg
 ****************************************************************************/

static inline void rzv_wdt_putreg(struct rzv_wdt_priv_s *priv,
                                  unsigned int offset, uint16_t value)
{
  putreg16(value, priv->base + offset);
}

/****************************************************************************
 * Name: rzv_wdt_settimeout_value
 ****************************************************************************/

static int rzv_wdt_settimeout_value(struct rzv_wdt_priv_s *priv,
                                    uint32_t timeout_ms)
{
  uint32_t pclk;
  uint32_t cycles;
  uint16_t wdtcr;
  uint8_t cks;
  uint8_t tops;
  uint32_t divisor;
  uint32_t timeout_cycles;

  /* Get peripheral clock frequency */
  pclk = rzv_get_pclk_frequency();

  /* Calculate required cycles for timeout */
  cycles = (uint64_t)pclk * timeout_ms / 1000;

  /* Find suitable clock divider and timeout period */
  const uint16_t divisors[] = {4, 64, 128, 512, 2048, 8192};
  const uint8_t cks_values[] =
    {
      WDT_WDTCR_CKS_DIV4, WDT_WDTCR_CKS_DIV64,
      WDT_WDTCR_CKS_DIV128, WDT_WDTCR_CKS_DIV512,
      WDT_WDTCR_CKS_DIV2048, WDT_WDTCR_CKS_DIV8192
    };
  const uint16_t tops_cycles[] = {1024, 4096, 8192, 16384};
  const uint8_t tops_values[] =
    {
      WDT_WDTCR_TOPS_1024, WDT_WDTCR_TOPS_4096,
      WDT_WDTCR_TOPS_8192, WDT_WDTCR_TOPS_16384
    };

  bool found = false;

  for (int i = 0; i < 6 && !found; i++)
    {
      divisor = divisors[i];
      for (int j = 0; j < 4; j++)
        {
          timeout_cycles = (pclk / divisor) * timeout_ms / 1000;
          if (timeout_cycles <= tops_cycles[j])
            {
              cks = cks_values[i];
              tops = tops_values[j];
              found = true;
              break;
            }
        }
    }

  if (!found)
    {
      wderr("ERROR: Cannot achieve timeout %lu ms\n", timeout_ms);
      return -EINVAL;
    }

  /* Configure WDT control register */
  wdtcr = (cks & WDT_WDTCR_CKS_MASK) |
          (tops & WDT_WDTCR_TOPS_MASK) |
          WDT_WDTCR_RPES_100;  /* No window mode */

  rzv_wdt_putreg(priv, RZV_WDT_WDTCR_OFFSET, wdtcr);

  /* Calculate actual timeout */
  priv->frequency = pclk / divisor;
  priv->timeout = timeout_ms;

  wdinfo("Timeout: %lu ms (CKS=%u, TOPS=%u)\n",
         timeout_ms, cks >> WDT_WDTCR_CKS_SHIFT,
         tops >> WDT_WDTCR_TOPS_SHIFT);

  return OK;
}

/****************************************************************************
 * Name: rzv_wdt_start
 ****************************************************************************/

static int rzv_wdt_start(struct watchdog_lowerhalf_s *lower)
{
  struct rzv_wdt_priv_s *priv = (struct rzv_wdt_priv_s *)lower;

  wdinfo("Starting WDT\n");

  /* Reset counter to start counting */
  rzv_wdt_putreg(priv, RZV_WDT_WDTCNT_OFFSET, 0);

  priv->started = true;

  return OK;
}

/****************************************************************************
 * Name: rzv_wdt_stop
 ****************************************************************************/

static int rzv_wdt_stop(struct watchdog_lowerhalf_s *lower)
{
  struct rzv_wdt_priv_s *priv = (struct rzv_wdt_priv_s *)lower;

  wdinfo("Stopping WDT\n");

  /* Note: RZV2H WDT cannot be stopped once started, only refreshed */
  /* This just marks it as stopped in software */

  priv->started = false;

  return OK;
}

/****************************************************************************
 * Name: rzv_wdt_keepalive
 ****************************************************************************/

static int rzv_wdt_keepalive(struct watchdog_lowerhalf_s *lower)
{
  struct rzv_wdt_priv_s *priv = (struct rzv_wdt_priv_s *)lower;

  wdinfo("WDT keepalive\n");

  /* Refresh watchdog by writing to counter register */
  rzv_wdt_putreg(priv, RZV_WDT_WDTCNT_OFFSET, 0);

  return OK;
}

/****************************************************************************
 * Name: rzv_wdt_getstatus
 ****************************************************************************/

static int rzv_wdt_getstatus(struct watchdog_lowerhalf_s *lower,
                             struct watchdog_status_s *status)
{
  struct rzv_wdt_priv_s *priv = (struct rzv_wdt_priv_s *)lower;
  uint16_t wdtsr;
  uint32_t timeleft;

  DEBUGASSERT(status != NULL);

  /* Get status register */
  wdtsr = rzv_wdt_getreg(priv, RZV_WDT_WDTSR_OFFSET);

  /* Return status */
  status->flags = 0;
  if (priv->started)
    {
      status->flags |= WDFLAGS_ACTIVE;
    }

  if (priv->handler)
    {
      status->flags |= WDFLAGS_CAPTURE;
    }

  status->timeout = priv->timeout;

  /* Calculate time left until timeout */
  if (priv->started && priv->frequency > 0)
    {
      uint16_t counter = wdtsr & WDT_WDTSR_CNTVAL_MASK;
      uint16_t wdtcr = rzv_wdt_getreg(priv, RZV_WDT_WDTCR_OFFSET);
      uint16_t tops = (wdtcr & WDT_WDTCR_TOPS_MASK) >>
                      WDT_WDTCR_TOPS_SHIFT;
      uint32_t max_count;

      switch (tops)
        {
          case 0: max_count = 1024; break;
          case 1: max_count = 4096; break;
          case 2: max_count = 8192; break;
          case 3: max_count = 16384; break;
          default: max_count = 1024; break;
        }

      timeleft = ((max_count - counter) * 1000) / priv->frequency;
      status->timeleft = timeleft;
    }
  else
    {
      status->timeleft = 0;
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_wdt_settimeout
 ****************************************************************************/

static int rzv_wdt_settimeout(struct watchdog_lowerhalf_s *lower,
                              uint32_t timeout)
{
  struct rzv_wdt_priv_s *priv = (struct rzv_wdt_priv_s *)lower;

  if (timeout < WDT_MINTIMEOUT || timeout > WDT_MAXTIMEOUT)
    {
      wderr("ERROR: Timeout out of range: %lu\n", timeout);
      return -ERANGE;
    }

  wdinfo("Setting timeout: %lu ms\n", timeout);

  return rzv_wdt_settimeout_value(priv, timeout);
}

/****************************************************************************
 * Name: rzv_wdt_capture
 ****************************************************************************/

static xcpt_t rzv_wdt_capture(struct watchdog_lowerhalf_s *lower,
                              xcpt_t handler)
{
  struct rzv_wdt_priv_s *priv = (struct rzv_wdt_priv_s *)lower;
  xcpt_t oldhandler;

  wdinfo("Capture handler: %p\n", handler);

  oldhandler = priv->handler;
  priv->handler = handler;

  return oldhandler;
}

/****************************************************************************
 * Name: rzv_wdt_ioctl
 ****************************************************************************/

static int rzv_wdt_ioctl(struct watchdog_lowerhalf_s *lower,
                         int cmd, unsigned long arg)
{
  /* No special IOCTL commands supported */
  return -ENOTTY;
}

/****************************************************************************
 * Name: rzv_wdt_interrupt
 ****************************************************************************/

static int rzv_wdt_interrupt(int irq, void *context, void *arg)
{
  struct rzv_wdt_priv_s *priv = (struct rzv_wdt_priv_s *)arg;
  uint16_t wdtsr;

  DEBUGASSERT(priv != NULL);

  /* Get and clear status */
  wdtsr = rzv_wdt_getreg(priv, RZV_WDT_WDTSR_OFFSET);

  /* Clear interrupt flags */
  rzv_wdt_putreg(priv, RZV_WDT_WDTSR_OFFSET,
                wdtsr & ~(WDT_WDTSR_UNDFF | WDT_WDTSR_REFEF));

  /* Call user handler if registered */
  if (priv->handler)
    {
      priv->handler(irq, context, priv->arg);
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_wdt_initialize
 ****************************************************************************/

int rzv_wdt_initialize(void)
{
#ifdef CONFIG_RZV_WDT0
  struct rzv_wdt_priv_s *priv = &g_wdt0_priv;
  int ret;

  wdinfo("Initializing WDT0\n");

  /* Set initial timeout */
  ret = rzv_wdt_settimeout_value(priv, priv->timeout);
  if (ret < 0)
    {
      wderr("ERROR: Failed to set timeout: %d\n", ret);
      return ret;
    }

  /* Register the watchdog device */
  ret = watchdog_register("/dev/watchdog0", &g_wdt0_dev);
  if (ret < 0)
    {
      wderr("ERROR: Failed to register watchdog: %d\n", ret);
      return ret;
    }

  return OK;
#else
  return -ENODEV;
#endif
}
/****************************************************************************
 * arch/arm/src/ra8/ra_cac.c
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
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/fs/fs.h>
#include <nuttx/mutex.h>

#include "arm_internal.h"
#include "chip.h"
#include "ra_mstp.h"
#include "ra_icu.h"
#include "ra_cac.h"
#include "hardware/ra_memorymap.h"

#ifdef CONFIG_RA_CAC

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct ra_cac_dev_s
{
  mutex_t lock;           /* Mutex for thread safety */
  int     crefs;          /* Reference count */
  int     irq_ferr;       /* Frequency Error IRQ */
  int     irq_mend;       /* Measurement End IRQ */
  int     irq_ovf;        /* Overflow IRQ */
  volatile uint32_t status; /* Current status flags */
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int     ra_cac_open(struct file *filep);
static int     ra_cac_close(struct file *filep);
static ssize_t ra_cac_read(struct file *filep, char *buffer, size_t buflen);
static ssize_t ra_cac_write(struct file *filep, const char *buffer, size_t buflen);
static int     ra_cac_ioctl(struct file *filep, int cmd, unsigned long arg);
static int     ra_cac_interrupt(int irq, void *context, void *arg);

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct file_operations g_cac_fops =
{
  ra_cac_open,    /* open */
  ra_cac_close,   /* close */
  ra_cac_read,    /* read */
  ra_cac_write,   /* write */
  NULL,           /* seek */
  ra_cac_ioctl,   /* ioctl */
  NULL            /* poll */
};

static struct ra_cac_dev_s g_cac_dev;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_cac_open
 ****************************************************************************/

static int ra_cac_open(struct file *filep)
{
  int ret;

  ret = nxmutex_lock(&g_cac_dev.lock);
  if (ret < 0)
    {
      return ret;
    }

  if (g_cac_dev.crefs == 0)
    {
      /* Enable CAC module */
      ra_mstp_start(R_MSTP_MSTPCRC_CAC);
    }

  g_cac_dev.crefs++;
  nxmutex_unlock(&g_cac_dev.lock);
  return OK;
}

/****************************************************************************
 * Name: ra_cac_close
 ****************************************************************************/

static int ra_cac_close(struct file *filep)
{
  int ret;

  ret = nxmutex_lock(&g_cac_dev.lock);
  if (ret < 0)
    {
      return ret;
    }

  if (g_cac_dev.crefs > 0)
    {
      g_cac_dev.crefs--;
      if (g_cac_dev.crefs == 0)
        {
          /* Disable CAC module */
          /* Note: We might want to keep it running if configured?
             For now, follow standard power saving. */
          ra_mstp_stop(R_MSTP_MSTPCRC_CAC);
        }
    }

  nxmutex_unlock(&g_cac_dev.lock);
  return OK;
}

/****************************************************************************
 * Name: ra_cac_read
 ****************************************************************************/

static ssize_t ra_cac_read(struct file *filep, char *buffer, size_t buflen)
{
  uint32_t status;
  ssize_t ret;

  if (buflen < sizeof(uint32_t))
    {
      return -EINVAL;
    }

  ret = nxmutex_lock(&g_cac_dev.lock);
  if (ret < 0)
    {
      return ret;
    }

  /* Read current hardware status */
  status = getreg8(R_CAC_CASTR);
  /* Combine with accumulated software status */
  status |= g_cac_dev.status;

  nxmutex_unlock(&g_cac_dev.lock);

  memcpy(buffer, &status, sizeof(uint32_t));
  return sizeof(uint32_t);
}

/****************************************************************************
 * Name: ra_cac_write
 ****************************************************************************/

static ssize_t ra_cac_write(struct file *filep, const char *buffer, size_t buflen)
{
  return -ENOSYS;
}

/****************************************************************************
 * Name: ra_cac_ioctl
 ****************************************************************************/

static int ra_cac_ioctl(struct file *filep, int cmd, unsigned long arg)
{
  int ret = OK;
  struct ra_cac_config_s *config;
  uint32_t regval;

  ret = nxmutex_lock(&g_cac_dev.lock);
  if (ret < 0)
    {
      return ret;
    }

  switch (cmd)
    {
      case CACIOC_START:
        /* Enable interrupts */
        regval = getreg8(R_CAC_CAICR);
        regval |= (R_CAC_CAICR_FERRIE | R_CAC_CAICR_MENDIE | R_CAC_CAICR_OVFIE);
        putreg8(regval, R_CAC_CAICR);

        /* Start measurement */
        regval = getreg8(R_CAC_CACR0);
        regval |= R_CAC_CACR0_CFME;
        putreg8(regval, R_CAC_CACR0);
        break;

      case CACIOC_STOP:
        /* Stop measurement */
        regval = getreg8(R_CAC_CACR0);
        regval &= ~R_CAC_CACR0_CFME;
        putreg8(regval, R_CAC_CACR0);
        break;

      case CACIOC_GET_STATUS:
        {
          uint32_t *status = (uint32_t *)((uintptr_t)arg);
          if (status)
            {
              *status = g_cac_dev.status;
              /* Clear status after read? Or let user clear?
                 Usually status is cleared when read or explicitly.
                 Here we return the accumulated status from ISR. */
              g_cac_dev.status = 0;
            }
          else
            {
              ret = -EINVAL;
            }
        }
        break;

      case CACIOC_SET_CONFIG:
        {
          config = (struct ra_cac_config_s *)((uintptr_t)arg);
          if (config)
            {
              /* Ensure measurement is stopped */
              putreg8(0, R_CAC_CACR0);

              /* Set CACR1 */
              regval = 0;
              regval |= (config->meas_edge & 0x3) << R_CAC_CACR1_EDGES_SHIFT;
              regval |= (config->meas_div & 0x3) << R_CAC_CACR1_TCSS_SHIFT;
              regval |= (config->meas_clock & 0x7) << R_CAC_CACR1_FMCS_SHIFT;
              if (config->ref_input_enable)
                {
                  regval |= R_CAC_CACR1_CACREFE;
                }
              putreg8(regval, R_CAC_CACR1);

              /* Set CACR2 */
              regval = 0;
              regval |= (config->ref_digfilter & 0x3) << R_CAC_CACR2_DFS_SHIFT;
              regval |= (config->ref_div & 0x3) << R_CAC_CACR2_RCDS_SHIFT;
              regval |= (config->ref_clock & 0x7) << R_CAC_CACR2_RSCS_SHIFT;
              if (config->ref_use_external) /* RPS bit: 0=Internal, 1=CACREF pin */
                {
                  regval |= R_CAC_CACR2_RPS;
                }
              putreg8(regval, R_CAC_CACR2);

              /* Set Limits */
              putreg16(config->upper_limit, R_CAC_CAULVR);
              putreg16(config->lower_limit, R_CAC_CALLVR);
            }
          else
            {
              ret = -EINVAL;
            }
        }
        break;

      case CACIOC_READ_COUNTER:
        {
          uint16_t *counter = (uint16_t *)((uintptr_t)arg);
          if (counter)
            {
              /* Read the counter buffer register (CACNTBR) */
              *counter = getreg16(R_CAC_CACNTBR);
            }
          else
            {
              ret = -EINVAL;
            }
        }
        break;

      default:
        ret = -ENOTTY;
        break;
    }

  nxmutex_unlock(&g_cac_dev.lock);
  return ret;
}

/****************************************************************************
 * Name: ra_cac_interrupt
 ****************************************************************************/

static int ra_cac_interrupt(int irq, void *context, void *arg)
{
  uint8_t status;
  uint8_t clear = 0;

  status = getreg8(R_CAC_CASTR);

  if (status & R_CAC_CASTR_FERRF)
    {
      g_cac_dev.status |= RA_CAC_STATUS_FERRF;
      clear |= R_CAC_CAICR_FERRFCL;
    }

  if (status & R_CAC_CASTR_MENDF)
    {
      g_cac_dev.status |= RA_CAC_STATUS_MENDF;
      clear |= R_CAC_CAICR_MENDFCL;
    }

  if (status & R_CAC_CASTR_OVFF)
    {
      g_cac_dev.status |= RA_CAC_STATUS_OVFF;
      clear |= R_CAC_CAICR_OVFFCL;
    }

  /* Clear flags */
  if (clear)
    {
      /* Write 1 to clear */
      /* Note: CAICR bits are write-only for clear, read-write for enable.
         We need to preserve enable bits. */
      uint8_t caicr = getreg8(R_CAC_CAICR);
      caicr &= (R_CAC_CAICR_FERRIE | R_CAC_CAICR_MENDIE | R_CAC_CAICR_OVFIE);
      caicr |= clear;
      putreg8(caicr, R_CAC_CAICR);
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_cac_initialize
 ****************************************************************************/

int ra_cac_initialize(void)
{
  int ret;

  /* Initialize the device structure */
  nxmutex_init(&g_cac_dev.lock);
  g_cac_dev.crefs = 0;
  g_cac_dev.status = 0;

  /* Attach Interrupts */
  /* We use the same handler for all events for simplicity,
     but we need to attach to each ELC event. */

  g_cac_dev.irq_ferr = ra_icu_attach(RA_ELC_CAC_FREQUENCY_ERROR, ra_cac_interrupt, &g_cac_dev, true);
  if (g_cac_dev.irq_ferr < 0)
    {
      _err("Failed to attach CAC FERR IRQ: %d\n", g_cac_dev.irq_ferr);
      return g_cac_dev.irq_ferr;
    }

  g_cac_dev.irq_mend = ra_icu_attach(RA_ELC_CAC_MEASUREMENT_END, ra_cac_interrupt, &g_cac_dev, true);
  if (g_cac_dev.irq_mend < 0)
    {
      _err("Failed to attach CAC MEND IRQ: %d\n", g_cac_dev.irq_mend);
      /* Cleanup? */
    }

  g_cac_dev.irq_ovf = ra_icu_attach(RA_ELC_CAC_OVERFLOW, ra_cac_interrupt, &g_cac_dev, true);
  if (g_cac_dev.irq_ovf < 0)
    {
      _err("Failed to attach CAC OVF IRQ: %d\n", g_cac_dev.irq_ovf);
    }

  /* Enable interrupts at NVIC */
  up_enable_irq(g_cac_dev.irq_ferr);
  up_enable_irq(g_cac_dev.irq_mend);
  up_enable_irq(g_cac_dev.irq_ovf);

  /* Register the device */
  ret = register_driver("/dev/cac0", &g_cac_fops, 0666, &g_cac_dev);
  if (ret < 0)
    {
      _err("Failed to register CAC driver: %d\n", ret);
      return ret;
    }

  return OK;
}

#endif /* CONFIG_RA_CAC */

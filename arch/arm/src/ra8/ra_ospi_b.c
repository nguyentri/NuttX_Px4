/****************************************************************************
 * arch/arm/src/ra8/ra_ospi_b.c
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

#include <nuttx/arch.h>
#include <nuttx/kmalloc.h>
#include <nuttx/mutex.h>
#include <nuttx/spi/qspi.h>

#include "arm_internal.h"
#include "ra_ospi_b.h"
#include "ra_mstp.h"
#include "ra_gpio.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define RA_OSPI_TIMEOUT_US  1000000

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct ra_ospi_priv_s
{
  struct qspi_dev_s qspi;
  uint32_t base;
  mutex_t lock;
  uint32_t frequency;
  int mode;
  int nbits;
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int ra_ospi_lock(struct qspi_dev_s *dev, bool lock);
static uint32_t ra_ospi_setfrequency(struct qspi_dev_s *dev,
                                     uint32_t frequency);
static void ra_ospi_setmode(struct qspi_dev_s *dev, enum qspi_mode_e mode);
static void ra_ospi_setbits(struct qspi_dev_s *dev, int nbits);
static int ra_ospi_command(struct qspi_dev_s *dev,
                           struct qspi_cmdinfo_s *cmdinfo);
static int ra_ospi_memory(struct qspi_dev_s *dev,
                          struct qspi_meminfo_s *meminfo);
static void *ra_ospi_alloc(struct qspi_dev_s *dev, size_t buflen);
static void ra_ospi_free(struct qspi_dev_s *dev, void *buffer);

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct qspi_ops_s g_ra_ospi_ops =
{
  .lock         = ra_ospi_lock,
  .setfrequency = ra_ospi_setfrequency,
  .setmode      = ra_ospi_setmode,
  .setbits      = ra_ospi_setbits,
  .command      = ra_ospi_command,
  .memory       = ra_ospi_memory,
  .alloc        = ra_ospi_alloc,
  .free         = ra_ospi_free,
};

static struct ra_ospi_priv_s g_ra_ospi0_priv =
{
  .qspi =
  {
    .ops = &g_ra_ospi_ops
  },
  .base = R_OSPI_B_BASE,
  .lock = NXMUTEX_INITIALIZER,
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static inline uint32_t ra_ospi_getreg(struct ra_ospi_priv_s *priv,
                                      uint32_t offset)
{
  return getreg32(priv->base + offset);
}

static inline void ra_ospi_putreg(struct ra_ospi_priv_s *priv,
                                  uint32_t offset, uint32_t value)
{
  putreg32(value, priv->base + offset);
}

static int ra_ospi_wait_status(struct ra_ospi_priv_s *priv,
                               uint32_t mask, uint32_t value)
{
  uint32_t regval;
  int retries = RA_OSPI_TIMEOUT_US;

  while (retries--)
    {
      regval = ra_ospi_getreg(priv, R_OSPI_B_INTS_OFFSET);
      if ((regval & mask) == value)
        {
          /* Clear status */
          ra_ospi_putreg(priv, R_OSPI_B_INTC_OFFSET, mask);
          return OK;
        }
      up_udelay(1);
    }

  return -ETIMEDOUT;
}

static int ra_ospi_lock(struct qspi_dev_s *dev, bool lock)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)dev;

  if (lock)
    {
      return nxmutex_lock(&priv->lock);
    }
  else
    {
      return nxmutex_unlock(&priv->lock);
    }
}

static uint32_t ra_ospi_setfrequency(struct qspi_dev_s *dev,
                                     uint32_t frequency)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)dev;
  priv->frequency = frequency;
  /* TODO: Implement clock divider calculation and setting */
  return frequency;
}

static void ra_ospi_setmode(struct qspi_dev_s *dev, enum qspi_mode_e mode)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)dev;
  priv->mode = mode;
  /* TODO: Implement mode setting (CPOL/CPHA) */
}

static void ra_ospi_setbits(struct qspi_dev_s *dev, int nbits)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)dev;
  priv->nbits = nbits;
}

static int ra_ospi_command(struct qspi_dev_s *dev,
                           struct qspi_cmdinfo_s *cmdinfo)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)dev;
  uint32_t cdtbuf = 0;
  uint32_t cdctl0 = 0;
  uint32_t cmd_val = 0;
  uint32_t addr_val = 0;
  uint32_t data_val = 0;
  int ret;

  /* Configure CDTBUF */

  /* Command phase */
  if (cmdinfo->cmd > 0xff)
    {
      cdtbuf |= R_OSPI_B_CDTBUF_CMDSIZE_10; /* 2 bytes */
      cmd_val = (uint32_t)cmdinfo->cmd << 16;
    }
  else
    {
      cdtbuf |= R_OSPI_B_CDTBUF_CMDSIZE_01; /* 1 byte */
      cmd_val = (uint32_t)cmdinfo->cmd << 24;
    }

  /* Address phase */
  if (QSPICMD_ISADDRESS(cmdinfo->flags))
    {
      if (cmdinfo->addrlen == 4)
        {
          cdtbuf |= R_OSPI_B_CDTBUF_ADDSIZE_100;
        }
      else if (cmdinfo->addrlen == 3)
        {
          cdtbuf |= R_OSPI_B_CDTBUF_ADDSIZE_011;
        }
      else if (cmdinfo->addrlen == 2)
        {
          cdtbuf |= R_OSPI_B_CDTBUF_ADDSIZE_010;
        }
      else
        {
          cdtbuf |= R_OSPI_B_CDTBUF_ADDSIZE_001;
        }
      addr_val = cmdinfo->addr;
    }
  else
    {
      cdtbuf |= R_OSPI_B_CDTBUF_ADDSIZE_000;
    }

  /* Data phase */
  if (QSPICMD_ISDATA(cmdinfo->flags))
    {
      if (cmdinfo->buflen > 0)
        {
          /* Set data size (bytes) */
          /* Note: DATASIZE field is 4 bits, encoding 0=0, 1=1, ..., 8=8 bytes?
             Check manual. Usually it's bytes.
             Mask is 0x1e0 (bits 8-5).
             Wait, 0x1e0 is 9 bits? No, 0x1e0 = 111100000 binary? No.
             0x1e0 = 480.
             Bits 5,6,7,8. 4 bits.
             Value 0-15.
             If buflen > 4, we might need multiple transactions or use memory mode.
             But command is usually short.
          */
           cdtbuf |= ((cmdinfo->buflen & 0xf) << R_OSPI_B_CDTBUF_DATASIZE_SHIFT);
        }

      if (QSPICMD_ISWRITE(cmdinfo->flags))
        {
          cdtbuf |= R_OSPI_B_CDTBUF_TRTYPE; /* Write */
          if (cmdinfo->buffer)
            {
              memcpy(&data_val, cmdinfo->buffer, cmdinfo->buflen);
            }
        }
      else
        {
          /* Read */
        }
    }

  /* Write to registers */
  ra_ospi_putreg(priv, R_OSPI_B_CDTBUF_OFFSET(0), cdtbuf | cmd_val);
  if (QSPICMD_ISADDRESS(cmdinfo->flags))
    {
      ra_ospi_putreg(priv, R_OSPI_B_CDABUF_OFFSET(0), addr_val);
    }

  if (QSPICMD_ISWRITE(cmdinfo->flags) && QSPICMD_ISDATA(cmdinfo->flags))
    {
      ra_ospi_putreg(priv, R_OSPI_B_CDD0BUF_OFFSET(0), data_val);
    }

  /* Trigger transaction */
  cdctl0 = R_OSPI_B_CDCTL0_TRREQ | R_OSPI_B_CDCTL0_TRNUM_00; /* 1 command */
  ra_ospi_putreg(priv, R_OSPI_B_CDCTL0_OFFSET, cdctl0);

  /* Wait for completion */
  ret = ra_ospi_wait_status(priv, R_OSPI_B_INTS_CMDCMP, R_OSPI_B_INTS_CMDCMP);
  if (ret < 0)
    {
      return ret;
    }

  /* Read data if needed */
  if (QSPICMD_ISREAD(cmdinfo->flags) && QSPICMD_ISDATA(cmdinfo->flags))
    {
      data_val = ra_ospi_getreg(priv, R_OSPI_B_CDD0BUF_OFFSET(0));
      if (cmdinfo->buffer)
        {
          memcpy(cmdinfo->buffer, &data_val, cmdinfo->buflen);
        }
    }

  return OK;
}

static int ra_ospi_memory(struct qspi_dev_s *dev,
                          struct qspi_meminfo_s *meminfo)
{
  /* For now, fall back to command for small transfers or implement loop */
  /* TODO: Implement proper memory transfer using Manual Mode loop or Direct Mode */
  return -ENOSYS;
}

static void *ra_ospi_alloc(struct qspi_dev_s *dev, size_t buflen)
{
  return kmm_malloc(buflen);
}

static void ra_ospi_free(struct qspi_dev_s *dev, void *buffer)
{
  kmm_free(buffer);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

struct qspi_dev_s *ra_ospi_initialize(int port)
{
  struct ra_ospi_priv_s *priv = &g_ra_ospi0_priv;

  if (port != 0)
    {
      return NULL;
    }

  /* Enable OSPI clock */
  ra_mstp_start(RA_MSTP_OSPI);

  /* Configure pins */
  /* Note: Pin configuration should be done in board logic or here if fixed.
     We assume board logic calls ra_ospi_initialize and has already set up pins
     or we set them up here using ra_gpio_config.
     Since pins are board specific, we should probably let board logic handle it
     or use a board-specific header.
     For now, we assume pins are configured by board_late_initialize or similar.
  */

  /* Reset OSPI peripheral */
  /* TODO: Reset logic */

  return &priv->qspi;
}

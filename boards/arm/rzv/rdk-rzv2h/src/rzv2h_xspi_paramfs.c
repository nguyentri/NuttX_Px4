/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_xspi_paramfs.c
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

#ifdef CONFIG_RDK_RZV2H_XSPI_PARAMFS

#include <sys/mount.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <syslog.h>

#include <nuttx/compiler.h>
#include <nuttx/fs/fs.h>
#include <nuttx/mtd/mtd.h>

#include "arm_internal.h"
#include "hardware/rzv_xspi.h"
#include "rdk-rzv2h.h"

#define RZV2H_XSPI_PARAM_DEVPATH       "/dev/xspi_params"
#define RZV2H_XSPI_PARAM_MOUNTPOINT    "/fs"
#define RZV2H_XSPI_PARAM_BASE          0x2fc00000u
#define RZV2H_XSPI_PARAM_SIZE          (4u * 1024u * 1024u)
#define RZV2H_XSPI_PARAM_ERASE_SIZE    4096u
#define RZV2H_XSPI_PARAM_PROG_SIZE     256u
#define RZV2H_XSPI_CMD_TIMEOUT         1000000u

#define XSPI_CMD_WRITE_ENABLE          0x06u
#define XSPI_CMD_READ_STATUS           0x05u
#define XSPI_CMD_SECTOR_ERASE          0x20u
#define XSPI_STATUS_WIP                (1u << 0)
#define XSPI_INTS_ERROR                (XSPI_INTS_BUSERR | XSPI_INTS_CAFAILCS0)

struct rzv2h_xspi_mtd_s
{
  struct mtd_dev_s mtd;
};

static struct rzv2h_xspi_mtd_s g_xspi_param_mtd =
{
  .mtd =
    {
      .name = "rzv2h_xspi_params",
    },
};

static int rzv2h_xspi_wait_cmd(void)
{
  uint32_t timeout = RZV2H_XSPI_CMD_TIMEOUT;

  while (timeout-- > 0)
    {
      uint32_t ints = getreg32(RZV_XSPI_INTS);

      if ((ints & XSPI_INTS_ERROR) != 0)
        {
          putreg32(ints & XSPI_INTS_ERROR, RZV_XSPI_INTS);
          return -EIO;
        }

      if ((ints & XSPI_INTS_CMDCMP) != 0)
        {
          putreg32(XSPI_INTS_CMDCMP, RZV_XSPI_INTS);
          return OK;
        }
    }

  return -ETIMEDOUT;
}

static int rzv2h_xspi_command(uint8_t cmd, uint32_t address,
                              uint8_t addrlen, FAR const uint8_t *tx,
                              FAR uint8_t *rx, size_t len)
{
  uint32_t cdt = ((uint32_t)cmd << XSPI_CDT_CMD_SHIFT);
  uint32_t cdctl = XSPI_CDCTL_TRREQ(0);
  uint32_t data = 0;
  size_t i;

  putreg32(XSPI_INTS_CMDCMP | XSPI_INTS_ERROR, RZV_XSPI_INTS);

  if (addrlen > 0)
    {
      cdt |= ((uint32_t)addrlen << XSPI_CDT_ADDSIZE_SHIFT);
      putreg32(address, RZV_XSPI_CDA);
    }

  if (len > 0)
    {
      if (len > sizeof(uint32_t))
        {
          return -E2BIG;
        }

      cdt |= ((uint32_t)len << XSPI_CDT_DATASIZE_SHIFT);

      if (tx != NULL)
        {
          cdt |= XSPI_CDT_TRTYPE;

          for (i = 0; i < len; i++)
            {
              data |= ((uint32_t)tx[i] << (i * 8));
            }

          putreg32(data, RZV_XSPI_CDD(0));
        }
    }

  putreg32(cdt, RZV_XSPI_CDT);
  putreg32(cdctl, RZV_XSPI_CDCTL(0));

  int ret = rzv2h_xspi_wait_cmd();
  if (ret < 0)
    {
      return ret;
    }

  if (rx != NULL && len > 0)
    {
      data = getreg32(RZV_XSPI_CDD(0));

      for (i = 0; i < len; i++)
        {
          rx[i] = (uint8_t)(data >> (i * 8));
        }
    }

  return OK;
}

static int rzv2h_xspi_wait_ready(void)
{
  uint32_t timeout = RZV2H_XSPI_CMD_TIMEOUT;
  uint8_t status = XSPI_STATUS_WIP;
  int ret;

  while (timeout-- > 0)
    {
      ret = rzv2h_xspi_command(XSPI_CMD_READ_STATUS, 0, 0, NULL,
                               &status, 1);
      if (ret < 0)
        {
          return ret;
        }

      if ((status & XSPI_STATUS_WIP) == 0)
        {
          return OK;
        }
    }

  return -ETIMEDOUT;
}

static int rzv2h_xspi_write_enable(void)
{
  return rzv2h_xspi_command(XSPI_CMD_WRITE_ENABLE, 0, 0, NULL, NULL, 0);
}

static void rzv2h_xspi_enable_memory_write(void)
{
  putreg32(getreg32(RZV_XSPI_BMCFG) | XSPI_BMCFG_WRMD, RZV_XSPI_BMCFG);
  putreg32(XSPI_BMCTL1_PBUFCLR, RZV_XSPI_BMCTL1);
}

static void rzv2h_xspi_push_memory_write(void)
{
  putreg32(XSPI_BMCTL1_MWRPUSH, RZV_XSPI_BMCTL1);
}

static int rzv2h_xspi_erase(FAR struct mtd_dev_s *dev, off_t startblock,
                            size_t nblocks)
{
  size_t i;
  int ret;

  UNUSED(dev);

  if ((startblock + nblocks) >
      (RZV2H_XSPI_PARAM_SIZE / RZV2H_XSPI_PARAM_ERASE_SIZE))
    {
      return -EINVAL;
    }

  for (i = 0; i < nblocks; i++)
    {
      uint32_t offset = (startblock + i) * RZV2H_XSPI_PARAM_ERASE_SIZE;

      ret = rzv2h_xspi_write_enable();
      if (ret < 0)
        {
          return ret;
        }

      ret = rzv2h_xspi_command(XSPI_CMD_SECTOR_ERASE, offset, 3, NULL,
                               NULL, 0);
      if (ret < 0)
        {
          return ret;
        }

      ret = rzv2h_xspi_wait_ready();
      if (ret < 0)
        {
          return ret;
        }
    }

  return nblocks;
}

static ssize_t rzv2h_xspi_bread(FAR struct mtd_dev_s *dev,
                                off_t startblock, size_t nblocks,
                                FAR uint8_t *buffer)
{
  size_t offset = startblock * RZV2H_XSPI_PARAM_PROG_SIZE;
  size_t nbytes = nblocks * RZV2H_XSPI_PARAM_PROG_SIZE;

  UNUSED(dev);

  if ((offset + nbytes) > RZV2H_XSPI_PARAM_SIZE)
    {
      return -EINVAL;
    }

  memcpy(buffer, (FAR const void *)(uintptr_t)(RZV2H_XSPI_PARAM_BASE +
                                               offset), nbytes);
  return nblocks;
}

static ssize_t rzv2h_xspi_bwrite(FAR struct mtd_dev_s *dev,
                                 off_t startblock, size_t nblocks,
                                 FAR const uint8_t *buffer)
{
  size_t offset = startblock * RZV2H_XSPI_PARAM_PROG_SIZE;
  size_t nbytes = nblocks * RZV2H_XSPI_PARAM_PROG_SIZE;
  int ret;

  UNUSED(dev);

  if ((offset + nbytes) > RZV2H_XSPI_PARAM_SIZE)
    {
      return -EINVAL;
    }

  while (nbytes > 0)
    {
      size_t chunk = nbytes > RZV2H_XSPI_PARAM_PROG_SIZE ?
                     RZV2H_XSPI_PARAM_PROG_SIZE : nbytes;

      ret = rzv2h_xspi_write_enable();
      if (ret < 0)
        {
          return ret;
        }

      rzv2h_xspi_enable_memory_write();

      FAR volatile uint8_t *dest =
        (FAR volatile uint8_t *)(uintptr_t)(RZV2H_XSPI_PARAM_BASE + offset);

      for (size_t i = 0; i < chunk; i++)
        {
          dest[i] = buffer[i];
        }

      rzv2h_xspi_push_memory_write();

      ret = rzv2h_xspi_wait_ready();
      if (ret < 0)
        {
          return ret;
        }

      offset += chunk;
      buffer += chunk;
      nbytes -= chunk;
    }

  return nblocks;
}

static ssize_t rzv2h_xspi_read(FAR struct mtd_dev_s *dev, off_t offset,
                               size_t nbytes, FAR uint8_t *buffer)
{
  UNUSED(dev);

  if ((offset + nbytes) > RZV2H_XSPI_PARAM_SIZE)
    {
      return -EINVAL;
    }

  memcpy(buffer, (FAR const void *)(uintptr_t)(RZV2H_XSPI_PARAM_BASE +
                                               offset), nbytes);
  return nbytes;
}

static int rzv2h_xspi_ioctl(FAR struct mtd_dev_s *dev, int cmd,
                            unsigned long arg)
{
  FAR struct mtd_geometry_s *geo;

  switch (cmd)
    {
      case MTDIOC_GEOMETRY:
        geo = (FAR struct mtd_geometry_s *)(uintptr_t)arg;
        if (geo == NULL)
          {
            return -EINVAL;
          }

        geo->blocksize = RZV2H_XSPI_PARAM_PROG_SIZE;
        geo->erasesize = RZV2H_XSPI_PARAM_ERASE_SIZE;
        geo->neraseblocks = RZV2H_XSPI_PARAM_SIZE /
                            RZV2H_XSPI_PARAM_ERASE_SIZE;
        return OK;

      case MTDIOC_BULKERASE:
        return rzv2h_xspi_erase(dev, 0, RZV2H_XSPI_PARAM_SIZE /
                                RZV2H_XSPI_PARAM_ERASE_SIZE);

      default:
        return -ENOTTY;
    }
}

int rzv2h_xspi_paramfs_initialize(void)
{
  int ret;

  g_xspi_param_mtd.mtd.erase = rzv2h_xspi_erase;
  g_xspi_param_mtd.mtd.bread = rzv2h_xspi_bread;
  g_xspi_param_mtd.mtd.bwrite = rzv2h_xspi_bwrite;
  g_xspi_param_mtd.mtd.read = rzv2h_xspi_read;
  g_xspi_param_mtd.mtd.ioctl = rzv2h_xspi_ioctl;

  ret = register_mtddriver(RZV2H_XSPI_PARAM_DEVPATH,
                           &g_xspi_param_mtd.mtd, 0755, NULL);
  if (ret < 0 && ret != -EEXIST)
    {
      syslog(LOG_ERR, "ERROR: register XSPI param MTD failed: %d\n", ret);
      return ret;
    }

  ret = mkdir(RZV2H_XSPI_PARAM_MOUNTPOINT, 0777);
  if (ret < 0 && errno != EEXIST)
    {
      syslog(LOG_ERR, "ERROR: mkdir %s failed: %d\n",
             RZV2H_XSPI_PARAM_MOUNTPOINT, errno);
      return -errno;
    }

  ret = nx_mount(RZV2H_XSPI_PARAM_DEVPATH, RZV2H_XSPI_PARAM_MOUNTPOINT,
                 "littlefs", 0, "autoformat");
  if (ret < 0 && ret != -EBUSY)
    {
      syslog(LOG_ERR, "ERROR: mount XSPI LittleFS failed: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "Mounted XSPI LittleFS params at %s\n",
         RZV2H_XSPI_PARAM_MOUNTPOINT);
  return OK;
}

#endif /* CONFIG_RDK_RZV2H_XSPI_PARAMFS */

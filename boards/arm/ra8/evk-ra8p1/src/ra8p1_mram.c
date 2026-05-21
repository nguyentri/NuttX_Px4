/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_mram.c
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
#include <string.h>
#include <errno.h>
#include <debug.h>
#include <syslog.h>

#include <nuttx/mtd/mtd.h>
#include <nuttx/fs/fs.h>

#ifdef CONFIG_FS_NXFFS
#  include <nuttx/fs/nxffs.h>
#endif

#ifdef CONFIG_FS_SMARTFS
#  include <nuttx/fs/smart.h>
#endif

#ifdef CONFIG_FS_LITTLEFS
#  include <nuttx/fs/littlefs.h>
#endif

#include <arch/board/board.h>
#include "ra_mram.h"
#include "evk-ra8p1.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Device paths for MTD block devices */

#define MRAM_CODE_DEVPATH       "/dev/mtdblock0"
#define MRAM_DATA_DEVPATH       "/dev/mtdblock1"

/* Device path for parameter storage partition */

#define MRAM_PARAM_DEVPATH      "/dev/params"
#define MRAM_PARAM_MOUNTPOINT   "/mnt/params"

/* FTL device for block access to data partition */

#define MRAM_FTL_MINOR          0

/****************************************************************************
 * Private Data
 ****************************************************************************/

#ifdef CONFIG_RA_MRAM
/* Pointers to initialized MTD devices */

static struct mtd_dev_s *g_code_mtd = NULL;
static struct mtd_dev_s *g_data_mtd = NULL;
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_mram_initialize
 *
 * Description:
 *   Initialize the MRAM MTD devices and optionally mount file systems.
 *   This function is called from board_late_initialize() or board_app_initialize()
 *   to set up MRAM storage for OTA updates, bootloader, and parameter storage.
 *
 *   Configuration options:
 *   - CONFIG_RA_MRAM: Enable MRAM driver
 *   - CONFIG_RA_MRAM_CODE: Enable code MRAM partition (for OTA/bootloader)
 *   - CONFIG_RA_MRAM_DATA: Enable data MRAM partition (for parameters)
 *   - CONFIG_RA_MRAM_DATA_NXFFS: Mount data partition with NXFFS
 *   - CONFIG_RA_MRAM_DATA_SMARTFS: Mount data partition with SmartFS
 *   - CONFIG_RA_MRAM_DATA_LITTLEFS: Mount data partition with LittleFS
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 ****************************************************************************/

#ifdef CONFIG_RA_MRAM
int board_mram_initialize(void)
{
  int ret = OK;
#ifdef CONFIG_MTD_PARTITION
  struct mtd_dev_s *mtd_part;
#endif

  syslog(LOG_INFO, "Initializing MRAM storage...\n");

  /* Initialize code MRAM partition */

#ifdef CONFIG_RA_MRAM_CODE
  g_code_mtd = ra_mram_initialize(false);
  if (g_code_mtd == NULL)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize code MRAM\n");
      return -ENODEV;
    }

  syslog(LOG_INFO, "Code MRAM initialized successfully\n");

#ifdef CONFIG_MTD_REGISTRATION
  /* Register code MRAM as MTD device */

  ret = mtd_register(g_code_mtd, MRAM_CODE_DEVPATH);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to register code MRAM: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "Code MRAM registered at %s\n", MRAM_CODE_DEVPATH);
    }
#endif /* CONFIG_MTD_REGISTRATION */

#ifdef CONFIG_RA_MRAM_PROGMEM
  /* Code MRAM is also available via up_progmem_* API for bootloader/OTA */

  syslog(LOG_INFO, "Code MRAM progmem interface enabled for OTA/bootloader\n");
#endif
#endif /* CONFIG_RA_MRAM_CODE */

  /* Initialize data MRAM partition */

#ifdef CONFIG_RA_MRAM_DATA
  g_data_mtd = ra_mram_initialize(true);
  if (g_data_mtd == NULL)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize data MRAM\n");
      return -ENODEV;
    }

  syslog(LOG_INFO, "Data MRAM initialized successfully\n");

#ifdef CONFIG_MTD_REGISTRATION
  /* Register data MRAM as MTD device */

  ret = mtd_register(g_data_mtd, MRAM_DATA_DEVPATH);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to register data MRAM: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "Data MRAM registered at %s\n", MRAM_DATA_DEVPATH);
    }
#endif /* CONFIG_MTD_REGISTRATION */

  /* Set up file system for parameter storage */

#ifdef CONFIG_FS_NXFFS
  /* Initialize NXFFS on data partition */

  ret = nxffs_initialize(g_data_mtd);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize NXFFS: %d\n", ret);
    }
  else
    {
      /* Mount the file system */

      ret = nx_mount(NULL, MRAM_PARAM_MOUNTPOINT, "nxffs", 0, NULL);
      if (ret < 0)
        {
          syslog(LOG_ERR, "ERROR: Failed to mount NXFFS at %s: %d\n",
                 MRAM_PARAM_MOUNTPOINT, ret);
        }
      else
        {
          syslog(LOG_INFO, "NXFFS mounted at %s for parameter storage\n",
                 MRAM_PARAM_MOUNTPOINT);
        }
    }
#endif /* CONFIG_FS_NXFFS */

#ifdef CONFIG_FS_LITTLEFS
  /* Initialize LittleFS on data partition */

  ret = register_mtddriver(MRAM_PARAM_DEVPATH, g_data_mtd, 0, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to register MTD driver: %d\n", ret);
    }
  else
    {
      /* Format if needed - LittleFS will detect if formatted */

      ret = nx_mount(MRAM_PARAM_DEVPATH, MRAM_PARAM_MOUNTPOINT, "littlefs",
                     0, "autoformat");
      if (ret < 0)
        {
          syslog(LOG_ERR, "ERROR: Failed to mount LittleFS at %s: %d\n",
                 MRAM_PARAM_MOUNTPOINT, ret);
        }
      else
        {
          syslog(LOG_INFO, "LittleFS mounted at %s for parameter storage\n",
                 MRAM_PARAM_MOUNTPOINT);
        }
    }
#endif /* CONFIG_FS_LITTLEFS */

#ifdef CONFIG_FS_SMARTFS
  /* Initialize SmartFS on data partition */

  ret = smart_initialize(MRAM_FTL_MINOR, g_data_mtd, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize SmartFS: %d\n", ret);
    }
  else
    {
      char devpath[32];
      snprintf(devpath, sizeof(devpath), "/dev/smart%d", MRAM_FTL_MINOR);

      /* Mount the file system */

      ret = nx_mount(devpath, MRAM_PARAM_MOUNTPOINT, "smartfs", 0, NULL);
      if (ret < 0)
        {
          /* Try to format and mount */

          syslog(LOG_WARNING, "SmartFS mount failed, attempting format...\n");

          ret = nx_mount(devpath, MRAM_PARAM_MOUNTPOINT, "smartfs", 0,
                         "forceformat");
          if (ret < 0)
            {
              syslog(LOG_ERR, "ERROR: Failed to format/mount SmartFS: %d\n",
                     ret);
            }
        }

      if (ret >= 0)
        {
          syslog(LOG_INFO, "SmartFS mounted at %s for parameter storage\n",
                 MRAM_PARAM_MOUNTPOINT);
        }
    }
#endif /* CONFIG_FS_SMARTFS */

#endif /* CONFIG_RA_MRAM_DATA */

  return ret;
}
#endif /* CONFIG_RA_MRAM */

/****************************************************************************
 * Name: board_get_code_mram
 *
 * Description:
 *   Get the code MRAM MTD device for direct access.
 *   Used by OTA and bootloader components.
 *
 * Returned Value:
 *   Pointer to MTD device or NULL if not initialized
 *
 ****************************************************************************/

#ifdef CONFIG_RA_MRAM_CODE
struct mtd_dev_s *board_get_code_mram(void)
{
  return g_code_mtd;
}
#endif

/****************************************************************************
 * Name: board_get_data_mram
 *
 * Description:
 *   Get the data MRAM MTD device for direct access.
 *   Used by parameter storage components.
 *
 * Returned Value:
 *   Pointer to MTD device or NULL if not initialized
 *
 ****************************************************************************/

#ifdef CONFIG_RA_MRAM_DATA
struct mtd_dev_s *board_get_data_mram(void)
{
  return g_data_mtd;
}
#endif

/****************************************************************************
 * Name: board_mram_read_param
 *
 * Description:
 *   Read a parameter from MRAM data partition using raw MTD access.
 *   This bypasses the file system for direct parameter access.
 *
 * Input Parameters:
 *   offset - Byte offset into data partition
 *   buffer - Buffer to store read data
 *   len    - Number of bytes to read
 *
 * Returned Value:
 *   Number of bytes read or negative errno
 *
 ****************************************************************************/

#ifdef CONFIG_RA_MRAM_DATA
ssize_t board_mram_read_param(off_t offset, void *buffer, size_t len)
{
  if (g_data_mtd == NULL)
    {
      return -ENODEV;
    }

  return g_data_mtd->read(g_data_mtd, offset, len, buffer);
}
#endif

/****************************************************************************
 * Name: board_mram_write_param
 *
 * Description:
 *   Write a parameter to MRAM data partition using raw MTD access.
 *   This bypasses the file system for direct parameter access.
 *
 * Input Parameters:
 *   offset - Byte offset into data partition
 *   buffer - Buffer containing data to write
 *   len    - Number of bytes to write
 *
 * Returned Value:
 *   Number of bytes written or negative errno
 *
 ****************************************************************************/

#ifdef CONFIG_RA_MRAM_DATA
ssize_t board_mram_write_param(off_t offset, const void *buffer, size_t len)
{
  if (g_data_mtd == NULL)
    {
      return -ENODEV;
    }

#ifdef CONFIG_MTD_BYTE_WRITE
  return g_data_mtd->write(g_data_mtd, offset, len, buffer);
#else
  /* Must use block writes - align to block size */

  struct mtd_geometry_s geo;
  int ret;

  ret = g_data_mtd->ioctl(g_data_mtd, MTDIOC_GEOMETRY,
                          (unsigned long)&geo);
  if (ret < 0)
    {
      return ret;
    }

  /* Calculate block number and write */

  off_t block = offset / geo.blocksize;
  return g_data_mtd->bwrite(g_data_mtd, block, 1, buffer) * geo.blocksize;
#endif
}
#endif

/****************************************************************************
 * Name: board_mram_erase_params
 *
 * Description:
 *   Erase the entire data MRAM partition (reset parameters to defaults).
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 ****************************************************************************/

#ifdef CONFIG_RA_MRAM_DATA
int board_mram_erase_params(void)
{
  if (g_data_mtd == NULL)
    {
      return -ENODEV;
    }

  return g_data_mtd->ioctl(g_data_mtd, MTDIOC_BULKERASE, 0);
}
#endif

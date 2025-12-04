/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_ospi_test.c
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
#include <syslog.h>
#include <stdio.h>
#include <string.h>
#include <debug.h>
#include <errno.h>

#include <nuttx/spi/qspi.h>
#include "ra_ospi_b.h"
#include "evk-ra8p1.h"

#ifdef CONFIG_RA8P1_OSPI_EXAMPLE

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define OSPI_B_COMMAND_READ_DEVICE_ID_SPI           (0x9F)
#define OSPI_B_DEVICE_ID_MACRONIX                   (0x3A86C2) /* MX25LW51245G */

/****************************************************************************
 * Private Data
 ****************************************************************************/

static struct qspi_dev_s *g_qspi;

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra8p1_ospi_test_init
 ****************************************************************************/

int ra8p1_ospi_test_init(void)
{
  /* Initialize the OSPI driver if not already done */
  /* Note: board_ospi_initialize calls ra_ospi_initialize(0) */

  g_qspi = ra_ospi_initialize(0);
  if (!g_qspi)
    {
      syslog(LOG_ERR, "ERROR: Failed to get OSPI interface\n");
      return -ENODEV;
    }

  return OK;
}

/****************************************************************************
 * Name: ra8p1_ospi_test_main
 ****************************************************************************/

int ra8p1_ospi_test_main(int argc, char *argv[])
{
  struct qspi_cmdinfo_s cmdinfo;
  uint8_t id_buf[3];
  uint32_t device_id;
  int ret;

  if (!g_qspi)
    {
      syslog(LOG_ERR, "ERROR: OSPI not initialized\n");
      return -ENODEV;
    }

  syslog(LOG_INFO, "Starting OSPI Test (Read ID)...\n");

  /* Read ID command */
  memset(&cmdinfo, 0, sizeof(cmdinfo));
  cmdinfo.flags   = QSPICMD_READDATA;
  cmdinfo.cmd     = OSPI_B_COMMAND_READ_DEVICE_ID_SPI;
  cmdinfo.buflen  = 3;
  cmdinfo.buffer  = id_buf;

  ret = QSPI_COMMAND(g_qspi, &cmdinfo);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: QSPI_COMMAND failed: %d\n", ret);
      return ret;
    }

  /* Construct Device ID from buffer */
  /* Usually Manufacturer, Type, Density */
  /* Macronix: C2 86 3A */

  syslog(LOG_INFO, "Read ID: %02X %02X %02X\n", id_buf[0], id_buf[1], id_buf[2]);

  device_id = ((uint32_t)id_buf[2] << 16) | ((uint32_t)id_buf[1] << 8) | id_buf[0];

  /* Check against expected ID */
  /* Note: The reference code defines OSPI_B_DEVICE_ID as 0x3A86C2.
     If id_buf[0] is C2, id_buf[1] is 86, id_buf[2] is 3A.
     Then 3A << 16 | 86 << 8 | C2 = 0x3A86C2.
  */

  if (device_id == OSPI_B_DEVICE_ID_MACRONIX)
    {
      syslog(LOG_INFO, "OSPI Test PASSED: Device ID matches MX25LW51245G (0x%06X)\n", (unsigned int)device_id);
    }
  else
    {
      syslog(LOG_ERR, "OSPI Test FAILED: Device ID mismatch (Expected 0x%06X, Got 0x%06X)\n",
             (unsigned int)OSPI_B_DEVICE_ID_MACRONIX, (unsigned int)device_id);
      /* Don't fail the function, just report error */
    }

  return OK;
}

#endif /* CONFIG_RA8P1_OSPI_EXAMPLE */

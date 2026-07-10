/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_spi_loopback.c
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

#ifdef CONFIG_RZV2H_SPI_LOOPBACK_EXAMPLE

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/spi/spi.h>
#include <nuttx/spi/spi_transfer.h>

#include <arch/board/board.h>
#include "rzv_spi.h"
#include "rzv_gpio.h"
#include "rdk-rzv2h.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SPI Configuration for loopback test */
#define SPI_LOOPBACK_BUFFER_SIZE    32
#define SPI_LOOPBACK_FREQUENCY      1000000  /* 1 MHz */
#define SPI_LOOPBACK_MODE           0        /* Mode 0 */

/* SPI buffer length for loopback test */
#define SPI_BUFF_LEN        32
#define SPI_BYTE_SIZE       4 // 1 for 8-bit, 2 for 16-bit, 4 for 32-bit
#define SPI_FREQUENCY       1000000  /* 1 MHz */
#define SPI_MODE            0        /* Mode 0 */

/* Test patterns */
#define TEST_PATTERN_1      0x12345678
#define TEST_PATTERN_2      0xAABBCCDD
#define TEST_PATTERN_3      0x55AA55AA
#define TEST_PATTERN_4      0xA5A55A5A

/* SPI Device IDs for loopback test */
#define SPI_DEVICE_SPI0     0x0000
#define SPI_DEVICE_SPI1     0x0001

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct spi_loopback_s
{
  FAR struct spi_dev_s *spi0;           /* SPI0 master */
  FAR struct spi_dev_s *spi1;           /* SPI1 master */
  uint8_t spi0_tx_buff[SPI_BUFF_LEN*SPI_BYTE_SIZE];   /* SPI0 transmit buffer */
  uint8_t spi0_rx_buff[SPI_BUFF_LEN*SPI_BYTE_SIZE];   /* SPI0 receive buffer */
  uint8_t spi1_tx_buff[SPI_BUFF_LEN*SPI_BYTE_SIZE];   /* SPI1 transmit buffer */
  uint8_t spi1_rx_buff[SPI_BUFF_LEN*SPI_BYTE_SIZE];   /* SPI1 receive buffer */
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

static struct spi_loopback_s g_spi_loopback;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/* rzv_spi_select() and rzv_spi_status() are provided by the board SPI
 * integration file (rzv2h_spi.c), which owns the chip-select GPIO.  They are
 * deliberately NOT redefined here — doing so caused a multiple-definition
 * link error.  The board versions (CS on P9_3, status PRESENT) are correct
 * for internal loopback (asserting an unused CS is harmless).
 */

/****************************************************************************
 * Name: rzv_spi_cmddata (strong override for loopback)
 *
 * Description:
 *   Control the SPI CMD/DATA GPIO for loopback test
 *
 ****************************************************************************/

int rzv_spi_cmddata(struct spi_dev_s *dev, uint32_t devid, bool cmd)
{
  /* Loopback test doesn't use CMD/DATA line */
  return 0;
}

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/* Use driver-provided API rzv_spi_set_loopback() to enable/disable
 * internal loopback. This avoids referencing low-level register
 * macros from board code and keeps register handling in the driver.
 * Note: For RZV2H, loopback may need to be implemented if not available.
 */

/****************************************************************************
 * Name: spi_prepare_test_data
 *
 * Description:
 *   Prepare test data buffers with known patterns for loopback test
 *
 ****************************************************************************/

static void spi_prepare_test_data(void)
{
  int i;

  /* Clear all buffers */
  memset(g_spi_loopback.spi0_tx_buff, 0, sizeof(g_spi_loopback.spi0_tx_buff));
  memset(g_spi_loopback.spi0_rx_buff, 0, sizeof(g_spi_loopback.spi0_rx_buff));
  memset(g_spi_loopback.spi1_tx_buff, 0, sizeof(g_spi_loopback.spi1_tx_buff));
  memset(g_spi_loopback.spi1_rx_buff, 0, sizeof(g_spi_loopback.spi1_rx_buff));

  /* Fill SPI0 TX buffer with test patterns */
  for (i = 0; i < SPI_BUFF_LEN; i++)
    {
      switch (i % 4)
        {
          case 0:
            g_spi_loopback.spi0_tx_buff[i] = (TEST_PATTERN_1 + i) & 0xFF;
            break;
          case 1:
            g_spi_loopback.spi0_tx_buff[i] = (TEST_PATTERN_2 + i) & 0xFF;
            break;
          case 2:
            g_spi_loopback.spi0_tx_buff[i] = (TEST_PATTERN_3 + i) & 0xFF;
            break;
          case 3:
            g_spi_loopback.spi0_tx_buff[i] = (TEST_PATTERN_4 + i) & 0xFF;
            break;
        }
    }

  /* Fill SPI1 TX buffer with different test patterns */
  for (i = 0; i < SPI_BUFF_LEN; i++)
    {
      switch (i % 4)
        {
          case 0:
            g_spi_loopback.spi1_tx_buff[i] = (~TEST_PATTERN_1 + i) & 0xFF;
            break;
          case 1:
            g_spi_loopback.spi1_tx_buff[i] = (~TEST_PATTERN_2 + i) & 0xFF;
            break;
          case 2:
            g_spi_loopback.spi1_tx_buff[i] = (~TEST_PATTERN_3 + i) & 0xFF;
            break;
          case 3:
            g_spi_loopback.spi1_tx_buff[i] = (~TEST_PATTERN_4 + i) & 0xFF;
            break;
        }
    }

  syslog(LOG_INFO, "Test data prepared: SPI0 TX[0]=0x%02x, SPI1 TX[0]=0x%02x\n",
          g_spi_loopback.spi0_tx_buff[0], g_spi_loopback.spi1_tx_buff[0]);
}

/****************************************************************************
 * Name: spi_verify_loopback_data
 *
 * Description:
 *   Verify loopback data - TX data should equal RX data for each SPI
 *
 ****************************************************************************/

static int spi_verify_loopback_data(void)
{
  int i;
  int errors = 0;

  syslog(LOG_INFO, "Verifying SPI loopback data...\n");

  /* Check SPI0: TX data should equal RX data (loopback) */
  for (i = 0; i < SPI_BUFF_LEN; i++)
    {
      if (g_spi_loopback.spi0_tx_buff[i] != g_spi_loopback.spi0_rx_buff[i])
        {
          syslog(LOG_ERR, "SPI0 loopback mismatch at index %d: TX=0x%02x != RX=0x%02x\n",
                 i, g_spi_loopback.spi0_tx_buff[i], g_spi_loopback.spi0_rx_buff[i]);
          up_mdelay(10); /* Small delay to avoid flooding syslog */
          errors++;
        }
        else {
          syslog(LOG_INFO, "SPI0 loopback match at index %d: TX=0x%02x == RX=0x%02x\n",
                 i, g_spi_loopback.spi0_tx_buff[i], g_spi_loopback.spi0_rx_buff[i]);
         up_mdelay(10); /* Small delay to avoid flooding syslog */
        }
    }

  /* Check SPI1: TX data should equal RX data (loopback) */
  for (i = 0; i < SPI_BUFF_LEN; i++)
    {
      if (g_spi_loopback.spi1_tx_buff[i] != g_spi_loopback.spi1_rx_buff[i])
        {
          syslog(LOG_ERR, "SPI1 loopback mismatch at index %d: TX=0x%02x != RX=0x%02x\n",
                 i, g_spi_loopback.spi1_tx_buff[i], g_spi_loopback.spi1_rx_buff[i]);
          up_mdelay(10); /* Small delay to avoid flooding syslog */
          errors++;
        } else {
          syslog(LOG_INFO, "SPI1 loopback match at index %d: TX=0x%02x == RX=0x%02x\n",
                 i, g_spi_loopback.spi1_tx_buff[i], g_spi_loopback.spi1_rx_buff[i]);
         up_mdelay(10); /* Small delay to avoid flooding syslog */
        }
    }

  if (errors == 0)
    {
      syslog(LOG_INFO, "✓ SPI loopback test PASSED - all data verified successfully\n");
      syslog(LOG_INFO, "  SPI0: %d bytes looped back correctly\n", SPI_BUFF_LEN);
      syslog(LOG_INFO, "  SPI1: %d bytes looped back correctly\n", SPI_BUFF_LEN);
      return OK;
    }
  else
    {
      syslog(LOG_ERR, "✗ SPI loopback test FAILED - %d errors found\n", errors);
      return -EIO;
    }
}

/****************************************************************************
 * Name: spi_configure_devices
 *
 * Description:
 *   Configure both SPI devices as masters for loopback testing
 *
 ****************************************************************************/

static int spi_configure_devices(void)
{
  /* Configure SPI0 as master */
  SPI_LOCK(g_spi_loopback.spi0, true);
  SPI_SETMODE(g_spi_loopback.spi0, SPI_MODE);
  SPI_SETBITS(g_spi_loopback.spi0, 8 * SPI_BYTE_SIZE);
  SPI_SETFREQUENCY(g_spi_loopback.spi0, SPI_FREQUENCY);
  SPI_LOCK(g_spi_loopback.spi0, false);

  /* Configure SPI1 as master */
  SPI_LOCK(g_spi_loopback.spi1, true);
  SPI_SETMODE(g_spi_loopback.spi1, SPI_MODE);
  SPI_SETBITS(g_spi_loopback.spi1, 8 * SPI_BYTE_SIZE);
  SPI_SETFREQUENCY(g_spi_loopback.spi1, SPI_FREQUENCY);
  SPI_LOCK(g_spi_loopback.spi1, false);

  syslog(LOG_INFO, "SPI devices configured: SPI0=%p, SPI1=%p (both as masters)\n",
          g_spi_loopback.spi0, g_spi_loopback.spi1);

  return OK;
}

/****************************************************************************
 * Name: spi_test_loopback
 *
 * Description:
 *   Test SPI loopback where MOSI is connected to MISO for each SPI
 *
 ****************************************************************************/

static int spi_test_loopback(void)
{
  syslog(LOG_INFO, "Starting SPI loopback test...\n");

  /* Test SPI0 loopback — enable SPCR2.SPLP, transfer, then disable */

  syslog(LOG_INFO, "Testing Internal SPI0 loopback ...\n");
  SPI_LOCK(g_spi_loopback.spi0, true);
  rzv_spi_set_loopback(g_spi_loopback.spi0, true);
  SPI_EXCHANGE(g_spi_loopback.spi0, g_spi_loopback.spi0_tx_buff,
               g_spi_loopback.spi0_rx_buff, SPI_BUFF_LEN);
  rzv_spi_set_loopback(g_spi_loopback.spi0, false);
  SPI_LOCK(g_spi_loopback.spi0, false);

  /* Test SPI1 loopback — enable SPCR2.SPLP, transfer, then disable */

  syslog(LOG_INFO, "Testing Internal SPI1 loopback ...\n");
  SPI_LOCK(g_spi_loopback.spi1, true);
  rzv_spi_set_loopback(g_spi_loopback.spi1, true);
  SPI_EXCHANGE(g_spi_loopback.spi1, g_spi_loopback.spi1_tx_buff,
               g_spi_loopback.spi1_rx_buff, SPI_BUFF_LEN);
  rzv_spi_set_loopback(g_spi_loopback.spi1, false);
  SPI_LOCK(g_spi_loopback.spi1, false);

  syslog(LOG_INFO, "Loopback transfers completed\n");
  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_spi_loopback_init
 *
 * Description:
 *   Initialize SPI loopback demo
 *
 ****************************************************************************/

int rzv2h_spi_loopback_init(void)
{
  int ret;

  syslog(LOG_INFO, "Initializing SPI loopback demo...\n");

  /* Clear the demo structure */
  memset(&g_spi_loopback, 0, sizeof(g_spi_loopback));

  /* Get SPI0 as master */
  g_spi_loopback.spi0 = rzv_spibus_initialize(0);
  if (!g_spi_loopback.spi0)
    {
      syslog(LOG_ERR, "Failed to initialize SPI0\n");
      return -ENODEV;
    }

  /* Get SPI1 as master */
  g_spi_loopback.spi1 = rzv_spibus_initialize(1);
  if (!g_spi_loopback.spi1)
    {
      syslog(LOG_ERR, "Failed to initialize SPI1\n");
      return -ENODEV;
    }

  /* Configure both SPI devices */
  ret = spi_configure_devices();
  if (ret < 0)
    {
      syslog(LOG_ERR, "Failed to configure SPI devices: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "SPI loopback demo initialized successfully\n");
  return OK;
}

/****************************************************************************
 * Name: rzv2h_spi_loopback_test
 *
 * Description:
 *   Run SPI loopback tests
 *
 ****************************************************************************/

int rzv2h_spi_loopback_test(void)
{
  int ret;

  syslog(LOG_INFO, "=== Starting SPI Loopback Test ===\n");

  if (!g_spi_loopback.spi0 || !g_spi_loopback.spi1)
    {
      syslog(LOG_ERR, "SPI devices not initialized. Call ra8e1_spi_loopback_init() first.\n");
      return -EINVAL;
    }

  /* Prepare test data */
  spi_prepare_test_data();

  /* Run loopback test */
  ret = spi_test_loopback();
  if (ret < 0)
    {
      syslog(LOG_ERR, "Loopback test failed: %d\n", ret);
      return ret;
    }

  /* Verify results */
  ret = spi_verify_loopback_data();
  if (ret < 0)
    {
      return ret;
    }

  syslog(LOG_INFO, "\n=== SPI Loopback Test COMPLETED SUCCESSFULLY ===\n");
  return OK;
}

/****************************************************************************
 * Name: rzv2h_spi_loopback_main
 *
 * Description:
 *   Main entry point for SPI loopback demo
 *
 ****************************************************************************/

int rzv2h_spi_loopback_main(int argc, char *argv[])
{
  int ret;

  syslog(LOG_INFO, "RZV2H SPI Loopback Test\n");
  syslog(LOG_INFO, "========================\n");
  syslog(LOG_INFO, "This test verifies SPI loopback functionality:\n");
  syslog(LOG_INFO, "- SPI0 and SPI1 both configured as masters\n");

  /* Run the test */
  ret = rzv2h_spi_loopback_test();
  if (ret < 0)
    {
      syslog(LOG_INFO, "Test failed: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "\nSPI Loopback Test completed successfully!\n");
  return OK;
}

#endif /* CONFIG_RZV2H_SPI_LOOPBACK_EXAMPLE */

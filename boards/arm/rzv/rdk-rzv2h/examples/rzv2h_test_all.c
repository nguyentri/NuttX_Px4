/****************************************************************************
 * apps/examples/rzv_test/rzv_test.c
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
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <debug.h>
#include <string.h>

#include <nuttx/analog/adc.h>
#include <nuttx/analog/ioctl.h>
#include <nuttx/timers/pwm.h>
#include <nuttx/timers/watchdog.h>
#include <nuttx/i2c/i2c_master.h>
#include <nuttx/spi/spi.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define TEST_ITERATIONS   10

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: test_gpio
 *
 * Description:
 *   Test GPIO functionality (requires LED support)
 *
 ****************************************************************************/

static void test_gpio(void)
{
  int i;

  printf("\n=== GPIO Test ===\n");

#ifdef CONFIG_USERLED
  /* Initialize LEDs */
  board_userled_initialize();

  /* Blink each LED */
  for (i = 0; i < TEST_ITERATIONS; i++)
    {
      printf("LED cycle %d/%d\n", i + 1, TEST_ITERATIONS);

      board_userled(0, true);
      usleep(200000);
      board_userled(0, false);

      board_userled(1, true);
      usleep(200000);
      board_userled(1, false);

      board_userled(2, true);
      usleep(200000);
      board_userled(2, false);

      board_userled(3, true);
      usleep(200000);
      board_userled(3, false);
    }

  printf("GPIO test completed\n");
#else
  printf("GPIO test skipped (CONFIG_USERLED not enabled)\n");
#endif
}

/****************************************************************************
 * Name: test_serial
 *
 * Description:
 *   Test serial port loopback
 *
 ****************************************************************************/

static void test_serial(void)
{
  int fd;
  const char *msg = "RZV2H Serial Test\n";
  char buffer[64];
  ssize_t nbytes;

  printf("\n=== Serial Test ===\n");

  /* Open serial port */
  fd = open("/dev/ttyS0", O_RDWR);
  if (fd < 0)
    {
      printf("Failed to open /dev/ttyS0: %d\n", errno);
      return;
    }

  /* Write test message */
  nbytes = write(fd, msg, strlen(msg));
  printf("Wrote %d bytes to serial port\n", (int)nbytes);

  /* Note: For actual loopback test, TX and RX pins should be connected */
  printf("Serial test completed (connect TX to RX for loopback)\n");

  close(fd);
}

/****************************************************************************
 * Name: test_i2c
 *
 * Description:
 *   Test I2C bus scanning
 *
 ****************************************************************************/

static void test_i2c(void)
{
  int fd;
  struct i2c_msg_s msg;
  struct i2c_transfer_s xfer;
  uint8_t data;
  int addr;
  int found = 0;

  printf("\n=== I2C Test ===\n");

  /* Open I2C bus */
  fd = open("/dev/i2c0", O_RDWR);
  if (fd < 0)
    {
      printf("Failed to open /dev/i2c0: %d\n", errno);
      return;
    }

  printf("Scanning I2C bus (addresses 0x08-0x77)...\n");

  /* Scan I2C addresses */
  for (addr = 0x08; addr <= 0x77; addr++)
    {
      msg.frequency = 100000;
      msg.addr = addr;
      msg.flags = I2C_M_READ;
      msg.buffer = &data;
      msg.length = 1;

      xfer.msgv = &msg;
      xfer.msgc = 1;

      if (ioctl(fd, I2CIOC_TRANSFER, &xfer) == 0)
        {
          printf("  Found device at 0x%02X\n", addr);
          found++;
        }
    }

  printf("I2C scan completed: %d devices found\n", found);

  close(fd);
}

/****************************************************************************
 * Name: test_spi
 *
 * Description:
 *   Test SPI transfer
 *
 ****************************************************************************/

static void test_spi(void)
{
  printf("\n=== SPI Test ===\n");
  printf("SPI test requires hardware connection\n");
  printf("Connect MOSI to MISO for loopback test\n");

  /* SPI test implementation would go here */
  /* Requires board-specific SPI device setup */

  printf("SPI test skipped (requires hardware setup)\n");
}

/****************************************************************************
 * Name: test_pwm
 *
 * Description:
 *   Test PWM output
 *
 ****************************************************************************/

static void test_pwm(void)
{
  int fd;
  struct pwm_info_s info;
  int i;

  printf("\n=== PWM Test ===\n");

  /* Open PWM device */
  fd = open("/dev/pwm0", O_RDONLY);
  if (fd < 0)
    {
      printf("Failed to open /dev/pwm0: %d\n", errno);
      return;
    }

  /* Test different duty cycles */
  for (i = 0; i <= 100; i += 25)
    {
      printf("Setting PWM duty cycle to %d%%\n", i);

      memset(&info, 0, sizeof(info));
      info.frequency = 1000;  /* 1 kHz */
      info.duty = (65536 * i) / 100;  /* Convert percentage to 16-bit value */
      info.channels[0].channel = 0;
      info.channels[0].duty = info.duty;

      if (ioctl(fd, PWMIOC_SETCHARACTERISTICS, &info) < 0)
        {
          printf("Failed to set PWM characteristics: %d\n", errno);
          break;
        }

      if (ioctl(fd, PWMIOC_START, 0) < 0)
        {
          printf("Failed to start PWM: %d\n", errno);
          break;
        }

      sleep(1);
    }

  /* Stop PWM */
  ioctl(fd, PWMIOC_STOP, 0);

  printf("PWM test completed\n");

  close(fd);
}

/****************************************************************************
 * Name: test_adc
 *
 * Description:
 *   Test ADC conversion
 *
 ****************************************************************************/

static void test_adc(void)
{
  int fd;
  struct adc_msg_s sample[4];
  ssize_t nbytes;
  int i;

  printf("\n=== ADC Test ===\n");

  /* Open ADC device */
  fd = open("/dev/adc0", O_RDONLY);
  if (fd < 0)
    {
      printf("Failed to open /dev/adc0: %d\n", errno);
      return;
    }

  /* Read ADC samples */
  for (i = 0; i < TEST_ITERATIONS; i++)
    {
      /* Trigger conversion */
      if (ioctl(fd, ANIOC_TRIGGER, 0) < 0)
        {
          printf("Failed to trigger ADC: %d\n", errno);
          break;
        }

      /* Read samples */
      nbytes = read(fd, sample, sizeof(sample));
      if (nbytes > 0)
        {
          int nsamples = nbytes / sizeof(struct adc_msg_s);
          int j;

          printf("ADC sample %d: ", i + 1);
          for (j = 0; j < nsamples; j++)
            {
              printf("CH%d=%d ", sample[j].am_channel, sample[j].am_data);
            }
          printf("\n");
        }

      usleep(100000);  /* 100ms delay between samples */
    }

  printf("ADC test completed\n");

  close(fd);
}

/****************************************************************************
 * Name: test_watchdog
 *
 * Description:
 *   Test watchdog timer (non-destructive)
 *
 ****************************************************************************/

static void test_watchdog(void)
{
  int fd;
  int timeout = 5000;  /* 5 seconds */
  struct watchdog_status_s status;
  int i;

  printf("\n=== Watchdog Test ===\n");

  /* Open watchdog device */
  fd = open("/dev/watchdog0", O_RDWR);
  if (fd < 0)
    {
      printf("Failed to open /dev/watchdog0: %d\n", errno);
      return;
    }

  /* Set timeout */
  if (ioctl(fd, WDIOC_SETTIMEOUT, timeout) < 0)
    {
      printf("Failed to set watchdog timeout: %d\n", errno);
      close(fd);
      return;
    }

  printf("Watchdog timeout set to %d ms\n", timeout);

  /* Start watchdog */
  if (ioctl(fd, WDIOC_START, 0) < 0)
    {
      printf("Failed to start watchdog: %d\n", errno);
      close(fd);
      return;
    }

  printf("Watchdog started, kicking every second...\n");

  /* Kick watchdog several times */
  for (i = 0; i < 10; i++)
    {
      sleep(1);

      /* Get status */
      if (ioctl(fd, WDIOC_GETSTATUS, &status) == 0)
        {
          printf("Watchdog status: flags=0x%x timeout=%lu timeleft=%lu\n",
                 status.flags, status.timeout, status.timeleft);
        }

      /* Kick watchdog */
      if (ioctl(fd, WDIOC_KEEPALIVE, 0) < 0)
        {
          printf("Failed to kick watchdog: %d\n", errno);
          break;
        }

      printf("Watchdog kicked (%d/10)\n", i + 1);
    }

  /* Stop watchdog */
  ioctl(fd, WDIOC_STOP, 0);

  printf("Watchdog test completed\n");

  close(fd);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: main
 *
 * Description:
 *   Main entry point for RZV2H driver test application
 *
 ****************************************************************************/

int main(int argc, char *argv[])
{
  int test = 0;

  printf("\n");
  printf("======================================\n");
  printf(" RZV2H Driver Test Application\n");
  printf("======================================\n");

  /* Parse command line arguments */
  if (argc > 1)
    {
      test = atoi(argv[1]);
    }

  /* Run specific test or all tests */
  switch (test)
    {
      case 0:
        printf("Running all tests...\n");
        test_gpio();
        test_serial();
        test_i2c();
        test_spi();
        test_pwm();
        test_adc();
        test_watchdog();
        break;

      case 1:
        test_gpio();
        break;

      case 2:
        test_serial();
        break;

      case 3:
        test_i2c();
        break;

      case 4:
        test_spi();
        break;

      case 5:
        test_pwm();
        break;

      case 6:
        test_adc();
        break;

      case 7:
        test_watchdog();
        break;

      default:
        printf("Usage: %s [test_number]\n", argv[0]);
        printf("  0 or no argument: Run all tests\n");
        printf("  1: GPIO test\n");
        printf("  2: Serial test\n");
        printf("  3: I2C test\n");
        printf("  4: SPI test\n");
        printf("  5: PWM test\n");
        printf("  6: ADC test\n");
        printf("  7: Watchdog test\n");
        return EXIT_FAILURE;
    }

  printf("\n");
  printf("======================================\n");
  printf(" Test completed\n");
  printf("======================================\n");

  return EXIT_SUCCESS;
}

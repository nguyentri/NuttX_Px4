/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_sdhi.c
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

/* RDK-RZV2H board-level SDHI glue.
 *
 * Calls rzv_sdhi_initialize(0) to obtain the SDIO lower-half for SD0
 * (the RDK SD card connector, signals QSD0_*), then registers it with the
 * NuttX MMCSD upper-half via mmcsd_slotinitialize().
 *
 * SD0 Pin Configuration:
 *   The six main SD0 signals are dedicated IOPORT pins on R9A09G057H; they
 *   are NOT normal PORT/PIN/PSEL multiplexed IOs and cannot be configured
 *   via rzv_gpio_config().
 *
 *   FSP encoding (refs/rz-fsp-master bsp_override.h):
 *     BSP_IO_SD0CLK  = 0xFFFF0900   (pin AN37, SD0 group 9, index 0)
 *     BSP_IO_SD0CMD  = 0xFFFF0901   (pin AN36, SD0 group 9, index 1)
 *     BSP_IO_SD0DAT0 = 0xFFFF0A00   (pin AP35, SD0 data group A, index 0)
 *     BSP_IO_SD0DAT1 = 0xFFFF0A01   (pin AN35, SD0 data group A, index 1)
 *     BSP_IO_SD0DAT2 = 0xFFFF0A02   (pin AP37, SD0 data group A, index 2)
 *     BSP_IO_SD0DAT3 = 0xFFFF0A03   (pin AR37, SD0 data group A, index 3)
 *
 *   The FSP configures these via r_ioport_dedicated_port_cfg() which writes
 *   IEN3_L/H and IOLH3_L/H registers within R_GPIO (base 0x10410020 for
 *   CR8 core, confirmed from R9A09G057H/cr/iodefines/gpio_iodefine.h).
 *   The register offsets within R_GPIO depend on the full R_GPIO_Type struct
 *   layout from the FSP CMSIS iodefine — not replicated here because:
 *     (a) FSP sources are in refs/ only, not in the NuttX build tree.
 *     (b) The struct layout spans >6000 lines and requires CMSIS headers.
 *     (c) u-boot / TF-A may already configure these pins before NuttX starts.
 *
 * TODO (follow-up): implement rzv2h_sdhi_pin_setup() using one of:
 *     Option A: Extract the 6 IEN3/IOLH3 register write addresses from the
 *               R_GPIO_Type struct in gpio_iodefine.h and hard-code them.
 *               NEEDS_VERIFY: confirm R_GPIO_BASE=0x10410020 is CA55-visible.
 *     Option B: Teach rzv_gpio_config() to handle the 0xFFFF09xx/0xFFFF0Axx
 *               encoding by routing to a new rzv_gpio_dedicated_config().
 *     Option C: Confirm that the boot firmware (u-boot/TF-A) already sets
 *               these pins and document that NuttX need not touch them.
 */


/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <errno.h>
#include <debug.h>
#include <syslog.h>

#include <nuttx/sdio.h>
#include <nuttx/mmcsd.h>

#include "rzv_sdhi.h"

#ifdef CONFIG_RZV_SDHI

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* RDK-RZV2H uses SDHI channel 0 (SD0, signals QSD0_*) for the SD slot */

#define RZV2H_SDHI_SLOT         0
#define RZV2H_SDHI_MMCSD_MINOR  0   /* /dev/mmcsd0 */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_sdhi_initialize
 *
 * Description:
 *   Board-level SD card initialization.  Obtains the SDIO lower-half for
 *   slot 0 and registers it with the MMCSD upper-half.
 *
 *   Called from board_bringup() when CONFIG_RZV_SDHI=y.
 *
 * Returned Value:
 *   0 on success; negated errno on failure.
 *
 ****************************************************************************/

int rzv2h_sdhi_initialize(void)
{
  struct sdio_dev_s *sdio;
  int ret;

  /* CPG clock: rzv_clock_enable_sdhi(0) is called inside rzv_sdhi_initialize()
   * (arch driver level).  No duplicate call needed here.
   */

  /* SD0 dedicated pin-mux: see file-level TODO comment.
   * The six pins (AN37/AN36/AP35/AN35/AP37/AR37) use FSP dedicated-pin
   * encoding 0xFFFF09xx / 0xFFFF0Axx and require IEN3/IOLH3 register writes
   * inside R_GPIO.  Not yet implemented; see the file-level TODO above.
   * NEEDS_VERIFY: confirm boot firmware state of these pins before adding
   * pin-mux code (u-boot may already enable them).
   */

  /* Obtain the SDIO lower-half interface */

  sdio = rzv_sdhi_initialize(RZV2H_SDHI_SLOT);
  if (sdio == NULL)
    {
      syslog(LOG_ERR,
             "ERROR: rzv_sdhi_initialize(slot=%d) failed\n",
             RZV2H_SDHI_SLOT);
      return -ENODEV;
    }

  /* Register with the MMCSD upper-half.
   * This creates /dev/mmcsd0 when CONFIG_MMCSD_SDIO=y.
   */

  ret = mmcsd_slotinitialize(RZV2H_SDHI_MMCSD_MINOR, sdio);
  if (ret < 0)
    {
      syslog(LOG_ERR,
             "ERROR: mmcsd_slotinitialize(minor=%d) failed: %d\n",
             RZV2H_SDHI_MMCSD_MINOR, ret);
      return ret;
    }

  syslog(LOG_INFO,
         "SDHI slot %d registered as /dev/mmcsd%d\n",
         RZV2H_SDHI_SLOT, RZV2H_SDHI_MMCSD_MINOR);
  return OK;
}

#endif /* CONFIG_RZV_SDHI */

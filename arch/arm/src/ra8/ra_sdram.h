/****************************************************************************
 * arch/arm/src/ra8/ra_sdram.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_SDRAM_H
#define __ARCH_ARM_SRC_RA8_RA_SDRAM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SDRAM Bus Width */

#define RA_SDRAM_BUS_WIDTH_8BIT   2  /* 8-bit bus width */
#define RA_SDRAM_BUS_WIDTH_16BIT  0  /* 16-bit bus width */
#define RA_SDRAM_BUS_WIDTH_32BIT  1  /* 32-bit bus width */

/* SDRAM Endian Mode */

#define RA_SDRAM_ENDIAN_LITTLE    0  /* Little endian */
#define RA_SDRAM_ENDIAN_BIG       1  /* Big endian */

/* SDRAM Access Mode */

#define RA_SDRAM_ACCESS_SINGLE    0  /* Single access */
#define RA_SDRAM_ACCESS_BURST     1  /* Burst access (continuous) */

/* SDRAM Address Multiplex Shift */

#define RA_SDRAM_MXC_8BIT_SHIFT   0  /* 8-bit column address shift */
#define RA_SDRAM_MXC_9BIT_SHIFT   1  /* 9-bit column address shift */
#define RA_SDRAM_MXC_10BIT_SHIFT  2  /* 10-bit column address shift */
#define RA_SDRAM_MXC_11BIT_SHIFT  3  /* 11-bit column address shift */

/* Default SDRAM timing parameters (based on IS42S16320F at 100MHz SDCLK)
 * These can be overridden in the board configuration.
 */

#ifndef CONFIG_RA_SDRAM_TCL
#  define CONFIG_RA_SDRAM_TCL     3  /* CAS Latency (cycles) */
#endif

#ifndef CONFIG_RA_SDRAM_TRAS
#  define CONFIG_RA_SDRAM_TRAS    6  /* Row Active time (tRAS, cycles) */
#endif

#ifndef CONFIG_RA_SDRAM_TRCD
#  define CONFIG_RA_SDRAM_TRCD    3  /* Row-to-Column delay (tRCD, cycles) */
#endif

#ifndef CONFIG_RA_SDRAM_TRP
#  define CONFIG_RA_SDRAM_TRP     3  /* Row Precharge time (tRP, cycles) */
#endif

#ifndef CONFIG_RA_SDRAM_TWR
#  define CONFIG_RA_SDRAM_TWR     2  /* Write Recovery time (tWR, cycles) */
#endif

#ifndef CONFIG_RA_SDRAM_TREFW
#  define CONFIG_RA_SDRAM_TREFW   8  /* Auto-Refresh Cycle Count Setting */
#endif

#ifndef CONFIG_RA_SDRAM_TRFC
#  define CONFIG_RA_SDRAM_TRFC    780  /* Refresh Cycle interval (tRFC, cycles) */
#endif

/* Initialization timing */

#ifndef CONFIG_RA_SDRAM_INIT_ARFI
#  define CONFIG_RA_SDRAM_INIT_ARFI  7  /* Init Auto-Refresh Interval (min 3) */
#endif

#ifndef CONFIG_RA_SDRAM_INIT_ARFC
#  define CONFIG_RA_SDRAM_INIT_ARFC  8  /* Init Auto-Refresh Count */
#endif

#ifndef CONFIG_RA_SDRAM_INIT_PRC
#  define CONFIG_RA_SDRAM_INIT_PRC   5  /* Init Precharge Cycle Count (min 3) */
#endif

/* Default bus width and configuration */

#ifndef CONFIG_RA_SDRAM_BUS_WIDTH
#  define CONFIG_RA_SDRAM_BUS_WIDTH  RA_SDRAM_BUS_WIDTH_32BIT
#endif

#ifndef CONFIG_RA_SDRAM_ENDIAN_MODE
#  define CONFIG_RA_SDRAM_ENDIAN_MODE  RA_SDRAM_ENDIAN_LITTLE
#endif

#ifndef CONFIG_RA_SDRAM_ACCESS_MODE
#  define CONFIG_RA_SDRAM_ACCESS_MODE  RA_SDRAM_ACCESS_BURST
#endif

#ifndef CONFIG_RA_SDRAM_MXC_SHIFT
#  define CONFIG_RA_SDRAM_MXC_SHIFT  RA_SDRAM_MXC_9BIT_SHIFT
#endif

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* SDRAM configuration structure */

struct ra_sdram_config_s
{
  /* Bus configuration */

  uint8_t  bus_width;      /* Bus width (8/16/32-bit) */
  uint8_t  endian_mode;    /* Endian mode (little/big) */
  uint8_t  access_mode;    /* Access mode (single/burst) */
  uint8_t  mxc_shift;      /* Address multiplex shift (column address bits) */

  /* Timing parameters */

  uint8_t  tcl;            /* CAS Latency */
  uint8_t  tras;           /* Row Active time (tRAS) */
  uint8_t  trcd;           /* Row-to-Column delay (tRCD) */
  uint8_t  trp;            /* Row Precharge time (tRP) */
  uint8_t  twr;            /* Write Recovery time (tWR) */
  uint16_t trefw;         /* Auto-Refresh Cycle Count */
  uint16_t trfc;           /* Refresh Cycle interval (tRFC) */

  /* Initialization timing */

  uint8_t  init_arfi;      /* Init Auto-Refresh Interval */
  uint8_t  init_arfc;      /* Init Auto-Refresh Count */
  uint8_t  init_prc;       /* Init Precharge Cycle Count */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Name: ra_sdram_initialize
 *
 * Description:
 *   Initialize the SDRAM controller and external SDRAM memory.
 *
 * Input Parameters:
 *   config      - Pointer to SDRAM configuration structure.
 *                 If NULL, default configuration will be used.
 *   init_memory - If true, execute full initialization sequence including
 *                 programming the SDRAM device. If false, only configure
 *                 the controller and leave memory in self-refresh mode.
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_sdram_initialize(const struct ra_sdram_config_s *config,
                        bool init_memory);

/****************************************************************************
 * Name: ra_sdram_selfrefresh_enable
 *
 * Description:
 *   Enable SDRAM self-refresh mode. This function changes SDRAM from
 *   Auto-refresh to Self-refresh mode, allowing Software Standby and
 *   Deep Software Standby modes to be entered without data loss.
 *
 *   Note: SDRAM cannot be accessed after calling this function.
 *         Use ra_sdram_selfrefresh_disable() to resume normal operation.
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_sdram_selfrefresh_enable(void);

/****************************************************************************
 * Name: ra_sdram_selfrefresh_disable
 *
 * Description:
 *   Disable SDRAM self-refresh mode. This function changes SDRAM from
 *   Self-refresh back to Auto-refresh mode, allowing normal SDRAM
 *   operation to resume.
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_sdram_selfrefresh_disable(void);

/****************************************************************************
 * Name: ra_sdram_is_initialized
 *
 * Description:
 *   Check if SDRAM has been initialized.
 *
 * Returned Value:
 *   true if SDRAM is initialized and accessible; false otherwise.
 *
 ****************************************************************************/

bool ra_sdram_is_initialized(void);

/****************************************************************************
 * Name: ra_sdram_test
 *
 * Description:
 *   Perform a basic read/write test on SDRAM memory.
 *
 * Input Parameters:
 *   base - Base address of SDRAM to test
 *   size - Size in bytes to test
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_RA_SDRAM_TEST
int ra_sdram_test(uintptr_t base, size_t size);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RA8_RA_SDRAM_H */

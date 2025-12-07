/****************************************************************************
 * arch/arm/src/ra8/ra_lpm.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_LPM_H
#define __ARCH_ARM_SRC_RA8_RA_LPM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* Low power modes supported by RA8P1 MCU */

enum ra_lpm_mode_e
{
  RA_LPM_MODE_SLEEP = 0,           /* Sleep mode - CPU stops, peripherals run */
  RA_LPM_MODE_DEEP_SLEEP,          /* Deep Sleep mode */
  RA_LPM_MODE_SW_STANDBY,          /* Software Standby mode */
  RA_LPM_MODE_DEEP_SW_STANDBY_1,   /* Deep Software Standby mode 1 */
  RA_LPM_MODE_DEEP_SW_STANDBY_2,   /* Deep Software Standby mode 2 */
  RA_LPM_MODE_DEEP_SW_STANDBY_3,   /* Deep Software Standby mode 3 */
};

/* I/O port state after Deep Software Standby mode */

enum ra_lpm_io_port_e
{
  RA_LPM_IO_PORT_RESET = 0,        /* I/O ports reset on wake */
  RA_LPM_IO_PORT_RETAIN = 1,       /* I/O ports retain state on wake */
};

/* Power supply control for Deep Software Standby */

enum ra_lpm_power_supply_e
{
  RA_LPM_POWER_SUPPLY_MODE1 = 0,   /* Power to standby RAM, LOCO, PVD0 */
  RA_LPM_POWER_SUPPLY_MODE2 = 1,   /* Standby RAM, LOCO, IWDT disabled */
  RA_LPM_POWER_SUPPLY_MODE3 = 2,   /* Standby RAM, PVD0, LOCO, IWDT disabled */
};

/* DCDC soft start mode for Deep Software Standby */

enum ra_lpm_dcss_mode_e
{
  RA_LPM_DCSS_MODE_128US = 1,      /* 128 µs soft start time */
  RA_LPM_DCSS_MODE_256US = 2,      /* 256 µs soft start time */
  RA_LPM_DCSS_MODE_512US = 3,      /* 512 µs soft start time */
};

/* Wake-up sources for standby/deep standby modes */

enum ra_lpm_wakeup_source_e
{
  /* IRQ pins (IRQ0-IRQ15) */

  RA_LPM_WAKEUP_IRQ0     = (1ULL << 0),
  RA_LPM_WAKEUP_IRQ1     = (1ULL << 1),
  RA_LPM_WAKEUP_IRQ2     = (1ULL << 2),
  RA_LPM_WAKEUP_IRQ3     = (1ULL << 3),
  RA_LPM_WAKEUP_IRQ4     = (1ULL << 4),
  RA_LPM_WAKEUP_IRQ5     = (1ULL << 5),
  RA_LPM_WAKEUP_IRQ6     = (1ULL << 6),
  RA_LPM_WAKEUP_IRQ7     = (1ULL << 7),
  RA_LPM_WAKEUP_IRQ8     = (1ULL << 8),
  RA_LPM_WAKEUP_IRQ9     = (1ULL << 9),
  RA_LPM_WAKEUP_IRQ10    = (1ULL << 10),
  RA_LPM_WAKEUP_IRQ11    = (1ULL << 11),
  RA_LPM_WAKEUP_IRQ12    = (1ULL << 12),
  RA_LPM_WAKEUP_IRQ13    = (1ULL << 13),
  RA_LPM_WAKEUP_IRQ14    = (1ULL << 14),
  RA_LPM_WAKEUP_IRQ15    = (1ULL << 15),

  /* Other wake-up sources */

  RA_LPM_WAKEUP_PVD1     = (1ULL << 16),
  RA_LPM_WAKEUP_PVD2     = (1ULL << 17),
  RA_LPM_WAKEUP_RTC_INT  = (1ULL << 18),
  RA_LPM_WAKEUP_RTC_ALM  = (1ULL << 19),
  RA_LPM_WAKEUP_NMI      = (1ULL << 20),
  RA_LPM_WAKEUP_USBFS    = (1ULL << 24),
  RA_LPM_WAKEUP_USBHS    = (1ULL << 25),
  RA_LPM_WAKEUP_ULPT0    = (1ULL << 26),
  RA_LPM_WAKEUP_ULPT1    = (1ULL << 27),
  RA_LPM_WAKEUP_IWDT     = (1ULL << 29),
  RA_LPM_WAKEUP_SOSTD    = (1ULL << 30),
  RA_LPM_WAKEUP_VBATT    = (1ULL << 31),
};

/* LPM configuration structure */

struct ra_lpm_config_s
{
  enum ra_lpm_mode_e mode;                /* Low power mode to enter */
  enum ra_lpm_io_port_e io_port_state;    /* I/O port state for deep standby */
  enum ra_lpm_power_supply_e power_supply; /* Power supply control */
  enum ra_lpm_dcss_mode_e dcss_mode;      /* DCDC soft start mode */
  uint64_t wakeup_sources;                /* Enabled wake-up sources */
  uint64_t wakeup_edges;                  /* Wake-up edge selection (1=rising) */
  bool output_port_enable;                /* Enable output ports in standby */
};

/* LPM status structure */

struct ra_lpm_status_s
{
  enum ra_lpm_mode_e last_mode;           /* Last LPM mode entered */
  uint64_t wakeup_flags;                  /* Wake-up source flags */
  bool deep_standby_reset;                /* True if woke from deep standby */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Name: ra_lpm_initialize
 *
 * Description:
 *   Initialize the LPM subsystem. Should be called once during system
 *   startup.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_lpm_initialize(void);

/****************************************************************************
 * Name: ra_lpm_configure
 *
 * Description:
 *   Configure low power mode settings without entering the mode.
 *
 * Input Parameters:
 *   config - Pointer to configuration structure
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_lpm_configure(FAR const struct ra_lpm_config_s *config);

/****************************************************************************
 * Name: ra_lpm_enter
 *
 * Description:
 *   Enter the configured low power mode. Function returns after waking up.
 *
 * Input Parameters:
 *   mode - Low power mode to enter (overrides configured mode)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_lpm_enter(enum ra_lpm_mode_e mode);

/****************************************************************************
 * Name: ra_lpm_sleep
 *
 * Description:
 *   Enter sleep mode. CPU halts but peripherals continue running.
 *   Wakes up on any enabled interrupt.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_lpm_sleep(void);

/****************************************************************************
 * Name: ra_lpm_deep_sleep
 *
 * Description:
 *   Enter deep sleep mode. Similar to sleep but with additional
 *   power savings. Wakes up on enabled interrupts.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_lpm_deep_sleep(void);

/****************************************************************************
 * Name: ra_lpm_standby
 *
 * Description:
 *   Enter software standby mode. Most power is cut, but RAM is retained.
 *   Wakes up on configured wake-up sources.
 *
 * Input Parameters:
 *   wakeup_sources - Bitmask of enabled wake-up sources
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_lpm_standby(uint64_t wakeup_sources);

/****************************************************************************
 * Name: ra_lpm_deep_standby
 *
 * Description:
 *   Enter deep software standby mode. Maximum power savings but
 *   requires longer wake-up time. Only standby RAM is retained.
 *
 * Input Parameters:
 *   wakeup_sources - Bitmask of enabled wake-up sources
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_lpm_deep_standby(uint64_t wakeup_sources);

/****************************************************************************
 * Name: ra_lpm_get_status
 *
 * Description:
 *   Get current LPM status including wake-up source information.
 *
 * Input Parameters:
 *   status - Pointer to status structure to fill
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_lpm_get_status(FAR struct ra_lpm_status_s *status);

/****************************************************************************
 * Name: ra_lpm_clear_wakeup_flags
 *
 * Description:
 *   Clear wake-up source flags after reading.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

void ra_lpm_clear_wakeup_flags(void);

/****************************************************************************
 * Name: ra_lpm_io_keep_clear
 *
 * Description:
 *   Clear the IOKEEP bit after waking from deep software standby.
 *   This releases I/O ports from their retained state.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

void ra_lpm_io_keep_clear(void);

/****************************************************************************
 * Name: ra_lpm_check_deep_standby_reset
 *
 * Description:
 *   Check if system was reset from deep software standby mode.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   true if reset was from deep standby, false otherwise.
 *
 ****************************************************************************/

bool ra_lpm_check_deep_standby_reset(void);

#ifdef CONFIG_PM
/****************************************************************************
 * Name: ra_pm_initialize
 *
 * Description:
 *   Initialize the RA8 power management and register with NuttX PM framework.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_pm_initialize(void);
#endif

/****************************************************************************
 * Name: ra_pmstop
 *
 * Description:
 *   Enter sleep or deep sleep mode (called from idle loop)
 *
 * Input Parameters:
 *   deep - true for deep sleep, false for regular sleep
 *
 ****************************************************************************/

void ra_pmstop(bool deep);

/****************************************************************************
 * Name: ra_pmstandby
 *
 * Description:
 *   Enter software standby mode (called from idle loop)
 *
 ****************************************************************************/

void ra_pmstandby(void);

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RA8_RA_LPM_H */

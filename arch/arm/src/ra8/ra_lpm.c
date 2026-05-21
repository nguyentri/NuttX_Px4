/****************************************************************************
 * arch/arm/src/ra8/ra_lpm.c
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
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <arch/board/board.h>

#ifdef CONFIG_PM
#include <nuttx/power/pm.h>
#endif

#include "arm_internal.h"
#include "chip.h"
#include "nvic.h"
#include "barriers.h"

#include "hardware/ra_memorymap.h"
#include "hardware/ra_hardware.h"
#include "ra_lpm.h"

#if defined(CONFIG_RA_LPM)

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* LPSCR values for RA8P1 (Gen2) */

#define LPSCR_SYSTEM_ACTIVE              0x00
#define LPSCR_SW_STANDBY_MODE            0x05
#define LPSCR_DEEP_SW_STANDBY_MODE1      0x08
#define LPSCR_DEEP_SW_STANDBY_MODE2      0x09
#define LPSCR_DEEP_SW_STANDBY_MODE3      0x0A

/* Register access macros */

#define getreg8(a)       (*(volatile uint8_t *)(a))
#define getreg16(a)      (*(volatile uint16_t *)(a))
#define getreg32(a)      (*(volatile uint32_t *)(a))
#define putreg8(v,a)     (*(volatile uint8_t *)(a) = (v))
#define putreg16(v,a)    (*(volatile uint16_t *)(a) = (v))
#define putreg32(v,a)    (*(volatile uint32_t *)(a) = (v))

/* Register protect access - use definitions from ra_hardware.h */

#define PRCR_PRC1        R_SYSC_PRCR_S_PRC1
#define PRCR_PRC3        R_SYSC_PRCR_S_PRC3

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct ra_lpm_s
{
  bool initialized;
  struct ra_lpm_config_s config;
  struct ra_lpm_status_s status;
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

static struct ra_lpm_s g_lpm_priv;

#ifdef CONFIG_PM
static struct pm_callback_s g_pm_callback;
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_lpm_protect_disable
 *
 * Description:
 *   Disable register protection for LPM registers
 *
 ****************************************************************************/

static void ra_lpm_protect_disable(void)
{
  putreg16(R_SYSC_PRCR_S_KEY | PRCR_PRC1 | PRCR_PRC3, R_SYSC_PRCR_S);
}

/****************************************************************************
 * Name: ra_lpm_protect_enable
 *
 * Description:
 *   Enable register protection for LPM registers
 *
 ****************************************************************************/

static void ra_lpm_protect_enable(void)
{
  putreg16(R_SYSC_PRCR_S_KEY, R_SYSC_PRCR_S);
}

/****************************************************************************
 * Name: ra_lpm_wait_operating_mode
 *
 * Description:
 *   Wait for any ongoing operating mode transition to complete
 *
 ****************************************************************************/

static void ra_lpm_wait_operating_mode(void)
{
  /* Wait for OPCCR.OPCMTSF = 0 (Operating mode transition complete) */

  while ((getreg8(R_SYSC_OPCCR) & R_SYSC_OPCCR_OPCMTSF) != 0)
    {
      /* Spin wait */
    }
}

/****************************************************************************
 * Name: ra_lpm_configure_wakeup
 *
 * Description:
 *   Configure wake-up sources for standby modes
 *
 ****************************************************************************/

static void ra_lpm_configure_wakeup(uint64_t sources, uint64_t edges)
{
  /* Configure ICU wake-up enable registers */

  putreg32((uint32_t)(sources & 0xFFFFFFFF), R_ICU_WUPEN0);
  putreg32((uint32_t)((sources >> 32) & 0xFFFFFFFF), R_ICU_WUPEN1);
}

/****************************************************************************
 * Name: ra_lpm_configure_deep_standby
 *
 * Description:
 *   Configure deep standby cancel sources
 *
 ****************************************************************************/

static void ra_lpm_configure_deep_standby(FAR const struct ra_lpm_config_s *cfg)
{
  uint8_t dpsbycr;
  uint64_t sources = cfg->wakeup_sources;
  uint64_t edges = cfg->wakeup_edges;

  /* Configure DPSIER registers for deep standby cancel sources */

  putreg8((uint8_t)(sources & 0xFF), R_SYSC_DPSIER0);
  putreg8((uint8_t)((sources >> 8) & 0xFF), R_SYSC_DPSIER1);
  putreg8((uint8_t)((sources >> 16) & 0xFF), R_SYSC_DPSIER2);
  putreg8((uint8_t)((sources >> 24) & 0xFF), R_SYSC_DPSIER3);

  /* Configure DPSIEGR registers for edge selection */

  putreg8((uint8_t)(edges & 0xFF), R_SYSC_DPSIEGR0);
  putreg8((uint8_t)((edges >> 8) & 0xFF), R_SYSC_DPSIEGR1);
  putreg8((uint8_t)((edges >> 16) & 0xFF), R_SYSC_DPSIEGR2);

  /* Configure DPSBYCR register */

  dpsbycr = cfg->power_supply & R_SYSC_DPSBYCR_DEEPCUT_MASK;

  if (cfg->io_port_state == RA_LPM_IO_PORT_RETAIN)
    {
      dpsbycr |= R_SYSC_DPSBYCR_IOKEEP;
    }

  dpsbycr |= (cfg->dcss_mode << R_SYSC_DPSBYCR_DCSSMODE_SHIFT) &
             R_SYSC_DPSBYCR_DCSSMODE_MASK;

  putreg8(dpsbycr, R_SYSC_DPSBYCR);
}

/****************************************************************************
 * Name: ra_lpm_enter_sleep
 *
 * Description:
 *   Enter sleep mode - CPU halts but peripherals continue
 *
 ****************************************************************************/

static int ra_lpm_enter_sleep(void)
{
  irqstate_t flags;

  _info("Entering sleep mode\n");

  flags = enter_critical_section();

  /* Make sure LPSCR is set to System Active before WFI
   * For sleep mode, we don't modify LPSCR - just execute WFI
   */

  /* Data Synchronization Barrier */

  ARM_DSB();

  /* Instruction Synchronization Barrier */

  ARM_ISB();

  /* Wait for interrupt - enter sleep mode */

  asm volatile("wfi");

  leave_critical_section(flags);

  _info("Woke from sleep mode\n");

  return OK;
}

/****************************************************************************
 * Name: ra_lpm_enter_deep_sleep
 *
 * Description:
 *   Enter deep sleep mode
 *
 ****************************************************************************/

static int ra_lpm_enter_deep_sleep(void)
{
  irqstate_t flags;
  uint32_t sleepdeep;

  _info("Entering deep sleep mode\n");

  flags = enter_critical_section();

  /* Set SLEEPDEEP bit in SCR */

  sleepdeep = getreg32(NVIC_SYSCON);
  sleepdeep |= NVIC_SYSCON_SLEEPDEEP;
  putreg32(sleepdeep, NVIC_SYSCON);

  /* Data Synchronization Barrier */

  ARM_DSB();

  /* Instruction Synchronization Barrier */

  ARM_ISB();

  /* Wait for interrupt - enter deep sleep mode */

  asm volatile("wfi");

  /* Clear SLEEPDEEP bit after wake-up */

  sleepdeep = getreg32(NVIC_SYSCON);
  sleepdeep &= ~NVIC_SYSCON_SLEEPDEEP;
  putreg32(sleepdeep, NVIC_SYSCON);

  leave_critical_section(flags);

  _info("Woke from deep sleep mode\n");

  return OK;
}

/****************************************************************************
 * Name: ra_lpm_enter_sw_standby
 *
 * Description:
 *   Enter software standby mode
 *
 ****************************************************************************/

static int ra_lpm_enter_sw_standby(FAR const struct ra_lpm_config_s *cfg)
{
  irqstate_t flags;
  uint32_t sleepdeep;

  _info("Entering software standby mode\n");

  flags = enter_critical_section();

  ra_lpm_protect_disable();

  /* Wait for any ongoing mode transition */

  ra_lpm_wait_operating_mode();

  /* Configure wake-up sources */

  ra_lpm_configure_wakeup(cfg->wakeup_sources, cfg->wakeup_edges);

  /* Set LPSCR for software standby mode */

  putreg8(LPSCR_SW_STANDBY_MODE, R_SYSC_LPSCR);

  /* Configure output port enable if needed */

  if (cfg->output_port_enable)
    {
      uint16_t sbycr = getreg16(R_SYSC_SBYCR);
      sbycr |= R_SYSC_SBYCR_OPE;
      putreg16(sbycr, R_SYSC_SBYCR);
    }

  /* Set SLEEPDEEP bit in SCR */

  sleepdeep = getreg32(NVIC_SYSCON);
  sleepdeep |= NVIC_SYSCON_SLEEPDEEP;
  putreg32(sleepdeep, NVIC_SYSCON);

  /* Data Synchronization Barrier */

  ARM_DSB();

  /* Instruction Synchronization Barrier */

  ARM_ISB();

  /* Wait for interrupt - enter standby mode */

  asm volatile("wfi");

  /* Clear SLEEPDEEP bit after wake-up */

  sleepdeep = getreg32(NVIC_SYSCON);
  sleepdeep &= ~NVIC_SYSCON_SLEEPDEEP;
  putreg32(sleepdeep, NVIC_SYSCON);

  /* Clear LPSCR back to System Active */

  putreg8(LPSCR_SYSTEM_ACTIVE, R_SYSC_LPSCR);

  ra_lpm_protect_enable();

  leave_critical_section(flags);

  _info("Woke from software standby mode\n");

  return OK;
}

/****************************************************************************
 * Name: ra_lpm_enter_deep_sw_standby
 *
 * Description:
 *   Enter deep software standby mode
 *
 ****************************************************************************/

static int ra_lpm_enter_deep_sw_standby(FAR const struct ra_lpm_config_s *cfg)
{
  irqstate_t flags;
  uint32_t sleepdeep;
  uint8_t lpscr;

  _info("Entering deep software standby mode\n");

  flags = enter_critical_section();

  ra_lpm_protect_disable();

  /* Wait for any ongoing mode transition */

  ra_lpm_wait_operating_mode();

  /* Configure deep standby settings */

  ra_lpm_configure_deep_standby(cfg);

  /* Clear any pending deep standby flags */

  putreg8(0, R_SYSC_DPSIFR0);
  putreg8(0, R_SYSC_DPSIFR1);
  putreg8(0, R_SYSC_DPSIFR2);
  putreg8(0, R_SYSC_DPSIFR3);

  /* Set LPSCR based on deep standby mode level */

  switch (cfg->mode)
    {
      case RA_LPM_MODE_DEEP_SW_STANDBY_2:
        lpscr = LPSCR_DEEP_SW_STANDBY_MODE2;
        break;

      case RA_LPM_MODE_DEEP_SW_STANDBY_3:
        lpscr = LPSCR_DEEP_SW_STANDBY_MODE3;
        break;

      case RA_LPM_MODE_DEEP_SW_STANDBY_1:
      default:
        lpscr = LPSCR_DEEP_SW_STANDBY_MODE1;
        break;
    }

  putreg8(lpscr, R_SYSC_LPSCR);

  /* Set SLEEPDEEP bit in SCR */

  sleepdeep = getreg32(NVIC_SYSCON);
  sleepdeep |= NVIC_SYSCON_SLEEPDEEP;
  putreg32(sleepdeep, NVIC_SYSCON);

  /* Data Synchronization Barrier */

  ARM_DSB();

  /* Instruction Synchronization Barrier */

  ARM_ISB();

  /* Wait for interrupt - enter deep standby mode
   * Note: System will reset when waking from deep standby
   */

  asm volatile("wfi");

  /* If we reach here, entry to deep standby failed */

  sleepdeep = getreg32(NVIC_SYSCON);
  sleepdeep &= ~NVIC_SYSCON_SLEEPDEEP;
  putreg32(sleepdeep, NVIC_SYSCON);

  putreg8(LPSCR_SYSTEM_ACTIVE, R_SYSC_LPSCR);

  ra_lpm_protect_enable();

  leave_critical_section(flags);

  pwmerr("Deep standby entry failed!\n");

  return -EIO;
}

#ifdef CONFIG_PM
/****************************************************************************
 * Name: ra_pm_prepare
 *
 * Description:
 *   Prepare for PM state transition
 *
 ****************************************************************************/

static int ra_pm_prepare(FAR struct pm_callback_s *cb, int domain,
                         enum pm_state_e pmstate)
{
  /* Always allow transition */

  return OK;
}

/****************************************************************************
 * Name: ra_pm_notify
 *
 * Description:
 *   Notify of PM state change
 *
 ****************************************************************************/

static void ra_pm_notify(FAR struct pm_callback_s *cb, int domain,
                         enum pm_state_e pmstate)
{
  switch (pmstate)
    {
      case PM_RESTORE:
        _info("PM_RESTORE\n");
        break;

      case PM_NORMAL:
        _info("PM_NORMAL\n");
        break;

      case PM_IDLE:
        _info("PM_IDLE\n");
        break;

      case PM_STANDBY:
        _info("PM_STANDBY - entering deep sleep\n");
        ra_lpm_deep_sleep();
        break;

      case PM_SLEEP:
        _info("PM_SLEEP - entering software standby\n");
        ra_lpm_standby(g_lpm_priv.config.wakeup_sources);
        break;

      default:
        break;
    }
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_lpm_initialize
 *
 * Description:
 *   Initialize the LPM subsystem
 *
 ****************************************************************************/

int ra_lpm_initialize(void)
{
  if (g_lpm_priv.initialized)
    {
      return OK;
    }

  memset(&g_lpm_priv, 0, sizeof(g_lpm_priv));

  /* Set default configuration */

  g_lpm_priv.config.mode = RA_LPM_MODE_SLEEP;
  g_lpm_priv.config.io_port_state = RA_LPM_IO_PORT_RETAIN;
  g_lpm_priv.config.power_supply = RA_LPM_POWER_SUPPLY_MODE1;
  g_lpm_priv.config.dcss_mode = RA_LPM_DCSS_MODE_256US;
  g_lpm_priv.config.wakeup_sources = 0;
  g_lpm_priv.config.output_port_enable = false;

  /* Check if we woke from deep standby */

  g_lpm_priv.status.deep_standby_reset = ra_lpm_check_deep_standby_reset();

  if (g_lpm_priv.status.deep_standby_reset)
    {
      /* Read wake-up source flags */

      g_lpm_priv.status.wakeup_flags =
        ((uint64_t)getreg8(R_SYSC_DPSIFR0)) |
        ((uint64_t)getreg8(R_SYSC_DPSIFR1) << 8) |
        ((uint64_t)getreg8(R_SYSC_DPSIFR2) << 16) |
        ((uint64_t)getreg8(R_SYSC_DPSIFR3) << 24);

      _info("Woke from deep standby, flags: 0x%llx\n",
             g_lpm_priv.status.wakeup_flags);
    }

  g_lpm_priv.initialized = true;

  _info("RA8 LPM initialized\n");

  return OK;
}

/****************************************************************************
 * Name: ra_lpm_configure
 *
 * Description:
 *   Configure low power mode settings
 *
 ****************************************************************************/

int ra_lpm_configure(FAR const struct ra_lpm_config_s *config)
{
  if (config == NULL)
    {
      return -EINVAL;
    }

  if (!g_lpm_priv.initialized)
    {
      return -EAGAIN;
    }

  memcpy(&g_lpm_priv.config, config, sizeof(struct ra_lpm_config_s));

  return OK;
}

/****************************************************************************
 * Name: ra_lpm_enter
 *
 * Description:
 *   Enter the specified low power mode
 *
 ****************************************************************************/

int ra_lpm_enter(enum ra_lpm_mode_e mode)
{
  struct ra_lpm_config_s *cfg = &g_lpm_priv.config;
  int ret = OK;

  if (!g_lpm_priv.initialized)
    {
      return -EAGAIN;
    }

  /* Store mode for status reporting */

  g_lpm_priv.status.last_mode = mode;

  switch (mode)
    {
      case RA_LPM_MODE_SLEEP:
        ret = ra_lpm_enter_sleep();
        break;

      case RA_LPM_MODE_DEEP_SLEEP:
        ret = ra_lpm_enter_deep_sleep();
        break;

      case RA_LPM_MODE_SW_STANDBY:
        cfg->mode = mode;
        ret = ra_lpm_enter_sw_standby(cfg);
        break;

      case RA_LPM_MODE_DEEP_SW_STANDBY_1:
      case RA_LPM_MODE_DEEP_SW_STANDBY_2:
      case RA_LPM_MODE_DEEP_SW_STANDBY_3:
        cfg->mode = mode;
        ret = ra_lpm_enter_deep_sw_standby(cfg);
        break;

      default:
        ret = -EINVAL;
        break;
    }

  return ret;
}

/****************************************************************************
 * Name: ra_lpm_sleep
 *
 * Description:
 *   Enter sleep mode
 *
 ****************************************************************************/

int ra_lpm_sleep(void)
{
  return ra_lpm_enter(RA_LPM_MODE_SLEEP);
}

/****************************************************************************
 * Name: ra_lpm_deep_sleep
 *
 * Description:
 *   Enter deep sleep mode
 *
 ****************************************************************************/

int ra_lpm_deep_sleep(void)
{
  return ra_lpm_enter(RA_LPM_MODE_DEEP_SLEEP);
}

/****************************************************************************
 * Name: ra_lpm_standby
 *
 * Description:
 *   Enter software standby mode
 *
 ****************************************************************************/

int ra_lpm_standby(uint64_t wakeup_sources)
{
  g_lpm_priv.config.wakeup_sources = wakeup_sources;
  return ra_lpm_enter(RA_LPM_MODE_SW_STANDBY);
}

/****************************************************************************
 * Name: ra_lpm_deep_standby
 *
 * Description:
 *   Enter deep software standby mode
 *
 ****************************************************************************/

int ra_lpm_deep_standby(uint64_t wakeup_sources)
{
  g_lpm_priv.config.wakeup_sources = wakeup_sources;
  return ra_lpm_enter(RA_LPM_MODE_DEEP_SW_STANDBY_1);
}

/****************************************************************************
 * Name: ra_lpm_get_status
 *
 * Description:
 *   Get current LPM status
 *
 ****************************************************************************/

int ra_lpm_get_status(FAR struct ra_lpm_status_s *status)
{
  if (status == NULL)
    {
      return -EINVAL;
    }

  memcpy(status, &g_lpm_priv.status, sizeof(struct ra_lpm_status_s));

  return OK;
}

/****************************************************************************
 * Name: ra_lpm_clear_wakeup_flags
 *
 * Description:
 *   Clear wake-up source flags
 *
 ****************************************************************************/

void ra_lpm_clear_wakeup_flags(void)
{
  ra_lpm_protect_disable();

  putreg8(0, R_SYSC_DPSIFR0);
  putreg8(0, R_SYSC_DPSIFR1);
  putreg8(0, R_SYSC_DPSIFR2);
  putreg8(0, R_SYSC_DPSIFR3);

  ra_lpm_protect_enable();

  g_lpm_priv.status.wakeup_flags = 0;
}

/****************************************************************************
 * Name: ra_lpm_io_keep_clear
 *
 * Description:
 *   Clear the IOKEEP bit after waking from deep standby
 *
 ****************************************************************************/

void ra_lpm_io_keep_clear(void)
{
  uint8_t dpsbycr;

  ra_lpm_protect_disable();

  dpsbycr = getreg8(R_SYSC_DPSBYCR);
  dpsbycr &= ~R_SYSC_DPSBYCR_IOKEEP;
  putreg8(dpsbycr, R_SYSC_DPSBYCR);

  ra_lpm_protect_enable();
}

/****************************************************************************
 * Name: ra_lpm_check_deep_standby_reset
 *
 * Description:
 *   Check if system was reset from deep standby mode
 *
 ****************************************************************************/

bool ra_lpm_check_deep_standby_reset(void)
{
  /* Check DPSRSTF bit in RSTSR0 register */

  return (getreg8(R_SYSC_RSTSR0) & R_SYSC_RSTSR0_DPSRSTF) != 0;
}

#ifdef CONFIG_PM
/****************************************************************************
 * Name: ra_pm_initialize
 *
 * Description:
 *   Initialize PM and register with NuttX PM framework
 *
 ****************************************************************************/

int ra_pm_initialize(void)
{
  int ret;

  /* Initialize LPM first */

  ret = ra_lpm_initialize();
  if (ret < 0)
    {
      return ret;
    }

  /* Register PM callbacks */

  g_pm_callback.prepare = ra_pm_prepare;
  g_pm_callback.notify = ra_pm_notify;

  ret = pm_register(&g_pm_callback);
  if (ret < 0)
    {
      pwmerr("Failed to register PM callbacks: %d\n", ret);
      return ret;
    }

  _info("RA8 PM registered with NuttX PM framework\n");

  return OK;
}
#endif /* CONFIG_PM */

/****************************************************************************
 * Name: ra_pmstop
 *
 * Description:
 *   Enter sleep or deep sleep mode
 *
 * Input Parameters:
 *   deep - true for deep sleep, false for regular sleep
 *
 ****************************************************************************/

void ra_pmstop(bool deep)
{
  if (deep)
    {
      ra_lpm_enter(RA_LPM_MODE_DEEP_SLEEP);
    }
  else
    {
      ra_lpm_enter(RA_LPM_MODE_SLEEP);
    }
}

/****************************************************************************
 * Name: ra_pmstandby
 *
 * Description:
 *   Enter software standby mode
 *
 ****************************************************************************/

void ra_pmstandby(void)
{
  ra_lpm_enter(RA_LPM_MODE_SW_STANDBY);
}

#endif /* CONFIG_RA_LPM */

/****************************************************************************
 * Name: arm_pminitialize
 *
 * Description:
 *   Initialize power management support. Called from up_initialize().
 *   This function is a required weak function that can be overridden by
 *   architecture-specific power management implementations.
 *
 ****************************************************************************/

#ifdef CONFIG_PM
void arm_pminitialize(void)
{
#ifdef CONFIG_RA_LPM
  /* Initialize LPM driver */

  ra_lpm_initialize();

  /* Register with PM framework if configured */

#ifdef CONFIG_RA_LPM_PM_INTEGRATION
  ra_pm_initialize();
#endif
#endif /* CONFIG_RA_LPM */
}
#endif /* CONFIG_PM */

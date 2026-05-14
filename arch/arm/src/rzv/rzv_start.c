/****************************************************************************
 * arch/arm/src/rzv/rzv_start.c
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

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <debug.h>
#include <string.h>

#include <nuttx/init.h>
#include <nuttx/arch.h>
#include <nuttx/irq.h>
#include <arch/board/board.h>

#include "chip.h"
#include "arm_internal.h"
#include "barriers.h"
#include "cp15_cacheops.h"
#include "mpu.h"
#include "rzv_start.h"
#include "rzv_clock.h"
#include "rzv_lowputc.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ACTLR register bits for Cortex-R8 */
#define ACTLR_ATCMPCEN              (1 << 25)  /* ATCM ECC enable */
#define ACTLR_B0TCMPCEN             (1 << 26)  /* B0TCM ECC enable */
#define ACTLR_B1TCMPCEN             (1 << 27)  /* B1TCM ECC enable */

/* SCTLR register bits */
#define SCTLR_M                     (1 << 0)   /* MMU/MPU enable */
#define SCTLR_A                     (1 << 1)   /* Alignment check enable */
#define SCTLR_C                     (1 << 2)   /* Data/Unified cache enable */
#define SCTLR_Z                     (1 << 11)  /* Branch prediction enable */
#define SCTLR_I                     (1 << 12)  /* Instruction cache enable */
#define SCTLR_V                     (1 << 13)  /* High vectors */

/* Use the standard NuttX approach for idle stack */
#ifndef CONFIG_IDLETHREAD_STACKSIZE
#  define CONFIG_IDLETHREAD_STACKSIZE 2048
#endif

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* Note: g_idle_topstack is defined in armv7-r/arm_head.S */

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Reference counter for register protection */
static volatile uint32_t g_protect_counters[3] =
{
  0, 0, 0
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: showprogress
 *
 * Description:
 *   Print a character on the UART to show boot status.
 *
 ****************************************************************************/

#ifdef CONFIG_DEBUG_FEATURES
#define showprogress(c) rzv_lowputc(c)
#else
#define showprogress(c)
#endif

/****************************************************************************
 * Name: rzv_enable_tcm
 *
 * Description:
 *   Enable ITCM and DTCM with ECC if supported
 *
 ****************************************************************************/

static inline void rzv_enable_tcm(void)
{
  uint32_t actlr;

  /* Read Auxiliary Control Register */
  __asm__ __volatile__
  (
    "mrc p15, 0, %0, c1, c0, 1"
    : "=r" (actlr)
    :
    : "memory"
  );

  /* Enable ECC for TCMs if available */
  actlr |= ACTLR_ATCMPCEN | ACTLR_B0TCMPCEN | ACTLR_B1TCMPCEN;

  /* Write back */
  __asm__ __volatile__
  (
    "mcr p15, 0, %0, c1, c0, 1"
    :
    : "r" (actlr)
    : "memory"
  );

  ARM_ISB();
  ARM_DSB();
}

/****************************************************************************
 * Name: rzv_enable_caches
 *
 * Description:
 *   Enable instruction and data caches for Cortex-R8
 *
 ****************************************************************************/

static inline void rzv_enable_caches(void)
{
  uint32_t sctlr;

  /* Invalidate instruction cache */
  cp15_invalidate_icache();

  /* Invalidate data cache */
  cp15_invalidate_dcache_all();

  /* Read System Control Register */
  __asm__ __volatile__
  (
    "mrc p15, 0, %0, c1, c0, 0"
    : "=r" (sctlr)
    :
    : "memory"
  );

  /* Enable instruction cache, data cache, and branch prediction */
  sctlr |= SCTLR_I | SCTLR_C | SCTLR_Z;

  /* Write back SCTLR */
  __asm__ __volatile__
  (
    "mcr p15, 0, %0, c1, c0, 0"
    :
    : "r" (sctlr)
    : "memory"
  );

  ARM_ISB();
  ARM_DSB();
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_ram_init
 *
 * Description:
 *   Initialize RAM sections (clear BSS, copy initialized data)
 *
 ****************************************************************************/

void rzv_ram_init(void)
{
  uint32_t *dest;

  /* Clear .bss section - zero-initialized data */
  for (dest = (uint32_t *)&_sbss; dest < (uint32_t *)&_ebss; )
    {
      *dest++ = 0;
    }

  /* The CR8 linker script emits Renesas loader metadata for ITCM/SRAM/DDR
   * copy ranges.  Those ranges are loaded before __start; _sdata/_edata are
   * image metadata addresses, not a single RAM .data run range.
   */

  ARM_DSB();
}

/****************************************************************************
 * Name: rzv_register_protect_disable
 *
 * Description:
 *   Disable register write protection for critical system registers.
 *   Uses reference counting to allow nested calls.
 *
 ****************************************************************************/

void rzv_register_protect_disable(rzv_reg_protect_t regs_to_unprotect)
{
  /* For RZV2H, most system registers don't have protection like RA8's PRCR.
   * GPIO PWPR protection is handled separately in rzv_gpio.c.
   * This function is provided for API compatibility and future extensions.
   */
  if (regs_to_unprotect < 3)
    {
      irqstate_t flags = enter_critical_section();
      g_protect_counters[regs_to_unprotect]++;
      leave_critical_section(flags);
    }
}

/****************************************************************************
 * Name: rzv_register_protect_enable
 *
 * Description:
 *   Enable register write protection for critical system registers.
 *   Uses reference counting - only enables when counter reaches zero.
 *
 ****************************************************************************/

void rzv_register_protect_enable(rzv_reg_protect_t regs_to_protect)
{
  if (regs_to_protect < 3)
    {
      irqstate_t flags = enter_critical_section();
      if (g_protect_counters[regs_to_protect] > 0)
        {
          g_protect_counters[regs_to_protect]--;
        }
      leave_critical_section(flags);
    }
}

extern uint32_t _vectors;  /* from arm_vectortab.S, placed by linker @ ITCM 0 */

static inline void rzv_set_vbar(void)
{
  uint32_t vbar = (uint32_t)(uintptr_t)&_vectors;
  uint32_t sctlr;

  DEBUGASSERT((vbar & 0x1F) == 0);
  __asm__ __volatile__
  (
    "mcr p15, 0, %0, c12, c0, 0\n"   /* VBAR */
    :: "r" (vbar) : "memory"
  );

  __asm__ __volatile__
  (
    "mrc p15, 0, %0, c1, c0, 0"
    : "=r" (sctlr)
    :
    : "memory"
  );

  sctlr &= ~SCTLR_V;

  __asm__ __volatile__
  (
    "mcr p15, 0, %0, c1, c0, 0"
    :
    : "r" (sctlr)
    : "memory"
  );

  ARM_DSB();
  ARM_ISB();
}

/****************************************************************************
 * Name: arm_boot
 *
 * Description:
 *   Complete boot sequence and start NuttX kernel.
 *   This is called from ARMv7-R arm_head.S after initial CPU setup.
 *
 ****************************************************************************/

void arm_boot(void)
{
  /* Disable interrupts during early boot */
  __asm__ __volatile__ ("cpsid i" : : : "memory");

  /* Route exceptions to linker-placed _vectors at ITCM 0 */
  rzv_set_vbar();

  showprogress('A');

  /* Enable TCM with ECC */
  rzv_enable_tcm();

  showprogress('B');

  /* Configure clocks early - needed for peripherals */
  rzv_clock_config();

  showprogress('C');

  /* Initialize RAM sections (BSS and DATA) */
  rzv_ram_init();

  showprogress('D');

  /* Enable caches and branch prediction */
  rzv_enable_caches();

  showprogress('E');

  /* Configure low-level serial for early debug output */
  rzv_lowsetup();

  showprogress('F');

  /* Perform early serial initialization if configured */
#ifdef USE_EARLYSERIALINIT
  rzv_earlyserialinit();
#endif

  showprogress('G');

  /* Initialize board-specific hardware */
  rzv_board_initialize();

  showprogress('H');

  /* Then start NuttX */
  showprogress('\r');
  showprogress('\n');

  nx_start();

  /* Should never return */
  for (; ; );
}

/****************************************************************************
 * Name: up_backtrace
 *
 * Description:
 *   Get backtrace from specified context. This function is used to get
 *   the backtrace when an exception occurred.
 *   Note: Frame-pointer based backtrace is not yet implemented for RZV.
 *
 ****************************************************************************/

int up_backtrace(struct tcb_s *tcb, void **buffer, int size, int skip)
{
  /* Frame-pointer based backtrace not yet implemented */
  return 0;
}

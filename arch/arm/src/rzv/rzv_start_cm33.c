/****************************************************************************
 * arch/arm/src/rzv/rzv_start_cm33.c
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
#include <assert.h>
#include <debug.h>

#include <nuttx/init.h>
#include <arch/board/board.h>

#include "arm_internal.h"
#include "nvic.h"
#include "barriers.h"

#include "rzv_start_cm33.h"
#include "hardware/rzv_cpg.h"
#include "hardware/rzv_sysc.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

#ifdef USE_EARLYSERIALINIT
void arm_earlyserialinit(void)
{
  /* For CM33, serial init is deferred to rzv_lowsetup */
}
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Memory Configuration for CM33 Core
 * RZV2H CM33 Memory Map:
 * - ATCM: 0x00000000 - 0x0001FFFF (128KB)
 * - System RAM: 0x22000000 - 0x2207FFFF (512KB)
 * - Peripheral: 0x10000000 - 0x1FFFFFFF
 * - External: 0x40000000 onwards
 */

#define CM33_VECTOR_BASE        0x00000000  /* Reset vector at ATCM start */

/* System Control Space (SCS) Base Addresses for ARMv8-M */
#define SCS_BASE                0xE000E000
#define SCB_BASE                (SCS_BASE + 0x0D00)
#define SYSTICK_BASE            (SCS_BASE + 0x0010)

/* System Control Block (SCB) Registers */
#define SCB_CPUID               (SCB_BASE + 0x000)  /* CPUID Base Register */
#define SCB_ICSR                (SCB_BASE + 0x004)  /* Interrupt Control State */
#define SCB_VTOR                (SCB_BASE + 0x008)  /* Vector Table Offset */
#define SCB_AIRCR               (SCB_BASE + 0x00C)  /* Application Interrupt/Reset Control */
#define SCB_SCR                 (SCB_BASE + 0x010)  /* System Control Register */
#define SCB_CCR                 (SCB_BASE + 0x014)  /* Configuration Control */
#define SCB_SHPR1               (SCB_BASE + 0x018)  /* System Handler Priority 1 */
#define SCB_SHPR2               (SCB_BASE + 0x01C)  /* System Handler Priority 2 */
#define SCB_SHPR3               (SCB_BASE + 0x020)  /* System Handler Priority 3 */
#define SCB_SHCSR               (SCB_BASE + 0x024)  /* System Handler Control and State */
#define SCB_CFSR                (SCB_BASE + 0x028)  /* Configurable Fault Status */
#define SCB_MMFAR               (SCB_BASE + 0x034)  /* MemManage Fault Address */
#define SCB_BFAR                (SCB_BASE + 0x038)  /* BusFault Address */

/* SCB_CCR Register Bits */
#define SCB_CCR_IC              (1 << 17)  /* Instruction cache enable */
#define SCB_CCR_DC              (1 << 16)  /* Data cache enable */
#define SCB_CCR_STKALIGN        (1 << 9)   /* Stack alignment */
#define SCB_CCR_BFHFNMIGN       (1 << 8)   /* Ignore precise data access faults */
#define SCB_CCR_DIV_0_TRP       (1 << 4)   /* Divide by zero trap */
#define SCB_CCR_UNALIGN_TRP     (1 << 3)   /* Unaligned access trap */

/* Cache Control */
#define CCR_ICACHE_ENABLE       SCB_CCR_IC
#define CCR_DCACHE_ENABLE       SCB_CCR_DC

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Vector table - defined in linker script */
extern uint32_t _vectors[];

/* Initial stack pointer - defined in linker script */
extern uint32_t _estack;

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* The main entry point to the user program starts */
const uintptr_t g_idle_topstack = (uintptr_t)&_estack;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_cm33_cpu_init
 *
 * Description:
 *   Initialize CM33 core-specific features (caches, FPU, etc.)
 *   Based on FSP bsp_cm33_core.c initialization
 *
 ****************************************************************************/

static void rzv_cm33_cpu_init(void)
{
  uint32_t regval;

  /* Set vector table base address */
  putreg32((uint32_t)_vectors, SCB_VTOR);
  ARM_DSB();
  ARM_ISB();

  /* Configure System Control Register (SCR) */
  regval = getreg32(SCB_SCR);
  regval &= ~(1 << 2);  /* Clear SLEEPDEEP for WFI behavior */
  putreg32(regval, SCB_SCR);

  /* Configure Configuration Control Register (CCR) */
  regval = getreg32(SCB_CCR);

  /* Enable stack alignment to 8 bytes */
  regval |= SCB_CCR_STKALIGN;

  /* Enable divide-by-zero trap */
  regval |= SCB_CCR_DIV_0_TRP;

  /* Enable unaligned access trap for safety */
#ifdef CONFIG_ARMV8M_UNALIGN_TRAP
  regval |= SCB_CCR_UNALIGN_TRP;
#endif

  putreg32(regval, SCB_CCR);
  ARM_DSB();
  ARM_ISB();

#ifdef CONFIG_ARMV8M_ICACHE
  /* Enable instruction cache if configured */
  regval = getreg32(SCB_CCR);
  regval |= CCR_ICACHE_ENABLE;
  putreg32(regval, SCB_CCR);
  ARM_DSB();
  ARM_ISB();
#endif

#ifdef CONFIG_ARMV8M_DCACHE
  /* Enable data cache if configured */
  regval = getreg32(SCB_CCR);
  regval |= CCR_DCACHE_ENABLE;
  putreg32(regval, SCB_CCR);
  ARM_DSB();
  ARM_ISB();
#endif

#ifdef CONFIG_ARCH_FPU
  /* Enable FPU (Cortex-M33 has optional FPU) */
  /* Set CP10 and CP11 to full access in CPACR */
  regval = getreg32(SCB_BASE + 0x088);  /* CPACR offset */
  regval |= (0xF << 20);  /* CP10 and CP11 full access */
  putreg32(regval, SCB_BASE + 0x088);
  ARM_DSB();
  ARM_ISB();
#endif
}

/****************************************************************************
 * Name: rzv_cm33_clock_init
 *
 * Description:
 *   Initialize CM33-specific clocks.
 *   The main system clocks are initialized by the bootloader or CA55,
 *   but CM33 may need specific peripheral clocks enabled.
 *
 ****************************************************************************/

static void rzv_cm33_clock_init(void)
{
  /* CM33 clock initialization
   * In RZV2H, the main clock tree is managed by CPG (Clock Pulse Generator)
   * which is typically initialized by the primary boot core (CA55).
   * CM33 just needs to enable its specific peripheral clocks.
   */

#ifdef CONFIG_RZV_CLOCK_PLL
  /* PLL should already be configured by boot core */
  /* Verify PLL lock status if needed */
#endif

  /* Enable CM33-specific peripheral clocks as needed */
  /* This will be done by individual peripheral drivers */
}

/****************************************************************************
 * Name: rzv_cm33_lowsetup
 *
 * Description:
 *   Called at the very beginning of _start to perform low-level
 *   initialization including:
 *   - CPU core initialization
 *   - Basic clock setup
 *   - Early UART initialization (if configured)
 *
 ****************************************************************************/

static void rzv_cm33_lowsetup(void)
{
  /* Initialize CM33 CPU core features */
  rzv_cm33_cpu_init();

  /* Initialize clocks */
  rzv_cm33_clock_init();

  /* Early serial initialization for debug output */
#ifdef USE_EARLYSERIALINIT
  arm_earlyserialinit();
#endif
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: __start
 *
 * Description:
 *   This is the CM33 reset entry point. This function is called from
 *   the vector table after a reset. It performs early initialization
 *   and then calls nx_start() to begin NuttX execution.
 *
 * Entry Conditions:
 *   - CM33 has just been reset
 *   - Stack pointer is set by hardware from vector table
 *   - Interrupts are disabled
 *   - No initialization has been performed yet
 *
 ****************************************************************************/

void __start(void) noinstrument_function;
void __start(void)
{
  const uint32_t *src;
  uint32_t *dest;

  /* Disable interrupts during initialization */
  __asm__ __volatile__ ("cpsid i" : : : "memory");

  /* Configure the UART so that we can get debug output as soon as possible */
  rzv_cm33_lowsetup();

#ifdef CONFIG_BOOT_RUNFROMFLASH
  /* Copy .data section from Flash to RAM */
  extern const uint32_t _eronly;      /* Start of .data in Flash */
  extern uint32_t _sdata;       /* Start of .data in RAM */
  extern uint32_t _edata;       /* End of .data in RAM */

  src  = &_eronly;
  dest = &_sdata;

  while (dest < &_edata)
    {
      *dest++ = *src++;
    }
#endif

  /* Clear .bss section */
  extern uint32_t _sbss;        /* Start of .bss */
  extern uint32_t _ebss;        /* End of .bss */

  dest = &_sbss;
  while (dest < &_ebss)
    {
      *dest++ = 0;
    }

  /* Perform early serial initialization */
#ifdef USE_EARLYSERIALINIT
  arm_earlyserialinit();
#endif

  /* Initialize onboard resources */
  rzv_board_initialize();

  /* Then start NuttX */
  nx_start();

  /* Shouldn't get here */
  for (; ; );
}

/****************************************************************************
 * Name: arm_data_initialize
 *
 * Description:
 *   Clear uninitialized data (BSS). This is done by __start but is
 *   provided as a separate function for potential use by other code.
 *
 ****************************************************************************/

void arm_data_initialize(void)
{
  /* This is already done in __start for CM33 */
  /* Kept for API compatibility */
}

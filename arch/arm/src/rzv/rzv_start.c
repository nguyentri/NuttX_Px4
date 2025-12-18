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
#include <assert.h>
#include <debug.h>

#include <nuttx/irq.h>

#include <nuttx/init.h>
#include <arch/board/board.h>

#include "chip.h"
#include "arm_internal.h"
#include "rzv_start.h"
#include "rzv_clock.h"
#include "rzv_lowputc.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* g_idle_topstack: _sbss is the start of the BSS region as defined by the
 * linker script. _ebss lies at the end of the BSS region. The idle task
 * stack starts at the end of BSS and is of size CONFIG_IDLETHREAD_STACKSIZE.
 * The IDLE thread is the thread that the system boots on and, eventually,
 * becomes the IDLE, do nothing task that runs only when there is nothing
 * else to run.  The heap continues from there until the end of memory.
 * The IDLE thread stack is quite small.
 */

//const uintptr_t g_idle_topstack = (uintptr_t)&_ebss + CONFIG_IDLETHREAD_STACKSIZE;

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
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: __start
 *
 * Description:
 *   This is the reset entry point.
 *
 ****************************************************************************/

int main(void)
{
  const uint32_t *src;
  uint32_t *dest;

  /* Disable interrupts */

  //up_irq_disable();

  /* Configure the uart so that we can get debug output as soon as possible */

  rzv_clock_config();
  rzv_lowsetup();
  showprogress('A');

  /* Clear .bss.  We'll do this inline (vs. calling memset) just to be
   * certain that there are no issues with the state of global variables.
   */

  for (dest = (uint32_t *)_sbss; dest < (uint32_t *)_ebss; )
    {
      *dest++ = 0;
    }

  showprogress('B');

  /* Move the initialized data section from his temporary holding spot in
   * FLASH into the correct place in SRAM.  The correct place in SRAM is
   * give by _sdata and _edata.  The temporary location is in FLASH at the
   * end of all of the other read-only data (.text, .rodata) at _eronly.
   */

  for (src = (const uint32_t *)_eronly,
       dest = (uint32_t *)_sdata; dest < (uint32_t *)_edata;
      )
    {
      *dest++ = *src++;
    }

  showprogress('C');

  /* Perform early serial initialization */

#ifdef USE_EARLYSERIALINIT
  rzv_earlyserialinit();
#endif
  showprogress('D');

  /* Initialize onboard resources */

  //rzv_board_initialize();
  showprogress('E');

  /* Then start NuttX */

  showprogress('\r');
  showprogress('\n');
  nx_start();

  return 0; /* Should never return */
}

/* Minimal arm_boot that delegates to nx_start().  This will start the
 * NuttX kernel.  A real implementation should perform architecture
 * specific memory initialization before calling nx_start().
 */
void arm_boot(void)
{
  main();
}

/* Provide a trivial up_backtrace stub when frame-pointer based
 * backtrace implementation is not compiled in.
 */
int up_backtrace(struct tcb_s *tcb, void **buffer, int size, int skip)
{
  (void)tcb;
  (void)buffer;
  (void)size;
  (void)skip;
  return 0;
}
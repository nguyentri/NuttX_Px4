/****************************************************************************
 * arch/arm/src/ra8/ra_lowputc.c
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

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/spinlock.h>

#include "arm_internal.h"
#include "ra_gpio.h"
#include "chip.h"
#include "ra_mstp.h"
#include "hardware/ra_memorymap.h"

/* The board.h file may redefine pin configurations defined in ra_pinmap.h */

#include <arch/board/board.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Check for RTT console */

#ifdef CONFIG_SERIAL_RTT_CONSOLE
#  define HAVE_RTT_CONSOLE 1
#endif

/* Is there a serial console?  It could be on SCI0-1 or USART0-3 */

#if defined(CONFIG_SCI0_SERIAL_CONSOLE) && defined(CONFIG_RA_SCI0_UART)
#undef CONFIG_SCI1_SERIAL_CONSOLE
#undef CONFIG_SCI2_SERIAL_CONSOLE
#undef CONFIG_SCI3_SERIAL_CONSOLE
#undef CONFIG_SCI4_SERIAL_CONSOLE
#undef CONFIG_SCI9_SERIAL_CONSOLE
#define HAVE_CONSOLE    1
#elif defined(CONFIG_SCI1_SERIAL_CONSOLE) && defined(CONFIG_RA_SCI1_UART)
#undef CONFIG_SCI0_SERIAL_CONSOLE
#undef CONFIG_SCI2_SERIAL_CONSOLE
#undef CONFIG_SCI3_SERIAL_CONSOLE
#undef CONFIG_SCI4_SERIAL_CONSOLE
#undef CONFIG_SCI9_SERIAL_CONSOLE
#define HAVE_CONSOLE    1
#elif defined(CONFIG_SCI2_SERIAL_CONSOLE) && defined(CONFIG_RA_SCI2_UART)
#undef CONFIG_SCI0_SERIAL_CONSOLE
#undef CONFIG_SCI1_SERIAL_CONSOLE
#undef CONFIG_SCI3_SERIAL_CONSOLE
#undef CONFIG_SCI4_SERIAL_CONSOLE
#undef CONFIG_SCI9_SERIAL_CONSOLE
#define HAVE_CONSOLE    1
#elif defined(CONFIG_SCI3_SERIAL_CONSOLE) && defined(CONFIG_RA_SCI3_UART)
#undef CONFIG_SCI0_SERIAL_CONSOLE
#undef CONFIG_SCI1_SERIAL_CONSOLE
#undef CONFIG_SCI2_SERIAL_CONSOLE
#undef CONFIG_SCI4_SERIAL_CONSOLE
#undef CONFIG_SCI9_SERIAL_CONSOLE
#define HAVE_CONSOLE    1
#elif defined(CONFIG_SCI4_SERIAL_CONSOLE) && defined(CONFIG_RA_SCI4_UART)
#undef CONFIG_SCI0_SERIAL_CONSOLE
#undef CONFIG_SCI1_SERIAL_CONSOLE
#undef CONFIG_SCI2_SERIAL_CONSOLE
#undef CONFIG_SCI3_SERIAL_CONSOLE
#undef CONFIG_SCI9_SERIAL_CONSOLE
#define HAVE_CONSOLE    1
#elif defined(CONFIG_SCI9_SERIAL_CONSOLE) && defined(CONFIG_RA_SCI9_UART)
#undef CONFIG_SCI0_SERIAL_CONSOLE
#undef CONFIG_SCI1_SERIAL_CONSOLE
#undef CONFIG_SCI2_SERIAL_CONSOLE
#undef CONFIG_SCI3_SERIAL_CONSOLE
#undef CONFIG_SCI4_SERIAL_CONSOLE
#define HAVE_CONSOLE    1
#else
#if !defined(HAVE_RTT_CONSOLE) && !defined(HAVE_CONSOLE)
#warning "No valid console configuration"
#endif

#undef CONFIG_SCI0_SERIAL_CONSOLE
#undef CONFIG_SCI1_SERIAL_CONSOLE
#undef CONFIG_SCI2_SERIAL_CONSOLE
#undef CONFIG_SCI3_SERIAL_CONSOLE
#undef CONFIG_SCI4_SERIAL_CONSOLE
#undef HAVE_CONSOLE
#endif

#if defined(HAVE_CONSOLE) && !defined(HAVE_RTT_CONSOLE)

/* Select USART parameters for the selected console */

#  if defined(CONFIG_SCI0_SERIAL_CONSOLE)
#    define RA_CONSOLE_BASE     R_SCI_B_CH_BASE(0)
#    define RA_CONSOLE_MTSP     R_MSTP_MSTPCRB_SCI0
#    define RA_CONSOLE_BAUD     CONFIG_SCI0_BAUD
#    define RA_CONSOLE_BITS     CONFIG_SCI0_BITS
#    define RA_CONSOLE_PARITY   CONFIG_SCI0_PARITY
#    define RA_CONSOLE_2STOP    CONFIG_SCI0_2STOP
#  elif defined(CONFIG_SCI1_SERIAL_CONSOLE)
#    define RA_CONSOLE_BASE     R_SCI_B_CH_BASE(1)
#    define RA_CONSOLE_MTSP     R_MSTP_MSTPCRB_SCI1
#    define RA_CONSOLE_BAUD     CONFIG_SCI1_BAUD
#    define RA_CONSOLE_BITS     CONFIG_SCI1_BITS
#    define RA_CONSOLE_PARITY   CONFIG_SCI1_PARITY
#    define RA_CONSOLE_2STOP    CONFIG_SCI1_2STOP
#  elif defined(CONFIG_SCI2_SERIAL_CONSOLE)
#    define RA_CONSOLE_BASE     R_SCI_B_CH_BASE(2)
#    define RA_CONSOLE_MTSP     R_MSTP_MSTPCRB_SCI2
#    define RA_CONSOLE_BAUD     CONFIG_SCI2_BAUD
#    define RA_CONSOLE_BITS     CONFIG_SCI2_BITS
#    define RA_CONSOLE_PARITY   CONFIG_SCI2_PARITY
#    define RA_CONSOLE_2STOP    CONFIG_SCI2_2STOP
#  elif defined(CONFIG_SCI3_SERIAL_CONSOLE)
#    define RA_CONSOLE_BASE     R_SCI_B_CH_BASE(3)
#    define RA_CONSOLE_MTSP     R_MSTP_MSTPCRB_SCI3
#    define RA_CONSOLE_BAUD     CONFIG_SCI3_BAUD
#    define RA_CONSOLE_BITS     CONFIG_SCI3_BITS
#    define RA_CONSOLE_PARITY   CONFIG_SCI3_PARITY
#    define RA_CONSOLE_2STOP    CONFIG_SCI3_2STOP
#  elif defined(CONFIG_SCI4_SERIAL_CONSOLE)
#    define RA_CONSOLE_BASE     R_SCI_B_CH_BASE(4)
#    define RA_CONSOLE_MTSP     R_MSTP_MSTPCRB_SCI4
#    define RA_CONSOLE_BAUD     CONFIG_SCI4_BAUD
#    define RA_CONSOLE_BITS     CONFIG_SCI4_BITS
#    define RA_CONSOLE_PARITY   CONFIG_SCI4_PARITY
#    define RA_CONSOLE_2STOP    CONFIG_SCI4_2STOP
#  elif defined(CONFIG_SCI5_SERIAL_CONSOLE)
#    define RA_CONSOLE_BASE     R_SCI_B_CH_BASE(5)
#    define RA_CONSOLE_MTSP     R_MSTP_MSTPCRB_SCI5
#    define RA_CONSOLE_BAUD     CONFIG_SCI5_BAUD
#    define RA_CONSOLE_BITS     CONFIG_SCI5_BITS
#    define RA_CONSOLE_PARITY   CONFIG_SCI5_PARITY
#    define RA_CONSOLE_2STOP    CONFIG_SCI5_2STOP
#  elif defined(CONFIG_SCI6_SERIAL_CONSOLE)
#    define RA_CONSOLE_BASE     R_SCI_B_CH_BASE(6)
#    define RA_CONSOLE_MTSP     R_MSTP_MSTPCRB_SCI6
#    define RA_CONSOLE_BAUD     CONFIG_SCI6_BAUD
#    define RA_CONSOLE_BITS     CONFIG_SCI6_BITS
#    define RA_CONSOLE_PARITY   CONFIG_SCI6_PARITY
#    define RA_CONSOLE_2STOP    CONFIG_SCI6_2STOP
#  elif defined(CONFIG_SCI7_SERIAL_CONSOLE)
#    define RA_CONSOLE_BASE     R_SCI_B_CH_BASE(7)
#    define RA_CONSOLE_MTSP     R_MSTP_MSTPCRB_SCI7
#    define RA_CONSOLE_BAUD     CONFIG_SCI7_BAUD
#    define RA_CONSOLE_BITS     CONFIG_SCI7_BITS
#    define RA_CONSOLE_PARITY   CONFIG_SCI7_PARITY
#    define RA_CONSOLE_2STOP    CONFIG_SCI7_2STOP
#  elif defined(CONFIG_SCI8_SERIAL_CONSOLE)
#    define RA_CONSOLE_BASE     R_SCI_B_CH_BASE(8)
#    define RA_CONSOLE_MTSP     R_MSTP_MSTPCRB_SCI8
#    define RA_CONSOLE_BAUD     CONFIG_SCI8_BAUD
#    define RA_CONSOLE_BITS     CONFIG_SCI8_BITS
#    define RA_CONSOLE_PARITY   CONFIG_SCI8_PARITY
#    define RA_CONSOLE_2STOP    CONFIG_SCI8_2STOP
#  elif defined(CONFIG_SCI9_SERIAL_CONSOLE)
#    define RA_CONSOLE_BASE     R_SCI_B_CH_BASE(9)
#    define RA_CONSOLE_MTSP     R_MSTP_MSTPCRB_SCI9
#    define RA_CONSOLE_BAUD     CONFIG_SCI9_BAUD
#    define RA_CONSOLE_BITS     CONFIG_SCI9_BITS
#    define RA_CONSOLE_PARITY   CONFIG_SCI9_PARITY
#    define RA_CONSOLE_2STOP    CONFIG_SCI9_2STOP
#  else
#    error "No CONFIG_UARTn_SERIAL_CONSOLE Setting"
#  endif
#endif

/* Configuration ************************************************************/

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/
#ifdef HAVE_CONSOLE
static spinlock_t g_ra_lowputc_lock;
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: arm_lowputc
 *
 * Description:
 *   Output one byte on the serial console
 *
 ****************************************************************************/

void arm_lowputc(char ch)
{
#ifdef HAVE_CONSOLE
  irqstate_t flags;

  /* Timeout safe checking - allow reasonable time for UART to be ready */
  volatile uint32_t time_out = 100000;

  /* Wait for Transmit Data Register Empty (TDRE) flag in CSR register */
  while ((time_out > 0) && ((getreg32(RA_CONSOLE_BASE + R_SCI_B_CSR_OFFSET) & R_SCI_B_CSR_TDRE) == 0))
    {
        time_out--;
    }

  /* If timeout expired, UART is not ready - exit early to avoid hang */
  if (time_out == 0)
    {
      return;
    }

  /* Disable interrupts so that the test and the transmission are atomic */
  flags = spin_lock_irqsave(&g_ra_lowputc_lock);

  /* Double-check TDRE is still set before transmitting */
  if ((getreg32(RA_CONSOLE_BASE + R_SCI_B_CSR_OFFSET) & R_SCI_B_CSR_TDRE) != 0)
    {
      /* Send the character to TDR_BY register (byte access) */
      putreg8((uint32_t)ch, RA_CONSOLE_BASE + R_SCI_B_TDR_OFFSET);

      /* Clear TDRE flag by writing to CFCLR register */
      putreg32(R_SCI_B_CFCLR_TDREC, RA_CONSOLE_BASE + R_SCI_B_CFCLR_OFFSET);
    }

  spin_unlock_irqrestore(&g_ra_lowputc_lock, flags);
#endif
}

/****************************************************************************
 * Name: up_putc
 *
 * Description:
 *   Provide priority, low-level access to support OS debug writes
 *
 ****************************************************************************/

int up_putc(int ch)
{
#ifdef HAVE_CONSOLE
  arm_lowputc(ch);
#endif
  return ch;
}

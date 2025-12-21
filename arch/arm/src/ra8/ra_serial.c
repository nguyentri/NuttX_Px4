/****************************************************************************
 * arch/arm/src/ra8/ra_serial.c
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
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>

#ifdef CONFIG_SERIAL_TERMIOS
#include <termios.h>
#endif

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/fs/ioctl.h>
#include <nuttx/serial/serial.h>

#include <arch/board/board.h>

#include "arm_internal.h"
#include "chip.h"
#include "hardware/ra_memorymap.h"
#include "ra_mstp.h"
#include "ra_icu.h"
#include "ra_gpio.h"
#include "ra_clock.h"

#if defined (CONFIG_SERIAL_TXDMA) || defined (CONFIG_SERIAL_RXDMA)
#if defined CONFIG_RA_DMAC
#  include "ra_dmac.h"
#else
#  error "DMA support required for serial TXDMA or RXDMA"
#endif
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Default to FIFO mode if not explicitly disabled */
#if defined(CONFIG_RA_SCI_FIFO_MODE)
/* Set Trigger levels and release reset
* For RA8 SCI-B with 16-byte FIFO:
* RTRG: RX trigger level (configurable via Kconfig, default: 1 for low latency)
* TTRG: TX trigger level (configurable via Kconfig, default: 15 for efficiency)
* RSTRG: RTS flow control trigger (set to 15 = fifo_depth - 1)
*
* RX interrupt triggers when: count >= RTRG or timeout after 15 bit times
* TX interrupt triggers when: count <= TTRG (free space available)
*/
#ifndef CONFIG_RA_SCI_FIFO_RX_TRIGGER
#define CONFIG_RA_SCI_FIFO_RX_TRIGGER 1  /* Default: trigger on 1 byte */
#endif
#ifndef CONFIG_RA_SCI_FIFO_TX_TRIGGER
#define CONFIG_RA_SCI_FIFO_TX_TRIGGER 15 /* Default: trigger when ≤15 in FIFO */
#endif
#endif

/* Is there a serial console?  */

#if defined(CONFIG_SCI0_SERIAL_CONSOLE) && defined(CONFIG_RA_SCI0_UART)
#undef CONFIG_SCI1_SERIAL_CONSOLE
#undef CONFIG_SCI2_SERIAL_CONSOLE
#undef CONFIG_SCI3_SERIAL_CONSOLE
#undef CONFIG_SCI4_SERIAL_CONSOLE
#undef CONFIG_SCI9_SERIAL_CONSOLE
#define HAVE_CONSOLE        1
#elif defined(CONFIG_SCI1_SERIAL_CONSOLE) && defined(CONFIG_RA_SCI1_UART)
#undef CONFIG_SCI0_SERIAL_CONSOLE
#undef CONFIG_SCI2_SERIAL_CONSOLE
#undef CONFIG_SCI3_SERIAL_CONSOLE
#undef CONFIG_SCI4_SERIAL_CONSOLE
#undef CONFIG_SCI9_SERIAL_CONSOLE
#define HAVE_CONSOLE        1
#elif defined(CONFIG_SCI2_SERIAL_CONSOLE) && defined(CONFIG_RA_SCI2_UART)
#undef CONFIG_SCI0_SERIAL_CONSOLE
#undef CONFIG_SCI1_SERIAL_CONSOLE
#undef CONFIG_SCI3_SERIAL_CONSOLE
#undef CONFIG_SCI4_SERIAL_CONSOLE
#undef CONFIG_SCI9_SERIAL_CONSOLE
#define HAVE_CONSOLE        1
#elif defined(CONFIG_SCI3_SERIAL_CONSOLE) && defined(CONFIG_RA_SCI3_UART)
#undef CONFIG_SCI0_SERIAL_CONSOLE
#undef CONFIG_SCI1_SERIAL_CONSOLE
#undef CONFIG_SCI2_SERIAL_CONSOLE
#undef CONFIG_SCI4_SERIAL_CONSOLE
#undef CONFIG_SCI9_SERIAL_CONSOLE
#define HAVE_CONSOLE        1
#elif defined(CONFIG_SCI4_SERIAL_CONSOLE) && defined(CONFIG_RA_SCI4_UART)
#undef CONFIG_SCI0_SERIAL_CONSOLE
#undef CONFIG_SCI1_SERIAL_CONSOLE
#undef CONFIG_SCI2_SERIAL_CONSOLE
#undef CONFIG_SCI3_SERIAL_CONSOLE
#undef CONFIG_SCI5_SERIAL_CONSOLE
#undef CONFIG_SCI6_SERIAL_CONSOLE
#undef CONFIG_SCI7_SERIAL_CONSOLE
#undef CONFIG_SCI8_SERIAL_CONSOLE
#undef CONFIG_SCI9_SERIAL_CONSOLE
#define HAVE_CONSOLE        1
#elif defined(CONFIG_SCI5_SERIAL_CONSOLE) && defined(CONFIG_RA_SCI5_UART)
#undef CONFIG_SCI0_SERIAL_CONSOLE
#undef CONFIG_SCI1_SERIAL_CONSOLE
#undef CONFIG_SCI2_SERIAL_CONSOLE
#undef CONFIG_SCI3_SERIAL_CONSOLE
#undef CONFIG_SCI4_SERIAL_CONSOLE
#undef CONFIG_SCI6_SERIAL_CONSOLE
#undef CONFIG_SCI7_SERIAL_CONSOLE
#undef CONFIG_SCI8_SERIAL_CONSOLE
#undef CONFIG_SCI9_SERIAL_CONSOLE
#define HAVE_CONSOLE        1
#elif defined(CONFIG_SCI6_SERIAL_CONSOLE) && defined(CONFIG_RA_SCI6_UART)
#undef CONFIG_SCI0_SERIAL_CONSOLE
#undef CONFIG_SCI1_SERIAL_CONSOLE
#undef CONFIG_SCI2_SERIAL_CONSOLE
#undef CONFIG_SCI3_SERIAL_CONSOLE
#undef CONFIG_SCI4_SERIAL_CONSOLE
#undef CONFIG_SCI5_SERIAL_CONSOLE
#undef CONFIG_SCI7_SERIAL_CONSOLE
#undef CONFIG_SCI8_SERIAL_CONSOLE
#undef CONFIG_SCI9_SERIAL_CONSOLE
#define HAVE_CONSOLE        1
#elif defined(CONFIG_SCI7_SERIAL_CONSOLE) && defined(CONFIG_RA_SCI7_UART)
#undef CONFIG_SCI0_SERIAL_CONSOLE
#undef CONFIG_SCI1_SERIAL_CONSOLE
#undef CONFIG_SCI2_SERIAL_CONSOLE
#undef CONFIG_SCI3_SERIAL_CONSOLE
#undef CONFIG_SCI4_SERIAL_CONSOLE
#undef CONFIG_SCI5_SERIAL_CONSOLE
#undef CONFIG_SCI6_SERIAL_CONSOLE
#undef CONFIG_SCI8_SERIAL_CONSOLE
#undef CONFIG_SCI9_SERIAL_CONSOLE
#define HAVE_CONSOLE        1
#elif defined(CONFIG_SCI8_SERIAL_CONSOLE) && defined(CONFIG_RA_SCI8_UART)
#undef CONFIG_SCI0_SERIAL_CONSOLE
#undef CONFIG_SCI1_SERIAL_CONSOLE
#undef CONFIG_SCI2_SERIAL_CONSOLE
#undef CONFIG_SCI3_SERIAL_CONSOLE
#undef CONFIG_SCI4_SERIAL_CONSOLE
#undef CONFIG_SCI5_SERIAL_CONSOLE
#undef CONFIG_SCI6_SERIAL_CONSOLE
#undef CONFIG_SCI7_SERIAL_CONSOLE
#undef CONFIG_SCI9_SERIAL_CONSOLE
#define HAVE_CONSOLE        1
#elif defined(CONFIG_SCI9_SERIAL_CONSOLE) && defined(CONFIG_RA_SCI9_UART)
#undef CONFIG_SCI0_SERIAL_CONSOLE
#undef CONFIG_SCI1_SERIAL_CONSOLE
#undef CONFIG_SCI2_SERIAL_CONSOLE
#undef CONFIG_SCI3_SERIAL_CONSOLE
#undef CONFIG_SCI4_SERIAL_CONSOLE
#undef CONFIG_SCI5_SERIAL_CONSOLE
#undef CONFIG_SCI6_SERIAL_CONSOLE
#undef CONFIG_SCI7_SERIAL_CONSOLE
#undef CONFIG_SCI8_SERIAL_CONSOLE
#define HAVE_CONSOLE        1
#else
#if !defined(CONFIG_NO_SERIAL_CONSOLE) && !defined(CONFIG_SERIAL_RTT_CONSOLE)
#warning "No valid CONFIG_SCIn_SERIAL_CONSOLE Setting"
#endif

#undef CONFIG_SCI0_SERIAL_CONSOLE
#undef CONFIG_SCI1_SERIAL_CONSOLE
#undef CONFIG_SCI2_SERIAL_CONSOLE
#undef CONFIG_SCI3_SERIAL_CONSOLE
#undef CONFIG_SCI4_SERIAL_CONSOLE
#undef CONFIG_SCI5_SERIAL_CONSOLE
#undef CONFIG_SCI6_SERIAL_CONSOLE
#undef CONFIG_SCI7_SERIAL_CONSOLE
#undef CONFIG_SCI8_SERIAL_CONSOLE
#undef CONFIG_SCI9_SERIAL_CONSOLE
#undef HAVE_CONSOLE
#endif

/* First pick the console and ttys0. */

#if defined(CONFIG_SCI0_SERIAL_CONSOLE)
#define CONSOLE_DEV     g_uart0port /* UART0 is console */
#define TTYS0_DEV       g_uart0port /* UART0 is ttyS0 */
#define UART0_ASSIGNED  1
#elif defined(CONFIG_SCI1_SERIAL_CONSOLE)
#define CONSOLE_DEV     g_uart1port /* UART1 is console */
#define TTYS0_DEV       g_uart1port /* UART1 is ttyS0 */
#define UART1_ASSIGNED  1
#elif defined(CONFIG_SCI2_SERIAL_CONSOLE)
#define CONSOLE_DEV     g_uart2port /* UART2 is console */
#define TTYS0_DEV       g_uart2port /* UART2 is ttyS0 */
#define UART2_ASSIGNED  1
#elif defined(CONFIG_SCI3_SERIAL_CONSOLE)
#define CONSOLE_DEV     g_uart3port /* UART3 is console */
#define TTYS0_DEV       g_uart3port /* UART3 is ttyS0 */
#define UART3_ASSIGNED  1
#elif defined(CONFIG_SCI4_SERIAL_CONSOLE)
#define CONSOLE_DEV     g_uart4port /* UART4 is console */
#define TTYS0_DEV       g_uart4port /* UART4 is ttyS0 */
#define UART4_ASSIGNED  1
#elif defined(CONFIG_SCI5_SERIAL_CONSOLE)
#define CONSOLE_DEV     g_uart5port /* UART5 is console */
#define TTYS0_DEV       g_uart5port /* UART5 is ttyS0 */
#define UART5_ASSIGNED  1
#elif defined(CONFIG_SCI6_SERIAL_CONSOLE)
#define CONSOLE_DEV     g_uart6port /* UART6 is console */
#define TTYS0_DEV       g_uart6port /* UART6 is ttyS0 */
#define UART6_ASSIGNED  1
#elif defined(CONFIG_SCI7_SERIAL_CONSOLE)
#define CONSOLE_DEV     g_uart7port /* UART7 is console */
#define TTYS0_DEV       g_uart7port /* UART7 is ttyS0 */
#define UART7_ASSIGNED  1
#elif defined(CONFIG_SCI8_SERIAL_CONSOLE)
#define CONSOLE_DEV     g_uart8port /* UART8 is console */
#define TTYS0_DEV       g_uart8port /* UART8 is ttyS0 */
#define UART8_ASSIGNED  1
#elif defined(CONFIG_SCI9_SERIAL_CONSOLE)
#define CONSOLE_DEV     g_uart9port /* UART9 is console */
#define TTYS0_DEV       g_uart9port /* UART9 is ttyS0 */
#define UART9_ASSIGNED  1
#else
#undef CONSOLE_DEV                  /* No console */
#if defined(CONFIG_RA_SCI0_UART)
#define TTYS0_DEV       g_uart0port /* UART0 is ttyS0 */
#define UART0_ASSIGNED  1
#elif defined(CONFIG_RA_SCI1_UART)
#define TTYS0_DEV       g_uart1port /* UART1 is ttyS0 */
#define UART1_ASSIGNED  1
#elif defined(CONFIG_RA_SCI2_UART)
#define TTYS0_DEV       g_uart2port /* UART2 is ttyS0 */
#define UART2_ASSIGNED  1
#elif defined(CONFIG_RA_SCI3_UART)
#define TTYS0_DEV       g_uart3port /* UART3 is ttyS0 */
#define UART3_ASSIGNED  1
#elif defined(CONFIG_RA_SCI4_UART)
#define TTYS0_DEV       g_uart4port /* UART4 is ttyS0 */
#define UART4_ASSIGNED  1
#elif defined(CONFIG_RA_SCI5_UART)
#define TTYS0_DEV       g_uart5port /* UART5 is ttyS0 */
#define UART5_ASSIGNED  1
#elif defined(CONFIG_RA_SCI6_UART)
#define TTYS0_DEV       g_uart6port /* UART6 is ttyS0 */
#define UART6_ASSIGNED  1
#elif defined(CONFIG_RA_SCI7_UART)
#define TTYS0_DEV       g_uart7port /* UART7 is ttyS0 */
#define UART7_ASSIGNED  1
#elif defined(CONFIG_RA_SCI8_UART)
#define TTYS0_DEV       g_uart8port /* UART8 is ttyS0 */
#define UART8_ASSIGNED  1
#elif defined(CONFIG_RA_SCI9_UART)
#define TTYS0_DEV       g_uart9port /* UART9 is ttyS0 */
#define UART9_ASSIGNED  1
#endif
#endif

/* Pick ttys1. */

#if defined(CONFIG_RA_SCI0_UART) && !defined(UART0_ASSIGNED)
#define TTYS1_DEV       g_uart0port /* UART0 is ttyS1 */
#define UART0_ASSIGNED  1
#elif defined(CONFIG_RA_SCI1_UART) && !defined(UART1_ASSIGNED)
#define TTYS1_DEV       g_uart1port /* UART1 is ttyS1 */
#define UART1_ASSIGNED  1
#elif defined(CONFIG_RA_SCI2_UART) && !defined(UART2_ASSIGNED)
#define TTYS1_DEV       g_uart2port /* UART2 is ttyS1 */
#define UART2_ASSIGNED  1
#elif defined(CONFIG_RA_SCI3_UART) && !defined(UART3_ASSIGNED)
#define TTYS1_DEV       g_uart3port /* UART3 is ttyS1 */
#define UART3_ASSIGNED  1
#elif defined(CONFIG_RA_SCI4_UART) && !defined(UART4_ASSIGNED)
#define TTYS1_DEV       g_uart4port /* UART4 is ttyS1 */
#define UART4_ASSIGNED  1
#elif defined(CONFIG_RA_SCI5_UART) && !defined(UART5_ASSIGNED)
#define TTYS1_DEV       g_uart5port /* UART5 is ttyS1 */
#define UART5_ASSIGNED  1
#elif defined(CONFIG_RA_SCI6_UART) && !defined(UART6_ASSIGNED)
#define TTYS1_DEV       g_uart6port /* UART6 is ttyS1 */
#define UART6_ASSIGNED  1
#elif defined(CONFIG_RA_SCI7_UART) && !defined(UART7_ASSIGNED)
#define TTYS1_DEV       g_uart7port /* UART7 is ttyS1 */
#define UART7_ASSIGNED  1
#elif defined(CONFIG_RA_SCI8_UART) && !defined(UART8_ASSIGNED)
#define TTYS1_DEV       g_uart8port /* UART8 is ttyS1 */
#define UART8_ASSIGNED  1
#elif defined(CONFIG_RA_SCI9_UART) && !defined(UART9_ASSIGNED)
#define TTYS1_DEV       g_uart9port /* UART9 is ttyS1 */
#define UART9_ASSIGNED  1
#endif

/* Pick ttys2. */

#if defined(CONFIG_RA_SCI0_UART) && !defined(UART0_ASSIGNED)
#define TTYS2_DEV       g_uart0port /* UART0 is ttyS2 */
#define UART0_ASSIGNED  1
#elif defined(CONFIG_RA_SCI1_UART) && !defined(UART1_ASSIGNED)
#define TTYS2_DEV       g_uart1port /* UART1 is ttyS2 */
#define UART1_ASSIGNED  1
#elif defined(CONFIG_RA_SCI2_UART) && !defined(UART2_ASSIGNED)
#define TTYS2_DEV       g_uart2port /* UART2 is ttyS2 */
#define UART2_ASSIGNED  1
#elif defined(CONFIG_RA_SCI3_UART) && !defined(UART3_ASSIGNED)
#define TTYS2_DEV       g_uart3port /* UART3 is ttyS2 */
#define UART3_ASSIGNED  1
#elif defined(CONFIG_RA_SCI4_UART) && !defined(UART4_ASSIGNED)
#define TTYS2_DEV       g_uart4port /* UART4 is ttyS2 */
#define UART4_ASSIGNED  1
#elif defined(CONFIG_RA_SCI5_UART) && !defined(UART5_ASSIGNED)
#define TTYS2_DEV       g_uart5port /* UART5 is ttyS2 */
#define UART5_ASSIGNED  1
#elif defined(CONFIG_RA_SCI6_UART) && !defined(UART6_ASSIGNED)
#define TTYS2_DEV       g_uart6port /* UART6 is ttyS2 */
#define UART6_ASSIGNED  1
#elif defined(CONFIG_RA_SCI7_UART) && !defined(UART7_ASSIGNED)
#define TTYS2_DEV       g_uart7port /* UART7 is ttyS2 */
#define UART7_ASSIGNED  1
#elif defined(CONFIG_RA_SCI8_UART) && !defined(UART8_ASSIGNED)
#define TTYS2_DEV       g_uart8port /* UART8 is ttyS2 */
#define UART8_ASSIGNED  1
#elif defined(CONFIG_RA_SCI9_UART) && !defined(UART9_ASSIGNED)
#define TTYS2_DEV       g_uart9port /* UART9 is ttyS2 */
#define UART9_ASSIGNED  1
#endif

/* Pick ttys3. */

#if defined(CONFIG_RA_SCI0_UART) && !defined(UART0_ASSIGNED)
#define TTYS3_DEV       g_uart0port /* UART0 is ttyS3 */
#define UART0_ASSIGNED  1
#elif defined(CONFIG_RA_SCI1_UART) && !defined(UART1_ASSIGNED)
#define TTYS3_DEV       g_uart1port /* UART1 is ttyS3 */
#define UART1_ASSIGNED  1
#elif defined(CONFIG_RA_SCI2_UART) && !defined(UART2_ASSIGNED)
#define TTYS3_DEV       g_uart2port /* UART2 is ttyS3 */
#define UART2_ASSIGNED  1
#elif defined(CONFIG_RA_SCI3_UART) && !defined(UART3_ASSIGNED)
#define TTYS3_DEV       g_uart3port /* UART3 is ttyS3 */
#define UART3_ASSIGNED  1
#elif defined(CONFIG_RA_SCI4_UART) && !defined(UART4_ASSIGNED)
#define TTYS3_DEV       g_uart4port /* UART4 is ttyS3 */
#define UART4_ASSIGNED  1
#elif defined(CONFIG_RA_SCI5_UART) && !defined(UART5_ASSIGNED)
#define TTYS3_DEV       g_uart5port /* UART5 is ttyS3 */
#define UART5_ASSIGNED  1
#elif defined(CONFIG_RA_SCI6_UART) && !defined(UART6_ASSIGNED)
#define TTYS3_DEV       g_uart6port /* UART6 is ttyS3 */
#define UART6_ASSIGNED  1
#elif defined(CONFIG_RA_SCI7_UART) && !defined(UART7_ASSIGNED)
#define TTYS3_DEV       g_uart7port /* UART7 is ttyS3 */
#define UART7_ASSIGNED  1
#elif defined(CONFIG_RA_SCI8_UART) && !defined(UART8_ASSIGNED)
#define TTYS3_DEV       g_uart8port /* UART8 is ttyS3 */
#define UART8_ASSIGNED  1
#elif defined(CONFIG_RA_SCI9_UART) && !defined(UART9_ASSIGNED)
#define TTYS3_DEV       g_uart9port /* UART9 is ttyS3 */
#define UART9_ASSIGNED  1
#endif

/* Pick ttys4. */

#if defined(CONFIG_RA_SCI0_UART) && !defined(UART0_ASSIGNED)
#define TTYS4_DEV       g_uart0port /* UART0 is ttyS4 */
#define UART0_ASSIGNED  1
#elif defined(CONFIG_RA_SCI1_UART) && !defined(UART1_ASSIGNED)
#define TTYS4_DEV       g_uart1port /* UART1 is ttyS4 */
#define UART1_ASSIGNED  1
#elif defined(CONFIG_RA_SCI2_UART) && !defined(UART2_ASSIGNED)
#define TTYS4_DEV       g_uart2port /* UART2 is ttyS4 */
#define UART2_ASSIGNED  1
#elif defined(CONFIG_RA_SCI3_UART) && !defined(UART3_ASSIGNED)
#define TTYS4_DEV       g_uart3port /* UART3 is ttyS4 */
#define UART3_ASSIGNED  1
#elif defined(CONFIG_RA_SCI4_UART) && !defined(UART4_ASSIGNED)
#define TTYS4_DEV       g_uart4port /* UART4 is ttyS4 */
#define UART4_ASSIGNED  1
#elif defined(CONFIG_RA_SCI5_UART) && !defined(UART5_ASSIGNED)
#define TTYS4_DEV       g_uart5port /* UART5 is ttyS4 */
#define UART5_ASSIGNED  1
#elif defined(CONFIG_RA_SCI6_UART) && !defined(UART6_ASSIGNED)
#define TTYS4_DEV       g_uart6port /* UART6 is ttyS4 */
#define UART6_ASSIGNED  1
#elif defined(CONFIG_RA_SCI7_UART) && !defined(UART7_ASSIGNED)
#define TTYS4_DEV       g_uart7port /* UART7 is ttyS4 */
#define UART7_ASSIGNED  1
#elif defined(CONFIG_RA_SCI8_UART) && !defined(UART8_ASSIGNED)
#define TTYS4_DEV       g_uart8port /* UART8 is ttyS4 */
#define UART8_ASSIGNED  1
#elif defined(CONFIG_RA_SCI9_UART) && !defined(UART9_ASSIGNED)
#define TTYS4_DEV       g_uart9port /* UART9 is ttyS4 */
#define UART9_ASSIGNED  1
#endif

/* Pick ttys5. */

#if defined(CONFIG_RA_SCI0_UART) && !defined(UART0_ASSIGNED)
#define TTYS5_DEV       g_uart0port /* UART0 is ttyS5 */
#define UART0_ASSIGNED  1
#elif defined(CONFIG_RA_SCI1_UART) && !defined(UART1_ASSIGNED)
#define TTYS5_DEV       g_uart1port /* UART1 is ttyS5 */
#define UART1_ASSIGNED  1
#elif defined(CONFIG_RA_SCI2_UART) && !defined(UART2_ASSIGNED)
#define TTYS5_DEV       g_uart2port /* UART2 is ttyS5 */
#define UART2_ASSIGNED  1
#elif defined(CONFIG_RA_SCI3_UART) && !defined(UART3_ASSIGNED)
#define TTYS5_DEV       g_uart3port /* UART3 is ttyS5 */
#define UART3_ASSIGNED  1
#elif defined(CONFIG_RA_SCI4_UART) && !defined(UART4_ASSIGNED)
#define TTYS5_DEV       g_uart4port /* UART4 is ttyS5 */
#define UART4_ASSIGNED  1
#elif defined(CONFIG_RA_SCI5_UART) && !defined(UART5_ASSIGNED)
#define TTYS5_DEV       g_uart5port /* UART5 is ttyS5 */
#define UART5_ASSIGNED  1
#elif defined(CONFIG_RA_SCI6_UART) && !defined(UART6_ASSIGNED)
#define TTYS5_DEV       g_uart6port /* UART6 is ttyS5 */
#define UART6_ASSIGNED  1
#elif defined(CONFIG_RA_SCI7_UART) && !defined(UART7_ASSIGNED)
#define TTYS5_DEV       g_uart7port /* UART7 is ttyS5 */
#define UART7_ASSIGNED  1
#elif defined(CONFIG_RA_SCI8_UART) && !defined(UART8_ASSIGNED)
#define TTYS5_DEV       g_uart8port /* UART8 is ttyS5 */
#define UART8_ASSIGNED  1
#elif defined(CONFIG_RA_SCI9_UART) && !defined(UART9_ASSIGNED)
#define TTYS5_DEV       g_uart9port /* UART9 is ttyS5 */
#define UART9_ASSIGNED  1
#endif

/* Pick ttys6. */

#if defined(CONFIG_RA_SCI0_UART) && !defined(UART0_ASSIGNED)
#define TTYS6_DEV       g_uart0port /* UART0 is ttyS6 */
#define UART0_ASSIGNED  1
#elif defined(CONFIG_RA_SCI1_UART) && !defined(UART1_ASSIGNED)
#define TTYS6_DEV       g_uart1port /* UART1 is ttyS6 */
#define UART1_ASSIGNED  1
#elif defined(CONFIG_RA_SCI2_UART) && !defined(UART2_ASSIGNED)
#define TTYS6_DEV       g_uart2port /* UART2 is ttyS6 */
#define UART2_ASSIGNED  1
#elif defined(CONFIG_RA_SCI3_UART) && !defined(UART3_ASSIGNED)
#define TTYS6_DEV       g_uart3port /* UART3 is ttyS6 */
#define UART3_ASSIGNED  1
#elif defined(CONFIG_RA_SCI4_UART) && !defined(UART4_ASSIGNED)
#define TTYS6_DEV       g_uart4port /* UART4 is ttyS6 */
#define UART4_ASSIGNED  1
#elif defined(CONFIG_RA_SCI5_UART) && !defined(UART5_ASSIGNED)
#define TTYS6_DEV       g_uart5port /* UART5 is ttyS6 */
#define UART5_ASSIGNED  1
#elif defined(CONFIG_RA_SCI6_UART) && !defined(UART6_ASSIGNED)
#define TTYS6_DEV       g_uart6port /* UART6 is ttyS6 */
#define UART6_ASSIGNED  1
#elif defined(CONFIG_RA_SCI7_UART) && !defined(UART7_ASSIGNED)
#define TTYS6_DEV       g_uart7port /* UART7 is ttyS6 */
#define UART7_ASSIGNED  1
#elif defined(CONFIG_RA_SCI8_UART) && !defined(UART8_ASSIGNED)
#define TTYS6_DEV       g_uart8port /* UART8 is ttyS6 */
#define UART8_ASSIGNED  1
#elif defined(CONFIG_RA_SCI9_UART) && !defined(UART9_ASSIGNED)
#define TTYS6_DEV       g_uart9port /* UART9 is ttyS6 */
#define UART9_ASSIGNED  1
#endif

/* Pick ttys7. */

#if defined(CONFIG_RA_SCI0_UART) && !defined(UART0_ASSIGNED)
#define TTYS7_DEV       g_uart0port /* UART0 is ttyS7 */
#define UART0_ASSIGNED  1
#elif defined(CONFIG_RA_SCI1_UART) && !defined(UART1_ASSIGNED)
#define TTYS7_DEV       g_uart1port /* UART1 is ttyS7 */
#define UART1_ASSIGNED  1
#elif defined(CONFIG_RA_SCI2_UART) && !defined(UART2_ASSIGNED)
#define TTYS7_DEV       g_uart2port /* UART2 is ttyS7 */
#define UART2_ASSIGNED  1
#elif defined(CONFIG_RA_SCI3_UART) && !defined(UART3_ASSIGNED)
#define TTYS7_DEV       g_uart3port /* UART3 is ttyS7 */
#define UART3_ASSIGNED  1
#elif defined(CONFIG_RA_SCI4_UART) && !defined(UART4_ASSIGNED)
#define TTYS7_DEV       g_uart4port /* UART4 is ttyS7 */
#define UART4_ASSIGNED  1
#elif defined(CONFIG_RA_SCI5_UART) && !defined(UART5_ASSIGNED)
#define TTYS7_DEV       g_uart5port /* UART5 is ttyS7 */
#define UART5_ASSIGNED  1
#elif defined(CONFIG_RA_SCI6_UART) && !defined(UART6_ASSIGNED)
#define TTYS7_DEV       g_uart6port /* UART6 is ttyS7 */
#define UART6_ASSIGNED  1
#elif defined(CONFIG_RA_SCI7_UART) && !defined(UART7_ASSIGNED)
#define TTYS7_DEV       g_uart7port /* UART7 is ttyS7 */
#define UART7_ASSIGNED  1
#elif defined(CONFIG_RA_SCI8_UART) && !defined(UART8_ASSIGNED)
#define TTYS7_DEV       g_uart8port /* UART8 is ttyS7 */
#define UART8_ASSIGNED  1
#elif defined(CONFIG_RA_SCI9_UART) && !defined(UART9_ASSIGNED)
#define TTYS7_DEV       g_uart9port /* UART9 is ttyS7 */
#define UART9_ASSIGNED  1
#endif

/* Pick ttys8. */

#if defined(CONFIG_RA_SCI0_UART) && !defined(UART0_ASSIGNED)
#define TTYS8_DEV       g_uart0port /* UART0 is ttyS8 */
#define UART0_ASSIGNED  1
#elif defined(CONFIG_RA_SCI1_UART) && !defined(UART1_ASSIGNED)
#define TTYS8_DEV       g_uart1port /* UART1 is ttyS8 */
#define UART1_ASSIGNED  1
#elif defined(CONFIG_RA_SCI2_UART) && !defined(UART2_ASSIGNED)
#define TTYS8_DEV       g_uart2port /* UART2 is ttyS8 */
#define UART2_ASSIGNED  1
#elif defined(CONFIG_RA_SCI3_UART) && !defined(UART3_ASSIGNED)
#define TTYS8_DEV       g_uart3port /* UART3 is ttyS8 */
#define UART3_ASSIGNED  1
#elif defined(CONFIG_RA_SCI4_UART) && !defined(UART4_ASSIGNED)
#define TTYS8_DEV       g_uart4port /* UART4 is ttyS8 */
#define UART4_ASSIGNED  1
#elif defined(CONFIG_RA_SCI5_UART) && !defined(UART5_ASSIGNED)
#define TTYS8_DEV       g_uart5port /* UART5 is ttyS8 */
#define UART5_ASSIGNED  1
#elif defined(CONFIG_RA_SCI6_UART) && !defined(UART6_ASSIGNED)
#define TTYS8_DEV       g_uart6port /* UART6 is ttyS8 */
#define UART6_ASSIGNED  1
#elif defined(CONFIG_RA_SCI7_UART) && !defined(UART7_ASSIGNED)
#define TTYS8_DEV       g_uart7port /* UART7 is ttyS8 */
#define UART7_ASSIGNED  1
#elif defined(CONFIG_RA_SCI8_UART) && !defined(UART8_ASSIGNED)
#define TTYS8_DEV       g_uart8port /* UART8 is ttyS8 */
#define UART8_ASSIGNED  1
#elif defined(CONFIG_RA_SCI9_UART) && !defined(UART9_ASSIGNED)
#define TTYS8_DEV       g_uart9port /* UART9 is ttyS8 */
#define UART9_ASSIGNED  1
#endif

/* Pick ttys9. */

#if defined(CONFIG_RA_SCI0_UART) && !defined(UART0_ASSIGNED)
#define TTYS9_DEV       g_uart0port /* UART0 is ttyS9 */
#define UART0_ASSIGNED  1
#elif defined(CONFIG_RA_SCI1_UART) && !defined(UART1_ASSIGNED)
#define TTYS9_DEV       g_uart1port /* UART1 is ttyS9 */
#define UART1_ASSIGNED  1
#elif defined(CONFIG_RA_SCI2_UART) && !defined(UART2_ASSIGNED)
#define TTYS9_DEV       g_uart2port /* UART2 is ttyS9 */
#define UART2_ASSIGNED  1
#elif defined(CONFIG_RA_SCI3_UART) && !defined(UART3_ASSIGNED)
#define TTYS9_DEV       g_uart3port /* UART3 is ttyS9 */
#define UART3_ASSIGNED  1
#elif defined(CONFIG_RA_SCI4_UART) && !defined(UART4_ASSIGNED)
#define TTYS9_DEV       g_uart4port /* UART4 is ttyS9 */
#define UART4_ASSIGNED  1
#elif defined(CONFIG_RA_SCI5_UART) && !defined(UART5_ASSIGNED)
#define TTYS9_DEV       g_uart5port /* UART5 is ttyS9 */
#define UART5_ASSIGNED  1
#elif defined(CONFIG_RA_SCI6_UART) && !defined(UART6_ASSIGNED)
#define TTYS9_DEV       g_uart6port /* UART6 is ttyS9 */
#define UART6_ASSIGNED  1
#elif defined(CONFIG_RA_SCI7_UART) && !defined(UART7_ASSIGNED)
#define TTYS9_DEV       g_uart7port /* UART7 is ttyS9 */
#define UART7_ASSIGNED  1
#elif defined(CONFIG_RA_SCI8_UART) && !defined(UART8_ASSIGNED)
#define TTYS9_DEV       g_uart8port /* UART8 is ttyS9 */
#define UART8_ASSIGNED  1
#elif defined(CONFIG_RA_SCI9_UART) && !defined(UART9_ASSIGNED)
#define TTYS9_DEV       g_uart9port /* UART9 is ttyS9 */
#define UART9_ASSIGNED  1
#endif

/* Check if any UART is enabled */

#ifdef CONFIG_RA_SCI0_UART
#  define HAVE_UART 1
#elif defined(CONFIG_RA_SCI1_UART)
#  define HAVE_UART 1
#elif defined(CONFIG_RA_SCI2_UART)
#  define HAVE_UART 1
#elif defined(CONFIG_RA_SCI3_UART)
#  define HAVE_UART 1
#elif defined(CONFIG_RA_SCI4_UART)
#  define HAVE_UART 1
#elif defined(CONFIG_RA_SCI5_UART)
#  define HAVE_UART 1
#elif defined(CONFIG_RA_SCI6_UART)
#  define HAVE_UART 1
#elif defined(CONFIG_RA_SCI7_UART)
#  define HAVE_UART 1
#elif defined(CONFIG_RA_SCI8_UART)
#  define HAVE_UART 1
#elif defined(CONFIG_RA_SCI9_UART)
#  define HAVE_UART 1
#endif

#ifdef HAVE_UART

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int up_setup(struct uart_dev_s *dev);
static void up_shutdown(struct uart_dev_s *dev);
static int up_attach(struct uart_dev_s *dev);
static void up_detach(struct uart_dev_s *dev);
static int up_rxinterrupt(int irq, void *context, void *arg);
static int up_txinterrupt(int irq, void *context, void *arg);
static int up_txeinterrupt(int irq, void *context, void *arg);
static int up_erinterrupt(int irq, void *context, void *arg);
static int up_ioctl(struct file *filep, int cmd, unsigned long arg);
static int up_receive(struct uart_dev_s *dev, unsigned int *status);
static void up_rxint(struct uart_dev_s *dev, bool enable);
static bool up_rxavailable(struct uart_dev_s *dev);
static void up_send(struct uart_dev_s *dev, int ch);
static void up_txint(struct uart_dev_s *dev, bool enable);
static bool up_txready(struct uart_dev_s *dev);
static bool up_txempty(struct uart_dev_s *dev);

/****************************************************************************
 * Private Data
 ****************************************************************************/

struct up_dev_s
{
  const uint32_t scibase;   /* Base address of SCI registers */
  uint32_t mstp;            /* Module Stop Control Register */
  uint32_t baud;            /* Configured baud */
  uint32_t sr;              /* Saved status bits */
  int rxi_irq;               /* RX IRQ number assigned by ICU */
  int txi_irq;               /* TX IRQ number assigned by ICU */
  int tei_irq;              /* TX End IRQ number assigned by ICU */
  int eri_irq;              /* Error IRQ number assigned by ICU */
  int elc_rx;               /* RX event link for ICU configuration */
  int elc_tx;               /* TX event link for ICU configuration */
  int elc_txe;              /* TX End event link for ICU configuration */
  int elc_err;              /* Error event link for ICU configuration */
  int parity;               /* 0=none, 1=odd, 2=even */
  int bits;                 /* Number of bits (5-9) */
  bool stopbits2;           /* true: Configure with 2 stop bits instead of 1 */
  uint8_t fifo_depth;       /* FIFO depth: 0=no FIFO, 16=FIFO supported */

#ifdef CONFIG_SERIAL_TXDMA
  ra_dmac_handle_t  dma_tx_handle; /* DMAC handle for TX */
  int               dma_tx_chn;    /* DMAC channel for TX */
  sem_t             dmatx_sem;     /* Sem for DMA wait */
#endif

#ifdef CONFIG_SERIAL_RXDMA
  ra_dmac_handle_t  dma_rx_handle; /* DMAC handle for RX */
  int               dma_rx_chn;    /* DMAC channel for RX */
  uint8_t          *rx_dma_buf;    /* Buffer for RX DMAC */
  size_t            rx_dma_size;   /* Size of RX DMAC buffer */
  size_t            rx_dma_pos;    /* Current read position */
  sem_t             dmarx_sem;     /* Sem for DMA wait */
#endif
};

static const struct uart_ops_s g_uart_ops =
{
  .setup        = up_setup,
  .shutdown     = up_shutdown,
  .attach       = up_attach,
  .detach       = up_detach,
  .ioctl        = up_ioctl,
  .receive      = up_receive,
  .rxint        = up_rxint,
  .rxavailable  = up_rxavailable,
  .send         = up_send,
#ifdef CONFIG_SERIAL_TXDMA
  .dmasend      = up_dma_send,
  .dmatxavail   = up_dma_txavailable,
  .txint        = up_dma_txint,
#else
  .txint        = up_txint,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dmarxavail   = up_dma_rxavailable,
#endif
  .txready      = up_txready,
  .txempty      = up_txempty,
};

/* I/O buffers */
#ifdef CONFIG_RA_SCI0_UART
static char g_uart0rxbuffer[CONFIG_SCI0_RXBUFSIZE];
static char g_uart0txbuffer[CONFIG_SCI0_TXBUFSIZE];
#endif

#ifdef CONFIG_RA_SCI1_UART
static char g_uart1rxbuffer[CONFIG_SCI1_RXBUFSIZE];
static char g_uart1txbuffer[CONFIG_SCI1_TXBUFSIZE];
#endif

#ifdef CONFIG_RA_SCI2_UART
static char g_uart2rxbuffer[CONFIG_SCI2_RXBUFSIZE];
static char g_uart2txbuffer[CONFIG_SCI2_TXBUFSIZE];
#endif

#ifdef CONFIG_RA_SCI3_UART
static char g_uart3rxbuffer[CONFIG_SCI3_RXBUFSIZE];
static char g_uart3txbuffer[CONFIG_SCI3_TXBUFSIZE];
#endif

#ifdef CONFIG_RA_SCI4_UART
static char g_uart4rxbuffer[CONFIG_SCI4_RXBUFSIZE];
static char g_uart4txbuffer[CONFIG_SCI4_TXBUFSIZE];
#endif

#ifdef CONFIG_RA_SCI5_UART
static char g_uart5rxbuffer[CONFIG_SCI5_RXBUFSIZE];
static char g_uart5txbuffer[CONFIG_SCI5_TXBUFSIZE];
#endif

#ifdef CONFIG_RA_SCI6_UART
static char g_uart6rxbuffer[CONFIG_SCI6_RXBUFSIZE];
static char g_uart6txbuffer[CONFIG_SCI6_TXBUFSIZE];
#endif

#ifdef CONFIG_RA_SCI7_UART
static char g_uart7rxbuffer[CONFIG_SCI7_RXBUFSIZE];
static char g_uart7txbuffer[CONFIG_SCI7_TXBUFSIZE];
#endif

#ifdef CONFIG_RA_SCI8_UART
static char g_uart8rxbuffer[CONFIG_SCI8_RXBUFSIZE];
static char g_uart8txbuffer[CONFIG_SCI8_TXBUFSIZE];
#endif

#ifdef CONFIG_RA_SCI9_UART
static char g_uart9rxbuffer[CONFIG_SCI9_RXBUFSIZE];
static char g_uart9txbuffer[CONFIG_SCI9_TXBUFSIZE];
#endif

#ifdef CONFIG_RA_SCI0_UART
static struct up_dev_s  g_uart0priv =
{
  .scibase      = R_SCI_B_CH_BASE(0),
  .mstp         = R_MSTP_MSTPCRB_SCI0,
  .rxi_irq      = -1,               /* Will be assigned by ICU */
  .txi_irq      = -1,               /* Will be assigned by ICU */
  .tei_irq      = -1,               /* Will be assigned by ICU */
  .eri_irq      = -1,               /* Will be assigned by ICU */
  .elc_rx       = RA_ELC_SCI0_RXI,
  .elc_tx       = RA_ELC_SCI0_TXI,
  .elc_txe      = RA_ELC_SCI0_TEI,
  .elc_err      = RA_ELC_SCI0_ERI,
  .baud         = CONFIG_SCI0_BAUD,
  .parity       = CONFIG_SCI0_PARITY,
  .bits         = CONFIG_SCI0_BITS,
  .stopbits2    = CONFIG_SCI0_2STOP,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn   = CONFIG_RA_DMAC_UART0_TX_CHANNEL,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn   = CONFIG_RA_DMAC_UART0_RX_CHANNEL,
#endif
};

static uart_dev_t g_uart0port =
{
  .recv     =
  {
    .size   = CONFIG_SCI0_RXBUFSIZE,
    .buffer = g_uart0rxbuffer,
  },
  .xmit  =
  {
    .size   = CONFIG_SCI0_TXBUFSIZE,
    .buffer = g_uart0txbuffer,
  },
  .ops   = &g_uart_ops,
  .priv = &g_uart0priv,
};
#endif

#ifdef CONFIG_RA_SCI1_UART
static struct up_dev_s  g_uart1priv =
{
  .scibase      = R_SCI_B_CH_BASE(1),
  .mstp         = R_MSTP_MSTPCRB_SCI1,
  .rxi_irq      = -1,               /* Will be assigned by ICU */
  .txi_irq      = -1,               /* Will be assigned by ICU */
  .tei_irq      = -1,               /* Will be assigned by ICU */
  .eri_irq      = -1,               /* Will be assigned by ICU */
  .elc_rx       = RA_ELC_SCI1_RXI,
  .elc_tx       = RA_ELC_SCI1_TXI,
  .elc_txe      = RA_ELC_SCI1_TEI,
  .elc_err      = RA_ELC_SCI1_ERI,
  .baud         = CONFIG_SCI1_BAUD,
  .parity       = CONFIG_SCI1_PARITY,
  .bits         = CONFIG_SCI1_BITS,
  .stopbits2    = CONFIG_SCI1_2STOP,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn   = CONFIG_RA_DMAC_UART1_TX_CHANNEL,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn   = CONFIG_RA_DMAC_UART1_RX_CHANNEL,
#endif
};

static uart_dev_t  g_uart1port =
{
  .recv     =
  {
    .size   = CONFIG_SCI1_RXBUFSIZE,
    .buffer = g_uart1rxbuffer,
  },
  .xmit  =
  {
    .size   = CONFIG_SCI1_TXBUFSIZE,
    .buffer = g_uart1txbuffer,
  },
  .ops   = &g_uart_ops,
  .priv = &g_uart1priv,
};
#endif

#ifdef CONFIG_RA_SCI2_UART
static struct up_dev_s  g_uart2priv =
{
  .scibase      = R_SCI_B_CH_BASE(2),
  .mstp         = R_MSTP_MSTPCRB_SCI2,
  .rxi_irq      = -1,               /* Will be assigned by ICU */
  .txi_irq      = -1,               /* Will be assigned by ICU */
  .tei_irq      = -1,               /* Will be assigned by ICU */
  .eri_irq      = -1,               /* Will be assigned by ICU */
  .elc_rx       = RA_ELC_SCI2_RXI,
  .elc_tx       = RA_ELC_SCI2_TXI,
  .elc_txe      = RA_ELC_SCI2_TEI,
  .elc_err      = RA_ELC_SCI2_ERI,
  .baud         = CONFIG_SCI2_BAUD,
  .parity       = CONFIG_SCI2_PARITY,
  .bits         = CONFIG_SCI2_BITS,
  .stopbits2    = CONFIG_SCI2_2STOP,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn   = CONFIG_RA_DMAC_UART2_TX_CHANNEL,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn   = CONFIG_RA_DMAC_UART2_RX_CHANNEL,
#endif
};

static uart_dev_t  g_uart2port =
{
  .recv     =
  {
    .size   = CONFIG_SCI2_RXBUFSIZE,
    .buffer = g_uart2rxbuffer,
  },
  .xmit  =
  {
    .size   = CONFIG_SCI2_TXBUFSIZE,
    .buffer = g_uart2txbuffer,
  },
  .ops   = &g_uart_ops,
  .priv = &g_uart2priv,
};
#endif

#ifdef CONFIG_RA_SCI3_UART
static struct up_dev_s  g_uart3priv =
{
  .scibase      = R_SCI_B_CH_BASE(3),
  .mstp         = R_MSTP_MSTPCRB_SCI3,
  .rxi_irq      = -1,               /* Will be assigned by ICU */
  .txi_irq      = -1,               /* Will be assigned by ICU */
  .tei_irq      = -1,               /* Will be assigned by ICU */
  .eri_irq      = -1,               /* Will be assigned by ICU */
  .elc_rx       = RA_ELC_SCI3_RXI,
  .elc_tx       = RA_ELC_SCI3_TXI,
  .elc_txe      = RA_ELC_SCI3_TEI,
  .elc_err      = RA_ELC_SCI3_ERI,
  .baud         = CONFIG_SCI3_BAUD,
  .parity       = CONFIG_SCI3_PARITY,
  .bits         = CONFIG_SCI3_BITS,
  .stopbits2    = CONFIG_SCI3_2STOP,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn   = CONFIG_RA_DMAC_UART3_TX_CHANNEL,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn   = CONFIG_RA_DMAC_UART3_RX_CHANNEL,
#endif
};

static uart_dev_t  g_uart3port =
{
  .recv     =
  {
    .size   = CONFIG_SCI3_RXBUFSIZE,
    .buffer = g_uart3rxbuffer,
  },
  .xmit  =
  {
    .size   = CONFIG_SCI3_TXBUFSIZE,
    .buffer = g_uart3txbuffer,
  },
  .ops   = &g_uart_ops,
  .priv = &g_uart3priv,
};
#endif

#ifdef CONFIG_RA_SCI4_UART
static struct up_dev_s  g_uart4priv =
{
  .scibase      = R_SCI_B_CH_BASE(4),
  .mstp         = R_MSTP_MSTPCRB_SCI4,
  .rxi_irq      = -1,               /* Will be assigned by ICU */
  .txi_irq      = -1,               /* Will be assigned by ICU */
  .tei_irq      = -1,               /* Will be assigned by ICU */
  .eri_irq      = -1,               /* Will be assigned by ICU */
  .elc_rx       = RA_ELC_SCI4_RXI,   /* RX event link for ICU configuration */
  .elc_tx       = RA_ELC_SCI4_TXI,
  .elc_txe      = RA_ELC_SCI4_TEI,
  .elc_err      = RA_ELC_SCI4_ERI,
  .baud         = CONFIG_SCI4_BAUD,
  .parity       = CONFIG_SCI4_PARITY,
  .bits         = CONFIG_SCI4_BITS,
  .stopbits2    = CONFIG_SCI4_2STOP,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn   = CONFIG_RA_DMAC_UART4_TX_CHANNEL,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn   = CONFIG_RA_DMAC_UART4_RX_CHANNEL,
#endif
};

static uart_dev_t  g_uart4port =
{
  .recv     =
  {
    .size   = CONFIG_SCI4_RXBUFSIZE,
    .buffer = g_uart4rxbuffer,
  },
  .xmit  =
  {
    .size   = CONFIG_SCI4_TXBUFSIZE,
    .buffer = g_uart4txbuffer,
  },
  .ops   = &g_uart_ops,
  .priv = &g_uart4priv,
};
#endif

#ifdef CONFIG_RA_SCI5_UART
static struct up_dev_s  g_uart5priv =
{
  .scibase      = R_SCI_B_CH_BASE(5),
  .mstp         = R_MSTP_MSTPCRB_SCI5,
  .rxi_irq      = -1,               /* Will be assigned by ICU */
  .txi_irq      = -1,               /* Will be assigned by ICU */
  .tei_irq      = -1,               /* Will be assigned by ICU */
  .eri_irq      = -1,               /* Will be assigned by ICU */
  .elc_rx       = RA_ELC_SCI5_RXI,
  .elc_tx       = RA_ELC_SCI5_TXI,
  .elc_txe      = RA_ELC_SCI5_TEI,
  .elc_err      = RA_ELC_SCI5_ERI,
  .baud         = CONFIG_SCI5_BAUD,
  .parity       = CONFIG_SCI5_PARITY,
  .bits         = CONFIG_SCI5_BITS,
  .stopbits2    = CONFIG_SCI5_2STOP,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn   = CONFIG_RA_DMAC_UART5_TX_CHANNEL,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn   = CONFIG_RA_DMAC_UART5_RX_CHANNEL,
#endif
};

static uart_dev_t  g_uart5port =
{
  .recv     =
  {
    .size   = CONFIG_SCI5_RXBUFSIZE,
    .buffer = g_uart5rxbuffer,
  },
  .xmit  =
  {
    .size   = CONFIG_SCI5_TXBUFSIZE,
    .buffer = g_uart5txbuffer,
  },
  .ops   = &g_uart_ops,
  .priv = &g_uart5priv,
};
#endif

#ifdef CONFIG_RA_SCI6_UART
static struct up_dev_s  g_uart6priv =
{
  .scibase      = R_SCI_B_CH_BASE(6),
  .mstp         = R_MSTP_MSTPCRB_SCI6,
  .rxi_irq      = -1,               /* Will be assigned by ICU */
  .txi_irq      = -1,               /* Will be assigned by ICU */
  .tei_irq      = -1,               /* Will be assigned by ICU */
  .eri_irq      = -1,               /* Will be assigned by ICU */
  .elc_rx       = RA_ELC_SCI6_RXI,
  .elc_tx       = RA_ELC_SCI6_TXI,
  .elc_txe      = RA_ELC_SCI6_TEI,
  .elc_err      = RA_ELC_SCI6_ERI,
  .baud         = CONFIG_SCI6_BAUD,
  .parity       = CONFIG_SCI6_PARITY,
  .bits         = CONFIG_SCI6_BITS,
  .stopbits2    = CONFIG_SCI6_2STOP,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn   = CONFIG_RA_DMAC_UART6_TX_CHANNEL,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn   = CONFIG_RA_DMAC_UART6_RX_CHANNEL,
#endif
};

static uart_dev_t  g_uart6port =
{
  .recv     =
  {
    .size   = CONFIG_SCI6_RXBUFSIZE,
    .buffer = g_uart6rxbuffer,
  },
  .xmit  =
  {
    .size   = CONFIG_SCI6_TXBUFSIZE,
    .buffer = g_uart6txbuffer,
  },
  .ops   = &g_uart_ops,
  .priv = &g_uart6priv,
};
#endif

#ifdef CONFIG_RA_SCI7_UART
static struct up_dev_s  g_uart7priv =
{
  .scibase      = R_SCI_B_CH_BASE(7),
  .mstp         = R_MSTP_MSTPCRB_SCI7,
  .rxi_irq      = -1,               /* Will be assigned by ICU */
  .txi_irq      = -1,               /* Will be assigned by ICU */
  .tei_irq      = -1,               /* Will be assigned by ICU */
  .eri_irq      = -1,               /* Will be assigned by ICU */
  .elc_rx       = RA_ELC_SCI7_RXI,
  .elc_tx       = RA_ELC_SCI7_TXI,
  .elc_txe      = RA_ELC_SCI7_TEI,
  .elc_err      = RA_ELC_SCI7_ERI,
  .baud         = CONFIG_SCI7_BAUD,
  .parity       = CONFIG_SCI7_PARITY,
  .bits         = CONFIG_SCI7_BITS,
  .stopbits2    = CONFIG_SCI7_2STOP,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn   = CONFIG_RA_DMAC_UART7_TX_CHANNEL,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn   = CONFIG_RA_DMAC_UART7_RX_CHANNEL,
#endif
};

static uart_dev_t  g_uart7port =
{
  .recv     =
  {
    .size   = CONFIG_SCI7_RXBUFSIZE,
    .buffer = g_uart7rxbuffer,
  },
  .xmit  =
  {
    .size   = CONFIG_SCI7_TXBUFSIZE,
    .buffer = g_uart7txbuffer,
  },
  .ops   = &g_uart_ops,
  .priv = &g_uart7priv,
};
#endif

#ifdef CONFIG_RA_SCI8_UART
static struct up_dev_s  g_uart8priv =
{
  .scibase      = R_SCI_B_CH_BASE(8),
  .mstp         = R_MSTP_MSTPCRB_SCI8,
  .rxi_irq      = -1,               /* Will be assigned by ICU */
  .txi_irq      = -1,               /* Will be assigned by ICU */
  .tei_irq      = -1,               /* Will be assigned by ICU */
  .eri_irq      = -1,               /* Will be assigned by ICU */
  .elc_rx       = RA_ELC_SCI8_RXI,
  .elc_tx       = RA_ELC_SCI8_TXI,
  .elc_txe      = RA_ELC_SCI8_TEI,
  .elc_err      = RA_ELC_SCI8_ERI,
  .baud         = CONFIG_SCI8_BAUD,
  .parity       = CONFIG_SCI8_PARITY,
  .bits         = CONFIG_SCI8_BITS,
  .stopbits2    = CONFIG_SCI8_2STOP,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn   = CONFIG_RA_DMAC_UART8_TX_CHANNEL,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn   = CONFIG_RA_DMAC_UART8_RX_CHANNEL,
#endif
};

static uart_dev_t  g_uart8port =
{
  .recv     =
  {
    .size   = CONFIG_SCI8_RXBUFSIZE,
    .buffer = g_uart8rxbuffer,
  },
  .xmit  =
  {
    .size   = CONFIG_SCI8_TXBUFSIZE,
    .buffer = g_uart8txbuffer,
  },
  .ops   = &g_uart_ops,
  .priv = &g_uart8priv,
};
#endif

#ifdef CONFIG_RA_SCI9_UART
static struct up_dev_s  g_uart9priv =
{
  .scibase      = R_SCI_B_CH_BASE(9),
  .mstp         = R_MSTP_MSTPCRB_SCI9,
  .rxi_irq      = -1,               /* Will be assigned by ICU */
  .txi_irq      = -1,               /* Will be assigned by ICU */
  .tei_irq      = -1,               /* Will be assigned by ICU */
  .eri_irq      = -1,               /* Will be assigned by ICU */
  .elc_rx       = RA_ELC_SCI9_RXI,
  .elc_tx       = RA_ELC_SCI9_TXI,
  .elc_txe      = RA_ELC_SCI9_TEI,
  .elc_err      = RA_ELC_SCI9_ERI,
  .baud         = CONFIG_SCI9_BAUD,
  .parity       = CONFIG_SCI9_PARITY,
  .bits         = CONFIG_SCI9_BITS,
  .stopbits2    = CONFIG_SCI9_2STOP,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn   = CONFIG_RA_DMAC_UART9_TX_CHANNEL,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn   = CONFIG_RA_DMAC_UART9_RX_CHANNEL,
#endif
};

static uart_dev_t  g_uart9port =
{
  .recv     =
  {
    .size   = CONFIG_SCI9_RXBUFSIZE,
    .buffer = g_uart9rxbuffer,
  },
  .xmit  =
  {
    .size   = CONFIG_SCI9_TXBUFSIZE,
    .buffer = g_uart9txbuffer,
  },
  .ops   = &g_uart_ops,
  .priv = &g_uart9priv,
};
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_calculate_baud_setting
 *
 * Description:
 *   Calculate baud rate register settings for SCI_B UART.
 *   Based on Renesas R_SCI_B_UART_BaudCalculate algorithm.
 *
 * Input Parameters:
 *   baudrate - Desired baud rate (bps)
 *   p_baud_setting - Output structure for baud rate settings
 *
 * Returned Value:
 *   0 on success, negative value on error
 *
 ****************************************************************************/

/* Baud rate divisor information (UART mode)*/
static const struct
{
  uint8_t bgdm : 1;    /* Baud rate generator double-speed mode */
  uint8_t abcs : 1;    /* Asynchronous mode base clock select */
  uint8_t abcse : 1;   /* Asynchronous mode extended base clock select */
  uint8_t cks : 2;     /* Clock select (n value) */
} g_async_baud[13] =
{
  {0, 0, 1, 0},  /* divisor: 6 */
  {1, 1, 0, 0},  /* divisor: 8 */
  {1, 0, 0, 0},  /* divisor: 16 */
  {0, 0, 1, 1},  /* divisor: 24 */
  {0, 0, 0, 0},  /* divisor: 32 */
  {1, 0, 0, 1},  /* divisor: 64 */
  {0, 0, 1, 2},  /* divisor: 96 */
  {0, 0, 0, 1},  /* divisor: 128 */
  {1, 0, 0, 2},  /* divisor: 256 */
  {0, 0, 1, 3},  /* divisor: 384 */
  {0, 0, 0, 2},  /* divisor: 512 */
  {1, 0, 0, 3},  /* divisor: 1024 */
  {0, 0, 0, 3}   /* divisor: 2048 */
};

static const uint16_t g_div_coefficient[13] =
{
  6, 8, 16, 24, 32, 64, 96, 128, 256, 384, 512, 1024, 2048
};

/* Common baud rate lookup table for different SCICLK frequencies */
struct common_baudrate_settings_s
{
  uint32_t baud;
  uint8_t bgdm;
  uint8_t abcs;
  uint8_t abcse;
  uint8_t abcse2;
  uint8_t cks;
  uint8_t brr;
  uint16_t mddr;  /* Changed to uint16_t to accommodate 256 */
};

struct clock_baud_table_s
{
  uint32_t clock_freq;
  const struct common_baudrate_settings_s *settings;
  uint32_t num_settings;
};


/* Baud rate settings for 500MHz SCICLK (BGDM/ABCS/ABCSE/CKS, BRR, MDDR) */
static const struct common_baudrate_settings_s g_baud_500mhz[] =
{
  /* baud,    bgdm, abcs, abcse, abcse2, cks,  brr, mddr */
  {   9600,     0,    0,     0,     0,     1,  202, 256 },  /* Div=128, BRR=202, Error≈+0.22% */
  {  19200,     1,    0,     0,     0,     1,  202, 256 },  /* Div=64,  BRR=202, Error≈+0.22% */
  {  38400,     0,    0,     0,     0,     0,  202, 256 },  /* Div=32,  BRR=202, Error≈+0.22% */
  {  57600,     0,    0,     1,     0,     1,  179, 256 },  /* Div=24,  BRR=179, Error≈+0.47% */
  { 115200,     1,    0,     0,     0,     0,  134, 256 },  /* Div=16,  BRR=134, Error≈+0.47% */
  { 230400,     0,    0,     1,     0,     0,  179, 256 },  /* Div=6,   BRR=179, Error≈+0.47% */
  { 460800,     0,    0,     1,     0,     0,   89, 256 },  /* Div=6,   BRR=89,  Error≈+0.47% */
  { 921600,     0,    0,     1,     0,     0,   44, 256 },  /* Div=6,   BRR=44,  Error≈+0.47% */
  /* 1843200 cannot meet ≤1.5% error without BRME/MDDR; best w/o BRME: Div=6, BRR=21, Error≈+2.75% */
};

/* Corrected baud rate settings for 250 MHz SCICLK */
static const struct common_baudrate_settings_s g_baud_250mhz[] =
{
  /* baud,   bgdm, abcs, abcse, abcse2, cks,  brr, mddr */
  {   9600,    0,    0,     0,     0,     1,  202, 256 },  /* Div=128, BRR=202, Error=+0.22% */
  {  19200,    1,    0,     0,     0,     1,  202, 256 },  /* Div=64,  BRR=202, Error=+0.22% */
  {  38400,    0,    0,     0,     0,     0,  202, 256 },  /* Div=32,  BRR=202, Error=+0.22% */
  {  57600,    0,    0,     1,     0,     1,  179, 256 },  /* Div=24,  BRR=179, Error=+0.47% */
  { 115200,    1,    0,     0,     0,     0,  134, 256 },  /* Div=16,  BRR=134, Error=+0.47% */
  { 230400,    0,    0,     1,     0,     0,  179, 256 },  /* Div=6,   BRR=179, Error=+0.47% */
  { 460800,    0,    0,     1,     0,     0,   89, 256 },  /* Div=6,   BRR=89,  Error=+0.47% */
  { 921600,    0,    0,     1,     0,     0,   44, 256 },  /* Div=6,   BRR=44,  Error=+0.47% */
  /* 1843200 cannot meet ≤1.5% without BRME/MDDR;
     best w/o BRME: Div=6, BRR=21, Error≈+2.75% */
};

/* Baud rate settings for 120MHz SCICLK */
static const struct common_baudrate_settings_s g_baud_120mhz[] =
{
  /* baud,   bgdm, abcs, abcse, abcse2, cks, brr, mddr */
  {   9600,    1,    0,    0,     0,     1,  102,  135 },  /* BGDM=1, ABCS=0, CKS=1, BRR=102, MDDR=135, err=0.004% */
  {  19200,    0,    0,    0,     0,     0,  102,  135 },  /* BGDM=0, ABCS=0, CKS=0, BRR=102, MDDR=135, err=0.004% */
  {  38400,    1,    0,    0,     0,     0,  102,  135 },  /* BGDM=1, ABCS=0, CKS=0, BRR=102, MDDR=135, err=0.004% */
  {  57600,    1,    0,    0,     0,     0,   87,  173 },  /* BGDM=1, ABCS=0, CKS=0, BRR=87, MDDR=173, err=0.009% */
  { 115200,    1,    0,    0,     0,     0,   43,  173 },  /* BGDM=1, ABCS=0, CKS=0, BRR=43, MDDR=173, err=0.009% */
  { 230400,    1,    0,    0,     0,     0,   21,  173 },  /* BGDM=1, ABCS=0, CKS=0, BRR=21, MDDR=173, err=0.009% */
  { 460800,    1,    0,    0,     0,     0,   10,  173 },  /* BGDM=1, ABCS=0, CKS=0, BRR=10, MDDR=173, err=0.009% */
  { 921600,    1,    0,    0,     0,     0,    6,  220 },  /* BGDM=1, ABCS=0, CKS=0, BRR=6, MDDR=220, err=0.092% */
  {1843200,    1,    0,    0,     0,     0,    3,  251 },  /* BGDM=1, ABCS=0, CKS=0, BRR=3, MDDR=251, err=0.262% */
};

/* Baud rate settings for 90MHz SCICLK */
static const struct common_baudrate_settings_s g_baud_90mhz[] =
{
  /* baud,   bgdm, abcs, abcse, abcse2, cks, brr, mddr */
  {   9600,    1,    0,    0,     0,     1,  146,  128 },  /* BGDM=1, ABCS=0, CKS=1, BRR=146, MDDR=128 */
  {  19200,    1,    0,    0,     0,     1,   73,  128 },  /* BGDM=1, ABCS=0, CKS=1, BRR=73, MDDR=128 */
  {  38400,    1,    0,    0,     0,     0,   73,  128 },  /* BGDM=1, ABCS=0, CKS=0, BRR=73, MDDR=128 */
  {  57600,    1,    0,    0,     0,     0,   48,  128 },  /* BGDM=1, ABCS=0, CKS=0, BRR=48, MDDR=128 */
  { 115200,    1,    0,    0,     0,     0,   47,  128 },  /* BGDM=1, ABCS=0, CKS=0, BRR=47, MDDR=128 */
  { 230400,    1,    0,    0,     0,     0,   23,  128 },  /* BGDM=1, ABCS=0, CKS=0, BRR=23, MDDR=128 */
  { 460800,    1,    0,    0,     0,     0,   11,  128 },  /* BGDM=1, ABCS=0, CKS=0, BRR=11, MDDR=128 */
  { 921600,    1,    0,    0,     0,     0,    5,  128 },  /* BGDM=1, ABCS=0, CKS=0, BRR=5, MDDR=128 */
  {1843200,    1,    0,    0,     0,     0,    2,  128 },  /* BGDM=1, ABCS=0, CKS=0, BRR=2, MDDR=128 */
};

/* Baud rate settings for 80MHz SCICLK */
static const struct common_baudrate_settings_s g_baud_80mhz[] =
{
  /* baud,   bgdm, abcs, abcse, abcse2, cks, brr, mddr */
  {   9600,    0,    0,    0,     0,     2,  129,  256 },  /* n=2, N=129 */
  {  19200,    0,    0,    0,     0,     2,   64,  256 },  /* n=2, N=64  */
  {  38400,    0,    0,    0,     0,     1,   64,  256 },  /* n=1, N=64  */
  {  57600,    0,    0,    0,     0,     1,   42,  256 },  /* n=1, N=42  */
  { 115200,    0,    0,    0,     0,     1,   21,  256 },  /* n=1, N=21  */
  { 230400,    0,    0,    0,     0,     0,   42,  256 },  /* n=0, N=42  */
  { 460800,    0,    0,    0,     0,     0,   21,  256 },  /* n=0, N=21  */
  { 921600,    0,    0,    0,     0,     0,   10,  256 },  /* n=0, N=10  */
  {1250000,    1,    0,    0,     0,     0,   10,  256 },  /* n=0, N=10, BGDM=1 */
};

/* Baud rate settings for 60MHz SCICLK */
static const struct common_baudrate_settings_s g_baud_60mhz[] =
{
  /* baud,   bgdm, abcs, abcse, abcse2, cks, brr, mddr */
  {   9600,    0,    0,    0,     0,     2,   97,  256 },  /* n=2, N=97  */
  {  19200,    0,    0,    0,     0,     2,   48,  256 },  /* n=2, N=48  */
  {  38400,    0,    0,    0,     0,     1,   48,  256 },  /* n=1, N=48  */
  {  57600,    0,    0,    0,     0,     1,   32,  256 },  /* n=1, N=32  */
  { 115200,    0,    0,    0,     0,     1,   16,  256 },  /* n=1, N=16  */
  { 230400,    0,    0,    0,     0,     0,   32,  256 },  /* n=0, N=32  */
  { 460800,    0,    0,    0,     0,     0,   16,  256 },  /* n=0, N=16  */
  { 921600,    0,    0,    0,     0,     0,    8,  256 },  /* n=0, N=8   */
  {1875000,    1,    0,    0,     0,     0,    8,  256 },  /* n=0, N=8, BGDM=1 */
};

/* Clock-specific baud rate table */
static const struct clock_baud_table_s g_common_baud_settings[] =
{
  { 500000000, g_baud_500mhz, sizeof(g_baud_500mhz) / sizeof(g_baud_500mhz[0]) },
  { 250000000, g_baud_250mhz, sizeof(g_baud_250mhz) / sizeof(g_baud_250mhz[0]) },
  { 120000000, g_baud_120mhz, sizeof(g_baud_120mhz) / sizeof(g_baud_120mhz[0]) },
  {  90000000, g_baud_90mhz,  sizeof(g_baud_90mhz) / sizeof(g_baud_90mhz[0]) },
  {  80000000, g_baud_80mhz,  sizeof(g_baud_80mhz) / sizeof(g_baud_80mhz[0]) },
  {  60000000, g_baud_60mhz,  sizeof(g_baud_60mhz) / sizeof(g_baud_60mhz[0]) },
};

#define NUM_CLOCK_BAUD_TABLES (sizeof(g_common_baud_settings) / sizeof(g_common_baud_settings[0]))

struct baud_setting
{
  uint8_t bgdm;
  uint8_t abcs;
  uint8_t abcse;
  uint8_t abcse2;
  uint8_t cks;
  uint8_t brr;
  uint8_t brme;
  uint16_t mddr;  /* Changed to uint16_t to accommodate 256 */
};

static int up_calculate_baud_setting(uint32_t baudrate, struct baud_setting *p_baud_setting)
{
  uint32_t freq_hz;
  int32_t hit_bit_err = 100000; /* 100% error as starting point */
  uint32_t divisor;

  /* Get SCI clock frequency */
  freq_hz = ra_get_peripheral_clock(RA_PCLK_SCICLK);

  if (baudrate == 0 || freq_hz == 0)
    {
      return -EINVAL;
    }

  /* First check common baud rate lookup table for exact matches */
  for (uint32_t i = 0; i < NUM_CLOCK_BAUD_TABLES; i++)
    {
      if (g_common_baud_settings[i].clock_freq == freq_hz)
        {
          /* Found matching clock frequency table */
          const struct common_baudrate_settings_s *settings = g_common_baud_settings[i].settings;
          uint32_t num_settings = g_common_baud_settings[i].num_settings;

          for (uint32_t j = 0; j < num_settings; j++)
            {
              if (settings[j].baud == baudrate)
                {
                  p_baud_setting->bgdm = settings[j].bgdm;
                  p_baud_setting->abcs = settings[j].abcs;
                  p_baud_setting->abcse = settings[j].abcse;
                  p_baud_setting->abcse2 = settings[j].abcse2;
                  p_baud_setting->cks = settings[j].cks;
                  p_baud_setting->brr = settings[j].brr;
                  /* Enable bit rate modulation if MDDR != 128 */
                  p_baud_setting->brme = (settings[j].mddr != 128) ? 1 : 0;
                  p_baud_setting->mddr = settings[j].mddr;
                  return 0;
                }
            }
          break; /* Found clock table but no matching baud rate */
        }
    }

  /* Initialize with worst case values for calculation */
  p_baud_setting->brr = 255;
  p_baud_setting->brme = 0;
  p_baud_setting->mddr = 256; /* Default value for no bit rate modulation */
  p_baud_setting->abcse2 = 0; /* Initialize ABCSE2 */

  /* Find the best BRR (bit rate register) value */
  for (uint32_t select_16_base_clk_cycles = 0;
       select_16_base_clk_cycles <= 1 && (hit_bit_err > 1500); /* 1.5% max error */
       select_16_base_clk_cycles++)
    {
      for (uint32_t i = 0; i < 13; i++)
        {
          /* Skip this calculation for divisors that don't match the clock cycle requirement */
          if (((uint8_t) select_16_base_clk_cycles) ^ (g_async_baud[i].abcs | g_async_baud[i].abcse))
            {
              continue;
            }

          divisor = (uint32_t) g_div_coefficient[i] * baudrate;
          uint32_t temp_brr = freq_hz / divisor;

          if (temp_brr <= 256) /* BRR can be 0-255 */
            {
              while (temp_brr > 0)
                {
                  temp_brr -= 1;

                  /* Calculate the bit rate error. Formula:
                   * bit rate error[%] = {(PCLK / (baud * div_coefficient * (BRR + 1)) - 1} x 100
                   */
                  int32_t err_divisor = (int32_t) (divisor * (temp_brr + 1));
                  int64_t bit_err_calc = (((int64_t) freq_hz) * 100000) / err_divisor - 100000;
                  int32_t bit_err = (int32_t) bit_err_calc;

                  uint16_t mddr = 256; /* No bit rate modulation */

                  /* Take the absolute value of the bit rate error */
                  if (bit_err < 0)
                    {
                      bit_err = -bit_err;
                    }

                  /* If this is the best error so far, save these settings */
                  if (bit_err < hit_bit_err)
                    {
                      p_baud_setting->bgdm = g_async_baud[i].bgdm;
                      p_baud_setting->abcs = g_async_baud[i].abcs;
                      p_baud_setting->abcse = g_async_baud[i].abcse;
                      p_baud_setting->abcse2 = 0; /* Assume ABCSE2=0 for calculation */
                      p_baud_setting->cks = g_async_baud[i].cks;
                      p_baud_setting->brr = (uint8_t) temp_brr;
                      p_baud_setting->mddr = mddr;
                      hit_bit_err = bit_err;
                    }

                  break; /* We don't implement bit rate modulation for simplicity */
                }
            }
        }
    }

  /* Return error if the percent error is too large (>1.5%) */
  if (hit_bit_err > 1500)
    {
      return -EINVAL;
    }

  return 0;
}

/****************************************************************************
 * Name: up_serialin
 ****************************************************************************/

static inline uint32_t up_serialin(struct up_dev_s *priv, int offset)
{
  /* RA uses SCI_B with 32-bit registers */
  if (offset >= R_SCI_B_CCR0_OFFSET)
    {
      return getreg32(priv->scibase + offset);
    }
  else
    {
      return getreg8(priv->scibase + offset);
    }
}

/****************************************************************************
 * Name: up_serialout
 ****************************************************************************/

static inline void up_serialout(struct up_dev_s *priv, int offset,
                                   uint32_t value)
{
  /* RA uses SCI_B with 32-bit registers */
  if (offset >= R_SCI_B_CCR0_OFFSET)
    {
      putreg32(value, priv->scibase + offset);
    }
  else
    {
      putreg8((uint8_t)value, priv->scibase + offset);
    }
}

/****************************************************************************
 * Name: up_disableallints
 ****************************************************************************/

static void up_disableallints(struct up_dev_s *priv, uint32_t *ie)
{
  irqstate_t flags;

  /* The following must be atomic */

  flags = enter_critical_section();

  /* RA uses SCI_B with 32-bit registers */
  if (ie)
    {
      /* Return the current interrupt mask */
      *ie = up_serialin(priv, R_SCI_B_CCR0_OFFSET);
    }

  /* Disable all interrupts */
  uint32_t regval = up_serialin(priv, R_SCI_B_CCR0_OFFSET) &
    ~(R_SCI_B_CCR0_TIE | R_SCI_B_CCR0_RIE | R_SCI_B_CCR0_TEIE);
  up_serialout(priv, R_SCI_B_CCR0_OFFSET, regval);

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: up_sci_config
 *
 * Description:
 *   Configure the SCI baud, bits, parity, etc. This method is called the
 *   first time that the serial port is opened.
 *
 ****************************************************************************/

static void up_sci_config(struct up_dev_s *priv)
{
  /* RA uses SCI_B (version 2) registers */
  uint32_t regval;
  struct baud_setting baud_setting;
  int ret;

  /* Disable SCI_B first */
  regval = 0;
  up_serialout(priv, R_SCI_B_CCR0_OFFSET, regval);

  /* Configure CCR1 for basic UART operation
   * From working XML: SPB2DT=1, SPB2IO=1 = 0x00000030
   */
  regval = R_SCI_B_CCR1_SPB2DT |     /* Serial port break data */
           R_SCI_B_CCR1_SPB2IO |     /* Serial port break I/O */
           0;                        /* No CTS flow control for basic UART */

  if (priv->parity == 1)  /* Odd parity */
    {
      regval |= R_SCI_B_CCR1_PE | R_SCI_B_CCR1_PM;
    }
  else if (priv->parity == 2)  /* Even parity */
    {
      regval |= R_SCI_B_CCR1_PE;
    }

  up_serialout(priv, R_SCI_B_CCR1_OFFSET, regval);

  /* Calculate baud rate settings dynamically */
  ret = up_calculate_baud_setting(priv->baud, &baud_setting);
  if (ret < 0)
    {
      /* Fallback to default 115200 baud if calculation fails */
      sinfo("Baud rate calculation failed for %lu, using 115200\n", (unsigned long)priv->baud);
      ret = up_calculate_baud_setting(115200, &baud_setting);
      if (ret < 0)
        {
          /* Final fallback to hardcoded values for 115200 */
          baud_setting.bgdm = 0;
          baud_setting.abcs = 0;
          baud_setting.abcse = 0;
          baud_setting.abcse2 = 0;
          baud_setting.cks = 1;
          baud_setting.brr = 24;
          baud_setting.brme = 0;
          baud_setting.mddr = 256;
        }
    }

  /* Configure CCR2 for baud rate generation using calculated values */
  regval = (baud_setting.bgdm ? R_SCI_B_CCR2_BGDM : 0) |
           (baud_setting.abcs ? R_SCI_B_CCR2_ABCS : 0) |
           (baud_setting.abcse ? R_SCI_B_CCR2_ABCSE : 0) |
           (baud_setting.abcse2 ? R_SCI_B_CCR2_ABCSE2 : 0) |
           (baud_setting.brme ? R_SCI_B_CCR2_BRME : 0) |
           ((uint32_t)baud_setting.cks << R_SCI_B_CCR2_CKS_SHIFT) |
           ((uint32_t)baud_setting.brr << R_SCI_B_CCR2_BRR_SHIFT) |
           ((uint32_t)baud_setting.mddr << R_SCI_B_CCR2_MDDR_SHIFT);

  up_serialout(priv, R_SCI_B_CCR2_OFFSET, regval);


  /* Detect FIFO capability for this channel */
  priv->fifo_depth = 0;
#ifdef CONFIG_RA_SCI_FIFO_MODE
  priv->fifo_depth = 16; /* RA8 SCI-B channels have 16-byte TX/RX FIFOs */
#endif

  /* Configure CCR3 for character format
   * From working XML: CHR=2 (8-bit), LSBF=1, RXDESEL=1 = 0x00009200
   * Enable FIFO Mode (FM=1) only if channel supports it
   */
  regval = R_SCI_B_CCR3_LSBF | R_SCI_B_CCR3_RXDESEL;
#ifdef CONFIG_RA_SCI_FIFO_MODE
  if (priv->fifo_depth > 0)
    {
      regval |= R_SCI_B_CCR3_FM;
    }
#endif

  if (priv->bits == 7)
    {
      regval |= (1 << R_SCI_B_CCR3_CHR_SHIFT); /* CHR=1 for 7-bit */
    }
  else
    {
      regval |= (2 << R_SCI_B_CCR3_CHR_SHIFT); /* CHR=2 for 8-bit (from XML) */
    }

  if (priv->stopbits2)
    {
      regval |= R_SCI_B_CCR3_STP;
    }

  up_serialout(priv, R_SCI_B_CCR3_OFFSET, regval);

  /* Configure CCR4 - no special features needed */
  regval = 0;
  up_serialout(priv, R_SCI_B_CCR4_OFFSET, regval);

#ifdef CONFIG_RA_SCI_FIFO_MODE
  /* Configure FIFO (FCR) only if channel supports it */
  if (priv->fifo_depth > 0)
    {
      /* Reset FIFOs first (RFRST=1, TFRST=1) */
      up_serialout(priv, R_SCI_B_FCR_OFFSET, R_SCI_B_FCR_RFRST | R_SCI_B_FCR_TFRST);

      uint32_t rx_trig = CONFIG_RA_SCI_FIFO_RX_TRIGGER & 0xF;
      uint32_t tx_trig = CONFIG_RA_SCI_FIFO_TX_TRIGGER & 0xF;
      uint32_t rts_trig = 15; /* RTS flow control at 15 (FIFO nearly full) */

      uint32_t fcr_val = (rx_trig << R_SCI_B_FCR_RTRG_SHIFT) |
                         (tx_trig << R_SCI_B_FCR_TTRG_SHIFT) |
                         (rts_trig << R_SCI_B_FCR_RSTRG_SHIFT);
      up_serialout(priv, R_SCI_B_FCR_OFFSET, fcr_val);
    }
#endif

  /* Clear any pending status flags */
  up_serialout(priv, R_SCI_B_CFCLR_OFFSET, 0xFFFFFFFF);
  up_serialout(priv, R_SCI_B_FFCLR_OFFSET, 0xFFFFFFFF);

  /* Enable transmit and receive
   * Match XML pattern: IDSEL=1, RE=1, TE=1 (interrupts controlled separately)
   */
  regval = R_SCI_B_CCR0_IDSEL | R_SCI_B_CCR0_TE | R_SCI_B_CCR0_RE;
  up_serialout(priv, R_SCI_B_CCR0_OFFSET, regval);

  /* Wait for receiver internal state = 1 (RIST bit)
   * This is critical for SCI_B proper initialization
   */
  while ((up_serialin(priv, R_SCI_B_CESR_OFFSET) & R_SCI_B_CESR_RIST) == 0)
    {
      /* Wait for RIST bit to be set */
    }
}

static int up_setup(struct uart_dev_s *dev)
{
  struct up_dev_s *priv = (struct up_dev_s *)dev->priv;

  /* Hardware setup for non-console devices (reset first) */
  if (!dev->isconsole)
    {
      up_shutdown(dev);
    }

  /* Enable module stop control for all SCI channels */
  putreg16((R_SYSC_PRCR_S_KEY | R_SYSC_PRCR_S_PRC1), R_SYSC_PRCR_S);
  modifyreg32(R_MSTP_MSTPCRB, priv->mstp, 0);
  putreg16(R_SYSC_PRCR_S_KEY, R_SYSC_PRCR_S);

  /* Read back to ensure write completed and add delay for module power-up */
  (void)getreg32(R_MSTP_MSTPCRB);

  /* Add a small delay to ensure the module is powered up */
  for (volatile int i = 0; i < 1000; i++)
    {
      /* Wait for module power-up */
    }

  /* Configure the UART hardware registers for both console and non-console devices */
  up_sci_config(priv);

  /* Setup is complete and ready for attach() to configure interrupts */
  return OK;
}

/****************************************************************************
 * Name: up_shutdown
 *
 * Description:
 *   Disable the SCI.
 *
 ****************************************************************************/

static void up_shutdown(struct uart_dev_s *dev)
{
  struct up_dev_s *priv = (struct up_dev_s *)dev->priv;

  /* Disable all interrupts */
  up_disableallints(priv, NULL);

  /* Reset SCI_B control */
  up_serialout(priv, R_SCI_B_CCR0_OFFSET, 0);

  /* Stop SCI  */
  putreg16((R_SYSC_PRCR_S_KEY | R_SYSC_PRCR_S_PRC1), R_SYSC_PRCR_S);
  modifyreg32(R_MSTP_MSTPCRB, priv->mstp, 1);
  putreg16(R_SYSC_PRCR_S_KEY, R_SYSC_PRCR_S);
}

/****************************************************************************
 * Name: up_attach
 *
 * Description:
 *   Configure the SCI to operation in interrupt driven mode.  This method
 *   is called when the serial port is opened.  Normally, this is just after
 *   the setup() method is called, however, the serial console may operate in
 *   a non-interrupt driven mode during the boot phase.
 *
 *   RX and TX interrupts are not enabled when by the attach method (unless
 *   the hardware supports multiple levels of interrupt enabling).  The RX
 *   and TX interrupts are not enabled until the txint() and rxint() methods
 *   are called.
 *
 ****************************************************************************/

static int up_attach(struct uart_dev_s *dev)
{
  struct up_dev_s   *priv = (struct up_dev_s *)dev->priv;
  int               ret;

#ifdef CONFIG_SERIAL_TXDMA
  /* Initialize DMAC for TX if channel is assigned */
  if (priv->dma_tx_chn >= 0)
    {
      ra_dmac_config_t dma_cfg;
      memset(&dma_cfg, 0, sizeof(dma_cfg));

      dma_cfg.mode = RA_DMAC_MODE_NORMAL;
      dma_cfg.size = RA_DMAC_SIZE_BYTE;
      dma_cfg.src_addr_mode = RA_DMAC_ADDR_INCR;
      dma_cfg.dest_addr_mode = RA_DMAC_ADDR_FIXED;
      dma_cfg.dest_addr = (uint32_t)(priv->scibase + R_SCI_B_TDR_OFFSET);
      dma_cfg.trigger = priv->elc_tx; /* Trigger on SCI TXI */
      dma_cfg.callback = up_dma_txcallback;
      dma_cfg.user_data = dev;

      /* Open DMAC channel */
      ret = ra_dmac_open_channel(priv->dma_tx_chn, &priv->dma_tx_handle, &dma_cfg);
      if (ret < 0)
        {
          serr("ERROR: Failed to open DMAC channel %d for SCI TX: %d\n",
               priv->dma_tx_chn, ret);
          /* Fallback to interrupt mode? For now, just warn. */
        }
      else
        {
          nxsem_init(&priv->dmatx_sem, 0, 0);
        }
    }
#endif

#ifdef CONFIG_SERIAL_RXDMA
  /* Initialize DMAC for RX */
  if (priv->dma_rx_chn >= 0)
    {
      ra_dmac_config_t dma_cfg;
      memset(&dma_cfg, 0, sizeof(dma_cfg));

      dma_cfg.mode = RA_DMAC_MODE_NORMAL;
      dma_cfg.src_addr = (uint32_t)(priv->scibase + R_SCI_B_RDR_OFFSET);
      dma_cfg.dest_addr = (uint32_t)dev->recv.buffer;
      dma_cfg.transfer_size = RA_DMAC_TRANSFER_SIZE_1BYTE;
      dma_cfg.src_addr_mode = RA_DMAC_ADDR_MODE_FIXED;
      dma_cfg.dest_addr_mode = RA_DMAC_ADDR_MODE_INCREMENTED;
      dma_cfg.trigger = priv->elc_rx; /* Trigger on SCI RXI */
      dma_cfg.callback = up_dma_rxcallback;
      dma_cfg.user_data = dev;

      /* Open DMAC channel */
      ret = ra_dmac_open_channel(priv->dma_rx_chn, &priv->dma_rx_handle, &dma_cfg);
      if (ret < 0)
        {
          serr("ERROR: Failed to open DMAC channel %d for SCI RX: %d\n",
               priv->dma_rx_chn, ret);
          /* Fallback to interrupt mode? For now, just warn. */
        }
    }
#endif

  /* Attach and enable the IRQ using the ICU API */

  ret = ra_icu_attach(priv->elc_rx, up_rxinterrupt, dev, true);
  if (ret < 0)
    {
      return ret;
    }
  priv->rxi_irq = ret; /* Store the assigned IRQ number */

  /* For TX, if using DMA, we still attach the interrupt but might keep it disabled
   * or use it for special cases. The DMAC will consume the ELC event.
   * However, NuttX serial logic expects us to enable/disable TX interrupts.
   */
  ret = ra_icu_attach(priv->elc_tx, up_txinterrupt, dev, true);
  if (ret < 0)
    {
      ra_icu_detach(priv->rxi_irq);
      return ret;
    }
  priv->txi_irq = ret; /* Store the assigned IRQ number */

  ret = ra_icu_attach(priv->elc_txe, up_txeinterrupt, dev, true);
  if (ret < 0)
    {
      ra_icu_detach(priv->rxi_irq);
      ra_icu_detach(priv->txi_irq);
      return ret;
    }
  priv->tei_irq = ret; /* Store the assigned IRQ number */

  ret = ra_icu_attach(priv->elc_err, up_erinterrupt, dev, true);
  if (ret < 0)
    {
      ra_icu_detach(priv->rxi_irq);
      ra_icu_detach(priv->txi_irq);
      ra_icu_detach(priv->tei_irq);
      return ret;
    }
  priv->eri_irq = ret; /* Store the assigned IRQ number */

  return OK;
}

static void up_detach(struct uart_dev_s *dev)
{
  struct up_dev_s *priv = (struct up_dev_s *)dev->priv;

#ifdef CONFIG_SERIAL_TXDMA
  if (priv->dma_tx_handle)
    {
      ra_dmac_close(priv->dma_tx_handle);
      priv->dma_tx_handle = NULL;
      nxsem_destroy(&priv->dmatx_sem);
    }
#endif

#ifdef CONFIG_SERIAL_RXDMA
  if (priv->dma_rx_handle)
    {
      ra_dmac_close(priv->dma_rx_handle);
      priv->dma_rx_handle = NULL;
    }
#endif

  ra_icu_detach(priv->rxi_irq);
  ra_icu_detach(priv->txi_irq);
  ra_icu_detach(priv->tei_irq);
  ra_icu_detach(priv->eri_irq);
}

/****************************************************************************
 * Name: up_rxinterrupt
 *
 * Description:
 *   This is the common SCI RX interrupt handler.
 *
 ****************************************************************************/

static int up_rxinterrupt(int irq, void *context, void *arg)
{
  struct uart_dev_s *dev = (struct uart_dev_s *)arg;

#ifdef CONFIG_SERIAL_RXDMA
  struct up_dev_s *priv = (struct up_dev_s *)dev->priv;
  if (priv->dma_rx_handle)
    {
      /* DMAC transfer in progress - update availability */
      up_dma_rxavailable(dev);
      uart_recvchars(dev);
      return OK;
    }
#endif

  uart_recvchars(dev);

  return OK;
}

/****************************************************************************
 * Name: up_txinterrupt
 *
 * Description:
 *   This is the common SCI TX interrupt handler.
 *
 ****************************************************************************/

static int up_txinterrupt(int irq, void *context, void *arg)
{
  struct uart_dev_s *dev = (struct uart_dev_s *)arg;

  uart_xmitchars(dev);

  return OK;
}

/****************************************************************************
 * Name: up_txeinterrupt
 *
 * Description:
 *   This is the common SCI TEI (Transmit End) interrupt handler.
 *   This interrupt occurs when transmission is completely finished.
 *
 ****************************************************************************/

static int up_txeinterrupt(int irq, void *context, void *arg)
{
  struct uart_dev_s *dev = (struct uart_dev_s *)arg;
  struct up_dev_s   *priv;

  DEBUGASSERT(dev != NULL && dev->priv != NULL);
  priv = (struct up_dev_s *)dev->priv;

  /* TEI interrupt indicates transmission is completely finished.
   * This is useful for RS-485 or other half-duplex protocols.
   * For now, we just clear the interrupt by reading the status.
   */

  up_serialin(priv, R_SCI_B_CSR_OFFSET);

  return OK;
}

/****************************************************************************
 * Name: up_erinterrupt
 *
 * Description:
 *   This is the common SCI Error interrupt handler.
 *
 ****************************************************************************/

static int up_erinterrupt(int irq, void *context, void *arg)
{
  struct uart_dev_s *dev = (struct uart_dev_s *)arg;
  struct up_dev_s   *priv;

  DEBUGASSERT(dev != NULL && dev->priv != NULL);
  priv = (struct up_dev_s *)dev->priv;

  /* Save for error reporting (SCI_B error bits) */
  priv->sr = up_serialin(priv, R_SCI_B_CSR_OFFSET) &
             (R_SCI_B_CSR_PER | R_SCI_B_CSR_FER | R_SCI_B_CSR_ORER);

  /* Clear error flags - this also clears the interrupt */
  up_serialout(priv, R_SCI_B_CFCLR_OFFSET,
               (R_SCI_B_CFCLR_PERC | R_SCI_B_CFCLR_FERC | R_SCI_B_CFCLR_ORERC));

  return OK;
}

/****************************************************************************
 * Name: up_ioctl
 *
 * Description:
 *   All ioctl calls will be routed through this method
 *
 ****************************************************************************/

static int up_ioctl(struct file *filep, int cmd, unsigned long arg)
{
  int ret = -ENOTTY;

  return ret;
}

/****************************************************************************
 * Name: up_receive
 *
 * Description:
 *   Called (usually) from the interrupt level to receive one
 *   character from the SCI.  Error bits associated with the
 *   receipt are provided in the return 'status'.
 *
 ****************************************************************************/

static int up_receive(struct uart_dev_s *dev, unsigned int *status)
{
  struct up_dev_s *priv = (struct up_dev_s *)dev->priv;
  int ch;

  /* Return the error information in the saved status */
  *status   = priv->sr;
  priv->sr  = 0;

  /* Read the received byte from the byte-access register */
  ch = (int)(up_serialin(priv, R_SCI_B_RDR_BY_OFFSET) & 0xff);

  /* Clear RDRF so the next RXI interrupt can fire (needed for FIFO mode too) */
  up_serialout(priv, R_SCI_B_CFCLR_OFFSET, R_SCI_B_CFCLR_RDRFC);

  return ch;
}

/****************************************************************************
 * Name: up_rxint
 *
 * Description:
 *   Call to enable or disable RX interrupts
 *
 ****************************************************************************/

static void up_rxint(struct uart_dev_s *dev, bool enable)
{
  struct up_dev_s *priv = (struct up_dev_s *)dev->priv;
  irqstate_t flags;

  flags = enter_critical_section();
  if (enable)
    {
#ifndef CONFIG_SUPPRESS_SERIAL_INTS
      /* Enable the RX interrupt */
      uint32_t regval = up_serialin(priv, R_SCI_B_CCR0_OFFSET);
      regval |= R_SCI_B_CCR0_RIE;
      up_serialout(priv, R_SCI_B_CCR0_OFFSET, regval);
#endif
    }
  else
    {
      /* Disable the RX interrupt */
      uint32_t regval = up_serialin(priv, R_SCI_B_CCR0_OFFSET);
      regval &= ~R_SCI_B_CCR0_RIE;
      up_serialout(priv, R_SCI_B_CCR0_OFFSET, regval);
    }

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: up_rxavailable
 *
 * Description:
 *   Return true if the receive holding register is not empty
 *
 ****************************************************************************/

static bool up_rxavailable(struct uart_dev_s *dev)
{
  struct up_dev_s *priv = (struct up_dev_s *)dev->priv;

#ifdef CONFIG_SERIAL_RXDMA
  if (priv->dma_rx_handle)
    {
      up_dma_rxavailable(dev);
      return (dev->recv.head != dev->recv.tail);
    }
#endif

#ifdef CONFIG_RA_SCI_FIFO_MODE
  /* With FIFO enabled, check receive count > 0 */
  if (priv->fifo_depth > 0)
    {
      return (up_serialin(priv, R_SCI_B_FRSR_OFFSET) & R_SCI_B_FRSR_R_MASK) != 0;
    }
#endif

  /* Non-FIFO path: rely on CSR.RDRF */
  return (up_serialin(priv, R_SCI_B_CSR_OFFSET) & R_SCI_B_CSR_RDRF) != 0;
}

#ifdef CONFIG_SERIAL_TXDMA
/****************************************************************************
 * Name: up_dma_txcallback
 *
 * Description:
 *   This function is called when the DMA transfer is complete.
 *
 ****************************************************************************/

#ifdef CONFIG_SERIAL_RXDMA
/****************************************************************************
 * Name: up_dma_rxavailable
 *
 * Description:
 *   Check for available RX data in DMA buffer and update head pointer.
 *
 ****************************************************************************/

static void up_dma_rxavailable(struct uart_dev_s *dev)
{
  struct up_dev_s *priv = (struct up_dev_s *)dev->priv;

  if (priv->dma_rx_handle)
    {
      uint32_t remaining = ra_dmac_getcount(priv->dma_rx_handle);
      uint32_t received = dev->recv.size - remaining;

      /* Update head. Assuming buffer starts at index 0. */
      dev->recv.head = received % dev->recv.size;

      /* Notify upper half */
      uart_recvchars(dev);
    }
}

/****************************************************************************
 * Name: up_dma_rxcallback
 *
 * Description:
 *   DMAC callback for RX transfer completion (buffer full).
 *
 ****************************************************************************/

static void up_dma_rxcallback(ra_dmac_handle_t handle, uint32_t event, void *user_data)
{
  struct uart_dev_s *dev = (struct uart_dev_s *)user_data;
  struct up_dev_s *priv = (struct up_dev_s *)dev->priv;

  /* DMAC completion event */
  if (event == RA_DMAC_EVENT_TRANSFER_END)
    {
      /* Transfer complete - update head position */
      up_dma_rxavailable(dev);

      /* Notify upper half of received data */
      uart_recvchars(dev);
    }
}
#endif

static void up_dma_txcallback(ra_dmac_handle_t handle, uint32_t event, void *arg)
{
  struct uart_dev_s *dev = (struct uart_dev_s *)arg;
  struct up_dev_s   *priv = (struct up_dev_s *)dev->priv;

  if (event & RA_DMAC_EVENT_COMPLETE)
    {
      /* DMA transfer completed.
       * Notify the upper half that the transfer is done.
       */
      uart_xmitchars(dev);
    }
}

/****************************************************************************
 * Name: up_dma_txavailable
 *
 * Description:
 *   This function is called to check if DMA is available.
 *
 ****************************************************************************/

static void up_dma_txavailable(struct uart_dev_s *dev)
{
  struct up_dev_s *priv = (struct up_dev_s *)dev->priv;

  /* If DMA is not initialized, fallback to interrupt */
  if (priv->dma_tx_handle == NULL)
    {
      uart_xmitchars(dev);
      return;
    }

  /* If DMA is busy, do nothing. The callback will trigger next send. */
  /* Note: We might need a way to check if DMA is active.
   * For now, we assume uart_xmitchars handles the flow.
   */
  uart_xmitchars(dev);
}

/****************************************************************************
 * Name: up_dma_send
 *
 * Description:
 *   This function is called to start a DMA transfer.
 *
 ****************************************************************************/

static void up_dma_send(struct uart_dev_s *dev)
{
  struct up_dev_s *priv = (struct up_dev_s *)dev->priv;

  /* If DMA is not initialized, fallback to interrupt send (not implemented here) */
  if (priv->dma_tx_handle == NULL)
    {
      /* This should not happen if dmasend is called */
      return;
    }

  /* Setup DMA transfer */
  /* Note: dev->dmatx.buffer and dev->dmatx.length are set by upper half */

  /* We need to flush cache if buffer is in cacheable region */
  up_clean_dcache((uintptr_t)dev->dmatx.buffer,
                  (uintptr_t)dev->dmatx.buffer + dev->dmatx.length);

  /* Reload DMAC configuration with new buffer */
  ra_dmac_reload(priv->dma_tx_handle,
                 (uint32_t)dev->dmatx.buffer,
                 (uint32_t)(priv->scibase + R_SCI_B_TDR_OFFSET),
                 dev->dmatx.length);

  /* Start DMAC */
  ra_dmac_start(priv->dma_tx_handle);

  /* Enable TX interrupts (TIE) to trigger DMAC?
   * On RA, the DMAC is triggered by the ELC event (SCI TXI).
   * We need to ensure SCI TXI is generated.
   * Setting TIE in CCR0 enables the interrupt output.
   * If DMAC is linked to the event, it intercepts it.
   */
  uint32_t regval = up_serialin(priv, R_SCI_B_CCR0_OFFSET);
  regval |= R_SCI_B_CCR0_TIE;
  up_serialout(priv, R_SCI_B_CCR0_OFFSET, regval);
}

/****************************************************************************
 * Name: up_dma_txint
 *
 * Description:
 *   Call to enable or disable TX interrupts for DMA
 *
 ****************************************************************************/

static void up_dma_txint(struct uart_dev_s *dev, bool enable)
{
  struct up_dev_s *priv = (struct up_dev_s *)dev->priv;
  irqstate_t flags;

  flags = enter_critical_section();
  if (enable)
    {
      /* Enable the TX interrupt to trigger DMA */
      uint32_t regval = up_serialin(priv, R_SCI_B_CCR0_OFFSET);
      regval |= R_SCI_B_CCR0_TIE;
      up_serialout(priv, R_SCI_B_CCR0_OFFSET, regval);

      /* If we are not using DMA (fallback), we would call uart_xmitchars here */
      if (priv->dma_tx_handle == NULL)
        {
           uart_xmitchars(dev);
        }
      else
        {
           /* Trigger DMA if needed? Usually enabling TIE is enough if TDR is empty */
           up_dma_txavailable(dev);
        }
    }
  else
    {
      /* Disable the TX interrupt */
      uint32_t regval = up_serialin(priv, R_SCI_B_CCR0_OFFSET);
      regval &= ~R_SCI_B_CCR0_TIE;
      up_serialout(priv, R_SCI_B_CCR0_OFFSET, regval);

      /* Also stop DMA if running? */
      if (priv->dma_tx_handle)
        {
          ra_dmac_stop(priv->dma_tx_handle);
        }
    }

  leave_critical_section(flags);
}
#endif

/****************************************************************************
 * Name: up_send
 *
 * Description:
 *   This method will send one byte on the SCI
 *
 ****************************************************************************/

static void up_send(struct uart_dev_s *dev, int ch)
{
  struct up_dev_s *priv = (struct up_dev_s *)dev->priv;

  /* Send the character to TDR_BY register (byte access) */
  up_serialout(priv, R_SCI_B_TDR_BY_OFFSET, (uint8_t)ch);

  /* Clear TDRE so the next TXI interrupt can be generated (FIFO and non-FIFO) */
  up_serialout(priv, R_SCI_B_CFCLR_OFFSET, R_SCI_B_CFCLR_TDREC);
}

/****************************************************************************
 * Name: up_txint
 *
 * Description:
 *   Call to enable or disable TX interrupts
 *
 ****************************************************************************/

static void up_txint(struct uart_dev_s *dev, bool enable)
{
  struct up_dev_s *priv = (struct up_dev_s *)dev->priv;
  irqstate_t flags;

  flags = enter_critical_section();
  if (enable)
    {
#ifndef CONFIG_SUPPRESS_SERIAL_INTS
      /* Enable the TX interrupt and TEI interrupt */
      uint32_t regval = up_serialin(priv, R_SCI_B_CCR0_OFFSET);
      regval |= (R_SCI_B_CCR0_TIE | R_SCI_B_CCR0_TEIE);
      up_serialout(priv, R_SCI_B_CCR0_OFFSET, regval);

      /* Fake a TX interrupt here by just calling uart_xmitchars() with
       * interrupts disabled (note this may recurse).
       */
       uart_xmitchars(dev);
#endif
    }
  else
    {
      /* Disable the TX interrupt and TEI interrupt */
      uint32_t regval = up_serialin(priv, R_SCI_B_CCR0_OFFSET);
      regval &= ~(R_SCI_B_CCR0_TIE | R_SCI_B_CCR0_TEIE);
      up_serialout(priv, R_SCI_B_CCR0_OFFSET, regval);
    }

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: up_txready
 *
 * Description:
 *   Return true if the transmit holding register is empty (SSR.TDRE)
 *
 ****************************************************************************/

static bool up_txready(struct uart_dev_s *dev)
{
  struct up_dev_s *priv = (struct up_dev_s *)dev->priv;

  return ((up_serialin(priv, R_SCI_B_CSR_OFFSET) & R_SCI_B_CSR_TDRE) == R_SCI_B_CSR_TDRE);
}

/****************************************************************************
 * Name: up_txempty
 *
 * Description:
 *   Return true if the transmit holding and shift registers are empty
 *
 ****************************************************************************/

static bool up_txempty(struct uart_dev_s *dev)
{
  struct up_dev_s *priv = (struct up_dev_s *)dev->priv;

  return (up_serialin(priv, R_SCI_B_CSR_OFFSET) & R_SCI_B_CSR_TEND) != 0;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: arm_earlyserialinit
 *
 * Description:
 *   Performs the low level SCI initialization early in debug so that the
 *   serial console will be available during boot up.  This must be called
 *   before arm_serialinit.
 *
 ****************************************************************************/

void arm_earlyserialinit(void)
{
  /* Disable all UART interrupts on all devices */

#ifdef TTYS0_DEV
  up_disableallints(TTYS0_DEV.priv, NULL);
#endif
#ifdef TTYS1_DEV
  up_disableallints(TTYS1_DEV.priv, NULL);
#endif
#ifdef TTYS2_DEV
  up_disableallints(TTYS2_DEV.priv, NULL);
#endif
#ifdef TTYS3_DEV
  up_disableallints(TTYS3_DEV.priv, NULL);
#endif
#ifdef TTYS4_DEV
  up_disableallints(TTYS4_DEV.priv, NULL);
#endif
#ifdef TTYS5_DEV
  up_disableallints(TTYS5_DEV.priv, NULL);
#endif
#ifdef TTYS6_DEV
  up_disableallints(TTYS6_DEV.priv, NULL);
#endif
#ifdef TTYS7_DEV
  up_disableallints(TTYS7_DEV.priv, NULL);
#endif
#ifdef TTYS8_DEV
  up_disableallints(TTYS8_DEV.priv, NULL);
#endif
#ifdef TTYS9_DEV
  up_disableallints(TTYS9_DEV.priv, NULL);
#endif

#ifdef HAVE_CONSOLE
  /* Configure the console device */
  CONSOLE_DEV.isconsole = true;

  /* Call up_setup() for console device to handle complete initialization */
  up_setup(&CONSOLE_DEV);
#endif

  /* Initialize hardware for all non-console UART devices */
#ifdef TTYS0_DEV
#ifndef HAVE_CONSOLE
  /* If no console, or if TTYS0 is not the console, initialize it */
  up_setup(&TTYS0_DEV);
#elif !defined(CONFIG_SCI0_SERIAL_CONSOLE) && !defined(CONFIG_SCI1_SERIAL_CONSOLE) && \
 !defined(CONFIG_SCI2_SERIAL_CONSOLE) && !defined(CONFIG_SCI3_SERIAL_CONSOLE) && \
 !defined(CONFIG_SCI4_SERIAL_CONSOLE) && !defined(CONFIG_SCI5_SERIAL_CONSOLE) && \
 !defined(CONFIG_SCI6_SERIAL_CONSOLE) && !defined(CONFIG_SCI7_SERIAL_CONSOLE) && \
 !defined(CONFIG_SCI8_SERIAL_CONSOLE) && !defined(CONFIG_SCI9_SERIAL_CONSOLE)
  /* TTYS0 is not the console, initialize it */
  up_setup(&TTYS0_DEV);
#endif
#endif

  /* Initialize non-console UART devices */
#ifdef TTYS1_DEV
  up_setup(&TTYS1_DEV);
#endif

#ifdef TTYS2_DEV
  up_setup(&TTYS2_DEV);
#endif

#ifdef TTYS3_DEV
  up_setup(&TTYS3_DEV);
#endif

#ifdef TTYS4_DEV
  up_setup(&TTYS4_DEV);
#endif

#ifdef TTYS5_DEV
  up_setup(&TTYS5_DEV);
#endif

#ifdef TTYS6_DEV
  up_setup(&TTYS6_DEV);
#endif

#ifdef TTYS7_DEV
  up_setup(&TTYS7_DEV);
#endif

#ifdef TTYS8_DEV
  up_setup(&TTYS8_DEV);
#endif

#ifdef TTYS9_DEV
  up_setup(&TTYS9_DEV);
#endif
}

/****************************************************************************
 * Name: arm_serialinit
 *
 * Description:
 *   Register serial console and serial ports.  This assumes
 *   that arm_earlyserialinit was called previously.
 *
 ****************************************************************************/

void arm_serialinit(void)
{
  /* Register the console */
#ifdef HAVE_CONSOLE
  uart_register("/dev/console", &CONSOLE_DEV);
#endif
  /* Register all SCIs */
#ifdef TTYS0_DEV
  uart_register("/dev/ttyS0", &TTYS0_DEV);
#endif
#ifdef TTYS1_DEV
  uart_register("/dev/ttyS1", &TTYS1_DEV);
#endif
#ifdef TTYS2_DEV
  uart_register("/dev/ttyS2", &TTYS2_DEV);
#endif
#ifdef TTYS3_DEV
  uart_register("/dev/ttyS3", &TTYS3_DEV);
#endif
#ifdef TTYS4_DEV
  uart_register("/dev/ttyS4", &TTYS4_DEV);
#endif
#ifdef TTYS5_DEV
  uart_register("/dev/ttyS5", &TTYS5_DEV);
#endif
#ifdef TTYS6_DEV
  uart_register("/dev/ttyS6", &TTYS6_DEV);
#endif
#ifdef TTYS7_DEV
  uart_register("/dev/ttyS7", &TTYS7_DEV);
#endif
#ifdef TTYS8_DEV
  uart_register("/dev/ttyS8", &TTYS8_DEV);
#endif
#ifdef TTYS9_DEV
  uart_register("/dev/ttyS9", &TTYS9_DEV);
#endif
}

#endif /* HAVE_UART */

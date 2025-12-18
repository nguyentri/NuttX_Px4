/****************************************************************************
 * arch/arm/src/rzv/rzv_lowputc.c
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

#include "chip.h"
#include "arm_internal.h"
#include "rzv_lowputc.h"
#include "rzv_clock.h"
#include "rzv_gpio.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCIF (Serial Communication Interface with FIFO) Register Offsets */
#define RZV_SCIF_SMR_OFFSET      0x00  /* Serial Mode Register */
#define RZV_SCIF_BRR_OFFSET      0x02  /* Bit Rate Register */
#define RZV_SCIF_SCR_OFFSET      0x04  /* Serial Control Register */
#define RZV_SCIF_FTDR_OFFSET     0x06  /* Transmit FIFO Data Register */
#define RZV_SCIF_FSR_OFFSET      0x08  /* Serial Status Register */
#define RZV_SCIF_FRDR_OFFSET     0x0A  /* Receive FIFO Data Register */
#define RZV_SCIF_FCR_OFFSET      0x0C  /* FIFO Control Register */
#define RZV_SCIF_FDR_OFFSET      0x0E  /* FIFO Data Count Register */
#define RZV_SCIF_SPTR_OFFSET     0x10  /* Serial Port Register */
#define RZV_SCIF_LSR_OFFSET      0x12  /* Line Status Register */

/* Serial Mode Register (SMR) bit definitions */
#define SCIF_SMR_CKS_MASK        0x0003  /* Clock Select */
#define SCIF_SMR_CKS_DIV1        0x0000  /* PCLK */
#define SCIF_SMR_CKS_DIV4        0x0001  /* PCLK/4 */
#define SCIF_SMR_CKS_DIV16       0x0002  /* PCLK/16 */
#define SCIF_SMR_CKS_DIV64       0x0003  /* PCLK/64 */
#define SCIF_SMR_STOP            0x0008  /* Stop Bit Length (1=2 bits) */
#define SCIF_SMR_PM              0x0010  /* Parity Mode (0=even, 1=odd) */
#define SCIF_SMR_PE              0x0020  /* Parity Enable */
#define SCIF_SMR_CHR             0x0040  /* Character Length (0=8bit, 1=7bit) */
#define SCIF_SMR_CM              0x0080  /* Communication Mode (0=async) */

/* Serial Control Register (SCR) bit definitions */
#define SCIF_SCR_CKE_MASK        0x0003  /* Clock Enable */
#define SCIF_SCR_TEIE            0x0004  /* Transmit End Interrupt Enable */
#define SCIF_SCR_REIE            0x0008  /* Receive Error Interrupt Enable */
#define SCIF_SCR_RE              0x0010  /* Receive Enable */
#define SCIF_SCR_TE              0x0020  /* Transmit Enable */
#define SCIF_SCR_RIE             0x0040  /* Receive Interrupt Enable */
#define SCIF_SCR_TIE             0x0080  /* Transmit Interrupt Enable */

/* Serial Status Register (FSR) bit definitions */
#define SCIF_FSR_DR              0x0001  /* Receive Data Ready */
#define SCIF_FSR_RDF             0x0002  /* Receive FIFO Full */
#define SCIF_FSR_PER             0x0004  /* Parity Error */
#define SCIF_FSR_FER             0x0008  /* Framing Error */
#define SCIF_FSR_BRK             0x0010  /* Break Detect */
#define SCIF_FSR_TDFE            0x0020  /* Transmit FIFO Empty */
#define SCIF_FSR_TEND            0x0040  /* Transmit End */
#define SCIF_FSR_ER              0x0080  /* Receive Error */
#define SCIF_FSR_FER_MASK        0x0F00  /* Framing Error Count */
#define SCIF_FSR_PER_MASK        0xF000  /* Parity Error Count */

/* FIFO Control Register (FCR) bit definitions */
#define SCIF_FCR_LOOP            0x0001  /* Loopback Test */
#define SCIF_FCR_RFRST           0x0002  /* Receive FIFO Reset */
#define SCIF_FCR_TFRST           0x0004  /* Transmit FIFO Reset */
#define SCIF_FCR_MCE             0x0008  /* Modem Control Enable */
#define SCIF_FCR_TTRG_MASK       0x0030  /* Transmit FIFO Trigger */
#define SCIF_FCR_TTRG_8          0x0000  /* 8 bytes */
#define SCIF_FCR_TTRG_4          0x0010  /* 4 bytes */
#define SCIF_FCR_TTRG_2          0x0020  /* 2 bytes */
#define SCIF_FCR_TTRG_1          0x0030  /* 1 byte */
#define SCIF_FCR_RTRG_MASK       0x00C0  /* Receive FIFO Trigger */
#define SCIF_FCR_RTRG_1          0x0000  /* 1 byte */
#define SCIF_FCR_RTRG_4          0x0040  /* 4 bytes */
#define SCIF_FCR_RTRG_8          0x0080  /* 8 bytes */
#define SCIF_FCR_RTRG_14         0x00C0  /* 14 bytes */
#define SCIF_FCR_RSTRG_MASK      0x0700  /* RTS Output Active Trigger */
#define SCIF_FCR_RSTRG_15        0x0000  /* 15 bytes or more */
#define SCIF_FCR_RSTRG_1         0x0100  /* 1 byte or more */
#define SCIF_FCR_RSTRG_4         0x0200  /* 4 bytes or more */
#define SCIF_FCR_RSTRG_6         0x0300  /* 6 bytes or more */
#define SCIF_FCR_RSTRG_8         0x0400  /* 8 bytes or more */
#define SCIF_FCR_RSTRG_10        0x0500  /* 10 bytes or more */
#define SCIF_FCR_RSTRG_12        0x0600  /* 12 bytes or more */
#define SCIF_FCR_RSTRG_14        0x0700  /* 14 bytes or more */

/* Line Status Register (LSR) bit definitions */
#define SCIF_LSR_ORER            0x0001  /* Overrun Error */

/* Console UART selection - default to SCIF0 */
#ifndef CONFIG_RZV_CONSOLE_UART
#  define CONFIG_RZV_CONSOLE_UART 0
#endif

/* Get console UART base address */
#if CONFIG_RZV_CONSOLE_UART == 0
#  define CONSOLE_BASE    RZV_SCI0_BASE
#elif CONFIG_RZV_CONSOLE_UART == 1
#  define CONSOLE_BASE    RZV_SCI1_BASE
#elif CONFIG_RZV_CONSOLE_UART == 2
#  define CONSOLE_BASE    RZV_SCI2_BASE
#elif CONFIG_RZV_CONSOLE_UART == 3
#  define CONSOLE_BASE    RZV_SCI3_BASE
#else
#  error "Invalid console UART selection"
#endif

/* Default UART configuration */
#ifndef CONFIG_RZV_CONSOLE_BAUD
#  define CONFIG_RZV_CONSOLE_BAUD 115200
#endif

#ifndef CONFIG_RZV_CONSOLE_BITS
#  define CONFIG_RZV_CONSOLE_BITS 8
#endif

#ifndef CONFIG_RZV_CONSOLE_PARITY
#  define CONFIG_RZV_CONSOLE_PARITY 0  /* 0=none, 1=odd, 2=even */
#endif

#ifndef CONFIG_RZV_CONSOLE_2STOP
#  define CONFIG_RZV_CONSOLE_2STOP 0
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_scif_getreg16
 *
 * Description:
 *   Read a 16-bit SCIF register
 *
 ****************************************************************************/

static inline uint16_t rzv_scif_getreg16(uintptr_t base, unsigned int offset)
{
  return getreg16(base + offset);
}

/****************************************************************************
 * Name: rzv_scif_putreg16
 *
 * Description:
 *   Write a 16-bit SCIF register
 *
 ****************************************************************************/

static inline void rzv_scif_putreg16(uint16_t value, uintptr_t base,
                                      unsigned int offset)
{
  putreg16(value, base + offset);
}

/****************************************************************************
 * Name: rzv_scif_getreg8
 *
 * Description:
 *   Read an 8-bit SCIF register
 *
 ****************************************************************************/

static inline uint8_t rzv_scif_getreg8(uintptr_t base, unsigned int offset)
{
  return getreg8(base + offset);
}

/****************************************************************************
 * Name: rzv_scif_putreg8
 *
 * Description:
 *   Write an 8-bit SCIF register
 *
 ****************************************************************************/

static inline void rzv_scif_putreg8(uint8_t value, uintptr_t base,
                                     unsigned int offset)
{
  putreg8(value, base + offset);
}

/****************************************************************************
 * Name: rzv_scif_waittxready
 *
 * Description:
 *   Wait until the TX FIFO is ready to accept more data
 *
 ****************************************************************************/

static void rzv_scif_waittxready(uintptr_t base)
{
  uint16_t fsr;
  int timeout = 10000;

  do
    {
      fsr = rzv_scif_getreg16(base, RZV_SCIF_FSR_OFFSET);
    }
  while ((fsr & SCIF_FSR_TDFE) == 0 && --timeout > 0);
}

/****************************************************************************
 * Name: rzv_scif_setbaud
 *
 * Description:
 *   Configure the SCIF baud rate
 *
 ****************************************************************************/

static void rzv_scif_setbaud(uintptr_t base, uint32_t baud)
{
  uint32_t pclk;
  uint32_t divisor;
  uint8_t brr;
  uint8_t cks;

  /* Get peripheral clock frequency */
  pclk = rzv_get_pclk_frequency();

  /* Calculate divisor for target baud rate
   * BRR = (PCLK / (64 * 2^(2n-1) * Baud)) - 1
   * where n is the CKS value (0-3)
   */

  /* Try different CKS values to find best match */
  for (cks = 0; cks <= 3; cks++)
    {
      divisor = pclk / (32 * (1 << (2 * cks)) * baud);
      if (divisor > 0 && divisor <= 256)
        {
          brr = (uint8_t)(divisor - 1);
          break;
        }
    }

  if (cks > 3)
    {
      /* Could not find suitable divisor, use defaults */
      cks = 0;
      brr = 0;
    }

  /* Set bit rate register */
  rzv_scif_putreg8(brr, base, RZV_SCIF_BRR_OFFSET);

  /* Set clock select in SMR */
  uint8_t smr = rzv_scif_getreg8(base, RZV_SCIF_SMR_OFFSET);
  smr = (smr & ~SCIF_SMR_CKS_MASK) | (cks & SCIF_SMR_CKS_MASK);
  rzv_scif_putreg8(smr, base, RZV_SCIF_SMR_OFFSET);

  /* Wait for at least 1 bit time */
  up_udelay((1000000 / baud) + 1);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Function: rzv_lowsetup
 *
 * Description:
 *   Called at the very beginning of _start.  Performs low level
 *   initialization including setup of the console uart.  This uart done
 *   early so that the serial console is available for debugging very early
 *   in the boot sequence.
 *
 ****************************************************************************/

void rzv_lowsetup(void)
{
  uint8_t smr;
  uint16_t scr;
  uint16_t fcr;

#if defined(CONFIG_SUPPRESS_UART_CONFIG)
  /* Just enable the console UART for early debug output */
  scr = rzv_scif_getreg16(CONSOLE_BASE, RZV_SCIF_SCR_OFFSET);
  scr |= SCIF_SCR_TE | SCIF_SCR_RE;
  rzv_scif_putreg16(scr, CONSOLE_BASE, RZV_SCIF_SCR_OFFSET);
  return;
#endif

  /* Disable transmit and receive */
  rzv_scif_putreg16(0, CONSOLE_BASE, RZV_SCIF_SCR_OFFSET);

  /* Configure GPIO pins for UART function */
#if CONFIG_RZV_CONSOLE_UART == 0
  /* Configure TXD0 and RXD0 pins - adjust based on board */
  /* Example: Port 20, Pin 0 (TXD0) and Pin 1 (RXD0) */
  rzv_gpioconfig(GPIO_PERIPH_PIN(0x20, 0, 1));  /* TXD0 */
  rzv_gpioconfig(GPIO_PERIPH_PIN(0x20, 1, 1));  /* RXD0 */
#endif

  /* Reset FIFOs */
  fcr = SCIF_FCR_TFRST | SCIF_FCR_RFRST;
  rzv_scif_putreg16(fcr, CONSOLE_BASE, RZV_SCIF_FCR_OFFSET);

  /* Wait for reset to complete */
  up_udelay(100);

  /* Configure FIFO control register */
  fcr = SCIF_FCR_TTRG_8 | SCIF_FCR_RTRG_1;
  rzv_scif_putreg16(fcr, CONSOLE_BASE, RZV_SCIF_FCR_OFFSET);

  /* Configure serial mode register */
  smr = 0;  /* Start with async mode, 8 bits, no parity, 1 stop */

#if CONFIG_RZV_CONSOLE_BITS == 7
  smr |= SCIF_SMR_CHR;
#endif

#if CONFIG_RZV_CONSOLE_PARITY == 1
  smr |= SCIF_SMR_PE | SCIF_SMR_PM;  /* Odd parity */
#elif CONFIG_RZV_CONSOLE_PARITY == 2
  smr |= SCIF_SMR_PE;  /* Even parity */
#endif

#if CONFIG_RZV_CONSOLE_2STOP != 0
  smr |= SCIF_SMR_STOP;
#endif

  rzv_scif_putreg8(smr, CONSOLE_BASE, RZV_SCIF_SMR_OFFSET);

  /* Set baud rate */
  rzv_scif_setbaud(CONSOLE_BASE, CONFIG_RZV_CONSOLE_BAUD);

  /* Clear all status flags */
  rzv_scif_putreg16(0, CONSOLE_BASE, RZV_SCIF_FSR_OFFSET);
  rzv_scif_putreg16(0, CONSOLE_BASE, RZV_SCIF_LSR_OFFSET);

  /* Enable transmit and receive */
  scr = SCIF_SCR_TE | SCIF_SCR_RE;
  rzv_scif_putreg16(scr, CONSOLE_BASE, RZV_SCIF_SCR_OFFSET);
}

/****************************************************************************
 * Function: rzv_lowputc
 *
 * Description:
 *   Low-level character output
 *
 ****************************************************************************/

void rzv_lowputc(char ch)
{
  uint16_t fsr;

  /* Wait for transmit FIFO to be ready */
  rzv_scif_waittxready(CONSOLE_BASE);

  /* Write character to transmit data register */
  rzv_scif_putreg8((uint8_t)ch, CONSOLE_BASE, RZV_SCIF_FTDR_OFFSET);

  /* Clear TDFE flag */
  fsr = rzv_scif_getreg16(CONSOLE_BASE, RZV_SCIF_FSR_OFFSET);
  fsr &= ~SCIF_FSR_TDFE;
  rzv_scif_putreg16(fsr, CONSOLE_BASE, RZV_SCIF_FSR_OFFSET);
}

/****************************************************************************
 * Function: rzv_earlyserialinit
 *
 * Description:
 *   Performs the low level UART initialization early in debug so that the
 *   serial console will be available during bootup.  This must be called
 *   before arm_serialinit.
 *
 ****************************************************************************/

void rzv_earlyserialinit(void)
{
  /* The console was already initialized by rzv_lowsetup */

  /* Disable all UART interrupts except the console */
  /* This will be done in the full serial initialization */
}

/****************************************************************************
 * Function: arm_lowputc
 *
 * Description:
 *   Output one byte on the serial console (for assertions)
 *
 ****************************************************************************/

void arm_lowputc(char ch)
{
  rzv_lowputc(ch);
}
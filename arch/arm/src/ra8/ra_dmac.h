/****************************************************************************
 * arch/arm/src/ra8/ra_dmac.h
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

#ifndef __ARCH_ARM_SRC_RA_RA8_DMAC_H
#define __ARCH_ARM_SRC_RA_RA8_DMAC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

#include "chip.h"
#include "hardware/ra_memorymap.h"

/****************************************************************************
 * Validate RA DMAC channel Kconfig values.
 * These checks ensure that users do not select invalid non-existent channel
 * numbers 8 and 9 (there are two DMAC units enabling channels 0-7 and
 * 10-17). Kconfig allows ranges and we use compile-time checks to trap
 * invalid assignments early.
****************************************************************************/

#ifdef CONFIG_RA_DMAC_SPI0_TX_CHANNEL
#if (CONFIG_RA_DMAC_SPI0_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_SPI0_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SPI0_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SPI0_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_SPI0_RX_CHANNEL
#if (CONFIG_RA_DMAC_SPI0_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_SPI0_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SPI0_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SPI0_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_SPI1_TX_CHANNEL
#if (CONFIG_RA_DMAC_SPI1_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_SPI1_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SPI1_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SPI1_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_SPI1_RX_CHANNEL
#if (CONFIG_RA_DMAC_SPI1_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_SPI1_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SPI1_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SPI1_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_I2C0_CHANNEL
#if (CONFIG_RA_DMAC_I2C0_CHANNEL == 8) || (CONFIG_RA_DMAC_I2C0_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_I2C0_CHANNEL > 17)
#error "CONFIG_RA_DMAC_I2C0_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_I2C1_CHANNEL
#if (CONFIG_RA_DMAC_I2C1_CHANNEL == 8) || (CONFIG_RA_DMAC_I2C1_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_I2C1_CHANNEL > 17)
#error "CONFIG_RA_DMAC_I2C1_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_I2C2_CHANNEL
#if (CONFIG_RA_DMAC_I2C2_CHANNEL == 8) || (CONFIG_RA_DMAC_I2C2_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_I2C2_CHANNEL > 17)
#error "CONFIG_RA_DMAC_I2C2_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_ADC_CHANNEL
#if (CONFIG_RA_DMAC_ADC_CHANNEL == 8) || (CONFIG_RA_DMAC_ADC_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_ADC_CHANNEL > 17)
#error "CONFIG_RA_DMAC_ADC_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART0_TX_CHANNEL
#if (CONFIG_RA_DMAC_UART0_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART0_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART0_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART0_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART0_RX_CHANNEL
#if (CONFIG_RA_DMAC_UART0_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART0_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART0_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART0_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART1_TX_CHANNEL
#if (CONFIG_RA_DMAC_UART1_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART1_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART1_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART1_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART1_RX_CHANNEL
#if (CONFIG_RA_DMAC_UART1_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART1_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART1_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART1_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART2_TX_CHANNEL
#if (CONFIG_RA_DMAC_UART2_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART2_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART2_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART2_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART2_RX_CHANNEL
#if (CONFIG_RA_DMAC_UART2_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART2_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART2_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART2_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART3_TX_CHANNEL
#if (CONFIG_RA_DMAC_UART3_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART3_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART3_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART3_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART3_RX_CHANNEL
#if (CONFIG_RA_DMAC_UART3_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART3_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART3_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART3_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART4_TX_CHANNEL
#if (CONFIG_RA_DMAC_UART4_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART4_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART4_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART4_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART4_RX_CHANNEL
#if (CONFIG_RA_DMAC_UART4_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART4_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART4_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART4_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART5_TX_CHANNEL
#if (CONFIG_RA_DMAC_UART5_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART5_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART5_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART5_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART5_RX_CHANNEL
#if (CONFIG_RA_DMAC_UART5_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART5_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART5_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART5_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART6_TX_CHANNEL
#if (CONFIG_RA_DMAC_UART6_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART6_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART6_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART6_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART6_RX_CHANNEL
#if (CONFIG_RA_DMAC_UART6_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART6_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART6_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART6_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART7_TX_CHANNEL
#if (CONFIG_RA_DMAC_UART7_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART7_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART7_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART7_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART7_RX_CHANNEL
#if (CONFIG_RA_DMAC_UART7_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART7_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART7_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART7_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART8_TX_CHANNEL
#if (CONFIG_RA_DMAC_UART8_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART8_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART8_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART8_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART8_RX_CHANNEL
#if (CONFIG_RA_DMAC_UART8_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART8_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART8_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART8_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART9_TX_CHANNEL
#if (CONFIG_RA_DMAC_UART9_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART9_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART9_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART9_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_UART9_RX_CHANNEL
#if (CONFIG_RA_DMAC_UART9_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_UART9_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_UART9_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_UART9_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_SDRAM_CHANNEL
#if (CONFIG_RA_DMAC_SDRAM_CHANNEL == 8) || (CONFIG_RA_DMAC_SDRAM_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SDRAM_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SDRAM_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_SCI0_SPI_TX_CHANNEL
#if (CONFIG_RA_DMAC_SCI0_SPI_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_SCI0_SPI_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SCI0_SPI_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SCI0_SPI_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_SCI0_SPI_RX_CHANNEL
#if (CONFIG_RA_DMAC_SCI0_SPI_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_SCI0_SPI_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SCI0_SPI_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SCI0_SPI_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_SCI1_SPI_TX_CHANNEL
#if (CONFIG_RA_DMAC_SCI1_SPI_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_SCI1_SPI_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SCI1_SPI_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SCI1_SPI_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_SCI1_SPI_RX_CHANNEL
#if (CONFIG_RA_DMAC_SCI1_SPI_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_SCI1_SPI_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SCI1_SPI_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SCI1_SPI_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_SCI2_SPI_TX_CHANNEL
#if (CONFIG_RA_DMAC_SCI2_SPI_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_SCI2_SPI_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SCI2_SPI_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SCI2_SPI_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_SCI2_SPI_RX_CHANNEL
#if (CONFIG_RA_DMAC_SCI2_SPI_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_SCI2_SPI_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SCI2_SPI_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SCI2_SPI_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_SCI3_SPI_TX_CHANNEL
#if (CONFIG_RA_DMAC_SCI3_SPI_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_SCI3_SPI_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SCI3_SPI_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SCI3_SPI_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_SCI3_SPI_RX_CHANNEL
#if (CONFIG_RA_DMAC_SCI3_SPI_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_SCI3_SPI_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SCI3_SPI_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SCI3_SPI_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif

#ifdef CONFIG_RA_DMAC_SCI4_SPI_TX_CHANNEL
#if (CONFIG_RA_DMAC_SCI4_SPI_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_SCI4_SPI_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SCI4_SPI_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SCI4_SPI_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_SCI4_SPI_RX_CHANNEL
#if (CONFIG_RA_DMAC_SCI4_SPI_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_SCI4_SPI_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SCI4_SPI_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SCI4_SPI_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_SCI9_SPI_TX_CHANNEL
#if (CONFIG_RA_DMAC_SCI9_SPI_TX_CHANNEL == 8) || (CONFIG_RA_DMAC_SCI9_SPI_TX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SCI9_SPI_TX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SCI9_SPI_TX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_SCI9_SPI_RX_CHANNEL
#if (CONFIG_RA_DMAC_SCI9_SPI_RX_CHANNEL == 8) || (CONFIG_RA_DMAC_SCI9_SPI_RX_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SCI9_SPI_RX_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SCI9_SPI_RX_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif
#ifdef CONFIG_RA_DMAC_USBFS_D0FIFO_CHANNEL
#if (CONFIG_RA_DMAC_USBFS_D0FIFO_CHANNEL == 8) || (CONFIG_RA_DMAC_USBFS_D0FIFO_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_USBFS_D0FIFO_CHANNEL > 17)
#error "CONFIG_RA_DMAC_USBFS_D0FIFO_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_USBFS_D1FIFO_CHANNEL
#if (CONFIG_RA_DMAC_USBFS_D1FIFO_CHANNEL == 8) || (CONFIG_RA_DMAC_USBFS_D1FIFO_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_USBFS_D1FIFO_CHANNEL > 17)
#error "CONFIG_RA_DMAC_USBFS_D1FIFO_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif
#ifdef CONFIG_RA_DMAC_GPT0_CHANNEL
#if (CONFIG_RA_DMAC_GPT0_CHANNEL == 8) || (CONFIG_RA_DMAC_GPT0_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_GPT0_CHANNEL > 17)
#error "CONFIG_RA_DMAC_GPT0_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_GPT1_CHANNEL
#if (CONFIG_RA_DMAC_GPT1_CHANNEL == 8) || (CONFIG_RA_DMAC_GPT1_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_GPT1_CHANNEL > 17)
#error "CONFIG_RA_DMAC_GPT1_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_GPT2_CHANNEL
#if (CONFIG_RA_DMAC_GPT2_CHANNEL == 8) || (CONFIG_RA_DMAC_GPT2_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_GPT2_CHANNEL > 17)
#error "CONFIG_RA_DMAC_GPT2_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif

#ifdef CONFIG_RA_DMAC_GPT3_CHANNEL
#if (CONFIG_RA_DMAC_GPT3_CHANNEL == 8) || (CONFIG_RA_DMAC_GPT3_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_GPT3_CHANNEL > 17)
#error "CONFIG_RA_DMAC_GPT3_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_GPT4_CHANNEL
#if (CONFIG_RA_DMAC_GPT4_CHANNEL == 8) || (CONFIG_RA_DMAC_GPT4_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_GPT4_CHANNEL > 17)
#error "CONFIG_RA_DMAC_GPT4_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_GPT5_CHANNEL
#if (CONFIG_RA_DMAC_GPT5_CHANNEL == 8) || (CONFIG_RA_DMAC_GPT5_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_GPT5_CHANNEL > 17)
#error "CONFIG_RA_DMAC_GPT5_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_GPT10_CHANNEL
#if (CONFIG_RA_DMAC_GPT10_CHANNEL == 8) || (CONFIG_RA_DMAC_GPT10_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_GPT10_CHANNEL > 17)
#error "CONFIG_RA_DMAC_GPT10_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_GPT11_CHANNEL
#if (CONFIG_RA_DMAC_GPT11_CHANNEL == 8) || (CONFIG_RA_DMAC_GPT11_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_GPT11_CHANNEL > 17)
#error "CONFIG_RA_DMAC_GPT11_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif

#ifdef CONFIG_RA_DMAC_GPT12_CHANNEL
#if (CONFIG_RA_DMAC_GPT12_CHANNEL == 8) || (CONFIG_RA_DMAC_GPT12_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_GPT12_CHANNEL > 17)
#error "CONFIG_RA_DMAC_GPT12_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_GPT13_CHANNEL
#if (CONFIG_RA_DMAC_GPT13_CHANNEL == 8) || (CONFIG_RA_DMAC_GPT13_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_GPT13_CHANNEL > 17)
#error "CONFIG_RA_DMAC_GPT13_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17)"
#endif
#endif

#ifdef CONFIG_RA_DMAC_SDHI_CHANNEL
#if (CONFIG_RA_DMAC_SDHI_CHANNEL == 8) || (CONFIG_RA_DMAC_SDHI_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SDHI_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SDHI_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17). Note: SDHI typically only supports 0-7."
#endif
#endif

#ifdef CONFIG_RA_DMAC_SDRAM_CHANNEL
#if (CONFIG_RA_DMAC_SDRAM_CHANNEL == 8) || (CONFIG_RA_DMAC_SDRAM_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_SDRAM_CHANNEL > 17)
#error "CONFIG_RA_DMAC_SDRAM_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17). Note: SDRAM typically only supports 0-7."
#endif
#endif

#ifdef CONFIG_RA_DMAC_QSPI0_CHANNEL
#if (CONFIG_RA_DMAC_QSPI0_CHANNEL == 8) || (CONFIG_RA_DMAC_QSPI0_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_QSPI0_CHANNEL > 17)
#error "CONFIG_RA_DMAC_QSPI0_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17). Note: QSPI typically only supports 0-7."
#endif
#endif

#ifdef CONFIG_RA_DMAC_QSPI1_CHANNEL
#if (CONFIG_RA_DMAC_QSPI1_CHANNEL == 8) || (CONFIG_RA_DMAC_QSPI1_CHANNEL == 9) || \
  (CONFIG_RA_DMAC_QSPI1_CHANNEL > 17)
#error "CONFIG_RA_DMAC_QSPI1_CHANNEL: invalid DMAC channel (valid: -1, 0-7, 10-17). Note: QSPI typically only supports 0-7."
#endif
#endif
#endif
#endif
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DMAC Events */
#define RA_DMAC_EVENT_COMPLETE   (0)  /* Transfer complete */
#define RA_DMAC_EVENT_ERROR      (1)  /* Transfer error */

/* DMAC Limits */
#define RA_DMAC_MAX_NORMAL_LENGTH     (0x10000)  /* Maximum transfers in normal mode */
#define RA_DMAC_MAX_REPEAT_LENGTH     (0x400)    /* Maximum transfers in repeat/block mode */
#define RA_DMAC_MAX_BLOCK_COUNT       (0x100)    /* Maximum block count */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* DMAC Priority Level
 * Higher priority channels are serviced first when multiple channels
 * have pending requests. Use RA_DMAC_PRIORITY_HIGH for flight-critical
 * paths like motor control (DShot) and sensor data (IMU).
 */

typedef enum
{
  RA_DMAC_PRIORITY_FIXED = 0,   /* Fixed priority (channel 0 highest) */
  RA_DMAC_PRIORITY_ROUND_ROBIN  /* Round-robin priority */
} ra_dmac_priority_mode_t;

/* Per-channel priority (0=lowest, 3=highest for conceptual use) */

typedef enum
{
  RA_DMAC_CHANNEL_PRIORITY_LOW = 0,    /* Low priority */
  RA_DMAC_CHANNEL_PRIORITY_MEDIUM,     /* Medium priority */
  RA_DMAC_CHANNEL_PRIORITY_HIGH,       /* High priority - sensors */
  RA_DMAC_CHANNEL_PRIORITY_CRITICAL    /* Critical - motor control */
} ra_dmac_channel_priority_t;

/* DMAC Transfer Mode */

typedef enum
{
  RA_DMAC_MODE_NORMAL = 0,  /* Normal mode */
  RA_DMAC_MODE_REPEAT,      /* Repeat mode */
  RA_DMAC_MODE_BLOCK        /* Block mode */
} ra_dmac_mode_t;

/* DMAC Repeat/Block Area Select (DTS field) */

typedef enum
{
  RA_DMAC_REPEAT_AREA_DEST = 0,   /* Destination is repeat/block area */
  RA_DMAC_REPEAT_AREA_SRC,        /* Source is repeat/block area */
  RA_DMAC_REPEAT_AREA_NONE        /* No repeat/block area specified */
} ra_dmac_repeat_area_t;

/* DMAC Transfer Size */
typedef enum
{
  RA_DMAC_SIZE_8BIT = 0,    /* 8-bit transfer */
  RA_DMAC_SIZE_16BIT,       /* 16-bit transfer */
  RA_DMAC_SIZE_32BIT        /* 32-bit transfer */
} ra_dmac_size_t;

/* DMAC Address Mode */
typedef enum
{
  RA_DMAC_ADDR_FIXED = 0,   /* Fixed address */
  RA_DMAC_ADDR_OFFSET,      /* Offset address */
  RA_DMAC_ADDR_INCR,        /* Increment address */
  RA_DMAC_ADDR_DECR         /* Decrement address */
} ra_dmac_addr_mode_t;

/* DMAC Trigger Mode */
typedef enum
{
  RA_DMAC_TRIGGER_SW = 0,   /* Software trigger */
  RA_DMAC_TRIGGER_HW        /* Hardware trigger */
} ra_dmac_trigger_t;

/* Forward declaration */
typedef void *ra_dmac_handle_t;

/* DMAC callback function type */
typedef void (*ra_dmac_callback_t)(void *handle, int event, void *user_data);

/* DMAC configuration structure */

typedef struct ra_dmac_config_s
{
  ra_dmac_mode_t       mode;             /* Transfer mode (MD field) */
  ra_dmac_repeat_area_t repeat_area;     /* Repeat/block area select (DTS field) */
  ra_dmac_size_t       size;             /* Transfer data size */
  ra_dmac_addr_mode_t  src_addr_mode;    /* Source address mode */
  ra_dmac_addr_mode_t  dest_addr_mode;   /* Destination address mode */
  ra_dmac_trigger_t    trigger;          /* Trigger mode */

  uint32_t             src_addr;         /* Source address */
  uint32_t             dest_addr;        /* Destination address */
  uint32_t             transfer_count;   /* Number of transfers */
  uint32_t             block_count;      /* Number of blocks (block mode) */

  int                  elc_end;          /* DMA End of transfer event link */
  int                  elc_err;          /* DMA Error event link */
  int                  elc_src;          /* Event link of activation source */

  ra_dmac_channel_priority_t priority;   /* Channel priority level */

  ra_dmac_callback_t   callback;         /* Transfer callback */
  void                *user_data;        /* User data for callback */
} ra_dmac_config_t;

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/* DMAC module functions */
int ra_dmac_initialize(void);
int ra_dmac_set_priority_mode(int unit, ra_dmac_priority_mode_t mode);
/* DMAC transfer functions */
int ra_dmac_open(ra_dmac_handle_t *handle, const ra_dmac_config_t *config);
int ra_dmac_open_channel(ra_dmac_handle_t *handle, const ra_dmac_config_t *config, int channel);
int ra_dmac_close(ra_dmac_handle_t handle);
int ra_dmac_enable(ra_dmac_handle_t handle);
int ra_dmac_disable(ra_dmac_handle_t handle);
int ra_dmac_software_start(ra_dmac_handle_t handle);
int ra_dmac_reset(ra_dmac_handle_t handle, uint32_t src_addr,
                  uint32_t dest_addr, uint32_t transfer_count);

/* DMAC status functions */

uint32_t ra_dmac_get_remaining_count(ra_dmac_handle_t handle);

/****************************************************************************
 * Debug Interface
 ****************************************************************************/

#ifdef CONFIG_DEBUG_DMA_INFO

/* DMAC debug register snapshot structure */

struct ra_dmaregs_s
{
  /* Channel identification */

  uint8_t  chan;          /* DMAC channel number */

  /* Global DMA registers */

  uint32_t dmast;         /* DMA Module Activation Register */
  uint32_t dmctl;         /* DMA Control Register */
  uint32_t dmechr;        /* DMA Error Channel Register */
  uint32_t delsr;         /* DMA Event Link Setting Register */

  /* Per-channel registers */

  uint32_t dmsar;         /* DMA Source Address Register */
  uint32_t dmdar;         /* DMA Destination Address Register */
  uint32_t dmcra;         /* DMA Transfer Count Register */
  uint32_t dmcrb;         /* DMA Block Transfer Count Register */
  uint32_t dmtmd;         /* DMA Transfer Mode Register */
  uint32_t dmamd;         /* DMA Address Mode Register */
  uint8_t  dmint;         /* DMA Interrupt Setting Register */
  uint8_t  dmcnt;         /* DMA Transfer Enable Register */
  uint8_t  dmreq;         /* DMA Software Start Register */
  uint8_t  dmsts;         /* DMA Status Register */
};

/****************************************************************************
 * Name: ra_dmasample
 *
 * Description:
 *   Sample DMA register contents for debugging
 *
 * Input Parameters:
 *   handle - DMA channel handle created by ra_dmac_open()
 *   regs   - Pointer to structure to receive register snapshot
 *
 ****************************************************************************/

void ra_dmasample(ra_dmac_handle_t handle, struct ra_dmaregs_s *regs);

/****************************************************************************
 * Name: ra_dmadump
 *
 * Description:
 *   Dump previously sampled DMA register contents
 *
 * Input Parameters:
 *   regs - Pointer to sampled register structure
 *   msg  - Message to print with dump
 *
 ****************************************************************************/

void ra_dmadump(const struct ra_dmaregs_s *regs, const char *msg);

#endif /* CONFIG_DEBUG_DMA_INFO */

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RA_RA8_DMAC_H */
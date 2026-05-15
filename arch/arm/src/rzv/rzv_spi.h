/****************************************************************************
 * arch/arm/src/rzv/rzv_spi.h
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

#ifndef __ARCH_ARM_SRC_RZV_RZV_SPI_H
#define __ARCH_ARM_SRC_RZV_RZV_SPI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/spi/spi.h>

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_spibus_initialize
 *
 * Description:
 *   Initialize the selected SPI bus
 *
 * Input Parameters:
 *   port - Port number (0, 1, 2)
 *
 * Returned Value:
 *   Valid SPI device structure reference on success; NULL on failure
 *
 ****************************************************************************/

struct spi_dev_s *rzv_spibus_initialize(int port);

/****************************************************************************
 * Name: rzv_spibus_uninitialize
 *
 * Description:
 *   Uninitialize an SPI bus
 *
 * Input Parameters:
 *   dev - SPI device structure
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_spibus_uninitialize(struct spi_dev_s *dev);

/****************************************************************************
 * Name: rzv_spi_set_loopback
 *
 * Description:
 *   Enable or disable internal SPI loopback (SPCR2.SPLP).
 *   When enabled, MOSI is wired internally to MISO — no physical wire needed.
 *   Phase-07 [Low-20]: replaces the commented-out stub in rzv2h_spi_loopback.c.
 *
 * Input Parameters:
 *   dev    - SPI device from rzv_spibus_initialize()
 *   enable - true = enable loopback, false = normal operation
 *
 ****************************************************************************/

void rzv_spi_set_loopback(struct spi_dev_s *dev, bool enable);

#endif /* __ARCH_ARM_SRC_RZV_RZV_SPI_H */

/****************************************************************************
 * arch/arm/src/ra8/ra_ospi_b.h
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

#ifndef __ARCH_ARM_SRC_RA_RA8_OSPI_B_H
#define __ARCH_ARM_SRC_RA_RA8_OSPI_B_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/spi/qspi.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Protocol mode values for ra_ospi_set_protocol() */

#define RA_OSPI_PROTO_SPI         0    /* 1S-1S-1S (Standard SPI) */
#define RA_OSPI_PROTO_QSPI_IO     1    /* 1S-4S-4S (Quad I/O) */
#define RA_OSPI_PROTO_QSPI        4    /* 4S-4S-4S (Quad mode) */
#define RA_OSPI_PROTO_OPI         8    /* 8D-8D-8D (Octal DDR) */

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: ra_ospi_initialize
 *
 * Description:
 *   Initialize the OSPI_B driver and return the QSPI device interface.
 *
 *   This function performs the complete initialization sequence:
 *   1. Enable module clock (MSTP)
 *   2. Configure wrapper timing (WRAPCFG)
 *   3. Configure protocol mode (LIOCFGCS) - starts in SPI mode
 *   4. Configure command mapping (CMCFG0/1/2)
 *   5. Configure bridge mapping (BMCTL0, BMCFGCH)
 *   6. Issue flash reset sequence
 *
 * Input Parameters:
 *   port - The OSPI port number (0 or 1)
 *
 * Returned Value:
 *   A valid QSPI device structure reference on success; NULL on failure
 *
 ****************************************************************************/

struct qspi_dev_s *ra_ospi_initialize(int port);

/****************************************************************************
 * Name: ra_ospi_set_protocol
 *
 * Description:
 *   Change the OSPI protocol mode. This is used to switch between SPI
 *   and OPI modes after initial communication with the flash device.
 *
 * Input Parameters:
 *   dev   - QSPI device structure from ra_ospi_initialize()
 *   proto - Protocol mode:
 *           RA_OSPI_PROTO_SPI (0)     - 1S-1S-1S Standard SPI
 *           RA_OSPI_PROTO_QSPI_IO (1) - 1S-4S-4S Quad I/O
 *           RA_OSPI_PROTO_QSPI (4)    - 4S-4S-4S Quad mode
 *           RA_OSPI_PROTO_OPI (8)     - 8D-8D-8D Octal DDR
 *
 * Returned Value:
 *   OK on success; negative errno on failure
 *
 ****************************************************************************/

int ra_ospi_set_protocol(struct qspi_dev_s *dev, int proto);

/****************************************************************************
 * Name: ra_ospi_set_latency
 *
 * Description:
 *   Set the read and write latency (dummy) cycles. This must match the
 *   flash device configuration.
 *
 * Input Parameters:
 *   dev           - QSPI device structure from ra_ospi_initialize()
 *   read_latency  - Read latency cycles (typically 0-20)
 *   write_latency - Write latency cycles (typically 0-4)
 *
 * Returned Value:
 *   OK on success; negative errno on failure
 *
 ****************************************************************************/

int ra_ospi_set_latency(struct qspi_dev_s *dev,
                        uint8_t read_latency, uint8_t write_latency);

/****************************************************************************
 * Name: ra_ospi_xip_enable
 *
 * Description:
 *   Enable XIP (Execute-in-Place) mode for continuous read optimization.
 *
 * Input Parameters:
 *   dev - QSPI device structure from ra_ospi_initialize()
 *
 * Returned Value:
 *   OK on success; negative errno on failure
 *
 ****************************************************************************/

int ra_ospi_xip_enable(struct qspi_dev_s *dev);

/****************************************************************************
 * Name: ra_ospi_xip_disable
 *
 * Description:
 *   Disable XIP (Execute-in-Place) mode.
 *
 * Input Parameters:
 *   dev - QSPI device structure from ra_ospi_initialize()
 *
 * Returned Value:
 *   OK on success; negative errno on failure
 *
 ****************************************************************************/

int ra_ospi_xip_disable(struct qspi_dev_s *dev);

#ifdef CONFIG_RA_DMAC

/****************************************************************************
 * Name: ra_ospi_set_dma
 *
 * Description:
 *   Enable or disable DMA for OSPI transfers.
 *
 * Input Parameters:
 *   dev        - QSPI device structure from ra_ospi_initialize()
 *   enable_dma - true to enable DMA, false to use CPU transfers
 *
 * Returned Value:
 *   OK on success; negative errno on failure
 *
 ****************************************************************************/

int ra_ospi_set_dma(struct qspi_dev_s *dev, bool enable_dma);

#endif /* CONFIG_RA_DMAC */

#endif /* __ARCH_ARM_SRC_RA_RA8_OSPI_B_H */

/****************************************************************************
 * arch/arm/src/ra8/hardware/ra_memorymap.h
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

#ifndef __ARCH_ARM_SRC_RA_HARDWARE_RA8_MEMORYMAP_H
#define __ARCH_ARM_SRC_RA_HARDWARE_RA8_MEMORYMAP_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include "chip.h"
#include "hardware/ra_hardware.h"

/* Include all hardware-dependent headers for the RA8 families here so
 * driver sources can simply include "chip.h" and get the correct
 * register offsets and bit definitions for the selected group.
 */
#if defined(CONFIG_RA8E1_GROUP)
#  include "hardware/ra8e1/ra_acmphs.h"
#  include "hardware/ra8e1/ra_adc12.h"
#  include "hardware/ra8e1/ra_agt.h"
#  include "hardware/ra8e1/ra_bus.h"
#  include "hardware/ra8e1/ra_cac.h"
#  include "hardware/ra8e1/ra_canfd.h"
#  include "hardware/ra8e1/ra_ceu.h"
#  include "hardware/ra8e1/ra_cpscu.h"
#  include "hardware/ra8e1/ra_cpu_ctrl.h"
#  include "hardware/ra8e1/ra_cpu_dbg.h"
#  include "hardware/ra8e1/ra_crc.h"
#  include "hardware/ra8e1/ra_dac.h"
#  include "hardware/ra8e1/ra_dma.h"
#  include "hardware/ra8e1/ra_dmac.h"
#  include "hardware/ra8e1/ra_doc_b.h"
#  include "hardware/ra8e1/ra_dtc.h"
#  include "hardware/ra8e1/ra_eccmb.h"
#  include "hardware/ra8e1/ra_edmac.h"
#  include "hardware/ra8e1/ra_elc.h"
#  include "hardware/ra8e1/ra_etherc.h"
#  include "hardware/ra8e1/ra_faci.h"
#  include "hardware/ra8e1/ra_fcache.h"
#  include "hardware/ra8e1/ra_flad.h"
#  include "hardware/ra8e1/ra_gpt16.h"
#  include "hardware/ra8e1/ra_gpt32.h"
#  include "hardware/ra8e1/ra_icu.h"
#  include "hardware/ra8e1/ra_iic.h"
#  include "hardware/ra8e1/ra_iic0wu.h"
#  include "hardware/ra8e1/ra_iwdt.h"
#  include "hardware/ra8e1/ra_mstp.h"
#  include "hardware/ra8e1/ra_ocd_cpu.h"
#  include "hardware/ra8e1/ra_ospi_b.h"
#  include "hardware/ra8e1/ra_pfs.h"
#  include "hardware/ra8e1/ra_poeg.h"
#  include "hardware/ra8e1/ra_port.h"
#  include "hardware/ra8e1/ra_pscu.h"
#  include "hardware/ra8e1/ra_rmpu.h"
#  include "hardware/ra8e1/ra_rtc.h"
#  include "hardware/ra8e1/ra_sci_b.h"
#  include "hardware/ra8e1/ra_spi_b.h"
#  include "hardware/ra8e1/ra_sram.h"
#  include "hardware/ra8e1/ra_ssie.h"
#  include "hardware/ra8e1/ra_sysc.h"
#  include "hardware/ra8e1/ra_tsd.h"
#  include "hardware/ra8e1/ra_tsn.h"
#  include "hardware/ra8e1/ra_ulpt.h"
#  include "hardware/ra8e1/ra_usbfs.h"
#  include "hardware/ra8e1/ra_wdt.h"
#elif defined(CONFIG_RA8P1_GROUP)
#  include "hardware/ra8p1/ra_acmphs.h"
#  include "hardware/ra8p1/ra_adc_b.h"
#  include "hardware/ra8p1/ra_agt.h"
#  include "hardware/ra8p1/ra_bus.h"
#  include "hardware/ra8p1/ra_cac.h"
#  include "hardware/ra8p1/ra_cache.h"
#  include "hardware/ra8p1/ra_canfd.h"
#  include "hardware/ra8p1/ra_ceu.h"
#  include "hardware/ra8p1/ra_coma.h"
#  include "hardware/ra8p1/ra_cpscu.h"
#  include "hardware/ra8p1/ra_cpu_ctrl.h"
#  include "hardware/ra8p1/ra_cpu_dbg.h"
#  include "hardware/ra8p1/ra_cpu_ocd.h"
#  include "hardware/ra8p1/ra_crc.h"
#  include "hardware/ra8p1/ra_dma.h"
#  include "hardware/ra8p1/ra_dmac.h"
#  include "hardware/ra8p1/ra_doc_b.h"
#  include "hardware/ra8p1/ra_dotf.h"
#  include "hardware/ra8p1/ra_drw.h"
#  include "hardware/ra8p1/ra_dtc.h"
#  include "hardware/ra8p1/ra_eccmb.h"
#  include "hardware/ra8p1/ra_elc.h"
#  include "hardware/ra8p1/ra_eswm.h"
#  include "hardware/ra8p1/ra_etha.h"
#  include "hardware/ra8p1/ra_fcache.h"
#  include "hardware/ra8p1/ra_glcdc.h"
#  include "hardware/ra8p1/ra_gpt32.h"
#  include "hardware/ra8p1/ra_gpt_gtclk.h"
#  include "hardware/ra8p1/ra_gpt_ops.h"
#  include "hardware/ra8p1/ra_gptp.h"
#  include "hardware/ra8p1/ra_gwca.h"
#  include "hardware/ra8p1/ra_i3c.h"
#  include "hardware/ra8p1/ra_icu.h"
#  include "hardware/ra8p1/ra_iic.h"
#  include "hardware/ra8p1/ra_iic0wu.h"
#  include "hardware/ra8p1/ra_ipc.h"
#  include "hardware/ra8p1/ra_iwdt.h"
#  include "hardware/ra8p1/ra_mfwd.h"
#  include "hardware/ra8p1/ra_mipi_csi.h"
#  include "hardware/ra8p1/ra_mipi_dsi.h"
#  include "hardware/ra8p1/ra_mipi_phy.h"
#  include "hardware/ra8p1/ra_mram.h"
#  include "hardware/ra8p1/ra_mstp.h"
#  include "hardware/ra8p1/ra_ospi_b.h"
#  include "hardware/ra8p1/ra_pdg.h"
#  include "hardware/ra8p1/ra_pdmif.h"
#  include "hardware/ra8p1/ra_pfs.h"
#  include "hardware/ra8p1/ra_poeg.h"
#  include "hardware/ra8p1/ra_port.h"
#  include "hardware/ra8p1/ra_pscu.h"
#  include "hardware/ra8p1/ra_rmac.h"
#  include "hardware/ra8p1/ra_rmpu.h"
#  include "hardware/ra8p1/ra_rtc.h"
#  include "hardware/ra8p1/ra_sci_b.h"
#  include "hardware/ra8p1/ra_sdhi.h"
#  include "hardware/ra8p1/ra_sdram.h"
#  include "hardware/ra8p1/ra_spi_b.h"
#  include "hardware/ra8p1/ra_sram.h"
#  include "hardware/ra8p1/ra_ssie.h"
#  include "hardware/ra8p1/ra_sysc.h"
#  include "hardware/ra8p1/ra_tcm.h"
#  include "hardware/ra8p1/ra_tsd.h"
#  include "hardware/ra8p1/ra_tsn.h"
#  include "hardware/ra8p1/ra_ulpt.h"
#  include "hardware/ra8p1/ra_usbfs.h"
#  include "hardware/ra8p1/ra_usbhs.h"
#  include "hardware/ra8p1/ra_vin.h"
#  include "hardware/ra8p1/ra_wdt.h"
#else
#  error "Unsupported RA8 Device"
#endif


#endif /* __ARCH_ARM_SRC_RA_HARDWARE_RA8_MEMORYMAP_H */

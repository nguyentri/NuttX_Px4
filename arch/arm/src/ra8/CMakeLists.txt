# ##############################################################################
# arch/arm/src/ra8/CMakeLists.txt
#
# Licensed to the Apache Software Foundation (ASF) under one or more contributor
# license agreements.  See the NOTICE file distributed with this work for
# additional information regarding copyright ownership.  The ASF licenses this
# file to you under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License.  You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations under
# the License.
#
# ##############################################################################

# Add RA8-specific include paths

target_include_directories(arch PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/hardware
  ${CMAKE_CURRENT_SOURCE_DIR}/hardware/ra8e1
  ${CMAKE_CURRENT_SOURCE_DIR}/hardware/ra8p1
)

# Required RA8 core files
set(SRCS
    ra_mstp.c
    ra_start.c
    ra_timerisr.c
    ra_clock.c
    ra_irq.c
    ra_lowputc.c
    ra_icu.c
    ra_gpio.c
    ra_memmng.c
    ra_serial.c)

# ADC driver
if(CONFIG_RA_ADC)
  list(APPEND SRCS ra_adc.c)
endif()

if(CONFIG_RA_ADC)
  list(APPEND SRCS ra_adc_b.c)
endif()

# SDHI driver
if(CONFIG_RA_SDHI)
  list(APPEND SRCS ra_sdhi.c)
endif()

# I2C driver
if(CONFIG_RA_I2C)
  list(APPEND SRCS ra_i2c.c)
endif()

# I2C slave driver
if(CONFIG_RA_I2C_SLAVE)
  list(APPEND SRCS ra_i2c_slave.c)
endif()

# I3C driver
if(CONFIG_RA_I3C)
  list(APPEND SRCS ra_i3c.c)
endif()

# DMAC driver
if(CONFIG_RA_DMAC)
  list(APPEND SRCS ra_dmac.c)
endif()

# MIPI-CSI driver
if(CONFIG_RA_MIPI_CSI)
  list(APPEND SRCS ra_mipi_csi.c)
endif()

# SPI driver
if(CONFIG_RA_SPI)
  list(APPEND SRCS ra_spi.c ra_dtc.c)
endif()

# PWM driver
if(CONFIG_RA_GPT)
  list(APPEND SRCS ra_gpt.c)
endif()

# ELC driver
if(CONFIG_RA_ELC)
  list(APPEND SRCS ra_elc.c)
endif()

# MRAM driver, RA8 internal flash as MRAM
if(CONFIG_RA_FLASH)
  list(APPEND SRCS ra_mram.c)
endif()

# CANFD driver
if(CONFIG_RA_CANFD)
  list(APPEND SRCS ra_canfd.c)
endif()

# Ethernet driver
if(CONFIG_RA_ETHERNET)
  list(APPEND SRCS ra_ether.c)
endif()

# SDRAM driver
if(CONFIG_RA_SDRAM)
  list(APPEND SRCS ra_sdram.c)
endif()

target_sources(arch PRIVATE ${SRCS})

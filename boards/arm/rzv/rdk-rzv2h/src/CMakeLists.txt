# ##############################################################################
# boards/arm/rzv/rdk-rzv2h/src/CMakeLists.txt
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

# Core board initialization files
set(SRCS rzv2h_boot.c rzv2h_bringup.c)

# Application examples support
if(CONFIG_RZV2H_EXAMPLE_SUPPORT)
  list(APPEND SRCS rzv2h_app_examples.c)
endif()

# Board-specific initialization
if(CONFIG_BOARDCTL)
  list(APPEND SRCS rzv2h_appinit.c)
endif()

if(CONFIG_ARCH_BUTTONS)
  list(APPEND SRCS rzv2h_buttons.c)
endif()

if(CONFIG_ARCH_LEDS)
  list(APPEND SRCS rzv2h_auto_leds.c)
else()
  list(APPEND SRCS rzv2h_user_leds.c)
endif()

# Peripheral driver initialization
if(CONFIG_RZV_UART_SCI)
  list(APPEND SRCS rzv2h_serial.c)
endif()

if(CONFIG_RZV_RIIC)
  list(APPEND SRCS rzv2h_i2c.c)
endif()

if(CONFIG_RZV_SPI)
  list(APPEND SRCS rzv2h_spi.c)
endif()

if(CONFIG_PWM)
  list(APPEND SRCS rzv2h_pwm.c)
endif()

if(CONFIG_RZV_ADC)
  list(APPEND SRCS rzv2h_adc.c)
endif()

# Example applications
if(CONFIG_RZV2H_SPI_LOOPBACK_EXAMPLE)
  list(APPEND SRCS rzv2h_spi_loopback.c)
endif()

if(CONFIG_RZV2H_I2C_GY912_EXAMPLE)
  list(APPEND SRCS rzv2h_i2c_gy912.c)
endif()

if(CONFIG_RZV2H_SPI_GY921_EXAMPLE)
  list(APPEND SRCS rzv2h_spi_gy921.c)
endif()

if(CONFIG_RZV2H_PWM_ONESHOT_EXAMPLE)
  list(APPEND SRCS rzv2h_pwm_oneshot.c)
endif()

target_sources(board PRIVATE ${SRCS})

# Set linker script based on core configuration
if(CONFIG_RZV2H_BUILD_CM33)
  set_property(GLOBAL PROPERTY LD_SCRIPT
                               "${NUTTX_BOARD_DIR}/scripts/rdk-rzv2h_cm33.ld")
elseif(CONFIG_RZV2H_BUILD_CR8_0)
  set_property(GLOBAL PROPERTY LD_SCRIPT
                               "${NUTTX_BOARD_DIR}/scripts/rdk-rzv2h_cr8_0.ld")
elseif(CONFIG_RZV2H_BUILD_CR8_1)
  set_property(GLOBAL PROPERTY LD_SCRIPT
                               "${NUTTX_BOARD_DIR}/scripts/rdk-rzv2h_cr8_1.ld")
endif()

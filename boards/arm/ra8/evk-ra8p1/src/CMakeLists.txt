# ##############################################################################
# boards/arm/ra8/evk-ra8p1/src/CMakeLists.txt
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

set(SRCS ra8p1_boot.c ra8p1_bringup.c ra8p1_gpio.c ra8p1_app_examples.c)

if(CONFIG_ARCH_LEDS)
  list(APPEND SRCS ra8p1_auto_leds.c)
else()
  list(APPEND SRCS ra8p1_user_leds.c)
endif()

if(CONFIG_ARCH_BUTTONS)
  list(APPEND SRCS ra8p1_buttons.c)
endif()

if(CONFIG_RA_I2C)
  list(APPEND SRCS ra8p1_i2c.c)
endif()

if(CONFIG_RA8P1_SPI_LOOPBACK_EXAMPLE)
  list(APPEND SRCS ra8p1_spi_loopback.c)
endif()

if(CONFIG_PWM)
  list(APPEND SRCS ra8p1_gpt_pwm.c)
endif()

if(CONFIG_RA_ADC_B)
  list(APPEND SRCS ra8p1_adc_b.c)
endif()

if(CONFIG_RA_CANFD)
  list(APPEND SRCS ra8p1_canfd.c)
endif()

target_sources(board PRIVATE ${SRCS})

set_property(GLOBAL PROPERTY LD_SCRIPT
                             "${NUTTX_BOARD_DIR}/scripts/evk-ra8p1.ld")

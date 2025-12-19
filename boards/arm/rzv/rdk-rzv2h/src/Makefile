############################################################################
# boards/arm/rzv/rdk-rzv2h/src/Makefile
#
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.  The
# ASF licenses this file to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance with the
# License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations
# under the License.
#
############################################################################

include $(TOPDIR)/Make.defs

############################################################################
# Core board initialization files
############################################################################

CSRCS = rzv2h_boot.c rzv2h_bringup.c

# Application examples support
ifeq ($(CONFIG_RZV2H_EXAMPLE_SUPPORT),y)
CSRCS += rzv2h_app_examples.c
endif

############################################################################
# Board-specific initialization
############################################################################

# Application initialization
ifeq ($(CONFIG_BOARDCTL),y)
CSRCS += rzv2h_appinit.c
endif

# Button/Switch support
ifeq ($(CONFIG_ARCH_BUTTONS),y)
CSRCS += rzv2h_buttons.c
endif

# LED support
ifeq ($(CONFIG_ARCH_LEDS),y)
CSRCS += rzv2h_auto_leds.c
else
CSRCS += rzv2h_user_leds.c
endif

############################################################################
# Peripheral driver initialization
############################################################################

# Serial/UART support
ifeq ($(CONFIG_RZV_UART_SCI),y)
CSRCS += rzv2h_serial.c
endif

# I2C support
ifeq ($(CONFIG_RZV_RIIC),y)
CSRCS += rzv2h_i2c.c
endif

# SPI support
ifeq ($(CONFIG_RZV_SPI),y)
CSRCS += rzv2h_spi.c
endif

# GPT PWM support
ifeq ($(CONFIG_PWM),y)
CSRCS += rzv2h_pwm.c
endif

# ADC support
ifeq ($(CONFIG_RZV_ADC),y)
CSRCS += rzv2h_adc.c
endif

# DTC support
ifeq ($(CONFIG_RZV_DTC),y)
CSRCS += rzv2h_dtc.c
endif

############################################################################
# Example applications
############################################################################

# SPI loopback example
ifeq ($(CONFIG_RZV2H_SPI_LOOPBACK_EXAMPLE),y)
CSRCS += rzv2h_spi_loopback.c
endif

# I2C GY-912 sensor example
ifeq ($(CONFIG_RZV2H_I2C_GY912_EXAMPLE),y)
CSRCS += rzv2h_i2c_gy912.c
endif

# SPI GY-921 sensor example
ifeq ($(CONFIG_RZV2H_SPI_GY921_EXAMPLE),y)
CSRCS += rzv2h_spi_gy921.c
endif

# PWM oneshot example
ifeq ($(CONFIG_RZV2H_PWM_ONESHOT_EXAMPLE),y)
CSRCS += rzv2h_pwm_oneshot.c
endif

include $(TOPDIR)/boards/Board.mk

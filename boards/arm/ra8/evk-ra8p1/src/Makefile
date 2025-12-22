############################################################################
# boards/arm/ra8/evk-ra8p1/src/Makefile
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

# Core board initialization files
CSRCS = ra8p1_boot.c ra8p1_bringup.c ra8p1_gpio.c ra8p1_app_examples.c

############################################################################
# Board-specific initialization
############################################################################

# Button/Switch support
ifeq ($(CONFIG_ARCH_BUTTONS),y)
CSRCS += ra8p1_buttons.c
endif

# LED support
ifeq ($(CONFIG_ARCH_LEDS),y)
CSRCS += ra8p1_auto_leds.c
else
CSRCS += ra8p1_user_leds.c
endif

# CAC support
ifeq ($(CONFIG_RA_CAC),y)
CSRCS += ra8p1_cac.c
endif

# I2C support
ifeq ($(CONFIG_RA_I2C),y)
CSRCS += ra8p1_i2c.c
endif

# I3C support
ifeq ($(CONFIG_RA_I3C),y)
CSRCS += ra8p1_i3c.c
endif

# SDHI support
ifeq ($(CONFIG_RA_SDHI),y)
CSRCS += ra8p1_sdhi.c
endif

# MIPI-CSI support
ifeq ($(CONFIG_RA_MIPI_CSI),y)
CSRCS += ra8p1_mipi_csi.c
endif

# ADC B support
ifeq ($(CONFIG_RA_ADC_B),y)
CSRCS += ra8p1_adc_b.c
endif

# GPT PWM support
ifeq ($(CONFIG_PWM),y)
CSRCS += ra8p1_pwm.c
endif

# POEG support
ifeq ($(CONFIG_RA_POEG),y)
CSRCS += ra8p1_opeg.c
endif

# ELC support
ifeq ($(CONFIG_RA_ELC),y)
CSRCS += ra8p1_elc.c
endif

# MRAM support
ifeq ($(CONFIG_RA_MRAM),y)
CSRCS += ra8p1_mram.c
endif

# CANFD support
ifeq ($(CONFIG_RA_CANFD),y)
CSRCS += ra8p1_canfd.c
endif

# OSPI support
ifeq ($(CONFIG_RA_OSPI),y)
CSRCS += ra8p1_ospi_b.c
endif

# Ethernet support
ifeq ($(CONFIG_RA_ETHERNET),y)
CSRCS += ra8p1_ether.c
endif

# SDRAM support
ifeq ($(CONFIG_RA_SDRAM),y)
CSRCS += ra8p1_sdram.c
endif

# RTC driver support
ifeq ($(CONFIG_RTC_DRIVER),y)
CSRCS += ra8p1_rtc.c
endif

# USB Device support
ifeq ($(CONFIG_RA_USBDEV),y)
  CSRCS += ra8p1_usb.c
endif

# ELC support
ifeq ($(CONFIG_RA8P1_ADC_HW_TRIGGER_EXAMPLE),y)
CSRCS += ra8p1_adc_b_hwtrigger.c
endif

# OSPI Example
ifeq ($(CONFIG_RA8P1_OSPI_EXAMPLE),y)
CSRCS += ra8p1_ospi_test.c
endif

# SPI loopback example support
ifeq ($(CONFIG_RA8P1_SPI_LOOPBACK_EXAMPLE),y)
CSRCS += ra8p1_spi_loopback.c
endif

# SCI_SPI support
ifeq ($(CONFIG_RA_SCI_SPI),y)
CSRCS += ra8p1_sci_spi.c
endif

# WDT support
ifeq ($(CONFIG_RA_WDT),y)
CSRCS += ra8p1_wdt.c
endif

# IWDT support
ifeq ($(CONFIG_RA_IWDT),y)
CSRCS += ra8p1_iwdt.c
endif

# IPC support
ifeq ($(CONFIG_RA_IPC),y)
CSRCS += ra8p1_ipc.c
endif

# LPM (Low Power Mode) support
ifeq ($(CONFIG_RA_LPM),y)
CSRCS += ra8p1_lpm.c
endif

# WDT test application
ifeq ($(CONFIG_RA8P1_WDT_TEST),y)
CSRCS += ra8p1_wdg_test.c
endif

# IPC test application
ifeq ($(CONFIG_RA8P1_IPC_TEST),y)
CSRCS += ra8p1_ipc_test.c
endif

include $(TOPDIR)/boards/Board.mk

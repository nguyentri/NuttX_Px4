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
CSRCS = ra8p1_boot.c ra8p1_bringup.c
CSRCS += ra8p1_app_examples.c

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

# I2C support
ifneq ($(CONFIG_RA_I2C),y)
CSRCS += ra8p1_i2c.c
endif

include $(TOPDIR)/boards/Board.mk

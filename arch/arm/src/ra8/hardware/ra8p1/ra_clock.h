/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_clock.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CLOCK_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CLOCK_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Clock Configuration Defaults */

#ifndef CONFIG_RA_HOCO_FREQUENCY
#  define CONFIG_RA_HOCO_FREQUENCY    48000000  /* 48MHz HOCO (default for RA8P1 EVK) */
#endif

#ifndef CONFIG_RA_MOCO_FREQUENCY
#  define CONFIG_RA_MOCO_FREQUENCY    8000000   /* 8MHz MOCO */
#endif

#ifndef CONFIG_RA_LOCO_FREQUENCY
#  define CONFIG_RA_LOCO_FREQUENCY    32768     /* 32.768kHz LOCO */
#endif

#ifndef CONFIG_RA_XTAL_FREQUENCY
#  define CONFIG_RA_XTAL_FREQUENCY    24000000  /* 24MHz External Crystal (RA8P1 EVK) */
#endif

#ifndef CONFIG_RA_MAIN_OSC_FREQUENCY
#  define CONFIG_RA_MAIN_OSC_FREQUENCY CONFIG_RA_XTAL_FREQUENCY
#endif

/* System Clock Selection */

#ifndef RA_CKSEL
#  ifdef CONFIG_RA_CLOCK_PLL1P
#    define RA_CKSEL                   5         /* PLL1P */
#  elif defined(CONFIG_RA_CLOCK_PLL)
#    define RA_CKSEL                   5         /* PLL */
#  elif defined(CONFIG_RA_CLOCK_HOCO)
#    define RA_CKSEL                   0         /* HOCO */
#  elif defined(CONFIG_RA_CLOCK_MOCO)
#    define RA_CKSEL                   1         /* MOCO */
#  elif defined(CONFIG_RA_CLOCK_MAIN_OSC)
#    define RA_CKSEL                   3         /* Main OSC */
#  else
#    define RA_CKSEL                   0         /* Default to HOCO */
#  endif
#endif

/* Clock Source Definitions */
#define RA_CLOCKS_SOURCE_CLOCK_HOCO      0     /* HOCO */
#define RA_CLOCKS_SOURCE_CLOCK_MOCO      1     /* MOCO */
#define RA_CLOCKS_SOURCE_CLOCK_LOCO      2     /* LOCO */
#define RA_CLOCKS_SOURCE_CLOCK_MAIN_OSC  3     /* Main OSC */
#define RA_CLOCKS_SOURCE_CLOCK_SUBCLOCK  4     /* Sub-clock */
#define RA_CLOCKS_SOURCE_CLOCK_PLL       5     /* PLL */
#define RA_CLOCKS_SOURCE_CLOCK_PLL1P     5     /* PLL1P (alias for PLL) */
#define RA_CLOCKS_SOURCE_CLOCK_PLL1Q     7     /* PLL1Q */
#define RA_CLOCKS_SOURCE_CLOCK_PLL1R     8     /* PLL1R */
#define RA_CLOCKS_SOURCE_CLOCK_PLL2      6     /* PLL2 */
#define RA_CLOCKS_SOURCE_CLOCK_PLL2P     6     /* PLL2P */
#define RA_CLOCKS_SOURCE_CLOCK_PLL2Q     9     /* PLL2Q */
#define RA_CLOCKS_SOURCE_CLOCK_PLL2R    10     /* PLL2R */
#define RA_CLOCKS_CLOCK_DISABLED        15     /* Clock disabled */

/* System clock divider options. */
#define RA_CLOCKS_SYS_CLOCK_DIV_1                   (0)  // System clock divided by 1.
#define RA_CLOCKS_SYS_CLOCK_DIV_2                   (1)  // System clock divided by 2.
#define RA_CLOCKS_SYS_CLOCK_DIV_4                   (2)  // System clock divided by 4.
#define RA_CLOCKS_SYS_CLOCK_DIV_8                   (3)  // System clock divided by 8.
#define RA_CLOCKS_SYS_CLOCK_DIV_16                  (4)  // System clock divided by 16.
#define RA_CLOCKS_SYS_CLOCK_DIV_32                  (5)  // System clock divided by 32.
#define RA_CLOCKS_SYS_CLOCK_DIV_64                  (6)  // System clock divided by 64.
#define RA_CLOCKS_SYS_CLOCK_DIV_128                 (7)  // System clock divided by 128 (available for CLKOUT only).
#define RA_CLOCKS_SYS_CLOCK_DIV_3                   (8)  // System clock divided by 3.
#define RA_CLOCKS_SYS_CLOCK_DIV_6                   (9)  // System clock divided by 6.
#define RA_CLOCKS_SYS_CLOCK_DIV_12                  (10) // System clock divided by 12.
#define RA_CLOCKS_SYS_CLOCK_DIV_24                  (11) // System clock divided by 24.

/* USB clock divider options. */
#define RA_CLOCKS_USB_CLOCK_DIV_1                   (0)  // Divide USB source clock by 1
#define RA_CLOCKS_USB_CLOCK_DIV_2                   (1)  // Divide USB source clock by 2
#define RA_CLOCKS_USB_CLOCK_DIV_3                   (2)  // Divide USB source clock by 3
#define RA_CLOCKS_USB_CLOCK_DIV_4                   (3)  // Divide USB source clock by 4
#define RA_CLOCKS_USB_CLOCK_DIV_5                   (4)  // Divide USB source clock by 5
#define RA_CLOCKS_USB_CLOCK_DIV_6                   (5)  // Divide USB source clock by 6
#define RA_CLOCKS_USB_CLOCK_DIV_8                   (7)  // Divide USB source clock by 8
#define RA_CLOCKS_USB_CLOCK_DIV_10                  (9)  // Divide USB source clock by 10
#define RA_CLOCKS_USB_CLOCK_DIV_16                  (15) // Divide USB source clock by 16
#define RA_CLOCKS_USB_CLOCK_DIV_32                  (9)  // Divide USB source clock by 32

/* USB60 clock divider options. */
#define RA_CLOCKS_USB60_CLOCK_DIV_1                 (0)  // Divide USB60 source clock by 1
#define RA_CLOCKS_USB60_CLOCK_DIV_2                 (1)  // Divide USB60 source clock by 2
#define RA_CLOCKS_USB60_CLOCK_DIV_3                 (5)  // Divide USB60 source clock by 3
#define RA_CLOCKS_USB60_CLOCK_DIV_4                 (2)  // Divide USB60 source clock by 4
#define RA_CLOCKS_USB60_CLOCK_DIV_5                 (6)  // Divide USB60 source clock by 5
#define RA_CLOCKS_USB60_CLOCK_DIV_6                 (3)  // Divide USB66 source clock by 6
#define RA_CLOCKS_USB60_CLOCK_DIV_8                 (4)  // Divide USB60 source clock by 8
#define RA_CLOCKS_USB60_CLOCK_DIV_10                (7)  // Divide USB60 source clock by 10
#define RA_CLOCKS_USB60_CLOCK_DIV_16                (8)  // Divide USB60 source clock by 16
#define RA_CLOCKS_USB60_CLOCK_DIV_32                (9)  // Divide USB60 source clock by 32

/* GLCD clock divider options. */
#define RA_CLOCKS_LCD_CLOCK_DIV_1                   (0)  // Divide LCD source clock by 1
#define RA_CLOCKS_LCD_CLOCK_DIV_2                   (1)  // Divide LCD source clock by 2
#define RA_CLOCKS_LCD_CLOCK_DIV_3                   (5)  // Divide LCD source clock by 3
#define RA_CLOCKS_LCD_CLOCK_DIV_4                   (2)  // Divide LCD source clock by 4
#define RA_CLOCKS_LCD_CLOCK_DIV_5                   (6)  // Divide LCD source clock by 5
#define RA_CLOCKS_LCD_CLOCK_DIV_6                   (3)  // Divide LCD source clock by 6
#define RA_CLOCKS_LCD_CLOCK_DIV_8                   (4)  // Divide LCD source clock by 8
#define RA_CLOCKS_LCD_CLOCK_DIV_10                  (7)  // Divide LCD source clock by 10
#define RA_CLOCKS_LCD_CLOCK_DIV_16                  (8)  // Divide LCD source clock by 16
#define RA_CLOCKS_LCD_CLOCK_DIV_32                  (9)  // Divide LCD source clock by 32

/* OCTA clock divider options. */
#define RA_CLOCKS_OCTA_CLOCK_DIV_1                  (0)  // Divide OCTA source clock by 1
#define RA_CLOCKS_OCTA_CLOCK_DIV_2                  (1)  // Divide OCTA source clock by 2
#define RA_CLOCKS_OCTA_CLOCK_DIV_3                  (5)  // Divide OCTA source clock by 3
#define RA_CLOCKS_OCTA_CLOCK_DIV_4                  (2)  // Divide OCTA source clock by 4
#define RA_CLOCKS_OCTA_CLOCK_DIV_5                  (6)  // Divide OCTA source clock by 5
#define RA_CLOCKS_OCTA_CLOCK_DIV_6                  (3)  // Divide OCTA source clock by 6
#define RA_CLOCKS_OCTA_CLOCK_DIV_8                  (4)  // Divide OCTA source clock by 8
#define RA_CLOCKS_OCTA_CLOCK_DIV_10                 (7)  // Divide OCTA source clock by 10
#define RA_CLOCKS_OCTA_CLOCK_DIV_16                 (8)  // Divide OCTA source clock by 16
#define RA_CLOCKS_OCTA_CLOCK_DIV_32                 (9)  // Divide OCTA source clock by 32

/* CANFD clock divider options. */
#define RA_CLOCKS_CANFD_CLOCK_DIV_1                 (0)  // Divide CANFD source clock by 1
#define RA_CLOCKS_CANFD_CLOCK_DIV_2                 (1)  // Divide CANFD source clock by 2
#define RA_CLOCKS_CANFD_CLOCK_DIV_3                 (5)  // Divide CANFD source clock by 3
#define RA_CLOCKS_CANFD_CLOCK_DIV_4                 (2)  // Divide CANFD source clock by 4
#define RA_CLOCKS_CANFD_CLOCK_DIV_5                 (6)  // Divide CANFD source clock by 5
#define RA_CLOCKS_CANFD_CLOCK_DIV_6                 (3)  // Divide CANFD source clock by 6
#define RA_CLOCKS_CANFD_CLOCK_DIV_8                 (4)  // Divide CANFD source clock by 8
#define RA_CLOCKS_CANFD_CLOCK_DIV_10                (7)  // Divide CANFD source clock by 10
#define RA_CLOCKS_CANFD_CLOCK_DIV_16                (8)  // Divide CANFD source clock by 16
#define RA_CLOCKS_CANFD_CLOCK_DIV_32                (9)  // Divide CANFD source clock by 32

/* SCI clock divider options. */
#define RA_CLOCKS_SCI_CLOCK_DIV_1                   (0)  // Divide SCI source clock by 1
#define RA_CLOCKS_SCI_CLOCK_DIV_2                   (1)  // Divide SCI source clock by 2
#define RA_CLOCKS_SCI_CLOCK_DIV_3                   (5)  // Divide SCI source clock by 3
#define RA_CLOCKS_SCI_CLOCK_DIV_4                   (2)  // Divide SCI source clock by 4
#define RA_CLOCKS_SCI_CLOCK_DIV_5                   (6)  // Divide SCI source clock by 5
#define RA_CLOCKS_SCI_CLOCK_DIV_6                   (3)  // Divide SCI source clock by 6
#define RA_CLOCKS_SCI_CLOCK_DIV_8                   (4)  // Divide SCI source clock by 8
#define RA_CLOCKS_SCI_CLOCK_DIV_10                  (7)  // Divide SCI source clock by 10
#define RA_CLOCKS_SCI_CLOCK_DIV_16                  (8)  // Divide SCI source clock by 16
#define RA_CLOCKS_SCI_CLOCK_DIV_32                  (9)  // Divide SCI source clock by 32

/* SPI clock divider options. */
#define RA_CLOCKS_SPI_CLOCK_DIV_1                   (0)  // Divide SPI source clock by 1
#define RA_CLOCKS_SPI_CLOCK_DIV_2                   (1)  // Divide SPI source clock by 2
#define RA_CLOCKS_SPI_CLOCK_DIV_3                   (5)  // Divide SPI source clock by 3
#define RA_CLOCKS_SPI_CLOCK_DIV_4                   (2)  // Divide SPI source clock by 4
#define RA_CLOCKS_SPI_CLOCK_DIV_5                   (6)  // Divide SPI source clock by 5
#define RA_CLOCKS_SPI_CLOCK_DIV_6                   (3)  // Divide SPI source clock by 6
#define RA_CLOCKS_SPI_CLOCK_DIV_8                   (4)  // Divide SPI source clock by 8
#define RA_CLOCKS_SPI_CLOCK_DIV_10                  (7)  // Divide SPI source clock by 10
#define RA_CLOCKS_SPI_CLOCK_DIV_16                  (8)  // Divide SPI source clock by 16
#define RA_CLOCKS_SPI_CLOCK_DIV_32                  (9)  // Divide SPI source clock by 32

/* SCISPI clock divider options. */
#define RA_CLOCKS_SCISPI_CLOCK_DIV_1                (0)  // Divide SCISPI source clock by 1
#define RA_CLOCKS_SCISPI_CLOCK_DIV_2                (1)  // Divide SCISPI source clock by 2
#define RA_CLOCKS_SCISPI_CLOCK_DIV_4                (2)  // Divide SCISPI source clock by 4
#define RA_CLOCKS_SCISPI_CLOCK_DIV_6                (3)  // Divide SCISPI source clock by 6
#define RA_CLOCKS_SCISPI_CLOCK_DIV_8                (4)  // Divide SCISPI source clock by 8

/* GPT clock divider options. */
#define RA_CLOCKS_GPT_CLOCK_DIV_1                   (0)  // Divide GPT source clock by 1
#define RA_CLOCKS_GPT_CLOCK_DIV_2                   (1)  // Divide GPT source clock by 2
#define RA_CLOCKS_GPT_CLOCK_DIV_3                   (5)  // Divide GPT source clock by 3
#define RA_CLOCKS_GPT_CLOCK_DIV_4                   (2)  // Divide GPT source clock by 4
#define RA_CLOCKS_GPT_CLOCK_DIV_5                   (6)  // Divide GPT source clock by 5
#define RA_CLOCKS_GPT_CLOCK_DIV_6                   (3)  // Divide GPT source clock by 6
#define RA_CLOCKS_GPT_CLOCK_DIV_8                   (4)  // Divide GPT source clock by 8
#define RA_CLOCKS_GPT_CLOCK_DIV_10                  (7)  // Divide GPT source clock by 10
#define RA_CLOCKS_GPT_CLOCK_DIV_16                  (8)  // Divide GPT source clock by 16
#define RA_CLOCKS_GPT_CLOCK_DIV_32                  (9)  // Divide GPT source clock by 32

/* IIC clock divider options. */
#define RA_CLOCKS_IIC_CLOCK_DIV_1                   (0)  // Divide IIC source clock by 1
#define RA_CLOCKS_IIC_CLOCK_DIV_2                   (1)  // Divide IIC source clock by 2
#define RA_CLOCKS_IIC_CLOCK_DIV_4                   (2)  // Divide IIC source clock by 4
#define RA_CLOCKS_IIC_CLOCK_DIV_6                   (3)  // Divide IIC source clock by 6
#define RA_CLOCKS_IIC_CLOCK_DIV_8                   (4)  // Divide IIC source clock by 8

/* CEC clock divider options. */
#define RA_CLOCKS_CEC_CLOCK_DIV_1                   (0)  // Divide CEC source clock by 1
#define RA_CLOCKS_CEC_CLOCK_DIV_2                   (1)  // Divide CEC source clock by 2

/* I3C clock divider options. */
#define RA_CLOCKS_I3C_CLOCK_DIV_1                   (0)  // Divide I3C source clock by 1
#define RA_CLOCKS_I3C_CLOCK_DIV_2                   (1)  // Divide I3C source clock by 2
#define RA_CLOCKS_I3C_CLOCK_DIV_3                   (5)  // Divide I3C source clock by 3
#define RA_CLOCKS_I3C_CLOCK_DIV_4                   (2)  // Divide I3C source clock by 4
#define RA_CLOCKS_I3C_CLOCK_DIV_5                   (6)  // Divide I3C source clock by 5
#define RA_CLOCKS_I3C_CLOCK_DIV_6                   (3)  // Divide I3C source clock by 6
#define RA_CLOCKS_I3C_CLOCK_DIV_8                   (4)  // Divide I3C source clock by 8
#define RA_CLOCKS_I3C_CLOCK_DIV_10                  (7)  // Divide I3C source clock by 10
#define RA_CLOCKS_I3C_CLOCK_DIV_16                  (8)  // Divide I3C source clock by 16
#define RA_CLOCKS_I3C_CLOCK_DIV_32                  (9)  // Divide I3C source clock by 32

/* ADC clock divider options. */
#define RA_CLOCKS_ADC_CLOCK_DIV_1                   (0)  // Divide ADC source clock by 1
#define RA_CLOCKS_ADC_CLOCK_DIV_2                   (1)  // Divide ADC source clock by 2
#define RA_CLOCKS_ADC_CLOCK_DIV_3                   (5)  // Divide ADC source clock by 3
#define RA_CLOCKS_ADC_CLOCK_DIV_4                   (2)  // Divide ADC source clock by 4
#define RA_CLOCKS_ADC_CLOCK_DIV_5                   (6)  // Divide ADC source clock by 5
#define RA_CLOCKS_ADC_CLOCK_DIV_6                   (3)  // Divide ADC source clock by 6
#define RA_CLOCKS_ADC_CLOCK_DIV_8                   (4)  // Divide ADC source clock by 8
#define RA_CLOCKS_ADC_CLOCK_DIV_10                  (7)  // Divide ADC source clock by 10
#define RA_CLOCKS_ADC_CLOCK_DIV_16                  (8)  // Divide ADC source clock by 16
#define RA_CLOCKS_ADC_CLOCK_DIV_32                  (9)  // Divide ADC source clock by 32

/* ESW clock divider options. */
#define RA_CLOCKS_ESW_CLOCK_DIV_1                   (0)  // Divide ESW source clock by 1
#define RA_CLOCKS_ESW_CLOCK_DIV_2                   (1)  // Divide ESW source clock by 2
#define RA_CLOCKS_ESW_CLOCK_DIV_3                   (5)  // Divide ESW source clock by 3
#define RA_CLOCKS_ESW_CLOCK_DIV_4                   (2)  // Divide ESW source clock by 4
#define RA_CLOCKS_ESW_CLOCK_DIV_5                   (6)  // Divide ESW source clock by 5
#define RA_CLOCKS_ESW_CLOCK_DIV_6                   (3)  // Divide ESW source clock by 6
#define RA_CLOCKS_ESW_CLOCK_DIV_8                   (4)  // Divide ESW source clock by 8
#define RA_CLOCKS_ESW_CLOCK_DIV_10                  (7)  // Divide ESW source clock by 10
#define RA_CLOCKS_ESW_CLOCK_DIV_16                  (8)  // Divide ESW source clock by 16
#define RA_CLOCKS_ESW_CLOCK_DIV_32                  (9)  // Divide ESW source clock by 32

/* ESWPHY clock divider options. */
#define RA_CLOCKS_ESWPHY_CLOCK_DIV_1                (0)  // Divide ESWPHY source clock by 1
#define RA_CLOCKS_ESWPHY_CLOCK_DIV_2                (1)  // Divide ESWPHY source clock by 2
#define RA_CLOCKS_ESWPHY_CLOCK_DIV_3                (5)  // Divide ESWPHY source clock by 3
#define RA_CLOCKS_ESWPHY_CLOCK_DIV_4                (2)  // Divide ESWPHY source clock by 4
#define RA_CLOCKS_ESWPHY_CLOCK_DIV_5                (6)  // Divide ESWPHY source clock by 5
#define RA_CLOCKS_ESWPHY_CLOCK_DIV_6                (3)  // Divide ESWPHY source clock by 6
#define RA_CLOCKS_ESWPHY_CLOCK_DIV_8                (4)  // Divide ESWPHY source clock by 8
#define RA_CLOCKS_ESWPHY_CLOCK_DIV_10               (7)  // Divide ESWPHY source clock by 10
#define RA_CLOCKS_ESWPHY_CLOCK_DIV_16               (8)  // Divide ESWPHY source clock by 16
#define RA_CLOCKS_ESWPHY_CLOCK_DIV_32               (9)  // Divide ESWPHY source clock by 32

/* ETHPHY clock divider options. */
#define RA_CLOCKS_ETHPHY_CLOCK_DIV_1                (0)  // Divide ETHPHY source clock by 1
#define RA_CLOCKS_ETHPHY_CLOCK_DIV_2                (1)  // Divide ETHPHY source clock by 2
#define RA_CLOCKS_ETHPHY_CLOCK_DIV_3                (5)  // Divide ETHPHY source clock by 3
#define RA_CLOCKS_ETHPHY_CLOCK_DIV_4                (2)  // Divide ETHPHY source clock by 4
#define RA_CLOCKS_ETHPHY_CLOCK_DIV_5                (6)  // Divide ETHPHY source clock by 5
#define RA_CLOCKS_ETHPHY_CLOCK_DIV_6                (3)  // Divide ETHPHY source clock by 6
#define RA_CLOCKS_ETHPHY_CLOCK_DIV_8                (4)  // Divide ETHPHY source clock by 8
#define RA_CLOCKS_ETHPHY_CLOCK_DIV_10               (7)  // Divide ETHPHY source clock by 10
#define RA_CLOCKS_ETHPHY_CLOCK_DIV_16               (8)  // Divide ETHPHY source clock by 16
#define RA_CLOCKS_ETHPHY_CLOCK_DIV_32               (9)  // Divide ETHPHY source clock by 32

/* BCLKA clock divider options. */
#define RA_CLOCKS_BCLKA_CLOCK_DIV_1                 (0)  // Divide BCLKA source clock by 1
#define RA_CLOCKS_BCLKA_CLOCK_DIV_2                 (1)  // Divide BCLKA source clock by 2
#define RA_CLOCKS_BCLKA_CLOCK_DIV_3                 (5)  // Divide BCLKA source clock by 3
#define RA_CLOCKS_BCLKA_CLOCK_DIV_4                 (2)  // Divide BCLKA source clock by 4
#define RA_CLOCKS_BCLKA_CLOCK_DIV_5                 (6)  // Divide BCLKA source clock by 5
#define RA_CLOCKS_BCLKA_CLOCK_DIV_6                 (3)  // Divide BCLKA source clock by 6
#define RA_CLOCKS_BCLKA_CLOCK_DIV_8                 (4)  // Divide BCLKA source clock by 8
#define RA_CLOCKS_BCLKA_CLOCK_DIV_10                (7)  // Divide BCLKA source clock by 10
#define RA_CLOCKS_BCLKA_CLOCK_DIV_16                (8)  // Divide BCLKA source clock by 16
#define RA_CLOCKS_BCLKA_CLOCK_DIV_32                (9)  // Divide BCLKA source clock by 32

/* SAU clock divider options. */
#define RA_CLOCKS_SAU_CLOCK_DIV_1                   (0)  // Divide SAU source clock by 1
#define RA_CLOCKS_SAU_CLOCK_DIV_2                   (1)  // Divide SAU source clock by 2
#define RA_CLOCKS_SAU_CLOCK_DIV_4                   (2)  // Divide SAU source clock by 4
#define RA_CLOCKS_SAU_CLOCK_DIV_8                   (3)  // Divide SAU source clock by 8
#define RA_CLOCKS_SAU_CLOCK_DIV_16                  (4)  // Divide SAU source clock by 16
#define RA_CLOCKS_SAU_CLOCK_DIV_32                  (5)  // Divide SAU source clock by 32
#define RA_CLOCKS_SAU_CLOCK_DIV_64                  (6)  // Divide SAU source clock by 64
#define RA_CLOCKS_SAU_CLOCK_DIV_128                 (7)  // Divide SAU source clock by 128
#define RA_CLOCKS_SAU_CLOCK_DIV_256                 (8)  // Divide SAU source clock by 256
#define RA_CLOCKS_SAU_CLOCK_DIV_512                 (9)  // Divide SAU source clock by 512
#define RA_CLOCKS_SAU_CLOCK_DIV_1024                (10) // Divide SAU source clock by 1024
#define RA_CLOCKS_SAU_CLOCK_DIV_2048                (11) // Divide SAU source clock by 2048
#define RA_CLOCKS_SAU_CLOCK_DIV_4096                (12) // Divide SAU source clock by 4096
#define RA_CLOCKS_SAU_CLOCK_DIV_8192                (13) // Divide SAU source clock by 8192
#define RA_CLOCKS_SAU_CLOCK_DIV_16384               (14) // Divide SAU source clock by 16384
#define RA_CLOCKS_SAU_CLOCK_DIV_32768               (15) // Divide SAU source clock by 32768

/* Extra peripheral 0 clock divider options. */
#define RA_CLOCKS_EXTRA_PERIPHERAL0_CLOCK_DIV_1     (0)  // Divide extra peripheral 0 source clock by 1
#define RA_CLOCKS_EXTRA_PERIPHERAL0_CLOCK_DIV_2     (1)  // Divide extra peripheral 0 source clock by 2
#define RA_CLOCKS_EXTRA_PERIPHERAL0_CLOCK_DIV_3     (5)  // Divide extra peripheral 0 source clock by 3
#define RA_CLOCKS_EXTRA_PERIPHERAL0_CLOCK_DIV_4     (2)  // Divide extra peripheral 0 source clock by 4
#define RA_CLOCKS_EXTRA_PERIPHERAL0_CLOCK_DIV_5     (6)  // Divide extra peripheral 0 source clock by 5
#define RA_CLOCKS_EXTRA_PERIPHERAL0_CLOCK_DIV_6     (3)  // Divide extra peripheral 0 source clock by 6
#define RA_CLOCKS_EXTRA_PERIPHERAL0_CLOCK_DIV_8     (4)  // Divide extra peripheral 0 source clock by 8
#define RA_CLOCKS_EXTRA_PERIPHERAL0_CLOCK_DIV_10    (7)  // Divide extra peripheral 0 source clock by 10
#define RA_CLOCKS_EXTRA_PERIPHERAL0_CLOCK_DIV_16    (8)  // Divide extra peripheral 0 source clock by 16
#define RA_CLOCKS_EXTRA_PERIPHERAL0_CLOCK_DIV_32    (9)  // Divide extra peripheral 0 source clock by 32

/* Extra peripheral 1 clock divider options. */
#define RA_CLOCKS_EXTRA_PERIPHERAL1_CLOCK_DIV_1     (0)  // Divide extra peripheral 1 source clock by 1
#define RA_CLOCKS_EXTRA_PERIPHERAL1_CLOCK_DIV_2     (1)  // Divide extra peripheral 1 source clock by 2
#define RA_CLOCKS_EXTRA_PERIPHERAL1_CLOCK_DIV_3     (5)  // Divide extra peripheral 1 source clock by 3
#define RA_CLOCKS_EXTRA_PERIPHERAL1_CLOCK_DIV_4     (2)  // Divide extra peripheral 1 source clock by 4
#define RA_CLOCKS_EXTRA_PERIPHERAL1_CLOCK_DIV_5     (6)  // Divide extra peripheral 1 source clock by 5
#define RA_CLOCKS_EXTRA_PERIPHERAL1_CLOCK_DIV_6     (3)  // Divide extra peripheral 1 source clock by 6
#define RA_CLOCKS_EXTRA_PERIPHERAL1_CLOCK_DIV_8     (4)  // Divide extra peripheral 1 source clock by 8
#define RA_CLOCKS_EXTRA_PERIPHERAL1_CLOCK_DIV_10    (7)  // Divide extra peripheral 1 source clock by 10
#define RA_CLOCKS_EXTRA_PERIPHERAL1_CLOCK_DIV_16    (8)  // Divide extra peripheral 1 source clock by 16
#define RA_CLOCKS_EXTRA_PERIPHERAL1_CLOCK_DIV_32    (9)  // Divide extra peripheral 1 source clock by 32

/* PLL divider options. */
#define RA_CLOCKS_PLL_DIV_1                         (0)  // Divide by 1
#define RA_CLOCKS_PLL_DIV_2                         (1)  // Divide by 2
#define RA_CLOCKS_PLL_DIV_3                         (2)  // Divide by 3
#define RA_CLOCKS_PLL_DIV_4                         (3)  // Divide by 4
#define RA_CLOCKS_PLL_DIV_5                         (4)  // Divide by 5
#define RA_CLOCKS_PLL_DIV_6                         (5)  // Divide by 6
#define RA_CLOCKS_PLL_DIV_8                         (7)  // Divide by 8
#define RA_CLOCKS_PLL_DIV_9                         (8)  // Divide by 9
#define RA_CLOCKS_PLL_DIV_1_5                       (9)  // Divide by 1.5
#define RA_CLOCKS_PLL_DIV_16                        (15) // Divide by 16

/* PLL Multiplier Macro (for fractional multipliers) */
/**
 * X = Integer portion of the multiplier
 * Y = Fractional portion of the multiplier (0, 33, 50, or 66)
 * This matches Renesas FSP RA_CLOCKS_PLL_MUL(X, Y) format
 */
#define RA_CLOCKS_PLL_MUL(X, Y)    ((((X) - 1U) << 2UL) | ((Y) == 50U ? 3U : ((Y) / 33UL)))

/* Helper macro to convert PLL divider encoding to actual divisor */
#define RA_PLL_DIV_TO_DIVISOR(enc) \
    ((enc) == 0 ? 1 : \
     (enc) == 1 ? 2 : \
     (enc) == 2 ? 3 : \
     (enc) == 3 ? 4 : \
     (enc) == 4 ? 5 : \
     (enc) == 5 ? 6 : \
     (enc) == 7 ? 8 : \
     (enc) == 8 ? 9 : \
     (enc) == 9 ? 1.5 : \
     (enc) == 15 ? 16 : 1)

/* PLL configuration macros */
#ifndef CONFIG_RA_PLL_SOURCE
#  define CONFIG_RA_PLL_SOURCE        RA_CLOCKS_SOURCE_CLOCK_MAIN_OSC  /* Main OSC (XTAL) as PLL source for RA8P1 */
#endif

#ifndef CONFIG_RA_PLL_DIV
#  define CONFIG_RA_PLL_DIV           RA_CLOCKS_PLL_DIV_3      /* PLL input divider /3 (encoded value 2) */
#endif

#ifndef CONFIG_RA_PLL_MUL
#  define CONFIG_RA_PLL_MUL           250       /* PLL multiplier x250 for 2000MHz VCO */
#endif

/* PLL frequency calculation using divider encoding */
#if CONFIG_RA_PLL_SOURCE == RA_CLOCKS_SOURCE_CLOCK_HOCO
#  define RA_PLL_SOURCE_FREQ          CONFIG_RA_HOCO_FREQUENCY
#elif CONFIG_RA_PLL_SOURCE == RA_CLOCKS_SOURCE_CLOCK_MAIN_OSC
#  define RA_PLL_SOURCE_FREQ          CONFIG_RA_MAIN_OSC_FREQUENCY
#else
#  define RA_PLL_SOURCE_FREQ          CONFIG_RA_HOCO_FREQUENCY  /* Default */
#endif

/* Convert CONFIG_RA_PLL_DIV encoding to actual divisor */
#define RA_PLL_INPUT_DIVISOR            RA_PLL_DIV_TO_DIVISOR(CONFIG_RA_PLL_DIV)

/* PLL output frequencies (based on BSP config for RA8P1) */
#define RA_CFG_PLL1P_FREQUENCY_HZ         (1000000000)  /* PLL1P 1000MHz */
#define RA_CFG_PLL1Q_FREQUENCY_HZ         (333333333)   /* PLL1Q 333MHz */
#define RA_CFG_PLL1R_FREQUENCY_HZ         (400000000)   /* PLL1R 400MHz */

/* Clock settling delay */
#ifndef RA_CFG_CLOCK_SETTLING_DELAY_US
#  define RA_CFG_CLOCK_SETTLING_DELAY_US  150U
#endif

/* PLL Output Dividers (RA8P1 specific) */
#ifndef CONFIG_RA_PLL1P_DIV
#  define CONFIG_RA_PLL1P_DIV         RA_CLOCKS_PLL_DIV_2      /* PLL1P divider /2 (encoded value 1) */
#endif

#ifndef CONFIG_RA_PLL1Q_DIV
#  define CONFIG_RA_PLL1Q_DIV         RA_CLOCKS_PLL_DIV_6      /* PLL1Q divider /6 (encoded value 5) */
#endif

#ifndef CONFIG_RA_PLL1R_DIV
#  define CONFIG_RA_PLL1R_DIV         RA_CLOCKS_PLL_DIV_5      /* PLL1R divider /5 (encoded value 4) */
#endif

/* PLL2 Configuration (RA8P1 specific) */
#ifndef CONFIG_RA_PLL2_SOURCE
#  define CONFIG_RA_PLL2_SOURCE       RA_CLOCKS_SOURCE_CLOCK_MAIN_OSC  /* PLL2 from Main OSC (XTAL) */
#endif

#ifndef CONFIG_RA_PLL2_DIV
#  define CONFIG_RA_PLL2_DIV          RA_CLOCKS_PLL_DIV_3      /* PLL2 input divider /3 (encoded value 2) */
#endif

#ifndef CONFIG_RA_PLL2_MUL
#  define CONFIG_RA_PLL2_MUL          300       /* PLL2 multiplier x300 for 2400MHz VCO */
#endif

#ifndef CONFIG_RA_PLL2P_DIV
#  define CONFIG_RA_PLL2P_DIV         RA_CLOCKS_PLL_DIV_4      /* PLL2P divider /4 (encoded value 3) */
#endif

#ifndef CONFIG_RA_PLL2Q_DIV
#  define CONFIG_RA_PLL2Q_DIV         RA_CLOCKS_PLL_DIV_3      /* PLL2Q divider /3 (encoded value 2) */
#endif

#ifndef CONFIG_RA_PLL2R_DIV
#  define CONFIG_RA_PLL2R_DIV         RA_CLOCKS_PLL_DIV_5      /* PLL2R divider /5 (encoded value 4) */
#endif

/* PLL Frequency Calculations using divider encoding */
/* Note: PLL divider encoding: 0=/1, 1=/2, 2=/3, 3=/4, 4=/5, 5=/6, 7=/8, 8=/9, 9=/1.5, 15=/16 */
#if CONFIG_RA_PLL_SOURCE == RA_CLOCKS_SOURCE_CLOCK_HOCO
#  define RA_PLL_SOURCE_FREQ          CONFIG_RA_HOCO_FREQUENCY
#elif CONFIG_RA_PLL_SOURCE == RA_CLOCKS_SOURCE_CLOCK_MAIN_OSC
#  define RA_PLL_SOURCE_FREQ          CONFIG_RA_MAIN_OSC_FREQUENCY
#else
#  define RA_PLL_SOURCE_FREQ          CONFIG_RA_HOCO_FREQUENCY  /* Default */
#endif

/* PLL VCO and output frequencies (calculated based on encoding) */
/* For RA8P1: 24MHz / 3 * 250 = 2000MHz VCO */
#if CONFIG_RA_PLL_DIV == RA_CLOCKS_PLL_DIV_3
#  define RA_PLL_FREQUENCY            ((RA_PLL_SOURCE_FREQ / 3) * CONFIG_RA_PLL_MUL)
#elif CONFIG_RA_PLL_DIV == RA_CLOCKS_PLL_DIV_2
#  define RA_PLL_FREQUENCY            ((RA_PLL_SOURCE_FREQ / 2) * CONFIG_RA_PLL_MUL)
#elif CONFIG_RA_PLL_DIV == RA_CLOCKS_PLL_DIV_1
#  define RA_PLL_FREQUENCY            (RA_PLL_SOURCE_FREQ * CONFIG_RA_PLL_MUL)
#elif CONFIG_RA_PLL_DIV == RA_CLOCKS_PLL_DIV_4
#  define RA_PLL_FREQUENCY            ((RA_PLL_SOURCE_FREQ / 4) * CONFIG_RA_PLL_MUL)
#elif CONFIG_RA_PLL_DIV == RA_CLOCKS_PLL_DIV_5
#  define RA_PLL_FREQUENCY            ((RA_PLL_SOURCE_FREQ / 5) * CONFIG_RA_PLL_MUL)
#elif CONFIG_RA_PLL_DIV == RA_CLOCKS_PLL_DIV_6
#  define RA_PLL_FREQUENCY            ((RA_PLL_SOURCE_FREQ / 6) * CONFIG_RA_PLL_MUL)
#else
#  define RA_PLL_FREQUENCY            ((RA_PLL_SOURCE_FREQ / 2) * CONFIG_RA_PLL_MUL) /* Default /2 */
#endif

/* PLL1P = 2000MHz / 2 = 1000MHz */
#if CONFIG_RA_PLL1P_DIV == RA_CLOCKS_PLL_DIV_2
#  define RA_PLL1P_FREQUENCY          (RA_PLL_FREQUENCY / 2)
#elif CONFIG_RA_PLL1P_DIV == RA_CLOCKS_PLL_DIV_1
#  define RA_PLL1P_FREQUENCY          RA_PLL_FREQUENCY
#elif CONFIG_RA_PLL1P_DIV == RA_CLOCKS_PLL_DIV_3
#  define RA_PLL1P_FREQUENCY          (RA_PLL_FREQUENCY / 3)
#elif CONFIG_RA_PLL1P_DIV == RA_CLOCKS_PLL_DIV_4
#  define RA_PLL1P_FREQUENCY          (RA_PLL_FREQUENCY / 4)
#else
#  define RA_PLL1P_FREQUENCY          (RA_PLL_FREQUENCY / 2) /* Default /2 */
#endif

/* PLL1Q = 2000MHz / 6 = 333MHz */
#if CONFIG_RA_PLL1Q_DIV == RA_CLOCKS_PLL_DIV_6
#  define RA_PLL1Q_FREQUENCY          (RA_PLL_FREQUENCY / 6)
#elif CONFIG_RA_PLL1Q_DIV == RA_CLOCKS_PLL_DIV_2
#  define RA_PLL1Q_FREQUENCY          (RA_PLL_FREQUENCY / 2)
#elif CONFIG_RA_PLL1Q_DIV == RA_CLOCKS_PLL_DIV_3
#  define RA_PLL1Q_FREQUENCY          (RA_PLL_FREQUENCY / 3)
#elif CONFIG_RA_PLL1Q_DIV == RA_CLOCKS_PLL_DIV_4
#  define RA_PLL1Q_FREQUENCY          (RA_PLL_FREQUENCY / 4)
#elif CONFIG_RA_PLL1Q_DIV == RA_CLOCKS_PLL_DIV_5
#  define RA_PLL1Q_FREQUENCY          (RA_PLL_FREQUENCY / 5)
#else
#  define RA_PLL1Q_FREQUENCY          (RA_PLL_FREQUENCY / 6) /* Default /6 */
#endif

/* PLL1R = 2000MHz / 5 = 400MHz */
#if CONFIG_RA_PLL1R_DIV == RA_CLOCKS_PLL_DIV_5
#  define RA_PLL1R_FREQUENCY          (RA_PLL_FREQUENCY / 5)
#elif CONFIG_RA_PLL1R_DIV == RA_CLOCKS_PLL_DIV_2
#  define RA_PLL1R_FREQUENCY          (RA_PLL_FREQUENCY / 2)
#elif CONFIG_RA_PLL1R_DIV == RA_CLOCKS_PLL_DIV_3
#  define RA_PLL1R_FREQUENCY          (RA_PLL_FREQUENCY / 3)
#elif CONFIG_RA_PLL1R_DIV == RA_CLOCKS_PLL_DIV_4
#  define RA_PLL1R_FREQUENCY          (RA_PLL_FREQUENCY / 4)
#else
#  define RA_PLL1R_FREQUENCY          (RA_PLL_FREQUENCY / 5) /* Default /5 */
#endif

/* PLL2 Frequency Calculations */
#if CONFIG_RA_PLL2_SOURCE == RA_CLOCKS_SOURCE_CLOCK_HOCO
#  define RA_PLL2_SOURCE_FREQ          CONFIG_RA_HOCO_FREQUENCY
#elif CONFIG_RA_PLL2_SOURCE == RA_CLOCKS_SOURCE_CLOCK_MAIN_OSC
#  define RA_PLL2_SOURCE_FREQ          CONFIG_RA_MAIN_OSC_FREQUENCY
#else
#  define RA_PLL2_SOURCE_FREQ          0  /* PLL2 disabled */
#endif

/* PLL2 VCO: 24MHz / 3 * 300 = 2400MHz */
#if CONFIG_RA_PLL2_DIV == RA_CLOCKS_PLL_DIV_3
#  define RA_PLL2_FREQUENCY           ((RA_PLL2_SOURCE_FREQ / 3) * CONFIG_RA_PLL2_MUL)
#elif CONFIG_RA_PLL2_DIV == RA_CLOCKS_PLL_DIV_2
#  define RA_PLL2_FREQUENCY           ((RA_PLL2_SOURCE_FREQ / 2) * CONFIG_RA_PLL2_MUL)
#elif CONFIG_RA_PLL2_DIV == RA_CLOCKS_PLL_DIV_1
#  define RA_PLL2_FREQUENCY           (RA_PLL2_SOURCE_FREQ * CONFIG_RA_PLL2_MUL)
#elif CONFIG_RA_PLL2_DIV == RA_CLOCKS_PLL_DIV_4
#  define RA_PLL2_FREQUENCY           ((RA_PLL2_SOURCE_FREQ / 4) * CONFIG_RA_PLL2_MUL)
#else
#  define RA_PLL2_FREQUENCY           ((RA_PLL2_SOURCE_FREQ / 3) * CONFIG_RA_PLL2_MUL) /* Default /3 */
#endif

/* PLL2P = 2400MHz / 4 = 600MHz */
#if CONFIG_RA_PLL2P_DIV == RA_CLOCKS_PLL_DIV_4
#  define RA_PLL2P_FREQUENCY          (RA_PLL2_FREQUENCY / 4)
#elif CONFIG_RA_PLL2P_DIV == RA_CLOCKS_PLL_DIV_2
#  define RA_PLL2P_FREQUENCY          (RA_PLL2_FREQUENCY / 2)
#elif CONFIG_RA_PLL2P_DIV == RA_CLOCKS_PLL_DIV_3
#  define RA_PLL2P_FREQUENCY          (RA_PLL2_FREQUENCY / 3)
#else
#  define RA_PLL2P_FREQUENCY          (RA_PLL2_FREQUENCY / 4) /* Default /4 */
#endif

/* PLL2Q = 2400MHz / 3 = 800MHz */
#if CONFIG_RA_PLL2Q_DIV == RA_CLOCKS_PLL_DIV_3
#  define RA_PLL2Q_FREQUENCY          (RA_PLL2_FREQUENCY / 3)
#elif CONFIG_RA_PLL2Q_DIV == RA_CLOCKS_PLL_DIV_2
#  define RA_PLL2Q_FREQUENCY          (RA_PLL2_FREQUENCY / 2)
#elif CONFIG_RA_PLL2Q_DIV == RA_CLOCKS_PLL_DIV_4
#  define RA_PLL2Q_FREQUENCY          (RA_PLL2_FREQUENCY / 4)
#else
#  define RA_PLL2Q_FREQUENCY          (RA_PLL2_FREQUENCY / 3) /* Default /3 */
#endif

/* PLL2R = 2400MHz / 5 = 480MHz */
#if CONFIG_RA_PLL2R_DIV == RA_CLOCKS_PLL_DIV_5
#  define RA_PLL2R_FREQUENCY          (RA_PLL2_FREQUENCY / 5)
#elif CONFIG_RA_PLL2R_DIV == RA_CLOCKS_PLL_DIV_2
#  define RA_PLL2R_FREQUENCY          (RA_PLL2_FREQUENCY / 2)
#elif CONFIG_RA_PLL2R_DIV == RA_CLOCKS_PLL_DIV_3
#  define RA_PLL2R_FREQUENCY          (RA_PLL2_FREQUENCY / 3)
#elif CONFIG_RA_PLL2R_DIV == RA_CLOCKS_PLL_DIV_4
#  define RA_PLL2R_FREQUENCY          (RA_PLL2_FREQUENCY / 4)
#else
#  define RA_PLL2R_FREQUENCY          (RA_PLL2_FREQUENCY / 5) /* Default /5 */
#endif

/* Clock Frequencies */

#if defined(CONFIG_RA_CLOCK_PLL1P) || defined(CONFIG_RA_CLOCK_PLL)
#  define RA_SYSTEM_CLOCK_FREQUENCY    RA_PLL1P_FREQUENCY
#elif defined(CONFIG_RA_CLOCK_HOCO)
#  define RA_SYSTEM_CLOCK_FREQUENCY    CONFIG_RA_HOCO_FREQUENCY
#elif defined(CONFIG_RA_CLOCK_MOCO)
#  define RA_SYSTEM_CLOCK_FREQUENCY    CONFIG_RA_MOCO_FREQUENCY
#elif defined(CONFIG_RA_CLOCK_MAIN_OSC)
#  define RA_SYSTEM_CLOCK_FREQUENCY    CONFIG_RA_MAIN_OSC_FREQUENCY
#else
#  define RA_SYSTEM_CLOCK_FREQUENCY    CONFIG_RA_HOCO_FREQUENCY
#endif

#ifndef CONFIG_RA_CPUCLK_DIV
#  define CONFIG_RA_CPUCLK_DIV        RA_CLOCKS_SYS_CLOCK_DIV_1   /* CPU clock = System clock / 1 */
#endif

#ifndef CONFIG_RA_ICK_DIV
#  define CONFIG_RA_ICK_DIV           RA_CLOCKS_SYS_CLOCK_DIV_4   /* ICLK = System clock / 4 (250MHz from 1GHz) */
#endif

#ifndef CONFIG_RA_PCKA_DIV
#  define CONFIG_RA_PCKA_DIV          RA_CLOCKS_SYS_CLOCK_DIV_8   /* PCKA = System clock / 8 (125MHz from 1GHz) */
#endif

#ifndef CONFIG_RA_PCKB_DIV
#  define CONFIG_RA_PCKB_DIV          RA_CLOCKS_SYS_CLOCK_DIV_16  /* PCKB = System clock / 16 (62.5MHz from 1GHz) */
#endif

#ifndef CONFIG_RA_PCKC_DIV
#  define CONFIG_RA_PCKC_DIV          RA_CLOCKS_SYS_CLOCK_DIV_8   /* PCKC = System clock / 8 (125MHz from 1GHz) */
#endif

#ifndef CONFIG_RA_PCKD_DIV
#  define CONFIG_RA_PCKD_DIV          RA_CLOCKS_SYS_CLOCK_DIV_4   /* PCKD = System clock / 4 (250MHz from 1GHz) */
#endif

#ifndef CONFIG_RA_PCKЕ_DIV
#  define CONFIG_RA_PCKЕ_DIV          RA_CLOCKS_SYS_CLOCK_DIV_4   /* PCKE = System clock / 4 (250MHz from 1GHz) */
#endif

#ifndef CONFIG_RA_BCLK_DIV
#  define CONFIG_RA_BCLK_DIV          RA_CLOCKS_SYS_CLOCK_DIV_8   /* BCLK = System clock / 8 (125MHz from 1GHz) */
#endif

#ifndef CONFIG_RA_FCLK_DIV
#  define CONFIG_RA_FCLK_DIV          RA_CLOCKS_SYS_CLOCK_DIV_8   /* FCLK = System clock / 8 (125MHz from 1GHz) */
#endif

/* Peripheral Clock Divider Configurations */
#ifndef CONFIG_RA_SCICLK_DIV
#  define CONFIG_RA_SCICLK_DIV        RA_CLOCKS_SCI_CLOCK_DIV_4   /* SCI clock div /4 */
#endif


#ifndef CONFIG_RA_SPICLK_DIV
#  define CONFIG_RA_SPICLK_DIV        RA_CLOCKS_SPI_CLOCK_DIV_4                           /* SPI clock div /4 */
#endif

#ifndef CONFIG_RA_CANFDCLK_DIV
#  define CONFIG_RA_CANFDCLK_DIV      RA_CLOCKS_CANFD_CLOCK_DIV_8                           /* CANFD clock div /4 */
#endif

#ifndef CONFIG_RA_OCTACLK_DIV
#  define CONFIG_RA_OCTACLK_DIV       RA_CLOCKS_OCTA_CLOCK_DIV_4                           /* OCTA clock div /2 (1 = /2) */
#endif

#ifndef CONFIG_RA_USBCLK_DIV
#  define CONFIG_RA_USBCLK_DIV        RA_CLOCKS_USB_CLOCK_DIV_5                           /* USB clock div /4 (3 = /4) */
#endif

#ifndef CONFIG_RA_SCISPICLK_DIV
#  define CONFIG_RA_SCISPICLK_DIV     RA_CLOCKS_SCISPI_CLOCK_DIV_4                        /* SCISPI clock div /4 */
#endif

#ifndef CONFIG_RA_GPTCLK_DIV
#  define CONFIG_RA_GPTCLK_DIV        RA_CLOCKS_GPT_CLOCK_DIV_4                           /* GPT clock div /4 */
#endif

#ifndef CONFIG_RA_IICCLK_DIV
#  define CONFIG_RA_IICCLK_DIV        RA_CLOCKS_IIC_CLOCK_DIV_4                           /* IIC clock div /4 */
#endif

#ifndef CONFIG_RA_ADCCLK_DIV
#  define CONFIG_RA_ADCCLK_DIV        RA_CLOCKS_ADC_CLOCK_DIV_4                           /* ADC clock div /4 */
#endif

/* Clock Divider Shift Positions for Register Settings */
#define RA_ICK_DIV                     (CONFIG_RA_ICK_DIV << 24)
#define RA_FCK_DIV                     (CONFIG_RA_FCLK_DIV << 28)
#define RA_PCKA_DIV                    (CONFIG_RA_PCKA_DIV << 12)
#define RA_PCKB_DIV                    (CONFIG_RA_PCKB_DIV << 8)
#define RA_PCKC_DIV                    (CONFIG_RA_PCKC_DIV << 4)
#define RA_PCKD_DIV                    (CONFIG_RA_PCKD_DIV << 0)

/* Helper macro to convert divider value to actual divisor */
#define RA_DIV_TO_DIVISOR(div) \
  (((div) >= 8) ? (((div) == 8) ? 3 : \
                   ((div) == 9) ? 6 : \
                   ((div) == 10) ? 12 : \
                   ((div) == 11) ? 24 : (1 << (div))) : (1 << (div)))

/* Derived Frequencies */

#define RA_CPUCLK_FREQUENCY            (RA_SYSTEM_CLOCK_FREQUENCY / RA_DIV_TO_DIVISOR(CONFIG_RA_CPUCLK_DIV))
#define RA_ICLK_FREQUENCY              (RA_SYSTEM_CLOCK_FREQUENCY / RA_DIV_TO_DIVISOR(CONFIG_RA_ICK_DIV))
#define RA_PCLKA_FREQUENCY             (RA_SYSTEM_CLOCK_FREQUENCY / RA_DIV_TO_DIVISOR(CONFIG_RA_PCKA_DIV))
#define RA_PCLKB_FREQUENCY             (RA_SYSTEM_CLOCK_FREQUENCY / RA_DIV_TO_DIVISOR(CONFIG_RA_PCKB_DIV))
#define RA_PCLKC_FREQUENCY             (RA_SYSTEM_CLOCK_FREQUENCY / RA_DIV_TO_DIVISOR(CONFIG_RA_PCKC_DIV))
#define RA_PCLKD_FREQUENCY             (RA_SYSTEM_CLOCK_FREQUENCY / RA_DIV_TO_DIVISOR(CONFIG_RA_PCKD_DIV))
#define RA_PCLKE_FREQUENCY             (RA_SYSTEM_CLOCK_FREQUENCY / RA_DIV_TO_DIVISOR(CONFIG_RA_PCKЕ_DIV))
#define RA_BCLK_FREQUENCY              (RA_SYSTEM_CLOCK_FREQUENCY / RA_DIV_TO_DIVISOR(CONFIG_RA_BCLK_DIV))
#define RA_FCLK_FREQUENCY              (RA_SYSTEM_CLOCK_FREQUENCY / RA_DIV_TO_DIVISOR(CONFIG_RA_FCLK_DIV))

/* Peripheral Clock Frequencies */
#ifndef RA_SCICLK_FREQUENCY
#  define RA_SCICLK_FREQUENCY          (RA_PLL1P_FREQUENCY / RA_DIV_TO_DIVISOR(CONFIG_RA_SCICLK_DIV))
#endif

/* Option Function Select Register Settings */

/* HOCO Frequency Options for RA8P1 */
#ifndef RA_HOCO_FREQUENCY
#  if CONFIG_RA_HOCO_FREQUENCY == 16000000
#    define RA_HOCO_FREQUENCY          0
#  elif CONFIG_RA_HOCO_FREQUENCY == 18000000
#    define RA_HOCO_FREQUENCY          1
#  elif CONFIG_RA_HOCO_FREQUENCY == 20000000
#    define RA_HOCO_FREQUENCY          2
#  elif CONFIG_RA_HOCO_FREQUENCY == 24000000
#    define RA_HOCO_FREQUENCY          4
#  elif CONFIG_RA_HOCO_FREQUENCY == 32000000
#    define RA_HOCO_FREQUENCY          5
#  elif CONFIG_RA_HOCO_FREQUENCY == 48000000
#    define RA_HOCO_FREQUENCY          7
#  elif CONFIG_RA_HOCO_FREQUENCY == 64000000
#    define RA_HOCO_FREQUENCY          8
#  else
#    define RA_HOCO_FREQUENCY          7         /* Default 48MHz for RA8P1 */
#  endif
#endif

#ifndef RA_HOCOEN
#  ifdef CONFIG_RA_HOCO_ENABLE
#    define RA_HOCOEN                  0         /* HOCO enabled */
#  else
#    define RA_HOCOEN                  1         /* HOCO disabled */
#  endif
#endif

#define RA_STARTUP_SOURCE_CLOCK_HZ    (RA_CFG_PLL1P_FREQUENCY_HZ)

/* Convert divisor bitfield settings into divisor values to calculate startup clocks */
#define RA_PRV_SCKDIVCR_DIV_VALUE(div)    (((div) & 8U) ? (3U << ((div) & ~8U)) : (1U << (div)))
#define RA_PRV_CPUCLK_DIV_VALUE          RA_PRV_SCKDIVCR_DIV_VALUE(RA_CFG_CPUCLK_DIV)
#define RA_PRV_ICLK_DIV_VALUE           RA_PRV_SCKDIVCR_DIV_VALUE(RA_CFG_ICLK_DIV)

/* System clock divider options. */

#define RA_CFG_CLOCKS_SECURE (0)
#define RA_CFG_CLOCKS_OVERRIDE (0)
#define RA_CFG_XTAL_HZ (24000000) /* XTAL 24000000Hz */
#define RA_CFG_HOCO_FREQUENCY (7) /* HOCO 48MHz */
#define RA_CFG_PLL_SOURCE (RA_CLOCKS_SOURCE_CLOCK_MAIN_OSC) /* PLL Src: XTAL */
#define RA_CFG_PLL_DIV (RA_CLOCKS_PLL_DIV_3) /* PLL Div /3 */
#define RA_CFG_PLL_MUL RA_CLOCKS_PLL_MUL(250,0) /* PLL Mul x240-259|Mul x250|PLL Mul x250.00 */
#define RA_CFG_PLL_FREQUENCY_HZ (2000000000) /* PLL 2000000000Hz */
#define RA_CFG_PLODIVP (RA_CLOCKS_PLL_DIV_2) /* PLL1P Div /2 */
#define RA_CFG_PLL1P_FREQUENCY_HZ (1000000000) /* PLL1P 1000000000Hz */
#define RA_CFG_PLODIVQ (RA_CLOCKS_PLL_DIV_6) /* PLL1Q Div /6 */
#define RA_CFG_PLL1Q_FREQUENCY_HZ (333333333) /* PLL1Q 333333333Hz */
#define RA_CFG_PLODIVR (RA_CLOCKS_PLL_DIV_5) /* PLL1R Div /5 */
#define RA_CFG_PLL1R_FREQUENCY_HZ (400000000) /* PLL1R 400000000Hz */
#define RA_CFG_PLL2_SOURCE (RA_CLOCKS_SOURCE_CLOCK_MAIN_OSC) /* PLL2 Src: XTAL */
#define RA_CFG_PLL2_DIV (RA_CLOCKS_PLL_DIV_3) /* PLL2 Div /3 */
#define RA_CFG_PLL2_MUL RA_CLOCKS_PLL_MUL(300,0) /* PLL2 Mul x280-300|Mul x300|PLL2 Mul x300.00 */
#define RA_CFG_PLL2_FREQUENCY_HZ (2400000000) /* PLL2 2400000000Hz */
#define RA_CFG_PL2ODIVP (RA_CLOCKS_PLL_DIV_4) /* PLL2P Div /4 */
#define RA_CFG_PLL2P_FREQUENCY_HZ (600000000) /* PLL2P 600000000Hz */
#define RA_CFG_PL2ODIVQ (RA_CLOCKS_PLL_DIV_3) /* PLL2Q Div /3 */
#define RA_CFG_PLL2Q_FREQUENCY_HZ (800000000) /* PLL2Q 800000000Hz */
#define RA_CFG_PL2ODIVR (RA_CLOCKS_PLL_DIV_5) /* PLL2R Div /5 */
#define RA_CFG_PLL2R_FREQUENCY_HZ (480000000) /* PLL2R 480000000Hz */
#define RA_CFG_CLOCK_SOURCE (RA_CLOCKS_SOURCE_CLOCK_PLL1P) /* Clock Src: PLL1P */
#define RA_CFG_CPUCLK_DIV (RA_CLOCKS_SYS_CLOCK_DIV_1) /* CPUCLK Div /1 */
#define RA_CFG_CPUCLK1_DIV (RA_CLOCKS_SYS_CLOCK_DIV_4) /* CPUCLK1 Div /4 */
#define RA_CFG_NPUCLK_DIV (RA_CLOCKS_SYS_CLOCK_DIV_2) /* NPUCLK Div /2 */
#define RA_CFG_MRICLK_DIV (RA_CLOCKS_SYS_CLOCK_DIV_4) /* MRICLK Div /4 */
#define RA_CFG_FCLK_DIV (RA_CLOCKS_SYS_CLOCK_DIV_8) /* MRPCLK Div /8 */
#define RA_CFG_ICLK_DIV (RA_CLOCKS_SYS_CLOCK_DIV_4) /* ICLK Div /4 */
#define RA_CFG_PCLKA_DIV (RA_CLOCKS_SYS_CLOCK_DIV_8) /* PCLKA Div /8 */
#define RA_CFG_PCLKB_DIV (RA_CLOCKS_SYS_CLOCK_DIV_16) /* PCLKB Div /16 */
#define RA_CFG_PCLKC_DIV (RA_CLOCKS_SYS_CLOCK_DIV_8) /* PCLKC Div /8 */
#define RA_CFG_PCLKD_DIV (RA_CLOCKS_SYS_CLOCK_DIV_4) /* PCLKD Div /4 */
#define RA_CFG_PCLKE_DIV (RA_CLOCKS_SYS_CLOCK_DIV_4) /* PCLKE Div /4 */
#define RA_CFG_BCLK_DIV (RA_CLOCKS_SYS_CLOCK_DIV_8) /* BCLK Div /8 */
#define RA_CFG_BCLKA_SOURCE (RA_CLOCKS_SOURCE_CLOCK_PLL2Q) /* BCLKA Src: PLL2Q */
#define RA_CFG_BCLKA_DIV (RA_CLOCKS_BCLKA_CLOCK_DIV_6) /* BCLKA Div /6 */
#define RA_CFG_SDCLK_OUTPUT (1) /* SDCLK Enabled */
#define RA_CFG_EBCLKA_SEL (0) /* EBCLK Src: BCLK (Synchronous) */
#define RA_CFG_BCLK_OUTPUT (2) /* EBCLK Div /2 */
#define RA_CFG_CLKOUT_SOURCE (RA_CLOCKS_SOURCE_CLOCK_HOCO) /* CLKOUT Src: HOCO */
#define RA_CFG_CLKOUT_DIV (RA_CLOCKS_SYS_CLOCK_DIV_1) /* CLKOUT Div /1 */
#define RA_CFG_SCICLK_SOURCE (RA_CLOCKS_SOURCE_CLOCK_PLL2R) /* SCICLK Src: PLL2R */
#define RA_CFG_SCICLK_DIV (RA_CLOCKS_SCI_CLOCK_DIV_4) /* SCICLK Div /4 */
#define RA_CFG_SPICLK_SOURCE (RA_CLOCKS_SOURCE_CLOCK_PLL1Q) /* SPICLK Src: PLL1Q */
#define RA_CFG_SPICLK_DIV (RA_CLOCKS_SPI_CLOCK_DIV_1) /* SPICLK Div /1 */
#define RA_CFG_CANFDCLK_SOURCE (RA_CLOCKS_SOURCE_CLOCK_PLL2R) /* CANFDCLK Src: PLL2R */
#define RA_CFG_CANFDCLK_DIV (RA_CLOCKS_CANFD_CLOCK_DIV_6) /* CANFDCLK Div /6 */
#define RA_CFG_GPTCLK_SOURCE (RA_CLOCKS_SOURCE_CLOCK_PLL2P) /* GPTCLK Src: PLL2P */
#define RA_CFG_GPTCLK_DIV (RA_CLOCKS_GPT_CLOCK_DIV_2) /* GPTCLK Div /2 */
#define RA_CFG_GPT_COUNT_CLOCK_SOURCE (1) /* GPT Src: PCLKD */
#define RA_CFG_LCDCLK_SOURCE (RA_CLOCKS_SOURCE_CLOCK_PLL2R) /* LCDCLK Src: PLL2R */
#define RA_CFG_LCDCLK_DIV (RA_CLOCKS_LCD_CLOCK_DIV_2) /* LCDCLK Div /2 */
#define RA_CFG_I3CCLK_SOURCE (RA_CLOCKS_SOURCE_CLOCK_PLL2Q) /* I3CCLK Src: PLL2Q */
#define RA_CFG_I3CCLK_DIV (RA_CLOCKS_I3C_CLOCK_DIV_4) /* I3CCLK Div /4 */
#define RA_CFG_UCLK_SOURCE (RA_CLOCKS_SOURCE_CLOCK_PLL2R) /* USBCLK Src: PLL2R */
#define RA_CFG_UCLK_DIV (RA_CLOCKS_USB_CLOCK_DIV_10) /* USBCLK Div /10 */
#define RA_CFG_USB60CLK_SOURCE (RA_CLOCKS_SOURCE_CLOCK_PLL2R) /* USB60CLK Src: PLL2R */
#define RA_CFG_USB60CLK_DIV (RA_CLOCKS_USB60_CLOCK_DIV_8) /* USB60CLK Div /8 */
#define RA_CFG_OCTACLK_SOURCE (RA_CLOCKS_SOURCE_CLOCK_PLL1Q) /* OCTACLK Src: PLL1Q */
#define RA_CFG_OCTACLK_DIV (RA_CLOCKS_OCTA_CLOCK_DIV_1) /* OCTACLK Div /1 */
#define RA_CFG_ADCCLK_SOURCE (RA_CLOCKS_SOURCE_CLOCK_PLL2R) /* ADCCLK Src: PLL2R */
#define RA_CFG_ADCCLK_DIV (RA_CLOCKS_ADC_CLOCK_DIV_4) /* ADCCLK Div /4 */
#define RA_CFG_ESWCLK_SOURCE (RA_CLOCKS_SOURCE_CLOCK_PLL1P) /* ESWCLK Src: PLL1P */
#define RA_CFG_ESWCLK_DIV (RA_CLOCKS_ESW_CLOCK_DIV_4) /* ESWCLK Div /4 */
#define RA_CFG_ESWPHYCLK_SOURCE (RA_CLOCKS_SOURCE_CLOCK_PLL1P) /* ESWPHYCLK Src: PLL1P */
#define RA_CFG_ESWPHYCLK_DIV (RA_CLOCKS_ESWPHY_CLOCK_DIV_2) /* ESWPHYCLK Div /2 */
#define RA_CFG_ETHPHYCLK_SOURCE (RA_CLOCKS_SOURCE_CLOCK_PLL2Q) /* ETHPHYCLK Src: PLL2Q */
#define RA_CFG_ETHPHYCLK_DIV (RA_CLOCKS_ETHPHY_CLOCK_DIV_32) /* ETHPHYCLK Div /32 */

#define RA_PRV_PCLKA_DIV_VALUE           RA_PRV_SCKDIVCR_DIV_VALUE(RA_CFG_PCLKA_DIV)
#define RA_PRV_PCLKB_DIV_VALUE           RA_PRV_SCKDIVCR_DIV_VALUE(RA_CFG_PCLKB_DIV)
#define RA_PRV_PCLKC_DIV_VALUE           RA_PRV_SCKDIVCR_DIV_VALUE(RA_CFG_PCLKC_DIV)
#define RA_PRV_PCLKD_DIV_VALUE           RA_PRV_SCKDIVCR_DIV_VALUE(RA_CFG_PCLKD_DIV)
#define RA_PRV_PCLKE_DIV_VALUE           RA_PRV_SCKDIVCR_DIV_VALUE(RA_CFG_PCLKE_DIV)
#define RA_PRV_BCLK_DIV_VALUE            RA_PRV_SCKDIVCR_DIV_VALUE(RA_CFG_BCLK_DIV)
#define RA_PRV_FCLK_DIV_VALUE            RA_PRV_SCKDIVCR_DIV_VALUE(RA_CFG_FCLK_DIV)
#define RA_PRV_MRICLK_DIV_VALUE          RA_PRV_SCKDIVCR_DIV_VALUE(RA_CFG_MRICLK_DIV)

/* Startup clock frequency of each system clock. These macros are only helpful if the system clock and dividers have
 * not changed since startup. These macros are not used in FSP modules except for the clock startup code. */
#define RA_STARTUP_CPUCLK_HZ             (RA_STARTUP_SOURCE_CLOCK_HZ / RA_PRV_CPUCLK_DIV_VALUE)
#define RA_STARTUP_ICLK_HZ               (RA_STARTUP_SOURCE_CLOCK_HZ / RA_PRV_ICLK_DIV_VALUE)
#define RA_STARTUP_PCLKA_HZ              (RA_STARTUP_SOURCE_CLOCK_HZ / RA_PRV_PCLKA_DIV_VALUE)
#define RA_STARTUP_PCLKB_HZ              (RA_STARTUP_SOURCE_CLOCK_HZ / RA_PRV_PCLKB_DIV_VALUE)
#define RA_STARTUP_PCLKC_HZ              (RA_STARTUP_SOURCE_CLOCK_HZ / RA_PRV_PCLKC_DIV_VALUE)
#define RA_STARTUP_PCLKD_HZ              (RA_STARTUP_SOURCE_CLOCK_HZ / RA_PRV_PCLKD_DIV_VALUE)
#define RA_STARTUP_PCLKE_HZ              (RA_STARTUP_SOURCE_CLOCK_HZ / RA_PRV_PCLKE_DIV_VALUE)
#define RA_STARTUP_BCLK_HZ               (RA_STARTUP_SOURCE_CLOCK_HZ / RA_PRV_BCLK_DIV_VALUE)
#define RA_STARTUP_FCLK_HZ               (RA_STARTUP_SOURCE_CLOCK_HZ / RA_PRV_FCLK_DIV_VALUE)
#define RA_STARTUP_MRICLK_HZ             (RA_STARTUP_SOURCE_CLOCK_HZ / RA_PRV_MRICLK_DIV_VALUE)

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CLOCK_H */

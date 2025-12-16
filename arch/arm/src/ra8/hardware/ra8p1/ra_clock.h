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

#ifndef CONFIG_RA_MAIN_OSC_FREQUENCY
#  define CONFIG_RA_MAIN_OSC_FREQUENCY    24000000  /* 24MHz External Crystal (RA8P1 EVK) */
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
/* PLL Divider encoding to divisor value (integer only for preprocessor compatibility)
 * Note: Encoding 9 represents 1.5 divider - use RA_PLL_DIV_FREQ macro for correct frequency calculation
 * Encoding values: 0=/1, 1=/2, 2=/3, 3=/4, 4=/5, 5=/6, 7=/8, 8=/9, 9=/1.5, 15=/16
 */
#define RA_PLL_DIV_TO_DIVISOR(enc) \
    ((enc) == 0 ? 1 : \
     (enc) == 1 ? 2 : \
     (enc) == 2 ? 3 : \
     (enc) == 3 ? 4 : \
     (enc) == 4 ? 5 : \
     (enc) == 5 ? 6 : \
     (enc) == 7 ? 8 : \
     (enc) == 8 ? 9 : \
     (enc) == 9 ? 2 : \
     (enc) == 15 ? 16 : 1)

/* Special macro for frequency calculation that handles 1.5 divider correctly
 * For encoding 9 (1.5 divider): freq / 1.5 = freq * 2 / 3
 * Uses UL suffix to prevent integer overflow with large frequencies (>2GHz)
 */
#define RA_PLL_DIV_FREQ(freq, enc) \
    ((enc) == 9 ? (((freq) * 2UL) / 3UL) : ((freq) / RA_PLL_DIV_TO_DIVISOR(enc)))

/* Default Profile (Maximum Performance) - RA8P1 */
#if defined(CONFIG_RA_CLOCK_PROFILE_DEFAULT) && !defined(CONFIG_RA_CLOCK_PROFILE_CUSTOM)
  /* PLL1 Configuration: 24MHz XTAL -> /3 -> 8MHz * 250 = 2000MHz VCO */
  #define RA_PROFILE_PLL_DIV            RA_CLOCKS_PLL_DIV_3      /* /3 divider */
  #define RA_PROFILE_PLL_MUL            250                       /* x250 multiplier */
  #define RA_PROFILE_PLL1P_DIV          RA_CLOCKS_PLL_DIV_2      /* /2 -> 1000MHz CPU */
  #define RA_PROFILE_PLL1Q_DIV          RA_CLOCKS_PLL_DIV_6      /* /6 -> 333MHz */
  #define RA_PROFILE_PLL1R_DIV          RA_CLOCKS_PLL_DIV_5      /* /5 -> 400MHz */

  /* PLL2 Configuration: 24MHz XTAL -> /3 -> 8MHz * 300 = 2400MHz VCO */
  #define RA_PROFILE_PLL2_DIV           RA_CLOCKS_PLL_DIV_3      /* /3 divider */
  #define RA_PROFILE_PLL2_MUL           300                       /* x300 multiplier */
  #define RA_PROFILE_PLL2P_DIV          RA_CLOCKS_PLL_DIV_4      /* /4 -> 600MHz */
  #define RA_PROFILE_PLL2Q_DIV          RA_CLOCKS_PLL_DIV_3      /* /3 -> 800MHz */
  #define RA_PROFILE_PLL2R_DIV          RA_CLOCKS_PLL_DIV_5      /* /5 -> 480MHz */

  /* System Clock Dividers (matches FSP BSP_CFG defaults) */
  #define RA_PROFILE_CPUCLK_DIV         RA_CLOCKS_SYS_CLOCK_DIV_1    /* /1 -> 1000MHz */
  #define RA_PROFILE_ICK_DIV            RA_CLOCKS_SYS_CLOCK_DIV_4    /* /4 -> 250MHz */
  #define RA_PROFILE_PCKA_DIV           RA_CLOCKS_SYS_CLOCK_DIV_8    /* /8 -> 125MHz */
  #define RA_PROFILE_PCKB_DIV           RA_CLOCKS_SYS_CLOCK_DIV_16   /* /16 -> 62.5MHz */
  #define RA_PROFILE_PCKC_DIV           RA_CLOCKS_SYS_CLOCK_DIV_8    /* /8 -> 125MHz */
  #define RA_PROFILE_PCKD_DIV           RA_CLOCKS_SYS_CLOCK_DIV_4    /* /4 -> 250MHz */
  #define RA_PROFILE_PCKE_DIV           RA_CLOCKS_SYS_CLOCK_DIV_4    /* /4 -> 250MHz */
  #define RA_PROFILE_BCLK_DIV           RA_CLOCKS_SYS_CLOCK_DIV_8    /* /8 -> 125MHz */
  #define RA_PROFILE_FCLK_DIV           RA_CLOCKS_SYS_CLOCK_DIV_8    /* /8 -> 125MHz */

/* Low Power Profile - RA8P1 */
#elif defined(CONFIG_RA_CLOCK_PROFILE_LOW_POWER) && !defined(CONFIG_RA_CLOCK_PROFILE_CUSTOM)
  /* PLL1 Configuration: 24MHz XTAL -> /3 -> 8MHz * 125 = 1000MHz VCO */
  #define RA_PROFILE_PLL_DIV            RA_CLOCKS_PLL_DIV_3      /* /3 divider */
  #define RA_PROFILE_PLL_MUL            125                       /* x125 multiplier */
  #define RA_PROFILE_PLL1P_DIV          RA_CLOCKS_PLL_DIV_2      /* /2 -> 500MHz CPU */
  #define RA_PROFILE_PLL1Q_DIV          RA_CLOCKS_PLL_DIV_6      /* /6 -> 166MHz */
  #define RA_PROFILE_PLL1R_DIV          RA_CLOCKS_PLL_DIV_5      /* /5 -> 200MHz */

  /* PLL2 Configuration: 24MHz XTAL -> /3 -> 8MHz * 150 = 1200MHz VCO */
  #define RA_PROFILE_PLL2_DIV           RA_CLOCKS_PLL_DIV_3      /* /3 divider */
  #define RA_PROFILE_PLL2_MUL           150                       /* x150 multiplier */
  #define RA_PROFILE_PLL2P_DIV          RA_CLOCKS_PLL_DIV_4      /* /4 -> 300MHz */
  #define RA_PROFILE_PLL2Q_DIV          RA_CLOCKS_PLL_DIV_3      /* /3 -> 400MHz */
  #define RA_PROFILE_PLL2R_DIV          RA_CLOCKS_PLL_DIV_5      /* /5 -> 240MHz */

  /* System Clock Dividers (reduced for power savings) */
  #define RA_PROFILE_CPUCLK_DIV         RA_CLOCKS_SYS_CLOCK_DIV_1    /* /1 -> 500MHz */
  #define RA_PROFILE_ICK_DIV            RA_CLOCKS_SYS_CLOCK_DIV_4    /* /4 -> 125MHz */
  #define RA_PROFILE_PCKA_DIV           RA_CLOCKS_SYS_CLOCK_DIV_8    /* /8 -> 62.5MHz */
  #define RA_PROFILE_PCKB_DIV           RA_CLOCKS_SYS_CLOCK_DIV_16   /* /16 -> 31.25MHz */
  #define RA_PROFILE_PCKC_DIV           RA_CLOCKS_SYS_CLOCK_DIV_8    /* /8 -> 62.5MHz */
  #define RA_PROFILE_PCKD_DIV           RA_CLOCKS_SYS_CLOCK_DIV_4    /* /4 -> 125MHz */
  #define RA_PROFILE_PCKE_DIV           RA_CLOCKS_SYS_CLOCK_DIV_4    /* /4 -> 125MHz */
  #define RA_PROFILE_BCLK_DIV           RA_CLOCKS_SYS_CLOCK_DIV_8    /* /8 -> 62.5MHz */
  #define RA_PROFILE_FCLK_DIV           RA_CLOCKS_SYS_CLOCK_DIV_8    /* /8 -> 62.5MHz */
#endif

/****************************************************************************
 * Configuration Default Macro (Phase 3 Optimization)
 * Single macro to define CONFIG_RA_* with profile-based fallback.
 * Reduces ~140 lines of repetitive if/else to concise definitions.
 ****************************************************************************/
#define RA_CONFIG_DEFAULT(cfg, profile, fallback) \
    _RA_CONFIG_DEFAULT_IMPL(cfg, profile, fallback)

/* Implementation detail: Check for profile override, else use fallback */
#define _RA_CONFIG_DEFAULT_IMPL(cfg, profile, fallback) \
    _RA_CONFIG_DEFAULT_##cfg##_IMPL(profile, fallback)

/* PLL configuration with profile-based defaults */
#ifndef CONFIG_RA_PLL_SOURCE
#  define CONFIG_RA_PLL_SOURCE        RA_CLOCKS_SOURCE_CLOCK_MAIN_OSC
#endif

/* PLL Dividers: Use profile defaults if available, else fallback */
#ifndef CONFIG_RA_PLL_DIV
#  ifdef RA_PROFILE_PLL_DIV
#    define CONFIG_RA_PLL_DIV         RA_PROFILE_PLL_DIV
#  else
#    define CONFIG_RA_PLL_DIV         RA_CLOCKS_PLL_DIV_3
#  endif
#endif

#ifndef CONFIG_RA_PLL_MUL
#  ifdef RA_PROFILE_PLL_MUL
#    define CONFIG_RA_PLL_MUL         RA_PROFILE_PLL_MUL
#  else
#    define CONFIG_RA_PLL_MUL         250
#  endif
#endif

#ifndef CONFIG_RA_PLL1P_DIV
#  ifdef RA_PROFILE_PLL1P_DIV
#    define CONFIG_RA_PLL1P_DIV       RA_PROFILE_PLL1P_DIV
#  else
#    define CONFIG_RA_PLL1P_DIV       RA_CLOCKS_PLL_DIV_2
#  endif
#endif

#ifndef CONFIG_RA_PLL1Q_DIV
#  ifdef RA_PROFILE_PLL1Q_DIV
#    define CONFIG_RA_PLL1Q_DIV       RA_PROFILE_PLL1Q_DIV
#  else
#    define CONFIG_RA_PLL1Q_DIV       RA_CLOCKS_PLL_DIV_6
#  endif
#endif

#ifndef CONFIG_RA_PLL1R_DIV
#  ifdef RA_PROFILE_PLL1R_DIV
#    define CONFIG_RA_PLL1R_DIV       RA_PROFILE_PLL1R_DIV
#  else
#    define CONFIG_RA_PLL1R_DIV       RA_CLOCKS_PLL_DIV_5
#  endif
#endif

#ifndef CONFIG_RA_PLL2_DIV
#  ifdef RA_PROFILE_PLL2_DIV
#    define CONFIG_RA_PLL2_DIV        RA_PROFILE_PLL2_DIV
#  else
#    define CONFIG_RA_PLL2_DIV        RA_CLOCKS_PLL_DIV_3
#  endif
#endif

#ifndef CONFIG_RA_PLL2_MUL
#  ifdef RA_PROFILE_PLL2_MUL
#    define CONFIG_RA_PLL2_MUL        RA_PROFILE_PLL2_MUL
#  else
#    define CONFIG_RA_PLL2_MUL        300
#  endif
#endif

#ifndef CONFIG_RA_PLL2P_DIV
#  ifdef RA_PROFILE_PLL2P_DIV
#    define CONFIG_RA_PLL2P_DIV       RA_PROFILE_PLL2P_DIV
#  else
#    define CONFIG_RA_PLL2P_DIV       RA_CLOCKS_PLL_DIV_4
#  endif
#endif

#ifndef CONFIG_RA_PLL2Q_DIV
#  ifdef RA_PROFILE_PLL2Q_DIV
#    define CONFIG_RA_PLL2Q_DIV       RA_PROFILE_PLL2Q_DIV
#  else
#    define CONFIG_RA_PLL2Q_DIV       RA_CLOCKS_PLL_DIV_3
#  endif
#endif

#ifndef CONFIG_RA_PLL2R_DIV
#  ifdef RA_PROFILE_PLL2R_DIV
#    define CONFIG_RA_PLL2R_DIV       RA_PROFILE_PLL2R_DIV
#  else
#    define CONFIG_RA_PLL2R_DIV       RA_CLOCKS_PLL_DIV_5
#  endif
#endif

/* System clock dividers with profile-based defaults */
#ifndef CONFIG_RA_CPUCLK_DIV
#  ifdef RA_PROFILE_CPUCLK_DIV
#    define CONFIG_RA_CPUCLK_DIV      RA_PROFILE_CPUCLK_DIV
#  else
#    define CONFIG_RA_CPUCLK_DIV      RA_CLOCKS_SYS_CLOCK_DIV_1
#  endif
#endif

#ifndef CONFIG_RA_ICK_DIV
#  ifdef RA_PROFILE_ICK_DIV
#    define CONFIG_RA_ICK_DIV         RA_PROFILE_ICK_DIV
#  else
#    define CONFIG_RA_ICK_DIV         RA_CLOCKS_SYS_CLOCK_DIV_4
#  endif
#endif

#ifndef CONFIG_RA_PCKA_DIV
#  ifdef RA_PROFILE_PCKA_DIV
#    define CONFIG_RA_PCKA_DIV        RA_PROFILE_PCKA_DIV
#  else
#    define CONFIG_RA_PCKA_DIV        RA_CLOCKS_SYS_CLOCK_DIV_8
#  endif
#endif

#ifndef CONFIG_RA_PCKB_DIV
#  ifdef RA_PROFILE_PCKB_DIV
#    define CONFIG_RA_PCKB_DIV        RA_PROFILE_PCKB_DIV
#  else
#    define CONFIG_RA_PCKB_DIV        RA_CLOCKS_SYS_CLOCK_DIV_16
#  endif
#endif

#ifndef CONFIG_RA_PCKC_DIV
#  ifdef RA_PROFILE_PCKC_DIV
#    define CONFIG_RA_PCKC_DIV        RA_PROFILE_PCKC_DIV
#  else
#    define CONFIG_RA_PCKC_DIV        RA_CLOCKS_SYS_CLOCK_DIV_8
#  endif
#endif

#ifndef CONFIG_RA_PCKD_DIV
#  ifdef RA_PROFILE_PCKD_DIV
#    define CONFIG_RA_PCKD_DIV        RA_PROFILE_PCKD_DIV
#  else
#    define CONFIG_RA_PCKD_DIV        RA_CLOCKS_SYS_CLOCK_DIV_4
#  endif
#endif

#ifndef CONFIG_RA_PCKE_DIV
#  ifdef RA_PROFILE_PCKE_DIV
#    define CONFIG_RA_PCKE_DIV        RA_PROFILE_PCKE_DIV
#  else
#    define CONFIG_RA_PCKE_DIV        RA_CLOCKS_SYS_CLOCK_DIV_4
#  endif
#endif

#ifndef CONFIG_RA_BCLK_DIV
#  ifdef RA_PROFILE_BCLK_DIV
#    define CONFIG_RA_BCLK_DIV        RA_PROFILE_BCLK_DIV
#  else
#    define CONFIG_RA_BCLK_DIV        RA_CLOCKS_SYS_CLOCK_DIV_8
#  endif
#endif

#ifndef CONFIG_RA_FCLK_DIV
#  ifdef RA_PROFILE_FCLK_DIV
#    define CONFIG_RA_FCLK_DIV        RA_PROFILE_FCLK_DIV
#  else
#    define CONFIG_RA_FCLK_DIV        RA_CLOCKS_SYS_CLOCK_DIV_8
#  endif
#endif

/* Peripheral Clock Divider Defaults */
#ifndef CONFIG_RA_SCICLK_DIV
#  define CONFIG_RA_SCICLK_DIV        RA_CLOCKS_SCI_CLOCK_DIV_4
#endif

#ifndef CONFIG_RA_SPICLK_DIV
#  define CONFIG_RA_SPICLK_DIV        RA_CLOCKS_SPI_CLOCK_DIV_4
#endif

#ifndef CONFIG_RA_CANFDCLK_DIV
#  define CONFIG_RA_CANFDCLK_DIV      RA_CLOCKS_CANFD_CLOCK_DIV_8
#endif

#ifndef CONFIG_RA_OCTACLK_DIV
#  define CONFIG_RA_OCTACLK_DIV       RA_CLOCKS_OCTA_CLOCK_DIV_4
#endif

#ifndef CONFIG_RA_USBCLK_DIV
#  define CONFIG_RA_USBCLK_DIV        RA_CLOCKS_USB_CLOCK_DIV_5
#endif

#ifndef CONFIG_RA_SCISPICLK_DIV
#  define CONFIG_RA_SCISPICLK_DIV     RA_CLOCKS_SCISPI_CLOCK_DIV_4
#endif

#ifndef CONFIG_RA_GPTCLK_DIV
#  define CONFIG_RA_GPTCLK_DIV        RA_CLOCKS_GPT_CLOCK_DIV_4
#endif

#ifndef CONFIG_RA_IICCLK_DIV
#  define CONFIG_RA_IICCLK_DIV        RA_CLOCKS_IIC_CLOCK_DIV_4
#endif

#ifndef CONFIG_RA_ADCCLK_DIV
#  define CONFIG_RA_ADCCLK_DIV        RA_CLOCKS_ADC_CLOCK_DIV_4
#endif

/****************************************************************************
 * PLL Frequency Calculation (Phase 3 Optimization)
 * Unified PLL divider-to-divisor conversion using a single macro.
 * Reduces ~140 lines of if/elif chains to ~30 lines.
 ****************************************************************************/

/* PLL source frequency selection */
#if defined(CONFIG_RA_PLL_SOURCE_HOCO)
#  define RA_PLL_SOURCE_FREQ          CONFIG_RA_HOCO_FREQUENCY
#  define CONFIG_RA_PLL_SOURCE        RA_CLOCKS_SOURCE_CLOCK_HOCO
#elif defined(CONFIG_RA_PLL_SOURCE_MAIN_OSC)
#  define RA_PLL_SOURCE_FREQ          CONFIG_RA_MAIN_OSC_FREQUENCY
#  define CONFIG_RA_PLL_SOURCE        RA_CLOCKS_SOURCE_CLOCK_MAIN_OSC
#else
#  define RA_PLL_SOURCE_FREQ          CONFIG_RA_HOCO_FREQUENCY
#  define CONFIG_RA_PLL_SOURCE        RA_CLOCKS_SOURCE_CLOCK_HOCO
#endif

/* PLL2 source frequency selection */
#if defined(CONFIG_RA_PLL2_SOURCE_HOCO)
#  define RA_PLL2_SOURCE_FREQ         CONFIG_RA_HOCO_FREQUENCY
#  define CONFIG_RA_PLL2_SOURCE       RA_CLOCKS_SOURCE_CLOCK_HOCO
#elif defined(CONFIG_RA_PLL2_SOURCE_MAIN_OSC)
#  define RA_PLL2_SOURCE_FREQ         CONFIG_RA_MAIN_OSC_FREQUENCY
#  define CONFIG_RA_PLL2_SOURCE       RA_CLOCKS_SOURCE_CLOCK_MAIN_OSC
#else
#  define RA_PLL2_SOURCE_FREQ         CONFIG_RA_MAIN_OSC_FREQUENCY
#  define CONFIG_RA_PLL2_SOURCE       RA_CLOCKS_SOURCE_CLOCK_MAIN_OSC
#endif

/* Clock settling delay */
#ifndef CONFIG_RA_CLOCK_SETTLING_DELAY_US
#  define CONFIG_RA_CLOCK_SETTLING_DELAY_US  150U
#endif

/****************************************************************************
 * PLL Frequency Calculations (if/elif chains for preprocessor compatibility)
 * This matches the working implementation and avoids macro expansion issues.
 ****************************************************************************/

/* PLL1 VCO frequency: source / input_div * multiplier */
#if CONFIG_RA_PLL_DIV == RA_CLOCKS_PLL_DIV_3
#  define RA_PLL_FREQUENCY            (((RA_PLL_SOURCE_FREQ) / 3UL) * (CONFIG_RA_PLL_MUL))
#elif CONFIG_RA_PLL_DIV == RA_CLOCKS_PLL_DIV_2
#  define RA_PLL_FREQUENCY            (((RA_PLL_SOURCE_FREQ) / 2UL) * (CONFIG_RA_PLL_MUL))
#elif CONFIG_RA_PLL_DIV == RA_CLOCKS_PLL_DIV_1
#  define RA_PLL_FREQUENCY            ((RA_PLL_SOURCE_FREQ) * (CONFIG_RA_PLL_MUL))
#elif CONFIG_RA_PLL_DIV == RA_CLOCKS_PLL_DIV_4
#  define RA_PLL_FREQUENCY            (((RA_PLL_SOURCE_FREQ) / 4UL) * (CONFIG_RA_PLL_MUL))
#elif CONFIG_RA_PLL_DIV == RA_CLOCKS_PLL_DIV_5
#  define RA_PLL_FREQUENCY            (((RA_PLL_SOURCE_FREQ) / 5UL) * (CONFIG_RA_PLL_MUL))
#elif CONFIG_RA_PLL_DIV == RA_CLOCKS_PLL_DIV_6
#  define RA_PLL_FREQUENCY            (((RA_PLL_SOURCE_FREQ) / 6UL) * (CONFIG_RA_PLL_MUL))
#else
#  define RA_PLL_FREQUENCY            (((RA_PLL_SOURCE_FREQ) / 3UL) * (CONFIG_RA_PLL_MUL))
#endif

/* PLL1P output frequency */
#if CONFIG_RA_PLL1P_DIV == RA_CLOCKS_PLL_DIV_1
#  define RA_PLL1P_FREQUENCY          (RA_PLL_FREQUENCY)
#elif CONFIG_RA_PLL1P_DIV == RA_CLOCKS_PLL_DIV_2
#  define RA_PLL1P_FREQUENCY          ((RA_PLL_FREQUENCY) / 2UL)
#elif CONFIG_RA_PLL1P_DIV == RA_CLOCKS_PLL_DIV_3
#  define RA_PLL1P_FREQUENCY          ((RA_PLL_FREQUENCY) / 3UL)
#elif CONFIG_RA_PLL1P_DIV == RA_CLOCKS_PLL_DIV_4
#  define RA_PLL1P_FREQUENCY          ((RA_PLL_FREQUENCY) / 4UL)
#elif CONFIG_RA_PLL1P_DIV == RA_CLOCKS_PLL_DIV_5
#  define RA_PLL1P_FREQUENCY          ((RA_PLL_FREQUENCY) / 5UL)
#elif CONFIG_RA_PLL1P_DIV == RA_CLOCKS_PLL_DIV_6
#  define RA_PLL1P_FREQUENCY          ((RA_PLL_FREQUENCY) / 6UL)
#else
#  define RA_PLL1P_FREQUENCY          ((RA_PLL_FREQUENCY) / 2UL)
#endif

/* PLL1Q output frequency */
#if CONFIG_RA_PLL1Q_DIV == RA_CLOCKS_PLL_DIV_1
#  define RA_PLL1Q_FREQUENCY          (RA_PLL_FREQUENCY)
#elif CONFIG_RA_PLL1Q_DIV == RA_CLOCKS_PLL_DIV_2
#  define RA_PLL1Q_FREQUENCY          ((RA_PLL_FREQUENCY) / 2UL)
#elif CONFIG_RA_PLL1Q_DIV == RA_CLOCKS_PLL_DIV_3
#  define RA_PLL1Q_FREQUENCY          ((RA_PLL_FREQUENCY) / 3UL)
#elif CONFIG_RA_PLL1Q_DIV == RA_CLOCKS_PLL_DIV_4
#  define RA_PLL1Q_FREQUENCY          ((RA_PLL_FREQUENCY) / 4UL)
#elif CONFIG_RA_PLL1Q_DIV == RA_CLOCKS_PLL_DIV_5
#  define RA_PLL1Q_FREQUENCY          ((RA_PLL_FREQUENCY) / 5UL)
#elif CONFIG_RA_PLL1Q_DIV == RA_CLOCKS_PLL_DIV_6
#  define RA_PLL1Q_FREQUENCY          ((RA_PLL_FREQUENCY) / 6UL)
#else
#  define RA_PLL1Q_FREQUENCY          ((RA_PLL_FREQUENCY) / 6UL)
#endif

/* PLL1R output frequency */
#if CONFIG_RA_PLL1R_DIV == RA_CLOCKS_PLL_DIV_1
#  define RA_PLL1R_FREQUENCY          (RA_PLL_FREQUENCY)
#elif CONFIG_RA_PLL1R_DIV == RA_CLOCKS_PLL_DIV_2
#  define RA_PLL1R_FREQUENCY          ((RA_PLL_FREQUENCY) / 2UL)
#elif CONFIG_RA_PLL1R_DIV == RA_CLOCKS_PLL_DIV_3
#  define RA_PLL1R_FREQUENCY          ((RA_PLL_FREQUENCY) / 3UL)
#elif CONFIG_RA_PLL1R_DIV == RA_CLOCKS_PLL_DIV_4
#  define RA_PLL1R_FREQUENCY          ((RA_PLL_FREQUENCY) / 4UL)
#elif CONFIG_RA_PLL1R_DIV == RA_CLOCKS_PLL_DIV_5
#  define RA_PLL1R_FREQUENCY          ((RA_PLL_FREQUENCY) / 5UL)
#elif CONFIG_RA_PLL1R_DIV == RA_CLOCKS_PLL_DIV_6
#  define RA_PLL1R_FREQUENCY          ((RA_PLL_FREQUENCY) / 6UL)
#else
#  define RA_PLL1R_FREQUENCY          ((RA_PLL_FREQUENCY) / 5UL)
#endif

/* PLL2 VCO frequency */
#if CONFIG_RA_PLL2_DIV == RA_CLOCKS_PLL_DIV_3
#  define RA_PLL2_FREQUENCY           (((RA_PLL2_SOURCE_FREQ) / 3UL) * (CONFIG_RA_PLL2_MUL))
#elif CONFIG_RA_PLL2_DIV == RA_CLOCKS_PLL_DIV_2
#  define RA_PLL2_FREQUENCY           (((RA_PLL2_SOURCE_FREQ) / 2UL) * (CONFIG_RA_PLL2_MUL))
#elif CONFIG_RA_PLL2_DIV == RA_CLOCKS_PLL_DIV_1
#  define RA_PLL2_FREQUENCY           ((RA_PLL2_SOURCE_FREQ) * (CONFIG_RA_PLL2_MUL))
#elif CONFIG_RA_PLL2_DIV == RA_CLOCKS_PLL_DIV_4
#  define RA_PLL2_FREQUENCY           (((RA_PLL2_SOURCE_FREQ) / 4UL) * (CONFIG_RA_PLL2_MUL))
#else
#  define RA_PLL2_FREQUENCY           (((RA_PLL2_SOURCE_FREQ) / 3UL) * (CONFIG_RA_PLL2_MUL))
#endif

/* PLL2P output frequency */
#if CONFIG_RA_PLL2P_DIV == RA_CLOCKS_PLL_DIV_1
#  define RA_PLL2P_FREQUENCY          (RA_PLL2_FREQUENCY)
#elif CONFIG_RA_PLL2P_DIV == RA_CLOCKS_PLL_DIV_2
#  define RA_PLL2P_FREQUENCY          ((RA_PLL2_FREQUENCY) / 2UL)
#elif CONFIG_RA_PLL2P_DIV == RA_CLOCKS_PLL_DIV_3
#  define RA_PLL2P_FREQUENCY          ((RA_PLL2_FREQUENCY) / 3UL)
#elif CONFIG_RA_PLL2P_DIV == RA_CLOCKS_PLL_DIV_4
#  define RA_PLL2P_FREQUENCY          ((RA_PLL2_FREQUENCY) / 4UL)
#elif CONFIG_RA_PLL2P_DIV == RA_CLOCKS_PLL_DIV_5
#  define RA_PLL2P_FREQUENCY          ((RA_PLL2_FREQUENCY) / 5UL)
#elif CONFIG_RA_PLL2P_DIV == RA_CLOCKS_PLL_DIV_6
#  define RA_PLL2P_FREQUENCY          ((RA_PLL2_FREQUENCY) / 6UL)
#else
#  define RA_PLL2P_FREQUENCY          ((RA_PLL2_FREQUENCY) / 4UL)
#endif

/* PLL2Q output frequency */
#if CONFIG_RA_PLL2Q_DIV == RA_CLOCKS_PLL_DIV_1
#  define RA_PLL2Q_FREQUENCY          (RA_PLL2_FREQUENCY)
#elif CONFIG_RA_PLL2Q_DIV == RA_CLOCKS_PLL_DIV_2
#  define RA_PLL2Q_FREQUENCY          ((RA_PLL2_FREQUENCY) / 2UL)
#elif CONFIG_RA_PLL2Q_DIV == RA_CLOCKS_PLL_DIV_3
#  define RA_PLL2Q_FREQUENCY          ((RA_PLL2_FREQUENCY) / 3UL)
#elif CONFIG_RA_PLL2Q_DIV == RA_CLOCKS_PLL_DIV_4
#  define RA_PLL2Q_FREQUENCY          ((RA_PLL2_FREQUENCY) / 4UL)
#elif CONFIG_RA_PLL2Q_DIV == RA_CLOCKS_PLL_DIV_5
#  define RA_PLL2Q_FREQUENCY          ((RA_PLL2_FREQUENCY) / 5UL)
#elif CONFIG_RA_PLL2Q_DIV == RA_CLOCKS_PLL_DIV_6
#  define RA_PLL2Q_FREQUENCY          ((RA_PLL2_FREQUENCY) / 6UL)
#elif CONFIG_RA_PLL2Q_DIV == RA_CLOCKS_PLL_DIV_8
#  define RA_PLL2Q_FREQUENCY          ((RA_PLL2_FREQUENCY) / 8UL)
#elif CONFIG_RA_PLL2Q_DIV == RA_CLOCKS_PLL_DIV_9
#  define RA_PLL2Q_FREQUENCY          ((RA_PLL2_FREQUENCY) / 9UL)
#elif CONFIG_RA_PLL2Q_DIV == RA_CLOCKS_PLL_DIV_1_5
#  define RA_PLL2Q_FREQUENCY          (((RA_PLL2_FREQUENCY) * 2UL) / 3UL)
#else
#  define RA_PLL2Q_FREQUENCY          ((RA_PLL2_FREQUENCY) / 3UL)
#endif

/* PLL2R output frequency */
#if CONFIG_RA_PLL2R_DIV == RA_CLOCKS_PLL_DIV_1
#  define RA_PLL2R_FREQUENCY          (RA_PLL2_FREQUENCY)
#elif CONFIG_RA_PLL2R_DIV == RA_CLOCKS_PLL_DIV_2
#  define RA_PLL2R_FREQUENCY          ((RA_PLL2_FREQUENCY) / 2UL)
#elif CONFIG_RA_PLL2R_DIV == RA_CLOCKS_PLL_DIV_3
#  define RA_PLL2R_FREQUENCY          ((RA_PLL2_FREQUENCY) / 3UL)
#elif CONFIG_RA_PLL2R_DIV == RA_CLOCKS_PLL_DIV_4
#  define RA_PLL2R_FREQUENCY          ((RA_PLL2_FREQUENCY) / 4UL)
#elif CONFIG_RA_PLL2R_DIV == RA_CLOCKS_PLL_DIV_5
#  define RA_PLL2R_FREQUENCY          ((RA_PLL2_FREQUENCY) / 5UL)
#elif CONFIG_RA_PLL2R_DIV == RA_CLOCKS_PLL_DIV_6
#  define RA_PLL2R_FREQUENCY          ((RA_PLL2_FREQUENCY) / 6UL)
#elif CONFIG_RA_PLL2R_DIV == RA_CLOCKS_PLL_DIV_8
#  define RA_PLL2R_FREQUENCY          ((RA_PLL2_FREQUENCY) / 8UL)
#elif CONFIG_RA_PLL2R_DIV == RA_CLOCKS_PLL_DIV_9
#  define RA_PLL2R_FREQUENCY          ((RA_PLL2_FREQUENCY) / 9UL)
#elif CONFIG_RA_PLL2R_DIV == RA_CLOCKS_PLL_DIV_1_5
#  define RA_PLL2R_FREQUENCY          (((RA_PLL2_FREQUENCY) * 2UL) / 3UL)
#else
#  define RA_PLL2R_FREQUENCY          ((RA_PLL2_FREQUENCY) / 5UL)
#endif

/* Frequency definitions (derived from calculations above) */
#define CONFIG_RA_PLL1P_FREQUENCY_HZ     RA_PLL1P_FREQUENCY
#define CONFIG_RA_PLL1Q_FREQUENCY_HZ     RA_PLL1Q_FREQUENCY
#define CONFIG_RA_PLL1R_FREQUENCY_HZ     RA_PLL1R_FREQUENCY

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

/* Note: CONFIG_RA_*_DIV defaults are defined in the profile-based section above */

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
#define RA_PCLKE_FREQUENCY             (RA_SYSTEM_CLOCK_FREQUENCY / RA_DIV_TO_DIVISOR(CONFIG_RA_PCKE_DIV))
#define RA_BCLK_FREQUENCY              (RA_SYSTEM_CLOCK_FREQUENCY / RA_DIV_TO_DIVISOR(CONFIG_RA_BCLK_DIV))
#define RA_FCLK_FREQUENCY              (RA_SYSTEM_CLOCK_FREQUENCY / RA_DIV_TO_DIVISOR(CONFIG_RA_FCLK_DIV))


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

#define RA_STARTUP_SOURCE_CLOCK_HZ    (CONFIG_RA_PLL1P_FREQUENCY_HZ)

/* Convert divisor bitfield settings into divisor values to calculate startup clocks */
#define RA_PRV_SCKDIVCR_DIV_VALUE(div)    (((div) & 8U) ? (3U << ((div) & ~8U)) : (1U << (div)))

/* PLL2 Frequency Aliases - use the calculated frequencies */
#define CONFIG_RA_PLL2_FREQUENCY_HZ      RA_PLL2_FREQUENCY
#define CONFIG_RA_PL2ODIVP               CONFIG_RA_PLL2P_DIV
#define CONFIG_RA_PLL2P_FREQUENCY_HZ     RA_PLL2P_FREQUENCY
#define CONFIG_RA_PL2ODIVQ               CONFIG_RA_PLL2Q_DIV
#define CONFIG_RA_PLL2Q_FREQUENCY_HZ     RA_PLL2Q_FREQUENCY
#define CONFIG_RA_PL2ODIVR               CONFIG_RA_PLL2R_DIV
#define CONFIG_RA_PLL2R_FREQUENCY_HZ     RA_PLL2R_FREQUENCY

/* System Clock Configuration - Map Kconfig names to internal names */
/* Note: CONFIG_RA_CPUCLK_DIV, CONFIG_RA_BCLK_DIV, CONFIG_RA_FCLK_DIV come from Kconfig */

/* Define clock source based on Kconfig selection */
#if defined(CONFIG_RA_CLOCK_PLL1P) || defined(CONFIG_RA_CLOCK_PLL)
#  define CONFIG_RA_CLOCK_SOURCE         RA_CLOCKS_SOURCE_CLOCK_PLL1P
#elif defined(CONFIG_RA_CLOCK_HOCO)
#  define CONFIG_RA_CLOCK_SOURCE         RA_CLOCKS_SOURCE_CLOCK_HOCO
#elif defined(CONFIG_RA_CLOCK_MOCO)
#  define CONFIG_RA_CLOCK_SOURCE         RA_CLOCKS_SOURCE_CLOCK_MOCO
#elif defined(CONFIG_RA_CLOCK_MAIN)
#  define CONFIG_RA_CLOCK_SOURCE         RA_CLOCKS_SOURCE_CLOCK_MAIN_OSC
#else
#  define CONFIG_RA_CLOCK_SOURCE         RA_CLOCKS_SOURCE_CLOCK_PLL1P
#endif

/* Map Kconfig divider names to alternate naming convention used by some code */
#define CONFIG_RA_ICLK_DIV               CONFIG_RA_ICK_DIV
#define CONFIG_RA_PCLKA_DIV              CONFIG_RA_PCKA_DIV
#define CONFIG_RA_PCLKB_DIV              CONFIG_RA_PCKB_DIV
#define CONFIG_RA_PCLKC_DIV              CONFIG_RA_PCKC_DIV
#define CONFIG_RA_PCLKD_DIV              CONFIG_RA_PCKD_DIV
#define CONFIG_RA_PCLKE_DIV              CONFIG_RA_PCKE_DIV

/* RA8P1-specific clocks - provide defaults if not defined in Kconfig */
#ifndef CONFIG_RA_CPUCLK1_DIV
#  define CONFIG_RA_CPUCLK1_DIV          RA_CLOCKS_SYS_CLOCK_DIV_4
#endif
#ifndef CONFIG_RA_NPUCLK_DIV
#  define CONFIG_RA_NPUCLK_DIV           RA_CLOCKS_SYS_CLOCK_DIV_2
#endif
#ifndef CONFIG_RA_MRICLK_DIV
#  define CONFIG_RA_MRICLK_DIV           RA_CLOCKS_SYS_CLOCK_DIV_4
#endif

/* External Bus Configuration */
#define CONFIG_RA_BCLKA_SOURCE           RA_CLOCKS_SOURCE_CLOCK_PLL2Q
#define CONFIG_RA_BCLKA_DIV              RA_CLOCKS_BCLKA_CLOCK_DIV_6
#define CONFIG_RA_SDCLK_OUTPUT           (1)
#define CONFIG_RA_EBCLKA_SEL             (0)
#define CONFIG_RA_BCLK_OUTPUT            (2)

/* Clock Output Configuration */
#define CONFIG_RA_CLKOUT_SOURCE          RA_CLOCKS_SOURCE_CLOCK_HOCO
#define CONFIG_RA_CLKOUT_DIV             RA_CLOCKS_SYS_CLOCK_DIV_1

/* Peripheral Clock Configuration - derived from CONFIG_RA_* where available */
#ifndef CONFIG_RA_SCICLK_SOURCE
#  define CONFIG_RA_SCICLK_SOURCE     RA_CLOCKS_SOURCE_CLOCK_PLL2R
#endif
#ifndef CONFIG_RA_SPICLK_SOURCE
#  define CONFIG_RA_SPICLK_SOURCE     RA_CLOCKS_SOURCE_CLOCK_PLL1Q
#endif
#ifndef CONFIG_RA_CANFDCLK_SOURCE
#  define CONFIG_RA_CANFDCLK_SOURCE   RA_CLOCKS_SOURCE_CLOCK_PLL2R
#endif
#ifndef CONFIG_RA_GPTCLK_SOURCE
#  define CONFIG_RA_GPTCLK_SOURCE     RA_CLOCKS_SOURCE_CLOCK_PLL2P
#endif
#ifndef CONFIG_RA_LCDCLK_SOURCE
#  define CONFIG_RA_LCDCLK_SOURCE     RA_CLOCKS_SOURCE_CLOCK_PLL2R
#endif
#ifndef CONFIG_RA_LCDCLK_DIV
#  define CONFIG_RA_LCDCLK_DIV        RA_CLOCKS_LCD_CLOCK_DIV_2
#endif
#ifndef CONFIG_RA_I3CCLK_SOURCE
#  define CONFIG_RA_I3CCLK_SOURCE     RA_CLOCKS_SOURCE_CLOCK_PLL2Q
#endif
#ifndef CONFIG_RA_I3CCLK_DIV
#  define CONFIG_RA_I3CCLK_DIV        RA_CLOCKS_I3C_CLOCK_DIV_4
#endif
#ifndef CONFIG_RA_USBCLK_SOURCE
#  define CONFIG_RA_USBCLK_SOURCE     RA_CLOCKS_SOURCE_CLOCK_PLL2R
#endif
#ifndef CONFIG_RA_USB60CLK_SOURCE
#  define CONFIG_RA_USB60CLK_SOURCE   RA_CLOCKS_SOURCE_CLOCK_PLL2R
#endif
#ifndef CONFIG_RA_USB60CLK_DIV
#  define CONFIG_RA_USB60CLK_DIV      RA_CLOCKS_USB60_CLOCK_DIV_8
#endif
#ifndef CONFIG_RA_OCTACLK_SOURCE
#  define CONFIG_RA_OCTACLK_SOURCE    RA_CLOCKS_SOURCE_CLOCK_PLL1Q
#endif
#ifndef CONFIG_RA_ADCCLK_SOURCE
#  define CONFIG_RA_ADCCLK_SOURCE     RA_CLOCKS_SOURCE_CLOCK_PLL2R
#endif
#ifndef CONFIG_RA_ESWCLK_SOURCE
#  define CONFIG_RA_ESWCLK_SOURCE     RA_CLOCKS_SOURCE_CLOCK_PLL1P
#endif
#ifndef CONFIG_RA_ESWCLK_DIV
#  define CONFIG_RA_ESWCLK_DIV        RA_CLOCKS_ESW_CLOCK_DIV_4
#endif
#ifndef CONFIG_RA_ESWPHYCLK_SOURCE
#  define CONFIG_RA_ESWPHYCLK_SOURCE  RA_CLOCKS_SOURCE_CLOCK_PLL1P
#endif
#ifndef CONFIG_RA_ESWPHYCLK_DIV
#  define CONFIG_RA_ESWPHYCLK_DIV     RA_CLOCKS_ESWPHY_CLOCK_DIV_2
#endif
#ifndef CONFIG_RA_ETHPHYCLK_SOURCE
#  define CONFIG_RA_ETHPHYCLK_SOURCE  RA_CLOCKS_SOURCE_CLOCK_PLL2Q
#endif
#ifndef CONFIG_RA_ETHPHYCLK_DIV
#  define CONFIG_RA_ETHPHYCLK_DIV     RA_CLOCKS_ETHPHY_CLOCK_DIV_32
#endif

/* Peripheral clock macros - Aliases for alternate naming conventions */
/* Note: CONFIG_RA_*_SOURCE and CONFIG_RA_*_DIV values come from Kconfig defaults above */
#define CONFIG_RA_GPT_COUNT_CLOCK_SOURCE (1)
#define CONFIG_RA_UCLK_SOURCE            CONFIG_RA_USBCLK_SOURCE
#define CONFIG_RA_UCLK_DIV               CONFIG_RA_USBCLK_DIV

/* Derived Divider Values for Startup Calculations */
#define RA_PRV_CPUCLK_DIV_VALUE       RA_PRV_SCKDIVCR_DIV_VALUE(CONFIG_RA_CPUCLK_DIV)
#define RA_PRV_ICLK_DIV_VALUE         RA_PRV_SCKDIVCR_DIV_VALUE(CONFIG_RA_ICLK_DIV)
#define RA_PRV_PCLKA_DIV_VALUE        RA_PRV_SCKDIVCR_DIV_VALUE(CONFIG_RA_PCLKA_DIV)
#define RA_PRV_PCLKB_DIV_VALUE        RA_PRV_SCKDIVCR_DIV_VALUE(CONFIG_RA_PCLKB_DIV)
#define RA_PRV_PCLKC_DIV_VALUE        RA_PRV_SCKDIVCR_DIV_VALUE(CONFIG_RA_PCLKC_DIV)
#define RA_PRV_PCLKD_DIV_VALUE        RA_PRV_SCKDIVCR_DIV_VALUE(CONFIG_RA_PCLKD_DIV)
#define RA_PRV_PCLKE_DIV_VALUE        RA_PRV_SCKDIVCR_DIV_VALUE(CONFIG_RA_PCLKE_DIV)
#define RA_PRV_BCLK_DIV_VALUE         RA_PRV_SCKDIVCR_DIV_VALUE(CONFIG_RA_BCLK_DIV)
#define RA_PRV_FCLK_DIV_VALUE         RA_PRV_SCKDIVCR_DIV_VALUE(CONFIG_RA_FCLK_DIV)
#define RA_PRV_MRICLK_DIV_VALUE       RA_PRV_SCKDIVCR_DIV_VALUE(CONFIG_RA_MRICLK_DIV)

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

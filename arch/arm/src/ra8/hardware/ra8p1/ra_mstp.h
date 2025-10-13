/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_mstp.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MSTP_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MSTP_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* MSTP Base Address */
#ifndef R_MSTP_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_MSTP_BASE           0x40203000
#else
#define R_MSTP_BASE           0x50203000
#endif
#endif

/* MSTP Register Offsets */

#define R_MSTP_MSTPCRA_OFFSET                     0x00000000  /* Module Stop Control Register A */
#define R_MSTP_MSTPCRB_OFFSET                     0x00000004  /* Module Stop Control Register B */
#define R_MSTP_MSTPCRC_OFFSET                     0x00000008  /* Module Stop Control Register C */
#define R_MSTP_MSTPCRD_OFFSET                     0x0000000c  /* Module Stop Control Register D */
#define R_MSTP_MSTPCRE_OFFSET                     0x00000010  /* Module Stop Control Register E */

/* MSTP Register Addresses */

#define R_MSTP_MSTPCRA                            (R_MSTP_BASE + R_MSTP_MSTPCRA_OFFSET)
#define R_MSTP_MSTPCRB                            (R_MSTP_BASE + R_MSTP_MSTPCRB_OFFSET)
#define R_MSTP_MSTPCRC                            (R_MSTP_BASE + R_MSTP_MSTPCRC_OFFSET)
#define R_MSTP_MSTPCRD                            (R_MSTP_BASE + R_MSTP_MSTPCRD_OFFSET)
#define R_MSTP_MSTPCRE                            (R_MSTP_BASE + R_MSTP_MSTPCRE_OFFSET)

/* Register bit definitions */
/* MSTPCRA Register bit definitions */
#define R_MSTP_MSTPCRA_MSTPA0                     (1 << 0)  /* SRAM0 Module Stop */

#define R_MSTP_MSTPCRA_MSTPA1                     (1 << 1)  /* SRAM1 Module Stop */

#define R_MSTP_MSTPCRA_MSTPA2                     (1 << 2)  /* SRAM2 Module Stop */

#define R_MSTP_MSTPCRA_MSTPA3                     (1 << 3)  /* SRAM3 Module Stop */

#define R_MSTP_MSTPCRA_MSTPA16                    (1 << 16)  /* NPU Module Stop */

#define R_MSTP_MSTPCRA_MSTPA22                    (1 << 22)  /* DMA Controller 0 and Data Transfer Controller 0 Module Stop */

#define R_MSTP_MSTPCRA_MSTPA23                    (1 << 23)  /* DMA Controller 1 and Data Transfer Controller 1 Module Stop */

#define R_MSTP_MSTPCRA_MSTPA4                     (1 << 4)  /* Module stop bit 4. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA5                     (1 << 5)  /* Module stop bit 5. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA6                     (1 << 6)  /* Module stop bit 6. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA7                     (1 << 7)  /* Module stop bit 7. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA8                     (1 << 8)  /* Module stop bit 8. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA9                     (1 << 9)  /* Module stop bit 9. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA10                    (1 << 10)  /* Module stop bit 10. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA11                    (1 << 11)  /* Module stop bit 11. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA12                    (1 << 12)  /* Module stop bit 12. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA13                    (1 << 13)  /* Module stop bit 13. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA14                    (1 << 14)  /* Module stop bit 14. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA15                    (1 << 15)  /* Module stop bit 15. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA17                    (1 << 17)  /* Module stop bit 17. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA18                    (1 << 18)  /* Module stop bit 18. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA19                    (1 << 19)  /* Module stop bit 19. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA20                    (1 << 20)  /* Module stop bit 20. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA21                    (1 << 21)  /* Module stop bit 21. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA24                    (1 << 24)  /* Module stop bit 24. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA25                    (1 << 25)  /* Module stop bit 25. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA26                    (1 << 26)  /* Module stop bit 26. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA27                    (1 << 27)  /* Module stop bit 27. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA28                    (1 << 28)  /* Module stop bit 28. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA29                    (1 << 29)  /* Module stop bit 29. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA30                    (1 << 30)  /* Module stop bit 30. See device hardware manual for usage. */

#define R_MSTP_MSTPCRA_MSTPA31                    (1 << 31)  /* Module stop bit 31. See device hardware manual for usage. */

/* MSTPCRB Register bit definitions */
#define R_MSTP_MSTPCRB_MSTPB4                     (1 << 4)  /* I3C Bus Interface Module Stop */

#define R_MSTP_MSTPCRB_MSTPB7                     (1 << 7)  /* IIC Bus Interface 2 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB8                     (1 << 8)  /* IIC Bus Interface 1 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB9                     (1 << 9)  /* IIC Bus Interface 0 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB11                    (1 << 11)  /* Universal Serial Bus 2.0 FS Interface 0 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB12                    (1 << 12)  /* Universal Serial Bus 2.0 HS Interface Module Stop */

#define R_MSTP_MSTPCRB_MSTPB16                    (1 << 16)  /* Octal Serial Peripheral Interface 0 and Decryption On The Fly 0 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB17                    (1 << 17)  /* Octal Serial Peripheral Interface 1 and Decryption On The Fly 1 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB18                    (1 << 18)  /* Serial Peripheral Interface 1 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB19                    (1 << 19)  /* Serial Peripheral Interface 0 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB22                    (1 << 22)  /* Serial Communication Interface 9 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB23                    (1 << 23)  /* Serial Communication Interface 8 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB24                    (1 << 24)  /* Serial Communication Interface 7 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB25                    (1 << 25)  /* Serial Communication Interface 6 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB26                    (1 << 26)  /* Serial Communication Interface 5 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB27                    (1 << 27)  /* Serial Communication Interface 4 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB28                    (1 << 28)  /* Serial Communication Interface 3 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB29                    (1 << 29)  /* Serial Communication Interface 2 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB30                    (1 << 30)  /* Serial Communication Interface 1 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB31                    (1 << 31)  /* Serial Communication Interface 0 Module Stop */

#define R_MSTP_MSTPCRB_MSTPB0                     (1 << 0)  /* Module stop bit 0. See device hardware manual for usage. */

#define R_MSTP_MSTPCRB_MSTPB1                     (1 << 1)  /* Module stop bit 1. See device hardware manual for usage. */

#define R_MSTP_MSTPCRB_MSTPB2                     (1 << 2)  /* Module stop bit 2. See device hardware manual for usage. */

#define R_MSTP_MSTPCRB_MSTPB3                     (1 << 3)  /* Module stop bit 3. See device hardware manual for usage. */

#define R_MSTP_MSTPCRB_MSTPB5                     (1 << 5)  /* Module stop bit 5. See device hardware manual for usage. */

#define R_MSTP_MSTPCRB_MSTPB6                     (1 << 6)  /* Module stop bit 6. See device hardware manual for usage. */

#define R_MSTP_MSTPCRB_MSTPB10                    (1 << 10)  /* Module stop bit 10. See device hardware manual for usage. */

#define R_MSTP_MSTPCRB_MSTPB13                    (1 << 13)  /* Module stop bit 13. See device hardware manual for usage. */

#define R_MSTP_MSTPCRB_MSTPB14                    (1 << 14)  /* Module stop bit 14. See device hardware manual for usage. */

#define R_MSTP_MSTPCRB_MSTPB15                    (1 << 15)  /* Module stop bit 15. See device hardware manual for usage. */

#define R_MSTP_MSTPCRB_MSTPB20                    (1 << 20)  /* Module stop bit 20. See device hardware manual for usage. */

#define R_MSTP_MSTPCRB_MSTPB21                    (1 << 21)  /* Module stop bit 21. See device hardware manual for usage. */

/* MSTPCRC Register bit definitions */
#define R_MSTP_MSTPCRC_MSTPC0                     (1 << 0)  /* Clock Frequency Accuracy Measurement Circuit Module Stop */

#define R_MSTP_MSTPCRC_MSTPC1                     (1 << 1)  /* Cyclic Redundancy Check Calculator Module Stop */

#define R_MSTP_MSTPCRC_MSTPC4                     (1 << 4)  /* Graphics LCD Controller Module Stop */

#define R_MSTP_MSTPCRC_MSTPC6                     (1 << 6)  /* 2D Drawing Engine Module Stop */

#define R_MSTP_MSTPCRC_MSTPC7                     (1 << 7)  /* Serial Sound Interface Enhanced 1 Module Stop */

#define R_MSTP_MSTPCRC_MSTPC8                     (1 << 8)  /* Serial Sound Interface Enhanced 0 Module Stop */

#define R_MSTP_MSTPCRC_MSTPC10                    (1 << 10)  /* MIPI Display Serial Interface Module Stop */

#define R_MSTP_MSTPCRC_MSTPC11                    (1 << 11)  /* Secure Digital Host IF 1 Module Stop */

#define R_MSTP_MSTPCRC_MSTPC12                    (1 << 12)  /* Secure Digital Host IF 0 Module Stop */

#define R_MSTP_MSTPCRC_MSTPC13                    (1 << 13)  /* Data Operation Circuit Module Stop */

#define R_MSTP_MSTPCRC_MSTPC14                    (1 << 14)  /* Event Link Controller Module Stop */

#define R_MSTP_MSTPCRC_MSTPC16                    (1 << 16)  /* Capture Engine Unit Module Stop */

#define R_MSTP_MSTPCRC_MSTPC17                    (1 << 17)  /* MIPI Camera Serial Interface Module Stop */

#define R_MSTP_MSTPCRC_MSTPC24                    (1 << 24)  /* Pulse Density Modulation Interface Module Stop */

#define R_MSTP_MSTPCRC_MSTPC26                    (1 << 26)  /* Controller Area Network with Flexible Data-Rate 1 Module Stop */

#define R_MSTP_MSTPCRC_MSTPC27                    (1 << 27)  /* Controller Area Network with Flexible Data-Rate 0 Module Stop */

#define R_MSTP_MSTPCRC_MSTPC28                    (1 << 28)  /* Ether-PHY clock Module Stop */

#define R_MSTP_MSTPCRC_MSTPC30                    (1 << 30)  /* Layer 3 Ethernet Switch Module Module Stop */

#define R_MSTP_MSTPCRC_MSTPC31                    (1 << 31)  /* Renesas Secure IP Module Stop */

#define R_MSTP_MSTPCRC_MSTPC2                     (1 << 2)  /* Module stop bit 2. See device hardware manual for usage. */

#define R_MSTP_MSTPCRC_MSTPC3                     (1 << 3)  /* Module stop bit 3. See device hardware manual for usage. */

#define R_MSTP_MSTPCRC_MSTPC5                     (1 << 5)  /* Module stop bit 5. See device hardware manual for usage. */

#define R_MSTP_MSTPCRC_MSTPC9                     (1 << 9)  /* Module stop bit 9. See device hardware manual for usage. */

#define R_MSTP_MSTPCRC_MSTPC15                    (1 << 15)  /* Module stop bit 15. See device hardware manual for usage. */

#define R_MSTP_MSTPCRC_MSTPC18                    (1 << 18)  /* Module stop bit 18. See device hardware manual for usage. */

#define R_MSTP_MSTPCRC_MSTPC19                    (1 << 19)  /* Module stop bit 19. See device hardware manual for usage. */

#define R_MSTP_MSTPCRC_MSTPC20                    (1 << 20)  /* Module stop bit 20. See device hardware manual for usage. */

#define R_MSTP_MSTPCRC_MSTPC21                    (1 << 21)  /* Module stop bit 21. See device hardware manual for usage. */

#define R_MSTP_MSTPCRC_MSTPC22                    (1 << 22)  /* Module stop bit 22. See device hardware manual for usage. */

#define R_MSTP_MSTPCRC_MSTPC23                    (1 << 23)  /* Module stop bit 23. See device hardware manual for usage. */

#define R_MSTP_MSTPCRC_MSTPC25                    (1 << 25)  /* Module stop bit 25. See device hardware manual for usage. */

#define R_MSTP_MSTPCRC_MSTPC29                    (1 << 29)  /* Module stop bit 29. See device hardware manual for usage. */

/* MSTPCRD Register bit definitions */
#define R_MSTP_MSTPCRD_MSTPD4                     (1 << 4)  /* Low power Asynchronous General Purpose Timer 1 Module Stop */

#define R_MSTP_MSTPCRD_MSTPD5                     (1 << 5)  /* Low power Asynchronous General Purpose Timer 0 Module Stop */

#define R_MSTP_MSTPCRD_MSTPD6                     (1 << 6)  /* PWM Delay Generation Circuit Module Stop */

#define R_MSTP_MSTPCRD_MSTPD11                    (1 << 11)  /* Port Output Enable for GPT Group D Module Stop */

#define R_MSTP_MSTPCRD_MSTPD12                    (1 << 12)  /* Port Output Enable for GPT Group C Module Stop */

#define R_MSTP_MSTPCRD_MSTPD13                    (1 << 13)  /* Port Output Enable for GPT Group B Module Stop */

#define R_MSTP_MSTPCRD_MSTPD14                    (1 << 14)  /* Port Output Enable for GPT Group A Module Stop */

#define R_MSTP_MSTPCRD_MSTPD19                    (1 << 19)  /* 12-bit D/A Converter 1 Module Stop */

#define R_MSTP_MSTPCRD_MSTPD20                    (1 << 20)  /* 12-bit D/A Converter 0 Module Stop */

#define R_MSTP_MSTPCRD_MSTPD21                    (1 << 21)  /* 16-Bit A/D Converter Module Stop */

#define R_MSTP_MSTPCRD_MSTPD22                    (1 << 22)  /* Temperature Sensor Module Stop */

#define R_MSTP_MSTPCRD_MSTPD25                    (1 << 25)  /* High-Speed Analog Comparator 3 Module Stop */

#define R_MSTP_MSTPCRD_MSTPD26                    (1 << 26)  /* High-Speed Analog Comparator 2 Module Stop */

#define R_MSTP_MSTPCRD_MSTPD27                    (1 << 27)  /* High-Speed Analog Comparator 1 Module Stop */

#define R_MSTP_MSTPCRD_MSTPD28                    (1 << 28)  /* High-Speed Analog Comparator 0 Module Stop */

#define R_MSTP_MSTPCRD_MSTPD0                     (1 << 0)  /* Module stop bit 0. See device hardware manual for usage. */

#define R_MSTP_MSTPCRD_MSTPD1                     (1 << 1)  /* Module stop bit 1. See device hardware manual for usage. */

#define R_MSTP_MSTPCRD_MSTPD2                     (1 << 2)  /* Module stop bit 2. See device hardware manual for usage. */

#define R_MSTP_MSTPCRD_MSTPD3                     (1 << 3)  /* Module stop bit 3. See device hardware manual for usage. */

#define R_MSTP_MSTPCRD_MSTPD7                     (1 << 7)  /* Module stop bit 7. See device hardware manual for usage. */

#define R_MSTP_MSTPCRD_MSTPD8                     (1 << 8)  /* Module stop bit 8. See device hardware manual for usage. */

#define R_MSTP_MSTPCRD_MSTPD9                     (1 << 9)  /* Module stop bit 9. See device hardware manual for usage. */

#define R_MSTP_MSTPCRD_MSTPD10                    (1 << 10)  /* Module stop bit 10. See device hardware manual for usage. */

#define R_MSTP_MSTPCRD_MSTPD15                    (1 << 15)  /* Module stop bit 15. See device hardware manual for usage. */

#define R_MSTP_MSTPCRD_MSTPD16                    (1 << 16)  /* Module stop bit 16. See device hardware manual for usage. */

#define R_MSTP_MSTPCRD_MSTPD17                    (1 << 17)  /* Module stop bit 17. See device hardware manual for usage. */

#define R_MSTP_MSTPCRD_MSTPD18                    (1 << 18)  /* Module stop bit 18. See device hardware manual for usage. */

#define R_MSTP_MSTPCRD_MSTPD23                    (1 << 23)  /* Module stop bit 23. See device hardware manual for usage. */

#define R_MSTP_MSTPCRD_MSTPD24                    (1 << 24)  /* Module stop bit 24. See device hardware manual for usage. */

#define R_MSTP_MSTPCRD_MSTPD29                    (1 << 29)  /* Module stop bit 29. See device hardware manual for usage. */

#define R_MSTP_MSTPCRD_MSTPD30                    (1 << 30)  /* Module stop bit 30. See device hardware manual for usage. */

#define R_MSTP_MSTPCRD_MSTPD31                    (1 << 31)  /* Module stop bit 31. See device hardware manual for usage. */

/* MSTPCRE Register bit definitions */
#define R_MSTP_MSTPCRE_MSTPE8                     (1 << 8)  /* Ultra-Low Power Timer 1 Module Stop */

#define R_MSTP_MSTPCRE_MSTPE9                     (1 << 9)  /* Ultra-Low Power Timer 0 Module Stop */

#define R_MSTP_MSTPCRE_MSTPE18                    (1 << 18)  /* General PWM Timer 13 Module Stop */

#define R_MSTP_MSTPCRE_MSTPE19                    (1 << 19)  /* General PWM Timer 12 Module Stop */

#define R_MSTP_MSTPCRE_MSTPE20                    (1 << 20)  /* General PWM Timer 11 Module Stop */

#define R_MSTP_MSTPCRE_MSTPE21                    (1 << 21)  /* General PWM Timer 10 Module Stop */

#define R_MSTP_MSTPCRE_MSTPE27                    (1 << 27)  /* General PWM Timer 4-9 Module Stop */

#define R_MSTP_MSTPCRE_MSTPE28                    (1 << 28)  /* General PWM Timer 3 Module Stop */

#define R_MSTP_MSTPCRE_MSTPE29                    (1 << 29)  /* General PWM Timer 2 Module Stop */

#define R_MSTP_MSTPCRE_MSTPE30                    (1 << 30)  /* General PWM Timer 1 Module Stop */

#define R_MSTP_MSTPCRE_MSTPE31                    (1 << 31)  /* General PWM Timer 0 Module Stop */

#define R_MSTP_MSTPCRE_MSTPE0                     (1 << 0)  /* Module stop bit 0. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE1                     (1 << 1)  /* Module stop bit 1. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE2                     (1 << 2)  /* Module stop bit 2. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE3                     (1 << 3)  /* Module stop bit 3. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE4                     (1 << 4)  /* Module stop bit 4. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE5                     (1 << 5)  /* Module stop bit 5. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE6                     (1 << 6)  /* Module stop bit 6. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE7                     (1 << 7)  /* Module stop bit 7. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE10                    (1 << 10)  /* Module stop bit 10. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE11                    (1 << 11)  /* Module stop bit 11. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE12                    (1 << 12)  /* Module stop bit 12. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE13                    (1 << 13)  /* Module stop bit 13. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE14                    (1 << 14)  /* Module stop bit 14. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE15                    (1 << 15)  /* Module stop bit 15. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE16                    (1 << 16)  /* Module stop bit 16. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE17                    (1 << 17)  /* Module stop bit 17. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE22                    (1 << 22)  /* Module stop bit 22. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE23                    (1 << 23)  /* Module stop bit 23. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE24                    (1 << 24)  /* Module stop bit 24. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE25                    (1 << 25)  /* Module stop bit 25. See device hardware manual for usage. */

#define R_MSTP_MSTPCRE_MSTPE26                    (1 << 26)  /* Module stop bit 26. See device hardware manual for usage. */


/* Maximum number of channels */

#define MSTP_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MSTP_H */

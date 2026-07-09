/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_intc.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_INTC_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_INTC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* INTC Base Addresses ***************************************************/

#ifndef RZV_INTC0_BASE
#  define RZV_INTC0_BASE              0x10400000
#endif
#ifndef RZV_INTC_BASE
#  define RZV_INTC_BASE               RZV_INTC0_BASE
#endif

/* INTC Register Offsets **************************************************/

/* BEISR%s Registers (0-3) */
#define RZV_INTC_BEISR_OFFSET(m)                (0x0000006c + ((m) * 0x00000004))  /* BEISR Register %s */
/* DMACKSEL%s Registers (0-22) */
#define RZV_INTC_DMACKSEL_OFFSET(m)             (0x000004bc + ((m) * 0x00000004))  /* DMACKSEL Register %s */
/* DMESR%s Registers (0-2) */
#define RZV_INTC_DMESR_OFFSET(m)                (0x0000052c + ((m) * 0x00000004))  /* DMESR Register %s */
/* DMRCTR%s Registers (0-2) */
#define RZV_INTC_DMRCTR_OFFSET(m)               (0x00000488 + ((m) * 0x00000004))  /* DMRCTR Register %s */
/* DMTENDSEL%s Registers (0-1) */
#define RZV_INTC_DMTENDSEL_OFFSET(m)            (0x00000518 + ((m) * 0x00000004))  /* DMTENDSEL Register %s */
/* ERCLR%s Registers (0-11) */
#define RZV_INTC_ERCLR_OFFSET(m)                (0x000000cc + ((m) * 0x00000004))  /* ERCLR Register %s */
/* EREISR%s Registers (0-11) */
#define RZV_INTC_EREISR_OFFSET(m)               (0x0000007c + ((m) * 0x00000004))  /* EREISR Register %s */
/* EVTSEL%s Registers (0-14) */
#define RZV_INTC_EVTSEL_OFFSET(m)               (0x000005c0 + ((m) * 0x00000004))  /* EVTSEL Register %s */
/* OFFDMSTAT%s Registers (0-2) */
#define RZV_INTC_OFFDMSTAT_OFFSET(m)            (0x0000073c + ((m) * 0x00000004))  /* OFFDMSTAT Register %s */
/* SWDMAC%s Registers (0-4) */
#define RZV_INTC_SWDMAC_OFFSET(m)               (0x000003c8 + ((m) * 0x00000004))  /* SWDMAC Register %s */
/* TITSR%s Registers (0-1) */
#define RZV_INTC_TITSR_OFFSET(m)                (0x00000024 + ((m) * 0x00000004))  /* TITSR Register %s */
/* TSSR%s Registers (0-7) */
#define RZV_INTC_TSSR_OFFSET(m)                 (0x0000002c + ((m) * 0x00000004))  /* TSSR Register %s */
#define RZV_INTC_NSCNT_OFFSET                            0x0000  /* NSCNT */
#define RZV_INTC_NSCLR_OFFSET                            0x0004  /* NSCLR */
#define RZV_INTC_NITSR_OFFSET                            0x0008  /* NITSR */
#define RZV_INTC_ISCTR_OFFSET                            0x0010  /* ISCTR */
#define RZV_INTC_ISCLR_OFFSET                            0x0014  /* ISCLR */
#define RZV_INTC_IITSR_OFFSET                            0x0018  /* IITSR */
#define RZV_INTC_TSCTR_OFFSET                            0x0020  /* TSCTR */
#define RZV_INTC_DRCTR_OFFSET                            0x004C  /* DRCTR */
#define RZV_INTC_DRCLR_OFFSET                            0x0050  /* DRCLR */
#define RZV_INTC_DRTSR_OFFSET                            0x0054  /* DRTSR */
#define RZV_INTC_IPTSR_OFFSET                            0x005C  /* IPTSR */
#define RZV_INTC_SWINT_OFFSET                            0x011C  /* SWINT */
#define RZV_INTC_INTR8SEL0_OFFSET                        0x012C  /* INTR8SEL0 */
#define RZV_INTC_INTR8SEL1_OFFSET                        0x0130  /* INTR8SEL1 */
#define RZV_INTC_INTR8SEL2_OFFSET                        0x0134  /* INTR8SEL2 */
#define RZV_INTC_INTR8SEL3_OFFSET                        0x0138  /* INTR8SEL3 */
#define RZV_INTC_INTR8SEL4_OFFSET                        0x013C  /* INTR8SEL4 */
#define RZV_INTC_INTR8SEL5_OFFSET                        0x0140  /* INTR8SEL5 */
#define RZV_INTC_INTR8SEL6_OFFSET                        0x0144  /* INTR8SEL6 */
#define RZV_INTC_INTR8SEL7_OFFSET                        0x0148  /* INTR8SEL7 */
#define RZV_INTC_INTR8SEL8_OFFSET                        0x014C  /* INTR8SEL8 */
#define RZV_INTC_INTR8SEL9_OFFSET                        0x0150  /* INTR8SEL9 */
#define RZV_INTC_INTR8SEL10_OFFSET                       0x0154  /* INTR8SEL10 */
#define RZV_INTC_INTR8SEL11_OFFSET                       0x0158  /* INTR8SEL11 */
#define RZV_INTC_INTR8SEL12_OFFSET                       0x015C  /* INTR8SEL12 */
#define RZV_INTC_INTR8SEL13_OFFSET                       0x0160  /* INTR8SEL13 */
#define RZV_INTC_INTR8SEL14_OFFSET                       0x0164  /* INTR8SEL14 */
#define RZV_INTC_INTR8SEL15_OFFSET                       0x0168  /* INTR8SEL15 */
#define RZV_INTC_INTR8SEL16_OFFSET                       0x016C  /* INTR8SEL16 */
#define RZV_INTC_INTR8SEL17_OFFSET                       0x0170  /* INTR8SEL17 */
#define RZV_INTC_INTR8SEL18_OFFSET                       0x0174  /* INTR8SEL18 */
#define RZV_INTC_INTR8SEL19_OFFSET                       0x0178  /* INTR8SEL19 */
#define RZV_INTC_INTR8SEL20_OFFSET                       0x017C  /* INTR8SEL20 */
#define RZV_INTC_INTR8SEL21_OFFSET                       0x0180  /* INTR8SEL21 */
#define RZV_INTC_INTR8SEL22_OFFSET                       0x0184  /* INTR8SEL22 */
#define RZV_INTC_INTR8SEL23_OFFSET                       0x0188  /* INTR8SEL23 */
#define RZV_INTC_INTR8SEL24_OFFSET                       0x018C  /* INTR8SEL24 */
#define RZV_INTC_INTR8SEL25_OFFSET                       0x0190  /* INTR8SEL25 */
#define RZV_INTC_INTR8SEL26_OFFSET                       0x0194  /* INTR8SEL26 */
#define RZV_INTC_INTR8SEL27_OFFSET                       0x0198  /* INTR8SEL27 */
#define RZV_INTC_INTR8SEL28_OFFSET                       0x019C  /* INTR8SEL28 */
#define RZV_INTC_INTR8SEL29_OFFSET                       0x01A0  /* INTR8SEL29 */
#define RZV_INTC_INTR8SEL30_OFFSET                       0x01A4  /* INTR8SEL30 */
#define RZV_INTC_INTR8SEL31_OFFSET                       0x01A8  /* INTR8SEL31 */
#define RZV_INTC_INTR8SEL32_OFFSET                       0x01AC  /* INTR8SEL32 */
#define RZV_INTC_INTR8SEL33_OFFSET                       0x01B0  /* INTR8SEL33 */
#define RZV_INTC_INTR8SEL34_OFFSET                       0x01B4  /* INTR8SEL34 */
#define RZV_INTC_INTR8SEL35_OFFSET                       0x01B8  /* INTR8SEL35 */
#define RZV_INTC_INTR8SEL36_OFFSET                       0x01BC  /* INTR8SEL36 */
#define RZV_INTC_INTR8SEL37_OFFSET                       0x01C0  /* INTR8SEL37 */
#define RZV_INTC_INTR8SEL38_OFFSET                       0x01C4  /* INTR8SEL38 */
#define RZV_INTC_INTR8SEL39_OFFSET                       0x01C8  /* INTR8SEL39 */
#define RZV_INTC_INTR8SEL40_OFFSET                       0x01CC  /* INTR8SEL40 */
#define RZV_INTC_INTR8SEL41_OFFSET                       0x01D0  /* INTR8SEL41 */
#define RZV_INTC_INTR8SEL42_OFFSET                       0x01D4  /* INTR8SEL42 */
#define RZV_INTC_INTM33SEL0_OFFSET                       0x01EC  /* INTM33SEL0 */
#define RZV_INTC_INTM33SEL1_OFFSET                       0x01F0  /* INTM33SEL1 */
#define RZV_INTC_INTM33SEL2_OFFSET                       0x01F4  /* INTM33SEL2 */
#define RZV_INTC_INTM33SEL3_OFFSET                       0x01F8  /* INTM33SEL3 */
#define RZV_INTC_INTM33SEL4_OFFSET                       0x01FC  /* INTM33SEL4 */
#define RZV_INTC_INTM33SEL5_OFFSET                       0x0200  /* INTM33SEL5 */
#define RZV_INTC_INTM33SEL6_OFFSET                       0x0204  /* INTM33SEL6 */
#define RZV_INTC_INTM33SEL7_OFFSET                       0x0208  /* INTM33SEL7 */
#define RZV_INTC_INTM33SEL8_OFFSET                       0x020C  /* INTM33SEL8 */
#define RZV_INTC_INTM33SEL9_OFFSET                       0x0210  /* INTM33SEL9 */
#define RZV_INTC_INTM33SEL10_OFFSET                      0x0214  /* INTM33SEL10 */
#define RZV_INTC_INTM33SEL11_OFFSET                      0x0218  /* INTM33SEL11 */
#define RZV_INTC_INTM33SEL12_OFFSET                      0x021C  /* INTM33SEL12 */
#define RZV_INTC_INTM33SEL13_OFFSET                      0x0220  /* INTM33SEL13 */
#define RZV_INTC_INTM33SEL14_OFFSET                      0x0224  /* INTM33SEL14 */
#define RZV_INTC_INTM33SEL15_OFFSET                      0x0228  /* INTM33SEL15 */
#define RZV_INTC_INTM33SEL16_OFFSET                      0x022C  /* INTM33SEL16 */
#define RZV_INTC_INTM33SEL17_OFFSET                      0x0230  /* INTM33SEL17 */
#define RZV_INTC_INTM33SEL18_OFFSET                      0x0234  /* INTM33SEL18 */
#define RZV_INTC_INTM33SEL19_OFFSET                      0x0238  /* INTM33SEL19 */
#define RZV_INTC_INTM33SEL20_OFFSET                      0x023C  /* INTM33SEL20 */
#define RZV_INTC_INTM33SEL21_OFFSET                      0x0240  /* INTM33SEL21 */
#define RZV_INTC_INTM33SEL22_OFFSET                      0x0244  /* INTM33SEL22 */
#define RZV_INTC_INTM33SEL23_OFFSET                      0x0248  /* INTM33SEL23 */
#define RZV_INTC_INTM33SEL24_OFFSET                      0x024C  /* INTM33SEL24 */
#define RZV_INTC_INTM33SEL25_OFFSET                      0x0250  /* INTM33SEL25 */
#define RZV_INTC_INTM33SEL26_OFFSET                      0x0254  /* INTM33SEL26 */
#define RZV_INTC_INTM33SEL27_OFFSET                      0x0258  /* INTM33SEL27 */
#define RZV_INTC_INTM33SEL28_OFFSET                      0x025C  /* INTM33SEL28 */
#define RZV_INTC_INTM33SEL29_OFFSET                      0x0260  /* INTM33SEL29 */
#define RZV_INTC_INTM33SEL30_OFFSET                      0x0264  /* INTM33SEL30 */
#define RZV_INTC_INTM33SEL31_OFFSET                      0x0268  /* INTM33SEL31 */
#define RZV_INTC_INTM33SEL32_OFFSET                      0x026C  /* INTM33SEL32 */
#define RZV_INTC_INTM33SEL33_OFFSET                      0x0270  /* INTM33SEL33 */
#define RZV_INTC_INTM33SEL34_OFFSET                      0x0274  /* INTM33SEL34 */
#define RZV_INTC_INTM33SEL35_OFFSET                      0x0278  /* INTM33SEL35 */
#define RZV_INTC_INTM33SEL36_OFFSET                      0x027C  /* INTM33SEL36 */
#define RZV_INTC_INTM33SEL37_OFFSET                      0x0280  /* INTM33SEL37 */
#define RZV_INTC_INTM33SEL38_OFFSET                      0x0284  /* INTM33SEL38 */
#define RZV_INTC_INTM33SEL39_OFFSET                      0x0288  /* INTM33SEL39 */
#define RZV_INTC_INTM33SEL40_OFFSET                      0x028C  /* INTM33SEL40 */
#define RZV_INTC_INTM33SEL41_OFFSET                      0x0290  /* INTM33SEL41 */
#define RZV_INTC_INTM33SEL42_OFFSET                      0x0294  /* INTM33SEL42 */
#define RZV_INTC_ERINTM33CTL0_OFFSET                     0x02F0  /* ERINTM33CTL0 */
#define RZV_INTC_ERINTM33CTL1_OFFSET                     0x02F4  /* ERINTM33CTL1 */
#define RZV_INTC_ERINTM33CTL2_OFFSET                     0x02F8  /* ERINTM33CTL2 */
#define RZV_INTC_ERINTM33CTL3_OFFSET                     0x02FC  /* ERINTM33CTL3 */
#define RZV_INTC_ERINTM33MSK0_OFFSET                     0x0304  /* ERINTM33MSK0 */
#define RZV_INTC_ERINTM33MSK1_OFFSET                     0x0308  /* ERINTM33MSK1 */
#define RZV_INTC_ERINTM33MSK2_OFFSET                     0x030C  /* ERINTM33MSK2 */
#define RZV_INTC_ERINTM33MSK3_OFFSET                     0x0310  /* ERINTM33MSK3 */
#define RZV_INTC_ERINTA55CTL0_OFFSET                     0x0314  /* ERINTA55CTL0 */
#define RZV_INTC_ERINTA55CTL1_OFFSET                     0x0318  /* ERINTA55CTL1 */
#define RZV_INTC_ERINTA55CTL2_OFFSET                     0x031C  /* ERINTA55CTL2 */
#define RZV_INTC_ERINTA55CTL3_OFFSET                     0x0320  /* ERINTA55CTL3 */
#define RZV_INTC_ERINTA55MSK0_OFFSET                     0x0324  /* ERINTA55MSK0 */
#define RZV_INTC_ERINTA55MSK1_OFFSET                     0x0328  /* ERINTA55MSK1 */
#define RZV_INTC_ERINTA55MSK2_OFFSET                     0x032C  /* ERINTA55MSK2 */
#define RZV_INTC_ERINTA55MSK3_OFFSET                     0x0330  /* ERINTA55MSK3 */
#define RZV_INTC_GPTINTA55CTL_OFFSET                     0x0334  /* GPTINTA55CTL */
#define RZV_INTC_SWPE_OFFSET                             0x0338  /* SWPE */
#define RZV_INTC_DM0SEL0_OFFSET                          0x03E8  /* DM0SEL0 */
#define RZV_INTC_DM0SEL1_OFFSET                          0x03EC  /* DM0SEL1 */
#define RZV_INTC_DM0SEL2_OFFSET                          0x03F0  /* DM0SEL2 */
#define RZV_INTC_DM0SEL3_OFFSET                          0x03F4  /* DM0SEL3 */
#define RZV_INTC_DM0SEL4_OFFSET                          0x03F8  /* DM0SEL4 */
#define RZV_INTC_DM0SEL5_OFFSET                          0x03FC  /* DM0SEL5 */
#define RZV_INTC_DM0SEL6_OFFSET                          0x0400  /* DM0SEL6 */
#define RZV_INTC_DM0SEL7_OFFSET                          0x0404  /* DM0SEL7 */
#define RZV_INTC_DM1SEL0_OFFSET                          0x0408  /* DM1SEL0 */
#define RZV_INTC_DM1SEL1_OFFSET                          0x040C  /* DM1SEL1 */
#define RZV_INTC_DM1SEL2_OFFSET                          0x0410  /* DM1SEL2 */
#define RZV_INTC_DM1SEL3_OFFSET                          0x0414  /* DM1SEL3 */
#define RZV_INTC_DM1SEL4_OFFSET                          0x0418  /* DM1SEL4 */
#define RZV_INTC_DM1SEL5_OFFSET                          0x041C  /* DM1SEL5 */
#define RZV_INTC_DM1SEL6_OFFSET                          0x0420  /* DM1SEL6 */
#define RZV_INTC_DM1SEL7_OFFSET                          0x0424  /* DM1SEL7 */
#define RZV_INTC_DM2SEL0_OFFSET                          0x0428  /* DM2SEL0 */
#define RZV_INTC_DM2SEL1_OFFSET                          0x042C  /* DM2SEL1 */
#define RZV_INTC_DM2SEL2_OFFSET                          0x0430  /* DM2SEL2 */
#define RZV_INTC_DM2SEL3_OFFSET                          0x0434  /* DM2SEL3 */
#define RZV_INTC_DM2SEL4_OFFSET                          0x0438  /* DM2SEL4 */
#define RZV_INTC_DM2SEL5_OFFSET                          0x043C  /* DM2SEL5 */
#define RZV_INTC_DM2SEL6_OFFSET                          0x0440  /* DM2SEL6 */
#define RZV_INTC_DM2SEL7_OFFSET                          0x0444  /* DM2SEL7 */
#define RZV_INTC_DM3SEL0_OFFSET                          0x0448  /* DM3SEL0 */
#define RZV_INTC_DM3SEL1_OFFSET                          0x044C  /* DM3SEL1 */
#define RZV_INTC_DM3SEL2_OFFSET                          0x0450  /* DM3SEL2 */
#define RZV_INTC_DM3SEL3_OFFSET                          0x0454  /* DM3SEL3 */
#define RZV_INTC_DM3SEL4_OFFSET                          0x0458  /* DM3SEL4 */
#define RZV_INTC_DM3SEL5_OFFSET                          0x045C  /* DM3SEL5 */
#define RZV_INTC_DM3SEL6_OFFSET                          0x0460  /* DM3SEL6 */
#define RZV_INTC_DM3SEL7_OFFSET                          0x0464  /* DM3SEL7 */
#define RZV_INTC_DM4SEL0_OFFSET                          0x0468  /* DM4SEL0 */
#define RZV_INTC_DM4SEL1_OFFSET                          0x046C  /* DM4SEL1 */
#define RZV_INTC_DM4SEL2_OFFSET                          0x0470  /* DM4SEL2 */
#define RZV_INTC_DM4SEL3_OFFSET                          0x0474  /* DM4SEL3 */
#define RZV_INTC_DM4SEL4_OFFSET                          0x0478  /* DM4SEL4 */
#define RZV_INTC_DM4SEL5_OFFSET                          0x047C  /* DM4SEL5 */
#define RZV_INTC_DM4SEL6_OFFSET                          0x0480  /* DM4SEL6 */
#define RZV_INTC_DM4SEL7_OFFSET                          0x0484  /* DM4SEL7 */
#define RZV_INTC_DERSR_OFFSET                            0x0538  /* DERSR */
#define RZV_INTC_SWEVT_OFFSET                            0x05BC  /* SWEVT */

/* INTC Register Addresses *************************************************/

#define RZV_INTC_BEISR(m)                       (RZV_INTC_BASE + RZV_INTC_BEISR_OFFSET(m))
#define RZV_INTC_DMACKSEL(m)                    (RZV_INTC_BASE + RZV_INTC_DMACKSEL_OFFSET(m))
#define RZV_INTC_DMESR(m)                       (RZV_INTC_BASE + RZV_INTC_DMESR_OFFSET(m))
#define RZV_INTC_DMRCTR(m)                      (RZV_INTC_BASE + RZV_INTC_DMRCTR_OFFSET(m))
#define RZV_INTC_DMTENDSEL(m)                   (RZV_INTC_BASE + RZV_INTC_DMTENDSEL_OFFSET(m))
#define RZV_INTC_ERCLR(m)                       (RZV_INTC_BASE + RZV_INTC_ERCLR_OFFSET(m))
#define RZV_INTC_EREISR(m)                      (RZV_INTC_BASE + RZV_INTC_EREISR_OFFSET(m))
#define RZV_INTC_EVTSEL(m)                      (RZV_INTC_BASE + RZV_INTC_EVTSEL_OFFSET(m))
#define RZV_INTC_OFFDMSTAT(m)                   (RZV_INTC_BASE + RZV_INTC_OFFDMSTAT_OFFSET(m))
#define RZV_INTC_SWDMAC(m)                      (RZV_INTC_BASE + RZV_INTC_SWDMAC_OFFSET(m))
#define RZV_INTC_TITSR(m)                       (RZV_INTC_BASE + RZV_INTC_TITSR_OFFSET(m))
#define RZV_INTC_TSSR(m)                        (RZV_INTC_BASE + RZV_INTC_TSSR_OFFSET(m))
#define RZV_INTC_NSCNT                               (RZV_INTC_BASE + RZV_INTC_NSCNT_OFFSET)
#define RZV_INTC_NSCLR                               (RZV_INTC_BASE + RZV_INTC_NSCLR_OFFSET)
#define RZV_INTC_NITSR                               (RZV_INTC_BASE + RZV_INTC_NITSR_OFFSET)
#define RZV_INTC_ISCTR                               (RZV_INTC_BASE + RZV_INTC_ISCTR_OFFSET)
#define RZV_INTC_ISCLR                               (RZV_INTC_BASE + RZV_INTC_ISCLR_OFFSET)
#define RZV_INTC_IITSR                               (RZV_INTC_BASE + RZV_INTC_IITSR_OFFSET)
#define RZV_INTC_TSCTR                               (RZV_INTC_BASE + RZV_INTC_TSCTR_OFFSET)
#define RZV_INTC_DRCTR                               (RZV_INTC_BASE + RZV_INTC_DRCTR_OFFSET)
#define RZV_INTC_DRCLR                               (RZV_INTC_BASE + RZV_INTC_DRCLR_OFFSET)
#define RZV_INTC_DRTSR                               (RZV_INTC_BASE + RZV_INTC_DRTSR_OFFSET)
#define RZV_INTC_IPTSR                               (RZV_INTC_BASE + RZV_INTC_IPTSR_OFFSET)
#define RZV_INTC_SWINT                               (RZV_INTC_BASE + RZV_INTC_SWINT_OFFSET)
#define RZV_INTC_INTR8SEL0                           (RZV_INTC_BASE + RZV_INTC_INTR8SEL0_OFFSET)
#define RZV_INTC_INTR8SEL1                           (RZV_INTC_BASE + RZV_INTC_INTR8SEL1_OFFSET)
#define RZV_INTC_INTR8SEL2                           (RZV_INTC_BASE + RZV_INTC_INTR8SEL2_OFFSET)
#define RZV_INTC_INTR8SEL3                           (RZV_INTC_BASE + RZV_INTC_INTR8SEL3_OFFSET)
#define RZV_INTC_INTR8SEL4                           (RZV_INTC_BASE + RZV_INTC_INTR8SEL4_OFFSET)
#define RZV_INTC_INTR8SEL5                           (RZV_INTC_BASE + RZV_INTC_INTR8SEL5_OFFSET)
#define RZV_INTC_INTR8SEL6                           (RZV_INTC_BASE + RZV_INTC_INTR8SEL6_OFFSET)
#define RZV_INTC_INTR8SEL7                           (RZV_INTC_BASE + RZV_INTC_INTR8SEL7_OFFSET)
#define RZV_INTC_INTR8SEL8                           (RZV_INTC_BASE + RZV_INTC_INTR8SEL8_OFFSET)
#define RZV_INTC_INTR8SEL9                           (RZV_INTC_BASE + RZV_INTC_INTR8SEL9_OFFSET)
#define RZV_INTC_INTR8SEL10                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL10_OFFSET)
#define RZV_INTC_INTR8SEL11                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL11_OFFSET)
#define RZV_INTC_INTR8SEL12                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL12_OFFSET)
#define RZV_INTC_INTR8SEL13                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL13_OFFSET)
#define RZV_INTC_INTR8SEL14                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL14_OFFSET)
#define RZV_INTC_INTR8SEL15                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL15_OFFSET)
#define RZV_INTC_INTR8SEL16                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL16_OFFSET)
#define RZV_INTC_INTR8SEL17                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL17_OFFSET)
#define RZV_INTC_INTR8SEL18                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL18_OFFSET)
#define RZV_INTC_INTR8SEL19                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL19_OFFSET)
#define RZV_INTC_INTR8SEL20                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL20_OFFSET)
#define RZV_INTC_INTR8SEL21                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL21_OFFSET)
#define RZV_INTC_INTR8SEL22                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL22_OFFSET)
#define RZV_INTC_INTR8SEL23                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL23_OFFSET)
#define RZV_INTC_INTR8SEL24                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL24_OFFSET)
#define RZV_INTC_INTR8SEL25                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL25_OFFSET)
#define RZV_INTC_INTR8SEL26                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL26_OFFSET)
#define RZV_INTC_INTR8SEL27                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL27_OFFSET)
#define RZV_INTC_INTR8SEL28                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL28_OFFSET)
#define RZV_INTC_INTR8SEL29                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL29_OFFSET)
#define RZV_INTC_INTR8SEL30                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL30_OFFSET)
#define RZV_INTC_INTR8SEL31                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL31_OFFSET)
#define RZV_INTC_INTR8SEL32                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL32_OFFSET)
#define RZV_INTC_INTR8SEL33                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL33_OFFSET)
#define RZV_INTC_INTR8SEL34                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL34_OFFSET)
#define RZV_INTC_INTR8SEL35                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL35_OFFSET)
#define RZV_INTC_INTR8SEL36                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL36_OFFSET)
#define RZV_INTC_INTR8SEL37                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL37_OFFSET)
#define RZV_INTC_INTR8SEL38                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL38_OFFSET)
#define RZV_INTC_INTR8SEL39                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL39_OFFSET)
#define RZV_INTC_INTR8SEL40                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL40_OFFSET)
#define RZV_INTC_INTR8SEL41                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL41_OFFSET)
#define RZV_INTC_INTR8SEL42                          (RZV_INTC_BASE + RZV_INTC_INTR8SEL42_OFFSET)
#define RZV_INTC_INTM33SEL0                          (RZV_INTC_BASE + RZV_INTC_INTM33SEL0_OFFSET)
#define RZV_INTC_INTM33SEL1                          (RZV_INTC_BASE + RZV_INTC_INTM33SEL1_OFFSET)
#define RZV_INTC_INTM33SEL2                          (RZV_INTC_BASE + RZV_INTC_INTM33SEL2_OFFSET)
#define RZV_INTC_INTM33SEL3                          (RZV_INTC_BASE + RZV_INTC_INTM33SEL3_OFFSET)
#define RZV_INTC_INTM33SEL4                          (RZV_INTC_BASE + RZV_INTC_INTM33SEL4_OFFSET)
#define RZV_INTC_INTM33SEL5                          (RZV_INTC_BASE + RZV_INTC_INTM33SEL5_OFFSET)
#define RZV_INTC_INTM33SEL6                          (RZV_INTC_BASE + RZV_INTC_INTM33SEL6_OFFSET)
#define RZV_INTC_INTM33SEL7                          (RZV_INTC_BASE + RZV_INTC_INTM33SEL7_OFFSET)
#define RZV_INTC_INTM33SEL8                          (RZV_INTC_BASE + RZV_INTC_INTM33SEL8_OFFSET)
#define RZV_INTC_INTM33SEL9                          (RZV_INTC_BASE + RZV_INTC_INTM33SEL9_OFFSET)
#define RZV_INTC_INTM33SEL10                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL10_OFFSET)
#define RZV_INTC_INTM33SEL11                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL11_OFFSET)
#define RZV_INTC_INTM33SEL12                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL12_OFFSET)
#define RZV_INTC_INTM33SEL13                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL13_OFFSET)
#define RZV_INTC_INTM33SEL14                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL14_OFFSET)
#define RZV_INTC_INTM33SEL15                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL15_OFFSET)
#define RZV_INTC_INTM33SEL16                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL16_OFFSET)
#define RZV_INTC_INTM33SEL17                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL17_OFFSET)
#define RZV_INTC_INTM33SEL18                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL18_OFFSET)
#define RZV_INTC_INTM33SEL19                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL19_OFFSET)
#define RZV_INTC_INTM33SEL20                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL20_OFFSET)
#define RZV_INTC_INTM33SEL21                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL21_OFFSET)
#define RZV_INTC_INTM33SEL22                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL22_OFFSET)
#define RZV_INTC_INTM33SEL23                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL23_OFFSET)
#define RZV_INTC_INTM33SEL24                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL24_OFFSET)
#define RZV_INTC_INTM33SEL25                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL25_OFFSET)
#define RZV_INTC_INTM33SEL26                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL26_OFFSET)
#define RZV_INTC_INTM33SEL27                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL27_OFFSET)
#define RZV_INTC_INTM33SEL28                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL28_OFFSET)
#define RZV_INTC_INTM33SEL29                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL29_OFFSET)
#define RZV_INTC_INTM33SEL30                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL30_OFFSET)
#define RZV_INTC_INTM33SEL31                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL31_OFFSET)
#define RZV_INTC_INTM33SEL32                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL32_OFFSET)
#define RZV_INTC_INTM33SEL33                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL33_OFFSET)
#define RZV_INTC_INTM33SEL34                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL34_OFFSET)
#define RZV_INTC_INTM33SEL35                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL35_OFFSET)
#define RZV_INTC_INTM33SEL36                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL36_OFFSET)
#define RZV_INTC_INTM33SEL37                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL37_OFFSET)
#define RZV_INTC_INTM33SEL38                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL38_OFFSET)
#define RZV_INTC_INTM33SEL39                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL39_OFFSET)
#define RZV_INTC_INTM33SEL40                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL40_OFFSET)
#define RZV_INTC_INTM33SEL41                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL41_OFFSET)
#define RZV_INTC_INTM33SEL42                         (RZV_INTC_BASE + RZV_INTC_INTM33SEL42_OFFSET)
#define RZV_INTC_ERINTM33CTL0                        (RZV_INTC_BASE + RZV_INTC_ERINTM33CTL0_OFFSET)
#define RZV_INTC_ERINTM33CTL1                        (RZV_INTC_BASE + RZV_INTC_ERINTM33CTL1_OFFSET)
#define RZV_INTC_ERINTM33CTL2                        (RZV_INTC_BASE + RZV_INTC_ERINTM33CTL2_OFFSET)
#define RZV_INTC_ERINTM33CTL3                        (RZV_INTC_BASE + RZV_INTC_ERINTM33CTL3_OFFSET)
#define RZV_INTC_ERINTM33MSK0                        (RZV_INTC_BASE + RZV_INTC_ERINTM33MSK0_OFFSET)
#define RZV_INTC_ERINTM33MSK1                        (RZV_INTC_BASE + RZV_INTC_ERINTM33MSK1_OFFSET)
#define RZV_INTC_ERINTM33MSK2                        (RZV_INTC_BASE + RZV_INTC_ERINTM33MSK2_OFFSET)
#define RZV_INTC_ERINTM33MSK3                        (RZV_INTC_BASE + RZV_INTC_ERINTM33MSK3_OFFSET)
#define RZV_INTC_ERINTA55CTL0                        (RZV_INTC_BASE + RZV_INTC_ERINTA55CTL0_OFFSET)
#define RZV_INTC_ERINTA55CTL1                        (RZV_INTC_BASE + RZV_INTC_ERINTA55CTL1_OFFSET)
#define RZV_INTC_ERINTA55CTL2                        (RZV_INTC_BASE + RZV_INTC_ERINTA55CTL2_OFFSET)
#define RZV_INTC_ERINTA55CTL3                        (RZV_INTC_BASE + RZV_INTC_ERINTA55CTL3_OFFSET)
#define RZV_INTC_ERINTA55MSK0                        (RZV_INTC_BASE + RZV_INTC_ERINTA55MSK0_OFFSET)
#define RZV_INTC_ERINTA55MSK1                        (RZV_INTC_BASE + RZV_INTC_ERINTA55MSK1_OFFSET)
#define RZV_INTC_ERINTA55MSK2                        (RZV_INTC_BASE + RZV_INTC_ERINTA55MSK2_OFFSET)
#define RZV_INTC_ERINTA55MSK3                        (RZV_INTC_BASE + RZV_INTC_ERINTA55MSK3_OFFSET)
#define RZV_INTC_GPTINTA55CTL                        (RZV_INTC_BASE + RZV_INTC_GPTINTA55CTL_OFFSET)
#define RZV_INTC_SWPE                                (RZV_INTC_BASE + RZV_INTC_SWPE_OFFSET)
#define RZV_INTC_DM0SEL0                             (RZV_INTC_BASE + RZV_INTC_DM0SEL0_OFFSET)
#define RZV_INTC_DM0SEL1                             (RZV_INTC_BASE + RZV_INTC_DM0SEL1_OFFSET)
#define RZV_INTC_DM0SEL2                             (RZV_INTC_BASE + RZV_INTC_DM0SEL2_OFFSET)
#define RZV_INTC_DM0SEL3                             (RZV_INTC_BASE + RZV_INTC_DM0SEL3_OFFSET)
#define RZV_INTC_DM0SEL4                             (RZV_INTC_BASE + RZV_INTC_DM0SEL4_OFFSET)
#define RZV_INTC_DM0SEL5                             (RZV_INTC_BASE + RZV_INTC_DM0SEL5_OFFSET)
#define RZV_INTC_DM0SEL6                             (RZV_INTC_BASE + RZV_INTC_DM0SEL6_OFFSET)
#define RZV_INTC_DM0SEL7                             (RZV_INTC_BASE + RZV_INTC_DM0SEL7_OFFSET)
#define RZV_INTC_DM1SEL0                             (RZV_INTC_BASE + RZV_INTC_DM1SEL0_OFFSET)
#define RZV_INTC_DM1SEL1                             (RZV_INTC_BASE + RZV_INTC_DM1SEL1_OFFSET)
#define RZV_INTC_DM1SEL2                             (RZV_INTC_BASE + RZV_INTC_DM1SEL2_OFFSET)
#define RZV_INTC_DM1SEL3                             (RZV_INTC_BASE + RZV_INTC_DM1SEL3_OFFSET)
#define RZV_INTC_DM1SEL4                             (RZV_INTC_BASE + RZV_INTC_DM1SEL4_OFFSET)
#define RZV_INTC_DM1SEL5                             (RZV_INTC_BASE + RZV_INTC_DM1SEL5_OFFSET)
#define RZV_INTC_DM1SEL6                             (RZV_INTC_BASE + RZV_INTC_DM1SEL6_OFFSET)
#define RZV_INTC_DM1SEL7                             (RZV_INTC_BASE + RZV_INTC_DM1SEL7_OFFSET)
#define RZV_INTC_DM2SEL0                             (RZV_INTC_BASE + RZV_INTC_DM2SEL0_OFFSET)
#define RZV_INTC_DM2SEL1                             (RZV_INTC_BASE + RZV_INTC_DM2SEL1_OFFSET)
#define RZV_INTC_DM2SEL2                             (RZV_INTC_BASE + RZV_INTC_DM2SEL2_OFFSET)
#define RZV_INTC_DM2SEL3                             (RZV_INTC_BASE + RZV_INTC_DM2SEL3_OFFSET)
#define RZV_INTC_DM2SEL4                             (RZV_INTC_BASE + RZV_INTC_DM2SEL4_OFFSET)
#define RZV_INTC_DM2SEL5                             (RZV_INTC_BASE + RZV_INTC_DM2SEL5_OFFSET)
#define RZV_INTC_DM2SEL6                             (RZV_INTC_BASE + RZV_INTC_DM2SEL6_OFFSET)
#define RZV_INTC_DM2SEL7                             (RZV_INTC_BASE + RZV_INTC_DM2SEL7_OFFSET)
#define RZV_INTC_DM3SEL0                             (RZV_INTC_BASE + RZV_INTC_DM3SEL0_OFFSET)
#define RZV_INTC_DM3SEL1                             (RZV_INTC_BASE + RZV_INTC_DM3SEL1_OFFSET)
#define RZV_INTC_DM3SEL2                             (RZV_INTC_BASE + RZV_INTC_DM3SEL2_OFFSET)
#define RZV_INTC_DM3SEL3                             (RZV_INTC_BASE + RZV_INTC_DM3SEL3_OFFSET)
#define RZV_INTC_DM3SEL4                             (RZV_INTC_BASE + RZV_INTC_DM3SEL4_OFFSET)
#define RZV_INTC_DM3SEL5                             (RZV_INTC_BASE + RZV_INTC_DM3SEL5_OFFSET)
#define RZV_INTC_DM3SEL6                             (RZV_INTC_BASE + RZV_INTC_DM3SEL6_OFFSET)
#define RZV_INTC_DM3SEL7                             (RZV_INTC_BASE + RZV_INTC_DM3SEL7_OFFSET)
#define RZV_INTC_DM4SEL0                             (RZV_INTC_BASE + RZV_INTC_DM4SEL0_OFFSET)
#define RZV_INTC_DM4SEL1                             (RZV_INTC_BASE + RZV_INTC_DM4SEL1_OFFSET)
#define RZV_INTC_DM4SEL2                             (RZV_INTC_BASE + RZV_INTC_DM4SEL2_OFFSET)
#define RZV_INTC_DM4SEL3                             (RZV_INTC_BASE + RZV_INTC_DM4SEL3_OFFSET)
#define RZV_INTC_DM4SEL4                             (RZV_INTC_BASE + RZV_INTC_DM4SEL4_OFFSET)
#define RZV_INTC_DM4SEL5                             (RZV_INTC_BASE + RZV_INTC_DM4SEL5_OFFSET)
#define RZV_INTC_DM4SEL6                             (RZV_INTC_BASE + RZV_INTC_DM4SEL6_OFFSET)
#define RZV_INTC_DM4SEL7                             (RZV_INTC_BASE + RZV_INTC_DM4SEL7_OFFSET)
#define RZV_INTC_DERSR                               (RZV_INTC_BASE + RZV_INTC_DERSR_OFFSET)
#define RZV_INTC_SWEVT                               (RZV_INTC_BASE + RZV_INTC_SWEVT_OFFSET)

/* INTC INTR8SEL Helper Macros **********************************************/

/* INTR8SEL registers: 43 registers × 3 slots per register = 129 total slots.
 * Each slot is 10 bits wide and routes an ELC event to a GIC SPI interrupt.
 * Slot N is delivered on physical GIC INTID (RZV_INTC_SEL_SPI_BASE + N) =
 * 385 + N (= FIXED_INTSEL_COUNT 353 + SGI/PPI offset 32).  See rzv_icu.c.
 */

#define RZV_INTC_INTR8SEL(m)        (RZV_INTC_BASE + RZV_INTC_INTR8SEL0_OFFSET + ((m) * 4))
#define RZV_INTC_INTR8SEL_REG(slot) ((slot) / 3)              /* Which register (0-42) */
#define RZV_INTC_INTR8SEL_IDX(slot) ((slot) % 3)              /* Which slot in register (0-2) */
#define RZV_INTC_INTR8SEL_SHIFT(idx) ((idx) * 10)            /* Bit shift for slot */
#define RZV_INTC_INTR8SEL_MASK      0x3FF                     /* 10-bit mask */

/* INTC BEISR Register Bit Definitions (Parameterized) *********************/

#define INTC_BEISR_BESTAT0_n_SHIFT                        (0)      /* Bits 0-31: Bestat0 N */
#define INTC_BEISR_BESTAT0_n_MASK(m)                      (0xffffffff << INTC_BEISR_BESTAT0_n_SHIFT)
#define INTC_BEISR_BESTAT0_n(m,val)                       (((val) << INTC_BEISR_BESTAT0_n_SHIFT) & INTC_BEISR_BESTAT0_n_MASK(m))

/* INTC DMACKSEL Register Bit Definitions (Parameterized) ******************/

#define INTC_DMACKSEL_DACK_SEL_SHIFT(n)                   ((unsigned)(0 + ((n) * 8)))  /* Bits for DACK_SELn */
#define INTC_DMACKSEL_DACK_SEL_MASK(m,n)                  (0x7fu << INTC_DMACKSEL_DACK_SEL_SHIFT(n))
#define INTC_DMACKSEL_DACK_SEL(m,n,v)                     (((unsigned)(v) & 0x7fu) << INTC_DMACKSEL_DACK_SEL_SHIFT(n))


/* INTC DMESR Register Bit Definitions (Parameterized) *********************/

#define INTC_DMESR_DMESEL0_n_SHIFT                        (0)      /* Bits 0-31: Dmesel0 N */
#define INTC_DMESR_DMESEL0_n_MASK(m)                      (0xffffffff << INTC_DMESR_DMESEL0_n_SHIFT)
#define INTC_DMESR_DMESEL0_n(m,val)                       (((val) << INTC_DMESR_DMESEL0_n_SHIFT) & INTC_DMESR_DMESEL0_n_MASK(m))

/* INTC DMRCTR Register Bit Definitions (Parameterized) ********************/

#define INTC_DMRCTR_DMADUP0_n_SHIFT                       (0)      /* Bits 0-31: Dmadup0 N */
#define INTC_DMRCTR_DMADUP0_n_MASK(m)                     (0xffffffff << INTC_DMRCTR_DMADUP0_n_SHIFT)
#define INTC_DMRCTR_DMADUP0_n(m,val)                      (((val) << INTC_DMRCTR_DMADUP0_n_SHIFT) & INTC_DMRCTR_DMADUP0_n_MASK(m))

/* INTC DMTENDSEL Register Bit Definitions (Parameterized) *****************/

#define INTC_DMTENDSEL_DTEND_SEL_SHIFT(n)                 ((unsigned)(0 + ((n) * 8)))  /* Bits for DTEND_SELn */
#define INTC_DMTENDSEL_DTEND_SEL_MASK(m,n)                (0x7fu << INTC_DMTENDSEL_DTEND_SEL_SHIFT(n))
#define INTC_DMTENDSEL_DTEND_SEL(m,n,v)                   (((unsigned)(v) & 0x7fu) << INTC_DMTENDSEL_DTEND_SEL_SHIFT(n))


/* INTC ERCLR Register Bit Definitions (Parameterized) *********************/

#define INTC_ERCLR_E1CLR0(m,n)                            (1u << (0 + ((unsigned)(n) * 1)))  /* E1Clr0 0 */

#define INTC_ERCLR_E2CLR0(m,n)                            (1u << (8 + ((unsigned)(n) * 1)))  /* E2Clr0 0 */

#define INTC_ERCLR_OFCLR0(m,n)                            (1u << (16 + ((unsigned)(n) * 1)))  /* Ofclr0 0 */


/* INTC EREISR Register Bit Definitions (Parameterized) ********************/

#define INTC_EREISR_E1STAT0(m,n)                          (1u << (0 + ((unsigned)(n) * 1)))  /* E1Stat0 0 */

#define INTC_EREISR_E2STAT0(m,n)                          (1u << (8 + ((unsigned)(n) * 1)))  /* E2Stat0 0 */

#define INTC_EREISR_OFSTAT0(m,n)                          (1u << (16 + ((unsigned)(n) * 1)))  /* Ofstat0 0 */


/* INTC EVTSEL Register Bit Definitions (Parameterized) ********************/

#define INTC_EVTSEL_EC_SEL_SHIFT(n)                       ((unsigned)(0 + ((n) * 10)))  /* Bits for EC_SELn */
#define INTC_EVTSEL_EC_SEL_MASK(m,n)                      (0x3ffu << INTC_EVTSEL_EC_SEL_SHIFT(n))
#define INTC_EVTSEL_EC_SEL(m,n,v)                         (((unsigned)(v) & 0x3ffu) << INTC_EVTSEL_EC_SEL_SHIFT(n))


/* INTC OFFDMSTAT Register Bit Definitions (Parameterized) *****************/

#define INTC_OFFDMSTAT_OD0STATn_SHIFT                     (0)      /* Bits 0-31: Od0Statn */
#define INTC_OFFDMSTAT_OD0STATn_MASK(m)                   (0xffffffff << INTC_OFFDMSTAT_OD0STATn_SHIFT)
#define INTC_OFFDMSTAT_OD0STATn(m,val)                    (((val) << INTC_OFFDMSTAT_OD0STATn_SHIFT) & INTC_OFFDMSTAT_OD0STATn_MASK(m))

/* INTC SWDMAC Register Bit Definitions (Parameterized) ********************/

#define INTC_SWDMAC_D0Cn_SHIFT                            (0)      /* Bits 0-15: D0Cn */
#define INTC_SWDMAC_D0Cn_MASK(m)                          (0xffff << INTC_SWDMAC_D0Cn_SHIFT)
#define INTC_SWDMAC_D0Cn(m,val)                           (((val) << INTC_SWDMAC_D0Cn_SHIFT) & INTC_SWDMAC_D0Cn_MASK(m))

/* INTC TITSR Register Bit Definitions (Parameterized) *********************/

#define INTC_TITSR_TITSEL0_SHIFT(n)                       ((unsigned)(0 + ((n) * 2)))  /* Bits for TITSEL0n */
#define INTC_TITSR_TITSEL0_MASK(m,n)                      (0x3u << INTC_TITSR_TITSEL0_SHIFT(n))
#define INTC_TITSR_TITSEL0(m,n,v)                         (((unsigned)(v) & 0x3u) << INTC_TITSR_TITSEL0_SHIFT(n))


/* INTC TSSR Register Bit Definitions (Parameterized) **********************/

#define INTC_TSSR_TIEN0(m,n)                              (1u << (7 + ((unsigned)(n) * 8)))  /* Tien0 0 */

#define INTC_TSSR_TSSEL0_SHIFT(n)                         ((unsigned)(0 + ((n) * 8)))  /* Bits for TSSEL0n */
#define INTC_TSSR_TSSEL0_MASK(m,n)                        (0x7fu << INTC_TSSR_TSSEL0_SHIFT(n))
#define INTC_TSSR_TSSEL0(m,n,v)                           (((unsigned)(v) & 0x7fu) << INTC_TSSR_TSSEL0_SHIFT(n))


/* INTC BECLR0 Register Bit Definitions ******************************/

#define INTC_BECLR0_BECLR0_n_SHIFT              (0)      /* Bits 0-31: Beclr0 N */
#define INTC_BECLR0_BECLR0_n_MASK               (0xffffffff << INTC_BECLR0_BECLR0_n_SHIFT)

/* INTC BECLR1 Register Bit Definitions ******************************/

#define INTC_BECLR1_BECLR1_n_SHIFT              (0)      /* Bits 0-31: Beclr1 N */
#define INTC_BECLR1_BECLR1_n_MASK               (0xffffffff << INTC_BECLR1_BECLR1_n_SHIFT)

/* INTC BECLR2 Register Bit Definitions ******************************/

#define INTC_BECLR2_BECLR2_n_SHIFT              (0)      /* Bits 0-31: Beclr2 N */
#define INTC_BECLR2_BECLR2_n_MASK               (0xffffffff << INTC_BECLR2_BECLR2_n_SHIFT)

/* INTC BECLR3 Register Bit Definitions ******************************/

#define INTC_BECLR3_BECLR3_n_SHIFT              (0)      /* Bits 0-31: Beclr3 N */
#define INTC_BECLR3_BECLR3_n_MASK               (0xffffffff << INTC_BECLR3_BECLR3_n_SHIFT)

/* INTC DERSR Register Bit Definitions *******************************/

/* DERSEL_ fields (parameterized for indices 0-4) */
#define INTC_DERSR_DERSEL(n)                              (1u << (0 + ((unsigned)(n) * 1)))  /* Dersel 0 */

/* INTC DM0SEL0 Register Bit Definitions *****************************/

#define INTC_DM0SEL0_D0RQ_SEL0_SHIFT            (0)      /* Bits 0-7: D0Rq Sel0 */
#define INTC_DM0SEL0_D0RQ_SEL0_MASK             (0xff << INTC_DM0SEL0_D0RQ_SEL0_SHIFT)

#define INTC_DM0SEL0_D0RQ_SEL_SHIFT             (8)      /* Bits 8-9: D0Rq Sel */
#define INTC_DM0SEL0_D0RQ_SEL_MASK              (0x3 << INTC_DM0SEL0_D0RQ_SEL_SHIFT)

#define INTC_DM0SEL0_D0SEL_CLRON                (1 << 15)  /* D0Sel Clron */

#define INTC_DM0SEL0_D0RQ_SEL1_SHIFT            (16)      /* Bits 16-25: D0Rq Sel1 */
#define INTC_DM0SEL0_D0RQ_SEL1_MASK             (0x3ff << INTC_DM0SEL0_D0RQ_SEL1_SHIFT)

#define INTC_DM0SEL0_D0SEL_CLRON1               (1 << 31)  /* D0Sel Clron1 */

/* INTC DM0SEL1 Register Bit Definitions *****************************/

#define INTC_DM0SEL1_D0RQ_SEL2_SHIFT            (0)      /* Bits 0-9: D0Rq Sel2 */
#define INTC_DM0SEL1_D0RQ_SEL2_MASK             (0x3ff << INTC_DM0SEL1_D0RQ_SEL2_SHIFT)

#define INTC_DM0SEL1_D0SEL_CLRON2               (1 << 15)  /* D0Sel Clron2 */

#define INTC_DM0SEL1_D0RQ_SEL3_SHIFT            (16)      /* Bits 16-25: D0Rq Sel3 */
#define INTC_DM0SEL1_D0RQ_SEL3_MASK             (0x3ff << INTC_DM0SEL1_D0RQ_SEL3_SHIFT)

#define INTC_DM0SEL1_D0SEL_CLRON3               (1 << 31)  /* D0Sel Clron3 */

/* INTC DM0SEL2 Register Bit Definitions *****************************/

#define INTC_DM0SEL2_D0RQ_SEL4_SHIFT            (0)      /* Bits 0-9: D0Rq Sel4 */
#define INTC_DM0SEL2_D0RQ_SEL4_MASK             (0x3ff << INTC_DM0SEL2_D0RQ_SEL4_SHIFT)

#define INTC_DM0SEL2_D0SEL_CLRON4               (1 << 15)  /* D0Sel Clron4 */

#define INTC_DM0SEL2_D0RQ_SEL5_SHIFT            (16)      /* Bits 16-25: D0Rq Sel5 */
#define INTC_DM0SEL2_D0RQ_SEL5_MASK             (0x3ff << INTC_DM0SEL2_D0RQ_SEL5_SHIFT)

#define INTC_DM0SEL2_D0SEL_CLRON5               (1 << 31)  /* D0Sel Clron5 */

/* INTC DM0SEL3 Register Bit Definitions *****************************/

#define INTC_DM0SEL3_D0RQ_SEL6_SHIFT            (0)      /* Bits 0-9: D0Rq Sel6 */
#define INTC_DM0SEL3_D0RQ_SEL6_MASK             (0x3ff << INTC_DM0SEL3_D0RQ_SEL6_SHIFT)

#define INTC_DM0SEL3_D0SEL_CLRON6               (1 << 15)  /* D0Sel Clron6 */

#define INTC_DM0SEL3_D0RQ_SEL7_SHIFT            (16)      /* Bits 16-25: D0Rq Sel7 */
#define INTC_DM0SEL3_D0RQ_SEL7_MASK             (0x3ff << INTC_DM0SEL3_D0RQ_SEL7_SHIFT)

#define INTC_DM0SEL3_D0SEL_CLRON7               (1 << 31)  /* D0Sel Clron7 */

/* INTC DM0SEL4 Register Bit Definitions *****************************/

#define INTC_DM0SEL4_D0RQ_SEL8_SHIFT            (0)      /* Bits 0-9: D0Rq Sel8 */
#define INTC_DM0SEL4_D0RQ_SEL8_MASK             (0x3ff << INTC_DM0SEL4_D0RQ_SEL8_SHIFT)

#define INTC_DM0SEL4_D0SEL_CLRON8               (1 << 15)  /* D0Sel Clron8 */

#define INTC_DM0SEL4_D0RQ_SEL9_SHIFT            (16)      /* Bits 16-25: D0Rq Sel9 */
#define INTC_DM0SEL4_D0RQ_SEL9_MASK             (0x3ff << INTC_DM0SEL4_D0RQ_SEL9_SHIFT)

#define INTC_DM0SEL4_D0SEL_CLRON9               (1 << 31)  /* D0Sel Clron9 */

/* INTC DM0SEL5 Register Bit Definitions *****************************/

#define INTC_DM0SEL5_D0RQ_SEL10_SHIFT           (0)      /* Bits 0-9: D0Rq Sel10 */
#define INTC_DM0SEL5_D0RQ_SEL10_MASK            (0x3ff << INTC_DM0SEL5_D0RQ_SEL10_SHIFT)

#define INTC_DM0SEL5_D0SEL_CLRON10              (1 << 15)  /* D0Sel Clron10 */

#define INTC_DM0SEL5_D0RQ_SEL11_SHIFT           (16)      /* Bits 16-25: D0Rq Sel11 */
#define INTC_DM0SEL5_D0RQ_SEL11_MASK            (0x3ff << INTC_DM0SEL5_D0RQ_SEL11_SHIFT)

#define INTC_DM0SEL5_D0SEL_CLRON11              (1 << 31)  /* D0Sel Clron11 */

/* INTC DM0SEL6 Register Bit Definitions *****************************/

#define INTC_DM0SEL6_D0RQ_SEL12_SHIFT           (0)      /* Bits 0-9: D0Rq Sel12 */
#define INTC_DM0SEL6_D0RQ_SEL12_MASK            (0x3ff << INTC_DM0SEL6_D0RQ_SEL12_SHIFT)

#define INTC_DM0SEL6_D0SEL_CLRON12              (1 << 15)  /* D0Sel Clron12 */

#define INTC_DM0SEL6_D0RQ_SEL13_SHIFT           (16)      /* Bits 16-25: D0Rq Sel13 */
#define INTC_DM0SEL6_D0RQ_SEL13_MASK            (0x3ff << INTC_DM0SEL6_D0RQ_SEL13_SHIFT)

#define INTC_DM0SEL6_D0SEL_CLRON13              (1 << 31)  /* D0Sel Clron13 */

/* INTC DM0SEL7 Register Bit Definitions *****************************/

#define INTC_DM0SEL7_D0RQ_SEL14_SHIFT           (0)      /* Bits 0-9: D0Rq Sel14 */
#define INTC_DM0SEL7_D0RQ_SEL14_MASK            (0x3ff << INTC_DM0SEL7_D0RQ_SEL14_SHIFT)

#define INTC_DM0SEL7_D0SEL_CLRON14              (1 << 15)  /* D0Sel Clron14 */

#define INTC_DM0SEL7_D0RQ_SEL15_SHIFT           (16)      /* Bits 16-25: D0Rq Sel15 */
#define INTC_DM0SEL7_D0RQ_SEL15_MASK            (0x3ff << INTC_DM0SEL7_D0RQ_SEL15_SHIFT)

#define INTC_DM0SEL7_D0SEL_CLRON15              (1 << 31)  /* D0Sel Clron15 */

/* INTC DM1SEL0 Register Bit Definitions *****************************/

#define INTC_DM1SEL0_D1RQ_SEL0_SHIFT            (0)      /* Bits 0-7: D1Rq Sel0 */
#define INTC_DM1SEL0_D1RQ_SEL0_MASK             (0xff << INTC_DM1SEL0_D1RQ_SEL0_SHIFT)

#define INTC_DM1SEL0_D1RQ_SEL_SHIFT             (8)      /* Bits 8-9: D1Rq Sel */
#define INTC_DM1SEL0_D1RQ_SEL_MASK              (0x3 << INTC_DM1SEL0_D1RQ_SEL_SHIFT)

#define INTC_DM1SEL0_D1SEL_CLRON                (1 << 15)  /* D1Sel Clron */

#define INTC_DM1SEL0_D1RQ_SEL1_SHIFT            (16)      /* Bits 16-25: D1Rq Sel1 */
#define INTC_DM1SEL0_D1RQ_SEL1_MASK             (0x3ff << INTC_DM1SEL0_D1RQ_SEL1_SHIFT)

#define INTC_DM1SEL0_D1SEL_CLRON1               (1 << 31)  /* D1Sel Clron1 */

/* INTC DM1SEL1 Register Bit Definitions *****************************/

#define INTC_DM1SEL1_D1RQ_SEL2_SHIFT            (0)      /* Bits 0-9: D1Rq Sel2 */
#define INTC_DM1SEL1_D1RQ_SEL2_MASK             (0x3ff << INTC_DM1SEL1_D1RQ_SEL2_SHIFT)

#define INTC_DM1SEL1_D1SEL_CLRON2               (1 << 15)  /* D1Sel Clron2 */

#define INTC_DM1SEL1_D1RQ_SEL3_SHIFT            (16)      /* Bits 16-25: D1Rq Sel3 */
#define INTC_DM1SEL1_D1RQ_SEL3_MASK             (0x3ff << INTC_DM1SEL1_D1RQ_SEL3_SHIFT)

#define INTC_DM1SEL1_D1SEL_CLRON3               (1 << 31)  /* D1Sel Clron3 */

/* INTC DM1SEL2 Register Bit Definitions *****************************/

#define INTC_DM1SEL2_D1RQ_SEL4_SHIFT            (0)      /* Bits 0-9: D1Rq Sel4 */
#define INTC_DM1SEL2_D1RQ_SEL4_MASK             (0x3ff << INTC_DM1SEL2_D1RQ_SEL4_SHIFT)

#define INTC_DM1SEL2_D1SEL_CLRON4               (1 << 15)  /* D1Sel Clron4 */

#define INTC_DM1SEL2_D1RQ_SEL5_SHIFT            (16)      /* Bits 16-25: D1Rq Sel5 */
#define INTC_DM1SEL2_D1RQ_SEL5_MASK             (0x3ff << INTC_DM1SEL2_D1RQ_SEL5_SHIFT)

#define INTC_DM1SEL2_D1SEL_CLRON5               (1 << 31)  /* D1Sel Clron5 */

/* INTC DM1SEL3 Register Bit Definitions *****************************/

#define INTC_DM1SEL3_D1RQ_SEL6_SHIFT            (0)      /* Bits 0-9: D1Rq Sel6 */
#define INTC_DM1SEL3_D1RQ_SEL6_MASK             (0x3ff << INTC_DM1SEL3_D1RQ_SEL6_SHIFT)

#define INTC_DM1SEL3_D1SEL_CLRON6               (1 << 15)  /* D1Sel Clron6 */

#define INTC_DM1SEL3_D1RQ_SEL7_SHIFT            (16)      /* Bits 16-25: D1Rq Sel7 */
#define INTC_DM1SEL3_D1RQ_SEL7_MASK             (0x3ff << INTC_DM1SEL3_D1RQ_SEL7_SHIFT)

#define INTC_DM1SEL3_D1SEL_CLRON7               (1 << 31)  /* D1Sel Clron7 */

/* INTC DM1SEL4 Register Bit Definitions *****************************/

#define INTC_DM1SEL4_D1RQ_SEL8_SHIFT            (0)      /* Bits 0-9: D1Rq Sel8 */
#define INTC_DM1SEL4_D1RQ_SEL8_MASK             (0x3ff << INTC_DM1SEL4_D1RQ_SEL8_SHIFT)

#define INTC_DM1SEL4_D1SEL_CLRON8               (1 << 15)  /* D1Sel Clron8 */

#define INTC_DM1SEL4_D1RQ_SEL9_SHIFT            (16)      /* Bits 16-25: D1Rq Sel9 */
#define INTC_DM1SEL4_D1RQ_SEL9_MASK             (0x3ff << INTC_DM1SEL4_D1RQ_SEL9_SHIFT)

#define INTC_DM1SEL4_D1SEL_CLRON9               (1 << 31)  /* D1Sel Clron9 */

/* INTC DM1SEL5 Register Bit Definitions *****************************/

#define INTC_DM1SEL5_D1RQ_SEL10_SHIFT           (0)      /* Bits 0-9: D1Rq Sel10 */
#define INTC_DM1SEL5_D1RQ_SEL10_MASK            (0x3ff << INTC_DM1SEL5_D1RQ_SEL10_SHIFT)

#define INTC_DM1SEL5_D1SEL_CLRON10              (1 << 15)  /* D1Sel Clron10 */

#define INTC_DM1SEL5_D1RQ_SEL11_SHIFT           (16)      /* Bits 16-25: D1Rq Sel11 */
#define INTC_DM1SEL5_D1RQ_SEL11_MASK            (0x3ff << INTC_DM1SEL5_D1RQ_SEL11_SHIFT)

#define INTC_DM1SEL5_D1SEL_CLRON11              (1 << 31)  /* D1Sel Clron11 */

/* INTC DM1SEL6 Register Bit Definitions *****************************/

#define INTC_DM1SEL6_D1RQ_SEL12_SHIFT           (0)      /* Bits 0-9: D1Rq Sel12 */
#define INTC_DM1SEL6_D1RQ_SEL12_MASK            (0x3ff << INTC_DM1SEL6_D1RQ_SEL12_SHIFT)

#define INTC_DM1SEL6_D1SEL_CLRON12              (1 << 15)  /* D1Sel Clron12 */

#define INTC_DM1SEL6_D1RQ_SEL13_SHIFT           (16)      /* Bits 16-25: D1Rq Sel13 */
#define INTC_DM1SEL6_D1RQ_SEL13_MASK            (0x3ff << INTC_DM1SEL6_D1RQ_SEL13_SHIFT)

#define INTC_DM1SEL6_D1SEL_CLRON13              (1 << 31)  /* D1Sel Clron13 */

/* INTC DM1SEL7 Register Bit Definitions *****************************/

#define INTC_DM1SEL7_D1RQ_SEL14_SHIFT           (0)      /* Bits 0-9: D1Rq Sel14 */
#define INTC_DM1SEL7_D1RQ_SEL14_MASK            (0x3ff << INTC_DM1SEL7_D1RQ_SEL14_SHIFT)

#define INTC_DM1SEL7_D1SEL_CLRON14              (1 << 15)  /* D1Sel Clron14 */

#define INTC_DM1SEL7_D1RQ_SEL15_SHIFT           (16)      /* Bits 16-25: D1Rq Sel15 */
#define INTC_DM1SEL7_D1RQ_SEL15_MASK            (0x3ff << INTC_DM1SEL7_D1RQ_SEL15_SHIFT)

#define INTC_DM1SEL7_D1SEL_CLRON15              (1 << 31)  /* D1Sel Clron15 */

/* INTC DM2SEL0 Register Bit Definitions *****************************/

#define INTC_DM2SEL0_D2RQ_SEL0_SHIFT            (0)      /* Bits 0-7: D2Rq Sel0 */
#define INTC_DM2SEL0_D2RQ_SEL0_MASK             (0xff << INTC_DM2SEL0_D2RQ_SEL0_SHIFT)

#define INTC_DM2SEL0_D2RQ_SEL_SHIFT             (8)      /* Bits 8-9: D2Rq Sel */
#define INTC_DM2SEL0_D2RQ_SEL_MASK              (0x3 << INTC_DM2SEL0_D2RQ_SEL_SHIFT)

#define INTC_DM2SEL0_D2SEL_CLRON                (1 << 15)  /* D2Sel Clron */

#define INTC_DM2SEL0_D2RQ_SEL1_SHIFT            (16)      /* Bits 16-25: D2Rq Sel1 */
#define INTC_DM2SEL0_D2RQ_SEL1_MASK             (0x3ff << INTC_DM2SEL0_D2RQ_SEL1_SHIFT)

#define INTC_DM2SEL0_D2SEL_CLRON1               (1 << 31)  /* D2Sel Clron1 */

/* INTC DM2SEL1 Register Bit Definitions *****************************/

#define INTC_DM2SEL1_D2RQ_SEL2_SHIFT            (0)      /* Bits 0-9: D2Rq Sel2 */
#define INTC_DM2SEL1_D2RQ_SEL2_MASK             (0x3ff << INTC_DM2SEL1_D2RQ_SEL2_SHIFT)

#define INTC_DM2SEL1_D2SEL_CLRON2               (1 << 15)  /* D2Sel Clron2 */

#define INTC_DM2SEL1_D2RQ_SEL3_SHIFT            (16)      /* Bits 16-25: D2Rq Sel3 */
#define INTC_DM2SEL1_D2RQ_SEL3_MASK             (0x3ff << INTC_DM2SEL1_D2RQ_SEL3_SHIFT)

#define INTC_DM2SEL1_D2SEL_CLRON3               (1 << 31)  /* D2Sel Clron3 */

/* INTC DM2SEL2 Register Bit Definitions *****************************/

#define INTC_DM2SEL2_D2RQ_SEL4_SHIFT            (0)      /* Bits 0-9: D2Rq Sel4 */
#define INTC_DM2SEL2_D2RQ_SEL4_MASK             (0x3ff << INTC_DM2SEL2_D2RQ_SEL4_SHIFT)

#define INTC_DM2SEL2_D2SEL_CLRON4               (1 << 15)  /* D2Sel Clron4 */

#define INTC_DM2SEL2_D2RQ_SEL5_SHIFT            (16)      /* Bits 16-25: D2Rq Sel5 */
#define INTC_DM2SEL2_D2RQ_SEL5_MASK             (0x3ff << INTC_DM2SEL2_D2RQ_SEL5_SHIFT)

#define INTC_DM2SEL2_D2SEL_CLRON5               (1 << 31)  /* D2Sel Clron5 */

/* INTC DM2SEL3 Register Bit Definitions *****************************/

#define INTC_DM2SEL3_D2RQ_SEL6_SHIFT            (0)      /* Bits 0-9: D2Rq Sel6 */
#define INTC_DM2SEL3_D2RQ_SEL6_MASK             (0x3ff << INTC_DM2SEL3_D2RQ_SEL6_SHIFT)

#define INTC_DM2SEL3_D2SEL_CLRON6               (1 << 15)  /* D2Sel Clron6 */

#define INTC_DM2SEL3_D2RQ_SEL7_SHIFT            (16)      /* Bits 16-25: D2Rq Sel7 */
#define INTC_DM2SEL3_D2RQ_SEL7_MASK             (0x3ff << INTC_DM2SEL3_D2RQ_SEL7_SHIFT)

#define INTC_DM2SEL3_D2SEL_CLRON7               (1 << 31)  /* D2Sel Clron7 */

/* INTC DM2SEL4 Register Bit Definitions *****************************/

#define INTC_DM2SEL4_D2RQ_SEL8_SHIFT            (0)      /* Bits 0-9: D2Rq Sel8 */
#define INTC_DM2SEL4_D2RQ_SEL8_MASK             (0x3ff << INTC_DM2SEL4_D2RQ_SEL8_SHIFT)

#define INTC_DM2SEL4_D2SEL_CLRON8               (1 << 15)  /* D2Sel Clron8 */

#define INTC_DM2SEL4_D2RQ_SEL9_SHIFT            (16)      /* Bits 16-25: D2Rq Sel9 */
#define INTC_DM2SEL4_D2RQ_SEL9_MASK             (0x3ff << INTC_DM2SEL4_D2RQ_SEL9_SHIFT)

#define INTC_DM2SEL4_D2SEL_CLRON9               (1 << 31)  /* D2Sel Clron9 */

/* INTC DM2SEL5 Register Bit Definitions *****************************/

#define INTC_DM2SEL5_D2RQ_SEL10_SHIFT           (0)      /* Bits 0-9: D2Rq Sel10 */
#define INTC_DM2SEL5_D2RQ_SEL10_MASK            (0x3ff << INTC_DM2SEL5_D2RQ_SEL10_SHIFT)

#define INTC_DM2SEL5_D2SEL_CLRON10              (1 << 15)  /* D2Sel Clron10 */

#define INTC_DM2SEL5_D2RQ_SEL11_SHIFT           (16)      /* Bits 16-25: D2Rq Sel11 */
#define INTC_DM2SEL5_D2RQ_SEL11_MASK            (0x3ff << INTC_DM2SEL5_D2RQ_SEL11_SHIFT)

#define INTC_DM2SEL5_D2SEL_CLRON11              (1 << 31)  /* D2Sel Clron11 */

/* INTC DM2SEL6 Register Bit Definitions *****************************/

#define INTC_DM2SEL6_D2RQ_SEL12_SHIFT           (0)      /* Bits 0-9: D2Rq Sel12 */
#define INTC_DM2SEL6_D2RQ_SEL12_MASK            (0x3ff << INTC_DM2SEL6_D2RQ_SEL12_SHIFT)

#define INTC_DM2SEL6_D2SEL_CLRON12              (1 << 15)  /* D2Sel Clron12 */

#define INTC_DM2SEL6_D2RQ_SEL13_SHIFT           (16)      /* Bits 16-25: D2Rq Sel13 */
#define INTC_DM2SEL6_D2RQ_SEL13_MASK            (0x3ff << INTC_DM2SEL6_D2RQ_SEL13_SHIFT)

#define INTC_DM2SEL6_D2SEL_CLRON13              (1 << 31)  /* D2Sel Clron13 */

/* INTC DM2SEL7 Register Bit Definitions *****************************/

#define INTC_DM2SEL7_D2RQ_SEL14_SHIFT           (0)      /* Bits 0-9: D2Rq Sel14 */
#define INTC_DM2SEL7_D2RQ_SEL14_MASK            (0x3ff << INTC_DM2SEL7_D2RQ_SEL14_SHIFT)

#define INTC_DM2SEL7_D2SEL_CLRON14              (1 << 15)  /* D2Sel Clron14 */

#define INTC_DM2SEL7_D2RQ_SEL15_SHIFT           (16)      /* Bits 16-25: D2Rq Sel15 */
#define INTC_DM2SEL7_D2RQ_SEL15_MASK            (0x3ff << INTC_DM2SEL7_D2RQ_SEL15_SHIFT)

#define INTC_DM2SEL7_D2SEL_CLRON15              (1 << 31)  /* D2Sel Clron15 */

/* INTC DM3SEL0 Register Bit Definitions *****************************/

#define INTC_DM3SEL0_D3RQ_SEL0_SHIFT            (0)      /* Bits 0-7: D3Rq Sel0 */
#define INTC_DM3SEL0_D3RQ_SEL0_MASK             (0xff << INTC_DM3SEL0_D3RQ_SEL0_SHIFT)

#define INTC_DM3SEL0_D3RQ_SEL_SHIFT             (8)      /* Bits 8-9: D3Rq Sel */
#define INTC_DM3SEL0_D3RQ_SEL_MASK              (0x3 << INTC_DM3SEL0_D3RQ_SEL_SHIFT)

#define INTC_DM3SEL0_D3SEL_CLRON                (1 << 15)  /* D3Sel Clron */

#define INTC_DM3SEL0_D3RQ_SEL1_SHIFT            (16)      /* Bits 16-25: D3Rq Sel1 */
#define INTC_DM3SEL0_D3RQ_SEL1_MASK             (0x3ff << INTC_DM3SEL0_D3RQ_SEL1_SHIFT)

#define INTC_DM3SEL0_D3SEL_CLRON1               (1 << 31)  /* D3Sel Clron1 */

/* INTC DM3SEL1 Register Bit Definitions *****************************/

#define INTC_DM3SEL1_D3RQ_SEL2_SHIFT            (0)      /* Bits 0-9: D3Rq Sel2 */
#define INTC_DM3SEL1_D3RQ_SEL2_MASK             (0x3ff << INTC_DM3SEL1_D3RQ_SEL2_SHIFT)

#define INTC_DM3SEL1_D3SEL_CLRON2               (1 << 15)  /* D3Sel Clron2 */

#define INTC_DM3SEL1_D3RQ_SEL3_SHIFT            (16)      /* Bits 16-25: D3Rq Sel3 */
#define INTC_DM3SEL1_D3RQ_SEL3_MASK             (0x3ff << INTC_DM3SEL1_D3RQ_SEL3_SHIFT)

#define INTC_DM3SEL1_D3SEL_CLRON3               (1 << 31)  /* D3Sel Clron3 */

/* INTC DM3SEL2 Register Bit Definitions *****************************/

#define INTC_DM3SEL2_D3RQ_SEL4_SHIFT            (0)      /* Bits 0-9: D3Rq Sel4 */
#define INTC_DM3SEL2_D3RQ_SEL4_MASK             (0x3ff << INTC_DM3SEL2_D3RQ_SEL4_SHIFT)

#define INTC_DM3SEL2_D3SEL_CLRON4               (1 << 15)  /* D3Sel Clron4 */

#define INTC_DM3SEL2_D3RQ_SEL5_SHIFT            (16)      /* Bits 16-25: D3Rq Sel5 */
#define INTC_DM3SEL2_D3RQ_SEL5_MASK             (0x3ff << INTC_DM3SEL2_D3RQ_SEL5_SHIFT)

#define INTC_DM3SEL2_D3SEL_CLRON5               (1 << 31)  /* D3Sel Clron5 */

/* INTC DM3SEL3 Register Bit Definitions *****************************/

#define INTC_DM3SEL3_D3RQ_SEL6_SHIFT            (0)      /* Bits 0-9: D3Rq Sel6 */
#define INTC_DM3SEL3_D3RQ_SEL6_MASK             (0x3ff << INTC_DM3SEL3_D3RQ_SEL6_SHIFT)

#define INTC_DM3SEL3_D3SEL_CLRON6               (1 << 15)  /* D3Sel Clron6 */

#define INTC_DM3SEL3_D3RQ_SEL7_SHIFT            (16)      /* Bits 16-25: D3Rq Sel7 */
#define INTC_DM3SEL3_D3RQ_SEL7_MASK             (0x3ff << INTC_DM3SEL3_D3RQ_SEL7_SHIFT)

#define INTC_DM3SEL3_D3SEL_CLRON7               (1 << 31)  /* D3Sel Clron7 */

/* INTC DM3SEL4 Register Bit Definitions *****************************/

#define INTC_DM3SEL4_D3RQ_SEL8_SHIFT            (0)      /* Bits 0-9: D3Rq Sel8 */
#define INTC_DM3SEL4_D3RQ_SEL8_MASK             (0x3ff << INTC_DM3SEL4_D3RQ_SEL8_SHIFT)

#define INTC_DM3SEL4_D3SEL_CLRON8               (1 << 15)  /* D3Sel Clron8 */

#define INTC_DM3SEL4_D3RQ_SEL9_SHIFT            (16)      /* Bits 16-25: D3Rq Sel9 */
#define INTC_DM3SEL4_D3RQ_SEL9_MASK             (0x3ff << INTC_DM3SEL4_D3RQ_SEL9_SHIFT)

#define INTC_DM3SEL4_D3SEL_CLRON9               (1 << 31)  /* D3Sel Clron9 */

/* INTC DM3SEL5 Register Bit Definitions *****************************/

#define INTC_DM3SEL5_D3RQ_SEL10_SHIFT           (0)      /* Bits 0-9: D3Rq Sel10 */
#define INTC_DM3SEL5_D3RQ_SEL10_MASK            (0x3ff << INTC_DM3SEL5_D3RQ_SEL10_SHIFT)

#define INTC_DM3SEL5_D3SEL_CLRON10              (1 << 15)  /* D3Sel Clron10 */

#define INTC_DM3SEL5_D3RQ_SEL11_SHIFT           (16)      /* Bits 16-25: D3Rq Sel11 */
#define INTC_DM3SEL5_D3RQ_SEL11_MASK            (0x3ff << INTC_DM3SEL5_D3RQ_SEL11_SHIFT)

#define INTC_DM3SEL5_D3SEL_CLRON11              (1 << 31)  /* D3Sel Clron11 */

/* INTC DM3SEL6 Register Bit Definitions *****************************/

#define INTC_DM3SEL6_D3RQ_SEL12_SHIFT           (0)      /* Bits 0-9: D3Rq Sel12 */
#define INTC_DM3SEL6_D3RQ_SEL12_MASK            (0x3ff << INTC_DM3SEL6_D3RQ_SEL12_SHIFT)

#define INTC_DM3SEL6_D3SEL_CLRON12              (1 << 15)  /* D3Sel Clron12 */

#define INTC_DM3SEL6_D3RQ_SEL13_SHIFT           (16)      /* Bits 16-25: D3Rq Sel13 */
#define INTC_DM3SEL6_D3RQ_SEL13_MASK            (0x3ff << INTC_DM3SEL6_D3RQ_SEL13_SHIFT)

#define INTC_DM3SEL6_D3SEL_CLRON13              (1 << 31)  /* D3Sel Clron13 */

/* INTC DM3SEL7 Register Bit Definitions *****************************/

#define INTC_DM3SEL7_D3RQ_SEL14_SHIFT           (0)      /* Bits 0-9: D3Rq Sel14 */
#define INTC_DM3SEL7_D3RQ_SEL14_MASK            (0x3ff << INTC_DM3SEL7_D3RQ_SEL14_SHIFT)

#define INTC_DM3SEL7_D3SEL_CLRON14              (1 << 15)  /* D3Sel Clron14 */

#define INTC_DM3SEL7_D3RQ_SEL15_SHIFT           (16)      /* Bits 16-25: D3Rq Sel15 */
#define INTC_DM3SEL7_D3RQ_SEL15_MASK            (0x3ff << INTC_DM3SEL7_D3RQ_SEL15_SHIFT)

#define INTC_DM3SEL7_D3SEL_CLRON15              (1 << 31)  /* D3Sel Clron15 */

/* INTC DM4SEL0 Register Bit Definitions *****************************/

#define INTC_DM4SEL0_D4RQ_SEL0_SHIFT            (0)      /* Bits 0-7: D4Rq Sel0 */
#define INTC_DM4SEL0_D4RQ_SEL0_MASK             (0xff << INTC_DM4SEL0_D4RQ_SEL0_SHIFT)

#define INTC_DM4SEL0_D4RQ_SEL_SHIFT             (8)      /* Bits 8-9: D4Rq Sel */
#define INTC_DM4SEL0_D4RQ_SEL_MASK              (0x3 << INTC_DM4SEL0_D4RQ_SEL_SHIFT)

#define INTC_DM4SEL0_D4SEL_CLRON                (1 << 15)  /* D4Sel Clron */

#define INTC_DM4SEL0_D4RQ_SEL1_SHIFT            (16)      /* Bits 16-25: D4Rq Sel1 */
#define INTC_DM4SEL0_D4RQ_SEL1_MASK             (0x3ff << INTC_DM4SEL0_D4RQ_SEL1_SHIFT)

#define INTC_DM4SEL0_D4SEL_CLRON1               (1 << 31)  /* D4Sel Clron1 */

/* INTC DM4SEL1 Register Bit Definitions *****************************/

#define INTC_DM4SEL1_D4RQ_SEL2_SHIFT            (0)      /* Bits 0-9: D4Rq Sel2 */
#define INTC_DM4SEL1_D4RQ_SEL2_MASK             (0x3ff << INTC_DM4SEL1_D4RQ_SEL2_SHIFT)

#define INTC_DM4SEL1_D4SEL_CLRON2               (1 << 15)  /* D4Sel Clron2 */

#define INTC_DM4SEL1_D4RQ_SEL3_SHIFT            (16)      /* Bits 16-25: D4Rq Sel3 */
#define INTC_DM4SEL1_D4RQ_SEL3_MASK             (0x3ff << INTC_DM4SEL1_D4RQ_SEL3_SHIFT)

#define INTC_DM4SEL1_D4SEL_CLRON3               (1 << 31)  /* D4Sel Clron3 */

/* INTC DM4SEL2 Register Bit Definitions *****************************/

#define INTC_DM4SEL2_D4RQ_SEL4_SHIFT            (0)      /* Bits 0-9: D4Rq Sel4 */
#define INTC_DM4SEL2_D4RQ_SEL4_MASK             (0x3ff << INTC_DM4SEL2_D4RQ_SEL4_SHIFT)

#define INTC_DM4SEL2_D4SEL_CLRON4               (1 << 15)  /* D4Sel Clron4 */

#define INTC_DM4SEL2_D4RQ_SEL5_SHIFT            (16)      /* Bits 16-25: D4Rq Sel5 */
#define INTC_DM4SEL2_D4RQ_SEL5_MASK             (0x3ff << INTC_DM4SEL2_D4RQ_SEL5_SHIFT)

#define INTC_DM4SEL2_D4SEL_CLRON5               (1 << 31)  /* D4Sel Clron5 */

/* INTC DM4SEL3 Register Bit Definitions *****************************/

#define INTC_DM4SEL3_D4RQ_SEL6_SHIFT            (0)      /* Bits 0-9: D4Rq Sel6 */
#define INTC_DM4SEL3_D4RQ_SEL6_MASK             (0x3ff << INTC_DM4SEL3_D4RQ_SEL6_SHIFT)

#define INTC_DM4SEL3_D4SEL_CLRON6               (1 << 15)  /* D4Sel Clron6 */

#define INTC_DM4SEL3_D4RQ_SEL7_SHIFT            (16)      /* Bits 16-25: D4Rq Sel7 */
#define INTC_DM4SEL3_D4RQ_SEL7_MASK             (0x3ff << INTC_DM4SEL3_D4RQ_SEL7_SHIFT)

#define INTC_DM4SEL3_D4SEL_CLRON7               (1 << 31)  /* D4Sel Clron7 */

/* INTC DM4SEL4 Register Bit Definitions *****************************/

#define INTC_DM4SEL4_D4RQ_SEL8_SHIFT            (0)      /* Bits 0-9: D4Rq Sel8 */
#define INTC_DM4SEL4_D4RQ_SEL8_MASK             (0x3ff << INTC_DM4SEL4_D4RQ_SEL8_SHIFT)

#define INTC_DM4SEL4_D4SEL_CLRON8               (1 << 15)  /* D4Sel Clron8 */

#define INTC_DM4SEL4_D4RQ_SEL9_SHIFT            (16)      /* Bits 16-25: D4Rq Sel9 */
#define INTC_DM4SEL4_D4RQ_SEL9_MASK             (0x3ff << INTC_DM4SEL4_D4RQ_SEL9_SHIFT)

#define INTC_DM4SEL4_D4SEL_CLRON9               (1 << 31)  /* D4Sel Clron9 */

/* INTC DM4SEL5 Register Bit Definitions *****************************/

#define INTC_DM4SEL5_D4RQ_SEL10_SHIFT           (0)      /* Bits 0-9: D4Rq Sel10 */
#define INTC_DM4SEL5_D4RQ_SEL10_MASK            (0x3ff << INTC_DM4SEL5_D4RQ_SEL10_SHIFT)

#define INTC_DM4SEL5_D4SEL_CLRON10              (1 << 15)  /* D4Sel Clron10 */

#define INTC_DM4SEL5_D4RQ_SEL11_SHIFT           (16)      /* Bits 16-25: D4Rq Sel11 */
#define INTC_DM4SEL5_D4RQ_SEL11_MASK            (0x3ff << INTC_DM4SEL5_D4RQ_SEL11_SHIFT)

#define INTC_DM4SEL5_D4SEL_CLRON11              (1 << 31)  /* D4Sel Clron11 */

/* INTC DM4SEL6 Register Bit Definitions *****************************/

#define INTC_DM4SEL6_D4RQ_SEL12_SHIFT           (0)      /* Bits 0-9: D4Rq Sel12 */
#define INTC_DM4SEL6_D4RQ_SEL12_MASK            (0x3ff << INTC_DM4SEL6_D4RQ_SEL12_SHIFT)

#define INTC_DM4SEL6_D4SEL_CLRON12              (1 << 15)  /* D4Sel Clron12 */

#define INTC_DM4SEL6_D4RQ_SEL13_SHIFT           (16)      /* Bits 16-25: D4Rq Sel13 */
#define INTC_DM4SEL6_D4RQ_SEL13_MASK            (0x3ff << INTC_DM4SEL6_D4RQ_SEL13_SHIFT)

#define INTC_DM4SEL6_D4SEL_CLRON13              (1 << 31)  /* D4Sel Clron13 */

/* INTC DM4SEL7 Register Bit Definitions *****************************/

#define INTC_DM4SEL7_D4RQ_SEL14_SHIFT           (0)      /* Bits 0-9: D4Rq Sel14 */
#define INTC_DM4SEL7_D4RQ_SEL14_MASK            (0x3ff << INTC_DM4SEL7_D4RQ_SEL14_SHIFT)

#define INTC_DM4SEL7_D4SEL_CLRON14              (1 << 15)  /* D4Sel Clron14 */

#define INTC_DM4SEL7_D4RQ_SEL15_SHIFT           (16)      /* Bits 16-25: D4Rq Sel15 */
#define INTC_DM4SEL7_D4RQ_SEL15_MASK            (0x3ff << INTC_DM4SEL7_D4RQ_SEL15_SHIFT)

#define INTC_DM4SEL7_D4SEL_CLRON15              (1 << 31)  /* D4Sel Clron15 */

/* INTC DMRCLR0 Register Bit Definitions *****************************/

#define INTC_DMRCLR0_DMADUPCLR0_n_SHIFT         (0)      /* Bits 0-31: Dmadupclr0 N */
#define INTC_DMRCLR0_DMADUPCLR0_n_MASK          (0xffffffff << INTC_DMRCLR0_DMADUPCLR0_n_SHIFT)

/* INTC DMRCLR1 Register Bit Definitions *****************************/

#define INTC_DMRCLR1_DMADUPCLR1_n_SHIFT         (0)      /* Bits 0-31: Dmadupclr1 N */
#define INTC_DMRCLR1_DMADUPCLR1_n_MASK          (0xffffffff << INTC_DMRCLR1_DMADUPCLR1_n_SHIFT)

/* INTC DMRCLR2 Register Bit Definitions *****************************/

#define INTC_DMRCLR2_DMADUPCLR2_n_SHIFT         (0)      /* Bits 0-31: Dmadupclr2 N */
#define INTC_DMRCLR2_DMADUPCLR2_n_MASK          (0xffffffff << INTC_DMRCLR2_DMADUPCLR2_n_SHIFT)

/* INTC DRCLR Register Bit Definitions *******************************/

/* DRCLR fields (parameterized for indices 0-4) */
#define INTC_DRCLR_DRCLR(n)                               (1u << (0 + ((unsigned)(n) * 1)))  /* Drclr0 */

/* INTC DRCTR Register Bit Definitions *******************************/

/* DRSTAT fields (parameterized for indices 0-4) */
#define INTC_DRCTR_DRSTAT(n)                              (1u << (0 + ((unsigned)(n) * 1)))  /* Drstat0 */

/* INTC DRTSR Register Bit Definitions *******************************/

/* DRITSEL fields (parameterized for indices 0-4) */
#define INTC_DRTSR_DRITSEL_SHIFT(n)                       ((unsigned)(0 + ((n) * 2)))  /* Bits for DRITSELn */
#define INTC_DRTSR_DRITSEL_MASK(n)                        (0x3u << INTC_DRTSR_DRITSEL_SHIFT(n))
#define INTC_DRTSR_DRITSEL_VAL(n,v)                       (((unsigned)(v) & 0x3u) << INTC_DRTSR_DRITSEL_SHIFT(n))

/* INTC ERINTA55CLR0 Register Bit Definitions ************************/

#define INTC_ERINTA55CLR0_ERRA50CLRn_SHIFT      (0)      /* Bits 0-31: Erra50Clrn */
#define INTC_ERINTA55CLR0_ERRA50CLRn_MASK       (0xffffffff << INTC_ERINTA55CLR0_ERRA50CLRn_SHIFT)

/* INTC ERINTA55CLR1 Register Bit Definitions ************************/

#define INTC_ERINTA55CLR1_ERRA51CLRn_SHIFT      (0)      /* Bits 0-31: Erra51Clrn */
#define INTC_ERINTA55CLR1_ERRA51CLRn_MASK       (0xffffffff << INTC_ERINTA55CLR1_ERRA51CLRn_SHIFT)

/* INTC ERINTA55CLR2 Register Bit Definitions ************************/

#define INTC_ERINTA55CLR2_ERRA52CLRn_SHIFT      (0)      /* Bits 0-31: Erra52Clrn */
#define INTC_ERINTA55CLR2_ERRA52CLRn_MASK       (0xffffffff << INTC_ERINTA55CLR2_ERRA52CLRn_SHIFT)

/* INTC ERINTA55CLR3 Register Bit Definitions ************************/

#define INTC_ERINTA55CLR3_ERRA53CLRn_SHIFT      (0)      /* Bits 0-31: Erra53Clrn */
#define INTC_ERINTA55CLR3_ERRA53CLRn_MASK       (0xffffffff << INTC_ERINTA55CLR3_ERRA53CLRn_SHIFT)

/* INTC ERINTA55CTL0 Register Bit Definitions ************************/

#define INTC_ERINTA55CTL0_ERR0STATn_SHIFT       (0)      /* Bits 0-31: Err0Statn */
#define INTC_ERINTA55CTL0_ERR0STATn_MASK        (0xffffffff << INTC_ERINTA55CTL0_ERR0STATn_SHIFT)

/* INTC ERINTA55CTL1 Register Bit Definitions ************************/

#define INTC_ERINTA55CTL1_ERR1STATn_SHIFT       (0)      /* Bits 0-31: Err1Statn */
#define INTC_ERINTA55CTL1_ERR1STATn_MASK        (0xffffffff << INTC_ERINTA55CTL1_ERR1STATn_SHIFT)

/* INTC ERINTA55CTL2 Register Bit Definitions ************************/

#define INTC_ERINTA55CTL2_ERR2STATn_SHIFT       (0)      /* Bits 0-31: Err2Statn */
#define INTC_ERINTA55CTL2_ERR2STATn_MASK        (0xffffffff << INTC_ERINTA55CTL2_ERR2STATn_SHIFT)

/* INTC ERINTA55CTL3 Register Bit Definitions ************************/

#define INTC_ERINTA55CTL3_ERR3STATn_SHIFT       (0)      /* Bits 0-31: Err3Statn */
#define INTC_ERINTA55CTL3_ERR3STATn_MASK        (0xffffffff << INTC_ERINTA55CTL3_ERR3STATn_SHIFT)

/* INTC ERINTA55MSK0 Register Bit Definitions ************************/

#define INTC_ERINTA55MSK0_ERRM30MKn_SHIFT       (0)      /* Bits 0-31: Errm30Mkn */
#define INTC_ERINTA55MSK0_ERRM30MKn_MASK        (0xffffffff << INTC_ERINTA55MSK0_ERRM30MKn_SHIFT)

/* INTC ERINTA55MSK1 Register Bit Definitions ************************/

#define INTC_ERINTA55MSK1_ERRM31MKn_SHIFT       (0)      /* Bits 0-31: Errm31Mkn */
#define INTC_ERINTA55MSK1_ERRM31MKn_MASK        (0xffffffff << INTC_ERINTA55MSK1_ERRM31MKn_SHIFT)

/* INTC ERINTA55MSK2 Register Bit Definitions ************************/

#define INTC_ERINTA55MSK2_ERRM32MKn_SHIFT       (0)      /* Bits 0-31: Errm32Mkn */
#define INTC_ERINTA55MSK2_ERRM32MKn_MASK        (0xffffffff << INTC_ERINTA55MSK2_ERRM32MKn_SHIFT)

/* INTC ERINTA55MSK3 Register Bit Definitions ************************/

#define INTC_ERINTA55MSK3_ERRM33MKn_SHIFT       (0)      /* Bits 0-31: Errm33Mkn */
#define INTC_ERINTA55MSK3_ERRM33MKn_MASK        (0xffffffff << INTC_ERINTA55MSK3_ERRM33MKn_SHIFT)

/* INTC ERINTM33CLR0 Register Bit Definitions ************************/

#define INTC_ERINTM33CLR0_ERRM30CLRn_SHIFT      (0)      /* Bits 0-31: Errm30Clrn */
#define INTC_ERINTM33CLR0_ERRM30CLRn_MASK       (0xffffffff << INTC_ERINTM33CLR0_ERRM30CLRn_SHIFT)

/* INTC ERINTM33CLR1 Register Bit Definitions ************************/

#define INTC_ERINTM33CLR1_ERRM31CLRn_SHIFT      (0)      /* Bits 0-31: Errm31Clrn */
#define INTC_ERINTM33CLR1_ERRM31CLRn_MASK       (0xffffffff << INTC_ERINTM33CLR1_ERRM31CLRn_SHIFT)

/* INTC ERINTM33CLR2 Register Bit Definitions ************************/

#define INTC_ERINTM33CLR2_ERRM32CLRn_SHIFT      (0)      /* Bits 0-31: Errm32Clrn */
#define INTC_ERINTM33CLR2_ERRM32CLRn_MASK       (0xffffffff << INTC_ERINTM33CLR2_ERRM32CLRn_SHIFT)

/* INTC ERINTM33CLR3 Register Bit Definitions ************************/

#define INTC_ERINTM33CLR3_ERRM33CLRn_SHIFT      (0)      /* Bits 0-31: Errm33Clrn */
#define INTC_ERINTM33CLR3_ERRM33CLRn_MASK       (0xffffffff << INTC_ERINTM33CLR3_ERRM33CLRn_SHIFT)

/* INTC ERINTM33CTL0 Register Bit Definitions ************************/

#define INTC_ERINTM33CTL0_ERRM30STATn_SHIFT     (0)      /* Bits 0-31: Errm30Statn */
#define INTC_ERINTM33CTL0_ERRM30STATn_MASK      (0xffffffff << INTC_ERINTM33CTL0_ERRM30STATn_SHIFT)

/* INTC ERINTM33CTL1 Register Bit Definitions ************************/

#define INTC_ERINTM33CTL1_ERRM31STATn_SHIFT     (0)      /* Bits 0-31: Errm31Statn */
#define INTC_ERINTM33CTL1_ERRM31STATn_MASK      (0xffffffff << INTC_ERINTM33CTL1_ERRM31STATn_SHIFT)

/* INTC ERINTM33CTL2 Register Bit Definitions ************************/

#define INTC_ERINTM33CTL2_ERRM32STATn_SHIFT     (0)      /* Bits 0-31: Errm32Statn */
#define INTC_ERINTM33CTL2_ERRM32STATn_MASK      (0xffffffff << INTC_ERINTM33CTL2_ERRM32STATn_SHIFT)

/* INTC ERINTM33CTL3 Register Bit Definitions ************************/

#define INTC_ERINTM33CTL3_ERRM33STATn_SHIFT     (0)      /* Bits 0-31: Errm33Statn */
#define INTC_ERINTM33CTL3_ERRM33STATn_MASK      (0xffffffff << INTC_ERINTM33CTL3_ERRM33STATn_SHIFT)

/* INTC ERINTM33MSK0 Register Bit Definitions ************************/

#define INTC_ERINTM33MSK0_ERRM30MKn_SHIFT       (0)      /* Bits 0-31: Errm30Mkn */
#define INTC_ERINTM33MSK0_ERRM30MKn_MASK        (0xffffffff << INTC_ERINTM33MSK0_ERRM30MKn_SHIFT)

/* INTC ERINTM33MSK1 Register Bit Definitions ************************/

#define INTC_ERINTM33MSK1_ERRM31MKn_SHIFT       (0)      /* Bits 0-31: Errm31Mkn */
#define INTC_ERINTM33MSK1_ERRM31MKn_MASK        (0xffffffff << INTC_ERINTM33MSK1_ERRM31MKn_SHIFT)

/* INTC ERINTM33MSK2 Register Bit Definitions ************************/

#define INTC_ERINTM33MSK2_ERRM32MKn_SHIFT       (0)      /* Bits 0-31: Errm32Mkn */
#define INTC_ERINTM33MSK2_ERRM32MKn_MASK        (0xffffffff << INTC_ERINTM33MSK2_ERRM32MKn_SHIFT)

/* INTC ERINTM33MSK3 Register Bit Definitions ************************/

#define INTC_ERINTM33MSK3_ERRM33MKn_SHIFT       (0)      /* Bits 0-31: Errm33Mkn */
#define INTC_ERINTM33MSK3_ERRM33MKn_MASK        (0xffffffff << INTC_ERINTM33MSK3_ERRM33MKn_SHIFT)

/* INTC GPTINTA55CLR Register Bit Definitions ************************/

#define INTC_GPTINTA55CLR_G0IADBxCLR_SHIFT      (0)      /* Bits 0-7: G0Iadbxclr */
#define INTC_GPTINTA55CLR_G0IADBxCLR_MASK       (0xff << INTC_GPTINTA55CLR_G0IADBxCLR_SHIFT)

#define INTC_GPTINTA55CLR_G0IADAxCLR_SHIFT      (8)      /* Bits 8-15: G0Iadaxclr */
#define INTC_GPTINTA55CLR_G0IADAxCLR_MASK       (0xff << INTC_GPTINTA55CLR_G0IADAxCLR_SHIFT)

#define INTC_GPTINTA55CLR_G1IADBxCLR_SHIFT      (16)      /* Bits 16-23: G1Iadbxclr */
#define INTC_GPTINTA55CLR_G1IADBxCLR_MASK       (0xff << INTC_GPTINTA55CLR_G1IADBxCLR_SHIFT)

#define INTC_GPTINTA55CLR_G1IADAxCLR_SHIFT      (24)      /* Bits 24-31: G1Iadaxclr */
#define INTC_GPTINTA55CLR_G1IADAxCLR_MASK       (0xff << INTC_GPTINTA55CLR_G1IADAxCLR_SHIFT)

/* INTC GPTINTA55CTL Register Bit Definitions ************************/

#define INTC_GPTINTA55CTL_G0IADBx_SHIFT         (0)      /* Bits 0-7: G0Iadbx */
#define INTC_GPTINTA55CTL_G0IADBx_MASK          (0xff << INTC_GPTINTA55CTL_G0IADBx_SHIFT)

#define INTC_GPTINTA55CTL_G0IADAx_SHIFT         (8)      /* Bits 8-15: G0Iadax */
#define INTC_GPTINTA55CTL_G0IADAx_MASK          (0xff << INTC_GPTINTA55CTL_G0IADAx_SHIFT)

#define INTC_GPTINTA55CTL_G1IADBx_SHIFT         (16)      /* Bits 16-23: G1Iadbx */
#define INTC_GPTINTA55CTL_G1IADBx_MASK          (0xff << INTC_GPTINTA55CTL_G1IADBx_SHIFT)

#define INTC_GPTINTA55CTL_G1IADAx_SHIFT         (24)      /* Bits 24-31: G1Iadax */
#define INTC_GPTINTA55CTL_G1IADAx_MASK          (0xff << INTC_GPTINTA55CTL_G1IADAx_SHIFT)

/* INTC IITSR Register Bit Definitions *******************************/

/* IITSEL fields (parameterized for indices 0-15) */
#define INTC_IITSR_IITSEL_SHIFT(n)                        ((unsigned)(0 + ((n) * 2)))  /* Bits for IITSELn */
#define INTC_IITSR_IITSEL_MASK(n)                         (0x3u << INTC_IITSR_IITSEL_SHIFT(n))
#define INTC_IITSR_IITSEL_VAL(n,v)                        (((unsigned)(v) & 0x3u) << INTC_IITSR_IITSEL_SHIFT(n))

/* INTC INTM33SEL0 Register Bit Definitions **************************/

#define INTC_INTM33SEL0_M33SPI0_SEL0_SHIFT      (0)      /* Bits 0-9: M33Spi0 Sel0 */
#define INTC_INTM33SEL0_M33SPI0_SEL0_MASK       (0x3ff << INTC_INTM33SEL0_M33SPI0_SEL0_SHIFT)

#define INTC_INTM33SEL0_M33SPI0_SEL1_SHIFT      (10)      /* Bits 10-19: M33Spi0 Sel1 */
#define INTC_INTM33SEL0_M33SPI0_SEL1_MASK       (0x3ff << INTC_INTM33SEL0_M33SPI0_SEL1_SHIFT)

#define INTC_INTM33SEL0_M33SPI0_SEL2_SHIFT      (20)      /* Bits 20-29: M33Spi0 Sel2 */
#define INTC_INTM33SEL0_M33SPI0_SEL2_MASK       (0x3ff << INTC_INTM33SEL0_M33SPI0_SEL2_SHIFT)

/* INTC INTM33SEL1 Register Bit Definitions **************************/

#define INTC_INTM33SEL1_M33SPI1_SEL0_SHIFT      (0)      /* Bits 0-9: M33Spi1 Sel0 */
#define INTC_INTM33SEL1_M33SPI1_SEL0_MASK       (0x3ff << INTC_INTM33SEL1_M33SPI1_SEL0_SHIFT)

#define INTC_INTM33SEL1_M33SPI1_SEL1_SHIFT      (10)      /* Bits 10-19: M33Spi1 Sel1 */
#define INTC_INTM33SEL1_M33SPI1_SEL1_MASK       (0x3ff << INTC_INTM33SEL1_M33SPI1_SEL1_SHIFT)

#define INTC_INTM33SEL1_M33SPI1_SEL2_SHIFT      (20)      /* Bits 20-29: M33Spi1 Sel2 */
#define INTC_INTM33SEL1_M33SPI1_SEL2_MASK       (0x3ff << INTC_INTM33SEL1_M33SPI1_SEL2_SHIFT)

/* INTC INTM33SEL10 Register Bit Definitions *************************/

#define INTC_INTM33SEL10_M33SPI10_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi10 Sel0 */
#define INTC_INTM33SEL10_M33SPI10_SEL0_MASK     (0x3ff << INTC_INTM33SEL10_M33SPI10_SEL0_SHIFT)

#define INTC_INTM33SEL10_M33SPI10_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi10 Sel1 */
#define INTC_INTM33SEL10_M33SPI10_SEL1_MASK     (0x3ff << INTC_INTM33SEL10_M33SPI10_SEL1_SHIFT)

#define INTC_INTM33SEL10_M33SPI10_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi10 Sel2 */
#define INTC_INTM33SEL10_M33SPI10_SEL2_MASK     (0x3ff << INTC_INTM33SEL10_M33SPI10_SEL2_SHIFT)

/* INTC INTM33SEL11 Register Bit Definitions *************************/

#define INTC_INTM33SEL11_M33SPI11_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi11 Sel0 */
#define INTC_INTM33SEL11_M33SPI11_SEL0_MASK     (0x3ff << INTC_INTM33SEL11_M33SPI11_SEL0_SHIFT)

#define INTC_INTM33SEL11_M33SPI11_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi11 Sel1 */
#define INTC_INTM33SEL11_M33SPI11_SEL1_MASK     (0x3ff << INTC_INTM33SEL11_M33SPI11_SEL1_SHIFT)

#define INTC_INTM33SEL11_M33SPI11_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi11 Sel2 */
#define INTC_INTM33SEL11_M33SPI11_SEL2_MASK     (0x3ff << INTC_INTM33SEL11_M33SPI11_SEL2_SHIFT)

/* INTC INTM33SEL12 Register Bit Definitions *************************/

#define INTC_INTM33SEL12_M33SPI12_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi12 Sel0 */
#define INTC_INTM33SEL12_M33SPI12_SEL0_MASK     (0x3ff << INTC_INTM33SEL12_M33SPI12_SEL0_SHIFT)

#define INTC_INTM33SEL12_M33SPI12_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi12 Sel1 */
#define INTC_INTM33SEL12_M33SPI12_SEL1_MASK     (0x3ff << INTC_INTM33SEL12_M33SPI12_SEL1_SHIFT)

#define INTC_INTM33SEL12_M33SPI12_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi12 Sel2 */
#define INTC_INTM33SEL12_M33SPI12_SEL2_MASK     (0x3ff << INTC_INTM33SEL12_M33SPI12_SEL2_SHIFT)

/* INTC INTM33SEL13 Register Bit Definitions *************************/

#define INTC_INTM33SEL13_M33SPI13_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi13 Sel0 */
#define INTC_INTM33SEL13_M33SPI13_SEL0_MASK     (0x3ff << INTC_INTM33SEL13_M33SPI13_SEL0_SHIFT)

#define INTC_INTM33SEL13_M33SPI13_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi13 Sel1 */
#define INTC_INTM33SEL13_M33SPI13_SEL1_MASK     (0x3ff << INTC_INTM33SEL13_M33SPI13_SEL1_SHIFT)

#define INTC_INTM33SEL13_M33SPI13_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi13 Sel2 */
#define INTC_INTM33SEL13_M33SPI13_SEL2_MASK     (0x3ff << INTC_INTM33SEL13_M33SPI13_SEL2_SHIFT)

/* INTC INTM33SEL14 Register Bit Definitions *************************/

#define INTC_INTM33SEL14_M33SPI14_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi14 Sel0 */
#define INTC_INTM33SEL14_M33SPI14_SEL0_MASK     (0x3ff << INTC_INTM33SEL14_M33SPI14_SEL0_SHIFT)

#define INTC_INTM33SEL14_M33SPI14_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi14 Sel1 */
#define INTC_INTM33SEL14_M33SPI14_SEL1_MASK     (0x3ff << INTC_INTM33SEL14_M33SPI14_SEL1_SHIFT)

#define INTC_INTM33SEL14_M33SPI14_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi14 Sel2 */
#define INTC_INTM33SEL14_M33SPI14_SEL2_MASK     (0x3ff << INTC_INTM33SEL14_M33SPI14_SEL2_SHIFT)

/* INTC INTM33SEL15 Register Bit Definitions *************************/

#define INTC_INTM33SEL15_M33SPI15_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi15 Sel0 */
#define INTC_INTM33SEL15_M33SPI15_SEL0_MASK     (0x3ff << INTC_INTM33SEL15_M33SPI15_SEL0_SHIFT)

#define INTC_INTM33SEL15_M33SPI15_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi15 Sel1 */
#define INTC_INTM33SEL15_M33SPI15_SEL1_MASK     (0x3ff << INTC_INTM33SEL15_M33SPI15_SEL1_SHIFT)

#define INTC_INTM33SEL15_M33SPI15_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi15 Sel2 */
#define INTC_INTM33SEL15_M33SPI15_SEL2_MASK     (0x3ff << INTC_INTM33SEL15_M33SPI15_SEL2_SHIFT)

/* INTC INTM33SEL16 Register Bit Definitions *************************/

#define INTC_INTM33SEL16_M33SPI16_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi16 Sel0 */
#define INTC_INTM33SEL16_M33SPI16_SEL0_MASK     (0x3ff << INTC_INTM33SEL16_M33SPI16_SEL0_SHIFT)

#define INTC_INTM33SEL16_M33SPI16_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi16 Sel1 */
#define INTC_INTM33SEL16_M33SPI16_SEL1_MASK     (0x3ff << INTC_INTM33SEL16_M33SPI16_SEL1_SHIFT)

#define INTC_INTM33SEL16_M33SPI16_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi16 Sel2 */
#define INTC_INTM33SEL16_M33SPI16_SEL2_MASK     (0x3ff << INTC_INTM33SEL16_M33SPI16_SEL2_SHIFT)

/* INTC INTM33SEL17 Register Bit Definitions *************************/

#define INTC_INTM33SEL17_M33SPI17_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi17 Sel0 */
#define INTC_INTM33SEL17_M33SPI17_SEL0_MASK     (0x3ff << INTC_INTM33SEL17_M33SPI17_SEL0_SHIFT)

#define INTC_INTM33SEL17_M33SPI17_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi17 Sel1 */
#define INTC_INTM33SEL17_M33SPI17_SEL1_MASK     (0x3ff << INTC_INTM33SEL17_M33SPI17_SEL1_SHIFT)

#define INTC_INTM33SEL17_M33SPI17_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi17 Sel2 */
#define INTC_INTM33SEL17_M33SPI17_SEL2_MASK     (0x3ff << INTC_INTM33SEL17_M33SPI17_SEL2_SHIFT)

/* INTC INTM33SEL18 Register Bit Definitions *************************/

#define INTC_INTM33SEL18_M33SPI18_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi18 Sel0 */
#define INTC_INTM33SEL18_M33SPI18_SEL0_MASK     (0x3ff << INTC_INTM33SEL18_M33SPI18_SEL0_SHIFT)

#define INTC_INTM33SEL18_M33SPI18_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi18 Sel1 */
#define INTC_INTM33SEL18_M33SPI18_SEL1_MASK     (0x3ff << INTC_INTM33SEL18_M33SPI18_SEL1_SHIFT)

#define INTC_INTM33SEL18_M33SPI18_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi18 Sel2 */
#define INTC_INTM33SEL18_M33SPI18_SEL2_MASK     (0x3ff << INTC_INTM33SEL18_M33SPI18_SEL2_SHIFT)

/* INTC INTM33SEL19 Register Bit Definitions *************************/

#define INTC_INTM33SEL19_M33SPI19_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi19 Sel0 */
#define INTC_INTM33SEL19_M33SPI19_SEL0_MASK     (0x3ff << INTC_INTM33SEL19_M33SPI19_SEL0_SHIFT)

#define INTC_INTM33SEL19_M33SPI19_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi19 Sel1 */
#define INTC_INTM33SEL19_M33SPI19_SEL1_MASK     (0x3ff << INTC_INTM33SEL19_M33SPI19_SEL1_SHIFT)

#define INTC_INTM33SEL19_M33SPI19_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi19 Sel2 */
#define INTC_INTM33SEL19_M33SPI19_SEL2_MASK     (0x3ff << INTC_INTM33SEL19_M33SPI19_SEL2_SHIFT)

/* INTC INTM33SEL2 Register Bit Definitions **************************/

#define INTC_INTM33SEL2_M33SPI2_SEL0_SHIFT      (0)      /* Bits 0-9: M33Spi2 Sel0 */
#define INTC_INTM33SEL2_M33SPI2_SEL0_MASK       (0x3ff << INTC_INTM33SEL2_M33SPI2_SEL0_SHIFT)

#define INTC_INTM33SEL2_M33SPI2_SEL1_SHIFT      (10)      /* Bits 10-19: M33Spi2 Sel1 */
#define INTC_INTM33SEL2_M33SPI2_SEL1_MASK       (0x3ff << INTC_INTM33SEL2_M33SPI2_SEL1_SHIFT)

#define INTC_INTM33SEL2_M33SPI2_SEL2_SHIFT      (20)      /* Bits 20-29: M33Spi2 Sel2 */
#define INTC_INTM33SEL2_M33SPI2_SEL2_MASK       (0x3ff << INTC_INTM33SEL2_M33SPI2_SEL2_SHIFT)

/* INTC INTM33SEL20 Register Bit Definitions *************************/

#define INTC_INTM33SEL20_M33SPI20_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi20 Sel0 */
#define INTC_INTM33SEL20_M33SPI20_SEL0_MASK     (0x3ff << INTC_INTM33SEL20_M33SPI20_SEL0_SHIFT)

#define INTC_INTM33SEL20_M33SPI20_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi20 Sel1 */
#define INTC_INTM33SEL20_M33SPI20_SEL1_MASK     (0x3ff << INTC_INTM33SEL20_M33SPI20_SEL1_SHIFT)

#define INTC_INTM33SEL20_M33SPI20_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi20 Sel2 */
#define INTC_INTM33SEL20_M33SPI20_SEL2_MASK     (0x3ff << INTC_INTM33SEL20_M33SPI20_SEL2_SHIFT)

/* INTC INTM33SEL21 Register Bit Definitions *************************/

#define INTC_INTM33SEL21_M33SPI21_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi21 Sel0 */
#define INTC_INTM33SEL21_M33SPI21_SEL0_MASK     (0x3ff << INTC_INTM33SEL21_M33SPI21_SEL0_SHIFT)

#define INTC_INTM33SEL21_M33SPI21_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi21 Sel1 */
#define INTC_INTM33SEL21_M33SPI21_SEL1_MASK     (0x3ff << INTC_INTM33SEL21_M33SPI21_SEL1_SHIFT)

#define INTC_INTM33SEL21_M33SPI21_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi21 Sel2 */
#define INTC_INTM33SEL21_M33SPI21_SEL2_MASK     (0x3ff << INTC_INTM33SEL21_M33SPI21_SEL2_SHIFT)

/* INTC INTM33SEL22 Register Bit Definitions *************************/

#define INTC_INTM33SEL22_M33SPI22_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi22 Sel0 */
#define INTC_INTM33SEL22_M33SPI22_SEL0_MASK     (0x3ff << INTC_INTM33SEL22_M33SPI22_SEL0_SHIFT)

#define INTC_INTM33SEL22_M33SPI22_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi22 Sel1 */
#define INTC_INTM33SEL22_M33SPI22_SEL1_MASK     (0x3ff << INTC_INTM33SEL22_M33SPI22_SEL1_SHIFT)

#define INTC_INTM33SEL22_M33SPI22_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi22 Sel2 */
#define INTC_INTM33SEL22_M33SPI22_SEL2_MASK     (0x3ff << INTC_INTM33SEL22_M33SPI22_SEL2_SHIFT)

/* INTC INTM33SEL23 Register Bit Definitions *************************/

#define INTC_INTM33SEL23_M33SPI23_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi23 Sel0 */
#define INTC_INTM33SEL23_M33SPI23_SEL0_MASK     (0x3ff << INTC_INTM33SEL23_M33SPI23_SEL0_SHIFT)

#define INTC_INTM33SEL23_M33SPI23_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi23 Sel1 */
#define INTC_INTM33SEL23_M33SPI23_SEL1_MASK     (0x3ff << INTC_INTM33SEL23_M33SPI23_SEL1_SHIFT)

#define INTC_INTM33SEL23_M33SPI23_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi23 Sel2 */
#define INTC_INTM33SEL23_M33SPI23_SEL2_MASK     (0x3ff << INTC_INTM33SEL23_M33SPI23_SEL2_SHIFT)

/* INTC INTM33SEL24 Register Bit Definitions *************************/

#define INTC_INTM33SEL24_M33SPI24_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi24 Sel0 */
#define INTC_INTM33SEL24_M33SPI24_SEL0_MASK     (0x3ff << INTC_INTM33SEL24_M33SPI24_SEL0_SHIFT)

#define INTC_INTM33SEL24_M33SPI24_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi24 Sel1 */
#define INTC_INTM33SEL24_M33SPI24_SEL1_MASK     (0x3ff << INTC_INTM33SEL24_M33SPI24_SEL1_SHIFT)

#define INTC_INTM33SEL24_M33SPI24_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi24 Sel2 */
#define INTC_INTM33SEL24_M33SPI24_SEL2_MASK     (0x3ff << INTC_INTM33SEL24_M33SPI24_SEL2_SHIFT)

/* INTC INTM33SEL25 Register Bit Definitions *************************/

#define INTC_INTM33SEL25_M33SPI25_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi25 Sel0 */
#define INTC_INTM33SEL25_M33SPI25_SEL0_MASK     (0x3ff << INTC_INTM33SEL25_M33SPI25_SEL0_SHIFT)

#define INTC_INTM33SEL25_M33SPI25_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi25 Sel1 */
#define INTC_INTM33SEL25_M33SPI25_SEL1_MASK     (0x3ff << INTC_INTM33SEL25_M33SPI25_SEL1_SHIFT)

#define INTC_INTM33SEL25_M33SPI25_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi25 Sel2 */
#define INTC_INTM33SEL25_M33SPI25_SEL2_MASK     (0x3ff << INTC_INTM33SEL25_M33SPI25_SEL2_SHIFT)

/* INTC INTM33SEL26 Register Bit Definitions *************************/

#define INTC_INTM33SEL26_M33SPI26_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi26 Sel0 */
#define INTC_INTM33SEL26_M33SPI26_SEL0_MASK     (0x3ff << INTC_INTM33SEL26_M33SPI26_SEL0_SHIFT)

#define INTC_INTM33SEL26_M33SPI26_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi26 Sel1 */
#define INTC_INTM33SEL26_M33SPI26_SEL1_MASK     (0x3ff << INTC_INTM33SEL26_M33SPI26_SEL1_SHIFT)

#define INTC_INTM33SEL26_M33SPI26_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi26 Sel2 */
#define INTC_INTM33SEL26_M33SPI26_SEL2_MASK     (0x3ff << INTC_INTM33SEL26_M33SPI26_SEL2_SHIFT)

/* INTC INTM33SEL27 Register Bit Definitions *************************/

#define INTC_INTM33SEL27_M33SPI27_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi27 Sel0 */
#define INTC_INTM33SEL27_M33SPI27_SEL0_MASK     (0x3ff << INTC_INTM33SEL27_M33SPI27_SEL0_SHIFT)

#define INTC_INTM33SEL27_M33SPI27_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi27 Sel1 */
#define INTC_INTM33SEL27_M33SPI27_SEL1_MASK     (0x3ff << INTC_INTM33SEL27_M33SPI27_SEL1_SHIFT)

#define INTC_INTM33SEL27_M33SPI27_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi27 Sel2 */
#define INTC_INTM33SEL27_M33SPI27_SEL2_MASK     (0x3ff << INTC_INTM33SEL27_M33SPI27_SEL2_SHIFT)

/* INTC INTM33SEL28 Register Bit Definitions *************************/

#define INTC_INTM33SEL28_M33SPI28_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi28 Sel0 */
#define INTC_INTM33SEL28_M33SPI28_SEL0_MASK     (0x3ff << INTC_INTM33SEL28_M33SPI28_SEL0_SHIFT)

#define INTC_INTM33SEL28_M33SPI28_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi28 Sel1 */
#define INTC_INTM33SEL28_M33SPI28_SEL1_MASK     (0x3ff << INTC_INTM33SEL28_M33SPI28_SEL1_SHIFT)

#define INTC_INTM33SEL28_M33SPI28_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi28 Sel2 */
#define INTC_INTM33SEL28_M33SPI28_SEL2_MASK     (0x3ff << INTC_INTM33SEL28_M33SPI28_SEL2_SHIFT)

/* INTC INTM33SEL29 Register Bit Definitions *************************/

#define INTC_INTM33SEL29_M33SPI29_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi29 Sel0 */
#define INTC_INTM33SEL29_M33SPI29_SEL0_MASK     (0x3ff << INTC_INTM33SEL29_M33SPI29_SEL0_SHIFT)

#define INTC_INTM33SEL29_M33SPI29_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi29 Sel1 */
#define INTC_INTM33SEL29_M33SPI29_SEL1_MASK     (0x3ff << INTC_INTM33SEL29_M33SPI29_SEL1_SHIFT)

#define INTC_INTM33SEL29_M33SPI29_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi29 Sel2 */
#define INTC_INTM33SEL29_M33SPI29_SEL2_MASK     (0x3ff << INTC_INTM33SEL29_M33SPI29_SEL2_SHIFT)

/* INTC INTM33SEL3 Register Bit Definitions **************************/

#define INTC_INTM33SEL3_M33SPI3_SEL0_SHIFT      (0)      /* Bits 0-9: M33Spi3 Sel0 */
#define INTC_INTM33SEL3_M33SPI3_SEL0_MASK       (0x3ff << INTC_INTM33SEL3_M33SPI3_SEL0_SHIFT)

#define INTC_INTM33SEL3_M33SPI3_SEL1_SHIFT      (10)      /* Bits 10-19: M33Spi3 Sel1 */
#define INTC_INTM33SEL3_M33SPI3_SEL1_MASK       (0x3ff << INTC_INTM33SEL3_M33SPI3_SEL1_SHIFT)

#define INTC_INTM33SEL3_M33SPI3_SEL2_SHIFT      (20)      /* Bits 20-29: M33Spi3 Sel2 */
#define INTC_INTM33SEL3_M33SPI3_SEL2_MASK       (0x3ff << INTC_INTM33SEL3_M33SPI3_SEL2_SHIFT)

/* INTC INTM33SEL30 Register Bit Definitions *************************/

#define INTC_INTM33SEL30_M33SPI30_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi30 Sel0 */
#define INTC_INTM33SEL30_M33SPI30_SEL0_MASK     (0x3ff << INTC_INTM33SEL30_M33SPI30_SEL0_SHIFT)

#define INTC_INTM33SEL30_M33SPI30_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi30 Sel1 */
#define INTC_INTM33SEL30_M33SPI30_SEL1_MASK     (0x3ff << INTC_INTM33SEL30_M33SPI30_SEL1_SHIFT)

#define INTC_INTM33SEL30_M33SPI30_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi30 Sel2 */
#define INTC_INTM33SEL30_M33SPI30_SEL2_MASK     (0x3ff << INTC_INTM33SEL30_M33SPI30_SEL2_SHIFT)

/* INTC INTM33SEL31 Register Bit Definitions *************************/

#define INTC_INTM33SEL31_M33SPI31_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi31 Sel0 */
#define INTC_INTM33SEL31_M33SPI31_SEL0_MASK     (0x3ff << INTC_INTM33SEL31_M33SPI31_SEL0_SHIFT)

#define INTC_INTM33SEL31_M33SPI31_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi31 Sel1 */
#define INTC_INTM33SEL31_M33SPI31_SEL1_MASK     (0x3ff << INTC_INTM33SEL31_M33SPI31_SEL1_SHIFT)

#define INTC_INTM33SEL31_M33SPI31_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi31 Sel2 */
#define INTC_INTM33SEL31_M33SPI31_SEL2_MASK     (0x3ff << INTC_INTM33SEL31_M33SPI31_SEL2_SHIFT)

/* INTC INTM33SEL32 Register Bit Definitions *************************/

#define INTC_INTM33SEL32_M33SPI32_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi32 Sel0 */
#define INTC_INTM33SEL32_M33SPI32_SEL0_MASK     (0x3ff << INTC_INTM33SEL32_M33SPI32_SEL0_SHIFT)

#define INTC_INTM33SEL32_M33SPI32_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi32 Sel1 */
#define INTC_INTM33SEL32_M33SPI32_SEL1_MASK     (0x3ff << INTC_INTM33SEL32_M33SPI32_SEL1_SHIFT)

#define INTC_INTM33SEL32_M33SPI32_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi32 Sel2 */
#define INTC_INTM33SEL32_M33SPI32_SEL2_MASK     (0x3ff << INTC_INTM33SEL32_M33SPI32_SEL2_SHIFT)

/* INTC INTM33SEL33 Register Bit Definitions *************************/

#define INTC_INTM33SEL33_M33SPI33_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi33 Sel0 */
#define INTC_INTM33SEL33_M33SPI33_SEL0_MASK     (0x3ff << INTC_INTM33SEL33_M33SPI33_SEL0_SHIFT)

#define INTC_INTM33SEL33_M33SPI33_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi33 Sel1 */
#define INTC_INTM33SEL33_M33SPI33_SEL1_MASK     (0x3ff << INTC_INTM33SEL33_M33SPI33_SEL1_SHIFT)

#define INTC_INTM33SEL33_M33SPI33_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi33 Sel2 */
#define INTC_INTM33SEL33_M33SPI33_SEL2_MASK     (0x3ff << INTC_INTM33SEL33_M33SPI33_SEL2_SHIFT)

/* INTC INTM33SEL34 Register Bit Definitions *************************/

#define INTC_INTM33SEL34_M33SPI34_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi34 Sel0 */
#define INTC_INTM33SEL34_M33SPI34_SEL0_MASK     (0x3ff << INTC_INTM33SEL34_M33SPI34_SEL0_SHIFT)

#define INTC_INTM33SEL34_M33SPI34_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi34 Sel1 */
#define INTC_INTM33SEL34_M33SPI34_SEL1_MASK     (0x3ff << INTC_INTM33SEL34_M33SPI34_SEL1_SHIFT)

#define INTC_INTM33SEL34_M33SPI34_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi34 Sel2 */
#define INTC_INTM33SEL34_M33SPI34_SEL2_MASK     (0x3ff << INTC_INTM33SEL34_M33SPI34_SEL2_SHIFT)

/* INTC INTM33SEL35 Register Bit Definitions *************************/

#define INTC_INTM33SEL35_M33SPI35_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi35 Sel0 */
#define INTC_INTM33SEL35_M33SPI35_SEL0_MASK     (0x3ff << INTC_INTM33SEL35_M33SPI35_SEL0_SHIFT)

#define INTC_INTM33SEL35_M33SPI35_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi35 Sel1 */
#define INTC_INTM33SEL35_M33SPI35_SEL1_MASK     (0x3ff << INTC_INTM33SEL35_M33SPI35_SEL1_SHIFT)

#define INTC_INTM33SEL35_M33SPI35_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi35 Sel2 */
#define INTC_INTM33SEL35_M33SPI35_SEL2_MASK     (0x3ff << INTC_INTM33SEL35_M33SPI35_SEL2_SHIFT)

/* INTC INTM33SEL36 Register Bit Definitions *************************/

#define INTC_INTM33SEL36_M33SPI36_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi36 Sel0 */
#define INTC_INTM33SEL36_M33SPI36_SEL0_MASK     (0x3ff << INTC_INTM33SEL36_M33SPI36_SEL0_SHIFT)

#define INTC_INTM33SEL36_M33SPI36_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi36 Sel1 */
#define INTC_INTM33SEL36_M33SPI36_SEL1_MASK     (0x3ff << INTC_INTM33SEL36_M33SPI36_SEL1_SHIFT)

#define INTC_INTM33SEL36_M33SPI36_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi36 Sel2 */
#define INTC_INTM33SEL36_M33SPI36_SEL2_MASK     (0x3ff << INTC_INTM33SEL36_M33SPI36_SEL2_SHIFT)

/* INTC INTM33SEL37 Register Bit Definitions *************************/

#define INTC_INTM33SEL37_M33SPI37_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi37 Sel0 */
#define INTC_INTM33SEL37_M33SPI37_SEL0_MASK     (0x3ff << INTC_INTM33SEL37_M33SPI37_SEL0_SHIFT)

#define INTC_INTM33SEL37_M33SPI37_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi37 Sel1 */
#define INTC_INTM33SEL37_M33SPI37_SEL1_MASK     (0x3ff << INTC_INTM33SEL37_M33SPI37_SEL1_SHIFT)

#define INTC_INTM33SEL37_M33SPI37_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi37 Sel2 */
#define INTC_INTM33SEL37_M33SPI37_SEL2_MASK     (0x3ff << INTC_INTM33SEL37_M33SPI37_SEL2_SHIFT)

/* INTC INTM33SEL38 Register Bit Definitions *************************/

#define INTC_INTM33SEL38_M33SPI38_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi38 Sel0 */
#define INTC_INTM33SEL38_M33SPI38_SEL0_MASK     (0x3ff << INTC_INTM33SEL38_M33SPI38_SEL0_SHIFT)

#define INTC_INTM33SEL38_M33SPI38_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi38 Sel1 */
#define INTC_INTM33SEL38_M33SPI38_SEL1_MASK     (0x3ff << INTC_INTM33SEL38_M33SPI38_SEL1_SHIFT)

#define INTC_INTM33SEL38_M33SPI38_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi38 Sel2 */
#define INTC_INTM33SEL38_M33SPI38_SEL2_MASK     (0x3ff << INTC_INTM33SEL38_M33SPI38_SEL2_SHIFT)

/* INTC INTM33SEL39 Register Bit Definitions *************************/

#define INTC_INTM33SEL39_M33SPI39_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi39 Sel0 */
#define INTC_INTM33SEL39_M33SPI39_SEL0_MASK     (0x3ff << INTC_INTM33SEL39_M33SPI39_SEL0_SHIFT)

#define INTC_INTM33SEL39_M33SPI39_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi39 Sel1 */
#define INTC_INTM33SEL39_M33SPI39_SEL1_MASK     (0x3ff << INTC_INTM33SEL39_M33SPI39_SEL1_SHIFT)

#define INTC_INTM33SEL39_M33SPI39_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi39 Sel2 */
#define INTC_INTM33SEL39_M33SPI39_SEL2_MASK     (0x3ff << INTC_INTM33SEL39_M33SPI39_SEL2_SHIFT)

/* INTC INTM33SEL4 Register Bit Definitions **************************/

#define INTC_INTM33SEL4_M33SPI4_SEL0_SHIFT      (0)      /* Bits 0-9: M33Spi4 Sel0 */
#define INTC_INTM33SEL4_M33SPI4_SEL0_MASK       (0x3ff << INTC_INTM33SEL4_M33SPI4_SEL0_SHIFT)

#define INTC_INTM33SEL4_M33SPI4_SEL1_SHIFT      (10)      /* Bits 10-19: M33Spi4 Sel1 */
#define INTC_INTM33SEL4_M33SPI4_SEL1_MASK       (0x3ff << INTC_INTM33SEL4_M33SPI4_SEL1_SHIFT)

#define INTC_INTM33SEL4_M33SPI4_SEL2_SHIFT      (20)      /* Bits 20-29: M33Spi4 Sel2 */
#define INTC_INTM33SEL4_M33SPI4_SEL2_MASK       (0x3ff << INTC_INTM33SEL4_M33SPI4_SEL2_SHIFT)

/* INTC INTM33SEL40 Register Bit Definitions *************************/

#define INTC_INTM33SEL40_M33SPI40_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi40 Sel0 */
#define INTC_INTM33SEL40_M33SPI40_SEL0_MASK     (0x3ff << INTC_INTM33SEL40_M33SPI40_SEL0_SHIFT)

#define INTC_INTM33SEL40_M33SPI40_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi40 Sel1 */
#define INTC_INTM33SEL40_M33SPI40_SEL1_MASK     (0x3ff << INTC_INTM33SEL40_M33SPI40_SEL1_SHIFT)

#define INTC_INTM33SEL40_M33SPI40_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi40 Sel2 */
#define INTC_INTM33SEL40_M33SPI40_SEL2_MASK     (0x3ff << INTC_INTM33SEL40_M33SPI40_SEL2_SHIFT)

/* INTC INTM33SEL41 Register Bit Definitions *************************/

#define INTC_INTM33SEL41_M33SPI41_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi41 Sel0 */
#define INTC_INTM33SEL41_M33SPI41_SEL0_MASK     (0x3ff << INTC_INTM33SEL41_M33SPI41_SEL0_SHIFT)

#define INTC_INTM33SEL41_M33SPI41_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi41 Sel1 */
#define INTC_INTM33SEL41_M33SPI41_SEL1_MASK     (0x3ff << INTC_INTM33SEL41_M33SPI41_SEL1_SHIFT)

#define INTC_INTM33SEL41_M33SPI41_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi41 Sel2 */
#define INTC_INTM33SEL41_M33SPI41_SEL2_MASK     (0x3ff << INTC_INTM33SEL41_M33SPI41_SEL2_SHIFT)

/* INTC INTM33SEL42 Register Bit Definitions *************************/

#define INTC_INTM33SEL42_M33SPI42_SEL0_SHIFT    (0)      /* Bits 0-9: M33Spi42 Sel0 */
#define INTC_INTM33SEL42_M33SPI42_SEL0_MASK     (0x3ff << INTC_INTM33SEL42_M33SPI42_SEL0_SHIFT)

#define INTC_INTM33SEL42_M33SPI42_SEL1_SHIFT    (10)      /* Bits 10-19: M33Spi42 Sel1 */
#define INTC_INTM33SEL42_M33SPI42_SEL1_MASK     (0x3ff << INTC_INTM33SEL42_M33SPI42_SEL1_SHIFT)

#define INTC_INTM33SEL42_M33SPI42_SEL2_SHIFT    (20)      /* Bits 20-29: M33Spi42 Sel2 */
#define INTC_INTM33SEL42_M33SPI42_SEL2_MASK     (0x3ff << INTC_INTM33SEL42_M33SPI42_SEL2_SHIFT)

/* INTC INTM33SEL5 Register Bit Definitions **************************/

#define INTC_INTM33SEL5_M33SPI5_SEL0_SHIFT      (0)      /* Bits 0-9: M33Spi5 Sel0 */
#define INTC_INTM33SEL5_M33SPI5_SEL0_MASK       (0x3ff << INTC_INTM33SEL5_M33SPI5_SEL0_SHIFT)

#define INTC_INTM33SEL5_M33SPI5_SEL1_SHIFT      (10)      /* Bits 10-19: M33Spi5 Sel1 */
#define INTC_INTM33SEL5_M33SPI5_SEL1_MASK       (0x3ff << INTC_INTM33SEL5_M33SPI5_SEL1_SHIFT)

#define INTC_INTM33SEL5_M33SPI5_SEL2_SHIFT      (20)      /* Bits 20-29: M33Spi5 Sel2 */
#define INTC_INTM33SEL5_M33SPI5_SEL2_MASK       (0x3ff << INTC_INTM33SEL5_M33SPI5_SEL2_SHIFT)

/* INTC INTM33SEL6 Register Bit Definitions **************************/

#define INTC_INTM33SEL6_M33SPI6_SEL0_SHIFT      (0)      /* Bits 0-9: M33Spi6 Sel0 */
#define INTC_INTM33SEL6_M33SPI6_SEL0_MASK       (0x3ff << INTC_INTM33SEL6_M33SPI6_SEL0_SHIFT)

#define INTC_INTM33SEL6_M33SPI6_SEL1_SHIFT      (10)      /* Bits 10-19: M33Spi6 Sel1 */
#define INTC_INTM33SEL6_M33SPI6_SEL1_MASK       (0x3ff << INTC_INTM33SEL6_M33SPI6_SEL1_SHIFT)

#define INTC_INTM33SEL6_M33SPI6_SEL2_SHIFT      (20)      /* Bits 20-29: M33Spi6 Sel2 */
#define INTC_INTM33SEL6_M33SPI6_SEL2_MASK       (0x3ff << INTC_INTM33SEL6_M33SPI6_SEL2_SHIFT)

/* INTC INTM33SEL7 Register Bit Definitions **************************/

#define INTC_INTM33SEL7_M33SPI7_SEL0_SHIFT      (0)      /* Bits 0-9: M33Spi7 Sel0 */
#define INTC_INTM33SEL7_M33SPI7_SEL0_MASK       (0x3ff << INTC_INTM33SEL7_M33SPI7_SEL0_SHIFT)

#define INTC_INTM33SEL7_M33SPI7_SEL1_SHIFT      (10)      /* Bits 10-19: M33Spi7 Sel1 */
#define INTC_INTM33SEL7_M33SPI7_SEL1_MASK       (0x3ff << INTC_INTM33SEL7_M33SPI7_SEL1_SHIFT)

#define INTC_INTM33SEL7_M33SPI7_SEL2_SHIFT      (20)      /* Bits 20-29: M33Spi7 Sel2 */
#define INTC_INTM33SEL7_M33SPI7_SEL2_MASK       (0x3ff << INTC_INTM33SEL7_M33SPI7_SEL2_SHIFT)

/* INTC INTM33SEL8 Register Bit Definitions **************************/

#define INTC_INTM33SEL8_M33SPI8_SEL0_SHIFT      (0)      /* Bits 0-9: M33Spi8 Sel0 */
#define INTC_INTM33SEL8_M33SPI8_SEL0_MASK       (0x3ff << INTC_INTM33SEL8_M33SPI8_SEL0_SHIFT)

#define INTC_INTM33SEL8_M33SPI8_SEL1_SHIFT      (10)      /* Bits 10-19: M33Spi8 Sel1 */
#define INTC_INTM33SEL8_M33SPI8_SEL1_MASK       (0x3ff << INTC_INTM33SEL8_M33SPI8_SEL1_SHIFT)

#define INTC_INTM33SEL8_M33SPI8_SEL2_SHIFT      (20)      /* Bits 20-29: M33Spi8 Sel2 */
#define INTC_INTM33SEL8_M33SPI8_SEL2_MASK       (0x3ff << INTC_INTM33SEL8_M33SPI8_SEL2_SHIFT)

/* INTC INTM33SEL9 Register Bit Definitions **************************/

#define INTC_INTM33SEL9_M33SPI9_SEL0_SHIFT      (0)      /* Bits 0-9: M33Spi9 Sel0 */
#define INTC_INTM33SEL9_M33SPI9_SEL0_MASK       (0x3ff << INTC_INTM33SEL9_M33SPI9_SEL0_SHIFT)

#define INTC_INTM33SEL9_M33SPI9_SEL1_SHIFT      (10)      /* Bits 10-19: M33Spi9 Sel1 */
#define INTC_INTM33SEL9_M33SPI9_SEL1_MASK       (0x3ff << INTC_INTM33SEL9_M33SPI9_SEL1_SHIFT)

#define INTC_INTM33SEL9_M33SPI9_SEL2_SHIFT      (20)      /* Bits 20-29: M33Spi9 Sel2 */
#define INTC_INTM33SEL9_M33SPI9_SEL2_MASK       (0x3ff << INTC_INTM33SEL9_M33SPI9_SEL2_SHIFT)

/* INTC INTR8SEL0 Register Bit Definitions ***************************/

#define INTC_INTR8SEL0_R8SPI0_SEL0_SHIFT        (0)      /* Bits 0-9: R8Spi0 Sel0 */
#define INTC_INTR8SEL0_R8SPI0_SEL0_MASK         (0x3ff << INTC_INTR8SEL0_R8SPI0_SEL0_SHIFT)

#define INTC_INTR8SEL0_R8SPI0_SEL1_SHIFT        (10)      /* Bits 10-19: R8Spi0 Sel1 */
#define INTC_INTR8SEL0_R8SPI0_SEL1_MASK         (0x3ff << INTC_INTR8SEL0_R8SPI0_SEL1_SHIFT)

#define INTC_INTR8SEL0_R8SPI0_SEL2_SHIFT        (20)      /* Bits 20-29: R8Spi0 Sel2 */
#define INTC_INTR8SEL0_R8SPI0_SEL2_MASK         (0x3ff << INTC_INTR8SEL0_R8SPI0_SEL2_SHIFT)

/* INTC INTR8SEL1 Register Bit Definitions ***************************/

#define INTC_INTR8SEL1_R8SPI1_SEL0_SHIFT        (0)      /* Bits 0-9: R8Spi1 Sel0 */
#define INTC_INTR8SEL1_R8SPI1_SEL0_MASK         (0x3ff << INTC_INTR8SEL1_R8SPI1_SEL0_SHIFT)

#define INTC_INTR8SEL1_R8SPI1_SEL1_SHIFT        (10)      /* Bits 10-19: R8Spi1 Sel1 */
#define INTC_INTR8SEL1_R8SPI1_SEL1_MASK         (0x3ff << INTC_INTR8SEL1_R8SPI1_SEL1_SHIFT)

#define INTC_INTR8SEL1_R8SPI1_SEL2_SHIFT        (20)      /* Bits 20-29: R8Spi1 Sel2 */
#define INTC_INTR8SEL1_R8SPI1_SEL2_MASK         (0x3ff << INTC_INTR8SEL1_R8SPI1_SEL2_SHIFT)

/* INTC INTR8SEL10 Register Bit Definitions **************************/

#define INTC_INTR8SEL10_R8SPI10_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi10 Sel0 */
#define INTC_INTR8SEL10_R8SPI10_SEL0_MASK       (0x3ff << INTC_INTR8SEL10_R8SPI10_SEL0_SHIFT)

#define INTC_INTR8SEL10_R8SPI10_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi10 Sel1 */
#define INTC_INTR8SEL10_R8SPI10_SEL1_MASK       (0x3ff << INTC_INTR8SEL10_R8SPI10_SEL1_SHIFT)

#define INTC_INTR8SEL10_R8SPI10_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi10 Sel2 */
#define INTC_INTR8SEL10_R8SPI10_SEL2_MASK       (0x3ff << INTC_INTR8SEL10_R8SPI10_SEL2_SHIFT)

/* INTC INTR8SEL11 Register Bit Definitions **************************/

#define INTC_INTR8SEL11_R8SPI11_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi11 Sel0 */
#define INTC_INTR8SEL11_R8SPI11_SEL0_MASK       (0x3ff << INTC_INTR8SEL11_R8SPI11_SEL0_SHIFT)

#define INTC_INTR8SEL11_R8SPI11_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi11 Sel1 */
#define INTC_INTR8SEL11_R8SPI11_SEL1_MASK       (0x3ff << INTC_INTR8SEL11_R8SPI11_SEL1_SHIFT)

#define INTC_INTR8SEL11_R8SPI11_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi11 Sel2 */
#define INTC_INTR8SEL11_R8SPI11_SEL2_MASK       (0x3ff << INTC_INTR8SEL11_R8SPI11_SEL2_SHIFT)

/* INTC INTR8SEL12 Register Bit Definitions **************************/

#define INTC_INTR8SEL12_R8SPI12_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi12 Sel0 */
#define INTC_INTR8SEL12_R8SPI12_SEL0_MASK       (0x3ff << INTC_INTR8SEL12_R8SPI12_SEL0_SHIFT)

#define INTC_INTR8SEL12_R8SPI12_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi12 Sel1 */
#define INTC_INTR8SEL12_R8SPI12_SEL1_MASK       (0x3ff << INTC_INTR8SEL12_R8SPI12_SEL1_SHIFT)

#define INTC_INTR8SEL12_R8SPI12_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi12 Sel2 */
#define INTC_INTR8SEL12_R8SPI12_SEL2_MASK       (0x3ff << INTC_INTR8SEL12_R8SPI12_SEL2_SHIFT)

/* INTC INTR8SEL13 Register Bit Definitions **************************/

#define INTC_INTR8SEL13_R8SPI13_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi13 Sel0 */
#define INTC_INTR8SEL13_R8SPI13_SEL0_MASK       (0x3ff << INTC_INTR8SEL13_R8SPI13_SEL0_SHIFT)

#define INTC_INTR8SEL13_R8SPI13_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi13 Sel1 */
#define INTC_INTR8SEL13_R8SPI13_SEL1_MASK       (0x3ff << INTC_INTR8SEL13_R8SPI13_SEL1_SHIFT)

#define INTC_INTR8SEL13_R8SPI13_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi13 Sel2 */
#define INTC_INTR8SEL13_R8SPI13_SEL2_MASK       (0x3ff << INTC_INTR8SEL13_R8SPI13_SEL2_SHIFT)

/* INTC INTR8SEL14 Register Bit Definitions **************************/

#define INTC_INTR8SEL14_R8SPI14_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi14 Sel0 */
#define INTC_INTR8SEL14_R8SPI14_SEL0_MASK       (0x3ff << INTC_INTR8SEL14_R8SPI14_SEL0_SHIFT)

#define INTC_INTR8SEL14_R8SPI14_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi14 Sel1 */
#define INTC_INTR8SEL14_R8SPI14_SEL1_MASK       (0x3ff << INTC_INTR8SEL14_R8SPI14_SEL1_SHIFT)

#define INTC_INTR8SEL14_R8SPI14_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi14 Sel2 */
#define INTC_INTR8SEL14_R8SPI14_SEL2_MASK       (0x3ff << INTC_INTR8SEL14_R8SPI14_SEL2_SHIFT)

/* INTC INTR8SEL15 Register Bit Definitions **************************/

#define INTC_INTR8SEL15_R8SPI15_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi15 Sel0 */
#define INTC_INTR8SEL15_R8SPI15_SEL0_MASK       (0x3ff << INTC_INTR8SEL15_R8SPI15_SEL0_SHIFT)

#define INTC_INTR8SEL15_R8SPI15_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi15 Sel1 */
#define INTC_INTR8SEL15_R8SPI15_SEL1_MASK       (0x3ff << INTC_INTR8SEL15_R8SPI15_SEL1_SHIFT)

#define INTC_INTR8SEL15_R8SPI15_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi15 Sel2 */
#define INTC_INTR8SEL15_R8SPI15_SEL2_MASK       (0x3ff << INTC_INTR8SEL15_R8SPI15_SEL2_SHIFT)

/* INTC INTR8SEL16 Register Bit Definitions **************************/

#define INTC_INTR8SEL16_R8SPI16_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi16 Sel0 */
#define INTC_INTR8SEL16_R8SPI16_SEL0_MASK       (0x3ff << INTC_INTR8SEL16_R8SPI16_SEL0_SHIFT)

#define INTC_INTR8SEL16_R8SPI16_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi16 Sel1 */
#define INTC_INTR8SEL16_R8SPI16_SEL1_MASK       (0x3ff << INTC_INTR8SEL16_R8SPI16_SEL1_SHIFT)

#define INTC_INTR8SEL16_R8SPI16_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi16 Sel2 */
#define INTC_INTR8SEL16_R8SPI16_SEL2_MASK       (0x3ff << INTC_INTR8SEL16_R8SPI16_SEL2_SHIFT)

/* INTC INTR8SEL17 Register Bit Definitions **************************/

#define INTC_INTR8SEL17_R8SPI17_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi17 Sel0 */
#define INTC_INTR8SEL17_R8SPI17_SEL0_MASK       (0x3ff << INTC_INTR8SEL17_R8SPI17_SEL0_SHIFT)

#define INTC_INTR8SEL17_R8SPI17_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi17 Sel1 */
#define INTC_INTR8SEL17_R8SPI17_SEL1_MASK       (0x3ff << INTC_INTR8SEL17_R8SPI17_SEL1_SHIFT)

#define INTC_INTR8SEL17_R8SPI17_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi17 Sel2 */
#define INTC_INTR8SEL17_R8SPI17_SEL2_MASK       (0x3ff << INTC_INTR8SEL17_R8SPI17_SEL2_SHIFT)

/* INTC INTR8SEL18 Register Bit Definitions **************************/

#define INTC_INTR8SEL18_R8SPI18_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi18 Sel0 */
#define INTC_INTR8SEL18_R8SPI18_SEL0_MASK       (0x3ff << INTC_INTR8SEL18_R8SPI18_SEL0_SHIFT)

#define INTC_INTR8SEL18_R8SPI18_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi18 Sel1 */
#define INTC_INTR8SEL18_R8SPI18_SEL1_MASK       (0x3ff << INTC_INTR8SEL18_R8SPI18_SEL1_SHIFT)

#define INTC_INTR8SEL18_R8SPI18_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi18 Sel2 */
#define INTC_INTR8SEL18_R8SPI18_SEL2_MASK       (0x3ff << INTC_INTR8SEL18_R8SPI18_SEL2_SHIFT)

/* INTC INTR8SEL19 Register Bit Definitions **************************/

#define INTC_INTR8SEL19_R8SPI19_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi19 Sel0 */
#define INTC_INTR8SEL19_R8SPI19_SEL0_MASK       (0x3ff << INTC_INTR8SEL19_R8SPI19_SEL0_SHIFT)

#define INTC_INTR8SEL19_R8SPI19_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi19 Sel1 */
#define INTC_INTR8SEL19_R8SPI19_SEL1_MASK       (0x3ff << INTC_INTR8SEL19_R8SPI19_SEL1_SHIFT)

#define INTC_INTR8SEL19_R8SPI19_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi19 Sel2 */
#define INTC_INTR8SEL19_R8SPI19_SEL2_MASK       (0x3ff << INTC_INTR8SEL19_R8SPI19_SEL2_SHIFT)

/* INTC INTR8SEL2 Register Bit Definitions ***************************/

#define INTC_INTR8SEL2_R8SPI2_SEL0_SHIFT        (0)      /* Bits 0-9: R8Spi2 Sel0 */
#define INTC_INTR8SEL2_R8SPI2_SEL0_MASK         (0x3ff << INTC_INTR8SEL2_R8SPI2_SEL0_SHIFT)

#define INTC_INTR8SEL2_R8SPI2_SEL1_SHIFT        (10)      /* Bits 10-19: R8Spi2 Sel1 */
#define INTC_INTR8SEL2_R8SPI2_SEL1_MASK         (0x3ff << INTC_INTR8SEL2_R8SPI2_SEL1_SHIFT)

#define INTC_INTR8SEL2_R8SPI2_SEL2_SHIFT        (20)      /* Bits 20-29: R8Spi2 Sel2 */
#define INTC_INTR8SEL2_R8SPI2_SEL2_MASK         (0x3ff << INTC_INTR8SEL2_R8SPI2_SEL2_SHIFT)

/* INTC INTR8SEL20 Register Bit Definitions **************************/

#define INTC_INTR8SEL20_R8SPI20_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi20 Sel0 */
#define INTC_INTR8SEL20_R8SPI20_SEL0_MASK       (0x3ff << INTC_INTR8SEL20_R8SPI20_SEL0_SHIFT)

#define INTC_INTR8SEL20_R8SPI20_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi20 Sel1 */
#define INTC_INTR8SEL20_R8SPI20_SEL1_MASK       (0x3ff << INTC_INTR8SEL20_R8SPI20_SEL1_SHIFT)

#define INTC_INTR8SEL20_R8SPI20_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi20 Sel2 */
#define INTC_INTR8SEL20_R8SPI20_SEL2_MASK       (0x3ff << INTC_INTR8SEL20_R8SPI20_SEL2_SHIFT)

/* INTC INTR8SEL21 Register Bit Definitions **************************/

#define INTC_INTR8SEL21_R8SPI21_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi21 Sel0 */
#define INTC_INTR8SEL21_R8SPI21_SEL0_MASK       (0x3ff << INTC_INTR8SEL21_R8SPI21_SEL0_SHIFT)

#define INTC_INTR8SEL21_R8SPI21_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi21 Sel1 */
#define INTC_INTR8SEL21_R8SPI21_SEL1_MASK       (0x3ff << INTC_INTR8SEL21_R8SPI21_SEL1_SHIFT)

#define INTC_INTR8SEL21_R8SPI21_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi21 Sel2 */
#define INTC_INTR8SEL21_R8SPI21_SEL2_MASK       (0x3ff << INTC_INTR8SEL21_R8SPI21_SEL2_SHIFT)

/* INTC INTR8SEL22 Register Bit Definitions **************************/

#define INTC_INTR8SEL22_R8SPI22_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi22 Sel0 */
#define INTC_INTR8SEL22_R8SPI22_SEL0_MASK       (0x3ff << INTC_INTR8SEL22_R8SPI22_SEL0_SHIFT)

#define INTC_INTR8SEL22_R8SPI22_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi22 Sel1 */
#define INTC_INTR8SEL22_R8SPI22_SEL1_MASK       (0x3ff << INTC_INTR8SEL22_R8SPI22_SEL1_SHIFT)

#define INTC_INTR8SEL22_R8SPI22_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi22 Sel2 */
#define INTC_INTR8SEL22_R8SPI22_SEL2_MASK       (0x3ff << INTC_INTR8SEL22_R8SPI22_SEL2_SHIFT)

/* INTC INTR8SEL23 Register Bit Definitions **************************/

#define INTC_INTR8SEL23_R8SPI23_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi23 Sel0 */
#define INTC_INTR8SEL23_R8SPI23_SEL0_MASK       (0x3ff << INTC_INTR8SEL23_R8SPI23_SEL0_SHIFT)

#define INTC_INTR8SEL23_R8SPI23_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi23 Sel1 */
#define INTC_INTR8SEL23_R8SPI23_SEL1_MASK       (0x3ff << INTC_INTR8SEL23_R8SPI23_SEL1_SHIFT)

#define INTC_INTR8SEL23_R8SPI23_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi23 Sel2 */
#define INTC_INTR8SEL23_R8SPI23_SEL2_MASK       (0x3ff << INTC_INTR8SEL23_R8SPI23_SEL2_SHIFT)

/* INTC INTR8SEL24 Register Bit Definitions **************************/

#define INTC_INTR8SEL24_R8SPI24_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi24 Sel0 */
#define INTC_INTR8SEL24_R8SPI24_SEL0_MASK       (0x3ff << INTC_INTR8SEL24_R8SPI24_SEL0_SHIFT)

#define INTC_INTR8SEL24_R8SPI24_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi24 Sel1 */
#define INTC_INTR8SEL24_R8SPI24_SEL1_MASK       (0x3ff << INTC_INTR8SEL24_R8SPI24_SEL1_SHIFT)

#define INTC_INTR8SEL24_R8SPI24_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi24 Sel2 */
#define INTC_INTR8SEL24_R8SPI24_SEL2_MASK       (0x3ff << INTC_INTR8SEL24_R8SPI24_SEL2_SHIFT)

/* INTC INTR8SEL25 Register Bit Definitions **************************/

#define INTC_INTR8SEL25_R8SPI25_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi25 Sel0 */
#define INTC_INTR8SEL25_R8SPI25_SEL0_MASK       (0x3ff << INTC_INTR8SEL25_R8SPI25_SEL0_SHIFT)

#define INTC_INTR8SEL25_R8SPI25_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi25 Sel1 */
#define INTC_INTR8SEL25_R8SPI25_SEL1_MASK       (0x3ff << INTC_INTR8SEL25_R8SPI25_SEL1_SHIFT)

#define INTC_INTR8SEL25_R8SPI25_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi25 Sel2 */
#define INTC_INTR8SEL25_R8SPI25_SEL2_MASK       (0x3ff << INTC_INTR8SEL25_R8SPI25_SEL2_SHIFT)

/* INTC INTR8SEL26 Register Bit Definitions **************************/

#define INTC_INTR8SEL26_R8SPI26_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi26 Sel0 */
#define INTC_INTR8SEL26_R8SPI26_SEL0_MASK       (0x3ff << INTC_INTR8SEL26_R8SPI26_SEL0_SHIFT)

#define INTC_INTR8SEL26_R8SPI26_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi26 Sel1 */
#define INTC_INTR8SEL26_R8SPI26_SEL1_MASK       (0x3ff << INTC_INTR8SEL26_R8SPI26_SEL1_SHIFT)

#define INTC_INTR8SEL26_R8SPI26_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi26 Sel2 */
#define INTC_INTR8SEL26_R8SPI26_SEL2_MASK       (0x3ff << INTC_INTR8SEL26_R8SPI26_SEL2_SHIFT)

/* INTC INTR8SEL27 Register Bit Definitions **************************/

#define INTC_INTR8SEL27_R8SPI27_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi27 Sel0 */
#define INTC_INTR8SEL27_R8SPI27_SEL0_MASK       (0x3ff << INTC_INTR8SEL27_R8SPI27_SEL0_SHIFT)

#define INTC_INTR8SEL27_R8SPI27_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi27 Sel1 */
#define INTC_INTR8SEL27_R8SPI27_SEL1_MASK       (0x3ff << INTC_INTR8SEL27_R8SPI27_SEL1_SHIFT)

#define INTC_INTR8SEL27_R8SPI27_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi27 Sel2 */
#define INTC_INTR8SEL27_R8SPI27_SEL2_MASK       (0x3ff << INTC_INTR8SEL27_R8SPI27_SEL2_SHIFT)

/* INTC INTR8SEL28 Register Bit Definitions **************************/

#define INTC_INTR8SEL28_R8SPI28_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi28 Sel0 */
#define INTC_INTR8SEL28_R8SPI28_SEL0_MASK       (0x3ff << INTC_INTR8SEL28_R8SPI28_SEL0_SHIFT)

#define INTC_INTR8SEL28_R8SPI28_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi28 Sel1 */
#define INTC_INTR8SEL28_R8SPI28_SEL1_MASK       (0x3ff << INTC_INTR8SEL28_R8SPI28_SEL1_SHIFT)

#define INTC_INTR8SEL28_R8SPI28_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi28 Sel2 */
#define INTC_INTR8SEL28_R8SPI28_SEL2_MASK       (0x3ff << INTC_INTR8SEL28_R8SPI28_SEL2_SHIFT)

/* INTC INTR8SEL29 Register Bit Definitions **************************/

#define INTC_INTR8SEL29_R8SPI29_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi29 Sel0 */
#define INTC_INTR8SEL29_R8SPI29_SEL0_MASK       (0x3ff << INTC_INTR8SEL29_R8SPI29_SEL0_SHIFT)

#define INTC_INTR8SEL29_R8SPI29_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi29 Sel1 */
#define INTC_INTR8SEL29_R8SPI29_SEL1_MASK       (0x3ff << INTC_INTR8SEL29_R8SPI29_SEL1_SHIFT)

#define INTC_INTR8SEL29_R8SPI29_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi29 Sel2 */
#define INTC_INTR8SEL29_R8SPI29_SEL2_MASK       (0x3ff << INTC_INTR8SEL29_R8SPI29_SEL2_SHIFT)

/* INTC INTR8SEL3 Register Bit Definitions ***************************/

#define INTC_INTR8SEL3_R8SPI3_SEL0_SHIFT        (0)      /* Bits 0-9: R8Spi3 Sel0 */
#define INTC_INTR8SEL3_R8SPI3_SEL0_MASK         (0x3ff << INTC_INTR8SEL3_R8SPI3_SEL0_SHIFT)

#define INTC_INTR8SEL3_R8SPI3_SEL1_SHIFT        (10)      /* Bits 10-19: R8Spi3 Sel1 */
#define INTC_INTR8SEL3_R8SPI3_SEL1_MASK         (0x3ff << INTC_INTR8SEL3_R8SPI3_SEL1_SHIFT)

#define INTC_INTR8SEL3_R8SPI3_SEL2_SHIFT        (20)      /* Bits 20-29: R8Spi3 Sel2 */
#define INTC_INTR8SEL3_R8SPI3_SEL2_MASK         (0x3ff << INTC_INTR8SEL3_R8SPI3_SEL2_SHIFT)

/* INTC INTR8SEL30 Register Bit Definitions **************************/

#define INTC_INTR8SEL30_R8SPI30_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi30 Sel0 */
#define INTC_INTR8SEL30_R8SPI30_SEL0_MASK       (0x3ff << INTC_INTR8SEL30_R8SPI30_SEL0_SHIFT)

#define INTC_INTR8SEL30_R8SPI30_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi30 Sel1 */
#define INTC_INTR8SEL30_R8SPI30_SEL1_MASK       (0x3ff << INTC_INTR8SEL30_R8SPI30_SEL1_SHIFT)

#define INTC_INTR8SEL30_R8SPI30_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi30 Sel2 */
#define INTC_INTR8SEL30_R8SPI30_SEL2_MASK       (0x3ff << INTC_INTR8SEL30_R8SPI30_SEL2_SHIFT)

/* INTC INTR8SEL31 Register Bit Definitions **************************/

#define INTC_INTR8SEL31_R8SPI31_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi31 Sel0 */
#define INTC_INTR8SEL31_R8SPI31_SEL0_MASK       (0x3ff << INTC_INTR8SEL31_R8SPI31_SEL0_SHIFT)

#define INTC_INTR8SEL31_R8SPI31_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi31 Sel1 */
#define INTC_INTR8SEL31_R8SPI31_SEL1_MASK       (0x3ff << INTC_INTR8SEL31_R8SPI31_SEL1_SHIFT)

#define INTC_INTR8SEL31_R8SPI31_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi31 Sel2 */
#define INTC_INTR8SEL31_R8SPI31_SEL2_MASK       (0x3ff << INTC_INTR8SEL31_R8SPI31_SEL2_SHIFT)

/* INTC INTR8SEL32 Register Bit Definitions **************************/

#define INTC_INTR8SEL32_R8SPI32_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi32 Sel0 */
#define INTC_INTR8SEL32_R8SPI32_SEL0_MASK       (0x3ff << INTC_INTR8SEL32_R8SPI32_SEL0_SHIFT)

#define INTC_INTR8SEL32_R8SPI32_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi32 Sel1 */
#define INTC_INTR8SEL32_R8SPI32_SEL1_MASK       (0x3ff << INTC_INTR8SEL32_R8SPI32_SEL1_SHIFT)

#define INTC_INTR8SEL32_R8SPI32_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi32 Sel2 */
#define INTC_INTR8SEL32_R8SPI32_SEL2_MASK       (0x3ff << INTC_INTR8SEL32_R8SPI32_SEL2_SHIFT)

/* INTC INTR8SEL33 Register Bit Definitions **************************/

#define INTC_INTR8SEL33_R8SPI33_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi33 Sel0 */
#define INTC_INTR8SEL33_R8SPI33_SEL0_MASK       (0x3ff << INTC_INTR8SEL33_R8SPI33_SEL0_SHIFT)

#define INTC_INTR8SEL33_R8SPI33_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi33 Sel1 */
#define INTC_INTR8SEL33_R8SPI33_SEL1_MASK       (0x3ff << INTC_INTR8SEL33_R8SPI33_SEL1_SHIFT)

#define INTC_INTR8SEL33_R8SPI33_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi33 Sel2 */
#define INTC_INTR8SEL33_R8SPI33_SEL2_MASK       (0x3ff << INTC_INTR8SEL33_R8SPI33_SEL2_SHIFT)

/* INTC INTR8SEL34 Register Bit Definitions **************************/

#define INTC_INTR8SEL34_R8SPI34_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi34 Sel0 */
#define INTC_INTR8SEL34_R8SPI34_SEL0_MASK       (0x3ff << INTC_INTR8SEL34_R8SPI34_SEL0_SHIFT)

#define INTC_INTR8SEL34_R8SPI34_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi34 Sel1 */
#define INTC_INTR8SEL34_R8SPI34_SEL1_MASK       (0x3ff << INTC_INTR8SEL34_R8SPI34_SEL1_SHIFT)

#define INTC_INTR8SEL34_R8SPI34_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi34 Sel2 */
#define INTC_INTR8SEL34_R8SPI34_SEL2_MASK       (0x3ff << INTC_INTR8SEL34_R8SPI34_SEL2_SHIFT)

/* INTC INTR8SEL35 Register Bit Definitions **************************/

#define INTC_INTR8SEL35_R8SPI35_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi35 Sel0 */
#define INTC_INTR8SEL35_R8SPI35_SEL0_MASK       (0x3ff << INTC_INTR8SEL35_R8SPI35_SEL0_SHIFT)

#define INTC_INTR8SEL35_R8SPI35_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi35 Sel1 */
#define INTC_INTR8SEL35_R8SPI35_SEL1_MASK       (0x3ff << INTC_INTR8SEL35_R8SPI35_SEL1_SHIFT)

#define INTC_INTR8SEL35_R8SPI35_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi35 Sel2 */
#define INTC_INTR8SEL35_R8SPI35_SEL2_MASK       (0x3ff << INTC_INTR8SEL35_R8SPI35_SEL2_SHIFT)

/* INTC INTR8SEL36 Register Bit Definitions **************************/

#define INTC_INTR8SEL36_R8SPI36_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi36 Sel0 */
#define INTC_INTR8SEL36_R8SPI36_SEL0_MASK       (0x3ff << INTC_INTR8SEL36_R8SPI36_SEL0_SHIFT)

#define INTC_INTR8SEL36_R8SPI36_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi36 Sel1 */
#define INTC_INTR8SEL36_R8SPI36_SEL1_MASK       (0x3ff << INTC_INTR8SEL36_R8SPI36_SEL1_SHIFT)

#define INTC_INTR8SEL36_R8SPI36_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi36 Sel2 */
#define INTC_INTR8SEL36_R8SPI36_SEL2_MASK       (0x3ff << INTC_INTR8SEL36_R8SPI36_SEL2_SHIFT)

/* INTC INTR8SEL37 Register Bit Definitions **************************/

#define INTC_INTR8SEL37_R8SPI37_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi37 Sel0 */
#define INTC_INTR8SEL37_R8SPI37_SEL0_MASK       (0x3ff << INTC_INTR8SEL37_R8SPI37_SEL0_SHIFT)

#define INTC_INTR8SEL37_R8SPI37_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi37 Sel1 */
#define INTC_INTR8SEL37_R8SPI37_SEL1_MASK       (0x3ff << INTC_INTR8SEL37_R8SPI37_SEL1_SHIFT)

#define INTC_INTR8SEL37_R8SPI37_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi37 Sel2 */
#define INTC_INTR8SEL37_R8SPI37_SEL2_MASK       (0x3ff << INTC_INTR8SEL37_R8SPI37_SEL2_SHIFT)

/* INTC INTR8SEL38 Register Bit Definitions **************************/

#define INTC_INTR8SEL38_R8SPI38_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi38 Sel0 */
#define INTC_INTR8SEL38_R8SPI38_SEL0_MASK       (0x3ff << INTC_INTR8SEL38_R8SPI38_SEL0_SHIFT)

#define INTC_INTR8SEL38_R8SPI38_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi38 Sel1 */
#define INTC_INTR8SEL38_R8SPI38_SEL1_MASK       (0x3ff << INTC_INTR8SEL38_R8SPI38_SEL1_SHIFT)

#define INTC_INTR8SEL38_R8SPI38_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi38 Sel2 */
#define INTC_INTR8SEL38_R8SPI38_SEL2_MASK       (0x3ff << INTC_INTR8SEL38_R8SPI38_SEL2_SHIFT)

/* INTC INTR8SEL39 Register Bit Definitions **************************/

#define INTC_INTR8SEL39_R8SPI39_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi39 Sel0 */
#define INTC_INTR8SEL39_R8SPI39_SEL0_MASK       (0x3ff << INTC_INTR8SEL39_R8SPI39_SEL0_SHIFT)

#define INTC_INTR8SEL39_R8SPI39_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi39 Sel1 */
#define INTC_INTR8SEL39_R8SPI39_SEL1_MASK       (0x3ff << INTC_INTR8SEL39_R8SPI39_SEL1_SHIFT)

#define INTC_INTR8SEL39_R8SPI39_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi39 Sel2 */
#define INTC_INTR8SEL39_R8SPI39_SEL2_MASK       (0x3ff << INTC_INTR8SEL39_R8SPI39_SEL2_SHIFT)

/* INTC INTR8SEL4 Register Bit Definitions ***************************/

#define INTC_INTR8SEL4_R8SPI4_SEL0_SHIFT        (0)      /* Bits 0-9: R8Spi4 Sel0 */
#define INTC_INTR8SEL4_R8SPI4_SEL0_MASK         (0x3ff << INTC_INTR8SEL4_R8SPI4_SEL0_SHIFT)

#define INTC_INTR8SEL4_R8SPI4_SEL1_SHIFT        (10)      /* Bits 10-19: R8Spi4 Sel1 */
#define INTC_INTR8SEL4_R8SPI4_SEL1_MASK         (0x3ff << INTC_INTR8SEL4_R8SPI4_SEL1_SHIFT)

#define INTC_INTR8SEL4_R8SPI4_SEL2_SHIFT        (20)      /* Bits 20-29: R8Spi4 Sel2 */
#define INTC_INTR8SEL4_R8SPI4_SEL2_MASK         (0x3ff << INTC_INTR8SEL4_R8SPI4_SEL2_SHIFT)

/* INTC INTR8SEL40 Register Bit Definitions **************************/

#define INTC_INTR8SEL40_R8SPI40_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi40 Sel0 */
#define INTC_INTR8SEL40_R8SPI40_SEL0_MASK       (0x3ff << INTC_INTR8SEL40_R8SPI40_SEL0_SHIFT)

#define INTC_INTR8SEL40_R8SPI40_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi40 Sel1 */
#define INTC_INTR8SEL40_R8SPI40_SEL1_MASK       (0x3ff << INTC_INTR8SEL40_R8SPI40_SEL1_SHIFT)

#define INTC_INTR8SEL40_R8SPI40_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi40 Sel2 */
#define INTC_INTR8SEL40_R8SPI40_SEL2_MASK       (0x3ff << INTC_INTR8SEL40_R8SPI40_SEL2_SHIFT)

/* INTC INTR8SEL41 Register Bit Definitions **************************/

#define INTC_INTR8SEL41_R8SPI41_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi41 Sel0 */
#define INTC_INTR8SEL41_R8SPI41_SEL0_MASK       (0x3ff << INTC_INTR8SEL41_R8SPI41_SEL0_SHIFT)

#define INTC_INTR8SEL41_R8SPI41_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi41 Sel1 */
#define INTC_INTR8SEL41_R8SPI41_SEL1_MASK       (0x3ff << INTC_INTR8SEL41_R8SPI41_SEL1_SHIFT)

#define INTC_INTR8SEL41_R8SPI41_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi41 Sel2 */
#define INTC_INTR8SEL41_R8SPI41_SEL2_MASK       (0x3ff << INTC_INTR8SEL41_R8SPI41_SEL2_SHIFT)

/* INTC INTR8SEL42 Register Bit Definitions **************************/

#define INTC_INTR8SEL42_R8SPI42_SEL0_SHIFT      (0)      /* Bits 0-9: R8Spi42 Sel0 */
#define INTC_INTR8SEL42_R8SPI42_SEL0_MASK       (0x3ff << INTC_INTR8SEL42_R8SPI42_SEL0_SHIFT)

#define INTC_INTR8SEL42_R8SPI42_SEL1_SHIFT      (10)      /* Bits 10-19: R8Spi42 Sel1 */
#define INTC_INTR8SEL42_R8SPI42_SEL1_MASK       (0x3ff << INTC_INTR8SEL42_R8SPI42_SEL1_SHIFT)

#define INTC_INTR8SEL42_R8SPI42_SEL2_SHIFT      (20)      /* Bits 20-29: R8Spi42 Sel2 */
#define INTC_INTR8SEL42_R8SPI42_SEL2_MASK       (0x3ff << INTC_INTR8SEL42_R8SPI42_SEL2_SHIFT)

/* INTC INTR8SEL5 Register Bit Definitions ***************************/

#define INTC_INTR8SEL5_R8SPI5_SEL0_SHIFT        (0)      /* Bits 0-9: R8Spi5 Sel0 */
#define INTC_INTR8SEL5_R8SPI5_SEL0_MASK         (0x3ff << INTC_INTR8SEL5_R8SPI5_SEL0_SHIFT)

#define INTC_INTR8SEL5_R8SPI5_SEL1_SHIFT        (10)      /* Bits 10-19: R8Spi5 Sel1 */
#define INTC_INTR8SEL5_R8SPI5_SEL1_MASK         (0x3ff << INTC_INTR8SEL5_R8SPI5_SEL1_SHIFT)

#define INTC_INTR8SEL5_R8SPI5_SEL2_SHIFT        (20)      /* Bits 20-29: R8Spi5 Sel2 */
#define INTC_INTR8SEL5_R8SPI5_SEL2_MASK         (0x3ff << INTC_INTR8SEL5_R8SPI5_SEL2_SHIFT)

/* INTC INTR8SEL6 Register Bit Definitions ***************************/

#define INTC_INTR8SEL6_R8SPI6_SEL0_SHIFT        (0)      /* Bits 0-9: R8Spi6 Sel0 */
#define INTC_INTR8SEL6_R8SPI6_SEL0_MASK         (0x3ff << INTC_INTR8SEL6_R8SPI6_SEL0_SHIFT)

#define INTC_INTR8SEL6_R8SPI6_SEL1_SHIFT        (10)      /* Bits 10-19: R8Spi6 Sel1 */
#define INTC_INTR8SEL6_R8SPI6_SEL1_MASK         (0x3ff << INTC_INTR8SEL6_R8SPI6_SEL1_SHIFT)

#define INTC_INTR8SEL6_R8SPI6_SEL2_SHIFT        (20)      /* Bits 20-29: R8Spi6 Sel2 */
#define INTC_INTR8SEL6_R8SPI6_SEL2_MASK         (0x3ff << INTC_INTR8SEL6_R8SPI6_SEL2_SHIFT)

/* INTC INTR8SEL7 Register Bit Definitions ***************************/

#define INTC_INTR8SEL7_R8SPI7_SEL0_SHIFT        (0)      /* Bits 0-9: R8Spi7 Sel0 */
#define INTC_INTR8SEL7_R8SPI7_SEL0_MASK         (0x3ff << INTC_INTR8SEL7_R8SPI7_SEL0_SHIFT)

#define INTC_INTR8SEL7_R8SPI7_SEL1_SHIFT        (10)      /* Bits 10-19: R8Spi7 Sel1 */
#define INTC_INTR8SEL7_R8SPI7_SEL1_MASK         (0x3ff << INTC_INTR8SEL7_R8SPI7_SEL1_SHIFT)

#define INTC_INTR8SEL7_R8SPI7_SEL2_SHIFT        (20)      /* Bits 20-29: R8Spi7 Sel2 */
#define INTC_INTR8SEL7_R8SPI7_SEL2_MASK         (0x3ff << INTC_INTR8SEL7_R8SPI7_SEL2_SHIFT)

/* INTC INTR8SEL8 Register Bit Definitions ***************************/

#define INTC_INTR8SEL8_R8SPI8_SEL0_SHIFT        (0)      /* Bits 0-9: R8Spi8 Sel0 */
#define INTC_INTR8SEL8_R8SPI8_SEL0_MASK         (0x3ff << INTC_INTR8SEL8_R8SPI8_SEL0_SHIFT)

#define INTC_INTR8SEL8_R8SPI8_SEL1_SHIFT        (10)      /* Bits 10-19: R8Spi8 Sel1 */
#define INTC_INTR8SEL8_R8SPI8_SEL1_MASK         (0x3ff << INTC_INTR8SEL8_R8SPI8_SEL1_SHIFT)

#define INTC_INTR8SEL8_R8SPI8_SEL2_SHIFT        (20)      /* Bits 20-29: R8Spi8 Sel2 */
#define INTC_INTR8SEL8_R8SPI8_SEL2_MASK         (0x3ff << INTC_INTR8SEL8_R8SPI8_SEL2_SHIFT)

/* INTC INTR8SEL9 Register Bit Definitions ***************************/

#define INTC_INTR8SEL9_R8SPI9_SEL0_SHIFT        (0)      /* Bits 0-9: R8Spi9 Sel0 */
#define INTC_INTR8SEL9_R8SPI9_SEL0_MASK         (0x3ff << INTC_INTR8SEL9_R8SPI9_SEL0_SHIFT)

#define INTC_INTR8SEL9_R8SPI9_SEL1_SHIFT        (10)      /* Bits 10-19: R8Spi9 Sel1 */
#define INTC_INTR8SEL9_R8SPI9_SEL1_MASK         (0x3ff << INTC_INTR8SEL9_R8SPI9_SEL1_SHIFT)

#define INTC_INTR8SEL9_R8SPI9_SEL2_SHIFT        (20)      /* Bits 20-29: R8Spi9 Sel2 */
#define INTC_INTR8SEL9_R8SPI9_SEL2_MASK         (0x3ff << INTC_INTR8SEL9_R8SPI9_SEL2_SHIFT)

/* INTC IPTSR Register Bit Definitions *******************************/

#define INTC_IPTSR_ISPSEL                       (1 << 0)  /* Ispsel */

#define INTC_IPTSR_GBE0SEL_tx                   (1 << 4)  /* Gbe0Sel Tx */

#define INTC_IPTSR_GBE1SEL_tx                   (1 << 5)  /* Gbe1Sel Tx */

#define INTC_IPTSR_GBE0SEL_rx                   (1 << 6)  /* Gbe0Sel Rx */

#define INTC_IPTSR_GBE1SEL_rx                   (1 << 7)  /* Gbe1Sel Rx */

/* INTC ISCLR Register Bit Definitions *******************************/

#define INTC_ISCLR_ICLRn_SHIFT                  (0)      /* Bits 0-15: Iclrn */
#define INTC_ISCLR_ICLRn_MASK                   (0xffff << INTC_ISCLR_ICLRn_SHIFT)

/* INTC ISCTR Register Bit Definitions *******************************/

#define INTC_ISCTR_ISTATn_SHIFT                 (0)      /* Bits 0-15: Istatn */
#define INTC_ISCTR_ISTATn_MASK                  (0xffff << INTC_ISCTR_ISTATn_SHIFT)

/* INTC NITSR Register Bit Definitions *******************************/

#define INTC_NITSR_NTSEL                        (1 << 0)  /* Ntsel */

/* INTC NSCLR Register Bit Definitions *******************************/

#define INTC_NSCLR_NCLR                         (1 << 0)  /* Nclr */

/* INTC NSCNT Register Bit Definitions *******************************/

#define INTC_NSCNT_NSTAT                        (1 << 0)  /* Nstat */

#define INTC_NSCNT_NSMON                        (1 << 16)  /* Nsmon */

/* INTC OFFDMCLR0 Register Bit Definitions ***************************/

#define INTC_OFFDMCLR0_ODCLR0_SHIFT             (0)      /* Bits 0-31: Odclr0 */
#define INTC_OFFDMCLR0_ODCLR0_MASK              (0xffffffff << INTC_OFFDMCLR0_ODCLR0_SHIFT)

/* INTC OFFDMCLR1 Register Bit Definitions ***************************/

#define INTC_OFFDMCLR1_ODCLR1_SHIFT             (0)      /* Bits 0-31: Odclr1 */
#define INTC_OFFDMCLR1_ODCLR1_MASK              (0xffffffff << INTC_OFFDMCLR1_ODCLR1_SHIFT)

/* INTC OFFDMCLR2 Register Bit Definitions ***************************/

#define INTC_OFFDMCLR2_ODCLR2_SHIFT             (0)      /* Bits 0-31: Odclr2 */
#define INTC_OFFDMCLR2_ODCLR2_MASK              (0xffffffff << INTC_OFFDMCLR2_ODCLR2_SHIFT)

/* INTC SWEVT Register Bit Definitions *******************************/

/* SWE fields (parameterized for indices 0-6) */
#define INTC_SWEVT_SWE(n)                                 (1u << (0 + ((unsigned)(n) * 1)))  /* Swe0 */

/* INTC SWINT Register Bit Definitions *******************************/

/* IA fields (parameterized for indices 0-3) */
#define INTC_SWINT_IA(n)                                  (1u << (0 + ((unsigned)(n) * 1)))  /* Ia550 */

/* IM fields (parameterized for indices 0-3) */
#define INTC_SWINT_IM(n)                                  (1u << (16 + ((unsigned)(n) * 1)))  /* Im330 */

/* IR fields (parameterized for indices 0-3) */
#define INTC_SWINT_IR(n)                                  (1u << (8 + ((unsigned)(n) * 1)))  /* Ir80 */

/* INTC SWPE Register Bit Definitions ********************************/

#define INTC_SWPE_PEn_SHIFT                     (0)      /* Bits 0-15: Pen */
#define INTC_SWPE_PEn_MASK                      (0xffff << INTC_SWPE_PEn_SHIFT)

/* INTC TSCLR Register Bit Definitions *******************************/

#define INTC_TSCLR_TCLRn_SHIFT                  (0)      /* Bits 0-31: Tclrn */
#define INTC_TSCLR_TCLRn_MASK                   (0xffffffff << INTC_TSCLR_TCLRn_SHIFT)

/* INTC TSCTR Register Bit Definitions *******************************/

#define INTC_TSCTR_TSTATn_SHIFT                 (0)      /* Bits 0-31: Tstatn */
#define INTC_TSCTR_TSTATn_MASK                  (0xffffffff << INTC_TSCTR_TSTATn_SHIFT)

/* INTC Channel definitions */
#define RZV_INTC_CHANNEL_0         0

/* Maximum number of INTC channels */
#define RZV_INTC_MAX_CHANNELS      1

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_INTC_H */

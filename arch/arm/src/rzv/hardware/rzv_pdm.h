/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_pdm.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_PDM_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_PDM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* PDM Base Addresses ****************************************************/

#ifndef RZV_PDM0_BASE
#  define RZV_PDM0_BASE               0x11040000
#endif
#ifndef RZV_PDM1_BASE
#  define RZV_PDM1_BASE               0x11050000
#endif

/* PDM Register Offsets ***************************************************/

/* PDCHGTRCH%s Registers (0-2) */
#define RZV_PDM_PDCHGTRCH_OFFSET(m)             (0x00000108 + ((m) * 0x00000100))  /* PDCHGTRCH Register %s */
/* PDDBCRCH%s Registers (0-2) */
#define RZV_PDM_PDDBCRCH_OFFSET(m)              (0x000001c0 + ((m) * 0x00000100))  /* PDDBCRCH Register %s */
/* PDDCRCH%s Registers (0-2) */
#define RZV_PDM_PDDCRCH_OFFSET(m)               (0x000001e4 + ((m) * 0x00000100))  /* PDDCRCH Register %s */
/* PDDRCRCH%s Registers (0-2) */
#define RZV_PDM_PDDRCRCH_OFFSET(m)              (0x000001e0 + ((m) * 0x00000100))  /* PDDRCRCH Register %s */
/* PDDRRCH%s Registers (0-2) */
#define RZV_PDM_PDDRRCH_OFFSET(m)               (0x000001e8 + ((m) * 0x00000100))  /* PDDRRCH Register %s */
/* PDDSRCH%s Registers (0-2) */
#define RZV_PDM_PDDSRCH_OFFSET(m)               (0x000001ec + ((m) * 0x00000100))  /* PDDSRCH Register %s */
/* PDICRCH%s Registers (0-2) */
#define RZV_PDM_PDICRCH_OFFSET(m)               (0x0000010c + ((m) * 0x00000100))  /* PDICRCH Register %s */
/* PDMDSRCH%s Registers (0-2) */
#define RZV_PDM_PDMDSRCH_OFFSET(m)              (0x00000120 + ((m) * 0x00000100))  /* PDMDSRCH Register %s */
/* PDOVLTRCH%s Registers (0-2) */
#define RZV_PDM_PDOVLTRCH_OFFSET(m)             (0x000001c8 + ((m) * 0x00000100))  /* PDOVLTRCH Register %s */
/* PDOVUTRCH%s Registers (0-2) */
#define RZV_PDM_PDOVUTRCH_OFFSET(m)             (0x000001cc + ((m) * 0x00000100))  /* PDOVUTRCH Register %s */
/* PDSCRCH%s Registers (0-2) */
#define RZV_PDM_PDSCRCH_OFFSET(m)               (0x00000118 + ((m) * 0x00000100))  /* PDSCRCH Register %s */
/* PDSCTSRCH%s Registers (0-2) */
#define RZV_PDM_PDSCTSRCH_OFFSET(m)             (0x000001c4 + ((m) * 0x00000100))  /* PDSCTSRCH Register %s */
/* PDSDCRCH%s Registers (0-2) */
#define RZV_PDM_PDSDCRCH_OFFSET(m)              (0x00000110 + ((m) * 0x00000100))  /* PDSDCRCH Register %s */
/* PDSDLTRCH%s Registers (0-2) */
#define RZV_PDM_PDSDLTRCH_OFFSET(m)             (0x000001b8 + ((m) * 0x00000100))  /* PDSDLTRCH Register %s */
/* PDSDUTRCH%s Registers (0-2) */
#define RZV_PDM_PDSDUTRCH_OFFSET(m)             (0x000001bc + ((m) * 0x00000100))  /* PDSDUTRCH Register %s */
/* PDSFCRCH%s Registers (0-2) */
#define RZV_PDM_PDSFCRCH_OFFSET(m)              (0x00000124 + ((m) * 0x00000100))  /* PDSFCRCH Register %s */
/* PDSRCH%s Registers (0-2) */
#define RZV_PDM_PDSRCH_OFFSET(m)                (0x00000114 + ((m) * 0x00000100))  /* PDSRCH Register %s */
/* PDSTPTRCH%s Registers (0-2) */
#define RZV_PDM_PDSTPTRCH_OFFSET(m)             (0x00000104 + ((m) * 0x00000100))  /* PDSTPTRCH Register %s */
/* PDSTRTRCH%s Registers (0-2) */
#define RZV_PDM_PDSTRTRCH_OFFSET(m)             (0x00000100 + ((m) * 0x00000100))  /* PDSTRTRCH Register %s */
#define RZV_PDM_PDCSTRTR_OFFSET                          0x0000  /* PDCSTRTR */
#define RZV_PDM_PDCSTPTR_OFFSET                          0x0004  /* PDCSTPTR */
#define RZV_PDM_PDCCHGTR_OFFSET                          0x0008  /* PDCCHGTR */
#define RZV_PDM_PDCICR_OFFSET                            0x000C  /* PDCICR */
#define RZV_PDM_PDCSR_OFFSET                             0x0010  /* PDCSR */
#define RZV_PDM_PDCSCR_OFFSET                            0x0014  /* PDCSCR */
#define RZV_PDM_PDCSDCR_OFFSET                           0x0020  /* PDCSDCR */
#define RZV_PDM_PDCDRCR_OFFSET                           0x0024  /* PDCDRCR */
#define RZV_PDM_PDCDCR_OFFSET                            0x0028  /* PDCDCR */
#define RZV_PDM_PDVR_OFFSET                              0x0080  /* PDVR */
#define RZV_PDM_PDHFCS0RCH0_OFFSET                       0x0128  /* PDHFCS0RCH0 */
#define RZV_PDM_PDHFCK1RCH0_OFFSET                       0x012C  /* PDHFCK1RCH0 */
#define RZV_PDM_PDHFCH0RCH0_OFFSET                       0x0130  /* PDHFCH0RCH0 */
#define RZV_PDM_PDHFCH1RCH0_OFFSET                       0x0134  /* PDHFCH1RCH0 */
#define RZV_PDM_PDCFCH00RCH0_OFFSET                      0x0138  /* PDCFCH00RCH0 */
#define RZV_PDM_PDCFCH01RCH0_OFFSET                      0x013C  /* PDCFCH01RCH0 */
#define RZV_PDM_PDCFCH02RCH0_OFFSET                      0x0140  /* PDCFCH02RCH0 */
#define RZV_PDM_PDCFCH03RCH0_OFFSET                      0x0144  /* PDCFCH03RCH0 */
#define RZV_PDM_PDCFCH04RCH0_OFFSET                      0x0148  /* PDCFCH04RCH0 */
#define RZV_PDM_PDCFCH05RCH0_OFFSET                      0x014C  /* PDCFCH05RCH0 */
#define RZV_PDM_PDCFCH06RCH0_OFFSET                      0x0150  /* PDCFCH06RCH0 */
#define RZV_PDM_PDCFCH07RCH0_OFFSET                      0x0154  /* PDCFCH07RCH0 */
#define RZV_PDM_PDCFCH08RCH0_OFFSET                      0x0158  /* PDCFCH08RCH0 */
#define RZV_PDM_PDCFCH09RCH0_OFFSET                      0x015C  /* PDCFCH09RCH0 */
#define RZV_PDM_PDCFCH10RCH0_OFFSET                      0x0160  /* PDCFCH10RCH0 */
#define RZV_PDM_PDLFCH010RCH0_OFFSET                     0x0164  /* PDLFCH010RCH0 */
#define RZV_PDM_PDLFCH100RCH0_OFFSET                     0x0168  /* PDLFCH100RCH0 */
#define RZV_PDM_PDLFCH101RCH0_OFFSET                     0x016C  /* PDLFCH101RCH0 */
#define RZV_PDM_PDLFCH102RCH0_OFFSET                     0x0170  /* PDLFCH102RCH0 */
#define RZV_PDM_PDLFCH103RCH0_OFFSET                     0x0174  /* PDLFCH103RCH0 */
#define RZV_PDM_PDLFCH104RCH0_OFFSET                     0x0178  /* PDLFCH104RCH0 */
#define RZV_PDM_PDLFCH105RCH0_OFFSET                     0x017C  /* PDLFCH105RCH0 */
#define RZV_PDM_PDLFCH106RCH0_OFFSET                     0x0180  /* PDLFCH106RCH0 */
#define RZV_PDM_PDLFCH107RCH0_OFFSET                     0x0184  /* PDLFCH107RCH0 */
#define RZV_PDM_PDLFCH108RCH0_OFFSET                     0x0188  /* PDLFCH108RCH0 */
#define RZV_PDM_PDLFCH109RCH0_OFFSET                     0x018C  /* PDLFCH109RCH0 */
#define RZV_PDM_PDLFCH110RCH0_OFFSET                     0x0190  /* PDLFCH110RCH0 */
#define RZV_PDM_PDLFCH111RCH0_OFFSET                     0x0194  /* PDLFCH111RCH0 */
#define RZV_PDM_PDLFCH112RCH0_OFFSET                     0x0198  /* PDLFCH112RCH0 */
#define RZV_PDM_PDLFCH113RCH0_OFFSET                     0x019C  /* PDLFCH113RCH0 */
#define RZV_PDM_PDLFCH114RCH0_OFFSET                     0x01A0  /* PDLFCH114RCH0 */
#define RZV_PDM_PDLFCH115RCH0_OFFSET                     0x01A4  /* PDLFCH115RCH0 */
#define RZV_PDM_PDLFCH116RCH0_OFFSET                     0x01A8  /* PDLFCH116RCH0 */
#define RZV_PDM_PDLFCH117RCH0_OFFSET                     0x01AC  /* PDLFCH117RCH0 */
#define RZV_PDM_PDLFCH118RCH0_OFFSET                     0x01B0  /* PDLFCH118RCH0 */
#define RZV_PDM_PDLFCH119RCH0_OFFSET                     0x01B4  /* PDLFCH119RCH0 */
#define RZV_PDM_PDHFCS0RCH1_OFFSET                       0x0228  /* PDHFCS0RCH1 */
#define RZV_PDM_PDHFCK1RCH1_OFFSET                       0x022C  /* PDHFCK1RCH1 */
#define RZV_PDM_PDHFCH0RCH1_OFFSET                       0x0230  /* PDHFCH0RCH1 */
#define RZV_PDM_PDHFCH1RCH1_OFFSET                       0x0234  /* PDHFCH1RCH1 */
#define RZV_PDM_PDCFCH00RCH1_OFFSET                      0x0238  /* PDCFCH00RCH1 */
#define RZV_PDM_PDCFCH01RCH1_OFFSET                      0x023C  /* PDCFCH01RCH1 */
#define RZV_PDM_PDCFCH02RCH1_OFFSET                      0x0240  /* PDCFCH02RCH1 */
#define RZV_PDM_PDCFCH03RCH1_OFFSET                      0x0244  /* PDCFCH03RCH1 */
#define RZV_PDM_PDCFCH04RCH1_OFFSET                      0x0248  /* PDCFCH04RCH1 */
#define RZV_PDM_PDCFCH05RCH1_OFFSET                      0x024C  /* PDCFCH05RCH1 */
#define RZV_PDM_PDCFCH06RCH1_OFFSET                      0x0250  /* PDCFCH06RCH1 */
#define RZV_PDM_PDCFCH07RCH1_OFFSET                      0x0254  /* PDCFCH07RCH1 */
#define RZV_PDM_PDCFCH08RCH1_OFFSET                      0x0258  /* PDCFCH08RCH1 */
#define RZV_PDM_PDCFCH09RCH1_OFFSET                      0x025C  /* PDCFCH09RCH1 */
#define RZV_PDM_PDCFCH10RCH1_OFFSET                      0x0260  /* PDCFCH10RCH1 */
#define RZV_PDM_PDLFCH010RCH1_OFFSET                     0x0264  /* PDLFCH010RCH1 */
#define RZV_PDM_PDLFCH100RCH1_OFFSET                     0x0268  /* PDLFCH100RCH1 */
#define RZV_PDM_PDLFCH101RCH1_OFFSET                     0x026C  /* PDLFCH101RCH1 */
#define RZV_PDM_PDLFCH102RCH1_OFFSET                     0x0270  /* PDLFCH102RCH1 */
#define RZV_PDM_PDLFCH103RCH1_OFFSET                     0x0274  /* PDLFCH103RCH1 */
#define RZV_PDM_PDLFCH104RCH1_OFFSET                     0x0278  /* PDLFCH104RCH1 */
#define RZV_PDM_PDLFCH105RCH1_OFFSET                     0x027C  /* PDLFCH105RCH1 */
#define RZV_PDM_PDLFCH106RCH1_OFFSET                     0x0280  /* PDLFCH106RCH1 */
#define RZV_PDM_PDLFCH107RCH1_OFFSET                     0x0284  /* PDLFCH107RCH1 */
#define RZV_PDM_PDLFCH108RCH1_OFFSET                     0x0288  /* PDLFCH108RCH1 */
#define RZV_PDM_PDLFCH109RCH1_OFFSET                     0x028C  /* PDLFCH109RCH1 */
#define RZV_PDM_PDLFCH110RCH1_OFFSET                     0x0290  /* PDLFCH110RCH1 */
#define RZV_PDM_PDLFCH111RCH1_OFFSET                     0x0294  /* PDLFCH111RCH1 */
#define RZV_PDM_PDLFCH112RCH1_OFFSET                     0x0298  /* PDLFCH112RCH1 */
#define RZV_PDM_PDLFCH113RCH1_OFFSET                     0x029C  /* PDLFCH113RCH1 */
#define RZV_PDM_PDLFCH114RCH1_OFFSET                     0x02A0  /* PDLFCH114RCH1 */
#define RZV_PDM_PDLFCH115RCH1_OFFSET                     0x02A4  /* PDLFCH115RCH1 */
#define RZV_PDM_PDLFCH116RCH1_OFFSET                     0x02A8  /* PDLFCH116RCH1 */
#define RZV_PDM_PDLFCH117RCH1_OFFSET                     0x02AC  /* PDLFCH117RCH1 */
#define RZV_PDM_PDLFCH118RCH1_OFFSET                     0x02B0  /* PDLFCH118RCH1 */
#define RZV_PDM_PDLFCH119RCH1_OFFSET                     0x02B4  /* PDLFCH119RCH1 */
#define RZV_PDM_PDHFCS0RCH2_OFFSET                       0x0328  /* PDHFCS0RCH2 */
#define RZV_PDM_PDHFCK1RCH2_OFFSET                       0x032C  /* PDHFCK1RCH2 */
#define RZV_PDM_PDHFCH0RCH2_OFFSET                       0x0330  /* PDHFCH0RCH2 */
#define RZV_PDM_PDHFCH1RCH2_OFFSET                       0x0334  /* PDHFCH1RCH2 */
#define RZV_PDM_PDCFCH00RCH2_OFFSET                      0x0338  /* PDCFCH00RCH2 */
#define RZV_PDM_PDCFCH01RCH2_OFFSET                      0x033C  /* PDCFCH01RCH2 */
#define RZV_PDM_PDCFCH02RCH2_OFFSET                      0x0340  /* PDCFCH02RCH2 */
#define RZV_PDM_PDCFCH03RCH2_OFFSET                      0x0344  /* PDCFCH03RCH2 */
#define RZV_PDM_PDCFCH04RCH2_OFFSET                      0x0348  /* PDCFCH04RCH2 */
#define RZV_PDM_PDCFCH05RCH2_OFFSET                      0x034C  /* PDCFCH05RCH2 */
#define RZV_PDM_PDCFCH06RCH2_OFFSET                      0x0350  /* PDCFCH06RCH2 */
#define RZV_PDM_PDCFCH07RCH2_OFFSET                      0x0354  /* PDCFCH07RCH2 */
#define RZV_PDM_PDCFCH08RCH2_OFFSET                      0x0358  /* PDCFCH08RCH2 */
#define RZV_PDM_PDCFCH09RCH2_OFFSET                      0x035C  /* PDCFCH09RCH2 */
#define RZV_PDM_PDCFCH10RCH2_OFFSET                      0x0360  /* PDCFCH10RCH2 */
#define RZV_PDM_PDLFCH010RCH2_OFFSET                     0x0364  /* PDLFCH010RCH2 */
#define RZV_PDM_PDLFCH100RCH2_OFFSET                     0x0368  /* PDLFCH100RCH2 */
#define RZV_PDM_PDLFCH101RCH2_OFFSET                     0x036C  /* PDLFCH101RCH2 */
#define RZV_PDM_PDLFCH102RCH2_OFFSET                     0x0370  /* PDLFCH102RCH2 */
#define RZV_PDM_PDLFCH103RCH2_OFFSET                     0x0374  /* PDLFCH103RCH2 */
#define RZV_PDM_PDLFCH104RCH2_OFFSET                     0x0378  /* PDLFCH104RCH2 */
#define RZV_PDM_PDLFCH105RCH2_OFFSET                     0x037C  /* PDLFCH105RCH2 */
#define RZV_PDM_PDLFCH106RCH2_OFFSET                     0x0380  /* PDLFCH106RCH2 */
#define RZV_PDM_PDLFCH107RCH2_OFFSET                     0x0384  /* PDLFCH107RCH2 */
#define RZV_PDM_PDLFCH108RCH2_OFFSET                     0x0388  /* PDLFCH108RCH2 */
#define RZV_PDM_PDLFCH109RCH2_OFFSET                     0x038C  /* PDLFCH109RCH2 */
#define RZV_PDM_PDLFCH110RCH2_OFFSET                     0x0390  /* PDLFCH110RCH2 */
#define RZV_PDM_PDLFCH111RCH2_OFFSET                     0x0394  /* PDLFCH111RCH2 */
#define RZV_PDM_PDLFCH112RCH2_OFFSET                     0x0398  /* PDLFCH112RCH2 */
#define RZV_PDM_PDLFCH113RCH2_OFFSET                     0x039C  /* PDLFCH113RCH2 */
#define RZV_PDM_PDLFCH114RCH2_OFFSET                     0x03A0  /* PDLFCH114RCH2 */
#define RZV_PDM_PDLFCH115RCH2_OFFSET                     0x03A4  /* PDLFCH115RCH2 */
#define RZV_PDM_PDLFCH116RCH2_OFFSET                     0x03A8  /* PDLFCH116RCH2 */
#define RZV_PDM_PDLFCH117RCH2_OFFSET                     0x03AC  /* PDLFCH117RCH2 */
#define RZV_PDM_PDLFCH118RCH2_OFFSET                     0x03B0  /* PDLFCH118RCH2 */
#define RZV_PDM_PDLFCH119RCH2_OFFSET                     0x03B4  /* PDLFCH119RCH2 */

/* PDM Register Addresses **************************************************/

#define RZV_PDM_PDCHGTRCH(ch,m)                 (RZV_PDM##ch##_BASE + RZV_PDM_PDCHGTRCH_OFFSET(m))
#define RZV_PDM_PDDBCRCH(ch,m)                  (RZV_PDM##ch##_BASE + RZV_PDM_PDDBCRCH_OFFSET(m))
#define RZV_PDM_PDDCRCH(ch,m)                   (RZV_PDM##ch##_BASE + RZV_PDM_PDDCRCH_OFFSET(m))
#define RZV_PDM_PDDRCRCH(ch,m)                  (RZV_PDM##ch##_BASE + RZV_PDM_PDDRCRCH_OFFSET(m))
#define RZV_PDM_PDDRRCH(ch,m)                   (RZV_PDM##ch##_BASE + RZV_PDM_PDDRRCH_OFFSET(m))
#define RZV_PDM_PDDSRCH(ch,m)                   (RZV_PDM##ch##_BASE + RZV_PDM_PDDSRCH_OFFSET(m))
#define RZV_PDM_PDICRCH(ch,m)                   (RZV_PDM##ch##_BASE + RZV_PDM_PDICRCH_OFFSET(m))
#define RZV_PDM_PDMDSRCH(ch,m)                  (RZV_PDM##ch##_BASE + RZV_PDM_PDMDSRCH_OFFSET(m))
#define RZV_PDM_PDOVLTRCH(ch,m)                 (RZV_PDM##ch##_BASE + RZV_PDM_PDOVLTRCH_OFFSET(m))
#define RZV_PDM_PDOVUTRCH(ch,m)                 (RZV_PDM##ch##_BASE + RZV_PDM_PDOVUTRCH_OFFSET(m))
#define RZV_PDM_PDSCRCH(ch,m)                   (RZV_PDM##ch##_BASE + RZV_PDM_PDSCRCH_OFFSET(m))
#define RZV_PDM_PDSCTSRCH(ch,m)                 (RZV_PDM##ch##_BASE + RZV_PDM_PDSCTSRCH_OFFSET(m))
#define RZV_PDM_PDSDCRCH(ch,m)                  (RZV_PDM##ch##_BASE + RZV_PDM_PDSDCRCH_OFFSET(m))
#define RZV_PDM_PDSDLTRCH(ch,m)                 (RZV_PDM##ch##_BASE + RZV_PDM_PDSDLTRCH_OFFSET(m))
#define RZV_PDM_PDSDUTRCH(ch,m)                 (RZV_PDM##ch##_BASE + RZV_PDM_PDSDUTRCH_OFFSET(m))
#define RZV_PDM_PDSFCRCH(ch,m)                  (RZV_PDM##ch##_BASE + RZV_PDM_PDSFCRCH_OFFSET(m))
#define RZV_PDM_PDSRCH(ch,m)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDSRCH_OFFSET(m))
#define RZV_PDM_PDSTPTRCH(ch,m)                 (RZV_PDM##ch##_BASE + RZV_PDM_PDSTPTRCH_OFFSET(m))
#define RZV_PDM_PDSTRTRCH(ch,m)                 (RZV_PDM##ch##_BASE + RZV_PDM_PDSTRTRCH_OFFSET(m))
#define RZV_PDM_PDCSTRTR(ch)                         (RZV_PDM##ch##_BASE + RZV_PDM_PDCSTRTR_OFFSET)
#define RZV_PDM_PDCSTPTR(ch)                         (RZV_PDM##ch##_BASE + RZV_PDM_PDCSTPTR_OFFSET)
#define RZV_PDM_PDCCHGTR(ch)                         (RZV_PDM##ch##_BASE + RZV_PDM_PDCCHGTR_OFFSET)
#define RZV_PDM_PDCICR(ch)                           (RZV_PDM##ch##_BASE + RZV_PDM_PDCICR_OFFSET)
#define RZV_PDM_PDCSR(ch)                            (RZV_PDM##ch##_BASE + RZV_PDM_PDCSR_OFFSET)
#define RZV_PDM_PDCSCR(ch)                           (RZV_PDM##ch##_BASE + RZV_PDM_PDCSCR_OFFSET)
#define RZV_PDM_PDCSDCR(ch)                          (RZV_PDM##ch##_BASE + RZV_PDM_PDCSDCR_OFFSET)
#define RZV_PDM_PDCDRCR(ch)                          (RZV_PDM##ch##_BASE + RZV_PDM_PDCDRCR_OFFSET)
#define RZV_PDM_PDCDCR(ch)                           (RZV_PDM##ch##_BASE + RZV_PDM_PDCDCR_OFFSET)
#define RZV_PDM_PDVR(ch)                             (RZV_PDM##ch##_BASE + RZV_PDM_PDVR_OFFSET)
#define RZV_PDM_PDHFCS0RCH0(ch)                      (RZV_PDM##ch##_BASE + RZV_PDM_PDHFCS0RCH0_OFFSET)
#define RZV_PDM_PDHFCK1RCH0(ch)                      (RZV_PDM##ch##_BASE + RZV_PDM_PDHFCK1RCH0_OFFSET)
#define RZV_PDM_PDHFCH0RCH0(ch)                      (RZV_PDM##ch##_BASE + RZV_PDM_PDHFCH0RCH0_OFFSET)
#define RZV_PDM_PDHFCH1RCH0(ch)                      (RZV_PDM##ch##_BASE + RZV_PDM_PDHFCH1RCH0_OFFSET)
#define RZV_PDM_PDCFCH00RCH0(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH00RCH0_OFFSET)
#define RZV_PDM_PDCFCH01RCH0(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH01RCH0_OFFSET)
#define RZV_PDM_PDCFCH02RCH0(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH02RCH0_OFFSET)
#define RZV_PDM_PDCFCH03RCH0(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH03RCH0_OFFSET)
#define RZV_PDM_PDCFCH04RCH0(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH04RCH0_OFFSET)
#define RZV_PDM_PDCFCH05RCH0(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH05RCH0_OFFSET)
#define RZV_PDM_PDCFCH06RCH0(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH06RCH0_OFFSET)
#define RZV_PDM_PDCFCH07RCH0(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH07RCH0_OFFSET)
#define RZV_PDM_PDCFCH08RCH0(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH08RCH0_OFFSET)
#define RZV_PDM_PDCFCH09RCH0(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH09RCH0_OFFSET)
#define RZV_PDM_PDCFCH10RCH0(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH10RCH0_OFFSET)
#define RZV_PDM_PDLFCH010RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH010RCH0_OFFSET)
#define RZV_PDM_PDLFCH100RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH100RCH0_OFFSET)
#define RZV_PDM_PDLFCH101RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH101RCH0_OFFSET)
#define RZV_PDM_PDLFCH102RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH102RCH0_OFFSET)
#define RZV_PDM_PDLFCH103RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH103RCH0_OFFSET)
#define RZV_PDM_PDLFCH104RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH104RCH0_OFFSET)
#define RZV_PDM_PDLFCH105RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH105RCH0_OFFSET)
#define RZV_PDM_PDLFCH106RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH106RCH0_OFFSET)
#define RZV_PDM_PDLFCH107RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH107RCH0_OFFSET)
#define RZV_PDM_PDLFCH108RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH108RCH0_OFFSET)
#define RZV_PDM_PDLFCH109RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH109RCH0_OFFSET)
#define RZV_PDM_PDLFCH110RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH110RCH0_OFFSET)
#define RZV_PDM_PDLFCH111RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH111RCH0_OFFSET)
#define RZV_PDM_PDLFCH112RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH112RCH0_OFFSET)
#define RZV_PDM_PDLFCH113RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH113RCH0_OFFSET)
#define RZV_PDM_PDLFCH114RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH114RCH0_OFFSET)
#define RZV_PDM_PDLFCH115RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH115RCH0_OFFSET)
#define RZV_PDM_PDLFCH116RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH116RCH0_OFFSET)
#define RZV_PDM_PDLFCH117RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH117RCH0_OFFSET)
#define RZV_PDM_PDLFCH118RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH118RCH0_OFFSET)
#define RZV_PDM_PDLFCH119RCH0(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH119RCH0_OFFSET)
#define RZV_PDM_PDHFCS0RCH1(ch)                      (RZV_PDM##ch##_BASE + RZV_PDM_PDHFCS0RCH1_OFFSET)
#define RZV_PDM_PDHFCK1RCH1(ch)                      (RZV_PDM##ch##_BASE + RZV_PDM_PDHFCK1RCH1_OFFSET)
#define RZV_PDM_PDHFCH0RCH1(ch)                      (RZV_PDM##ch##_BASE + RZV_PDM_PDHFCH0RCH1_OFFSET)
#define RZV_PDM_PDHFCH1RCH1(ch)                      (RZV_PDM##ch##_BASE + RZV_PDM_PDHFCH1RCH1_OFFSET)
#define RZV_PDM_PDCFCH00RCH1(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH00RCH1_OFFSET)
#define RZV_PDM_PDCFCH01RCH1(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH01RCH1_OFFSET)
#define RZV_PDM_PDCFCH02RCH1(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH02RCH1_OFFSET)
#define RZV_PDM_PDCFCH03RCH1(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH03RCH1_OFFSET)
#define RZV_PDM_PDCFCH04RCH1(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH04RCH1_OFFSET)
#define RZV_PDM_PDCFCH05RCH1(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH05RCH1_OFFSET)
#define RZV_PDM_PDCFCH06RCH1(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH06RCH1_OFFSET)
#define RZV_PDM_PDCFCH07RCH1(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH07RCH1_OFFSET)
#define RZV_PDM_PDCFCH08RCH1(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH08RCH1_OFFSET)
#define RZV_PDM_PDCFCH09RCH1(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH09RCH1_OFFSET)
#define RZV_PDM_PDCFCH10RCH1(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH10RCH1_OFFSET)
#define RZV_PDM_PDLFCH010RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH010RCH1_OFFSET)
#define RZV_PDM_PDLFCH100RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH100RCH1_OFFSET)
#define RZV_PDM_PDLFCH101RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH101RCH1_OFFSET)
#define RZV_PDM_PDLFCH102RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH102RCH1_OFFSET)
#define RZV_PDM_PDLFCH103RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH103RCH1_OFFSET)
#define RZV_PDM_PDLFCH104RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH104RCH1_OFFSET)
#define RZV_PDM_PDLFCH105RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH105RCH1_OFFSET)
#define RZV_PDM_PDLFCH106RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH106RCH1_OFFSET)
#define RZV_PDM_PDLFCH107RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH107RCH1_OFFSET)
#define RZV_PDM_PDLFCH108RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH108RCH1_OFFSET)
#define RZV_PDM_PDLFCH109RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH109RCH1_OFFSET)
#define RZV_PDM_PDLFCH110RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH110RCH1_OFFSET)
#define RZV_PDM_PDLFCH111RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH111RCH1_OFFSET)
#define RZV_PDM_PDLFCH112RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH112RCH1_OFFSET)
#define RZV_PDM_PDLFCH113RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH113RCH1_OFFSET)
#define RZV_PDM_PDLFCH114RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH114RCH1_OFFSET)
#define RZV_PDM_PDLFCH115RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH115RCH1_OFFSET)
#define RZV_PDM_PDLFCH116RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH116RCH1_OFFSET)
#define RZV_PDM_PDLFCH117RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH117RCH1_OFFSET)
#define RZV_PDM_PDLFCH118RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH118RCH1_OFFSET)
#define RZV_PDM_PDLFCH119RCH1(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH119RCH1_OFFSET)
#define RZV_PDM_PDHFCS0RCH2(ch)                      (RZV_PDM##ch##_BASE + RZV_PDM_PDHFCS0RCH2_OFFSET)
#define RZV_PDM_PDHFCK1RCH2(ch)                      (RZV_PDM##ch##_BASE + RZV_PDM_PDHFCK1RCH2_OFFSET)
#define RZV_PDM_PDHFCH0RCH2(ch)                      (RZV_PDM##ch##_BASE + RZV_PDM_PDHFCH0RCH2_OFFSET)
#define RZV_PDM_PDHFCH1RCH2(ch)                      (RZV_PDM##ch##_BASE + RZV_PDM_PDHFCH1RCH2_OFFSET)
#define RZV_PDM_PDCFCH00RCH2(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH00RCH2_OFFSET)
#define RZV_PDM_PDCFCH01RCH2(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH01RCH2_OFFSET)
#define RZV_PDM_PDCFCH02RCH2(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH02RCH2_OFFSET)
#define RZV_PDM_PDCFCH03RCH2(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH03RCH2_OFFSET)
#define RZV_PDM_PDCFCH04RCH2(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH04RCH2_OFFSET)
#define RZV_PDM_PDCFCH05RCH2(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH05RCH2_OFFSET)
#define RZV_PDM_PDCFCH06RCH2(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH06RCH2_OFFSET)
#define RZV_PDM_PDCFCH07RCH2(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH07RCH2_OFFSET)
#define RZV_PDM_PDCFCH08RCH2(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH08RCH2_OFFSET)
#define RZV_PDM_PDCFCH09RCH2(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH09RCH2_OFFSET)
#define RZV_PDM_PDCFCH10RCH2(ch)                     (RZV_PDM##ch##_BASE + RZV_PDM_PDCFCH10RCH2_OFFSET)
#define RZV_PDM_PDLFCH010RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH010RCH2_OFFSET)
#define RZV_PDM_PDLFCH100RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH100RCH2_OFFSET)
#define RZV_PDM_PDLFCH101RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH101RCH2_OFFSET)
#define RZV_PDM_PDLFCH102RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH102RCH2_OFFSET)
#define RZV_PDM_PDLFCH103RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH103RCH2_OFFSET)
#define RZV_PDM_PDLFCH104RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH104RCH2_OFFSET)
#define RZV_PDM_PDLFCH105RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH105RCH2_OFFSET)
#define RZV_PDM_PDLFCH106RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH106RCH2_OFFSET)
#define RZV_PDM_PDLFCH107RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH107RCH2_OFFSET)
#define RZV_PDM_PDLFCH108RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH108RCH2_OFFSET)
#define RZV_PDM_PDLFCH109RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH109RCH2_OFFSET)
#define RZV_PDM_PDLFCH110RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH110RCH2_OFFSET)
#define RZV_PDM_PDLFCH111RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH111RCH2_OFFSET)
#define RZV_PDM_PDLFCH112RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH112RCH2_OFFSET)
#define RZV_PDM_PDLFCH113RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH113RCH2_OFFSET)
#define RZV_PDM_PDLFCH114RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH114RCH2_OFFSET)
#define RZV_PDM_PDLFCH115RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH115RCH2_OFFSET)
#define RZV_PDM_PDLFCH116RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH116RCH2_OFFSET)
#define RZV_PDM_PDLFCH117RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH117RCH2_OFFSET)
#define RZV_PDM_PDLFCH118RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH118RCH2_OFFSET)
#define RZV_PDM_PDLFCH119RCH2(ch)                    (RZV_PDM##ch##_BASE + RZV_PDM_PDLFCH119RCH2_OFFSET)

/* PDM PDCHGTRCH Register Bit Definitions (Parameterized) ******************/

#define PDM_PDCHGTRCH_CHGTRG(m)                           (1 << 0)  /* Chgtrg */

/* PDM PDDBCRCH Register Bit Definitions (Parameterized) *******************/

#define PDM_PDDBCRCH_DATRITHR_SHIFT                       (0)      /* Bits 0-2: Datrithr */
#define PDM_PDDBCRCH_DATRITHR_MASK(m)                     (0x7 << PDM_PDDBCRCH_DATRITHR_SHIFT)
#define PDM_PDDBCRCH_DATRITHR(m,val)                      (((val) << PDM_PDDBCRCH_DATRITHR_SHIFT) & PDM_PDDBCRCH_DATRITHR_MASK(m))

/* PDM PDDCRCH Register Bit Definitions (Parameterized) ********************/

#define PDM_PDDCRCH_DATC(m)                               (1 << 0)  /* Datc */

/* PDM PDDRCRCH Register Bit Definitions (Parameterized) *******************/

#define PDM_PDDRCRCH_DATRE(m)                             (1 << 0)  /* Datre */

/* PDM PDDRRCH Register Bit Definitions (Parameterized) ********************/

#define PDM_PDDRRCH_DAT_SHIFT                             (0)      /* Bits 0-19: Dat */
#define PDM_PDDRRCH_DAT_MASK(m)                           (0xfffff << PDM_PDDRRCH_DAT_SHIFT)
#define PDM_PDDRRCH_DAT(m,val)                            (((val) << PDM_PDDRRCH_DAT_SHIFT) & PDM_PDDRRCH_DAT_MASK(m))

/* PDM PDDSRCH Register Bit Definitions (Parameterized) ********************/

#define PDM_PDDSRCH_DATNUM_SHIFT                          (0)      /* Bits 0-7: Datnum */
#define PDM_PDDSRCH_DATNUM_MASK(m)                        (0xff << PDM_PDDSRCH_DATNUM_SHIFT)
#define PDM_PDDSRCH_DATNUM(m,val)                         (((val) << PDM_PDDSRCH_DATNUM_SHIFT) & PDM_PDDSRCH_DATNUM_MASK(m))

/* PDM PDICRCH Register Bit Definitions (Parameterized) ********************/

#define PDM_PDICRCH_ISDE(m)                               (1 << 1)  /* Isde */
#define PDM_PDICRCH_IDRE(m)                               (1 << 2)  /* Idre */
#define PDM_PDICRCH_IEDE(m)                               (1 << 16)  /* Iede */

/* PDM PDMDSRCH Register Bit Definitions (Parameterized) *******************/

#define PDM_PDMDSRCH_INPSEL(m)                            (1 << 0)  /* Inpsel */
#define PDM_PDMDSRCH_SFMD_SHIFT                           (4)      /* Bits 4-6: Sfmd */
#define PDM_PDMDSRCH_SFMD_MASK(m)                         (0x7 << PDM_PDMDSRCH_SFMD_SHIFT)
#define PDM_PDMDSRCH_SFMD(m,val)                          (((val) << PDM_PDMDSRCH_SFMD_SHIFT) & PDM_PDMDSRCH_SFMD_MASK(m))
#define PDM_PDMDSRCH_HFIS_SHIFT                           (8)      /* Bits 8-9: Hfis */
#define PDM_PDMDSRCH_HFIS_MASK(m)                         (0x3 << PDM_PDMDSRCH_HFIS_SHIFT)
#define PDM_PDMDSRCH_HFIS(m,val)                          (((val) << PDM_PDMDSRCH_HFIS_SHIFT) & PDM_PDMDSRCH_HFIS_MASK(m))
#define PDM_PDMDSRCH_CFIS_SHIFT                           (12)      /* Bits 12-13: Cfis */
#define PDM_PDMDSRCH_CFIS_MASK(m)                         (0x3 << PDM_PDMDSRCH_CFIS_SHIFT)
#define PDM_PDMDSRCH_CFIS(m,val)                          (((val) << PDM_PDMDSRCH_CFIS_SHIFT) & PDM_PDMDSRCH_CFIS_MASK(m))
#define PDM_PDMDSRCH_LFIS_SHIFT                           (16)      /* Bits 16-17: Lfis */
#define PDM_PDMDSRCH_LFIS_MASK(m)                         (0x3 << PDM_PDMDSRCH_LFIS_SHIFT)
#define PDM_PDMDSRCH_LFIS(m,val)                          (((val) << PDM_PDMDSRCH_LFIS_SHIFT) & PDM_PDMDSRCH_LFIS_MASK(m))
#define PDM_PDMDSRCH_SDMAMD_SHIFT                         (24)      /* Bits 24-25: Sdmamd */
#define PDM_PDMDSRCH_SDMAMD_MASK(m)                       (0x3 << PDM_PDMDSRCH_SDMAMD_SHIFT)
#define PDM_PDMDSRCH_SDMAMD(m,val)                        (((val) << PDM_PDMDSRCH_SDMAMD_SHIFT) & PDM_PDMDSRCH_SDMAMD_MASK(m))
#define PDM_PDMDSRCH_DBIS_SHIFT                           (28)      /* Bits 28-31: Dbis */
#define PDM_PDMDSRCH_DBIS_MASK(m)                         (0xf << PDM_PDMDSRCH_DBIS_SHIFT)
#define PDM_PDMDSRCH_DBIS(m,val)                          (((val) << PDM_PDMDSRCH_DBIS_SHIFT) & PDM_PDMDSRCH_DBIS_MASK(m))

/* PDM PDOVLTRCH Register Bit Definitions (Parameterized) ******************/

#define PDM_PDOVLTRCH_OVDL_SHIFT                          (0)      /* Bits 0-19: Ovdl */
#define PDM_PDOVLTRCH_OVDL_MASK(m)                        (0xfffff << PDM_PDOVLTRCH_OVDL_SHIFT)
#define PDM_PDOVLTRCH_OVDL(m,val)                         (((val) << PDM_PDOVLTRCH_OVDL_SHIFT) & PDM_PDOVLTRCH_OVDL_MASK(m))

/* PDM PDOVUTRCH Register Bit Definitions (Parameterized) ******************/

#define PDM_PDOVUTRCH_OVDU_SHIFT                          (0)      /* Bits 0-19: Ovdu */
#define PDM_PDOVUTRCH_OVDU_MASK(m)                        (0xfffff << PDM_PDOVUTRCH_OVDU_SHIFT)
#define PDM_PDOVUTRCH_OVDU(m,val)                         (((val) << PDM_PDOVUTRCH_OVDU_SHIFT) & PDM_PDOVUTRCH_OVDU_MASK(m))

/* PDM PDSCRCH Register Bit Definitions (Parameterized) ********************/

#define PDM_PDSCRCH_SDFC(m)                               (1 << 1)  /* Sdfc */
#define PDM_PDSCRCH_SCDFC(m)                              (1 << 16)  /* Scdfc */
#define PDM_PDSCRCH_OVLDFC(m)                             (1 << 17)  /* Ovldfc */
#define PDM_PDSCRCH_OVUDFC(m)                             (1 << 18)  /* Ovudfc */
#define PDM_PDSCRCH_BFOWDFC(m)                            (1 << 27)  /* Bfowdfc */

/* PDM PDSCTSRCH Register Bit Definitions (Parameterized) ******************/

#define PDM_PDSCTSRCH_SCDL_SHIFT                          (0)      /* Bits 0-12: Scdl */
#define PDM_PDSCTSRCH_SCDL_MASK(m)                        (0x1fff << PDM_PDSCTSRCH_SCDL_SHIFT)
#define PDM_PDSCTSRCH_SCDL(m,val)                         (((val) << PDM_PDSCTSRCH_SCDL_SHIFT) & PDM_PDSCTSRCH_SCDL_MASK(m))
#define PDM_PDSCTSRCH_SCDH_SHIFT                          (16)      /* Bits 16-28: Scdh */
#define PDM_PDSCTSRCH_SCDH_MASK(m)                        (0x1fff << PDM_PDSCTSRCH_SCDH_SHIFT)
#define PDM_PDSCTSRCH_SCDH(m,val)                         (((val) << PDM_PDSCTSRCH_SCDH_SHIFT) & PDM_PDSCTSRCH_SCDH_MASK(m))

/* PDM PDSDCRCH Register Bit Definitions (Parameterized) *******************/

#define PDM_PDSDCRCH_SDE(m)                               (1 << 1)  /* Sde */
#define PDM_PDSDCRCH_SCDE(m)                              (1 << 16)  /* Scde */
#define PDM_PDSDCRCH_OVLDE(m)                             (1 << 17)  /* Ovlde */
#define PDM_PDSDCRCH_OVUDE(m)                             (1 << 18)  /* Ovude */
#define PDM_PDSDCRCH_BFOWDE(m)                            (1 << 27)  /* Bfowde */

/* PDM PDSDLTRCH Register Bit Definitions (Parameterized) ******************/

#define PDM_PDSDLTRCH_SDETL_SHIFT                         (0)      /* Bits 0-19: Sdetl */
#define PDM_PDSDLTRCH_SDETL_MASK(m)                       (0xfffff << PDM_PDSDLTRCH_SDETL_SHIFT)
#define PDM_PDSDLTRCH_SDETL(m,val)                        (((val) << PDM_PDSDLTRCH_SDETL_SHIFT) & PDM_PDSDLTRCH_SDETL_MASK(m))

/* PDM PDSDUTRCH Register Bit Definitions (Parameterized) ******************/

#define PDM_PDSDUTRCH_SDETU_SHIFT                         (0)      /* Bits 0-19: Sdetu */
#define PDM_PDSDUTRCH_SDETU_MASK(m)                       (0xfffff << PDM_PDSDUTRCH_SDETU_SHIFT)
#define PDM_PDSDUTRCH_SDETU(m,val)                        (((val) << PDM_PDSDUTRCH_SDETU_SHIFT) & PDM_PDSDUTRCH_SDETU_MASK(m))

/* PDM PDSFCRCH Register Bit Definitions (Parameterized) *******************/

#define PDM_PDSFCRCH_CKDIV_SHIFT                          (0)      /* Bits 0-3: Ckdiv */
#define PDM_PDSFCRCH_CKDIV_MASK(m)                        (0xf << PDM_PDSFCRCH_CKDIV_SHIFT)
#define PDM_PDSFCRCH_CKDIV(m,val)                         (((val) << PDM_PDSFCRCH_CKDIV_SHIFT) & PDM_PDSFCRCH_CKDIV_MASK(m))
#define PDM_PDSFCRCH_SINCDEC_SHIFT                        (16)      /* Bits 16-23: Sincdec */
#define PDM_PDSFCRCH_SINCDEC_MASK(m)                      (0xff << PDM_PDSFCRCH_SINCDEC_SHIFT)
#define PDM_PDSFCRCH_SINCDEC(m,val)                       (((val) << PDM_PDSFCRCH_SINCDEC_SHIFT) & PDM_PDSFCRCH_SINCDEC_MASK(m))
#define PDM_PDSFCRCH_SINCRNG_SHIFT                        (24)      /* Bits 24-28: Sincrng */
#define PDM_PDSFCRCH_SINCRNG_MASK(m)                      (0x1f << PDM_PDSFCRCH_SINCRNG_SHIFT)
#define PDM_PDSFCRCH_SINCRNG(m,val)                       (((val) << PDM_PDSFCRCH_SINCRNG_SHIFT) & PDM_PDSFCRCH_SINCRNG_MASK(m))

/* PDM PDSRCH Register Bit Definitions (Parameterized) *********************/

#define PDM_PDSRCH_STATE(m)                               (1 << 0)  /* State */
#define PDM_PDSRCH_SDF(m)                                 (1 << 1)  /* Sdf */
#define PDM_PDSRCH_DRF(m)                                 (1 << 2)  /* Drf */
#define PDM_PDSRCH_SCDF(m)                                (1 << 16)  /* Scdf */
#define PDM_PDSRCH_OVLDF(m)                               (1 << 17)  /* Ovldf */
#define PDM_PDSRCH_OVUDF(m)                               (1 << 18)  /* Ovudf */
#define PDM_PDSRCH_BFOWDF(m)                              (1 << 27)  /* Bfowdf */

/* PDM PDSTPTRCH Register Bit Definitions (Parameterized) ******************/

#define PDM_PDSTPTRCH_STPTRG(m)                           (1 << 0)  /* Stptrg */

/* PDM PDSTRTRCH Register Bit Definitions (Parameterized) ******************/

#define PDM_PDSTRTRCH_STRTRG(m)                           (1 << 0)  /* Strtrg */

/* PDM PDCCHGTR Register Bit Definitions *****************************/

#define PDM_PDCCHGTR_CHGTRG_SHIFT               (0)      /* Bits 0-2: Chgtrg */
#define PDM_PDCCHGTR_CHGTRG_MASK                (0x7 << PDM_PDCCHGTR_CHGTRG_SHIFT)

/* PDM PDCDCR Register Bit Definitions *******************************/

#define PDM_PDCDCR_DATC_SHIFT                   (0)      /* Bits 0-2: Datc */
#define PDM_PDCDCR_DATC_MASK                    (0x7 << PDM_PDCDCR_DATC_SHIFT)

/* PDM PDCDRCR Register Bit Definitions ******************************/

#define PDM_PDCDRCR_DATRE_SHIFT                 (0)      /* Bits 0-2: Datre */
#define PDM_PDCDRCR_DATRE_MASK                  (0x7 << PDM_PDCDRCR_DATRE_SHIFT)

/* PDM PDCFCH00RCH0 Register Bit Definitions *************************/

#define PDM_PDCFCH00RCH0_CFH00_SHIFT            (0)      /* Bits 0-12: Cfh00 */
#define PDM_PDCFCH00RCH0_CFH00_MASK             (0x1fff << PDM_PDCFCH00RCH0_CFH00_SHIFT)

/* PDM PDCFCH00RCH1 Register Bit Definitions *************************/

#define PDM_PDCFCH00RCH1_CFH00_SHIFT            (0)      /* Bits 0-12: Cfh00 */
#define PDM_PDCFCH00RCH1_CFH00_MASK             (0x1fff << PDM_PDCFCH00RCH1_CFH00_SHIFT)

/* PDM PDCFCH00RCH2 Register Bit Definitions *************************/

#define PDM_PDCFCH00RCH2_CFH00_SHIFT            (0)      /* Bits 0-12: Cfh00 */
#define PDM_PDCFCH00RCH2_CFH00_MASK             (0x1fff << PDM_PDCFCH00RCH2_CFH00_SHIFT)

/* PDM PDCFCH01RCH0 Register Bit Definitions *************************/

#define PDM_PDCFCH01RCH0_CFH01_SHIFT            (0)      /* Bits 0-12: Cfh01 */
#define PDM_PDCFCH01RCH0_CFH01_MASK             (0x1fff << PDM_PDCFCH01RCH0_CFH01_SHIFT)

/* PDM PDCFCH01RCH1 Register Bit Definitions *************************/

#define PDM_PDCFCH01RCH1_CFH01_SHIFT            (0)      /* Bits 0-12: Cfh01 */
#define PDM_PDCFCH01RCH1_CFH01_MASK             (0x1fff << PDM_PDCFCH01RCH1_CFH01_SHIFT)

/* PDM PDCFCH01RCH2 Register Bit Definitions *************************/

#define PDM_PDCFCH01RCH2_CFH01_SHIFT            (0)      /* Bits 0-12: Cfh01 */
#define PDM_PDCFCH01RCH2_CFH01_MASK             (0x1fff << PDM_PDCFCH01RCH2_CFH01_SHIFT)

/* PDM PDCFCH02RCH0 Register Bit Definitions *************************/

#define PDM_PDCFCH02RCH0_CFH02_SHIFT            (0)      /* Bits 0-12: Cfh02 */
#define PDM_PDCFCH02RCH0_CFH02_MASK             (0x1fff << PDM_PDCFCH02RCH0_CFH02_SHIFT)

/* PDM PDCFCH02RCH1 Register Bit Definitions *************************/

#define PDM_PDCFCH02RCH1_CFH02_SHIFT            (0)      /* Bits 0-12: Cfh02 */
#define PDM_PDCFCH02RCH1_CFH02_MASK             (0x1fff << PDM_PDCFCH02RCH1_CFH02_SHIFT)

/* PDM PDCFCH02RCH2 Register Bit Definitions *************************/

#define PDM_PDCFCH02RCH2_CFH02_SHIFT            (0)      /* Bits 0-12: Cfh02 */
#define PDM_PDCFCH02RCH2_CFH02_MASK             (0x1fff << PDM_PDCFCH02RCH2_CFH02_SHIFT)

/* PDM PDCFCH03RCH0 Register Bit Definitions *************************/

#define PDM_PDCFCH03RCH0_CFH03_SHIFT            (0)      /* Bits 0-12: Cfh03 */
#define PDM_PDCFCH03RCH0_CFH03_MASK             (0x1fff << PDM_PDCFCH03RCH0_CFH03_SHIFT)

/* PDM PDCFCH03RCH1 Register Bit Definitions *************************/

#define PDM_PDCFCH03RCH1_CFH03_SHIFT            (0)      /* Bits 0-12: Cfh03 */
#define PDM_PDCFCH03RCH1_CFH03_MASK             (0x1fff << PDM_PDCFCH03RCH1_CFH03_SHIFT)

/* PDM PDCFCH03RCH2 Register Bit Definitions *************************/

#define PDM_PDCFCH03RCH2_CFH03_SHIFT            (0)      /* Bits 0-12: Cfh03 */
#define PDM_PDCFCH03RCH2_CFH03_MASK             (0x1fff << PDM_PDCFCH03RCH2_CFH03_SHIFT)

/* PDM PDCFCH04RCH0 Register Bit Definitions *************************/

#define PDM_PDCFCH04RCH0_CFH04_SHIFT            (0)      /* Bits 0-12: Cfh04 */
#define PDM_PDCFCH04RCH0_CFH04_MASK             (0x1fff << PDM_PDCFCH04RCH0_CFH04_SHIFT)

/* PDM PDCFCH04RCH1 Register Bit Definitions *************************/

#define PDM_PDCFCH04RCH1_CFH04_SHIFT            (0)      /* Bits 0-12: Cfh04 */
#define PDM_PDCFCH04RCH1_CFH04_MASK             (0x1fff << PDM_PDCFCH04RCH1_CFH04_SHIFT)

/* PDM PDCFCH04RCH2 Register Bit Definitions *************************/

#define PDM_PDCFCH04RCH2_CFH04_SHIFT            (0)      /* Bits 0-12: Cfh04 */
#define PDM_PDCFCH04RCH2_CFH04_MASK             (0x1fff << PDM_PDCFCH04RCH2_CFH04_SHIFT)

/* PDM PDCFCH05RCH0 Register Bit Definitions *************************/

#define PDM_PDCFCH05RCH0_CFH05_SHIFT            (0)      /* Bits 0-12: Cfh05 */
#define PDM_PDCFCH05RCH0_CFH05_MASK             (0x1fff << PDM_PDCFCH05RCH0_CFH05_SHIFT)

/* PDM PDCFCH05RCH1 Register Bit Definitions *************************/

#define PDM_PDCFCH05RCH1_CFH05_SHIFT            (0)      /* Bits 0-12: Cfh05 */
#define PDM_PDCFCH05RCH1_CFH05_MASK             (0x1fff << PDM_PDCFCH05RCH1_CFH05_SHIFT)

/* PDM PDCFCH05RCH2 Register Bit Definitions *************************/

#define PDM_PDCFCH05RCH2_CFH05_SHIFT            (0)      /* Bits 0-12: Cfh05 */
#define PDM_PDCFCH05RCH2_CFH05_MASK             (0x1fff << PDM_PDCFCH05RCH2_CFH05_SHIFT)

/* PDM PDCFCH06RCH0 Register Bit Definitions *************************/

#define PDM_PDCFCH06RCH0_CFH06_SHIFT            (0)      /* Bits 0-12: Cfh06 */
#define PDM_PDCFCH06RCH0_CFH06_MASK             (0x1fff << PDM_PDCFCH06RCH0_CFH06_SHIFT)

/* PDM PDCFCH06RCH1 Register Bit Definitions *************************/

#define PDM_PDCFCH06RCH1_CFH06_SHIFT            (0)      /* Bits 0-12: Cfh06 */
#define PDM_PDCFCH06RCH1_CFH06_MASK             (0x1fff << PDM_PDCFCH06RCH1_CFH06_SHIFT)

/* PDM PDCFCH06RCH2 Register Bit Definitions *************************/

#define PDM_PDCFCH06RCH2_CFH06_SHIFT            (0)      /* Bits 0-12: Cfh06 */
#define PDM_PDCFCH06RCH2_CFH06_MASK             (0x1fff << PDM_PDCFCH06RCH2_CFH06_SHIFT)

/* PDM PDCFCH07RCH0 Register Bit Definitions *************************/

#define PDM_PDCFCH07RCH0_CFH07_SHIFT            (0)      /* Bits 0-12: Cfh07 */
#define PDM_PDCFCH07RCH0_CFH07_MASK             (0x1fff << PDM_PDCFCH07RCH0_CFH07_SHIFT)

/* PDM PDCFCH07RCH1 Register Bit Definitions *************************/

#define PDM_PDCFCH07RCH1_CFH07_SHIFT            (0)      /* Bits 0-12: Cfh07 */
#define PDM_PDCFCH07RCH1_CFH07_MASK             (0x1fff << PDM_PDCFCH07RCH1_CFH07_SHIFT)

/* PDM PDCFCH07RCH2 Register Bit Definitions *************************/

#define PDM_PDCFCH07RCH2_CFH07_SHIFT            (0)      /* Bits 0-12: Cfh07 */
#define PDM_PDCFCH07RCH2_CFH07_MASK             (0x1fff << PDM_PDCFCH07RCH2_CFH07_SHIFT)

/* PDM PDCFCH08RCH0 Register Bit Definitions *************************/

#define PDM_PDCFCH08RCH0_CFH08_SHIFT            (0)      /* Bits 0-12: Cfh08 */
#define PDM_PDCFCH08RCH0_CFH08_MASK             (0x1fff << PDM_PDCFCH08RCH0_CFH08_SHIFT)

/* PDM PDCFCH08RCH1 Register Bit Definitions *************************/

#define PDM_PDCFCH08RCH1_CFH08_SHIFT            (0)      /* Bits 0-12: Cfh08 */
#define PDM_PDCFCH08RCH1_CFH08_MASK             (0x1fff << PDM_PDCFCH08RCH1_CFH08_SHIFT)

/* PDM PDCFCH08RCH2 Register Bit Definitions *************************/

#define PDM_PDCFCH08RCH2_CFH08_SHIFT            (0)      /* Bits 0-12: Cfh08 */
#define PDM_PDCFCH08RCH2_CFH08_MASK             (0x1fff << PDM_PDCFCH08RCH2_CFH08_SHIFT)

/* PDM PDCFCH09RCH0 Register Bit Definitions *************************/

#define PDM_PDCFCH09RCH0_CFH09_SHIFT            (0)      /* Bits 0-12: Cfh09 */
#define PDM_PDCFCH09RCH0_CFH09_MASK             (0x1fff << PDM_PDCFCH09RCH0_CFH09_SHIFT)

/* PDM PDCFCH09RCH1 Register Bit Definitions *************************/

#define PDM_PDCFCH09RCH1_CFH09_SHIFT            (0)      /* Bits 0-12: Cfh09 */
#define PDM_PDCFCH09RCH1_CFH09_MASK             (0x1fff << PDM_PDCFCH09RCH1_CFH09_SHIFT)

/* PDM PDCFCH09RCH2 Register Bit Definitions *************************/

#define PDM_PDCFCH09RCH2_CFH09_SHIFT            (0)      /* Bits 0-12: Cfh09 */
#define PDM_PDCFCH09RCH2_CFH09_MASK             (0x1fff << PDM_PDCFCH09RCH2_CFH09_SHIFT)

/* PDM PDCFCH10RCH0 Register Bit Definitions *************************/

#define PDM_PDCFCH10RCH0_CFH10_SHIFT            (0)      /* Bits 0-12: Cfh10 */
#define PDM_PDCFCH10RCH0_CFH10_MASK             (0x1fff << PDM_PDCFCH10RCH0_CFH10_SHIFT)

/* PDM PDCFCH10RCH1 Register Bit Definitions *************************/

#define PDM_PDCFCH10RCH1_CFH10_SHIFT            (0)      /* Bits 0-12: Cfh10 */
#define PDM_PDCFCH10RCH1_CFH10_MASK             (0x1fff << PDM_PDCFCH10RCH1_CFH10_SHIFT)

/* PDM PDCFCH10RCH2 Register Bit Definitions *************************/

#define PDM_PDCFCH10RCH2_CFH10_SHIFT            (0)      /* Bits 0-12: Cfh10 */
#define PDM_PDCFCH10RCH2_CFH10_MASK             (0x1fff << PDM_PDCFCH10RCH2_CFH10_SHIFT)

/* PDM PDCICR Register Bit Definitions *******************************/

#define PDM_PDCICR_ISDE_SHIFT                   (8)      /* Bits 8-10: Isde */
#define PDM_PDCICR_ISDE_MASK                    (0x7 << PDM_PDCICR_ISDE_SHIFT)

#define PDM_PDCICR_IDRE_SHIFT                   (16)      /* Bits 16-18: Idre */
#define PDM_PDCICR_IDRE_MASK                    (0x7 << PDM_PDCICR_IDRE_SHIFT)

#define PDM_PDCICR_IEDE_SHIFT                   (24)      /* Bits 24-26: Iede */
#define PDM_PDCICR_IEDE_MASK                    (0x7 << PDM_PDCICR_IEDE_SHIFT)

/* PDM PDCSCR Register Bit Definitions *******************************/

#define PDM_PDCSCR_SDFC_SHIFT                   (8)      /* Bits 8-10: Sdfc */
#define PDM_PDCSCR_SDFC_MASK                    (0x7 << PDM_PDCSCR_SDFC_SHIFT)

/* PDM PDCSDCR Register Bit Definitions ******************************/

#define PDM_PDCSDCR_SDE_SHIFT                   (0)      /* Bits 0-2: Sde */
#define PDM_PDCSDCR_SDE_MASK                    (0x7 << PDM_PDCSDCR_SDE_SHIFT)

/* PDM PDCSR Register Bit Definitions ********************************/

#define PDM_PDCSR_STATE_SHIFT                   (0)      /* Bits 0-2: State */
#define PDM_PDCSR_STATE_MASK                    (0x7 << PDM_PDCSR_STATE_SHIFT)

#define PDM_PDCSR_SDF_SHIFT                     (8)      /* Bits 8-10: Sdf */
#define PDM_PDCSR_SDF_MASK                      (0x7 << PDM_PDCSR_SDF_SHIFT)

#define PDM_PDCSR_DRF_SHIFT                     (16)      /* Bits 16-18: Drf */
#define PDM_PDCSR_DRF_MASK                      (0x7 << PDM_PDCSR_DRF_SHIFT)

#define PDM_PDCSR_EDF_SHIFT                     (24)      /* Bits 24-26: Edf */
#define PDM_PDCSR_EDF_MASK                      (0x7 << PDM_PDCSR_EDF_SHIFT)

/* PDM PDCSTPTR Register Bit Definitions *****************************/

#define PDM_PDCSTPTR_STPTRG_SHIFT               (0)      /* Bits 0-2: Stptrg */
#define PDM_PDCSTPTR_STPTRG_MASK                (0x7 << PDM_PDCSTPTR_STPTRG_SHIFT)

/* PDM PDCSTRTR Register Bit Definitions *****************************/

#define PDM_PDCSTRTR_STRTRG_SHIFT               (0)      /* Bits 0-2: Strtrg */
#define PDM_PDCSTRTR_STRTRG_MASK                (0x7 << PDM_PDCSTRTR_STRTRG_SHIFT)

/* PDM PDHFCH0RCH0 Register Bit Definitions **************************/

#define PDM_PDHFCH0RCH0_HFH0_SHIFT              (0)      /* Bits 0-15: Hfh0 */
#define PDM_PDHFCH0RCH0_HFH0_MASK               (0xffff << PDM_PDHFCH0RCH0_HFH0_SHIFT)

/* PDM PDHFCH0RCH1 Register Bit Definitions **************************/

#define PDM_PDHFCH0RCH1_HFH0_SHIFT              (0)      /* Bits 0-15: Hfh0 */
#define PDM_PDHFCH0RCH1_HFH0_MASK               (0xffff << PDM_PDHFCH0RCH1_HFH0_SHIFT)

/* PDM PDHFCH0RCH2 Register Bit Definitions **************************/

#define PDM_PDHFCH0RCH2_HFH0_SHIFT              (0)      /* Bits 0-15: Hfh0 */
#define PDM_PDHFCH0RCH2_HFH0_MASK               (0xffff << PDM_PDHFCH0RCH2_HFH0_SHIFT)

/* PDM PDHFCH1RCH0 Register Bit Definitions **************************/

#define PDM_PDHFCH1RCH0_HFH1_SHIFT              (0)      /* Bits 0-15: Hfh1 */
#define PDM_PDHFCH1RCH0_HFH1_MASK               (0xffff << PDM_PDHFCH1RCH0_HFH1_SHIFT)

/* PDM PDHFCH1RCH1 Register Bit Definitions **************************/

#define PDM_PDHFCH1RCH1_HFH1_SHIFT              (0)      /* Bits 0-15: Hfh1 */
#define PDM_PDHFCH1RCH1_HFH1_MASK               (0xffff << PDM_PDHFCH1RCH1_HFH1_SHIFT)

/* PDM PDHFCH1RCH2 Register Bit Definitions **************************/

#define PDM_PDHFCH1RCH2_HFH1_SHIFT              (0)      /* Bits 0-15: Hfh1 */
#define PDM_PDHFCH1RCH2_HFH1_MASK               (0xffff << PDM_PDHFCH1RCH2_HFH1_SHIFT)

/* PDM PDHFCK1RCH0 Register Bit Definitions **************************/

#define PDM_PDHFCK1RCH0_HFKm_SHIFT              (0)      /* Bits 0-15: Hfkm */
#define PDM_PDHFCK1RCH0_HFKm_MASK               (0xffff << PDM_PDHFCK1RCH0_HFKm_SHIFT)

/* PDM PDHFCK1RCH1 Register Bit Definitions **************************/

#define PDM_PDHFCK1RCH1_HFKm_SHIFT              (0)      /* Bits 0-15: Hfkm */
#define PDM_PDHFCK1RCH1_HFKm_MASK               (0xffff << PDM_PDHFCK1RCH1_HFKm_SHIFT)

/* PDM PDHFCK1RCH2 Register Bit Definitions **************************/

#define PDM_PDHFCK1RCH2_HFKm_SHIFT              (0)      /* Bits 0-15: Hfkm */
#define PDM_PDHFCK1RCH2_HFKm_MASK               (0xffff << PDM_PDHFCK1RCH2_HFKm_SHIFT)

/* PDM PDHFCS0RCH0 Register Bit Definitions **************************/

#define PDM_PDHFCS0RCH0_HFSm_SHIFT              (0)      /* Bits 0-15: Hfsm */
#define PDM_PDHFCS0RCH0_HFSm_MASK               (0xffff << PDM_PDHFCS0RCH0_HFSm_SHIFT)

/* PDM PDHFCS0RCH1 Register Bit Definitions **************************/

#define PDM_PDHFCS0RCH1_HFSm_SHIFT              (0)      /* Bits 0-15: Hfsm */
#define PDM_PDHFCS0RCH1_HFSm_MASK               (0xffff << PDM_PDHFCS0RCH1_HFSm_SHIFT)

/* PDM PDHFCS0RCH2 Register Bit Definitions **************************/

#define PDM_PDHFCS0RCH2_HFSm_SHIFT              (0)      /* Bits 0-15: Hfsm */
#define PDM_PDHFCS0RCH2_HFSm_MASK               (0xffff << PDM_PDHFCS0RCH2_HFSm_SHIFT)

/* PDM PDLFCH010RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH010RCH0_LFH010_SHIFT          (0)      /* Bits 0-12: Lfh010 */
#define PDM_PDLFCH010RCH0_LFH010_MASK           (0x1fff << PDM_PDLFCH010RCH0_LFH010_SHIFT)

/* PDM PDLFCH010RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH010RCH1_LFH010_SHIFT          (0)      /* Bits 0-12: Lfh010 */
#define PDM_PDLFCH010RCH1_LFH010_MASK           (0x1fff << PDM_PDLFCH010RCH1_LFH010_SHIFT)

/* PDM PDLFCH010RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH010RCH2_LFH010_SHIFT          (0)      /* Bits 0-12: Lfh010 */
#define PDM_PDLFCH010RCH2_LFH010_MASK           (0x1fff << PDM_PDLFCH010RCH2_LFH010_SHIFT)

/* PDM PDLFCH100RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH100RCH0_LFH100_SHIFT          (0)      /* Bits 0-12: Lfh100 */
#define PDM_PDLFCH100RCH0_LFH100_MASK           (0x1fff << PDM_PDLFCH100RCH0_LFH100_SHIFT)

/* PDM PDLFCH100RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH100RCH1_LFH100_SHIFT          (0)      /* Bits 0-12: Lfh100 */
#define PDM_PDLFCH100RCH1_LFH100_MASK           (0x1fff << PDM_PDLFCH100RCH1_LFH100_SHIFT)

/* PDM PDLFCH100RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH100RCH2_LFH100_SHIFT          (0)      /* Bits 0-12: Lfh100 */
#define PDM_PDLFCH100RCH2_LFH100_MASK           (0x1fff << PDM_PDLFCH100RCH2_LFH100_SHIFT)

/* PDM PDLFCH101RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH101RCH0_LFH101_SHIFT          (0)      /* Bits 0-12: Lfh101 */
#define PDM_PDLFCH101RCH0_LFH101_MASK           (0x1fff << PDM_PDLFCH101RCH0_LFH101_SHIFT)

/* PDM PDLFCH101RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH101RCH1_LFH101_SHIFT          (0)      /* Bits 0-12: Lfh101 */
#define PDM_PDLFCH101RCH1_LFH101_MASK           (0x1fff << PDM_PDLFCH101RCH1_LFH101_SHIFT)

/* PDM PDLFCH101RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH101RCH2_LFH101_SHIFT          (0)      /* Bits 0-12: Lfh101 */
#define PDM_PDLFCH101RCH2_LFH101_MASK           (0x1fff << PDM_PDLFCH101RCH2_LFH101_SHIFT)

/* PDM PDLFCH102RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH102RCH0_LFH102_SHIFT          (0)      /* Bits 0-12: Lfh102 */
#define PDM_PDLFCH102RCH0_LFH102_MASK           (0x1fff << PDM_PDLFCH102RCH0_LFH102_SHIFT)

/* PDM PDLFCH102RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH102RCH1_LFH102_SHIFT          (0)      /* Bits 0-12: Lfh102 */
#define PDM_PDLFCH102RCH1_LFH102_MASK           (0x1fff << PDM_PDLFCH102RCH1_LFH102_SHIFT)

/* PDM PDLFCH102RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH102RCH2_LFH102_SHIFT          (0)      /* Bits 0-12: Lfh102 */
#define PDM_PDLFCH102RCH2_LFH102_MASK           (0x1fff << PDM_PDLFCH102RCH2_LFH102_SHIFT)

/* PDM PDLFCH103RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH103RCH0_LFH103_SHIFT          (0)      /* Bits 0-12: Lfh103 */
#define PDM_PDLFCH103RCH0_LFH103_MASK           (0x1fff << PDM_PDLFCH103RCH0_LFH103_SHIFT)

/* PDM PDLFCH103RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH103RCH1_LFH103_SHIFT          (0)      /* Bits 0-12: Lfh103 */
#define PDM_PDLFCH103RCH1_LFH103_MASK           (0x1fff << PDM_PDLFCH103RCH1_LFH103_SHIFT)

/* PDM PDLFCH103RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH103RCH2_LFH103_SHIFT          (0)      /* Bits 0-12: Lfh103 */
#define PDM_PDLFCH103RCH2_LFH103_MASK           (0x1fff << PDM_PDLFCH103RCH2_LFH103_SHIFT)

/* PDM PDLFCH104RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH104RCH0_LFH104_SHIFT          (0)      /* Bits 0-12: Lfh104 */
#define PDM_PDLFCH104RCH0_LFH104_MASK           (0x1fff << PDM_PDLFCH104RCH0_LFH104_SHIFT)

/* PDM PDLFCH104RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH104RCH1_LFH104_SHIFT          (0)      /* Bits 0-12: Lfh104 */
#define PDM_PDLFCH104RCH1_LFH104_MASK           (0x1fff << PDM_PDLFCH104RCH1_LFH104_SHIFT)

/* PDM PDLFCH104RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH104RCH2_LFH104_SHIFT          (0)      /* Bits 0-12: Lfh104 */
#define PDM_PDLFCH104RCH2_LFH104_MASK           (0x1fff << PDM_PDLFCH104RCH2_LFH104_SHIFT)

/* PDM PDLFCH105RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH105RCH0_LFH105_SHIFT          (0)      /* Bits 0-12: Lfh105 */
#define PDM_PDLFCH105RCH0_LFH105_MASK           (0x1fff << PDM_PDLFCH105RCH0_LFH105_SHIFT)

/* PDM PDLFCH105RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH105RCH1_LFH105_SHIFT          (0)      /* Bits 0-12: Lfh105 */
#define PDM_PDLFCH105RCH1_LFH105_MASK           (0x1fff << PDM_PDLFCH105RCH1_LFH105_SHIFT)

/* PDM PDLFCH105RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH105RCH2_LFH105_SHIFT          (0)      /* Bits 0-12: Lfh105 */
#define PDM_PDLFCH105RCH2_LFH105_MASK           (0x1fff << PDM_PDLFCH105RCH2_LFH105_SHIFT)

/* PDM PDLFCH106RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH106RCH0_LFH106_SHIFT          (0)      /* Bits 0-12: Lfh106 */
#define PDM_PDLFCH106RCH0_LFH106_MASK           (0x1fff << PDM_PDLFCH106RCH0_LFH106_SHIFT)

/* PDM PDLFCH106RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH106RCH1_LFH106_SHIFT          (0)      /* Bits 0-12: Lfh106 */
#define PDM_PDLFCH106RCH1_LFH106_MASK           (0x1fff << PDM_PDLFCH106RCH1_LFH106_SHIFT)

/* PDM PDLFCH106RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH106RCH2_LFH106_SHIFT          (0)      /* Bits 0-12: Lfh106 */
#define PDM_PDLFCH106RCH2_LFH106_MASK           (0x1fff << PDM_PDLFCH106RCH2_LFH106_SHIFT)

/* PDM PDLFCH107RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH107RCH0_LFH107_SHIFT          (0)      /* Bits 0-12: Lfh107 */
#define PDM_PDLFCH107RCH0_LFH107_MASK           (0x1fff << PDM_PDLFCH107RCH0_LFH107_SHIFT)

/* PDM PDLFCH107RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH107RCH1_LFH107_SHIFT          (0)      /* Bits 0-12: Lfh107 */
#define PDM_PDLFCH107RCH1_LFH107_MASK           (0x1fff << PDM_PDLFCH107RCH1_LFH107_SHIFT)

/* PDM PDLFCH107RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH107RCH2_LFH107_SHIFT          (0)      /* Bits 0-12: Lfh107 */
#define PDM_PDLFCH107RCH2_LFH107_MASK           (0x1fff << PDM_PDLFCH107RCH2_LFH107_SHIFT)

/* PDM PDLFCH108RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH108RCH0_LFH108_SHIFT          (0)      /* Bits 0-12: Lfh108 */
#define PDM_PDLFCH108RCH0_LFH108_MASK           (0x1fff << PDM_PDLFCH108RCH0_LFH108_SHIFT)

/* PDM PDLFCH108RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH108RCH1_LFH108_SHIFT          (0)      /* Bits 0-12: Lfh108 */
#define PDM_PDLFCH108RCH1_LFH108_MASK           (0x1fff << PDM_PDLFCH108RCH1_LFH108_SHIFT)

/* PDM PDLFCH108RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH108RCH2_LFH108_SHIFT          (0)      /* Bits 0-12: Lfh108 */
#define PDM_PDLFCH108RCH2_LFH108_MASK           (0x1fff << PDM_PDLFCH108RCH2_LFH108_SHIFT)

/* PDM PDLFCH109RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH109RCH0_LFH109_SHIFT          (0)      /* Bits 0-12: Lfh109 */
#define PDM_PDLFCH109RCH0_LFH109_MASK           (0x1fff << PDM_PDLFCH109RCH0_LFH109_SHIFT)

/* PDM PDLFCH109RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH109RCH1_LFH109_SHIFT          (0)      /* Bits 0-12: Lfh109 */
#define PDM_PDLFCH109RCH1_LFH109_MASK           (0x1fff << PDM_PDLFCH109RCH1_LFH109_SHIFT)

/* PDM PDLFCH109RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH109RCH2_LFH109_SHIFT          (0)      /* Bits 0-12: Lfh109 */
#define PDM_PDLFCH109RCH2_LFH109_MASK           (0x1fff << PDM_PDLFCH109RCH2_LFH109_SHIFT)

/* PDM PDLFCH110RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH110RCH0_LFH110_SHIFT          (0)      /* Bits 0-12: Lfh110 */
#define PDM_PDLFCH110RCH0_LFH110_MASK           (0x1fff << PDM_PDLFCH110RCH0_LFH110_SHIFT)

/* PDM PDLFCH110RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH110RCH1_LFH110_SHIFT          (0)      /* Bits 0-12: Lfh110 */
#define PDM_PDLFCH110RCH1_LFH110_MASK           (0x1fff << PDM_PDLFCH110RCH1_LFH110_SHIFT)

/* PDM PDLFCH110RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH110RCH2_LFH110_SHIFT          (0)      /* Bits 0-12: Lfh110 */
#define PDM_PDLFCH110RCH2_LFH110_MASK           (0x1fff << PDM_PDLFCH110RCH2_LFH110_SHIFT)

/* PDM PDLFCH111RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH111RCH0_LFH111_SHIFT          (0)      /* Bits 0-12: Lfh111 */
#define PDM_PDLFCH111RCH0_LFH111_MASK           (0x1fff << PDM_PDLFCH111RCH0_LFH111_SHIFT)

/* PDM PDLFCH111RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH111RCH1_LFH111_SHIFT          (0)      /* Bits 0-12: Lfh111 */
#define PDM_PDLFCH111RCH1_LFH111_MASK           (0x1fff << PDM_PDLFCH111RCH1_LFH111_SHIFT)

/* PDM PDLFCH111RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH111RCH2_LFH111_SHIFT          (0)      /* Bits 0-12: Lfh111 */
#define PDM_PDLFCH111RCH2_LFH111_MASK           (0x1fff << PDM_PDLFCH111RCH2_LFH111_SHIFT)

/* PDM PDLFCH112RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH112RCH0_LFH112_SHIFT          (0)      /* Bits 0-12: Lfh112 */
#define PDM_PDLFCH112RCH0_LFH112_MASK           (0x1fff << PDM_PDLFCH112RCH0_LFH112_SHIFT)

/* PDM PDLFCH112RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH112RCH1_LFH112_SHIFT          (0)      /* Bits 0-12: Lfh112 */
#define PDM_PDLFCH112RCH1_LFH112_MASK           (0x1fff << PDM_PDLFCH112RCH1_LFH112_SHIFT)

/* PDM PDLFCH112RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH112RCH2_LFH112_SHIFT          (0)      /* Bits 0-12: Lfh112 */
#define PDM_PDLFCH112RCH2_LFH112_MASK           (0x1fff << PDM_PDLFCH112RCH2_LFH112_SHIFT)

/* PDM PDLFCH113RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH113RCH0_LFH113_SHIFT          (0)      /* Bits 0-12: Lfh113 */
#define PDM_PDLFCH113RCH0_LFH113_MASK           (0x1fff << PDM_PDLFCH113RCH0_LFH113_SHIFT)

/* PDM PDLFCH113RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH113RCH1_LFH113_SHIFT          (0)      /* Bits 0-12: Lfh113 */
#define PDM_PDLFCH113RCH1_LFH113_MASK           (0x1fff << PDM_PDLFCH113RCH1_LFH113_SHIFT)

/* PDM PDLFCH113RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH113RCH2_LFH113_SHIFT          (0)      /* Bits 0-12: Lfh113 */
#define PDM_PDLFCH113RCH2_LFH113_MASK           (0x1fff << PDM_PDLFCH113RCH2_LFH113_SHIFT)

/* PDM PDLFCH114RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH114RCH0_LFH114_SHIFT          (0)      /* Bits 0-12: Lfh114 */
#define PDM_PDLFCH114RCH0_LFH114_MASK           (0x1fff << PDM_PDLFCH114RCH0_LFH114_SHIFT)

/* PDM PDLFCH114RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH114RCH1_LFH114_SHIFT          (0)      /* Bits 0-12: Lfh114 */
#define PDM_PDLFCH114RCH1_LFH114_MASK           (0x1fff << PDM_PDLFCH114RCH1_LFH114_SHIFT)

/* PDM PDLFCH114RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH114RCH2_LFH114_SHIFT          (0)      /* Bits 0-12: Lfh114 */
#define PDM_PDLFCH114RCH2_LFH114_MASK           (0x1fff << PDM_PDLFCH114RCH2_LFH114_SHIFT)

/* PDM PDLFCH115RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH115RCH0_LFH115_SHIFT          (0)      /* Bits 0-12: Lfh115 */
#define PDM_PDLFCH115RCH0_LFH115_MASK           (0x1fff << PDM_PDLFCH115RCH0_LFH115_SHIFT)

/* PDM PDLFCH115RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH115RCH1_LFH115_SHIFT          (0)      /* Bits 0-12: Lfh115 */
#define PDM_PDLFCH115RCH1_LFH115_MASK           (0x1fff << PDM_PDLFCH115RCH1_LFH115_SHIFT)

/* PDM PDLFCH115RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH115RCH2_LFH115_SHIFT          (0)      /* Bits 0-12: Lfh115 */
#define PDM_PDLFCH115RCH2_LFH115_MASK           (0x1fff << PDM_PDLFCH115RCH2_LFH115_SHIFT)

/* PDM PDLFCH116RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH116RCH0_LFH116_SHIFT          (0)      /* Bits 0-12: Lfh116 */
#define PDM_PDLFCH116RCH0_LFH116_MASK           (0x1fff << PDM_PDLFCH116RCH0_LFH116_SHIFT)

/* PDM PDLFCH116RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH116RCH1_LFH116_SHIFT          (0)      /* Bits 0-12: Lfh116 */
#define PDM_PDLFCH116RCH1_LFH116_MASK           (0x1fff << PDM_PDLFCH116RCH1_LFH116_SHIFT)

/* PDM PDLFCH116RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH116RCH2_LFH116_SHIFT          (0)      /* Bits 0-12: Lfh116 */
#define PDM_PDLFCH116RCH2_LFH116_MASK           (0x1fff << PDM_PDLFCH116RCH2_LFH116_SHIFT)

/* PDM PDLFCH117RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH117RCH0_LFH117_SHIFT          (0)      /* Bits 0-12: Lfh117 */
#define PDM_PDLFCH117RCH0_LFH117_MASK           (0x1fff << PDM_PDLFCH117RCH0_LFH117_SHIFT)

/* PDM PDLFCH117RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH117RCH1_LFH117_SHIFT          (0)      /* Bits 0-12: Lfh117 */
#define PDM_PDLFCH117RCH1_LFH117_MASK           (0x1fff << PDM_PDLFCH117RCH1_LFH117_SHIFT)

/* PDM PDLFCH117RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH117RCH2_LFH117_SHIFT          (0)      /* Bits 0-12: Lfh117 */
#define PDM_PDLFCH117RCH2_LFH117_MASK           (0x1fff << PDM_PDLFCH117RCH2_LFH117_SHIFT)

/* PDM PDLFCH118RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH118RCH0_LFH118_SHIFT          (0)      /* Bits 0-12: Lfh118 */
#define PDM_PDLFCH118RCH0_LFH118_MASK           (0x1fff << PDM_PDLFCH118RCH0_LFH118_SHIFT)

/* PDM PDLFCH118RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH118RCH1_LFH118_SHIFT          (0)      /* Bits 0-12: Lfh118 */
#define PDM_PDLFCH118RCH1_LFH118_MASK           (0x1fff << PDM_PDLFCH118RCH1_LFH118_SHIFT)

/* PDM PDLFCH118RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH118RCH2_LFH118_SHIFT          (0)      /* Bits 0-12: Lfh118 */
#define PDM_PDLFCH118RCH2_LFH118_MASK           (0x1fff << PDM_PDLFCH118RCH2_LFH118_SHIFT)

/* PDM PDLFCH119RCH0 Register Bit Definitions ************************/

#define PDM_PDLFCH119RCH0_LFH119_SHIFT          (0)      /* Bits 0-12: Lfh119 */
#define PDM_PDLFCH119RCH0_LFH119_MASK           (0x1fff << PDM_PDLFCH119RCH0_LFH119_SHIFT)

/* PDM PDLFCH119RCH1 Register Bit Definitions ************************/

#define PDM_PDLFCH119RCH1_LFH119_SHIFT          (0)      /* Bits 0-12: Lfh119 */
#define PDM_PDLFCH119RCH1_LFH119_MASK           (0x1fff << PDM_PDLFCH119RCH1_LFH119_SHIFT)

/* PDM PDLFCH119RCH2 Register Bit Definitions ************************/

#define PDM_PDLFCH119RCH2_LFH119_SHIFT          (0)      /* Bits 0-12: Lfh119 */
#define PDM_PDLFCH119RCH2_LFH119_MASK           (0x1fff << PDM_PDLFCH119RCH2_LFH119_SHIFT)

/* PDM PDVR Register Bit Definitions *********************************/

#define PDM_PDVR_VER_SHIFT                      (0)      /* Bits 0-11: Ver */
#define PDM_PDVR_VER_MASK                       (0xfff << PDM_PDVR_VER_SHIFT)

/* PDM Channel definitions */
#define RZV_PDM_CHANNEL_0          0
#define RZV_PDM_CHANNEL_1          1

/* Maximum number of PDM channels */
#define RZV_PDM_MAX_CHANNELS       2

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_PDM_H */

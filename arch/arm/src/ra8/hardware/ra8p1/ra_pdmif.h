/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_pdmif.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PDMIF_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PDMIF_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* PDMIF Base Address */
#ifndef R_PDMIF_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_PDMIF_BASE           0x40256000
#else
#define R_PDMIF_BASE           0x50256000
#endif
#endif

/* PDMIF Register Offsets */

#define R_PDMIF_PDCSTRTR_OFFSET                   0x00000000  /* Channel Software Start Trigger Register */
#define R_PDMIF_PDCSTPTR_OFFSET                   0x00000004  /* Channel Software Stop Trigger Register */
#define R_PDMIF_PDCCHGTR_OFFSET                   0x00000008  /* Channel Software Change Trigger Register */
#define R_PDMIF_PDCICR_OFFSET                     0x0000000c  /* Channel Interrupt Control Register */
#define R_PDMIF_PDCSR_OFFSET                      0x00000010  /* Channel Status Register */
#define R_PDMIF_PDCSCR_OFFSET                     0x00000014  /* Channel Status Clear Register */
#define R_PDMIF_PDCSDCR_OFFSET                    0x00000020  /* Channel Sound Detection Control Register */
#define R_PDMIF_PDCDRCR_OFFSET                    0x00000024  /* Channel Data Read Control Register */
#define R_PDMIF_PDCDCR_OFFSET                     0x00000028  /* Channel Data Clear Register */
#define R_PDMIF_PDVR_OFFSET                       0x00000080  /* Version Register */
/* PDSTRTRCH%s Registers (0-2) */
#define R_PDMIF_PDSTRTRCH_OFFSET(m)               (0x00000100 + ((m) * 0x00000100))  /* Software Start Trigger Register Channel %s */
/* PDSTPTRCH%s Registers (0-2) */
#define R_PDMIF_PDSTPTRCH_OFFSET(m)               (0x00000104 + ((m) * 0x00000100))  /* Software Stop Trigger Register Channel %s */
/* PDCHGTRCH%s Registers (0-2) */
#define R_PDMIF_PDCHGTRCH_OFFSET(m)               (0x00000108 + ((m) * 0x00000100))  /* Software Change Trigger Register Channel %s */
/* PDICRCH%s Registers (0-2) */
#define R_PDMIF_PDICRCH_OFFSET(m)                 (0x0000010c + ((m) * 0x00000100))  /* Interrupt Control Register Channel %s */
/* PDSDCRCH%s Registers (0-2) */
#define R_PDMIF_PDSDCRCH_OFFSET(m)                (0x00000110 + ((m) * 0x00000100))  /* Status Detection Control Register Channel %s */
/* PDSRCH%s Registers (0-2) */
#define R_PDMIF_PDSRCH_OFFSET(m)                  (0x00000114 + ((m) * 0x00000100))  /* Status Register Channel %s */
/* PDSCRCH%s Registers (0-2) */
#define R_PDMIF_PDSCRCH_OFFSET(m)                 (0x00000118 + ((m) * 0x00000100))  /* Status Clear Register Channel %s */
/* PDMDSRCH%s Registers (0-2) */
#define R_PDMIF_PDMDSRCH_OFFSET(m)                (0x00000120 + ((m) * 0x00000100))  /* Mode Setting Register Channel %s */
/* PDSFCRCH%s Registers (0-2) */
#define R_PDMIF_PDSFCRCH_OFFSET(m)                (0x00000124 + ((m) * 0x00000100))  /* Sinc Filter Control Register Channel %s */
/* PDHFCS0RCH%s Registers (0-2) */
#define R_PDMIF_PDHFCS0RCH_OFFSET(m)              (0x00000128 + ((m) * 0x00000100))  /* High-pass Filter Coefficient s(0) Register Channel %s */
/* PDHFCK1RCH%s Registers (0-2) */
#define R_PDMIF_PDHFCK1RCH_OFFSET(m)              (0x0000012c + ((m) * 0x00000100))  /* High-pass Filter Coefficient k(1) Register Channel %s */
/* PDHFCH0RCH%s Registers (0-2) */
#define R_PDMIF_PDHFCH0RCH_OFFSET(m)              (0x00000130 + ((m) * 0x00000100))  /* High-pass Filter Coefficient h(0) Register Channel %s */
/* PDHFCH1RCH%s Registers (0-2) */
#define R_PDMIF_PDHFCH1RCH_OFFSET(m)              (0x00000134 + ((m) * 0x00000100))  /* High-pass Filter Coefficient h(1) Register Channel %s */
/* PDCFCH00RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH00RCH_OFFSET(m)             (0x00000138 + ((m) * 0x00000100))  /* Compensation Filter Coefficient h(0) Register Channel %s */
/* PDCFCH01RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH01RCH_OFFSET(m)             (0x0000013c + ((m) * 0x00000100))  /* Compensation Filter Coefficient h(1) Register Channel %s */
/* PDCFCH02RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH02RCH_OFFSET(m)             (0x00000140 + ((m) * 0x00000100))  /* Compensation Filter Coefficient h(2) Register Channel %s */
/* PDCFCH03RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH03RCH_OFFSET(m)             (0x00000144 + ((m) * 0x00000100))  /* Compensation Filter Coefficient h(3) Register Channel %s */
/* PDCFCH04RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH04RCH_OFFSET(m)             (0x00000148 + ((m) * 0x00000100))  /* Compensation Filter Coefficient h(4) Register Channel %s */
/* PDCFCH05RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH05RCH_OFFSET(m)             (0x0000014c + ((m) * 0x00000100))  /* Compensation Filter Coefficient h(5) Register Channel %s */
#define R_PDMIF_PDCFCH06RCHN_OFFSET               0x00000150  /* Compensation Filter Coefficient h(6) Register Channel n */
/* PDCFCH07RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH07RCH_OFFSET(m)             (0x00000154 + ((m) * 0x00000100))  /* Compensation Filter Coefficient h(7) Register Channel %s */
/* PDCFCH08RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH08RCH_OFFSET(m)             (0x00000158 + ((m) * 0x00000100))  /* Compensation Filter Coefficient h(8) Register Channel %s */
/* PDCFCH09RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH09RCH_OFFSET(m)             (0x0000015c + ((m) * 0x00000100))  /* Compensation Filter Coefficient h(9) Register Channel %s */
/* PDCFCH10RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH10RCH_OFFSET(m)             (0x00000160 + ((m) * 0x00000100))  /* Compensation Filter Coefficient h(10) Register Channel %s */
/* PDLFCH010RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH010RCH_OFFSET(m)            (0x00000164 + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h0(10) Register Channel %s */
/* PDLFCH100RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH100RCH_OFFSET(m)            (0x00000168 + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(0) Register Channel %s */
/* PDLFCH101RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH101RCH_OFFSET(m)            (0x0000016c + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(1) Register Channel %s */
/* PDLFCH102RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH102RCH_OFFSET(m)            (0x00000170 + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1 (2) Register Channel %s */
/* PDLFCH103RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH103RCH_OFFSET(m)            (0x00000174 + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(3) Register Channel %s */
/* PDLFCH104RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH104RCH_OFFSET(m)            (0x00000178 + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(4) Register Channel %s */
/* PDLFCH105RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH105RCH_OFFSET(m)            (0x0000017c + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(5) Register Channel %s */
/* PDLFCH106RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH106RCH_OFFSET(m)            (0x00000180 + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(6) Register Channel %s */
/* PDLFCH107RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH107RCH_OFFSET(m)            (0x00000184 + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(7) Register Channel %s */
/* PDLFCH108RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH108RCH_OFFSET(m)            (0x00000188 + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(8) Register Channel %s */
/* PDLFCH109RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH109RCH_OFFSET(m)            (0x0000018c + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(9) Register Channel %s */
/* PDLFCH110RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH110RCH_OFFSET(m)            (0x00000190 + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(10) Register Channel %s */
/* PDLFCH111RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH111RCH_OFFSET(m)            (0x00000194 + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(11) Register Channel %s */
/* PDLFCH112RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH112RCH_OFFSET(m)            (0x00000198 + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(12) Register Channel %s */
/* PDLFCH113RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH113RCH_OFFSET(m)            (0x0000019c + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(13) Register Channel %s */
/* PDLFCH114RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH114RCH_OFFSET(m)            (0x000001a0 + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(14) Register Channel %s */
/* PDLFCH115RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH115RCH_OFFSET(m)            (0x000001a4 + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(15) Register Channel %s */
/* PDLFCH116RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH116RCH_OFFSET(m)            (0x000001a8 + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(16) Register Channel %s */
/* PDLFCH117RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH117RCH_OFFSET(m)            (0x000001ac + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(17) Register Channel %s */
/* PDLFCH118RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH118RCH_OFFSET(m)            (0x000001b0 + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(18) Register Channel %s */
/* PDLFCH119RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH119RCH_OFFSET(m)            (0x000001b4 + ((m) * 0x00000100))  /* Low-pass Filter Coefficient h1(19) Register Channel %s */
/* PDSDLTRCH%s Registers (0-2) */
#define R_PDMIF_PDSDLTRCH_OFFSET(m)               (0x000001b8 + ((m) * 0x00000100))  /* Sound Detection Lower Threshold Register Channel %s */
/* PDSDUTRCH%s Registers (0-2) */
#define R_PDMIF_PDSDUTRCH_OFFSET(m)               (0x000001bc + ((m) * 0x00000100))  /* Sound Detection Upper Threshold Register Channel %s */
/* PDDBCRCH%s Registers (0-2) */
#define R_PDMIF_PDDBCRCH_OFFSET(m)                (0x000001c0 + ((m) * 0x00000100))  /* Data Buffer Control Register Channel %s */
/* PDSCTSRCH%s Registers (0-2) */
#define R_PDMIF_PDSCTSRCH_OFFSET(m)               (0x000001c4 + ((m) * 0x00000100))  /* Short Circuit Threshold Setting Register Channel %s */
/* PDOVLTRCH%s Registers (0-2) */
#define R_PDMIF_PDOVLTRCH_OFFSET(m)               (0x000001c8 + ((m) * 0x00000100))  /* Overvoltage Lower Threshold Register Channel %s */
/* PDOVUTRCH%s Registers (0-2) */
#define R_PDMIF_PDOVUTRCH_OFFSET(m)               (0x000001cc + ((m) * 0x00000100))  /* Overvoltage Upper Threshold Register Channel %s */
/* PDDRCRCH%s Registers (0-2) */
#define R_PDMIF_PDDRCRCH_OFFSET(m)                (0x000001e0 + ((m) * 0x00000100))  /* Data Read Control Register Channel %s */
/* PDDCRCH%s Registers (0-2) */
#define R_PDMIF_PDDCRCH_OFFSET(m)                 (0x000001e4 + ((m) * 0x00000100))  /* Data Clear Register Channel %s */
/* PDDRRCH%s Registers (0-2) */
#define R_PDMIF_PDDRRCH_OFFSET(m)                 (0x000001e8 + ((m) * 0x00000100))  /* Data Read Register Channel %s */
/* PDDSRCH%s Registers (0-2) */
#define R_PDMIF_PDDSRCH_OFFSET(m)                 (0x000001ec + ((m) * 0x00000100))  /* Data Status Register Channel %s */

/* PDMIF Register Addresses */

#define R_PDMIF_PDCSTRTR                          (R_PDMIF_BASE + R_PDMIF_PDCSTRTR_OFFSET)
#define R_PDMIF_PDCSTPTR                          (R_PDMIF_BASE + R_PDMIF_PDCSTPTR_OFFSET)
#define R_PDMIF_PDCCHGTR                          (R_PDMIF_BASE + R_PDMIF_PDCCHGTR_OFFSET)
#define R_PDMIF_PDCICR                            (R_PDMIF_BASE + R_PDMIF_PDCICR_OFFSET)
#define R_PDMIF_PDCSR                             (R_PDMIF_BASE + R_PDMIF_PDCSR_OFFSET)
#define R_PDMIF_PDCSCR                            (R_PDMIF_BASE + R_PDMIF_PDCSCR_OFFSET)
#define R_PDMIF_PDCSDCR                           (R_PDMIF_BASE + R_PDMIF_PDCSDCR_OFFSET)
#define R_PDMIF_PDCDRCR                           (R_PDMIF_BASE + R_PDMIF_PDCDRCR_OFFSET)
#define R_PDMIF_PDCDCR                            (R_PDMIF_BASE + R_PDMIF_PDCDCR_OFFSET)
#define R_PDMIF_PDVR                              (R_PDMIF_BASE + R_PDMIF_PDVR_OFFSET)
#define R_PDMIF_PDSTRTRCH(m)                      (R_PDMIF_BASE + R_PDMIF_PDSTRTRCH_OFFSET(m))
#define R_PDMIF_PDSTPTRCH(m)                      (R_PDMIF_BASE + R_PDMIF_PDSTPTRCH_OFFSET(m))
#define R_PDMIF_PDCHGTRCH(m)                      (R_PDMIF_BASE + R_PDMIF_PDCHGTRCH_OFFSET(m))
#define R_PDMIF_PDICRCH(m)                        (R_PDMIF_BASE + R_PDMIF_PDICRCH_OFFSET(m))
#define R_PDMIF_PDSDCRCH(m)                       (R_PDMIF_BASE + R_PDMIF_PDSDCRCH_OFFSET(m))
#define R_PDMIF_PDSRCH(m)                         (R_PDMIF_BASE + R_PDMIF_PDSRCH_OFFSET(m))
#define R_PDMIF_PDSCRCH(m)                        (R_PDMIF_BASE + R_PDMIF_PDSCRCH_OFFSET(m))
#define R_PDMIF_PDMDSRCH(m)                       (R_PDMIF_BASE + R_PDMIF_PDMDSRCH_OFFSET(m))
#define R_PDMIF_PDSFCRCH(m)                       (R_PDMIF_BASE + R_PDMIF_PDSFCRCH_OFFSET(m))
#define R_PDMIF_PDHFCS0RCH(m)                     (R_PDMIF_BASE + R_PDMIF_PDHFCS0RCH_OFFSET(m))
#define R_PDMIF_PDHFCK1RCH(m)                     (R_PDMIF_BASE + R_PDMIF_PDHFCK1RCH_OFFSET(m))
#define R_PDMIF_PDHFCH0RCH(m)                     (R_PDMIF_BASE + R_PDMIF_PDHFCH0RCH_OFFSET(m))
#define R_PDMIF_PDHFCH1RCH(m)                     (R_PDMIF_BASE + R_PDMIF_PDHFCH1RCH_OFFSET(m))
#define R_PDMIF_PDCFCH00RCH(m)                    (R_PDMIF_BASE + R_PDMIF_PDCFCH00RCH_OFFSET(m))
#define R_PDMIF_PDCFCH01RCH(m)                    (R_PDMIF_BASE + R_PDMIF_PDCFCH01RCH_OFFSET(m))
#define R_PDMIF_PDCFCH02RCH(m)                    (R_PDMIF_BASE + R_PDMIF_PDCFCH02RCH_OFFSET(m))
#define R_PDMIF_PDCFCH03RCH(m)                    (R_PDMIF_BASE + R_PDMIF_PDCFCH03RCH_OFFSET(m))
#define R_PDMIF_PDCFCH04RCH(m)                    (R_PDMIF_BASE + R_PDMIF_PDCFCH04RCH_OFFSET(m))
#define R_PDMIF_PDCFCH05RCH(m)                    (R_PDMIF_BASE + R_PDMIF_PDCFCH05RCH_OFFSET(m))
#define R_PDMIF_PDCFCH06RCHN                      (R_PDMIF_BASE + R_PDMIF_PDCFCH06RCHN_OFFSET)
#define R_PDMIF_PDCFCH07RCH(m)                    (R_PDMIF_BASE + R_PDMIF_PDCFCH07RCH_OFFSET(m))
#define R_PDMIF_PDCFCH08RCH(m)                    (R_PDMIF_BASE + R_PDMIF_PDCFCH08RCH_OFFSET(m))
#define R_PDMIF_PDCFCH09RCH(m)                    (R_PDMIF_BASE + R_PDMIF_PDCFCH09RCH_OFFSET(m))
#define R_PDMIF_PDCFCH10RCH(m)                    (R_PDMIF_BASE + R_PDMIF_PDCFCH10RCH_OFFSET(m))
#define R_PDMIF_PDLFCH010RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH010RCH_OFFSET(m))
#define R_PDMIF_PDLFCH100RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH100RCH_OFFSET(m))
#define R_PDMIF_PDLFCH101RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH101RCH_OFFSET(m))
#define R_PDMIF_PDLFCH102RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH102RCH_OFFSET(m))
#define R_PDMIF_PDLFCH103RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH103RCH_OFFSET(m))
#define R_PDMIF_PDLFCH104RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH104RCH_OFFSET(m))
#define R_PDMIF_PDLFCH105RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH105RCH_OFFSET(m))
#define R_PDMIF_PDLFCH106RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH106RCH_OFFSET(m))
#define R_PDMIF_PDLFCH107RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH107RCH_OFFSET(m))
#define R_PDMIF_PDLFCH108RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH108RCH_OFFSET(m))
#define R_PDMIF_PDLFCH109RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH109RCH_OFFSET(m))
#define R_PDMIF_PDLFCH110RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH110RCH_OFFSET(m))
#define R_PDMIF_PDLFCH111RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH111RCH_OFFSET(m))
#define R_PDMIF_PDLFCH112RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH112RCH_OFFSET(m))
#define R_PDMIF_PDLFCH113RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH113RCH_OFFSET(m))
#define R_PDMIF_PDLFCH114RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH114RCH_OFFSET(m))
#define R_PDMIF_PDLFCH115RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH115RCH_OFFSET(m))
#define R_PDMIF_PDLFCH116RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH116RCH_OFFSET(m))
#define R_PDMIF_PDLFCH117RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH117RCH_OFFSET(m))
#define R_PDMIF_PDLFCH118RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH118RCH_OFFSET(m))
#define R_PDMIF_PDLFCH119RCH(m)                   (R_PDMIF_BASE + R_PDMIF_PDLFCH119RCH_OFFSET(m))
#define R_PDMIF_PDSDLTRCH(m)                      (R_PDMIF_BASE + R_PDMIF_PDSDLTRCH_OFFSET(m))
#define R_PDMIF_PDSDUTRCH(m)                      (R_PDMIF_BASE + R_PDMIF_PDSDUTRCH_OFFSET(m))
#define R_PDMIF_PDDBCRCH(m)                       (R_PDMIF_BASE + R_PDMIF_PDDBCRCH_OFFSET(m))
#define R_PDMIF_PDSCTSRCH(m)                      (R_PDMIF_BASE + R_PDMIF_PDSCTSRCH_OFFSET(m))
#define R_PDMIF_PDOVLTRCH(m)                      (R_PDMIF_BASE + R_PDMIF_PDOVLTRCH_OFFSET(m))
#define R_PDMIF_PDOVUTRCH(m)                      (R_PDMIF_BASE + R_PDMIF_PDOVUTRCH_OFFSET(m))
#define R_PDMIF_PDDRCRCH(m)                       (R_PDMIF_BASE + R_PDMIF_PDDRCRCH_OFFSET(m))
#define R_PDMIF_PDDCRCH(m)                        (R_PDMIF_BASE + R_PDMIF_PDDCRCH_OFFSET(m))
#define R_PDMIF_PDDRRCH(m)                        (R_PDMIF_BASE + R_PDMIF_PDDRRCH_OFFSET(m))
#define R_PDMIF_PDDSRCH(m)                        (R_PDMIF_BASE + R_PDMIF_PDDSRCH_OFFSET(m))

/* Register bit definitions */
/* PDCSTRTR Register bit definitions */
#define R_PDMIF_PDCSTRTR_STRTRG0                  (1 << 0)  /* Channel 0 Start Trigger */

#define R_PDMIF_PDCSTRTR_STRTRG1                  (1 << 1)  /* Channel 1 Start Trigger */

#define R_PDMIF_PDCSTRTR_STRTRG2                  (1 << 2)  /* Channel 2 Start Trigger */

/* PDCSTPTR Register bit definitions */
#define R_PDMIF_PDCSTPTR_STPTRG0                  (1 << 0)  /* Channel 0 Stop Trigger */

#define R_PDMIF_PDCSTPTR_STPTRG1                  (1 << 1)  /* Channel 1 Stop Trigger */

#define R_PDMIF_PDCSTPTR_STPTRG2                  (1 << 2)  /* Channel 2 Stop Trigger */

/* PDCCHGTR Register bit definitions */
#define R_PDMIF_PDCCHGTR_CHGTRG0                  (1 << 0)  /* Channel 0 Change Trigger */

#define R_PDMIF_PDCCHGTR_CHGTRG1                  (1 << 1)  /* Channel 1 Change Trigger */

#define R_PDMIF_PDCCHGTR_CHGTRG2                  (1 << 2)  /* Channel 2 Change Trigger */

/* PDCICR Register bit definitions */
#define R_PDMIF_PDCICR_ISDE0                      (1 << 8)  /* Channel 0 Sound Detection Interrupt Enable Bit */

#define R_PDMIF_PDCICR_ISDE1                      (1 << 9)  /* Channel 1 Sound Detection Interrupt Enable Bit */

#define R_PDMIF_PDCICR_ISDE2                      (1 << 10)  /* Channel 2 Sound Detection Interrupt Enable Bit */

#define R_PDMIF_PDCICR_IDRE0                      (1 << 16)  /* Channel 0 Data Reception Interrupt Enable Bit */

#define R_PDMIF_PDCICR_IDRE1                      (1 << 17)  /* Channel 1 Data Reception Interrupt Enable Bit */

#define R_PDMIF_PDCICR_IDRE2                      (1 << 18)  /* Channel 2 Data Reception Interrupt Enable Bit */

#define R_PDMIF_PDCICR_IEDE0                      (1 << 24)  /* Channel 0 Error Detection Interrupt Enable Bit */

#define R_PDMIF_PDCICR_IEDE1                      (1 << 25)  /* Channel 1 Error Detection Interrupt Enable Bit */

#define R_PDMIF_PDCICR_IEDE2                      (1 << 26)  /* Channel 2 Error Detection Interrupt Enable Bit */

/* PDCSR Register bit definitions */
#define R_PDMIF_PDCSR_STATE0                      (1 << 0)  /* Channel 0 State */

#define R_PDMIF_PDCSR_STATE1                      (1 << 1)  /* Channel 1 State */

#define R_PDMIF_PDCSR_STATE2                      (1 << 2)  /* Channel 2 State */

#define R_PDMIF_PDCSR_SDF0                        (1 << 8)  /* Channel 0 Sound Detection Flag */

#define R_PDMIF_PDCSR_SDF1                        (1 << 9)  /* Channel 1 Sound Detection Flag */

#define R_PDMIF_PDCSR_SDF2                        (1 << 10)  /* Channel 2 Sound Detection Flag */

#define R_PDMIF_PDCSR_DRF0                        (1 << 16)  /* Channel 0 Data Reception Flag */

#define R_PDMIF_PDCSR_DRF1                        (1 << 17)  /* Channel 1 Data Reception Flag */

#define R_PDMIF_PDCSR_DRF2                        (1 << 18)  /* Channel 2 Data Reception Flag */

#define R_PDMIF_PDCSR_EDF0                        (1 << 24)  /* Channel 0 Error Detection Flag */

#define R_PDMIF_PDCSR_EDF1                        (1 << 25)  /* Channel 1 Error Detection Flag */

#define R_PDMIF_PDCSR_EDF2                        (1 << 26)  /* Channel 2 Error Detection Flag */

/* PDCSCR Register bit definitions */
#define R_PDMIF_PDCSCR_SDFC0                      (1 << 8)  /* Channel 0 Sound Detection Flag Clear */

#define R_PDMIF_PDCSCR_SDFC1                      (1 << 9)  /* Channel 1 Sound Detection Flag Clear */

#define R_PDMIF_PDCSCR_SDFC2                      (1 << 10)  /* Channel 2 Sound Detection Flag Clear */

/* PDCSDCR Register bit definitions */
#define R_PDMIF_PDCSDCR_SDE0                      (1 << 0)  /* Channel 0 Sound Detection Enable Bit */

#define R_PDMIF_PDCSDCR_SDE1                      (1 << 1)  /* Channel 1 Sound Detection Enable Bit */

#define R_PDMIF_PDCSDCR_SDE2                      (1 << 2)  /* Channel 2 Sound Detection Enable Bit */

/* PDCDRCR Register bit definitions */
#define R_PDMIF_PDCDRCR_DATRE0                    (1 << 0)  /* Channel 0 Data Read Enable Bit */

#define R_PDMIF_PDCDRCR_DATRE1                    (1 << 1)  /* Channel 1 Data Read Enable Bit */

#define R_PDMIF_PDCDRCR_DATRE2                    (1 << 2)  /* Channel 2 Data Read Enable Bit */

/* PDCDCR Register bit definitions */
#define R_PDMIF_PDCDCR_DATC0                      (1 << 0)  /* Channel 0 Data Clear */

#define R_PDMIF_PDCDCR_DATC1                      (1 << 1)  /* Channel 1 Data Clear */

#define R_PDMIF_PDCDCR_DATC2                      (1 << 2)  /* Channel 2 Data Clear */

/* PDVR Register bit definitions */
#define R_PDMIF_PDVR_VER_SHIFT                    (0)  /* PDM-IF version is shown. */
#define R_PDMIF_PDVR_VER_MASK                     0xfff

/* PDSTRTRCH Register bit definitions */
#define R_PDMIF_PDSTRTRCH_STRTRG                  (1 << 0)  /* Start Trigger */

/* PDSTPTRCH Register bit definitions */
#define R_PDMIF_PDSTPTRCH_STPTRG                  (1 << 0)  /* Stop Trigger */

/* PDCHGTRCH Register bit definitions */
#define R_PDMIF_PDCHGTRCH_CHGTRG                  (1 << 0)  /* Change Trigger */

/* PDICRCH Register bit definitions */
#define R_PDMIF_PDICRCH_ISDE                      (1 << 1)  /* Sound Detection Interrupt Enable Bit */

#define R_PDMIF_PDICRCH_IDRE                      (1 << 2)  /* Data Reception Interrupt Enable Bit */

#define R_PDMIF_PDICRCH_IEDE                      (1 << 16)  /* Error Detection Interrupt Enable Bit */

/* PDSDCRCH Register bit definitions */
#define R_PDMIF_PDSDCRCH_SDE                      (1 << 1)  /* Sound Detection Enable Bit */

#define R_PDMIF_PDSDCRCH_SCDE                     (1 << 16)  /* Short Circuit Detection Enable Bit */

#define R_PDMIF_PDSDCRCH_OVLDE                    (1 << 17)  /* Overvoltage Lower Limit Exceeded Detection Enable Bit */

#define R_PDMIF_PDSDCRCH_OVUDE                    (1 << 18)  /* Overvoltage Upper Limit Exceeded Detection Enable Bit */

#define R_PDMIF_PDSDCRCH_BFOWDE                   (1 << 27)  /* Buffer Overwriting Detection Enable Bit */

/* PDSRCH Register bit definitions */
#define R_PDMIF_PDSRCH_STATE                      (1 << 0)  /* State */

#define R_PDMIF_PDSRCH_SDF                        (1 << 1)  /* Sound Detection Flag */

#define R_PDMIF_PDSRCH_DRF                        (1 << 2)  /* Data Reception Flag */

#define R_PDMIF_PDSRCH_SCDF                       (1 << 16)  /* Short circuit detection flag. */

#define R_PDMIF_PDSRCH_OVLDF                      (1 << 17)  /* Overvoltage Lower Limit Exceeded Detection Flag */

#define R_PDMIF_PDSRCH_OVUDF                      (1 << 18)  /* Overvoltage Upper Limit Exceeded Detection Flag */

#define R_PDMIF_PDSRCH_BFOWDF                     (1 << 27)  /* Buffer Overwriting Detection Flag */

/* PDSCRCH Register bit definitions */
#define R_PDMIF_PDSCRCH_SDFC                      (1 << 1)  /* Sound Detection Flag Clear */

#define R_PDMIF_PDSCRCH_SCDFC                     (1 << 16)  /* Short Circuit Detection Flag Clear */

#define R_PDMIF_PDSCRCH_OVLDFC                    (1 << 17)  /* Overvoltage Lower Limit Exceeded Detection Flag Clear */

#define R_PDMIF_PDSCRCH_OVUDFC                    (1 << 18)  /* Overvoltage Upper Limit Exceeded Detection Flag Clear */

#define R_PDMIF_PDSCRCH_BFOWDFC                   (1 << 27)  /* Buffer Overwriting Detection Flag Clear */

/* PDMDSRCH Register bit definitions */
#define R_PDMIF_PDMDSRCH_INPSEL                   (1 << 0)  /* Input Data Select */

#define R_PDMIF_PDMDSRCH_SFMD_SHIFT               (4)  /* Sinc Filter Mode Setting */
#define R_PDMIF_PDMDSRCH_SFMD_MASK                0x70
#  define R_PDMIF_PDMDSRCH_SFMD_001                       (1 << R_PDMIF_PDMDSRCH_SFMD_SHIFT)  /* 1-order */
#  define R_PDMIF_PDMDSRCH_SFMD_010                       (2 << R_PDMIF_PDMDSRCH_SFMD_SHIFT)  /* 2-order */
#  define R_PDMIF_PDMDSRCH_SFMD_011                       (3 << R_PDMIF_PDMDSRCH_SFMD_SHIFT)  /* 3-order */

#define R_PDMIF_PDMDSRCH_HFIS_SHIFT               (8)  /* High-pass Filter Input Shift Setting */
#define R_PDMIF_PDMDSRCH_HFIS_MASK                0x300
#  define R_PDMIF_PDMDSRCH_HFIS_00                        (0 << R_PDMIF_PDMDSRCH_HFIS_SHIFT)  /* No shift */
#  define R_PDMIF_PDMDSRCH_HFIS_01                        (1 << R_PDMIF_PDMDSRCH_HFIS_SHIFT)  /* 1-bit right shift */
#  define R_PDMIF_PDMDSRCH_HFIS_10                        (2 << R_PDMIF_PDMDSRCH_HFIS_SHIFT)  /* 2-bit right shift  */
#  define R_PDMIF_PDMDSRCH_HFIS_11                        (3 << R_PDMIF_PDMDSRCH_HFIS_SHIFT)  /* 3-bit right shift */

#define R_PDMIF_PDMDSRCH_CFIS_SHIFT               (12)  /* Compensation Filter Input Shift Setting */
#define R_PDMIF_PDMDSRCH_CFIS_MASK                0x3000
#  define R_PDMIF_PDMDSRCH_CFIS_00                        (0 << R_PDMIF_PDMDSRCH_CFIS_SHIFT)  /* No shift */
#  define R_PDMIF_PDMDSRCH_CFIS_01                        (1 << R_PDMIF_PDMDSRCH_CFIS_SHIFT)  /* 1-bit right shift */
#  define R_PDMIF_PDMDSRCH_CFIS_10                        (2 << R_PDMIF_PDMDSRCH_CFIS_SHIFT)  /* 2-bit right shift */
#  define R_PDMIF_PDMDSRCH_CFIS_11                        (3 << R_PDMIF_PDMDSRCH_CFIS_SHIFT)  /* 3-bit right shift */

#define R_PDMIF_PDMDSRCH_LFIS_SHIFT               (16)  /* Low-pass (half-band decimation) Filter Input Shift Setting */
#define R_PDMIF_PDMDSRCH_LFIS_MASK                0x30000
#  define R_PDMIF_PDMDSRCH_LFIS_00                        (0 << R_PDMIF_PDMDSRCH_LFIS_SHIFT)  /* No shift */
#  define R_PDMIF_PDMDSRCH_LFIS_01                        (1 << R_PDMIF_PDMDSRCH_LFIS_SHIFT)  /* 1-bit right shift */
#  define R_PDMIF_PDMDSRCH_LFIS_10                        (2 << R_PDMIF_PDMDSRCH_LFIS_SHIFT)  /* 2-bit right shift */
#  define R_PDMIF_PDMDSRCH_LFIS_11                        (3 << R_PDMIF_PDMDSRCH_LFIS_SHIFT)  /* 3-bit right shift */

#define R_PDMIF_PDMDSRCH_SDMAMD_SHIFT             (24)  /* Moving Average Mode for Sound Detection Data */
#define R_PDMIF_PDMDSRCH_SDMAMD_MASK              0x3000000
#  define R_PDMIF_PDMDSRCH_SDMAMD_00                      (0 << R_PDMIF_PDMDSRCH_SDMAMD_SHIFT)  /* 1-order (filter is skipped) (default) */
#  define R_PDMIF_PDMDSRCH_SDMAMD_01                      (1 << R_PDMIF_PDMDSRCH_SDMAMD_SHIFT)  /* 2-order */
#  define R_PDMIF_PDMDSRCH_SDMAMD_10                      (2 << R_PDMIF_PDMDSRCH_SDMAMD_SHIFT)  /* 4-order */
#  define R_PDMIF_PDMDSRCH_SDMAMD_11                      (3 << R_PDMIF_PDMDSRCH_SDMAMD_SHIFT)  /* User prohibition */

#define R_PDMIF_PDMDSRCH_DBIS_SHIFT               (28)  /* Data Buffer Input Shift Setting */
#define R_PDMIF_PDMDSRCH_DBIS_MASK                0xf0000000
#  define R_PDMIF_PDMDSRCH_DBIS_0X0                       (0 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 20-bit mode, {1{S}, [18:0]} */
#  define R_PDMIF_PDMDSRCH_DBIS_0X1                       (1 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 20-bit mode, {2{S}, [18:1]} */
#  define R_PDMIF_PDMDSRCH_DBIS_0X2                       (2 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 20-bit mode, {3{S}, [18:2]} */
#  define R_PDMIF_PDMDSRCH_DBIS_0X3                       (3 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 20-bit mode, {4{S}, [18:3]} */
#  define R_PDMIF_PDMDSRCH_DBIS_0X8                       (8 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 16-bit mode, {S,D[18:4]} */
#  define R_PDMIF_PDMDSRCH_DBIS_0X9                       (9 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 16-bit mode, {S,D[17:3]} */
#  define R_PDMIF_PDMDSRCH_DBIS_0XA                       (10 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 16-bit mode, {S,D[16:2]} */
#  define R_PDMIF_PDMDSRCH_DBIS_0XB                       (11 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 16-bit mode, {S,D[15:1]} */
#  define R_PDMIF_PDMDSRCH_DBIS_0XC                       (12 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 16-bit mode, {S,D[14:0]} */

/* PDSFCRCH Register bit definitions */
#define R_PDMIF_PDSFCRCH_CKDIV_SHIFT              (0)  /* PDM_CLKn Dividend Ratio to Core Clock */
#define R_PDMIF_PDSFCRCH_CKDIV_MASK               0xf

#define R_PDMIF_PDSFCRCH_SINCDEC_SHIFT            (16)  /* Sinc Filter Decimation Ratio */
#define R_PDMIF_PDSFCRCH_SINCDEC_MASK             0xff0000

#define R_PDMIF_PDSFCRCH_SINCRNG_SHIFT            (24)  /* Sinc Filter Output Valid Range */
#define R_PDMIF_PDSFCRCH_SINCRNG_MASK             0x1f000000
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X00                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [32:14]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X01                   (1 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [31:13]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X02                   (2 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [30:12]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X03                   (3 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [29:11]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X04                   (4 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [28:10]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X05                   (5 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [27:9]} (default) */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X06                   (6 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [26:8]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X07                   (7 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [25:7]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X08                   (8 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [24:6]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X09                   (9 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [23:5]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X0A                   (10 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [22:4]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X0B                   (11 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [21:3]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X0C                   (12 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [20:2]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X0D                   (13 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [19:1]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X0E                   (14 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [18:0]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X0F                   (15 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [17:0], 0} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X10                   (16 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [16:0], 00} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X11                   (17 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [15:0], 000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X12                   (18 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [14:0], 0000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X13                   (19 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [13:0], 00000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X14                   (20 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [12:0], 000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X15                   (21 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [11:0], 0000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X16                   (22 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [10:0], 00000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X17                   (23 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [9:0], 000000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X18                   (24 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [8:0], 0000000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X19                   (25 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [7:0], 00000000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X1A                   (26 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [6:0], 000000000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X1B                   (27 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [5:0], 0000000000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X1C                   (28 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [4:0], 00000000000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X1D                   (29 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [3:0], 000000000000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X1E                   (30 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [2:0], 0000000000000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X1F                   (31 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [1:0], 00000000000000000} (prohibited) */

/* PDHFCS0RCH Register bit definitions */
#define R_PDMIF_PDHFCS0RCH_HFS_SHIFT              (0)  /* High-pass Filter Coefficient s(0) */
#define R_PDMIF_PDHFCS0RCH_HFS_MASK               0xffff

/* PDHFCK1RCH Register bit definitions */
#define R_PDMIF_PDHFCK1RCH_HFK_SHIFT              (0)  /* High-pass Filter Coefficient k(1) */
#define R_PDMIF_PDHFCK1RCH_HFK_MASK               0xffff

/* PDHFCH0RCH Register bit definitions */
#define R_PDMIF_PDHFCH0RCH_HFH_SHIFT              (0)  /* High-pass Filter Coefficient h(0) */
#define R_PDMIF_PDHFCH0RCH_HFH_MASK               0xffff

/* PDHFCH1RCH Register bit definitions */
#define R_PDMIF_PDHFCH1RCH_HFH_SHIFT              (0)  /* High-pass Filter Coefficient h(1) */
#define R_PDMIF_PDHFCH1RCH_HFH_MASK               0xffff

/* PDCFCH00RCH Register bit definitions */
#define R_PDMIF_PDCFCH00RCH_CFH_SHIFT             (0)  /* Compensation Filter Coefficients h(0) */
#define R_PDMIF_PDCFCH00RCH_CFH_MASK              0x1fff

/* PDCFCH01RCH Register bit definitions */
#define R_PDMIF_PDCFCH01RCH_CFH_SHIFT             (0)  /* Compensation Filter Coefficients h(1) */
#define R_PDMIF_PDCFCH01RCH_CFH_MASK              0x1fff

/* PDCFCH02RCH Register bit definitions */
#define R_PDMIF_PDCFCH02RCH_CFH_SHIFT             (0)  /* Compensation Filter Coefficients h(2) */
#define R_PDMIF_PDCFCH02RCH_CFH_MASK              0x1fff

/* PDCFCH03RCH Register bit definitions */
#define R_PDMIF_PDCFCH03RCH_CFH_SHIFT             (0)  /* Compensation Filter Coefficients h(3) */
#define R_PDMIF_PDCFCH03RCH_CFH_MASK              0x1fff

/* PDCFCH04RCH Register bit definitions */
#define R_PDMIF_PDCFCH04RCH_CFH_SHIFT             (0)  /* Compensation Filter Coefficients h(4) */
#define R_PDMIF_PDCFCH04RCH_CFH_MASK              0x1fff

/* PDCFCH05RCH Register bit definitions */
#define R_PDMIF_PDCFCH05RCH_CFH_SHIFT             (0)  /* Compensation Filter Coefficients h(5) */
#define R_PDMIF_PDCFCH05RCH_CFH_MASK              0x1fff

/* PDCFCH06RCHN Register bit definitions */
#define R_PDMIF_PDCFCH06RCHN_CFH_SHIFT            (0)  /* Compensation Filter Coefficients h(6) */
#define R_PDMIF_PDCFCH06RCHN_CFH_MASK             0x1fff

/* PDCFCH07RCH Register bit definitions */
#define R_PDMIF_PDCFCH07RCH_CFH_SHIFT             (0)  /* Compensation Filter Coefficients h(7) */
#define R_PDMIF_PDCFCH07RCH_CFH_MASK              0x1fff

/* PDCFCH08RCH Register bit definitions */
#define R_PDMIF_PDCFCH08RCH_CFH_SHIFT             (0)  /* Compensation Filter Coefficients h(8) */
#define R_PDMIF_PDCFCH08RCH_CFH_MASK              0x1fff

/* PDCFCH09RCH Register bit definitions */
#define R_PDMIF_PDCFCH09RCH_CFH_SHIFT             (0)  /* Compensation Filter Coefficients h(9) */
#define R_PDMIF_PDCFCH09RCH_CFH_MASK              0x1fff

/* PDCFCH10RCH Register bit definitions */
#define R_PDMIF_PDCFCH10RCH_CFH_SHIFT             (0)  /* Compensation Filter Coefficients h(10) */
#define R_PDMIF_PDCFCH10RCH_CFH_MASK              0x1fff

/* PDLFCH010RCH Register bit definitions */
#define R_PDMIF_PDLFCH010RCH_LFH0_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h0(10) */
#define R_PDMIF_PDLFCH010RCH_LFH0_MASK            0x1fff

/* PDLFCH100RCH Register bit definitions */
#define R_PDMIF_PDLFCH100RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(0) */
#define R_PDMIF_PDLFCH100RCH_LFH1_MASK            0x1fff

/* PDLFCH101RCH Register bit definitions */
#define R_PDMIF_PDLFCH101RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(1) */
#define R_PDMIF_PDLFCH101RCH_LFH1_MASK            0x1fff

/* PDLFCH102RCH Register bit definitions */
#define R_PDMIF_PDLFCH102RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(2) */
#define R_PDMIF_PDLFCH102RCH_LFH1_MASK            0x1fff

/* PDLFCH103RCH Register bit definitions */
#define R_PDMIF_PDLFCH103RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(3) */
#define R_PDMIF_PDLFCH103RCH_LFH1_MASK            0x1fff

/* PDLFCH104RCH Register bit definitions */
#define R_PDMIF_PDLFCH104RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(4) */
#define R_PDMIF_PDLFCH104RCH_LFH1_MASK            0x1fff

/* PDLFCH105RCH Register bit definitions */
#define R_PDMIF_PDLFCH105RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(5) */
#define R_PDMIF_PDLFCH105RCH_LFH1_MASK            0x1fff

/* PDLFCH106RCH Register bit definitions */
#define R_PDMIF_PDLFCH106RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(6) */
#define R_PDMIF_PDLFCH106RCH_LFH1_MASK            0x1fff

/* PDLFCH107RCH Register bit definitions */
#define R_PDMIF_PDLFCH107RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(7) */
#define R_PDMIF_PDLFCH107RCH_LFH1_MASK            0x1fff

/* PDLFCH108RCH Register bit definitions */
#define R_PDMIF_PDLFCH108RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(8) */
#define R_PDMIF_PDLFCH108RCH_LFH1_MASK            0x1fff

/* PDLFCH109RCH Register bit definitions */
#define R_PDMIF_PDLFCH109RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(9) */
#define R_PDMIF_PDLFCH109RCH_LFH1_MASK            0x1fff

/* PDLFCH110RCH Register bit definitions */
#define R_PDMIF_PDLFCH110RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(10) */
#define R_PDMIF_PDLFCH110RCH_LFH1_MASK            0x1fff

/* PDLFCH111RCH Register bit definitions */
#define R_PDMIF_PDLFCH111RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(11) */
#define R_PDMIF_PDLFCH111RCH_LFH1_MASK            0x1fff

/* PDLFCH112RCH Register bit definitions */
#define R_PDMIF_PDLFCH112RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(12) */
#define R_PDMIF_PDLFCH112RCH_LFH1_MASK            0x1fff

/* PDLFCH113RCH Register bit definitions */
#define R_PDMIF_PDLFCH113RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(13) */
#define R_PDMIF_PDLFCH113RCH_LFH1_MASK            0x1fff

/* PDLFCH114RCH Register bit definitions */
#define R_PDMIF_PDLFCH114RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(14) */
#define R_PDMIF_PDLFCH114RCH_LFH1_MASK            0x1fff

/* PDLFCH115RCH Register bit definitions */
#define R_PDMIF_PDLFCH115RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(15) */
#define R_PDMIF_PDLFCH115RCH_LFH1_MASK            0x1fff

/* PDLFCH116RCH Register bit definitions */
#define R_PDMIF_PDLFCH116RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(15) */
#define R_PDMIF_PDLFCH116RCH_LFH1_MASK            0x1fff

/* PDLFCH117RCH Register bit definitions */
#define R_PDMIF_PDLFCH117RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(17) */
#define R_PDMIF_PDLFCH117RCH_LFH1_MASK            0x1fff

/* PDLFCH118RCH Register bit definitions */
#define R_PDMIF_PDLFCH118RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(18) */
#define R_PDMIF_PDLFCH118RCH_LFH1_MASK            0x1fff

/* PDLFCH119RCH Register bit definitions */
#define R_PDMIF_PDLFCH119RCH_LFH1_SHIFT           (0)  /* Low-pass (half-band decimation) Filter Coefficient h1(19) */
#define R_PDMIF_PDLFCH119RCH_LFH1_MASK            0x1fff

/* PDSDLTRCH Register bit definitions */
#define R_PDMIF_PDSDLTRCH_SDETL_SHIFT             (0)  /* Sound Detection Lower Limit */
#define R_PDMIF_PDSDLTRCH_SDETL_MASK              0xfffff

/* PDSDUTRCH Register bit definitions */
#define R_PDMIF_PDSDUTRCH_SDETU_SHIFT             (0)  /* Sound Detection Upper Limit */
#define R_PDMIF_PDSDUTRCH_SDETU_MASK              0xfffff

/* PDDBCRCH Register bit definitions */
#define R_PDMIF_PDDBCRCH_DATRITHR_SHIFT           (0)  /* Data Reception Interrupt Threshold */
#define R_PDMIF_PDDBCRCH_DATRITHR_MASK            0x7
#  define R_PDMIF_PDDBCRCH_DATRITHR_000                   (0 << R_PDMIF_PDDBCRCH_DATRITHR_SHIFT)  /* Output interrupt when receiving 1 or more data */
#  define R_PDMIF_PDDBCRCH_DATRITHR_001                   (1 << R_PDMIF_PDDBCRCH_DATRITHR_SHIFT)  /* Output interrupt when receiving 2 or more data */
#  define R_PDMIF_PDDBCRCH_DATRITHR_010                   (2 << R_PDMIF_PDDBCRCH_DATRITHR_SHIFT)  /* Output interrupt when receiving 4 or more data */
#  define R_PDMIF_PDDBCRCH_DATRITHR_011                   (3 << R_PDMIF_PDDBCRCH_DATRITHR_SHIFT)  /* Output interrupt when receiving 8 or more data */

/* PDSCTSRCH Register bit definitions */
#define R_PDMIF_PDSCTSRCH_SCDL_SHIFT              (0)  /* Short Circuit Detection Low Continuous Detection Count */
#define R_PDMIF_PDSCTSRCH_SCDL_MASK               0x1fff

#define R_PDMIF_PDSCTSRCH_SCDH_SHIFT              (16)  /* Short Circuit Detection High Continuous Detection Count */
#define R_PDMIF_PDSCTSRCH_SCDH_MASK               0x1fff0000

/* PDOVLTRCH Register bit definitions */
#define R_PDMIF_PDOVLTRCH_OVDL_SHIFT              (0)  /* Overvoltage Detection Lower Limit */
#define R_PDMIF_PDOVLTRCH_OVDL_MASK               0xfffff

/* PDOVUTRCH Register bit definitions */
#define R_PDMIF_PDOVUTRCH_OVDU_SHIFT              (0)  /* Overvoltage Detection Upper Limit */
#define R_PDMIF_PDOVUTRCH_OVDU_MASK               0xfffff

/* PDDRCRCH Register bit definitions */
#define R_PDMIF_PDDRCRCH_DATRE                    (1 << 0)  /* Data Read Enable Bit */

/* PDDCRCH Register bit definitions */
#define R_PDMIF_PDDCRCH_DATC                      (1 << 0)  /* Data Clear */

/* PDDRRCH Register bit definitions */
#define R_PDMIF_PDDRRCH_DAT_SHIFT                 (0)  /* Data */
#define R_PDMIF_PDDRRCH_DAT_MASK                  0xfffff

/* PDDSRCH Register bit definitions */
#define R_PDMIF_PDDSRCH_DATNUM_SHIFT              (0)  /* Number of Data Stored in Buffer */
#define R_PDMIF_PDDSRCH_DATNUM_MASK               0xff


/* Maximum number of channels */

#define PDMIF_MAX_CHANNELS    3

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PDMIF_H */

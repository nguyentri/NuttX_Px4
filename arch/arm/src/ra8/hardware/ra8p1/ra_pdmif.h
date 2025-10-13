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

/* Channel stride for multi-channel peripherals */
#define R_PDMIF_CH_STRIDE    0x00000100
#define R_PDMIF_CH_BASE(ch)   (R_PDMIF_BASE + ((uint32_t)(ch) * R_PDMIF_CH_STRIDE))

/* PDMIF Register Offsets */

#define R_PDMIF_PDCSTRTR_OFFSET     0x00000000  /* Channel Software Start Trigger Register */
#define R_PDMIF_PDCSTPTR_OFFSET     0x00000004  /* Channel Software Stop Trigger Register */
#define R_PDMIF_PDCCHGTR_OFFSET     0x00000008  /* Channel Software Change Trigger Register */
#define R_PDMIF_PDCICR_OFFSET     0x0000000c  /* Channel Interrupt Control Register */
#define R_PDMIF_PDCSR_OFFSET     0x00000010  /* Channel Status Register */
#define R_PDMIF_PDCSCR_OFFSET     0x00000014  /* Channel Status Clear Register */
#define R_PDMIF_PDCSDCR_OFFSET     0x00000020  /* Channel Sound Detection Control Register */
#define R_PDMIF_PDCDRCR_OFFSET     0x00000024  /* Channel Data Read Control Register */
#define R_PDMIF_PDCDCR_OFFSET     0x00000028  /* Channel Data Clear Register */
#define R_PDMIF_PDVR_OFFSET     0x00000080  /* Version Register */
/* PDSTRTRCH%s Registers (0-2) */
#define R_PDMIF_PDSTRTRCH0_OFFSET     0x00000100  /* Software Start Trigger Register Channel 0 */
#define R_PDMIF_PDSTRTRCH1_OFFSET     0x00000200  /* Software Start Trigger Register Channel 1 */
#define R_PDMIF_PDSTRTRCH2_OFFSET     0x00000300  /* Software Start Trigger Register Channel 2 */
/* PDSTPTRCH%s Registers (0-2) */
#define R_PDMIF_PDSTPTRCH0_OFFSET     0x00000104  /* Software Stop Trigger Register Channel 0 */
#define R_PDMIF_PDSTPTRCH1_OFFSET     0x00000204  /* Software Stop Trigger Register Channel 1 */
#define R_PDMIF_PDSTPTRCH2_OFFSET     0x00000304  /* Software Stop Trigger Register Channel 2 */
/* PDCHGTRCH%s Registers (0-2) */
#define R_PDMIF_PDCHGTRCH0_OFFSET     0x00000108  /* Software Change Trigger Register Channel 0 */
#define R_PDMIF_PDCHGTRCH1_OFFSET     0x00000208  /* Software Change Trigger Register Channel 1 */
#define R_PDMIF_PDCHGTRCH2_OFFSET     0x00000308  /* Software Change Trigger Register Channel 2 */
/* PDICRCH%s Registers (0-2) */
#define R_PDMIF_PDICRCH0_OFFSET     0x0000010c  /* Interrupt Control Register Channel 0 */
#define R_PDMIF_PDICRCH1_OFFSET     0x0000020c  /* Interrupt Control Register Channel 1 */
#define R_PDMIF_PDICRCH2_OFFSET     0x0000030c  /* Interrupt Control Register Channel 2 */
/* PDSDCRCH%s Registers (0-2) */
#define R_PDMIF_PDSDCRCH0_OFFSET     0x00000110  /* Status Detection Control Register Channel 0 */
#define R_PDMIF_PDSDCRCH1_OFFSET     0x00000210  /* Status Detection Control Register Channel 1 */
#define R_PDMIF_PDSDCRCH2_OFFSET     0x00000310  /* Status Detection Control Register Channel 2 */
/* PDSRCH%s Registers (0-2) */
#define R_PDMIF_PDSRCH0_OFFSET     0x00000114  /* Status Register Channel 0 */
#define R_PDMIF_PDSRCH1_OFFSET     0x00000214  /* Status Register Channel 1 */
#define R_PDMIF_PDSRCH2_OFFSET     0x00000314  /* Status Register Channel 2 */
/* PDSCRCH%s Registers (0-2) */
#define R_PDMIF_PDSCRCH0_OFFSET     0x00000118  /* Status Clear Register Channel 0 */
#define R_PDMIF_PDSCRCH1_OFFSET     0x00000218  /* Status Clear Register Channel 1 */
#define R_PDMIF_PDSCRCH2_OFFSET     0x00000318  /* Status Clear Register Channel 2 */
/* PDMDSRCH%s Registers (0-2) */
#define R_PDMIF_PDMDSRCH0_OFFSET     0x00000120  /* Mode Setting Register Channel 0 */
#define R_PDMIF_PDMDSRCH1_OFFSET     0x00000220  /* Mode Setting Register Channel 1 */
#define R_PDMIF_PDMDSRCH2_OFFSET     0x00000320  /* Mode Setting Register Channel 2 */
/* PDSFCRCH%s Registers (0-2) */
#define R_PDMIF_PDSFCRCH0_OFFSET     0x00000124  /* Sinc Filter Control Register Channel 0 */
#define R_PDMIF_PDSFCRCH1_OFFSET     0x00000224  /* Sinc Filter Control Register Channel 1 */
#define R_PDMIF_PDSFCRCH2_OFFSET     0x00000324  /* Sinc Filter Control Register Channel 2 */
/* PDHFCS0RCH%s Registers (0-2) */
#define R_PDMIF_PDHFCS0RCH0_OFFSET     0x00000128  /* High-pass Filter Coefficient s(0) Register Channel 0 */
#define R_PDMIF_PDHFCS0RCH1_OFFSET     0x00000228  /* High-pass Filter Coefficient s(0) Register Channel 1 */
#define R_PDMIF_PDHFCS0RCH2_OFFSET     0x00000328  /* High-pass Filter Coefficient s(0) Register Channel 2 */
/* PDHFCK1RCH%s Registers (0-2) */
#define R_PDMIF_PDHFCK1RCH0_OFFSET     0x0000012c  /* High-pass Filter Coefficient k(1) Register Channel 0 */
#define R_PDMIF_PDHFCK1RCH1_OFFSET     0x0000022c  /* High-pass Filter Coefficient k(1) Register Channel 1 */
#define R_PDMIF_PDHFCK1RCH2_OFFSET     0x0000032c  /* High-pass Filter Coefficient k(1) Register Channel 2 */
/* PDHFCH0RCH%s Registers (0-2) */
#define R_PDMIF_PDHFCH0RCH0_OFFSET     0x00000130  /* High-pass Filter Coefficient h(0) Register Channel 0 */
#define R_PDMIF_PDHFCH0RCH1_OFFSET     0x00000230  /* High-pass Filter Coefficient h(0) Register Channel 1 */
#define R_PDMIF_PDHFCH0RCH2_OFFSET     0x00000330  /* High-pass Filter Coefficient h(0) Register Channel 2 */
/* PDHFCH1RCH%s Registers (0-2) */
#define R_PDMIF_PDHFCH1RCH0_OFFSET     0x00000134  /* High-pass Filter Coefficient h(1) Register Channel 0 */
#define R_PDMIF_PDHFCH1RCH1_OFFSET     0x00000234  /* High-pass Filter Coefficient h(1) Register Channel 1 */
#define R_PDMIF_PDHFCH1RCH2_OFFSET     0x00000334  /* High-pass Filter Coefficient h(1) Register Channel 2 */
/* PDCFCH00RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH00RCH0_OFFSET     0x00000138  /* Compensation Filter Coefficient h(0) Register Channel 0 */
#define R_PDMIF_PDCFCH00RCH1_OFFSET     0x00000238  /* Compensation Filter Coefficient h(0) Register Channel 1 */
#define R_PDMIF_PDCFCH00RCH2_OFFSET     0x00000338  /* Compensation Filter Coefficient h(0) Register Channel 2 */
/* PDCFCH01RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH01RCH0_OFFSET     0x0000013c  /* Compensation Filter Coefficient h(1) Register Channel 0 */
#define R_PDMIF_PDCFCH01RCH1_OFFSET     0x0000023c  /* Compensation Filter Coefficient h(1) Register Channel 1 */
#define R_PDMIF_PDCFCH01RCH2_OFFSET     0x0000033c  /* Compensation Filter Coefficient h(1) Register Channel 2 */
/* PDCFCH02RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH02RCH0_OFFSET     0x00000140  /* Compensation Filter Coefficient h(2) Register Channel 0 */
#define R_PDMIF_PDCFCH02RCH1_OFFSET     0x00000240  /* Compensation Filter Coefficient h(2) Register Channel 1 */
#define R_PDMIF_PDCFCH02RCH2_OFFSET     0x00000340  /* Compensation Filter Coefficient h(2) Register Channel 2 */
/* PDCFCH03RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH03RCH0_OFFSET     0x00000144  /* Compensation Filter Coefficient h(3) Register Channel 0 */
#define R_PDMIF_PDCFCH03RCH1_OFFSET     0x00000244  /* Compensation Filter Coefficient h(3) Register Channel 1 */
#define R_PDMIF_PDCFCH03RCH2_OFFSET     0x00000344  /* Compensation Filter Coefficient h(3) Register Channel 2 */
/* PDCFCH04RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH04RCH0_OFFSET     0x00000148  /* Compensation Filter Coefficient h(4) Register Channel 0 */
#define R_PDMIF_PDCFCH04RCH1_OFFSET     0x00000248  /* Compensation Filter Coefficient h(4) Register Channel 1 */
#define R_PDMIF_PDCFCH04RCH2_OFFSET     0x00000348  /* Compensation Filter Coefficient h(4) Register Channel 2 */
/* PDCFCH05RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH05RCH0_OFFSET     0x0000014c  /* Compensation Filter Coefficient h(5) Register Channel 0 */
#define R_PDMIF_PDCFCH05RCH1_OFFSET     0x0000024c  /* Compensation Filter Coefficient h(5) Register Channel 1 */
#define R_PDMIF_PDCFCH05RCH2_OFFSET     0x0000034c  /* Compensation Filter Coefficient h(5) Register Channel 2 */
#define R_PDMIF_PDCFCH06RCHN_OFFSET     0x00000150  /* Compensation Filter Coefficient h(6) Register Channel n */
/* PDCFCH07RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH07RCH0_OFFSET     0x00000154  /* Compensation Filter Coefficient h(7) Register Channel 0 */
#define R_PDMIF_PDCFCH07RCH1_OFFSET     0x00000254  /* Compensation Filter Coefficient h(7) Register Channel 1 */
#define R_PDMIF_PDCFCH07RCH2_OFFSET     0x00000354  /* Compensation Filter Coefficient h(7) Register Channel 2 */
/* PDCFCH08RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH08RCH0_OFFSET     0x00000158  /* Compensation Filter Coefficient h(8) Register Channel 0 */
#define R_PDMIF_PDCFCH08RCH1_OFFSET     0x00000258  /* Compensation Filter Coefficient h(8) Register Channel 1 */
#define R_PDMIF_PDCFCH08RCH2_OFFSET     0x00000358  /* Compensation Filter Coefficient h(8) Register Channel 2 */
/* PDCFCH09RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH09RCH0_OFFSET     0x0000015c  /* Compensation Filter Coefficient h(9) Register Channel 0 */
#define R_PDMIF_PDCFCH09RCH1_OFFSET     0x0000025c  /* Compensation Filter Coefficient h(9) Register Channel 1 */
#define R_PDMIF_PDCFCH09RCH2_OFFSET     0x0000035c  /* Compensation Filter Coefficient h(9) Register Channel 2 */
/* PDCFCH10RCH%s Registers (0-2) */
#define R_PDMIF_PDCFCH10RCH0_OFFSET     0x00000160  /* Compensation Filter Coefficient h(10) Register Channel 0 */
#define R_PDMIF_PDCFCH10RCH1_OFFSET     0x00000260  /* Compensation Filter Coefficient h(10) Register Channel 1 */
#define R_PDMIF_PDCFCH10RCH2_OFFSET     0x00000360  /* Compensation Filter Coefficient h(10) Register Channel 2 */
/* PDLFCH010RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH010RCH0_OFFSET     0x00000164  /* Low-pass Filter Coefficient h0(10) Register Channel 0 */
#define R_PDMIF_PDLFCH010RCH1_OFFSET     0x00000264  /* Low-pass Filter Coefficient h0(10) Register Channel 1 */
#define R_PDMIF_PDLFCH010RCH2_OFFSET     0x00000364  /* Low-pass Filter Coefficient h0(10) Register Channel 2 */
/* PDLFCH100RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH100RCH0_OFFSET     0x00000168  /* Low-pass Filter Coefficient h1(0) Register Channel 0 */
#define R_PDMIF_PDLFCH100RCH1_OFFSET     0x00000268  /* Low-pass Filter Coefficient h1(0) Register Channel 1 */
#define R_PDMIF_PDLFCH100RCH2_OFFSET     0x00000368  /* Low-pass Filter Coefficient h1(0) Register Channel 2 */
/* PDLFCH101RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH101RCH0_OFFSET     0x0000016c  /* Low-pass Filter Coefficient h1(1) Register Channel 0 */
#define R_PDMIF_PDLFCH101RCH1_OFFSET     0x0000026c  /* Low-pass Filter Coefficient h1(1) Register Channel 1 */
#define R_PDMIF_PDLFCH101RCH2_OFFSET     0x0000036c  /* Low-pass Filter Coefficient h1(1) Register Channel 2 */
/* PDLFCH102RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH102RCH0_OFFSET     0x00000170  /* Low-pass Filter Coefficient h1 (2) Register Channel 0 */
#define R_PDMIF_PDLFCH102RCH1_OFFSET     0x00000270  /* Low-pass Filter Coefficient h1 (2) Register Channel 1 */
#define R_PDMIF_PDLFCH102RCH2_OFFSET     0x00000370  /* Low-pass Filter Coefficient h1 (2) Register Channel 2 */
/* PDLFCH103RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH103RCH0_OFFSET     0x00000174  /* Low-pass Filter Coefficient h1(3) Register Channel 0 */
#define R_PDMIF_PDLFCH103RCH1_OFFSET     0x00000274  /* Low-pass Filter Coefficient h1(3) Register Channel 1 */
#define R_PDMIF_PDLFCH103RCH2_OFFSET     0x00000374  /* Low-pass Filter Coefficient h1(3) Register Channel 2 */
/* PDLFCH104RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH104RCH0_OFFSET     0x00000178  /* Low-pass Filter Coefficient h1(4) Register Channel 0 */
#define R_PDMIF_PDLFCH104RCH1_OFFSET     0x00000278  /* Low-pass Filter Coefficient h1(4) Register Channel 1 */
#define R_PDMIF_PDLFCH104RCH2_OFFSET     0x00000378  /* Low-pass Filter Coefficient h1(4) Register Channel 2 */
/* PDLFCH105RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH105RCH0_OFFSET     0x0000017c  /* Low-pass Filter Coefficient h1(5) Register Channel 0 */
#define R_PDMIF_PDLFCH105RCH1_OFFSET     0x0000027c  /* Low-pass Filter Coefficient h1(5) Register Channel 1 */
#define R_PDMIF_PDLFCH105RCH2_OFFSET     0x0000037c  /* Low-pass Filter Coefficient h1(5) Register Channel 2 */
/* PDLFCH106RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH106RCH0_OFFSET     0x00000180  /* Low-pass Filter Coefficient h1(6) Register Channel 0 */
#define R_PDMIF_PDLFCH106RCH1_OFFSET     0x00000280  /* Low-pass Filter Coefficient h1(6) Register Channel 1 */
#define R_PDMIF_PDLFCH106RCH2_OFFSET     0x00000380  /* Low-pass Filter Coefficient h1(6) Register Channel 2 */
/* PDLFCH107RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH107RCH0_OFFSET     0x00000184  /* Low-pass Filter Coefficient h1(7) Register Channel 0 */
#define R_PDMIF_PDLFCH107RCH1_OFFSET     0x00000284  /* Low-pass Filter Coefficient h1(7) Register Channel 1 */
#define R_PDMIF_PDLFCH107RCH2_OFFSET     0x00000384  /* Low-pass Filter Coefficient h1(7) Register Channel 2 */
/* PDLFCH108RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH108RCH0_OFFSET     0x00000188  /* Low-pass Filter Coefficient h1(8) Register Channel 0 */
#define R_PDMIF_PDLFCH108RCH1_OFFSET     0x00000288  /* Low-pass Filter Coefficient h1(8) Register Channel 1 */
#define R_PDMIF_PDLFCH108RCH2_OFFSET     0x00000388  /* Low-pass Filter Coefficient h1(8) Register Channel 2 */
/* PDLFCH109RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH109RCH0_OFFSET     0x0000018c  /* Low-pass Filter Coefficient h1(9) Register Channel 0 */
#define R_PDMIF_PDLFCH109RCH1_OFFSET     0x0000028c  /* Low-pass Filter Coefficient h1(9) Register Channel 1 */
#define R_PDMIF_PDLFCH109RCH2_OFFSET     0x0000038c  /* Low-pass Filter Coefficient h1(9) Register Channel 2 */
/* PDLFCH110RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH110RCH0_OFFSET     0x00000190  /* Low-pass Filter Coefficient h1(10) Register Channel 0 */
#define R_PDMIF_PDLFCH110RCH1_OFFSET     0x00000290  /* Low-pass Filter Coefficient h1(10) Register Channel 1 */
#define R_PDMIF_PDLFCH110RCH2_OFFSET     0x00000390  /* Low-pass Filter Coefficient h1(10) Register Channel 2 */
/* PDLFCH111RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH111RCH0_OFFSET     0x00000194  /* Low-pass Filter Coefficient h1(11) Register Channel 0 */
#define R_PDMIF_PDLFCH111RCH1_OFFSET     0x00000294  /* Low-pass Filter Coefficient h1(11) Register Channel 1 */
#define R_PDMIF_PDLFCH111RCH2_OFFSET     0x00000394  /* Low-pass Filter Coefficient h1(11) Register Channel 2 */
/* PDLFCH112RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH112RCH0_OFFSET     0x00000198  /* Low-pass Filter Coefficient h1(12) Register Channel 0 */
#define R_PDMIF_PDLFCH112RCH1_OFFSET     0x00000298  /* Low-pass Filter Coefficient h1(12) Register Channel 1 */
#define R_PDMIF_PDLFCH112RCH2_OFFSET     0x00000398  /* Low-pass Filter Coefficient h1(12) Register Channel 2 */
/* PDLFCH113RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH113RCH0_OFFSET     0x0000019c  /* Low-pass Filter Coefficient h1(13) Register Channel 0 */
#define R_PDMIF_PDLFCH113RCH1_OFFSET     0x0000029c  /* Low-pass Filter Coefficient h1(13) Register Channel 1 */
#define R_PDMIF_PDLFCH113RCH2_OFFSET     0x0000039c  /* Low-pass Filter Coefficient h1(13) Register Channel 2 */
/* PDLFCH114RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH114RCH0_OFFSET     0x000001a0  /* Low-pass Filter Coefficient h1(14) Register Channel 0 */
#define R_PDMIF_PDLFCH114RCH1_OFFSET     0x000002a0  /* Low-pass Filter Coefficient h1(14) Register Channel 1 */
#define R_PDMIF_PDLFCH114RCH2_OFFSET     0x000003a0  /* Low-pass Filter Coefficient h1(14) Register Channel 2 */
/* PDLFCH115RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH115RCH0_OFFSET     0x000001a4  /* Low-pass Filter Coefficient h1(15) Register Channel 0 */
#define R_PDMIF_PDLFCH115RCH1_OFFSET     0x000002a4  /* Low-pass Filter Coefficient h1(15) Register Channel 1 */
#define R_PDMIF_PDLFCH115RCH2_OFFSET     0x000003a4  /* Low-pass Filter Coefficient h1(15) Register Channel 2 */
/* PDLFCH116RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH116RCH0_OFFSET     0x000001a8  /* Low-pass Filter Coefficient h1(16) Register Channel 0 */
#define R_PDMIF_PDLFCH116RCH1_OFFSET     0x000002a8  /* Low-pass Filter Coefficient h1(16) Register Channel 1 */
#define R_PDMIF_PDLFCH116RCH2_OFFSET     0x000003a8  /* Low-pass Filter Coefficient h1(16) Register Channel 2 */
/* PDLFCH117RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH117RCH0_OFFSET     0x000001ac  /* Low-pass Filter Coefficient h1(17) Register Channel 0 */
#define R_PDMIF_PDLFCH117RCH1_OFFSET     0x000002ac  /* Low-pass Filter Coefficient h1(17) Register Channel 1 */
#define R_PDMIF_PDLFCH117RCH2_OFFSET     0x000003ac  /* Low-pass Filter Coefficient h1(17) Register Channel 2 */
/* PDLFCH118RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH118RCH0_OFFSET     0x000001b0  /* Low-pass Filter Coefficient h1(18) Register Channel 0 */
#define R_PDMIF_PDLFCH118RCH1_OFFSET     0x000002b0  /* Low-pass Filter Coefficient h1(18) Register Channel 1 */
#define R_PDMIF_PDLFCH118RCH2_OFFSET     0x000003b0  /* Low-pass Filter Coefficient h1(18) Register Channel 2 */
/* PDLFCH119RCH%s Registers (0-2) */
#define R_PDMIF_PDLFCH119RCH0_OFFSET     0x000001b4  /* Low-pass Filter Coefficient h1(19) Register Channel 0 */
#define R_PDMIF_PDLFCH119RCH1_OFFSET     0x000002b4  /* Low-pass Filter Coefficient h1(19) Register Channel 1 */
#define R_PDMIF_PDLFCH119RCH2_OFFSET     0x000003b4  /* Low-pass Filter Coefficient h1(19) Register Channel 2 */
/* PDSDLTRCH%s Registers (0-2) */
#define R_PDMIF_PDSDLTRCH0_OFFSET     0x000001b8  /* Sound Detection Lower Threshold Register Channel 0 */
#define R_PDMIF_PDSDLTRCH1_OFFSET     0x000002b8  /* Sound Detection Lower Threshold Register Channel 1 */
#define R_PDMIF_PDSDLTRCH2_OFFSET     0x000003b8  /* Sound Detection Lower Threshold Register Channel 2 */
/* PDSDUTRCH%s Registers (0-2) */
#define R_PDMIF_PDSDUTRCH0_OFFSET     0x000001bc  /* Sound Detection Upper Threshold Register Channel 0 */
#define R_PDMIF_PDSDUTRCH1_OFFSET     0x000002bc  /* Sound Detection Upper Threshold Register Channel 1 */
#define R_PDMIF_PDSDUTRCH2_OFFSET     0x000003bc  /* Sound Detection Upper Threshold Register Channel 2 */
/* PDDBCRCH%s Registers (0-2) */
#define R_PDMIF_PDDBCRCH0_OFFSET     0x000001c0  /* Data Buffer Control Register Channel 0 */
#define R_PDMIF_PDDBCRCH1_OFFSET     0x000002c0  /* Data Buffer Control Register Channel 1 */
#define R_PDMIF_PDDBCRCH2_OFFSET     0x000003c0  /* Data Buffer Control Register Channel 2 */
/* PDSCTSRCH%s Registers (0-2) */
#define R_PDMIF_PDSCTSRCH0_OFFSET     0x000001c4  /* Short Circuit Threshold Setting Register Channel 0 */
#define R_PDMIF_PDSCTSRCH1_OFFSET     0x000002c4  /* Short Circuit Threshold Setting Register Channel 1 */
#define R_PDMIF_PDSCTSRCH2_OFFSET     0x000003c4  /* Short Circuit Threshold Setting Register Channel 2 */
/* PDOVLTRCH%s Registers (0-2) */
#define R_PDMIF_PDOVLTRCH0_OFFSET     0x000001c8  /* Overvoltage Lower Threshold Register Channel 0 */
#define R_PDMIF_PDOVLTRCH1_OFFSET     0x000002c8  /* Overvoltage Lower Threshold Register Channel 1 */
#define R_PDMIF_PDOVLTRCH2_OFFSET     0x000003c8  /* Overvoltage Lower Threshold Register Channel 2 */
/* PDOVUTRCH%s Registers (0-2) */
#define R_PDMIF_PDOVUTRCH0_OFFSET     0x000001cc  /* Overvoltage Upper Threshold Register Channel 0 */
#define R_PDMIF_PDOVUTRCH1_OFFSET     0x000002cc  /* Overvoltage Upper Threshold Register Channel 1 */
#define R_PDMIF_PDOVUTRCH2_OFFSET     0x000003cc  /* Overvoltage Upper Threshold Register Channel 2 */
/* PDDRCRCH%s Registers (0-2) */
#define R_PDMIF_PDDRCRCH0_OFFSET     0x000001e0  /* Data Read Control Register Channel 0 */
#define R_PDMIF_PDDRCRCH1_OFFSET     0x000002e0  /* Data Read Control Register Channel 1 */
#define R_PDMIF_PDDRCRCH2_OFFSET     0x000003e0  /* Data Read Control Register Channel 2 */
/* PDDCRCH%s Registers (0-2) */
#define R_PDMIF_PDDCRCH0_OFFSET     0x000001e4  /* Data Clear Register Channel 0 */
#define R_PDMIF_PDDCRCH1_OFFSET     0x000002e4  /* Data Clear Register Channel 1 */
#define R_PDMIF_PDDCRCH2_OFFSET     0x000003e4  /* Data Clear Register Channel 2 */
/* PDDRRCH%s Registers (0-2) */
#define R_PDMIF_PDDRRCH0_OFFSET     0x000001e8  /* Data Read Register Channel 0 */
#define R_PDMIF_PDDRRCH1_OFFSET     0x000002e8  /* Data Read Register Channel 1 */
#define R_PDMIF_PDDRRCH2_OFFSET     0x000003e8  /* Data Read Register Channel 2 */
/* PDDSRCH%s Registers (0-2) */
#define R_PDMIF_PDDSRCH0_OFFSET     0x000001ec  /* Data Status Register Channel 0 */
#define R_PDMIF_PDDSRCH1_OFFSET     0x000002ec  /* Data Status Register Channel 1 */
#define R_PDMIF_PDDSRCH2_OFFSET     0x000003ec  /* Data Status Register Channel 2 */

/* PDMIF Register Addresses */

#define R_PDMIF_PDCSTRTR                 (R_PDMIF_BASE + R_PDMIF_PDCSTRTR_OFFSET)
#define R_PDMIF_PDCSTPTR                 (R_PDMIF_BASE + R_PDMIF_PDCSTPTR_OFFSET)
#define R_PDMIF_PDCCHGTR                 (R_PDMIF_BASE + R_PDMIF_PDCCHGTR_OFFSET)
#define R_PDMIF_PDCICR                 (R_PDMIF_BASE + R_PDMIF_PDCICR_OFFSET)
#define R_PDMIF_PDCSR                 (R_PDMIF_BASE + R_PDMIF_PDCSR_OFFSET)
#define R_PDMIF_PDCSCR                 (R_PDMIF_BASE + R_PDMIF_PDCSCR_OFFSET)
#define R_PDMIF_PDCSDCR                 (R_PDMIF_BASE + R_PDMIF_PDCSDCR_OFFSET)
#define R_PDMIF_PDCDRCR                 (R_PDMIF_BASE + R_PDMIF_PDCDRCR_OFFSET)
#define R_PDMIF_PDCDCR                 (R_PDMIF_BASE + R_PDMIF_PDCDCR_OFFSET)
#define R_PDMIF_PDVR                 (R_PDMIF_BASE + R_PDMIF_PDVR_OFFSET)
#define R_PDMIF_PDSTRTRCH0                 (R_PDMIF_BASE + R_PDMIF_PDSTRTRCH0_OFFSET)
#define R_PDMIF_PDSTRTRCH1                 (R_PDMIF_BASE + R_PDMIF_PDSTRTRCH1_OFFSET)
#define R_PDMIF_PDSTRTRCH2                 (R_PDMIF_BASE + R_PDMIF_PDSTRTRCH2_OFFSET)
#define R_PDMIF_PDSTPTRCH0                 (R_PDMIF_BASE + R_PDMIF_PDSTPTRCH0_OFFSET)
#define R_PDMIF_PDSTPTRCH1                 (R_PDMIF_BASE + R_PDMIF_PDSTPTRCH1_OFFSET)
#define R_PDMIF_PDSTPTRCH2                 (R_PDMIF_BASE + R_PDMIF_PDSTPTRCH2_OFFSET)
#define R_PDMIF_PDCHGTRCH0                 (R_PDMIF_BASE + R_PDMIF_PDCHGTRCH0_OFFSET)
#define R_PDMIF_PDCHGTRCH1                 (R_PDMIF_BASE + R_PDMIF_PDCHGTRCH1_OFFSET)
#define R_PDMIF_PDCHGTRCH2                 (R_PDMIF_BASE + R_PDMIF_PDCHGTRCH2_OFFSET)
#define R_PDMIF_PDICRCH0                 (R_PDMIF_BASE + R_PDMIF_PDICRCH0_OFFSET)
#define R_PDMIF_PDICRCH1                 (R_PDMIF_BASE + R_PDMIF_PDICRCH1_OFFSET)
#define R_PDMIF_PDICRCH2                 (R_PDMIF_BASE + R_PDMIF_PDICRCH2_OFFSET)
#define R_PDMIF_PDSDCRCH0                 (R_PDMIF_BASE + R_PDMIF_PDSDCRCH0_OFFSET)
#define R_PDMIF_PDSDCRCH1                 (R_PDMIF_BASE + R_PDMIF_PDSDCRCH1_OFFSET)
#define R_PDMIF_PDSDCRCH2                 (R_PDMIF_BASE + R_PDMIF_PDSDCRCH2_OFFSET)
#define R_PDMIF_PDSRCH0                 (R_PDMIF_BASE + R_PDMIF_PDSRCH0_OFFSET)
#define R_PDMIF_PDSRCH1                 (R_PDMIF_BASE + R_PDMIF_PDSRCH1_OFFSET)
#define R_PDMIF_PDSRCH2                 (R_PDMIF_BASE + R_PDMIF_PDSRCH2_OFFSET)
#define R_PDMIF_PDSCRCH0                 (R_PDMIF_BASE + R_PDMIF_PDSCRCH0_OFFSET)
#define R_PDMIF_PDSCRCH1                 (R_PDMIF_BASE + R_PDMIF_PDSCRCH1_OFFSET)
#define R_PDMIF_PDSCRCH2                 (R_PDMIF_BASE + R_PDMIF_PDSCRCH2_OFFSET)
#define R_PDMIF_PDMDSRCH0                 (R_PDMIF_BASE + R_PDMIF_PDMDSRCH0_OFFSET)
#define R_PDMIF_PDMDSRCH1                 (R_PDMIF_BASE + R_PDMIF_PDMDSRCH1_OFFSET)
#define R_PDMIF_PDMDSRCH2                 (R_PDMIF_BASE + R_PDMIF_PDMDSRCH2_OFFSET)
#define R_PDMIF_PDSFCRCH0                 (R_PDMIF_BASE + R_PDMIF_PDSFCRCH0_OFFSET)
#define R_PDMIF_PDSFCRCH1                 (R_PDMIF_BASE + R_PDMIF_PDSFCRCH1_OFFSET)
#define R_PDMIF_PDSFCRCH2                 (R_PDMIF_BASE + R_PDMIF_PDSFCRCH2_OFFSET)
#define R_PDMIF_PDHFCS0RCH0                 (R_PDMIF_BASE + R_PDMIF_PDHFCS0RCH0_OFFSET)
#define R_PDMIF_PDHFCS0RCH1                 (R_PDMIF_BASE + R_PDMIF_PDHFCS0RCH1_OFFSET)
#define R_PDMIF_PDHFCS0RCH2                 (R_PDMIF_BASE + R_PDMIF_PDHFCS0RCH2_OFFSET)
#define R_PDMIF_PDHFCK1RCH0                 (R_PDMIF_BASE + R_PDMIF_PDHFCK1RCH0_OFFSET)
#define R_PDMIF_PDHFCK1RCH1                 (R_PDMIF_BASE + R_PDMIF_PDHFCK1RCH1_OFFSET)
#define R_PDMIF_PDHFCK1RCH2                 (R_PDMIF_BASE + R_PDMIF_PDHFCK1RCH2_OFFSET)
#define R_PDMIF_PDHFCH0RCH0                 (R_PDMIF_BASE + R_PDMIF_PDHFCH0RCH0_OFFSET)
#define R_PDMIF_PDHFCH0RCH1                 (R_PDMIF_BASE + R_PDMIF_PDHFCH0RCH1_OFFSET)
#define R_PDMIF_PDHFCH0RCH2                 (R_PDMIF_BASE + R_PDMIF_PDHFCH0RCH2_OFFSET)
#define R_PDMIF_PDHFCH1RCH0                 (R_PDMIF_BASE + R_PDMIF_PDHFCH1RCH0_OFFSET)
#define R_PDMIF_PDHFCH1RCH1                 (R_PDMIF_BASE + R_PDMIF_PDHFCH1RCH1_OFFSET)
#define R_PDMIF_PDHFCH1RCH2                 (R_PDMIF_BASE + R_PDMIF_PDHFCH1RCH2_OFFSET)
#define R_PDMIF_PDCFCH00RCH0                 (R_PDMIF_BASE + R_PDMIF_PDCFCH00RCH0_OFFSET)
#define R_PDMIF_PDCFCH00RCH1                 (R_PDMIF_BASE + R_PDMIF_PDCFCH00RCH1_OFFSET)
#define R_PDMIF_PDCFCH00RCH2                 (R_PDMIF_BASE + R_PDMIF_PDCFCH00RCH2_OFFSET)
#define R_PDMIF_PDCFCH01RCH0                 (R_PDMIF_BASE + R_PDMIF_PDCFCH01RCH0_OFFSET)
#define R_PDMIF_PDCFCH01RCH1                 (R_PDMIF_BASE + R_PDMIF_PDCFCH01RCH1_OFFSET)
#define R_PDMIF_PDCFCH01RCH2                 (R_PDMIF_BASE + R_PDMIF_PDCFCH01RCH2_OFFSET)
#define R_PDMIF_PDCFCH02RCH0                 (R_PDMIF_BASE + R_PDMIF_PDCFCH02RCH0_OFFSET)
#define R_PDMIF_PDCFCH02RCH1                 (R_PDMIF_BASE + R_PDMIF_PDCFCH02RCH1_OFFSET)
#define R_PDMIF_PDCFCH02RCH2                 (R_PDMIF_BASE + R_PDMIF_PDCFCH02RCH2_OFFSET)
#define R_PDMIF_PDCFCH03RCH0                 (R_PDMIF_BASE + R_PDMIF_PDCFCH03RCH0_OFFSET)
#define R_PDMIF_PDCFCH03RCH1                 (R_PDMIF_BASE + R_PDMIF_PDCFCH03RCH1_OFFSET)
#define R_PDMIF_PDCFCH03RCH2                 (R_PDMIF_BASE + R_PDMIF_PDCFCH03RCH2_OFFSET)
#define R_PDMIF_PDCFCH04RCH0                 (R_PDMIF_BASE + R_PDMIF_PDCFCH04RCH0_OFFSET)
#define R_PDMIF_PDCFCH04RCH1                 (R_PDMIF_BASE + R_PDMIF_PDCFCH04RCH1_OFFSET)
#define R_PDMIF_PDCFCH04RCH2                 (R_PDMIF_BASE + R_PDMIF_PDCFCH04RCH2_OFFSET)
#define R_PDMIF_PDCFCH05RCH0                 (R_PDMIF_BASE + R_PDMIF_PDCFCH05RCH0_OFFSET)
#define R_PDMIF_PDCFCH05RCH1                 (R_PDMIF_BASE + R_PDMIF_PDCFCH05RCH1_OFFSET)
#define R_PDMIF_PDCFCH05RCH2                 (R_PDMIF_BASE + R_PDMIF_PDCFCH05RCH2_OFFSET)
#define R_PDMIF_PDCFCH06RCHN                 (R_PDMIF_BASE + R_PDMIF_PDCFCH06RCHN_OFFSET)
#define R_PDMIF_PDCFCH07RCH0                 (R_PDMIF_BASE + R_PDMIF_PDCFCH07RCH0_OFFSET)
#define R_PDMIF_PDCFCH07RCH1                 (R_PDMIF_BASE + R_PDMIF_PDCFCH07RCH1_OFFSET)
#define R_PDMIF_PDCFCH07RCH2                 (R_PDMIF_BASE + R_PDMIF_PDCFCH07RCH2_OFFSET)
#define R_PDMIF_PDCFCH08RCH0                 (R_PDMIF_BASE + R_PDMIF_PDCFCH08RCH0_OFFSET)
#define R_PDMIF_PDCFCH08RCH1                 (R_PDMIF_BASE + R_PDMIF_PDCFCH08RCH1_OFFSET)
#define R_PDMIF_PDCFCH08RCH2                 (R_PDMIF_BASE + R_PDMIF_PDCFCH08RCH2_OFFSET)
#define R_PDMIF_PDCFCH09RCH0                 (R_PDMIF_BASE + R_PDMIF_PDCFCH09RCH0_OFFSET)
#define R_PDMIF_PDCFCH09RCH1                 (R_PDMIF_BASE + R_PDMIF_PDCFCH09RCH1_OFFSET)
#define R_PDMIF_PDCFCH09RCH2                 (R_PDMIF_BASE + R_PDMIF_PDCFCH09RCH2_OFFSET)
#define R_PDMIF_PDCFCH10RCH0                 (R_PDMIF_BASE + R_PDMIF_PDCFCH10RCH0_OFFSET)
#define R_PDMIF_PDCFCH10RCH1                 (R_PDMIF_BASE + R_PDMIF_PDCFCH10RCH1_OFFSET)
#define R_PDMIF_PDCFCH10RCH2                 (R_PDMIF_BASE + R_PDMIF_PDCFCH10RCH2_OFFSET)
#define R_PDMIF_PDLFCH010RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH010RCH0_OFFSET)
#define R_PDMIF_PDLFCH010RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH010RCH1_OFFSET)
#define R_PDMIF_PDLFCH010RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH010RCH2_OFFSET)
#define R_PDMIF_PDLFCH100RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH100RCH0_OFFSET)
#define R_PDMIF_PDLFCH100RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH100RCH1_OFFSET)
#define R_PDMIF_PDLFCH100RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH100RCH2_OFFSET)
#define R_PDMIF_PDLFCH101RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH101RCH0_OFFSET)
#define R_PDMIF_PDLFCH101RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH101RCH1_OFFSET)
#define R_PDMIF_PDLFCH101RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH101RCH2_OFFSET)
#define R_PDMIF_PDLFCH102RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH102RCH0_OFFSET)
#define R_PDMIF_PDLFCH102RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH102RCH1_OFFSET)
#define R_PDMIF_PDLFCH102RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH102RCH2_OFFSET)
#define R_PDMIF_PDLFCH103RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH103RCH0_OFFSET)
#define R_PDMIF_PDLFCH103RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH103RCH1_OFFSET)
#define R_PDMIF_PDLFCH103RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH103RCH2_OFFSET)
#define R_PDMIF_PDLFCH104RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH104RCH0_OFFSET)
#define R_PDMIF_PDLFCH104RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH104RCH1_OFFSET)
#define R_PDMIF_PDLFCH104RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH104RCH2_OFFSET)
#define R_PDMIF_PDLFCH105RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH105RCH0_OFFSET)
#define R_PDMIF_PDLFCH105RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH105RCH1_OFFSET)
#define R_PDMIF_PDLFCH105RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH105RCH2_OFFSET)
#define R_PDMIF_PDLFCH106RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH106RCH0_OFFSET)
#define R_PDMIF_PDLFCH106RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH106RCH1_OFFSET)
#define R_PDMIF_PDLFCH106RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH106RCH2_OFFSET)
#define R_PDMIF_PDLFCH107RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH107RCH0_OFFSET)
#define R_PDMIF_PDLFCH107RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH107RCH1_OFFSET)
#define R_PDMIF_PDLFCH107RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH107RCH2_OFFSET)
#define R_PDMIF_PDLFCH108RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH108RCH0_OFFSET)
#define R_PDMIF_PDLFCH108RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH108RCH1_OFFSET)
#define R_PDMIF_PDLFCH108RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH108RCH2_OFFSET)
#define R_PDMIF_PDLFCH109RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH109RCH0_OFFSET)
#define R_PDMIF_PDLFCH109RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH109RCH1_OFFSET)
#define R_PDMIF_PDLFCH109RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH109RCH2_OFFSET)
#define R_PDMIF_PDLFCH110RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH110RCH0_OFFSET)
#define R_PDMIF_PDLFCH110RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH110RCH1_OFFSET)
#define R_PDMIF_PDLFCH110RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH110RCH2_OFFSET)
#define R_PDMIF_PDLFCH111RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH111RCH0_OFFSET)
#define R_PDMIF_PDLFCH111RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH111RCH1_OFFSET)
#define R_PDMIF_PDLFCH111RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH111RCH2_OFFSET)
#define R_PDMIF_PDLFCH112RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH112RCH0_OFFSET)
#define R_PDMIF_PDLFCH112RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH112RCH1_OFFSET)
#define R_PDMIF_PDLFCH112RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH112RCH2_OFFSET)
#define R_PDMIF_PDLFCH113RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH113RCH0_OFFSET)
#define R_PDMIF_PDLFCH113RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH113RCH1_OFFSET)
#define R_PDMIF_PDLFCH113RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH113RCH2_OFFSET)
#define R_PDMIF_PDLFCH114RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH114RCH0_OFFSET)
#define R_PDMIF_PDLFCH114RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH114RCH1_OFFSET)
#define R_PDMIF_PDLFCH114RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH114RCH2_OFFSET)
#define R_PDMIF_PDLFCH115RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH115RCH0_OFFSET)
#define R_PDMIF_PDLFCH115RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH115RCH1_OFFSET)
#define R_PDMIF_PDLFCH115RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH115RCH2_OFFSET)
#define R_PDMIF_PDLFCH116RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH116RCH0_OFFSET)
#define R_PDMIF_PDLFCH116RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH116RCH1_OFFSET)
#define R_PDMIF_PDLFCH116RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH116RCH2_OFFSET)
#define R_PDMIF_PDLFCH117RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH117RCH0_OFFSET)
#define R_PDMIF_PDLFCH117RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH117RCH1_OFFSET)
#define R_PDMIF_PDLFCH117RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH117RCH2_OFFSET)
#define R_PDMIF_PDLFCH118RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH118RCH0_OFFSET)
#define R_PDMIF_PDLFCH118RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH118RCH1_OFFSET)
#define R_PDMIF_PDLFCH118RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH118RCH2_OFFSET)
#define R_PDMIF_PDLFCH119RCH0                 (R_PDMIF_BASE + R_PDMIF_PDLFCH119RCH0_OFFSET)
#define R_PDMIF_PDLFCH119RCH1                 (R_PDMIF_BASE + R_PDMIF_PDLFCH119RCH1_OFFSET)
#define R_PDMIF_PDLFCH119RCH2                 (R_PDMIF_BASE + R_PDMIF_PDLFCH119RCH2_OFFSET)
#define R_PDMIF_PDSDLTRCH0                 (R_PDMIF_BASE + R_PDMIF_PDSDLTRCH0_OFFSET)
#define R_PDMIF_PDSDLTRCH1                 (R_PDMIF_BASE + R_PDMIF_PDSDLTRCH1_OFFSET)
#define R_PDMIF_PDSDLTRCH2                 (R_PDMIF_BASE + R_PDMIF_PDSDLTRCH2_OFFSET)
#define R_PDMIF_PDSDUTRCH0                 (R_PDMIF_BASE + R_PDMIF_PDSDUTRCH0_OFFSET)
#define R_PDMIF_PDSDUTRCH1                 (R_PDMIF_BASE + R_PDMIF_PDSDUTRCH1_OFFSET)
#define R_PDMIF_PDSDUTRCH2                 (R_PDMIF_BASE + R_PDMIF_PDSDUTRCH2_OFFSET)
#define R_PDMIF_PDDBCRCH0                 (R_PDMIF_BASE + R_PDMIF_PDDBCRCH0_OFFSET)
#define R_PDMIF_PDDBCRCH1                 (R_PDMIF_BASE + R_PDMIF_PDDBCRCH1_OFFSET)
#define R_PDMIF_PDDBCRCH2                 (R_PDMIF_BASE + R_PDMIF_PDDBCRCH2_OFFSET)
#define R_PDMIF_PDSCTSRCH0                 (R_PDMIF_BASE + R_PDMIF_PDSCTSRCH0_OFFSET)
#define R_PDMIF_PDSCTSRCH1                 (R_PDMIF_BASE + R_PDMIF_PDSCTSRCH1_OFFSET)
#define R_PDMIF_PDSCTSRCH2                 (R_PDMIF_BASE + R_PDMIF_PDSCTSRCH2_OFFSET)
#define R_PDMIF_PDOVLTRCH0                 (R_PDMIF_BASE + R_PDMIF_PDOVLTRCH0_OFFSET)
#define R_PDMIF_PDOVLTRCH1                 (R_PDMIF_BASE + R_PDMIF_PDOVLTRCH1_OFFSET)
#define R_PDMIF_PDOVLTRCH2                 (R_PDMIF_BASE + R_PDMIF_PDOVLTRCH2_OFFSET)
#define R_PDMIF_PDOVUTRCH0                 (R_PDMIF_BASE + R_PDMIF_PDOVUTRCH0_OFFSET)
#define R_PDMIF_PDOVUTRCH1                 (R_PDMIF_BASE + R_PDMIF_PDOVUTRCH1_OFFSET)
#define R_PDMIF_PDOVUTRCH2                 (R_PDMIF_BASE + R_PDMIF_PDOVUTRCH2_OFFSET)
#define R_PDMIF_PDDRCRCH0                 (R_PDMIF_BASE + R_PDMIF_PDDRCRCH0_OFFSET)
#define R_PDMIF_PDDRCRCH1                 (R_PDMIF_BASE + R_PDMIF_PDDRCRCH1_OFFSET)
#define R_PDMIF_PDDRCRCH2                 (R_PDMIF_BASE + R_PDMIF_PDDRCRCH2_OFFSET)
#define R_PDMIF_PDDCRCH0                 (R_PDMIF_BASE + R_PDMIF_PDDCRCH0_OFFSET)
#define R_PDMIF_PDDCRCH1                 (R_PDMIF_BASE + R_PDMIF_PDDCRCH1_OFFSET)
#define R_PDMIF_PDDCRCH2                 (R_PDMIF_BASE + R_PDMIF_PDDCRCH2_OFFSET)
#define R_PDMIF_PDDRRCH0                 (R_PDMIF_BASE + R_PDMIF_PDDRRCH0_OFFSET)
#define R_PDMIF_PDDRRCH1                 (R_PDMIF_BASE + R_PDMIF_PDDRRCH1_OFFSET)
#define R_PDMIF_PDDRRCH2                 (R_PDMIF_BASE + R_PDMIF_PDDRRCH2_OFFSET)
#define R_PDMIF_PDDSRCH0                 (R_PDMIF_BASE + R_PDMIF_PDDSRCH0_OFFSET)
#define R_PDMIF_PDDSRCH1                 (R_PDMIF_BASE + R_PDMIF_PDDSRCH1_OFFSET)
#define R_PDMIF_PDDSRCH2                 (R_PDMIF_BASE + R_PDMIF_PDDSRCH2_OFFSET)

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
#  define R_PDMIF_PDMDSRCH_DBIS_0X1                       (0 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 20-bit mode, {2{S}, [18:1]} */
#  define R_PDMIF_PDMDSRCH_DBIS_0X2                       (0 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 20-bit mode, {3{S}, [18:2]} */
#  define R_PDMIF_PDMDSRCH_DBIS_0X3                       (0 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 20-bit mode, {4{S}, [18:3]} */
#  define R_PDMIF_PDMDSRCH_DBIS_0X8                       (0 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 16-bit mode, {S,D[18:4]} */
#  define R_PDMIF_PDMDSRCH_DBIS_0X9                       (0 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 16-bit mode, {S,D[17:3]} */
#  define R_PDMIF_PDMDSRCH_DBIS_0XA                       (0 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 16-bit mode, {S,D[16:2]} */
#  define R_PDMIF_PDMDSRCH_DBIS_0XB                       (0 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 16-bit mode, {S,D[15:1]} */
#  define R_PDMIF_PDMDSRCH_DBIS_0XC                       (0 << R_PDMIF_PDMDSRCH_DBIS_SHIFT)  /* 16-bit mode, {S,D[14:0]} */

/* PDSFCRCH Register bit definitions */
#define R_PDMIF_PDSFCRCH_CKDIV_SHIFT              (0)  /* PDM_CLKn Dividend Ratio to Core Clock */
#define R_PDMIF_PDSFCRCH_CKDIV_MASK               0xf

#define R_PDMIF_PDSFCRCH_SINCDEC_SHIFT            (16)  /* Sinc Filter Decimation Ratio */
#define R_PDMIF_PDSFCRCH_SINCDEC_MASK             0xff0000

#define R_PDMIF_PDSFCRCH_SINCRNG_SHIFT            (24)  /* Sinc Filter Output Valid Range */
#define R_PDMIF_PDSFCRCH_SINCRNG_MASK             0x1f000000
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X00                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [32:14]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X01                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [31:13]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X02                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [30:12]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X03                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [29:11]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X04                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [28:10]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X05                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [27:9]} (default) */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X06                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [26:8]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X07                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [25:7]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X08                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [24:6]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X09                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [23:5]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X0A                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [22:4]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X0B                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [21:3]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X0C                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [20:2]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X0D                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [19:1]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X0E                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [18:0]} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X0F                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [17:0], 0} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X10                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [16:0], 00} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X11                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [15:0], 000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X12                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [14:0], 0000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X13                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [13:0], 00000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X14                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [12:0], 000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X15                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [11:0], 0000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X16                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [10:0], 00000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X17                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [9:0], 000000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X18                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [8:0], 0000000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X19                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [7:0], 00000000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X1A                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [6:0], 000000000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X1B                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [5:0], 0000000000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X1C                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [4:0], 00000000000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X1D                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [3:0], 000000000000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X1E                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [2:0], 0000000000000000} */
#  define R_PDMIF_PDSFCRCH_SINCRNG_0X1F                   (0 << R_PDMIF_PDSFCRCH_SINCRNG_SHIFT)  /* {S, [1:0], 00000000000000000} (prohibited) */

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

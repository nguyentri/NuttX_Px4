/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_glcdc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GLCDC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GLCDC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GLCDC Base Address */
#ifndef R_GLCDC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_GLCDC_BASE           0x40342000
#else
#define R_GLCDC_BASE           0x50342000
#endif
#endif

/* GLCDC Register Offsets */

/* GR1_CLUT0%s Registers (0-255) */
#define R_GLCDC_GR1_CLUT0_OFFSET(m)               (0x00000000 + ((m) * 0x00000004))  /* Color Palette */
/* GR1_CLUT1%s Registers (0-255) */
#define R_GLCDC_GR1_CLUT1_OFFSET(m)               (0x00000400 + ((m) * 0x00000004))  /* Color Palette */
/* GR2_CLUT0%s Registers (0-255) */
#define R_GLCDC_GR2_CLUT0_OFFSET(m)               (0x00000800 + ((m) * 0x00000004))  /* Color Palette */
/* GR2_CLUT1%s Registers (0-255) */
#define R_GLCDC_GR2_CLUT1_OFFSET(m)               (0x00000c00 + ((m) * 0x00000004))  /* Color Palette */
#define R_GLCDC_BG_EN_OFFSET                      0x00001000  /* Background Plane Setting Operation Control Register */
#define R_GLCDC_BG_PERI_OFFSET                    0x00001004  /* Background Plane Setting Free-Running Period Register */
#define R_GLCDC_BG_SYNC_OFFSET                    0x00001008  /* Background Plane Setting Synchronization Position Register */
#define R_GLCDC_BG_VSIZE_OFFSET                   0x0000100c  /* Background Plane Setting Full Image Vertical Size Register */
#define R_GLCDC_BG_HSIZE_OFFSET                   0x00001010  /* Background Plane Setting Full Image Horizontal Size Register */
#define R_GLCDC_BG_BGC_OFFSET                     0x00001014  /* Background Plane Setting Background Color Register */
#define R_GLCDC_BG_MON_OFFSET                     0x00001018  /* Background Plane Setting Status Monitor Register */
/* GR%s_VEN Registers (1-2) */
#define R_GLCDC_GR_VEN_OFFSET(m)                  (0x00001100 + ((m) * 0x00000100))  /* Graphics %s Register Update Control Register */
/* GR%s_FLMRD Registers (1-2) */
#define R_GLCDC_GR_FLMRD_OFFSET(m)                (0x00001104 + ((m) * 0x00000100))  /* Graphics %s Frame Buffer Read Control Register */
/* GR%s_FLM1 Registers (1-2) */
#define R_GLCDC_GR_FLM1_OFFSET(m)                 (0x00001108 + ((m) * 0x00000100))  /* Graphics %s Frame Buffer Control Register 1 */
/* GR%s_FLM2 Registers (1-2) */
#define R_GLCDC_GR_FLM2_OFFSET(m)                 (0x0000110c + ((m) * 0x00000100))  /* Graphics %s Frame Buffer Control Register 2 */
/* GR%s_FLM3 Registers (1-2) */
#define R_GLCDC_GR_FLM3_OFFSET(m)                 (0x00001110 + ((m) * 0x00000100))  /* Graphics %s Frame Buffer Control Register 3 */
/* GR%s_FLM5 Registers (1-2) */
#define R_GLCDC_GR_FLM5_OFFSET(m)                 (0x00001118 + ((m) * 0x00000100))  /* Graphics %s Frame Buffer Control Register 5 */
/* GR%s_FLM6 Registers (1-2) */
#define R_GLCDC_GR_FLM6_OFFSET(m)                 (0x0000111c + ((m) * 0x00000100))  /* Graphics %s Frame Buffer Control Register 6 */
/* GR%s_AB1 Registers (1-2) */
#define R_GLCDC_GR_AB1_OFFSET(m)                  (0x00001120 + ((m) * 0x00000100))  /* Graphics %s Alpha Blending Control Register 1 */
/* GR%s_AB2 Registers (1-2) */
#define R_GLCDC_GR_AB2_OFFSET(m)                  (0x00001124 + ((m) * 0x00000100))  /* Graphics %s Alpha Blending Control Register 2 */
/* GR%s_AB3 Registers (1-2) */
#define R_GLCDC_GR_AB3_OFFSET(m)                  (0x00001128 + ((m) * 0x00000100))  /* Graphics %s Alpha Blending Control Register 3 */
/* GR%s_AB4 Registers (1-2) */
#define R_GLCDC_GR_AB4_OFFSET(m)                  (0x0000112c + ((m) * 0x00000100))  /* Graphics %s Alpha Blending Control Register 4 */
/* GR%s_AB5 Registers (1-2) */
#define R_GLCDC_GR_AB5_OFFSET(m)                  (0x00001130 + ((m) * 0x00000100))  /* Graphics %s Alpha Blending Control Register 5 */
/* GR%s_AB6 Registers (1-2) */
#define R_GLCDC_GR_AB6_OFFSET(m)                  (0x00001134 + ((m) * 0x00000100))  /* Graphics %s Alpha Blending Control Register 6 */
/* GR%s_AB7 Registers (1-2) */
#define R_GLCDC_GR_AB7_OFFSET(m)                  (0x00001138 + ((m) * 0x00000100))  /* Graphics %s Alpha Blending Control Register 7 */
/* GR%s_AB8 Registers (1-2) */
#define R_GLCDC_GR_AB8_OFFSET(m)                  (0x0000113c + ((m) * 0x00000100))  /* Graphics %s Alpha Blending Control Register 8 */
/* GR%s_AB9 Registers (1-2) */
#define R_GLCDC_GR_AB9_OFFSET(m)                  (0x00001140 + ((m) * 0x00000100))  /* Graphics %s Alpha Blending Control Register 9 */
/* GR%s_BASE Registers (1-2) */
#define R_GLCDC_GR_BASE_OFFSET(m)                 (0x0000114c + ((m) * 0x00000100))  /* Graphics %s Background Color Control Register */
/* GR%s_CLUTINT Registers (1-2) */
#define R_GLCDC_GR_CLUTINT_OFFSET(m)              (0x00001150 + ((m) * 0x00000100))  /* Graphics %s CLUT Table Interrupt Control Register */
/* GR%s_MON Registers (1-2) */
#define R_GLCDC_GR_MON_OFFSET(m)                  (0x00001154 + ((m) * 0x00000100))  /* Graphics %s Status Monitor Register */
#define R_GLCDC_GAMG_LATCH_OFFSET                 0x00001300  /* Gamma G Register Update Control Register */
#define R_GLCDC_GAM_SW_OFFSET                     0x00001304  /* Gamma Correction Block Function Switch Register */
#define R_GLCDC_GAMG_LUT1_OFFSET                  0x00001308  /* Gamma G Correction Block Table Setting Register 1 */
#define R_GLCDC_GAMG_LUT2_OFFSET                  0x0000130c  /* Gamma G Correction Block Table Setting Register 2 */
#define R_GLCDC_GAMG_LUT3_OFFSET                  0x00001310  /* Gamma G Correction Block Table Setting Register 3 */
#define R_GLCDC_GAMG_LUT4_OFFSET                  0x00001314  /* Gamma G Correction Block Table Setting Register 4 */
#define R_GLCDC_GAMG_LUT5_OFFSET                  0x00001318  /* Gamma G Correction Block Table Setting Register 5 */
#define R_GLCDC_GAMG_LUT6_OFFSET                  0x0000131c  /* Gamma G Correction Block Table Setting Register 6 */
#define R_GLCDC_GAMG_LUT7_OFFSET                  0x00001320  /* Gamma G Correction Block Table Setting Register 7 */
#define R_GLCDC_GAMG_LUT8_OFFSET                  0x00001324  /* Gamma G Correction Block Table Setting Register 8 */
#define R_GLCDC_GAMG_AREA1_OFFSET                 0x00001328  /* Gamma G Correction Block Area Setting Register 1 */
#define R_GLCDC_GAMG_AREA2_OFFSET                 0x0000132c  /* Gamma G Correction Block Area Setting Register 2 */
#define R_GLCDC_GAMG_AREA3_OFFSET                 0x00001330  /* Gamma G Correction Block Area Setting Register 3 */
#define R_GLCDC_GAMG_AREA4_OFFSET                 0x00001334  /* Gamma G Correction Block Area Setting Register 4 */
#define R_GLCDC_GAMG_AREA5_OFFSET                 0x00001338  /* Gamma G Correction Block Area Setting Register 5 */
#define R_GLCDC_GAMB_LATCH_OFFSET                 0x00001340  /* Gamma B Register Update Control Register */
#define R_GLCDC_GAMB_LUT1_OFFSET                  0x00001348  /* Gamma B Correction Block Table Setting Register 1 */
#define R_GLCDC_GAMB_LUT2_OFFSET                  0x0000134c  /* Gamma B Correction Block Table Setting Register 2 */
#define R_GLCDC_GAMB_LUT3_OFFSET                  0x00001350  /* Gamma B Correction Block Table Setting Register 3 */
#define R_GLCDC_GAMB_LUT4_OFFSET                  0x00001354  /* Gamma B Correction Block Table Setting Register 4 */
#define R_GLCDC_GAMB_LUT5_OFFSET                  0x00001358  /* Gamma B Correction Block Table Setting Register 5 */
#define R_GLCDC_GAMB_LUT6_OFFSET                  0x0000135c  /* Gamma B Correction Block Table Setting Register 6 */
#define R_GLCDC_GAMB_LUT7_OFFSET                  0x00001360  /* Gamma B Correction Block Table Setting Register 7 */
#define R_GLCDC_GAMB_LUT8_OFFSET                  0x00001364  /* Gamma B Correction Block Table Setting Register 8 */
#define R_GLCDC_GAMB_AREA1_OFFSET                 0x00001368  /* Gamma B Correction Block Area Setting Register 1 */
#define R_GLCDC_GAMB_AREA2_OFFSET                 0x0000136c  /* Gamma B Correction Block Area Setting Register 2 */
#define R_GLCDC_GAMB_AREA3_OFFSET                 0x00001370  /* Gamma B Correction Block Area Setting Register 3 */
#define R_GLCDC_GAMB_AREA4_OFFSET                 0x00001374  /* Gamma B Correction Block Area Setting Register 4 */
#define R_GLCDC_GAMB_AREA5_OFFSET                 0x00001378  /* Gamma B Correction Block Area Setting Register 5 */
#define R_GLCDC_GAMR_LATCH_OFFSET                 0x00001380  /* Gamma R Register Update Control Register */
#define R_GLCDC_GAMR_LUT1_OFFSET                  0x00001388  /* Gamma R Correction Block Table Setting Register 1 */
#define R_GLCDC_GAMR_LUT2_OFFSET                  0x0000138c  /* Gamma R Correction Block Table Setting Register 2 */
#define R_GLCDC_GAMR_LUT3_OFFSET                  0x00001390  /* Gamma R Correction Block Table Setting Register 3 */
#define R_GLCDC_GAMR_LUT4_OFFSET                  0x00001394  /* Gamma R Correction Block Table Setting Register 4 */
#define R_GLCDC_GAMR_LUT5_OFFSET                  0x00001398  /* Gamma R Correction Block Table Setting Register 5 */
#define R_GLCDC_GAMR_LUT6_OFFSET                  0x0000139c  /* Gamma R Correction Block Table Setting Register 6 */
#define R_GLCDC_GAMR_LUT7_OFFSET                  0x000013a0  /* Gamma R Correction Block Table Setting Register 7 */
#define R_GLCDC_GAMR_LUT8_OFFSET                  0x000013a4  /* Gamma R Correction Block Table Setting Register 8 */
#define R_GLCDC_GAMR_AREA1_OFFSET                 0x000013a8  /* Gamma R Correction Block Area Setting Register 1 */
#define R_GLCDC_GAMR_AREA2_OFFSET                 0x000013ac  /* Gamma R Correction Block Area Setting Register 2 */
#define R_GLCDC_GAMR_AREA3_OFFSET                 0x000013b0  /* Gamma R Correction Block Area Setting Register 3 */
#define R_GLCDC_GAMR_AREA4_OFFSET                 0x000013b4  /* Gamma R Correction Block Area Setting Register 4 */
#define R_GLCDC_GAMR_AREA5_OFFSET                 0x000013b8  /* Gamma R Correction Block Area Setting Register 5 */
#define R_GLCDC_OUT_VLATCH_OFFSET                 0x000013c0  /* Output Control Block Register Update Control Register */
#define R_GLCDC_OUT_SET_OFFSET                    0x000013c4  /* Output Control Block Output Interface Register */
#define R_GLCDC_OUT_BRIGHT1_OFFSET                0x000013c8  /* Output Control Block Brightness Correction Register 1 */
#define R_GLCDC_OUT_BRIGHT2_OFFSET                0x000013cc  /* Output Control Block Brightness Correction Register 2 */
#define R_GLCDC_OUT_CONTRAST_OFFSET               0x000013d0  /* Output Control Block Contrast Correction Register */
#define R_GLCDC_OUT_PDTHA_OFFSET                  0x000013d4  /* Output Control Block Panel Dither Correction Register */
#define R_GLCDC_OUT_CLKPHASE_OFFSET               0x000013e4  /* Output Control Block Output Phase Control Register */
#define R_GLCDC_TCON_TIM_OFFSET                   0x00001404  /* TCON Reference Timing Setting Register */
#define R_GLCDC_TCON_STVA1_OFFSET                 0x00001408  /* TCON Vertical Timing Setting Register x1 */
#define R_GLCDC_TCON_STVA2_OFFSET                 0x0000140c  /* TCON Vertical Timing Setting Register x2 */
#define R_GLCDC_TCON_STVB1_OFFSET                 0x00001410  /* TCON Vertical Timing Setting Register x1 */
#define R_GLCDC_TCON_STVB2_OFFSET                 0x00001414  /* TCON Vertical Timing Setting Register x2 */
#define R_GLCDC_TCON_STHA1_OFFSET                 0x00001418  /* TCON Horizontal Timing Setting Register x1 */
#define R_GLCDC_TCON_STHA2_OFFSET                 0x0000141c  /* TCON Horizontal Timing Setting Register x2 */
#define R_GLCDC_TCON_STHB1_OFFSET                 0x00001420  /* TCON Horizontal Timing Setting Register x1 */
#define R_GLCDC_TCON_STHB2_OFFSET                 0x00001424  /* TCON Horizontal Timing Setting Register x2 */
#define R_GLCDC_TCON_DE_OFFSET                    0x00001428  /* TCON Data Enable Polarity Setting Register */
#define R_GLCDC_SYSCNT_DTCTEN_OFFSET              0x00001440  /* System Control Block State Detection Control Register */
#define R_GLCDC_SYSCNT_INTEN_OFFSET               0x00001444  /* System Control Block Interrupt Request Enable Control Register */
#define R_GLCDC_SYSCNT_STCLR_OFFSET               0x00001448  /* System Control Block Status Clear Register */
#define R_GLCDC_SYSCNT_STMON_OFFSET               0x0000144c  /* System Control Block Status Monitor Register */
#define R_GLCDC_SYSCNT_PANEL_CLK_OFFSET           0x00001450  /* System Control Block Version and Panel Clock Control Register */

/* GLCDC Register Addresses */

#define R_GLCDC_GR1_CLUT0(m)                      (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0_OFFSET(m))
#define R_GLCDC_GR1_CLUT1(m)                      (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1_OFFSET(m))
#define R_GLCDC_GR2_CLUT0(m)                      (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0_OFFSET(m))
#define R_GLCDC_GR2_CLUT1(m)                      (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1_OFFSET(m))
#define R_GLCDC_BG_EN                             (R_GLCDC_BASE + R_GLCDC_BG_EN_OFFSET)
#define R_GLCDC_BG_PERI                           (R_GLCDC_BASE + R_GLCDC_BG_PERI_OFFSET)
#define R_GLCDC_BG_SYNC                           (R_GLCDC_BASE + R_GLCDC_BG_SYNC_OFFSET)
#define R_GLCDC_BG_VSIZE                          (R_GLCDC_BASE + R_GLCDC_BG_VSIZE_OFFSET)
#define R_GLCDC_BG_HSIZE                          (R_GLCDC_BASE + R_GLCDC_BG_HSIZE_OFFSET)
#define R_GLCDC_BG_BGC                            (R_GLCDC_BASE + R_GLCDC_BG_BGC_OFFSET)
#define R_GLCDC_BG_MON                            (R_GLCDC_BASE + R_GLCDC_BG_MON_OFFSET)
#define R_GLCDC_GR_VEN(m)                         (R_GLCDC_BASE + R_GLCDC_GR_VEN_OFFSET(m))
#define R_GLCDC_GR_FLMRD(m)                       (R_GLCDC_BASE + R_GLCDC_GR_FLMRD_OFFSET(m))
#define R_GLCDC_GR_FLM1(m)                        (R_GLCDC_BASE + R_GLCDC_GR_FLM1_OFFSET(m))
#define R_GLCDC_GR_FLM2(m)                        (R_GLCDC_BASE + R_GLCDC_GR_FLM2_OFFSET(m))
#define R_GLCDC_GR_FLM3(m)                        (R_GLCDC_BASE + R_GLCDC_GR_FLM3_OFFSET(m))
#define R_GLCDC_GR_FLM5(m)                        (R_GLCDC_BASE + R_GLCDC_GR_FLM5_OFFSET(m))
#define R_GLCDC_GR_FLM6(m)                        (R_GLCDC_BASE + R_GLCDC_GR_FLM6_OFFSET(m))
#define R_GLCDC_GR_AB1(m)                         (R_GLCDC_BASE + R_GLCDC_GR_AB1_OFFSET(m))
#define R_GLCDC_GR_AB2(m)                         (R_GLCDC_BASE + R_GLCDC_GR_AB2_OFFSET(m))
#define R_GLCDC_GR_AB3(m)                         (R_GLCDC_BASE + R_GLCDC_GR_AB3_OFFSET(m))
#define R_GLCDC_GR_AB4(m)                         (R_GLCDC_BASE + R_GLCDC_GR_AB4_OFFSET(m))
#define R_GLCDC_GR_AB5(m)                         (R_GLCDC_BASE + R_GLCDC_GR_AB5_OFFSET(m))
#define R_GLCDC_GR_AB6(m)                         (R_GLCDC_BASE + R_GLCDC_GR_AB6_OFFSET(m))
#define R_GLCDC_GR_AB7(m)                         (R_GLCDC_BASE + R_GLCDC_GR_AB7_OFFSET(m))
#define R_GLCDC_GR_AB8(m)                         (R_GLCDC_BASE + R_GLCDC_GR_AB8_OFFSET(m))
#define R_GLCDC_GR_AB9(m)                         (R_GLCDC_BASE + R_GLCDC_GR_AB9_OFFSET(m))
#define R_GLCDC_GR_BASE(m)                        (R_GLCDC_BASE + R_GLCDC_GR_BASE_OFFSET(m))
#define R_GLCDC_GR_CLUTINT(m)                     (R_GLCDC_BASE + R_GLCDC_GR_CLUTINT_OFFSET(m))
#define R_GLCDC_GR_MON(m)                         (R_GLCDC_BASE + R_GLCDC_GR_MON_OFFSET(m))
#define R_GLCDC_GAMG_LATCH                        (R_GLCDC_BASE + R_GLCDC_GAMG_LATCH_OFFSET)
#define R_GLCDC_GAM_SW                            (R_GLCDC_BASE + R_GLCDC_GAM_SW_OFFSET)
#define R_GLCDC_GAMG_LUT1                         (R_GLCDC_BASE + R_GLCDC_GAMG_LUT1_OFFSET)
#define R_GLCDC_GAMG_LUT2                         (R_GLCDC_BASE + R_GLCDC_GAMG_LUT2_OFFSET)
#define R_GLCDC_GAMG_LUT3                         (R_GLCDC_BASE + R_GLCDC_GAMG_LUT3_OFFSET)
#define R_GLCDC_GAMG_LUT4                         (R_GLCDC_BASE + R_GLCDC_GAMG_LUT4_OFFSET)
#define R_GLCDC_GAMG_LUT5                         (R_GLCDC_BASE + R_GLCDC_GAMG_LUT5_OFFSET)
#define R_GLCDC_GAMG_LUT6                         (R_GLCDC_BASE + R_GLCDC_GAMG_LUT6_OFFSET)
#define R_GLCDC_GAMG_LUT7                         (R_GLCDC_BASE + R_GLCDC_GAMG_LUT7_OFFSET)
#define R_GLCDC_GAMG_LUT8                         (R_GLCDC_BASE + R_GLCDC_GAMG_LUT8_OFFSET)
#define R_GLCDC_GAMG_AREA1                        (R_GLCDC_BASE + R_GLCDC_GAMG_AREA1_OFFSET)
#define R_GLCDC_GAMG_AREA2                        (R_GLCDC_BASE + R_GLCDC_GAMG_AREA2_OFFSET)
#define R_GLCDC_GAMG_AREA3                        (R_GLCDC_BASE + R_GLCDC_GAMG_AREA3_OFFSET)
#define R_GLCDC_GAMG_AREA4                        (R_GLCDC_BASE + R_GLCDC_GAMG_AREA4_OFFSET)
#define R_GLCDC_GAMG_AREA5                        (R_GLCDC_BASE + R_GLCDC_GAMG_AREA5_OFFSET)
#define R_GLCDC_GAMB_LATCH                        (R_GLCDC_BASE + R_GLCDC_GAMB_LATCH_OFFSET)
#define R_GLCDC_GAMB_LUT1                         (R_GLCDC_BASE + R_GLCDC_GAMB_LUT1_OFFSET)
#define R_GLCDC_GAMB_LUT2                         (R_GLCDC_BASE + R_GLCDC_GAMB_LUT2_OFFSET)
#define R_GLCDC_GAMB_LUT3                         (R_GLCDC_BASE + R_GLCDC_GAMB_LUT3_OFFSET)
#define R_GLCDC_GAMB_LUT4                         (R_GLCDC_BASE + R_GLCDC_GAMB_LUT4_OFFSET)
#define R_GLCDC_GAMB_LUT5                         (R_GLCDC_BASE + R_GLCDC_GAMB_LUT5_OFFSET)
#define R_GLCDC_GAMB_LUT6                         (R_GLCDC_BASE + R_GLCDC_GAMB_LUT6_OFFSET)
#define R_GLCDC_GAMB_LUT7                         (R_GLCDC_BASE + R_GLCDC_GAMB_LUT7_OFFSET)
#define R_GLCDC_GAMB_LUT8                         (R_GLCDC_BASE + R_GLCDC_GAMB_LUT8_OFFSET)
#define R_GLCDC_GAMB_AREA1                        (R_GLCDC_BASE + R_GLCDC_GAMB_AREA1_OFFSET)
#define R_GLCDC_GAMB_AREA2                        (R_GLCDC_BASE + R_GLCDC_GAMB_AREA2_OFFSET)
#define R_GLCDC_GAMB_AREA3                        (R_GLCDC_BASE + R_GLCDC_GAMB_AREA3_OFFSET)
#define R_GLCDC_GAMB_AREA4                        (R_GLCDC_BASE + R_GLCDC_GAMB_AREA4_OFFSET)
#define R_GLCDC_GAMB_AREA5                        (R_GLCDC_BASE + R_GLCDC_GAMB_AREA5_OFFSET)
#define R_GLCDC_GAMR_LATCH                        (R_GLCDC_BASE + R_GLCDC_GAMR_LATCH_OFFSET)
#define R_GLCDC_GAMR_LUT1                         (R_GLCDC_BASE + R_GLCDC_GAMR_LUT1_OFFSET)
#define R_GLCDC_GAMR_LUT2                         (R_GLCDC_BASE + R_GLCDC_GAMR_LUT2_OFFSET)
#define R_GLCDC_GAMR_LUT3                         (R_GLCDC_BASE + R_GLCDC_GAMR_LUT3_OFFSET)
#define R_GLCDC_GAMR_LUT4                         (R_GLCDC_BASE + R_GLCDC_GAMR_LUT4_OFFSET)
#define R_GLCDC_GAMR_LUT5                         (R_GLCDC_BASE + R_GLCDC_GAMR_LUT5_OFFSET)
#define R_GLCDC_GAMR_LUT6                         (R_GLCDC_BASE + R_GLCDC_GAMR_LUT6_OFFSET)
#define R_GLCDC_GAMR_LUT7                         (R_GLCDC_BASE + R_GLCDC_GAMR_LUT7_OFFSET)
#define R_GLCDC_GAMR_LUT8                         (R_GLCDC_BASE + R_GLCDC_GAMR_LUT8_OFFSET)
#define R_GLCDC_GAMR_AREA1                        (R_GLCDC_BASE + R_GLCDC_GAMR_AREA1_OFFSET)
#define R_GLCDC_GAMR_AREA2                        (R_GLCDC_BASE + R_GLCDC_GAMR_AREA2_OFFSET)
#define R_GLCDC_GAMR_AREA3                        (R_GLCDC_BASE + R_GLCDC_GAMR_AREA3_OFFSET)
#define R_GLCDC_GAMR_AREA4                        (R_GLCDC_BASE + R_GLCDC_GAMR_AREA4_OFFSET)
#define R_GLCDC_GAMR_AREA5                        (R_GLCDC_BASE + R_GLCDC_GAMR_AREA5_OFFSET)
#define R_GLCDC_OUT_VLATCH                        (R_GLCDC_BASE + R_GLCDC_OUT_VLATCH_OFFSET)
#define R_GLCDC_OUT_SET                           (R_GLCDC_BASE + R_GLCDC_OUT_SET_OFFSET)
#define R_GLCDC_OUT_BRIGHT1                       (R_GLCDC_BASE + R_GLCDC_OUT_BRIGHT1_OFFSET)
#define R_GLCDC_OUT_BRIGHT2                       (R_GLCDC_BASE + R_GLCDC_OUT_BRIGHT2_OFFSET)
#define R_GLCDC_OUT_CONTRAST                      (R_GLCDC_BASE + R_GLCDC_OUT_CONTRAST_OFFSET)
#define R_GLCDC_OUT_PDTHA                         (R_GLCDC_BASE + R_GLCDC_OUT_PDTHA_OFFSET)
#define R_GLCDC_OUT_CLKPHASE                      (R_GLCDC_BASE + R_GLCDC_OUT_CLKPHASE_OFFSET)
#define R_GLCDC_TCON_TIM                          (R_GLCDC_BASE + R_GLCDC_TCON_TIM_OFFSET)
#define R_GLCDC_TCON_STVA1                        (R_GLCDC_BASE + R_GLCDC_TCON_STVA1_OFFSET)
#define R_GLCDC_TCON_STVA2                        (R_GLCDC_BASE + R_GLCDC_TCON_STVA2_OFFSET)
#define R_GLCDC_TCON_STVB1                        (R_GLCDC_BASE + R_GLCDC_TCON_STVB1_OFFSET)
#define R_GLCDC_TCON_STVB2                        (R_GLCDC_BASE + R_GLCDC_TCON_STVB2_OFFSET)
#define R_GLCDC_TCON_STHA1                        (R_GLCDC_BASE + R_GLCDC_TCON_STHA1_OFFSET)
#define R_GLCDC_TCON_STHA2                        (R_GLCDC_BASE + R_GLCDC_TCON_STHA2_OFFSET)
#define R_GLCDC_TCON_STHB1                        (R_GLCDC_BASE + R_GLCDC_TCON_STHB1_OFFSET)
#define R_GLCDC_TCON_STHB2                        (R_GLCDC_BASE + R_GLCDC_TCON_STHB2_OFFSET)
#define R_GLCDC_TCON_DE                           (R_GLCDC_BASE + R_GLCDC_TCON_DE_OFFSET)
#define R_GLCDC_SYSCNT_DTCTEN                     (R_GLCDC_BASE + R_GLCDC_SYSCNT_DTCTEN_OFFSET)
#define R_GLCDC_SYSCNT_INTEN                      (R_GLCDC_BASE + R_GLCDC_SYSCNT_INTEN_OFFSET)
#define R_GLCDC_SYSCNT_STCLR                      (R_GLCDC_BASE + R_GLCDC_SYSCNT_STCLR_OFFSET)
#define R_GLCDC_SYSCNT_STMON                      (R_GLCDC_BASE + R_GLCDC_SYSCNT_STMON_OFFSET)
#define R_GLCDC_SYSCNT_PANEL_CLK                  (R_GLCDC_BASE + R_GLCDC_SYSCNT_PANEL_CLK_OFFSET)

/* Register bit definitions */
/* GR1_CLUT Register bit definitions */
#define R_GLCDC_GR1_CLUT_B_SHIFT                  (0)  /* B value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR1_CLUT_B_MASK                   0xff

#define R_GLCDC_GR1_CLUT_G_SHIFT                  (8)  /* G value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR1_CLUT_G_MASK                   0xff00

#define R_GLCDC_GR1_CLUT_R_SHIFT                  (16)  /* R value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR1_CLUT_R_MASK                   0xff0000

#define R_GLCDC_GR1_CLUT_A_SHIFT                  (24)  /* Alpha blending value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR1_CLUT_A_MASK                   0xff000000

/* GR1_CLUT Register bit definitions */
#define R_GLCDC_GR1_CLUT_B_SHIFT                  (0)  /* B value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR1_CLUT_B_MASK                   0xff

#define R_GLCDC_GR1_CLUT_G_SHIFT                  (8)  /* G value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR1_CLUT_G_MASK                   0xff00

#define R_GLCDC_GR1_CLUT_R_SHIFT                  (16)  /* R value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR1_CLUT_R_MASK                   0xff0000

#define R_GLCDC_GR1_CLUT_A_SHIFT                  (24)  /* Alpha blending value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR1_CLUT_A_MASK                   0xff000000

/* GR2_CLUT Register bit definitions */
#define R_GLCDC_GR2_CLUT_B_SHIFT                  (0)  /* B value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR2_CLUT_B_MASK                   0xff

#define R_GLCDC_GR2_CLUT_G_SHIFT                  (8)  /* G value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR2_CLUT_G_MASK                   0xff00

#define R_GLCDC_GR2_CLUT_R_SHIFT                  (16)  /* R value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR2_CLUT_R_MASK                   0xff0000

#define R_GLCDC_GR2_CLUT_A_SHIFT                  (24)  /* Alpha blending value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR2_CLUT_A_MASK                   0xff000000

/* GR2_CLUT Register bit definitions */
#define R_GLCDC_GR2_CLUT_B_SHIFT                  (0)  /* B value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR2_CLUT_B_MASK                   0xff

#define R_GLCDC_GR2_CLUT_G_SHIFT                  (8)  /* G value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR2_CLUT_G_MASK                   0xff00

#define R_GLCDC_GR2_CLUT_R_SHIFT                  (16)  /* R value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR2_CLUT_R_MASK                   0xff0000

#define R_GLCDC_GR2_CLUT_A_SHIFT                  (24)  /* Alpha blending value of color palette n plane for graphics m plane. Unsigned 8-bit integer. */
#define R_GLCDC_GR2_CLUT_A_MASK                   0xff000000

/* BG_EN Register bit definitions */
#define R_GLCDC_BG_EN_EN                          (1 << 0)  /* Background Plane Operation Enable */

#define R_GLCDC_BG_EN_VEN                         (1 << 8)  /* Control of GLCDC Internal Register Value Reflection to Internal Operations */

#define R_GLCDC_BG_EN_SWRST                       (1 << 16)  /* Software Reset Control */

/* BG_PERI Register bit definitions */
#define R_GLCDC_BG_PERI_FH_SHIFT                  (0)  /* Background Plane Horizontal Synchronization Signal Period */
#define R_GLCDC_BG_PERI_FH_MASK                   0x7ff
#  define R_GLCDC_BG_PERI_FH_0X017                        (23 << R_GLCDC_BG_PERI_FH_SHIFT)  /* 24 cycles (pixels) */
#  define R_GLCDC_BG_PERI_FH_0X3FF                        (1023 << R_GLCDC_BG_PERI_FH_SHIFT)  /* 1024 cycles (pixels) */
#  define R_GLCDC_BG_PERI_FH_0X7FF                        (2047 << R_GLCDC_BG_PERI_FH_SHIFT)  /* 2048 cycles (pixels) */

#define R_GLCDC_BG_PERI_FV_SHIFT                  (16)  /* Background Plane Vertical Synchronization Signal Period */
#define R_GLCDC_BG_PERI_FV_MASK                   0x7ff0000
#  define R_GLCDC_BG_PERI_FV_0X013                        (19 << R_GLCDC_BG_PERI_FV_SHIFT)  /* 20 lines */
#  define R_GLCDC_BG_PERI_FV_0X3FF                        (1023 << R_GLCDC_BG_PERI_FV_SHIFT)  /* 1024 lines */
#  define R_GLCDC_BG_PERI_FV_0X7FF                        (2047 << R_GLCDC_BG_PERI_FV_SHIFT)  /* 2048 lines */

/* BG_SYNC Register bit definitions */
#define R_GLCDC_BG_SYNC_HP_SHIFT                  (0)  /* Background Plane Horizontal Synchronization Signal Assertion Position */
#define R_GLCDC_BG_SYNC_HP_MASK                   0xf
#  define R_GLCDC_BG_SYNC_HP_0X0                          (0 << R_GLCDC_BG_SYNC_HP_SHIFT)  /* Setting prohibited */

#define R_GLCDC_BG_SYNC_VP_SHIFT                  (16)  /* Background Plane Vertical Synchronization Assertion Position */
#define R_GLCDC_BG_SYNC_VP_MASK                   0xf0000
#  define R_GLCDC_BG_SYNC_VP_0X0                          (0 << R_GLCDC_BG_SYNC_VP_SHIFT)  /* Setting prohibited */

/* BG_VSIZE Register bit definitions */
#define R_GLCDC_BG_VSIZE_VW_SHIFT                 (0)  /* Background Plane Vertical Valid Pixel Width */
#define R_GLCDC_BG_VSIZE_VW_MASK                  0x7ff

#define R_GLCDC_BG_VSIZE_VP_SHIFT                 (16)  /* Background Plane Vertical Valid Pixel Start Position */
#define R_GLCDC_BG_VSIZE_VP_MASK                  0x7ff0000

/* BG_HSIZE Register bit definitions */
#define R_GLCDC_BG_HSIZE_HW_SHIFT                 (0)  /* Background Plane Horizontal Valid Pixel Width */
#define R_GLCDC_BG_HSIZE_HW_MASK                  0x7ff

#define R_GLCDC_BG_HSIZE_HP_SHIFT                 (16)  /* Background Plane Horizontal Valid Pixel Start Position */
#define R_GLCDC_BG_HSIZE_HP_MASK                  0x7ff0000

/* BG_BGC Register bit definitions */
#define R_GLCDC_BG_BGC_B_SHIFT                    (0)  /* Background Plane Valid Pixel Area B Value */
#define R_GLCDC_BG_BGC_B_MASK                     0xff

#define R_GLCDC_BG_BGC_G_SHIFT                    (8)  /* Background Plane Valid Pixel Area G Value */
#define R_GLCDC_BG_BGC_G_MASK                     0xff00

#define R_GLCDC_BG_BGC_R_SHIFT                    (16)  /* Background Plane Valid Pixel Area R Value */
#define R_GLCDC_BG_BGC_R_MASK                     0xff0000

/* BG_MON Register bit definitions */
#define R_GLCDC_BG_MON_EN                         (1 << 0)  /* Background Plane Operation Monitor */

#define R_GLCDC_BG_MON_VEN                        (1 << 8)  /* Entire Module Internal Operation Reflection Control Signal Monitor */

#define R_GLCDC_BG_MON_SWRST                      (1 << 16)  /* Entire Module SW Reset State Monitor */

/* GR_VEN Register bit definitions */
#define R_GLCDC_GR_VEN_PVEN                       (1 << 0)  /* This bit is cleared to 0 by an internal source. */

/* GR_FLMRD Register bit definitions */
#define R_GLCDC_GR_FLMRD_RENB                     (1 << 0)  /* Graphics Data Read Enable */

/* GR_FLM Register bit definitions */
#define R_GLCDC_GR_FLM_BSTMD_SHIFT                (0)  /* Burst Transfer Control for Graphics Data Access */
#define R_GLCDC_GR_FLM_BSTMD_MASK                 0x3
#  define R_GLCDC_GR_FLM_BSTMD_11                         (3 << R_GLCDC_GR_FLM_BSTMD_SHIFT)  /* 16-beat increment burst transfer (64-byte boundary) */

/* GR_FLM Register bit definitions */
#define R_GLCDC_GR_FLM_BASE_SHIFT                 (0)  /* Base Address for Accessing Graphics Data */
#define R_GLCDC_GR_FLM_BASE_MASK                  0xffffffff

/* GR_FLM Register bit definitions */
#define R_GLCDC_GR_FLM_LNOFF_SHIFT                (16)  /* Macro Line Offset Address for Accessing Graphics Data */
#define R_GLCDC_GR_FLM_LNOFF_MASK                 0xffff0000

/* GR_FLM Register bit definitions */
#define R_GLCDC_GR_FLM_DATANUM_SHIFT              (0)  /* Number of Data Transfer Times Per Line for Accessing Graphics Data */
#define R_GLCDC_GR_FLM_DATANUM_MASK               0xffff

#define R_GLCDC_GR_FLM_LNNUM_SHIFT                (16)  /* Number of Lines Per Frame for Accessing Graphics Data */
#define R_GLCDC_GR_FLM_LNNUM_MASK                 0x7ff0000

/* GR_FLM Register bit definitions */
#define R_GLCDC_GR_FLM_FORMAT_SHIFT               (28)  /* Data Format for Accessing Graphics Data */
#define R_GLCDC_GR_FLM_FORMAT_MASK                0x70000000
#  define R_GLCDC_GR_FLM_FORMAT_000                       (0 << R_GLCDC_GR_FLM_FORMAT_SHIFT)  /* RGB565 (16 bits/pixel) */
#  define R_GLCDC_GR_FLM_FORMAT_001                       (1 << R_GLCDC_GR_FLM_FORMAT_SHIFT)  /* RGB888 (32 bits/pixel, 8 bits on the MSB side are invalid) */
#  define R_GLCDC_GR_FLM_FORMAT_010                       (2 << R_GLCDC_GR_FLM_FORMAT_SHIFT)  /* ARGB1555 (16 bits/pixel, 1 bit of A is LUT data) */
#  define R_GLCDC_GR_FLM_FORMAT_011                       (3 << R_GLCDC_GR_FLM_FORMAT_SHIFT)  /* ARGB4444 (16 bits/pixel) */
#  define R_GLCDC_GR_FLM_FORMAT_100                       (4 << R_GLCDC_GR_FLM_FORMAT_SHIFT)  /* ARGB8888 (32 bits/pixel) */
#  define R_GLCDC_GR_FLM_FORMAT_101                       (5 << R_GLCDC_GR_FLM_FORMAT_SHIFT)  /* CLUT8 (8 bits/pixel) */
#  define R_GLCDC_GR_FLM_FORMAT_110                       (6 << R_GLCDC_GR_FLM_FORMAT_SHIFT)  /* CLUT4 (4 bits/pixel) */
#  define R_GLCDC_GR_FLM_FORMAT_111                       (7 << R_GLCDC_GR_FLM_FORMAT_SHIFT)  /* CLUT1 (1 bit/pixel) */

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_DISPSEL_SHIFT               (0)  /* Graphics Display Plane Control */
#define R_GLCDC_GR_AB_DISPSEL_MASK                0x3
#  define R_GLCDC_GR_AB_DISPSEL_00                        (0 << R_GLCDC_GR_AB_DISPSEL_SHIFT)  /* Background color display (value set in the GRn_BASE register) */
#  define R_GLCDC_GR_AB_DISPSEL_01                        (1 << R_GLCDC_GR_AB_DISPSEL_SHIFT)  /* Lower-layer graphics display */
#  define R_GLCDC_GR_AB_DISPSEL_10                        (2 << R_GLCDC_GR_AB_DISPSEL_SHIFT)  /* Current graphics display */
#  define R_GLCDC_GR_AB_DISPSEL_11                        (3 << R_GLCDC_GR_AB_DISPSEL_SHIFT)  /* Blended display of lower-layer graphics (input image from the previous stage) and current graphics (data read from the GLCDC0 and GLCDC1 bus) */

#define R_GLCDC_GR_AB_GRCDISPON                   (1 << 4)  /* Graphics Image Area Border Display Control */

#define R_GLCDC_GR_AB_ARCDISPON                   (1 << 8)  /* Image Area Border Display Control for Rectangular Area Alpha Blending */

#define R_GLCDC_GR_AB_ARCON                       (1 << 12)  /* Rectangular Area Alpha Blending Control */

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_GRCVW_SHIFT                 (0)  /* Vertical Width of Graphics Image Area */
#define R_GLCDC_GR_AB_GRCVW_MASK                  0x7ff

#define R_GLCDC_GR_AB_GRCVS_SHIFT                 (16)  /* Vertical Start Position of Graphics Image Area */
#define R_GLCDC_GR_AB_GRCVS_MASK                  0x7ff0000

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_GRCHW_SHIFT                 (0)  /* Horizontal Width of Graphics Image Area */
#define R_GLCDC_GR_AB_GRCHW_MASK                  0x7ff

#define R_GLCDC_GR_AB_GRCHS_SHIFT                 (16)  /* Horizontal Start Position of Graphics Image Area */
#define R_GLCDC_GR_AB_GRCHS_MASK                  0x7ff0000

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_ARCVW_SHIFT                 (0)  /* Vertical Width of Rectangular Area Alpha Blending Image Area */
#define R_GLCDC_GR_AB_ARCVW_MASK                  0x7ff

#define R_GLCDC_GR_AB_ARCVS_SHIFT                 (16)  /* Vertical Start Position of Rectangular Area Alpha Blending Image Area */
#define R_GLCDC_GR_AB_ARCVS_MASK                  0x7ff0000

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_ARCHW_SHIFT                 (0)  /* Horizontal Width of Rectangular Area Alpha Blending Image Area */
#define R_GLCDC_GR_AB_ARCHW_MASK                  0x7ff

#define R_GLCDC_GR_AB_ARCHS_SHIFT                 (16)  /* Horizontal Start Position of Rectangular Area Alpha Blending Image Area */
#define R_GLCDC_GR_AB_ARCHS_MASK                  0x7ff0000

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_ARCRATE_SHIFT               (0)  /* Frame Rate for Alpha Blending in Rectangular Area */
#define R_GLCDC_GR_AB_ARCRATE_MASK                0xff

#define R_GLCDC_GR_AB_ARCCOEF_SHIFT               (16)  /* Alpha Coefficient for Alpha Blending in Rectangular Area */
#define R_GLCDC_GR_AB_ARCCOEF_MASK                0x1ff0000

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_CKON                        (1 << 0)  /* RGB-Index Chroma-Key Processing Control */

#define R_GLCDC_GR_AB_ARCDEF_SHIFT                (16)  /* Initial Alpha Value for Alpha Blending in Rectangular Area */
#define R_GLCDC_GR_AB_ARCDEF_MASK                 0xff0000

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_CKKR_SHIFT                  (0)  /* R Signal for RGB-Index Chroma-Key Processing */
#define R_GLCDC_GR_AB_CKKR_MASK                   0xff

#define R_GLCDC_GR_AB_CKKB_SHIFT                  (8)  /* B Signal for RGB-Index Chroma-Key Processing */
#define R_GLCDC_GR_AB_CKKB_MASK                   0xff00

#define R_GLCDC_GR_AB_CKKG_SHIFT                  (16)  /* G Signal for RGB-Index Chroma-Key Processing */
#define R_GLCDC_GR_AB_CKKG_MASK                   0xff0000

/* GR_AB Register bit definitions */
#define R_GLCDC_GR_AB_CKR_SHIFT                   (0)  /* R Value after RGB-Index Chroma-Key Processing Replacement */
#define R_GLCDC_GR_AB_CKR_MASK                    0xff

#define R_GLCDC_GR_AB_CKB_SHIFT                   (8)  /* B Value after RGB-Index Chroma-Key Processing Replacement */
#define R_GLCDC_GR_AB_CKB_MASK                    0xff00

#define R_GLCDC_GR_AB_CKG_SHIFT                   (16)  /* G Value after RGB-Index Chroma-Key Processing Replacement */
#define R_GLCDC_GR_AB_CKG_MASK                    0xff0000

#define R_GLCDC_GR_AB_CKA_SHIFT                   (24)  /* A Value after RGB-Index Chroma-Key Processing Replacement */
#define R_GLCDC_GR_AB_CKA_MASK                    0xff000000

/* GR_BASE Register bit definitions */
#define R_GLCDC_GR_BASE_R_SHIFT                   (0)  /* Background Color R Value */
#define R_GLCDC_GR_BASE_R_MASK                    0xff

#define R_GLCDC_GR_BASE_B_SHIFT                   (8)  /* Background Color B Value */
#define R_GLCDC_GR_BASE_B_MASK                    0xff00

#define R_GLCDC_GR_BASE_G_SHIFT                   (16)  /* Background Color G Value */
#define R_GLCDC_GR_BASE_G_MASK                    0xff0000

/* GR_CLUTINT Register bit definitions */
#define R_GLCDC_GR_CLUTINT_LINE_SHIFT             (0)  /* Number of Detection Lines */
#define R_GLCDC_GR_CLUTINT_LINE_MASK              0x7ff

#define R_GLCDC_GR_CLUTINT_SEL                    (1 << 16)  /* CLUT Table Control */

/* GR_MON Register bit definitions */
#define R_GLCDC_GR_MON_ARCST                      (1 << 0)  /* Status Monitor for Alpha Blending in Rectangular Area */

#define R_GLCDC_GR_MON_UNDFLST                    (1 << 16)  /* Underflow Status Monitor */

/* GAMG_LATCH Register bit definitions */
#define R_GLCDC_GAMG_LATCH_VEN                    (1 << 0)  /* Control of Gamma Correction × Module Register Value Reflection to Internal Operations */

/* GAM_SW Register bit definitions */
#define R_GLCDC_GAM_SW_GAMON                      (1 << 0)  /* Gamma Correction On/Off Control */

/* GAMG_LUT1 Register bit definitions */
#define R_GLCDC_GAMG_LUT1_GAIN01_SHIFT            (0)  /* Gain Value of Area 1 */
#define R_GLCDC_GAMG_LUT1_GAIN01_MASK             0x7ff

#define R_GLCDC_GAMG_LUT1_GAIN00_SHIFT            (16)  /* Gain Value of Area 0 */
#define R_GLCDC_GAMG_LUT1_GAIN00_MASK             0x7ff0000

/* GAMG_LUT2 Register bit definitions */
#define R_GLCDC_GAMG_LUT2_GAIN03_SHIFT            (0)  /* Gain Value of Area 3 */
#define R_GLCDC_GAMG_LUT2_GAIN03_MASK             0x7ff

#define R_GLCDC_GAMG_LUT2_GAIN02_SHIFT            (16)  /* Gain Value of Area 2 */
#define R_GLCDC_GAMG_LUT2_GAIN02_MASK             0x7ff0000

/* GAMG_LUT3 Register bit definitions */
#define R_GLCDC_GAMG_LUT3_GAIN05_SHIFT            (0)  /* Gain Value of Area 5 */
#define R_GLCDC_GAMG_LUT3_GAIN05_MASK             0x7ff

#define R_GLCDC_GAMG_LUT3_GAIN04_SHIFT            (16)  /* Gain Value of Area 4 */
#define R_GLCDC_GAMG_LUT3_GAIN04_MASK             0x7ff0000

/* GAMG_LUT4 Register bit definitions */
#define R_GLCDC_GAMG_LUT4_GAIN07_SHIFT            (0)  /* Gain Value of Area 7 */
#define R_GLCDC_GAMG_LUT4_GAIN07_MASK             0x7ff

#define R_GLCDC_GAMG_LUT4_GAIN06_SHIFT            (16)  /* Gain Value of Area 6 */
#define R_GLCDC_GAMG_LUT4_GAIN06_MASK             0x7ff0000

/* GAMG_LUT5 Register bit definitions */
#define R_GLCDC_GAMG_LUT5_GAIN09_SHIFT            (0)  /* Gain Value of Area 9 */
#define R_GLCDC_GAMG_LUT5_GAIN09_MASK             0x7ff

#define R_GLCDC_GAMG_LUT5_GAIN08_SHIFT            (16)  /* Gain Value of Area 8 */
#define R_GLCDC_GAMG_LUT5_GAIN08_MASK             0x7ff0000

/* GAMG_LUT6 Register bit definitions */
#define R_GLCDC_GAMG_LUT6_GAIN11_SHIFT            (0)  /* Gain Value of Area 11 */
#define R_GLCDC_GAMG_LUT6_GAIN11_MASK             0x7ff

#define R_GLCDC_GAMG_LUT6_GAIN10_SHIFT            (16)  /* Gain Value of Area 10 */
#define R_GLCDC_GAMG_LUT6_GAIN10_MASK             0x7ff0000

/* GAMG_LUT7 Register bit definitions */
#define R_GLCDC_GAMG_LUT7_GAIN13_SHIFT            (0)  /* Gain Value of Area 13 */
#define R_GLCDC_GAMG_LUT7_GAIN13_MASK             0x7ff

#define R_GLCDC_GAMG_LUT7_GAIN012_SHIFT           (16)  /* Gain Value of Area 12 */
#define R_GLCDC_GAMG_LUT7_GAIN012_MASK            0x7ff0000

/* GAMG_LUT8 Register bit definitions */
#define R_GLCDC_GAMG_LUT8_GAIN15_SHIFT            (0)  /* Gain Value of Area 15 */
#define R_GLCDC_GAMG_LUT8_GAIN15_MASK             0x7ff

#define R_GLCDC_GAMG_LUT8_GAIN14_SHIFT            (16)  /* Gain Value of Area 14 */
#define R_GLCDC_GAMG_LUT8_GAIN14_MASK             0x7ff0000

/* GAMG_AREA1 Register bit definitions */
#define R_GLCDC_GAMG_AREA1_TH03_SHIFT             (0)  /* Start Threshold of Area 3 */
#define R_GLCDC_GAMG_AREA1_TH03_MASK              0x3ff

#define R_GLCDC_GAMG_AREA1_TH02_SHIFT             (10)  /* Start Threshold of Area 2 */
#define R_GLCDC_GAMG_AREA1_TH02_MASK              0xffc00

#define R_GLCDC_GAMG_AREA1_TH01_SHIFT             (20)  /* Start Threshold of Area 1 */
#define R_GLCDC_GAMG_AREA1_TH01_MASK              0x3ff00000

/* GAMG_AREA2 Register bit definitions */
#define R_GLCDC_GAMG_AREA2_TH06_SHIFT             (0)  /* Start Threshold of Area 6 */
#define R_GLCDC_GAMG_AREA2_TH06_MASK              0x3ff

#define R_GLCDC_GAMG_AREA2_TH05_SHIFT             (10)  /* Start Threshold of Area 5 */
#define R_GLCDC_GAMG_AREA2_TH05_MASK              0xffc00

#define R_GLCDC_GAMG_AREA2_TH04_SHIFT             (20)  /* Start Threshold of Area 4 */
#define R_GLCDC_GAMG_AREA2_TH04_MASK              0x3ff00000

/* GAMG_AREA3 Register bit definitions */
#define R_GLCDC_GAMG_AREA3_TH09_SHIFT             (0)  /* Start Threshold of Area 9 */
#define R_GLCDC_GAMG_AREA3_TH09_MASK              0x3ff

#define R_GLCDC_GAMG_AREA3_TH08_SHIFT             (10)  /* Start Threshold of Area 8 */
#define R_GLCDC_GAMG_AREA3_TH08_MASK              0xffc00

#define R_GLCDC_GAMG_AREA3_TH07_SHIFT             (20)  /* Start Threshold of Area 7 */
#define R_GLCDC_GAMG_AREA3_TH07_MASK              0x3ff00000

/* GAMG_AREA4 Register bit definitions */
#define R_GLCDC_GAMG_AREA4_TH12_SHIFT             (0)  /* Start Threshold of Area 12 */
#define R_GLCDC_GAMG_AREA4_TH12_MASK              0x3ff

#define R_GLCDC_GAMG_AREA4_TH11_SHIFT             (10)  /* Start Threshold of Area 11 */
#define R_GLCDC_GAMG_AREA4_TH11_MASK              0xffc00

#define R_GLCDC_GAMG_AREA4_TH10_SHIFT             (20)  /* Start Threshold of Area 10 */
#define R_GLCDC_GAMG_AREA4_TH10_MASK              0x3ff00000

/* GAMG_AREA5 Register bit definitions */
#define R_GLCDC_GAMG_AREA5_TH15_SHIFT             (0)  /* Start Threshold of Area 15 */
#define R_GLCDC_GAMG_AREA5_TH15_MASK              0x3ff

#define R_GLCDC_GAMG_AREA5_TH14_SHIFT             (10)  /* Start Threshold of Area 14 */
#define R_GLCDC_GAMG_AREA5_TH14_MASK              0xffc00

#define R_GLCDC_GAMG_AREA5_TH13_SHIFT             (20)  /* Start Threshold of Area 13 */
#define R_GLCDC_GAMG_AREA5_TH13_MASK              0x3ff00000

/* GAMB_LATCH Register bit definitions */
#define R_GLCDC_GAMB_LATCH_VEN                    (1 << 0)  /* Control of Gamma Correction × Module Register Value Reflection to Internal Operations */

/* GAMB_LUT1 Register bit definitions */
#define R_GLCDC_GAMB_LUT1_GAIN01_SHIFT            (0)  /* Gain Value of Area 1 */
#define R_GLCDC_GAMB_LUT1_GAIN01_MASK             0x7ff

#define R_GLCDC_GAMB_LUT1_GAIN00_SHIFT            (16)  /* Gain Value of Area 0 */
#define R_GLCDC_GAMB_LUT1_GAIN00_MASK             0x7ff0000

/* GAMB_LUT2 Register bit definitions */
#define R_GLCDC_GAMB_LUT2_GAIN03_SHIFT            (0)  /* Gain Value of Area 3 */
#define R_GLCDC_GAMB_LUT2_GAIN03_MASK             0x7ff

#define R_GLCDC_GAMB_LUT2_GAIN02_SHIFT            (16)  /* Gain Value of Area 2 */
#define R_GLCDC_GAMB_LUT2_GAIN02_MASK             0x7ff0000

/* GAMB_LUT3 Register bit definitions */
#define R_GLCDC_GAMB_LUT3_GAIN05_SHIFT            (0)  /* Gain Value of Area 5 */
#define R_GLCDC_GAMB_LUT3_GAIN05_MASK             0x7ff

#define R_GLCDC_GAMB_LUT3_GAIN04_SHIFT            (16)  /* Gain Value of Area 4 */
#define R_GLCDC_GAMB_LUT3_GAIN04_MASK             0x7ff0000

/* GAMB_LUT4 Register bit definitions */
#define R_GLCDC_GAMB_LUT4_GAIN07_SHIFT            (0)  /* Gain Value of Area 7 */
#define R_GLCDC_GAMB_LUT4_GAIN07_MASK             0x7ff

#define R_GLCDC_GAMB_LUT4_GAIN06_SHIFT            (16)  /* Gain Value of Area 6 */
#define R_GLCDC_GAMB_LUT4_GAIN06_MASK             0x7ff0000

/* GAMB_LUT5 Register bit definitions */
#define R_GLCDC_GAMB_LUT5_GAIN09_SHIFT            (0)  /* Gain Value of Area 9 */
#define R_GLCDC_GAMB_LUT5_GAIN09_MASK             0x7ff

#define R_GLCDC_GAMB_LUT5_GAIN08_SHIFT            (16)  /* Gain Value of Area 8 */
#define R_GLCDC_GAMB_LUT5_GAIN08_MASK             0x7ff0000

/* GAMB_LUT6 Register bit definitions */
#define R_GLCDC_GAMB_LUT6_GAIN11_SHIFT            (0)  /* Gain Value of Area 11 */
#define R_GLCDC_GAMB_LUT6_GAIN11_MASK             0x7ff

#define R_GLCDC_GAMB_LUT6_GAIN10_SHIFT            (16)  /* Gain Value of Area 10 */
#define R_GLCDC_GAMB_LUT6_GAIN10_MASK             0x7ff0000

/* GAMB_LUT7 Register bit definitions */
#define R_GLCDC_GAMB_LUT7_GAIN13_SHIFT            (0)  /* Gain Value of Area 13 */
#define R_GLCDC_GAMB_LUT7_GAIN13_MASK             0x7ff

#define R_GLCDC_GAMB_LUT7_GAIN012_SHIFT           (16)  /* Gain Value of Area 12 */
#define R_GLCDC_GAMB_LUT7_GAIN012_MASK            0x7ff0000

/* GAMB_LUT8 Register bit definitions */
#define R_GLCDC_GAMB_LUT8_GAIN15_SHIFT            (0)  /* Gain Value of Area 15 */
#define R_GLCDC_GAMB_LUT8_GAIN15_MASK             0x7ff

#define R_GLCDC_GAMB_LUT8_GAIN14_SHIFT            (16)  /* Gain Value of Area 14 */
#define R_GLCDC_GAMB_LUT8_GAIN14_MASK             0x7ff0000

/* GAMB_AREA1 Register bit definitions */
#define R_GLCDC_GAMB_AREA1_TH03_SHIFT             (0)  /* Start Threshold of Area 3 */
#define R_GLCDC_GAMB_AREA1_TH03_MASK              0x3ff

#define R_GLCDC_GAMB_AREA1_TH02_SHIFT             (10)  /* Start Threshold of Area 2 */
#define R_GLCDC_GAMB_AREA1_TH02_MASK              0xffc00

#define R_GLCDC_GAMB_AREA1_TH01_SHIFT             (20)  /* Start Threshold of Area 1 */
#define R_GLCDC_GAMB_AREA1_TH01_MASK              0x3ff00000

/* GAMB_AREA2 Register bit definitions */
#define R_GLCDC_GAMB_AREA2_TH06_SHIFT             (0)  /* Start Threshold of Area 6 */
#define R_GLCDC_GAMB_AREA2_TH06_MASK              0x3ff

#define R_GLCDC_GAMB_AREA2_TH05_SHIFT             (10)  /* Start Threshold of Area 5 */
#define R_GLCDC_GAMB_AREA2_TH05_MASK              0xffc00

#define R_GLCDC_GAMB_AREA2_TH04_SHIFT             (20)  /* Start Threshold of Area 4 */
#define R_GLCDC_GAMB_AREA2_TH04_MASK              0x3ff00000

/* GAMB_AREA3 Register bit definitions */
#define R_GLCDC_GAMB_AREA3_TH09_SHIFT             (0)  /* Start Threshold of Area 9 */
#define R_GLCDC_GAMB_AREA3_TH09_MASK              0x3ff

#define R_GLCDC_GAMB_AREA3_TH08_SHIFT             (10)  /* Start Threshold of Area 8 */
#define R_GLCDC_GAMB_AREA3_TH08_MASK              0xffc00

#define R_GLCDC_GAMB_AREA3_TH07_SHIFT             (20)  /* Start Threshold of Area 7 */
#define R_GLCDC_GAMB_AREA3_TH07_MASK              0x3ff00000

/* GAMB_AREA4 Register bit definitions */
#define R_GLCDC_GAMB_AREA4_TH12_SHIFT             (0)  /* Start Threshold of Area 12 */
#define R_GLCDC_GAMB_AREA4_TH12_MASK              0x3ff

#define R_GLCDC_GAMB_AREA4_TH11_SHIFT             (10)  /* Start Threshold of Area 11 */
#define R_GLCDC_GAMB_AREA4_TH11_MASK              0xffc00

#define R_GLCDC_GAMB_AREA4_TH10_SHIFT             (20)  /* Start Threshold of Area 10 */
#define R_GLCDC_GAMB_AREA4_TH10_MASK              0x3ff00000

/* GAMB_AREA5 Register bit definitions */
#define R_GLCDC_GAMB_AREA5_TH15_SHIFT             (0)  /* Start Threshold of Area 15 */
#define R_GLCDC_GAMB_AREA5_TH15_MASK              0x3ff

#define R_GLCDC_GAMB_AREA5_TH14_SHIFT             (10)  /* Start Threshold of Area 14 */
#define R_GLCDC_GAMB_AREA5_TH14_MASK              0xffc00

#define R_GLCDC_GAMB_AREA5_TH13_SHIFT             (20)  /* Start Threshold of Area 13 */
#define R_GLCDC_GAMB_AREA5_TH13_MASK              0x3ff00000

/* GAMR_LATCH Register bit definitions */
#define R_GLCDC_GAMR_LATCH_VEN                    (1 << 0)  /* Control of Gamma Correction × Module Register Value Reflection to Internal Operations */

/* GAMR_LUT1 Register bit definitions */
#define R_GLCDC_GAMR_LUT1_GAIN01_SHIFT            (0)  /* Gain Value of Area 1 */
#define R_GLCDC_GAMR_LUT1_GAIN01_MASK             0x7ff

#define R_GLCDC_GAMR_LUT1_GAIN00_SHIFT            (16)  /* Gain Value of Area 0 */
#define R_GLCDC_GAMR_LUT1_GAIN00_MASK             0x7ff0000

/* GAMR_LUT2 Register bit definitions */
#define R_GLCDC_GAMR_LUT2_GAIN03_SHIFT            (0)  /* Gain Value of Area 3 */
#define R_GLCDC_GAMR_LUT2_GAIN03_MASK             0x7ff

#define R_GLCDC_GAMR_LUT2_GAIN02_SHIFT            (16)  /* Gain Value of Area 2 */
#define R_GLCDC_GAMR_LUT2_GAIN02_MASK             0x7ff0000

/* GAMR_LUT3 Register bit definitions */
#define R_GLCDC_GAMR_LUT3_GAIN05_SHIFT            (0)  /* Gain Value of Area 5 */
#define R_GLCDC_GAMR_LUT3_GAIN05_MASK             0x7ff

#define R_GLCDC_GAMR_LUT3_GAIN04_SHIFT            (16)  /* Gain Value of Area 4 */
#define R_GLCDC_GAMR_LUT3_GAIN04_MASK             0x7ff0000

/* GAMR_LUT4 Register bit definitions */
#define R_GLCDC_GAMR_LUT4_GAIN07_SHIFT            (0)  /* Gain Value of Area 7 */
#define R_GLCDC_GAMR_LUT4_GAIN07_MASK             0x7ff

#define R_GLCDC_GAMR_LUT4_GAIN06_SHIFT            (16)  /* Gain Value of Area 6 */
#define R_GLCDC_GAMR_LUT4_GAIN06_MASK             0x7ff0000

/* GAMR_LUT5 Register bit definitions */
#define R_GLCDC_GAMR_LUT5_GAIN09_SHIFT            (0)  /* Gain Value of Area 9 */
#define R_GLCDC_GAMR_LUT5_GAIN09_MASK             0x7ff

#define R_GLCDC_GAMR_LUT5_GAIN08_SHIFT            (16)  /* Gain Value of Area 8 */
#define R_GLCDC_GAMR_LUT5_GAIN08_MASK             0x7ff0000

/* GAMR_LUT6 Register bit definitions */
#define R_GLCDC_GAMR_LUT6_GAIN11_SHIFT            (0)  /* Gain Value of Area 11 */
#define R_GLCDC_GAMR_LUT6_GAIN11_MASK             0x7ff

#define R_GLCDC_GAMR_LUT6_GAIN10_SHIFT            (16)  /* Gain Value of Area 10 */
#define R_GLCDC_GAMR_LUT6_GAIN10_MASK             0x7ff0000

/* GAMR_LUT7 Register bit definitions */
#define R_GLCDC_GAMR_LUT7_GAIN13_SHIFT            (0)  /* Gain Value of Area 13 */
#define R_GLCDC_GAMR_LUT7_GAIN13_MASK             0x7ff

#define R_GLCDC_GAMR_LUT7_GAIN012_SHIFT           (16)  /* Gain Value of Area 12 */
#define R_GLCDC_GAMR_LUT7_GAIN012_MASK            0x7ff0000

/* GAMR_LUT8 Register bit definitions */
#define R_GLCDC_GAMR_LUT8_GAIN15_SHIFT            (0)  /* Gain Value of Area 15 */
#define R_GLCDC_GAMR_LUT8_GAIN15_MASK             0x7ff

#define R_GLCDC_GAMR_LUT8_GAIN14_SHIFT            (16)  /* Gain Value of Area 14 */
#define R_GLCDC_GAMR_LUT8_GAIN14_MASK             0x7ff0000

/* GAMR_AREA1 Register bit definitions */
#define R_GLCDC_GAMR_AREA1_TH03_SHIFT             (0)  /* Start Threshold of Area 3 */
#define R_GLCDC_GAMR_AREA1_TH03_MASK              0x3ff

#define R_GLCDC_GAMR_AREA1_TH02_SHIFT             (10)  /* Start Threshold of Area 2 */
#define R_GLCDC_GAMR_AREA1_TH02_MASK              0xffc00

#define R_GLCDC_GAMR_AREA1_TH01_SHIFT             (20)  /* Start Threshold of Area 1 */
#define R_GLCDC_GAMR_AREA1_TH01_MASK              0x3ff00000

/* GAMR_AREA2 Register bit definitions */
#define R_GLCDC_GAMR_AREA2_TH06_SHIFT             (0)  /* Start Threshold of Area 6 */
#define R_GLCDC_GAMR_AREA2_TH06_MASK              0x3ff

#define R_GLCDC_GAMR_AREA2_TH05_SHIFT             (10)  /* Start Threshold of Area 5 */
#define R_GLCDC_GAMR_AREA2_TH05_MASK              0xffc00

#define R_GLCDC_GAMR_AREA2_TH04_SHIFT             (20)  /* Start Threshold of Area 4 */
#define R_GLCDC_GAMR_AREA2_TH04_MASK              0x3ff00000

/* GAMR_AREA3 Register bit definitions */
#define R_GLCDC_GAMR_AREA3_TH09_SHIFT             (0)  /* Start Threshold of Area 9 */
#define R_GLCDC_GAMR_AREA3_TH09_MASK              0x3ff

#define R_GLCDC_GAMR_AREA3_TH08_SHIFT             (10)  /* Start Threshold of Area 8 */
#define R_GLCDC_GAMR_AREA3_TH08_MASK              0xffc00

#define R_GLCDC_GAMR_AREA3_TH07_SHIFT             (20)  /* Start Threshold of Area 7 */
#define R_GLCDC_GAMR_AREA3_TH07_MASK              0x3ff00000

/* GAMR_AREA4 Register bit definitions */
#define R_GLCDC_GAMR_AREA4_TH12_SHIFT             (0)  /* Start Threshold of Area 12 */
#define R_GLCDC_GAMR_AREA4_TH12_MASK              0x3ff

#define R_GLCDC_GAMR_AREA4_TH11_SHIFT             (10)  /* Start Threshold of Area 11 */
#define R_GLCDC_GAMR_AREA4_TH11_MASK              0xffc00

#define R_GLCDC_GAMR_AREA4_TH10_SHIFT             (20)  /* Start Threshold of Area 10 */
#define R_GLCDC_GAMR_AREA4_TH10_MASK              0x3ff00000

/* GAMR_AREA5 Register bit definitions */
#define R_GLCDC_GAMR_AREA5_TH15_SHIFT             (0)  /* Start Threshold of Area 15 */
#define R_GLCDC_GAMR_AREA5_TH15_MASK              0x3ff

#define R_GLCDC_GAMR_AREA5_TH14_SHIFT             (10)  /* Start Threshold of Area 14 */
#define R_GLCDC_GAMR_AREA5_TH14_MASK              0xffc00

#define R_GLCDC_GAMR_AREA5_TH13_SHIFT             (20)  /* Start Threshold of Area 13 */
#define R_GLCDC_GAMR_AREA5_TH13_MASK              0x3ff00000

/* OUT_VLATCH Register bit definitions */
#define R_GLCDC_OUT_VLATCH_VEN                    (1 << 0)  /* Control of Output Control Module Register Value Reflection to Internal Operations */

/* OUT_SET Register bit definitions */
#define R_GLCDC_OUT_SET_PHASE_SHIFT               (0)  /* Data Output Delay Control in Serial RGB Format */
#define R_GLCDC_OUT_SET_PHASE_MASK                0x3
#  define R_GLCDC_OUT_SET_PHASE_00                        (0 << R_GLCDC_OUT_SET_PHASE_SHIFT)  /* 0 cycle */
#  define R_GLCDC_OUT_SET_PHASE_01                        (1 << R_GLCDC_OUT_SET_PHASE_SHIFT)  /* 1 cycle */
#  define R_GLCDC_OUT_SET_PHASE_10                        (2 << R_GLCDC_OUT_SET_PHASE_SHIFT)  /* 2 cycles */
#  define R_GLCDC_OUT_SET_PHASE_11                        (3 << R_GLCDC_OUT_SET_PHASE_SHIFT)  /* 3 cycles */

#define R_GLCDC_OUT_SET_DIRSEL                    (1 << 4)  /* Scan Direction Select of Serial RGB Format */

#define R_GLCDC_OUT_SET_FRQSEL_SHIFT              (8)  /* Clock Frequency Division Control */
#define R_GLCDC_OUT_SET_FRQSEL_MASK               0x300
#  define R_GLCDC_OUT_SET_FRQSEL_00                       (0 << R_GLCDC_OUT_SET_FRQSEL_SHIFT)  /* No frequency division, parallel RGB */
#  define R_GLCDC_OUT_SET_FRQSEL_01                       (1 << R_GLCDC_OUT_SET_FRQSEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_OUT_SET_FRQSEL_10                       (2 << R_GLCDC_OUT_SET_FRQSEL_SHIFT)  /* Quarter frequency (serial RGB) */
#  define R_GLCDC_OUT_SET_FRQSEL_11                       (3 << R_GLCDC_OUT_SET_FRQSEL_SHIFT)  /* Setting prohibited */

#define R_GLCDC_OUT_SET_FORMAT_SHIFT              (12)  /* Output Format Select */
#define R_GLCDC_OUT_SET_FORMAT_MASK               0x3000
#  define R_GLCDC_OUT_SET_FORMAT_00                       (0 << R_GLCDC_OUT_SET_FORMAT_SHIFT)  /* RGB888 — select RGB888 as dither output format */
#  define R_GLCDC_OUT_SET_FORMAT_01                       (1 << R_GLCDC_OUT_SET_FORMAT_SHIFT)  /* RGB666 — select RGB666 as dither output format */
#  define R_GLCDC_OUT_SET_FORMAT_10                       (2 << R_GLCDC_OUT_SET_FORMAT_SHIFT)  /* RGB565 — select RGB565 as dither output format */
#  define R_GLCDC_OUT_SET_FORMAT_11                       (3 << R_GLCDC_OUT_SET_FORMAT_SHIFT)  /* Serial RGB — select RGB888 as dither output format. Select dither output format in OUT_PDTHA.FORM[1:0]  */

#define R_GLCDC_OUT_SET_SWAPON                    (1 << 24)  /* Pixel Order Control */

#define R_GLCDC_OUT_SET_ENDIANON                  (1 << 28)  /* Bit Endian Control */

/* OUT_BRIGHT1 Register bit definitions */
#define R_GLCDC_OUT_BRIGHT1_BRTG_SHIFT            (0)  /* Brightness Adjustment of G Signal */
#define R_GLCDC_OUT_BRIGHT1_BRTG_MASK             0x3ff

/* OUT_BRIGHT2 Register bit definitions */
#define R_GLCDC_OUT_BRIGHT2_BRTR_SHIFT            (0)  /* Brightness Adjustment of R Signal */
#define R_GLCDC_OUT_BRIGHT2_BRTR_MASK             0x3ff

#define R_GLCDC_OUT_BRIGHT2_BRTB_SHIFT            (16)  /* Brightness Adjustment of B Signal */
#define R_GLCDC_OUT_BRIGHT2_BRTB_MASK             0x3ff0000

/* OUT_CONTRAST Register bit definitions */
#define R_GLCDC_OUT_CONTRAST_CONTR_SHIFT          (0)  /* Contrast Adjustment of R Signal */
#define R_GLCDC_OUT_CONTRAST_CONTR_MASK           0xff

#define R_GLCDC_OUT_CONTRAST_CONTB_SHIFT          (8)  /* Contrast Adjustment of B Signal */
#define R_GLCDC_OUT_CONTRAST_CONTB_MASK           0xff00

#define R_GLCDC_OUT_CONTRAST_CONTG_SHIFT          (16)  /* Contrast Adjustment of G Signal */
#define R_GLCDC_OUT_CONTRAST_CONTG_MASK           0xff0000

/* OUT_PDTHA Register bit definitions */
#define R_GLCDC_OUT_PDTHA_PD_SHIFT                (0)  /* Pattern Value (D) of 2×2 Pattern Dither */
#define R_GLCDC_OUT_PDTHA_PD_MASK                 0x3

#define R_GLCDC_OUT_PDTHA_PC_SHIFT                (4)  /* Pattern Value (C) of 2×2 Pattern Dither */
#define R_GLCDC_OUT_PDTHA_PC_MASK                 0x30

#define R_GLCDC_OUT_PDTHA_PB_SHIFT                (8)  /* Pattern Value (B) of 2×2 Pattern Dither */
#define R_GLCDC_OUT_PDTHA_PB_MASK                 0x300

#define R_GLCDC_OUT_PDTHA_PA_SHIFT                (12)  /* Pattern Value (A) of 2×2 Pattern Dither */
#define R_GLCDC_OUT_PDTHA_PA_MASK                 0x3000

#define R_GLCDC_OUT_PDTHA_FORM_SHIFT              (16)  /* Output Format Select */
#define R_GLCDC_OUT_PDTHA_FORM_MASK               0x30000
#  define R_GLCDC_OUT_PDTHA_FORM_00                       (0 << R_GLCDC_OUT_PDTHA_FORM_SHIFT)  /* RGB888; select RGB888 or serial RGB as output interface format */
#  define R_GLCDC_OUT_PDTHA_FORM_01                       (1 << R_GLCDC_OUT_PDTHA_FORM_SHIFT)  /* RGB666; select RGB666 as output interface format */
#  define R_GLCDC_OUT_PDTHA_FORM_10                       (2 << R_GLCDC_OUT_PDTHA_FORM_SHIFT)  /* RGB565; select RGB565 as output interface format */
#  define R_GLCDC_OUT_PDTHA_FORM_11                       (3 << R_GLCDC_OUT_PDTHA_FORM_SHIFT)  /* Setting prohibited Select output interface format in OUT_SET.FORMAT[1:0].  */

#define R_GLCDC_OUT_PDTHA_SEL_SHIFT               (20)  /* Operation Mode */
#define R_GLCDC_OUT_PDTHA_SEL_MASK                0x300000
#  define R_GLCDC_OUT_PDTHA_SEL_00                        (0 << R_GLCDC_OUT_PDTHA_SEL_SHIFT)  /* Truncate */
#  define R_GLCDC_OUT_PDTHA_SEL_01                        (1 << R_GLCDC_OUT_PDTHA_SEL_SHIFT)  /* Round-off */
#  define R_GLCDC_OUT_PDTHA_SEL_10                        (2 << R_GLCDC_OUT_PDTHA_SEL_SHIFT)  /* 2×2 pattern dither */
#  define R_GLCDC_OUT_PDTHA_SEL_11                        (3 << R_GLCDC_OUT_PDTHA_SEL_SHIFT)  /* Setting prohibited  */

/* OUT_CLKPHASE Register bit definitions */
#define R_GLCDC_OUT_CLKPHASE_TCON3EDGE            (1 << 3)  /* LCD_TCON3 Output Phase Control */

#define R_GLCDC_OUT_CLKPHASE_TCON2EDGE            (1 << 4)  /* LCD_TCON2 Output Phase Control */

#define R_GLCDC_OUT_CLKPHASE_TCON1EDGE            (1 << 5)  /* LCD_TCON1 Output Phase Control */

#define R_GLCDC_OUT_CLKPHASE_TCON0EDGE            (1 << 6)  /* LCD_TCON0 Output Phase Control */

#define R_GLCDC_OUT_CLKPHASE_LCDEDGE              (1 << 8)  /* LCD_DATA Output Phase Control */

#define R_GLCDC_OUT_CLKPHASE_FRONTGAM             (1 << 12)  /* Correction Control */

/* TCON_TIM Register bit definitions */
#define R_GLCDC_TCON_TIM_OFFSET_SHIFT             (0)  /* Horizontal Synchronization Signal Generation Reference Timing */
#define R_GLCDC_TCON_TIM_OFFSET_MASK              0x7ff

#define R_GLCDC_TCON_TIM_HALF_SHIFT               (16)  /* Vertical Synchronization Signal Generation Change Timing */
#define R_GLCDC_TCON_TIM_HALF_MASK                0x7ff0000

/* TCON_STVA1 Register bit definitions */
#define R_GLCDC_TCON_STVA1_VW_SHIFT               (0)  /* Vertical Synchronization Signal STVx1 Second Change Timing */
#define R_GLCDC_TCON_STVA1_VW_MASK                0x7ff

#define R_GLCDC_TCON_STVA1_VS_SHIFT               (16)  /* Vertical Synchronization Signal STVx1 First Change Timing */
#define R_GLCDC_TCON_STVA1_VS_MASK                0x7ff0000

/* TCON_STVA2 Register bit definitions */
#define R_GLCDC_TCON_STVA2_SEL_SHIFT              (0)  /* Output Signal Select Control for VSOUT/VEOUT Pin */
#define R_GLCDC_TCON_STVA2_SEL_MASK               0x7
#  define R_GLCDC_TCON_STVA2_SEL_000                      (0 << R_GLCDC_TCON_STVA2_SEL_SHIFT)  /* STVA */
#  define R_GLCDC_TCON_STVA2_SEL_001                      (1 << R_GLCDC_TCON_STVA2_SEL_SHIFT)  /* STVB */
#  define R_GLCDC_TCON_STVA2_SEL_010                      (2 << R_GLCDC_TCON_STVA2_SEL_SHIFT)  /* STHA */
#  define R_GLCDC_TCON_STVA2_SEL_011                      (3 << R_GLCDC_TCON_STVA2_SEL_SHIFT)  /* STHB */
#  define R_GLCDC_TCON_STVA2_SEL_100                      (4 << R_GLCDC_TCON_STVA2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STVA2_SEL_101                      (5 << R_GLCDC_TCON_STVA2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STVA2_SEL_110                      (6 << R_GLCDC_TCON_STVA2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STVA2_SEL_111                      (7 << R_GLCDC_TCON_STVA2_SEL_SHIFT)  /* DE */

#define R_GLCDC_TCON_STVA2_INV                    (1 << 4)  /* Vertical Synchronization Signal STVx Polarity Inversion Control */

/* TCON_STVB1 Register bit definitions */
#define R_GLCDC_TCON_STVB1_VW_SHIFT               (0)  /* Vertical Synchronization Signal STVx1 Second Change Timing */
#define R_GLCDC_TCON_STVB1_VW_MASK                0x7ff

#define R_GLCDC_TCON_STVB1_VS_SHIFT               (16)  /* Vertical Synchronization Signal STVx1 First Change Timing */
#define R_GLCDC_TCON_STVB1_VS_MASK                0x7ff0000

/* TCON_STVB2 Register bit definitions */
#define R_GLCDC_TCON_STVB2_SEL_SHIFT              (0)  /* Output Signal Select Control for VSOUT/VEOUT Pin */
#define R_GLCDC_TCON_STVB2_SEL_MASK               0x7
#  define R_GLCDC_TCON_STVB2_SEL_000                      (0 << R_GLCDC_TCON_STVB2_SEL_SHIFT)  /* STVA */
#  define R_GLCDC_TCON_STVB2_SEL_001                      (1 << R_GLCDC_TCON_STVB2_SEL_SHIFT)  /* STVB */
#  define R_GLCDC_TCON_STVB2_SEL_010                      (2 << R_GLCDC_TCON_STVB2_SEL_SHIFT)  /* STHA */
#  define R_GLCDC_TCON_STVB2_SEL_011                      (3 << R_GLCDC_TCON_STVB2_SEL_SHIFT)  /* STHB */
#  define R_GLCDC_TCON_STVB2_SEL_100                      (4 << R_GLCDC_TCON_STVB2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STVB2_SEL_101                      (5 << R_GLCDC_TCON_STVB2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STVB2_SEL_110                      (6 << R_GLCDC_TCON_STVB2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STVB2_SEL_111                      (7 << R_GLCDC_TCON_STVB2_SEL_SHIFT)  /* DE */

#define R_GLCDC_TCON_STVB2_INV                    (1 << 4)  /* Vertical Synchronization Signal STVx Polarity Inversion Control */

/* TCON_STHA1 Register bit definitions */
#define R_GLCDC_TCON_STHA1_HW_SHIFT               (0)  /* Horizontal Synchronization Signal STHx1 Second Change Timing */
#define R_GLCDC_TCON_STHA1_HW_MASK                0x7ff

#define R_GLCDC_TCON_STHA1_HS_SHIFT               (16)  /* Horizontal Synchronization Signal STHx1 First Change Timing */
#define R_GLCDC_TCON_STHA1_HS_MASK                0x7ff0000

/* TCON_STHA2 Register bit definitions */
#define R_GLCDC_TCON_STHA2_SEL_SHIFT              (0)  /* Output Signal Select Control for LCD_TCON2/LCD_TCON3 Pin */
#define R_GLCDC_TCON_STHA2_SEL_MASK               0x7
#  define R_GLCDC_TCON_STHA2_SEL_000                      (0 << R_GLCDC_TCON_STHA2_SEL_SHIFT)  /* STVA */
#  define R_GLCDC_TCON_STHA2_SEL_001                      (1 << R_GLCDC_TCON_STHA2_SEL_SHIFT)  /* STVB */
#  define R_GLCDC_TCON_STHA2_SEL_010                      (2 << R_GLCDC_TCON_STHA2_SEL_SHIFT)  /* STHA */
#  define R_GLCDC_TCON_STHA2_SEL_011                      (3 << R_GLCDC_TCON_STHA2_SEL_SHIFT)  /* STHB */
#  define R_GLCDC_TCON_STHA2_SEL_100                      (4 << R_GLCDC_TCON_STHA2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STHA2_SEL_101                      (5 << R_GLCDC_TCON_STHA2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STHA2_SEL_110                      (6 << R_GLCDC_TCON_STHA2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STHA2_SEL_111                      (7 << R_GLCDC_TCON_STHA2_SEL_SHIFT)  /* DE */

#define R_GLCDC_TCON_STHA2_INV                    (1 << 4)  /* Horizontal Synchronization Signal STHx Polarity Inversion Control */

#define R_GLCDC_TCON_STHA2_HSSEL                  (1 << 8)  /* Horizontal Synchronization Signal STHx Reference Timing Control */

/* TCON_STHB1 Register bit definitions */
#define R_GLCDC_TCON_STHB1_HW_SHIFT               (0)  /* Horizontal Synchronization Signal STHx1 Second Change Timing */
#define R_GLCDC_TCON_STHB1_HW_MASK                0x7ff

#define R_GLCDC_TCON_STHB1_HS_SHIFT               (16)  /* Horizontal Synchronization Signal STHx1 First Change Timing */
#define R_GLCDC_TCON_STHB1_HS_MASK                0x7ff0000

/* TCON_STHB2 Register bit definitions */
#define R_GLCDC_TCON_STHB2_SEL_SHIFT              (0)  /* Output Signal Select Control for LCD_TCON2/LCD_TCON3 Pin */
#define R_GLCDC_TCON_STHB2_SEL_MASK               0x7
#  define R_GLCDC_TCON_STHB2_SEL_000                      (0 << R_GLCDC_TCON_STHB2_SEL_SHIFT)  /* STVA */
#  define R_GLCDC_TCON_STHB2_SEL_001                      (1 << R_GLCDC_TCON_STHB2_SEL_SHIFT)  /* STVB */
#  define R_GLCDC_TCON_STHB2_SEL_010                      (2 << R_GLCDC_TCON_STHB2_SEL_SHIFT)  /* STHA */
#  define R_GLCDC_TCON_STHB2_SEL_011                      (3 << R_GLCDC_TCON_STHB2_SEL_SHIFT)  /* STHB */
#  define R_GLCDC_TCON_STHB2_SEL_100                      (4 << R_GLCDC_TCON_STHB2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STHB2_SEL_101                      (5 << R_GLCDC_TCON_STHB2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STHB2_SEL_110                      (6 << R_GLCDC_TCON_STHB2_SEL_SHIFT)  /* Setting prohibited */
#  define R_GLCDC_TCON_STHB2_SEL_111                      (7 << R_GLCDC_TCON_STHB2_SEL_SHIFT)  /* DE */

#define R_GLCDC_TCON_STHB2_INV                    (1 << 4)  /* Horizontal Synchronization Signal STHx Polarity Inversion Control */

#define R_GLCDC_TCON_STHB2_HSSEL                  (1 << 8)  /* Horizontal Synchronization Signal STHx Reference Timing Control */

/* TCON_DE Register bit definitions */
#define R_GLCDC_TCON_DE_INV                       (1 << 0)  /* Data Enable Signal DE Polarity Inversion Control */

/* SYSCNT_DTCTEN Register bit definitions */
#define R_GLCDC_SYSCNT_DTCTEN_VPOSDTC             (1 << 0)  /* Specified Line Detection Control */

#define R_GLCDC_SYSCNT_DTCTEN_L1UNDFDTC           (1 << 1)  /* Graphics 1 Underflow Detection Control */

#define R_GLCDC_SYSCNT_DTCTEN_L2UNDFDTC           (1 << 2)  /* Graphics 2 Underflow Detection Control */

/* SYSCNT_INTEN Register bit definitions */
#define R_GLCDC_SYSCNT_INTEN_VPOSINTEN            (1 << 0)  /* Interrupt Request Signal GLCDC_VPOS Enable Control */

#define R_GLCDC_SYSCNT_INTEN_L1UNDFINTEN          (1 << 1)  /* Interrupt Request Signal GLCDC_L1UNDF Enable Control */

#define R_GLCDC_SYSCNT_INTEN_L2UNDFINTEN          (1 << 2)  /* Interrupt Request Signal GLCDC_L2UNDF Enable Control */

/* SYSCNT_STCLR Register bit definitions */
#define R_GLCDC_SYSCNT_STCLR_VPOSCLR              (1 << 0)  /* Graphics 2 Specified Line Detection Flag Clear */

#define R_GLCDC_SYSCNT_STCLR_L1UNDFCLR            (1 << 1)  /* Graphics 1 Underflow Detection Flag Clear */

#define R_GLCDC_SYSCNT_STCLR_L2UNDFCLR            (1 << 2)  /* Graphics 2 Underflow Detection Flag Clear */

/* SYSCNT_STMON Register bit definitions */
#define R_GLCDC_SYSCNT_STMON_VPOS                 (1 << 0)  /* Graphics 2 Specified Line Detection Flag */

#define R_GLCDC_SYSCNT_STMON_L1UNDF               (1 << 1)  /* Graphics 1 Underflow Detection Flag */

#define R_GLCDC_SYSCNT_STMON_L2UNDF               (1 << 2)  /* Graphics 2 Underflow Detection Flag */

/* SYSCNT_PANEL_CLK Register bit definitions */
#define R_GLCDC_SYSCNT_PANEL_CLK_DCDR_SHIFT       (0)  /* Clock Division Ratio Setting Control */
#define R_GLCDC_SYSCNT_PANEL_CLK_DCDR_MASK        0x3f

#define R_GLCDC_SYSCNT_PANEL_CLK_CLKEN            (1 << 6)  /* Panel Clock Output Enable Control */

#define R_GLCDC_SYSCNT_PANEL_CLK_CLKSEL           (1 << 8)  /* Panel Clock Supply Source Control */

#define R_GLCDC_SYSCNT_PANEL_CLK_PIXSEL           (1 << 12)  /* Pixel Clock Select Control */

#define R_GLCDC_SYSCNT_PANEL_CLK_VER_SHIFT        (16)  /* Version Information */
#define R_GLCDC_SYSCNT_PANEL_CLK_VER_MASK         0xffff0000


/* Maximum number of channels */

#define GLCDC_MAX_CHANNELS    256

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GLCDC_H */

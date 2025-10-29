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

/* GR1_CLUT0[%s] Registers () */
#define R_GLCDC_GR1_CLUT0_OFFSET(m)               (0x00000000 + ((m) * 0x00000004))  /* Color Palette 0 Plane for Graphics 1 Plane */
#define R_GLCDC_GR1_CLUT1_OFFSET                  0x00000400  /* Color Palette 1 Plane for Graphics 1 Plane */
#define R_GLCDC_GR2_CLUT0_OFFSET                  0x00000800  /* Color Palette 0 Plane for Graphics 2 Plane */
#define R_GLCDC_GR2_CLUT1_OFFSET                  0x00000c00  /* Color Palette 1 Plane for Graphics 2 Plane */
#define R_GLCDC_BG_OFFSET                         0x00001000  /* Background Registers */
/* GR[%s] Registers () */
#define R_GLCDC_GR_OFFSET(m)                      (0x00001100 + ((m) * 0x00000100))  /* Layer Registers */
/* GAM[%s] Registers () */
#define R_GLCDC_GAM_OFFSET(m)                     (0x00001300 + ((m) * 0x00000040))  /* Gamma Settings */
#define R_GLCDC_OUT_OFFSET                        0x000013c0  /* Output Control Registers */
#define R_GLCDC_TCON_OFFSET                       0x00001400  /* Timing Control Registers */
#define R_GLCDC_SYSCNT_OFFSET                     0x00001440  /* GLCDC System Control Registers */

/* GLCDC Register Addresses */

#define R_GLCDC_GR1_CLUT0(m)                      (R_GLCDC_BASE + R_GLCDC_GR1_CLUT0_OFFSET(m))
#define R_GLCDC_GR1_CLUT1                         (R_GLCDC_BASE + R_GLCDC_GR1_CLUT1_OFFSET)
#define R_GLCDC_GR2_CLUT0                         (R_GLCDC_BASE + R_GLCDC_GR2_CLUT0_OFFSET)
#define R_GLCDC_GR2_CLUT1                         (R_GLCDC_BASE + R_GLCDC_GR2_CLUT1_OFFSET)
#define R_GLCDC_BG                                (R_GLCDC_BASE + R_GLCDC_BG_OFFSET)
#define R_GLCDC_GR(m)                             (R_GLCDC_BASE + R_GLCDC_GR_OFFSET(m))
#define R_GLCDC_GAM(m)                            (R_GLCDC_BASE + R_GLCDC_GAM_OFFSET(m))
#define R_GLCDC_OUT                               (R_GLCDC_BASE + R_GLCDC_OUT_OFFSET)
#define R_GLCDC_TCON                              (R_GLCDC_BASE + R_GLCDC_TCON_OFFSET)
#define R_GLCDC_SYSCNT                            (R_GLCDC_BASE + R_GLCDC_SYSCNT_OFFSET)

/* Register bit definitions */
/* GR1_CLUT0 Register bit definitions */
#define R_GLCDC_GR1_CLUT0_A_SHIFT                 (24)  /* Alpha Blending Value of Color Palette n Plane for Graphics m Plane */
#define R_GLCDC_GR1_CLUT0_A_MASK                  0xff000000

#define R_GLCDC_GR1_CLUT0_R_SHIFT                 (16)  /* R Value of Color Palette n Plane for Graphics m Plane */
#define R_GLCDC_GR1_CLUT0_R_MASK                  0xff0000

#define R_GLCDC_GR1_CLUT0_G_SHIFT                 (8)  /* G Value of Color Palette n Plane for Graphics m Plane */
#define R_GLCDC_GR1_CLUT0_G_MASK                  0xff00

#define R_GLCDC_GR1_CLUT0_B_SHIFT                 (0)  /* B Value of Color Palette n Plane for Graphics m Plane */
#define R_GLCDC_GR1_CLUT0_B_MASK                  0xff

/* GR1_CLUT1 Register bit definitions */
#define R_GLCDC_GR1_CLUT1_B_SHIFT                 (0)  /* B Value of Color Palette n Plane for Graphics m Plane */
#define R_GLCDC_GR1_CLUT1_B_MASK                  0xff

#define R_GLCDC_GR1_CLUT1_G_SHIFT                 (8)  /* G Value of Color Palette n Plane for Graphics m Plane */
#define R_GLCDC_GR1_CLUT1_G_MASK                  0xff00

#define R_GLCDC_GR1_CLUT1_R_SHIFT                 (16)  /* R Value of Color Palette n Plane for Graphics m Plane */
#define R_GLCDC_GR1_CLUT1_R_MASK                  0xff0000

#define R_GLCDC_GR1_CLUT1_A_SHIFT                 (24)  /* Alpha Blending Value of Color Palette n Plane for Graphics m Plane */
#define R_GLCDC_GR1_CLUT1_A_MASK                  0xff000000

/* GR2_CLUT0 Register bit definitions */
#define R_GLCDC_GR2_CLUT0_B_SHIFT                 (0)  /* B Value of Color Palette n Plane for Graphics m Plane */
#define R_GLCDC_GR2_CLUT0_B_MASK                  0xff

#define R_GLCDC_GR2_CLUT0_G_SHIFT                 (8)  /* G Value of Color Palette n Plane for Graphics m Plane */
#define R_GLCDC_GR2_CLUT0_G_MASK                  0xff00

#define R_GLCDC_GR2_CLUT0_R_SHIFT                 (16)  /* R Value of Color Palette n Plane for Graphics m Plane */
#define R_GLCDC_GR2_CLUT0_R_MASK                  0xff0000

#define R_GLCDC_GR2_CLUT0_A_SHIFT                 (24)  /* Alpha Blending Value of Color Palette n Plane for Graphics m Plane */
#define R_GLCDC_GR2_CLUT0_A_MASK                  0xff000000

/* GR2_CLUT1 Register bit definitions */
#define R_GLCDC_GR2_CLUT1_B_SHIFT                 (0)  /* B Value of Color Palette n Plane for Graphics m Plane */
#define R_GLCDC_GR2_CLUT1_B_MASK                  0xff

#define R_GLCDC_GR2_CLUT1_G_SHIFT                 (8)  /* G Value of Color Palette n Plane for Graphics m Plane */
#define R_GLCDC_GR2_CLUT1_G_MASK                  0xff00

#define R_GLCDC_GR2_CLUT1_R_SHIFT                 (16)  /* R Value of Color Palette n Plane for Graphics m Plane */
#define R_GLCDC_GR2_CLUT1_R_MASK                  0xff0000

#define R_GLCDC_GR2_CLUT1_A_SHIFT                 (24)  /* Alpha Blending Value of Color Palette n Plane for Graphics m Plane */
#define R_GLCDC_GR2_CLUT1_A_MASK                  0xff000000


/* Maximum number of channels */

#define GLCDC_MAX_CHANNELS    256

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GLCDC_H */

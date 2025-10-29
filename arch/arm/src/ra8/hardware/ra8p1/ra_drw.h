/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_drw.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DRW_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DRW_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DRW Base Address */
#ifndef R_DRW_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_DRW_BASE           0x40444000
#else
#define R_DRW_BASE           0x50444000
#endif
#endif

/* DRW Register Offsets */

#define R_DRW_CONTROL_OFFSET                      0x00000000  /* Geometry Control Register */
#define R_DRW_STATUS_OFFSET                       0x00000000  /* Status Control Register */
#define R_DRW_CONTROL2_OFFSET                     0x00000004  /* Surface Control Register  */
#define R_DRW_HWREVISION_OFFSET                   0x00000004  /* Hardware Version and Feature Set ID Register */
/* L%sSTART Registers (1-6) */
#define R_DRW_LSTART_OFFSET(m)                    (0x00000010 + ((m) * 0x00000004))  /* Limiter %s Start Value Register */
/* L%sXADD Registers (1-6) */
#define R_DRW_LXADD_OFFSET(m)                     (0x00000028 + ((m) * 0x00000004))  /* Limiter %s X-Axis Increment Register */
/* L%sYADD Registers (1-6) */
#define R_DRW_LYADD_OFFSET(m)                     (0x00000040 + ((m) * 0x00000004))  /* Limiter %s Y-Axis Increment Register */
/* L%sBAND Registers (1,2) */
#define R_DRW_LBAND_OFFSET(m)                     (0x00000058 + ((m) * 0x00000004))  /* Limiter %s Band Width Parameter Register */
#define R_DRW_COLOR1_OFFSET                       0x00000064  /* Base Color Register */
#define R_DRW_COLOR2_OFFSET                       0x00000068  /* Secondary Color Register */
#define R_DRW_PATTERN_OFFSET                      0x00000074  /* Pattern Register */
#define R_DRW_SIZE_OFFSET                         0x00000078  /* Bounding Box Dimension Register */
#define R_DRW_PITCH_OFFSET                        0x0000007c  /* Framebuffer Pitch And Spanstore Delay Register */
#define R_DRW_ORIGIN_OFFSET                       0x00000080  /* Framebuffer Base Address Register */
#define R_DRW_LUSTART_OFFSET                      0x00000090  /* U Limiter Start Value Register  */
#define R_DRW_LUXADD_OFFSET                       0x00000094  /* U Limiter X-Axis Increment Register */
#define R_DRW_LUYADD_OFFSET                       0x00000098  /* U Limiter Y-Axis Increment Register */
#define R_DRW_LVSTARTI_OFFSET                     0x0000009c  /* V Limiter Start Value Integer Part Register */
#define R_DRW_LVSTARTF_OFFSET                     0x000000a0  /* V Limiter Start Value Fractional Part Register */
#define R_DRW_LVXADDI_OFFSET                      0x000000a4  /* V Limiter X-Axis Increment Integer Part Register */
#define R_DRW_LVYADDI_OFFSET                      0x000000a8  /* V Limiter Y-Axis Increment Integer Part Register */
#define R_DRW_LVYXADDF_OFFSET                     0x000000ac  /* V Limiter Increment Fractional Parts Register */
#define R_DRW_TEXPITCH_OFFSET                     0x000000b4  /* Texels Per Texture Line Register */
#define R_DRW_TEXMASK_OFFSET                      0x000000b8  /* Texture Size or Texture Address Mask Register */
#define R_DRW_TEXORIGIN_OFFSET                    0x000000bc  /* Texture Base Address Register  */
#define R_DRW_IRQCTL_OFFSET                       0x000000c0  /* Interrupt Control Register */
#define R_DRW_CACHECTL_OFFSET                     0x000000c4  /* Cache Control Register */
#define R_DRW_DLISTSTART_OFFSET                   0x000000c8  /* Display List Start Address Register */
/* PERFCOUNT%s Registers (1,2) */
#define R_DRW_PERFCOUNT_OFFSET(m)                 (0x000000cc + ((m) * 0x00000004))  /* Performance Counter %s */
#define R_DRW_PERFTRIGGER_OFFSET                  0x000000d4  /* Performance Counters Control Register */
#define R_DRW_TEXCLADDR_OFFSET                    0x000000dc  /* CLUT Start Address Register */
#define R_DRW_TEXCLDATA_OFFSET                    0x000000e0  /* CLUT Data Register */
#define R_DRW_TEXCLOFFSET_OFFSET                  0x000000e4  /* CLUT Offset Register */
#define R_DRW_COLKEY_OFFSET                       0x000000e8  /* Color Key Register */
#define R_DRW_DBWER_OFFSET                        0x00000100  /* DRW Bufferable Write Enable Register */

/* DRW Register Addresses */

#define R_DRW_CONTROL                             (R_DRW_BASE + R_DRW_CONTROL_OFFSET)
#define R_DRW_STATUS                              (R_DRW_BASE + R_DRW_STATUS_OFFSET)
#define R_DRW_CONTROL2                            (R_DRW_BASE + R_DRW_CONTROL2_OFFSET)
#define R_DRW_HWREVISION                          (R_DRW_BASE + R_DRW_HWREVISION_OFFSET)
#define R_DRW_LSTART(m)                           (R_DRW_BASE + R_DRW_LSTART_OFFSET(m))
#define R_DRW_LXADD(m)                            (R_DRW_BASE + R_DRW_LXADD_OFFSET(m))
#define R_DRW_LYADD(m)                            (R_DRW_BASE + R_DRW_LYADD_OFFSET(m))
#define R_DRW_LBAND(m)                            (R_DRW_BASE + R_DRW_LBAND_OFFSET(m))
#define R_DRW_COLOR1                              (R_DRW_BASE + R_DRW_COLOR1_OFFSET)
#define R_DRW_COLOR2                              (R_DRW_BASE + R_DRW_COLOR2_OFFSET)
#define R_DRW_PATTERN                             (R_DRW_BASE + R_DRW_PATTERN_OFFSET)
#define R_DRW_SIZE                                (R_DRW_BASE + R_DRW_SIZE_OFFSET)
#define R_DRW_PITCH                               (R_DRW_BASE + R_DRW_PITCH_OFFSET)
#define R_DRW_ORIGIN                              (R_DRW_BASE + R_DRW_ORIGIN_OFFSET)
#define R_DRW_LUSTART                             (R_DRW_BASE + R_DRW_LUSTART_OFFSET)
#define R_DRW_LUXADD                              (R_DRW_BASE + R_DRW_LUXADD_OFFSET)
#define R_DRW_LUYADD                              (R_DRW_BASE + R_DRW_LUYADD_OFFSET)
#define R_DRW_LVSTARTI                            (R_DRW_BASE + R_DRW_LVSTARTI_OFFSET)
#define R_DRW_LVSTARTF                            (R_DRW_BASE + R_DRW_LVSTARTF_OFFSET)
#define R_DRW_LVXADDI                             (R_DRW_BASE + R_DRW_LVXADDI_OFFSET)
#define R_DRW_LVYADDI                             (R_DRW_BASE + R_DRW_LVYADDI_OFFSET)
#define R_DRW_LVYXADDF                            (R_DRW_BASE + R_DRW_LVYXADDF_OFFSET)
#define R_DRW_TEXPITCH                            (R_DRW_BASE + R_DRW_TEXPITCH_OFFSET)
#define R_DRW_TEXMASK                             (R_DRW_BASE + R_DRW_TEXMASK_OFFSET)
#define R_DRW_TEXORIGIN                           (R_DRW_BASE + R_DRW_TEXORIGIN_OFFSET)
#define R_DRW_IRQCTL                              (R_DRW_BASE + R_DRW_IRQCTL_OFFSET)
#define R_DRW_CACHECTL                            (R_DRW_BASE + R_DRW_CACHECTL_OFFSET)
#define R_DRW_DLISTSTART                          (R_DRW_BASE + R_DRW_DLISTSTART_OFFSET)
#define R_DRW_PERFCOUNT(m)                        (R_DRW_BASE + R_DRW_PERFCOUNT_OFFSET(m))
#define R_DRW_PERFTRIGGER                         (R_DRW_BASE + R_DRW_PERFTRIGGER_OFFSET)
#define R_DRW_TEXCLADDR                           (R_DRW_BASE + R_DRW_TEXCLADDR_OFFSET)
#define R_DRW_TEXCLDATA                           (R_DRW_BASE + R_DRW_TEXCLDATA_OFFSET)
#define R_DRW_TEXCLOFFSET                         (R_DRW_BASE + R_DRW_TEXCLOFFSET_OFFSET)
#define R_DRW_COLKEY                              (R_DRW_BASE + R_DRW_COLKEY_OFFSET)
#define R_DRW_DBWER                               (R_DRW_BASE + R_DRW_DBWER_OFFSET)

/* Register bit definitions */
/* CONTROL Register bit definitions */
#define R_DRW_CONTROL_SPANSTORE                   (1 << 23)  /* Nextline span start is always equal or left to current-line span start */

#define R_DRW_CONTROL_SPANABORT                   (1 << 22)  /* Shape is horizontally convex, only a single span per scanline */

#define R_DRW_CONTROL_UNIONCD                     (1 << 21)  /* Combine outputs C & D as union (output is final) */

#define R_DRW_CONTROL_UNIONAB                     (1 << 20)  /* Combine outputs A & B as union (output is called C) */

#define R_DRW_CONTROL_UNION56                     (1 << 19)  /* Combine limter 5 & 6 as union (output is called D) */

#define R_DRW_CONTROL_UNION34                     (1 << 18)  /* Combine limter 3 & 4 as union (output is called B) */

#define R_DRW_CONTROL_UNION12                     (1 << 17)  /* Combine limter 1 & 2 as union (output is called A) */

#define R_DRW_CONTROL_BAND2ENABLE                 (1 << 16)  /* Enable band postprocess for limiter 1 (see L1BAND) */

#define R_DRW_CONTROL_BAND1ENABLE                 (1 << 15)  /* Enable band postprocess for limiter 1 (see L1BAND) */

#define R_DRW_CONTROL_LIM6THRESHOLD               (1 << 14)  /* Enable limiter 6 threshold mode */

#define R_DRW_CONTROL_LIM5THRESHOLD               (1 << 13)  /* Enable limiter 5 threshold mode */

#define R_DRW_CONTROL_LIM4THRESHOLD               (1 << 12)  /* Enable limiter 4 threshold mode */

#define R_DRW_CONTROL_LIM3THRESHOLD               (1 << 11)  /* Enable limiter 3 threshold mode */

#define R_DRW_CONTROL_LIM2THRESHOLD               (1 << 10)  /* Enable limiter 2 threshold mode */

#define R_DRW_CONTROL_LIM1THRESHOLD               (1 << 9)  /* Enable limiter 1 threshold mode */

#define R_DRW_CONTROL_QUAD3ENABLE                 (1 << 8)  /* Enable quadratic coupling of limiters 5 and 6 */

#define R_DRW_CONTROL_QUAD2ENABLE                 (1 << 7)  /* Enable quadratic coupling of limiters 3 and 4 */

#define R_DRW_CONTROL_QUAD1ENABLE                 (1 << 6)  /* Enable quadratic coupling of limiters 1 and 2 */

#define R_DRW_CONTROL_LIM6ENABLE                  (1 << 5)  /* Enable limiter 6 */

#define R_DRW_CONTROL_LIM5ENABLE                  (1 << 4)  /* Enable limiter 5 */

#define R_DRW_CONTROL_LIM4ENABLE                  (1 << 3)  /* Enable limiter 4 */

#define R_DRW_CONTROL_LIM3ENABLE                  (1 << 2)  /* Enable limiter 3  */

#define R_DRW_CONTROL_LIM2ENABLE                  (1 << 1)  /* Enable limiter 2  */

#define R_DRW_CONTROL_LIM1ENABLE                  (1 << 0)  /* Enable limiter 1  */

/* CONTROL2 Register bit definitions */
#define R_DRW_CONTROL2_RLEPIXELWIDTH_SHIFT        (30)  /* Texel width for RLE unit */
#define R_DRW_CONTROL2_RLEPIXELWIDTH_MASK         0xc0000000
#  define R_DRW_CONTROL2_RLEPIXELWIDTH_00                 (0 << R_DRW_CONTROL2_RLEPIXELWIDTH_SHIFT)  /* 1 byte per texel */
#  define R_DRW_CONTROL2_RLEPIXELWIDTH_01                 (1 << R_DRW_CONTROL2_RLEPIXELWIDTH_SHIFT)  /* 2 byte per texel */
#  define R_DRW_CONTROL2_RLEPIXELWIDTH_10                 (2 << R_DRW_CONTROL2_RLEPIXELWIDTH_SHIFT)  /* 3 byte per texel */
#  define R_DRW_CONTROL2_RLEPIXELWIDTH_11                 (3 << R_DRW_CONTROL2_RLEPIXELWIDTH_SHIFT)  /* 4 byte per texel */

#define R_DRW_CONTROL2_BDIA                       (1 << 29)  /* Blend destination factor inverted in alpha channel (USEACB = 1) */

#define R_DRW_CONTROL2_BSIA                       (1 << 28)  /* Blend source factor inverted in alpha channel (USEACB = 1) */

#define R_DRW_CONTROL2_CLUTFORMAT                 (1 << 27)  /* Format of the CLUT */

#define R_DRW_CONTROL2_COLKEYENABLE               (1 << 26)  /* color keying enable */

#define R_DRW_CONTROL2_CLUTENABLE                 (1 << 25)  /* CLUT enable */

#define R_DRW_CONTROL2_RLEENABLE                  (1 << 24)  /* RLE enable */

#define R_DRW_CONTROL2_WRITEALPHA_SHIFT           (22)  /* Writeback alpha source for framebufferSet the 'alpha source' for the framebuffer(USEACB = 0)Blend alpha in color 2 instead of framebuffer alpha((USEACB = 1))In not alpha channel blending mode (USEACB = 0):Set the 'alpha source' for the framebuffer.In alpha channel blending mode (USEACB = 1):Blend alpha in color 2 instead of framebuffer alpha00B:  BC2A = 1: use alpha from framebuffer as destination (DST_A)else: BC2A = 0: use alpha in color 2 as destination (DST_A) */
#define R_DRW_CONTROL2_WRITEALPHA_MASK            0xc00000
#  define R_DRW_CONTROL2_WRITEALPHA_00                    (0 << R_DRW_CONTROL2_WRITEALPHA_SHIFT)  /* use alpha from color 2 */
#  define R_DRW_CONTROL2_WRITEALPHA_01                    (1 << R_DRW_CONTROL2_WRITEALPHA_SHIFT)  /* use source alpha (pixel coverage) */
#  define R_DRW_CONTROL2_WRITEALPHA_10                    (2 << R_DRW_CONTROL2_WRITEALPHA_SHIFT)  /* use 0.0 as alpha */
#  define R_DRW_CONTROL2_WRITEALPHA_11                    (3 << R_DRW_CONTROL2_WRITEALPHA_SHIFT)  /* use alpha from framebuffer    */

#define R_DRW_CONTROL2_WRITEFORMAT10_SHIFT        (20)  /* Pixel format of the framebuffer */
#define R_DRW_CONTROL2_WRITEFORMAT10_MASK         0x300000
#  define R_DRW_CONTROL2_WRITEFORMAT10_00                 (0 << R_DRW_CONTROL2_WRITEFORMAT10_SHIFT)  /* 8bpp a(8)0 */
#  define R_DRW_CONTROL2_WRITEFORMAT10_01                 (1 << R_DRW_CONTROL2_WRITEFORMAT10_SHIFT)  /* 16bpp RGB(565)  */
#  define R_DRW_CONTROL2_WRITEFORMAT10_10                 (2 << R_DRW_CONTROL2_WRITEFORMAT10_SHIFT)  /* 32bpp aRGB(8888) */
#  define R_DRW_CONTROL2_WRITEFORMAT10_11                 (3 << R_DRW_CONTROL2_WRITEFORMAT10_SHIFT)  /* 16bpp aRGB(4444)  */

#define R_DRW_CONTROL2_READFORMAT10_SHIFT         (18)  /* Pixel format of the texture buffer{READFORMAT32,READFORMAT10}0000: 8 bpp a(8)0001: 16 bpp RGB(565)0010: 32 bpp aRGB(8888)0011: 16 bpp aRGB(4444)0100: 16 bpp aRGB(1555)0101: 8 bpp aCLUT(44) 4 bit alpha and 4 bit indexed color1001: 8 bpp CLUT(8)/I(8), 8 bit indexed color/luminance1010: 4 bpp CLUT(4)/I(4), 4 bit indexed color/luminance1011: 2 bpp CLUT(2)/I(2), 2 bit indexed color/luminance 1100: 1 bpp CLUT(1)/I(1), 1 bit indexed color/luminance */
#define R_DRW_CONTROL2_READFORMAT10_MASK          0xc0000
#  define R_DRW_CONTROL2_READFORMAT10_00                  (0 << R_DRW_CONTROL2_READFORMAT10_SHIFT)  /* 8 bpp a(8) (READFORMAT32=00) / 16 bpp aRGB(1555)  (READFORMAT32=01) / 1 bpp CLUT(1)/I(1), 1 bit indexed color/luminance  (READFORMAT32=11) */
#  define R_DRW_CONTROL2_READFORMAT10_01                  (1 << R_DRW_CONTROL2_READFORMAT10_SHIFT)  /* 16 bpp RGB(565)  (READFORMAT32=00) / 8 bpp aCLUT(44) 4 bit alpha and 4 bit indexed color  (READFORMAT32=01) / 8 bpp CLUT(8)/I(8), 8 bit indexed color/luminance  (READFORMAT32=10)  */
#  define R_DRW_CONTROL2_READFORMAT10_10                  (2 << R_DRW_CONTROL2_READFORMAT10_SHIFT)  /* 32 bpp aRGB(8888) (READFORMAT32=00)  / 4 bpp CLUT(4)/I(4), 4 bit indexed color/luminance (READFORMAT32=10)  */
#  define R_DRW_CONTROL2_READFORMAT10_11                  (3 << R_DRW_CONTROL2_READFORMAT10_SHIFT)  /* 16 bpp aRGB(4444)  (READFORMAT32=00) / 2 bpp CLUT(2)/I(2), 2 bit indexed color/luminance  (READFORMAT32=10)  */

#define R_DRW_CONTROL2_TEXTUREFILTERY             (1 << 17)  /* Linear filtering on texture V axis */

#define R_DRW_CONTROL2_TEXTUREFILTERX             (1 << 16)  /* Linear filtering on texture U axis */

#define R_DRW_CONTROL2_TEXTURECLAMPY              (1 << 15)  /* Calculating V limiter outside use textureThe bit describes what happens if the V limiter (y direction in texture space) calculates a V value outside of the used texture */

#define R_DRW_CONTROL2_TEXTURECLAMPX              (1 << 14)  /* Calculating U limiter outside use textureThe bit describes what happens if the U limiter (x direction in texture space) calculates a U value outside of the used texture */

#define R_DRW_CONTROL2_BC2                        (1 << 13)  /* Blend color 2 instead of framebuffer pixel */

#define R_DRW_CONTROL2_BDI                        (1 << 12)  /* Blend destination factor is inverteddst factor will be inverted (meaning 1-a or 1-1 depending on BDF) */

#define R_DRW_CONTROL2_BSI                        (1 << 11)  /* Blend source factor is invertedsrc factor will be inverted (meaning 1-a or 1-1 depending on BSF) */

#define R_DRW_CONTROL2_BDF                        (1 << 10)  /* Blend destination factordst factor is alpha (factor is 1 per default) */

#define R_DRW_CONTROL2_BSF                        (1 << 9)  /* Blend source factorsrc factor is alpha (factor is 1 per default) */

#define R_DRW_CONTROL2_WRITEFORMAT2               (1 << 8)  /* Bit 3 of framebuffer pixel formatSee WRITEFORMAT above description. */

#define R_DRW_CONTROL2_BDFA                       (1 << 7)  /* Blend destinetion factor  for alpha channel in alpha channel blending mode (USEACB = 1) */

#define R_DRW_CONTROL2_BSFA                       (1 << 6)  /* Blend source factor  for alpha channel in alpha channel blending mode (USEACB = 1) */

#define R_DRW_CONTROL2_READFORMAT32_SHIFT         (4)  /* Bit 4 and 3 of the texture buffer format.See READFORMAT above for description */
#define R_DRW_CONTROL2_READFORMAT32_MASK          0x30

#define R_DRW_CONTROL2_USEACB                     (1 << 3)  /* Alpha blend mode */

#define R_DRW_CONTROL2_PATTERNSOURCEL5            (1 << 2)  /* Limiter 5 is used as pattern index instead of the default U limiter.Limiter 5 can be combined with limiter 6 to form a quadratic limiter which can be used to make quadratic pattern functions to draw radial patterns. */

#define R_DRW_CONTROL2_TEXTUREENABLE              (1 << 1)  /* Pixel source is read from texture and used as an alpha to blend between COLOR1 and COLOR2 */

#define R_DRW_CONTROL2_PATTERNENABLE              (1 << 0)  /* Pixel source is a pattern color (blend of COLOR1 and COLOR2 depending on PATTERN and pattern index) */

/* IRQCTL Register bit definitions */
#define R_DRW_IRQCTL_BUSIRQCLR                    (1 << 5)  /* Clear bus error interrupt BUSIRQ */

#define R_DRW_IRQCTL_BUSIRQEN                     (1 << 4)  /* BUSIRQ interrupt mask enable */

#define R_DRW_IRQCTL_DLISTIRQCLR                  (1 << 3)  /* Clear display list interrupt DLISTIRQ */

#define R_DRW_IRQCTL_ENUMIRQCLR                   (1 << 2)  /* Clear enumeration interrupt ENUMIRQ */

#define R_DRW_IRQCTL_DLISTIRQEN                   (1 << 1)  /* DLISTIRQ interrupt mask enable */

#define R_DRW_IRQCTL_ENUMIRQEN                    (1 << 0)  /* ENUMIRQ interrupt mask enable */

/* CACHECTL Register bit definitions */
#define R_DRW_CACHECTL_CFLUSHTX                   (1 << 3)  /* Flush texture cache */

#define R_DRW_CACHECTL_CENABLETX                  (1 << 2)  /* Texture cache enable */

#define R_DRW_CACHECTL_CFLUSHFX                   (1 << 1)  /* Flush framebuffer cache */

#define R_DRW_CACHECTL_CENABLEFX                  (1 << 0)  /* Framebuffer cache enable */

/* STATUS Register bit definitions */
#define R_DRW_STATUS_BUSERRMDL                    (1 << 10)  /* display list bus error interrupt triggered */

#define R_DRW_STATUS_BUSERRMTXMRL                 (1 << 9)  /* texture bus error interrupt triggered */

#define R_DRW_STATUS_BUSERRMFB                    (1 << 8)  /* framebuffer bus error interrupt triggered */

#define R_DRW_STATUS_BUSIRQ                       (1 << 6)  /* bus error interrupt triggered */

#define R_DRW_STATUS_DLISTIRQ                     (1 << 5)  /* display list finished interrupt triggered */

#define R_DRW_STATUS_ENUMIRQ                      (1 << 4)  /* enumeration finished interrupt triggered */

#define R_DRW_STATUS_DLISTACTIVE                  (1 << 3)  /* Display list reader status */

#define R_DRW_STATUS_CACHEDIRTY                   (1 << 2)  /* Framebuffer cache status */

#define R_DRW_STATUS_BUSYWRITE                    (1 << 1)  /* Framebuffer writeback status */

#define R_DRW_STATUS_BUSYENUM                     (1 << 0)  /* Enumeration unit status */

/* HWREVISION Register bit definitions */
#define R_DRW_HWREVISION_ACBLEND                  (1 << 27)  /* Alpha channel blending feature  */

#define R_DRW_HWREVISION_COLORKEY                 (1 << 25)  /* Colorkey feature  */

#define R_DRW_HWREVISION_TEXCLUT256               (1 << 24)  /* Texture CLUT feature  */

#define R_DRW_HWREVISION_RLEUNIT                  (1 << 23)  /* RLE unit feature  */

#define R_DRW_HWREVISION_TEXCLU                   (1 << 21)  /* Texture CLUT with 16 or 256 entries feature  */

#define R_DRW_HWREVISION_PERFCOUNT                (1 << 20)  /* Two performance counter feature */

#define R_DRW_HWREVISION_TXCACHE                  (1 << 19)  /* Texture cache feature */

#define R_DRW_HWREVISION_FBCACHE                  (1 << 18)  /* Framebuffer cache feature */

#define R_DRW_HWREVISION_DLR                      (1 << 17)  /* Display list reader feature */

#define R_DRW_HWREVISION_REV_SHIFT                (0)  /* Revision number */
#define R_DRW_HWREVISION_REV_MASK                 0xfff

/* COLOR1 Register bit definitions */
#define R_DRW_COLOR1_COLOR1A_SHIFT                (24)  /* Alpha channel of color 1(0x00: transparent. . .  0xFF: opaque) */
#define R_DRW_COLOR1_COLOR1A_MASK                 0xff000000

#define R_DRW_COLOR1_COLOR1R_SHIFT                (16)  /* Red channel of color 1 */
#define R_DRW_COLOR1_COLOR1R_MASK                 0xff0000

#define R_DRW_COLOR1_COLOR1G_SHIFT                (8)  /* Green channel of color 1 */
#define R_DRW_COLOR1_COLOR1G_MASK                 0xff00

#define R_DRW_COLOR1_COLOR1B_SHIFT                (0)  /* Blue channel of color 1 */
#define R_DRW_COLOR1_COLOR1B_MASK                 0xff

/* COLOR2 Register bit definitions */
#define R_DRW_COLOR2_COLOR2A_SHIFT                (24)  /* Alpha channel of color 2(0x00: transparent. . .   0xFF: opaque) */
#define R_DRW_COLOR2_COLOR2A_MASK                 0xff000000

#define R_DRW_COLOR2_COLOR2R_SHIFT                (16)  /* Red channel of color 2 */
#define R_DRW_COLOR2_COLOR2R_MASK                 0xff0000

#define R_DRW_COLOR2_COLOR2G_SHIFT                (8)  /* Green channel of color 2 */
#define R_DRW_COLOR2_COLOR2G_MASK                 0xff00

#define R_DRW_COLOR2_COLOR2B_SHIFT                (0)  /* Blue channel of color 2 */
#define R_DRW_COLOR2_COLOR2B_MASK                 0xff

/* PATTERN Register bit definitions */
#define R_DRW_PATTERN_PATTERN_SHIFT               (0)  /* Bitmap of the pattern */
#define R_DRW_PATTERN_PATTERN_MASK                0xff

/* LSTART Register bit definitions */
#define R_DRW_LSTART_LSTART_SHIFT                 (0)  /* Start value of the n'th limiter(n=1-6) */
#define R_DRW_LSTART_LSTART_MASK                  0xffffffff

/* LXADD Register bit definitions */
#define R_DRW_LXADD_LXADD_SHIFT                   (0)  /* X-axis increment */
#define R_DRW_LXADD_LXADD_MASK                    0xffffffff

/* LYADD Register bit definitions */
#define R_DRW_LYADD_LYADD_SHIFT                   (0)  /* Y-axis increment */
#define R_DRW_LYADD_LYADD_MASK                    0xffffffff

/* LBAND Register bit definitions */
#define R_DRW_LBAND_LBAND_SHIFT                   (0)  /* Limiter m band width parameter */
#define R_DRW_LBAND_LBAND_MASK                    0xffffffff

/* TEXORIGIN Register bit definitions */
#define R_DRW_TEXORIGIN_TEXORIGIN_SHIFT           (0)  /* Texture base address */
#define R_DRW_TEXORIGIN_TEXORIGIN_MASK            0xffffffff

/* TEXPITCH Register bit definitions */
#define R_DRW_TEXPITCH_TEXPITCH_SHIFT             (0)  /* Texels per texture linevalid range: 0 to 2048 */
#define R_DRW_TEXPITCH_TEXPITCH_MASK              0xffffffff

/* TEXMASK Register bit definitions */
#define R_DRW_TEXMASK_TEXVMASK_SHIFT              (11)  /* V maskSet TEXVMASK[20:0] = TEXPITCH * (texture_height - 1).In texture wrapping mode (CONTROL2.TEXTURECLAMPY = 0): texture_height must be a power of 2In texture clamping mode (CONTROL2.TEXTURECLAMPY = 1):all heights up to 1024 are allowed. */
#define R_DRW_TEXMASK_TEXVMASK_MASK               0xfffff800

#define R_DRW_TEXMASK_TEXUMASK_SHIFT              (0)  /* U maskSet TEXUMASK[10:0] = texture_width -1In texture wrapping mode (CONTROL2.TEXTURECLAMPX = 0): texture_width must be a power of 2.In texture clamping mode (CONTROL2.TEXTURECLAMPX = 1):all widths up to 2048 are allowed. */
#define R_DRW_TEXMASK_TEXUMASK_MASK               0x7ff

/* LUSTART Register bit definitions */
#define R_DRW_LUSTART_LUSTART_SHIFT               (0)  /* U limiter start value */
#define R_DRW_LUSTART_LUSTART_MASK                0xffffffff

/* LUXADD Register bit definitions */
#define R_DRW_LUXADD_LUXADD_SHIFT                 (0)  /* U limiter x-axis increment */
#define R_DRW_LUXADD_LUXADD_MASK                  0xffffffff

/* LUYADD Register bit definitions */
#define R_DRW_LUYADD_LUYADD_SHIFT                 (0)  /* U limiter y-axis increment */
#define R_DRW_LUYADD_LUYADD_MASK                  0xffffffff

/* LVSTARTI Register bit definitions */
#define R_DRW_LVSTARTI_LVSTARTI_SHIFT             (0)  /* V limiter start value integer part */
#define R_DRW_LVSTARTI_LVSTARTI_MASK              0xffffffff

/* LVSTARTF Register bit definitions */
#define R_DRW_LVSTARTF_LVSTARTF_SHIFT             (0)  /* V limiter start value fractional part */
#define R_DRW_LVSTARTF_LVSTARTF_MASK              0xffff

/* LVXADDI Register bit definitions */
#define R_DRW_LVXADDI_LVXADDI_SHIFT               (0)  /* V limiter x-axis increment integer part */
#define R_DRW_LVXADDI_LVXADDI_MASK                0xffffffff

/* LVYADDI Register bit definitions */
#define R_DRW_LVYADDI_LVYADDI_SHIFT               (0)  /* V limiter y-axis increment integer part */
#define R_DRW_LVYADDI_LVYADDI_MASK                0xffffffff

/* LVYXADDF Register bit definitions */
#define R_DRW_LVYXADDF_LVYADDF_SHIFT              (16)  /* V y limiter increment fractional part */
#define R_DRW_LVYXADDF_LVYADDF_MASK               0xffff0000

#define R_DRW_LVYXADDF_LVXADDF_SHIFT              (0)  /* V xlimiter increment fractional part */
#define R_DRW_LVYXADDF_LVXADDF_MASK               0xffff

/* TEXCLADDR Register bit definitions */
#define R_DRW_TEXCLADDR_CLADDR_SHIFT              (0)  /* Texture CLUT start address for indexed texture format */
#define R_DRW_TEXCLADDR_CLADDR_MASK               0xff

/* TEXCLDATA Register bit definitions */
#define R_DRW_TEXCLDATA_CLDATA_SHIFT              (0)  /* Texture CLUT data for Indexed texture format */
#define R_DRW_TEXCLDATA_CLDATA_MASK               0xffffffff

/* TEXCLOFFSET Register bit definitions */
#define R_DRW_TEXCLOFFSET_CLOFFSET_SHIFT          (0)  /* Texture CLUT offset for Indexed texture format. CLOFFSET[7:0] is or'ed with the original index */
#define R_DRW_TEXCLOFFSET_CLOFFSET_MASK           0xff

/* COLKEY Register bit definitions */
#define R_DRW_COLKEY_COLKEYR_SHIFT                (16)  /* Red channel of color key */
#define R_DRW_COLKEY_COLKEYR_MASK                 0xff0000

#define R_DRW_COLKEY_COLKEYG_SHIFT                (8)  /* Green channel of color key */
#define R_DRW_COLKEY_COLKEYG_MASK                 0xff00

#define R_DRW_COLKEY_COLKEYB_SHIFT                (0)  /* Blue channel of color key */
#define R_DRW_COLKEY_COLKEYB_MASK                 0xff

/* SIZE Register bit definitions */
#define R_DRW_SIZE_SIZEY_SHIFT                    (16)  /* Height of the bounding box in pixelsvalid range: 0 to 1024 */
#define R_DRW_SIZE_SIZEY_MASK                     0xffff0000

#define R_DRW_SIZE_SIZEX_SHIFT                    (0)  /*  Width of the bounding box in pixelsvalid range: 0 to 1024 */
#define R_DRW_SIZE_SIZEX_MASK                     0xffff

/* PITCH Register bit definitions */
#define R_DRW_PITCH_SSD_SHIFT                     (16)  /* Spanstore delay */
#define R_DRW_PITCH_SSD_MASK                      0xffff0000

#define R_DRW_PITCH_PITCH_SHIFT                   (0)  /* pitch of the framebuffer. A negative width can be used to render bottom-up instead of top-down */
#define R_DRW_PITCH_PITCH_MASK                    0xffff

/* ORIGIN Register bit definitions */
#define R_DRW_ORIGIN_ORIGIN_SHIFT                 (0)  /* Address of the first pixel in framebuffer */
#define R_DRW_ORIGIN_ORIGIN_MASK                  0xffffffff

/* DLISTSTART Register bit definitions */
#define R_DRW_DLISTSTART_DLISTSTART_SHIFT         (0)  /* Display list start address */
#define R_DRW_DLISTSTART_DLISTSTART_MASK          0xffffffff

/* PERFTRIGGER Register bit definitions */
#define R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT      (16)  /* Selects the internal event that will increment PERFCOUNT2 register */
#define R_DRW_PERFTRIGGER_PERFTRIGGER2_MASK       0xffff0000
#  define R_DRW_PERFTRIGGER_PERFTRIGGER2_0X00             (0 << R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT)  /* disable performance counter  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER2_0X01             (1 << R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT)  /* 2D Drawing Engine active cycles  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER2_0X02             (2 << R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT)  /* framebuffer read access  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER2_0X03             (3 << R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT)  /* framebuffer write access  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER2_0X04             (4 << R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT)  /* texture read access  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER2_0X05             (5 << R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT)  /* invisible pixels (enumerated but selected with alpha 0percent)  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER2_0X06             (6 << R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT)  /* invisible pixels while internal FIFO is empty (lost cycles)  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER2_0X07             (7 << R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT)  /* display list reader active cycles  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER2_0X08             (8 << R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT)  /* framebuffer read hits */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER2_0X09             (9 << R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT)  /* framebuffer read misses */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER2_0X0A             (10 << R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT)  /* framebuffer write hits  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER2_0X0B             (11 << R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT)  /* framebuffer write misses  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER2_0X0C             (12 << R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT)  /* texture read hits  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER2_0X0D             (13 << R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT)  /* texture read misses  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER2_0X1F             (31 << R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT)  /* every clock cycle (for use as timer)  */

#define R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT      (0)  /* Selects the internal event that will increment PERFCOUNT1 register. */
#define R_DRW_PERFTRIGGER_PERFTRIGGER1_MASK       0xffff
#  define R_DRW_PERFTRIGGER_PERFTRIGGER1_0X00             (0 << R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT)  /* disable performance counter  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER1_0X01             (1 << R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT)  /* 2D Drawing Engine active cycles  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER1_0X02             (2 << R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT)  /* framebuffer read access  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER1_0X03             (3 << R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT)  /* framebuffer write access  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER1_0X04             (4 << R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT)  /* texture read access  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER1_0X05             (5 << R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT)  /* invisible pixels (enumerated but selected with alpha 0percent)  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER1_0X06             (6 << R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT)  /* invisible pixels while internal FIFO is empty (lost cycles)  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER1_0X07             (7 << R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT)  /* display list reader active cycles  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER1_0X08             (8 << R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT)  /* framebuffer read hits */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER1_0X09             (9 << R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT)  /* framebuffer read misses */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER1_0X0A             (10 << R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT)  /* framebuffer write hits  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER1_0X0B             (11 << R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT)  /* framebuffer write misses  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER1_0X0C             (12 << R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT)  /* texture read hits  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER1_0X0D             (13 << R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT)  /* texture read misses  */
#  define R_DRW_PERFTRIGGER_PERFTRIGGER1_0X1F             (31 << R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT)  /* every clock cycle (for use as timer)  */

/* PERFCOUNT Register bit definitions */
#define R_DRW_PERFCOUNT_PERFCOUNT_SHIFT           (0)  /* Counter value.The counter is reset by writing PERFCOUNT = 0000 0000H. */
#define R_DRW_PERFCOUNT_PERFCOUNT_MASK            0xffffffff

/* DBWER Register bit definitions */
#define R_DRW_DBWER_BWE                           (1 << 2)  /* Bufferable Write Enable */


/* Maximum number of channels */

#define DRW_MAX_CHANNELS    6

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DRW_H */

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
#define R_DRW_CONTROL2_OFFSET                     0x00000004  /* Surface Control Register */
#define R_DRW_HWREVISION_OFFSET                   0x00000004  /* Hardware Version and Feature Set ID Register */
/* L%sSTART Registers (1-6) */
#define R_DRW_LSTART_OFFSET(m)                    (0x00000010 + ((m) * 0x00000004))  /* Limiter %s Start Value Register (n = 1 to 6) */
/* L%sXADD Registers (1-6) */
#define R_DRW_LXADD_OFFSET(m)                     (0x00000028 + ((m) * 0x00000004))  /* Limiter %s X-Axis Increment Register(n = 1 to 6) */
/* L%sYADD Registers (1-6) */
#define R_DRW_LYADD_OFFSET(m)                     (0x00000040 + ((m) * 0x00000004))  /* Limiter %s Y-Axis Increment Register(n = 1 to 6) */
/* L%sBAND Registers (1-2) */
#define R_DRW_LBAND_OFFSET(m)                     (0x00000058 + ((m) * 0x00000004))  /* Limiter m Band Width Parameter Register(n = 1, 2) */
#define R_DRW_COLOR1_OFFSET                       0x00000064  /* Base Color Register */
#define R_DRW_COLOR2_OFFSET                       0x00000068  /* Secondary Color Register */
#define R_DRW_PATTERN_OFFSET                      0x00000074  /* Pattern Register */
#define R_DRW_SIZE_OFFSET                         0x00000078  /* Bounding Box Dimension Register */
#define R_DRW_PITCH_OFFSET                        0x0000007c  /* Framebuffer Pitch And Spanstore Delay Register */
#define R_DRW_ORIGIN_OFFSET                       0x00000080  /* Framebuffer Base Address Register */
#define R_DRW_LUSTART_OFFSET                      0x00000090  /* U Limiter Start Value Register */
#define R_DRW_LUXADD_OFFSET                       0x00000094  /* U Limiter X-Axis Increment Register */
#define R_DRW_LUYADD_OFFSET                       0x00000098  /* U Limiter Y-Axis Increment Register */
#define R_DRW_LVSTARTI_OFFSET                     0x0000009c  /* V Limiter Start Value Integer Part Register */
#define R_DRW_LVSTARTF_OFFSET                     0x000000a0  /* V Limiter Start Value Fractional Part Register */
#define R_DRW_LVXADDI_OFFSET                      0x000000a4  /* V Limiter X-Axis Increment Integer Part Register */
#define R_DRW_LVYADDI_OFFSET                      0x000000a8  /* V Limiter Y-Axis Increment Integer Part Register */
#define R_DRW_LVYXADDF_OFFSET                     0x000000ac  /* V Limiter Increment Fractional Parts Register */
#define R_DRW_TEXPITCH_OFFSET                     0x000000b4  /* Texels Per Texture Line Register */
#define R_DRW_TEXMASK_OFFSET                      0x000000b8  /* Texture Size or Texture Address Mask Register */
#define R_DRW_TEXORIGIN_OFFSET                    0x000000bc  /* Texture Base Address Register */
#define R_DRW_IRQCTL_OFFSET                       0x000000c0  /* Interrupt Control Register */
#define R_DRW_CACHECTL_OFFSET                     0x000000c4  /* Cache Control Register */
#define R_DRW_DLISTSTART_OFFSET                   0x000000c8  /* Display List Start Address Register */
#define R_DRW_PERFCOUNT1_OFFSET                   0x000000cc  /* Performance Counter 1 */
#define R_DRW_PERFCOUNT2_OFFSET                   0x000000d0  /* Performance Counter 2 */
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
#define R_DRW_PERFCOUNT1                          (R_DRW_BASE + R_DRW_PERFCOUNT1_OFFSET)
#define R_DRW_PERFCOUNT2                          (R_DRW_BASE + R_DRW_PERFCOUNT2_OFFSET)
#define R_DRW_PERFTRIGGER                         (R_DRW_BASE + R_DRW_PERFTRIGGER_OFFSET)
#define R_DRW_TEXCLADDR                           (R_DRW_BASE + R_DRW_TEXCLADDR_OFFSET)
#define R_DRW_TEXCLDATA                           (R_DRW_BASE + R_DRW_TEXCLDATA_OFFSET)
#define R_DRW_TEXCLOFFSET                         (R_DRW_BASE + R_DRW_TEXCLOFFSET_OFFSET)
#define R_DRW_COLKEY                              (R_DRW_BASE + R_DRW_COLKEY_OFFSET)
#define R_DRW_DBWER                               (R_DRW_BASE + R_DRW_DBWER_OFFSET)

/* Register bit definitions */
/* CONTROL Register bit definitions */
#define R_DRW_CONTROL_LIM1ENABLE                  (1 << 0)  /* Enable Limiter 1 */

#define R_DRW_CONTROL_LIM2ENABLE                  (1 << 1)  /* Enable Limiter 2 */

#define R_DRW_CONTROL_LIM3ENABLE                  (1 << 2)  /* Enable Limiter 3 */

#define R_DRW_CONTROL_LIM4ENABLE                  (1 << 3)  /* Enable Limiter 4 */

#define R_DRW_CONTROL_LIM5ENABLE                  (1 << 4)  /* Enable Limiter 5 */

#define R_DRW_CONTROL_LIM6ENABLE                  (1 << 5)  /* Enable Limiter 6 */

#define R_DRW_CONTROL_QUAD1ENABLE                 (1 << 6)  /* Enable Quadratic Coupling of Limiters 1 and 2 */

#define R_DRW_CONTROL_QUAD2ENABLE                 (1 << 7)  /* Enable Quadratic Coupling of Limiters 3 and 4 */

#define R_DRW_CONTROL_QUAD3ENABLE                 (1 << 8)  /* Enable Quadratic Coupling of Limiters 5 and 6 */

#define R_DRW_CONTROL_LIM1THRESHOLD               (1 << 9)  /* Enable Limiter 1 Threshold Mode */

#define R_DRW_CONTROL_LIM2THRESHOLD               (1 << 10)  /* Enable Limiter 2 Threshold Mode */

#define R_DRW_CONTROL_LIM3THRESHOLD               (1 << 11)  /* Enable Limiter 3 Threshold Mode */

#define R_DRW_CONTROL_LIM4THRESHOLD               (1 << 12)  /* Enable Limiter 4 Threshold Mode */

#define R_DRW_CONTROL_LIM5THRESHOLD               (1 << 13)  /* Enable Limiter 5 Threshold Mode */

#define R_DRW_CONTROL_LIM6THRESHOLD               (1 << 14)  /* Enable Limiter 6 Threshold Mode */

#define R_DRW_CONTROL_BAND1ENABLE                 (1 << 15)  /* Enable Band Post Process for Limiter 1 */

#define R_DRW_CONTROL_BAND2ENABLE                 (1 << 16)  /* Enable Band Post Process for Limiter 2 */

#define R_DRW_CONTROL_UNION12                     (1 << 17)  /* Combine Limiters 1 and 2 as Union */

#define R_DRW_CONTROL_UNION34                     (1 << 18)  /* Combine Limiters 3 and 4 as Union */

#define R_DRW_CONTROL_UNION56                     (1 << 19)  /* Combine Limiters 5 and 6 as Union */

#define R_DRW_CONTROL_UNIONAB                     (1 << 20)  /* Combine Outputs A and B as Union */

#define R_DRW_CONTROL_UNIONCD                     (1 << 21)  /* Combine Outputs C and D as Union */

#define R_DRW_CONTROL_SPANABORT                   (1 << 22)  /* Spanabort */

#define R_DRW_CONTROL_SPANSTORE                   (1 << 23)  /* Spanstore */

/* STATUS Register bit definitions */
#define R_DRW_STATUS_BUSYENUM                     (1 << 0)  /* Enumeration Unit Status */

#define R_DRW_STATUS_BUSYWRITE                    (1 << 1)  /* Framebuffer Writeback Status */

#define R_DRW_STATUS_CACHEDIRTY                   (1 << 2)  /* Framebuffer Cache Status */

#define R_DRW_STATUS_DLISTACTIVE                  (1 << 3)  /* Display List Reader Status */

#define R_DRW_STATUS_ENUMIRQ                      (1 << 4)  /* Enumeration Interrupt Triggered */

#define R_DRW_STATUS_DLISTIRQ                     (1 << 5)  /* Display List Interrupt Triggered */

#define R_DRW_STATUS_BUSIRQ                       (1 << 6)  /* Bus Error Interrupt Triggered */

#define R_DRW_STATUS_BUSERRMFB                    (1 << 8)  /* Framebuffer Bus Error Interrupt Triggered */

#define R_DRW_STATUS_BUSERRMTXMRL                 (1 << 9)  /* Texture Bus Error Interrupt Triggered */

#define R_DRW_STATUS_BUSERRMDL                    (1 << 10)  /* Display List Bus Error Interrupt Triggered */

/* CONTROL2 Register bit definitions */
#define R_DRW_CONTROL2_PATTERNENABLE              (1 << 0)  /* Pattern Color Enable for Pixel Source */

#define R_DRW_CONTROL2_TEXTUREENABLE              (1 << 1)  /* Texture Enable for Pixel Source */

#define R_DRW_CONTROL2_PATTERNSOURCEL5            (1 << 2)  /* Limiter 5 Enable for Pattern Index */

#define R_DRW_CONTROL2_USEACB                     (1 << 3)  /* Alpha Blend Mode */

#define R_DRW_CONTROL2_READFORMAT_H_SHIFT         (4)  /* Texture Format Descriptor */
#define R_DRW_CONTROL2_READFORMAT_H_MASK          0x30

#define R_DRW_CONTROL2_BSFA                       (1 << 6)  /* Blend Source Factor for Alpha Channel */

#define R_DRW_CONTROL2_BDFA                       (1 << 7)  /* Blend Destination Factor for Alpha Channel */

#define R_DRW_CONTROL2_WRITEFORMAT2               (1 << 8)  /* Writeback Framebuffer Format */

#define R_DRW_CONTROL2_BSF                        (1 << 9)  /* Blend Source Factor */

#define R_DRW_CONTROL2_BDF                        (1 << 10)  /* Blend Destination Factor */

#define R_DRW_CONTROL2_BSI                        (1 << 11)  /* Blend Source Factor Inverted */

#define R_DRW_CONTROL2_BDI                        (1 << 12)  /* Blend Destination Factor Inverted */

#define R_DRW_CONTROL2_BC2                        (1 << 13)  /* Blend color 2 */

#define R_DRW_CONTROL2_TEXTURECLAMPX              (1 << 14)  /* Calculating U Limiter Outside Used Texture */

#define R_DRW_CONTROL2_TEXTURECLAMPY              (1 << 15)  /* Calculating V Limiter Outside Used Texture */

#define R_DRW_CONTROL2_TEXTUREFILTERX             (1 << 16)  /* Linear Filtering on Texture U Axis */

#define R_DRW_CONTROL2_TEXTUREFILTERY             (1 << 17)  /* Linear Filtering on Texture V Axis */

#define R_DRW_CONTROL2_READFORMAT_L_SHIFT         (18)  /* Texture Format Descriptor */
#define R_DRW_CONTROL2_READFORMAT_L_MASK          0xc0000

#define R_DRW_CONTROL2_WRITEFORMAT_SHIFT          (20)  /* Writeback Framebuffer Format */
#define R_DRW_CONTROL2_WRITEFORMAT_MASK           0x300000

#define R_DRW_CONTROL2_WRITEALPHA_SHIFT           (22)  /* Writeback Alpha Source for Framebuffer */
#define R_DRW_CONTROL2_WRITEALPHA_MASK            0xc00000
#  define R_DRW_CONTROL2_WRITEALPHA_00                    (0 << R_DRW_CONTROL2_WRITEALPHA_SHIFT)  /* (USEACB = 0) Use alpha from color 2 (USEACB = 0) (USEACB = 1) BC2A = 1: Use alpha in color 2 as destination (DST_A)  */
#  define R_DRW_CONTROL2_WRITEALPHA_01                    (1 << R_DRW_CONTROL2_WRITEALPHA_SHIFT)  /* (USEACB = 0) Use source alpha (pixel coverage) (USEACB = 1) BC2A = 0: Use alpha from framebuffer as destination (DST_A)  */
#  define R_DRW_CONTROL2_WRITEALPHA_10                    (2 << R_DRW_CONTROL2_WRITEALPHA_SHIFT)  /* (USEACB = 0) Use 0.0 as alpha (USEACB = 1) BC2A = 0: Use alpha from framebuffer as destination (DST_A)  */
#  define R_DRW_CONTROL2_WRITEALPHA_10                    (2 << R_DRW_CONTROL2_WRITEALPHA_SHIFT)  /* (USEACB = 0) Use alpha from framebuffer (USEACB = 1) BC2A = 0: Use alpha from framebuffer as destination (DST_A)  */

#define R_DRW_CONTROL2_RLEENABLE                  (1 << 24)  /* RLE Enable */

#define R_DRW_CONTROL2_CLUTENABLE                 (1 << 25)  /* CLUT Enable */

#define R_DRW_CONTROL2_COLKEYENABLE               (1 << 26)  /* Color Keying Enable */

#define R_DRW_CONTROL2_CLUTFORMAT                 (1 << 27)  /* CLUT Format */

#define R_DRW_CONTROL2_BSIA                       (1 << 28)  /* Blend Source Factor Inverted in Alpha Channel */

#define R_DRW_CONTROL2_BDIA                       (1 << 29)  /* Blend Destination Factor Inverted in Alpha Channel */

#define R_DRW_CONTROL2_RLEPIXELWIDTH_SHIFT        (30)  /* Texel Width for RLE Unit */
#define R_DRW_CONTROL2_RLEPIXELWIDTH_MASK         0xc0000000
#  define R_DRW_CONTROL2_RLEPIXELWIDTH_00                 (0 << R_DRW_CONTROL2_RLEPIXELWIDTH_SHIFT)  /* 1 byte per texel */
#  define R_DRW_CONTROL2_RLEPIXELWIDTH_01                 (1 << R_DRW_CONTROL2_RLEPIXELWIDTH_SHIFT)  /* 2 bytes per texel */
#  define R_DRW_CONTROL2_RLEPIXELWIDTH_10                 (2 << R_DRW_CONTROL2_RLEPIXELWIDTH_SHIFT)  /* 3 bytes per texel */
#  define R_DRW_CONTROL2_RLEPIXELWIDTH_11                 (3 << R_DRW_CONTROL2_RLEPIXELWIDTH_SHIFT)  /* 4 bytes per texel */

#define R_DRW_CONTROL2_READFORMAT32_SHIFT         (4)  /* Bit 4 and 3 of the texture buffer format.See READFORMAT above for description */
#define R_DRW_CONTROL2_READFORMAT32_MASK          0x30

#define R_DRW_CONTROL2_READFORMAT10_SHIFT         (18)  /* Pixel format of the texture buffer{READFORMAT32,READFORMAT10}0000: 8 bpp a(8)0001: 16 bpp RGB(565)0010: 32 bpp aRGB(8888)0011: 16 bpp aRGB(4444)0100: 16 bpp aRGB(1555)0101: 8 bpp aCLUT(44) 4 bit alpha and 4 bit indexed color1001: 8 bpp CLUT(8)/I(8), 8 bit indexed color/luminance1010: 4 bpp CLUT(4)/I(4), 4 bit indexed color/luminance1011: 2 bpp CLUT(2)/I(2), 2 bit indexed color/luminance 1100: 1 bpp CLUT(1)/I(1), 1 bit indexed color/luminance */
#define R_DRW_CONTROL2_READFORMAT10_MASK          0xc0000

#define R_DRW_CONTROL2_WRITEFORMAT10_SHIFT        (20)  /* Pixel format of the framebuffer */
#define R_DRW_CONTROL2_WRITEFORMAT10_MASK         0x300000

/* HWREVISION Register bit definitions */
#define R_DRW_HWREVISION_REV_SHIFT                (0)  /* Revision Number of DRW is stored. */
#define R_DRW_HWREVISION_REV_MASK                 0xfff

#define R_DRW_HWREVISION_DLR                      (1 << 17)  /* Display List Reader Available */

#define R_DRW_HWREVISION_FBCACHE                  (1 << 18)  /* Framebuffer Cache Available */

#define R_DRW_HWREVISION_TXCACHE                  (1 << 19)  /* Texture Cache Available */

#define R_DRW_HWREVISION_PERFCOUNT                (1 << 20)  /* Two Performance Counter Available */

#define R_DRW_HWREVISION_TEXCLUT                  (1 << 21)  /* Texture CLUT Available */

#define R_DRW_HWREVISION_RLEUNIT                  (1 << 23)  /* RLE Unit Available */

#define R_DRW_HWREVISION_TEXCLUT256               (1 << 24)  /* Texture CLUT size */

#define R_DRW_HWREVISION_COLORKEY                 (1 << 25)  /* Color Key Available */

#define R_DRW_HWREVISION_ACBLEND                  (1 << 27)  /* Alpha Channel Blending Available */

#define R_DRW_HWREVISION_TEXCLU                   (1 << 21)  /* Texture CLUT with 16 or 256 entries feature */

/* LSTART Register bit definitions */
#define R_DRW_LSTART_LSTART_SHIFT                 (0)  /* Start Value of the nth Limiter */
#define R_DRW_LSTART_LSTART_MASK                  0xffffffff

/* LXADD Register bit definitions */
#define R_DRW_LXADD_LXADD_SHIFT                   (0)  /* X-Axis Increment */
#define R_DRW_LXADD_LXADD_MASK                    0xffffffff

/* LYADD Register bit definitions */
#define R_DRW_LYADD_LYADD_SHIFT                   (0)  /* Y-Axis Increment */
#define R_DRW_LYADD_LYADD_MASK                    0xffffffff

/* LBAND Register bit definitions */
#define R_DRW_LBAND_LBAND_SHIFT                   (0)  /* Limiter m Band Width Parameter */
#define R_DRW_LBAND_LBAND_MASK                    0xffffffff

/* COLOR1 Register bit definitions */
#define R_DRW_COLOR1_COLOR1B_SHIFT                (0)  /* Blue Channel of Color 1 */
#define R_DRW_COLOR1_COLOR1B_MASK                 0xff

#define R_DRW_COLOR1_COLOR1G_SHIFT                (8)  /* Green Channel of Color 1 */
#define R_DRW_COLOR1_COLOR1G_MASK                 0xff00

#define R_DRW_COLOR1_COLOR1R_SHIFT                (16)  /* Red Channel of Color 1 */
#define R_DRW_COLOR1_COLOR1R_MASK                 0xff0000

#define R_DRW_COLOR1_COLOR1A_SHIFT                (24)  /* Alpha Channel of Color 1 */
#define R_DRW_COLOR1_COLOR1A_MASK                 0xff000000

/* COLOR2 Register bit definitions */
#define R_DRW_COLOR2_COLOR2B_SHIFT                (0)  /* Blue Channel of Color 2 */
#define R_DRW_COLOR2_COLOR2B_MASK                 0xff

#define R_DRW_COLOR2_COLOR2G_SHIFT                (8)  /* Green Channel of Color 2 */
#define R_DRW_COLOR2_COLOR2G_MASK                 0xff00

#define R_DRW_COLOR2_COLOR2R_SHIFT                (16)  /* Red Channel of Color 2 */
#define R_DRW_COLOR2_COLOR2R_MASK                 0xff0000

#define R_DRW_COLOR2_COLOR2A_SHIFT                (24)  /* Alpha Channel of Color 2 */
#define R_DRW_COLOR2_COLOR2A_MASK                 0xff000000

/* PATTERN Register bit definitions */
#define R_DRW_PATTERN_PATTERN_SHIFT               (0)  /* Bitmap of the Pattern */
#define R_DRW_PATTERN_PATTERN_MASK                0xff

/* SIZE Register bit definitions */
#define R_DRW_SIZE_SIZEX_SHIFT                    (0)  /* Bounding Box Width */
#define R_DRW_SIZE_SIZEX_MASK                     0xffff

#define R_DRW_SIZE_SIZEY_SHIFT                    (16)  /* Bounding Box Height */
#define R_DRW_SIZE_SIZEY_MASK                     0xffff0000

/* PITCH Register bit definitions */
#define R_DRW_PITCH_PITCH_SHIFT                   (0)  /* Pitch of the Framebuffer */
#define R_DRW_PITCH_PITCH_MASK                    0xffff

#define R_DRW_PITCH_SSD_SHIFT                     (16)  /* Spanstore Delay */
#define R_DRW_PITCH_SSD_MASK                      0xffff0000

/* ORIGIN Register bit definitions */
#define R_DRW_ORIGIN_ORIGIN_SHIFT                 (0)  /* Address of the First Pixel in Framebuffer */
#define R_DRW_ORIGIN_ORIGIN_MASK                  0xffffffff

/* LUSTART Register bit definitions */
#define R_DRW_LUSTART_LUSTART_SHIFT               (0)  /* U Limiter Start Value */
#define R_DRW_LUSTART_LUSTART_MASK                0xffffffff

/* LUXADD Register bit definitions */
#define R_DRW_LUXADD_LUXADD_SHIFT                 (0)  /* U Limiter X-Axis Increment */
#define R_DRW_LUXADD_LUXADD_MASK                  0xffffffff

/* LUYADD Register bit definitions */
#define R_DRW_LUYADD_LUYADD_SHIFT                 (0)  /* U Limiter Y-Axis Increment */
#define R_DRW_LUYADD_LUYADD_MASK                  0xffffffff

/* LVSTARTI Register bit definitions */
#define R_DRW_LVSTARTI_LVSTARTI_SHIFT             (0)  /* V Limiter Start Value Integer Part */
#define R_DRW_LVSTARTI_LVSTARTI_MASK              0xffffffff

/* LVSTARTF Register bit definitions */
#define R_DRW_LVSTARTF_LVSTARTF_SHIFT             (0)  /* V Limiter Start Value Fractional Part */
#define R_DRW_LVSTARTF_LVSTARTF_MASK              0xffff

/* LVXADDI Register bit definitions */
#define R_DRW_LVXADDI_LVXADDI_SHIFT               (0)  /* V Limiter X-Axis Increment Integer Part */
#define R_DRW_LVXADDI_LVXADDI_MASK                0xffffffff

/* LVYADDI Register bit definitions */
#define R_DRW_LVYADDI_LVYADDI_SHIFT               (0)  /* V Limiter Y-Axis Increment Integer Part */
#define R_DRW_LVYADDI_LVYADDI_MASK                0xffffffff

/* LVYXADDF Register bit definitions */
#define R_DRW_LVYXADDF_LVXADDF_SHIFT              (0)  /* V Limiter X-Axis Increment Fractional Part */
#define R_DRW_LVYXADDF_LVXADDF_MASK               0xffff

#define R_DRW_LVYXADDF_LVYADDF_SHIFT              (16)  /* V Limiter Y-Axis Increment Fractional Part */
#define R_DRW_LVYXADDF_LVYADDF_MASK               0xffff0000

/* TEXPITCH Register bit definitions */
#define R_DRW_TEXPITCH_TEXPITCH_SHIFT             (0)  /* Texels Per Texture Line */
#define R_DRW_TEXPITCH_TEXPITCH_MASK              0xffffffff

/* TEXMASK Register bit definitions */
#define R_DRW_TEXMASK_TEXUMASK_SHIFT              (0)  /* U Mask in Texture Mode */
#define R_DRW_TEXMASK_TEXUMASK_MASK               0x7ff

#define R_DRW_TEXMASK_TEXVMASK_SHIFT              (11)  /* V Mask in Texture Mode */
#define R_DRW_TEXMASK_TEXVMASK_MASK               0xfffff800

/* TEXORIGIN Register bit definitions */
#define R_DRW_TEXORIGIN_TEXORIGIN_SHIFT           (0)  /* Texture Base Address */
#define R_DRW_TEXORIGIN_TEXORIGIN_MASK            0xffffffff

/* IRQCTL Register bit definitions */
#define R_DRW_IRQCTL_ENUMIRQEN                    (1 << 0)  /* ENUMIRQ Interrupt Mask Enable */

#define R_DRW_IRQCTL_DLISTIRQEN                   (1 << 1)  /* DLISTIRQ Interrupt Mask Enable */

#define R_DRW_IRQCTL_ENUMIRQCLR                   (1 << 2)  /* Clear ENUMIRQ */

#define R_DRW_IRQCTL_DLISTIRQCLR                  (1 << 3)  /* Clear DLISTIRQ */

#define R_DRW_IRQCTL_BUSIRQEN                     (1 << 4)  /* BUSIRQ Interrupt Mask Enable */

#define R_DRW_IRQCTL_BUSIRQCLR                    (1 << 5)  /* Clear BUSIRQ */

/* CACHECTL Register bit definitions */
#define R_DRW_CACHECTL_CENABLEFX                  (1 << 0)  /* Framebuffer Cache Enable */

#define R_DRW_CACHECTL_CFLUSHFX                   (1 << 1)  /* Flush Framebuffer Cache */

#define R_DRW_CACHECTL_CENABLETX                  (1 << 2)  /* Texture Cache Enable */

#define R_DRW_CACHECTL_CFLUSHTX                   (1 << 3)  /* Flush Texture Cache */

/* DLISTSTART Register bit definitions */
#define R_DRW_DLISTSTART_DLISTSTART_SHIFT         (0)  /* Display List Start Address */
#define R_DRW_DLISTSTART_DLISTSTART_MASK          0xffffffff

/* PERFCOUNT1 Register bit definitions */
#define R_DRW_PERFCOUNT1_PERFCOUNT_SHIFT          (0)  /* Performance Counter k Value */
#define R_DRW_PERFCOUNT1_PERFCOUNT_MASK           0xffffffff

/* PERFCOUNT2 Register bit definitions */
#define R_DRW_PERFCOUNT2_PERFCOUNT_SHIFT          (0)  /* Performance Counter k Value */
#define R_DRW_PERFCOUNT2_PERFCOUNT_MASK           0xffffffff

/* PERFTRIGGER Register bit definitions */
#define R_DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT      (0)  /* Trigger of Performance Counter 1 */
#define R_DRW_PERFTRIGGER_PERFTRIGGER1_MASK       0xffff

#define R_DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT      (16)  /* Trigger of Performance Counter 2 */
#define R_DRW_PERFTRIGGER_PERFTRIGGER2_MASK       0xffff0000

/* TEXCLADDR Register bit definitions */
#define R_DRW_TEXCLADDR_CLADDR_SHIFT              (0)  /* Texture CLUT Start Address */
#define R_DRW_TEXCLADDR_CLADDR_MASK               0xff

/* TEXCLDATA Register bit definitions */
#define R_DRW_TEXCLDATA_CLDATA_SHIFT              (0)  /* Texture CLUT Data */
#define R_DRW_TEXCLDATA_CLDATA_MASK               0xffffffff

/* TEXCLOFFSET Register bit definitions */
#define R_DRW_TEXCLOFFSET_CLOFFSET_SHIFT          (0)  /* Texture CLUT Offset */
#define R_DRW_TEXCLOFFSET_CLOFFSET_MASK           0xff

/* COLKEY Register bit definitions */
#define R_DRW_COLKEY_COLKEYB_SHIFT                (0)  /* Blue Channel of Color Key */
#define R_DRW_COLKEY_COLKEYB_MASK                 0xff

#define R_DRW_COLKEY_COLKEYG_SHIFT                (8)  /* Green Channel of Color Key */
#define R_DRW_COLKEY_COLKEYG_MASK                 0xff00

#define R_DRW_COLKEY_COLKEYR_SHIFT                (16)  /* Red Channel of Color Key */
#define R_DRW_COLKEY_COLKEYR_MASK                 0xff0000

/* DBWER Register bit definitions */
#define R_DRW_DBWER_BWE                           (1 << 2)  /* Bufferable Write Enable */


/* Maximum number of channels */

#define DRW_MAX_CHANNELS    6

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DRW_H */

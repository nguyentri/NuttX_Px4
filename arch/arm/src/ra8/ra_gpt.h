/****************************************************************************
 * arch/arm/src/ra8/ra_gpt.h
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

#ifndef __ARCH_ARM_SRC_RA_RA8_GPT_H
#define __ARCH_ARM_SRC_RA_RA8_GPT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/timers/pwm.h>
#include <nuttx/timers/timer.h>
#include "chip.h"
#include "hardware/ra_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Maximum number of GPT channels */
#define RA_GPT_NCHANNELS               14

/* GPT modes */
#define RA_GPT_MODE_TIMER              0   /* Timer mode */
#define RA_GPT_MODE_PWM                1   /* PWM mode */
#define RA_GPT_MODE_INPUT_CAPTURE      2   /* Input capture mode */

/* GPT timer modes */
#define RA_GPT_TIMER_PERIODIC          0   /* Periodic timer */
#define RA_GPT_TIMER_ONE_SHOT          1   /* One-shot timer */

/* GPT PWM output modes */
#define RA_PWM_SINGLE_OUTPUT       0   /* Single output (GTIOCA only) */
#define RA_PWM_COMPLEMENTARY       1   /* Complementary output (GTIOCA + GTIOCB) */
#define RA_PWM_INDEPENDENT         2   /* Independent outputs */

/* GPT interrupt sources */
#define RA_GPT_INT_OVERFLOW            (1 << 0)
#define RA_GPT_INT_UNDERFLOW           (1 << 1)
#define RA_GPT_INT_COMPARE_A           (1 << 2)
#define RA_GPT_INT_COMPARE_B           (1 << 3)
#define RA_GPT_INT_COMPARE_C           (1 << 4)
#define RA_GPT_INT_COMPARE_D           (1 << 5)

/* Custom ioctl commands for GPT driver */
#define RA_GPT_IOCTL_BASE              0x8000
#define RA_GPTIOC_SETDEADTIME          (RA_GPT_IOCTL_BASE + 0)  /* Set dead-time config */
#define RA_GPTIOC_GETDEADTIME          (RA_GPT_IOCTL_BASE + 1)  /* Get dead-time config */
#define RA_GPTIOC_SETTRIGGER           (RA_GPT_IOCTL_BASE + 2)  /* Set external trigger config */
#define RA_GPTIOC_GETTRIGGER           (RA_GPT_IOCTL_BASE + 3)  /* Get external trigger config */
#define RA_GPTIOC_SETCAPTURE           (RA_GPT_IOCTL_BASE + 4)  /* Set input capture config */
#define RA_GPTIOC_GETCAPTURE           (RA_GPT_IOCTL_BASE + 5)  /* Get captured value */
#define RA_GPTIOC_SETDMA               (RA_GPT_IOCTL_BASE + 6)  /* Set DMA config */
#define RA_GPTIOC_GETDMA               (RA_GPT_IOCTL_BASE + 7)  /* Get DMA config */

/* GPT input capture edge detection */
#define RA_GPT_CAPTURE_NONE            0   /* Capture disabled */
#define RA_GPT_CAPTURE_RISING          1   /* Capture on rising edge */
#define RA_GPT_CAPTURE_FALLING         2   /* Capture on falling edge */
#define RA_GPT_CAPTURE_BOTH            3   /* Capture on both edges */

/* GPT external trigger sources */
#define RA_GPT_TRIGGER_NONE            0   /* No external trigger */
#define RA_GPT_TRIGGER_ELC             1   /* ELC event trigger */
#define RA_GPT_TRIGGER_GTIOCA          2   /* GTIOCA pin trigger */
#define RA_GPT_TRIGGER_GTIOCB          3   /* GTIOCB pin trigger */

/* GPT trigger actions */
#define RA_GPT_TRIGGER_START           (1 << 0)  /* Trigger starts timer */
#define RA_GPT_TRIGGER_STOP            (1 << 1)  /* Trigger stops timer */
#define RA_GPT_TRIGGER_CLEAR           (1 << 2)  /* Trigger clears counter */
#define RA_GPT_TRIGGER_COUNT_UP        (1 << 3)  /* Trigger counts up */
#define RA_GPT_TRIGGER_COUNT_DN        (1 << 4)  /* Trigger counts down */
#define RA_GPT_TRIGGER_CAPTURE_A       (1 << 5)  /* Trigger captures to GTCCRA */
#define RA_GPT_TRIGGER_CAPTURE_B       (1 << 6)  /* Trigger captures to GTCCRB */

/* Dead-time configuration structure for ioctl */
struct ra_gpt_deadtime_s
{
  uint32_t deadtime_up;    /* Dead-time for rising edge (timer ticks) */
  uint32_t deadtime_dn;    /* Dead-time for falling edge (timer ticks) */
  bool     enable;         /* True to enable dead-time, false to disable */
};

/* External trigger configuration structure for ioctl */
struct ra_gpt_trigger_s
{
  uint8_t  source;         /* Trigger source (RA_GPT_TRIGGER_*) */
  uint8_t  action;         /* Trigger action flags (RA_GPT_TRIGGER_START/STOP/CLEAR...) */
  uint16_t elc_event;      /* ELC event number (when source is RA_GPT_TRIGGER_ELC) */
  bool     enable;         /* True to enable trigger, false to disable */
};

/* Input capture configuration structure for ioctl */
struct ra_gpt_capture_s
{
  uint8_t  channel;        /* Capture channel (0=A, 1=B) */
  uint8_t  edge;           /* Edge detection (RA_GPT_CAPTURE_*) */
  bool     filter_enable;  /* Enable noise filter */
  uint8_t  filter_clock;   /* Noise filter clock divisor (0-3) */
  bool     enable;         /* True to enable capture, false to disable */
};

/* Captured value structure */
struct ra_gpt_captured_s
{
  uint8_t  channel;        /* Capture channel (0=A, 1=B) */
  uint32_t value;          /* Captured counter value */
  bool     overflow;       /* True if overflow occurred before capture */
};

/* DMA configuration structure for ioctl */
struct ra_gpt_dma_s
{
  uint8_t  trigger;        /* DMA trigger source (0=compare A, 1=compare B, 2=overflow) */
  uint32_t src_addr;       /* Source address for DMA transfer */
  uint32_t dst_addr;       /* Destination address (typically GTCCRA/B) */
  uint32_t transfer_count; /* Number of transfers */
  bool     enable;         /* True to enable DMA, false to disable */
};

/**********************************************************************/

/* GTWP Register bit definitions */
#define GPT_GTWP_PRKEY                            (0xa500 << 8)  /* Write protect key */
#define GPT_GTWP_WP                               (1 << 0)       /* Write protection enable */
#define GPT_GTWP_CMNWP                            (1 << 4)       /* Common register write protect */

/* GTCR Register bit definitions
 * Validated against R7KA8P1KF_core0.h (CMSIS):
 *   R_GPT0_GTCR_CST_Pos  = 0   (Count Start)
 *   R_GPT0_GTCR_MD_Pos   = 16  (Mode Select, 4-bit field)
 *   R_GPT0_GTCR_TPCS_Pos = 23  (Timer Prescaler, 4-bit field)
 */
#define GPT_GTCR_CST                              (1 << 0)       /* Count start */

/* Mode Select (MD) - bits [19:16] */
#define GPT_GTCR_MD_SHIFT                         (16)           /* Mode select shift (CMSIS: R_GPT0_GTCR_MD_Pos) */
#define GPT_GTCR_MD_MASK                          (0xf << GPT_GTCR_MD_SHIFT)  /* 4-bit field */
#define GPT_GTCR_MD_SAW_WAVE_UP                   (0 << GPT_GTCR_MD_SHIFT)    /* Saw-wave PWM (up-count) */
#define GPT_GTCR_MD_SAW_WAVE_ONESHOT              (1 << GPT_GTCR_MD_SHIFT)    /* Saw-wave one-shot pulse */
#define GPT_GTCR_MD_SAW_WAVE_DN                   (2 << GPT_GTCR_MD_SHIFT)    /* Reserved (was down-count) */
#define GPT_GTCR_MD_TRIANGULAR_WAVE               (4 << GPT_GTCR_MD_SHIFT)    /* Triangle-wave PWM mode 1 */
#define GPT_GTCR_MD_TRIANGULAR_WAVE2              (5 << GPT_GTCR_MD_SHIFT)    /* Triangle-wave PWM mode 2 */
#define GPT_GTCR_MD_TRIANGULAR_WAVE3              (6 << GPT_GTCR_MD_SHIFT)    /* Triangle-wave PWM mode 3 */

/* Timer Prescaler Select (TPCS) - bits [26:23] */
#define GPT_GTCR_TPCS_SHIFT                       (23)           /* Timer prescaler shift (CMSIS: R_GPT0_GTCR_TPCS_Pos) */
#define GPT_GTCR_TPCS_MASK                        (0xf << GPT_GTCR_TPCS_SHIFT)  /* 4-bit field */
#define GPT_GTCR_TPCS_PCLKD_1                     (0 << GPT_GTCR_TPCS_SHIFT)  /* PCLKD / 1 */
#define GPT_GTCR_TPCS_PCLKD_2                     (1 << GPT_GTCR_TPCS_SHIFT)  /* PCLKD / 2 */
#define GPT_GTCR_TPCS_PCLKD_4                     (2 << GPT_GTCR_TPCS_SHIFT)  /* PCLKD / 4 */
#define GPT_GTCR_TPCS_PCLKD_8                     (3 << GPT_GTCR_TPCS_SHIFT)  /* PCLKD / 8 */
#define GPT_GTCR_TPCS_PCLKD_16                    (4 << GPT_GTCR_TPCS_SHIFT)  /* PCLKD / 16 */
#define GPT_GTCR_TPCS_PCLKD_32                    (5 << GPT_GTCR_TPCS_SHIFT)  /* PCLKD / 32 */
#define GPT_GTCR_TPCS_PCLKD_64                    (6 << GPT_GTCR_TPCS_SHIFT)  /* PCLKD / 64 */
#define GPT_GTCR_TPCS_PCLKD_128                   (7 << GPT_GTCR_TPCS_SHIFT)  /* PCLKD / 128 */
#define GPT_GTCR_TPCS_PCLKD_256                   (8 << GPT_GTCR_TPCS_SHIFT)  /* PCLKD / 256 */
#define GPT_GTCR_TPCS_PCLKD_512                   (9 << GPT_GTCR_TPCS_SHIFT)  /* PCLKD / 512 */
#define GPT_GTCR_TPCS_PCLKD_1024                  (10 << GPT_GTCR_TPCS_SHIFT) /* PCLKD / 1024 */

/* GTIOR Register bit definitions */
/* GTIOA function select bits [4:0] */
#define GPT_GTIOR_GTIOA_SHIFT                     (0)
#define GPT_GTIOR_GTIOA_MASK                      (0x1f << GPT_GTIOR_GTIOA_SHIFT)
#define GPT_GTIOR_GTIOA_DISABLED                  (0x00 << GPT_GTIOR_GTIOA_SHIFT) /* Pin function disabled */
#define GPT_GTIOR_GTIOA_INITIAL_LOW               (0x00 << GPT_GTIOR_GTIOA_SHIFT) /* Initial low, no toggle */
#define GPT_GTIOR_GTIOA_INITIAL_HIGH              (0x10 << GPT_GTIOR_GTIOA_SHIFT) /* Initial high, no toggle */
#define GPT_GTIOR_GTIOA_LOW_CMP_HIGH_END          (0x06 << GPT_GTIOR_GTIOA_SHIFT) /* Initial low, high@cmp, low@end */
#define GPT_GTIOR_GTIOA_HIGH_CMP_LOW_END          (0x09 << GPT_GTIOR_GTIOA_SHIFT) /* Initial high, low@cmp, high@end */
#define GPT_GTIOR_GTIOA_TOGGLE_CMP                (0x03 << GPT_GTIOR_GTIOA_SHIFT) /* Toggle on compare match */

/* GTIOA output default value at stop [6] */
#define GPT_GTIOR_OADFLT                          (1 << 6)  /* Output value at count stop: 0=low, 1=high */

/* GTIOA output hold at start/stop [7] - not commonly used */
#define GPT_GTIOR_OAHLD                           (1 << 7)  /* Output hold at start/stop */

/* GTIOA output enable [8] - CRITICAL for PWM output! */
#define GPT_GTIOR_OAE                             (1 << 8)  /* GTIOCA pin output enable */

/* GTIOA output disable setting [10:9] */
#define GPT_GTIOR_OADF_SHIFT                      (9)
#define GPT_GTIOR_OADF_MASK                       (0x3 << GPT_GTIOR_OADF_SHIFT)
#define GPT_GTIOR_OADF_HIGHZ                      (0 << GPT_GTIOR_OADF_SHIFT)  /* Hi-Z on disable */
#define GPT_GTIOR_OADF_LOW                        (2 << GPT_GTIOR_OADF_SHIFT)  /* Low on disable */
#define GPT_GTIOR_OADF_HIGH                       (3 << GPT_GTIOR_OADF_SHIFT)  /* High on disable */

/* Noise filter A enable [13] and clock select [15:14] */
#define GPT_GTIOR_NFAEN                           (1 << 13) /* Noise filter A enable */
#define GPT_GTIOR_NFCSA_SHIFT                     (14)
#define GPT_GTIOR_NFCSA_MASK                      (0x3 << GPT_GTIOR_NFCSA_SHIFT)

/* GTIOCB function select bits [20:16] */
#define GPT_GTIOR_GTIOB_SHIFT                     (16)
#define GPT_GTIOR_GTIOB_MASK                      (0x1f << GPT_GTIOR_GTIOB_SHIFT)
#define GPT_GTIOR_GTIOB_DISABLED                  (0x00 << GPT_GTIOR_GTIOB_SHIFT) /* Pin function disabled */
#define GPT_GTIOR_GTIOB_INITIAL_LOW               (0x00 << GPT_GTIOR_GTIOB_SHIFT) /* Initial low, no toggle */
#define GPT_GTIOR_GTIOB_INITIAL_HIGH              (0x10 << GPT_GTIOR_GTIOB_SHIFT) /* Initial high, no toggle */
#define GPT_GTIOR_GTIOB_LOW_CMP_HIGH_END          (0x06 << GPT_GTIOR_GTIOB_SHIFT) /* Initial low, high@cmp, low@end */
#define GPT_GTIOR_GTIOB_HIGH_CMP_LOW_END          (0x09 << GPT_GTIOR_GTIOB_SHIFT) /* Initial high, low@cmp, high@end */
#define GPT_GTIOR_GTIOB_TOGGLE_CMP                (0x03 << GPT_GTIOR_GTIOB_SHIFT) /* Toggle on compare match */

/* GTIOCB output default value at stop [22] */
#define GPT_GTIOR_OBDFLT                          (1 << 22) /* Output value at count stop: 0=low, 1=high */

/* GTIOCB output hold at start/stop [23] */
#define GPT_GTIOR_OBHLD                           (1 << 23) /* Output hold at start/stop */

/* GTIOCB output enable [24] - CRITICAL for PWM output! */
#define GPT_GTIOR_OBE                             (1 << 24) /* GTIOCB pin output enable */

/* GTIOCB output disable setting [26:25] */
#define GPT_GTIOR_OBDF_SHIFT                      (25)
#define GPT_GTIOR_OBDF_MASK                       (0x3 << GPT_GTIOR_OBDF_SHIFT)
#define GPT_GTIOR_OBDF_HIGHZ                      (0 << GPT_GTIOR_OBDF_SHIFT)  /* Hi-Z on disable */
#define GPT_GTIOR_OBDF_LOW                        (2 << GPT_GTIOR_OBDF_SHIFT)  /* Low on disable */
#define GPT_GTIOR_OBDF_HIGH                       (3 << GPT_GTIOR_OBDF_SHIFT)  /* High on disable */

/* Noise filter B enable [29] and clock select [31:30] */
#define GPT_GTIOR_NFBEN                           (1 << 29) /* Noise filter B enable */
#define GPT_GTIOR_NFCSB_SHIFT                     (30)
#define GPT_GTIOR_NFCSB_MASK                      (0x3 << GPT_GTIOR_NFCSB_SHIFT)

/* Convenience macros for common PWM output configurations */
/* Saw-wave PWM: Initial low, go high at compare match, go low at period end */
#define GPT_GTIOR_PWM_HIGH_A   (GPT_GTIOR_GTIOA_LOW_CMP_HIGH_END | GPT_GTIOR_OAE)
#define GPT_GTIOR_PWM_HIGH_B   (GPT_GTIOR_GTIOB_LOW_CMP_HIGH_END | GPT_GTIOR_OBE)
#define GPT_GTIOR_PWM_HIGH_AB  (GPT_GTIOR_PWM_HIGH_A | GPT_GTIOR_PWM_HIGH_B)

/* Saw-wave PWM: Initial high, go low at compare match, go high at period end */
#define GPT_GTIOR_PWM_LOW_A    (GPT_GTIOR_GTIOA_HIGH_CMP_LOW_END | GPT_GTIOR_OAE)
#define GPT_GTIOR_PWM_LOW_B    (GPT_GTIOR_GTIOB_HIGH_CMP_LOW_END | GPT_GTIOR_OBE)
#define GPT_GTIOR_PWM_LOW_AB   (GPT_GTIOR_PWM_LOW_A | GPT_GTIOR_PWM_LOW_B)

/* GTBER Register bit definitions (Buffer Enable Register) */
#define GPT_GTBER_CCRA                            (1 << 16)  /* GTCCRA buffer enable */
#define GPT_GTBER_CCRB                            (1 << 18)  /* GTCCRB buffer enable */
#define GPT_GTBER_PR                              (1 << 20)  /* GTPR buffer enable */
#define GPT_GTBER_CCRSWT                          (1 << 22)  /* GTCCRA/GTCCRB forcible buffer transfer */
#define GPT_GTBER_PRSWT                           (1 << 23)  /* GTPR forcible buffer transfer */

/* GTINTAD Register bit definitions (Interrupt Output Setting Register) */
#define GPT_GTINTAD_GTINTA                        (1 << 0)  /* Compare match A interrupt enable */
#define GPT_GTINTAD_GTINTB                        (1 << 1)  /* Compare match B interrupt enable */
#define GPT_GTINTAD_GTINTC                        (1 << 2)  /* Compare match C interrupt enable */
#define GPT_GTINTAD_GTINTD                        (1 << 3)  /* Compare match D interrupt enable */
#define GPT_GTINTAD_GTINTE                        (1 << 4)  /* Compare match E interrupt enable */
#define GPT_GTINTAD_GTINTF                        (1 << 5)  /* Compare match F interrupt enable */
#define GPT_GTINTAD_GTINTPR_SHIFT                 (6)       /* Overflow/Underflow interrupt skip setting */
#define GPT_GTINTAD_GTINTPR_MASK                  (0x3 << GPT_GTINTAD_GTINTPR_SHIFT)
#define GPT_GTINTAD_GTINTPR_NONE                  (0 << GPT_GTINTAD_GTINTPR_SHIFT)
#define GPT_GTINTAD_GTINTPR_SKIP1                 (1 << GPT_GTINTAD_GTINTPR_SHIFT)
#define GPT_GTINTAD_GTINTPR_SKIP2                 (2 << GPT_GTINTAD_GTINTPR_SHIFT)
#define GPT_GTINTAD_GTINTPR_SKIP3                 (3 << GPT_GTINTAD_GTINTPR_SHIFT)
#define GPT_GTINTAD_EINT                          (1 << 8)  /* Dead time error interrupt enable */
#define GPT_GTINTAD_OINT                          (1 << 9)  /* Same time output level detection interrupt enable */
#define GPT_GTINTAD_ADTRAUEN                      (1 << 16) /* GTADTRA compare match (up) A/D start request enable */
#define GPT_GTINTAD_ADTRADEN                      (1 << 17) /* GTADTRA compare match (down) A/D start request enable */
#define GPT_GTINTAD_ADTRBUEN                      (1 << 18) /* GTADTRB compare match (up) A/D start request enable */
#define GPT_GTINTAD_ADTRBDEN                      (1 << 19) /* GTADTRB compare match (down) A/D start request enable */

/* GTST Register bit definitions (Status Register) */
#define GPT_GTST_TCFA                             (1 << 0)  /* Compare match flag A */
#define GPT_GTST_TCFB                             (1 << 1)  /* Compare match flag B */
#define GPT_GTST_TCFC                             (1 << 2)  /* Compare match flag C */
#define GPT_GTST_TCFD                             (1 << 3)  /* Compare match flag D */
#define GPT_GTST_TCFE                             (1 << 4)  /* Compare match flag E */
#define GPT_GTST_TCFF                             (1 << 5)  /* Compare match flag F */
#define GPT_GTST_TCFPO                            (1 << 6)  /* Overflow flag */
#define GPT_GTST_TCFPU                            (1 << 7)  /* Underflow flag */
#define GPT_GTST_TUCF                             (1 << 15) /* Count direction flag (1=up, 0=down) */
#define GPT_GTST_ADTRAUEN                         (1 << 16) /* A/D Start Request Active */
#define GPT_GTST_ADTRBUEN                         (1 << 17) /* A/D Start Request Active */
#define GPT_GTST_ADTRADEN                         (1 << 20) /* A/D Start Request Active */
#define GPT_GTST_ADTRBDEN                         (1 << 21) /* A/D Start Request Active */

/* GTDTCR Register bit definitions (Dead Time Control Register) */
#define GPT_GTDTCR_TDE                            (1 << 0)  /* Negative-phase waveform enable (dead-time) */
#define GPT_GTDTCR_TDBUE                          (1 << 4)  /* GTDVU buffer enable */
#define GPT_GTDTCR_TDBDE                          (1 << 5)  /* GTDVD buffer enable */
#define GPT_GTDTCR_TDFER                          (1 << 8)  /* Dead time error flag */

/* GTSSR/GTPSR/GTCSR Register bit definitions (Start/Stop/Clear Source Select) */
/* These registers control external trigger sources via ELC events */
#define GPT_GTSSR_CSTRT_SHIFT                     (0)
#define GPT_GTSSR_SSELC                           (1 << 8)   /* Software source select for start */
#define GPT_GTSSR_SSELCH                          (1 << 9)   /* Clear on read after software start */

#define GPT_GTPSR_CSTOP_SHIFT                     (0)
#define GPT_GTPSR_PSEC                            (1 << 8)   /* Software source select for stop */
#define GPT_GTPSR_PSELCH                          (1 << 9)   /* Clear on read after software stop */

#define GPT_GTCSR_CCLR_SHIFT                      (0)
#define GPT_GTCSR_CSELC                           (1 << 8)   /* Software source select for clear */
#define GPT_GTCSR_CSELCH                          (1 << 9)   /* Clear on read after software clear */

/* GTUPSR/GTDNSR Register bit definitions (Up/Down Count Source Select) */
#define GPT_GTUPSR_USELC                          (1 << 8)   /* Software source select for up count */
#define GPT_GTDNSR_DSELC                          (1 << 8)   /* Software source select for down count */

/* GTICASR/GTICBSR Register bit definitions (Input Capture Source Select) */
/* Common bit definitions for input capture source select */
#define GPT_GTICSR_ASELC                          (1 << 8)   /* Software capture A trigger */
#define GPT_GTICSR_BSELC                          (1 << 8)   /* Software capture B trigger */

/* ELC event input source bits (GTSSR, GTPSR, GTCSR, GTICASR, GTICBSR) */
/* Bit 0: ELCTRGA event, Bit 1: ELCTRGB event, etc. */
#define GPT_SSSR_ELC_EVENT(n)                     (1 << (n)) /* ELC event n (0-7) */

/* GTIOCA/GTIOCB input for capture */
#define GPT_GTICSR_GTIOCA_RISE                    (1 << 0)   /* GTIOCA rising edge */
#define GPT_GTICSR_GTIOCA_FALL                    (1 << 1)   /* GTIOCA falling edge */
#define GPT_GTICSR_GTIOCB_RISE                    (1 << 2)   /* GTIOCB rising edge */
#define GPT_GTICSR_GTIOCB_FALL                    (1 << 3)   /* GTIOCB falling edge */

/* Input capture mode configuration for GTIOR */
/* For input capture: configure GTIOA/GTIOB as input */
#define GPT_GTIOR_GTIOA_INPUT_RISE                (0x01 << GPT_GTIOR_GTIOA_SHIFT)  /* Input, capture on rising */
#define GPT_GTIOR_GTIOA_INPUT_FALL                (0x02 << GPT_GTIOR_GTIOA_SHIFT)  /* Input, capture on falling */
#define GPT_GTIOR_GTIOA_INPUT_BOTH                (0x03 << GPT_GTIOR_GTIOA_SHIFT)  /* Input, capture on both */
#define GPT_GTIOR_GTIOB_INPUT_RISE                (0x01 << GPT_GTIOR_GTIOB_SHIFT)  /* Input, capture on rising */
#define GPT_GTIOR_GTIOB_INPUT_FALL                (0x02 << GPT_GTIOR_GTIOB_SHIFT)  /* Input, capture on falling */
#define GPT_GTIOR_GTIOB_INPUT_BOTH                (0x03 << GPT_GTIOR_GTIOB_SHIFT)  /* Input, capture on both */

/****************************************************************************
 * Public Types
 ****************************************************************************/


/* GPT Channel Configuration Structure */

struct ra_gpt_config_s
{
  uint32_t base;                   /* GPT peripheral base address */
  uint32_t pclkd_frequency;        /* PCLKD frequency in Hz */
  uint8_t  channel;                /* GPT channel (0-13) */
  uint8_t  irq;                    /* Interrupt request number */
};

/* GPT Device Structure */

struct ra_gpt_dev_s
{
  const struct ra_gpt_config_s *config;  /* GPT configuration */
  uint32_t frequency;                      /* PWM frequency */
  uint32_t period;                         /* PWM period in timer counts */
  bool started;                            /* PWM started flag */
};


/* GPT timer configuration */
struct ra_gpt_timer_config_s
{
  uint8_t  channel;                /* GPT channel number */
  uint8_t  mode;                   /* Timer mode (periodic/one-shot) */
  uint32_t frequency;              /* Timer frequency in Hz */
  uint32_t timeout_us;             /* Timeout in microseconds (for one-shot) */
  void     (*callback)(void *arg); /* Timer callback function */
  void     *arg;                   /* Callback argument */
};

/* GPT PWM configuration */
struct ra_gpt_pwm_config_s
{
  uint8_t  channel;                /* GPT channel number */
  uint8_t  output_mode;            /* PWM output mode */
  uint32_t frequency;              /* PWM frequency in Hz */
  uint32_t duty_a;                 /* Duty cycle for GTIOCA (0-65535) */
  uint32_t duty_b;                 /* Duty cycle for GTIOCB (0-65535) */
  bool     enable_deadtime;        /* Enable dead time control */
  uint16_t deadtime_up;            /* Dead time for rising edge */
  uint16_t deadtime_down;          /* Dead time for falling edge */
};

/* GPT channel configuration */
struct ra_gpt_channel_s
{
  uint8_t channel;                 /* GPT channel number (0-13) */
  uint8_t mode;                    /* GPT mode flags */
  uint32_t pin_a;                  /* GTIOA pin configuration */
  uint32_t pin_b;                  /* GTIOB pin configuration (for complementary mode) */
  uint16_t deadtime_up;            /* Dead time for rising edge (in timer counts) */
  uint16_t deadtime_down;          /* Dead time for falling edge (in timer counts) */
};

/* GPT driver configuration */
struct ra_gpt_driver_config_s
{
  uint8_t nchannels;               /* Number of GPT channels */
  const struct ra_gpt_channel_s *channels; /* GPT channel configurations */
  uint32_t base_frequency;         /* Base timer frequency in Hz */
  uint32_t default_frequency;      /* Default PWM frequency in Hz */
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifndef __ASSEMBLY__

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: ra_gpt_initialize
 *
 * Description:
 *   Initialize the GPT subsystem
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

struct pwm_lowerhalf_s *ra_gpt_initialize(int channel);

/****************************************************************************
 * Name: ra_gpt_pwm_setup
 *
 * Description:
 *   Initialize one PWM channel for the given GPT channel
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *
 * Returned Value:
 *   On success, a pointer to the RA GPT lower half PWM driver is returned.
 *   NULL is returned on any failure.
 *
 ****************************************************************************/

struct pwm_lowerhalf_s *ra_gpt_pwm_setup(int channel);

/****************************************************************************
 * Name: ra_gpt_timer_setup
 *
 * Description:
 *   Initialize one timer for the given GPT channel
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *
 * Returned Value:
 *   On success, a pointer to the RA GPT lower half timer driver is returned.
 *   NULL is returned on any failure.
 *
 ****************************************************************************/

struct timer_lowerhalf_s *ra_gpt_timer_setup(int channel);

/****************************************************************************
 * Name: ra_gpt_start
 *
 * Description:
 *   Start the specified GPT channel
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_start(int channel);

/****************************************************************************
 * Name: ra_gpt_stop
 *
 * Description:
 *   Stop the specified GPT channel
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_stop(int channel);

/****************************************************************************
 * Name: ra_gpt_pwm_config
 *
 * Description:
 *   Configure PWM parameters for the specified GPT channel
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *   config  - PWM configuration
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_pwm_config(int channel, const struct ra_gpt_pwm_config_s *config);

/****************************************************************************
 * Name: ra_gpt_timer_config
 *
 * Description:
 *   Configure timer parameters for the specified GPT channel
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *   config  - Timer configuration
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_timer_config(int channel, const struct ra_gpt_timer_config_s *config);

/****************************************************************************
 * Name: ra_gpt_get_counter
 *
 * Description:
 *   Get the current counter value for the specified GPT channel
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *
 * Returned Value:
 *   Current counter value, or 0 on error.
 *
 ****************************************************************************/

uint32_t ra_gpt_get_counter(int channel);

/****************************************************************************
 * Name: ra_gpt_set_period
 *
 * Description:
 *   Set the period for the specified GPT channel
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *   period  - Period value in timer counts
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_set_period(int channel, uint32_t period);

/****************************************************************************
 * Name: ra_gpt_set_compare
 *
 * Description:
 *   Set the compare value for the specified GPT channel and compare register
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *   compare - Compare register (0=A, 1=B, 2=C, 3=D)
 *   value   - Compare value in timer counts
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_set_compare(int channel, int compare, uint32_t value);

/****************************************************************************
 * Name: ra_gpt_set_trigger
 *
 * Description:
 *   Configure external trigger sources for the specified GPT channel.
 *   This allows ELC events to start, stop, clear, or count the timer.
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *   config  - Trigger configuration
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_set_trigger(int channel, const struct ra_gpt_trigger_s *config);

/****************************************************************************
 * Name: ra_gpt_set_capture
 *
 * Description:
 *   Configure input capture mode for the specified GPT channel.
 *   This enables capturing the counter value on external pin edges.
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *   config  - Capture configuration
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_set_capture(int channel, const struct ra_gpt_capture_s *config);

/****************************************************************************
 * Name: ra_gpt_get_capture
 *
 * Description:
 *   Get the captured counter value from input capture mode.
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *   capture - Pointer to capture result structure
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_get_capture(int channel, struct ra_gpt_captured_s *capture);

/****************************************************************************
 * Name: ra_gpt_set_dma
 *
 * Description:
 *   Configure DMA for waveform generation on the specified GPT channel.
 *   This enables automatic duty cycle updates via DMA transfers.
 *
 * Input Parameters:
 *   channel - GPT channel number (0-13)
 *   config  - DMA configuration
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_gpt_set_dma(int channel, const struct ra_gpt_dma_s *config);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RA_RA8_GPT_H */

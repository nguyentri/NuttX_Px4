/****************************************************************************
 * arch/arm/src/ra8/ra_start.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <assert.h>
#include <debug.h>
#include <string.h>

#include <nuttx/init.h>
#include <nuttx/arch.h>
#include <nuttx/cache.h>
#include <arch/irq.h>
#include "arch/board/board.h"
#include "arm_internal.h"
#include "nvic.h"
#include "chip.h"
#include "ra_clock.h"
#include "ra_lowputc.h"
#include "ra_start.h"
#include "hardware/ra_hardware.h"
#include "hardware/ra_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Use the standard NuttX approach for heap base - will be defined in config */
#ifndef CONFIG_IDLETHREAD_STACKSIZE
#  define CONFIG_IDLETHREAD_STACKSIZE 2048
#endif

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* The top of the idle thread stack.  This is used to initialize the
 * initial stack pointer for the idle thread.  The idle thread stack is
 * allocated in the .bss section, so it will be zero initialized.
 * The idle thread stack is allocated in the .bss section, so it will be
 * zero initialized.
 */
extern uint32_t __ram_thread_stack$$Limit;
const uintptr_t g_idle_topstack = (uintptr_t)&__ram_thread_stack$$Limit + CONFIG_IDLETHREAD_STACKSIZE;

extern uint32_t _vectors[]; /* See arm_vectors.S */

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

 /* Time conversion macros */
#define RA_PRV_NS_PER_SECOND    (1000000000)
#define RA_PRV_US_PER_SECOND    (1000000)
#define RA_PRV_NS_PER_US        (1000)
#define RA_PRV_LOOP_CYCLES      (4)
#define RA_PRV_LOOPS_CALCULATE  (cycles)    (((cycles) / RA_PRV_LOOP_CYCLES) + 1U)

/* Key constants for option bytes */
#define RA_TZ_STACK_SEAL_VALUE     (0xFEF5EDA5)
#define RA_CCR_CACHE_ENABLE        (0x000E0201) /* Enable instruction cache, branch prediction and LOB extension */

/* PRCR register unlock keys */
#define RA_PRCR_PRC1_UNLOCK        ((R_SYSC_PRCR_S_KEY) | 0x2U)
#define RA_PRCR_LOCK               ((R_SYSC_PRCR_S_KEY) | 0x0U)


#if defined (CONFIG_RA_OPTION_SETTING_ENABLE)
/* boot loaded applications cannot set ofs registers (only do so in the boot loader) */
#if !defined(CONFIG_RA_BOOTLOADED_APPLICATION) || !CONFIG_RA_BOOTLOADED_APPLICATION

/* Option byte settings */
#if defined(CONFIG_RA8E1_GROUP)

/* Option byte Configuration registers to sections */
#if defined CONFIG_RA_OFS0_SETTING && !CONFIG_RA_TZ_NONSECURE_BUILD
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_ofs0") g_ra_cfg_option_setting_ofs0[] = {CONFIG_RA_OPTION_SETTING_OFS0};
#endif
#if defined CONFIG_RA_OFS2_SETTING && !CONFIG_RA_TZ_NONSECURE_BUILD
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_ofs2") g_ra_cfg_option_setting_ofs2[] = {CONFIG_RA_OPTION_SETTING_OFS2};
#endif
#if defined CONFIG_RA_DUAL_BANK_SETTING && !CONFIG_RA_TZ_NONSECURE_BUILD
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_dualsel") g_ra_cfg_option_setting_dualsel[] = {CONFIG_RA_OPTION_SETTING_DUALSEL};
#endif
#if defined CONFIG_RA_OFS1_SETTING
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_ofs1") g_ra_cfg_option_setting_ofs1[] = {CONFIG_RA_OPTION_SETTING_OFS1};
#endif
#if defined CONFIG_RA_BANK_SELECT_SETTING
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_banksel") g_ra_cfg_option_setting_banksel[] = {CONFIG_RA_OPTION_SETTING_BANKSEL};
#endif
#if defined CONFIG_RA_BOOT_PROTECT_SETTING
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_bps") g_ra_cfg_option_setting_bps[] = {CONFIG_RA_OPTION_SETTING_BPS};
#endif
#if defined CONFIG_RA_BOOT_PROTECT_SETTING
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_pbps") g_ra_cfg_option_setting_pbps[] = {CONFIG_RA_OPTION_SETTING_PBPS};
#endif
#if defined CONFIG_RA_OFS1_SEC_SETTING && !CONFIG_RA_TZ_NONSECURE_BUILD
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_ofs1_sec") g_ra_cfg_option_setting_ofs1_sec[] = {CONFIG_RA_OPTION_SETTING_OFS1_SEC};
#endif
#if defined CONFIG_RA_BANK_SELECT_SETTING && !CONFIG_RA_TZ_NONSECURE_BUILD
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_banksel_sec") g_ra_cfg_option_setting_banksel_sec[] = {CONFIG_RA_OPTION_SETTING_BANKSEL_SEC};
#endif
#if defined CONFIG_RA_BANK_SELECT_SETTING && !CONFIG_RA_TZ_NONSECURE_BUILD
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_bps_sec") g_ra_cfg_option_setting_bps_sec[] = {CONFIG_RA_OPTION_SETTING_BPS_SEC};
#endif
#if defined CONFIG_RA_BOOT_PROTECT_SETTING && !CONFIG_RA_TZ_NONSECURE_BUILD
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_pbps_sec") g_ra_cfg_option_setting_pbps_sec[] = {CONFIG_RA_OPTION_SETTING_PBPS_SEC};
#endif
#if defined CONFIG_RA_OFS1_SEL_SETTING && !CONFIG_RA_TZ_NONSECURE_BUILD
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_ofs1_sel") g_ra_cfg_option_setting_ofs1_sel[] = {CONFIG_RA_OPTION_SETTING_OFS1_SEL};
#endif
#if defined CONFIG_RA_BANK_SELECT_SETTING && !CONFIG_RA_TZ_NONSECURE_BUILD
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_banksel_sel") g_ra_cfg_option_setting_banksel_sel[] = {CONFIG_RA_OPTION_SETTING_BANKSEL_SEL};
#endif
#if defined CONFIG_RA_BOOT_PROTECT_SETTING && !CONFIG_RA_TZ_NONSECURE_BUILD
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_bps_sel") g_ra_cfg_option_setting_bps_sel[] = {CONFIG_RA_OPTION_SETTING_BPS_SEL};
#endif

#else /* CONFIG_RA8E1_GROUP */

#define RA_CFG_CPU_CORE           (0) /* RA8P1 is Cortex-M85 based */

/* Option byte Configuration registers to sections */
#if defined RA_CFG_OPTION_SETTING_OFS0 && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_ofs0") g_bsp_cfg_option_setting_ofs0[] = {RA_CFG_OPTION_SETTING_OFS0};
#endif
#if defined RA_CFG_OPTION_SETTING_OFS2 && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_ofs2") g_bsp_cfg_option_setting_ofs2[] = {RA_CFG_OPTION_SETTING_OFS2};
#endif
#if defined RA_CFG_OPTION_SETTING_SAS && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_sas") g_bsp_cfg_option_setting_sas[] = {RA_CFG_OPTION_SETTING_SAS};
#endif
#if defined RA_CFG_OPTION_SETTING_OFS1 && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_ofs1") g_bsp_cfg_option_setting_ofs1[] = {RA_CFG_OPTION_SETTING_OFS1};
#endif
#if defined RA_CFG_OPTION_SETTING_OFS1_SEC && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_ofs1_sec") g_bsp_cfg_option_setting_ofs1_sec[] = {RA_CFG_OPTION_SETTING_OFS1_SEC};
#endif
#if defined RA_CFG_OPTION_SETTING_OFS1_SEL && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_ofs1_sel") g_bsp_cfg_option_setting_ofs1_sel[] = {RA_CFG_OPTION_SETTING_OFS1_SEL};
#endif
#if defined RA_CFG_OPTION_SETTING_OFS3 && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_ofs3") g_bsp_cfg_option_setting_ofs3[] = {RA_CFG_OPTION_SETTING_OFS3};
#endif
#if defined RA_CFG_OPTION_SETTING_OFS3_SEC && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_ofs3_sec") g_bsp_cfg_option_setting_ofs3_sec[] = {RA_CFG_OPTION_SETTING_OFS3_SEC};
#endif
#if defined RA_CFG_OPTION_SETTING_OFS3_SEL && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_ofs3_sel") g_bsp_cfg_option_setting_ofs3_sel[] = {RA_CFG_OPTION_SETTING_OFS3_SEL};
#endif
#if defined RA_CFG_OPTION_SETTING_BPS && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_bps") g_bsp_cfg_option_setting_bps[] = {RA_CFG_OPTION_SETTING_BPS};
#endif
#if defined RA_CFG_OPTION_SETTING_BPS_SEC && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_bps_sec") g_bsp_cfg_option_setting_bps_sec[] = {RA_CFG_OPTION_SETTING_BPS_SEC};
#endif
#if defined RA_CFG_OPTION_SETTING_OTP_FSBLCTRL0 && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_otp_fsblctrl0") g_bsp_cfg_option_setting_otp_fsblctrl0[] = {RA_CFG_OPTION_SETTING_OTP_FSBLCTRL0};
#endif
#if defined RA_CFG_OPTION_SETTING_OTP_FSBLCTRL1 && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_otp_fsblctrl1") g_bsp_cfg_option_setting_otp_fsblctrl1[] = {RA_CFG_OPTION_SETTING_OTP_FSBLCTRL1};
#endif
#if defined RA_CFG_OPTION_SETTING_OTP_FSBLCTRL2 && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_otp_fsblctrl2") g_bsp_cfg_option_setting_otp_fsblctrl2[] = {RA_CFG_OPTION_SETTING_OTP_FSBLCTRL2};
#endif
#if defined RA_CFG_OPTION_SETTING_OTP_SAMR && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_otp_samr") g_bsp_cfg_option_setting_otp_samr[] = {RA_CFG_OPTION_SETTING_OTP_SAMR};
#endif
#if defined RA_CFG_OPTION_SETTING_OTP_SACC00 && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_otp_sacc00") g_bsp_cfg_option_setting_otp_sacc00[] = {RA_CFG_OPTION_SETTING_OTP_SACC00};
#endif
#if defined RA_CFG_OPTION_SETTING_OTP_SACC10 && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_otp_sacc10") g_bsp_cfg_option_setting_otp_sacc10[] = {RA_CFG_OPTION_SETTING_OTP_SACC10};
#endif
#if defined RA_CFG_OPTION_SETTING_OTP_SACC01 && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_otp_sacc01") g_bsp_cfg_option_setting_otp_sacc01[] = {RA_CFG_OPTION_SETTING_OTP_SACC01};
#endif
#if defined RA_CFG_OPTION_SETTING_OTP_SACC11 && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_otp_sacc11") g_bsp_cfg_option_setting_otp_sacc11[] = {RA_CFG_OPTION_SETTING_OTP_SACC11};
#endif
#if defined RA_CFG_OPTION_SETTING_OTP_SACC02 && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_otp_sacc02") g_bsp_cfg_option_setting_otp_sacc02[] = {RA_CFG_OPTION_SETTING_OTP_SACC02};
#endif
#if defined RA_CFG_OPTION_SETTING_OTP_SACC12 && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_otp_sacc12") g_bsp_cfg_option_setting_otp_sacc12[] = {RA_CFG_OPTION_SETTING_OTP_SACC12};
#endif
#if defined RA_CFG_OPTION_SETTING_OTP_SACC03 && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_otp_sacc03") g_bsp_cfg_option_setting_otp_sacc03[] = {RA_CFG_OPTION_SETTING_OTP_SACC03};
#endif
#if defined RA_CFG_OPTION_SETTING_OTP_SACC13 && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_otp_sacc13") g_bsp_cfg_option_setting_otp_sacc13[] = {RA_CFG_OPTION_SETTING_OTP_SACC13};
#endif
#if defined RA_CFG_OPTION_SETTING_OTP_PBPS_SEC && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_otp_pbps_sec") g_bsp_cfg_option_setting_otp_pbps_sec[] = {RA_CFG_OPTION_SETTING_OTP_PBPS_SEC};
#endif
#if defined RA_CFG_OPTION_SETTING_OTP_PBPS && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_otp_pbps") g_bsp_cfg_option_setting_otp_pbps[] = {RA_CFG_OPTION_SETTING_OTP_PBPS};
#endif
#if defined RA_CFG_OPTION_SETTING_OTP_ZHUK && !RA_TZ_NONSECURE_BUILD && (RA_CFG_CPU_CORE == 0)
RA_DONT_REMOVE static const uint32_t RA_PLACE_IN_SECTION(".option_setting_otp_zhuk") g_bsp_cfg_option_setting_otp_zhuk[] = {RA_CFG_OPTION_SETTING_OTP_ZHUK};
#endif

#endif /* CONFIG_RA8E1_GROUP */

#endif /* CONFIG_RA_BOOTLOADED_APPLICATION */

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/* NuttX has its own memory initialization in arm_head.S */
typedef enum e_ra_init_mem
{
    INIT_MEM_ZERO,
    INIT_MEM_FLASH,
    INIT_MEM_DATA_FLASH,
    INIT_MEM_RAM,
    INIT_MEM_DTCM,
    INIT_MEM_ITCM,
    INIT_MEM_CTCM,
    INIT_MEM_STCM,
    INIT_MEM_OSPI0_CS0,
    INIT_MEM_OSPI0_CS1,
    INIT_MEM_OSPI1_CS0,
    INIT_MEM_OSPI1_CS1,
    INIT_MEM_QSPI_FLASH,
    INIT_MEM_SDRAM,
} ra_init_mem_t;

typedef struct st_ra_init_type
{
    uint32_t copy_64 :8; /* if 1, must use 64 bit copy operation (to keep ecc happy) */
    uint32_t external :8; /* =1 if either source or destination is external, else 0  */
    uint32_t source_type :8;
    uint32_t destination_type :8;
} ra_init_type_t;

typedef struct st_ra_init_zero_info
{
    uint32_t *const p_base;
    uint32_t *const p_limit;
    ra_init_type_t type;
} ra_init_zero_info_t;

typedef struct st_ra_init_copy_info
{
    uint32_t *const p_base;
    uint32_t *const p_limit;
    uint32_t *const p_load;
    ra_init_type_t type;
} ra_init_copy_info_t;

typedef struct st_ra_init_nocache_info
{
    uint32_t *const p_base;
    uint32_t *const p_limit;
} ra_mpu_nocache_info_t;

typedef struct st_ra_init_info
{
    uint32_t zero_count;
    ra_init_zero_info_t const *const p_zero_list;
    uint32_t copy_count;
    ra_init_copy_info_t const *const p_copy_list;
    uint32_t nocache_count;
    ra_mpu_nocache_info_t const *const p_nocache_list;
} ra_init_info_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

extern ra_init_info_t const g_init_info;
/* These symbols are used for sau/idau configuration in a secure project */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Objects allocated by bsp_linker.c
 **********************************************************************************************************************/
/* DDSC symbol definitions */
/* Zero initialization tables */
extern uint32_t __ospi0_cs0_zero_nocache$$Base;
extern uint32_t __ospi0_cs0_zero_nocache$$Limit;
extern uint32_t __ospi0_cs0_zero$$Base;
extern uint32_t __ospi0_cs0_zero$$Limit;
extern uint32_t __itcm_zero$$Base;
extern uint32_t __itcm_zero$$Limit;
extern uint32_t __dtcm_zero$$Base;
extern uint32_t __dtcm_zero$$Limit;
extern uint32_t __ram_zero_nocache$$Base;
extern uint32_t __ram_zero_nocache$$Limit;
extern uint32_t __ram_zero$$Base;
extern uint32_t __ram_zero$$Limit;
extern uint32_t __ram_tbss$$Base;
extern uint32_t __ram_tbss$$Limit;
static const ra_init_zero_info_t zero_list[] =
{
  {.p_base = &__ospi0_cs0_zero_nocache$$Base, .p_limit = &__ospi0_cs0_zero_nocache$$Limit,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_OSPI0_CS0}},
  {.p_base = &__ospi0_cs0_zero$$Base, .p_limit = &__ospi0_cs0_zero$$Limit,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_OSPI0_CS0}},
  {.p_base = &__itcm_zero$$Base, .p_limit = &__itcm_zero$$Limit,.type={.copy_64 = 1, .external = 0, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_ITCM}},
  {.p_base = &__dtcm_zero$$Base, .p_limit = &__dtcm_zero$$Limit,.type={.copy_64 = 1, .external = 0, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_DTCM}},
  {.p_base = &__ram_zero_nocache$$Base, .p_limit = &__ram_zero_nocache$$Limit,.type={.copy_64 = 0, .external = 0, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_RAM}},
  {.p_base = &__ram_zero$$Base, .p_limit = &__ram_zero$$Limit,.type={.copy_64 = 0, .external = 0, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_RAM}},
  {.p_base = &__ram_tbss$$Base, .p_limit = &__ram_tbss$$Limit,.type={.copy_64 = 0, .external = 0, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_RAM}}
};
/* Load initialization tables */
extern uint32_t __ospi0_cs0_from_ospi0_cs1$$Base;
extern uint32_t __ospi0_cs0_from_ospi0_cs1$$Limit;
extern uint32_t __ospi0_cs0_from_ospi0_cs1$$Load;
extern uint32_t __ospi0_cs0_from_data_flash$$Base;
extern uint32_t __ospi0_cs0_from_data_flash$$Limit;
extern uint32_t __ospi0_cs0_from_data_flash$$Load;
extern uint32_t __ospi0_cs0_from_flash$$Base;
extern uint32_t __ospi0_cs0_from_flash$$Limit;
extern uint32_t __ospi0_cs0_from_flash$$Load;
extern uint32_t __itcm_from_ospi0_cs1$$Base;
extern uint32_t __itcm_from_ospi0_cs1$$Limit;
extern uint32_t __itcm_from_ospi0_cs1$$Load;
extern uint32_t __itcm_from_data_flash$$Base;
extern uint32_t __itcm_from_data_flash$$Limit;
extern uint32_t __itcm_from_data_flash$$Load;
extern uint32_t __itcm_from_flash$$Base;
extern uint32_t __itcm_from_flash$$Limit;
extern uint32_t __itcm_from_flash$$Load;
extern uint32_t __dtcm_from_ospi0_cs1$$Base;
extern uint32_t __dtcm_from_ospi0_cs1$$Limit;
extern uint32_t __dtcm_from_ospi0_cs1$$Load;
extern uint32_t __dtcm_from_data_flash$$Base;
extern uint32_t __dtcm_from_data_flash$$Limit;
extern uint32_t __dtcm_from_data_flash$$Load;
extern uint32_t __dtcm_from_flash$$Base;
extern uint32_t __dtcm_from_flash$$Limit;
extern uint32_t __dtcm_from_flash$$Load;
extern uint32_t __ram_from_ospi0_cs1$$Base;
extern uint32_t __ram_from_ospi0_cs1$$Limit;
extern uint32_t __ram_from_ospi0_cs1$$Load;
extern uint32_t __ram_from_data_flash$$Base;
extern uint32_t __ram_from_data_flash$$Limit;
extern uint32_t __ram_from_data_flash$$Load;
extern uint32_t __ram_from_flash$$Base;
extern uint32_t __ram_from_flash$$Limit;
extern uint32_t __ram_from_flash$$Load;
extern uint32_t __ram_tdata$$Base;
extern uint32_t __ram_tdata$$Limit;
extern uint32_t __ram_tdata$$Load;
static const ra_init_copy_info_t copy_list[] =
{
  {.p_base = &__ospi0_cs0_from_ospi0_cs1$$Base, .p_limit = &__ospi0_cs0_from_ospi0_cs1$$Limit, .p_load = &__ospi0_cs0_from_ospi0_cs1$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_OSPI0_CS1, .destination_type = INIT_MEM_OSPI0_CS0}},
  {.p_base = &__ospi0_cs0_from_data_flash$$Base, .p_limit = &__ospi0_cs0_from_data_flash$$Limit, .p_load = &__ospi0_cs0_from_data_flash$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_DATA_FLASH, .destination_type = INIT_MEM_OSPI0_CS0}},
  {.p_base = &__ospi0_cs0_from_flash$$Base, .p_limit = &__ospi0_cs0_from_flash$$Limit, .p_load = &__ospi0_cs0_from_flash$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_FLASH, .destination_type = INIT_MEM_OSPI0_CS0}},
  {.p_base = &__itcm_from_ospi0_cs1$$Base, .p_limit = &__itcm_from_ospi0_cs1$$Limit, .p_load = &__itcm_from_ospi0_cs1$$Load,.type={.copy_64 = 1, .external = 1, .source_type = INIT_MEM_OSPI0_CS1, .destination_type = INIT_MEM_ITCM}},
  {.p_base = &__itcm_from_data_flash$$Base, .p_limit = &__itcm_from_data_flash$$Limit, .p_load = &__itcm_from_data_flash$$Load,.type={.copy_64 = 1, .external = 0, .source_type = INIT_MEM_DATA_FLASH, .destination_type = INIT_MEM_ITCM}},
  {.p_base = &__itcm_from_flash$$Base, .p_limit = &__itcm_from_flash$$Limit, .p_load = &__itcm_from_flash$$Load,.type={.copy_64 = 1, .external = 0, .source_type = INIT_MEM_FLASH, .destination_type = INIT_MEM_ITCM}},
  {.p_base = &__dtcm_from_ospi0_cs1$$Base, .p_limit = &__dtcm_from_ospi0_cs1$$Limit, .p_load = &__dtcm_from_ospi0_cs1$$Load,.type={.copy_64 = 1, .external = 1, .source_type = INIT_MEM_OSPI0_CS1, .destination_type = INIT_MEM_DTCM}},
  {.p_base = &__dtcm_from_data_flash$$Base, .p_limit = &__dtcm_from_data_flash$$Limit, .p_load = &__dtcm_from_data_flash$$Load,.type={.copy_64 = 1, .external = 0, .source_type = INIT_MEM_DATA_FLASH, .destination_type = INIT_MEM_DTCM}},
  {.p_base = &__dtcm_from_flash$$Base, .p_limit = &__dtcm_from_flash$$Limit, .p_load = &__dtcm_from_flash$$Load,.type={.copy_64 = 1, .external = 0, .source_type = INIT_MEM_FLASH, .destination_type = INIT_MEM_DTCM}},
  {.p_base = &__ram_from_ospi0_cs1$$Base, .p_limit = &__ram_from_ospi0_cs1$$Limit, .p_load = &__ram_from_ospi0_cs1$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_OSPI0_CS1, .destination_type = INIT_MEM_RAM}},
  {.p_base = &__ram_from_data_flash$$Base, .p_limit = &__ram_from_data_flash$$Limit, .p_load = &__ram_from_data_flash$$Load,.type={.copy_64 = 0, .external = 0, .source_type = INIT_MEM_DATA_FLASH, .destination_type = INIT_MEM_RAM}},
  {.p_base = &__ram_from_flash$$Base, .p_limit = &__ram_from_flash$$Limit, .p_load = &__ram_from_flash$$Load,.type={.copy_64 = 0, .external = 0, .source_type = INIT_MEM_FLASH, .destination_type = INIT_MEM_RAM}},
  {.p_base = &__ram_tdata$$Base, .p_limit = &__ram_tdata$$Limit, .p_load = &__ram_tdata$$Load,.type={.copy_64 = 0, .external = 0, .source_type = INIT_MEM_FLASH, .destination_type = INIT_MEM_RAM}}
};
/* nocache regions */
extern uint32_t __ospi0_cs0_noinit_nocache$$Base;
extern uint32_t __ospi0_cs0_noinit_nocache$$Limit;
extern uint32_t __ospi0_cs0_zero_nocache$$Base;
extern uint32_t __ospi0_cs0_zero_nocache$$Limit;
extern uint32_t __ram_noinit_nocache$$Base;
extern uint32_t __ram_noinit_nocache$$Limit;
extern uint32_t __ram_zero_nocache$$Base;
extern uint32_t __ram_zero_nocache$$Limit;
static const ra_mpu_nocache_info_t nocache_list[] =
{
  {.p_base = &__ospi0_cs0_noinit_nocache$$Base, .p_limit = &__ospi0_cs0_zero_nocache$$Limit},
  {.p_base = &__ram_noinit_nocache$$Base, .p_limit = &__ram_zero_nocache$$Limit},
};

/* initialization data structure */
const ra_init_info_t g_init_info =
{
    .zero_count  = sizeof(zero_list) / sizeof(zero_list[0]),
    .p_zero_list = zero_list,
    .copy_count  = sizeof(copy_list) / sizeof(copy_list[0]),
    .p_copy_list = copy_list,
    .nocache_count  = sizeof(nocache_list) / sizeof(nocache_list[0]),
    .p_nocache_list = nocache_list
};

#endif /* CONFIG_RA_LINKER_C */

/* Register protection counters */
static volatile uint16_t g_register_protect_counters[4] = {0};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: showprogress
 *
 * Description:
 *   Print a character on the CONSOLE USART to show boot status.
 *
 ****************************************************************************/

#ifdef CONFIG_DEBUG_FEATURES
#  define showprogress(c)  arm_lowputc(c)
#else
#  define showprogress(c)
#endif

/* Function prototype for nx_start */
void nx_start(void);

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_cortex_m85_init
 *
 * Description:
 *   Initialize Cortex-M85 specific features following Renesas SystemInit
 *
 ****************************************************************************/
static void ra_cortex_m85_init(void)
{
#ifdef CONFIG_ARMV8M_ICACHE
  up_enable_icache();
#endif
#ifdef CONFIG_ARMV8M_DCACHE
  up_enable_dcache();
#endif
#ifdef CONFIG_ARCH_FPU
  arm_fpuconfig();
#endif
#ifdef CONFIG_ARCH_RAMVECTORS
  /* Initialize RAM vectors and set VTOR */
  arm_ramvec_initialize();
#else
  /* Set VTOR to point to the vector table using NuttX symbol */
#if defined(__ICCARM__)
  putreg32((uint32_t)__vector_table, NVIC_VECTAB);
#else
  putreg32((uint32_t)_vectors, NVIC_VECTAB);
#endif
#endif
#if defined(R_FCACHE_FCACHEIV) && defined(R_FCACHE_FCACHEE)
  /* Enable flash cache and wait for it to be ready */
  putreg16(1U, R_FCACHE_FCACHEIV);
  RA_HARDWARE_WAIT(getreg16(R_FCACHE_FCACHEIV), 0U);
  putreg16(1U, R_FCACHE_FCACHEE);
#endif
}

/* Main entry point */
int main(void){

  /* Cortex-M85 Initialization */
  ra_cortex_m85_init();

  /*TrustZone Configuration - early security setup */
#if CONFIG_RA_TZ_SECURE_BUILD || CONFIG_RA_TZ_NONSECURE_BUILD
  ra_trustzone_init();
#endif

  /* Core and Clock Initialization */
  /* Setup System Clocks (includes Cortex-M85 core features) */
  ra_clock();

  /* Set Vector Table Base Address */
  ra_vector_table_init();

  /* Memory Initialization */
  /* Initialize internal RAM Sections (BSS, data, TCM) */
  ra_ram_init(0);

  /* Initialize external RAM Sections (BSS, data, TCM) */
  ra_ram_init(1);

  /* Initialize GPIO security attribution */
  ra_gpio_security_init();

  /* Perform early serial initialization */
#ifdef USE_EARLYSERIALINIT
  /* Low-level Hardware Setup */
  /* Configure the uart pins for arm_earlyserialinit */
  ra_lowsetup();

  /* The 'A' character is not displayed because the UART hardware is not fully ready */
  //showprogress('A');
  arm_earlyserialinit();
#else
  /* No early serial initialization - console will be set up later */
  //showprogress('A');
#endif

  //showprogress('B');

  /* Board-level Initialization */
  /* Initialize onboard resources */
  ra_board_initialize();
  //showprogress('C');

  /* Start NuttX */
  /* Then start NuttX main initialization */
  //showprogress('\r');
  //showprogress('\n');

  nx_start();

  return 0;
}

/****************************************************************************
 * Name: __start
 *
 * Description:
 *   This is the reset entry point.
 *
 ****************************************************************************/

void __start(void)
{
  /* Main entry point */
  main();
  /* Shouldn't get here */
  for (; ; )
    {
    }
}

/* Additional initialization functions for RA8E1 startup */

/****************************************************************************
 * Name: ra_option_bytes_init
 *
 * Description:
 *   Initialize option bytes (security and boot configuration)
 *   Following Renesas bsp_linker.c approach
 *
 ****************************************************************************/

void ra_option_bytes_init(void)
{
  /* Configure option bytes for security, boot, etc. */
  /* Option bytes are typically handled by linker sections and bootloader */
  /* On RA8E1, these are defined in ra_start.h and placed by linker */

  /* Option bytes include:
   * - RA_OPTION_SETTING_OFS0: IWDT and WDT settings
   * - RA_OPTION_SETTING_OFS2: Boot mode selection
   * - RA_OPTION_SETTING_OFS1_SEC: Security settings for TrustZone
   * - RA_OPTION_SETTING_OFS1_SEL: Secure/Non-secure selection
   */

  /* These are handled automatically by the linker script and bootloader */
  /* No runtime configuration needed here */
}

/****************************************************************************
 * Name: ra_trustzone_init
 *
 * Description:
 *   Initialize ARM TrustZone features following Renesas SystemInit
 *
 ****************************************************************************/

void ra_trustzone_init(void)
{
#if defined(CONFIG_RA_TZ_SECURE_BUILD)
  /* Enable TrustZone Secure settings following Renesas SystemInit */
  /* Seal the main stack for secure projects */
  /* Reference: https://developer.arm.com/documentation/100720/0300 */
  /* uint32_t * p_main_stack_top = (uint32_t *) &g_main_stack[CONFIG_RA_SECURE_STACK_BYTES]; */
  /* *p_main_stack_top = RA_TZ_STACK_SEAL_VALUE; */

  /* Configure SAU, IDAU, and secure memory regions */
  /* RA_SecurityInit(); */

#elif defined(CONFIG_RA_TZ_NONSECURE_BUILD)
  /* Configure non-secure memory regions and permissions */
  /* Non-secure VTOR is set by secure project, skip here */
#endif
}

/****************************************************************************
 * Name: ra_vector_table_init
 *
 * Description:
 *   Initialize vector table following Renesas SystemInit
 *
 ****************************************************************************/

void ra_vector_table_init(void)
{
  /* Set VTOR to point to the vector table base address */
  /* Following Renesas SystemInit: SCB->VTOR = (uint32_t) &__VECTOR_TABLE; */
#if !CONFIG_RA_TZ_NONSECURE_BUILD
  /* VTOR is in undefined state out of RESET, set it explicitly */
  /* Use NuttX standard method to set vector table */
  /* Note: This will be handled by the ARM core initialization later */
  /* For now, just ensure the vector table is properly set in linker script */
#endif
}

/****************************************************************************
 * Name: ra_tcm_init
 *
 * Description:
 *   Initialize TCM memories following Renesas SystemInit
 *
 ****************************************************************************/

void ra_tcm_init(void)
{
#if defined(CONFIG_ARMV8M_HAVE_ITCM) || defined(CONFIG_ARMV8M_HAVE_DTCM)
  /* Following Renesas SystemInit:
   * Zero initialize TCM memory if ECC is enabled and this is the first project
   * This prevents ECC errors on first access
   */

  /* TCM initialization will be handled by NuttX memory management */
  /* The linker script should properly configure TCM regions */
#endif
}

/****************************************************************************
 * Name: ra_ram_init
 *
 * Description:
 *   Initialize RAM sections following standard NuttX ARM startup
 *
 ****************************************************************************/
void ra_ram_init (const uint32_t external)
{
#if 0 // Disable standard NuttX RAM initialization
    const register uint32_t *src;
    register uint32_t *dest;

    /* Clear .bss.  We'll do this inline (vs. calling memset) just to be
     * certain that there are no issues with the state of global variables.
     */
    extern uint32_t _sbss;
    extern uint32_t _ebss;

    for (dest = (uint32_t *)&_sbss; dest < (uint32_t *)&_ebss; )
    {
      *dest++ = 0;
    }

    /* Move the initialized data section from his temporary holding spot in
     * FLASH into the correct place in RAM.  The correct place in RAM is
     * given by _sdata and _edata.  The temporary location is in FLASH at the
     * end of all of the other read-only data (.text, .rodata) at _eronly.
     */
    extern const uint32_t _eronly;  // Flash location (const)
    extern uint32_t _sdata;         // RAM location
    extern uint32_t _edata;         // RAM location

    for (src = (const uint32_t *)&_eronly,
         dest = (uint32_t *)&_sdata; dest < (uint32_t *)&_edata;
      )
    {
      *dest++ = *src++;  // CRITICAL: Copy initialized .data from flash!
    }
#else

    /* Use custom memory sections */
    for (uint32_t i = 0; i < g_init_info.zero_count; i++)
    {
        if (external == g_init_info.p_zero_list[i].type.external)
        {
            memset(g_init_info.p_zero_list[i].p_base, 0U,
                   ((uintptr_t) g_init_info.p_zero_list[i].p_limit - (uintptr_t) g_init_info.p_zero_list[i].p_base));
        }
    }

    for (uint32_t i = 0; i < g_init_info.copy_count; i++)
    {
        if (external == g_init_info.p_copy_list[i].type.external)
        {
            memcpy(g_init_info.p_copy_list[i].p_base, g_init_info.p_copy_list[i].p_load,
                   ((uintptr_t) g_init_info.p_copy_list[i].p_limit - (uintptr_t) g_init_info.p_copy_list[i].p_base));
        }
    }
#endif
}


/****************************************************************************
 * Name: ra_register_protect_enable
 *
 * Description:
 *   Enable register protection
 *
 * Input Parameters:
 *   regs_to_protect - Registers which have write protection enabled
 *
 ****************************************************************************/

void ra_register_protect_enable(ra_reg_protect_t regs_to_protect)
{
  irqstate_t flags;
  uint16_t prcr_masks[] = {0x0001, 0x0002, 0x0008, 0x0010};

  flags = enter_critical_section();

  /* Is it safe to disable write access? */
  if (g_register_protect_counters[regs_to_protect] != 0)
    {
      g_register_protect_counters[regs_to_protect]--;
    }

  /* If counter reaches zero, enable protection */
  if (g_register_protect_counters[regs_to_protect] == 0)
    {
      uint16_t prcr_value = getreg16(R_SYSC_PRCR_S);
      prcr_value = (prcr_value | R_SYSC_PRCR_S_KEY) &
                   (~prcr_masks[regs_to_protect]);
      putreg16(prcr_value, R_SYSC_PRCR_S);
    }

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: ra_register_protect_disable
 *
 * Description:
 *   Disable register protection
 *
 * Input Parameters:
 *   regs_to_unprotect - Registers which have write protection disabled
 *
 ****************************************************************************/

void ra_register_protect_disable(ra_reg_protect_t regs_to_unprotect)
{
  irqstate_t flags;
  uint16_t prcr_masks[] = {0x0001, 0x0002, 0x0008, 0x0010};

  flags = enter_critical_section();

  /* If this is first entry then disable protection */
  if (g_register_protect_counters[regs_to_unprotect] == 0)
    {
      uint16_t prcr_value = getreg16(R_SYSC_PRCR_S);
      prcr_value = (prcr_value | R_SYSC_PRCR_S_KEY) |
                   prcr_masks[regs_to_unprotect];
      putreg16(prcr_value, R_SYSC_PRCR_S);
    }

  /* Increment the protect counter */
  g_register_protect_counters[regs_to_unprotect]++;

  leave_critical_section(flags);
}


/****************************************************************************
 * Name: ra_gpio_security_init
 *
 * Description:
 *   Initialize PMSAR and PSCU registers to their default values.
 *   Sets all port pins to secure mode (0) as per  implementation.
 *   Must be called before configuring any port pins.
 *
 ****************************************************************************/

void ra_gpio_security_init(void)
{
  uint32_t i;

  /* Disable register protection for SAR (Security Attribution Registers) */
  ra_register_protect_disable(RA_REG_PROTECT_SAR);

  /* Set all PMSAR registers to 0 (secure mode for all pins) */
  for (i = 0; i < PFS_MAX_CHANNELS; i++)
    {
      putreg16(0U, R_PFS_PMSAR(i));
    }

  /* Set all PSCU registers to 0 (secure mode) */
  putreg32(0U, R_PSCU_PSARB);
  putreg32(0U, R_PSCU_PSARC);
  putreg32(0U, R_PSCU_PSARD);
  putreg32(0U, R_PSCU_PSARE);

  /* Re-enable register protection for SAR */
  ra_register_protect_enable(RA_REG_PROTECT_SAR);
}

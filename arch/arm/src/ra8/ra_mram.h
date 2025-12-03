/****************************************************************************
 * arch/arm/src/ra8/ra_mram.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_MRAM_H
#define __ARCH_ARM_SRC_RA8_RA_MRAM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include "chip.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* RA8P1 MRAM Memory Configuration
 * The RA8P1 uses MRAM (Magnetoresistive RAM) instead of traditional flash.
 * MRAM provides faster write speeds and higher endurance than flash.
 */

/* MRAM programming block size - RA8P1 uses 32-byte programming granularity */

#define RA_MRAM_PROGRAMMING_SIZE    32     /* 32-byte programming block */

/* Code MRAM configuration for RA8P1 */

#define RA_MRAM_CODE_START          0x02000000  /* Code MRAM start address */
#define RA_MRAM_CODE_SIZE           0x00200000  /* 2MB Code MRAM */
#define RA_MRAM_CODE_BLOCK_SIZE     RA_MRAM_PROGRAMMING_SIZE

/* Note: RA8P1 does not have separate data flash - use code MRAM partition
 * for parameter storage. Define a reserved area at end of code MRAM.
 */

#define RA_MRAM_DATA_START          0x021F0000  /* Last 64KB reserved for data */
#define RA_MRAM_DATA_SIZE           0x00010000  /* 64KB data area */
#define RA_MRAM_DATA_BLOCK_SIZE     RA_MRAM_PROGRAMMING_SIZE

/* MRAM Controller Base Address */

#ifndef R_MRMS_BASE
#  if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#    define R_MRMS_BASE             0x4013C000  /* Secure base address */
#  else
#    define R_MRMS_BASE             0x5013C000  /* Non-secure base address */
#  endif
#endif

/* MACI Command Issuing Area */

#define R_MRAM_CMD_BASE             0x40120000

/* MRAM Register Offsets (from R_MRMS_BASE) */

#define R_MRMS_MRCPFB_OFFSET        0x0000  /* Code MRAM Prefetch Buffer Enable */
#define R_MRMS_MRCFREQ_OFFSET       0x0004  /* Code MRAM Frequency Notifications */
#define R_MRMS_MREFREQ_OFFSET       0x0008  /* Extra MRAM Frequency Notifications */
#define R_MRMS_MRCDECC_OFFSET       0x0010  /* Code MRAM ECC Decoder Control */
#define R_MRMS_MRCRAEINT_OFFSET     0x0014  /* Code MRAM Read Access Error Int Enable */
#define R_MRMS_MRCRAES_OFFSET       0x0018  /* Code MRAM Read Access Error Status */
#define R_MRMS_MRCRTEA_OFFSET       0x001C  /* Code MRAM TED Error Address */
#define R_MRMS_MRCRDEA_OFFSET       0x0020  /* Code MRAM DEC Error Address */
#define R_MRMS_MREZS_OFFSET         0x0400  /* Extra MRAM Zeroization Status */
#define R_MRMS_MREZC_OFFSET         0x0404  /* Extra MRAM Zeroization Control */
#define R_MRMS_MASTAT_OFFSET        0x2010  /* Extra MRAM Access Status */
#define R_MRMS_MPAEINT_OFFSET       0x2014  /* Extra MRAM Access Error Int Enable */
#define R_MRMS_MRDYIE_OFFSET        0x2018  /* Extra MRAM Ready Int Enable */
#define R_MRMS_MSADDR_OFFSET        0x2030  /* MACI Command Start Address */
#define R_MRMS_MCNTSELR_OFFSET      0x2048  /* MRAM Counter Select */
#define R_MRMS_MCNTDTR0_OFFSET      0x204C  /* MRAM Counter Data 0 */
#define R_MRMS_MCNTDTR1_OFFSET      0x2050  /* MRAM Counter Data 1 */
#define R_MRMS_MSTATR_OFFSET        0x2080  /* Extra MRAM Status */
#define R_MRMS_MENTRYR_OFFSET       0x2084  /* Extra MRAM Program Mode Entry */
#define R_MRMS_MSUINITR_OFFSET      0x208C  /* Extra MRAM Sequencer Setup Init */
#define R_MRMS_MCMDR_OFFSET         0x20A0  /* MACI Command */
#define R_MRMS_MSUASMON_OFFSET      0x20DC  /* MRAM Startup Area Select Monitor */
#define R_MRMS_MSUACR_OFFSET        0x20E8  /* MRAM Startup Area Control */
#define R_MRMS_MRPSC_OFFSET         0x2800  /* MRAM Program Speed Control */
#define R_MRMS_MRCPC0_OFFSET        0x3000  /* Code MRAM Program Control (NS) */
#define R_MRMS_MRCPC1_OFFSET        0x3004  /* Code MRAM Program Control (S) */
#define R_MRMS_MRCBPROT0_OFFSET     0x3008  /* Code MRAM Block Protection (NS) */
#define R_MRMS_MRCBPROT1_OFFSET     0x300C  /* Code MRAM Block Protection (S) */
#define R_MRMS_MRCPS_OFFSET         0x3010  /* Code MRAM Program Status */
#define R_MRMS_MRCPAEINT_OFFSET     0x3014  /* Code MRAM Program Access Error Int */
#define R_MRMS_MRCPEA_OFFSET        0x3018  /* Code MRAM Program Error Address */
#define R_MRMS_MRCFLR_OFFSET        0x3030  /* Code MRAM Flush */
#define R_MRMS_MRCEECC_OFFSET       0x3804  /* Code MRAM ECC Encoder Control */

/* MRAM Register Addresses */

#define R_MRMS_MRCPFB               (R_MRMS_BASE + R_MRMS_MRCPFB_OFFSET)
#define R_MRMS_MRCFREQ              (R_MRMS_BASE + R_MRMS_MRCFREQ_OFFSET)
#define R_MRMS_MREFREQ              (R_MRMS_BASE + R_MRMS_MREFREQ_OFFSET)
#define R_MRMS_MRCDECC              (R_MRMS_BASE + R_MRMS_MRCDECC_OFFSET)
#define R_MRMS_MRCRAEINT            (R_MRMS_BASE + R_MRMS_MRCRAEINT_OFFSET)
#define R_MRMS_MRCRAES              (R_MRMS_BASE + R_MRMS_MRCRAES_OFFSET)
#define R_MRMS_MRCRTEA              (R_MRMS_BASE + R_MRMS_MRCRTEA_OFFSET)
#define R_MRMS_MRCRDEA              (R_MRMS_BASE + R_MRMS_MRCRDEA_OFFSET)
#define R_MRMS_MREZS                (R_MRMS_BASE + R_MRMS_MREZS_OFFSET)
#define R_MRMS_MREZC                (R_MRMS_BASE + R_MRMS_MREZC_OFFSET)
#define R_MRMS_MASTAT               (R_MRMS_BASE + R_MRMS_MASTAT_OFFSET)
#define R_MRMS_MPAEINT              (R_MRMS_BASE + R_MRMS_MPAEINT_OFFSET)
#define R_MRMS_MRDYIE               (R_MRMS_BASE + R_MRMS_MRDYIE_OFFSET)
#define R_MRMS_MSADDR               (R_MRMS_BASE + R_MRMS_MSADDR_OFFSET)
#define R_MRMS_MCNTSELR             (R_MRMS_BASE + R_MRMS_MCNTSELR_OFFSET)
#define R_MRMS_MCNTDTR0             (R_MRMS_BASE + R_MRMS_MCNTDTR0_OFFSET)
#define R_MRMS_MCNTDTR1             (R_MRMS_BASE + R_MRMS_MCNTDTR1_OFFSET)
#define R_MRMS_MSTATR               (R_MRMS_BASE + R_MRMS_MSTATR_OFFSET)
#define R_MRMS_MENTRYR              (R_MRMS_BASE + R_MRMS_MENTRYR_OFFSET)
#define R_MRMS_MSUINITR             (R_MRMS_BASE + R_MRMS_MSUINITR_OFFSET)
#define R_MRMS_MCMDR                (R_MRMS_BASE + R_MRMS_MCMDR_OFFSET)
#define R_MRMS_MSUASMON             (R_MRMS_BASE + R_MRMS_MSUASMON_OFFSET)
#define R_MRMS_MSUACR               (R_MRMS_BASE + R_MRMS_MSUACR_OFFSET)
#define R_MRMS_MRPSC                (R_MRMS_BASE + R_MRMS_MRPSC_OFFSET)
#define R_MRMS_MRCPC0               (R_MRMS_BASE + R_MRMS_MRCPC0_OFFSET)
#define R_MRMS_MRCPC1               (R_MRMS_BASE + R_MRMS_MRCPC1_OFFSET)
#define R_MRMS_MRCBPROT0            (R_MRMS_BASE + R_MRMS_MRCBPROT0_OFFSET)
#define R_MRMS_MRCBPROT1            (R_MRMS_BASE + R_MRMS_MRCBPROT1_OFFSET)
#define R_MRMS_MRCPS                (R_MRMS_BASE + R_MRMS_MRCPS_OFFSET)
#define R_MRMS_MRCPAEINT            (R_MRMS_BASE + R_MRMS_MRCPAEINT_OFFSET)
#define R_MRMS_MRCPEA               (R_MRMS_BASE + R_MRMS_MRCPEA_OFFSET)
#define R_MRMS_MRCFLR               (R_MRMS_BASE + R_MRMS_MRCFLR_OFFSET)
#define R_MRMS_MRCEECC              (R_MRMS_BASE + R_MRMS_MRCEECC_OFFSET)

/* Register Bit Definitions */

/* MRCPFB - Prefetch Buffer Enable */

#define R_MRMS_MRCPFB_MPFBEN        (1 << 0)   /* Prefetch buffer enable */

/* MRCPS - Program Status Register */

#define R_MRMS_MRCPS_PRGERRC        (1 << 0)   /* Programming Error */
#define R_MRMS_MRCPS_ECCERRC        (1 << 1)   /* ECC Error */
#define R_MRMS_MRCPS_ABUFEMP        (1 << 5)   /* Address Buffer Empty */
#define R_MRMS_MRCPS_ABUFFULL       (1 << 6)   /* Address Buffer Full */
#define R_MRMS_MRCPS_PRGBSYC        (1 << 7)   /* Code MRAM Program Busy */

/* MASTAT - Access Status Register */

#define R_MRMS_MASTAT_MREAE         (1 << 3)   /* Extra MRAM Access Violation */
#define R_MRMS_MASTAT_CMDLK         (1 << 4)   /* Command Lock Flag */

/* MSTATR - Extra MRAM Status Register */

#define R_MRMS_MSTATR_CFGSETERR     (1 << 5)   /* Configuration Set Error */
#define R_MRMS_MSTATR_PRGERR        (1 << 12)  /* Programming Error */
#define R_MRMS_MSTATR_ILGLERR       (1 << 14)  /* Illegal Command Error */
#define R_MRMS_MSTATR_MRDY          (1 << 15)  /* Extra MRAM Ready */
#define R_MRMS_MSTATR_TZFERR        (1 << 19)  /* TrustZone Filter Error */
#define R_MRMS_MSTATR_OTERR         (1 << 20)  /* Other Error */
#define R_MRMS_MSTATR_SECERR        (1 << 21)  /* Security Error */
#define R_MRMS_MSTATR_ILGCOMERR     (1 << 23)  /* Illegal Command Error */

/* MENTRYR - P/E Mode Entry Register */

#define R_MRMS_MENTRYR_PE_MODE      0x0080     /* P/E mode bits */
#define R_MRMS_MENTRYR_KEY          0xAA00     /* Key code */
#define R_MRMS_MENTRYR_TRANSITION   0xAA80     /* Transition to P/E mode */
#define R_MRMS_MENTRYR_READ_MODE    0xAA00     /* Transition to read mode */

/* MRCPC0/MRCPC1 - Program Control Registers */

#define R_MRMS_MRCPC0_KEY           0x8600     /* Key for non-secure program */
#define R_MRMS_MRCPC1_KEY           0x6800     /* Key for secure program */
#define R_MRMS_MRCPC_ENABLE         0x0001     /* Program enable bit */

/* MRCFLR - Flush Register */

#define R_MRMS_MRCFLR_KEY           0xC300     /* Key code */
#define R_MRMS_MRCFLR_FLUSH         0xC301     /* Flush command with key */

/* MSUACR - Startup Area Control Register */

#define R_MRMS_MSUACR_KEY           0x6600     /* Key code */

/* MREZS - Zeroization Status */

#define R_MRMS_MREZS_WHUKZF         (1 << 0)   /* W-HUK Zero Flag */
#define R_MRMS_MREZS_WHUKEXE        (1 << 1)   /* W-HUK Zeroization Executing */

/* MACI Commands */

#define MRAM_MACI_CMD_STATUS_CLEAR  0x50       /* Status clear command */
#define MRAM_MACI_CMD_FORCED_STOP   0xB3       /* Forced stop command */
#define MRAM_MACI_CMD_CONFIG_SET_1  0x40       /* Configuration set part 1 */
#define MRAM_MACI_CMD_CONFIG_SET_2  0x08       /* Configuration set part 2 */
#define MRAM_MACI_CMD_FINAL         0xD0       /* Final command */

/* Timeout values (in microseconds) */

#define MRAM_TIMEOUT_WRITE_US       100        /* Max write time */
#define MRAM_TIMEOUT_MACI_CMD_US    4          /* Max MACI command time */
#define MRAM_TIMEOUT_CONFIG_SET_US  10000      /* Max config set time */

/* TrustZone offset for non-secure access */

#define RA_TZ_NS_OFFSET             0x10000000

/****************************************************************************
 * Public Types
 ****************************************************************************/

struct mtd_dev_s;  /* Forward declaration */

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Name: ra_mram_initialize
 *
 * Description:
 *   Initialize the MRAM MTD device driver for either Code MRAM or
 *   Data MRAM partition.
 *
 * Input Parameters:
 *   data_flash - true for Data MRAM partition, false for Code MRAM
 *
 * Returned Value:
 *   Pointer to MTD device structure on success; NULL on failure
 *
 ****************************************************************************/

struct mtd_dev_s *ra_mram_initialize(bool data_flash);

/****************************************************************************
 * Name: ra_mram_erasestate
 *
 * Description:
 *   Return the erase state of MRAM (0xFF for erased bytes).
 *
 * Returned Value:
 *   The erase state value (0xFF)
 *
 ****************************************************************************/

uint8_t ra_mram_erasestate(void);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RA8_RA_MRAM_H */

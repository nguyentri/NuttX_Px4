/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/scripts/cm33/evk-ra8p1_cm33.ld
 *
 * Modular Linker Script for Cortex-M33 (CPU1) on Renesas RA8P1
 * Preserves all Renesas FSP symbols required by ra_start.c
 ****************************************************************************/

/* Memory region base addresses for CM33 */
FLASH_START = 0x02080000;
FLASH_LENGTH = 0x00080000;
RAM_START = 0x220EA000;
RAM_LENGTH = 0x000EA000;
ITCM_START = 0x00000000;
ITCM_LENGTH = 0x00010000;
DTCM_START = 0x20000000;
DTCM_LENGTH = 0x00010000;
OSPI0_CS0_START = 0x88000000;
OSPI0_CS0_LENGTH = 0x08000000;
IPC_SHMEM_START = 0x220E2000;
IPC_SHMEM_LENGTH = 0x00008000;
SDRAM_START = 0x6C000000;
SDRAM_LENGTH = 0x04000000;
OSPI0_CS1_START = 0x90000000;
OSPI0_CS1_LENGTH = 0x04000000;
OSPI1_CS0_START = 0x70000000;
OSPI1_CS0_LENGTH = 0x08000000;
OSPI1_CS1_START = 0xA0000000;
OSPI1_CS1_LENGTH = 0x04000000;
DATA_FLASH_START = 0x08000000;
DATA_FLASH_LENGTH = 0x00010000;
FLASH_APP_START = OSPI0_CS0_START;
FLASH_APP_LENGTH = OSPI0_CS0_LENGTH;

MEMORY
{
    FLASH (rx) : ORIGIN = FLASH_START, LENGTH = FLASH_LENGTH
    RAM (rwx) : ORIGIN = RAM_START, LENGTH = RAM_LENGTH
    ITCM (rwx) : ORIGIN = ITCM_START, LENGTH = ITCM_LENGTH
    DTCM (rwx) : ORIGIN = DTCM_START, LENGTH = DTCM_LENGTH
    FLASH_APP (rx) : ORIGIN = FLASH_APP_START, LENGTH = FLASH_APP_LENGTH
    SDRAM (rwx) : ORIGIN = SDRAM_START, LENGTH = SDRAM_LENGTH
    OSPI0_CS0 (rx) : ORIGIN = OSPI0_CS0_START, LENGTH = OSPI0_CS0_LENGTH
    OSPI0_CS1 (rx) : ORIGIN = OSPI0_CS1_START, LENGTH = OSPI0_CS1_LENGTH
    OSPI1_CS0 (rx) : ORIGIN = OSPI1_CS0_START, LENGTH = OSPI1_CS0_LENGTH
    OSPI1_CS1 (rx) : ORIGIN = OSPI1_CS1_START, LENGTH = OSPI1_CS1_LENGTH
    DATA_FLASH (r) : ORIGIN = DATA_FLASH_START, LENGTH = DATA_FLASH_LENGTH
    IPC_SHMEM_REGION (rw) : ORIGIN = IPC_SHMEM_START, LENGTH = IPC_SHMEM_LENGTH
}

OUTPUT_ARCH(arm)
EXTERN(_vectors)
ENTRY(_stext)

INCLUDE ../common/renesas_copy_sections.ld
INCLUDE ../common/renesas_zero_sections.ld
INCLUDE cm33_kernel_sections.ld
INCLUDE cm33_ipc_sections.ld

PROVIDE( _sdata = ADDR(__ram_from_flash$$) );
PROVIDE( _edata = ADDR(__ram_from_flash$$) + SIZEOF(__ram_from_flash$$) );
PROVIDE( _stext = ADDR(__flash_readonly$$));
PROVIDE( _etext = ADDR(__flash_readonly$$) + SIZEOF(__flash_readonly$$) );
PROVIDE( _eronly = ADDR(__flash_readonly$$) + SIZEOF(__flash_readonly$$) );
PROVIDE( _sbss = ADDR(__ram_zero$$) );
PROVIDE( _ebss = ADDR(__ram_zero$$) + SIZEOF(__ram_zero$$) );

/* Move CM33 code SRAM regions to a high, non-overlapping address range */
SRAM_CODE_S_START = 0xA0000000;
SRAM_CODE_S_LENGTH = 0x10000000;
SRAM_CODE_N_START = 0xA1000000;
SRAM_CODE_N_LENGTH = 0x10000000;
SRAM_DATA_S_START = 0x20000000;
SRAM_DATA_S_LENGTH = 0x10000000;
SRAM_DATA_N_START = 0x30000000;
SRAM_DATA_N_LENGTH = 0x10000000;
XSPIFLASH_S_START = 0x60000000;
XSPIFLASH_S_LENGTH = 0x10000000;
XSPIFLASH_N_START = 0x70000000;
XSPIFLASH_N_LENGTH = 0x10000000;
DDR_S_START = 0x80000000;
DDR_S_LENGTH = 0x10000000;
DDR_N_START = 0x90000000;
DDR_N_LENGTH = 0x10000000;

DDR_START  = DDR_S_START;
DDR_LENGTH = 0x00800000;

BOOTPARAM_START  = SRAM_CODE_S_START + 0x08001E00;
BOOTPARAM_LENGTH = 0x00000200;
DUMMY_START      = SRAM_CODE_S_START + 0x08002000;
DUMMY_LENGTH     = 0x00000008;
SRAM_START       = SRAM_CODE_S_START + 0x08002800;
SRAM_LENGTH      = 0x000FC7FF;

/* Memory allocation OpenAMP using ddr. */
OPENAMP_RSCTBL_START    = DDR_S_START + 0x02f00000;
OPENAMP_RSCTBL_LENGTH   = 0x00001000;
MHU_SHMEM_START         = DDR_S_START + 0x02f01000;
MHU_SHMEM_LENGTH        = 0x00001000;
OPENAMP_VRING_START     = DDR_S_START + 0x03000000;
OPENAMP_VRING_LENGTH    = 0x00F00000;

MEMORY
{
  BOOTPARAM (rx)    : ORIGIN = BOOTPARAM_START,     LENGTH = BOOTPARAM_LENGTH
  DUMMY             : ORIGIN = DUMMY_START,         LENGTH = DUMMY_LENGTH
  SRAM      (rwx)   : ORIGIN = SRAM_START,          LENGTH = SRAM_LENGTH
  DDR       (rw)    : ORIGIN = DDR_START,           LENGTH = DDR_LENGTH
  OPENAMP_RSCTBL(rw): ORIGIN = OPENAMP_RSCTBL_START,LENGTH = OPENAMP_RSCTBL_LENGTH
  MHU_SHMEM(rw)     : ORIGIN = MHU_SHMEM_START,     LENGTH = MHU_SHMEM_LENGTH
  OPENAMP_VRING(rw) : ORIGIN = OPENAMP_VRING_START, LENGTH = OPENAMP_VRING_LENGTH
}

/* Library configurations */
GROUP(libgcc.a libc.a libm.a libnosys.a)

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions CODE, RAM and etc.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler_S : Entry of secure reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 *   __Vectors_End
 *   __Vectors_Size
 */
ENTRY(Entry_Function_S)
SECTIONS
{
    .rodata.bootparam :
    {
        LONG(__RAM_segment_used_end__ - 0x08000000)
        FILL(0xFFFFFFFF);
        . += 0xC;
        LONG(0x00000A00);/* 0x200(BOOTPARAM size) + 0x800(gap size to Reset_Handler_S */
        FILL(0xFFFFFFFF);
        . += 0xC;
        LONG(_Reset_Handler_S + 0x20000000);
        FILL(0xFFFFFFFF);
        . += 0x1DA;
        SHORT(0xAA55)
    } > BOOTPARAM

    .text.boot :
    {
        _Reset_Handler_S = .;
        KEEP(*(.text.Reset_Handler_S))
        _Entry_Function_S = .;
        KEEP(*(.text.Entry_Function_S))
        . = ALIGN(0x1000);
        KEEP(*(.fixed_secure_vectors*))
        KEEP(*(.application_vectors*))

        *(.text*)
        KEEP(*(.version))
        KEEP(*(.init))
        KEEP(*(.fini))
        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(* crtend?.o * crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)
        /* .dtors */
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(* crtend?.o * crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)
        *(.rodata*)
        KEEP(*(.eh_frame*))
    } > SRAM

    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > SRAM
    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > SRAM
    __exidx_end = .;
    __etext = .;

    .loader_dummy :
    {
        _loader_dummy_start = .;
        KEEP(*(.loader_dummy));
        _loader_dummy_end = .;
    } > DUMMY AT > SRAM

    /* Initialized data section. */
    .data :
    {
        __data_start__ = .;
        . = ALIGN(4);
        __Code_In_RAM_Start = .;
        KEEP(*(.code_in_ram*))
        __Code_In_RAM_End = .;
        *(vtable)
        /* Don't use *(.data*) because it will place data meant for .data_flash in this section. */
        *(.data.*)
        *(.data)
        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN(__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN(__preinit_array_end = .);
        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN(__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN(__init_array_end = .);
        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN(__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN(__fini_array_end = .);
        KEEP(*(.jcr*))
        . = ALIGN(4);
        /* All data end */
        __data_end__ = .;
    } > SRAM

    /* secure stacks are stored in this section. */
    .stack (NOLOAD) :
    {
        __S_StackLimit = .;
        /* secure main stack */
        KEEP(*(.s_stack))
        __S_StackTop = .;
    } > SRAM

    .bss.noinit (NOLOAD) :
    {
        . = ALIGN(4);
        __noinit_start = .;
        KEEP(*(.noinit*))
        . = ALIGN(8);
        /* Place the FreeRTOS heap here so that the __HeapLimit calculation does not include the freertos heap. */
        KEEP(*(.heap.*))
        __noinit_end = .;
    } > SRAM

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > SRAM

    .gnu.sgstubs : ALIGN (32)
    {
        . = ALIGN(32);
        _start_sg = .;
        *(.gnu.sgstubs*)
        . = ALIGN(32);
        _end_sg = .;
    } > SRAM

    .heap (NOLOAD) :
    {
        . = ALIGN(8);
        __HeapBase = .;
        /* Place the STD heap here. */
        KEEP(*(.heap))
        __HeapLimit = .;
    } > SRAM

    /* Stacks are stored in this section. */
    .stack (NOLOAD) :
    {
        . = ALIGN(8);
        __StackLimit = .;
        /* Main stack */
        KEEP(*(.stack))
        __StackTop = .;
        /* Thread stacks */
        KEEP(*(.stack*))
        __StackTopAll = .;
    } > SRAM
    PROVIDE(__stack = __StackTopAll);

    /* This symbol represents the end of user allocated RAM. The RAM after this symbol can be used
     at run time for things such as ThreadX memory pool allocations. */
    __RAM_segment_used_end__ = ALIGN(__StackTopAll , 4);

    /* DDR buffer, default empty */
    .ddr_buffer (NOLOAD) :
    {
        . = ALIGN ( 0x10 ) ;
        PROVIDE(_ddr_buffer_start = .);
        PROVIDE(_ddrbuffer_end = .);
    } > DDR

    __tz_MHU_SHMEM = ABSOLUTE ( MHU_SHMEM_START ) ;
    . = __tz_MHU_SHMEM;
    .resource_table :
    {
        PROVIDE(__rsctbl_start = .);
        *  (  .resource_table  )
        PROVIDE(__rsctbl_end = .);
    } > OPENAMP_RSCTBL
    __tz_MHU_SHMEM = ABSOLUTE ( MHU_SHMEM_START ) ;
    . = __tz_MHU_SHMEM;
    .mhu_shmem (NOLOAD) :
    {
        PROVIDE(__mhu_shmem_start = .);
        . += MHU_SHMEM_LENGTH;
        PROVIDE(__mhu_shmem_end = .);
    } > MHU_SHMEM
    __tz_OPENAMP_VRING = ABSOLUTE ( OPENAMP_VRING_START ) ;
    . = __tz_OPENAMP_VRING;
    .vring (NOLOAD) :
    {
        PROVIDE(__vring_start = .);
        . += OPENAMP_VRING_LENGTH;
        PROVIDE(__vring_end = .);
    } > OPENAMP_VRING

}

/* Provide required symbols for libgcc even though we don't use exception handling */
__exidx_start = 0;
__exidx_end = 0;

/* NuttX specific symbol definitions (using existing computed symbols) */
PROVIDE( _sinit = __init_array_start );
PROVIDE( _einit = __init_array_end );
/* Flash area containing data to copy to RAM starts at _itcm_load_addr (FLASH_DATA_START) */
PROVIDE( _sdata = _itcm_load_addr );
/* End of flash load area: end of SDRAM load region */
PROVIDE( _edata = _sdram_load_addr + _sdram_load_size );
/* Flash readonly/text area: use FLASH_HEADER_START as the base for readonly data */
PROVIDE( _stext = FLASH_HEADER_START );
/* End of readonly/text area: same end as the overall flash load region */
PROVIDE( _etext = _sdram_load_addr + _sdram_load_size );
PROVIDE( _eronly = _etext );
/* End of zero-initialized RAM (BSS end) */
PROVIDE( _sbss = __bss_start__ );
PROVIDE( _ebss = __bss_end__ );

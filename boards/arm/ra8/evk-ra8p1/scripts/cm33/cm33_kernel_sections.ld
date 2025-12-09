/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/scripts/cm85/cm85_kernel_sections.ld
 *
 * NuttX Kernel sections for Cortex-M85
 * Contains vectors, code, rodata sections for kernel in FLASH
 *
 ****************************************************************************/

SECTIONS
{
    /* Wrapper section for all readonly code - Required by Renesas FSP */
    __flash_readonly$$ :
    {
        __flash_readonly$$Base = .;

        /* Interrupt vectors - must be first */
        _svectors = ABSOLUTE(.);
        *(.vectors)
        _evectors = ABSOLUTE(.);

        /* Code sections */
        _stext = ABSOLUTE(.);
        *(.text)
        *(.text.*)
        *(.fixup)
        *(.gnu.warning)
        *(.glue_7)
        *(.glue_7t)
        *(.got)
        *(.gcc_except_table)
        *(.gnu.linkonce.t.*)
        _etext = ABSOLUTE(.);

        /* C++ support */
        _sinit = ABSOLUTE(.);
        KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
        KEEP(*(.init_array .ctors))
        _einit = ABSOLUTE(.);

        /* ARM unwinding support */
        *(.ARM.extab*)

        __exidx_start = ABSOLUTE(.);
        *(.ARM.exidx*)
        __exidx_end = ABSOLUTE(.);

        /* Read-only data */
        _srodata = ABSOLUTE(.);
        *(.rodata)
        *(.rodata.*)
        *(.gnu.linkonce.r.*)
        _erodata = ABSOLUTE(.);

        /* System call stubs */
        _stdata = ABSOLUTE(.);
        *(.tdata .tdata.* .gnu.linkonce.td.*)
        _etdata = ABSOLUTE(.);

        _stbss = ABSOLUTE(.);
        *(.tbss .tbss.* .gnu.linkonce.tb.* .tcommon)
        _etbss = ABSOLUTE(.);

        __flash_readonly$$Limit = .;
    }> FLASH

    /* End-of-flash marker */
    _eronly = ABSOLUTE(.);
}

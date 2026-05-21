/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/scripts/common/renesas_zero_sections.ld
 *
 * Renesas FSP zero initialization sections
 * Required by ra_start.c for BSS initialization
 *
 * CRITICAL: These sections define memory regions that are zeroed during
 * startup. Each section has two symbols:
 *   $$Base  - Start address
 *   $$Limit - End address
 ****************************************************************************/

SECTIONS
{
    /* OSPI0_CS0 BSS sections */
    __ospi0_cs0_zero$$ (NOLOAD) :
    {
        __ospi0_cs0_zero$$Base = .;
        *(.ospi0_cs0_zero)
        *(.ospi0_cs0_bss)
        __ospi0_cs0_zero$$Limit = .;
    }> OSPI0_CS0

    /* OSPI1_CS0 BSS sections */
    __ospi1_cs0_zero$$ (NOLOAD) :
    {
        __ospi1_cs0_zero$$Base = .;
        *(.ospi1_cs0_zero)
        *(.ospi1_cs0_bss)
        __ospi1_cs0_zero$$Limit = .;
    }> OSPI1_CS0

    /* ITCM BSS sections */
    __itcm_zero$$ (NOLOAD) :
    {
        __itcm_zero$$Base = .;
        *(.itcm_zero)
        *(.itcm_bss)
        __itcm_zero$$Limit = .;
    }> ITCM

    /* DTCM BSS sections */
    __dtcm_zero$$ (NOLOAD) :
    {
        __dtcm_zero$$Base = .;
        *(.dtcm_zero)
        *(.dtcm_bss)
        __dtcm_zero$$Limit = .;
    }> DTCM

    /* CRITICAL: Primary .bss section in RAM */
    __ram_zero$$ (NOLOAD) :
    {
        __ram_zero$$Base = .;
        *(.bss)
        *(.bss.*)
        *(.gnu.linkonce.b.*)
        *(COMMON)
        __ram_zero$$Limit = .;
    }> RAM

    /* Thread-local storage BSS */
    __ram_tbss$$ (NOLOAD) :
    {
        __ram_tbss$$Base = .;
        *(.tbss)
        *(.tbss.*)
        *(.gnu.linkonce.tb.*)
        __ram_tbss$$Limit = .;
    }> RAM

    /* SDRAM BSS sections */
    __sdram_zero$$ (NOLOAD) :
    {
        __sdram_zero$$Base = .;
        *(.sdram_zero)
        *(.sdram_bss)
        __sdram_zero$$Limit = .;
    }> SDRAM

    /* Thread stack - for Renesas FSP thread initialization */
    __ram_thread_stack$$ (NOLOAD) :
    {
        __ram_thread_stack$$Base = .;
        *(.ram_thread_stack)
        . = ALIGN(8);
        __ram_thread_stack$$Limit = .;
    }> RAM

    /* Heap section */
    __ram_heap$$ (NOLOAD) :
    {
        __ram_heap$$Base = .;
        *(.ram_heap)
        __ram_heap$$Limit = .;
    }> RAM

    /* Non-cacheable OSPI0_CS0 BSS sections */
    __ospi0_cs0_zero_nocache$$ (NOLOAD) :
    {
        __ospi0_cs0_zero_nocache$$Base = .;
        *(.ospi0_cs0_zero_nocache)
        *(.ospi0_cs0_bss_nocache)
        __ospi0_cs0_zero_nocache$$Limit = .;
    }> OSPI0_CS0

    /* Non-cacheable RAM BSS sections */
    __ram_zero_nocache$$ (NOLOAD) :
    {
        __ram_zero_nocache$$Base = .;
        *(.bss_nocache)
        *(.ram_zero_nocache)
        *(.ram_bss_nocache)
        __ram_zero_nocache$$Limit = .;
    }> RAM
}

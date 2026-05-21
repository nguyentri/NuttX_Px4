/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/scripts/common/renesas_copy_sections.ld
 *
 * Renesas FSP copy initialization sections
 * Required by ra_start.c for multi-stage memory initialization
 *
 * CRITICAL: These sections define memory regions that are copied from one
 * location to another during startup. Each section has three symbols:
 *   $$Base  - Start address in destination memory
 *   $$Limit - End address in destination memory
 *   $$Load  - Source address in load memory (via LOADADDR())
 ****************************************************************************/

SECTIONS
{
    /* OSPI0_CS0 initialized from different sources */
    __ospi0_cs0_from_ospi0_cs1$$ :
    {
        __ospi0_cs0_from_ospi0_cs1$$Base = .;
        __ospi0_cs0_from_ospi0_cs1$$Load = LOADADDR(__ospi0_cs0_from_ospi0_cs1$$);
        *(.ospi0_cs0_from_ospi0_cs1)
        *(.ospi0_cs0_code_from_ospi0_cs1)
        __ospi0_cs0_from_ospi0_cs1$$Limit = .;
    }> OSPI0_CS0 AT > OSPI0_CS1

    __ospi0_cs0_from_ospi1_cs1$$ :
    {
        __ospi0_cs0_from_ospi1_cs1$$Base = .;
        __ospi0_cs0_from_ospi1_cs1$$Load = LOADADDR(__ospi0_cs0_from_ospi1_cs1$$);
        *(.ospi0_cs0_from_ospi1_cs1)
        *(.ospi0_cs0_code_from_ospi1_cs1)
        __ospi0_cs0_from_ospi1_cs1$$Limit = .;
    }> OSPI0_CS0 AT > OSPI1_CS1

    __ospi0_cs0_from_data_flash$$ :
    {
        __ospi0_cs0_from_data_flash$$Base = .;
        __ospi0_cs0_from_data_flash$$Load = LOADADDR(__ospi0_cs0_from_data_flash$$);
        *(.ospi0_cs0_from_data_flash)
        *(.ospi0_cs0_code_from_data_flash)
        __ospi0_cs0_from_data_flash$$Limit = .;
    }> OSPI0_CS0 AT > DATA_FLASH

    __ospi0_cs0_from_flash$$ :
    {
        __ospi0_cs0_from_flash$$Base = .;
        __ospi0_cs0_from_flash$$Load = LOADADDR(__ospi0_cs0_from_flash$$);
        *(.ospi0_cs0_from_flash)
        *(.ospi0_cs0_code_from_flash)
        __ospi0_cs0_from_flash$$Limit = .;
    }> OSPI0_CS0 AT > FLASH

    /* OSPI1_CS0 initialized from different sources */
    __ospi1_cs0_from_ospi0_cs1$$ :
    {
        __ospi1_cs0_from_ospi0_cs1$$Base = .;
        __ospi1_cs0_from_ospi0_cs1$$Load = LOADADDR(__ospi1_cs0_from_ospi0_cs1$$);
        *(.ospi1_cs0_from_ospi0_cs1)
        *(.ospi1_cs0_code_from_ospi0_cs1)
        __ospi1_cs0_from_ospi0_cs1$$Limit = .;
    }> OSPI1_CS0 AT > OSPI0_CS1

    __ospi1_cs0_from_ospi1_cs1$$ :
    {
        __ospi1_cs0_from_ospi1_cs1$$Base = .;
        __ospi1_cs0_from_ospi1_cs1$$Load = LOADADDR(__ospi1_cs0_from_ospi1_cs1$$);
        *(.ospi1_cs0_from_ospi1_cs1)
        *(.ospi1_cs0_code_from_ospi1_cs1)
        __ospi1_cs0_from_ospi1_cs1$$Limit = .;
    }> OSPI1_CS0 AT > OSPI1_CS1

    __ospi1_cs0_from_data_flash$$ :
    {
        __ospi1_cs0_from_data_flash$$Base = .;
        __ospi1_cs0_from_data_flash$$Load = LOADADDR(__ospi1_cs0_from_data_flash$$);
        *(.ospi1_cs0_from_data_flash)
        *(.ospi1_cs0_code_from_data_flash)
        __ospi1_cs0_from_data_flash$$Limit = .;
    }> OSPI1_CS0 AT > DATA_FLASH

    __ospi1_cs0_from_flash$$ :
    {
        __ospi1_cs0_from_flash$$Base = .;
        __ospi1_cs0_from_flash$$Load = LOADADDR(__ospi1_cs0_from_flash$$);
        *(.ospi1_cs0_from_flash)
        *(.ospi1_cs0_code_from_flash)
        __ospi1_cs0_from_flash$$Limit = .;
    }> OSPI1_CS0 AT > FLASH

    /* ITCM initialized from different sources */
    __itcm_from_ospi0_cs1$$ :
    {
        __itcm_from_ospi0_cs1$$Base = .;
        __itcm_from_ospi0_cs1$$Load = LOADADDR(__itcm_from_ospi0_cs1$$);
        *(.itcm_from_ospi0_cs1)
        *(.itcm_code_from_ospi0_cs1)
        __itcm_from_ospi0_cs1$$Limit = .;
    }> ITCM AT > OSPI0_CS1

    __itcm_from_ospi1_cs1$$ :
    {
        __itcm_from_ospi1_cs1$$Base = .;
        __itcm_from_ospi1_cs1$$Load = LOADADDR(__itcm_from_ospi1_cs1$$);
        *(.itcm_from_ospi1_cs1)
        *(.itcm_code_from_ospi1_cs1)
        __itcm_from_ospi1_cs1$$Limit = .;
    }> ITCM AT > OSPI1_CS1

    __itcm_from_data_flash$$ :
    {
        __itcm_from_data_flash$$Base = .;
        __itcm_from_data_flash$$Load = LOADADDR(__itcm_from_data_flash$$);
        *(.itcm_from_data_flash)
        *(.itcm_code_from_data_flash)
        __itcm_from_data_flash$$Limit = .;
    }> ITCM AT > DATA_FLASH

    __itcm_from_flash$$ :
    {
        __itcm_from_flash$$Base = .;
        __itcm_from_flash$$Load = LOADADDR(__itcm_from_flash$$);
        *(.itcm_from_flash)
        *(.itcm_code_from_flash)
        __itcm_from_flash$$Limit = .;
    }> ITCM AT > FLASH

    /* DTCM initialized from different sources */
    __dtcm_from_ospi0_cs1$$ :
    {
        __dtcm_from_ospi0_cs1$$Base = .;
        __dtcm_from_ospi0_cs1$$Load = LOADADDR(__dtcm_from_ospi0_cs1$$);
        *(.dtcm_from_ospi0_cs1)
        *(.dtcm_code_from_ospi0_cs1)
        __dtcm_from_ospi0_cs1$$Limit = .;
    }> DTCM AT > OSPI0_CS1

    __dtcm_from_ospi1_cs1$$ :
    {
        __dtcm_from_ospi1_cs1$$Base = .;
        __dtcm_from_ospi1_cs1$$Load = LOADADDR(__dtcm_from_ospi1_cs1$$);
        *(.dtcm_from_ospi1_cs1)
        *(.dtcm_code_from_ospi1_cs1)
        __dtcm_from_ospi1_cs1$$Limit = .;
    }> DTCM AT > OSPI1_CS1

    __dtcm_from_data_flash$$ :
    {
        __dtcm_from_data_flash$$Base = .;
        __dtcm_from_data_flash$$Load = LOADADDR(__dtcm_from_data_flash$$);
        *(.dtcm_from_data_flash)
        *(.dtcm_code_from_data_flash)
        __dtcm_from_data_flash$$Limit = .;
    }> DTCM AT > DATA_FLASH

    __dtcm_from_flash$$ :
    {
        __dtcm_from_flash$$Base = .;
        __dtcm_from_flash$$Load = LOADADDR(__dtcm_from_flash$$);
        *(.dtcm_from_flash)
        *(.dtcm_code_from_flash)
        __dtcm_from_flash$$Limit = .;
    }> DTCM AT > FLASH

    /* RAM initialized from different sources */
    __ram_from_ospi0_cs1$$ :
    {
        __ram_from_ospi0_cs1$$Base = .;
        __ram_from_ospi0_cs1$$Load = LOADADDR(__ram_from_ospi0_cs1$$);
        *(.ram_from_ospi0_cs1)
        *(.ram_code_from_ospi0_cs1)
        __ram_from_ospi0_cs1$$Limit = .;
    }> RAM AT > OSPI0_CS1

    __ram_from_data_flash$$ :
    {
        __ram_from_data_flash$$Base = .;
        __ram_from_data_flash$$Load = LOADADDR(__ram_from_data_flash$$);
        *(.ram_from_data_flash)
        *(.ram_code_from_data_flash)
        __ram_from_data_flash$$Limit = .;
    }> RAM AT > DATA_FLASH

    /* CRITICAL: Primary .data section - initialized from FLASH */
    __ram_from_flash$$ :
    {
        __ram_from_flash$$Base = .;
        __ram_from_flash$$Load = LOADADDR(__ram_from_flash$$);
        *(.data)
        *(.data.*)
        *(.gnu.linkonce.d.*)
        CONSTRUCTORS
        *(vtable)
        __ram_from_flash$$Limit = .;
    }> RAM AT > FLASH

    /* Thread-local storage data */
    __ram_tdata$$ :
    {
        __ram_tdata$$Base = .;
        __ram_tdata$$Load = LOADADDR(__ram_tdata$$);
        *(.tdata)
        *(.tdata.*)
        *(.gnu.linkonce.td.*)
        __ram_tdata$$Limit = .;
    }> RAM AT > FLASH

    /* SDRAM initialized from OSPI1_CS1 */
    __sdram_from_ospi1_cs1$$ :
    {
        __sdram_from_ospi1_cs1$$Base = .;
        __sdram_from_ospi1_cs1$$Load = LOADADDR(__sdram_from_ospi1_cs1$$);
        *(.sdram_from_ospi1_cs1)
        *(.sdram_code_from_ospi1_cs1)
        __sdram_from_ospi1_cs1$$Limit = .;
    }> SDRAM AT > OSPI1_CS1
}

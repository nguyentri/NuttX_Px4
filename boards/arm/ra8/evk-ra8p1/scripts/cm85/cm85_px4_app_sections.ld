/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/scripts/cm85/cm85_px4_app_sections.ld
 *
 * PX4 Application sections in OSPI Flash (Execute-In-Place)
 * Large modules placed in external flash to save internal MRAM
 *
 ****************************************************************************/

SECTIONS
{
    /* PX4 application code in OSPI Flash (XIP enabled) */
    __flash_app$$ :
    {
        __flash_app$$Base = .;
        __px4_app_start = .;

        /* PX4 modules - Controllers, estimators, navigators */
        *libmodules__*commander*.a:(.text .text.* .rodata .rodata.*)
        *libmodules__*navigator*.a:(.text .text.* .rodata .rodata.*)
        *libmodules__*local_position_estimator*.a:(.text .text.* .rodata .rodata.*)
        *libmodules__*ekf2*.a:(.text .text.* .rodata .rodata.*)
        *libmodules__*mc_*.a:(.text .text.* .rodata .rodata.*)
        *libmodules__*fw_*.a:(.text .text.* .rodata .rodata.*)
        *libmodules__*vtol_*.a:(.text .text.* .rodata .rodata.*)
        *libmodules__*land_detector*.a:(.text .text.* .rodata .rodata.*)
        *libmodules__*mavlink*.a:(.text .text.* .rodata .rodata.*)

        /* PX4 drivers - Sensors, actuators */
        *libdrivers__*imu*.a:(.text .text.* .rodata .rodata.*)
        *libdrivers__*gps*.a:(.text .text.* .rodata .rodata.*)
        *libdrivers__*magnetometer*.a:(.text .text.* .rodata .rodata.*)
        *libdrivers__*barometer*.a:(.text .text.* .rodata .rodata.*)
        *libdrivers__*px4io*.a:(.text .text.* .rodata .rodata.*)
        *libdrivers__*pwm_out*.a:(.text .text.* .rodata .rodata.*)

        /* PX4 libraries */
        *liblib__*matrix*.a:(.text .text.* .rodata .rodata.*)
        *liblib__*mathlib*.a:(.text .text.* .rodata .rodata.*)
        *liblib__*conversion*.a:(.text .text.* .rodata .rodata.*)
        *liblib__*geo*.a:(.text .text.* .rodata .rodata.*)
        *liblib__*ecl*.a:(.text .text.* .rodata .rodata.*)

        /* PX4 system commands */
        *libsystemcmds__*.a:(.text .text.* .rodata .rodata.*)

        /* Examples and user code */
        *libexamples__*.a:(.text .text.* .rodata .rodata.*)

        /* Catch-all for any PX4 code not in MRAM */
        *(.px4_app)
        *(.px4_app.*)

        __px4_app_end = .;
        __flash_app$$Limit = .;
    }> FLASH_APP
}

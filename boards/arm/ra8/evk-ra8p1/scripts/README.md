# Modularized Dual-Core Linker Scripts for Renesas RA8P1

## Overview

This directory contains modularized linker scripts for the Renesas RA8P1 dual-core microcontroller running NuttX with PX4 autopilot firmware. The scripts have been refactored from a monolithic 1725-line file into maintainable, reusable components while preserving all Renesas FSP (Flexible Software Package) symbols required by `ra_start.c`.

## Directory Structure

```
scripts/
├── evk-ra8p1.ld                     # Reference monolithic script (backup)
├── common/
│   ├── renesas_option_settings.ld   # Renesas option setting bytes (set by CM85)
│   ├── renesas_copy_sections.ld     # Renesas copy initialization sections
│   └── renesas_zero_sections.ld     # Renesas zero initialization sections
├── cm85/
│   ├── evk-ra8p1_cm85.ld            # Main CM85 linker script
│   ├── cm85_kernel_sections.ld      # NuttX kernel sections (vectors, .text, .rodata)
│   ├── cm85_px4_app_sections.ld     # PX4 application sections in OSPI Flash
│   ├── cm85_ipc_sections.ld         # IPC shared memory sections
└── cm33/
    ├── evk-ra8p1_cm33.ld           # Main CM33 linker script
    ├── cm33_kernel_sections.ld     # NuttX kernel sections for CM33
    └── cm33_ipc_sections.ld        # Hardware option setting bytes
```

## Memory Map

### Cortex-M85 (CPU0) - Primary Core @ 1GHz

| Memory Region | Address Range            | Size    | Purpose                              |
|---------------|--------------------------|---------|--------------------------------------|
| MRAM          | 0x02000000 - 0x0207FFFF  | 512KB   | NuttX kernel code/rodata             |
| SRAM          | 0x22000000 - 0x220CFFFF  | 832KB   | Runtime data/bss/heap/stack          |
| ITCM          | 0x00000000 - 0x0001FFFF  | 128KB   | Fast code execution (ISRs)           |
| DTCM          | 0x20000000 - 0x0001FFFF  | 128KB   | Fast data access (DMA buffers)       |
| OSPI0 Flash   | 0x80000000 - 0x83FFFFFF  | 64MB    | PX4 application code (XIP)           |
| IPC Shared    | 0x220D0000 - 0x220DFFFF  | 64KB    | Inter-processor communication        |
| SDRAM         | 0x68000000 - 0x6FFFFFFF  | 128MB   | External SDRAM                       |

### Cortex-M33 (CPU1) - Secondary Core @ 250MHz

| Memory Region | Address Range            | Size    | Purpose                              |
|---------------|--------------------------|---------|--------------------------------------|
| MRAM          | 0x02080000 - 0x020FFFFF  | 512KB   | NuttX kernel code/rodata             |
| SRAM          | 0x220E0000 - 0x221A0000  | 768KB   | Runtime data/bss/heap/stack          |
| ITCM          | 0x00000000 - 0x0000FFFF  | 64KB    | Fast code execution (ISRs)           |
| DTCM          | 0x20000000 - 0x0000FFFF  | 64KB    | Fast data access (DMA buffers)       |
| OSPI0 Flash   | 0x80000000 - 0x83FFFFFF  | 64MB    | Shared application space with CM85   |
| IPC Shared    | 0x220D0000 - 0x220DFFFF  | 64KB    | Inter-processor communication        |
| SDRAM         | 0x68000000 - 0x6FFFFFFF  | 128MB   | Shared external SDRAM                |

**CRITICAL**: The IPC shared memory region must be configured as **non-cacheable** via MPU on both cores to ensure cache coherency!

## Renesas FSP Symbol Convention

Renesas startup code (`ra_start.c`) requires specific symbol triplets for multi-stage initialization:

### Copy Sections (initialized data)
Each copy section has three symbols:
- `__<region>_from_<source>$$Base` - Destination start address
- `__<region>_from_<source>$$Limit` - Destination end address
- `__<region>_from_<source>$$Load` - Source address in loadable memory

Example:
```ld
__ram_from_flash$$ :
{
    __ram_from_flash$$Base = .;
    __ram_from_flash$$Load = LOADADDR(__ram_from_flash$$);
    *(.data)
    *(.data.*)
    __ram_from_flash$$Limit = .;
}> RAM AT > FLASH
```

### Zero Sections (BSS)
Each zero section has two symbols:
- `__<region>_zero$$Base` - Start address
- `__<region>_zero$$Limit` - End address

Example:
```ld
__ram_zero$$ (NOLOAD) :
{
    __ram_zero$$Base = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    __ram_zero$$Limit = .;
}> RAM
```

### Supported Memory Combinations

The `common/renesas_copy_sections.ld` file provides symbols for all Renesas-supported source/destination combinations:

**Sources**: FLASH, DATA_FLASH, OSPI0_CS1, OSPI1_CS1
**Destinations**: RAM, ITCM, DTCM, OSPI0_CS0, OSPI1_CS0, SDRAM

## Component Files

### 1. `common/renesas_copy_sections.ld`
Contains all Renesas FSP copy initialization sections with proper `$$Base/$$Limit/$$Load` symbols. This file is **shared by both cores** and must not be modified without understanding the Renesas startup sequence.

**Key sections**:
- `__ram_from_flash$$` - Primary .data section (most important!)
- `__itcm_from_flash$$` - ITCM code copied from FLASH
- `__dtcm_from_flash$$` - DTCM data copied from FLASH
- `__ospi0_cs0_from_*$$` - OSPI Flash initialization
- `__sdram_from_*$$` - SDRAM initialization

### 2. `common/renesas_zero_sections.ld`
Contains all Renesas FSP zero initialization (BSS) sections with proper `$$Base/$$Limit` symbols.

**Key sections**:
- `__ram_zero$$` - Primary .bss section (most important!)
- `__ram_tbss$$` - Thread-local storage BSS
- `__ram_thread_stack$$` - Thread stack region
- `__itcm_zero$$` - ITCM BSS
- `__dtcm_zero$$` - DTCM BSS

### 3. `cm85/cm85_kernel_sections.ld`
NuttX kernel sections in MRAM for CM85:
- `.vectors` - Interrupt vector table (must be first!)
- `.text` - Kernel code
- `.rodata` - Read-only data
- `.init_section` - C++ constructors
- `.ARM.extab`/`.ARM.exidx` - ARM unwinding tables

All wrapped in `__flash_readonly$$` section required by Renesas FSP.

### 4. `cm85/cm85_px4_app_sections.ld`
PX4 application code placed in OSPI Flash (Execute-In-Place) to save internal MRAM:
- Flight controllers (commander, navigator, estimators)
- Non-critical drivers (sensors, GPS, magnetometer)
- Libraries (matrix, mathlib, geo, ecl)
- System commands
- User examples

Uses wildcard patterns to match PX4 module archives:
```ld
*libmodules__*ekf2*.a:(.text .text.* .rodata .rodata.*)
*libdrivers__*imu*.a:(.text .text.* .rodata .rodata.*)
```

### 5. `cm85/cm85_ipc_sections.ld` and `cm33/cm33_ipc_sections.ld`
Inter-processor communication sections (identical for both cores):
- `.resource_table` - OpenAMP resource table
- `.vring_tx`/`.vring_rx` - VirtIO ring buffers
- `.shmem_buffers` - Shared memory buffers
- `.hw_semaphores` - Hardware semaphores
- `.mailbox` - Mailbox data structures
- `.ipc_msgq` - Message queues

All sections are `(NOLOAD)` and 64-byte aligned for cache line boundaries.

### 6. `cm85/cm85_option_settings.ld` and `cm33/cm33_option_settings.ld`
Hardware option setting bytes programmed during MCU reset:
- OFS0-3: Option function select registers
- BPS: Block protection settings
- OTP_*: One-time programmable security settings
- SACC*: Security access control

These sections use `KEEP()` to prevent linker garbage collection.

## Build Configuration

### CM85 Build (Primary Core)
```bash
cd /path/to/PX4-Autopilot
make renesas_evk-ra8p1:ipc-cm85
```

Configuration:
- `CONFIG_ARCH_CORTEX_M85=y`
- `CONFIG_RA_CPU_CORE=0`
- Linker script: `boards/arm/ra8/evk-ra8p1/scripts/cm85/evk-ra8p1_cm85.ld`

### CM33 Build (Secondary Core)
```bash
cd /path/to/PX4-Autopilot
make renesas_evk-ra8p1:ipc-cm33
```

Configuration:
- `CONFIG_ARCH_CORTEX_M33=y`
- `CONFIG_RA_CPU_CORE=1`
- Linker script: `boards/arm/ra8/evk-ra8p1/scripts/cm33/evk-ra8p1_cm33.ld`

## Verification Commands

### Check Renesas FSP Symbols
```bash
# Verify copy section symbols exist
arm-none-eabi-nm nuttx | grep '$$Base'
arm-none-eabi-nm nuttx | grep '$$Limit'
arm-none-eabi-nm nuttx | grep '$$Load'

# Critical symbols that MUST exist:
# __ram_from_flash$$Base
# __ram_from_flash$$Limit
# __ram_from_flash$$Load
# __ram_zero$$Base
# __ram_zero$$Limit
# __flash_readonly$$Base
# __flash_readonly$$Limit
```

### Check Memory Sections
```bash
# Section sizes
arm-none-eabi-size nuttx

# Section headers
arm-none-eabi-objdump -h nuttx

# Detailed section info
arm-none-eabi-readelf -S nuttx
```

### Check PX4 Module Placement
```bash
# Verify PX4 modules in OSPI Flash (0x80000000 - 0x83FFFFFF)
arm-none-eabi-nm nuttx | grep -E "__px4_app|__flash_app"
arm-none-eabi-objdump -h nuttx | grep -A 5 "FLASH_APP"

# Check specific module placement
arm-none-eabi-nm nuttx | grep "ekf2"
arm-none-eabi-nm nuttx | grep "commander"
```

### Check IPC Shared Memory
```bash
# Verify IPC region (0x220D0000 - 0x220DFFFF)
arm-none-eabi-nm nuttx | grep "__ipc"
arm-none-eabi-nm nuttx | grep "resource_table"
arm-none-eabi-nm nuttx | grep "vring"
```

### Memory Map Analysis
```bash
# Full memory map
arm-none-eabi-readelf -l nuttx

# Symbol addresses sorted by address
arm-none-eabi-nm -n nuttx | head -100
```

## Troubleshooting

### Error: `undefined reference to '__ram_from_flash$$Base'`
**Cause**: Missing Renesas copy section symbols.
**Solution**: Ensure `common/renesas_copy_sections.ld` is included in main linker script.

### Error: `undefined reference to '__flash_readonly$$Base'`
**Cause**: Kernel sections not wrapped properly.
**Solution**: Check that `cm85_kernel_sections.ld` has the `__flash_readonly$$` wrapper section.

### Warning: `section ... will not fit in region 'FLASH'`
**Cause**: NuttX kernel code too large for 512KB MRAM.
**Solution**: Move non-critical drivers to PX4 app section in OSPI Flash.

### Warning: `section ... will not fit in region 'RAM'`
**Cause**: CM85 or CM33 RAM allocation too large.
**Solution**: Check that CM85 uses 832KB (0xD0000) and CM33 uses 768KB (0xC0000), leaving 64KB for IPC.

### Error: IPC communication failures at runtime
**Cause**: IPC shared memory not configured as non-cacheable.
**Solution**: Configure MPU to mark 0x220D0000-0x220DFFFF as non-cacheable on both cores:
```c
// In board initialization (src/drivers/boards/ra8/evk-ra8p1/init.c)
mpu_configure_region(IPC_REGION, 0x220D0000, 0x10000,
                     MPU_ATTR_NON_CACHEABLE | MPU_ATTR_SHAREABLE);
```

### Build fails with "cannot open linker script file"
**Cause**: Incorrect INCLUDE path in main linker script.
**Solution**: Use relative paths from the main script directory:
```ld
INCLUDE ../common/renesas_copy_sections.ld  # Correct
INCLUDE renesas_copy_sections.ld            # Wrong - file not found
```

## Maintenance Guidelines

### Adding New Memory Sections

1. **If using standard NuttX sections** (.text, .data, .bss):
   - Add to existing kernel section files
   - No Renesas symbols needed

2. **If creating custom initialized sections**:
   - Add to `common/renesas_copy_sections.ld`
   - Must provide `$$Base`, `$$Limit`, and `$$Load` symbols
   - Use `AT > SOURCE_MEMORY` to specify load address

3. **If creating custom BSS sections**:
   - Add to `common/renesas_zero_sections.ld`
   - Must provide `$$Base` and `$$Limit` symbols
   - Use `(NOLOAD)` attribute

### Modifying Memory Layout

1. Update memory region variables in main linker script:
   ```ld
   FLASH_START = 0x02000000;
   FLASH_LENGTH = 0x00080000;  /* Modify size here */
   ```

2. Update `MEMORY` block accordingly

3. Ensure CM85 + CM33 + IPC regions don't overlap:
   - CM85 RAM: 0x22000000 - 0x220CFFFF (832KB)
   - IPC:      0x220D0000 - 0x220DFFFF (64KB)
   - CM33 RAM: 0x220E0000 - 0x2219FFFF (768KB)

### Testing Changes

1. Build both cores:
   ```bash
   make renesas_evk-ra8p1:ipc-cm85 && make renesas_evk-ra8p1:ipc-cm33
   ```

2. Check for undefined symbols:
   ```bash
   arm-none-eabi-nm nuttx | grep " U "
   ```

3. Verify memory regions:
   ```bash
   arm-none-eabi-objdump -h nuttx | grep -E "FLASH|RAM|ITCM|DTCM"
   ```

4. Test IPC communication on hardware

## Performance Considerations

### Code Placement Strategy

**Place in MRAM (Fast, 0 wait states)**:
- Interrupt handlers (critical timing)
- NuttX kernel (scheduler, memory manager)
- Critical drivers (UART, timer, interrupt controller)
- Startup and boot code

**Place in OSPI Flash (Slower, ~3-5 wait states with cache)**:
- PX4 application modules (large code size)
- Non-critical drivers (sensors, GPS)
- User applications and examples
- Libraries (unless performance-critical)

**Place in ITCM (Ultra-fast, 0 wait states)**:
- High-frequency ISRs (>10kHz)
- DSP/Math hotspots (FFT, matrix operations)
- Real-time control loops

**Place in DTCM (Ultra-fast, 0 wait states)**:
- DMA descriptors and buffers
- Sensor data buffers
- Time-critical data structures

### Cache Optimization

- **Instruction cache**: Enabled for OSPI Flash (improves XIP performance)
- **Data cache**: Enabled for SDRAM and normal SRAM
- **IPC region**: Must be non-cacheable (hardware coherency not available)

## References

- [Renesas RA8P1 User Manual](https://www.renesas.com/us/en/document/man/ra8p1-group-users-manual-hardware)
- [Renesas FSP Documentation](https://github.com/renesas/fsp)
- [NuttX Linker Script Guide](https://nuttx.apache.org/docs/latest/implementation/linker_script.html)
- [ARM Cortex-M85 Technical Reference](https://developer.arm.com/documentation/101928)
- [OpenAMP Dual-Core Communication](https://github.com/OpenAMP/open-amp)

## Version History

- **v2.0** (2025-01-XX): Modularized from monolithic 1725-line script
  - Separated Renesas FSP sections into reusable components
  - Created core-specific section files (CM85/CM33)
  - Added PX4 OSPI Flash placement for large applications
  - Documented IPC non-cacheable requirement
  - Fixed CM85 RAM overlap (1344KB → 832KB)

- **v1.0** (Original): Monolithic `evk-ra8p1.ld` single file
  - All sections in one 1725-line file
  - Conditional compilation for CM85/CM33
  - Difficult to maintain and understand

---

**Author**: GitHub Copilot
**Date**: January 2025
**License**: Apache License 2.0 (Same as NuttX)

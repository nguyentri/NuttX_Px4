#!/usr/bin/env python3
"""
Memory Placement Configuration Tool for Renesas RA8P1 Dual-Core

This tool provides an interactive interface to configure memory allocations
for CM85 and CM33 cores with automatic validation and calculation.

Features:
- Load/save memory configuration from YAML
- Interactive menu for editing regions
- Automatic length calculation
- Automatic next address calculation
- Overlap detection and validation
- Size constraint checking
- Generate linker script files
"""

import yaml
import sys
import os
from typing import Dict, List, Tuple, Optional
from dataclasses import dataclass, field
from pathlib import Path


@dataclass
class MemoryRegion:
    """Represents a memory region with start address and size"""
    name: str
    start: int
    length: int
    description: str = ""
    permissions: str = "rwx"

    @property
    def end(self) -> int:
        """Calculate end address (exclusive)"""
        return self.start + self.length

    @property
    def start_hex(self) -> str:
        """Return start address as hex string"""
        return f"0x{self:08X}"

    @property
    def end_hex(self) -> str:
        """Return end address as hex string"""
        return f"0x{self.end:08X}"

    @property
    def length_hex(self) -> str:
        """Return length as hex string"""
        return f"0x{self.length:08X}"

    @property
    def length_kb(self) -> int:
        """Return length in KB"""
        return self.length // 1024

    def overlaps_with(self, other: 'MemoryRegion') -> bool:
        """Check if this region overlaps with another"""
        return not (self.end <= other.start or self.start >= other.end)


@dataclass
class CoreMemory:
    """Memory configuration for a single core"""
    name: str
    flash: MemoryRegion
    ram: MemoryRegion
    itcm: MemoryRegion
    dtcm: MemoryRegion

    def get_all_regions(self) -> List[MemoryRegion]:
        """Get all memory regions for this core"""
        return [self.flash, self.ram, self.itcm, self.dtcm]


@dataclass
class SharedMemory:
    """Shared memory regions accessible by both cores"""
    ipc: MemoryRegion
    sdram: MemoryRegion
    ospi_flash: MemoryRegion

    def get_all_regions(self) -> List[MemoryRegion]:
        """Get all shared memory regions"""
        return [self.ipc, self.sdram, self.ospi_flash]


class MemoryConfiguration:
    """Complete memory configuration for dual-core system"""

    def __init__(self):
        # Default RA8P1 memory layout
        self.cm85 = CoreMemory(
            name="CM85",
            flash=MemoryRegion("FLASH_CM85", 0x02000000, 0x00080000, "512KB MRAM for CM85", "rx"),
            ram=MemoryRegion("RAM_CM85", 0x22000000, 0x000D0000, "832KB SRAM for CM85", "rwx"),
            itcm=MemoryRegion("ITCM_CM85", 0x00000000, 0x00020000, "128KB ITCM for CM85", "rwx"),
            dtcm=MemoryRegion("DTCM_CM85", 0x20000000, 0x00020000, "128KB DTCM for CM85", "rwx")
        )

        self.cm33 = CoreMemory(
            name="CM33",
            flash=MemoryRegion("FLASH_CM33", 0x02080000, 0x00080000, "512KB MRAM for CM33", "rx"),
            ram=MemoryRegion("RAM_CM33", 0x220E0000, 0x000C0000, "768KB SRAM for CM33", "rwx"),
            itcm=MemoryRegion("ITCM_CM33", 0x00000000, 0x00010000, "64KB ITCM for CM33", "rwx"),
            dtcm=MemoryRegion("DTCM_CM33", 0x20000000, 0x00010000, "64KB DTCM for CM33", "rwx")
        )

        self.shared = SharedMemory(
            ipc=MemoryRegion("IPC_SHMEM", 0x220D0000, 0x00010000, "64KB IPC shared memory", "rw"),
            sdram=MemoryRegion("SDRAM", 0x68000000, 0x08000000, "128MB external SDRAM", "rwx"),
            ospi_flash=MemoryRegion("OSPI0_CS0", 0x80000000, 0x04000000, "64MB OSPI Flash", "rx")
        )

        # Hardware constraints
        self.constraints = {
            "total_mram": 0x00100000,  # 1MB total
            "total_sram": 0x001A0000,  # 1664KB total (excluding IPC)
            "ipc_fixed_size": 0x00010000,  # 64KB fixed
            "ipc_fixed_start": 0x220D0000,  # Fixed location
        }

    def load_from_yaml(self, yaml_file: str) -> bool:
        """Load configuration from YAML file"""
        try:
            with open(yaml_file, 'r') as f:
                data = yaml.safe_load(f)

            if not data:
                return False

            # Load CM85
            if 'cm85' in data:
                self._load_core_memory(data['cm85'], self.cm85)

            # Load CM33
            if 'cm33' in data:
                self._load_core_memory(data['cm33'], self.cm33)

            # Load shared
            if 'shared' in data:
                self._load_shared_memory(data['shared'])

            return True
        except Exception as e:
            print(f"Error loading YAML: {e}")
            return False

    def _load_core_memory(self, data: dict, core: CoreMemory):
        """Load core memory from YAML data"""
        if 'flash' in data:
            self._update_region_from_dict(data['flash'], core.flash)
        if 'ram' in data:
            self._update_region_from_dict(data['ram'], core.ram)
        if 'itcm' in data:
            self._update_region_from_dict(data['itcm'], core.itcm)
        if 'dtcm' in data:
            self._update_region_from_dict(data['dtcm'], core.dtcm)

    def _load_shared_memory(self, data: dict):
        """Load shared memory from YAML data"""
        if 'ipc' in data:
            self._update_region_from_dict(data['ipc'], self.shared.ipc)
        if 'sdram' in data:
            self._update_region_from_dict(data['sdram'], self.shared.sdram)
        if 'ospi_flash' in data:
            self._update_region_from_dict(data['ospi_flash'], self.shared.ospi_flash)

    def _update_region_from_dict(self, data: dict, region: MemoryRegion):
        """Update a memory region from dictionary"""
        if 'start' in data:
            region.start = int(data['start'], 16) if isinstance(data['start'], str) else data['start']
        if 'length' in data:
            region.length = int(data['length'], 16) if isinstance(data['length'], str) else data['length']
        if 'description' in data:
            region.description = data['description']
        if 'permissions' in data:
            region.permissions = data['permissions']

    def save_to_yaml(self, yaml_file: str) -> bool:
        """Save configuration to YAML file"""
        try:
            data = {
                'cm85': self._core_to_dict(self.cm85),
                'cm33': self._core_to_dict(self.cm33),
                'shared': self._shared_to_dict()
            }

            with open(yaml_file, 'w') as f:
                yaml.dump(data, f, default_flow_style=False, sort_keys=False)

            return True
        except Exception as e:
            print(f"Error saving YAML: {e}")
            return False

    def _core_to_dict(self, core: CoreMemory) -> dict:
        """Convert core memory to dictionary"""
        return {
            'flash': self._region_to_dict(core.flash),
            'ram': self._region_to_dict(core.ram),
            'itcm': self._region_to_dict(core.itcm),
            'dtcm': self._region_to_dict(core.dtcm)
        }

    def _shared_to_dict(self) -> dict:
        """Convert shared memory to dictionary"""
        return {
            'ipc': self._region_to_dict(self.shared.ipc),
            'sdram': self._region_to_dict(self.shared.sdram),
            'ospi_flash': self._region_to_dict(self.shared.ospi_flash)
        }

    def _region_to_dict(self, region: MemoryRegion) -> dict:
        """Convert memory region to dictionary"""
        return {
            'start': f"0x{region.start:08X}",
            'length': f"0x{region.length:08X}",
            'description': region.description,
            'permissions': region.permissions
        }

    def validate(self) -> Tuple[bool, List[str]]:
        """Validate the memory configuration"""
        errors = []

        # Check MRAM constraint
        total_mram = self.cm85.flash.length + self.cm33.flash.length
        if total_mram > self.constraints['total_mram']:
            errors.append(f"Total MRAM ({total_mram//1024}KB) exceeds limit ({self.constraints['total_mram']//1024}KB)")

        # Check SRAM constraint (excluding IPC)
        total_sram = self.cm85.ram.length + self.cm33.ram.length
        if total_sram > self.constraints['total_sram']:
            errors.append(f"Total SRAM ({total_sram//1024}KB) exceeds limit ({self.constraints['total_sram']//1024}KB)")

        # Check IPC is fixed
        if self.shared.ipc.start != self.constraints['ipc_fixed_start']:
            errors.append(f"IPC must start at {self.constraints['ipc_fixed_start']:08X}")
        if self.shared.ipc.length != self.constraints['ipc_fixed_size']:
            errors.append(f"IPC must be {self.constraints['ipc_fixed_size']//1024}KB")

        # Check for overlaps in MRAM
        if self.cm85.flash.overlaps_with(self.cm33.flash):
            errors.append(f"MRAM overlap: CM85 {self.cm85.flash.start_hex}-{self.cm85.flash.end_hex} and CM33 {self.cm33.flash.start_hex}-{self.cm33.flash.end_hex}")

        # Check for overlaps in SRAM
        if self.cm85.ram.overlaps_with(self.cm33.ram):
            errors.append(f"SRAM overlap: CM85 {self.cm85.ram.start_hex}-{self.cm85.ram.end_hex} and CM33 {self.cm33.ram.start_hex}-{self.cm33.ram.end_hex}")

        if self.cm85.ram.overlaps_with(self.shared.ipc):
            errors.append(f"SRAM overlap: CM85 RAM and IPC")

        if self.cm33.ram.overlaps_with(self.shared.ipc):
            errors.append(f"SRAM overlap: CM33 RAM and IPC")

        # Check alignment (must be on reasonable boundaries)
        for core in [self.cm85, self.cm33]:
            for region in core.get_all_regions():
                if region.start % 4 != 0:
                    errors.append(f"{region.name}: start address not 4-byte aligned")
                if region.length % 4 != 0:
                    errors.append(f"{region.name}: length not 4-byte aligned")

        return len(errors) == 0, errors


class PlacementTool:
    """Interactive tool for memory placement configuration"""

    def __init__(self, config_file: str = "memory.yaml"):
        self.config_file = config_file
        self.config = MemoryConfiguration()

        # Try to load existing config
        if os.path.exists(config_file):
            if self.config.load_from_yaml(config_file):
                print(f"✓ Loaded configuration from {config_file}")
            else:
                print(f"⚠ Could not load {config_file}, using defaults")
        else:
            print(f"ℹ No existing configuration found, using defaults")

    def run(self):
        """Run the interactive tool"""
        while True:
            self.clear_screen()
            self.print_header()
            self.print_memory_layout()
            self.print_menu()

            choice = input("\nEnter choice: ").strip()

            if choice == '1':
                self.edit_cm85_memory()
            elif choice == '2':
                self.edit_cm33_memory()
            elif choice == '3':
                self.edit_shared_memory()
            elif choice == '4':
                self.auto_balance_sram()
            elif choice == '5':
                self.validate_and_show_errors()
            elif choice == '6':
                self.save_configuration()
            elif choice == '7':
                self.generate_linker_scripts()
            elif choice == '8':
                self.export_header_file()
            elif choice == 'q' or choice == '0':
                print("\nExiting...")
                break
            else:
                input("Invalid choice. Press Enter to continue...")

    def clear_screen(self):
        """Clear the terminal screen"""
        os.system('clear' if os.name == 'posix' else 'cls')

    def print_header(self):
        """Print tool header"""
        print("=" * 80)
        print("  RA8P1 Dual-Core Memory Placement Configuration Tool")
        print("=" * 80)
        print()

    def print_memory_layout(self):
        """Print current memory layout"""
        print("Current Memory Layout:")
        print("-" * 80)

        # CM85
        print(f"\n📍 CM85 (Cortex-M85 @ 1GHz):")
        self._print_region("  MRAM ", self.config.cm85.flash)
        self._print_region("  SRAM ", self.config.cm85.ram)
        self._print_region("  ITCM ", self.config.cm85.itcm)
        self._print_region("  DTCM ", self.config.cm85.dtcm)

        # CM33
        print(f"\n📍 CM33 (Cortex-M33 @ 250MHz):")
        self._print_region("  MRAM ", self.config.cm33.flash)
        self._print_region("  SRAM ", self.config.cm33.ram)
        self._print_region("  ITCM ", self.config.cm33.itcm)
        self._print_region("  DTCM ", self.config.cm33.dtcm)

        # Shared
        print(f"\n📍 Shared (Both Cores):")
        self._print_region("  IPC  ", self.config.shared.ipc)
        self._print_region("  SDRAM", self.config.shared.sdram)
        self._print_region("  OSPI ", self.config.shared.ospi_flash)

        # Totals
        print(f"\n📊 Totals:")
        total_mram = self.config.cm85.flash.length + self.config.cm33.flash.length
        total_sram = self.config.cm85.ram.length + self.config.cm33.ram.length
        max_mram = self.config.constraints['total_mram']
        max_sram = self.config.constraints['total_sram']

        print(f"  MRAM: {total_mram//1024}KB / {max_mram//1024}KB ({100*total_mram//max_mram}%)")
        print(f"  SRAM: {total_sram//1024}KB / {max_sram//1024}KB ({100*total_sram//max_sram}%) + 64KB IPC")
        print()

    def _print_region(self, label: str, region: MemoryRegion):
        """Print a single memory region"""
        print(f"{label}: {region.start_hex} - {region.end_hex} ({region.length_kb:4d}KB) {region.permissions:3s} - {region.description}")

    def print_menu(self):
        """Print main menu"""
        print("-" * 80)
        print("Actions:")
        print("  1) Edit CM85 memory regions")
        print("  2) Edit CM33 memory regions")
        print("  3) Edit shared memory regions")
        print("  4) Auto-balance SRAM between cores")
        print("  5) Validate configuration")
        print("  6) Save configuration to YAML")
        print("  7) Generate linker script files")
        print("  8) Export C header file")
        print("  0/q) Quit")

    def edit_cm85_memory(self):
        """Edit CM85 memory regions"""
        self._edit_core_memory(self.config.cm85, "CM85")

    def edit_cm33_memory(self):
        """Edit CM33 memory regions"""
        self._edit_core_memory(self.config.cm33, "CM33")

    def _edit_core_memory(self, core: CoreMemory, core_name: str):
        """Edit memory regions for a core"""
        while True:
            self.clear_screen()
            print(f"=== Edit {core_name} Memory ===\n")

            print("Current regions:")
            self._print_region("1. MRAM", core.flash)
            self._print_region("2. SRAM", core.ram)
            self._print_region("3. ITCM", core.itcm)
            self._print_region("4. DTCM", core.dtcm)
            print("\n0) Back to main menu")

            choice = input("\nSelect region to edit: ").strip()

            if choice == '1':
                self._edit_region(core.flash, "MRAM")
            elif choice == '2':
                self._edit_region(core.ram, "SRAM")
            elif choice == '3':
                self._edit_region(core.itcm, "ITCM")
            elif choice == '4':
                self._edit_region(core.dtcm, "DTCM")
            elif choice == '0':
                break

    def _edit_region(self, region: MemoryRegion, region_type: str):
        """Edit a single memory region"""
        print(f"\n--- Edit {region_type} ({region.name}) ---")
        print(f"Current: {region.start_hex} - {region.end_hex} ({region.length_kb}KB)")
        print()
        print("Options:")
        print("  1) Change start address")
        print("  2) Change length (size)")
        print("  3) Change end address (auto-calculate length)")
        print("  4) Move after another region (auto-calculate start)")
        print("  0) Cancel")

        choice = input("\nSelect option: ").strip()

        if choice == '1':
            self._change_start_address(region)
        elif choice == '2':
            self._change_length(region)
        elif choice == '3':
            self._change_end_address(region)
        elif choice == '4':
            print("Feature not implemented yet")
            input("Press Enter to continue...")

    def _change_start_address(self, region: MemoryRegion):
        """Change start address of a region"""
        while True:
            addr_str = input(f"Enter new start address (hex, e.g., 0x02000000) or 'c' to cancel: ").strip()
            if addr_str.lower() == 'c':
                return

            try:
                new_start = int(addr_str, 16)
                if new_start % 4 != 0:
                    print("⚠ Warning: Address should be 4-byte aligned")
                    if input("Continue anyway? (y/n): ").lower() != 'y':
                        continue

                region.start = new_start
                print(f"✓ Start address changed to {region.start_hex}")
                print(f"  New range: {region.start_hex} - {region.end_hex}")
                input("Press Enter to continue...")
                return
            except ValueError:
                print("✗ Invalid hex address")

    def _change_length(self, region: MemoryRegion):
        """Change length of a region"""
        while True:
            print("\nEnter new size:")
            print("  Examples: 512KB, 0x80000, 524288")
            size_str = input("Size (or 'c' to cancel): ").strip()

            if size_str.lower() == 'c':
                return

            try:
                new_length = self._parse_size(size_str)
                if new_length % 4 != 0:
                    print("⚠ Warning: Length should be 4-byte aligned")
                    if input("Continue anyway? (y/n): ").lower() != 'y':
                        continue

                region.length = new_length
                print(f"✓ Length changed to {region.length_kb}KB ({region.length_hex})")
                print(f"  New range: {region.start_hex} - {region.end_hex}")
                input("Press Enter to continue...")
                return
            except ValueError as e:
                print(f"✗ Invalid size: {e}")

    def _change_end_address(self, region: MemoryRegion):
        """Change end address and auto-calculate length"""
        while True:
            addr_str = input(f"Enter new end address (hex, e.g., 0x02080000) or 'c' to cancel: ").strip()
            if addr_str.lower() == 'c':
                return

            try:
                new_end = int(addr_str, 16)
                if new_end <= region.start:
                    print(f"✗ End address must be greater than start ({region.start_hex})")
                    continue

                new_length = new_end - region.start
                if new_length % 4 != 0:
                    print("⚠ Warning: Length should be 4-byte aligned")
                    if input("Continue anyway? (y/n): ").lower() != 'y':
                        continue

                region.length = new_length
                print(f"✓ End address set to {region.end_hex}")
                print(f"  Calculated length: {region.length_kb}KB ({region.length_hex})")
                print(f"  New range: {region.start_hex} - {region.end_hex}")
                input("Press Enter to continue...")
                return
            except ValueError:
                print("✗ Invalid hex address")

    def _parse_size(self, size_str: str) -> int:
        """Parse size string (supports KB, MB suffixes and hex)"""
        size_str = size_str.strip().upper()

        if size_str.startswith('0X'):
            return int(size_str, 16)
        elif size_str.endswith('KB'):
            return int(size_str[:-2]) * 1024
        elif size_str.endswith('MB'):
            return int(size_str[:-2]) * 1024 * 1024
        elif size_str.endswith('K'):
            return int(size_str[:-1]) * 1024
        elif size_str.endswith('M'):
            return int(size_str[:-1]) * 1024 * 1024
        else:
            return int(size_str)

    def edit_shared_memory(self):
        """Edit shared memory regions"""
        print("\n⚠ Shared memory regions have hardware constraints")
        print("  IPC region is fixed at 0x220D0000 (64KB)")
        input("Press Enter to continue...")

    def auto_balance_sram(self):
        """Automatically balance SRAM between CM85 and CM33"""
        print("\n--- Auto-Balance SRAM ---")
        print("This will automatically calculate SRAM allocation based on:")
        print("  - CM85 gets SRAM from 0x22000000")
        print("  - IPC fixed at 0x220D0000 (64KB)")
        print("  - CM33 gets remaining SRAM after IPC")
        print()

        cm85_kb = input("Enter CM85 SRAM size in KB (e.g., 832): ").strip()
        try:
            cm85_size = int(cm85_kb) * 1024

            # Calculate CM85 region
            self.config.cm85.ram.start = 0x22000000
            self.config.cm85.ram.length = cm85_size

            # IPC is fixed
            self.config.shared.ipc.start = 0x220D0000
            self.config.shared.ipc.length = 0x00010000

            # Calculate CM33 region (starts after IPC)
            self.config.cm33.ram.start = 0x220E0000
            remaining = 0x001A0000 - cm85_size  # Total SRAM - CM85 size
            self.config.cm33.ram.length = remaining

            print(f"\n✓ SRAM balanced:")
            print(f"  CM85: {cm85_size//1024}KB at {self.config.cm85.ram.start_hex}")
            print(f"  IPC:  64KB at {self.config.shared.ipc.start_hex}")
            print(f"  CM33: {remaining//1024}KB at {self.config.cm33.ram.start_hex}")

        except ValueError:
            print("✗ Invalid input")

        input("\nPress Enter to continue...")

    def validate_and_show_errors(self):
        """Validate configuration and show errors"""
        print("\n--- Validating Configuration ---")
        valid, errors = self.config.validate()

        if valid:
            print("✓ Configuration is valid!")
        else:
            print(f"✗ Found {len(errors)} error(s):")
            for i, error in enumerate(errors, 1):
                print(f"  {i}. {error}")

        input("\nPress Enter to continue...")

    def save_configuration(self):
        """Save configuration to YAML file"""
        print(f"\n--- Save Configuration ---")
        filename = input(f"Enter filename [{self.config_file}]: ").strip()
        if not filename:
            filename = self.config_file

        if self.config.save_to_yaml(filename):
            print(f"✓ Configuration saved to {filename}")
        else:
            print(f"✗ Failed to save configuration")

        input("Press Enter to continue...")

    def generate_linker_scripts(self):
        """Generate linker script files"""
        print("\n--- Generate Linker Scripts ---")
        print("This will update:")
        print("  - cm85/evk-ra8p1_cm85.ld")
        print("  - cm33/evk-ra8p1_cm33.ld")
        print()

        if input("Continue? (y/n): ").lower() != 'y':
            return

        # TODO: Implement linker script generation
        print("⚠ Feature not yet implemented")
        print("  Manually update the linker scripts with the new values")

        input("\nPress Enter to continue...")

    def export_header_file(self):
        """Export memory definitions as C header file"""
        print("\n--- Export C Header ---")
        filename = input("Enter filename [memory_map.h]: ").strip()
        if not filename:
            filename = "memory_map.h"

        try:
            with open(filename, 'w') as f:
                f.write("/* Auto-generated memory map for RA8P1 dual-core */\n\n")
                f.write("#ifndef __MEMORY_MAP_H\n")
                f.write("#define __MEMORY_MAP_H\n\n")

                # CM85
                f.write("/* CM85 (Cortex-M85) Memory Map */\n")
                self._write_region_defines(f, "CM85_FLASH", self.config.cm85.flash)
                self._write_region_defines(f, "CM85_RAM", self.config.cm85.ram)
                self._write_region_defines(f, "CM85_ITCM", self.config.cm85.itcm)
                self._write_region_defines(f, "CM85_DTCM", self.config.cm85.dtcm)
                f.write("\n")

                # CM33
                f.write("/* CM33 (Cortex-M33) Memory Map */\n")
                self._write_region_defines(f, "CM33_FLASH", self.config.cm33.flash)
                self._write_region_defines(f, "CM33_RAM", self.config.cm33.ram)
                self._write_region_defines(f, "CM33_ITCM", self.config.cm33.itcm)
                self._write_region_defines(f, "CM33_DTCM", self.config.cm33.dtcm)
                f.write("\n")

                # Shared
                f.write("/* Shared Memory */\n")
                self._write_region_defines(f, "IPC_SHMEM", self.config.shared.ipc)
                self._write_region_defines(f, "SDRAM", self.config.shared.sdram)
                self._write_region_defines(f, "OSPI_FLASH", self.config.shared.ospi_flash)

                f.write("\n#endif /* __MEMORY_MAP_H */\n")

            print(f"✓ Header file exported to {filename}")
        except Exception as e:
            print(f"✗ Failed to export: {e}")

        input("\nPress Enter to continue...")

    def _write_region_defines(self, f, prefix: str, region: MemoryRegion):
        """Write C defines for a memory region"""
        f.write(f"#define {prefix}_START  {region.start_hex}UL\n")
        f.write(f"#define {prefix}_LENGTH {region.length_hex}UL\n")
        f.write(f"#define {prefix}_END    {region.end_hex}UL\n")


def main():
    """Main entry point"""
    import argparse

    parser = argparse.ArgumentParser(
        description='RA8P1 Dual-Core Memory Placement Configuration Tool',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Interactive mode with default memory.yaml
  %(prog)s

  # Interactive mode with custom config file
  %(prog)s -c custom_memory.yaml

  # Validate only (no interactive)
  %(prog)s --validate

  # Export header file only
  %(prog)s --export memory_map.h
        """
    )

    parser.add_argument('-c', '--config', default='memory.yaml',
                       help='Configuration file (default: memory.yaml)')
    parser.add_argument('--validate', action='store_true',
                       help='Validate configuration and exit')
    parser.add_argument('--export', metavar='FILE',
                       help='Export C header file and exit')

    args = parser.parse_args()

    tool = PlacementTool(args.config)

    if args.validate:
        valid, errors = tool.config.validate()
        if valid:
            print("✓ Configuration is valid")
            sys.exit(0)
        else:
            print(f"✗ Configuration has {len(errors)} error(s):")
            for error in errors:
                print(f"  - {error}")
            sys.exit(1)

    elif args.export:
        tool.export_header_file()

    else:
        tool.run()


if __name__ == '__main__':
    main()

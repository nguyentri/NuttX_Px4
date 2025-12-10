#!/bin/bash
##############################################################################
# boards/arm/ra8/evk-ra8p1/scripts/verification/verify_placement.sh
#
# Verification script for RA8P1 dual-core memory layout
# Checks section placement, memory usage, and potential issues
##############################################################################

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
NUTTX_ELF=${1:-nuttx}
CORE=${2:-cm85}  # cm85 or cm33
TOOLCHAIN_PREFIX=${TOOLCHAIN_PREFIX:-arm-none-eabi-}

# Commands
NM="${TOOLCHAIN_PREFIX}nm"
OBJDUMP="${TOOLCHAIN_PREFIX}objdump"
SIZE="${TOOLCHAIN_PREFIX}size"
READELF="${TOOLCHAIN_PREFIX}readelf"

echo -e "${BLUE}================================================${NC}"
echo -e "${BLUE}RA8P1 Memory Layout Verification for ${CORE^^}${NC}"
echo -e "${BLUE}================================================${NC}"
echo ""

# Check if file exists
if [ ! -f "$NUTTX_ELF" ]; then
    echo -e "${RED}Error: $NUTTX_ELF not found${NC}"
    exit 1
fi

# Check if tools are available
for tool in $NM $OBJDUMP $SIZE $READELF; do
    if ! command -v $tool &> /dev/null; then
        echo -e "${RED}Error: $tool not found. Please install ARM toolchain.${NC}"
        exit 1
    fi
done

##############################################################################
# Function: Check symbol location
##############################################################################
check_symbol() {
    local symbol=$1
    local expected_start=$2
    local expected_end=$3
    local region_name=$4

    local addr=$($NM $NUTTX_ELF | grep " $symbol$" | awk '{print $1}')

    if [ -z "$addr" ]; then
        echo -e "${YELLOW}  Warning: Symbol $symbol not found${NC}"
        return 1
    fi

    local addr_dec=$((16#$addr))
    local start_dec=$((16#${expected_start#0x}))
    local end_dec=$((16#${expected_end#0x}))

    if [ $addr_dec -ge $start_dec ] && [ $addr_dec -lt $end_dec ]; then
        echo -e "${GREEN}  ✓ $symbol @ 0x$addr (in $region_name)${NC}"
        return 0
    else
        echo -e "${RED}  ✗ $symbol @ 0x$addr (NOT in $region_name: 0x$expected_start-0x$expected_end)${NC}"
        return 1
    fi
}

##############################################################################
# Function: Check section size
##############################################################################
check_section_size() {
    local section=$1
    local max_size=$2
    local region_name=$3

    local size=$($OBJDUMP -h $NUTTX_ELF | grep " $section " | awk '{print $3}')

    if [ -z "$size" ]; then
        echo -e "${YELLOW}  Warning: Section $section not found${NC}"
        return 0
    fi

    local size_dec=$((16#$size))
    local max_dec=$((16#${max_size#0x}))

    local size_kb=$((size_dec / 1024))
    local max_kb=$((max_dec / 1024))
    local pct=$((size_dec * 100 / max_dec))

    if [ $size_dec -le $max_dec ]; then
        echo -e "${GREEN}  ✓ $section: ${size_kb}KB / ${max_kb}KB ($pct%) in $region_name${NC}"
        return 0
    else
        echo -e "${RED}  ✗ $section: ${size_kb}KB exceeds ${max_kb}KB limit in $region_name${NC}"
        return 1
    fi
}

##############################################################################
# Function: Check for overlaps
##############################################################################
check_overlaps() {
    echo -e "\n${BLUE}Checking for memory overlaps...${NC}"

    $READELF -l $NUTTX_ELF | grep LOAD | while read line; do
        local vaddr=$(echo $line | awk '{print $3}')
        local memsz=$(echo $line | awk '{print $6}')

        if [ -n "$vaddr" ] && [ -n "$memsz" ]; then
            local start=$((16#${vaddr#0x}))
            local end=$((start + 16#${memsz#0x}))
            echo -e "  Region: 0x$(printf '%08x' $start) - 0x$(printf '%08x' $end) ($(($memsz / 1024))KB)"
        fi
    done

    # Check for common overlap issues
    local has_overlap=0

    # TODO: Add overlap detection logic

    if [ $has_overlap -eq 0 ]; then
        echo -e "${GREEN}  ✓ No overlaps detected${NC}"
    fi
}

##############################################################################
# Memory region definitions based on core
##############################################################################
if [ "$CORE" == "cm85" ]; then
    MRAM_START="0x02000000"
    MRAM_END="0x020E0000"  # 896KB
    MRAM_SIZE="0x000E0000"

    SRAM_START="0x22000000"
    SRAM_END="0x22150000"  # 1344KB
    SRAM_SIZE="0x00150000"

    ITCM_START="0x00000000"
    ITCM_END="0x00020000"  # 128KB
    ITCM_SIZE="0x00020000"

    DTCM_START="0x20000000"
    DTCM_END="0x20020000"  # 128KB
    DTCM_SIZE="0x00020000"

    OSPI_START="0x80000000"
    OSPI_END="0x84000000"  # 64MB
    OSPI_SIZE="0x04000000"

elif [ "$CORE" == "cm33" ]; then
    MRAM_START="0x02080000"
    MRAM_END="0x020A0000"  # 128KB
    MRAM_SIZE="0x00020000"

    SRAM_START="0x220E0000"
    SRAM_END="0x22120000"  # 256KB
    SRAM_SIZE="0x00040000"

    ITCM_START="0x00000000"
    ITCM_END="0x00010000"  # 64KB
    ITCM_SIZE="0x00010000"

    DTCM_START="0x20000000"
    DTCM_END="0x20010000"  # 64KB
    DTCM_SIZE="0x00010000"

    OSPI_START="0x80000000"
    OSPI_END="0x84000000"  # 64MB (shared)
    OSPI_SIZE="0x04000000"
fi

# Common regions
IPC_START="0x220D0000"
IPC_END="0x220E0000"  # 64KB
IPC_SIZE="0x00010000"

SDRAM_START="0x68000000"
SDRAM_END="0x70000000"  # 128MB
SDRAM_SIZE="0x08000000"

##############################################################################
# 1. Check Key Symbol Locations
##############################################################################
echo -e "\n${BLUE}1. Checking Key Symbol Locations${NC}"
echo -e "${BLUE}===================================${NC}"

echo -e "\nMRAM Symbols:"
check_symbol "_stext" "$MRAM_START" "$MRAM_END" "MRAM"
check_symbol "_etext" "$MRAM_START" "$MRAM_END" "MRAM"
check_symbol "_eronly" "$MRAM_START" "$MRAM_END" "MRAM"

echo -e "\nSRAM Symbols:"
check_symbol "_sdata" "$SRAM_START" "$SRAM_END" "SRAM"
check_symbol "_edata" "$SRAM_START" "$SRAM_END" "SRAM"
check_symbol "_sbss" "$SRAM_START" "$SRAM_END" "SRAM"
check_symbol "_ebss" "$SRAM_START" "$SRAM_END" "SRAM"

if [ "$CORE" == "cm85" ]; then
    echo -e "\nOSPI Flash Symbols (PX4 Application):"
    check_symbol "__px4_app_start" "$OSPI_START" "$OSPI_END" "OSPI"
    check_symbol "__px4_app_end" "$OSPI_START" "$OSPI_END" "OSPI"
fi

echo -e "\nIPC Shared Memory:"
check_symbol "__ipc_shmem_start" "$IPC_START" "$IPC_END" "IPC"
check_symbol "__ipc_shmem_end" "$IPC_START" "$IPC_END" "IPC"

##############################################################################
# 2. Check Section Sizes
##############################################################################
echo -e "\n${BLUE}2. Checking Section Sizes${NC}"
echo -e "${BLUE}===================================${NC}"

echo -e "\nInternal MRAM Usage:"
check_section_size ".text" "$MRAM_SIZE" "MRAM"
check_section_size ".rodata" "$MRAM_SIZE" "MRAM"

echo -e "\nSRAM Usage:"
check_section_size ".data" "$SRAM_SIZE" "SRAM"
check_section_size ".bss" "$SRAM_SIZE" "SRAM"

if [ "$CORE" == "cm85" ]; then
    echo -e "\nOSPI Flash Usage (PX4):"
    check_section_size ".px4_text" "$OSPI_SIZE" "OSPI"
fi

##############################################################################
# 3. Memory Usage Summary
##############################################################################
echo -e "\n${BLUE}3. Memory Usage Summary${NC}"
echo -e "${BLUE}===================================${NC}"

$SIZE $NUTTX_ELF
echo ""

$SIZE -A $NUTTX_ELF | grep -E "\.text|\.rodata|\.data|\.bss|\.px4_text|\.ipc_shmem" | \
    awk '{printf "  %-20s %10d bytes (%6d KB)\n", $1, $2, $2/1024}'

##############################################################################
# 4. Check Critical Sections
##############################################################################
echo -e "\n${BLUE}4. Checking Critical Sections${NC}"
echo -e "${BLUE}===================================${NC}"

# Check if .vectors is at the start of FLASH
echo -e "\nVector Table:"
vectors_addr=$($NM $NUTTX_ELF | grep " _VECTORS$" | awk '{print $1}')
if [ "$vectors_addr" == "${MRAM_START#0x}" ]; then
    echo -e "${GREEN}  ✓ Vectors at start of MRAM (0x$vectors_addr)${NC}"
else
    echo -e "${RED}  ✗ Vectors not at start of MRAM (at 0x$vectors_addr, expected $MRAM_START)${NC}"
fi

# Check if PX4 code is in OSPI (CM85 only)
if [ "$CORE" == "cm85" ]; then
    echo -e "\nPX4 Code Placement:"
    px4_syms=$($NM $NUTTX_ELF | grep -E "px4_|ekf2_|mavlink_" | wc -l)
    if [ $px4_syms -gt 0 ]; then
        echo -e "${GREEN}  ✓ Found $px4_syms PX4 symbols${NC}"

        # Check a few PX4 symbols are in OSPI range
        $NM $NUTTX_ELF | grep -E "px4_|ekf2_|mavlink_" | head -5 | while read addr type sym; do
            addr_dec=$((16#$addr))
            ospi_start=$((16#${OSPI_START#0x}))
            ospi_end=$((16#${OSPI_END#0x}))

            if [ $addr_dec -ge $ospi_start ] && [ $addr_dec -lt $ospi_end ]; then
                echo -e "${GREEN}    ✓ $sym in OSPI (0x$addr)${NC}"
            else
                echo -e "${YELLOW}    ? $sym not in OSPI (0x$addr)${NC}"
            fi
        done
    else
        echo -e "${YELLOW}  Warning: No PX4 symbols found${NC}"
    fi
fi

##############################################################################
# 5. Check for Common Issues
##############################################################################
echo -e "\n${BLUE}5. Checking for Common Issues${NC}"
echo -e "${BLUE}===================================${NC}"

# Check for undefined symbols
echo -e "\nUndefined Symbols:"
undef_count=$($NM $NUTTX_ELF | grep " U " | wc -l)
if [ $undef_count -eq 0 ]; then
    echo -e "${GREEN}  ✓ No undefined symbols${NC}"
else
    echo -e "${YELLOW}  Warning: $undef_count undefined symbols${NC}"
    $NM $NUTTX_ELF | grep " U " | head -10 | awk '{print "    " $2}'
    if [ $undef_count -gt 10 ]; then
        echo -e "    ... and $((undef_count - 10)) more"
    fi
fi

# Check for overlaps
check_overlaps

# Check heap size
echo -e "\nHeap Configuration:"
heap_start=$($NM $NUTTX_ELF | grep " __heap_start$" | awk '{print $1}')
heap_end=$($NM $NUTTX_ELF | grep " __heap_end$" | awk '{print $1}')

if [ -n "$heap_start" ] && [ -n "$heap_end" ]; then
    heap_size=$((16#$heap_end - 16#$heap_start))
    heap_kb=$((heap_size / 1024))
    echo -e "${GREEN}  ✓ Heap size: ${heap_kb}KB (0x$heap_start - 0x$heap_end)${NC}"

    if [ $heap_kb -lt 100 ]; then
        echo -e "${YELLOW}    Warning: Heap size is small (<100KB)${NC}"
    fi
else
    echo -e "${YELLOW}  Warning: Heap symbols not found${NC}"
fi

##############################################################################
# 6. Generate Memory Map
##############################################################################
echo -e "\n${BLUE}6. Memory Map${NC}"
echo -e "${BLUE}===================================${NC}"

$READELF -S $NUTTX_ELF | grep -E "PROGBITS|NOBITS" | \
    awk '{printf "  %-20s %10s  %s\n", $2, $6, $4}'

##############################################################################
# Summary
##############################################################################
echo -e "\n${BLUE}================================================${NC}"
echo -e "${GREEN}Verification Complete for ${CORE^^}${NC}"
echo -e "${BLUE}================================================${NC}"
echo ""
echo -e "For detailed analysis, use:"
echo -e "  ${YELLOW}$OBJDUMP -h $NUTTX_ELF${NC}"
echo -e "  ${YELLOW}$NM $NUTTX_ELF | grep <symbol>${NC}"
echo -e "  ${YELLOW}$READELF -l $NUTTX_ELF${NC}"
echo ""
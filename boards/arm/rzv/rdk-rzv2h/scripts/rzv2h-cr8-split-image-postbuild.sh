#!/usr/bin/env bash
# Split-image postbuild for RZ/V2H CR8-0 / CR8-1 NuttX images.
#
# Extracts the linker's per-core load sections into raw binaries, concatenates
# them in the loader-expected order (header + itcm + sram + sdram), then emits
# an SREC at the core's flash VMA. Mirrors the Renesas FSP reference at
# refs/px4-freertos-posix-renesas-fsp/script/postbuild.sh (RZ/V branch).
#
# Usage:  postbuild.sh <path-to-nuttx-elf> <cr8_0|cr8_1>
# Emits:  <elfbase>_header.bin, _itcm.bin, _sram.bin, _sdram.bin,
#         <elfbase>.bin (concatenated), <elfbase>.srec (loader-ready)
#
# Loader SREC VMA (from Renesas ATF / SCIF-boot flow):
#   CR8-0 -> 0x60200000
#   CR8-1 -> 0x61300000

set -euo pipefail

if [ "$#" -lt 2 ]; then
  echo "usage: $0 <nuttx-elf> <cr8_0|cr8_1>" >&2
  exit 1
fi

ELF="$1"
CORE="$2"

case "$CORE" in
  cr8_0) SREC_VMA=0x60200000 ;;
  cr8_1) SREC_VMA=0x61300000 ;;
  *)     echo "$0: unknown core '$CORE' (expected cr8_0 or cr8_1)" >&2; exit 1 ;;
esac

OBJCOPY="${OBJCOPY:-arm-none-eabi-objcopy}"
BODY="${ELF%.*}"

echo "Postbuild: split image for $CORE (SREC VMA $SREC_VMA)"

"$OBJCOPY" -O binary -j .header -j .header_reserved             "$ELF" "${BODY}_header.bin"
"$OBJCOPY" -O binary -j .itcm_load_section0 -j .itcm_load_section1 "$ELF" "${BODY}_itcm.bin"
"$OBJCOPY" -O binary -j .sram_load_section0 -j .sram_load_section1 "$ELF" "${BODY}_sram.bin"
"$OBJCOPY" -O binary -j .sdram_text_section -j .sdram_data_section "$ELF" "${BODY}_sdram.bin"

# Concatenate in loader-expected order; tolerate missing (empty) sections.
cat "${BODY}_header.bin" "${BODY}_itcm.bin" "${BODY}_sram.bin" "${BODY}_sdram.bin" \
    > "${BODY}.bin"

"$OBJCOPY" -I binary -O srec --adjust-vma "$SREC_VMA" --srec-forceS3 \
    "${BODY}.bin" "${BODY}.srec"

echo "Postbuild: $(stat -c%s "${BODY}.bin") bytes -> ${BODY}.bin, ${BODY}.srec"

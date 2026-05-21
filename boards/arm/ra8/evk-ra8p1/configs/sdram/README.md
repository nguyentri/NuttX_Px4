# EVK-RA8P1 – SDRAM NSH Application

This configuration builds NuttX NSH with support for **External SDRAM** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/sdram/`

## Features Enabled

- `CONFIG_RA_SDRAM=y` - SDRAM Controller Driver
- `CONFIG_RA_SDRAM_SIZE=0x02000000` - 32MB SDRAM Size

## Hardware Setup

- Signal: SDRAM Bus
- EVK-RA8P1 Pin: On-board SDRAM
- External device: None (On-board)

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:sdram
make -j
```

## Flash

Example (J-Link):

```bash
JLinkExe -device R7KA8P1KF -if SWD -speed 4000
loadfile nuttx.hex
r
g
```

## Console

Connect USB-serial:

```text
115200 8N1
```

## NSH Test Commands

Run the following commands to verify functionality:

```bash
nsh> free
             total       used       free    largest
Mem:      34078720     123456   33955264   33955264
```

(Verify total memory includes SDRAM size)

## Files of Interest

- defconfig
- `src/ra8p1_sdram.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure correct config selected
- Check SDRAM initialization logs

# EVK-RA8P1 – MRAM NSH Application

This configuration builds NuttX NSH with support for **MRAM (Magnetoresistive RAM)** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/mram/`

## Features Enabled

- `CONFIG_RA_MRAM=y` - MRAM Driver
- `CONFIG_MTD=y` - Memory Technology Device Support
- `CONFIG_FS_LITTLEFS=y` - LittleFS (for parameter storage)
- `CONFIG_RA_MRAM_DATA=y` - Data MRAM Support

## Hardware Setup

No external HW required. Uses internal MRAM.

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:mram
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
nsh> mount -t littlefs /dev/mtdblock0 /mnt/mram
nsh> echo "Hello MRAM" > /mnt/mram/test.txt
nsh> cat /mnt/mram/test.txt
Hello MRAM
```

## Files of Interest

- defconfig
- `src/ra8p1_mram.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure correct config selected
- Use `ls /dev` to confirm MTD device exists

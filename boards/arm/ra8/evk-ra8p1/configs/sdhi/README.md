# EVK-RA8P1 – SDHI NSH Application

This configuration builds NuttX NSH with support for **SD Card (SDHI)** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/sdhi/`

## Features Enabled

- `CONFIG_RA_SDHI=y` - SDHI Driver
- `CONFIG_MMCSD=y` - MMC/SD Driver
- `CONFIG_FS_FAT=y` - FAT Filesystem

## Hardware Setup

- Signal: SDIO
- EVK-RA8P1 Pin: MicroSD Card Slot
- External device: MicroSD Card (Formatted FAT32)

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:sdhi
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
nsh> mount -t vfat /dev/mmcsd0 /mnt/sdcard
nsh> ls /mnt/sdcard
```

## Files of Interest

- defconfig
- `src/ra8p1_sdhi.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure SD card is inserted
- Check card formatting
- Use `ls /dev` to confirm driver node exists (`/dev/mmcsd0`)

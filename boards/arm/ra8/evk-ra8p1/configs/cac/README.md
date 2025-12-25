# EVK-RA8P1 – CAC NSH Application

This configuration builds NuttX NSH with support for **CAC (Clock Frequency Accuracy Measurement Circuit)** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/cac/`

## Features Enabled

- `CONFIG_RA_CAC=y` - CAC Driver Support

## Hardware Setup

No external HW required.

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:cac
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
nsh> ls /dev/cac*
/dev/cac0
```

## Files of Interest

- defconfig
- `src/ra8p1_cac.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure correct config selected
- Use `ls /dev` to confirm driver node exists

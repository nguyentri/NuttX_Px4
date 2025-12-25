# EVK-RA8P1 – I3C NSH Application

This configuration builds NuttX NSH with support for **I3C (Improved Inter-Integrated Circuit)** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/i3c/`

## Features Enabled

- `CONFIG_RA_I3C=y` - I3C Driver
- `CONFIG_RA_I3C0=y` - I3C Unit 0
- `CONFIG_RA8P1_I3C_EXAMPLE=y` - I3C Example Application

## Hardware Setup

- Signal: I3C0 SDA/SCL
- EVK-RA8P1 Pin: P403 (SDA), P404 (SCL) (Verify against board schematic)
- External device: I3C Target Device
- Power/Jumper notes: Ensure pull-ups are present if required (I3C has active pull-ups but check board config).

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:i3c
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
nsh> i3c_demo
```

## Files of Interest

- defconfig
- `src/ra8p1_i3c.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure correct config selected
- Check pinmux in board sources
- Use `ls /dev` to confirm driver node exists

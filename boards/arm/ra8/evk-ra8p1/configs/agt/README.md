# EVK-RA8P1 – AGT NSH Application

This configuration builds NuttX NSH with support for **AGT (Asynchronous General Purpose Timer)** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/agt/`

## Features Enabled

- `CONFIG_RA8_AGT=y` - AGT Driver Support
- `CONFIG_RA8_AGT0=y` - AGT Channel 0
- `CONFIG_RA8_AGT1=y` - AGT Channel 1
- `CONFIG_TIMER=y` - Standard Timer Interface

## Hardware Setup

No external HW required.

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:agt
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
nsh> ls /dev/timer*
/dev/timer0
/dev/timer1
```

## Files of Interest

- defconfig
- `src/ra8p1_agt.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure correct config selected
- Use `ls /dev` to confirm driver node exists

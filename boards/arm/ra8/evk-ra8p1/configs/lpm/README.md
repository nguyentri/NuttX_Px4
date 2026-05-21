# EVK-RA8P1 – LPM NSH Application

This configuration builds NuttX NSH with support for **Low Power Modes (LPM)** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/lpm/`

## Features Enabled

- `CONFIG_RA_LPM=y` - Low Power Mode Support
- `CONFIG_PM=y` - Power Management Framework
- `CONFIG_RA_ULPT=y` - Ultra-Low Power Timer (for wake-up)
- `CONFIG_RA_LPM_DEEP_STANDBY_SUPPORT=y` - Deep Standby Support

## Hardware Setup

No external HW required.

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:lpm
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
nsh> pmconfig
```

(Use `pmconfig` or similar PM commands if enabled, or verify power consumption)

## Files of Interest

- defconfig
- `src/ra8p1_lpm.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure correct config selected
- Monitor current consumption to verify low power states

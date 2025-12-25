# EVK-RA8P1 – MIPI-CSI NSH Application

This configuration builds NuttX NSH with support for **MIPI-CSI Camera Interface** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/mipi-csi/`

## Features Enabled

- `CONFIG_RA_MIPI_CSI=y` - MIPI-CSI Driver
- `CONFIG_VIDEO=y` - Video Subsystem
- `CONFIG_RA_VIN=y` - Video Input (VIN)
- `CONFIG_RA_MIPI_CSI_DATA_LANES=2` - 2-Lane Configuration

## Hardware Setup

- Signal: MIPI-CSI
- EVK-RA8P1 Pin: Camera Connector (CN1/CN2 - verify schematic)
- External device: MIPI-CSI Camera Module (e.g., OV5640)
- Power/Jumper notes: Ensure camera is powered and connected correctly.

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:mipi-csi
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
nsh> ls /dev/video*
/dev/video0
```

## Files of Interest

- defconfig
- `src/ra8p1_mipi_csi.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure camera module is compatible and connected
- Check I2C communication with camera sensor
- Verify MIPI clock and lane configuration

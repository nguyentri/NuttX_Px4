# EVK-RA8P1 – GPS NSH Application

This configuration builds NuttX NSH with support for **GPS** connected via UART on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/gps/`

## Features Enabled

- `CONFIG_RA_UART3_GPS=y` - UART3 configured for GPS
- `CONFIG_EXAMPLES_GPS=y` - GPS Example Application
- `CONFIG_RA_SCI3_RXDMA=y` - DMA Receive Support

## Hardware Setup

- Signal: UART3 RX/TX
- EVK-RA8P1 Pin: P408 (TX), P409 (RX) (Verify against board schematic/pinmap)
- External device: GPS Module (e.g., u-blox)
- Power/Jumper notes: Connect GPS TX to EVK RX, GPS RX to EVK TX.

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:gps
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
nsh> gps
```

Expected output:

```text
Reading from /dev/ttyS3...
<NMEA data stream>
```

## Files of Interest

- defconfig
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure GPS module is powered and has a fix
- Verify baud rate matches GPS module default
- Check wiring (TX/RX crossed)

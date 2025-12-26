# EVK-RA8P1 – SPI Loopback NSH Application

This configuration builds NuttX NSH with support for **SPI Loopback Test** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/spi-loopback/`

## Features Enabled

- `CONFIG_RA_SPI=y` - SPI Driver
- `CONFIG_RA8P1_SPI_LOOPBACK_EXAMPLE=y` - SPI Loopback Example
- `CONFIG_SPI_EXCHANGE=y` - SPI Exchange Support

## Hardware Setup

**No external connections required** - This test uses internal SPI loopback mode.

The SPI peripheral is configured with internal loopback enabled (SPLP2 bit), which routes transmitted data directly back to the receive buffer without requiring physical MOSI-to-MISO connections.

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:spi-loopback
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

Connect USB-serial (SCI0 UART):

```text
115200 8N1
```

**Note:** Test output is logged via RTT (SEGGER Real-Time Transfer), not UART console.

## Viewing RTT Logs

The SPI loopback test outputs detailed logs via RTT. To view them:

**Option 1: J-Link RTT Viewer (GUI)**
```bash
JLinkRTTViewer
# Select device: R7KA8P1KF
# Interface: SWD
# Speed: 4000 kHz
```

**Option 2: JLinkRTTClient (Command line)**
```bash
# Terminal 1: Start RTT Server
JLinkExe -device R7KA8P1KF -if SWD -speed 4000
# Inside J-Link prompt, keep connection active

# Terminal 2: Connect RTT Client
JLinkRTTClient
```

**Option 3: GDB + RTT**
If debugging with GDB, RTT logs appear automatically in the J-Link GDB Server console.

## NSH Test Commands

The test runs automatically at boot. No manual command execution is needed.

## Expected RTT Output

When the board boots, you should see the following in the RTT log viewer:

```text
Nuttx: RA8P1 Board bring-up starting...
Initializing SPI loopback demo...
SPI devices configured: SPI0=0x220000bc as master
SPI devices configured: SPI1=0x22000080 as master
SPI loopback demo initialized successfully
RA8P1 SPI Loopback Test
=======================
This test verifies SPI loopback functionality:
=== Starting SPI Loopback Test ===
Test data prepared: SPI0 TX[0]=0x78, SPI1 TX[0]=0x87
Starting SPI loopback test...
Testing Internal SPI0 loopback ...
Testing Internal SPI1 loopback ...
Loopback transfers completed
Verifying SPI loopback data...
SPI0 loopback match at index 0: TX=0x78 == RX=0x78
SPI0 loopback match at index 1: TX=0xde == RX=0xde
...
SPI0 loopback match at index 31: TX=0x79 == RX=0x79
SPI1 loopback match at index 0: TX=0x87 == RX=0x87
SPI1 loopback match at index 1: TX=0x23 == RX=0x23
...
SPI1 loopback match at index 31: TX=0xc4 == RX=0xc4
✓ SPI loopback test PASSED - all data verified successfully
  SPI0: 32 bytes looped back correctly
  SPI1: 32 bytes looped back correctly
```

**Success criteria:** All 32 bytes for both SPI0 and SPI1 show TX == RX matches.

## Files of Interest

- defconfig
- `src/ra8p1_spi_loopback.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- If test fails, verify SPI driver is properly initialized
- Check that `CONFIG_RA_SPI=y` and `CONFIG_RA8P1_SPI_LOOPBACK_EXAMPLE=y` are enabled
- Review syslog output via RTT for detailed error messages

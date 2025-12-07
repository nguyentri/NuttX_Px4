# WDT Test Application for EVK-RA8P1

## Overview

This test application demonstrates the Watchdog Timer (WDT) functionality on the EVK-RA8P1 board, similar to the Renesas FSP reference example (wdt_ek_ra8p1_ep).

## Features

- Initializes WDT with 2-second timeout
- Refreshes WDT counter every 1 second using a periodic POSIX timer
- Prints refresh status every 3 seconds to syslog
- Button SW1 triggers timeout by stopping refresh
- LED1 indicates system status:
  - Toggles during normal operation (WDT being refreshed)
  - Stays OFF when refresh is stopped
  - Stays ON after WDT reset

## Build Instructions

1. Configure NuttX for WDT test:
```bash
cd platforms/nuttx/NuttX/nuttx
./tools/configure.sh evk-ra8p1:wdt
```

2. Build:
```bash
make -j$(nproc)
```

3. Flash to board:
```bash
# Use your preferred flashing method (JLink, etc.)
```

## Usage

1. Connect to serial console (115200 baud, 8N1)
2. The application runs automatically at boot
3. Observe:
   - WDT refresh messages every 3 seconds
   - LED1 toggling every second
4. Press button SW1 to trigger WDT timeout
5. System will reset after ~2 seconds
6. After reset, LED1 will stay ON and a reset message will be displayed

## Expected Output

### Normal Operation
```
NuttX WDT Test Application (FSP-style)
========================================================
This example demonstrates WDT HAL module functionality.
The WDT counter is refreshed periodically every 1 second.
Refresh status is printed every 3 seconds.
Press push button SW1 to stop WDT counter from refreshing.
Approximately after 2 seconds, WDT resets MCU and turns LED ON.
========================================================

Button SW1 configured for external interrupt
Watchdog device opened: /dev/watchdog0
WDT timeout set to 2000 ms
WDT started successfully
GPT-like timer started - refreshing WDT every 1000 ms

WDT initialized and running. Press SW1 to trigger timeout.

WDT counter refreshed (count=3, timeout=2000 ms, timeleft=1500 ms)
WDT counter refreshed (count=6, timeout=2000 ms, timeleft=1800 ms)
...
```

### After Button Press
```
*** Button SW1 pressed - Stopping WDT refresh ***
WDT will timeout in approximately 2 seconds and reset MCU
Timer stopped - WDT will no longer be refreshed
Waiting for WDT reset...
Waiting for WDT reset...
<SYSTEM RESETS>
```

### After WDT Reset
```
************************ WDT Reset detected ************************
System was reset by watchdog timeout!
********************************************************************
<LED1 stays ON for 2 seconds>
<Application restarts>
```

## Hardware Connections

- **LED1**: Connected to P40_0 (active low)
- **SW1**: Connected to P40_1 (falling edge trigger)
- **Serial Console**: SCI2 (115200 8N1)

## Configuration Options

Key Kconfig settings in `evk-ra8p1:wdt` defconfig:

```
CONFIG_WATCHDOG=y                 # Enable watchdog framework
CONFIG_RA_WDT=y                   # Enable RA8 WDT driver
CONFIG_RA8P1_EXAMPLE_SUPPORT=y    # Enable board examples
CONFIG_RA8P1_WDT_TEST=y           # Enable WDT test application
CONFIG_ARCH_BUTTONS=y             # Enable button support
```

## Implementation Notes

### Differences from FSP Example

1. **Timer Implementation**: Uses POSIX timer_create() instead of GPT hardware timer
2. **Button Handling**: Uses NuttX GPIO interrupt API instead of FSP ICU API
3. **WDT API**: Uses NuttX watchdog IOCTLs instead of FSP R_WDT_* functions
4. **Logging**: Uses syslog() instead of RTT/UART printf

### NuttX Watchdog IOCTLs Used

- `WDIOC_START`: Start the watchdog timer
- `WDIOC_SETTIMEOUT`: Configure timeout period
- `WDIOC_KEEPALIVE`: Refresh/pet the watchdog
- `WDIOC_GETSTATUS`: Read status and time left

### Reset Detection

The application reads `R_SYSTEM->RSTSR1` register (0x4001e410) to detect if the previous reset was caused by WDT timeout.

## Troubleshooting

1. **WDT doesn't reset system**:
   - Verify WDT is not in auto-start mode (check OFS0 option bytes)
   - Ensure DBGSTOPCR.DBGSTOP_WDT is cleared for debug mode operation

2. **Button doesn't work**:
   - Check SW1 GPIO configuration in board GPIO table
   - Verify external interrupt is properly configured

3. **LED doesn't toggle**:
   - Verify LED1 GPIO configuration
   - Check LED polarity (active low on EVK-RA8P1)

## References

- FSP Example: `.refs/wdt_ek_ra8p1_ep/`
- NuttX WDT Driver: `arch/arm/src/ra8/ra_wdt.c`
- RA8P1 Hardware Manual: Section on WDT and RSTSR registers

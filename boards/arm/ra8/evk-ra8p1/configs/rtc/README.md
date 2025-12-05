# RTC Configuration for EVK-RA8P1

This configuration enables the NuttX RTC (Real-Time Clock) driver with alarm
support on the Renesas EVK-RA8P1 board.

## Features

- Full RTC functionality with date/time support
- Alarm interrupt support (1 alarm)
- Uses sub-clock (32.768 kHz) as the clock source
- Includes the NuttX `alarm` example application for testing

## Building

```bash
# From NuttX root directory
cd platforms/nuttx/NuttX/nuttx
./tools/configure.sh evk-ra8p1:rtc
make
```

Or using PX4 build system:
```bash
make renesas_evk-ra8p1_rtc
```

## Testing the RTC Alarm

Once booted into NSH, the `alarm` command is available:

### Set an alarm for 10 seconds from now:
```
nsh> alarm 10
Opening /dev/rtc0
alarm_daemon started
Alarm 0 set in 10 seconds
```

### Wait for alarm to trigger:
After 10 seconds, you should see:
```
alarm_daemon: alarm 0 received
```

### Read the current alarm status:
```
nsh> alarm -r
Opening /dev/rtc0
Alarm 0 is active with 5 seconds to expiration
```

### Cancel an alarm:
```
nsh> alarm -c
Opening /dev/rtc0
Alarm 0 has been canceled
```

### Command help:
```
nsh> alarm
USAGE:
        alarm [-a <alarmid>] [-cr] [<seconds>]
Where:
        -a <alarmid>
                <alarmid> selects the alarm: 0..0 (default: 0)
        -c      Cancel previously set alarm
        -r      Read previously set alarm
        <seconds>
                The number of seconds until the alarm expires.
                (only if no -c or -r option given.)
```

## Configuration Options

Key options enabled in this defconfig:

| Config Option | Description |
|---------------|-------------|
| `CONFIG_RA_RTC=y` | Enable RA8 RTC peripheral |
| `CONFIG_RA_RTC_CLOCK_SUBCLK=y` | Use 32.768 kHz sub-clock |
| `CONFIG_RTC=y` | Enable RTC framework |
| `CONFIG_RTC_DATETIME=y` | Calendar mode support |
| `CONFIG_RTC_ALARM=y` | Alarm support |
| `CONFIG_RTC_NALARMS=1` | Number of alarms |
| `CONFIG_RTC_DRIVER=y` | Upper-half RTC driver |
| `CONFIG_EXAMPLES_ALARM=y` | Alarm test example |

## Debug Output

RTC debug output is enabled. Use RTT or serial console to view:
- `rtcinfo()` - Informational messages
- `rtcwarn()` - Warning messages
- `rtcerr()` - Error messages

## Hardware Notes

- The RTC uses the 32.768 kHz sub-clock oscillator (SOSC)
- RTC maintains time during low-power modes if VBATT is provided
- The alarm interrupt uses the RTC ALM interrupt vector

## Files Modified/Created

- `arch/arm/src/ra8/ra_rtc.c` - RTC driver implementation
- `arch/arm/src/ra8/ra_rtc.h` - RTC header with definitions
- `arch/arm/src/ra8/ra_rtc_lowerhalf.c` - RTC lower-half driver
- `arch/arm/src/ra8/ra_rtc_lowerhalf.h` - Lower-half header
- `boards/arm/ra8/evk-ra8p1/src/ra8p1_rtc.c` - Board RTC init
- `boards/arm/ra8/evk-ra8p1/configs/rtc/defconfig` - This config

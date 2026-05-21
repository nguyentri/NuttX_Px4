# EVK-RA8P1 – Ethernet NSH Application

This configuration builds NuttX NSH with support for **Ethernet** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/ether/`

## Features Enabled

- `CONFIG_RA_ETHERNET=y` - Ethernet Controller
- `CONFIG_RA_ETHERC_RGMII=y` - RGMII Interface
- `CONFIG_RA_ETHERNET_PHY_GPY111=y` - GPY111 PHY Support
- `CONFIG_NET=y` - Networking Stack (IPv4, TCP, UDP, ICMP)

## Hardware Setup

- Signal: Ethernet
- EVK-RA8P1 Pin: RJ45 Connector
- External device: Network Switch/Router
- Power/Jumper notes: Ensure PHY jumpers are set for RGMII mode if applicable.

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:ether
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
nsh> ifconfig
eth0    Link encap:Ethernet HWaddr 00:11:22:33:44:55 at UP
        inet addr:10.0.0.2 DRaddr:10.0.0.1 Mask:255.255.255.0

nsh> ping 10.0.0.1
PING 10.0.0.1 56 bytes of data
56 bytes from 10.0.0.1: icmp_seq=0 time=0 ms
```

## Files of Interest

- defconfig
- `src/ra8p1_ether.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure Ethernet cable is connected
- Check network configuration (IP address, gateway)
- Verify PHY initialization in boot logs

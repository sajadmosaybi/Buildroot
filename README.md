cat <<EOL > README.md
# Buildroot Network Setup

This repository contains instructions and configurations for enabling **Ethernet**, **DHCP**, and **SSH** in a Buildroot-based Linux system for embedded boards such as STM32MP1, Zynq, or Raspberry Pi.

## Features

- Ethernet interface support
- DHCP client to automatically obtain IP
- SSH server (Dropbear) for remote access

## Buildroot Configuration Steps

### 1. Enable Ethernet Interface

1. Start Buildroot configuration:

\`\`\`bash
make menuconfig
\`\`\`

2. Enable networking support:

\`\`\`
Target packages → Networking applications → Network configuration
\`\`\`

- Ensure \`ifupdown\` or BusyBox networking utilities are selected.

3. Enable the correct Ethernet driver in the kernel:

\`\`\`
Kernel → Linux Kernel → Kernel configuration
\`\`\`

- Enable your board’s Ethernet driver (e.g., ENET for STM32MP1).
- Make sure \`CONFIG_NET\` and \`CONFIG_INET\` are enabled.

### 2. Enable DHCP

**Option A: Using BusyBox \`udhcpc\` (recommended)**

- In Buildroot menu:

\`\`\`
Target packages → Networking applications → BusyBox → udhcpc
\`\`\`

- Configure \`/etc/network/interfaces\`:

\`\`\`text
auto eth0
iface eth0 inet dhcp
\`\`\`

**Option B: Using \`dhcpcd\`**

- In Buildroot menu:

\`\`\`
Target packages → Networking applications → dhcpcd
\`\`\`

- DHCP client will automatically assign an IP at boot.

### 3. Enable SSH (Dropbear)

1. In Buildroot menu:

\`\`\`
Target packages → Networking applications → Dropbear
\`\`\`

2. Configure root password or SSH keys.
3. Dropbear starts automatically at boot.

### 4. Build and Deploy

\`\`\`bash
make
\`\`\`

- Flash the generated image to your board.
- Boot and verify:

\`\`\`bash
ip addr show eth0
ssh root@<board_ip>
\`\`\`

### Notes

- Replace \`eth0\` with your actual Ethernet interface name if different.
- Make sure your board’s kernel has proper drivers for your Ethernet hardware.
- Dropbear is lightweight and suitable for embedded systems.

### References

- [Buildroot Manual](https://buildroot.org/downloads/manual/manual.html)
- [BusyBox udhcpc](https://busybox.net/downloads/BusyBox.html)
- [Dropbear SSH](https://matt.ucc.asn.au/dropbear/dropbear.html)
EOL

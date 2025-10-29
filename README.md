# Buildroot: Ethernet, DHCP, and SSH Setup Guide

This guide explains how to configure a Buildroot-based Linux system with **Ethernet**, **DHCP**, and **SSH** support. It includes step-by-step instructions, configuration examples, and optional automation scripts for your target board.

---

## Table of Contents

1. [Prerequisites](#prerequisites)  
2. [Enable Ethernet Support](#enable-ethernet-support)  
3. [Configure DHCP](#configure-dhcp)  
4. [Enable SSH (Dropbear)](#enable-ssh-dropbear)  
5. [Automate Network Startup](#automate-network-startup)  
6. [Build and Deploy](#build-and-deploy)  
7. [Verify Network and SSH](#verify-network-and-ssh)  
8. [Optional: Static IP](#optional-static-ip)  
9. [Notes](#notes)  

---

## Prerequisites

- Buildroot installed on your host machine.  
- A target board with Ethernet support.  
- Serial console access for initial configuration.  

---

## Enable Ethernet Support

1. Launch Buildroot configuration:

```bash
make menuconfig
```

2. Configure target packages:

```
Target packages  --->
    Hardware handling  --->
        Network applications  --->
            [*] ifconfig
```

3. Configure the Linux kernel to include your Ethernet driver:

```
Linux Kernel  --->
    Device Drivers  --->
        Network device support  --->
            [*] Your Ethernet driver
```

> **Tip:** If unsure which driver, check your board documentation or use `dmesg` on Linux to see recognized network devices.

---

## Configure DHCP

1. Include a DHCP client (e.g., `dhcpcd`) in Buildroot:

```
Target packages  --->
    Networking applications  --->
        [*] dhcpcd
```

2. Enable automatic DHCP on boot by editing network interfaces:

**Create `/etc/network/interfaces` on target rootfs:**

```bash
auto eth0
iface eth0 inet dhcp
```

> Replace `eth0` with your actual Ethernet interface if different.

3. BusyBox alternative (in `/etc/init.d/S99network`):

```bash
#!/bin/sh
# Start DHCP client
ifconfig eth0 up
dhcpcd eth0
```

- Make script executable:

```bash
chmod +x /etc/init.d/S99network
```

---
## Static IP Configuration
```bash
nano//etc/network/interfaces
```
```bash
auto eth0
iface eth0 inet static
    address 192.168.100.99
    netmask 255.255.255.0
    gateway 192.168.100.1
    dns-nameservers 8.8.8.8 1.1.1.1
```
## Enable SSH (Dropbear)

1. Enable Dropbear in Buildroot:

```
Target packages  --->
    Networking applications  --->
        [*] dropbear
```

2. Set a root password:

```
System configuration  --->
    Root password
```

3. Optional: Add SSH keys for passwordless login:

- Create `/etc/dropbear/authorized_keys` and add your public key.  

4. Dropbear will automatically start at boot (if enabled via Buildroot config).

---

## Automate Network Startup (Optional)

You can add a script to automatically bring up Ethernet and DHCP:

**`/etc/init.d/S50network`**

```bash
#!/bin/sh
### BEGIN INIT INFO
# Provides:          network
# Required-Start:    $network
# Required-Stop:
# Default-Start:     2 3 4 5
# Default-Stop:
# Short-Description: Bring up network interfaces
### END INIT INFO

ifconfig eth0 up
dhcpcd eth0
```

- Make it executable:

```bash
chmod +x /etc/init.d/S50network
```

- This ensures DHCP is requested on every boot.

---

## Build and Deploy

1. Build Buildroot image:

```bash
make
```

2. Flash the image to your target board using your preferred method (SD card, USB, JTAG, etc.).  

3. Boot the board.

---

## Verify Network and SSH

1. Check Ethernet interface:

```bash
ifconfig eth0
```

- Should show an IP address assigned via DHCP.

2. Ping to test connectivity:

```bash
ping google.com
```

3. Connect via SSH:

```bash
ssh root@<target-ip>
```

---

## Optional: Static IP

If you prefer a static IP instead of DHCP:

**Edit `/etc/network/interfaces`:**

```bash
auto eth0
iface eth0 inet static
    address 192.168.1.100
    netmask 255.255.255.0
    gateway 192.168.1.1
```

- Then restart network:

```bash
/etc/init.d/S50network restart
```

---

## Notes

- Ethernet interface name may vary (e.g., `enp0s1` instead of `eth0`). Adjust configurations accordingly.  
- For production, prefer SSH key authentication over password login.  
- If using Wi-Fi, you can add `wpa_supplicant` and follow a similar process.


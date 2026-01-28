# Buildroot Configuration

This repository contains the configuration and support files for building a custom Linux system using Buildroot for the STM32MP157-DK1 development board.

## 🧠 What is Buildroot?

[Buildroot](https://buildroot.org) is a simple, efficient, and powerful tool to generate embedded Linux systems through cross-compilation.

## 🧩 Board Used

- **STM32MP157-DK1**, **Raspberry Pi**,**Allwinner Chip** (or any development board)
- STMicroelectronics MPU

## 📁 Repository Contents

- `configs/stm32mp157_defconfig` - Custom Buildroot configuration file
- `board/stm32mp157/` - Post-build scripts and board-specific data
- `README.md` - Project documentation

## 🔧 Requirements

- Linux build host (Ubuntu 20.04+ recommended)
- Git, build-essential, cpio, rsync, unzip, wget, gcc, make
- Python3, libncurses-dev, bc, etc.
- Internet access to download packages

## 🚀 Getting Started

### 1. Clone this repo and Buildroot

```bash
git clone https://github.com/buildroot/buildroot.git
cd buildroot
git checkout 2024.02  # or latest stable release
cp ../stm32mp157-buildroot/configs/stm32mp157_defconfig configs/
make stm32mp157_defconfig
```

## 🛠️ Build the Image

```bash
make -jx
```
## 📤 Output

```bash
output/images/
├── zImage                # Linux kernel
├── rootfs.ext4           # Root filesystem
├── boot.scr              # U-Boot boot script
├── sdcard.img            # Full SD card image (optional)
```
## 💽 Flash to SD Card

Insert your SD card and identify the correct device path (e.g., /dev/sdX). Then flash:

```bash
sudo dd if=output/images/sdcard.img of=/dev/sdX bs=1M status=progress
sync
```

## 🚀 Boot the STM32MP157-DK1

1-Insert the SD card.

2-Connect the USB-to-UART or HDMI display.

3-Power on the board.

4-You should see Linux boot messages.

## 📜 Post-Build Script

You can customize the root filesystem with a post-build.sh script:

```bash
#!/bin/sh
echo "Customizing root filesystem..."
cp /path/to/local/script.sh $TARGET_DIR/usr/local/bin/
chmod +x $TARGET_DIR/usr/local/bin/script.sh
```
Add this script path under System configuration → Custom scripts in make menuconfig.

## 🖼️ Screenshots (Optional)

```
U-Boot 2024.01 (Apr 29 2025 - 10:00:00 +0000)

CPU: STM32MP157C Rev.B
DRAM: 512 MiB
NAND: 0 MiB
MMC: STM32 SD/MMC: 0
In: serial
Out: serial
Err: serial
Net: No ethernet found.
Hit any key to stop autoboot: 0
Booting Linux...

Starting kernel ...

[    0.000000] Booting Linux on physical CPU 0x0
[    0.000000] Linux version 6.6.9 (buildroot@localhost) ...
[    2.123456] Freeing unused kernel memory...
[    3.456789] Welcome to Buildroot
stm32mp157 login: root
```
```
Welcome to Buildroot

stm32mp157 login: root
# uname -a
Linux buildroot 6.6.9 #1 SMP Tue Apr 29 10:00:00 UTC 2025 armv7l GNU/Linux
# df -h
Filesystem      Size  Used Avail Use% Mounted on
/dev/root        32M   15M   17M  47% /
tmpfs            64M     0   64M   0% /tmp
```
```
## 🙋 Author & Credits

Developed by Sajad Mosayebi


This project is inspired by the open-source STM32 ecosystem and Buildroot community.

Buildroot: https://buildroot.org

STM32MP1 Docs: https://wiki.st.com/stm32mpu




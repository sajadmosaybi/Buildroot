 
# README: User Access limitation

This method uses a restricted shell (rbash) + a ~/bin containing only the permitted programs (owned by root). It’s simple and robust for embedded systems.

## 🧩 Goal
---

We’ll create a user named limiteduser who:
Can only run: `ls`, `cp`, `ip`
Cannot run any other commands
Uses restricted shell (rbash)
## 1. Create the Package Directory

## 🧩 Board Used

- **STM32MP157-DK1** (or any STM32MP1-based development board)
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
Navigate to the Buildroot `package` directory and create a folder for your package:

```bash
git clone https://github.com/buildroot/buildroot.git
cd buildroot
git checkout 2024.02  # or latest stable release
cp ../stm32mp157-buildroot/configs/stm32mp157_defconfig configs/
make stm32mp157_defconfig
cd <buildroot>/package
mkdir mycustompkg
cd mycustompkg
```

## 🛠️ Build the Image
---

```bash
make
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
## 2. Create Config.in

Insert your SD card and identify the correct device path (e.g., /dev/sdX). Then flash:
Create a file named `Config.in` inside the package directory:

```bash
sudo dd if=output/images/sdcard.img of=/dev/sdX bs=1M status=progress
sync
```text
config BR2_PACKAGE_MYCUSTOMPKG
    bool "mycustompkg"
    help
      My custom package for Buildroot
```

## 🚀 Boot the STM32MP157-DK1

1-Insert the SD card.
This allows the package to appear in Buildroot's `menuconfig`.

2-Connect the USB-to-UART or HDMI display.
---

3-Power on the board.
## 3. Create the Build Script (`.mk`)

4-You should see Linux boot messages.
Create `mycustompkg.mk` in the same folder:

## 📜 Post-Build Script
```makefile
MYCUSTOMPKG_VERSION = 1.0
MYCUSTOMPKG_SITE = $(TOPDIR)/package/mycustompkg
MYCUSTOMPKG_LICENSE = GPL-2.0+
MYCUSTOMPKG_LICENSE_FILES = LICENSE

You can customize the root filesystem with a post-build.sh script:

```bash
#!/bin/sh
echo "Customizing root filesystem..."
cp /path/to/local/script.sh $TARGET_DIR/usr/local/bin/
chmod +x $TARGET_DIR/usr/local/bin/script.sh
```
Add this script path under System configuration → Custom scripts in make menuconfig.
define MYCUSTOMPKG_BUILD_CMDS
    $(MAKE) -C $(@D)
endef

## ⚙️ Customize Your Build
define MYCUSTOMPKG_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/mycustomprog $(TARGET_DIR)/usr/bin/mycustomprog
endef

```bash
make menuconfig
$(eval $(generic-package))
```

Here you can:

1-Add BusyBox utilities

2-Enable SSH (dropbear or OpenSSH)
> Replace `mycustomprog` with your actual executable or script.
3-Add Qt, Python, Node.js, or other packages
---

4-Modify root password and hostname
## 4. Add the Package to Buildroot Tree

5-Enable systemd or other init systems
Edit `package/Config.in` in Buildroot and add:

## 🧪 Debugging

```
Username: root
Password: (none)
```text
source "package/mycustompkg/Config.in"
```

## 🖼️ Screenshots (Optional)
---

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
## 🧩 Important make menuconfig Options for STM32MP157
## 5. Enable the Package in Menuconfig

### 1. Target Options
```bash
make menuconfig
```
Target Architecture          → ARM (little endian)

Target Architecture Variant → cortex-a7
Navigate to your section (e.g., **Target packages → Custom packages**) and enable **mycustompkg**.

Target ABI                  → EABIhf (hard float)
```
---

### 2. Toolchain
## 6. Build Buildroot

If you’re not using an external toolchain, use Buildroot’s:
```
Toolchain Type              → Buildroot toolchain
C library                   → glibc or musl (default: musl for size)
Enable C++ support          → [*]
```
If you want to use ST's toolchain (optional):
```
Toolchain Type              → External toolchain
Toolchain                   → Custom
Path                        → /path/to/st-toolchain
```

### 3. System Configuration
```
Root password               → (Optional) Set to "root" or leave empty
Enable root login with password → [*]
System hostname             → stm32mp157
Init system                 → busybox or systemd (default: busybox)
```
Post-build script:

```
Custom scripts to run → board/stm32mp157/post-build.sh
```
### 4. Kernel
```
Linux Kernel → [*] (enable)
  → Kernel Version        → Latest stable or specific tag (e.g., 6.6.9)
  → Kernel configuration  → Use a custom defconfig (e.g., linux-headers or stm32mp1_defconfig)
  → Kernel binary format  → zImage
  → Device Tree           → [*] stm32mp157c-dk1.dtb (or your variant)
  → Install kernel image to /boot → [*]
```
### 5. Bootloader (U-Boot)
```
Bootloaders → U-Boot → [*]
  → Board       → st/stm32mp157-dk1
  → U-Boot version → 2024.01 or latest
  → Build system  → Kconfig
```
### 6. Target Packages

Enable based on your needs. For example:
```
Networking applications → [*] dropbear (SSH server)
```
Filesystem Tools:
```
Filesystem utilities → [*] e2fsprogs, dosfstools, mtools
```
Languages / Runtime:
```
Interpreter languages and scripting → [*] Python 3.x, Lua
```
Debugging tools:
```
Debugging, profiling and benchmarking → [*] strace, gdb, ltrace
```
Other Utilities:
```
Text editors → [*] nano, vim
```
### 7. Filesystem Images
```
Filesystem images → [*] ext2/3/4 root filesystem
  → ext2/3/4 variant → ext4
  → Journaled       → [ ]
  → Image name      → rootfs.ext4
```
If you're using an SD card image:
```
SD card image → [*]
  → GPT partition table → [*]
  → Populate boot and rootfs partitions → [*]
```
### 8. Host Utilities
```
Host utilities → [*] host-genimage, host-dtc, host-pkgconf
```bash
make
```
## 🙋 Author & Credits

Developed by Sajad Mosayebi


This project is inspired by the open-source STM32 ecosystem and Buildroot community.

Buildroot: https://buildroot.org

STM32MP1 Docs: https://wiki.st.com/stm32mpu
Buildroot will build and install your package into the target root filesystem.

---

### Notes

- Ensure your package files are in the proper directory structure (`mycustompkg/Config.in` and `mycustompkg.mk`).
- You can include source files in the same directory or point to a remote site in the `.mk` file.
- This method allows full control over building, installing, and configuring custom software in Buildroot.

# Buildroot for STM32MP157

This repository contains the configuration and support files for building a custom Linux system using Buildroot for the STM32MP157-DK1 development board.

## 🧠 What is Buildroot?

[Buildroot](https://buildroot.org) is a simple, efficient, and powerful tool to generate embedded Linux systems through cross-compilation.

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

```bash
git clone https://github.com/buildroot/buildroot.git
cd buildroot
git checkout 2024.02  # or latest stable release
cp ../stm32mp157-buildroot/configs/stm32mp157_defconfig configs/
make stm32mp157_defconfig

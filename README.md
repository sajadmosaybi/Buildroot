# 🐧 Change System Hostname and System Banner in Buildroot

This document explains **how to change the system hostname and system banner** in an embedded Linux system built with **Buildroot**.
It is suitable for **BusyBox-based embedded Linux** systems such as STM32MP1, Zynq, and Raspberry Pi.

---

## ✅ Supported Platforms
- STM32MP1
- Zynq-7000
- Raspberry Pi (Buildroot)
- licheepi zero
- Any Buildroot-based embedded Linux system

---

## 📌 Definitions

### System Hostname
The hostname is the system name shown in the shell prompt:

```
root@buildroot:~#
```

### System Banner
The system banner is the message displayed **before login**, for example:

```
Welcome to Buildroot
buildroot login:
```

---

## 🛠 Method 1: Using Buildroot menuconfig (Recommended)

### 1️⃣ Open Buildroot Configuration

From the Buildroot directory:

```
make menuconfig
```

---

## 🖥 Change System Hostname

Navigate to:

```
System configuration  --->
    System hostname (buildroot)
```

Change it to your board name, for example:

```
System hostname (STM32MP1)
```

### ✅ Result After Boot

```
root@STM32MP1:~#
```

### 📁 Generated File
Buildroot automatically creates:

```
/etc/hostname
```

---

## 🖥 Change System Banner

Navigate to:

```
System configuration  --->
    System banner
```

Example banner text:

```
====================================
 Welcome to STM32MP1 Embedded Linux
 Built with Buildroot
====================================
```

### ✅ Result on Boot

```
====================================
 Welcome to STM32MP1 Embedded Linux
====================================
STM32MP1 login:
```

### 📁 Generated File
Buildroot writes the banner to:

```
/etc/issue
```

---

## 🛠 Method 2: Using Root Filesystem Overlay (Advanced)

This method is useful when you want **file-based control** and version tracking.

---

## 📁 Directory Structure

```
buildroot/
└── board/
    └── myboard/
        └── rootfs-overlay/
            └── etc/
                ├── hostname
                └── issue
```

---

## ✏️ Change Hostname via Overlay

Create the file:

```
board/myboard/rootfs-overlay/etc/hostname
```

Content:
```
STM32MP1
```

---

## ✏️ Change Banner via Overlay

Create the file:

```
board/myboard/rootfs-overlay/etc/issue
```

Example content:
```
====================================
 STM32MP1 Embedded Linux System
 Company / Project Name
====================================
```

---

## ⚙️ Enable Overlay in Buildroot

```
make menuconfig
System configuration  --->
    Root filesystem overlay directories
```

Set value:
```
board/myboard/rootfs-overlay
```

---

## 🔨 Build and Test

```
make
```

Flash and boot your target board.

---

## ⚠️ Common Mistakes

| Mistake | Correct Method |
|------|---------------|
Editing files at runtime | Use Buildroot |
Editing output/target | Use overlay |
Forgetting rebuild | Run make |

---

## 🧠 Recommendations

- Use **menuconfig** for simple projects
- Use **overlay** for production and GitHub projects
- Keep hostname short and board-specific
- Include project name and version in banner

---

## 📜 License
MIT License

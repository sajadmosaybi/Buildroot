# 🐧 Buildroot Linux Shell Prompt Configuration (PS1)
## Change Prompt Name, Colors, and Settings (BusyBox ash)

This guide explains **how to change the Linux shell prompt name and colors** in an **embedded Linux system built with Buildroot**.
It is written for **BusyBox (ash)** and is ready to use in a **GitHub repository**.

---

## ✅ Supported Targets
- STM32MP1
- Zynq-7000
- Raspberry Pi (Buildroot)
- Licheepi zero
- Any BusyBox-based embedded Linux

---

## 📌 What Is the Shell Prompt (PS1)?

Example default prompt:
```
root@buildroot:~#
```

The prompt text and colors are controlled by the environment variable **PS1**.

---

## ⚠️ Important Notes (BusyBox)
- Buildroot uses **BusyBox ash**
- `.bashrc` is **NOT used**
- Prompt must be set in:
```
/etc/profile
```

---

## ⭐ Best Practice (Recommended)

Use a **Root Filesystem Overlay** so changes are permanent and version-controlled.

❌ Do NOT edit:
```
output/target/etc/profile
```

---

## 📁 Directory Structure

```
buildroot/
└── board/
    └── myboard/
        └── rootfs-overlay/
            └── etc/
                └── profile
```

---

## 🛠 Step-by-Step Configuration

### 1️⃣ Create Rootfs Overlay
```
mkdir -p board/myboard/rootfs-overlay/etc
```

---

### 2️⃣ Create `/etc/profile`
```
nano board/myboard/rootfs-overlay/etc/profile
```

---

## ✏️ Change Prompt Name (Basic)

```
export PS1="MyLinux:\W# "
```

Result:
```
MyLinux:~#
```

---

## 🧩 PS1 Variables

| Symbol | Meaning |
|------|--------|
| \u | Username |
| \h | Hostname |
| \w | Full path |
| \W | Current directory |
| \$ | # (root) or $ (user) |
| \t | Time |
| \d | Date |

---

## 🎨 Color Configuration

### ⚠️ Color Rules (Very Important)
- Always wrap colors with `\[` and `\]`
- Always reset color at the end
- Use ANSI escape codes

---

### 🎨 ANSI Text Colors

| Color | Code |
|----|----|
| Black | 30 |
| Red | 31 |
| Green | 32 |
| Yellow | 33 |
| Blue | 34 |
| Magenta | 35 |
| Cyan | 36 |
| White | 37 |

---

### 🎨 Background Colors

| Color | Code |
|----|----|
| Black | 40 |
| Red | 41 |
| Green | 42 |
| Yellow | 43 |
| Blue | 44 |

---

## 🧪 Prompt Examples

### 🟢 Green Prompt
```
export PS1="\[\e[32m\]MyLinux:\W# \[\e[0m\]"
```

---

### 🔵 Username + Hostname (Blue)
```
export PS1="\[\e[34m\][\u@\h \W]# \[\e[0m\]"
```

---

### 🟡 Embedded Board Name (Yellow)
```
export PS1="\[\e[33m\]STM32MP1\[\e[0m\]:\W# "
```

---

### 🎯 Professional Multi-Color Prompt
```
export PS1="\[\e[32m\]\u\[\e[0m\]@\[\e[34m\]\h\[\e[0m\]:\[\e[36m\]\W\[\e[0m\]# "
```

---

## 📄 Full `/etc/profile` Example

```
#!/bin/sh

echo "Welcome to My Embedded Linux System"

export PS1="\[\e[36m\]MyBoard[\u@\h:\W]# \[\e[0m\]"
```

---

## ⚙️ Enable Overlay in Buildroot

```
make menuconfig
System configuration  --->
Root filesystem overlay directories
board/myboard/rootfs-overlay
```

---

## 🔨 Build and Run

```
make
```

Flash and boot your target board.

---

## ❌ Common Mistakes

| Mistake | Fix |
|------|----|
Editing output files | Use overlay |
Using .bashrc | Use /etc/profile |
Broken colors | Add \[ \] |
No rebuild | Run make |

---

## 📜 License
MIT License

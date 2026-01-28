# 🚀 Embedded Linux Auto Login  
### Using **Buildroot + BusyBox (`inittab`)**

---

## 🌟 Why Auto Login?

In many **embedded Linux systems**, you don’t want a login screen.  
You want the device to:

➡️ Power ON  
➡️ Boot Linux  
➡️ Drop **directly into a shell or application**  

That’s exactly what **auto-login** does.

---

## 📁 Configuration File

🗂 **BusyBox init configuration file:**

```bash
/ etc / inittab
```

📍 In Buildroot build output:

```bash
output/target/etc/inittab
```

---

## 🔐 Default Behavior (Login Required)

By default, Buildroot launches `getty`, which shows a login prompt:

```ini
ttyS0::respawn:/sbin/getty -L tty1 0 vt100
```

❌ Requires username & password

---

## ✨ Enable Auto Login (Recommended)

### 🛠️ Step 1: Edit `inittab`

Replace the `getty` line with:

```ini
ttyS0::respawn:/bin/login
```

### ✅ Result

✔ No `login:` prompt  
✔ Automatic **root** shell  
✔ Perfect for embedded boards

---

## 🖥️ Best Practice: Bind Shell to Console

For a stable terminal experience, use:

```ini
ttyS0::respawn:/bin/login < /dev/ttyS0 > /dev/ttyS0 2>&1
```

📌 Ensures correct input/output on `tty1`

---

## 🔁 Alternative: Auto Login Using `getty`

BusyBox supports auto-login via `getty`:

```ini
tty1::respawn:/sbin/getty -a root tty1
```

🟢 Keeps `getty`  
🟢 Auto-login as `root`  
🟢 No password required

---

## 📦 Root Filesystem Overlay (⭐ Best Way)

To make changes **persistent** across builds:

```text
board/myboard/rootfs_overlay/
└── etc/
    └── inittab
```

📥 Buildroot will copy this automatically during build.

---

## ⚠️ Security Warning

🚨 **Auto-login as root is NOT secure for production systems**

✔ OK for:
- Development boards
- Lab environments
- Offline embedded devices

❌ Avoid for:
- Network-connected products
- Commercial devices

---

## 🧪 Verify Auto Login

After boot, you should see:

```bash
#
```

Check current user:

```bash
whoami
```

Output:

```text
root
```

---

## 📊 Quick Summary

| 🔧 Action | 🎯 Outcome |
|---------|-----------|
Replace `getty` | Instant auto-login |
Bind `/dev/ttyS0` | Stable console |
Use overlay | Permanent config |

---

## 🎉 Done!

Your embedded Linux system now boots **clean, fast, and password-free** 🚀  
Perfect for demos, labs, and embedded products.

---

🧠 *Simple configuration. Professional result.*

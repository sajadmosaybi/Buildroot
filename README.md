# Restricted User Setup in BusyBox-Based Embedded Linux

This guide explains how to create a restricted user in a **Buildroot BusyBox**-based Embedded Linux system that can **only run** the commands `ls`, `cp`, and `ip`, without using `useradd`.

---

## 🧩 Goal
Create a user named `limiteduser` who:
- Can **only** run `ls`, `cp`, and `ip`
- Cannot run other commands
- Uses a **restricted shell** (`rbash`)

---

## 🪜 Step-by-Step Instructions

### 🥇 Step 1 — Check required commands
Verify that `ls`, `cp`, and `ip` exist:
```bash
ls /bin/ls /bin/cp /sbin/ip /bin/ip
```
You should see something like `/bin/ls`, `/bin/cp`, `/sbin/ip`.

If not, reconfigure Buildroot to include them.

---

### 🥈 Step 2 — Create `/bin/rbash`
Check for `bash`:
```bash
ls /bin/bash
```
If it exists:
```bash
ln -sf /bin/bash /bin/rbash
```
If `bash` does **not** exist, use BusyBox shell:
```bash
ln -sf /bin/sh /bin/rbash
```

---

### 🥉 Step 3 — Add the user manually
Since `useradd` is not available, edit `/etc/passwd` directly.

Append this line:
```
limiteduser:x:1001:1001::/home/limiteduser:/bin/rbash
```

You can do it via:
```bash
echo "limiteduser:x:1001:1001::/home/limiteduser:/bin/rbash" >> /etc/passwd
```

---

### 🧰 Step 4 — Create home and bin directories
```bash
mkdir -p /home/limiteduser/bin
```

---

### 🪞 Step 5 — Link only allowed commands
```bash
ln -sf /bin/ls /home/limiteduser/bin/ls
ln -sf /bin/cp /home/limiteduser/bin/cp
ln -sf /sbin/ip /home/limiteduser/bin/ip   # or /bin/ip if that's where it is
```

---

### 🔒 Step 6 — Lock down permissions
```bash
chown -R root:root /home/limiteduser/bin
chmod 755 /home/limiteduser/bin
```

---

### 🧱 Step 7 — Create restricted environment file
Create `/home/limiteduser/.profile`:
```bash
cat > /home/limiteduser/.profile <<'EOF'
# Restricted user environment
PATH=/home/limiteduser/bin
export PATH
unset HISTFILE
EOF
```

Protect it:
```bash
chown root:root /home/limiteduser/.profile
chmod 644 /home/limiteduser/.profile
```

---

### ✅ Step 9 — Test the setup
Switch to the user:
```bash
su - limiteduser
```
Try:
```bash
ls
cp
ip addr
```
✅ These should work.

Then try:
```bash
ps
cd /
/bin/sh
```
❌ These should fail or show restriction messages.

---

## ✅ Result
You now have a **restricted BusyBox user** who can only execute:
```
ls, cp, ip
```

---
.

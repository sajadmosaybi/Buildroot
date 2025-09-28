# README: Adding a Custom Package in Buildroot

This README explains how to add a custom package to **Buildroot** so it appears in **menuconfig** and is built into the target filesystem.

---

## 1. Create the Package Directory

Navigate to the Buildroot `package` directory and create a folder for your package:

```bash
cd <buildroot>/package
mkdir mycustompkg
cd mycustompkg
```

---

## 2. Create Config.in

Create a file named `Config.in` inside the package directory:

```text
config BR2_PACKAGE_MYCUSTOMPKG
    bool "mycustompkg"
    help
      My custom package for Buildroot
```

This allows the package to appear in Buildroot's `menuconfig`.

---

## 3. Create the Build Script (`.mk`)

Create `mycustompkg.mk` in the same folder:

```makefile
MYCUSTOMPKG_VERSION = 1.0
MYCUSTOMPKG_SITE = $(TOPDIR)/package/mycustompkg
MYCUSTOMPKG_LICENSE = GPL-2.0+
MYCUSTOMPKG_LICENSE_FILES = LICENSE

define MYCUSTOMPKG_BUILD_CMDS
    $(MAKE) -C $(@D)
endef

define MYCUSTOMPKG_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/mycustomprog $(TARGET_DIR)/usr/bin/mycustomprog
endef

$(eval $(generic-package))
```

> Replace `mycustomprog` with your actual executable or script.

---

## 4. Add the Package to Buildroot Tree

Edit `package/Config.in` in Buildroot and add:

```text
source "package/mycustompkg/Config.in"
```

---

## 5. Enable the Package in Menuconfig

```bash
make menuconfig
```

Navigate to your section (e.g., **Target packages → Custom packages**) and enable **mycustompkg**.

---

## 6. Build Buildroot

```bash
make
```

Buildroot will build and install your package into the target root filesystem.

---

### Notes

- Ensure your package files are in the proper directory structure (`mycustompkg/Config.in` and `mycustompkg.mk`).
- You can include source files in the same directory or point to a remote site in the `.mk` file.
- This method allows full control over building, installing, and configuring custom software in Buildroot.

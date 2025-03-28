# Part I. Getting started
## About Buildroot
Buildroot is a tool that simplifies and automates the process of building a complete Linux system for an embedded system, using cross-compilation.

In order to achieve this, Buildroot is able to generate a cross-compilation toolchain, a root filesystem, a Linux kernel image and a bootloader for your target. Buildroot can be used for any combination of these options, independently (you can for example use an existing cross-compilation toolchain, and build only your root filesystem with Buildroot).

Buildroot is useful mainly for people working with embedded systems. Embedded systems often use processors that are not the regular x86 processors everyone is used to having in his PC. They can be PowerPC processors, MIPS processors, ARM processors, etc.

Buildroot supports numerous processors and their variants; it also comes with default configurations for several boards available off-the-shelf. Besides this, a number of third-party projects are based on, or develop their BSP [1] or SDK [2] on top of Buildroot.
## System requirements
Buildroot is designed to run on Linux systems.

While Buildroot itself will build most host packages it needs for the compilation, certain standard Linux utilities are expected to be already installed on the host system. Below you will find an overview of the mandatory and optional packages (note that package names may vary between distributions)
## Mandatory packages
```which, sed, make (version 3.81 or any later), binutils, build-essential (only for Debian based systems), diffutils, gcc (version 4.8 or any later), g++ (version 4.8 or any later), bash, patch, gzip, bzip2, perl (version 5.8.7 or any later), tar, cpio, unzip, rsync, file (must be in /usr/bin/file), bc,findutils, wget```
## Optional packages
```python (version 2.7 or any later), ncurses5 to use the menuconfig interface, qt5 to use the xconfig interface, glib2, gtk2 and glade2 to use the gconfig interface, bazaar, curl, cvs, git, mercurial, scp, sftp, subversion```
## Getting Buildroot
```git clone -b master https://github.com/buildroot/buildroot.git```
# Part II: Buildroot quick start
**Important**: you can and should **build everything as a normal user**. There is no need to be root to configure and use Buildroot. By running all commands as a regular user, you protect your system against packages behaving badly during compilation and installation.

The first step when using Buildroot is to create a configuration. Buildroot has a nice configuration tool similar to the one you can find in the [Linux kernel](https://www.kernel.org) or in [BusyBox](https://busybox.net).

From the buildroot directory, run

```$ make menuconfig```

for the original curses-based configurator, or

```$ make nconfig```

for the new curses-based configurator, or

```$ make xconfig```

for the Qt-based configurator, or

```$ make gconfig```

Once everything is configured, the configuration tool generates a .config file that contains the entire configuration. This file will be read by the top-level Makefile.

To start the build process, simply run:

```$ make```


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

From the buildroot directory, run<br />
```$ make menuconfig```

for the original curses-based configurator, or<br />
```$ make nconfig```

for the new curses-based configurator, or<br />
```$ make xconfig```

for the Qt-based configurator, or<br />
```$ make gconfig```

Once everything is configured, the configuration tool generates a .config file that contains the entire configuration. This file will be read by the top-level Makefile.

To start the build process, simply run:<br />
```$ make```

By default, Buildroot does not support top-level parallel build, so running ```make -jN ```is not necessary. Buildroot has always been capable of using parallel build on a per package basis: each package is built by Buildroot using ```make -jN``` (or the equivalent invocation for non-make-based build systems). The level of parallelism is by default number of CPUs + 1, but it can be adjusted using the ```BR2_JLEVEL``` configuration option.

The ```make``` command will generally perform the following steps:

- download source files (as required).<br />
- configure, build and install the cross-compilation toolchain, or simply import an external toolchain.<br />
- configure, build and install selected target packages.<br />
- build a kernel image, if selected.<br />
- build a bootloader image, if selected.<br />
- create a root filesystem in selected formats.

Buildroot output is stored in a single directory, output/. This directory contains several subdirectories:

- $${\color{blue}images/}$$ where all the images (kernel image, bootloader and root filesystem images) are stored. These are the files you need to put on your target system.
- $${\color{blue}build/}$$  where all the components are built (this includes tools needed by Buildroot on the host and packages compiled for the target). This directory contains one subdirectory for each of these components.
- $${\color{blue}host/}$$ contains both the tools built for the host, and the sysroot of the target toolchain. The former is an installation of tools compiled for the host that are needed for the proper execution of Buildroot, including the cross-compilation toolchain. The latter is a hierarchy similar to a root filesystem hierarchy. It contains the headers and libraries of all user-space packages that provide and install libraries used by other packages. However, this directory is not intended to be the root filesystem for the target: it contains a lot of development files, unstripped binaries and libraries that make it far too big for an embedded system. These development files are used to compile libraries and applications for the target that depend on other libraries.
- $${\color{blue}staging/}$$ is a symlink to the target toolchain sysroot inside host/, which exists for backwards compatibility.
- $${\color{blue}target/}$$ which contains almost the complete root filesystem for the target: everything needed is present except the device files in /dev/ (Buildroot can’t create them because Buildroot doesn’t run as root and doesn’t want to run as root). Also, it doesn’t have the correct permissions (e.g. setuid for the busybox binary). Therefore, this directory should not be used on your target. Instead, you should use one of the images built in the images/ directory. If you need an extracted image of the root filesystem for booting over NFS, then use the tarball image generated in images/ and extract it as root. Compared to staging/, target/ contains only the files and libraries needed to run the selected target applications: the development files (headers, etc.) are not present, the binaries are stripped.

These commands, ```make menuconfig|nconfig|gconfig|xconfig``` and make, are the basic ones that allow to easily and quickly generate images fitting your needs, with all the features and applications you enabled.
 

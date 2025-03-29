# Part I. Getting started
## About Buildroot
<p align="justify">Buildroot is a tool that simplifies and automates the process of building a complete Linux system for an embedded system, using cross-compilation.</p>

<p align="justify">In order to achieve this, Buildroot is able to generate a cross-compilation toolchain, a root filesystem, a Linux kernel image and a bootloader for your target. Buildroot can be used for any combination of these options, independently (you can for example use an existing cross-compilation toolchain, and build only your root filesystem with Buildroot).</p>

<p align="justify">Buildroot is useful mainly for people working with embedded systems. Embedded systems often use processors that are not the regular x86 processors everyone is used to having in his PC. They can be PowerPC processors, MIPS processors, ARM processors, etc.</p>

<p align="justify">Buildroot supports numerous processors and their variants; it also comes with default configurations for several boards available off-the-shelf. Besides this, a number of third-party projects are based on, or develop their BSP [1] or SDK [2] on top of Buildroot.</p>

## System requirements
Buildroot is designed to run on Linux systems.

<p align="justify">While Buildroot itself will build most host packages it needs for the compilation, certain standard Linux utilities are expected to be already installed on the host system. Below you will find an overview of the mandatory and optional packages (note that package names may vary between distributions)</p>

## Mandatory packages
```which, sed, make (version 3.81 or any later), binutils, build-essential (only for Debian based systems), diffutils, gcc (version 4.8 or any later), g++ (version 4.8 or any later), bash, patch, gzip, bzip2, perl (version 5.8.7 or any later), tar, cpio, unzip, rsync, file (must be in /usr/bin/file), bc,findutils, wget```
## Optional packages
```python (version 2.7 or any later), ncurses5 to use the menuconfig interface, qt5 to use the xconfig interface, glib2, gtk2 and glade2 to use the gconfig interface, bazaar, curl, cvs, git, mercurial, scp, sftp, subversion```
## Getting Buildroot
```git clone -b master https://github.com/buildroot/buildroot.git```
# Part II: Buildroot quick start
**<p align="justify">Important**: you can and should **build everything as a normal user**. There is no need to be root to configure and use Buildroot. By running all commands as a regular user, you protect your system against packages behaving badly during compilation and installation.</p>

<p align="justify">The first step when using Buildroot is to create a configuration. Buildroot has a nice configuration tool similar to the one you can find in the [Linux kernel](https://www.kernel.org) or in [BusyBox](https://busybox.net).</p>

From the buildroot directory, run<br />
```$ make menuconfig```

for the original curses-based configurator, or<br />
```$ make nconfig```

for the new curses-based configurator, or<br />
```$ make xconfig```

for the Qt-based configurator, or<br />
```$ make gconfig```

<p align="justify">Once everything is configured, the configuration tool generates a .config file that contains the entire configuration. This file will be read by the top-level Makefile.</p>

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

- <p align="justify">$${\color{blue}images/}$$ where all the images (kernel image, bootloader and root filesystem images) are stored. These are the files you need to put on your target system.</p>
- <p align="justify">$${\color{blue}build/}$$ where all the components are built (this includes tools needed by Buildroot on the host and packages compiled for the target). This directory contains one subdirectory for each of these components.</p>
- <p align="justify">$${\color{blue}host/}$$ contains both the tools built for the host, and the sysroot of the target toolchain. The former is an installation of tools compiled for the host that are needed for the proper execution of Buildroot, including the cross-compilation toolchain. The latter is a hierarchy similar to a root filesystem hierarchy. It contains the headers and libraries of all user-space packages that provide and install libraries used by other packages. However, this directory is not intended to be the root filesystem for the target: it contains a lot of development files, unstripped binaries and libraries that make it far too big for an embedded system. These development files are used to compile libraries and applications for the target that depend on other libraries.</p>
- $${\color{blue}staging/}$$ is a symlink to the target toolchain sysroot inside host/, which exists for backwards compatibility.
- <p align="justify">$${\color{blue}target/}$$ which contains almost the complete root filesystem for the target: everything needed is present except the device files in /dev/ (Buildroot can’t create them because Buildroot doesn’t run as root and doesn’t want to run as root). Also, it doesn’t have the correct permissions (e.g. setuid for the busybox binary). Therefore, this directory should not be used on your target. Instead, you should use one of the images built in the images/ directory. If you need an extracted image of the root filesystem for booting over NFS, then use the tarball image generated in images/ and extract it as root. Compared to staging/, target/ contains only the files and libraries needed to run the selected target applications: the development files (headers, etc.) are not present, the binaries are stripped.</p>

These commands, ```make menuconfig|nconfig|gconfig|xconfig``` and make, are the basic ones that allow to easily and quickly generate images fitting your needs, with all the features and applications you enabled.

# Part III: Buildroot configuration
All the configuration options in ```make *config``` have a help text providing details about the option.

The make ```*config``` commands also offer a search tool. Read the help message in the different frontend menus to know how to use it:

- in ```menuconfig```, the search tool is called by pressing ```/```;
- in ```xconfig```, the search tool is called by pressing ```Ctrl + f```.

## Cross-compilation toolchain<br />
A compilation toolchain is the set of tools that allows you to compile code for your system. It consists of a compiler (in our case, ```gcc)```, binary utils like assembler and linker (in our case, ```binutils```) and a C standard library (for example GNU Libc, uClibc-ng).<br />
Toolchain Directory: ```/Buildroot/output/host/bin```.

## make tips<br />
This is a collection of tips that help you make the most of Buildroot.<br />
Display all commands executed by make: ```$ make V=1 <target>```.<br />
Display the list of boards with a defconfig: ```$ make list-defconfigs```.<br />
Display all available targets: ```$ make help```.<br />
Not all targets are always available, some settings in the .config file may hide some targets:<br />
- ```busybox-menuconfig``` only works when busybox is enabled;
- ```linux-menuconfig``` and ```linux-savedefconfig``` only work when linux is enabled;
- ```uclibc-menuconfig``` is only available when the uClibc C library is selected in the internal toolchain backend;
- ```barebox-menuconfig``` and ```barebox-savedefconfig``` only work when the barebox bootloader is enabled.
- ```uboot-menuconfig``` and ```uboot-savedefconfig``` only work when the U-Boot bootloader is enabled and the uboot build system is set to Kconfig.

To delete all build products (including build directories, host, staging and target trees, the images and the toolchain):<br />
```$ make clean```<br />
Generating the manual: The present manual sources are located in the docs/manual directory. To generate the manual:<br />
```$ make manual-clean```<br />
```$ make manual```<br />
Resetting Buildroot for a new target: To delete all build products as well as the configuration: ```$ make distclean```<br />
<p align="justify">Generally speaking, when you’re facing a build error and you’re unsure of the potential consequences of the configuration changes you’ve made, do a full rebuild. If you get the same build error, then you are sure that the error is not related to partial rebuilds of packages, and if this error occurs with packages from the official Buildroot, do not hesitate to report the problem! As your experience with Buildroot progresses, you will progressively learn when a full rebuild is really necessary, and you will save more and more time.</p>

```$ make clean all```

## Offline builds<br />
<p align="justify">If you intend to do an offline build and just want to download all sources that you previously selected in the configurator (menuconfig, nconfig, xconfig or gconfig), then issue:</p>

```$ make source```



 

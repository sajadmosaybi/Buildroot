# README: Adding a Custom U-Boot Command

This repository demonstrates how to add a custom command to **U-Boot** and integrate it with **menuconfig** so it can be enabled or disabled during build.

---

## 1. Create the Command Source File

Create `cmd_mycommand.c` inside the `cmd/` directory:

```c
#include <common.h>
#include <command.h>

static int do_mycommand(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    printf("Hello from my custom command!\n");
    return 0;
}

/* Register the command with U-Boot */
U_BOOT_CMD(
    mycommand,   // Command name
    1,           // Max number of arguments
    1,           // Repeatable
    do_mycommand,// Function pointer
    "My custom command", // Short help
    "mycommand - prints a greeting" // Long help
);
```

---

## 2. Add a Kconfig Entry

Add a Kconfig option for your command. Edit `cmd/Kconfig` or the appropriate file:

```text
config CMD_MYCOMMAND
    bool "Enable mycommand"
    default y
    help
      Enable the 'mycommand' command in U-Boot.
```

---

## 3. Update the Makefile

Edit the `cmd/Makefile` to include your file conditionally:

```makefile
obj-$(CONFIG_CMD_MYCOMMAND) += cmd_mycommand.o
```

---

## 4. Enable the Command in Menuconfig

Run:

```bash
make menuconfig
```

Navigate to **Commands → Custom Commands** (or the relevant section) and enable **mycommand**.

---

## 5. Build U-Boot

```bash
make CROSS_COMPILE=<your-toolchain-prefix> <board>_defconfig
make CROSS_COMPILE=<your-toolchain-prefix> -j$(nproc)
```

Replace `<your-toolchain-prefix>` with your cross-compiler prefix, e.g., `arm-none-eabi-`.

---

## 6. Test the Command

After flashing U-Boot, test your command at the prompt:

```bash
=> mycommand
Hello from my custom command!
```

---

### Notes

- Ensure the `.c` file, Kconfig, and Makefile modifications are placed in the correct folders.
- You can toggle the command on/off using `menuconfig` without modifying the source code each time.

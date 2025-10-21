
# STM32MP157A-DK1 Custom U-Boot Command: `myconfig`

This project demonstrates how to add a custom U-Boot command on the STM32MP157A-DK1 board to **set IP, server IP, MAC address dynamically, and ping a server**.

## Features

- Set IP, server IP, and MAC address dynamically via U-Boot command arguments.
- Works without overwriting type-checked U-Boot variables.
- Pings the specified server to verify connectivity.

## Prerequisites

- STM32MP157A-DK1 board
- U-Boot source code (e.g., version 2021.10)
- Buildroot environment for STM32MP1
- Basic knowledge of U-Boot build and flash process

## Step 1: Add Custom Command Source File

Create a file `cmd_myconfig.c` in the `cmd/` directory of U-Boot:

```c
#include <common.h>
#include <command.h>
#include <net.h>

int do_myconfig(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    /* Set IP address */
    env_set("ipaddr", "IP");   // replace with your desired IP
    env_set("serverip", "server IP");   // replace with your server IP
    env_set("ethaddr", "MAC"); // replace with your MAC

    printf("IP: %s\n", env_get("ipaddr"));
    printf("Server IP: %s\n", env_get("serverip"));
    printf("MAC: %s\n", env_get("ethaddr"));

    /* Ping the server */
    printf("Pinging server...\n");
    if (ping(get_server_ip(), 1) == 0) {
        printf("Ping success!\n");
    } else {
        printf("Ping failed!\n");
    }

    return 0;
}

/* Register the command */
U_BOOT_CMD(
    myconfig,    /* name */
    1,           /* max args */
    0,           /* repeatable */
    do_myconfig, /* command function */
    "Set IP, server IP, MAC and ping", /* description */
    ""
);
```

## Step 2: Build U-Boot

```bash
make stm32mp157a_dk1_defconfig
make -j$(nproc)
```

## Step 3: Flash U-Boot to STM32MP157A-DK1

- Follow your normal method (SD card, eMMC, or ST-Link) to flash the new U-Boot binary.

## Step 4: Usage

Boot into U-Boot and run:

```bash
=> myconfig 192.168.100.180 192.168.100.1 00:11:22:33:44:55
```

- Sets the IP, server IP, and MAC using your inputs.
- Pings the server IP to verify connectivity.

## Notes

- Do not overwrite default type-checked variables (`ipaddr`, `serverip`, `ethaddr`) directly; use custom variables instead.
- `ethaddr` must be set if not already configured; otherwise, Ethernet will not initialize.
- You can modify the command to add DHCP initialization or static network setup as needed.

## License

MIT License

# Embedded CLI Shell for STM32MP157A (Buildroot + BusyBox)

This project provides a lightweight **Command Line Interface (CLI) shell** written in **C** for the **STM32MP157A-DK1** development board running **Linux built with Buildroot**.  
It replaces the standard Linux shell (bash/sh) with a custom user-defined shell that allows only specific commands and restricts system access.

---
## CLI C Code
```bash
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CMD_LEN 128

void print_help(void) {
    printf("\nAvailable commands:\n");
    printf("  help        - Show this help message\n");
    printf("  clear       - Clear screen\n");
    printf("  ls          - List files in current directory\n");
    printf("  cat <file>  - Display file contents\n");
    printf("  ps          - Show running processes\n");
    printf("  reboot      - Reboot the system\n");
    printf("  led_on      - Turn LED on (example)\n");
    printf("  led_off     - Turn LED off (example)\n");
    printf("  exit        - Exit shell (restarts if respawned)\n");
    printf("\n");
}

void execute_linux_command(const char *cmd) {
    int ret = system(cmd);
    if (ret == -1)
        perror("system");
}

int main(void) {
    char cmdline[MAX_CMD_LEN];
    char *cmd;
    char *arg;

    printf("=====================================\n");
    printf("  Embedded CLI Shell - STM32MP157A\n");
    printf("=====================================\n");
    printf("Type 'help' to see available commands.\n\n");

    while (1) {
        printf("stm32> ");
        fflush(stdout);

        if (fgets(cmdline, sizeof(cmdline), stdin) == NULL) {
            printf("\n");
            break;
        }

        // Remove newline
        cmdline[strcspn(cmdline, "\r\n")] = '\0';

        if (strlen(cmdline) == 0)
            continue;

        // Split command and argument
        cmd = strtok(cmdline, " ");
        arg = strtok(NULL, "");

        // Built-in commands
        if (strcmp(cmd, "help") == 0) {
            print_help();
        } else if (strcmp(cmd, "clear") == 0) {
            printf("\033[2J\033[H");  // ANSI clear screen
        } else if (strcmp(cmd, "ls") == 0) {
            execute_linux_command("ls");
        } else if (strcmp(cmd, "cat") == 0) {
            if (arg) {
                char command[MAX_CMD_LEN + 10];
                snprintf(command, sizeof(command), "cat %s", arg);
                execute_linux_command(command);
            } else {
                printf("Usage: cat <filename>\n");
            }
        } else if (strcmp(cmd, "ps") == 0) {
            execute_linux_command("ps");
        } else if (strcmp(cmd, "reboot") == 0) {
            printf("Rebooting...\n");
            execute_linux_command("reboot");
        } else if (strcmp(cmd, "led_on") == 0) {
            printf("Turning LED on...\n");
            system("echo 1 > /sys/class/leds/led0/brightness 2>/dev/null");
        } else if (strcmp(cmd, "led_off") == 0) {
            printf("Turning LED off...\n");
            system("echo 0 > /sys/class/leds/led0/brightness 2>/dev/null");
        } else if (strcmp(cmd, "exit") == 0) {
            printf("Exiting shell...\n");
            break;
        } else {
            printf("Unknown command: %s\n", cmd);
        }
    }

    return 0;
}

```
## 🧩 Features

- Runs automatically on boot via serial console (`ttySTM0`)
- Provides a restricted, user-friendly CLI
- Supports common Linux commands:
  - `ls`, `cat <file>`, `ps`, `reboot`
- Includes user-defined commands:
  - `led_on`, `led_off`
- Built-in commands:
  - `help`, `clear`, `exit`
- Prevents user access to bash or other shells
- Simple, clean C implementation (no external libraries)

---

## 🛠️ Requirements

- STM32MP157A-DK1 board  
- Buildroot (tested with 2024.x)  
- BusyBox init system (default in Buildroot)  
- UART serial console (e.g., `/dev/ttySTM0` at 115200 baud)

---

## 📁 Project Structure

```
embedded_shell/
├── Config.in
├── embedded_shell.c
└── embedded_shell.mk
```

---

## ⚙️ Build Instructions

### 1️⃣ Add to Buildroot

Copy this folder into your Buildroot tree:
```
buildroot/package/embedded_shell/
```

Then add it to Buildroot’s configuration:

```bash
make menuconfig
```

Go to:
```
Target packages → Misc → [*] embedded_shell
```

Save and exit.

---

### 2️⃣ Build the System

Run:
```bash
make
```

After the build completes, the binary will be installed at:
```
/usr/bin/embedded_shell
```

---

### 3️⃣ Auto-start on Boot

Edit your Buildroot overlay or root filesystem file `/etc/inittab`:

Find this line:
```
ttySTM0::respawn:/sbin/getty -L ttySTM0 115200 vt100
```

Replace it with:
```
ttySTM0::respawn:/usr/bin/embedded_shell
```

This ensures that when the board boots and the serial console opens, your CLI runs directly — without login or access to the standard Linux shell.

---

## ▶️ Usage Example

When you power up and connect via serial (115200 baud), you’ll see:

```
=====================================
  Embedded CLI Shell - STM32MP157A
=====================================
Type 'help' to see available commands.

stm32>
```

### Available Commands

| Command | Description |
|----------|-------------|
| `help` | Show list of available commands |
| `clear` | Clear the terminal screen |
| `ls` | List files in current directory |
| `cat <file>` | Display file contents |
| `ps` | Show running processes |
| `reboot` | Reboot the system |
| `led_on` | Turn on LED (example using sysfs) |
| `led_off` | Turn off LED |
| `exit` | Exit shell (if `respawn:` in inittab, it restarts) |

---

## 🔒 Security

To limit access to the standard shell:
- Disable `login` and `bash` in Buildroot (`make menuconfig`)
- Ensure `/bin/sh` is not accessible
- Configure `/etc/inittab` to run only this CLI

This ensures that users interacting over UART can **only** use your restricted CLI.

---

## 🧰 Future Enhancements

- Command history and arrow key navigation (via `linenoise`)
- Tab auto-completion
- Custom hardware control commands (GPIO, I2C, etc.)
- Ethernet or UART remote CLI interface

---

## 🧑‍💻 Author

**Sajad Mosayebi**  
Embedded Systems Engineer  
📧 Smosaybi@gmail.com 

---

## 📄 License

This project is licensed under the **MIT License** — you are free to use, modify, and distribute it with attribution.

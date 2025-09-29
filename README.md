# My Startup Program

This repository contains a program/script that can run automatically on Linux startup.

## Features

- Auto-run on system boot using **systemd** (if available)
- Logs output to a file for monitoring
- Works with both Bash scripts and compiled C programs

## Files

- `myscript.sh` — Example Bash script
- `myscript.c` — Example C program (requires compilation)
- `myscript.service` — systemd service file for auto-start

## Installation

### 1. Bash Script

Make the script executable:

```bash
chmod +x myscript.sh
```

### 2. C Program

Compile the C program:

```bash
gcc -o myscript myscript.c
chmod +x myscript
```

## Auto-run with systemd

1. Copy the service file:

```bash
sudo cp myscript.service /etc/systemd/system/myscript.service
```

2. Reload systemd:

```bash
systemctl daemon-reload
```

3. Enable the service at boot:

```bash
systemctl enable myscript.service
```

4. Start the service immediately (optional):

```bash
systemctl start myscript.service
```

5. Check status:

```bash
systemctl status myscript.service
```

6. View logs:

```bash
journalctl -u myscript.service -f
```


## License

This project is licensed under the MIT License.

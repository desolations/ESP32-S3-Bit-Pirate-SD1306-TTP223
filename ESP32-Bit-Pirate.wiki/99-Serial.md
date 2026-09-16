# Serial Connection Guide

This guide explains how to connect to the ESP32 Bit Pirate using a serial terminal on your computer.  
Whether you're using Windows, macOS, or Linux, several tools are available to open a serial port and interact with the CLI.

---

## Web Serial Terminal

The Web Serial Terminal provides direct access to the Serial CLI from a compatible browser, without installing PuTTY, minicom, or another terminal application.

- [Open the ESP32 Bit Pirate Web Tools](https://geo-tp.github.io/ESP32-Bit-Pirate/web-tools/)
<img width="600" alt="ESP32 Bit Pirate Web Serial Tools" src="https://github.com/user-attachments/assets/d39d008e-62a7-4e3f-a878-a45b91fc7e41" />




The terminal communicates directly with the device through USB and behaves like a regular serial terminal, with support for interactive commands, keyboard shortcuts, copy and paste, and ANSI terminal output.

If the port does not appear, verify that the board exposes a USB CDC serial interface and that the correct USB connector is being used.

---

## 🪟 Windows

### 🔁 Find the COM port
Open Device Manager and look under Ports (COM & LPT).
You’ll see something like:

``USB Serial Device (COM3)``

If you're using M5Burner, plug in the device while M5Burner is open — the COM port will appear automatically when the board is connected.

### ✅ Recommended: [**PuTTY**](https://www.putty.org/)
- Free, open-source, lightweight.
- Supports serial (COMx) mode easily.
- Simple raw text display for command-line interaction.

<img width="900" alt="capturewindowsputty" src="https://github.com/user-attachments/assets/e851710a-8243-4410-b51b-d1228d37eec2" />
<img width="900" alt="Captureputty2" src="https://github.com/user-attachments/assets/77f447fd-2b84-47f6-ae60-e86c2d8b9a6d" />


### 🔄 Alternatives:
- [**CoolTerm**](https://freeware.the-meiers.org/) — Visual, easy to configure.
- [**RealTerm**](https://realterm.sourceforge.net/) — Advanced features, older UI.
- [**YAT (Yet Another Terminal)**](https://sourceforge.net/projects/y-a-terminal/) — Clean and MCU-friendly.

---

## 🍎 macOS

### 🔁 Find the COM port

In a terminal, run:

```bash
ls /dev/tty.usb*
```

You may see something like:

```bash
/dev/tty.usbserial-0001
```
If you're using M5Burner, plug in the device while M5Burner is open — the USB interface will appear automatically when the board is connected.

### ✅ Recommended: [**CoolTerm**](https://freeware.the-meiers.org/)
- Auto-detects USB serial ports (CH340, CP210x, FTDI, etc.).
- Friendly interface and customizable.

### 🔄 Alternatives:
- **screen** in terminal:
  ```bash
  screen /dev/tty.usbserial-XXXX 115200
  ```

---

## 🐧 Linux

### 🔁 Find the COM port
In a terminal, run:

```bash
ls /dev/ttyUSB*
ls /dev/ttyACM*
```

You may see something like:

```bash
/dev/ttyUSB0
```
If you're using M5Burner, plug in the device while M5Burner is open — the USB interface will appear automatically when the board is connected.

### ✅ Recommended: `screen` or `minicom`

#### 📦 `screen`
- Pre-installed on most distros.
- Simple to use:
  ```bash
  screen /dev/ttyUSB0 115200
  ```

#### 🧩 `minicom`
- Configurable with menus.
- First time setup: run `sudo minicom -s`

### 🔄 Alternatives:
- **picocom**
- **gtkterm**
- **CuteCom**
- **PuTTY for Linux**

---

## ℹ️ Tips

- Make sure to select the correct serial port (e.g. `COM3`, `/dev/ttyUSB0` `/dev/ttyACMO`, or `/dev/tty.usbserial-*`).
- Use **115200 baud rate**, 8 data bits, no parity, 1 stop bit.
- If you don’t see the welcome message, **send any key** to “wake” the Bit Pirate and trigger the banner.


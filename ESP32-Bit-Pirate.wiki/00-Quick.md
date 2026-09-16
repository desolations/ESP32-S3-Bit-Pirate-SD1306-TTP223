# Quick Start
<img width=900 alt="ESP32 Bit Pirate Logo and Supported Protocols" src="https://github.com/user-attachments/assets/a13d7669-3513-48c5-b7bb-05d236796af9" />

## What is ESP32 Bit Pirate?

ESP32 Bit Pirate is a **multi-protocol exploration and debugging tool** for hardware hacking.

It allows you to:

* Explore electronic buses (I2C, SPI, UART, 1-Wire, JTAG, SWD, CAN, etc.)
* Explore radio protocols (RFID, RF, Bluetooth, WiFi, SubGhz)
* Reverse engineer unknown devices
* Send raw transactions
* Read / write memories (EEPROM, Flash, Smartcards)
* Automate tests and scripts

Think of it as a **modern, scriptable toolbox** running on ESP32, with a large range of supported protocols.

---


## What You Need

To get started with ESP32 Bit Pirate, you only need a few basic components.

<img width="200" height="200" alt="ESP32 S3 devkit board" src="https://github.com/user-attachments/assets/b9ffca22-95bd-45cf-91f8-fc001c90df09" />
<img width="200" height="200" alt="Grove cable" src="https://github.com/user-attachments/assets/22e46aff-4188-4f79-bf95-319d426fba3d" />
<img width="200" height="200" alt="Dupont wires male/female" src="https://github.com/user-attachments/assets/a2721a20-1f61-481c-814f-4adda2f38e6a" />
<img width="200" height="200" alt="test hooks grippers" src="https://github.com/user-attachments/assets/f23466a1-e4c7-48b4-853a-b92c0b66d334" />




- An **ESP32-S3 board**
  - Any ESP32S3N8 or ESP32S3N16, **at least 8MB Flash**, no PSRAM required
  - For maximum compatibility, use the boards listed in the [README](https://github.com/geo-tp/ESP32-Bus-Pirate?tab=readme-ov-file#supported-devices)
  - You can install the firmware in one click using the [Web Flasher](https://geo-tp.github.io/ESP32-Bit-Pirate/webflasher/)
- Wiring:
  - Dupont jumper wires (male/female)
  - Or Grove → Dupont / Qwiic → Dupont cables
  - Test hooks / grabbers


## Optional Accessories

Additional protocol support and features can be enabled by connecting external modules:

<img width="200" height="200" alt="CC1101 radio module for subghz" src="https://github.com/user-attachments/assets/f968f66f-7070-45da-9ca4-6541e41e4320" />
<img width="200" height="200" alt="Bus Pirate DIP8 adapter" src="https://github.com/user-attachments/assets/7d89d737-e8ca-4d6a-aab9-37fe16a91451" />
<img width="200" height="200" alt="NRF24 module for 2.4Ghz" src="https://github.com/user-attachments/assets/678795ab-7d66-4dae-aaad-e4cc78082db5" />
<img width="200" height="200" alt="Bus Pirate SOC8 adapter" src="https://github.com/user-attachments/assets/a38641f9-885c-4d0f-8c16-135c6b8d2ce3" />




- [Accessories from the Original Bus Pirate ecosystem](https://buspirate.com/get/) 
- [ESP32 Bit Pirate Dock for ESP32S3 DevKit](https://github.com/AndreiVladescu/ESP32-Bus-Pirate-Dock)
- [ESP32 Bus Expander for WiFi 5GHZ](https://github.com/geo-tp/ESP32-Bus-Expander)

The connection details, references, and information for each module are described in the corresponding [mode](https://github.com/geo-tp/ESP32-Bus-Pirate/wiki).

---


## Basic Concept

Everything is done using commands.
Don’t worry though, **most commands are intentionally kept very simple**. You even have a [Pirate Assistant](https://github.com/geo-tp/ESP32-Bus-Pirate/wiki/99-Assistant) on the web UI to translate what you want to do into commands.

In many cases, **you only need to type a single word** with no arguments or flags at all, such as `read`, `receive`, or `scan`.
Some commands do accept arguments, but they follow straightforward and **intuitive formats**.

General form:

```
command [arg1] [arg2] ...
```

Examples:

```
scan
monitor 0x13
wizard 1
sniff
logic 1
jam
read 0x13 6
```

* Arguments are space-separated
* Arguments in `< >` are required
* Arguments in `[ ]` are optionnal
* Numbers can be decimal or hex:

```
255
0xFF
```
You can **chain multiple commands**, **repeat commands**, and **insert delays** between actions.  
This makes it possible to build simple scripts directly from the command line interface.

Exemples:
```
m dio || read 1 || set 1 LOW || delayms 1 || set 1 HIGH
repeat 5 scan
repeat 10 set 1 LOW || delayus 100 || set 1 HIGH || delayus 100
```

---

## Switching Protocol Modes

You usually start by selecting a protocol:

Type `m`, `mode` or `m uart`, `m i2c`.

```
m         (prompt for mode)
mode      (prompt for mode)
mode uart (direct mode access)
m dio     (direct mode access)
```

## Example 1 – Some I2C operations

![490790516-229dc03c-cb8a-40f2-935c-096d59462378](https://github.com/user-attachments/assets/740447cc-65c2-4281-a9b7-8634a6d7b853)

## Example 2 – Some UART operations

![466254812-6c6752c8-dc4e-47a8-b10c-7e178987f9b1](https://github.com/user-attachments/assets/e3c2dc1e-886f-41a8-8fd3-e51864dd302c)


## Web Serial Tools

The [ESP32 Bit Pirate Web Serial Tools](https://geo-tp.github.io/ESP32-Bit-Pirate/web-tools/) provide direct browser access to embedded hardware utilities, without installing PuTTY, minicom, flashrom, PulseView, or other desktop applications.

<img width="800" alt="web tools demo" src="https://github.com/user-attachments/assets/8b1e145a-6b85-422a-8d67-85d8ac2c9cd2" />



## Python Scripting

You can control ESP32 Bus Pirate from Python over Serial. See [Python Automation](https://github.com/geo-tp/ESP32-Bus-Pirate/wiki/99-Python)

![ezgif-4508b9f0394d2712](https://github.com/user-attachments/assets/654d90df-23f2-4788-b5e8-0c6f8bf34732)


---


ESP32 Bus Pirate is designed to be **explored**.
Type commands, experiment, break things, learn.

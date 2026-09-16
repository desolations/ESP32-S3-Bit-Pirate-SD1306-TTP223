# Terminal Selection

The ESP32 Bit Pirate firmware supports **three main modes of interaction**:

- 🖥️ **Serial CLI** – Connect over USB to send commands via a terminal.
- 🌐 **Web CLI** – Access the browser-based interface through an existing Wi-Fi network or the device hotspot.
- 📟 **Standalone** – On-device screen and keyboard, only for the Cardputer.

All modes offer the same commands and features, but their setup differs depending on your device.

<img width="600" alt="image" src="https://github.com/user-attachments/assets/6ae8adca-9db5-4e14-9ded-c9d34dc5cf05" />

## Web Serial Terminal

The Web Serial Terminal provides direct access to the Serial CLI from a compatible browser, without installing PuTTY, minicom, or another terminal application.

- [Open the ESP32 Bit Pirate Web Tools](https://geo-tp.github.io/ESP32-Bit-Pirate/web-tools/)

<img width="600" alt="ESP32 Bit Pirate Web Serial Tools" src="https://github.com/user-attachments/assets/c946ff16-2073-4285-85d5-00b7b65d5c6f" />



The terminal communicates directly with the device through USB and behaves like a regular serial terminal, with support for interactive commands, keyboard shortcuts, copy and paste, and ANSI terminal output.

---

## Getting Started with Stick

<img width="390" alt="image" src="https://github.com/user-attachments/assets/f499afc9-8e34-447b-9d07-fd29ca97c30d" />

Since the **M5Stick** has no built-in keyboard, you must:

1. Connect to the device via **Serial** or **Wi-Fi HotSpot** (see [Serial](https://github.com/geo-tp/ESP32-Bit-Pirate/wiki/99-Serial)).
2. Select WiFi mode and use the `connect` command to join your Wi-Fi.
3. Restart the device and select **WiFi Connect** to use the browser-based CLI.

## Instant Setup with Cardputer

![cardputer](https://github.com/user-attachments/assets/021fa815-8016-47d3-a5be-d76246964cef)

The **M5Stack Cardputer** includes a built-in keyboard and a screen, so:

- Choose **Standalone** mode to use it on its own, with no connection or Serial terminal required.
- Use `arrows up/down` to scroll, `esc` to scroll line by line and `tab` to restore previous commands.
- Enter your Wi-Fi credentials directly on the device for **WiFi Connect**.
- Select **WiFi Hotspot** to create a direct Wi-Fi network for the Web CLI.
- You can also use a normal Serial connection.

---

## Getting Started with M5StampS3, AtomS3, S3 DevKit, Xiao S3

![s3-devkit](https://github.com/user-attachments/assets/809a5f81-f376-44ac-89db-601ec4a137c2)

These devices have no built-in screen or keyboard, so initial Wi-Fi setup must be done **via Serial** or **WI-Fi Hotspot**.

### Boot Procedure and LED Feedback

After reset, press the board button within 3 seconds:

- **Short press** = WiFi Connect
- **Hold press** = WiFi Hotspot

WiFi Connect uses the saved network credentials. WiFi Hotspot creates a direct network for the Web CLI without requiring an existing Wi-Fi network.

- 🔵 **Blue** – No saved Wi-Fi credentials.
- ⚪ **White** – Connecting.
- 🟢 **Green** – Connected, open the Web CLI.
- 🔴 **Red** – Connection failed.

> ⚠️ **Important:**  
> Do not hold the BOOT button while powering the device, or it may enter USB bootloader mode.

### Fallback to Serial

If WiFi Connect fails, use WiFi Hotspot or reconnect through Serial and run `mode wifi` then `connect`.

## Instant WiFi Setup with the T-Embeds

![tembedcc1101](https://github.com/user-attachments/assets/bac4ae2e-25c0-46b8-9481-f9db42f2e787)


1. Power the device and select **WiFi Connect** or **WiFi Hotspot**.
2. For WiFi Connect, select your network and enter the password with the encoder.
3. Open the Web CLI address shown on the screen.

## Instant WiFi Setup with the T-Display

![t_displays3](https://github.com/user-attachments/assets/1b08ae2d-0bcd-4338-b4d1-c079916f1ae0)

1. Power the device and select **WiFi Connect** or **WiFi Hotspot**.
2. For WiFi Connect, select your network and enter the password with the buttons.
3. Open the Web CLI address shown on the screen.

### Fallback to Serial

If WiFi Connect fails, use WiFi Hotspot or reconnect through Serial and run `mode wifi` then `connect`.

---

## Serial Connection

See the dedicated page about [Serial](https://github.com/geo-tp/ESP32-Bit-Pirate/wiki/99-Serial).

## Note

⚠️ Some commands can interrupt the current terminal session depending on your connection type.

For example, using a Wi-Fi disconnect command will close the Web CLI, while some USB commands will end the USB Serial connection.

💡 For features that generate a large amount of output, such as 1-Wire or I2C sniffers, use the Serial CLI to avoid missing data.

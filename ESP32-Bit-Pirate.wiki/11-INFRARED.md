
# Infrared Mode

This mode allows communication using infrared signals to send and receive remote control commands.  
It supports sending specific codes, learning signals from remotes, broadcasting Device-B-Gone codes, wide protocol selection, and universal remote builtin.


## 🧩 Commands
Arguments in `< >` are required, while arguments in `[ ]` are optional.

| Command                         | Description                                                                 |
|----------------------------------|-----------------------------------------------------------------------------|
| `send <dev> <sub> <cmd>`        | Send an IR command with current protocol, device, sub-device and command (check [IRDB](https://github.com/probonopd/irdb) for a wide list of remotes data) |
| `receive`                       | Listen for incoming IR signal and decode it or see it raw                                |
| `setprotocol`                   | Choose from 83 supported IR protocols (NEC, Sony, RC5, etc.)                |
| `devicebgone`                   | Send a sequence of IR commands to power off TVs, projectors, boxes...      |
| `remote`                        | Launch an interactive shell to universal remote control features        |
| `record`                        | Interactively record IR signals and save them to a .ir file using [LittleFS storage](https://github.com/geo-tp/ESP32-Bus-Pirate/wiki/99-LittleFS)        |
| `load`                          | Load and select remote `.ir` files from the [LittleFS storage](https://github.com/geo-tp/ESP32-Bus-Pirate/wiki/99-LittleFS)
| `replay [count]`                | Records up to 64 frames and replay them with original delays in between        |
| `jam`                           | Transmits infrared bursts to evaluate how well an infrared receiver handles noise        |
| `config`                        | Configure IR TX and RX pins                                                 |

## 🧪 Recipes

- [Capture an infrared remote signal](https://geo-tp.github.io/ESP32-Bit-Pirate/recipes/capture-infrared-remote/)
- [Load and send a Flipper IR file](https://geo-tp.github.io/ESP32-Bit-Pirate/recipes/load-flipper-ir-file/)
- [Record an infrared remote to a .ir file](https://geo-tp.github.io/ESP32-Bit-Pirate/recipes/record-infrared-remote-file/)
- [Use the infrared universal remote shell](https://geo-tp.github.io/ESP32-Bit-Pirate/recipes/use-infrared-universal-remote-shell/)
- [Use the USB IR Toy LIRC adapter](https://geo-tp.github.io/ESP32-Bit-Pirate/recipes/use-usb-ir-toy-lirc-adapter/)


## 📂 Load (`.ir` files)

The `load` command uses infrared remote files from the [**Flipper IR DB**](https://github.com/Lucaslhm/Flipper-IRDB).

### How it works (quick start)
1. **Upload the file(s)**  
   In the Web UI, open [**Files → LittleFS**](https://github.com/geo-tp/ESP32-Bus-Pirate/wiki/99-LittleFS) and drop your `.ir` files.  

2. **Load from the device**  
   In INFRARED mode, run:
   ```bash
   load
   ```
   - Pick a `.ir` from the list.
   - You can send frames by selecting the index.

3. **Send**  
   Use the file’s metadata (frequency, preset, protocol) to send the command.  
   If multiple commands are present, you can iterate and replay as needed.


## 📝 Notes

- `send` uses the current protocol defined in `setprotocol` and repeats the command 3 times.
- `receive` continuously listens for IR signals and displays the protocol + data when valid.
- `devicebgone` loops through a list of known "off" commands from 83 common IR protocols.
- `remote` opens an interactive menu to blast common keys (VOL, MUTE, POWER...) across many protocols (200 commands per action). Use `Enter` to stop early.
- `replay` asks you to record frames, once it's done, press ENTER to replay them. Optional replay count.
- `setprotocol` displays a list of all available protocols and lets you choose one, it will be used with `send`.
- `config` allows you to set which GPIOs are used for IR transmit (TX) and receive (RX).
- `load` works with `.ir` files from https://github.com/Lucaslhm/Flipper-IRDB
- `record` asks for function name and save up to 64 frames using flipper zero IR file format.
- `jam` prompts for mode, carrier frequency (khz), and transmission density before running.
- See https://github.com/probonopd/irdb for a massive database of IR remotes (`device` `subdevice` `function`) to use with the `send` command


## 📌 Example Usage

```bash
mode infrared
config                     # Set TX and RX pins
setprotocol                # Select a protocol (e.g. NEC, Sony)
send 0 0 64                # Send command (device=0, sub=0, command=64)
receive                    # Wait for and decode IR signals
remote                     # Open an universal remote shell
replay                     # Records up to 64 IR signals and replay until ENTER is pressed
load                       # Load .ir remote files from the NVS and select the one you want
replay 10                  # Records up to 64 IR signals and replay 10 times or until ENTER is pressed
jam                        # Spam random infrared signals
devicebgone                # Try turning off all nearby devices
```

## ▶️ Demo
![infrared](https://github.com/user-attachments/assets/7072cfa5-1495-4369-bcd2-a41027d0177e)



## 🔧 Hardware
![S7d82489ac25345fa9146425cfb5a0cb4o jpg_960x960](https://github.com/user-attachments/assets/ed817ad4-7b13-4d09-9172-f9d53d093aeb)
![51MHwDtnELL _AC_UF350,350_QL80_](https://github.com/user-attachments/assets/d558c2ab-b62f-46bd-9c17-50d591f062b4)


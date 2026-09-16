
# Python Scripts for ESP32 Bit Pirate

<img width="800" alt="bit pirate scripts" src="https://github.com/user-attachments/assets/a967e3bf-ab25-40dd-9a15-fb1beb900cbe" />




https://github.com/geo-tp/ESP32-Bit-Pirate-Scripts

This repository provides a collection of ready-to-use Python scripts to **interact**, **log**, and **automate hardware actions** using the ESP32 Bus Pirate via serial communication.

https://github.com/geo-tp/Bit-Pirate-Python

This repository provides the `bit-pirate` python package used with the scripts.

## Use the Web Python Lab

<img width="1000" alt="The ESP32 Bit Pirate Python Lab interface" src="https://github.com/user-attachments/assets/43d6a01d-738a-4be9-a569-5e54cc50e226" />

[Open ESP32 Bit Pirate Python Lab](https://geo-tp.github.io/ESP32-Bit-Pirate/web-tools/python-lab/)


## Create Your Script

`python -m pip install bit-pirate`

```python
from bitpirate import BitPirate

bp = BitPirate.auto_connect()
bp.start()
bp.change_mode("i2c")
bp.send("scan")
bp.wait()
print(bp.receive())
bp.stop()


```

Additional `Helper`, `bpio2` class to parse, bit bang and manipulate response from the ESP32 Bit Pirate.



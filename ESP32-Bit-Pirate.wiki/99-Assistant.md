# Pirate Assistant

The **Pirate Assistant** is an integrated smart interface that translates human intent into executable commands for the firmware. It's simplify the usage of the Bus Pirate by allowing users to describe what they want to do, without needing to know exact commands.

## Example 1 - Monitor pins
<img width="900" alt="aibox6" src="https://github.com/user-attachments/assets/8f62be8b-33bb-4208-8570-9ba708b3e19e" />

## Example 2 - Set PWMs
<img width="900" alt="aibox4" src="https://github.com/user-attachments/assets/d57404d0-df76-4c42-bde9-3ea6bd95d4ad" />

## Example 3 - Monitor I2C registers
<img width="900" alt="aibox3" src="https://github.com/user-attachments/assets/0da989ea-d214-43dd-a094-1916a3d8a855" />

## Example 4 - PWMs on mobile phone
<img width="400" alt="38455953-9CEE-4E4B-965B-B1AC43C3CAEC" src="https://github.com/user-attachments/assets/185feae9-6848-4576-b83c-1695c641ab12" />


## 🔐 Gemini API Key

The Pirate Assistant uses the Gemini API for natural language translation. See [API Quickstart](https://ai.google.dev/gemini-api/docs/quickstart) to get a key (free).


### How to use it

1. Connect to the ESP32 Bus Pirate WEB interface
2. Open the **Pirate Assistant** with ✨ button
2. Click **API Key**
3. Paste your Gemini API key

Once saved, the assistant can start translating requests into firmware commands.


### Where the key is stored

- The API key is stored **locally in the browser**
- It is **not hardcoded in the firmware**
- It is **not embedded in the device**
- It remains available for future sessions on the same browser unless manually cleared

## ⚠️ Limitations

- Requires internet access
- Suggestions may need manual validation
- The Pirate Assistant can make errors

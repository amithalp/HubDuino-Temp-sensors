# HubDuino Temp Sensors

This project reads water and room temperature from two DS18B20 sensors using an ESP32 connected via Ethernet (W5500 module) and sends the data to a Hubitat hub using the HubDuino SmartThings protocol. It also displays temperature and connection status on an OLED screen (SSD1315).

---

## 📦 Components Used

- ESP32 DevKit v1
- W5500 Ethernet module (powered by 3.3V)
- DS18B20 waterproof temperature sensors (x2)
- 0.96" SSD1315 OLED Display (I²C, 128x64)
- Terminal adapter board for ESP32
- 4.7kΩ pull-up resistor on DS18B20 data line (or onboard with terminal)
- IP55+ enclosure (recommended for humid environments)

---

## 📐 Wiring Summary

| Component       | ESP32 GPIO | Notes                         |
|----------------|------------|-------------------------------|
| DS18B20 Sensors| GPIO 32     | Shared data line for both     |
| OLED Display   | GPIO 21 (SDA), 22 (SCL) | I²C default pins     |
| W5500 Module   | GPIO 5 (CS) | SPI wiring required (3.3V)    |

---
<img width="1553" height="841" alt="image" src="https://github.com/user-attachments/assets/6f342c79-7b58-42fb-956a-0b3e10103c69" />

## 💡 Display

The OLED displays:
- Pool temperature
- Room temperature
- ESP32 IP address
- Connection status (`OK` or `FAIL` based on last sync)
- 
<img width="223" height="205" alt="image" src="https://github.com/user-attachments/assets/9a7ae034-9d0b-4156-81d3-cbeed6352124" />

---

## 🧠 Hubitat Integration

### Required HubDuino Drivers
Install the following drivers from the HubDuino GitHub repository:
- **Parent Ethernet Device**: `HubDuino Parent Ethernet`
  
- **Child Temperature Devices**: using the native Generic Component Temperature Sensor no need to download

You must also install the HubDuino SmartApp:
- `ST_Anything_EthernetW5500` (or use the HubDuino Service Manager)

### Device Setup
1. Create a **Parent Ethernet Device** in Hubitat.
2. Set the device IP address to the one used by the ESP32.
3. The ESP32 will create two child devices: `temperature1` and `temperature2`.

---

## 🔧 Setup Instructions

1. Connect all components per the wiring diagram.
2. Open `HubDuinoTempSensors.ino` in the Arduino IDE.
3. **Update these lines to match your network:**

```cpp
IPAddress ip(10, 21, 1, 160);     // ESP32 static IP
IPAddress hubIP(10, 21, 1, 51);   // Hubitat hub IP
Connect the ESP32 via USB to your computer and upload the sketch.

After flashing, power the ESP32 through a 3.3V power supply and connect Ethernet.

Check that temperatures appear in Hubitat and on the OLED screen.

🚨 Notes
The ESP32 does not support OTA updates via Ethernet; updates require USB connection.

The system does not rely on Wi-Fi, making it ideal for shielded/underground environments.

Use an IP55/IP65 case or better if installed in high humidity areas like a pool machine room.

📜 License
This project is released under the MIT License.

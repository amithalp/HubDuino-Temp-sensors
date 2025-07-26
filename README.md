# HubDuino Temp Sensors

This project is a wired ESP32-based temperature monitoring system designed for Hubitat integration via HubDuino. It reads two DS18B20 temperature sensors (for pool and machine room), transmits data over Ethernet using a W5500 module, and displays real-time values on an OLED screen.

## 💡 Features

- ESP32 + W5500 Ethernet module for stable LAN communication
- Two DS18B20 temperature sensors on a shared 1-Wire bus (GPIO32)
- SSD1315 OLED display showing:
  - Pool temperature
  - Machine room temperature
  - IP address
  - Connection status (OK / FAIL)
- Hubitat HubDuino integration using `SmartThingsEthernetW5x00` library
- Presence detection handled via Hubitat device timeout

---

## 🧰 Hardware Used

- ESP32 DevKit board
- ESP32 terminal adapter board (optional)
- W5500 Ethernet module (powered via 3.3V)
- 2× DS18B20 waterproof temperature sensors (with pluggable terminal + 4.7kΩ resistor)
- 0.96" OLED Display (SSD1315 I2C)
- IP55 electrical enclosure or CI3 case
- Power supply: 5V via USB (fed from PC or wall adapter)

---

## 🔌 Wiring

| Component        | ESP32 Pin | Notes                       |
|------------------|-----------|-----------------------------|
| DS18B20 Sensors  | GPIO32    | 1-Wire shared bus           |
| OLED (SSD1315)   | GPIO21 (SDA) / GPIO22 (SCL) | I2C Bus |
| W5500 CS         | GPIO5     | SPI CS                      |
| W5500 Power      | 3.3V      | Not 5V!                     |
| GND              | GND       | Common ground               |

**Note**: DS18B20 sensors require a 4.7kΩ pull-up resistor on the data line. If your pluggable terminal includes a `472` component, it already has it.

---

## 🔧 Hubitat Setup

- Parent device created using `HubDuino Parent Ethernet Beta` driver.
- Child devices:
  - `temperature1` → Pool temp
  - `temperature2` → Machine room temp
- Presence attribute used for "online/offline" status (based on ESP32 updates).

---

## 📟 OLED Display

Display format:
Pool: 26.5C
Room: 24.8C
IP: 10.21.1.160
Status: OK


Status turns to `FAIL` if the ESP32 hasn't sent data for more than 30 seconds.

---

## 🛠️ Future Enhancements

- Add enclosure layout image
- Include 3D model for internal mounting (optional)
- Display uptime or custom logo on OLED
- Optional: Add button input for reset or calibration

---

## 📸 Project Overview

_Example layout or wiring diagram here_
<!-- You can add a link to a diagram or upload it to your GitHub repo -->

---

## 📁 File Structure


---

## 📜 License

MIT License – feel free to adapt and reuse.

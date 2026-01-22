# DiyaGlow-ESP32 🪔

A Wi-Fi controlled **Smart Diya lighting system** built using **ESP32**, featuring a modern web dashboard and a smooth LED glow-up sequence inspired by a real diya lighting experience.

This project demonstrates how embedded systems, web technologies, and PWM-based lighting control can be combined to create an elegant IoT showcase.

---

## ✨ Features

- ESP32 operates in **Wi-Fi Access Point mode** (no internet required)
- Mobile-friendly **web dashboard**
- Single interactive control: **“Light up Diya”**
- Smooth **PWM-based LED glow-up sequence**
- Sequential lighting of 6 LEDs
- Clean UI with responsive design
- Fully offline and self-contained

---

## 🛠️ Hardware Requirements

- ESP32 DevKit V1
- 6 × LEDs
- 6 × 220Ω (or 330Ω) resistors
- Breadboard and jumper wires
- Smartphone or laptop with Wi-Fi

---

## 🔌 Pin Configuration

| LED Number | ESP32 GPIO Pin |
| ---------- | -------------- |
| LED 1      | GPIO 21        |
| LED 2      | GPIO 22        |
| LED 3      | GPIO 23        |
| LED 4      | GPIO 19        |
| LED 5      | GPIO 18        |
| LED 6      | GPIO 5         |

**Wiring Rule:**
ESP32 GPIO → Resistor → LED Anode (+)
LED Cathode (–) → GND


---

## 🌐 How It Works

1. ESP32 creates its own Wi-Fi network (Access Point).
2. A web server runs directly on the ESP32.
3. The user connects to the network using a phone or laptop.
4. A web dashboard is opened in the browser.
5. Clicking **“Light up Diya”** triggers a smooth LED glow-up sequence.
6. PWM (LEDC) is used to gradually increase LED brightness.
7. The **Back** button turns off the LEDs and resets the system.

No cloud, no internet, no external dependencies.

---

## 📱 How to Use

1. Upload the code to ESP32.
2. Power the ESP32.
3. Connect to Wi-Fi network:

SSID: ESP32_LED
Password: 12345678

4. Open a browser and go to:
http://192.168.4.1

5. Click **Light up Diya**.

---

## 🎯 Use Case

- College mini-project
- IoT demonstrations
- Embedded systems learning
- Guest or faculty showcase
- Smart lighting concept prototype

---

## 🔒 Security Note

The Wi-Fi credentials are for a **local ESP32 Access Point only**.
They are not connected to any personal or external network and are safe to keep public for demonstration purposes.

---

## 📁 Project Structure

DiyaGlow-ESP32/
├── Smooth_Glow_Up_LED.ino
└── README.md


---

## 🚀 Future Enhancements

- Individual LED control
- Diya flicker animation
- Adjustable glow speed
- Status indicators
- Mobile app integration

---

**DiyaGlow-ESP32** — where technology meets tradition.
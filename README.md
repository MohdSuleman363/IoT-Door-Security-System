# IoT Door Security System using ESP8266 & Telegram

This project implements an IoT-based door security system using **NodeMCU (ESP8266)**.  
Whenever the door is opened (simulated using a push button or reed switch), an instant alert message is sent to the user via **Telegram**.

---

## Features
- Real-time Telegram alert notification
- Uses NodeMCU ESP8266 (ESP-12E)
- Secure HTTPS communication
- Simple and low-cost hardware setup
- Suitable for smart home security applications

---

## Hardware Components
- NodeMCU ESP8266 (ESP-12E)
- Push Button / Reed Switch
- Jumper wires
- USB cable
- Wi-Fi / Mobile Hotspot

---

## Software & Tools
- Arduino IDE / VS Code
- Telegram Bot API
- Embedded C / Arduino programming

---

## Circuit Connections

| Component | NodeMCU Pin |
|---------|-------------|
| Push Button / Reed Switch | D2 (GPIO4) |
| Push Button / Reed Switch | GND |

> Internal pull-up resistor is used, so no external resistor is required.

---

## Configuration (IMPORTANT)

Before uploading the code, update the following details inside the `.ino` file.

### Wi-Fi Credentials 
-> ```cpp
  const char* ssid = "YOUR_WIFI_NAME";
  const char* password = "YOUR_WIFI_PASSWORD";

  ssid → Wi-Fi or mobile hotspot name

password → Wi-Fi password

-> ESP8266 supports 2.4 GHz networks only


Telegram Bot API

const String BOT_TOKEN = "YOUR_BOT_TOKEN";
const String CHAT_ID  = "YOUR_CHAT_ID";

BOT_TOKEN → Create using @BotFather on Telegram

CHAT_ID → Chat ID where alerts will be received


###Working Principle

Door opening triggers the button/reed switch
ESP8266 detects LOW signal using INPUT_PULLUP
ESP8266 connects to Wi-Fi
HTTPS request is sent to Telegram Bot API
User receives real-time alert message


Output Screenshots

Telegram Alert Messages
Hardware Setup
Arduino IDE Output



Applications

Home door security
Smart room monitoring
Intrusion alert system
IoT-based alert automation


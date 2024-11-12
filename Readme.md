# ESP8266 Robot Car Controller

This project is a WiFi-based robot car controller built using an ESP8266 module and an L298N motor driver. It allows you to control a robot car remotely via WiFi, using different commands to move the car in various directions, adjust the speed, and toggle an LED lamp.

## Components

- ESP8266 (NodeMCU) module
- L298N Motor Driver
- DC Motors
- LED or Lamp
- Jumper Wires

## Pin Configuration

| ESP8266 Pin | Component             | Description                      |
|-------------|-----------------------|----------------------------------|
| D16 (GPIO 16) | ENA               | Right motor speed control         |
| D14 (GPIO 14) | ENB               | Left motor speed control          |
| D5 (GPIO 5)  | IN_1              | Right motor control               |
| D4 (GPIO 4)  | IN_2              | Right motor control               |
| D0 (GPIO 0)  | IN_3              | Left motor control                |
| D2 (GPIO 2)  | IN_4              | Left motor control                |
| D12 (GPIO 12) | Lamp              | Lamp control                      |

## Code Description

The code sets up the ESP8266 in Access Point (AP) mode, enabling a simple server to control the robot. Commands are received as URL parameters, allowing users to control the car's movements, adjust speed, and toggle the lamp via HTTP requests.

### Movements
The robot car can move in the following directions:
- **Forward**
- **Backward**
- **Left**
- **Right**
- **Diagonal Movements** (Forward Right, Forward Left, Backward Right, Backward Left)

### Speed Control
The speed is controlled using a predefined coefficient for each speed level, allowing smoother movements and better control.

### Lamp Control
An LED or lamp can be toggled on and off with specific commands.

## Commands

The HTTP server listens for commands sent as URL parameters with the key `State`. The possible values and actions are:

| Command | Action                |
|---------|------------------------|
| F       | Move forward           |
| B       | Move backward          |
| L       | Move left              |
| R       | Move right             |
| I       | Move diagonally forward-right |
| G       | Move diagonally forward-left  |
| J       | Move diagonally backward-right|
| H       | Move diagonally backward-left |
| S       | Stop the robot         |
| W       | Turn lamp on           |
| w       | Turn lamp off          |
| 0-9, q  | Set speed levels       |

## Setup Instructions

### Hardware Setup

1. Connect the DC motors to the L298N motor driver.
2. Connect the L298N pins to the ESP8266 as follows:
   - ENA to GPIO 16, ENB to GPIO 14
   - IN1 to GPIO 5, IN2 to GPIO 4, IN3 to GPIO 0, IN4 to GPIO 2
3. Connect an LED or lamp to GPIO 12, with an appropriate resistor if needed.
4. Power the ESP8266 and the motors.

### Software Setup

1. Ensure the **ESP8266 board support** is installed in the Arduino IDE.
2. Set up the WiFi credentials (optional as the ESP8266 will act as an AP).
3. Upload the code to the ESP8266.

### Connecting to the Robot Car

1. Power on the ESP8266 module.
2. Connect to the ESP8266's WiFi network with SSID **KOMINFO** and password **Admin1234**.
3. Access the control interface by navigating to the ESP8266’s IP address (printed in the Serial Monitor).

### Controlling the Car

Use an HTTP client or web browser to send requests to control the car. For example:
- Move forward: `http://<IP_ADDRESS>/?State=F`
- Move backward: `http://<IP_ADDRESS>/?State=B`
- Turn lamp on: `http://<IP_ADDRESS>/?State=W`
- Set speed to level 5: `http://<IP_ADDRESS>/?State=5`

Replace `<IP_ADDRESS>` with the actual IP address of your ESP8266 module.

---

This should give you full control over the robot car's movements, speed, and lamp functionality via WiFi.
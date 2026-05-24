# 🚗 Smart Robot Car

A four-wheel autonomous robot car controlled via a custom-built Flutter mobile application over Bluetooth. The car supports multiple intelligent driving modes and was built as part of a microprocessor systems project.

---

## 📱 Mobile App

The car is controlled through a custom Flutter app built from scratch, currently in active development and **coming soon to the Play Store**.

Features:
- Bluetooth device pairing & connection
- Joystick-based manual control
- Speed dial (0–9)
- Mode switching (Manual / Autonomous / Parking)
- Teach & Repeat recording and playback
- Real-time battery level indicator

---

## 🎮 Modes

### 1. Manual Mode
Control the car in real time using a joystick in the app. Supports forward, backward, left, right, and all four diagonal directions. Speed is adjustable from the app.

### 2. Autonomous Mode
The car navigates independently using a front-mounted ultrasonic sensor on a servo motor. When an obstacle is detected, the servo scans left and right to measure available space, then turns toward the clearest path automatically.

### 3. Teach & Repeat Mode
Record a manual driving path using the app, then replay it autonomously. The car memorizes every movement and its duration, then executes the exact sequence on demand.

### 4. Auto Parking Mode
The car detects a parking spot on its right side using an ultrasonic sensor, aligns itself with the space, and executes a full parallel parking maneuver automatically using a 4-stage state machine:
- **Stage 1:** Approach and longitudinal alignment with target vehicle
- **Stage 2:** Entry turn — reverse arc into the spot
- **Stage 3:** Pivot — straighten up inside the spot
- **Stage 4:** Centering — adjust position between front and rear vehicles

---

## 🔧 Hardware

| Component | Details |
|---|---|
| Microcontroller | Arduino Uno |
| Motor Driver | L298N |
| Motors | 2x DC Motors |
| Bluetooth | HC-05 |
| Ultrasonic Sensors | 3x HC-SR04 (Front, Right, Rear) |
| Servo Motors | 2x (Parking + Autonomous scanning) |
| Battery | 12V |
| Battery Monitoring | Voltage divider circuit → Analog pin |

---

## 💻 Software

### Arduino (PlatformIO)
Modular architecture split into HAL and App layers:
src/
├── HAL/              # Hardware Abstraction Layer
│   ├── config.h      # All pin definitions and constants
│   ├── HALmotor      # Motor control
│   ├── HALsensors    # Ultrasonic sensors
│   ├── HALservo      # Servo control
│   └── HALbattery    # Battery monitoring
└── App/              # Application Logic Layer
├── AppManual     # Manual mode & command processing
├── AppAuto       # Autonomous mode state machine
├── AppParking    # Parking state machine
└── AppT_L        # Teach & Repeat logic

### Flutter App
Built from scratch using Flutter & Dart. Communicates with the car via HC-05 Bluetooth module using the `flutter_bluetooth_serial` package.

> 📲 App is currently in development — **publishing soon**

---

## 🚀 Getting Started

### Arduino
1. Clone the repository
2. Open in VS Code with the PlatformIO extension installed
3. Connect your Arduino Uno
4. Build and upload via PlatformIO

### Dependencies
Add to `platformio.ini`:
```ini
lib_deps =
    arduino-libraries/Servo
```

---

## 📂 Repository Structure
Smart-Robot-Car/
├── src/
│   ├── HAL/
│   └── App/
├── main.ino          # Standalone single-file version (Arduino IDE)
├── platformio.ini
└── README.md

---

## 🛠️ Built With

- C++ / Arduino Framework
- Flutter / Dart
- PlatformIO

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

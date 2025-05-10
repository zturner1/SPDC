# SPDC – Sealed Pulse Dosing Cell

**Designed by Zachary Turner, 2025**

The **Sealed Pulse Dosing Cell (SPDC)** is a precision-controlled fluid dispensing architecture. It uses a diaphragm pump, solenoid valve, flow sensor, and check valve to measure and deliver exact volumes of liquid using pulse-based feedback.


---

## 🔧 What Is It?

SPDC is a microcontroller-driven flow control system that delivers measured water doses with sub-±5mL accuracy across a wide range (50–500mL tested). It is optimized for systems where fluid must be precisely dosed and sealed — such as greenhouse watering, lab reagent filling, or automated brewing.

---

## ⚙️ System Architecture

Pump → Solenoid Valve → Flow Sensor → Check Valve → Output


- **Pump**: Self-priming diaphragm pump pressurizes the system
- **Solenoid Valve**: Normally closed; opens on command to initiate flow
- **Flow Sensor**: YF-S401 pulse-output sensor measures exact flow volume
- **Check Valve**: Prevents backflow and seals off final fluid path post-dispense

---

## 🧠 Why This Order?

This architecture provides:
- 💧 Clean hydraulic startup
- 📏 Accurate volume sensing with minimal turbulence
- 🔒 Sealed delivery to prevent drift, leakage, or siphon errors
- ⚡ Quick on/off flow dynamics due to pulse-based triggering and valve gating

Unlike traditional open-loop timers, the SPDC reacts to real flow — not assumptions.

---

## 🧪 Core Principles

- **Pulse Counting = Precision**: All flow is measured in digital pulses, not approximated by time or pump speed.
- **Sealed Volume**: From solenoid to check valve, the measured water is isolated and delivered exactly.
- **Repeatable**: The same request yields the same result every time.

---

## 📋 Components (Reference Build)

| Component         | Example Model            |
|------------------|--------------------------|
| Microcontroller  | Arduino Uno R3           |
| Pump             | 12V self-priming diaphragm |
| Solenoid Valve   | 12V normally-closed       |
| Flow Sensor      | YF-S401                   |
| Check Valve      | 1/4" inline plastic       |

---

## 🔓 Licensing

This architecture is **free for personal and educational use**.  
For commercial use, please contact:

**Zachary Turner**  
📧 zturner14@gmail.com  

> © 2025 Zachary Turner. All rights reserved.

---

## 📍 Coming Soon
- Full Arduino Sketch (SPDC_Firmware_v1.0.ino)
- Calibration guide
- Sample flow logs
- Wiring diagrams & illustrations




# Wiring Guide

This guide documents the current starter-firmware wiring. Disconnect USB and battery power while changing connections.

## 1. FSR402 pressure sensor

Use a 10 kΩ fixed resistor as a voltage divider:

```text
Arduino 5V
   |
 FSR402
   |
   +---------- Arduino A0
   |
  10 kΩ
   |
Arduino GND
```

- FSR402 has no polarity.
- Put the FSR between 5V and A0.
- Connect a 10 kΩ resistor between A0 and GND.
- Do not connect the FSR directly across 5V and GND without the divider.

## 2. MLX90614 temperature sensor

For a breakout board whose VIN pin accepts 5 V:

| MLX90614 breakout | Arduino UNO |
|---|---|
| VIN / VCC | 5V (only if the breakout supports 5V input) |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

Some MLX90614 boards are 3.3 V-only or have different pin labels. Check the exact breakout documentation before applying power.

## 3. HW-072 vibration module

| HW-072 pin | Arduino UNO |
|---|---|
| VCC | 5V, if supported by the module |
| GND | GND |
| DO | D2 |

If the board also has AO, it is not used by this starter firmware. Digital output polarity can vary by module; the sketch prints the raw HIGH/LOW state.

## 4. Optional LED

```text
Arduino D9 ---- 220 Ω resistor ---- LED anode (+)
LED cathode (-) ------------------- GND
```

The resistor is required to limit LED current.

## 5. Optional buzzer

Do not assume every buzzer can be driven directly from an Arduino pin. For a typical 5 V buzzer, use an NPN transistor driver:

```text
Arduino D8 ---- 1 kΩ ---- transistor base
Transistor emitter -------- GND
Transistor collector ------ buzzer negative (-)
Buzzer positive (+) ------- suitable 5 V supply
```

Use a transistor with an appropriate current rating and verify its pinout. If the buzzer is magnetic/inductive, add a flyback diode across it (cathode to +5 V, anode to the transistor collector). Ensure the Arduino and buzzer supply grounds are common.

## 6. Conductive touch/contact probe

The probe's exact construction/interface has not been confirmed, so no pin assignment is specified here. Do not connect unknown electrodes directly to an Arduino pin or to a power rail. Share a photo or the module part number to add a safe, exact circuit.

## 7. OLED/display

A display type and controller have not been confirmed. No display wiring is included in this starter configuration. If using a 4-pin I²C OLED, it may share A4 (SDA) and A5 (SCL) with the MLX90614, but its supply voltage and I²C address must first be checked.

# Multifunctional Smart Glove

An Arduino Uno-based wearable sensing project that monitors temperature, vibration and pressure/contact using multiple sensors. Sensor readings are displayed on an I2C OLED and printed to the Serial Monitor.

## Features

- **Temperature monitoring:** GY-906 MLX90614 infrared temperature sensor.
- **Vibration detection:** HW-072 vibration sensor.
- **Pressure/contact sensing:** FSR402 force-sensitive resistor.
- **OLED output:** Displays temperature, pressure score and vibration status.
- **Temperature alert:** Buzzer activates when the object temperature reaches the configured threshold.
- **Serial monitoring:** Displays sensor readings for testing and debugging.

## Hardware Components

| Component | Quantity |
|---|---:|
| Arduino Uno | 1 |
| GY-906 MLX90614 | 1 |
| HW-072 vibration sensor | 1 |
| FSR402 | 1 |
| 0.96-inch I2C OLED (SSD1306) | 1 |
| Active buzzer | 1 |
| Resistor for FSR voltage divider | 1 |
| Battery pack and suitable regulated power supply | 1 |

## Pin Connections

| Component | Arduino Uno |
|---|---|
| MLX90614 SDA | A4 |
| MLX90614 SCL | A5 |
| OLED SDA | A4 |
| OLED SCL | A5 |
| HW-072 DO | D2 |
| FSR voltage-divider output | A0 |
| Buzzer signal | D8 |
| VCC | 5V, where supported |
| GND | GND |

The OLED and MLX90614 share the I2C bus.

## Software Requirements

Install the following libraries through Arduino IDE Library Manager:

1. Adafruit MLX90614
2. Adafruit SSD1306
3. Adafruit GFX Library

Select **Arduino Uno** as the board and upload `smart_glove.ino`.

## Repository Structure

```text
Multifunctional-Smart-Glove/
│
├── smart_glove.ino
├── README.md
├── LICENSE
├── .gitignore
│
├── docs/
│   ├── wiring.md
│   └── troubleshooting.md
│
└── sensor_tests/
    ├── MLX_sen_test.ino
    ├── FSR_sen_test.ino
    └── vibration_sensor_testing.ino
```

## Working Principle

1. The MLX90614 measures object and ambient temperature.
2. The HW-072 detects vibration through its digital output.
3. The FSR402 produces an analog reading based on applied force.
4. The Arduino processes the readings and updates the OLED.
5. The buzzer provides an alert when the configured temperature threshold is reached.

## Important Notes

- The FSR percentage is a scaled analog reading, not calibrated force.
- The temperature alert threshold is set to 40°C in the code and can be changed.
- The vibration output is configured as active-LOW. Change `VIBRATION_ACTIVE_LEVEL` if your module behaves differently.
- The OLED is configured for I2C address `0x3C`. Some displays use `0x3D`.
- Verify the regulated supply voltage and common ground before powering the circuit. Do not connect an unregulated battery pack directly to the Arduino 5V pin.

## Project Status

Completed prototype with temperature sensing, vibration detection, pressure/contact sensing and OLED output.

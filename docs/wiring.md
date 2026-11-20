
# Wiring Guide

## I2C: OLED and MLX90614

Both modules use the same I2C bus.

| Module pin | Arduino Uno |
|---|---|
| OLED VCC | 5V (if supported by module) |
| OLED GND | GND |
| OLED SDA | A4 |
| OLED SCL | A5 |
| MLX90614 VIN | 5V (if supported by breakout) |
| MLX90614 GND | GND |
| MLX90614 SDA | A4 |
| MLX90614 SCL | A5 |

## HW-072 Vibration Sensor

| HW-072 | Arduino Uno |
|---|---|
| VCC | 5V |
| GND | GND |
| DO | D2 |

## FSR402 Voltage Divider

Connect the FSR and a fixed resistor as a voltage divider:

- One FSR terminal → 5V
- Other FSR terminal → A0
- Fixed 10kΩ resistor → between A0 and GND

The junction between the FSR and resistor connects to A0.

## Buzzer

- Buzzer positive / signal → D8
- Buzzer negative → GND

Use a suitable driver if the buzzer current exceeds the Arduino pin rating.

## Power

Use a properly regulated supply suitable for the Arduino and connected modules. Confirm the battery pack, protection circuitry and converter output before connecting power. All circuit grounds must be common.

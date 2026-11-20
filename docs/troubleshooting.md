
# Troubleshooting

## OLED is blank
- Check SDA → A4 and SCL → A5.
- Confirm the OLED address is 0x3C; some modules use 0x3D.
- Confirm the Adafruit SSD1306 and Adafruit GFX libraries are installed.

## MLX90614 not detected
- Check VIN, GND, SDA and SCL.
- Confirm the sensor breakout's voltage requirements.
- Check for I2C address conflicts or loose connections.

## Vibration status is reversed
Change this line in smart_glove.ino:

const byte VIBRATION_ACTIVE_LEVEL = LOW;

Use HIGH if your module outputs HIGH when vibration is detected.

## FSR reading is always low
- Check the voltage-divider connections.
- Confirm the resistor connects from A0 to GND.
- Confirm the FSR is connected between 5V and A0.
- Check the sensor and jumper wires.

## Buzzer does not activate
- Check the buzzer polarity and connection to D8.
- Confirm that the object temperature reaches the configured threshold.
- Confirm that the buzzer is compatible with the output circuit.

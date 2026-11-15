# Multifunctional Smart Glove

Arduino UNO prototype for monitoring external conditions during inspection and maintenance.

## Project functions

- **Temperature:** MLX90614 non-contact infrared temperature sensor.
- **Pressure / force response:** FSR402 force-sensitive resistor.
- **Vibration:** HW-072 vibration switch/module.
- **Feedback (prototype):** optional LED and buzzer outputs.
- **Contact detection:** conductive touch/contact probe is part of the planned hardware; its exact interface has not yet been specified.

The current firmware reports sensor readings over the Arduino Serial Monitor. It is intended for prototyping and calibration, not as a certified safety device.

## Hardware status

| Component | Status in this repository |
|---|---|
| Arduino UNO | Confirmed |
| MLX90614 IR temperature sensor | Confirmed |
| HW-072 vibration sensor | Confirmed |
| FSR402 pressure sensor | Confirmed |
| Conductive touch/contact probe | Hardware mentioned; exact module/wiring to be confirmed |
| 5 V buzzer | Planned output; use a transistor driver |
| LED + 220 Ω resistor | Planned output |
| 3 × 3.7 V Li-ion cells | Battery pack mentioned; series/parallel arrangement must be verified |
| MT306 boost converter | Converter model marking and electrical limits must be verified |
| OLED/display | Not confirmed; not included in firmware pin map |

## Repository structure

```text
smart-glove/
├── README.md
├── .gitignore
├── docs/
│   ├── wiring.md
│   └── power-and-safety.md
└── firmware/
    ├── smart_glove/
    │   └── smart_glove.ino
    ├── fsr402_test/
    │   └── fsr402_test.ino
    ├── mlx90614_test/
    │   └── mlx90614_test.ino
    └── hw072_test/
        └── hw072_test.ino
```

## Arduino libraries

Install through Arduino IDE → Library Manager:

- **Adafruit MLX90614** (for the MLX90614 sensor)
- **Adafruit BusIO** (dependency, normally installed automatically)

The FSR402 and HW-072 sketches use built-in Arduino functions and need no extra library.

## Pin map used by the starter firmware

| Arduino UNO pin | Function |
|---|---|
| A0 | FSR402 analog output / voltage-divider midpoint |
| A4 | MLX90614 SDA |
| A5 | MLX90614 SCL |
| D2 | HW-072 digital output |
| D8 | Buzzer driver input (optional) |
| D9 | LED output through 220 Ω resistor (optional) |

**Note:** A4/A5 are the UNO's I²C pins. If another I²C display is added later, it can share SDA/A4 and SCL/A5, provided its address and voltage compatibility are checked. The display is not assumed to be present.

## Getting started

1. Read [`docs/power-and-safety.md`](docs/power-and-safety.md) before connecting the battery.
2. Wire and test each sensor individually using the sketches in `firmware/`.
3. Install the Adafruit MLX90614 library.
4. Open `firmware/smart_glove/smart_glove.ino` in Arduino IDE.
5. Select **Arduino UNO**, select the correct port, upload, and open Serial Monitor at **9600 baud**.
6. Keep the FSR402 unloaded during startup calibration.

## FSR402 reading

The firmware reports:
- `fsr_raw`: Arduino ADC reading (0–1023).
- `pressure_score`: relative response from 0.0 to 100.0 after subtracting the startup baseline.

This score is **not** force in grams, Newtons, or pressure in kPa. FSRs are nonlinear and must be calibrated with known loads for physical-force estimates.

## Development notes

- Test sensors individually before integrating them.
- Calibrate the FSR402 with no load at startup and keep it untouched during calibration.
- Tune the HW-072 module's onboard potentiometer, if present, for the desired vibration sensitivity.
- Confirm the MLX90614 breakout's VIN range and I²C logic-level compatibility.
- Add thresholds and alerts only after readings are stable.
- This prototype is not a medical device or certified industrial safety system.

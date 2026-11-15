/*
  Multifunctional Smart Glove - Arduino UNO starter firmware

  Sensors:
    FSR402       -> A0 (10k voltage divider to GND)
    MLX90614     -> I2C: SDA=A4, SCL=A5
    HW-072       -> DO=D2

  Optional outputs:
    Buzzer driver input -> D8
    LED (through 220 ohm resistor) -> D9

  Serial Monitor: 9600 baud

  Required library:
    Adafruit MLX90614

  IMPORTANT:
    - Keep the FSR unloaded during startup baseline calibration.
    - pressure_score is a relative 0-100 score, NOT calibrated force.
    - Verify sensor breakout voltage compatibility before powering.
*/

#include <Wire.h>
#include <Adafruit_MLX90614.h>

const byte FSR_PIN = A0;
const byte VIBRATION_PIN = 2;
const byte BUZZER_PIN = 8;  // Optional: drives a transistor, not a high-current buzzer directly
const byte LED_PIN = 9;     // Optional LED through 220 ohm resistor

const bool ENABLE_BUZZER = false;
const bool ENABLE_LED = false;

// Change to LOW if your HW-072 module's DO output is active-LOW.
const byte VIBRATION_ACTIVE_STATE = HIGH;

const unsigned long SERIAL_INTERVAL_MS = 250;
const unsigned int FSR_SAMPLES = 20;
const unsigned int BASELINE_SAMPLES = 100;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

float fsrBaseline = 0.0;
bool mlxAvailable = false;
unsigned long lastPrint = 0;

float readFsrAverage() {
  unsigned long total = 0;
  for (unsigned int i = 0; i < FSR_SAMPLES; i++) {
    total += analogRead(FSR_PIN);
    delay(2);
  }
  return (float)total / FSR_SAMPLES;
}

void calibrateFsr() {
  Serial.println(F("FSR calibration: keep sensor completely unloaded."));
  delay(1500);

  unsigned long total = 0;
  for (unsigned int i = 0; i < BASELINE_SAMPLES; i++) {
    total += analogRead(FSR_PIN);
    delay(10);
  }

  fsrBaseline = (float)total / BASELINE_SAMPLES;
  Serial.print(F("FSR baseline = "));
  Serial.println(fsrBaseline, 1);
}

void setup() {
  Serial.begin(9600);
  pinMode(VIBRATION_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  Wire.begin();

  Serial.println(F("\nMultifunctional Smart Glove"));
  Serial.println(F("Starting sensors..."));

  mlxAvailable = mlx.begin();
  if (mlxAvailable) {
    Serial.println(F("MLX90614 detected."));
  } else {
    Serial.println(F("WARNING: MLX90614 not detected. Check VIN/GND/SDA/SCL."));
  }

  calibrateFsr();

  Serial.println(F("Ready. Serial output begins."));
  Serial.println(F("Columns: fsr_raw, pressure_score, object_C, ambient_C, vibration"));
}

void loop() {
  float fsrRaw = readFsrAverage();

  // Convert the increase above the unloaded baseline into a relative 0-100 score.
  float pressureScore = 0.0;
  float availableRange = 1023.0 - fsrBaseline;

  if (fsrRaw > fsrBaseline + 3.0 && availableRange > 0.0) {
    pressureScore = ((fsrRaw - fsrBaseline) / availableRange) * 100.0;
  }

  pressureScore = constrain(pressureScore, 0.0, 100.0);

  bool vibrationDetected =
      (digitalRead(VIBRATION_PIN) == VIBRATION_ACTIVE_STATE);

  if (ENABLE_LED) {
    digitalWrite(LED_PIN, vibrationDetected ? HIGH : LOW);
  }

  if (ENABLE_BUZZER) {
    digitalWrite(BUZZER_PIN, vibrationDetected ? HIGH : LOW);
  }

  if (millis() - lastPrint >= SERIAL_INTERVAL_MS) {
    lastPrint = millis();

    Serial.print(F("fsr_raw="));
    Serial.print(fsrRaw, 1);

    Serial.print(F(", pressure_score="));
    Serial.print(pressureScore, 1);

    if (mlxAvailable) {
      Serial.print(F(", object_C="));
      Serial.print(mlx.readObjectTempC(), 1);

      Serial.print(F(", ambient_C="));
      Serial.print(mlx.readAmbientTempC(), 1);
    } else {
      Serial.print(F(", object_C=NA, ambient_C=NA"));
    }

    Serial.print(F(", vibration="));
    Serial.println(vibrationDetected ? F("1") : F("0"));
  }
}


#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------------- OLED SETTINGS ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

// ---------------- SENSOR OBJECTS ----------------
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// ---------------- PIN CONFIGURATION ----------------
const byte VIBRATION_PIN = 2;
const byte FSR_PIN       = A0;
const byte BUZZER_PIN    = 8;

// HW-072 output observed LOW during vibration.
// Change to HIGH if your module behaves oppositely.
const byte VIBRATION_ACTIVE_LEVEL = LOW;

// Temperature warning threshold in Celsius.
// Adjust this threshold to suit your project demonstration.
const float TEMP_LIMIT_C = 40.0;

// ---------------- SENSOR STATUS ----------------
bool mlxAvailable = false;
bool oledAvailable = false;

// ---------------- VARIABLES ----------------
float objectTempC = 0.0;
float ambientTempC = 0.0;
int fsrRaw = 0;
float pressurePercent = 0.0;
bool vibrationDetected = false;

// ---------------- OLED DISPLAY ----------------
void showStartupMessage() {
  if (!oledAvailable) return;

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("MULTIFUNCTIONAL"));
  display.println(F("SMART GLOVE"));
  display.println();
  display.println(F("Initializing..."));
  display.display();
}

void showSensorError() {
  if (!oledAvailable) return;

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("SMART GLOVE"));
  display.println(F("----------------"));
  display.println(F("MLX90614 ERROR"));
  display.println(F("Check I2C wiring"));
  display.println(F("OLED is working"));
  display.display();
}

void updateOLED() {
  if (!oledAvailable) return;

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println(F("SMART GLOVE"));
  display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

  display.setCursor(0, 14);
  display.print(F("Object: "));
  if (mlxAvailable) {
    display.print(objectTempC, 1);
    display.println(F(" C"));
  } else {
    display.println(F("Sensor Error"));
  }

  display.setCursor(0, 26);
  display.print(F("Ambient: "));
  if (mlxAvailable) {
    display.print(ambientTempC, 1);
    display.println(F(" C"));
  } else {
    display.println(F("--"));
  }

  display.setCursor(0, 38);
  display.print(F("Pressure: "));
  display.print(pressurePercent, 1);
  display.println(F("%"));

  display.setCursor(0, 50);
  display.print(F("Vibration: "));
  display.println(
    vibrationDetected ? F("DETECTED") : F("NO")
  );

  display.display();
}

// ---------------- SERIAL MONITOR ----------------
void printSerialData() {
  Serial.println(F("------ SMART GLOVE ------"));

  if (mlxAvailable) {
    Serial.print(F("Object Temperature: "));
    Serial.print(objectTempC, 2);
    Serial.println(F(" C"));

    Serial.print(F("Ambient Temperature: "));
    Serial.print(ambientTempC, 2);
    Serial.println(F(" C"));
  } else {
    Serial.println(F("MLX90614: NOT AVAILABLE"));
  }

  Serial.print(F("FSR Raw Value: "));
  Serial.println(fsrRaw);

  Serial.print(F("Pressure Score: "));
  Serial.print(pressurePercent, 1);
  Serial.println(F("%"));

  Serial.print(F("Vibration: "));
  Serial.println(
    vibrationDetected ? F("DETECTED") : F("NOT DETECTED")
  );

  Serial.print(F("Temperature Alert: "));
  Serial.println(
    (mlxAvailable && objectTempC >= TEMP_LIMIT_C)
      ? F("WARNING")
      : F("NORMAL")
  );

  Serial.println(F("-------------------------"));
  Serial.println();
}

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(9600);

  pinMode(VIBRATION_PIN, INPUT_PULLUP);
  pinMode(FSR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);

  Wire.begin();

  // Initialize OLED
  oledAvailable = display.begin(
    SSD1306_SWITCHCAPVCC,
    OLED_ADDRESS
  );

  if (oledAvailable) {
    showStartupMessage();
  } else {
    Serial.println(F("OLED initialization failed."));
    Serial.println(F("Check OLED address and wiring."));
  }

  // Initialize MLX90614
  mlxAvailable = mlx.begin();

  if (mlxAvailable) {
    Serial.println(F("MLX90614 initialized."));
  } else {
    Serial.println(F("MLX90614 initialization failed."));
    showSensorError();
  }

  Serial.println();
  Serial.println(F("MULTIFUNCTIONAL SMART GLOVE"));
  Serial.println(F("System initialization complete."));
  Serial.println();
  delay(1500);
}

// ---------------- MAIN LOOP ----------------
void loop() {
  // Read temperature sensor
  if (mlxAvailable) {
    objectTempC = mlx.readObjectTempC();
    ambientTempC = mlx.readAmbientTempC();

    // Reject obviously invalid readings
    if (isnan(objectTempC) || isnan(ambientTempC)) {
      mlxAvailable = false;
    }
  }

  // Read FSR402
  fsrRaw = analogRead(FSR_PIN);

  // Convert ADC reading (0-1023) to a 0-100 score.
  // This is a percentage-style score, NOT calibrated force.
  pressurePercent = (fsrRaw / 1023.0) * 100.0;

  // Read vibration sensor
  vibrationDetected =
    (digitalRead(VIBRATION_PIN) == VIBRATION_ACTIVE_LEVEL);

  // Temperature warning controls the buzzer
  bool temperatureWarning =
    mlxAvailable && (objectTempC >= TEMP_LIMIT_C);

  digitalWrite(
    BUZZER_PIN,
    temperatureWarning ? HIGH : LOW
  );

  // Update OLED and Serial Monitor
  updateOLED();
  printSerialData();

  delay(300);
}

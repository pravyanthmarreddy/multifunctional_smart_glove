/*
  FSR402 standalone test - Arduino UNO
  Wiring:
    5V -> FSR402 -> A0 -> 10k resistor -> GND
  Serial Monitor: 9600 baud
*/

const byte FSR_PIN = A0;
const byte SAMPLE_COUNT = 20;
float baseline = 0;

int readAverage() {
  unsigned long total = 0;
  for (byte i = 0; i < SAMPLE_COUNT; i++) {
    total += analogRead(FSR_PIN);
    delay(2);
  }
  return total / SAMPLE_COUNT;
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("FSR402 test - leave sensor untouched for calibration"));

  unsigned long total = 0;
  for (int i = 0; i < 100; i++) {
    total += analogRead(FSR_PIN);
    delay(10);
  }
  baseline = total / 100.0;

  Serial.print(F("Baseline raw ADC: "));
  Serial.println(baseline, 1);
}

void loop() {
  int raw = readAverage();
  float score = 0.0;

  if (raw > baseline + 3.0) {
    score = ((raw - baseline) / (1023.0 - baseline)) * 100.0;
  }
  score = constrain(score, 0.0, 100.0);

  Serial.print(F("Raw ADC: "));
  Serial.print(raw);
  Serial.print(F(" | Relative pressure score: "));
  Serial.println(score, 1);

  delay(100);
}

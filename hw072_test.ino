/*
  HW-072 vibration module standalone test - Arduino UNO
  Wiring: VCC -> compatible supply, GND -> GND, DO -> D2.
  Serial Monitor: 9600 baud.

  If your module is active-LOW, change ACTIVE_STATE to LOW.
*/

const byte VIBRATION_PIN = 2;
const byte ACTIVE_STATE = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(VIBRATION_PIN, INPUT);
  Serial.println(F("HW-072 vibration sensor test"));
}

void loop() {
  int state = digitalRead(VIBRATION_PIN);

  if (state == ACTIVE_STATE) {
    Serial.println(F("Vibration detected"));
  } else {
    Serial.println(F("No vibration"));
  }

  delay(100);
}

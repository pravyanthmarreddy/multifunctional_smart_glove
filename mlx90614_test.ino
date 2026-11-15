/*
  MLX90614 standalone test - Arduino UNO
  Wiring: VIN/VCC -> compatible supply, GND -> GND,
          SDA -> A4, SCL -> A5.
  Install Adafruit MLX90614 library.
  Serial Monitor: 9600 baud.
*/

#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Serial.println(F("MLX90614 test"));

  if (!mlx.begin()) {
    Serial.println(F("MLX90614 not detected. Check wiring and voltage."));
    while (true) {
      delay(100);
    }
  }

  Serial.println(F("Sensor detected."));
}

void loop() {
  Serial.print(F("Object temperature: "));
  Serial.print(mlx.readObjectTempC(), 2);
  Serial.print(F(" C | Ambient temperature: "));
  Serial.print(mlx.readAmbientTempC(), 2);
  Serial.println(F(" C"));

  delay(500);
}

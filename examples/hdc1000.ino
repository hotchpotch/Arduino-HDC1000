
#include "HDC1000.h"

HDC1000 hdc1000;

void setup() {
  Serial.begin(9600);
  hdc1000.begin();
}

void loop() {
  float temp = hdc1000.getTemperature();
  Serial.print("Temperature: ");
  Serial.println(temp);
  float humi = hdc1000.getHumidity();
  Serial.print("Humidity: ");
  Serial.println(humi);
  delay(1000);
}



#include "HDC1000.h"

HDC1000 hdc1000;

void setup() {
  Serial.begin(9600);
  // hdc1000.setRdyPin(PIN_NO); // use Rdy Pin
  hdc1000.begin();
}

void loop() {
  float temp = hdc1000.getTemperature();

  if (temp == HDC1000_ERROR_CODE) {
    hdc1000.begin(); // retry once
    temp = hdc1000.getTemperature();
  }
  Serial.print("Temperature: ");
  Serial.println(temp);

  float humi = hdc1000.getHumidity();

  if (humi== HDC1000_ERROR_CODE) {
    hdc1000.begin(); // retry once
    humi = hdc1000.getTemperature();
  }

  Serial.print("Humidity: ");
  Serial.println(humi);
  delay(1000);
}



#include <Wire.h>
#include <Arduino.h>
#include "HDC1000.h"

HDC1000::HDC1000(int address)
{
  _address = address;
}

void HDC1000::begin()
{
  Wire.begin();
  configure();
}


void HDC1000::configure()
{
  delay(15);
  uint8_t commands[] = {
    HDC1000_CONFIGURATION_ADDRESS,
    0b00000000, // LBR MODE 0, 14-bit
    0b00000000
  };
  int i, length = sizeof(commands);

  Wire.beginTransmission(_address);
  for (i = 0; i < length; i++) {
    Wire.write(commands[i]);
  }
  Wire.endTransmission(_address);
}

float HDC1000::getTemperature()
{
  uint16_t data = getData(HDC1000_TEMP_ADDRESS);

  if (data == HDC1000_ERROR_CODE) {
    return HDC1000_ERROR_CODE;
  }

  return (data / 65536.0 * 165) - 40;
}

float HDC1000::getHumidity()
{
  uint16_t data = getData(HDC1000_HUMI_ADDRESS);

  if (data == HDC1000_ERROR_CODE) {
    return HDC1000_ERROR_CODE;
  }

  return data / 65536.0 * 100;
}

uint16_t HDC1000::getData(uint8_t address)
{
  uint16_t data;

  Wire.beginTransmission(_address);
  Wire.write(address);
  Wire.endTransmission(_address);

  delay(7);

  Wire.requestFrom(_address, (uint8_t)2);
  data = Wire.read() << 8;
  Serial.println(data);
  data = data | Wire.read();
  Serial.println(data);

  return data;
}

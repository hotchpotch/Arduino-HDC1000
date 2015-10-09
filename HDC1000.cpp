
#include <Wire.h>
#include <Arduino.h>
#include "HDC1000.h"

HDC1000::HDC1000(uint8_t address)
{
  _rdy_pin = -1;
  _address = address;
}

void HDC1000::setRdyPin(int8_t rdy_pin)
{
  _rdy_pin = rdy_pin;
  if (_rdy_pin != HDC1000_RDY_PIN_DISABLE) {
    pinMode(_rdy_pin, INPUT);
  }
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
  uint8_t i, length = sizeof(commands);

  Wire.beginTransmission(_address);
  for (i = 0; i < length; i++) {
    Wire.write(commands[i]);
  }
  Wire.endTransmission(_address);

  setRdyPin(_rdy_pin);
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

  if (_rdy_pin == HDC1000_RDY_PIN_DISABLE) {
    delay(7);
  } else {
    // wait rdy pin == L
    uint16_t wait_count = 0;
    while (digitalRead(_rdy_pin) == HIGH) {
      if (wait_count++ == 50000) {
        return HDC1000_ERROR_CODE;
      }
    }
  }

  Wire.requestFrom(_address, (uint8_t)2);
  data = Wire.read() << 8;
  data = data | Wire.read();

  return data;
}

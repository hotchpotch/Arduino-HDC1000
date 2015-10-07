
#ifndef __HDC1000_H__
#define __HDC1000_H__

#define HDC1000_DEFAULT_ADDRESS 0x40
#define HDC1000_CONFIGURATION_ADDRESS 0x02
#define HDC1000_TEMP_ADDRESS 0x00
#define HDC1000_HUMI_ADDRESS 0x01
#define HDC1000_ERROR_CODE 65535
#define HDC1000_RDY_PIN_DISABLE -1

class HDC1000
{
private:
  uint8_t _address;
  int8_t _rdy_pin;
public:
  HDC1000(uint8_t address = HDC1000_DEFAULT_ADDRESS);
  void begin();
  void configure();
  void setRdyPin(int8_t rdy_pin);
  float getTemperature();
  float getHumidity();
  uint16_t getData(uint8_t address);
};

#endif  // __HDC1000_H__


#ifndef __HDC1000_H__
#define __HDC1000_H__

#define HDC1000_DEFAULT_ADDRESS 0x40
#define HDC1000_CONFIGURATION_ADDRESS 0x02
#define HDC1000_TEMP_ADDRESS 0x00
#define HDC1000_HUMI_ADDRESS 0x01

class HDC1000
{
private:
  uint8_t _address;
public:
  HDC1000(int address = HDC1000_DEFAULT_ADDRESS);
  void begin();
  void configure();
  float getTemperature();
  float getHumidity();
};

#endif  // __HDC1000_H__

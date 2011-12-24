/*
  MAX31855.h - Library for reading temperature from a MAX31855.
  
  This work is licensed under a Creative Commons Attribution-ShareAlike 3.0 Unported License.
  http://creativecommons.org/licenses/by-sa/3.0/
*/

#include <Arduino.h>

class MAX31855 {
 public:
  MAX31855(int SCK_pin, int CS_pin, int SO_pin, bool temp_unit);
  bool readMAX31855(double *tempTC, double *tempCJC, bool *faultOpen, bool *faultShortGND, bool *faultShortVCC);
  double readCelsius(void);
  double readFahrenheit(void);
  double readCJC(void);
  int readFaultCode(void);
 private:
  int _sck_pin, _cs_pin, _so_pin;
  bool _temp_unit;
  long spiread32(void);
  long spiread16(void);
};

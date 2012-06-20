/*
   MAX31855.h - Library for reading temperature from a MAX31855.

   This work is licensed under a Creative Commons Attribution-ShareAlike 3.0 Unported License.
http://creativecommons.org/licenses/by-sa/3.0/
*/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class MAX31855 {
        public:
                MAX31855(int SCK_pin, int CS_pin, int SO_pin);
                bool readMAX31855(double *tempTC, double *tempCJC, bool *faultOpen, bool *faultShortGND, bool *faultShortVCC, bool temp_unit);
                double readCelsius(void);
                double readFahrenheit(void);
                double readCJC(void);
                int readFaultCode(void);
        private:
                int _sck_pin, _cs_pin, _so_pin;
                long spiread32(void);
                int spiread16(void);
                void spiread32(int *tc, int *cjc);
};

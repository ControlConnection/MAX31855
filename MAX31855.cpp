/*
   MAX31855.cpp - Library for reading temperature from a MAX31855.

   This work is licensed under a Creative Commons Attribution-ShareAlike 3.0
   Unported License.  http://creativecommons.org/licenses/by-sa/3.0/
*/

#include "MAX31855.h"

MAX31855::MAX31855(int SCK_pin, int CS_pin, int SO_pin) {
        _sck_pin = SCK_pin;
        _cs_pin = CS_pin;
        _so_pin = SO_pin;

        //define pin modes
        pinMode(_cs_pin, OUTPUT);
        pinMode(_sck_pin, OUTPUT);
        pinMode(_so_pin, INPUT);
        digitalWrite(_cs_pin, HIGH);
}


double MAX31855::readCelsius(void) {
        int v;
        v = spiread16();
        //if fault bit set // return 2000deg

        if (v & 0x1) {
                return 2000;
        }

        v&=0xfffc; // mask lower two bits
        return v / 16.0;
}


double MAX31855::readFahrenheit(void) {
        return readCelsius() * 9.0/5.0 + 32;
}


double MAX31855::readCJC(void) {
        int tc, cjc;
        spiread32(&tc, &cjc);
        return (cjc & 0xfff0)  / 256.0;
}



int MAX31855::readFaultCode(void) {
        return (spiread32() & 0x7) ; // return low 3 bits
}


long MAX31855::spiread32(void) {
        int i;
        long d = 0; // we only need last 16 bits, first 16 will be discarded
        digitalWrite(_cs_pin, LOW);

        for (i=31; i>=0; i--) {
                digitalWrite(_sck_pin, LOW);
                if (digitalRead(_so_pin))
                        d |= (1 << i);
                digitalWrite(_sck_pin, HIGH);
        }

        digitalWrite(_cs_pin, HIGH);
        return d;
}

void MAX31855::spiread32(int *tc, int *cjc) {
        int i;
        *tc = *cjc =  0;
        digitalWrite(_cs_pin, LOW);

        for (i=15; i>=0; i--) {
                digitalWrite(_sck_pin, LOW);

                if (digitalRead(_so_pin)) {
                        *tc |= (1 << i);
                }

                digitalWrite(_sck_pin, HIGH);
        }

        for (i=15; i>=0; i--) {
                digitalWrite(_sck_pin, LOW);

                if (digitalRead(_so_pin)) {
                        *cjc |= (1 << i);
                }

                digitalWrite(_sck_pin, HIGH);
        }

        digitalWrite(_cs_pin, HIGH);
}

int MAX31855::spiread16(void) {
        int i;
        int d = 0;
        digitalWrite(_cs_pin, LOW);

        for (i=15; i>=0; i--) {
                digitalWrite(_sck_pin, LOW);

                if (digitalRead(_so_pin)) {
                        d |= (1 << i);
                }

                digitalWrite(_sck_pin, HIGH);
        }

        digitalWrite(_cs_pin, HIGH);

        return d;
}


bool MAX31855::readMAX31855(double *tempTC, double *tempCJC, bool *faultOpen, bool *faultShortGND, bool *faultShortVCC, bool temp_unit){
        int tc = 0;
        int cjc = 0;
        bool fault = false;

        spiread32(&tc, &cjc);

        if (tc & 0x1) {
                fault=true;
                *tempTC =9999;
        } else {
                tc&=0xfffc; // mask lower two bits
                *tempTC = tc / 16.0;

                if(temp_unit == 1) {
                        *tempTC = *tempTC * 9.0/5.0 + 32;
                }
        }

        *faultOpen = (cjc & 0x1) ? true : false  ;
        *faultShortGND = ((cjc>>1) & 0x1) ? true : false;
        *faultShortVCC = ((cjc>>2) & 0x1) ? true : false;
        cjc = cjc & 0xfff0;// mask lower 4 bits
        *tempCJC = cjc / 256.0;

        if(temp_unit == 1) {
                *tempCJC = *tempCJC * 9.0/5.0 + 32;
        }

        return fault;
}


/*
  MAX31855.cpp - Library for reading temperature from a MAX31855.
  
  This work is licensed under a Creative Commons Attribution-ShareAlike 3.0 Unported License.
  http://creativecommons.org/licenses/by-sa/3.0/
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
  long v;
  v = spiread16();
   //if fault bit set // return 2000deg
  if (v & 0x1) 
	  return 2000;    
  v&=0xfffc; // mask lower two bits
  return v / 16.0;
}


double MAX31855::readFahrenheit(void) {
 	return readCelsius() * 9.0/5.0 + 32;
}


double MAX31855::readCJC(void) {
  long v;
  v = spiread32() & 0xfff0;
  return v / 256.0;
}


int MAX31855::readFaultCode(void) {
	return (spiread32() & 0x7) ; // return low 3 bits   	
}


long MAX31855::spiread32(void) { 
  int i;
  long d = 0; // we only need last 16 bits, first 16 will be discarded
   digitalWrite(_cs_pin, LOW);
  for (i=31; i>=0; i--)
	  {
		digitalWrite(_sck_pin, LOW);
		if (digitalRead(_so_pin))   
			d |= (1 << i);
		digitalWrite(_sck_pin, HIGH);
	  }
	digitalWrite(_cs_pin, HIGH);

  return d; 
}


long MAX31855::spiread16(void) { 
  int i;
  long d = 0;
  digitalWrite(_cs_pin, LOW);
  for (i=15; i>=0; i--)
  {
	digitalWrite(_sck_pin, LOW);
	if (digitalRead(_so_pin))
		d |= (1 << i);
	digitalWrite(_sck_pin, HIGH);
  }
  digitalWrite(_cs_pin, HIGH);

  return d; 
}


bool MAX31855::readMAX31855(double *tempTC, double *tempCJC, bool *faultOpen, bool *faultShortGND, bool *faultShortVCC, bool temp_unit){
	int i;
	long d = 0;
	long v = 0;
	bool fault = false;

	digitalWrite(_cs_pin, LOW);
	for (i=15; i>=0; i--)
		{
		digitalWrite(_sck_pin, LOW);
		if (digitalRead(_so_pin))
			d |= (1 << i);
		digitalWrite(_sck_pin, HIGH);
		}
	for (i=15; i>=0; i--)
		{
		digitalWrite(_sck_pin, LOW);
		if (digitalRead(_so_pin))
			v |= (1 << i);
		digitalWrite(_sck_pin, HIGH);
		}
	digitalWrite(_cs_pin, HIGH);
	
	if (d & 0x1)
	{
		fault=true;
		*tempTC =9999;
	} 
	else
	{
		d&=0xfffc; // mask lower two bits
		*tempTC = d / 16.0;
		if(temp_unit == 1) {
			*tempTC = *tempTC * 9.0/5.0 + 32;
		}
	}
	
	*faultOpen = (v & 0x1) ? true : false  ;
	*faultShortGND = ((v>>1) & 0x1) ? true : false;
	*faultShortVCC = ((v>>2) & 0x1) ? true : false;

	v = v & 0xfff0;// mask lower 4 bits
	*tempCJC = v / 256.0;
	if(temp_unit == 1) {
		*tempCJC = *tempCJC * 9.0/5.0 + 32;
	}

	return fault;
}

/*
  read_MAX31855.pde - Demo of library usage.

  TODO: 
	Clean up code and comment!!  
	Also make use of all library functions and make more robust.
  
  This work is licensed under a Creative Commons Attribution-ShareAlike 3.0 Unported License.
  http://creativecommons.org/licenses/by-sa/3.0/
*/

#include <MAX31855.h>

double tempTC, tempCJC;
bool faultOpen, faultShortGND, faultShortVCC, x;
int SCK_pin = 13;
int SO_pin = 12;
int CS_pin = 10;
bool temp_unit = 1;  // 0 = Celsius, 1 = Fahrenheit

MAX31855 temp(SCK_pin, CS_pin, SO_pin, temp_unit);

void setup() {
  Serial.begin(9600);
}

void loop() {
  x = temp.readMAX31855(&tempTC, &tempCJC, &faultOpen, &faultShortGND, &faultShortVCC);
  
    Serial.print(tempTC);
    Serial.print("\t");
    Serial.print(tempCJC);
    Serial.print("\t");
    Serial.print(faultOpen);
    Serial.print(faultShortGND);
    Serial.println(faultShortVCC); 
  
  delay(1000);
}
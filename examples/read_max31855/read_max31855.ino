/*
  read_MAX31855.ino

  TODO: 
	Clean up code and comment!!  
	Also make use of all library functions and make more robust.
  
  This work is licensed under a Creative Commons Attribution-ShareAlike 3.0 Unported License.
  http://creativecommons.org/licenses/by-sa/3.0/
*/

#include <MAX31855.h>

// Adruino 1.0 pre-defines these variables
#if ARDUINO < 100
int SCK = 13;
int MISO = 12;
int SS = 10;
#endif
int LED = 9;

// Setup the variables we are going to use.
double tempTC, tempCJC;
bool faultOpen, faultShortGND, faultShortVCC, x;
bool temp_unit = 1;  // 0 = Celsius, 1 = Fahrenheit

// Init the MAX31855 library for the chip.
MAX31855 temp(SCK, SS, MISO);

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  x = temp.readMAX31855(&tempTC, &tempCJC, &faultOpen, &faultShortGND, &faultShortVCC, temp_unit);
  
    Serial.print(tempTC);
    Serial.print("\t");
    Serial.print(tempCJC);
    Serial.print("\t");
    Serial.print(faultOpen);
    Serial.print(faultShortGND);
    Serial.println(faultShortVCC); 
  
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}
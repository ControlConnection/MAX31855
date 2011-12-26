/*
  multi_MAX31855.ino

  Demo code for reading 4 MAX31855 chips.  
  Can be used with Quad shield.

  This work is licensed under a Creative Commons Attribution-ShareAlike 3.0 Unported License.
  http://creativecommons.org/licenses/by-sa/3.0/
*/

#include <MAX31855.h>

// Adruino 1.0 pre-defines these variables
#if ARDUINO < 100
int SCK = 13;
int MISO = 12;
#endif

double tempTC[4], tempCJC[4], tempTCf[4];
int CS1 = 10;
int CS2 = 9;
int CS3 = 8;
int CS4 = 7;
int LED = 6;
bool temp_unit = 1;  // 0 = Celsius, 1 = Fahrenheit

MAX31855 temp1(SCK, CS1, MISO);
MAX31855 temp2(SCK, CS2, MISO);
MAX31855 temp3(SCK, CS3, MISO);
MAX31855 temp4(SCK, CS4, MISO);

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  
  tempTC[0] = temp1.readCelsius();
  tempTCf[0] = temp1.readFahrenheit();
  tempCJC[0] = temp1.readCJC();
  tempTC[1] = temp2.readCelsius();
  tempTCf[1] = temp2.readFahrenheit();
  tempCJC[1] = temp2.readCJC();
  tempTC[2] = temp3.readCelsius();
  tempTCf[2] = temp3.readFahrenheit();
  tempCJC[2] = temp3.readCJC();
  tempTC[3] = temp4.readCelsius();
  tempTCf[3] = temp4.readFahrenheit();
  tempCJC[3] = temp4.readCJC();
  
  for(int i=0; i<4; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(tempTC[i]);
    Serial.print("/");
    Serial.print(tempTCf[i]);
    Serial.print("\t");
    Serial.println(tempCJC[i]);
  }
  
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}
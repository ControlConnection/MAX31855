/*
  read_multi_MAX31855.pde - Demo of library usage.

  Demo code for use with Quad shield
*/

#include <MAX31855.h>

double tempTC[4], tempCJC[4];

int SCK_pin = 13;
int SO_pin = 12;
int CS1 = 10;
int CS2 = 9;
int CS3 = 8;
int CS4 = 7;
bool temp_unit = 1;  // 0 = Celsius, 1 = Fahrenheit

MAX31855 temp1(SCK_pin, CS1, SO_pin, temp_unit);
MAX31855 temp2(SCK_pin, CS2, SO_pin, temp_unit);
MAX31855 temp3(SCK_pin, CS3, SO_pin, temp_unit);
MAX31855 temp4(SCK_pin, CS4, SO_pin, temp_unit);

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  tempTC[0] = temp1.readCelsius();
  tempCJC[0] = temp1.readCJC();
  tempTC[1] = temp2.readCelsius();
  tempCJC[1] = temp2.readCJC();
  tempTC[2] = temp3.readCelsius();
  tempCJC[2] = temp3.readCJC();
  tempTC[3] = temp4.readCelsius();
  tempCJC[3] = temp4.readCJC();
  
  for(int i=0; i<4; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(tempTC[i]);
    Serial.print("\t");
    Serial.println(tempCJC[i]);
  }
  
  delay(1000);
}

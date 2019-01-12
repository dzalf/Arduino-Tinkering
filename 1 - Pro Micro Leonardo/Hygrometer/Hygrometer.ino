//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>


int humidity  = 0;
const int sensor = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  establishContact(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    humidity = analogRead(sensor);
    Serial.print(humidity);
    delay(20);
  }
}
void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("0,0,0");   // send an initial string
    delay(300);
  }
}

#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define rxPin 10
#define txPin 11
#define flagLED 13
#define ONE_WIRE_BUS 2

float temp  = 0.0;

SoftwareSerial BTSerial =  SoftwareSerial(rxPin, txPin);
OneWire oneWire(ONE_WIRE_BUS);
//DeviceAddress tempDeviceAddress;
DallasTemperature sensors(&oneWire);

void setup() {

  BTSerial.begin(115200); // bleSerial 2 & 3 Arduino UNO - DUEMILANOVE
  //Serial.begin(115200);
  sensors.begin();
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(flagLED, OUTPUT);

  

}

void loop() {
  digitalWrite(flagLED, HIGH);
  
  sensors.requestTemperatures(); // Send the command to get temperature readings
  temp = sensors.getTempCByIndex(0);

  BTSerial.print(temp);
  BTSerial.print("\n");
  
  digitalWrite(flagLED, LOW);
  delay(500);
}

//void bleSerialEvent() {
//
//  while (bleSerial.available() && stringComplete == false)  {
//    digitalWrite(flagLED, HIGH);
//    inChar = (char)bleSerial.read();
//
//    if (inChar == 0x0A) { //READ LINE FEED
//
//      stringComplete = true;
//
//    }
//
//  }

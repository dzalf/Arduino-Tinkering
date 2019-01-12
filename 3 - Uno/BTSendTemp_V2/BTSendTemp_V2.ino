#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define rxPin 8
#define txPin 10
#define flagLED 13
#define statusLED 12
#define BTeventLED 9

#define ONE_WIRE_BUS 2

float temp  = 0.0;
boolean stringComplete = false;
String inString = "";
char inChar = ' ';

SoftwareSerial BTSerial =  SoftwareSerial(rxPin, txPin);
OneWire oneWire(ONE_WIRE_BUS);
//DeviceAddress tempDeviceAddress;
DallasTemperature sensors(&oneWire);

void BTSerialEvent() {

  while (BTSerial.available() && stringComplete == false)  {
    digitalWrite(BTeventLED, HIGH);

    inChar = (char)BTSerial.read();

    if (inChar == 0x0A) { //READ LINE FEED
      BTSerial.print("Received...");
      BTSerial.print(inString);
      BTSerial.print("\n");
      stringComplete = true;
    }
    inString += inChar;
  }
  if (stringComplete == true) {

    if ((inString[0] == 'O') && (inString[1] == 'N') ) {

      digitalWrite(BTeventLED, LOW);
      digitalWrite(statusLED, HIGH);
      inString = "";
      BTSerial.print(" Led ON!");
      BTSerial.print("\n");
      //inChar = ' ';
    } else if ((inString[0] == 'O') && (inString[1] == 'F') && (inString[2] == 'F') ) {

      digitalWrite(BTeventLED, LOW);
      digitalWrite(statusLED, LOW);
      inString = "";
      BTSerial.print(" Led OFF!");
      BTSerial.print("\n");
      //inChar = '';
    } else {
      inString = "";
      //start = false;
      digitalWrite(BTeventLED, LOW);
      BTSerial.print(" Wrong command ");
      BTSerial.print("\n");
    }
  }
}

void setup() {

  BTSerial.begin(115200); // bleSerial 2 & 3 Arduino UNO - DUEMILANOVE
  //Serial.begin(115200);
  sensors.begin();
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(flagLED, OUTPUT);
  pinMode(statusLED, OUTPUT);
  pinMode(BTeventLED, OUTPUT);
  digitalWrite(statusLED, LOW);
  digitalWrite(flagLED, LOW);
  digitalWrite(BTeventLED, LOW);
}

void loop() {

  stringComplete = false;
  if (BTSerial.available()) {
    BTSerialEvent();
  }

  digitalWrite(flagLED, HIGH);

  sensors.requestTemperatures(); // Send the command to get temperature readings
  temp = sensors.getTempCByIndex(0);

  BTSerial.print("Temperature now: ");
  BTSerial.print(temp);
  BTSerial.print("\n");

  digitalWrite(flagLED, LOW);
  delay(500);

}



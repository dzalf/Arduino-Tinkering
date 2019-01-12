//#include <Wire.h>

#include <LiquidCrystal.h>
//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 15
#define ledRed  11
#define ledYellow  12
#define ledGreen  13
#define lux  16
//#define PWMPin = 10
#define pump  10 //PWM
#define buzzer  3 //PWM
#define sensorHumidity  A0
//#define TEMPERATURE_PRECISION 9
//#define sensorTemp = A1;

LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
OneWire oneWire(ONE_WIRE_BUS);
//DeviceAddress tempDeviceAddress;
DallasTemperature sensors(&oneWire);


float humidity  = 0.0;
float temp  = 0.0;
int raw;
//int dallasDevice = 0;
int control;
int PWMOn = 127;
int PWMOff = 0;
boolean luxVal = false;
boolean initFlag = false;
boolean critical = false;

void beep(int repeat, int time) {
  lcd.setCursor(1, 1);
  lcd.write("VERIFY PUMP!");
  for (int i = 0; i < repeat; i++) {
    analogWrite(buzzer, PWMOn);
    delay(time);
    analogWrite(buzzer, PWMOff);
  }
  lcd.clear();
}

void setup() {
  lcd.begin(16, 2);
  Serial.begin(115200);
  sensors.begin();

  Serial.println("Dallas Temperature IC Control Library Demo");
  // Search the wire for address
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(lux, INPUT);
  pinMode(sensorHumidity, INPUT);
  //pinMode(sensorTemp, INPUT);
  analogWrite (pump, PWMOff);
  humidity = 100.0;
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledYellow, HIGH);
  digitalWrite(ledGreen, HIGH);
  delay(2000);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, LOW);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.write("Hygrometer V0.3");

  if (initFlag == false) {
    lcd.setCursor(1, 1);
    lcd.write("Initializing...");
    analogWrite(pump, PWMOn);
    delay(500);
    analogWrite(pump, PWMOff);
    delay(500);
    lcd.clear();
    initFlag = true;
  }

  raw = analogRead(sensorHumidity);
  humidity = map(raw, 1023, 250, 0, 100);
  control = constrain(humidity, 0, 255);

  sensors.requestTemperatures(); // Send the command to get temperature readings
  temp = sensors.getTempCByIndex(0);

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.print("; ");
  Serial.print("Temp = ");
  Serial.print(temp);
  Serial.print("\n");

  if ((humidity >= 50.0) && (humidity <= 99.9)) {
  analogWrite(pump, PWMOff);
    if (critical == true) {


      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.write("Hygrometer V0.3");
      analogWrite (pump, PWMOff);
      lcd.setCursor(1, 4);
      lcd.write(" PUMP OFF!!");
      delay(3000);
      lcd.clear();
      critical = false;
    }

    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("H= ");
    lcd.print(humidity, 1);
    lcd.print("%");
    lcd.print(" T= ");
    lcd.print(temp, 1);
  } else if ((humidity > 10.0) && (humidity <= 49.0)) {
    
    analogWrite(pump, PWMOn);
    
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, HIGH);

    critical = false;

    lcd.setCursor(0, 1);
    lcd.write("H= ");
    lcd.print(humidity, 1);
    lcd.write("%");
    lcd.write("T = ");
    lcd.print(temp, 1);

  } else if ((humidity >= 0.0) && (humidity <= 10 )) {

    critical = true;
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);

    if (humidity < 5.0) {
      beep(3, 500);
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.write("Hygrometer V0.3");
      analogWrite (pump, PWMOn);
      lcd.setCursor(1, 4);
      lcd.write(" PUMP ON!");
      //delay(500);
      //lcd.clear();
    }
  }

  if (digitalRead(lux) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write("Hygrometer V0.3");
    lcd.setCursor(1, 4);
    lcd.write(" Is daylight! ");
    delay(1000);
  }

  delay(1);
}



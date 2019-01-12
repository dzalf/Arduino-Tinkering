//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
//#include <SoftwareSerial.h>


float humidity  = 0;
int raw;
int control;

const int sensor = A0;
const int PWMPin = 9;
const int pump = 8;
const int pulseOut = 6;
int PWMOn = 127;
int PWMOff = 0;

void setup() {
  pinMode(pump, OUTPUT);
  digitalWrite (pump, LOW);
  humidity = 100.0;
  //  Serial.begin(9600);
}

void loop() {

    raw = analogRead(sensor);
    humidity = map(raw, 1023, 250, 0, 100);
    control = constrain(humidity, 0, 255);
    analogWrite(PWMPin, control);
    delay(10);

    if (humidity < 10.0) {
      digitalWrite (pump, HIGH);
    } else {
      digitalWrite (pump, LOW);
    }
    if (humidity < 5.0) {
      beep(3, 500);
    }
  
}

void beep(int repeat, int time) {
  for (int i = 0; i < repeat; i++) {
    analogWrite(pulseOut, PWMOn);
    delay(time);
    analogWrite(pulseOut, PWMOff);
  }
}

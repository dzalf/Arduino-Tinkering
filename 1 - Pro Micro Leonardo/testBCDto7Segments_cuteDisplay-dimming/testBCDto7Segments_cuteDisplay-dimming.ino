#include <LM95071.h>

float temperature;
int intensity;
int SSP = 17;
int dimPin = 10;
int potDim = A3;

int outputs[4] = {6, 7, 8, 9}; // A,B,C,D inputs
int number = 0;
int cathodes[3] = {5, 4, 3};
byte cathodeOn[3][3] = {{HIGH, LOW, LOW}, {LOW, HIGH, LOW}, {LOW, LOW, HIGH}};
int pointer = 2;
int val;
int num[3] = {0, 0, 0};

byte BCD[10][4] = {
  {0, 0, 0, 0},
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {1, 1, 0, 0},
  {0, 0, 1, 0},
  {1, 0, 1, 0},
  {0, 1, 1, 0},
  {1, 1, 1, 0},
  {0, 0, 0, 1},
  {1, 0, 0, 1},
}; //BCD code

LM95071 SPI_Sensor(SSP, DEBUG_OFF);

void setup() {

  Serial.begin(115200);
  for (int i = 0; i < 4; i++) {
    pinMode(outputs[i], OUTPUT);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(cathodes[i], OUTPUT);
  }

  for (int anode = 0; anode < 4; anode++) {
    digitalWrite(outputs[anode], BCD[0][anode]);
  }


  for (int index = 0; index < 4; index++) {
    digitalWrite(cathodes[index], LOW);
  }
  pinMode(intensity, OUTPUT);
  SPI_Sensor.begin();
}

void loop() {

  intensity =  map(analogRead(potDim), 10,1010,80,255);
  
  analogWrite(dimPin, intensity);
  
  temperature =  SPI_Sensor.getTemperature();

//  Serial.print("Current temp = ");
//  Serial.println(temperature);
//  Serial.print(char(194));
//  Serial.println("C");
  
  num[0] =  (unsigned int)(temperature * 10)  % 10;
  num[1] = ((unsigned int)(temperature * 10 / 10)) % 10;
  num[2] = ((unsigned int)(temperature * 10 / 100)) % 10;

  for (int numIndex = 0; numIndex < 3; numIndex++) {
    for (int catIndex = 0; catIndex < 3; catIndex++) {
      digitalWrite(cathodes[catIndex], cathodeOn[numIndex][catIndex]);
    }
    for (int anode = 0; anode < 4; anode++) {
      digitalWrite(outputs[anode], BCD[num[numIndex]][anode]);
    }
    delay(10);
  }
}



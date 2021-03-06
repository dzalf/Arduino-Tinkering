#include "LM95071.h"

float temperature;
int SSP = 17;
int LED = 2;

LM95071 SPI_Sensor(SSP, DEBUG_OFF);

void setup() {

  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  SPI_Sensor.begin();
}


void loop() {

  delay(150);
  temperature =  SPI_Sensor.getTemperature();

  Serial.print("Current temp = ");
  Serial.print(temperature);
  Serial.print(char(194));
  Serial.println("C");

  digitalWrite(LED, HIGH);
  delay(50);

  digitalWrite(LED, LOW);
  delay(150);

}

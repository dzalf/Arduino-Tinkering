//Enviar datos con módulo Blutooth para Arduino

#include <SoftwareSerial.h>

SoftwareSerial blue= SoftwareSerial(10,11);

int pot(0);
int led = 13;

void setup() {
  // put your setup code here, to run once:

    blue.begin(9600);
    
//    while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
    digitalWrite(led, HIGH);
//  }
    blue.println("Conectado");
//    digitalWrite(led,LOW);
delay(2500);
}

void loop() {
  // put your main code here, to run repeatedly: 
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);               // wait for a second
                 // wait for a second
  pot=analogRead(0);
  blue.println(pot);
  
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(250);
  
}

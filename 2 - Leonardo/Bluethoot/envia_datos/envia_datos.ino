
//Recibir datos con modulo Bluetooth para Arduino http://zygzax.com/
//#include <SoftwareSerial.h>
//#define rxPin 10
//#define txPin 11
int ledPin = 13;
char rec;
//SoftwareSerial blue =  SoftwareSerial(rxPin, txPin);

void setup(){
  //pinMode(rxPin,INPUT);
  //pinMode(txPin,OUTPUT);
  pinMode(ledPin,OUTPUT);
  Serial1.begin(9600);
 while(!Serial1){
    ;
 }
  Serial1.println("Listo para direccionar datos");
 delay(1000);
  Serial1.println("Conectado");
delay(1000);
}

void loop() {
 
  while(Serial1.available()>0){
    rec=Serial1.read(); 
  
  
    switch(rec){
      case '0':
        digitalWrite(ledPin,LOW);
        delay(150);
        Serial1.println("Led off");
        break;
      case '1':
        digitalWrite(ledPin,HIGH);
        delay(150);
        Serial1.println("Led on");
        break;
      default:
        delay(150);
        Serial1.print(rec);
        Serial1.println(" no es una orden valida. Introduzca 0 o 1");
    }
  }   
}


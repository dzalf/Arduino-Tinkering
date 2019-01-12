//Recibir datos con modulo Bluetooth para Arduino http://zygzax.com/

#include <Servo.h>

Servo motor;

int a=0;

void setup(){
  
  Serial1.begin(9600);
  motor.attach(3);
}

byte contador = 0;
char cadena[24];
int posicion = 0;

void loop(){
 
  for(a; a<1; a++){
    Serial1.print("Angulo deseado [0-180] -> ");
  }
  
 if(Serial1.available()){
   memset(cadena, 0, sizeof(cadena));
   
   while (Serial1.available()>0){
     delay(5);
     cadena[contador]=Serial1.read();
     contador++;
   }
      posicion=atoi(cadena);
      posicion = min(posicion, 180);
      posicion = max(posicion, 0);
      Serial1.print(posicion);
      Serial1.println("   grados"); 
      motor.write(posicion);
      a=0;
      contador=0;      
      delay(100); 
 }
}


#include <Servo.h>


Servo myservo;

int pos = 0;
int a;

void setup() {
  Serial1.begin(9600);
  myservo.attach(3);
}

char cadena[24];
byte contador=0;
int valor = 0;
void loop(){

  for(a; a<1; a++){
    Serial1.print("Introduzca posicion de servo :");
  }  

  if(Serial1.available()){
    memset(cadena, 0, sizeof(cadena));

    while (Serial1.available()>0){
      delay(5);
      cadena[contador]=Serial1.read();
      contador++;
    }
    valor=atoi(cadena); 
    valor = min(valor, 180);       //establece valor maximo
    valor = max(valor, 0);          //establece valor minimo
    Serial1.print(valor);               //imprime en pantalla el valor introducido
    Serial1.println(" grados");
    myservo.write(valor);           //establece el valor como posicion myservo
    a=0;                                    //reiniciamos a para volver a mostrar aviso para introduccion de datos
    contador=0;
    delay(100);     
  }
}

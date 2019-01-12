
float R1 = 0.988e6;                 //Este resistor es el que junto con C1 determina la constante de tiempo

float C1 = 0;                       //Aquí guardaremos la capacidad medida.
float calCap = 0;
float CFinal = 0;
float acum = 0;
int i = 0;
int samples;
byte flag = 0;

int ledPin = 10;         //terminal al que conectamos un led que encenderemos lo que dure el pulso de entrada.
int ledCalibrate = 16;
int triggerPin = 5;

long tInit = 0;        //Guardamos el instante de inicio.
long tFinal = 0;         //Guardamos el instante del final del pulso.
long T = 0;                         //Duración del pulso

const byte interruptFALL = 0;
const byte interruptRISE = 1;

void start() {
  tInit = micros();                //millis me da el tiempo transcurrido desde que el programa inicio su ejecucion.
  digitalWrite(ledPin, HIGH);        //Encendemos el led como indicador de que la interrupcion fue activada.
}

void stop() {
  tFinal = micros();                 //Guardamos el tiempo retornado por millis().

  digitalWrite(ledPin, LOW);         //Apagamos el led indicando el final del pulso
}

void displayValue(float CFinal) {
  Serial.print("C = ");
  Serial.print(CFinal);        //Convertimos a picoFaradios
  Serial.print(" pF");
//  Serial.print("\t");        //Convertimos a picoFaradios
//  Serial.print("CalCap = ");
//  Serial.print(calCap);        //Convertimos a picoFaradios
//  Serial.print(" pF");
  Serial.print("\n");

}

void trigger( int milliseconds) {
  digitalWrite(triggerPin, HIGH);
  delay(milliseconds);
  digitalWrite(triggerPin, LOW);
  delay(milliseconds);
}

float computeCap(long tInit, long tFinal) {

  if (tFinal > 0) {
    T = tFinal - tInit;         //Determinamos el tiempo de duracion del pulso.
    C1 = (T * 1E6 / (1.07881 * R1));   //Calculamos la capacidad desconocida (en microFaradios)
    tInit = 0;                   //Reasignamos cero a las variables que guardan los
    tFinal = 0;                    //tiempos inicial y final y asi habilitar una nueva medicion.
  }
  return C1;
}

float calibration(int samples) {
  digitalWrite(ledCalibrate, HIGH);
  float acum = 0;
  int i = 0;
  C1 = 0;
  do {
    trigger(4);
    C1 = computeCap( tInit, tFinal);
    acum = acum + C1;
    i++;
  } while (i < samples);

  digitalWrite(ledCalibrate, LOW);
  calCap = acum / samples;
  return calCap;
}

void setup() {

  pinMode(ledPin, OUTPUT);           //Habilitamos el pin del led como salida.
  pinMode(ledCalibrate, OUTPUT);
  pinMode(triggerPin, OUTPUT);       //
 

  attachInterrupt(digitalPinToInterrupt(interruptRISE), start, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptFALL), stop, FALLING);

  digitalWrite(triggerPin, LOW);
 
 calCap = calibration(200);
  Serial.begin(9600);                 //Habilitamos el puerto serie
}

void loop() {
    
    
    samples = 100;
    i = 0;
    C1 = 0;
    acum = 0;
    do {
      trigger(4);
      C1 = computeCap( tInit, tFinal);
      acum = acum + C1;
      i++;
    } while (i < samples);
    
    CFinal = (acum / samples) - calCap;
  //  displayValue(CFinal, calCap);
    displayValue(CFinal);
    delay(20);

}


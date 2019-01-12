/*
    MEDIDOR DE CAPACITANCIAS CON EL TIMER 555
*/

float R1 = 0.988e6;                 //Este resistor es el que junto con C1 determina la constante de tiempo
float C1 = 0;                       //Aquí guardaremos la capacidad medida.
volatile int led_pin = 10;         //terminal al que conectamos un led que encenderemos lo que dure el pulso de entrada.
volatile int trigger_pin = 5;
volatile int discharge_pin = 3;
volatile long t_inicio = 0;        //Guardamos el instante de inicio.
volatile long t_final = 0;         //Guardamos el instante del final del pulso.
long T = 0;                         //Duración del pulso
const byte interruptFALL = 0;
const byte interruptRISE = 1;


void setup()
{
//    void start();
//    void stop();
//    void trigger_555();
//    float compute_cap();
    pinMode(led_pin, OUTPUT);           //Habilitamos el pin del led como salida.
    pinMode(trigger_pin, OUTPUT);       //
    pinMode(discharge_pin, OUTPUT);
    digitalWrite(trigger_pin, LOW);
    digitalWrite(discharge_pin, HIGH);
    pinMode(digitalPinToInterrupt(interruptRISE),INPUT_PULLUP);
    pinMode(digitalPinToInterrupt(interruptRISE),INPUT_PULLUP);
    
    attachInterrupt(digitalPinToInterrupt(interruptRISE),start,RISING);  //El interrupt 0 está asociado al pin 2. RISING indica que la interrupcion
                                        //se dispara con el flanco ascendente del pulso.
    attachInterrupt(digitalPinToInterrupt(interruptFALL),stop,FALLING);  //El interrupt 1 está asociado al pin 3. FALLING indica que la interrupcion
                                        //se dispara con el flanco descendiente del pulso.
    
    Serial.begin(115200);                 //Habilitamos el puerto serie
}

void loop(){
    //El loop se ejecutara indefinidamente hasta que la variable t_final
    //ya no sea 0, lo que ocurrira luego de la interrupcion de final de pulso.
    
    trigger_555();
    C1 = compute_cap();
    display_value();
      
}

// Funcion asociada al interrupt 0. Se ejecuta al iniciar el pulso.
void start(){
    t_inicio = micros();                //millis me da el tiempo transcurrido desde que el programa inicio su ejecucion.
    digitalWrite(led_pin, HIGH);        //Encendemos el led como indicador de que la interrupcion fue activada.
}


// Funcion asociada al interrupt 1. Se ejecuta al finalizar el pulso.
void stop(){
    t_final = micros();                 //Guardamos el tiempo retornado por millis().
    digitalWrite(led_pin, LOW);         //Apagamos el led indicando el final del pulso
}

void display_value(){
        Serial.print("C = ");
        Serial.print(C1);        //Convertimos a picoFaradios
        Serial.println(" pF");
        Serial.println();

}

void trigger_555(){
   digitalWrite(trigger_pin, HIGH);
    delay(1);
    digitalWrite(trigger_pin, LOW);

    digitalWrite(discharge_pin, LOW);
    delay(2);
    digitalWrite(discharge_pin, HIGH);   
}

float compute_cap(){

if (t_final > 0){
        T = t_final - t_inicio;         //Determinamos el tiempo de duracion del pulso.
        C1 = (T*1E6 / (1.1 * R1));     //Calculamos la capacidad desconocida (en microFaradios)

        
        t_inicio = 0;                   //Reasignamos cero a las variables que guardan los
        t_final = 0;                    //tiempos inicial y final y asi habilitar una nueva medicion.
    }
   return C1;
}


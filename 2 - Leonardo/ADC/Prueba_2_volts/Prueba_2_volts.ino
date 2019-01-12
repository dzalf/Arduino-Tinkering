/*
Read values from a potentiometer
*/
const int pot_pin = 0;                  // Potentiometer

void setup()
{
 // initialize the serial communications:
 Serial.begin(9600);
 //analogReference(DEFAULT);
 
}
void loop()
{
 int value = analogRead(pot_pin);  //read from pot_pin
 delay(1); //

 
float quanta = 5.0/1023;
float volts = value*quanta;  //

Serial.print(volts); 
Serial.print("\n");


delay(1000);  //wait for 1 second 
}

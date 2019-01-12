/*
Read values from a potentiometer
*/
const int pot_pin = 0;                  // Potentiometer

void setup()
{
 // initialize the serial communications:
 Serial.begin(9600);
 analogReference(DEFAULT);
 
}
void loop()
{
 int value = analogRead(pot_pin);  //read from pot_pin
 delay(1); //

 
float zero_G = 512.0; //ADC is 0~1023  the zero g output equal to Vs/2
                      //ADXL335 power supply by Vs 3.3V
float scale = 102.3;  //ADXL335330 Sensitivity is 330mv/g
                       //330 * 1024/3.3/1000  

Serial.print(value); 
Serial.print("\n");


delay(1000);  //wait for 1 second 
}

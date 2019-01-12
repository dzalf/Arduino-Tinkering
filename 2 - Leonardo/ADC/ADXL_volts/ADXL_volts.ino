/*
ADXL335
note:vcc-->5v ,but ADXL335 Vs is 3.3V
The circuit:
      5V: VCC
analog 1: x-axis
analog 2: y-axis
analog 3: z-axis
*/
const int xpin = 1;                  // x-axis of the accelerometer
const int ypin = 2;                  // y-axis
const int zpin = 3;                  // z-axis (only on 3-axis models)
void setup()
{
 // initialize the serial communications:
 Serial.begin(9600);
 analogReference(EXTERNAL);
}
void loop()
{
 int x = analogRead(xpin);  //read from xpin
 delay(1); //
 int y = analogRead(ypin);  //read from ypin
 delay(1);  
 int z = analogRead(zpin);  //read from zpin
 
float quanta = 3.3/1023;
float volts_x = x*quanta;  //
float volts_y = y*quanta;  //
float volts_z = z*quanta;  //

//float zero_G = 512.0; //ADC is 0~1023  the zero g output equal to Vs/2
//                      //ADXL335 power supply by Vs 3.3V
//float scale = 102.3;  //ADXL335330 Sensitivity is 330mv/g
//                       //330 * 1024/3.3/1000  

Serial.print(volts_x); 
Serial.print("\t");
Serial.print(volts_y);
Serial.print("\t");
Serial.print(volts_z);  
Serial.print("\n");

//Serial.print(x);  //print x value on serial monitor
//Serial.print("\t");
//Serial.print(y);  //print y value on serial monitor
//Serial.print("\t");
//Serial.print(z);  //print z value on serial monitor
//Serial.print("\n");

delay(1000);  //wait for 1 second 
}

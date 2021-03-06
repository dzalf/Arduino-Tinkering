#include <LedControl.h>
const int OUT_PIN = A2;
const int IN_PIN = A0;
int val;
LedControl lc=LedControl(16,15,14,1); // 

// pin 12 is connected to the MAX7219 pin 1
// pin 11 is connected to the CLK pin 13
// pin 10 is connected to LOAD pin 12
// 1 as we are only using 1 MAX7219

void setup()
{
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,8);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  Serial.begin(9600);      // open the serial port at 9600 bps:  
}
void loop()
{
  pinMode(IN_PIN, INPUT);
      digitalWrite(OUT_PIN, HIGH);
      val = analogRead(IN_PIN);

  Serial.println(val, DEC);  // print as an ASCII-encoded decimal
  
//  for (int row=0; row<8; row++)
//  {
//    for (int col=0; col<8; col++)
//    {
//      lc.setLed(0,col,row,true); // turns on LED at col, row
//      delay(25);
//    }
//  }
//
//  for (int row=0; row<8; row++)
//  {
//    for (int col=0; col<8; col++)
//    {
//      lc.setLed(0,col,row,false); // turns off LED at col, row
//      delay(25);
//    }
//  }
}

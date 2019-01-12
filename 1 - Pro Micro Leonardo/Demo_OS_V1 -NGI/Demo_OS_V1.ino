
#include <LedControl.h>
#include <MaxMatrix.h>
#include <LiquidCrystal.h>
#include <avr/pgmspace.h>

PROGMEM const unsigned char CH[] = {
3, 8, B00000000, B00000000, B00000000, B00000000, B00000000, // space
1, 8, B01011111, B00000000, B00000000, B00000000, B00000000, // !
3, 8, B00000011, B00000000, B00000011, B00000000, B00000000, // "
5, 8, B00010100, B00111110, B00010100, B00111110, B00010100, // #
4, 8, B00100100, B01101010, B00101011, B00010010, B00000000, // $
5, 8, B01100011, B00010011, B00001000, B01100100, B01100011, // %
5, 8, B00110110, B01001001, B01010110, B00100000, B01010000, // &
1, 8, B00000011, B00000000, B00000000, B00000000, B00000000, // '
3, 8, B00011100, B00100010, B01000001, B00000000, B00000000, // (
3, 8, B01000001, B00100010, B00011100, B00000000, B00000000, // )
5, 8, B00101000, B00011000, B00001110, B00011000, B00101000, // *
5, 8, B00001000, B00001000, B00111110, B00001000, B00001000, // +
2, 8, B10110000, B01110000, B00000000, B00000000, B00000000, // ,
4, 8, B00001000, B00001000, B00001000, B00001000, B00000000, // -
2, 8, B01100000, B01100000, B00000000, B00000000, B00000000, // .
4, 8, B01100000, B00011000, B00000110, B00000001, B00000000, // /
4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // 0
3, 8, B01000010, B01111111, B01000000, B00000000, B00000000, // 1
4, 8, B01100010, B01010001, B01001001, B01000110, B00000000, // 2
4, 8, B00100010, B01000001, B01001001, B00110110, B00000000, // 3
4, 8, B00011000, B00010100, B00010010, B01111111, B00000000, // 4
4, 8, B00100111, B01000101, B01000101, B00111001, B00000000, // 5
4, 8, B00111110, B01001001, B01001001, B00110000, B00000000, // 6
4, 8, B01100001, B00010001, B00001001, B00000111, B00000000, // 7
4, 8, B00110110, B01001001, B01001001, B00110110, B00000000, // 8
4, 8, B00000110, B01001001, B01001001, B00111110, B00000000, // 9
2, 8, B01010000, B00000000, B00000000, B00000000, B00000000, // :
2, 8, B10000000, B01010000, B00000000, B00000000, B00000000, // ;
3, 8, B00010000, B00101000, B01000100, B00000000, B00000000, // <
3, 8, B00010100, B00010100, B00010100, B00000000, B00000000, // =
3, 8, B01000100, B00101000, B00010000, B00000000, B00000000, // >
4, 8, B00000010, B01011001, B00001001, B00000110, B00000000, // ?
5, 8, B00111110, B01001001, B01010101, B01011101, B00001110, // @
4, 8, B01111110, B00010001, B00010001, B01111110, B00000000, // A
4, 8, B01111111, B01001001, B01001001, B00110110, B00000000, // B
4, 8, B00111110, B01000001, B01000001, B00100010, B00000000, // C
4, 8, B01111111, B01000001, B01000001, B00111110, B00000000, // D
4, 8, B01111111, B01001001, B01001001, B01000001, B00000000, // E
4, 8, B01111111, B00001001, B00001001, B00000001, B00000000, // F
4, 8, B00111110, B01000001, B01001001, B01111010, B00000000, // G
4, 8, B01111111, B00001000, B00001000, B01111111, B00000000, // H
3, 8, B01000001, B01111111, B01000001, B00000000, B00000000, // I
4, 8, B00110000, B01000000, B01000001, B00111111, B00000000, // J
4, 8, B01111111, B00001000, B00010100, B01100011, B00000000, // K
4, 8, B01111111, B01000000, B01000000, B01000000, B00000000, // L
5, 8, B01111111, B00000010, B00001100, B00000010, B01111111, // M
5, 8, B01111111, B00000100, B00001000, B00010000, B01111111, // N
4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // O
4, 8, B01111111, B00001001, B00001001, B00000110, B00000000, // P
4, 8, B00111110, B01000001, B01000001, B10111110, B00000000, // Q
4, 8, B01111111, B00001001, B00001001, B01110110, B00000000, // R
4, 8, B01000110, B01001001, B01001001, B00110010, B00000000, // S
5, 8, B00000001, B00000001, B01111111, B00000001, B00000001, // T
4, 8, B00111111, B01000000, B01000000, B00111111, B00000000, // U
5, 8, B00001111, B00110000, B01000000, B00110000, B00001111, // V
5, 8, B00111111, B01000000, B00111000, B01000000, B00111111, // W
5, 8, B01100011, B00010100, B00001000, B00010100, B01100011, // X
5, 8, B00000111, B00001000, B01110000, B00001000, B00000111, // Y
4, 8, B01100001, B01010001, B01001001, B01000111, B00000000, // Z
2, 8, B01111111, B01000001, B00000000, B00000000, B00000000, // [
4, 8, B00000001, B00000110, B00011000, B01100000, B00000000, // \ backslash
2, 8, B01000001, B01111111, B00000000, B00000000, B00000000, // ]
3, 8, B00000010, B00000001, B00000010, B00000000, B00000000, // hat
4, 8, B01000000, B01000000, B01000000, B01000000, B00000000, // _
2, 8, B00000001, B00000010, B00000000, B00000000, B00000000, // `
4, 8, B00100000, B01010100, B01010100, B01111000, B00000000, // a
4, 8, B01111111, B01000100, B01000100, B00111000, B00000000, // b
4, 8, B00111000, B01000100, B01000100, B00101000, B00000000, // c
4, 8, B00111000, B01000100, B01000100, B01111111, B00000000, // d
4, 8, B00111000, B01010100, B01010100, B00011000, B00000000, // e
3, 8, B00000100, B01111110, B00000101, B00000000, B00000000, // f
4, 8, B10011000, B10100100, B10100100, B01111000, B00000000, // g
4, 8, B01111111, B00000100, B00000100, B01111000, B00000000, // h
3, 8, B01000100, B01111101, B01000000, B00000000, B00000000, // i
4, 8, B01000000, B10000000, B10000100, B01111101, B00000000, // j
4, 8, B01111111, B00010000, B00101000, B01000100, B00000000, // k
3, 8, B01000001, B01111111, B01000000, B00000000, B00000000, // l
5, 8, B01111100, B00000100, B01111100, B00000100, B01111000, // m
4, 8, B01111100, B00000100, B00000100, B01111000, B00000000, // n
4, 8, B00111000, B01000100, B01000100, B00111000, B00000000, // o
4, 8, B11111100, B00100100, B00100100, B00011000, B00000000, // p
4, 8, B00011000, B00100100, B00100100, B11111100, B00000000, // q
4, 8, B01111100, B00001000, B00000100, B00000100, B00000000, // r
4, 8, B01001000, B01010100, B01010100, B00100100, B00000000, // s
3, 8, B00000100, B00111111, B01000100, B00000000, B00000000, // t
4, 8, B00111100, B01000000, B01000000, B01111100, B00000000, // u
5, 8, B00011100, B00100000, B01000000, B00100000, B00011100, // v
5, 8, B00111100, B01000000, B00111100, B01000000, B00111100, // w
5, 8, B01000100, B00101000, B00010000, B00101000, B01000100, // x
4, 8, B10011100, B10100000, B10100000, B01111100, B00000000, // y
3, 8, B01100100, B01010100, B01001100, B00000000, B00000000, // z
3, 8, B00001000, B00110110, B01000001, B00000000, B00000000, // {
1, 8, B01111111, B00000000, B00000000, B00000000, B00000000, // |
3, 8, B01000001, B00110110, B00001000, B00000000, B00000000, // }
4, 8, B00001000, B00000100, B00001000, B00000100, B00000000, // ~
};

volatile byte state = HIGH;
const byte interruptPin = 2;
const int OUT_PIN = A2;
const int IN_PIN = A0;
int val;
int flag = 0;
const int buttonPin = 9;     // the number of the pushbutton pin
const int ledPin =  10;      // the number of the LED pin
byte buffer[10];
char string1[] = " * Te he pensado todo el dia...";  // Scrolling Text
// variables will change:
int buttonState;         // variable for reading the pushbutton status

int data = 16;    // DIN pin of MAX7219 module
int load = 14;    // CS pin of MAX7219 module
int clock = 15;  // CLK pin of MAX7219 module
int maxInUse = 4;  //how many MAX7219 are connected

//Capacitance between IN_PIN and Ground
//Stray capacitance is always present. Extra capacitance can be added to
//allow higher capacitance to be measured.
const float IN_STRAY_CAP_TO_GND = 27.107; //initially this was 27.107
const float IN_EXTRA_CAP_TO_GND = 0.0;
const float IN_CAP_TO_GND  = IN_STRAY_CAP_TO_GND + IN_EXTRA_CAP_TO_GND;
const int MAX_ADC_VALUE = 1023;
float capacitance;
float acum;
float acumADC;
float finalADC;
float finalVal;
int linear;
int i;
const int samples = 100;

LedControl lc=LedControl(16,15,14,1); // 
// pin 12 is connected to the MAX7219 pin 1
// pin 11 is connected to the CLK pin 13
// pin 10 is connected to LOAD pin 12
// 1 as we are only using 1 MAX7219
MaxMatrix m(data, load, clock, maxInUse); // define Library

LiquidCrystal lcd(3, 4, 6, 7, 8, 9);

void setup()
{
  pinMode(interruptPin, INPUT_PULLUP);
  
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,8);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  Serial.begin(9600);      // open the serial port at 9600 bps:  
   // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(IN_PIN, INPUT);
  pinMode(OUT_PIN, OUTPUT);
  m.init(); // module MAX7219
//  m.setIntensity(5); // LED Intensity 0-15
  attachInterrupt(digitalPinToInterrupt(interruptPin), toggle, FALLING);
  digitalWrite(ledPin, state);
  lcd.begin(16, 2);
}
void loop()
{
  
//  buttonState = digitalRead(buttonPin);
//  delay(150);
//  
//  if (buttonState == LOW) {
//    if (flag == 0) {
     
//       turn LED on:
//      digitalWrite(ledPin, HIGH);
//      flag = 1;
//    
    do{  
          i = 0;
          acum = 0;
          acumADC = 0;
          do{
              pinMode(IN_PIN, INPUT);
              digitalWrite(OUT_PIN, HIGH);
              val = analogRead(IN_PIN);
//              delay(1);
              //Clear everything for next measurement
              digitalWrite(OUT_PIN, LOW);
              pinMode(IN_PIN, OUTPUT);
            
              //Calculate and print result
              
              capacitance = (float)val * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val);
              acum = acum + capacitance;
//              acumADC = acumADC + val;
              i = i+1;
            } while (i<samples);
    
          finalVal = acum/samples;
//          finalADC = acumADC/samples;
//          linear = 21.3*finalADC - 7076;
            linear = 310*finalVal - 3627; //310x - 3627
//          Serial.println(val, DEC);  // print as an ASCII-encoded decimal
          senseLevel(linear);

//          lcd.setCursor(0,0);
            lcd.setCursor(0,0);
            lcd.print("Graphene level");
            lcd.setCursor(0,1);
            lcd.print(F("Cap = "));
          lcd.setCursor(6,1);
          lcd.print(finalVal, 1);
          lcd.setCursor(12,1);
          lcd.print(F("pF"));
//          lcd.setCursor(0,1);
//          lcd.print("ADC = ");
//          lcd.setCursor(6,1);
//          lcd.print(finalADC);
          
      }while(state == LOW);

      do{
        byte c;
        delay(10);
        m.shiftLeft(false, true);
        printStringWithShift(string1, 50);  // Send scrolling Text
      }while(state == HIGH);
//}
// }

}
// Function to sense level

void senseLevel(int val){
  if (val < 1){
        //Setting the leds from the fisrt row (index=2) of the first device 
        
        lc.setColumn(0,0,B00000000); 
        lc.setColumn(0,1,B00000000);
        lc.setColumn(0,2,B00000000); 
        lc.setColumn(0,3,B00000000);
        lc.setColumn(0,4,B00000000); 
        lc.setColumn(0,5,B00000000); 
        lc.setColumn(0,6,B00000000); 
        lc.setColumn(0,7,B00000000);
        
      }
  
  if (val < 128 && val > 1){
        //Setting the leds from the fisrt row (index=2) of the first device 
        
        lc.setColumn(0,0,B11111111); 
        lc.setColumn(0,1,B00000000);
        lc.setColumn(0,2,B00000000); 
        lc.setColumn(0,3,B00000000);
        lc.setColumn(0,4,B00000000); 
        lc.setColumn(0,5,B00000000); 
        lc.setColumn(0,6,B00000000); 
        lc.setColumn(0,7,B00000000);
        
      }
      if (val > 127 && val < 256){
        //Setting the leds from the second row (index=2) of the first device 
        
        lc.setColumn(0,0,B11111111); 
        lc.setColumn(0,1,B11111111);
        lc.setColumn(0,2,B00000000); 
        lc.setColumn(0,3,B00000000);
        lc.setColumn(0,4,B00000000); 
        lc.setColumn(0,5,B00000000); 
        lc.setColumn(0,6,B00000000); 
        lc.setColumn(0,7,B00000000);
        
      }
    if (val > 255 && val < 384){
        //Setting the leds from the third row (index=2) of the first device 
        
        lc.setColumn(0,0,B11111111); 
        lc.setColumn(0,1,B11111111);
        lc.setColumn(0,2,B11111111); 
        lc.setColumn(0,3,B00000000);
        lc.setColumn(0,4,B00000000); 
        lc.setColumn(0,5,B00000000); 
        lc.setColumn(0,6,B00000000); 
        lc.setColumn(0,7,B00000000);
        
      }
      if (val > 383 && val < 512){
        //Setting the leds from the fourth row (index=2) of the first device 
        
        lc.setColumn(0,0,B11111111); 
        lc.setColumn(0,1,B11111111);
        lc.setColumn(0,2,B11111111); 
        lc.setColumn(0,3,B11111111);
        lc.setColumn(0,4,B00000000); 
        lc.setColumn(0,5,B00000000); 
        lc.setColumn(0,6,B00000000); 
        lc.setColumn(0,7,B00000000);
        
      }
      if (val > 511 && val < 640){
        //Setting the leds from the fourth row (index=2) of the first device 
        
        lc.setColumn(0,0,B11111111); 
        lc.setColumn(0,1,B11111111);
        lc.setColumn(0,2,B11111111); 
        lc.setColumn(0,3,B11111111);
        lc.setColumn(0,4,B11111111); 
        lc.setColumn(0,5,B00000000); 
        lc.setColumn(0,6,B00000000); 
        lc.setColumn(0,7,B00000000);
        
      }
      if (val > 639 && val < 768){
        //Setting the leds from the fourth row (index=2) of the first device 
        
        lc.setColumn(0,0,B11111111); 
        lc.setColumn(0,1,B11111111);
        lc.setColumn(0,2,B11111111); 
        lc.setColumn(0,3,B11111111);
        lc.setColumn(0,4,B11111111); 
        lc.setColumn(0,5,B11111111); 
        lc.setColumn(0,6,B00000000); 
        lc.setColumn(0,7,B00000000);
        
      }
      if (val > 767 && val < 896){
        //Setting the leds from the fourth row (index=2) of the first device 
        
        lc.setColumn(0,0,B11111111); 
        lc.setColumn(0,1,B11111111);
        lc.setColumn(0,2,B11111111); 
        lc.setColumn(0,3,B11111111);
        lc.setColumn(0,4,B11111111); 
        lc.setColumn(0,5,B11111111); 
        lc.setColumn(0,6,B11111111); 
        lc.setColumn(0,7,B00000000);
        
      }
  
      if (val > 895 && val < 1024){
        //Setting the leds from the fourth row (index=2) of the first device 
        
        lc.setColumn(0,0,B11111111); 
        lc.setColumn(0,1,B11111111);
        lc.setColumn(0,2,B11111111); 
        lc.setColumn(0,3,B11111111);
        lc.setColumn(0,4,B11111111); 
        lc.setColumn(0,5,B11111111); 
        lc.setColumn(0,6,B11111111); 
        lc.setColumn(0,7,B11111111);
        
      }
  
  }

  // Put extracted character on Display
    void printCharWithShift(char c, int shift_speed){
      if (c < 32) return;
      c -= 32;
      memcpy_P(buffer, CH + 7*c, 7);
      m.writeSprite(maxInUse*8, 0, buffer);
      m.setColumn(maxInUse*8 + buffer[0], 0);
      
      for (int i=0; i<buffer[0]+1; i++) 
      {
        delay(shift_speed);
        m.shiftLeft(false, false);
      }
    }
// Extract characters from Scrolling text
 void printStringWithShift(char* s, int shift_speed){
      while (*s != 0){
        printCharWithShift(*s, shift_speed);
        s++;
      }
    }

 void toggle() {
  state = !state;
  digitalWrite(ledPin, state);
  
}

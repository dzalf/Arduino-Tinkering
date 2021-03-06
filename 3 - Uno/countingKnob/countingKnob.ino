/*



inspired by circuits at home
http://www.circuitsathome.com/mcu/reading-rotary-encoder-on-arduino

*/

#define encPinA 14                           // rotary encoder pin A
int encALast;
#define encPinB 15                           // rotary encoder pin B

int theNumber = 0; // 3.8.2011
int val; 
int segments[7] = {12,13,3,4,5,10,9};       // pins, the segments are attached to

//int segments[7] = {3,4,9,11,12,5,6};       // pins, the segments are attached to
int digits[2] = {7,11};                    // common anode of each digit
int buttonPin = 2;                         // pin, where the start stop button is connected
int lastButtonState;

boolean timer = false;
long myStartTime;

long theSecond = 1000;

byte seven_seg_segments[10][7] = { 
  {1,1,1,1,1,1,0},  // = 0
  {0,1,1,0,0,0,0},  // = 1
  {1,1,0,1,1,0,1},  // = 2
  {1,1,1,1,0,0,1},  // = 3
  {0,1,1,0,0,1,1},  // = 4
  {1,0,1,1,0,1,1},  // = 5
  {1,0,1,1,1,1,1},  // = 6
  {1,1,1,0,0,0,0},  // = 7
  {1,1,1,1,1,1,1},  // = 8
  {1,1,1,1,0,1,1}   // = 9
};

void setup() {    
//  Serial.begin(9600);                    // starts serial communication
  pinMode(encPinA, INPUT);                    // set rotary encoder A pin as input
  pinMode(encPinB, INPUT);                    // set rotary encoder B pin as input  
  digitalWrite(encPinA, HIGH);                // switches internal drop down resistors on
  digitalWrite(encPinB, HIGH);                // switches internal drop down resistors on

  pinMode(buttonPin,INPUT);

  for (int i=0; i<7; i++){
    pinMode(segments[i], OUTPUT);           // sets the seven segment outputs
  }

  for (int i=0; i<2; i++){
    pinMode(digits[i], OUTPUT);             // sets the seven segment outputs 
  }
}

void sevenSegWrite(int thePosition, int digit) {  // write a number to a seven segment digit
  for (int i = 0; i < 7; i++) {          
    if (seven_seg_segments[digit][i] == 1){  
      digitalWrite(segments[i], LOW);
    } 
    else {
      digitalWrite(segments[i], HIGH);
    }
  }
  digitalWrite(digits[thePosition], HIGH);
  delayMicroseconds(200);
  digitalWrite(digits[thePosition], LOW);
  delayMicroseconds(200);
}

void clearDisplay() {                              // clear the display
  for (int i=0; i<5; i++){
    digitalWrite(digits[i], LOW);
  }
}

void showNumber(){                                 // show the number
    char szZahl[1];
    sprintf(szZahl, "%d", theNumber);
    int ergebnis = szZahl[0] - '0';
    if (ergebnis>-1){
      sevenSegWrite(1,ergebnis);
      delayMicroseconds(10);
    } else {
      sevenSegWrite(1,0);
      delayMicroseconds(10);
    }
    delay(1);
    clearDisplay();
}

void loop() {
  // read rotary encoder
  if (encALast!=digitalRead(encPinA)){
    if ((digitalRead(encPinA)==LOW)&&(digitalRead(encPinB)==LOW)) {
      theNumber++;
      if (theNumber>9) theNumber=0;
    }
    if ((digitalRead(encPinA)==LOW)&&(digitalRead(encPinB)==HIGH)) {
      theNumber--;
      if (theNumber<0) theNumber=9;
    }
  }
  
  encALast=digitalRead(encPinA);
  
  clearDisplay();
  showNumber();
  delay(1);
}

/* @file CustomKeypad.pde
  || @version 1.0
  || @author Alexander Brevig
  || @contact alexanderbrevig@gmail.com
  ||
  || @description
  || | Demonstrates changing the keypad size and key values.
  || #
*/
#include <Keypad.h>
#include "Wire.h"
#include "LiquidCrystal_I2C.h"


const byte ROWS = 4; //four rows
const byte COLS = 2; //four columns
const int clk = 2;
const int dt = 3;
int counter;
int flag;

//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'E', ' '},
  {'C', ' '},
  {'B', ' '},
  {'A', 'D'}
};
byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


void setup() {
  delay(150);
  attachInterrupt(0, rotaryChange, FALLING);
  lcd.begin(20, 4);        // initialize the lcd for 20 chars 4 lines
  lcd.backlight(); // backlight on
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("* Keyboard testing *");
  pinMode(clk, INPUT);
  pinMode(dt, INPUT);
  counter = 0;
  flag = 1; 
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    lcd.setCursor(1, 0);
    lcd.print(" Pressed --> ");
    lcd.print(customKey);
    lcd.setCursor(2, 0);
    lcd.print(" Value --> ");
    lcd.print(counter);
  }
}

void rotaryChange() {

  int clk_val = digitalRead(clk);
  int dt_val = digitalRead(dt);

  if (clk_val == LOW || dt_val == LOW ) {
    flag = 0;
    debounce();
    if (clk_val == dt_val) {
      //    digitalWrite(yellow, HIGH);
      //    delay(100);
      //    digitalWrite(yellow,LOW);
      counter--;

      if (counter < 0) {
        counter = 7;
      }
    }
    else
    {
      //    digitalWrite(green, HIGH);
      //   delay(100);
      //    digitalWrite(green,LOW);
      counter++;

      if (counter > 7) {
        counter = 0;
      }
    }
  }
}

void debounce() {
  while (flag == 0) {

    if (digitalRead(clk) == HIGH && flag == 0) {
      flag = 1 ;
    }
    else {
      while (digitalRead(clk) == LOW) {
        flag = 0;
      }
    }

    if (digitalRead(dt) == HIGH && flag == 0) {
      flag = 1 ;
    }
    else {
      while (digitalRead(dt) == LOW) {
        flag = 0;
      }
    }
  }
}

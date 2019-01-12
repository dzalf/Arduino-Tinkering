#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const byte ROWS = 4; //four rows
const byte COLS = 2; //four columns
const int clk = 3;
const int dt = 2;
int counter = 0;
int flag = 1;
boolean change = false;

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

  pinMode(clk, INPUT);
  digitalWrite(clk, HIGH);
  pinMode(dt, INPUT);
  digitalWrite(dt, HIGH);

  attachInterrupt(0, rotaryChangeA, CHANGE);
//  attachInterrupt(1, rotaryChangeB, CHANGE);

  lcd.begin(20, 4);// initialize the lcd for 20 chars 4 lines
  lcd.backlight(); // backlight on
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("* Keyboard testing *");

  lcd.setCursor(0, 3);
  lcd.print(" Value --> ");
  lcd.print(counter);
}

void loop() {
  char customKey = customKeypad.getKey();
  lcd.setCursor(0, 2);
  lcd.print(" Pressed --> ");
    if (customKey) {
      lcd.print(customKey);
    }
  lcd.setCursor(0, 3);
  lcd.print("   Value --> ");
  lcd.print(counter);
  
    if (change) {
      cleanLine();
      change = false;
    }
}

void rotaryChangeA() {
//  change = true;
  // look for a low-to-high on channel A
  if (digitalRead(clk) == HIGH) {
//    flag = 0;
//    debounce();
    // check channel B to see which way encoder is turning
    if (digitalRead(dt) == LOW) {
      flag = 0;
      debounce();
      counter = counter + 1;         // CW
      if (counter > 255) {
        counter  = 255;
      }
    }
    else {
      counter = counter - 1;         // CCW
      if (counter < 0) {
        counter  = 0;
      }
    }
  }
  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(dt) == HIGH) {
      counter = counter + 1;          // CW
      if (counter > 255) {
        counter  = 255;
      }
    }
    else {
      counter = counter - 1;          // CCW
      if (counter < 0) {
        counter  = 0;
      }
    }
  }
}

void rotaryChangeB() {
  change = true;
  // look for a low-to-high on channel A
  if (digitalRead(dt) == HIGH) {
    flag = 0;
    debounce();

    // check channel B to see which way encoder is turning
    if (digitalRead(clk) == HIGH) {
      flag = 0;
      debounce();
      counter = counter + 1;         // CW
      if (counter > 255) {
        counter  = 255;
      }
    }
    else {
      counter = counter - 1;         // CCW
      if (counter < 0) {
        counter  = 0;
      }
    }
  }
  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(clk) == LOW) {
      counter = counter + 1;          // CW
      if (counter > 255) {
        counter  = 255;
      }
    }
    else {
      counter = counter - 1;          // CCW
      if (counter < 0) {
        counter  = 0;
      }
    }
  }

}
void cleanLine() {
  if (counter < 10) {
    lcd.setCursor(13, 3);
    lcd.print(" ");
  }
  if (counter < 256) {
    lcd.setCursor(13, 3);
    lcd.print("  ");
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

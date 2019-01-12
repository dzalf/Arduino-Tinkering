#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>


const byte ROWS = 4; //four rows
const byte COLS = 2; //four columns

int counter = 0;

// Setup a RoraryEncoder for pins A2 and A3:
RotaryEncoder encoder(A2, A3);
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'E', ' '},
  {'C', ' '},
  {'B', ' '},
  {'A', 'D'}
};
byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5}; //connect to the column pinouts of the keypad
char customKey = customKeypad.getKey();
static int pos = 0;
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


void setup() {
  delay(150);

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
    
  int newPos = encoder.getPosition();
  
  lcd.setCursor(0, 2);
  lcd.print(" Pressed --> ");
    if (customKey) {
      lcd.print(customKey);
    }
    //// new

  encoder.tick();
  if (pos != newPos) {
    if (newPos < 0){
      newPos = 0;
    }
    if (newPos > 255){
      newPos = 255;
    }
    lcd.setCursor(0, 3);
    lcd.print("   Value --> "); 
    lcd.print(newPos);
    lcd.print(" ");
    pos = newPos;
  } 
    ////
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


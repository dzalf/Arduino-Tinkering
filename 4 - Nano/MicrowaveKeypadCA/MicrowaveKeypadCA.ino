#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>

const byte ROWS = 4; //four rows
const byte COLS = 2; //four columns
char hexaKeys[ROWS][COLS] = {
  {'E', ' '},
  {'C', ' '},
  {'B', ' '},
  {'A', 'D'}
};
byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5}; //connect to the column pinouts of the keypad
char customKey;
byte counter = 0;
byte pin = 34;
const int pulseOut = 3;
const int relay = 2;
int PWMOn  = 127;
int PWMOff  = 0;
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Setup a RoraryEncoder for pins A2 and A3:
RotaryEncoder encoder(A2, A3);
//define the cymbols on the buttons of the keypads

void setup() {
  delay(50);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);

  lcd.begin(20, 4);// initialize the lcd for 20 chars 4 lines
  lcd.backlight(); // backlight on
  lcd.clear();

  lcd.setCursor(0, 2);
  lcd.print("   Initializing ");
  for (int i = 0; i < 20; i++) {
    lcd.setCursor(i, 3);
    lcd.print(".");
    delay(60);
  }
  //  pinMode(3, OUTPUT);
  beep(300);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("*  Control access  *");

  lcd.setCursor(0, 2);
  lcd.print("Character --> ");
  lcd.print("-");
  lcd.setCursor(0, 3);
  lcd.print("   Value --> ");
  lcd.print(counter);

  // You may have to modify the next 2 lines if using other pins than A2 and A3
  PCICR |= (1 << PCIE1);    // This enables Pin Change Interrupt 1 that covers the Analog input pins or Port C.
  PCMSK1 |= (1 << PCINT10) | (1 << PCINT11);  // This enables the interrupt for pin 2 and 3 of Port C.
}

void loop() {

  do {

    lcd.setCursor(0, 2);
    lcd.print(" Pressed --> ");
    customKey = customKeypad.getKey();
    if (customKey) {
      beep(70);
      lcd.print(customKey);
    }
    static int pos = 0;

    counter = encoder.getPosition();

    if (pos != counter) {

      lcd.setCursor(0, 3);
      lcd.print("   Value --> ");
      lcd.print(counter);
      lcd.print(" ");
      pos = counter;
    }

    if (customKey == 'D' && pos == pin ) {

      lcd.setCursor(3, 1);
      lcd.print("ACCESS GRANTED!");
      digitalWrite(relay, HIGH);
      for (int i = 1; i < 4; i++) {
        lcd.setCursor(3, 1);
        lcd.print("ACCESS GRANTED!");
        beep(1000);
        lcd.setCursor(3, 1);
        lcd.print("                    ");
        delay(1000);
      }
    }

    digitalWrite(relay, LOW);
  }
} while (counter < 255 && counter > 0);
}

void beep(int time) {
  analogWrite(pulseOut, PWMOn);
  delay(time);
  analogWrite(pulseOut, PWMOff);
}
// The Interrupt Service Routine for Pin Change Interrupt 1
// This routine will only be called on any signal change on A2 and A3: exactly where we need to check.
ISR(PCINT1_vect) {
  beep(70);
  encoder.tick(); // just call tick() to check the state.
}


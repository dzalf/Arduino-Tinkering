#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_LCD_buttons(){               // read the buttons
    adc_key_in = analogRead(0);       // read the value from the sensor 
    Serial.print(adc_key_in);
    Serial.print(";");
    // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
    // we add approx 50 to those values and check to see if we are close
    // We make this the 1st option for speed reasons since it will be the most likely result

    if (adc_key_in > 1000) return btnNONE; 

    // For V1.1 us this threshold
//    if (adc_key_in < 50)   return btnRIGHT;  
//    if (adc_key_in < 110)  return btnUP; 
//    if (adc_key_in < 270)  return btnDOWN; 
//    if (adc_key_in < 415)  return btnLEFT; 
//    if (adc_key_in < 650)  return btnSELECT;  

   // For V1.0 comment the other threshold and use the one below:
   
     if (adc_key_in < 50)   return btnRIGHT;  
     if (adc_key_in < 195)  return btnUP; 
     if (adc_key_in < 380)  return btnDOWN; 
     if (adc_key_in < 555)  return btnLEFT; 
     if (adc_key_in < 790)  return btnSELECT;   
 

    return btnNONE;                // when all others fail, return this.
}

void setup(){
   lcd.begin(16, 2);               // start the library
   lcd.setCursor(0,0);             // set the LCD cursor   position 
   lcd.print("Push the buttons");  // print a simple message on the LCD
   Serial.begin(115200);
}
 
void loop(){
 
   lcd.setCursor(9,1);             // move cursor to second line "1" and 9 spaces over
   lcd.print(millis()/1000);       // display seconds elapsed since power-up

   lcd.setCursor(0,1);             // move to the begining of the second line
   lcd_key = read_LCD_buttons();   // read the buttons

   switch (lcd_key){               // depending on which button was pushed, we perform an action

       case btnRIGHT:{             //  push button "RIGHT" and show the word on the screen
            lcd.print("RIGHT ");
            Serial.println("RIGHT");
            break;
       }
       case btnLEFT:{
             lcd.print("LEFT   "); //  push button "LEFT" and show the word on the screen
             Serial.println("LEFT");
             break;
       }    
       case btnUP:{
             lcd.print("UP    ");  //  push button "UP" and show the word on the screen
             Serial.println("UP");
             break;
       }
       case btnDOWN:{
             lcd.print("DOWN  ");  //  push button "DOWN" and show the word on the screen
             Serial.println("DOWN");
             break;
       }
       case btnSELECT:{
             lcd.print("SELECT");  //  push button "SELECT" and show the word on the screen
             Serial.println("SELECT");
             break;
       }
       case btnNONE:{
             lcd.print("NONE  ");  //  No action  will show "None" on the screen
             Serial.println("NONE");
             break;
       }
   }
}

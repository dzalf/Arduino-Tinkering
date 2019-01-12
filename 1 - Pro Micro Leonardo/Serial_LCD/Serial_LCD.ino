
/* FILE:    ARD_LCD_HCMODU0010_I2C_Hello_World_Example
   DATE:    24/05/13
   VERSION: 0.1

  This is a simple example of how to use the Hobby Components 20 x 4 line
  I2C LCD module (HCMODU0010). To use this module you will require the
  appropriate LiquidCrystal_I2C library, which can be downloaded from our support
  forum:

  http://forum.hobbycomponents.com

  This code also demonstrates the correct pin assignment for the LCD. When you
  run this program you should see a greeting message appear on the display.


  DEVICE PINOUT (SPI Interface):

  PIN 1: GND
  PIN 2: +5V
  PIN 3: SDA - Connect to Arduino analogue PIN 4
  PIN 4: SCL - Connect to Arduino analogue PIN 5


  You may copy, alter and reuse this code in any way you like, but please leave
  reference to HobbyComponents.com in your comments if you redistribute this code.
  This software may not be used directly for the purpose of selling products that
  directly compete with Hobby Components Ltd's own range of products.

  THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS LTD MAKES NO WARRANTIES, WHETHER
  EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
  HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
  INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
  REASON WHATSOEVER.
*/

/* Include the SPI/IIC Library */
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

/* Create some custom graphic characters to make a simple border */
uint8_t TopLeftCorner[]  = {0x00, 0x00, 0x0f, 0x08, 0x0b, 0x0a, 0x0a, 0x0a};
uint8_t TopRightCorner[]  = {0x00, 0x00, 0x1e, 0x02, 0x1a, 0x0a, 0x0a, 0x0a};
uint8_t BottomLeftCorner[]  = {0x0a, 0x0a, 0x0b, 0x08, 0x0f, 0x00, 0x00, 0x00};
uint8_t BottomRightCorner[]  = {0x0a, 0x0a, 0x1a, 0x02, 0x1e, 0x00, 0x00, 0x00};
uint8_t VerticalBar[]  = {0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a};

volatile byte state = HIGH;
int RxLED = 17;

/* Initialise the LiquidCrystal library. Note that the displays will have a default I2C
    address of either 0x27 or 0x3F. Uncomment one of the lines below depending on
    the address of your module. */

LiquidCrystal_I2C lcd(0x27, 20, 4); //For the 4x20 screen

void setup()
{
  /* Initialise the LCD */
  lcd.begin();
  /* Transfer the custom characters into the LCD's memory */
  lcd.createChar(0, TopLeftCorner);
  lcd.createChar(1, TopRightCorner);
  lcd.createChar(2, BottomLeftCorner);
  lcd.createChar(3, BottomRightCorner);
  lcd.createChar(4, VerticalBar);

  lcd.setCursor(1, 1);
  lcd.print(" Daniel Melendrez ");
  lcd.setCursor(1, 2);
  lcd.print("Arduino Pro Micro");
}
/* Main program loop */
void loop()
{
  /* Use the custom graphic characters to draw a border */
  lcd.setCursor(0, 0);
  lcd.write(0); //Write the top left graphic
  lcd.print("==================");
  lcd.write(1); //Write the top right graphic
  lcd.setCursor(0, 1);
  lcd.write(4); //Write the vertical bar graphic
  lcd.setCursor(0, 2);
  lcd.write(4); //Write the vertical bar graphic
  lcd.setCursor(19, 1);
  lcd.write(4); //Write the vertical bar graphic
  lcd.setCursor(19, 2);
  lcd.write(4); //Write the vertical bar graphic
  lcd.setCursor(0, 3);
  lcd.write(2); //Write the bottom left graphic
  lcd.print("==================");
  lcd.write(3); //Write the bottom right graphic

  /* Display some text inside the border */
  while (1)
  {
   
    digitalWrite(RxLED, state);   // turn the LED on (HIGH is the voltage level)
    TXLED1;
    delay(100);              // wait for a second
    digitalWrite(RxLED, !state);    // turn the LED off by making the voltage LOW
    TXLED0;
    delay(100);              // wait for a second

  }
}



/**************************************************************************
  This is a library for several Adafruit displays based on ST77* drivers.

  Works with the Adafruit 1.8" TFT Breakout w/SD card
    ----> http://www.adafruit.com/products/358
  The 1.8" TFT shield
    ----> https://www.adafruit.com/product/802
  The 1.44" TFT breakout
    ----> https://www.adafruit.com/product/2088
  as well as Adafruit raw 1.8" TFT display
    ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams.
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional).

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 **************************************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <gfxfont.h>
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735

#include <SPI.h>

#if defined(__AVR_ATmega328P__)
#define TFT_CS   SS           //CS - CE            (pin 10)
#define TFT_CLK  SCK          //hw SPI - SCK       (pin 13)
#define TFT_MOSI MOSI         //hw SPI - SDA - DIN (pin 11)
#define TFT_A0   8           //A0 - DC - RS - D/C
#define TFT_RST   9           //RESET
#endif

// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// SCLK = pin 13. This is the fastest mode of operation and is required if
// using the breakout board's microSD card.


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_A0, TFT_RST);

#define LIGHT_BLUE 0x24F7
#define PURPLE_UOM 0x6012
#define AQUA 0x3679
#define ORANGE 0xDD88

float timeElapsed, previousTime, result;
bool minutes = false;
int timeWindow;

void setup(void) {
  Serial.begin(115200);

  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.setRotation(2);   // Val = 2 --> Portrait Pins on top

 // Serial.println(F("Initialized"));

  
  timeElapsed = 0.0;
  result = 0.0;
  timeWindow = 5;

  tft.fillScreen(ST7735_BLACK);
  drawFrames();
  drawAxis();

  tftPrintWelcome();

  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.setCursor(8, 30);
  tft.println("Elapsed: ");
  previousTime = millis();
}

void loop() {
  
  result = drawSine(timeElapsed/1000, 1, timeWindow);
  
  Serial.println(result);
  timeElapsed = millis() - previousTime;
  
  if ((timeElapsed / 1000 < 60) && (!minutes)) {
    char stringTime[10];
    dtostrf(timeElapsed / 1000, 3, 1, stringTime);
    tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
    tft.setCursor(60, 30);
    tft.print(stringTime);
    tft.print("  sec");
  } else {

    minutes = true;
  }
  
  if (minutes) {
    char stringTime[10];
    dtostrf((timeElapsed / 1000)/60, 3, 1, stringTime);
    tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
    tft.setCursor(60, 30);
    tft.print(stringTime);
    tft.print("  min ");
    
   // timeElapsed /= 60;
    
  }
}

void tftPrintWelcome() {
  tft.setTextWrap(false);
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(2);
  tft.setCursor(15, 6);
  tft.println(" AM GUI ");

}

void drawFrames() {

  byte topRectX = 3;
  byte topRectY = 3;

  byte secondRectX = 3;
  byte secondRectY = 24;

  byte thirdRectX = 3;
  byte thirdRectY = 45;

  tft.drawRoundRect(1, 1, tft.width() - 2, tft.height() - 2, 5, ST7735_WHITE);
  tft.drawRoundRect(topRectX, topRectY, tft.width() - (topRectX + 3), 20, 6, AQUA);
  tft.drawRoundRect(secondRectX, secondRectY, tft.width() - (secondRectX + 3), 20, 6, AQUA);
  tft.drawRoundRect(thirdRectX, thirdRectY, tft.width() - (thirdRectX + 3), tft.height() - (thirdRectY + 3), 6, AQUA);

}

void drawAxis() {

  byte thirdRectX = 3;
  byte thirdRectY = 45;

  tft.drawFastVLine(7, 50, tft.height() - (thirdRectY + 15), ST7735_GREEN);
  tft.drawFastHLine(5, tft.height() - 13, tft.width() - 10, ST7735_GREEN);

}

float drawSine(float t, float freq, byte tw) {

  float y;
  
  int scaleX = 111;
  int scaleY = 147;  // the dims of the axis are X--> 128 - 10 - 7 = 111; Y--> 160 - 13 = 147
  int origin[2] = {8, tft.height() - 13 - 1};

  y = sin(2 * 3.1415 * freq * t);
  
  if(((t * scaleX)/tw) >= scaleX){
    
    
    }

  tft.drawPixel(origin[0] + (t * scaleX)/tw, (origin[1] - origin[1]/4 ) - y * (scaleY/4), ORANGE);
  return y;
}

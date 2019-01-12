#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4

Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

float var;
int j;

void setup()   {
  Serial.begin(115200);
  var = 0.0;
  j = 0;
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done

  display.display();
  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);


}

void loop() {
  for (j = 0; j < 600; j+=5) {
    for (int i = 0; i < 1024; i+=5) {

      display.setCursor(0, 0);
      display.setTextSize(2);
      display.print("Testing...");

      display.setTextSize(1);
      display.setCursor(0, 19);
      display.print("i=");
      display.print(i, DEC);
      display.print(";");
      display.print("j=");
      display.print(j, DEC);
      display.print(";");
      display.print("var=");
      display.print(var, 1);
      display.display();

      Serial.print(i);
      Serial.print(", ");
      Serial.print(j);
      Serial.print(", ");
      Serial.print(var);
      Serial.print("\n");
      
      var = var + 0.1;

      //delay(1);
      display.clearDisplay();
    }
  }
}





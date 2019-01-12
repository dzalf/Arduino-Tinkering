#include <Adafruit_NeoPixel.h>

#define PIN 1

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, PIN, NEO_GRB + NEO_KHZ800);
void basicFlutter() {
  for (int i=1; i < 80; i++) {
    for(int j=0; j<strip.numPixels(); j++) {
      strip.setPixelColor(j, strip.Color(155,115,0));
    }
    strip.show();
    delay(40);
    for(int j=0; j<strip.numPixels(); j++) {
      strip.setPixelColor(j,0,0,0);
    }
    strip.show();
    delay(27);
  }
}


void breathAll() {
  for (int i; i < 225 ; i++) {
    for(int j=0; j<strip.numPixels(); j++) {
      strip.setPixelColor(j, strip.Color(i+15,i,0)); // yellow with a little extra red to make it warmer 
    }
    strip.show();
    delay(10);
  }
  for (int i = 225; i > 0; i--) {
    for(int j=0; j<strip.numPixels(); j++) {
      strip.setPixelColor(j, strip.Color(i+15,i,0));
    }
    strip.show();
    delay(10);
  }
}
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // "THE DANCE"
  // Basically calling a the functions defined below to perform the moves
  // but also adding in delays and setting values between the functions to make sure it looks good
  // The setPixelColor() and shows() could be avoided, but in the end it was easier.
  // maybe it would be nice to make a simple function to set and show, pass in position and color, idk.
  basicFlutter();
  
  delay(1000);
  
  strip.setPixelColor(0,0,0,0);
  strip.show();
  
  delay(2000);

  breathAll();
  breathAll();
  breathAll();
  delay(2000);
}

// This function blinks the outer LEDs at with delays that are relatively prime so they won't sync up after x loops
// I think this creates a stronger flapping/fluttering illusion, maybe I'm crazy


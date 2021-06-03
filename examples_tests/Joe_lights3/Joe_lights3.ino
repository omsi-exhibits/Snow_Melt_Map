#include "utillity.h"
#include <Adafruit_NeoPixel.h>

#define PIN1 A5
#define PIN2 A5

#define NUMPIXELS0 300
#define NUMPIXELS1 300
#define MINPIXELS 50

Adafruit_NeoPixel pixels0(NUMPIXELS0, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels1(NUMPIXELS1, PIN2, NEO_GRB + NEO_KHZ800);

/*
 * Using Brian Connections Mux Prototype PCB from 2-24-2019
 * Out putting standard neopixel led data to pins A5 and A4
 * FastLED has some pinout issues that need resolving, or bypassing
 */

////**** Animation
int animStep = 0;

unsigned long timer = 0;
int timeStep = 30;

void clearLeds() {
  pixels0.clear();
  pixels1.clear();
}

void drawLeds() {
    pixels0.show();
    pixels1.show(); 
}

void setup() {
  pixels0.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels1.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  clearLeds();
}



void loop() {

  // reset all the leds to off
  clearLeds();
  

  // draw River static - blue
  int riverLen = 30;

  for(int i=0; i <riverLen; i++ ) {
    pixels0.setPixelColor(i, pixels0.Color(0,48,255));
    //pixels0.setPixelColor(i, pixels0.Color(255,0,0));
  }


  // draw Dams - golden yellow
  int damSegment = 4;
  int damStart = 30;
  for(int i=damStart; i< damStart + damSegment; i ++ ) {
    pixels1.setPixelColor(i, pixels0.Color(255,255,0));
  }

  // City - purple
  int citySegment = 4;
  int cityStart = 20;
  for(int i=cityStart; i< cityStart + citySegment; i ++ ) {
    pixels1.setPixelColor(i, pixels0.Color(160,0, 255));
  }

  // Snow Sample site

  
  int snowSegment = 8;
  int snowStart = 42;
  for(int i=snowStart; i< snowStart + snowSegment; i ++ ) {
    pixels1.setPixelColor(i, pixels0.Color(255,255,255));
  }
  

  // draw blue river animation - blue 3 led pattern

  // draw aquaducts - blue

  // water receiving - pink

  int resSegment = 4;
  int resStart = 40;
  for(int i=resStart; i< resStart + resSegment; i ++ ) {
    pixels1.setPixelColor(i, pixels0.Color(255, 20, 100));
  }
  riverAnimate();
  
  drawLeds();
}

void riverAnimate() {
  if(millis() - timer > timeStep) {
    // update animation
    animStep = (animStep+1) %3;
    timer = millis();
    Serial.println(animStep);
  }
  int start = 32;
  int len = 15;
  for(int i = start; i < start + len; i = i + 3 ) {
    
      pixels0.setPixelColor(i + animStep,  pixels0.Color(0,48,255) );

  }
  
}



// Adafruit code
/*
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
*/

/* Snow Melt Map - Proof of Concept (MVP-ish)
 * Using Brian Connections Mux Prototype PCB from 2-24-2019
 * Can Output standard neopixel led data to pins A5 and A4 (Blue wires)
 * Using dma neopixel library on pins 5, 12, MOSI to not interfear with timing
 * Theese pins were modded on bypassing the MUX on the pcb and going into LS245
 * 
 * There are no exposed inputs on the board so I am using a timer to simulate
 * a button being pressed to trigger animation
 */


#include <Adafruit_NeoPixel_ZeroDMA.h>
#include "HeartBeat.h"
#include "hw.h"
#include "LedModule.h"
#include "Input.h"

HeartBeat heartBeat = HeartBeat(13); // pin

// pixels0 Holds River segments
// pixels1 Holds (City, Snow-Monitor-Site, Dam )
// pixels2 Holds (Aquaducts, Water Sheds)
Adafruit_NeoPixel_ZeroDMA pixels0(NUMPIXELS0, LEDPIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel_ZeroDMA pixels1(NUMPIXELS1, LEDPIN2, NEO_GRB + NEO_KHZ800);

// Even though its called river at the moment it only fades leds in and fades them back out

LedModule river1 = LedModule(&pixels1, 2, 10);
bool riverToggle = true;
unsigned long riverTimer = 0;
unsigned long riverTimeStep = 2500;


////**** Animation
int animStep = 0;

unsigned long timer = 0;
unsigned long timeStep = 30;

// Input global object
Input input = Input(buttonPins, NUM_BUTTONS);

// function declarations
void riverAnimate();

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
  input.begin();
}
void loop() {
  heartBeat.update();
  input.update();
  //clearLeds();

  // Inputs 
  if(input.isDown(0)) {
    river1.triggerFadeIn1();
  }
  if(input.isDown(1)) {
    river1.triggerFadeOut1();
  }
  if(input.isDown(2)) {
    
  }

  //**************************River Test *************************************
  //Serial.println(millis());
  if( millis() - riverTimer > riverTimeStep) {
    if(riverToggle == true) {
      river1.triggerFadeIn1();
      //Serial.println("triggering fade in");
      riverToggle = false;
    } else { 
      //Serial.println("triggering fade out");
      river1.triggerFadeOut1();
      riverToggle = true;
    }
    riverTimer = millis();
  }
  river1.update();


/*
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
  */
  
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
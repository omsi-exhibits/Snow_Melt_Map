/* Snow Melt Map - Proof of Concept (MVP-ish)
 * Using Brian Connections Mux Prototype PCB from 2-24-2019
 * Can Output standard neopixel led data to pins A5 and A4 (Blue wires)
 * Using dma neopixel library on pins 5, 12, MOSI to not interfear with timing
 * Theese pins were modded on bypassing the MUX on the pcb and going into LS245
 * 
 * There are no exposed inputs on the board so I am using a timer to simulate
 * a button being pressed to trigger animation
 */


//#include <Adafruit_NeoPixel_ZeroDMA.h>
#include <FastLED.h>
#include "HeartBeat.h"
//#include "hw.h"
#include "hw_teensy.h"
#include "LedModule.h"
#include "LedSegment.h"
#include "Input.h"

HeartBeat heartBeat = HeartBeat(13); // pin

// pixels0 Holds River segments
// pixels1 Holds (Water Areas, Cities, Tractors, Dams, Snow-Monitor-Site, Map-Key)
//Adafruit_NeoPixel_ZeroDMA pixels0(NUMPIXELS0, LEDPIN1, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel_ZeroDMA pixels1(NUMPIXELS1, LEDPIN2, NEO_GRB + NEO_KHZ800);

CRGB leds0[NUMPIXELS0]; // UI strip
CRGB leds1[NUMPIXELS1]; // main strip

 

// River Segments
#define CRS_LENGTH 9
LedSegment caliRiverSegments[CRS_LENGTH];
LedModule river1 = LedModule(leds1, caliRiverSegments, CRS_LENGTH);

#define SS_LENGTH 7
LedSegment snowSiteSegments[SS_LENGTH];
//LedModule snowSites = LedModule(&pixels1, snowSiteSegments, 2);

bool riverToggle = true;
unsigned long riverTimer = 0;
unsigned long riverTimeStep = 2200;

// Input global object
Input input = Input(buttonPins, NUM_BUTTONS);

/********************** function definitions *************************/

// configures all the river segments. Reference the spreadsheet for indexes and segment lengths
void configLedSegments() {
  // config(start_index, length, connects_to_segment, connects_at_index, segment_type )
  // River Segments
  caliRiverSegments[0].config(0, 8, &caliRiverSegments[1], 0, RIVER_ASC);
  caliRiverSegments[1].config(8, 14, &caliRiverSegments[5], 0, RIVER_ASC);
  caliRiverSegments[2].config(22, 7, &caliRiverSegments[1], 0, RIVER_ASC);
  caliRiverSegments[3].config(29, 5, &caliRiverSegments[2], 0, RIVER_ASC);
  caliRiverSegments[4].config(34, 5, &caliRiverSegments[5], 0, RIVER_ASC);
  caliRiverSegments[5].config(39, 3, NULL, 0, RIVER_ASC);
  caliRiverSegments[6].config(42, 2, NULL, 0, DAM);
  caliRiverSegments[7].config(44, 2, NULL, 0, CITY);
  caliRiverSegments[8].config(46, 104, NULL, 0, SNOWSITE);
  // Snow Site Segments
  snowSiteSegments[0].config(0, 4, NULL, 0, SNOWSITE);
  snowSiteSegments[1].config(4, 5, NULL, 0, SNOWSITE);
}
void clearLeds() {
  fill_solid(leds0, NUMPIXELS0, CRGB::Black);
  fill_solid(leds1, NUMPIXELS1, CRGB::Black);
  //pixels0.clear();
  //pixels1.clear();
}
void drawLeds() {
    //pixels0.show();
    //pixels1.show(); 
    FastLED.show();
    delay(25);
}

/************************* SETUP ***********************/
void setup() {
  
  //FastLED.addLeds<NEOPIXEL, LEDPIN2>(leds1, 600);
  // for teensy4.0 use this one
  FastLED.addLeds<1, WS2813, LEDPIN2, GRB>(leds1, NUMPIXELS1);
  //FastLED.addLeds<NUM_STRIPS, WS2813, LED_PIN, RGB>(leds, NUM_LEDS);

  configLedSegments();
  //pixels0.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  //pixels1.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  clearLeds();
  input.begin();
}
void loop() {
  /*
  unsigned long timer = millis();
  static uint8_t hue = 0;
  FastLED.showColor(CHSV(hue++, 255, 255));
  delay(1);
  unsigned long timeSpent = millis() - timer;
  Serial.print("TimeSpent: ");
  Serial.println(timeSpent);
  */

  heartBeat.update();
  input.update();
  //clearLeds();

  // Inputs 
  if(input.isDown(0)) {
  }
  if(input.isDown(1)) {
  }
  if(input.isDown(2)) {
    
  }
  

  //**************************River Test *************************************
  unsigned int tStep = 0;
  if(riverToggle == true)
    tStep = riverTimeStep;
  else
    tStep = riverTimeStep * 4;

  if( millis() - riverTimer > tStep) {
    if(riverToggle == true) {
      river1.triggerFadeIn();
      Serial.println("triggering fade in");
      riverToggle = false;
    } else { 
      Serial.println("triggering fade out");
      river1.triggerFadeOut();
      riverToggle = true;
    }
    riverTimer = millis();
  }
  river1.update();

  

  
  drawLeds();
  
}


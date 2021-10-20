/* Snow Melt Map - Proof of Concept (MVP-ish)
 * 
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


// leds0 Holds (Water Areas, Cities, Tractors, Dams, Snow-Monitor-Site, Map-Key)
//CRGB leds0[NUMPIXELS0]; // UI strip
//CRGB leds1[NUMPIXELS1]; // main strip, that has all the river segments
CRGB leds0[NUM_PIXELS_PER_STRIP]; // UI strip
CRGB leds1[NUM_PIXELS_PER_STRIP]; // main strip, that has all the rivers and activities

// combines the leds0 and leds1 arrays together
// so that fast led can do multiple strips out on a teensy 
CRGB ledsAll[NUM_PIXELS_PER_STRIP * NUM_STRIPS]; 

// Snow sites
#define SS_LENGTH 1
LedSegment snowSiteSegments[SS_LENGTH];
LedModule snowSites = LedModule(leds1, snowSiteSegments, SS_LENGTH);
//LedModule snowSites = LedModule(&pixels1, snowSiteSegments, 2);

// River Segments
#define CRS_LENGTH 1
LedSegment caliRiverSegments[CRS_LENGTH];
LedModule river1 = LedModule(leds0, caliRiverSegments, CRS_LENGTH);


bool riverToggle = true;
unsigned long riverTimer = 0;
unsigned long riverTimeStep = 2200;

// Input global object
Input input = Input(buttonPins, NUM_BUTTONS);

/********************** function definitions *************************/

// configures all the river segments. Reference the spreadsheet for indexes and segment lengths
void configLedSegments() {
  // config(start_index, length, connects_to_segment (NULL if empty), connects_at_index (0 if not needed), segment_type )
  // River Segments
  caliRiverSegments[0].config(0, 450,  NULL, 0, SNOWSITE);
  /*
  caliRiverSegments[0].config(0, 8,  &caliRiverSegments[1], 3, RIVER_ASC);
  caliRiverSegments[1].config(8, 14, &caliRiverSegments[5], 0, RIVER_ASC);
  caliRiverSegments[2].config(22, 7, &caliRiverSegments[1], 12, RIVER_ASC);
  caliRiverSegments[3].config(29, 5, &caliRiverSegments[2], 3, RIVER_ASC);
  caliRiverSegments[4].config(34, 5, &caliRiverSegments[5], 0, RIVER_ASC);
  caliRiverSegments[5].config(39, 3, NULL, 0, RIVER_ASC);
  caliRiverSegments[6].config(42, 2, NULL, 0, DAM);
  caliRiverSegments[7].config(44, 2, NULL, 0, CITY);
  caliRiverSegments[8].config(46, 104+200, NULL, 0, RIVER_ASC);
  */
  // Snow Site Segments
  snowSiteSegments[0].config(0, 300, NULL, 0, SNOWSITE);
  /*
  snowSiteSegments[0].config(0, 24, NULL, 0, SNOWSITE);
  snowSiteSegments[1].config(24, 2, NULL, 0, SNOWSITE);
  snowSiteSegments[2].config(26, 15, NULL, 0, SNOWSITE);
  snowSiteSegments[3].config(41, 2, NULL, 0, SNOWSITE);
  snowSiteSegments[4].config(43, 2, NULL, 0, SNOWSITE);
  snowSiteSegments[5].config(45, 154, NULL, 0, SNOWSITE);
  */
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
  for(int i = 0 ; i < NUM_PIXELS_PER_STRIP; i ++) {
    ledsAll[i] = leds0[i];
  }
  for(int i = 0 ; i < NUM_PIXELS_PER_STRIP; i ++) {
    ledsAll[NUM_PIXELS_PER_STRIP + i] = leds1[i];
  }
  FastLED.show();
  delay(25);
}

/************************* SETUP ***********************/
void setup() {
  //heartbeat led
  pinMode(13,OUTPUT);
  
  //FastLED.addLeds<NEOPIXEL, LEDPIN2>(leds1, 600);
  // for teensy4.0 use this one

  // only one works
  //FastLED.addLeds<2, WS2813, LEDPIN0, GRB>(leds0, NUMPIXELS0);
  //FastLED.addLeds<2, WS2813, LEDPIN1, GRB>(leds1, NUMPIXELS1);

  // my hack to combine CRGB arrays
  FastLED.addLeds<NUM_STRIPS, WS2812, LEDPIN_PARALLEL, GRB>(ledsAll, NUM_PIXELS_PER_STRIP);
  //FastLED.addLeds<NUM_STRIPS, WS2813, LED_PIN, RGB>(leds, NUM_LEDS);
  //FastLED.setBrightness(64);
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
    tStep = riverTimeStep * 2;
  else
    tStep = riverTimeStep * 3;

  if( millis() - riverTimer > tStep) {
    if(riverToggle == true) {
      river1.triggerFadeIn();
      snowSites.triggerFadeIn();
      Serial.println("triggering fade in");
      riverToggle = false;
    } else { 
      Serial.println("triggering fade out");
      river1.triggerFadeOut();
      snowSites.triggerFadeOut();
      riverToggle = true;
    }
    riverTimer = millis();
  }
  river1.update();
  snowSites.update();


  

  
  drawLeds();
  
}


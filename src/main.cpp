/* Snow Melt Map - Proof of Concept (MVP-ish)
 * 
 */

#include <FastLED.h>
#include "HeartBeat.h"
//#include "hw.h"
#include "hw_teensy.h"
#include "LedModule.h"
#include "LedSegment.h"
#include "Input.h"

HeartBeat heartBeat = HeartBeat(13); // pin

CRGB leds0[NUM_PIXELS_PER_STRIP]; // River Segments
CRGB leds1[NUM_PIXELS_PER_STRIP]; // (Water Areas, Cities, Tractors, Dams, Snow-Monitor-Site, Map-Key)

// combines the leds0 and leds1 arrays together
// so that fast led can do multiple strips out on a teensy 
CRGB ledsAll[NUM_PIXELS_PER_STRIP * NUM_STRIPS]; 

// Snow sites
#define SS_LENGTH 34
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
  caliRiverSegments[0].config(0, 348,  NULL, 0, RIVER_ASC);
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
  //snowSiteSegments[0].config(0, 189, NULL, 0, CITY); // All none-river leds
  
  
  // Section 1
  snowSiteSegments[0].config(0, 2, NULL, 0, CITY);
  snowSiteSegments[1].config(2, 24, NULL, 0, WATERAREA);
  snowSiteSegments[2].config(26, 16, NULL, 0, WATERAREA);
  snowSiteSegments[3].config(42, 2, NULL, 0, TRACTOR);
  snowSiteSegments[4].config(44, 2, NULL, 0, TRACTOR);
  snowSiteSegments[5].config(46, 1, NULL, 0, DAM); // Dam Imperial Diversion
  snowSiteSegments[6].config(47, 1, NULL, 0, DAM); // Dam Parker
  snowSiteSegments[7].config(48, 1, NULL, 0, DAM); // Dam Hoover
  snowSiteSegments[8].config(49, 2, NULL, 0, CITY); // Las Vegas
  snowSiteSegments[9].config(51, 1, NULL, 0, SNOWSITE); // Las Vegas

  // Section 2
  snowSiteSegments[10].config(52, 12, NULL, 0, SNOWSITE); // snowsites O11 - O22
  snowSiteSegments[11].config(64, 2, NULL, 0, WATERAREA); // Start of Key icons
  snowSiteSegments[12].config(66, 1, NULL, 0, SNOWSITE); 
  snowSiteSegments[13].config(67, 2, NULL, 0, TRACTOR); 
  snowSiteSegments[14].config(69, 2, NULL, 0, CITY); 
  snowSiteSegments[15].config(71, 1, NULL, 0, DAM); 
  snowSiteSegments[16].config(72, 1, NULL, 0, RIVER_ASC);  // River segment
  snowSiteSegments[17].config(73, 1, NULL, 0, RIVER_ASC); // End of key - aquaduct
  snowSiteSegments[18].config(74, 20, NULL, 0, WATERAREA); // Water Area 3
  snowSiteSegments[19].config(94, 7, NULL, 0, SNOWSITE); // Snow sites O31-O37
  snowSiteSegments[20].config(101, 1, NULL, 0, DAM); // Dam Blue Mesa

  // Section 3
  snowSiteSegments[21].config(102, 1, NULL, 0, DAM); // O39
  snowSiteSegments[22].config(103, 20, NULL, 0, WATERAREA); // O40 - Waterarea 4
  snowSiteSegments[23].config(123, 24, NULL, 0, WATERAREA); // O41 - Waterarea 4
  snowSiteSegments[24].config(147, 5, NULL, 0, SNOWSITE); // O42 - O46 Snowsites

  // Section 4
  snowSiteSegments[25].config(152, 9, NULL, 0, SNOWSITE); // O47 - O55 Snowsites
  snowSiteSegments[26].config(161, 2, NULL, 0, CITY); // O56 - Grand Junction 
  snowSiteSegments[27].config(163, 2, NULL, 0, TRACTOR); // O57 Tracktor 3
  snowSiteSegments[28].config(165, 4, NULL, 0, SNOWSITE); // O58 - O61 Snowsites
  snowSiteSegments[29].config(169, 1, NULL, 0, DAM); // O62 Flaming Gorge
  snowSiteSegments[30].config(170, 8, NULL, 0, SNOWSITE); // O63 - O70 Snowsites
  snowSiteSegments[31].config(178, 5, NULL, 0, WATERAREA); // O71 Water Area 6
  snowSiteSegments[32].config(183, 7, NULL, 0, SNOWSITE); // O72 - O78 Snowsites
  snowSiteSegments[33].config(190, 1, NULL, 0, DAM); // O79 Dam Glen Canyon
  // end

  
  
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


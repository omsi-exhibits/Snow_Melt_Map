#include "LedMap.h"
/* // This throws an error
LedMap::LedMap() : coloradoMod(leds0, caliRiverSegments, CRS), snowSiteMod(leds1, snowSiteSeg, SSS)
 {
    FastLED.addLeds<NUM_STRIPS, WS2812, LEDPIN_PARALLEL, GRB>(ledsAll, NUM_PIXELS_PER_STRIP);
    //FastLED.addLeds<NUM_STRIPS, WS2813, LED_PIN, RGB>(leds, NUM_LEDS);
    //FastLED.setBrightness(64);
    configureLedSegments();
    //snowSiteMod = LedModule(leds1, snowSiteSeg, SSS);
    //coloradoMod = LedModule(leds0, caliRiverSegments, CRS);
    clearLeds();
} */
LedMap::LedMap() {
    coloradoMod.config(leds0, caliRiverSegments, CRS);
    snowSiteMod.config(leds1, snowSiteSeg, SSS);
    FastLED.addLeds<NUM_STRIPS, WS2812, LEDPIN_PARALLEL, GRB>(ledsAll, NUM_PIXELS_PER_STRIP);
    //FastLED.addLeds<NUM_STRIPS, WS2813, LED_PIN, RGB>(leds, NUM_LEDS);
    //FastLED.setBrightness(64);
    configureLedSegments();
    //snowSiteMod = LedModule(leds1, snowSiteSeg, SSS);
    //coloradoMod = LedModule(leds0, caliRiverSegments, CRS);
    clearLeds();
}
void LedMap::update() {
    snowSiteMod.update();
    coloradoMod.update();
}

void LedMap::configureLedSegments() {
    // Section 1
    snowSiteSeg[0].config(0, 2, NULL, 0, CITY);
    snowSiteSeg[1].config(2, 24, NULL, 0, WATERAREA);
    snowSiteSeg[2].config(26, 16, NULL, 0, WATERAREA);
    snowSiteSeg[3].config(42, 2, NULL, 0, TRACTOR);
    snowSiteSeg[4].config(44, 2, NULL, 0, TRACTOR);
    snowSiteSeg[5].config(46, 1, NULL, 0, DAM); // Dam Imperial Diversion
    snowSiteSeg[6].config(47, 1, NULL, 0, DAM); // Dam Parker
    snowSiteSeg[7].config(48, 1, NULL, 0, DAM); // Dam Hoover
    snowSiteSeg[8].config(49, 2, NULL, 0, CITY); // Las Vegas
    snowSiteSeg[9].config(51, 1, NULL, 0, SNOWSITE); // Las Vega

    // River Segments
    // caliRiverSegments[0].config(0, 348,  NULL, 0, RIVER_ASC); // for testing all river segments
    caliRiverSegments[0].config(0, 8,  &caliRiverSegments[1], 3, RIVER_ASC);
    caliRiverSegments[1].config(8, 14, &caliRiverSegments[5], 0, RIVER_ASC);
    caliRiverSegments[2].config(22, 7, &caliRiverSegments[1], 12, RIVER_ASC);
    caliRiverSegments[3].config(29, 5, &caliRiverSegments[2], 3, RIVER_ASC);
    caliRiverSegments[4].config(34, 5, &caliRiverSegments[5], 0, RIVER_ASC);
    caliRiverSegments[5].config(39, 3, NULL, 0, RIVER_ASC);
    caliRiverSegments[6].config(42, 7, &caliRiverSegments[5], 0, RIVER_ASC);

    // section 2
    caliRiverSegments[7].config(49, 10,  &caliRiverSegments[5], 1, RIVER_ASC); // for testing all river segments
    caliRiverSegments[8].config(59, 10,  &caliRiverSegments[7], 6, RIVER_ASC); // for testing all river segments
    caliRiverSegments[9].config(69, 7,  &caliRiverSegments[8], 5, RIVER_ASC); // for testing all river segments
    caliRiverSegments[10].config(76, 20, NULL, 0, RIVER_ASC); // for testing all river segments
}


void LedMap::clearLeds() {
  fill_solid(leds0, NUMPIXELS0, CRGB::Black);
  fill_solid(leds1, NUMPIXELS1, CRGB::Black);
}
void LedMap::drawLeds() {
  for(int i = 0 ; i < NUM_PIXELS_PER_STRIP; i ++) {
    ledsAll[i] = leds0[i];
  }
  for(int i = 0 ; i < NUM_PIXELS_PER_STRIP; i ++) {
    ledsAll[NUM_PIXELS_PER_STRIP + i] = leds1[i];
  }
  FastLED.show();
  delay(25);
}

void LedMap::triggerColoradoRiver() {
  coloradoMod.triggerFadeIn();  
}
void LedMap::triggerSnowSites() {
  snowSiteMod.triggerFadeIn();
}
void LedMap::triggerFadeOutAll() {
  coloradoMod.triggerFadeOut();
  snowSiteMod.triggerFadeOut();
}
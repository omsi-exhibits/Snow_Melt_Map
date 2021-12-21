#include "LedMap.h"
/* // This throws an error
LedMap::LedMap() : coloradoMod(leds0, coloradoRiverSeg, CRS), snowSiteMod(leds1, snowSiteSeg, SSS)
 {
    FastLED.addLeds<NUM_STRIPS, WS2812, LEDPIN_PARALLEL, GRB>(ledsAll, NUM_PIXELS_PER_STRIP);
    //FastLED.addLeds<NUM_STRIPS, WS2813, LED_PIN, RGB>(leds, NUM_LEDS);
    //FastLED.setBrightness(64);
    configureLedSegments();
    //snowSiteMod = LedModule(leds1, snowSiteSeg, SSS);
    //coloradoMod = LedModule(leds0, coloradoRiverSeg, CRS);
    clearLeds();
} */
LedMap::LedMap() : attractorMod(leds0, leds1, NUM_PIXELS_PER_STRIP, NUM_PIXELS_PER_STRIP) {
    coloradoMod.config(leds0, coloradoRiverSeg, CRS);
    coloradoExitMod.config(leds0, coloradoRiverExitSeg, CRES);
    snowSiteMod.config(leds1, snowSiteSeg, SSS);
    damMod.config(leds1, damSeg, DS);

    farmMod.config(leds1, farmSeg, FS);

    riverToVegasMod.config(leds0, riverToVegasSeg, RTLVS);
    lasVegasMod.config(leds1, lasVegasSeg, LVS);

    riverToGJCityMod.config(leds0, riverToGJCitySeg, RTGJCS);
    GJCityMod.config(leds1, GJCitySeg, LVS);

    LAMod.config(leds1, LASeg, LAS);
    riverToLAMod.config(leds0, riverToLASeg, RTLAS);

    supplyFromAfarMod.config(leds1, supplyFromAfarSeg, SFAS);
    mapKeyMod.config(leds1, mapKeySeg, MKS);

    allCitiesMod.config(leds1, allCitiesSeg, ACS);


    FastLED.addLeds<NUM_STRIPS, WS2812, LEDPIN_PARALLEL, GRB>(ledsAll, NUM_PIXELS_PER_STRIP);
    //FastLED.addLeds<NUM_STRIPS, WS2813, LED_PIN, RGB>(leds, NUM_LEDS);
    //FastLED.setBrightness(64);
    configureLedSegments();
    //snowSiteMod = LedModule(leds1, snowSiteSeg, SSS);
    //coloradoMod = LedModule(leds0, coloradoRiverSeg, CRS);
    previousButton = -1;
    mapKeyMod.triggerFadeIn();
    clearLeds();
}
void LedMap::update() {
    snowSiteMod.update();
    damMod.update();
    farmMod.update();
    coloradoMod.update();
    coloradoExitMod.update();
    riverToVegasMod.update();
    lasVegasMod.update();
    GJCityMod.update();
    riverToGJCityMod.update();
    LAMod.update();
    riverToLAMod.update();
    supplyFromAfarMod.update();
    attractorMod.update();
    mapKeyMod.update();
    allCitiesMod.update();
}

void LedMap::configureLedSegments() {
    // Colorado River 
    // section 3 R14 - R18
    coloradoRiverSeg[0].config(96, 20,  &coloradoRiverSeg[4]/*r18*/, 5, RIVER_ASC);
    coloradoRiverSeg[1].config(116, 7,  &coloradoRiverSeg[0]/*r14*/, 17, RIVER_ASC); 
    coloradoRiverSeg[2].config(123, 6,  &coloradoRiverSeg[1]/*r15*/, 5, RIVER_ASC);
    coloradoRiverSeg[3].config(129, 8,  &coloradoRiverSeg[4]/*r18*/, 5, RIVER_ASC);
    coloradoRiverSeg[4].config(137, 10,  &coloradoRiverSeg[5]/*r19*/, 5, RIVER_ASC);

    // section 4 R19 - R21
    coloradoRiverSeg[5].config(147, 9,  &coloradoRiverSeg[7]/*r21*/, 19, RIVER_ASC);
    coloradoRiverSeg[6].config(156, 7,  &coloradoRiverSeg[7]/*r21*/, 21, RIVER_ASC);
    coloradoRiverSeg[7].config(163, 33,  &coloradoRiverSeg[14]/*r28*/, 0, RIVER_ASC);

    // section 5 R22 - R25
    coloradoRiverSeg[8].config(196, 10,  &coloradoRiverSeg[7]/*r21*/, 12, RIVER_ASC);
    coloradoRiverSeg[9].config(206, 9,  &coloradoRiverSeg[7]/*r21*/, 16, RIVER_ASC);
    coloradoRiverSeg[10].config(215, 3,  &coloradoRiverSeg[11]/*r25*/, 6, RIVER_ASC);
    coloradoRiverSeg[11].config(218, 18,  &coloradoRiverSeg[7]/*r21*/, 26, RIVER_ASC);
    
    // section 6 R26 - R30
    coloradoRiverSeg[12].config(236, 17,  &coloradoRiverSeg[7]/*r21*/, 32, RIVER_ASC);
    coloradoRiverSeg[13].config(253, 5,  &coloradoRiverSeg[12]/*r26*/, 8, RIVER_ASC);
    coloradoRiverSeg[14].config(258, 12,  &coloradoRiverSeg[16]/*r31*/, 0, RIVER_ASC);
    coloradoRiverSeg[15].config(270, 7,  &coloradoRiverSeg[14]/*r28*/, 11, RIVER_ASC);
    coloradoRiverSeg[16].config(277, 2,  &coloradoRiverSeg[15]/*r29*/, 5, RIVER_ASC);

    // section 7 R31 - R34
    coloradoRiverSeg[17].config(279, 9,  &coloradoRiverSeg[20]/*r34*/, 0, RIVER_ASC);
    coloradoRiverSeg[18].config(288, 5,  &coloradoRiverSeg[19]/*r33*/, 2, RIVER_ASC);
    coloradoRiverSeg[19].config(293, 5,  &coloradoRiverSeg[20]/*r34*/, 0, RIVER_ASC);
    coloradoRiverSeg[20].config(298, 13,  NULL, 0, RIVER_ASC);
 
    // Just R34
    coloradoRiverExitSeg[0].config(298, 13,  NULL, 0, RIVER_ASC);

    // snow sites
    snowSiteSeg[0].config(51, 5, NULL, 0, SNOWSITE); 
    snowSiteSeg[1].config(57, 7, NULL, 0, SNOWSITE); 
    snowSiteSeg[2].config(94, 7, NULL, 0, SNOWSITE); 
    snowSiteSeg[3].config(102, 1, NULL, 0, SNOWSITE); 
    snowSiteSeg[4].config(147, 14, NULL, 0, SNOWSITE); 
    snowSiteSeg[5].config(165, 4, NULL, 0, SNOWSITE); 
    snowSiteSeg[6].config(170, 8, NULL, 0, SNOWSITE); 
    snowSiteSeg[7].config(183, 7, NULL, 0, SNOWSITE);

    // Farm Segments
    farmSeg[0].config(42, 4,  NULL, 0, TRACTOR);
    farmSeg[1].config(163, 2,  NULL, 0, TRACTOR);

    damSeg[0].config(46, 3, NULL, 0, DAM); 
    damSeg[1].config(56, 1, NULL, 0, DAM); 
    damSeg[2].config(101, 1, NULL, 0, DAM); 
    damSeg[3].config(169, 1, NULL, 0, DAM); 
    damSeg[4].config(190, 1, NULL, 0, DAM); 

    lasVegasSeg[0].config(48, 1, NULL, 0, DAM);  // hoover dam
    lasVegasSeg[1].config(49, 2, NULL, 0, CITY);  // vegas

    // river to vegas section R14 - R30
    // section 3 R14 - R18
    riverToVegasSeg[0].config(96, 20,  &riverToVegasSeg[4]/*r18*/, 5, RIVER_ASC);
    riverToVegasSeg[1].config(116, 7,  &riverToVegasSeg[0]/*r14*/, 17, RIVER_ASC); 
    riverToVegasSeg[2].config(123, 6,  &riverToVegasSeg[1]/*r15*/, 5, RIVER_ASC);
    riverToVegasSeg[3].config(129, 8,  &riverToVegasSeg[4]/*r18*/, 5, RIVER_ASC);
    riverToVegasSeg[4].config(137, 10,  &riverToVegasSeg[5]/*r19*/, 5, RIVER_ASC);

    // section 4 R19 - R21
    riverToVegasSeg[5].config(147, 9,  &riverToVegasSeg[7]/*r21*/, 19, RIVER_ASC);
    riverToVegasSeg[6].config(156, 7,  &riverToVegasSeg[7]/*r21*/, 21, RIVER_ASC);
    riverToVegasSeg[7].config(163, 33,  &riverToVegasSeg[14]/*r28*/, 0, RIVER_ASC);

    // section 5 R22 - R25
    riverToVegasSeg[8].config(196, 10,  &riverToVegasSeg[7]/*r21*/, 12, RIVER_ASC);
    riverToVegasSeg[9].config(206, 9,  &riverToVegasSeg[7]/*r21*/, 16, RIVER_ASC);
    riverToVegasSeg[10].config(215, 3,  &riverToVegasSeg[11]/*r25*/, 6, RIVER_ASC);
    riverToVegasSeg[11].config(218, 18,  &riverToVegasSeg[7]/*r21*/, 26, RIVER_ASC);
    
    // section 6 R26 - R30
    riverToVegasSeg[12].config(236, 17,  &riverToVegasSeg[7]/*r21*/, 32, RIVER_ASC);
    riverToVegasSeg[13].config(253, 5,  &riverToVegasSeg[12]/*r26*/, 8, RIVER_ASC);
    riverToVegasSeg[14].config(258, 12,  &riverToVegasSeg[16]/*r31*/, 0, RIVER_ASC);
    riverToVegasSeg[15].config(270, 7,  &riverToVegasSeg[14]/*r28*/, 11, RIVER_ASC);
    riverToVegasSeg[16].config(277, 3,  &riverToVegasSeg[15]/*r29*/, 5, RIVER_ASC);

    // river to GJ city
    // Partial R21 (0-12leds), R22
    riverToGJCitySeg[0].config(163, 13,  NULL, 0, RIVER_ASC);
    riverToGJCitySeg[1].config(196, 10,  NULL, 0, RIVER_ASC);
    GJCitySeg[0].config(161, 2, NULL, 0, CITY);
    GJCitySeg[1].config(101, 1, NULL, 0, DAM);

    LASeg[0].config(0, 2, NULL, 0, CITY);
    // River Segments supplying water to LA
    // section 1
    riverToLASeg[0].config(0, 8,  &riverToLASeg[1], 3, RIVER_ASC);
    riverToLASeg[1].config(8, 14, &riverToLASeg[5], 0, RIVER_ASC);
    riverToLASeg[2].config(22, 7, &riverToLASeg[1], 12, RIVER_ASC);
    riverToLASeg[3].config(29, 5, &riverToLASeg[2], 3, RIVER_ASC);
    riverToLASeg[4].config(34, 5, &riverToLASeg[5], 0, RIVER_ASC);
    riverToLASeg[5].config(39, 3, NULL, 0, RIVER_ASC);
    riverToLASeg[6].config(42, 7, &riverToLASeg[5], 0, RIVER_ASC);

    // section 2
    riverToLASeg[7].config(49, 10,  &riverToLASeg[5], 1, RIVER_ASC); // for testing all river segments
    riverToLASeg[8].config(59, 10,  &riverToLASeg[7], 6, RIVER_ASC); // for testing all river segments
    riverToLASeg[9].config(69, 7,  &riverToLASeg[8], 5, RIVER_ASC); // for testing all river segments
    riverToLASeg[10].config(76, 20, NULL, 0, RIVER_ASC); // for testing all river segments

    // for section 3 - 6 turn on the coloradoRiverSeg
    // section 3 R14 - R18
    riverToLASeg[11].config(96, 20,  &riverToLASeg[15]/*r18*/, 5, RIVER_ASC);
    riverToLASeg[12].config(116, 7,  &riverToLASeg[11]/*r14*/, 17, RIVER_ASC); 
    riverToLASeg[13].config(123, 6,  &riverToLASeg[12]/*r15*/, 5, RIVER_ASC);
    riverToLASeg[14].config(129, 8,  &riverToLASeg[15]/*r18*/, 5, RIVER_ASC);
    riverToLASeg[15].config(137, 10,  &riverToLASeg[16]/*r19*/, 5, RIVER_ASC);

    // section 4 R19 - R21
    riverToLASeg[16].config(147, 9,  &riverToLASeg[18]/*r21*/, 19, RIVER_ASC);
    riverToLASeg[17].config(156, 7,  &riverToLASeg[18]/*r21*/, 21, RIVER_ASC);
    riverToLASeg[18].config(163, 33,  &riverToLASeg[25]/*r28*/, 0, RIVER_ASC);

    // section 5 R22 - R25
    riverToLASeg[19].config(196, 10,  &riverToLASeg[18]/*r21*/, 12, RIVER_ASC);
    riverToLASeg[20].config(206, 9,  &riverToLASeg[18]/*r21*/, 16, RIVER_ASC);
    riverToLASeg[21].config(215, 3,  &riverToLASeg[22]/*r25*/, 6, RIVER_ASC);
    riverToLASeg[22].config(218, 18,  &riverToLASeg[18]/*r21*/, 26, RIVER_ASC);
    
    // section 6 R26 - R30
    riverToLASeg[23].config(236, 17,  &riverToLASeg[18]/*r21*/, 32, RIVER_ASC);
    riverToLASeg[24].config(253, 5,  &riverToLASeg[23]/*r26*/, 8, RIVER_ASC);
    riverToLASeg[25].config(258, 12,  &riverToLASeg[27]/*r31*/, 0, RIVER_ASC);
    riverToLASeg[26].config(270, 7,  &riverToLASeg[25]/*r28*/, 11, RIVER_ASC);
    riverToLASeg[27].config(277, 2,  &riverToLASeg[26]/*r29*/, 5, RIVER_ASC);

    // section 7 R31 - R35(old R13)
    riverToLASeg[28].config(279, 9,  NULL, 0, RIVER_ASC);
    riverToLASeg[29].config(288, 5,  &riverToLASeg[30]/*r33*/, 2, RIVER_ASC);
    riverToLASeg[30].config(293, 6,  NULL, 0, RIVER_ASC);
    //riverToLASeg[31].config(298, 1,  NULL, 0, RIVER_ASC); // just first pixel of R34

    // section 7 R35
    riverToLASeg[31].config(311, 12,  NULL, 0, RIVER_ASC);
    // section 8 R36
    riverToLASeg[32].config(323, 24,  NULL, 0, RIVER_ASC); // end

    // Water areas
    supplyFromAfarSeg[0].config(2, 24, NULL, 0, WATERAREA);
    supplyFromAfarSeg[1].config(26, 16, NULL, 0, WATERAREA);
    supplyFromAfarSeg[2].config(74, 20, NULL, 0, WATERAREA);
    supplyFromAfarSeg[3].config(103, 20, NULL, 0, WATERAREA);
    supplyFromAfarSeg[4].config(123, 24, NULL, 0, WATERAREA);
    supplyFromAfarSeg[5].config(178, 5, NULL, 0, WATERAREA);

    // Map Key icons
    mapKeySeg[0].config(64, 2, NULL, 0, WATERAREA);
    mapKeySeg[1].config(66, 1, NULL, 0, SNOWSITE);
    mapKeySeg[2].config(67, 2, NULL, 0, TRACTOR);
    mapKeySeg[3].config(69, 2, NULL, 0, CITY);
    mapKeySeg[4].config(71, 1, NULL, 0, DAM);
    mapKeySeg[5].config(72, 1, NULL, 0, RIVER_ASC); // river
    mapKeySeg[6].config(73, 1, NULL, 0, RIVER_ASC); // Aqueduct

    allCitiesSeg[0].config(0, 2, NULL, 0, CITY); // LA
    allCitiesSeg[1].config(49, 2, NULL, 0, CITY);  // vegas
    allCitiesSeg[2].config(161, 2, NULL, 0, CITY); // GJcity
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
void LedMap::triggerVegas() {
  lasVegasMod.triggerFadeIn();
  riverToVegasMod.triggerFadeIn();
}
void LedMap::triggerGJCity() {
  riverToGJCityMod.triggerFadeIn();
  GJCityMod.triggerFadeIn();
}
void LedMap::triggerLA() {
  LAMod.triggerFadeIn();
  riverToLAMod.triggerFadeIn();
}
void LedMap::triggerMapKey() {
  mapKeyMod.triggerFadeIn();
}

void LedMap::triggerFadeOutAll() {
  coloradoMod.triggerFadeOut();
  snowSiteMod.triggerFadeOut();
  damMod.triggerFadeOut();
  farmMod.triggerFadeOut();
  lasVegasMod.triggerFadeOut();
  riverToVegasMod.triggerFadeOut();
  GJCityMod.triggerFadeOut();
  riverToGJCityMod.triggerFadeOut();
  LAMod.triggerFadeOut();
  riverToLAMod.triggerFadeOut();
  supplyFromAfarMod.triggerFadeOut();
}
void LedMap::triggerFadeInAll() {
  coloradoMod.triggerFadeIn();
  snowSiteMod.triggerFadeIn();
  damMod.triggerFadeIn();
  farmMod.triggerFadeIn();
  lasVegasMod.triggerFadeIn();
  riverToVegasMod.triggerFadeIn();
}

void LedMap::receiveInput(int butt) {
  if(previousButton == butt)
    return;
  // debounce the input like in nakaya
  if (butt > 0 && butt <= NUM_MODULES) {
    // fadeOut previous button pressed ledModules
    
    switch(previousButton) {
      case 1:
        coloradoMod.triggerFadeOut();
        break;
      case 2:
        snowSiteMod.triggerFadeOut();
        break;
      case 3:
        damMod.triggerFadeOut();
        break;
      case 4:
        lasVegasMod.triggerFadeOut();
        riverToVegasMod.triggerFadeOut();
        break;
      case 5:
        farmMod.triggerFadeOut();
        break;
      case 6:
        GJCityMod.triggerFadeOut();
        riverToGJCityMod.triggerFadeOut();
        break;
      case 7:
        supplyFromAfarMod.triggerFadeOut();
        break;
      case 8:
        LAMod.triggerFadeOut();
        riverToLAMod.triggerFadeOut();
        break;
      case 9:
        riverToLAMod.triggerFadeOut();
        allCitiesMod.triggerFadeOut();
        coloradoExitMod.triggerFadeOut();
        break;
      case -1:
        Serial.println(F("No previous press"));
        break;
      default:
        Serial.println(F("Error out of bounds button number passed to LedMap"));
        break;
    } // end switch

    // fade in the currently pressed button LedModule
    switch(butt) {
      case 1:
        coloradoMod.triggerFadeIn();
        break;
      case 2:
        snowSiteMod.triggerFadeIn();
        break;
      case 3:
        damMod.triggerFadeIn();
        break;
      case 4:
        lasVegasMod.triggerFadeIn();
        riverToVegasMod.triggerFadeIn();
        break;
      case 5:
        farmMod.triggerFadeIn();
        break;
      case 6:
        GJCityMod.triggerFadeIn();
        riverToGJCityMod.triggerFadeIn();
        break;
      case 7:
        supplyFromAfarMod.triggerFadeIn();
        break;
      case 8:
        LAMod.triggerFadeIn();
        riverToLAMod.triggerFadeIn();
        break;
      case 9:
        // attractorMod.triggerFadeIn();
        riverToLAMod.triggerFadeInAttractor();
        allCitiesMod.triggerFadeInAttractor();
        coloradoExitMod.triggerFadeInAttractor();
        break;
      case -1:
        Serial.println(F("No previous press"));
        break;
      default:
        Serial.println(F("Error out of bounds button number passed to LedMap"));
        break;
    } // end switch
    // remember the current button as a previous button press
    previousButton = butt;

  }
}
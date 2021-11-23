#ifndef LEDMAP_H
#define LEDMAP_H
/* LedMap houses all the LedSegments that make up LedModules that get triggered on and off.
 * A LedModule stores the animation and state of the led segments that it updates and draws.
 *
 * LedMap also has the state for the the whole map. Which sections have been toggled on or toggled off.
 *
 * configureLedSegments() has all the led indexes
 */

#include <Arduino.h>
#include <FastLED.h>
#include "hw_teensy.h"
#include "LedSegment.h"
#include "LedModule.h"
#include "LedModuleAttractor.h"

// Segment lengths :: abbreviations of the LedSegment Names they are used in
// for example: SSS = snow site segments, RTLVS = river to las vegas segments
#define CRS 21
#define SSS 7

#define DS 4
#define LVS 2
#define RTLVS 17

#define FS 2
#define GJCS 2
#define RTGJCS 2

#define RTLAS 13
#define LAS 1

#define SFAS 6

#define MKS 7

// used to map button presses to ledModules
// 8 module sets for buttons and +1 attractor
#define NUM_MODULES 9


class LedMap {
    private:
    // NUM_PIXELS_PER_STRIP and the like are declared in the hw_teensy.h
    CRGB leds0[NUM_PIXELS_PER_STRIP];
    CRGB leds1[NUM_PIXELS_PER_STRIP];
    CRGB ledsAll[NUM_PIXELS_PER_STRIP * NUM_STRIPS];

    // LED Segments
    LedSegment coloradoRiverSeg[CRS];
    LedSegment snowSiteSeg[SSS];
    LedSegment damSeg[DS];
    LedSegment farmSeg[FS];

    LedSegment lasVegasSeg[LVS];
    LedSegment riverToVegasSeg[RTLVS];

    LedSegment riverToGJCitySeg[RTGJCS];
    LedSegment GJCitySeg[GJCS];

    LedSegment riverToLASeg[RTLAS];
    LedSegment LASeg[LAS];

    LedSegment supplyFromAfarSeg[SFAS];
    LedSegment mapKeySeg[MKS];

    LedModule coloradoMod;
    LedModule snowSiteMod;
    LedModule damMod;
    LedModule farmMod;

    LedModule lasVegasMod; // includes a dam
    LedModule riverToVegasMod;

    LedModule riverToGJCityMod;
    LedModule GJCityMod; // includes the dams

    LedModule riverToLAMod;
    LedModule LAMod; //includes the dams
    
    LedModule supplyFromAfarMod;
    LedModule mapKeyMod;

    // 9th module is the attractorMod
    LedModuleAttractor attractorMod;

    int previousButton;

    public:
    LedMap();
    void update();
    void clearLeds();
    void drawLeds();
    void configureLedSegments(); // call from LedMap Constructor
    void triggerFadeOutAll();
    void triggerFadeInAll();

    void triggerColoradoRiver();
    void triggerSnowSites();
    void triggerFarms();
    void triggerDams();
    void triggerVegas();
    void triggerGJCity();
    void triggerLA();
    void triggerSupplyFromAfar();
    void triggerMapKey();

    void receiveInput(int butt);
};

#endif
#ifndef LEDMAP_H
#define LEDMAP_H
/* LedMap houses all the LedSegments that make up LedModules that get triggered on and off.
 * A LedModule stores the animation and state of the led segments that it updates and draws.
 *
 * configureLedSegments() has all the led indexes
 */

#include <Arduino.h>
#include <FastLED.h>
#include "hw_teensy.h"
#include "LedSegment.h"
#include "LedModule.h"

// Segment lengths
#define CRS 11
#define SSS 10
#define DS 10
#define LVS 10
#define FS 10
#define GJS 3
#define LAC 34
#define LAA 8


class LedMap {
    private:
    LedSegment caliRiverSegments[CRS];
    LedSegment snowSiteSeg[SSS];
    LedSegment damSeg[DS];
    LedSegment lasVegasSeg[LVS];
    LedSegment farmSeg[FS];
    LedSegment grandJunctionSeg[GJS];
    LedSegment laSupplyFromColoradoSeg[LAC];
    LedSegment laSupplyFromAfarSeg[LAA];
    

    // NUM_PIXELS_PER_STRIP and the like are declared in the hw_teensy.h
    CRGB leds0[NUM_PIXELS_PER_STRIP];
    CRGB leds1[NUM_PIXELS_PER_STRIP];

    CRGB ledsAll[NUM_PIXELS_PER_STRIP * NUM_STRIPS];

    LedModule coloradoMod;
    LedModule snowSiteMod;
    LedModule damMod;

    public:
    LedMap();
    void update();
    void clearLeds();
    void drawLeds();
    void configureLedSegments(); // call from arduino setup()
    void triggerColoradoRiver();
    void triggerSnowSites();
    void triggerFadeOutAll();
};

#endif
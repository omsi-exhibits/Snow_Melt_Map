#ifndef LEDMODULEATTRACTOR_H
#define LEDMODULEATTRACTOR_H
#include <Arduino.h>
#include "FastLED.h"
#include "LedSegment.h"

class LedModuleAttractor {
    public:
        LedModuleAttractor(CRGB* leds0, CRGB* leds1, int numLeds0, int numLeds1);
        void update();
        void draw();
        void config(LedSegment coloradoRiverSeg[], int numColSegs, LedSegment snowSiteSeg[], int numSnowSegs);

        void triggerFadeIn();
        void triggerFadeOut();

    private:
        CRGB* pLeds0;
        CRGB* pLeds1;
        LedSegment* pColoradoRiverSeg;
        int mNumColoradoSegs;
        LedSegment* pSnowSiteSegs;
        int mNumSnowSiteSegs;
        uint16_t mNumLeds0;
        uint16_t mNumLeds1;
        int mState; // 0 - idle, 1 - draw sparkles, 2 - fade out 
        unsigned long timer;
        static const unsigned long fadeOutTime = 1000;
};

#endif
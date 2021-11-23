#include "LedModuleAttractor.h"

LedModuleAttractor::LedModuleAttractor(CRGB* leds0, CRGB* leds1, int numLeds0, int numLeds1) {
    pLeds0 = leds0;
    pLeds1 = leds1;
    mNumLeds0 = numLeds0;
    mNumLeds1 = numLeds1;
    timer = 0;
    mState = 0;
}

void LedModuleAttractor::config(LedSegment coloradoRiverSeg[], int numColSegs, LedSegment snowSiteSeg[], int numSnowSegs) {
    pColoradoRiverSeg = coloradoRiverSeg;
    mNumColoradoSegs = numColSegs;
    pSnowSiteSegs = snowSiteSeg;
    mNumSnowSiteSegs = numSnowSegs;
}


void LedModuleAttractor::update() {
    if(mState == 0) {
        //idle state do nothing
    } else if(mState == 1){
        // draw sparkles
        int numSparkles = 8;
        for(int i = 0; i < numSparkles; i ++) {
            int j = random(mNumLeds0);
            pLeds0[j] = CRGB::CadetBlue;
        }
        for(int i = 0; i < numSparkles / 4; i ++) {
            int j = random(mNumLeds1);
            pLeds1[j] = CRGB::CadetBlue;
        }
        // fade out strip
        fadeToBlackBy(pLeds0, mNumLeds0, 64);
        fadeToBlackBy(pLeds1, mNumLeds1, 64);
    } else if (mState == 2) {
        fadeToBlackBy(pLeds0, mNumLeds0, 128);
        fadeToBlackBy(pLeds1, mNumLeds1, 128);
        if(millis() - timer > fadeOutTime) {
            mState = 0;
        }
        
    } // end mState
}
void LedModuleAttractor::draw() {

}
void LedModuleAttractor::triggerFadeOut() {
    mState = 2;
    timer = millis();
}
void LedModuleAttractor::triggerFadeIn() {
    mState = 1;
}

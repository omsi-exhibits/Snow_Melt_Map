#include "LedModule.h"
#include "LedSegment.h"
#include <Adafruit_NeoPixel_ZeroDMA.h>
//#include <Arduino.h>
/*
  int i = 0;
  // draw Dams - golden yellow
    pixels1.setPixelColor(i, pixels0.Color(255,255,0));

  // City - purple
    pixels1.setPixelColor(i, pixels0.Color(160,0, 255));

  // Snow Sample site
    pixels1.setPixelColor(i, pixels0.Color(255,255,255));
  
  // water receiving - pink
    pixels1.setPixelColor(i, pixels0.Color(255, 20, 100));
  */
// Static member definitions  
uint32_t LedModule::mDamColor = Adafruit_NeoPixel_ZeroDMA::Color(255,255,0);
uint32_t LedModule::mCityColor = Adafruit_NeoPixel_ZeroDMA::Color(160,0,200);
uint32_t LedModule::mSnowSiteColor = Adafruit_NeoPixel_ZeroDMA::Color(255,255,255);
uint32_t LedModule::mWaterAreaColor = Adafruit_NeoPixel_ZeroDMA::Color(255,20,100);
uint32_t LedModule::mTractorColor = Adafruit_NeoPixel_ZeroDMA::Color(255,200,200);
uint32_t LedModule::mHalfRiverColor = Adafruit_NeoPixel_ZeroDMA::Color(0,0,127);
uint32_t LedModule::mBrightRiverColor = Adafruit_NeoPixel_ZeroDMA::Color(40,40,255);

LedModule::LedModule(Adafruit_NeoPixel_ZeroDMA* strip, LedSegment* ledSegments, int numLedSegments) {
    pLedSegments = ledSegments;
    mNumLedSegments = numLedSegments;

    mTimer = 0;
    mAnimationStep = 0;
    mState = IDLE_STATIC;
    pStrip = strip;

    mFadeStartColor = Adafruit_NeoPixel_ZeroDMA::Color(0,0,0);
    mTargetColor = Adafruit_NeoPixel_ZeroDMA::Color(0,0,0);
    //mCurrentFadeOutDuration = 0;

    mFadeDamColor = Adafruit_NeoPixel_ZeroDMA::Color(0,0,0);
    mFadeSnowSiteColor = Adafruit_NeoPixel_ZeroDMA::Color(0,0,0);
    mFadeCityColor = Adafruit_NeoPixel_ZeroDMA::Color(0,0,0);
    mFadeTractorColor = Adafruit_NeoPixel_ZeroDMA::Color(0,0,0);
    mFadeWaterAreaColor = Adafruit_NeoPixel_ZeroDMA::Color(0,0,0);
    mFadeHalfRiverColor = Adafruit_NeoPixel_ZeroDMA::Color(0,0,0);
    mFadeBrightRiverColor = Adafruit_NeoPixel_ZeroDMA::Color(0,0,0);
}
void LedModule::begin() {
    // prob not needed
}
void LedModule::clearAllSegments() {
    uint32_t black = Adafruit_NeoPixel_ZeroDMA::Color(0,0,0);
    for(int j = 0; j < mNumLedSegments; j ++) {
        int si = pLedSegments[j].mStartIndex;
        int nl = pLedSegments[j].mLength;
        for(int i = si; i < si + nl; i++) {
            pStrip->setPixelColor(i , black);
        }
        
    }
}
void LedModule::clearNotRiverSegments() {
    uint32_t black = Adafruit_NeoPixel_ZeroDMA::Color(0,0,0);
    for(int j = 0; j < mNumLedSegments; j ++) {
        int si = pLedSegments[j].mStartIndex;
        int nl = pLedSegments[j].mLength;
        SEGMENT_TYPE type = pLedSegments[j].mType;
        //enum SEGMENT_TYPE { RIVER_ASC, RIVER_DES, DAM, SNOWSITE, CITY, WATERAREA, TRACTOR };
        if(type != RIVER_ASC || type != RIVER_DES )
        for(int i = si; i < si + nl; i++) {
            pStrip->setPixelColor(i , black);
        }
        
    }
}
void LedModule::fillRiverSegments(uint32_t color) {
    for(int j = 0; j < mNumLedSegments; j ++) {
        int si = pLedSegments[j].mStartIndex;
        int nl = pLedSegments[j].mLength;
        SEGMENT_TYPE type = pLedSegments[j].mType;
        //enum SEGMENT_TYPE { RIVER_ASC, RIVER_DES, DAM, SNOWSITE, CITY, WATERAREA, TRACTOR };
        if(type == RIVER_ASC || type == RIVER_DES )
        for(int i = si; i < si + nl; i++) {
            pStrip->setPixelColor(i , color);
        }
        
    }
}
void LedModule::clearRiverSegments() {
    uint32_t black = Adafruit_NeoPixel_ZeroDMA::Color(0,0,0);
    for(int j = 0; j < mNumLedSegments; j ++) {
        int si = pLedSegments[j].mStartIndex;
        int nl = pLedSegments[j].mLength;
        SEGMENT_TYPE type = pLedSegments[j].mType;
        //enum SEGMENT_TYPE { RIVER_ASC, RIVER_DES, DAM, SNOWSITE, CITY, WATERAREA, TRACTOR };
        if(type == RIVER_ASC || type == RIVER_DES )
        for(int i = si; i < si + nl; i++) {
            pStrip->setPixelColor(i , black);
        }
        
    }
}
void LedModule::drawFadeSegments() {
    //Draw FadeIn / FadeOutSegments
    
    // Serial.println(deltaTime);
    // Calculate all fade Colors For Dams, Cities, WaterAreas, Tractors, riversHalfway?
    if(mToggleState == FADEIN) {
        float deltaTime = ((float)(millis() - mFadeInStartTime)/(float)mFadeInDuration);
        mFadeDamColor = lerpColor(0, mDamColor, deltaTime);
        mFadeCityColor = lerpColor(0, mCityColor, deltaTime);
        mFadeSnowSiteColor = lerpColor(0, mSnowSiteColor, deltaTime);
        mFadeTractorColor = lerpColor(0, mTractorColor, deltaTime);
        mFadeWaterAreaColor = lerpColor(0, mWaterAreaColor, deltaTime);
        mFadeHalfRiverColor = lerpColor(0, mHalfRiverColor, deltaTime);

        mFadeDamColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeDamColor);
        mFadeCityColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeCityColor);
        mFadeSnowSiteColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeSnowSiteColor);
        mFadeTractorColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeTractorColor);
        mFadeWaterAreaColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeWaterAreaColor);
        mFadeHalfRiverColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeHalfRiverColor);
    } else if (mToggleState == FADEOUT) {
        float deltaTime = ((float)(millis() - mFadeOutStartTime)/(float)mFadeOutDuration);
        mFadeDamColor = lerpColor(mDamColor, 0, deltaTime);
        mFadeCityColor = lerpColor(mCityColor, 0, deltaTime);
        mFadeSnowSiteColor = lerpColor(mSnowSiteColor, 0, deltaTime);
        mFadeTractorColor = lerpColor(mTractorColor, 0, deltaTime);
        mFadeWaterAreaColor = lerpColor(mWaterAreaColor, 0, deltaTime);
        mFadeHalfRiverColor = lerpColor(mHalfRiverColor, 0, deltaTime);

        // Needs more testing
        // Might cause a brightness jump when fading out
        mFadeDamColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeDamColor);
        mFadeCityColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeCityColor);
        mFadeSnowSiteColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeSnowSiteColor);
        mFadeTractorColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeTractorColor);
        mFadeWaterAreaColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeWaterAreaColor);
        mFadeHalfRiverColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeHalfRiverColor);
    }

    for(int j = 0; j < mNumLedSegments; j ++) {
        int si = pLedSegments[j].mStartIndex;
        int nl = pLedSegments[j].mLength;

        SEGMENT_TYPE type = pLedSegments[j].mType;
        if(type == DAM) {
            for(int i = si; i < si + nl; i++) {
                pStrip->setPixelColor(i , mFadeDamColor);
            }
        } else if(type == CITY) { 
            for(int i = si; i < si + nl; i++) {
                pStrip->setPixelColor(i , mFadeCityColor);
            }
            
        } else if(type == SNOWSITE) { 
            for(int i = si; i < si + nl; i++) {
                pStrip->setPixelColor(i , mFadeSnowSiteColor);
            }
            
        } else if(type == TRACTOR) { 
            for(int i = si; i < si + nl; i++) {
                pStrip->setPixelColor(i , mFadeTractorColor);
            }
            
        } else if(type == WATERAREA) { 
            for(int i = si; i < si + nl; i++) {
                pStrip->setPixelColor(i , mFadeWaterAreaColor);
            }
            
        } else if(type == RIVER_ASC || type == RIVER_DES) { 
            for(int i = si; i < si + nl; i++) {
                pStrip->setPixelColor(i , mFadeHalfRiverColor);
            }
            
        }

        
    } // end for loop segments
    
}
void LedModule::drawAnimatedSegments() {

    for(int j = 0; j < mNumLedSegments; j ++) {
        int si = pLedSegments[j].mStartIndex;
        int nl = pLedSegments[j].mLength;

        SEGMENT_TYPE dir = pLedSegments[j].mType;
        if(dir == RIVER_ASC) {
            // Marque the strip leds. Ascending order
            for(int i = si; i < si + nl; i++) {
                if(i%3 == mAnimationStep) 
                    pStrip->setPixelColor(i , Adafruit_NeoPixel_ZeroDMA::Color(0,0,255));
            }
        } else if(dir == RIVER_DES) { 
            // Marque in Descending order
            int aStep = mAnimationStep;
            if(aStep == 2)
                aStep = 0;
            else if(aStep == 0)
                aStep = 2;
            for(int i = si + nl - 1; i >= si; i--) {
                if(i%3 == aStep) 
                    pStrip->setPixelColor(i , Adafruit_NeoPixel_ZeroDMA::Color(0,0,255));
            }
        }

        
    } // end for loop segments
}

void LedModule::update() {
    switch(mToggleState) {
        case FADEIN :
            if(millis() - mFadeInStartTime < mFadeInDuration) {
                drawFadeSegments();
            } else {
                triggerIdleAnimate();
            }
            break;
        case IDLE_ANIMATE :
            if((millis() - mTimer) > mTimeStep) {
                //advance animation pattern 
                mAnimationStep = (mAnimationStep+1) %3;
                mTimer = millis();
                //Serial.println(mAnimationStep);
                clearRiverSegments();
                //fillRiverSegments(mHalfRiverColor);
                drawAnimatedSegments();
            }
            break;
        case FADEOUT :
            if((millis() - mFadeOutStartTime) < mFadeOutDuration) {
                drawFadeSegments();
            } else {
                // incase the leds still had some light when the timer done
                //clearNotRiverSegments();
                clearAllSegments();
                triggerIdleStatic();
            }
            break;
        case IDLE_STATIC :
            break;
        default :
            Serial.println(F("Undefined state of mToggleable in ledModule!"));
            break;
    }
}
void LedModule::triggerIdleAnimate() {
    mToggleState = IDLE_ANIMATE;
    Serial.println(F("Idle Animate triggered"));
}
void LedModule::triggerIdleStatic() {
    mToggleState = IDLE_STATIC;
    Serial.println(F("Idle Static triggered"));
}
void LedModule::triggerFadeOut() {
    Serial.println(F("FadeOut triggered"));
    mFadeOutStartTime = millis();
    //mCurrentFadeOutDuration = mFadeOutDuration;
    mToggleState = FADEOUT;
}
void LedModule::triggerFadeIn() {
    Serial.println(F("FadeIn triggered"));
    mFadeInStartTime = millis();
    mToggleState = FADEIN;
}

uint8_t LedModule::lerpSingle(uint8_t startColor, uint8_t endColor, float deltaTime) {
    // lerp a single color channel. For example R for RGB.
    // deltaTime needs to be normalized value: 0 -1
    uint8_t currentColor = 0;
    if(deltaTime <= 1 && deltaTime >= 0) {
        currentColor = (uint8_t) round(lerp(deltaTime, 0.0, 1.0, startColor, endColor));
    } 
    return currentColor;
}
uint32_t LedModule::lerpColor(uint32_t colorStart, uint32_t colorEnd, float deltaTime) {
    // start colors and end colors
    uint8_t u8R = (uint8_t)((colorStart >> 16) & 0xff),
                    u8G = (uint8_t)((colorStart >> 8) & 0xff),
                    u8B = (uint8_t)(colorStart & 0xff);
    uint8_t u8RE = (uint8_t)((colorEnd >> 16) & 0xff),
                    u8GE = (uint8_t)((colorEnd >> 8) & 0xff),
                    u8BE = (uint8_t)(colorEnd & 0xff);
    uint8_t rChan = lerpSingle(u8R, u8RE, deltaTime);
    uint8_t gChan = lerpSingle(u8G, u8GE, deltaTime);
    uint8_t bChan = lerpSingle(u8B, u8BE, deltaTime);
    uint32_t newColor = Adafruit_NeoPixel_ZeroDMA::Color(rChan,gChan,bChan,0);
    return newColor;
}
float LedModule::lerp (float x, float x0, float x1, float y0, float y1) {
    // linear interpellation
    x = x > x1 ? x1 : x;
    x = x < x0 ? x0 : x;
    return y0 + (y1-y0) * ((x-x0)/(x1-x0));
}
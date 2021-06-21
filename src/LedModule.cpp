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
CRGB LedModule::mDamColor = CRGB(255,255,0);
CRGB LedModule::mCityColor = CRGB(160,0,200);
CRGB LedModule::mSnowSiteColor = CRGB(255,255,255);
CRGB LedModule::mWaterAreaColor = CRGB(255,20,100);
CRGB LedModule::mTractorColor = CRGB(255,200,200);
CRGB LedModule::mHalfRiverColor = CRGB(0,0,127);
CRGB LedModule::mBrightRiverColor = CRGB(40,40,255);

LedModule::LedModule(CRGB* leds, LedSegment* ledSegments, int numLedSegments) {
    pLedSegments = ledSegments;
    pLeds = leds;
    mNumLedSegments = numLedSegments;

    mTimer = 0;
    mAnimationStep = 0;
    mState = IDLE_STATIC;

    mFadeStartColor = CRGB::Black;
    mTargetColor = CRGB::Black;
    //mCurrentFadeOutDuration = 0;

    mFadeDamColor = CRGB::Black;
    mFadeSnowSiteColor = CRGB::Black;
    mFadeCityColor = CRGB::Black;
    mFadeTractorColor = CRGB::Black;
    mFadeWaterAreaColor = CRGB::Black;
    mFadeHalfRiverColor = CRGB::Black;
    mFadeBrightRiverColor = CRGB::Black;
}
void LedModule::begin() {
    // prob not needed
}
void LedModule::clearAllSegments() {
    for(int j = 0; j < mNumLedSegments; j ++) {
        int si = pLedSegments[j].mStartIndex;
        int nl = pLedSegments[j].mLength;
        for(int i = si; i < si + nl; i++) {
            pLeds[i] = CRGB::Black;
        }
        
    }
}
void LedModule::clearNotRiverSegments() {
    for(int j = 0; j < mNumLedSegments; j ++) {
        int si = pLedSegments[j].mStartIndex;
        int nl = pLedSegments[j].mLength;
        SEGMENT_TYPE type = pLedSegments[j].mType;
        //enum SEGMENT_TYPE { RIVER_ASC, RIVER_DES, DAM, SNOWSITE, CITY, WATERAREA, TRACTOR };
        if(type != RIVER_ASC || type != RIVER_DES )
        for(int i = si; i < si + nl; i++) {
            pLeds[i] = CRGB::Black;
        }
        
    }
}
void LedModule::fillRiverSegments(CRGB color) {
    for(int j = 0; j < mNumLedSegments; j ++) {
        int si = pLedSegments[j].mStartIndex;
        int nl = pLedSegments[j].mLength;
        SEGMENT_TYPE type = pLedSegments[j].mType;
        //enum SEGMENT_TYPE { RIVER_ASC, RIVER_DES, DAM, SNOWSITE, CITY, WATERAREA, TRACTOR };
        if(type == RIVER_ASC || type == RIVER_DES )
        for(int i = si; i < si + nl; i++) {
            pLeds[i] = color;
        }
        
    }
}
void LedModule::clearRiverSegments() {
    for(int j = 0; j < mNumLedSegments; j ++) {
        int si = pLedSegments[j].mStartIndex;
        int nl = pLedSegments[j].mLength;
        SEGMENT_TYPE type = pLedSegments[j].mType;
        //enum SEGMENT_TYPE { RIVER_ASC, RIVER_DES, DAM, SNOWSITE, CITY, WATERAREA, TRACTOR };
        if(type == RIVER_ASC || type == RIVER_DES )
        for(int i = si; i < si + nl; i++) {
            pLeds[i] = CRGB::Black;
        }
        
    }
}
void LedModule::drawFadeSegments() {
    //Draw FadeIn / FadeOutSegments
    
    // Serial.println(deltaTime);
    // Calculate all fade Colors For Dams, Cities, WaterAreas, Tractors, riversHalfway?
    if(mToggleState == FADEIN) {
        float deltaTime = ((float)(millis() - mFadeInStartTime)/(float)mFadeInDuration);
        fract8 dTime = round(deltaTime * 255);
        mFadeDamColor = blend(CRGB::Black, mDamColor, dTime);

        mFadeDamColor = blend(CRGB::Black, mDamColor, dTime);
        mFadeCityColor = blend(CRGB::Black, mCityColor, dTime);
        mFadeSnowSiteColor = blend(CRGB::Black, mSnowSiteColor, dTime);
        mFadeTractorColor = blend(CRGB::Black, mTractorColor, dTime);
        mFadeWaterAreaColor = blend(CRGB::Black, mWaterAreaColor, dTime);
        mFadeHalfRiverColor = blend(CRGB::Black, mHalfRiverColor, dTime);
        /*
        mFadeDamColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeDamColor);
        mFadeCityColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeCityColor);
        mFadeSnowSiteColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeSnowSiteColor);
        mFadeTractorColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeTractorColor);
        mFadeWaterAreaColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeWaterAreaColor);
        mFadeHalfRiverColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeHalfRiverColor);
        */
    } else if (mToggleState == FADEOUT) {
        float deltaTime = ((float)(millis() - mFadeOutStartTime)/(float)mFadeOutDuration);
        fract8 dTime = round(deltaTime * 255);

        mFadeDamColor = blend(mDamColor, CRGB::Black, dTime);
        mFadeCityColor = blend(mCityColor, CRGB::Black, dTime);
        mFadeSnowSiteColor = blend(mSnowSiteColor, CRGB::Black, dTime);
        mFadeTractorColor = blend(mTractorColor, CRGB::Black, dTime);
        mFadeWaterAreaColor = blend(mWaterAreaColor, CRGB::Black, dTime);
        mFadeHalfRiverColor = blend(mHalfRiverColor, CRGB::Black, dTime);

        // Needs more testing
        // Might cause a brightness jump when fading out
        /*
        mFadeDamColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeDamColor);
        mFadeCityColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeCityColor);
        mFadeSnowSiteColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeSnowSiteColor);
        mFadeTractorColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeTractorColor);
        mFadeWaterAreaColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeWaterAreaColor);
        mFadeHalfRiverColor = Adafruit_NeoPixel_ZeroDMA::gamma32(mFadeHalfRiverColor);
        */
    }

    for(int j = 0; j < mNumLedSegments; j ++) {
        int si = pLedSegments[j].mStartIndex;
        int nl = pLedSegments[j].mLength;

        SEGMENT_TYPE type = pLedSegments[j].mType;
        if(type == DAM) {
            for(int i = si; i < si + nl; i++) {
                pLeds[i] = mFadeDamColor;
            }
        } else if(type == CITY) { 
            for(int i = si; i < si + nl; i++) {
                pLeds[i] = mFadeCityColor;
            }
            
        } else if(type == SNOWSITE) { 
            for(int i = si; i < si + nl; i++) {
                pLeds[i] = mFadeSnowSiteColor;
            }
            
        } else if(type == TRACTOR) { 
            for(int i = si; i < si + nl; i++) {
                pLeds[i] = mFadeTractorColor;
            }
            
        } else if(type == WATERAREA) { 
            for(int i = si; i < si + nl; i++) {
                pLeds[i] = mFadeWaterAreaColor;
            }
            
        } else if(type == RIVER_ASC || type == RIVER_DES) { 
            for(int i = si; i < si + nl; i++) {
                pLeds[i] = mFadeHalfRiverColor;
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
                if(i%3 == mAnimationStep)  {
                    pLeds[i] = CRGB::Blue;
                    Serial.println("drawing");
                }
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
                    pLeds[i] = CRGB::Blue;
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
                Serial.println(mAnimationStep);
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
#include "LedModule.h"
#include "LedSegment.h"
#include <Adafruit_NeoPixel_ZeroDMA.h>
//#include <Arduino.h>

// Static member definitions  
uint32_t LedModule::mFadeColor1 = Adafruit_NeoPixel_ZeroDMA::Color(0,0,255);
uint32_t LedModule::mFadeColor2 = Adafruit_NeoPixel_ZeroDMA::Color(255,200,200);

LedModule::LedModule(Adafruit_NeoPixel_ZeroDMA* strip, LedSegment* ledSegments, int numLedSegments) {
    // remove
    mStartIndex = 0;
    mNumLeds = 0;
    //
    pLedSegments = ledSegments;
    mNumLedSegments = numLedSegments;

    mTimer = 0;
    mAnimationStep = 0;
    mState = IDLE;
    pStrip = strip;

    mFadeStartColor = Adafruit_NeoPixel_ZeroDMA::Color(0,0,0);
    mTargetColor = Adafruit_NeoPixel_ZeroDMA::Color(0,0,0);
    mCurrentFadeOutDuration = 0;
}
void LedModule::begin() {
    // prob not needed
}
void LedModule::clearSegments() {
    for(int j = 0; j < mNumLedSegments; j ++) {
        int si = pLedSegments[j].mStartIndex;
        int nl = pLedSegments[j].mLength;
        // Marque the strip leds. Ascending order
        for(int i = si; i < si + nl; i++) {
            pStrip->setPixelColor(i , Adafruit_NeoPixel_ZeroDMA::Color(0,0,0));
        }
        
    }
}
void LedModule::drawSegments() {

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

        
    }
    
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

void LedModule::fillSection(uint32_t color) {
    for(int i = mStartIndex; i < mStartIndex + mNumLeds; i ++ ) {
        pStrip->setPixelColor(i, color);
    }

}
void LedModule::update() {
    switch(mState) {
        case FADEIN :
            // calculate a fadeIn Brightness 
            if(millis() - mFadeInStartTime > mFadeInDuration) {
                //Serial.println(millis()-mFadeInStartTime);
                float deltaTime = ((float)(millis() - mFadeInStartTime)/(float)mFadeInDuration);
                //Serial.println(deltaTime);
                uint32_t currentFade = lerpColor(0, mTargetColor, deltaTime);
                currentFade = Adafruit_NeoPixel_ZeroDMA::gamma32(currentFade);
                fillSection(currentFade);

                //mStrip.fill(currentFade);
                //mStrip.show();
            } else {
                triggerIdle();
            }
            break;
        case IDLE :
            break;
        case FADEOUT :
            if((millis() - mFadeOutStartTime) > mCurrentFadeOutDuration) {
                // normalized to 0-1
                float deltaTime = ((float)(millis() - mFadeOutStartTime)/(float)mCurrentFadeOutDuration);
                uint32_t currentFade = lerpColor(mFadeStartColor, 0, deltaTime);
                //currentFade = mStrip.gamma32(currentFade); // causes brightness to drop
                fillSection(currentFade);
            } else {
                // incase the leds still had some light when the timer done
                uint32_t currentFade = Adafruit_NeoPixel_ZeroDMA::Color(0,0,0,0);
                fillSection(currentFade);
                triggerIdle();
            }
            break;
        case RIVER_ANIMATE :
            if((millis() - mTimer) > mTimeStep) {
                //advance animation pattern 
                mAnimationStep = (mAnimationStep+1) %3;
                mTimer = millis();
                Serial.println(mAnimationStep);
                clearSegments();
                //fillSection(Adafruit_NeoPixel_ZeroDMA::Color(0,0,0)); // set all to black 
                drawSegments();
                
            }
            break;
        default :
            Serial.println(F("Undefined state in ledModule!"));
            break;
    }
}
void LedModule::triggerIdle() {
    mState = IDLE;
    //Serial.println("Idle triggered");
}
void LedModule::triggerFadeOut2() {
    triggerFadeOut1();
}
void LedModule::triggerFadeOut1() {
    // check if fadeIn has not completed and if so progress the fadeOut to the right
    // amount so that it Fades out from where the fade in left off.
    mFadeStartColor = pStrip->getPixelColor(mStartIndex);
    //Serial.print("fadeStart: ");
    //Serial.println(mFadeStartColor);
    if(mState == FADEIN) {
        mCurrentFadeOutDuration = (millis() - mFadeInStartTime);
        //Serial.print("Current fade duration: ");
        //Serial.println(mCurrentFadeOutDuration);
    } else {
        mCurrentFadeOutDuration = mFadeOutDuration;
    }
    mFadeOutStartTime = millis();
    mState = FADEOUT;
}
void LedModule::triggerFadeIn2() {
    mTargetColor = mFadeColor2;
    mFadeInStartTime = millis();
    mState = FADEIN;
}
void LedModule::triggerFadeIn1() {
    // do things on enter fadein state
    // reset fadein details
    mTargetColor = mFadeColor1;
    mFadeInStartTime = millis();
    mState = FADEIN;
}
void LedModule::triggerRiverAnimate() {
    mState = RIVER_ANIMATE;
}

float LedModule::lerp (float x, float x0, float x1, float y0, float y1) {
    // linear interpellation
    x = x > x1 ? x1 : x;
    x = x < x0 ? x0 : x;
    return y0 + (y1-y0) * ((x-x0)/(x1-x0));
}
#include "LedModule.h"
#include "LedSegment.h"
// Static color definitions  
CRGB LedModule::mDamColor = CRGB(255,255,0);
CRGB LedModule::mCityColor = CRGB(255,60,0);
//CRGB LedModule::mCityColor = CRGB(160,0,200); // old color
CRGB LedModule::mSnowSiteColor = CRGB(255,255,255);
CRGB LedModule::mWaterAreaColor = CRGB(255,20,100);
//CRGB LedModule::mTractorColor = CRGB(255,200,200); // old color
CRGB LedModule::mTractorColor = CRGB(32,255,0);
CRGB LedModule::mHalfRiverColor = CRGB(0,0,127);
CRGB LedModule::mBrightRiverColor = CRGB(40,40,255);

LedModule::LedModule(CRGB* leds, LedSegment* ledSegments, int numLedSegments) {
    config(leds, ledSegments, numLedSegments);
    // this constructor is not used
}
LedModule::LedModule() {
    // when this constructore is used the config function must me called
    // at a later time. before you start using the class
    // LedModule is Made to be used in the LedMap class
}
void LedModule::config(CRGB* leds, LedSegment* ledSegments, int numLedSegments) {
    mAttractorActive = false;
    mAttractorFadeDir = FADEOUT; //0 - fadeIn, 1 = fadeOut


    pLedSegments = ledSegments;
    pLeds = leds;
    mNumLedSegments = numLedSegments;

    mTimer = 0;
    mAnimationStep = 0;
    //mState = IDLE_STATIC;

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
void LedModule::fadeRiverSegments() {
    // Fade out the river segments over time
    // Used to dim the previously lit leds
    // during the river animations
    // Fade all the leds a 64/256th brightness
    
    for(int j = 0; j < mNumLedSegments; j ++) {
        int si = pLedSegments[j].mStartIndex;
        int nl = pLedSegments[j].mLength;
        SEGMENT_TYPE type = pLedSegments[j].mType;
        //enum SEGMENT_TYPE { RIVER_ASC, RIVER_DES, DAM, SNOWSITE, CITY, WATERAREA, TRACTOR };
        if(type == RIVER_ASC || type == RIVER_DES )
            fadeToBlackBy(pLeds + si, nl, 64);
    }
}
void LedModule::drawFadeSegments() {
    //Draw FadeIn / FadeOutSegments
    fract8 dTime = 0;
    
    // Serial.println(deltaTime);
    // Calculate all fade Colors For Dams, Cities, WaterAreas, Tractors, riversHalfway?
    if(mToggleState == FADEIN) {
        float deltaTime = ((float)(millis() - mFadeInStartTime)/(float)mFadeInDuration);
        dTime = round(deltaTime * 255);
        mFadeDamColor = blend(CRGB::Black, mDamColor, dTime);

        mFadeDamColor = blend(CRGB::Black, mDamColor, dTime);
        mFadeCityColor = blend(CRGB::Black, mCityColor, dTime);
        mFadeSnowSiteColor = blend(CRGB::Black, mSnowSiteColor, dTime);
        mFadeTractorColor = blend(CRGB::Black, mTractorColor, dTime);
        mFadeWaterAreaColor = blend(CRGB::Black, mWaterAreaColor, dTime);
        mFadeHalfRiverColor = blend(CRGB::Black, mHalfRiverColor, dTime);

    } else if (mToggleState == FADEOUT) {
        float deltaTime = ((float)(millis() - mFadeOutStartTime)/(float)mFadeOutDuration);
        dTime = round(deltaTime * 255);

        mFadeDamColor = blend(mDamColor, CRGB::Black, dTime);
        mFadeCityColor = blend(mCityColor, CRGB::Black, dTime);
        mFadeSnowSiteColor = blend(mSnowSiteColor, CRGB::Black, dTime);
        mFadeTractorColor = blend(mTractorColor, CRGB::Black, dTime);
        mFadeWaterAreaColor = blend(mWaterAreaColor, CRGB::Black, dTime);
        mFadeHalfRiverColor = blend(mHalfRiverColor, CRGB::Black, dTime);
       
    }

    for(int j = 0; j < mNumLedSegments; j ++) {
        int si = pLedSegments[j].mStartIndex;
        int nl = pLedSegments[j].mLength;

        SEGMENT_TYPE type = pLedSegments[j].mType;
        if(type == DAM) {
            for(int i = si; i < si + nl; i++) {
                // pLeds[i] = mFadeDamColor;
                pLeds[i] = blend(pLeds[i], mFadeDamColor, dTime);
            }
        } else if(type == CITY) { 
            for(int i = si; i < si + nl; i++) {
                //pLeds[i] = mFadeCityColor;
                pLeds[i] = blend(pLeds[i], mFadeCityColor, dTime);
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
                //pLeds[i] = mFadeHalfRiverColor;
                pLeds[i] = blend(pLeds[i], mFadeHalfRiverColor,dTime);
            }
            
        }

        
    } // end for loop segments
    
}
void LedModule::drawAnimatedAttractor() {
    // if river types
    // if fade direction
    // slight pulse in brightness

    CRGB bottomColor = CRGB(10,10,32);
    CRGB riverAttractorColor = CRGB::Black;

    if(mAttractorFadeDir == FADEIN) {
        float deltaTime = ((float)(millis() - mFadeInStartTime)/(float)mFadeInDuration);
        fract8 dTime = round(deltaTime * 255);
        //Serial.println(F("Fading in Attractor"));
        riverAttractorColor = blend(bottomColor, mHalfRiverColor, dTime);
    } else if (mAttractorFadeDir == FADEOUT) {
        //Serial.println(F("Fading out Attractor"));
        float deltaTime = ((float)(millis() - mFadeOutStartTime)/(float)mFadeOutDuration);
        fract8 dTime = round(deltaTime * 255);
        riverAttractorColor = blend(mHalfRiverColor, bottomColor, dTime);
    }

    for(int j = 0; j < mNumLedSegments; j ++) {
        int si = pLedSegments[j].mStartIndex;
        int nl = pLedSegments[j].mLength;
        int type = pLedSegments[j].mType;

        if(type == RIVER_ASC || type == RIVER_DES) { 
            for(int i = si; i < si + nl; i++) {
                pLeds[i] = riverAttractorColor;
            }
        }
    }
    // if snow sites
    // sparkle 
}

void LedModule::drawAnimatedSegments() {
    // reset river segment animIndexs

    for(int j = 0; j < mNumLedSegments; j ++) {
        int si = pLedSegments[j].mStartIndex;
        int nl = pLedSegments[j].mLength;
        int ai = pLedSegments[j].animationIndex;

        SEGMENT_TYPE dir = pLedSegments[j].mType;
        if(dir == RIVER_ASC) {
            pLeds[si + ai] = CRGB::Blue;
            ai = (ai+1) % nl;
            pLedSegments[j].animationIndex = ai;
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
        case FADEIN_WAIT :
            if(millis() - mFadeInWaitTime > mFadeOutDuration) {
                triggerFadeIn2();
            }
            break;
        case FADEIN :
            if(millis() - mFadeInStartTime < mFadeInDuration) {
                drawFadeSegments();
            } else {
                if(mAttractorActive == false) {
                    triggerIdleAnimate();
                } else {
                    triggerAttractorAnimate();
                }
            }
            break;
        case IDLE_ANIMATE :
            if((millis() - mTimer) > mTimeStep) {
                //advance animation pattern 
                mAnimationStep = (mAnimationStep+1) %3;
                mTimer = millis();
                //Serial.println(mAnimationStep);
                fadeRiverSegments();
                //clearRiverSegments();
                /////////////fillRiverSegments(mHalfRiverColor);
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
        case IDLE_ANIMATE_ATTRACTOR :
            // if((millis() - mTimer) > mTimeStep) {
            //     mTimer = millis();
            // }
            if(mAttractorFadeDir == FADEOUT) {
                if((millis() - mFadeOutStartTime) >mFadeOutDuration) {
                    mAttractorFadeDir = FADEIN;
                    mFadeInStartTime = millis();
                    Serial.println(F("Switching to FADEIN attractor"));
                } 
            } else if(mAttractorFadeDir == FADEIN) {
                if((millis() - mFadeInStartTime) >mFadeInDuration) {
                    mAttractorFadeDir = FADEOUT;
                    mFadeOutStartTime = millis();
                    Serial.println(F("Switching to FADEOUT attractor"));
                } 
            }
            drawAnimatedAttractor();

            break;
        case IDLE_STATIC :
            break;
        default :
            Serial.println(F("Undefined state of mToggleState in ledModule!"));
            break;
    }
    
}
void LedModule::triggerIdleAnimate() {
    mAttractorActive = false;
    mToggleState = IDLE_ANIMATE;
    Serial.println(F("Idle Animate triggered"));
}
void LedModule::triggerIdleStatic() {
    mAttractorActive = false;
    mToggleState = IDLE_STATIC;
    Serial.println(F("Idle Static triggered"));
}
void LedModule::triggerFadeOut() {
    mAttractorActive = false;
    Serial.println(F("FadeOut triggered"));
    mFadeOutStartTime = millis();
    //mCurrentFadeOutDuration = mFadeOutDuration;
    mToggleState = FADEOUT;
}
void LedModule::triggerFadeIn2() {
    Serial.println(F("FadeIn triggered"));
    mFadeInStartTime = millis();
    mToggleState = FADEIN;
}
void LedModule::triggerFadeIn() {
    mAttractorActive = false;
    Serial.println(F("FadeInWait triggered"));
    mFadeInWaitTime = millis();
    mToggleState = FADEIN_WAIT;
}
void LedModule::triggerFadeInAttractor() {
    mAttractorActive = true;
    Serial.println(F("FadeInAttractor triggered"));
    mFadeInWaitTime = millis();
    mToggleState = FADEIN_WAIT;
}

void LedModule::triggerAttractorAnimate() {
    Serial.println(F("AttractorAnimate triggered"));
    mFadeOutStartTime = millis();
    mToggleState = IDLE_ANIMATE_ATTRACTOR;
    mAttractorFadeDir = FADEOUT;
}

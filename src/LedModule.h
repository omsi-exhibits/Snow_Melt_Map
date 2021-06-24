#ifndef LEDMODULE_H
#define LEDMODULE_H
#include <Arduino.h>
#include <FastLED.h>
#include "LedSegment.h"

enum LEDSTATE { IDLE_STATIC, FADEIN, FADEOUT, IDLE_ANIMATE };

class LedModule {
    public:
        LedModule(CRGB leds[], LedSegment ledSegments[], int numLeds);
        void begin(); // not used
        void update();
        void triggerIdleStatic();
        void triggerIdleAnimate(); // animates river
        void triggerFadeIn();
        void triggerFadeOut();

        void drawSegments(); // un needed?
        void drawFadeSegments();
        void drawAnimatedSegments();

        void clearAllSegments();
        void clearRiverSegments();
        void clearNotRiverSegments();
        void clearToggleableSegments();

        void fillRiverSegments(CRGB color);

        void fillSection(CRGB color);

    private:
        //Adafruit_NeoPixel_ZeroDMA* pStrip;
        CRGB* pLeds;
        LedSegment* pLedSegments;
        int mNumLedSegments;
        LEDSTATE mState;
        LEDSTATE mToggleState;
        LEDSTATE mRiverState;

        unsigned long mTimer; // Used in river and needs name update
        static const unsigned int mTimeStep = 333;
        int mAnimationStep;
        // Fade Related
        unsigned long mFadeInStartTime;
        unsigned long mFadeOutStartTime;
        static const int mFadeInDuration = 2000;
        static const int mFadeOutDuration = 2000;
        //unsigned int mCurrentFadeOutDuration;
        CRGB mFadeStartColor;
        CRGB mTargetColor;

        CRGB mFadeDamColor;
        CRGB mFadeSnowSiteColor;
        CRGB mFadeCityColor;
        CRGB mFadeTractorColor;
        CRGB mFadeWaterAreaColor;
        CRGB mFadeHalfRiverColor;
        CRGB mFadeBrightRiverColor;

        // The colors of segments when they are fully faded in
        static CRGB mDamColor;
        static CRGB mSnowSiteColor;
        static CRGB mCityColor;
        static CRGB mTractorColor;
        static CRGB mWaterAreaColor;
        static CRGB mHalfRiverColor;
        static CRGB mBrightRiverColor;

};

#endif

#ifndef LEDMODULE_H
#define LEDMODULE_H
#include <Arduino.h>
#include <Adafruit_Neopixel_ZeroDMA.h>
#include "LedSegment.h"

enum LEDSTATE { IDLE_STATIC, FADEIN, FADEOUT, IDLE_ANIMATE };

class LedModule {
    public:
        LedModule(Adafruit_NeoPixel_ZeroDMA* strip, LedSegment ledSegments[], int numLeds);
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

        void fillSection(uint32_t color);
        uint32_t lerpColor(uint32_t colorStart, uint32_t colorEnd, float deltaTime);
        uint8_t lerpSingle(uint8_t startColor, uint8_t endColor, float deltaTime);
        float lerp(float x, float x0, float x1, float y0, float y1);

    private:
        Adafruit_NeoPixel_ZeroDMA* pStrip;
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
        unsigned int mCurrentFadeOutDuration;
        uint32_t mFadeStartColor;
        uint32_t mTargetColor;

        uint32_t mFadeDamColor;
        uint32_t mFadeSnowSiteColor;
        uint32_t mFadeCityColor;
        uint32_t mFadeTractorColor;
        uint32_t mFadeWaterAreaColor;
        uint32_t mFadeHalfRiverColor;
        uint32_t mFadeBrightRiverColor;

        // The colors of segments when they are fully faded in
        static uint32_t mDamColor;
        static uint32_t mSnowSiteColor;
        static uint32_t mCityColor;
        static uint32_t mTractorColor;
        static uint32_t mWaterAreaColor;
        static uint32_t mHalfRiverColor;
        static uint32_t mBrightRiverColor;

};

#endif

#ifndef LEDMODULE_H
#define LEDMODULE_H
#include <Arduino.h>
#include <Adafruit_Neopixel_ZeroDMA.h>
#include "LedSegment.h"

enum LEDSTATE { IDLE, FADEIN, FADEOUT, RIVER_ANIMATE };

class LedModule {
    public:
        LedModule(Adafruit_NeoPixel_ZeroDMA* strip, LedSegment ledSegments[], int numLeds);
        void begin(); // not used
        void update();
        void triggerIdle();
        void triggerFadeIn1();
        void triggerFadeIn2();
        void triggerFadeOut1();
        void triggerFadeOut2();
        void triggerRiverAnimate();

        void drawSegments();
        void clearSegments();

        void fillSection(uint32_t color);
        uint32_t lerpColor(uint32_t colorStart, uint32_t colorEnd, float deltaTime);
        uint8_t lerpSingle(uint8_t startColor, uint8_t endColor, float deltaTime);
        float lerp(float x, float x0, float x1, float y0, float y1);

    private:
        Adafruit_NeoPixel_ZeroDMA* pStrip;
        LedSegment* pLedSegments;
        int mNumLedSegments;
        LEDSTATE mState;
        int mStartIndex;
        uint8_t mNumLeds;
        unsigned long mTimer;
        static const int mTimeStep = 333;
        int mAnimationStep;
        // Fade Related
        unsigned long mFadeInStartTime;
        unsigned long mFadeOutStartTime;
        static const int mFadeInDuration = 400;
        static const int mFadeOutDuration = 400;
        unsigned int mCurrentFadeOutDuration;
        uint32_t mFadeStartColor;
        uint32_t mTargetColor;
        static uint32_t mFadeColor1;
        static uint32_t mFadeColor2;

};

#endif

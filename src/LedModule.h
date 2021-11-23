#ifndef LEDMODULE_H
#define LEDMODULE_H
#include <Arduino.h>
#include <FastLED.h>
#include "LedSegment.h"

enum LEDSTATE { IDLE_STATIC, FADEIN, FADEOUT, IDLE_ANIMATE, IDLE_ANIMATE_ATTRACTOR };

class LedModule {
    public:
        LedModule();
        LedModule(CRGB leds[], LedSegment ledSegments[], int numLeds);
        void config(CRGB leds[], LedSegment ledSegments[], int numLeds);
        void begin(); // not used
        void update();
        void triggerIdleStatic();
        void triggerIdleAnimate(); // animates river
        void triggerFadeInAttractor();
        void triggerFadeIn();
        void triggerFadeOut();
        void triggerAttractorAnimate();

        void drawSegments(); // un needed?
        void drawFadeSegments();
        void drawAnimatedSegments();
        void drawAnimatedSegments2(); // Animate riversegments
        void drawAnimatedAttractor();

        void clearAllSegments();
        void clearRiverSegments();
        void clearNotRiverSegments();
        void clearToggleableSegments();
        void fadeRiverSegments();

        void fillRiverSegments(CRGB color);

        void fillSection(CRGB color);

    private:
        CRGB* pLeds;
        LedSegment* pLedSegments;
        int mNumLedSegments;
        //LEDSTATE mState;
        //LEDSTATE mRiverState;
        LEDSTATE mToggleState;
        bool mAttractorActive;
        bool mAttractorFadeDirection;

        unsigned long mTimer; // Used in river 
        static const unsigned int mTimeStep = 66;
        int mAnimationStep;
        // Fade Related
        unsigned long mFadeInStartTime;
        unsigned long mFadeOutStartTime;
        static const int mFadeInDuration = 2200;
        static const int mFadeOutDuration = 1800;
        // Attractor Related
        unsigned long mAttractorFadeTimer;
        static const int mAttractorFadeDuration = 4000;
        int mAttractorFadeDir; 

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

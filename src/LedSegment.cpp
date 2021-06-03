#include "LedSegment.h"
#include <Arduino.h>

LedSegment::LedSegment(int startIndex, int length, LedSegment *nextSegment) {
    mStartIndex = startIndex;
    mLength = length;
    mNextSegment = nextSegment;
    mIndex = 0;
}
void LedSegment::update() {
    if(millis() - mTimer >= mTimeStep) {
        mTimer = millis();
        if(mIndex >= mLength) {
            // drop is at the end. start a drop on the next segment
            // loop drop to the begining index
            mIndex = 0;
        }
    }

}


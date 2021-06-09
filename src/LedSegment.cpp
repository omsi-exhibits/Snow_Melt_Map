#include "LedSegment.h"
#include <Arduino.h>

LedSegment::LedSegment() {
    mStartIndex = 0;
    mLength = 0;
    pNextSegment = NULL;
    mConnectingIndex = 0;
    mType = RIVER_ASC;
}
void LedSegment::config(int startIndex, int length, LedSegment *nextSegment, int connectingIndex, SEGMENT_TYPE type) {
    mType = type;
    mStartIndex = startIndex;
    mLength = length;
    pNextSegment = nextSegment;
    mConnectingIndex = connectingIndex;
}
void LedSegment::update() {

}


#ifndef LED_SEGMENT
#define LED_SEGMENT
enum SEGMENT_TYPE { RIVER_ASC, RIVER_DES, DAM, SNOWSITE, CITY, WATERAREA, TRACTOR };
class LedSegment {
    public:
        LedSegment();
        void config(int startIndex, int length, LedSegment* nextSegment, int connectingIndex, SEGMENT_TYPE type);
        void update();
        SEGMENT_TYPE mType;
        int mStartIndex;
        int mLength;
        LedSegment *pNextSegment;
        int mConnectingIndex;

    private:
};

#endif
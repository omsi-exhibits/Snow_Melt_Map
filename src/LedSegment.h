#ifndef LED_SEGMENT
#define LED_SEGMENT
class LedSegment {
    public:
        LedSegment(int startIndex, int length, LedSegment* nextSegment);
        void update();

    private:
        int mStartIndex;
        int mLength;
        LedSegment *mNextSegment;
        int mIndex;
        //int mDrops[]; 
        const int mTimeStep = 500;
        unsigned long mTimer;
};

#endif
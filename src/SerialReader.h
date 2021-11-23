#ifndef SERIAL_READER_H
#define SERIAL_READER_H
#include <Arduino.h>
/* * * * * * Serial Reader  * * * * *
Button presses are stored in an array. Keeping track of button down pressed
and up released. The input object keeps track if a button state changed. At anytime
you can just ask for the state of the button and it will return 
// Returns a button state
input.getButton(1);

0-not_pressed 1-just_pressed 2-held_down 3-released 
input class updates buttonStates[] 
* * * * * * * * * * * * * * * * * */
// buttons stored in an array[1-8], [0] not used
#define MAX_BUTTONS 9
enum BSTATE { BIDLE, BDOWN, BHELD, BUP };

class SerialReader {
    public:
        SerialReader();
        void update();
        void begin();
        int getAButton();

    private:
        int mButtonStates[MAX_BUTTONS];
        int mButtonLastStates[MAX_BUTTONS];
        int mNumButtons;

        const int mTimeStep = 10;
        const int mDebounceInterval = 25; // milliseconds
        unsigned long mTimer;

};

#endif
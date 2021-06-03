#ifndef INPUT_H
#define INPUT_H
/* * * * * * Input System * * * * *
uses bounce2 library. Button presses are stored in an array. Keeping track of button down pressed
and up released. The input object keeps track if a button state changed. At anytime
you can just ask for the state of the button and it will return 
// Returns a button state
input.getButton(1);

0-not_pressed 1-just_pressed 2-held_down 3-released 
input class updates buttonStates[] 
* * * * * * * * * * * * * * * * * */
#include <Arduino.h>
#include <Bounce2.h>

#define MAX_BUTTONS 10
// Buttons are connected to an internal pullup INPUT_PULLUP.
enum BSTATE { BIDLE, BDOWN, BHELD, BUP };

class Input {
    public:
        // ideally you could pass an array of pins and number of pins
        // That would need memory allocation ... or we can hard code max lengths
        Input(const int buttonPins[], int numButtons);
        int hasChanged();
        int getButton(int buttonNum);
        bool isDown(int buttonNum);
        void update();
        void begin();
    private:
        Bounce mButtons[MAX_BUTTONS];
        int mNumButtons;
        int mButtonStates[MAX_BUTTONS];
        int mButtonLastStates[MAX_BUTTONS];
        int mButtonPins[MAX_BUTTONS];
        const int mTimeStep = 10;
        const int mDebounceInterval = 25; // milliseconds
        unsigned long mTimer;
};
#endif
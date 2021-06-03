#include "Input.h"
#define DEBUG

Input::Input(const int buttonPins[], int numButtons) {
    if(numButtons <= MAX_BUTTONS && numButtons >0) {
        for(int i = 0; i < numButtons; i++) {
            mButtonStates[i] = 0;
            mButtonPins[i] = buttonPins[i];
            mButtons[i] = Bounce();
        }
        mNumButtons = numButtons;
    } else {
        #ifdef DEBUG
        Serial.print(F("Error: Number of buttons is out of range: "));
        Serial.println(mNumButtons);
        Serial.print(F("inputs disabled"));
        #endif
        mNumButtons = 0;
    }
}
void Input::begin() {
    //Setup pinMode
    for(int i = 0; i < mNumButtons; i ++) {
        if(i < mNumButtons) {
            pinMode(mButtonPins[i], INPUT_PULLUP);
            mButtons[i].attach(mButtonPins[i]);
            mButtons[i].interval(mDebounceInterval);
        }
    }
} // end begin

void Input::update() {
    if(millis() - mTimer >= mTimeStep) {
        // update button states
        for(int i = 0; i < mNumButtons; i++) {
            mButtonLastStates[i] = mButtonStates[i];
            mButtons[i].update();
            if(mButtons[i].fell()) {
                mButtonStates[i] = BDOWN;
                Serial.print("Index: ");
                Serial.print(i);
                Serial.print(" ButtonPIN: ");
                Serial.print(mButtonPins[i]);
                Serial.println(" - DOWN Triggered");
            } else if (mButtons[i].rose()) {
                mButtonStates[i] = BUP;
                Serial.print("Index: ");
                Serial.print(i);
                Serial.print(" ButtonPIN: ");
                Serial.print(mButtonPins[i]);
                Serial.println(" - UP Triggered");
            } else if(mButtonLastStates[i] == BDOWN) {
                mButtonStates[i] = BHELD;
            } else if(mButtonLastStates[i] == BUP) {
                mButtonStates[i] = BIDLE;
            }
        }
        mTimer = millis();
    }
} // end update

bool Input::isDown(int buttonNum) {
    // if buttonNum is out of range it will 
    bool state = false;
    if(buttonNum >= 0 && buttonNum < MAX_BUTTONS) {
        if(mButtonStates[buttonNum] == BDOWN) {
            state = true;
        }
    } else {
        #ifdef DEBUG
        Serial.print(F("isDown buttonNum is out of range"));
        #endif
    }
    return state;
}
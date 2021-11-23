#include "SerialReader.h"
#define DEBUG

SerialReader::SerialReader() {
    for(int i =0; i < mNumButtons; i ++) {
        mButtonStates[i] = 0;
    }
    mNumButtons = MAX_BUTTONS;
}

void SerialReader::begin() {
    Serial1.begin(9600);
}
void SerialReader::update() {
    int inByte = -1;
    // Just keep track of button down and idle states
    for(int i = 0; i < mNumButtons; i ++) {
        mButtonLastStates[i] = mButtonStates[i];
        mButtonStates[i] = BIDLE;
    }
    while(Serial1.available() >0) {
        inByte = Serial1.read();
        Serial.print("Byte Received: ");
        Serial.println(inByte);
        if(inByte< mNumButtons && inByte >=0) {
            mButtonStates[inByte] = BDOWN;
        } else {
            Serial.println("Invalid inByte received");
        }
    }
}

int SerialReader::getAButton() {
    int result = -1;
    // if more than one button has been received
    // this will return the last button that shows up
    // or -1 if no button has been received.
    for(int i =0; i < mNumButtons; i ++) {
        if(mButtonStates[i] == BDOWN) 
            result = i;
    }
    return result;
}
#ifndef HW_TEENSY_H
#define HW_TEENSY_H

#define HEARTLED 13

// Teensy LEDPINS
#define LEDPIN1 2
#define LEDPIN2 14
// https://www.pjrc.com/teensy/td_libs_OctoWS2811.html
// LED STRIP # 1- 8
// 2,14, 7, 8, 6, 20, 21
#define NUMPIXELS0 50
#define NUMPIXELS1 300

//Configured for teensy 4.0
#define NUM_BUTTONS 8
const int buttonPins[NUM_BUTTONS] = {0,1,16,17,18,19,22,23};//,10,11};
const int buttonLightPins[NUM_BUTTONS] = {3, 4, 5, 9, 10, 11, 12, 15};

// The itsy bitsy has 22 usable pins. With 8 for buttons and 8 for button lights and 3 for light strips and 1 for Tx for audio feed back.

#endif
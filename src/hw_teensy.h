#ifndef HW_TEENSY_H
#define HW_TEENSY_H

#define HEARTLED 13

// Teensy LEDPINS
#define LEDPIN0 2
#define LEDPIN1 14
// https://www.pjrc.com/teensy/td_libs_OctoWS2811.html
// LED STRIP # 1- 8
// 2,14, 7, 8, 6, 20, 21
#define NUMPIXELS0 200
#define NUMPIXELS1 350

//Configured for teensy 4.0
#define NUM_BUTTONS 7
// unused pins broken out on the OctoWS2811 adapter
// 0, 1, 23, 22, 19, 18, 17
const int buttonPins[NUM_BUTTONS] = {0,1,23,22,19,18,17};
//const int buttonLightPins[NUM_BUTTONS] = {3, 4, 5, 9, 10, 11, 12, 15};

#endif
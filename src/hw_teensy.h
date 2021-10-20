#ifndef HW_TEENSY_H
#define HW_TEENSY_H

#define HEARTLED 13

// Teensy LEDPINS

// parallel out requires specific pins. see Parallel output on the Teensy 4 
// https://github.com/FastLED/FastLED/wiki/Parallel-Output
/* The new Teensy 4 also supports parallel output, but it's done slightly differently from the above platforms. First off, there are three sets of possible pins that can be used - each of the three set of pins, in order:

First: 1,0,24,25,19,18,14,15,17,16,22,23,20,21,26,27
Second: 10,12,11,13,6,9,32,8,7
Third: 37, 36, 35, 34, 39, 38, 28, 31, 30

Note that any pin above 21 is a pad on the back of the board. This is the ordering of pins for each grouping. Now, when calling add LEDs, you can pick which pin you want to start with in each group, and how many lanes. For example, if you want 16 way output, you would use Pin 1 (and the rest of the pins in that first group) (with 4 of the strips having to connect to the backside of the panel). If you only want a few channels of output, say 6 - and you don't want to use pads on the back, then you can select pin 19 as your initial pin (from that first group), and set the number of channels to 6 which will use pins 19,18,14,15,17,16.
* * * * * * * In our case pin 8 gets us output on pin 8 and pin 7 * * * * * * * */

#define LEDPIN_PARALLEL 8
//#define LEDPIN0 2
//#define LEDPIN1 14
// https://www.pjrc.com/teensy/td_libs_OctoWS2811.html
// OctoWS2811 adapter LED pins. LED STRIP # 1- 8
// 2, 14, 7, 8, 6, 20, 21

// Teensy Multi out attempt
#define NUM_PIXELS_PER_STRIP 450
#define NUM_STRIPS 2

// Note used
#define NUMPIXELS0 300
#define NUMPIXELS1 450

//Configured for teensy 4.0
#define NUM_BUTTONS 7
// unused pins broken out on the OctoWS2811 adapter
// 0, 1, 23, 22, 19, 18, 17
const int buttonPins[NUM_BUTTONS] = {0,1,23,22,19,18,17};
//const int buttonLightPins[NUM_BUTTONS] = {3, 4, 5, 9, 10, 11, 12, 15};

#endif
#ifndef HW_H
#define HW_H

#define HEARTLED 13

// Available pins for Neopixel DMA: 5,12,MOSI (ItsyBitsy M0)
#define LEDPIN1 5
#define LEDPIN2 12
#define NUMPIXELS0 200
#define NUMPIXELS1 350

#define NUM_BUTTONS 8
const int buttonPins[NUM_BUTTONS] = {A2,A3,A4,2,3,4,7,9};//,10,11};
const int buttonLightPins[NUM_BUTTONS] = {A0, A1, A5, MOSI, MISO, 1, SDA, SCL};

// The itsy bitsy has 22 usable pins. With 8 for buttons and 8 for button lights and 3 for light strips and 1 for Tx for audio feed back.

#endif
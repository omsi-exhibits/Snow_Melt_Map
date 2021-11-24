/* Snow Melt Map - Proof of Concept 
 * 
 */

#include <FastLED.h>
#include "HeartBeat.h"
//#include "hw.h"
#include "hw_teensy.h"
#include "LedModule.h"
#include "LedSegment.h"
#include "LedMap.h"
#include "SerialReader.h"

HeartBeat heartBeat = HeartBeat(13); // pin
LedMap ledMap = LedMap();

// Input object
SerialReader serialInput = SerialReader();


unsigned long attractorTimer = 0;
unsigned long attractorTimeOut = 10000; // 10 seconds
enum STATE { ATTRACTOR, LISTENING, IDLE };
int mainState = LISTENING; // 0 - attractor, 1 - listening to buttons

bool riverToggle = true;
unsigned long riverTimer = 0;
unsigned long riverTimeStep = 2200;

/********************** function definitions *************************/

/************************* SETUP ***********************/
void setup() {
  //heartbeat led
  //Serial.begin(9600);
  pinMode(13,OUTPUT);
  serialInput.begin();
  ledMap.receiveInput(8);
}
void loop() {
  heartBeat.update();

  // Get input from SerialReader 
  serialInput.update();
  int buttonIn = serialInput.getAButton();
  //Serial.print("button rec: ");
  //Serial.println(buttonIn);


  // *********** Main State *************
  if(mainState == ATTRACTOR) {
    if(buttonIn != -1) {
        ledMap.receiveInput(buttonIn);
        attractorTimer = millis();
        mainState = LISTENING;
        Serial.println(F("Entering Listening Mode"));
    } 
  } else if (mainState == LISTENING) {
    if(buttonIn != -1) {
      ledMap.receiveInput(buttonIn);
      Serial.print(F("Trigger ledmap.receiveInput(): "));
      Serial.println(buttonIn);
      attractorTimer = millis();
    } else {
      // else check if enough time has passed to enter attractor mode
      if(millis() - attractorTimer > attractorTimeOut) {
        mainState = ATTRACTOR;
        //enter attractor mode in led map. 
        ledMap.receiveInput(9);
        Serial.println(F("Entering Attractor Mode"));
      }
    }
  }

  // ******************************** update and draw map ***************************
    ledMap.update();
    ledMap.drawLeds();
}


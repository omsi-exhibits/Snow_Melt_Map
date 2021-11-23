// 8-Button IO Board, based on Vroom by Daniel Smolentsev
// Customized for Snow_Melt_Map By Justin Patrizi 11/18/21
// Updated 11/23/21 - Added Serial1 out 

// * * * * Author * * * * //
// Daniel Smolentsev
// OMSI . 1/12/20

// * * * * Arduino * * * * * * //
// Arduino Version 1.8.9
// Teensy 3.2

// * * * * Libraries Used * * * * * * //
// https://github.com/thomasfredericks/Bounce2
// Arduino Keyboard.h

/*
   This progran listens to button inputs and then outputs a on Serial1 . 1-8 buttons press a byte with the value of 1-8
   In attractor mode the buttons pulse in unison. Once a button is pressed it will Disable input and dim the led lights for
   the duration of that video. Each button has a video length asociated with it to disable the button led and presses.
*/

#define DEBUG 1

#include <Bounce2.h>
//#include <Keyboard.h>

#define BUTTON_1 A5
#define BUTTON_2 A4
#define BUTTON_3 A3
#define BUTTON_4 A2
#define BUTTON_5 A1
#define BUTTON_6 A0
#define BUTTON_7 12
#define BUTTON_8 11

#define BUTTON_1_LED A9
#define BUTTON_2_LED A8
#define BUTTON_3_LED A7
#define BUTTON_4_LED A6
#define BUTTON_5_LED 6
#define BUTTON_6_LED 5
#define BUTTON_7_LED 4
#define BUTTON_8_LED 3

Bounce button1 = Bounce();
Bounce button2 = Bounce();
Bounce button3 = Bounce();
Bounce button4 = Bounce();
Bounce button5 = Bounce();
Bounce button6 = Bounce();
Bounce button7 = Bounce();
Bounce button8 = Bounce();

//////////////////////////////////////////// Button panel /////////////////////////////////////////////////
//
// 1 - Colorado River and Main Tributaries
// 3 - Snow Monitoring Sites
// 4 - Dams
// 5 - Farms
// 6 - Grand Junction City
// 7 - Long-Distance Water Users
// 8 - Los Angeles Water Supply
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int state = 0;
// state 0 - attractor (buttons pulse), state - 1 button pressed, state - 2 wait for video length time

unsigned long videoDelayTimer = 0;
unsigned long pulseDelayTimer = 0;
const unsigned int pulseStepDelay = 20;

unsigned int skewerDelay = 100;
unsigned int skewerSPDelay = 100; //Patrones en la comida
unsigned int beatsDelay = 100;
unsigned int beatsSPDelay = 100; //Ritmos Intermitentes
unsigned int shoesDelay = 100;
unsigned int shoesSPDelay = 100; // Eparajar los Zapatos
unsigned long currentDelay = 0;


unsigned long heartBeatTimer = 0;
boolean heartBeat = false;


int ramp = 0;
const int rampMax = 125;
const int rampMin = 16;
int dimming = 1; // 1 incrase, -1 decrease
const int pressedBrightness = 175;


//* * * * * setup * * * * *//
void setup ()
{
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
  pinMode(BUTTON_5, INPUT_PULLUP);
  pinMode(BUTTON_6, INPUT_PULLUP);
  pinMode(BUTTON_7, INPUT_PULLUP);
  pinMode(BUTTON_8, INPUT_PULLUP);

  pinMode(BUTTON_1_LED, OUTPUT);
  pinMode(BUTTON_2_LED, OUTPUT);
  pinMode(BUTTON_3_LED, OUTPUT);
  pinMode(BUTTON_4_LED, OUTPUT);
  pinMode(BUTTON_5_LED, OUTPUT);
  pinMode(BUTTON_6_LED, OUTPUT);
  pinMode(BUTTON_7_LED, OUTPUT);
  pinMode(BUTTON_8_LED, OUTPUT);


  button1.attach(BUTTON_1);
  button1.interval(50);

  button2.attach(BUTTON_2);
  button2.interval(50);

  button3.attach(BUTTON_3);
  button3.interval(50);

  button4.attach(BUTTON_4);
  button4.interval(50);

  button5.attach(BUTTON_5);
  button5.interval(50);

  button6.attach(BUTTON_6);
  button6.interval(50);

  button7.attach(BUTTON_7);
  button7.interval(50);

  button8.attach(BUTTON_8);
  button8.interval(50);

//Keyboard.begin();

// Serial Out setup to the led controller board.
Serial1.begin(9600);

}  // end of setup

void pulseButtonLeds() {
  if (millis() - pulseDelayTimer >= pulseStepDelay) {
    //pulse button led
    if (ramp >= rampMax) {
      // flip the direction of the dimming
      dimming = -1;
    } else if (ramp <= rampMin ) {
      dimming = 1;
    }
    ramp += dimming;

    analogWrite(BUTTON_1_LED, ramp);
    analogWrite(BUTTON_2_LED, ramp);
    analogWrite(BUTTON_3_LED, ramp);
    analogWrite(BUTTON_4_LED, ramp);
    analogWrite(BUTTON_5_LED, ramp);
    analogWrite(BUTTON_6_LED, ramp);
    analogWrite(BUTTON_7_LED, ramp);
    analogWrite(BUTTON_8_LED, ramp);
    pulseDelayTimer = millis();
  }
}

void dimButtonLeds() {
  analogWrite(BUTTON_1_LED, rampMin);
  analogWrite(BUTTON_2_LED, rampMin);
  analogWrite(BUTTON_3_LED, rampMin);
  analogWrite(BUTTON_4_LED, rampMin);
  analogWrite(BUTTON_5_LED, rampMin);
  analogWrite(BUTTON_6_LED, rampMin);
  analogWrite(BUTTON_7_LED, rampMin);
  analogWrite(BUTTON_8_LED, rampMin);
}

void doButtons() {

  // update button input
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  button5.update();
  button6.update();
  button7.update();
  button8.update();
  // read buttons

  if (button1.fell()) {
#ifdef DEBUG
    Serial.println("1 Button Fell");
#endif
    state = 1;
    videoDelayTimer = millis();
    currentDelay = shoesDelay;
    //Keyboard.write('1');
    analogWrite(BUTTON_1_LED, pressedBrightness);
    Serial1.write(1);
  }

  if (button2.fell()) {
#ifdef DEBUG
    Serial.println("2 Button Fell");
#endif
    state = 1;
    videoDelayTimer = millis();
    currentDelay = beatsDelay;
    //Keyboard.write('2');
    analogWrite(BUTTON_2_LED, pressedBrightness);
    Serial1.write(2);
  }

  if (button3.fell()) {
#ifdef DEBUG
    Serial.println("3 Button Fell");
#endif
    state = 1;
    videoDelayTimer = millis();
    currentDelay = skewerDelay;
    //Keyboard.write('3');
    analogWrite(BUTTON_3_LED, pressedBrightness);
    Serial1.write(3);
  }

  if (button4.fell()) {
#ifdef DEBUG
    Serial.println("4 Button Fell");
#endif
    state = 1;
    videoDelayTimer = millis();
    currentDelay = shoesSPDelay;
    //Keyboard.write('4');
    analogWrite(BUTTON_4_LED, pressedBrightness);
    Serial1.write(4);
  }

  if (button5.fell()) {
#ifdef DEBUG
    Serial.println("5 Button Fell");
#endif
    state = 1;
    videoDelayTimer = millis();
    currentDelay = beatsSPDelay;
    //Keyboard.write('5');
    analogWrite(BUTTON_5_LED, pressedBrightness);
    Serial1.write(5);
  }

  if (button6.fell()) {
#ifdef DEBUG
    Serial.println("6 Button Fell");
#endif
    state = 1;
    videoDelayTimer = millis();
    currentDelay = skewerSPDelay;
    //Keyboard.write('6');
    analogWrite(BUTTON_6_LED, pressedBrightness);
    Serial1.write(6);
  }

  if (button7.fell()) {
#ifdef DEBUG
    Serial.println("7 Button Fell");
#endif
    state = 1;
    videoDelayTimer = millis();
    currentDelay = skewerSPDelay;
    //Keyboard.write('7');
    analogWrite(BUTTON_7_LED, pressedBrightness);
    Serial1.write(7);
  }

  if (button8.fell()) {
#ifdef DEBUG
    Serial.println("8 Button Fell");
#endif
    state = 1;
    videoDelayTimer = millis();
    currentDelay = skewerSPDelay;
    //Keyboard.write('8');
    analogWrite(BUTTON_8_LED, pressedBrightness);
    Serial1.write(8);
  }
}

void loop() {

  // pulse button leds
  // ramp up ledstrip brightness
  if (state == 0) {
    pulseButtonLeds();
    doButtons();
  } else if (state == 1) {
    // do nothing this loop to flash button on being pressed
    // transition to state 2
    delay(100);
    state = 2;
  } else  if (state == 2) {
    dimButtonLeds();
    // return to state 0 after 4 secs
    if (millis() - videoDelayTimer > currentDelay) {
      state = 0;
    }

  }


  if (millis() - heartBeatTimer > 500) {
    if (heartBeat) {
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
    }
    heartBeat = !heartBeat;
    heartBeatTimer = millis();
  }

 
}

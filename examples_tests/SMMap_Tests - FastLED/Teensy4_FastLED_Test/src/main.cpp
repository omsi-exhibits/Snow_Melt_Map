#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 900
#define NUM_STRIPS 2
#define LED_PIN 8

CRGB leds[NUM_LEDS];
CRGB currentColor = CRGB::Black;
CRGB targetColor = CRGB(255,255,255);

int fadeDir = 0; // 0 or 1
unsigned long startTime = 0;
unsigned long fadeDuration = 4000;

void setup() {
  FastLED.addLeds<NUM_STRIPS, WS2812B, LED_PIN, GRB>(leds, NUM_LEDS / NUM_STRIPS);
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  startTime = millis();
  FastLED.setMaxRefreshRate(60);
}

void loop() {
  if(millis() - startTime < fadeDuration) {
    // Fade in
    if(fadeDir == 0) { 
      float deltaTime = ((float)(millis() - startTime) / (float)fadeDuration);
      fract8 dTime = round(deltaTime * 255);
      /*Serial.print("DeltaTime: ");
      Serial.println(deltaTime);
      Serial.print("dTime: ");
      Serial.println(dTime);
      */
      currentColor = blend(CRGB::Black, targetColor, dTime);
    } else if (fadeDir == 1) {
      // Fade out
      float deltaTime = ( (float)(millis() - startTime) / (float)fadeDuration);
      fract8 dTime = round(deltaTime * 255);
      currentColor = blend(targetColor, CRGB::Black, dTime);
    }
    for(int i = 0; i < NUM_LEDS; i ++) {
      leds[i] = currentColor;
      /*if (i % 2) {
              leds[i] = currentColor;
      } else {
        leds[i] = CRGB(255,0,0);
      }*/
    }
    FastLED.show();
    //delay(25);
  } else {
    // toggle the direction of fd
    if(fadeDir == 0) {
      //delay(3000);
      fadeDir = 1;
    } else if(fadeDir == 1) {
      fadeDir = 0;
    }

    startTime = millis();
    //delay(25);
  }

}
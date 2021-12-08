#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 60
#define NUM_STRIPS 1
#define LED_PIN 14


int fadeDir = 0; // 0 or 1
unsigned long startTime = 0;
unsigned long fadeDuration = 500;

Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

float lerp (float x, float x0, float x1, float y0, float y1) {
    // linear interpellation
    x = x > x1 ? x1 : x;
    x = x < x0 ? x0 : x;
    return y0 + (y1-y0) * ((x-x0)/(x1-x0));
}
uint8_t lerpSingle(uint8_t startColor, uint8_t endColor, float deltaTime) {
    // lerp a single color channel. For example R for RGB.
    // deltaTime needs to be normalized value: 0 -1
    uint8_t currentColor = 0;
    if(deltaTime <= 1 && deltaTime >= 0) {
        currentColor = (uint8_t) round(lerp(deltaTime, 0.0, 1.0, startColor, endColor));
    } 
    return currentColor;
}
uint32_t lerpColor(uint32_t colorStart, uint32_t colorEnd, float deltaTime) {
    // start colors and end colors
    uint8_t u8R = (uint8_t)((colorStart >> 16) & 0xff),
                    u8G = (uint8_t)((colorStart >> 8) & 0xff),
                    u8B = (uint8_t)(colorStart & 0xff);
    uint8_t u8RE = (uint8_t)((colorEnd >> 16) & 0xff),
                    u8GE = (uint8_t)((colorEnd >> 8) & 0xff),
                    u8BE = (uint8_t)(colorEnd & 0xff);
    uint8_t rChan = lerpSingle(u8R, u8RE, deltaTime);
    uint8_t gChan = lerpSingle(u8G, u8GE, deltaTime);
    uint8_t bChan = lerpSingle(u8B, u8BE, deltaTime);
    uint32_t newColor = Adafruit_NeoPixel::Color(rChan,gChan,bChan,0);
    return newColor;
}


void setup() {
  leds.begin();
  for(int i = 0; i < NUM_LEDS; i++) {
    leds.setPixelColor(i,leds.Color(0,0,0));
  }
  startTime = millis();
}

void loop() {
  if(millis() - startTime < fadeDuration) {
    // Fade in
    if(fadeDir == 0) { 
      float deltaTime = ((float)(millis() - startTime) / (float)fadeDuration);

      //Serial.println(deltaTime);
      uint32_t currentFade = lerpColor(0, leds.Color(255,255,255), deltaTime);
      //currentFade = leds.gamma32(currentFade);
      leds.fill(currentFade);

      /*Serial.print("DeltaTime: ");
      Serial.println(deltaTime);
      Serial.print("dTime: ");
      Serial.println(dTime);
      */
    } else if (fadeDir == 1) {
      // Fade out
      float deltaTime = ( (float)(millis() - startTime) / (float)fadeDuration);
      uint32_t currentFade = lerpColor(leds.Color(255,255,255), 0, deltaTime);
      //currentFade = mStrip.gamma32(currentFade); // causes brightness to drop
      leds.fill(currentFade);
    }
    leds.show();
  } else {
    startTime = millis();
    // toggle the direction of fd
    if(fadeDir == 0) {
      fadeDir = 1;
    } else if(fadeDir == 1) {
      fadeDir = 0;
    }
  }

}
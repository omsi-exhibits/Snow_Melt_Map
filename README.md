# Snow Melt Map Notes
The electronics consist of a custom printed circuit board that has 8 button inputs and 3 or 4
addressable rgb led channels with a mcu to control the leds. The current mcu is Adafruit ItsyBitsy M0 express
with a plan to switch to a Teensy 4.0 if more pins or processing power is needed.

## Led Lights
WS2813B  WS2812 code compatible. These leds have 2 data channels incase one led breaks the
backup data channel will be used. This allows the strip to skip a bad led and continue.

## Power Calculations
550 leds 48ma each LED when light at max. The led strings come in 50 led segments. We need power injection every 50 leds at least.
So that is 11 + 1 the end of the strip. 50 Leds at 48mA is 2.4A.

- New idea to use 2pin 18awg jst connectors for power injections
I can connect an inline capacitor to them aswell.


## Prototype Testing
- [x] Led Fit anc securement into acrylic
- [x] Bigger areas that get lit up

## Microcontroller testing
- Leds on a 4 Meter ethernet cable using octows2812 level

# SNOW MELT MAP Button Target Areas
// Button 0 - Colorado R. & Tributaries
// --- R14 - R30 
// Button 1 - Snow Monitoring Sites
// Button 2 - Dams (7)
// Button 3 - Grand Junction City, Dam, and rivers to the right of the city leading into it
// --- R21b (0-12leds) & R22
// Button 4 - Los Vegas City, Dams, and river segments
// --- R14 - R30 light up & 4 Dams
// Button 5 - LA water supply from Colorado R.
// --- R13 - R33 + 4 dams
// Button 6 - LA supply from far away 
// --- All river supply. exclude R34
// Button 7 - Outside Colorado r. Watershed
// --- All Water supply areas.


- divide into segments and record led lengths
- [x] [ ] [ ] program some logic for things turning on and off
- program river flow animation
- design pcb schematic

## Programing Priorities
- [x] Init git and make a master&dev branch
- [ ] Mini Document how the prototype works now
- [x] MVP whole system
- [ ] Research git branching standards to use
- [x] Input system
- [ ] Toggle Sections
- [ ] RiverAnimation Simple
- [ ] Juicy RiverAnimations
- [ ] Create git project template ~
## Programing Notes
LedSegment defines a segment of leds, and their connection point to others.
LedRegion collects LedSegments and has state. The LedRegion can be interacted with.
- TurnedOn, TurnedOff, RiverOn, RiverOff.
- LedModule(Segment) that are for the Dams, etc. Should not store color data in their object.

## FastLED notes:
Colors are always dimmed down by a fraction. The dimming fraction is expressed in 256ths, so if you wanted to dim a color down by 25% of its current brightness, you first have to express that in 256ths. In this case, 25% = 64/256.
```cpp
  // Dim a color by 25% (64/256ths)
  // using "video" scaling, meaning: never fading to full black
  leds[i].fadeLightBy( 64 );
```
The library also provides a function that lets you 'clamp' each of the RGB channels to be within given minimums and maximums. 

Blending colors amountOfP2 is 0 - 255. 128 is 50% 255 is 100 color p2.
```cpp 
CRGB 	blend (const CRGB &p1, const CRGB &p2, fract8 amountOfP2)
```


## Test results
- [x] figure out led mounting.
- [x] test long wire length. between controller and sender
I tested it with total 1600 leds with the Neopixel Zero DMA library. 2400 leds was causing it to crash.
The HCT245 level shifter  

## Other tests
Try Teensy & Octo shield. Hook up all the lights.
Write code to animate led strings.
Test out the rs485 connector.

## Hardware Purchased:
(WS2813 LEDs from raywu)[https://www.aliexpress.com/item/32733155461.html]
Large 5v psu
(Aliexpress Neopixel store - Ray Wu) [https://www.aliexpress.com/store/701799?spm=a2g0o.detail.1000002.2.75cff4f3j9F8uI]
(Exact pixels): [https://www.aliexpress.com/item/32733155461.html]

## Misc Notes
Neopixels recomended distance from controller is 1 meter. Can be extended to 3 meters based on what people online say
nullpixels can be used every 3 meters to refresh the signal.
RS485 seems to be the solution for long runs. 
************************************************************************************************************************

(Wire Ampacity) [https://en.wikipedia.org/wiki/American_wire_gauge#Tables_of_AWG_wire_sizes]
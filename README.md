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
// Button 1 - Colorado R. & Tributaries
// --- R14 - R34
// Button 2 - Snow Monitoring Sites
// Button 3 - Dams (7)
// Button 4 - Los Vegas City, Dams, and river segments feeding Los Vegas. 
// --- R14 - R30 light up & 4 Dams (Lighting up Damns seems wrong, but maybe okay)
// Button 5 - Farms

// Button 6 - Grand Junction City, Dam, and rivers to the right of the city leading into it
// --- R21b (sub segment) (0-12leds) & R22, Dam
// Button 7 - Greater Los Angeles water supply
// --- Aqueducts too
// --- All river supply. exclude R34
// Button 8 -  (Long-distance water users) Outside Colorado r. Watershed
// --- All Water supply areas.

Once a button is pressed  - Only 1 button may be active at a time.
UI - dim all the currently lit segments and lights then activate what was pressed
Good opportunity for a fade in and fade out sound.

If the on button is pressed it turns the feature off.
If left on after a set time it can return to attractor mode. 

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
[WS2813 LEDs from raywu](https://www.aliexpress.com/item/32733155461.html)
Large 5v psu
[Aliexpress Neopixel store - Ray Wu](https://www.aliexpress.com/store/701799?spm=a2g0o.detail.1000002.2.75cff4f3j9F8uI)
[Exact pixels](https://www.aliexpress.com/item/32733155461.html)

## Misc Notes
Neopixels recomended distance from controller is 1 meter. Can be extended to 3 meters based on what people online say
nullpixels can be used every 3 meters to refresh the signal.
RS485 seems to be the solution for long runs. 
************************************************************************************************************************

(Wire Ampacity) [https://en.wikipedia.org/wiki/American_wire_gauge#Tables_of_AWG_wire_sizes]


## LED quality testing
I have determined that the last batch of hardware had some defects that likely were contributing to the intermittent problems
with leds flickering and possible temperature based issues.
We ordered more led strands to try to solve the issue. This time we got about 2x the leds we will need incase we run into the
same issues and need to pick the best leds from the pack.

### Testing quality
There should be a few tests to do on the newly arrived leds. For this we will need to re-setup the test rig. That will connect
Several of the strands together in series. 

- [ ] visual inspection. mark leds that pass. Jot down issues with ones that don't.
- [ ] connecting and running a test pattern
- [ ] Test connectors compatible with the final build 
- [ ] Test all the leds in a 400 led setup (at least 350)

We need 2 end connectors, and 7 in between connectors with power injection 

### Questions
Can a poorly soldered LED string damage the other strips?

Testing connector has a Data In connector, DataOut, and Power Injection connector. As well as a 1000mF capacitor.

Do we need to shorten the connectors to take up as little space as possible or make them as long as possible for the possibility of interconnecting to a segment farther away? 

[Wire Ampacity](https://en.wikipedia.org/wiki/American_wire_gauge#Tables_of_AWG_wire_sizes)

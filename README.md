# Snow Melt Map Notes
The electronics consist of a custom printed circuit board that has 8 button inputs and 3 or 4
addressable rgb led channels with a mcu to control the leds. The current mcu is Adafruit ItsyBitsy M0 express
with a plan to switch to a Teensy 4.0 if more pins or processing power is needed.

## Led Lights
WS2813B  WS2812 code compatible. These leds have 2 data channels incase one led breaks the
backup data channel will be used. This allows the strip to skip a bad led and continue.

## Prototype Testing
- [x] Led Fit anc securement into acrylic
- [x] Bigger areas that get lit up

## Microcontroller testing
- Leds on a 4 Meter ethernet cable using octows2812 level

# SNOW MELT MAP Notes
The Plan:
Breakdown map into segments.
There will need to be several strings
- River
- Snow sites
- Cities
- Dams
- Aquaducts
- Water sources

The code loop
// Get input
// update strip segments
// -- logic ~!
// draw leds

27 main segments

41 - segments
6 - water areas
7 - dams

- divide into segments and record led lengths
- [x] [ ] [ ] program some logic for things turning on and off
- program river flow animation
- design pcb schematic

## Programing Priorities
- [ ] Init git and make a master&dev branch
- [ ] Mini Document how the prototype works now
- [ ] MVP whole system
- [ ] Research git branching standards to use
- [ ] Input system
- [ ] Toggle Sections
- [ ] RiverAnimation Simple
- [ ] Juicy RiverAnimations
- [ ] Create git project template ~

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
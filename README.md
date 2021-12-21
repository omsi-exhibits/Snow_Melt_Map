# Snow Melt Map Notes
The electronics consist of a custom button controller pcb titled 8x_button_io_board that sends button press
commands to a octoWS2811 adapter with a teensy 4.0 socketed in it. The data sent over serial hand twisted
cable that is around 7 feet long. At a baud rate of 9600. 

addressable rgb led channels with a mcu to control the leds. The current mcu is Adafruit ItsyBitsy M0 express
with a plan to switch to a Teensy 4.0 if more pins or processing power is needed.

## Folder organization
- pcb :: contains eagle pcb files: 8x_button_io_board
- src :: main source code for the led controller 
- docs :: documentation, system diagram, map_led_hole numbering, river_segment_indexes, data sheets
- button_controller_arduino :: code for the button controller
- audio :: audio assets to be used with the wavTrigger board
- examples_tests :: quick tests used to guide prototype direction


## Led Lights
WS2813B  WS2812 code compatible. These leds have 2 data channels incase one led breaks the
backup data channel will be used. This allows the strip to skip a bad led and continue.

## Power Calculations
550 leds 48ma each LED when light at max. The led strings come in 50 led segments. We need power injection every 50 leds at least.
So that is 11 + 1 the end of the strip. 50 Leds at 48mA is 2.4A.

### Total Max Power usage
550 leds * 48mA = 26400mA, If all the leds are on at full brightness.
Power supply is a LRS-200-5 5v 200W output
(Wire Ampacity) [https://en.wikipedia.org/wiki/American_wire_gauge#Tables_of_AWG_wire_sizes]

### Adding fuse

(assorted fuses) [https://www.amazon.com/Bussmann-NO-43-Blade-Tester-Puller/dp/B000DCN9BW]
(fuse holder board mount) [https://www.keyelco.com/product.cfm/Mini-Auto-Fuse-Holders/3544-2/product_id/1376]
(fuse holder mini ATM) [https://www.digikey.com/en/products/detail/keystone-electronics/3568/2137306]

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

## Hardware Purchased:
[WS2813 LEDs from raywu](https://www.aliexpress.com/item/32733155461.html)
[Aliexpress Neopixel store - Ray Wu](https://www.aliexpress.com/store/701799?spm=a2g0o.detail.1000002.2.75cff4f3j9F8uI)
LRS-200-5

## LED quality testing
I have determined that the last batch of hardware had some defects that likely were contributing to the intermittent problems
with leds flickering and possible temperature based issues.
We ordered more led strands to try to solve the issue. This time we got about 2x the leds we will need incase we run into the
same issues and need to pick the best leds from the pack.
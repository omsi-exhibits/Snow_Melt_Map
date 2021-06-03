# Snow Melt Map Notes
The electronics consist of a custom printed circuit board that has 8 button inputs and 3 or 4
addressable rgb led channels and a mcu to control the leds. The current mcu is Adafruit ItsyBitsy M0 express
with a plan to switch to a Teensy 4.0 for more pins

## Led Lights
WS2813B  WS2812 code compatible. These leds have 2 data channels incase one led breaks the
backup data channel will be used. This allows the strip to skip a bad led and continue.

## Prototype Testing
- [x] Led Fit anc securement into acrylic
- [x] Bigger areas that get lit up


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


// Get input
// update strip segments
// -- logic ~!
// draw leds

27 main segments

41 - segments
6 - water areas
7 - dams

// River button is pressed
// River leds fade on
// Then river segments update
// THe segments that are water sources animate a drop flowing down 

What needs to be done?
- [x] figure out led mounting.
- [x] test long wire length. between controller and sender
- divide into segments and record led lengths
- program some logic for things turning on and off
- program river flow animation
- design pcb schematic


## Hardware Purchased:
[WS2813 LEDs from raywu](https://www.aliexpress.com/item/32733155461.html)
Large 5v psu

## Snow Melt Map
Try Teensy & Octo shield. Hook up all the lights.
Write code to animate led strings.
Test out the rs485 connector.

# Snow Melt Map Notes
Aliexpress Neopixel store - Ray Wu - https://www.aliexpress.com/store/701799?spm=a2g0o.detail.1000002.2.75cff4f3j9F8uI
Exact pixels: https://www.aliexpress.com/item/32733155461.html?gps-id=pcStoreJustForYou&scm=1007.23125.137358.0&scm_id=1007.23125.137358.0&scm-url=1007.23125.137358.0&pvid=f6f587cd-6b61-4b4d-a483-732021d7021d&spm=a2g0o.store_home.smartJustForYou_728718005.0

Neopixels recomended distance from controller is 1 meter. Can be extended to 3 meters based on what people online say
nullpixels can be used every 3 meters to refresh the signal.
RS485 seems to be the solution for long runs. 
************************************************************************************************************************

Wire Ampacity
https://en.wikipedia.org/wiki/American_wire_gauge#Tables_of_AWG_wire_sizes

12v LED modules: https://www.superbrightleds.com/moreinfo/led-module-strings/single-color-led-modules-linear-module-w-3-smd-leds-185-lumensmodule/6219/14110/

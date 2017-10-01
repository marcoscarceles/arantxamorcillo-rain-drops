#include "FastLED.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RGB Calibration code
//
// Use this sketch to determine what the RGB ordering for your chipset should be.  Steps for setting up to use:

// * Uncomment the line in setup that corresponds to the LED chipset that you are using.  (Note that they
//   all explicitly specify the RGB order as RGB)
// * Define DATA_PIN to the pin that data is connected to.
// * (Optional) if using software SPI for chipsets that are SPI based, define CLOCK_PIN to the clock pin
// * Compile/upload/run the sketch 

// You should see six leds on.  If the RGB ordering is correct, you should see 1 red led, 2 green 
// leds, and 3 blue leds.  If you see different colors, the count of each color tells you what the 
// position for that color in the rgb orering should be.  So, for example, if you see 1 Blue, and 2
// Red, and 3 Green leds then the rgb ordering should be BRG (Blue, Red, Green).  

// You can then test this ordering by setting the RGB ordering in the addLeds line below to the new ordering
// and it should come out correctly, 1 red, 2 green, and 3 blue.
//
//////////////////////////////////////////////////

#define NUM_LEDS 56

// Data pin that led data will be written out over
#define DATA_PIN 5
// Clock pin only needed for SPI based chipsets when not using hardware SPI
//#define CLOCK_PIN 8

#define BRIGHTNESS  8

CRGB leds[NUM_LEDS];

void setup() {
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);

      // Uncomment one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS)
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS)
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS)
      // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS)
      // FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS)
      // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS)
      FastLED.addLeds<WS2812B, 3, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
      FastLED.addLeds<WS2812B, 5, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
      FastLED.addLeds<WS2812B, 9, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
      FastLED.addLeds<WS2812B, 11, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
      // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS)
      // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS)
      // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS)
      // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS)

      // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS)
      // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS)
      //FastLED.addLeds<LPD8806, 9, 10, RGB>(leds, NUM_LEDS)

      // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS)
      // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS)
      // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS)

  FastLED.setBrightness(  BRIGHTNESS );
}

int tick = 255;

int counter = -1;

void loop() {
  for(int i = 0; i < NUM_LEDS/7; i++) {
    int index = i*7;
    leds[(index++) % NUM_LEDS] = CHSV( HUE_RED,    128, tick);
    leds[(index++) % NUM_LEDS] = CHSV( HUE_ORANGE, 128, tick);
    leds[(index++) % NUM_LEDS] = CHSV( HUE_GREEN,  128, tick);
    leds[(index++) % NUM_LEDS] = CHSV( HUE_AQUA,   128, tick);
    leds[(index++) % NUM_LEDS] = CHSV( HUE_BLUE,   128, tick);
    leds[(index++) % NUM_LEDS] = CHSV( HUE_PURPLE, 128, tick);
    leds[(index++) % NUM_LEDS] = CHSV( HUE_PINK,   128, tick);
  }
  FastLED.show();
  tick = (tick + counter);
  if(tick == 128) {
    counter = 1;
  }
  if(tick == 255) {
    counter = -1;
  }
  FastLED.delay(10);
}

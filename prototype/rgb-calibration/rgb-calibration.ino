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

#define NUM_LEDS 60

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
      FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS)
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
      .setCorrection( TypicalLEDStrip );

  FastLED.setBrightness(  BRIGHTNESS );
}

void loop() {
  for(int i = 0; i < NUM_LEDS/6; i++) {
    int index = i*6;
    leds[index++] = CRGB(255,0,0);      //RED
    leds[index++] = CRGB(0,255,0);      //GREEN
    leds[index++] = CRGB(0,255,0);      //GREEN
    leds[index++] = CRGB(0,0,255);      //BLUE
    leds[index++] = CRGB(255, 255,255); //WHITE
    leds[index++] = CRGB(0,0,0);        //BLACK
  }
  FastLED.show();
  FastLED.delay(1000);
}

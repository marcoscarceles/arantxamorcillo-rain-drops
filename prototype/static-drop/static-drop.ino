#include <FastLED.h>

#define SAFETY_BOOT_TIME 3000

#define LED_PIN     5
#define NUM_LEDS    60
#define BRIGHTNESS  32
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 60
#define PALETTE_DEPTH 256

CRGB leds[NUM_LEDS];

DEFINE_GRADIENT_PALETTE( RainDrop_gp ) {
    0,    0,    0,    0, //Black
  127,   15,   15,   15, //Darker
  191,   63,   63,   63, //Dark
  223,  127,  127,  127, //Light
  255,  255,  255,  255  //White
};

CRGBPalette16 palette;
int dropSize = 8;
int paletteStep = PALETTE_DEPTH / dropSize;

void setup() {
  delay(SAFETY_BOOT_TIME);
  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  palette = RainDrop_gp;
}


void loop() {
  for(int i = 0; i < dropSize; i++) {
//    Flickers with low globl brightness
    leds[NUM_LEDS/2+i] = ColorFromPalette(palette, (i*paletteStep) % PALETTE_DEPTH, 255, NOBLEND);
  }
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}


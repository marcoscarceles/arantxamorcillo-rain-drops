#include <FastLED.h>

#define SAFETY_BOOT_TIME 3000

#define LED_PIN     5
#define NUM_LEDS    60
#define BRIGHTNESS  32
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define PALETTE_DEPTH 256

#define UPDATES_PER_SECOND 100
#define DROP_CONSTANT 40

CRGB leds[NUM_LEDS];

DEFINE_GRADIENT_PALETTE( RainDrop_gp ) {
    0,   15,   15,   15, //Shadow
  127,   31,   31,   31, //Darker
  191,   63,   63,   63, //Dark
  223,  127,  127,  127, //Light
  255,  255,  255,  255  //White
};

CRGBPalette16 palette;
int stepCounter = -1;
int dropPosition = 0;
int dropSize = 16;
int dropStep = DROP_CONSTANT / dropSize;
int paletteStep = PALETTE_DEPTH / dropSize;

void setup() {
  delay(SAFETY_BOOT_TIME);
  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  palette = RainDrop_gp;
}


void loop() {

  stepCounter = (stepCounter + 1) % dropStep;

  if(stepCounter == 0) {
    dropPosition = (dropPosition + 1) % (NUM_LEDS);
  }

  //Cleanup previous drop
  leds[(dropPosition+NUM_LEDS-1) % NUM_LEDS] = CRGB::Black;

  for(int i = 0; i < dropSize; i++) {
    int index = (dropPosition + i) % (NUM_LEDS);

    // Fade away drop as it falls
    int brightness = 255 * (NUM_LEDS - index) / NUM_LEDS;
    
    // Flickers with low globl brightness
    leds[index] = ColorFromPalette(palette, (i*paletteStep) % PALETTE_DEPTH, brightness, LINEARBLEND);
  }

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}


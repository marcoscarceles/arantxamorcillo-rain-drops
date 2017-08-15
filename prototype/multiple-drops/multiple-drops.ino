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

#define MAX_DROPS 8

#define NEW_DROP_INTERVAL 50

CRGB leds[NUM_LEDS];

DEFINE_GRADIENT_PALETTE( RainDrop_gp ) {
    0,    3,    3,   3, //Shadow
  127,    7,    7,    7, //Darker
  191,   31,   31,   31, //Dark
  223,  127,  127,  127, //Light
  255,  255,  255,  255  //White
};

typedef struct drop_t {
  int size;
  int position;
  int speedOffset;
} Drop;

Drop drops[MAX_DROPS];

CRGBPalette16 palette;

int totalDrops = 0;

void setup() {

  totalDrops = MAX_DROPS;//random(2, MAX_DROPS+1);
  for(int i = 0; i < MAX_DROPS; i++) {
    if(i < totalDrops) {
      drops[i].position = random(0, NUM_LEDS);
      drops[i].size = pow(2, 3+random(0, 2)); //One of [8, 16]
      drops[i].speedOffset = random(-1, 2);
    } else {
      drops[i].position = -NUM_LEDS;
      drops[i].size = -1;
      drops[i].speedOffset = 0;
    }
  }

  //Do not operate LED's before this time
  delay(SAFETY_BOOT_TIME);
  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  palette = RainDrop_gp;
}

int stepCounter = -1;

void loop() {

  stepCounter = (stepCounter + 1) % DROP_CONSTANT;

  //Cleanup previous step
  fill_solid( leds, NUM_LEDS, CRGB::Black );

  //For every drop
  for(int dropIndex = 0; dropIndex < totalDrops; dropIndex++) {
    
    //If the drop is visible
    if(drops[dropIndex].size > 0) {
      Drop* drop = drops + dropIndex;
      //Calculate its position
      int dropStep = (DROP_CONSTANT / drop->size) + drop->speedOffset;
      bool nextStep = (stepCounter % dropStep) == 0;
    
      if(nextStep == 0) {
        drop->position = (drop->position + 1) % (NUM_LEDS);
      }

      //Paint it
      for(int dropPixel = 0; dropPixel < drop->size; dropPixel++) {
        int index = (drop->position + dropPixel) % (NUM_LEDS);
    
        // Fade away drop as it falls
        int brightness = 255 * (NUM_LEDS - index) / NUM_LEDS;
        
        // Flickers with low globl brightness
        int paletteStep = PALETTE_DEPTH / drop->size;
        CRGB dropColour = ColorFromPalette(palette, (dropPixel*paletteStep) % PALETTE_DEPTH, brightness, LINEARBLEND);

        leds[index].red   = leds[index].red    + dropColour.red   / totalDrops ;
        leds[index].green = leds[index].green  + dropColour.green / totalDrops ;
        leds[index].blue  = leds[index].blue   + dropColour.blue  / totalDrops  ;
      }
    }
  }

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}


#include <FastLED.h>

#define SAFETY_BOOT_TIME 3000

#define STRIP_A       3
#define STRIP_B       5
#define STRIP_C       9
#define STRIP_D       11
#define STRIPS        4
#define NUM_LEDS      60
#define BRIGHTNESS    32
#define MINIMUM_INTENSITY 36 // Below this threshold the strip misbehaves
#define LED_TYPE      NEOPIXEL
#define COLOR_ORDER   RGB

#define SPEED_FACTOR 4

#define UPDATES_PER_SECOND  200

//PLAY WITH THESE VALUES FOR MAX AND MI INTENSITY
#define MAX_DROPS           8
#define MAX_DROP_INTENSITY  255
#define BRIGHTNESS          32

CRGB  leds[STRIPS][NUM_LEDS];
int intensity[NUM_LEDS];

typedef struct drop_t {
  int size;
  int position;
  int tick;
} Drop;

Drop drops[STRIPS][MAX_DROPS];

void setup() {

  //Do not operate LED's before this time
  FastLED.delay(SAFETY_BOOT_TIME);
  fill_solid(leds[0], NUM_LEDS, CRGB::Black );
  fill_solid(leds[1], NUM_LEDS, CRGB::Black );
  fill_solid(leds[2], NUM_LEDS, CRGB::Black );
  fill_solid(leds[3], NUM_LEDS, CRGB::Black );

  //Define drops
  for(int strip = 0; strip < STRIPS; strip++) {
    for(int i = 0; i < MAX_DROPS; i++) {
      drops[strip][i].position = random(NUM_LEDS);
      drops[strip][i].size = pow(2, 2+random(3)); //One of [8, 16]
      drops[strip][i].tick = drops[strip][i].size;
    }
  }

  FastLED.addLeds<LED_TYPE, STRIP_A>( leds[0], NUM_LEDS ).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, STRIP_B>( leds[1], NUM_LEDS ).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, STRIP_C>( leds[2], NUM_LEDS ).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, STRIP_D>( leds[3], NUM_LEDS ).setCorrection( TypicalLEDStrip );

  fill_solid( leds[0], NUM_LEDS, CRGB::Black );
  fill_solid( leds[1], NUM_LEDS, CRGB::Black );
  fill_solid( leds[2], NUM_LEDS, CRGB::Black );
  fill_solid( leds[3], NUM_LEDS, CRGB::Black );

  FastLED.setDither( 0 );
  FastLED.setBrightness(  BRIGHTNESS );

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);

}

void loop() {

  //On each strip
  for(int strip = 0; strip < STRIPS; strip++) {
    //Cleanup previous step
    fill_solid(leds[strip], NUM_LEDS, CRGB::Black );

    for(int pixel = 0; pixel < NUM_LEDS; pixel++) {
      intensity[pixel] = 0;
    }

    //For every drop
    for(int i = 0; i < MAX_DROPS; i++) {
      Drop* drop = &drops[strip][i];

      //Draw its pixels
      for(int j = 0; j < drop->size; j++) {
        int position = (drop->position + j) % NUM_LEDS;
        int dropValue = (j+1) * MAX_DROP_INTENSITY / drop->size ;
        //intensity[position] += dropValue;
        intensity[position] =  max(intensity[position], dropValue);
      }

      drop->tick -= SPEED_FACTOR;

      if(drop->tick <= 0) {
        drop->tick = drop->size;
        drop->position++;
      }
    }

    //Paint the strip
    for(int pixel = 0; pixel < NUM_LEDS; pixel++) {
      //int value = min(intensity[pixel], 255);
      int value = intensity[pixel];
      leds[strip][pixel] = CHSV(HUE_AQUA,   144, value);
    }
  }

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}


#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    9
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    60
CRGB leds[NUM_LEDS];
int pos = 0;

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}



  
void loop()
{

 // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(100/FRAMES_PER_SECOND); 
  if(pos<NUM_LEDS){
  leds[pos] = CRGB( 200, 200, 200);
  leds[pos-1] = CRGB( 100, 100, 100);
  leds[pos-2] = CRGB( 30, 30, 30);
  leds[pos-3] = CRGB::Black;
  } else {
    leds[NUM_LEDS-1] = CRGB::Black;
    leds[NUM_LEDS-2] = CRGB::Black;
    leds[NUM_LEDS-3] = CRGB::Black;
    pos = 0;
  }
  pos++;
  delay(70);
}




  

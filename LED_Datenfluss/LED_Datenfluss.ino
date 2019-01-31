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
int incomingByte = 0;

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

void setup() {

  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(9600);
  Serial.print("Los");
}


  
void loop()
{


if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    Serial.print(incomingByte);
  }


if (incomingByte == 49) {

 FastLED.show();  
  FastLED.delay(100/FRAMES_PER_SECOND); 
  for(int pos = 1; pos <= NUM_LEDS; pos++) { 
            leds[pos] = CRGB::Green;
            FastLED.show();
            // clear this led for the next time around the loop
            leds[pos] = CRGB::Black;
            delay(100);
}

  
 /*// send the 'leds' array out to the actual LED strip
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
  delay(70);*/
  }
  
  else if (incomingByte == 50)
  {

  FastLED.show();  
  FastLED.delay(100/FRAMES_PER_SECOND); 
  for(int pos = 60; pos <= NUM_LEDS; pos--) { 
            leds[pos] = CRGB::Blue;
            FastLED.show();
            // clear this led for the next time around the loop
            leds[pos] = CRGB::Black;
            delay(100);
            
}
  }
}

  




  

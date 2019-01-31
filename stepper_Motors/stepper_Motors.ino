
#include <FastLED.h>

// LEDs
FASTLED_USING_NAMESPACE
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif
#define DATA_PIN    9
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    59
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
int previousLEDrun = false;
int currentLED = 0;
int currentLED2= 59;


// stepper motors
int incomingByte = 0;
int cabinSteps = 0;
const int stepPinRotor = 2; 
const int dirPinRotor = 3;
const int stepPinCabin = 4; 
const int dirPinCabin = 5;  

// general
int rotateCabin = false; // false standing still, true turning
int currentStatusLEDs = 0; // 0 off, -1 down, 1 up
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
const long interval = 500;


void setup() {
  //delay(3000); // 3 second delay for recovery
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(stepPinCabin,OUTPUT); 
  pinMode(dirPinCabin,OUTPUT);
  pinMode(stepPinRotor,OUTPUT); 
  pinMode(dirPinRotor,OUTPUT);
  Serial.begin(9600);
  Serial.print("los");

  digitalWrite(dirPinRotor,HIGH);
  digitalWrite(dirPinCabin,HIGH);
}

void loop()
{
  unsigned long currentMillis = millis();
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    
  }
  
  if (incomingByte == 49) {
    Serial.print("1");
    rotateCabin = true;
  }
  /*else if (incomingByte != 49) {
    Serial.print("nichts");
  }*/

  else if (incomingByte == 50) {

    //previousLEDrun = true;
    currentStatusLEDs = 2;
    Serial.print("2"); 
    //Serial.print(incomingByte);
    // FastLED.show();  
    // FastLED.delay(100/FRAMES_PER_SECOND); 

  if(currentLED <= NUM_LEDS && currentStatusLEDs == 2 && currentMillis - previousMillis >= interval) { 
            previousMillis = currentMillis;
            leds[currentLED] = CRGB::Red;
            leds[currentLED-1] = CRGB::Green;
            leds[currentLED-2] = CRGB::Black;
            FastLED.show();
            //FastLED.delay(100/FRAMES_PER_SECOND); 
            // clear this led for the next time around the loop
            leds[currentLED] = CRGB::Black;
            leds[currentLED-1] = CRGB::Black;
            //delay(100);
            currentLED++;
            
  }
  currentStatusLEDs = 0;
  }

     else if (incomingByte == 51) {
      
  
    //previousLEDrun = true;
     currentStatusLEDs = 3;
     Serial.print("3"); 
    //Serial.print(incomingByte);
    // FastLED.show();  
    // FastLED.delay(100/FRAMES_PER_SECOND); 

  if(currentLED2 <= NUM_LEDS && currentStatusLEDs == 3 && currentMillis - previousMillis2 >= interval) { 
    Serial.print("Blau");
            previousMillis2 = currentMillis;
            leds[currentLED2] = CRGB::Red;
            leds[currentLED2-1] = CRGB::Blue;
            leds[currentLED2-2] = CRGB::Green;
            FastLED.show();
            //delay(500);
            //FastLED.delay(100/FRAMES_PER_SECOND); 
            // clear this led for the next time around the loop
            Serial.print("WIESO");
            leds[currentLED2] = CRGB::Black;
            leds[currentLED2-1] = CRGB::Black;
            leds[currentLED2-2] = CRGB::Black;
            //delay(100);
            currentLED2--; 

          
  }
  currentStatusLEDs = 0;
  }
    

 
  /*if (currentLED >= NUM_LEDS) {
    currentStatusLEDs = 0;
    currentLED = 0;
    previousLEDrun = true;
  }

  // turning or not
 /* if (rotateCabin == true && cabinSteps <= 3000) {
    cabinStep();
    cabinSteps ++;
    rotorStep();
  } else {
    rotorStep();
    rotateCabin = false;
    cabinSteps = 0;
  }
 */ 
  // LEDs moving or not
  /*if (previousLEDrun && currentMillis - previousMillis >= interval) {
    int op = currentMillis - previousMillis;
    Serial.print(">"+currentLED);
    previousMillis = currentMillis;
    leds[2] = CRGB::Blue;
    FastLED.show();
    // clear this led for the next time around the loop
    leds[1] = CRGB::Black;
    currentLED++;
  }*/
 
}

void rotorStep(){
  digitalWrite(stepPinRotor,HIGH); 
  delayMicroseconds(500); 
  digitalWrite(stepPinRotor,LOW); 
  delayMicroseconds(500);
}

void cabinStep(){
  digitalWrite(stepPinCabin,HIGH); 
  delayMicroseconds(500); 
  digitalWrite(stepPinCabin,LOW); 
  delayMicroseconds(500);
}


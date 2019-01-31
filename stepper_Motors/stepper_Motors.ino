
#include <FastLED.h>

// LEDs
FASTLED_USING_NAMESPACE
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif
#define DATA_PIN    2
#define LED_TYPE WS2812B
#define COLOR_ORDER RGB
#define NUM_LEDS    60
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
int previousLEDrun = false;
int currentLED = 0;


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
const long interval = 30;

void setup() {
  delay(3000); // 3 second delay for recovery
  //FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.setBrightness(BRIGHTNESS);
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
    Serial.print(incomingByte);
  }
  
  if (incomingByte == 49) {
    rotateCabin = true;
  }
  /*else if (incomingByte != 49) {
    Serial.print("nichts");
  }*/

  else if (incomingByte == 50) {
    currentStatusLEDs = 1;
    previousLEDrun = true;
    //Serial.print("geht");
    FastLED.show();
  }
 
  if (currentLED >= NUM_LEDS) {
    currentStatusLEDs = 0;
    currentLED = 0;
    previousLEDrun = true;
  }

  // turning or not
  if (rotateCabin == true && cabinSteps <= 3000) {
    cabinStep();
    cabinSteps ++;
    rotorStep();
  } else {
    rotorStep();
    rotateCabin = false;
    cabinSteps = 0;
  }
 
  // LEDs moving or not
  if (previousLEDrun && currentMillis - previousMillis >= interval) {
    int op = currentMillis - previousMillis;
    Serial.print(">"+currentLED);
    previousMillis = currentMillis;
    leds[2] = CRGB::Blue;
    FastLED.show();
    // clear this led for the next time around the loop
    leds[1] = CRGB::Black;
    currentLED++;
  }
 
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


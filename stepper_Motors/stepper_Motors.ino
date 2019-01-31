
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
int currentLED2 = 59;


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
const long interval = 100;
int showLEDVorne = false;
int showLEDHinten = false;


void setup() {
  //delay(3000); // 3 second delay for recovery
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(stepPinCabin, OUTPUT);
  pinMode(dirPinCabin, OUTPUT);
  pinMode(stepPinRotor, OUTPUT);
  pinMode(dirPinRotor, OUTPUT);
  Serial.begin(9600);
  Serial.print("los");

  digitalWrite(dirPinRotor, HIGH);
  digitalWrite(dirPinCabin, HIGH);
}


/* turning or not
  if (rotateCabin == true && cabinSteps <= 3000) {
  cabinStep();
  cabinSteps ++;
  rotorStep();
  } else {
  rotorStep();
  rotateCabin = false;
  cabinSteps = 0;
  }*/

//LEDs moving or not
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



void rotorStep() {
  digitalWrite(stepPinRotor, HIGH);
  delayMicroseconds(500);
  digitalWrite(stepPinRotor, LOW);
  delayMicroseconds(500);
}

void cabinStep() {
  digitalWrite(stepPinCabin, HIGH);
  delayMicroseconds(500);
  digitalWrite(stepPinCabin, LOW);
  delayMicroseconds(500);
}

void loop()
{
  unsigned long currentMillis = millis();
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
  }

  if (incomingByte == 49) {
    incomingByte = 0;
    rotateCabin = true;
  }

  if (incomingByte != 49) {

  }


  if (incomingByte == 50) {
    incomingByte = 0;
    showLEDVorne = true;
  }

  if (incomingByte == 51) {
    incomingByte = 0;
    showLEDHinten = true;
  }


  if (showLEDVorne == true && currentLED <= NUM_LEDS && currentMillis - previousMillis >= interval) {
    //previousLEDrun = true;
    //currentStatusLEDs = 2;

    //Serial.print(incomingByte);
    // FastLED.show();
    // FastLED.delay(100/FRAMES_PER_SECOND);

    //if (currentLED <= NUM_LEDS && currentStatusLEDs == 2 && currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    leds[currentLED] = CRGB::Green;
    leds[currentLED - 1] = CRGB::Green;
    leds[currentLED - 2] = CRGB::Black;
    FastLED.show();
    //FastLED.delay(100/FRAMES_PER_SECOND);
    // clear this led for the next time around the loop
    leds[currentLED] = CRGB::Black;
    leds[currentLED - 1] = CRGB::Black;
    //delay(100);
    currentLED++;
  }
  else if (currentLED == NUM_LEDS) {
    showLEDVorne = false;
    currentLED = 0;
  }

  if (showLEDHinten == true && currentLED2 <= NUM_LEDS && currentMillis - previousMillis2 >= interval) {

    previousMillis2 = currentMillis;
    leds[currentLED2] = CRGB::Blue;
    leds[currentLED2 - 1] = CRGB::Blue;
    leds[currentLED2 - 2] = CRGB::Green;
    FastLED.show();
    //delay(500);
    //FastLED.delay(100/FRAMES_PER_SECOND);
    // clear this led for the next time around the loop
    leds[currentLED2] = CRGB::Black;
    leds[currentLED2 - 1] = CRGB::Black;
    leds[currentLED2 - 2] = CRGB::Black;
    //delay(100);
    currentLED2--;
  }
  else if (currentLED2 == 0) {
    showLEDHinten = false;
    currentLED2 = 59;
  }





  /*if (currentLED >= NUM_LEDS) {
    currentStatusLEDs = 0;
    currentLED = 0;
    previousLEDrun = true;
    }*/

  if (rotateCabin == true && cabinSteps <= 3000) {
    cabinStep();
    cabinSteps ++;
    rotorStep();
  } else {
    rotorStep();
    rotateCabin = false;
    cabinSteps = 0;
  }



}


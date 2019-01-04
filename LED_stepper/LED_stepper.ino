#include <Stepper.h>
#include <FastLED.h>

// LEDs
FASTLED_USING_NAMESPACE
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif
#define DATA_PIN    2
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    60
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
int previousLEDrun = false;
int currentLED = 0;

// stepper motors
int incomingByte = 0;
int previousStepsCabin = 500;
const int stepperRotorBladesSteps = 500;  // change this to fit the number of steps per revolution for your motor
const int stepperCabinSteps = -500;
Stepper stepperCabin(stepperCabinSteps, 8, 10, 9, 11);
Stepper stepperRotorBlades(stepperRotorBladesSteps, 4, 6, 5, 7);

// general
int currentStatusAngle = false; // false standing still, true turning
int currentStatusLEDs = 0; // 0 off, -1 down, 1 up
unsigned long previousMillis = 0;
const long interval = 30;

void setup() {
  delay(3000); // 3 second delay for recovery
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  stepperCabin.setSpeed(15);
  stepperRotorBlades.setSpeed(15);
  Serial.begin(9600);
}

void loop()
{
  unsigned long currentMillis = millis();
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
  if (incomingByte == 49) {
    currentStatusAngle = true;
  }
  else if (incomingByte == 50) {
    currentStatusLEDs = 1;
    previousLEDrun = true;
  }

  // check if status still valid
  if (previousStepsCabin >= stepperCabinSteps) {
    previousStepsCabin = 500;
    currentStatusAngle = false;
  }
  if (currentLED >= NUM_LEDS) {
    currentStatusLEDs = 0;
    currentLED = 0;
    previousLEDrun = true;
  }

  // turning or not
  if (currentStatusAngle) {
    stepperCabin.step(stepperCabinSteps / stepperRotorBladesSteps);
    stepperRotorBlades.step(stepperRotorBladesSteps / stepperCabinSteps);
    previousStepsCabin--;
  } else {
    stepperRotorBlades.step(stepperRotorBladesSteps);
    previousStepsCabin = 0;
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

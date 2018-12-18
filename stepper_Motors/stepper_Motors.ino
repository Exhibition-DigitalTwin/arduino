#include <Stepper.h>

int incomingByte = 0;
int previousStepsCabin = 0;

const int stepperRotorBladesSteps = 500;  // change this to fit the number of steps per revolution for your motor
const int stepperCabinSteps = 500;

// initialize the stepper library on pins 8 through 11:
Stepper stepperCabin(stepperCabinSteps, 8, 10, 9, 11);
Stepper stepperRotorBlades(stepperRotorBladesSteps, 4, 6, 5, 7);

void setup() {
  // set the speed at 60 rpm:
  stepperCabin.setSpeed(15);
  stepperRotorBlades.setSpeed(15);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
  if (incomingByte == 49) {
    Serial.println("turning cabin angle");
    while (previousStepsCabin < stepperCabinSteps) {
      int doSteps = stepperCabinSteps - previousStepsCabin;
      previousStepsCabin++;
      stepperCabin.step(1);
      stepperRotorBlades.step(1);
    }
    previousStepsCabin = 0;
    delay(10);
  }
  stepperRotorBlades.step(stepperRotorBladesSteps);
  delay(10);
}

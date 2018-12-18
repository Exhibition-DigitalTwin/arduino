#include <Stepper.h>

int incomingByte = 0; 


const int stepsPerRevolution = 500;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper myStepper1(stepsPerRevolution, 4, 6, 5, 7);

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(15);
  myStepper1.setSpeed(15);
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
        
  if(incomingByte == 49){
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);
  }

  else {}

  myStepper1.step(stepsPerRevolution);
  delay(10);
}

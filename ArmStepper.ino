#include "SpeedyStepper.h"
#include "RCServo.h"

SpeedyStepper armStepper; // init objects from libs
RCServo EMagnet;

int microStepping = 8;  // settings values
float armAccel = 2;
float armSpeed = 10;
int steps = 200;
int transmissionRatio = 2;
float maxDistance = 1.0;

const byte ARM_STEPPER_PIN = 2; // assigning sensors and pins to vars
const byte HOME_SENSOR_PIN = A1;
const byte TOP_SENSOR_PIN = A2;
const byte BOTTOM_SENSOR_PIN = A3;
const byte EMAGNET_PIN = A4;
const byte PISTON_PIN = 10;

void setup() {
  pinMode(HOME_SENSOR_PIN, INPUT_PULLUP); // init sensors to be inputs
  pinMode(TOP_SENSOR_PIN, INPUT_PULLUP);
  pinMode(BOTTOM_SENSOR_PIN, INPUT_PULLUP);
  pinMode(PISTON_PIN, OUTPUT);

  armStepper.connectToPort(ARM_STEPPER_PIN); // init stepper and electromagnet
  EMagnet.connectToPin(EMAGNET_PIN);

  armStepper.setAccelerationInRevolutionsPerSecondPerSecond(armAccel); //init the speed and accel
  armStepper.setStepsPerRevolution(transmissionRatio * microStepping * steps);
  armStepper.setSpeedInRevolutionsPerSecond(armSpeed);
}

void loop() {
  goHome();
  goToTopTower();
  turnOnEMagnet();
  armGoDown();
  delay(1000);
  armGoUp();
  delay(2000);
  GoToBottomPad();
  armGoDown();
  delay(2000);
  turnOffEmagnet();
  armGoUp();
  delay(2000);
}

void goHome() {
  armStepper.moveToHomeInRevolutions(-1, armSpeed, maxDistance, HOME_SENSOR_PIN);
}

void goToTopTower() {
  armStepper.moveToPositionInRevolutions(.255);
}

void turnOnEMagnet() {
  EMagnet.setServoPosition(1.0);
}

void turnOffEmagnet() {
  EMagnet.setServoPosition(0.0);
}

void armGoUp() {
  digitalWrite(PISTON_PIN, LOW);
}

void armGoDown() {
  digitalWrite(PISTON_PIN, HIGH);
}

void GoToBottomPad() {
  armStepper.moveToPositionInRevolutions(.42);
}

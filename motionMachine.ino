#include "SpeedyStepper.h"
#include "RCServo.h"

//variables

SpeedyStepper rampStepper;
RCServo gateServo;

const byte RAMPSTEPPER_PORT = 2;
const byte GATE_SERVO_PIN = A0;
const byte BOTTOM_SENSOR = A1;
const byte TOP_SENSOR = A2;
const byte RAMP_HOME_LIMIT_SWITCH_PIN = A3;
const byte STAIR_MOTOR_PIN = 10;

int distance = 230;
const byte steps = 25;
const byte microStepping = 8;
const byte rampStepperSpeed = 25;
const byte rampStepperAccel = 10;


void setup() {

  //pinmodes to set up
  pinMode(TOP_SENSOR, INPUT_PULLUP);
  pinMode(BOTTOM_SENSOR, INPUT_PULLUP);
  pinMode(RAMP_HOME_LIMIT_SWITCH_PIN, INPUT_PULLUP);
  pinMode(STAIR_MOTOR_PIN, OUTPUT);
  // pinMode(RAMP_STEPPER, INPUT_PULLUP);


  //methods to connect to ports/pins
  gateServo.connectToPin(GATE_SERVO_PIN);
  rampStepper.connectToPort(RAMPSTEPPER_PORT);

  //setup rampStepper speeds and accel
  rampStepper.setStepsPerMillimeter(steps * microStepping);
  rampStepper.setSpeedInMillimetersPerSecond(rampStepperSpeed);
  rampStepper.setAccelerationInMillimetersPerSecondPerSecond(rampStepperAccel);

  //Move to home
  goHome();

  //Make sure gate is closed
  gateServo.setServoPosition(-1);

}

void loop() {

  if (digitalRead(BOTTOM_SENSOR == 0)) {
    moveUpRamp();
  }
  delay(1000);
  startStairs();
  delay(3500);
  stopStairs();
  goHome();
  gateServoOpen();
  delay(1000);
  gateServoClose();

}

void goHome() {
  rampStepper.moveToHomeInMillimeters(-1, rampStepperSpeed, distance, RAMP_HOME_LIMIT_SWITCH_PIN);
}

void moveUpRamp() {
  rampStepper.moveToPositionInMillimeters(230);
}

void startStairs() {
  digitalWrite(STAIR_MOTOR_PIN, HIGH);
}

void stopStairs() {
  digitalWrite(STAIR_MOTOR_PIN, LOW);
}

void gateServoOpen() {
  gateServo.setServoPosition(0);
}

void gateServoClose() {
  gateServo.setServoPosition(-1);
}

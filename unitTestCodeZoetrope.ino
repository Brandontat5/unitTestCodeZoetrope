#include <Arduino.h>
#include <SpeedyStepper.h>
#include <FlexyStepper.h>

#define BEAM_BUTTON_LIGHT 24
#define BEAM_BUTTON 25
#define BEAM_LEDS 10

#define BACKLIGHT_BUTTON_LIGHT 26
#define BACKLIGHT_BUTTON 27
#define BACKLIGHT_LEDS 9

#define LID_SENSOR 28

#define MOTOR_BUTTON_LIGHT 8
#define MOTOR_BUTTON 23
#define MOTOR_SPEED_POT A1
#define MOTOR_PORT 1

#define MICROSTEPPING 8
#define TRANSMISSION 5
#define BASE_STEPS_PER_REV 200
#define MIN_SPEED 0.2  //0.075

int beamState = LOW;
int lastBeamState = LOW;
bool beamCount = false;
int backlightState = LOW;
int lastBacklightState = LOW;
bool backlightCount = false;
int motorState = LOW;
int lastMotorState = LOW;
bool motorCount = false;

int potVal = 0;
int lastPotVal = 0;

FlexyStepper stepper;

void setup() {
  ////// Pinmode all ports ///////////

  pinMode(MOTOR_BUTTON_LIGHT, OUTPUT);
  pinMode(MOTOR_BUTTON, INPUT_PULLUP);
  pinMode(MOTOR_SPEED_POT, INPUT_PULLUP);

  pinMode(BEAM_BUTTON_LIGHT, OUTPUT);
  pinMode(BEAM_BUTTON, INPUT_PULLUP);
  pinMode(BEAM_LEDS, OUTPUT);

  pinMode(BACKLIGHT_BUTTON_LIGHT, OUTPUT);
  pinMode(BACKLIGHT_BUTTON, INPUT_PULLUP);
  pinMode(BACKLIGHT_LEDS, OUTPUT);

  pinMode(LID_SENSOR, INPUT_PULLUP);

  ////////// Initialize Stepper //////////

  stepper.connectToPort(MOTOR_PORT);
  stepper.setStepsPerRevolution(BASE_STEPS_PER_REV * TRANSMISSION * MICROSTEPPING);
  stepper.setSpeedInRevolutionsPerSecond(1.6);
  stepper.setAccelerationInRevolutionsPerSecondPerSecond(0.05);
  stepper.setCurrentPositionInRevolutions(0.0);
  stepper.setTargetPositionRelativeInRevolutions(1000.0);
  stepper.enableStepper();

  ///////// Initialize Lights and Button Lights //////////

  digitalWrite(MOTOR_BUTTON_LIGHT, motorState);
  digitalWrite(BEAM_BUTTON_LIGHT, beamState);
  digitalWrite(BEAM_LEDS, beamState);
  digitalWrite(BACKLIGHT_BUTTON_LIGHT, backlightState);
  digitalWrite(BACKLIGHT_LEDS, backlightState);

}

void loop() {
  //stepper.setSpeedInRevolutionsPerSecond(1);
  stepper.setSpeedInRevolutionsPerSecond(MIN_SPEED +  (float)potVal / 1023.0 * 1.5);
  stepper.processMovement();
}

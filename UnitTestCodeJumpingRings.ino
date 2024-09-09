//variables

const byte chargeRelayPin = 27;
const byte ringOneRelayPin = 28;
const byte ringTwoRelayPin = 29;
const byte ringOneLEDPin = 54;
const byte ringTwoLEDPin = 55;
const byte ringThreeLEDPin = 56;
const int blinkDelayForLED = 100;
const int waitTimeForHighCharge = 18000;
const int waitTimeForLowCharge = 18000;
const int waitTimeForRingJump = 1000;

// set up, only does one run per reset

void setup() {
  pinMode(chargeRelayPin, OUTPUT); //init lEDS
  pinMode(ringOneLEDPin, OUTPUT);
  pinMode(ringTwoLEDPin, OUTPUT);
  pinMode(ringThreeLEDPin, OUTPUT);

  chargeCapacitor(waitTimeForHighCharge, ringOneLEDPin);
  jumpRingOne();
  delay(100);
  chargeCapacitor(waitTimeForLowCharge, ringTwoLEDPin);
  jumpRingTwo();

  jumpThirdRing();

}


void loop() {

}

void chargeCapacitor(int delayTime, int LEDNumber) {
  digitalWrite(chargeRelayPin, HIGH); //circuit is opened by default therefore write to HIGH will close loop
  digitalWrite(LEDNumber, HIGH);
  delay(delayTime);
  digitalWrite(chargeRelayPin, LOW);

  for (int index = 0; index <= 10; index++) {
    digitalWrite(LEDNumber, LOW);
    delay(blinkDelayForLED);
    digitalWrite(LEDNumber, HIGH);
    delay(blinkDelayForLED);
  }
  digitalWrite(LEDNumber, LOW);
}

void jumpRingOne() { // write pin to HIGH which allowed power to go through to move ring

  digitalWrite(ringOneRelayPin, HIGH);
  delay(waitTimeForRingJump);
  digitalWrite(ringOneRelayPin, LOW);
}

void jumpRingTwo() {
  digitalWrite(ringTwoRelayPin, HIGH);
  delay(waitTimeForRingJump);
  digitalWrite(ringTwoRelayPin, LOW);
}

void jumpThirdRing() {

  digitalWrite(ringThreeLEDPin, HIGH);
  delay(waitTimeForHighCharge);

  for (int index = 0; index <= 10; index++) {
    digitalWrite(ringThreeLEDPin, LOW);
    delay(blinkDelayForLED);
    digitalWrite(ringThreeLEDPin, HIGH);
    delay(blinkDelayForLED);
  }
  digitalWrite(ringThreeLEDPin, LOW);
}

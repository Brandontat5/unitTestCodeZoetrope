const int mintSensorPin = 2; // changed to 2 because it is usable for interrupt also make sure to use a digital pin
volatile int mintCount = 0; // start this at zero in order to count
volatile byte state = LOW; // idk what this does

void setup() {

  Serial.begin(9600);
  pinMode(mintSensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(mintSensorPin), incrementMintCount, FALLING); // (maps pin to correct interrupt pin, calls ISR function, when to do it [HIGH TO LOW])
}

void loop() {

  int mintSensorRead = digitalRead(mintSensorPin);

  if (mintSensorRead) {
    Serial.println("All clear");
    Serial.println(mintSensorRead);
  }
  else
  {
    Serial.println("Blocked");
    Serial.println(mintSensorRead);
  }
  delay(500);

  Serial.print("Mint count: ");
  Serial.println(mintCount);
  delay(500);
}

void incrementMintCount() {

  mintCount++;

}

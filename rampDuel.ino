// variables

bool leftSide = true;
const byte LEFT_SENSOR_PIN = A0;
const byte RIGHT_SENSOR_PIN = A1;
const byte LEFT_PISTON_PIN = 10;
const byte RIGHT_PISTON_PIN = 9;
int score = 0;

// set up

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_SENSOR_PIN, INPUT_PULLUP); // init sensors and pneumatics
  pinMode(RIGHT_SENSOR_PIN, INPUT_PULLUP);
  pinMode(LEFT_PISTON_PIN, OUTPUT);
  pinMode(RIGHT_PISTON_PIN, OUTPUT);
}


void loop() {
  if (leftSide == true && digitalRead(RIGHT_SENSOR_PIN) == 0) {
    score++;
    leftSide = false;
  }
  else if (leftSide == false && digitalRead(LEFT_SENSOR_PIN) == 0) {
    score++;
    leftSide = true;
  }
  Serial.println(score);

  delay(10);
}

void fireLeftPiston() {
  digitalWrite(LEFT_SENSOR_PIN, HIGH);
  delay(200);
  digitalWrite(LEFT_SENSOR_PIN, LOW);
}

void fireRightPiston() {
  digitalWrite(RIGHT_PISTON_PIN, HIGH);
  delay(200);
  digitalWrite(RIGHT_PISTON_PIN, LOW);
}

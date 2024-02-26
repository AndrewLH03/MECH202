const int motorRightPin = 2;          // Motor 1 Pin
const int motorLeftPin = 3;           // Motor 2 Pin
const int motorRightSpeedPin = 6;     // Motor 1 Speed Pin
const int motorLeftSpeedPin = 5;      // Motor 2 Speed Pin
const int potRightPin = A3;           // Potentiometer 1 Pin (Left)
const int potLeftPin = A1;            // Potentiometer 2 Pin (Right)

int pwmValueRight;                     // PWM value for Motor 1
int pwmValueLeft;                      // PWM value for Motor 2

void setup() {
  pinMode(motorRightPin, OUTPUT);      // Motor 1 control pin
  pinMode(motorLeftPin, OUTPUT);       // Motor 2 control pin
  pinMode(motorRightSpeedPin, OUTPUT);// Motor 1 speed control pin
  pinMode(motorLeftSpeedPin, OUTPUT); // Motor 2 speed control pin
  pinMode(potRightPin, INPUT);         // Potentiometer 1 pin
  pinMode(potLeftPin, INPUT);          // Potentiometer 2 pin
}

void loop() {
  int potValueRight = analogRead(potRightPin);     // Read potentiometer 1 value
  int potValueLeft = analogRead(potLeftPin);       // Read potentiometer 2 value

  // Map potentiometer values to PWM values
  pwmValueRight = map(potValueRight, 0, 1023, -255, 255);
  pwmValueLeft = map(potValueLeft, 0, 1023, -255, 255);

  // Adjust PWM values around the middle to stop the motors
  if (abs(pwmValueRight) < 20) {
    pwmValueRight = 0;
  }
  if (abs(pwmValueLeft) < 20) {
    pwmValueLeft = 0;
  }

  // Control Motor 1 (Right)
  if (pwmValueRight > 0) {
    digitalWrite(motorRightPin, HIGH);       // Turn Motor 1 on forward
    analogWrite(motorRightSpeedPin, pwmValueRight); // Set Motor 1 speed
  } else {
    digitalWrite(motorRightPin, LOW);        // Turn Motor 1 off backward
    analogWrite(motorRightSpeedPin, -pwmValueRight); // Set Motor 1 speed
  }

  // Control Motor 2 (Left)
  if (pwmValueLeft > 0) {
    digitalWrite(motorLeftPin, HIGH);        // Turn Motor 2 on forward
    analogWrite(motorLeftSpeedPin, pwmValueLeft); // Set Motor 2 speed
  } else {
    digitalWrite(motorLeftPin, LOW);         // Turn Motor 2 off backward
    analogWrite(motorLeftSpeedPin, -pwmValueLeft); // Set Motor 2 speed
  }

  delay(100); // Delay for stability
}
const int motorRight1Pin = 2;          // Motor Right1 Pin
const int motorLeft1Pin = 3;           // Motor Left1 Pin
const int motorRight2Pin = 7;          // Motor Right2 Pin
const int motorLeft2Pin = 4;           // Motor Left2 Pin
const int motorRightSpeedPin = 6;     // Motor 1 Speed Pin
const int motorLeftSpeedPin = 5;      // Motor 2 Speed Pin
const int potRightPin = A3;           // Potentiometer 1 Pin (Left)
const int potLeftPin = A1;            // Potentiometer 2 Pin (Right)

int pwmValueRight;                     // PWM value for Right Motor
int pwmValueLeft;                      // PWM value for Left Motor

void setup() 
{
  Serial.begin(9600);

  pinMode(motorRight1Pin, OUTPUT);      // Motor Right1 control pin
  pinMode(motorLeft1Pin, OUTPUT);       // Motor Left1 control pin
  pinMode(motorRight2Pin, OUTPUT);      // Motor Right2 control pin
  pinMode(motorLeft2Pin, OUTPUT);       // Motor Left2 control pin
  pinMode(motorRightSpeedPin, OUTPUT);  // Motor Right speed control pin
  pinMode(motorLeftSpeedPin, OUTPUT);   // Motor Left speed control pin

  pinMode(potRightPin, INPUT);          // Potentiometer 1 pin
  pinMode(potLeftPin, INPUT);           // Potentiometer 2 pin
}

void loop() 
{
  int pwmValueRight = analogRead(potRightPin);     // Read potentiometer 1 value
  int pwmValueLeft = analogRead(potLeftPin);       // Read potentiometer 2 value

  Serial.print("Right Potentiometer Before:");
  Serial.println(pwmValueRight);
  Serial.print("Left Potentiometer Before:");
  Serial.println(pwmValueLeft);
  Serial.println();

  // Map potentiometer values to PWM values
  pwmValueRight = map(pwmValueRight, 0, 1023, 0, 255);
  pwmValueLeft = map(pwmValueLeft, 0, 1023, 0, 255);

  // Adjust PWM values around the middle to stop the motors
  if ((pwmValueRight <= 148) && (pwmValueRight >= 108))
  {
    pwmValueRight = 0;
  }
  if ((pwmValueLeft <= 148) && (pwmValueLeft >= 108))
  {
    pwmValueLeft = 0;
  }

  // Control Motor 1 (Right)
  if (pwmValueRight > 148) 
  {
    digitalWrite(motorRight1Pin, HIGH);       // Turn Right Motor on forward
    digitalWrite(motorRight2Pin, LOW);
    analogWrite(motorRightSpeedPin, (pwmValueRight - 148) * (255 / 148)); // Set Right Motor speed
  } else if(pwmValueRight < 108)
  {
    digitalWrite(motorRight1Pin, LOW);        // Turn Right Motor backward
    digitalWrite(motorRight2Pin, HIGH);        
    analogWrite(motorRightSpeedPin, (pwmValueRight - 108) * (255 / 108)); // Set Right Motor Speed
  } else
  {
    digitalWrite(motorRight1Pin, LOW);
    digitalWrite(motorRight2Pin, LOW);
  }

  // Control Motor 2 (Left)
  if (pwmValueLeft > 148) 
  {
    digitalWrite(motorLeft1Pin, HIGH);        // Turn Left Motor on forward
    digitalWrite(motorLeft2Pin, LOW);
    analogWrite(motorLeftSpeedPin, (pwmValueLeft - 148) * (255 / 148)); // Set Left Motor Speed
  } else if (pwmValueLeft < 108)
  {
    digitalWrite(motorLeft1Pin, LOW);         // Turn Left Motor off backward
    digitalWrite(motorLeft2Pin, HIGH);
    analogWrite(motorLeftSpeedPin, (pwmValueLeft - 108) * (255 / 108)); // Set Left Motor speed
  } else
  {
    digitalWrite(motorLeft1Pin, LOW);
    digitalWrite(motorLeft2Pin, LOW);
  }

  Serial.print("Right Potentiometer After:");
  Serial.println(pwmValueRight);
  Serial.print("Left Potentiometer After:");
  Serial.println(pwmValueLeft);
  Serial.println();
  
  delay(300); // Delay for stability
}
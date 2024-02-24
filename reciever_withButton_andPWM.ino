#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(2, 10);  // CE, CSN
const int motor1Pin = 2;          //Motor 1 (Left) Control Pin
const int motor2Pin = 3;          //Motor 2 (Right) Control Pin
const int motor1SpeedPin = A4;    //Motor 1 (Left) Speed Pin
const int motor2SpeedPin = A5;    //Motor 2 (Right) Speed Pin

const int trigPin = 9;            //Supersonic Pins
const int echoPin = 10;

struct DataPacket {
  //Declaring Data variables
  int pwmValue1;
  int pwmValue2;
  int choochooPressed;
};

DataPacket data;

void setup() {
  //Declaring outputs
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(motor1SpeedPin, OUTPUT);
  pinMode(motor2SpeedPin, OUTPUT);

  //Initializing Supersonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  radio.begin();
  radio.setChannel(63);
  radio.openReadingPipe(0,0xA1A1A1A1A1LL);
  radio.startListening();
  Serial.begin(9600);
}

void loop() {
  if (radio.available()) 
  {
    //Read in data from radio and output true or false for buttonpush
    radio.read(&data, sizeof(data));

    //Sets motor 1 speed based on switch position
    digitalWrite(motor1, HIGH);
    analogWrite(motor1SpeedPin, pwmValue1)

    //Sets motor 2 speed based on switch position
    digitalWrite(motor2, HIGH);
    analogWrite(motor2SpeedPin, pwmValue2)

    if(data.choochooPressed)      //If button is pressed to activate the choo choo mechanism
    {
      digitalWrite(ChooChooMotor, HIGH);    //Turn on motor to run choo choo
      
      do                                    //Do While loop to keep taking measurements from supersonic until latching
      {
        digitalWrite(trigPin, HIGH);        //Take in info
        delayMicroseconds(10);              //Continue taking in info
        digitalWrite(trigPin, LOW);         //Stop taking in info
        duration = pulseIn(echoPin, HIGH);  //Find time until echoPin reads HIGH
      } while(duration < revTime)

      digitalWrite(ChooChooMotor, LOW);     //Turn off choo choo mechanism
    }
  } 

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8);  // CE, CSN
const int choochooPin = 3;  //Flipper mechanism
const int pot1Pin = A3;     //Potentiometer 1 (Left)
const int pot2Pin = A1;     //Potentiometer 2 (Right)

struct DataPacket {
  //Declaring Data variables
  int pwmValue1;
  int pwmValue2;
  int choochooPressed;
};

DataPacket data;

void setup() {
  pinMode(pot1Pin, INPUT);          //Declaring inputs
  pinMode(pot2Pin, INPUT);
  pinMode(buttonPin, INPUT);

  radio.begin();                    //Starting radio
  radio.setChannel(5);
  radio.openWritingPipe(0xA1A1A1A1A1LL);
  radio.stopListening();
  Serial.begin(9600);
}

void loop() {

  data.choochooPressed = digitalRead(choochooPin);         //Read if choo choo button is pressed
  data.pwmValue1 = analogRead(pot1Pin);                    //Read potentiometer 1 value in
  data.pwmValue2 = analogRead(pot2Pin);                    //Read potentiometer 2 value in

  data.pwmValue = map(data.pwmValue1, 0, 450, 255, 0);     //If potentiometer value is slightly below half, go reverse
  data.pwmValue = map(data.pwmValue1, 0, 573, 0, 255);     //If potentiometer value is slightly above half, go forward
  
  data.pwmValue = map(data.pwmValue2, 0, 450, 255, 0);     //If potentiometer value is slightly below half, go reverse
  data.pwmValue = map(data.pwmValue2, 0, 573, 0, 255);     //If potentiometer value is slightly above half, go forward
  
  radio.write(&data, sizeof(data));                        //Send data

  delay(100);                                              // Simple debounce - may need to adjust timing or implement a more robust debounce method
}

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8);  // CE, CSN
const int buttonPin = A2;  // the number of the pushbutton pin
//const int potPin = A0;  // Potentiometer connected to A0

struct DataPacket {
  int pwmValue;
  bool isButtonPressed;
};

DataPacket data;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  //pinMode(potPin, INPUT);
  radio.begin();
  radio.setChannel(46);
  radio.openWritingPipe(0xA1A1A1A1A1LL);
  radio.stopListening();
  Serial.begin(9600);
}

void loop() {
  data.pwmValue = digitalRead(buttonPin);
 // data.pwmValue = map(analogRead(potPin), 0, 1023, 0, 255);  // Read potentiometer value and map to range 0-255

  //Send data
  radio.write(&data, sizeof(data));

  if (data.pwmValue) {
    Serial.println("Button is pressed - Message sent");
  } else {
    Serial.println("Button is NOT pressed - Message sent");
  }
  delay(300);  // Simple debounce - may need to adjust timing or implement a more robust debounce method
}

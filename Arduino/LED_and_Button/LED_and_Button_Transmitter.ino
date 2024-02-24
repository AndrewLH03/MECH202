#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(2, 10);  // CE, CSN
const int buttonPin = 5;  // the number of the pushbutton pin
double testVoltRF;

struct DataPacket {
  bool isButtonPressed;
  
};

DataPacket data;

void setup() {
  pinMode(buttonPin, INPUT);
  radio.begin();
  radio.setChannel(63);
  radio.openWritingPipe(0xA1A1A1A1A1LL);
  radio.stopListening();
  Serial.begin(9600);
}

void loop() {
  //Read in voltage as HIGH or LOW from button
  data.isButtonPressed = digitalRead(buttonPin); 
  Serial.println(data.isButtonPressed);

  //Read in voltage going to RF24 (/ 1024 * 5 = 10 bit reading at 5 volt maximum)
  testVoltRF = analogRead(A2);
  Serial.println(testVoltRF / 1024 * 5);

  //If voltage is read in as HIGH, output button pressed
  if (data.isButtonPressed) {
    Serial.println("Button is pressed");
  } else {
    Serial.println("Button is NOT pressed");
  }

  // Send data and check if sent
  bool transmissionSuccess = radio.write(&data, sizeof(data));

  //If transmission sent succesfully, output success
  if (transmissionSuccess) {
    Serial.println("Transmission successful \n");
  } else {
    Serial.println("Transmission failed \n");
  }

  delay(100);  // Simple debounce - may need to adjust timing or implement a more robust debounce method
}
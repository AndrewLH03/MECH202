#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8);      // CE, CSN
const int ledPin = 3;  // LED connected to pin 3 (PWM capable)

struct DataPacket {
  int pwmValue;
  // bool isButtonPressed;
};

DataPacket data;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // Ensure LED is off initially
  radio.begin();
  radio.setChannel(3);
  radio.openReadingPipe(0, 0xA1A1A1A1A1LL);
  radio.startListening();
  Serial.begin(9600);
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    if (data.pwmValue == 0) {
      digitalWrite(ledPin, HIGH);
      Serial.println("Writing LED High");
    }
    else {
      digitalWrite(ledPin, LOW);
      Serial.println("Writing LED Low");
    };
    delay(100);
  }
  else
  {
    Serial.println("No Radio");
  };
}
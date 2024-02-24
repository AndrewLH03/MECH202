#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(2, 10);  // CE, CSN
const int ledPin = 3;  // LED connected to pin 3 (PWM capable)
double testVoltRF;

struct DataPacket {
  bool isButtonPressed;
};

DataPacket data;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // Ensure LED is off initially
  radio.begin();
  radio.setChannel(63);
  radio.openReadingPipe(0,0xA1A1A1A1A1LL);
  radio.startListening();
  Serial.begin(9600);
  
  data.isButtonPressed = 1;
}

void loop() {
  //Read in voltage going to RF24 (/ 1024 * 5 = 10 bit reading at 5 volt maximum)
    testVoltRF = analogRead(A2);
    Serial.println(testVoltRF / 1024 * 5);

  if (radio.available()) {
    //Read in data from radio and output true or false for buttonpush
    radio.read(&data, sizeof(data));
    Serial.println(data.isButtonPressed);

    if (data.isButtonPressed) 
    {
      // If button is pressed, set LED brightness
      digitalWrite(ledPin, HIGH);
      Serial.print("Button is pressed\n");
    } else if(!data.isButtonPressed)
    {
      // If button is not pressed, turn off LED
      digitalWrite(ledPin, LOW);
      Serial.println("Button is not Pressed\n");
    }
    else
    {
      //Catch all
      Serial.println("No Value\n");
    }
  }
  else
  {
    Serial.println("No radio available\n");
  }
}

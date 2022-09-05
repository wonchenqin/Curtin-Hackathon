/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8); // CE, CSN

uint8_t address[][6] = {"send", "reci"};

int readval;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address[1]);
  radio.setPayloadSize(sizeof(int));
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  Serial.println("initialising receiver");
}

void loop() {
  if (radio.available()) {
    Serial.println("receiving line:");
    radio.read(&readval, sizeof(int));
    Serial.println(readval);
  }
  else {
    // Serial.println("radio not available");
  }
  delay(20);
}

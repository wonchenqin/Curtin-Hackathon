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

RF24 radio(A4, A5); // CE, CSN

uint8_t address[][6] = {"send", "reci"};

int readval[5];
// int readval;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address[1]);
  radio.setPayloadSize(5 * sizeof(int));
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  Serial.println("initialising receiver");
}

void loop() {
  if (radio.available()) {
  radio.read(&readval, 5 * sizeof(int));
  Serial.print(readval[0]);
  Serial.print(" ");
  Serial.print(readval[1]);
  Serial.print(" ");
  Serial.print(readval[2]);
  Serial.print(" ");
  Serial.print(readval[3]);
  Serial.print(" ");
  Serial.print(readval[4]);
  Serial.println();
  }
  else {
    // Serial.println("radio not available");
  }
  delay(20);
}

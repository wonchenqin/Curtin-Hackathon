#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define TX_DELAY 10
RF24 radio(7, 8); // CE, CSN

uint8_t address[][6] = {"send", "reci"};

int writeval = 69;

void setup() {
  Serial.begin(19200);
  radio.begin();
  radio.openWritingPipe(address[1]);
  radio.setPayloadSize(sizeof(int));
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
  Serial.println("initialising transmitter");
}

void loop() {
  radio.write(&writeval, sizeof(writeval));
  // Serial.print("sending ");
  // Serial.println(writeval);
  writeval++;
  /*
  if(TX_DELAY) {
    delay(TX_DELAY);
  }
  */
  delay(10);
}

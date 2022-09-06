#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define TX_DELAY 10
RF24 radio(10, 9); // CE, CSN

uint8_t address[][6] = {"send", "reci"};

int writeval[5] = {0, 690, 420, 1337, 9001};
// int writeval = 69;

void setup() {
  Serial.begin(19200);
  radio.begin();
  radio.openWritingPipe(address[1]);
  radio.setPayloadSize(5 * sizeof(int));
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
  Serial.println("initialising transmitter");
}   

void loop() {
  radio.write(&writeval, 5 * sizeof(writeval));
  
  Serial.println("sending ");
  /*
  Serial.print(writeval[0]);
  Serial.print(writeval[1]);
  Serial.print(writeval[2]);
  Serial.print(writeval[3]);
  Serial.print(writeval[4]);
  Serial.println();
  */
  // writeval++;
  delay(TX_DELAY);
}

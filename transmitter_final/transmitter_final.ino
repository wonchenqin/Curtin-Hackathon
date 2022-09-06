// transmitter code
// sends a 5-integer array of data for each channel of freedom on the transmitter.
// array is as follows:
// { buttonstate1, vrx, vry, potentiometer, buttonstate2 }
// array[0] -> line follow button
// array[1] -> joystick x-axis
// array[2] -> joystick y-axis
// array[3] -> potentiometer
// array[4] -> lightshow actuator button


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define TX_DELAY 10

// pin definitions
//joystick
#define VRX     A1
#define VRY     A4
#define BUTTON1 2

//potentiometer
#define POT     A0

// pushbutton
#define BUTTON2 4

int xvalue = 0;
int yvalue = 0;
int buttonstate1 = 0;
int potentiometer = 0;
int buttonstate2 = 0;

// transceiver
RF24 radio(10, 9); // CE, CSN
uint8_t address[][6] = {"send", "reci"};

// transmission buffer
int writeval[5] = {0, 690, 420, 1337, 9001};

void setup() {
  Serial.begin(19200);

  // joystick setup
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(VRX, INPUT);
  pinMode(VRY,INPUT);

  // potentiometer setup
  pinMode(POT, INPUT);

  // statebutton setup
  pinMode(BUTTON2, INPUT_PULLUP);

  // transceiver setup
  radio.begin();
  radio.openWritingPipe(address[1]);
  radio.setPayloadSize(5 * sizeof(int));
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
  Serial.println("initialising transmitter");
}   

void loop() {
  // read joystick values
  xvalue = analogRead(VRX);
  yvalue = analogRead(VRY);
  buttonstate1 = digitalRead(BUTTON1);
  potentiometer = analogRead(POT);
  buttonstate2 = digitalRead(BUTTON2);

  writeval[0] = buttonstate1;
  writeval[1] = xvalue;
  writeval[2] = yvalue;
  writeval[3] = potentiometer;
  writeval[4] = buttonstate2;
  
  radio.write(&writeval, 5 * sizeof(writeval));
  
  Serial.println("sending ");
  Serial.print(writeval[0]);
  Serial.print(" ");
  Serial.print(writeval[1]);
  Serial.print(" ");
  Serial.print(writeval[2]);
  Serial.print(" ");
  Serial.print(writeval[3]);
  Serial.print(" ");
  Serial.print(writeval[4]);
  Serial.println();
  // writeval++;
  delay(TX_DELAY);
}

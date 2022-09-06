#include <Servo.h>

// MOTOR PINS
#define ENABLE1 10
#define ENABLE2 6
#define APIN    9
#define BPIN    8
#define CPIN    7
#define DPIN    5
#define DEADZONE 0.4
#define MAXSPEED 255 //from 0-255

// IR SENSOR PINS
#define IR_LEFT     2
#define IR_MID      1
#define IR_RIGHT    4

// ULTRASONIC PINS
//#define ECHO_PIN        12
//#define TRIG_PIN        13

// SERVO
#define SERVO_PIN   3
Servo sam;

//LED CODE
#define LEDPIN A0
int LEDCODE[16] = {0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1};
long int ii;
int counter;
int toggle = 1;
int on = 0;

//RADIO CODE
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(A4, A5); // CE, CSN
uint8_t address[][6] = {"send", "reci"};
int readval;

void setup() {
  Serial.begin(9600);

  // IR SENSOR PINS
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_MID, INPUT);
  pinMode(IR_RIGHT, INPUT);

  // MOTOR PINS
  pinMode(ENABLE1, OUTPUT);
  pinMode(ENABLE2, OUTPUT);
  pinMode(APIN, OUTPUT);
  pinMode(BPIN, OUTPUT);
  pinMode(CPIN, OUTPUT);
  pinMode(DPIN, OUTPUT);

  // ULTRASONIC PINS
  //pinMode(TRIG_PIN, OUTPUT);
  //pinMode(ECHO_PIN, INPUT);

  // SERVO SETUP
  sam.attach(SERVO_PIN);

  // LED CODE


  // RADIO CODE
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address[1]);
  radio.setPayloadSize(5 * sizeof(int));
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  Serial.println("initialising receiver");
  
}

void loop() {
  // put your main code here, to run repeatedly:

  int comm[5] = {0, 512, 512, 0, 0};
  readComm(comm);
  int state = comm[0];
  switch (state) {
    case (0):
      autonomous();
      //motorDrive(1,1);

      break;

    case (1):
      teleop(comm[1], comm[2], comm[3], comm[4]);// Xval,Yval,Servo,LEDbutton
      break;

    default:
      break;
  }

  //digitalWrite(LEDPIN, HIGH);
  //sam.write(0);
  ledCode();
}

void autonomous() {
  colourFollowing();
  sam.write(0);
  //duration = get_pulse_duration();
  //cm = ms_to_cm(duration);

}

void teleop(int xval, int yval, int servo1, int ledButton) {


  int left = map(xval, 0, -1, 1024, 1);
  int right = map(yval, 0, -1, 1024, 1);
  motorDrive(left, right);

  servo1 = map(servo1, 0, 1024,0,60);
  Serial.println(servo1);
  sam.write(servo1);

  if (ledButton == 1)
  {
    on = 1;
    Serial.println("change led");
  }
  
  
}

void colourFollowing() {
  bool left = digitalRead(IR_LEFT);
  bool mid = digitalRead(IR_MID);
  bool right = digitalRead(IR_RIGHT);


  if ((!left && !mid && !right) or (left && mid && right)) {          // LLL or HHH
    motorDrive(1, 1);
    //forward();
  } else if (!left && !mid && right) {                                // LLH (left corner)
    motorDrive(-1, 0);
  } else if (!left && mid && right) {                                 // LHH
    motorDrive(-1, 1);
    //right();
  } else if (left && !mid && !right) {                                // HLL (right corner)
    motorDrive(0, -1);
  } else if (left && mid && !right) {                                 // HHL
    motorDrive(1, -1);
    //left();
  } else if (!left && mid && !right) {                                // LHL (weird)
    motorDrive(1, 1);
    //forward();
  } else if (left && !mid && right) {                                 // HLH (desired)
    motorDrive(1, 1);
    //forward();
  }
}

void motorDrive(float left, float right) {
  int L_speed = 0;
  int R_speed = 0;

  if (left > 0) {
    digitalWrite(APIN, HIGH);
    digitalWrite(BPIN, LOW);
  }
  else // left < 0
  {
    digitalWrite(APIN, LOW);
    digitalWrite(BPIN, HIGH);
  }

  if (right > 0) {
    digitalWrite(CPIN, HIGH);
    digitalWrite(DPIN, LOW);
  }
  else // right < 0
  {
    digitalWrite(CPIN, LOW);
    digitalWrite(DPIN, HIGH);
  }

  L_speed = (int)MAXSPEED * abs(left);
  R_speed = (int)MAXSPEED * abs(right);


  if (abs(left) < DEADZONE) {
    L_speed = 0;
  }
  if (abs(right) < DEADZONE) {
    R_speed = 0;
  }
  analogWrite(ENABLE1, L_speed);
  analogWrite(ENABLE2, R_speed);
}

void readComm(int (& buff) [5]) {
  while (!radio.available()) {
     Serial.println("waiting:");
  } 
  Serial.println("receiving line:");
  radio.read(&buff,5*sizeof(int));
  Serial.println(buff[0]);
  Serial.println(buff[1]);
  Serial.println(buff[2]);
  Serial.println(buff[3]);
  Serial.println(buff[4]);
  delay(20);
  
}

void ledCode() {


    if (LEDCODE[ii%16] == 1)
    {
      digitalWrite(LEDPIN, HIGH);
    }
    else
    {
      digitalWrite(LEDPIN, LOW);
    }
    if (millis() > counter + 60)
    {
      ii = ii + 1;
      counter = millis();
    }

    if(ii >= 10000){
      ii =0;
    }

}



/*
  long get_pulse_duration() {                 // Sends a pulse from the trigger, and calculates how long it takes to return
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  return pulseIn(ECHO_PIN, HIGH);
  }

  long ms_to_cm(long microseconds) {          // d = v * t
  double speed_sound = 0.0343;            // in centimetres per microseconds
  return microseconds * speed_sound / 2;  // divide by 2 to account for pulse travelling forward and backward
  }
*/

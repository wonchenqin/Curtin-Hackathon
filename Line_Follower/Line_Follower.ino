// MOTOR PINS
#define ENABLE1 10
#define ENABLE2 11
#define APIN    9
#define BPIN    8
#define CPIN    7
#define DPIN    6
#define DEADZONE 0.1



#define IR_LEFT     7
#define IR_MID      6
#define IR_RIGHT    5

void setup() {
  Serial.begin(9600);
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

}

void loop() {
  // put your main code here, to run repeatedly:

  for 
  motorDrive(1,1);

}

void readInfrared() {
  bool left = digitalRead(IR_LEFT);
  bool mid = digitalRead(IR_MID);
  bool right = digitalRead(IR_RIGHT);


  if ((!left && !mid && !right) or (left && mid && right)) {            // LLL or HHH
    motorDrive(1, 1);
    //forward();
  } else if ((!left && !mid && right) or (!left && mid && right)) {     // LLH or LHH
    motorDrive(1, -1);
    //right();
  } else if ((left && !mid && !right) or (left && mid && !right)) {     // HLL or HHL
    motorDrive(-1, 1);
    //left();
  } else if (!left && mid && !right) {                                // LHL (desired)
    motorDrive(1, 1);
    //forward();
  } else if (left && !mid && right) {                                 // HLH (weird)
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
    digitalWrite(CPIN, HIGH);
    digitalWrite(DPIN, LOW);
  }

 L_speed = (int)255 * abs(left);
 R_speed = (int)255 * abs(right);


if (abs(left) < DEADZONE) {
  L_speed = 0;
}
if (abs(right) < DEADZONE) {
  R_speed = 0;
}
analogWrite(ENABLE1, L_speed);
analogWrite(ENABLE2, R_speed);

}

// MOTOR PINS
#define ENABLE1 10
#define ENABLE2 11
#define APIN    9
#define BPIN    8
#define CPIN    7
#define DPIN    6
#define DEADZONE 0.1

// IR SENSOR PINS
#define IR_LEFT     2
#define IR_MID      3
#define IR_RIGHT    4

// ULTRASONIC PINS
#define ECHO_PIN        12
#define TRIG_PIN        13

int duration, cm;

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
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  readInfrared();
  duration = get_pulse_duration();
  cm = ms_to_cm(duration);
}

void readInfrared() {
  bool left = digitalRead(IR_LEFT);
  bool mid = digitalRead(IR_MID);
  bool right = digitalRead(IR_RIGHT);


  if ((!left && !mid && !right) or (left && mid && right)) {          // LLL or HHH
    motorDrive(1, 1);
    //forward();
  } else if (!left && !mid && right) {                                // LLH (left corner)
    motorDrive(-1, 0.2);
  } else if (!left && mid && right) {                                 // LHH
    motorDrive(-1, 1);
    //right();
  } else if (left && !mid && !right) {                                // HLL (right corner)
    motorDrive(0.2, -1);
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

  L_speed = (int)100 * abs(left);
  R_speed = (int)100 * abs(right);


  if (abs(left) < DEADZONE) {
    L_speed = 0;
  }
  if (abs(right) < DEADZONE) {
    R_speed = 0;
  }
  analogWrite(ENABLE1, L_speed);
  analogWrite(ENABLE2, R_speed);
}

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

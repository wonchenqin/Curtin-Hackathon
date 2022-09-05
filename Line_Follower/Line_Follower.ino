#define IR_LEFT     7
#define IR_MID      6
#define IR_RIGHT    5

void setup() {
    Serial.begin(9600);
    pinMode(IR_LEFT, INPUT);
    pinMode(IR_MID, INPUT);
    pinMode(IR_RIGHT, INPUT);
}

void loop() {
    // put your main code here, to run repeatedly:

}

void readInfrared() {
    bool left = digitalRead(IR_LEFT);
    bool mid = digitalRead(IR_MID);
    bool right = digitalRead(IR_RIGHT);


    if (!left && !mid && !right) or (left && mid && right){             // LLL or HHH
        forward();
    } else if (!left && !mid && right) or (!left && mid && right) {     // LLH or LHH
        right();
    } else if (left && !mid && !right) or (left && mid && !right) {     // HLL or HHL
        left();
    } else if (!left && mid && !right) {                                // LHL (desired)
        forward(); 
    } else if (left && !mid && right) {                                 // HLH (weird)
        forward();
    }
}

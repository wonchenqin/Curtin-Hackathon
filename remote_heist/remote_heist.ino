//Poterntiometer

#include <Servo.h>

Servo servo;

int angle = 10;

//joystick
#define vrx A1
#define vry A4


int xvalue = 0;
int yvalue = 0;
const int button1 = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(A3, INPUT); //Set pins for digital and analog pins
  pinMode(A0, OUTPUT);
  Serial.begin(9600);

  servo.attach(A0);
  servo.write(angle);

   //joystick
  pinMode(button1, INPUT_PULLUP);
  pinMode(vrx, INPUT);
  pinMode(vrx,INPUT);
  Serial.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  int potValue;
  potValue = analogRead(A3);
  angle = (int)map(potValue, 0, 1023, 0, 180);
  servo.write(angle);
  //Serial.println(potValue);
  Serial.println(angle);

    //joystick
  int xvalue = analogRead(vrx);
int yvalue = analogRead(vry);
int buttonstate1 = digitalRead(button1);

//Serial.print (yvalue);
//Serial.println();

//forward
if (xvalue == 1023)
{
   Serial.print("forward \n");
  
  //delay(200);
}

//backward
if (xvalue == 0)
{
  Serial.print("backward \n");
  //delay(200);
}          

//left
if (yvalue == 0)
{
   Serial.print("left \n");
  //delay(200);
}

//right
if (yvalue == 1023)  
{
  Serial.print("right \n");
  //delay(200);
}

//pushbutton(joystick)
if (buttonstate1 == LOW)
{
   Serial.print("pushbutton \n");
   delay(200);
}
  

}

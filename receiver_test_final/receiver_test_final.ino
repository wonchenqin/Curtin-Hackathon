/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
long int ii;
int counter;

void setup(){
    pinMode(LEDPIN, OUTPUT);
  ii = 0;
  counter = millis();
}

void loop() {

  ledCode();
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
    if (millis() > counter + 100)
    {
      ii = ii + 1;
      counter = millis();
    }

    if(ii >= 10000){
      ii =0;
    }

}

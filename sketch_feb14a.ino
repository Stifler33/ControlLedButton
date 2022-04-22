#include <Arduino_AVRSTL.h>
bool flag = false;
class Control
{
  int pinLed;
  int brigthness;
  int pinButton;
  int modeBacklight = 0;
 public:
  Control(int _pinLed, int _pinButton, int _bright = 0): pinLed(_pinLed), brigthness(_bright), pinButton(_pinButton)
  {
   pinMode(pinButton, INPUT);
  }
  void setBrigth(int brigth){
    brigthness = brigth;
    analogWrite(pinLed, brigthness);
  }
  void setSmooBrigth(int brigth, int speedSmoo = 30){
    if ((brigth < 0 || brigth > 255) || (brigth == brigthness)){
      return;
    }
    while(brigthness != brigth){
      delay(speedSmoo);
      brigth > brigthness ? brigthness++ : brigthness--;
      analogWrite(pinLed, brigthness);
    }
  }
  void selectMode(long oldMill = 0){
    while (!digitalRead(pinButton)){
      if (millis() - oldMill >= 250){       
        modeBacklight = 0;
        setSmooBrigth(brigthness + 100, 5);
        setSmooBrigth(0);
        return;
      }
    }
    if (modeBacklight >= 2){
      modeBacklight = 0;
      Serial.println(modeBacklight);
      //return;
    }else modeBacklight++;
    Serial.println(modeBacklight);
      if (modeBacklight == 0) setSmooBrigth(0);
      if (modeBacklight == 1) setSmooBrigth(150, 10);
      if (modeBacklight == 2) setSmooBrigth(20, 20);
    //delay(50);
  }
};
void setup() {
  Serial.begin(9600);
  Serial.print("Hello !\n");
}
Control myLed(11, 10);
int firstMillis = 0;
int count = 0;
void loop() {
  long count1 = millis();
  if (!digitalRead(10) && !flag){
    myLed.selectMode(count1);
    flag = true;
  }
  if (digitalRead(10) && flag){
    flag = false;
  }
}

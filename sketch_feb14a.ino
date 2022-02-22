#include <Arduino_AVRSTL.h>

class Control
{
  int pinLed;
  int brigthness;
  int pinButton;
  int modeBacklight = 0;
 public:
  Control(int _pinLed, int _pinButton, int _bright = 0): pinLed(_pinLed), brigthness(_bright), pinButton(_pinButton)
  {
   //pinMode(pinLed, INPUT);
   pinMode(pinButton, INPUT);
  }
  void setBrigth(int brigth){
    brigthness = brigth;
    analogWrite(pinLed, brigthness);
  }
  void setSmooBrigth(int brigth, int speedSmoo = 30){
    if ((brigth < 0 || brigth > 255) && (brigth == brigthness)){
      return;
    }
    while(brigthness != brigth){
      delay(speedSmoo);
      brigth > brigthness ? brigthness++ : brigthness--;
      analogWrite(pinLed, brigthness);
    }
  }
  void selectMode(){
    if (modeBacklight >= 2){
      modeBacklight = 0;
      Serial.println(modeBacklight);
      //return;
    }else modeBacklight++;
    Serial.println(modeBacklight);
    while (!digitalRead(pinButton)){
      if (modeBacklight == 0) setSmooBrigth(0);
      if (modeBacklight == 1) setSmooBrigth(150, 10);
      if (modeBacklight == 2) setSmooBrigth(20, 20);
      }
    delay(50);
  }
};
void setup() {
  Serial.begin(9600);
  Serial.print("Hello !\n");
}
Control myLed(11, 10);
int firstMillis = 0;
bool flag = false;
std::vector<int> myVec(20);
int count = 0;
void loop() {
    if (!digitalRead(10)){
      myLed.selectMode();
    }
  
 /*
  if (!digitalRead(10) && !flag){
    firstMillis = millis();
    flag = true;
  }
  if (digitalRead(10) && flag){
    int result = millis() - firstMillis;
    myVec[count++] = result;
    if (count > (myVec.size() - 1)) count = 0;
    int average = 0;
    for (auto i : myVec){
      average += i;
    }
    average /= myVec.size();
    Serial.println(average);
    //Serial.println(result);
    flag = false;
  }
  */
  //myLed.setBrigth(50);
  // put your main code here, to run repeatedly:
  
}

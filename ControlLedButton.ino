//#include <Arduino_AVRSTL.h>
bool flag = false;
class Control
{
  int pinLed;
  int brigthness;
  int pinButton;
  int pinSensor;
  int average = 64;
  int modeBacklight = 0;
  float k = 0.09;
  
 public:
  Control(int _pinLed, int _pinButton, int _pinSensor, int _bright = 0): pinLed(_pinLed), brigthness(_bright), pinButton(_pinButton), pinSensor(_pinSensor)
  {
   pinMode(pinButton, INPUT);
   pinMode(pinSensor, OUTPUT);
  }
  //устанавливаем яркость и записываем это значение и запоминаем его
  void setBrigth(int brigth){
    brigthness = brigth;
    analogWrite(pinLed, brigthness);
  }
  //функция для плавной регулировки яркости (значение яркости, скорость ее достижения)
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
  //переключение режимов
  void selectMode(long oldMill = 0){
    //если мы захотим плавно выключить свет
    while (!digitalRead(pinButton)){
      if (millis() - oldMill >= 250){       
        modeBacklight = 0;
        setSmooBrigth(brigthness + 100, 5);
        setSmooBrigth(0);
        return;
      }
    }
    if (modeBacklight >= 1){
      modeBacklight = 0;
    }else modeBacklight++;
      if (modeBacklight == 0) setSmooBrigth(0);// выключаем
      while (modeBacklight == 1 && digitalRead(pinButton)){//здесь висим в 1 режиме автоматической регулеровки яркости
        int valueLight = readSensor();
        int filterValueLight = map(valueLight, 300, 1023, 0, 150);
        if (filterValueLight <= 0){
          filterValueLight = 0;
        }
        setBrigth(filterValueLight);
      }
  }
  //считывание показаний с датчика с использованием фильтра.
  float readSensor(){
    float newVal = analogRead(pinSensor);
    static float filVal = 0;
    filVal += (newVal - filVal) * k;
    return filVal;
  }
  
};
void setup() {
  Serial.begin(9600);
  Serial.print("Hello !\n");
}
Control myLed(11, 10, 13);
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

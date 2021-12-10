#include <Arduino.h>

const int MOTOR_PIN = 11;
const int PIN_ANALOG_INPUT = 5;
const int th = 3; //しきい値

bool rainFlag = false;
bool moved = false;

void setup() {
  Serial.begin( 9600 );
  pinMode(MOTOR_PIN, OUTPUT);
}

void setRainState(float voltage) {
  rainFlag = voltage < th;
}

void setMoved(bool boolean) {
  moved = boolean;
}

void moveMotor(int time){         //モータをtimeミリ秒だけ動かす
  digitalWrite(MOTOR_PIN, HIGH);  //モータピンの出力をHIGH = 5Vにする
  delay(time);
  digitalWrite(MOTOR_PIN, LOW);   //モータピンの出力をLOW = 0Vにする
}

void print(float voltage) {
  setRainState(voltage);
  Serial.print("voltage:");
  Serial.println(voltage);
  Serial.print("rainFlag:");
  Serial.println( rainFlag );
  Serial.print("moved:");
  Serial.println( moved );
  Serial.println("");
}

void loop() {
  int input = analogRead( PIN_ANALOG_INPUT );
  float voltage = input * 5.0 / 1023.0; //アナログ値を電圧値へ変更
  setRainState(voltage);
  print(voltage);

  if(rainFlag && !moved){
    moveMotor(2000);
    setMoved(true);
  }

  if (!rainFlag) {
    setMoved(false);
  }

  delay( 1000 ); 
}

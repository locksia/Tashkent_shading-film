#include <Servo.h>
#include <Wire.h>
#include <AM2320.h>
#include <BH1750.h>

AM2320 am2320;
BH1750 LightSensor;
Servo sv1, sv2, sv3;

int motor[4] = {0, 0, 0, 1}; // motor 상태 배열 (0: 닫힘, 1: 열림)

void setup() {
  Serial.begin(9600);
  LightSensor.begin();  

  sv1.attach(9);
  sv2.attach(10);
  sv3.attach(11); 

}

void loop() {
  am2320.Read();
  Serial.print("Temp: ");
  Serial.println(am2320.t);
  Serial.print("Hum: ");
  Serial.println(am2320.h);
  int16_t lux = LightSensor.readLightLevel();
  Serial.print("Light: ");
  Serial.println(lux);

  Serial.print("motor[1] : ");
  if(motor[1] == 0){Serial.println(1);}
  else if(motor[1] == 1){Serial.println(0);}
  Serial.print("motor[2] : ");
  Serial.println(motor[2]);
  Serial.print("motor[3] : ");
  if(motor[3] == 0){Serial.println(1);}
  else if(motor[3] == 1){Serial.println(0);}
  Serial.println("--------------------------");
  delay(1000);

  if (lux < 100) {
    close(1);
    open(2);
    close(3);
  } else if (lux > 1500) {
    open(1);
    close(2);
    open(3);
  } else {
    close(1);
    close(2);
    open(3);//mung cheong lee
  }

  delay(500);
}

void mchar(int c, int move) {
  if (c == 1) {
    sv1.write(move);
    delay(2000);
    sv1.write(90); // 중립 위치
    delay(10);
  } else if (c == 2) {
    sv2.write(move);
    delay(2500);
    sv2.write(90);
    delay(10);
  } else if (c == 3) {
    sv3.write(move);
    delay(3400);
    sv3.write(90);
    delay(10);
  }
}

void open(int c) {
  if (motor[c] == 0) {
    mchar(c, 80); // 열린 위치
    motor[c] = 1; // 열림 상태로 변경
  }
}

void close(int c) {
  if (motor[c] == 1) {
    mchar(c, 104); // 닫힌 위치
    motor[c] = 0; // 닫힘 상태로 변경
  }
}

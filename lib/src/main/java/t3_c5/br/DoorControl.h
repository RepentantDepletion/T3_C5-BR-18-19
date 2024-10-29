#include <ESP32Servo.h>   // ignore red line
#include <stdio.h>
#include <string.h>
#include <jni.h>


// static const int servoPin = 13; // change servo pin based on what motions setup their 

Servo servo1;

void setupDoorControl() {

  Serial.begin(115200);
  servo1.attach(servoPin);
}

void open() {     // need to add feature that can read whether or not do
  for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {    // open
    servo1.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
}

void close(){
for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {    // close
    servo1.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
}
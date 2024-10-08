// package t3_c5.br;
/*
public class DoorControl {
    private String doorStatus;

    public DoorControl() {
        this.doorStatus = "closed"; // Default status
    }

    public String getDoorStatus() {
        return doorStatus;
    }

    public void openDoor() {
        this.doorStatus = "open";
        System.out.println("Door opened.");
    }

    public void closeDoor() {
        this.doorStatus = "closed";
        System.out.println("Door closed.");
    }
}
*/


#include <ESP32Servo.h>
#include <stdio.h>
#include <string.h>

// static const int servoPin = 13; // change servo pin based on what motions setup their 

Servo servo1;

void setup() {

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
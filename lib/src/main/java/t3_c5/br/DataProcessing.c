// DataProcessing.h
#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

#include "DoorControl.h"
#include "IRSensor.h"
#include "LightStatus.h"
#include "Main.h"
#include "SpeedManagement.h"
#include "UltrasonicSensor.h"
#include "SensorFeedback.h"

typedef struct {
    DoorControl doorManager;
    IRSensor irSensor;
    LightStatus lightStatus;
    Main main;
    SpeedManagement speedManager;
    UltrasonicSensor ultrasonicSensor;
    SensorFeedback sensorFeedback;
} DataProcessing;

void initDataProcessing(DataProcessing* dp);
void updateSensorFeedback(DataProcessing* dp);

#endif  // DATA_PROCESSING_H

// DataProcessing.c
#include "DataProcessing.h"

void initDataProcessing(DataProcessing* dp) {
    initDoorControl(&dp->doorManager);
    initIRSensor(&dp->irSensor);
    initLightStatus(&dp->lightStatus);
    initMain(&dp->main);
    initSpeedManagement(&dp->speedManager);
    initUltrasonicSensor(&dp->ultrasonicSensor);
    initSensorFeedback(&dp->sensorFeedback);
}

void updateSensorFeedback(DataProcessing* dp) {
    // Read sensor feedback from multiple sources
    char doorStatus[10];
    strcpy(doorStatus, getDoorStatus(&dp->doorManager));

    char irSensorStatus[10];
    strcpy(irSensorStatus, getIRSensorStatus(&dp->irSensor));

    char lightStatus[10];
    strcpy(lightStatus, getLightStatus(&dp->lightStatus));

    char mainStatus[10];
    strcpy(mainStatus, getMainStatus(&dp->main));

    float currentSpeed = getCurrentSpeed(&dp->speedManager);

    float ultrasonicDistance = getUltrasonicDistance(&dp->ultrasonicSensor);

    // Update the sensor feedback
    char sensorFeedback[100];
    sprintf(sensorFeedback, "Door: %s, IR Sensor: %s, Light: %s, Main: %s, Speed: %.2f cm/s, Ultrasonic: %.2f cm", doorStatus, irSensorStatus, lightStatus, mainStatus, currentSpeed, ultrasonicDistance);
    updateSensorStatus(&dp->sensorFeedback, sensorFeedback);
}

// DoorControl.h
#ifndef DOOR_CONTROL_H
#define DOOR_CONTROL_H

typedef struct {
    char doorStatus[10];
} DoorControl;

void initDoorControl(DoorControl* dc);
void closeDoor(DoorControl* dc);
const char* getDoorStatus(DoorControl* dc);

#endif  // DOOR_CONTROL_H

// DoorControl.c
#include "DoorControl.h"

void initDoorControl(DoorControl* dc) {
    strcpy(dc->doorStatus, "open");
}

void closeDoor(DoorControl* dc) {
    strcpy(dc->doorStatus, "closed");
}

const char* getDoorStatus(DoorControl* dc) {
    return dc->doorStatus;
}

// IRSensor.h
#ifndef IR_SENSOR_H
#define IR_SENSOR_H

typedef struct {
    char irSensorStatus[10];
} IRSensor;

void initIRSensor(IRSensor* ir);
void updateIRSensorStatus(IRSensor* ir, const char* status);
const char* getIRSensorStatus(IRSensor* ir);

#endif  // IR_SENSOR_H

// IRSensor.c
#include "IRSensor.h"

void initIRSensor(IRSensor* ir) {
    strcpy(ir->irSensorStatus, "unknown");
}

void updateIRSensorStatus(IRSensor* ir, const char* status) {
    strcpy(ir->irSensorStatus, status);
}

const char* getIRSensorStatus(IRSensor* ir) {
    return ir->irSensorStatus;
}

// LightStatus.h
#ifndef LIGHT_STATUS_H
#define LIGHT_STATUS_H

typedef struct {
    char lightStatus[10];
} LightStatus;

void initLightStatus(LightStatus* ls);
void updateLightStatus(LightStatus* ls, const char* status);
const char* getLightStatus(LightStatus* ls);

#endif  // LIGHT_STATUS_H

// LightStatus.c
#include "LightStatus.h"

void initLightStatus(LightStatus* ls) {
    strcpy(ls->lightStatus, "unknown");
}

void updateLightStatus(LightStatus* ls, const char* status) {
    strcpy(ls->lightStatus, status);
}

const char* getLightStatus(LightStatus* ls) {
    return ls->lightStatus;
}

// Main.h
#ifndef MAIN_H
#define MAIN_H

typedef struct {
    char mainStatus[10];
} Main;

void initMain(Main* m);
void updateMainStatus(Main* m, const char* status);
const char* getMainStatus(Main* m);

#endif  // MAIN_H

// Main.c
#include "Main.h"

void initMain(Main* m) {
    strcpy(m->mainStatus, "unknown");
}

void updateMainStatus(Main* m, const char*){
    
}
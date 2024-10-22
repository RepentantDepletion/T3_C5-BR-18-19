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

void updateMainStatus(Main* m, const char*

/*
#define PACKAGE t3_c5_br
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SpeedManagement.c"
#include "DoorControl.c"
#include "SensorFeedback.c"
#include "UltrasonicSensor.c"
#include "IRSensor.c"
#include "LightStatus.c"
#include "Main.c"
#include "DataProcessing.c"

// Define the structures for each component
typedef struct {
    int speed; // Speed value
} SpeedManagement;

typedef struct {
    int doorStatus; // Door status
    int lightStatus; // Light status
    int mainStatus; // Main status
} DoorControl;

typedef struct {
    char sensorFeedback[100]; // Sensor feedback message
} SensorFeedback;

typedef struct {
    int sensorStatus; // Sensor status
} UltrasonicSensor;

typedef struct {
    int sensorStatus; // Sensor status
} IRSensor;

typedef struct {
    int lightStatus; // Light status
} LightStatus;

typedef struct {
    int mainStatus; // Main status
} MainStatus;

// Define the functions for each component
void initSpeedManagement(SpeedManagement* speedManagement) {
    speedManagement->speed = 0; // Initialize speed to 0
}

void initDoorControl(DoorControl* doorControl) { // * = pointer
    doorControl->doorStatus = 0; // Initialize door status to 0
    doorControl->lightStatus = 0; // Initialize light status to 0
    doorControl->mainStatus = 0; // Initialize main status to 0
}

void initSensorFeedback(SensorFeedback* sensorFeedback) {
    strcpy(sensorFeedback->sensorFeedback, "No feedback"); // Initialize sensor feedback to "No feedback"
}

void initUltrasonicSensor(UltrasonicSensor* ultrasonicSensor) {
    ultrasonicSensor->sensorStatus = 0; // Initialize ultrasonic sensor status to 0
}

void initIRSensor(IRSensor* irSensor) {
    irSensor->sensorStatus = 0; // Initialize IR sensor status to 0
}

void initLightStatus(LightStatus* lightStatus) {
    lightStatus->lightStatus = 0; // Initialize light status to 0
}

void initMainStatus(MainStatus* mainStatus) {
    mainStatus->mainStatus = 0; // Initialize main status to 0
}

void updateSensorFeedback(SensorFeedback* sensorFeedback, int ultrasonicSensorStatus, int irSensorStatus) {
    // Update sensor feedback based on sensor statuses
    if (ultrasonicSensorStatus == 1 && irSensorStatus == 1) {
        strcpy(sensorFeedback->sensorFeedback, "Obstacle detected");
    } else {
        strcpy(sensorFeedback->sensorFeedback, "No obstacle detected");
    }
}

void getMainStatus(MainStatus* mainStatus) {
    mainStatus->mainStatus = 1; // Set main status to 1
}

void printStatus(DoorControl* doorControl, SensorFeedback* sensorFeedback, SpeedManagement* speedManagement, MainStatus* mainStatus) {
    // Print the status of each component
    printf("Door Control Status: %d\n", doorControl->doorStatus);
    printf("Light Status: %d\n", doorControl->lightStatus);
    printf("Main Status: %d\n", mainStatus->mainStatus);
    printf("Sensor Feedback: %s\n", sensorFeedback->sensorFeedback);
    printf("Speed Management: %d\n", speedManagement->speed);
}

int main() {
    // Initialize components
    DoorControl doorControl;
    SensorFeedback sensorFeedback;
    SpeedManagement speedManagement;
    MainStatus mainStatus;

    initDoorControl(&doorControl);
    initSensorFeedback(&sensorFeedback);
    initSpeedManagement(&speedManagement);
    initMainStatus(&mainStatus);

    // Update main status
    getMainStatus(&mainStatus);

    // Print status
    printStatus(&doorControl, &sensorFeedback, &speedManagement, &mainStatus);

    return 0;
}


/*
#include "SpeedManagement.c"
#include "DoorControl.c"
#include "SensorFeedback.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <jni.h>      // should be the library to allow a java class to call this class + the other c files


#define SERVER_PORT_DEFAULT 3018
#define SERVER_IP "10.20.30.1"
#define BUFFER_SIZE 1024

// Global Variables
int sockfd;
struct sockaddr_in server_addr, local_addr, client_addr;
socklen_t client_len = sizeof(client_addr);

// DataProcessing struct to hold all components
typedef struct {
    SpeedManagement speedManager;
    DoorControl doorManager;
    SensorFeedback sensorManager;
    char stationID[MAX_KEY_LENGTH];
} DataProcessing;

// Function to initialize the DataProcessing system
void initDataProcessing(DataProcessing* dp) {
    // Initialize the components
    initSpeedManagement(&dp->speedManager);
    initDoorControl(&dp->doorManager);
    initSensorFeedback(&dp->sensorManager);
    strcpy(dp->stationID, "Station-01");  // Default station ID
}

// Function to start the connection based on Blade Runner ID
void connectionStartBR(int BR) {
    int port = (BR == 18) ? 3018 : (BR == 19) ? 3019 : SERVER_PORT_DEFAULT;

    // Create the socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
}

// Send packet function
void sendPacket(const char *message) {
    int sent_bytes = sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (sent_bytes == -1) {
        perror("sendto failed");
        exit(EXIT_FAILURE);
    }
    printf("Message sent: %s\n", message);
}

// Receive packet function
void receivePacket(char *buffer) {
    int recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &client_len);
    if (recv_len == -1) {
        perror("recvfrom failed");
        exit(EXIT_FAILURE);
    }
    buffer[recv_len] = '\0';  // Null-terminate the received data
    printf("Received message: %s\n", buffer);
}

// Handle station ID setting
void setStationID(DataProcessing *dp, const char *stationID) {
    strncpy(dp->stationID, stationID, MAX_KEY_LENGTH);
}

// Retrieve station ID
const char *getStationID(DataProcessing *dp) {
    return dp->stationID;
}

// Function to execute commands based on received input
void executeCommand(DataProcessing* dp, const char* command) {
    if (strcmp(command, "FFASTC") == 0) {
        setSpeed(&dp->speedManager, 5.0);
        closeDoor(&dp->doorManager);
    } else if (strcmp(command, "FSLOWC") == 0) {
        setSpeed(&dp->speedManager, 2.5);
        closeDoor(&dp->doorManager);
    } else if (strcmp(command, "RSLOWC") == 0) {
        setSpeed(&dp->speedManager, -2.5);
        closeDoor(&dp->doorManager);
    } else if (strcmp(command, "STOPC") == 0) {
        setSpeed(&dp->speedManager, 0);
        closeDoor(&dp->doorManager);
    } else if (strcmp(command, "STOPO") == 0) {
        setSpeed(&dp->speedManager, 0);
        openDoor(&dp->doorManager);
    } else if (strcmp(command, "DISCONNECT") == 0) {
        sendCarriageMessage("OFLN");
    } else {
        printf("Unknown command: %s\n", command);
    }
}

// Function to send messages to the carriage control system
void sendCarriageMessage(const char *message) {
    printf("Sending message to Carriage Control Program: %s\n", message);
    sendPacket(message);
}
*/
#include <stdio.h>
#include <string.h>

// SensorFeedback structure
typedef struct {
    char sensorStatus[20]; // Sensor status as a string
} SensorFeedback;

// Function to initialize the SensorFeedback structure
void initSensorFeedback(SensorFeedback *sf) {
    strcpy(sf->sensorStatus, "normal"); // Default sensor status
}

// Function to get the current sensor status
const char* getSensorStatus(SensorFeedback *sf) {
    return sf->sensorStatus;
}

// Function to update the sensor status
void updateSensorStatus(SensorFeedback *sf, const char* status) {
    strcpy(sf->sensorStatus, status);
    printf("Sensor status updated to: %s\n", sf->sensorStatus);
}
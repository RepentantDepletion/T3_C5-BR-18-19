#include <stdio.h>
#include "driver/gpio.h"

// Declare the functions from SpeedManagement.c
void initSpeedManagement();
void setSpeed(int speedLevel);
void stopMotor();
void increaseSpeed();
void decreaseSpeed();

// Declare the functions from DoorControl.c
void initDoorControl();
void openDoor();
void closeDoor();

// Define the GPIO pin where the IR sensor is connected
// need to update which pin is actually being used
#define IR_SENSOR_PIN 15

// IRSensor struct to manage the sensor state
typedef struct {
    int isLightDetected;  // 0 = no light detected, 1 = light detected
} IRSensor;

// Initialize the IR sensor
void initIRSensor(IRSensor* irSensor) {
    irSensor->isLightDetected = 0;  // Initially no light detected

    // Initialize the GPIO pin for the IR sensor
    gpio_pad_select_gpio(IR_SENSOR_PIN);
    gpio_set_direction(IR_SENSOR_PIN, GPIO_MODE_INPUT);

    // Print initialization message
    printf("IR sensor initialized on pin %d.\n", IR_SENSOR_PIN);
}

// Check if the IR sensor detects light, stop the motor, and open the door
void checkForLight(IRSensor* irSensor) {
    int sensorValue = gpio_get_level(IR_SENSOR_PIN);  // Read sensor value (HIGH/LOW)
    
    if (sensorValue == 1 && irSensor->isLightDetected == 0) {
        // Light detected for the first time, stop the motor and open the door
        irSensor->isLightDetected = 1;  // Update sensor state to detected
        printf("Light detected! Stopping motor and opening door...\n");

        stopMotor();  // Stop the motor using SpeedManagement
        openDoor();   // Open the door using DoorControl
    } else if (sensorValue == 0 && irSensor->isLightDetected == 1) {
        // Light no longer detected, reset the sensor state
        irSensor->isLightDetected = 0;  // Reset sensor state
        printf("Light no longer detected.\n");
    }
}

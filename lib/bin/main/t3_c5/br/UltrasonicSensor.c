#include <stdio.h>
#include "driver/gpio.h"
#include "esp_timer.h"  // For precise timing

#define TRIGGER_PIN 18  // GPIO pin for the Trigger of the ultrasonic sensor
#define ECHO_PIN 19     // GPIO pin for the Echo of the ultrasonic sensor

// UltrasonicSensor struct to manage the sensor state
typedef struct {
    int distance_cm;  // Measured distance in cm
} UltrasonicSensor;

// Function to initialize the ultrasonic sensor
void initUltrasonicSensor() {
    // Initialize the GPIO pins
    gpio_pad_select_gpio(TRIGGER_PIN);
    gpio_set_direction(TRIGGER_PIN, GPIO_MODE_OUTPUT);  // Trigger pin as output
    gpio_pad_select_gpio(ECHO_PIN);
    gpio_set_direction(ECHO_PIN, GPIO_MODE_INPUT);  // Echo pin as input
    printf("Ultrasonic sensor initialized (Trigger: %d, Echo: %d).\n", TRIGGER_PIN, ECHO_PIN);
}

// Function to get the distance from the ultrasonic sensor
int getDistance(UltrasonicSensor *sensor) {
    // Ensure Trigger pin is low
    gpio_set_level(TRIGGER_PIN, 0);
    ets_delay_us(2);  // Wait for 2 microseconds

    // Send a 10 microsecond pulse to the Trigger pin
    gpio_set_level(TRIGGER_PIN, 1);
    ets_delay_us(10);  // Wait for 10 microseconds
    gpio_set_level(TRIGGER_PIN, 0);

    // Measure the time it takes for the Echo pin to go HIGH
    int64_t startTime = esp_timer_get_time();
    while (gpio_get_level(ECHO_PIN) == 0) {
        startTime = esp_timer_get_time();  // Wait until Echo pin goes HIGH
    }

    // Measure the time it takes for the Echo pin to go LOW again
    int64_t endTime = startTime;
    while (gpio_get_level(ECHO_PIN) == 1) {
        endTime = esp_timer_get_time();  // Wait until Echo pin goes LOW
    }

    // Calculate the distance based on the time difference
    int64_t timeElapsed = endTime - startTime;
    int distance = (int)(timeElapsed * 0.034 / 2);  // Convert to cm (speed of sound in air is 0.034 cm/us)

    // Update the sensor struct with the measured distance
    sensor->distance_cm = distance;

    printf("Measured Distance: %d cm\n", distance);
    return distance;
}

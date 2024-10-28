#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "driver/gpio.h" 
#include "driver/ledc.h"

static const int motorPin1 = 12; // Motor direction pin 1
static const int motorPin2 = 13; // Motor direction pin 2
static const int pwmPin = 14;    // PWM pin to control motor speed

const int freq = 5000;             // Frequency for PWM
const int pwmChannel = 0;          // Channel for PWM
const int resolution = 8;          // 8-bit resolution (0-255)
int dutyCycle = 0;  

void setSpeed(int speedLevel)
{
    // Ensure speedLevel is between 0 and 255 (PWM duty cycle)
    if (speedLevel < 0 || speedLevel > 255)
    {
        Serial.println("Invalid speed level. Please set a value between 0 and 255.");
        return;
    }

    // Set motor direction (forward or reverse)
    gpio_set_level(static_cast<gpio_num_t>(motorPin1), 1); // Forward direction
    gpio_set_level(static_cast<gpio_num_t>(motorPin2), 0); // Reverse direction (reverse if necessary)

    // Set the PWM duty cycle for the motor speed
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, static_cast<ledc_channel_t>(pwmChannel), speedLevel);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, static_cast<ledc_channel_t>(pwmChannel));

    // Print the current speed level
    Serial.print("Speed set to: ");
    Serial.println(speedLevel);
}


// Function to gradually increase the motor speed
void increaseSpeed()
{
    for (int speedLevel = 0; speedLevel <= 255; speedLevel += 10)
    {
        setSpeed(speedLevel); // Increase speed
        delay(200);           // Simulate gradual speed increase
    }
    Serial.println("Speed at maximum.");
}

// Function to gradually decrease the motor speed
void decreaseSpeed()
{
    for (int speedLevel = 255; speedLevel >= 0; speedLevel -= 10)
    {
        setSpeed(speedLevel); // Decrease speed
        delay(200);           // Simulate gradual speed decrease
    }
    Serial.println("Speed at minimum.");
}

// Function to stop the motor
void stopMotor()
{
    // Set both motor direction pins to low to stop the motor
    gpio_set_level(static_cast<gpio_num_t>(motorPin1), 0);
    gpio_set_level(static_cast<gpio_num_t>(motorPin2), 0);

    // Set PWM duty cycle to 0 to ensure motor is off
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, static_cast<ledc_channel_t>(pwmChannel), 0);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, static_cast<ledc_channel_t>(pwmChannel));

    // Print message confirming the motor is stopped
    Serial.println("Motor stopped.");
}

void initSpeedManagement()
{
    // Configure motor direction pins
    esp_rom_gpio_pad_select_gpio(static_cast<gpio_num_t>(motorPin1));
    gpio_set_direction(static_cast<gpio_num_t>(motorPin1), GPIO_MODE_OUTPUT);
    esp_rom_gpio_pad_select_gpio(static_cast<gpio_num_t>(motorPin2));
    gpio_set_direction(static_cast<gpio_num_t>(motorPin2), GPIO_MODE_OUTPUT);

    // Configure PWM for speed control (field order corrected)
    ledc_timer_config_t pwm_timer = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = freq
    };
    ledc_timer_config(&pwm_timer);

    // Configure PWM channel (field order corrected, and type cast)
    ledc_channel_config_t pwm_channel = {
        .gpio_num = pwmPin,                              // GPIO pin must come first
        .speed_mode = LEDC_HIGH_SPEED_MODE,              // Then the speed mode
        .channel = static_cast<ledc_channel_t>(pwmChannel), // PWM channel typecast
        .timer_sel = LEDC_TIMER_0,                       // Timer selection
        .duty = 0,                                       // Duty cycle
        .hpoint = 0                                      // Hpoint
    };
    ledc_channel_config(&pwm_channel);

    // Start serial communication for debugging
    Serial.begin(115200);
    Serial.println("Speed management for DC motor initialized.");
}
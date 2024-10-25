#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <WiFi.h>
#include <WiFiUdp.h>

static const int motorPin1 = 18; // Motor direction pin 1
static const int motorPin2 = 19; // Motor direction pin 2
static const int pwmPin = 14;    // PWM pin to control motor speed
unsigned long myTime;
unsigned long startTime;

// Main function loop
void loop()
{
    myTime = millis();
    setSpeed(155);
    startTime = myTime;
    if(myTime >= startTime + 5000){
        setSpeed(0);
        startTime = myTime;
        if(myTime >= startTime + 2000){
            stopMotor();
        }
    }
}

// Setup function to initialize WiFi and data processing
void setup()
{
    initSpeedManagement();
}

void initSpeedManagement()
{
    // Configure motor direction pins
    gpio_pad_select_gpio(motorPin1);
    gpio_set_direction(motorPin1, GPIO_MODE_OUTPUT);
    gpio_pad_select_gpio(motorPin2);
    gpio_set_direction(motorPin2, GPIO_MODE_OUTPUT);

    // Configure PWM for speed control
    ledc_timer_config_t pwm_timer = {
        .duty_resolution = LEDC_TIMER_8_BIT,
        .freq_hz = freq,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
    };
    ledc_timer_config(&pwm_timer);

    ledc_channel_config_t pwm_channel = {
        .channel = pwmChannel,
        .duty = 0, // Start with duty cycle 0
        .gpio_num = pwmPin,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_TIMER_0,
    };
    ledc_channel_config(&pwm_channel);

    // Start serial communication for debugging
    Serial.begin(115200);
    Serial.println("Speed management for DC motor initialized.");
}

// Function to set the speed of the motor (0-255 for PWM duty cycle)
void setSpeed(int speedLevel)
{
    // Ensure speedLevel is between 0 and 255 (PWM duty cycle)
    if (speedLevel < 0 || speedLevel > 255)
    {
        Serial.println("Invalid speed level. Please set a value between 0 and 255.");
        return;
    }

    // Set motor direction (forward or reverse)
    gpio_set_level(motorPin1, 1); // Forward direction
    gpio_set_level(motorPin2, 0); // Reverse direction (you can reverse these if necessary)

    // Set the PWM duty cycle for the motor speed
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, pwmChannel, speedLevel);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, pwmChannel);

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
    gpio_set_level(motorPin1, 0);
    gpio_set_level(motorPin2, 0);

    // Set PWM duty cycle to 0 to ensure motor is off
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, pwmChannel, 0);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, pwmChannel);

    // Print message confirming the motor is stopped
    Serial.println("Motor stopped.");
}
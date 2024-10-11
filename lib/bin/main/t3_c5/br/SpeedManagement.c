#include <ESP32Servo.h>
#include <stdio.h>
#include <string.h>

// Define the servo pin to control the motor speed
static const int servoPin = 14;  // You can change this pin based on your setup

Servo motorServo;  // Create a Servo object to control the motor

// Function to initialize the servo motor control for speed management
void initSpeedManagement() {
    // Attach the motorServo to the defined pin
    motorServo.attach(servoPin);

    // Initial print message
    Serial.begin(115200);
    Serial.println("Speed management initialized.");
}

// Function to set the speed of the motor
// speedLevel is expected to be between 0 and 180 (degrees for servo, simulating speed level)
void setSpeed(int speedLevel) {
    // Check if the speed level is within the correct range
    if (speedLevel < 0 || speedLevel > 180) {
        Serial.println("Invalid speed level. Please set a value between 0 and 180.");
        return;
    }

    // Move the servo to the desired position, simulating speed control
    motorServo.write(speedLevel);

    // Print the current speed level
    Serial.print("Speed set to: ");
    Serial.println(speedLevel);
}

// Function to gradually increase the motor speed
void increaseSpeed() {
    // Increase speed gradually by moving the servo from 0 to 180 degrees
    for (int speedLevel = 0; speedLevel <= 180; speedLevel += 10) {
        motorServo.write(speedLevel);  // Move the servo to simulate speed increase
        Serial.print("Increasing speed: ");
        Serial.println(speedLevel);

        // Delay to simulate gradual speed increase
        delay(200);
    }

    // Print a final message once maximum speed is reached
    Serial.println("Speed at maximum.");
}

// Function to gradually decrease the motor speed
void decreaseSpeed() {
    // Decrease speed gradually by moving the servo from 180 to 0 degrees
    for (int speedLevel = 180; speedLevel >= 0; speedLevel -= 10) {
        motorServo.write(speedLevel);  // Move the servo to simulate speed decrease
        Serial.print("Decreasing speed: ");
        Serial.println(speedLevel);

        // Delay to simulate gradual speed decrease
        delay(200);
    }

    // Print a final message once the speed reaches zero
    Serial.println("Speed at minimum.");
}

// Function to stop the motor by setting speed to 0
void stopMotor() {
    // Set the servo position to 0 to stop the motor
    motorServo.write(0);

    // Print message confirming that the motor is stopped
    Serial.println("Motor stopped.");
}

void setup() {
    // Initialize the speed management system
    initSpeedManagement();
    /*
    // Example usage
    setSpeed(90);       // Set the speed to 90 degrees (mid-range)
    delay(2000);        // Hold the speed for 2 seconds

    increaseSpeed();    // Gradually increase speed
    delay(2000);        // Hold the maximum speed for 2 seconds

    decreaseSpeed();    // Gradually decrease speed
    delay(2000);        // Hold the minimum speed for 2 seconds

    stopMotor();        // Stop the motor
    */
}

void loop() {
    // to do real time updates
}



/*#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float currentSpeed;
    int isSpeedSet;
} SpeedManagement;

SpeedManagement* createSpeedManagement() {
    SpeedManagement* sm = (SpeedManagement*) malloc(sizeof(SpeedManagement));
    if (sm != NULL) {
        sm->currentSpeed = 0.0;
        sm->isSpeedSet = 0;
    }
    return sm;
}


void initSpeedManagement(SpeedManagement *sm) {
    sm->currentSpeed = 0.0;
    sm->isSpeedSet = 0;
}

void setSpeed(SpeedManagement *sm, float speed) {
    // actual speed setting
    sm->currentSpeed = speed;
    sm->isSpeedSet = 1; // checks if the speed was set
    printf("Speed set to: %.2f cm/s\n", sm->currentSpeed);
}

int confirmSpeedSet(SpeedManagement *sm) {
    // confirms if the speed was successfully set
    return sm->isSpeedSet;
}

float getCurrentSpeed(SpeedManagement *sm) {
    return sm->currentSpeed;
}



//test function
int main() {
    SpeedManagement sm;
    initSpeedManagement(&sm);

    setSpeed(&sm, 75.0);
    if (confirmSpeedSet(&sm)) {
        printf("Speed was successfully set!\n");
    } else {
        printf("Failed to set speed.\n");
    }
    return 0;
}
*/
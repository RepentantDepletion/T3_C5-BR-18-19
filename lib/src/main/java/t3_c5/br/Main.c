#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "DataProcessing.h"
#include "driver/gpio.h" 
#include "driver/ledc.h"
#include "SpeedManagement.h"
#include "DoorControl.h"
#include "SensorFeedback.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <jni.h>


// Define package as instructed
#define PACKAGE t3_c5_br

#define SERVER_IP "10.20.30.1"
#define SERVER_PORT_BR18 3018
#define SERVER_PORT_BR19 3019
#define BUFFER_SIZE 1024

typedef enum {
    COMMAND_FAST_CLOSE,         // Command for fast close
    COMMAND_SLOW_CLOSE,        // Command for slow close
    COMMAND_REVERSE_SLOW_CLOSE, // Command for reverse slow close
    COMMAND_STOP_CLOSE,        // Command to stop closing
    COMMAND_STOP_OPEN,         // Command to stop and open
    COMMAND_DISCONNECT,        // Command to disconnect
    COMMAND_UNKNOWN            // Unknown command handler
} Command;

// WiFi credentials
const char *ssid = "ENGG2K3K";
IPAddress local_IP(10, 20, 30, 118);
IPAddress gateway(10, 30, 20, 1);

// UDP communication
WiFiUDP udp;
int serverPort = SERVER_PORT_BR18;
DataProcessing dataProcessing;

// Main function loop
void loop() {
    dataprocess();  // Continuously process data in the loop
}

// Setup function to initialize WiFi and data processing
void setup() {
    Serial.begin(115200);  // Initialize serial communication for debugging
    delay(1000);

    // Connect to WiFi
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid);
    Serial.println("\nConnecting to WiFi...");

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }

    // Display connection information
    Serial.println("\nConnected to network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());

    // Start UDP communication
    udp.begin(serverPort);
    Serial.println("UDP started on port: " + String(serverPort));

    // Initialize data processing components
    initDataProcessing(&dataProcessing);
}




void connectionStartBR(int BR) {
    // Determine the port to use based on the Blade Runner ID
    int port = (BR == 18) ? 3018 : (BR == 19) ? 3019 : SERVER_PORT_DEFAULT;

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        // Print error message if socket creation fails
        fprintf(stderr, "Socket creation failed. Retrying...\n");
        return;
    }

    // Set up the server address structure
    memset(&server_addr, 0, sizeof(server_addr));  // Clear the structure
    server_addr.sin_family = AF_INET;              // Use IPv4
    server_addr.sin_port = htons(port);             // Set port number
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP); // Set server IP address
}



/*
// Data processing function that receives and executes commands
void dataprocess() {
    // Receive packet
    receivePacket();

    // Example received command
    const char *command = "FFASTC";  // Example command for fast close

    // Execute the received command
    executeCommand(&dataProcessing, command);
    

    // Example data to send
    const char *dataToSend = "PACKET_DATA";
    sendPacket(dataToSend);
}
*/

////////////////////////////////////////////////////// DATA PROCESS

void initDataProcessing(DataProcessing* dp) {
    // Initialize individual components of the DataProcessing system
    initSpeedManagement(&dp->speedManager); // Initialize speed manager
    initDoorControl(&dp->doorManager);       // Initialize door manager
    initSensorFeedback(&dp->sensorManager);  // Initialize sensor feedback manager
    strcpy(dp->stationID, "Station-01");     // Set default station ID
}




// Function to simulate receiving a packet (placeholder for actual UDP receive)
void receivePacket() {
    char packetBuffer[BUFFER_SIZE];
    int packetSize = udp.parsePacket();

    if (packetSize) {
        // Read the incoming packet
        int len = udp.read(packetBuffer, BUFFER_SIZE);
        if (len > 0) {
            packetBuffer[len] = '\0';  // Null-terminate the string
        }

        // Print the received packet data
        Serial.print("Received packet: ");
        Serial.println(packetBuffer);
    }
}

// Function to execute a command using DataProcessing structure
void executeCommand(DataProcessing* dp, const char *command) {
    Serial.print("Executing command: ");
    Serial.println(command);

    // Parse and execute the command
    Command cmd = parseCommand(command);
    executeCommand(dp, command);
}

// Function to send a packet (placeholder for actual UDP send)
void sendPacket(const char *data) {
    udp.beginPacket(SERVER_IP, serverPort);
    udp.write(data);
    udp.endPacket();

    Serial.print("Sent packet with data: ");
    Serial.println(data);
}

void setStationID(DataProcessing *dp, const char *stationID) {
    // Copy the provided station ID into the struct
    strncpy(dp->stationID, stationID, MAX_KEY_LENGTH);
}

// Function to retrieve the station ID from the DataProcessing struct
const char *getStationID(DataProcessing *dp) {
    return dp->stationID; // Return the station ID
}

// Function to parse command strings into Command enums
Command parseCommand(const char* command) {
    // Compare input command with known commands
    if (strcmp(command, "FFASTC") == 0) return COMMAND_FAST_CLOSE; // Fast close command
    if (strcmp(command, "FSLOWC") == 0) return COMMAND_SLOW_CLOSE; // Slow close command
    if (strcmp(command, "RSLOWC") == 0) return COMMAND_REVERSE_SLOW_CLOSE; // Reverse slow close command
    if (strcmp(command, "STOPC") == 0) return COMMAND_STOP_CLOSE; // Stop closing command
    if (strcmp(command, "STOPO") == 0) return COMMAND_STOP_OPEN; // Stop and open command
    if (strcmp(command, "DISCONNECT") == 0) return COMMAND_DISCONNECT; // Disconnect command
    return COMMAND_UNKNOWN; // Return unknown command if no match found
}

// Function to execute commands based on received input
void executeCommand(DataProcessing* dp, const char* command) {
    // Use a switch statement to handle different commands
    switch (parseCommand(command)) {
        case COMMAND_FAST_CLOSE:
            setSpeed(&dp->speedManager, 5.0); // Set speed for fast close
            closeDoor(&dp->doorManager); // Close the door
            break;
        case COMMAND_SLOW_CLOSE:
            setSpeed(&dp->speedManager, 2.5); // Set speed for slow close
            closeDoor(&dp->doorManager); // Close the door
            break;
        case COMMAND_REVERSE_SLOW_CLOSE:
            setSpeed(&dp->speedManager, -2.5); // Set speed for reverse slow close
            closeDoor(&dp->doorManager); // Close the door
            break;
        case COMMAND_STOP_CLOSE:
            setSpeed(&dp->speedManager, 0); // Stop movement
            closeDoor(&dp->doorManager); // Close the door
            break;
        case COMMAND_STOP_OPEN:
            setSpeed(&dp->speedManager, 0); // Stop movement
            openDoor(&dp->doorManager); // Open the door
            break;
        case COMMAND_DISCONNECT:
            sendCarriageMessage("OFLN"); // Send disconnect message
            break;
        case COMMAND_UNKNOWN:
        default:
            // Print error message for unknown command
            printf("Unknown command: %s\n", command);
            break;
    }
}

// Function to send messages to the carriage control system
void sendCarriageMessage(const char *message) {
    // Print sending message info
    printf("Sending message to Carriage Control Program: %s\n", message);
    sendPacket(message); // Call sendPacket to send the message
}

///////////////////////////////////////////////////////////////// DOOR CONTROL

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

///////////////////////////////////////////////////////////////// SPEED CONTROL

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

///////////////////////////////////////////////////////////SENSOR FEEDBACK

typedef struct {
    char sensorStatus[20];
} SensorFeedback;

// Initialize the SensorFeedback object
void initSensorFeedback(SensorFeedback* sf) {
    strcpy(sf->sensorStatus, "normal"); // Default sensor status
}

// Get the sensor status
const char* getSensorStatus(SensorFeedback* sf) {
    return sf->sensorStatus;
}

// Update the sensor status
void updateSensorStatus(SensorFeedback* sf, const char* status) {
    strcpy(sf->sensorStatus, status);
    printf("Sensor status updated to: %s\n", sf->sensorStatus);
}

int main() {
    // Create a SensorFeedback object
    SensorFeedback sf;
    
    // Initialize the SensorFeedback object
    initSensorFeedback(&sf);
    
    // Test the sensor feedback methods
    printf("Initial Sensor Status: %s\n", getSensorStatus(&sf));
    updateSensorStatus(&sf, "warning");
    printf("Current Sensor Status: %s\n", getSensorStatus(&sf));
    updateSensorStatus(&sf, "critical");
    printf("Current Sensor Status: %s\n", getSensorStatus(&sf));
    
    return 0;
}

/////////////////////////////////////////////////////// IRSensor

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

    } else if (sensorValue == 0 && irSensor->isLightDetected == 1) {
        // Light no longer detected, reset the sensor state
        irSensor->isLightDetected = 0;  // Reset sensor state
        printf("Light no longer detected.\n");
    }
}

//update 1.2
#define PACKAGE t3_c5_br

//Include required libraries
#include "SpeedManagement.h"
#include "DoorControl.h"
#include "SensorFeedback.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <jni.h>
#include <WiFi.h>  // Include the WiFi library for ESP32
#include <WiFiUdp.h> // Include the WiFi UDP library for handling UDP connections

// Define constants
#define SERVER_PORT_DEFAULT 3018  // Default server port
#define SERVER_IP "10.20.30.1"    // Server IP address
#define BUFFER_SIZE 1024           // Size of the buffer for receiving messages
#define MAX_KEY_LENGTH 50          // Maximum length for the station ID

// Global Variables
int sockfd;  // Socket file descriptor for UDP communication
struct sockaddr_in server_addr, client_addr;  // Structures for server and client addresses
socklen_t client_len = sizeof(client_addr);  // Length of the client address structure

// DataProcessing struct to hold all components
typedef struct {
    SpeedManagement speedManager;  // Instance of SpeedManagement for controlling speed
    DoorControl doorManager;        // Instance of DoorControl for managing doors
    SensorFeedback sensorManager;   // Instance of SensorFeedback for sensor data handling
    char stationID[MAX_KEY_LENGTH]; // Station ID for identifying the data processing unit
} DataProcessing;

// Enumeration to define command types
typedef enum {
    COMMAND_FAST_CLOSE,         // Command for fast close
    COMMAND_SLOW_CLOSE,        // Command for slow close
    COMMAND_REVERSE_SLOW_CLOSE, // Command for reverse slow close
    COMMAND_STOP_CLOSE,        // Command to stop closing
    COMMAND_STOP_OPEN,         // Command to stop and open
    COMMAND_DISCONNECT,        // Command to disconnect
    COMMAND_UNKNOWN            // Unknown command handler
} Command;

// Function to initialize the DataProcessing system
void initDataProcessing(DataProcessing* dp) {
    // Initialize individual components of the DataProcessing system
    initSpeedManagement(&dp->speedManager); // Initialize speed manager
    initDoorControl(&dp->doorManager);       // Initialize door manager
    initSensorFeedback(&dp->sensorManager);  // Initialize sensor feedback manager
    strcpy(dp->stationID, "Station-01");     // Set default station ID
}

// Function to start the connection based on Blade Runner ID
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

// Function to send a packet to the server
void sendPacket(const char *message) {
    // Send the message to the server
    int sent_bytes = sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (sent_bytes == -1) {
        // Print error message if sending fails
        perror("sendto failed");
        exit(EXIT_FAILURE); // Exit on failure
    }
    // Print confirmation of sent message
    printf("Message sent: %s\n", message);
}

// Function to receive a packet from the client
void receivePacket() {
    // Allocate memory for the buffer to hold incoming messages
    char *buffer = malloc(BUFFER_SIZE);
    if (!buffer) {
        // Handle memory allocation failure
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Receive the message from the client
    int recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &client_len);
    if (recv_len == -1) {
        // Print error message if receiving fails
        perror("recvfrom failed");
        free(buffer); // Free allocated memory before exit
        exit(EXIT_FAILURE);
    }

    buffer[recv_len] = '\0'; // Null-terminate the received data
    // Print the received message
    printf("Received message: %s\n", buffer);
    free(buffer); // Free allocated memory after use
}

// Function to set the station ID in the DataProcessing struct
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


/*
//update 1.1

#define PACKAGE t3_c5_br

#include "SpeedManagement.h"
#include "DoorControl.h"
#include "SensorFeedback.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <jni.h>


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
void executeCommand(DataProcessing* dp, const char* command) { //dp - pointer to the DataProcessing struct
    if (strcmp(command, "FFASTC") == 0) {
        setSpeed(&dp->speedManager, 5.0); // Set spped 5.0, 2.5, 2.0
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
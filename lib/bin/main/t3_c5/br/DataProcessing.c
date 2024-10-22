#define PACKAGE t3_c5_br

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

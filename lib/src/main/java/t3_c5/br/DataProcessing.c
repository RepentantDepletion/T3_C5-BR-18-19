#define package t3_c5.br;

#include "C:\Users\iaml2\Documents\T3_C5-BR-18-19\lib\src\main\java\SpeedManagement.c"
#include "C:\Users\iaml2\Documents\T3_C5-BR-18-19\lib\src\main\java\DoorControl.c"
#include "C:\Users\iaml2\Documents\T3_C5-BR-18-19\lib\src\main\java\SensorFeedback.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_PORT 3018
#define SERVER_IP "10.20.30.1"

#define MAX_KEY_LENGTH 50
#define MAX_VALUE_LENGTH 100

struct
{
    SpeedManagement;
    DoorControl;
    SensorFeedback;
} DataProcessing;

void DataProcessing(SpeedManagement, DoorControl, SensorFeedback)
{
    SpeedManagement speedManager;
    DoorControl doorManager;
    SensorFeedback sensorManager;
}

void connectionStartBR(int BR)
{
    if(BR == 18){
        SERVER_PORT = 3018;
    }
    else if(BR == 19){
        SERVER_PORT = 3019;
    }
    else{
        printf("Unknown/Incorrect Bladerunner ID for Bladerunner");
    }
    
    int sockfd;
    struct sockaddr_in server_addr;

    // Create the socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    // Set address family, IP, and port
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
}

void sendPacket(String message){
    int sent_bytes = sendto(sockfd, message, strlen(message), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    if (sent_bytes == -1) {
        perror("sendto failed");
        exit(EXIT_FAILURE);
    }

    printf("Message sent.\n");
}

String receivePacket(){
    // Bind the socket to the specified port
    if (bind(sockfd, (const struct sockaddr *)&local_addr, sizeof(local_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Waiting for data...\n");

    // Receive the message
    int recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_len);
    if (recv_len == -1) {
        perror("recvfrom failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buffer[recv_len] = '\0';  // Null-terminate the received data
    printf("Received message: %s\n", buffer);

    return buffer.trimwhitespace();
}

void setStationID(DataProcessing *dp, const char *stationID)
{
}

const char *getStationID(DataProcessing *dp)
{
    return dp->stationID;
}

void storeComponentData(DataProcessing *dp, const char *key, const char *data)
{
    if (dp->componentCount < MAX_COMPONENTS)
    {
        strcpy(dp->componentData[dp->componentCount].key, key);
        strcpy(dp->componentData[dp->componentCount].value, data);
        dp->componentCount++;
    }
}

void executeCommand(const char Command)
{
    char action[10];
    sscanf(Command, "%s", action);

    switch (Command)
    case "FFASTC":
        speedManager.setSpeed(5.0);
    doorManager.close();
case "FSLOWC":
    speedManager.setSpeed(2.5);
    doorManager.close();
case "RSLOWC":
    speedManager.setSpeed(-2.5);
    doorManager.close();
case "STOPC" speedManager.setSpeed(0);
    doorManager.close();
    case "STOPO":
    speedManager.setSpeed(0);
    doorManager.open();
case "DISCONNECT":
    sendCarriageMessage("OFLN");
}

void sendCarriageMessage(const char *message)
{
    printf("Sending message to Carriage Control Program: %s\n", message);
}

const char *receiveCarriageCommand()
{
    return "set_speed:80.5"; // Returning a dummy command for simulation
}

char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}
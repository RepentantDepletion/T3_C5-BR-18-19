#define PACKAGE t3_c5_br

#include "SpeedManagement.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "10.20.30.1"
#define SERVER_PORT_BR18 3018
#define SERVER_PORT_BR19 3019
#define BUFFER_SIZE 1024

DataProcesing data;

// Main function
int main() {
    int sockfdBR18, sockfdBR19;
    struct sockaddr_in server_addrBR18, server_addrBR19;
    char buffer[BUFFER_SIZE];
    
    // Create UDP sockets
    if ((sockfdBR18 = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed for BR18");
        exit(EXIT_FAILURE);
    }
    if ((sockfdBR19 = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed for BR19");
        exit(EXIT_FAILURE);
    }

    // Set up server addresses for BR18 and BR19
    memset(&server_addrBR18, 0, sizeof(server_addrBR18));
    server_addrBR18.sin_family = AF_INET;
    server_addrBR18.sin_port = htons(SERVER_PORT_BR18);
    server_addrBR18.sin_addr.s_addr = inet_addr(SERVER_IP);

    memset(&server_addrBR19, 0, sizeof(server_addrBR19));
    server_addrBR19.sin_family = AF_INET;
    server_addrBR19.sin_port = htons(SERVER_PORT_BR19);
    server_addrBR19.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Handshake with MCP
    handshake(sockfdBR18, &server_addrBR18);
    handshake(sockfdBR19, &server_addrBR19);

    // Initialize data processing system
    init_data_processing();

    // Listener loop
    while (1) {
        // Receive incoming command for BR18
        receive_packet(sockfdBR18, buffer, &server_addrBR18);
        execute_command(buffer);

        // Send status message
        const char *status_string = cJSON_Print(statusMessage);
        send_packet(sockfdBR18, status_string, &server_addrBR18);
        cJSON_Delete(statusMessage);
        free((void*)status_string);
    }

    close(sockfdBR18);
    close(sockfdBR19);

    return 0;
}

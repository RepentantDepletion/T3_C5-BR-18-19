#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cjson/cJSON.h>

#define SERVER_IP "10.20.30.1"
#define SERVER_PORT_BR18 3018
#define SERVER_PORT_BR19 3019
#define BUFFER_SIZE 1024

// Define function prototypes
void handshake(int sockfd, struct sockaddr_in *server_addr);
void receive_packet(int sockfd, char *buffer, struct sockaddr_in *client_addr);
void send_packet(int sockfd, const char *message, struct sockaddr_in *server_addr);
void execute_command(const char *command);
void init_data_processing();
void set_speed(float speed);
void close_door();
void open_door();

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
        cJSON *statusMessage = cJSON_CreateObject();
        cJSON_AddStringToObject(statusMessage, "type", "STAT");
        const char *status_string = cJSON_Print(statusMessage);
        send_packet(sockfdBR18, status_string, &server_addrBR18);
        cJSON_Delete(statusMessage);
        free((void*)status_string);
    }

    close(sockfdBR18);
    close(sockfdBR19);

    return 0;
}

// Handshake function
void handshake(int sockfd, struct sockaddr_in *server_addr) {
    const char *handshake_msg = "HANDSHAKE";
    send_packet(sockfd, handshake_msg, server_addr);
}

// Function to receive packets
void receive_packet(int sockfd, char *buffer, struct sockaddr_in *client_addr) {
    socklen_t len = sizeof(*client_addr);
    recvfrom(sockfd, buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *) client_addr, &len);
    buffer[strlen(buffer)] = '\0';
}

// Function to send packets
void send_packet(int sockfd, const char *message, struct sockaddr_in *server_addr) {
    sendto(sockfd, message, strlen(message), MSG_CONFIRM, (const struct sockaddr *) server_addr, sizeof(*server_addr));
}

// Function to execute command
void execute_command(const char *command) {
    if (strcmp(command, "fast") == 0) {
        set_speed(5.0f);
        close_door();
    } else if (strcmp(command, "slow") == 0) {
        set_speed(2.5f);
        close_door();
    } else if (strcmp(command, "reverseSlow") == 0) {
        set_speed(-2.5f);
        close_door();
    } else if (strcmp(command, "stopClose") == 0) {
        set_speed(0.0f);
        close_door();
    } else if (strcmp(command, "stopOpen") == 0) {
        set_speed(0.0f);
        open_door();
    } else if (strcmp(command, "disconnect") == 0) {
        printf("Carriage disconnected: OFLN\n");
    } else {
        printf("Unknown command: %s\n", command);
    }
}

// Placeholder functions for system control
void set_speed(float speed) {
    printf("Setting speed to: %.2f\n", speed);
}

void close_door() {
    printf("Closing door\n");
}

void open_door() {
    printf("Opening door\n");
}

void init_data_processing() {
    printf("Initializing data processing...\n");
    // Initialization logic
}

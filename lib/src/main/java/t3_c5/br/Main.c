#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "SpeedManagement.h"
#include "DoorControl.h"
#include "SensorFeedback.h"

// Define package as instructed
#define PACKAGE t3_c5_br

#define SERVER_IP "10.20.30.1"
#define SERVER_PORT_BR18 3018
#define SERVER_PORT_BR19 3019
#define BUFFER_SIZE 1024

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

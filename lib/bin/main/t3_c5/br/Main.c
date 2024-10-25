#define PACKAGE t3_c5_br

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <WiFi.h>

#define SERVER_IP "10.20.30.1"
#define SERVER_PORT_BR18 3018
#define SERVER_PORT_BR19 3019
#define BUFFER_SIZE 1024

const char *ssid = "ENGG2K3K";
IPAddress local_IP(10, 20, 30, 118);
IPAddress gateway(10, 30, 20, 1);

// Main function
void loop(){}

void setup()
{
    Serial.begin(SERVER_PORT_BR18);
    delay(1000);

    WiFi.mode(WIFI_STA); // optional
    WiFi.begin(ssid);
    Serial.println("\nconnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nIP Address:\n" + local_IP);
    Serial.println("\nConnected to network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

void dataprocess(){     // may need to change specific names of functions once data processing is actually complete

    receivePacket();

    const char *command = "example";
    executeCommand(command);

    // Example data to send
    const char *dataToSend = "PACKET_DATA";
    sendPacket(dataToSend);
}

// Function to simulate receiving a packet
void receivePacket(){
    Serial.println("Receiving packet...");
}

// Function to execute a command
void executeCommand(const char *command){
    Serial.print("Executing command: ");
    Serial.println(command);

}

// Function for sending a packet
void sendPacket(const char *data){
    Serial.print("Sending packet with data: ");
    Serial.println(data);
}

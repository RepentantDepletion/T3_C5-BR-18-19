#define PACKAGE t3_c5_br

#include "SpeedManagement.h"
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

DataProcessing data;

// Main function
int main()
{
    data.receivePacket();
    data.executeCommand()
}

void setupWifiConnection()
{
    Serial.begin(115200);
    delay(1000);

    WiFi.mode(WIFI_STA); // optional
    WiFi.begin(ssid);
    Serial.println("\nconnecting");

    while(WiFi.status() != WL_CONNECTING){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

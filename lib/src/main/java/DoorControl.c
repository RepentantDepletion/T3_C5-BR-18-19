#include <stdio.h>
#include <string.h>

// DoorControl structure
typedef struct {
    char doorStatus[10]; // Door status as a string
} DoorControl;

// Function to initialize the DoorControl structure
void initDoorControl(DoorControl *dc) {
    strcpy(dc->doorStatus, "closed"); // Default status
}

// Function to get the current door status
const char* getDoorStatus(DoorControl *dc) {
    return dc->doorStatus;
}

// Function to open the door
void openDoor(DoorControl *dc) {
    strcpy(dc->doorStatus, "open");
    printf("Door opened.\n");
}

// Function to close the door
void closeDoor(DoorControl *dc) {
    strcpy(dc->doorStatus, "closed");
    printf("Door closed.\n");
}
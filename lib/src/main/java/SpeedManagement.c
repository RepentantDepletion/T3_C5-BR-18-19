#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float currentSpeed;
    int isSpeedSet;
} SpeedManagement;

SpeedManagement* createSpeedManagement() {
    SpeedManagement* sm = (SpeedManagement*) malloc(sizeof(SpeedManagement));
    if (sm != NULL) {
        sm->currentSpeed = 0.0;
        sm->isSpeedSet = 0;
    }
    return sm;
}


/*
void initSpeedManagement(SpeedManagement *sm) {
    sm->currentSpeed = 0.0;
    sm->isSpeedSet = 0;
}
*/

void setSpeed(SpeedManagement *sm, float speed) {
    // actual speed setting
    sm->currentSpeed = speed;
    sm->isSpeedSet = 1; // checks if the speed was set
    printf("Speed set to: %.2f cm/s\n", sm->currentSpeed);
}

int confirmSpeedSet(SpeedManagement *sm) {
    // confirms if the speed was successfully set
    return sm->isSpeedSet;
}

float getCurrentSpeed(SpeedManagement *sm) {
    return sm->currentSpeed;
}

//function to receive commands from Java
void receiveCommandFromJava(const char* command) {
    printf("Received command: %s\n", command);
}

//test function
int main() {
    SpeedManagement sm;
    initSpeedManagement(&sm);

    setSpeed(&sm, 75.0);
    if (confirmSpeedSet(&sm)) {
        printf("Speed was successfully set!\n");
    } else {
        printf("Failed to set speed.\n");
    }
    return 0;
}
//package t3_c5.br;

/*
public class SensorFeedback {
    private String sensorStatus;

    public SensorFeedback() {
        this.sensorStatus = "normal"; // Default sensor status
    }

    public String getSensorStatus() {
        return sensorStatus;
    }

    public void updateSensorStatus(String status) {
        this.sensorStatus = status;
        System.out.println("Sensor status updated to: " + sensorStatus);
    }
}
*/

#include <stdio.h>
#include <string.h>

// Define the SensorFeedback struct
typedef struct {
    char sensorStatus[20];
} SensorFeedback;

// Initialize the SensorFeedback object
void initSensorFeedback(SensorFeedback* sf) {
    strcpy(sf->sensorStatus, "normal"); // Default sensor status
}

// Get the sensor status
const char* getSensorStatus(SensorFeedback* sf) {
    return sf->sensorStatus;
}

// Update the sensor status
void updateSensorStatus(SensorFeedback* sf, const char* status) {
    strcpy(sf->sensorStatus, status);
    printf("Sensor status updated to: %s\n", sf->sensorStatus);
}

int main() {
    // Create a SensorFeedback object
    SensorFeedback sf;
    
    // Initialize the SensorFeedback object
    initSensorFeedback(&sf);
    
    // Test the sensor feedback methods
    printf("Initial Sensor Status: %s\n", getSensorStatus(&sf));
    updateSensorStatus(&sf, "warning");
    printf("Current Sensor Status: %s\n", getSensorStatus(&sf));
    updateSensorStatus(&sf, "critical");
    printf("Current Sensor Status: %s\n", getSensorStatus(&sf));
    
    return 0;
}

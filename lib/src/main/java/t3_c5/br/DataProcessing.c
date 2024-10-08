#define package t3_c5.br;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMPONENTS 10
#define MAX_COMMANDS 10
#define MAX_KEY_LENGTH 50
#define MAX_VALUE_LENGTH 100

typedef struct {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
} CommandData;

typedef struct {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
} ComponentData;

typedef struct {
    ComponentData componentData[MAX_COMPONENTS];
    CommandData commandData[MAX_COMMANDS];
    char stationID[MAX_VALUE_LENGTH];
    int componentCount;
    int commandCount;
} DataProcessing;

void initDataProcessing(DataProcessing *dp) {
    dp->componentCount = 0;
    dp->commandCount = 0;
    strcpy(dp->stationID, "");
}

void setStationID(DataProcessing *dp, const char *stationID) {
    strcpy(dp->stationID, stationID);
    // Also store in commandData (for simplicity, we overwrite if it exists)
    strcpy(dp->commandData[0].key, "stationID");
    strcpy(dp->commandData[0].value, stationID);
}

const char* getStationID(DataProcessing *dp) {
    return dp->stationID;
}

void processCarriageCommand(DataProcessing *dp, const char *command) {
    char commandType[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
    sscanf(command, "%[^:]:%s", commandType, value);

    if (strcmp(commandType, "set_speed") == 0) {
        strcpy(dp->commandData[1].key, "speed");
        strcpy(dp->commandData[1].value, value);
    } else if (strcmp(commandType, "set_door_status") == 0) {
        strcpy(dp->commandData[2].key, "doorStatus");
        strcpy(dp->commandData[2].value, value);
    } else if (strcmp(commandType, "set_status") == 0) {
        strcpy(dp->commandData[3].key, "status");
        strcpy(dp->commandData[3].value, value);
    } else if (strcmp(commandType, "set_station_id") == 0) {
        setStationID(dp, value);
    } else {
        printf("Unknown command: %s\n", command);
    }
}

void storeComponentData(DataProcessing *dp, const char *key, const char *data) {
    if (dp->componentCount < MAX_COMPONENTS) {
        strcpy(dp->componentData[dp->componentCount].key, key);
        strcpy(dp->componentData[dp->componentCount].value, data);
        dp->componentCount++;
    }
}

void executeCommand(DataProcessing *dp, const char *Command) {
    char action[10];
    sscanf(Command, "%s", action);


    switch(Command)
    case "FFASTC":
        SpeedManagement.increaseSpeed();
    if (strcmp(action, "FFASTC") == 0) {
        strcpy(dp->commandData[1].key, "speed");
    } else if (strcmp(action, "open_door") == 0) {
        strcpy(dp->commandData[2].key, "doorStatus");
        strcpy(dp->commandData[2].value, "open");
    } else if (strcmp(action, "close_door") == 0) {
        strcpy(dp->commandData[2].key, "doorStatus");
        strcpy(dp->commandData[2].value, "closed");
    } else if (strcmp(action, "update_status") == 0) {
        strcpy(dp->commandData[3].key, "status");
        strcpy(dp->commandData[3].value, value);
    } else {
        printf("Unknown action: %s\n", action);
    }
}

void sendCarriageMessage(const char *message) {
    printf("Sending message to Carriage Control Program: %s\n", message);
}

const char* receiveCarriageCommand() {
    return "set_speed:80.5"; // Returning a dummy command for simulation
}

int main() {
    DataProcessing dp;
    initDataProcessing(&dp);

    // Simulating command processing
    const char *command = receiveCarriageCommand();
    processCarriageCommand(&dp, command);
    storeComponentData(&dp, "feedback", "All systems operational.");
    sendRelevantDataToMCP(&dp);

    return 0;
}


/*
package t3_c5.br;

import java.util.HashMap;
import java.util.Map;

import org.json.JSONObject;

public class DataProcessing {

    private Map<String, Object> componentData; // Stores data from various components (e.g., feedback, Aryan's classes)
    private static Map<String, Object> commandData;   // Stores commands and data received from the Carriage Control Program (CCP)
    private String stationID; // Variable to store station ID directly

    // Constructor initializes the componentData and commandData maps
    public DataProcessing() {
        this.componentData = new HashMap<>();
        DataProcessing.commandData = new HashMap<>();
    }

    // Setter method for stationID
    public static void setStationID(String stationID) {
        commandData.put("stationID", stationID); // Also store in commandData map
    }

    // Getter method for stationID
    public String getStationID() {
        return this.stationID;
    }

    // Method to store and process string commands received from the Carriage Control Program (CCP)
    public static void processCarriageCommand(String command) {
        try {
            String[] parts = command.split(":");
            String commandType = parts[0].trim();
            String value = parts.length > 1 ? parts[1].trim() : "";

            switch (commandType) {
                case "set_speed":
                    commandData.put("speed", Float.parseFloat(value));
                    break;
                case "set_door_status":
                    commandData.put("doorStatus", value);
                    break;
                case "set_status":
                    commandData.put("status", value);
                    break;
                case "set_station_id":
                    setStationID(value); // Use the setter for stationID
                    break;
                default:
                    System.out.println("Unknown command: " + command);
            }
        } catch (Exception e) {
            System.out.println("Error processing command: " + e.getMessage());
        }
    }

    // Method to store data from other components (like feedback, Aryan's classes, etc.)
    public void storeComponentData(String key, Object data) {
        componentData.put(key, data);
    }

    // Method to sift through the data and send relevant data to the Master Control Program (MCP)
    public JSONObject sendRelevantDataToMCP() {
        JSONObject mcpData = new JSONObject(); // JSON object to send to MCP

        try {
            // Adding relevant data from commandData to the JSON object
            mcpData.put("door_status", commandData.get("doorStatus"));
            mcpData.put("status", commandData.get("status"));
            mcpData.put("station_id", getStationID()); // Use the getter for stationID

            // Optionally add additional component data if it exists
            if (componentData.containsKey("feedback")) {
                mcpData.put("feedback", componentData.get("feedback"));
            }

        } catch (Exception e) {
            System.out.println("Error creating MCP data JSON: " + e.getMessage());
        }

        return mcpData; // Return the created JSON object to be sent to MCP
    }

    // Method to execute commands received from the Master Control Program (MCP)
    public void executeMCPCommand(JSONObject execCommand) {
        try {
            String action = execCommand.optString("action"); // Extract the action command from the JSON object
            if (action != null && !action.isEmpty()) {
                // Execute the appropriate command based on the action value
                switch (action) {
                    case "update_speed":
                        commandData.put("speed", (float) execCommand.getDouble("speed"));
                        break;
                    case "open_door":
                        commandData.put("doorStatus", "open");
                        break;
                    case "close_door":
                        commandData.put("doorStatus", "closed");
                        break;
                    case "update_status":
                        commandData.put("status", execCommand.getString("status"));
                        break;
                    case "update_sensor_status":
                        commandData.put("sensorStatus", execCommand.getString("sensor_status"));
                        break;
                    default:
                        System.out.println("Unknown action: " + action); // Handle unknown actions
                }
            }
        } catch (Exception e) {
            System.out.println("Error processing execution JSON: " + e.getMessage());
        }
    }

    // Method to simulate sending a message to the Carriage Control Program (CCP)
    public void sendCarriageMessage(JSONObject message) {
        System.out.println("Sending message to Carriage Control Program: " + message.toString());
        // Here you would actually send the message to the Carriage Control Program
    }

    // Method to simulate receiving a message from the Carriage Control Program (CCP)
    public String receiveCarriageCommand() {
        System.out.println("Receiving command from Carriage Control Program...");
        // Here you would actually receive the command from the Carriage Control Program
        return "set_speed:80.5"; // Returning a dummy command for simulation
    }
}
*/

/* 
//code before setter - getter 
package t3_c5.br;

import org.json.JSONObject;
import java.util.HashMap;
import java.util.Map;

public class DataProcessing {

    private Map<String, Object> componentData; // Stores data from various components (e.g., feedback, Aryan's classes)
    private Map<String, Object> commandData;   // Stores commands and data received from the Carriage Control Program (CCP)

    // Constructor initializes the componentData and commandData maps
    public DataProcessing() {
        this.componentData = new HashMap<>();
        this.commandData = new HashMap<>();
    }

    // Method to store data received from the Carriage Control Program (CCP)
    public void storeCarriageData(JSONObject carriageData) {
        try {
            // Storing relevant data fields from the received JSON object
            commandData.put("speed", carriageData.getFloat("speed"));
            commandData.put("doorStatus", carriageData.getString("door_status"));
            commandData.put("status", carriageData.getString("status"));
            commandData.put("sensorStatus", carriageData.getString("sensor_status"));
            commandData.put("batteryLevel", carriageData.getFloat("battery_level"));
            commandData.put("stationID", carriageData.getString("station_id"));
        } catch (Exception e) {
            System.out.println("Error storing carriage data: " + e.getMessage());
        }
    }

    // Method to store data from other components (like feedback, Aryan's classes, etc.)
    public void storeComponentData(String key, Object data) {
        componentData.put(key, data);
    }

    // Method to sift through the data and send relevant data to the Master Control Program (MCP)
    public JSONObject sendRelevantDataToMCP() {
        JSONObject mcpData = new JSONObject(); // JSON object to send to MCP

        try {
            // Adding relevant data from commandData to the JSON object
            mcpData.put("speed", commandData.get("speed"));
            mcpData.put("door_status", commandData.get("doorStatus"));
            mcpData.put("status", commandData.get("status"));
            mcpData.put("sensor_status", commandData.get("sensorStatus"));
            mcpData.put("battery_level", commandData.get("batteryLevel"));
            mcpData.put("station_id", commandData.get("stationID"));

            // Optionally add additional component data if it exists
            if (componentData.containsKey("feedback")) {
                mcpData.put("feedback", componentData.get("feedback"));
            }

            // Placeholder for adding any other relevant data from Aryan's classes
            // Example: mcpData.put("aryan_class_data", componentData.get("aryan_class_key"));

        } catch (Exception e) {
            System.out.println("Error creating MCP data JSON: " + e.getMessage());
        }

        return mcpData; // Return the created JSON object to be sent to MCP
    }

    // Method to execute commands received from the Master Control Program (MCP)
    public void executeMCPCommand(JSONObject execCommand) {
        try {
            String action = execCommand.optString("action"); // Extract the action command from the JSON object
            if (action != null && !action.isEmpty()) {
                // Execute the appropriate command based on the action value
                switch (action) {
                    case "update_speed":
                        commandData.put("speed", (float) execCommand.getDouble("speed"));
                        break;
                    case "open_door":
                        commandData.put("doorStatus", "open");
                        break;
                    case "close_door":
                        commandData.put("doorStatus", "closed");
                        break;
                    case "update_status":
                        commandData.put("status", execCommand.getString("status"));
                        break;
                    case "update_sensor_status":
                        commandData.put("sensorStatus", execCommand.getString("sensor_status"));
                        break;
                    default:
                        System.out.println("Unknown action: " + action); // Handle unknown actions
                }
            }
        } catch (Exception e) {
            System.out.println("Error processing execution JSON: " + e.getMessage());
        }
    }

    // Method to simulate sending a message to the Carriage Control Program (CCP)
    public void sendCarriageMessage(JSONObject message) {
        System.out.println("Sending message to Carriage Control Program: " + message.toString());
        // Here you would actually send the message to the Carriage Control Program
    }

    // Method to simulate receiving a message from the Carriage Control Program (CCP)
    public JSONObject receiveCarriageMessage() {
        System.out.println("Receiving message from Carriage Control Program...");
        // Here you would actually receive the message from the Carriage Control Program
        return new JSONObject(); // Returning a dummy JSON object
    }
}
*/

/* 
package t3_c5.br;

import org.json.JSONObject;
import java.util.HashMap;
import java.util.Map;

public class DataProcessing {

    private Map<String, Object> componentData;
    private Map<String, Object> commandData;

    // Constructor
    public DataProcessing() {
        this.componentData = new HashMap<>();
        this.commandData = new HashMap<>();
    }

    // Method to store data received from the Carriage Control Program
    public void storeCarriageData(JSONObject carriageData) {
        try {
            commandData.put("speed", carriageData.getFloat("speed"));
            commandData.put("doorStatus", carriageData.getString("door_status"));
            commandData.put("status", carriageData.getString("status"));
            commandData.put("sensorStatus", carriageData.getString("sensor_status"));
            commandData.put("batteryLevel", carriageData.getFloat("battery_level"));
            commandData.put("stationID", carriageData.getString("station_id"));
        } catch (Exception e) {
            System.out.println("Error storing carriage data: " + e.getMessage());
        }
    }

    // Method to store data from other components (like feedback, Aryan's classes, etc.)
    public void storeComponentData(String key, Object data) {
        componentData.put(key, data);
    }

    // Method to sift through the data and send relevant data to MCP
    public JSONObject sendRelevantDataToMCP() {
        // Create a JSON object to send to MCP with relevant data
        JSONObject mcpData = new JSONObject();

        // Add data from commandData and componentData that is relevant to MCP
        try {
            mcpData.put("speed", commandData.get("speed"));
            mcpData.put("door_status", commandData.get("doorStatus"));
            mcpData.put("status", commandData.get("status"));
            mcpData.put("sensor_status", commandData.get("sensorStatus"));
            mcpData.put("battery_level", commandData.get("batteryLevel"));
            mcpData.put("station_id", commandData.get("stationID"));

            // Add any additional component data if needed
            if (componentData.containsKey("feedback")) {
                mcpData.put("feedback", componentData.get("feedback"));
            }

            // Add any other relevant data from Aryan's classes
            // Example: mcpData.put("aryan_class_data", componentData.get("aryan_class_key"));

        } catch (Exception e) {
            System.out.println("Error creating MCP data JSON: " + e.getMessage());
        }

        return mcpData;
    }

    // Method to execute commands from MCP
    public void executeMCPCommand(JSONObject execCommand) {
        try {
            String action = execCommand.optString("action");
            if (action != null && !action.isEmpty()) {
                switch (action) {
                    case "update_speed":
                        commandData.put("speed", (float) execCommand.getDouble("speed"));
                        break;
                    case "open_door":
                        commandData.put("doorStatus", "open");
                        break;
                    case "close_door":
                        commandData.put("doorStatus", "closed");
                        break;
                    case "update_status":
                        commandData.put("status", execCommand.getString("status"));
                        break;
                    case "update_sensor_status":
                        commandData.put("sensorStatus", execCommand.getString("sensor_status"));
                        break;
                    default:
                        System.out.println("Unknown action: " + action);
                }
            }
        } catch (Exception e) {
            System.out.println("Error processing execution JSON: " + e.getMessage());
        }
    }

    // Method to simulate sending a message to the Carriage Control Program
    public void sendCarriageMessage(JSONObject message) {
        System.out.println("Sending message to Carriage Control Program: " + message.toString());
        // Here you would actually send the message to the Carriage Control Program
    }

    // Method to simulate receiving a message from the Carriage Control Program
    public JSONObject receiveCarriageMessage() {
        System.out.println("Receiving message from Carriage Control Program...");
        // Here you would actually receive the message from the Carriage Control Program
        return new JSONObject(); // Returning a dummy JSON object
    }
}

*/


// old code - trystan - 3/9/24
/* 
//Data processing 

package t3_c5.br;
import org.json.JSONObject;
import java.util.HashMap;
import java.util.Map;

public class DataProcessing {
       // change "SystemController" name to whatever class youre extendinh

    private Map<String, Object> componentData;
    private Map<String, Object> commandData;
    
    // Constructor
    public DataProcessing() {
        this.componentData = new HashMap<>();
        this.commandData = new HashMap<>();
    }

    // Method to store data received from the Carriage Control Program
    public void storeCarriageData(JSONObject carriageData) {
        try {
            commandData.put("speed", carriageData.getFloat("speed"));
            commandData.put("doorStatus", carriageData.getString("door_status"));
            commandData.put("status", carriageData.getString("status"));
            commandData.put("sensorStatus", carriageData.getString("sensor_status"));
            commandData.put("batteryLevel", carriageData.getFloat("battery_level"));
            commandData.put("stationID", carriageData.getString("station_id"));
        } catch (Exception e) {
            System.out.println("Error storing carriage data: " + e.getMessage());
        }
    }

    // Method to store data from other components (like feedback, Aryan's classes, etc.)
    public void storeComponentData(String key, Object data) {
        componentData.put(key, data);
    }

    // Method to sift through the data and send relevant data to MCP
    public JSONObject sendRelevantDataToMCP() {
        // Create a JSON object to send to MCP with relevant data
        JSONObject mcpData = new JSONObject();

        // Add data from commandData and componentData that is relevant to MCP
        try {
            mcpData.put("speed", commandData.get("speed"));
            mcpData.put("door_status", commandData.get("doorStatus"));
            mcpData.put("status", commandData.get("status"));
            mcpData.put("sensor_status", commandData.get("sensorStatus"));
            mcpData.put("battery_level", commandData.get("batteryLevel"));
            mcpData.put("station_id", commandData.get("stationID"));

            // Add any additional component data if needed
            if (componentData.containsKey("feedback")) {
                mcpData.put("feedback", componentData.get("feedback"));
            }

            // Add any other relevant data from Aryan's classes
            // Example: mcpData.put("aryan_class_data", componentData.get("aryan_class_key"));

        } catch (Exception e) {
            System.out.println("Error creating MCP data JSON: " + e.getMessage());
        }

        return mcpData;
    }

    // Method to execute commands from MCP
    public void executeMCPCommand(JSONObject execCommand) {
        try {
            String action = execCommand.optString("action");
            if (action != null && !action.isEmpty()) {
                switch (action) {
                    case "update_speed":
                        commandData.put("speed", (float) execCommand.getDouble("speed"));
                        break;
                    case "open_door":
                        commandData.put("doorStatus", "open");
                        break;
                    case "close_door":
                        commandData.put("doorStatus", "closed");
                        break;
                    case "update_status":
                        commandData.put("status", execCommand.getString("status"));
                        break;
                    case "update_sensor_status":
                        commandData.put("sensorStatus", execCommand.getString("sensor_status"));
                        break;
                    default:
                        System.out.println("Unknown action: " + action);
                }
            }
        } catch (Exception e) {
            System.out.println("Error processing execution JSON: " + e.getMessage());
        }
    }

    // Method to simulate sending a message to the Carriage Control Program
    public void sendCarriageMessage(JSONObject message) {
        System.out.println("Sending message to Carriage Control Program: " + message.toString());
        // Here you would actually send the message to the Carriage Control Program
    }

    // Method to simulate receiving a message from the Carriage Control Program
    public JSONObject receiveCarriageMessage() {
        System.out.println("Receiving message from Carriage Control Program...");
        // Here you would actually receive the message from the Carriage Control Program
        return new JSONObject(); // Returning a dummy JSON object
    }
}
*/